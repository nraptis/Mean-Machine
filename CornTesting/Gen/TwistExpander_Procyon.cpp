#include "TwistExpander_Procyon.hpp"
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

TwistExpander_Procyon::TwistExpander_Procyon()
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

void TwistExpander_Procyon::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xEA36178BBDD46D42ULL; std::uint64_t aIngress = 0xABBE6ADFEEE52B63ULL; std::uint64_t aCarry = 0x8AE671E4DA3BC160ULL;

    std::uint64_t aWandererA = 0x86C541F406A9A520ULL; std::uint64_t aWandererB = 0x8669A4DD2A64D8ABULL; std::uint64_t aWandererC = 0xA5872F9371320EC0ULL; std::uint64_t aWandererD = 0xEBCB826208E9EEE3ULL;
    std::uint64_t aWandererE = 0x8EA2A8C997BC9FF2ULL; std::uint64_t aWandererF = 0xBEDFD4A954EC4747ULL; std::uint64_t aWandererG = 0xC97EFC4F4C20440EULL; std::uint64_t aWandererH = 0xE6AF3446F56DBF89ULL;
    std::uint64_t aWandererI = 0x8FD7E5B9FEB41AF9ULL; std::uint64_t aWandererJ = 0xC7B9E11658C7AEE4ULL; std::uint64_t aWandererK = 0xCA8C6109FBA236BDULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17213001368729977784U;
        aCarry = 14875007031344707797U;
        aWandererA = 9872425117746802469U;
        aWandererB = 14651122759216383678U;
        aWandererC = 15490674099305888710U;
        aWandererD = 15412118822242692804U;
        aWandererE = 10531530145734213764U;
        aWandererF = 13484764838642173486U;
        aWandererG = 15190285081491792518U;
        aWandererH = 14775188640002311995U;
        aWandererI = 17373423116776054635U;
        aWandererJ = 10851743273195967806U;
        aWandererK = 9541469299160763732U;
    TwistExpander_Procyon_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Procyon_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Procyon_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Procyon_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Procyon_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Procyon::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC26051273E2C2627ULL; std::uint64_t aIngress = 0x9FF6B94D9CB0F2B8ULL; std::uint64_t aCarry = 0xBD2F1985E2C53248ULL;

    std::uint64_t aWandererA = 0xB100E572BB967A57ULL; std::uint64_t aWandererB = 0xA0AC94D5132CF9FDULL; std::uint64_t aWandererC = 0x9CBFC3E36D359D82ULL; std::uint64_t aWandererD = 0x84FA67686AB9B83DULL;
    std::uint64_t aWandererE = 0x8E49D7351465B376ULL; std::uint64_t aWandererF = 0xE102ABFBB2408658ULL; std::uint64_t aWandererG = 0xC0A66560061E38B7ULL; std::uint64_t aWandererH = 0xBFF37F6DED88616BULL;
    std::uint64_t aWandererI = 0xEA1BF36A8CBBBB60ULL; std::uint64_t aWandererJ = 0x83416CCA438F3417ULL; std::uint64_t aWandererK = 0xA3B38C9879F98D43ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14790689312402361064U;
        aCarry = 9980489537329728629U;
        aWandererA = 10762152801008087627U;
        aWandererB = 14572567337212085614U;
        aWandererC = 14387194502785153269U;
        aWandererD = 10186128444439846095U;
        aWandererE = 9387490610539977837U;
        aWandererF = 13297543038467413430U;
        aWandererG = 15783834199404236558U;
        aWandererH = 11986802564675736703U;
        aWandererI = 14636936098487111432U;
        aWandererJ = 13742383291180811622U;
        aWandererK = 10310955371991146285U;
    TwistExpander_Procyon_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Procyon_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Procyon_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Procyon_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Procyon::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x9D44DD65E55988ECULL;
    std::uint64_t aIngress = 0x8B852CE7A02B9670ULL;
    std::uint64_t aCarry = 0x9A66346FFDA119ACULL;

    std::uint64_t aWandererA = 0x9C59BB1FF9EE0B2FULL;
    std::uint64_t aWandererB = 0xF08EE5072C461466ULL;
    std::uint64_t aWandererC = 0xC74EAAA5ABA80FBAULL;
    std::uint64_t aWandererD = 0xAFF90BA511A0D5D2ULL;
    std::uint64_t aWandererE = 0xF7911D294D4C39DDULL;
    std::uint64_t aWandererF = 0xF430AED27DCB62D3ULL;
    std::uint64_t aWandererG = 0xFF8B97B5AE3AA057ULL;
    std::uint64_t aWandererH = 0x82711ED805BE2235ULL;
    std::uint64_t aWandererI = 0x89151EE6513F4EA7ULL;
    std::uint64_t aWandererJ = 0xB0FBCF130F175A24ULL;
    std::uint64_t aWandererK = 0x93809B5F12355365ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
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
    TwistExpander_Procyon_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
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
    TwistExpander_Procyon_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Procyon_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Procyon_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 26 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 45307
void TwistExpander_Procyon::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1286U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2004U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1712U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 361U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1688U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1372U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1369U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1121U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1195U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1459U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 380U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 441U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1753U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1929U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 820U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1772U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1213U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 417U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1855U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1635U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 461U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1137U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1013U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1671U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 783U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 367U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1922U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1582U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1059U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1295U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 842U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 686U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 299U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 539U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 174U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1382U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 889U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 728U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1547U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 306U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 199U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 734U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 887U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1076U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2042U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1925U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1241U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 168U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 569U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1355U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1253U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 235U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1594U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1412U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 401U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 99U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1397U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 536U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 787U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 38U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 544U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1974U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1579U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1852U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1959U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1328U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1518U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 562U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 604U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1609U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1826U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 816U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 90U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1235U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 504U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 586U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1616U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1782U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1248U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1455U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 111U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1123U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 387U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1915U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1127U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1166U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 37U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1007U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1716U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 921U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 335U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1387U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1391U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 634U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 984U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2028U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 262U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 793U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 280U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 429U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 809U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 963U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1441U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1298U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 503U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1146U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1653U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 415U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 455U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1103U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 766U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1350U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 204U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 638U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 82U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1494U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 383U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 325U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 391U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 761U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 729U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 792U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 342U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 612U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 22U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 691U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 876U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1089U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Procyon::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC80961DCC9D398F8ULL; std::uint64_t aIngress = 0x86171D68F1B79FFAULL; std::uint64_t aCarry = 0xF3EEE1A6E7F81AABULL;

    std::uint64_t aWandererA = 0xE8C9AC129245B37FULL; std::uint64_t aWandererB = 0xDEE868352310D1D1ULL; std::uint64_t aWandererC = 0x8B5401574A91B2D1ULL; std::uint64_t aWandererD = 0xB57EB5D5DA7D0421ULL;
    std::uint64_t aWandererE = 0x9B1B62A2C83B3767ULL; std::uint64_t aWandererF = 0xC8EBA713250EB322ULL; std::uint64_t aWandererG = 0x9FF885CB375B5624ULL; std::uint64_t aWandererH = 0xC08A410AE3736519ULL;
    std::uint64_t aWandererI = 0x9FA24BB91BFF7B9AULL; std::uint64_t aWandererJ = 0xDF0EBD71D5518693ULL; std::uint64_t aWandererK = 0xB3D77DFE164BB6F0ULL;

    // [seed]
        aPrevious = 13599958394499545979U;
        aCarry = 14804488615362716795U;
        aWandererA = 15225287945014534816U;
        aWandererB = 10078498956943732284U;
        aWandererC = 15543381661666413520U;
        aWandererD = 15250994073941674048U;
        aWandererE = 16288279894371138817U;
        aWandererF = 9527049265762626253U;
        aWandererG = 9332801350920027437U;
        aWandererH = 17773938685296765651U;
        aWandererI = 15494454871083484151U;
        aWandererJ = 14587905114710778434U;
        aWandererK = 9811054137782611650U;
    TwistExpander_Procyon_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Procyon_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Procyon_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Procyon_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Procyon_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 26 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13528; nearest pair: 467 / 674
