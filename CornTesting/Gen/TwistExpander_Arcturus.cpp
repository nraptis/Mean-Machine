#include "TwistExpander_Arcturus.hpp"
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

TwistExpander_Arcturus::TwistExpander_Arcturus()
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

void TwistExpander_Arcturus::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xCA63E7C2A452A9A9ULL; std::uint64_t aIngress = 0x8DA60D330AA31430ULL; std::uint64_t aCarry = 0xA501ABE0993144C9ULL;

    std::uint64_t aWandererA = 0xF1DC1CC2B14D1B76ULL; std::uint64_t aWandererB = 0xD11E5F39E194F9EAULL; std::uint64_t aWandererC = 0xC749FFD88F536D5FULL; std::uint64_t aWandererD = 0x8DDB3F54C3AD71FBULL;
    std::uint64_t aWandererE = 0xDA0138D3318F30ADULL; std::uint64_t aWandererF = 0x89F076451E80FB8FULL; std::uint64_t aWandererG = 0x809979B79EE18097ULL; std::uint64_t aWandererH = 0x80B16DE36F37FCF1ULL;
    std::uint64_t aWandererI = 0xFCBFD89F90D820A2ULL; std::uint64_t aWandererJ = 0x8FFF11BFECD55E65ULL; std::uint64_t aWandererK = 0x8897C5B60373B619ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13130252716494720904U;
        aCarry = 9454496750392841259U;
        aWandererA = 15163476576981361514U;
        aWandererB = 13249123487455533742U;
        aWandererC = 14042899213138684312U;
        aWandererD = 17002418174113099115U;
        aWandererE = 17389662146010373575U;
        aWandererF = 15831004594807201788U;
        aWandererG = 16589060066349077676U;
        aWandererH = 13595586763824010169U;
        aWandererI = 12349498219364974254U;
        aWandererJ = 15283202598288472656U;
        aWandererK = 11974635972745214095U;
    TwistExpander_Arcturus_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Arcturus::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC46262129CE436C5ULL; std::uint64_t aIngress = 0x9A1CB033C7E935EBULL; std::uint64_t aCarry = 0x89BCC1A3A5135842ULL;

    std::uint64_t aWandererA = 0x8185A6DC86BB743AULL; std::uint64_t aWandererB = 0xCA35E021188581A1ULL; std::uint64_t aWandererC = 0xCC1C882A47188BA1ULL; std::uint64_t aWandererD = 0xDE363E4BE404672AULL;
    std::uint64_t aWandererE = 0xF248A6BCC6C5A113ULL; std::uint64_t aWandererF = 0x89FAF4E3FCACE530ULL; std::uint64_t aWandererG = 0xD0A3BAB0DADD3EADULL; std::uint64_t aWandererH = 0xF113D45524D79671ULL;
    std::uint64_t aWandererI = 0x89E8599705CD4B02ULL; std::uint64_t aWandererJ = 0xB8B52B4A45DEDB39ULL; std::uint64_t aWandererK = 0xF8F61A5E2D46C55CULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11831869819684921149U;
        aCarry = 11918789937806604169U;
        aWandererA = 13726568089811128816U;
        aWandererB = 10425522404375552897U;
        aWandererC = 11562555105497806867U;
        aWandererD = 17703270289525457776U;
        aWandererE = 15759968178633707322U;
        aWandererF = 15741201351289875377U;
        aWandererG = 9577905245447791284U;
        aWandererH = 18141970995664692281U;
        aWandererI = 11973621304771955845U;
        aWandererJ = 16752227177486962568U;
        aWandererK = 16343185253450715376U;
    TwistExpander_Arcturus_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Arcturus::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xD13FA0FE447E0F41ULL;
    std::uint64_t aIngress = 0xEEABC307065311F0ULL;
    std::uint64_t aCarry = 0xD74E5BBB81901692ULL;

    std::uint64_t aWandererA = 0xA30ECD0F9DE2F07DULL;
    std::uint64_t aWandererB = 0xF11AE45CBEA45C28ULL;
    std::uint64_t aWandererC = 0x9FDD2942376ACC69ULL;
    std::uint64_t aWandererD = 0xD712A00040424867ULL;
    std::uint64_t aWandererE = 0x921485274DC94DF9ULL;
    std::uint64_t aWandererF = 0xBD007C7B435FD1ECULL;
    std::uint64_t aWandererG = 0xA634D39243AFCC4FULL;
    std::uint64_t aWandererH = 0xB801C1FBC2D949BCULL;
    std::uint64_t aWandererI = 0xD251EFF105F0D9D4ULL;
    std::uint64_t aWandererJ = 0xCC54BF90F2A47655ULL;
    std::uint64_t aWandererK = 0x8C9C27BBF982EC12ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
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
    TwistExpander_Arcturus_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Arcturus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 10 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1851 / 1984 (93.30%)
// Total distance from earlier candidates: 16701
void TwistExpander_Arcturus::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 101U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 664U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1098U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1968U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 50U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1902U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 639U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1167U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1456U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 684U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1724U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1841U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1885U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1815U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1371U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 620U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 490U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 326U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 256U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 723U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1444U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 891U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1054U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 711U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2019U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1215U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1786U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 258U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1982U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1850U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 930U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 488U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1123U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1243U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 34U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1637U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 99U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1577U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2004U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1479U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 51U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1331U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 925U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 154U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1917U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 333U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 748U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1816U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 83U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1734U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1771U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1117U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1903U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 622U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1038U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 743U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1730U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1177U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1498U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 561U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1708U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1415U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 313U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 959U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 648U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 90U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1045U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1195U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1406U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1199U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 973U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 918U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1370U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 788U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 646U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 708U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 296U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 13U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 605U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 540U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1466U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1202U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 645U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 519U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 180U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 678U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1289U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1134U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 654U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 875U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 629U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 425U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1735U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 148U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 737U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2027U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1431U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 591U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1409U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1183U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 632U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 232U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 124U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1471U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 160U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 963U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1527U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1950U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 282U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1362U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 371U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1428U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 728U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 701U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 933U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 638U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1610U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 150U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1667U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1440U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1325U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 582U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 389U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 894U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1548U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1818U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 426U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 889U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Arcturus::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xCB4EB8E18E2B07B6ULL; std::uint64_t aIngress = 0x90B9E0A7F7879907ULL; std::uint64_t aCarry = 0xAF49485B95A04C9AULL;

    std::uint64_t aWandererA = 0xA9FD9A8294BCAFEAULL; std::uint64_t aWandererB = 0xBE9F73F5D27944EFULL; std::uint64_t aWandererC = 0x8DD5E96A126956C1ULL; std::uint64_t aWandererD = 0x9F1CE9C587185206ULL;
    std::uint64_t aWandererE = 0x8C36332DB493F1E3ULL; std::uint64_t aWandererF = 0xDF13C912B3A7A4F5ULL; std::uint64_t aWandererG = 0x8EFAFACD68329D77ULL; std::uint64_t aWandererH = 0xD7C6AAEF3ED77C2FULL;
    std::uint64_t aWandererI = 0x9A8AE8DE589A5ACCULL; std::uint64_t aWandererJ = 0xC8A8CE5FE0B72E34ULL; std::uint64_t aWandererK = 0xDFA1C1FC20B69A52ULL;

    // [seed]
        aPrevious = 15684101542781280852U;
        aCarry = 13648471537550019630U;
        aWandererA = 14966928533508499748U;
        aWandererB = 17846760633540542025U;
        aWandererC = 14614562975294748802U;
        aWandererD = 10849149818707062666U;
        aWandererE = 16639583752618421581U;
        aWandererF = 12242714500710232040U;
        aWandererG = 17463515101488192393U;
        aWandererH = 15545751981909547459U;
        aWandererI = 9967907590462920394U;
        aWandererJ = 18050285520071864146U;
        aWandererK = 16703058452071935931U;
    TwistExpander_Arcturus_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    TwistExpander_Arcturus_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Arcturus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 10 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 5004; nearest pair: 494 / 674
