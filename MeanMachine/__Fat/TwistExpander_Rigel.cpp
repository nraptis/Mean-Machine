#include "TwistExpander_Rigel.hpp"
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

TwistExpander_Rigel::TwistExpander_Rigel()
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

void TwistExpander_Rigel::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x879CCCF75BE2C740ULL; std::uint64_t aIngress = 0xE92F87E23DAA6C09ULL; std::uint64_t aCarry = 0xEBA21623AB589DABULL;

    std::uint64_t aWandererA = 0x84C25F0DEB80A9DCULL; std::uint64_t aWandererB = 0xE7ECA5BD4388F88DULL; std::uint64_t aWandererC = 0xF74AE26E87951747ULL; std::uint64_t aWandererD = 0xBC91F0D7557FB1ACULL;
    std::uint64_t aWandererE = 0x8C2E4F74614D6D8AULL; std::uint64_t aWandererF = 0x9D3D809656D90CD3ULL; std::uint64_t aWandererG = 0xA54D002866A85D7DULL; std::uint64_t aWandererH = 0x9238176AC9572468ULL;
    std::uint64_t aWandererI = 0xFCF340B15E204C8AULL; std::uint64_t aWandererJ = 0xEBB4CA043E03F0B0ULL; std::uint64_t aWandererK = 0xA664048D2D65677FULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16406804006213462580U;
        aCarry = 13157279244989525749U;
        aWandererA = 17759634593796555199U;
        aWandererB = 17125349748804305991U;
        aWandererC = 14412453209620590659U;
        aWandererD = 17960349630194732245U;
        aWandererE = 14491488091547835449U;
        aWandererF = 13202960698930138467U;
        aWandererG = 11170172170283282293U;
        aWandererH = 12386513007964027706U;
        aWandererI = 14700878028631798408U;
        aWandererJ = 13006184456693383486U;
        aWandererK = 16139101755184637608U;
    TwistExpander_Rigel_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Rigel::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xDDBD243F8F73D9A0ULL; std::uint64_t aIngress = 0xF3C14A926CFE4489ULL; std::uint64_t aCarry = 0xB62565E41B3C7FEAULL;

    std::uint64_t aWandererA = 0x9A11685104BE5063ULL; std::uint64_t aWandererB = 0xFCD5FC2027E7FCFBULL; std::uint64_t aWandererC = 0xFE69B1EC0979770DULL; std::uint64_t aWandererD = 0xAF6170DD142B9B13ULL;
    std::uint64_t aWandererE = 0x90022E5BEA0371DEULL; std::uint64_t aWandererF = 0xE19377F1523FB3EDULL; std::uint64_t aWandererG = 0x8B3EA0D7FF622FB5ULL; std::uint64_t aWandererH = 0xF26061F9B0BD3688ULL;
    std::uint64_t aWandererI = 0x99807B9B351F6494ULL; std::uint64_t aWandererJ = 0x9CCB776ABDCEC4E2ULL; std::uint64_t aWandererK = 0xE79262405F9D56A7ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13114471893143795635U;
        aCarry = 9780127008019498675U;
        aWandererA = 16968877903255785534U;
        aWandererB = 10870429556395938236U;
        aWandererC = 11517047997695973256U;
        aWandererD = 10657655006624486270U;
        aWandererE = 12541415488942429080U;
        aWandererF = 13855096363284825322U;
        aWandererG = 11679820346436086094U;
        aWandererH = 10405490427271820246U;
        aWandererI = 12633316978110764729U;
        aWandererJ = 17987519371665839591U;
        aWandererK = 13593064273567347520U;
    TwistExpander_Rigel_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Rigel::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xDE2A228E4AC54750ULL;
    std::uint64_t aIngress = 0xCC5864702E0EE73DULL;
    std::uint64_t aCarry = 0x8ED8D10D7F91E2C1ULL;

    std::uint64_t aWandererA = 0x96BE27826E51591DULL;
    std::uint64_t aWandererB = 0xD0ED928A4AF7A46BULL;
    std::uint64_t aWandererC = 0xE7128F974B77D15EULL;
    std::uint64_t aWandererD = 0xCCF2CE91371C957EULL;
    std::uint64_t aWandererE = 0xBB3DBB37E20AD272ULL;
    std::uint64_t aWandererF = 0x88A72B7D75D5FDE4ULL;
    std::uint64_t aWandererG = 0xBDF332E71F64E43AULL;
    std::uint64_t aWandererH = 0x9AFF4A1D59DA4025ULL;
    std::uint64_t aWandererI = 0xA329F1E734027958ULL;
    std::uint64_t aWandererJ = 0xCC15BB2CD1C0A4E8ULL;
    std::uint64_t aWandererK = 0x9AA37F9BE63408B5ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
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
    TwistExpander_Rigel_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Rigel_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Rigel_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 29 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1791 / 1984 (90.27%)
// Total distance from earlier candidates: 50974
void TwistExpander_Rigel::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1374U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1478U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 226U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 547U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1839U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1534U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1824U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 63U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 118U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 806U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 672U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 216U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 316U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1015U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 812U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1472U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 960U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 13U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 790U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 994U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 47U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 272U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 39U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1659U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1548U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1592U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 497U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 953U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 534U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 595U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 434U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1587U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1139U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 477U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1767U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 37U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 940U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1006U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 221U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1984U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1253U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1035U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1378U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1315U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 315U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 499U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1336U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 546U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 690U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1732U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1719U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 770U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 200U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 203U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 255U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 492U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 0U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 217U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1300U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1213U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1981U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 199U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 456U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 376U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1215U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1693U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 310U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1241U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 565U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1384U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1658U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1939U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 977U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1740U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1055U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 379U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 414U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 30U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 906U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1861U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1688U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1373U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1186U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1053U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1751U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 679U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1500U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 463U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1607U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1264U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 894U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1596U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 642U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1736U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1298U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1034U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 144U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 508U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 907U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1342U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 284U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 389U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1048U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1608U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 275U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2026U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 580U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1741U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1820U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 75U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 113U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 638U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 397U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1613U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1089U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1114U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1638U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 542U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 911U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 789U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1411U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1851U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1346U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 331U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1070U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1102U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 119U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 693U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Rigel::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xB1EB40F9D551BE92ULL; std::uint64_t aIngress = 0xF64823FE5A8C42ABULL; std::uint64_t aCarry = 0xB748A266088DE354ULL;

    std::uint64_t aWandererA = 0x8270C0BB0EBAC706ULL; std::uint64_t aWandererB = 0xE95A1738387F5D80ULL; std::uint64_t aWandererC = 0xACFECD9AFD37D88AULL; std::uint64_t aWandererD = 0xB10A7F4E4FD199C0ULL;
    std::uint64_t aWandererE = 0xD31286A31B2B75E0ULL; std::uint64_t aWandererF = 0x8959BE5157945ED0ULL; std::uint64_t aWandererG = 0xCB3EEEB0FBB3E709ULL; std::uint64_t aWandererH = 0x970159EBB98920CAULL;
    std::uint64_t aWandererI = 0xBED095E7D7B5BD2FULL; std::uint64_t aWandererJ = 0xD49CDB57960328B6ULL; std::uint64_t aWandererK = 0xBD33DE842887A774ULL;

    // [seed]
        aPrevious = 12681588499945586047U;
        aCarry = 15331583789151247240U;
        aWandererA = 17625458390476911915U;
        aWandererB = 11293130566597624500U;
        aWandererC = 18222541265990417835U;
        aWandererD = 15493966005275817462U;
        aWandererE = 13210429262558212306U;
        aWandererF = 12205266901243362988U;
        aWandererG = 15840040362487635813U;
        aWandererH = 13958559576893134067U;
        aWandererI = 14345831405930372431U;
        aWandererJ = 9396044743762056457U;
        aWandererK = 16258011016974744779U;
    TwistExpander_Rigel_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Rigel_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Rigel_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 29 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15130; nearest pair: 477 / 674