void TwistExpander_Procyon::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7073U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 907U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1840U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2175U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 692U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1733U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1939U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5094U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 221U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6356U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7458U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6166U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7695U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2351U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 238U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2874U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 514U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1108U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1690U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 672U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 857U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 418U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 115U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1401U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1193U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1428U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 173U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2029U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 799U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1985U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 666U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 359U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 821U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 937U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1672U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1074U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 26 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 13520; nearest pair: 476 / 674
void TwistExpander_Procyon::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4639U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2048U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7577U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8034U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2897U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 609U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 781U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6269U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1558U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5701U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2833U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6755U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 8128U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 115U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5734U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5018U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 266U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 408U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 571U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1049U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 368U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1870U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1303U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2011U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 521U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1921U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1258U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 202U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 918U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 829U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 942U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2024U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1832U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 907U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1913U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 701U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseASalts = {
    {
        {
            0x79EAAD49CF9C1AB3ULL, 0xB0CE77B96D953089ULL, 0xBA0ECB14B429A134ULL, 0x4EC9516E6E00AD73ULL, 
            0xFF728743AB613742ULL, 0x52E3AFC840D78E72ULL, 0x1A32EE804AE47245ULL, 0x4988C5EA70D04CB6ULL, 
            0x79B9202BECBF0447ULL, 0xCC5CBB043381F57FULL, 0x1FF39F58FD163483ULL, 0xFC7AD2783A02A9B2ULL, 
            0x3DF13CB656DACA20ULL, 0x4AA7B4B94E14CDADULL, 0xDBB0C3D112711679ULL, 0xE0014CCB851EF085ULL, 
            0xDCE8F8DFC2305925ULL, 0x9C08541010B6AEBEULL, 0x913E8A14536ACC7AULL, 0x490084196803761DULL, 
            0x30979F1692DF2377ULL, 0xE99BC46D2E47A7A0ULL, 0x569169F8A73F3B79ULL, 0x010392144B4FE892ULL, 
            0x2C738C999E31554EULL, 0xAD6F7BEE0279FE9BULL, 0x752A2A6D4159A776ULL, 0xB3790B3F1B68D7EBULL, 
            0x84F73026CA5E2B73ULL, 0xE099ECA5FEB0B310ULL, 0x7FE46F93C9680449ULL, 0xA9FEF7AE712AD4F6ULL
        },
        {
            0x417C68D3BBBF25B8ULL, 0x0195D8ADF5FBDBB3ULL, 0x0C63ADF0629BFDC8ULL, 0xFBD52611924C3F19ULL, 
            0xDE858C85AC2F6CEBULL, 0xB8B05139E70AAF88ULL, 0x1B2C113818B54806ULL, 0x3B05F00788512BEDULL, 
            0x89D0B8BAB8C43953ULL, 0xBF5A421403278A94ULL, 0x41F5136347C54F1FULL, 0x719C826A2FF80246ULL, 
            0x61F452E85737CD50ULL, 0x237D1F85F156D5D5ULL, 0x9376019FBAB995CAULL, 0x01DED63A047FD089ULL, 
            0xAA62658B957C6DF0ULL, 0xF5F3BDF9A668CBF8ULL, 0xBBB2834848AFCF14ULL, 0x1255D9A5B4650EE3ULL, 
            0x47F3B0A53823F572ULL, 0xAFE473F2983CFD2AULL, 0x8B5EB6770FDE7F7AULL, 0x92A7AE31A74B5FFBULL, 
            0x8B3D3C8780CA44CAULL, 0xF4F6DEA7124D5CDAULL, 0xD40F24C33C1B244CULL, 0x8507D353A3D84F71ULL, 
            0x98485E0E1828A2C2ULL, 0x8FE0A63EB2D660BAULL, 0x8A1579AC56839921ULL, 0x924EB4F324D1DA66ULL
        },
        {
            0x1B48622C127D202BULL, 0x0268FCE84C8B8606ULL, 0x6C14C9470A46E903ULL, 0x037E2AA13C59B9C0ULL, 
            0xC9B0A1E35749E4E8ULL, 0xC7758FB1CB79537AULL, 0xD167EDD0B6E5DEC6ULL, 0x207855F22B917A65ULL, 
            0x420CDD366DDD42A6ULL, 0x24D47977A8F4B287ULL, 0x6DDB4B1515D4E811ULL, 0xF85E6389C8CD6EA4ULL, 
            0x54E2C3C1689D59DEULL, 0x8BDD3EC4DACFF213ULL, 0xB20D2AD5FC817BD5ULL, 0x1A0CDED5A9951095ULL, 
            0x2B39AE8691DF41FBULL, 0xB3B7F27CEC96F39BULL, 0xD6CE56BEBB40323EULL, 0x9A7CB4A0E8D0D68AULL, 
            0x1419478EB21A4D1AULL, 0x8BDADE01923EC306ULL, 0x8DC74FFCCABF1B8FULL, 0xC8AE8A5623F195A1ULL, 
            0x92E8C1A96A8AD90DULL, 0xCA1B9A816A88EA4BULL, 0xFF2D6BC7D5EA9BA7ULL, 0x6DB0BD9F717445C6ULL, 
            0xF817ED62D642C07EULL, 0x8278BDABC902922EULL, 0xD284EA157F646D04ULL, 0x894AF901CC730A9DULL
        },
        {
            0xD4039858AB4AE625ULL, 0x7DBC17DDF84E0F7BULL, 0x3BA380265E875863ULL, 0xC48EC035017F9638ULL, 
            0xE3B43CC440907E07ULL, 0xAFB858D31C29DFE7ULL, 0xB796B1DAB34C47FCULL, 0x59DB51C32893387EULL, 
            0xD5F8121BA2EDE5DDULL, 0x950FF9E20760C891ULL, 0x77381CD8D5C511E6ULL, 0x8239A992CE68AF2FULL, 
            0x3F7FF1E91BF23269ULL, 0x228B691EAB61A263ULL, 0x84C7C20FD44DD312ULL, 0x1857C88C8777D614ULL, 
            0xD159D442E7F61BF4ULL, 0xFA3302B2F5E0258DULL, 0x26C556F55B0170AEULL, 0x7E92594D27615DAEULL, 
            0x43E7E9377D822C95ULL, 0xAD0FCF9D6ECC2624ULL, 0x66DBA0FE2FCC4696ULL, 0x8645057A827B59D8ULL, 
            0x225C7E38D221205AULL, 0xB56C4B530DD4CC46ULL, 0x699EC08D9A21268EULL, 0x18C3E5CD8271CCCCULL, 
            0xEF6C19B6140DC552ULL, 0x8B905E663DDF890AULL, 0x903931756EB24481ULL, 0x97A91CA6B7762046ULL
        },
        {
            0x42E8035E8A9AFDDFULL, 0x5A56B847FC751906ULL, 0x04FD0596B4C1EB10ULL, 0xF8A698C321468860ULL, 
            0xFF5D31859DB0F36CULL, 0x6B49C1613A660F03ULL, 0x25BD2512484EB4B7ULL, 0x2AF3DB393D3FD769ULL, 
            0xC8ED42AD78704521ULL, 0xDB4627C0D9F3F644ULL, 0xC68F635BCD9E1F6FULL, 0xE548B5A31E116CCFULL, 
            0x649E946397D6C74EULL, 0x08E3FD939026D644ULL, 0xB3961A98AE9176BDULL, 0x533CCF4EBB233237ULL, 
            0xB0768BC9B0E98959ULL, 0xB2EC5399CC88B32DULL, 0x97406B5E8E0CDF4EULL, 0x6B41615EEC5E0F89ULL, 
            0x7F8EEDDA90FC853AULL, 0xF1E688F207C1C0BCULL, 0xB53F377D339F2376ULL, 0x157FC836F3700541ULL, 
            0x33010F4E494A2273ULL, 0xC444058D65AAEC2CULL, 0x3A1C664526E899B5ULL, 0x2FFF5EF256DD9491ULL, 
            0x0197971C5AFE956DULL, 0x957220E002D564AEULL, 0xB6C370C6B76DEC77ULL, 0xE6517C529E424986ULL
        },
        {
            0xABF6057F3207C0DCULL, 0xF5942673C820FBCAULL, 0x2F82E747402C2DB0ULL, 0x6A2BE24A54672607ULL, 
            0x3D8ADD16C43EEADFULL, 0x817B5247750FFDD3ULL, 0x95B1DDBCD34611EDULL, 0x767ACB50529EB0E7ULL, 
            0x573EC029A2C32530ULL, 0x378AB3DD0521F2D9ULL, 0xEF257BD527A15791ULL, 0x3FD00E7F8EDD4358ULL, 
            0x5DF88DDEF45C2CCEULL, 0x99D3DBCF50A71003ULL, 0xA3676B747FCE940AULL, 0x0C89FDE6CDC8679AULL, 
            0x572BE5A3699DF0E3ULL, 0x830CDD557808FF4EULL, 0x382967D49DD2C535ULL, 0x4ECD558ED40F0EF5ULL, 
            0x6E072626BAD640DBULL, 0xE69B8EFFD518756EULL, 0x9573B390E5C74E3AULL, 0x761920EF5D9BDF32ULL, 
            0xCE5F128315B694FBULL, 0xAC2A904567542CF3ULL, 0xDB9AA604DADB8CA5ULL, 0xA7FD8A83E3385690ULL, 
            0x0897BFD15CF9CD3EULL, 0xDA308DEDDAB3ED0BULL, 0xA2ACB89E9B7091C8ULL, 0xB47352ED346C4B21ULL
        }
    },
    {
        {
            0x44C3C0A2FDEC5F1BULL, 0xBD19D67E81C94822ULL, 0xABA137FD05F9B983ULL, 0x7B63B60F6E837EAEULL, 
            0x09EF802C25F64E86ULL, 0x770B3FE126ACD36BULL, 0x9DA5309FF072D8D1ULL, 0x4037ED2ED9117515ULL, 
            0xF8BEA2C7188476E9ULL, 0x435A65D5B5A04B6EULL, 0xB4D8E1940420F3E5ULL, 0x8D4FDB658C3F8802ULL, 
            0xAF73DB3CFB251FD3ULL, 0x0712BF65CE35551AULL, 0xEDDC38082CA0A373ULL, 0xBD97D8B977EADCC4ULL, 
            0x6F2FD5B78686DE16ULL, 0x1E239BD4DC7DC8BBULL, 0x3FA720BFB409CE33ULL, 0xBD089FAF40EB890BULL, 
            0x2259B79F67D60853ULL, 0x075EC034FE16CE7CULL, 0x9E68026052215920ULL, 0xE4B75E8C1F303A91ULL, 
            0x35C568A64E40ABABULL, 0xE8656688DC987223ULL, 0xE48DD2BAF18405C3ULL, 0x731E73CE5F947F62ULL, 
            0x073325FC98B02A69ULL, 0x94F3698BBBD19A89ULL, 0xC9FA1E1F46156808ULL, 0xE9EB90CCBCEF49FEULL
        },
        {
            0xBB214741C842EDC7ULL, 0x323A81BB2B361105ULL, 0xF024E49261B40D70ULL, 0xE8F6DBE0A2255824ULL, 
            0xD361788E28790BF2ULL, 0x10F3F5185165D82AULL, 0x5E2E5AC32A3F53AEULL, 0x030D6855E235519AULL, 
            0xCAEBDD88101C531BULL, 0x1E0845088AAF748EULL, 0x5EA6AA6B9534DD8FULL, 0x28852A301E5B5299ULL, 
            0x1C1F1824F846BA40ULL, 0x76055E89F399BF49ULL, 0x54E2204ACAF216AFULL, 0x8263F413A0FFE833ULL, 
            0xE1213C7D803420EFULL, 0x2C1A8A97D6264C56ULL, 0x3447768FEF13F217ULL, 0x3CF9591CA33793BAULL, 
            0x4B2A7993BF9CB1FAULL, 0x8D753882AB81DA23ULL, 0x4951D88303EAD880ULL, 0x17B315DC888EE76DULL, 
            0xFAB4806D3CC9D910ULL, 0xD31AB486B3D4ED6CULL, 0x87A6CE974D1B8810ULL, 0xFD3B7EAEA10CADEBULL, 
            0x12A6670B0AB24B92ULL, 0x68ECD956E43AAD8AULL, 0xCCA32F5047AACFEBULL, 0xBF6D3E7E3104D1DCULL
        },
        {
            0x4CEBDEF67DE5BE87ULL, 0x98F7BF215888308CULL, 0x39F20D0E5A046F7BULL, 0xC032617D99FEAC31ULL, 
            0xB07072417AA8BBF3ULL, 0x88D4383B876E06C0ULL, 0xC4A4EBD2E47261AFULL, 0x5569AA3986D3855AULL, 
            0x41E128D7E68F5647ULL, 0x86FFFF697F28EA17ULL, 0x0863420AAA62BFC0ULL, 0xE2F6E398DA16D26EULL, 
            0x76E0092EBACB9094ULL, 0xDE170D22311580D0ULL, 0xE5A2C83925814B26ULL, 0x2BEC352BD0CE0A87ULL, 
            0x56DD007907EF1E68ULL, 0x7BDEA4226593E08EULL, 0x386F11E66E03DD53ULL, 0xF972AB7740B4E006ULL, 
            0x060B761A443DBE26ULL, 0x23D89C0815562568ULL, 0x7A0D19CF2516F02FULL, 0x8E0FCF318FA20FDFULL, 
            0x8215D0DE0DDAAD9AULL, 0x75821C9EB947B665ULL, 0xD3A8B38429FD015CULL, 0xD55483BA1E23CB62ULL, 
            0xE341C4BF91F561E5ULL, 0xA7B29816156CCEDBULL, 0x30E23576D736DEA3ULL, 0x9CE065B2D049F96AULL
        },
        {
            0xBCA405F458E773ABULL, 0x6C39B46C73FB730DULL, 0x35F63C76071A52FEULL, 0x36CCA1A64FE3117DULL, 
            0x956AE69A84B0D97EULL, 0xFD696F78AB6992A2ULL, 0x1EC840BF6ED6B414ULL, 0x015D184AACD36EE5ULL, 
            0x0292F0D6CD9615C3ULL, 0x933FC42594F0BEC7ULL, 0xBADBAA9C5CB2D3DBULL, 0xB89208FD22F9C878ULL, 
            0x39A6F3700F8DDCF4ULL, 0x8105E2751AA67DD4ULL, 0xEF4C00B54DA32F85ULL, 0x88F2E014F6FD91A0ULL, 
            0xAAFEFF1F366C1B78ULL, 0x9B61FF18BCAA13EBULL, 0x71C75F7B4B3C4ABAULL, 0x41B34EA56B98DA6AULL, 
            0xACA854EB5660F48CULL, 0xD1CCBB51DFDC5058ULL, 0x4507614F615AB7F5ULL, 0xCD7F8594CA823292ULL, 
            0x7038036BF01F5D4DULL, 0x5A1F3672435E6A41ULL, 0xE5AFF6616C3EB8E5ULL, 0xD942B198AFF0664EULL, 
            0x4EDE6E24D2D3D26EULL, 0x545A89CE9AAEB96EULL, 0xCF7F1E726B14BD71ULL, 0x996A08FC324F08EFULL
        },
        {
            0xBCAFAD3EC41988B7ULL, 0x606EE92229C96C7FULL, 0x80D25392C90CE99EULL, 0x573CE6EFEAB2B3A1ULL, 
            0xD6D0A5145F42A3CCULL, 0x26119C56BD775CA1ULL, 0xCE4FFFEE1BE0CB84ULL, 0xA37BAF6D71F1B6D0ULL, 
            0xD6E6744240BDD457ULL, 0xBBEA764184BA67ECULL, 0xFC648AABD5CC41A7ULL, 0x380205AB7B2C94B0ULL, 
            0x3F6271AF997F8011ULL, 0x409671480336B4CBULL, 0xD91A64CEA2C22193ULL, 0xE46808E470931737ULL, 
            0xD0E0087AE913C387ULL, 0x01DE6CEB77C56B0EULL, 0xC80664981717D723ULL, 0x0068367E2E5806DAULL, 
            0xF4F7C800A2B95BA9ULL, 0xDF5D893C357176D4ULL, 0xFFFE7A2D231DECC7ULL, 0x856F293D3BB36602ULL, 
            0x75A634827950BA1BULL, 0xD691EC02204262ADULL, 0x05999B0CE374B873ULL, 0xBBA9DA28262A86AEULL, 
            0x08CB2D9F1DF1A0DEULL, 0x9365CFFCECE1FE6CULL, 0x2461F0549D0B1202ULL, 0x1446D877CD9ABA29ULL
        },
        {
            0xA05DD64E1EE4FFE2ULL, 0x5DD559D27547187AULL, 0x4359B9AA9EC575D0ULL, 0x34844A5F0BBACAD0ULL, 
            0xA8872F87A23401D7ULL, 0x1986D7EA289299ACULL, 0x7A7549A57766766DULL, 0x8B3C309068377AFEULL, 
            0xB9DFBE357872516FULL, 0xC6B6FAD1920ACEFBULL, 0x647BC52213D87989ULL, 0xE23D9C0E58DF3B2BULL, 
            0x8B7476EE89B20F9AULL, 0x1C6200A9C96A368FULL, 0xE284AC6FF8E9873AULL, 0xBABAA712810D31B0ULL, 
            0xA6EB261376F931FDULL, 0xB8A800DF30CB9BACULL, 0x8D95C04C1B2AC127ULL, 0x2AD1A80CDB1DCB4CULL, 
            0x0B5FCBFDBFA52AD2ULL, 0xD26C295749CFEDFAULL, 0x91287E95B8350938ULL, 0x21E44426F988CE54ULL, 
            0xE82C5D0098335EA6ULL, 0xB0B4D14372131D48ULL, 0x4E52B2D95471CC06ULL, 0x7B18D26F63162281ULL, 
            0x279FFC2515B9D296ULL, 0x21FF6DB0EA010902ULL, 0x313C54D7577D7471ULL, 0x29DFB4D9E1666481ULL
        }
    },
    {
        {
            0xC35B8725D7B924B2ULL, 0x1844BE299BDAB97EULL, 0xBD91347FC53552EEULL, 0x621F74A9911134BFULL, 
            0x524F9630E3A67CB2ULL, 0x71AD152EA66B980FULL, 0x978526C437811A92ULL, 0xD157DF2E980A4C2CULL, 
            0x4B0A040F90ADA3FFULL, 0x4F83E616D999D55AULL, 0x5436AD482AC31642ULL, 0xCBBF393D5F58E4A7ULL, 
            0x0A6DC166BE65BD1BULL, 0x58E9C4D1759A5F18ULL, 0xFA8D9A91A6317177ULL, 0x6DBAB0E35EB86BCDULL, 
            0x145D6DA96B4FDC5BULL, 0x774C97C644051C9BULL, 0xC55FDBEEEEF02CCEULL, 0x67593CF699AEA820ULL, 
            0xF6E64F27253683B4ULL, 0xFB88C54A0AC6B828ULL, 0x0F6A70FDC319C27DULL, 0xAF4DE02759AAC4A0ULL, 
            0x1A9C9981C0ABB746ULL, 0x5499CB0E91977756ULL, 0x2015808F7C6D6016ULL, 0xAA69C121E3BC53B6ULL, 
            0x654927BB8AF4E59BULL, 0xBC31180617E65F92ULL, 0xB9C87850FBCF85A5ULL, 0x1F55F1DE9A142E4DULL
        },
        {
            0x86872657D063B8EDULL, 0x4C4C1874E26A9F30ULL, 0x05ACD5D81327D39EULL, 0x79DDDD329B3219F2ULL, 
            0x12B8F1B35A51580EULL, 0xDBC17A6E04504A09ULL, 0x840EDFE9A25FC3D1ULL, 0xAF4AB367B141C8ADULL, 
            0xD2F8FE57FD53D12BULL, 0xC370031E67988B02ULL, 0xAAE6E15FEA96D624ULL, 0x12C68C827FCC37BDULL, 
            0xA54DFB0D6C4E6605ULL, 0xEC3CBC4C55E1B8A4ULL, 0x2AE9F47303ED6F46ULL, 0xC2352C4EC03F0068ULL, 
            0xEE7FBB098500895AULL, 0xC8A78EF458348B19ULL, 0xBDAD48FC64D33A4BULL, 0x12C3355871373E71ULL, 
            0x51D9E11E256AB443ULL, 0x9E2BA66CB1DD0C7CULL, 0xE2ED9A014B3B3F29ULL, 0x0646EE6FDC9048C6ULL, 
            0x4691BF9F220DA2CCULL, 0x24AF1982F9ABEC3BULL, 0x39232BA515ACF46AULL, 0xF016A6EA5F201EA4ULL, 
            0x7A611397C9D47484ULL, 0x00A0BACCB2DA9BECULL, 0xC3A333F9F4B065FCULL, 0x1354F49E7FB71A54ULL
        },
        {
            0x91AF8A0DC8E4533AULL, 0xEFBD8A0E59367D06ULL, 0xB8F3DBCA9155EFD4ULL, 0x451EA33882488492ULL, 
            0xC65C5F9C82A214B3ULL, 0x2D30F0A3D9E437BFULL, 0x4084F790C2C574C9ULL, 0xC3DD4A6617BAC8CDULL, 
            0x0D5D0CDE53354C5DULL, 0x546E55D94216B8BDULL, 0xA5226D00C6729F68ULL, 0xC85F50C064C8AA76ULL, 
            0x07722FB16DC76819ULL, 0xF49F02BB7FE01516ULL, 0xB28E17D795DC5C9BULL, 0xA886B3C79FD5B668ULL, 
            0x5FFE537F67B99807ULL, 0x8A47413FBDFAB345ULL, 0x4A1C159DD36AF406ULL, 0x0BDAA4F26CDAE279ULL, 
            0xE49C69C1BA393BCCULL, 0xE002B996BE01E48EULL, 0xFE4BFBCBC4ABCB41ULL, 0x38870C6DB609EEC0ULL, 
            0x202776CFA3C0E8EEULL, 0x5A7A85CEA50FFDEDULL, 0xCD5D6EA27EF53E91ULL, 0x1429D5791C1560CAULL, 
            0x3A921A3BA8D4610CULL, 0x93D459AFC02FB88BULL, 0xE731BA34E321A832ULL, 0x0FF2D8885C29CB14ULL
        },
        {
            0xA3F2DAFE15A0E414ULL, 0x90B1ED252B20F514ULL, 0xF1CBA6CD56444456ULL, 0x2B08B3CAA0AF3DF5ULL, 
            0x8204303194B362A7ULL, 0x1018456074BF7AF7ULL, 0x47FD683E3E70F64BULL, 0x72066C95C1A906F5ULL, 
            0xA279B642269D1D43ULL, 0x4536F08397ADF16EULL, 0x4EFBCD2BAB5A262EULL, 0x6DC06F3D967CC40BULL, 
            0x57DF9B258665AC73ULL, 0x84DB7F260866E204ULL, 0x92EB42E37BEC9196ULL, 0x3672A7C57E730488ULL, 
            0x8C3912692E7AD97DULL, 0x5D740314DBC07A9BULL, 0xB207824E6B269C1BULL, 0xC9A2EEDED82967CFULL, 
            0x0282E9743CF628B9ULL, 0x663E8231A2A8CE8BULL, 0x210D334DE086002BULL, 0x2038C49C06165C35ULL, 
            0x1BED9D9F82FE7464ULL, 0xD755A14B82BE1C0FULL, 0x90A7A2E0D323D8B7ULL, 0x67FE0FB48D3F2E9EULL, 
            0xCEBEF0F1B7F701B6ULL, 0x52FFC2638E79D236ULL, 0x788DD1DF32C1671FULL, 0xECDBD673530ACDE9ULL
        },
        {
            0xA9C0DBCC947CC1A6ULL, 0xEE8686890F202A76ULL, 0x446BEC29BAD69EA3ULL, 0x4D2998DBAD889EC1ULL, 
            0x101B0EF3AED4B436ULL, 0xB172058AA0E8A4E8ULL, 0xB10068F0DED59066ULL, 0x216D984B6C8C13FDULL, 
            0xC771B5081A49E1AAULL, 0x7FB2E835865291E7ULL, 0x0F9B0D6EABB15CCBULL, 0x3585D7F78885A5ABULL, 
            0x67F12C403CFA07F6ULL, 0x9775AF8A2274B41CULL, 0xBB005FE0D6F02DCDULL, 0xCDA42B3D4C598E5FULL, 
            0x1EEFF8601F2BA1AEULL, 0xC720CAD6C504D6BDULL, 0xE67C5ACA5352FEEDULL, 0x8BACA7D4761EF2CDULL, 
            0x7056B016B9B18919ULL, 0x76BFBB657E43694FULL, 0x1748BE8BACA3CAC5ULL, 0x3E59A7518E5FD49BULL, 
            0x67419DC3D24AA2F5ULL, 0x0B2721BB9DFAAF6AULL, 0xCB811EAFF3035E43ULL, 0xAF658B1D1F898C7EULL, 
            0xCC057B083C587B3DULL, 0xB1F5EBCFA9F1E06FULL, 0x6E56C4EB65FA75B8ULL, 0x2C70ABA79A2001C7ULL
        },
        {
            0x5B62E37D6E02FA66ULL, 0x200ABEF1196E0D33ULL, 0xA5C6FB760FAA89F8ULL, 0x5A8A5049CA92BF63ULL, 
            0xD535A332F03AE791ULL, 0x7BC1A1FCE288E4D1ULL, 0x006E3EBF3B0A99D8ULL, 0x2501585724B0F782ULL, 
            0xEDD33DEA78B5B7F3ULL, 0xD7AF29A19263F8E4ULL, 0xACB6DD55E7FC43C3ULL, 0x1A688E6A1F3FF47DULL, 
            0x54FFE1EA55866325ULL, 0x285BDDF3C41C8E64ULL, 0x9EF757C65D81FDFFULL, 0x8423E632CE3C7B75ULL, 
            0x70CB85CA0580C332ULL, 0x9001BACCDBB61CC7ULL, 0xBF6E7B97B1FC321AULL, 0x2924C5179A59B19AULL, 
            0x2F48C8B3D8F5947EULL, 0x104A1E3BEDF448A1ULL, 0x687BFA116CB37B8FULL, 0xEE56A3C5A21B3E0BULL, 
            0x1A1861686FE27821ULL, 0xB8DC716DF036F15AULL, 0xD43FE74CAD5DBB4BULL, 0x0F78BE5B7C37CD3DULL, 
            0xEEAECF7E22ADB085ULL, 0xA7DAD7F416069CC0ULL, 0xD225E983E35B5DCBULL, 0x44D7E3DDCBCA2B35ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseAConstants = {
    0x049BAD1B4844E8A2ULL,
    0x80BCCB7122229680ULL,
    0xF34FA0217FF6D411ULL,
    0x049BAD1B4844E8A2ULL,
    0x80BCCB7122229680ULL,
    0xF34FA0217FF6D411ULL,
    0xB3BF2F053E1B3F57ULL,
    0xDAE741DE4060A9A2ULL,
    0x57,
    0xB9,
    0x60,
    0xA8,
    0x43,
    0xBB,
    0xC1,
    0xCD
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseBSalts = {
    {
        {
            0xD715172E4ACCEF5AULL, 0x16B8D9AF6FFF49A2ULL, 0x54A2053A4781D28CULL, 0x8B523E2FDC682D23ULL, 
            0x536B4D83C7E490ABULL, 0x9C9B8F5430CA9E92ULL, 0xCC22AAC686103643ULL, 0x999EEF1F34E1681EULL, 
            0xAAACAB73F8E6CC57ULL, 0xF499D5CEA0F2DAABULL, 0x04ED169B9FE34C4EULL, 0x7D3123997374A268ULL, 
            0x8499E93EE0B4263BULL, 0xD5867CEF7F5C8DDEULL, 0xC4CC12D59A787E91ULL, 0xC42967D74368AA53ULL, 
            0x7ABB1DC288B4CC01ULL, 0x4410D7C7A6BB5059ULL, 0xD95A5132FC4E83DFULL, 0x8C8BC7AC662F891CULL, 
            0xAF7DDE4219A4E7ADULL, 0x95FE32908EB40471ULL, 0x28F100D90EAAB24AULL, 0x91F2AE2B6E9382E8ULL, 
            0x2026931E4D94830EULL, 0x5394CEAFE5C29BB3ULL, 0xBD5808ECEEB6963DULL, 0x68B3CA25D50E2CD7ULL, 
            0x118686B5399C60F8ULL, 0x66183CE1FB6B8035ULL, 0xF2A1C45126F11BEDULL, 0xB2FA566876C1BC95ULL
        },
        {
            0xDCEBEA539F75623BULL, 0x5ACDF1292E2CB3DAULL, 0x06AC215A00EB8FA7ULL, 0xE125999074F76E10ULL, 
            0xEAB2223BFEEB0DE9ULL, 0xD67D26CE0A7E3496ULL, 0xDC9ED4F5363DDBB2ULL, 0xF7A79A914CCF91DAULL, 
            0x3CBA2C203ADACB22ULL, 0xB2370183B9AC16BAULL, 0x1C20B7113A3AFF39ULL, 0xB61BC91C5B2AD945ULL, 
            0xCCBCCDF3BBC3E4B3ULL, 0x5C77A84FA5A26292ULL, 0x183D72CB8CD399C9ULL, 0x332B274CBB240497ULL, 
            0x897A45844650EF02ULL, 0x935A681C7C5ECDBFULL, 0x61FDBA4DA2482D78ULL, 0xF18497C0C0F5D79DULL, 
            0x7B556A453649EB4FULL, 0x577DF60920540E60ULL, 0xC3FC55FED7F84248ULL, 0x4C7B540C1CFB79BEULL, 
            0x86F9C8131E0BAA50ULL, 0xD191C1DA284BD4CAULL, 0xE36D3B4A9DC82515ULL, 0x4650326E310AB010ULL, 
            0x5FAED69E95A03ADFULL, 0x35E836DA101E0E50ULL, 0xC404E863BB2521D0ULL, 0x496D5314AA0CAC50ULL
        },
        {
            0x6B5EE791B3711D80ULL, 0x8AB6AE39C9CCB2BBULL, 0x57CF6D6961E7EC1FULL, 0x4610318851AA0609ULL, 
            0x9217E39B2D47D71BULL, 0x659964D62F669C16ULL, 0x2A3029B20204B265ULL, 0xAB962F3D2AF4DDA7ULL, 
            0x0EA43674C5C1894AULL, 0x9F34386C02105C51ULL, 0xD973910865636F1EULL, 0xCA0A2A904D530032ULL, 
            0x57F45C81585DF000ULL, 0x7D62B9AC983862EEULL, 0xE7949A4148973C76ULL, 0x36200D000305EEC4ULL, 
            0xECD86C10DC80BEDAULL, 0x544897F10A675C7BULL, 0xC75020D341C28720ULL, 0x585FD7EC95E846A7ULL, 
            0xBB1827C0E1D975E2ULL, 0x50B19640BA23F124ULL, 0xC08D75EB5652E9D4ULL, 0x84C99D7B2851845CULL, 
            0xF699BD8105A53D6CULL, 0xE9C4CAD7568671F5ULL, 0x86781AB905EEB498ULL, 0x08F1613DF0A91526ULL, 
            0x96DD6F8300E9B417ULL, 0x41BEC6EDF5A705BBULL, 0xF9A876EA45254497ULL, 0xB73C0B03D2CE4FAFULL
        },
        {
            0xBD44FFC4D486EFBAULL, 0xCA1B9E22DE50ABBDULL, 0x71460C9EDCE14A7EULL, 0x2977B74D624D1CBBULL, 
            0xE77F4E05CD361900ULL, 0xC2E982875EC74597ULL, 0x22BA071DB44B49F7ULL, 0x9A1F79E6CC7072B8ULL, 
            0xF57C0A3E93C41831ULL, 0x13E8E6C2BCA05363ULL, 0x7E27A7D03EC277A5ULL, 0x0F57DB19DAC93367ULL, 
            0x58A07B155C6F029BULL, 0x3D990198FB2CDF82ULL, 0xF92169CE1EA4B12CULL, 0x41B818B7BA5ACCE5ULL, 
            0xC7811CB6DDDF4847ULL, 0x154F8A69F2094B51ULL, 0x5A3F702E871481C5ULL, 0x6E0972F85369FF4FULL, 
            0x057FAE67AA8A3359ULL, 0x90E3EB5C65E1B1DAULL, 0x756503535EB6BE2EULL, 0xFD3B16D76B234AA8ULL, 
            0x36C1C301A210C65FULL, 0xEB6BB2152D33FA63ULL, 0x8C582B35C4AACFEFULL, 0x6001698C5E8AF350ULL, 
            0x71E42EB74FF3A313ULL, 0xD3B011CC64BFA738ULL, 0xEA9A4D2CFD48F54DULL, 0xEE1B7C05F215685BULL
        },
        {
            0xED8643314FAD4D1BULL, 0x679EB6C7BB0095DBULL, 0x26613965C8D4CFC9ULL, 0x4B1637064CC0F104ULL, 
            0x273F242CC815261DULL, 0x80E44EF7526ED258ULL, 0x6F8505AEC770805DULL, 0xA54BECBBA1CEDA2AULL, 
            0x8D6BE420A0EC1561ULL, 0x7A0D9AEFFC3F2CDEULL, 0xF0215CB9E8E2D40EULL, 0xE7AABBC668E12111ULL, 
            0xD59E6C257512D8EEULL, 0x9880BB7588E29475ULL, 0xD4BAD266D896848EULL, 0x456DD02E8C5AC4D1ULL, 
            0x77D9CCE5BFF5B73EULL, 0xD30523B8FB239C71ULL, 0x33D6699A953F3B22ULL, 0x0864BF0A58A8779AULL, 
            0x86EA93096DD4DAE7ULL, 0x375C19A4E18D5B1BULL, 0x4615470711DA01CFULL, 0x5B4FE32669381ADDULL, 
            0xAFE37F1EE4898C65ULL, 0x623886BC026B8840ULL, 0xC9F57A5FEEEACCC6ULL, 0x4C73BE210B42C5A7ULL, 
            0x098CDC73F1B99FB5ULL, 0xC0FE572560A5CFDEULL, 0x953F93CF000ED82AULL, 0x89303B5A358A6099ULL
        },
        {
            0xA73DC640AD2AF81BULL, 0x032A0FD15307D10AULL, 0xB393305F52BB174EULL, 0xFBD31B81627E6005ULL, 
            0x502E08B6B9FCB9CDULL, 0xB8D0647F3E2D4872ULL, 0x541E1C1854977A2AULL, 0x11CE84D21BFCD312ULL, 
            0xC8F1B0A845F27CAFULL, 0x69B722F3E4C0F636ULL, 0xA91D71F62A724B96ULL, 0x3045070D1756327BULL, 
            0x713AD356C3887011ULL, 0xA9BC0D1E28AFE2A5ULL, 0xAF575CA2913A7FF2ULL, 0x1CB44ADE6D089DCDULL, 
            0x6B0C696EFFDBFC90ULL, 0x1022416150124DC8ULL, 0x6C4025E67654EFD6ULL, 0x42800AE0EE4693F9ULL, 
            0x7412FDF0048AAC5AULL, 0xB118AC8B730F7A44ULL, 0x3734430B4C48453FULL, 0x8FAE0CB7EEB240BDULL, 
            0xCFE159B2D3AB3202ULL, 0x8D7169A0C62480A1ULL, 0xA10DF40E50218125ULL, 0x0EAC324F324AC978ULL, 
            0x4602943F284D9FF9ULL, 0x88AA0BB5EEC927CDULL, 0x436012F54A9B8866ULL, 0x1E677B2923C51BD9ULL
        }
    },
    {
        {
            0x6B8BB7BAAE26E8A2ULL, 0xBB7C06A6A88291DBULL, 0x65B292D8AA9BD01AULL, 0x20F2DC00F2490255ULL, 
            0xFA3B696BC65322D3ULL, 0x69A6AC49E7956225ULL, 0xDE8C5FA2218460FCULL, 0xB3DDA68C07C48C85ULL, 
            0xCF70C7AB79C19F45ULL, 0xDEA3301333E085CAULL, 0xF114397838D45D3FULL, 0xB38558519098F34FULL, 
            0xCE0076A1BE3FE82AULL, 0xDBD5785816095F00ULL, 0xACA9F6BE27DF6DD0ULL, 0xC8A576624A205EA8ULL, 
            0x05A3012764F0E64DULL, 0xC131B7D7AB59575EULL, 0x1866CE6CAC18D7D1ULL, 0xDDFF8A6963BD4B95ULL, 
            0xB095A8F3D3936872ULL, 0xB3F1F47202FAECDCULL, 0x436A5EF8F8CED430ULL, 0x67A5AF898D562CC5ULL, 
            0xDBD334996A5825E3ULL, 0xD4F77CD42F3ACEE2ULL, 0x69DF5F5D7F65C58BULL, 0x71B9AF38469B7593ULL, 
            0x44052AA9227D1444ULL, 0xBEBDC9A9B8FF988BULL, 0x41F4CE08378243DEULL, 0xB8040D88CE5FE835ULL
        },
        {
            0x322A7852715336CDULL, 0x6D5902BA623ECADCULL, 0xF7825A0A4A02B9CAULL, 0xB0201F0C00014BB9ULL, 
            0xC9EAEE4753ED322AULL, 0x23875B4DD8F5CDE1ULL, 0xE267F4D0172A4F2AULL, 0x674DC2606B43F10CULL, 
            0x9A8C6D8EFF5760F4ULL, 0x899C9AD90101C00BULL, 0xBF88F96BF404F328ULL, 0xB84F56E4B347BE8DULL, 
            0x72AF6FAA5BFB39CEULL, 0xA360F2434A91E956ULL, 0xF570953E7FBC3CF8ULL, 0xC929989AF959818DULL, 
            0x19ADA8489F5EB735ULL, 0x6F458FF80C08D0DFULL, 0x21462D71FBB9DD3BULL, 0x1EEF658179EEA535ULL, 
            0xDFACE0B4E060101FULL, 0xBF6EE5E64B56F981ULL, 0x89C8D0BCC7317E11ULL, 0x1B81DC6806EEDB4DULL, 
            0x341C0678FFB52540ULL, 0x027BBB83774EB33AULL, 0x88322F89F63C11BEULL, 0x4727D3BC2BD96083ULL, 
            0x8D38D3023ED6774BULL, 0x1D4BEAF6C3BF87E2ULL, 0x0FD9D5C736F105D9ULL, 0xA2E8DF70A0036FF1ULL
        },
        {
            0xF47BB95C2C59A38EULL, 0xD05BB368965FC074ULL, 0x43C57BA97879B4D3ULL, 0xDE315BD6F7221DD2ULL, 
            0x4B4C5C7C2D5EE572ULL, 0x57AD10E83F39C407ULL, 0x86FB59E38CC34291ULL, 0xFF71E431F5F38D5FULL, 
            0x260ECB3C71F02638ULL, 0xB71A0A2839B66A55ULL, 0x08C4233ED480F7E3ULL, 0x2DA19999FBB2B8F8ULL, 
            0x8340828E04F00F43ULL, 0xF04FF00D716DCA28ULL, 0xDC77C25259B50FE9ULL, 0x9E4757447DBB4FBFULL, 
            0xAECD61330B790EFAULL, 0xD4587D80CF360ED0ULL, 0x9799F63F432D7914ULL, 0x4C1AABE40A60F54FULL, 
            0x39FC98EA50A50D72ULL, 0xC82A0BDA02109CB1ULL, 0xAD6E59BB80F67FDFULL, 0x68D36F592E396B14ULL, 
            0xFC706728D1106126ULL, 0xB3071AB5EC0DA364ULL, 0xCE3A77E1436AD496ULL, 0xB16C7EF5BF93F62BULL, 
            0xD234AA5026777E39ULL, 0x1690B9F429645728ULL, 0xD5FEE5946B0ED7FFULL, 0x39A748B02F9C044CULL
        },
        {
            0xFEBEDF6B603E54E9ULL, 0x786233CDCBE7B196ULL, 0xBB5E7EC9CE96F547ULL, 0x4D94A3A861704C50ULL, 
            0xCB73B107F3B00BE7ULL, 0x8095631B17AF9586ULL, 0x88F275358AB9DE9CULL, 0x8CADDC35F8225F96ULL, 
            0xB0B694435668DAE7ULL, 0xC1D5BF50122A466CULL, 0x207340F36CADA2FFULL, 0x2AA1B1532D8E5132ULL, 
            0xE15C79EA7C41AD65ULL, 0xBC64092B2D09E4E9ULL, 0x512146E699FAA4D4ULL, 0xF51D74FD43776417ULL, 
            0xAFC4CC11A6BD6FF0ULL, 0x1F89FB4EA1452D02ULL, 0x2E23EB31404297DBULL, 0x05939E65600FF68FULL, 
            0x4A0C48906C0A370DULL, 0x0C2B036C8EA3128DULL, 0x886FC6FEB19CD9FAULL, 0x39412427A64FC58FULL, 
            0x6BD5166C9837AD33ULL, 0x0236CB24762F30C5ULL, 0xD38170092AC91B4BULL, 0x8BB229E7A99D25BFULL, 
            0x9F1292A40D920EFCULL, 0x82AF647718FE31A3ULL, 0x12D2290648B5D418ULL, 0x004E88FBBF8F1C71ULL
        },
        {
            0x2532F616F90D7F71ULL, 0x9C7635104DD0E037ULL, 0x4D5356BBFABC87F4ULL, 0xC0C108400BA290EEULL, 
            0x9E6EC986C207900BULL, 0x15EEE2D9C915DA39ULL, 0xC0D456D40BA56395ULL, 0x7A6EB043B4909D78ULL, 
            0xD7FB388C0F04982DULL, 0x099AC8FA1336A491ULL, 0x1DD7664B8052FDF3ULL, 0xAA76BAA9AB177FBEULL, 
            0xFB5FC0771C22A5A0ULL, 0x003DA35312EBA0FFULL, 0x947F951EC71F9BB2ULL, 0x2DE302CFF51AA25DULL, 
            0x0F395880E48716CFULL, 0xE0297398F9E9AB28ULL, 0x7579A0125E266E67ULL, 0x5B3E6A84160677CFULL, 
            0x332E33E974063D58ULL, 0xE284D3CEAB1DD8E2ULL, 0xD70D90380A99FC90ULL, 0x1E983D0119732F80ULL, 
            0x08283D50078240AFULL, 0x5C88067D2E6802BBULL, 0x2362E2A62FFCBCD0ULL, 0xC301D7845FF5B3DBULL, 
            0x521691588206DCB5ULL, 0x369D71EA95D0EEBEULL, 0x6504846F3A2325C6ULL, 0x4457A27811F58D52ULL
        },
        {
            0x817450417709F564ULL, 0x5DC00138A5363458ULL, 0xA06F18EB25869EF7ULL, 0xE61A4AA8762559C2ULL, 
            0x4F30C8EBC0E626A0ULL, 0xC389A606EBB0454CULL, 0x58FFB3A678D4A127ULL, 0x8DFCA455904B0F06ULL, 
            0xAB11CCF0E68B3202ULL, 0xF43980B120A711C5ULL, 0x09AF45414BA50EE4ULL, 0xE4E0C5EF58DE706CULL, 
            0x878D18B5866FB6FFULL, 0xA33D380E82413340ULL, 0x5F2B3A1303D2DE45ULL, 0xDD0F8C52E775C041ULL, 
            0xC269145FA0F18190ULL, 0xE5E2857484337329ULL, 0x1114E92BD743FF46ULL, 0xE052492626A5FBE8ULL, 
            0x5B4CF2F212E42F2FULL, 0xFCAF9A08C225232BULL, 0x7E5D20117557FE26ULL, 0x440B9C234A1FCF62ULL, 
            0xDDDFE001E89DADD2ULL, 0x643CD306CED0273DULL, 0x6D35C5EEDE28B453ULL, 0x56EF89A408DDBDE7ULL, 
            0xEF34A8552D0405D9ULL, 0xC3ECF89877C475C5ULL, 0x04990F6EDAD16E5EULL, 0x0EB00E6F1FDA6ABEULL
        }
    },
    {
        {
            0xC88605D878E00592ULL, 0x3A956DD9E53F61C9ULL, 0x0C026B2FE2A2CA7EULL, 0x856C139630613050ULL, 
            0x5A971895D6CF2793ULL, 0xB1952637E3DCF466ULL, 0x4DF75C1A445F180FULL, 0xD1EB841D9997D008ULL, 
            0x20CBF25DF9D2C12FULL, 0x249FE6691D4D0F62ULL, 0xD1303834CD0590D0ULL, 0x412C13573922E10DULL, 
            0x2F3EDDE22DC5322AULL, 0x3F1B7298980C20B7ULL, 0xA68E81D2C39D8954ULL, 0xF4229A92FA8E0F53ULL, 
            0xAFFEC4781381ED75ULL, 0x2448F0522E7D2CFCULL, 0xA310D00F0E65B32CULL, 0x04063DF412715FBEULL, 
            0x03A6195D2D8D58E7ULL, 0x60FDE51ABC12F3E7ULL, 0xB8F2722CCC7034A3ULL, 0xEE16962DD3E2AA7CULL, 
            0xBF637E06A24DFF0FULL, 0x338DA68309059DBBULL, 0x94F7BB6CB4D8D6A4ULL, 0x70AE92F701EB28BCULL, 
            0x55AEC8600587F864ULL, 0xF24F799906311488ULL, 0xE94EAC9DE646DA1DULL, 0xA7EFE14841C8F844ULL
        },
        {
            0x95A77FCFA00BBC13ULL, 0x0699B66A33BC3D24ULL, 0x73F93CA5A9F325DCULL, 0x5755D6AD8C09F624ULL, 
            0x2802D06DB5942F00ULL, 0xE2E866798D262677ULL, 0x287641E70229582BULL, 0xD0BF297FCDBD4FC7ULL, 
            0xC5935D889CE45E2BULL, 0x5729D61891818B98ULL, 0xE333DE44D7D5F046ULL, 0x69BE22A5994D5251ULL, 
            0xCE1D59AC74F54FE9ULL, 0x8B7664832D98A9DCULL, 0x8CC924BD8597822FULL, 0xF9D46BDBE496259EULL, 
            0xD4B824D0770FF439ULL, 0x9B98EF0DBCBD3624ULL, 0x07CD2D3AAFFCE321ULL, 0x7E12B00496D03815ULL, 
            0xE25BE9D0779E1200ULL, 0x6472E0E3351983B5ULL, 0x4AE21B91CD611E08ULL, 0x04F72BD604DE84F9ULL, 
            0xAE653BCF67486131ULL, 0xC1C7EBA363189BE3ULL, 0xECE399F41798FF74ULL, 0x578175B7B884FF02ULL, 
            0x001B183803BBFADEULL, 0x3649E179514FBB67ULL, 0xEAAF3EAC864B5AE0ULL, 0x4E5F68106FB0B028ULL
        },
        {
            0xD2E0A579FAE5E2D1ULL, 0x5E751745CBC3ECA8ULL, 0x2138763FFB5EDFA1ULL, 0x743DE69D1C9A9DC6ULL, 
            0x6D2233E294F1D71AULL, 0xA59FD9A99F54B411ULL, 0x8E66D65A567E665CULL, 0x3D6157443F8FCF49ULL, 
            0x553C19E92BA0E455ULL, 0x197646947BEFF15FULL, 0xCC64F846DBCFA19AULL, 0x592461016B2CA145ULL, 
            0x23D5D130C41AD73CULL, 0x8378FB3B850FBDF6ULL, 0x32C78222DB40DA73ULL, 0x0FAAD48C1B9DAE3EULL, 
            0x74B9FBB36B40B6F1ULL, 0xA6C43F7A55E21C1CULL, 0xA7097B74D655E5BFULL, 0x2D58E1C57F99A6B1ULL, 
            0x618D01E295AE516FULL, 0x44CFBD361AF74E3CULL, 0xA8830B3EE51A5A0DULL, 0xD1B10D4F7B33FBAAULL, 
            0x7403D00B50E1E87FULL, 0x99757EAFC8E098DEULL, 0xAF131C3A98C1F26FULL, 0xE99C024B76E46B1EULL, 
            0x3A6C3CA665ACB561ULL, 0x447C0ABBBDE07E0EULL, 0xBE7868DB7E0E7617ULL, 0xA2183A3ED50FCAF6ULL
        },
        {
            0xE001A984C67EC65FULL, 0x34EC86A0CED6BA36ULL, 0xDABE91DDF1C5F8C1ULL, 0x3143D04FF97AFA96ULL, 
            0x9E11185FAEDD01A1ULL, 0x007B4372559578A5ULL, 0x6AF152520EC93B3DULL, 0xCBA28564016603B4ULL, 
            0x96F4A75099A0449BULL, 0x96A7D3EB0FB99DC6ULL, 0x726F5350FAE32EB4ULL, 0x8BF406AEFFF5B778ULL, 
            0x943D2512C7EAF3A3ULL, 0x2418FB640212E4E4ULL, 0x4E611F7371CA156EULL, 0x1FCC2F1B4BBEEE3EULL, 
            0xC8B5A94511424C81ULL, 0xF4BAB797504E2BD2ULL, 0xC1537DDC804DAF9AULL, 0xA3D08A7DB1CD9B6CULL, 
            0x393FE8BF3D69E11FULL, 0xC8B9EF9B5E601D9CULL, 0xF625FDE38BC983FBULL, 0x70278A7E5FA4D630ULL, 
            0xAC4C2321D58D8B9AULL, 0x1C211F208ACC3602ULL, 0xC24480835E8E5F6EULL, 0xF7120355D0AC53BEULL, 
            0xD16CE033A06AB893ULL, 0xF8B7ED1D000CD90CULL, 0x1D38C4F774449D7AULL, 0x29A427AEF458BB18ULL
        },
        {
            0xB2B7377E61584DCAULL, 0xB70955F443628B32ULL, 0x8017F9439BB5F6AEULL, 0xE7FE45A768E93B49ULL, 
            0xDECA3DC064093A88ULL, 0xD184358E8A4073F6ULL, 0x9FDF5F60CB5140A4ULL, 0x24521EF0F57B1C45ULL, 
            0x84EEB961E668C2F4ULL, 0x6A902E48A473F034ULL, 0x2DCFF06CBC2D30D1ULL, 0x338BC2E73D3D77B6ULL, 
            0xF2AFC25A300BC3B8ULL, 0xE2C93D69742B90E2ULL, 0xC2B12B88429A74B2ULL, 0x13808873E9927B4DULL, 
            0xBDD200D7AD5DABB7ULL, 0xD76D4EB1DF970984ULL, 0xE36FA56EE88939A7ULL, 0xABB372B53CE46A19ULL, 
            0xFF142CF1D2AAD124ULL, 0xE0755E2654ED120DULL, 0x53AAEF7315B1DBA4ULL, 0x3FF4FD09978165E5ULL, 
            0x93EAB71FB755C8A1ULL, 0x6C13E8624319DB44ULL, 0x7797AD837BC3D9CFULL, 0xB5C62B93D554C6BFULL, 
            0x292CE23D15D6625EULL, 0x476D7BC6B4733E10ULL, 0x8429014D5A8DBB8AULL, 0xD236F11C5C177AFBULL
        },
        {
            0x9F6F7ACA6498B1BEULL, 0x9328A7C419F2C82FULL, 0x9488D15C507B2092ULL, 0x43E83B13F8EC7655ULL, 
            0xC80AEB9DADDC3181ULL, 0xC70D2A6CFCE3BBD0ULL, 0xAF08032D1056B1FDULL, 0xA9E25A733DE993CBULL, 
            0x6C63553E690EA0EDULL, 0xA58F6F85257E63F3ULL, 0x6E2632E18ECE46E1ULL, 0x0A29C057A08AB9BDULL, 
            0xA0469536120E2EBCULL, 0x5B34A67B54F7BC06ULL, 0x046F1B4BB5138E93ULL, 0x3B433F3FE0FD066FULL, 
            0x265278605EA0C0E4ULL, 0xE16F4A8F2FE032FDULL, 0x5F438C6143E4E6A5ULL, 0xFA23D180D6C1B769ULL, 
            0xC4E53EDBB1496CD3ULL, 0xED53F50198948586ULL, 0x7C548ACAA9432678ULL, 0x3A2ADA680DEB7E32ULL, 
            0x5816B7D99E34571CULL, 0x8537797F10048AEAULL, 0x37F84D069C9F9D57ULL, 0x6B532190278EB08FULL, 
            0x03B7E6197E082CD9ULL, 0xC797D88D31A27EA3ULL, 0x51F891B654CCA2D4ULL, 0xFC1C2424519A9BC0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseBConstants = {
    0x7C1F3F8ACEF41245ULL,
    0xC42C54BE0F2ED0C0ULL,
    0xE22B1DE8E6F12224ULL,
    0x7C1F3F8ACEF41245ULL,
    0xC42C54BE0F2ED0C0ULL,
    0xE22B1DE8E6F12224ULL,
    0x3B346081081FBFE2ULL,
    0x257CD826CEB65B61ULL,
    0x39,
    0xE7,
    0x0C,
    0x8E,
    0x80,
    0x85,
    0x4A,
    0x96
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseCSalts = {
    {
        {
            0xD4943875FFDA3EBFULL, 0x798F27595F642EACULL, 0xC59BA6E5F02C5316ULL, 0x807D9EEA9807C9C1ULL, 
            0x2E0C15F0FEA79F6AULL, 0x4FDD54093256AFD4ULL, 0xC65F490D1B4EFE79ULL, 0x8C3481847C95C1A2ULL, 
            0x6AF407FCE28BAECCULL, 0x6E03889DC6D1C5E1ULL, 0x8E4D6718B1EE6890ULL, 0x22D685A9B9FC5E37ULL, 
            0x1965AED7EC25B489ULL, 0x951A6E0D75F3CFD7ULL, 0xAA3CF61FF44B6440ULL, 0x335B08D754FA4BFBULL, 
            0xCA976D8653C89CDBULL, 0x6741917F12B94771ULL, 0x1E39C36AE1ED1D9EULL, 0xC2A61823A6997E01ULL, 
            0x2A409E7577A2F830ULL, 0x429A6DBFE2283F1BULL, 0x65A55FFCA42C89FAULL, 0xD7159B1C8E18C830ULL, 
            0x0F55F2459E01FD18ULL, 0x2137A53C98EDCE9BULL, 0x8C155A56E0B953DCULL, 0x1B829B934E5B81EEULL, 
            0x7D4EFA781FF69A4DULL, 0xD45C8E7D4F575C1AULL, 0x9643D8BFEE8BF77AULL, 0x618103C0211D5949ULL
        },
        {
            0x0CE0F0139A7E3AB9ULL, 0x574701598C00756CULL, 0xDC3FA73D6343AEC5ULL, 0x72F90477B2159B8DULL, 
            0x8A4A126F4A041D1DULL, 0x1A1CDBC195FFF815ULL, 0x78E612034C279C3FULL, 0xFF1973DD98C1AB01ULL, 
            0x3849D72D526E2D67ULL, 0x9AB8849F3118AF14ULL, 0xB30895BA55DD9551ULL, 0x4E46AFF1DFD47FCCULL, 
            0x158B1F08D65DAEB1ULL, 0xC3D4C6E039589A0DULL, 0xA9151E6CDAAB465EULL, 0x35E526F6D657477DULL, 
            0x37B1CF3DE2114CA6ULL, 0x29E2E7C898DE0B8DULL, 0xC256E1F11622E78EULL, 0xC1E40CA2EABFD748ULL, 
            0xC0F85CCB0AB6D00FULL, 0x2969682D52B1D4E5ULL, 0xA541598CE4BAD4ADULL, 0x8A4709438C5C0341ULL, 
            0xBDF46A38C5D58C3FULL, 0x45EBAE09D8E34536ULL, 0x49CF1AC109D3CFC6ULL, 0xCE0022ACD78E89AEULL, 
            0x92C9C69CC7FA84F5ULL, 0xF4FC2C5B59B24F5BULL, 0x5AE12736A92CD2FAULL, 0x822D0D60C314DF5EULL
        },
        {
            0xC59D6607DAB656EAULL, 0x19D1760BBEFF9FF6ULL, 0x78B7003D5E498672ULL, 0x6981180FCF614077ULL, 
            0x0A2AB13BDD340DD7ULL, 0x58890D4F20978BC7ULL, 0x2859DE5339BD7C18ULL, 0xB2D07E1A054CB27BULL, 
            0x0C9CBEBC8901F194ULL, 0x569416EFF602D9F4ULL, 0x08F502F047E5600EULL, 0x7DD1A7A4255DDF11ULL, 
            0x4131D3E2BDF0C731ULL, 0x7900308B3BD25740ULL, 0x25884E3560A645ABULL, 0xC1E5625B5F9C133CULL, 
            0xCE005ABDE5E7B16EULL, 0xC4D9BDC232E64A03ULL, 0x56B85462C9212248ULL, 0x4413DE961565C02EULL, 
            0x7194882FEC8A29D5ULL, 0xCD9DEA37D6F8B0BFULL, 0x3E48E6F2114DEFF8ULL, 0x4F3A39B926D6DEF5ULL, 
            0xF286FFEBF52409CCULL, 0x8B5670948D4A5388ULL, 0xB13E267CE329ABB5ULL, 0xF7AB4DB35491F7D1ULL, 
            0xDA20F4AC96B468CEULL, 0xA205B56A9F7DF134ULL, 0x1C489F1868632DEBULL, 0x7FBEA39AD8F69AA4ULL
        },
        {
            0x0F2A840BCA5891EDULL, 0x0608B95E755489E2ULL, 0x5CD8E3450483C2B7ULL, 0x1626D02872BBD3C6ULL, 
            0x75D889B9C79B4712ULL, 0xA41E95A2E1ECE12BULL, 0xAB085F89CBC40DFAULL, 0xA8E34B9AAEBE0134ULL, 
            0x514F36058D5F03D9ULL, 0x6FCAD37CD3DBFA72ULL, 0x817F6C3E0ED8DA2CULL, 0xF39C75140E2A3DF0ULL, 
            0xDA8A55CCEC769979ULL, 0xEE50997A8015B7A2ULL, 0x8F4104B20D4785CFULL, 0x6BF63DA110BC6B5BULL, 
            0x9EF8950FA661B515ULL, 0x455B7301D71660B8ULL, 0x8533E567D5EF5719ULL, 0x5017B986E997507CULL, 
            0x4D1C6CBFE5AA4E0CULL, 0x789583CA7DAAAF93ULL, 0x058B41C7BC7290CDULL, 0xD54AE3752F4837E9ULL, 
            0x2E1E622798311846ULL, 0xC4AF775D814CC882ULL, 0x799C8AC1B40DD52AULL, 0x52E23F6C72D9FA5AULL, 
            0xF15BF49623F09518ULL, 0xF47AC42A0DEDBEB8ULL, 0xC4F94D6D351C899DULL, 0x6D9CA600BC6DCB2BULL
        },
        {
            0xFC034F418DB6E975ULL, 0x7891C9D9CB4690F0ULL, 0x6DA1C285183773AEULL, 0x0FBDF4478E61593DULL, 
            0xBEA9FFAAD5065535ULL, 0x660690378EA2EF3CULL, 0x7B196DA2DC929788ULL, 0x3F533FA1540646A5ULL, 
            0xAB5112FED8E2EF9CULL, 0x2AE08543C7263BBBULL, 0x151DB377D44DE9F0ULL, 0x6AC02AB41430F673ULL, 
            0x00DE848C3CED2FB6ULL, 0xBDCC831F8A1E3C0DULL, 0x50C87B789FA75FBBULL, 0xC27D4EBFCB5E6AFFULL, 
            0x99C8CA746A329A52ULL, 0x3B1B296A0CB907F8ULL, 0x8086CBCD9B0D5CC6ULL, 0xBF5463A779C192C9ULL, 
            0xFC728D038CC3DEEDULL, 0xF0210B96D36E04FFULL, 0xDF8FE43E9FD65734ULL, 0x8A5440A1768EC88CULL, 
            0xD20D28B330B094BDULL, 0x15B5721C95710602ULL, 0x5C4F1E241A26A3D6ULL, 0x12421DA4CE770C96ULL, 
            0x12566DC9058235B9ULL, 0x1DBFCB4BAE26447CULL, 0x7B240448142421C9ULL, 0x0EB988D4E9848B07ULL
        },
        {
            0x4CBDFA4FC1A6E86FULL, 0x6AECA5C8FD28B0E7ULL, 0x35E2AC2D8B4A1A39ULL, 0x5A8557F757C5919EULL, 
            0x91A39F734F98CD07ULL, 0x784DD47D147A29FEULL, 0x98955F30A90A1BEEULL, 0x3C00B3394499D3EBULL, 
            0xB95E3B963562E212ULL, 0xDBA777D2F774C627ULL, 0x367128071664D3B5ULL, 0x2C02B31B7CFD1C5EULL, 
            0x8154F02056B388FCULL, 0xC87C66CAE6B1787DULL, 0x08F643C6516C017CULL, 0x7183D4C1DF53D6AEULL, 
            0xACCDCD1B867F63D8ULL, 0x2FB92E6A0B343EBFULL, 0x14C29242E51BC6DEULL, 0xC957BB2FA3D2FFEAULL, 
            0x56D10547D103ED95ULL, 0x1302A5C6B0495972ULL, 0x81BCCF4B89AF6600ULL, 0x31CB13C6C7C11C11ULL, 
            0xA1337ED428A40687ULL, 0x8964D05740DA378FULL, 0x02727707C8B6413DULL, 0x270379C7F6C08137ULL, 
            0x4A5502EB78AD17C3ULL, 0xD7CC5EB5BD7167C2ULL, 0xF56D7119276B932BULL, 0x1A8733FA33FCB339ULL
        }
    },
    {
        {
            0x5FB14ABDCD4CD1B8ULL, 0x499E8C57F7152675ULL, 0x6B1997C04A6D5C55ULL, 0xDEA5C2DF66719FCAULL, 
            0xB1143918404E603DULL, 0x6DB7805D4569C7F6ULL, 0xCD1549E77CB8D476ULL, 0xF587FE9CA91DD863ULL, 
            0x9DC468B162997AA2ULL, 0xD8010901F75E37AAULL, 0xF1CDD5306282717CULL, 0x8CD12559B8D19F41ULL, 
            0x0115BB1C307D44B0ULL, 0x99D77135826E28A8ULL, 0xDFD37FC32B648757ULL, 0x441FDDB1FAD9E562ULL, 
            0xAABA9FB6C056AF03ULL, 0x65CCF0DF9B888B3AULL, 0xCA5216ACEA7C6309ULL, 0x4C92A1FDB3FC6D08ULL, 
            0xA4F75C6ACE6A51E2ULL, 0x28F922EE3761AB82ULL, 0x2AD45541E824CF2DULL, 0x9D9FEFBBE94FF8F4ULL, 
            0x44B730F4EC1E9655ULL, 0xFA5E52E9DA9C24DDULL, 0x162FEF8C55B6EAD8ULL, 0x73E566E0E8F24122ULL, 
            0x876F90FDAC9D1D33ULL, 0x90CF0C1EF2BE1A84ULL, 0x8962DEC1154CD258ULL, 0xD94E2D9078192BAFULL
        },
        {
            0xBA7D8F46EF57DC69ULL, 0xE202B7A9C8EAFD22ULL, 0xF3F64541EC871F63ULL, 0x01FEE5E6DCD0036CULL, 
            0xCD07CD907AF8CB5DULL, 0x8D92EBD4A9E3946BULL, 0x4F98E84976CFDDA7ULL, 0x16838D5830375E76ULL, 
            0x68283EF4916E3DF5ULL, 0xE6ABB4A90A07CBECULL, 0xB4CF576EB6E9B675ULL, 0x49B066A746FA0B75ULL, 
            0x1591B6FBE4F07D33ULL, 0xE32091026D58A0CDULL, 0x79F3A3D493FA924FULL, 0x02589B151C0AA784ULL, 
            0xC4EFDD0770384DE4ULL, 0xDA6E848ED8F096D1ULL, 0x074089C3CAC83D32ULL, 0xA840138D69EDD03CULL, 
            0x2B2724909FA3E50AULL, 0x308B4914E86375EAULL, 0x72BB69F92BDD8921ULL, 0xBE47EE709E9101A2ULL, 
            0x9F00C160EFF25CF0ULL, 0xED2056FDE76F4531ULL, 0x0F5088D3161FD7C2ULL, 0xEEB5B0AE8A001996ULL, 
            0x0528A1D4A274DFF3ULL, 0xB15A50CA473CEB63ULL, 0x5094AC2E7D72A137ULL, 0x2CA6405E01E82B6DULL
        },
        {
            0x8C1063F79546B4CEULL, 0xB524260DDF272CCAULL, 0x59A04781F8961A73ULL, 0x3F6757F77EEB25D7ULL, 
            0x077C4ABFB8BC462FULL, 0x8D0AE17B0B34CB78ULL, 0x85B0F09770BBB2FDULL, 0xA6C0E63647B1FC7CULL, 
            0x9F3EABD172979D33ULL, 0x2157B6B8B982A133ULL, 0x71AD19E6E7C3A118ULL, 0x68F0518C68EFF0C7ULL, 
            0x1B248B79507BFBE3ULL, 0xB2C0BC85501B4A61ULL, 0xCC4591F12564C784ULL, 0x6E912B13E93A3E30ULL, 
            0x8787DEC11BD7CF65ULL, 0x84A42D78EAD758C9ULL, 0xA0ADDA892CB88835ULL, 0x8B6D3A5F08795447ULL, 
            0xB3E936A8397B4427ULL, 0x8E23D3C756835E1DULL, 0xE846F52CEA0BBDD2ULL, 0x67958FD710CB1B21ULL, 
            0xB0EBF2E61B463A0DULL, 0xA75B7E3DBE8D8451ULL, 0xFF8FAE9922846AB1ULL, 0x293758B914FEF18DULL, 
            0x9A3722CB569232ECULL, 0x3EE4D6D6BC3593EEULL, 0x49BE2B53F312FEA6ULL, 0x8AE77C08C8F0CEBDULL
        },
        {
            0xF981CE850619CAE9ULL, 0xC849DDC6715804BAULL, 0x70149A1A03CA1E10ULL, 0xFDDA7EA7B676E9E9ULL, 
            0x3C1E5DAD1B4D53F6ULL, 0xDA412FBE78E939FCULL, 0x82E828B5A8C348FFULL, 0x578AE7F0D532458EULL, 
            0xD426F7DA4374F3AAULL, 0xF02AFA058CC2A22FULL, 0x6E1DFFC23440FB63ULL, 0xFD51A94EA8282D4DULL, 
            0x4497CDBF27E64CD9ULL, 0x91AC4FDDE07ED527ULL, 0x74E62A6A65FE9C6DULL, 0x06E720DD1274EA32ULL, 
            0x4F832DA171091FFDULL, 0xA6E87FF1B44AF058ULL, 0x6975AFC03F3600A9ULL, 0x4F5BAC13EADBE3C5ULL, 
            0x60529410CA97F2E9ULL, 0x80476BB4B847B936ULL, 0xF70CAB4A96270951ULL, 0x5C3A9447EEF1BA18ULL, 
            0x85F1A6D1714F8EA8ULL, 0x1866AE3868D86E16ULL, 0xF3BE09D72CEE9A3AULL, 0xF039B3389CB6A919ULL, 
            0xF1D20872AB3AB4B0ULL, 0x3DE82CC8A1D877B7ULL, 0x94A1FD065F92B7DFULL, 0x76EB39340B857178ULL
        },
        {
            0x6E0335C7D05D82CCULL, 0x755A365C96F1B672ULL, 0xD169FB8F35879509ULL, 0x28FFF63505CF2F2EULL, 
            0x594E3319A0D2023DULL, 0x4CC1C7F55BE1EC38ULL, 0x95921FB18B451104ULL, 0xDAF4BD17CD8C7344ULL, 
            0x549D441EB263BE04ULL, 0x2E77EA07F7C58118ULL, 0xB479054E38952CA2ULL, 0xD68978FBC4F6454EULL, 
            0x328C7E61681E030BULL, 0x6200462AAE25924CULL, 0x81721443C5D2C583ULL, 0xBC6F52CBB224F230ULL, 
            0xFECC3AEBE8195824ULL, 0xB428861F0DA5CB42ULL, 0x9158C73A7EE72630ULL, 0xD54C8E03C8EF5F72ULL, 
            0x683297A94EB98E43ULL, 0x212CA331E23482BAULL, 0x4D6D359CBCEBB04AULL, 0x2DBF75FC249FA60DULL, 
            0x6468252162ED8248ULL, 0x1ACD069F393003F8ULL, 0xF541703AD75478B7ULL, 0xDAC4236732A9DD44ULL, 
            0xCCBDB0D7C9737FDBULL, 0x8A8D97435C0A6AC0ULL, 0x035D0DC08956FD7CULL, 0xDC120FEB8C7DA05EULL
        },
        {
            0x4E85D1006CEE58EEULL, 0x8F3D03A682F5A5FEULL, 0x125CA28A6D55999BULL, 0x206CC22527285DDCULL, 
            0x47A0179FFAF30F55ULL, 0xCCB3E23292330C2BULL, 0xBA118977B74980FAULL, 0xBED344A3A97E6FB5ULL, 
            0x61A3083218EAD1EDULL, 0x674E16388C980DD1ULL, 0xC599FB34B7E7100CULL, 0x08A31EFB44DE0292ULL, 
            0x250C8CAE1CAC0F9AULL, 0x1840104E6549035DULL, 0x31F27D2977DB1B82ULL, 0xC82133852FF35319ULL, 
            0x4D685661052EE7FBULL, 0x1E22DDBDE9745C7EULL, 0x802D915D2B3DC8A2ULL, 0x6E2CB76DD6FB19C4ULL, 
            0xE2E83C2F9175C427ULL, 0x46A5BAA401054A37ULL, 0x4D1DD18799DC529EULL, 0xB81DA7E42F0B3684ULL, 
            0xF955935867311C76ULL, 0xF5C1B5F2B8A6FD30ULL, 0x13FFE7DFD74AAFC4ULL, 0x259DF1F199947F06ULL, 
            0xB6031E0812657AF8ULL, 0x718E82DEAD2CF377ULL, 0xC48E778D6412F046ULL, 0x7CFA8A7DF6D56425ULL
        }
    },
    {
        {
            0x597ABF9219342DF7ULL, 0x0BB0C479656C53BEULL, 0x998BA6496B714FF7ULL, 0x03EB48648C15386CULL, 
            0x2BCBCEFAEF5D212AULL, 0xA01EDBE22849CDDDULL, 0xF0DB8E7AF8503C07ULL, 0xB093AA9BD341D6DDULL, 
            0x71979DCB3A0461DDULL, 0xDD9316BADA0ACFE7ULL, 0x1181AE5B6ABF28A8ULL, 0x8D89C0F6CDA02A45ULL, 
            0x866D1EC12741CF9EULL, 0x76E8E339C3C2771FULL, 0x40CF301A1ED2E9F7ULL, 0x5EEB92458C30CC60ULL, 
            0x8175052B19BCE1D4ULL, 0xB398E11AC51C27AEULL, 0xE8E07761F4ED1796ULL, 0x37D85A4273C61A0FULL, 
            0x3A6A1E245385A969ULL, 0xB5579AE7B63FFAA4ULL, 0xDFEB07976B2E6567ULL, 0x1D75CD12F19E2E16ULL, 
            0xC45587F92A02699DULL, 0x49CA23642E9BB0F0ULL, 0x24240E5D06D8C22EULL, 0xA111EF6EC9466FE1ULL, 
            0x719D2EB02D2F00EFULL, 0xCD3AEFE6B5F2009EULL, 0x74116901B5FAEC3AULL, 0xCB0B2D79964C29EEULL
        },
        {
            0x478396237E0F2EA6ULL, 0xA90852CC394790C0ULL, 0xE9F9059FD1AB045EULL, 0x2287C782D39EAF03ULL, 
            0xA20E0A8181E59407ULL, 0x604CAD07161E2675ULL, 0xEDDBD348C135FC1BULL, 0xEACE281AB34BCC9BULL, 
            0xD70D21A28ECE783EULL, 0x7AD8958D3620D605ULL, 0x6BE00092EA656CF5ULL, 0xE80E10DB1AB702E4ULL, 
            0x3C5E09872BABB3CEULL, 0xDBC40EFE083ED0E4ULL, 0x2C60FF4CD1E80630ULL, 0xF5AD7387F739FE94ULL, 
            0x30DF0E133095DF75ULL, 0x1C10174101DD6830ULL, 0x2CFF9571E74FDC64ULL, 0x51F6CE9AFC8788DAULL, 
            0xFF18F2AB862F1749ULL, 0x3AF37B42EBBC38B0ULL, 0x73DB3C73D026209FULL, 0xC5E6919DA9952A48ULL, 
            0x021E41E6FC88DF18ULL, 0xA918AECA09EE9B47ULL, 0xE20BE6B2312D1B01ULL, 0x72FC0613A637DBC3ULL, 
            0x1ED7C4870B2FF9A9ULL, 0xEED65C72BE719BAFULL, 0x18F008EC27A35680ULL, 0x9B0DF29AB69376C1ULL
        },
        {
            0xCC5327A885E7CE2FULL, 0x6E7C61AB944CEF68ULL, 0xC7AF07A056F3179DULL, 0xFDF64665C0E145FCULL, 
            0x1168CFCA54E95C58ULL, 0x7D0B223D3F839284ULL, 0xAA37E15207F3FE49ULL, 0x992C692354541945ULL, 
            0x67776644D220718AULL, 0xEE2BB5D8C050DBA5ULL, 0x97F5359686647335ULL, 0xCD4A91DE62388AFCULL, 
            0x1A73C9C53E6D3BC6ULL, 0x3B4D844A1586EBDCULL, 0x642FBFB27CED048AULL, 0x476B9B5822FF1DE3ULL, 
            0x4D1F74A5A71B611FULL, 0xD2E5867E6F1E0A97ULL, 0x460B8C60669898E3ULL, 0x37155D492576DF70ULL, 
            0x0225E0CFF0E642BEULL, 0x7D47824116233C47ULL, 0xD3E2AEE85D93AFF7ULL, 0x1DC28B4F8989E0EDULL, 
            0x8B482A569BDE5A47ULL, 0x80F48BD3EE358FE6ULL, 0x1F8A737D5B963B25ULL, 0x9747CD103E33D05DULL, 
            0x22328B404CD52BC8ULL, 0x424B1C808067AA4FULL, 0x72C09AFC56F991B1ULL, 0xD54A8F24E3499803ULL
        },
        {
            0xB918CC5DE7E5CF49ULL, 0xD00AF9085C238162ULL, 0xC475A5D7B60AF814ULL, 0x2E0561F6E5AC87A4ULL, 
            0xF4C9F668005C3634ULL, 0xED66EE0F401F2EE1ULL, 0x1896B22196344C2DULL, 0xB24CAC01B8AB82CCULL, 
            0x0D282CD410288CCAULL, 0x129500051E5E1A2FULL, 0x929973A64FBBBFB7ULL, 0x15DBC7D8CCF7406BULL, 
            0x8EBB2809FFDD7E38ULL, 0x1384A2286E414D57ULL, 0xAB05E459EF090B47ULL, 0xDDEA133E551ABA44ULL, 
            0xB41FFCF7D1554BC2ULL, 0x2BE1F52C0B4C1AE3ULL, 0x64A900317355DA12ULL, 0x5827DCF8DCE09F01ULL, 
            0xD99B2E362DB2C3BFULL, 0x1DA2EEE076C029FAULL, 0x134AF95ECB1C9412ULL, 0x99B5E63D58A4348AULL, 
            0xB79143B231505742ULL, 0x29D67275470D00CBULL, 0x208DAA26CCF6C7B7ULL, 0xA95C38090CF641CEULL, 
            0x2B11A56336D5D12DULL, 0x6F663306AB49E072ULL, 0x1ECA7BE95F8DB5F4ULL, 0xB965BAD91BEBB6D7ULL
        },
        {
            0x58A42F7706822C68ULL, 0x9F559220AA9C6A73ULL, 0xDD483FAD479C0369ULL, 0x90D7F0B8772A8140ULL, 
            0x4A0D3B1CE8DF1EC3ULL, 0x45C6CA5AA51C0EC5ULL, 0xF81F61260793FA9BULL, 0x991F0D473B554A61ULL, 
            0xE9E9E23DF96A5AADULL, 0x20C8D6CE6ED9526BULL, 0x4787E7D793921755ULL, 0xE6390835AE865DF4ULL, 
            0x0C295BAE9285604DULL, 0x6F154938A5E1AA6CULL, 0xDCD9C75300E3EC6FULL, 0x10D102216B98189FULL, 
            0xC7F008DBB438E0A7ULL, 0xBFBCCE753CB3093AULL, 0x64824ABFED1EBEBAULL, 0xF615321A3C7ADCA3ULL, 
            0x4C1A9DFE453FEAA9ULL, 0x3BD7C896BC5853BFULL, 0xFAB74623661B4001ULL, 0x4142E81C52EC96BBULL, 
            0x17CB9E296BC19D74ULL, 0xFC52441C3A3970C8ULL, 0xAE6E65817939F1ECULL, 0xEF86B4B4DAD6F46DULL, 
            0x9633EE6104FCED94ULL, 0xC50A9F332604192EULL, 0x21C17416FE7E7A30ULL, 0x0F36318FB553ED34ULL
        },
        {
            0x41E8FFC8E6259C2AULL, 0x7A8381224F662A0EULL, 0xA290D3787AF949F6ULL, 0x7CE67178B76733C4ULL, 
            0x1F44644621802F7FULL, 0x66CE9B84B6C9548CULL, 0x8C7FDA07298435A6ULL, 0xE41B8C479482F843ULL, 
            0x43F3F26250EABE83ULL, 0xAA82C0912D493C1CULL, 0xC7B979A45FFDA592ULL, 0x5E4424E657814FC9ULL, 
            0x148323D9E328EA1DULL, 0xE26744186ABE89A8ULL, 0x734DE8C2250ECEE9ULL, 0xB0E3F946B167984EULL, 
            0x5BE1F441A3AE34B8ULL, 0xE162C3E5346C1DF2ULL, 0x6A96C3FBCDEDEC97ULL, 0xD44A23145E27ECFFULL, 
            0x6599961C4F14FFD2ULL, 0x905BFE635F1A917DULL, 0x621228AE4B51E70EULL, 0x20EF0BF7B0617DF0ULL, 
            0x50B669B7B3400C8FULL, 0xEE234DA6D079AAD5ULL, 0xD934428A3EAD4046ULL, 0xDE82708F4C291BD8ULL, 
            0xFB9C433AE272B50EULL, 0x6FE408F617996434ULL, 0x656B8889C9890A2CULL, 0x136F2C35E8D18B4CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseCConstants = {
    0x0F9FBF35633816C0ULL,
    0xBA186CAC69BA2A65ULL,
    0x43BECCCFC1BD267AULL,
    0x0F9FBF35633816C0ULL,
    0xBA186CAC69BA2A65ULL,
    0x43BECCCFC1BD267AULL,
    0x78FC9AC4FCDC81CEULL,
    0x96BEC5A5BEFA9173ULL,
    0x24,
    0x3A,
    0x0D,
    0x3E,
    0x8C,
    0x80,
    0xBD,
    0x94
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseDSalts = {
    {
        {
            0x8D80E809B7BE5C63ULL, 0x68CCA3A0BB579CAEULL, 0xBB1FE6AFB68A2969ULL, 0x8E532385045AD5DDULL, 
            0x8239D348E0D786B5ULL, 0x6FE1A69091F1754BULL, 0x411B9C045D00C53BULL, 0x270EE68C74E5FD28ULL, 
            0x2DDA9924ACED5205ULL, 0xA17ED153085C5BA6ULL, 0x58DF45B65178C842ULL, 0xF27350EC8904DE3AULL, 
            0xCB6345354550B1C4ULL, 0xD4C48EE28AA31BF0ULL, 0xC25AF38611C4CE07ULL, 0x8BC1E466F20872D5ULL, 
            0x5DCDDD274842ECBAULL, 0xDC600C6254C34710ULL, 0x4655EA5D8D51DAAFULL, 0x5588069E8C0D6432ULL, 
            0xC1408A3D2E321033ULL, 0x55A2C6262B7ABD30ULL, 0x873663C8879AF012ULL, 0x5424D7AB78B0FDEDULL, 
            0xE3CB48203AD7DA10ULL, 0x15D5CC234CE92EC4ULL, 0xC4B1B00C476928D2ULL, 0x8D54363AD438E332ULL, 
            0x60DE11E1210D4FB2ULL, 0xA7F40332DDEED8B7ULL, 0x3C404CBCCF1522E1ULL, 0x66BAD22E3A317461ULL
        },
        {
            0x52CA4F8A7357F1D2ULL, 0xDCB9DD35C40039F0ULL, 0x13C89DE4AAEFEB75ULL, 0x121291EA2468FB3DULL, 
            0x658BBB2DBE20A27EULL, 0x1147EEEC7DFBC27BULL, 0x12F6F185AD0872E8ULL, 0x074E916FC6038ECFULL, 
            0xBFFF0B19692E8448ULL, 0xD0AD1FF85EC4D6BDULL, 0x3CF8265F9DE3C5A6ULL, 0x232DEA9FE326A8D1ULL, 
            0x493325EDB5C69B8DULL, 0x38459DF0F8371C7FULL, 0x6CFA716916C39FEAULL, 0xFE5A01B97E541AE9ULL, 
            0x8C4CF5855DC0F7B9ULL, 0xEC7AD7CE21973947ULL, 0x732CE425BCF7E42CULL, 0x0AE36B0F282F1D25ULL, 
            0xDE971CF35841F984ULL, 0x82A4D0AEA047AB92ULL, 0xB235392B0310FF6AULL, 0x18E0EB1866A30BFAULL, 
            0x4ACB32BD5BACF324ULL, 0x5622641BB581C0BFULL, 0xBE29A368214D5F1BULL, 0x8AAEE86D05DD8216ULL, 
            0xAB8F00AC09BD0BB5ULL, 0x3DA0187E0D2B24BDULL, 0xCC3E78BF074C3D89ULL, 0x5838083783A73879ULL
        },
        {
            0x9F0AEFAE8AA92780ULL, 0xF833FF026A3A5564ULL, 0xDA48C3DF1985FB70ULL, 0xC0111EBDA5A20CB9ULL, 
            0x2E2F1AC7C7B32EC8ULL, 0x636B016274C7D540ULL, 0xCF9DE8C575BA04A8ULL, 0x68E5FEDF95CA9A9CULL, 
            0xB243F6D2A5A48DACULL, 0xA6B560578C73562DULL, 0xB1F0D4904F92CC10ULL, 0xF3EC57E707714879ULL, 
            0x9114E90B82CB1136ULL, 0xDE7F29C245798528ULL, 0x6D02C10F03DFA383ULL, 0xBEA670A37BE66B6CULL, 
            0xACB64A5ED5FD3005ULL, 0x7722C178FB6B62C3ULL, 0x517472AFC8575D24ULL, 0xFE7B7AC58D9A573BULL, 
            0x4DB84A05DBD107ABULL, 0xDCDABB50C04D397DULL, 0x546D9447E6050FDFULL, 0x018D11F83F29970EULL, 
            0x954ADC5E5D9CA4A5ULL, 0x48D0C1EB9093291BULL, 0x12C20DB1066B2849ULL, 0xCCEA077E0AA6307AULL, 
            0x4D73A24522A42BEFULL, 0x76A7E5167437B2A7ULL, 0x1A5A5EE21B8E4E01ULL, 0x7D3CF4204F5E0B01ULL
        },
        {
            0x3553271848473666ULL, 0xECAAEC0AA396948CULL, 0x9EAD09ED31C490F8ULL, 0xF211259F7468F792ULL, 
            0x0DB84B26232A4BB5ULL, 0x1819AA813A97D501ULL, 0x1C87DC1232B2EAABULL, 0x1519F5DB5215FE78ULL, 
            0x44BC5D313ABC1F05ULL, 0xB5B43B2D3C1C3FD4ULL, 0x502570475C2CB677ULL, 0xE41DFD3CFFBA1A5AULL, 
            0x98A855BAAA635462ULL, 0x763B8F6CBC56B8E7ULL, 0x1EC10947DCD2BC17ULL, 0x3AF1701AEF2A1F89ULL, 
            0x5C8E15E00E0C28CEULL, 0xBEDD2C2C744E06ACULL, 0x7FBAD4FE5D7DF240ULL, 0x8F9B976D34C6CA3AULL, 
            0xBA1AED03135C05B0ULL, 0xC7B29785C6D70AA3ULL, 0x63F89D1E379FB8D7ULL, 0xC2C8438AB0791F99ULL, 
            0x3A42082804FB7864ULL, 0xAAF1629000AB9A27ULL, 0x66D12FBCA65FCF4CULL, 0xD95DE1FE9CD86412ULL, 
            0x49674FECDB872579ULL, 0x35FD9F90D8FEC909ULL, 0x5793BD77757F345DULL, 0x48879FD3F3686EF3ULL
        },
        {
            0xFFDD4C48BE4B987AULL, 0x6DA748633C365FFEULL, 0x2B8777BC39F46749ULL, 0xAFE1CC947AB84576ULL, 
            0xCFBA8E63CCFEB406ULL, 0x736639975A50C69DULL, 0x38034B1CFE5166AEULL, 0xAFAAAC48D26DE54DULL, 
            0x0F253412C7DDD617ULL, 0x7DF5B7741431767AULL, 0x1DF4703C8DD60203ULL, 0x095F901E5B1A765BULL, 
            0x09254693C8214871ULL, 0xEA6FB05FAB53A3D8ULL, 0x89C113F2F67B2684ULL, 0x7320CB0DEBAB7630ULL, 
            0xD9F794A0907E1CC6ULL, 0x5E982A64E8D786DCULL, 0xD4D05EB80A2BDD7BULL, 0xD09566BF89899711ULL, 
            0xEA3D590F9D394DE1ULL, 0x12030F767BFEC2D5ULL, 0x7A670EC02D6D2014ULL, 0x59AA003DBBBAEE8CULL, 
            0xAEDBFDCBFBCA5D69ULL, 0x1CC5E3BBAFBCBB19ULL, 0x8471E19B679D63DCULL, 0x58DF7C4D19E160E8ULL, 
            0xB4B071B53A258875ULL, 0x86BAF0A1161B9DDDULL, 0xD59F74994D0AB19DULL, 0x344C5BF844EF6E5DULL
        },
        {
            0x13F03C07DCA02451ULL, 0xA579C930718F957FULL, 0x0C1D482453A75882ULL, 0x92525F15ED0E87ACULL, 
            0x2C572ACD9F537595ULL, 0x15FE6D2D3AB63774ULL, 0x9EDE24B4D9D5D1B2ULL, 0xAFE67B1136DD86ADULL, 
            0x243C12ABF377DBB7ULL, 0x5BDD2994C54D1358ULL, 0x03D17F12603C85DFULL, 0x8BE460EAB5C670C7ULL, 
            0x3BA771E9D2C31D48ULL, 0x4B6930AD484F7B84ULL, 0xC88DBDD857F40C42ULL, 0x215C0DBC06874AB5ULL, 
            0xCB305C9A5D25C3C0ULL, 0x35253651E9756C2FULL, 0x8DE0A3DD6F1786C7ULL, 0x78D2941D433E6DB8ULL, 
            0xCEEDB24F84E6D07EULL, 0x7DA25A284A447A39ULL, 0xDA51EE0A1CBF8104ULL, 0xBBE75C59108601FDULL, 
            0x50F0CE252750D393ULL, 0x9CF3A3D5268E03D1ULL, 0x6BBBFE516BB8392DULL, 0x14B89A0CD883B746ULL, 
            0x3DBF0A976A339CA0ULL, 0xD02FD379F9CA1ECAULL, 0xCFF70E8873301024ULL, 0xF358429431B1E35DULL
        }
    },
    {
        {
            0x0B96D5B6E9382BE7ULL, 0xD5BAC642D338C337ULL, 0x93D5D71EF2F678F7ULL, 0xEBC4392640032594ULL, 
            0xA7F449C563125860ULL, 0xE0600E629D23080AULL, 0x11572950DC32B947ULL, 0xA8DDEA45E6A887DAULL, 
            0x0A25775F09947642ULL, 0xFCB23E8EA2DA892BULL, 0xB9F0E142D06DBA9CULL, 0x0F258DEB91FDD5C8ULL, 
            0x7DDF8F5106083B83ULL, 0x10D024AC1A1C7787ULL, 0x3F81BD77E364C09DULL, 0x18B36C4B619E1DE9ULL, 
            0x4382FD6E872F33E3ULL, 0x3C30058E45DC89F5ULL, 0x312D095BA2FAD5D1ULL, 0xB2E8475F32CEB1CBULL, 
            0x0FC260617E0C1923ULL, 0x0DB1CC07F386BD85ULL, 0x5A45F22223A83AADULL, 0xEF8A0938749D4697ULL, 
            0x0F5108AA2E1A427FULL, 0x8CC3E9C31E6089F8ULL, 0xF25C949A6248FA70ULL, 0xD3D3EC0EA6084340ULL, 
            0xE85FCBC712C98E79ULL, 0x63C32D3354D4912AULL, 0x0CA0EA17036D1561ULL, 0x6C1B2B01A8D320DEULL
        },
        {
            0x93705851E3A42C26ULL, 0x25E45F628B6DE8D1ULL, 0xE5EA4C2D4795ED5CULL, 0x5840B8848E53F204ULL, 
            0x18219B92B2E3B16CULL, 0xFCE95AB73AEAB436ULL, 0xED428F268840F07CULL, 0xA433A91609A66095ULL, 
            0x588F4608BBCCA04CULL, 0x6574F75316C639FDULL, 0x12607BBF67D1FC1CULL, 0x2125B91547A53604ULL, 
            0x0DEB19DFD51CBFCEULL, 0x6349B75CCF5F5932ULL, 0x1FC79564114C3A82ULL, 0x35D11844297616E7ULL, 
            0x38AE4F4CE43A4305ULL, 0x78DA2DB7C9C00110ULL, 0x4CD2F295112E708CULL, 0x46B98A9D4DE1D6AFULL, 
            0xB830EC8AA4D2E51BULL, 0x2CC878E6FE423B40ULL, 0xAE14A69AA4673EE8ULL, 0x2E32271A8250B190ULL, 
            0x62FE7F0F8ADD836CULL, 0x2CA30081023B34F3ULL, 0x2EBCE7244B2CFDF9ULL, 0x5C7496272E2CF766ULL, 
            0xD0346149BC391D76ULL, 0x3C3749BE962A4D6EULL, 0x29BEDF39C8B939E0ULL, 0x8441738AA7C96A89ULL
        },
        {
            0x501B786FB726FFABULL, 0x3B03BCC337EDEE58ULL, 0x3F9EAD7AF1B19481ULL, 0x83928DF0B416795BULL, 
            0x179F42B55A96FD8EULL, 0xE7899B59CC397AA3ULL, 0xCE87FB793903AA26ULL, 0x69FA311D1EAB1357ULL, 
            0xB8AD2ED92FC8063FULL, 0x3268E5E449441E4DULL, 0x8827BF7608EF0F79ULL, 0x3F658292187F55AEULL, 
            0x8DCE06292B29301AULL, 0xF65F2CA7DE653BE6ULL, 0x34CBB62F8C4C0246ULL, 0x307BE3FB9A3ECD70ULL, 
            0x18CB5554F7314A98ULL, 0x016F966C4518A7ECULL, 0x12DEF432D7BE5475ULL, 0x1A304F05123FA6F0ULL, 
            0x2EC640BC477E258FULL, 0x1F3CD3714079B8B8ULL, 0x093DE0FF4888F8B7ULL, 0x8B244DCD66D2E0B6ULL, 
            0xF36192BC961303DDULL, 0xE6066A2FB0E3FD38ULL, 0xBB7208EB5E016A3BULL, 0xFF3A81AD6D045A70ULL, 
            0x9FECB24B34B82B78ULL, 0x27661A719B361C66ULL, 0xA1C5D18164343DE6ULL, 0x39427E43C53526A7ULL
        },
        {
            0x1A3BD28A4FD616D8ULL, 0x118ACC84AF315C4EULL, 0xEE2CBE893B3589C4ULL, 0xF46977CF7EA8A38FULL, 
            0xB8FADBE7332E6612ULL, 0x421C8114FC479A90ULL, 0x5FD6F9D21E12F3B6ULL, 0x0D921E019EAE6112ULL, 
            0x273E7BC55E5E6E3DULL, 0xFBE6D8C9730EEF4CULL, 0xF7A357C5E0CA39C2ULL, 0x7CED1E6C6158EAE3ULL, 
            0x13A01F5DC7212C14ULL, 0x3400D0389842136EULL, 0x5A4D2701CA62BE97ULL, 0x3EF2018EB43183BEULL, 
            0xAEFE76D8FE5B4245ULL, 0x837C8FE390F51B91ULL, 0xF6B5438A41CFC5E1ULL, 0xDD3AC118086E00EFULL, 
            0x2D23DB6539D73809ULL, 0x047E0733CF78DE54ULL, 0xA591D8AB60C4469AULL, 0xCF44FA55E49030ECULL, 
            0xDD668EF475FEB1AAULL, 0x6F8D2A97BDCFD98BULL, 0x1560C5CC039D52D9ULL, 0x3292DE5D16E475A2ULL, 
            0x8DAE4A779260F38CULL, 0x98BA02B6FB7CC276ULL, 0x13E41FC2F22E43FDULL, 0x9ABB381C55BACB43ULL
        },
        {
            0x04FAE25EC83ACB66ULL, 0xE4F454773470D92AULL, 0x7BB7AC258A7AC8FDULL, 0xB6AB03106C7D7304ULL, 
            0xC8D5A19E55D1C269ULL, 0x9B7ED3C3E08844F5ULL, 0x6A8B0029ACE15FC9ULL, 0x2774793F9D9197C3ULL, 
            0xBEB6EF8FCD8645C8ULL, 0xF27E215E56998980ULL, 0xC7CB8D21138E4E72ULL, 0x2EE0256172CD5946ULL, 
            0x89EBCBB6365D9072ULL, 0x34B592B7425BDBC2ULL, 0xCF57E78B46E839A6ULL, 0xE5F5812EB935E6B9ULL, 
            0xA6B5CCCC0505BD3FULL, 0xC959F8E41AE00925ULL, 0xCD9D7486A8C56AA0ULL, 0xDCEAE23120C7F391ULL, 
            0xFAC63581EC6ED37AULL, 0x474D1383AB1103CFULL, 0x1A32A46FF712D098ULL, 0x30B141FF1EDA56A9ULL, 
            0x09115B8284D16935ULL, 0xC0D3B0F309DF78D9ULL, 0x4D73EFD242B933D6ULL, 0x434B0702CCCD319DULL, 
            0xE5825FDE4A77DD36ULL, 0xBCC469258FB9D4C4ULL, 0x068E271793474F51ULL, 0x1FAA43F5378CE9F4ULL
        },
        {
            0x72D30419FF9A5D73ULL, 0xBFAAF4F24413CB38ULL, 0x25B83866C20ADCDAULL, 0x8DE5F0A578DDBD0CULL, 
            0x914C6E50DFC21F19ULL, 0xAC3E380E45E6418BULL, 0xC99153D255E26317ULL, 0x73058420FBD16267ULL, 
            0x8DAB718BDB28D8A4ULL, 0xD56A8EAC29C84DB9ULL, 0x5EDBC145EFC9283FULL, 0xCD40071574CE097EULL, 
            0x9BF112F69A8BADD3ULL, 0xA757945C23557207ULL, 0xCC5A283602FCDC3BULL, 0x68C191EA12660A8CULL, 
            0xD8F018608561889FULL, 0xA97ED4C2B1312357ULL, 0x32884F27B50ACEB6ULL, 0x7CEA97997ECC4235ULL, 
            0x5D90C96DAE69113EULL, 0xF8615DEFD9C98DD9ULL, 0x62C482D5DBCE7522ULL, 0x62D0CE44F534FA80ULL, 
            0x4E90633B6F1360EAULL, 0x2EED15C7472013CCULL, 0x7A87296AD58A7CB3ULL, 0x1268B49D23E4288DULL, 
            0x8247D0E8DC097A8FULL, 0xB74383193DA6A696ULL, 0xDF16626C6B462D16ULL, 0x72CAC3734D2E4619ULL
        }
    },
    {
        {
            0xB443A4D4A138B56FULL, 0xBC3C20D7EFACACFFULL, 0xA9FFF5220D30D55FULL, 0x513504ECD8875C19ULL, 
            0xF715C7C923A6E4EAULL, 0xA41960A85965DC0CULL, 0xFE18DDA2CB5E5569ULL, 0x17A8180FED48B300ULL, 
            0x1FF5A6CC7A74A77CULL, 0xD9C3B87700ED0740ULL, 0x3DE0356B7767E9E9ULL, 0xAA285582182FAAB4ULL, 
            0x5C584E7D41D5C08AULL, 0xC6DA9B2DCB4FDA77ULL, 0x6B082F6F286485EDULL, 0x68B89B8C9A3A7B3FULL, 
            0xD888E011214E8D1AULL, 0x903CAA06526DA8CFULL, 0xB3378AF6B4649118ULL, 0x3DD4F4C748CBFCE3ULL, 
            0xBB4E09CDB654380BULL, 0x1E9F9AA47A1E0043ULL, 0x0C12769BB6DB6291ULL, 0x7E9BA4A893E4612BULL, 
            0x1E407B2EDFDD80C3ULL, 0xBA4A031DD94ABD32ULL, 0x3FA818663AF10AE4ULL, 0xBED013E698351EB1ULL, 
            0x9126BF3099AE5689ULL, 0x79512CA999EA9508ULL, 0x66AFB3AB9FE446C4ULL, 0xCAE2CA13BDEBF1B2ULL
        },
        {
            0x6B688BC8F98E7493ULL, 0x0C2B1853637BD945ULL, 0xF27A5E015D2ED80CULL, 0xD0DB2EA0BFF15CF1ULL, 
            0xD0B7029B4DB259A2ULL, 0xA6C854BAC874B1E6ULL, 0x858F8B5C3E386B26ULL, 0xC225D4E4E6DDDBC4ULL, 
            0x3361D01D39A0EE35ULL, 0xE6CCF0A55592B639ULL, 0xDF01AB1486D499BEULL, 0xD707BAE524286078ULL, 
            0xCA0649B2814580A1ULL, 0xEB339BFAEAB81DDFULL, 0xEF2D887DF0DDA24EULL, 0x2CFDEDD290DB4E3EULL, 
            0x262A0F269E0D12D2ULL, 0x523965587A3EF99DULL, 0xC0A8550EB4AADA4BULL, 0xDABF8CE7744D6AC7ULL, 
            0xFAEFA1DFECCF0595ULL, 0x9B1BA27A976010B4ULL, 0x8452C3A9ACB6CE44ULL, 0x52C3A8BB5CB27712ULL, 
            0x567223657F16E6B8ULL, 0x232834B2F52475D5ULL, 0xBEA2B56BF9ED77F1ULL, 0x69D73B312CF4673EULL, 
            0x1B4CDAFF782264C1ULL, 0xB404E1CABBAC9FC1ULL, 0x52C9D069C6AB2C39ULL, 0x319E16B80DF52077ULL
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
            0x31D7BCA7069E0BECULL, 0x10F7898B4BE56F63ULL, 0xA6A5B4AB8C53E03AULL, 0x8B3E8440FEBB3E5DULL, 
            0xDDA0B98069F2E069ULL, 0xA2EF20BB6D9DE92DULL, 0x32F29A3409565532ULL, 0x46FAE46867E7446BULL, 
            0xA17C0C888B75217BULL, 0x182A115EBDEB7A0CULL, 0xA28A90BFFE3088B1ULL, 0x5CC559C7ED704A49ULL, 
            0x1F4F5057F2AA9D96ULL, 0x352DE4447A55043AULL, 0x271E03DD0032AC5DULL, 0xACFF53C6256D7D2EULL, 
            0x626EF5CF4B83ADA5ULL, 0xB5E219654AFA4B89ULL, 0xA73F863423CF1556ULL, 0xB34F9167E8A3BCE7ULL, 
            0x4B06C81EB0F532CDULL, 0x7BF1D89F7FB0998AULL, 0x38DE5F057AC838E9ULL, 0x2E327772E599D50CULL, 
            0x488A15AA947B085BULL, 0xC752F2AE7080B785ULL, 0x59DE6BB7B3BAF9F2ULL, 0xBC9EDCD36BE3DF3FULL, 
            0xD11F36034D000EFDULL, 0x5125B29DC2D2FF22ULL, 0x4E2A22D62BC6871CULL, 0x0C4EA4426C17EC37ULL
        },
        {
            0x6D7FF1324D45CDBCULL, 0xABE0C1599E7B3D9DULL, 0x95C2DC7727AB7046ULL, 0xB441AF39C1557D6DULL, 
            0xFE8FFE213E892725ULL, 0xDEA57491313F6EBEULL, 0x7E79C40E83EF92FEULL, 0xE8FF3CA565313DD6ULL, 
            0xA9172E5D6E1B0F18ULL, 0x89BCEDBA8E519A1BULL, 0xCDD86923AFFC6372ULL, 0xBFA509FF65821E88ULL, 
            0x2B1F0FA60B60E148ULL, 0x1DE6038FB5F1500CULL, 0x98A51EEEE6D5D21BULL, 0xF6F6DAB6626280F1ULL, 
            0x701B5F2D944F74EAULL, 0xE50D65B87A8F0216ULL, 0x94474602C943B72DULL, 0x07468A57DB1838B3ULL, 
            0xE7D1C7EF57382EBDULL, 0xFB03E27C8A007C05ULL, 0x8B08CCA53ED033A4ULL, 0x872A2B8872319C5AULL, 
            0xDE0925BCBAAFCC7BULL, 0xB161901BA1D157FAULL, 0x8C8E8210EF5FE950ULL, 0x0A1F155E541CF564ULL, 
            0x11455FC4E045FFDDULL, 0x4FA137C93A2EFB8AULL, 0xF2FAF50507127D92ULL, 0xAD9B566F093478A8ULL
        },
        {
            0xAF46EEE2B191BCF1ULL, 0x7056313686022C90ULL, 0x1597CB63F4E325F1ULL, 0x4532EE700AF58C19ULL, 
            0x17109BE2CD6D8457ULL, 0x0111DCF4DCE4754CULL, 0x348F046356F913CDULL, 0x5A1F07ACAA2FF868ULL, 
            0xBBACA1FD5602E2C5ULL, 0xF6F7A349CDA9D3FAULL, 0x91FDE115509B92C1ULL, 0x790E4A68908A47F3ULL, 
            0x3EEF64AACDCDC8D1ULL, 0xDC1CDFDCDC8EC2C8ULL, 0x3E73128FE59F9CD1ULL, 0xB13558F151749DB2ULL, 
            0x5A8C22B63A0EA442ULL, 0xF3C39C110EA76086ULL, 0xA145968E06ADF9A4ULL, 0x812C70F3AF0F4CE5ULL, 
            0x706248BDF1EC3239ULL, 0xBB5C8A38DA15EC8EULL, 0x50C66BBC9B38E3B3ULL, 0x8E6B7ECC90FB7D49ULL, 
            0xF02F1C80BEFA8974ULL, 0xF3C18A8D6E437E80ULL, 0xF58979ECDFD77829ULL, 0xDB5C56127EC45CF2ULL, 
            0xF9121D415D6930D6ULL, 0x4C6F11B708157DC1ULL, 0x1D01D419A123AA55ULL, 0xC537A0AFAA91031EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseDConstants = {
    0x70C6B868A4FBE0A4ULL,
    0x92A822748FE820F5ULL,
    0x16BF0BC8749F5D96ULL,
    0x70C6B868A4FBE0A4ULL,
    0x92A822748FE820F5ULL,
    0x16BF0BC8749F5D96ULL,
    0x477266534A13338EULL,
    0x66803D47F3EDE3B9ULL,
    0xEA,
    0x73,
    0xFC,
    0x53,
    0xDC,
    0x35,
    0x7C,
    0xC9
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseESalts = {
    {
        {
            0x1B0AC338DB65BA5AULL, 0x6F0F26057607F085ULL, 0x167C87099652990CULL, 0xA37CDB9F8ADD19ACULL, 
            0xF8F38A4304E41F71ULL, 0x35FC9D252880DDD2ULL, 0x7350B14283CB8069ULL, 0x94727A8DE7046A23ULL, 
            0x384529831D8E5E07ULL, 0x8E40CCCD5E18ED16ULL, 0x3C949E8D8CEEF657ULL, 0x3CA88398C8D0651DULL, 
            0x861A98DF7C4B82EAULL, 0x2965587112B80F75ULL, 0x6A113A0A907FC161ULL, 0x82E813DF3A8C7EBDULL, 
            0xD951BD15E190FEBDULL, 0x41766D391A7C62F2ULL, 0xA77DCC4EEEF23A07ULL, 0x7800DF43A2ECFAEBULL, 
            0x3BEA7A18596067F2ULL, 0x234E3EB6C4B7660AULL, 0xB3C2F1046E26964FULL, 0x42304A8B80691261ULL, 
            0xE16528438BEE396CULL, 0xDDCF24211CC9A24CULL, 0x1F37CEC9B2F93890ULL, 0xCB7C2CB7EA2D0271ULL, 
            0x4E6B4C3413075402ULL, 0x1C7C3BE1C15C7A17ULL, 0x574682A86E3BBE14ULL, 0x714BE2308F23E691ULL
        },
        {
            0xF2DCF8A278B6279AULL, 0xC70A4E5B8EBD1F8BULL, 0xFD4D40BE995BA67DULL, 0xCF884AD5E19353D4ULL, 
            0xC40ED3906A245CFAULL, 0x3FDB0D7FC28EDDF1ULL, 0x0E2E6C07E652C66BULL, 0xF63680E401A2C05AULL, 
            0xB2F73E35C9A9D3FFULL, 0xA1D4210E46EEA721ULL, 0x6C9EEC4C7F69F543ULL, 0x8E08FC8AA60F2914ULL, 
            0x16698D781221AEBFULL, 0xC6A719F8B625C4AAULL, 0x78DEB0581B3D6C6FULL, 0x68BC720339FE14E0ULL, 
            0x7A405D57012DB446ULL, 0xE9322CF39E590253ULL, 0x7B6B5C7B315CBDD8ULL, 0x08979A648656309FULL, 
            0x41FA9292E93FCE84ULL, 0xEA9C4BBD91FF3FDCULL, 0xCFFEFA36980F560CULL, 0xE19F3AE5BF8CBC06ULL, 
            0xE6685661645228D8ULL, 0x8E8D97D4A6B08FD9ULL, 0xCF2796D51556A7F5ULL, 0x15293070A4075DFDULL, 
            0x994ABE9E0A771C1FULL, 0xFF37A8E07A02E878ULL, 0x17376E5961CF8401ULL, 0xB9A4939A631EADF6ULL
        },
        {
            0xBB07FFD3970AA2CBULL, 0xAC2EB9FC757CCC8BULL, 0xB5385EA5287C5CB8ULL, 0xCE0FCC926CF36054ULL, 
            0xE39D066620DAE523ULL, 0xBB021146761A3346ULL, 0x73EA8E621ADF08E5ULL, 0xB4D7D017A0194677ULL, 
            0x852954F5E678788AULL, 0xF19F154AF5917011ULL, 0x1B03FC548CAAD3A3ULL, 0xE22708FE4E176469ULL, 
            0x923BAA9FFC65AEA6ULL, 0x72CACD3286CE8D1BULL, 0xBE3B22155B40C266ULL, 0xDB4D5F185E203E4CULL, 
            0x218F6F0345F731EEULL, 0x8694FDBA9384F27CULL, 0xED076617CC341621ULL, 0xB04B4EAC7F85020FULL, 
            0xF10418BF0B6F3935ULL, 0x74173ACD1A39FF28ULL, 0xABD1C596E0B3F215ULL, 0x9D0EE5FD130D772BULL, 
            0xE508FA840B950EFAULL, 0x0E757A1BF9A54F20ULL, 0x71371221F51F041AULL, 0xC0806CB0755EB384ULL, 
            0x91F6FD96E63D3708ULL, 0x6DA58710E72427D6ULL, 0xB916BFDAC2CA9F1CULL, 0x6E8CC842C21A1ACEULL
        },
        {
            0x6716D8D0D14F7E1EULL, 0xB37E0A03205FB253ULL, 0x060F999F4826873CULL, 0x415178D59B2AB5E5ULL, 
            0xA15E0BE30237E527ULL, 0x79BD81AED182CC96ULL, 0xC3E45684BDE12EA0ULL, 0x85378321D0E9647AULL, 
            0x310FE33B719023B1ULL, 0x0DBDB524417C8644ULL, 0xD93C0EAFF52F48DEULL, 0x015B748C801360D8ULL, 
            0xEAAD56A93D376449ULL, 0xFD135D009539B9C7ULL, 0x573760DF3139E97CULL, 0xC4244FB9AF13669FULL, 
            0xB69F8E86C3609E89ULL, 0xE40559BF0DEA16D0ULL, 0xD1B289325680199EULL, 0x7977E1EB650F415CULL, 
            0x2C897D156A9EB729ULL, 0x447EAFE58BF6C418ULL, 0x5D4800337D08D238ULL, 0x900B5CD27B914EE6ULL, 
            0xBA4E8583D2A5C987ULL, 0x81F6FF0E474707FCULL, 0x97614E7100FE97DFULL, 0x664ED66766D00FFFULL, 
            0xC942FD2A20015B4CULL, 0xC9C7C81B71F58B84ULL, 0x68EBD376FC5563FAULL, 0x0CC3BB76DEE583AFULL
        },
        {
            0x91D2051008EB3D7DULL, 0xC09B9E8241C0048DULL, 0x84BE88048FB966EFULL, 0xDF3FABCE0C67F7E0ULL, 
            0x2E5C4C8514AD51DFULL, 0x254770960FE3C792ULL, 0x57044A40E3011DD6ULL, 0x4AFA8A0CD4BDD1FAULL, 
            0x33BC27BAA29C56D7ULL, 0x696E7FCB7256E089ULL, 0x08BABA95D618438CULL, 0x13AA503AC0D0707DULL, 
            0x1F950B8D00D9C448ULL, 0x30109F5366B7D946ULL, 0xCC074A2827C1F079ULL, 0xC23E0766D81A9FAEULL, 
            0x34B7B70AF7610420ULL, 0x7E1157362510DC9FULL, 0xD82DA6DFEAD9A287ULL, 0x1D369AA21CA64027ULL, 
            0xBBC949D35B2AF557ULL, 0x27A0CACE67BBBED6ULL, 0x99524A69BEF69649ULL, 0x8985258ACED32976ULL, 
            0x90E3C2DBE1D5BB89ULL, 0x5D75D3A69C7A550EULL, 0x7482DFDC3604DAAEULL, 0xD727538184C92EA5ULL, 
            0x97C16BE46BE25B49ULL, 0xFAF9C78E9A5F1298ULL, 0xB3BAC6AED3C88A94ULL, 0xD88243AB9B0B5F91ULL
        },
        {
            0x316E8F5F753E5FC3ULL, 0x055292EF0F2D4983ULL, 0xEA33739C045A66C8ULL, 0xD821832469BF865FULL, 
            0xA03ED34CCEB5D54CULL, 0x848210D428B3CA42ULL, 0x8219C8DE48D2E96EULL, 0xAC68EDC1D557AFCEULL, 
            0xBC09D6AA8BF0DF0CULL, 0xDB7A6ADD90CF8D21ULL, 0x9F66C41471CAEE98ULL, 0x30B9423E2D00EBCEULL, 
            0x8956A84E89AF2FDCULL, 0x5BA054BE64092D23ULL, 0x3D69A0C1E5CBDDFBULL, 0xACCDDF28FFE8606CULL, 
            0x66C5C1F32F522B16ULL, 0x8D48790537C5254DULL, 0x6AF478525B92A253ULL, 0x7D5B621000F42297ULL, 
            0x462EBFDEF9EAED14ULL, 0x7936D05AD0585E79ULL, 0xE969132AB185EA50ULL, 0xBE1F9C0F917A7485ULL, 
            0x14CA280066C9FF97ULL, 0x8890CD44F042E824ULL, 0x512A3BCF9A4268FCULL, 0xF1392EDA7893C049ULL, 
            0x778861501AD1E93BULL, 0xF4E08101772AE5E4ULL, 0xD7580E1AABBF6C4BULL, 0xB6C0D4DE9B5827FAULL
        }
    },
    {
        {
            0x82376F9722BB0C97ULL, 0x6BA484DF2554A7FEULL, 0x7F0050960502C2C9ULL, 0x31B4896B15989AB0ULL, 
            0x52F73E9472E64607ULL, 0x93E691BC8DEF9682ULL, 0x17D59315F33FF3F5ULL, 0xFE4E40C97B5C232DULL, 
            0x7408242BB4F4979AULL, 0xD95691EF55BA50D9ULL, 0x264B85CAF7D2E401ULL, 0x2D7A065D54B4522DULL, 
            0x46CFF82968F66EB9ULL, 0x0C63866F9A23DB1FULL, 0x89B6C3223BCB8AB1ULL, 0xE1B232F5531B540FULL, 
            0xE29A3549C876C91DULL, 0x2B9824593055AE14ULL, 0xDB45D2C8118C93B8ULL, 0xF81662F1212747CDULL, 
            0x59CFE1971A0B0C24ULL, 0x64DF26679D1E8931ULL, 0x00A1C5F0F3F54965ULL, 0x34777FE07CED6994ULL, 
            0xF558E21D1CC77C58ULL, 0x6387C40A7EF1FF99ULL, 0x8EDF608A950E7598ULL, 0x23411E1430520805ULL, 
            0x54C15294E848EA9FULL, 0x13ED86D64FD56EFCULL, 0xBDD8FA82BC11BAB2ULL, 0xEF90701AF8CD6E0DULL
        },
        {
            0x43214C9E4CE3F014ULL, 0xC1B81CD91E9904CDULL, 0xA171D0AC2B2B9F52ULL, 0xD1F88F4F9BCD22E8ULL, 
            0x1BF93C5D70D88F4AULL, 0xEC91299E24A1ACCFULL, 0xCB01C4A49B185FC5ULL, 0xB9708CE3D81DBF55ULL, 
            0x353F63D4FA91BB50ULL, 0x35DCC025988800A0ULL, 0x8C1C8A5FCA7F9A8BULL, 0x6F68562502556826ULL, 
            0xF21639BBAF796AF3ULL, 0xADF38BD21CF1470EULL, 0x92278D5346EDD5F9ULL, 0x06E21357C46813CCULL, 
            0xBEED0EC9C5717F21ULL, 0x237315F33E400901ULL, 0xE9E4737ADA17DF45ULL, 0x40132B77E294DDD5ULL, 
            0x444693CC61A1BBC5ULL, 0xC9C97AA0B591E5AFULL, 0x6AA15BC129DE243AULL, 0x1E0FAEABC2C43276ULL, 
            0xA4AD592B2915962FULL, 0x12B0E61C9E4EE40CULL, 0xCD532473B7AD86DFULL, 0xF566ACA7A0A236F6ULL, 
            0xBE2BFE28488C4C10ULL, 0x30E7868D031AB13FULL, 0x223BFD340B3922A3ULL, 0x7F7481B06BC0AA25ULL
        },
        {
            0x879E1F9F139EB8D2ULL, 0xD695ACD9F79C9D7EULL, 0x13344041F9067AC7ULL, 0x3819914D2B036840ULL, 
            0x51C117A7B8992ACEULL, 0xFB7F92F024973F72ULL, 0xA7C91F5556175287ULL, 0x330F5879E295CD7DULL, 
            0xBC63D07C403F5E82ULL, 0x0B0628D2B895C8FBULL, 0xF4C3CA389EE78A7EULL, 0x46E5F3BB39FE6CBCULL, 
            0x3DD9CFB30C1919CFULL, 0xA0EBED4AB1CE10FFULL, 0x32C516C256076E97ULL, 0x244FABC1B80C7111ULL, 
            0x4D37AA5180F9863EULL, 0x7F62C7BF80409F45ULL, 0xBE5FBB5532C96D5AULL, 0x133D60E80F5C33B4ULL, 
            0xA0A8B19E24D66A42ULL, 0xEA549440369B8E24ULL, 0x351661260F3E274DULL, 0xD98B9A3870D4EFD6ULL, 
            0x51EEA8A616133FAEULL, 0xD07FF202DD1088FDULL, 0x09C443E66216C5C0ULL, 0x23944D4E5DF37E37ULL, 
            0xE4AE7CAC4B15E335ULL, 0x37C895D951ECB79FULL, 0x7793F6702569BB2BULL, 0xE029518CBD1DA3BDULL
        },
        {
            0x8CA593B74E9E6D17ULL, 0xC1BC66AB17F61A74ULL, 0xF59026323864B458ULL, 0x953F7EE95A8DB894ULL, 
            0xE19C24E108967DE7ULL, 0xB140FC407791B0ECULL, 0x05EC0CFD0F5BE417ULL, 0x004815E0B8D19EE2ULL, 
            0xBC2016C2231BC0EDULL, 0x4C984A27B20D7E47ULL, 0x492CDFF1A466D7E1ULL, 0xB9BED1B6978A5632ULL, 
            0xF0C166AB798DDEEFULL, 0x92CF330590DA0D15ULL, 0x2ABF2CA980F9877CULL, 0x9C855F2BB96B9708ULL, 
            0x5739092A36C4B784ULL, 0xF4EAE4E46BF40BACULL, 0x04FD29E521212F69ULL, 0x859DBA80E51CEAA6ULL, 
            0xB0B95B192594F400ULL, 0x4B72C464FBFA2C44ULL, 0x29D48AE66EB64821ULL, 0x3F3CEF36577CDD9BULL, 
            0x1BACBBD91B57469DULL, 0x015D024FBED55EC0ULL, 0x247C5FC2E1CFF8B2ULL, 0xDA6F086947A02673ULL, 
            0xC5A0B1AFDAFEC9DBULL, 0x4898E2D4FA2818B1ULL, 0xF42BF493A02D2C2EULL, 0x93F39E38CBFD5ABCULL
        },
        {
            0xB048AE58165C05A9ULL, 0x03A656CB673D44E0ULL, 0xBC5136F04A1BB145ULL, 0x00CB74FB4C219690ULL, 
            0x3C33113FB7DF0496ULL, 0x07F239525490D7C9ULL, 0x0C81840E8E09E1E6ULL, 0x23AC5B0E57F4400BULL, 
            0x7DB55C57BB89B2F1ULL, 0x23749F295A50DCA4ULL, 0xCA58C053F2C66188ULL, 0x5E59EE00ABD66464ULL, 
            0x4B682DFBAB376AC9ULL, 0xCB944C2FAB9DCD1CULL, 0xD6C8F8A5E9ADE38AULL, 0x6041E2FC3102B403ULL, 
            0xCD3F990B704FA76CULL, 0xBC6FD2B0CC704A3FULL, 0xBBAEDB1D781967D5ULL, 0x7E0C09348535CBAFULL, 
            0x8794F679EEBAF4BBULL, 0x1E3818A477025913ULL, 0xF089420A237F17E8ULL, 0xA92A5467826A95E5ULL, 
            0x5649179E3E787377ULL, 0x8C25AAA9FAD5F8F2ULL, 0x872250DDA5ADA13DULL, 0xD177E21AE9152942ULL, 
            0x3A54FEB213EE6D8BULL, 0xDC7CF6E665D1B83CULL, 0x16FA22C273065D3AULL, 0x27F4C7CC9D60A456ULL
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
        }
    },
    {
        {
            0xAC55A667074D1E0EULL, 0x91B49940EF8AEBACULL, 0x95C0F707047DEF27ULL, 0x21482F5D1C3F0258ULL, 
            0x31292EE3C8C27444ULL, 0xB513EE7065B1CE33ULL, 0xA6DFEFB9D065B592ULL, 0x4FB95389B5E6D9D8ULL, 
            0x42DDA0D07C984F9AULL, 0x71AE7D121205E4ABULL, 0x4BA33E756BA17108ULL, 0xDCF6A8CC4632EB68ULL, 
            0xC2BBEEB2DBDE9020ULL, 0x5F9519E85CE88D0BULL, 0x4F711EFDBD5D693CULL, 0xA767D9D36119F881ULL, 
            0x1345216E5F6F4A4CULL, 0x692D1A27530EB255ULL, 0x9021C360D21CCDE1ULL, 0xC4AB8F81E25A955DULL, 
            0xD20B94641E42A2F6ULL, 0xBD0D84860D7AE2FAULL, 0xB21A92E9F51C68D8ULL, 0x0DA314F6C99D5B48ULL, 
            0xA142153EAC13E53FULL, 0x956479D929C22D5DULL, 0xBC113C7D9618A806ULL, 0xFABC56854DABB019ULL, 
            0x8FEC7BF2C03DA910ULL, 0xC0D351159251A6E3ULL, 0x54329B8D58CD8BA8ULL, 0xDE59BE278A3EEDD8ULL
        },
        {
            0xC35A5087861A1E2FULL, 0x8C1CDF51EC11DC1EULL, 0x5AD8B8FBC382315EULL, 0xE44D4808C65A1FFEULL, 
            0x13F1B124FEEAF3FDULL, 0xED197F1355BE5186ULL, 0xF739773148C3A674ULL, 0x1D4106BE7289A616ULL, 
            0x40A53A3686EFF975ULL, 0xBFBC0AECA66A0964ULL, 0xA4BA4438761657EBULL, 0x0838173B53DED042ULL, 
            0x88554F6312FC630DULL, 0xE1572009EA6EDC86ULL, 0xF4A5860B20666B76ULL, 0x29A687F784FB6C68ULL, 
            0x7ED7F00EE5ADBDD3ULL, 0xF1F0F16C7F4E9D86ULL, 0x0ED1B8E45C732519ULL, 0xDC17DFC0A03665BCULL, 
            0x9BEA7D0559F5B5B2ULL, 0x95F5968D8B5F81D8ULL, 0xFBFE5D7D5869B200ULL, 0x983F730CE2C9B063ULL, 
            0x245D62C00B3EC7E8ULL, 0x1853E291A3334D70ULL, 0x68DB5C079C868884ULL, 0x63E4D09F18D59A33ULL, 
            0x4BDD264521125C40ULL, 0x351BE8FC5A00CFE4ULL, 0xCD0C7C2966D88788ULL, 0x13807D4DE56B4F16ULL
        },
        {
            0x10172F1195CE2660ULL, 0x74284D7FD2DE9EDAULL, 0x4343CD05FD2EC97BULL, 0x0AD7194E39B2EF1EULL, 
            0x32AB2D1DC919AF0BULL, 0xE510AF95DDA46A73ULL, 0xD285FFC30125EFE7ULL, 0x003736CA54A293CCULL, 
            0xAC680D066B647BCAULL, 0xAAD40AFC4FFEF809ULL, 0x455A6AE29E6DBC02ULL, 0x4FC3CACA08E83218ULL, 
            0x8A3D7F3237CD74A8ULL, 0x59F77C584DBD0A77ULL, 0x6CB8DCF300BCAFD6ULL, 0x84B86F539778C732ULL, 
            0x67284044C7EE9D6CULL, 0xAD252F85F1AE500DULL, 0xA951206BDFA74868ULL, 0x65D94746EC437044ULL, 
            0x70EA87843DB3B872ULL, 0x54682FF9BD66956DULL, 0x90C1063D8750A081ULL, 0x1869A3B4BC3E154DULL, 
            0x36D6D5D951F785A8ULL, 0x5E3184A73C924FCCULL, 0x115C45698259C7DFULL, 0x4ED73A338957CF9AULL, 
            0xBD0469A0838F7729ULL, 0x39F06E0D54A59136ULL, 0x33D4B4281762ED8EULL, 0x0CF8912B7A049D41ULL
        },
        {
            0x7106FEE08846C191ULL, 0x692E2886A3FEF3D7ULL, 0x00E9EDE817CFDFDAULL, 0x36115C39953B4054ULL, 
            0x737121AD6CBC25DAULL, 0x8F1F7DB0445A6807ULL, 0x9258A2DFE282A614ULL, 0x745EC18D0BB9138AULL, 
            0x5F2921B758E1E753ULL, 0x201D7A6FD5B7BAFFULL, 0x378DF915DAAAEA66ULL, 0x54DD2753B9674C22ULL, 
            0xF671DE0058380B21ULL, 0x2D3FF31AACB16B28ULL, 0x767D2F6BE5D57A1BULL, 0x59289C88BD439971ULL, 
            0xF5BC2B31166DF6FAULL, 0xAD39DF6596A4F45DULL, 0x53A31AE75BE059F3ULL, 0x17D547DABE013521ULL, 
            0xD4EE7BAAE787BF5DULL, 0x37AB545C372D7479ULL, 0x834837C81D888EBAULL, 0x97B7302A881A34A9ULL, 
            0x2BB336CB9F669B5EULL, 0x02B15AF0F4FA3954ULL, 0x168345216286B0E1ULL, 0xF2A92F8D0087E44CULL, 
            0x567C85D9F13BA3C3ULL, 0xD363DB0DE9D7B095ULL, 0x9D2148517A505295ULL, 0x7A99F1710416CC3BULL
        },
        {
            0x5DCE85DC2F4CDFECULL, 0xB4434E3B90E5871CULL, 0xC619AA59C38E9C14ULL, 0x34C88B750821BE20ULL, 
            0x067B1CFDE45ADE48ULL, 0xC66CC11B78F2BDCCULL, 0xA1CA82CB659896BEULL, 0xB372379FDD0361FEULL, 
            0x8254C40812DD900FULL, 0x53B8B83156DE0B14ULL, 0x24F4EDBBADD51616ULL, 0xD41A9586E542AD6DULL, 
            0x9D0188E97264E7F8ULL, 0x61A61CCF02136090ULL, 0x95DD6404D4A436A9ULL, 0x5569F5AC958BA3B9ULL, 
            0xD49DB6EAB9AA8281ULL, 0xB8C30A3A72F01F2BULL, 0x98026CC0F2D1B84FULL, 0x7FF77438D26B35D0ULL, 
            0xD0A1902A749EF8EBULL, 0x86F3FE348EC96714ULL, 0x5585B1B09B2CA4F1ULL, 0x24B6676A71E4B5E0ULL, 
            0x216DF1851386D600ULL, 0xDDAA4F36DCDC2E57ULL, 0xE2FB8294CA5C5E27ULL, 0x75BF0C30A46037A9ULL, 
            0x7F06350D7132F1C8ULL, 0x50D8B0A66AF2D843ULL, 0x3F77F3982DB17EDEULL, 0xBA6A285A1A3BB618ULL
        },
        {
            0x6A29FA593CF74B91ULL, 0x9CF0906C406FE2BCULL, 0xADAD3805E699583EULL, 0x9DD673DCA4C7502EULL, 
            0x72B654672E75B26DULL, 0x079B141370C84850ULL, 0x01533A64B8DF1D67ULL, 0xCF52D42253770C0BULL, 
            0x08EE42AA5439F4A1ULL, 0x5DF134119E010276ULL, 0xCCA75F0617493CE4ULL, 0x83B4E4E81A873F4EULL, 
            0xD30D357F0C3B78DFULL, 0xEC3D4654B836545EULL, 0x2C3B41AA5A243880ULL, 0xAEFCD4BFD462BB15ULL, 
            0x8F965233DA9C80C9ULL, 0xC9BE96882DDD27EBULL, 0xA93791370F88AB8DULL, 0x2F9C9DFCB68F437EULL, 
            0x4409D6646A2A6AFBULL, 0x2E4273AB4A5AC704ULL, 0x3069549053666616ULL, 0xCE8A8784E57033DFULL, 
            0xD3666681E8CEE525ULL, 0xF0F5B49987112ADCULL, 0xCF43E446D262F8B9ULL, 0x6B6125BC0D8096F5ULL, 
            0xD380ED9CC11D4016ULL, 0xE5D43AD83854BF5EULL, 0xBE31960EA61CAB8DULL, 0x6463567016A20567ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseEConstants = {
    0x53F67592E907B8BEULL,
    0x9A35D0E0153CFFAFULL,
    0xF19CD158B53FADE8ULL,
    0x53F67592E907B8BEULL,
    0x9A35D0E0153CFFAFULL,
    0xF19CD158B53FADE8ULL,
    0x8873773DDEE9639AULL,
    0xAE95D6D7FC8E2C65ULL,
    0x31,
    0xD5,
    0x5F,
    0x20,
    0x5E,
    0xB4,
    0x38,
    0xFD
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseFSalts = {
    {
        {
            0x5B148F36A13ABEEBULL, 0xF2B900CECB7D2CFDULL, 0xD35E71EF68661D0BULL, 0x9A0D86CE1088F0ADULL, 
            0xD92F5E2086B3135DULL, 0x313F021267A055BAULL, 0x681E6AD0CA6F2098ULL, 0x6B33F1FA2226B027ULL, 
            0x33911A3C55F65523ULL, 0x5E995372FD961D30ULL, 0x76D9C50265705DA7ULL, 0x8CE9A8626B64F1E2ULL, 
            0x8E6B2AC00EDDE9BEULL, 0x57DC3B85D9C0E5B2ULL, 0x17ED1F2A96ACD406ULL, 0x6CE16B678C28FF21ULL, 
            0x610CB4E0E6876BCAULL, 0x9B10F59AF65F53EDULL, 0x53F2AF30F8FF9C86ULL, 0xA121A1C992B36C11ULL, 
            0x5E706F50F301AD05ULL, 0xF6B0E893EFA6D186ULL, 0xC6DB4187C8B54242ULL, 0x02E73939D60C3B7FULL, 
            0xF3A6CCA08DDBB839ULL, 0x90BDC76703A13C3EULL, 0x0733F9E816F0CFF7ULL, 0x486FFBD76B16BCE3ULL, 
            0xA84D387EEF37EA51ULL, 0xE789820105CD7807ULL, 0x11577136C711B6CDULL, 0xD4C42349A6615299ULL
        },
        {
            0xEDCD1A441C9F4BD2ULL, 0xEF0D4D4AD42393FEULL, 0xF9277DF1286A7DD1ULL, 0x7910CE705E3EA26FULL, 
            0x28794B37DD6FDA5FULL, 0x2B7D6F431EE2185FULL, 0xA2ED387A63301AF7ULL, 0x7C3E4167E65D7C62ULL, 
            0xB0F1B2079E595225ULL, 0x7E1002941C54A92AULL, 0x39069DE1F61681A2ULL, 0xDE1619DCCCBB5230ULL, 
            0xC9E9BFF1EB56BB93ULL, 0x576B1D0DCD184584ULL, 0xAE211E0E83834FACULL, 0x5AD3F67BF5147F30ULL, 
            0xF5C51F932C2E8DDEULL, 0x2BD215018E62733FULL, 0x58D3EC28865B5720ULL, 0xE839EAF7EA3383D1ULL, 
            0xBBE178003E828FFFULL, 0x1541A5049EC38F11ULL, 0x89B237C8489AC2E9ULL, 0x2BEFD1065585E995ULL, 
            0xC5C4246D62744C0BULL, 0x1BDE4F6CA4F1F385ULL, 0xC365A3ED1FC4E79EULL, 0xD3A7F8445C3CA394ULL, 
            0x2068D0CCEAE45593ULL, 0x9185380312CED64EULL, 0x0052E15F010709C0ULL, 0x03171F5C2CEB0323ULL
        },
        {
            0x2F764E5B047AFA57ULL, 0xA4230BF83EF513EFULL, 0x876A65981B4FCC42ULL, 0x41133CAA4E62E406ULL, 
            0xD2CB2534C2AD8712ULL, 0x25666B0EB41A16BFULL, 0xE859EBBB593338F6ULL, 0x623D4E7458ACC995ULL, 
            0xAAFE25F33BD335D6ULL, 0xE327564442F045CDULL, 0xD6CE93CCEA38F547ULL, 0x89CBA9636083BF31ULL, 
            0x6F29114A613BBE2CULL, 0x3ADB3E1B728F497FULL, 0x7D2ECE69449D4671ULL, 0x8931B41D9A0BA36DULL, 
            0xB7655E046C12EBB5ULL, 0x34756A276795A425ULL, 0x78468E7A5600F1D2ULL, 0x3B4EFE6922A10591ULL, 
            0x10DCB3230B75BA71ULL, 0x814AD2B2FE26ADAAULL, 0xA74EE23666CD5FC5ULL, 0x21B4C746B6049AE8ULL, 
            0xAC63E55F93F9DE36ULL, 0xE99A3DF3785FD2E4ULL, 0xF08995F911FC8393ULL, 0xE103B5EC1D62FC97ULL, 
            0x008539C80505254BULL, 0x4F4BCD75BC18FF3AULL, 0x9BAB5E037F77BA8FULL, 0x773579A794E28592ULL
        },
        {
            0xCFF64CE5DAA38A2EULL, 0x6499D1DC5EC8EB1BULL, 0x16BE9C3547AEDF61ULL, 0xE3D0C22B9899BBE0ULL, 
            0x5AB3CC98B54C9D02ULL, 0x70089ADDFF96F464ULL, 0xFC9B445D972010A5ULL, 0xAF98D76283CB49E1ULL, 
            0xDDF39E3A87929F58ULL, 0xC3419DE20E1ABB04ULL, 0x2EB29211CACAC4BDULL, 0x21B0E253F09CCE05ULL, 
            0xA6827A3324A44128ULL, 0xFC8B8FDF6B53D4C3ULL, 0xFB1666ABAADD4441ULL, 0xE9748E7E122A7E5EULL, 
            0x0E1E4F19FE0DB5A9ULL, 0x421BE123784AD3DCULL, 0xDFA84DDFE234654AULL, 0x13708D40951A9B80ULL, 
            0x94EB68E3BCC5F46DULL, 0x73D6C9B333316357ULL, 0x4EBEA81C16BCEB63ULL, 0x8274A016C79B5D48ULL, 
            0x61546F5CD435101AULL, 0x46B875583498B53CULL, 0x3BB6D09D7437AEB2ULL, 0x062FFC08E6DC3523ULL, 
            0xF7D37AAC9307F39AULL, 0x702C0A822F641A92ULL, 0xB485F0C8BBFD8530ULL, 0xAF50D7F2BF82EB28ULL
        },
        {
            0xB487E5293B88F830ULL, 0xADF8966EF7058943ULL, 0x1A28722C78D76052ULL, 0x08A520452B61D3C6ULL, 
            0x8E812E15E560DC4EULL, 0xEEE21E78AB9471F0ULL, 0x9934D8E1D8C2FC19ULL, 0x2F793FC40B613892ULL, 
            0x50C7491231720190ULL, 0x054694AF9A50965BULL, 0xC6E2FB0B9C3E3430ULL, 0xE7C12C7FB80B8CD0ULL, 
            0x57E2926F89009952ULL, 0x79393B02F743F4FAULL, 0x09F2426E15AC7B5FULL, 0xEAAEA876B50616B5ULL, 
            0xA5CEE2DFB0707EF0ULL, 0xFC00711C6A7D4FBEULL, 0x9A8C104C9BEA16BBULL, 0x1F1C3842C28ADFF9ULL, 
            0xD9E8EBE2637BDF27ULL, 0x4E3B3BDBDF0BB073ULL, 0x843650EFC938111BULL, 0xD8534D4B78C1BF1AULL, 
            0x86B157D402214E2FULL, 0x5F9DF873E8C94413ULL, 0x736BD056A7C0C79FULL, 0x6F09C26468543A77ULL, 
            0x0E1F5554DDC9D0A3ULL, 0xCA9B262A9246F9C6ULL, 0x6D851E38F105FD89ULL, 0x079E61A1ABF50E52ULL
        },
        {
            0x3847AA1596C18DE3ULL, 0xD0DE9BA18FE1CC42ULL, 0xB644F0C9E62C65FEULL, 0x421059575020DEC0ULL, 
            0x6A8F9D032B09E8DEULL, 0xA2287266EAC21A9CULL, 0x3EFCDCC627A5A308ULL, 0xD1B208601DCD408FULL, 
            0xC3AE6B7A18245FE3ULL, 0x733DA73AE844DE6AULL, 0x7EE55DEAB2AFEFF8ULL, 0xEDB2E15E240C46BEULL, 
            0x5A314158469AE068ULL, 0xAA0B6299831D4D49ULL, 0xF84D5A48A2A7819CULL, 0x5DD4F37E25A3ED4FULL, 
            0xCB65F4C4FC0528F4ULL, 0xEF91CCDD36083483ULL, 0x7D6C7AF9F4469D7BULL, 0xE45D33A45684B6B9ULL, 
            0x2FA581BF9437B6D8ULL, 0x4A21DEF78DE31035ULL, 0xF1FB007E6F575CBEULL, 0xA3BCCEDCDC9C4F6EULL, 
            0x4BAF17859ADB96EAULL, 0x7C8DD8D8F5A75E69ULL, 0x2779C752C6CACDEBULL, 0xA6C93F96271ED35AULL, 
            0xDDE140920FCD929BULL, 0xBE16ED6A57D02CF7ULL, 0x8C25AD8BA06FDD4FULL, 0x1836E843E6DB52BCULL
        }
    },
    {
        {
            0xF312BC2AEE6C15BDULL, 0xEBC4D247C1353B50ULL, 0x192919B5DE055939ULL, 0x187E02E12B710CAFULL, 
            0xDB40BDA03016AFB2ULL, 0x0E67EC7579504761ULL, 0x66C0BBD17ECA73E9ULL, 0xCB45422F8C7ADD1BULL, 
            0xB220744B60161188ULL, 0x1FECF18217A08A1BULL, 0x78BF7D3A2E36B59AULL, 0x99F48173B657E3D2ULL, 
            0x8AF1DF2F96E00447ULL, 0xDD2885010E8CDAE6ULL, 0x8CC2CCBFFA059EE9ULL, 0x8241F07673D08BDEULL, 
            0xD42249D3C5AA87B9ULL, 0xB23ACBF76687B063ULL, 0x0E06601C1A5B77B3ULL, 0x5B38F8861FB4AE93ULL, 
            0x47353CBC6AE6BCEFULL, 0x781257169D48DF05ULL, 0xCDE802827E6BE7F7ULL, 0xE6E798BB12F57640ULL, 
            0xFE16C0B9EE88226EULL, 0xFB316103DC45F678ULL, 0xB5D608BE71EB8C9FULL, 0xFF2D1CA12022DC81ULL, 
            0x1AB99A42244F84D5ULL, 0x772D265084A29EF2ULL, 0x6E33FB73F7FA71B8ULL, 0x9D1CE1668CA230F0ULL
        },
        {
            0xFCD64C774241965EULL, 0xA2F8709FA1202EA2ULL, 0x45B98ED8F347BD0FULL, 0xB889A58BF7350B27ULL, 
            0x6649AB88DA1F1352ULL, 0x666FF4A69160051EULL, 0xC507947B585A3A7CULL, 0xF1C535E807A766F5ULL, 
            0x767FE50DF72AC19FULL, 0x7EAA34632C76E4E4ULL, 0xC6B49AFC729727B4ULL, 0xF66DEFC70E17B126ULL, 
            0x3D5DF0CE613756FDULL, 0x73F02FB3B3CCBA75ULL, 0x420EEA307EDD4CBEULL, 0xFD9F5AA9335961B9ULL, 
            0x61DC4AF3A1DB5146ULL, 0x183565BE5F0BE6A0ULL, 0xC5802727AAC74D95ULL, 0x1DBB68FF9DE037DAULL, 
            0x9814113FE4B5991EULL, 0x287AE6AF913CBB11ULL, 0xAAE284672039E51DULL, 0x5B8BEA5F4F953321ULL, 
            0xD196462EE1B36290ULL, 0xC685A0BFE1579FFFULL, 0xD50EF3D7DE352BDFULL, 0x928B05A39C92F3E2ULL, 
            0x360518F23E6F483BULL, 0xE85169CAFF25A099ULL, 0xFA2C80AC8F2595D9ULL, 0x16AA0899E5CA504EULL
        },
        {
            0x44E7336C8A37634AULL, 0x2564AB3577656C47ULL, 0x38FC7A62FEACEAB5ULL, 0x09B4C7B0DDCA06A2ULL, 
            0xD72E3C98D3473B85ULL, 0xF28D0AE2D52F509BULL, 0xD8D9DC74792AA947ULL, 0xBCA5F67A5A95413CULL, 
            0xCEAB444C5C45D059ULL, 0x2289D793792F3711ULL, 0x4B7F60AC6614DCB3ULL, 0x04BDCCFB4E1DE0A4ULL, 
            0x559DB703125B7831ULL, 0x71C05C4F8C2DB3E9ULL, 0x108F89B1F2E1624CULL, 0x98B068E792E97DF2ULL, 
            0x5C17E85394120BD9ULL, 0x4AFF24EA1D44B0BDULL, 0x573393F14FB1F5FCULL, 0x749D451C18D90A81ULL, 
            0xF5E94E0C61FFF106ULL, 0x07F77C6F15294424ULL, 0xBAD3B881B49CEB91ULL, 0x690578A93193CED4ULL, 
            0x7B3215321A7E70EBULL, 0x84381806735ACD18ULL, 0x0C25AFCD5EDC3644ULL, 0xAC4233C8F9D5A7EEULL, 
            0x348D77F73721990DULL, 0x979D1127DDB01BC9ULL, 0x89F64D0584C06557ULL, 0x7AD42910287B3781ULL
        },
        {
            0xF4DE984CABE325D3ULL, 0x3B0EF1844C007E8DULL, 0x6460D3514133901BULL, 0xB0B78486E7BE6B38ULL, 
            0xAFD1F1CA14EA0977ULL, 0xA47F6391B5A1BDE8ULL, 0xD7A524BD8F6182E8ULL, 0xD9CC37854CAE94BBULL, 
            0x1593739E31B8560FULL, 0x53A76847DA1AC072ULL, 0x8B18FB093508131CULL, 0x8A3884A7F7E2BFCAULL, 
            0x87C38CBA41C62E2FULL, 0x926A6CDF1C1C08FBULL, 0x4E87E5495F5BB225ULL, 0x87EB0FBE3F97643CULL, 
            0x719936BC08F340C9ULL, 0xFF11B5DD222FDFF5ULL, 0xE3A8D54D0E1FD830ULL, 0xD827425A38FD4D42ULL, 
            0x0889C0B2474BD9CDULL, 0x49E9351A0F09587DULL, 0x41E14AD1DBC72C74ULL, 0x47F51FDA84E7EF60ULL, 
            0xEAE5C4EDA5FAD1D6ULL, 0x05D852C2EC3C4E42ULL, 0x0E1DBA1140F4CEA6ULL, 0xB7B428295A3C762FULL, 
            0x9EA09C49B0325A74ULL, 0xC984CE6D25001CB4ULL, 0xB5442F71999FA7BCULL, 0x89B5E64EB23AAB40ULL
        },
        {
            0x36607CD618E644A4ULL, 0x6DE4A6896C20E745ULL, 0x25673CE64B17D45AULL, 0x1E792034771A86A8ULL, 
            0xC1B294A63DB58630ULL, 0x7923D36FC45D7D07ULL, 0x5D796D3EAB4B5D53ULL, 0xFF2B9142AB836533ULL, 
            0x2412FE795DABF7ECULL, 0xE298927CF2F3F987ULL, 0x7A89D51F3B942903ULL, 0xA3AA34160F091731ULL, 
            0x0E1452CA9E0077E0ULL, 0x7CE11C93B41951B3ULL, 0x6ED655AD927786DEULL, 0x790B3F41D772BC88ULL, 
            0x10A7C66D9FFB12EAULL, 0xA39ED459FD378149ULL, 0x73733312393E6C68ULL, 0xE62719A4E6F7D4A6ULL, 
            0x697F5749E5BA41A4ULL, 0x4750ECA7A2D6698AULL, 0xD76A7C1D8446BFC8ULL, 0x97C56319AFA4421AULL, 
            0x500F1726AA5A0E8DULL, 0x2E893AF0E000CD01ULL, 0xAE8D2087984B5963ULL, 0x486BA31B18ADE6A6ULL, 
            0xAE0CF8A22CFEA9E7ULL, 0xDBE5D80AEA5A24AFULL, 0x85797D026F8D3C0EULL, 0xBA380C548D1B861EULL
        },
        {
            0xA3835C107A0DB272ULL, 0x4EEA3577BC7501E1ULL, 0x418D829CDD457C93ULL, 0xC161823CBC065BECULL, 
            0x6CDB59A125BF2936ULL, 0x758D2F627498A00DULL, 0xE70D6F220FF3A397ULL, 0x91F273D0049D16DAULL, 
            0xA1A502B5F84A48C1ULL, 0xB3FD4B002819D2F5ULL, 0x779B37D6BC1E17EFULL, 0xD0657A18B20F584FULL, 
            0x60E98049AFBE6C73ULL, 0x17728899F0783D54ULL, 0x1091C9ABAE5B4D39ULL, 0xF60F866C2D8A7251ULL, 
            0x507F4B39B928EC09ULL, 0xF6B822B0732505E3ULL, 0x776B7E751CC2C5ACULL, 0x16E02DD1AAAC3264ULL, 
            0x013F182424B76DEDULL, 0x503EAD717EC543B8ULL, 0xA1119870DB33615BULL, 0xE65FF79B381D7617ULL, 
            0xDECA231ED6DA8439ULL, 0xB242D2011BCCF1D3ULL, 0x7AFDFA78A60D8099ULL, 0xDBAD7CDF151C986AULL, 
            0x52AA896340CE7E52ULL, 0xA7C4F9AA6DFA98EDULL, 0x6075A4026219B288ULL, 0xF5CA1D73AE6FAB46ULL
        }
    },
    {
        {
            0xD558637532B1EED2ULL, 0x4DFC3A6368DB109FULL, 0xD57B23B1233F7FFAULL, 0xD91D94BBF2360926ULL, 
            0x57B7ED55390A13EBULL, 0x277E531E860A084AULL, 0xA2154D22253D4FFCULL, 0xDC0270326149D00EULL, 
            0xB42004E16D270B6CULL, 0xCEEB80CB63768F40ULL, 0x284BAE19B99372BDULL, 0xFFB32F8ACCB126ACULL, 
            0x4A052ED8495A0982ULL, 0xE3314B3D7C4A089DULL, 0x7C3B71C42CEE1008ULL, 0xCA9EA1F260B52200ULL, 
            0x706C4046BA8D2037ULL, 0xEB72678C3C838C59ULL, 0x9E2DEAD06ACD2B1DULL, 0x5B7A04ED0DB8D5C0ULL, 
            0x85ACB21071EDBE49ULL, 0xBD435FF23CD62C85ULL, 0xF94D487ED0FEA253ULL, 0x812A05BDDA940F7CULL, 
            0xABEDEDC67F49520CULL, 0xD2DC81BE5AD14097ULL, 0xA5454CB5EC8E3A1CULL, 0x6B584F69AB284AEBULL, 
            0xEA34C26619000DD1ULL, 0x06B7247EB1303D55ULL, 0x7857F1B35D32DFECULL, 0xA9EA30C2D35FABC5ULL
        },
        {
            0x888B073206FA084FULL, 0x50F1A23CAB820DA0ULL, 0x9A08877285B448A6ULL, 0xF570DD1B4D4C3F6AULL, 
            0xB7C247BAA8EEE96CULL, 0xD4731663624B61CBULL, 0x7FC286CDCD7F43F2ULL, 0xE6F447C931B0AF88ULL, 
            0x0848DAB9D98E73ECULL, 0xEBE35E73B049C135ULL, 0x164A09006B18AB7CULL, 0xFD00EE4897193564ULL, 
            0x61C5E96E9385D8A7ULL, 0xD9006E0E5E936CF4ULL, 0x4165CD94FFC7DD3EULL, 0xD75F064F72E3EA51ULL, 
            0x1058A93AFED0177DULL, 0x83830A6804330320ULL, 0x8CC9AD0365D13F78ULL, 0x4EE017D20FBFD2F4ULL, 
            0xEAEA6E50A6BABB92ULL, 0xDD7ABAB6493A909AULL, 0xF0FE6C4C33729284ULL, 0xDE7BF80CED67FD5DULL, 
            0xF95D086ACD308DE3ULL, 0x34183F13ABB7E0C4ULL, 0x90A34B43A0E8468AULL, 0x06822B74A862CE06ULL, 
            0x5D4C1D820B43CADBULL, 0x9FEAE09E7F22C353ULL, 0x8BB26E3B301028D0ULL, 0xCEFD407FDB2E738AULL
        },
        {
            0xEEA30AD1466E9DF0ULL, 0xAC1EEE441F019D61ULL, 0x31657C218DB22EB7ULL, 0x7119C800EFE44A74ULL, 
            0xA0BD655DCAF7229EULL, 0x1751930488C691F8ULL, 0x1662AE98E544FFE0ULL, 0xF21C92EC0753C1D4ULL, 
            0x9F9CE9F002E5AA37ULL, 0xE0BFF03E63CA6C33ULL, 0xC978FC5B2A3A40C3ULL, 0xEA1D93869AC4EBDAULL, 
            0x65DEF6FB334A7AE0ULL, 0x4586A3EB6FE6DA8FULL, 0x0B1A8755DE4B53E8ULL, 0x502003CE2397F19AULL, 
            0xAB2CE5BAF4246166ULL, 0xDACAD097163495FEULL, 0x33A473A396750963ULL, 0x146F0A0DBB88624CULL, 
            0xDDF9B5F97192FB2AULL, 0x19EF6988D5BB7B05ULL, 0x683BE2CE658ABF49ULL, 0x62B9AEA434BCF58EULL, 
            0x7613964AB026828CULL, 0xF395AC00C3E62829ULL, 0x00B8E0FB20485FEEULL, 0xA05E5F02648ED52CULL, 
            0x60FFB8DDA8E8C58AULL, 0x6EFE774CBEEC9BDBULL, 0xE2F9D7DEAD3ECFB4ULL, 0x50E5156BA8E8BFEDULL
        },
        {
            0x0CE7CF36E22CEDA1ULL, 0x20525CF3A5E89685ULL, 0x68DE65CEE7266F40ULL, 0x163EDCA045854367ULL, 
            0xF7F76EEA63BB04DAULL, 0xADC59DF8314304A4ULL, 0x7F6BB95603E10AA5ULL, 0x18EB0CF699F64F2EULL, 
            0x67CED6BD64D4D410ULL, 0xE70CCBB0A7626EE8ULL, 0x984DE5ADDFD5E880ULL, 0xB2F4A60288D6D72EULL, 
            0xEF75C8339DC2DDCFULL, 0x5594D6FA3ED00EC6ULL, 0xB9C9AB40CE63E51FULL, 0x6F3C49F1D97249AAULL, 
            0xFC50498687E6BA5FULL, 0x57D0F2C11E2A21D7ULL, 0x2270BFCE7599A0F3ULL, 0x86D8335AA5D86ED8ULL, 
            0x644EFB0834B07C27ULL, 0xC95D1958692CBB72ULL, 0x9781E064C15292C9ULL, 0x4F9BB363FB79BB37ULL, 
            0x822847F63A5504DDULL, 0x69D8DB54F8FDE416ULL, 0x96E591491E8D1E23ULL, 0x34B58294C07DEAE3ULL, 
            0x09126377CDBF2A34ULL, 0xB9675727BDF87C2AULL, 0xECA0F1653EC79B2FULL, 0x4031E44AEC2BEE03ULL
        },
        {
            0xF0224F842C740462ULL, 0xA4C872371A9638DEULL, 0xB1A6ABB5F200F0DDULL, 0x1DD268518F997051ULL, 
            0x49421A927F19BDC6ULL, 0x4A4D99076841CA50ULL, 0x6ED07B6BD715DC81ULL, 0xEC7D016CB0BBDDF1ULL, 
            0xB58CCBA2708DC78DULL, 0x654F7648F254A4AEULL, 0xE01FF897BCE86178ULL, 0x0EF599EC916D74CAULL, 
            0x8BFB15A35752ED32ULL, 0x6A73A07273DADE09ULL, 0xE18E1D6E0D3EFF2AULL, 0xBA14190C3A58C005ULL, 
            0x9FCB9786956C5B4BULL, 0x63C56F0BA089BECDULL, 0x9FEFE9DDCE811BD8ULL, 0x5A55F6229A6AB3C3ULL, 
            0x45A467CEB45F95F7ULL, 0x084E9C8F344E0229ULL, 0x333BC35F82DE339AULL, 0x0A302C8DB7B85F82ULL, 
            0x8ED4980AA77A967FULL, 0x5139531E62A30ED9ULL, 0x17D407BB6EB4932BULL, 0x9D68E98EDF66B866ULL, 
            0xB94700ED2EA8A1DCULL, 0xFA343CAB6848B99EULL, 0xF49176FF6EB7A0DDULL, 0x3F3C3F735304860BULL
        },
        {
            0xE50D2BB5B4379D68ULL, 0x97511D8C01C2FA86ULL, 0x26F44A9A730A25EDULL, 0xA647EE0227B71551ULL, 
            0x11CEEC68C02552B1ULL, 0x2734FF2BCE4CE23CULL, 0x406B03D8DD201306ULL, 0x214D2144892DDFFEULL, 
            0x5F075CCF8E1ED6A5ULL, 0x5FF4E41A345F8AF8ULL, 0xA2C4EACFE3A956F6ULL, 0x8D0D93704A96410CULL, 
            0xA18F10330EBCD01DULL, 0xBF8CB3890FD6FFB5ULL, 0x4EADCAC60FD4E806ULL, 0x4C7AE2D01400B083ULL, 
            0x67756F65513E3F8BULL, 0x0646940D49B1236AULL, 0x5106762AB3F30868ULL, 0x0FAD62EFD2FE464DULL, 
            0xC11E5B33C60A9761ULL, 0x4ABF9C533EBA0A29ULL, 0x961A75CC49F23BBFULL, 0x6C86700838051577ULL, 
            0xDBE14D57F597884EULL, 0x9A051A174842E941ULL, 0x1DB6DA050DF0E2D3ULL, 0x974A8247E32ED594ULL, 
            0xAB7ADA69FA31E06DULL, 0xD3E0E40D2A2467D1ULL, 0xCF9B0C6A5CD8D1A5ULL, 0xF35B0CBD5AA41FD4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseFConstants = {
    0x6E0A9DBC0CC7AE21ULL,
    0x7F4566762B35CDF1ULL,
    0x554CAFE667471739ULL,
    0x6E0A9DBC0CC7AE21ULL,
    0x7F4566762B35CDF1ULL,
    0x554CAFE667471739ULL,
    0x36DB24C376448ADAULL,
    0x611F0B1F236AFEB5ULL,
    0x89,
    0xB0,
    0xCF,
    0xF0,
    0x21,
    0x23,
    0x66,
    0x33
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseGSalts = {
    {
        {
            0xB56AE38D7DBCDF66ULL, 0x82721363CCAEBD55ULL, 0xA579C48C129F1C91ULL, 0x28974A1BA437FF0BULL, 
            0xF5148176568D8F55ULL, 0x7255449EB53E88FAULL, 0xF76A956A1009ECECULL, 0x7ED47B95F8246095ULL, 
            0x5C66BC7438689A1BULL, 0xBAAEE050384EDF4EULL, 0x1BB8942FA031A36AULL, 0x6C061FFF6B98360DULL, 
            0x94043ECC3461D301ULL, 0x8843B6890AFD98F1ULL, 0xC6B570A8E4B98510ULL, 0x4FE30DED99F95744ULL, 
            0xC3553BDDD61854C9ULL, 0x5AE0DA0074DCD88CULL, 0x1F6EDEDDC576E2F8ULL, 0xAC6B80EA6D61E263ULL, 
            0xECD20E73845B5986ULL, 0x82052109C0075280ULL, 0x386BF33D9551CD66ULL, 0x473D0CA261C9738DULL, 
            0xC096E037EF14C3F2ULL, 0x927EBF9485AFF27FULL, 0x1D47BCA02549DC31ULL, 0x82A0FA812A2079D6ULL, 
            0xD0C39141DD84B8C5ULL, 0x9795089BE93DA83DULL, 0x90CA0AA4CEC0C04CULL, 0x6322D83A8F3BE9D1ULL
        },
        {
            0xC089E2083EB4BAD0ULL, 0x900939C6A6412ACDULL, 0xF0B56109446881A4ULL, 0xDAEBD5C0BC5FF594ULL, 
            0x4F0D3EC59C3F055CULL, 0x4246B03F29E8C9DCULL, 0x374D8E9D6799EBF8ULL, 0x6978774850EA6B95ULL, 
            0xEBE81493939EAEBBULL, 0x2FA1E75C45F8F09BULL, 0xEFD2B295AD5A588FULL, 0xF180C05C7FDBA3A9ULL, 
            0x7F2C0D46BD400145ULL, 0xD167CB50F5F18D45ULL, 0x58AF7C5421BF3B70ULL, 0x30A44B55DDF159EFULL, 
            0xCBDCA7BA70D33613ULL, 0x09E916D70120D731ULL, 0xBBBC2BB0836A1E84ULL, 0x3130D86F57C63D70ULL, 
            0x5E60E90365DD0709ULL, 0x32DB7ED8E2F788B6ULL, 0x1B7D078B84A423E3ULL, 0x336A35985340C931ULL, 
            0xE2C9DFB058F02BCFULL, 0x3C90EA136414B772ULL, 0x5F9C469449604CFFULL, 0x392917606045215FULL, 
            0xEA05061CB8CF1651ULL, 0x5CB14F49857036CAULL, 0x8BADDE26FA2CEBFFULL, 0xE1DB5AD9CE91FB8AULL
        },
        {
            0x7A393DD8A921C632ULL, 0x0B82A4020084F0B3ULL, 0x3B2C502B1AF8EE34ULL, 0xD54C5C64C8EC35A3ULL, 
            0x14533B1E81144802ULL, 0xA793031E38735AB4ULL, 0x5BE61C4BC515A6BDULL, 0x4900A3035CC67485ULL, 
            0x529D3D9F2FB34839ULL, 0x066AF5E42916569FULL, 0xC7952A808BF255B2ULL, 0x0B5BEB9584BA8CE0ULL, 
            0xEED2FA3A12FC822CULL, 0xBAC4D4FC1EE54EF5ULL, 0x016EDED0F5810367ULL, 0xE3E86E1AEF4610B8ULL, 
            0xD78E2E07B6435316ULL, 0x78C5FECB42BA266DULL, 0x5A9F059DA6BAF7E4ULL, 0x49D51FA44D66274BULL, 
            0x3486D5146C2BC62FULL, 0xCEF171D5FC047EB3ULL, 0xD83B8558ED93CAD7ULL, 0x2C5370DC17340005ULL, 
            0x6D15E9FB766F6BBDULL, 0xB9990BA20046E4B6ULL, 0xCDCCD3680D242AF1ULL, 0x09CFAC2769FA8E5CULL, 
            0x29F113AB4498714DULL, 0x7282D5AC68335A52ULL, 0x1BD150151F55C9ABULL, 0x51D90BFD71045A63ULL
        },
        {
            0x31F81A3D704BA6ECULL, 0x920514A26C64CF00ULL, 0xC3DB738FC17A52D5ULL, 0xA2C057243F77B161ULL, 
            0x8C76445772E4114CULL, 0x4334EB879C0A2831ULL, 0x131B7C3470A4FFD1ULL, 0x3D114F29F0EC0902ULL, 
            0x875B97D0619D5766ULL, 0xD6EA9EF306AFC464ULL, 0xD35F1A49BA46FCC6ULL, 0x466AF86C68EFE515ULL, 
            0x81E082B613A0568AULL, 0x2896F338CAAD51D8ULL, 0x7168E007F0A0E443ULL, 0x4989EC3B403CC482ULL, 
            0xB4E46232505C0CD3ULL, 0xEE33AB5019B32BCCULL, 0x74AA2BB9CE8B5A8CULL, 0x18CB13B8F0BAF11EULL, 
            0x7EC805DFF7450144ULL, 0xBB3AA0A229E7AC9EULL, 0xFC10FDD8F40E0DADULL, 0x6825B40E47C740F2ULL, 
            0x28F22091E341682AULL, 0xDF675113EE56CF31ULL, 0x20FFE299F0496B41ULL, 0xB3EC151407CFDB9CULL, 
            0x563D90CD097FB1F6ULL, 0xE6281E18B837390FULL, 0x9011F6E14BA1E485ULL, 0xEB76C9763134F2FFULL
        },
        {
            0xDD8ED801D1FF4474ULL, 0x2A9F9CF4B5597362ULL, 0xF14FE2474D68E5A8ULL, 0xCF108140EBCE758FULL, 
            0x6F7BECFBD48CF90BULL, 0x699BA1D189932878ULL, 0x65EC91CD85470FC6ULL, 0x2A387B259C092F37ULL, 
            0x6E2ADA4D4240CB14ULL, 0xE5C3D380C8F03FBFULL, 0x545AF6A6F8CFA197ULL, 0x4BBB42B6D685D065ULL, 
            0x5E91C688C0D7C226ULL, 0x1E7C34A44CE984F1ULL, 0xC35EAA37ABBD01F1ULL, 0xB9386C2CFDE53E74ULL, 
            0xFD16787535F0EB5BULL, 0x162C26009E843233ULL, 0xC12AC2882104DF6DULL, 0x7C88FCD52F802212ULL, 
            0xC2ABDFB10E98400CULL, 0x04991B971CBAD037ULL, 0x0F74523637174EB5ULL, 0xCF7811402933C827ULL, 
            0x3042E5528FE25F72ULL, 0x9A1CD93D291A4943ULL, 0xAFDF3F465125DB59ULL, 0x3007ED114D37B18DULL, 
            0xC967156C252CD277ULL, 0x76035CD12035AD00ULL, 0x9250AF4452A029E0ULL, 0x23AD9E8FB1388DB9ULL
        },
        {
            0xE5C8517BC4A78E25ULL, 0x712906FE542EB959ULL, 0x77DD87A82880BF2AULL, 0xDF712FFF6BAFC458ULL, 
            0x218E497897AC3D30ULL, 0xA56ABD832D61E83FULL, 0x34396A928B3CCFCBULL, 0x251FCBCBC7CEA044ULL, 
            0x0D94542776937238ULL, 0x5604C71FB41F0F2EULL, 0xD9E9A8DBFFE908E2ULL, 0xEE35A6C6849926A3ULL, 
            0x7E96D32F7F5FA62EULL, 0xA8E62B55073B787FULL, 0xEBDDCBFA12D0C3C0ULL, 0x22AD2E6B0362DC15ULL, 
            0x0F6F69B759F426DCULL, 0xE656BB3A0B68F3CDULL, 0x4ECFC78A7C61EFFFULL, 0xC15F6B5EB066D473ULL, 
            0xC9E8911576133E3EULL, 0x7473C5FD648C7CD2ULL, 0xAF8FBFB93EC5EB44ULL, 0xAF27DD14BFCC8758ULL, 
            0xDC8496E3AB9262B5ULL, 0x2C3F4E31400E6A27ULL, 0x0A2589FDF7FF943BULL, 0x71E3582BF1B5A144ULL, 
            0x643171338B9964F5ULL, 0x625C3C243F676F96ULL, 0x1AB1247421817BE5ULL, 0x4A4A02D14BFAFFCCULL
        }
    },
    {
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
            0xCEDB49F906C17ED3ULL, 0x1F1C2159C0213639ULL, 0x7FF586B7E8DE2ABDULL, 0x15B45BB5742C4806ULL, 
            0xE7798E7942677CB4ULL, 0xBC6A24E37610946DULL, 0x4BD131F832A7BEF4ULL, 0x07128CBDB578D7A1ULL, 
            0x9618B7D95CA75065ULL, 0x620BAB825A3C5D01ULL, 0x283CFB97C259D0CAULL, 0x75306CB8190C79BBULL, 
            0xC7222E7A34E8D8ACULL, 0xC132B529F345C7FBULL, 0x921365AAB35DFC3BULL, 0x3E6D86C656C51EA9ULL, 
            0x7BF24D85BBE30828ULL, 0x2162D0ED524C28C9ULL, 0xB5959102E777EFBAULL, 0x002B6111C636D3AEULL, 
            0x90DC0455170E7325ULL, 0xDC71EBD92887AFC7ULL, 0x602BD1FEC914A265ULL, 0xBBB1AC10C2BA0143ULL, 
            0x63481444F27F10C4ULL, 0x53AB9EBE5E84C2C9ULL, 0xB13465758E7A18C0ULL, 0xF0447C58B23EF4ABULL, 
            0x19341AAED5AE7D40ULL, 0x87AF85557FFC8C52ULL, 0x2676BF4C094B2C69ULL, 0x82142E6EAE926EC8ULL
        },
        {
            0x7F6507389748D512ULL, 0xCD8D02A65E168011ULL, 0x37ED79DEE414F7FFULL, 0x82BFEBA47D1B598AULL, 
            0xB0475C4D149970ECULL, 0x6920FFF444712B47ULL, 0x88A189CBEAA5C3FBULL, 0x4FFEF397006733BAULL, 
            0xA43E6F5940C516F4ULL, 0x856CC0A648A82E9FULL, 0x5E2C782494394D3DULL, 0xCABEBAAC63C392DDULL, 
            0x2F26B5D2CB04E3E3ULL, 0xDEF60A5E81BDCD02ULL, 0xD4789DAED9A4C332ULL, 0xD93FDAEC3446B916ULL, 
            0x6C287A1DF9A76428ULL, 0x9F77B0263AA4DADDULL, 0xEF06DBB49D7B8CCCULL, 0x207614ED408A0851ULL, 
            0x46D6CE9E5B53D001ULL, 0x46C56DC47C97A492ULL, 0x5DD94A95B2CE7538ULL, 0xF014D035258C93E4ULL, 
            0x6683F019B235C589ULL, 0x678E0E02CE715A77ULL, 0xD3F5A98E253606A2ULL, 0x1B165D4DEA111518ULL, 
            0x594F68C21A5D5C02ULL, 0x93CFA519505A69A4ULL, 0x1B88BA05BC355148ULL, 0x5E9D2100E60EEA8AULL
        },
        {
            0x4E49303A17FBC187ULL, 0x65FF16F8A4D996B9ULL, 0x289F28F37F625B42ULL, 0x1FBBF5BA8CA4AB03ULL, 
            0x2D24B9C1C35CB1ACULL, 0x688B916D81DC6CC7ULL, 0x25669E9635F99030ULL, 0xB3631E6692935650ULL, 
            0x6F144DFC1DE9A3DCULL, 0xA4461F105A91A7FDULL, 0x367BCD4913505DEEULL, 0xDD8FCC443972CC54ULL, 
            0x247A6ED04BD7E9EAULL, 0xF852A02A8105DE30ULL, 0x93BC156D7A48588EULL, 0xF5CE515116EE05EBULL, 
            0xBE8E9E1FA4A58D5EULL, 0x24C839D98740F43FULL, 0x825ADA706AA82573ULL, 0x8D505DB9BD60E562ULL, 
            0xF04EC84F2C8035BCULL, 0xCC6C6E1D59F3B192ULL, 0x3804C3A2352ABBF0ULL, 0x061BB68AC91479F6ULL, 
            0xB8E91E81677BF0C1ULL, 0xF231BFE55BBDBD51ULL, 0x6C6EE42074F87EE2ULL, 0xA6CCB118F7BA53CDULL, 
            0x9DF510B9471213F2ULL, 0x22BDC719A88FC009ULL, 0xE9F80FFAAC13DFE5ULL, 0xC0F373EA9542BDF7ULL
        },
        {
            0x2106553E88DBCABFULL, 0xF350CA8E21FF674CULL, 0x30234364A4E130A6ULL, 0x5A6C8A9502F42230ULL, 
            0x3C5CB68DD1865B6BULL, 0xDBC7B241B8ED57E5ULL, 0x843EF0DBBC30C057ULL, 0x6E1C4EF859111FD7ULL, 
            0x137A9A2E8F934B98ULL, 0x7E2156F6C9C1FB30ULL, 0xD96886EC4F4FB6DAULL, 0x7757991B6C603EE1ULL, 
            0x101B6DB48C47A402ULL, 0x50F91669DBDF8761ULL, 0xC42F7E5B635343F7ULL, 0x4114CA2A72AAF78EULL, 
            0xF88F755C07E94473ULL, 0x841659D67278DFE0ULL, 0x9377C1CDE1017E44ULL, 0x69826BA476CDBFC4ULL, 
            0x176C2EF55BF2869DULL, 0x2140ACDA3A1DC2A2ULL, 0x12D74C4F82B1A6CDULL, 0xE2DE19DF695F8601ULL, 
            0x9C4DCBA3303FE778ULL, 0x3E3DE4F4FBE39D05ULL, 0xC165DBC57347A4AFULL, 0x0D659DCBA41F5844ULL, 
            0xC47D5380C230E612ULL, 0x2D923B86BA176FDAULL, 0x5C59966D96D7AD03ULL, 0xCA819AC73640C584ULL
        },
        {
            0x6F96AEC4FC5522D6ULL, 0x4F4ABAB99F4832B3ULL, 0x1F306E9829137D26ULL, 0x2AC420E9F1E9A671ULL, 
            0x9CAA198D45101862ULL, 0xB734FEDC9FE2CB90ULL, 0x4E923457D36C2AA6ULL, 0xE59F848CE591DFC0ULL, 
            0x02D48C021DEAD2B8ULL, 0xC04CF71D31265D6AULL, 0x99940DE6D327CC46ULL, 0x42658C3E2E38BBFAULL, 
            0x7D4918F6F026AD3FULL, 0x224CB199CE1FC720ULL, 0xABEC56518DA404C1ULL, 0x3F5761FDE256F488ULL, 
            0x3432E200A4F1BED6ULL, 0xBE1217A0C93DD27BULL, 0xB5C44500D73E42DBULL, 0xB9E219B37B66C5AAULL, 
            0x4670852DDF0D093CULL, 0xAC135F2AD6DC799EULL, 0x13E2FD459AAF801FULL, 0x4FDFBF04EF94C0B6ULL, 
            0x2F90603586465CA5ULL, 0xA00F3B339DEC9B32ULL, 0x80A5C49E729845BDULL, 0xAF2523E0336B5AC6ULL, 
            0xEDF6306799C4BF5FULL, 0x4F4E489752F72D42ULL, 0x2304ACF54E54830DULL, 0x8D5AF31651880349ULL
        }
    },
    {
        {
            0x4CE6B7688325BE50ULL, 0x636F5A4DC60C41ABULL, 0x42D22AB9C50AF2E3ULL, 0x4E06FBE096B91B8EULL, 
            0x3DB0BAAB5A1D2CCEULL, 0xB5F35FF434949D0FULL, 0x5A50D80ADB4B65F3ULL, 0xD087912B8F14D895ULL, 
            0x96BEDB4CCC5CCAF6ULL, 0x0E1CCFFB60AD14C9ULL, 0x1FBA241FE623688FULL, 0x64C80DE26B9C4D95ULL, 
            0x1C1DE947739A6BBBULL, 0xC2B699D142E90317ULL, 0xB8BBE26875EBC424ULL, 0xEB5C2BF1FBD7A1F5ULL, 
            0xD29093D996CBFBE2ULL, 0xA3BAB7AEFDC48663ULL, 0xA3C13895FCDE4690ULL, 0xF45E8F6DDCC20CEAULL, 
            0x6294D3B5985C1CA3ULL, 0x210138559CC7DECBULL, 0x23E4D29503D49B7AULL, 0x8C216D85B5CDD05AULL, 
            0x132E41A2792C2687ULL, 0x2A3AC09E1448C1A8ULL, 0x184250A7BEB16214ULL, 0x5D17DE254689CEC0ULL, 
            0x978340353A1CBC09ULL, 0xDAC7B8AE68FE4D2DULL, 0xBEA8455C79487D36ULL, 0xA31CF542DBE0A784ULL
        },
        {
            0x5C257889F29870FBULL, 0xFA6040152A486686ULL, 0x2A54F5BB08C79555ULL, 0xAA0B509EDFDA32A6ULL, 
            0x4368D901B78F7EBBULL, 0xB585BEA9F49A6522ULL, 0x1F0C573176338CA4ULL, 0xEBE7419749B22AB9ULL, 
            0xD15A4C3AE89E17FEULL, 0x625A8A57C02B61C5ULL, 0x0228EC2B1FAC57DBULL, 0xFBF4B643A5D204B8ULL, 
            0xEC251F29B247545EULL, 0xAD99A16688F8AFA1ULL, 0x7928F62D0955D554ULL, 0x5E000B60306A0BB9ULL, 
            0xE5C27C2EC9803249ULL, 0x6E95DC9887DDDE39ULL, 0xD31CFA8F475538FFULL, 0x281BF8D8A1191D25ULL, 
            0xA586BDC6F7D679B0ULL, 0xF935A1A43D56CD74ULL, 0xC0F80ABD9BC60C2AULL, 0xBBC1057AE6970D73ULL, 
            0x7E2466E0B4AEC582ULL, 0xD615646BEE0B23DBULL, 0xCB4FE8D0BD6948DDULL, 0xBBEE24D0E5B5A9A4ULL, 
            0x1C9D9D94C4A8C086ULL, 0x41918A47F4AC28A1ULL, 0xC077C0955C04FCC7ULL, 0xD6B4091AA8D63F6BULL
        },
        {
            0x363346EA4927AEF3ULL, 0x6FBBB98B513ABD1EULL, 0xDAD01602364201F8ULL, 0x96FC096456DD7F40ULL, 
            0x9FF4A1FC02FBB4F3ULL, 0x3EDB76F80F2108D6ULL, 0xCDDCDA5EF7DC81EFULL, 0x6C1028FD35BD2AFAULL, 
            0x446CC54BA1AE1A2EULL, 0x7B28276F78B8B89FULL, 0xEE24A095A2E8FC0EULL, 0xE711F993ECAFC58CULL, 
            0xF97E28C73659732AULL, 0x766371E145034B15ULL, 0x37705C9A4E5B207EULL, 0xBA32F2B16C8D9A4EULL, 
            0x44AEA8C9DA31B404ULL, 0xEADFCEFCBCE08059ULL, 0xFB1271D6FC0DC524ULL, 0xDF7E0F27B28DB560ULL, 
            0xD5469E2F43E67A9AULL, 0x5038BB372D430161ULL, 0xA8982E8EC6F0C15EULL, 0x79FC8A2BA75249CEULL, 
            0x71E1B3410501726EULL, 0x646CE47A68636EF9ULL, 0x645E71F8FC9316EEULL, 0x5B7CFB8EB6F6D172ULL, 
            0x09D060461E88847AULL, 0xC1A4D8537AC0671CULL, 0x905B7C6866F7FE89ULL, 0xBB960E9D4FBBBB93ULL
        },
        {
            0xD7F7AA481C178374ULL, 0x4DA2A9E83520B929ULL, 0xC1CFC7C338DF53EEULL, 0x37ADD4FD11018181ULL, 
            0x9380465CA1003A0FULL, 0x60E83FC9545211B5ULL, 0x1084550054F6107CULL, 0xB5E8CBBB28412928ULL, 
            0x7CF27AAD3BA4869FULL, 0x6C39BB84D78A0D55ULL, 0xF98AA4B3E88A2147ULL, 0x2AA4DAB5E434ECA1ULL, 
            0x3A6F5B7751B676A9ULL, 0x8F671625FA09845CULL, 0xA8B8988CCB33E155ULL, 0x40D121DD4047E66BULL, 
            0x911B119A4208630BULL, 0x37ED2D7FC6E19923ULL, 0x8AB236165527640BULL, 0x6B1B31C7BB2918CFULL, 
            0x3A2B2A614969F6DFULL, 0x278BDB02A1D9E4BDULL, 0x184882C3DA8B4E35ULL, 0x4C9B16B4EADE024EULL, 
            0xA41B18C16D0D0108ULL, 0xAE1F396454D24ADDULL, 0xBBD7A92012CE91CBULL, 0x25D0CB7F89D94DBBULL, 
            0x63505E43C47DE98DULL, 0xE7561438BA7793E8ULL, 0xBB786E269611DC1CULL, 0x6EC0AD0F7CF979F9ULL
        },
        {
            0x4BC3AAA6339EE848ULL, 0x4AC808EAACA9E38BULL, 0x50ABAEF109E132AFULL, 0x3C9481BBE37560A1ULL, 
            0x6684F77A14474F71ULL, 0x00661A292EF05931ULL, 0x8ACECF0F9028F30EULL, 0xEB15A8FD0C1E4BECULL, 
            0xB4C65F18AF62F0BDULL, 0xE7DEFB5BA55BCDDAULL, 0x7832C54E786ACB9BULL, 0x8C882F46CCA0C908ULL, 
            0xF115893E62CD06BAULL, 0xDAD43E9B8360D12BULL, 0x09B11C5B5D064FE7ULL, 0xF542C61868114129ULL, 
            0x0978DCBB75380EAEULL, 0x913B257BC1379F97ULL, 0x57330575A2B021E7ULL, 0xB952935B49672993ULL, 
            0xFDEEF12B56B89D25ULL, 0x69EDFAB8DED32838ULL, 0x4D802B203DF5FF76ULL, 0xB4A771A74ED0AECDULL, 
            0x50A6DC91926B444DULL, 0xAB789C6D6C6044A8ULL, 0x7FE2AA3C1A58E076ULL, 0x54EDDFAD12493124ULL, 
            0x1707AA6FE0A126E4ULL, 0xF0DC0FC030FD8466ULL, 0xF9CEE36EF6063395ULL, 0x8FB9588A888C5535ULL
        },
        {
            0xDD36DB459F29857DULL, 0xF65D671EBA00BAB0ULL, 0x9717A00A1D808213ULL, 0xF268D8C82EF81F38ULL, 
            0x9A5DB9105C815C19ULL, 0x97972C7E11C32895ULL, 0xFF6E84F840863DA5ULL, 0xB1F619395A94D0E0ULL, 
            0x2DDF5EB32010A249ULL, 0x1558B55495E56B7DULL, 0x91387E2FD4385817ULL, 0xD60030F4874DE21CULL, 
            0x45E04C819DB481DDULL, 0x03E47B2A7A4DCCD8ULL, 0x9587F715C3AB1680ULL, 0x851DFE083B5DFA80ULL, 
            0xFB570B04B47E0A4CULL, 0xC5602E2029EF94C1ULL, 0x98538EA4C2B53188ULL, 0x8F8FA4CD7C9B4ECCULL, 
            0x468B9BB85862503BULL, 0xECB961051B10F670ULL, 0xB2211EA768A8EF37ULL, 0xA1331A0CE386FDF6ULL, 
            0x55488263224DB6E0ULL, 0xE0C43389195E1062ULL, 0xF5B7BC3A93E800DEULL, 0xE12FD8964B406249ULL, 
            0x40E28E0AAD6ED7F8ULL, 0x384003EE18FCB4D9ULL, 0xF626FABA339921F4ULL, 0xF4D60376BE9A88F8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseGConstants = {
    0xBCE1B3FDE3D4261CULL,
    0x07EC4D1409D459A7ULL,
    0xC46DBF0D3D1D1A42ULL,
    0xBCE1B3FDE3D4261CULL,
    0x07EC4D1409D459A7ULL,
    0xC46DBF0D3D1D1A42ULL,
    0x5AB46EC71DCBC48FULL,
    0xBFA62EB1B3313008ULL,
    0x65,
    0xCF,
    0xC4,
    0x95,
    0xEA,
    0x1C,
    0xC2,
    0x6A
};

const TwistDomainSaltSet TwistExpander_Procyon::kPhaseHSalts = {
    {
        {
            0x35A84F23F0FF32E1ULL, 0x994CEA49CBE1249FULL, 0xABD01DE713700BC7ULL, 0xA3323C981F2F686FULL, 
            0x0D4F76339D89CE1CULL, 0x853FCD1F52AAB424ULL, 0x49D3E17E42D9D9E8ULL, 0xE0F98BA3F29CCC34ULL, 
            0xE776AE0FED1710AEULL, 0x71C2F69F7014E418ULL, 0xEF184146D77D8A90ULL, 0x643702D06859B215ULL, 
            0x79D0F1C02BA3AFAAULL, 0x6FFE2CE17949318EULL, 0xA5272D7DF0752644ULL, 0xE2C674209326F4C8ULL, 
            0x8C0C7AA59C0F15E8ULL, 0x95C81A722FFD543BULL, 0xD3FAF0FA2A3E067AULL, 0x074A65578015CDEAULL, 
            0x01741CE0D047F559ULL, 0x635F60D0B6F6DC25ULL, 0x709017170E79C26DULL, 0x882CEDF6068316FDULL, 
            0xC9A8054405A04EB2ULL, 0x89910F7B63F1BE3FULL, 0x14169F0763F74158ULL, 0x6EB2A1535B16F966ULL, 
            0x727AB01F6297A8B6ULL, 0x0F0B67943CD7DA4AULL, 0xEBB04CF1ACE8A29BULL, 0x649D26C4303EDE37ULL
        },
        {
            0x193039334FCC6F96ULL, 0x7A0D80A0DD74650CULL, 0x9B545A06D03E1C55ULL, 0xC2CBEE3D9DF05FBAULL, 
            0xB2C38000B2062D8FULL, 0xF7DD7E47D9D4DCF0ULL, 0xBE39585F1A85EB73ULL, 0x2FB3FEA3C2FD434DULL, 
            0x3DCE1108D7B66D07ULL, 0x4E18F8A11C43E71CULL, 0xC9E95597092A8644ULL, 0x739B5170D9435FE6ULL, 
            0x74873BA78020B304ULL, 0x6BF5CD1FAAFF7292ULL, 0x1A816D43A5326C0EULL, 0x6A0DEB3900355CB5ULL, 
            0x288F219E8A78BF88ULL, 0x6CF991FE2CBEF7FDULL, 0x19EC3C88EDE9EEC2ULL, 0x0EDE7468F3A29882ULL, 
            0x940E547F5BF5BAEDULL, 0x798364BC1E0E71DBULL, 0x5498ED3BECE825B1ULL, 0x0DDCE5C695D84629ULL, 
            0x0C8E947C5179D5D3ULL, 0x84AE5AA349243778ULL, 0xDEC2EB4F1714BAA1ULL, 0x456F6B8707B011ACULL, 
            0x6E759E7987E84FC4ULL, 0xBBAB99DC5C6C8ED6ULL, 0x9F0E9425E47934C9ULL, 0x5EA113D578EA7E8FULL
        },
        {
            0x12DCC7471564D0DDULL, 0x051D13A6563F4138ULL, 0xE457B2CBD8EDF741ULL, 0x03CF74B9A145CC2FULL, 
            0x78F989A89062F67AULL, 0xDF138D1273DFFDF5ULL, 0x5DA8A9D0BD1FF4A3ULL, 0x2A68D572F4067E9EULL, 
            0xCBE548710CC3E0F0ULL, 0xE8F3B91D07D80E14ULL, 0x7A9CD33E92AFA43CULL, 0xACEB4E74057E4D84ULL, 
            0xE3C207B0770BC6C5ULL, 0x2B8762A0DC3DFB0FULL, 0x74CF97A48A0E1F47ULL, 0x0EB433A3E9F2C3F4ULL, 
            0xEC031F30CF97A894ULL, 0xBC02D33127110061ULL, 0x072118A51551D60DULL, 0xEE22B743238E4F3DULL, 
            0xF06E136FE0646D1BULL, 0x7AD9BDD38336C281ULL, 0xCFDDF054E92A7490ULL, 0xB2A7C6463493FED4ULL, 
            0x4FB55D0A80B4B15EULL, 0xB98EB8CB6269FC6AULL, 0xE3D8F0BC8B084E2DULL, 0xEDF6757EF36C42C7ULL, 
            0xE1A30057DBF6D133ULL, 0xEBE679CFE342D333ULL, 0xF0216E10891BFCA0ULL, 0xA56D8DB99D28C3D2ULL
        },
        {
            0x84160555BCAD80F2ULL, 0xB706F4B760A83D32ULL, 0x78F2D0318586F4A5ULL, 0x90607EF4DAE56316ULL, 
            0xD05254BD2508D504ULL, 0x314322CC1FAF49ECULL, 0x030CB2A845CC607BULL, 0x132BC0F30CE99F4CULL, 
            0x8A4E1967B6FF91C3ULL, 0xECB9D86C795BBD6EULL, 0xDA3D7E0FD7F19F21ULL, 0xA55C74948DAF03DBULL, 
            0xDC5A623373EE780CULL, 0x865A650FEE55DCEFULL, 0x11876F4CF374F040ULL, 0xB822FD8439ADADB8ULL, 
            0x8033B39C9CF466F5ULL, 0x2814215FF240F0E1ULL, 0xA7DAA59DE2C53837ULL, 0xADE296400792377DULL, 
            0x0E55A4C1DF766069ULL, 0x2EEE218C37F7791DULL, 0x762658F7B04CEBF0ULL, 0x358DF7C2E99EC694ULL, 
            0x73A5D87B35A0F1F7ULL, 0x73691D8F6C31F1D4ULL, 0x5764EE3B3D58E3DBULL, 0x51BAA5A76BA1666BULL, 
            0x72C8816FA35B54D3ULL, 0xE126AE316FF54CDEULL, 0xBEA3FD508DA5CF71ULL, 0xF4C5798B97A8EDDFULL
        },
        {
            0x578FDB15C2DBE654ULL, 0x5152F9432A38E5B7ULL, 0x11FC00A022979A24ULL, 0x487C33571D074F7BULL, 
            0xE6CC015A337CAA3EULL, 0xCCF7C3DB5FF69FF0ULL, 0x159BAECDAF98ED35ULL, 0xF9F428BB647BD19BULL, 
            0x8B8733764DC39B91ULL, 0x9A3C1BF3CB60FBCFULL, 0x609BFD877D8A534CULL, 0xC61A57C591BC8FF4ULL, 
            0xACE02B7763734337ULL, 0x83F31BA65B85A740ULL, 0xC3E8C64D375E8951ULL, 0xA021D89D9911E724ULL, 
            0xD9FD7B079A789257ULL, 0xF2BE23FEF3DA443AULL, 0x46091DE59F262FACULL, 0xE2D0A9302DE3FAB1ULL, 
            0x36A031662A368511ULL, 0xDF2731706CAB0305ULL, 0x1C3888942C30107BULL, 0xD11C8A02B8ECAB68ULL, 
            0xE4D10D1C4823C9F2ULL, 0xC458AA7684D871CEULL, 0xF97213C2055493B3ULL, 0x9261E2A0EB1AAE75ULL, 
            0xA8A990ED0A39463BULL, 0xE10CC36D957740D2ULL, 0x6E0C913015C3E134ULL, 0xCF1E0937BBAD8C05ULL
        },
        {
            0x9FD5FC019B0E7B71ULL, 0xFDC10AB612889E17ULL, 0xE9C41A72C0B663BDULL, 0x4E670364A8945139ULL, 
            0xD32AEDCAD26B8A49ULL, 0x58EA459D97368D85ULL, 0x3D3E6C9B0D9B0931ULL, 0xE8BAEBC082268A88ULL, 
            0x362FCB1F26E67EEAULL, 0xD52611DA25893349ULL, 0x4C297FE0254B1ED9ULL, 0xCDD9AAB8622CA6C1ULL, 
            0x329CF963D56A0F13ULL, 0x9768716A901BB9ACULL, 0x24981D0692A552B3ULL, 0x63C1DD0908901DDBULL, 
            0xDDBFF4DBE455ADF4ULL, 0x76B1683A0005CC9DULL, 0xD1E293D94833AB68ULL, 0x615F5DCC611A5DA9ULL, 
            0xFE7F902E70737884ULL, 0x1C6E3F60522A63BCULL, 0x01DEF0E9E7A78DEFULL, 0x49D556F5537CD794ULL, 
            0xAE81A6F5333A5C51ULL, 0x6B6B11A022A262C2ULL, 0x80E6EF586387FD7BULL, 0x09FDE626C27BF019ULL, 
            0x8891224FD7D20997ULL, 0xF822CEBF06368CE3ULL, 0xDB6FACF184F4536CULL, 0xB78E16A11012E34BULL
        }
    },
    {
        {
            0x77D30FFFE9C28FD1ULL, 0x387B2D9D0BE66296ULL, 0xCB22F095C68DA629ULL, 0x6CD7C8F7B2AEEC4FULL, 
            0x52D3EA8F47B6C07FULL, 0x3968C2FC20FE1A45ULL, 0xF2D547B4E937B37BULL, 0x983F4DB6EEA28557ULL, 
            0x3D487CFD6F08D5DBULL, 0x3C291E0208BD9546ULL, 0xE1E1D61422CE5646ULL, 0x3E7AD9C6DBF980D3ULL, 
            0x78DDB4F9516CE4DDULL, 0x82D7A6CCF36113A9ULL, 0xA32D82520C1FDEA5ULL, 0xA39F726FBFBE53D7ULL, 
            0xDAD9A1A636550D8BULL, 0x771BF854AC2A66DFULL, 0xCE5C171AB00EFCF0ULL, 0xA32C7D616ACF4EB0ULL, 
            0xE574505CF379CF33ULL, 0x3E97AE823E3531D6ULL, 0xAC30FF2AFC0E5D03ULL, 0xE059E22BE9990415ULL, 
            0xCC94AD7AD9C5B1ADULL, 0x2B1C0577AF2BE840ULL, 0x4A136B32F889DA82ULL, 0xC648E3616B969CFFULL, 
            0x8F2B5D6CAFCC4447ULL, 0xA32E2E99453F5413ULL, 0xACBD1A516E6045D6ULL, 0xEF8A0DF3061385F0ULL
        },
        {
            0xDCF5C3A3E71478B2ULL, 0x75947899ACEE5621ULL, 0x64D1C6852D5C7F16ULL, 0xC3A406204682EC5AULL, 
            0x10DAFBF8FFB3B4DCULL, 0xD336ED116B280FA1ULL, 0xDBEADCFDD7D20F56ULL, 0xB1CB83FC2C9D5AE2ULL, 
            0xBF1E7B621D757B8DULL, 0x6A4DF615E5488710ULL, 0x025909A852C198F9ULL, 0xD2AA5924FCF3512AULL, 
            0x9B4512E364687A31ULL, 0x13A98FF3B8B81667ULL, 0xBAC7D1FE4EA6BADDULL, 0x2D5A7F50DC6EE3C7ULL, 
            0x90A88F5FBB61BDBFULL, 0x99AEFFA0C14C449DULL, 0xE7E71F32193FE933ULL, 0xF5C122FEF1063576ULL, 
            0xA1830D85F43F5251ULL, 0xD2E1F0BDA59549A9ULL, 0x8E6DEF6472F14A5EULL, 0xE80A5166A005345DULL, 
            0xC67251549804FBA2ULL, 0x7901AE41B83CB1ABULL, 0x01A97FB1EFD9F17CULL, 0x54B36724E9F6E2D5ULL, 
            0xDE843303203FB2A2ULL, 0xEE4788027E2E7EF5ULL, 0x4AD5100909D6F27EULL, 0x0C4E00186B100CD4ULL
        },
        {
            0x5F9F8EAC4B8E6566ULL, 0x88D8124731CBC8DEULL, 0x65B1A4E5DA64B49EULL, 0x683C198794728CEFULL, 
            0x7D5231513540759EULL, 0xF9F3C7CCF25CCE08ULL, 0xC362E328138DDE39ULL, 0xAA269D29F5F147B2ULL, 
            0x213BC99A1085EC5AULL, 0x8494BFB6E65C88DFULL, 0xE24E53E4FDF7893AULL, 0x61D5A5F6F3502150ULL, 
            0xF9F251C08F738C30ULL, 0x3F6438ED9B86BC31ULL, 0xF60DD8A5370A6D44ULL, 0xD0868D1FDB7B7971ULL, 
            0x46367753C666886DULL, 0x10F419A252C132CEULL, 0xA8383082730CE5D0ULL, 0x31352876F4531E2BULL, 
            0x7157BA73E872E394ULL, 0x25AF079C10909CE7ULL, 0xC6D13959386F45D9ULL, 0x219F8ACE9358EEB3ULL, 
            0x540049ECCDEA195EULL, 0xD72179B81B16F6FAULL, 0x9D89A8B60C3DC84CULL, 0x9D66A7F631704824ULL, 
            0xDA896BC19F65913BULL, 0xA2EEA3B4636E988BULL, 0x3B82D25BE4064977ULL, 0xEF41AC2B8B22616FULL
        },
        {
            0xF7AA45D1B6B00FC9ULL, 0x91EFA70E267F4C6EULL, 0x29C0F99F6EAC4C72ULL, 0x97D0EBFF00692765ULL, 
            0x6488795964773A5CULL, 0xF6B270E572318A13ULL, 0x8BAD2F811C54DE72ULL, 0xDABADF0CE6A0C657ULL, 
            0x0974798C913EFC06ULL, 0x76C96FEB9FDFBB6DULL, 0xFCC7544055DDF0D7ULL, 0x5E601A7C750742F3ULL, 
            0x96351E64DAB0A55CULL, 0xE1CCBCBDEF74267FULL, 0x387C461CEDE543B8ULL, 0xF0809D6C3EB3514EULL, 
            0xA37DABB77802B29FULL, 0x7BA6C705BD872DB9ULL, 0xB98A9922A99605F8ULL, 0xD59F846FBB4D4C3FULL, 
            0x570984678344F137ULL, 0x5281F0488AF1421CULL, 0x922A5C7C40A17F1FULL, 0xCCF5DB4ECB6AD73BULL, 
            0x573FB38E5E829397ULL, 0x0CD9F64EC9D9D769ULL, 0xE86B69BBFB3DC508ULL, 0x29732EC5928353B2ULL, 
            0x9B3E33B7C3817326ULL, 0x5CF3E1D190D18966ULL, 0x11B5C59456E99440ULL, 0xF5799E1B6E0CD9ABULL
        },
        {
            0x9DC5A1B9E7E4CD57ULL, 0x7D566060D7640A13ULL, 0x0589D8B1E8FC13C9ULL, 0x1F3FEA9D5A30E5F8ULL, 
            0x1DA7F6769174DEF6ULL, 0xEBF2D6EF2DD366DBULL, 0xF4A3CF2981F128EAULL, 0x405374AD80769516ULL, 
            0x3EB6C896FBF99C47ULL, 0x1CE166A69AF8182AULL, 0x7154731999F73581ULL, 0xA93E4C591AF3B6FAULL, 
            0x3CD617711BEEA4C0ULL, 0x3BF9B158C965B7D9ULL, 0x8CB184CCE8BDDF24ULL, 0xEF20CFF86E2172ADULL, 
            0x550A2F1704B875F4ULL, 0x9D9522B8596A276CULL, 0xE4033AB8F3B07F0EULL, 0xC0FBABF907FD8235ULL, 
            0x2966A279CC1EE1A1ULL, 0x308AA42D49FF0274ULL, 0x83AB34FD89AB57E0ULL, 0xD06060C672B7E999ULL, 
            0xC4474D0E91360A2AULL, 0x82A5D8F9DD9BB454ULL, 0x5937B44409803C4BULL, 0xFE7EB9462F7D29ABULL, 
            0x0805F07222060899ULL, 0xF2BB94317FF99A78ULL, 0x089A2E9BF9544882ULL, 0x23DBA0464C4EC20FULL
        },
        {
            0x44AE2D0FB4F833C8ULL, 0x0B11B0CE7904BE56ULL, 0x6011353B4F61636EULL, 0xAE547195DBC9D753ULL, 
            0x5D35228F1A880EA3ULL, 0x3D2775FF3A010BC9ULL, 0xC25585CAA2E0D1F7ULL, 0xF4390A28C0C68984ULL, 
            0x84599EEBCEB186D6ULL, 0xA5AD6D0013996C1DULL, 0x7C9B7F587D271CE0ULL, 0x43E06D8399F04AB5ULL, 
            0x5E2871168A19B088ULL, 0xD69FDD5D06728B56ULL, 0xA5EEB26346DC736CULL, 0x579891D789252DE8ULL, 
            0x62D2ECCFED065CFAULL, 0x7E995B0E965CA3D2ULL, 0x476DDA674F36A340ULL, 0xA284469A20225CD9ULL, 
            0x30712FE9026CD020ULL, 0x139A83DBB55A3ED4ULL, 0x4F9A273980825A7CULL, 0x3E0C5E1E2BCAAF54ULL, 
            0x6A7ED9F007DAE279ULL, 0x79F9775AC29D347DULL, 0x79223F14EF9964CDULL, 0x9D1D3F88A05C09D9ULL, 
            0xD3C3990426CABFD5ULL, 0xC7DD1224C8268EAAULL, 0x8E48E3C18D883729ULL, 0x9E92429265D8DA6BULL
        }
    },
    {
        {
            0x276ECC24F9B9C45DULL, 0xEB219748644109DEULL, 0x7798F7895EEDBF0EULL, 0xC711CC7665DCACB5ULL, 
            0xE5A42B6108478A5BULL, 0x01738D05A7225947ULL, 0xC1E1C9A420E9DA2FULL, 0x75093BD7C44377AAULL, 
            0x4498EA12443E00EDULL, 0xCBDF627FB0FF5DCDULL, 0x63C698121F7F30FBULL, 0xCEF974C8EDDBFCA2ULL, 
            0x8EFE19EDA7959186ULL, 0x1796A216918B1365ULL, 0x71C92F93A9CCB28CULL, 0xFECDE45F214D28F8ULL, 
            0x90126710D28346A0ULL, 0x804D5EF288F9EEB9ULL, 0x3918D6CB10099DA9ULL, 0x3271ADDB765B6882ULL, 
            0x5299A1FDE78B5C1BULL, 0x10EDE7E03ACFC035ULL, 0x9907A77FC525B5E4ULL, 0x22E4F13274775169ULL, 
            0xDA49CD750337F9BCULL, 0x9B2FE9A7286E875EULL, 0x69C100BA14D7B371ULL, 0xD883571E9EFEA725ULL, 
            0x534C844D04F0AC50ULL, 0xD4FAFA1E796B3512ULL, 0x6970FFBB41D0C32FULL, 0x37BD2552F5398A8DULL
        },
        {
            0x356D54CA9A1A4E4EULL, 0x0FFD4945064D479AULL, 0x08D6ACBF80860945ULL, 0x7E8FEAAAB1B71E43ULL, 
            0x8A7DE3ECF8D0391AULL, 0x0CF3824B3101F6F1ULL, 0x8CA79F68356C188AULL, 0x9C3E111A5E58DA25ULL, 
            0xA52EC296153F3CDEULL, 0x5AC361D7EB77284CULL, 0xCEBBB6E2CF40C233ULL, 0x22AD0376D1B17040ULL, 
            0xCB5DE3291A494428ULL, 0xECB62FB0059B272CULL, 0x1B1F39EC5557D1C6ULL, 0x1EF7BDF2C07799D5ULL, 
            0x7D8CC3A833E66548ULL, 0x5301E285DEAD00E0ULL, 0xBC853517E17EBB6FULL, 0x231AB7670A4E0DC3ULL, 
            0xBA270013CAF08CD3ULL, 0x526128D1C501442DULL, 0xA1DB0031FF32D8BCULL, 0x3AB5B73231765B05ULL, 
            0xC59894E24C7DC872ULL, 0x731E18DC7F5C3BEEULL, 0x23FBCCC813B6AD2CULL, 0x4DB9538352F3FA6CULL, 
            0x2570326AC5C9319EULL, 0xDA757A4EF69FFF1AULL, 0x49B9FCFB242672F7ULL, 0xF5BA97A29F786346ULL
        },
        {
            0x843547CE4AB922F5ULL, 0xB09EA0E2589074CEULL, 0xA1964E11C525F9D1ULL, 0xC55F6329111389ACULL, 
            0x9F97B740EDBD07BBULL, 0x05FAE58176B197C7ULL, 0x08606BD1D8B7E46DULL, 0xD542F5EEBA5C0C92ULL, 
            0x5D6F1F636A699350ULL, 0x48E0F9D6E5C6EFD9ULL, 0x2988070F0D2F9031ULL, 0x7D4D27874E36A4CDULL, 
            0xDD6CB147706170E2ULL, 0x24F9BB773AE0B9C6ULL, 0x95587C59B956A35FULL, 0x3037F2DCDF572F4AULL, 
            0xCC01A71ADCF14CADULL, 0x760AB939B5416FECULL, 0xF4437C7262737967ULL, 0x49613948752C27DAULL, 
            0x807EAAB0F2B37F04ULL, 0x721606F7081E9497ULL, 0xBB0265B24AB46F1DULL, 0xA45B650A91690ED4ULL, 
            0x08440ACDC532D838ULL, 0xA8889699C4404E8BULL, 0xD90C8EC41DE322FEULL, 0x6F3DB79E0A1ADFC4ULL, 
            0xA5576AC45E761652ULL, 0xD825459723277E23ULL, 0x913CFFBEF4206086ULL, 0xD960FFAB3C9B3908ULL
        },
        {
            0x0A364B57E280E2BDULL, 0xE8E6CF6D2DA9B0DCULL, 0x20370C7406C19D80ULL, 0xAF9E80D7753E034AULL, 
            0x91E6F70BB9A96DE2ULL, 0xA38BE49E7BBE5C0BULL, 0xC5D1DDACC970933CULL, 0xE97E41A4F007B2C1ULL, 
            0xDF4BABA1C237DC6FULL, 0xADD7ED1D70D6722FULL, 0xEE3BE9FA165216F6ULL, 0xF12D7D9B4ADE5748ULL, 
            0xEE8614BAE5503716ULL, 0xB44B9C805E885D8BULL, 0xC1C67D2BADB9180AULL, 0x2915F636A3ABB424ULL, 
            0x760E283497725955ULL, 0x24B14797A0FAE0A1ULL, 0x44CA10F2DB25BF0AULL, 0x72D68DCBCA9AA530ULL, 
            0xAF458D02DE01E7A3ULL, 0x550E03769470641DULL, 0x9247C18E668F6C67ULL, 0xA99C309EFBDB63DAULL, 
            0xFCD28CCBC21BC94EULL, 0x46ADA5BC1CA7DA25ULL, 0x480C707F84203FAEULL, 0x416332C8E3D93271ULL, 
            0xF7543F65CC1FB2ABULL, 0x07B6E40A6DF96D4FULL, 0x738CB2326222B3B1ULL, 0x626B3FFCD782B646ULL
        },
        {
            0xC8926880E6640F59ULL, 0x8935187579E4C05DULL, 0x4F051E428B39AD97ULL, 0xE23B8FE508CF2F62ULL, 
            0x165CD8960DAE5351ULL, 0xEE2007C2CD8DD1CBULL, 0xE54069A0744A0CC1ULL, 0xC000B110051BDDBFULL, 
            0xD28EAD34A0E2D89AULL, 0xFD0DBEC5ABDE5B5AULL, 0x5F5702CC3E331F0AULL, 0xB51EC390F4E3CEC8ULL, 
            0x9F4F2E23798A94C9ULL, 0x7143E6757AFF8517ULL, 0xA6EF11B9F6CC63EBULL, 0x2739767DA1D11B1DULL, 
            0xCE8749F4165BCDC7ULL, 0x307289C69206328FULL, 0x226A70C79922B0B7ULL, 0x9DDA21383C40322DULL, 
            0xE6C3CE8090E6D951ULL, 0x429B9CFCC1585023ULL, 0x82DC58F26FE1A9D7ULL, 0x9B73915A69245A27ULL, 
            0x378A9F3FCB0A1A32ULL, 0x5DA636DB2CDE5749ULL, 0xE5F433D55D241615ULL, 0xB329ECF73405AAF0ULL, 
            0x171AAAC06F0C6008ULL, 0x10D4057DFAC623EEULL, 0x051A73766259CBA1ULL, 0x0DAE8E3B5C1F67E7ULL
        },
        {
            0xE58474B4D9A0EC95ULL, 0x192995D8E76C0075ULL, 0xC3AB026FC8672ECDULL, 0x65AE74C3056C2E7CULL, 
            0x9F4D0187A8CBF2E6ULL, 0xF7719F4F2514B7F6ULL, 0x2AB16BCB8ADDFD7BULL, 0xC2FD3E10C917A373ULL, 
            0x95F57623DDF7E4ACULL, 0x3501F4EDE5FFDF37ULL, 0x54C67F73D004B633ULL, 0x91703CD9DB26FA70ULL, 
            0x9E44A313A854CC6FULL, 0xCEA73F303F37C886ULL, 0x89AB073C7CDDF6D7ULL, 0x07CA9969A4F33614ULL, 
            0xB02F1EBDA2AB3487ULL, 0x9CC942D06BFF77DBULL, 0x2702A361D58A4475ULL, 0x05801253D7072778ULL, 
            0x2E9E83419F207348ULL, 0xD014BA4F2A7817AEULL, 0xBF8763F48C5ACB6EULL, 0x6BD788338F2947D3ULL, 
            0xA031BCB5CE8E87E2ULL, 0x415A73CB9950F926ULL, 0x288B6C331F1F0C03ULL, 0xA2A41C52B0BFA09AULL, 
            0x6782C180F7BCE509ULL, 0x0CFCB061B6C5C296ULL, 0xC31121F46271E630ULL, 0x0D741FC57991DD5BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Procyon::kPhaseHConstants = {
    0xCBC70EEE4FA7F4B2ULL,
    0xDCCA32A1BD3D2E65ULL,
    0x7EE7327D9334251DULL,
    0xCBC70EEE4FA7F4B2ULL,
    0xDCCA32A1BD3D2E65ULL,
    0x7EE7327D9334251DULL,
    0xCD0656BAF06F0F4AULL,
    0xC23846ECB4B9A643ULL,
    0xD2,
    0x03,
    0xD4,
    0x24,
    0x70,
    0xCF,
    0xB1,
    0x23
};

