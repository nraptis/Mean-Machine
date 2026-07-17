#include "TwistExpander_Altair.hpp"
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

TwistExpander_Altair::TwistExpander_Altair()
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

void TwistExpander_Altair::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x87DA14807A6C40BFULL; std::uint64_t aIngress = 0xB6D3AFCEAB8A6301ULL; std::uint64_t aCarry = 0x93DFD765B092822FULL;

    std::uint64_t aWandererA = 0xE638D06CF27F6FA6ULL; std::uint64_t aWandererB = 0xA43D8563DD1BD0AAULL; std::uint64_t aWandererC = 0xAC716A0292299CAFULL; std::uint64_t aWandererD = 0x8B52EF1E20397436ULL;
    std::uint64_t aWandererE = 0xB89257F90D3B43D2ULL; std::uint64_t aWandererF = 0xC34C1089FB0EA72FULL; std::uint64_t aWandererG = 0xA1E3E50394AFC7E2ULL; std::uint64_t aWandererH = 0xAB35D977EA3E0568ULL;
    std::uint64_t aWandererI = 0xD6C7EBD0104E4C11ULL; std::uint64_t aWandererJ = 0x8F50C33309DA8434ULL; std::uint64_t aWandererK = 0x85C27E933F337D95ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17958321792455308596U;
        aCarry = 18422207072150640529U;
        aWandererA = 13349880697921418655U;
        aWandererB = 13705675261806687725U;
        aWandererC = 11611944861159503999U;
        aWandererD = 12746901383298136010U;
        aWandererE = 16775312447529738801U;
        aWandererF = 11278422271687142665U;
        aWandererG = 14485190528428494356U;
        aWandererH = 13352020453320136715U;
        aWandererI = 17880012649430458218U;
        aWandererJ = 15868632940463264474U;
        aWandererK = 11828200992991693331U;
    TwistExpander_Altair_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Altair::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC11FBDC04231E3F4ULL; std::uint64_t aIngress = 0xAC5CF1826F167976ULL; std::uint64_t aCarry = 0x9D069AE29AA0044AULL;

    std::uint64_t aWandererA = 0x86B3DCC7C82A6E7BULL; std::uint64_t aWandererB = 0xE7D80F996F553990ULL; std::uint64_t aWandererC = 0xB2BC1EC170EC2060ULL; std::uint64_t aWandererD = 0xAC3C805CF4D7483CULL;
    std::uint64_t aWandererE = 0x838441D9B567AF5DULL; std::uint64_t aWandererF = 0xF2396DF9C3EB0859ULL; std::uint64_t aWandererG = 0xCE1FEAF9A2DD88B9ULL; std::uint64_t aWandererH = 0x974193134E27F8EEULL;
    std::uint64_t aWandererI = 0xB325F9231CFD48BBULL; std::uint64_t aWandererJ = 0xB08D4F03BB22C58FULL; std::uint64_t aWandererK = 0xFBE0BBAAC6F7AD1EULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15666350658906328169U;
        aCarry = 12042186595734219730U;
        aWandererA = 16914706390838670142U;
        aWandererB = 10464338490787070591U;
        aWandererC = 9748223090714340653U;
        aWandererD = 11171704884084584497U;
        aWandererE = 17228749230578445958U;
        aWandererF = 18385064014119671141U;
        aWandererG = 16794149941393774768U;
        aWandererH = 17846720303928527690U;
        aWandererI = 13142461427142441107U;
        aWandererJ = 17736808848530163594U;
        aWandererK = 18220913915290314575U;
    TwistExpander_Altair_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Altair_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Altair_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Altair::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE9DA523A817CA5A8ULL;
    std::uint64_t aIngress = 0x887D087F6B8EB349ULL;
    std::uint64_t aCarry = 0xC6BEC3F4A014BDCDULL;

    std::uint64_t aWandererA = 0xBD9F8D4E06EA58A4ULL;
    std::uint64_t aWandererB = 0xEFA8A68E07C8CE03ULL;
    std::uint64_t aWandererC = 0xEADB3709946EAFB8ULL;
    std::uint64_t aWandererD = 0xAF2CCB25924984C0ULL;
    std::uint64_t aWandererE = 0x89FD99818F923506ULL;
    std::uint64_t aWandererF = 0x9F9BB9B3518FE584ULL;
    std::uint64_t aWandererG = 0x8861F3761349AD62ULL;
    std::uint64_t aWandererH = 0xA1840678F9110CA1ULL;
    std::uint64_t aWandererI = 0x8CC4E033982BE33CULL;
    std::uint64_t aWandererJ = 0xA92F23A5FD535F58ULL;
    std::uint64_t aWandererK = 0xD3F794FD00B2E231ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
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
    TwistExpander_Altair_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Altair_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Altair_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Altair_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Altair_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 7 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1907 / 1984 (96.12%)
// Total distance from earlier candidates: 11500
void TwistExpander_Altair::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 774U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1152U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 6U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 214U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 22U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 815U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 946U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 348U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 152U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1799U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1905U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1537U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1950U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 61U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 903U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 294U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 659U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1149U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 458U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1209U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1859U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1841U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1512U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 344U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1349U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1806U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 427U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1960U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 870U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 75U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1882U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 582U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1378U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1729U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1921U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1891U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 830U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1395U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 573U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 844U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1666U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1901U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2004U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2021U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1610U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1320U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1480U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 856U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 179U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1375U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1500U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1791U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 324U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 491U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1504U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1444U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1890U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1619U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1774U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1103U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 772U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 163U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1290U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1548U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1056U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1064U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 861U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 103U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 77U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1226U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1095U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 528U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1834U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1802U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 418U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 100U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1182U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1853U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 829U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1586U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 476U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 223U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1098U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 594U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1592U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1337U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1959U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1354U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2017U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1223U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1762U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1838U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 920U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 667U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1380U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1297U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1926U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1957U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 259U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 828U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1085U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 153U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1401U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1481U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 229U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 518U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 392U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 10U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 149U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1626U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 320U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1598U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 59U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 788U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1331U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 743U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 700U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1302U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 675U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1516U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1125U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1584U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 524U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 766U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 511U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1162U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 181U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1596U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Altair::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xF693E291595AAA6CULL; std::uint64_t aIngress = 0xD26D23A2BAB36799ULL; std::uint64_t aCarry = 0x997015BFD9DE4133ULL;

    std::uint64_t aWandererA = 0xED069A505FAE83D1ULL; std::uint64_t aWandererB = 0x809D7FDF63839833ULL; std::uint64_t aWandererC = 0x97FEFAEC6F7B1735ULL; std::uint64_t aWandererD = 0x8DBE295AD29F00D2ULL;
    std::uint64_t aWandererE = 0xAEFE234F741809B9ULL; std::uint64_t aWandererF = 0xE9AD9F306BA01250ULL; std::uint64_t aWandererG = 0x92F504C6A86693FBULL; std::uint64_t aWandererH = 0xEE030173CC5BB1F9ULL;
    std::uint64_t aWandererI = 0xE56E7EBFBBE451E7ULL; std::uint64_t aWandererJ = 0x8F531C229064CFDBULL; std::uint64_t aWandererK = 0xE11BD216D9B5FB29ULL;

    // [seed]
        aPrevious = 14763290156999124776U;
        aCarry = 14220883800573440405U;
        aWandererA = 14537323730479711553U;
        aWandererB = 10244935371467346516U;
        aWandererC = 15913098401870002988U;
        aWandererD = 13548951631356816639U;
        aWandererE = 11434168328305722747U;
        aWandererF = 11283439790735655582U;
        aWandererG = 13067285274072879781U;
        aWandererH = 14195550094608488757U;
        aWandererI = 9796190247431236295U;
        aWandererJ = 11135479014150175955U;
        aWandererK = 13737998479506478921U;
    TwistExpander_Altair_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Altair_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Altair_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Altair_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Altair_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 7 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3392; nearest pair: 494 / 674
