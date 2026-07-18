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
    std::uint64_t aPrevious = 0xB00B059ACE979D65ULL; std::uint64_t aIngress = 0xAF033C5C7707690DULL; std::uint64_t aCarry = 0xDEF4A5C2034D694BULL;

    std::uint64_t aWandererA = 0x9F2FE932C4285203ULL; std::uint64_t aWandererB = 0xA370FA21C219124AULL; std::uint64_t aWandererC = 0x9A602A4C7D5535CEULL; std::uint64_t aWandererD = 0xD514EE115873F710ULL;
    std::uint64_t aWandererE = 0xDA89476917938B12ULL; std::uint64_t aWandererF = 0x823BB6B22AAA3ADEULL; std::uint64_t aWandererG = 0xF3D793CBA2C243C0ULL; std::uint64_t aWandererH = 0x9DF2DC000F4ACAF1ULL;
    std::uint64_t aWandererI = 0xA3DA5CE2A5714FFFULL; std::uint64_t aWandererJ = 0xCCC651A241BB5CB9ULL; std::uint64_t aWandererK = 0xAEE9AB859AECF012ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13168630206677111512U;
        aCarry = 16763462014867814341U;
        aWandererA = 9381960819070717292U;
        aWandererB = 9993082873529774488U;
        aWandererC = 14806988841385658945U;
        aWandererD = 11943125902478234326U;
        aWandererE = 11647438952302732994U;
        aWandererF = 13216783094654326125U;
        aWandererG = 14498321953239035969U;
        aWandererH = 16275264231628571633U;
        aWandererI = 16060552647530591627U;
        aWandererJ = 12219877123596481896U;
        aWandererK = 17282699870795127360U;
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
    std::uint64_t aPrevious = 0xE1D83174A3E13970ULL; std::uint64_t aIngress = 0xB8E1529D988F48F5ULL; std::uint64_t aCarry = 0xCF05D193E77DBD8EULL;

    std::uint64_t aWandererA = 0x8F5208B53FC7FDE2ULL; std::uint64_t aWandererB = 0xAA119411CBD80922ULL; std::uint64_t aWandererC = 0x80662057CFFFE7D7ULL; std::uint64_t aWandererD = 0x9136EABF8174137CULL;
    std::uint64_t aWandererE = 0xCEC1B1C36167B134ULL; std::uint64_t aWandererF = 0x92733DE367376098ULL; std::uint64_t aWandererG = 0xCC6C402F703E1F57ULL; std::uint64_t aWandererH = 0x8B6EA376AFB36AF6ULL;
    std::uint64_t aWandererI = 0xD4ABA0ACCF198EA8ULL; std::uint64_t aWandererJ = 0x9913E1E95422F60DULL; std::uint64_t aWandererK = 0xE3418C88931739A7ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12763149300946124120U;
        aCarry = 16644200441816496519U;
        aWandererA = 10650056950846445616U;
        aWandererB = 12014749514409031644U;
        aWandererC = 14762586608193305557U;
        aWandererD = 17106139222774217033U;
        aWandererE = 11318931569651902308U;
        aWandererF = 10704995529930629719U;
        aWandererG = 9750738361772424157U;
        aWandererH = 11011138107611472017U;
        aWandererI = 9804886738725619076U;
        aWandererJ = 9868831219200038736U;
        aWandererK = 11686838158618530159U;
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
    std::uint64_t aPrevious = 0x96376F74F6CF83D8ULL;
    std::uint64_t aIngress = 0xFFBBF19FDA500F90ULL;
    std::uint64_t aCarry = 0x90576BAB4AF51E0CULL;

    std::uint64_t aWandererA = 0xA63FF30354BB0295ULL;
    std::uint64_t aWandererB = 0xF9FFFF6E986BA83BULL;
    std::uint64_t aWandererC = 0xB13D83C66EB46124ULL;
    std::uint64_t aWandererD = 0xFDB948073593909AULL;
    std::uint64_t aWandererE = 0xE2C80378B7914CD1ULL;
    std::uint64_t aWandererF = 0x80AB0F3E30A7323FULL;
    std::uint64_t aWandererG = 0xA8DED66BFAB9DB23ULL;
    std::uint64_t aWandererH = 0xE1743D16875D40A4ULL;
    std::uint64_t aWandererI = 0x98F538612434478DULL;
    std::uint64_t aWandererJ = 0xE1C2E2B48328128AULL;
    std::uint64_t aWandererK = 0xF539F47F4599F8FCULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    std::uint64_t aPrevious = 0xF5D02EF5B37B52BBULL; std::uint64_t aIngress = 0x85EB6E073BCE237BULL; std::uint64_t aCarry = 0xB9106AB6523F3791ULL;

    std::uint64_t aWandererA = 0x86C59C261B20623EULL; std::uint64_t aWandererB = 0xB5C0683A897CE3DBULL; std::uint64_t aWandererC = 0xAFD15312220BBD66ULL; std::uint64_t aWandererD = 0x85F37D01FA406242ULL;
    std::uint64_t aWandererE = 0xDF96C110BAF4DA67ULL; std::uint64_t aWandererF = 0xC25B85347059B58AULL; std::uint64_t aWandererG = 0x8546E73A1AB631C0ULL; std::uint64_t aWandererH = 0xA16974EDCE8C4ADFULL;
    std::uint64_t aWandererI = 0xB734CF98ECD00598ULL; std::uint64_t aWandererJ = 0xCCFE6225FE91E916ULL; std::uint64_t aWandererK = 0xFB21A83C35343FC2ULL;

    // [seed]
        aPrevious = 14908494849109111867U;
        aCarry = 12683452651110341141U;
        aWandererA = 13627383779100503517U;
        aWandererB = 9274650218665632735U;
        aWandererC = 18230540000507470811U;
        aWandererD = 9554330927303217409U;
        aWandererE = 10666166643902010119U;
        aWandererF = 11717917391540779087U;
        aWandererG = 9500463143195125708U;
        aWandererH = 11083415185254019064U;
        aWandererI = 9262029466856469144U;
        aWandererJ = 15688948802005335416U;
        aWandererK = 12128398100396411209U;
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
            0xBACE917123875B73ULL, 0x654E191544D5F5D6ULL, 0x8FE68E7084045726ULL, 0x63410461EB73DCDAULL, 
            0x32125BB1CB51E659ULL, 0x5093D684229ABDE9ULL, 0x4441C05A73517E3AULL, 0x2664922DA9E4C01FULL, 
            0xDE16E3214E48E472ULL, 0x026600B199CC8948ULL, 0x6BB98250DF02853AULL, 0xD17D90CD943C7CEAULL, 
            0xDADC81A1147F94F9ULL, 0xCF16250517D9F464ULL, 0x33E9230D10215A63ULL, 0x4413D11DB6279229ULL, 
            0x0E1161097E55D271ULL, 0x0A8D533FF8BC1BD4ULL, 0x4EF91251249DE5F7ULL, 0xD091505DA2812F71ULL, 
            0x2FE88FCD8E173674ULL, 0x0865A6D15B620EABULL, 0xCF8A66949B93A48BULL, 0x50D16E01C46B459EULL, 
            0x2A69381AA73063F5ULL, 0x43213C21913AF36DULL, 0x5549474D21CDD73EULL, 0x4A76D074665E3EBDULL, 
            0x0FA05C1D0E86DE61ULL, 0x36D787D70544A512ULL, 0x0D08DD13884F25F6ULL, 0xDDCD454ECA6BEB8AULL
        },
        {
            0xDB8D1085EF3BAA00ULL, 0x7F3C07809A0D37FEULL, 0x0A52FC4AF042DC30ULL, 0x62D4ED314D1F0403ULL, 
            0x984D83A1D3D27BADULL, 0xC570260638FF5296ULL, 0xE87E83E1CB79FBD8ULL, 0xB3E946B85E16995BULL, 
            0x3875A9081754965FULL, 0xC413AB7ED0A5F22AULL, 0x4EAB566AE04EEF59ULL, 0x80D42CCB59CCBE18ULL, 
            0x268CF370CE2EF43EULL, 0xD4320D3B6954C915ULL, 0x7341D735E06F72B6ULL, 0x1901BFE5B151719AULL, 
            0xA70DA9CCA1AF1A65ULL, 0xC0C0E68BA8B147EDULL, 0x69C131C7944CA818ULL, 0xC2C5393F7B294829ULL, 
            0x7B6FBABFB0D60364ULL, 0xD42275031F2FF61EULL, 0x5315AE39A0FEFABFULL, 0x625A0A8A82E55FDAULL, 
            0x39F0FD6B2CE91E8DULL, 0xDB5E15081E36A7FFULL, 0x219D6E6CCDA53AEEULL, 0x7592C4CC570F8978ULL, 
            0x4B76B032F2E10943ULL, 0x2C5999564A9B7284ULL, 0x2FAC0D546B8C26A5ULL, 0xCEFDEA6261AD8B82ULL
        },
        {
            0xDA292E2A6A8B5478ULL, 0xF725E40E1AD7E9FCULL, 0xCF6D102446C43625ULL, 0x750FEC160C84BFC8ULL, 
            0x1050500629BE805BULL, 0x8218DB587FBF0300ULL, 0x4552AA9729A9E258ULL, 0x155535DDAEF1644EULL, 
            0xB7F19E9318E130C0ULL, 0xEFF95E53D915C198ULL, 0x990D2E0BB86829F2ULL, 0x27D837CA96565727ULL, 
            0x8E5FF3BFC827AD17ULL, 0x000B0E3AF7779B03ULL, 0xFAAEDDBD1BCF195AULL, 0x9BF82EFF74E224F8ULL, 
            0xF66403927DA37509ULL, 0xF41E3A3A7B963B9EULL, 0x161E119E11443EE3ULL, 0x976625726940D4AAULL, 
            0x4CA222A29D44A27CULL, 0x8E8015D5E1BCF2A9ULL, 0x4EC9CA7216FCAA3AULL, 0xEE48B43937E1E188ULL, 
            0x56BC0FCD79FE6046ULL, 0xB29BC4628D5F1E3FULL, 0x6A5CFDBA145889CDULL, 0xCDEC4777A8FE9BDAULL, 
            0x18AABE799E33B52FULL, 0xAC916011727C450DULL, 0x7A2D9A2AD96A76B3ULL, 0xD1248CA373EFE786ULL
        },
        {
            0x0663D47CF5E99B27ULL, 0x8B028D75203480DFULL, 0xE2BABB726319EF2AULL, 0xDBBDEF1F05F5B33AULL, 
            0x8FBA022D9C2E4BC3ULL, 0xC7E5C9AF745C41BAULL, 0x904DA5E7955A3058ULL, 0xB131EF40BEC1592AULL, 
            0x28595A673CC416B2ULL, 0x70953F6E6CB15031ULL, 0x37D5AAEAF75D98BDULL, 0xDD5BC30B0D40ABC3ULL, 
            0x513B820CEB89FC74ULL, 0x8607E2F18D2E569BULL, 0xEE4153E4E9C0796CULL, 0x1413092A531EAFD8ULL, 
            0x68968C576A95B9C9ULL, 0xB0D477364AAFBFE3ULL, 0xC00DAD29D1B1BFE1ULL, 0xDD176DD3A9BFCF97ULL, 
            0x93F4CD8C549E6374ULL, 0xD1761616C49C5D13ULL, 0x63F771759015E8C2ULL, 0x2CE0DF62E6CF935BULL, 
            0x38E3AE59C35E8055ULL, 0x990AE72DB863062EULL, 0x65037D55819D2D17ULL, 0x5B67548D93B02299ULL, 
            0xFC4DB3E696077021ULL, 0xC840243F9A4D1641ULL, 0xE2322736E9D7A68FULL, 0x4C4F1D882715C3BAULL
        },
        {
            0x0AC8D878EF758E72ULL, 0x69016F344D1912C8ULL, 0x5A4C67C916209938ULL, 0xF5D4CAD57AE7BE21ULL, 
            0xD08056100CAA6E9EULL, 0xEBC6F681DF808E98ULL, 0x0AEB23354D083504ULL, 0xD21C927CF3E2D1DBULL, 
            0xE2CB6289D022CFC6ULL, 0x51E8A34705B74C66ULL, 0x7D06609BFAF97E59ULL, 0x56298F1C32E0E8A4ULL, 
            0x44C27B0022D586D5ULL, 0x21D5FF0FDC79920AULL, 0xED04637D4AE1BB44ULL, 0x7A71C5FBB782336CULL, 
            0x5D50F4A41BDA0EACULL, 0x16CD09847B53115CULL, 0x3FC7FF3971CE69FDULL, 0x7ED4FA8D7C09E5CCULL, 
            0x6C4320BDB78F4AA0ULL, 0xA7F4B4835B7CB05CULL, 0xC4B0F2BFF638257EULL, 0x877E1C2A14D07FEFULL, 
            0x41D7057E5C5DC86CULL, 0xB3B621FD3876A2C7ULL, 0xFA6E8F490C8C091EULL, 0x38A3B7C3AF6D58ABULL, 
            0x8805C30B73AE4D1FULL, 0x679A5CADE203ED52ULL, 0x989123F6E1E18809ULL, 0x02C558771358C0D0ULL
        },
        {
            0xDBAE14BB1879AD2BULL, 0xB4C6AC7890DEED99ULL, 0x8AE9AE4FA56E03B0ULL, 0x9904D9B888F0E6F9ULL, 
            0xEE97106D577248F1ULL, 0x7EA487BF3F970C44ULL, 0x02FB6F1E582BE806ULL, 0x94FFE0C08F142F15ULL, 
            0x91A5288071BFB32BULL, 0x20B584A33C3384ECULL, 0x54F41FE24D6CF1DCULL, 0x0AB85836EBE0EE43ULL, 
            0xDA5D434F94B61726ULL, 0xBF261314B0C10AE3ULL, 0xF94B7FB006A52D01ULL, 0x8AE87F248AC85078ULL, 
            0x0C25C6E97AA40F06ULL, 0x1DFFA926D84CA95BULL, 0x8A4838D9C566998DULL, 0x6356C93437499603ULL, 
            0x7B5A673CA80F6B71ULL, 0x08A24D8B2CC5D2F6ULL, 0xC2F393DFA114A2D8ULL, 0xB6D5498A3B27F6BEULL, 
            0x10CF715BC23D7701ULL, 0xA3EE7FC65DEABAE6ULL, 0x8B1FA5235F84B2E0ULL, 0x71B5B0ADD235992CULL, 
            0xEF6780081EA36695ULL, 0x264B5E64EABA1A25ULL, 0xF5D65C43499F1FC9ULL, 0x78F3A8571D8AD70DULL
        }
    },
    {
        {
            0x5D959C795F9809F3ULL, 0x0FE7BB3BED644506ULL, 0x006F32A97887E139ULL, 0x3909FA71D8EBEA97ULL, 
            0xA02B226496431D6CULL, 0x0B555FE7C3EA44BEULL, 0xB80E9D872D6FF93EULL, 0x1DE7F1ABE8158A90ULL, 
            0x1CD6EFF9515991E5ULL, 0x57F91150AD02EEAAULL, 0xB6C0AF7ACA72A6DAULL, 0x67DFE8F17564E89CULL, 
            0xB333C0BB0C822884ULL, 0x30B8E13993D3E90AULL, 0x319D55AA6B7FE310ULL, 0x9C6B5D8F6DAEEE2BULL, 
            0x295449846FEF6C7EULL, 0x9F494142A81E1256ULL, 0xFFE45E08E4EE0C5BULL, 0x1258F8D5B360B237ULL, 
            0x8CF884A47BABA072ULL, 0xAD8B560C9280AC20ULL, 0xA69CB5CF3FD5741DULL, 0xB0AD03AC58C4594AULL, 
            0xA52825C5DBB863F1ULL, 0xEBF72655EC36010FULL, 0x176CF70D62DD92AFULL, 0xBD4EDE8D53B33661ULL, 
            0x5F2254845A3FA2C6ULL, 0x5A133CE2310BD11AULL, 0xF37426B8E398A57BULL, 0x141A935722228AB9ULL
        },
        {
            0xB1908A76CCF719B9ULL, 0xBAF2BEF1E68E6780ULL, 0x938EC804D30A29B2ULL, 0x689FC5E8426FB61DULL, 
            0xB3E52AF316FBFFB3ULL, 0x247CF1A78D9470E0ULL, 0x2DA0E5D19A16559DULL, 0x7ACE2AD483536FE9ULL, 
            0x081E23836FEE4875ULL, 0x8B906C5C553A8288ULL, 0x789E1BC522A28CC2ULL, 0x9E774278F95DA7E4ULL, 
            0x28EB43715EB70453ULL, 0x8E7F7E6862617466ULL, 0x8A293EE85DEA8589ULL, 0x90CAD524FEEB24F1ULL, 
            0x54417D6EEE98E0E1ULL, 0xDAD79514EE794501ULL, 0x697C8E0730FDB265ULL, 0xD8BE9313CAC7A3B5ULL, 
            0x8732AC6BB320F101ULL, 0xD97C8AF872A3F419ULL, 0xE44CFE9EED3AC91DULL, 0xDB53928E8B188EA7ULL, 
            0x55B75FBBA5F36861ULL, 0x32E11F68F00DC87CULL, 0xA39A54ED2A152EC9ULL, 0x49732A4900535570ULL, 
            0x5F4F35F66454ED31ULL, 0xB5D8706C6D98D3BEULL, 0x1089BD3E485EA5F8ULL, 0x69B126DBB34B6D52ULL
        },
        {
            0x42D8DB111BDE4F8BULL, 0xCDE4B8C76405BAA9ULL, 0x771C31D6123F5689ULL, 0x942F4EDB79FDBB62ULL, 
            0x4513A43239E9E32DULL, 0x6876698586E48844ULL, 0x4BF628EAC7CA5576ULL, 0xD55520316FC1F946ULL, 
            0x9ABBD57CCFD17ED1ULL, 0x1BC28C3A2A774B4BULL, 0x3902FC73FAAAED9CULL, 0x10222E722DE3CAEDULL, 
            0xAAF8E9486C1023B9ULL, 0x92EC765DCCC3792CULL, 0x47F93B9F2CDCA6AAULL, 0x0C0F12B23B370BA9ULL, 
            0xDEAB02D9E9CDFACAULL, 0xA4094DBDCA8365ACULL, 0x6372AE9CF26DCF15ULL, 0x331B2E5D068F2155ULL, 
            0xA74E6774AD5036EBULL, 0x2504AF160C4B0731ULL, 0xEAB2602543CE0F0BULL, 0xAD1AF59725737361ULL, 
            0xFC51FDE0A7AB20D1ULL, 0x31F5A8D701FACFD1ULL, 0xCCC4506FFA6A4406ULL, 0x68840B176F4AD19DULL, 
            0x51CC724AD719698CULL, 0x005813B0A9DA1D23ULL, 0xB03C6FB638C01D12ULL, 0x9B87F89C75839337ULL
        },
        {
            0x26A6236932ACC91EULL, 0xA29999F72AF45C5AULL, 0xC9893B7C5FEBF2F7ULL, 0x4DC411134DBBED9BULL, 
            0x6E4945168D212121ULL, 0x302E5DC6EED53D72ULL, 0xFD56FAE516426C19ULL, 0x3E0C6D9023258F44ULL, 
            0xBDD2BCB1884982D0ULL, 0x0634DFF4F7B8DD88ULL, 0x4CEC1B83DA15D8DBULL, 0x7072F6C4CA3934BEULL, 
            0x4419FDE0EF6ADC7CULL, 0x2061BBE284B0EDFCULL, 0xEBE9B3344A7343C2ULL, 0x37F665231AE04495ULL, 
            0x853174892C1E7976ULL, 0x10928A3C18A61D43ULL, 0xA947961DCB3BADBAULL, 0xC08433DA852D524DULL, 
            0xE18E79279E3DD7CAULL, 0x52DDE0191F9292FEULL, 0xB16D744BECA19667ULL, 0xDB0B6C7A43709181ULL, 
            0x3932153CA92A7A1DULL, 0xA48BE1A9F9FB7894ULL, 0xD5909F9870462D80ULL, 0x1078426F9894BDBFULL, 
            0xB5E774B1E314AE19ULL, 0xB78DE258217AAB4FULL, 0x75588EA225C92D9FULL, 0x7A3A7DD8129FF5C4ULL
        },
        {
            0x3E07976C235CDFABULL, 0xB518A8DB7240959DULL, 0x2B2AB345F5A68934ULL, 0x1AC91FEB82A0EC57ULL, 
            0x3FEA1F81A8291415ULL, 0xA8992C58AF5EF70EULL, 0xFE2CCE4EB0EDECF5ULL, 0xA189E66E9C300C94ULL, 
            0xF1C230D054D440F1ULL, 0x4142AB7FEB948446ULL, 0x7BD43E69159C6A57ULL, 0xF532622F96A9CACEULL, 
            0xB5A7A09589DC41F4ULL, 0x9FAB5EB613291885ULL, 0x3127DFAC6A809936ULL, 0x513F76B34CB26E66ULL, 
            0x9FDA532AA715AD47ULL, 0xD082200E71D8677DULL, 0x8CB636ADC47597B1ULL, 0x9280400DFA119124ULL, 
            0xD04F34B25FFDA89FULL, 0xCB55BD2095CC2ED0ULL, 0xC22EC509AF65E095ULL, 0xBEDE092CC21F77B6ULL, 
            0x36A15A27FA005CE2ULL, 0xD53467C0FD014BBFULL, 0xA4D0C7A1436670B9ULL, 0x0746E9C9FBC9BED2ULL, 
            0x487EC3BF28BD9915ULL, 0x097932C16FC78D36ULL, 0x82B083C65B64E79BULL, 0x619231D52E1A8165ULL
        },
        {
            0x250912B342409C60ULL, 0x5784F1C8ADE379CAULL, 0xF21E8E9263591428ULL, 0xF821C7C0A2966357ULL, 
            0xF1080FC6C76163A5ULL, 0xB5883637E851723CULL, 0x2B474941C32861DCULL, 0x986B70114ACF7ACDULL, 
            0x17A85E95FF6C85A3ULL, 0x31BCDD75FCF22081ULL, 0x3802273E59A7DABBULL, 0xDD0F6F221992F6B6ULL, 
            0x63F8ED06308387B1ULL, 0xB18EFD83DA63FC42ULL, 0xC1C146910992F5F1ULL, 0x473EE7637E769F27ULL, 
            0x268DC4615973EC56ULL, 0x5D9C53D68579660DULL, 0xDD3819A53A9AF601ULL, 0xD79FD90E0C5AA687ULL, 
            0x45EEC4A9197F9A23ULL, 0xB4BD9D92C33E07ADULL, 0x7C524D286F592AA9ULL, 0xA5752135DC5DAD67ULL, 
            0x2E810F8E4EB007E8ULL, 0x19DFC18F086E5B4CULL, 0xEB6E51863489DAAFULL, 0x67D3D84FA7113246ULL, 
            0x997CE11EE69E70DEULL, 0xD54326851FB0363FULL, 0x63CB6D89FCE46155ULL, 0x2AA33867D8C144E3ULL
        }
    },
    {
        {
            0xB3563F85B6B15C00ULL, 0xC9151698AE054173ULL, 0xCAB43A2D45CC7450ULL, 0x19A951BC7130C79AULL, 
            0xE5C0085C5B7367EFULL, 0xB9FDBA5DD83B0CF7ULL, 0x2E558FAD649223E7ULL, 0xE18C32A0DC838160ULL, 
            0x744D57D03BCF0DDDULL, 0x443920924DB6AD06ULL, 0x10343B19BD56BB52ULL, 0x85A57443304CE115ULL, 
            0x39DE384A9BA8B542ULL, 0xA8C63B0724F11664ULL, 0xC6AEB45A709BABA7ULL, 0x17B6F17A0258E99BULL, 
            0x1A6C1A80F57B16FBULL, 0x3523519AFE93F5D9ULL, 0x04FE572582C915E2ULL, 0x008458C59749F6E0ULL, 
            0xB39BB9726C3BCB3CULL, 0xA1620E0102E719CFULL, 0xD33D3D1B9FF37FEDULL, 0xD86D8B61C85F4CDCULL, 
            0x80A1C4AC978E6217ULL, 0x5F1E41065C856802ULL, 0x1017475F3BA357C7ULL, 0x17DB2C2B788E2581ULL, 
            0x22A11297B3E05FE8ULL, 0xD4D76676DEF4A4A0ULL, 0x417D073F34C7DADAULL, 0x5CEF95D989058EF5ULL
        },
        {
            0x0CCBB4E4DD3074E9ULL, 0x71B28517FD6AED3AULL, 0x7F715378AAEC3721ULL, 0x6F56B33A132422F5ULL, 
            0x2A94CF8DE9DDBDE3ULL, 0xEB9EEE6AED28351AULL, 0x7F0CE58EC4AD8DE7ULL, 0x508A6DBE1A3F49D9ULL, 
            0xD8BBD358E2C6F176ULL, 0x86041B7E925576FBULL, 0xA1E3837FBDD52676ULL, 0xC7E73300E2ACA34CULL, 
            0x7DBA68544AC16D7DULL, 0x9059F790FE51FB2AULL, 0xB846D3A4577B8FA0ULL, 0x5774283422F8AE65ULL, 
            0x6274E7A1E98AC3D5ULL, 0x8BBB846775E707CDULL, 0x1427AFEA1A29268CULL, 0x124CB27A578D7807ULL, 
            0x0C8415AC3178887CULL, 0x7710E197ACACA146ULL, 0x616D001E494A3D3CULL, 0xB9B1C80846DD2168ULL, 
            0x16F62BD45D76B0DFULL, 0xDD527765CC41BA6FULL, 0xB4B4CA36B66CC105ULL, 0xAEAD7995B6CDDD72ULL, 
            0xB437206D4992122FULL, 0xFE4F1E3E4CC0F972ULL, 0x515DA2D0B753AA83ULL, 0x244F8599A94F2D33ULL
        },
        {
            0x444484AEBC0522B0ULL, 0x6AC86FF538CA8399ULL, 0xCA1826C1F1BB40CAULL, 0x15DCB889E2C73F50ULL, 
            0xE38042BC65795815ULL, 0x9ECDEFDE316F3C53ULL, 0x49D106020D2C5AAAULL, 0x8882027156112DEDULL, 
            0xDA45641A42082370ULL, 0x0C2511FECE9AEF96ULL, 0xFCE359FD12DBD150ULL, 0x5826254737F8BF64ULL, 
            0x236D01DAA92C2E5BULL, 0x1CD7A7D9BFDD5C8DULL, 0x21F8FE218E50E442ULL, 0x8FAC45753379B445ULL, 
            0x822CF8EE9E3A195CULL, 0x4FAF7C3E76974C88ULL, 0x3687220792CC908CULL, 0xAC170BD83C7DD658ULL, 
            0x5FB1D8EA5E1BF120ULL, 0xDF3FFED407ADD195ULL, 0x4892DD3958998B12ULL, 0x703322711CC998C9ULL, 
            0xFD3EBB4F1F41602DULL, 0x7CAD119BDE2FCC8FULL, 0x13C6B9D97433CAA6ULL, 0x508EC90AAF4CB7B6ULL, 
            0x4CA5F9996DF9E96CULL, 0x6FC4B776E821D577ULL, 0x8CD0B66479AABAFAULL, 0x5A0103AF0F59DCD9ULL
        },
        {
            0x6DF2A72E7C37DBEBULL, 0xCDE54E78C3705063ULL, 0x2E96CE581C08BD9FULL, 0x277B8EFFEA8DBDECULL, 
            0x20C0076D348C9527ULL, 0x2AD9E612F992DE2CULL, 0x75BE57FA6980005EULL, 0x66441AAFFBE70836ULL, 
            0x725840E0C0C231B9ULL, 0x751E9CB5EE032E72ULL, 0x4D0ABC5C94265A62ULL, 0xFE1689C1A000F317ULL, 
            0x407D51CD0F9CABE7ULL, 0x4F2CD4DD5D85BA95ULL, 0x5192575E39CE86DFULL, 0x9BE33AED9289F3B2ULL, 
            0xD962F4802D3E106BULL, 0x352992B4CE76E59FULL, 0xE2B77F65B8ABE19AULL, 0xECEB7E57E0071960ULL, 
            0xF6938C594042435FULL, 0x993E4AB015ED4322ULL, 0x29D0ABFA408F00E2ULL, 0x1AA0A909A67A907BULL, 
            0xC6F2857B240ABCFAULL, 0x80278E3AAC116859ULL, 0x47A1088ED4134470ULL, 0xC7F009564C9B6448ULL, 
            0x7DCCB35794506D10ULL, 0x8CE09CEC1418964BULL, 0x1F97AD9A7FEC6D56ULL, 0x349B56DA91CD90E9ULL
        },
        {
            0x8987BF791B103831ULL, 0x8AFDE5AD84EE10ABULL, 0xDF25C602FE702859ULL, 0x28866177B78C5D2BULL, 
            0x34758C28D8613AC9ULL, 0x07DFE3F44A9C4A75ULL, 0xCC43FC562D29FB4FULL, 0xB0CFF78B9D48BD12ULL, 
            0xF1D6432C0794F1A9ULL, 0x537BC809BB7C83EEULL, 0x956EDAFCD432438FULL, 0x3FD30F4D8A0D2926ULL, 
            0x48E5123390575C4CULL, 0xB506D7BD1F2E73E0ULL, 0xF915F959CEFE9426ULL, 0x9BA0F61C33A26899ULL, 
            0x6ADD8300C0F2D09CULL, 0x2ACDB84FD9550BE4ULL, 0x55FC15946B09D6F1ULL, 0x99F1E82DC0BD5611ULL, 
            0x255DC61AAD49C961ULL, 0x4F42A8ED43CEB855ULL, 0x2B4C769F753FDE43ULL, 0x9055142FC4B626B2ULL, 
            0x34121A88AC7AA055ULL, 0xFB5AA07E4F65C90DULL, 0xFC085A2431DB5704ULL, 0x918FA1118B210177ULL, 
            0xB5225F30AD9BB39EULL, 0x537AB706C97B4B64ULL, 0xF0A7F51421977A66ULL, 0x13B198D280705337ULL
        },
        {
            0xAEC16986BE2F67E4ULL, 0x21FF4CFE7CD78411ULL, 0x62C3F492083DF49AULL, 0xA2C0A293DCDD741AULL, 
            0x964E498DAB93E0DFULL, 0xE45EBD503A45DD13ULL, 0xC8641EF9A3AC3254ULL, 0x1B60341D8D702215ULL, 
            0x2DB0BF441B3CCAFCULL, 0x6DA5328338022ECBULL, 0x7CA3A559CC5FD7F2ULL, 0x40C8018FAB46A540ULL, 
            0xF4450A9D81462BD4ULL, 0x59F2192F03A8EF29ULL, 0x2883EAD6FE5509D6ULL, 0xE6006D7625AFC51FULL, 
            0x79CDE1D91278ECF0ULL, 0x51F0245421249D90ULL, 0x3553AD23B933F341ULL, 0xA2C675E2E6786463ULL, 
            0x576E7BCD9AA08BD6ULL, 0xA0E519183C79CE37ULL, 0xAFA8104246399B70ULL, 0x300CAA8583590FAEULL, 
            0x735F0B993BBB0B50ULL, 0x2F7DC5E08A591CECULL, 0xB285F1CE0277625DULL, 0x009C7364F81C34D3ULL, 
            0x1F5559FC7DBCA1EBULL, 0xA6EE50CB54536668ULL, 0xF5E8667B3F46D8ECULL, 0x5CEE699BAE6AD5A0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseAConstants = {
    0xCF647F49EE551B42ULL,
    0x61B8B1B359A03BADULL,
    0x8BF2B22AE5FE7AD9ULL,
    0xCF647F49EE551B42ULL,
    0x61B8B1B359A03BADULL,
    0x8BF2B22AE5FE7AD9ULL,
    0x5CF3004CA54074ABULL,
    0x2624C6FF4360AEBAULL,
    0xA0,
    0x45,
    0xC8,
    0x66,
    0x09,
    0xB6,
    0xCF,
    0xF2
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseBSalts = {
    {
        {
            0x3BC7C0BB35267DBAULL, 0xE460B0CEE558EB5BULL, 0x17978DAA499B8BC6ULL, 0x0E2EE46E80665184ULL, 
            0x5B29AC97D6C9F647ULL, 0xE1C0AA52A5F03E7FULL, 0xADA9C8F4301A7B8FULL, 0x76207C207E146DEBULL, 
            0x9810747601AE1526ULL, 0x341B6C1DCF1C428EULL, 0x000F40B34B64FF65ULL, 0xD97DB9F42F154D72ULL, 
            0x368189598BFB02CDULL, 0xB2AB97A11C97C2BDULL, 0x55B6C168842E17A7ULL, 0xEB98C9A037199CA8ULL, 
            0x9ADFB36D8EBB84D3ULL, 0xB38F8FCF09F81720ULL, 0x78C0B7FFAFA00DFEULL, 0x2D2EF7AB0B2D0D6BULL, 
            0x95F19547C479A5D9ULL, 0x889CEFBFBC98818CULL, 0x1F551064F226776AULL, 0x4EDC818AE4904C09ULL, 
            0xF27FE4DB58C43646ULL, 0x6A1FCD71D35F1308ULL, 0x14A4855B3B734F16ULL, 0x675F015A26D63B30ULL, 
            0x55A0669AE12F1237ULL, 0x1A07259A58C42F15ULL, 0x5DE457FE30580577ULL, 0x378F497BDC124DA9ULL
        },
        {
            0x84BA817E0941E7F3ULL, 0x57B529F76A4FFEACULL, 0x38AEABC0C97257E4ULL, 0x2A85DE77987A3DA3ULL, 
            0xD1CA1FCC1D49844EULL, 0x0BB2F8CAEA17218CULL, 0x3FB9F64960176CFDULL, 0x74F20B814DC8C9DCULL, 
            0x50CBCF6C0B7BE79CULL, 0xD72910A40FB982CFULL, 0x0718DDA9C8134544ULL, 0x8725B3803FC43C67ULL, 
            0x635A0D88F9EE4532ULL, 0x0236B7D252B58EC6ULL, 0x0A5F5E7EEAC42318ULL, 0x587A7EA6667615A2ULL, 
            0xF9D5312463BA50D0ULL, 0x277FC9E16F6A4DC8ULL, 0x80D804DE1A4DF7D0ULL, 0xEA4514FF13E4CAEDULL, 
            0xC2485929460A9014ULL, 0xB8E5C22815D76ED9ULL, 0x1FA28BF4322CD282ULL, 0xF51B21FC36BB3FC3ULL, 
            0x72E23102F5C593D7ULL, 0x7D4EDD39BFF9FEC8ULL, 0x9BB1834EFCA3883BULL, 0x5CE7216B7728BD8BULL, 
            0x8F54458297D38CA9ULL, 0xC7B4C3578B2EBFC2ULL, 0x8EB91B4DF75629E4ULL, 0xECA7F29A8451ACB3ULL
        },
        {
            0x8F1A8846EA4465F3ULL, 0xDB030ED79FDDE14AULL, 0x6D97EE46E3B6F5D4ULL, 0xE14809B055DFE51BULL, 
            0x014946FB3C08228DULL, 0xEE5D17638541A058ULL, 0x68BDAD5659B6C419ULL, 0xBE069D2BB4CEE9BFULL, 
            0x0AD68B26FAB6076BULL, 0xA5F31781604FB756ULL, 0x80CE98915C80426FULL, 0x35CA3B058B2B4CB5ULL, 
            0xB36521FE469E7B2CULL, 0xC8BC788516DAEF43ULL, 0xB22012B28D0496E0ULL, 0x5D3B572E095CEA25ULL, 
            0x83FBC1EFDA796446ULL, 0x957A331AAE137C7EULL, 0x52608E1EC9355872ULL, 0x3E8B7270C165E693ULL, 
            0x2521125D89703541ULL, 0x1E7C258E5A08F9B7ULL, 0x8727E5CADE11DB53ULL, 0x809B1AE37F86544AULL, 
            0x1C2F4F721A0C0ACDULL, 0x4514C25B587A1074ULL, 0x6BD38852793EBDD3ULL, 0x38E34BFE3C8FC094ULL, 
            0x870EF9A4BACE2E0EULL, 0x54D970F6B8C97A22ULL, 0x73371C82FA850284ULL, 0x2C9D7631F746A276ULL
        },
        {
            0x930FBB36A38BB31AULL, 0xBB1ACACA3097F5AFULL, 0xBA56E42065D78B95ULL, 0xD2D07A6EEDA4D7F2ULL, 
            0x94EA3C306076D17AULL, 0xEAECFAD7155948A1ULL, 0x8DE3D243850EF517ULL, 0xEBFDF02D9D36233CULL, 
            0x86DE6EF4628A6437ULL, 0xC34A504F7DAFCF52ULL, 0x23B7EEE95EAA4813ULL, 0x95DC38F445239394ULL, 
            0xF45857CD1B6B3A8BULL, 0x9FF3EE660FAF117AULL, 0x5BB7B65865EEFAECULL, 0x4A44C4204554809DULL, 
            0x8DC78AF1BB26093FULL, 0xAA3607905361F18DULL, 0x09FD66E44F59D067ULL, 0xB4F4946C2DACA694ULL, 
            0x42630ADFFC3DFC1AULL, 0x9B9CF6751F5221C9ULL, 0x68732660BEC5B36BULL, 0x0EEAF82ED9356CEFULL, 
            0x177943C60799FE26ULL, 0xB4E10AA82748E7E0ULL, 0x52EB78EB72595FACULL, 0x603046B95EBF08EFULL, 
            0x46CA4D2743022B05ULL, 0x38482602DA4E4E7BULL, 0x7A8D5D84C5FF47E7ULL, 0x7DA30558E46BE61FULL
        },
        {
            0x751498D428AA6100ULL, 0xCA4C8F0CA990A91BULL, 0x146C649BDD4085FBULL, 0xA4743028692DBCC5ULL, 
            0x28011B70803BB6BFULL, 0xCD6FC9E5D40B6F13ULL, 0x7CBC09758B53E971ULL, 0x98556AAE043CA8CCULL, 
            0xEF59520A52E25C3FULL, 0xE5DD4FA0E8FA5B18ULL, 0x9F8D16D6CF9F8D84ULL, 0x298B073D151614CEULL, 
            0x25B6BC0013C01AE4ULL, 0x3A4D916C63065BCEULL, 0x9A5D0A52D4FD01D6ULL, 0x73AA51FCDEB8C48CULL, 
            0x0C621568097BC74CULL, 0x654EE6E782D26552ULL, 0x235A0A165EAA7E2CULL, 0x2C155BBA80BE33B4ULL, 
            0x3E333F71E27D9FE7ULL, 0x8B0D5E71564C7CCEULL, 0xFC045661B27839F6ULL, 0xFE4B440F85D98A15ULL, 
            0xA1AF4BD7037AE2BCULL, 0xD38917D1A0054600ULL, 0x3186C6C61F8A28B3ULL, 0x4BDAA33FA2556C7AULL, 
            0xE5865A7924C77B23ULL, 0x6632172F66474AAAULL, 0xB8FB98A3BE2B556DULL, 0x7081E54DD1BE197BULL
        },
        {
            0x8788411A3F6933F2ULL, 0xF83EE3D8C43F320EULL, 0xE056909D223B0A0BULL, 0x66E19F08B73A8AD0ULL, 
            0x440CEFF2E75F306FULL, 0x1BE319A28CEAD5CBULL, 0xFC1809C4659C41D8ULL, 0x3A8E7EEBB6A33F01ULL, 
            0xB2067AB8977D6238ULL, 0x024BD62A58F1820CULL, 0x37FB12AB45AB0FE8ULL, 0x4A149ED3E44AC14DULL, 
            0x332ABB3AD8F809D1ULL, 0x148687641D2489D6ULL, 0x364EE45E5A537BEDULL, 0xC8E7F0842D729D98ULL, 
            0x0E279DF3AA01AFC6ULL, 0x0B79888554534427ULL, 0xD851F1EB23B9115BULL, 0xA0FA32780FC4E924ULL, 
            0xFF8ED704DB41CB6CULL, 0x3B29A1B366759F86ULL, 0xA20B8C80428E9E2FULL, 0xD911E9DBBDFE5E9AULL, 
            0xA87D690A96D1948FULL, 0xA9CA260EFE3D1155ULL, 0x00EB2D1A24CD163DULL, 0xE623342F890573F1ULL, 
            0xECE5F080FE5EACA5ULL, 0xCC2240749398B177ULL, 0x4610F62AE69EA000ULL, 0x7A2C3E49C12F0C66ULL
        }
    },
    {
        {
            0x1B35B00654329323ULL, 0xFA1542A9FEC0C3D5ULL, 0x6BB18AB67E2D74CCULL, 0xA23A32E20F9D62AFULL, 
            0x72CB5CADC4CF87A3ULL, 0x4C9716315B067C59ULL, 0x3A3D2B1DCE1CE68DULL, 0x6C326743C4D64B3AULL, 
            0x5224EBC74098EC9AULL, 0xC124F62E379DCA59ULL, 0x2736D77A778C5E26ULL, 0xADD245A7E6E51EBCULL, 
            0x866982C718A94609ULL, 0x24EE91546FCBC862ULL, 0x551D3B5589E52923ULL, 0x3FCD7BDF536241A7ULL, 
            0x6E0B2E1C4BEAEC2DULL, 0x2C7BF676F54F4D81ULL, 0x4415A2C409D2EF1FULL, 0x294130905FE53435ULL, 
            0x49669B53A2D68517ULL, 0x1530907039384483ULL, 0x1B06D3083850A976ULL, 0x0C69E59931B0B6FEULL, 
            0x8BFFBBD37AA2B734ULL, 0x23DA060C78B6D37BULL, 0x620AC1847675CCABULL, 0xEEE1582B399C3A1BULL, 
            0xE90854DB898DF071ULL, 0xDDAF1B2CDC86BEC9ULL, 0xC3D947D6150E29A8ULL, 0x5EB5A2F44B08D562ULL
        },
        {
            0xFAFBC3E0F0730C53ULL, 0xDE57845C3D51B639ULL, 0xF345630DF26E333DULL, 0x93E4AB3F7497253FULL, 
            0x93BF939F3AC9FD8CULL, 0xC1AF9087160C4F10ULL, 0x9ABC5C3D23C5F4DFULL, 0x1989BD979330792AULL, 
            0x58A7A046B35199A6ULL, 0x50417B0D47DAFC9EULL, 0x0205AC323F37F35CULL, 0xB113808037495DBCULL, 
            0xE43DDC941D39915BULL, 0x34AACC9523F8889BULL, 0xCAEE920240ED13EFULL, 0xBE7E7864D743FAD3ULL, 
            0x4B2D10C0ABA08544ULL, 0xB736E5871AC9172BULL, 0x8C93639E7F7473AEULL, 0x75CACFA80B828B91ULL, 
            0x6A669C168AE8840CULL, 0x7C881DCF942AE8B5ULL, 0x1BD6DB24D07C3BF9ULL, 0x1E4D3C493FC5057BULL, 
            0x31097949D185EE81ULL, 0xC43F85D836B46D0EULL, 0x00208F0C6601188BULL, 0x811098ABB34A94C4ULL, 
            0xE1830B2CD03C84ACULL, 0x42E4BF1A900C3B74ULL, 0xF87ED81A80EF3C95ULL, 0x6EA3C38D05D9FEA1ULL
        },
        {
            0x3E1C6D6F3E753E94ULL, 0xE4BC37699D45FF27ULL, 0x6225BC8D446671BEULL, 0x8CD48B2015B15D87ULL, 
            0xEB4CA396C1F8B6E2ULL, 0x06AC03BF36049162ULL, 0xCFD39FE0B94A9157ULL, 0x1E648B44A62F4C47ULL, 
            0x515162150C1493EFULL, 0x9D861D31D2FD7AABULL, 0x86748A6CCA3D4091ULL, 0xED20C7D0CA089A12ULL, 
            0xCBA1E2D4E9888D67ULL, 0x39F659CBA80B4EACULL, 0x83C74E5B66ABAF9FULL, 0xC82D3EAC78E827D5ULL, 
            0x5A2592D43CEB7DECULL, 0xCEC853EE19A6ABBBULL, 0xCCD92E15BD16843BULL, 0x8ECE4B0E1AA7B0BEULL, 
            0x76AFA07DC5A6AC2AULL, 0xB0649A3049665EF5ULL, 0x66790807DF5C37A6ULL, 0xC04D6B35B86D3000ULL, 
            0xE2A464263F752294ULL, 0x0D47909EF818AD84ULL, 0x6393C191CBCE023AULL, 0x9B795DC0286E5E72ULL, 
            0x9D3A9F437ACC264AULL, 0x6D081CFC95116C8BULL, 0xD90EBF47D2CFF593ULL, 0xA623E9E443B7CAA0ULL
        },
        {
            0x6380261AC51471E5ULL, 0xCB822B93AEC69413ULL, 0xCD6C1174EC10396CULL, 0xB035CBC9FD7267F1ULL, 
            0x05AD822D8CF046DDULL, 0xB16787B11F097E92ULL, 0xEEAB606C6717817EULL, 0x93A732BEC1878A07ULL, 
            0x48CE7BE34DBB22AEULL, 0x93094089648D20A5ULL, 0x55FE587222EA967BULL, 0xE1A35AE3F335BDB9ULL, 
            0x35F79318E36897C9ULL, 0xF717AC01B4DDCF52ULL, 0x95F5C79D2212F945ULL, 0xA7D7EEC324D44D78ULL, 
            0x7D745A342BE1A59EULL, 0x216686E7FB0865DAULL, 0x54D46C0EEF5AD5C7ULL, 0x0821CAC5AEFBF908ULL, 
            0x8683E6F1D7C129F1ULL, 0xAE3A473C1D3BEABDULL, 0x825DC430D151FC64ULL, 0xA048411E9B8BF9D3ULL, 
            0x5298A803D31D2E18ULL, 0x75ED32F2C436CE0AULL, 0x36F6BD4F336322DCULL, 0xF386EB4B48E8CE15ULL, 
            0xFFF43712755354E7ULL, 0x592B083B6B2C60DAULL, 0xF0C4AE723248C810ULL, 0xB5AF29F8ED4A9D2EULL
        },
        {
            0xDEF8CC79D284549BULL, 0xE431CE9BA6B32FB4ULL, 0x3A3AC549038BBB81ULL, 0xDFEBCCD6D54380A5ULL, 
            0x16FE60A48739AB24ULL, 0x51644662EE7B1638ULL, 0xFB89A511F2745282ULL, 0xA6DE3FCB628897D8ULL, 
            0x39DD4A308099AA20ULL, 0x19C2F4497E7AD414ULL, 0x7D0F620486D465CFULL, 0x9CD626369962DBACULL, 
            0xEF809305A85FFF97ULL, 0xA4B2413CA16AA6E7ULL, 0xA5A785F7D880A97EULL, 0x8209CEFA3688A033ULL, 
            0x7B03190202541D1BULL, 0xBB5E08FF04D35EA9ULL, 0x77060FAE4187F065ULL, 0x91A3748B5F85B41FULL, 
            0x1527BE543D5570A0ULL, 0xF8140D4C1BB8E89BULL, 0x28A1816728B129FFULL, 0xFB753F32B4606435ULL, 
            0x5C1A93B64DA00D01ULL, 0x10975A68582448B6ULL, 0x19E89BB2EDC8C61CULL, 0xDCDE84DDEF2E4C63ULL, 
            0xA3A0F00CEE184D1FULL, 0xD1988F7A5D260EFEULL, 0xFFD9632C9071BC51ULL, 0x98F6EC0372B307C5ULL
        },
        {
            0x3B86BC8ECD17E4ABULL, 0xDEBC600A1B4276F4ULL, 0x90222CB7715BE986ULL, 0x87012CF53A367D76ULL, 
            0x6A378DABF2F31015ULL, 0xE859BADAFB2EF358ULL, 0xDAEB20DA79D2BE24ULL, 0x640A82B3108E6865ULL, 
            0x3794BCFDD265D108ULL, 0xA191EDAFC6479195ULL, 0xA2C3D3E375E95E20ULL, 0xB27AF55A5827AC2CULL, 
            0x129F57659B413F94ULL, 0x25138D8D643AA99DULL, 0x50909105F051C125ULL, 0x32F3896B01697CD5ULL, 
            0xE47B761DAD35C7E1ULL, 0x3129263AA2B1EF6FULL, 0x92F50269D649CBD2ULL, 0xC6EBC1D593953CE8ULL, 
            0xAB032C8080F0B87FULL, 0x4690BE9577A889EAULL, 0x29ECB6CA4D38AE08ULL, 0x9F3C91BA0336C449ULL, 
            0x5EAAAD8A4538441DULL, 0xACFA436CA9BCED5FULL, 0xC17ED3C2C58FDEA9ULL, 0xD5A0D75FD7C44859ULL, 
            0xDA5BFAF00945F02DULL, 0xFDAB30ADB52FC7F2ULL, 0x387ABC228354828FULL, 0x46A946527B84517BULL
        }
    },
    {
        {
            0x085E4AA19B316C34ULL, 0x96BB6C2DEF528115ULL, 0xB444488E92A0C237ULL, 0x496179ADCDAB57E2ULL, 
            0x8DC8A9F2A2813893ULL, 0x7F2070AAD81E684EULL, 0x721BA7A62B196C5AULL, 0x102BB7225EF6EA48ULL, 
            0x4E5E9305BF9B5263ULL, 0xA5C7698BBBF6C59AULL, 0x118DA4168EE5D177ULL, 0x707B9355A183B010ULL, 
            0x9B98047672F3629CULL, 0x74694A32BDF62943ULL, 0xA87850FF8B11719AULL, 0x83248A6D274EBDF8ULL, 
            0x02D4319C228C46EFULL, 0xC3838E116C1F4E90ULL, 0x754D5F86F0B4F735ULL, 0xEED45AC52A9AA421ULL, 
            0xDCD51FFF4D4D32D2ULL, 0xAFB7162B8BAF5646ULL, 0xF110403232DCDA67ULL, 0x00D47BEB3808EE30ULL, 
            0xE80968E130691E1AULL, 0x8AC41335E87FFC0FULL, 0x8B7FF849C651CAF0ULL, 0xA5ED4EC518BACCA1ULL, 
            0xC610FE70C31D72EAULL, 0x909661F596C31C85ULL, 0xC40A15FF62A4B45BULL, 0xEC6C760CABA239AEULL
        },
        {
            0x223FD4FFAA3CAD93ULL, 0xC1A4325F9EEC0550ULL, 0xE7C8E497BC8A79BBULL, 0x2BF1CA386A5E62E8ULL, 
            0x658B091A5CC70272ULL, 0x15F858084EFC0ABDULL, 0x5A2D7265517C273EULL, 0x04B0A2FC5846A74EULL, 
            0xFC2D203BDE605522ULL, 0x0176A170BC6E2137ULL, 0x45CF2D3070537E58ULL, 0xB5642C7C7F4779B4ULL, 
            0xD3DB78B986734152ULL, 0xAC693A9C95A51626ULL, 0x10A14AEAB0F4F309ULL, 0x4E26A4DC79B4C4D6ULL, 
            0x37331612D91597A4ULL, 0x0A8A1F187499886FULL, 0x3AA96CD3C26FF728ULL, 0x38354C0C218087B1ULL, 
            0xBA5528A791700FE1ULL, 0xC9D8EB4258E73595ULL, 0xB9AA959E539F9373ULL, 0x82E6459C7251F310ULL, 
            0xFD78754CBDC40E57ULL, 0x1464578CA4556719ULL, 0xBD58E6DAE69CED92ULL, 0x2DB3E70C9CBED98CULL, 
            0xC18D8ED0F2B13B6CULL, 0xCFF5DE4B8E82D233ULL, 0xDED1FA90B31BD8E9ULL, 0xF43631B4A08D02BBULL
        },
        {
            0x2548A8D929482C75ULL, 0x8F7D1EC270B9E8A9ULL, 0xA8B6B15CFA688128ULL, 0x60EFB8012AE5389EULL, 
            0x412DCFFF344B69A5ULL, 0x7DD11B8C71BFE587ULL, 0x8DC2D519450A2802ULL, 0x26F12E6D51248F16ULL, 
            0xD5E889D7F3E98F43ULL, 0x499B49ACED111B83ULL, 0x2EE01FEE84B31E5AULL, 0x1E2EB9C50907F128ULL, 
            0x0E167692D0C18DC2ULL, 0xAB8A328E353B15DEULL, 0xBE37B9E6207059EAULL, 0x86CE7E3FB0F08548ULL, 
            0x4FA516653868E68BULL, 0x7F0B8D7968E1D10EULL, 0x3C5E65C535860410ULL, 0x99031E012A5C4AABULL, 
            0x0A1989791FD0D66CULL, 0x902700C120A9FDAAULL, 0x64FE053A08DF9E7EULL, 0xA32F23A1919A77ABULL, 
            0xF3AE9FB0718C713DULL, 0x8E65618643DC66ABULL, 0x00EF03C0F4BAAC6EULL, 0x54B4AA842D84CCEFULL, 
            0x7D4FD9B078A6290BULL, 0x8DC36911476BF240ULL, 0x50F80DD78D1E4E5EULL, 0x126CF20EADC56AB2ULL
        },
        {
            0x896166A968C43674ULL, 0x4C403EE6B20DBB15ULL, 0x9FD7E3A24E6D1CEFULL, 0x6301FB81F8C02142ULL, 
            0xFCBF8F6683D7341DULL, 0x9576CE977A37F5E4ULL, 0xC15C1785B2A1590CULL, 0x862299F760BFF1FAULL, 
            0x6CD41C8B3020561FULL, 0x915F22D64D457E20ULL, 0x95813A41B3DC6AC2ULL, 0x8AEA00F4E63DDACDULL, 
            0x03E4F78A49666581ULL, 0xB50C1C6363A99B00ULL, 0x17DE41535E17BE4AULL, 0x51A096050E779100ULL, 
            0x77FCC79C6185A672ULL, 0x476BACBE7C2A203BULL, 0x148AF658A8438583ULL, 0xC3E66912344B85CFULL, 
            0x1716830D6543E3F1ULL, 0xAB98839411A8ED84ULL, 0xF08C8D1B43F90126ULL, 0xCB604E586819E444ULL, 
            0x66AC6E367ED591FAULL, 0xFDBE5351893B60C4ULL, 0x219DDFF63E46C862ULL, 0x31E14B7752525B77ULL, 
            0x55B9D1E23CA0FC99ULL, 0xF4A0DFA282A72809ULL, 0x6B5C03171B5A6376ULL, 0x217CEB8D29002E34ULL
        },
        {
            0x6D5CE1855EE014CAULL, 0x4DF60DD28074D9C5ULL, 0xEE5B7427F75F7310ULL, 0x4C9D0CEF6450790CULL, 
            0xF55CF736FFB77A42ULL, 0x803DB2EFDB171D49ULL, 0x506D5C4EC4A28ED8ULL, 0x61275E1F3E93F413ULL, 
            0xA17086B996C145F4ULL, 0x76B11ECE3B5C41FCULL, 0x52305608B8C4C9E9ULL, 0x8BF1598537031A07ULL, 
            0xD1A12C2559C3B3C5ULL, 0x7D8B641780277435ULL, 0x547C41A977EBE57AULL, 0x9418F57EE7C1D207ULL, 
            0x302F90022E399BA6ULL, 0xAEA627BDA429BE3DULL, 0x849FB3DCD625EF5AULL, 0x3B6AA26591B02C9DULL, 
            0xC435EDF823C135FAULL, 0x5013EE14A9665A1DULL, 0x6283F3872983473EULL, 0x87CB2FC6C32B0F6CULL, 
            0xF45DA77DEA8995D7ULL, 0xBF056D90234BEF62ULL, 0xC3B7204BEE63DB6FULL, 0xD9F1D37C014813AEULL, 
            0x0E33B9623FF78287ULL, 0x854DE5552BCEABB6ULL, 0x85BD942CC12BB020ULL, 0xF1CCE694D809F2F7ULL
        },
        {
            0xE2BF11AC10D2FAF7ULL, 0x6D6F24B71B55D703ULL, 0xE73189F3EF9BC16BULL, 0x525C4462D9774775ULL, 
            0x002C51D4BCAD179BULL, 0xECBB86956C2024C5ULL, 0x3E27C193B9D3A264ULL, 0xA132992D12C6F546ULL, 
            0x9297308891105B4EULL, 0xDB4D04D7C0E11945ULL, 0xB81E4F2F3E18EBB4ULL, 0xA0A9E094E5440274ULL, 
            0x27C7C2B6A2634B32ULL, 0x3583595E7F2CBFF7ULL, 0x178700741AD2C46DULL, 0x7F583F520BFB8E96ULL, 
            0xACC61B67BE6097B7ULL, 0xEED5A07F9DF8EDF3ULL, 0x5F07B883C7649BF3ULL, 0xBCC46EE7A78229C1ULL, 
            0xF5728F65B12D37DEULL, 0x9E19B29171E668DBULL, 0x700094E59BE54EF3ULL, 0x0D91AB1C695FEAD3ULL, 
            0xBD57D02E57D0B3A4ULL, 0xAC75C6926B17149BULL, 0x028051D98165E4B9ULL, 0x035EF37BF9616983ULL, 
            0xC9DD1AA6E85D13EFULL, 0xC10E3E679038EDD4ULL, 0x03EFC8EB43FD2A9CULL, 0xA237FBDB04C7AB90ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseBConstants = {
    0x8FB8A0AB1E479CB6ULL,
    0xED176970F967F11AULL,
    0x20689B1E69857D5AULL,
    0x8FB8A0AB1E479CB6ULL,
    0xED176970F967F11AULL,
    0x20689B1E69857D5AULL,
    0x872B5BFF8A044930ULL,
    0xC18E0781AF7C0CE6ULL,
    0x07,
    0x88,
    0x08,
    0x84,
    0x17,
    0x9B,
    0x65,
    0xAD
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseCSalts = {
    {
        {
            0x3DBD5FDF5025C74CULL, 0x0ADC61255400386AULL, 0xA197F36C37F433A0ULL, 0x4D7E8AA1F9128C5BULL, 
            0x29EB9F2FDDC8AF43ULL, 0x10CF98C2FD10256BULL, 0x9D3737290E7A0BE6ULL, 0xE453D79C71B38234ULL, 
            0x6CD0F51AE1C8AEA0ULL, 0x6D9806186D4F07B0ULL, 0xF0E9ED03CF3AA3E5ULL, 0x2F2F4A402929227CULL, 
            0x11CB2C4D610BC926ULL, 0x695ED309CD4641E9ULL, 0x64A19E8DDFE200B2ULL, 0x3DB8EB831FEF5A20ULL, 
            0xBBEC41F6FE748BD5ULL, 0x0F400897B1DA0AA6ULL, 0x2F076790555F704FULL, 0x4CB668DD8EA9AD28ULL, 
            0xBB70C3ADE5D62108ULL, 0x6995B7F00BF16857ULL, 0x12C1502A7950031EULL, 0xE5C2A3B8C3984018ULL, 
            0x089CD84D0E814773ULL, 0x6D8076E5BF4BDD74ULL, 0xF32504C39E72486CULL, 0x17C3066FFC9DE28CULL, 
            0x063BE73AFD975F35ULL, 0x845038B2B2B97987ULL, 0xC8B8C891B3031F3AULL, 0xE0904B057F51A932ULL
        },
        {
            0x369623C4C044A994ULL, 0x0F9AFB3A09C3E65DULL, 0xA5C9D66EB946D239ULL, 0x7CFA7DEA2756FA0DULL, 
            0xDC36F26263C864FBULL, 0x26335F639D48E34DULL, 0x26C1A92DEC7CE907ULL, 0x9779C3BFDA4FF784ULL, 
            0x09FAC0C606AA6045ULL, 0x909FCBEE53D72253ULL, 0x3F04CD4F41AF6D6AULL, 0x6BC53497022862B2ULL, 
            0xBF57AB04128DA9CCULL, 0xAFEEA3ECE28D6BF8ULL, 0x8C46EA4F9469B992ULL, 0xA362CF78AB404D6EULL, 
            0x3C58AB966D4554C4ULL, 0x3D3C400242C16088ULL, 0xB78AC2424832D6EFULL, 0x10E9E40498612446ULL, 
            0xE13900EA56DD67B4ULL, 0xB5585930EEF69F42ULL, 0x4DB054C3565B57F2ULL, 0xF8072968E38C75FFULL, 
            0x4719429C82371B54ULL, 0x981ACD1006AB3EB0ULL, 0xD004282FBB6C17F7ULL, 0xFCE6FB0EA97AD05CULL, 
            0x0854AE63E8378615ULL, 0xF3DB0F7026244ACFULL, 0xB26EC8604FD26A77ULL, 0x187F79CB1B56D398ULL
        },
        {
            0x20B2D73C80E1F851ULL, 0xA9997ED9891A25DBULL, 0xB87F444CA4A68F5DULL, 0xC76347C553CAA579ULL, 
            0xEC11DB11D57D8AF7ULL, 0xCBA431C1024A5C98ULL, 0x4B98A320535DC9FEULL, 0xE3C3103C46819965ULL, 
            0xD8EE58F84AFF2C5CULL, 0x021FC454FE6730B0ULL, 0x0C9937FCC37E113AULL, 0x18EC22411477FE05ULL, 
            0x5455CA433AB10164ULL, 0xE6EF0718D06DB9A7ULL, 0x6713BD4221EBEC63ULL, 0xAF41BE83FFFDEE00ULL, 
            0x00A75AA099241F5DULL, 0x5F37A5CDEEF864D3ULL, 0x45326BA619C1AC0AULL, 0x724774390DF84BE7ULL, 
            0xCD0A04E605D4E86DULL, 0x545A970EE0308879ULL, 0x2D34709358B11A69ULL, 0x3ACDB8204C0DA1B9ULL, 
            0x6895304E93A69065ULL, 0x7376A6AB258B7A5AULL, 0xB1B4D59C60263E8BULL, 0xB7B92BE153E965A7ULL, 
            0x44BDE6DF66E5D847ULL, 0x7253F3B288D9C150ULL, 0x9B3A1434A7CB3B7EULL, 0x06E4BC528F409077ULL
        },
        {
            0x87CB374FC0C54137ULL, 0xE2EDF62299558300ULL, 0xC60C168B5DC69B65ULL, 0xC303AB6E05E4B09AULL, 
            0xC2A7D676C9435FC0ULL, 0x4075923D731F9651ULL, 0xA799B1664D76C05CULL, 0xF78BC88CF4C0B0D7ULL, 
            0xEB664B0D22A598CFULL, 0x44FBB6520367CBDFULL, 0x9C0FD36DFB235346ULL, 0x6A5914D96277C114ULL, 
            0x2807CAEABAB058DCULL, 0x6CF79C79777E24B1ULL, 0x0DE1CAA96751B2A1ULL, 0x406FC5910BCB1636ULL, 
            0xD389BCE0F77CBA46ULL, 0x1837917BAD9C9F6BULL, 0x28D709DAB04EE763ULL, 0x09EBCFE73742C10FULL, 
            0xF271AD5673C1B9F4ULL, 0xAADC96741A86B6E7ULL, 0x7D229D9DDE38B2BEULL, 0x1F12FAB50DE0465EULL, 
            0x61574AC63B6EEE4BULL, 0x648142878C4E7E6FULL, 0xE5EAAC5B348AC057ULL, 0x148CBD93D9E09514ULL, 
            0xFB2DC733F538F600ULL, 0x53EF3EA224C7C3C0ULL, 0xE8A869C544440191ULL, 0xC838B484520606FBULL
        },
        {
            0x058FD4CC1860E5A1ULL, 0xFDFB645310F4680DULL, 0xBA0096033A358AC2ULL, 0x101A4C17062939A1ULL, 
            0xDF489AC580E0BE14ULL, 0xF1FA447B0597AFBCULL, 0xB0E40AC9C04D7C76ULL, 0x47C5EA6D5C680FAAULL, 
            0xF44A8192037A7524ULL, 0x68E0B0AD889760A0ULL, 0x530C989898545184ULL, 0x204E394F443EC0E6ULL, 
            0xB658C05DD21ED0B3ULL, 0xCCE0AD71148B3E75ULL, 0x03EC3EEDC37B49E8ULL, 0xCE38454895536975ULL, 
            0x78888B70BE5933B9ULL, 0x9A7F4E88326C0B89ULL, 0x014F71BC9B7ADD26ULL, 0xBA25AEC749B8E4A9ULL, 
            0xD11FB1DC920B238FULL, 0x498F501A984D6C8AULL, 0x16BEB494F8A564D0ULL, 0xB550597A40BDE79AULL, 
            0x1419FAC603223CF7ULL, 0x9D19AA2D45A2AD96ULL, 0x9389594BB4731673ULL, 0x96318F40E6617241ULL, 
            0x3DDA59DA2DA6F62DULL, 0x734A9795E7CA30FAULL, 0xDF5194D511E46BC5ULL, 0xBD794CF258CB676CULL
        },
        {
            0x419E92F514A95599ULL, 0x277B51255F134F17ULL, 0xDE7ADEA8D509FBF7ULL, 0x9F843F3C3E9B8A4AULL, 
            0xA45EA0DE4777D230ULL, 0x8E60855EE71CDD9FULL, 0x6540A7EBB9E862AEULL, 0x9F4A3869C6D5F13CULL, 
            0x58AA1BD41ABF796EULL, 0x17A2622EEC1CEF52ULL, 0x900DEB249EDFAF67ULL, 0x92ED3AD1D3AC885CULL, 
            0xD83F4FCF620EB52EULL, 0xA2BF2BA3C1682319ULL, 0x629490B944199D16ULL, 0xD2DF0C7E014FAD4DULL, 
            0x92101829D5B69542ULL, 0xE871E45DDCC5887FULL, 0x860951E9437FE920ULL, 0xBC816C42E04E683FULL, 
            0x46E567D272141DCEULL, 0x3FF02BB03945CD5CULL, 0xD5F21104ED2B6014ULL, 0x356803B72C532973ULL, 
            0xE75CE30F69CE9937ULL, 0x128C93CAAA83106CULL, 0x8F991BBD5185C2DFULL, 0xF54FC328AA0C4450ULL, 
            0x2B15608F1040C353ULL, 0x57BECD64B6D0B568ULL, 0xCD29F87E932B4C67ULL, 0x4B7743AE9796BEAAULL
        }
    },
    {
        {
            0x656796FAE0440557ULL, 0xEF24B711309BE953ULL, 0xC49C6A85761C9EACULL, 0xEDAB96B238A90313ULL, 
            0xD78C1D365BA917B8ULL, 0x4C0CD09EB4696A27ULL, 0xCF97A7F535A4360AULL, 0x64401A6FB5C87892ULL, 
            0x750BD9B277CD37FEULL, 0x22B89B0DCBFF21E5ULL, 0xC630BA296735384CULL, 0x1227E4C102CA7ADDULL, 
            0xD6EE7922A12DC5C6ULL, 0xADD569A129BB9C87ULL, 0x3B89D9BFC78ECBC3ULL, 0x441D06699F279B62ULL, 
            0x6F2B01BBBFB4DC65ULL, 0x757E717985FE0ABDULL, 0x15E7288FD9538F19ULL, 0x4C2E920880EB9C26ULL, 
            0xF75EDF80526D2B3BULL, 0xCC7B733718CE20C3ULL, 0xD67BC8606A3926E4ULL, 0xD4F537D57031A906ULL, 
            0x14941E672FD4F8DDULL, 0x9BDF188095675868ULL, 0xD6ECFC0831D8FAB7ULL, 0x7D3103BB3B1AC011ULL, 
            0x4F3CB5B593C70DA1ULL, 0xAD3A7FDC540A3269ULL, 0x813E3EAEA250972EULL, 0xC0C0502A8F02AB6EULL
        },
        {
            0x2171763F7393234BULL, 0xCAB4353F9C0C7049ULL, 0xEC8BD7B49331C244ULL, 0x07B44CA51879F6C6ULL, 
            0x4F1A1F29CA4D8A8BULL, 0x14D904B911EB902DULL, 0x6E34263E43904BA1ULL, 0xF9BF408787F7F338ULL, 
            0xAB906CF092841CC7ULL, 0x043022581AD2DED0ULL, 0x28CA0718B8B21181ULL, 0x14A913BF5F670D03ULL, 
            0xC78B523721709265ULL, 0x546E7BFD0C227B13ULL, 0x59D284966695620DULL, 0x15FE629E1E26556DULL, 
            0xF67F9A4CEA711B03ULL, 0xE68B6C8BB0C35F60ULL, 0xF1D8106C4C8C4284ULL, 0xBBA184DEC2FDB733ULL, 
            0x0BC8DA5342FF4555ULL, 0x02E57B8EC1C7A0C3ULL, 0x93A38BE3E11100E9ULL, 0xCCF5348897594387ULL, 
            0x314CFB12BC563508ULL, 0x8253313B8515A56DULL, 0x2A21FC3502E3674BULL, 0x07DD34A7F55AA4E9ULL, 
            0x10B5F24AB9CE239EULL, 0x9D3997236E51080BULL, 0x1A7CF2931369A025ULL, 0x213DA3675AC371CBULL
        },
        {
            0x5F99F94FEBCAC278ULL, 0x50CD37C309CD9003ULL, 0x50207EB2C4909422ULL, 0x143C3EB6D9769FB6ULL, 
            0x0AA9C3B6F15E4622ULL, 0x6CB9D60E4EAC424AULL, 0x4640AD264BF2B85AULL, 0xAAE54B355D4C445AULL, 
            0x0CAE22595F463A99ULL, 0x0229E014BA199D3BULL, 0xF519A22E4F65EA0CULL, 0xB54B22C5CC29113EULL, 
            0x0A39ABCE9CA5A979ULL, 0xEFC4B7E3CAE8EF37ULL, 0x02C973895517CF1EULL, 0xBD5D60E439F86E42ULL, 
            0x82B36638AA318FECULL, 0x45181D24B3B18D91ULL, 0x6626C2E75365EDA9ULL, 0xADE5EDF7EA784DC1ULL, 
            0x32D988DD918EF592ULL, 0xA5212F81C470F46DULL, 0x74BA1F57EB40969BULL, 0x8D7D9AF6F389B4EEULL, 
            0xFFA2914BB724309FULL, 0xD2A1C11297E0F2C9ULL, 0xAE2188AD4AE65D63ULL, 0x474E317990ED720CULL, 
            0x18434003BD8C957AULL, 0xDBEC2C5708177B31ULL, 0x079652D4E5A165CAULL, 0x21790227EB0EB8F0ULL
        },
        {
            0x37DEA4003A56CA66ULL, 0x3A0D495255D923A2ULL, 0x513ECB06C15BD403ULL, 0xEE426AC36E35C84FULL, 
            0xFBF7AA2B857E14A5ULL, 0xBD5BAE770D5DF27FULL, 0x579900E61307BB51ULL, 0x070325A9E7F01A67ULL, 
            0x8091CB67D4EDEB17ULL, 0xB2983A6740D4F203ULL, 0x055DA756565472AEULL, 0x7245E8821CFE236DULL, 
            0x9E31E73113ED5B5CULL, 0xB87FE16861787B1EULL, 0x7F2BE43702ECD412ULL, 0x3AB0127F1F2F88ABULL, 
            0xF49B4D62EF046C3AULL, 0xF427EB961A10CD13ULL, 0xF8917E4138BD5C78ULL, 0x6A666C85A051D14FULL, 
            0xC8B3D25C44506048ULL, 0x3E661211F88B7D69ULL, 0x431129004FDA724CULL, 0x9F56142A77DA4381ULL, 
            0x546EB4048E464405ULL, 0x31B5CA601CFFF1A4ULL, 0x121679F085A5AD64ULL, 0xC4CADD46B4BE646BULL, 
            0x31B3F5A62E12FF72ULL, 0x9DF3D8F009CAB4DDULL, 0x8F66EF49959E9882ULL, 0x0D2E45E5E710A679ULL
        },
        {
            0xBBA19C2E3142B4EAULL, 0x98537E9495E6FE5BULL, 0x784E31F571B12271ULL, 0xACD48417BFB4FF53ULL, 
            0x8519512944E5FC5DULL, 0xC211EEE2E724B144ULL, 0x4CA99266A7FE4BD6ULL, 0x814E25A6EA411739ULL, 
            0x87F62D22AECF9F81ULL, 0x034B1316A7425B19ULL, 0xCFF7F97C6291059BULL, 0x57604FFB7B23F33DULL, 
            0xFDC6C7CA496A7AE7ULL, 0x551C45EF22A20143ULL, 0x7086E6BC3E668B28ULL, 0xB7BF97D8127F71D7ULL, 
            0xA429BBDE1BC502F9ULL, 0x3C021482DE564F54ULL, 0xE106D2EAB77703CAULL, 0x286F68793C2026FFULL, 
            0x55A5AD44F058A9E7ULL, 0xBA92CE1C44A3E3EDULL, 0x715525D0947047B6ULL, 0xFCD2C6683758E321ULL, 
            0x5732D19ACD8780BAULL, 0x1CE6A9DE62A17C70ULL, 0x8B916189504AD10BULL, 0x442F4C4C8ADD59BCULL, 
            0x1603F869A284B2AFULL, 0xB4E332805414962DULL, 0xB25D1DCD78A3F15FULL, 0xFDE56D5487CBC048ULL
        },
        {
            0x509BE41D74A671A2ULL, 0xA63201FBB3C4DC34ULL, 0xD0B38A569C6912F5ULL, 0x03D45264C85DB96EULL, 
            0x8DD320FE8602C13FULL, 0x2E770EFF85F508E7ULL, 0xB2340555A583414BULL, 0x0A1EC9E29D5BC846ULL, 
            0x4155A22A5A339B72ULL, 0x50FCF87E4E564BDCULL, 0xC97F4EECB52F1104ULL, 0x2E192166A14E9E6BULL, 
            0x935F08761C5784E5ULL, 0x61F5BD6573351D9DULL, 0x40C802D578A08DC0ULL, 0xA4D079870DBF9C2BULL, 
            0x76561A3A251BDF04ULL, 0x796EABAE35790EBDULL, 0x8C38964D521F8397ULL, 0x915153620495F7B9ULL, 
            0xA6B9764B931B5C37ULL, 0x7E54F556F8546F03ULL, 0x4BCAED981D7F0E6CULL, 0x69B5B5D36A77D7A4ULL, 
            0x27053FE3CADB8C7BULL, 0x054B8CBEDF4AC953ULL, 0x4DB047FA57A7646AULL, 0x71AFA3526F485D8FULL, 
            0x0704BC25448EB76AULL, 0x1DD07C6143EEAB2FULL, 0x33FF9B9F373C5E8FULL, 0xC5DC149827EA1F50ULL
        }
    },
    {
        {
            0x9EFAAB3F539D3811ULL, 0x518A6DF54DAB2894ULL, 0xCC4F0B5E8585E84BULL, 0x40DFABAC9C81639FULL, 
            0xF0FF949FE66CBC6CULL, 0xAAF9F565E8284B85ULL, 0x1F62FDE8A5A50437ULL, 0x7722795DB3CCCAF8ULL, 
            0x4823CCF9C051F246ULL, 0xC7AD50FF1E978151ULL, 0x61E4B4C7D7312466ULL, 0x80213B3BD7235E1CULL, 
            0x68953F067B8536B5ULL, 0x57C245E4A2E7B0FEULL, 0xC1A08E7CB04FC16CULL, 0x0EE7D80124D85AB1ULL, 
            0x24A1A6B710E0ADE8ULL, 0xDF865A2302EA9A00ULL, 0xFB86FE2233FE954FULL, 0x527BE99A4019E1CBULL, 
            0x3328C2953EC51E40ULL, 0x41A2EDFAC34EEB76ULL, 0x3ACF86769113571DULL, 0x6EA7C1A127B7D5E2ULL, 
            0xD85C5C5118370EF5ULL, 0x19FC3D9DEFB61EC7ULL, 0x40A01066F40AFFE0ULL, 0xD47BC7E298CC603BULL, 
            0x89725CE7F2EE2DE7ULL, 0x5E118D7344C9975DULL, 0xD85D375B7908FC06ULL, 0x19A4FA391DAF4A8EULL
        },
        {
            0xA39EC764CB691F06ULL, 0x25F4F771C741FCDCULL, 0x6FB052A42D00D844ULL, 0x178507AE1168A7D0ULL, 
            0xED27F522A211A2FAULL, 0xDDBAA7A15C71DCBBULL, 0x91F9156DE56165F3ULL, 0x3BDB52EF2812BC8FULL, 
            0x4740D56D9C76D3EAULL, 0x671CC6C3AE31B8CBULL, 0x816B127008ED358FULL, 0xEF03796FC14181B0ULL, 
            0xE9EB04DE56474068ULL, 0xE2C91A2CC1E7E009ULL, 0xCB94FB9D5ABFBE16ULL, 0x0F46E3670C630F26ULL, 
            0x8219E6476795690CULL, 0xE2155F7C0F902FD6ULL, 0x491D0299381AC180ULL, 0xFA60336828064749ULL, 
            0x96D60BD24D2B5DE9ULL, 0x097F1B1A81C52ACFULL, 0xDF5FE562CBC389D7ULL, 0x1625DF17A5893ABBULL, 
            0xFF14A9EFD43262E4ULL, 0xCE6EED27008D01C9ULL, 0xD4D06AA468ABAD0EULL, 0x2A9456C76BC33A62ULL, 
            0x9072B6F54B2A931BULL, 0x9046683D97E19636ULL, 0xBF7CD28B70985E2AULL, 0x404CCBE1B53D96C9ULL
        },
        {
            0x6A45A1488DB35F59ULL, 0xBF38DF7C304BA5A8ULL, 0xE75A508AE7E7136BULL, 0x998F4DCD810D13DEULL, 
            0x2E5856CDF2FCEEF6ULL, 0x3BD38ECC6CEEDA47ULL, 0x946780803990EF82ULL, 0xBB6E31FAEB803EB2ULL, 
            0xC84B63E28A1EB2F5ULL, 0x5314185EF39B7658ULL, 0xDF4C2778078D5FC0ULL, 0xDEAB0C91C0CB9DF5ULL, 
            0xAAD2781980D32DFCULL, 0xC91665C32B7D483DULL, 0xBF283655F32676EAULL, 0x582E8443DE2D243FULL, 
            0xDDD913AB74A750B6ULL, 0xE4F5F642F8282BF5ULL, 0xD53BB3699294B358ULL, 0x14C2BE48A59686FDULL, 
            0x007F9BA2AA58D8C7ULL, 0xC833F4CB8A73013CULL, 0x743A0584809825A4ULL, 0x2AD680ED5CF17191ULL, 
            0x376EAC5DA7193ED2ULL, 0xA3D408A473B8F2FBULL, 0xCE30737B5C5A5D71ULL, 0x28461762D41508DBULL, 
            0x9028C219B8AEBF9DULL, 0xEED6FC740FBA35A9ULL, 0x80F33E33F27BD32FULL, 0x2226FEC9946F475BULL
        },
        {
            0x20D12049030F059CULL, 0x55F2F08A586A8DDDULL, 0x30E51B45D10B4514ULL, 0xF7FEF2DCF57737E5ULL, 
            0x118C48334EFACB84ULL, 0xFFBD8B18E72AB5DFULL, 0x741F4E3B46841E46ULL, 0x9D86C662469D763BULL, 
            0x2BFEFA188A803FE4ULL, 0xA060D87E828AC460ULL, 0xD99DC500C411EAEDULL, 0xBD95986E9CFBD32CULL, 
            0x1FADD19DF76FF93FULL, 0xC10DF76370326037ULL, 0x1E6DDEC7139CF091ULL, 0x29B09A0CA66ABE5CULL, 
            0x2E43AFEA214AE7D6ULL, 0x29F532ED754B772FULL, 0xBE15551A987866B4ULL, 0x40C1F994B6E246B5ULL, 
            0x258087DD6C444344ULL, 0x8D15C0FD9A97362DULL, 0xC1E318F2768AFE41ULL, 0xA444FEB9E5F82C87ULL, 
            0xCE73562D41061CBEULL, 0xBDD57C44F136514FULL, 0x4D550C0E1DADEBAEULL, 0x5DE50AD1293BCA4CULL, 
            0xF1973D9FA202AA25ULL, 0xF9B6BBF82BB99FC9ULL, 0x0E96841FD288B435ULL, 0x614D12C6A58C5EA4ULL
        },
        {
            0x21618F8715B62AD6ULL, 0x62617602AFDD4D18ULL, 0x16B2F817628B5766ULL, 0x5F65EF5D2BC33C3FULL, 
            0x9809EBDFA1B0DB20ULL, 0x9A247A6A53D96F0CULL, 0xA6CE7E96A7D8E95DULL, 0xB6C343E41C6FFD3FULL, 
            0xDE0F14C39680741CULL, 0x966DCFE862AB8CCDULL, 0xC8A4728D0ADBE36CULL, 0x061EAC76CF80B3D9ULL, 
            0x0298ED44965FC1E1ULL, 0xC1FC474A27B75F58ULL, 0x80C9BF7E488A2D83ULL, 0x8C254E18C462AB20ULL, 
            0xCF02D5C7FFF37903ULL, 0x67A8FAF46F81FE5CULL, 0x87628AFF60CD4E40ULL, 0xA046E0F0B036CC8AULL, 
            0x95881013BA88A5AAULL, 0x4DD590D2ACB1AC84ULL, 0xE983E6F8202F499EULL, 0x0844F6860FADFF2AULL, 
            0x90E501488D323E66ULL, 0xC582795E5F88669DULL, 0xC1D622D9044EE758ULL, 0x1347D39BBD9F2BB1ULL, 
            0x3E2F50AC0BDE305FULL, 0xAB68B46C06A4B088ULL, 0xE68588AF3866DC89ULL, 0xC38E5CA704A36FAFULL
        },
        {
            0x6C5479030B7A0EBBULL, 0xA076AC7AC71F9CD5ULL, 0x63CDF7ED674C8DFEULL, 0x30F5F0E1F1084FF8ULL, 
            0x6CAE47FAB3A75ABEULL, 0x0FC8CA525675E4A7ULL, 0xF751A503E4D7B996ULL, 0x34538F023551C38DULL, 
            0xE44F61F6198C9EEDULL, 0x2B4ABAC9F371658DULL, 0x9212BB03463E5B66ULL, 0x0CFBB6DA40F45CF4ULL, 
            0x1770426C1B30C299ULL, 0x086860FC28BDCE82ULL, 0xFA2A8D4F44871430ULL, 0x37330C85D5941F6EULL, 
            0xA0C5E2E0A8A02770ULL, 0x02870B988A3C2DE7ULL, 0xFD4A8CEE7A8F8D87ULL, 0xFCCAA9B0CAC0700CULL, 
            0x199A0EEFC09F19C8ULL, 0x042D5DD6191644E9ULL, 0x78F26B7329C5BB4CULL, 0xF1D0BC69734994FAULL, 
            0xCFF2F6B29AFFA25CULL, 0x0CD5EE06D9962F9FULL, 0x3B19E51C96CFC228ULL, 0x6BAFED9C68924E16ULL, 
            0x944B8BBEA7985A69ULL, 0x8E87A49495B1FB4EULL, 0xB7F05411CC0A5227ULL, 0xE79CCDF6C0F2F608ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseCConstants = {
    0x176DA7229541D709ULL,
    0xF8EBF778930D6621ULL,
    0x366A08DB29B56868ULL,
    0x176DA7229541D709ULL,
    0xF8EBF778930D6621ULL,
    0x366A08DB29B56868ULL,
    0x1486096BE1006F10ULL,
    0x16EC7F80E66FA934ULL,
    0xAF,
    0x5C,
    0x54,
    0xBE,
    0x8C,
    0xA7,
    0x3B,
    0x15
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseDSalts = {
    {
        {
            0x0A93F8938EEB034BULL, 0x777B6BA2C68ED4AEULL, 0xEBD2942AD63512F2ULL, 0xDDD5680999A118ECULL, 
            0xCE8E0AD455362A62ULL, 0x6F3EFA1576A2DCB5ULL, 0x38561ED6D651A99FULL, 0x76474642B855CF6EULL, 
            0xF5896A4B615A68EBULL, 0x3561ED536B260463ULL, 0xF37DDF3CC9438751ULL, 0x1A23410D89376BA8ULL, 
            0xE5A38F2D196A2519ULL, 0x527054FFF8165187ULL, 0x8B1172D3FD085444ULL, 0xD23B934B9FC0EFD9ULL, 
            0xFDBC337E1EE42085ULL, 0x8EE31767FF2980B6ULL, 0x21C9F97F594B2351ULL, 0xA6616E9E18FBC2B3ULL, 
            0x5A942654B205ECA0ULL, 0x1B8CDFF39E3F3924ULL, 0xBA8A79604701B94DULL, 0x8EBC6C17B2DB4503ULL, 
            0xE25EEDDB9D1D282CULL, 0x443C71E76ADD82EBULL, 0x555DD9F57680CB3CULL, 0xEC6D1CF911580A94ULL, 
            0xCFB74B98C30C44D9ULL, 0x87D34339A0EA6B9EULL, 0x8F833549A2687C9DULL, 0xF521B201C2526AC9ULL
        },
        {
            0x31BE7A5D313FF53AULL, 0x4594F41D0A916FE0ULL, 0x1A859782B083DC1CULL, 0x6D24288E271712ACULL, 
            0xEEEDC89EE5D09E34ULL, 0xA42F1713A4C29766ULL, 0x3A5920D8C874B3B0ULL, 0x5761E35A5CE97DD5ULL, 
            0xF7315C1B088A8B6AULL, 0x349C1939A59AE970ULL, 0xEA05BAE7B0231A88ULL, 0xF5F01241828A5BB2ULL, 
            0x534CD2A30A194C29ULL, 0xE3FDE0940A173B39ULL, 0x8CCC3F6F3532C5CCULL, 0x7530EC5BD32B3236ULL, 
            0xE29BE0CD1BDF8C23ULL, 0x86963A549BF8E41CULL, 0x4E1559D10AD79B47ULL, 0xE334372F6B9B22C2ULL, 
            0x86EC6DE3E5A49230ULL, 0xDE8AD487AF39BC2BULL, 0x345F649B71F24C3FULL, 0x5053EB53641D05FEULL, 
            0xF81B7FB42B07FD86ULL, 0x83D7AF2933DBA1C2ULL, 0x39C9A796B1B584E3ULL, 0x0DBC72DB874AB883ULL, 
            0xAAA37558D93B520DULL, 0xDC0AA264E4F6E5A9ULL, 0xD65AD62949A91D10ULL, 0x08C4FB0A7A41A3E1ULL
        },
        {
            0x995728E865A320DDULL, 0xE3F181C159F93AF5ULL, 0x652489437893D32DULL, 0x88C8F4CE3EA5418EULL, 
            0x73ED9DC1017118A7ULL, 0x0CBFF2AD068B7FBBULL, 0x1F46DCD142D1B3F9ULL, 0x0A1AE858F7EF7C33ULL, 
            0x24335CE734A2ED05ULL, 0x728C5843BE4DA013ULL, 0x44E760BA37B35363ULL, 0x24266A1D1194F6E4ULL, 
            0x3850D5EFBD20DAF8ULL, 0x694E2DFA7BDB2FCDULL, 0xCDC60EE9506D2885ULL, 0x001940F8AA8A32F8ULL, 
            0x62D379BFA5A989A2ULL, 0xD1BE40C50355DE30ULL, 0x3D76F18682D6E7B7ULL, 0x5CFC75FCB1D2EACFULL, 
            0xCF542D9C2A2528FEULL, 0xF0396477D7EB3FC9ULL, 0x5EB6C2C2CCCE3DC6ULL, 0xB73BAC00649FC53CULL, 
            0xB7C46EAE73CB4FEDULL, 0x6CE1E00C68CE2015ULL, 0x7D3989B6ACEF4128ULL, 0x67BB193400D5F154ULL, 
            0x5F9E054041BAC7F5ULL, 0xB30183035DB57D6FULL, 0x20A6E095DF4D118BULL, 0x1F5DF459EB670B9EULL
        },
        {
            0x3147749CDA9E23A4ULL, 0x83E223CD8C455B71ULL, 0x0B2C6BBF85D81621ULL, 0x7339EECF4A2B562FULL, 
            0x0B5D4E0E3DB48BB2ULL, 0xC85348FE4C176054ULL, 0x3FED8E021DFA814CULL, 0x63BC765C4BB0C99FULL, 
            0x725F4831FD509812ULL, 0x0E8710C7E6F6C290ULL, 0x4DA9E2BF2C219ACBULL, 0x559FE2B5C0BD929FULL, 
            0xE757BF4967576EA8ULL, 0x32E200E337170331ULL, 0xC66C81F5875FD9CAULL, 0x1A33D87AF277B8C0ULL, 
            0xAF3BF6FCE63E3F40ULL, 0xBB6C036B4BD2B5E6ULL, 0x7BFF63A46FC130EAULL, 0x9CFF72EC2FE5A025ULL, 
            0x5E858F79EE12CB39ULL, 0x132AEEBB7F6FA9A0ULL, 0xFCA316FC5F8A629BULL, 0x93B5332C65D7A8C2ULL, 
            0xC5A7362C75454CBBULL, 0x9CE811FC4D7CB351ULL, 0x70B3147239F5BE33ULL, 0x891653A809CD7613ULL, 
            0xB6715960316B5EF6ULL, 0xF3D8BC15E0954811ULL, 0x9C4F19F567A398C9ULL, 0x43BE6C48228BE71BULL
        },
        {
            0xB0BF3FE31C72C5B2ULL, 0x46610F1FDDF91FF8ULL, 0x5E9A8B1E24537ACBULL, 0xD874902989C1BDE9ULL, 
            0xF88620D1B2FA4946ULL, 0xB664B045B06196EBULL, 0xD91AB2D07CC9F2AFULL, 0x73891652F456C11AULL, 
            0x0C7922DD2DD9B8CAULL, 0x6153673C63FF361CULL, 0x583D50E870A60810ULL, 0x71E12C6FDF46BBBFULL, 
            0x88C587FF1EE2131EULL, 0x5CADE348EFF32BBBULL, 0x2BA36C7487871F2CULL, 0x5A6B41B32F4F5EE6ULL, 
            0x5ECD7A8BC74C139EULL, 0x494E05BE8177BD03ULL, 0x9741D419AB4B470BULL, 0x04043C82CFE0054DULL, 
            0x4EF4257BBCCEC32CULL, 0x4A3063A68987B108ULL, 0x984296403F107A82ULL, 0x30A3610B3F3C231AULL, 
            0xD2E8A921730DE644ULL, 0xEC67E5A906BF5903ULL, 0x36CF779DDCDFF44BULL, 0xC0311F495C7A1206ULL, 
            0x103D110D697BC774ULL, 0x2B86BD9C599E4736ULL, 0x5530628421F8538EULL, 0x546368CAAF12547AULL
        },
        {
            0xBD82485A0B037729ULL, 0x57FC04B7425CB325ULL, 0x6E575BFC809F8D3DULL, 0x18FEEE14A8AF123EULL, 
            0x5A1A288C058B3A60ULL, 0xBCE8BADA4F0B15BDULL, 0xF13E4F6462A34A16ULL, 0x8AA79CAAAD560337ULL, 
            0xBD2AB77E162BBC8FULL, 0xF38711C47FB53281ULL, 0x290D4949FF5CB89DULL, 0x9C53A063292323CDULL, 
            0x3C001265C8703B74ULL, 0xB5CF394BC152C756ULL, 0xCFB38723DFF486F6ULL, 0x5FE57DE203DE4D4DULL, 
            0x3087181D5FCEA1B1ULL, 0x0718BDB1F702EB5BULL, 0x7816853F6C8927EEULL, 0x293F336D2AAE9D00ULL, 
            0x0B879843CE21581EULL, 0xD8CD7C4171F880DFULL, 0x272438655E313851ULL, 0x1397B014E2D5D36DULL, 
            0x47D31EADE0F549CEULL, 0xD5FACF92BCD8DDB5ULL, 0xED2068BBFF58E479ULL, 0x120D75F27047BDA3ULL, 
            0x41CFEC37CECE149BULL, 0x7B8DBD64BE036791ULL, 0xD10F3C65302FF9C6ULL, 0x986FBF8D57F94AD8ULL
        }
    },
    {
        {
            0x3080BC679A5F37B7ULL, 0x25A586A3BA698E0CULL, 0xCE3953CDCD973B1AULL, 0x537896F4BE547A37ULL, 
            0xFAB16D80892AF8EAULL, 0xFA94B8B63CD7439BULL, 0x74FFD8E5EEE3017DULL, 0x8D15BD836F1FE1A8ULL, 
            0xD3FFE1C12931DAE5ULL, 0xA4BC50E1CE777AFDULL, 0xF3A7BF33C78C0691ULL, 0xA9F3F95ACF40C427ULL, 
            0x1B1F0D419A1FF902ULL, 0x2DF28751A002AB07ULL, 0xB4350224C0675BD3ULL, 0x6147C5FDC93B0C68ULL, 
            0x50531CDD7040554CULL, 0x4F5BE97265435A81ULL, 0xF64D2DA283258094ULL, 0x8F93B70F0901D200ULL, 
            0x5006C6F7A35FC4A1ULL, 0xF8F5A36426CD455CULL, 0xCCDBAE5510FDA92AULL, 0xE6F05353EB3B4964ULL, 
            0xAED5237C4D8DC91EULL, 0xA0CAA66B26362251ULL, 0x1BF474122E2A25A2ULL, 0xD6314CB68D4880BCULL, 
            0x6D1DF6A32F86F8CFULL, 0x2B07ED6279960C2BULL, 0x94BA381470943C2FULL, 0x72EB269BC6A711EFULL
        },
        {
            0x5F6C3605251D896CULL, 0xA13192EE546B8165ULL, 0xA6254FDADB7BED06ULL, 0x2372FF3A50F13BF3ULL, 
            0x4369DA2D06E8B059ULL, 0xDCC5B3914138249AULL, 0x736C791B67D765B5ULL, 0xEF410C1EDB32BE32ULL, 
            0x041C5BA336FD0DECULL, 0x725C83DC5B22EB4FULL, 0x0AB37397B1CE1DFCULL, 0x9BF5C168F8F98FDBULL, 
            0xC552369A3899AC26ULL, 0xB14F53C5150C8922ULL, 0x39120021B6A3CEC7ULL, 0xAA72D874AC2E4412ULL, 
            0x6849CE1868C5BA54ULL, 0x3F02DB4D8E99CA6DULL, 0x362C99068B2B250AULL, 0x94D5F1C320D4F6FDULL, 
            0x42859890E2BD8742ULL, 0xC94FE234FE657D41ULL, 0x7FBDC88600343C13ULL, 0xC870899B7A77556DULL, 
            0xB10E9542D27426ECULL, 0x7AED498AFC907351ULL, 0x76CBE34CF2BC7148ULL, 0xA36A02B571E5497CULL, 
            0xB467DD377A5B825CULL, 0x2624EBB808F8496AULL, 0x5010EF88BD01AC9FULL, 0x1E6902639BE1FB3EULL
        },
        {
            0xA913551C6F4453C0ULL, 0x74654D3CD268CDEBULL, 0xC2A0E9D903E6CA51ULL, 0xF471C9677623E355ULL, 
            0x10F6D8E5079DD73FULL, 0xB4F60FA5F2091AB8ULL, 0x0895C3DEEF00D952ULL, 0x3D4B0AD157F0CD41ULL, 
            0x1AA36CFAC3EAD42CULL, 0xA0FDF570F3341C18ULL, 0xE5162DD97165A094ULL, 0xF1315FE3EF9F439BULL, 
            0x1267E37020186E98ULL, 0xB96EB744D14C33AAULL, 0x16F55A0D0146296CULL, 0x6884C4E88030EECDULL, 
            0xB0C0CBFE1875E749ULL, 0x5436750AADB94627ULL, 0x5E787B6DC7168467ULL, 0xD4FF7367A9CFBC87ULL, 
            0x250DB57916B41357ULL, 0x926A3D978B3393F7ULL, 0xBDFA3E8FA089B108ULL, 0x8BB9D02D8A2E84C2ULL, 
            0xF664D4B76E634A09ULL, 0x159531F094A6939BULL, 0xA0379846680FB1F7ULL, 0xFE864563285DF62AULL, 
            0x2570ADEBD6C98F1EULL, 0x1700C5B186131F7DULL, 0xBDE36EDC7A326795ULL, 0x912D7B5A403AA775ULL
        },
        {
            0xA9D88AE214C6E2DCULL, 0x23250951307C5A6CULL, 0x842CB656A9BA93B0ULL, 0xDA2679B48F675CE7ULL, 
            0x189988ABA248B6CCULL, 0xE33DBA64FDA1D4C1ULL, 0xD5A9E9BD3A4BD98EULL, 0x52483C46D253EB74ULL, 
            0xFD91D1BB0A526EC0ULL, 0x2A892650A163D0BDULL, 0x971B533FD04BB54AULL, 0x66399CEFE440D6F7ULL, 
            0x5E6E22646AA7861FULL, 0x42198A4BE66AF0D1ULL, 0x5D9EBABA7366F5EFULL, 0x6374A543ED3F710FULL, 
            0x9D069805EAEB9BC6ULL, 0x60F763EC7F437920ULL, 0xA662F1C4D6D8E6EFULL, 0xC883F13EC4C549C3ULL, 
            0xBADCE115251990EEULL, 0xD35E4FAC299AB50DULL, 0x012AE3CD3C94BAC3ULL, 0x00221E8AEFE300DDULL, 
            0x26C531D59CCF5ECEULL, 0xC7907B49340911F4ULL, 0x1C3AE9394916AD66ULL, 0xB056AB097268F58DULL, 
            0xD23757C432DFEA73ULL, 0x5EAEE3CB08E03E24ULL, 0xF32FA8B8895FDDA6ULL, 0x6210E88CCC4DDD7CULL
        },
        {
            0x1C049E3F6E380827ULL, 0x73593B679FDC7F78ULL, 0xD8A6213C3345FD67ULL, 0x9176F40F0D7DF0F9ULL, 
            0x884EFE541B822238ULL, 0xD9A8BEF3D842D3FDULL, 0xFF6D5F5C7B59EE68ULL, 0x89BA1B8D03856B42ULL, 
            0x24B6577A9108DB2AULL, 0x204B3319252614ACULL, 0x988D0B43B6C75A5DULL, 0x6851B4CC4C634C20ULL, 
            0x8B8D716C4BA15537ULL, 0x663136365B03F450ULL, 0xF96685BABA5E608FULL, 0x22ABB3B552627415ULL, 
            0xB46F319C92559A0EULL, 0xBD3125F91966414AULL, 0x84AA573FCA98BBF5ULL, 0x3F31573DF72418B3ULL, 
            0xA0179D61F002FB8BULL, 0x91C515CA6C79D06AULL, 0x4D0D609E3DD2A283ULL, 0x25B9827098821204ULL, 
            0x728E2B0007605E20ULL, 0xF38C9939A2A9E605ULL, 0x69C7F1F0D28F1401ULL, 0xE368D457F707C663ULL, 
            0xDE531344E12F5245ULL, 0x1E1AA19F9FD5173AULL, 0x3B4D15E1889B3714ULL, 0x694DED912317BDB7ULL
        },
        {
            0x2FFF77213809F1D6ULL, 0x720418564DE05DCBULL, 0x0E5D4EA79B3FF964ULL, 0xB642DA73F9C0AACBULL, 
            0x613226C4E54A9A3EULL, 0x4A76F5143E76A01DULL, 0xA71D4663CFAD82B8ULL, 0x1EDF1B27687DA8CFULL, 
            0x165CBDC5DF3EFADAULL, 0xCA09A86D1B1B86FFULL, 0x164B58AD407CBFF6ULL, 0xD340A75E32F9BDDEULL, 
            0xDCE731C91EEF7719ULL, 0x7BC274075490BABCULL, 0xEA0EC95BB597E63BULL, 0x7E0FF28E7F1B0EB2ULL, 
            0xEE9900BAC9E37978ULL, 0x89AC04C130908E8AULL, 0x7752FC38307D362DULL, 0x825FD3C7905ADED1ULL, 
            0xF675760D21A77EB0ULL, 0x1761F0C979E01F31ULL, 0xAB09CAB45A434D6CULL, 0x8226257EF0619AB5ULL, 
            0xFF1F8EEE48C977AEULL, 0xB68914EE36181BB4ULL, 0x697370150DA9A13FULL, 0xBE27ADF6FB33C2D6ULL, 
            0x803CC11B79026E1AULL, 0x4668325302C0A44CULL, 0x11C3947F04896F9AULL, 0x8184F3AEC243795CULL
        }
    },
    {
        {
            0x711E12217A7C6D16ULL, 0x3F27962A62F46A4DULL, 0x856D3785635EA1C0ULL, 0x7A3976739208B575ULL, 
            0x98DEF2D146423A46ULL, 0x8C5C82ABDA0AA9AFULL, 0x3AE062B06836C438ULL, 0x9471C63239BE3914ULL, 
            0xF76F3955E550F30FULL, 0x617A5568A0DE0F4FULL, 0x22B8C26CBAEB96F8ULL, 0x1AA2EA594E531986ULL, 
            0x36CB60FB4A69CE44ULL, 0x6F1886CED28D0F41ULL, 0x44CC7B3ABFB47D24ULL, 0x6EB18C9374AD93D4ULL, 
            0x35DA0CD114493467ULL, 0x59E07B521AE4A60EULL, 0x51FEEC20FD37E084ULL, 0xA028FF1EE6FA1B9FULL, 
            0xFEFE95EF1AC61584ULL, 0x7C28AD4314204ABAULL, 0x369997DC5485B029ULL, 0xFEC709AC57146012ULL, 
            0xD1B22735495BD190ULL, 0x2ED36B1C6DE47018ULL, 0x4A16CE189C09D115ULL, 0x9152F7D96BCFA8EAULL, 
            0xCD8D905BAF19D870ULL, 0x07046DFA2C2A2F5DULL, 0x32FF303EDE39E980ULL, 0xE8DF4926B8DAA3C5ULL
        },
        {
            0xD2CD5F4DF705305BULL, 0x7D75BD122401D9C3ULL, 0x878E1E547AB4D475ULL, 0x7608F6160597FD0CULL, 
            0x17A98066744A9AAFULL, 0x7DBAB70EAADA422AULL, 0xFB73526D1237D8B9ULL, 0x63A88ABEBD3DA906ULL, 
            0x6DA7DF0E1530E534ULL, 0x7ABDEFA806E28A8CULL, 0xDDB7610BF439F5F0ULL, 0x4033E654A7925EFDULL, 
            0x87DE57FEE4280973ULL, 0xE33DF501BCEBBA1EULL, 0x261C81AB062094D5ULL, 0x0A1CD4988C4A718DULL, 
            0xF89B09C1D95854E5ULL, 0xC90DC470C5B516C1ULL, 0x9ADC60ED3C32F35CULL, 0x705435CDC35B5058ULL, 
            0xB4A41F55A3D9B4E6ULL, 0x216B18821DCCACC3ULL, 0x5E924B6B9D7CDD74ULL, 0xCE836254F1216292ULL, 
            0xB39FF122D015C22DULL, 0x253D24B94B1A29D4ULL, 0xEBFF0880CDF4A1EFULL, 0x9ADC18994B3EF057ULL, 
            0xC381A9CC63E3C3B6ULL, 0xADA5570E4FF00A9DULL, 0xD52B0278CAA4EB7FULL, 0x11B1BA71B4C372D6ULL
        },
        {
            0x2FF4258033268720ULL, 0xCFDF8189861643E1ULL, 0xFE3114C9A4D4B710ULL, 0xD7CDAD0CC33DFCA9ULL, 
            0xD140E671F9BDAC8DULL, 0x39CA34FEFE5E2043ULL, 0x91A73CD037BB9C2EULL, 0x5D413ACEA68EF377ULL, 
            0x894FF0F16522A81AULL, 0xA54FED41A096E841ULL, 0x5F31397D5E8BCFF0ULL, 0x0BEE09BDD1050778ULL, 
            0xEAB1F853D15F448EULL, 0xB50237552CA7E3CEULL, 0x57B012A025C1064DULL, 0x0CA550956B8F1CC3ULL, 
            0x89EA8379D6146459ULL, 0x473BE77AB64F7024ULL, 0x8BF2027A35A60BCEULL, 0x066390B5CB71DD03ULL, 
            0x21B9D447ABB9F7D4ULL, 0x12529E7C4F27BED4ULL, 0xEA11E7B085F3A9EBULL, 0xFF0D51AC3B4A2270ULL, 
            0x7C3C91E11B0D3F6DULL, 0x15501CBDFE660532ULL, 0x0C7EAC7B6564740FULL, 0x58BC8ADB636F10FFULL, 
            0x918524080D57E296ULL, 0x475037153A11BFB9ULL, 0x516DE5C379F5F73BULL, 0x4B307DD52C85AF29ULL
        },
        {
            0x6DEE3CDE68DCBED2ULL, 0x70D8018E99AAEF52ULL, 0x873C7F7E48F1BA73ULL, 0xA21D594B1E15805CULL, 
            0x68F91E5A32940B59ULL, 0x90DE09583078C8E7ULL, 0x14025C387A261383ULL, 0xDA591F1EC68E1731ULL, 
            0x22BCDBE5CDC712F3ULL, 0x33BB0AEBE9410747ULL, 0xF35B03E1EC702F47ULL, 0x3C199A950C6EAE9BULL, 
            0x3389A84B1A4F495AULL, 0x2F320DF815AB29D8ULL, 0xE44CA1B54135397BULL, 0xD5B760FF5479E7EBULL, 
            0x5777CB577FEC711FULL, 0x952C47BCBBDE430FULL, 0xA0943C0842F36DE7ULL, 0x73C35621392B2118ULL, 
            0x67208AE46F35E6E0ULL, 0xDFA01874231D6CD8ULL, 0xC236D5D4C82E4311ULL, 0xF7C802DE0F128926ULL, 
            0x86D190969EF74A98ULL, 0xE071BB1601EC61B2ULL, 0xF5224BB07815D289ULL, 0xC91F7450AD7563DCULL, 
            0x059582ECBF1E2720ULL, 0xB5B58FA01D23C9E9ULL, 0x12444C8AE14A508AULL, 0x8EBF79674ED4B62FULL
        },
        {
            0x308161F4D49CE353ULL, 0x3181C6E6D23A14C8ULL, 0x31120E7254111FB2ULL, 0x197A8660C0FF9DA9ULL, 
            0x5F3D8582A6855874ULL, 0x8289F85EBBF2E0F0ULL, 0x4418337FCAC96550ULL, 0x4515254CCC87001FULL, 
            0x495FBD2A52C57830ULL, 0x9638766473A43428ULL, 0x1CB7361FD53BD86EULL, 0x728268A7F2995D34ULL, 
            0xD3CF5CF3BDBD5298ULL, 0x563CD0ABAD15C7B6ULL, 0x1BAA14A9981CA258ULL, 0x09BFB4F53865A00FULL, 
            0xDE41A37E8B85DE7AULL, 0xEC3FD739975224AEULL, 0x627E4381C16FC984ULL, 0xB89D66318E54E9A1ULL, 
            0x2BE975226714440DULL, 0x66BFCDBA500D4489ULL, 0x25C54DCE2BD566D4ULL, 0x7D98C31D9EEF36AEULL, 
            0x3C7629AE1171F8C4ULL, 0xEC8750D1A05D1022ULL, 0xC7297F7C0B2F1E92ULL, 0xA59D1A4F566AFBACULL, 
            0xAD6F3CA710CE2419ULL, 0xC1B23B54544DCF72ULL, 0xC07A92988B84B8C3ULL, 0xA61163C1A0F7AB4EULL
        },
        {
            0xA659F077AF768599ULL, 0x689EEC8B691E7771ULL, 0x2052D96633008E34ULL, 0xFCF8B5DEFDFC1D51ULL, 
            0x5188B353CDDDC216ULL, 0x2C32E87AF6FB21A8ULL, 0xE091C1345266FF1DULL, 0x0A0AE9DEE1A1481DULL, 
            0x08378D4E157DDD28ULL, 0xBEC8668C60075A29ULL, 0xEBB2AC1517B005DDULL, 0x3568C7CC6860DAADULL, 
            0x34EB4685D17804A2ULL, 0x4C37A65EEA6B37CEULL, 0x186CF742703AE2EDULL, 0xAEAB63EA2FAD7D92ULL, 
            0xE92F42260ED829ABULL, 0x3483F0A795835141ULL, 0x368AE2E1ADFC8777ULL, 0x0B1A194616A2BEADULL, 
            0x491F8A51D5533EACULL, 0x203EE083DFC3F66DULL, 0xD59D025D77D7B81BULL, 0x6B14E67BDFB7BC9CULL, 
            0x3AB685C0D61477CAULL, 0xDF925436D2ED0F2FULL, 0xD80889BD03302237ULL, 0xC95F267B319F8B20ULL, 
            0x5A4787A8CD18CC88ULL, 0x063380471030B30FULL, 0x20FFFE827B91DB25ULL, 0x941F1F2DFD24205CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseDConstants = {
    0x83286EF1FFB14C80ULL,
    0x148732D969619638ULL,
    0x9F04B0B688878793ULL,
    0x83286EF1FFB14C80ULL,
    0x148732D969619638ULL,
    0x9F04B0B688878793ULL,
    0x9096D516A457A124ULL,
    0x8B4255EA8175C548ULL,
    0x32,
    0xF7,
    0xDE,
    0xC1,
    0x92,
    0x73,
    0x47,
    0x3D
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseESalts = {
    {
        {
            0x3140A0D276937930ULL, 0x7DCBEB06FE7FBE8CULL, 0x2E55C696887F8327ULL, 0xF32B4CE788C44DB2ULL, 
            0xDDA89321C936B525ULL, 0xA98925AD4A1ECA3EULL, 0x1035715DC1513C18ULL, 0xDCDBAA523224B46FULL, 
            0x1912CB9082C1B7E0ULL, 0x1234C60584B77725ULL, 0x2F76E2E1BB62B8E5ULL, 0x3449E77AC41833A9ULL, 
            0x630031B311789A42ULL, 0xE635139FE57C1139ULL, 0x56035E29BFFDEB6AULL, 0x44A67F6450DFEC7CULL, 
            0x5A1ABA4B1EEB9CC7ULL, 0x29FF91790138509AULL, 0xB7869610C3757DFFULL, 0x150BC7D4279B91A1ULL, 
            0x15C41E29E8635D6BULL, 0x39EA4DE0A0832C5FULL, 0x796B84C28B7C50CBULL, 0xD176208A66110A5DULL, 
            0x33DFDE1947418E3BULL, 0xC967B636CCB4D379ULL, 0x4A8B54CE1C230DB0ULL, 0xB135D2D19467F83DULL, 
            0xDB1DFD60837D1DCFULL, 0xB603A1E0E6A0B12BULL, 0x33E91C6057AFE128ULL, 0xA54C9F159092DA46ULL
        },
        {
            0xFC2CC1FBA1E9A51EULL, 0xA76D8AF54A20BE78ULL, 0xB8A08BFAB49822AFULL, 0x3886A07177060332ULL, 
            0x3BAB82D253B856ECULL, 0x46842901EBB6EFE8ULL, 0x6AE16892617D2B7CULL, 0xDFB5FA94CB02930FULL, 
            0x0ECEF18FEFCECAAEULL, 0x99D3DD2DA772524AULL, 0xCD16279307A4F64DULL, 0xAA1A6F9F184BA40EULL, 
            0x9ED18C589EA76DFDULL, 0x9316B1DC3EF6B631ULL, 0x1399BC8D676B731AULL, 0x49EB649A183E386AULL, 
            0x738E958EA65BF573ULL, 0xD9C47F44727D083CULL, 0x5C4F114479F5DECBULL, 0x4A896CB3B962CD2EULL, 
            0x5C98083D8BDC6F8FULL, 0x9B26EF1B2B8A60E3ULL, 0x1FA9D5E955D9B6BDULL, 0x7842E64E34DBB947ULL, 
            0x56EBB3D66D39CC07ULL, 0x3ADEFED67441BB49ULL, 0xE5F97B3CE44CBEE0ULL, 0x5880BA5BF85AD287ULL, 
            0xB91D81A88509A703ULL, 0x457F984477A33F3AULL, 0xA72B802D69095F57ULL, 0xA50D3CA03EA7A7FFULL
        },
        {
            0xB048FF8D621B5E99ULL, 0x4DBFD87FD39E5CACULL, 0x5CAEAA900CF4CB68ULL, 0xE024A424D624A9C1ULL, 
            0x868E952E4B8C61F8ULL, 0x27F0BE29A306B06DULL, 0x95EEE723A5CEB7F4ULL, 0xD9E446359BC79CB2ULL, 
            0x1ED052819A1FB110ULL, 0xB675B326959F1867ULL, 0x9D1471282D4ABB57ULL, 0x5AA60049ABF4F9F9ULL, 
            0x48C81DFAF64D5AEFULL, 0x020FA8EE10290F80ULL, 0xB68E447D42A0184FULL, 0x0FF0EC39276BE011ULL, 
            0xF747365B43839954ULL, 0x7D9BAB77450596F4ULL, 0xCFD54EF6AD05687BULL, 0xE5936C4ACD623EE5ULL, 
            0x6D644045360AA7DDULL, 0x4B3BC770E0858707ULL, 0x669AD2F2BB6F09CFULL, 0xC5B91D0C4507FA66ULL, 
            0x99DEA96910225AD2ULL, 0xFB4964C71ADCC9E6ULL, 0x5F5137014B676FB6ULL, 0x36D9F7F4B4B3071FULL, 
            0xE6CD872D64C27D29ULL, 0xF69ECEF18FF32BC0ULL, 0xFCFBC238B4671998ULL, 0x70E79C80B47551B9ULL
        },
        {
            0x70A3B200F08D6E70ULL, 0xA8C619E39F9882B5ULL, 0xE02263B8D2BD6BC7ULL, 0xF28F16C4D8C2F225ULL, 
            0xA908B44103967FADULL, 0xB965B4092E87E531ULL, 0xA22F81843296AA3CULL, 0x7C31B6952CF43F48ULL, 
            0x6E8E7ADA0EC8B2B9ULL, 0x8F7838312A96A00BULL, 0xC134AFF47EB31498ULL, 0xD24EA2380CCD65CFULL, 
            0x1AA9AADEB95ADB0CULL, 0x21CB6F14916B5636ULL, 0xEE554CC0D9EDB8FAULL, 0x83A05A946EA6BDFEULL, 
            0xCCF2EB0F09B4A430ULL, 0x684FC662C56B2649ULL, 0x9EFE587B71A77282ULL, 0xEB02633909634402ULL, 
            0x4EECC06AD5CD49DEULL, 0x448B94A2C9F275EBULL, 0x1AAF464EA7BEE4DEULL, 0x940449C9D7A9655DULL, 
            0xAA754BA859A2D151ULL, 0xCDDF76872D947E1EULL, 0x5E9A80FAFBF125D7ULL, 0x0C700FC46BD3C1FDULL, 
            0xFCC2DD3355D6B5D1ULL, 0x66F6A4F9A00BFD86ULL, 0xB1691954EC5FAB35ULL, 0x600C934C4F41DE70ULL
        },
        {
            0x40A8879F84AF0548ULL, 0x785E23DDA5E37C31ULL, 0xBF13B39F6DC5D8A9ULL, 0x2162A869F3FB1AEBULL, 
            0x09478FBFC7D2954CULL, 0x57E579479F39CD1BULL, 0xCBA35DB1E589D1C8ULL, 0xD61692FF35EBCA6BULL, 
            0xB1E43A9C33DC2E1CULL, 0x9668F2DAF8DBF400ULL, 0xCBE49A9544DF8CFCULL, 0x5C9904B05799A7A2ULL, 
            0x15A4C481E1B7B252ULL, 0xB6DB446405AB566CULL, 0x1CD25E2A96997AD3ULL, 0xA8EA01617C67F66EULL, 
            0x36D2D6B9A11C2A03ULL, 0xE72F80D07C80A98EULL, 0x0B09C8E74B86DA0EULL, 0x01AB8246E5518320ULL, 
            0xC67D0C1E719542FCULL, 0x90F4BB2550F43BC0ULL, 0x79DAA7B12FE0F190ULL, 0xAFA50E8657218EA9ULL, 
            0x617AAA860BCDD64FULL, 0x9687E1739B102988ULL, 0x56FB6D37B7AC1A7CULL, 0x9B85FF8F79D97CC4ULL, 
            0xAF7F617932E39CF0ULL, 0x15DF678B1BEBD190ULL, 0xACC9180EF2E62B04ULL, 0xB2CE12C181262C6DULL
        },
        {
            0xDA242BAEA5F7646AULL, 0x3228F2A98389F997ULL, 0xD2D8DB2062982AC6ULL, 0x567BDE855EE15DACULL, 
            0x5D958CC6F483F7F9ULL, 0xDF4D7C8590EC5DA5ULL, 0x3D02D39C2927108BULL, 0x9E15FA11FEAC700AULL, 
            0x114B93E36B324409ULL, 0x9BBCEDDA2AF66156ULL, 0xE9C1D0516B38482CULL, 0x65570040BA3CE3EEULL, 
            0x79B90F3225311C50ULL, 0x92A25A9C68EDA91DULL, 0x6D77CDDD541CA4B4ULL, 0xF5D93D5A16B31B4CULL, 
            0xBF92B09B0A4FDAD2ULL, 0x9B02F5AC58D885BBULL, 0x6ACA76E6E9722088ULL, 0xC62B46370CC2B7EEULL, 
            0xB27C2245DA01349DULL, 0xD32DCB14593783DBULL, 0x7A85EE734B06752FULL, 0x037BE7AEDDD24072ULL, 
            0xE185AFDB2D1BC1F4ULL, 0xA1C418265E0CD26CULL, 0x8C7B3CE4E9D72E5BULL, 0x812C35203AC0D26AULL, 
            0x6ACC8AEFA029F5D6ULL, 0x8FCEA86AB2EE01CEULL, 0x68C4C71AE8E00B47ULL, 0x436FF081A675F03EULL
        }
    },
    {
        {
            0x0734F10DE84CB854ULL, 0x0CC0CED2535C4142ULL, 0x3A5A8F32DC3AFF85ULL, 0x6A1168B7931E26A6ULL, 
            0x7FDC696C1B1CC5F7ULL, 0x6906F4B8072020CDULL, 0x1AC49C5619041C68ULL, 0xC292B536E2CFE8C4ULL, 
            0x733EC767B5AC64ABULL, 0x94844365763B98AFULL, 0x59175C88201D7E3AULL, 0xE9E985EB50F68425ULL, 
            0x2FFBAE881301ED3AULL, 0x5BBFC97833A73B05ULL, 0x9C22B4B4796DFDF6ULL, 0x6262478605DD3E5AULL, 
            0x4B6706535EF8988AULL, 0x87F0BC71502E6997ULL, 0x9749BF99DE69A0F1ULL, 0x39E6F70A98892A3EULL, 
            0x4BADC1134DF1B929ULL, 0xF3DC1150AB30D9CEULL, 0xEFAF77920A397A42ULL, 0x447839D8CE650635ULL, 
            0x141EDFBB790ACE57ULL, 0x1A62527DE44A554EULL, 0x57D5968664171B06ULL, 0xF427B41F5B339631ULL, 
            0xC95E2154776A5D61ULL, 0x54E5CE28E051E9EEULL, 0x2E2932B9905672D3ULL, 0xD565FB44572EFDFCULL
        },
        {
            0xE7C1FFF7FD57A23FULL, 0xEBBD372381EF65EAULL, 0x5CCA567B3897EBCAULL, 0x08526A83B0F851AAULL, 
            0x4BCE54D604AF076AULL, 0x1525F34CBEEEE720ULL, 0x77E4BAB17233F6CDULL, 0x50BF8524C2E35136ULL, 
            0x4763A7023ACBD7C5ULL, 0x770D58E14815D512ULL, 0x55C005471F716528ULL, 0xFF9CCD124A4AC398ULL, 
            0xD31084F65D8FCAEFULL, 0xE5AB9E8DA46D84D4ULL, 0x932294DC25EA3379ULL, 0x9C09AD1800E82918ULL, 
            0x1F4ABEE18DC87093ULL, 0xEC2F377CCE10AC1EULL, 0x32F7A15DE8607A67ULL, 0xBD9538D2850910E6ULL, 
            0x25963CFAA1B47A37ULL, 0x8631D1C8C5F54F39ULL, 0x67A5C20CDEFDA045ULL, 0x9BC8D6A2FC0C5CEFULL, 
            0x4C42CA89C7FF6AC2ULL, 0x78E103892762ED56ULL, 0x72E5B5500AF87B42ULL, 0xF571F26213B0AFE8ULL, 
            0xD39CABC53EAF4105ULL, 0xC5D78D7587535018ULL, 0xC134A8C966C3CFEAULL, 0x7961A44A23EA4972ULL
        },
        {
            0xE4284D645F420C9DULL, 0xD9E27E4BB938DE70ULL, 0xB6C5809C91104BA5ULL, 0x8A013125FB4D5828ULL, 
            0x4303FFDDE05CC145ULL, 0xD8EFBCD3D5D30DDBULL, 0xD94DF7866E84C9FCULL, 0xACAAFE07F9387A47ULL, 
            0xB27FFFA4B65C5898ULL, 0x369A77AC1F9E35C4ULL, 0xF80A54F75BFBBDCCULL, 0x2E4AF6072670D176ULL, 
            0xDF7B464394745D00ULL, 0x4DB8A88CBE890ECCULL, 0x6B07954151534F3DULL, 0xD12966C0350B259DULL, 
            0x6DFEF5210F905F31ULL, 0x79ED66CD9372BF65ULL, 0xB503993E818C58F6ULL, 0x50B4088938DA554FULL, 
            0x64EA322B5153B346ULL, 0xDE4375C890D8D924ULL, 0x9AEE8472E5FEF116ULL, 0x58DA22A5D3ABE4A1ULL, 
            0x0FE4B62750160D4AULL, 0x6E2CA994E1C20EB5ULL, 0x6B1D0D115DCEDDC2ULL, 0x2F526D7D16F71ED9ULL, 
            0x1B8913D18F399B50ULL, 0xED67F5FA835BDFD0ULL, 0xE0EB90DF0CB7FF41ULL, 0x89A0AF6231898290ULL
        },
        {
            0x615E95134A0E9EBCULL, 0x3526D27C3E3BAA89ULL, 0x6E650317443D549AULL, 0xBF50FA1956584FC5ULL, 
            0xCE942F16B5D19A6EULL, 0xDF1FBFC96A4B601DULL, 0x8BC96D9B0B5BA0ADULL, 0x15E8D8C40FD9559AULL, 
            0x5F5E4EC3236AB971ULL, 0xECF2BB423208A5F8ULL, 0xB9868A913D158052ULL, 0x18667FFE5CD44932ULL, 
            0x6585E04BFB20E279ULL, 0x2C99596D2FC6B661ULL, 0x74F41705C6C03746ULL, 0x6555C129F2E532EAULL, 
            0x6C1E9AC605B8CDB2ULL, 0xAEC71AB4B2E43266ULL, 0x90A6EFB6A6D9A5C9ULL, 0x80AE7D8897D131D9ULL, 
            0x33A18CE57DC13E20ULL, 0x0AB3979FDE6EA072ULL, 0x37D3DEB4640397B8ULL, 0x17125CDDC16697C7ULL, 
            0xFEEA7978F9AA9FA4ULL, 0x6D0A8D40DEB60686ULL, 0x5CD6A46AD2183676ULL, 0x03B2F50F97EB306BULL, 
            0xAEEB6FE649E882E3ULL, 0xED936E5C47835C81ULL, 0xACEEFF672F33BACBULL, 0x380BB5F55D6E7F00ULL
        },
        {
            0xA40BE5873AB81A76ULL, 0xC0EA45C897B6B7BAULL, 0xCA6742C9F1A121FEULL, 0x855C932000BA60C6ULL, 
            0x6345CE01D2D10D8CULL, 0x37F52A6AFC12B0A9ULL, 0xCC26FA3BBF051F22ULL, 0xEBB8740BFABE6230ULL, 
            0xC3A36997120FE4E1ULL, 0x5838749260D9440FULL, 0x8071D0ABBCEBA819ULL, 0x02C8983AAC1CC444ULL, 
            0x5F80A53768D192F0ULL, 0x456C166F44C0D645ULL, 0xDA64FC5844969EECULL, 0xEA1E4D9D3AAEC02FULL, 
            0x4A96449E26CC6685ULL, 0x6ADD679BD820356CULL, 0xF8FE7BB78ACE3473ULL, 0x5BF505D275D58F77ULL, 
            0x58DC842C18DBB38EULL, 0xCE7477ADCC56A2D0ULL, 0xCDB8F9D77ADB392DULL, 0xFC2BF896E6DCF77FULL, 
            0xE91E79544A204EB0ULL, 0x898F642AD790775EULL, 0x99AFDC95BDAC1D7AULL, 0xA1CA50EF50A35F23ULL, 
            0xBF50BFE12F0C2300ULL, 0xFFD75B5E05C355F5ULL, 0xEA89E0D13CD632AFULL, 0xD81CF723FC7BE879ULL
        },
        {
            0x2423431BD23A33ADULL, 0x91BAFB08CF8686B6ULL, 0x41F4D19657856580ULL, 0x8241F765B2179D11ULL, 
            0x413CB156017098B6ULL, 0x07AB68FA6BB20804ULL, 0x611AA52E39B08DFFULL, 0xB775E356A0265D18ULL, 
            0x7D41173CD67D7D02ULL, 0x144E2FE8CB36EF40ULL, 0xED262354D87F6C70ULL, 0x23DC1741481A9F38ULL, 
            0xD74891052AABABE8ULL, 0xEC993E1C04A6383EULL, 0x29B99A88433ACDE8ULL, 0x010FFEA87F8CE373ULL, 
            0x52A2B768C73CAD74ULL, 0x13954F2DC4B52E73ULL, 0x4812677B3456BD5CULL, 0x863EC6806F157AB7ULL, 
            0xB9C9A94ABA85A82DULL, 0xD3DE61BC2354746EULL, 0xD9B9004783269A67ULL, 0xC65D8E14637A4453ULL, 
            0x208DDF1AD9181091ULL, 0xFD06217DB7B46EC0ULL, 0xE26CC0C9ED2DB068ULL, 0x6718D25DEEADD0E8ULL, 
            0x2E6CC1D7C7D6D7C1ULL, 0x9C11D3954B1FF85BULL, 0x1192C867E4135640ULL, 0x3C1EB577419A39C2ULL
        }
    },
    {
        {
            0xBA38B78D21BAE28AULL, 0xA2DCDB3562C74AF7ULL, 0xEA65FB85EFC97032ULL, 0x609DCDEE6811A38DULL, 
            0xFFE62401EF5994D6ULL, 0x26497A71C89110AEULL, 0x6A5AD4BAA6E0005EULL, 0x7AD878F92795F673ULL, 
            0x2C656125D863A5BBULL, 0x1622E4F77267C68EULL, 0x7115959422553ED0ULL, 0x727DEC3FDA3DD111ULL, 
            0x652F296D66D8A808ULL, 0x8E3510482683EC6AULL, 0x6655E2217C35AD4AULL, 0xAF709D78F1F41F15ULL, 
            0x1AEAD8ED408461D1ULL, 0xD49C8414B2F5BF8AULL, 0xD32BA6053949AAD5ULL, 0xEABA1E6CE6936A19ULL, 
            0x58D2C99C8176996DULL, 0xFDCE9E608F5A4480ULL, 0xEE65CEAB37C97069ULL, 0x5163A51FF431463BULL, 
            0x47D2E849B65C6494ULL, 0x15516CE9D558E389ULL, 0x6AC5BCB2E2401FC1ULL, 0xFA45B7328307FEADULL, 
            0x245A2A895490200AULL, 0x6C9528013816F8FEULL, 0x9841C2F3C0CF799CULL, 0xCE6F9DAD1A4C13A2ULL
        },
        {
            0x6C34B7821F73FA0CULL, 0x0AC8584BB0C42BC0ULL, 0x718832A3A941B80DULL, 0x3F23D72D2B9C020EULL, 
            0xE9C7C45469556446ULL, 0xA23E8808C1E1729AULL, 0xAA6598B125782265ULL, 0x41A5A0809D46BDA0ULL, 
            0xEAB3C68F61EE3D03ULL, 0xEF41A42B522F694DULL, 0xD53B2B74B9982F7DULL, 0xB0D3283B05382B75ULL, 
            0x4ADA2B6B6CD68E35ULL, 0x2CBAC37EE915F68BULL, 0x0A766C84DE63393FULL, 0x29A8A625348577F8ULL, 
            0x6D6D88777088DC76ULL, 0x32738391B1D7FE2FULL, 0x5FF5500FD3C872D2ULL, 0x6984824A711F09B3ULL, 
            0x6BEAEA32DEEAAEC9ULL, 0xADDE472E66B524E1ULL, 0x893C087D5EC0D3D0ULL, 0xF61F24C8BFCCBE67ULL, 
            0xFCEC7D1B1876E81CULL, 0xFD8CD18D07D710D2ULL, 0x1E98B4F212CBFF5AULL, 0x9529EF66FE4465DBULL, 
            0x67E41C807481505DULL, 0x443526F6258446AEULL, 0x47298D0009CBCFEEULL, 0x7B2FA924B23523CAULL
        },
        {
            0x9301AF43C77D1B7CULL, 0x416803959894667FULL, 0xDD835F15E4524F4AULL, 0xD898D42607ECBDC1ULL, 
            0xF8D053F9A7653A64ULL, 0x823DADD59151BF91ULL, 0x04C16B8EE4D2272AULL, 0xE1BE39883C4094D9ULL, 
            0xA8533AD47E4A043DULL, 0x15CB7CB546D098F0ULL, 0x37221FF647696A16ULL, 0x6E729CCC0EB881AAULL, 
            0xC1F98742C0864779ULL, 0x2AEA2EBA12EB4EDCULL, 0x0AC58452902B92CCULL, 0x888AD7A8F1798720ULL, 
            0xEE30F1D2AFC3288CULL, 0x0E614A1E329FA6ACULL, 0xF73E973F95D99314ULL, 0xD6C02C39686AFE0FULL, 
            0x2A253F26765640EDULL, 0x55AA57D50533D49CULL, 0x66BE1CD168D0F61FULL, 0x0474D13E1B08756FULL, 
            0xEB12A7347F05EF8CULL, 0x6269C97A74150F28ULL, 0xF40581EC2326AFBDULL, 0x5D4BD5AB7C16FDCBULL, 
            0xDF368AD14C25D4D4ULL, 0xEA42880EA04318C5ULL, 0x02832936888088CEULL, 0x64FA54BF789CD84DULL
        },
        {
            0xF1102D7CFD98A638ULL, 0xC4F4F6DEB0C2AF35ULL, 0x1247E4AFEBF750ADULL, 0x163330B240D5C210ULL, 
            0x199E4389B02362E2ULL, 0x24B039AAA785A2FEULL, 0x6093C28FE077D4A5ULL, 0xECB3B90412531351ULL, 
            0x84330A18E7CF258AULL, 0x7E1834886D385B07ULL, 0x09120B8EE31444ABULL, 0xBB096C6F070306C6ULL, 
            0x6780A5FA480A7BEEULL, 0xBCB37B1E328C9A50ULL, 0x3EB9793DD552F71FULL, 0x7F4E27FA79B42420ULL, 
            0x9597E4EA782DBE04ULL, 0x5CECA3E20A51AEF2ULL, 0x2855EFB1DD423A7DULL, 0xDAED2700146FA11EULL, 
            0x2E3FFC51DEB60D6BULL, 0x058F19709B33698AULL, 0x05B74D94C779B861ULL, 0x49A442B5B3A4AA45ULL, 
            0xE216F95F269AD2D5ULL, 0x3CEBF3519B2D3561ULL, 0x9B9F1AA35F856E11ULL, 0x67E735C6A1949FC1ULL, 
            0x7F5E67C8722BADAFULL, 0x6F5D703E8E32E20EULL, 0xD0382E4B2B9C2031ULL, 0xA10D2C2386214E58ULL
        },
        {
            0x1562031A9C0A28A5ULL, 0xBB57B3581529417FULL, 0x4702A64503AD0F03ULL, 0x4965B1368B1ED474ULL, 
            0xE643FBC31BACE5FCULL, 0x2CB1FC1D28EBFD82ULL, 0x78D94A64B04DBD9FULL, 0x3A91A5AB3E681268ULL, 
            0x8576FA6F7D95330FULL, 0x0F7326709BFA19F4ULL, 0xE0EB974D0FF5CF01ULL, 0x91DCE8779094D17FULL, 
            0x2BE874C45FE28C32ULL, 0xF1A8885B89AE39D7ULL, 0x3B3D24F8063DFDA8ULL, 0x69AF4E1143AF062AULL, 
            0x6DD1630A365D0134ULL, 0x25C6B4A90D1AB553ULL, 0xA9645CB1D928D092ULL, 0xB51CCE66EC1080FDULL, 
            0xEBEACA50664FCDC3ULL, 0x2B092DB5AC5B29DFULL, 0xAAF27320F9F0E0CAULL, 0xEA2DAE3BA6D6B388ULL, 
            0xED89C3908D720E5AULL, 0x28FAC19B3560BC5AULL, 0x1A70A1D147AB53CDULL, 0xB8EFB85408D76F90ULL, 
            0x5787505E593573A8ULL, 0x57204573CFBD645AULL, 0xE0A826582F75F0BAULL, 0x0FEFE4A69E1320E7ULL
        },
        {
            0x7302BA5ED2B944F7ULL, 0x52A51493B1B26B29ULL, 0x3F20729F1EF5B06DULL, 0xAD790D9453DDAF72ULL, 
            0xBB657C5CBA376C02ULL, 0x4D11E3177B1821ACULL, 0x913F87B4809134A0ULL, 0xD2551E026C60FF2CULL, 
            0x1FD87AF052438C50ULL, 0x7D449ABEA70060CFULL, 0x2C3EE4E5B8A2D1F9ULL, 0xCD0331A877C4E693ULL, 
            0x8B0650B81122F80FULL, 0xFC0A922587184A55ULL, 0xD37EC123C138AE99ULL, 0xF81114C318E6ED30ULL, 
            0xFCBA76BF90C9CE9EULL, 0x58D4E215E93A3EDFULL, 0xCA96A2664C3A1598ULL, 0xFA04B1801BAFE584ULL, 
            0x1DE35D1C1DFB5AEEULL, 0x29D7EC00AA6FA16CULL, 0x8D5170673C3DE769ULL, 0xADED488F8B2DEE94ULL, 
            0x6E37341AA08D0369ULL, 0x0A8B12411AD00FD0ULL, 0x277FDD6596613E36ULL, 0xD6B39BADF6BD0D4EULL, 
            0x543F9DB6C4A7593BULL, 0xA3FFB849EE02434EULL, 0xCEA9AAF84D5B9027ULL, 0x3FB7EA060297D511ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseEConstants = {
    0x8C1198813504C282ULL,
    0x3C4AE188D9D7F1BAULL,
    0xA102B5C5CB2B3E60ULL,
    0x8C1198813504C282ULL,
    0x3C4AE188D9D7F1BAULL,
    0xA102B5C5CB2B3E60ULL,
    0xFEEE5BEBBE0EA4A6ULL,
    0x9266DEC9D62874B4ULL,
    0x5C,
    0x87,
    0x35,
    0x52,
    0x54,
    0xFD,
    0x3C,
    0x91
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseFSalts = {
    {
        {
            0xAFCD0D4D18FF79C5ULL, 0x3F74FA95F1403D36ULL, 0x2ABC46D525B4A2ECULL, 0x05D467853B3E9F21ULL, 
            0xEFED1E222502E233ULL, 0x4E7C9A40E9D6B792ULL, 0x56AE55039DF469BAULL, 0x167B47B8AD962047ULL, 
            0x5AA3A36909E55A23ULL, 0xA4F90599BAF75C8FULL, 0xEB5379C2F174FD01ULL, 0x31C5EA608F2ECF82ULL, 
            0xF942715E1F8ECA88ULL, 0xD8050E522A8EF1C2ULL, 0x653D1CC20E03C55FULL, 0xB38C7798F77B623BULL, 
            0x1BC429B70A4138FDULL, 0x9254F7771958161CULL, 0x5AB4D973740E4AB4ULL, 0x6B9486DBB989A513ULL, 
            0x0D9B538AE1635993ULL, 0xC4F08671478C158CULL, 0x3B8CA52F2C06BDDEULL, 0x43660E4354651F7AULL, 
            0xAD19125D20583065ULL, 0x5BD9F07EE284042BULL, 0x8E0DA561709E0E14ULL, 0x9FFE0A3E102D214EULL, 
            0xA453B835F2E94917ULL, 0xD5F0C2545DF129F3ULL, 0x31168402E4DA9C60ULL, 0x91CCC3F3FF097A3CULL
        },
        {
            0x427F074F497159FAULL, 0xB076F61D24612B62ULL, 0x265265F7EE832830ULL, 0x221476386CFD94F3ULL, 
            0xCFBD341E1D0A8510ULL, 0xF7ACE42F77D0E6D6ULL, 0xF608D819C2DCB362ULL, 0x57FD29C8C22286EDULL, 
            0xA07578AE1B231D84ULL, 0xFCEB4DA13DC83612ULL, 0xFADC9157E2ED8153ULL, 0x76B613330FDAC496ULL, 
            0x914DE08089C44576ULL, 0x788CAC0B24E741DAULL, 0xD430953CB660E506ULL, 0x8FD839FE3DAB12F3ULL, 
            0x111CAD0B6A5B7381ULL, 0x612A44AA177A7413ULL, 0x238AB921C84E5F54ULL, 0x39E4B32E5881141DULL, 
            0xDAAD30B2115D4767ULL, 0x728A1CF5375F6138ULL, 0x23FCBB254C793D2EULL, 0xE8D6AB679D079427ULL, 
            0x1B28EFA24DAAE3E6ULL, 0x9DEBB5D9B8695D20ULL, 0xAFCBCFF7B29B06CDULL, 0x56FDAE071CEF49C7ULL, 
            0xEA79F5AE47D2D887ULL, 0xD505D393038ED328ULL, 0x45852AED4891EC33ULL, 0x46B372F63B64C290ULL
        },
        {
            0x9B32C389DB4B0041ULL, 0x766364513AD705B2ULL, 0xC9466C0E4F73B187ULL, 0xD513EC4FCA170F36ULL, 
            0xD4CA10B63E71EF93ULL, 0x4C1580C527182E7AULL, 0x028BA0FCD5E06146ULL, 0xB38481A82763738CULL, 
            0x7613E702FB609C12ULL, 0x8CA15EBF9C03AAAEULL, 0x42E25F34F99CAB55ULL, 0x4F616E23B338D750ULL, 
            0x6D801FA0AE1A40AFULL, 0x136F8739E5A89B7BULL, 0x716E6EFEB2102402ULL, 0x89F86DAB104EA124ULL, 
            0x159D6DB8493E2833ULL, 0x4A81129827D76AB5ULL, 0x7A8DCA6F9932998FULL, 0x7CB9F05E7C6FE9C5ULL, 
            0xC99753085D18B19AULL, 0xEE7666F297A3E8FCULL, 0x1BD3F2770F6672F8ULL, 0x856A610A60D368C7ULL, 
            0xA1B35EC5B222157BULL, 0x44578D317671629DULL, 0xCC8C54A8D4E90F79ULL, 0x9EABC2CD81A60A44ULL, 
            0x8A5C2BB7C0DB611EULL, 0x99C2C33357AADC17ULL, 0xEB47067063D40562ULL, 0x4B6CF64DD7F008CAULL
        },
        {
            0xFF5810017B04D3B9ULL, 0x58110F699192260CULL, 0x6DED9D8F3BF946CDULL, 0x04FF22A0A6BAF2DEULL, 
            0xFE88B29DF98CAD5FULL, 0x27361BBE3380CD67ULL, 0x1A281B1389C5F3D2ULL, 0x197C5F01C2EA3AE2ULL, 
            0x6B4F9C58E14A9E8CULL, 0xF01248121F408D03ULL, 0x785F2DA476043169ULL, 0x2C42FE4B2A5089ECULL, 
            0x6113FEE18ABD01F0ULL, 0x03390558EA60503FULL, 0xD6F8080C8F407389ULL, 0x960FC6553F7B3E22ULL, 
            0xB8B80AEA39555D84ULL, 0xFFA053164C3AA26BULL, 0xD1FE481B85EE554CULL, 0xA50C6D2F1E18F384ULL, 
            0xFD523BF243A1E143ULL, 0x19BFB73ACD03DC7CULL, 0x158AD2AAB2728FE8ULL, 0xD5AD69E98F62DBF5ULL, 
            0xDD3A2214B2C6E3A0ULL, 0x52E3204F6D8B0723ULL, 0x9C42E0A46EE5FABDULL, 0x2D0D7EE4DEF8240CULL, 
            0x4344B769AA1398CAULL, 0x8496A80DDD24D694ULL, 0x496960A6CA402D9CULL, 0xE1DB00095CAEF47DULL
        },
        {
            0xDD5419E94779DA4DULL, 0x464198D6BCE273C9ULL, 0x0BA5F725B2187C2BULL, 0xB86EFC0705E57399ULL, 
            0x3970069AAB7DD3D7ULL, 0x212C7872D74B71ADULL, 0x8DF4A7A295BB5318ULL, 0x4529ADC89F6F84BEULL, 
            0x60FF0B682E517380ULL, 0x51B2A64D5441CD4DULL, 0x0C6FE2FDEAFCB6E9ULL, 0xE297546AD3AB1051ULL, 
            0x2DFC8FD1735E7823ULL, 0xD627B24718D03441ULL, 0xA63406F23F19B846ULL, 0xD7E045B47E56B04AULL, 
            0x47A9D7138C872869ULL, 0x10C71FFB1F0E5BFCULL, 0x0C57367015EE5405ULL, 0xB98A341CB89A0216ULL, 
            0x057BD0FB1F74F4ACULL, 0x674C04038D12D68CULL, 0x4998C4AFAFCBDE27ULL, 0xF86416B372B36259ULL, 
            0xB6BE3AC03A174713ULL, 0xABA26A5A5001ED54ULL, 0x3287FBD7C7A89C00ULL, 0xA9AD3DF0C646C4DAULL, 
            0x1A58B14DA44FD862ULL, 0x8204E0A48C45E2B9ULL, 0x34161C31E4DB0216ULL, 0xDA4897C9CB6F58BAULL
        },
        {
            0x959FF6DCA9DB732BULL, 0x332570D28FB5EBB8ULL, 0xE0E7EAA3C09910FCULL, 0x89D357834D25F8E9ULL, 
            0x7AE57409A34F5115ULL, 0x082ECA74931D2ADDULL, 0x6D1B6DF661F0DE92ULL, 0xAA1CD0E979C3D257ULL, 
            0xE30CECEE979CB9DAULL, 0x01695B4B40515546ULL, 0xEDBAF19C6129358CULL, 0xC49F0FE8084935A0ULL, 
            0xB754F7DA0DAD8AA2ULL, 0x5D2C8CFC33D21DE3ULL, 0x7882C2E2EDBB5911ULL, 0xDEF0F2A7B24CED88ULL, 
            0x16B8FC76F3097256ULL, 0x5BAEA9722B03D77EULL, 0x6C996041C53B4858ULL, 0xD55A88842CBEAC79ULL, 
            0x6C183EC90D050B1DULL, 0x68EF8DAD33D83FC1ULL, 0x80CB769C97021778ULL, 0x7BAB74EF1356796FULL, 
            0x17B9A681B0AFC669ULL, 0x6D8BA889CFAD4207ULL, 0xD1A485414E450F79ULL, 0xEC9B8D4A09F11AE7ULL, 
            0x07EDF9C88349DA1CULL, 0xD748FF14520C09DAULL, 0x3FB81A2A3548B8A0ULL, 0x48914B2AE54C1F97ULL
        }
    },
    {
        {
            0x22FB66D597F5A2CDULL, 0x773337861DE92A20ULL, 0xAA0FA4935026834BULL, 0xB5ED321B9E3ABEECULL, 
            0x879DB8DE694453FEULL, 0xB4EC5F1D33D5DD2DULL, 0x79007FEAD5495722ULL, 0x8DB87AAAA3821566ULL, 
            0xB69231FEB3BDC1B2ULL, 0x52758E30AD6F4F6BULL, 0xF4A83D17EF50AF64ULL, 0x987CE8A0443EFB7DULL, 
            0xD1FEC2C71081C948ULL, 0x1BF65A6E205EF65BULL, 0x66639A11693DECA7ULL, 0xA1C299C0A18AFE55ULL, 
            0x54CFFE64096C4C7BULL, 0xDBCFCEB2B8031A51ULL, 0xAB2FCEF4518D59AAULL, 0x71DD6EBF7AB650C3ULL, 
            0x35A4B028A319A44FULL, 0xBE54606EDA0DC65DULL, 0xAD6D3DA896FB6A8CULL, 0xC6D3A7883D078BFDULL, 
            0x2ED0FB795664D36BULL, 0x3224FE7243E871A9ULL, 0x079CFFC25BDCF3ECULL, 0x6539AF12BEB37CB9ULL, 
            0x601AD9CBF8390F8CULL, 0x9F8ED4BBFB346869ULL, 0x62816DF25EECA188ULL, 0x207AD17DE5D3B99DULL
        },
        {
            0xAFE616B4DE91F37EULL, 0xBF2D7875A22C8E90ULL, 0x3F5A1176F850FB59ULL, 0xFE1D0F8536C83AC6ULL, 
            0x0FA8C0D1A10FAE2EULL, 0x9670A430CCF68506ULL, 0xDBD57FB2BC6E7837ULL, 0x56AC24840F27C624ULL, 
            0xD89895B8837BCF4EULL, 0x988F67EBAE74EC21ULL, 0xD5B87B0C3858E2ABULL, 0xE305C1FC6EDD88EDULL, 
            0x5D8EB1D86041E9F4ULL, 0x8A9227305CA1EFE1ULL, 0x15CA6FDF8ECA96F3ULL, 0xE6C10D38CA1F8BB2ULL, 
            0x9727AB5F70149657ULL, 0x78A1C11BD8CB8808ULL, 0x885D3381B13A3836ULL, 0xD455B1E9CA72DEA3ULL, 
            0x1D38AC3ECEC05E37ULL, 0x749E6BE2D9785A12ULL, 0x9C820B7DDD45C9FCULL, 0x48F68E1EC54B4EDFULL, 
            0x2354979562CA64ACULL, 0xC90344175CA94B61ULL, 0xDBC9E26B61748C70ULL, 0x4D6E3821D3A4DA4DULL, 
            0x55BC43FFA8143323ULL, 0xAE7C2A0251B6A220ULL, 0x7CD29D14FA71294FULL, 0x3BC99AFE53CD8D5BULL
        },
        {
            0xBDE6D27493308DDAULL, 0xB0072DD9468060D8ULL, 0x262991697DBF7BD3ULL, 0xA8FC06B9666396A5ULL, 
            0x0A999B89C1B51992ULL, 0x1EEC985FF25DF8F9ULL, 0x50E9793A4B89670FULL, 0x40CEEF339115037DULL, 
            0xC306C4264C54EF19ULL, 0xC0315C67B8161AFAULL, 0x5F07EED5E335CC10ULL, 0x72D8AFBB09F54728ULL, 
            0x65B29941EF81BE54ULL, 0x3F5A24B25F427614ULL, 0x83718EEC0BD5C157ULL, 0x79646DF4F8816629ULL, 
            0xFACAAB59F89BC52AULL, 0x535E6E9490F212D4ULL, 0xFA49F85540A1BEC7ULL, 0x054986D1055994DCULL, 
            0x1C9714CCE5E79CB1ULL, 0xAA6C3C1A200BC362ULL, 0xF15581BC16956B0FULL, 0x0741DA8710A85260ULL, 
            0xC9FD7C6FFE099927ULL, 0xC6DB6136894C9257ULL, 0x3B8FDE7C3A0BA715ULL, 0x4B2D1325D740905AULL, 
            0x52BF9C85AF0A7531ULL, 0xB207C8EAE4472612ULL, 0xE54F6CD29096B2BDULL, 0x05F6D840D3779463ULL
        },
        {
            0x12112C648879F587ULL, 0xFCB8BAD575B5905BULL, 0x1648ABA21965706BULL, 0x5DCA65A411AD35C7ULL, 
            0x6EA719726B600859ULL, 0xB49CBE3D2458728AULL, 0x46FBF3CFB148BAA6ULL, 0x8E27058DBCBE4427ULL, 
            0xBD4B95E3163AD83DULL, 0x7D85E1A871EB2C30ULL, 0xD2273C25FBE7AA0AULL, 0x24F5337705AE0F1DULL, 
            0x204183682E4E0D04ULL, 0x4DF296080001E3E6ULL, 0x95F3600A0C83B1B7ULL, 0x9CC2E4993E4E0491ULL, 
            0x2C311AA5166068B0ULL, 0xECB3027F939EDE53ULL, 0xBC0EF8FD6D0406D3ULL, 0xE4A63A7B99A7C567ULL, 
            0x22365E920438B9C7ULL, 0xA6E419549707C2DFULL, 0xC679CA90F8FA27AEULL, 0xF43B4CFD1F5AD142ULL, 
            0xDD6A3A553ECDACBBULL, 0x76269395C023D202ULL, 0x7CCA9C117248E6CAULL, 0xF83DC43630B4FFA3ULL, 
            0x4E8D9C2C226AA94CULL, 0x32B3E81EA5955C44ULL, 0x8E7E4674DC8F1485ULL, 0x1909FFD58A898EBAULL
        },
        {
            0xCC91A4E5DAA9BF23ULL, 0x9A0EE8A163714CF1ULL, 0x1D54EBC244A6DD9DULL, 0x5E9E5BF21A5EBC46ULL, 
            0xD0F94205A9550B3EULL, 0x0851BC86D28BE68BULL, 0x2ACB83C9A4BB14A3ULL, 0x3A4B0D23A5C899C9ULL, 
            0x6812F3FD9D749A25ULL, 0x85DFD704C26900D5ULL, 0xE613A42C6C1CC45AULL, 0x373FE2FA837C482FULL, 
            0x433DAD58B9C233FEULL, 0x7405E8E62ADB03CAULL, 0x4D2169A9FED29555ULL, 0x3356E487D9FA1BEBULL, 
            0xD5D3AB7DA4401439ULL, 0x86A34BB5A24AF6A5ULL, 0x4DD81F969879D61BULL, 0x835F0C333939D6FBULL, 
            0x6EA61C0C950A7197ULL, 0x1A4BE018BC8816BAULL, 0xDA15B6C8B6EF8DC8ULL, 0xA453886D164EDFC3ULL, 
            0xA84D5BD57CA38510ULL, 0x08B1F0F8E179C408ULL, 0xADB59E9D45B908BCULL, 0xE4457BAD068290F1ULL, 
            0xED9FEACCE086FC4DULL, 0xD94E64A561BB3B9DULL, 0x9B8F01043C4EE344ULL, 0xFD837E7C2F07B85FULL
        },
        {
            0x3B444A1972D78433ULL, 0xC222A9577A5BA9BAULL, 0xAABC8F459D0BF29AULL, 0x6171419F97E9AFCCULL, 
            0xC498C13D3F5E4783ULL, 0xF91DD948A50FCF22ULL, 0x3935DCB833F986CFULL, 0x00D7A642CCC8FC84ULL, 
            0xFFF47E716871CD5BULL, 0x0D611C09AD11BBA7ULL, 0x142627EDD54C3F8CULL, 0xC0D69CEDB1411BC5ULL, 
            0xE023C2A61CE6D145ULL, 0xC424520E51A39844ULL, 0x78A6F0D5A8994619ULL, 0x63E016709B472DFEULL, 
            0xB036493D6B927117ULL, 0xDEF6E4A028AA891BULL, 0xD0674D76D10FF259ULL, 0xA662F0A671E0B45FULL, 
            0x56D090DF288B94E9ULL, 0x6A8C6064BA81F3F2ULL, 0x26CEF21487355288ULL, 0xF876C686C2ACEF0BULL, 
            0xE05E7B0BA81F4916ULL, 0x45256E0A4B52C0C0ULL, 0x11323DAF939699B1ULL, 0xC05BB03BE5D7BD0BULL, 
            0x5EA331EAAAC050C9ULL, 0xD1913E2CB5EDC809ULL, 0xF02E038F4282B119ULL, 0x6CFFEC7981F5EBD2ULL
        }
    },
    {
        {
            0x39D715A92A345DEAULL, 0x3F63633E37BA65D0ULL, 0xA6091A3AA7D20F0BULL, 0x477B3304043D4020ULL, 
            0x5B97D68007C8DA42ULL, 0xC4BFED87B9541D98ULL, 0x80F764D0CBAE7698ULL, 0xE804FB7F4D8145ADULL, 
            0xD3E96622733229F0ULL, 0xD90D3A9AC8DCA9F0ULL, 0x4D75AD3A799CC0A6ULL, 0xA7017EBC97186B42ULL, 
            0x033BEAAB4E443953ULL, 0x2ABC3B89574C30D4ULL, 0xB5218451456167CEULL, 0xA18B3C30F5409F79ULL, 
            0x530C9FFE5FE579EAULL, 0x6F62F2B10D77AEFBULL, 0x0E0BE9631E997DB9ULL, 0x236C6E4E0FA7DB44ULL, 
            0xAF6B01F5FD003330ULL, 0x48D0B02C2D6D7EB3ULL, 0x202E93F91D93FD62ULL, 0x0CC084423E2A61DBULL, 
            0x8538C6AC9007EC5FULL, 0x93287F249E223ED0ULL, 0x2727E2B7BCF47CF9ULL, 0x064D56CFDFDEB6B7ULL, 
            0xB6079D00B58ECB2DULL, 0x93664A6A0E00E4D1ULL, 0x5CEF35BA9D7A93CCULL, 0x52D3EDC6B5C54E02ULL
        },
        {
            0xF4C8BE10FEF029B2ULL, 0xBDFDE9EAEED4AA51ULL, 0xF965AB85DFAD8F30ULL, 0x7173E78679F3816FULL, 
            0x80113BA4EDE009E2ULL, 0xDA49F47D65B5B2FAULL, 0xAD9022774999E6A6ULL, 0x2C97902E1487362CULL, 
            0x087FAA33A1B284BDULL, 0xA121E6DAC9F77931ULL, 0x667ABC916A0AE55BULL, 0x7043FF3009A13B34ULL, 
            0xC8298E9C4BFCF7DDULL, 0x343B5852E488706DULL, 0x09385327DE341689ULL, 0xC2AB3CC859C46BF8ULL, 
            0xC3F911258392800AULL, 0xD4838224E76345F5ULL, 0x3DF301515FEBA1A7ULL, 0x2DA7713EBD6C3201ULL, 
            0xF993A8D1332A65E0ULL, 0x3A3B2CC310A3E114ULL, 0x2E9CB15A93A9287DULL, 0xCDD9C2246434FF82ULL, 
            0x10647E509843B588ULL, 0x839AFEF4E5601397ULL, 0x851BAA2C77819149ULL, 0x397AE4C99C7D262BULL, 
            0x199AF6CADD16A2A5ULL, 0x3FD69A8EFA56A0F8ULL, 0x365ADDC0FE0A21ABULL, 0xBF19FE124B1BFB3CULL
        },
        {
            0x17D6D9A3AED2FA9AULL, 0x48292A8E841E3592ULL, 0x600E5703F3977193ULL, 0x0F51F4E73F3087BEULL, 
            0x7A04373C5F9D9CA7ULL, 0xDE4B26B7AEAC865DULL, 0xE27FAC61E5ED24D8ULL, 0xC8690526FC7975F7ULL, 
            0xF28955B5B97DF43DULL, 0x60AD2576101AD1D0ULL, 0xB6DAAA503DFAB2E9ULL, 0xD75595B0FA237158ULL, 
            0xE7B76F24D902E72EULL, 0x9717B90E92D2EF53ULL, 0x1ED86D654F05AE1FULL, 0x83B84AAFB691C8D9ULL, 
            0xB52FEAC269413F60ULL, 0x176D5D25978BCDB0ULL, 0x8DC6CA538A45C137ULL, 0xEBFDEFF06EF9F913ULL, 
            0xA167059582C07E36ULL, 0x265D0A3739B78C25ULL, 0xA4AFD221D4E5CE73ULL, 0xE6D67D9FAB4E4EB6ULL, 
            0xE99A4268401B3A29ULL, 0x69BF3C3F8435886CULL, 0xC9EC850EAA3027FEULL, 0x94051FBEC9802E7CULL, 
            0x1A09311484DB3E4EULL, 0xF9880DB30C8585C8ULL, 0x8E83A9391E2E58CDULL, 0x92F8EF12F992956FULL
        },
        {
            0x9C08B60FC4F1D091ULL, 0xD8B3D866D2C9893DULL, 0x794D170C2DD62387ULL, 0x74B3CA3A6A1A39ECULL, 
            0x172F9A6097E39192ULL, 0x90C125776E8B009BULL, 0x0B08BD13BCD34F1FULL, 0xB7B7DC364B9D79B4ULL, 
            0xB7A5D5A84263D821ULL, 0x7C421E95656B277CULL, 0x448F497C8ECD17E0ULL, 0x7256B18C09EA5979ULL, 
            0xD24C433E00B8A960ULL, 0xA990ABF967E99134ULL, 0xCE467F77F36653ABULL, 0xE6FC401BAA1B8D66ULL, 
            0xF0D60551DACA4A72ULL, 0x2A8B90FB7062CEB9ULL, 0xA2A7B8985A28D0FAULL, 0xD337FE8095E393B9ULL, 
            0xBE9D0542B132A64FULL, 0xE5AF7C580B788183ULL, 0x367CD4420F502EF1ULL, 0xEC5E3CC99BDE1901ULL, 
            0x5917F99C313696C4ULL, 0x7AFBFAA7715CCFCFULL, 0x3DCECEABAD993A66ULL, 0xE40B8A1748C74B12ULL, 
            0x1AC0324E4B166953ULL, 0xFA18B30AF91F368EULL, 0x6350EAA5F19A389FULL, 0x72472B719A288DBBULL
        },
        {
            0x2C217817C5B23488ULL, 0x02447F5DE76C2BB9ULL, 0x4BB344BA6B2A5E3FULL, 0x0B8AB53DAB016586ULL, 
            0xADC801A1265F76D4ULL, 0x5840CC953E9ABECCULL, 0x4E499149DB92A91BULL, 0x66022E7A746D69CFULL, 
            0x74FB7DD80625E8DAULL, 0x7A1C0CFB0DF72CD9ULL, 0xA7EDDA107074B3EDULL, 0xF5340E033E957FF5ULL, 
            0xB177C0CD9666947BULL, 0x4BC33EC9639B6AAAULL, 0x97F445CDB8C52867ULL, 0x4B3884B0E82BA5A3ULL, 
            0x946A7A75508528F7ULL, 0x60C62758074614ACULL, 0x76E4C2C825428884ULL, 0x440269DA819DBD26ULL, 
            0x2EAF0658C1E9B831ULL, 0xEB4F41245988380EULL, 0xE273903C37C83553ULL, 0xD3FD199F3589BE03ULL, 
            0x03411F5E906B2F1EULL, 0x68277485501DC6BFULL, 0xAD83E1830BC27BAFULL, 0xA1350A0C2ECC2658ULL, 
            0x0A7E52A09F44D238ULL, 0xF6D7468EF6B2135BULL, 0x02B600B7A831162CULL, 0x58055B915FFB1935ULL
        },
        {
            0x85B30B97575413F0ULL, 0x8D7F0BC1F8F71421ULL, 0x741C07DEECD12D97ULL, 0x0D259F9BF3C81E79ULL, 
            0x76F5BD9A55875F61ULL, 0xC5201B08D6BD88CEULL, 0x5810E98F928ACEB8ULL, 0x419504EDC3062B9DULL, 
            0xADBDE608D634D6CDULL, 0xB304E440140E4EAAULL, 0xACFC898FF3B22310ULL, 0x31CC581A041CF11AULL, 
            0xCE702DE92E8F32C9ULL, 0xC4608A5FAEBDF945ULL, 0xECC3CC5C0E152415ULL, 0x28ACF84BAAF3274AULL, 
            0xB70A53E153910230ULL, 0x5670D2E8EE70410DULL, 0x830ABE6E3CBF9B6DULL, 0x06EE938C60686A06ULL, 
            0x4D2BD623B2641BFEULL, 0x24B9443B7E949FF5ULL, 0x48176C4AF9B7B064ULL, 0xE51DE6ECF5D1E39BULL, 
            0xA46FE9772C0B9958ULL, 0x171578321E5C9C5AULL, 0xE50FF70073E4E8E0ULL, 0x2C695E361BA0CC42ULL, 
            0xBBA9DEEBB635C446ULL, 0xC865417AD5DD5ACAULL, 0x250CE7C64EC2D87DULL, 0x6F26A19705FEDEFCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseFConstants = {
    0x54DC69F4613C44AFULL,
    0x0025E5B0C8328D91ULL,
    0xE9F111EECF33AA81ULL,
    0x54DC69F4613C44AFULL,
    0x0025E5B0C8328D91ULL,
    0xE9F111EECF33AA81ULL,
    0xC4C48B50136C1C82ULL,
    0x026BBA33AED450C9ULL,
    0xAD,
    0xB6,
    0x8B,
    0x46,
    0xB6,
    0xBE,
    0x75,
    0xE2
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseGSalts = {
    {
        {
            0x74E0008EA2162A8BULL, 0x7A68C41F2DB9F3E4ULL, 0x28AB9085264E675EULL, 0x68A9B4EF45F1341AULL, 
            0x2EB6C0D3D6585961ULL, 0x8CE5565C2446FBFDULL, 0x33A721713EF9B5C6ULL, 0x0E8637C0A263C10AULL, 
            0x2B143BB0D2DC2DA5ULL, 0x9FC079DA7013BCABULL, 0x87511D049D560844ULL, 0xA7F294132D982951ULL, 
            0x38AEAEC15DD7D360ULL, 0xC8EED79CB5A2606FULL, 0x402B6795B8A281DDULL, 0x52C37FF795312A14ULL, 
            0x14C319B81B33D210ULL, 0x6D6DA0EB32F6406FULL, 0x2D91B1418945A5D4ULL, 0xCF879E3D00E751E8ULL, 
            0x7CAD904C7A58C484ULL, 0x795688B71402C9FEULL, 0x042A97ECFAC04A47ULL, 0x1866763C16F09B50ULL, 
            0x3CF5362AB4E9B4F6ULL, 0x14A271D9B5008A48ULL, 0xD1FFBF11FA078F77ULL, 0x54524D578C3C2CCAULL, 
            0x7A7F17D6AC7E7B94ULL, 0xD04F6AEE7B44AFABULL, 0x5D04AB4964850271ULL, 0x86F338A88A95D4D5ULL
        },
        {
            0x11ED8F43720ABEF6ULL, 0xBE0682293981E2A8ULL, 0x3370E41410FAB98DULL, 0x15251665075152BCULL, 
            0x99710942A110EE99ULL, 0x7415BB555729A468ULL, 0x162DDBB54E909AABULL, 0xBF9AD8613B1A2416ULL, 
            0xB3AD8C858C14587EULL, 0xAB9EC472463E608BULL, 0xC11835939DFDC06FULL, 0xCAF1532FB3FC0938ULL, 
            0x4E5C08794ADA0E1BULL, 0x8F713F9D91D5E5B8ULL, 0xF2DC412DAA8B55A5ULL, 0x13D15BFED5DD161CULL, 
            0x25EED14E2AA508C6ULL, 0xE807C79E9A2AC7CFULL, 0x75B1F80CE719ECB1ULL, 0x9463EFF4A5748979ULL, 
            0x31C904DBA3DB5948ULL, 0x402FB1B2AA2071A9ULL, 0xD6A856860C545A3EULL, 0x66353305CD7D4F6AULL, 
            0x857FD402415B7169ULL, 0xC80866CE4B86B81FULL, 0xA4D0CCE84BF2567FULL, 0xEB5EC9871E9BDF9EULL, 
            0xB5F23B6E50265605ULL, 0x3AA9B4F0BEC2DF67ULL, 0x23A7FC2F54273CF5ULL, 0xB28459B309946B71ULL
        },
        {
            0x46B926EC721BFF5BULL, 0x9C1CBE18A4CDFFCBULL, 0xB4215C53B1801C92ULL, 0xC544ACC21351D6ACULL, 
            0x94354757C237CB39ULL, 0x22A1B38525AC1C2CULL, 0x66430B015EA2825FULL, 0xB6A8849B3090C64FULL, 
            0x363C7B9B4245C5F6ULL, 0xA3854F2607D57F2DULL, 0x8D2A8193378BB83CULL, 0x346B2648A6158884ULL, 
            0x0054C9B63CD5168DULL, 0xF660B9F3BD7F1B8BULL, 0xB1D600B0306AAD42ULL, 0x0572AE738DA10457ULL, 
            0x36A4E6808A0B18B0ULL, 0x61C860B16693EFCDULL, 0x248CD22C2EEA702FULL, 0x902DED0F6B5DFE0CULL, 
            0x563BB289E2834F1BULL, 0x6EAED1F72DC86937ULL, 0x16F2587A94BC7369ULL, 0x1095B336A6F4BC7FULL, 
            0x23003DFDA545A70CULL, 0x26AA116390E2AA2BULL, 0x92BFD05292EB5A72ULL, 0x7E675B1E8B9888C6ULL, 
            0xB74BE96AE3C6C8AEULL, 0x3060721052D53DC4ULL, 0x10F9FD239C6A4513ULL, 0x02A0044018B3D9D6ULL
        },
        {
            0x0F7B450EB5A5011BULL, 0x4FE19F2A1CB9B091ULL, 0xD244E12844F9D1ECULL, 0xED743D3019D526A5ULL, 
            0xF94FDDD63E5339ACULL, 0x11E3C6002C2CDDC3ULL, 0xC7BFB7F7C7172BF8ULL, 0xFB5F5828E5228916ULL, 
            0xAC2FD13E571C7FDDULL, 0x3580238885E60ED9ULL, 0x75B2734382239A5FULL, 0x8398AC55FF5BC957ULL, 
            0x1661782C377C4B43ULL, 0x57063EB2AFFD5EB3ULL, 0xE3A07E0AB90C551DULL, 0x2C3C67FE30B82B32ULL, 
            0x2FC6E5464299EF79ULL, 0x7E930FF42EA0F907ULL, 0x74D0DBA9707EF182ULL, 0xB3FEB5846174EAAAULL, 
            0x34393FB789D57072ULL, 0xD7A1B96EF5BD14FAULL, 0x1ADB8AE3D12A3CAFULL, 0xB5ECBEE01C0FA8F7ULL, 
            0xA84F8AD2E2D72B9BULL, 0x5E6C7A7C92040E9DULL, 0x0B67E25D34F83A68ULL, 0x6FCC4A28EBE4A616ULL, 
            0x65C78F2385E44FA0ULL, 0x03B84B7DCD79447BULL, 0x92B9A17145CAC6B4ULL, 0x3C4FD1EFDE418470ULL
        },
        {
            0xCF4E2795B683D80CULL, 0x64C848B00AAC16D1ULL, 0x21A8B4F56C63DDC2ULL, 0x00A2498C509436E1ULL, 
            0x5F2754ABFAB00C5EULL, 0x2E9A1710A7399F7EULL, 0x32E4119DA51E2F93ULL, 0xCE24EFC499035EA5ULL, 
            0x903E4FF705D49C83ULL, 0x14CA544C41F85A2BULL, 0x90A59985720F1F27ULL, 0x96E23D2A9F3A8916ULL, 
            0xD2203E175D6215DEULL, 0x4EE9A2FB8F8D3AE1ULL, 0x01171EC2C87A88ADULL, 0xA7CB127F8BDDC5E8ULL, 
            0x85C474259FA48DD2ULL, 0x58AD08C24149F7C5ULL, 0xA7424FE91528039DULL, 0x5D87602AB891BF3EULL, 
            0x5CFA59BA40CFB3FCULL, 0x301F2FA8501DCD80ULL, 0x2C7B32ECA6A149CCULL, 0x1AF2DA127FF9EDC3ULL, 
            0x60CE2B01396EF9ACULL, 0xB36B77A295C719FAULL, 0x7EE3DEB96F9EB0C6ULL, 0x66A30AA077C918F4ULL, 
            0x3D75349F30CD7BEAULL, 0xDE84270449B210E8ULL, 0xB53DBEFD8065E750ULL, 0x96F6BAD2F33B9F68ULL
        },
        {
            0xD0EE9468C83F03B3ULL, 0x22629B7C4F68DEFAULL, 0xE7D22D3BAB153381ULL, 0xEF6A76D09431948FULL, 
            0x3987FBA4DA27AB7EULL, 0xE7C94FDF39C47DBDULL, 0xD118B688AD9FAC72ULL, 0x9172ADADFF4338F3ULL, 
            0xD31878A17E5C7E9AULL, 0xD0C7D0BB402CBC9FULL, 0x18B01A1CCCC1007FULL, 0x34571BF5D89429A9ULL, 
            0x0FD6B980CF1328ACULL, 0x38E0683771C1B7F5ULL, 0x905671BD3D3B273BULL, 0x5EFE1D48AA9B928EULL, 
            0x2719DDFF94151350ULL, 0x6664EB4F24429D68ULL, 0xCC645C67E9498076ULL, 0xD22139AABECE6507ULL, 
            0x927988FF1A5A9F82ULL, 0xCD6BF14FD1339FAAULL, 0xF4BBE98D031DC4B7ULL, 0x8EF09E1458269EEEULL, 
            0xC201F2FD9F74A61DULL, 0x88B044066B933CB7ULL, 0xFD0291A9743B3BFEULL, 0x3DAF41B40FD73E35ULL, 
            0xEAC7A6054B322C2CULL, 0xD71D9D8BEE6DA0D2ULL, 0x41796B1A3F140A5AULL, 0xB771209932588A13ULL
        }
    },
    {
        {
            0x1563086A7334D7D4ULL, 0xC04E50A35F99276CULL, 0x85404BD301F0A56FULL, 0xA53BC98A8A3DC242ULL, 
            0xBA452E5DCAE661CAULL, 0x6982C36242DAA8F7ULL, 0xD5EF6881A807919EULL, 0xBE2D28EC86D0504EULL, 
            0xD966BDDA64DAA3A7ULL, 0x5D851CB64A5067B7ULL, 0xAF77D17E23C92649ULL, 0xE8295C4303E50AEDULL, 
            0xB10404919E2E5A47ULL, 0x2AC089A5F7445007ULL, 0x3B6D177B0944981FULL, 0xD85194DB5B4CDF3BULL, 
            0xAA5C598136947656ULL, 0x1BB6C5DCD5E2A757ULL, 0xC3AA70826AA6D128ULL, 0xEA42D3DCC7DD5B61ULL, 
            0xB4217511D120F3EDULL, 0xDF59732DEE8C8230ULL, 0xAE77225A3E8D5C80ULL, 0x140BCF0CBDCAC2EBULL, 
            0x594EFBF5B5CC4EC6ULL, 0xEA202835334A587BULL, 0xFC6B3F7E3C8F2371ULL, 0xE6D9A8093F689382ULL, 
            0x33DFFA80CF3CB736ULL, 0x9F6DAA5B435CAC3DULL, 0x296C27E7D72B859EULL, 0xFD48BC2AA4ECD5B1ULL
        },
        {
            0xDCDA0D6EEFBF1B15ULL, 0xA70DD89B090A6D48ULL, 0x107F77B501482E45ULL, 0x2E034385CF90EAABULL, 
            0xAB4F12DE8DB6F076ULL, 0x94522601EAE4E91FULL, 0x0F5CBF2CF0BD7C66ULL, 0x5B3D99034A7146D0ULL, 
            0xAF536839629A3803ULL, 0x6350001917A99C33ULL, 0x483C1CDDB18109FCULL, 0x05708FB44D4BDFB0ULL, 
            0x59458903E6C9FA32ULL, 0xB0476FA2BA43FF32ULL, 0x76A76D87BAA7D8D5ULL, 0x65FF2DB2B41E59EFULL, 
            0x2F559329CF2F3A28ULL, 0x5304C40E4BDA406AULL, 0x2FF6EC227AF48D4DULL, 0x641C475F7D86D78BULL, 
            0x95EC0002997D6EFFULL, 0xDC710BA0CEC8A8F7ULL, 0xDF852A2497565E8FULL, 0xBDF75C753505DA5AULL, 
            0x130F9E48AC3A60E3ULL, 0x9ABD9734D3330604ULL, 0xBB790CDCB0A081D0ULL, 0xAB04373BA875B483ULL, 
            0x0DC6C2252F3B4842ULL, 0x35F4693263865779ULL, 0xE1FF53327C2D416EULL, 0x2DC959603239AED8ULL
        },
        {
            0x0ACDD3CF25BDE2B5ULL, 0x308C56A7227A62E8ULL, 0xF1A41FBADC9F22D5ULL, 0x95FE16E20D32DA0DULL, 
            0x97D2F6AAF788ECBAULL, 0x4CA1C3BEE29C6071ULL, 0xE030A6633C94D95AULL, 0x989FB669087324E5ULL, 
            0x1A94F88C4DAE05CBULL, 0xEF92ECE1983184B2ULL, 0x3FCA49CD03A39577ULL, 0x831EB7C8EA684714ULL, 
            0x44A4B111B7BA8E9BULL, 0x9AE52BEEB5578A15ULL, 0x41633BAB6883D32CULL, 0x206A19D4D3E3F866ULL, 
            0x292376CB469925B6ULL, 0x89C9770205739DCCULL, 0x38A21FE770306076ULL, 0x7E02B67061C1A17AULL, 
            0x9726054CBDF6294DULL, 0x45F010403E05862EULL, 0x3120E656C25FCE73ULL, 0xB13FE1F2D3606A72ULL, 
            0x6A0BD613CF3A31E0ULL, 0x2A13FD9C0F89221CULL, 0x5E2BD27EE50BF203ULL, 0x63E8379536D307EEULL, 
            0x4F13AE7696B37E30ULL, 0xB62614A1C9CF4D8DULL, 0x76C097C030182D21ULL, 0x90A395717C1D796DULL
        },
        {
            0x198A726778A92697ULL, 0xB911BE6C33B73553ULL, 0xC55B0D48B1C563CAULL, 0x2FB3111F377E0590ULL, 
            0x275DA80D447F773CULL, 0xAF4FAE685F3665F5ULL, 0x8721542F9A0C075FULL, 0x01061A8D7D5E69DAULL, 
            0x35CBDE07E1C7AC2FULL, 0xE19EB75D09FAB1F0ULL, 0x7C8DE2BB00664AD4ULL, 0x902CC7DD3F4F935CULL, 
            0xF1F4028C10A27830ULL, 0xD0A7F3BDEB581316ULL, 0xC5991F19FEFCEDE4ULL, 0x078FE0EFCE5D4CF2ULL, 
            0x729E753A6A00AD32ULL, 0x82ED3F298FA94D1CULL, 0x282B26E3CC5C7401ULL, 0x2A7406B7A89EA78AULL, 
            0x828A3F49042112E3ULL, 0xC519AD17749403D4ULL, 0xE2AA38BF01A09BCAULL, 0x8E8F867C4209539EULL, 
            0xCCEF4F11596C13B6ULL, 0xDFCF73C3B58745FFULL, 0x66C04CD61B68E73AULL, 0xB718133C0009EA55ULL, 
            0xA04F8A3C6DD58D75ULL, 0xFC6EE6B3627F793EULL, 0x17986618421D2226ULL, 0xFC5942F2160B710FULL
        },
        {
            0x597F375C5358E024ULL, 0x4E5E87B456BDA034ULL, 0x17F9CA6DABED72DDULL, 0x4AE99A87206C31A6ULL, 
            0x1C11B9E4BBD4FE4EULL, 0x09E068406A119682ULL, 0x4D9713BF10778781ULL, 0x0E4B03C02343F997ULL, 
            0x99F47311D7C047B5ULL, 0x6EBA54DC2876BE9EULL, 0xB32C538E8923A361ULL, 0x287BA7788FEE12B2ULL, 
            0xEEBC4A764075CA43ULL, 0x97A8CAAED508D7EEULL, 0x04923DE1B932DD19ULL, 0x36981848870DA57DULL, 
            0x41D8E7BAA3504603ULL, 0xB76AA45C82A7D3AEULL, 0xA493DE362964DE0CULL, 0x41B93F4184FAD9F1ULL, 
            0x687FB829F6A0EBBEULL, 0x15A8E127D023A09DULL, 0x7042D33195CFE660ULL, 0x01F9739188C24CDFULL, 
            0x9E70E7D3A89832CBULL, 0x9E88FE6BB0F57752ULL, 0x390C2334037520A7ULL, 0x018EB53A879F7071ULL, 
            0x85FFB71D0BF69D26ULL, 0x9B3990A21C910F2AULL, 0xB9D74645C770D78DULL, 0x6B881BDFAFD433B2ULL
        },
        {
            0x97690ADA310A60E1ULL, 0xB0871D2EBD0CAB25ULL, 0x1316A3A27807D7B8ULL, 0xD8EDBBD95EE58FB1ULL, 
            0xEBD0C5EF3E95CF9AULL, 0x1A84FB0A549CDD7EULL, 0x0EB5E2783CACF3E1ULL, 0x11D1083E3E1905C8ULL, 
            0x3D315AAF909A9BD0ULL, 0xE6DD7B9F67114E54ULL, 0x4718D38ACD853AA6ULL, 0x885FF775E499D23DULL, 
            0x337AFA0926A5BD05ULL, 0x11474FA0F18368C5ULL, 0xEAA072FFD70A97D6ULL, 0x83978EF322B07BE3ULL, 
            0x7B8F356856AE91A1ULL, 0xA7D66C9091EB67BEULL, 0x6AA9F1603131D18AULL, 0x2146D163830B8243ULL, 
            0x3A6A15E72D1B0B28ULL, 0x34942CD4DD7C3339ULL, 0x148190692D02E0B5ULL, 0x7C3BF242F2D142FBULL, 
            0xE0B43B74C1E597D1ULL, 0x5495EE29749A2770ULL, 0x9A51EB7B11B2DD41ULL, 0x09AA37AFC76344AAULL, 
            0xD8425DE6CF8C3BF9ULL, 0x60A0C5AE5AE87AA8ULL, 0x31217C607E98B9D7ULL, 0x850EF6E9C3A990EEULL
        }
    },
    {
        {
            0x67E06093F3A118A4ULL, 0xFB3E1BEE7463E11CULL, 0x52CB8E79E063E801ULL, 0xDE654BF8E59272E5ULL, 
            0x06B675EA714E0BCDULL, 0xB873592932FBC277ULL, 0xF1A504A826631E24ULL, 0x48B689D44533F186ULL, 
            0x9ADD37A53DB0E4D5ULL, 0x3B3DFF051DD6F658ULL, 0x7F2789018D9AA2B9ULL, 0x5CFB49A4BEC2DEA9ULL, 
            0x752EFB899A878137ULL, 0x1ADAB0B94C3D468CULL, 0x2E5AA4274E5900F2ULL, 0x46852429442D80AFULL, 
            0x0F323E048E9F62CFULL, 0x7BC0201489EFE338ULL, 0x34573684763109B2ULL, 0x92307F21D9149A0DULL, 
            0xE8D78101D4557A72ULL, 0x6C4D75389E3F9DF6ULL, 0x7F70B20A3481BDC9ULL, 0x1AF0BDAA145CBE0BULL, 
            0x805C4DF492F0CE7FULL, 0x062640B87BB692C2ULL, 0x7C7BDC9158199A05ULL, 0xADACD068DD14C21FULL, 
            0x1210911258119FEEULL, 0x34EE89ED58B67B2AULL, 0x4312CAFC76213FC1ULL, 0x1D274BF7D4F678A2ULL
        },
        {
            0x26A30420DCE4D489ULL, 0xB035E651035E1E9BULL, 0x94F26F8CFAB1DC96ULL, 0xA36CC35B6AC7F1EAULL, 
            0x87569FE23CFEFE86ULL, 0x087DB27A50423097ULL, 0x4E7205F115897EE4ULL, 0x97AB311C2FC47D7BULL, 
            0xB7331D229FB78E08ULL, 0xB6C7FFDF6440FB4CULL, 0x308C2370183F8DDEULL, 0xB654C8824DBBFDF8ULL, 
            0x21EA1B9939B30795ULL, 0x278AA176588EBBBBULL, 0xF6F9C65790AAD55EULL, 0xBEBE8520C3153C91ULL, 
            0xA952F001B0593EE7ULL, 0xCA84F70ED2C1C4C2ULL, 0x0937E2E52B91557EULL, 0xABB9465833BF018EULL, 
            0xDFD1CAB9F86B9893ULL, 0x25BFE30D609DFCB1ULL, 0xEB8498DE11762977ULL, 0x7ECC44C868650180ULL, 
            0xE33D3B3941955441ULL, 0x6002A334E4DB8DE3ULL, 0x2BB3B7DEE1BC5D80ULL, 0x772F77A261FB6849ULL, 
            0x47A06B5423C2AC5EULL, 0x67853B5D8B97D6B0ULL, 0x535DCFCD37181A89ULL, 0x10EFF0C31F0C63C8ULL
        },
        {
            0xCE75E8ECE190ACACULL, 0x3006FFCA3E45552BULL, 0x949B3323765ADBFCULL, 0x3B5ECD5C655A63E4ULL, 
            0x0177C1FA02E63E34ULL, 0xB5D0428A4BC81A79ULL, 0x9322A085EA681F3DULL, 0xC7C33D61EABCAB09ULL, 
            0x33BA1496A3323F12ULL, 0xA359E8A84E33CF93ULL, 0x96EEC2083DC4FE53ULL, 0x36A3A768F53075D9ULL, 
            0x5F389247B3FB6039ULL, 0x5498A47CEA1B0A60ULL, 0x9F379CF12F1B0AB1ULL, 0x1B3115808CE7A9D5ULL, 
            0xEC69D3AE1E0600D5ULL, 0x32BCCFC1CBFE394DULL, 0x56D8D4F8E78072FFULL, 0x2B4473EAC7C62037ULL, 
            0x2F3389C21E58F89EULL, 0xFC6D8CC5311DFA56ULL, 0xA88C9B36C0BB4B45ULL, 0x62E14801BB42B3E5ULL, 
            0xD48E8D6F1C6DEEBCULL, 0xE5430F89ECB85B47ULL, 0x1A0B024DE5B78D14ULL, 0x77CA7E8FF024C5D6ULL, 
            0xA93607FE01031810ULL, 0x2497E951D411EFB8ULL, 0xB5F3B10828648FDDULL, 0x1EC268EBDB6BB284ULL
        },
        {
            0x0519E2B89CFE9511ULL, 0x1C062896FDAC7638ULL, 0xEE06B30014B9FBFAULL, 0x95811E4CBF5AE642ULL, 
            0x92234B072653F80BULL, 0x9A87C75443ABBCABULL, 0x550554A415788214ULL, 0x13AD0F76BD2C25B6ULL, 
            0xB5720DC46B6AF227ULL, 0x70F55254142C5331ULL, 0xF75AA038D507A78FULL, 0xB1ECD1843B73689DULL, 
            0xE7C5846F18D22B43ULL, 0xF58CB55DAAB3D527ULL, 0xD39C75CBCF809A99ULL, 0x2F3FB91FCE5917FFULL, 
            0xE65162D8C74C26D8ULL, 0xED1AB7F45CC4DBC6ULL, 0x141787325B660DA2ULL, 0x351D0464A5C84B0DULL, 
            0xB3EE661078131D2EULL, 0x4D4999F54E0C15E6ULL, 0x0952F9E799130EA2ULL, 0xACFC852E1FCC5D6AULL, 
            0xA536A1B686F15461ULL, 0xD2872A90854E61C5ULL, 0xD67DB782981CBF4CULL, 0x92E0F1B558AF2502ULL, 
            0x80414C4A9636D705ULL, 0x803069D535D0A52BULL, 0xC39C2C24DE72266FULL, 0x975AA25297489235ULL
        },
        {
            0x4FA65600E86562FDULL, 0xFA3C6C47B783C149ULL, 0xA9E2BE612DE2857AULL, 0xEF804F52F7CFD859ULL, 
            0xE13B04672AC4B6D6ULL, 0xCCE01ADF40F18EE1ULL, 0x35FB8464E7EAEAAFULL, 0xA8E2AE6BAA872C2FULL, 
            0x2DC77051B4AE4FDAULL, 0xAE8CD63499DEA77AULL, 0xF737A747D252CEEAULL, 0xF6AE81C8F4E83751ULL, 
            0x887EBCF948BA171EULL, 0x50F5098F710D40A5ULL, 0x84F06E1ADD9E5B32ULL, 0xE41DA10BC2D8B1D6ULL, 
            0x4ECF6CE7B75C6B77ULL, 0x8EF9586E0BE1480FULL, 0xBBB1EE98796EB448ULL, 0x90CF2CDC491BC201ULL, 
            0x81B89E543D25DF2DULL, 0xEB66B182C8BE0430ULL, 0x4115920D66242F90ULL, 0xF183FC32AD7E4E02ULL, 
            0xC5E001AB1B546546ULL, 0x83B529522BA17BCDULL, 0x50708E88142EC4FCULL, 0x56E38BDC2F9106B5ULL, 
            0xB64CAFB9CB777D35ULL, 0xD91D7260165C6278ULL, 0x19356F57AC97A670ULL, 0xDBF87014D99A192FULL
        },
        {
            0x6EA3E36523B5C409ULL, 0x926A16844920020CULL, 0x9349E5C3AE5ACB5EULL, 0x9AB598E1EB45EED2ULL, 
            0x401F7125E1A9CD47ULL, 0xAFD49EBFF2E17740ULL, 0xAC4634B149E812D9ULL, 0x1BBC382B31AC9DA9ULL, 
            0x20ADB67C3460C7E2ULL, 0x9A9D815DDAC64A1BULL, 0x44D1E3310ABD3BF0ULL, 0x3A1CBEA0BF217668ULL, 
            0xB727391A70C53766ULL, 0x56A695F6799FA601ULL, 0x182F748F820C9EB9ULL, 0xAEBB1DB00C975636ULL, 
            0x9FE81A8417E878BDULL, 0xF130C93C82A7D601ULL, 0x4DEF85CDB86157B9ULL, 0x8AE2D5006976A977ULL, 
            0xB62501FB3A61A782ULL, 0x06D4CF677EE7D754ULL, 0xAD0D26FE33F5F3A4ULL, 0x484789E21B478B32ULL, 
            0x85A832BB451D2B67ULL, 0xB8309C87EE0602D9ULL, 0x7AE017FB237CA684ULL, 0x420DE6FA1D8EA363ULL, 
            0x349E4E7699F83BF9ULL, 0xE155CB3B84EE84EFULL, 0xB4D20D7B46224851ULL, 0xB72159225312A321ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseGConstants = {
    0x9F460774AD7D97D5ULL,
    0x2D73FF30F17657D1ULL,
    0x2230182B35265C6BULL,
    0x9F460774AD7D97D5ULL,
    0x2D73FF30F17657D1ULL,
    0x2230182B35265C6BULL,
    0x3B78BDE2298F9195ULL,
    0xBDF1D8A4814DAF1BULL,
    0x2D,
    0x50,
    0x56,
    0xE3,
    0x5A,
    0xDE,
    0xB0,
    0xC9
};

const TwistDomainSaltSet TwistExpander_Alkaid::kPhaseHSalts = {
    {
        {
            0xB8AB3675DF02C039ULL, 0x236180A23C49D4B4ULL, 0x3DC5263FBF7EDA03ULL, 0x0DED7555D4042318ULL, 
            0x7A8C09A014A26960ULL, 0x034D45EEC4A4944FULL, 0x71BAFDE20A2E07AEULL, 0xB8010F71ECC0D011ULL, 
            0x61E93EA9ABF07E77ULL, 0x06371D3815253FCAULL, 0x85E1E82136BAA87CULL, 0x891E1BDA57A3D44EULL, 
            0x1094F03BB23D8D98ULL, 0xA7ECE0D69B6B173FULL, 0xA90CAACCF0790E53ULL, 0x8E4E36D165D3890BULL, 
            0x71F17D6D183E4944ULL, 0x20D7585004B3E1AFULL, 0x385ED70DFA7BAEBCULL, 0x2C09ACEEF25C73D8ULL, 
            0x0B8DCF01845530F0ULL, 0x684D906DBB90E0A2ULL, 0xA043CE1E5C5EB2B6ULL, 0x0A98F4350EE42BF6ULL, 
            0xCC96448F971AF819ULL, 0x95A3716C629E0FD1ULL, 0x7877A378ABB9DE89ULL, 0x36EBD46B2B92823AULL, 
            0x9E587339C0DD0C37ULL, 0x9C5C6E7A92A4AFB0ULL, 0x295F207C8921692DULL, 0xA8DB943119BA84CCULL
        },
        {
            0x8CFCF0CDDCEBB685ULL, 0xF311E3F0325107B1ULL, 0xA57BFE37DCF170C1ULL, 0x27B9AF9CA0F49F4FULL, 
            0xD7FE4A61B84A5090ULL, 0x562C95BB78AA5E23ULL, 0xC299C0F35BAD5CEBULL, 0x1B2B5198A464591EULL, 
            0x3A6FC7AD5844120FULL, 0x39C423A231880D9AULL, 0x8C0F7CA9F4E0EED4ULL, 0x2328A5A41234C8FFULL, 
            0x5939781295598822ULL, 0xE571BE38B2430DB6ULL, 0xB7DB473F83D5B46AULL, 0x280601AFA1883575ULL, 
            0x227E7E8D2092DFFBULL, 0x847D383AF8C5ECF3ULL, 0xF2B3B62F0A990FFEULL, 0x2AD0239DE0BA8FA8ULL, 
            0xBE3A6FC6508D6015ULL, 0x843654A36C81A39AULL, 0xFAA8A1B6F9CE69F3ULL, 0xB60546F59CFB3670ULL, 
            0xD066408AA57BAADEULL, 0x281ED4B2D52C9CDEULL, 0x1012C7CBE66740DDULL, 0x1975A079E35810CDULL, 
            0x411D453B10A2B51FULL, 0xE1E4E7FFE3411A78ULL, 0xE94A660E72F8F5A9ULL, 0x130A448634D09F9AULL
        },
        {
            0xD6EAC89433D20149ULL, 0x26DA4AB2D12DC282ULL, 0x0961BD964F02E5DCULL, 0x1C0F3C856B45546DULL, 
            0x3939CF99E516C850ULL, 0x48A513627BE7C0ADULL, 0x28C40A1931703376ULL, 0xCEECC14381F8490AULL, 
            0xE2BFFD446443578BULL, 0x20E30079094A6F64ULL, 0xB3BF7CBA31E46A86ULL, 0xD6C0527BBCFB864AULL, 
            0x094740EFEF4A2238ULL, 0xD47239FA867800A5ULL, 0x73B66DF5F0C405ACULL, 0x7B8037D74FBB8215ULL, 
            0xAE81C15A1EC63E58ULL, 0x76E1C7C01CF645AEULL, 0x7FEB6616497DBA62ULL, 0x0BEAE1F70890D0EDULL, 
            0x9055353598AFA5A7ULL, 0x2211AF9B987F52DCULL, 0x22D7D1A642D79F8DULL, 0xA62718CAD9C86762ULL, 
            0x21571CC957465302ULL, 0x790FD4B373834CC9ULL, 0x43B4505DAAE38DEEULL, 0x1904E33F8FDEDD2FULL, 
            0x747B9B006B34165BULL, 0x33D6B853C2FE4DDDULL, 0x439B305B081AF202ULL, 0xDDBB7141B22EF025ULL
        },
        {
            0x41E7946529EA9400ULL, 0xDEF9F7021C712880ULL, 0xD8A1610D237DC8A4ULL, 0x4EAD74EC339F59C7ULL, 
            0xF47046CF48E8F910ULL, 0x258FCD8FC2DB1589ULL, 0xC9CFCC1B279F1475ULL, 0xE7CD996ECDCF4564ULL, 
            0x583DBC33966E23B6ULL, 0xD3491A7B70D973B5ULL, 0x6C3BFD3EA3588FD5ULL, 0xE1A084D98186750FULL, 
            0xEFC659F5406E86F7ULL, 0x9BFEDBE092A5F4EAULL, 0x5D8D5D73629BC801ULL, 0x060E2966D6D5309FULL, 
            0x2587F80D114EB76EULL, 0x09595471FCE59127ULL, 0x30FB2095E322B211ULL, 0x04639AC28EECE13FULL, 
            0x0ACDB73C3E653AC7ULL, 0xC8995B7C1ACE1C27ULL, 0x73BD190981CE56F2ULL, 0x345A6FD878E38695ULL, 
            0x9F6EB650CE813902ULL, 0x9A624A649607675BULL, 0xA298270B6E54FB4DULL, 0xECFD15A0EA164698ULL, 
            0x4723BCFD5A27EB8CULL, 0x741D3D16D7D4213FULL, 0x4BA2BEBD7F49FF91ULL, 0x59F6811D1BA39971ULL
        },
        {
            0xFC61F848E8D42976ULL, 0x3724C78C0432CD76ULL, 0x589622B562E209DCULL, 0x84B01C1BAF471DA7ULL, 
            0xEF0A06F4AC172773ULL, 0xA780BD162C498BA2ULL, 0x9A03659DA774B429ULL, 0x9A2CB74B461410E9ULL, 
            0xB299DD6ECA9A4111ULL, 0xD3F431C30003162AULL, 0xF81E32672C9F8B3CULL, 0x0865C64413F64009ULL, 
            0xD4E15B5C1FFF3876ULL, 0x9427EC6BDCA457E4ULL, 0x6D94FAE2D359AD2CULL, 0x1DDE3790EC7376DFULL, 
            0xE0ECC0049693F6B0ULL, 0x92D3BC80CAF4212DULL, 0x1DBF2F9288013EA0ULL, 0x1757D85B93E4EDEAULL, 
            0x47A4975017F5AC71ULL, 0x41BD82D3503A69E9ULL, 0x33AEC91D1335A92CULL, 0x9366129176FA6F30ULL, 
            0xDF689540F9FF29E9ULL, 0x52E318D79293B566ULL, 0xBB8C01AADE2ED1DBULL, 0x1C641975D3B9D5AEULL, 
            0xD4D9956338DEE382ULL, 0x3EDB67E064ED107CULL, 0xAE36FBC02796CEDDULL, 0xE85A9CF8288085D5ULL
        },
        {
            0x3DAA16B4324264D1ULL, 0xFB49D0277E2D9185ULL, 0x1E2D70AB01A9D8A8ULL, 0xA54D7D9E82AC4EDFULL, 
            0x23847519D7D36433ULL, 0x18C5E184DF511A25ULL, 0xA4B8735A18A21CF8ULL, 0xB0772F5BCAF2532BULL, 
            0x9D00E70627CA62D9ULL, 0x28FF5B9FD9F73F1AULL, 0xE6004D3A836796DDULL, 0xD436AE421ACFDE1DULL, 
            0x9A4B237279622B4DULL, 0x31FE3F03B3B8AC72ULL, 0x0C0CA895D6C24610ULL, 0xF19F5DC37E37181FULL, 
            0x5BD283D4F6449046ULL, 0x33FE917A45A111C5ULL, 0xC43ADA8315BF1BA7ULL, 0xD1EFD3245E6017E3ULL, 
            0x743462336503860BULL, 0xECD4D43559D5F861ULL, 0xBA3E5B9D4F7F7FCAULL, 0x48264A54BE4B9DD8ULL, 
            0x2A23B755380DFF5AULL, 0x0FB4D7548A35FB14ULL, 0x5236823226C42E2DULL, 0x8C79A560B2FBBDC7ULL, 
            0x8CCFA6CC19CA36EBULL, 0xB0D6654931CE472BULL, 0x7D0D233FCAEED742ULL, 0xA4F9FEFF287EAB79ULL
        }
    },
    {
        {
            0x284CFFAC31DBEEDDULL, 0x1F929E19A800BA05ULL, 0x91804578853D8991ULL, 0x13D92B1F0ECE91D8ULL, 
            0x6BFCF35437A87905ULL, 0x73B77AEA026BA725ULL, 0x32AE7304A68FE05AULL, 0x14CA85A5D0A94B3FULL, 
            0x5A7210490BA642CBULL, 0x5B9BE4963D61517FULL, 0xE87E252BF243E5C5ULL, 0xC554BBD2FB315F19ULL, 
            0x6959F90A7C2469F7ULL, 0x097916A4E3053708ULL, 0x58EF9FBEF6DF383CULL, 0x2B97E607FA691723ULL, 
            0x9F91E4772BC94F90ULL, 0x7E8E9DF6B3F4BC6EULL, 0xA6D95DE680E06F74ULL, 0x55441F5C6DDDA387ULL, 
            0x202BF8B82F38CE4DULL, 0x40346168BADB4E40ULL, 0xB492AC44F1D1972EULL, 0xDDECA209BD3DC3C4ULL, 
            0x6C1EDAA60B7807D5ULL, 0xC1E126B10AB7E0E0ULL, 0xF2BC71EC16E4C203ULL, 0x7F836AB3625D146FULL, 
            0x418D4969693BEE0AULL, 0x0AD00ECA1D229BC7ULL, 0xA2AD4277A12E5652ULL, 0xC86F87F1A5A7F543ULL
        },
        {
            0xC6E2A773FE5A712AULL, 0x28AFC697145D98D7ULL, 0x31C36C60F77BA01BULL, 0xADA7ED6329B11DF4ULL, 
            0x00A36EEA4E82A0C3ULL, 0x732BC22B6D07820CULL, 0xC07DE5ED310C7943ULL, 0x92189E1CA21BC970ULL, 
            0x6BD7A40D56781901ULL, 0x3078EAE6A90EA743ULL, 0x6AB48B012F927ECAULL, 0x30A1A7503866DA6AULL, 
            0xC4B8CFDB8A61700BULL, 0x13BE23BDC013954AULL, 0xAE6F15F055362A28ULL, 0x1B08A7967EC29B70ULL, 
            0xBF7C1D0A7CBD1AB5ULL, 0x93D2884FE0C22997ULL, 0x9B6051A094B6D81AULL, 0xE990DE64B909B119ULL, 
            0xE784C7ABD1EA71B0ULL, 0xCBB7034C4B7C15C3ULL, 0xC1D8E1CCD8176B9AULL, 0x304BE65FCE2B131EULL, 
            0x9BCD1D9BC9EA3621ULL, 0xF1261DE064838457ULL, 0x2A7082A50400AD91ULL, 0x4C16029914E6804CULL, 
            0x2078614963E3C8D1ULL, 0x9CB96F1EAE7EDC5BULL, 0x8F1E4BD35385BCE0ULL, 0xE8754C6476FC853EULL
        },
        {
            0x68320FDD40458ADEULL, 0xC2D17281282041F9ULL, 0xF885749131D17C15ULL, 0x17012423A3B3D4F8ULL, 
            0xF4BB7F8116377CEAULL, 0xB896A1AAECA5DF90ULL, 0x2A78878B348C711DULL, 0x3ABE68693F50335AULL, 
            0xB5EA43542DDFE62BULL, 0xEEBAB42464D01BCCULL, 0xE7134BA22A4CBA60ULL, 0x067137A8A9216193ULL, 
            0x24629F9A4805BF5FULL, 0xE5595613D1430FF2ULL, 0x7AF0F0FFC536F8A1ULL, 0xD9D0E602E0F69BC5ULL, 
            0x4CAA93A3BC48BC3DULL, 0x461D0F8755E22FC6ULL, 0x3EC5FE2DA4236C7CULL, 0x17355B88FC9B3936ULL, 
            0xCC7C76F1A17853DCULL, 0x0EB710B2FA06364BULL, 0xCB22D58FF8CBE46FULL, 0x7B002BDEFF59D46DULL, 
            0x8A3F0C7DCBD34103ULL, 0x95AB70956E26438FULL, 0x5E5C00FAE3C17C6EULL, 0x4F0D1BEA8AADCDBDULL, 
            0x3117561FE32EB485ULL, 0xA9AD00654347CB75ULL, 0x7296E07403891BA1ULL, 0x07A804A155ADBB59ULL
        },
        {
            0xD9D484F8C74E0142ULL, 0x326583D04507BFBEULL, 0xAD046EE6CE0061ADULL, 0x61F5056C54C8E5DFULL, 
            0x7F7A709F593A3971ULL, 0xC80978275783C3C3ULL, 0xEB6AEEC3DA190825ULL, 0xB1D2134113465752ULL, 
            0xB09F7FD40E036E58ULL, 0x7EE8E4B9D2AB14CEULL, 0x0AB0B769797E6E47ULL, 0xE7078B5E8E08C0D8ULL, 
            0x2EBAE789F720356FULL, 0x2C3A43DF3FAD2754ULL, 0xD7BB99B73E3E66FDULL, 0x9EB1A5353EF7F1D2ULL, 
            0x727F41B030428D36ULL, 0x11D0ED4AD55F8015ULL, 0x81A6B955789B6499ULL, 0x07388B45C9D4860EULL, 
            0x9DD1233C071B45C0ULL, 0x103CD07242B3C08BULL, 0x8FBE4AB2752F3F3BULL, 0x1A95E55DC8761587ULL, 
            0xEB8498B7D6436F6CULL, 0x15DC61E01AD60B7FULL, 0x93B94A803ED0D244ULL, 0x5C7BEE9B54078362ULL, 
            0x876FB1B42CAF3376ULL, 0x4E576B006AF0129DULL, 0x56E9A03E121C8ABDULL, 0xB49F0E112F5DB9D0ULL
        },
        {
            0x43A63063B379B854ULL, 0xC39AB8927EF02443ULL, 0xC743A97C830CB7DAULL, 0xE248A724F3D19360ULL, 
            0x2FC023769FAB2D1DULL, 0x19F50A1BD2EB223FULL, 0x696EBD0F37E730CCULL, 0x8367A2ED29598EC9ULL, 
            0x1E9EA0ABE43328EBULL, 0x1CD4C9E27EA633A5ULL, 0x4FC2091936221130ULL, 0x1089E00D357F6AD3ULL, 
            0xE70C40911517CC5CULL, 0x69C259422F58A0C5ULL, 0x6392B724757D0C35ULL, 0x0F773D2F082A94A8ULL, 
            0x5EEC6BBB3DE33161ULL, 0xA4A15647CE1AB6FEULL, 0x4B5F88343A3728A5ULL, 0xBB6ADAB1632A4FC0ULL, 
            0x7AD4457349C32C8CULL, 0x50C802098E546177ULL, 0x40E1BBAFE40DD663ULL, 0x04675ADE59F24EA8ULL, 
            0x343D4D994879F3B7ULL, 0x52672DF8B3600A1BULL, 0x809576572975DAA9ULL, 0x78626E8DEB83595DULL, 
            0x49E1A414FD5C176BULL, 0x8470575321508185ULL, 0xD9F800CACC440560ULL, 0x4AF18A0D17A2CF09ULL
        },
        {
            0x1753DCEC43A62504ULL, 0xAAD9E82A2747A0EBULL, 0x8F7E51F0C98AF1F9ULL, 0x2FA1581CF38B9A77ULL, 
            0x4446F9363CAA0905ULL, 0xF478F1E878C325C6ULL, 0xB44C0E1D21AF22A2ULL, 0x15B9E41AB7C51E05ULL, 
            0xB523BB79E4D60551ULL, 0x4735B8D16452C06DULL, 0xA569EB55BE701CB6ULL, 0x5E4B94B6DF3AFF1CULL, 
            0xDD6C5FAD3CD01DAFULL, 0x26CD3F9E6196DB5AULL, 0x1809B488B19D6EE4ULL, 0x3984EA91CC4A34BFULL, 
            0x935A1CE1C86C5EE4ULL, 0x635F4BD5215E6AC2ULL, 0x2DD787945C760C14ULL, 0x87CD2509456914D4ULL, 
            0x430363F7CB9D3EF6ULL, 0x9292187DC0934E4EULL, 0xF361FF3549A756DFULL, 0xC2AF87CF6138F99BULL, 
            0xF60D9BF3BDC579B0ULL, 0x8A3477FB4075ACBEULL, 0x655ACA921627A542ULL, 0x6DCB08F74A8C7FE8ULL, 
            0xC638D8D4CCFE239EULL, 0x86D765AF6D8499DCULL, 0xFDA3BC68025475ACULL, 0x8ABE6B9A34734502ULL
        }
    },
    {
        {
            0x5BA2BB3ADAFB3948ULL, 0x826F251C1F292450ULL, 0x9869CE65B05666C8ULL, 0x9827A94D50A7A90DULL, 
            0x88D063A4DB347C53ULL, 0x439FE117CEE19EB5ULL, 0xE59C3FEA340A0DC2ULL, 0xC9EF5553C4E79025ULL, 
            0x4F6E2C86BF1E9C64ULL, 0x3B90D197F71A2ED0ULL, 0x10A24BE5BEF08D69ULL, 0x504E7DDD963DF672ULL, 
            0xF4F55225AA3C5858ULL, 0xA677FCA48F365FE8ULL, 0x5FC40ED973FC4CF8ULL, 0x6B80BDA9EFD44ACAULL, 
            0xCC3BF35B67627FF1ULL, 0x65BB3C2AF08BFD65ULL, 0x6816063B14DBEBCBULL, 0xB6F5D3CC06B0B805ULL, 
            0x0D0AB2C3078A5BBCULL, 0xA7681DB1265918EDULL, 0xEAD3D272F85A35C6ULL, 0x3A422A63952B44AEULL, 
            0x3A3C5B48452F696DULL, 0xECF35DC631507437ULL, 0x9C9BA43372297FA9ULL, 0x39C6E65E9FC46950ULL, 
            0x4FA6DC650FCF38A7ULL, 0x21B7E4E29390AF70ULL, 0x81B8081C36F2F0B6ULL, 0xC034AFAB9C653AD3ULL
        },
        {
            0x7278CDBD8EE077C0ULL, 0x44F4F828F721E282ULL, 0x35B76939992A3B11ULL, 0x187DE653B882E284ULL, 
            0xAD8CA36391F342C7ULL, 0xE222B64F70EEF0BBULL, 0xC1B8A4D3CE2ABD66ULL, 0x07BE2B86F00835EFULL, 
            0x341D9DD569C084FBULL, 0xF923CA286DD3B447ULL, 0x1B9B60A782A7257BULL, 0xEEDF7DCF3EEFC26EULL, 
            0xA64DCF0D4CB0FF57ULL, 0x4DEF14B6988F59A2ULL, 0x08FAE94F72DAC233ULL, 0x66EEFAFEB5F54E15ULL, 
            0x6A57AFB851F19CA1ULL, 0xE000847E6C24D164ULL, 0xEBDA0AC8BFDFBAAFULL, 0xD9A22DC01FDC8456ULL, 
            0xAC86F4B3BC129A64ULL, 0x4061652D9F596FE1ULL, 0x13A51BC81EAAD13AULL, 0xC32010F4F85D7E58ULL, 
            0x257C8E38BA75950CULL, 0xB6F162F880E41866ULL, 0x4B246518FEF10077ULL, 0xD70DABCB8D212939ULL, 
            0xD283EE269605213FULL, 0x812DFFB59CDA3293ULL, 0xF8D5E4DCE406F2DEULL, 0x341A9CE68F638ED9ULL
        },
        {
            0xC8B769D35D7DF1B9ULL, 0x0993B4C10E448247ULL, 0x8F25F13537F71C6CULL, 0x1EEF41D35E06B0F7ULL, 
            0x77A010AA38487FE6ULL, 0x61E7BDBDE0458D11ULL, 0x6FE542EDDFCD859EULL, 0x931DB784BDA54E47ULL, 
            0x9144F4E37969FBBFULL, 0xC1871529888A0EB4ULL, 0xCFB4DA139AA1E90CULL, 0x465F9B743ECAFBDCULL, 
            0x17CEDB794321DD58ULL, 0xFE83A409B14B0312ULL, 0x2368B3E94F8109A7ULL, 0x969F29B279DE84F7ULL, 
            0xDE52FC207EA84C86ULL, 0x08D8E23EEDF77216ULL, 0xDC96D64F2C09DC05ULL, 0x3DDB9D7AC6231BCCULL, 
            0xB7F5C168BA6AC9C5ULL, 0xB71A1362C058F14FULL, 0x8D584A9EFF6148DBULL, 0x36CE80F4CC5506BAULL, 
            0x65DDC561811922A5ULL, 0x3AC1B5C544397FC6ULL, 0xFB83B6B44167C891ULL, 0x0BC2D7F4283DC216ULL, 
            0x563CB547A017114DULL, 0x9A4F57686949430FULL, 0x756D6B9FD03FB1C6ULL, 0xEF00755B6068650AULL
        },
        {
            0x84372785B7B9A71AULL, 0x79CC35D3C444E7BEULL, 0xA964926A5F019F44ULL, 0x81C4876983C3E950ULL, 
            0x210C49F8DE4E6FF9ULL, 0xF4C2954507772961ULL, 0x383FFFFF4EE553D9ULL, 0x5C2B1D1C4E1D1C33ULL, 
            0x92BFBD49BD533806ULL, 0x7CB232A271E4148AULL, 0xD4391D413CA3B209ULL, 0xBDE49CBB0F50CDCDULL, 
            0x07860A45E0C22EF0ULL, 0x7FAF0A4B15BBE144ULL, 0x90C5E6091E718830ULL, 0x8376CADB7E6BA42AULL, 
            0x330C76DFD7780173ULL, 0x4FB7A3F0BFE3E31BULL, 0x64FA01E7DE058DC0ULL, 0xFEA8EA80D0DB5708ULL, 
            0x0DF79EAA3CAD513CULL, 0x2528319560CE3284ULL, 0x26C6A372F55A8A0CULL, 0x8978F547BC712E4FULL, 
            0x25EBBA77A575634BULL, 0xD3D9FA4F61252649ULL, 0x3D296033E626E872ULL, 0xA699BCE21542000AULL, 
            0xA09F2E0F2A06D263ULL, 0xEDCB8B941F48115DULL, 0x5381090419AA6387ULL, 0x821C0A33073FCC67ULL
        },
        {
            0xD6D17816CD15BC13ULL, 0x2B245A28B8E41BFFULL, 0xEEB4F6C4531DEA12ULL, 0x45C0531A681FE1AFULL, 
            0x30D11BCECAEAA301ULL, 0x77F67D68F1752AECULL, 0xC2A1EA94FAB10C57ULL, 0xD2DECCD46AAE1878ULL, 
            0x7B5DF086D0F9D6ACULL, 0xCA36C9DE5E91835CULL, 0x62D1179B7CB103E5ULL, 0x4D4962DFF9712FC8ULL, 
            0x98F70B7ECF79C107ULL, 0xD96D74A85C87B777ULL, 0xC5A13BB7287D8D83ULL, 0x9C7D68EB6845E599ULL, 
            0xF52D13E955CD4226ULL, 0xA492FF760EF5CB14ULL, 0x17C788FD0496803CULL, 0xB7BE67D5C14AC414ULL, 
            0xDC468551D18CF1D4ULL, 0xE3FCB9E684C4CEA1ULL, 0xFD50842A68689F6FULL, 0x03B168ABF1E450A7ULL, 
            0x3FD2F43BD2D143B3ULL, 0xC09F05F0FA4B191CULL, 0x3AB5C4EA8D205AC1ULL, 0x1A30A10766A6C97CULL, 
            0x5B00113DF88A0661ULL, 0xF2DD32BF859FFA13ULL, 0xC1B74652C7C9B8CEULL, 0x34720244AEFB3F90ULL
        },
        {
            0x255AE79117E73AAFULL, 0x1E596A053EDD3866ULL, 0x041F89C8D40264CDULL, 0xB23837936B5814D0ULL, 
            0xC5A50082EDB3273AULL, 0xBE7AF1EAC2281BF1ULL, 0x06EB524865533BCEULL, 0x218E0DCAF3458218ULL, 
            0x9D4CFF25D8DD68CFULL, 0x5D06B3DD6DE17B1DULL, 0x358DE19EB2661BEBULL, 0x468059E9B18CF5CDULL, 
            0x0F8E4BDA984FA724ULL, 0xF177DE64CEDB0CEAULL, 0x9082FAF82C247C43ULL, 0x8A9061EEECE5D830ULL, 
            0x5F910DCFAB123ECBULL, 0x5E3959D9F68BE8CBULL, 0xB7BDA72B6A72A4D1ULL, 0xD45A99D829C70198ULL, 
            0xFE601001A5852DA8ULL, 0x6A3CEAE4C8171A24ULL, 0xE7532370DC13A3BBULL, 0xC64711A4E7D4C17DULL, 
            0xCCDE0C2495F5C51DULL, 0x9B354214A7A22DE4ULL, 0x04310818DAFE3D49ULL, 0x6948B03685753318ULL, 
            0x0BC0DCE2845EBC35ULL, 0x0759D2E32F4DC2B8ULL, 0x08561E5311084784ULL, 0x43A03CD1F384726BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alkaid::kPhaseHConstants = {
    0xC90C06E28DED7CE8ULL,
    0xF0EDEDED5CBD7A6AULL,
    0x060AC62C21CBDA10ULL,
    0xC90C06E28DED7CE8ULL,
    0xF0EDEDED5CBD7A6AULL,
    0x060AC62C21CBDA10ULL,
    0x61C67954650D16ACULL,
    0x835B83297545192DULL,
    0x8F,
    0x59,
    0x73,
    0x93,
    0xF0,
    0x0D,
    0x60,
    0x18
};