void TwistExpander_Rigel::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2650U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6540U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1734U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4001U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 395U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1371U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3948U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6680U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4991U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4497U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4920U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6290U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2462U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2574U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 500U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8063U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 216U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 211U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1915U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 407U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1202U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1054U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 473U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 325U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1051U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 829U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1667U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1416U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 497U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1489U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1767U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 657U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1796U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 980U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 327U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1800U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 29 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15145; nearest pair: 485 / 674
void TwistExpander_Rigel::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1189U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2044U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3010U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5688U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5765U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6132U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6103U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7446U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 577U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7253U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6616U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4135U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7598U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5239U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 891U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3861U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1677U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 362U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 327U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1682U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1322U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2001U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1171U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 932U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1162U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1204U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2029U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 717U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1696U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 148U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 40U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 580U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1891U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 201U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1286U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1606U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseASalts = {
    {
        {
            0xE5566006E565B7A8ULL, 0xD3DDEE1C7B9E9F4EULL, 0x858D2FFDA306C333ULL, 0x004725474E13E25CULL, 
            0xB38FCF7465BE8DA9ULL, 0x9B0F8B865D945306ULL, 0x16A527D1802E22DCULL, 0xFF5BA7313AC555D7ULL, 
            0x21A10599C011DE44ULL, 0xFCABD14B466A4F12ULL, 0xC26BEE4B6AB2A6A3ULL, 0xC89DCED224902577ULL, 
            0x19894F8BC2DBF644ULL, 0xA845BD640B5F6633ULL, 0xF2247704114EA1A6ULL, 0x31570DCD9AABEA27ULL, 
            0xDB39085267135C72ULL, 0xFDB16F3EEEEC797AULL, 0x4F655608E4FEF8B2ULL, 0x1849BB8F7F4D6205ULL, 
            0x13C640E378A95145ULL, 0x342586348F954E6FULL, 0xE158F8990DEB8B23ULL, 0x6B48855E81B7B679ULL, 
            0x5D823D16DFCB5979ULL, 0xA73C32DF495F7A2DULL, 0xE4973B0C9C2B8088ULL, 0xD97B76C4BF230FACULL, 
            0xD8661004D0B479D6ULL, 0x8C56020ABDDF88DEULL, 0xA309DD0478D9FB1DULL, 0x9DD86298AF1ECE8FULL
        },
        {
            0xF2F770F93522A924ULL, 0x74FEC17A8D897C27ULL, 0x363387C579E2CAC7ULL, 0x252C0A76E4107234ULL, 
            0x51093B60A7981838ULL, 0xC11135098C2CAAFFULL, 0x0968ACEB1F767DE2ULL, 0x9751CCA5E139E5E1ULL, 
            0x9EA77E2D5B532AE0ULL, 0xADAD7ED22ACC0514ULL, 0xDECBCFB5D2DC60A6ULL, 0x2CAA07478DCBC668ULL, 
            0xBF75158745F08614ULL, 0x0C5205F6FC0DBD6FULL, 0x1A60319B186F10B2ULL, 0x9E9C3BEDB2519C8DULL, 
            0xBE9397F47A2D50CFULL, 0x87F22DFFD3C2B270ULL, 0xD15FA8509B9C45C7ULL, 0x7E1D410DD5A9B5F2ULL, 
            0xC7DC78BEA1440CD9ULL, 0x1ABBBBADC2DD484DULL, 0xB72A13061835BEBEULL, 0xCA18B4D0C219C641ULL, 
            0xCCA5F8E9F8FDF40FULL, 0x43D8C25AF36BE359ULL, 0xFEA4F0EE77438204ULL, 0xC635FC11FFC87F9CULL, 
            0x190B43C5CF907FDEULL, 0x26A13A82DA755E50ULL, 0xB2646323EC0D7504ULL, 0xF82D7E088BCBACA4ULL
        },
        {
            0x02EDC95FF7B1DCC1ULL, 0xFEB8EC1C76FCA947ULL, 0x466A938175399FC2ULL, 0xC6B603F95166E554ULL, 
            0x377EEFA7D980DBB4ULL, 0xDFACA615A422675BULL, 0x61423EFDCD15D1B0ULL, 0x0D77396D38444079ULL, 
            0x576AD5CDF5EE5203ULL, 0x6D690BE79FCFBD36ULL, 0x6E2B85AE103BC382ULL, 0x419F2FE12559FB92ULL, 
            0x7CD816963996AD19ULL, 0x553A686367672FBBULL, 0x6499975D2936115EULL, 0x899972B2FC523275ULL, 
            0xD1CD6C65EBC0C814ULL, 0xCAAFE86F839D03FAULL, 0x6763CCA934B63413ULL, 0x56E86658148C9542ULL, 
            0x2C323D134BFC1CCDULL, 0xF5023134D6CBF135ULL, 0x66BA2FD405B28ED6ULL, 0xF6540284AEDF1B01ULL, 
            0x972CADDAE352A906ULL, 0xD8B9928AF5FCAAFAULL, 0x7037ECF681495BA5ULL, 0x5A8D57EDBAD1167AULL, 
            0xCC59DF199DBE86F3ULL, 0x5C46E595F4F21FD3ULL, 0x11E796B166781601ULL, 0x67A5822BB09C679DULL
        },
        {
            0xA794B7BD7C94B12CULL, 0x82D4E9A85383E554ULL, 0xBAA58B84E37315B7ULL, 0x019BCA1965E9FDB6ULL, 
            0x328E41BBCDDD3743ULL, 0x5ADCD39B1626888CULL, 0x950AE3909489709EULL, 0x50D8DA69B494D90AULL, 
            0xE653A5D1DBFE84E5ULL, 0xCDB702C1BEE1A123ULL, 0x30CC593EEDB08CC1ULL, 0x8996936F74BF50AEULL, 
            0x25C07251996A1283ULL, 0xA5607D97BC148C9DULL, 0x7637D344B64C7023ULL, 0xFF73B46AB03674B6ULL, 
            0x37A30883C632E906ULL, 0x97A6C1AF97B78737ULL, 0xF382839445FEF814ULL, 0xF8B8CDC3E8B9FDF0ULL, 
            0x7C2602086D25249AULL, 0x7BBF7D44F97D0577ULL, 0x242255EBD2E98A8EULL, 0xC9D1D1728882FC0FULL, 
            0x7F1C38860DADF3A8ULL, 0x655E92457B574E4EULL, 0x14716CF398C28877ULL, 0x5B0D5749DEE29686ULL, 
            0xBD4EC3E054E1E66FULL, 0xE3079F6A7573326CULL, 0x2FB407587245B477ULL, 0xE2AACE1074616127ULL
        },
        {
            0x46F76533C6DDA69FULL, 0x7B3F8A153231CD93ULL, 0x0D1C4A05A5B068FDULL, 0x959EBB19CD4D873AULL, 
            0x90F666108483F3D7ULL, 0x4EA7420C773922FDULL, 0x0B1CD69B626BFB6CULL, 0x6A4EB30C2EB36F7BULL, 
            0x836935E2EDF7B7F9ULL, 0x41B8CDE40473882EULL, 0xC71CEA63099AF4FAULL, 0x2A3AC192E2E0D135ULL, 
            0x124176CEAA2815BCULL, 0x0687EC18882351A0ULL, 0x91534426EF34839AULL, 0xF8D1BC185AF3F6AAULL, 
            0x23B64DB7788BBB8FULL, 0x92B9C8A770EDA5EFULL, 0x19B8AA5A562FC4EDULL, 0x40BF553C85FD6357ULL, 
            0x472B397D91741DD7ULL, 0x2DBA90F2C2D06B8EULL, 0x2EC297F982C76583ULL, 0xC70061DFFF729891ULL, 
            0xD4B620DB82EEDAFDULL, 0xB35AFE21E0101102ULL, 0x8945BB0AD7D5C244ULL, 0x05CC56E7B6724442ULL, 
            0xD3BD7980837112C5ULL, 0x60EFD3A4AA0BE2A6ULL, 0x1BBFE7F2967B07AFULL, 0xF9B9333EF8353AB7ULL
        },
        {
            0x60B74E61F1C7FA50ULL, 0xF394E34E87F3AC56ULL, 0x3BC0F60623BEA7D2ULL, 0xBCDD1BA1A99A7DD8ULL, 
            0x3ABB1E380ABEE80EULL, 0xE5E91780D97DC2A2ULL, 0x9B9206A823823141ULL, 0x04F382F637C8789FULL, 
            0xD2799BCA04266431ULL, 0x1404D35CAC7CF5A6ULL, 0x0DFAD73DCD8C8C61ULL, 0x2F7037797F511E28ULL, 
            0x7F0699AD32BD33F0ULL, 0x9BF0D61358346DA7ULL, 0xC498504441D34C45ULL, 0x96E3DC9F194BE523ULL, 
            0x5B5C77B685AC0454ULL, 0x8DE89A281569F59FULL, 0x6EA9F49E33AAB21CULL, 0x2C54F3FB163B68D3ULL, 
            0x36D06FE911DE6515ULL, 0x011124502F880D2FULL, 0xD806E75EA67A0A4DULL, 0x7945A4F4DDAAAA3AULL, 
            0x0FABAF024714DB2FULL, 0xCE40B9598947FE39ULL, 0xBE4964A31B3F4D92ULL, 0x7FE4FD4711A15BAEULL, 
            0x5D20D629E1907CBFULL, 0x1638C305F705BC8DULL, 0x2570F5F4FF193A12ULL, 0xAA559E7C8A407C85ULL
        }
    },
    {
        {
            0x1B829C48453DE60CULL, 0x49618C9F2B1FD7CBULL, 0xC6C80F8341466CBAULL, 0x76452E6DE335CF65ULL, 
            0x7B13167E0A526A14ULL, 0x5E1DFD1E656090F8ULL, 0x2167743E39B61FFDULL, 0xA0FBBCCEF8E26458ULL, 
            0xC3CCF4B67CF30FB1ULL, 0xA195180E59BDF2F5ULL, 0xC86F9B3CF9967EECULL, 0x8DAA4039867EA67EULL, 
            0x7973BE111EC145E9ULL, 0x976B3F76C4CCED45ULL, 0x79D8A147BBA5042BULL, 0x3AC5252F3C1EBD03ULL, 
            0x32D9AE7D48E3AA9FULL, 0x2D9EA2C7E54AECD5ULL, 0x0B545D5B403CE1E4ULL, 0x9E3610DA30704108ULL, 
            0x72EE1F6D84DA21B8ULL, 0x215858A7EC9D385BULL, 0xDD7BA18D782D57ACULL, 0x786BC88D8AA7A4E9ULL, 
            0xAD8CF7625A1C294FULL, 0x28AD60F00A532E44ULL, 0x2727BC9C8B3A38E8ULL, 0xE805E01434DBE14EULL, 
            0xAF8E3C83152BC154ULL, 0x9366510C38A2FAD2ULL, 0x5BE6BC87FDB797BAULL, 0x325A1FA922A6FFCDULL
        },
        {
            0x5323DD040D565C6EULL, 0x1A2DC15B1FE4B829ULL, 0x6A23E98288E2D487ULL, 0x038D567E57D56620ULL, 
            0xA7C9B9702466A8A0ULL, 0x7C3E79A97F26CE3CULL, 0xFB6055392B47E74AULL, 0xF272DC8A17877DF1ULL, 
            0xA8D6768830EEB252ULL, 0x88EAD5CC251B5B2EULL, 0x4FF10709D1180E6CULL, 0x94B3B8F5E48E601DULL, 
            0x620B36F7E0E3CB71ULL, 0x93535BCDB4A0EB37ULL, 0xB4B23BDDD2F0FDFEULL, 0x1A966229BB6BD0A0ULL, 
            0xC9D15A2ED54FA469ULL, 0xFFC323F7A2F78962ULL, 0x022F0BDD5B5E01FBULL, 0x3B2144669F818279ULL, 
            0x757BA7AB5BF165A9ULL, 0x7297F0A0FE1CCAA3ULL, 0xEAF79F20B77A2A9EULL, 0x97C2CAE545083689ULL, 
            0xF479F1F9667BBBA6ULL, 0x4F949FE4D4D8CE5EULL, 0x39AB69F3EC8FA089ULL, 0x0B2922E8D7D17C75ULL, 
            0x1119C48EEBFF1106ULL, 0x52C0DF04B08D3B71ULL, 0xAAB039A45D1377EEULL, 0x275792C22A60C501ULL
        },
        {
            0xD5CDECE8122C44C0ULL, 0x945266AB0D3C9EEEULL, 0x596E116CCD9909E0ULL, 0x1512E2FF676D4A15ULL, 
            0xE6876CF85A7FD571ULL, 0xC56EB93FCA76BF5DULL, 0x4F6C7F841EB08983ULL, 0xD083330D625A1E2DULL, 
            0x3C925C99209959BCULL, 0x11BEE147833E8A9DULL, 0xD713BB84D64ADED2ULL, 0x7F3038AC23C0E353ULL, 
            0x704C1B187A0D069EULL, 0x877AE492B7817182ULL, 0x6723BF7975271173ULL, 0x282FF38DEB94EC81ULL, 
            0x199EC6E64CF4BCD4ULL, 0x7CD55B80D977E283ULL, 0xF6FA51B52035E347ULL, 0x3DEB7F8FD8198CF0ULL, 
            0x673A5145A2503022ULL, 0xFD54073FE1FAAE99ULL, 0x20D7B9C3CE4C22D8ULL, 0x5A88B63EA4C40B12ULL, 
            0xA680E166A45E1317ULL, 0x911E47B4BC51401EULL, 0x0C424523BBB08A2DULL, 0x2354679713AC4CB2ULL, 
            0x9090B4C99E44D472ULL, 0x17A3301E86A5A177ULL, 0x1B183F831E4585AFULL, 0x7DB13778A3BFB3EDULL
        },
        {
            0x204395C28B8EF8E4ULL, 0x695BB952314DB452ULL, 0xCE1E1EFB5B7261B5ULL, 0xE36B3A9C007DAE7BULL, 
            0x9543705F3DF7803AULL, 0x040744C744B9D530ULL, 0xC0AF4B22179AA3CAULL, 0x613F84429910D8B3ULL, 
            0xA45C8F41CACB901FULL, 0xEA3DDDC17CB9A3D0ULL, 0xEC0A11F252C444AFULL, 0xE09B0CCB02DFF266ULL, 
            0xE3A5AD7538C741EEULL, 0xA98C47F41F7D190EULL, 0x85B586AB8C8904B3ULL, 0x39D92F9948322A15ULL, 
            0x04A9EBDC292C4DC3ULL, 0x017E58CCC5A157BAULL, 0xEE9299847D1C9BA5ULL, 0xB3AF167E41B43059ULL, 
            0xD61E8B318229F268ULL, 0x3616550FCB2B0ADBULL, 0xA9B41782317145F7ULL, 0x94B8D552D61D5F44ULL, 
            0x977C5EB947048EE3ULL, 0x752F03F650FE3337ULL, 0x67667050309BE275ULL, 0xD5D02A4FBA17C595ULL, 
            0x49C33915AC14CD45ULL, 0xBE8E118C00FAD24FULL, 0xD16CCF14C96E5E5AULL, 0x717751730172C490ULL
        },
        {
            0xF2E63A38036C2447ULL, 0x7DFE5218D2FBDB11ULL, 0x528EE27A2B0BAAFAULL, 0x42C5CE87F6E5A59AULL, 
            0x4F82620107315068ULL, 0xD65DC283D07818BCULL, 0xD19B80E8054D5746ULL, 0xB6D8F6E60A29DED9ULL, 
            0x369E5FCBDCC70DF1ULL, 0x1DDEEB82E9780912ULL, 0x06D8261B9E530CF9ULL, 0x67E563F3595D6DE9ULL, 
            0xDA374F3B9226CC83ULL, 0xC5659C3795EFA093ULL, 0xA1AB4246392765BDULL, 0xF2A236A2AAD46820ULL, 
            0x7B8CBBA1A59B27EDULL, 0x6DF33628880AA577ULL, 0x6DBCF997F0D89C71ULL, 0x1F773BFC3FFF9A04ULL, 
            0x80FB045B4423B642ULL, 0xB1C7718613D56925ULL, 0xFF95DC6EB3AE255DULL, 0x5ABA87DBF082FD46ULL, 
            0x72C695221633AE43ULL, 0x4C00B998C58858B0ULL, 0xC107D1CFEF18875BULL, 0xD5CCAEA6A6BF6E2EULL, 
            0xC13A89D4C4524F04ULL, 0x49CC876FCCC09BEEULL, 0x4E65442B2760C73CULL, 0x2145F30F86516E27ULL
        },
        {
            0xEC244234D8A2F165ULL, 0xEED22F71FEA3BA1EULL, 0xF5343313C0026FA6ULL, 0x197FC386D92BEE17ULL, 
            0x99CA0F034E60058EULL, 0xF045EC5B05F0531EULL, 0x13FF24B67BE24783ULL, 0x6278DC1C1BAE33BBULL, 
            0x0D937F41F21035A6ULL, 0x1B29EA1C9690C1F1ULL, 0xCF1C8DE9D2D9184FULL, 0x596BD1F61E33A15FULL, 
            0xD4A51ED02A6C106CULL, 0xC116A5ECD1F3FF93ULL, 0x49A970353E2ADEE3ULL, 0xA73AC2A1EF4D9BCFULL, 
            0x99D42EDEDF7B4307ULL, 0x517C97813D05A2EEULL, 0xC9D3DFAF58D39ECCULL, 0xAEFABE92A2AA8BEFULL, 
            0xC7089C75E3884DD1ULL, 0x05D0CF504BE12479ULL, 0xDBCA067200618C4FULL, 0xC639B0ED984B3C4CULL, 
            0x9B92A49894CE02D0ULL, 0x4C0DAB9EC047CD9AULL, 0xB7C67EC649F80F5DULL, 0xF9C3C2365874D790ULL, 
            0x7273381B231484ECULL, 0x9308E5CD835286D4ULL, 0x9F9BB3BC66158559ULL, 0x912C5236D5F4C42FULL
        }
    },
    {
        {
            0xE8029A2022F0AA84ULL, 0x199BD3838140E6E3ULL, 0xD8F45C6DA9DF2CCEULL, 0x6F895E1E39B6E9A4ULL, 
            0xAB7A09C4C22D416BULL, 0xDC18F79DF02802A4ULL, 0x1674C3314B2B33ABULL, 0x76869324DA2BA77AULL, 
            0x8634106277F5C84AULL, 0x577C104C101342CDULL, 0x6053BE1765087407ULL, 0x49681796296E6603ULL, 
            0xC74C5A2D9591C176ULL, 0x5CEE42538BF0AF0BULL, 0x91295E3151675C87ULL, 0x0D6D347332805769ULL, 
            0x470C97059EBA37E6ULL, 0x7D4AD2168735B4ABULL, 0x911768C6A41C73B9ULL, 0xFFDFB5B57943C922ULL, 
            0x85DD168A4AB1DB7EULL, 0x976BB441284BDCC3ULL, 0xF3CD34876F9C56ACULL, 0xE6685E5444156998ULL, 
            0x173B5F8B2840758EULL, 0xCB7E499B67592A38ULL, 0x66535EBD85A4C2F0ULL, 0x5CFFC9A8868EA591ULL, 
            0x1938F782E7C1BCDDULL, 0x48890A3915711318ULL, 0x8038D305018D6185ULL, 0xF47185926C9A6E7EULL
        },
        {
            0xB85E75B3AAC37862ULL, 0x3D1E64658CA70973ULL, 0x20666EEE4CB6CDE5ULL, 0x3C560AF64D411D2DULL, 
            0x2D709E06CDBD09F0ULL, 0xE8E20E6BA1D8C1C8ULL, 0xC78264A4F816B1FAULL, 0xD2FC7C3B47A275B8ULL, 
            0x8A6FAE49AE1460EFULL, 0x8B8C361E6126A475ULL, 0xDDAC8C9741C481E4ULL, 0x6ECFC04E9E7C0191ULL, 
            0xFD8EAE2ED81A99EFULL, 0x324F0A3E844A8FB8ULL, 0xE3B64CDBF0851060ULL, 0xBCECEDF51CD9FE9FULL, 
            0x34A5F82BA15E475BULL, 0x6AF04E30BCE4212DULL, 0x010DC53192F3FD0FULL, 0x219E87FA59545C8EULL, 
            0xF1E730946FDED27FULL, 0x8C1D134EC550C168ULL, 0x7B4E94D3C7A356E8ULL, 0x888C90A250184E34ULL, 
            0x83795B7362B4D55BULL, 0x108B434A3321B406ULL, 0xAA9C2616E0CDB305ULL, 0xE43232F16A9B38BBULL, 
            0x778216A9F52F38F0ULL, 0x6E7E435E6632DF2DULL, 0x1E24B564DA6DA3D6ULL, 0x4CC218DFFC4B2245ULL
        },
        {
            0xB64826289F9A2A15ULL, 0xCF3CFB0367FFA3D2ULL, 0x9E23E19832A25A91ULL, 0x9A01DFA230CEBD44ULL, 
            0x24A7AB5D8794CE4BULL, 0xDB39BD87CA1D0884ULL, 0xC757C0207A3D7094ULL, 0x1B2B07D996EDB265ULL, 
            0x4F7B3834DA1A2337ULL, 0x5AAE6BC9F677855CULL, 0x6E80644A3A32ADE2ULL, 0x61968AE84680B9B1ULL, 
            0x94C78B19E68C8E2FULL, 0x2A5AAA887DE34FEBULL, 0x4ECD3749CF02BA69ULL, 0x44C267BAE31921CCULL, 
            0x32937E35B47C8DBCULL, 0xDCB68B026C93309DULL, 0xB5422BE7E05E8C57ULL, 0xABA1681AFFA17742ULL, 
            0x6995A4C8A37790A9ULL, 0xB6A7DFA2D5C46BA2ULL, 0xEDAC43C13C42B721ULL, 0x5F21BED50E6FF46DULL, 
            0x5CDF321D646F1564ULL, 0x29342B99FD7C8AA7ULL, 0x6312F7CEC40AC445ULL, 0x66421057A2AC5D94ULL, 
            0x512122C5C8F73A41ULL, 0xF71D7D095C08E5A2ULL, 0x93FC287BE0C9658EULL, 0x2A91FEFD4EFF1197ULL
        },
        {
            0x674644C38C2450EAULL, 0xE523B2C459CF686AULL, 0x1D30441FB43A480AULL, 0xD69AC7D31AAC5B52ULL, 
            0x85C34EEA168329F8ULL, 0x6C3411087E5EE555ULL, 0x8B8BF396456B6306ULL, 0x475CB57C2FAAD25BULL, 
            0x925AB788BFF1C3EEULL, 0x2D502000E6B78CB4ULL, 0x387B1EE7FBA1082FULL, 0xE6D889604B7B9A52ULL, 
            0x65C80FA508E268DFULL, 0xF66F49779E363024ULL, 0x4C0230E3588BEFC3ULL, 0xFA917EBD0400F2ABULL, 
            0x99F1AFD7221E7BE9ULL, 0x4ED4A14D70779D04ULL, 0xFE8A763E9DA235B2ULL, 0x252280A95100029DULL, 
            0xA627EBAA68BCE2F4ULL, 0x71BD7078F15A68B6ULL, 0xF743CBD19CEB0278ULL, 0xBC15566FEC9BCAD4ULL, 
            0x0461AF52C33D1A55ULL, 0xCB4C165B78D6D9FFULL, 0x7207247AB2CDC5C6ULL, 0x9B9EAF1E46D256BDULL, 
            0xB9A78FFBAF2A97F1ULL, 0xE770EEB51B402B82ULL, 0x8EA9E4B14E15D213ULL, 0x4941440B2B480C40ULL
        },
        {
            0x54A928EC3DD280BFULL, 0x7BC56D9F177A0B65ULL, 0x75664B06EBA7D45AULL, 0x7965F3DA1A2263E1ULL, 
            0x9BDAC1E6F973E51AULL, 0xE83F0BE86C88FB41ULL, 0x871128EC73B31612ULL, 0xEEDC59D2A4D0074FULL, 
            0xDDE23C4DA35E7FC5ULL, 0x144E08C13B336F06ULL, 0x09FBB90328EF89CBULL, 0xFEF69996D60200F6ULL, 
            0x2E604C22082D6D26ULL, 0xC2194B1B75E0D519ULL, 0xD20F3958FAE152E7ULL, 0xC16349988EEFFB4CULL, 
            0x764B772356FA9DDBULL, 0xF44F54E4672B0671ULL, 0xBDC7AB4E845A53C5ULL, 0x1CB49D34AD4610ABULL, 
            0xA9E46817116A63C3ULL, 0x1348DF80E951F7ABULL, 0xA565A3A25ACBF560ULL, 0xD6D6104B74167925ULL, 
            0x8C85F40DE03F8DF1ULL, 0x15D5F50B149BA12BULL, 0x1EED619CA1968B98ULL, 0x514972E03A895BA1ULL, 
            0xFC39644DAEB5E173ULL, 0xC0449E6CA65327EFULL, 0xD598E63FE996C0D4ULL, 0x218491D2110EEFCDULL
        },
        {
            0xAAD8E3012EF62BF2ULL, 0xE632527C532C433DULL, 0x7AF9DF0C9BD0A193ULL, 0x6014EFA1A58EBC82ULL, 
            0xC6361FDE312799F2ULL, 0x9B8BD424743ED658ULL, 0x86DCAFB92CAADB03ULL, 0x75006161E7FBE21EULL, 
            0x02288B2B6D155190ULL, 0x9262136382781224ULL, 0x2EEC85007E2C95BEULL, 0x78448E73F6358780ULL, 
            0x768675539B5AFD9AULL, 0x976427556DB7A1EBULL, 0x928A1D4C5C56F65DULL, 0x2EAEF4B1B1B314E8ULL, 
            0x700B5DB69D041F49ULL, 0xB889F7861184B6D7ULL, 0x25264D4451436FE0ULL, 0xB03507FBA3C47B5FULL, 
            0x4D95AAAF71BE3126ULL, 0x47EFBBDF25D4FC98ULL, 0x50C919BFFDDFF6E4ULL, 0xE59C1760D3F07AB3ULL, 
            0x01303C68A315E916ULL, 0x5E4E2059AF90A158ULL, 0xEACD8E199E4E6B16ULL, 0x4B3E89887C88704DULL, 
            0x19F9D1822FFF34C6ULL, 0x9421AA84F55FB110ULL, 0xD44C0431E24A001BULL, 0xE7A85EBC652AF371ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseAConstants = {
    0xCEBB9099B442D6EFULL,
    0xEAAEBAAAA5B10917ULL,
    0x6E458F29CCC42F3DULL,
    0xCEBB9099B442D6EFULL,
    0xEAAEBAAAA5B10917ULL,
    0x6E458F29CCC42F3DULL,
    0xC62481F6EA30D577ULL,
    0x9EBC12969DEA757AULL,
    0x2B,
    0x90,
    0x39,
    0x4E,
    0xD8,
    0xAC,
    0x7C,
    0x3A
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseBSalts = {
    {
        {
            0x286291D5FBD354EBULL, 0xD2BFA7AE261FD900ULL, 0xFB4FBB62F4AA03FEULL, 0xC2DAF64204D7ED54ULL, 
            0x4507EA0FE7B7C44DULL, 0xCE83E9E045BEE2F9ULL, 0x643B2223FF686EB7ULL, 0xBA9B0B8B417F768BULL, 
            0x4E4CC03DE8AA6D72ULL, 0x9B3A5238CDE36A79ULL, 0xE158DDD8B35E4829ULL, 0x3A4C492F55758F10ULL, 
            0x7393A8CC6BC19FF9ULL, 0x657DD78430EF1227ULL, 0x7887EF6BA5EC57BDULL, 0xDFFDEB2C10DB0806ULL, 
            0xBEB784BFBDE2B56EULL, 0x7043D53F95B61315ULL, 0xA4C37222FEB560F0ULL, 0x5B88FEF701823243ULL, 
            0xA5EC1875575E7431ULL, 0xFF9039D699571161ULL, 0xF30192628181CF3AULL, 0x2350C87D97FB3EC7ULL, 
            0x02AB2D5CEDC4914BULL, 0x1E4799DB80B02D58ULL, 0xA6DCCD7A6E2C4ACFULL, 0xF401AF0CF38E37C1ULL, 
            0xDCC167813E190269ULL, 0xBC5ACAC4DA4C5D9FULL, 0x5C3CA8E3D0517443ULL, 0xCA676D986AAECA8CULL
        },
        {
            0xBD55B5602986F995ULL, 0xD192CFA671A91407ULL, 0x1B9ADAE995422DB0ULL, 0x0AEEE51C306BB60EULL, 
            0xF66F42A72970E7FEULL, 0x206EE18152200C55ULL, 0xD8596E0406D3371CULL, 0xE71251713D2DF30BULL, 
            0xBCD181EEB94E202FULL, 0x6AA99A67396AF6D9ULL, 0xCB3DB8C65A8594AEULL, 0xBFFFD5D4EE8AAE12ULL, 
            0xB34F6FD651A3BA94ULL, 0x2CB3C23890E584A6ULL, 0x382D2DFAFEE000FFULL, 0x0312598E550B5D17ULL, 
            0xCEB9647ACFC9081AULL, 0x7BE94C4C574732B4ULL, 0x3CF4EC4F60E6FA7DULL, 0xC851B6908A82ED5DULL, 
            0x9A15AFD80FA0701AULL, 0x41DD3DAB86015786ULL, 0x1E63A8480B6D73EFULL, 0xDEDCE1B6B36D8585ULL, 
            0x3B2D30F8FB93B248ULL, 0x04BF204A90D0A964ULL, 0xE3FC7CCC74BC094DULL, 0x4F9A5F007F8AD02FULL, 
            0x9C2A440699CBE4E9ULL, 0xBD9CB85EFDB18D17ULL, 0xE210BE7E112AFEBCULL, 0xF370737576EED616ULL
        },
        {
            0x7665FC310A99B8A2ULL, 0x313D93BE5C696B20ULL, 0x891853B5A0CDDEC4ULL, 0xED703DF0CE0F6E5CULL, 
            0x1B2DA5E11E9BCD32ULL, 0x3165795B05997336ULL, 0x4A31B52883F8291FULL, 0x4FA49D2938FE84C1ULL, 
            0x0837450DA51CC5BFULL, 0xC9842C97B48E7418ULL, 0x37903789EF128CD4ULL, 0x0C1E54F718D2B826ULL, 
            0x1FCAD9513EBC2169ULL, 0xC8397F6EE0BD5EBBULL, 0x8E305C6FCABE6406ULL, 0xBCE561D0B477EACBULL, 
            0xCD3181FB842C61C1ULL, 0x2BF29535ADA4C0C8ULL, 0xF7D26A385CBBA597ULL, 0x04143D8EFF5F51ACULL, 
            0xF42B3E0C955D5395ULL, 0xFD7B8387D79B16C3ULL, 0x77D1A7178EFF90EAULL, 0xA7E3F3A0713C3DCEULL, 
            0xC1894F6D7165AFFDULL, 0x11FAD9C78283BBCBULL, 0x44EB191E01D57E5AULL, 0xF2BF3ECC8186BC21ULL, 
            0xFF7A1E5BEE908BF6ULL, 0xD0B2637ED87FCE6EULL, 0x36505D6F9A3FA843ULL, 0x30CECF2A2DEA40CAULL
        },
        {
            0x0BD9CE72DD518B1BULL, 0x322C689DC331EE89ULL, 0xD99B3628A6A1B790ULL, 0xC6E5EA84253250F6ULL, 
            0x2FAAC895C35C4D05ULL, 0xDFE4FA090AE74FE9ULL, 0xCDF56011F0F080B6ULL, 0xAA51B06A4B606DF3ULL, 
            0x534A9B32939E05D1ULL, 0xBEFBD6C53BAA7CC3ULL, 0xBB9BCDC458C8AE54ULL, 0xF5452FC9C61BC194ULL, 
            0x9C00CB29B527042CULL, 0x9E1050F2DA50256DULL, 0x0629A74C8DB698C4ULL, 0xC9B4C337D37CF877ULL, 
            0x072F00804D8F85ACULL, 0x40698214FBD110FDULL, 0x1AF490FD21A364D4ULL, 0x561020393F10081CULL, 
            0xB73FF1DB21168C64ULL, 0x034880CA78B58B3EULL, 0xB8DE8C87BE714BC5ULL, 0xB74A2CF4A204297EULL, 
            0xAC9ED1C48ACDDD75ULL, 0xC70446475AA00E34ULL, 0x8306EC26DAE6CFB1ULL, 0x5132F8E40501BAABULL, 
            0x7209AC0D28EB2980ULL, 0x6ECEF7C3C96C6EE6ULL, 0xEE595313194FFDFAULL, 0xB57ED584E60EF071ULL
        },
        {
            0x9778465942D4A59DULL, 0x8BA57423F53643A5ULL, 0xFE7BB3D4DE593DB7ULL, 0x5FD1202823A3970DULL, 
            0x05F9896ADB8C50AAULL, 0x3E6F84F5BB95E17AULL, 0x2C9A6EDFEFB7B79EULL, 0x987D167212760D1DULL, 
            0x89502C5069090A3DULL, 0x37D6E0256CE9DCCCULL, 0xEF37DDBB145C9AD6ULL, 0x1F8B349CB70135D4ULL, 
            0x811C924A94ACD623ULL, 0x523D02D500FD7117ULL, 0xC4EC034F34E75B6CULL, 0x6308F3E9EA3EA92DULL, 
            0x74B4EA56EF01ED59ULL, 0x28939E87C597EB12ULL, 0x512EA2DF17059D53ULL, 0x206B749A8E363E8EULL, 
            0x6A5B2CA2EB0C4D1AULL, 0x8C32538DF871DD59ULL, 0x8D3396B5864EF94BULL, 0xC326A01BEDD488A2ULL, 
            0x5E914F0D7F46ACBEULL, 0xF33E0337E5BFE44AULL, 0xAE890E4BC28F99F2ULL, 0x28768FBF6102C1B0ULL, 
            0x18815976DC447DB4ULL, 0xEB70CEC1F168B39DULL, 0x0D6553C9BCC0904CULL, 0x6195253575FCD73EULL
        },
        {
            0xCFEE87DEEF5CF227ULL, 0x41003567B0223502ULL, 0x3AFA1EFDF6B8AF4EULL, 0x80F18B384AF28951ULL, 
            0x2B023D7A805D8AAFULL, 0x96A3DCD0E42976ABULL, 0x7F099D34EA5A6EB9ULL, 0x08A0A2A01CA920C3ULL, 
            0x2ACAC703FE1ED6BCULL, 0x2701FC877AF3E40BULL, 0x16286790FF111FF9ULL, 0x6CA9A0CA07FDE206ULL, 
            0xB774091CC06D3944ULL, 0x739369DA895B717FULL, 0x62079F078787B913ULL, 0xAF3533FF21BCB66EULL, 
            0xBDF15674F92A10BFULL, 0x3CF072AA73964EF4ULL, 0xCEA620A15D7F5E50ULL, 0x710834C2A38B5A9DULL, 
            0x9EAA075D604F6250ULL, 0xA89254BBE871F1B1ULL, 0xBC18AC6A20811424ULL, 0x398D58F9070E2C15ULL, 
            0x82B8D670F76C9792ULL, 0x890A83A4AAF55024ULL, 0xAB2213A148B56839ULL, 0xE8713E6CD62D5DBFULL, 
            0xDD982A37B0D6C1F8ULL, 0x8A18BD12D9663635ULL, 0x9B9F8464BFB4E515ULL, 0x96C32A521AA0683EULL
        }
    },
    {
        {
            0xD926526F7BB338C8ULL, 0x38AD03F51294550FULL, 0x14874E4CCEE549B1ULL, 0x9427A4C89C1F3DDBULL, 
            0x80FA62127B174842ULL, 0x2D2472FDFD4048F1ULL, 0x2452D696A8E52AC7ULL, 0x3C224B7F4A262451ULL, 
            0xC0E2E5D92A084CA8ULL, 0xE0F29FCB21F294EFULL, 0x237455208E7BD16CULL, 0xBE20A385CF8040D3ULL, 
            0x106CEBFD8255B62DULL, 0xB9BC39DCC053337AULL, 0xA1900CCDD5658295ULL, 0x5D7D4C56315F3CC7ULL, 
            0x7B4ECEEF3113E138ULL, 0x00970F810E9FFF40ULL, 0x4BFDA26B0A65AB13ULL, 0x1AEA07A9588A271AULL, 
            0x291D92B6528AD08EULL, 0xAC99925716343C77ULL, 0x8D73F19CCC4D9FE6ULL, 0x653C9AAB24FB3FA1ULL, 
            0x3BBA772D44D7C28AULL, 0x7875C9CBD7260DC1ULL, 0x6A41F522BD40B863ULL, 0x788567364C54FDEBULL, 
            0x3D44849C415D7095ULL, 0x6DE1DE89EFD10110ULL, 0x18F41453C8195C93ULL, 0x5F8ED8A876C917C7ULL
        },
        {
            0xC428BF9A3DCE92DFULL, 0x39C6A6899CEC3DFEULL, 0x3AD881EF44996570ULL, 0x63DD90FA4DCB681DULL, 
            0x12E85FD17B816876ULL, 0xFF1DD1FB806C42B4ULL, 0x6ACE58BCDCD107CAULL, 0x3D19C29388660B14ULL, 
            0xB413FE5E0AE6732EULL, 0x9042C6DC3DA4D932ULL, 0x9738E1B60C2FD236ULL, 0x41FD948F2AB4B3F4ULL, 
            0xF0DBC72A3F30B1CAULL, 0x515D2A506391DBCAULL, 0xFBD9B1E90E398A04ULL, 0xCBB74AF6FDC444A5ULL, 
            0xA762ACC919AA0E7AULL, 0x27008FAFF0A151BEULL, 0x596713D92EDF3394ULL, 0x35E1E37DA2B7A93CULL, 
            0x1D6EF4FB809CCAC0ULL, 0xE364F61A56F3DF16ULL, 0xDC4273CD78C616C5ULL, 0xDE7DF99B2590F88BULL, 
            0x4E84D4D316C9FC94ULL, 0x098E237C0F8191C4ULL, 0x4F554DD1405E4982ULL, 0xA74D3893B4B06576ULL, 
            0x3F03AA02FB506254ULL, 0xD2424BE121858BD2ULL, 0x2B370013D74957FDULL, 0x627CAE81D10EB22CULL
        },
        {
            0xF5E6BA41D22E9CCDULL, 0xA321B1A4EA1C044CULL, 0x026B5EA42302851FULL, 0x5F1B3CC37280C17FULL, 
            0x50B7D4DAAC09D531ULL, 0xC68FE8A036BB5B32ULL, 0xD9B2C83DD391BDE1ULL, 0x77DC89CF2BEA2845ULL, 
            0xC21C214C2E950867ULL, 0xF83B020549975666ULL, 0xFE0A3CD83AED3273ULL, 0xAA05C19BCD4176BFULL, 
            0xC414FB926BE858FDULL, 0x7503CE73A725EFFCULL, 0x8EC823D805D5BE1FULL, 0x6F7438457883B691ULL, 
            0x9E4B3A9BD29AB51CULL, 0x7DFB84142FF44A57ULL, 0x5AF87357D4408D77ULL, 0xAAA2FDBDF67D4D1DULL, 
            0x9AA382C72CF352A0ULL, 0x93E846C08772071FULL, 0x9FC7F6E0B8791606ULL, 0x81BB83CDCBA9CBD6ULL, 
            0x8C29D215E42DB2A8ULL, 0xE4636578268BA2B8ULL, 0xD41E1DD7D029F4B5ULL, 0xA7BD8F08D86D7B68ULL, 
            0x14E2E3196C3E7681ULL, 0x76834E41462E3955ULL, 0x3C66C0FA687E2CA9ULL, 0x4922E34C4A9D1A53ULL
        },
        {
            0x3DDF5F0E2D605B98ULL, 0xAFD575DD354EB831ULL, 0xAAD68C9A8C358549ULL, 0x23B2C4E09C2C0FEFULL, 
            0x4F8F837F314FC478ULL, 0xB0F2B016A2C9A102ULL, 0x06A64E65BCC3C234ULL, 0xA4D6C28B44A8B3D0ULL, 
            0x4BEBFE582BEAB4DDULL, 0x611C7AEF95BA8133ULL, 0x92041C5D43D530D4ULL, 0x3C050563126C060DULL, 
            0xF6759C8776D55521ULL, 0x0B9E9D0F34676A24ULL, 0x78C01C1EBD7D933CULL, 0xF58D073ED6695F52ULL, 
            0xAA8CA46BC56FC820ULL, 0x06CA31A2776055ECULL, 0x8B45B0B93CDD8270ULL, 0x7E78E474B116E5AFULL, 
            0xA334BDB87B54CCDDULL, 0x670B5C7CD9C0AB06ULL, 0xBC8CE6110CC94878ULL, 0xCE2F809DDE11A1B6ULL, 
            0x847A3BC6809284BCULL, 0xCCE462CBDC32221DULL, 0xB01D3F88E832FFAFULL, 0xAC3395ED88A0E414ULL, 
            0xCE2FD721A998804AULL, 0x6A3EF4C666068B7FULL, 0x3FCBAC2CDF6DEE27ULL, 0xF118065EB81E411EULL
        },
        {
            0xCE1C24E4F5C16F24ULL, 0xF9E94DD26B86DEF0ULL, 0xB3721285CB87BE23ULL, 0x908ECDBB08A80039ULL, 
            0xFFD6801D1E765802ULL, 0xD1864B9217B79517ULL, 0xA225CD6C6B3B44D6ULL, 0xC0D4F1F5A458690FULL, 
            0xF68ECE6B6192DFF0ULL, 0x910201D0456231C5ULL, 0xACC580138E0DB542ULL, 0xD30B74316DCC8E54ULL, 
            0x05BC139E271DB096ULL, 0x049988E7C6835730ULL, 0x9FE00984C664AF01ULL, 0x4BAEFF44259ECA82ULL, 
            0xC01DEDF9F69900C8ULL, 0x229A6125FEF58FD8ULL, 0xA0CFD48A048DFAA4ULL, 0xB16C0229F86A2DA2ULL, 
            0x06D872A70ED245F4ULL, 0xED80A23F83143E69ULL, 0x7AB6F29CEAD12102ULL, 0xB9FB7E49C1BAD000ULL, 
            0xDBC6018675BB3205ULL, 0x0DE740CA37351A15ULL, 0xDF62707EFB58D304ULL, 0x2667AD35C0B3C1A2ULL, 
            0x7E7C6B69B17E3034ULL, 0xB8905D4A62EFAA70ULL, 0x708203F9FB569B3AULL, 0x40AD76FBF8335346ULL
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
        }
    },
    {
        {
            0x62F353A8F7597DF5ULL, 0x4CDCEE37524D4E69ULL, 0x2975F5BA5F1D2AEDULL, 0x7C06339E6E06BD35ULL, 
            0xF7FD197B1C2BD6D8ULL, 0xC95EB821B5DBE9E6ULL, 0x7DADB818D2D406F4ULL, 0x261122BF515A5160ULL, 
            0x29F8C8C8CFCB651DULL, 0x613C327566CFE12DULL, 0x9C4A6609B447CA16ULL, 0xB3E467DDF5A96DD2ULL, 
            0x5EEBFB470534BA03ULL, 0xAA5CAC1273FA7EE7ULL, 0x36E3DEDB05BD729EULL, 0x80C28450259AF1DCULL, 
            0x91A4F94CDD0420C4ULL, 0x272E8047E4570368ULL, 0x4E9826442FD1DCBBULL, 0x32529D8C769A4FDDULL, 
            0x54FDE3E70182A13AULL, 0x73FD38449E185C25ULL, 0x960C3D26D23CDE10ULL, 0x3013C9BB781B6C89ULL, 
            0x035B6B02F0AE5321ULL, 0x7937892D5176CBAFULL, 0x95D5481A712C4DF9ULL, 0xFB51726DAD7FB0D5ULL, 
            0x9BC8B94C06400B03ULL, 0x3DA3D323A224737BULL, 0x47B19A2BFCDB5C9EULL, 0xC575C119C31064ACULL
        },
        {
            0xE744E39CF7A8C430ULL, 0x89D275BB6E7E63D4ULL, 0x175C092A68F74D78ULL, 0xCD98834D46A81555ULL, 
            0x04C33EC62A78BDA9ULL, 0xAADCED1E1B47530BULL, 0x9B4E760110EA42DEULL, 0xCA6E41B94246B3F5ULL, 
            0xE3E390ABB44C06DCULL, 0x7A7C813C4C46F6AFULL, 0xA5468F26F5CD8768ULL, 0xB0142C122991F902ULL, 
            0x1910584D6AD999CFULL, 0x84BFF2775E4845C6ULL, 0x1B72AA7D224D0A57ULL, 0x436D14ABFB58B3A0ULL, 
            0xE91972735967C3A4ULL, 0x094DF85768D526E5ULL, 0x156F46946B20E52FULL, 0xA0B6D34009DEF430ULL, 
            0xC3E2B008C5C592C7ULL, 0x989309045D0E0C19ULL, 0xB4662BA028389CA5ULL, 0xE9E95793AADCF587ULL, 
            0x480FF2E10513A6A5ULL, 0xF1D78F5630C4FE49ULL, 0xADD1B3496BAEDD53ULL, 0x1DD526454FB43ABFULL, 
            0xAA6D1F3B6D81D447ULL, 0x7322AB17E0E23A0EULL, 0xC913736833251230ULL, 0x0740C69DF889B60EULL
        },
        {
            0x285CB7DB1087DC89ULL, 0xCA35FF6DB0394BD5ULL, 0x34A8A52428F4AD63ULL, 0x093E10AB8CB53B11ULL, 
            0xC657264D890859BBULL, 0x3037C13A3AB44A6CULL, 0x054EF548D33485EEULL, 0x676B09B36B047680ULL, 
            0x8A1753DDE4A792ACULL, 0x684585B18917BD1BULL, 0xD7450BD9CADE513BULL, 0x35925886EB066841ULL, 
            0x85FE23ADF4009CE0ULL, 0x0C26B0F2946981E5ULL, 0xB3FF614BDCC8E205ULL, 0x73F6126FF3999F80ULL, 
            0xC731B21DF550F693ULL, 0xD3D3F3C0330A98DFULL, 0x9E65C7F4A26F306DULL, 0xFDA55CBFF70CAB8FULL, 
            0x2A94F0865496F93FULL, 0xF8F4579C7A7EC690ULL, 0x70F075F068BCFD35ULL, 0x77353683E9E575B2ULL, 
            0xEC57C85690F96B0FULL, 0xDE496136D14FC1CDULL, 0xE403CE4987009963ULL, 0x397A8EB556581226ULL, 
            0xC5BB865F43D8BC00ULL, 0x7F63C7911B40E9DAULL, 0x971FAD606FBA6719ULL, 0x4486E143458C281AULL
        },
        {
            0x52A9C6659C52643BULL, 0x0AB7F4733CFE8743ULL, 0xB97AF92C059E2C44ULL, 0x136418F6690322E8ULL, 
            0x47DDB6C5CC5C0E8DULL, 0xB8369A7BCA2C708BULL, 0x1FFE85AEF0527BEBULL, 0xF82255CDF107BC22ULL, 
            0x5F576C0FF9B46238ULL, 0x41C480D7DA07BD8DULL, 0x4E4FDB0B9CFF8DE6ULL, 0xD3CD40202C172691ULL, 
            0x3315CBAD8EA28821ULL, 0x8E655B0DF751CE7AULL, 0xD4A24934482FDA55ULL, 0xE340CD3CB1957935ULL, 
            0x10B46852A11EE180ULL, 0x9BBE56AA56E64459ULL, 0x5F829328887BA7EDULL, 0xA189B5A711AB784BULL, 
            0xBF72F89454CD3039ULL, 0x2ABB89BFBBE30963ULL, 0x0BC3AF1CA8804009ULL, 0x44688349F6F96C04ULL, 
            0xA2485C833AA5B6ADULL, 0xB17863E747195230ULL, 0x658EA2E9C62351DCULL, 0x81DB62947BF6D8D2ULL, 
            0x0A2399522E919423ULL, 0x1B281D4023E19DE7ULL, 0x94AF17091C1FC42CULL, 0xAC1323A44476C98DULL
        },
        {
            0x392DF28533AD2A71ULL, 0x065424E37A9FE6F8ULL, 0x9AD3EB196FB3E4A2ULL, 0x22C899EF77360F80ULL, 
            0xA4C3DE2D2BDF6CE4ULL, 0xA181C639CCB47AE1ULL, 0x8441A3F9DB9D4F48ULL, 0xF70EE947F0F73A1DULL, 
            0x62A79656BC927074ULL, 0x4C491BC89D444B77ULL, 0x7248B18EF904C838ULL, 0x6642913D82C02DB4ULL, 
            0x5F45861AA07C8CABULL, 0xC1C19F7978981C20ULL, 0x77843B0FB095173AULL, 0x5037626D717127CCULL, 
            0x0259E4B930719B5BULL, 0xCE769F141D479E21ULL, 0x92F676F7F8E36DCDULL, 0xDFBB14746D0F1B64ULL, 
            0x0B6728DBD1A168ADULL, 0x5C459BA2E5FC94BFULL, 0xA2783B8B7C977789ULL, 0x28C5C5D1227B7C0FULL, 
            0x0CBFD279BED118CEULL, 0x0F878A7BF7FD68C7ULL, 0xEE6B6DF06C1AD92BULL, 0xC50B873AA078F655ULL, 
            0xB1E78004ED78AFB3ULL, 0xD42C0CACEA0E8E16ULL, 0x1539C6C0C1335B5CULL, 0xAFF0A426C8D28753ULL
        },
        {
            0xF307297557B9CF5EULL, 0xED39B2B11C92C3F3ULL, 0xC31186166EC3AFFBULL, 0x96EC7F811A3F655CULL, 
            0x6D482516D77D63DCULL, 0x1F1ADA877C7EAD8BULL, 0x0D0541DACA036C22ULL, 0xF72FBB7693FE2E8DULL, 
            0x293EE15AEFF8EEF2ULL, 0xBE69F672BAAE2CB5ULL, 0xADC323E6349ADC2EULL, 0xA09136775FE589D5ULL, 
            0xA286F92F8AD3C293ULL, 0x9B23484F0F62A1A0ULL, 0x2962D73E67D049EBULL, 0x36E95D9743859B41ULL, 
            0x32D6907A439C6387ULL, 0x399C2C94705FECB6ULL, 0x54C14D83F9573170ULL, 0xFF9FA194BD95A195ULL, 
            0xA46A1DD5469597D2ULL, 0x30624B7F395C3035ULL, 0xA0625682101559FEULL, 0x10401944AD62EC1EULL, 
            0x953A363F8562310FULL, 0x3BC4A5504DBDA4F4ULL, 0xDD23547F035FE3B2ULL, 0xA51A7F1223E7C7DDULL, 
            0x850E6F1D865D9080ULL, 0xEEBB765A83772EB1ULL, 0x044993BE1AE247CCULL, 0xD83C7A3A4167D6B5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseBConstants = {
    0x02C20010C8925277ULL,
    0x30F692B6F8C35F2CULL,
    0x7240652AD2383081ULL,
    0x02C20010C8925277ULL,
    0x30F692B6F8C35F2CULL,
    0x7240652AD2383081ULL,
    0xAB5DEB3D0A75DE70ULL,
    0xCFA1DA42E66C4421ULL,
    0xBE,
    0xE9,
    0x06,
    0x26,
    0x29,
    0xC6,
    0x5A,
    0xF4
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseCSalts = {
    {
        {
            0x6869F3B922A1143DULL, 0x832788BA000535FAULL, 0x27F2BAB668AC6EB6ULL, 0x8DCDE6E5F6A05F3DULL, 
            0x1DAB35B13FEF0A8AULL, 0xE7994E0A91AB1D5CULL, 0xB88AE9EAFFB29520ULL, 0x4724B81B09D0D901ULL, 
            0x4D3A11A8322A0537ULL, 0x099CE83CD7C43392ULL, 0xB5E1CA7D98E2E4ECULL, 0x0B58428C8D318CADULL, 
            0x94BB4FD13F7B1701ULL, 0x10CA02085DCB6BBAULL, 0xFA7B0943A7918CADULL, 0xF4078BFC95DB9B3CULL, 
            0x372667A15C7B107EULL, 0xF3D96AE2C4F169DCULL, 0x399E72323314E926ULL, 0x97E6980449497180ULL, 
            0xA7ECDE50F0B727D5ULL, 0xEC2FA4EB848EA389ULL, 0xCA2DE7A0FDD04C7EULL, 0xDB596B344CDBBA7BULL, 
            0xF1D58E2486EE5FB7ULL, 0x74963F17425E5F0AULL, 0xCA2010FFE2FFC097ULL, 0xE147D24AA65F57EBULL, 
            0x86991617FF704952ULL, 0x7DCAD917171C115CULL, 0xD9B3AB51CC54F73BULL, 0x51C6D3B71CB45C48ULL
        },
        {
            0x17B12033FA39E578ULL, 0xAFB63806A05EB35CULL, 0x81C7E18531F95D48ULL, 0x5223D5AD473FFFD4ULL, 
            0x35204B8CBD3F0099ULL, 0x3AB466625CBFF3C4ULL, 0x2E1AAB3EAA1AA07CULL, 0xE221EBD0274DD3D6ULL, 
            0xA79243690AD475F6ULL, 0x093AF97845D6A1E9ULL, 0xEA4DE209266C8F89ULL, 0x2BC22E69EDCF1344ULL, 
            0xD97B6F722B064C53ULL, 0x2494371C33E909C4ULL, 0x2411D166F9D42AFFULL, 0x2351F5097DA41586ULL, 
            0x3393AE0CA3089D32ULL, 0xDF801E7A51BAB474ULL, 0xAC9E2384B58D35A5ULL, 0x1E94E02A2B861FCEULL, 
            0xF614616C933CFC78ULL, 0x3B51E189414F1740ULL, 0xB6786CCB60642C86ULL, 0x5C243F747CBF8365ULL, 
            0x13C3942D830B1D53ULL, 0x8F1251FB7AF93D51ULL, 0x87ADAED5AD824CB9ULL, 0x01B7DF09D42D0B8BULL, 
            0x79E632C2ABFA6E9CULL, 0x82FC81ACF3CE1E4BULL, 0xD012AABD32CB231BULL, 0x2CFFACB2579B46F7ULL
        },
        {
            0xA5BAAE58D3172413ULL, 0xE15C5AA7ECACE8DFULL, 0x79A890587CFCA355ULL, 0xFF60045E66A4FB33ULL, 
            0x47CE763EDE48F52FULL, 0x7F9586EFFF8F4FF1ULL, 0xB4D4FAC265C8B8C3ULL, 0xB5FB766FE8EC83DFULL, 
            0x833996DCEF0991B4ULL, 0x5B21AC292E264DE7ULL, 0xA1B4F2D738C7B680ULL, 0x7E38F68E8CC444D5ULL, 
            0x026B0C260C8F64B9ULL, 0xE20C7EFE438BA298ULL, 0x41B92DBBF811EFF5ULL, 0xA75D40F4D2A5186AULL, 
            0x77DFD6D1E6FB7386ULL, 0xF8594E91AFB80508ULL, 0x847030527899D80DULL, 0x298D5E388B76CCF5ULL, 
            0xD62062B3411DBCD2ULL, 0x54E239E0BF4815F4ULL, 0x268A7F0771488FFAULL, 0xB53CB3F0A873DFFAULL, 
            0x71909E9105F4E906ULL, 0x1820EDEB4F763D1EULL, 0xB59C3DA6DB980844ULL, 0xDA45FC2CC72A9EA1ULL, 
            0x7767D01407032C81ULL, 0x79FF4E25AD7EC86FULL, 0x12D3CF0128FA416DULL, 0xF4BDEBCBE81CB00CULL
        },
        {
            0x1BD96735C449B43BULL, 0x15744869DE570907ULL, 0x64BC9E647FD50576ULL, 0xF3F7306686B69A56ULL, 
            0x6ECD33C85797F30CULL, 0x1C18D5911F74F285ULL, 0x060D242F876C48DBULL, 0x49EC8FBDE7B7FEE9ULL, 
            0xDC9DCE3E9A552ABCULL, 0x51B92006883BD35AULL, 0x021DDCD84D1BC7B5ULL, 0x9D7D3D4F3E672B24ULL, 
            0x269AF9CEC01E4CE7ULL, 0xFD0A9CFC78DDF438ULL, 0x3F5C05EE6109B160ULL, 0x642E0DE00BE872BFULL, 
            0x2020C63014A7E7C3ULL, 0x71706A71AD804983ULL, 0x0C8FE1BB5A13B808ULL, 0x4EE51FAC4DF78E5FULL, 
            0x6970D130B7565E8FULL, 0xF775DD847D0B927BULL, 0x37EE1F53E1789F74ULL, 0x3DB9C6FB4C66AC61ULL, 
            0x9B1D77B3B951D4E1ULL, 0x3C359133459F8323ULL, 0x09585A0E8B5644ECULL, 0xB5C03C436B96D971ULL, 
            0x3F63B364A36AFB86ULL, 0xF5A46E149BFE364AULL, 0x74FFE08A127B75ACULL, 0xAF6C8D094F2BA0FCULL
        },
        {
            0x125EAC99E63F07E4ULL, 0x506EBACED94E8B81ULL, 0x6B005987BEE922EBULL, 0xF67D0BDF5C3E1E69ULL, 
            0x80D07832BCC4CE11ULL, 0x8209F1E7AF6E6F2AULL, 0xA90B93851FCAE6CDULL, 0x3D0B5CC7995919CBULL, 
            0x24C6A6CD2F68262FULL, 0x7AE68DC43F3CF76FULL, 0x7213CF6E8729E3DCULL, 0x0A4378F771004627ULL, 
            0xE9F8F0B1F55EE562ULL, 0xA51BDD28BFAA97CAULL, 0x709CA4C99411486AULL, 0x6F9A231E5DAD6EBEULL, 
            0x2A2A1042A4870AE8ULL, 0x4165961C594A25F6ULL, 0x44B521CB89DB77B2ULL, 0x98A44B312964FF2AULL, 
            0xE3ADFC59936D0E9FULL, 0xCD95F9B7C25CBD32ULL, 0x01B9E7B403C123F5ULL, 0x3496ABB07C49AA3DULL, 
            0x5A7B9AACDD4734AFULL, 0xF7E127073765E911ULL, 0xD2B748780FB8B609ULL, 0x400ABB64872253F4ULL, 
            0x9EF4358A0485DA45ULL, 0x37E3682938CC6A6DULL, 0xB19104C578F1D3C9ULL, 0xCC36C4FB34AC3F3EULL
        },
        {
            0x861063553426CA9FULL, 0x8B24DF3B0D00D1E7ULL, 0x78E8B98653E97CBAULL, 0x4B398B9305399A93ULL, 
            0xB967D53B171D9156ULL, 0x4224DBDFB72D5B7AULL, 0xFA8965B14E2C5AD5ULL, 0x278E3615D52F83A8ULL, 
            0x3E64F86C0035E0EDULL, 0xE411BB05FF0425BFULL, 0xCB40AD6239F154A2ULL, 0x3BE160513D624ADAULL, 
            0x0B3C3C9F52264FABULL, 0x448AFD1739106A17ULL, 0xDDA6FAE5D65A9C72ULL, 0x847495E8D502B5E9ULL, 
            0xEA56AE19A9765101ULL, 0x1A5B007B08D3046DULL, 0xA1B4BCEF14BAA3EAULL, 0xC45F7C8FAE4C8FAFULL, 
            0x470FC2CBC243190CULL, 0x04410196EB99ABE4ULL, 0xD5A7B481C4D631B4ULL, 0x796C003C7C0DD778ULL, 
            0x7B4FDCE9369E2785ULL, 0x682E687927E63C78ULL, 0x3C9BBBA38EB74307ULL, 0x20C6900A4B3D8FE7ULL, 
            0x92CB8E120974C466ULL, 0x6416E898457AE519ULL, 0xCBE192BCC158381AULL, 0x29886BE5E2F6383BULL
        }
    },
    {
        {
            0xC753C02858C518B6ULL, 0xD53CCE3978442170ULL, 0x0D1BCEFF4054C130ULL, 0x3E0B2D4B12304C94ULL, 
            0xE70BA0B1013DFD51ULL, 0x4FE92B56E338C1F1ULL, 0x4D9A8A74E255D5BDULL, 0x546547FDC56066A0ULL, 
            0x4555AD7B00A41CF2ULL, 0x5EB3C369329C7709ULL, 0x543EAC73AF7E9D4EULL, 0xBAD31141E20A655CULL, 
            0x93C8387B84F39529ULL, 0x67ABF4420C0C717BULL, 0x47AA813175549664ULL, 0xA153E4BCF93EAFF7ULL, 
            0xABFD0CAF69C392A0ULL, 0xEBB015176EDC2382ULL, 0x6395F7510E1F9B9AULL, 0x6C6ED547010C0767ULL, 
            0x12552343B4CA2786ULL, 0x55CEFA434CAF5283ULL, 0xB0D281004DEEEAFFULL, 0x319A4C972DD40353ULL, 
            0xC0E71AFED848CC32ULL, 0xDF4FEEE7E7579253ULL, 0x36CFD56FAF5322F0ULL, 0xC8DC53B75E55BFCDULL, 
            0x8509E0FA6179A0DDULL, 0x01D383458CDE0368ULL, 0xB424E5F34FB09B79ULL, 0x92EF54D423AE1CDDULL
        },
        {
            0xB261E97B7D91600BULL, 0x1B8C5B3A3E0DFE54ULL, 0x7F76864886DCC681ULL, 0x585DDA6C578B2926ULL, 
            0x30288F2CFF3F34ADULL, 0x4AD213FA56DB25A4ULL, 0x4C99B07E183D1C9FULL, 0x274C11347A6B4893ULL, 
            0x8AFC2A2BB82D9120ULL, 0xE6953E171E54F57EULL, 0x6DBD0D9C4E41A576ULL, 0x5AB97D5EB1D2A7E0ULL, 
            0x25E197F90606776DULL, 0x2B946B460344DF9FULL, 0x4C6D33BB73EEC71EULL, 0x1A6EA830FEFFA6BBULL, 
            0xD9E4E499A880A251ULL, 0x5B02211C0CE056D7ULL, 0x1FC58455AC5DC1D3ULL, 0x9C3C42C1EB8DC6EFULL, 
            0xA3C7D05D23FF97B0ULL, 0x39AB2F4EF5D5FB3EULL, 0xF5664CC2B5F74680ULL, 0x059E0CF0EA324076ULL, 
            0x9DFA3300B0D638A9ULL, 0xA94B9AF28D8B1BB6ULL, 0xC18D0C67FB339BBEULL, 0x80992D4B82718B29ULL, 
            0x70039C98FD051AEAULL, 0xA0B2E89FD2491138ULL, 0x4577CD6B6DFEC92AULL, 0xA6AAFDCBBB046CE9ULL
        },
        {
            0xBABBB6167A1C9559ULL, 0x1767B65BBCCD5973ULL, 0x6767BCB386DF81F8ULL, 0x263408F58A1C2926ULL, 
            0xDF7E2713857DF6A2ULL, 0x2FB81A0B0310ACB4ULL, 0x2135795EB5B7D724ULL, 0xB2591351A80D5569ULL, 
            0x1408552FBCD16A6EULL, 0xFD11CC755C0F0DBEULL, 0x49189A29882F9CFDULL, 0x272CEE092062E845ULL, 
            0x96F86D7B2DFD925BULL, 0xCECADAD699AE5FFFULL, 0xF0BA0E0A1859E85EULL, 0x03BD9E298D304201ULL, 
            0x784D4C342B6B88A5ULL, 0xBA77491D1AF71D11ULL, 0x550D8A29E392C65BULL, 0x0341544DB67D1A48ULL, 
            0x8A45B1ABE0A286BBULL, 0x558FDF4D459BA697ULL, 0xC523E20835AB70C2ULL, 0x37B1846612A4717CULL, 
            0x767C866D4BB174D8ULL, 0x51344AD35618E183ULL, 0x60100A525CA00E66ULL, 0x6F1A36C25BEB7D66ULL, 
            0x7DCDD210E441A4EAULL, 0xD46C97A3E2FE5525ULL, 0x6B51BBF8741B48C6ULL, 0xA684118EAE1BCE95ULL
        },
        {
            0x5601B896CC82893FULL, 0x993D991958AA43A8ULL, 0xFC5337054E54DC08ULL, 0x6A879B2439ECB578ULL, 
            0x229A5BF1BECB3674ULL, 0x860ADAC80142D03AULL, 0xC3ED2BDE1DEA8175ULL, 0x65E9B7D42CE6078BULL, 
            0x61F4F2BB4F9D6022ULL, 0xA02D9CFAA0E366C4ULL, 0xE8B48DA0E8537606ULL, 0x29BE1E6F9D1207A5ULL, 
            0x181D77368CEA033FULL, 0x6FCE09BD8FE028FCULL, 0x36EFDC6C88DD288FULL, 0x87102DA85150BE62ULL, 
            0xD74229DEEA7586A0ULL, 0x393D713459E192E1ULL, 0x3DDE9DDCC7A5BFD1ULL, 0xBB394E7B9B928E5BULL, 
            0x33F696C24FC1D599ULL, 0x3947110BC2A1446EULL, 0xFE1F7A7F51DD566FULL, 0x2C8A6C2E17BEA99FULL, 
            0x0B690462E14DF316ULL, 0x09E082E2CA59C514ULL, 0x5A944E40E94A3748ULL, 0x70C49F22D9462EE7ULL, 
            0x9788EAC33143CB98ULL, 0x4A4E7845FF6B9C8CULL, 0x8ECE4837D5BEA935ULL, 0x961410F763B38730ULL
        },
        {
            0x1A24D674DC61947DULL, 0x0704790CF6616FDAULL, 0x41DB2CA444473D0AULL, 0xFF7A1C7183C9D6EBULL, 
            0x1500BCCB65319149ULL, 0x17977837A508A266ULL, 0x248072CE71768DFDULL, 0x57A92C6C05817EE5ULL, 
            0xA552DFDDC520D1E9ULL, 0xC875118E7BDB197AULL, 0x09485C7EFD0AD833ULL, 0x1CE9F0E55655EE6AULL, 
            0x2DFB64E7786493A5ULL, 0x2EC814C40E4DAFACULL, 0x7CD32B6913897FF4ULL, 0x2755EEE109F580A2ULL, 
            0xF9309AEE641AAF56ULL, 0xC220A0278C0EC6A6ULL, 0xB76DDD0929EE4C12ULL, 0xE0ADC98E5C3C7F82ULL, 
            0x0E0324E11029FD5AULL, 0x8D617A684135A91AULL, 0x7219C47E01C7A4EAULL, 0x6587F9676AF4407BULL, 
            0xB9331212A46ACB1BULL, 0xF7D3682CD5104BE6ULL, 0x9ED179F910FCF188ULL, 0x9C3E40B5614897C6ULL, 
            0x129C16042B0EDF9FULL, 0x2D460296CC58B555ULL, 0x8A49FDB6901EE74CULL, 0x05D4E380B37550B7ULL
        },
        {
            0x437380A9FE91E8CCULL, 0x8DD6C47D34374E13ULL, 0x596EF44C3B5FB073ULL, 0x9419726886DE3121ULL, 
            0x78BC004D04B10CBEULL, 0xF95B62FD5FDE48D2ULL, 0x83E1141ECAAB21C4ULL, 0x6F3481C34B8B8F1BULL, 
            0x620E3BE129593616ULL, 0x8BBE25DC49EFA90DULL, 0xEB7E7D64B2574D12ULL, 0xC29B0CA7303B70B3ULL, 
            0x7648573DE6F68BD1ULL, 0x975581339F2C0B44ULL, 0x2F7D2F1E5BD93752ULL, 0x393FBFD68B9F8D76ULL, 
            0xBE061722FC643796ULL, 0xA2FAF63C3E9CA13FULL, 0x31165E316BCC068DULL, 0xFFC97B2A133176D0ULL, 
            0x477A4EFF190DEE8EULL, 0xA9FD3861D68A8139ULL, 0x729BD4D8B89B4CA0ULL, 0x1CDFEC68C3CA04F5ULL, 
            0x0FF2FAD92DFD78F4ULL, 0x623E4ECF5DF037D2ULL, 0x7C7D41E214512F14ULL, 0xEBE5180F4E92BE71ULL, 
            0xAF984FA210A0B83AULL, 0xBB98CEC074FDBA62ULL, 0x443155301C7EE264ULL, 0x64B5F9936340A55AULL
        }
    },
    {
        {
            0x0484815659C87E86ULL, 0x71DBC7E08D2F855CULL, 0x554DF7899540F07FULL, 0xA9EEAB5AC79BA926ULL, 
            0xB859560AF6196551ULL, 0x369C1CC8E060AAC9ULL, 0x23A2C743E24B9280ULL, 0x9E5A7B4427971850ULL, 
            0x3F5E9FF10D316389ULL, 0xFCB735CD2006F2B3ULL, 0x678ACC3623D341BEULL, 0xE04262C9BE4BC325ULL, 
            0xD25CC28235B635D7ULL, 0xAFA119789A336215ULL, 0x84358A4726776D0EULL, 0x95123E5CDE57C885ULL, 
            0x04C6702535F71E28ULL, 0xEECC2CD1B41C6BF4ULL, 0x79F5FA328449CA41ULL, 0x5DEA8C3D1BB86F59ULL, 
            0x51BDFD9C8BD3F93BULL, 0xF37E4F4500527E0EULL, 0x387E5F255C297754ULL, 0x4921AA0024D33D0CULL, 
            0xAEB6A70B5641219BULL, 0xF6AABDCF057EB6E5ULL, 0xE1DA446F4D8F1EF4ULL, 0x30EBC82F6848EDDBULL, 
            0xE13123D6461143D3ULL, 0x1053A95E0CB4A918ULL, 0x0E00FADBA83FE0A9ULL, 0x2D2846664D01758AULL
        },
        {
            0xE03EC36BABB33F28ULL, 0xA6E124FDC8ADDEF8ULL, 0x59CA587DE9DF4644ULL, 0xA382E06E4EFBDF9BULL, 
            0x34A5F0854615B9A5ULL, 0xF6A428FCF8CAB188ULL, 0x1783BDBCCEF630B7ULL, 0x90FD6133890C93C6ULL, 
            0x6E5A5E440CDD0741ULL, 0x968A5E360EA37056ULL, 0x333EAA91D4BF2EB1ULL, 0xDB047386714E74EAULL, 
            0x03A4617A3F541A3BULL, 0x4F14391CAE4275DCULL, 0x0811A0152E1A491EULL, 0x56E46F2B701A5DC3ULL, 
            0x3CEAC0F2A3BF094BULL, 0x62227C7BEF5B1F55ULL, 0x77E9643D3F0936CAULL, 0x59BAC9FF5941E084ULL, 
            0x34849DEA1CDF36B8ULL, 0xF013E1C61F34BEE0ULL, 0xC68E7E6C3E22461FULL, 0xFC82CE079C19640CULL, 
            0x8E137133BD4A15A9ULL, 0x9F1605F4E0E43EB5ULL, 0x9F372B8FA371122AULL, 0x5B8AA507EC3C572CULL, 
            0x7167A66C4A8EF451ULL, 0x5D7CF126B5FB0EF4ULL, 0x09DD7DA38CE2A796ULL, 0x57C51B90A89EDA74ULL
        },
        {
            0xE82200BF0CCD0661ULL, 0xE22CBAF5C01512EFULL, 0x5D7C20588F49D658ULL, 0xF07D82780379D01FULL, 
            0xF7DBAC441261C9FEULL, 0xFFAC20B70A57E2CEULL, 0x56C98A4880185BD0ULL, 0xA92091F4BCAA2A38ULL, 
            0xA6288E61C0FB32E1ULL, 0x4551D5337F6680A7ULL, 0x7763D56C5D6D21C1ULL, 0x8500CF46DF1EF91FULL, 
            0xCA9E96F354EEAE16ULL, 0xBD16926F65597DF1ULL, 0x4B943D5470DA459EULL, 0x1D4B07DA33524538ULL, 
            0x9B363C66B1F3FE1AULL, 0x9DEE30DC631976EDULL, 0x8EE11F095C8EED7CULL, 0xB45BA22809012E3AULL, 
            0x65F2CBAD4EA74A0CULL, 0x924C4B186EF429F2ULL, 0x7423974D5F97456AULL, 0xB2BC3BF8CCCCE44DULL, 
            0xC059E951A588FBFEULL, 0x97E9EF38D9C099ABULL, 0x6239C43D94620483ULL, 0x4F4C6E60714D265BULL, 
            0x1751E50E5A72A55EULL, 0xB66343FDEE8EEB12ULL, 0xF3DF80672E44CD00ULL, 0x1C3CE761D2889C4EULL
        },
        {
            0x8452ABECF4E2D49CULL, 0x9DC4C4E56B9060D8ULL, 0x013ECC5F326A9C15ULL, 0x0CCA6B21BB2DD8BEULL, 
            0x4120B0FE8CD36BD0ULL, 0x82B8516E4386E05DULL, 0xAAEE2DD265C5D366ULL, 0xF6C6AFD18AE1BA17ULL, 
            0xE54BA67AD156D3D1ULL, 0x632B095CF19FFE19ULL, 0xD70AE840C679C015ULL, 0x494FA6476D3D15D8ULL, 
            0x7248D1768DBF2AFCULL, 0xF038A4F6FBB6525FULL, 0x8B668A46A8903AB9ULL, 0x48BAE1B840B6B59CULL, 
            0xDE6D12D5C583EF58ULL, 0xA76006E70D776C3FULL, 0x03D3F0E1452C63A6ULL, 0x7F25CCFE9EB2CD2DULL, 
            0xC132B7CD094F9FA3ULL, 0x4EF96AB58D59B181ULL, 0xEA20E341E6D013E0ULL, 0xC8584525EA9FD196ULL, 
            0x61A2CC805F2640CFULL, 0x0150F677F8440992ULL, 0x41BC5C4A733C5859ULL, 0x232B1838EF151CEAULL, 
            0x721A993DB2F6911EULL, 0x6B922600B62785A4ULL, 0x0D5478A3FB830AB9ULL, 0xBD70BBD0577C3166ULL
        },
        {
            0x746A4CD0D05B1BF3ULL, 0x1DD36325C516559CULL, 0xA0FA157096B4FDE5ULL, 0xC15D73A4FAF450FDULL, 
            0xB376DF6DAA96CD3FULL, 0x188686367EA94DECULL, 0x5557FBD8AF5046D8ULL, 0x58F5958D3EF9CDD5ULL, 
            0x6C7D746A7E5A0B29ULL, 0x6E477F08692B450CULL, 0x3E65ACBBF749D5F6ULL, 0x039D6E7621308B2AULL, 
            0x37DAB7D1E5FA8A06ULL, 0x01358F1BCBE8320EULL, 0x92E3FBBCA4C10850ULL, 0xD846F74747996E31ULL, 
            0x4A0EB960494FF467ULL, 0xF2C9BB7F3BDC3099ULL, 0x401E5714BF50030BULL, 0x3D35398A6A5EBCB6ULL, 
            0x3D3172E665A62BFBULL, 0x9DF5FC062FDA53FCULL, 0x89A38C915B1CAD30ULL, 0x6877F0F938C9A8E1ULL, 
            0x6B0B8B2F28018369ULL, 0x88D43E6C3668FB35ULL, 0x457EE56859BE119FULL, 0x2AD38251A44C58C5ULL, 
            0x4837042E9DAA525EULL, 0xA71BFD4A4704C499ULL, 0x036C84D90C036862ULL, 0x08E1603F32BD3EBCULL
        },
        {
            0x571374A152B2E2F9ULL, 0xCA9AE85CE2F441A0ULL, 0xA1707B99CEFE4DE2ULL, 0xD5D6591C7004BB89ULL, 
            0x8F0B559FEE949FE5ULL, 0xC42340E682D078B1ULL, 0x96F4294FFE4EDA54ULL, 0xDADD2EFE8FA2C6AEULL, 
            0x7798B56DF85CF356ULL, 0x540973D380A4AB33ULL, 0x818BC26425445B37ULL, 0x9CE87AEC411F47A6ULL, 
            0x5CA30F1A2EAB26F8ULL, 0xA0675409CACE1905ULL, 0xE9C9EDAA3CB0F20AULL, 0x306398EAB3260A76ULL, 
            0x2807EE9BA052152EULL, 0xDD2EB10EA4308173ULL, 0x3852302A2A4CE41BULL, 0xA9E94A163CFC7F7EULL, 
            0x80A395D46BF88936ULL, 0x213E8945E8BDBF83ULL, 0x2450E970C3B99F13ULL, 0x52EF614E8C16D03FULL, 
            0xEC11DAA30196AB31ULL, 0xA66A823C6BC2009FULL, 0xA44E61A718F47EB4ULL, 0x0D1CEE370105FAA0ULL, 
            0xC14079FAD65C4CC1ULL, 0x611226E4D16D794BULL, 0x0489F4DD49A47CE0ULL, 0xD5B280201D490C3EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseCConstants = {
    0xBB6D08EC075C68BFULL,
    0xEB2F9A43A1558BB6ULL,
    0x94D5129F5F9B722EULL,
    0xBB6D08EC075C68BFULL,
    0xEB2F9A43A1558BB6ULL,
    0x94D5129F5F9B722EULL,
    0xD32DB72ABB8EEC87ULL,
    0x2A1FBE35582D8CCCULL,
    0x3B,
    0x4E,
    0xBC,
    0x87,
    0xE6,
    0x39,
    0x2F,
    0x9E
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseDSalts = {
    {
        {
            0x4AB96403145406B2ULL, 0xE87799176B738365ULL, 0xAEDC51AF7E1EF731ULL, 0xF849BC2F9D99FCBCULL, 
            0xF63F8E65BFB3E87AULL, 0xF7BABF31925655A3ULL, 0xB001911D0E853BF1ULL, 0x7AAE4793AC67C2C3ULL, 
            0xA69610FDE4E8CB65ULL, 0x2AA89E08F7527CE2ULL, 0xA71579DD033B8386ULL, 0xF12A64398118B3BAULL, 
            0x8C9F6DE6F96D8950ULL, 0x5C0DFC79FC13F8C7ULL, 0x6808F9E79960290DULL, 0x6D7E8F5D7B522E32ULL, 
            0x7D3833DB413EC1D5ULL, 0x514626DB5055E09AULL, 0xE7E4D6CF90A2993CULL, 0xD44E5E7B854575ABULL, 
            0x994F915B7B015410ULL, 0x38C2C631A0878EC8ULL, 0xD8F5D612AAA59393ULL, 0x20D927DF5AEE1A03ULL, 
            0xB4834D031C5ABF9EULL, 0x5EA6D0B196D49F55ULL, 0x7CC7EBCC2186CAE7ULL, 0x47BAFBCB9D5F68A0ULL, 
            0xABA6CA49436D41E8ULL, 0x725B47D476CE8F5AULL, 0x5977DD712EE88C5CULL, 0xA199C7E06AB1D535ULL
        },
        {
            0x19DC64A03152584AULL, 0x6E732996CC05631FULL, 0xA621F8D90D3F46E5ULL, 0xFCE2E44DAE378D35ULL, 
            0x83E02D2FEBC26E0CULL, 0x5BBB8344107E1AE7ULL, 0x37074383ACBEE02FULL, 0xE3D3E6938ABE9C1CULL, 
            0xAC811881387EDF94ULL, 0xB55CE70578D63CD3ULL, 0xF72F0D2A3343B84EULL, 0xFDD9167F447DA8D3ULL, 
            0x988A1B52C87945CCULL, 0xFC57785E4B1706BCULL, 0x2FAB7724130B4125ULL, 0x99D760C5AC8C7399ULL, 
            0x8898F6529E5C6198ULL, 0x83BE4D1F24B74C36ULL, 0xB5517E903471DF84ULL, 0x661CDC62FC8AC0A9ULL, 
            0x029260DCA83B6A18ULL, 0xB0FBFFAA423BD1CBULL, 0xA96FA9C547305ADBULL, 0x3F8461C7703864ABULL, 
            0x71B02AFFC3D9F4BEULL, 0xD85D2221CECDA63FULL, 0xA793B89ADC8F7FC6ULL, 0x47F3F99D1E6045D4ULL, 
            0x53CDEB0333650BD0ULL, 0x3D6AAAE5D56260EFULL, 0x4980C91C39FD8DD4ULL, 0xCF8313956D20A79AULL
        },
        {
            0xAD8B04103DB742A2ULL, 0x6914C69DE4F13078ULL, 0x577E8820685C172BULL, 0x215271ACC1352D7FULL, 
            0x97B3A6D9DB5DB630ULL, 0x2DC89A34C5908DC3ULL, 0xA902160F1D119DC4ULL, 0xBEB5115490858BDCULL, 
            0x2749141A21728904ULL, 0x880E5114D281245BULL, 0x6A356F748F3B0903ULL, 0x0081744839FC12DFULL, 
            0x38C206A6C05A6389ULL, 0xFA52BE3BEEE0078CULL, 0x8C9763F3012B735AULL, 0xE2F240710033FA1DULL, 
            0x03B55F1911EEC0F8ULL, 0xFB698E9004E8D38CULL, 0x56C147BF6E36AA41ULL, 0x646395FDF787FB11ULL, 
            0xC6E39DECBB8B9CA9ULL, 0x2A3060EE1A237106ULL, 0xEAF20F8B3FDBFBD8ULL, 0x914091423F48935BULL, 
            0x833C15760B9B2E99ULL, 0x1F8D0FC541565A19ULL, 0xFD63BD1A51D428A6ULL, 0x151831F33697E954ULL, 
            0x2DDA3694068F7EF7ULL, 0xF6DA90C3CB2FB5A7ULL, 0x7A57651AD95C5451ULL, 0x694F947C29F7E6C0ULL
        },
        {
            0x2F76DB84F1453E55ULL, 0x6B14D9667EB6D744ULL, 0x60196BF982E0786EULL, 0xEFB6A96F62EA58ADULL, 
            0x72A57F13E5E851E1ULL, 0x1BB5A5138E905C51ULL, 0xBB75918C0741A131ULL, 0xEDCBCD7A8697D421ULL, 
            0xD7ECFB44CCDD56C8ULL, 0x3B060B5F21BE5FE9ULL, 0x7F62404860EB0137ULL, 0xD02DA227FB58DC5AULL, 
            0xFC5A94BA797DE77AULL, 0x7DB13C052172EC1EULL, 0x6167DA065D98FFC9ULL, 0x294DE42404DFC676ULL, 
            0x0D2EE2D060BEC6D1ULL, 0x6A6117F58C83E1CBULL, 0x4CA204A8A01C8083ULL, 0xF43FDAA3099A45E3ULL, 
            0x8FB9FDC33FC563ABULL, 0xA613615F74E984FEULL, 0xB9BD767DDE0D62A3ULL, 0xF5ED648D554D54C2ULL, 
            0x15F2B9A82087A1B1ULL, 0x5AACAF73C90D8E33ULL, 0x4BC4C25169468DB3ULL, 0xC6D198AC157E3B7DULL, 
            0x3F9C201B7FF21CC5ULL, 0x4B71E6E3696003C6ULL, 0x6CF4FC11EB30FB76ULL, 0xDCB3C844F1E29BB9ULL
        },
        {
            0xE89BAA02F9B5EEFAULL, 0x879A5AFAA79F5267ULL, 0xA3B99D5FF98E8E03ULL, 0x09D6BBFD82738DBCULL, 
            0xC56BA52A71BCEDA9ULL, 0x18984E198E8FD18CULL, 0xF2D9C44A5B3474D2ULL, 0x3D3606C449D3067FULL, 
            0xB3CCB2377F33693EULL, 0x9F15313073877394ULL, 0x71B5DCE45AD9EBB6ULL, 0x8BCFCFC049644AC1ULL, 
            0x6D4A5AB0CC51763BULL, 0xBCC2FDFCC5E524A5ULL, 0x5518E499B2D19315ULL, 0xF25707230C21F6E9ULL, 
            0x7A93558E1E6B9207ULL, 0xA77AC1179C3107C5ULL, 0xC4BDB5AEA04A762CULL, 0xE1A3AC6BC6F1B823ULL, 
            0x805C5A912E89B477ULL, 0x9C9D8425659D5AB3ULL, 0x73B12D5E8D838DDCULL, 0x9FDEAEC39E90B717ULL, 
            0x827CE41C0900BB41ULL, 0x921C9BFA7A05EDABULL, 0x131C10D39CCE7226ULL, 0xB150F1BBCB5EF47AULL, 
            0x6703AC0189C5C41DULL, 0xF23CE96794EDD977ULL, 0x1936B63CD8C13D70ULL, 0x4529241E61B538BAULL
        },
        {
            0x0389669AE4A25CD8ULL, 0x3703B49431EF77F4ULL, 0xDBFB35FA55831995ULL, 0x108EECA7597BA00BULL, 
            0x2C08B2B309F142E5ULL, 0x5B6E76764A86FC91ULL, 0xFD78867259DBD743ULL, 0x4E1DC96D13DD1347ULL, 
            0xA364E37436A99948ULL, 0xFE389B991F8A5AD0ULL, 0x943F7183992655D2ULL, 0x2BC81BA6CC2DC7A1ULL, 
            0x89566E5942B553F7ULL, 0x0C001A718A70B923ULL, 0xF53601CF7270B87BULL, 0x5BDE4F2D0AAEE400ULL, 
            0xE3A0C270DFEBDF42ULL, 0x95E2E20A0740FDAFULL, 0xFEAD66875C1B70E3ULL, 0x323F8B2B8BA91AC8ULL, 
            0xE48A34F4D1F4A18EULL, 0xB993424DF4913B78ULL, 0xB2D2754887141C52ULL, 0xED54DAD85BBAD842ULL, 
            0x4478A27C66E00504ULL, 0x1EEF6B4428BA2C92ULL, 0xAA66A710E220CAAAULL, 0x5272AE972E720F28ULL, 
            0x2D85370160B2384BULL, 0x46B9E9D49EE65C99ULL, 0x9E7297270517B22FULL, 0xA6109AD91B084F4EULL
        }
    },
    {
        {
            0xF5E7B393963382F4ULL, 0x09D245AE4892BC27ULL, 0x57D1C6011AA96244ULL, 0x06540FD3C4F81637ULL, 
            0xC0B0171D2554E1F4ULL, 0xBD532D1B2A132F48ULL, 0x0C94BC01AA0689A5ULL, 0x86F7D0EF8374030BULL, 
            0xFC308923C17D23C8ULL, 0xCD084261C80BF978ULL, 0x3A7FDFB8C129D9C3ULL, 0xCB5E93338A3D2386ULL, 
            0xD7BAFCB6E52C090BULL, 0xD9075547289515BCULL, 0x192E92873D0792C3ULL, 0x5A1C1204EF217C94ULL, 
            0xFDB7CAEC0FAAF478ULL, 0x38107C90CD1921A5ULL, 0xE4F33FE4A68E505DULL, 0x38CFC4E9640C43A3ULL, 
            0x81A17B132A18AAC6ULL, 0xA50F68AE463B37C0ULL, 0x37871CA396184CDDULL, 0xCE1B6574952CC0CAULL, 
            0x17C593D0C81993D8ULL, 0xAF9CE73CDDCEA859ULL, 0x8CB98DC44682EE67ULL, 0x14B7A2D21676232FULL, 
            0xD4347380E1A2BD94ULL, 0xFF5F9FDD97110F86ULL, 0xB0BC115DA9A1D2C9ULL, 0xE2DB304294644050ULL
        },
        {
            0x06E2642DF803F5BCULL, 0xE55C0CAE6FBD6AADULL, 0xAF6E8F1DB1A5360DULL, 0x7EA9AD61324744AAULL, 
            0x8A1755B8FFAF30F2ULL, 0x80415E28142205E4ULL, 0x83B693F99E93DDF5ULL, 0xAD5BA57E4B36B4DDULL, 
            0xCD69836B19BC9DB9ULL, 0xF2BCB0A378A04A58ULL, 0xA0151E90A80BB4D1ULL, 0xF80BBC8A228C58B1ULL, 
            0xD6A9626F530B11A5ULL, 0x29893112409C1DF1ULL, 0xE6B37D69E40E26FFULL, 0x1A3403DAAA1D7F75ULL, 
            0xC0A7298F6947AA65ULL, 0x00E2CBEBB53C0104ULL, 0x445257154524C1D7ULL, 0x917303225203A0A0ULL, 
            0xE0C3AB9C2B54E42AULL, 0x8D2FB494F94B49C3ULL, 0x257D5BFEDAE632DAULL, 0x9AC8B045ACF5246BULL, 
            0x8AE342D6B694CA50ULL, 0x6B907D82A1E4922CULL, 0x391027D04A8F679FULL, 0x30EECCEFE057ADA9ULL, 
            0x31AD80F80CBADB9FULL, 0x5AC381B9B265DFA8ULL, 0x424F2235CABCB220ULL, 0x13486AFE215C3981ULL
        },
        {
            0x68BCD379CB426100ULL, 0x0DE1A6CC655E9BA7ULL, 0x4EA15A9757591ACCULL, 0xCBF84C05CCD50008ULL, 
            0x209063B7A1E36C8DULL, 0x186B16693923D434ULL, 0x9FB66B848F82FCF1ULL, 0x70559C3F3C98E82CULL, 
            0xFD1555C1A30C3BE1ULL, 0x225B37B51C6BC15FULL, 0x7BC9D31828845A97ULL, 0x4C8A6A8F5FAF9049ULL, 
            0x3634DFAB24375967ULL, 0x4EE2D0CD97FA4E61ULL, 0xD80AE31A2E9305E1ULL, 0x8592A33559493F8DULL, 
            0x465DD8DBBF18F689ULL, 0xB9765339DFD92B63ULL, 0x74A5F7786A4CA98BULL, 0x492DE8F679C72857ULL, 
            0xB9FCA267661D7D1AULL, 0x2B2DCC81F2A38CB6ULL, 0x501E84E850C430C5ULL, 0xAF040BFA60D0A25FULL, 
            0x981645E55D1F03B8ULL, 0x5A769B9A26E5F744ULL, 0x15640D724E83FE1FULL, 0xDD4A9CB0825D2967ULL, 
            0x279483E0D5819921ULL, 0xF758E6AEC3FD3AC8ULL, 0x90DD285000D34289ULL, 0x9BB9DE4AB84D2BAFULL
        },
        {
            0xA037641C307235DCULL, 0x0480C61B7AE0FC0FULL, 0xA55E927497FFCDBAULL, 0x2C60844292A94A55ULL, 
            0x4B769F6F007CF835ULL, 0x395DE617CED19747ULL, 0x7183840FC8917D8EULL, 0x6A445DEEFC8D4198ULL, 
            0x1A61D002618DE198ULL, 0x540B713DC3369521ULL, 0xE755BDDA3C882EA5ULL, 0x09935995987C372BULL, 
            0x6B0E30719AEF58E9ULL, 0x94DD19B3A453902CULL, 0x5068362120041C55ULL, 0xECCB177DB4FA15B7ULL, 
            0x7835BE06CB1446F8ULL, 0xE744BB6611EDF371ULL, 0x0A93D845692FFA53ULL, 0xB152CDFFFF3AB779ULL, 
            0xA7BEECDB3146E2BFULL, 0xFD60F424D7AC79FFULL, 0xF1D0D7D74F3ECF5FULL, 0x319189E5091D447FULL, 
            0xE1B3CC4880DB9989ULL, 0x7529DE50932F3A6BULL, 0xF67101A627996424ULL, 0xC768208FEDD49ECFULL, 
            0x3D970C56EEB0F01BULL, 0x07372F7BFF256693ULL, 0x20F35CC4E5E06B1FULL, 0xE787B46F4A3F71EDULL
        },
        {
            0x816222E128CD00DDULL, 0xE20DA2B52222D72CULL, 0xC27B830CFBA2C32FULL, 0xA5055C070AB6B434ULL, 
            0xDB170AC2FE69DE96ULL, 0xF282DF53F7C23BC3ULL, 0xCEB1A1EBFBBFDBE4ULL, 0x275D76E951D26611ULL, 
            0x963226D8E06A78B7ULL, 0xDBD65566DBF341D3ULL, 0x7846A1D7BB21E201ULL, 0xF3D3DB8808E347C4ULL, 
            0x5D50AE10CB8A38CFULL, 0xBE9B36D4C1656862ULL, 0xCBB5F8BDA8FC444CULL, 0x7521B05CEB18016AULL, 
            0x6AD70045DA70815EULL, 0xD84432B189ED145EULL, 0x66DAB560005A3835ULL, 0x0A4A57F6F280045AULL, 
            0x96C0462720ABBD10ULL, 0xA02FCCD0EDB229C3ULL, 0xA2808CB1702531C6ULL, 0xD354C56FD6649B52ULL, 
            0xBB590D6BFEBEB7B3ULL, 0xAEAA984CB223E8B6ULL, 0x1DAB03514742D369ULL, 0xD496DDB335A09C9BULL, 
            0xADB84327997C0D1EULL, 0x37D3F1DCDCB9DB1EULL, 0xDDCB3B0F5D7C57A5ULL, 0x97FF5325F2B7274BULL
        },
        {
            0xAC285F4DB78C2344ULL, 0x028B08AD5ED5A654ULL, 0xB69DFAD7CB07F95AULL, 0x37E4E856069E33C1ULL, 
            0xA6A8850719A45142ULL, 0x799AB005450D1517ULL, 0x84AF16DFCF9B72E3ULL, 0x20E7D19A91395E01ULL, 
            0x3664E187BBF614C7ULL, 0xAD9453F8504B9F5CULL, 0xDB1F29405B44B215ULL, 0x58A10250DBED69FDULL, 
            0xFBC5C3A366184C6AULL, 0x1DF16D8D31A1C67AULL, 0x2B5C8DD596CF79FAULL, 0x2F37760327900C9FULL, 
            0x957160844C8B41A9ULL, 0x4DBD32C61D8501E0ULL, 0x517B49CB79A1B8A8ULL, 0xB994E0B6EDD7F553ULL, 
            0xD816A02C722BDF3DULL, 0x91B90FF7BD6DDE2AULL, 0x1EF3E1BBC2E500FEULL, 0x925DF6A922DB174DULL, 
            0x8D81FAB5776A88CCULL, 0x609C20EBFFD3B57CULL, 0x6039CC9FD63B70A3ULL, 0x416355297E4B9B91ULL, 
            0x5F5E0EE0CA1D76FDULL, 0x4E385154333CFB28ULL, 0x1C6B029B5F83D184ULL, 0x2A61D96B0FD7B254ULL
        }
    },
    {
        {
            0xF583D715E159CE09ULL, 0xB6A5E71CBA78F612ULL, 0x1E4ED7440ECDBCF7ULL, 0xC5B71473EAF45454ULL, 
            0x4014F9B18177115BULL, 0x3CDFC460BC21A24AULL, 0x2E1528580D2E35D2ULL, 0xD8A4FF7EDF008D55ULL, 
            0xFE209DA301638D18ULL, 0x2D7AD69B4B5B15EAULL, 0xE5ECCA1909BEB605ULL, 0xA5A3EE3EFE9EEA33ULL, 
            0xB79929B3869BC547ULL, 0xEA9E4D5D406837BFULL, 0x8EBA15DF7D203392ULL, 0x2DB4226D4B88E679ULL, 
            0xCC6C266664C1B202ULL, 0xA5C701AB49FF26B9ULL, 0xCB91E20F9093D778ULL, 0xEBED042F5FB00CFEULL, 
            0x165CD4C671852C31ULL, 0x25057E710B7C2E5EULL, 0x5F486B219EEF1468ULL, 0xBE1C6119922CB175ULL, 
            0x3B8BC903E4457342ULL, 0x0DD3E2F5CECA14BFULL, 0xB30B914F3E8E601AULL, 0xEF9F200B658AE927ULL, 
            0xA2855A7889A12F0CULL, 0x336EE93FF6FD6E2DULL, 0xFD1238A576373C4DULL, 0xA379FD95133BB4E5ULL
        },
        {
            0xEA6C7AB1A70CD954ULL, 0x86EC6F9F2FAC2CE3ULL, 0xC8EDFCA86C52A14DULL, 0x1FC1E2CCD150E3D7ULL, 
            0x727DFDF169CBDA71ULL, 0xA1B81EC68B2BA7E7ULL, 0x18D241DEBB0020EEULL, 0x0DA65033208B5473ULL, 
            0x17E734E70299AF05ULL, 0xBF826730D5225ADAULL, 0xE96FE20A5DA7C0F9ULL, 0xA1B5D7648416CBECULL, 
            0xA8E098E16640744FULL, 0xD98E871BBA295375ULL, 0xAE53771D0D2FD085ULL, 0xCC77C8614B321380ULL, 
            0x9AC2D6AE30277D7BULL, 0xA87B2D3D4A167186ULL, 0xE85BAE0FF0E66C41ULL, 0x70C7CE47C7FAA77AULL, 
            0x0C482790B0DEE52BULL, 0x82940C4651F759A7ULL, 0x61828243DD95105BULL, 0x7EA0C3B4AA4E956DULL, 
            0x26149C7588A48528ULL, 0x3273363B367E4442ULL, 0xF280AAAF82578955ULL, 0x845E9E4DD1D42BFCULL, 
            0x1CB6A9BE26D1E1FAULL, 0x43C94C33B9AC5227ULL, 0x666A538805AE9B07ULL, 0x9480F899E9D07A5DULL
        },
        {
            0xF6D1C8CD0AFF1177ULL, 0x917F067B7C17AEEEULL, 0x4DB9895B2F05EA68ULL, 0x3A7F68F9A6EA7C54ULL, 
            0x474B839447912DDFULL, 0xD691C0D47C87521AULL, 0xB2BF81A10C8B2F85ULL, 0xB1838B13262FCF7AULL, 
            0x4E426A72D2B5DD13ULL, 0xAC7E77AD73BFEEBBULL, 0x2C3195D28BB0C1DCULL, 0x7737B035716E2D8AULL, 
            0xD6547B725902D492ULL, 0x287700CA93420FD2ULL, 0x67F6DFB38DBCD5E4ULL, 0x3F3C958A91A8D59CULL, 
            0x6751765D79D0246EULL, 0x6A82BAB64C196D04ULL, 0x40E386808F6412ABULL, 0x7599D83C7D13D4A3ULL, 
            0x46979BF466A4B400ULL, 0xC3370E6AE58678EFULL, 0xBE1DF22BDF713C7CULL, 0xCBC481D287C1124DULL, 
            0x7DAF8079A2E23B2CULL, 0x69AA38A2E806A99AULL, 0x0BA0866843DC38A1ULL, 0x25FB2B0295E1EB3CULL, 
            0x4C89CD09FFF0D889ULL, 0x449FAE3163074C76ULL, 0xB446D1BC790FD7E8ULL, 0xFF35DA7215CA5439ULL
        },
        {
            0x676EB9D5B91F816FULL, 0xF6334A5A8CFDC185ULL, 0x6C6202AE9B6F4B1FULL, 0x744FDBDF2D336E0DULL, 
            0xADD8BDF768B293F8ULL, 0xF4A7162A775222F0ULL, 0x423F27250C9AD8E0ULL, 0x9E9C83E6342D3440ULL, 
            0xF84DB05518D38B49ULL, 0x76369F05EB07161BULL, 0xA288D58EDE6ED80CULL, 0x1E5BC1AA78E2360BULL, 
            0x4A58657FCD9D79A5ULL, 0x21A9A9D328533C38ULL, 0xFCE82C4A6543C8B4ULL, 0x53E8EF03BF89CF1AULL, 
            0x42B42F0E60E45E4EULL, 0x0576BED5A4FDB72BULL, 0x0078E04BA678BA70ULL, 0x12662310E29163C6ULL, 
            0x2A2CADA775B0F723ULL, 0x688491F1D3A98965ULL, 0x01E2DA3D1A291882ULL, 0xF63412E8198631C4ULL, 
            0x402D6A7104613059ULL, 0xAEC53A9257620272ULL, 0x901A72520A72B463ULL, 0xC17B6CA9DB8024ECULL, 
            0x31521C9CCC7406B2ULL, 0xA24E0CF14D280A92ULL, 0x5EE226248B21F35AULL, 0x751D19D01671EFAFULL
        },
        {
            0x268D861E833CF7ADULL, 0xA523F6FE91A70565ULL, 0xBC287BF72807F733ULL, 0x39017D54875C7271ULL, 
            0x6BA86C2561964A57ULL, 0x9CC0CC79CF4CE85FULL, 0x17DD2D03164440A2ULL, 0xD48195609F3E2EB1ULL, 
            0x76C071D925E93FB2ULL, 0x7D2945246698EE0EULL, 0x11344DA7F30A5C2FULL, 0x4CE4687C68CBB2FAULL, 
            0xB4C22DC8C82EE2E8ULL, 0x13E89FF05E5D6E1AULL, 0x19E856650D1C2208ULL, 0xF3C3C9AC2BC22DD3ULL, 
            0xA65674B14934E230ULL, 0x6188E1678F9145ADULL, 0x60F11F4F35016C3AULL, 0x16F67A553ACE5121ULL, 
            0x5EB7F183C638E829ULL, 0xAA76CE968C717358ULL, 0x6F339D6E83D007FBULL, 0x61E115AD6ACCC43BULL, 
            0x70D0D40CFBDE47CAULL, 0x73CAD315E785E6A8ULL, 0x4DEE5B7538B43907ULL, 0xD5AD508A748EBCF1ULL, 
            0xA53C68C9C020A096ULL, 0x10D2F120E81F3A00ULL, 0xADACA98AB5E1ECE9ULL, 0xBA02BADF994D27A6ULL
        },
        {
            0x973D244CD428A5B6ULL, 0x6E12D2F4FDD2209DULL, 0x881A6663742D30D5ULL, 0x02777A756A449073ULL, 
            0xB55196D4EF809092ULL, 0x5AA1586C4C567FC9ULL, 0xC0C64ECC0346048AULL, 0x1AF1F413CA429EB3ULL, 
            0xD2B88CC25E3262BAULL, 0xDDD817E752389A94ULL, 0xE94E677EE8185A5CULL, 0xC486800171B53DABULL, 
            0xA75319E1D649909CULL, 0x747DE44A2DF0B03AULL, 0xEBCB32BCE2E7618BULL, 0xADEAAB08E63F0874ULL, 
            0x045CE56A601181F3ULL, 0x186C935DBE3D9D1BULL, 0xA3E5C346AE026BB0ULL, 0x60B9C3DA87BD79F7ULL, 
            0x3A73C7F0B40C499FULL, 0x1305CC25536CAA9EULL, 0x5E1B2BF64088C4E5ULL, 0x552D84BECC4ECD28ULL, 
            0x86D2C730DEF2B453ULL, 0x77A670FA5FBA9A59ULL, 0xF770DC3A19404204ULL, 0x9299051A18DDDA10ULL, 
            0x96A31607EC39EE87ULL, 0x2677F8DB82A0E33DULL, 0x803F5384DF06D220ULL, 0xD58A4717A216CE34ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseDConstants = {
    0xFC3E93BC418ED3DEULL,
    0x0E116E460957072DULL,
    0xA7F5C5D9CDFB649EULL,
    0xFC3E93BC418ED3DEULL,
    0x0E116E460957072DULL,
    0xA7F5C5D9CDFB649EULL,
    0xA2EC13565998BDF7ULL,
    0xAD7107A8364717B5ULL,
    0xE3,
    0xBD,
    0x0B,
    0x7C,
    0x1C,
    0x31,
    0xD5,
    0xFE
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseESalts = {
    {
        {
            0x227436809D25D6A2ULL, 0xA81DEB6A210A742EULL, 0xE61AE01DFC5D72BFULL, 0xB351FAE291ADED33ULL, 
            0xF8EF91FC89D44ED7ULL, 0xB71133CF6BFA7EEBULL, 0xD4AC516AE64DFD76ULL, 0x702941C6DF9A8809ULL, 
            0xDB71E9AF241119C7ULL, 0xB72E759076183E72ULL, 0xFFB1A2933DAEDCE4ULL, 0x65E471B33C932558ULL, 
            0xFEEE1F1A64010F26ULL, 0xD9AFF0B721790242ULL, 0xF0AE0A56252EA873ULL, 0xC914C1556F281E3AULL, 
            0xFEB8DAD17AAE9A1FULL, 0x14567CC1A538759AULL, 0x6F837776A6E6CAA7ULL, 0x609BCBADB0C33EA9ULL, 
            0x6B9BF0F2D6955691ULL, 0xA54640A3E98CF267ULL, 0x6C77C49D6DEDE8F6ULL, 0xFE9D70ECCCA935BDULL, 
            0x560346C28FA30BA2ULL, 0xA8940B3301B18A6DULL, 0xF2226C4EAF481756ULL, 0x9CF64096328E69A6ULL, 
            0xEF3463E9C91D3CA0ULL, 0x5E84BF1BC33CFC46ULL, 0x0F646419071D385EULL, 0x15A04FD87B4B4173ULL
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
            0x7F131EB1F39E982BULL, 0x4A0E929A4B4A4E78ULL, 0xEA221B36BFEEFAA8ULL, 0xAF67195067A98464ULL, 
            0x3CA99F968D0D1898ULL, 0xBFA6C7D59CEC6BFBULL, 0x43EDEFA133FCE855ULL, 0xB770354C4738F1C6ULL, 
            0x14772C9770547788ULL, 0xA4491249D74E151AULL, 0xFC16954973516DC9ULL, 0x6A99DF4B5441B830ULL, 
            0xEB8FBE9778E6725AULL, 0x8011983B884BF7ECULL, 0x7AD1B395F4C64B88ULL, 0x5E087658263A4495ULL, 
            0x7A13138B4F963DF9ULL, 0x22648AB9FAB4A17BULL, 0x6B77CCFE0B1A4A7AULL, 0xC5B51B3149ADC99AULL, 
            0x025FB2C56C3B9F29ULL, 0x0287548C158CB38AULL, 0x82E0236C8D118580ULL, 0xB1F5ABB9CB8DA3E8ULL, 
            0x48BCD05D3271AFC9ULL, 0x8BE2DC63129AE4C5ULL, 0x38CCC8400F09EEC8ULL, 0x414BFFA69732DFB7ULL, 
            0xF8BF626845203C50ULL, 0x7B67CEFAEDDB5678ULL, 0xF5597C0EC072FE0DULL, 0xCADA81BF2723EDEFULL
        },
        {
            0xCE28D558F55E0045ULL, 0xBF2F5FB6C6F43E54ULL, 0x638891FA3700FCD4ULL, 0x3606AB7E9416B77FULL, 
            0x25CCD4A6F3CF0C65ULL, 0xC50FD17E227B8A09ULL, 0xE418C6FF3FC86B15ULL, 0x0E2AEF2B3CB71166ULL, 
            0xCE09B78D7AB29157ULL, 0x32803C2C0B464D83ULL, 0xDD5F8AC1C91C9D6CULL, 0xF49044BA7BD6C4A3ULL, 
            0xB944A93CC8DB1374ULL, 0x50314DD0C0637792ULL, 0x606D48EC7E524580ULL, 0x6BA8785B4A42007CULL, 
            0x0A6A55F4D1073FF0ULL, 0x2B9C082BB420BB3DULL, 0xE00C74511593B1FDULL, 0x6F2B19B532579A40ULL, 
            0x1A2D3B4CB10C95D9ULL, 0x5B56B896D5ADA157ULL, 0x75E5A275D4C8386EULL, 0xAA66B44CE179D678ULL, 
            0x11DD75CCC9800DFBULL, 0x685B12966960BF49ULL, 0x123BE086B0032507ULL, 0xD5F0CDE374FBDF64ULL, 
            0x51E1C9E008756201ULL, 0x985D7CBCEA80C718ULL, 0x621091BD556E9F44ULL, 0x2702076202ECE07DULL
        },
        {
            0x2BC4FD8B3145FD57ULL, 0x3A43691CB24ABE7DULL, 0x21ABF0F4AD359896ULL, 0x1A91F7C256A243C5ULL, 
            0x59143DE2F4859647ULL, 0x5D33B48541B221CAULL, 0xF7456688E314763DULL, 0x042DE66445939232ULL, 
            0x118056807F995C91ULL, 0xD13D8C1C32F6F112ULL, 0x469E8FA387EB6C09ULL, 0x396A4F88F8695526ULL, 
            0xDB42E9F67F1572D3ULL, 0x1B6E254448B91030ULL, 0xF63891A968B88F43ULL, 0xC46F3EB302AE8118ULL, 
            0x56A79DC638BD25FAULL, 0x53335B7456B4FB83ULL, 0x95E160DDFC31573BULL, 0x4221B5A68B4253B9ULL, 
            0x46BCCCFFFBA7E568ULL, 0x7EC9F75DD62BAD7CULL, 0xF10456E3B97A583AULL, 0xA6C8BB4D870D56F0ULL, 
            0x5F15301B2A590E15ULL, 0xC9F7C859C2D2C7A1ULL, 0x5FD478F876F586E1ULL, 0xE495AAD218799D8AULL, 
            0xDC61A9F829AD16CEULL, 0x280532FB8F7A9AD8ULL, 0x5E75AB502BA2CCFAULL, 0x698DA4BA767523B6ULL
        },
        {
            0x1E478E2FAA10B521ULL, 0x9E2DBA8E6A263098ULL, 0x280A674E11F30F70ULL, 0x1C9C482968A18152ULL, 
            0x5558F888CE8751E8ULL, 0xB9AAF3459F0818EEULL, 0x164BF51BEA7F7312ULL, 0xE27A1719F9EF2A32ULL, 
            0xB3B0200FE9E95FF0ULL, 0x73239A0FECDB7116ULL, 0xCA13AB197968A890ULL, 0x67A8D763B66AC555ULL, 
            0x7E5642EF7737C185ULL, 0x4AB57C222ED72EC5ULL, 0x78A51ADFDCFA1392ULL, 0xCCD8EDE4A67B2966ULL, 
            0x2FB2328E0931EBC1ULL, 0xBDC14EB3DAA295C7ULL, 0x25A0F8D82D5543EEULL, 0xD12FECE5205271C1ULL, 
            0x4FFAE90E082A7117ULL, 0x85E6E18B80CBA371ULL, 0x910EED59BC779E3EULL, 0xB12D6BDEE4394964ULL, 
            0x7551F28ACD359D72ULL, 0xD5846CE0750A1F0FULL, 0x2AF993D4A279EB8FULL, 0xA0759F39B3EBFD1AULL, 
            0x3CB226946AC3DB3CULL, 0xE59FF30CC353A207ULL, 0xB02DE02C21D9AE6AULL, 0x457CB5B6BC9E2762ULL
        }
    },
    {
        {
            0xAC034180B774F422ULL, 0x04FF7AF06E00AB01ULL, 0xCB98A6374A7EDB81ULL, 0x0E3C95A2B6675483ULL, 
            0xDBB00D67AD775A39ULL, 0x4E462F673E644DAAULL, 0x0F7651E0C08F8B21ULL, 0x443B5DEF8398EE09ULL, 
            0x2A97C45D02FD9409ULL, 0xE04077D60517C39AULL, 0xB5C7061D15C8EAD2ULL, 0x23D14ACB493356E8ULL, 
            0xBEF8B746F0791649ULL, 0xC7D734E32ED8EB4DULL, 0x0D7655A53E722074ULL, 0xDD82F5B114979FBAULL, 
            0xF46C4C1D7E55EE0BULL, 0x3FAFC51DCBED586BULL, 0xEDB8851B2AC996F4ULL, 0x90E6DFB85B4E6D4DULL, 
            0xD4C75D6AC14002E9ULL, 0x1BE1BA9C104E47DFULL, 0x815AAEEA046B6E85ULL, 0x1E05D71E180F994CULL, 
            0xF64E60E77412CFE0ULL, 0xFA7DE816284E9A74ULL, 0xFE3DF9ADD27F3B52ULL, 0xBE86FCB0E4F98916ULL, 
            0x7F7A2D198EEC3F7CULL, 0xDF982F5B87FE6488ULL, 0x654C6204C14DCF21ULL, 0xEA96306825B3006BULL
        },
        {
            0xC3B76DE136A61B56ULL, 0x8CC9DD59AEF1B82DULL, 0xA5FDFDFED7CD23D2ULL, 0x03323F373949C682ULL, 
            0x41287570D3574AE2ULL, 0x6122F15EEC475AEEULL, 0x659DF57B157398D8ULL, 0x60EF5F7027851149ULL, 
            0xDE3E99DBBBFAFB90ULL, 0x732BC9C3C4EFB2ABULL, 0xEEB0BB3072D7CA6DULL, 0x3D4637147E19B297ULL, 
            0xBB93566D7C3AF703ULL, 0xFD0DBEF238EA03E8ULL, 0x815CCE265E218203ULL, 0x53735482B689BF1FULL, 
            0xA1FC0EBA5924FD16ULL, 0x73F78953BED0732CULL, 0x3D933D8F28B17B6DULL, 0x66CB2676D5E29734ULL, 
            0x0AEAF9B5E03AF02AULL, 0xE6C2C98B3EC7CC40ULL, 0xCDF470BA66311F54ULL, 0x3EA4873F2753518EULL, 
            0xBB1EDED19DDDC875ULL, 0xE14DAD6E219E03E6ULL, 0x3D748C524F33D07AULL, 0x8A2817C71626F3F4ULL, 
            0x0AA1DCF62E1BAF9CULL, 0x82913FAD0B392905ULL, 0xB740AAAACFA60A85ULL, 0x5360E5C38047C4C5ULL
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
            0xBC6ABB92993C5CB0ULL, 0x29252AA263F90175ULL, 0xBF33A9DD6350D8F8ULL, 0x638C19F375BF41FEULL, 
            0x6123876F29C39569ULL, 0x1C741BD26250C242ULL, 0x581AADCCCB565CACULL, 0x9FAD1113F87E6077ULL, 
            0x03F43DC3A6420EFDULL, 0xCD660BB7F6BDF824ULL, 0xAF213C3AAA680369ULL, 0x28DAF32ACDF34216ULL, 
            0xAD385863FE0D7188ULL, 0x755CC85BE850851AULL, 0x58AB95317DD14C0DULL, 0x8BBE004B4A2DA7F7ULL, 
            0x9D2F9BF80B573756ULL, 0x703A65AE455722B0ULL, 0x432C1AD228E416E8ULL, 0x1DC67DCE218D5B10ULL, 
            0x7B21AC62FAFD8E61ULL, 0x131C977563E9B766ULL, 0x670983A5F6904631ULL, 0x5032080FA7C1F3BAULL, 
            0x22B3F95292EC5214ULL, 0x723E65386B198FE9ULL, 0x0CCA5BFA8AEC770CULL, 0x940F524F7F2C3A36ULL, 
            0xC2400066D055B421ULL, 0x7D2638B22EFCDAF5ULL, 0x8266121CDD845A0EULL, 0x4D3E85797187121AULL
        },
        {
            0xC2CD205AFD839369ULL, 0x2CBF233604983D4CULL, 0x5CC5279E8457EFF6ULL, 0x579567F76314E13BULL, 
            0x554411447E0DFC9CULL, 0x94AD72DE558D1EABULL, 0xCADC52767089D083ULL, 0xE7D3025DF6611D18ULL, 
            0xC5D08631116E8F8AULL, 0xAD718299CFADD72DULL, 0x0E91C7F4FB63EDDFULL, 0x39C0FB1FF132F959ULL, 
            0xC42115F85B06689BULL, 0xF034C3854F64BFCEULL, 0x79AC1734D116289AULL, 0x67DC1A8C008FBBE3ULL, 
            0x1EC5793703DD3DD5ULL, 0xF608D18448A82EF7ULL, 0x729FFF928712F3D2ULL, 0x7AE9E745C3C3FD2CULL, 
            0x5142D2E93BB5FB0CULL, 0x143C77BCFCFA1147ULL, 0x93F7BE8AEC49662AULL, 0x197D8913FFC79830ULL, 
            0x6A84D30F46ADEB5CULL, 0xE2831FCC6328E92BULL, 0xC65EFC208F93C170ULL, 0xFD78FF84ED861A23ULL, 
            0xB530D315C52FDAFDULL, 0xECEF433C31000D2DULL, 0x94FC37DD5427F160ULL, 0xF349F451069A71ADULL
        },
        {
            0x850F4E394FE3E915ULL, 0xCFFDF0A1F8406A48ULL, 0x23FB232CFBFDB641ULL, 0x5591531C876B6247ULL, 
            0xF3C9296E25A4AE85ULL, 0x3387AA9C51FED7AFULL, 0xDFCB1137FA90611AULL, 0x1FBC940EDDE1EB41ULL, 
            0xA6C8F6368CE13E3EULL, 0xB2FCD148CF03B940ULL, 0x7D0D44670A4AABAAULL, 0x780511CCF54AB083ULL, 
            0xFA95D1821E4E7F3CULL, 0xB77FD0C34B122F87ULL, 0x483E786BB5EED28DULL, 0x117D72E4181CDAE0ULL, 
            0x48E7DC12159FFECBULL, 0xD97722B8DDB82037ULL, 0x8520C5CC7DC96E8BULL, 0xA98386F7A760D2D8ULL, 
            0x1B3106A3A9C25BF9ULL, 0x22AD1D8CACBF590BULL, 0xFD50706132FD5424ULL, 0x93F621885024D358ULL, 
            0x502116F6E3603546ULL, 0x3F7145051EED0ACEULL, 0x9C19E464948BE9E6ULL, 0x06D4B6F3BA81EB61ULL, 
            0x1F19E91583F9DCC6ULL, 0x5D0FFEDCB9C87C32ULL, 0xED0A58DEC2AE0E8EULL, 0x79C11FC8972D28DEULL
        }
    },
    {
        {
            0xD1D02E287F8EFB97ULL, 0xB5A24258485C8DF3ULL, 0x4853803DA10BCC12ULL, 0x237A8C1B55886E3DULL, 
            0x38555910CC03B705ULL, 0x3E68F59847A0F173ULL, 0xCF84A1BA788DF479ULL, 0x73A3E88D89DAF72DULL, 
            0xC6F19BD6C2AEE0C7ULL, 0x25BB9A2E8AC82819ULL, 0xE810C20A4B98321AULL, 0xF6A3C33059193551ULL, 
            0xF937B77625F11DD2ULL, 0x13886674A7530650ULL, 0xD621DC65D77295FFULL, 0x5A71A8AA7CC1D6C2ULL, 
            0x6C04D0811EEE21A6ULL, 0xF7AA7CF06C8FA8A2ULL, 0x5941AC649C6EA4AFULL, 0x745C63D4C8634884ULL, 
            0x70D9564581F285CDULL, 0x057160658FFA8DD8ULL, 0x325A47215212FFE6ULL, 0xE172BB5EB0791FD9ULL, 
            0x3E9BB7E316657134ULL, 0x4705384D9D36BF72ULL, 0x23C5A9DC545E05F6ULL, 0x0AD845953CFD3BD9ULL, 
            0xF5E35503EF10E82CULL, 0x01A7E2535A7F2030ULL, 0x036BECE29AF24E70ULL, 0xBB55DA8C4537E321ULL
        },
        {
            0xD03AA989689FEA62ULL, 0x32092C1E764B2475ULL, 0xD3663772740D4A61ULL, 0x82A97329DE9DB0C8ULL, 
            0xEF0418CEFA609273ULL, 0xD6AAB9AF512B325EULL, 0x9C0A6354DC792951ULL, 0x7CBDBB97B5C41B5EULL, 
            0x75C1A0FA763A6105ULL, 0x544BE21C974410F1ULL, 0x918EE9ACCC948FDAULL, 0x8A7A95D2DC624CF5ULL, 
            0xD0D8C538600DEEADULL, 0x2D1DDAA97B748126ULL, 0x8BB5B702C6AC278DULL, 0xFF19A14A69EECC27ULL, 
            0x49C2C44E70F4985DULL, 0x4C513036D61FFE82ULL, 0x6186FE82BE77968CULL, 0x842FE0FB0EF969E1ULL, 
            0x7D04796AAFB1DC9EULL, 0xB8027F55CBB1472FULL, 0x4FA369FDF9B3FF92ULL, 0x0B0192411C96BA17ULL, 
            0xC065D5A66A51C1B0ULL, 0x1D38289E9987BA62ULL, 0x52F25E5DA5B89254ULL, 0xAFBAF25C2D40E978ULL, 
            0xF88393A4AF0094ECULL, 0x154ADC8E1B07636DULL, 0xF34A7049A4610753ULL, 0x9B4F466E154B11BEULL
        },
        {
            0xA586C38C144E0932ULL, 0x0FD2CBECB9877CC9ULL, 0xDC47B5194342EBA8ULL, 0xF56188AA532D4AC3ULL, 
            0x33647DE2355AF5AAULL, 0x7EDC735FA9F192D8ULL, 0x1385AB9AE19BEEF7ULL, 0xB430ED0BED518D8FULL, 
            0xF1853EC1506B1C0AULL, 0xC611580D06B5740FULL, 0x2B233729B275D4B4ULL, 0xBF3EBEFAE756EE4EULL, 
            0xC951FF35CF26249FULL, 0x41E90EF31A8BC8E9ULL, 0x1B4E135E7913F0C0ULL, 0xB8594994C1EFC54BULL, 
            0x9D68D835E3F3DBA6ULL, 0x9A24236BDD97A320ULL, 0xEED5ECCE1FE7DE8BULL, 0x6DF2F581D0C9EA65ULL, 
            0x8B621C15897D303AULL, 0x8A0C215360FB993DULL, 0x96D0F3A351AF9790ULL, 0x060DF75DA753A5C3ULL, 
            0xC81285CF4F91FC90ULL, 0xC9D84C60A4785DCFULL, 0x947594D6517DDA88ULL, 0x3383445BF315CAFEULL, 
            0x05ADB2981A549FB9ULL, 0xC122EFFF279570B6ULL, 0xED72E22806023C4AULL, 0xDEA1D64AA3B68E81ULL
        },
        {
            0xEEFE35DBAFB946AAULL, 0xC98FBD94A684659AULL, 0x6AF77A5B1EA0D325ULL, 0x73F3855F9CA1C222ULL, 
            0x68037BC97BC64715ULL, 0xC06FE29EC745A470ULL, 0x806A93AD09D24D26ULL, 0x0C2018688B87D7C9ULL, 
            0xEB4A89A740B0ECF1ULL, 0x1F2812EB8FB73BC6ULL, 0x653EA7E50E893503ULL, 0x1D2D10D0C0B98ED4ULL, 
            0x7D2004C62B12A66CULL, 0xDE2B555F56FDD6DFULL, 0x9C858BB087D3E136ULL, 0xDA50D1602E7A89FFULL, 
            0x9702E528FEF37B2AULL, 0xF09FA056A448FCDAULL, 0x0335DF33B57A48C0ULL, 0x71D96E0A8C09B7D0ULL, 
            0x240D50319B7BECC0ULL, 0x0F49F736B60D4796ULL, 0x17D4D1EDE189F83BULL, 0xFB9B07869E7C4438ULL, 
            0x3B7D81B1B2CE25B7ULL, 0x3BEF6B3CF34CF7D0ULL, 0x271442B8452DD1F7ULL, 0x9AFBBADCB1C17B04ULL, 
            0x7C581BF58C319B3CULL, 0x2CAFF7DC07B7A31CULL, 0x6A5E158B211C6573ULL, 0xD5B59123AA4195E3ULL
        },
        {
            0x75F8988476D1BC71ULL, 0x46492CF2C147D126ULL, 0x241D10ABCD349F21ULL, 0xB925012E5FB36BA8ULL, 
            0x69C1013F8B195F9CULL, 0x1C643DC64C355243ULL, 0x9861BF5DEEDE5BE2ULL, 0xBB1381F79C1680FDULL, 
            0x145406177FF6C0E1ULL, 0x7E50E2873FD597DAULL, 0x3EBFA09D19B74F44ULL, 0x29D0246AC5805BF2ULL, 
            0x00B1CD0BAEA01F99ULL, 0xC2A23798B91DBE65ULL, 0x351B17D39140EEEDULL, 0x3D6B92697EA4E169ULL, 
            0xDF5D09E135B633ADULL, 0xF1654F3842EE28B9ULL, 0x839DEC250F34ABE2ULL, 0x4BFCA49FCF95D4BDULL, 
            0x3E8E857F27CA20BFULL, 0xF150C3DE62AE44E3ULL, 0x9F491B29BCB7EAC9ULL, 0x33B07498BAC4D53AULL, 
            0x63E0A70672C3F26DULL, 0x89027C9FC8086F5DULL, 0xCC1384D08DB8ED43ULL, 0x3685CB962E14F98DULL, 
            0x29BA3FCAA573BF2DULL, 0x200925D88BC4909AULL, 0xBA609BFA288CDC36ULL, 0xC2014EE60C0515A3ULL
        },
        {
            0x0D78694D6349E8CDULL, 0x31114C232FF61460ULL, 0xDB9597723878AD34ULL, 0x3F37586FD8620E6FULL, 
            0xB6435F75D9CEF581ULL, 0x810E9EFD9B7D8463ULL, 0x0D405FFB7F17034AULL, 0x13CFCA61C6669FB6ULL, 
            0x4FC20980D29DA1E4ULL, 0xE7FF64F96C79CBF2ULL, 0xABC813F65153B89AULL, 0x3A92B7A510F3878DULL, 
            0x18B83A83FA16A3BEULL, 0xFA9E950A351E067DULL, 0x84ABD1D055CCE465ULL, 0xDA65EC5F5D76CD33ULL, 
            0x4B66D81ECB365F24ULL, 0x469A8CDB1DAC3FF5ULL, 0xFD51988528179E0DULL, 0xDF04DEBDF1722AF7ULL, 
            0x365BA43735243745ULL, 0x0886B384DB7AA662ULL, 0x5CD6261A03A15974ULL, 0x07DB9A25743925DAULL, 
            0xA0581B04E2ED812CULL, 0xAC52699476E5E4FFULL, 0x805B42938E8DCD20ULL, 0x7FF3FB004CC25F28ULL, 
            0x3D14BA3593CFB3A4ULL, 0xB36FCD909375E435ULL, 0xF7F8153E65D32CF3ULL, 0x96145C4650EC9173ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseEConstants = {
    0xAE73F8C239092CBAULL,
    0x23CCC400ABFE6810ULL,
    0x25E568B520F7098BULL,
    0xAE73F8C239092CBAULL,
    0x23CCC400ABFE6810ULL,
    0x25E568B520F7098BULL,
    0x017425D9FBCA7CAFULL,
    0x281BD3478721CF4AULL,
    0xCF,
    0xDE,
    0x6E,
    0xDD,
    0xA9,
    0x30,
    0x05,
    0xB3
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseFSalts = {
    {
        {
            0xE4048393224277B6ULL, 0x1BC50821001C0857ULL, 0xA7A4C99392EC6BD6ULL, 0x570B792BE47275CEULL, 
            0xE0028B2A42AD3E5FULL, 0x586A294261E852EAULL, 0xE6ECAB3B01C9EEE4ULL, 0x6697E1D227F39968ULL, 
            0xDDA06236951AFCDBULL, 0x827F88BBFFA95A5DULL, 0x62BF539783A70D34ULL, 0x7A845BB7549485B4ULL, 
            0xFBC96D1AD9A724B1ULL, 0xBECF1398C5D352C2ULL, 0xD98412170F681BD4ULL, 0x3A08B20B7667CE8EULL, 
            0x5A60173B92D88047ULL, 0x59ADA1161A7F1634ULL, 0xCACFA98F660C3F9BULL, 0x8CD249759FBF7CAAULL, 
            0xCB0158F7E5634217ULL, 0x5D4AF8573AAF20BCULL, 0x3761DD8568016437ULL, 0x29E30D91CE122F1CULL, 
            0x5A198F9D9180ECD9ULL, 0x11105E5E1D323CFCULL, 0x9D5B4B388E6A7673ULL, 0x20F691F4F073E9ABULL, 
            0x2A9CB6CB2F0625B3ULL, 0xBBE25FD075843950ULL, 0xF2B8346A33534898ULL, 0x739A1601BD087F97ULL
        },
        {
            0xE0869600C38EF02DULL, 0xE2F4B0E8411BDF22ULL, 0xF75185EBE957FD20ULL, 0x4278FF3C5BC6DCEAULL, 
            0x9FCE46BC3C84ABD6ULL, 0xE0CA42A025098E90ULL, 0x6A9BEB845EFCA8A8ULL, 0x5839036357E96261ULL, 
            0xABC11F547E8B1D9EULL, 0xCBE4830D1B25F93CULL, 0x0163B02F61377634ULL, 0x4F39247202DD1B2EULL, 
            0xB6D22C7C0B4D9701ULL, 0x332E25CC8F02C996ULL, 0xED2163C28E3EE143ULL, 0x17DE9AFF7D1D857CULL, 
            0xA9EA3D1960087EBEULL, 0xCC6C6CC90AF250F5ULL, 0x849C34711FDA0813ULL, 0x4FFAAB1161A3604DULL, 
            0x41EB5F35DFDB5FD3ULL, 0xA47F67A77E211225ULL, 0x3CAFD4C0339C0601ULL, 0xE9DBBA8BB7A134E0ULL, 
            0x66EA34CAE78075DEULL, 0xC999CD67780FBDDDULL, 0x164F4BD399F611EDULL, 0xA49A329730A71C4EULL, 
            0xC1C85FA2B1F4467CULL, 0xFA14F13586842B63ULL, 0x2154F43284E1DC4AULL, 0xCD28E8BFF0611ED6ULL
        },
        {
            0xEAEF625ABFCAD709ULL, 0x477BDFB51263DAD4ULL, 0xA3CD186B4E99A437ULL, 0x7D8FC0C9466FB210ULL, 
            0x3912D9CEAD5A0320ULL, 0xC6E374891067C551ULL, 0x4B264A57F71A89C3ULL, 0x14E4ED767F1DDC66ULL, 
            0x9678F1F3F044EA06ULL, 0x51EF32017D39AA2BULL, 0x9D671CDED5858640ULL, 0xC1B28A1E422584F1ULL, 
            0xCA990714CFD2C4D8ULL, 0x518784ABC6952EDAULL, 0x0B25C5E4762BA015ULL, 0x7624C4ED183339C0ULL, 
            0xF417FDBC577DB7C0ULL, 0x8DB4AE2DAC57F45DULL, 0x453E58F4CFC8EBADULL, 0x28ED083C7995D7B1ULL, 
            0xFE7DBCF18BD10719ULL, 0xA722624D590A11ABULL, 0x9767C8CBA9E26CB8ULL, 0xC477BBA1C5A74AA2ULL, 
            0xD3F173EE41E1A908ULL, 0xB093C7419B0C7679ULL, 0xAD59FB86C6656362ULL, 0x9D4DFA11B6A50BA3ULL, 
            0x91BC9B74807CEE64ULL, 0x99AE19BE6517D978ULL, 0x342A48431A417F6AULL, 0xB4D443ABAE46DFC7ULL
        },
        {
            0xDB70725EFBBD4B37ULL, 0x190534E6CED53854ULL, 0xA0D001C6BA71C6E4ULL, 0x6A1B7D005E4E42B3ULL, 
            0x08A0C662B4A38547ULL, 0x855D1F3ACE7DA462ULL, 0x388A6BBDC6D01E12ULL, 0xF85AA9FFCCEDD633ULL, 
            0xC9F8ED280E9F409EULL, 0x331D63596AFA766EULL, 0x5A74E1BA02AFE0A2ULL, 0x833F0891D788B7E3ULL, 
            0xB4D2A5ABD13D9D34ULL, 0xD220302D8960813DULL, 0x106222E38B9CDFEAULL, 0x7A1AD80DBA7BBE7FULL, 
            0x9E57AE003E633A22ULL, 0xA0681495D00E4B74ULL, 0xFA6958F86656483BULL, 0x6D11D646124E7897ULL, 
            0xA7A571CDAFAB81D1ULL, 0xC896D75753B8C4E0ULL, 0xA318B84F562AEF75ULL, 0xA744608373AF8504ULL, 
            0x9BA7A2B74CAF552FULL, 0x24D163655E1532F6ULL, 0xCD542B2A8A35CE27ULL, 0x93047C7183DF2458ULL, 
            0x8DB10C119FD7616DULL, 0x5827E20175E3A280ULL, 0x1FF572EDA7E5F47AULL, 0x3733BBE6E4CDE715ULL
        },
        {
            0x9C921E9A5FF788AAULL, 0x16915AC9FC1CD546ULL, 0xF441D4B1A972CB4DULL, 0x7DB6B34E687E6F42ULL, 
            0xD575027E5F2DD005ULL, 0x13044D8D1BD5C595ULL, 0x4E49F2B95E7024ECULL, 0xB3B0B3593B586DA4ULL, 
            0x3B1E003FCE6DE0A8ULL, 0xBF77A309EB1D8373ULL, 0xBD8E24C1EBDE006EULL, 0x5B56C1EAC361D10BULL, 
            0x06247E82821C6781ULL, 0xAEF2DA5746246526ULL, 0x80E410F7CB3D88BBULL, 0x2704EF4A308DF864ULL, 
            0x2E183C6B21F1FEEFULL, 0x8170FC45DCFBDD8CULL, 0x37867662CB0195B4ULL, 0x37A010B57323900EULL, 
            0x3024AE414BD45F67ULL, 0x44DD90B7F41E55D8ULL, 0x187D8EC3E31584F2ULL, 0x51D345E69806919FULL, 
            0xEA2E551038D712ACULL, 0x5B86532CA3D7B07DULL, 0x03E7534FDC93047CULL, 0x0E5725F6A1FE9A9FULL, 
            0x07E9212426279392ULL, 0xEFA2546F0141DCD3ULL, 0x5D0E26DB7F115913ULL, 0xD6279DF69C5E2493ULL
        },
        {
            0xCBC0820C98FC2F2FULL, 0x44FEFA9A8680CA1CULL, 0x56922AB028C7DE20ULL, 0xE3F29B7BB2330273ULL, 
            0xB5984A4CF03AABE5ULL, 0xD48E0C6CFF8742C1ULL, 0x721B38A6830BB870ULL, 0xC83D8837C319AEF9ULL, 
            0xD1085BF6EBB88193ULL, 0x362F89EC896BDC68ULL, 0x2ABA5C6A9C4BE7ACULL, 0xA8F3356747BD55AAULL, 
            0x0D784F58F663EF04ULL, 0xA205DC5E398834A0ULL, 0x4777C489BAB6DDF6ULL, 0x830B5F5FAB6ABA7DULL, 
            0xBD797C70F7EFE332ULL, 0x273DE9C6DC967D59ULL, 0x29D5424867A7BB16ULL, 0xFB4EB27E892DCD56ULL, 
            0xD0CCA65B5758FDB4ULL, 0x1A0573F372695E64ULL, 0xEA3CCDC159DB6D2CULL, 0x16AC2B075B5B2F23ULL, 
            0x3D8C1D7DC31F02A9ULL, 0x14718356EAA8C332ULL, 0x1B6C1D722EE1758CULL, 0x75554356C332B78FULL, 
            0x2E8400DF09A4679FULL, 0x19CBFA3E1C81E629ULL, 0xEBD4530560020F5EULL, 0xF4B523744E2863B6ULL
        }
    },
    {
        {
            0x67E72FC4D19051B0ULL, 0xA571033DDB1E23E1ULL, 0x8FA8902666CF6460ULL, 0xB79D460CF8A1F68AULL, 
            0x6C27B58F56386E49ULL, 0x5FE285C85BEB1869ULL, 0x1857207EAA44D567ULL, 0x752F061053570A66ULL, 
            0x9FB68321F0AD0B56ULL, 0xEE1D984B714AEF5CULL, 0xB297B0453C0CD79EULL, 0x47A69EC382B847DEULL, 
            0xE01134A0EBAB556BULL, 0x244033C8B8FFBD54ULL, 0x5A7F04FD871D644DULL, 0x3C73480430727179ULL, 
            0x489232106C11677CULL, 0x4B6E641DFE7B2FE3ULL, 0x6D21EE8607FC9987ULL, 0xEC953F28A11815BDULL, 
            0x7A925C996BD4D846ULL, 0x7C586242B86EE6E3ULL, 0xD6A79A5A8D69756FULL, 0xCB0162243794D82FULL, 
            0x3A805703426363FBULL, 0xF31ACAA4289EC3ADULL, 0x7185843998323FF1ULL, 0xED25AE514C95E10DULL, 
            0x238229D6F1D2F7F5ULL, 0x7AB0DDE8AE323B54ULL, 0x3090F20C07200DCFULL, 0x43CEBC02560FE35DULL
        },
        {
            0xF22F452F7969EEB8ULL, 0x9A822DB50EB7E00AULL, 0xAE695055145266C0ULL, 0x6E4A14DE9EDE4EEBULL, 
            0x021322D089A617F5ULL, 0x665CEC25483E0E01ULL, 0xD84B5D604B8D21EFULL, 0xF8C287524D8981E8ULL, 
            0xA1ED55D92014DF60ULL, 0x51C8BCA7F6842E96ULL, 0x32D01622C80CDBB1ULL, 0x29D9D40681679FB1ULL, 
            0x3FEACF363A17EAA0ULL, 0x71225A9C02380317ULL, 0xC20D7E727C1C1C7EULL, 0x0518A5C79C4C9F10ULL, 
            0x34206DE93DEDDDDBULL, 0x4955DA2624FE819AULL, 0xF399A438A5566721ULL, 0x0E5333DB6751B9AEULL, 
            0xF0A3CF048E15D775ULL, 0x38488C0D687C7F2CULL, 0x418775B76D7FE514ULL, 0x0ABB0A3A5CA7C8A7ULL, 
            0x2CD1B972B1574A25ULL, 0xD0BB5429C031C77CULL, 0x59AE4A5903791E24ULL, 0xE9AC247A3BB09EF2ULL, 
            0x5C7975C58DE6B755ULL, 0x640346BD7BF79BDEULL, 0x5BDC207AF14B4711ULL, 0xF191E24647652C6EULL
        },
        {
            0xBB46692BAFCA719EULL, 0xE4F5B3B16E70C7EBULL, 0xD175B84857DB8341ULL, 0xC14499F82E5C3F6DULL, 
            0x098277EFD1340952ULL, 0x3826CDA0A9F17980ULL, 0x292C05C03F667334ULL, 0x259136F7710818DAULL, 
            0xDF98CA5A2ECA6BC2ULL, 0x7683C43C9031D89FULL, 0xF959FC4C65A144D2ULL, 0xB712109804B1D991ULL, 
            0xC0AB0EEA9024A737ULL, 0x914607B884C151C3ULL, 0x8569B8877B9F7D7AULL, 0x82B1770941245A2CULL, 
            0x8DBC29EE2B492F50ULL, 0x0164B27377B19167ULL, 0x044DEC7F093F4629ULL, 0xACC5C99AA07540A2ULL, 
            0x1851629F277E67DCULL, 0x8484237C13EF0050ULL, 0x072AB007C4687111ULL, 0x5AE52CC981C2D736ULL, 
            0xEEE18EDE2850EF13ULL, 0xA03608A7750C4B8AULL, 0xA7A8CB866B648096ULL, 0xAE1C36377C16D88DULL, 
            0xCFFDF3AD2610C465ULL, 0x795AB2E56C002D24ULL, 0xCAFF1E291E06AAA5ULL, 0xA7447F3CBF3C336EULL
        },
        {
            0x0BD3BA76B8459BAAULL, 0x5913339C75F52769ULL, 0x11E721B5A76DDAD6ULL, 0xC94099BA276EEB3DULL, 
            0x0F1ADC2AE416C1EAULL, 0x5B99C076B3EC3E80ULL, 0x09C6E0137CA02C18ULL, 0xE044D7420089A577ULL, 
            0xD4B8215593759086ULL, 0x736C1FF7A822BBAEULL, 0x89C4CC90B28B9338ULL, 0x8B94CEC8B071C828ULL, 
            0x6B935FF756CF7F8BULL, 0x9BE3AFFF693D5AEDULL, 0xEEC6FDC4B718F843ULL, 0xB334FD8ECA9D2A0FULL, 
            0x13D7AC52DFB5CCAAULL, 0xB04B8D862B602970ULL, 0x11C609D38D264594ULL, 0x01FD926DF0B724B0ULL, 
            0x980126C3ACF9B90BULL, 0x784EA1C55DF900D4ULL, 0xB8ADA599621972D4ULL, 0x2A549134E83B4384ULL, 
            0xFB5C3EDB3954CD2BULL, 0xF9DAB20DF62F4EB1ULL, 0x1A2F2FBF6205BF80ULL, 0x963B97638E152B1CULL, 
            0x2FE76B4F18747C9DULL, 0x49A1E105AC292EE6ULL, 0x05CFE4449A1C26F8ULL, 0x85BF6C1E7E244B76ULL
        },
        {
            0xC9F1DCB8AE3AF134ULL, 0x2D3AC88E2B17809AULL, 0x49906938ECCEEC56ULL, 0xBBC1D08C6D44FBBAULL, 
            0x6D966B66076AA068ULL, 0x70867D849A4A6936ULL, 0x97D2782C61258585ULL, 0x6538C10BFF190032ULL, 
            0xF6D662058347F64CULL, 0xD22FD9CC77058CE8ULL, 0xDDB4773B86FE6C33ULL, 0x7976BF7B5233244DULL, 
            0x44EE02C4F77C9A4DULL, 0xCB713EBA4EECD372ULL, 0xA06C2C8136D6FCC1ULL, 0x64B8054F99FD5D8FULL, 
            0x0B706EB6F9BA465CULL, 0x2B4683673DD9B799ULL, 0xA673F87E35F69575ULL, 0x7DADDC6CE2FDE37AULL, 
            0xCB2927148A40279AULL, 0xF0C8666BADDEAC32ULL, 0x4EA2A6C4CFA5A7F6ULL, 0x194715536E3D30B5ULL, 
            0x83ACC7B66985A2D8ULL, 0xFBE19F3B706E7D3BULL, 0x753FA2F7A4B65DADULL, 0x8B596AF2E776953EULL, 
            0x2F7423BC060C1686ULL, 0xCC46C90361EE2BA1ULL, 0x56D3FFD41C1F35A2ULL, 0x67C16386C7A09EC2ULL
        },
        {
            0xE1699B36DDFFB05BULL, 0x4F7106D79D4CDE47ULL, 0x3CFFC8B08F68F917ULL, 0xEADB2716F2B208A7ULL, 
            0xDD1C861CA250BE4DULL, 0xA137EF7C256650BFULL, 0xD3C6259FECE42629ULL, 0x65CBE1CF15718230ULL, 
            0x3AE40CD64B489CB4ULL, 0x1281A7CFADA553CEULL, 0x23A161C943868BF4ULL, 0xCAB1130C103F2F82ULL, 
            0xBFB025701515172FULL, 0x6BDC9BFB38D3DFC2ULL, 0x1AF5D89F271FA34CULL, 0x48819131B665525DULL, 
            0x8D40E65D0A148963ULL, 0x3EBFBE5F53F0C193ULL, 0x3394070CFF772105ULL, 0x992CC5175C5186CBULL, 
            0xFF971B1363BB3F49ULL, 0xE835BF0F8B929748ULL, 0x8D907CF22FA87A82ULL, 0x7D8A57551F03B5B4ULL, 
            0xFA0CA00CA9B675D1ULL, 0x72BF153BEB20C962ULL, 0x043EFEC68E24B0A2ULL, 0x5577D40EC66BB585ULL, 
            0x6A00ABFADC01C3D0ULL, 0xE718EB447BC048DFULL, 0x4EEB754257EAA04FULL, 0x441FA3BF25C9EC92ULL
        }
    },
    {
        {
            0x0188483EBE6D82F2ULL, 0xB6C74E13BBAA14E0ULL, 0x019B0E33760E6024ULL, 0x2BC7091DC3FAAC1AULL, 
            0x4BF8CD1DA7C0337BULL, 0x44958953876151AAULL, 0x3BC3A782D4E7591AULL, 0xA9A892E59B7689DAULL, 
            0x4E376E889C2228B1ULL, 0x5E861C55898E4BCCULL, 0xD338E659BFC3F4ADULL, 0x2B4FD3FC67538480ULL, 
            0xAE44A041868120DEULL, 0x1D2D456CE8F1BEB7ULL, 0x145A041821ADF06FULL, 0x68847BB40685E985ULL, 
            0x0DDAB2FE06618A19ULL, 0x7119BC2BD705BD22ULL, 0xC2DEE04A944BFF8CULL, 0x3DFD4C30FB093F5FULL, 
            0x7A65525696A79284ULL, 0x1C71ACA8635C8858ULL, 0x36347A53AF0348A4ULL, 0x4D9175194E06BAD7ULL, 
            0xBE4F7AAC0338550DULL, 0xFD0DD38CC336C5C1ULL, 0x9C6A2B158FEDC5F8ULL, 0x8356C1384C4EFB4BULL, 
            0x04A546163F1E60A0ULL, 0xC609720D2C0892A2ULL, 0x57426080D1CFA938ULL, 0xB0F98383C917E68CULL
        },
        {
            0xB005C2C2BBC1FB94ULL, 0xACC04B54D74F35A7ULL, 0x2E6BC25CEC06A9C4ULL, 0xDBC861E4FD6C5202ULL, 
            0x5E33B5D8BC12646CULL, 0xCBDE26CE25F12467ULL, 0x16947EC0FC0D70B8ULL, 0xD54B1DE121E9DD9CULL, 
            0x49801698831E4953ULL, 0xABBA90825D620D0BULL, 0x869FE7687FE41C04ULL, 0xB85E53754E03A44FULL, 
            0x7D520F21EA80FC41ULL, 0x08BFE55F33D29743ULL, 0xA2DA7FED7A23D6C2ULL, 0xB4786E63AC92EC10ULL, 
            0xCAB6AB459FB61059ULL, 0xF5AA122F8ABE40E1ULL, 0x3538B09303C18723ULL, 0x7EB4643A275D4B3EULL, 
            0x049B24CF22D9F0B7ULL, 0x8CE30FFAC2F7593EULL, 0xAE32D096BAD45609ULL, 0x01A9EBD34B73C6F4ULL, 
            0x496C2762A462A144ULL, 0x952137BABA81301CULL, 0x1CB4FFEA0C43AD47ULL, 0xEE99C77A7553D4A1ULL, 
            0x5978CCB959DEB370ULL, 0x8C0CBB37FEDD37DCULL, 0x18ED12A41CF1DFCAULL, 0x13106EF39DE4A7CCULL
        },
        {
            0xF122D0AC134676F4ULL, 0x90E83B3404EBA0A5ULL, 0x7CA24E7747474133ULL, 0x720DCA2F272126E3ULL, 
            0x5DEF7E84B0C13FB5ULL, 0x356F4ECCF1D34B0FULL, 0x81DB37ADDAAB8499ULL, 0xE8B3AA888EA2EB01ULL, 
            0xF9153DF82B95640DULL, 0xD0DAE3E7FC98AA29ULL, 0x6BEC4A11D82ED3EBULL, 0xBAC4590E4897D631ULL, 
            0x4DCB06624D27AF27ULL, 0xBC19DA969FA1DD40ULL, 0x982EDF425B4F5997ULL, 0x49BE0D2BB2FB3A93ULL, 
            0x6D052BF724B18327ULL, 0x73152893CC1C163AULL, 0x8B5D0A752FE782D5ULL, 0x941427CF00F757DDULL, 
            0xBD40B54935486874ULL, 0x7FC4056AE3CCA773ULL, 0x361B96C66D0D8289ULL, 0xB600AAA192C9191BULL, 
            0xE296BBDE4819C87BULL, 0xBA834348D2A60799ULL, 0x6BB91268F129693CULL, 0x55834F43F1A296B5ULL, 
            0x0BE33469F2F722BBULL, 0x6BF429153E623353ULL, 0x1BA281CEBD1868EFULL, 0x09312D558211B534ULL
        },
        {
            0xA60AE85819E956F0ULL, 0x47411EB599CCAFDBULL, 0x243D6F0B699DDA46ULL, 0x43C947BC502B3D1FULL, 
            0x42B6BA8F92F59A72ULL, 0xFE0ACC1DC20E0357ULL, 0x88D9A6BE07738F62ULL, 0x046517484FE79EDCULL, 
            0x14ECCA0C0DCE33BDULL, 0x677D315ED75DFD02ULL, 0xCABB96F0387B8551ULL, 0x79100FE5C4924910ULL, 
            0xC85D27EEDDE6321FULL, 0x082A577A350030BAULL, 0x8216AC9F04F500B8ULL, 0x0DA8B464E2C1A0C3ULL, 
            0x7600EC6E4830E76FULL, 0x57327A8962B5F534ULL, 0x4FAE57428E89C8BFULL, 0x80146C5634D84660ULL, 
            0xA8B8C0AB21FD9194ULL, 0x3951DD8593243FB7ULL, 0x0CC3370731578FB6ULL, 0xB287724E2539DD60ULL, 
            0xA8B7B886FCF543A9ULL, 0x9A575FF46CC8F8A0ULL, 0x7FCD697B5A4236F1ULL, 0x88BF1AC743CAF22DULL, 
            0xD3022E5CD019384AULL, 0x8CE1F1350CD6A372ULL, 0xF8B2F4BE55C73809ULL, 0x64D389FF5C329FE0ULL
        },
        {
            0xC46CCA535DA8474BULL, 0xCB587B36E91F921AULL, 0x5C716DDF7E627EE8ULL, 0x4CA91D046258CBF9ULL, 
            0xB17B0FBE4A41D0DDULL, 0xC47B38FF2AED0239ULL, 0xEC4537EEA316D92AULL, 0xABEDD2F461A06E60ULL, 
            0xC2CB502A3993BA5AULL, 0xC83DC94BAB77F0FCULL, 0xB334023149D4CA1CULL, 0x21CFFC67781CA270ULL, 
            0x39E5DAE0C676584CULL, 0x34963432BE270254ULL, 0xBD745311E559D445ULL, 0x959D5FD63DDAA6D5ULL, 
            0x68BA6CE760AC607DULL, 0x7F4855E77B4F60E5ULL, 0xF1804E8F28E2C337ULL, 0xD9392C1EA650741CULL, 
            0xE9D0C65ED91643AAULL, 0x18595EBF15D9DA41ULL, 0x4FF288369A220BB0ULL, 0x900CDA4C4C21C0B8ULL, 
            0x7448B5FBC2145FD7ULL, 0x6AE302435AEACE38ULL, 0xE8E9338BC52DE326ULL, 0x750206452BAB9D07ULL, 
            0xBA14241AB2A9F070ULL, 0x9E856D7FE5F007F8ULL, 0x4984F32AE68ADA1AULL, 0x9925F4F565030504ULL
        },
        {
            0x7BBCBC7C2B132D5AULL, 0x387EB71A9057B598ULL, 0xC6C662B536080DCFULL, 0xC6744B7D4F196C16ULL, 
            0x9B3E116E5754CA46ULL, 0x26654E24AA37350CULL, 0x7EF518121C8108FCULL, 0xA10797BF01960946ULL, 
            0x52E4663005CFC106ULL, 0x249509B5F74CD9BBULL, 0x6C2AB289E4FB7D69ULL, 0xEB417D24654C6D27ULL, 
            0x22119E8CF62AB978ULL, 0x73EF63D885B44AECULL, 0x40DC7CD6F72E9C6BULL, 0x471BCD3429F56EA0ULL, 
            0x034781D41A3E282EULL, 0x8EF38FD1EAB946BEULL, 0xC427D010E57AA57BULL, 0x4B9F1D8167BCAE5DULL, 
            0x917AF881A315BCE0ULL, 0x25F984788305CF12ULL, 0x02D5A88541366211ULL, 0x97A31E5452A1634CULL, 
            0x8CF8BBB0607FAE42ULL, 0xFB4224F8240B63F6ULL, 0x0BE1D102E56E476BULL, 0xC99F0204A94F6702ULL, 
            0x758BB56449B78DD0ULL, 0xBA36E4D839AEBA70ULL, 0x429373AFA65962A6ULL, 0xE9A571F69F8BD3FFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseFConstants = {
    0x5D29F778FC3055A9ULL,
    0x71E69BCB923290B4ULL,
    0xB1105CA9D8A0D4ADULL,
    0x5D29F778FC3055A9ULL,
    0x71E69BCB923290B4ULL,
    0xB1105CA9D8A0D4ADULL,
    0x282EE2A269705B4CULL,
    0xCEB8F9014DDC2D3CULL,
    0xFC,
    0xA9,
    0x37,
    0x0D,
    0xE5,
    0x87,
    0xD5,
    0x59
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseGSalts = {
    {
        {
            0xCA3FE8249B484EFBULL, 0xE1D98542210A308CULL, 0x59AAD61B179E0213ULL, 0x098D948CCBC656C8ULL, 
            0x2F6FE8E287981693ULL, 0xEBC127B4F98D49E9ULL, 0xDAD56EFB13A3202CULL, 0xEC008C0D3485ECBCULL, 
            0xC03BD0D79A4141DBULL, 0x9EE2857BF6D39D71ULL, 0xD1034A5FE4E8D696ULL, 0x45F745A9C50936F8ULL, 
            0x50C1DEAA9FD92F0FULL, 0xAAAAAD7655AA7D1CULL, 0x9C0CEE40A4E52918ULL, 0x207C0B0403297587ULL, 
            0x341D098F044CEFCAULL, 0x0ADEC45D56EFFC17ULL, 0x2578853C6734B620ULL, 0xEFF1D5FC5BC22936ULL, 
            0xB11A72DDD92CC07AULL, 0x180BFFF01EB51CD1ULL, 0x46C6EA33CC70D3E9ULL, 0x46170AAACC2D766AULL, 
            0xF1D9E9D1BCEEE72EULL, 0x57C94197D9ABB73EULL, 0xA3044453425D70C2ULL, 0x3568C7CA7A058C06ULL, 
            0x28B80DB7031BFBD5ULL, 0x09A8CA0C1D9D4466ULL, 0x77499DB837BC67BEULL, 0xCC98467FC3DAF81CULL
        },
        {
            0x5541CC889480A682ULL, 0x725252A31AB9214FULL, 0xEBBCDB9E1FECBFE9ULL, 0x7EF560B2A06C867EULL, 
            0x2A821D1DE0C93DD5ULL, 0xE14D224A6531BA2EULL, 0x066DEB3D2004B684ULL, 0x46913464AC3B98A2ULL, 
            0xDC65D1A5AE379E58ULL, 0x69011D9A16AC1B27ULL, 0x716FEC173E588C67ULL, 0xE5F47B57625F789CULL, 
            0x3E784E0CF3C5AA62ULL, 0x9A7FC16A41D326D9ULL, 0x516FDAF01C9C2CB6ULL, 0x1D7354A92AEA0122ULL, 
            0x5201DBEC0B10D7B2ULL, 0xA9B210A2F7D5AF54ULL, 0xBF26F8245AEAACC3ULL, 0x1F9941800535A390ULL, 
            0x7C226BD262E6226AULL, 0x625BE7E64F1E3358ULL, 0x35086A99E4873AEFULL, 0xDA134A73509E4DBFULL, 
            0xC8C21BF9AF64723BULL, 0x54E3F388B4920EECULL, 0xF59DDD4D155967E7ULL, 0x5F766A64459391CCULL, 
            0xF7B47CCA5B5374F3ULL, 0xCB7241EBD2BD6C30ULL, 0xD23C39AB4F0773C8ULL, 0x9AA8BC3C7343BD23ULL
        },
        {
            0xA604593EFB67697CULL, 0xB61BB05292D9AA6FULL, 0x4BBDCDC6819374CFULL, 0x9C35A14C22DEEEACULL, 
            0x259AB792E4932692ULL, 0xAB1CB9C74F16768FULL, 0xB686EADCD8039A37ULL, 0xBB7159F9C413CD60ULL, 
            0x4335EA5E3401213EULL, 0x47018CBCCAC4DD2FULL, 0x750C9E06AAE0AB7DULL, 0x779E68B5AA7C06ABULL, 
            0xD9D1742193528A12ULL, 0x57A8DC1884FA8E91ULL, 0xE363DBF47BBD0A65ULL, 0x27F3D3CB132F7062ULL, 
            0x1CF807E0EF41F35FULL, 0x8F82FA68CFB76975ULL, 0x230DB34A23AC2FC6ULL, 0x32960C320E838DC3ULL, 
            0x683529EF15CDF355ULL, 0x1DAC3FD38C31C5C7ULL, 0x7D1F8B874767E13BULL, 0xA906719EC2E696EAULL, 
            0x51394573D88724C1ULL, 0x97FF7317C3FAF123ULL, 0x9D52129B027962C1ULL, 0x6BC67C65C01CD253ULL, 
            0x5127ED9A2E45DF3AULL, 0xECF3DBC05D625C51ULL, 0x6DCFC014C52FFB1FULL, 0xCA48D39665E15176ULL
        },
        {
            0xDB5C626DE86403B8ULL, 0xBF0696D1C5974DB4ULL, 0xF0A8D35F84CA6141ULL, 0xBDD9ADF3FC3EC049ULL, 
            0x103ED3F4F1D9C519ULL, 0x161CD65058045E92ULL, 0x2DC2C26F5656B772ULL, 0xC6B33DF34D73321BULL, 
            0x98A51835708377E5ULL, 0x4E1C4FD8A013E71AULL, 0x3A9DCF731ADC96D4ULL, 0xAC3BAD67C4224DD9ULL, 
            0x29D4FF1AA8FB0C80ULL, 0x04D8A617FAEF30E3ULL, 0xA3BF6711DB231151ULL, 0xAADA85A2D7EB6005ULL, 
            0xC7BBCF1724FE1BB2ULL, 0xAE7673BA193BFBA5ULL, 0x5CF7ECA078390BFBULL, 0xC03A6444CE0497E1ULL, 
            0xFF3A4A25FF1759A0ULL, 0x7CD20CAC1FCDA2D3ULL, 0xF54AC24C5AD0A6B6ULL, 0x2B90B10CAF618593ULL, 
            0xC51134C42EC7DBC4ULL, 0x3EB79CD46BA3350EULL, 0xA98C234A076FECDEULL, 0x8E1835A4ABD77833ULL, 
            0x19B4DF0B7B44E716ULL, 0x3CF7A1C329194689ULL, 0xC5C2D83293F77499ULL, 0xA11AE6A8009B4898ULL
        },
        {
            0x3CB4BA16BCEC77DFULL, 0xE51D478798FE63FAULL, 0x36875FEBCD212C6EULL, 0xBF2263AC3A221F55ULL, 
            0x7753EB25BD11BCDDULL, 0x74DA0B228654FB66ULL, 0xD19F4C6F2D894F8BULL, 0x8023106161150154ULL, 
            0x9E41790F8BED6EFDULL, 0x11B078CD8FF21E11ULL, 0xEC12C10A3371ACA6ULL, 0x8AB7553F53A1C0FDULL, 
            0xA6434A5D8BCA39AFULL, 0xAA6A046D55CE2177ULL, 0x6FD5FDF5174A9C8EULL, 0xB5568A25F73F43E2ULL, 
            0x9AB73DE32CABFF32ULL, 0xAE70FA11668D4AE4ULL, 0xCC15AAF1DB9050AEULL, 0xB09DE3F4B485C6BFULL, 
            0x3009C212CEBA65D3ULL, 0xF09C39B44226F180ULL, 0xF22D46AE0BDC6900ULL, 0x3EC26A2AE5FB001DULL, 
            0x7CC0AD7A255582C6ULL, 0x14D1F9F8B8FAFD23ULL, 0x464BE679411576E9ULL, 0x52E3C74A0112B65EULL, 
            0x78AD7404EDF5EE11ULL, 0x865F0C7385ECF0C9ULL, 0x5F6582A8B9C1011FULL, 0x49ED0936A9B3A688ULL
        },
        {
            0x668547629D7D77E1ULL, 0x1CC5917B6372D203ULL, 0xE74A34BC2AF2249CULL, 0x7EC2340379F22DB2ULL, 
            0xC5055C50B6BFB11FULL, 0x1A9AFBDBCE417AD8ULL, 0x14C54A594B32F0C1ULL, 0xCFEC7E7F7D943AD4ULL, 
            0x38C4EB7A4D159853ULL, 0x56DA65285D27A813ULL, 0x9CAB4CCD1A855ABCULL, 0xFBD94D548D3B5A06ULL, 
            0xC9080393471F5A2DULL, 0x695A436D399685FDULL, 0x8127F896BAB8464BULL, 0x615F1570A822F71EULL, 
            0xE4617CC8921D4602ULL, 0x9392463DE4389F0DULL, 0x0873F36571F89D68ULL, 0xBFEB0E836DD89645ULL, 
            0x505D07D318830F87ULL, 0x6472237DD73A1965ULL, 0xF8EF46D6264D3390ULL, 0x659AA084377BA57BULL, 
            0xD13A74E30ED4CB90ULL, 0x582B90555AFF1EA8ULL, 0x3E258D996759882CULL, 0xAD96C1E698304129ULL, 
            0xFB7740B2B5995BC0ULL, 0x204F7633488DA6BDULL, 0x1DF65A37E9A6B3BDULL, 0x083E22558D1FB5CEULL
        }
    },
    {
        {
            0x9794366080DA0A3BULL, 0x2C62A0643151DC5FULL, 0x15B6B06C84DC54BAULL, 0x732CD947064DAC5EULL, 
            0xA84FDB6442811E0BULL, 0x2CB7F1B7B9E3754AULL, 0x9553D6CF59BE96A2ULL, 0xA7AC55FEF9C67129ULL, 
            0x08C8C93E57961FA5ULL, 0x67BE9DABDAB1F97FULL, 0xE06F1E29FA3F82F7ULL, 0x0F7DD636785880DCULL, 
            0x94B45EBF251E2B36ULL, 0x3148FC632DA58DBCULL, 0xF03A63C5C69552E4ULL, 0x8F52E6CFBFEAF318ULL, 
            0xB2759B39D4C69190ULL, 0x3D7D2E9F7BE3570DULL, 0xAE4FED6D90997544ULL, 0x8EC5FC523A8657CFULL, 
            0x8819554B1D453384ULL, 0xDADF88F917D19612ULL, 0xF0ABD93DB585628AULL, 0x090F042ECA41413BULL, 
            0x938DCD1DAB311E2FULL, 0x36562AC859FDF7EAULL, 0x728D30DD196C3902ULL, 0xBC085D9B08834C95ULL, 
            0xFAD9CC510F54E5BBULL, 0xD7C275A3C5A7D222ULL, 0xB3BB8F55BD8D6535ULL, 0x19E55442448AC127ULL
        },
        {
            0x2BA3C86D30272D02ULL, 0xA1EB8DE3DD7EFCC4ULL, 0xDAB5F05488EBBEE8ULL, 0xE233A2D36EE8F9B3ULL, 
            0xF40877A97C75713FULL, 0x013EC7946A3F447BULL, 0xE67CFDA0F4CA3B77ULL, 0x39BB393DB8756E49ULL, 
            0x156397E85377267AULL, 0x228BAB2EC02130F5ULL, 0x7442F18B93A23622ULL, 0x1F82598466C6B8F7ULL, 
            0x6EE309D218FDC0C8ULL, 0x12E7A853D9B534E4ULL, 0xA29642027544F048ULL, 0xD388B855274A30C9ULL, 
            0x54F5887AD37EC805ULL, 0xBE82FB16605A810BULL, 0x3422634D77690129ULL, 0x891F34C6194664DDULL, 
            0xBA371791D62D0EB6ULL, 0x1DF42C6A0A059183ULL, 0xBFFDC7D96C41B3E6ULL, 0x07A1A8DDB8F92542ULL, 
            0x2E9ABEA25DB487A6ULL, 0x3D96FDD0ECCB583EULL, 0x7A4AB1AD5B908FBEULL, 0x85463B90E605A19FULL, 
            0xEA0442C5CFB40215ULL, 0xB0DD23CFF96A495DULL, 0x04B809B10BA97553ULL, 0x4711DFC25F2A337EULL
        },
        {
            0x49E3D4480C5CA07CULL, 0x375007E326D07C72ULL, 0xA190BE9578ACCD8DULL, 0x32E1EFA540D395CCULL, 
            0x9CDD4E97BBF29EEFULL, 0x267E177568AEBD54ULL, 0xFC4BD03921FE913CULL, 0x1E1D05184FAEBE93ULL, 
            0x16169EFCFFEB86D5ULL, 0x84EBE1554458B35BULL, 0x439989EDB5304653ULL, 0x3CFCFD4945D6CEF9ULL, 
            0xD24877627BFF6512ULL, 0xBDB7E3EE0CEB6E6DULL, 0xCC15E49B5F0EDC7EULL, 0xCC30071FA3629E96ULL, 
            0x38F33F98A4DBDE1CULL, 0x44A9E4B00FF90274ULL, 0x7602FCBF80C58245ULL, 0xBCF67EEEE29256F5ULL, 
            0x046D5F0269317B29ULL, 0x8E2E53C9F8B48A5FULL, 0x3650B1F16BD82AE9ULL, 0xF6599E22268E143DULL, 
            0x9D12ED0523AC95AAULL, 0xD54A10B2AC78230DULL, 0x2A67752A67F46D2BULL, 0x2E6AAD2DC6B7E4C3ULL, 
            0x7BE405979D59DB6DULL, 0xDB0563A6244EDA03ULL, 0xA35F8BE7C85F3E5EULL, 0xCD5C8195A2ABD08FULL
        },
        {
            0x97E1A419BC060CE2ULL, 0x6D032A6AD41A0782ULL, 0xE71F7134225F9781ULL, 0xAF5E27E27FEDE842ULL, 
            0xC28EE4883D47E227ULL, 0x5A09428D622C7A7BULL, 0xE40A9256210ED53CULL, 0x87629C99C6373290ULL, 
            0x2049C8CA8810025DULL, 0xF3D7BA9B65F3B2D0ULL, 0x1CBE4FFF27C35BB3ULL, 0xED979C80D7EB3154ULL, 
            0xDCC8324225AC62A8ULL, 0xDEFF60D33F2535E3ULL, 0x5DFF84BBB02B9C41ULL, 0xCE817087D5C3745BULL, 
            0x6135E5B1F673B422ULL, 0x66283C9C88DDC7BAULL, 0x3A12AE063966217EULL, 0xD04505FAB5DCD8D0ULL, 
            0x44D8FD669C1125ADULL, 0x36CB4E372146302EULL, 0x2A67447CC95097B8ULL, 0x6A551298C5CFABE7ULL, 
            0x76C04A5A0015A2DFULL, 0xC3F2F79810D91FD8ULL, 0x48A627C668361909ULL, 0x6DA03D119003504BULL, 
            0x8E336D94F3AF0011ULL, 0xC98302573D336B4DULL, 0xD160A9120D557750ULL, 0xD380086B80EA9837ULL
        },
        {
            0x757F97DD5977B946ULL, 0x5D13F4EDCF45AC78ULL, 0x0917F0B4A1AAC923ULL, 0x0BDB3B3E3D3C56BAULL, 
            0xB15091AC2D42E5EBULL, 0x4530AC8E270936D0ULL, 0x9F9E2271E13FD451ULL, 0x0E9BE8EA6F6FD4C7ULL, 
            0xFDE42FC215C5F657ULL, 0xFA5EBD6574764C0BULL, 0x779C7CD484D51A49ULL, 0x6CB9DE8D846CD76DULL, 
            0x05019F88AB1AB9F8ULL, 0x335B2375DE874F01ULL, 0x285C88E36E315883ULL, 0x7CF9339F755FD351ULL, 
            0x990E2A2BDB266862ULL, 0x23AA6676B1077AFBULL, 0x522B16CD8706798CULL, 0x59CE255E2547128CULL, 
            0x735537A4FE20E40BULL, 0x1A07BB4B130820A9ULL, 0x6BB120BED06D32A6ULL, 0x1101D2E2AF35C00AULL, 
            0xEC2A559256AF8732ULL, 0x1836C7DEF20277BCULL, 0xBD3C3F87412ED37BULL, 0x2E1631E8E576FDD1ULL, 
            0x1EF4F19FB0B7BE5DULL, 0xA77AF499899BF98CULL, 0x1059C677662F502FULL, 0x3263F305E22E4527ULL
        },
        {
            0xC21AF5AD942A434DULL, 0x06C5996C71330DD5ULL, 0x98C6B8B03DA80D6BULL, 0x43CD7042A545F674ULL, 
            0xCC2D9ACB6D3B87FFULL, 0xD3E636E9F0FCDB8BULL, 0xEE55B2F32C0B4738ULL, 0x63BDC444216D5596ULL, 
            0xD6EF6EFDB8D2160BULL, 0x14C844C3637974F4ULL, 0x2633454D982FF2ECULL, 0x66637CB980BDB0A5ULL, 
            0x2785D756702B20C4ULL, 0xAB92F001393DA835ULL, 0xC151C08CD4BB0340ULL, 0x49FE96CBAD6A777EULL, 
            0xD879B8786AF1EC42ULL, 0x474D1D7B27EDD622ULL, 0x756C8DDE7DF95AA0ULL, 0x7165CE5D26C509BDULL, 
            0x1BDE08721EBF9F13ULL, 0x443AEAB3A26DCEF3ULL, 0x4AC6D4E1CA133FB4ULL, 0xFB439E28CF2C1EE7ULL, 
            0x26B4B1F57700A8DEULL, 0x7DFBD509467C69AEULL, 0x3D5EBB7B0A6BA55FULL, 0x6C8786B9E1C4A068ULL, 
            0x63D2EA2FC8CEDE7FULL, 0x559C1B784351A0C4ULL, 0x9297674D11D61C15ULL, 0x7A0A71185668D774ULL
        }
    },
    {
        {
            0x26A8EF88DCA137D4ULL, 0x583AA380BEC57B6FULL, 0x1B448274566CA212ULL, 0x28183EF97234BFC1ULL, 
            0xA55B950237202C9FULL, 0x91DC76BE98671386ULL, 0x0050D787F19B6F58ULL, 0xFAA34A1EF06CA354ULL, 
            0xE85EECC234519225ULL, 0x9132C967551DDCDBULL, 0x20E51370B89B3064ULL, 0xD394921CE7E1C50EULL, 
            0x365A2DBC326FD870ULL, 0x50E022183245E9EBULL, 0x15FC284798F54AE6ULL, 0x4A2C419BADAB1B18ULL, 
            0x79291ACF00C9AF82ULL, 0x5C3C5A4D4F1B030AULL, 0xF28FB4AFA3C177F1ULL, 0x8A7F2E0DCCE029B7ULL, 
            0xBEC8740A6FCA5B42ULL, 0xDC28154959E9596AULL, 0x5E928EA212FCBB0BULL, 0x7328672B8B02C2B5ULL, 
            0x1E3244388098E175ULL, 0x3194022D150486FBULL, 0x263E300630CE51F4ULL, 0x3DD596D08F27D208ULL, 
            0x88B9FA017B1A5F05ULL, 0x67C637E9849C8B49ULL, 0x51964B5FC13F7133ULL, 0x2E8C60757B0B625FULL
        },
        {
            0x84ADE96FEF98DD9EULL, 0xADB87074FF48C87FULL, 0xBD6C0F1305C1BA52ULL, 0x8D41B0391D1745FEULL, 
            0x0DC0C8E4DD4743ACULL, 0x9AC37D2502C5A25CULL, 0x3F81AF648BADBA2DULL, 0xD31C76E309FF1341ULL, 
            0x4FE695235DB2835FULL, 0x98EA22ABFCC8FEE9ULL, 0xECCBC58C055BD07EULL, 0x54C4976F5433D4F5ULL, 
            0x1AE2C3A5C5886D6AULL, 0x318F648D8C7F36EBULL, 0x0C0FC04BF7D4BBCCULL, 0x5DEE99EC4853C620ULL, 
            0x65EFA24168B7DFB7ULL, 0xD640240D87CF9B6DULL, 0x97E5F38D53BD0970ULL, 0xE8899AD796879EC1ULL, 
            0x6FABD687E9AEA933ULL, 0xF05EA3E2EA43E428ULL, 0xD316CAE65A6AC14EULL, 0xB0F4460EB171142CULL, 
            0xB3706B534C6A8F53ULL, 0x709B3B9B598D3F1BULL, 0x019B080505EA1CCDULL, 0x33D7F5E46D5605E2ULL, 
            0x25FAC43DFA10AF08ULL, 0xFCB6741CE78B7B5EULL, 0xD52D5684BC3EBC4FULL, 0x1E8CC321C74C7601ULL
        },
        {
            0x40945AEF3753883FULL, 0xC3ACF51DFA47BCC1ULL, 0x07D98232F717D836ULL, 0x3CC16FF430FDD840ULL, 
            0x3FA7D3707DACF087ULL, 0x11B72D6D4AC23922ULL, 0x139B088ECEDFBABAULL, 0xEC74CCE01AA5C00FULL, 
            0xC92D1A19D387826FULL, 0xD90AFECD6EDE9B26ULL, 0x59FD7CB264038E99ULL, 0x5B993FC386A4B91AULL, 
            0xE91B266DABC3D455ULL, 0xFFC36B709802993DULL, 0x9D72D7CC4AF16064ULL, 0x40C400B1EAA91DE2ULL, 
            0xA062170CE12B6B2CULL, 0xEC6DF29F68CB9289ULL, 0x803FF415D6478CC0ULL, 0x71196D46A8B816C2ULL, 
            0xA30DA4C7FECDE452ULL, 0x33F5E650A5A1942FULL, 0xBFD0EDADF8662D01ULL, 0x66A28F8A7179BD49ULL, 
            0x0B9BD1F314C51B5AULL, 0xD0E845FDE4313E9AULL, 0xA45CE9FC4A979A6AULL, 0x80DC2950F5817EE9ULL, 
            0x418988D9D1460875ULL, 0x0A15637A85382C1AULL, 0xC8CEA02583941EA3ULL, 0xBEED66EA90B7D018ULL
        },
        {
            0x802F70599752D785ULL, 0xCBB7365416CCBD09ULL, 0x24F968986103D1F7ULL, 0x777F20A9D54BBA37ULL, 
            0x22C33E52F0F5D77BULL, 0x47F9ACC901A48F0EULL, 0xD13C63B3FDBC4A78ULL, 0x6B8E6B9867CE46D0ULL, 
            0x669B82FDCF7C5A3AULL, 0x38CB1F7F821223A4ULL, 0x23FD6806A4288E80ULL, 0x184C5C86D6956E9CULL, 
            0xBD1BF33899858103ULL, 0x162E009968F20104ULL, 0x0E5E6FD9F4A0E321ULL, 0x6579E8831ECFAC59ULL, 
            0x9139D0B78399312BULL, 0x9A1A62E3EFD11E62ULL, 0x7BFEDF391D58A1B6ULL, 0x7692EF70F155CCCFULL, 
            0x39F5FA602A1DCF28ULL, 0x9D3ADCD44B38739BULL, 0xD6BFA05FC9E67805ULL, 0x962816C543A0153CULL, 
            0x1C3C06D9605807F6ULL, 0x20B89BBBAF6C7FB1ULL, 0x0A21826701FE6CB6ULL, 0xD774D626B7CAB7E5ULL, 
            0x3508BF6DE9678C49ULL, 0x55729F5B9E14ABA1ULL, 0xD9E7631CBF534819ULL, 0x45C7276E5B9D3AD2ULL
        },
        {
            0x032C18E7604B8752ULL, 0xB424AB9DC2FE72BCULL, 0x1F4F6356E0EAEEC4ULL, 0x5B33B3D5310D9895ULL, 
            0x19E69A885D65830CULL, 0x4284CDFD19AE9AACULL, 0x8A28EE7EC3636D98ULL, 0x03407BC8738C78ABULL, 
            0x4D92A27DFB559D20ULL, 0xF485EEC5BAC076B2ULL, 0x28E9DBF4F52234F7ULL, 0x2145F23B48CDC7F1ULL, 
            0xC9B71AC5ECAEE19AULL, 0xC5AEAD796363C3B8ULL, 0xB8C7F171AB611DA7ULL, 0xE8787A682E32CC61ULL, 
            0x3D2C8886B46A132AULL, 0xB0B3BB19CB448AFAULL, 0x59B700195CA36D24ULL, 0x78B1223BB76BF15FULL, 
            0x7010E21770523EBCULL, 0xAA57AA0AEC3362EFULL, 0x8784217161965CB1ULL, 0xCF8D87843E93532CULL, 
            0x72A8D24A4CCB7F7DULL, 0xBC5AF3EE04FE1053ULL, 0xB007D55A1853FE1BULL, 0x8C067E8C67261676ULL, 
            0xE05A08294F382026ULL, 0x86363EF0FF50D7A8ULL, 0x854DB41A4C3B4F2FULL, 0x9ECA2F9D0D449077ULL
        },
        {
            0xB914B8B806AA26EAULL, 0xC448FD2EBDBABF90ULL, 0x71FF071E34DE8228ULL, 0x7189891BA9D2E96EULL, 
            0x218C8B6AA14B71A9ULL, 0x4351B9BAAB3B2531ULL, 0xDE04F3F23C6F9AF0ULL, 0xD987FD83C5F23533ULL, 
            0xCECBD5C9FB41951FULL, 0x312EF154ABF1DADEULL, 0x2E3656F8AF6D53D6ULL, 0xD9119D56D75A2FA8ULL, 
            0xC821140DB6559B33ULL, 0xFF07E1FFF23FF9C5ULL, 0x45AF5FC4993A2F33ULL, 0xB14ABC23E39C33D1ULL, 
            0x011832A6659852ABULL, 0x6AF9C5611470E902ULL, 0xBEBCEB386216F1C7ULL, 0x38035BAE164D8694ULL, 
            0x8A4FBB04BE7990ADULL, 0x7D15B559B6211E94ULL, 0xF60CC562EE25C1B7ULL, 0x1CFBD451CF7EAF8BULL, 
            0x260B4796EA4104B3ULL, 0xA657009BA6D50A04ULL, 0x2F927E60AD14A5B0ULL, 0xE08FEFD1B7012374ULL, 
            0x9F085E83CBD263B8ULL, 0x1828ECFF0EE3CDF4ULL, 0xBA4E05694CF9C150ULL, 0x72E4EADA550BFCE2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseGConstants = {
    0xA6630D08666DE097ULL,
    0xD4774834A563059FULL,
    0xF7379087A81BE3F6ULL,
    0xA6630D08666DE097ULL,
    0xD4774834A563059FULL,
    0xF7379087A81BE3F6ULL,
    0xAB00028A860DA8C7ULL,
    0xAC71D8A741724C75ULL,
    0x55,
    0x3C,
    0x4D,
    0xBE,
    0xFF,
    0xD4,
    0x96,
    0xD1
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseHSalts = {
    {
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
            0xEAFB1462308A4848ULL, 0x8DEA6990D06CD264ULL, 0xBDAA303B29DFEB8EULL, 0xC803ECCC67F1A9D8ULL, 
            0xED50C6BE424A58D1ULL, 0x4CA65D6DB0BA5A25ULL, 0xE1B63016C0439112ULL, 0x7D26A5C003E78D8EULL, 
            0x19CCF05EBE2D235FULL, 0x942A7BE1A28F3C6BULL, 0x0524FC81217349B7ULL, 0xD95B8E7914181335ULL, 
            0x2A6097875AA25D9BULL, 0x43CD1A64C0B787C3ULL, 0x8C7A0F1F6FB6E6C9ULL, 0xA94D08DB92FF6728ULL, 
            0x49B6CA62646B698FULL, 0x15F5A9C9727E55FAULL, 0x48783EF441EE3BECULL, 0xC338D886716439EDULL, 
            0x6610747113011C3DULL, 0x9CFC76D55737AED0ULL, 0x16D0E958ED0FC947ULL, 0x99A66551B5C640E6ULL, 
            0xB1567836E57D77EBULL, 0xC737A24AC0378B89ULL, 0xD831B938FE5E6D7AULL, 0x2982737880F9D041ULL, 
            0xB9AB9C1E2B14EDE0ULL, 0xDA4529E03EFB84ADULL, 0xCD6FC45B474C6FFDULL, 0x77ACE12F4CAAC1BAULL
        },
        {
            0xE07DBCACF52547F8ULL, 0xCCCFB98DCA24841CULL, 0xA461E8B98E4E2338ULL, 0x1109BA5377AA77BDULL, 
            0x22611F435ABCC384ULL, 0x27455203BB00E652ULL, 0x57805144BA208C4BULL, 0x987A700A5DDE827EULL, 
            0xA287023B7647FFE8ULL, 0x7CB89FA28997AF36ULL, 0xDB75FEBE33151562ULL, 0x59E3A56EF5A0705BULL, 
            0x84D971595689C24DULL, 0xE4A1CAF857346700ULL, 0x08335AEC85C69554ULL, 0xCA9543F8041B1319ULL, 
            0x424177E8AF00164BULL, 0xBC1340A28DE40149ULL, 0xDAB5BF652F51701FULL, 0x9290AD5AD047B0BFULL, 
            0x28CC584318F3A357ULL, 0xCFF0120F3029A94FULL, 0x60824C2EDE98D89DULL, 0xD8030E1FB6E06CB7ULL, 
            0x39D625C967067C93ULL, 0xBF9F55FEDD92C9C8ULL, 0x04FFA97C1084C145ULL, 0x3C70F1CD4F7077E5ULL, 
            0x42BFD5926FD7A773ULL, 0xB42034734EEFD293ULL, 0xF61A655F265A4F5FULL, 0xEEDF8673B4D9B346ULL
        },
        {
            0xEBD74BC1F072CDA5ULL, 0x947B9DA717449D56ULL, 0x7D10831213B9B8E8ULL, 0x092334676A41B921ULL, 
            0x072950945921EA09ULL, 0x1FC41233F4E3874BULL, 0x5DDB6FBA648ED795ULL, 0xA5DE3AAA6CF6BED0ULL, 
            0x7860BC3B1992D9E0ULL, 0x587F2E4B564DFA68ULL, 0x5A268330D5BD0C9DULL, 0x1B59525714A19C2DULL, 
            0x117A30D29D3AAF6AULL, 0x174841AFFF8A4DC3ULL, 0x9C3A0CD4C5D965DAULL, 0x026F46FC249F5F4EULL, 
            0x7283239BCC01C5B2ULL, 0xA290A1867E55E613ULL, 0x26B499A78CACBF9BULL, 0x1C4672B986367B8EULL, 
            0xBB7FEE398454C71FULL, 0xFE56E98D5FF20104ULL, 0x7295C08FA44C66AAULL, 0xB9EFBB4039AFFFEFULL, 
            0x2D92355794FCAD76ULL, 0xECFB99EB06E18FA9ULL, 0xAFE05F83F74794E8ULL, 0xC1E83C871F3A7719ULL, 
            0xA8000FAE8277523AULL, 0xB12C70F6171672A7ULL, 0x02372764280157B4ULL, 0x2DBB5BDDA614C091ULL
        },
        {
            0x2F77D3BDA6902141ULL, 0xB8726AB857B9A63FULL, 0xF3E8B9E3A5403CACULL, 0x3676CE85D1C7AA35ULL, 
            0x74EC0A64B4AAC1E9ULL, 0x3B78C66D21F1B441ULL, 0x55413422A5015029ULL, 0x3EB7EFA4F01E0FCFULL, 
            0xCD131D4541941C2FULL, 0x9E45C7E7034A912FULL, 0x5500CD5B0659EDD8ULL, 0x535C53522207A660ULL, 
            0x1529783BB9A7A706ULL, 0xCBB3176929247DD4ULL, 0x9DCC255C0B2245A1ULL, 0xBF4CA5A5EBD1D175ULL, 
            0x5D41B35A9E469C7CULL, 0x3D3D2FBB19BBF577ULL, 0xDB3DAD3F985F9585ULL, 0x1B6BBCF9BD5452D6ULL, 
            0xC3022CA42A0FB2D0ULL, 0xDA2FB59CA58334A3ULL, 0xE02C52743C051354ULL, 0x65968CC2D1238976ULL, 
            0x32B24BD5B6710B12ULL, 0x3BF308646F42A58BULL, 0xE6DC7CC523B42C41ULL, 0x87A965D4F0F8AE08ULL, 
            0x21BE2D41C69D2006ULL, 0x3FB4E880C50ED434ULL, 0x3E657B2E54800797ULL, 0xA76B8D678BC89E34ULL
        },
        {
            0xEFEA98ED3F913A66ULL, 0xF5C47443AD67055DULL, 0x0C57D8C8A608D6ADULL, 0x755EFE64A1A2E7F4ULL, 
            0x6EAE048484D87593ULL, 0x932DBCD1C0CC6DA3ULL, 0x89614A9C732B05C9ULL, 0x161672977A6E6352ULL, 
            0xCB5383E83AF35C3DULL, 0x1FEB0FB3136A18D7ULL, 0x4504C235FD5EE175ULL, 0x91900EDD963D4E30ULL, 
            0x08AA3B99148D569CULL, 0x88C102EFBCCBDE7BULL, 0x935F78916891682FULL, 0xC3116D18DB15406BULL, 
            0xED70B43EE1568D4DULL, 0x1B284FB8CF4917DDULL, 0x66440CE32770AA5BULL, 0xD50E78A62AEAB77AULL, 
            0xC6375E2AAEDB063FULL, 0x1DBE04D70B724838ULL, 0x472BEA62E6BC8825ULL, 0x4E8DAE61D03FC37FULL, 
            0x485DE28EC1D4FAE1ULL, 0x97B0AF0E493D92F6ULL, 0xA7216E0DF1D3FC73ULL, 0xECAD7531322B55AEULL, 
            0xE4DB6330C26F555CULL, 0x1F08449F27441E28ULL, 0x80BB9BD2A59C46C3ULL, 0x21A66D72B85EA19EULL
        }
    },
    {
        {
            0x12C11548B3774978ULL, 0xE29B6CFBB8CA6A6EULL, 0xFDDD6A1F9E68D105ULL, 0xA81D78DB627C3794ULL, 
            0x56592EF885902636ULL, 0x7425D9435C05E8ADULL, 0xD6ED6D1E66D93653ULL, 0x5F0DCF7A297C8C26ULL, 
            0x83B9A46BF70F4A89ULL, 0x4FBBE0E6145C89FBULL, 0xE5D57B8FF1502732ULL, 0x6B631A72290929F9ULL, 
            0x09CCACDDE79DC45FULL, 0x78BBACA7AF66582FULL, 0x93B15DFC5C236D4EULL, 0xED3893C460F434CEULL, 
            0x9C56EFB39EB184FCULL, 0x86B1E2AAC7E372C9ULL, 0x0D65C36C815AD3ABULL, 0xE3694EFFBAAA276CULL, 
            0x33560D008B2F5090ULL, 0x693257C315C37FC7ULL, 0xA8DBED710B97F94BULL, 0x78B387A8173992FDULL, 
            0x668ED13AB238203BULL, 0x46306E114A76FD60ULL, 0xA826CF3278963B4BULL, 0xFE007A7AF3EB511DULL, 
            0xDE925748724F3DAEULL, 0xEB415F8B8B45598CULL, 0xC5B427BCF3CDC522ULL, 0x99531CC718EFA088ULL
        },
        {
            0xCDD2A1658C6B5EECULL, 0x589A7CAED128F150ULL, 0x93D37B2292C0896EULL, 0xB51212D83033F94FULL, 
            0xB19BDE09D12EA5A2ULL, 0x3D657022572C60D7ULL, 0x09AC46D1A6CA605BULL, 0xC96861719ECC04F9ULL, 
            0x8E4D02EA1286BE7AULL, 0x177139C56628461BULL, 0x952D0AEF2EA52F1FULL, 0x38C4142DB759C787ULL, 
            0xBC6042F3572E21CFULL, 0xFB5C80A07B6AE5CBULL, 0x406ADA12D19559C2ULL, 0x71BE5A9324802B85ULL, 
            0x4728F8BE9481D62FULL, 0xA299D203AF043C58ULL, 0x16131338C5FCAEDFULL, 0x6D261F1B2726F205ULL, 
            0x9F3C1152C7438C95ULL, 0x7BF9A34D9E70C984ULL, 0x910FADFB930A4B9DULL, 0x53F920D89E956E5DULL, 
            0x37948FFE4DBD84A6ULL, 0x8ADFBF4F33FF0172ULL, 0xB9AFC915CB4EF57BULL, 0x3A87F8909EC06421ULL, 
            0xF93E547D9ECB30CAULL, 0x1C1327EBACDEF398ULL, 0x315B1896F8EEB1FDULL, 0xFDD25701FA49E8A8ULL
        },
        {
            0xC05DBB0C26B8B98EULL, 0xB93815E238989AB0ULL, 0x46D3BC2BB06C8B27ULL, 0x1D96E2F2B073B4D3ULL, 
            0x4323E8A6D2D387DEULL, 0xFD9476D299B29E25ULL, 0x5109D2A45F0A7492ULL, 0xC79E98F7E659D448ULL, 
            0xEB47249F8C349131ULL, 0x654128D7E6902D4BULL, 0x2F89A183146F1882ULL, 0xCBBBD15C9C488ED4ULL, 
            0xFFEE026908595215ULL, 0x6A4948A576AC0183ULL, 0xB8A5C46BD71169A6ULL, 0x279040FA046F02F8ULL, 
            0xD825AAD08449C4C3ULL, 0x64A1E92D493892F7ULL, 0xCF37D919C6619238ULL, 0x1FA0C9A11C3EA225ULL, 
            0x539871E1BE41E2E3ULL, 0x0C8B0726D1C93A85ULL, 0x3E6DEC2A62C01834ULL, 0x8061D077A1386FEBULL, 
            0xB3D45020CC779918ULL, 0x22B8180A8ADD3DB5ULL, 0x86954F8417BB2C5EULL, 0x4936A80CA73EAAD2ULL, 
            0x513D10330166E6ECULL, 0xCF47F065951AF0ABULL, 0x98EF9B22EF6A5761ULL, 0x4A54216AB2484382ULL
        },
        {
            0xB90E663E4AC4D9B6ULL, 0x7A43226F1DBD24D5ULL, 0x2A432033092F764AULL, 0xE72ECEF38BFFE3DAULL, 
            0x57ADC58CD501F5EFULL, 0x1DACC1778F00DAD7ULL, 0xA3C351A219449F4DULL, 0xDF27299E35472A94ULL, 
            0xD4D56C85E741FA00ULL, 0x3DCD335191B799FBULL, 0xCDFFFBF367B96513ULL, 0xC750E4F51F25634BULL, 
            0x3B0D0ED4EE8F8571ULL, 0xECAA95517AA45FDAULL, 0xA001E03C89CCA337ULL, 0x5453A980A5511195ULL, 
            0xF23166FE185679A8ULL, 0x6813EF80E1EFD694ULL, 0x520821D155595A2DULL, 0x9C308C3FB2CF2770ULL, 
            0x6E4F2F1E380655ADULL, 0x76248FD9823C0530ULL, 0xE462798A8CAE6012ULL, 0xA51AAEF509B2A59CULL, 
            0x2A4A9C4FCBC3E82CULL, 0x9EA85B6016A0F50CULL, 0xA81076057F2D8368ULL, 0xAEAD4E1BDA6A0A26ULL, 
            0x15A0EA5DF240FA0EULL, 0x4AA7E63443DFF4E4ULL, 0x02EEA83A1B3D9CDEULL, 0x3170F73F56D9E81DULL
        },
        {
            0x8444C1C79586B90BULL, 0xBA6A6F90A0BAEFA6ULL, 0xC5EAF4F2F826BEF5ULL, 0xAD1DF3B3A3DC3526ULL, 
            0xE5047FF9BA7F525EULL, 0xD042B424D10DEE6BULL, 0xA6A30F81E2068C28ULL, 0x7A36934CAE771048ULL, 
            0x1AB4193732358214ULL, 0x76615AC345A8C91CULL, 0x78F431CB3652FCDBULL, 0xAC0E195C6AB7B042ULL, 
            0xE7C280FAA195A6FEULL, 0xCD7560B8CE7388A6ULL, 0x76202365491F7979ULL, 0x8BF6D758041D9DC1ULL, 
            0xC87B84DFC1484D44ULL, 0x83F582283E7E2F87ULL, 0x5C925DB7C910014EULL, 0x71F8B4A417789A1CULL, 
            0x8049B6D0DE7D990EULL, 0x0CFCABAD259FB119ULL, 0x0FA3E6D7FE6A479BULL, 0x5B9079894CC5A3FBULL, 
            0xC3231AC6F20D423FULL, 0x4D4FBFFF48B63A31ULL, 0xBAD79078D3D3AACAULL, 0x458505F17B7AC2DDULL, 
            0x1F61173351ABEBDFULL, 0x45A7A925F27A225AULL, 0xE74ED7A40D9702B6ULL, 0xBE24DBDFEC27D413ULL
        },
        {
            0x715269790435EF40ULL, 0x5AE8A32829515B27ULL, 0x213F2C72DFA5D186ULL, 0x7BB870B27EF0365CULL, 
            0xEE07FACBADC048D2ULL, 0xF3516EE410E0CAC5ULL, 0x5C8947ED1C678266ULL, 0xD388C823333F0565ULL, 
            0x56FC76B82065984DULL, 0xE9A364DBA8346D84ULL, 0x9B6F6EF0182B6E91ULL, 0x74E2F50925A9CC31ULL, 
            0x5A1CC905CF3BD69FULL, 0xE51595F33384A8DCULL, 0xE7D3EDBB29D7B17DULL, 0x1FAB114D0FCDE769ULL, 
            0x83CAB3056260B102ULL, 0x92C0CCFF598218FCULL, 0x3EF729D2D6C501A7ULL, 0x4D8036235FEB3B51ULL, 
            0x291626F715F4FB1BULL, 0xF1C8D01099BA51F1ULL, 0x86025FA50E3BA678ULL, 0x26500DEA0CE4D386ULL, 
            0xA6511998CAD6776AULL, 0x808329B1742A95CCULL, 0x6BE8291DA8C1D497ULL, 0x04AD05EE0ACE283AULL, 
            0x0A2080CEAE56F3BEULL, 0x5792DAF2830C327AULL, 0xFA8E029CC0412943ULL, 0x7BB7E66DA792C5D2ULL
        }
    },
    {
        {
            0x7AE2CC20E98E8E01ULL, 0xE5672C2E1D65A410ULL, 0x71B53DE069C7FB76ULL, 0xC2AF507DC1955307ULL, 
            0xD83351B3C767DE9DULL, 0x12EA17DD088BE298ULL, 0xADA00BE724A7A8C8ULL, 0x611B9A81EBCD7AA4ULL, 
            0x8562B1352DF0E398ULL, 0x879DF13915ABE5ADULL, 0x58730F3C7F58EDD9ULL, 0x03119D8A750B353DULL, 
            0xCF03754F8B82E6A4ULL, 0x6CD54B101B80EF80ULL, 0xDC1EB6988E9AFA56ULL, 0xBD363F29F1CB1C3DULL, 
            0x4ECD396CD7A8767DULL, 0x891C664C5FBDDCF5ULL, 0x04B6C0D1531D26C6ULL, 0x29F1987BF4D8138FULL, 
            0xB5EE2D646A8BD650ULL, 0x4C3868F0421C9038ULL, 0x1C56994816C09E7DULL, 0x79E2124975B4EB6DULL, 
            0xB5D9EE3EFEC5582AULL, 0x0D5F2188AAE309A8ULL, 0xE79A985B98E05B9BULL, 0x318503C5A1704DC4ULL, 
            0x0EAD896A507EDB85ULL, 0x6F97A8FA099FE1F9ULL, 0x15A6F9807E3CF221ULL, 0xACFA2013E5FA0C53ULL
        },
        {
            0xF40B3955C55D7A7EULL, 0xE5F7C955805EB8D6ULL, 0xABFE081494648E46ULL, 0xC0407C4893615F7FULL, 
            0x744E5EA2FBA34AE3ULL, 0xE4DAB471CBDD21B8ULL, 0x7166DB846C1871F5ULL, 0x821E976C9F6019F3ULL, 
            0xC3C240A0081BF3BDULL, 0xC2035FF6D576C7C1ULL, 0x2CAF08EA580FDB0DULL, 0x43C7D230FB65940AULL, 
            0x5E63CBADC39AC096ULL, 0x0AA034B76AACE881ULL, 0x2FF4C622E40C2DC3ULL, 0xDA76440BCD3CE6B4ULL, 
            0xD57E91F08ED5733BULL, 0x3093DDA29816B839ULL, 0xD43483FC5F68FB7EULL, 0xD1F1DD7442522F64ULL, 
            0x8E4C47429ADAEADDULL, 0x3EF120A09799ABE4ULL, 0x996099550AA604C0ULL, 0xD06B865C7E7B34C2ULL, 
            0xEF385130C218FC58ULL, 0x85C531AA3B1AE809ULL, 0xC91ABAD97B69E5D6ULL, 0xE9E4763E2801775AULL, 
            0x19D2E6F447111CFCULL, 0xF534D72C9F10F606ULL, 0xB27BD2F438B20EF8ULL, 0x261E01BA199E1256ULL
        },
        {
            0x302B5A65D069CADAULL, 0xE469E9EAC3FE5655ULL, 0xAE2D3ED93B2399BCULL, 0x24EE805A26695456ULL, 
            0xC7149146080CF2A9ULL, 0x8482D5C46722861AULL, 0x6A93E315E60E4A23ULL, 0x3A4E392C849FDB56ULL, 
            0x9E95DCC5FED3B0F6ULL, 0x052C3F422DC2052FULL, 0x3335B577AD264481ULL, 0x1AE9327CFD708847ULL, 
            0x851E7479FCA3A362ULL, 0x2317D7134305E60DULL, 0x49AE961F40FB0B3BULL, 0x652171FE63624744ULL, 
            0x267FA0A0A3DA45C3ULL, 0x140677DAB8840CF5ULL, 0xC79093C8C9C0E35FULL, 0x5BE77CB63360B721ULL, 
            0x0A3C61CC8D174967ULL, 0x8D86C8A741BC12CAULL, 0x10EEFEF105CE0E1BULL, 0xE414BEDB5C754278ULL, 
            0xC120421DE14A1254ULL, 0x96D59CD869CF567EULL, 0x2656D6A6236EC3F5ULL, 0x039508B77861D706ULL, 
            0x0305B87B46EDF335ULL, 0x7F929C14E9FED142ULL, 0xA5F15169A4189FF1ULL, 0xDB67B41BCFAEC67CULL
        },
        {
            0x74EEF88FEB5671EAULL, 0x69B33577074FFD18ULL, 0x6EB9D0222EA521EAULL, 0x686E899308D5E4CEULL, 
            0x4B0085612AF788BBULL, 0xE0EBD583E213400DULL, 0xCC0B3CE991235499ULL, 0x711513AF119F190CULL, 
            0x87D0709CBF71DE18ULL, 0x9DCE5FEAE4BCF5DCULL, 0x2662A75424D9E518ULL, 0xDB7D4E8AE038CE93ULL, 
            0x8670876F90187C52ULL, 0xE9769354B7585B26ULL, 0x9DB138151AD69AA8ULL, 0x892ED98AB28DC7E3ULL, 
            0x2293073D743647D6ULL, 0xC77C9B08C0924704ULL, 0x7FFDF2CC2A85075EULL, 0xBF7A8F6DFCB2D51DULL, 
            0x2B77CC37F4B52092ULL, 0xAA36EBDCFB1E6683ULL, 0x25C2AC843B7155E7ULL, 0xA8D1C07E50B4D113ULL, 
            0x8A46D7F0C0DA7202ULL, 0x2B586D91169BE176ULL, 0xA73696EA203D6302ULL, 0xBEB8D1F1058ADC5DULL, 
            0x49AC1F0D9A3E97D5ULL, 0x906065F7DA93DD31ULL, 0x131D074CE25ECB55ULL, 0x4A172F9AC159E185ULL
        },
        {
            0x89AB287AE529BDE4ULL, 0xF336D3FF6573C893ULL, 0x6FDD43E75933E421ULL, 0xB559AB2F018239A3ULL, 
            0xA8CDF86A848A8AA1ULL, 0xC9DC8F221A3B30B6ULL, 0x33A3CA18CF1FC342ULL, 0xDEFDE792ADABFF46ULL, 
            0xFFE74E9667982B86ULL, 0xDD7CA657B24632ADULL, 0x06DD6FDFE90B7895ULL, 0xD11B0594F97108E0ULL, 
            0x2ECCE49CA92F04ADULL, 0x81356D8485D86B46ULL, 0x88CF2AEC5E66A847ULL, 0xE1A4AFFCE1009FE0ULL, 
            0xCD3DF6C75BCE474AULL, 0x4BD1D9168D34E77FULL, 0x7A6457E0DBB4ED71ULL, 0x4DE5A0E164A8308FULL, 
            0xB409BD1AE40F2F08ULL, 0xC16FD1F7D60DE5E9ULL, 0x11440392A31108D0ULL, 0xDFBA6310A152494AULL, 
            0xEA0B445328F080C2ULL, 0xCBA93F8DBB4B9A79ULL, 0x1F2B3E0BBF066ADDULL, 0x9714146ACBE7681BULL, 
            0x5F5607809CF51A6DULL, 0xCFB18BE41041F288ULL, 0xC60C964C839BE0B8ULL, 0x48200D377E325AEBULL
        },
        {
            0x6B7852CB30DA61FCULL, 0x7D47063849D629EBULL, 0xA420085890D0D1D8ULL, 0x09D20454D5D71BF4ULL, 
            0xED26A5795AE6FEB2ULL, 0xD6BB4FC4C75A24AAULL, 0x16E33E7DF1172638ULL, 0x2C5D666E8EA42CB8ULL, 
            0x4359B84938A366ECULL, 0x384155ABDBBCB41BULL, 0x085F49C3F73DB86AULL, 0xB8592EA612808965ULL, 
            0x635475246AE51DE2ULL, 0x7A267BCDC106B77EULL, 0xC13084E11E1F6F73ULL, 0x6CE5FD98B792F84CULL, 
            0x0598028CAEBB7CD4ULL, 0x58ACE9CEBFBC157BULL, 0x08F14C808A526682ULL, 0xAC92C3683A4E54B5ULL, 
            0xC7C2E04E14A0BAEBULL, 0x91DE9D4840CC9D28ULL, 0x6E95B82014047659ULL, 0xA090F99B2432A8A1ULL, 
            0x110B89BBF9EE4F8DULL, 0x184B4F6500B7492AULL, 0x788DDAC07A953594ULL, 0x3FC0F098DBFF4A0EULL, 
            0x6C6647CFA265C21AULL, 0x96FE9136472A13E0ULL, 0x683CC1A816E37A7EULL, 0xB0D60C174452917FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseHConstants = {
    0x046E328140FD5925ULL,
    0x20ECBA7D1DA8C3FDULL,
    0x75DF7FDE9B959DD0ULL,
    0x046E328140FD5925ULL,
    0x20ECBA7D1DA8C3FDULL,
    0x75DF7FDE9B959DD0ULL,
    0x9F6D9FA64F255B8CULL,
    0x96AC903DE84C8227ULL,
    0xFB,
    0x97,
    0xB4,
    0x89,
    0xDC,
    0xE5,
    0xA9,
    0x9F
};