void TwistExpander_Altair::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 570U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4651U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3096U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2468U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6679U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2344U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7514U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 888U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 166U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3361U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 392U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6730U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6144U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4854U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3513U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2916U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 261U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 249U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1926U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1625U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 300U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1004U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1636U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 824U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 972U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1898U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 923U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 595U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 932U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1079U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 791U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 413U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 95U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 634U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 926U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1901U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 7 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3387; nearest pair: 514 / 674
void TwistExpander_Altair::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6189U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4912U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2313U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5001U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3421U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4157U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6697U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3355U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 747U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 927U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5560U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3126U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7403U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3680U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4311U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6723U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 924U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 600U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1369U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1934U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 669U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 959U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 147U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1632U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1857U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 584U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 937U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 853U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 904U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 710U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 157U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 960U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 80U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1992U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1851U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 136U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Altair::kPhaseASalts = {
    {
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
            0xBA59C59EF7CC7375ULL, 0x271431D6FD806493ULL, 0xEA22626D8D8A9236ULL, 0x9250E09A6654ADA5ULL, 
            0x608E628039DEDDFDULL, 0x47E5D026CD3BB6A7ULL, 0x3B08D2C79C6ABAF2ULL, 0xD42149EF2E00F250ULL, 
            0xDA8B92B190CFADA6ULL, 0xF69AC9742317BC82ULL, 0x0AACA76BB5C19504ULL, 0xA5A2CB886C70992CULL, 
            0x9F08847787E23EA2ULL, 0x3DAF5DC8C917503EULL, 0x4C5EEE13DF81007EULL, 0xCF80212FFC51F6C9ULL, 
            0xAB17C8BCC2DE64F8ULL, 0xCC48BCD484F2C757ULL, 0xB375D203ABBF2825ULL, 0xC6AA094922CBD9BBULL, 
            0xA7771043EB9FDEE9ULL, 0xD957FED6A81ECC88ULL, 0x5D75B657FE438229ULL, 0xCFE5F5627693E6F7ULL, 
            0x1A09A0E78391A71AULL, 0x5DB4DD4B45037F3BULL, 0x0DBC6ED888770C4EULL, 0x0889802947F637FBULL, 
            0x1E6C88202CB131BFULL, 0xCA95D5DE59631F40ULL, 0x58ADDB1FF2E185E1ULL, 0xC1979D5102895597ULL
        },
        {
            0x41EB3919F9AA679DULL, 0xC557B13AD2B22370ULL, 0x4BF4E373BA9B5B7DULL, 0xD37F39949254D3D3ULL, 
            0x76287403BC2C67F3ULL, 0x66F1D97DC141BB85ULL, 0x7918DCDA8723F797ULL, 0xA0288B2CE4683B75ULL, 
            0xDC90F23DF6B323E0ULL, 0xE5B0B461E63C71AAULL, 0x26616F5E5F963184ULL, 0x40E4496DCE1CE183ULL, 
            0xAE327629EF2FA6D8ULL, 0xD3F06FBE9C61BC73ULL, 0xB89E917F3A9C9C4DULL, 0x06EAA4B6E1AEECD1ULL, 
            0x190126B03AE9856DULL, 0xBC1F15A95467C18BULL, 0x10921800FC33F7BFULL, 0x59FC3B669E4B2FC4ULL, 
            0x17B4449D70602A12ULL, 0xAC54872EF24DD4DBULL, 0x69C232037B9F84C6ULL, 0xB1B8E388B388A18EULL, 
            0x9CF13EAE429CCFA1ULL, 0xEA14C8C0822DC9E0ULL, 0xA3381A1D9041D25AULL, 0x5EC634318F1D4604ULL, 
            0xA5B38FD7EED3FED1ULL, 0x71DEE536427849E0ULL, 0x21B07DC33CA0E8ABULL, 0x06E7D2CEA07E8F12ULL
        },
        {
            0x93F4EC4B05E83E55ULL, 0x86738B59F895E13FULL, 0xDC8E425E41334A16ULL, 0xEB48B67A3F47CB26ULL, 
            0x01C5E1362177C61CULL, 0xF91B1551C68A3EB8ULL, 0x245ED7DD33B15232ULL, 0x2B8DA14E273A0790ULL, 
            0x2C346E2640B6C94CULL, 0x7A3B61140659F78DULL, 0xC319C706227EBBB9ULL, 0xF1C8E3021B4D4707ULL, 
            0xC1504CFB2308104DULL, 0x09A4DFDEB878B342ULL, 0xCC8BB689A622FB71ULL, 0xD79005DE10811955ULL, 
            0x135652B8CA4989C6ULL, 0x117E6FD88013E4B5ULL, 0x3354FBB9CCCFC719ULL, 0xC961344F06E2F6C4ULL, 
            0x8128A4D63EC82841ULL, 0xCEBA5DC41FE87D5BULL, 0x676D998728AF55E3ULL, 0xD174DEC1D3C6545FULL, 
            0x01C5BA7AA0463C79ULL, 0xF0531772FE81A319ULL, 0xBD8085ACD22CCFA5ULL, 0xC9C957BBB7A16723ULL, 
            0x13DACAD35898737DULL, 0x753AF9741A0732FCULL, 0xD1A82A41CCE5188DULL, 0x8E18B5F6D87AA67DULL
        },
        {
            0xD9179AE45CDEF4A6ULL, 0x27835D1001EEC19FULL, 0x9F588B7B9F4E5CB4ULL, 0xCE1572E60C372CF3ULL, 
            0x5B34EEAC424DE787ULL, 0xC12F0C4B0BD13494ULL, 0x33AEB1C555D0E4C0ULL, 0xBAB56F047729E422ULL, 
            0x090F6C0154C1218BULL, 0x0BB2E27AFDBE3C0DULL, 0xBFE9DE6C7183A019ULL, 0xE0DB8981AA82A450ULL, 
            0x7D78C2C2CF10324FULL, 0x3B20490F377639FBULL, 0xA8E33A1F07848238ULL, 0xE642442CCF3AEFD0ULL, 
            0xC8FEAF49518BE493ULL, 0xFC2A1D056305AF2CULL, 0xE980C1DD5782C462ULL, 0x101FE7A9FF6C0CD2ULL, 
            0xA8BF3A6845323BD6ULL, 0xCC58804B4550F593ULL, 0x30439A75D9F94042ULL, 0x7B5969D0EBB9F687ULL, 
            0xA9B18B86BF9FF56EULL, 0xCB6B884DD825B74CULL, 0x9C80736F10C05F37ULL, 0x56A99A5D2FEFE9AEULL, 
            0x373CC369DEED6371ULL, 0x84A54E1386130FB8ULL, 0xBABEF3E0619A7958ULL, 0xB758EBF34CC4CCE9ULL
        },
        {
            0xFA0509E8BE0C2E6AULL, 0xF7C89A67D6FEF9C0ULL, 0x783126840213B399ULL, 0x885C3545CB5CE1FEULL, 
            0xB2487F44B35DF8D8ULL, 0x5D8BBB612FBBC74BULL, 0x2504A7A5EDFE687DULL, 0xF57CB3DF707E6866ULL, 
            0xA83DE02ECCF1B355ULL, 0xF1595DF485045D57ULL, 0xC0029131034FA5FCULL, 0x26106694BFF219DAULL, 
            0xADE4D759F913CFDEULL, 0x006D1F794A11CF65ULL, 0x0F82DF89BD456F57ULL, 0x58FDE6CA5B467E1EULL, 
            0x7C1B2B0489F81435ULL, 0x6F7E0089FD49D761ULL, 0x6A4176D33C75DB7CULL, 0x021EABFC5322F295ULL, 
            0x25FA2FA6638DF687ULL, 0x0DCD572A66E33F1AULL, 0xA3B3929B3D992855ULL, 0x70E3EB7C806BF236ULL, 
            0xA37C9B78DDD8511CULL, 0x54A780DB2F5B1DA2ULL, 0xA872B769901FC17FULL, 0xA44C374FB36D47B5ULL, 
            0x731398E685F21D0EULL, 0x77124BBB36833383ULL, 0xDCA265B139FA6FF0ULL, 0xEE78BA85367CCB36ULL
        }
    },
    {
        {
            0x66D6BA801D5E1848ULL, 0x84A03F54C609A0A5ULL, 0x225823A7746A1776ULL, 0xE2D6FF0EBAA8430CULL, 
            0xD0823146F28B487AULL, 0x08819556A7896D7EULL, 0x5FFB6770B21B14C9ULL, 0xA4F8901FAE8BD93FULL, 
            0x85D3C13C55481716ULL, 0x39721EAA18B0BB02ULL, 0xC034DF3130028B6EULL, 0xFE96CF1470AE37AFULL, 
            0x6D924CEBAF1FB2BBULL, 0xFBD9CF02D7AE5E2CULL, 0x04BD39D454726651ULL, 0xB113DC6374ABD268ULL, 
            0x1C4F339183623C5EULL, 0x369BF2F4FB49618AULL, 0x759ECA32545A4FE4ULL, 0xFCEA257D67C9D90DULL, 
            0xC565E6F238489EEBULL, 0x302F28587DA8C72AULL, 0x4E56434399614C6BULL, 0x69150D959C2FF0D0ULL, 
            0xD804D464DAE126D0ULL, 0xF012B38A5E224109ULL, 0x90F2887A7BA09871ULL, 0x471D48F7BD40E68DULL, 
            0x9DDAB875CD515892ULL, 0x3C39371E07ECFA8BULL, 0xF2CBFD905574DBEEULL, 0x06854D64A26B0A6EULL
        },
        {
            0x6E0E4043AD41EEC2ULL, 0xDDCAAA35FD83EC15ULL, 0x64981CB7A6EA0FE2ULL, 0x1DE65C4378B5A422ULL, 
            0x45B780B12795E310ULL, 0x8FBA0C7D6CC411FCULL, 0x3DEE7A9624B1FED5ULL, 0x37CED2EA5CDA2535ULL, 
            0x5F62C5A8DAD3A4D5ULL, 0x4D388B854BCD7655ULL, 0xF7BA871A89A6F8F4ULL, 0x3EF3699EF31390E5ULL, 
            0xA86869045A51CFC2ULL, 0x8F839EB8A9903A4FULL, 0xA7FE0E98F0C152BAULL, 0xAD886809A9405970ULL, 
            0x0C88A12FA3B8E802ULL, 0x1A1D26CA9795A54FULL, 0xB6C5F700AFD86D41ULL, 0x21DEC73089932184ULL, 
            0xE3E819CAA043A834ULL, 0xFC6BEB054EB82842ULL, 0x7F1A8E76E71DC173ULL, 0x13BA241C875876AFULL, 
            0xA7B46300C50F136FULL, 0xD3EF8217A70BBB9EULL, 0x6337A241DE0671AEULL, 0xBECEF5C8BE54801BULL, 
            0x6FF50F08D2FAF3A0ULL, 0xFA2DFFBE4F627B0FULL, 0x06F7AA86C1CE20A3ULL, 0xA40F50FCB167F434ULL
        },
        {
            0x62D0B4F5FD780B67ULL, 0x0844F768237E7479ULL, 0xDC4C23712663834DULL, 0x5FB8CDED631DDDBAULL, 
            0x2122FCFAD4BD16D3ULL, 0x3F230A64D83B1C5CULL, 0x621FAE27E4110917ULL, 0x9357BB687C96F155ULL, 
            0xBE122351F0708FD8ULL, 0x16F0A59E19A0A560ULL, 0x25492B9BDD8E84D2ULL, 0x5595A2821970CDB7ULL, 
            0xCA2BD571E82F6307ULL, 0x3D7E958C5B2D5FF0ULL, 0x70EE9509D72E0203ULL, 0x116916FA919ADA2FULL, 
            0xBBE7B8B933052034ULL, 0xBA4114DC04358CFEULL, 0xA2B90737C19387ECULL, 0xA03F7DB9960BE3E8ULL, 
            0xABA1CA6A139547FEULL, 0xCDE72DA2BD7B38C3ULL, 0x524405C7D022D8F3ULL, 0x25DD9289497E40CEULL, 
            0x36193C6ACAD8965AULL, 0x7F25028530E66E7AULL, 0x1BBF0C27239D6469ULL, 0xEB66950A55B3AF8AULL, 
            0xA70FF89A4DBAC62CULL, 0x7CDEE99BFD926208ULL, 0x02EB73C04143E943ULL, 0x08EC659093C4A3C3ULL
        },
        {
            0x35BF8F1588999CE3ULL, 0x69B696D4483D7DC5ULL, 0x2D7A59F58F164985ULL, 0x8A083D619F6D6E8FULL, 
            0x7D37250EA69203B0ULL, 0x8466CB9E08AB98E3ULL, 0x921FA302F315197DULL, 0xCC35ACB4B4D5152CULL, 
            0x7031FE6098F209BBULL, 0xEE0CEEDA4867FF68ULL, 0xC2DA7B4EBCE8B087ULL, 0x02F14F522EA61967ULL, 
            0x051CCC322A0E91B0ULL, 0xE029B786FE3B31F5ULL, 0xEC88ACBEE46E7C88ULL, 0x0E84D11CCC8273EBULL, 
            0x695AA0942B9917FCULL, 0x9F851CB555DB56D9ULL, 0xA1C98B6370F4068FULL, 0xAECF2C76F448D23AULL, 
            0xE822B21D7E1A38C5ULL, 0x40A915154C06E0B8ULL, 0x91EE625AD8CD67BEULL, 0xE8BF63FC704C5CF4ULL, 
            0x9B070C23E48A1207ULL, 0x9021FE94460ECE36ULL, 0x2F2FF6F71515258FULL, 0xBF8205957D577696ULL, 
            0x2707863398570D21ULL, 0xB68B8A963426B667ULL, 0x00EC36819B99D9B9ULL, 0xBC240EEDBE65661FULL
        },
        {
            0x8C4C7C633133FB56ULL, 0xA95AE25D35D55008ULL, 0xA194332C9B23D691ULL, 0x39126FD5EDC551E9ULL, 
            0x0AF98E3E463E6161ULL, 0xAC7FCD152114A3D2ULL, 0x8A170D7A570B1FF7ULL, 0xDE442098700AF02CULL, 
            0x67AE11892C8B74F7ULL, 0xCDC4BA3533766B55ULL, 0x546AC0573C3258D8ULL, 0x155B23589CD4360BULL, 
            0xA856C1A82B6E4820ULL, 0x2FA0DA6CF89B5A0FULL, 0xBD88931DF60EAB02ULL, 0xA75AE9F84D86979EULL, 
            0x7C8BD38A35EF1FA9ULL, 0xF0DB1C14B37416D0ULL, 0x42CFEFA485363918ULL, 0xAE852E42BF16A716ULL, 
            0x3DA9C8A75F2EE484ULL, 0xD2FF18551F7C29F2ULL, 0x9281BDBDA693191EULL, 0x555CB48EEFC7F0AFULL, 
            0xE4922787118E66B5ULL, 0xB50B154E1D0C3554ULL, 0x044319DC8305E906ULL, 0x685128632741D672ULL, 
            0x1B49AF7062101E7EULL, 0x3D7CBF8DBE23E847ULL, 0x2FC83540CE097A4AULL, 0xCBB3D96F68A97993ULL
        },
        {
            0xCF74906645129D42ULL, 0x6E914090DB8B95ECULL, 0xF7FD07AB7CDC1A03ULL, 0xEE89EF2161288853ULL, 
            0xE7D753B27EE28B12ULL, 0xE7D137FEB0D51E62ULL, 0xD78DADA7EC4AC7DBULL, 0xB736F78953A482CDULL, 
            0x8EEA032B9CC41F09ULL, 0x044363A32FCFADEFULL, 0x58F40876B1BAF081ULL, 0x29C6744C31003A77ULL, 
            0xEF5A122C6D437317ULL, 0x335A11FFC6D68BEFULL, 0xF04F2A11B9705A47ULL, 0xD0B8A6B7118CCD8BULL, 
            0x720238D4F0E0AC50ULL, 0xDA709356C36E6107ULL, 0xD2FAB93F2301C91EULL, 0x69B0545F320F6572ULL, 
            0x485F045BCF5E3EC3ULL, 0xDC139C1342A3A1E6ULL, 0x3850DDADDA435186ULL, 0x4843EAEA5B84873FULL, 
            0xF7C40EF9BBD48887ULL, 0xB3B6D0787060420EULL, 0x1CAFA740B28AC0F8ULL, 0x9B4DCDC9CEC60D98ULL, 
            0x898FD0426D9E9343ULL, 0x88787E2360862975ULL, 0xEE10AA9590194BE0ULL, 0xD569CCBE879930D5ULL
        }
    },
    {
        {
            0xE684D7C1840ABEF0ULL, 0xF1C512BEDD1D88E8ULL, 0xAB19EBE059A8857CULL, 0x7A9B2B0046F985E8ULL, 
            0x5FB4823C37D0B2E1ULL, 0xCB16EC3A3DA24665ULL, 0x6D5BC78A839A9C82ULL, 0x69E88A0147056431ULL, 
            0xA185EFC4DF3A2C68ULL, 0x4B2754F07FFF1AF6ULL, 0x3D20E552E77F80B0ULL, 0x6AFCBB694440A79CULL, 
            0x2787E9285A1774A9ULL, 0xB9701F741E17A770ULL, 0xEC06B8230F9AF62CULL, 0x3793B613B31AB21DULL, 
            0x7333812B39913A96ULL, 0x6600E9017F8579A9ULL, 0x77199CED8E17AD95ULL, 0x2D32A56BABA3AB0DULL, 
            0x6D6B9A677AD05598ULL, 0x468E10EB838F35E1ULL, 0xE69948F57FA84844ULL, 0x62A3F2C545F1ABD5ULL, 
            0x5D2B4C630CE93707ULL, 0xB8279C533F9D2064ULL, 0x8DE82199CF914D6DULL, 0x7AC27D42E21B3530ULL, 
            0x1BBE816C22CF3049ULL, 0xAAE39BDFE1C25F86ULL, 0xE4592311CC4F4A86ULL, 0x50471D64901CEFD9ULL
        },
        {
            0x432A77E683FC1A9FULL, 0x5C1595225C839E17ULL, 0x61AA7F14D72A8142ULL, 0x74F2EC672B968B31ULL, 
            0x7C00F861EB47ECBCULL, 0xCB180D7A8C488338ULL, 0x45E6D50A65271529ULL, 0xEF2D595CCC3277A8ULL, 
            0x8F3A839EF8916FCEULL, 0x2FD461963791FF28ULL, 0xAAF3DD6EE40E0BE8ULL, 0xEB0C7CC4836EC3FEULL, 
            0x40416567537B484AULL, 0x5297CB41D151BD81ULL, 0x9343C809D436B73AULL, 0xCF053041ADF0D043ULL, 
            0x9A413A3076D0ED51ULL, 0xC06D69F3937F12E5ULL, 0x36F0C7E5236426E3ULL, 0x97FD99B04F6D9F8EULL, 
            0xAE2E4FCEA09373A9ULL, 0x79E5C9F9731F21C2ULL, 0x84135638560AD151ULL, 0x2DEE2898A2C25F18ULL, 
            0x7F522B3DF290C371ULL, 0xF8EB754C6D8727F5ULL, 0x59EFCB3BE4D15A83ULL, 0x6A19233EEC6E0DA8ULL, 
            0xFC7D37FAD7B4A482ULL, 0x546464EABE44402DULL, 0xCD8A1BF7BB13F860ULL, 0xE54C3120FBD5918FULL
        },
        {
            0x670A14D1B75AF8CAULL, 0xEC62003400E8B7F3ULL, 0x986043F01F2BE2C0ULL, 0x56A6E4A89BE3C26CULL, 
            0xA122511491668B42ULL, 0x138BC753AD5BE5A7ULL, 0xE41C09F99AEF1E78ULL, 0x2F477F670C79F29CULL, 
            0x291F6FA35A2FCA52ULL, 0xB2898C48904E992BULL, 0x60BDD1EDA1AB9ACBULL, 0x0D6E0670736A1CCAULL, 
            0xB85FEDCBDD400BC9ULL, 0x327D27A276AB6DF8ULL, 0xA6E60915C591FFB7ULL, 0xCF4FD158AE889FD6ULL, 
            0x4959DEFACB4103E6ULL, 0xDB04C9342734D275ULL, 0x4F8C5CE41913C253ULL, 0x0ECEF40F7CE8E2F0ULL, 
            0xCDCC9C4863455B2FULL, 0x30ABBB35BE3FFCC6ULL, 0xB650D0D700C5AFD1ULL, 0x9CDA1563468C6655ULL, 
            0x41921F1B2CCD3721ULL, 0x910948E1915D1FB6ULL, 0xA32DC22BFE22AAF9ULL, 0x8ACB4BFF60F3067EULL, 
            0x5990311B6B90C800ULL, 0x7E53765F1A373C8BULL, 0xA289AC2965D66116ULL, 0x74742D5AA92F55CAULL
        },
        {
            0x90225BDD63B9BFDDULL, 0x05B4C0CF6E302FB2ULL, 0x76BDDD2C25668EC1ULL, 0x758C8907FFD6665DULL, 
            0x5F0B21EFED085B0CULL, 0xE906415095E12D49ULL, 0x78C8FE2F25764770ULL, 0x75608E1E48E2DF8AULL, 
            0x584DDFB1F12EC80BULL, 0x999F975FA3EA6CD5ULL, 0x40789D251E35A7CAULL, 0xFFB7FDD49B71EC16ULL, 
            0x23A9F6A17737B861ULL, 0x45281CA7BB377825ULL, 0x06BF9DF329B9B59EULL, 0x3C2AC3BB9385E268ULL, 
            0xEA46AF8BDC6E8AFDULL, 0x0F9BDAEF3EA61A16ULL, 0x0E4B22B5829704CBULL, 0x9268B9A9AF7A1AD5ULL, 
            0x322D312F3698B598ULL, 0x26AF761E60D891BCULL, 0x5A1A2FF00C496476ULL, 0xA5166569DD90001EULL, 
            0x93AC2300B8CC11ADULL, 0xAD618B92786A0739ULL, 0x2A563D2493138962ULL, 0x8BD335201B9BC180ULL, 
            0xF64A54107AFBE47BULL, 0xCD9E4A0BA73370E0ULL, 0x978B2F112D63E3C8ULL, 0xEEFD470585912ABEULL
        },
        {
            0x7E89C5B309B765F8ULL, 0x64C7A7D8790A1204ULL, 0xDC90D30612863A30ULL, 0x1CA434E95B030F54ULL, 
            0xCE2E20B4E62E16FBULL, 0x389361EB97A2DB8BULL, 0xF52A91884DA8441EULL, 0xF82A4F495DEB4E28ULL, 
            0xF832FD5673776F4BULL, 0x49D6C0DC396605AFULL, 0xDCEB218667FFDCC7ULL, 0x2F876C8C44D664A8ULL, 
            0xB7F1E71BFD275233ULL, 0x8E2A7F9D247B6A56ULL, 0xC70609BDA7C5B91FULL, 0xC76E8B00EEBB235BULL, 
            0x4705CC9799585C5CULL, 0x44B9362F07DF1AA8ULL, 0xE536B57C25AA4EFAULL, 0xBFD26EF8E864187EULL, 
            0x24DFA6D30084BC24ULL, 0x9BB9DECA2F2A2946ULL, 0x1F31C1DA7CE9C2F8ULL, 0x9FA1EBE2C85B1509ULL, 
            0xC4A88A1E180F3D2BULL, 0xE7190FDA810CBDF1ULL, 0xE789BE7E800A6E4DULL, 0x127E877B4C029485ULL, 
            0x94EE0DC5961A5E6BULL, 0x513830CFC78B48D7ULL, 0x1D7E81F20EA8153AULL, 0xAD1E6D4AF9E1A9F0ULL
        },
        {
            0xC0F8EC46951A57B9ULL, 0x0FDB8939B0654540ULL, 0xB703879AE9C555C8ULL, 0x28B98C2DFC90687CULL, 
            0x5702BCA9F5DC2354ULL, 0xAC259F31FAE73340ULL, 0x465A033E71745B56ULL, 0x266FFBFDD3612E0DULL, 
            0x566CA41726E5A197ULL, 0x86B3825BBF9D903AULL, 0xDE91B21253EB7C41ULL, 0xFAF2CFE725B5A080ULL, 
            0x40EDAD271EF0384EULL, 0xB4434EC4A9D8B45FULL, 0x1159705FED7287B4ULL, 0xD56B4F0187EFE9EDULL, 
            0x62E98CEAFA8ECB0CULL, 0x361B638D5AC5B1FEULL, 0x3323056610599BDBULL, 0xBD9DA58DEABA73BBULL, 
            0x5CEA8741E308B275ULL, 0x677602D810937DC5ULL, 0x74CE4CA6A1046178ULL, 0xA0F2914519167186ULL, 
            0x4C71DBFAE1046EE9ULL, 0xD9629CD4EBC1A44FULL, 0xCFCA2B03C89C1747ULL, 0xF1F8F573B3F04012ULL, 
            0xBC66A3E95F28352FULL, 0x7533F120D17FA1A1ULL, 0xBD8BAE7C3F894A1EULL, 0xC8D477226DBA8BFCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseAConstants = {
    0x75A0B85D6CE388F8ULL,
    0x7C0CE1EC30DB7DE8ULL,
    0x413A132D8EF8C35AULL,
    0x75A0B85D6CE388F8ULL,
    0x7C0CE1EC30DB7DE8ULL,
    0x413A132D8EF8C35AULL,
    0x7F7688982B02E165ULL,
    0x8BD0B2D5A8409677ULL,
    0x76,
    0x0F,
    0xDF,
    0x85,
    0x29,
    0xA2,
    0xD1,
    0x82
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseBSalts = {
    {
        {
            0x3826061E1C10A2A4ULL, 0x33B38768236ACA6EULL, 0x4737E895D7D2BF28ULL, 0x04A05BB749712EB6ULL, 
            0x9F8B4838BB3C38EFULL, 0x07F4230A8ABCB62FULL, 0xCA061DC64DC7D480ULL, 0x39ACA68AA3628464ULL, 
            0x42DB1A426ECBDAE7ULL, 0xEFB22A8740E3A69CULL, 0x06FEA1BCA892BEE2ULL, 0xF998350E69C3D8C8ULL, 
            0xB1E9BF87A377B2D2ULL, 0x3616531762E69DEBULL, 0x03B924663338184EULL, 0x89885A367C8C60F7ULL, 
            0x933990B43E53A130ULL, 0xC5CDD28519DAB7A5ULL, 0xA61095A46A4F3D4DULL, 0x3B25991132844CAFULL, 
            0xA691E230C166C730ULL, 0x2C1FEAFB4D57F13AULL, 0xDC36A58CAC915461ULL, 0x7EEA7F65E0DBF4D6ULL, 
            0x05912A5714189528ULL, 0x4C25FF8BDD0BE601ULL, 0x08BA38A3E54C63B7ULL, 0x47E105FB25A0B54AULL, 
            0x4D74B39B295CB9CFULL, 0xB45AE749AF19DB00ULL, 0xBC067D39D053A70FULL, 0x7E276F8FAC0DABF8ULL
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
            0x6C6717281AD8F027ULL, 0xDE7A314A08786EA3ULL, 0x69FB54C92FBD0ED7ULL, 0x0A9DA521C60BE07BULL, 
            0x0BCEF74E2D86DC48ULL, 0x436C6A57568D3FD3ULL, 0x6A9A6182B5190725ULL, 0xC55E6213BD347D9DULL, 
            0x12A0E8FA004BCA85ULL, 0x2813EA7AAE789474ULL, 0xD4FDD0D290FBB51CULL, 0xCCECA0D06315400EULL, 
            0xFB260F5DD94B1C8EULL, 0xB8B2480F03E09B7CULL, 0xBE29510841432908ULL, 0x88C732D37F947F2BULL, 
            0xC0C65943F1CAAAD8ULL, 0xAC48F7AFBCAE0CB1ULL, 0x90FED301691AD3BBULL, 0xDEF2117F9CCE172BULL, 
            0xD972F988234E79E0ULL, 0xDCE94DC1EC966F71ULL, 0x97CC7DCC468388C9ULL, 0x12297405BB9D025EULL, 
            0x248130A8F902F403ULL, 0xCC3A329891571C19ULL, 0x8072FAA4ABF1672BULL, 0x1AAF370609B59948ULL, 
            0xA9806380B1B8F8C5ULL, 0x1319C79CE7C85FCDULL, 0x43AB0D2D487F8416ULL, 0xAA11129B0F1CBE97ULL
        },
        {
            0x4367DD719F5E9A97ULL, 0x3132F1B0B33AC44DULL, 0x4AF4DEECB07BFAC7ULL, 0x3BA3AC570F6C5D5CULL, 
            0x51905FF8E7CE28F0ULL, 0xD5C9B50036B69901ULL, 0xEA6A4042B0A432A4ULL, 0x5A1DAD2BEB1B0F19ULL, 
            0x4193D8FD2E4B13A6ULL, 0xD5B95B679520DE4DULL, 0xCC476A240F85A6CCULL, 0x1ED4C543172CBC0FULL, 
            0xF3761F67D92092F2ULL, 0x2F15F3498FC66E8AULL, 0x263450112581C45AULL, 0x145E67E45BF699C9ULL, 
            0x7F81BF4CB234FD60ULL, 0x8489B7A0D78C1997ULL, 0x62BE1E642714A305ULL, 0x994DF94AE5A9905CULL, 
            0x3B2379DA4B9B0A96ULL, 0xEB5AC7FC030147A0ULL, 0x5D9E5983B64D61D6ULL, 0xB12424E51828D5E7ULL, 
            0x1693D5A08ED740E6ULL, 0x61F1C8F4CF9DCBB7ULL, 0x2B75FC03C46141FFULL, 0x74A9679A0151E94DULL, 
            0x534068A787115E00ULL, 0x1CD484163EE5F8B2ULL, 0x1722FA2CE36AC9BFULL, 0x916CFA42C4365963ULL
        },
        {
            0xE6E5A766E875D8B7ULL, 0xE006FE0BD1D77C4AULL, 0xB5C95CC81CB03F8EULL, 0x32ECB26C4A4175F3ULL, 
            0xA9E2797A434146CBULL, 0x8A3D4E6BF41E143CULL, 0x223194F2E86B9A85ULL, 0x768E0F130F8166C6ULL, 
            0xC1CA2CDD6D8B6C77ULL, 0xFB9BD3D9557E23A4ULL, 0x0B73E49E9C75D35CULL, 0x190B6D435B00093CULL, 
            0x9408740C2CC47889ULL, 0xD2BFB77FA2E00F83ULL, 0x6F26F35D61651639ULL, 0x6077171D283533EBULL, 
            0x1AB9FACAA5CDDAF5ULL, 0xB8B1C3D2B6CB3A2EULL, 0xE3A6121EF82D8E63ULL, 0xC3DAC66ECD8D2518ULL, 
            0x3B612940270C984EULL, 0xB083F74AD8CDA44CULL, 0xDCD3D34128E8878BULL, 0x1728297A1DE2349DULL, 
            0x45F1529EAE89C9C9ULL, 0x1B06D0AEF9291898ULL, 0xCA7839E632990A83ULL, 0x78746052D9B884A0ULL, 
            0x96CDDEBFFBAE3320ULL, 0x85A7D0B6E1485D66ULL, 0x98A3C5D46BC634BFULL, 0x545C2E13EE62BF9BULL
        },
        {
            0x21457EE063A2D3BDULL, 0x21DF2FB85E963F81ULL, 0x6D65929DCF7187EAULL, 0x52F0CC10CCA24CAEULL, 
            0x14AFD2361322A579ULL, 0xEAD7293C87FF098DULL, 0x9783D99F8CBA4C55ULL, 0x741C74435B037A1EULL, 
            0x1BDC715CCC68B09CULL, 0x8138D16EE20CFDBAULL, 0x24C7EAE9406721DAULL, 0xB69554D334D91010ULL, 
            0xFB84D32CC01676D8ULL, 0x6ACE1E94FA17A6E1ULL, 0x4E4CD75D6D4121C0ULL, 0x52B39FA143CDB5C1ULL, 
            0xA498431FA5093A96ULL, 0x2DB26EDEDBA07288ULL, 0x2097614A8E628ED6ULL, 0x9B207352BDDDC135ULL, 
            0x2844F95B84C12500ULL, 0x19C245496B35AC13ULL, 0xDB88F906B021C40FULL, 0xC28BAC81D8B9BC29ULL, 
            0xA4F56130664F044EULL, 0xABAAAC9BB8A6F3DBULL, 0x3A5A1D656FA31A50ULL, 0x9EE7FB064F31A4B1ULL, 
            0x8AF5BA547731E936ULL, 0x0A93E1142EF38335ULL, 0xE741FFBAD4B6E327ULL, 0x04FF61ECFC983811ULL
        }
    },
    {
        {
            0x04C23995F6737A5DULL, 0xBA48EEB3C12713E8ULL, 0xBEDA7BE3229EB145ULL, 0x4F1E893227A3D518ULL, 
            0x745D1A5DC8C86399ULL, 0xB54D6C94E7D7A284ULL, 0x8A811A933F30D418ULL, 0x76C151137F6E01B3ULL, 
            0xB37284D3793B93E0ULL, 0x22DD3E829736B055ULL, 0x492DE5FBE8998EFCULL, 0x4EC40529314987E0ULL, 
            0x5EBA9E75D61C764EULL, 0x32E644D174ADD4C3ULL, 0x8E9511CF403DC01CULL, 0xDCEF6BECDEED837BULL, 
            0x270014E37B08B4A6ULL, 0x66B3440043033BDBULL, 0xCF3EB6335F572FA8ULL, 0xDA0072E284D3D9D7ULL, 
            0xC4DCDF1184AA6FC0ULL, 0x0877A903C06A4DC8ULL, 0x5B5BA371A0AD5574ULL, 0xC490898669B067D5ULL, 
            0x4BE84D755333A6F8ULL, 0x4C2FA27B2C639104ULL, 0x58DD48EBFC21886DULL, 0x3C74672BE6D7E254ULL, 
            0xEEAD1CB5545D5F22ULL, 0x9D64565851FA86A6ULL, 0x9ACA18DBF26C8ABFULL, 0x5AB9519DCC863065ULL
        },
        {
            0xC351649DF434E8D9ULL, 0xEECF2C2040F10551ULL, 0xC9EBDEB8002908F1ULL, 0xEE302F636AD28656ULL, 
            0x20BC2CC636D35A90ULL, 0x7B57C0AF9EB1D628ULL, 0x069B8EA5E166F3CDULL, 0x9FD116DFDC94F7CFULL, 
            0xF310B53641B0277BULL, 0x2CEB8C9D5A2AC814ULL, 0x464790CADB0FC435ULL, 0x73708111C601C9BCULL, 
            0xCBB5E26D9BAC9A51ULL, 0xF091B712EF38B65CULL, 0xD4125A59D191C22DULL, 0x760058C138D84ABDULL, 
            0x1DC4345C3C6B12CBULL, 0xFB39BC26D73B7721ULL, 0x7144B7539E27A220ULL, 0xF7215D92DB202352ULL, 
            0x902F17CC794519D8ULL, 0x917E0A61F5729FE8ULL, 0x1F7BC38717D99D6BULL, 0xDDB5972140AE5661ULL, 
            0xAA1CB8E8B1DEA650ULL, 0x0D9472D0BB347221ULL, 0x3996E80D95CDCFD0ULL, 0xEA94AD1E1CDC772BULL, 
            0x7411F36DBF5623C4ULL, 0x39246D4F1ADF08ACULL, 0x5E91171F98F02566ULL, 0x5D9BD3173D4A9A1EULL
        },
        {
            0x2E9F99E5D26D0E56ULL, 0xAA7B1D898D56EDAAULL, 0x8A30EBBCCC7E4D98ULL, 0x8C9299DE7DFAFE9FULL, 
            0x4D97719235191FC9ULL, 0x78C21F1D19850B7CULL, 0x78B83F0B4BBC4391ULL, 0xF040C1350906AFC8ULL, 
            0xDB3AAE69466B5BBDULL, 0x3647FB6BFB68D430ULL, 0xEBA3BC82369C96B6ULL, 0x3B6C923FE46FEC0EULL, 
            0x5E7638FA77AD2446ULL, 0x031894D0D67D9D83ULL, 0x71350B5FEFF5296FULL, 0xAC1F932DE1990254ULL, 
            0x52B656D074916EE3ULL, 0x6D7F334A47809E57ULL, 0x26BE98C9AC4D552BULL, 0x3F54E563AE0BCFB8ULL, 
            0x635E68FBA65658E7ULL, 0xB8098084C329ACB7ULL, 0x0F6CA3277920E6C7ULL, 0x13FEE4969A4D6AA2ULL, 
            0x6099B10802BA966DULL, 0x532BED513227FB9DULL, 0x8DFF7B4B40E50697ULL, 0x1B7493D66B92B09EULL, 
            0xDA43F12E3EB09054ULL, 0x26E604286857FA35ULL, 0x27667AF38163DDFFULL, 0x30379F586042A5A5ULL
        },
        {
            0x3F872126253374C5ULL, 0xCFD5346C82AC7462ULL, 0xC79E20AE08CBDF1DULL, 0x8C0909DE61E592DAULL, 
            0x884E887C3343C597ULL, 0x2D40DB898CB38A93ULL, 0xF25DE8DAEB7D925BULL, 0x73B28E1E7B00B5FCULL, 
            0x71810CA0042BEFB3ULL, 0x882578256C777189ULL, 0x2358B07AC857C8A5ULL, 0xAE8FFED0DB8C86C1ULL, 
            0x51AA89297E79B829ULL, 0xB2984637F8A2C8ABULL, 0x1E3FAEF35DC29C62ULL, 0xBE38B20B95E89F68ULL, 
            0xFE5057499CAC5585ULL, 0xB977E6008CF4DDB3ULL, 0x69D789AB0042D69CULL, 0xB82B8DFEFB39264FULL, 
            0x3296AD28A02D2C6CULL, 0x097B384410BAF3D3ULL, 0x50D7F63663A722D1ULL, 0x891E8C7BE7B8E4E7ULL, 
            0x1983EA27A10B19D4ULL, 0x14B184D02CE5F64EULL, 0x0550A7AAA2AA24CEULL, 0xEF6E253E31460645ULL, 
            0x5EF71843A3596E0AULL, 0xC2AB467A3E7061DAULL, 0xDFED29A8A104074BULL, 0xA9FE37E3E54C9FABULL
        },
        {
            0x062DF32E2F21535CULL, 0x438B3042E2A79EA5ULL, 0x770E7AC82D4F07DDULL, 0x68B44614DF260760ULL, 
            0xDB36FAAD414A7669ULL, 0x3B204F7194805154ULL, 0xFF2F7F71883F2D43ULL, 0x88A23432B7D3C76AULL, 
            0xDEAB2162301078DDULL, 0x7B6F0254CE3C57A0ULL, 0x7B8672B51D1A4BD2ULL, 0xFB610571A7CF92E5ULL, 
            0xB2AF3C27B8301BA7ULL, 0x4CAC99D5DD788E50ULL, 0x4EF2377C464636B8ULL, 0x6144377AD4C99C3BULL, 
            0x305ABF1D39C3E594ULL, 0x87ADCAA74DCCE081ULL, 0x007D85A90260A646ULL, 0xA37D287104D0E4BFULL, 
            0xF73045894D0CF772ULL, 0xFDE5AF57A274D7F3ULL, 0x31A7A7C3B83D4629ULL, 0x415A351950021F52ULL, 
            0x24A6E83FE20FFF9BULL, 0x4A6F07F9E265D904ULL, 0x09057F1DBEAA56A7ULL, 0x645E9430BD401564ULL, 
            0x36897BD0885F10EAULL, 0xCE4297539BCBC336ULL, 0xDBFCE2BFD45B6A23ULL, 0x8F9CD0ECB4997C17ULL
        },
        {
            0xFF3A316CE8113B3DULL, 0xCF082BCB10ECDECDULL, 0x47D3B280F06F6C43ULL, 0x05C30081B6546063ULL, 
            0x851EC0D24ACC21E8ULL, 0x11C62B607912826DULL, 0x838144571B87E728ULL, 0x611E58575BE34F72ULL, 
            0x66F0070DA1740CCAULL, 0xE2037790D8012794ULL, 0x4C47EDBFD0CC6FA5ULL, 0x70EB4B24B0F54D9BULL, 
            0xA855D8FEFC6E6690ULL, 0x9C20BA9B89FB2AC4ULL, 0x31F5B0A615071D6DULL, 0xCD20B37F4FFF73D7ULL, 
            0x7127654EC3CE4F15ULL, 0xB042B5D860738096ULL, 0xA5BD0B128FA507DCULL, 0xFBE092155631E95AULL, 
            0xB53759D8EA404F68ULL, 0x4450A22C3154C261ULL, 0x55BD00FEF55C0784ULL, 0xC55CB6F04ACE8782ULL, 
            0x903E18D020B8F1CAULL, 0x090EDD4520869DF8ULL, 0xEB504E6BC932BA0DULL, 0x3C5F01ECBA7DDAA0ULL, 
            0x9AF8131E5E04134CULL, 0x0743471A52C0D8E5ULL, 0x9815E5E56A6A49D3ULL, 0x110090E43B42AA3FULL
        }
    },
    {
        {
            0x8C3BCD7229AB3F2CULL, 0x63E0526669964D2DULL, 0x10A87C1F23B26EC9ULL, 0x09C7FC87E5D3EF52ULL, 
            0x8513DA775AEA394BULL, 0x8E62CEE052F9F7E6ULL, 0xD4845769D6CE7CDFULL, 0xEDDCC9F582298756ULL, 
            0x5F381428992E7B71ULL, 0xC3DFD323983FDC1AULL, 0xBDE55AB68E3ECF8AULL, 0x35686D19D803E8F4ULL, 
            0xE36FC4D9E524DD95ULL, 0x956F99DA1F96C2FEULL, 0xE9894A4CA410F22EULL, 0xCDC8C29EFE8AC747ULL, 
            0x536D3C51CFA2B159ULL, 0x96AA4514C30DD25BULL, 0x217CCFD881085C4FULL, 0x2C826A9F2ACF1E3BULL, 
            0x1F1AA3142D717481ULL, 0x51570B74FD899BEEULL, 0x37FEDB51C85922ADULL, 0xCBBDA5C0EF5EC2FFULL, 
            0x04F09FA9B4C1C8F9ULL, 0xBB994EEB4432862DULL, 0x221F25A60FB453AAULL, 0x06886595BDFFDB42ULL, 
            0xD0DFE24E44DE93F2ULL, 0xAA2C14142895CC27ULL, 0x3C621E28C834E338ULL, 0x3F381FB4325F4022ULL
        },
        {
            0xA7D396FFD6D9822BULL, 0x90C946C94CDAA980ULL, 0x255E830455F61618ULL, 0x02883BD828ABDEB4ULL, 
            0x21768AA95FD89418ULL, 0x2A926DDD16388529ULL, 0xA8FA766964C5EEBDULL, 0x4AD62732B91A1C05ULL, 
            0x2DF4067D9DFD3F98ULL, 0xE228A53D565B2CFCULL, 0x197946126823C43EULL, 0x567CE705BFD0E13BULL, 
            0x1EBDCE6C9B612A53ULL, 0x97AF93E79AE25685ULL, 0x8F983C5FCE223F47ULL, 0xC2EB08BB1CB8715AULL, 
            0xB62A50DE728A8DC9ULL, 0xE3EE7E2AB791CCCCULL, 0x8E900839315FE08DULL, 0x6AC2315D1DCB943BULL, 
            0x248BDFE2065D3573ULL, 0x0C8A24FFE2B4C359ULL, 0xD1291DC8D02D26B6ULL, 0xB1EF904A2B701C44ULL, 
            0x7A404DC8BFB408DDULL, 0xB5C88FA74D6BA8C5ULL, 0x4457A6FFB21F5657ULL, 0xC18B2B86A50629BBULL, 
            0x921C503A4CE950B6ULL, 0xECD5DCAA3D2F0406ULL, 0x93E7C8316ABBA9B1ULL, 0x8AE1498CC05F5185ULL
        },
        {
            0x5274F1C3792135A2ULL, 0x32ED69DD5E98850CULL, 0x53BC6DDBE8680BA7ULL, 0x3E839294056D8904ULL, 
            0x302C43401FE37389ULL, 0xFA38F3A11EA7A3E3ULL, 0x9831BED073D107FAULL, 0xA3CC65C547F906E7ULL, 
            0xC7E56175234E7032ULL, 0x82AFCA14B87A49BAULL, 0x5697A37ADA3D319CULL, 0xF4BB6E35DB3B7EFCULL, 
            0x57D4D8C05A8E1193ULL, 0xDA52A2E916A9D9CDULL, 0xEEAC86EBADEEFBD9ULL, 0x51FCF69AD4FF746CULL, 
            0x7146C2D1B44ED80DULL, 0xD0E8E0799CC6EE08ULL, 0x3E093C7D4ADA8282ULL, 0xD769016587D7938AULL, 
            0xEE4D93C0261D9912ULL, 0xEEC58FFE83AA8EA7ULL, 0xC804081EA83B6220ULL, 0x3159AE96F75F6CA0ULL, 
            0xF4E3808A4D421BCDULL, 0xE225BA65EA0A67E0ULL, 0xC30005D79705F6C7ULL, 0xD03128E2CB854A0AULL, 
            0x32C5FDEB6F9ED89AULL, 0x9DDCEEC6A16DD3B4ULL, 0x0E05A482119BB625ULL, 0x0999C3970A1A9B65ULL
        },
        {
            0xA9B2F856C83DC3D6ULL, 0xB1ECA754AB5B0663ULL, 0xFAABA5B4983E8C85ULL, 0x08C6EA58C84ED974ULL, 
            0xC44C8D3C3C74A580ULL, 0x2E4B7E3C65416192ULL, 0xDB8D417F26DF3370ULL, 0xBC6DCE11E6F91926ULL, 
            0xC42AD308F9EE01FEULL, 0x40693AFA221EE0B3ULL, 0x08EE376F3FFF4165ULL, 0x3A3E2C305D9530E1ULL, 
            0x14537E933FCA56C5ULL, 0x782099FC1B6DF62FULL, 0x6FA666C793BC80B8ULL, 0x06AAC7BECB6D415EULL, 
            0x6722C9D1548C0AD4ULL, 0xCAA13F4F30225EC4ULL, 0x7850988B5E81E60CULL, 0x2CAB282533FF979BULL, 
            0x1AF6E2668B3E9413ULL, 0x7DA114256759D911ULL, 0x5EF5B2DD825FD0BCULL, 0xAB4DE3ACB174B206ULL, 
            0x29061AAB6347DA11ULL, 0x34C7FBFA635662E7ULL, 0x8E118492068C258EULL, 0xC1DA45B0255EC7F5ULL, 
            0xE316BD26BE804380ULL, 0xAEA2DD7963A3E3FFULL, 0xCD797CCC3082F5F3ULL, 0xA8BF9EE718242365ULL
        },
        {
            0x559699E9FAEF8D59ULL, 0xBF041FEE2FD628DFULL, 0xE82FFD2F6F831DDCULL, 0x11AF5539DB4DE644ULL, 
            0x2523902AA0BE9DBAULL, 0x3C9DD931F28829E0ULL, 0x6F8AF90B314907C0ULL, 0x0321233F80C61823ULL, 
            0x8E9CED1393E9377CULL, 0x2F42C20D3F610E93ULL, 0xABBC19E6AAE26B16ULL, 0x2A3DFCC399CC4223ULL, 
            0xE9894DF07B5DB91AULL, 0x211F055391F94E4CULL, 0x9FA9A9D56EB5A2C5ULL, 0x7779B4D142CFAF5BULL, 
            0x7EC13B878B6BD67FULL, 0x9FEBF625C071823DULL, 0x6C5BBB018CDABDB0ULL, 0x2F35B80A08FBF581ULL, 
            0xA2FF911BE87A130CULL, 0xBD9C9ECC6B59E588ULL, 0x0B68FEABB28EB54BULL, 0x0EEEE69D2FA85FBAULL, 
            0xF361F0FB3E8B00F7ULL, 0x52C57E0808772100ULL, 0x4332D2C66E3D212EULL, 0xEC396F20D9C42709ULL, 
            0x73337F6FA5466E81ULL, 0x361A1F94863DD07CULL, 0xC915C5D41F9D47C9ULL, 0xD835EEA14E191886ULL
        },
        {
            0xD2973AFA980DACF4ULL, 0xADE75CC81E5D6637ULL, 0x21D2E396A72FFF8CULL, 0x435BF437B25677D6ULL, 
            0x83D2899618BF5977ULL, 0x4E98FC0DB5347D55ULL, 0xFB786155EB28A71DULL, 0xAF3FC2200D9817EAULL, 
            0xCEEA9C23EE2C0BB0ULL, 0xD4BB43F231335246ULL, 0xB30BA7434EFA8B71ULL, 0xA24A497938FD18EFULL, 
            0xAA2FCA0608BEAF64ULL, 0x6C09B6463B4F06B6ULL, 0xF4ACDC6595F278DBULL, 0x3179A18720D81B15ULL, 
            0x53239F86DC99204DULL, 0x9BEE61E264F6B3CBULL, 0x21AA4FA77FF18099ULL, 0xD0F69338DE1FC7C5ULL, 
            0x94BA3FAC1683CF22ULL, 0x8AE0B807066ECF32ULL, 0xDBB3ACDF8C895ACCULL, 0xD602540B75331A59ULL, 
            0x9DE40897BA54ECAEULL, 0x0E3CD30685C648D6ULL, 0x0DC51FE032471479ULL, 0xE5D651D3F833D51BULL, 
            0xCC5951B4A3700EF5ULL, 0x4DDDFAF9810DA914ULL, 0xCC2CCE37CE8F28EFULL, 0x658032749682FCF3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseBConstants = {
    0xF488BE1CD51F86C8ULL,
    0xEA8E73C132B806ACULL,
    0x27434EC7F8003A09ULL,
    0xF488BE1CD51F86C8ULL,
    0xEA8E73C132B806ACULL,
    0x27434EC7F8003A09ULL,
    0x545E001FCAEEB58DULL,
    0xB719420E5513AF71ULL,
    0x6F,
    0xBC,
    0x8A,
    0x33,
    0x33,
    0x93,
    0x2C,
    0xD9
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseCSalts = {
    {
        {
            0x32FFB664A2ECBD6EULL, 0x4DA40B11F30A7168ULL, 0x7CF21AEAE83C743BULL, 0xCA05952CC5669269ULL, 
            0x19DA1CAF1EFBDF5CULL, 0xC2EFBBA60974DCB5ULL, 0xB972FB30EBC9B66CULL, 0xC159EE2A5BB20C2BULL, 
            0xAD32A62437609AFAULL, 0x5EB65710913B7C4FULL, 0xE1516DA98C64214FULL, 0xC582BA8595B884A2ULL, 
            0x7379E380AFA37807ULL, 0x4613C9B5076E81E2ULL, 0xE5EF91020230A993ULL, 0x94E7D2467B19F3EFULL, 
            0x696B35A3005B9D13ULL, 0x0D6405DE022E1D76ULL, 0x9C40D4CB5C41530DULL, 0x8640DB6C273C3756ULL, 
            0xF9D0863CEA1288C5ULL, 0x2A1AF5A8565D56BAULL, 0xBF35C911588AA31FULL, 0xD4357112BEB8FC37ULL, 
            0xD8FC2E0CA318DDFCULL, 0x1F7D2D133E738B93ULL, 0xC44C84FD07B2CD40ULL, 0x97605D25E7EA858EULL, 
            0xC14F117A35245054ULL, 0x3A7315EB4147B877ULL, 0xDC2A0261B0252C09ULL, 0x831DE5DDBE1903B8ULL
        },
        {
            0x5CCE8CFB952B38D4ULL, 0xDF7B2200B0F2971AULL, 0x47681A546ABE00D1ULL, 0x1D6A703BCF14CEF0ULL, 
            0x10240BF54AAADC80ULL, 0xC99F3E14408BC8F0ULL, 0x7FC96F027628DC25ULL, 0x4BAF2728C768AD14ULL, 
            0xF2EB99CB679D8214ULL, 0xB0F9161F06C7C254ULL, 0x46C2B4CC6225103EULL, 0xDB7D2CE6FB3296FEULL, 
            0x9077D0FD198049EBULL, 0x2D11D744614C4670ULL, 0x8EBEA53F19EF4C19ULL, 0x5658AD4A4AD53C1AULL, 
            0xBD1BF8E5C74600EEULL, 0xBF7E9BE9121AFDCBULL, 0xD38BAE5AA1A7CC38ULL, 0x7846A8FAC51EAE32ULL, 
            0x266E3919D45BE6A8ULL, 0x5ED056ACFF1C459AULL, 0x83A2CA7F1BDC35BDULL, 0x750BB0945525C155ULL, 
            0xFDE13DC7E353E824ULL, 0x7752D8ED6DC8CE46ULL, 0xF58F84C220817930ULL, 0x496B803BFCDAC409ULL, 
            0x35F3C38FBC4D0684ULL, 0x4C95FE615E704507ULL, 0xBF98523B475A9056ULL, 0x732B0937A8B19B59ULL
        },
        {
            0xCBFF9EA5C67C4763ULL, 0x5711F94C74762233ULL, 0xFE2F8DF6A12AB7DEULL, 0x3F475F96A69AC9FBULL, 
            0x63B4E4F33B1C8948ULL, 0xCA59991293B4CB79ULL, 0x77F5460ECC927B0AULL, 0xB09A5C20B4DCA52FULL, 
            0x3A95A2E71A759944ULL, 0x704E9056D6B0790DULL, 0xA0670C5C26BFB10AULL, 0xF2056D548C02DA15ULL, 
            0xFA4D57861E4D875BULL, 0xDE3619928C9FF9E4ULL, 0x4DABAB8582BF7834ULL, 0x82B1C77721097CAEULL, 
            0x04961BF671783CF4ULL, 0xEAB947D14BC11C8CULL, 0x119D0FAC93AC1186ULL, 0x96FF5DFE087A106FULL, 
            0x9C7BC120D30EC966ULL, 0xF9B61319B5A445B8ULL, 0x9A2803E12A377662ULL, 0x9CCD9F780016B82CULL, 
            0x9F4FC19B22503B78ULL, 0x34348F851739D646ULL, 0xFB887F4229057D71ULL, 0x8C6E16461D6469DAULL, 
            0x180FAD43525A20B7ULL, 0x80F414771EF39C15ULL, 0x6B4DB048950D6187ULL, 0x9FC7748277598180ULL
        },
        {
            0x3F126537426D32BDULL, 0x898A2F00C480D129ULL, 0xC3847FD703B7A313ULL, 0x725806F80CD623DAULL, 
            0xB4570A181A8A7E3AULL, 0x912FD1ED77741DA6ULL, 0x528FF9FA7F81DE79ULL, 0x9A19CD077D3E784FULL, 
            0x3DECF3F54FFEF355ULL, 0x5C59CA0514D522E5ULL, 0x01A757F790467E44ULL, 0xAE05D85119FC2C3FULL, 
            0x9E5D9D1E661BC5FFULL, 0x460C9AB21954C803ULL, 0xDA58A66BAA0493FAULL, 0x9A8A3453743A39C8ULL, 
            0x70676EE2DC1AA888ULL, 0xBEE60A6BCFB4D156ULL, 0xC8ED826DA1622CC2ULL, 0x83D1F6AE823A6CFEULL, 
            0xB86E0B9711ABD81AULL, 0xB87BB4F21F0BB439ULL, 0xA57A927055E5FA56ULL, 0x001CBFB78289BD1FULL, 
            0x150BAE00D3D701ECULL, 0x20BC25D608C3077FULL, 0xA834E8BD918FEF12ULL, 0x73246325E2E95C22ULL, 
            0xA9C10F3048510755ULL, 0x3B81ADC59E8DFE6EULL, 0xB8060C3BEA64735BULL, 0x76E8A89463E51266ULL
        },
        {
            0xC61AC06D16DC81B3ULL, 0xE6EA6CE170545BF4ULL, 0x52D12CEE5A4A1DB5ULL, 0x38BEBE22C6C734EFULL, 
            0xC9E06F3B0E53069CULL, 0x335E1853FCEA24E4ULL, 0x3CD0C4CEC3F46B5BULL, 0x014626CC2C3EBCD1ULL, 
            0x28F8A8F23B055A51ULL, 0x2BDFF4CEC7665A94ULL, 0x5673E57357290ACEULL, 0x6D6D083AF6022ED5ULL, 
            0xB55B5648BD167E79ULL, 0x2922A9634978DE0DULL, 0x22B465808299E145ULL, 0x1D4BFF021F3B4560ULL, 
            0x06D209D9BCFA070EULL, 0x9CDD862CC40FDF42ULL, 0xC1C42F1323FB7F26ULL, 0x5ADB503880B32A7CULL, 
            0x3EF11519F769463DULL, 0x37805DA5FA3CF56DULL, 0x33C4B8BBDF029E0FULL, 0xBC40881A5057706CULL, 
            0x4B3DC947E49D8B19ULL, 0x8796C2F71A71F00CULL, 0xAE9E45D37BBFDAA2ULL, 0x1F9C75FEC35E3352ULL, 
            0xC2CD43967B6F6D82ULL, 0x4914DAED0FB81477ULL, 0x32789CFAEF5D517AULL, 0x9ADA9A4BEBB809BCULL
        },
        {
            0x75E3C9D53408721FULL, 0xC262ABD19C9ED7B8ULL, 0xFFEB2511983C8D8BULL, 0x917D5DE8BBDEF5FAULL, 
            0x88800AF0F079CEFDULL, 0x57CDF918755F38D3ULL, 0xE93A3BC2320D3703ULL, 0x826AE62E6A654364ULL, 
            0xF50693F480004EAFULL, 0xEC254997A7623733ULL, 0x669526D8A14C2AEAULL, 0x51DF8C3F46C167B7ULL, 
            0xBC345AB42C4CB0B2ULL, 0x1C14B7F55A8C2486ULL, 0xB9C0A487FC55B0D5ULL, 0x7799395776A47984ULL, 
            0xD438C7FA3A7FD39EULL, 0xD4042588A85CC5A0ULL, 0xB4CED0BA312E2D9AULL, 0x3CC58B86959E0470ULL, 
            0x339B98DC2D48FBF7ULL, 0x82ED50629C74D38BULL, 0x547AD7A4A6676B0EULL, 0x37C31D436B66E6E5ULL, 
            0xB0413ABB7AD4BBD9ULL, 0xA886D13E2AECC427ULL, 0xBE1DDA56149E330CULL, 0xE4577439A583BAF3ULL, 
            0x135CF3F5B543F17BULL, 0x2B5F88187AF43AA2ULL, 0x1AB17D10DE787285ULL, 0x61F0362833B84023ULL
        }
    },
    {
        {
            0x1232119EE7C29A7BULL, 0x8504ED05B07418ECULL, 0x020FAFB66A9D581CULL, 0xA3CF174FCB2BDA15ULL, 
            0x87B508D585B4336BULL, 0x9A9B265C1D5241AFULL, 0x496295A386C867EAULL, 0xEC60C65C4C69BAFDULL, 
            0x2B2377128294A7E0ULL, 0xDAD324486978884BULL, 0x47F302AE1B6E86EFULL, 0xD2391D901B9E1BD9ULL, 
            0xF1F9858A2D2C5E89ULL, 0x23A6766BB41DFEEFULL, 0x762D54ED9EA4FD0FULL, 0xCE57EA187E11D66FULL, 
            0x455C63B417EEC960ULL, 0x2F26DC40D1BE385BULL, 0x9467B72DB6AC1405ULL, 0x877CF0EA868B55FFULL, 
            0xE15E339B972CF1BCULL, 0x500FD6D05177641BULL, 0x766D36231400F4F9ULL, 0x9FDF17B294BAB807ULL, 
            0x7DAB65C8C0DBD29DULL, 0xCD3D1E6E5AFFFEA3ULL, 0x9D42EE8CD4DD0B80ULL, 0x12608A50A577CC62ULL, 
            0x3F39A6BA25399693ULL, 0x74A0E9E7203882EBULL, 0x9E498197B7AE934BULL, 0x4420C1623B9287B2ULL
        },
        {
            0xE37B958BFF0048D1ULL, 0xA42FA8045DAE6DD8ULL, 0x1E1D7D92E1707F6CULL, 0x196C0C373701356DULL, 
            0x850FBF486ED54AAEULL, 0xFAB54A509E317693ULL, 0x44853D2B6EACD158ULL, 0xE18FB0D9F5C46DCCULL, 
            0xAEF1747F336DFC44ULL, 0x6E6C1790BF2252DFULL, 0xD999DBAD00BF0757ULL, 0x550A920C6264844DULL, 
            0x1750EBC2A7BE68C6ULL, 0xB101D21565A85061ULL, 0x87DD0CE8B5D5C9B5ULL, 0x0831D7328D104D4CULL, 
            0xB95FEF4FC9EF1D66ULL, 0xA45F3ADEDC96B443ULL, 0xE780B7A71E0F3FA6ULL, 0x20661B9883F9FDC2ULL, 
            0x877ADD5DE60F6E63ULL, 0xD10869C88170C450ULL, 0x11EA575645996869ULL, 0x8A57E1FF2AD2E542ULL, 
            0x5AEF191C18A30538ULL, 0xFBA1A8D9AE66C566ULL, 0x63AF2A0FC9B5E108ULL, 0x7233831FBFBC9504ULL, 
            0xBBEA3B4090EF4938ULL, 0xDC031E8DE76CB4EEULL, 0x8232928B8E613B4BULL, 0x9DA27A4DDA05BD4DULL
        },
        {
            0x92840EE005AF234CULL, 0x92F8BF89B2F5FFBFULL, 0x2B4F8CCA48F8BD74ULL, 0x1CF2AE7523111D1CULL, 
            0x889E3A2634680F1AULL, 0x60739A436AEA3851ULL, 0x9B429AF57369D2E8ULL, 0x7A5DEC5756A680B9ULL, 
            0x142DF2E42A0B47AAULL, 0x79E43B58CD4DB011ULL, 0x9263D89B7FCDA7D4ULL, 0xB687BD17843CFD4CULL, 
            0x4A312FE99950C3CCULL, 0xBF086A0BE8B08130ULL, 0x6FFD4689DAA3F9CEULL, 0xB5B67FE2381BBB2AULL, 
            0xF6CD6EFF40831930ULL, 0x81626B01462CA65AULL, 0xE59752C4D1584970ULL, 0xEDB84AD584083CD7ULL, 
            0x2A47E84C9F3CC750ULL, 0x290DB7ED2A3A4F1BULL, 0x6118DA33CF52426DULL, 0x7504FD78525A2ECBULL, 
            0x623A13695FBFC475ULL, 0xD7B121043DA3187BULL, 0x6392116C78C0AD27ULL, 0xF6AD6D9E1A8E42B5ULL, 
            0xC2E73BF0A1562FD1ULL, 0x120D3E99244F7E7AULL, 0xF7A8C7D65F04A5EFULL, 0xA7A760D27483704FULL
        },
        {
            0xB276EF2D912F9CCEULL, 0x4FC0D70DA5D8C0EFULL, 0x9690C5B798A49672ULL, 0x5A19556DFF06BA4DULL, 
            0xE5E44ACBA6DEA420ULL, 0x102F8457A66B2CB4ULL, 0x16DFF58AA2DEF6F8ULL, 0x451309BB66A33043ULL, 
            0x0F018A1FE04F60AAULL, 0x9A3814A9C5F12626ULL, 0xF5910E84E3932221ULL, 0xBD27C4FE688C3016ULL, 
            0xADC4DC28ED2F94B1ULL, 0x9F005DAAC3390F5FULL, 0xD17D871BC1D70738ULL, 0x935D5E545736AB71ULL, 
            0x40208BEEE6BDAAACULL, 0x4DCF534B5F72781EULL, 0x3039157E2897AB0AULL, 0xA1BD19CC20A45290ULL, 
            0x57EE92A8C34BCE60ULL, 0x08EF2ED714B16A45ULL, 0xD30E343108A3C841ULL, 0x88678A1737F35D26ULL, 
            0xD2E437F315D906B6ULL, 0x2126F4DE998053ACULL, 0x7E8416AB1BF8332CULL, 0x1E94B89492291275ULL, 
            0xCCF58A6626A2AB35ULL, 0x68CD517C8C7FEFB1ULL, 0x50A866F0510BE192ULL, 0x78D6365C54413ECDULL
        },
        {
            0x14F5A05A5B346ABCULL, 0xD0835F237F1809A6ULL, 0x484B21998FF1F47CULL, 0xC174568E7C3521BFULL, 
            0x83736982F5337264ULL, 0x26DBD8BDC1EE6EE6ULL, 0x8F089D374E29AF25ULL, 0x68D5875A01CB426AULL, 
            0x5A3B6EB01B899676ULL, 0x3700C098E34EB1DDULL, 0xFA4F247002D453D2ULL, 0x9EC3D428C1842F9AULL, 
            0x258794C73F8689C6ULL, 0x3106A7C4876ED880ULL, 0xDAFFAD4B875F5057ULL, 0xD14F68BCE6AA9307ULL, 
            0x0D62BCD9AF9629DEULL, 0x20B4EDEAA8A1C3B1ULL, 0x4E8DA76F6EC633E1ULL, 0xB273A07843C7E405ULL, 
            0x47D94D4F2177C693ULL, 0x158C6ACD925AEB49ULL, 0xD7D0E0D61F76473FULL, 0x91F0D64C0AE2D098ULL, 
            0xFB9D42B9CFAEB533ULL, 0x0AB5FD8B6B3E65BCULL, 0x0A9507078EB1F83CULL, 0x9BE83DEDBB890892ULL, 
            0xF4D72D057E53EA84ULL, 0x762FACEA1D92E194ULL, 0xD37D98765B9589CFULL, 0xE5DE77E76506FDB1ULL
        },
        {
            0x0AD2F9C9D7D39351ULL, 0x8FB7F308E70F6A29ULL, 0x34E41FC9FE8DD43AULL, 0xC4E69E65B98D904EULL, 
            0x81AF303EDC168B2EULL, 0xB6E108686E048658ULL, 0x9F9B3FC42EED12E3ULL, 0x26DEB53BDE43937DULL, 
            0x59B040933DC523D4ULL, 0x4D90775C25A5DCFBULL, 0x4348EDEBF46D3306ULL, 0x5874218692BB1A45ULL, 
            0x342B305E3D1E9F6DULL, 0x47EE871E1F3174F3ULL, 0xAD86AD12F17C205BULL, 0x678207794F2E1AB2ULL, 
            0x5EED9E8F6EAA51B1ULL, 0xA8DF5E25193F8A61ULL, 0x77CAFB4C0EB60C43ULL, 0xC8AD82284FAB14FAULL, 
            0xB552469392A811E1ULL, 0x1975BD806EF83C8BULL, 0x75B5F026EF3FDA82ULL, 0x5D90D3A079AF47F9ULL, 
            0xFC84774F8823D692ULL, 0x56EFBC6371671B85ULL, 0x40F89E5F2C368E6CULL, 0xE8B2534510D83283ULL, 
            0x76DC16B2A839CA83ULL, 0x41E0DCE90871F8B5ULL, 0x1F26B125D659A953ULL, 0xF73E09DB11A4F590ULL
        }
    },
    {
        {
            0x7B47E3020341C313ULL, 0xA0B8737C9085E397ULL, 0xF2ACBF675EA6F8B0ULL, 0x00246264716905C0ULL, 
            0xC7B8B7FBD714F92FULL, 0xFE4572BF6DA7394AULL, 0x42D5A5111E59E8A4ULL, 0x5ACC85EBF4195795ULL, 
            0xAE8593C33EDFB34DULL, 0x18C1EA848D03E8D2ULL, 0xF7B9F40B4AC6CB90ULL, 0xE92E5DFD6FF069EEULL, 
            0x9B1330FA930346E9ULL, 0x1CAA3E5BDC644CD3ULL, 0x061179FC05E8EFA6ULL, 0xCCFAEE6159DAD129ULL, 
            0x502D115FDBE49E34ULL, 0x56C6822CB8CCE401ULL, 0x3880C36D84668733ULL, 0xB64685636981DBCAULL, 
            0x6108A88F91C3D4B7ULL, 0x03658D31D997F087ULL, 0x759480C7A65BD501ULL, 0x4204AAE7A1687DE9ULL, 
            0xCC087800A1B28183ULL, 0x7E656BA898E89467ULL, 0x78161FA35C681630ULL, 0xAAEE7C57E238631CULL, 
            0xA4B81C1427704D9AULL, 0x0803E42579BEE835ULL, 0xBAA3AD5AF3CC88F4ULL, 0x866D2CDE58696604ULL
        },
        {
            0xBFC5150335BA8170ULL, 0x42DEE36EEFD3A81AULL, 0x9B8EEF27BADAD34DULL, 0xE9A9EC7528ABD048ULL, 
            0x2C0432662718E642ULL, 0x7009AF36FDC2B09CULL, 0x6A5C90CE1FF98D0EULL, 0x4077C44CF45BAE82ULL, 
            0xFCF7864B6C82683EULL, 0x1231449D0E699A45ULL, 0x74D4F169D930B110ULL, 0xB16C8F3D03FFF511ULL, 
            0x1BE3D8403FBCDB8DULL, 0x5DA16B1084F5A054ULL, 0x4B3A1FD7AF57DEFFULL, 0x6AAB452E816BE690ULL, 
            0xD05496D4F7C8DE1AULL, 0x2CA7CBB5EFDF756EULL, 0x8491D6BC97738EB1ULL, 0x2B67857A1641B91CULL, 
            0x0D2977266DACB463ULL, 0x8DF2354B28CBE433ULL, 0x2690A4F0FC24167DULL, 0x13EF57240AE5ECF2ULL, 
            0xC335EC71F40254E6ULL, 0x2F95556F47CDF3C2ULL, 0xB4D997FAFC78C899ULL, 0xFA25BDD8A9B83571ULL, 
            0xDB97287319B8E341ULL, 0xE8A3B75AD359F6AAULL, 0x45B39CB31506D9E1ULL, 0xC6E79D595465E68DULL
        },
        {
            0x974CAC393CF07BA4ULL, 0x51E818AAB3522CFBULL, 0x99DFDEB865605C5AULL, 0x6A171610D99D8270ULL, 
            0x5633DA924A41E1E1ULL, 0x9A6C054CFBECBA6CULL, 0xB14138D12A5FEE99ULL, 0xA798AEF08C0ED6FDULL, 
            0x1F9E79F23C2F5E82ULL, 0xA8450AEACDD50D13ULL, 0x4232DAE5DB74F8A3ULL, 0xC4A430BA451305D5ULL, 
            0xFF6756401C69F105ULL, 0x3B01E2E6AF176158ULL, 0x888C49488FBE0EA6ULL, 0xEDEAC83EA59EE255ULL, 
            0xACF2598ACEA03DACULL, 0x4103C4B52FF49208ULL, 0x6D53613EE53FDD8DULL, 0x9C68F25AFBC30A29ULL, 
            0x9FEB2227611EDF79ULL, 0x9AA12C424D4A6E59ULL, 0xC9407410DF3323ECULL, 0x8A212E85FBFAE714ULL, 
            0x28A7F15043C40810ULL, 0x178C24B7AC4EB5C4ULL, 0x001529BADCCFC61DULL, 0xA3079C613DBEAC03ULL, 
            0x69F234AFD8B14D0BULL, 0x4A89403F0BFE8D1BULL, 0x33803131AF7ED20EULL, 0x746654736AE5EA52ULL
        },
        {
            0x913EF629B22E391AULL, 0x659F886BE2C35ABCULL, 0x1CC80EE7AB23220CULL, 0x9A6B231E3FE1916CULL, 
            0x2ADBCEE72AF42913ULL, 0x5D9BD51CA7D8C1D9ULL, 0xC18EACBCEB5226E3ULL, 0x749C667FE4C67601ULL, 
            0xD0D3F44364226291ULL, 0xB3A3EE4BB9302AEDULL, 0x49E37EB9DA6AF461ULL, 0xFEC708F67ED51742ULL, 
            0xFCA65B898EBBF93DULL, 0x87FEDE4655586C90ULL, 0xAEF79ED41C953583ULL, 0x851025FD2AD39A7BULL, 
            0x09BDF86D08E764C6ULL, 0xED6D92868BE40757ULL, 0x4124112090E751DAULL, 0x21751088E5B87919ULL, 
            0xD9AFCE8E2EE8138EULL, 0x76C8B177600878A4ULL, 0xC109D11B2D59DF1CULL, 0x65E298182D3FD986ULL, 
            0x18B25C67427A3354ULL, 0x48767C535C78B6C5ULL, 0xB72B315F39E4B263ULL, 0x04430A675A863CFBULL, 
            0x1DA30EB451D136CAULL, 0x7D2ACCB2C2F428F1ULL, 0x19A55A48C44076F9ULL, 0x036D6A76B74A36B5ULL
        },
        {
            0x559D56CD1E3676DDULL, 0xE08DE13D27B08CDCULL, 0x1DDAECB6DDA9A4B5ULL, 0x702E8437D863CA23ULL, 
            0x3A9BC9AB9AA54519ULL, 0x5846B3CE15D35C96ULL, 0xD732EFB5B13F6288ULL, 0x09F043FB9F92416DULL, 
            0x211CED5FA34E6B2FULL, 0xE354DD5FF44A9316ULL, 0x5851ACB1F8D062E2ULL, 0x480351634C5E9CD9ULL, 
            0xC39BE941A69BCC0EULL, 0xE32CBC46EA04EB9DULL, 0x4759C04D388B2ADBULL, 0xB780E196CD654C58ULL, 
            0xF4A6B2D55ADF6955ULL, 0x6F1672E8E3D3F64CULL, 0x15AFCEA5A4005D56ULL, 0xC5113BE79C6E51B4ULL, 
            0x5FBAACDD944EFA4EULL, 0x93D4964978874EB3ULL, 0x2BABA987C8136D09ULL, 0x4B48011EC1BAB203ULL, 
            0x006D0AA5738AA360ULL, 0x192058E82581AFA7ULL, 0x7F6E4D87C7B4546CULL, 0x774500B427615FBBULL, 
            0x98249B104DA3E2D9ULL, 0x030AECC96D4949D4ULL, 0x32FB93ECFDA03FE6ULL, 0xB288380E834F3B1AULL
        },
        {
            0x0E6BA370C77FC788ULL, 0xF26681C0916D4B23ULL, 0x84A7DDF61D7E1376ULL, 0xCD7C8BA9A75F3453ULL, 
            0xB42D6AE0B03046C6ULL, 0x1FF2DB683368970EULL, 0xE18ECACF4DE5A1D2ULL, 0x451493C0AF3E85BFULL, 
            0x65EB86BD003EAF57ULL, 0xE3E5BF8751EF2037ULL, 0xF2C2F5296DBBECCBULL, 0x3B3ECEB9787C974DULL, 
            0x2AEBC19142964EE9ULL, 0xFA3D9D41A1581A6AULL, 0xF998E530E4EFEBEAULL, 0x501FC60EB7F388EFULL, 
            0x5AC02DFB5EBACCC3ULL, 0x1E6F5A31AA630C9BULL, 0x0F41BFA6FD22A43FULL, 0xE41E930AF490221AULL, 
            0xCA7C202175162DEAULL, 0xD4EC143C59639DA3ULL, 0xD36F1A869AEB0749ULL, 0x947BB9DA45E834DEULL, 
            0x4480B4326E470586ULL, 0x4C07665AFB2AA895ULL, 0xA1E579F950CD665AULL, 0x46993280F5F03A93ULL, 
            0x9E15C8E163C142A4ULL, 0x87073C404D0C9EC1ULL, 0xDCAD8D92A49E2669ULL, 0x4BD9BC3762B17D2DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseCConstants = {
    0xD6FFC382DD2DB1F1ULL,
    0x4C99F784C567D11EULL,
    0x1B85DCD6D1C8BA42ULL,
    0xD6FFC382DD2DB1F1ULL,
    0x4C99F784C567D11EULL,
    0x1B85DCD6D1C8BA42ULL,
    0x4EE99C81FB72FBB4ULL,
    0x45B8EF00D93CFF33ULL,
    0x53,
    0x0D,
    0x8A,
    0xBF,
    0x35,
    0xF4,
    0x1E,
    0x6E
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseDSalts = {
    {
        {
            0xD0241B1D5A4AF0CAULL, 0xAFA0ACDFD4420ADBULL, 0x84DC63C781EE9FBBULL, 0xC5B3D904A6C29201ULL, 
            0xE5CD9B8FBD6F74D5ULL, 0xCF80E751D4182A51ULL, 0x543AFCA483899288ULL, 0x4F06075F69AA43ECULL, 
            0x5850C8A0894D1420ULL, 0x8D1E768244433651ULL, 0x142B87E0BAF29689ULL, 0x7D600BB3A4B2530AULL, 
            0x1C91576FAE465787ULL, 0xAE19938433E9F2BFULL, 0xD4BA6C3C6DEC33D1ULL, 0x2C130438778115A3ULL, 
            0xE2B5DAEC34C66009ULL, 0xE2368D09948EF6CFULL, 0xE7C570A4922876F3ULL, 0xA5A94B585331E84DULL, 
            0xC41D82B5CAC8C73BULL, 0x1F75F438A5316723ULL, 0x8A24D150426A09AAULL, 0xC5407569DBE3F75DULL, 
            0x74EF57755A422875ULL, 0xA44255E83EA5307BULL, 0xAFCD1A0AC0B82726ULL, 0x90CF51824CA5A84FULL, 
            0xAAD9401CAFAFEEC9ULL, 0x7C730E248D3D41E9ULL, 0x83270562A25C4E3CULL, 0xEF6D47B31A6AF76EULL
        },
        {
            0xF8D369C4E5C54D7BULL, 0x22774F0350A1013FULL, 0x5096BCAD5D3B8F6AULL, 0x7983ECEEE84ABB46ULL, 
            0x48C03B8264E8338FULL, 0x12CC6B545CD2F6FDULL, 0xE854A9CF1AF97609ULL, 0x03DFD1AF87F63164ULL, 
            0xA4A70AAE522DAC66ULL, 0x1873D5B4E7A7D43AULL, 0xCEB0EFBA140A6E9AULL, 0xAB2C0611FA55BA59ULL, 
            0xAD301155D3EAEAB0ULL, 0xB8F63FC602C1E1ABULL, 0x87D5CE1A5740643CULL, 0x871D47E0481B694CULL, 
            0x4ECB33A1C84BA571ULL, 0xE09FBDA198B9A883ULL, 0x39BD00A23F0796F3ULL, 0xAE504EEE0C036CE1ULL, 
            0x3DB008407D885AD1ULL, 0x543246027F51E7CAULL, 0xD8426B40A0779DA0ULL, 0xEB2B40D82016369AULL, 
            0xCB0BC1241951093DULL, 0x0380C996822C8E44ULL, 0xD5439EACC1E630FDULL, 0xD5798011076D8DE1ULL, 
            0x1AD420AB21C9B400ULL, 0x1965ED8E56D63C50ULL, 0xB73E8AA50791960AULL, 0x0CF41238C98B8D57ULL
        },
        {
            0xF1B2677BCEE2F524ULL, 0x37C77B3F7121A09CULL, 0x16CDB883F7C4C951ULL, 0xD7CEC8BC0DF032EDULL, 
            0x4E5D0D95560ADDD3ULL, 0x32415A66BDEAD45EULL, 0x2BA94DBB91F8BC30ULL, 0xA0F0DB2112089F2EULL, 
            0x2360BED98021FD78ULL, 0x9531565453D77CABULL, 0x645BAA0BA4633C6FULL, 0xE3B36B0A71A29FBAULL, 
            0xA3E90565A95FF7B1ULL, 0xA26E17FC9348BCC3ULL, 0x1502AE89A75491D4ULL, 0x015D67F4568EDE26ULL, 
            0x254ADD00C3B5AB79ULL, 0xD145CF0E2A2C2B27ULL, 0x1048563C87EA33ADULL, 0x3AC35ADC49E1B7C7ULL, 
            0x05145BBDDED495FCULL, 0xAECF41C058D83D82ULL, 0x3C286F1E436DB3EBULL, 0x6A44DC360CC77532ULL, 
            0x625A4097F6C639DBULL, 0xF642C79AAA952D09ULL, 0x10C4D42CC5C97415ULL, 0x08F06D692F2AC7D7ULL, 
            0x2B106FD040E9A2F8ULL, 0x5F773F4DBD02287EULL, 0x3FA5F880812CF475ULL, 0x75E46C412B8FED59ULL
        },
        {
            0xAB2F0A97BC8E483DULL, 0xA719376E8A52163BULL, 0x9BDFC8FE91D729BBULL, 0x4E60FE1715AC2C74ULL, 
            0x1B1EDD2CED497DD8ULL, 0x7618A5D61FDA786CULL, 0x0E7F66836FAE2F81ULL, 0x5AFBE5A205FD249EULL, 
            0xE1AF3A8008F32AD3ULL, 0x7B2C892C849B0FDAULL, 0x8D53E24FBD500DACULL, 0x7A2EE15BCC6EA1C0ULL, 
            0x1EF0A0DAEBA2FE9FULL, 0x0B1EFF7232CEFC07ULL, 0x6DD3CCF1DED50552ULL, 0x588C9158CD99D99FULL, 
            0x916A18BA1A7DA52FULL, 0x6027748D60F9B918ULL, 0xAE8DAE81E214D305ULL, 0x830C65A432658C59ULL, 
            0x66F0FD83A4BD7CA6ULL, 0x603B21D20A2B452CULL, 0x1E50DD232E0769A2ULL, 0x3AE44F099FD91705ULL, 
            0xF6CAA73CFF506A7EULL, 0x400D94148D076F1FULL, 0x0364435373E37A92ULL, 0x4A8807DF712C3B57ULL, 
            0x65CB228836A0A5ABULL, 0x00746C770FBF9B69ULL, 0x4D965EEF46315B68ULL, 0xB914666F968EE7D6ULL
        },
        {
            0x3815FE81CE2714B3ULL, 0xFBDDDECF777214F8ULL, 0x0BA4794662664195ULL, 0x2617B5AC05E4604FULL, 
            0x49C6FD90DE5BD487ULL, 0x4D251DF7D2557793ULL, 0x578DE9E7384A2F82ULL, 0x55D97F3CE6B88C78ULL, 
            0x411552F2EC0C5C96ULL, 0x6A127329A17ABBE3ULL, 0x3617D1F971C17BB6ULL, 0x430A097B97DCE3A7ULL, 
            0x4D3EA12028BF595BULL, 0x0B9456FD4B080C35ULL, 0xA86455782D5B6B36ULL, 0xF33A1A9487FD607EULL, 
            0x46495D12DAA71872ULL, 0x66879F1E0980A5A3ULL, 0xDA73558A32E3EC13ULL, 0x2168706678EDAEC3ULL, 
            0x389A3EE0AF3DE910ULL, 0x296B62DAD609B000ULL, 0x1B070BBD904D8A6BULL, 0x475655640C13BF25ULL, 
            0x9D66C556057A844AULL, 0xD0CA5A650136168CULL, 0xF44EF36D5D238445ULL, 0x3140E7813CCD4889ULL, 
            0x0214D72801B5C60EULL, 0x21A4F6689DE14821ULL, 0x69F5EF65959F287BULL, 0xC7413643EC7297F4ULL
        },
        {
            0x5E83F497486AE6D9ULL, 0x9F5430D686FA1A0BULL, 0x7928E5B434484637ULL, 0x3D6F65AFE0339232ULL, 
            0x745429845E3F27DEULL, 0x1E5F834202F9E76CULL, 0xCD574D768CEE3EE4ULL, 0x7EC84F8211D7CAE5ULL, 
            0x1CFCD6458B2682A7ULL, 0xA7415F43CB956944ULL, 0x9BC422DDA0E4FF1FULL, 0x68E9EA8D8AA0EA23ULL, 
            0xDD776009852E6170ULL, 0x899DDFAEC3845076ULL, 0xC883B2930AFBAF66ULL, 0xC8FDB49F4C4ED891ULL, 
            0xCE65DB7272F0712DULL, 0xEB61E0A051F88AA9ULL, 0xE58B42DB2069FC04ULL, 0xF301826E7BDBDCC4ULL, 
            0x59ECB47FCEAD1A5BULL, 0x5BA884D6765659A5ULL, 0xDBC4439988A6A483ULL, 0xDD74412E39ED6A12ULL, 
            0xD6818EA373CE1035ULL, 0xD6F6258F521457D9ULL, 0x865BD801E1027562ULL, 0x4D14DF526827CDFEULL, 
            0xD689167B025B4EF2ULL, 0x0E4C559DA1288C91ULL, 0x9A26CAF3F6776A50ULL, 0x9C5D7188597474CCULL
        }
    },
    {
        {
            0xEF72929498962FC9ULL, 0xDC890E23691F418EULL, 0xC38A391EE37DE9C5ULL, 0x4B0507109F60DC28ULL, 
            0xECE05D795F94734AULL, 0xD28EBDF3873BE0FBULL, 0x986D347F80DBD6B6ULL, 0xFACFAADFCAA088FCULL, 
            0xD87C291638A78C57ULL, 0x9F3BC6682B6B69D7ULL, 0x07B22A250CCB3457ULL, 0x0F6421C9B33CCF25ULL, 
            0xBD39049678ED7C1AULL, 0x1080AA8C9B09D1BFULL, 0x0E7BAD392BDAB1ADULL, 0xD6774351F82ED4FFULL, 
            0x75A985EE8ED3BF5EULL, 0x93156EA92D47C8D9ULL, 0x131C202378544790ULL, 0x78C305C2200CD8F4ULL, 
            0x437B8B5581C17131ULL, 0x9FD2B60946831590ULL, 0x0A416FE971303654ULL, 0x93181C07D33382C8ULL, 
            0xC9E79F092808F642ULL, 0x0220DF3880495E0AULL, 0x337B0CA4BA7BDCA1ULL, 0x5427B81D87A51CCAULL, 
            0x0595E9BBB1E4C202ULL, 0xB80B015B52E7FADEULL, 0xDCB34A16AE6BF241ULL, 0x2BE679D3DDFA4C38ULL
        },
        {
            0x4E5A367802AE53AEULL, 0xBBECF497F2B0A6ECULL, 0xB38B25E9CEA65D1CULL, 0xE259F204F514E9C1ULL, 
            0xE94AEE1AB06550EFULL, 0x779EC931F323EBADULL, 0xE2C11E08CCAD7916ULL, 0x07CA125CBEA0BEAAULL, 
            0xF95649CFD0AA81A9ULL, 0x179A6A59BC59D7B8ULL, 0xE4C0C70CB29FE77DULL, 0x987DAC8F8486298AULL, 
            0x02076D7A0B0C148AULL, 0x6F81F23DD1905E5CULL, 0x42AC1461D776B599ULL, 0xB7EB8592BD660CD5ULL, 
            0x71B1B9B62E3801D5ULL, 0x431AE65ED17ADEBDULL, 0x7100466240E28835ULL, 0x16637B9EA3A7E0E8ULL, 
            0x4A43ED9E127CC4EAULL, 0xBDE3CFB466080B95ULL, 0x1151E5FC1F652F15ULL, 0x57EA83D99439D987ULL, 
            0x0A21B6A174B909EAULL, 0x3A7C04725035EB77ULL, 0x0174CC1225738994ULL, 0x7245AE56AB87A287ULL, 
            0xCA1382E0B0F848AAULL, 0x38C1B96289490B5AULL, 0x16F3D7658EE982F4ULL, 0x031A85F549CFDCD3ULL
        },
        {
            0x7A8CBCDF0EFCF37CULL, 0x2ADDB8457FDC1642ULL, 0x92FD411035C0E61EULL, 0xDDF4C819D5C53E06ULL, 
            0xCD0D5849ABC4740EULL, 0x4E2F53EB405E4959ULL, 0xC5F2075FF5275DD3ULL, 0x44172B5F9E6956B7ULL, 
            0xD152910B16902875ULL, 0xE76595E4C8F004FDULL, 0xF545AAD4E646EF69ULL, 0x42A2B55CE190E93FULL, 
            0x4B62B16ED73E342DULL, 0x5CD054A2A8DC1BECULL, 0x3B652063F235E61CULL, 0x94DE72949051DC88ULL, 
            0x84D89F7D20421E93ULL, 0x9A8A73EF6E96471EULL, 0xE773C63C08219989ULL, 0xC875BB33B7391808ULL, 
            0xF03F0F84161ECEA4ULL, 0xD3F5EC98B1406A1CULL, 0x268BC8942D3C04B2ULL, 0x84E3EFCE67C7943EULL, 
            0xF23F370791C22413ULL, 0xDFB0A33313865DB2ULL, 0xF32C1E9C8C60B717ULL, 0x4B3D08D78F743FB9ULL, 
            0x2AC4504A19F319CAULL, 0xBA3ED87E2C785D7BULL, 0xD9D621807977097EULL, 0x44484FC9281E0040ULL
        },
        {
            0xCC1512AD8CFB4CBEULL, 0x4123B15121BA9EDCULL, 0xC0A0E730F88C80D8ULL, 0x762486EC95E8E650ULL, 
            0x1C7A19C3A7D99AB0ULL, 0x4DEAD3E62E2B25D9ULL, 0x708E6C56C9602857ULL, 0x4811555F420367B6ULL, 
            0x9183173E3DFDDCC0ULL, 0x001074CE0F8C9D92ULL, 0x5A98FCD7DD2159DCULL, 0x59CE50179F65799AULL, 
            0x19176B0A418F663DULL, 0x0D92B6C512AFA2F6ULL, 0xDF03469647224149ULL, 0xC70C063A6DB8C1E1ULL, 
            0x5AF0670B43649621ULL, 0x148358E94E638D0EULL, 0x42FEFA6E0F63A669ULL, 0x0E33DEBE94112173ULL, 
            0x1CB79AB4B428B6FAULL, 0x0BCF6FC6D4E84F32ULL, 0x6B947B240032A73EULL, 0x4A23AB6CFDEE6B55ULL, 
            0x5329A2B97016A017ULL, 0xF210CE225C003358ULL, 0x1911C1D2BF03B2EAULL, 0x5058458A9D8ADEC1ULL, 
            0x450AB8001CD59CBFULL, 0xCF937C00338E13D7ULL, 0xD53704F645C910A7ULL, 0x53055A757057DE88ULL
        },
        {
            0x27CC4FDBC53807AEULL, 0x5468ED39D494E45AULL, 0x9E231A960271252DULL, 0xF1908CA8C689F288ULL, 
            0x3A4A0D5F5493ADCAULL, 0xE352EC8714365586ULL, 0xAEDB50EDB23F8BA8ULL, 0x7B474E9F74CACE73ULL, 
            0x6DCF40144845149CULL, 0xC33761911CB1621BULL, 0xDB58DE96D830A895ULL, 0x357292E8EFC8600FULL, 
            0xF210A61F9E0F44D7ULL, 0x707E4E61C5E59A89ULL, 0x10D8CF27C3579999ULL, 0xA23B164C8DC2D329ULL, 
            0x1F0CEC56F0522D08ULL, 0xE32DBCEF0FEAF48FULL, 0x192577B244A8E8C4ULL, 0x202539E772AA445CULL, 
            0x12C3728D3E10522DULL, 0x6409EE701EF4A5BEULL, 0x4BD3B4F177C5CE28ULL, 0x24342C3BDC836383ULL, 
            0x39AF56EA33E2CDF0ULL, 0x02EC07C148C91183ULL, 0x344E30965E602128ULL, 0xF332D406F7736856ULL, 
            0x04AC93F118AC1175ULL, 0x8A4DFFCA771B5383ULL, 0xA64478D8AFD84AEFULL, 0x644D0CE55F9D9CE5ULL
        },
        {
            0x15ED78C89942E519ULL, 0x6B9A9F380787F33DULL, 0x7FFE1B0DDFB27167ULL, 0xE3AB84707C514CE2ULL, 
            0xF846CA30EFA08B45ULL, 0xECF015CD69D0803FULL, 0x1FE556DAC510317BULL, 0x68C09D5243E2349AULL, 
            0xE3D118E1F29AB8B5ULL, 0xAC81180AE83A25C7ULL, 0x0130E20EF1ABFBB8ULL, 0xD24DA629762C3EF8ULL, 
            0xA94951F2605D8F3FULL, 0xDD84E33915CF6DB2ULL, 0x2FF1F57EB417DAFEULL, 0x72D09CEA8447B65AULL, 
            0xE267908FD2C3ACE4ULL, 0xCC8255469BFBA781ULL, 0xD6249C13A23EA69DULL, 0x1CE561199C532569ULL, 
            0x8E2F9D6D098FA350ULL, 0xB9BC4203321ED4CAULL, 0x86388A8E958344CDULL, 0x505CE5F66AF66A04ULL, 
            0xC327AB6A9972E0E7ULL, 0xB1F2A2D64E985F62ULL, 0xEE960E52C9139282ULL, 0xA7689794BBD776DFULL, 
            0xDB2D3282315942CDULL, 0xA6DB1E3B1A355F5AULL, 0x3C5D52482E554A2FULL, 0x8C3D022AB41A6802ULL
        }
    },
    {
        {
            0x762F7DCE3C05D49AULL, 0xF546F1F12342E7F4ULL, 0x682F6C304D5EAF80ULL, 0xAE757D78409FD403ULL, 
            0x1A0C3CE00F399C5AULL, 0x3F07662FA964FA82ULL, 0x5E649D678F17C346ULL, 0xBC7E237CE4D97651ULL, 
            0x44B32DA6FCCDFEB5ULL, 0x6A0AD46EE890AC3EULL, 0x7BDCB5B11AC97D61ULL, 0x98C52D35231E032EULL, 
            0x15B60EFB93E593EDULL, 0xC6181E7F7D4D4F07ULL, 0x240255C27257B9EAULL, 0x780E7628CFAD2D04ULL, 
            0xC4542D767A88243EULL, 0x5D4982B159554BA2ULL, 0xB9BD1B51756DF71AULL, 0x97E512B3D906A114ULL, 
            0xDB3A2CF0A29B0261ULL, 0x7CDE956968321DECULL, 0x709357AA3CD1574CULL, 0x8ECBE6E6E83C7639ULL, 
            0x2058775B5FC3E3C1ULL, 0xC1A4EA9E18A31032ULL, 0xAC3780F034F5E6A6ULL, 0xD796D287E670FC36ULL, 
            0xD2C6053927ED2506ULL, 0x6948A61A741BEB0CULL, 0x1CB7785EB2639AA8ULL, 0x6BFDBE89AEBA02EFULL
        },
        {
            0x5C5E8C8B70D0A131ULL, 0x65AB2515DC768F2BULL, 0x81E0B7414C8AA296ULL, 0x6BF6F14B3F80165CULL, 
            0xBEAF647EA84D7B15ULL, 0xE304853FB1F2310AULL, 0x610DFBC7ECEF44C8ULL, 0xDE92838EBEE78F9CULL, 
            0x56C9575FCF0D25DEULL, 0xC0D7D5BF1AE8713BULL, 0x0A00CE7D9A72B151ULL, 0x66973F419DD4B350ULL, 
            0x83BF5C11C439459EULL, 0xA3D4980DC9706E80ULL, 0x2847E2E7646035A2ULL, 0x93A938B6261D92ACULL, 
            0xBCE6D43AE12597A9ULL, 0x2140FC5F41E3C369ULL, 0x471A446BF46F50F3ULL, 0x8CC953249A1816FFULL, 
            0xA5F87F41496647CFULL, 0x3CFE1C4E060CCDAFULL, 0x38C4DB9EEC8139D2ULL, 0x6A189D4473F7B93DULL, 
            0x63A616B087B94314ULL, 0xF04999DD11D493BEULL, 0x025C76C82656AFC8ULL, 0x19FC913A04348EFEULL, 
            0xE5985D4EA18C403CULL, 0xE468431A08BCA2BFULL, 0xD8CEDA3230C3B373ULL, 0x6D51A465EF6506F1ULL
        },
        {
            0xD6F5ECBFC10FF180ULL, 0x0E21407586C5BD1BULL, 0xF8DC5C5CBFF65C48ULL, 0x81ECFCC7C2DC8AA3ULL, 
            0xFE95E9EBFEBBC7A0ULL, 0xF8F6FB1D09F5CE93ULL, 0xF68B490086AB408FULL, 0x616541B6A9275552ULL, 
            0x43A1832C267ADF16ULL, 0xFD14DCFB881681DAULL, 0x33252190859AF68EULL, 0x6994EC8AAC3C371FULL, 
            0x0771E9AB557E79F0ULL, 0xB3625D3454C113D4ULL, 0x7F72C4C5455ECE23ULL, 0x27B4D13219342A99ULL, 
            0x9748D9034BFDD5E9ULL, 0xF1798D786B96D4E1ULL, 0xEE4A0A2D779B00D6ULL, 0xC0E4EF928DC124EDULL, 
            0xFC2D071512A7090EULL, 0x2056ECE0351D7100ULL, 0x766C4099523AA98DULL, 0xB38FA73C1868B4FAULL, 
            0xF34AFC72232E0123ULL, 0x95F368565B4C5D4BULL, 0xC5CD596A1B41BC55ULL, 0xC4524C934C283158ULL, 
            0x2A2E7CD6AE2A01C0ULL, 0xDB600E7AC3E69624ULL, 0xDD3A6719CA766AB3ULL, 0x21191F905345B631ULL
        },
        {
            0xFC136AA8465BA0D2ULL, 0x18C250FB52C65769ULL, 0xC0F0B13397EB28A1ULL, 0x359AEDAF9FDE6377ULL, 
            0xBD6F55301345C3FAULL, 0xF1A5E009EC5B4AC0ULL, 0x6F730FC827A9D0BCULL, 0xC030FCAF345DB867ULL, 
            0x52A915A48B9A164BULL, 0x2A13F9B6C66A9459ULL, 0xB2F9BE7DCEB8637BULL, 0xDEB9530D99D78B16ULL, 
            0xA358490A6023A5B9ULL, 0x4E132DB4C437E208ULL, 0x214E98487EE7A6C9ULL, 0xC5394525988F0A71ULL, 
            0x4A83FF25DBC3F795ULL, 0xA43E6EED7E4589C5ULL, 0x5CEB242C0F615FC4ULL, 0xF0CD252C2ECB81BDULL, 
            0x7A4299B8D2CF6EFCULL, 0x081EF32EB02CCF56ULL, 0xEBECECD8D0FFCB10ULL, 0xF67BA3D8FB3E4762ULL, 
            0x5EC37921253B2F60ULL, 0x44D9C69B01DC19E4ULL, 0x76E69C60371807ADULL, 0x15AD047D42E6BC36ULL, 
            0xD747F8EBC5EF76F1ULL, 0x9B639826FFD4E671ULL, 0x8383C9049218C54BULL, 0xA047CFE213B8EFBDULL
        },
        {
            0xC6A02BB576202813ULL, 0x87B38120F4B7CF80ULL, 0x17647F3BCDA96C12ULL, 0xC2265074798B6585ULL, 
            0x6D6F87261DAF7EFCULL, 0x9D2724FBEC34B6B6ULL, 0x550655793756987CULL, 0x92C31507BE839F2CULL, 
            0x5BC1848E2201F7ECULL, 0x583651E1A00E49BBULL, 0x6C4C0E370CAE9176ULL, 0xFA5F5C7D406EFE04ULL, 
            0x33465F0BB91F7844ULL, 0x314F2FE125A2F9E2ULL, 0xA71AA5A5B9F2956CULL, 0x846819BEA448C1CFULL, 
            0x0B81774C86C54CC3ULL, 0x094AB85FB8CA63D7ULL, 0x802B6F06BD38EAD3ULL, 0x09D6D0F9D3BA2C22ULL, 
            0x4E7C6F3C9922E537ULL, 0x1A5D2AB81972995BULL, 0x102BAFE9F526C927ULL, 0x0E4D31C76B7BDDB2ULL, 
            0x914A0BA8FAC4500AULL, 0xAFB67C93283BC398ULL, 0x830516489C741009ULL, 0x3C718B71F7CD0106ULL, 
            0x664D8005BDAEB8ABULL, 0xFAE3C7B8EBCE8705ULL, 0x1DA5A99C247CF98EULL, 0xC3511E67A0FA2EE4ULL
        },
        {
            0x55AC8654E1F098CDULL, 0x33D211B011EF39C7ULL, 0xB974D6CF74EE41C7ULL, 0xAA113EAA2F017D42ULL, 
            0x7B94976045B2912CULL, 0xCC0C28F651CCC44EULL, 0x4557A12D16B1F864ULL, 0x4C0443224F58733AULL, 
            0x9EC9BAF30AB6201CULL, 0x8362A2D94E99D236ULL, 0x1DC9643A0BBEE920ULL, 0xC833114A26216FC1ULL, 
            0x5334558E3C847BF3ULL, 0xE1FCC503E3CA4E2BULL, 0x92FA099B8EDBE46EULL, 0x76796FB39BD74FE4ULL, 
            0x4FB1733393066BE4ULL, 0xE8129937AF2213D2ULL, 0x582ED54794E219CAULL, 0x1522E1860140C838ULL, 
            0xA1D6C6D8804FDEB2ULL, 0x2AFBFAEEDEE7CF0AULL, 0xD65303E53CAE4869ULL, 0x3F0C068F426699A7ULL, 
            0x8728528917F9CB79ULL, 0x447D4E8A423715ACULL, 0xA4534E208034C6F6ULL, 0x78BE357190896F70ULL, 
            0x0334E1EA1B399A09ULL, 0x561A8B08B2E0C9DAULL, 0xBEE909BBFDDE4D9BULL, 0xD345E92AF8ABCA51ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseDConstants = {
    0x46652F114BB04758ULL,
    0xCFBCA0D6BC4B9177ULL,
    0x7B884C7B5D578DB9ULL,
    0x46652F114BB04758ULL,
    0xCFBCA0D6BC4B9177ULL,
    0x7B884C7B5D578DB9ULL,
    0x7BDA31A2197C0EB8ULL,
    0x1AF26989EC16DDFBULL,
    0xB0,
    0x41,
    0xCB,
    0x13,
    0x8D,
    0x73,
    0xAF,
    0x66
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseESalts = {
    {
        {
            0x4525C72DABF2DE10ULL, 0xA10248604BF974E7ULL, 0x68DE14468C4D9805ULL, 0xBB4632935184FC05ULL, 
            0x52043DE7CDE51C1CULL, 0xC8811AF03A692EB6ULL, 0xA84D7C40E0855436ULL, 0x23323ED6F9567EBDULL, 
            0x9A9BAD319D3304F6ULL, 0x7E2F8986EA1D1BCFULL, 0xF749BF81223EB250ULL, 0x12E9420241EF84C2ULL, 
            0x2965864343148BC7ULL, 0xE9836AD7DF9A7A3FULL, 0x67D6458015405B46ULL, 0x5A11B072DD59024BULL, 
            0x5956E4F2E0C4D2BFULL, 0x6C6DA66CF069D4F0ULL, 0x869B846ED4CDD813ULL, 0xD373ED0B108846E5ULL, 
            0x309BC066E24930ECULL, 0x4C75D8A79974C95AULL, 0x6BEAFFC8742FCB08ULL, 0x6B77F510B6D14B1DULL, 
            0x9F62E47A128A6150ULL, 0x0703758E3A378D80ULL, 0x45D0FBE54ED1E40EULL, 0x1B52C0F91EA0CF26ULL, 
            0xE56E66CA2521DD48ULL, 0x50749ACC0E3AE4FCULL, 0xB41A34000C9EE7E6ULL, 0xCBE4491CF497E34CULL
        },
        {
            0x29592A274C7AD062ULL, 0x5B5CBA22B71B11FAULL, 0xBE61DDA7676CEB97ULL, 0x8BFF15C405C8F56EULL, 
            0x714426BD3663F44BULL, 0x727BE94CA6AA5AB1ULL, 0x199C8A1121B3847EULL, 0xF5974769AE52C0CAULL, 
            0x8073D37BFAD74F0FULL, 0x269C8154D74230F8ULL, 0x99D5702251873933ULL, 0x205C3358C72C2F60ULL, 
            0xB1650045E7BCB840ULL, 0x6AAA7C18DD095BA7ULL, 0x148F050FE81FEA3DULL, 0x2DB7420051204E17ULL, 
            0xAF7C833D7BD43B0DULL, 0x6429C398954BBE72ULL, 0xFD174851393399EDULL, 0x434F314067452473ULL, 
            0xD456B64BC70E289BULL, 0xA6A889B32B54714AULL, 0x26CAA797613BEDA8ULL, 0x760328A1494901BAULL, 
            0xB2694628D5FDE085ULL, 0x8A17946459910FB2ULL, 0xC786E8098E0DDCD8ULL, 0xC00A065A7D496EAFULL, 
            0xABA19E6EEEDB7108ULL, 0xA9EDDE0449C9A2C6ULL, 0x4971D3911C3DA7F2ULL, 0x66B46233AC9B84EBULL
        },
        {
            0x8F51D59737F914BFULL, 0x6DB7C6B7C3A8F35DULL, 0x64B3AD5AF700FAFAULL, 0x1528E32248510A1AULL, 
            0xF92E1CA6AF9FCD72ULL, 0xB7AD68AE6D64C3F5ULL, 0x6691F67EFA0241BCULL, 0xA39A60F1DB6BC868ULL, 
            0xB07E1FB67AF8785BULL, 0x9D6A459988FFF989ULL, 0xDBFDDA64B8D34310ULL, 0xDDEC27981372912AULL, 
            0x976A70E709D6AF96ULL, 0xBD21F54A79E2AB01ULL, 0xB812F5F3F177A9E4ULL, 0xCF551A21334BA062ULL, 
            0x4417FEE575267E9AULL, 0x9DCD9F6E1F26AB54ULL, 0x93088655558ED697ULL, 0xBA8999A54C573C13ULL, 
            0xE26206F6EDC02029ULL, 0xE5E6F12913ECA425ULL, 0xFDCEA59EDEB9D46BULL, 0x3AC5B2A1257D0F13ULL, 
            0x697A862DC67A790AULL, 0x27C161066178C558ULL, 0xB5267FB2BD7F1CB1ULL, 0x08C413A4F3B4A939ULL, 
            0x12CEFF9B19565BF2ULL, 0x7E7076115808588EULL, 0x72299655DD94F2D1ULL, 0xFCCF737461C1A821ULL
        },
        {
            0x78493AFE300382A3ULL, 0xC1E2EEF740919E24ULL, 0x8961A9F766BD611BULL, 0x1E2E436D47A0768FULL, 
            0x7CA482B789BC6A28ULL, 0xE6CC579EEC9010D3ULL, 0xF50BB5A0A4EC301CULL, 0xF89DB4DD4E7766F3ULL, 
            0xE3FE70CD96C377A0ULL, 0x9F23A1E844E2EBBAULL, 0x290CD6D48655F79BULL, 0x13BE48429C4F78E4ULL, 
            0xD09E26E56D745843ULL, 0x0F674E5964A92BC3ULL, 0xE5FAA1FBB397DC3CULL, 0x03B63137694EB581ULL, 
            0x0CA1B0F305C89A35ULL, 0xDDA9CB95F4F244FAULL, 0x7A129CE20AF3D2ABULL, 0x1E28E968EAA03CAFULL, 
            0x595C93AF425CD37FULL, 0xB35F484001B07ACEULL, 0x39FB09AE26B3940EULL, 0x0FF30ACC31F56D6AULL, 
            0x10505D697FB8F782ULL, 0x7792C0E33C544BE0ULL, 0x3F0E9B385A407A99ULL, 0xC93C4EEF2D3A545EULL, 
            0x985613969E10D229ULL, 0xCE20890E0C501E4DULL, 0x8C22E4153A6E8352ULL, 0x65B95D9971F9C5E7ULL
        },
        {
            0xE3FB0E50C37D933AULL, 0xFC144CD0C1985D8BULL, 0x0D0BDF6F20D64E4CULL, 0x5BE8FE945FE53AB2ULL, 
            0x9C25F30ABC93A1C1ULL, 0x95E54C56C2F13E09ULL, 0xE4DDCFDFB5FA258FULL, 0x6BB1CB6DB49AF798ULL, 
            0x2AB0CF266EBB47AFULL, 0xD7A896E49CEB060AULL, 0x9DD66ECF24DCB83CULL, 0x54AE32E7780E15E4ULL, 
            0xE4FE7F44CD782D99ULL, 0x908EE2CFFF6ECF94ULL, 0x5203987755C04D3BULL, 0x8AA9442CD06486FFULL, 
            0x02012FF3FAC636FBULL, 0xD865322688672159ULL, 0xC12626A6E0E280DAULL, 0xA65CD137DA0BD15AULL, 
            0x3EC7F185536122FEULL, 0x325A370DB22037B5ULL, 0x77B75B3D569B0C1CULL, 0x3C7F7CAC53E9A2FFULL, 
            0x89065773F7613E73ULL, 0xFB148DB60F68B34DULL, 0xE3ADD3C0C31AC5ADULL, 0x9DAD9CA048CE582DULL, 
            0xE97D5166FA640CF1ULL, 0x0AB64D8EB1AFD40AULL, 0xA4FB9E0BC452A7D4ULL, 0x3D3B6BC69F69DD21ULL
        },
        {
            0x3254DE8210F3779DULL, 0x10AE875AEE7F66FFULL, 0x3F079148C4CEBCEFULL, 0x587C9D0602D38BF5ULL, 
            0xCC6347CFF75E90EDULL, 0xFEFFEA10D3E921F4ULL, 0x2A061DD288C87798ULL, 0x300051CD0A5D31E7ULL, 
            0xAAA2D613F56F1701ULL, 0x8FC584FE76ABDA4CULL, 0x7EAC923270893FB8ULL, 0xC0C2ACC31CE77B19ULL, 
            0xDC05DA490D5D3A43ULL, 0xDD4585C0CBB50EDFULL, 0x0CA6CA7358EDFA4BULL, 0x9027C1A24BE88AFAULL, 
            0xB1D6AA580A29E43FULL, 0x887C6AB79466F343ULL, 0xEAF8EBB7DCD93DC6ULL, 0x1D11DB97A4727147ULL, 
            0x20ABFB1A53DD6E63ULL, 0xACB88D0CC8B6E251ULL, 0xA281D49E677AD31AULL, 0x76B12B5E1F17B2C2ULL, 
            0x2FF0EBF30B146992ULL, 0xB138DABC9D077AF1ULL, 0x977739EE09E70CDDULL, 0x4C9BA66B75C6D7ADULL, 
            0x3D19CA3EB7B4F9FCULL, 0x78E399A1FD7A51ADULL, 0xD9A24BD7EE7A5DE2ULL, 0x0E308D8CBACE5340ULL
        }
    },
    {
        {
            0xC0967A9F12E84EBBULL, 0x1BC5566BD41CA19CULL, 0xFC70BD313D48AC16ULL, 0xF1E06DB22E0E70CFULL, 
            0x9520344A8B373D65ULL, 0x71CA7B8FCD105208ULL, 0xC4B59381C02C3E37ULL, 0x61E82E0E0CFDCD42ULL, 
            0x41518C0105927F95ULL, 0x8CEC3B0523D5BBCAULL, 0x8400926103A76D0DULL, 0x696F9935A14BDF39ULL, 
            0xE10D9B43EE6F1280ULL, 0x7B60F36F328202DEULL, 0xDB4AA73A17C17491ULL, 0x9C558C7A678C7C76ULL, 
            0x7B138B433A2B62ACULL, 0x28F297D10013F151ULL, 0xCE7FABC35E89B07FULL, 0x6AA335DB7BF9EF3BULL, 
            0xA1E3287D85653C1DULL, 0x50DA03B81D873AA4ULL, 0x31DAE6C8D5E36D04ULL, 0x1BC5E11F47B25DB4ULL, 
            0x4771950E3F7D27D1ULL, 0x7D17AC83964C1D6FULL, 0x5D170A6EFE8DC3A4ULL, 0x4D62DEAD682C87A8ULL, 
            0x0FFE28F7E5E4FF00ULL, 0x030B259EFCDE6328ULL, 0x8DA4B57B2C28C21EULL, 0xD02A278F080A3AA6ULL
        },
        {
            0x165CF613F1EC652FULL, 0x1DCBDA8F6D2CC633ULL, 0x03541F271118C64EULL, 0x38071C20BBD601E2ULL, 
            0xF24AE5A6912A5C15ULL, 0x60884669CA9ADA75ULL, 0x7EABD34CCAFCB80BULL, 0x387162874511C41AULL, 
            0xB46BE47405A7578AULL, 0xE18711B998766101ULL, 0xA64FA0D7CA8A2738ULL, 0x939FEB7477D443B9ULL, 
            0xAE205E6A9AB884F1ULL, 0xF219366E7FED465DULL, 0xD29E8B761E69AF88ULL, 0xAC90698D8FFB2C89ULL, 
            0x751481E93D42B673ULL, 0x7625BAD2DDFA12A3ULL, 0x0216D226610DBF8FULL, 0x0CE5E2A372C88571ULL, 
            0x372375284B1D9A64ULL, 0x53E23278DB3B5AC3ULL, 0x3C72B349AC00B669ULL, 0xBF93DC038097C983ULL, 
            0x23BA7D4F696B6ECDULL, 0x6C32A5524078685EULL, 0xADCF274E2F564FFCULL, 0xF8989507D62CAC80ULL, 
            0x015F6D6429EB00DAULL, 0xE4E3D5815119536EULL, 0x8069CEE3A50151F8ULL, 0x355A7F4109AD51CBULL
        },
        {
            0x8E339B57B17CF20DULL, 0x8EEC0DFB04C2E049ULL, 0x674062B00214748BULL, 0x6CB5D85336C7BF05ULL, 
            0xFFD24AE9F4497BD8ULL, 0x192D1DA2B9EF1F1EULL, 0x2742529E73443C67ULL, 0x04FDB65BD5129F6AULL, 
            0x0A56240FA2B64145ULL, 0xE557115B3B23AB56ULL, 0xB810033FA3FFEA34ULL, 0x679A05408ED04607ULL, 
            0x198A43B84C406500ULL, 0x6E1678DE59282519ULL, 0x2EFE807EDEE737B6ULL, 0x4D69553B889067B2ULL, 
            0xE572D3575FED38E1ULL, 0xC3F03E58BB8F8898ULL, 0x9DEC6BCBFF7E5EE3ULL, 0x23500F5D4710CAFEULL, 
            0xA21CA2336800F49DULL, 0x60A01CE4D3236884ULL, 0x3402BA2723BB667DULL, 0x030E41BE3F847AF3ULL, 
            0x1CDF5CFCC3E8DF7BULL, 0xE927B5E0DA7D4A31ULL, 0x077A3F7BE6D80D37ULL, 0x7CAD39C1978F8D7AULL, 
            0xF0D6E0CAE2CFE860ULL, 0x0AD7F2C6279878E2ULL, 0x2BB3D6540D70437DULL, 0xE74E7578E58D558BULL
        },
        {
            0xA2A1DBABC1BCDD32ULL, 0xFDFFC399701308E2ULL, 0xDC64CCF3134D8642ULL, 0x00B41CE62F029EC9ULL, 
            0x57776C4D93B31B58ULL, 0x9A24A5F0680266E0ULL, 0xAAEEE730894CBE45ULL, 0xE3429D7CCFDE6D02ULL, 
            0xCC5C20B9A2727859ULL, 0xF4F6459F3729A62AULL, 0x3D06BC32DB7030ABULL, 0x4ACED709C925C53DULL, 
            0xD288FA38D1A30C50ULL, 0xC6349F089B510617ULL, 0x9DE784877525A04AULL, 0xB7E6A7A3FCA3E613ULL, 
            0xB711D276055D3AA3ULL, 0xA81C98D70BB76521ULL, 0x48F964C76555BF7EULL, 0x9A1A51B4323F80C3ULL, 
            0x7FBFC4A996F3DEC6ULL, 0xB016A64473DA3400ULL, 0xD79529E4B251E2AEULL, 0xE43C2E3B8C1A2172ULL, 
            0x41CE176D141FB0EBULL, 0x077EB31B76713841ULL, 0x77E67B1DD11A7474ULL, 0x010C133E6EDFDAB8ULL, 
            0x157E053AED8FECE8ULL, 0x68F0C4C359E92F69ULL, 0x1BB2D502D02E560AULL, 0x8E0914EFCE5CABD8ULL
        },
        {
            0x5092B3F69067F9DEULL, 0x1F1A85C988D8502DULL, 0x2A45F27A49CE2198ULL, 0x1E4AC6987AA7CB74ULL, 
            0x8723196CAFD8920DULL, 0x31F4196ADD21C6CCULL, 0x0094613A55F0C1D2ULL, 0x9A99BBF1524EFF40ULL, 
            0xF598AFF8BF2257EAULL, 0x06A71965FA18C45DULL, 0x2FD852334F4846AFULL, 0x603B30A48A32B6D5ULL, 
            0x0E5D0061F4AC664DULL, 0x3A44C3D56C3623B9ULL, 0x929310708738E203ULL, 0x6A2B003F99EB5196ULL, 
            0xFA3D31123B305F79ULL, 0xC12CB769531AFC9CULL, 0xD2D7C9F211EAA454ULL, 0xF23123AD55A2E98DULL, 
            0xE35B305F772D2818ULL, 0xFDFAB06E1CA5DFEFULL, 0xF4871C2120F08B72ULL, 0x33FDDBD34265993FULL, 
            0x78094BA4EE4D279DULL, 0x2C0532D8F3C0F948ULL, 0x48C4532F81481CCFULL, 0x68A3669D9A9F61B7ULL, 
            0x4C77CFA2D1F86FADULL, 0xF308766585822928ULL, 0x7C45A95126D3F481ULL, 0x746E8294F074D360ULL
        },
        {
            0xEC33988DD2D23244ULL, 0xA500FF003926F196ULL, 0x8B00D1A5777498EBULL, 0xAA633B4720950C6DULL, 
            0x0F0172705A15770CULL, 0xBD511A4889FB48B5ULL, 0xEA38FC59DCDC9EABULL, 0x163EC3F7241B424FULL, 
            0xF851981349B49916ULL, 0xBC543365B923374AULL, 0xBF9C253B57430E25ULL, 0x3C5F5249016DA34EULL, 
            0x4292E5683010B1BEULL, 0xF14349741B0ADAEAULL, 0x309EA4A87EED3C32ULL, 0x02F37F4C3BAD3FDDULL, 
            0xD596E8DC3D4EAE46ULL, 0x9C0B98DB5013DDB8ULL, 0xC89F8B23B9E61218ULL, 0x1DBEAD4A744726BEULL, 
            0xE97943368F020DC5ULL, 0x63F3C263E7564EAAULL, 0x458A413477BBB515ULL, 0xDA6452B0687898AEULL, 
            0x119BB1FD609A9C2DULL, 0xABD291EB090D6C82ULL, 0xDE86F420732EBC00ULL, 0x3926207E82056349ULL, 
            0x7927B35E56F35E64ULL, 0x48084EFB24B9FA80ULL, 0x1905B091EB69DA0DULL, 0x202C29E23CD51DA5ULL
        }
    },
    {
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
            0x313CC721D3794682ULL, 0x97CDF73E9F6776BFULL, 0x4BB9A0C86FF141C0ULL, 0x6351FDF6AB75FBAAULL, 
            0x340BE2501EF78BADULL, 0x15C90B7A4C91A745ULL, 0x91650F8330994931ULL, 0x28D8A9C6E1B53C55ULL, 
            0x47784EE72FC35B60ULL, 0x83B1E61AD4B0D887ULL, 0x07B67E649F5979E4ULL, 0xA32B7A67EC2C8D0AULL, 
            0x7416FBB035E52EBAULL, 0x015F843BD8A9CF27ULL, 0x376FB5C28BDA10CDULL, 0xDF3744A037281CCBULL, 
            0x71AECBFD0DD88832ULL, 0x27CEAE431B67952CULL, 0x066F0A07182EA8CAULL, 0xFF7C4E3679D2F6A4ULL, 
            0x422B80319C5AFDE5ULL, 0x05F1F64160B57693ULL, 0x823ED05594A29922ULL, 0x6C29D773D28CD439ULL, 
            0x5F241DBAF40A560BULL, 0x8B58C8FB27745557ULL, 0x4C78F1066ED14B91ULL, 0x5D0DA34D9E50B943ULL, 
            0x2A4ABE6D84C0C84AULL, 0x887A42C0ACB2911EULL, 0x2D9DBD3033476975ULL, 0xA8500E27A4CDF083ULL
        },
        {
            0x8B21C301E42FDB5EULL, 0x8986FCA7A2F89AF9ULL, 0xE67DD3BBCB7FE68AULL, 0x519503BAC146C481ULL, 
            0xCDCEA502F2476AC8ULL, 0x052559516886031DULL, 0xFA198E123CAE1B52ULL, 0x30DA196C9494251CULL, 
            0xEB85A25654500596ULL, 0x533FBC60A5CB2A05ULL, 0xC76E31CFE5E7D166ULL, 0xA3019ED580E4CE6AULL, 
            0x072419C67A4727AAULL, 0xF78068F86C32D743ULL, 0xC99413D4601FC247ULL, 0x14B65564C84D4604ULL, 
            0xB80721C047316724ULL, 0xBD0A655F9DED098FULL, 0x74AE91CBE2DABC5FULL, 0xA1CC0F05D8B335DFULL, 
            0x6282897D2357741BULL, 0x03F10644633E1137ULL, 0x36473C8EB9E985DAULL, 0x6F49CF9A61D163A8ULL, 
            0x8F292CF990449085ULL, 0x57C69F282097D37BULL, 0x74D58B13DA714C96ULL, 0x9D7766C5E038EA9CULL, 
            0x98E9984B8BF1026FULL, 0x12BC80D8DDB3EAB8ULL, 0x4034CDA7D97B69AEULL, 0xAB337E974D1DE456ULL
        },
        {
            0x0EF3FEB06FDAA50EULL, 0x73D2A539D7113C26ULL, 0x89A5965D2EA8D000ULL, 0x5A77A786456B9E67ULL, 
            0xDD2F2D1CA2D423DBULL, 0x7A51037ECF2885D4ULL, 0x3E7D437CC50C0860ULL, 0x7DFA3AB44BE1DFC3ULL, 
            0x2961A2A4519055D5ULL, 0x79D430EE5DD3A804ULL, 0x217555D969594D7CULL, 0xDB859F653199BF7DULL, 
            0x1A50F94726E54A83ULL, 0x40E0CF3B5550DAA7ULL, 0x60D7110667AFBCA4ULL, 0x08E6BE63159DF7F8ULL, 
            0xFCB94A223DBB423AULL, 0xA191917036B946E4ULL, 0xCEE9FFF14B73B2DFULL, 0x75911C677FD75537ULL, 
            0x32F62D42261DD56AULL, 0x136953347058ADA5ULL, 0xDDA8CC002EEA7C63ULL, 0xA056B28B0EB42053ULL, 
            0x7C12BB9CD8F88556ULL, 0x0E672FFFC5AA9D72ULL, 0x61E3254421010F2CULL, 0x5C55B19660113CBBULL, 
            0x8DC26E45A842B221ULL, 0x8AA8EB370984E44BULL, 0xC2BA612586C62AA6ULL, 0x97C44C08ADB5621AULL
        },
        {
            0x0AB83BA67E7A7BDDULL, 0x49C1CE7AF738A741ULL, 0x091520B0902D5D11ULL, 0x514662A46E58C6B1ULL, 
            0x899BBA827B6AC3D0ULL, 0xBA75A43DC02B5CB9ULL, 0x339FAF00D8717D9CULL, 0xAFF86D8593692093ULL, 
            0xF4DC5809B9C0D7C8ULL, 0xDDDF08FDA98310EFULL, 0x1A5E2F881DBA5684ULL, 0x0B32DCE2433D6ABDULL, 
            0x82876FAD31EFDA86ULL, 0x44125B4C27455E86ULL, 0xDEFD301BEE65AC35ULL, 0xB6A7A9AC7D4F585EULL, 
            0xD320A2341A509E9DULL, 0x26F9443412CEB5A6ULL, 0xFE2B44A0D4744544ULL, 0x41595DFA5E8DE1D1ULL, 
            0xF1E127A7767154E6ULL, 0x8526C26AF5AF018AULL, 0x52AEE1DB2B44568BULL, 0x652F77826BEF5AB9ULL, 
            0xEC5C92D2F03F2FFEULL, 0xFDCC39884B50E4CFULL, 0x439B14B71D6B7BD5ULL, 0x0A0721696B1FFED6ULL, 
            0x64FB7B1CE9E8314BULL, 0xC3BBBD8CB7722D3FULL, 0xFD6444A09F16D456ULL, 0x8BD1732562454FABULL
        },
        {
            0xDA74C92C5B619669ULL, 0x167D2076976504ACULL, 0x287511F7F37E0122ULL, 0x666F3C6152AB1A74ULL, 
            0x00233A29C4E71C43ULL, 0x226C89E26B9E2330ULL, 0x9479774ACC528B38ULL, 0x415DC6AD318C5D3FULL, 
            0x5F2E2D1CF7A0B7CFULL, 0xC2F9FAD1A86F04B3ULL, 0xB12C705542F5EAC9ULL, 0x50DADADBA9800FA0ULL, 
            0xEE2B9028043BEA77ULL, 0x905403942E1C4D68ULL, 0x929F38BE90631E23ULL, 0xCE6086B278B6CA55ULL, 
            0x275A388F9FC8E456ULL, 0xE501D85F3DA4B75BULL, 0x5AA083E1FF1FAB4FULL, 0xDC5829B7B75F8BD8ULL, 
            0x3D54219087C2E4F7ULL, 0xC18907C48206B3DCULL, 0x53CEE8A6B6B2E6A4ULL, 0x5C0707F84C5AC105ULL, 
            0x58562A55315A248CULL, 0xD9071FB940C51356ULL, 0x132B9003AAED78D7ULL, 0xE06E525CE9DD5E74ULL, 
            0x56BD39EEF2C5A356ULL, 0x9D2908434879A932ULL, 0xF81482DAF3344D72ULL, 0x91249342037DCE18ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseEConstants = {
    0xA208DD5132A6132FULL,
    0xD28C0787CE92E4FBULL,
    0x76D05322DA3C90BDULL,
    0xA208DD5132A6132FULL,
    0xD28C0787CE92E4FBULL,
    0x76D05322DA3C90BDULL,
    0xAE68F0DC2DAA0937ULL,
    0xDC94C9401974E394ULL,
    0xBF,
    0xE7,
    0xC8,
    0x33,
    0x41,
    0x79,
    0x18,
    0xAA
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseFSalts = {
    {
        {
            0x933B7E29EDEFF41AULL, 0x774543ECAD22AEAFULL, 0x414D455EC8017DF9ULL, 0x8D826D808625938CULL, 
            0x2A9A1F495EB62078ULL, 0xE88EBB923CE3F018ULL, 0x8E0F1382DEF46CB1ULL, 0x19185C6699B07A7BULL, 
            0xA172D13E919B99FFULL, 0xB17BD6A7B369B587ULL, 0x693D723DC5402F85ULL, 0x91EDA027B254DB3EULL, 
            0x70E5179ECAAF10C3ULL, 0x335DE19DD6F77271ULL, 0xCC6CB44C8ED3766DULL, 0x332CB04941BE2534ULL, 
            0x93C641002ADE12B3ULL, 0xFE9AA942D3D43C19ULL, 0xEBE54890AD05FB30ULL, 0x5726221ECAC804E6ULL, 
            0xA8BAB704DF163590ULL, 0xC6A0CC0BC571E089ULL, 0xEA4D7A4532985AA5ULL, 0xD5433D49AAC59504ULL, 
            0x8701EEABBF0AB66CULL, 0x84D8D190B2133C28ULL, 0x395911AD139D5D55ULL, 0xB510F5D250085BB5ULL, 
            0x0486057C18A53FC6ULL, 0x1045BA6DAF092A3CULL, 0xDEFB7B74A79AE37DULL, 0xB624707E5ACFD2F1ULL
        },
        {
            0x795C9F121088CFE1ULL, 0x7773FCB148CD9687ULL, 0xBC2390BE5731374EULL, 0xD74F44B1AB2AC65DULL, 
            0xD6327D3CF5AD730DULL, 0xE06EC440A665FD4AULL, 0x2E78A71B85E3BC75ULL, 0x8266CB5B75161E49ULL, 
            0x7C7EA4E638901F30ULL, 0x819477B8B8B7D1F5ULL, 0xB8A7355122F13E4BULL, 0x75A6F5A20D18B291ULL, 
            0x0356264CCB10BBDDULL, 0xCF03286F1F2D63EBULL, 0x71CFA1388670E2D9ULL, 0xCF089B8C855CFA14ULL, 
            0x3CBC8E4A6B072ACDULL, 0xD34E81C03DAA494BULL, 0x0C2D37FA494276E2ULL, 0x55DB39574E0D019EULL, 
            0x65B15006C3A7C89DULL, 0xAE6BD8A5CD286776ULL, 0x12295BEBF853827BULL, 0x2834D9B938F3FEF4ULL, 
            0x05C05C9AA40ACF44ULL, 0x21501122AFC7ABD6ULL, 0x266ACADDB5A43EE8ULL, 0xAFC6F7372E9A86A4ULL, 
            0x4E8D74CAA170B4F5ULL, 0x24A9AA0930C608E3ULL, 0x0896A435DDC0C37EULL, 0xEFC9BD40A45F690BULL
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
        },
        {
            0xED7B509B36122586ULL, 0x7ABC19C3AF79634FULL, 0x9E28EEE5D692381CULL, 0xD5545C3F8EDE2308ULL, 
            0x10D5CC7ED67927EBULL, 0xB9020AAE109AD980ULL, 0xE76B1A38D22FC4A1ULL, 0x82C3BF13639ED3EDULL, 
            0xBB5D223625CBD788ULL, 0xE8DB233A91206450ULL, 0xF5DB3526AC49CE5BULL, 0xA1A8A1BB7A745F47ULL, 
            0xAE82D3FFB378A7F9ULL, 0x252EBD2023E60EA1ULL, 0x4342596FF50D0610ULL, 0x616439006F812ADCULL, 
            0x594BF3A7A4A8B27BULL, 0xC118EDDF42C6346FULL, 0x55BF4F5CAA6EAB3DULL, 0x50BED0CF8EDA0C17ULL, 
            0x36B9731DC7EFCD61ULL, 0x26C5E7FD2882D8D1ULL, 0xBBF012B0C4B7CFE0ULL, 0x71CE08B2AEE7E860ULL, 
            0x3D1E6B710D721A7BULL, 0xC4402F6ABDB276C4ULL, 0xF4F5123351397AD2ULL, 0x9ED97C6727D56027ULL, 
            0xF46113F7CAB7BB2BULL, 0x1E81FACF09BC6EB0ULL, 0x9CA0782BBC3A14F2ULL, 0xC5370D1EEC25820BULL
        },
        {
            0x2666ED9B8690F907ULL, 0xB7CE42F15D0DB865ULL, 0xB8007D50DAC5DC97ULL, 0x5DECE351BC16F82FULL, 
            0x64F6364A40A69778ULL, 0x5A3F5DF545CC9E05ULL, 0x3573A17BB330586CULL, 0xAE8B42CC87F31FEEULL, 
            0x90676F56826FF6B0ULL, 0xDD7FD1B10169336FULL, 0xA8EF64DB7FD7D9A1ULL, 0x42B5E0E1F65C60C8ULL, 
            0x353EEAC349BAA77DULL, 0xC388A870E0F55EDAULL, 0xEF930DD37D6E23FEULL, 0xB6BFF53269EA4BACULL, 
            0x7ED6CAA12EEEEE80ULL, 0xF46E56D9B92C3DFEULL, 0xBA1FA08DFA6CB05AULL, 0x652A31D95D85ED79ULL, 
            0x027274F9D4B41385ULL, 0xFBDFE308F5AE14DBULL, 0x5D0F0DC034FFE394ULL, 0xDD3B199F660E5336ULL, 
            0xF14337A977E1F2D6ULL, 0x4D7AB35ED7D75163ULL, 0x162CBC1E7E2C0499ULL, 0xD94AEBD036B5784CULL, 
            0xAF878D3235871055ULL, 0xA20EDD8BCCE9710FULL, 0xC41E8FC102EFA852ULL, 0xAF1B2CF9F8732932ULL
        },
        {
            0x3FE1BAF96260EDE5ULL, 0x1C972000F054DB2AULL, 0xC987B3C9725D93B6ULL, 0x9749E42B9E7DAA6CULL, 
            0x8877157C81430070ULL, 0x250406BE2CE6EC64ULL, 0xF9B23D3429ADA5EDULL, 0xA8D9E84466F4F12CULL, 
            0x9E4F9593A4CFCC68ULL, 0x43094E01CCAB5695ULL, 0xE175B5BC7E3A6985ULL, 0x7685C9BE8DD6016BULL, 
            0x8416173153E8F0CDULL, 0x19C69DF03D1A0C19ULL, 0xB5684765085310BFULL, 0x1541E5BBB3A90399ULL, 
            0x782B559A99FB2993ULL, 0x54311F4AF3E3F06FULL, 0xDEEB150417DDB0A5ULL, 0x5B23AFDEC076FC4AULL, 
            0x14FB6BEC596EFBB1ULL, 0xE1FDFDEF369BF306ULL, 0x3E99AB88410248F4ULL, 0xDF5E1014E9F9EFB3ULL, 
            0x6066C03A17357810ULL, 0x67048D68BE1C1EAAULL, 0x2F2855902B0788F8ULL, 0x78CBD42CEC57197BULL, 
            0xA521DB58437C69DAULL, 0x1D467F5529A34359ULL, 0x83365331A3F98072ULL, 0x55431E03633B9520ULL
        }
    },
    {
        {
            0x8A21D7E10BD3530CULL, 0x0B138D00A17FB560ULL, 0x0D06948D6374AF39ULL, 0x96D5A696ECDD5849ULL, 
            0x5A25DBCFCA584328ULL, 0xA92D18088E34CC7CULL, 0xC8533229FED3DF02ULL, 0xB2C23535229E9F8BULL, 
            0x989A398FEFE797BCULL, 0x84BA08AAAECBC2BFULL, 0x3491C03BF93AB2ACULL, 0x92C019D8B027005DULL, 
            0xEBA926644D3DA295ULL, 0x464112389D265C02ULL, 0x224CCCD4B00A5291ULL, 0x4CFFEFAD7066B1D9ULL, 
            0xD67910991E9C1954ULL, 0xE69FB02FAEBE07BCULL, 0x8B4BE496962C210EULL, 0x40CEF73A9BBA1B1BULL, 
            0x947A6FDE458D4FCAULL, 0x33FCD0D3214555FDULL, 0x612113816A0A4B65ULL, 0xC01AF2656F86A040ULL, 
            0xBE388BDA06021F9CULL, 0xFDCEB3DC0D57A81BULL, 0x5BB9EE514ADA540CULL, 0xFDD10820C313A8ACULL, 
            0x5769B3EB371A1E29ULL, 0x90425C1173B44DADULL, 0x06F1CA89FCDEF533ULL, 0x9830C6A9AD20FAE5ULL
        },
        {
            0xD803062C001A0825ULL, 0x70DFB572C29BDD47ULL, 0xE466F1D0A93DEE21ULL, 0x41143538E9FECDE8ULL, 
            0xC0180BAA1888CD42ULL, 0x1D77E5D794958E5EULL, 0xD24B6A3D84236D65ULL, 0x60955FF6752777D6ULL, 
            0xB1E1CA6BA20C4A89ULL, 0x120E76DA8C390A78ULL, 0x0B45E244DE5CED4BULL, 0xC93FC2D8BBA70034ULL, 
            0x29B85AA23930760AULL, 0x3CCCE45323A64A0EULL, 0xC6F4E032D7ACC64DULL, 0xEAE2116CEA3440AAULL, 
            0x63AADFD8AAACF7A7ULL, 0x61C22C05FE3FB743ULL, 0xEEC516DE8C033B53ULL, 0x60E54E0B88B61413ULL, 
            0xB4609FEC28751192ULL, 0x63A1C76C3DF96000ULL, 0xB774E1F967D235B6ULL, 0xCB18B532EE8F99EAULL, 
            0xDC14768E3242E741ULL, 0xC0936C32745C27FAULL, 0xE859E4C04171D1DDULL, 0xD5E5016F058A31B7ULL, 
            0xCED6DD88E4040D2EULL, 0xA6EDECAA97382473ULL, 0xDC3F2054D466A25FULL, 0xC35C478CFDF95F6DULL
        },
        {
            0x8B3BAD77ADBB3C83ULL, 0x5F736E837CC865C3ULL, 0x2C6271CA5842E61FULL, 0xE879DEE9042D9289ULL, 
            0xDA51A52A0B6422ACULL, 0xDD583ABFEB002EB6ULL, 0xA7CF1E344BC631C2ULL, 0x42E6CC73C449FE81ULL, 
            0xF753E05992A253EBULL, 0xB976196F3CF977ECULL, 0xEC5140A139CB3B33ULL, 0x258855E164D3E216ULL, 
            0x8B02EBE6593926D5ULL, 0xDE7B83915CB5B947ULL, 0x29F70DF283D18189ULL, 0xC968A80E56D30444ULL, 
            0xCA3996D2C38454A0ULL, 0x2E1A05D3726952A0ULL, 0x0301A3D38D251750ULL, 0x4CC633BDE6CBDB83ULL, 
            0x1D79352F6F35E74AULL, 0x8B1DF3C11EF8FBCFULL, 0x2B46E97B2B6920A3ULL, 0x90A55313335F4380ULL, 
            0x830A488EBC62687CULL, 0x93E083B480B76CEAULL, 0x1C315BBFF3912F08ULL, 0x52724DEE2F75D295ULL, 
            0x44622A5AA261EFB6ULL, 0x8ECBBED9AB07ECA9ULL, 0x9F7B319D253AD2F6ULL, 0xB90F37464BBA3936ULL
        },
        {
            0x89BF9A8CCCDC2D8DULL, 0x66A3CBBA53853D11ULL, 0xFE625E0CFA70CCB3ULL, 0x6A7C469D25397C91ULL, 
            0xCD07DB82053E1469ULL, 0x49486B2D6AA13660ULL, 0xBA2E723791DE98E5ULL, 0x9B095766E41AC072ULL, 
            0x3F7A731CB1F12278ULL, 0x742003590B6F9795ULL, 0x8E8513A9EA14735CULL, 0x5149FF9CAC425BA7ULL, 
            0xE849CC740DDD2B60ULL, 0xC6325F3E68418A7AULL, 0x37B89BFF9A062A4CULL, 0x207B2AE3BF3D6076ULL, 
            0xA00E378F9A1DEA4EULL, 0x13949C7C7A98B59CULL, 0x363DD0D3087E64D1ULL, 0x65F7C0DF0CF0EE74ULL, 
            0xF48C4660C4C70260ULL, 0x4774981FBA308EDAULL, 0x23F43D19CE7B78E9ULL, 0x99800233D044A070ULL, 
            0x0635D31BA9082451ULL, 0x97B6D2D8FEFAAD16ULL, 0x996686BD69D50908ULL, 0x26F30D9A6428E4C2ULL, 
            0x3ED4BE10C1591DCBULL, 0x625824125B53D4F8ULL, 0x126E469BC59D69F8ULL, 0x350F1929BEEADDFDULL
        },
        {
            0x424D893E0F27EE45ULL, 0x1F7231509FCAEFF3ULL, 0x034A086A057B408BULL, 0xE58A2A19978B5EB6ULL, 
            0x26608D57EE2F8F8BULL, 0xA55D888176E3FACDULL, 0xAAB69266325449C7ULL, 0x7567D09F4DF41E1AULL, 
            0x97F98BA7C13A9E9FULL, 0x9F827905F1E24A31ULL, 0x8EFCB5B16175CBBAULL, 0xBC131634CF11A541ULL, 
            0x0914E6967336676DULL, 0x43378469C370C8C4ULL, 0x2AD4BD69763DA180ULL, 0x5F3531472436FF48ULL, 
            0x83AF6ED2EB06E094ULL, 0x175EFA739F412D47ULL, 0x7C919E64A273D17FULL, 0x2D6999257DAAC9F0ULL, 
            0xE4A6AB31713D9615ULL, 0x8D4DD43F2868A475ULL, 0x9CA2BC07C3A74990ULL, 0x4F93F4E3BC015864ULL, 
            0x93CF5ADE308E27B3ULL, 0x545148F294EC0F03ULL, 0x7F1F4C8DD67FA1F9ULL, 0x669118D94A69C2ECULL, 
            0x6587A0397883F59FULL, 0x98ADD272000B7235ULL, 0xA7E18CC48160277AULL, 0x79BD047A17925FBFULL
        },
        {
            0x252900608315420BULL, 0x5BAC80601C63FCCEULL, 0x80A40DF316995F01ULL, 0x1724908B791A401AULL, 
            0x06D2CF9797747CD6ULL, 0x02C4BBD0045A3F35ULL, 0x5FCDC8AABB3DC03CULL, 0x23FD15E09AEC8391ULL, 
            0x97AB044FBD31E888ULL, 0xF726D48CDE5056E6ULL, 0x989B0150A44E233EULL, 0xF0A523E0BDA9FFB8ULL, 
            0x14B8C691BB38A5E1ULL, 0xE707B8CAB4886D81ULL, 0x1F862E145B75F906ULL, 0x77A8F9C302C37DAAULL, 
            0x392E704972A264E9ULL, 0x5A8CDE109D5E2513ULL, 0x12554EF1E74AD0CAULL, 0x095A9C81955AF9ECULL, 
            0x74D61A0149BBE05EULL, 0xB5E769441C857250ULL, 0x8C0FB0CDD01EA611ULL, 0xA0258C34BA9C81D1ULL, 
            0xD14DE87C2C5D4AECULL, 0xD016B3880F6DDD17ULL, 0x20808631A9E9224AULL, 0x59AE37282A7FD558ULL, 
            0x22BA8EB1FAAC0A41ULL, 0xF3D333A8C396FEE7ULL, 0xD7DD727505DFD723ULL, 0xDC02BC61E590D633ULL
        }
    },
    {
        {
            0x3B36D9F99AF4482AULL, 0x6C4BE1F5C577AE48ULL, 0x55486F2C9883F8ACULL, 0xA4399E4EC046EC4BULL, 
            0x282F3FE9CF4D3896ULL, 0x0C8D75A1A1AC50C7ULL, 0x67B5ABA3F2D4564AULL, 0x01640478FB8DE13BULL, 
            0x9A34ECC513424F1DULL, 0x735CF52B136B2E24ULL, 0xB0D66CEBFD57296BULL, 0x047C4A4A16CDE02FULL, 
            0x592DF32EB3876D89ULL, 0x4513465163E31352ULL, 0x0CA809F0C2F70AD9ULL, 0xC7249461DDB1948AULL, 
            0x8962493B3F5E38A2ULL, 0xDC6F5F44A5A9022EULL, 0xCC9477829E30609FULL, 0xE789025B995614FDULL, 
            0xD0AF82F1FC6E64F8ULL, 0x87F34E062903A528ULL, 0x7DC5477D4B2F5853ULL, 0x6813D8CFC32045F6ULL, 
            0x5714D9210BCCA106ULL, 0x54302E5BFA7659D3ULL, 0x7124EC9DFB658563ULL, 0x5839B96B97DC842FULL, 
            0x6FD9CEB2F68FFF31ULL, 0x612D024740BA050FULL, 0x0E26CBCE484D935CULL, 0xFF3746A1611C1157ULL
        },
        {
            0x63FB6F444E25D938ULL, 0x22B28FAFC83EA01DULL, 0x911CB1F673876FE7ULL, 0x3B896E2F4F0A75E5ULL, 
            0xC6A5EB2FAE035EB1ULL, 0x39824E7B713E9A4DULL, 0xD750B2297CAE09BAULL, 0x0D9BE07057C37531ULL, 
            0x56A7D64466631732ULL, 0xB5D50533A33D93ABULL, 0xFEE9E6D7CDBCA629ULL, 0x93D8EEC0AA1207C5ULL, 
            0x2E0DB654613B4346ULL, 0xF93B93F357299363ULL, 0x43547BD2970F62A0ULL, 0x003BD757E1751A3DULL, 
            0x046482B35C85855AULL, 0x82BD48C19BD2BD89ULL, 0x9DA36960511B793EULL, 0x272E7951E0B6D357ULL, 
            0x5E3801A35A1CD7A5ULL, 0xF28F7A0D826B2EAAULL, 0x12B450DC2BC84DCBULL, 0x0B68C8A37E168B85ULL, 
            0x9C50CD70FF46B793ULL, 0x2EEAB49FB3F86D77ULL, 0x4D6FE4A961B0E1FFULL, 0xADA0609476307819ULL, 
            0x6738A890BE97F16CULL, 0xDB7D6E888075D6B7ULL, 0x0A6F3A268C06A299ULL, 0x43F81A73D14C3DD0ULL
        },
        {
            0xF94DE649EADF4CCAULL, 0xB5EE1420B5A4810DULL, 0xC65681842E32FD23ULL, 0xD2333C903111C7AEULL, 
            0x4C74F60E87C973FFULL, 0xE4A2705A2D0B29C5ULL, 0x388F6D5DD9957B48ULL, 0x35551A0B42895472ULL, 
            0x525E040D9804B345ULL, 0x376ACA1E980B986BULL, 0x4865F839F2F0B159ULL, 0x6C9365E082484225ULL, 
            0x91C3001D3A11489EULL, 0x97E2E92952385E63ULL, 0xFFB6FE4F32E967F0ULL, 0xE75C29AD30303F12ULL, 
            0xF9D25CFF60B931CEULL, 0xE7EE54F46F0F6581ULL, 0xCB4E220174675C6FULL, 0xB88559D03613E59CULL, 
            0xACA8882185E920B0ULL, 0xF7C7B039912F197FULL, 0xA8E2BE42308E2174ULL, 0xA1707551B79D9E3FULL, 
            0xD789B72F7A22EB2CULL, 0xD28D0E1FB4927898ULL, 0xA2C1F64E1448A546ULL, 0x9CAF344BEFB76166ULL, 
            0x397589AEDEF0C296ULL, 0x9792A6C5B9FE6BE1ULL, 0x627A50FEB1F1984AULL, 0x6887DFCA87FBA23AULL
        },
        {
            0xEADF0377821FEBE5ULL, 0xC9029BD3722E17DBULL, 0x25231D774FA0FB74ULL, 0x51AC805BDDE1CCB9ULL, 
            0xE770400036640A84ULL, 0x1BF633ACB98A84C9ULL, 0x42FEE80A1F52E0B2ULL, 0x116A494908AB7960ULL, 
            0x323ED04640EC5114ULL, 0x94EED7667D48CAAAULL, 0x65F77452928E4E9CULL, 0xB1AD00456ED15D90ULL, 
            0x535D920B3AA5B4F0ULL, 0x0D519F30A1B40F15ULL, 0xAB5959F4336241EAULL, 0xBF9D294539EB67C3ULL, 
            0x4E3D1602DBD3F3BEULL, 0x7ADD8DFE6B656362ULL, 0xE234A3520CAA09DCULL, 0xCFED4461E41AE9F3ULL, 
            0x01168C4523279B07ULL, 0xB6A61BFE3807BE8FULL, 0x8B06CB67171E1C80ULL, 0x530717BF9013F374ULL, 
            0x920C3EA7EE338803ULL, 0x61A7492C4E999975ULL, 0x4D56A6BFC90D5E0AULL, 0x2ED929703C2860A9ULL, 
            0xFCAC3C04ED14CEFCULL, 0xAA1CB62BAE43819CULL, 0x2E8AB3092DDF491AULL, 0x2EE04AF0646C7338ULL
        },
        {
            0x0FFAC1E00A656E46ULL, 0x5D2CF0325CCE8F56ULL, 0xE633839681B6F8F8ULL, 0x01927F9A28633A9FULL, 
            0x42BF38AD22DB3570ULL, 0x5FA5CEA8DA5AF586ULL, 0x94B152B0E0576DB5ULL, 0xEA12878640083AE0ULL, 
            0x0C5B3184811BAD33ULL, 0x747C3C820BC3569BULL, 0x589C87506B66FA50ULL, 0xB2E7DFE144A55530ULL, 
            0x259F3B20756B5BA1ULL, 0x9DD1727913CA8958ULL, 0x809B3EC5012489CCULL, 0xD4E66D5A4C21538AULL, 
            0x1E85CD82A748B1D4ULL, 0x7BE1258542F14DC8ULL, 0xD6BC5D9D51100066ULL, 0xE30B7B8D63BAD6D0ULL, 
            0xA8AB4E7761D4330AULL, 0x585CA4C5B7640515ULL, 0xAD3790FEAD9EF48EULL, 0x78CEAB0F0509BB72ULL, 
            0x37B060C6F801CE59ULL, 0xA14D92CAB4426EFEULL, 0xB8972E06AE69190FULL, 0xE78A2392C320D2FCULL, 
            0x1E05FAB7D2EED3ABULL, 0x7DFFD55DBB348263ULL, 0x7C6C7B2A312E82E0ULL, 0xA3836736EBACF524ULL
        },
        {
            0x298E1681072539DCULL, 0x5D1E796D7FA3A38EULL, 0x02100735AE85D793ULL, 0x773E0C19CD588805ULL, 
            0x7D6477F1BFC574FBULL, 0xA3529AE6559951A6ULL, 0x00CC09EC8B6090CDULL, 0x214074976B62808AULL, 
            0x8324582C401AE902ULL, 0xC4D461E9B65C2BADULL, 0x3B0EE18B8842C370ULL, 0x2EE0459BA35A1937ULL, 
            0xB76CF091289F7BE5ULL, 0x45366DA7AF800168ULL, 0x81DFC3A7480909AAULL, 0x8CA7D784FC96CA33ULL, 
            0xB8980ABD301B5273ULL, 0xE598D259D033CA35ULL, 0x411AA6E03BEFCABEULL, 0x932D33CD068B1868ULL, 
            0x24BDA0F4556A5926ULL, 0x1D8D611585F29FEEULL, 0x0DA955A4A043774FULL, 0x8DE34A5800B2FD57ULL, 
            0xBDD2986EAC0065B5ULL, 0x394C10098E55E4F5ULL, 0xE54F250CE4F0921DULL, 0x89019F47BDADC0DAULL, 
            0x8F3E2C0C5D7CA95AULL, 0xEEC4CAC8150F30BCULL, 0xF2ED0D40B418391CULL, 0x6AEFB8E4766C5D19ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseFConstants = {
    0xBF1BBAF059130468ULL,
    0x1547C81B98079DD7ULL,
    0x66B690D80A9971C5ULL,
    0xBF1BBAF059130468ULL,
    0x1547C81B98079DD7ULL,
    0x66B690D80A9971C5ULL,
    0x9EC767C6BD85FD99ULL,
    0xBD9E071E964BD209ULL,
    0x38,
    0xF1,
    0x18,
    0xC1,
    0x1F,
    0x09,
    0xEC,
    0x25
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseGSalts = {
    {
        {
            0x4EDDEC6250D9C7EDULL, 0x894276212998005EULL, 0x0883BF9F132FA9B6ULL, 0x1FCF96075357EAC9ULL, 
            0xDDC0804679E9CE29ULL, 0x0F708746C1B75C5BULL, 0xCB3173202B955383ULL, 0x216831E2E6887C50ULL, 
            0x8ED2B70CBE2CFE0CULL, 0xC9C573906D37AC42ULL, 0x716873BB7F5F4A86ULL, 0xFF11B0C0B9AD26D8ULL, 
            0xF9796281E5562797ULL, 0x5EE277D8432F5E77ULL, 0xB329A25129DDA9A4ULL, 0xB1217B9F3BFD5FF1ULL, 
            0x94AC22B8EAAD28ACULL, 0x4A0BCA424FE4BD27ULL, 0x9FAA9D03350CCB63ULL, 0x655CAA68B7EFC0D1ULL, 
            0x45B2039E3236E9CEULL, 0xF56F7DF6275103C6ULL, 0x9861A977319457DEULL, 0x45A596D9B81E9998ULL, 
            0xADBD5C100B3D5FA0ULL, 0xEA4D1658BA6F6177ULL, 0x5E73B3D1D5ACCB52ULL, 0x2B5FD3CC581B1335ULL, 
            0xCF4D15C52FA18F91ULL, 0x3E1CC36C404EC9EBULL, 0x44F321FF79F22D05ULL, 0x7981BED0FDB14C28ULL
        },
        {
            0x1A5DC8ED128DD361ULL, 0x551A19A96FEB3A34ULL, 0x1ADB54EC98590787ULL, 0x317C2ADF0C180049ULL, 
            0x5A3520B1B5F62BE8ULL, 0x5F17104D2BD76A3BULL, 0x1C641F19CE6865CEULL, 0xDE34BAAA9790B934ULL, 
            0x96F86C8FB006BB9AULL, 0xA144789F51753D0BULL, 0xB0AEF199E4591619ULL, 0xF2EB81A690E83793ULL, 
            0x82486697C3DF4B29ULL, 0xA80A47A9EAEAE08DULL, 0x22930FCF14FB6374ULL, 0xBCC8D8028EA3F9A0ULL, 
            0x69EF7F3D89D7E239ULL, 0xBBE186FD3A835C46ULL, 0x50DC12100A3A0D68ULL, 0x0B66F39730EE8E84ULL, 
            0x6E79C7CEFF1C3131ULL, 0x3576EA07CDA5C822ULL, 0x1B19D59853B5C175ULL, 0x62A9ADBA66731220ULL, 
            0xE26525164F82A367ULL, 0xF952F45EB8EB7010ULL, 0x8560E0F6E5D0FC0BULL, 0xA86F03B8BE73FC71ULL, 
            0xA012BF15315DA470ULL, 0x2D54184D94CEABD1ULL, 0xB1BB0F80D8572A19ULL, 0xF7F55CA1218D379CULL
        },
        {
            0x54A021290873AC0DULL, 0x4E7386E350A4DEA2ULL, 0x21B84EF3651F9180ULL, 0x8577FBBE7A8D71EAULL, 
            0xAD4EF681A21CB7B4ULL, 0x813FEDB6DC167149ULL, 0x3CBD3F74BBCB7698ULL, 0xF4D95C862276135FULL, 
            0xCFEDC2831704A8ABULL, 0xE7EE0DB3048D9427ULL, 0xCD4DEC214AC97EABULL, 0x4AD131EAF6038041ULL, 
            0x5CD3F6AE2E789E7FULL, 0xAD3BE9842DED0F3FULL, 0x3668792C97659C5CULL, 0x550ED569082D9FDCULL, 
            0xD7629CCEE912A703ULL, 0xF85F60FB4EFBA1CCULL, 0xDE93897D09D74568ULL, 0x48644047B9FB7B94ULL, 
            0x9CAADAB926908118ULL, 0xB24C1F5A7D579E43ULL, 0xE2994AEFCCA03D2AULL, 0xF7FFBFF2BD9CE55CULL, 
            0xC15A5A54B6FBE1F7ULL, 0x721232C4EE691410ULL, 0xD68DA397521AA0D1ULL, 0xA25618DFC70D8818ULL, 
            0x183434C0AD2EDDC4ULL, 0x024E1E88A761A1E6ULL, 0x2F1C0F372F58EF5CULL, 0x9D078B730B42F45FULL
        },
        {
            0x1FCF6B23BA794986ULL, 0x12762D4AA168CDBFULL, 0x1FF5F122D4815B47ULL, 0xE21DD2F1C04E486CULL, 
            0xA304F039AEED3004ULL, 0x0227148E5B0E7AC0ULL, 0x3F58ACB1C5212501ULL, 0x09D6A492698840E0ULL, 
            0x21EB7ABF66F2BD48ULL, 0x7F7B0FD6BB9416FFULL, 0xDD9F4C8297F63068ULL, 0xCA90BDB0D86B8436ULL, 
            0x1049FD1072455CF7ULL, 0x4BEAC598FAF3148BULL, 0x622609E170DD7149ULL, 0x0809F7C119356027ULL, 
            0x7CE83D68B2C1DDF8ULL, 0xB6F4908D3076570FULL, 0x7D6E3765AF3B16D6ULL, 0xD934F14CEB6562D4ULL, 
            0x5500229C2C474DE4ULL, 0x532D2D6EDCAC9B81ULL, 0x1EE0337838BA313AULL, 0x969739AF5F36A4B1ULL, 
            0xBFB40DF05A638869ULL, 0x9CC8CC35632D9501ULL, 0xF1C2BF70C141C1F0ULL, 0x09D66EE1708A5383ULL, 
            0xF828587DA0B39BE0ULL, 0xCBE122034F04146FULL, 0x379D4A21CADD8806ULL, 0x27C32B34EC2C075CULL
        },
        {
            0xBF0F1DBCE61AA33DULL, 0xC144B759CA220EF2ULL, 0xB45EFB5ED81A4C71ULL, 0xA2841EF27BB840A7ULL, 
            0xE63DE42224D3F500ULL, 0x78EF27DA0A7DB904ULL, 0xF33833DB8E75ED91ULL, 0xEF790A6DBA6EDC9AULL, 
            0xF1B2A32A6D2B8A05ULL, 0xD6457C19DD53B1B4ULL, 0xA284742F4EE6F16FULL, 0x6E26B01B48E1988BULL, 
            0xEFA75AFDE30FB41BULL, 0x16196D70105CA73DULL, 0xAE18F3ADC8F45278ULL, 0x08F5F955420CEA39ULL, 
            0xA96ADA1553D4714AULL, 0x11ED2D4BDA4D4B24ULL, 0x7B9CBA435C1C4D4CULL, 0xB3D8092BF445A773ULL, 
            0xB5361BEAA54D4D96ULL, 0x43C17BCA5523D61DULL, 0xF3FAACE95B0DF9ECULL, 0xCECDD397A20C7C5EULL, 
            0xE24AE3E0F73C618FULL, 0xD477A68C944A45C3ULL, 0xCBA9C13D707EEA99ULL, 0x0DD6FB73F20934C4ULL, 
            0xA0E541218CDBE2CBULL, 0x681F03EF9CB068CBULL, 0x85636DB32D2853B0ULL, 0x38C1887CA14E83EEULL
        },
        {
            0xF392F8BE8E702072ULL, 0xD928B4CD8002266AULL, 0xE4388342B090F514ULL, 0x8E14C7F83339DD97ULL, 
            0x24FEDD0733340442ULL, 0xAF87E4E8398D948FULL, 0x0A76E62C24448874ULL, 0xE94A4099C762221DULL, 
            0x6FA9723BB46A1D5CULL, 0x8ECF987B343AF8E3ULL, 0x2CD97E7CCF159F3DULL, 0x09DD09CBF1044753ULL, 
            0xDCE35EF08DBCEA37ULL, 0x92C1FD0468F37420ULL, 0x52CF4A18E7F99860ULL, 0x8B2C8E0B61CEE455ULL, 
            0x9DC6C798D7262267ULL, 0xD0759E249D2BECB9ULL, 0xED6AF517C58538C5ULL, 0x4D612483F8F04230ULL, 
            0xC7765C23D3A19A53ULL, 0x0B1FA31D87DE8C7BULL, 0x1E6564C1FEBBFED8ULL, 0x34BF75D0410AD726ULL, 
            0xF2399B589EE08589ULL, 0x6E13C4DB972CCF91ULL, 0xDC4D44235D3C924FULL, 0x7566AC4CD7F7C7EEULL, 
            0xEEB60923B58DF9C3ULL, 0xBB0BDF1E6BFB3A20ULL, 0x185AEEDC2D763933ULL, 0x4995576910A2FB7FULL
        }
    },
    {
        {
            0x9D441906F2CDFBB8ULL, 0xA7189F871D6D1B67ULL, 0x8A425787EE83DD8FULL, 0x9ECA385A42AD1FB8ULL, 
            0x8E5A9C67FE061403ULL, 0x1FC2EE19687A6040ULL, 0x506217760F9B4282ULL, 0xC0134F219D91C591ULL, 
            0x72360503F06CF548ULL, 0xA7634352E0A015DFULL, 0xEDE8300FA4E500C5ULL, 0xE1C47F9DE56620E3ULL, 
            0xBFD8517FC9F3A794ULL, 0xA7E2AE7FDB0BE6AEULL, 0x3BE5CA12DE3409C7ULL, 0xC359091EE4EA3821ULL, 
            0x6EA8B45BD34967DDULL, 0x6C6985623BB5F063ULL, 0x0608A8F27AAA7F26ULL, 0x6EC0DC90D51947BFULL, 
            0xDAA97D2012C36F2AULL, 0x46C3A11F8925C24DULL, 0xD9577246B31557F1ULL, 0x56481513623E6182ULL, 
            0x9623A23EBD402E42ULL, 0xFBBA606B01917063ULL, 0x5F0AC32BE6904FF4ULL, 0x4021FDC37312329AULL, 
            0x4A780E7964F790BAULL, 0x577AA5DFB77086B9ULL, 0x89C6E4C30975EF7AULL, 0x51859C9B8FD4AF4CULL
        },
        {
            0xC0EB03B53F124435ULL, 0x2F39696BFD0762CAULL, 0x38C9032644BD5231ULL, 0x7D3E89FE4313A5D3ULL, 
            0xB8689F3B676EC50FULL, 0xCA8E523E54DC9F36ULL, 0xE66505015A5A4972ULL, 0x5357E1A4209B85F3ULL, 
            0x05AFBEC028D9F748ULL, 0x3299EC98538B6809ULL, 0x4A5E97AC51E9FFD8ULL, 0xCC31655FE629611FULL, 
            0x238B40AD9DDBB1BCULL, 0xB9008CBD35A62FEEULL, 0x861B6934DD3D5191ULL, 0x70C98A899C98989BULL, 
            0x2C0AC1F18833B46BULL, 0x81A0CE31996DFA88ULL, 0x9B5FE5EF59A11232ULL, 0xE78273C4A11F8517ULL, 
            0xF92067790BB4E832ULL, 0x1214DF46F4A26784ULL, 0x1870BB6C5DCC1FBFULL, 0x568B8E1A7103990FULL, 
            0x649B4C298734D81FULL, 0xBA6BF009FC14E187ULL, 0x043B0327755D98DDULL, 0xF8D2ED0522EE561CULL, 
            0x3607032A6FEB35B6ULL, 0x00CF6B84FF1B8C33ULL, 0x8E84EF5CED8FC5C4ULL, 0x8C5671F30ED11390ULL
        },
        {
            0x9613434F1A3D5425ULL, 0x60509C5BC8122381ULL, 0xF29E71B4D05782C3ULL, 0xACEF2A5EACBB341DULL, 
            0x541C985F99D7B62AULL, 0xD5482878D4F5517EULL, 0x92E66C657B522AE1ULL, 0x5521757E9256104FULL, 
            0x7BA798274B88AD77ULL, 0x853FAD4EB32C9602ULL, 0xF43F4F6B34B8A797ULL, 0xD4BE823A6559AD5BULL, 
            0xF1B125D3E20FE4D5ULL, 0x08650D0385FBB34DULL, 0x44FA6EE25AAEF2DEULL, 0x216406B0F607C608ULL, 
            0xAEE800349FD1EAC8ULL, 0x881F862EAD2B8152ULL, 0x719CA3F2BF4C21B9ULL, 0xC3847F34C85AA71EULL, 
            0x0F6B73EE6EA3BA03ULL, 0xAE824B9455DF1DB3ULL, 0xA3694B508BAE4E95ULL, 0xE9F3887B3A2F5E42ULL, 
            0x8F289C9FFCB4352AULL, 0x1854D4AE76D71960ULL, 0xDDF36DD0390DA480ULL, 0x7265ACE75FE1272CULL, 
            0x4DC5BD331AABDEF2ULL, 0x386B1D30DBE85BFFULL, 0xD5CF8D5F34BB2FC1ULL, 0x5E9C4F9AB85AAEB4ULL
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
            0x9AD3A94343C0571EULL, 0x0853BAAE555746E8ULL, 0xADEAE4C8BD920821ULL, 0x6F3CE6D9B28BEA53ULL, 
            0x70E21ED1AE58C434ULL, 0x2625C792434DF0A3ULL, 0x53C3E80BE9146A2CULL, 0xA91903101A9D0AF2ULL, 
            0xFDC09D027048198EULL, 0x540B5129423F07F4ULL, 0xA2589831B5D2B9F2ULL, 0x30F9B6F48809CE83ULL, 
            0xBDBEAAA33D8C0722ULL, 0x7BE685EBE4AEACD0ULL, 0x991AE2A462DCBD3FULL, 0xC9F9C6397192B9ACULL, 
            0xB97DDB477CE5E552ULL, 0x572E95D1ACD9FD9AULL, 0x5FA1420A72E02213ULL, 0x7913F2CC60F68150ULL, 
            0xD6F0C32DA6306985ULL, 0xFFDD4B3C738BCD3DULL, 0x77E0AEEE09C015E3ULL, 0x068B206F959B3B50ULL, 
            0xA7A80DD2973E49E0ULL, 0xE605E3582C5CCEC5ULL, 0xE9CB175B6E8982E1ULL, 0xA0ED126CE44FDD0BULL, 
            0x8EFEA1346C0C0181ULL, 0x8931C2B3A422B23FULL, 0x01305C19BCAFE3D6ULL, 0xB65453E6D3616580ULL
        },
        {
            0x90ECAD77377EC932ULL, 0xFFB4E58E7C013BB2ULL, 0x6C011A3FFAB1ADE3ULL, 0x75FD3D0D558C320CULL, 
            0xE9D7AE95179344E9ULL, 0x60393BBA3E5D05C3ULL, 0x191D57ABAFD2E702ULL, 0x6D77BF045937E522ULL, 
            0xADD9895E379349DAULL, 0x179E1749533B3992ULL, 0xB21433E8CCE0F395ULL, 0x9F423A18ECEC0417ULL, 
            0xD1AC7A6642C6D40AULL, 0x6D8337ED8209CA39ULL, 0xE491C636E6B0E852ULL, 0xF49562C52995AEB4ULL, 
            0x77665FFF710D1DF5ULL, 0x99C94AA3C0159294ULL, 0x7CF9ED40B6EB6C01ULL, 0xC31353A0612AB941ULL, 
            0xAB46C48C6B6D0007ULL, 0x1546E2C43C33FC70ULL, 0x38E85A078CB99D02ULL, 0x5ADD4D4BAF8EE020ULL, 
            0xF631BA7225F5E0D5ULL, 0xC525E985F9839EF2ULL, 0xC260B8307F9E5738ULL, 0x864DD82FA3A0FBBDULL, 
            0x9B37FA2542CC9C11ULL, 0x1C4A75EEE1F1021DULL, 0xC1DA6C4351AEDA08ULL, 0x654CC20CEE22885DULL
        }
    },
    {
        {
            0xF91F6C94F76547C7ULL, 0xDB4021E52DFBAD13ULL, 0x7D8896F96A380554ULL, 0xD950748925B94DC4ULL, 
            0xEDADED3C4B731154ULL, 0x197BA85BB020E146ULL, 0xB53D443CA9D8EF80ULL, 0xA1D24E2C1430BD2DULL, 
            0xE1669B070F7CE4C1ULL, 0x46CCA6A493F238F2ULL, 0xA7C0305FEA15688CULL, 0x87A420D86870E811ULL, 
            0xF507117515082949ULL, 0x2F0AF61907F42C5AULL, 0xA3102D67BC6BD980ULL, 0x8B8BBE5B983233FDULL, 
            0xE406EE41B3CDA814ULL, 0x84BF4136D9923C1CULL, 0x6DFD7BB91CBFAF4EULL, 0xE13A448982F2148EULL, 
            0x588EF8F72B1F804BULL, 0x8F4F12774A4A5714ULL, 0x316F9E7A6CAF7553ULL, 0x27ED97B8559A618BULL, 
            0x2B455FF1CFFF2DFDULL, 0xA300EB8481A692B9ULL, 0xCB06A4F1E8DDDAE7ULL, 0xA08B08642BE72C97ULL, 
            0x593AB69BB0677A3DULL, 0xD65B2D3530D78B62ULL, 0x4F68AD58BDDED44BULL, 0x884B485EA928E5BFULL
        },
        {
            0x698D301D807B733FULL, 0xDDB8C1A6F5DEB78EULL, 0xB4384245BDA4E4E8ULL, 0x26FA113A3F7696B4ULL, 
            0x8FA4888C8B467FA4ULL, 0xD1CF9E5A5F5432ABULL, 0xF0C911BF9E7F3431ULL, 0x3BED87186CF7C617ULL, 
            0xF1D36FED7896343DULL, 0xC3F0FD8A619344EFULL, 0x91EF0289F534302DULL, 0x2C4F6918CA23C87AULL, 
            0x7285DDE7F33EE241ULL, 0x951A56056727DC7DULL, 0xBB440BA95527E6E6ULL, 0x3CC855728E5C4BB9ULL, 
            0x8A8CAD7D4232DFB4ULL, 0xD92C129609D42952ULL, 0x16620F61F53063B4ULL, 0xF5DBC2B6C04925E4ULL, 
            0x31BADB9C983423A1ULL, 0x82098DEADC66669CULL, 0x7AB83CF297AEA841ULL, 0xA971B37CB2F50865ULL, 
            0x47E44A4FD1BF3E3CULL, 0x9D2B783B6FC94BBAULL, 0xFD3BF57D14C8EAD5ULL, 0xCCA510FBB259EE0CULL, 
            0x9D36CD50819E4CCEULL, 0x14DC0F739BC951ACULL, 0xD9729AE3E29B850AULL, 0xA1C26B59D472ED01ULL
        },
        {
            0x9C54DDF973A382F0ULL, 0x25D3A6256CEDC7ECULL, 0x001D5EA9C343454DULL, 0x863C6AFAE57BB905ULL, 
            0xE296703B36E9B038ULL, 0x3D44C32CCF1691DCULL, 0x36911AF25E541458ULL, 0x2AA3B7EEC941ABCCULL, 
            0xB23335181187750CULL, 0x2550D502437A3BF2ULL, 0xA76E57826DE8D7DFULL, 0x19E58F84D0F54777ULL, 
            0x70954B1230729ACCULL, 0x5AE2D5F080DB32E6ULL, 0x7D4806D885D90B71ULL, 0xABB06653ABFF0967ULL, 
            0xADB1B47DA6D43EDAULL, 0x43E4482A8F155856ULL, 0x97DC2DC6E091F7FFULL, 0x9C892EB3928DB747ULL, 
            0x546D01A8E18285E8ULL, 0xFE449FB88FC96588ULL, 0x0C5A5F4414EC6E0CULL, 0xB63BF8F2EC47C778ULL, 
            0x45A89564EB12451BULL, 0x164BB7D5841DEC07ULL, 0xC5366161B1D8C21DULL, 0x003EBF0FA41D57EBULL, 
            0x23BA25A6A3E126D8ULL, 0xE37A28C43B2660F4ULL, 0x31E7DDA9999019DBULL, 0x85795E16425D54BEULL
        },
        {
            0x0467008A0AFBEACAULL, 0x3AAA751452E1E063ULL, 0x6F835CABB8ABD8F5ULL, 0x97EC297467DD8029ULL, 
            0x6C1AB5D74D79E030ULL, 0xA75F9492BB1EEAC9ULL, 0xAC3C0A7808EC7246ULL, 0x37C1FA17377C16D8ULL, 
            0xDFEC5D50B51D90B1ULL, 0xA700F9DB64A03229ULL, 0xCF0FD4B20D470DD2ULL, 0x1062BA8B0B597852ULL, 
            0xDE8928BCAF9E4FA0ULL, 0x4BD23C2C0FA99E05ULL, 0xA234733B3FF3343CULL, 0xEA1F104C5AB43F31ULL, 
            0x8C1CDD1D0B552492ULL, 0x54D5078B93630604ULL, 0xE8C572DA8FF98977ULL, 0xB07B1E2F0E189D5DULL, 
            0x0C6B9C1AF332C5BAULL, 0x596120640988B1B7ULL, 0x3E7BF445555130AAULL, 0xA9BEF2AD3451A56BULL, 
            0xD38456359E646A36ULL, 0x715D0A89AB87E660ULL, 0x716CD0C004C70A04ULL, 0x1EDB1933D0235AA6ULL, 
            0x572E160BDABD035CULL, 0x50470AE1B8F7D466ULL, 0xE3818DF5CBF3303FULL, 0xD0771EC25BCAD1E7ULL
        },
        {
            0x2E52C409FE06AD65ULL, 0xB543DDBB2E8716BDULL, 0x7539F9BE238228CBULL, 0xE4AD7CDAF1E044FCULL, 
            0x9ED9A51DE0A017A8ULL, 0x38D712B5C80F2DF1ULL, 0x1DB59836273A9C02ULL, 0xF19927329DB307FCULL, 
            0x9C4EA77194FCBBCDULL, 0x738CC7013D654B24ULL, 0x9B19EA64950698AEULL, 0x5B3E6EF3A05D9C3CULL, 
            0x2A91572227E91425ULL, 0xE61A9AFC1BC14549ULL, 0xD878CBCEB9F5934AULL, 0xEEE298FB0489358DULL, 
            0x04FBE65A6027349CULL, 0x266333C5B5A065B9ULL, 0xC7AFBAABC26F4FF5ULL, 0x1AEFB54B89615E37ULL, 
            0xDA9C4FD991212856ULL, 0x3342006C21F3B837ULL, 0x176F1F6083A37D18ULL, 0xEE16C9BDCE9B8597ULL, 
            0x917765E5C5B42EE3ULL, 0xEE69C7476A60F34FULL, 0x21597CCD6698390CULL, 0xEC948E4A25D911E0ULL, 
            0xD7373E2A396A2908ULL, 0x18B9CDF3A7C6240CULL, 0x23AEF90233C11279ULL, 0xAEE4C7B8250248DCULL
        },
        {
            0xCE11D2D88092606BULL, 0x88BDE2C3B5203123ULL, 0xEA6CADEAB83B979FULL, 0xFA0E0C1E71347C8AULL, 
            0x80210E8C6979FB14ULL, 0x38D97E5CF2693F12ULL, 0x92A766C1291C5C7AULL, 0x755183F18E2A9A4CULL, 
            0xB1B577D1C4DFD1C0ULL, 0xD2DE965AD7D38373ULL, 0x92FEBF59CF7762A7ULL, 0x9355416BCE7A1E73ULL, 
            0x8A82A3242B2483B7ULL, 0xB77586991339A1DDULL, 0x2386FD9D442E38B9ULL, 0x8ACA7CADBE7B2701ULL, 
            0xA70C211E36429364ULL, 0x8FDCD2125EBB308DULL, 0xE8343B9B32AF0560ULL, 0xC0D78B8DCF73A3ADULL, 
            0x6005117A78CCC9B6ULL, 0x24E20A3992D14097ULL, 0x51386AF9FED0AB80ULL, 0x784DD5589E618211ULL, 
            0x824DAEC6A32E17EAULL, 0xA3A327E7420D2353ULL, 0x72946568594B22B2ULL, 0xCC99CE2750C9794DULL, 
            0x13E217A7B36EFCF1ULL, 0x8FFF1437A3FD6478ULL, 0x7DC6F29F7937C49BULL, 0x161A4A74BA0A5883ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseGConstants = {
    0xBF01067C2A06F1B9ULL,
    0x8D538CC33DB9938FULL,
    0xB8AFE6081A7D5F06ULL,
    0xBF01067C2A06F1B9ULL,
    0x8D538CC33DB9938FULL,
    0xB8AFE6081A7D5F06ULL,
    0x412F2E12BF743FA3ULL,
    0xE557F1B5B5A8710FULL,
    0xA6,
    0x5A,
    0xA1,
    0xD7,
    0x10,
    0x6F,
    0x04,
    0x3A
};

const TwistDomainSaltSet TwistExpander_Altair::kPhaseHSalts = {
    {
        {
            0xD7A7C9C12CF9E643ULL, 0xAE3E4F23A769C1FEULL, 0xAF28C3B38C0F2C21ULL, 0xB5422F4EA4C44DA7ULL, 
            0x269150B884B277FBULL, 0x2CC70E58564E7896ULL, 0xEF7D09CB880C8121ULL, 0xA4FD9D7A0CBEDE18ULL, 
            0xC3BC996410E288AEULL, 0xA786EE3C704728D7ULL, 0x326A15649A77887CULL, 0xE9EE7646EAE574D0ULL, 
            0xA539138ED2D1F8B9ULL, 0x302CDDAF04C4568EULL, 0x99881210898C783BULL, 0xD7613ADC39A052B2ULL, 
            0x61ED005BEE49B259ULL, 0x0630290464D2230FULL, 0x30E94A661DDD6CEFULL, 0xCD50C2149DB73C2EULL, 
            0x7F80F23753FCA9BDULL, 0x90362F49F22EAE45ULL, 0xB6A347EABCA41ED8ULL, 0xA225C83AAA93844EULL, 
            0xC439AB1BB6810A8FULL, 0xB507F92FFBE1B072ULL, 0x2D9448A6E6AA73D1ULL, 0x8B8CF21F79D22E6DULL, 
            0x58FA196A86D5C36AULL, 0x26D77591DED0EBFFULL, 0xB029731472695E9EULL, 0x9B9267EF73A8A55BULL
        },
        {
            0xDE30614D38BE6878ULL, 0x5C57137674CA778DULL, 0x6C86B75DA752D52DULL, 0x72F6439AA0C142A7ULL, 
            0xAF754E6177725831ULL, 0x295D01CFAA23BA9AULL, 0xDA785C1416B45119ULL, 0xE000F8BE4A18E087ULL, 
            0x9E54C706726916F1ULL, 0x967192CBD13347DEULL, 0x5709053EAA4EC736ULL, 0x6AF120EC091CC4F7ULL, 
            0x1220AFED686817C2ULL, 0x316CF1D1A5D10383ULL, 0x6CBA8F7813E9EDD6ULL, 0xAEB739B8FE0CA48EULL, 
            0xDD44AB19F4606DDAULL, 0x0180D2C6888D39BBULL, 0xAAC8534CE9425FF5ULL, 0xD29D573F7149173BULL, 
            0x38D73733DC9063E1ULL, 0x98EC9B4FA729B68AULL, 0x55670AC2B98DE653ULL, 0x93BDAED4B4CBEA20ULL, 
            0x7E6CE8BE6F426CD8ULL, 0x64AA2E83DCF69D31ULL, 0x0CBAB8A8BB2A2FA9ULL, 0xE18125054B7DDA79ULL, 
            0xC940932007DF4835ULL, 0x1E192BC510CFB28BULL, 0x7ABDD7491584B8F6ULL, 0xB004A737E7EEBA1CULL
        },
        {
            0x865FE4D362DC2D11ULL, 0x2FE247BC274387C2ULL, 0xE3BFD8190E00A151ULL, 0x8A81A3F168569A27ULL, 
            0xC984FF3C10080F74ULL, 0x5B60D3B4ABAFBBE8ULL, 0x862C2FF900422BA1ULL, 0x37E07F04A992FDF6ULL, 
            0xADC6154A0C6B1F8DULL, 0x511BA8DEEE855E02ULL, 0x3BDD48DDA9278EDDULL, 0xCF0A138F083E7237ULL, 
            0x95D34CBE05CEEE28ULL, 0x75384404E133BF57ULL, 0x59F9D35D60F59530ULL, 0x997F39F54DC8D6C4ULL, 
            0xCA13183ED6159BFFULL, 0x724E53090088CACDULL, 0x32AFD6897AEE7D8EULL, 0x97CD40051E525AB3ULL, 
            0x48D97EA6D48D7F7FULL, 0x6D35E2C4C64C52EBULL, 0x7215033E65D39B28ULL, 0x23E98F083AD53FC1ULL, 
            0xCBEA7CA19A191356ULL, 0x2D27C82046FCBB69ULL, 0x6B559FE27A9F4AF6ULL, 0xCE3778ADEBCC165CULL, 
            0x0BF3695DE4D65753ULL, 0x70C6899C15272203ULL, 0x040969E87B193050ULL, 0x74459BF9F232599CULL
        },
        {
            0xF292E247DED23A8CULL, 0x6E904710AD602427ULL, 0x0CF97BA80B3D527FULL, 0xACF51B37203546D4ULL, 
            0x64D747122C2C8BA7ULL, 0x05DEE9022492169AULL, 0x2BE2D152587AAD29ULL, 0x9B82DAE9C0C5A0BFULL, 
            0x90AAE579204C93C7ULL, 0xB4CD6125CC7F7CD0ULL, 0x9A4E80B1C54864DFULL, 0x154A735C46D8E36DULL, 
            0xCFBFA8A15E327C3DULL, 0x9A285B10EB890939ULL, 0x66A05E599FEDA5BBULL, 0xC2D732F06FCB6B28ULL, 
            0x1B60FA20A889C12DULL, 0x299C7BF9061D1082ULL, 0x84DAEA75E9A8216AULL, 0x3DCD0FD8D04DB5C9ULL, 
            0xBA86CC263B6AB5E0ULL, 0xF6681A60C843BFABULL, 0xA26A90B992213AFCULL, 0x14DB29208A81DE8AULL, 
            0x885187776E6A2A78ULL, 0x3D2B7E75F8E8C604ULL, 0xF6D1603B7AD59C5FULL, 0x302EF6677473AD67ULL, 
            0x52D9CE581D49CDBEULL, 0x40ACA169E7CD760DULL, 0x96C2E58F0479E18FULL, 0xD0B6A3CB66FDB6BDULL
        },
        {
            0x4C5E4B101895455FULL, 0x389DDF297EE6F400ULL, 0x37556ED58B954D90ULL, 0x511EAC4E0861B6DDULL, 
            0x270AE87278960547ULL, 0x2EA3E0C0BD5B875DULL, 0xF646E9633BE6EE94ULL, 0xC5675D5CC1BFDAF3ULL, 
            0xBFF8AC0F27B330DDULL, 0x1E2CCB9CFB1CDF46ULL, 0xC1D63F7157F040D1ULL, 0xC6E89348301AA11BULL, 
            0x2BB032911B81808DULL, 0xC238C5DBF0BF6E57ULL, 0x97C0175C0C5B82DDULL, 0x236426FE4AB0F829ULL, 
            0xD157A49BD188233DULL, 0xC6B39E8F999F9526ULL, 0x23F46E8F342D97C1ULL, 0xE07FF02C2CD746FDULL, 
            0xD741B0A4C59CA64CULL, 0xD386612F7610CE66ULL, 0x839E9B6EB4A68042ULL, 0xF3E56911B9A161B0ULL, 
            0x34E0E421456326DFULL, 0x6CD1458BC2E21E92ULL, 0xFA17558D45D86372ULL, 0xBECCA3DDEFABE4E2ULL, 
            0x9D755521E1E435ACULL, 0x1D2802D6231C8287ULL, 0xB439F483296A003AULL, 0xE87D04392D866CE1ULL
        },
        {
            0xE7289B826B5ED62CULL, 0x90CFD462BD8B36B2ULL, 0x68EC38C9B4688C65ULL, 0x50FB349432E2D461ULL, 
            0x593C8F6568594276ULL, 0x8FB33921C078C93BULL, 0x9ADE3C0C46DD95B7ULL, 0xB99188D78C1A8D55ULL, 
            0x0A608475BBF58AB5ULL, 0x5ED3288B4C138B24ULL, 0x280097217FBCAEB6ULL, 0x25E09C3C13B7BA77ULL, 
            0x49AF7B863FC32733ULL, 0x722E08DB4F62A19EULL, 0x3C421D918FF87C0EULL, 0x59A12ECFF9918424ULL, 
            0x04504C4934DCF14EULL, 0xB863D96FC70B2274ULL, 0xB89D4A279A2D697CULL, 0x4961248E2C03A499ULL, 
            0x6709E102FF74B567ULL, 0x03555029174E774BULL, 0x7D36A729E138FC05ULL, 0x8EA99320E17FADF4ULL, 
            0x0BCA7059C98714E3ULL, 0xF3C0E67DFEE009B8ULL, 0xA2263891D482044EULL, 0xE82CFC579C4EE410ULL, 
            0x1F1397E900FAB69EULL, 0x2A53147EC09BC056ULL, 0x88922B0C68466AE6ULL, 0xC5CB937A8B51E402ULL
        }
    },
    {
        {
            0xA44670BD285E5250ULL, 0x7A9DD625FB5FE138ULL, 0x6F2C34B2E7A7E2C8ULL, 0x36002A3412645AE5ULL, 
            0x131956F1F153EE62ULL, 0x4DD65BAE1E4AC6FDULL, 0xEA5E37B9FD3EC99CULL, 0x1654D53EBB32FB78ULL, 
            0x77D02C053B3E304AULL, 0x7B722DAFF7EB2983ULL, 0x2FF789F68E570DE8ULL, 0x35B8E581348D3557ULL, 
            0x7FE49748499AC739ULL, 0x9B2C7AA5EF80EB58ULL, 0xE1FFE40F22195623ULL, 0xFD63D18ADAB7BA56ULL, 
            0x72B5D994AC3B7C31ULL, 0xF02616BC91E7DBB6ULL, 0xFDB7208B46B3AE77ULL, 0xF5542206A5D219D7ULL, 
            0xDBEB285DB83D7B9BULL, 0xF55F85178279D09BULL, 0xB4B91C4CDB38488AULL, 0x9173F4E7E138A0ADULL, 
            0x0A8D0B9450BF569FULL, 0x2142C80DCAACDA47ULL, 0x27C41BE083216DDFULL, 0xD5B412200A823F22ULL, 
            0xAD9A7557D05FE6F2ULL, 0x4E17EE45BC2C7FC6ULL, 0xE79CB8489958A4EFULL, 0x8B7016A1B84FB43BULL
        },
        {
            0x72829B53986F7A8EULL, 0x3BA99AEFF9685D07ULL, 0x034D39F7152D3D4DULL, 0xA9D990B6DB054110ULL, 
            0xF993B25FF8790603ULL, 0xE0A2EAD897E783D8ULL, 0xA0456C36FE7F487BULL, 0x23EFF172BB478D34ULL, 
            0x56F06E50B5F825D4ULL, 0x9F3CDB51B3C5F4DBULL, 0xC464EAC1CAE04A90ULL, 0x68093A5792BF3C11ULL, 
            0xFD431BCE7C485C6EULL, 0xAE655A63B879EC35ULL, 0xF645BF5EDF75015BULL, 0xD7DDEA3C1671AFAAULL, 
            0xCF879FE2D8F0379FULL, 0xC02F7167B00E3942ULL, 0xE9CF07919F6CE836ULL, 0x31422EE45D3AB3A4ULL, 
            0x3EDE23D52F1FA04AULL, 0x7E8D09E1E30375ADULL, 0x47D6A88CBA063B3AULL, 0x1F3AB8322A5CAA56ULL, 
            0x2F69B92056E1C652ULL, 0x192650CCAD58D5C7ULL, 0x5BBBAC1F030C2E62ULL, 0x16FA91F50D7E7F47ULL, 
            0x4D2ED806A2001230ULL, 0xC0C4372398EBBE37ULL, 0x2345B0C7D24FD643ULL, 0x9A0B8BC73FF572E6ULL
        },
        {
            0xD23C1F86A1169BA2ULL, 0x3B43C6132A67FAA9ULL, 0xA051ACD1772A5992ULL, 0xCA4FA78105A13E48ULL, 
            0x89DDD456BEF41677ULL, 0x2B9CBA69B1F328C6ULL, 0x33EF0DABD8FB32F7ULL, 0x030A2F3845FFB6D4ULL, 
            0x0A0CD1F50702CE5AULL, 0x32C062D5C33FE1F5ULL, 0x19D6E6D415A877C9ULL, 0x503AED2F5C6FA2C9ULL, 
            0xE1EFCFC285E4021CULL, 0xF7E97685D01E27D7ULL, 0x4F798AC77E2276E3ULL, 0xB641F76527B1E1D1ULL, 
            0x617405DD79428849ULL, 0x5CF55691D3FA4506ULL, 0xE8D8C543FA10D429ULL, 0xD29A9FBD9C97C34EULL, 
            0x6C6453B9915BFE00ULL, 0x09259491E9A20978ULL, 0x06D868AF1D0E87EBULL, 0x6CD5278D44BED06FULL, 
            0xD317EAB810521CC2ULL, 0xB61FA53176DA7877ULL, 0xDDA6EAC3F9DBB42EULL, 0x920D13C1C2FFCCA7ULL, 
            0xC1A2AD69732B7398ULL, 0x94994357C5F6C75FULL, 0x502A29597BEAF48EULL, 0x649FC2088C484E0AULL
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
            0x6DE6C7EAAE64A028ULL, 0x99D35499268B0946ULL, 0x4A62F59D7CBC2838ULL, 0x0742253C86024B78ULL, 
            0x878EC502B71FD73DULL, 0x7901F349C55BAFF8ULL, 0x1ACEBEF43F094042ULL, 0xB95B68367948CF16ULL, 
            0xE307DD3B1FBE5EF5ULL, 0xDEFE8F10B3B8C3EBULL, 0x430400298B1E2EA6ULL, 0x00FCFB34FD28264EULL, 
            0x1DD0A91CAEB36381ULL, 0xCCA50D8BEDE2BBE2ULL, 0xC7072D9FDDCAA927ULL, 0xFE585412E12E42CEULL, 
            0xF586AF03FB89A3AFULL, 0x0EAEE6876B13B047ULL, 0x60E91B79F87A7A56ULL, 0x8F012C661C9F0C2AULL, 
            0x2D79D2D68B49850DULL, 0xF5CF37CE3826C901ULL, 0xCE283C8AFA831217ULL, 0x3C82C633A0421481ULL, 
            0xE7DD5B72489FDF37ULL, 0xDE91CA54CA4E9947ULL, 0x6B1081285EEBBD00ULL, 0x3E408B314D223691ULL, 
            0x5506CD0A28AE0A44ULL, 0xE24BF257BECCE79FULL, 0x2CAA9B036E4F2D8EULL, 0x10D8FE56723E2A4BULL
        },
        {
            0x7A9AEE391811FB29ULL, 0xC7D48F51285A345CULL, 0x3F92B98A9423E2C2ULL, 0xBFEEB121C353DE10ULL, 
            0xAA8BFC525CA9416BULL, 0xEA0F00CBEB1848E0ULL, 0x28DED242B9998229ULL, 0xFFAB120423DD2290ULL, 
            0x3BD565CBAC89F9EEULL, 0xDD94816472EE79F7ULL, 0xF2EAC9EFC122FF53ULL, 0x629008BF390F73B2ULL, 
            0xA2E713F3DDF915C4ULL, 0x314D6D35DF64DD30ULL, 0xAA67EFAF5CC152D1ULL, 0xC8C60496F60F660EULL, 
            0xF0B821D2325F0AADULL, 0xB0BA89673DFAB3EEULL, 0xCFD48671EA44C08AULL, 0x0CB647B4BE69581DULL, 
            0xDBBD7AA7B59629D9ULL, 0xD46F11601D005388ULL, 0x46599772C2E8DCF8ULL, 0x87C2CC2F152CA679ULL, 
            0xA3134B5309B4E186ULL, 0xEA1190814884A7BFULL, 0xC4E96C4098E361CBULL, 0xAE022D6D7E36A74FULL, 
            0xE46BFA4CE82E4892ULL, 0xFDB81BCC0BD9F569ULL, 0xF66AEC605ED36591ULL, 0x0CB243666138BDAAULL
        }
    },
    {
        {
            0x9ECEC5CD17C8B05BULL, 0xDCE8D436021AFFFBULL, 0xCF4C7B9241E54423ULL, 0xFA201C5FA8442974ULL, 
            0x4F521FA4481651D3ULL, 0xCD8F9E1F38341641ULL, 0x8BFC63221AF66D8FULL, 0x2E206535B7982FC6ULL, 
            0x3107179F29CF4EBBULL, 0xD7C23C540094FCE3ULL, 0xC5A146E17C62FD1AULL, 0xF273D83D656CA0BCULL, 
            0x0E62F6AB2AB60428ULL, 0x1D33546DBB355718ULL, 0x423D859D5C6A9A8FULL, 0xF609E05D2532D2EFULL, 
            0x976FAFFD42BAC67BULL, 0xB389F86016851B30ULL, 0x01D0B58EBFD934A7ULL, 0x1DD10D37755D1D51ULL, 
            0xA85C8A8173FE6D87ULL, 0x4ECA2D85C8F2DEF4ULL, 0xCC10525607CCAD0EULL, 0xC6E48B69E9995170ULL, 
            0x13AB267C353EF75FULL, 0x25DC09B1DFFCB6F1ULL, 0xE8BF566631E6D5F2ULL, 0xF3151716291EFAE4ULL, 
            0xA7AF9BEF923C2999ULL, 0xCE7314B13D55A9E5ULL, 0x0590471BA20D6B65ULL, 0x6594D89102D474EAULL
        },
        {
            0x31757658BA5618D6ULL, 0x3528AE7FAB8B28B4ULL, 0x722B539C2B69CA0EULL, 0xC6EF1CA6BC5C9221ULL, 
            0xDD5E0F956669EA86ULL, 0x62552AFEBD872CAFULL, 0x6939CDBF3856F86DULL, 0x636FD3F2DC1C0E67ULL, 
            0x4E3598BE88FD71A4ULL, 0x2B545525BFD473DAULL, 0x50FB42B923F9018CULL, 0x3C7D07C11E1106ECULL, 
            0xD0BE3432370F3DBDULL, 0x6B2B43AE89390F85ULL, 0xA378696E91747280ULL, 0xCB8CD8D9457EC30CULL, 
            0x5E1C476D58E24D2AULL, 0xC209F7541FDB4B45ULL, 0x8ACCBC6127AD14BDULL, 0xC2F58111F5C460F5ULL, 
            0x2C5FDD420081B53EULL, 0xB606977DF1498B83ULL, 0x2DFDD627FBFE8BA8ULL, 0x2A45004C3037F773ULL, 
            0xBE26667F4C95E810ULL, 0xDE81CAF47CAAEAC7ULL, 0xB26147499396E077ULL, 0xB9DEC0F8051379D2ULL, 
            0xA91416C6494239A6ULL, 0xFDCE28D18132A4B9ULL, 0x35E315BA9E9F346FULL, 0xAB3B758F7EA0DAEEULL
        },
        {
            0x7433C39F5E34CB21ULL, 0xE7BAC3155BDC6E3AULL, 0xA65562B71573F980ULL, 0x88BB7E3DB79234F9ULL, 
            0xB77B33284B518E64ULL, 0x92A6515332140E05ULL, 0x0E9209E193DB0D1CULL, 0xDAD8EB2BD98F1BAFULL, 
            0x2D61620C1EE19A43ULL, 0xEBA1EFBDA56D0D28ULL, 0xC83B5403CF88B75FULL, 0x7B34F3A352E7145FULL, 
            0xD0D20C044B140DB0ULL, 0x4D61E6B3E577C4B2ULL, 0x44765073604B1862ULL, 0x6854C86CA5AC0F84ULL, 
            0xAD16D4F469F4E3CDULL, 0xF94FAA7F95EA930EULL, 0x3B533F5EDF4F5885ULL, 0x49EC967936E1FD0AULL, 
            0xE4680C99E6AE03E3ULL, 0xD810885425C5361EULL, 0x29BB9FF775BE0128ULL, 0xCB232ED7358CDAFBULL, 
            0xCF6462ED004D7917ULL, 0x7228330763339E75ULL, 0x71617CE558DDA3AEULL, 0x4CCDA3AF9AC32A9BULL, 
            0x03FC36827F0C6086ULL, 0xC55CA9D2D0342176ULL, 0x739593505C6782FCULL, 0xB8D06A8D5378095AULL
        },
        {
            0x1C3D7D7592A65987ULL, 0x83A79009D1EF6BEAULL, 0x7734864D15A1AFF8ULL, 0x3C0EC6BFB1F5F488ULL, 
            0x0ED8B01A23E5FC7DULL, 0x0D509B24C4BA6F0FULL, 0x1FDF359AB86F3531ULL, 0x046877C36C8D6F29ULL, 
            0xFCE50980FA0EF826ULL, 0x67D0A231D4870FCEULL, 0xEF199E963FAFEDE1ULL, 0x0A037868E22E233BULL, 
            0x534A08E145D320E1ULL, 0xC14B97CA36E72810ULL, 0x37341E098EA694BDULL, 0x41A92176AFA3D09EULL, 
            0x2E2B7B48CBDFBEF5ULL, 0x09F9B75F7FAF4C32ULL, 0x1F83A442AA008BCAULL, 0xBC0B5AAD81DE1A68ULL, 
            0x3EAA4D33EBD3D1ACULL, 0x67CFEE9BA817007AULL, 0x3D24F24B969F45E7ULL, 0xCAC9D3759DCE9532ULL, 
            0x11AB2383F5C739BDULL, 0xDE20141412579EF4ULL, 0xE7510171166BBEA7ULL, 0x68C8BBF98101E746ULL, 
            0x83094902B0F9A075ULL, 0x9FBA29AFC6AAF6A3ULL, 0x21DB6D5D5BDC12CEULL, 0x466F77C0F286256CULL
        },
        {
            0xA2882C45268D7955ULL, 0xC14714FC46B25BFBULL, 0x8479A473F5B4580CULL, 0x1A7691B0419B8C13ULL, 
            0xA372530B88BF3D22ULL, 0x3C850894BAD6C783ULL, 0x993B255437E0F72CULL, 0x657D08820878DA19ULL, 
            0xA43BF85FFA52741FULL, 0xDC9117BEB958EB14ULL, 0xC96C444552C4BDD5ULL, 0xBF4FAEC636DFA91DULL, 
            0x3DD4C70D25A40362ULL, 0xD2902173786B8097ULL, 0x554FA1A8E497B2FEULL, 0x8FEA82D5A7D8CA90ULL, 
            0xB6FA3A74AA382AE9ULL, 0x4F36DBC2B2D0342AULL, 0x233916D19BF6569CULL, 0x848938C7B18071A0ULL, 
            0xD8FE87BB013990CBULL, 0x28DA088304CCB3F8ULL, 0xF50B8305923B486AULL, 0x5929DC655D983EEFULL, 
            0x4487ACFEE4A23C97ULL, 0xABD35AF2F73F638EULL, 0x99B853FCD15BB54BULL, 0xA093FE7D8EB54393ULL, 
            0x3E39BAE8A63566C0ULL, 0x180734C8A9F3FBA3ULL, 0xDD098EC548CDF21DULL, 0xFDA0F9DBA683EBABULL
        },
        {
            0x7E399108D0D1DB5FULL, 0x5D95F7734CFA0A40ULL, 0x0D243469FD6E361CULL, 0x7EF2B4A3CFBB56E5ULL, 
            0x154496045768000FULL, 0x32847510CBCEF927ULL, 0xD492F4BF66896509ULL, 0x6381E6F1D7115C3DULL, 
            0x00B7609C381F0E75ULL, 0xCDE97999D1CF7AB0ULL, 0x4BA55681C84D2355ULL, 0x66CB9918307B164CULL, 
            0xCB2975A24E923BBFULL, 0x1FE65EDDF8FF4756ULL, 0xE1F7F6AAAC911539ULL, 0xC82A11BB582F6273ULL, 
            0x5404648D174D8E46ULL, 0x1D6332015808003BULL, 0x7018DC0A54814E66ULL, 0x568DD5940874519CULL, 
            0xCC1E8DCCA82F2372ULL, 0x7CB870FA68B8242EULL, 0xE42E07F0CDB31FCEULL, 0xB79E56AE8687F954ULL, 
            0x23B16ADDA1E8FCF5ULL, 0x152B60728109A4DFULL, 0xB6003CD6F05CA244ULL, 0x19765AD0FF83E37EULL, 
            0x5E5807D96CB679AEULL, 0x7E86F58AA36A595CULL, 0x060B5425C26ADC61ULL, 0x9F7390C0EFE577EBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Altair::kPhaseHConstants = {
    0x68CD218257958EBAULL,
    0xA0E12D96F670C451ULL,
    0x26C44F5171DA8D75ULL,
    0x68CD218257958EBAULL,
    0xA0E12D96F670C451ULL,
    0x26C44F5171DA8D75ULL,
    0x686E4D49B1F5EA32ULL,
    0x97DD8AB495979312ULL,
    0x9C,
    0xB0,
    0x88,
    0x1F,
    0xF0,
    0x7F,
    0x73,
    0xCF
};