void TwistExpander_Arcturus::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2622U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5147U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 770U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3306U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2483U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8129U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5086U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5275U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7210U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6553U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7064U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6392U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2207U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2630U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3429U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 985U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 999U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1561U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 250U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 90U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 231U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1972U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 176U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1729U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1991U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1640U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 403U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1216U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1915U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1643U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1577U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 743U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1100U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 842U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 787U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1433U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 10 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 4986; nearest pair: 516 / 674
void TwistExpander_Arcturus::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7563U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4797U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3039U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7810U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7884U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7029U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7628U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6498U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1815U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6970U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2874U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6407U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2321U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1195U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3578U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6044U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 218U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1020U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 830U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 467U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1048U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 27U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 472U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 795U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1240U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1214U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 915U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1627U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 583U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1490U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 82U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1411U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 459U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 29U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 170U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1040U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseASalts = {
    {
        {
            0xC9957C2770F2676CULL, 0xD134BEA38DBF1336ULL, 0xA58C8820DB4FDDDAULL, 0x5FBA281FA3751BF0ULL, 
            0xA12F0301C3E1CFCDULL, 0xEE3DBA18CCC6CB20ULL, 0xA18DF323D12663EDULL, 0xE3FCCECA1BED23A8ULL, 
            0xBB33C299F711ED76ULL, 0xF2FABF33814FAE38ULL, 0x7D1C877760F2BEA9ULL, 0x09200CEB23517671ULL, 
            0xA8AA5C581BA56254ULL, 0x46F9D3171D7ED087ULL, 0x4A11D0B88DC78593ULL, 0xE3AF9D95B2C2FD47ULL, 
            0x25DFB0DFCC55EAD5ULL, 0x9E1B6C4F957B9AA5ULL, 0x866DC79451975BE1ULL, 0x8D90332AA66DB2D3ULL, 
            0x655A9C0119C3E939ULL, 0x4E61AAFB8B6E70DAULL, 0x7C8DBBB7E283E18DULL, 0x82782A50F28030F9ULL, 
            0xA5779077480634FAULL, 0x399D0E20FDE60720ULL, 0x6E6268DC66BECF75ULL, 0x98A8E2B43DAD98E5ULL, 
            0x618E565A070C989AULL, 0x897D7096DABAF15FULL, 0xC176398DE9BE127BULL, 0xDC256EFB7B079E11ULL
        },
        {
            0x69DE38A2414B4F87ULL, 0xCC7A1E539BC401A6ULL, 0x097AFF0D76360ECCULL, 0xCD1C557F8489092AULL, 
            0x2F34512FEAB8DA7BULL, 0x1EAED723546BA03BULL, 0xBFC5B2365C69FF81ULL, 0x743B3D0F09DDD0EFULL, 
            0xC83DE347CD88212EULL, 0xC4DF2DED54792BAEULL, 0x5ADA19418C7E8263ULL, 0x571C5E1282CC02BAULL, 
            0x088CFECE1D508BB4ULL, 0x5A0285B1084BFD76ULL, 0x57029E2F5F79CA44ULL, 0xD4B58894A3BE7E5CULL, 
            0x687870571D272372ULL, 0x9A969BF295F2F91FULL, 0x9D5CA640C609006FULL, 0x20ABB290AD53E544ULL, 
            0x112A5AD999B93D96ULL, 0xD222BF672FAD25E1ULL, 0xEBC49A0687687DE6ULL, 0x98156CF842B3162CULL, 
            0xA09094D84199B2A4ULL, 0xA11F076BA35063C1ULL, 0x184C05967F11E7DDULL, 0x2447E74ADCDD6E4BULL, 
            0xC30BE066448BBA92ULL, 0x5CD0FCF2C5F5C4A4ULL, 0x6AEA907248493D49ULL, 0x64FEBE844DFC9FBAULL
        },
        {
            0x5659B18F34D00859ULL, 0xF7BDB14B981996F3ULL, 0xBE79F700D51D7C3DULL, 0x5442270999E2B335ULL, 
            0xCE4656F2F0892474ULL, 0x39702A66A1C9CBFAULL, 0xEE26BEEE87D17166ULL, 0x2EB7B52F2AE0FE83ULL, 
            0x8C8F0CD6D7FAD8D8ULL, 0x2C2C4424FEBE1F29ULL, 0x95F168D68DB54C5DULL, 0x70E023C5F755527EULL, 
            0x8E5CE51B74EBC6A1ULL, 0xDA0F726B8DC952A5ULL, 0x181E17FD173E5AF9ULL, 0xAC9B97C19E10DAE8ULL, 
            0x6443FE05E4B35D6BULL, 0xE9CAE9B99ECB2207ULL, 0x44F2A1FCAAF909B6ULL, 0xB1B9BB95501D2A80ULL, 
            0x8757809FDBB96F4CULL, 0xFF7EC0B3D8B4C650ULL, 0x417937524E5080E7ULL, 0x972740545741A039ULL, 
            0x7737770B567D631DULL, 0x3BF217CCC404485CULL, 0x02B7252763D3FB3DULL, 0x665C4AD281802E43ULL, 
            0x24917EA29515AD55ULL, 0xBD19FEA25F562B12ULL, 0x554C85AAAFC9DAD4ULL, 0xC2C0DB52AD2DF4C5ULL
        },
        {
            0x85CC05E60C223071ULL, 0xFF4A84B9862B1445ULL, 0x03DC477CD48E1ACBULL, 0xB2A2CE6B23663783ULL, 
            0x77EC3B300489806FULL, 0x288A8410A954DE98ULL, 0x506353F211F543FBULL, 0xC6DBD056936602B3ULL, 
            0xA1071ED6C139F98AULL, 0x42B303A217E003B0ULL, 0x6C6C64F584568FD6ULL, 0x4CA4C1F92DC3121DULL, 
            0x9CFBD76CA0C238D6ULL, 0xCF30FDFA27E34996ULL, 0xE6E5D6FBC5A9C3BFULL, 0x97B7DC6AA4A5F336ULL, 
            0x961AEB146F0EE937ULL, 0xE68D3AC1B3BE1406ULL, 0x846E23A77E5E6572ULL, 0x3C6BD6C520013043ULL, 
            0x1A57C5AC349A8D7FULL, 0x67CA7B605FAD4331ULL, 0x105026C02A9C001AULL, 0x129981A0A509A3DFULL, 
            0x1E17C9FB5C32F38DULL, 0x42F47C44F8981703ULL, 0x560D14FCCEAEFED5ULL, 0x8E25FEA22D909474ULL, 
            0x5E2444343EE6ECDFULL, 0xF3115518EFC24AF9ULL, 0xDB1D9BCFD0998D05ULL, 0xB78D3779DE84600BULL
        },
        {
            0x8D3E2B5C06C91C9CULL, 0x740802F02548BE9DULL, 0xE0A8094DA3718DB5ULL, 0xBF6EA324A811EF61ULL, 
            0x08D4C709EE1CB39EULL, 0x1AB4E7A013B9F267ULL, 0xE5F53F4A427BACAEULL, 0x5B55F8B2E273BEECULL, 
            0xB7CFF7256C1004F7ULL, 0x32B1809906834F94ULL, 0xAA2819A82CD8549EULL, 0x7984823E26509B48ULL, 
            0xDE12607AC32E0C91ULL, 0x10816E0F0C9C6751ULL, 0x6D38D10515ABF636ULL, 0x387B769BE5A4C072ULL, 
            0xE81C3165EC95F11CULL, 0xB99B0EBC214A676BULL, 0x9BC2C7B6B3981F60ULL, 0xA46CE0E07CAA5C4DULL, 
            0xF32E96E8DF66D149ULL, 0xA171B25342FE0343ULL, 0x38EEC0389C2643F9ULL, 0xE340776F37BCEF95ULL, 
            0xAC756DA98C7889E5ULL, 0xFCA77A34804831E0ULL, 0xC90F37721D4A373FULL, 0xE1C7CA59ED1A9A5BULL, 
            0x6844682AA84B1BAFULL, 0x86104AB0956CA2AEULL, 0xF3CB59E087CD6D4DULL, 0x119E24663C6DA5F6ULL
        },
        {
            0x3702D11B14D9FD80ULL, 0x045D11EE45B38E7FULL, 0xD0A414E3C2130999ULL, 0x4D508C15EC742AA2ULL, 
            0x91AF2D367E92FFDAULL, 0x44DD38969389BE40ULL, 0xA7511C5E712C3600ULL, 0xA058981F4113D0ABULL, 
            0x0E1B40D9E974691FULL, 0x7D794FC318A5E80EULL, 0x7107A4F583834160ULL, 0xD06884D0BFA46C5EULL, 
            0x635294BB0CD7CAEAULL, 0xFE1AF2218C55E666ULL, 0x951DEAA946075141ULL, 0x7F045FC88311D75FULL, 
            0x4729831EF1B3B8C1ULL, 0x7CBA631FE879CB40ULL, 0x824BB6C2F48D5FA1ULL, 0x3E00474004880512ULL, 
            0x632781F9C8F213C3ULL, 0x9DBE9708C2D5E76CULL, 0xC186846F2C05E281ULL, 0xC0425A3C33856EA7ULL, 
            0x69F3EFB901ECF503ULL, 0xB89BDFB7BB5F338DULL, 0xF3A1E81738CDED53ULL, 0xD4806DBEA8145AFCULL, 
            0x0BB2B15A77AA0381ULL, 0xB502268F815BB584ULL, 0x7D17D5D49CE18A1FULL, 0xF7E916EC3B558E66ULL
        }
    },
    {
        {
            0x228D52466B7EFE52ULL, 0xED4F8678D3E8DBF2ULL, 0xCB5008BD2279E848ULL, 0x03A4FB3AE847812EULL, 
            0xF6EB6588637CB1DBULL, 0x8D531B3589A6C906ULL, 0xB7651B7D14E05002ULL, 0xBD9E2E77C9560465ULL, 
            0x2472EE229C9E611CULL, 0xCFCCB5BEE08199C0ULL, 0x158E318C92338817ULL, 0x7801EB289E8259E4ULL, 
            0x89B848FC1B033331ULL, 0x15BB34A5E4954351ULL, 0xADEF0179E09C96EBULL, 0xA57B39A1FA2917D1ULL, 
            0x29D02FFD32644C91ULL, 0x71F872FAAC8BE307ULL, 0xAA300E5BE27F701CULL, 0xC0C87C88BDACB8B9ULL, 
            0x0B29266C36692FB4ULL, 0xCE3B79C2E90CAC91ULL, 0x40C28BC380D068E2ULL, 0xB96E4750355CFA5FULL, 
            0x2A4CD7D9385CF9ACULL, 0x69E0662F579E437CULL, 0xB7AAC4B53E24EA9CULL, 0x6BCED689F8629FDBULL, 
            0x929F633F8D21532EULL, 0xF2164481643A983BULL, 0x94ADD05853B686FCULL, 0x28B78D1080A3E3D1ULL
        },
        {
            0xD06979290BA9A724ULL, 0x46F4236C043F9B2BULL, 0x15F23AFC8EF1B4F9ULL, 0x31571442E8F9806CULL, 
            0xC9EA6D147CF28F57ULL, 0xD3D5696BFCB5B05EULL, 0x616355A97387E1C5ULL, 0x10924F667A2059B1ULL, 
            0xE87206E57692DA9EULL, 0xDA566C78B9203C2AULL, 0x236F6EEBE67978CCULL, 0x6FE0D7A60CFF3BD8ULL, 
            0x798AD8C148B0259EULL, 0x268801FF876F344DULL, 0xEAB1EC999A878DFCULL, 0xB6EA62CB2BF42566ULL, 
            0x594C8F024003590BULL, 0x86E2732993310444ULL, 0xB98B19EDB0BED085ULL, 0x36DB42CDA02226D0ULL, 
            0x790523C8BB7BA1B9ULL, 0xCA663D86595768F5ULL, 0xC3F94494ED0E2A57ULL, 0x8214CCCB5CF1CADDULL, 
            0xB6B2D6987F8F4C6DULL, 0x8F0D02A65784F127ULL, 0xAB358D0A270A4248ULL, 0x6A53EB0C736DA712ULL, 
            0x9AD7272EF5D71112ULL, 0xA20E4EB4D63A25E8ULL, 0xBCE63140C3B3C396ULL, 0xDD600CD1D963F28CULL
        },
        {
            0x71F47B915D8D8C1FULL, 0xD0CD10E26301BCACULL, 0xD40046C4E23AF19AULL, 0x78FADE1A076A5DFEULL, 
            0xC32960286E657513ULL, 0x369C00440643CAFAULL, 0xDBF947AB4110D05FULL, 0x9D61511E2856062CULL, 
            0xD4212B543F1E47FEULL, 0xBEB24433DA08B497ULL, 0xD4B8C34C11B34B6EULL, 0xDE809BE2ED0B5DB1ULL, 
            0xA02808D2F32C7FF0ULL, 0x328BA3F355F4873CULL, 0x67A3D4F4079FC5B3ULL, 0x845259523D6FE989ULL, 
            0xC2FC5E0AFB1DB0D8ULL, 0xEF8439FE399272D0ULL, 0xA9D3D84A3892138BULL, 0x84630D66B69C7D64ULL, 
            0x10C395E2C5899349ULL, 0xBE74FD4029FABCA6ULL, 0x5A3121B36FE1099DULL, 0x5252D9A8E59CBE42ULL, 
            0x98DA537632DB6C52ULL, 0x4BE55F241349C093ULL, 0x044D68DDFC8FB31EULL, 0xDC12F43DF40716DEULL, 
            0xD47C1A363C2ACE72ULL, 0x9E719A75DFBC41D0ULL, 0x519118599424F3D3ULL, 0x45FACA37FF7BC4A0ULL
        },
        {
            0x8BCF7561FABC7851ULL, 0xF527CFFCED2A85E7ULL, 0x6DFC5EE0CFEB0164ULL, 0x9E88D8BCF033C7FBULL, 
            0x5D1E8BFA1E1446D1ULL, 0x575A944BC5C7EAB5ULL, 0x4290CFC715AFC1BCULL, 0x1BB2C3089713BD62ULL, 
            0xA8CC7B0719708079ULL, 0xEAC70DFFF1009E0CULL, 0x3F21B25741AC1429ULL, 0xB9BDFF618B6FEA59ULL, 
            0x55B5559D3CAA4357ULL, 0x31021E9EE3A65D91ULL, 0x3FA7346F503F7855ULL, 0xD7AE945DA8435F0CULL, 
            0x64986AC14C9DD112ULL, 0x31DAD9D531A21366ULL, 0xC04B863F594EC742ULL, 0x80E654F18742B6F6ULL, 
            0xBA226A5CCC89B825ULL, 0xD5D2ED4D79A35D51ULL, 0x66AB1EBB5F77586EULL, 0x798C694F0258D495ULL, 
            0x61D887C426C7F493ULL, 0x38337B4108B12228ULL, 0xAABC2875A26C73F7ULL, 0xDE9555B20469ABAEULL, 
            0x09DC7D770BAE38C1ULL, 0x28BDB3CB3ABE8CCFULL, 0x7EA1CA0E9A2ADAFDULL, 0x3DC6A3F2457504B8ULL
        },
        {
            0x3C05B4B66D61AB90ULL, 0x1B5973E4098D14C0ULL, 0x4DB3087A5D21B394ULL, 0x9656DFF5EAFDC773ULL, 
            0x5DB9D08CB1C78B56ULL, 0x5848A9EF8860621FULL, 0xA028D401BCF6819EULL, 0x677DA10B78F95BA5ULL, 
            0x3A1864A7D942DC19ULL, 0xF02B770F1D69D819ULL, 0xBA4E0FF7F32EF6C3ULL, 0x6152E154CE0A9A19ULL, 
            0xF531F91232D9248EULL, 0x70AE346216FFE09BULL, 0x28AB80DBE63E27BAULL, 0x92FF6632D028FB8AULL, 
            0x297DC7BAEECC71DFULL, 0x1981FD68A0F8504BULL, 0xE1F4A36160120C6BULL, 0x1B8578D3AE29FFDEULL, 
            0xF204D7B5B782D349ULL, 0xCBBBC527BFE3D6C1ULL, 0xECA66C3E271919A0ULL, 0x05E68F24FCF84723ULL, 
            0xC5FBF4E1E7212A67ULL, 0xE6D0204AB428805EULL, 0x96BF72256A936F47ULL, 0x27AC74281287D9E8ULL, 
            0xBE1CCE7A821FEC53ULL, 0xC81069384F49FD82ULL, 0x492B0A7A5C6A6899ULL, 0xB1E1733ECF3A6BA3ULL
        },
        {
            0x1450411AE2FE9741ULL, 0x9A7104E0E82F68B9ULL, 0x80838091BB3AEBDCULL, 0x13FD38D10E31BDD3ULL, 
            0x82D75FCF55660D59ULL, 0xE162452E762543FFULL, 0xA2D6B325CB5665D5ULL, 0x50D2D23AF214F808ULL, 
            0xF6096A6AC21912EBULL, 0x324342A9D3AD4F7AULL, 0xC2DE18CB154B2E53ULL, 0xC9C0E5716847B837ULL, 
            0x2AE3C14DC272FB76ULL, 0xF50B7EAEB6C4C24FULL, 0x98E7501774D45398ULL, 0x2294FEDA4ED396CBULL, 
            0x9A66C56CDD8D0AC4ULL, 0x2BA8649DBBBBBF50ULL, 0x56A03751E42F4CD9ULL, 0xA7E878272E17A3F4ULL, 
            0xEC8D787F9A975F1BULL, 0x0E58A8238741A171ULL, 0x844B744467459B9AULL, 0x0FB6B9A623E6057FULL, 
            0x588F6515430CA5B0ULL, 0xAFE2759382DCA4EEULL, 0xDD01E03C739CF607ULL, 0xA408A1E75D57803CULL, 
            0x031CB158B830E411ULL, 0x5BDEB99002FB796DULL, 0x9E5FE2021EFE88DBULL, 0x42C999283CC2F7D0ULL
        }
    },
    {
        {
            0xC9DBCA623ADAADBDULL, 0xCEDB4CCF7107ABC9ULL, 0x8B13B6481AAD8438ULL, 0x386AF7170F2AD4E0ULL, 
            0xED15C99489548B4FULL, 0x1FA1E28505AE5C99ULL, 0x615CC335061A5DBAULL, 0xA39FBFA9840CF8A6ULL, 
            0x69E92E79F788F4FEULL, 0x7123EC659927681CULL, 0x61A65CA9D012DAF8ULL, 0x303A8D3729BE4A40ULL, 
            0xEC3B09D3E68D1FFBULL, 0xFDCC7AF6167965B7ULL, 0xC4797CF2C3B94078ULL, 0x0AEA07C794E45493ULL, 
            0x95224AA5EE064CC1ULL, 0xEB8211C8199F0698ULL, 0xCD30A7C44F8188F9ULL, 0xF3401EDA5477B7E4ULL, 
            0xDFF06E051908A335ULL, 0x931A71CEF4ED3970ULL, 0x37D4D040FCAE368AULL, 0x32C69F6813B28E85ULL, 
            0xB750383A2DCDD2E5ULL, 0x71BFF10A06948E2FULL, 0x15FC9BA261B552BBULL, 0x09E82D736AE65067ULL, 
            0x29F8E3FE93CFF9B1ULL, 0xD46702DA9EC13177ULL, 0x3A711E3086EEBE15ULL, 0x10F201E2BEBE1B60ULL
        },
        {
            0x94E04F94587645DAULL, 0x2F5A879CCDF83063ULL, 0xA1C19866188E6FC5ULL, 0x513750514D4DA294ULL, 
            0x6994A319496926E8ULL, 0x74DEFA3E263A8048ULL, 0x2D6B297E80D9FDFDULL, 0xF90AA9A1A2DB1FB5ULL, 
            0x21E0DDEAC0FF9AA9ULL, 0x9AC1C3A4F8074AAAULL, 0xF5FCBCEF26BE4DEEULL, 0x70BAA06BBE35297AULL, 
            0xF64A08815D090855ULL, 0x5A8B8AA92EB7E0C6ULL, 0x61337DF5B834B5E5ULL, 0x09481A354529096BULL, 
            0xBA9ECAE5C118D5EFULL, 0xC0C4C47D889687DCULL, 0xE779DE559B7A8338ULL, 0x33C3127CB030967CULL, 
            0x44AB36F0BA9ACC54ULL, 0x935E716BF0AF5B98ULL, 0x619CEB2BD8FCE93BULL, 0x3B4998908C24C2EFULL, 
            0x5BF809610C5100FAULL, 0xAE04B4F4E8115DC6ULL, 0x5740B485BE7D0F22ULL, 0xE97BB28211CECCC2ULL, 
            0xD25BBB4231721A6AULL, 0x4EAB2CCC38293E73ULL, 0x5E41B714BF9108ACULL, 0xA6636C794EA22232ULL
        },
        {
            0x3E5B8F34B4B7B4FBULL, 0x6151E6000BAE2AC2ULL, 0x7616C9A618834DA1ULL, 0x56DF7EAB3A57AD2FULL, 
            0x38E2FCC53320D92EULL, 0x9C59F565B848A632ULL, 0x05C7E71CCDD47175ULL, 0xDD8927871B30E901ULL, 
            0xD696A0BCE022FAC2ULL, 0x3C4E6EE7F91989CCULL, 0xF8FA32821835E9A6ULL, 0xD4E2FD88401A42E7ULL, 
            0xA97310F4B6D21C84ULL, 0x8D27D443BF085859ULL, 0x1D09BE3ECA9CE0C7ULL, 0x0687662827D97E70ULL, 
            0xBFBACC7FD313E640ULL, 0xF10D09CD4871478DULL, 0x3955F7ED371D69BAULL, 0x547B4535A80A4954ULL, 
            0x731C30D7CB0C83FAULL, 0x192611947FD291A5ULL, 0x9DE6029AB91E73EAULL, 0x5A4E12AE5A659184ULL, 
            0x0B8DAD39042CC7E1ULL, 0x75E117B6DEFC8517ULL, 0x2269CDFB2A15B88CULL, 0xF5A4578A840811D9ULL, 
            0xE431F469AE2203F0ULL, 0x97C402740CD1F0A2ULL, 0xEB79D00E77F5A79DULL, 0xEA0E3147C59C889DULL
        },
        {
            0xF9DFCFD42B28011DULL, 0x640D62D7F9001665ULL, 0xFCF6DFE8D569E3F2ULL, 0x0CEE8B02E70E5175ULL, 
            0x255A6733E39BD0FAULL, 0xBCFCA87E38CF3133ULL, 0xB704688827669D90ULL, 0x9E4F46157FEF9A69ULL, 
            0x208A4A724D63FF38ULL, 0xB2C72393CBEB0489ULL, 0x284EBA92FC67D5CFULL, 0x6F63420EA48E421BULL, 
            0x09F382C909266687ULL, 0x637B014EE2EB0843ULL, 0x175FF7EDF9B0E0B2ULL, 0x557B73C396629898ULL, 
            0xB8CA41624054D59EULL, 0xCB7FA5A3FE1996E2ULL, 0xB52AEDF95979141FULL, 0xFE8B05F40E5C2B7BULL, 
            0x46AAA5AE17441478ULL, 0xE178A2A4399D4380ULL, 0x3F4E3234BC6B5B6CULL, 0xD7BA621FB685AE88ULL, 
            0x29C0174FF45E8727ULL, 0xE3C2E50E01C42DF7ULL, 0x6271CA64FAF26B7EULL, 0xE424A34D059AF0B8ULL, 
            0x1BF33434F0FDBB69ULL, 0x5440DC673010A4BCULL, 0x519841892727F14EULL, 0x705062781980F961ULL
        },
        {
            0xD76EDEC87E18ECAAULL, 0xDAF37B03E8BDD038ULL, 0x741A6CE6725CAA48ULL, 0x3C0571778FD66A2EULL, 
            0xC5F9C1D7626AC8FDULL, 0xA05A5AA8850B73D2ULL, 0x52C00F5B3E798DC3ULL, 0x03F4E2A35A82CB3AULL, 
            0xDE3798515F7C816AULL, 0x7BF573EF79FD4D20ULL, 0x559ED107EE250C58ULL, 0x5A71F07D44D3996DULL, 
            0x0E3D8106AD3948F5ULL, 0xE1DBF097A1602616ULL, 0x8DFD97BE2136B232ULL, 0xC74F550827CA8FA7ULL, 
            0xB1C29924DA7D4685ULL, 0x81A8CB343196DA23ULL, 0xA304C24ECE8D3595ULL, 0x89CC1D326B550676ULL, 
            0xB262F550877A2235ULL, 0x770BC303F1AD0D4EULL, 0xE54353B8145D828EULL, 0x37A4E81B514E9407ULL, 
            0x913DD30B8CE6D51DULL, 0x6BF7128F81A41E88ULL, 0xB8911D58A42D74A2ULL, 0xF1A0F21AA9B86D68ULL, 
            0x16197F2896DDF975ULL, 0xDCD4094EAE9EC4CCULL, 0x026F6ED1DB19EEDBULL, 0x50ECAD7789458A87ULL
        },
        {
            0xE6F6816D0D88ACF5ULL, 0x8E91F74959B8834FULL, 0xC14F6AC8B0343B4FULL, 0xE5B213EA1B690FF4ULL, 
            0x250676DD44858AE0ULL, 0xFCAC12D7B1B361D3ULL, 0x9D1C702C142E4277ULL, 0x861A2DA722C3EE31ULL, 
            0x3D21658A27C0598BULL, 0x91D46F7A3728FAD3ULL, 0x5A44CC73F7D04BC2ULL, 0x9966455FAF37E4BAULL, 
            0x49E2E6A9608A25E6ULL, 0x22BC827E4A446FC4ULL, 0x04EB9731B53CCC14ULL, 0xF1C59E14B01A1DC0ULL, 
            0x6703B6A75F4D048FULL, 0x814B68C8BFD63086ULL, 0xFD4418AB58A5366AULL, 0xF5D5AF41E5D83281ULL, 
            0x6D3F2C9DFC8427FAULL, 0x0CA05860D90A7D18ULL, 0x0ECCE859C5B1F974ULL, 0x0FC77C47D2AC8FB1ULL, 
            0x45972FC235DCEED5ULL, 0xDDEDBFAE5AA43CEFULL, 0xAE6D57ABB4DEC269ULL, 0x66952671374545CAULL, 
            0x2CF35741374346A9ULL, 0xD222680DCB2E6891ULL, 0x3ADAADC53A2FA248ULL, 0x054217B2CBE2047CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseAConstants = {
    0x741E74C598FB0A52ULL,
    0x919E611B3F7BC0EBULL,
    0x225E94FC26A5ECCDULL,
    0x741E74C598FB0A52ULL,
    0x919E611B3F7BC0EBULL,
    0x225E94FC26A5ECCDULL,
    0x7CF75BCA7A8EE501ULL,
    0xDA94B7C07B90D778ULL,
    0x70,
    0x0B,
    0x45,
    0xCE,
    0x1B,
    0x8A,
    0x82,
    0x32
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseBSalts = {
    {
        {
            0xF526943A1FD2FE91ULL, 0x9C31AAE75AD06E21ULL, 0xD55C941D3E9F9FFAULL, 0x13410770D0A67951ULL, 
            0xD74A6E6D4783DE73ULL, 0x059721D57BD0DF10ULL, 0xA825BB6002D9E2B4ULL, 0xD9C89DFBD7B857CBULL, 
            0x02186BEFB0DF93C1ULL, 0xBDBAC4DD2939EE89ULL, 0x662E8CD23C6D3A9DULL, 0x3A994E7E56475347ULL, 
            0xDCE7EF81E0E78926ULL, 0xF1F7670AEF884ECBULL, 0xB5AACC01966290BAULL, 0x5F3282E53A61DFC9ULL, 
            0x1DEEEBFE02A67893ULL, 0xE248FFB090478F82ULL, 0xC6CB55416E13DA7EULL, 0x6BDA2F4C7FA86BF5ULL, 
            0x4CF07E1BD01FACE4ULL, 0xE82CCAB4447854D0ULL, 0x7163B3731E15A51BULL, 0x2E2FBBB9A4026733ULL, 
            0x2F5DB093D70746A7ULL, 0x6AB3625107CA2A33ULL, 0x238177E419D0806EULL, 0xEA05EC4FA91D8CFBULL, 
            0xBF0CF4549D8FDA9BULL, 0x771F857F9982DE98ULL, 0xECBDA9012D6F58E2ULL, 0x32AF1294E6D165ECULL
        },
        {
            0x24AEB01994CA629EULL, 0xAADB460A928C1427ULL, 0x1C4BC234FA84DB44ULL, 0x98A6FD294A96A523ULL, 
            0x16F27312BA69D761ULL, 0x4B49DA1107D195A8ULL, 0x2C2CECE2AAA6AF21ULL, 0x5B3C6D6A670170A0ULL, 
            0x18E259188A19B54CULL, 0x5AB17C4C6CB879EBULL, 0x517CD77E43D24553ULL, 0xF05735A73FC57521ULL, 
            0xED2DBB7D2D15B43AULL, 0xB2D22E3DACE51D00ULL, 0xBCDE6C4F723F24DAULL, 0x8F94F7729028466FULL, 
            0x4610322D2698796FULL, 0xBD8359807DB78FC8ULL, 0xF54A24FE5B94D24AULL, 0xD4096FBA24F271CEULL, 
            0xCA19CDCB753E78A4ULL, 0x06413A5370187E0FULL, 0x207648E84DD7655CULL, 0x665DCFB62D15C941ULL, 
            0x0F5D8D43C809AD15ULL, 0x10B2F07B3ADE3DBEULL, 0xF3016F46E1E2CFB8ULL, 0xCB85D680862002EAULL, 
            0xEA625E320A93D8CCULL, 0x487AAE80BCEAAFFEULL, 0xE3734E892322E2E9ULL, 0xA42D8FCB19AC1915ULL
        },
        {
            0x2BD3F6F1521220A1ULL, 0x7C7572264D13FB8DULL, 0x1CCA5BD6493454DBULL, 0x4030EEBF2B7FC532ULL, 
            0xD96306B3E0B3729AULL, 0xA716C78E784B222CULL, 0x97B400875932FE7BULL, 0x1A614864E30B4873ULL, 
            0x4E0419E9D6901849ULL, 0x575361DF5126F1D5ULL, 0x18BE62BBE6EDBD7EULL, 0x5091A0C68F722EDDULL, 
            0x8B44083C34F001ABULL, 0x050DEDE9E4205D9CULL, 0xC1ECF646FA5A2FACULL, 0xCEDAB0C71566D8EEULL, 
            0x2EB1B44EF21A33F6ULL, 0x5CECFDB3BA14117EULL, 0xFEC5A3FA1D01C562ULL, 0x46718B16B56708C9ULL, 
            0x4E54311F0AF88998ULL, 0xE231B07AC48D54D5ULL, 0x7759C9BC0F3B9640ULL, 0xACB468E2D8AC41ABULL, 
            0xCC1FE02DDA706F25ULL, 0x729A7AB1BDDB4544ULL, 0x8FF0A4AC546D316CULL, 0x5F3D3CDF47D50149ULL, 
            0x10665479D9100E4BULL, 0x46770DD817CAEE7EULL, 0xB598CC35E2E4ED42ULL, 0x332647730F82E445ULL
        },
        {
            0x1790729957A79070ULL, 0x40A8506FBC0803BFULL, 0x6E2C941BBE4A8850ULL, 0x8302461885D0D9E2ULL, 
            0xDEF16434A9C470E7ULL, 0xC77E53AFB9CD9F81ULL, 0x47020EDBAED88E61ULL, 0x6B36DA93C7A33555ULL, 
            0x59590F174857CA3AULL, 0x9CE397C0067D6197ULL, 0x0FB7F2E6D9B8D527ULL, 0x1A7AB0F7CB62F838ULL, 
            0x78540E5D739D1810ULL, 0xA5DFE02F8B150C02ULL, 0xE1A8B8CC4988D382ULL, 0xD472622F8AC75CA2ULL, 
            0xC046E3CE9B7BE8B7ULL, 0x3E39166A544AC8A9ULL, 0x332135A983F1A0C0ULL, 0xABD9B4B6A4671CE7ULL, 
            0x12F6D5693757EDC5ULL, 0x9D6370594F492867ULL, 0x542590CA3E6CFC72ULL, 0xCF8760F79DC4F595ULL, 
            0x39ECBBAA88213D2FULL, 0x8602E17327112F13ULL, 0xA69C984558A110BCULL, 0x694471858EEBBCA8ULL, 
            0x66E187E9105484D3ULL, 0x3D0B01E7A6D1C773ULL, 0xC6B3DFA9BC85CFA1ULL, 0x0AC322F8A98343C7ULL
        },
        {
            0x2AE11CEB5738D15DULL, 0x859289ABCC0FB5F0ULL, 0x2401F07E1F8042EEULL, 0x66513AA9E4EAF21FULL, 
            0x4E1F80DF78916DF4ULL, 0x3898C03C3E386489ULL, 0x2892F57D17713E72ULL, 0x8263C7AA2C0C82E9ULL, 
            0x9AE7DB01D9227354ULL, 0xC9467D868CCE16F1ULL, 0x751F749D85CA8FBFULL, 0x40E4CE3637613B15ULL, 
            0x52176BE556D111EFULL, 0x40A1543937422BE8ULL, 0x8B5A66813CBA8033ULL, 0x8FCEDCD0C43D8F52ULL, 
            0x02F6F57CDB356F13ULL, 0xF036394BD7345E26ULL, 0x85C4E71928989455ULL, 0xDA8837D99F52A354ULL, 
            0xC9E8AF6F10FAC3F6ULL, 0x78173D92CB94FAB4ULL, 0xF75F05A6FC8EC883ULL, 0x10A9C8EB38CD2F2BULL, 
            0x77ECD69147640A33ULL, 0x78B8F00C37702994ULL, 0x9F6BE0AB9AB663A7ULL, 0x0C7F538CDC8CC1FDULL, 
            0x1FA5960CADA4E0ACULL, 0x430355771F5D89C5ULL, 0x62053A484F0FA960ULL, 0xFC33A6A182192BF4ULL
        },
        {
            0x8E90D5E96B71190AULL, 0x3BDB38945DD465E3ULL, 0x10C2E4512BB4F1C2ULL, 0xB50C0CF1D7D207FCULL, 
            0x4186317C1D45EBA2ULL, 0x9A7267131BAFF74EULL, 0x30DD1A4132CD0830ULL, 0x7B442A9B2B41B30EULL, 
            0x49DE2F17546F5DE9ULL, 0x52742010434D00ACULL, 0x98B959A57B590D5DULL, 0x10D43CFD3B3A96CBULL, 
            0xCCD51B34D1D750ACULL, 0x0D9644A2BEFE553DULL, 0x7D659D83B3B766EEULL, 0x71F7B7C50B41C071ULL, 
            0x55B9B01668CC91C7ULL, 0x1372E1D312FBE58CULL, 0xE6FC66C3A1A2A478ULL, 0xFECF9982FBE310D3ULL, 
            0xA4EA75023E5C8268ULL, 0x33F22CEA2CCD01A4ULL, 0xD8DC7ACB69664DF2ULL, 0x100A91705A418928ULL, 
            0x205428B88665E757ULL, 0x3FDDA92EBA4089E4ULL, 0x56E831AB46C3FFE1ULL, 0xBEC829EEA7FAA4F7ULL, 
            0x792A96BDC4015CABULL, 0x968B06B07AD3B1ADULL, 0xED4FC69883D6E579ULL, 0x1B0A59823D54E0DDULL
        }
    },
    {
        {
            0x2971F7B91E114AD3ULL, 0xE9A92D015F31585BULL, 0xBE372526A0754908ULL, 0x16AECE87E272B525ULL, 
            0x3F3BC622CCE83996ULL, 0xC895FDD7E567C767ULL, 0x5C6038B5573B52A2ULL, 0x287A881CFE627F8AULL, 
            0x7C749A036DB26518ULL, 0x5424DF645045C26FULL, 0x4D240B461E367283ULL, 0x92462549A364D39CULL, 
            0xF74269FE47929DD3ULL, 0x1EFE720C901BFA44ULL, 0xEDA01014AEF6A58BULL, 0x61313F102A8145A8ULL, 
            0x93DA553C0EBEB4F1ULL, 0xFC6580031CA36120ULL, 0xEB67062412B26946ULL, 0x26C0C1E5E570701AULL, 
            0x23FCF31F92AC2AF4ULL, 0x202DAAA18E67262DULL, 0xFE22CD84CFAB5B96ULL, 0x0B18F533139F6DB5ULL, 
            0x073F63933B1141ACULL, 0xC553CAEC1D4B4E51ULL, 0x6AE7F4C281871F0DULL, 0x5DE4FA146AF5F4F6ULL, 
            0x74FC6AA2926F3476ULL, 0x81A2225D7146B7E8ULL, 0x105B976589B5751CULL, 0x916E0A200910D0B4ULL
        },
        {
            0xE87AACA5B9AA8092ULL, 0x1AB5B9D640B53BD4ULL, 0xF2CD086B90CA7A16ULL, 0x46B63543899466CAULL, 
            0xC8EA8BA59CD8C2E1ULL, 0x52A610FAB1FCCE38ULL, 0x201B2A80A01752ECULL, 0xC4A3CEE4AB18B9B7ULL, 
            0xFFD293614081FF7CULL, 0xC18AE49D3AD9077CULL, 0xDF608204362CD95BULL, 0xD00D21A418BF9F5DULL, 
            0x5F720AE9C6C2BBF3ULL, 0xC8F78FAE7F4BE951ULL, 0xA1FD14F38984C325ULL, 0x4974B3481B1FFAC8ULL, 
            0xB3492E8DE72C4AD2ULL, 0x29365C8825EBD4C4ULL, 0x5BF0CB1BF1D49ADDULL, 0x6967987BEAE84A76ULL, 
            0xD05DBE644C619FE5ULL, 0xF68421910CA57BC8ULL, 0xD74573EEAC1D91D9ULL, 0xA8CD5068760B3CC1ULL, 
            0x120584EBEC6FBD32ULL, 0xCE38130CC961A0E6ULL, 0xF6A033004B2FB74DULL, 0x3171E3DDA22A732BULL, 
            0xA94D8EB2ACF7B5DEULL, 0x070447AAFBA709A6ULL, 0x55AB932D490E2130ULL, 0xFC03D536E2237488ULL
        },
        {
            0xE77AC1876C53E9A4ULL, 0x56986A4A77E73832ULL, 0x56C27E604DBBE178ULL, 0x781FD293374CEA61ULL, 
            0x1344ADE95A7913FAULL, 0x0E4E0177314525D3ULL, 0xC32ADF8E5B582FDEULL, 0x92F4CAC6C5ECF638ULL, 
            0x8638D7B7EE27F423ULL, 0xB202382752A4A56DULL, 0xFC1CCDAEC0A76C21ULL, 0xD39F688D90BBEFADULL, 
            0x15FF5FA474B996FFULL, 0x8A87961F146F756AULL, 0x87EB5A00947D8EEFULL, 0x0935B55D063539FAULL, 
            0x68628D127F3C286CULL, 0xA5FA50D4559D5C5FULL, 0xC8F29CF0E7F804D8ULL, 0x3971D3C9C2459FC9ULL, 
            0x8BA1D874677B7260ULL, 0xE37FB30FBDE4B3F4ULL, 0xE93BEA336D1D9ACDULL, 0x2F12178B676963A4ULL, 
            0xF1830268D8E98B1DULL, 0xFBAE79960535E035ULL, 0x08DD92AFA98180F5ULL, 0x8A1C90B34D6DB389ULL, 
            0xEEA5444E2F96045CULL, 0x7A394092118E0C31ULL, 0xD36F053C6387FE6FULL, 0xAEEDD64173E2A538ULL
        },
        {
            0x41099BD6A93EFB90ULL, 0x3B673CB32094BE71ULL, 0x346C7E5B6E9F3522ULL, 0x8C74881C2BAF5924ULL, 
            0x3955D0939D56A263ULL, 0xB67D57F248010D30ULL, 0xB299C4C338C3C83CULL, 0x636E552A253A490AULL, 
            0x91167FB6893E9154ULL, 0x1FCC2E6BC51F5CE9ULL, 0xA0D98E08B69E2691ULL, 0xFBA03A3AC73E95ABULL, 
            0x420073176AF616A0ULL, 0x46A93986A85D3D7EULL, 0xDEEE3718956B6551ULL, 0x1B5531EA0F1D1C82ULL, 
            0x4E66D77000513ADFULL, 0x7932478B6040228AULL, 0x16887E3E0B00C176ULL, 0xE197C81B10FB15A1ULL, 
            0x55A4B9B76D0B2126ULL, 0x8B29C57D17D92E2CULL, 0x7951FD5AE4C31ECCULL, 0xFBFD2FEACC37C652ULL, 
            0x61342B1E57655EE2ULL, 0x39C2D7596D5B1748ULL, 0x6577344AF2D80D62ULL, 0x0E4D0AEE156354B9ULL, 
            0x95CA850B11B25AA8ULL, 0x75358984F46E7E32ULL, 0x01E9705F54D3394DULL, 0x46F920E53A7039A4ULL
        },
        {
            0xB123C3D28F3D2811ULL, 0xF197D9516F05CE39ULL, 0x2DCF68F3D679D254ULL, 0x8DA07E5E69A9B588ULL, 
            0xB6DE97B1DD230084ULL, 0x90E7B7A6E6BCB5DBULL, 0x60EC3614D1260342ULL, 0x5A393E986AB86787ULL, 
            0x7FCA1F7ADB6866B7ULL, 0xC821FB2596C4D04CULL, 0x05CF577669C93B7BULL, 0x0EEF7C34EA6027E7ULL, 
            0x340E869A3D98B496ULL, 0x347FFC7AF64241DBULL, 0xA8C8A70CE3B7B745ULL, 0xCED54DEA344261E9ULL, 
            0xB390D800D805F038ULL, 0x00A490FBDE3250AFULL, 0x086276F19876CB21ULL, 0x633349AB33401D30ULL, 
            0xCE55ECBE7E4F3EAAULL, 0xAECD916902485399ULL, 0x9F60B2536DB1F061ULL, 0x8C871C242951248DULL, 
            0x474F5B1B5A74C452ULL, 0x279564A5451F680EULL, 0x978626983A86B306ULL, 0x23C230E8A0625FF5ULL, 
            0x9C185A6DC3D5C356ULL, 0x1853AD37131C7DF4ULL, 0x7FCCBF4D6C59FAC7ULL, 0xAED4090A4AE24551ULL
        },
        {
            0xDF9FCB02540593C7ULL, 0x65A38FCD6645D778ULL, 0xB44CC9F03D847EF8ULL, 0x0639B7E18C32FA2AULL, 
            0x3F1616DB85E224D9ULL, 0xC6E293CDA02CDE14ULL, 0x458B417A354B73E1ULL, 0x786203152F8D08E3ULL, 
            0xC8BE134962553DF0ULL, 0x0998B48D2F1B49E1ULL, 0x0525E23425A135E9ULL, 0xF7F75CE9D5B98821ULL, 
            0x694E8D2586FF74EAULL, 0xFD1527832CFDEB34ULL, 0xE5CF0F19F669E8DCULL, 0xD3153784FB07A0E6ULL, 
            0xF262DD3CB3421DECULL, 0xBD4A21185FB22260ULL, 0x2F7ED1AC002D032BULL, 0xE665367E25D7CAFDULL, 
            0xFFEFADC10B54D257ULL, 0xFEA734A9B1E4900FULL, 0x5953273EAEFCA023ULL, 0x5C5CA6959459F7D1ULL, 
            0x1C282F904BA7D76BULL, 0x5D0CE33B812E33DBULL, 0xB07B4EA64BA2EF11ULL, 0x39037414268D8317ULL, 
            0xDE437F0ADE3136D4ULL, 0x87EEFD3E9166B4FEULL, 0x1C727F2B964851D6ULL, 0x505AC32BFEC23A08ULL
        }
    },
    {
        {
            0x70114B004A2FE045ULL, 0xAB1F803CBF2DB696ULL, 0x461A49CB6034ABACULL, 0xE945AB5767246786ULL, 
            0xD5B68112BF72F065ULL, 0x280F1E2D8EAD3687ULL, 0xA545D95257B18614ULL, 0xC0F1402DF2C429EDULL, 
            0x8253E8F4921EF768ULL, 0xA088F50E7FEC8A98ULL, 0xE356D690D775CD5CULL, 0xFAA13AD97368C5B5ULL, 
            0x9EB56643C396346EULL, 0xDEADE8CD1CCEA9FCULL, 0x3E2FEDCD8846F595ULL, 0x6D249E5D25628609ULL, 
            0xD74C5C9B1829977EULL, 0x8855BF15C98D4155ULL, 0x723C83C6F7DEB6C4ULL, 0x62DB5C272A50C940ULL, 
            0x409832852A5056C5ULL, 0x3B73FBAA45F6DC3DULL, 0x058CC0FBE34F0891ULL, 0xA7B28AA9D3A70D45ULL, 
            0xB124EE34CA647165ULL, 0x84C8566FDE54D5BDULL, 0x06A66FFDD048FFB6ULL, 0x00140DD3D0A3D912ULL, 
            0x04D040C4E40D30E3ULL, 0xD7F0C0BD041F57E6ULL, 0x94F99B8ECDC58FE0ULL, 0x26D7FD39CB394951ULL
        },
        {
            0xACC77C90FD134304ULL, 0xA6AFD9F24E6C296FULL, 0x3E14E3D3E2FBC151ULL, 0xE34196D21D864B18ULL, 
            0x2569F9B58E5401A8ULL, 0xA2DB3BB20561A694ULL, 0xA7A6CE17A1024790ULL, 0x575DDF1D3FC9915DULL, 
            0xF52E5F8A7E0B23C2ULL, 0x983C1408267CA339ULL, 0xED9339EA2C156373ULL, 0x15EE1661D693BB99ULL, 
            0x68273361DB3380AFULL, 0x7824B44EFBEF8CC3ULL, 0x7A8989F682196AA9ULL, 0x4342F6E972ABF4B7ULL, 
            0xC69C240E8805EBACULL, 0x0389FA46BE9ABEA5ULL, 0x3AEDFFE3D625C9E3ULL, 0x9E04F919F4AC5006ULL, 
            0x775C3629B489D77EULL, 0x0503193D54AC346EULL, 0x038C63E96E7EA3F4ULL, 0x36B011380EB7775DULL, 
            0x79CC274BA5BCBF05ULL, 0x1E2F220B2B57385DULL, 0x834B69F4675B90FBULL, 0x7A89345A63F8E490ULL, 
            0x35806F2C4608191DULL, 0xEA88888C0BA00722ULL, 0xE5F20316DF24358EULL, 0x998784D525F2A49BULL
        },
        {
            0x08970630C833B6A3ULL, 0x1D7FC7747E200DDAULL, 0x58AC86FE56A412DFULL, 0x8F3CF73756E5B388ULL, 
            0xB60F7F67C6B1D5C1ULL, 0xF8ECEAF884CD9FF6ULL, 0x48728EF2350C857FULL, 0x8837A04F7815CDB3ULL, 
            0xC5F65038C9EE2D03ULL, 0x3050A4079D6B6E98ULL, 0xB9CA4D847526D750ULL, 0xE7CD62AA8139549DULL, 
            0xEF0414A6EC75FDAFULL, 0x72A540818DD47808ULL, 0xB3EAC44E30ED9F13ULL, 0xE38F753FFAB513BFULL, 
            0x99805296A1CE48CBULL, 0xA867BF0613D3FD29ULL, 0xBA7A266B284F07EBULL, 0xF2AB3770647A1D39ULL, 
            0x698BDD52CCF54AB1ULL, 0x535358768351A8CFULL, 0x9AB85340610C89F3ULL, 0xF6C4C93B65147F48ULL, 
            0xEA231F878B90FBEDULL, 0x83A27703ABB80561ULL, 0xB1B73E71E9DF3B45ULL, 0xD3CBBBC076CE09A0ULL, 
            0x4FC096EB724693EFULL, 0x728137D50371DE02ULL, 0xF8847D0CC2D69225ULL, 0x6F41A127F0C0439CULL
        },
        {
            0xCCE258571D598C46ULL, 0x547E8D83B1E503C6ULL, 0x00CFD1580413573EULL, 0xBBD338ACB6B0AEAEULL, 
            0x44BF7AB5806AAB8CULL, 0xCEA8CBCE8350E3EBULL, 0x71EE3841F56C71BEULL, 0xABF278E0F7D2063FULL, 
            0x4E7DC4C8A9639486ULL, 0x5AF796EEAF2EEE6DULL, 0xBE13D1E38FA6E764ULL, 0x368B4FC2E7B82BF4ULL, 
            0xBCBCC2489C4FD6BDULL, 0x69BAEB22681ABDCBULL, 0x8168E316F7C08706ULL, 0xD4211F8FA2382C62ULL, 
            0x81964EAD773AA144ULL, 0x098E58E279AC9765ULL, 0xDFC8EA46AC60D607ULL, 0x582751E937C98BB5ULL, 
            0x0D7F32B7BBABCCE6ULL, 0xC5527DAEC17D6F39ULL, 0x50D2A018B4AD5456ULL, 0xE4DF46B5DD97A7BDULL, 
            0x7F4A84AADB6E154CULL, 0x43A5567D3CE13A35ULL, 0x47113F92ED976E79ULL, 0x724BB6D0F6D57ED6ULL, 
            0x8146A3FA4620162AULL, 0x4516E32C23D21ACBULL, 0x691B464A175F844FULL, 0x64CE368B8A87EDA6ULL
        },
        {
            0x220BF9E3F72C72D3ULL, 0x4CA652B786907AEDULL, 0x56AD2B671424A10AULL, 0x00AFD00B570CFFF6ULL, 
            0xEF0B91789C431316ULL, 0xA0F0BD18C2560A16ULL, 0xA0AA67BF4DA3D5F7ULL, 0xF4B8998AAC564164ULL, 
            0xB827CAE60E5578F9ULL, 0xF394C8C572C2BC80ULL, 0x4546411176210AFAULL, 0x12135BE78771C4DAULL, 
            0xC063BDC3649983B2ULL, 0x87D0DE5404BC3509ULL, 0x3300169D4BFF169EULL, 0x1B9CFA2149314C0EULL, 
            0x17262FF14CBE7951ULL, 0x0F3A1BFD0256BD1AULL, 0x2BDC5E2B378B98A8ULL, 0xA5A9873AB3CCADF4ULL, 
            0xF3A8DD80BEB9735DULL, 0x32225735AC466F71ULL, 0xECC485F479B23CC3ULL, 0x7A3A2F0522CDBEDEULL, 
            0xCAFFE773FFE1C6F2ULL, 0x4AAB8E8992067A70ULL, 0xBC71230D8D125897ULL, 0xED41FFD2031D79E2ULL, 
            0x467146E6D768EA5EULL, 0xE6AF909FF241806FULL, 0x83214C098939127BULL, 0xDDECA95C3F3B5708ULL
        },
        {
            0x981B040399C05E41ULL, 0x6FDB349B7621B09FULL, 0xE526075C0D30F336ULL, 0x33AB566D8F9A0B24ULL, 
            0x1EE7BEAFA66E0336ULL, 0x59FF0D2C69622B2BULL, 0x6033CC104F16E4F7ULL, 0x77D41B3AA81D43F5ULL, 
            0x8F554CFF54003B74ULL, 0xC2F8945762C5F956ULL, 0x35E34A8D171F50DDULL, 0x62A594F842DDBBA2ULL, 
            0x29C97C8A6221E815ULL, 0xC4B8280CF87571D8ULL, 0xE9063C43C1DFA515ULL, 0xB28CAF91F06C6D17ULL, 
            0xE853EA244E575C32ULL, 0x269C0D88A7094DFFULL, 0x1805CD6C8C1F34FDULL, 0x6A37FD3AA8673020ULL, 
            0xFE58EF030C40099AULL, 0xA5E82A7A22D3C8E5ULL, 0xD8FBC12617DFE7A9ULL, 0xED74275730B6255CULL, 
            0xFF42722F26F4918FULL, 0xCCF3184E5809639DULL, 0x5D71383AC60DFC0EULL, 0xA331D8A9AE600497ULL, 
            0x4D8F2BD0EE4CC05EULL, 0xD91309A77DC3438AULL, 0xDCF624F863575CE3ULL, 0xC42E0AAB650490EEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseBConstants = {
    0x0CB5557B49BBBF08ULL,
    0x35834011118F9F2BULL,
    0xAE64780CF49479DDULL,
    0x0CB5557B49BBBF08ULL,
    0x35834011118F9F2BULL,
    0xAE64780CF49479DDULL,
    0xD4EC782BB9DB6A56ULL,
    0x31F37882884F9A8BULL,
    0xD7,
    0x84,
    0x77,
    0xD2,
    0x87,
    0xDE,
    0xF3,
    0xFC
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseCSalts = {
    {
        {
            0x2BC1E164A7E3565CULL, 0x34E63F344856CB10ULL, 0xA1498E74D99309D9ULL, 0x11FF1C28BD2EDA46ULL, 
            0x869E8F908618A6D1ULL, 0x0AC713592DBBAF44ULL, 0x46301EB61118AF81ULL, 0x4BEFDAE7E909B1E5ULL, 
            0x16AF651EF0AF705FULL, 0xC3794BDBC1042A93ULL, 0x42632EAAB956EF49ULL, 0xD5B212D2C78ECBB0ULL, 
            0x22F03711792D284EULL, 0xC3B1EC3270C60238ULL, 0x682E98D788FBB466ULL, 0x766E024BC13EFBB0ULL, 
            0x593A8F8DB3703C80ULL, 0xF60A70B6DE9C2DFEULL, 0x05E2C57FB6A51DD9ULL, 0xCC924043A6C5D248ULL, 
            0xFCDBFE1DA57929EBULL, 0x26BAB5C080BC30CCULL, 0x48F270FA27AEF914ULL, 0x61F1036144380300ULL, 
            0xADB287B0FB165941ULL, 0x1304C8A5093BBCB0ULL, 0x864875743E5951E9ULL, 0xBBE7D0FB40B75D39ULL, 
            0x0657723C3B444838ULL, 0xA69677E656B6AAE6ULL, 0x6F67CA8EBFE75652ULL, 0x12721FD5D54C86C7ULL
        },
        {
            0xC1BB9CFA174E3F2DULL, 0x687892785ECBDC29ULL, 0xCC0B2DBC0C79CB90ULL, 0xE89B19DFF0CC7350ULL, 
            0x16A6A99C8CCB95F3ULL, 0x04DF3C804B96DFB8ULL, 0xF9AED73C04506C27ULL, 0xE2B4956DC6BF9856ULL, 
            0x9EB2F3DF8953A2E7ULL, 0xD149258CEE0AADE7ULL, 0x92C6DFB41964989AULL, 0x6CFE57B1A95863B9ULL, 
            0x8F6AEEC2818838BAULL, 0x26DAC4F5666CC363ULL, 0x80F45F78FAA8D78CULL, 0xB318461552BB390CULL, 
            0xA26C0D5A328383C5ULL, 0xBEBAF1C6ECFF1097ULL, 0xC68BAF41E63A3E8CULL, 0x596A00AF47778CE4ULL, 
            0x03DFEA7FE3993594ULL, 0x641C631E2F878002ULL, 0x82515168DAB6CA48ULL, 0x9E9CE5365B57CD02ULL, 
            0xF5DF4A724D47644CULL, 0x6EDE9FC579D22A1DULL, 0x4D8A4D6086854924ULL, 0xE42EBE9884A13A02ULL, 
            0x6286720BA43D5248ULL, 0x20AA250CCBD440CAULL, 0xCD8E04BC2B851041ULL, 0xE0B4C3800EA62EE5ULL
        },
        {
            0xE1EEED57922F5A15ULL, 0x1A6F41CF39C9686AULL, 0x3C359FD16CE7237EULL, 0x10624D01714D438FULL, 
            0x015BC0143BD36C41ULL, 0xD0529D39DC709931ULL, 0x5DB5AFF93C6F9587ULL, 0xE84B11AF8697B9E5ULL, 
            0x14C53B50F4913EDDULL, 0xEFD29A1022473D08ULL, 0xD5ED5EC083C7E8F6ULL, 0x663B26AE2E4FF04BULL, 
            0xC4641C5E57555C4BULL, 0xF49838D3E7A6F512ULL, 0x379F25DF105E2A5FULL, 0x165B8EAABD25BBB8ULL, 
            0xCD139380C0C57E1EULL, 0x30ED4EA1A9B8D5FDULL, 0xA0340C31B5691E71ULL, 0xE6C26C3C148D1781ULL, 
            0xAE60B63C823014E0ULL, 0x96D7D2D3FE0A8F64ULL, 0x75C98C6D4876FF1BULL, 0x20F5FB8C5B975E96ULL, 
            0xCD4571BDF82E8852ULL, 0xBAECFC473EE1EC5DULL, 0x0C15A8CD53EC1F28ULL, 0x82EDC7B54A2D059DULL, 
            0x61E729E2F929F1F4ULL, 0x253D99C4E21EA33DULL, 0xA5CB94642267671DULL, 0x138E895766F466AAULL
        },
        {
            0x47B7B5E1A265423EULL, 0x45A9CDE9B2C9FF9BULL, 0xB5DBA47F69100008ULL, 0x812BFED36EC6E587ULL, 
            0xD16F2F4852D8E7FAULL, 0x22A7A8161AC40B98ULL, 0x0BF4247C60463BC8ULL, 0xEC77B06C532E81CFULL, 
            0xFD6BD76CD29EC080ULL, 0xB40B0D649202A0FEULL, 0xD420305C2CFBF8E6ULL, 0x65713A5347614674ULL, 
            0x80F34376047DE4B8ULL, 0xA9BB368D8E6920DBULL, 0xADAFE89CD36F0C90ULL, 0x0D728F57A34B6D9CULL, 
            0x11CF471B1EFE8F74ULL, 0xA59759A99353302EULL, 0x4B1767435E2E0E4FULL, 0xD8E7C8DD09D6182EULL, 
            0xB6C17D0A80071209ULL, 0xEDA55F6BBEFA4084ULL, 0xFAD8673A12538386ULL, 0xF7C5E6FADF4D8E4AULL, 
            0xB3A05A569B9F8A13ULL, 0xA56653D3DC627C00ULL, 0x1534F5E80B2E5BB0ULL, 0x64EB1C7343F7D11AULL, 
            0x109C2C72F57343F4ULL, 0x8B20EF071864E5E9ULL, 0x7DE402565CE05CF6ULL, 0x32F3EF31990B94B7ULL
        },
        {
            0x3683E2119B70ACD5ULL, 0x5DBFD61F0A9CC318ULL, 0x74225595315A4CD5ULL, 0xA2AD5CBDFF8A8E41ULL, 
            0x89A12705652BDDC4ULL, 0xFE97BC6F90F667DBULL, 0x90CEC69E3368A592ULL, 0x53C7090C61FEDD9BULL, 
            0x4DC5D2702C0256B1ULL, 0xF5C3DA4FBCFB3FC2ULL, 0x029D67DC8211D79DULL, 0x447DA89727C69D32ULL, 
            0x9EB617E59FB47E6BULL, 0x90B37D362C626C16ULL, 0x3A5D6B28BB459C27ULL, 0xF2046E6EE27D3F21ULL, 
            0x2A235B8E59DAB44EULL, 0x8839C09AE5CEF389ULL, 0x4F18F5FB824E77B4ULL, 0x50CCE97DB510615AULL, 
            0xB57FB83A272CC263ULL, 0x0EB25167192AF191ULL, 0x2AD7FAD2A7E9E19BULL, 0xB0BB02E3769066C4ULL, 
            0x8F982B711A1186A8ULL, 0x543753EA41CD243FULL, 0xE9A4A9EE66D3033EULL, 0x80AFAE02BF5BC07FULL, 
            0x4617E437842AF6CFULL, 0x481943C47362B7A0ULL, 0x45458699A8E35F64ULL, 0x0621AF80AE8943C4ULL
        },
        {
            0x8D18F6DED5DD5727ULL, 0x43F68A87E10597F3ULL, 0xF9C4496645D0670CULL, 0xEFF0A06F8864EE07ULL, 
            0x91B2FA4411CAF871ULL, 0x622F06EC4DF77EA9ULL, 0x06B4E08C82AB5BEDULL, 0x04A9FB67D772F0CCULL, 
            0x8366948D86525232ULL, 0xCE943B2A44C622CAULL, 0xBDB9ACB665F12F8EULL, 0x420CD55DA81C0902ULL, 
            0x5CC53EE01CC3BD06ULL, 0x97A0297B07073D39ULL, 0x3DA43E1CAB246D5AULL, 0x0EB6CF8298592C08ULL, 
            0x56A4D44E1840DD7EULL, 0xC094F7AA694C427EULL, 0x419E9A3D97D04DA9ULL, 0x38C69014A03A4EFCULL, 
            0x39853BFBA46AFDF3ULL, 0xCB9591FDD8E51881ULL, 0x56C7625BD90C02EBULL, 0x661F4F9A01527DF3ULL, 
            0xB54CE5EABC0CFEE6ULL, 0x14F3448EED2ECE20ULL, 0xD3ED49D13BD8863EULL, 0x35E3FF3D1918700AULL, 
            0x9920D1E187B13A90ULL, 0x617A4EF99E712E21ULL, 0xD01F11DD4F726E37ULL, 0x954D27743C9D3AF2ULL
        }
    },
    {
        {
            0x9394B46B5AA077F1ULL, 0xD4E1C859A3D0CE3FULL, 0xD860F839C3002532ULL, 0x9121A67B7228E595ULL, 
            0x4F5DA61EB8EFE837ULL, 0xD038631DA37B8A3FULL, 0xA06602DA7365770CULL, 0x21B69E84E6B7FEB9ULL, 
            0x14D343B30E6FF22CULL, 0xCB4AB5D6691A1A5DULL, 0x48A48C0684D7C89DULL, 0xB9C762E52C01C8F7ULL, 
            0x1BD1FEECDE37BD0FULL, 0x411D1FC676611E82ULL, 0x19D353CC154030A7ULL, 0xB466D2800F763E09ULL, 
            0xD759ABD4B38A30AAULL, 0xA1BC5E309CE02021ULL, 0x3DE523FC5B63F1CFULL, 0xDD0715CDCF312724ULL, 
            0xD406FFC9B1412AD9ULL, 0x48B9E350240586EDULL, 0x719C50AC1D045738ULL, 0x6CEF92C7351CB507ULL, 
            0x9E8A1E55C379A623ULL, 0x19C79145DBFAD37BULL, 0xD376FF706147A675ULL, 0xEE985A7CB7BA2382ULL, 
            0x998DAB1E203966C1ULL, 0x1DA546BD5B98FD98ULL, 0x559ADBC3C6E05FC5ULL, 0x377AAF6FD07B2646ULL
        },
        {
            0xFC715363DBFFE7A5ULL, 0x1F5129264C8B2F67ULL, 0x25DF2684CE9F1BB8ULL, 0x2050FC14029547B8ULL, 
            0x483D331ACD11AEF7ULL, 0x3C0C72972FB576F8ULL, 0x6DF2FFC3313F2705ULL, 0xD8E9639F254845AFULL, 
            0x3A7A51C8C490C75EULL, 0xF2F870724FC30E9DULL, 0x375B3E3C499B3808ULL, 0x2670C1CAF3D62517ULL, 
            0x15DE917250B54123ULL, 0x786CD1E0835DA7E0ULL, 0x46E011FD9B2B229CULL, 0x4F1ACAB6425FA15DULL, 
            0xB91AB05AE93B8190ULL, 0xFDB72A2C642652F7ULL, 0xF2B809FF4F38AC5EULL, 0x580E21ECD9BAC02AULL, 
            0x5C55CBADD6D02D04ULL, 0x9174F253655E2B63ULL, 0xA0DAB733F604451FULL, 0x8D9B37022C289AEFULL, 
            0x3D254E08CDD97B50ULL, 0x373245B176D7A7C3ULL, 0xDFE64BEBE4A8129EULL, 0x3FCEEDB79C3D1344ULL, 
            0x15328511A128472BULL, 0x123AEDF976788585ULL, 0xC75E35E83DFF4431ULL, 0x014C574CF0CFFB00ULL
        },
        {
            0x4117A719132186F1ULL, 0xCCC61A7CA1D58D6DULL, 0x9CE399FD2C7B8FAEULL, 0xEF7BD73188D8BD0AULL, 
            0x600E11692DDC6B3DULL, 0x99F3733DF34A6490ULL, 0x46738D96DB0C9463ULL, 0x150CAA6B767067BAULL, 
            0x845E9760153D868AULL, 0xB62B1B864862C9A8ULL, 0x423B7884EAFAD12CULL, 0x8FCC8C1E0D46FC23ULL, 
            0x42F20F97EE2E3A9DULL, 0x88DDCE8E45825B13ULL, 0xC98273B4729D9287ULL, 0x31997469D2AA25AEULL, 
            0xB554660C3A04271CULL, 0xEBF33A8D5A02F32EULL, 0x2B901A3D77CE2098ULL, 0x46828838EB39D858ULL, 
            0xB516AF12FB756FF7ULL, 0x6B4F6F790E97FFEAULL, 0xAAB64D7E5D2E1EE5ULL, 0x2DBC38B4CA6F7A89ULL, 
            0x0CACBA5570F911B5ULL, 0xB190009676F0E34CULL, 0xD59DA4431458B16AULL, 0x2C4F021F35D483E1ULL, 
            0x0C9002B24006E3DCULL, 0xD11B7A9CB23FD54DULL, 0xEB1AD84EF5E6BBE1ULL, 0x44FE2A406F93E496ULL
        },
        {
            0xB5300BED70D23C62ULL, 0xB50F2B3F5E42DFEBULL, 0x3DD0E3646015C29AULL, 0xFA043821A0E6AA3EULL, 
            0x94A856F41CF3B570ULL, 0x9212E4527F341E1FULL, 0xFBAA6D488278CC33ULL, 0x2F5A3AA5E6272CC2ULL, 
            0x8CF1920C6D5646A1ULL, 0x1F6E62DC4796D4EAULL, 0xD50A937D247BB23EULL, 0x0160390DAE76CC15ULL, 
            0x77B890D811E2B7BAULL, 0xCAE8DAE5E3C8B194ULL, 0x794F40354E4E1330ULL, 0x1CAAC2AFE81CCA7DULL, 
            0x5536CB33AAE72879ULL, 0x26D57D776CCC0D94ULL, 0x29179C818FCD3E4EULL, 0x69D13D4D9D4B870BULL, 
            0x1783E491063C113BULL, 0x0E2D0D5E204DC434ULL, 0xFF735AE3B280AC97ULL, 0x40D2748831966CCDULL, 
            0xDA24646E5F9DEBB8ULL, 0x83C41542F7CC7159ULL, 0xB615B0942BC837E6ULL, 0x8EAAB4B349013BAFULL, 
            0x0D31457A7AC6CA50ULL, 0x4953F75F1DCAF79DULL, 0x039CEDF01659C2BFULL, 0xCAA4B6266B6760BCULL
        },
        {
            0x33ADC03A10373856ULL, 0x5A8F151259BBF0ECULL, 0xFD0AF598E1E24E15ULL, 0xAC37A28DCCE2EC07ULL, 
            0x31DBA7DE1E5F7970ULL, 0x57A97072424CDC19ULL, 0x6AE388B4CA5C57EAULL, 0x3AEE417994E248EDULL, 
            0xB06830D8DA960F57ULL, 0x09CFE5D994094FA1ULL, 0x492FD0A48D0E27F1ULL, 0xD48EBE7289F6BF69ULL, 
            0x41B983CD5D51D752ULL, 0x4026ACEC93295AC5ULL, 0x9B67CF38ED1FDD9BULL, 0xD84214F078538D82ULL, 
            0x424B722D5B95559BULL, 0x4633F27A9A8469D7ULL, 0x4D1DA13FFACE098BULL, 0x1A583F4FAD17AE6AULL, 
            0xAE2CDF7039467C5BULL, 0x19F456D7D0F7A5F7ULL, 0x1726757E6AD0D202ULL, 0x794A3F7EFCF71C3AULL, 
            0xFE5B98C6384C1FE9ULL, 0x4CE4225275A51AE9ULL, 0x3219FE21B8AAEC78ULL, 0xFC389C28399B83C5ULL, 
            0x1F168EAD3542178FULL, 0xB8AC9D0F2EEFFA92ULL, 0x61C053D92B71DA97ULL, 0x2A51FFA586B53687ULL
        },
        {
            0xAF2757D1A8C29D3AULL, 0xEC9A754C83953DC6ULL, 0xAF6C6BAB3266297EULL, 0xA73BC10D9FF3E520ULL, 
            0xBD5FAD3F5D7BA896ULL, 0x9E61435C97E28F01ULL, 0xAAB6995C843E66D5ULL, 0xCDE6963C61DEB8D7ULL, 
            0x7471DDB22DC2A5D1ULL, 0x696237EFE007B87EULL, 0x600321A1D5F397BCULL, 0x67C33684B7CD40FBULL, 
            0x1F303DCF2CF94354ULL, 0xD68E4E45590A0933ULL, 0xC7B7A93F9966783FULL, 0x65CA0DD9F6F87B80ULL, 
            0x9CFDB731524246E0ULL, 0x8D53727DBA3D4CD6ULL, 0x5851FB16BD5B2144ULL, 0x0D0792E6C28087B0ULL, 
            0x9A835753F7257959ULL, 0x3CF41F259B47EC60ULL, 0xE132F917C2654073ULL, 0x907AF770AD8A2866ULL, 
            0x0BCBCA52DC535802ULL, 0x6D6D7F6862F087B5ULL, 0xD685B91E4CE291D1ULL, 0xD3F60F7B586DB100ULL, 
            0x2FC565E21FD64B90ULL, 0xBB37FFF50933E128ULL, 0x60285E92ADC028BBULL, 0x566604EFF7BDC08AULL
        }
    },
    {
        {
            0x683D5CC574AC208EULL, 0xD9E21179A1D5BD8BULL, 0x53A57D4DAA840609ULL, 0x38614F39B5DB103DULL, 
            0x7A650268A62172EEULL, 0xB4C45786B0AD1729ULL, 0xDCB72C0EB9C36ABAULL, 0x677497DBF8E12F3EULL, 
            0x2A9394B3485C1C5CULL, 0xE58AF40211E5CFF7ULL, 0x17E3E59A7583B960ULL, 0xAE6E93389BDB40CAULL, 
            0x3B3BDEF2BF56512BULL, 0xE94A59BB04664BDBULL, 0x23DF093E53EE70F3ULL, 0x00EEE0AB35648383ULL, 
            0x3F28CCED27A6AC64ULL, 0x0D0CB961EC2FCD3AULL, 0xADB7EEACCD6A57D6ULL, 0xE081F2BE812294A5ULL, 
            0x0999AF6DAD2A2ABAULL, 0x3B57848D658C562CULL, 0x181A849D5B3271DAULL, 0xA2C58EA5C7BD8462ULL, 
            0x011AC6119FEC93A1ULL, 0x0D36FAB12B2A6577ULL, 0x9077407225A80DD5ULL, 0x7456DD30714BE93CULL, 
            0x989737EE7A0E193DULL, 0xFEC3BEEA3785DB70ULL, 0xF57F463B7A008AFDULL, 0x4B726E366AAC7802ULL
        },
        {
            0xFB916EF5FEC5C22EULL, 0x368E7BA3E6737E4DULL, 0xD15AEE9EFC29CD46ULL, 0x989655DC99CE775EULL, 
            0xBFAD0B4758484ABEULL, 0x2C85566D6E1B4B78ULL, 0x933DF661FF64A75DULL, 0x0F411C21E55D1585ULL, 
            0x7B22C03378CEF4B8ULL, 0xCB709C1F7F4867BDULL, 0x8025D323CDD09596ULL, 0x931928AAC10041BBULL, 
            0xBEFC29429D0EF343ULL, 0x719D6121D94E6571ULL, 0xF85F7801E3FC5E02ULL, 0x0FBA26575AA8024BULL, 
            0x1C247787900DCB85ULL, 0xF84DFC21BFD16BF4ULL, 0x857D8FA17368B3DEULL, 0x08747E0E8F4ED123ULL, 
            0xD51976EADCA63F15ULL, 0x39010052A0E6B1BDULL, 0x5722943649E8B3BFULL, 0xE031D5ED3892EB72ULL, 
            0x0694F1076DB840D9ULL, 0xAAC47E1B84894DE9ULL, 0x5E7CABBD2092E360ULL, 0x596315C19C98C42BULL, 
            0xA46938CF3A61B2DEULL, 0xFC5BF71E41AB3AADULL, 0x0038EB9245871BA0ULL, 0x871B240AFD4B935BULL
        },
        {
            0x1E629BB202534F07ULL, 0x4244A9E733DD9AFAULL, 0x7AE30F9495094E12ULL, 0xE36718219D5D2FD2ULL, 
            0xD37E0EF384D90BFFULL, 0xE9A09D100EA675EDULL, 0xAD81220D2DC03F13ULL, 0x5B79211455CC2C0FULL, 
            0x214D459A1CAF6E5BULL, 0xCF39A3576F7F0C30ULL, 0xB23537FA5AFA3D4FULL, 0x04E7448D81C8C198ULL, 
            0xA76F08E7474FE3CDULL, 0xCD6E71D0D7F55BE7ULL, 0x0C252BEE80523B96ULL, 0x6587D699DFEB4BD2ULL, 
            0x586EC2D399B6B069ULL, 0xF43DB2EDAB40111DULL, 0x20AF575E3834CBD1ULL, 0x493314DFAE0C14C0ULL, 
            0xB62063EA12E3015AULL, 0x6A4CDBB1171FC86FULL, 0x32B3DEEDC652BFE3ULL, 0x730011D18B2D033FULL, 
            0x5B84F12444D62966ULL, 0xB3F0DB66BEE7136BULL, 0xD79494F0C7D28D07ULL, 0x65E4F9244624EC4BULL, 
            0x0A7BBF81CBCCB200ULL, 0x55508C1477536FDFULL, 0x828F9CE3B0265361ULL, 0xCFB228525C9E9823ULL
        },
        {
            0x92B3FC73A4319C53ULL, 0x91A65D9D5572AA55ULL, 0xD54F935B7925F602ULL, 0x621EF9A5AB496C56ULL, 
            0x3289F529A2673169ULL, 0xD74A1E6E49A29A7BULL, 0x61AFA05142AF7198ULL, 0xBEF76E2E6F0D72A6ULL, 
            0xFE76E662042FB907ULL, 0xB256E875B078BC73ULL, 0x9DF6499D3F6FECCBULL, 0xDFFD031EA801A843ULL, 
            0x0D236089597F733DULL, 0xF121BB99C7B6BE11ULL, 0x24A86D911482AE21ULL, 0xD4F7F642BB588406ULL, 
            0x66D0E10F469990BDULL, 0xDAA1B8439AF91571ULL, 0x222F46BF537E83BAULL, 0xB634CE46A380707CULL, 
            0xD04F6B780DBB3490ULL, 0xD1605670E05F0D2BULL, 0xC81AE4413BFF9B0AULL, 0x1EA3B97E2EF2655DULL, 
            0xF76F92522334F576ULL, 0xDE7A4E4221D3C6BAULL, 0x62272BB0F2C5DF39ULL, 0x917B3E876885FF8FULL, 
            0xF6CBDE4C6488D0E0ULL, 0xC848B47DFF8633CEULL, 0x628D7023C36B4E79ULL, 0x33B1ABA080965EA8ULL
        },
        {
            0x512F0AC067E928ECULL, 0x56D6F5EA91D5D492ULL, 0x7BDA88426DCE2239ULL, 0x028D9F685D74DC2AULL, 
            0xD551D6766F776676ULL, 0x11794EA8257EF854ULL, 0x353DFE14C99882DDULL, 0x84D50F7193EE3195ULL, 
            0xD3184DA3578CBD38ULL, 0x88B9198951AC2C1DULL, 0xBEF0A9C7E06ABAB2ULL, 0x8F20B30784BE8090ULL, 
            0x6C4915A2F9AF9666ULL, 0x6687AE72804199A1ULL, 0xE5BF9EE03DE04328ULL, 0xDEBF8730DB546A79ULL, 
            0x2DE793772C9D0D7AULL, 0xE54E369EF7B1FC27ULL, 0xA46539B1728190EEULL, 0x51665E3AD58781FDULL, 
            0x34AD146A04057034ULL, 0x85BD2442CEAAD4FEULL, 0x3822CD208C268C8CULL, 0xCC02F70E7C5DFF56ULL, 
            0x9F28359FA96E5033ULL, 0xA804025DD6B8D5A7ULL, 0xD31232D5CFFE00C4ULL, 0x98CEA41E905ED245ULL, 
            0xF54A0F8637ADAC62ULL, 0xB30F89E4A541EAE3ULL, 0x6D925E4B93141D92ULL, 0x23F9F06FE81CE03CULL
        },
        {
            0x1A76919058EEAC54ULL, 0x4C100A13499D89CDULL, 0x5172B8271E266509ULL, 0x551B07131A0BCEF5ULL, 
            0x553C67C883B3F964ULL, 0x5FC4275ED2AA9BE1ULL, 0xF136F002AABEBFC6ULL, 0xCDEC9321842C3232ULL, 
            0x0144A64323B29FD4ULL, 0xB0406919CC7E522FULL, 0x964F1E391CB3EEC4ULL, 0x0B5206D91429B6F7ULL, 
            0xE21FCB458500F622ULL, 0xA0FC8DA856F92C6FULL, 0xD944A3C9B1B92A7BULL, 0x3C47B9A2435E2BA5ULL, 
            0xC9924A4DC466F930ULL, 0xCDD227CE67626064ULL, 0x232540413362527AULL, 0x449BBD8AF5BB59BEULL, 
            0xBBB51492DB0CFDD0ULL, 0x9C6B1BDB6A2065A3ULL, 0x5F20F36E2D8BF2A2ULL, 0x88839840CEB158A1ULL, 
            0x93DF3A5D09459158ULL, 0xD0B210F062FC0D4BULL, 0x6EF45A51334CE205ULL, 0x615E631798D8B55CULL, 
            0x3D2164F7DA41DAFCULL, 0xF4CE21C995246DD2ULL, 0x266709C8BCBE9190ULL, 0x4D93F7A5A4053DE5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseCConstants = {
    0x4E472BC4618C6188ULL,
    0x5B3AAD9EB8AEBF8FULL,
    0x8A7C1F53D46A60D7ULL,
    0x4E472BC4618C6188ULL,
    0x5B3AAD9EB8AEBF8FULL,
    0x8A7C1F53D46A60D7ULL,
    0xF68DFBC9BC95F5ADULL,
    0x8FA049F07476767EULL,
    0xCC,
    0xD8,
    0x5E,
    0x30,
    0x98,
    0x36,
    0x90,
    0x70
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseDSalts = {
    {
        {
            0x15C3ADEEDF3205DDULL, 0x9D345681FED4CA7EULL, 0x171C38D0B0E701B7ULL, 0x0D265BF77C9538E9ULL, 
            0xC7110280394B16BBULL, 0x56209EBC51DCF869ULL, 0x2496F5A4FD1BDFD2ULL, 0xC01E76FDB5D64855ULL, 
            0xAAE67C24B3548DFFULL, 0x0175F2F7C019773BULL, 0xAC7D2E3B4BC73AEAULL, 0xE45BD1AF90250991ULL, 
            0x0196B1EED212F26FULL, 0x4F9BC83B1DAD07FCULL, 0x6A1B28D414F6898EULL, 0x23664633B83C9477ULL, 
            0xB99A4C031754806CULL, 0xDB5F2512DDDA465DULL, 0x276B659A2879F165ULL, 0xB12443536EB220E5ULL, 
            0xBBC74F3C1F337F15ULL, 0xFA49A468AA847B39ULL, 0x2E56EAAFBCEFD815ULL, 0x0357BEDE86A8AFD4ULL, 
            0x7CFF901C280A90DFULL, 0x268CDCCA75C8420AULL, 0xED6F5F4E47B3707EULL, 0xBD5C8E5BD33279FAULL, 
            0x8584AD667E48A762ULL, 0x3CF2A2F5C3BE4869ULL, 0x9812BC715FD3DDCFULL, 0x24F4AA64E9095856ULL
        },
        {
            0xA93BBCEA6DABB64EULL, 0x619F2F686F4C40B6ULL, 0x9E0CEB4C888705EFULL, 0x8052480DCAAA91D2ULL, 
            0x34E14C4F8EBAB4EAULL, 0xEE2F5823AF37FCCDULL, 0xA82EF5CBC2047723ULL, 0x7229BC561CD0F537ULL, 
            0xF1F691CB7F72AF88ULL, 0x084F2BF118AA47C4ULL, 0xCF7DCB68E8F030B3ULL, 0x7BE8536AFE345F4FULL, 
            0x049927C5173D4DCEULL, 0xBCBDEA80A6F2ADA8ULL, 0x00A8DB8BE0075D78ULL, 0x920F5A79A8F0AA2EULL, 
            0x37E373EB15CAF705ULL, 0xDCF932F4930E3986ULL, 0xF122769ACA85868DULL, 0x30717FE2F073C603ULL, 
            0xC090D2AB4FEC3591ULL, 0xB17FBDBEC6CB0788ULL, 0x1D5BCCEFB7B5EFAAULL, 0x1D2B220BEDE036BCULL, 
            0xEF6BA7F52199A9F2ULL, 0x1E4F1443545E4E0BULL, 0x6FB863FC6F62978DULL, 0xAB07E00A4E922D14ULL, 
            0xA23D490CED4FC6F1ULL, 0xB85C849B452BCDE8ULL, 0x83A9E911DD0C4D62ULL, 0x131FD7AA7A01BD08ULL
        },
        {
            0x7126629EA2983346ULL, 0xCFEBD5675D78056AULL, 0x1DCB66835013F362ULL, 0x5294DD57F7BECE61ULL, 
            0x1AB7753049A572D8ULL, 0x649053D54133B53BULL, 0xDA5A5326D3E4FA8AULL, 0x3AF0111FF3A0C03FULL, 
            0x0AE25F05878C4814ULL, 0x73A7DA9A2AE96B84ULL, 0xB282D8B974BFC92DULL, 0xB3599707259B0837ULL, 
            0x64A2295176A90065ULL, 0xB3254090482A9062ULL, 0x6314A941E7143D0DULL, 0x5E6326CA2B02B5E6ULL, 
            0xF1BBE956FBA81004ULL, 0xC751712BC668ADC5ULL, 0x223ABBDF7BB74660ULL, 0xF47DB95C76F5A525ULL, 
            0x8D73F6F17935CD20ULL, 0xD248A6AC28BE4B7DULL, 0x049D242535624C95ULL, 0xA6B8EDAA769A8876ULL, 
            0x8459E75848A2CAF5ULL, 0x0BB9F5C5E46AE275ULL, 0x94786B51B6F7C5EAULL, 0x8418068DA0BA6B19ULL, 
            0x0E76799F5E2EFB71ULL, 0x8C02D9375AF71496ULL, 0x117C5C36174436D7ULL, 0xA8522153475D7A06ULL
        },
        {
            0x411916900A03F495ULL, 0x0B97ABB9BEC5767CULL, 0xB40352258EACEC50ULL, 0x7AE6A5E4B3D8D9B6ULL, 
            0x52164D2D9B6E089CULL, 0xCA8BA20228152314ULL, 0x1412E55AADF502D0ULL, 0xC93D829E033081E9ULL, 
            0x7690EC3088A68BEDULL, 0x533C51B023E99597ULL, 0x2B4A889643F40499ULL, 0x7F938DD1D355D2CBULL, 
            0x6A19BB0200A90E79ULL, 0xDE5CDBB01C398EFAULL, 0x7644CCB4806C9A10ULL, 0x14ACDF257B9C8728ULL, 
            0x02774B82D5D23F1DULL, 0x49FE3439AF373375ULL, 0x93597C69B439DD2BULL, 0x98DB918E96C533B9ULL, 
            0xEBF81AFC854208C4ULL, 0xC04A0D5E2936095FULL, 0x53A202900E976D77ULL, 0xD28F021F03BA2979ULL, 
            0xE3600B24167AEAD2ULL, 0x25B3670931E2C7D1ULL, 0xA1E20F356CA6762AULL, 0x8D3D9CD8BBDFF732ULL, 
            0xB56F4A6DDE1C28E3ULL, 0xF324E305236FBD2FULL, 0x156C453C75141D1CULL, 0x6588E5161CE641B2ULL
        },
        {
            0x06E35C11FC68329AULL, 0x6E85C9A0BD0A2F29ULL, 0x32F0BC110845C09EULL, 0x4FF1A1DCD3084D77ULL, 
            0x5D1EA058134807B7ULL, 0xD23EFE3A56811106ULL, 0xFF7C14EFF1083A38ULL, 0xE1CADDC09B2D6B62ULL, 
            0xDE6B021C45007956ULL, 0x191E0F576385686BULL, 0x0968654C80CCBA70ULL, 0x6E24549A4D2D7682ULL, 
            0x6E318A54165FF99BULL, 0xE14C60FC61A09C86ULL, 0x4C8852CC2F111913ULL, 0x68B85C78BDCA9E7BULL, 
            0x976546AC8CA0F3E8ULL, 0x08764210635C0EB9ULL, 0xB27C72FC380F305CULL, 0x633BE4DD11EBBCBEULL, 
            0xB38312DB17F4075EULL, 0xED3353BAC08EE8FAULL, 0xAC41A66FD1605565ULL, 0x9727D5972695E29CULL, 
            0x74ED01F3D7191AEFULL, 0x572A40CD753ACEABULL, 0x55E5EA9E62BB8FA6ULL, 0x50E623C110717C25ULL, 
            0xC29BCF261F93C5DBULL, 0x81F02D731C1015B5ULL, 0x12F312E10B1F494EULL, 0x35ECF33E3E3C51D0ULL
        },
        {
            0xD97CC8C425694FB3ULL, 0xD8CA5F7D9AC56190ULL, 0x7804422E020386F9ULL, 0x632AF72AF1C7AB62ULL, 
            0x76A0567D6AB07B4FULL, 0x021C458EB7D1779EULL, 0x56C40566229DE803ULL, 0x74C27660836E41BFULL, 
            0x36705FE7795A9216ULL, 0xD60F48CFC81F89D0ULL, 0xD5048D41822069FEULL, 0x918992B0731E49D0ULL, 
            0x3FFEBEA002AA0650ULL, 0xBBF779C6C2FA0556ULL, 0x18F31895B515793FULL, 0xB4ADF40987B7F4AAULL, 
            0x0807CA723DABC534ULL, 0x3CA15572B256ADEDULL, 0xC82727F9CE9A7C4AULL, 0x293EAD9A55FCEDA2ULL, 
            0x3D7EB87F4DD7536DULL, 0xF97BF228170E295AULL, 0xDAEC0ABE87230CE4ULL, 0x87DDF7817A7764F2ULL, 
            0x053CC0B353B441C5ULL, 0xA6A12A47BDD34D43ULL, 0xF536F6693E6CC52CULL, 0xF57450582ADD122CULL, 
            0x4F48D46029057C49ULL, 0x37AB4CA0BD80F9A6ULL, 0x1023B51B60777607ULL, 0xACBF62C12490F144ULL
        }
    },
    {
        {
            0xE815D584769D7012ULL, 0xDF7D43569ADCC158ULL, 0xA69BC410F57DC0F8ULL, 0x833509CAA6D34A56ULL, 
            0xB9F83F55675B9930ULL, 0xC9DA4A2C28B036BBULL, 0xEE6108471194AA60ULL, 0x4BF05FFB49E8E366ULL, 
            0xA0103E9C901A0B43ULL, 0x55AF93558D46679BULL, 0x9FD51614386C10BBULL, 0xF6E73955FF31B652ULL, 
            0x46EF2DE8CA0C20F7ULL, 0xFC662C26F668B248ULL, 0x4D71902B866946B4ULL, 0x4E76E41A22FD64E4ULL, 
            0x75FB79F2CF448BC2ULL, 0xF7CD8BAE64FDCEB3ULL, 0xC3D6772D0F5A449FULL, 0x6F6B7B3D0A1C6D4FULL, 
            0xC12FC07AE4F02915ULL, 0xE16E818A3B42BB3DULL, 0x131B7BD4EFA365A4ULL, 0x7BA575D804BE31BBULL, 
            0x0E33985A702DACA7ULL, 0x7EC364B4C2C627C0ULL, 0x892FAFBACD772983ULL, 0x8A3D9918E54B5831ULL, 
            0x6B539608DD46E521ULL, 0x388857377F26FF72ULL, 0xA41D059D8841BA69ULL, 0x10A79E20BDB5B7C0ULL
        },
        {
            0x7C6178019E2C3654ULL, 0xD22EB73C1CEA58FCULL, 0x7477450D0E8EBA55ULL, 0x456A435D5EA9FFD2ULL, 
            0xE8244DB1BFDC7975ULL, 0x5DA34B5480478A63ULL, 0x602FF80A17D2D5FDULL, 0x37EA10950808BDA4ULL, 
            0x0950F5A3A5D8D07CULL, 0x03A95F90719AE75CULL, 0x21535E49B7B2EAD3ULL, 0xBE738D9DEC2349B7ULL, 
            0x3DFEFA62D69A0A5FULL, 0x230487AF23D434B0ULL, 0x6C109FB68E505F0CULL, 0x00F69E3867AE7997ULL, 
            0x5E05D05434758A91ULL, 0xB0D4E79AC47A52BEULL, 0x3F4CCBFE6E866AAAULL, 0x0014E8F12926E8C7ULL, 
            0x3B3EEBCE94DA9940ULL, 0x269ACE57009B1816ULL, 0x4AD770B336024BD9ULL, 0xF48A97B730599A46ULL, 
            0x508191EB1ED045DEULL, 0x27D1174BBBE23D52ULL, 0x8A6D11CF71B54520ULL, 0x63C5427577AE1C93ULL, 
            0x9516BEDAD7EF797EULL, 0xB80671E5344C90B0ULL, 0x23C9CDCA9785F5BCULL, 0x1A28E55B17CBDFE5ULL
        },
        {
            0x3931727D77C7BA0EULL, 0xA571EC59CE3EF618ULL, 0xE754DA6A52C47FD2ULL, 0xA34D3F802988C62FULL, 
            0xF2C4289E66E2B40EULL, 0x63625A80B4B3427BULL, 0xF3E8FB11918A8871ULL, 0x0AE7E457E49C6555ULL, 
            0x30F1E109B2565CBCULL, 0x88133F065EE40E82ULL, 0xD5E2E7E1D2DA2C72ULL, 0xB0209184A11641C7ULL, 
            0x336AAAB9C2723492ULL, 0x47B0A0F93C2B53C9ULL, 0x64B6C9BB0A9D39A3ULL, 0x2C923D3FDDED7EBCULL, 
            0xEE9EE10AA3098D65ULL, 0xA9AE44518EE9385CULL, 0xB90A8215BB710354ULL, 0xAE2639F86E91D758ULL, 
            0x75321E9472679A80ULL, 0x67ADFC591BE8A883ULL, 0x4972D66EB871CED5ULL, 0x2290E2A088746D5CULL, 
            0x562E835B132BFFDBULL, 0x8CFD525A18468A1AULL, 0x93D6987F528E1A54ULL, 0xA6ABBA54789EB7F7ULL, 
            0xC78E53D0F49281F0ULL, 0x6810E34F16AF9117ULL, 0x49E67E7F9018BCABULL, 0xEA8BDBD683A2E300ULL
        },
        {
            0xC89155A55355CFB9ULL, 0x0EB92A4F1E6B95C1ULL, 0xAA2D4E5AF09737ABULL, 0xA0AE97CFA83DA1C1ULL, 
            0x68B1167C677177F2ULL, 0x66789590152F7284ULL, 0x88B87A95F8CA89C4ULL, 0x194206AB3E3BD41DULL, 
            0x6E9E25430F4710C3ULL, 0x58AA6B36DA98E282ULL, 0x7898A4B1ACBFEB7DULL, 0xB624B47E21CD0788ULL, 
            0x38EC6890E39F9276ULL, 0xD27917A8CBB3CB22ULL, 0x979AF81836C3C3F0ULL, 0xAD8A9497292FE067ULL, 
            0xF9DE595CB92E9AAEULL, 0xC2E0DF79409FBD9CULL, 0x4E3AF6A5CDE9FDBFULL, 0xA6925196AA5D70B0ULL, 
            0xF3CB2920DDEF66BBULL, 0x85861439F13B892BULL, 0x2A17AABA6CCF75D2ULL, 0x33DB6FF7E346FAF7ULL, 
            0xD7E72FB0180847B2ULL, 0x7E85BFC6D292C3BAULL, 0x10CAA7242F408B4BULL, 0x133E7587083911E9ULL, 
            0xDC8A41837F913672ULL, 0x0889590112D2A2BFULL, 0x81BC9CA5DEC734E8ULL, 0xBA39F919ACE3D463ULL
        },
        {
            0xC46DB7740A0D1A3FULL, 0x1DC1937B62A0BDAEULL, 0xA2613FDBEE7224D3ULL, 0x154A860C3B189689ULL, 
            0x64D803AF0A1399A7ULL, 0xA77F4532183383EAULL, 0x727570E85B14040EULL, 0x97AF99CFD647E56DULL, 
            0x449E959F8240025EULL, 0x2B35F85162031E3EULL, 0xAF5859F3A14FB2F4ULL, 0x8B5A97F9D3E2A050ULL, 
            0x75A7B063EA2C3FFDULL, 0x216E46902BDD5B01ULL, 0x0B2B0F6EB592007DULL, 0x765894DB623330C0ULL, 
            0xE47152AE35828B2CULL, 0x99FE6D763FDFE261ULL, 0xF2627B09CC6DCA43ULL, 0xF2BFD12D2942EFDFULL, 
            0xC1B62A9DF42D1E2BULL, 0x0B1A1ECE641E484BULL, 0xC4C06350E51E9FA9ULL, 0x127E9ED6199E1C83ULL, 
            0x50B0D40153E1B7CDULL, 0x00E99C9B62660050ULL, 0x76F0DEE7851DD97BULL, 0x64C21B9641C41CFDULL, 
            0x92C7C5D92819DC64ULL, 0xC0249EC1C8468235ULL, 0x0FCFDDCF487FBC5AULL, 0xDE3DCDD17FAA5569ULL
        },
        {
            0x026F996DBC532ACAULL, 0x0314EFC2C6C24739ULL, 0x7C313FB90E952FBBULL, 0x8C45A788A9C0CCF7ULL, 
            0x2344700CDDAADD54ULL, 0x7F05868AEEDD68B3ULL, 0xA79C3DEB24E3481BULL, 0xB050D0F85EB88F1BULL, 
            0xDF6B6A7B595D9A5EULL, 0xA18FF73A246B9FE2ULL, 0x40A9EC4F3A39FF4FULL, 0x5271A1D9B84A612FULL, 
            0x05623B3DA9D41A86ULL, 0x1F15CFA087A506EDULL, 0x537A3A57AC0E684DULL, 0xE8F26541C2279E59ULL, 
            0x37F860E8DE6C276EULL, 0x4A817210743D2CDAULL, 0xEF431900F3A4AC96ULL, 0xC3955AB1D610C7DBULL, 
            0xCC71D93F39A49C57ULL, 0x66C9C010EB7F8A7CULL, 0x19B8D7883758B9F8ULL, 0xE03B92ED532E3E94ULL, 
            0x331857BD3A576049ULL, 0x52D4BE1C41B1A8B4ULL, 0xEB4FD966542D91C7ULL, 0x7AB60E1A6B878A06ULL, 
            0xB5025F730E45CD16ULL, 0x7C8A033CF05570F9ULL, 0x1BF84A407C5618FBULL, 0x318052B54FF645ECULL
        }
    },
    {
        {
            0x2EA33EE08002A7E9ULL, 0xE0F5A29CF66AA9FDULL, 0xFDC2C5CD234E5F22ULL, 0x585DD3D52D80743BULL, 
            0x8558B24435C0DC9FULL, 0x102C04D11C02ADA8ULL, 0x7898B0E43E3E3A66ULL, 0xD748DB1842ED0D57ULL, 
            0x8058E2F9A854E14AULL, 0xEE55715614E0B051ULL, 0x678FD76FAB215BA7ULL, 0x5A660C3A092FF953ULL, 
            0x888D4E009989B172ULL, 0xB40E3D421A9D2973ULL, 0x9A4C666F0244E5AAULL, 0x3F7A2DBC793A7CABULL, 
            0x075C98435D5E0C1CULL, 0xD01D5F101B1092ECULL, 0xD2F0049289796142ULL, 0xA43484FECC4AD1BCULL, 
            0x5B573EBB5B9157B6ULL, 0x75555A850C028102ULL, 0x29C29ED3000DE424ULL, 0x65B838934D6EFB63ULL, 
            0x5F25EF12A8DCF859ULL, 0x71D9A9574023B52EULL, 0x6993A8B4567D3B56ULL, 0x54F5F267B5B7F3CFULL, 
            0xE329E22C883988D8ULL, 0x00F5166A8B6CE051ULL, 0x86F2B8CBB2D36C11ULL, 0x3704405811FF92A6ULL
        },
        {
            0x104EACCB3BDBAABDULL, 0x909E4417D3A71FB0ULL, 0x67BC008908EBB275ULL, 0x23917CADFA5A2195ULL, 
            0x35BC5EB5420E8CDEULL, 0xC10B881EE2984791ULL, 0x84D8529341B2C3DCULL, 0xD06B74A84CFCC903ULL, 
            0x1A60CDE0AABE00D9ULL, 0xB9D03C35F5E553BEULL, 0xB64D9A959902EE03ULL, 0xA4AE9797B30446DBULL, 
            0xD30B9A40D0821B89ULL, 0x4F971CF8A169E58EULL, 0x5D4D3C61CC264EE3ULL, 0x452363EE42C19562ULL, 
            0x7325398F23D8D78DULL, 0xC5B36073F6AB66CEULL, 0x62A4FA55A673F2BCULL, 0xD982D48F22CF47B5ULL, 
            0xE41D8FB34C04A23EULL, 0x962E50ACB40D1D6FULL, 0xD83806320931E748ULL, 0x07DCBFECB4523B2FULL, 
            0x48DB04C30FCF0AC5ULL, 0x842A69CE1694E61AULL, 0x7BB7C7E749227FF8ULL, 0x6BCEDE5C6C72143DULL, 
            0x2D8808A7D44ED6CBULL, 0x4D5B2D846C2D518BULL, 0x72DF4AE324F56E46ULL, 0x584265409D1ADD09ULL
        },
        {
            0x2D7A15CDC6F63E78ULL, 0x43DC57954DA382F0ULL, 0x243BB8D3691D5FC9ULL, 0x53FDFF1BC836F7AFULL, 
            0xA832FD7D45565238ULL, 0x6749581D0E0E1D65ULL, 0x6CACDD32F9C96148ULL, 0xFC904B03453AFE38ULL, 
            0xEE853128EEF047D8ULL, 0xEA3AC357558B807BULL, 0xF1F404FCCA117A92ULL, 0xF56D9594195B4F8BULL, 
            0xEB493A84E2E0DBEBULL, 0x045D882A2860F63EULL, 0x760EAFCC08A1D495ULL, 0x027D7F19913ECA7AULL, 
            0xDD310A453D89FB23ULL, 0xF2D51EA3794B2598ULL, 0x86CEDFCA5CF83BE9ULL, 0xA934D6A97718EA02ULL, 
            0x9E558D10410C0482ULL, 0xEA367E43F91D6C30ULL, 0x115E6B79794B78DDULL, 0x239598AF32E06A3DULL, 
            0xE713FD9403034D1CULL, 0xCCF0C349D9FF7925ULL, 0x107800E595571E30ULL, 0x3950524D1398892AULL, 
            0xFA3DD209AB245B53ULL, 0x4F53F391DC22B35BULL, 0x1B5C49A56DA03F36ULL, 0x044EF5361263BF80ULL
        },
        {
            0x6FAD4872414B00D7ULL, 0x995A7A67E7E8D6DAULL, 0xA599F94743A43618ULL, 0x59EF35C4ED9692BEULL, 
            0xE1FFF0C944564438ULL, 0x38530355CE128FB0ULL, 0x6AB271089349A9E7ULL, 0x7332B53F0AE83782ULL, 
            0x6A41413B1C0FB161ULL, 0xE0E6D731E4507F3CULL, 0x87CB9380FC613215ULL, 0x8C4D5B92B6379017ULL, 
            0xDB206E9710EFB70BULL, 0x34C738940014732EULL, 0xB131E3BCEC99C39BULL, 0x22BB5DDDAA5A2A9CULL, 
            0xD06C077442D6AEAFULL, 0xBFA4C244AE513B93ULL, 0xF3394AAD1E184F76ULL, 0xB46437FD36174577ULL, 
            0x57FC6503CCD66530ULL, 0xA71A5B53753A7E7AULL, 0x256F54DFBDF68267ULL, 0x5D4EFFC7656EDF03ULL, 
            0xDAD0C801ADFBF74DULL, 0xB3AAC99DCA67123AULL, 0x457A782B1C548E84ULL, 0x51848870A596741EULL, 
            0xB4645C2FBC633512ULL, 0xDB4FC1D59242E584ULL, 0xB01B2AF3957CF5C6ULL, 0xC8BD8A5724EA9AC1ULL
        },
        {
            0x8C656058BCD79C54ULL, 0x291DE7CFA6703171ULL, 0xE518EECB4521B512ULL, 0xC52D29A5DB7AB852ULL, 
            0xC454947C582468A2ULL, 0x44A82CB0A103ACD0ULL, 0xD393AA1349F0A1F5ULL, 0x20C80AFCDC205078ULL, 
            0x6488E66A299FE93BULL, 0xC1E2E89ADABCBD47ULL, 0x956C9EF2A612B70EULL, 0xEFFF929CF93038DCULL, 
            0xD358968A28CF36ECULL, 0xDF851082F967DCD4ULL, 0xC6C49BFAB849A24CULL, 0xFB70F3F68BAEF230ULL, 
            0xB82A090206D34CACULL, 0x74928066086BC4CEULL, 0x1D6E5D3427583B42ULL, 0xB2601AE429B34022ULL, 
            0x65CF0E76AAC269EFULL, 0x1F53479CC895B86EULL, 0xD7115B7D96BDC51AULL, 0x18BB8C5FFD46E303ULL, 
            0xDA64883C9895FCB6ULL, 0x624BD96F479AA3E4ULL, 0xA23B6963D37A7830ULL, 0x3B42B8FFD8F43111ULL, 
            0x3D11453DD45D37F4ULL, 0xCB3BD1D596E0391AULL, 0x5AC5163F1E94FFEBULL, 0x8D31A8D3DD6FAF8FULL
        },
        {
            0xC5BA9B2335A9A5EAULL, 0xDD1469AC31DC5222ULL, 0xC67CD94FBEFEF33CULL, 0xF32A81BF03567032ULL, 
            0x611D3101147053E6ULL, 0x008761C338B75138ULL, 0xE38AFAFA6CDCABF3ULL, 0xE84EAC11870E3A1FULL, 
            0xBD974B26958A1DF8ULL, 0x08579F5BCBD78502ULL, 0x935386AF7DDE7DE2ULL, 0x0F3292EC03C6418EULL, 
            0x1F78C2935EE837E8ULL, 0x90C152085F63AC48ULL, 0x083514966EE0D779ULL, 0x7ABA4E8087978DAFULL, 
            0x003E08BBF01A6B3DULL, 0xF487B8330B686FA2ULL, 0xE46DEFEB3E211E56ULL, 0xC1B56A1639A1AB73ULL, 
            0xBF73DBBFD58A1567ULL, 0x3B4DC4B2A6BA6F53ULL, 0x4E010E10699313E1ULL, 0x2CC9938865FC0172ULL, 
            0xFE5932653E1F0217ULL, 0xFD90FE57AA8C0C2CULL, 0x7E98345C97C0AAAEULL, 0x3382620EF24D733BULL, 
            0x3CEF0422FAD3108AULL, 0x71241C80180ADA62ULL, 0xED823DFADD455CFAULL, 0x12E37F669C96EB1EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseDConstants = {
    0x1F258E812C1B9479ULL,
    0x183C5C3914384581ULL,
    0xB1CE029FA7121110ULL,
    0x1F258E812C1B9479ULL,
    0x183C5C3914384581ULL,
    0xB1CE029FA7121110ULL,
    0xA080D04E1187120DULL,
    0x6989AA5F19CEC7FEULL,
    0x20,
    0x5A,
    0x6F,
    0xAC,
    0x57,
    0xDC,
    0x88,
    0x48
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseESalts = {
    {
        {
            0x7BA42D4E3B4FF7A5ULL, 0xCBB5ED20368B7D76ULL, 0xA5422086C31A59E8ULL, 0xD168673ED15DB4D3ULL, 
            0xB97A75178589195FULL, 0xC0725133B96B5885ULL, 0x0969BA7FDE2B8F4CULL, 0xA5FC64897CB2ED04ULL, 
            0xAA0AD124097A5C9BULL, 0x24DD0D9A40FC3B4EULL, 0xBBBC892BF4C4B7D1ULL, 0x456DFA5500E8ED34ULL, 
            0x659B94E5AD688A1DULL, 0x02DDADC922C0CB7BULL, 0x2EB41572AA20F969ULL, 0x18E19E97C860154CULL, 
            0xE6986DBDB493F290ULL, 0xE2E79A63871F1981ULL, 0x4F1E8390D86F5408ULL, 0x397C509570BEECBEULL, 
            0x31C33F8E770023E7ULL, 0x47E8B4E6BDCEADF9ULL, 0x65FE52D6E55A5DBEULL, 0x09FEE268403F509FULL, 
            0xCD78C50B6F839A5FULL, 0xAA1B229DD87F1FCBULL, 0xDFDB0EC40AD75300ULL, 0xF84A7AEC060E1468ULL, 
            0x49C1F0EE5D679748ULL, 0xBE3F5F930FADB38CULL, 0xF711B53FEBC9905FULL, 0xBCBBAD85F85EC248ULL
        },
        {
            0xC3786FFBA5BEC479ULL, 0x82628ECD12EBCC0DULL, 0x706CB2AF827940D4ULL, 0xF7ADB53D9A56CEE6ULL, 
            0xFF9059E0CFDD49EDULL, 0x1E8D99E62F5F579EULL, 0x2A628078A73EB420ULL, 0xB96C54ADCE2D17B1ULL, 
            0x260D35C49058B441ULL, 0x997622FD2808DC0DULL, 0xF2F348306C34743EULL, 0x808067E04AEDC8A7ULL, 
            0x5F987B20DB1BD1DEULL, 0x9057A1C737C2DE5FULL, 0x3829171411B248C6ULL, 0xB6D43E349D1BC988ULL, 
            0x0E85C46C4C5BDE64ULL, 0xEA1174325F43EABEULL, 0xDBE0B5C6111E6148ULL, 0x128252F7E1EFAF41ULL, 
            0x6C808ACA1BDE6160ULL, 0xEC07FB54DA4F7759ULL, 0x6FF31BC03CDDD242ULL, 0x3B5A96276B7BC2C8ULL, 
            0xA39F613894245DE3ULL, 0x7DD667595915E0C8ULL, 0x70A31BBEB7E6E563ULL, 0x613BA3331599AA5BULL, 
            0xAE92EF2BAC1AE1ADULL, 0x35B6ADB0A92B3121ULL, 0xEEDDE1F0169FF536ULL, 0x19D33FDDEBF5C7FAULL
        },
        {
            0x09223C9FCCE24CEDULL, 0x738826BFAE369B4AULL, 0x5015D8C405D9DB90ULL, 0x97D7674476DC9C08ULL, 
            0xC0756ECC69682DC5ULL, 0x35FFC28CD7AF9742ULL, 0x2E569A52CC4B626BULL, 0x51C09F77AEA66FB2ULL, 
            0xAE265DFDAF25F40DULL, 0x612FB3D8BF48C455ULL, 0x9BA7FF42DE5B4F69ULL, 0x491CA92242020385ULL, 
            0x4250C43EDC66E9C1ULL, 0x727D47A5E7D6B72DULL, 0x4FE1E8222BE7E669ULL, 0x6ACA5E61CE55C1ACULL, 
            0xF5B14714A591A5E8ULL, 0xDF697F789F78C77AULL, 0x52BE37CEEDCBDA26ULL, 0x5971D92B68E7D248ULL, 
            0x6C97889F52FB67B1ULL, 0xCBD8C47981148243ULL, 0x35DF176E71056FDBULL, 0x4E581E687312BB42ULL, 
            0x651DB73D50EA2F66ULL, 0xADC8C45A9390F41DULL, 0x4C860B98B0AC5AC6ULL, 0x137AF77F3858665BULL, 
            0x09584A5E3F7F911AULL, 0x94DF747006BFA3EBULL, 0xFB63074FF94D36C8ULL, 0xC454B9AA5D9EEAFDULL
        },
        {
            0xBA25974A0FB357C0ULL, 0x136B4C0BC4D25AEBULL, 0x573D4A7BD60398BBULL, 0x75D4F9D65F823D06ULL, 
            0xC672EFE27F0031A6ULL, 0x7059C5B4128D58B3ULL, 0x95CB609FCC50DA61ULL, 0x1D2C61C36F5C4183ULL, 
            0x6DF2513302F35972ULL, 0xDE9E4123B956C6F2ULL, 0x6E614CF0D08D7903ULL, 0x6DF77ED6A44CA486ULL, 
            0x185A7D8D65562B6CULL, 0x684E8484F8CA31D3ULL, 0xCF07C837F14B8D02ULL, 0x0A79A512303175E2ULL, 
            0x853255BD09450701ULL, 0x26D8071D15293FD0ULL, 0xE312E57658E1A02EULL, 0x283A1216B29768ACULL, 
            0xB112B8BA2675BCA7ULL, 0x5FE913E556FDCFB7ULL, 0xA58BBC4FE77AB28AULL, 0xE42F1BBB18FF7FE8ULL, 
            0x19130C363A9F5775ULL, 0x609CBFA612D93C19ULL, 0xBCD8F8DEBA8D5502ULL, 0xF9216F3A41439EF6ULL, 
            0x7675A1159B9E7A59ULL, 0xDA864CA1050E7964ULL, 0x760D151C986A80B0ULL, 0x4A91C844896A1A03ULL
        },
        {
            0x17024CAFED67AF10ULL, 0xB759EF7099D7FC5EULL, 0xE001BAD199F0F757ULL, 0x5732C3A67F067DA0ULL, 
            0x6A8EFDA94B51D7B2ULL, 0xEC8134D3A5F7F39FULL, 0xD1A92A88938DE141ULL, 0x8059C8E0457B6D26ULL, 
            0xEB98ED4B2B0E0B98ULL, 0x5C3108EA527C63D2ULL, 0x5F8409586ECE4029ULL, 0x369D205BBB92C5D6ULL, 
            0xD0DEBD6CEA68A15AULL, 0x79CEE1FFD5B66D7BULL, 0xAEA1D3BC9649A168ULL, 0xC0D417430967C7B5ULL, 
            0x066FB47973D01DEEULL, 0xEFBBC80CB2A151EEULL, 0x123E292D439EECDEULL, 0x86BCCF635A069B58ULL, 
            0xD193FF7636C06DCEULL, 0xF90A5CFDBE36FE49ULL, 0xF9941915AB66E67AULL, 0xBAB58851078AA853ULL, 
            0xA0FAD00133605826ULL, 0xEED44F4AC5051BB6ULL, 0x18AE148430613F4DULL, 0xBA5A9B211ED88508ULL, 
            0x8EAE149E5DC20818ULL, 0xF049EF4AA8596469ULL, 0x8EEDA1E5F6D7B6CBULL, 0xBC75A03B4F556255ULL
        },
        {
            0xEC94AD9B0524C10DULL, 0xDCD2E45D90D32F54ULL, 0xBA5C45D02999C658ULL, 0xA7DC232A97D0DE62ULL, 
            0xCE41C5A8B1FB1A09ULL, 0x018DA75CF2D8011CULL, 0x7968462CF4F82B81ULL, 0x170EDBF1862E65A5ULL, 
            0xBFE7715D63FFB807ULL, 0x964958B692D3754EULL, 0xE89E4BDE3EAD5861ULL, 0x1598E30E24F83D53ULL, 
            0x55B329F141B35AC2ULL, 0x0B64331FD369FA0DULL, 0xA6FE1B4DE858BC90ULL, 0x699AAD867E73FA3CULL, 
            0xFB8A0CB5007D75A8ULL, 0xEF43CE9285042BCCULL, 0x2DA361B37D69A1E7ULL, 0xE1D98CD02A3C599CULL, 
            0x5BF38CCDEB5B4207ULL, 0x20131F5A99A7FD5BULL, 0x79B4C82EF1C4717BULL, 0xFDD1FDF6243469BAULL, 
            0xEDE08E94AEAEA423ULL, 0x4DD95809544720E7ULL, 0x3F41C73E7C738D70ULL, 0x4EF9BA2E27B28164ULL, 
            0xB58DB6AE70A97302ULL, 0x003F0AD1877CB465ULL, 0x7EFBD62E95380E1DULL, 0x8DE8FF3D489E1829ULL
        }
    },
    {
        {
            0x2E1921F955F1BECCULL, 0x6398C89C9AB35592ULL, 0x0B2410BEEA55F564ULL, 0x76B6F75ABC1A681CULL, 
            0xDA58A87F32DFD02AULL, 0x304B6A86F6A69FA8ULL, 0xA974527FE4F60AC7ULL, 0x369290ACA9738954ULL, 
            0x2624848F58B17AE5ULL, 0xFFE954D82B853C93ULL, 0xD24A6FA44A10F521ULL, 0x3D8BCEEFD7AD3CF8ULL, 
            0x7E4C6F59079492FCULL, 0xFE7658386E1660ABULL, 0x9063B029108A0EB3ULL, 0xFF78210D2EE16B73ULL, 
            0xC5AA12F8635B3C42ULL, 0x133C87FBEA8D37DAULL, 0x72FBA711F6564100ULL, 0x240318E569EAD633ULL, 
            0x2C535C85F0E7C949ULL, 0xBA8BDAB954F7A46BULL, 0x40EC557CD5920DF0ULL, 0x672618BEDC5C842FULL, 
            0x20D76B32BDCB3567ULL, 0xEA63A3F4DC832156ULL, 0xA741781CADF61DA9ULL, 0x0F27654128E0F42AULL, 
            0x5DC4537EE7123385ULL, 0x717AC1D0B5DCA247ULL, 0x49DDCAA353EAB8C3ULL, 0x2963D52BAD6D4AD8ULL
        },
        {
            0x1A94217C530D1221ULL, 0x8A07D5D8E03A373DULL, 0x550EA157D89D139BULL, 0xC1C7E105601AB5ABULL, 
            0x3DECFEE856EEB123ULL, 0x193A429C3306A6D3ULL, 0x1C902EE1D7073AE1ULL, 0x4315F665F3F9B387ULL, 
            0xCCD74B6CDB3D6933ULL, 0x593FD1D4229A6D32ULL, 0xFDA8E48282C16015ULL, 0x926240521B35A7FDULL, 
            0x2C55FAE5BFE22A79ULL, 0x06DED683BC9D0833ULL, 0x35E6AAD812A385DBULL, 0x5B9927E6556E7A31ULL, 
            0x07FC67DF938AC6ECULL, 0xE20788CB1E679B72ULL, 0x0CF22D88743E5554ULL, 0xFC57B411A816572DULL, 
            0xD34DEAA0E73E2240ULL, 0x0D5CD934304FB695ULL, 0xDD2119DACE48501EULL, 0x9DD3580C8D9616BEULL, 
            0xB3DBA35A345ADCCEULL, 0x1A11CB6B9FF99199ULL, 0x488D024227306846ULL, 0x7EB70D48493F1B08ULL, 
            0x6376A6B84E9A43CDULL, 0xDD1969D3F41F401FULL, 0xDDD4601F38DC09BBULL, 0x7421035CCA2A6A6CULL
        },
        {
            0x9D0B675D7B8D1966ULL, 0x8BCDC2E09730C8BDULL, 0x357041BCD95D6171ULL, 0xA7C561350AEC35C8ULL, 
            0x2B3F76C9B5600A9AULL, 0x7C2966EC3241AFBAULL, 0xAA50A9AE66F3825AULL, 0x1CDBE60751D49B0DULL, 
            0x4E9F300496017942ULL, 0x7FB6F408CD6B7F64ULL, 0x785B622050BA0A63ULL, 0x7C5CC1CE146501BFULL, 
            0x67399EC14B399F23ULL, 0x1640F5C6DB55D2F7ULL, 0xABF276833732C286ULL, 0xC21ED39532EF08F7ULL, 
            0x8FCE4F90749A8820ULL, 0x216BF8491150BDA1ULL, 0x4A1EB5D967BFE344ULL, 0x42A959E80FC1D93EULL, 
            0xE098EDF30D215E11ULL, 0x9273BE551F8D1D41ULL, 0x57B4720AB487C888ULL, 0xED089B1C737E9CB2ULL, 
            0x5B6293F2E65D4C40ULL, 0xF4950D2F04FEACD2ULL, 0xE804CE86C9E519CBULL, 0x8A984979DF054209ULL, 
            0xC5533229110E3984ULL, 0x18D8361C0FD3708EULL, 0x76ED8ABD7DDC7D3FULL, 0x741CB37D554592E5ULL
        },
        {
            0x792F13C6C60D014DULL, 0x12A38A04AE1E0469ULL, 0x9FE1D00E7FA5C98AULL, 0xCBBB5C2F72994093ULL, 
            0x9847FDE9C0DA79CBULL, 0x0E26C8F9C9366F21ULL, 0x21E5BC891657984FULL, 0x983AD0574B63979AULL, 
            0x305A2E2AF156A0BAULL, 0xB5A5E838CDB6D658ULL, 0xCE497E7BAF9EA9B1ULL, 0xB661DE670473A443ULL, 
            0x8D57CF918F0A5B1AULL, 0x9EE55C3CBFA85038ULL, 0xA718C64ABD475C1EULL, 0xEFA6656673C615F7ULL, 
            0xA340DECDE7A92209ULL, 0x2EA159B9879F2DB3ULL, 0xCF70824F0144F73FULL, 0x0730B82F50EA8B2CULL, 
            0x235509024C508290ULL, 0x5BA1323355535C4EULL, 0x62383CDCEE8118EFULL, 0x7A9675070DBAAEF6ULL, 
            0x9FC6239F719232B2ULL, 0x1D31C7884BF210AAULL, 0x4F2EFF3654A66CCDULL, 0x4555117A5FF350EBULL, 
            0x91DA9A46DF838D19ULL, 0xA7D5D906C40B7756ULL, 0x72E9D584878DD227ULL, 0xCCDB392FC91B4594ULL
        },
        {
            0x98044C2918D54BEFULL, 0x28E90B6F551EFC15ULL, 0x1B6643557D9C6DA4ULL, 0x9AB06539113369DEULL, 
            0xC0BD59B87889F858ULL, 0x61D72E97C2304D2DULL, 0x3BD69219F8C12403ULL, 0x7601EBE7523D4A36ULL, 
            0x344CFB16EDC8217AULL, 0xFECAE07920289E9CULL, 0x031C90450A0B4EADULL, 0xA5B522AB44FCCEBAULL, 
            0x19CEFCC094E383F8ULL, 0xAA961D00E36DFBBDULL, 0x21B3AE3BBC4D703AULL, 0x4F427B3FDD3050DBULL, 
            0x60A47783DFA0A912ULL, 0xBE1AA3A77B01FD3AULL, 0xBF126B75E9D48A15ULL, 0x26391F74DBD64697ULL, 
            0x2BEDC16C6E7B3099ULL, 0x1C4EBE46265ED0D9ULL, 0x439E5D349450FC93ULL, 0x5E74ECD4D83FBDB9ULL, 
            0x17E2F2FC897B1E0BULL, 0x4920868C2C74BDCEULL, 0xA2D1C99661F135EAULL, 0xC71EC1B09F1C301AULL, 
            0x274EE6A3FB7FCF6EULL, 0x4949D90A2A48A209ULL, 0xABA67AF59791FF6CULL, 0x1486E95ED7DABEECULL
        },
        {
            0x1A0756B7FC2E1650ULL, 0xCE7E41170165A259ULL, 0x1CE35F6B4213B610ULL, 0xAF3EF53D62F9E35AULL, 
            0x3083740F08EFFC99ULL, 0xCD86AA3F08FBA410ULL, 0xFB198EF05F73BEE5ULL, 0xA1F697B8ABBCA868ULL, 
            0x503426B15B47F8AEULL, 0x522EB6C415313BF1ULL, 0x48B7DDED3EE39259ULL, 0x3D313553D3DCD0DBULL, 
            0x0E5C3C792FC6AD2EULL, 0x0B1E8ACE36D80A45ULL, 0x83A69B4AB8F94ABAULL, 0xB6F1F9FC57602378ULL, 
            0x6783E5521CAC0D5CULL, 0x40656F4F206F5065ULL, 0x81454D45351C0EB3ULL, 0x0DECED4651834305ULL, 
            0x650CB4521AD546D9ULL, 0xC35B52CF2783C31AULL, 0x99FD74B23425C275ULL, 0x3B4F85C739183211ULL, 
            0x3BD22D3AA74156BDULL, 0xAC15019B61BE2B16ULL, 0xAEE0506CA874B02CULL, 0x77F4C2C0B5B0798EULL, 
            0xD31E2AEC05F90808ULL, 0x9A30BDA4EA5CDC1FULL, 0x3D1777C5E97AA4F8ULL, 0x6D60B3104EF1C711ULL
        }
    },
    {
        {
            0xE0BCE08F7BC44FFDULL, 0x7E1F0D5402FFC60CULL, 0x627FA4FEE34B4DD7ULL, 0x4060CBBD48C25200ULL, 
            0x5744576A812C4AB4ULL, 0xA304A3B0A5B33850ULL, 0xCBC07A73E4142741ULL, 0x97C1CA232ED4B51DULL, 
            0x5BF7A71E60480F1CULL, 0xD5F563571612F339ULL, 0xBA910D50EB6963EBULL, 0x6EBD75DBA668B532ULL, 
            0x8C7CA533698B11EAULL, 0xAC3B853B771B569AULL, 0x595247F056D2DB82ULL, 0xB93DC275B8A7CEC0ULL, 
            0x5D1F34B2CB039BCCULL, 0x3C7BC9CF37C338BBULL, 0xE61D839E7AD0BC71ULL, 0x802D26F7671F2A6AULL, 
            0xCE54B9559AD45DA4ULL, 0x96D1C2C93BF016D0ULL, 0x33E7CE2BB090DCE6ULL, 0xFE9A8C4ADBA0485FULL, 
            0xDE318E06F8056810ULL, 0x493EE2A3189DA616ULL, 0x7949AEA06BE86EBDULL, 0x3BA77EFE9E0EC0F2ULL, 
            0x9FB39CFBE1364ADCULL, 0x6496F26ECF9218F7ULL, 0xC4DCD649819425EEULL, 0x56AAA5D126DC2BEBULL
        },
        {
            0xD494C80B4253EBC4ULL, 0x044C1B42E45E633AULL, 0x6BBEE3D83F1A07E8ULL, 0xA87600E0B92D4A96ULL, 
            0x2B11A4F59B731083ULL, 0x3BF03123DA662E78ULL, 0xBB50C19611E0377BULL, 0x7E27FD8C2824A1DCULL, 
            0x2817401925D75E9EULL, 0xCA57472CF3154DEBULL, 0x6BFB8909366DCDF1ULL, 0x8AF6945DACD06E01ULL, 
            0x83A0D05E19478727ULL, 0xF7B70B0043B5503FULL, 0x2678771A58842020ULL, 0x80122C50DC0CCA47ULL, 
            0x46FFC457EF4279F0ULL, 0xB3380732393A4937ULL, 0x629452151EA78545ULL, 0x5808ACAE10288A72ULL, 
            0x96BDD4D36ACBFCEBULL, 0x3352A1B332A289ECULL, 0xA22FA309E5292E9EULL, 0x73B72D15DAB5A348ULL, 
            0xEC236F88F502736AULL, 0x858E4E9E5D16B70AULL, 0xA2A98A91E852C6C0ULL, 0xA49C237B3533D090ULL, 
            0x0EF6643142D96BA4ULL, 0xBB4A97B6305E039EULL, 0xF037DAF916C5D0C0ULL, 0x95F728BC3B8D4F23ULL
        },
        {
            0xF76B64D297105646ULL, 0xA9D8ED6A2631CA40ULL, 0x4C4959787BC60D1AULL, 0xF078B490D33BEA92ULL, 
            0xD12EA386060CFD93ULL, 0x9567BB97B5CF1A3CULL, 0x57B8BE54D5BC6375ULL, 0x6B000DE72C117482ULL, 
            0x373B4856FE355200ULL, 0x9FED5867FF98A978ULL, 0xAE3C0154A76BD34FULL, 0xD14B011BF906AD5CULL, 
            0x36FA7F410C511433ULL, 0x72FC4FC5084289F9ULL, 0x28415D7241F6838BULL, 0x3CE706DBF1A95900ULL, 
            0x518C0FF9DB2A37BAULL, 0x13B45AAD0C563C3FULL, 0x19CBCD2386CB2045ULL, 0x862CF9F380E0C5D1ULL, 
            0x38BFCFE8FBBA1A0EULL, 0xA076D454123EF229ULL, 0xE849684869E0B191ULL, 0x9D165C56F332C143ULL, 
            0x984D3F27F5E19219ULL, 0xC5BEA0737F25C0B0ULL, 0x956DD42A3C0B153FULL, 0x882D3D486EF4BA2CULL, 
            0xBE0B9073BB13E622ULL, 0x30928E6E63DD1BCCULL, 0x5E1C3A7B94FC571DULL, 0xF73AA6A7C7BD6F16ULL
        },
        {
            0xBE455BCAABA8C0CAULL, 0xD62A0BDE354F86FAULL, 0xF8E3DD678740915CULL, 0xC1535072F089B466ULL, 
            0xCB13D3503C0F0863ULL, 0xC0EB1B0D3011B8DAULL, 0x18AF8ED539780DB9ULL, 0xF903097C9D6F37A1ULL, 
            0x2668B00339B06A3AULL, 0x69AEF30961CCBF59ULL, 0xFC8C12C14AFB1D9EULL, 0x2FCC704500D83555ULL, 
            0x9B749B5B0AF1EFB8ULL, 0xAE420EEF2A7F9145ULL, 0xDCA3DB2647B189D3ULL, 0x133EF1E7D4616D3BULL, 
            0xBD4C9C50706A7137ULL, 0x77D3A1F77007F6AEULL, 0xD01450B618118E05ULL, 0x4651ACF2EA5B5F3FULL, 
            0x73DCD379C9708606ULL, 0x1575AF5D2130C10DULL, 0x617826B472C81624ULL, 0x870B5DC522F8A27EULL, 
            0xD89A69C2DCD198B6ULL, 0x990644D36DA9F79AULL, 0xD23E0FF9C802620FULL, 0x687A0DCC4A4AE325ULL, 
            0x703D189BF4A64934ULL, 0x11106BE4428B0FB1ULL, 0x4161473E7179CA8AULL, 0xEF12112034BD3613ULL
        },
        {
            0xF139E821C7838778ULL, 0x613C0309DFD2D91DULL, 0xDA35A6DBB5580635ULL, 0x38AAFBA58E331FC3ULL, 
            0x744BEB3E9DE9DEFFULL, 0xEF29FD9CE49C6172ULL, 0x0A30EA5FBBB572EDULL, 0xD8C538BC5CB88295ULL, 
            0x9A3FC354119A90E5ULL, 0xF8F801468F166633ULL, 0x3F583F8C7389CD95ULL, 0x464B1602F1F5EF85ULL, 
            0x55C92F7D18C75401ULL, 0x9B0765C25AB59300ULL, 0xC6F8F9816AA8C505ULL, 0x2CED84C26D70A379ULL, 
            0x5D3FF47D5168E1FFULL, 0xED41CB7CFEF621A1ULL, 0x49D0E091496231BFULL, 0xB526F8958CEF693DULL, 
            0x7AF4F3F7B3E114DCULL, 0xB7C83A0AC92BD2E2ULL, 0x2B9FB1B90E8231F8ULL, 0xEE413D978AEE38B1ULL, 
            0x76BAD6D38B744751ULL, 0x29570D29F038B424ULL, 0x0C8AC26E04D12CF0ULL, 0x011104B2405B578CULL, 
            0x78276C51B3D77853ULL, 0xBCD55376BB2E8B1FULL, 0x325519977D410CF9ULL, 0x895574F0CCD05F90ULL
        },
        {
            0xE0005A0A21BDB404ULL, 0x17F576D20EB74E00ULL, 0x571DFBE0C931AED1ULL, 0x70345BCC36114D25ULL, 
            0xA5248C8A7D21A661ULL, 0xD4E8426A38DCBEF4ULL, 0xCBE1A36F503135A7ULL, 0xDD8D1A375C63E2B8ULL, 
            0x88B918A65AE0A9B6ULL, 0xED2B1A092DDB988CULL, 0x05DAFA6AABEFC831ULL, 0x5AB8D68A67DD3A27ULL, 
            0x5E33F48D853F7703ULL, 0xFB42A6E35809394AULL, 0x488FE6FF2482C8DDULL, 0x7DE7C1A6EEA25466ULL, 
            0x931B209C85A289E1ULL, 0x7805193C90E96A94ULL, 0x7167AA51A64960EAULL, 0xD890AFEC047108B6ULL, 
            0xA843AF0ED95BD441ULL, 0xDA13F1B689D64318ULL, 0x26E85C5E5E8DEF74ULL, 0xD68D7EBC88BB279BULL, 
            0x602CB1F7F51F36D7ULL, 0xE50A5CFD6A0D4716ULL, 0x9DA4F1E1D1BDFA6DULL, 0x061827F603A6F6B2ULL, 
            0xF8151E18E27FF5E9ULL, 0x703F5B64A78E8A41ULL, 0x937A0E15FD015401ULL, 0x627D2E6AA7EF867BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseEConstants = {
    0xC5952C1B7598B899ULL,
    0x3E014347FF1CD1E8ULL,
    0xEF7BAC294C45637FULL,
    0xC5952C1B7598B899ULL,
    0x3E014347FF1CD1E8ULL,
    0xEF7BAC294C45637FULL,
    0xBABE1858457A7CD3ULL,
    0x3C8E0F6840D477D1ULL,
    0xFB,
    0xD9,
    0x10,
    0x18,
    0xDC,
    0x8E,
    0xA4,
    0xDC
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseFSalts = {
    {
        {
            0xBC64900EAD67E1D9ULL, 0xDFF526A3FA1DD473ULL, 0x188FAA13BA2C5595ULL, 0x3B5E2217BE554988ULL, 
            0xEFEC1959F66FBA8DULL, 0x349708D70FE00F28ULL, 0x01563369BBC3E59EULL, 0xF08291137E054163ULL, 
            0x008A63834EA11CA7ULL, 0xBCF2523E1104F0ABULL, 0xABD34536462C85DEULL, 0x5E80ECBD42ED99C3ULL, 
            0xEA0707167EA76222ULL, 0x7EC54B0C71F03A85ULL, 0x6A9A678A49BC7E29ULL, 0x78D926C7A9F4F460ULL, 
            0x84538B12949C38FFULL, 0xC284C7B9EF689F1EULL, 0xC1F0CE2E7753BCEDULL, 0xEC94D136844C7F21ULL, 
            0x2D54143FF2B2742AULL, 0xAE002C02C8977FD9ULL, 0xE0B5B243139093C0ULL, 0x89D72ED846CE5DCDULL, 
            0x341DDEFC4C544240ULL, 0x7AA9BA4171D01BA8ULL, 0x86DA19FCEEBE8570ULL, 0x18BC4E2B8D7CCD5BULL, 
            0x7B3C4A83F044CB67ULL, 0x09552645A63F2474ULL, 0xB7EF5C311B0908E0ULL, 0xD3ADEEB7F1785DA2ULL
        },
        {
            0x5523A4D0C7943799ULL, 0x8570780C81ECC24EULL, 0x35666694A1B0A61CULL, 0x47CC7FCC88743BF6ULL, 
            0x755C06C98BE7E401ULL, 0x42B2CB1EDD8A3C5BULL, 0x9F668DB239C08063ULL, 0xE9C50F57ADF8036CULL, 
            0xC956AAA285169080ULL, 0x1815C03C0CB95638ULL, 0x2694CD91A3A1D621ULL, 0x43AC81C9383F4A5BULL, 
            0x9E81EEC45F7329FDULL, 0x216C68657F15F204ULL, 0xC4A0C3D16BB9D917ULL, 0xD28F739DC6B830E5ULL, 
            0x853EA13842C354B5ULL, 0xCA15C665FCCD7DA9ULL, 0xBBA1472763C41B89ULL, 0x3F516C26A37A5A29ULL, 
            0xF96DDB31087DCFECULL, 0x04CC9528C12D6C04ULL, 0x97548C260C43A6EFULL, 0xF1ABB0ED95C1B0F8ULL, 
            0xAEBC79759AE104AAULL, 0x5D48094B3EDC9E83ULL, 0x4D18FA6F6D2D1600ULL, 0x5F4739C9FD084E98ULL, 
            0xC9B504E593C90AB6ULL, 0xF1B3B234597122A4ULL, 0xA2F4385157FD50B5ULL, 0x4CE1FEA9ABADFCF0ULL
        },
        {
            0xEB8C3836404D3F4EULL, 0x7C0E06D8341D82A0ULL, 0x76AFF52B8FF3ADC3ULL, 0x7A48DC7DAA96A580ULL, 
            0x3A59E1AF84256C05ULL, 0x5D709D2AE7834552ULL, 0x1F54C00B5B74B5C7ULL, 0x56DD963AC47F5E31ULL, 
            0x1A7FE5064701377BULL, 0xA75E4D0882AD0E55ULL, 0xBD1A153322C5F0A4ULL, 0xEA822C2BD6283B27ULL, 
            0x155FE42BC6B185B1ULL, 0xE3776DFEFA183ABCULL, 0xDBA16F36B767B1C6ULL, 0xF374855D89D92375ULL, 
            0x4600A043A9B6A208ULL, 0x0024F3136E5D1DDBULL, 0xB691F783B4E4FB34ULL, 0xB8BDA82A20277B8BULL, 
            0xF90730D6A2DC893FULL, 0xEDE4AB41DC4A9D54ULL, 0x099A0C5ECCF40932ULL, 0x1A42A7016429A850ULL, 
            0xB8BFE32834692312ULL, 0x975E1CA75FC159B6ULL, 0xB4DC6E3A3838DFBFULL, 0x05488DE584AFD120ULL, 
            0xD057E3405BCB7558ULL, 0xB96BB93626D55FE4ULL, 0x11B2C6AB41971085ULL, 0xBB67158BB6A02E5EULL
        },
        {
            0xA2675F37574226F5ULL, 0x0E8C3457C18871B9ULL, 0xFCAEFBE8DA38E052ULL, 0xEB245F65FDA3C43EULL, 
            0x6E63E17651F3DA04ULL, 0xBE41C7E3CE67BCFDULL, 0x32CA26ACA94F096FULL, 0xB886BD814DEDFCCEULL, 
            0xAAF8C53C862AF51EULL, 0xC4144F4D9478E086ULL, 0xB69DF9E61504807BULL, 0x511996C83773E339ULL, 
            0x9DDDFF0441E80DF9ULL, 0x1B8997CDA032A384ULL, 0xCFC304C2E0602823ULL, 0xDC15667C3CE1DA0AULL, 
            0xE916539E5BFC9720ULL, 0x22C534BBF6808F63ULL, 0x95EE20776927803AULL, 0x47EFDD673EC22A55ULL, 
            0x1C52E2EFBAF36B2EULL, 0xB40A0B6881DF7398ULL, 0x0F91BC3DB5C993F3ULL, 0xD1106B535739DD70ULL, 
            0xE0C85A970090B83CULL, 0x8599DE2F162283F2ULL, 0xB18122679166D814ULL, 0x5F57F02A4965E37AULL, 
            0x6192BFC7B7867645ULL, 0xF83B9D57B2092C4CULL, 0x1BEB25520B0A15F7ULL, 0x0068FDCA91036D1CULL
        },
        {
            0xF448F1062AA7EB33ULL, 0xE439F23EF8637DA1ULL, 0x76002D62AAC158E2ULL, 0x885D92D2C45CA4D9ULL, 
            0x4A2872D7297D760BULL, 0xE8C3FED62082D6EBULL, 0x24BF29D48FE61283ULL, 0xB2351419E7C62C9DULL, 
            0xBE362C37AFBBF060ULL, 0x22275CF2E21874FAULL, 0xD0CE2075033138EEULL, 0x51DE0F214ED37B57ULL, 
            0xCAC5A2D5FA0B7F0FULL, 0xACDA67F06047ADEFULL, 0x71D437F050E2F396ULL, 0x12951195F35AB8ABULL, 
            0x7051556CA61BBC23ULL, 0x3078A70E6161E506ULL, 0xC413666FDB9560DBULL, 0x1337308EA3AED8E0ULL, 
            0x9155A67C58C70633ULL, 0x4647CD5E07951CEDULL, 0x4B35867BAB280154ULL, 0xD596432F862AEB54ULL, 
            0xDFD8DCAADA82021EULL, 0x5D7E65613AF50721ULL, 0x6FFA4F1186317011ULL, 0x07B3D300D4343AAAULL, 
            0x0C4F10B36A4F903DULL, 0xA1F843898D3BECC7ULL, 0xF5B6E71873A3F978ULL, 0x93688724C2DA92EEULL
        },
        {
            0xE6060B8C25DA95CAULL, 0xC668B51897831FBDULL, 0xFF4699E3EB77AAE7ULL, 0xFF4D7ECBAFB5B4E9ULL, 
            0x61D822D5A4C8CA04ULL, 0x31D8754D5E547A07ULL, 0xFD94CA310481B5B5ULL, 0x04016F72E09E47A6ULL, 
            0x885D080308CE583BULL, 0x208F34A373FC34D1ULL, 0x42FF6839D60950F8ULL, 0x1C1D371C06158FE1ULL, 
            0x9263CFFDFE34AF28ULL, 0x20B2BA2939F19605ULL, 0x434CA078D110991FULL, 0x0FCCF23280CD8F04ULL, 
            0xA0802705873A16C9ULL, 0x7BD71EF8BA8D376AULL, 0x0B7C16C211B47C50ULL, 0xC7BC1CB2D06E79D2ULL, 
            0x89B1A129DF9851D5ULL, 0xB0A4C209523183DCULL, 0xBD803D8911D8BF6AULL, 0x53984A639B1528BEULL, 
            0x494070D125E57A39ULL, 0xCC7372F96561D8F9ULL, 0xAE6492576CD2E22AULL, 0x808AF02513B02A75ULL, 
            0xF572CE0C4BDF7D3FULL, 0x39A3E659D00E4CFFULL, 0x772590C21B6ECFDAULL, 0x7EF6B14E1E08E25BULL
        }
    },
    {
        {
            0x2B09F11087FAD79DULL, 0xE5D4C17AEB3EE32DULL, 0xD2E37C844298197BULL, 0x66BF3E24014A0728ULL, 
            0xD71767CD6355C3B8ULL, 0x28D47723C343CF06ULL, 0x4B679758E3F2F043ULL, 0x35547C8656DD23A8ULL, 
            0x9D02D3086A6C1C3CULL, 0x0B51EC7018AB671FULL, 0x07C75BAAECEC9B6AULL, 0x2AB071275DF90E95ULL, 
            0x0FF10536E82D6BA0ULL, 0x560738ABB4FC7FC1ULL, 0xECE532DFDF90BD5CULL, 0x8F260407DE5CB43AULL, 
            0x5936568944AB3A26ULL, 0x204DA5F6140C0D21ULL, 0x643E2A3B54031182ULL, 0x69D261F44FF21FAFULL, 
            0x8BCC06276D719B77ULL, 0x67C082A7B8532EF2ULL, 0x0FB937BB38915B50ULL, 0x9B2EAA08108371ADULL, 
            0x55DF8DCCF791B302ULL, 0x3E5FA2BC72B93708ULL, 0x319A5FED9E1CAD24ULL, 0x71375C947CE4F54CULL, 
            0x75F0EBD7480E7081ULL, 0x96E1F10862C1293FULL, 0xBA307C016A3A8FDBULL, 0x34571771817C73E2ULL
        },
        {
            0x37183A18E383E837ULL, 0xF61F2FEBC66B259BULL, 0x876E56763E5A6B5FULL, 0xB42D5735FCB36FF3ULL, 
            0x61265420AF833869ULL, 0x03464911C47DE7EBULL, 0xCFAD5D671F6D6813ULL, 0x0DF170C02ABAC7A4ULL, 
            0xB25AB2D25411CBE0ULL, 0xC7434E6A932078D6ULL, 0x7FE887E614B7E834ULL, 0x7C374E96D47065B0ULL, 
            0xE1A448171B1D4FF6ULL, 0x51325E0A900B5A59ULL, 0xFC556D71C03FAE82ULL, 0xB48D6F5B30403693ULL, 
            0x0E8F7AC1FD1D271DULL, 0xAC1D19F1E7C667DEULL, 0x1FC9C8D84D75FF31ULL, 0x46744D51F95F0599ULL, 
            0xBB990F25CA11F047ULL, 0x9BFE7DF3CF6CA4E3ULL, 0x08E24E3DA860ADF4ULL, 0x7AB5938390A30437ULL, 
            0x2F20035EC39E64E3ULL, 0xE2BDC61EC9386A45ULL, 0x651E5CCC96327753ULL, 0xE3295392302F36C7ULL, 
            0xC35032578AE6C7E1ULL, 0x5937FC4FAC1881A5ULL, 0xAF47AA7414CC3BF4ULL, 0x3160520555BB44E6ULL
        },
        {
            0x0670754132E0141DULL, 0x6E44AE16A1F8BC81ULL, 0x0196E686309CED5EULL, 0x9ECCA7380AB5F83CULL, 
            0xB46D5F4525B1C64DULL, 0xC19761F7FCFB736DULL, 0x31DD5E3B021C391AULL, 0xCADDEF61DAE1471EULL, 
            0x8CE2B86B70E2F9F8ULL, 0xEFF131999832F3E8ULL, 0xCB42E55ECB689967ULL, 0x3C88DA07E61C8EF6ULL, 
            0x8BB7B17809697EC7ULL, 0x290602567526B85AULL, 0xA61175B05FA25904ULL, 0xD3B84CA3521EE786ULL, 
            0x20522C43C9D047ACULL, 0x02621D6433BB38B1ULL, 0xAD5E733A49EA5E7DULL, 0x18C5E00332E658BAULL, 
            0xA9595D34C63D285BULL, 0x8BDAC458A4368647ULL, 0x2BE27C8EA6D689CAULL, 0xD436E9FC3F53501AULL, 
            0x00FA07112D950A23ULL, 0xD5C5CB425B76DDB3ULL, 0xEFDA168D2A825C5EULL, 0x6FF8725851990C88ULL, 
            0x1602FFC86645196EULL, 0xD235FA16FF75DBBAULL, 0x2B7C66FAEE0A3968ULL, 0x2B21823BD72CF531ULL
        },
        {
            0x62EAB01D365D6387ULL, 0x66D9AE34072DA52CULL, 0x117C254FA4A52A80ULL, 0xAC4B62E3DD3EC948ULL, 
            0x6F4925D3977C4AC7ULL, 0xFB23CAB8F4BAA692ULL, 0x0890F8D68F65538CULL, 0x7AFD45518BEABC49ULL, 
            0xC58DD75005BC04A6ULL, 0xAED49AC8C77ED6A5ULL, 0x3FEC00D155A1829BULL, 0xBB27E11FB36D8245ULL, 
            0x4ED792781BF89194ULL, 0x38A7AFBA7ACDDB85ULL, 0xA572CC7BD87421BDULL, 0x45BCAFCCDE10CE19ULL, 
            0xA13CF57B46CB7582ULL, 0x7F183F929C9EC22DULL, 0xB11D601EF529C073ULL, 0xEB817F7241107EE3ULL, 
            0xC6AFB82095390829ULL, 0x4DF12BA916B55DC1ULL, 0xA05C2B3B1800B53BULL, 0xD3191E25BA2FFDFCULL, 
            0x6C8081937A908C1CULL, 0x7ABF21FDA0C6D7C9ULL, 0x2705F2596B4C4CA8ULL, 0xF9D2398B20EABC6BULL, 
            0x972CFE2A21A5EC31ULL, 0x19FE536BEF890E8DULL, 0xBCC99A3175D6BBEBULL, 0xD541446EB6991C65ULL
        },
        {
            0x4C7208DB8C1991E5ULL, 0x85D542136874EBC8ULL, 0xFD4B28F95FF194BAULL, 0x8AA5274F73C0E144ULL, 
            0xD0F27564113F419AULL, 0x4D2A066EF4BFA5C0ULL, 0xECA26A96DF564336ULL, 0xA65F88095E05A579ULL, 
            0x88AB2AE3F89755BCULL, 0xB2DC708F561AD490ULL, 0x948875EA5D7D04D2ULL, 0x1FEFD199408C8354ULL, 
            0x97D3EE93D3ECDFE3ULL, 0x9E1BB8CA2F4B05D8ULL, 0x1C444FFB85ABDEE2ULL, 0xB46C4C93CEC6F4DFULL, 
            0x57EB49A9F0D59EAEULL, 0xD6E122C936C8CFEAULL, 0x97B894FA12352910ULL, 0x6FCD7D2F40AED647ULL, 
            0x88F9416F9437336EULL, 0x03DC41BBF4B14A6CULL, 0x4550D99FA31D9663ULL, 0xB5414A6FA92459A1ULL, 
            0x1FF32EC63EA329E6ULL, 0x84CC8143AEF3BDAEULL, 0xB9D44414509A5310ULL, 0x03C4B5D731E15624ULL, 
            0xB7580DA83750B042ULL, 0x0E679A2E5D6D3EA1ULL, 0x9DD5C023843183C8ULL, 0x13A7D1A78C4C14E8ULL
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
        }
    },
    {
        {
            0xDF6B9D560F34FC6FULL, 0xEFE6D83FE90DDEAFULL, 0x5E54CC723E457B45ULL, 0xC7887F9183B761A1ULL, 
            0x96AC8FB9983E828EULL, 0xFFF38B187AF5D397ULL, 0x8E28E698DF9AD05FULL, 0x70B706B37B91B646ULL, 
            0xEAB1A3436FAAAC87ULL, 0x842CDC5FBC576954ULL, 0xE98D2A96F2744763ULL, 0x4B3A086514E9E080ULL, 
            0xC474D8056069233BULL, 0x58A274A0448FFC6AULL, 0x716D8EC599C0A83EULL, 0x9B088D07E1E8093BULL, 
            0xFFC7EF2350689CDEULL, 0x18E34F531762291BULL, 0x5A68AD4709245E50ULL, 0x42159110271F28F2ULL, 
            0x58D5FC8B5EE8DC91ULL, 0xF13AFB8FDDBEE542ULL, 0x263D78D1D267AC38ULL, 0x92A710422DE471A2ULL, 
            0x992C4AB1B07B8814ULL, 0xB75B0380380B7715ULL, 0xC2EBCD79FDD78682ULL, 0x097522EF323B12AEULL, 
            0x766D7B6D326580BFULL, 0x89FD5E7DAD231C79ULL, 0x5A9A6F92DF6A9AEBULL, 0x1A2678EAA107F0E2ULL
        },
        {
            0xE190A87209648F5FULL, 0x00FA59EA1E664320ULL, 0xBE6F5F71313A2BA9ULL, 0x1DDF9226966BF673ULL, 
            0x4F586AE441F0CDF9ULL, 0xA9F3FDD81C500A9BULL, 0xBA686EB8EC354170ULL, 0xD17EB8107BFFF1CBULL, 
            0x9867676D7DC68051ULL, 0xC5DB562F7D89DD25ULL, 0xB2DDABC02551A689ULL, 0x0EDAD120E09581A5ULL, 
            0xB592D4D0AEF75B63ULL, 0x0EA5DD0084CB3688ULL, 0x859F6E08CF50223CULL, 0x73623BC3493B7DB2ULL, 
            0x2656780C4D5899EEULL, 0xEFA0C19AA94C4C56ULL, 0x8E4B1FA45D2DA2C0ULL, 0x3921AE710B309A59ULL, 
            0x583E9D420A4B1F4EULL, 0xEA3D48C67FAD4727ULL, 0xC76C69BEB57EA6C0ULL, 0x8B19A0E2E25B170CULL, 
            0x893B336877158137ULL, 0xEB5A8D3563549E78ULL, 0x9FD7FC778D51EF46ULL, 0x41076A68C5E91BB4ULL, 
            0x24C32105E617A6D4ULL, 0x0D85D224BC2D8832ULL, 0x3DDADF1A6F228FE4ULL, 0x6664D2A5F9CF0666ULL
        },
        {
            0xDE5F0189422DA3A8ULL, 0x6CCE3D357EFDF51DULL, 0x230914D598E56E6CULL, 0xB5F2B843827F8E54ULL, 
            0x712023AEFD4106A1ULL, 0x710380FA61752A76ULL, 0x57148EE98D07D796ULL, 0x7757468A8CE45032ULL, 
            0x8C8F0ABA6347DA94ULL, 0x98AE6872DB1D374BULL, 0x9F9D026EBEEBEC0EULL, 0x160C451E79847480ULL, 
            0x5709DA230829A8E2ULL, 0x087A11F724367567ULL, 0x445265D70BDA6B92ULL, 0xCE0990F32F50B4FAULL, 
            0xB3EE6A3AAD89574BULL, 0x45C21174E5528A1AULL, 0x1AA622E078DCE417ULL, 0x10BBB3FE8E51821DULL, 
            0xD423CAAA63EE1ADDULL, 0x7D1227F73759A651ULL, 0x9D2AD746EED60F8CULL, 0xD14FE560EF0E1B84ULL, 
            0xFA1501F685F06B57ULL, 0x57AFD0BCB6C52873ULL, 0xAC6DAE043FB9D48BULL, 0x2600AF248ACDF179ULL, 
            0xA42B0421B6CADB4BULL, 0xBEA1156346BFAA42ULL, 0x3DA3C3ACF4790498ULL, 0xA598ADEFD6C32982ULL
        },
        {
            0x2C160188B8D06F79ULL, 0x1618A55829AAA73CULL, 0xDB37B42BFE5E4B6CULL, 0x8F4F9E45C9DB2BD5ULL, 
            0x2B20490F29F2E739ULL, 0xAA157976BB21A9D9ULL, 0xC66C28ECE069E750ULL, 0x67BD2CD355845352ULL, 
            0x752AB53BC0CB88D5ULL, 0xB0E6FFEF491E700CULL, 0x59A73D1347257B4FULL, 0x0D050E436BA30858ULL, 
            0x832799C0C5E5FD13ULL, 0x0F0265431418F52EULL, 0xBC66B15F2FB67A8DULL, 0x70A43A08507C3BFEULL, 
            0x660A4877A12E065EULL, 0xB3AC7CC231C12AECULL, 0x64A6DCF49C687F6BULL, 0xC44E6B8D267727C1ULL, 
            0x5CD1F698C388E1ECULL, 0xF068922475712230ULL, 0xCE1CBA8506A63D5EULL, 0x01E39260E4EE9025ULL, 
            0x64E7756E4089E6F4ULL, 0x1416145DBD8F30CFULL, 0xC56CE545D9E19B29ULL, 0x4F02869C8424FC55ULL, 
            0xFFF0180B9702F29BULL, 0xCB1281076CAE99FFULL, 0xE847C45B53A579B1ULL, 0xF5E14160D74E46E4ULL
        },
        {
            0xD1CA2F06FF55B2DBULL, 0xD2847E5EFEEF8878ULL, 0x5ACE190AC75EB647ULL, 0x15602F87AD2C173BULL, 
            0x792DEBEDA21290BBULL, 0x271DF98FDD43A3F8ULL, 0xD282B6182420AE38ULL, 0xD3C0F605CB2C0B01ULL, 
            0x539175E5A469F546ULL, 0x7E01ADB6F725AC9CULL, 0x81FF98AA95364418ULL, 0x218CEBAD21AC307BULL, 
            0xF3BD71BB4D198309ULL, 0xCBFE9549DFF8D10CULL, 0xB13F6A0DA27A8330ULL, 0x9E7F501EF641A1A3ULL, 
            0xC0E4DA93C5BC0EB6ULL, 0x18350B2DA631BA80ULL, 0xA8C65DD33BD8583BULL, 0xB9FAC3BAE47D97A9ULL, 
            0x2212F064D7929547ULL, 0x7FC53441A05AF3AFULL, 0xE7454EF1ACE1A2F2ULL, 0xD7471156ED33629BULL, 
            0xF8F043DB051ABDA4ULL, 0x875121835ADA6A37ULL, 0x469E9E502998C5CAULL, 0x930D9C2417BB300DULL, 
            0x1A37359008CBEFAAULL, 0x9CE7D3BF2E624431ULL, 0x117F064827E90B6DULL, 0xD787CBCEE0E9E1F2ULL
        },
        {
            0xE173A9BCE915E2DFULL, 0xBCC4DF8A97AF2816ULL, 0xCB0FADF807318B0CULL, 0xBE310FC431C673B4ULL, 
            0xCBA726DFB2BBAD2FULL, 0x6DD1116C5B3CD746ULL, 0x9AC431F70B0AC781ULL, 0x5E6C75F736DD6F17ULL, 
            0xAF5144393A793944ULL, 0xFEE74A9EB0F80319ULL, 0x02721211256324C1ULL, 0x2AF0F4F435E0C172ULL, 
            0xE75DD5E506FE871CULL, 0xDF5686CFCCF773CFULL, 0xAD9A3E186E995166ULL, 0x499159FCA83C4CDEULL, 
            0x491977A0F241AE82ULL, 0xEABEB231D6D8AC14ULL, 0xE2D3A0C5BAB4C650ULL, 0x33CA7443F6A15739ULL, 
            0xC50C866DA0CF6768ULL, 0x94CC3712976DE1B6ULL, 0x0852154716001CC4ULL, 0x750D1E8522D94925ULL, 
            0x7EE282F01222CD89ULL, 0xE6ACF0C5CFC2914FULL, 0x6B69096C965C5DF1ULL, 0x6306ABC1F5BFB720ULL, 
            0x6ECCE8F3FAF360FCULL, 0x0731A97B96DB44BFULL, 0x26291ADA00BC2C46ULL, 0x5139B59ED001E4BBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseFConstants = {
    0x12F093F1DDCA6E34ULL,
    0x2330BB9EB8EBF023ULL,
    0x20EEF62D1B0F0490ULL,
    0x12F093F1DDCA6E34ULL,
    0x2330BB9EB8EBF023ULL,
    0x20EEF62D1B0F0490ULL,
    0xD8B9293BC1F4ED67ULL,
    0x8E5956BDAF91A6ACULL,
    0x4D,
    0xC0,
    0x96,
    0x4D,
    0x5D,
    0x40,
    0xC0,
    0x38
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseGSalts = {
    {
        {
            0xC088AFC4ED5ED499ULL, 0x797AC9620BE7A53BULL, 0xA3AB49CCD97679BBULL, 0xCEF2A2B0704D90AEULL, 
            0xCC45B0ABAE60B309ULL, 0x51B7BB3BF932E3FFULL, 0xA6249AA17122C644ULL, 0x10B352BADF421EEEULL, 
            0x3E0C10F631892E0EULL, 0x79ADCC665B11B348ULL, 0x52C8B6FC47BF19CCULL, 0xB2DC6A7BD2D7D320ULL, 
            0xF28721B32D7C0080ULL, 0xAEDB32E8672E95A0ULL, 0xF6271EE5D075017BULL, 0x6195B947FE5879D4ULL, 
            0xB5C185AF16B150B0ULL, 0xFADE8D3B844F6E9EULL, 0x7B510D886F29FB69ULL, 0xD5005D393A847E62ULL, 
            0x438B41A4B197DDDCULL, 0x7D0B458E761F010DULL, 0xCC5E2BB346FA9DA3ULL, 0x5F31C5BFEAF4FAA7ULL, 
            0x5292F3A520066C5DULL, 0xDFAF9001FF6542A6ULL, 0xA1EFD4330D8896A9ULL, 0xE64B333CC0197AB6ULL, 
            0xB866DF3FEFF643A4ULL, 0x5F2794B192759CB7ULL, 0xED8CC44AC4D95D44ULL, 0x2436207B6F8937BBULL
        },
        {
            0x7DDFD89A7723A080ULL, 0x41A199E678154060ULL, 0x56AE223072183C65ULL, 0x8BBABC4054E1915BULL, 
            0xED58C7189DF91DF4ULL, 0x9CDE3792D2DD7BE8ULL, 0x47E11DA1489ECD6CULL, 0x1CE50F9C7BA32254ULL, 
            0x126C07A80B57D197ULL, 0x2BD1896D5DE0534CULL, 0xDAF12D2F1FF235F8ULL, 0xC84B323CB740F44EULL, 
            0xE2E502E250D2AE68ULL, 0xA1D0B02FB3BE5C02ULL, 0x4F222D05BC4D5057ULL, 0x4EC7ABCF33391831ULL, 
            0x075C3CA2D67B106BULL, 0x66586E54F9586295ULL, 0x3599BC6F7224F15FULL, 0x78AE21F84334C30AULL, 
            0x994B34F60BC99124ULL, 0xCFCD6AEB10DFBDAAULL, 0xF232FBA26FBEF02CULL, 0x02D3F4603D9B69B8ULL, 
            0xB75E36968A5449A1ULL, 0x723F08B02E20BAA1ULL, 0x05C1720D1B9684DBULL, 0x8A62F1DFBD2D72A1ULL, 
            0xB47ACD33FDAEC359ULL, 0x64B4DDEA14F4E497ULL, 0x2C803A325541A752ULL, 0xEAFD7EBB4B1D4251ULL
        },
        {
            0xF9ED1CEBA761F57AULL, 0xEE89039CFCE8E284ULL, 0x8D10F2D31717955BULL, 0x4BF44E73C08302A2ULL, 
            0x73FA1502412E168EULL, 0x80BD1AD90CE1420DULL, 0x8DB3D94F2D218162ULL, 0x1542110B77B6EFCBULL, 
            0xC2BC77E6066E93E2ULL, 0xE774FC29E8926800ULL, 0xF3CC489B419F6B66ULL, 0xF3F29829C01D8F0BULL, 
            0x41E43EA8C00FEC24ULL, 0x7B02FB4DE1B2BD35ULL, 0x17EE932AC02621B1ULL, 0x59F8295FE3741027ULL, 
            0x111C986896FD1B4AULL, 0x0FC2AA986045E227ULL, 0xF5EDB972C88AD0BFULL, 0x75A08A46B51B5AA7ULL, 
            0xB7ECA39E7D8BDAB0ULL, 0x93E17E3DD7A4103FULL, 0x57B84464BEBE810AULL, 0x1A28A103053FDDACULL, 
            0x5CFC76C9B1AC7B51ULL, 0xAEE1D1080B3A987FULL, 0xFB985CC223FAA64FULL, 0x766ED8918543E5C5ULL, 
            0xABD309903BB31DCDULL, 0xF823A8E169B6C8DCULL, 0x841B106239B2BDBDULL, 0x5235B19298BA07ADULL
        },
        {
            0xD2B0FE48572AAB40ULL, 0x1A063A2B8F619A49ULL, 0xE13BD60D9D922980ULL, 0x4167D392744C40F3ULL, 
            0xDE1FD932022D666DULL, 0x5CA26D5366126486ULL, 0x9C865FF8098148CFULL, 0x71D579F816AA6D6BULL, 
            0xA10636A81AE7AC23ULL, 0x9E7D01633569216BULL, 0x2F7C321941B918C0ULL, 0x16DE23A40E2D55E7ULL, 
            0x370841E905E8B653ULL, 0xDBB3F40AF04B648EULL, 0x5ED6F5E79DA953F4ULL, 0x88C8F07D4D92C703ULL, 
            0xD900659E0951973DULL, 0xC4DF239F104EDFFFULL, 0x5B66AC75D5CB46CAULL, 0x473F12781909BB6FULL, 
            0x316D45424180CB34ULL, 0xC59CBCE2DABDA6B4ULL, 0x8E3A9DB2A37CB971ULL, 0xA1CF931B5FB7AE64ULL, 
            0x3904997F07586A3DULL, 0x3B584E561715A1F4ULL, 0x083BBF16B06FECCBULL, 0xF422F581EABCCD5BULL, 
            0xF5957DD318366C48ULL, 0x20F801584C604FAAULL, 0x8A699B7DC4474F96ULL, 0x21E06DBC4EB20362ULL
        },
        {
            0xFCEAE85C0E1658C8ULL, 0x0CD3E8BEDBAD0E75ULL, 0x69C91390FD66C93BULL, 0x928E768BA13A0462ULL, 
            0x81AF4FA3748C6324ULL, 0x9F8BBD32C0902323ULL, 0xD5AA91105B70810DULL, 0xAC0E087DE6DE853CULL, 
            0xD18977DD2185C366ULL, 0x061F77740503FE75ULL, 0xCB77262D18785672ULL, 0x7899C5FE544446C7ULL, 
            0xDF61BF0F89FFDA69ULL, 0xADCBA2B1823D495DULL, 0x8FE2270CD6ABC304ULL, 0x160609FEFCC492DBULL, 
            0xA7EA219344A75B23ULL, 0x6ADEBDB4B86110FEULL, 0x4C62382D0477AF58ULL, 0xA22917737177D322ULL, 
            0x22931C9870CB44A0ULL, 0xFA6079BE4FE91904ULL, 0x096CF0D567A40C37ULL, 0xC1DD987CD578C1C7ULL, 
            0xBAB2D096D9082E5EULL, 0x355165FD29959BE0ULL, 0xB7BB36A1598A8E88ULL, 0x7FF4889EF6C5E197ULL, 
            0x6E46BAFD8F2D2A0BULL, 0xFFDF8A8DB9C5201BULL, 0xB359B4EB9490DE87ULL, 0x194A4E37650E487DULL
        },
        {
            0x0B52F2D96E02B041ULL, 0x2F0688569A817916ULL, 0x84B45D3D3ADB44C8ULL, 0x0CD9E517D04B4181ULL, 
            0xD30AD1D34DEAC051ULL, 0x3100C3AEC65C980CULL, 0x99555FD4F79CE06FULL, 0x7977E055D029B1F4ULL, 
            0x1173B4DC1EE9634EULL, 0xDF8283C5B449C5FCULL, 0x0BCC4EB8334402CEULL, 0x5640071806209B26ULL, 
            0x3183038EC9C647C2ULL, 0x4D4DCBA07363ECC5ULL, 0x19A66AC5224B7ED8ULL, 0x83E3F55AD06E0FD8ULL, 
            0x257DFD37BA58069CULL, 0xBFBD1D64CBC19CA1ULL, 0xD4A9E285A47D4907ULL, 0xC42B9890205D42D0ULL, 
            0xC19782707BE4B6B5ULL, 0x147747060874FF92ULL, 0xC38C6ACFC2E9CB72ULL, 0xA86C16C83373B3B4ULL, 
            0x237785D8CCF3AF46ULL, 0xD1D84C28E4622B9AULL, 0x4A99C2FC444F48C8ULL, 0xA2A41F11C7A39027ULL, 
            0xDB47BC6E33D6D235ULL, 0xFB8F43771B09553EULL, 0x2A9A382DE208CE38ULL, 0x72B233139AC921C7ULL
        }
    },
    {
        {
            0x291946B46AFF9254ULL, 0xB965C883EBB823F3ULL, 0x078A48EC88774476ULL, 0x354EB39F1908477EULL, 
            0x7547D9E1DDCED8F2ULL, 0xC907A26937612F4CULL, 0x6478625023D64509ULL, 0x61AA91A4637B8458ULL, 
            0x6E2A43521D1F8F09ULL, 0xE204759D163223F1ULL, 0xF410D86836304E98ULL, 0x17AEFFAEDE826AAAULL, 
            0x1EDD08E0C6797ABAULL, 0x540350CC9F573CAEULL, 0x0DED05DB63B4E0ABULL, 0x2048EB63C6433E30ULL, 
            0x4053E6B31C5F65D4ULL, 0x9FA9C121D13FD4EBULL, 0x89E83FBCE7B360CDULL, 0x5FB6A99880AC8FABULL, 
            0x2554D79EC2AA88ACULL, 0xC54524A8564A59FFULL, 0xE2FA3A496ED71249ULL, 0x932A33CA21425766ULL, 
            0xF33676EBB9955D6BULL, 0xF969E2A50EFA792EULL, 0xE6364B36DB118AC9ULL, 0x441C05992D117C47ULL, 
            0x98AFE775A4391C60ULL, 0xF584EF44A0B00E41ULL, 0xDEDE7D5CC93ED855ULL, 0xA2C63EE81A8C1F56ULL
        },
        {
            0xFC607B1C926694B7ULL, 0x1F78C48BEDA5983AULL, 0xF5F7FCAAA6B3EC04ULL, 0x70AF8491A1D05CA7ULL, 
            0x6F5138DF105AF4B7ULL, 0x5E0E25E64F9D6819ULL, 0xB717E688C3386CC6ULL, 0xA01E5E593D4B7AEAULL, 
            0x8C5A5A253477694DULL, 0x1CC16F10A03791B2ULL, 0x92E1BF9D8379FDC1ULL, 0xEDF92C1D66E11460ULL, 
            0x0736E804829A0078ULL, 0xCC30AB2C3CC08914ULL, 0x2B09C805EA0D1C69ULL, 0x0C3077FED56540C7ULL, 
            0x4DE34773A1901821ULL, 0x8598B70A8B72AA8AULL, 0x71F3DAC8D26C8AF6ULL, 0x1F33C1DB6BD318A6ULL, 
            0x4DC636D1B1FDD550ULL, 0x93AAAC2EC13B7FF4ULL, 0xFC26C93B5AAA0308ULL, 0xA219324F0BA34C5BULL, 
            0xA024B1A6F01BA8ADULL, 0xE13BFF5001A81CFFULL, 0xE737DB7060EDA29CULL, 0x23132BD2ED316E5FULL, 
            0xB8DED93E14FFF1AFULL, 0x51F7701C0ED84782ULL, 0xB2D344F2E92347ADULL, 0x1E83C3DC74E873A7ULL
        },
        {
            0x95F580614283B977ULL, 0xC4BACF6FAA356614ULL, 0xFD9554EE8B0534F2ULL, 0x5661DED7DC07F0DBULL, 
            0xBF6BCDCC2649FB73ULL, 0x7FA1393AE9456F60ULL, 0xEC50F3A5751697D9ULL, 0x43CD381885807825ULL, 
            0x42DD0C283DF5554FULL, 0x0B129A29735F9A4EULL, 0x6C7AFFF0E20594A6ULL, 0x7AE85A01D84284A7ULL, 
            0xDFA53899FE0A6C4CULL, 0x60534AC4EEEA48ADULL, 0x48A9B88F347DD1AAULL, 0x23BCF16BC2B4A8E1ULL, 
            0x01829D16830B0EDEULL, 0x89123EB229072BA5ULL, 0x2AA22B03591359DCULL, 0x43A6F3E3EFAF5862ULL, 
            0x0C179E35E12807FBULL, 0xC23D85722D15AD46ULL, 0x692E29401B5D28ADULL, 0xA8A529CF8C7FC44CULL, 
            0x8DBC1187037E24CBULL, 0xE8372A669904DF7AULL, 0x5699BFFAC20534C0ULL, 0x82CA12E26B3108C5ULL, 
            0x36574EDA03DBFC01ULL, 0x0A00FECF3AB6402AULL, 0xA84D84F8C57E4105ULL, 0xB444EB807018808FULL
        },
        {
            0x277F3E6A442F9E41ULL, 0xB1EF786216112AE5ULL, 0x3E10A35BE73CC57EULL, 0x643FD21B7A677F16ULL, 
            0x7BAB9736F96987D3ULL, 0x7FBAA4CCEB0EDB7CULL, 0x96C8E11A3AB4C1CDULL, 0x358AA0AE976975A2ULL, 
            0xF82B2092B9B45CF2ULL, 0xDE9E6B95387EE92AULL, 0x5561915C8FAB8FCDULL, 0xACE81F662A2506CDULL, 
            0xB597F2B5B43FBC7EULL, 0x56FFD264EA7D74DAULL, 0xA9D8922094A1FE65ULL, 0xBB47E8FB386251D6ULL, 
            0xB94B896786CEE213ULL, 0x4DC9A5578811A963ULL, 0x98A9A47A7D234494ULL, 0x596D15B7F6C9A6E0ULL, 
            0x0FE4E04419C37D41ULL, 0xE27AFD9E0BC2FD16ULL, 0x524D7FCA20FBEF3CULL, 0xFA8DCC1E9D52FEFEULL, 
            0xF7A179F17BD7B0A3ULL, 0xF44EAE18DAC1547EULL, 0x193BC2FCF609A5AAULL, 0x19528D229C759E24ULL, 
            0x7E112AB1C3FBA01DULL, 0x8D2FBB81B433FEDEULL, 0x067F0DF24D02696DULL, 0x9FC849CBC765C3CDULL
        },
        {
            0xBB32BE9CE883F09CULL, 0xAA5A0B91BA30B9C5ULL, 0xEDEBC3E5397206B4ULL, 0x99A2183CE9E646D6ULL, 
            0xD035C088E683540CULL, 0x98688BC801BB5677ULL, 0x3B6249767BCB4247ULL, 0x3D9DDCB1A68937D1ULL, 
            0xF2B8380AE49A37C7ULL, 0x1849BB0920052EFEULL, 0xBD7B9161C98DCC07ULL, 0x3437F73D02F653AEULL, 
            0xC7D175B695381681ULL, 0xBF201127A01CAB70ULL, 0xFDA8DFCCB7BF81DAULL, 0x499137D9BFFF9D8AULL, 
            0x4246B79D753FB950ULL, 0x698EA18899744342ULL, 0x6DB9CF85BD7ABD58ULL, 0x09FD6B93997281E3ULL, 
            0xEC834A3F8A117F1FULL, 0xEEA1C0613046C70EULL, 0xE563C85391581DCBULL, 0xEAE1B6002164BA25ULL, 
            0xB16BC67FEFE9C4FFULL, 0x62CD0AC6BAA8C7FBULL, 0xFEDBC4453904042DULL, 0x41CD675BC393CD4DULL, 
            0xEB6448915114F41EULL, 0x1EDB69778079B1ECULL, 0xA405AE2DAAE9BAB2ULL, 0xF8BC7070A62B5B1EULL
        },
        {
            0x2C00436F9C5C65F6ULL, 0xDD950847842C15BCULL, 0x3838A308EE9EEB26ULL, 0x699D1C8C1A6F00ABULL, 
            0x1E4BFFB81975EB4DULL, 0xA230B5D4CADE2B26ULL, 0x5E8413BFF294B6FEULL, 0x791970998310D94CULL, 
            0x0E9F6CC323B0E9ABULL, 0x312CB7DA9703F493ULL, 0xA88058E18B16D539ULL, 0x8792EEFC42432EC8ULL, 
            0x032D633E60535C8CULL, 0x36B38BF48C3198C0ULL, 0xA1EF243D015E6303ULL, 0x80A49913D6562E66ULL, 
            0x805DE9AC2BF70F71ULL, 0x256D9F82E85AA470ULL, 0xB213F7ADC4EC6B88ULL, 0xD312D906F65EDD85ULL, 
            0x7A7FB537BEB476C2ULL, 0x9F17C7F102F97255ULL, 0x3FF38BBC4AF196DDULL, 0x65F906C8370AE0AEULL, 
            0x01FBB5C2159B7C27ULL, 0xA34C4F852C6C0754ULL, 0x7A4882459FEBF26BULL, 0xDADAEC804FC40877ULL, 
            0xABFFCE08CEE7E4DBULL, 0xFD0AC6114C199587ULL, 0xF5CF28F7D9FD128EULL, 0x42E54F4A46C84764ULL
        }
    },
    {
        {
            0x4135F305BF924988ULL, 0x62FFECD641EE36A6ULL, 0xB1C1EB24F0DE6417ULL, 0x9DCFC85057BB5AB8ULL, 
            0x11CA40D90E558D2FULL, 0x6FC0EB6D1F82DD22ULL, 0x1B29C861AD5ACCDCULL, 0x8210DE7A37329F6CULL, 
            0xDE4E3AC9BE30506FULL, 0x45415FBBBE5A62EBULL, 0x8318432D0F3511CBULL, 0xFBBCFDFB392FABE0ULL, 
            0x8F68853C13B58857ULL, 0xAF6BCA97BF576B14ULL, 0x67F7E26CC48572FDULL, 0xB9038D72D97211D3ULL, 
            0x41F222A3A945B472ULL, 0xA3D88CE562E4D410ULL, 0x8F6CE7ED1CDE3ABEULL, 0x0ABF0339168336ADULL, 
            0xD37ACF6F29938322ULL, 0x98AE81406ED1FB12ULL, 0xC490E7521F6D9723ULL, 0x105C4A3862D341EFULL, 
            0xC8059FCF1D207740ULL, 0xE951D6031735C13FULL, 0xAC8AE253E8E6A3BAULL, 0x6E0FE005A60571A9ULL, 
            0xD45D12C49D81943FULL, 0xE58C4F6D5F560A26ULL, 0xEFC563F5BBD8C692ULL, 0xCF8109111EEA131DULL
        },
        {
            0x677D4EF943462D50ULL, 0xF0E2C28DBF0C255BULL, 0x3F49F1741070AE8DULL, 0x0C8EEE2C2B96821FULL, 
            0x898E1E91505C22A0ULL, 0x85752092546CD89EULL, 0xA8DFA4720A558A39ULL, 0xB644F8D58486CD42ULL, 
            0x526DE7BD92077342ULL, 0x745DBBCCDE813B6DULL, 0x10C993B3ACA2E2CBULL, 0xEB82E54C8D86DA85ULL, 
            0x479EFB53446568EBULL, 0xDDB173FCB4BE7522ULL, 0x7DD57167D47C1473ULL, 0x69ADEF55863B1634ULL, 
            0x45269BB2D626FFF5ULL, 0x2996D7812F9A9FF0ULL, 0xF59C1701958FA989ULL, 0x21E5BEFAF449DEBEULL, 
            0x5F9EA65B66A28E81ULL, 0xE5ABD3DAFEFD6B0DULL, 0x2D5A34920AD37BDAULL, 0x879E869105C292BCULL, 
            0x4C56C5D6A48EEED5ULL, 0xCE1F0C955EDFC8FDULL, 0x330E90C8FA309D90ULL, 0xA1A6BEA8555F6056ULL, 
            0x6F62022FED553029ULL, 0xE41D58FC2BC62B81ULL, 0xEE2C97D3667DE8A0ULL, 0x9F29F8DB564D66B1ULL
        },
        {
            0x1A433D7F0EDFB541ULL, 0xECBD89AB09454299ULL, 0x0847C2A07F4B02C1ULL, 0xC8295AFED0DC2B17ULL, 
            0xE5F15B63C00AF613ULL, 0xA8BCD4579BDF7101ULL, 0x9EE0A01A6193C493ULL, 0xB8C9E0B9FD0322B8ULL, 
            0xA79CB65515BABEA1ULL, 0x97B828277DEDFE82ULL, 0x5F18B848E364C6BEULL, 0x1D415FB09AE3B5C6ULL, 
            0x2037C44626AFDA73ULL, 0x3D4BF3BEA8471532ULL, 0x63D64BAD2939D498ULL, 0xCF61C492096D014CULL, 
            0xAE8EA941B0C086E6ULL, 0x3F25CC6DC3CFB24EULL, 0x684A3E8AAA156FBEULL, 0x34874559B2EBCE90ULL, 
            0x0624F719E6E7D501ULL, 0xAEA6EADC179DB847ULL, 0xE10F4DC4D6CF58A9ULL, 0x71DB63BBC4554165ULL, 
            0x136CBA583E8E8716ULL, 0x0599DF43BB23B44CULL, 0x0AEE034376658EDCULL, 0x48F5FF4018F1B560ULL, 
            0xC3F462717659DADDULL, 0x6A1043D66A7F1582ULL, 0x2728CF0E8503F580ULL, 0x70B792AEF8306C93ULL
        },
        {
            0xB8621CAE69F1D3DCULL, 0x4F731463408C729AULL, 0xDBBEA569DA2A4346ULL, 0x84DF140D4E2C04EEULL, 
            0x04DEF46DC4867B5FULL, 0x20384E0B1AEA8C21ULL, 0x864F9D5E9C825C57ULL, 0x2D2A6F30D64AFF86ULL, 
            0x26263C07475169F6ULL, 0x0BCB1F02E55A6CACULL, 0xB2DA111AE3973A47ULL, 0x2391DE0112705C66ULL, 
            0xD4059245666BB7B1ULL, 0xD057B7B0BDD536D9ULL, 0x6261D9CA603E01BFULL, 0xACD6B360229D5D89ULL, 
            0xD51067097C2CD631ULL, 0xB7D2AD0B4A286BCAULL, 0x598F0294D96E55C5ULL, 0xEE2E7E2B73CC748AULL, 
            0x8B5A8FE30D8A3554ULL, 0x875E9A1664BF1466ULL, 0x5C1658670632377AULL, 0x6DE3CA47C82032ACULL, 
            0x9039B13989BA9C09ULL, 0xD69ED89776739EABULL, 0xD6BC1DDBF7D5F19FULL, 0x8B8EC264D23BD141ULL, 
            0x6B2FF4C650A1CECFULL, 0x681C02ED54987B9FULL, 0xB19AE408D93BECCBULL, 0xDEF68B395C5DDB17ULL
        },
        {
            0xF00B4E339FA44A78ULL, 0x9CC2C536ED1DBEBEULL, 0x2C6E0703E4C2244AULL, 0xEA4D07B633438A97ULL, 
            0x18F5CDF26EBE6D36ULL, 0xC64EF5E878824910ULL, 0x78CDBD58DE08CD1AULL, 0x7A7E742F742E18C1ULL, 
            0xF2605B6D3B1D9DE0ULL, 0x63B9F91CC8CEE1BFULL, 0x57A29BCC6ECF7AF5ULL, 0x8DC0C3F8782D141FULL, 
            0xDB37F82B1F3F150FULL, 0xD2DBBD67E57006FEULL, 0xC8B860487998134DULL, 0xCCAB8395A7BDE3E0ULL, 
            0x15881222384A1839ULL, 0x86327DCB5979DAB1ULL, 0x763CE3C9A28F6525ULL, 0x33FBA15907440B24ULL, 
            0x6016C88C76F7C97BULL, 0xDB3B341E379FA150ULL, 0x470D48DC7B39F84EULL, 0x4956345846FE5DBCULL, 
            0xD1B20A4C70428DDCULL, 0x13B23EA50D2B4526ULL, 0x4F52B33AE79E5C82ULL, 0xB059A08B6D46D6B9ULL, 
            0x66DFA5B005C4A765ULL, 0x682419026D2EDE55ULL, 0x40E021A72B219421ULL, 0xFACD1707EB19BB18ULL
        },
        {
            0xA28F0E2DEE892A15ULL, 0x8724A1065D5EDC84ULL, 0xA894EB17BB6D1A98ULL, 0x6A6881B13C0070B0ULL, 
            0xF265B03515FC3CDCULL, 0xBB34B3AC902917DBULL, 0xAA12A7D668B363ABULL, 0x4D996975F069C69EULL, 
            0x1D6EE3885ED65763ULL, 0xABC93617AB1FD843ULL, 0x4703CEB4CF685D50ULL, 0xB73CC48E75A8B0A8ULL, 
            0xA8F6F7102A2C2F00ULL, 0x1DCC52343828B3D2ULL, 0x738D5BE84C230612ULL, 0x74693BF0D597D843ULL, 
            0xFB90946DA82029BAULL, 0xDAE2C998682ED5ADULL, 0x0BB397ECF703ED0CULL, 0xF146608E225A5A3BULL, 
            0x0CF45008FEF996AEULL, 0xDE9953CAFEDEA47EULL, 0xD5EF643E817377E8ULL, 0x641A8CF986A3A712ULL, 
            0xEDE6984D8AEA483FULL, 0x8C82B1DC15572F1BULL, 0xFB3A0CD10B36C6FBULL, 0x9164C6BDAAB310A5ULL, 
            0xF058CCBA593776B3ULL, 0x9C3CF070037759D1ULL, 0x19C3C551327894FCULL, 0x6B3F9ECD894CCB93ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseGConstants = {
    0xC2700F8DE17E1996ULL,
    0x1F36821318EACB0BULL,
    0x1F47463D0BC81364ULL,
    0xC2700F8DE17E1996ULL,
    0x1F36821318EACB0BULL,
    0x1F47463D0BC81364ULL,
    0x31D41984DE2B889FULL,
    0x3C34EC5981FF2ECEULL,
    0xB6,
    0xA7,
    0x0F,
    0xF9,
    0x89,
    0x8D,
    0x79,
    0x94
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseHSalts = {
    {
        {
            0x71A7A5C3CA68643FULL, 0x9B24F5558E60D21EULL, 0x49F93F34E3032CA7ULL, 0xB74AECAD9B5C2306ULL, 
            0x109A1BE710C40193ULL, 0x99898FDF249EF568ULL, 0x636CE3E90B841119ULL, 0x907D1E34E5BA576CULL, 
            0x0481BC3153DAE2C2ULL, 0x8BB22EF8341BD4AAULL, 0x8E5CEBBCF8B912D3ULL, 0xF12823827A4307DAULL, 
            0xC6DAB3CBC7AEB408ULL, 0x02B65E7ED63C5428ULL, 0x14FDDEBFE9F74216ULL, 0xF19CADCE8EBC9EE9ULL, 
            0x4CB95A3092A2722FULL, 0x90D319EA6AB24420ULL, 0x8BD21AB845379793ULL, 0xF2649C8E61E9B0AAULL, 
            0x2FD6A774E2CCF154ULL, 0xB4875C3975D39FFDULL, 0x4ACB901C8207C9C8ULL, 0x03E1C3B2CA508BF8ULL, 
            0x032DEC95A96F7007ULL, 0xB4410DC5DCD23A70ULL, 0xA16609A093FA19B9ULL, 0x8A018EC7420F69EAULL, 
            0x481E01290D7649A2ULL, 0xEE339ECB26DE090FULL, 0xED82CC00CD3B6537ULL, 0x3C1EB3B5422F04DDULL
        },
        {
            0xF377F337BC359152ULL, 0x22F6DCB127418E10ULL, 0xA2D86DD037D454ECULL, 0x5991328051F8DB77ULL, 
            0x92A018DE3B3C9FF6ULL, 0xE0112AA5D5C037B0ULL, 0x388E413C6DF689B6ULL, 0x9AC55DE132986284ULL, 
            0x807A343AF4CA40C2ULL, 0xE0C0B04B59300218ULL, 0x62486D0E5782CE79ULL, 0xFE68A6A9289CAC59ULL, 
            0x6C3DCD5FF39F09ADULL, 0xD7E7C09EA526EEA0ULL, 0x0422857B402198D6ULL, 0xEAC8B835ABA65EC4ULL, 
            0x16C4F7DA6F7D18FAULL, 0xBD74096869FE16F7ULL, 0x25A040CF68DDC86AULL, 0x4D78878E1233AEF3ULL, 
            0xCA0FE12D2A0728A8ULL, 0x9921616FD4B2D97BULL, 0xD08CFD4F480082EDULL, 0x7DC77AB645461E2BULL, 
            0x5DB3D2CDEC4C168CULL, 0x23FD28A1EA24B7E5ULL, 0x3B2F89AB77EBD3E8ULL, 0xAF712E221E4A311BULL, 
            0x5FC5E73095B871C9ULL, 0xCEB7AF88EF53A932ULL, 0x31AC1941B9C9B6B3ULL, 0x9F39169EE8D15678ULL
        },
        {
            0x4B5B8BFEA7607DB8ULL, 0x8C682A64BF95943CULL, 0xA0DADCDE924FDEF9ULL, 0x1F297D052460629EULL, 
            0x606247422CBA8789ULL, 0x4AE613E73B1D9E96ULL, 0x2A750A527B7DFA5FULL, 0x7956EBD5E1F27FB2ULL, 
            0x6717B3878AC49732ULL, 0x295B6DDCD6F6886EULL, 0x70B4039F223AEDCCULL, 0x393B42112D64E523ULL, 
            0xB04AC151A6DEB5ADULL, 0xEFB1E49AF57886CBULL, 0x77E19BD09ECC0BA8ULL, 0x103DCF40AF54B335ULL, 
            0x1E3C63337173FF85ULL, 0x3F06BA2664540CC0ULL, 0x7A9C1B7DBD58653EULL, 0x1E3EBD03E9567BF6ULL, 
            0x60F98C57687E22F5ULL, 0xFECE5CBC0807CD15ULL, 0x358CA74605DF7921ULL, 0x49D9CA3C81CA7EAFULL, 
            0x665D89E4A52776F9ULL, 0x5C1BBD30E190AF57ULL, 0xF9A26E2B3EAD6E0AULL, 0x77BE8854184D301AULL, 
            0xA6904048A76852F8ULL, 0xEB7A77739EEC9D7AULL, 0xAB1B30E0A650127BULL, 0xA8D6B92834C13480ULL
        },
        {
            0xDCB742B7079DCEBBULL, 0xB241AC4A99DADA63ULL, 0xAE64EDD1E17F3002ULL, 0xBFE17913630772A8ULL, 
            0xEB6EE3488737CAA9ULL, 0x2684E690B26BFA97ULL, 0x5C100201FA01AF62ULL, 0x1DEC14E73CC18D09ULL, 
            0x8CA3A1B3BD44706AULL, 0x7CD02D0B3885B68EULL, 0x3599BA363F112FE7ULL, 0xEBAB7FA769C7BFB2ULL, 
            0xD2D8016E6A49B61DULL, 0x77D5382644851C0EULL, 0xA762E70A02548940ULL, 0x3B7D9F21D96553C6ULL, 
            0x4D670FA4820FC8D2ULL, 0x325D73CF9E5F463CULL, 0x0B0263BC1E3854BFULL, 0xAAD538BDEE5B5F74ULL, 
            0x66BA42347EEF933BULL, 0x9A44314103A6D9F9ULL, 0x92582679FE86B161ULL, 0xD2A43000965FE31EULL, 
            0x71550A27B77B5910ULL, 0x8FE5766C5FBCD7F1ULL, 0x40836E8DA6B8CD7AULL, 0xA1E82BB33A53AD72ULL, 
            0x34B1CCA9FABA133DULL, 0x37EFE4AE862519FFULL, 0x0584F3C87CBD5169ULL, 0x83016EBE271FE195ULL
        },
        {
            0xB4EAE361DDA879EFULL, 0x746A54AFCCC36353ULL, 0x3890DA1971F41A36ULL, 0x611321C1F8C838D0ULL, 
            0xE2D27C5544C8AAA5ULL, 0x408C5BB838DDB5FEULL, 0xDF8193E70B72FFD2ULL, 0x47730D8C14CFDD56ULL, 
            0x67E8F2859DC54ECAULL, 0xFEE417978080C0C1ULL, 0x45A9322D402E15B7ULL, 0xCCCD25C4B8246D40ULL, 
            0xA7F323FD3E9D170CULL, 0x2AEB82D70055D079ULL, 0xDD8B18126E6BA472ULL, 0x5F8A633100E8D9E1ULL, 
            0xAF9665BD3371C24BULL, 0x05E53DC97F0C6037ULL, 0x0D7257A26BABC5F2ULL, 0x92B95FA03BE4C574ULL, 
            0x43F8E26A3A73DF0EULL, 0xA5A7563F9BC0A6BFULL, 0xAC793CB1A2907261ULL, 0x682FA9B6783365BCULL, 
            0xCCEDB0EDACF7CCBBULL, 0xC93F882813BB928FULL, 0xDF46C711823CBB8CULL, 0xD01D6E6004F4DBDBULL, 
            0xBB59D21FF04FF843ULL, 0x0EB5EE25E79A3855ULL, 0x5F251D3BD48F3467ULL, 0x7B065C95B7B026A1ULL
        },
        {
            0x3C22D597924CC827ULL, 0xE9772CA2A60E4F29ULL, 0xB827E19EBEE53EBCULL, 0x9B3C2513ABC86358ULL, 
            0x11E1A5020AD0896EULL, 0xA2E18963010543B3ULL, 0x7C83226E04377AEEULL, 0x823C5768B7D4CA59ULL, 
            0x04F21E21CC34F43BULL, 0x31AFA48A8C63E425ULL, 0x7BF99BD1ADEEC77FULL, 0x32AE732F377710C3ULL, 
            0x25A682A51F47030EULL, 0x4BC5F72B91A50941ULL, 0x3167D04EE074FE41ULL, 0xE0890FBDD38D42CEULL, 
            0xAF11C33A026B8C53ULL, 0xD8C47BE14C967A7EULL, 0x468F8A2DB5E9E62AULL, 0xD2242179AAF857E8ULL, 
            0x83212E6176FA26D8ULL, 0x4AB80C66154BC632ULL, 0x8256C0007F0428B7ULL, 0xA68D283450022319ULL, 
            0x437A900647354411ULL, 0xDF47561B8303F9BFULL, 0x2FBB1D697BCBD64BULL, 0x71CE481A0EA63F1EULL, 
            0x39149E81B29EDBB1ULL, 0xE4F65857C6001606ULL, 0xE5E57D193A5542B3ULL, 0x99A160E417185247ULL
        }
    },
    {
        {
            0xF7B584B9FEF1F7ECULL, 0x325E22CEFC837872ULL, 0x7A489F946A57E835ULL, 0x62A9B786C296103CULL, 
            0x42F164AF448DB165ULL, 0x0F53C481808CD459ULL, 0xBFA601520386BA71ULL, 0xAEFC1110C672010CULL, 
            0xECE5861F2A9B4B44ULL, 0x57965328C8F76228ULL, 0x9DCA6955D723DB94ULL, 0x82D34E193A927728ULL, 
            0x76F0842DA8A8561DULL, 0x87DFEB29F8A7F849ULL, 0x879396723A3EB8ECULL, 0x69B6F933A2A278EFULL, 
            0x6DA033815087D877ULL, 0x584DE06CAC5FD026ULL, 0xC5E2EE31CB603476ULL, 0x4F94F65BD8FDF0A1ULL, 
            0x660E7E5EC98D418FULL, 0x124798B78431555FULL, 0xEBFE0414D35A7AB7ULL, 0xA7353B068E58D427ULL, 
            0xCED74BA4118325FBULL, 0xB4226459473E781AULL, 0x5E8008F0ACE30147ULL, 0xB20964DE0C89CF17ULL, 
            0x4E145A273DC68886ULL, 0xD393FD930D80D62EULL, 0xE471024EE3EA9EC0ULL, 0x6E9787B77F50620FULL
        },
        {
            0xA610351248C22A87ULL, 0x2B06C363CA2F734DULL, 0x13E6B5B276E76061ULL, 0x304D3400EB551DF9ULL, 
            0x090B26959199954CULL, 0xEB37D8DFDA42562CULL, 0xF11840BC1C04717EULL, 0x99AACD9DF6CE6437ULL, 
            0x6776E0F8EADA42BEULL, 0xC233ABB54177F23CULL, 0x2C94722416D567B8ULL, 0x8E3D13364C56C7B8ULL, 
            0x5D8E7EC638E226A5ULL, 0xC1435ABB22EABD1BULL, 0xE9060C6C0E6F7862ULL, 0x0B19E32352058E08ULL, 
            0x9DE26A0A7B03C0FDULL, 0x0FAD8DB02429D040ULL, 0xFE99A7D49F596BB5ULL, 0xF1FF839F85AEA001ULL, 
            0x9A4E8092F7521B1BULL, 0x8B5EA12D044A120EULL, 0xAC8F07CD28E75C56ULL, 0x336C34B55405D775ULL, 
            0xE732A0B5ECAC9852ULL, 0x36DEB1FCEFDD9B8DULL, 0x63929A7B0A1F8DC3ULL, 0x0064879248CCF145ULL, 
            0xCEDB531CFE6FFAC2ULL, 0x89BBC052B973A32AULL, 0xB0990A602C1A3AC0ULL, 0xF6021B9B8DFE25D8ULL
        },
        {
            0xB335240B37BF33C6ULL, 0xA02F83A9BEC821B2ULL, 0xE36BB98F8CE6B1D0ULL, 0x71C3C6446DF23F16ULL, 
            0x1437AD8001D721A5ULL, 0x37360B02BE045FE4ULL, 0xD1F8123F02C06539ULL, 0x9823940F40DD8F51ULL, 
            0x6B183BA43B774832ULL, 0x01B55942068057B8ULL, 0x33CDE9E55AF1323DULL, 0x288D47456980E420ULL, 
            0xD489E30B700666F1ULL, 0x0F3FC525FCAF4415ULL, 0x8ACCC9ED34966619ULL, 0xFAF841005D12AC2FULL, 
            0xA47B0B0C137C5B90ULL, 0xA70438FBCCED2358ULL, 0x44BD29E02DB4026AULL, 0xF83705A983E3E1FDULL, 
            0xC5FC70EAD159CCF8ULL, 0x846F36E2A3973713ULL, 0xCA8D62F278A18EB4ULL, 0x58F706777BAEEF91ULL, 
            0x642EB733B33F9CBBULL, 0x7D5AED1868DF063DULL, 0xD374BD052BA0EDB7ULL, 0x3D83EBCB64678025ULL, 
            0x5877BA2AFACB5A2AULL, 0xD813FC644CF056BDULL, 0xDD6D2E547ED03E9CULL, 0xFAE36757B4F29D8DULL
        },
        {
            0x8D70598380FD2402ULL, 0x3F8B7277E305ED9DULL, 0xA0915BD5DE4445D8ULL, 0xF7DC1EB38233B5B6ULL, 
            0xC30986F5B2EB6491ULL, 0xBCEF05293E1DB5F2ULL, 0x024BF2698B4FC4E1ULL, 0xC6F572682F21A4F4ULL, 
            0xF90A5CCB6840074DULL, 0x8FEB200748969819ULL, 0x2A5A55F3359AC469ULL, 0xB625F33A77D27E8BULL, 
            0x39D2F06AAE58223EULL, 0x49BDA3094494A7E4ULL, 0x45468D717E96FE44ULL, 0xB20462518737E21BULL, 
            0xFB2058BD85AF0389ULL, 0xCEA37921D4AC53E5ULL, 0x6A5EBF7D900F49F7ULL, 0x4A1D7C0578AE6B9BULL, 
            0x8829C09B2524FEA1ULL, 0x690D6658AC215422ULL, 0x791499C3F8311BF4ULL, 0xE2EF647D80AB7316ULL, 
            0x8ACDDA5CA1378C9CULL, 0xE334A2843E483673ULL, 0xCDA5EFE308EA3258ULL, 0xF566BDD360A01815ULL, 
            0x1B1B3B0F9199D578ULL, 0x87FF3C34B86A0507ULL, 0xD27916261BD90F00ULL, 0x6E97E2190CE10017ULL
        },
        {
            0x93753299508CB245ULL, 0x0D66FAEE53251190ULL, 0x60789A16908E479EULL, 0x148523D422C0688FULL, 
            0xF7708FEC8BD02487ULL, 0x0ECEC0098C01408EULL, 0x4838A64CCB5C23CEULL, 0x6A341395190062F7ULL, 
            0xC35D697FB290A33CULL, 0x4E99B0B342824B73ULL, 0x8ACBAC8F07EEAF9BULL, 0xCC7D3F5C5801A4BFULL, 
            0x04BA2CB99E951707ULL, 0xB7F28F1C4E153D48ULL, 0xDAA05E118B5D871CULL, 0x22A2FCB316A09AAFULL, 
            0xFB20C9701A1C0B21ULL, 0x3B3DD6CA526AE302ULL, 0xF0A1D087EACCB62EULL, 0x94ED74A1B5B78346ULL, 
            0xFAC7356A34B99BCCULL, 0x9DEF4276D6C9B368ULL, 0x3885DFFFC7C57CD6ULL, 0x17273A814BB475F8ULL, 
            0x3ED0B588D712230BULL, 0xAB5DA0F30A8AD3F8ULL, 0x407BA4A6BF2E5336ULL, 0x9E7B8A278379802BULL, 
            0x637FCEF4293FD407ULL, 0xCBAA45E1547000D5ULL, 0x57503010B198A804ULL, 0x66C7D2DFA93ADBC1ULL
        },
        {
            0xACC77B46EC07DE0CULL, 0xAF4693F58D6EDF31ULL, 0xE37642D47FE67049ULL, 0x9113E20EEBAC7BA6ULL, 
            0x2B6CC6B7D5F1FC9DULL, 0x0E9E8E1C2FF4AFA5ULL, 0x08FC781839F5F7C7ULL, 0xCA6A2BE954321D92ULL, 
            0xC03FA969D80F1D70ULL, 0x5A1E12612DDF1B4FULL, 0x434A15A6A6065FFDULL, 0xFD312D407215EB2FULL, 
            0x7428FAA5DB3DC473ULL, 0x3CC8994FE9A4EBFFULL, 0xAB7DFEF240D17B60ULL, 0x2A70434925BAB72AULL, 
            0x62A21A6AD32726B6ULL, 0x799092454146E67AULL, 0x2DAEA32488C92F0FULL, 0xC602973CABDCDA94ULL, 
            0x96B4E9DB5AFFD922ULL, 0xC442AB6A4D6DEC2CULL, 0x82A1F8A42CD8E1D6ULL, 0xD6A142AFE5B435E8ULL, 
            0x65B7B43CB0C52D2EULL, 0xB9226DE210205E79ULL, 0x51EE99D1811091B5ULL, 0xF9F4D9E775DDD4ECULL, 
            0x51F71D13C6F6A9CEULL, 0x4AC01D3304EE7BCBULL, 0x98448DF2FA28482FULL, 0x159080CC0A073DAAULL
        }
    },
    {
        {
            0xD433602AB6024156ULL, 0x5C5F38B7446742F9ULL, 0x221C4DA132D22A1BULL, 0xD93AA0BE8B1DE231ULL, 
            0x03787CD05BDA9F61ULL, 0x5D9F469B48CA701EULL, 0x1120A0BFFA5D18DFULL, 0x8CED57FA875CA7A3ULL, 
            0xE3652DBF179C6F2EULL, 0xBD794797D44858E0ULL, 0xFCBECFC8ACD4290EULL, 0x8B5DC087EA85F196ULL, 
            0x3F5EE3888A05F611ULL, 0x17AFBC9947D222D8ULL, 0x78AE8B6786AE374EULL, 0x727204AE02D79ADDULL, 
            0xBE41558C5160127BULL, 0x4A97B3EF5CFA3082ULL, 0xAB95DEB196C46185ULL, 0x7B6D9D53CF26E75CULL, 
            0xB757DF88C7DFA170ULL, 0x0645212B9904FE90ULL, 0xB43EDB09E65E74AAULL, 0xE673839A5E75B8D3ULL, 
            0xC75904BEDE9D2EF5ULL, 0xA3D6713D10BAB20EULL, 0x6D1593F7321775DEULL, 0x38CB69487A3A3B6DULL, 
            0xA3348FCF9DBE40A0ULL, 0xE5AB93C828B1F7CBULL, 0x39DF589CF528EA89ULL, 0xDD6265D8E5084173ULL
        },
        {
            0xD61CB4B7945E3EBDULL, 0xC38AA0D27D37CEC7ULL, 0x153B5627104801D5ULL, 0xBDBCACFEF09DA27CULL, 
            0x3EE6CECD00CCBBC8ULL, 0x307FDE272CA8A95FULL, 0x182C3A2F238B8EE7ULL, 0xB69EFF9FDB0CADB6ULL, 
            0x31A42CFF3B933DD8ULL, 0x239A32FD9CFD5657ULL, 0xB1E45E342A277CBEULL, 0x72FF8333D9E68365ULL, 
            0x4D04FB7B1C50D1E4ULL, 0xF058E8E04828CB13ULL, 0xFC35654BCF2EFC0CULL, 0x71CF6C0C6AE69C40ULL, 
            0x395A71F905715EFEULL, 0x21584A99131DFC76ULL, 0x7AA6B3175DE031E2ULL, 0x90CA9B24583468C4ULL, 
            0x67F854FAA2B48E97ULL, 0x09AD38368F406FCEULL, 0xC3BB2CA46E1A2F65ULL, 0x1CF86FF405D13A2CULL, 
            0xD56B79C5AF844FD9ULL, 0xB9B21186947CEC87ULL, 0xD0CE026DEEB52D80ULL, 0x90D8537F2B9E89A5ULL, 
            0xFBACB5E1EC2D2749ULL, 0x6CEDAB780E13B2C5ULL, 0x1BEB8977744E66BEULL, 0xC7F6AABBA603F782ULL
        },
        {
            0xC09962FD48615EFAULL, 0x0C208A9A5F3AD578ULL, 0x590F21386FE4CE6AULL, 0x816FEC995FA637BFULL, 
            0x64B9B21F3170CEB8ULL, 0xCB4762F28409E004ULL, 0x72C21730CEE26682ULL, 0xB5CEA5ABE2771CC0ULL, 
            0x156BD3E44054B57BULL, 0xA2B107D6FD03C5E2ULL, 0x87CFF852E527076DULL, 0xADE65AA20A8BB917ULL, 
            0xA697043B9B7BA7BCULL, 0xBD180D7271C51651ULL, 0xEFFA176410FDEB0CULL, 0x40DE1E4C19C1778CULL, 
            0x2232A7EC91BBA6BCULL, 0x2EAD445E0FD4D6D8ULL, 0x7FA42A8A8BE5B5A7ULL, 0xBB938E3350546570ULL, 
            0x1C9D41F4B701E51FULL, 0xAFFA0A14B98247A4ULL, 0xFA2140A9CA80CB61ULL, 0x0F7866170511EFA2ULL, 
            0x56F73EE1439EDF3CULL, 0x2A6113CE48E72A51ULL, 0x8CF87D574A0038B6ULL, 0x9792F0E486BB5887ULL, 
            0x5D1841A9DC0148DBULL, 0xA3951470E902CAA9ULL, 0x7C832C78359C452CULL, 0x65B54A90825AB9BCULL
        },
        {
            0xB8BFACCA99469F7FULL, 0x404366597A1CAE26ULL, 0x66F460255BB6A4C0ULL, 0xE4372E61168A5A17ULL, 
            0xC9BA4822C022F746ULL, 0x2A83BA383D00E538ULL, 0xEEF253CF1143EE4BULL, 0xBC98794388A2360CULL, 
            0x33095811823B0869ULL, 0xF96C166144E9701CULL, 0xF62965FD8774328CULL, 0x855F929D0E8DEDACULL, 
            0x61BCAA54393B9623ULL, 0xB585A61234E60F3AULL, 0x12897B9A7B02EF91ULL, 0x183D371999118D38ULL, 
            0x7632E4A1B4D3B76BULL, 0x778AF3E94DC2D9DEULL, 0x0754F58E0BF11A52ULL, 0x2312273D2079412EULL, 
            0x92221C2F7F70AE04ULL, 0xC5E7462AEB7215BAULL, 0xA2C041648A34FD6DULL, 0x8323F2BFAED06A79ULL, 
            0xB31B2332BE068DCBULL, 0x0FF01A4ECEE8E9CCULL, 0xF660B84C9CB81577ULL, 0x3CE870DB4B68B20CULL, 
            0x182F9FD038AB4F19ULL, 0x0F4F1DA71A8C4DA2ULL, 0x8A5E8F0EAB775F81ULL, 0xAF93550D952CB080ULL
        },
        {
            0xA1E388BD2FDE55FFULL, 0x6F35F64B9F68F39AULL, 0x8FA24782822B4F56ULL, 0x286EA0FFB42C3D02ULL, 
            0x093C43AD5A7D6FA5ULL, 0x818574B015A02BA5ULL, 0x3A66E7A7A1EC88CAULL, 0xDEF5781ADA1628FFULL, 
            0xDDC01B44A7546E16ULL, 0x03FB1CAA56BC0DF6ULL, 0xE9B80B6C41819420ULL, 0x14AEF06AFE629657ULL, 
            0x0195B32456ABC8D0ULL, 0xEFDB7FF912B13E9AULL, 0x072A6CAE6ECDDD0CULL, 0x4E9E98BD042BC6F5ULL, 
            0x597AA8D96F0366E6ULL, 0xA76583D375A22D7DULL, 0x52AEBE6C997B2D1AULL, 0xE2CAA0ABCF2F5504ULL, 
            0xDDBD4BC495459750ULL, 0x0FE6173F425C46D9ULL, 0x8D26D780ABC0B03CULL, 0x55C90D9FE6B5EB16ULL, 
            0x9A120F04F8FE2692ULL, 0xF59BD1574D3BE0CAULL, 0xC22A1CFD120F9664ULL, 0x6BB4CD6E7E9A90F2ULL, 
            0xE8FF7019DEFA87EAULL, 0xD125818A07E59117ULL, 0x1FA7334CEC1C5B0CULL, 0x7AF2A875A90F4A35ULL
        },
        {
            0x0B7D5A5B7446F0E6ULL, 0x77B4F99B200F77E0ULL, 0xEB813F73481EAF96ULL, 0xC60104E4BC970978ULL, 
            0x7F95661C80A27059ULL, 0x46E56857B8DE4531ULL, 0x2CA6A9E306C28475ULL, 0xD3B5D9C04AFA20D5ULL, 
            0xF4D4265B5D6FD774ULL, 0xC099706AFC0338CAULL, 0x504CA8C875BD84BAULL, 0x0035B1F5E55C9955ULL, 
            0x2A07585BE189C94CULL, 0xD37E878AC0A50FD4ULL, 0x24C37792D74F6DB6ULL, 0xF3B0E9E31E1FE6DCULL, 
            0x1CA4C4629B16EC70ULL, 0xD1F6D6968CA32907ULL, 0x9FF28397BD04C25DULL, 0x08A3CDAA0FB010E0ULL, 
            0xB94EC2EB99F5C1A2ULL, 0x6A5E8F74908EF41AULL, 0xD100353CFBEB7F01ULL, 0xB05E26BFBB3E91BAULL, 
            0x05EDAE987118FDEFULL, 0x928C319AB17BFA8DULL, 0xED705F2EE8F8C80BULL, 0x24BA43E6E042F4E3ULL, 
            0x41134FD38758F467ULL, 0x2FC90AB687D1CDD9ULL, 0x062700927D234D61ULL, 0x63665DB239509D13ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseHConstants = {
    0xEA76B2C96774722EULL,
    0xD9195EF3A6AD5524ULL,
    0xC30FB8C4FF8B236EULL,
    0xEA76B2C96774722EULL,
    0xD9195EF3A6AD5524ULL,
    0xC30FB8C4FF8B236EULL,
    0x82A0B26450617A2EULL,
    0x15E5C586D4AB7028ULL,
    0x2E,
    0x5E,
    0x39,
    0x34,
    0x2B,
    0x3B,
    0x93,
    0x26
};

