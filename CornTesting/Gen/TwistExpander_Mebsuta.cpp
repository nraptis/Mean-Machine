#include "TwistExpander_Mebsuta.hpp"
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

TwistExpander_Mebsuta::TwistExpander_Mebsuta()
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

void TwistExpander_Mebsuta::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9558A327B0B9468BULL; std::uint64_t aIngress = 0xDBD02D1E2D7C7319ULL; std::uint64_t aCarry = 0xD6F2EEB3E2F68DC5ULL;

    std::uint64_t aWandererA = 0xBDDACB5F1913C3A7ULL; std::uint64_t aWandererB = 0xB1B7604B55F8CA0FULL; std::uint64_t aWandererC = 0xC95CA688360934ECULL; std::uint64_t aWandererD = 0x9453D3DB450BC97AULL;
    std::uint64_t aWandererE = 0x9653E04F49186071ULL; std::uint64_t aWandererF = 0xE7FB35DC5A859D07ULL; std::uint64_t aWandererG = 0xB17C8CF90FAA52F3ULL; std::uint64_t aWandererH = 0xCA4C167ACC9191CDULL;
    std::uint64_t aWandererI = 0xDFD95DC2557584C9ULL; std::uint64_t aWandererJ = 0x85A46FF139E36577ULL; std::uint64_t aWandererK = 0xA644A14CDCE70232ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9718758277445153148U;
        aCarry = 11498594433942568366U;
        aWandererA = 14265157628610727312U;
        aWandererB = 12459636132208765259U;
        aWandererC = 11317692063772602063U;
        aWandererD = 12024379630398381040U;
        aWandererE = 18435656271693871134U;
        aWandererF = 17891148942093387673U;
        aWandererG = 9667524281834613180U;
        aWandererH = 9360331207075374879U;
        aWandererI = 11618360661174363151U;
        aWandererJ = 10383605147828587830U;
        aWandererK = 11433958252032825929U;
    TwistExpander_Mebsuta_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mebsuta_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mebsuta::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xDC028322A010FAD0ULL; std::uint64_t aIngress = 0xF291C9DE351DD407ULL; std::uint64_t aCarry = 0xD7A4546C42C042EFULL;

    std::uint64_t aWandererA = 0xA0F203F40DC9FE74ULL; std::uint64_t aWandererB = 0xA19460D951FB7076ULL; std::uint64_t aWandererC = 0xA82D03F64F508F65ULL; std::uint64_t aWandererD = 0xCCA702F12B622B81ULL;
    std::uint64_t aWandererE = 0xE6B47366A2C94293ULL; std::uint64_t aWandererF = 0xFDAB44C15E47592FULL; std::uint64_t aWandererG = 0xA3C1AA31990FD0DAULL; std::uint64_t aWandererH = 0xFBA7E8C088B73759ULL;
    std::uint64_t aWandererI = 0xD0FD6270753235BDULL; std::uint64_t aWandererJ = 0xEA94280DAFE50ED0ULL; std::uint64_t aWandererK = 0x8A85025543859745ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12883582056813095945U;
        aCarry = 13637604515185290515U;
        aWandererA = 12925519425947635848U;
        aWandererB = 9690017608919523945U;
        aWandererC = 13952268189128028227U;
        aWandererD = 15086132550642555251U;
        aWandererE = 10971301727808493352U;
        aWandererF = 13283979064404941807U;
        aWandererG = 16413985313854347667U;
        aWandererH = 13079376057359194610U;
        aWandererI = 13835652521779792931U;
        aWandererJ = 9892567042271628053U;
        aWandererK = 18328284854268957295U;
    TwistExpander_Mebsuta_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mebsuta_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mebsuta::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x9D0DA750E3ECD067ULL;
    std::uint64_t aIngress = 0xE6E10AA875E67786ULL;
    std::uint64_t aCarry = 0xB1421369F1CC7160ULL;

    std::uint64_t aWandererA = 0xDE82C9033A6C64D6ULL;
    std::uint64_t aWandererB = 0x87080C350E129FECULL;
    std::uint64_t aWandererC = 0x81459E62F90CC5A7ULL;
    std::uint64_t aWandererD = 0xA03DC928BAC8E34FULL;
    std::uint64_t aWandererE = 0xABB20DDC896F3C03ULL;
    std::uint64_t aWandererF = 0xC2B84FEB98163E8FULL;
    std::uint64_t aWandererG = 0xF0A9E258CEAF5DB2ULL;
    std::uint64_t aWandererH = 0xE0297291BCB722BFULL;
    std::uint64_t aWandererI = 0xDC165D3D73ADC400ULL;
    std::uint64_t aWandererJ = 0xC58079F01C7F461DULL;
    std::uint64_t aWandererK = 0xCEB1E6596D2EF829ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::AES256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
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
    TwistExpander_Mebsuta_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Mebsuta_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
    TwistExpander_Mebsuta_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mebsuta_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mebsuta_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 17 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1817 / 1984 (91.58%)
// Total distance from earlier candidates: 29246
void TwistExpander_Mebsuta::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1702U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1204U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2012U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1119U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 247U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 407U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 327U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 34U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1837U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1240U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1199U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1730U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1015U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 732U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 3U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 950U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1151U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 224U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 45U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1153U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 705U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 131U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 162U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1115U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 814U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 785U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 796U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 937U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 448U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1926U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 136U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 620U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1192U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1773U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 526U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 601U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 15U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 528U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1919U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 630U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1454U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 693U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1398U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1731U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 704U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 81U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 178U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1411U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1577U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1183U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 333U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 211U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 867U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1096U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 823U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1170U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1918U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 945U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1375U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 145U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 773U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 964U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 109U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 734U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1249U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1042U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 918U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 90U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 489U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1052U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1868U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1615U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 581U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1584U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 361U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1658U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1169U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2023U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1568U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 940U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1297U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1145U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 146U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1499U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 324U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 879U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 194U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 710U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 308U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1633U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1869U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1485U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1762U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1647U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1910U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 449U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 29U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 833U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1347U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1670U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 815U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 920U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 925U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 663U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 64U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 939U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1959U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 606U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 654U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1070U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 623U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1589U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 656U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1216U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1562U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 270U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 988U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1853U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 9U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 534U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1828U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1603U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1163U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 352U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1458U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1048U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1955U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1862U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Mebsuta::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x8DE86588888F6203ULL; std::uint64_t aIngress = 0xE01155E5838C9AD0ULL; std::uint64_t aCarry = 0xF11765170F09AC3CULL;

    std::uint64_t aWandererA = 0xDABDD4C3549F3156ULL; std::uint64_t aWandererB = 0xC3F896F8AEE714FEULL; std::uint64_t aWandererC = 0x83AB79D1DF992B75ULL; std::uint64_t aWandererD = 0xA3BF7549C41EEA90ULL;
    std::uint64_t aWandererE = 0xDD050E0D0A909EC8ULL; std::uint64_t aWandererF = 0xEE565AC2B24D4031ULL; std::uint64_t aWandererG = 0xB064969E8FAEBF11ULL; std::uint64_t aWandererH = 0xF10F0AB7927509BDULL;
    std::uint64_t aWandererI = 0xC817A81E2F0D470CULL; std::uint64_t aWandererJ = 0x978F630176F239A1ULL; std::uint64_t aWandererK = 0xDA60A26F571F2805ULL;

    // [seed]
        aPrevious = 14899900569058509995U;
        aCarry = 10538294410748076806U;
        aWandererA = 13376326532291102268U;
        aWandererB = 12356043621253281343U;
        aWandererC = 17088389532923485860U;
        aWandererD = 16285490496272488015U;
        aWandererE = 18381949496008025420U;
        aWandererF = 13750476457678616996U;
        aWandererG = 13882457411175664393U;
        aWandererH = 18112789506614977795U;
        aWandererI = 17367560956423382767U;
        aWandererJ = 15601525688323407601U;
        aWandererK = 12310740997063542827U;
    TwistExpander_Mebsuta_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Mebsuta_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Mebsuta_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Mebsuta_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mebsuta_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 17 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8752; nearest pair: 481 / 674
void TwistExpander_Mebsuta::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4331U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5024U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 601U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6529U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2775U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7814U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6245U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7686U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2098U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2003U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 380U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7933U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3091U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5474U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6939U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3129U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1744U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1993U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 501U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1691U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1138U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 170U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 809U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 233U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1862U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1728U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 244U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 256U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 19U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1592U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 572U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 116U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1102U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 76U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 897U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 17 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8737; nearest pair: 481 / 674
void TwistExpander_Mebsuta::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2056U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6378U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3807U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4685U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7840U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3222U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 508U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5836U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1282U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4266U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4082U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1153U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4406U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2106U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5247U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2399U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1498U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1892U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 82U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1857U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1384U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1355U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1069U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 536U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 99U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 342U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1550U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1787U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 645U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1405U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 866U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1568U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1801U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 568U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 18U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 930U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseASalts = {
    {
        {
            0x620DFE1B6F629E5EULL, 0xC9398B3CC5BA3898ULL, 0xF93005DFCAD6CFC1ULL, 0x24FEB9B409CCEC13ULL, 
            0x3A56F4CE93B97DA6ULL, 0xE294E48D5B99841EULL, 0x21619B41F05C9F37ULL, 0xC51B6120CB622A80ULL, 
            0x8601D9D7FA79B7A5ULL, 0x1A6D712F7316523EULL, 0xA56650D612703ED5ULL, 0x3AF777FA053BA71FULL, 
            0x9C156B8963BE452DULL, 0xB6E8D5849DD1D67BULL, 0x186510891E6DDDFEULL, 0xD76EB0C9DD4A8ADCULL, 
            0x938DBA240E5D4A70ULL, 0xD65F77DD97368A8FULL, 0xE64E160B7257E028ULL, 0x75193BFD0CE294E6ULL, 
            0x457A428FD1556F39ULL, 0xAC7806A1BAF818ECULL, 0xA5027E74E2144C04ULL, 0xF7015B4F7D06AC4EULL, 
            0xCD3340535715B2FCULL, 0x93CAADD66BB71240ULL, 0xEA0162B2CFBEB5A6ULL, 0xBCDC0716D8137DCCULL, 
            0xD12CC90D0C22F10EULL, 0xF7EF5FEF6904EA8AULL, 0xF34841E2BEDCF562ULL, 0x2DCAA6E901658DBDULL
        },
        {
            0x929E71C8DA59B534ULL, 0xF2027106AB02DF23ULL, 0xF7B348294F65B5E6ULL, 0x2955C23B83556133ULL, 
            0x865F746C808F70B6ULL, 0x0492D0B2D1E86E58ULL, 0x9AA0360277F9B37AULL, 0xFCDE5E67EBF42CB3ULL, 
            0xE311651319FC7E8DULL, 0x30E1FED373B100D7ULL, 0xD695FFEAACA7C20EULL, 0xB4A09CB2792B4093ULL, 
            0xA8A7F12A20AD008EULL, 0x12B2251C6CAFE9C6ULL, 0xAEB6BBCC6A504A7AULL, 0xE684B39FD2705E77ULL, 
            0x5E0A084FF239AEC7ULL, 0x1A54291CC3F762F3ULL, 0x37FFA10DA49DF17DULL, 0x2E57D6ED90680CB5ULL, 
            0x665A891B58317CDFULL, 0xFDD97140AE98F84BULL, 0x44A32B0D5F5953DCULL, 0x7CEA3DA44E2F78BAULL, 
            0x8BDADEEC9176E5DAULL, 0x023754D4A06CC03EULL, 0xAD7F32D38B26D370ULL, 0xD1C87420F23EA97FULL, 
            0x038B338E9751657CULL, 0x3161EF1102BEE5E1ULL, 0x009EE1588F3FC9B9ULL, 0x55A7EEF33FCAEC36ULL
        },
        {
            0x975DF15098A9D213ULL, 0x92BE266B0CD80DB1ULL, 0x705A657878AA7985ULL, 0x611A457675B94472ULL, 
            0x839D60AC36AC80CDULL, 0x46AA1661EDF14CD4ULL, 0xFAEFD263BA4C3FDCULL, 0x7B862CF35F0F60DAULL, 
            0x1F4DAECEB0FC40B5ULL, 0x8E68BCFA91A93E4EULL, 0xB3C853D98886DA7FULL, 0x4C6331AAD2E3DABDULL, 
            0x19A6DEF6024E34B9ULL, 0x73BC3FB14B8236EDULL, 0x5D2DC5E14BABF5DBULL, 0x4F58E43A5C3A06DCULL, 
            0xEB5AC5783BF714F8ULL, 0xD8495A8DE23B6181ULL, 0x8BA4E7458CF0B725ULL, 0x1866375EE22BD39FULL, 
            0xDA675B329BE2F69BULL, 0xA6630AB5C5CBD63CULL, 0xDBF98CAA87988352ULL, 0x14DA6D7DC22580ECULL, 
            0x173A783D4120B905ULL, 0x55F13ABBC4C4CD4EULL, 0x1660D866A54B2D11ULL, 0xC14105E369CBAB20ULL, 
            0x0940EA3BC54F025AULL, 0x21E09438DCCC433BULL, 0x8527FE69F84657B6ULL, 0x71A0E91149D9B08EULL
        },
        {
            0x64AD98FA2E6AF373ULL, 0x4D6579126DD2B64BULL, 0xCD8BE489AC675BB4ULL, 0x719E50E31A2106C9ULL, 
            0xFBDA37D2AB2AFDE2ULL, 0x1D5A199C9E945D32ULL, 0xADE7367BCC7AF7C5ULL, 0xEFBA8CB5E94DA493ULL, 
            0xEDF3CB2E149E25B1ULL, 0xE6FE6A0E9999F5DAULL, 0x5CFC235A7B7E74C1ULL, 0xDB8A73936F5925FDULL, 
            0xEA4B945DF8EE2A24ULL, 0x2104E20938A209DBULL, 0x854B564B78EF0CF2ULL, 0xEFC39355740BDD45ULL, 
            0xE415AC52576FC961ULL, 0x5ECD885AEFBEC549ULL, 0x00E8F1EA5469E498ULL, 0x24B2F8064CD93D17ULL, 
            0xB791051A2AD425ACULL, 0x8C55857E27B12922ULL, 0x802426ECB4F8E8ADULL, 0xA3B0A1D0F20FD808ULL, 
            0x75E2500B5DB7B850ULL, 0x5776B706F5E62C9DULL, 0x7912CB1E1D6B5FE3ULL, 0x07B85E56003AA4CBULL, 
            0xA234E1704D17F517ULL, 0x0A2466097167C220ULL, 0xD100DB058AFCB499ULL, 0x76B2C06DBFC33763ULL
        },
        {
            0x2B4336AE6F09848AULL, 0x16000208B272C50FULL, 0x570EE9757A4864F3ULL, 0xD7E011871889DC49ULL, 
            0x981EBB13261DD16CULL, 0xDD146224876E27C4ULL, 0xC55185AF564B0E9AULL, 0xB5A0F2DFB4F88EEAULL, 
            0x6B46203C7AF1C509ULL, 0x10E27D61E0461A5AULL, 0xCB559FF3A2E6AFFDULL, 0xAB985B937261C14EULL, 
            0x76492930E796260BULL, 0xD2B33F6AD2168C37ULL, 0xFE379AC27335827FULL, 0x7C0DBD6B39AFBC47ULL, 
            0xFB4635545A79F249ULL, 0xD5EA90BEA6F6DBE4ULL, 0x5DC6BEBC9F482A57ULL, 0x0C356BA5FF28C74DULL, 
            0x4BFD39198328E63BULL, 0xAC8AD10EC0761C3BULL, 0xAD02B0DD4663AAEFULL, 0x0F825B31EFFA99B0ULL, 
            0xEE56AC7C605E178AULL, 0xF3B02422EC2251AEULL, 0x0DB0CDF8B0364244ULL, 0xE31E7F463CF70C81ULL, 
            0xAC60D3DB5275F16BULL, 0x21E4D1451EDE8111ULL, 0x2D8616A39D1F1DC5ULL, 0x2F8A8450D8473A95ULL
        },
        {
            0xDE892BD9866F1B05ULL, 0xEEBAEC6A801460CCULL, 0x737A50DA76B02AA8ULL, 0xB3DE8F8037696BA6ULL, 
            0x637CCB78A4554E24ULL, 0xE51482C1C3BC5F84ULL, 0x0D14D2DC2A8D6A0AULL, 0x89369B075CDAC16CULL, 
            0x4FAA2E73D10E2807ULL, 0x1A60FAA31A31A356ULL, 0x2C97033F49A55258ULL, 0xF5521932743DD85DULL, 
            0xF1372D91267261B5ULL, 0x5DFB816D4EB1E0EFULL, 0xD58F4A9DB48E7AA9ULL, 0x7E07AEAE1084490EULL, 
            0xB3A7EC82FD3B7101ULL, 0xBC0BDF4BA52B5559ULL, 0x6C7EF8C53BB39238ULL, 0x2549ABC1273D2DCAULL, 
            0x0C980F871CA409C4ULL, 0x7F88F95101E888BCULL, 0x67B7F195C05225A1ULL, 0x13BFDC8C9021876CULL, 
            0x652F9977CE11F90CULL, 0x6D82A55079B40BD2ULL, 0xC8ABEF9D42C4DF48ULL, 0x883FC5A22BD88118ULL, 
            0x657874C3C38421CDULL, 0x0120B7AC51460E50ULL, 0x4A5B5310E6F8C868ULL, 0xBB93A3F5AA439E3BULL
        }
    },
    {
        {
            0x82F8351F655D0EB1ULL, 0xD51ACAE39F9E517CULL, 0xCFFC73909B438D5FULL, 0xB8C65B013D005BCAULL, 
            0x0261840EE9573798ULL, 0xE484DF6074EE7732ULL, 0xA0F39B0B9FD674B9ULL, 0x8D1A72494B525F50ULL, 
            0x01AF7F4D10FC290EULL, 0x46E9324AB5F8110AULL, 0x922F1CDCFD8E540BULL, 0x5212B4A8870C453CULL, 
            0xF3934E893B40B990ULL, 0x06EE5D8DF39B638AULL, 0xA7D5F51C7596FD6EULL, 0x99EAB35BEBEC153AULL, 
            0x68E4473C58986F86ULL, 0x9F2DAB9FCF6A2944ULL, 0xBC5C915BFECB3422ULL, 0x477B33F18937A4DEULL, 
            0x4572D6FFDECDDED5ULL, 0x2EC1E4B5709D48B6ULL, 0xBEA6EE5253B70DDFULL, 0xF04D0AE7A9C5F561ULL, 
            0xC1E66B45D8D471C6ULL, 0xB39FCE4E4004B4AEULL, 0xB8A926AD8873B12EULL, 0xB6D6708644998020ULL, 
            0x507D51F12EBD60E2ULL, 0x11E926178CB69EEBULL, 0xE93D3AF45E40F440ULL, 0x45F1DEC43A4DC5F9ULL
        },
        {
            0xB9CC7E5B08C592E2ULL, 0xBC82BDDAA8119389ULL, 0x104F3FB92B07998AULL, 0x2065FEB4895A56CCULL, 
            0x2173B252DE8AC6EFULL, 0x793B202EB2C89B4EULL, 0x97FDE49F3A20C883ULL, 0xA8108D323A5D508CULL, 
            0x9A34D3F6FAF6486BULL, 0x3ACD98352A8F1540ULL, 0x3D2F1144A2D15AF4ULL, 0x27159B611943F4E7ULL, 
            0xEB34548E8A2E7758ULL, 0x4202DAF4DE2EC701ULL, 0xA84DE7E674DD160CULL, 0xAFEE741D600B98D8ULL, 
            0x14C6508130DA23FBULL, 0xA56ED14D3FDA1C94ULL, 0xB649709162F86407ULL, 0xAD136E552C04CA5EULL, 
            0x539FBE2059A7B533ULL, 0x27CA3329FB15B158ULL, 0x301CC9D35330EFB3ULL, 0x00204D62F26FD188ULL, 
            0x6EFD1AD580C5B4E5ULL, 0x40DBA003E36344F8ULL, 0x91E0712B2276F11BULL, 0x416F42BE606D6F68ULL, 
            0x00C5CE4FB4FB32EFULL, 0x0A29E6B70DC24822ULL, 0xDCF3846133618CE9ULL, 0xCAD703BC6FD78A37ULL
        },
        {
            0xB97FBDFCDAB70621ULL, 0xFF595D99634659F0ULL, 0x3B6EECA0B08CA57DULL, 0xB0FC5DD525AF142CULL, 
            0x6F0A552C8F958827ULL, 0x6861581BD73949F2ULL, 0xDB8BF5E0F88D380FULL, 0x35C016B017BF9FF2ULL, 
            0x22FACB44712C2C95ULL, 0xA784908C5848B5B3ULL, 0x452201CC6007550CULL, 0xCA248BBC966C04AAULL, 
            0x4622B6FDA6545026ULL, 0x797E8F34FEE6DC46ULL, 0xDF673E7860B42555ULL, 0x8A309D1A5A7C0178ULL, 
            0x69433BD5846226BAULL, 0xC187F85DB9429537ULL, 0xC13C9530E4F45326ULL, 0x27F2AF7775A163A3ULL, 
            0xAD4BFE176A57E3C2ULL, 0xB221FA9B4FFBBABAULL, 0x46A4337923F3A545ULL, 0x3287F4164AD6BCADULL, 
            0x04A5B7570D98C91DULL, 0x45AD41590FD5F584ULL, 0x8024DCB34B6D09E5ULL, 0xD0656E6C01F2C789ULL, 
            0x8BD18D6DECD10DB6ULL, 0x86E0C0CF7A20E896ULL, 0xD1C56224E1A23A36ULL, 0x2C2C2B8371D0FCB5ULL
        },
        {
            0xB6EAC64BE1D763A5ULL, 0xBA0DCC2BBF8F1275ULL, 0x80621DFFC61F8879ULL, 0xF8998D99468B5FDDULL, 
            0x15061EFBC8078672ULL, 0x5936D3D3C421C2A4ULL, 0xBD1AC17F1186A317ULL, 0x605E75EB854D4D51ULL, 
            0x429FEA592C05D3BFULL, 0x56BCAF0598B2BEF7ULL, 0x1141907CF0E25CAFULL, 0xAC541AD60EBC8296ULL, 
            0x853166D73BA7CE3AULL, 0x569558AA7AA03B13ULL, 0x6ABBDA62CF8D7EF0ULL, 0x81731E7D4BF25BFDULL, 
            0x1ECD2E382659FC9AULL, 0x2D1DA623F0B5DD18ULL, 0x0238E1448DA9341BULL, 0x3D407FC77F271CCFULL, 
            0x99089505FCF10E20ULL, 0x31F46492A1CA19F9ULL, 0x6FE3C6AF1D30158BULL, 0x4EFA8145FA918375ULL, 
            0x4AF8C7F4517E8A3CULL, 0xE01AD59DE33881A2ULL, 0xE552D0547B2A0A72ULL, 0x33814F79778CF93DULL, 
            0xBD46CF372D27E13CULL, 0x698DF3A878BAFFD4ULL, 0x01FD2AEA6873F4A5ULL, 0x0BA616AD064A4443ULL
        },
        {
            0x5A52A03BE874A15CULL, 0x50AD68FC5BFCBF71ULL, 0x472B303BF9F5000EULL, 0x388B4557CCD7576FULL, 
            0x3E7947BF4F6D4EA8ULL, 0x27571AE93BF0E186ULL, 0xBE16EDFDF1F1847CULL, 0x1FFFC9E2FFC8CDA5ULL, 
            0x8F5D2910B534FBE3ULL, 0x8C107401EE68C232ULL, 0x59914A9C825459CCULL, 0x75E2509DE4663EFBULL, 
            0x51DCA63C913D14F9ULL, 0x707C5089E0183B6DULL, 0xE4D8A6EBE33E7255ULL, 0x1CE509E29D1AD177ULL, 
            0x1C7FEF044E8B353DULL, 0xD7E8AEFA7EE18AD1ULL, 0xD3D228C9763CF368ULL, 0x1DBC8A60CB7A65FCULL, 
            0xE6478902DCD102F2ULL, 0xE57E62F5865668A5ULL, 0xCCBE1FD61ED5A492ULL, 0xD75C141D1C68FA1BULL, 
            0x832EE516695FF19BULL, 0x613D3A7887B52D92ULL, 0x4A743B0B1BB33C51ULL, 0x6B0C4A132C8AEC0BULL, 
            0x44548ACF8B1A5F2DULL, 0xD8AA7EB96BE94CB0ULL, 0xE21DE4765B0F5245ULL, 0x6F6737E43B16D828ULL
        },
        {
            0xBD0C6A5A1149F7AFULL, 0x03AE1BA36F1958C2ULL, 0x827E1EF147339378ULL, 0x9A52DD008CE48B4DULL, 
            0x5FE7718B44706DCEULL, 0x34CF999EF9AD0A7EULL, 0x52A7BD661522D33AULL, 0xA9BFDCE30FE80C09ULL, 
            0xD54357D12C6E129AULL, 0x492371E9E8DA3DD7ULL, 0xB5890F00B235EB98ULL, 0x8F50E0A4EF3B94ADULL, 
            0xEC7606D8F62F444EULL, 0xB7DECD980937B85CULL, 0xFB58CF124A4AB898ULL, 0xDFECBFCE28A82331ULL, 
            0xC155DE4622372AAAULL, 0x1A48541845CD590DULL, 0xAE7F4193C3947273ULL, 0x907CE5B05109794CULL, 
            0x43B82F9A3D517270ULL, 0x38F54E2946A4A491ULL, 0x8400D938D6C9414BULL, 0x572BF87DB28EDAF4ULL, 
            0xEA48C6F35B1270CBULL, 0x57A3E8D4E6CF4F4EULL, 0xFD3FE5F70AA711B6ULL, 0xC62596E19EFDEF44ULL, 
            0x132909F39F09D2D9ULL, 0x0ABEBCCF19664AF5ULL, 0xA30E7FC3849B4FBEULL, 0x03D3D9810B4F7B48ULL
        }
    },
    {
        {
            0xAA7FABB9A43FFEE5ULL, 0x8F6B266E031E17BEULL, 0xA4BFBD4E026C63D7ULL, 0xFD93191A5D7D8A0AULL, 
            0x24FB025DF352F433ULL, 0x40BF93ECED472615ULL, 0xC83E3A61A86448C0ULL, 0xDFC67686C296C6BBULL, 
            0x539EAC7B0689D36EULL, 0xD35C97A0E970C1A5ULL, 0xA89AA7ABBE7BD484ULL, 0xADF4AD863E8786E8ULL, 
            0x44C149CEE8C168B0ULL, 0x1B247907660FF2A3ULL, 0x6A8E09FBD7F2587DULL, 0xD1AE6E122473FDF7ULL, 
            0x70E8C24A4C40AA06ULL, 0x5314D877A4327E38ULL, 0x9CE57F711124FBC0ULL, 0x2339BE520B43FB16ULL, 
            0xECD97339862B5A3CULL, 0xF7CEEE4640961F69ULL, 0xA6FEAF838455F566ULL, 0x9F36D112BDF78377ULL, 
            0x3C1DDC254DD14286ULL, 0xDAF0A56C798056A3ULL, 0xE21C154B3125C9AEULL, 0x6627A64815C4CC70ULL, 
            0x389530C2C55AD87CULL, 0xE7CDA76A74C8EF9DULL, 0x780A785473EE34D2ULL, 0x40367C7D8C0F0959ULL
        },
        {
            0x8C12EE9643363FB3ULL, 0xA85BF9D02BB6D1F7ULL, 0x08C350A2199972FDULL, 0x875BC1D863B9EE43ULL, 
            0xE1B6AAE21266309FULL, 0x7A6399FA48E40431ULL, 0x41DBDB730991B5DFULL, 0xC3D29D6644CECF8CULL, 
            0x9916B195114B51B9ULL, 0x605BD2EA7BBDE3FFULL, 0x5F653BB6CD94E205ULL, 0x90F8092E41030844ULL, 
            0x8619C04B7703FFD3ULL, 0x84F87513A4A1FE06ULL, 0xA69625357EC09376ULL, 0x20C5974B6D73109EULL, 
            0xD4608C33951476A8ULL, 0x2B6D70E9209290D4ULL, 0xBC17666313B70EC1ULL, 0x60678B238CC56052ULL, 
            0xD8ED7D9C946D572AULL, 0x4E75C107B0285A90ULL, 0xABAA89CD91287C52ULL, 0xDBC3FAF4D8BC0130ULL, 
            0xF525C5CDEE4C9B53ULL, 0x98DB5BC3F06B803AULL, 0x7F2F9EE71AFFD31CULL, 0x8489BC908E5021D6ULL, 
            0xF499B63231C89F85ULL, 0xE7D5C48598B36872ULL, 0x835DE0F3496AA770ULL, 0x30D785DECEA7FAA7ULL
        },
        {
            0xEB3DC36FEDAA2D6DULL, 0xF9E079489DB0C232ULL, 0x1D4752799E7DB090ULL, 0xE00637CA49164B18ULL, 
            0xE329088A88F4C5DAULL, 0xDC8A0F756E5FBC21ULL, 0x153B525EA72FBCF0ULL, 0x1375924A18343A74ULL, 
            0x31F801D9BD55C0A0ULL, 0xD27E7D71B050EB43ULL, 0xDE1651FF2EAA9B78ULL, 0x42A9775156EBCB83ULL, 
            0x2175D367AD4BEEC6ULL, 0x2F4667E2023EF706ULL, 0xA2B1273D05883C25ULL, 0x179BF1CF8CFC9A99ULL, 
            0x9922931623E4BE4CULL, 0x78ADB71BBABD57CBULL, 0x5313E55C0D7D41A0ULL, 0xB30A86DF79FECF78ULL, 
            0x53210A88DEAD888EULL, 0x3CE34FC04D37B2B2ULL, 0x35D3EF340D257B19ULL, 0x732F4C0D8B0AFE74ULL, 
            0xF53EC1656B55AB27ULL, 0x3D9621A9D8D92B21ULL, 0x80735D411F41B164ULL, 0x36BF30E26F2DE59FULL, 
            0x88341FBB9689DDF9ULL, 0xA16BAC77817A1199ULL, 0x3EFA821683A74B68ULL, 0x14F3FCEBD8AE3F7AULL
        },
        {
            0x33E88EC8FE660585ULL, 0x4F07E45DA4D31A8EULL, 0x430C710FB6080E53ULL, 0x548C6EA2F644E19DULL, 
            0x43246065E6269818ULL, 0x96170B01474F6217ULL, 0x1E73C1C27DE98F77ULL, 0x53BDB26BDAC4BCEAULL, 
            0x19E3BEA054F99F71ULL, 0xDF11D1B990593CA1ULL, 0x10785ACE3BBD09DFULL, 0x9FE422FF252D7A32ULL, 
            0xC74E5BF07F15F986ULL, 0x11C29C20ED71976FULL, 0x2C8F49F4B6BAFE01ULL, 0x6099E52E7B819C61ULL, 
            0x5886864A6B0A5400ULL, 0xF45D7B588C906DABULL, 0xAB9F39E5D565028BULL, 0xF2290A85E9A8A1A5ULL, 
            0xDA74A0865C7D097EULL, 0x3B009A63310DD03AULL, 0x97F06D9119C6C342ULL, 0xA5699983B93E839FULL, 
            0x509A9D0593F6F94AULL, 0xEB8AED06AC128443ULL, 0xCA39CEE76073C696ULL, 0x09451C4AB224E55AULL, 
            0x96C37A975DC232EBULL, 0x8A2E13BA74A8F739ULL, 0x21D12B64FA536288ULL, 0x339086F83746ED7BULL
        },
        {
            0x2B904D0F25B397D2ULL, 0xBBDAF1773B430276ULL, 0x859A98BFA0569F4AULL, 0x7B0A61EF5D91727EULL, 
            0x5BE4C1E6096FC461ULL, 0x21938170000F0B0FULL, 0x695AF1AEF291B579ULL, 0x87FCF542C9219069ULL, 
            0xFBCD674281FE651DULL, 0x60503FE87EC84AC2ULL, 0x8EAAB0E51C14EA3BULL, 0x7CFCDD3862512892ULL, 
            0x8AA8FFE6F8A7CAD3ULL, 0xF2995FEFDC026AB6ULL, 0x0615328B9F4F2EE5ULL, 0xAA6B1D25EA6AD797ULL, 
            0x8C6FF0827B9173ADULL, 0x6969DB4DE746B8F2ULL, 0xA33FB94CD36D9EE4ULL, 0xF4F0D8387C481D74ULL, 
            0xFCDD4F59F1828C95ULL, 0xBB1270218E895114ULL, 0xBD3B358B94653098ULL, 0x59DC6C296020731FULL, 
            0x3FD9C8A2E6B1F2AFULL, 0xD08ECF14530412DFULL, 0x3EC5ECA845D3ED6BULL, 0xE5610F310B0E8B50ULL, 
            0xB465160B5CE6852BULL, 0xCDA8806F02C2E895ULL, 0x5173DD47D6EAF3EFULL, 0x55CE155CC285A3FCULL
        },
        {
            0x81320B7DA8DE23B6ULL, 0xBE6FF84A910B80EEULL, 0xAA63A1423B27FF9EULL, 0x8323F9BCC80CF771ULL, 
            0xCD7F88057FFBAB6AULL, 0xD9107F76046DDDC5ULL, 0x4808CEA3535F3145ULL, 0xB1F7E17C8A0EC2F8ULL, 
            0xC549867D219C0694ULL, 0x2FECA2BC6E4AEA46ULL, 0x328502D21CEFE520ULL, 0xACFFAEBA5A45DEC8ULL, 
            0xB464640065FBCAD5ULL, 0x8A2B9CB799981AB1ULL, 0x7EEED1FC1D765A35ULL, 0x6F51F00EECD6A6EBULL, 
            0x7514F97F1DB30CD0ULL, 0x6918A235794BE02BULL, 0x33A1B94DA32AF216ULL, 0xCAD8D7CC9694D169ULL, 
            0xC02DC53F284F6BF2ULL, 0x043CAEAECAEC4918ULL, 0xB0011E7C7AE8D88AULL, 0xB52700B1CA6C3BF4ULL, 
            0xB245FD3DBED20057ULL, 0x3E922EEAFBA920DCULL, 0x006C598ADB2606EBULL, 0x1F8068AD65A3ABE8ULL, 
            0xEF15EEA49C98F614ULL, 0xE083BA456FDC7FBDULL, 0xE286BF1D1D3DB3D4ULL, 0x1F93A0B539F76868ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseAConstants = {
    0x97BD57CD5CCA5784ULL,
    0xD1DFBD6B8E931207ULL,
    0xCA75169F1FAC3E3FULL,
    0x97BD57CD5CCA5784ULL,
    0xD1DFBD6B8E931207ULL,
    0xCA75169F1FAC3E3FULL,
    0xDE35FF15E2C3894CULL,
    0xEF2C52069FA46196ULL,
    0xA9,
    0x7C,
    0x3C,
    0x23,
    0xB4,
    0x33,
    0xB4,
    0x8A
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseBSalts = {
    {
        {
            0xE890FD3D1AD04276ULL, 0x108D50FBE40216B8ULL, 0x3C0824E90500ED9FULL, 0xAF9D6088CA910D83ULL, 
            0xED230B1F14030CBCULL, 0xE8C1FAF5C078D580ULL, 0x9B1062803EB77662ULL, 0x53776A3E556D2FEFULL, 
            0xBFCBF37AC51BC68CULL, 0xB436B0785B44CA6DULL, 0x05512BF635B44E3AULL, 0x9DC7E6B206C9B45FULL, 
            0xF250198BC38B2DD2ULL, 0xE12C18395A61EE6BULL, 0x8FEAD89F30A05B55ULL, 0xD1D4F7AF1BEEACBAULL, 
            0xE5BE690F565A422BULL, 0x7C7B2678A9EB47D1ULL, 0x9B97E55C3E487FEFULL, 0xC52EED73F9683348ULL, 
            0x79F3D721D7EF8F3DULL, 0xC110BA3658288430ULL, 0xBD3D8BCE1E7CF811ULL, 0xB28FD9E03CC9C941ULL, 
            0xC945838752CBDF06ULL, 0x8761638A05D2D119ULL, 0x437926D4C559CBDAULL, 0x86EAF8EC3EB3AE01ULL, 
            0x2058C699FA39C0F7ULL, 0xD1109685BA166BFAULL, 0x9C0FA94F99277AAEULL, 0xB51AE6D93D0FA204ULL
        },
        {
            0xD57941D1EEE371F4ULL, 0xAF052355D4E176CBULL, 0x38769B28364D862FULL, 0xCF11886BFEAAD351ULL, 
            0xA84E547C828D4B1AULL, 0xCA7B2A2C6186B767ULL, 0x09779C6E05E7C81FULL, 0x39AC11A43A59DB76ULL, 
            0x3F99AA11295EE544ULL, 0x45A94690341E5FDFULL, 0xA4AF77C52B641C02ULL, 0xE2B1EC3E32C4A374ULL, 
            0xA99FEF656318C22FULL, 0xF6875A47D8ADD039ULL, 0x5BA7302361AA18A0ULL, 0x5A9742563D4187FFULL, 
            0xA308B0E7343935C2ULL, 0x759DC52628F59308ULL, 0x8B24B61209C4F55CULL, 0xA595B9EB979551AEULL, 
            0xE23D32995AE5978EULL, 0x952ED172DC833711ULL, 0x26D01076AB335C32ULL, 0xCE2F1B3F42004C53ULL, 
            0x8D0C71ACD6DA487EULL, 0x29C27DCDA894C059ULL, 0x666EEFC6942534BBULL, 0x6AA76B36305ACA1DULL, 
            0x25512965116FDF43ULL, 0x4F98F31FDB5BD728ULL, 0x6C4CD01CB7CCEA5EULL, 0xB9C5077F0CE4B855ULL
        },
        {
            0x7916552B4118CA63ULL, 0xD9DCB3950144A66CULL, 0x4FC70436D2B23AE5ULL, 0x83AB38A78531CA9FULL, 
            0x9721B1266F7423EFULL, 0x72247C18F3C7D6F7ULL, 0x8DD688966E98884DULL, 0x9EFE4D9C78B8CF7DULL, 
            0x39EF0CF60786CBD2ULL, 0x2E587EC707682BE1ULL, 0x54B0F6072CE9CC9FULL, 0xF90B169167EA7850ULL, 
            0x65A275569D1BACD2ULL, 0x7EA3EB522F031087ULL, 0x9168AC90DDE050C1ULL, 0x04D342B6642C795BULL, 
            0x7A5B1A05E58F72F8ULL, 0x0564CC93350C90E5ULL, 0x91357DF4B2AB450DULL, 0x2618A2DFBFA14DBCULL, 
            0x484E016F5393B9A6ULL, 0x789E579075F554B0ULL, 0x143ED47F798841D1ULL, 0x10944D3B616EABDBULL, 
            0x33928AA76E28C1E4ULL, 0x0230365D3CB9CC61ULL, 0xE4A465A9A0525FB5ULL, 0x7840EBCB5C8852FDULL, 
            0xA6F4439AE3AFE78AULL, 0x6C3CBCA4437F8C57ULL, 0x7BA680E79E61D3C2ULL, 0x2B3808716BE6E796ULL
        },
        {
            0xFBDBEACB4851911DULL, 0x188FAF766D60C736ULL, 0xF9BDDF82B9756168ULL, 0x1098239C7FF7808AULL, 
            0x046CB1DA07861C70ULL, 0x3F616651A1B4E841ULL, 0xA6C6AE6C581C5FA8ULL, 0x03E89623DA4CB5CAULL, 
            0xC3ECD75AE5235BE8ULL, 0x81EFF8A7BE5B5F16ULL, 0xB3D4C7A446A49B0CULL, 0x69CA81A5743D1778ULL, 
            0x75874E4D744B365CULL, 0x190ACA82E2CF67D1ULL, 0x7F566851205276DEULL, 0x57E4AE3609E00D48ULL, 
            0x5873A6F3AC2F189BULL, 0x5F3FD770545EC840ULL, 0xE76AD1ADECC5D20CULL, 0xBC1EB7FFE201E006ULL, 
            0x180AA58D9FBF630CULL, 0xECCCE6B5F7038CDDULL, 0x0950CEF7D6C7B4F7ULL, 0x79AC7398E3FAF390ULL, 
            0x494A40B7ED1F762BULL, 0x4D3958B162ED18FEULL, 0x57539063A70A8BAAULL, 0x5CA0D427F517651EULL, 
            0xDD638BFCB1BEA1FEULL, 0x6FEDDA1B98A51F22ULL, 0x09D450F7EE3736E7ULL, 0xF2B48658737299F9ULL
        },
        {
            0x3B3AD9DAB89D24CCULL, 0x8311B5D6E1799B53ULL, 0x9111952014B79CA3ULL, 0x7F5FC6B18574577FULL, 
            0xD344981C6122F636ULL, 0x34AF0A56361915E8ULL, 0xB519554D1B287B32ULL, 0xB53BD49A82F620E4ULL, 
            0x5155B8B390540626ULL, 0x3B5D265FF3ED7760ULL, 0x512A2469027BB182ULL, 0x7A367DB58EF32DC0ULL, 
            0xB6D851F03A143F6AULL, 0xB97B97B24610DA54ULL, 0x4EF4AF3381360149ULL, 0x39A137C9759C9596ULL, 
            0xD4CC2C4ACF893663ULL, 0xB3895C7706C32397ULL, 0x0C96036607CA0F7AULL, 0xFDE75003DE5327C7ULL, 
            0xE928C98BEC7CCA11ULL, 0xDE6EE8F4BF3B3276ULL, 0x64F5FEB695C2328EULL, 0xC8EF2CC05BEEF5FBULL, 
            0x8D99E3BF23FA7207ULL, 0xF3C740298CEC60A6ULL, 0x278AF204BCAAC5A4ULL, 0xF75889CF5F15AB23ULL, 
            0xCE2119D9F7C72AA6ULL, 0xDC518CD91A23DBABULL, 0x136DB22255EC1B7DULL, 0x98BB7789F9244EEDULL
        },
        {
            0x47A0AFD2042D3FE9ULL, 0xA4200A68BAD5366BULL, 0x265D8D9C7589685EULL, 0x8E6DE1F9494E933AULL, 
            0xE2BDACF7BFE632E8ULL, 0x4E5B97FD90E944BDULL, 0x31F114FA6909B398ULL, 0xBDE23B6AF9D51968ULL, 
            0x55573C496698B260ULL, 0x5FC30E2B6D01199DULL, 0xBFABFC199F94D989ULL, 0xB75D152BFDBFEA25ULL, 
            0x376048C93972A0AAULL, 0x52D1E45320ED78E8ULL, 0xA05260C2F1E85A5EULL, 0xE989631A59A28DC1ULL, 
            0x6AAAEAFC7DE56FE4ULL, 0x41F78FE4FBE9D5F6ULL, 0x11071070540ED836ULL, 0x78ABCD4969423DF0ULL, 
            0x8AF9225236B47C44ULL, 0x618980AEEB67CC4EULL, 0x7314DB513900B148ULL, 0x96BFA1DCE3423F46ULL, 
            0x014438F683EAC7C2ULL, 0x15F592F0C196147BULL, 0x40C5903887D21B39ULL, 0x7A74861EB63D86B2ULL, 
            0x6961AF134DFF6E49ULL, 0x46A4BF62F054EC07ULL, 0x161772DD31BF8108ULL, 0x234AC23A74591630ULL
        }
    },
    {
        {
            0x4D3EEBE46C470623ULL, 0x67D6CE7A9C847718ULL, 0xAFBC7CBF0158668AULL, 0x5BB3E8C19C9F62E6ULL, 
            0xCFC5CF9F5D584C6CULL, 0xEABDEC22A0BB9AF4ULL, 0xA715409FA513BA38ULL, 0x283D7FB5655D402BULL, 
            0xD6C7B21C8E816523ULL, 0xFC65904ADF6AF217ULL, 0x6330C3127904A8E5ULL, 0xDAB8BF91BD828002ULL, 
            0x942082351724A44EULL, 0x6AC3D85A220B46DDULL, 0xE10E7938F95D0796ULL, 0x37B65087CBE2E059ULL, 
            0xF4188A12A73D7E83ULL, 0x085EBC29FCC78C6BULL, 0x46486B53E3873D33ULL, 0xB9EA8A4F26A975C6ULL, 
            0x1362F549F83B8ED8ULL, 0xA7D9FF6291946770ULL, 0x1EA4639542946B0AULL, 0xC828AF686876BC23ULL, 
            0x7CDFD28ECA832637ULL, 0xE638555DD1CA7E4DULL, 0x1F1103103477CB79ULL, 0xA739B13EF7DA5041ULL, 
            0x5FBBA5721DCD90EEULL, 0xE5E5AA820AFE79AEULL, 0x10E5AED024232AC2ULL, 0xB14E6D0622221ACDULL
        },
        {
            0xE628B508FAC62CE6ULL, 0x8D1E436BD60E0CAFULL, 0x9FF8030096C659AFULL, 0x069CDAF9620629B5ULL, 
            0x70168A104B418CD2ULL, 0x64A20323C9CB5FA5ULL, 0x5CF38ADD0D5D76D3ULL, 0xEC4D3605384105AAULL, 
            0x3AF5137EDC65A00BULL, 0xF4E21ED01EB08A7DULL, 0x219AB2004D13C0DFULL, 0x08765A04F044A41AULL, 
            0x12E7C9B3173E55CDULL, 0x3F0A451ACF5A1630ULL, 0x0F8711B09344B5D3ULL, 0x03BE47C9A9489F7DULL, 
            0x5166027BA5A1DDC0ULL, 0x5A7A21D6601D6544ULL, 0xF07109C3A9CE7871ULL, 0xA38C47D5F22958D4ULL, 
            0x866EB042DB8F7A79ULL, 0x07DD30C112589172ULL, 0x0B7F3B5295BDE297ULL, 0xCCEDF29D32852239ULL, 
            0x299091CEBFE960DEULL, 0x73BE2BB6AA9620C3ULL, 0x92D02272FC42F3ADULL, 0x18D5EA945FAF938AULL, 
            0xBF135BD192B4BDB8ULL, 0x4F15DCB6874C02D6ULL, 0x8C90412A837E4278ULL, 0x8692AD7A62939BDAULL
        },
        {
            0x09E688B6D31A1AC3ULL, 0x6055FE0E2EEA0938ULL, 0x0B55D68618374AACULL, 0xFE6F3D4F0C3E2B35ULL, 
            0x7E6105D895251732ULL, 0x7DA1613F50C6B572ULL, 0x47A5ED68B128378FULL, 0xA6F1849910C100C3ULL, 
            0x50C3664ED634DBC3ULL, 0xFC6B22766BF63ECCULL, 0x44AD2714B50F8E49ULL, 0xCA046A18C99218DBULL, 
            0x6D9AD7CC69FE7EF4ULL, 0xFDF1EEB123E4870FULL, 0x6CE1907E1458074FULL, 0x5CAC4CE193A32DEEULL, 
            0xE481E44AC90E3AC7ULL, 0x95E470C3C27A6947ULL, 0x49D19E107F6C18DAULL, 0x33AA0CD0604DA222ULL, 
            0x49CC837232C412A2ULL, 0xE357337230396CBDULL, 0x874B6426577F47D9ULL, 0x1863FEB40C307C9DULL, 
            0xAA26A5E513D96B29ULL, 0xADFB01EA45D22623ULL, 0xC9F6B81AC7627794ULL, 0xAF3CB4E873EABFEBULL, 
            0x3C828F71FA9B9AF0ULL, 0xA0181827E67F9551ULL, 0x7331BF805CF09B21ULL, 0x32C06449364F4E11ULL
        },
        {
            0x9DCF677F56B8ED48ULL, 0x3792DDAE53A72AA4ULL, 0x7AF27C674E32139FULL, 0x9624FDB3E0103BEDULL, 
            0x3F54B2F8FDB822A3ULL, 0x78BD62A19BE985E0ULL, 0x553A318F6840225BULL, 0xE295E42A073A45B9ULL, 
            0xADB93E1D580C230AULL, 0x2D8D1335CA95F593ULL, 0x65A15DA2F731027AULL, 0xF4243EB53CE29DBAULL, 
            0x74311A0497F7446BULL, 0xE919DAC595580762ULL, 0x30EEA9D1A00CDD32ULL, 0x6166D3ABACB4D5E5ULL, 
            0x1463D12E8BC6D340ULL, 0x360AAF76EAB06CE5ULL, 0x3D27C2F1D2E810AEULL, 0x72560272806A0258ULL, 
            0x1F3DC4AD742089F0ULL, 0x62FD48ABEFE3E819ULL, 0x0D41120AC067482DULL, 0xBD07E5419EB17816ULL, 
            0x58B36CE156D09196ULL, 0x2AF8ED00B0FDAA41ULL, 0x69B83E93F9F05925ULL, 0xF9A5FE8A088FEDDDULL, 
            0x80EAC82C705149FAULL, 0x52C661B426795BC1ULL, 0x246238A39348C081ULL, 0x8F47AD6E8C30A0C3ULL
        },
        {
            0x5F658E0E9B728554ULL, 0x29CF05CC8C204DD1ULL, 0x8BA39AABCAA3BEEDULL, 0x6D8B039BDF4A70AEULL, 
            0xC26E606EB6755A37ULL, 0x90DFA339059AE38BULL, 0x7F63E9038F7BAB31ULL, 0x1FB07B58880EE6D1ULL, 
            0x59C3BFB08F705DABULL, 0x0DEAF777D168B15CULL, 0x04F56F3E095DE2C6ULL, 0x35271A0C8C660982ULL, 
            0xD1934F6B8A68BD02ULL, 0x4961CC3937CEF853ULL, 0xBBE00FC484C49AB3ULL, 0x79B759B0724ED988ULL, 
            0x5654DDF5B9825BF8ULL, 0x826B359201B67246ULL, 0xE16EFF55E79EB5F2ULL, 0xC4B5B539E09D44E7ULL, 
            0x32E4832B129B0756ULL, 0xFBB20C60BC5592A4ULL, 0x69C95C7036A6934DULL, 0xBFF0FA34321A1AA3ULL, 
            0x271A71401526E4E2ULL, 0xF329534BE4831193ULL, 0x02895F468CC6BED6ULL, 0x8BA064C27AB6113FULL, 
            0xF78DC174A40CA6EDULL, 0x6B98C78D4941774BULL, 0x66A525CA888156FEULL, 0x845CE0F732A5D2C3ULL
        },
        {
            0xB6EA907D149796CCULL, 0x9BC50F722A0EB90DULL, 0xAFB31D80A846ED35ULL, 0x33581F90F447F0EDULL, 
            0xEC67DCA15609847CULL, 0x3477CB5CD7A3903BULL, 0xDE3D79F0844004C2ULL, 0x8AA8B57CDFF792BEULL, 
            0x5C5FE340B28579F2ULL, 0x3031EB6232BF38C8ULL, 0x01DA82A35D266D49ULL, 0xEF1414E803FD30B5ULL, 
            0xA8C59D42FCB6CCF3ULL, 0xD61206A953E8D1F1ULL, 0xEC571BAFE50A57F3ULL, 0xBBBA415F0CE8B1D6ULL, 
            0x60BAB901EDAA7F31ULL, 0x4FE416DEF4101FC7ULL, 0xDF16E76CBFE42455ULL, 0xE31A5FE838BD961EULL, 
            0x4C64F201C960C55AULL, 0x85D29BBD7672049EULL, 0xF27A0179F4A86EF7ULL, 0x7A84E78C60EF8ED9ULL, 
            0x463E2B75BBDCC81EULL, 0xA3E910354E4D6BA4ULL, 0x189F7C9CC923FDBBULL, 0xE99177BD83D2EDCEULL, 
            0x17109110B3195355ULL, 0x10EB38B4C155C9B1ULL, 0x2A333FF2D6CD2901ULL, 0xF3F68328A5D732D0ULL
        }
    },
    {
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
            0x9BDC9DA40C24F5C9ULL, 0x03A51F482BD41B31ULL, 0xBA2C3CAD377A4D13ULL, 0x74A7239CD8E4CAD3ULL, 
            0xEE34338060F513CAULL, 0x8BE1A77C41552B45ULL, 0x77F73A1BE47CF6E7ULL, 0x8A78202F4D400C15ULL, 
            0x6A575097B23C3B4AULL, 0x4321689DFBE862A7ULL, 0x69407A040098112CULL, 0x4B90BA9F42981640ULL, 
            0xDBB890489732A93CULL, 0xF7152A15B864B012ULL, 0xC6D7C386D5F90A35ULL, 0x82FC77904B4B3F0DULL, 
            0x492F81189DED6C25ULL, 0x9A5149FFF2C461DAULL, 0x3FF5A47AFC37F844ULL, 0x6031E86831F3DF10ULL, 
            0x4F4D43A82E973B0CULL, 0xDD79E2FBC7BC00D0ULL, 0x8B36D61BDEE6C05AULL, 0x531C628A8ABEE80AULL, 
            0x6AF0D9C13578E821ULL, 0xBD51E6198D8CA62FULL, 0xE27A6BA1A9AFF645ULL, 0x9C126EB8C9D6A786ULL, 
            0x00B4023899512BA7ULL, 0x9C3E39A5029F23CDULL, 0xD2F2D8B5C64AF60AULL, 0x8762DF5DDAFDDA25ULL
        },
        {
            0x045B9DDB2E7C7D14ULL, 0x25682F0E879B6625ULL, 0xB6F4061798035DF9ULL, 0xB81E5572F6F58B1FULL, 
            0xC408145DC8B192ADULL, 0x730CA640E43AF9D7ULL, 0x5C81119839B0CCDFULL, 0x283F1FB081676430ULL, 
            0xDA3F75565A5E12CDULL, 0x30026E060058B2FBULL, 0x1A27989F4A26F05CULL, 0x345DF3D409CE4361ULL, 
            0x4E96C7796BB3CCA3ULL, 0x78C9BCC3E279D625ULL, 0xE9741F92BD2461C5ULL, 0xA3D34215EBD60DB6ULL, 
            0x54ACF6C9A67C78FEULL, 0x059258960FB15C0EULL, 0x18EF731D51BD3E0CULL, 0x4A8E8AF8748691ECULL, 
            0x5825E0E80686CF89ULL, 0x6DE59C9776147B2CULL, 0xF1E83162736680CAULL, 0x51340C808ACD94A2ULL, 
            0x4725D144BDB866D1ULL, 0x5287D72B0C4ED55EULL, 0xAEDC8789B4A7252DULL, 0x3D51B40FAFB79D5EULL, 
            0x8DC6F9F2EBF3CAB5ULL, 0x8025C13A455A0B21ULL, 0xD514F1F8B76D31C3ULL, 0x641AD82B619ADED0ULL
        },
        {
            0x79564956B96AB243ULL, 0x16479B3E82F53DEFULL, 0x4EDACC1B9D4424D2ULL, 0x941E94763AD3F0C4ULL, 
            0x0BFD333B11FCF366ULL, 0x7109F05B4F40A6ABULL, 0x139922D0F8E3CEAAULL, 0x3870EF008B265AFAULL, 
            0xF469D3273D0F06DCULL, 0x7DABA3D0B8ACBCE6ULL, 0x2D2867BBE3885566ULL, 0x1A1EF4ADD46347A2ULL, 
            0xF18B6A7DAF686F0CULL, 0xFDE6F5B743864E18ULL, 0x72E2348414C36953ULL, 0x4358AAF45C6E5691ULL, 
            0xA85FE60DDE980113ULL, 0xF6938D91D809C87EULL, 0x068FC38695CA196FULL, 0xA8A06BB9E966FF8DULL, 
            0x59CE5B33BA2F4C99ULL, 0x473245876C867504ULL, 0xC011C77EE1AC807BULL, 0xD2DF3A7300E7F8A8ULL, 
            0x3EEDB957D64D823BULL, 0x657496054547E0DEULL, 0xAD5255B5D41C0E61ULL, 0xF85C08BB9A2EBF8AULL, 
            0xA6F68D38658782ABULL, 0x58B7204867C28556ULL, 0x4D0C07F6AE1A2A76ULL, 0x79AA4A09BC1ECC25ULL
        },
        {
            0x4B7DF74D16227081ULL, 0x509A15A158DD270CULL, 0xC619A8079C0597F0ULL, 0x38BF1F797639303EULL, 
            0x2E44C3C525D87526ULL, 0x076BC264AADB4089ULL, 0x06C23C3362A92548ULL, 0xF097F4C633A1440DULL, 
            0xE30D2A1BD31259E0ULL, 0xDB931705D81D7092ULL, 0x444253A8C8ED5105ULL, 0xAF8CDDA0438E2F1DULL, 
            0xBE0A726760B7C713ULL, 0x83C0C70596079C65ULL, 0xA16C2C599CCD3181ULL, 0x4D69BDDAE229C67FULL, 
            0x00C2AC58D3503E2AULL, 0x8B0D857FB85889A1ULL, 0x571ACB4970625FDEULL, 0xB4DF5D08C6048866ULL, 
            0x02DEC7D76DFC157CULL, 0x68DE73E112C88CC3ULL, 0x60647303768BAC03ULL, 0x1AEFA5AA6B6A9B07ULL, 
            0xEB857E4EB8FFEB02ULL, 0x98670C64005C6ADBULL, 0xA17BFB5B66CEB3E3ULL, 0x3A42F3CC97855FAAULL, 
            0xBC525A2E7360974DULL, 0x009ACE71911A1F4AULL, 0xFE46493453F6E3C5ULL, 0xAC173E9DB6DF0E77ULL
        },
        {
            0xCBABB8CD580AEB1DULL, 0xF3FBED905839B05FULL, 0x997EBDBB62C274DCULL, 0x069EB223F9B5EA0EULL, 
            0x5B143438B8D68AE0ULL, 0xE069EB06DEB2CDC3ULL, 0xAABA1E9F7EDBD993ULL, 0x2A463BB0EAEE9038ULL, 
            0x792BF928FC863205ULL, 0xE7F5C0C076EE36C5ULL, 0x35F05332E4208380ULL, 0xC99D1C912997A47FULL, 
            0xAB56F579D49D04D6ULL, 0xEE654B4F2897077AULL, 0x343A3F248D4C8F5CULL, 0x88CAF7BD36E3F9BBULL, 
            0xBC9594E9DD56034CULL, 0xB426823708601A2EULL, 0xF0C5BACC87369A29ULL, 0xC4F325C37DD56FB3ULL, 
            0xAD6E06A039807203ULL, 0x0BAE4991C48133EBULL, 0x5321ACCA095C7A99ULL, 0x5A08F84BBD15E91CULL, 
            0x5D5776EE3890A8C5ULL, 0x1A82E8696D426D53ULL, 0x1EABB87DF8FE9E37ULL, 0x3138D2C40E6BA76BULL, 
            0x353413E40CE34A07ULL, 0x66B2E46588561C36ULL, 0x1714AE0873687A39ULL, 0xCA5D1032DE561F6BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseBConstants = {
    0x01E57BF9C7508065ULL,
    0xAD70375F6CF651C7ULL,
    0xBE723A573509E242ULL,
    0x01E57BF9C7508065ULL,
    0xAD70375F6CF651C7ULL,
    0xBE723A573509E242ULL,
    0x13EB05EC4F5FC8DBULL,
    0x3FA1B3FB10FD2BCBULL,
    0x02,
    0x87,
    0x03,
    0x19,
    0xC1,
    0xAA,
    0x9F,
    0x8B
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseCSalts = {
    {
        {
            0xE18E74C3E48F6882ULL, 0x3893D50EA4930311ULL, 0x36E4A15C8A83051CULL, 0x4DC9F75E119F392CULL, 
            0x9671B8F176BB24B4ULL, 0x3B2B0F5887C83579ULL, 0x88E280D246CD9BFAULL, 0x86521DBE2A6A58E9ULL, 
            0x1302FB5F3D4CBAD2ULL, 0xAB065BB310666949ULL, 0xE75632CBE34A9263ULL, 0x7DDBAA63F38E5B2DULL, 
            0x7ED423940F897FDBULL, 0x65ED0B77D82E59E4ULL, 0x6456506F7AEA2971ULL, 0xF8A99FB2FEAE6847ULL, 
            0x288F6C88E038196FULL, 0xB4D4BE7145EBE71AULL, 0x510EB7E8BF929A84ULL, 0xBD1689B1501EBB46ULL, 
            0x2F2341797CDA375AULL, 0x0E0A154D6B88119DULL, 0xD5D4011E47B8AC9BULL, 0x1DF7E14C5876E2F8ULL, 
            0x84319AF4DDC4B7C3ULL, 0x1D9E8D00BE8F821DULL, 0x983C0CED52DF81C5ULL, 0x16D9F576F174D158ULL, 
            0x2788D0E81DD91A78ULL, 0x9178914DA69928D8ULL, 0x86315D64404FDA89ULL, 0xCEE2D04ED20F6C13ULL
        },
        {
            0x8642F015AA5BEB46ULL, 0x52CEB88821713A7CULL, 0x14498142C0233ECBULL, 0x7145DCEDBE5809FAULL, 
            0x543B1DE7D670D77EULL, 0x6A64AFB920F2FFDDULL, 0x38407BA151D0B76EULL, 0xB6252D7F368D4EB1ULL, 
            0x43FF102260EEBA98ULL, 0x56C757A89B891DB8ULL, 0xA110C47930E5FAAFULL, 0xA0612B8B31B84AA8ULL, 
            0x249C57C0BFCF8B50ULL, 0x94499B6296C770E0ULL, 0xEF75A1C98073348EULL, 0xFF62A2E6D4A41949ULL, 
            0x4A193E1532C16DEFULL, 0x744B34B4DA514140ULL, 0x7DF59DA4BDE23645ULL, 0xCA7CF7D90C4490ADULL, 
            0x7F458B8823CBEDFDULL, 0x04A9333B127623B4ULL, 0xB576D5918D8B9623ULL, 0xF53E8804523CB0EFULL, 
            0xB6837298B95F3548ULL, 0xD27679E496E2BD4AULL, 0x7D2039419E240274ULL, 0xC4F44DF2DF6E248EULL, 
            0x6A69F8BDBF35F173ULL, 0xAC02BC9C332431C9ULL, 0x36479596DA1580C2ULL, 0xE8AF24A7DA0A3F26ULL
        },
        {
            0xFB4358B661F8EE5FULL, 0xDDD346DECD3BED97ULL, 0xEB6D24EB47FD7D74ULL, 0xA87C32916E508C79ULL, 
            0xD345F592DA4449ADULL, 0x58CDB2631CB0ABACULL, 0x086BFC86847A340BULL, 0xF463450E2D51B10FULL, 
            0xEE3348429BF51C09ULL, 0x55CED81085BE3C34ULL, 0x0B31C48586762B37ULL, 0x2930F17B31801239ULL, 
            0xB1E3E6764ADF296FULL, 0xB55F6811436ED52AULL, 0xDB46F952BEE865F3ULL, 0xEB356CE2AB7D1C69ULL, 
            0x4011E841B426FA7FULL, 0x7D04B579D44CF151ULL, 0x9C1C897DE5B3934AULL, 0x1A390767A7A3BA12ULL, 
            0x7D804CB7D66A0B41ULL, 0x966B0B5FA3A04EC5ULL, 0xF5B9BB1E1DF1285DULL, 0x56135C260C161DA7ULL, 
            0x1D3BF9A00B4D5104ULL, 0x62B72333D1E40552ULL, 0x48876EE8A52C134FULL, 0xCDCC37F0C42134C3ULL, 
            0xE97BB4E9DDABF596ULL, 0xBFF809E5497B9C6DULL, 0x79EAC883D9B03D37ULL, 0x13132F58B4E71370ULL
        },
        {
            0xAB6001C8A32E3D28ULL, 0x5D466D2DE20D5A8AULL, 0xF3EA6DE76B58D991ULL, 0xB3F0016389C098BAULL, 
            0x13AE20E44EB62898ULL, 0xDB7A641963B63EBCULL, 0xB6B1C0DC0DDA5C4CULL, 0x1264D56AC8C48B59ULL, 
            0x52A152F44F00566AULL, 0x19816546BD7C86F3ULL, 0x4594186DCECCB891ULL, 0xEEE2337E0E06A1C5ULL, 
            0x5229D44C9F85B14AULL, 0x3979053827F857CAULL, 0x97B62C7F39637451ULL, 0x2C27DBB8912A4D88ULL, 
            0x04440B0932CF15FAULL, 0xBCD8FCF16630FEDFULL, 0xBD1FAD9245779F1BULL, 0x4564791EC177C271ULL, 
            0x4F2F696B2CB92DD2ULL, 0x6C73A3A8FBEB93E9ULL, 0x2EAD5397841FF8C4ULL, 0x98B7EED0687BAD2CULL, 
            0x86604639C067D1D2ULL, 0xC2398E0E577EA971ULL, 0x35FB808B4539378BULL, 0x9A67782715C4022DULL, 
            0xE23B409EA2A43088ULL, 0x1F1FFB6114251B15ULL, 0x04DD7AADDF610D8AULL, 0x7F037FC4F061289AULL
        },
        {
            0xB77DEB325B1367C8ULL, 0x7DF6B4841E8589A7ULL, 0xD9371F76DAEBF9C0ULL, 0xF0073CAD5D234AB5ULL, 
            0x0CDFAE26EB89DEF7ULL, 0x7900CD7DF39F7893ULL, 0x68A10695323DE9ADULL, 0x3A9E53AFEBC3CE25ULL, 
            0x0D1875F70648FD59ULL, 0xDDBDE136F24007D0ULL, 0x9C5C12A086310B96ULL, 0xDE5E294532F287EDULL, 
            0x2E3B0B9B865C15C0ULL, 0xB0EEA0D8886DDDF5ULL, 0xBD37E6D0CD0B96B4ULL, 0xE96E8631BFF0984DULL, 
            0xE440D301C505A236ULL, 0x1B1CD1125FC9FFA9ULL, 0x4456525C1C9BC6B5ULL, 0x142CABF3C4CC9241ULL, 
            0x3EEE3027FD4D1E76ULL, 0xBF13F5BBC735ABBDULL, 0x3406BC28B7BE9BA9ULL, 0xB9D5F019878444A4ULL, 
            0x144141B9986391B2ULL, 0xAC5251AC4B4C5487ULL, 0xF6240CFFB1830B0EULL, 0xDBF96DEB664D4859ULL, 
            0x7E065ADA9FAC569CULL, 0x6AC6727C2758C7B3ULL, 0xD91600024D21D3FFULL, 0x3291DBF9481A6021ULL
        },
        {
            0x0FCF5CC5A6899F3DULL, 0x37F1678ECE95B6C6ULL, 0x92E6448B9916A930ULL, 0x0299A294B26E84D9ULL, 
            0x5FE13563A5E5CCC8ULL, 0x3DF94A3AFCAC86E1ULL, 0x7CDA541DAFBFAC70ULL, 0xD1136674BBA31403ULL, 
            0xBD30D21C41D1DCB9ULL, 0xFD7AC25CE32AE9F1ULL, 0xBAED9D39559AF93EULL, 0xF879DF9FB67DDDD6ULL, 
            0x459F0E2E3390CA67ULL, 0x361187265770D201ULL, 0xBA418247E438AC21ULL, 0xB4237CB794DFD01BULL, 
            0x600BB65EEA59BB9DULL, 0xE138BBF31B702F0FULL, 0x6A51014EDA30C884ULL, 0xF1A05F3D39B7664AULL, 
            0xCC9463375748F789ULL, 0xBEA2DA1782279669ULL, 0xBA7FA78261B7DA27ULL, 0x920E47CCF9ABCA0AULL, 
            0x4524596FEDF2A4B9ULL, 0x88760124E7430CD7ULL, 0xCE9C0EB8483CD6A7ULL, 0x69F3581C4C519FAFULL, 
            0x855F31D1DF979D42ULL, 0xB770100B3600A00AULL, 0xD7B43DA49B9DE155ULL, 0xF73A0E354F8DA6F4ULL
        }
    },
    {
        {
            0xCC7742C44914B010ULL, 0x3EB952C5608DB5D3ULL, 0xB6AB66943E3F1360ULL, 0x54E27BE35177167FULL, 
            0x5170D151D263983FULL, 0x78A5039CC3A343A2ULL, 0x2F45817BA58995B7ULL, 0xF64D6D8AC9D67E50ULL, 
            0x598C9C8A0538B8C0ULL, 0x806F8CB830EDF699ULL, 0x9CA19EBDC0443621ULL, 0x39CE2110B915216AULL, 
            0x5451C4F300CC6BA6ULL, 0x275E11CC9294B93AULL, 0x15D8F0803A340B2FULL, 0xA2D3288F4EFAEF4CULL, 
            0x142303C512FB7A36ULL, 0xEFF76A2882FEF684ULL, 0xC1006B594DC5D4EAULL, 0xF084B297BA1A979FULL, 
            0x8BEFF001E32C622EULL, 0x13E8E1BDCA08184AULL, 0x98D092F8EAE1D921ULL, 0x95DD7877F29AFF03ULL, 
            0x9876F4C2E012E413ULL, 0x2B5B2C62C1C0E78DULL, 0x466C47079351C632ULL, 0x413ADDC9A50C0F25ULL, 
            0x34ADCEC634DAC9E7ULL, 0xE899473811CAEEF7ULL, 0x5D06FF2AB7C8A243ULL, 0x437E9A7404751DA3ULL
        },
        {
            0x14BA96EBB2781F00ULL, 0xB8BFA74C326C9412ULL, 0x88A7D4F746813C55ULL, 0x5147686DE4E0C5DBULL, 
            0x8F1A4E4E97BED0A5ULL, 0xB8EB8CFB740DD553ULL, 0x8E71D3EE16E769E0ULL, 0x6EB3646A93E3D11DULL, 
            0xA42E98B25282C0C3ULL, 0x525AF6421A86E6FFULL, 0x1BA838B1BDF28687ULL, 0x9BFA170340093598ULL, 
            0xC80A1E36C843B555ULL, 0x38C0C8CD083E3DA8ULL, 0x9ABDBDE2403A91B4ULL, 0x56C6FCDE1D2C7050ULL, 
            0xB7E1E955EEB383E0ULL, 0xEE1EE332E6877813ULL, 0x90794CDBCD42713CULL, 0x0A5488FD62654526ULL, 
            0x622CE47A7E2F62D8ULL, 0x8C095D9E96C08821ULL, 0xA0C50A3A067FAB21ULL, 0x4F3BFCD14230ED14ULL, 
            0xF31137377DB2DBEAULL, 0x2F661FC6D5CC7A2CULL, 0x795B5F6A3C200606ULL, 0x4FC86D4899DBC1C3ULL, 
            0x7B500B4CAA31CB0BULL, 0x990D2F418D642D10ULL, 0x20F4F51B4FC8ABD2ULL, 0x3F0011765F7E6945ULL
        },
        {
            0x913D5F13C9FE0477ULL, 0x56CF2C1B0B393536ULL, 0x43054AE585074E5CULL, 0xE057E38543C9F935ULL, 
            0xF5CFA2269495F14CULL, 0xA27915A69F6D74A4ULL, 0x7EF02892A327865AULL, 0x87663FBA7072DA02ULL, 
            0x85BABC8ACC134934ULL, 0xFF953122F675C122ULL, 0x9CAB9EE78A6593DAULL, 0x528D7D2EFD582239ULL, 
            0xD4A58F1276F82399ULL, 0x0B39BA5F9F391E25ULL, 0xCAD1B93E32724EE2ULL, 0x88B81D91BD4F9AB2ULL, 
            0x4ECBFABBCBDEE850ULL, 0x3650FED3DAE5D3F2ULL, 0x16B28BA6FA1031DEULL, 0x456AAAD97DDB928AULL, 
            0xB11083D959958A08ULL, 0xBCF40B9238B97329ULL, 0xC6CD1FFF715C70ABULL, 0x87D3CDC90F53F7A4ULL, 
            0x7802767D5B43F85DULL, 0x9DAE45BF22B53037ULL, 0x9A7D54CDDB9B9507ULL, 0x87AD9DDB6F785CD3ULL, 
            0x36F7469FC6C5CD0EULL, 0xD01BDA67E0A3CFD5ULL, 0xF5E5DC9FB33290A7ULL, 0x610608A540FA429DULL
        },
        {
            0xE6309BADDB017E51ULL, 0xF7937F3BDEE140E2ULL, 0x3322E10CA98FC2CAULL, 0xE723397E96E0B5E9ULL, 
            0x5776E84CB7631692ULL, 0x29D657759C82BA33ULL, 0xDE85E090B352DD9CULL, 0xE2229A76D45AF169ULL, 
            0x301F0581C0A20E9CULL, 0x3DFD9E8E5E63B7E5ULL, 0xEB480DECA26C7CCFULL, 0xCEAD1DBF3DD90A01ULL, 
            0xBE7760A9A6135E60ULL, 0x9B130FF259C7E072ULL, 0xBF9A45AE0B5F22ABULL, 0xC4885868D8B7890DULL, 
            0x1895BF9D88EC91AEULL, 0xF9437029FF1515CCULL, 0x828A80E4C5FCA974ULL, 0x79E64CCB78991B5EULL, 
            0xFF673067D347C395ULL, 0x2E750603DE30620CULL, 0x54AB9AD1E7A831B1ULL, 0x13D58561C33E9374ULL, 
            0x6878903AFA7CA108ULL, 0x65B0836093C5204DULL, 0x576DCF6A431D31B0ULL, 0x8B2FB13DBA4DA413ULL, 
            0xDCD06657474B6489ULL, 0xB10293130A100A12ULL, 0x4F92513B250D2C0EULL, 0xCD5464E163E2C405ULL
        },
        {
            0x61A30CF3FF02B9D3ULL, 0xE85ED66842C1F5EDULL, 0xE520DA86A97CD461ULL, 0x39B96347AF7D22A5ULL, 
            0x70F6149D271D47E6ULL, 0xBF239B4021C11F62ULL, 0xCD69464A56106791ULL, 0xF4ABF55722ACC885ULL, 
            0x5EF7BCE2016A51ACULL, 0x1EC87A764BF0B890ULL, 0xB1E4B296A4254CC4ULL, 0x1139534AE79C5116ULL, 
            0x45DB4374DE9AB1A2ULL, 0xE66BE8AB83248C8DULL, 0x1C2558D59FBEF63EULL, 0xB9F8A3E540D82794ULL, 
            0x05725F70E76C93B1ULL, 0xC46E5696A7CFDBD8ULL, 0x84A13D43B9A23D76ULL, 0x6696FE9A8A48494BULL, 
            0x07B63CB7CBFC0435ULL, 0x22D97DC3A72F5BFEULL, 0x3104F8396CC081CCULL, 0x8E9C7EF7573C5805ULL, 
            0x37E4987D60024D04ULL, 0x09BD0F94948ADA82ULL, 0xFAFE8CC5A8CC5C2FULL, 0xA6342A3913D27DC7ULL, 
            0x6CF031ECEAB951D6ULL, 0xE75B4C688CDAF059ULL, 0x7584BE56B2D55DC1ULL, 0x98B9491E85E32C39ULL
        },
        {
            0x0047DED38AF3AF1BULL, 0x273C04FE89B603A3ULL, 0xB54EF981B387D504ULL, 0x2861858AB5B2BD93ULL, 
            0x82755F6F2A59951EULL, 0xF305E34D7A4FFC8DULL, 0xB2B41E04DE94CDF8ULL, 0xB384D2E347729E7EULL, 
            0xBF637CB466099383ULL, 0xA7D04470CE6F4A2FULL, 0x31F2D610E5B1ECA2ULL, 0x9EB2EEBFB23E1C9BULL, 
            0xE5E92883759C34CEULL, 0x56127694E633139AULL, 0x6BC59378F9EA341BULL, 0x48CEE9DE644C61BEULL, 
            0xB22058CD67297939ULL, 0x7D1FC646737AE9E2ULL, 0xADD494DC46BCC345ULL, 0xF79E4CA6C61C6CC9ULL, 
            0x67CA67F50669A5B3ULL, 0x85D8E27CFD3C1C18ULL, 0xF34C43A6678463D7ULL, 0x38D0A2F53088E994ULL, 
            0x22093007450EC877ULL, 0x4371B6617F45A7E0ULL, 0xA314996190C942A5ULL, 0xA9089546B0F5564BULL, 
            0x3F288BFED8B72F05ULL, 0xEF65D29D73933EA0ULL, 0x9C41634C109E541BULL, 0x4C575EF6E277E763ULL
        }
    },
    {
        {
            0x0C0E072472F350BCULL, 0x6631EA85D99C21FAULL, 0xB28EAC6930096973ULL, 0x1CC6064851E1E47DULL, 
            0xC5B536EC608C41DAULL, 0x21838FB68611C714ULL, 0x698983E94F829DF1ULL, 0xEAE12C118031FA7EULL, 
            0xD473BCF752FBCACDULL, 0x69118B68B512B048ULL, 0x65CED200BA78CD8DULL, 0xF86257F7E4166919ULL, 
            0x085343177C1881BBULL, 0xA52D478565632CDDULL, 0x015C3B01EBA4204BULL, 0x155AFD234FC185D4ULL, 
            0x3B60D04E8D4DE755ULL, 0x27A1E1634C47138FULL, 0x2BC09C913D8D1575ULL, 0x74FAC3FA0E845B4FULL, 
            0x42F43087E412A09CULL, 0x9F5BA92FE05CD425ULL, 0x1B1C98CDEAC06024ULL, 0xABAB2C0041D9E2C0ULL, 
            0x05442D5334E5B497ULL, 0xA28203C8653CB495ULL, 0xA79DBC8723B25E04ULL, 0xB7D56054A6E0A5C5ULL, 
            0x911837B103CFE860ULL, 0x1D0A88745D5AE13FULL, 0xBC321B4AD6C517A8ULL, 0x11BC7378C3894A50ULL
        },
        {
            0x3AC7C5B40B434259ULL, 0xAE9D70E9A262F581ULL, 0xFF4A3C9E79BE18B9ULL, 0xA423ACBFCBEF7147ULL, 
            0xE788C930A9F3205FULL, 0xC308DF4E6094A585ULL, 0x5851706B0EA65ABCULL, 0x3D3193EBD0BE80EFULL, 
            0x595D377025EE20EAULL, 0x73067A845DC19067ULL, 0x49FECC5349C1D7B7ULL, 0x6913C05541056613ULL, 
            0x96A9CB303461D817ULL, 0x93D9F2C7A4A1A7FAULL, 0x8191A7C670A7D3FAULL, 0x5E62D3ECF063286BULL, 
            0xEB41338D39A1BFF5ULL, 0x8C1920D931B63BD4ULL, 0x03DED5657AB0AC22ULL, 0x0AF354485B86B75BULL, 
            0xC4FD709B053EB7A5ULL, 0x329095D8FFA1ACF6ULL, 0x1FDA3DD0E8C12CA5ULL, 0x91873EE04E8824A1ULL, 
            0x442658C20EAEA114ULL, 0xD968B1F8AEED460CULL, 0xCB41AA4E6850384EULL, 0x2EB0E6FC83470958ULL, 
            0xA1EA10B6BA3A909CULL, 0xE2EE5DF86634E027ULL, 0x153EB805F24C41D8ULL, 0x5C77842BD08E6899ULL
        },
        {
            0xCAFBE21FA5235747ULL, 0x17914E2F5AA023C9ULL, 0xEAD647AA3DA9FD67ULL, 0xFC07F03BD74A9BF1ULL, 
            0xDF83F3C9CDB0891DULL, 0x407CCE80F17DC2C9ULL, 0x00D138C6E12EEB07ULL, 0x6B32D2FD64DECA94ULL, 
            0xC98B4D684125692DULL, 0x6C6BEC8EFBEF0D2BULL, 0x14BE7B6DE283AC09ULL, 0x16DC77A7D0F0D61DULL, 
            0x31229F5C2A318598ULL, 0x3D29885190C3336AULL, 0x1C33F385938626B4ULL, 0xED18D76B07894FEEULL, 
            0x9F52604747A4F196ULL, 0x78EF2CF9D2CECC60ULL, 0xCAFBD6B5EF5046ACULL, 0x5129305AEDDBF2CEULL, 
            0x3BCB0CFC4D109B8CULL, 0x63F99DD9CA09DF9FULL, 0xC378B55C6A3E11CEULL, 0x04A999A2EA8A7CFEULL, 
            0xE8B4A9B4F774FA5CULL, 0xF86FBF5E4A322153ULL, 0xDF703D083D506C46ULL, 0x4C17636BF5BFA24BULL, 
            0x40F2D15CC345DCFDULL, 0x38F68CFFE85641D5ULL, 0x4A25A91102B63823ULL, 0xF55F9382B65494C4ULL
        },
        {
            0x81F9BDE3450DD6F1ULL, 0x3BC4BA53B5CBF1FEULL, 0x1BDB5D7A8F0A94F9ULL, 0x329664E8E69F79EDULL, 
            0x120D7AF28B136581ULL, 0xE4BC9A8FD790DA1BULL, 0x701C085D00CAF6EFULL, 0x220C394433EA77D7ULL, 
            0x5A4B8606F0D12306ULL, 0x5E1FD3E5540F79A9ULL, 0x02F8F9D6B414272EULL, 0xA0CEE34C8CB4DCD9ULL, 
            0x3A8933C41CF65BDBULL, 0x7F16031F027FED62ULL, 0xD2D2A8FA9ADD9D6EULL, 0x60D35D9A469ED018ULL, 
            0x5FA33B7208BBFBB7ULL, 0xA911420DFD1B22B9ULL, 0x19926B3A2358BB57ULL, 0x4BF58A845A01193AULL, 
            0x2C5FDE4FC4971CE1ULL, 0x1CF6C359D7DD60A4ULL, 0x4F9E23EF4B4029D8ULL, 0x4CFDD950F5AEDFF4ULL, 
            0xCDFBC3803E01C52DULL, 0xE86AE5B43FC7F5A0ULL, 0x1206824908B85166ULL, 0xAF021DE6BE095AD8ULL, 
            0x80834406FD186CBAULL, 0x88F3A97A8A1E44C8ULL, 0x002E13620FD5BDC6ULL, 0xCC183B1CC9CE9169ULL
        },
        {
            0x6866D3FE7CBEF019ULL, 0x0BCE656B64D84575ULL, 0x796B0AB903B5855AULL, 0x9AD232876348227EULL, 
            0xA4C27DCC794ECA9BULL, 0xB4FCB0ADBDB1BAC2ULL, 0x81A524DFCD382D2FULL, 0xCC3CDD9F8AF3195DULL, 
            0x67696C6357096B34ULL, 0xEEB409E1C7153A7BULL, 0x4D788C99FC6067D1ULL, 0xB84281ACF924869EULL, 
            0x2891AE78147E0309ULL, 0x199B18B68AA26009ULL, 0x37E62A1C5043E80EULL, 0x0FA6F60D8B5B42BDULL, 
            0x020701347BC8A529ULL, 0x0CADBB18B66F15EBULL, 0x625F3FC5BAECB063ULL, 0x7FCD967FD7EA224AULL, 
            0xBF08C96758AD8515ULL, 0xDA45F5C968526658ULL, 0xCEC77C83BF2657F0ULL, 0xFBBBD2BE6AEB7F32ULL, 
            0xFA64901E1B348941ULL, 0x2FE12ADEE7E591F1ULL, 0x5713D5DCD18C5ADAULL, 0xB45F124BDAC565C4ULL, 
            0xB368777E21654FD2ULL, 0x9E67007C3E214E40ULL, 0x4135D65C2FA6BCD4ULL, 0xF8F0742A2B567338ULL
        },
        {
            0xF849F39A486CD73CULL, 0x9FEAE8EA7E9DC8F9ULL, 0xB3BE7E1515FD2AF9ULL, 0x24C53EFCD1C81600ULL, 
            0x0AAA6E50C4DB2993ULL, 0xB9EB8FD092D66398ULL, 0xA8CB6507FF29D523ULL, 0x231A937BC271A7A1ULL, 
            0xAD032668C3464801ULL, 0xFA317C682C37B752ULL, 0x4E08BC48DB8B3D65ULL, 0x0453C3B3169EAADBULL, 
            0x79854A52EC1C9DAAULL, 0x0E64ECD5363F6818ULL, 0x6770CFDE33C6F2D4ULL, 0x78A11BD055322B94ULL, 
            0x32A250E03B46B669ULL, 0x3318C01E2ED97BEBULL, 0x03129352E20714D6ULL, 0xD8B5A85558307551ULL, 
            0xF1AC7579B1DFF47FULL, 0xF84C5A8E693A27B9ULL, 0x3EDA3A464DD0D842ULL, 0x372438DF03B3080FULL, 
            0x58E18C873CC2E1C0ULL, 0xAB57E995A671E2F5ULL, 0x1FC0EF0F07584435ULL, 0x432AF7D9C51BE516ULL, 
            0xF32C5D61D52129C9ULL, 0x1E3C786572E4E163ULL, 0x6CC8C64AC21E9876ULL, 0xC1643A59E7B72213ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseCConstants = {
    0xCAD7032F4F4F44A1ULL,
    0x6FBAAC8DA60BF808ULL,
    0xBE9891914DF15944ULL,
    0xCAD7032F4F4F44A1ULL,
    0x6FBAAC8DA60BF808ULL,
    0xBE9891914DF15944ULL,
    0x89C78D04FC725EE7ULL,
    0x6357F3E5B2FE3685ULL,
    0xDB,
    0xDD,
    0xBC,
    0x30,
    0xB3,
    0x1A,
    0xBD,
    0xC4
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseDSalts = {
    {
        {
            0xE863FC390A3428EFULL, 0x3CC103621FE470CBULL, 0xD9BA3B4E6C693F07ULL, 0xDFAEE50EB27F9011ULL, 
            0x69BCDEAE9A3CAEBCULL, 0x884B7344799C6A00ULL, 0x4D21B91932B2AA7EULL, 0xCC18486833EA7BDDULL, 
            0x5721719D9899F0A6ULL, 0x2B64855EF71A14D2ULL, 0x299F826CA54C1298ULL, 0xDE139C33F8EC5013ULL, 
            0x41C1C0214F6DFDDBULL, 0x08600A809F43874AULL, 0x64F037586E635842ULL, 0xD23E00B5CBC57576ULL, 
            0x48227F32B0DFC1A2ULL, 0xCFCBC5E04C96DB87ULL, 0x47A6A0CA2E14AC79ULL, 0xFCF45E21C7E282C5ULL, 
            0xAB06832CEF14EBBFULL, 0x01C7DF09DFDA597EULL, 0x70C89F09D0DD20DEULL, 0xE5D7AFBDB89A7F0DULL, 
            0x02C213B62B4A953DULL, 0xEA9E7DE6C0108600ULL, 0x6E98BC763399A36AULL, 0x8459F3A2C9FEC48BULL, 
            0x03993DA4F7D5B4BEULL, 0x4B9D15F174A30D7BULL, 0x7BCED7884579DD87ULL, 0x1C7BAE9850D0653FULL
        },
        {
            0x7F6A7ED0F3653175ULL, 0x24A323B8A0DF7CE9ULL, 0x8F3844F760E94DDEULL, 0xE7D0FEFE031F0D60ULL, 
            0xE902D9F4B5769A3EULL, 0xEF6493535B1B50E6ULL, 0xE39B03C9ECBCDF2BULL, 0xDF4EA9F8765B5E4EULL, 
            0x59A65117C56B71B4ULL, 0x2CD63D70D795DD5EULL, 0xA3C93C06BAAD775AULL, 0xB1DA4992D96FC300ULL, 
            0xA96D62C908DAFA19ULL, 0x9A6A9FA973408888ULL, 0xCCB366E1322A4ADBULL, 0xA0956ACDACE68EFBULL, 
            0x2F979B0AA535DFA1ULL, 0xF756B4D09F688F51ULL, 0x1FA247AB62ACE235ULL, 0x2DFFC012425A60E7ULL, 
            0xD860B8B93BE289C7ULL, 0xC672862A387C4C60ULL, 0xEE6FC9466FADECC7ULL, 0x682E36455E7CF972ULL, 
            0x0D720E2CD44AE974ULL, 0xF98F89E0DDD57DD3ULL, 0x875A6CB442A7F141ULL, 0xAF88471CFEE00FDAULL, 
            0x1CEB94B28C0FA187ULL, 0x76C8805B17E0D1E3ULL, 0xB3B85BEA85CDD30FULL, 0xF1A52FC8DC02F2F4ULL
        },
        {
            0x41A311939B7713ABULL, 0x13A54EA3F8EB6F24ULL, 0x4D57365521DEA0C9ULL, 0x0BA2650A77771722ULL, 
            0x9F569680ABA6EF3CULL, 0x6318900F1DB20FF2ULL, 0x6D68A897A47C9BE9ULL, 0x3CA0EA84918179BCULL, 
            0xF895E45C826FE5DFULL, 0x0935D049ED6F9314ULL, 0x7F06ADA6BA573444ULL, 0xF5470D2E5C937235ULL, 
            0xBEBC41A44CF1B585ULL, 0x07AB1A6B1FA12C67ULL, 0x6A8B9E2675E400DCULL, 0x697236FDAA758C3CULL, 
            0x1CBFF89EC07435A2ULL, 0xFE6C4F17249910E3ULL, 0xDAC20993E7064162ULL, 0xAE6C483A9626DF8FULL, 
            0x2C3A3EBE76FCBA89ULL, 0x69B49177D0FB47BBULL, 0x68F5B0E71BDC1917ULL, 0x439BA01A8664A263ULL, 
            0x5AFFB7F2886B79F4ULL, 0xD562E9F887CC1D37ULL, 0x1561B19E9673C4C5ULL, 0xA9F82A24DF2C139DULL, 
            0x9DC7D338A6CBE263ULL, 0x6645C30ACD54FCB8ULL, 0x4334F1DC194811A4ULL, 0xBEE3E5CC3693B948ULL
        },
        {
            0xAAA2FBE9CAACAD18ULL, 0xD752037C6AC7FC25ULL, 0xD87885E8DA88C100ULL, 0xBE35E36F7B11745DULL, 
            0x059CA45C75FB3368ULL, 0xA92DFE39698BC357ULL, 0xE6AF1EAE87315481ULL, 0xDD0D0D5686D33838ULL, 
            0x90752B131A216D6CULL, 0x6C9B4238C212DBA6ULL, 0x4F4511316C8AC073ULL, 0xAC58E0385498F574ULL, 
            0x8741604E75973325ULL, 0x4C141BE51EC94B38ULL, 0xFC69BDC9C8ED98A3ULL, 0x57FD9D108431FE75ULL, 
            0x0139F572691A45ABULL, 0xEE6DFD9593612139ULL, 0xF013F09C51143DA8ULL, 0x709341B8F479A287ULL, 
            0xD0026CC4BCAFA404ULL, 0xED0CBCE93FEE8FC2ULL, 0x701AD4EC978830ABULL, 0x8BA2AD6F99F323B4ULL, 
            0x3D53EFD53FFE99CEULL, 0x80E1BE3BFB906D1EULL, 0x770BF6CA1FB8EA43ULL, 0x21F574F9D5D85426ULL, 
            0x5C9629702EDB875CULL, 0x7773A8C3F5A3E9F1ULL, 0x4997E4BA7090C816ULL, 0xA1116C0D0139D417ULL
        },
        {
            0x49DCDDDDB71DFCABULL, 0x7BAA0607D99B68D5ULL, 0x45D346BD4A9F8400ULL, 0x5808F2AAEB3FAD03ULL, 
            0xEDE4A4E8823CEDEBULL, 0xA83D73D4449570CFULL, 0x4449CF4720523BCFULL, 0x58D1036E93505B4BULL, 
            0x9EE6B259A898A5CFULL, 0xDB3557B1E2F815F2ULL, 0xD774D985A5541348ULL, 0x69186DB3C399C607ULL, 
            0x4F4302145C883C62ULL, 0x270F5DF2C282CAD2ULL, 0xE34DA24E6D4433F9ULL, 0x81D4F28A93FABEC0ULL, 
            0x0C07462706295BD7ULL, 0x058245A2A11452E1ULL, 0x2050C55CCF439CAAULL, 0xFDA72524DC8A26E3ULL, 
            0xDDA6F21C9208A95CULL, 0x8B6E9D3F278D04E2ULL, 0x5EBF44D0C0CFB18CULL, 0xCD601AE8D5D20E2EULL, 
            0x7740122B6A71C5C0ULL, 0x0AB094FF64A2CF62ULL, 0x592B0FF7E9C278CBULL, 0x7DA12669CFA7CE44ULL, 
            0x40F648A997FF7188ULL, 0x936D9FB4DE49FE76ULL, 0xD2F3A25F2800C17AULL, 0x5526950EE8FDE435ULL
        },
        {
            0x316AF0FE68F17B38ULL, 0xBDA94EF40E58C82DULL, 0x81AB74022480410CULL, 0x0F77DFC473F7B074ULL, 
            0x91E73F27022358B4ULL, 0x1D23978B748F4CEFULL, 0x4C9E7F07A175601EULL, 0xCC3A8C13817B15A2ULL, 
            0x776E6613A67C8D91ULL, 0xF81E40F2FDE58CF5ULL, 0x14C05938ABD93B5DULL, 0x80A2E21B236113FCULL, 
            0xA2DA3B8297782552ULL, 0xC7BD30E41A644A8BULL, 0xCC4B480EB2395C98ULL, 0x265AB2B9481A837FULL, 
            0x45214E9D81D0C932ULL, 0x9D6541FB31C7AD08ULL, 0xB8F53CDBCE1D3880ULL, 0xE715EA6E450D644BULL, 
            0x3BFB2CFA70F889FAULL, 0x5A1158A58A75EB2AULL, 0x6C02DA260BFA285FULL, 0x59CCA0E042E44587ULL, 
            0x74B28705F67CE834ULL, 0xE7B3F78C064B753EULL, 0x4BB91D9F745B01CFULL, 0x7F190E888EA3E8F5ULL, 
            0xDFC4B186C7F3281AULL, 0x2EF3B0BC0EDEA4CEULL, 0xA444F1E8D49382CFULL, 0xFD4ABEA1DE2459DDULL
        }
    },
    {
        {
            0x3E26666DDE80AA28ULL, 0xCFCF6F121DA27AB4ULL, 0x5646A6BE1AF19EBFULL, 0x9A5CC59E3D624AEDULL, 
            0xC798392825C6157AULL, 0x0A2BBAF4B5F1E1E8ULL, 0x84551A21B65860B1ULL, 0x25CC2D39EFE0F10DULL, 
            0x76B217240ABB35E2ULL, 0x58D54AB86220EB01ULL, 0xA3231DFE85554B1BULL, 0x14E9CA7B3F400235ULL, 
            0xE830E3590CE8E524ULL, 0x8E09DD75D20DA339ULL, 0xB996F19472444A74ULL, 0x64205656ABBAD90CULL, 
            0x03382CCF5DCBAC50ULL, 0xC1925F8FFBBDD2CDULL, 0x96AC72952E9F595BULL, 0xC8F0DA54DBEB69C8ULL, 
            0x418FDF6559ACA084ULL, 0xB8A814C8C56F1A6CULL, 0x5742BB0739629ED8ULL, 0xAC4E0A6FE64CAA5DULL, 
            0x0FAD969F6DBB0C45ULL, 0x0015F9EA4EFD3552ULL, 0xAF9DDC2E6AD57B0BULL, 0xEC7DFAB1A68F7012ULL, 
            0x21DD64814D4E9D53ULL, 0x3AC95CC851188F08ULL, 0xE6DFBCDB36B99EB8ULL, 0xCBCAF7723548B0BDULL
        },
        {
            0xC537129F8F03EA10ULL, 0x4E4A3881C94C8D95ULL, 0x694ADA5C1CC2645EULL, 0xE3559B919F8F4EFCULL, 
            0xD4AF5BFF49B63C2CULL, 0x7D5F690FD59F39C8ULL, 0x6C1CE5B90ABE3398ULL, 0xC3AA624D7520C1A2ULL, 
            0x4AA1D5101127863BULL, 0x354F54CE4B5355E8ULL, 0x3EF0C68495F66A79ULL, 0x5F8B9B51CA0A73FEULL, 
            0xF33BD9F4529DD3EEULL, 0xEB98D31F46A5836AULL, 0xC74C94C169C073D7ULL, 0xEF843E1561AC656AULL, 
            0xF114E18D1ECC64B4ULL, 0x3C4DF5192EDD51B8ULL, 0x27CF39F6150AB145ULL, 0x21FAF6DEC780E2F9ULL, 
            0xD044863FE6E46743ULL, 0x1A3FF84A065C3027ULL, 0xAD5A0BAD50945AD1ULL, 0xAEDF3DD9060DB5EBULL, 
            0xBA254C60210DD5D0ULL, 0xDE5708EBAFB8AF3EULL, 0xD9393BE3F40E36F9ULL, 0x0547389A1213DC51ULL, 
            0xB8138EAC9A2EA1EFULL, 0xEC81A513B8A9DA0CULL, 0x19BB11C7399023F0ULL, 0x06443BE18B7191A9ULL
        },
        {
            0xC55F615E7A5C823BULL, 0x6AD12DA89EB136A5ULL, 0xBBF22B2A01C14990ULL, 0x42875760A78A95C6ULL, 
            0x791FB8B034CC9291ULL, 0x9F9A9C0B30B8BB5AULL, 0x8D841A3A52E896B9ULL, 0x49BB5DDEF31F8291ULL, 
            0x053A5F11AFEF067BULL, 0x1DA36919D12931BCULL, 0xE7FE0DE68450D95DULL, 0x0F46D0DD82919B19ULL, 
            0x1AB2EDB604199BABULL, 0xEC5C12AF553C8A7FULL, 0x39CB35ADBC5F98DFULL, 0xF97769AEC93BAD99ULL, 
            0xE7941F8603E54B2DULL, 0xA3FB620F65FDF7A6ULL, 0xF37E20F0D3988D39ULL, 0x486F2E008C33B8C5ULL, 
            0xDD22CE20197591DDULL, 0x781B2E3F2AA48726ULL, 0xD5444CBF02742F85ULL, 0x39C51F11642DDA13ULL, 
            0x8DE7EEB35C379D52ULL, 0x95D311FBCA43632EULL, 0xF4598431085F5676ULL, 0x64B5041918E46415ULL, 
            0x7AA31DA194F4E245ULL, 0x43BE040782B875A8ULL, 0x1322D920DAA632D2ULL, 0xF3308C53382FF4B4ULL
        },
        {
            0x4D52AA9336131C1EULL, 0x091E04CA5C5FA6D9ULL, 0x89D2324340B50B06ULL, 0x2685870683F44C5BULL, 
            0xEB212E0C2012CDAFULL, 0x92B7ADE881F559A8ULL, 0xFF51A6564D9A61FCULL, 0x02B0BF09BFA9CF7AULL, 
            0xBAA4E265D97DAE8FULL, 0x0D9E4C9065782F48ULL, 0xC5E9C1908FE0F94EULL, 0x63DC9995A0750561ULL, 
            0x552C52414763ED22ULL, 0xE8534F0CA7937E85ULL, 0x2A0219A7C2DE2ACDULL, 0x3AF3668E9ECF70DFULL, 
            0x2F9B18E9380F3094ULL, 0x78AE113F4BBB5809ULL, 0x724D94176D1C7D83ULL, 0xC9B7FF58CC1DDB08ULL, 
            0xF61DB37768B69839ULL, 0x4A0F4A268ECC4A3DULL, 0xE5B8ABEEED4BDF65ULL, 0xF051915A5EF46C09ULL, 
            0x875F6B89A3DA1EF1ULL, 0xA47AF9E4D71FE2E3ULL, 0xBF8A22FB0CC5D718ULL, 0x2D6C64F215FF8C95ULL, 
            0x5F06CE3490B22235ULL, 0x87216E98FC99DA64ULL, 0x344D410B063B0B6CULL, 0xD5BE133C4815440DULL
        },
        {
            0xEBBBC246E87252B2ULL, 0x589D72273ABFEF39ULL, 0x1A4F56E7F3C298D9ULL, 0xF82441D8BD6FC691ULL, 
            0x46AC96338EAD4706ULL, 0x821CABECE6504060ULL, 0xA3C02778D71AE93AULL, 0x0725E0BEFFC2EBC8ULL, 
            0xFD27955D4528EBC9ULL, 0x2F2D221E28BF78CFULL, 0xD4CBF482CEC67705ULL, 0xF6D5963A7EBD058BULL, 
            0x0C4E2B6EB677E785ULL, 0x0BF10BC2AAACAE38ULL, 0xA1448BCEE499CEC5ULL, 0xF310551275F30098ULL, 
            0x94171D301114BE23ULL, 0x46480E0E050D4007ULL, 0x28D7D7B5DFB40E29ULL, 0xED38C9E00EB80376ULL, 
            0x91CBD468D535FE26ULL, 0xE8867203F4C10883ULL, 0x283F6143C0BA16D3ULL, 0x4B9DEEA9ABA968CDULL, 
            0xC2205D83C16A8BD0ULL, 0xA0CC94D27AB24CB1ULL, 0x33E0F8CED3FA58E1ULL, 0x86A15CFA932C2031ULL, 
            0x662C8BEDC814001CULL, 0x12E0BB940451AF27ULL, 0xA0AEB88C9E1BE07EULL, 0x30E82322C82D8943ULL
        },
        {
            0x30EA74630660F248ULL, 0x4D71C18E77BB3A15ULL, 0x641FD624898FC13DULL, 0x911B79B7431AA05DULL, 
            0x202132F29728AFF3ULL, 0x72AAFBA155C8A163ULL, 0x1D81B6A458E5EBA6ULL, 0xE61B2119B3536CB7ULL, 
            0x678CF218185F42D5ULL, 0x1CDDA0CF9BCF240BULL, 0x59BCC5BB8A099E9AULL, 0xF840AA530D11B159ULL, 
            0x6A7E24F7A7F97EA3ULL, 0x4EB2EB1EE7A89E77ULL, 0xA8854FFB7BD7AA0FULL, 0x5BFB02C3FEF57739ULL, 
            0x3861FE7085BD4A63ULL, 0xA9322BF9FCFA19D1ULL, 0x12F1DD78D9CAFDA0ULL, 0xBE5398C405F7706DULL, 
            0xF6CA8330F3C5621EULL, 0xF42E724FEDA0EE7CULL, 0x3E6DA436FD1CD34CULL, 0xC64F04431CBB9D22ULL, 
            0x2FFA08D399B7F2F5ULL, 0xA22A014EBE15F08DULL, 0xF5EBD1E8187E2620ULL, 0xA739B3E494D20DF4ULL, 
            0xA555F8A67DE19147ULL, 0xCD9A698586060EE9ULL, 0x8612A2E2962B7E63ULL, 0x5079F1862C9835B8ULL
        }
    },
    {
        {
            0x8C3CF0C29F873E0FULL, 0x6FFABC5160217547ULL, 0xC080B7D89A51DE3EULL, 0x1FED44459C7AE492ULL, 
            0xB14584E8CA2E69E3ULL, 0xE8DDC4F8F23885D0ULL, 0xF51F95ABD0AA6B4DULL, 0xBEB5DF4F7123D5D6ULL, 
            0x9885C80C5A67867EULL, 0xA55915A6A557F3DFULL, 0x2F88D5921A4EEBBAULL, 0x8FE4C0DDEB47687AULL, 
            0x87AC61D6DBA5194DULL, 0xCA89CE6C9EF51DD1ULL, 0xD453E40945744EBEULL, 0x29BF6212A19372B2ULL, 
            0x17BAE6E67E07DA6CULL, 0xC1B36C7CF55B4258ULL, 0x9B8DA2DC8C2A3229ULL, 0x2AD61E536B9147ABULL, 
            0xC29A022F5CE15308ULL, 0x27B2A9F029AF3061ULL, 0x857F4E5427198BADULL, 0x558D896F89E2A661ULL, 
            0x60B6A797DF9211BEULL, 0x95542740DEE0B717ULL, 0x3DB29684C578BD82ULL, 0x7D45C0FDA0A01761ULL, 
            0x33686150ABB6CAF2ULL, 0x9360C7803C88E4D5ULL, 0x225A24290430CE0BULL, 0x7F029507AB9C03D6ULL
        },
        {
            0x3EA68B39D7E6EE1BULL, 0x8CB981600427974FULL, 0x8B426F4F430459F3ULL, 0xF1FD5709947D7F5BULL, 
            0x0365F9AD8C61AB0FULL, 0x802CD991589CA5A7ULL, 0x9D9150D814F7231BULL, 0x461FF49489248373ULL, 
            0x275F524473915E77ULL, 0xC33CDD43E3AE6966ULL, 0x1FB65A9CBF94FD15ULL, 0xA32790823BE39B3DULL, 
            0x5260D263FB1D1FB7ULL, 0x2AA976B6C6A25059ULL, 0x5E82375852238BA9ULL, 0xF44222E9A1AE6977ULL, 
            0x93E07BB90F0CB849ULL, 0x6D02C82399E8CA7CULL, 0x0DD9740A04AB0B32ULL, 0x8467575FADFADBBEULL, 
            0xFCCAB9F36C2895A3ULL, 0x4B9D8306A198243DULL, 0xE7AD7019807F241CULL, 0x115DC1399AAA6D10ULL, 
            0x03D9E442D6159969ULL, 0x57A4ACFFB4BBF56AULL, 0xB779CA8426E39589ULL, 0xA05B83D099229598ULL, 
            0x6941E0309079A921ULL, 0x63C4B2893DD3A908ULL, 0x25E2234D1E688A23ULL, 0xEA022454453EBEF3ULL
        },
        {
            0xF798765564393026ULL, 0x335F3A6AD1632047ULL, 0x848B03589CF4A282ULL, 0xB8F51F7CE0842A44ULL, 
            0xABC4AD95C4CD4EA1ULL, 0xDD6AC6318E21ED2FULL, 0xA0DFAD77C5CF4B18ULL, 0xCBE5BF963B06034AULL, 
            0x075BE1886C48ACE1ULL, 0xE8210133B9ABB80BULL, 0xECD7176AB75D59D9ULL, 0x739521AB0DB3AF4DULL, 
            0xA0A2EB7670F6AB2DULL, 0xE749665CFA066EC8ULL, 0x1E0E7E16603586A7ULL, 0x4E96D16201608E7AULL, 
            0xDA7CCBF6FC9BA233ULL, 0x5C7C000617B66D21ULL, 0x28DF69C1EC456AD5ULL, 0x8CDDC94424BE1783ULL, 
            0xB2B77CAFAD1206A0ULL, 0xA0C43B620A744BA4ULL, 0x491653197EA9A52EULL, 0xDA1A69A97F7B11DBULL, 
            0xD2D9ECC0C5C4C5D0ULL, 0xFB1B7557708817B2ULL, 0xF192AAC33A7A231AULL, 0xACF7510013E6112BULL, 
            0xEC9C0DF6AE6DBF1FULL, 0x6864852D91E057B8ULL, 0x6412F5FBD8F1E348ULL, 0x0F011D82BB543FD0ULL
        },
        {
            0xFBB412159A69606CULL, 0x0AEBE5DF2DA2D4E6ULL, 0x1B897413F5000E00ULL, 0xF97CFAD55B4DC273ULL, 
            0xF093AE1873C30467ULL, 0x6FAE2140FFE61946ULL, 0xFE1FE71E1BB5CDB1ULL, 0xE9C304982D68A728ULL, 
            0xAD4CCFBF3E8F4396ULL, 0x6A72C64D3C9E00F4ULL, 0xAD3D6CBF91938F82ULL, 0x4106E28A9A2514F6ULL, 
            0x5BC2978DB23EF53BULL, 0x78938A071024136EULL, 0xF9D328E6633BF3D3ULL, 0xD40F73E486658497ULL, 
            0x9B4E4E5D17D5A9A6ULL, 0x22BDA0E46CA00CE0ULL, 0x6325C5984E55F826ULL, 0x368E7DE9EC5C0423ULL, 
            0x8696AEF0F46660D6ULL, 0x60EF9E5DDEA20155ULL, 0x14824462C1C4DE48ULL, 0x0643DF9D376A3B76ULL, 
            0x2F5C17C66E79CCBFULL, 0x073B790B904F71A9ULL, 0x4F157F55A7F2A8D9ULL, 0xE8611AEBC926ABD9ULL, 
            0x319AB58546BCF6A0ULL, 0xB8DDFB679F0AE70BULL, 0xE05BAE2848116CF1ULL, 0x675CB07766DD37EEULL
        },
        {
            0xC5BFC2AF96E2EC9DULL, 0x6E27CAE0B7E3D71CULL, 0x20AB57C737220210ULL, 0xAB2AF15374DFF30AULL, 
            0x04022393705CA475ULL, 0xA3A6ABD33021EFEAULL, 0x74E27D163A76E863ULL, 0x71638980DE040502ULL, 
            0x580012FBD8CA7314ULL, 0x1CE36E2068E5A8E8ULL, 0x15590DBF58CAC579ULL, 0xDAD79F59F59005D5ULL, 
            0x23228329C6C39BD0ULL, 0x214E99739B831D26ULL, 0xA5A1139E711FE5B3ULL, 0x0B0ACFCF957E7B36ULL, 
            0x50847BAEDF6540EFULL, 0x01B55740F5970718ULL, 0x6FD64FACA809EE4AULL, 0xC693722AC7DAB4E8ULL, 
            0x7135C8ABC55131D9ULL, 0x17D2DEEF5542F4E1ULL, 0x3B20ADDCE5BD6C30ULL, 0x4120732348A8769CULL, 
            0xF5BC717CC9611CB6ULL, 0xC45A24775AAE8384ULL, 0x540C61CEFE9C696AULL, 0x8C6807E2E3B17AFBULL, 
            0x3A933748287F1D38ULL, 0xADED2A3230672F0BULL, 0xA0BF0DFB0F5C1D55ULL, 0xD22C5099EEDA54CBULL
        },
        {
            0x4933E8031B152E24ULL, 0x46A2D79E321DE369ULL, 0x68817BC9E55D0145ULL, 0x97702C953ADB0009ULL, 
            0x53782F8DD668674AULL, 0x25D2BDE1EF9E1F02ULL, 0x7288148E48AD126EULL, 0xB6CAA41C313D7641ULL, 
            0x1408BA299F5B5929ULL, 0x9ECEAB00910C5DAFULL, 0x638403A836E103E4ULL, 0xF6CC78B36E233E9FULL, 
            0x4AD9CAC577A00BDFULL, 0x45883F8333900DCCULL, 0x1E3FFC479A831920ULL, 0xAFFC920DD7C5F4EDULL, 
            0x6A67829F26292840ULL, 0xE1FA5DC9263B4AADULL, 0x767AC50FD8D53D3CULL, 0x2D15BF6422EBFE3CULL, 
            0x3121F397DC63193DULL, 0x939F98296A153F06ULL, 0xDC059382751FB383ULL, 0x8D886E40CA0F0EB2ULL, 
            0x0CFE100C29292AB6ULL, 0x9C1033246BADCB00ULL, 0xC23219BAFFEC4B82ULL, 0x82B905B383C2142CULL, 
            0x1C8C15312823A017ULL, 0xDC703591C5BED3A8ULL, 0x49EAA62727051A96ULL, 0xB6893AAB4DB7EC5BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseDConstants = {
    0x64571634CD375383ULL,
    0xABB5F75B3E5DCC89ULL,
    0x590A6DD072C12F13ULL,
    0x64571634CD375383ULL,
    0xABB5F75B3E5DCC89ULL,
    0x590A6DD072C12F13ULL,
    0xEB44E200ACA5E387ULL,
    0x393BA3D91EE87DF0ULL,
    0x73,
    0x4D,
    0xCE,
    0x3E,
    0x19,
    0xBE,
    0x7C,
    0x3C
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseESalts = {
    {
        {
            0x9080154E8DAE5AECULL, 0x8352E6EA25F5543EULL, 0x3F2CF79BCB963650ULL, 0x75C1F9BBA076A2ACULL, 
            0x4E469AA3936FC91FULL, 0x047F7EBEDA1DC3FDULL, 0x3953125E67EEE4DAULL, 0x476B59DDAD74E485ULL, 
            0x187C6D3F543ECD28ULL, 0x3D74D2EAE941FE69ULL, 0xFD0DEFCDD2CE4BFFULL, 0x525D6B97BFF17849ULL, 
            0xB1712EAC284F63D3ULL, 0x41F27A823EE8E1B1ULL, 0x638214E8648F81C3ULL, 0x2174DF53CC5D9619ULL, 
            0xCF7833117EABEDF5ULL, 0xBC9C87D6782D9419ULL, 0xB09E1730BACED537ULL, 0x4E7E1AFC5D75A54AULL, 
            0xCBCEB788A217C018ULL, 0x42846C116B72B466ULL, 0x86A2E7F7C0B4DB92ULL, 0xE2B384D71637EB56ULL, 
            0x2D8BB357BA8F326DULL, 0xFE3343C5E4E95298ULL, 0x6AA80FF839462450ULL, 0x0E0DB512FB480B77ULL, 
            0x52687FB4FF310344ULL, 0xC10DE2B6B0CFCF47ULL, 0xAE90446E4B737354ULL, 0xE89D69757DAF8C88ULL
        },
        {
            0xEE2A7CCA95734383ULL, 0x1033FFF2C5EBCEACULL, 0x686778C05944C617ULL, 0xF9BD184FB8F1DD69ULL, 
            0x43DB6071A3E13C10ULL, 0x434C0321FABA3A47ULL, 0xBDD17E6688EA8B7EULL, 0x7F04005B3D5D4940ULL, 
            0xBEF18B37F93FF2CAULL, 0xF1FF5EE7FC88E886ULL, 0x531540F0663E6078ULL, 0x2C925EB273581833ULL, 
            0xB542A87A715DE86BULL, 0x52793D250061343BULL, 0x445FCFC0554678D8ULL, 0x4B6838D81AB05D86ULL, 
            0x7769C9A6E9B5D1F5ULL, 0xF6AD31A54C304751ULL, 0xB3F82A50C77C2A04ULL, 0x812A5EF3915B1FB4ULL, 
            0x6739F17DD256192CULL, 0x586E42577826F769ULL, 0x15C45C3B4E517CFBULL, 0xC730DB3679D1D8BBULL, 
            0x4BF9BF21FE89CF4CULL, 0x9D42692503CD2171ULL, 0x930B0BEA5814D49FULL, 0xCA82686B94F03EF2ULL, 
            0xE16D0F52A14F5FB9ULL, 0x1D44A6F75C45EDC8ULL, 0x2ED27BCB14169435ULL, 0x2BC6CE4E5BAE659BULL
        },
        {
            0xE521B311B56557DDULL, 0x4B1748CF2589600CULL, 0xC501CBE838C0D156ULL, 0x6721B5A5BA7A4D03ULL, 
            0x52678C8AB22A3AE0ULL, 0x0F2CD8400657D049ULL, 0xC96F7DFB250B2D84ULL, 0x50911170FCCF9ABEULL, 
            0x4479269D98AA20F4ULL, 0x3C7E3A0FB4CD388FULL, 0xE3F227B3F301388BULL, 0x6D57B2125968FC02ULL, 
            0x078237DF150319EDULL, 0x8644E465BE944709ULL, 0xE054DADD032F3C1AULL, 0x44D8C9FAF6EF2196ULL, 
            0x4BA8AD0F74CE41EFULL, 0x3D40CA67354A96D9ULL, 0x443056AF4F310064ULL, 0x71DBEBD780B3C629ULL, 
            0x74DBAAB0CB586429ULL, 0x6FE3D7D8810B212DULL, 0x5974803406240574ULL, 0x2A43822EA0A78908ULL, 
            0xF5C21E250A997902ULL, 0x46F16101B23DAFDBULL, 0xA1BC4DBC5BF81ACFULL, 0x45EFD1434C1A5060ULL, 
            0x6A14618966F41FFBULL, 0xE5186AB2DDF0E130ULL, 0x4B9A6D8112FAE00DULL, 0xA98174DFFD96ADB6ULL
        },
        {
            0x1E1628F807292F62ULL, 0xE16662912B8EB8BFULL, 0x6FE2CFF61A309734ULL, 0x4C09AA6B2C29EE2EULL, 
            0x36AD6B8B58286303ULL, 0x2B63FD9D82DD1463ULL, 0xEB74DF8651B474EEULL, 0x575F435F486C8061ULL, 
            0xDDE44455FF4745D3ULL, 0xC893D6C4FAE9F786ULL, 0x8A396EB1DC5C6B4DULL, 0xE0F8123F1651E4B4ULL, 
            0x49835B9DC8CB2DC7ULL, 0x6A9C87CD9C794507ULL, 0x0212D8782274D0B9ULL, 0x4F6D09D24E4D1E35ULL, 
            0xDA1D3E5C144BCC19ULL, 0xB930338643ACC114ULL, 0x8FC6ADC1282FA648ULL, 0x694261FB4EDD42E8ULL, 
            0x7693D83FD5815CBAULL, 0x96D714050173A50BULL, 0xA98421F018A3F518ULL, 0x911EA8DBEF0693F8ULL, 
            0x5353A103463206F8ULL, 0x1C3EA10325CF2F07ULL, 0xA2E052C187CEF7FCULL, 0xC9A81F7E9F5D3AA6ULL, 
            0x82C047861AD04421ULL, 0x231DAACD4263B028ULL, 0xD8C42FE0E7068D95ULL, 0x106C621143E66723ULL
        },
        {
            0x8D507B796C7595DCULL, 0x0FCCBF33470F47A5ULL, 0x1E8B3545B0C15765ULL, 0xDC361023837D9CB5ULL, 
            0x9112BC01CD092F99ULL, 0xE0E78DFF65C1EF93ULL, 0x40405DC7D0C63D74ULL, 0x7978DA20F3570FBCULL, 
            0x82AAA5D7B9581F4CULL, 0xD009F153E1B20801ULL, 0x1588E503146AAEDDULL, 0x6F74C01B5D1D7F2BULL, 
            0xF75BCC7DA6B78780ULL, 0x5D78DCF005B2E9D7ULL, 0x1E6CEAFCAAF6E42AULL, 0x7802EDDA7E9AB32AULL, 
            0xC77977F7E7948FE8ULL, 0x8D09D6151796DE71ULL, 0x2B303232CAB0AAAEULL, 0x22B2A07126C8D6F2ULL, 
            0x939D4077CE5F4BC4ULL, 0xDBF5C945FAACC6DDULL, 0xE1D6123DC2061F09ULL, 0x12E7DA8288399B8BULL, 
            0x716433FC743FC7F2ULL, 0xFC7674E1269B9932ULL, 0x92030A11B21BD678ULL, 0x2F0ACD1B59A99DBEULL, 
            0x3C78695D0C754F2EULL, 0x798A62036D3FE809ULL, 0x1A63F8F4C3D2F7C5ULL, 0x87A3DAA63070013AULL
        },
        {
            0xB681BDCB68E09F11ULL, 0x4A597258845AA4F0ULL, 0x4B16AC028F3E2879ULL, 0x905B30CDC98451C6ULL, 
            0x878DB1D1EF5C828DULL, 0x8EE7343AA2973B8AULL, 0x105A1F68A9502557ULL, 0xE3D76E1FABBB4D6AULL, 
            0x4DABEB8323D426CDULL, 0x56F09B2E5FD67078ULL, 0xAF1331D42EDB1031ULL, 0xBA8B2160108154D0ULL, 
            0x2570A61C1345E5FBULL, 0x1BB96411337A760BULL, 0xFA9BCDFC7C1DD61DULL, 0xEB458697FFF891FEULL, 
            0xDF4DDA312938A01DULL, 0x94D774F24FBB4B63ULL, 0x147240B1432F0ADFULL, 0xDB9AC822F1A3B613ULL, 
            0x8D7BEA07A04E25D2ULL, 0x17C0143EB782EAF3ULL, 0xD0CA4FCB87E58EF4ULL, 0x0E1C05744CAA1E9DULL, 
            0xE2FCEDDDEED5F22AULL, 0xF5D52FE99C25303BULL, 0x65707760A51C945BULL, 0x1C590EEC5F821C80ULL, 
            0xE5AE34FE99C347DFULL, 0x63D4836FDF123643ULL, 0x330EE3C511BE0D14ULL, 0x8614D52FC03335B2ULL
        }
    },
    {
        {
            0x2891C98E17C447B9ULL, 0x6702E337D3008A18ULL, 0x7F6B2DF0051529BEULL, 0x60F9DF66F8D20BE8ULL, 
            0x6FB4F29F36BB0ED5ULL, 0xB467FF1AD062E83CULL, 0x27F452CF330F6902ULL, 0xAB45FE382AEF65A8ULL, 
            0xD7933BA664FDD41DULL, 0x69C97282EDD9FFF2ULL, 0x417FCE586C3CE294ULL, 0xF362D136A7F20A8AULL, 
            0x763F73473FFD01BCULL, 0xC8A7EEC49F02B77BULL, 0x1E90B10B31E4E81BULL, 0x339E958D17BC56FCULL, 
            0xC5A3948138460E7CULL, 0xFA97354DD5E925E7ULL, 0x5F3BA285BB4A4D8BULL, 0x458E2E33F4DE6D3AULL, 
            0x33065502300245BAULL, 0xC56A3E1F84DCFF63ULL, 0x269104A89F8D54A8ULL, 0xA12927B96C1CEFF9ULL, 
            0xC81B43E54C26A847ULL, 0x8F659B26B9570A36ULL, 0xA25DB39C3AB068CCULL, 0x21D51D7E7AE95AE6ULL, 
            0xA0A136B7D98442E0ULL, 0xB2CBDB2CA1F8F740ULL, 0x22AC3E7ECD9D6A42ULL, 0xCB530AD4F7522F7FULL
        },
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
            0x90840A352ED0B915ULL, 0x32203BDB44220866ULL, 0x44D67AAF38CF45F3ULL, 0xD38591F855EF321DULL, 
            0x61F4D2893BB22B22ULL, 0x5D43F5EC726DC42BULL, 0x63D22B3BF578BD4DULL, 0x31488FB7EA31FBF6ULL, 
            0x80DF33534B4B5758ULL, 0xAA87464E7BCFE7EAULL, 0x13A4A09229D21568ULL, 0x74EF55E6DBF87569ULL, 
            0x51A99E851CC2D555ULL, 0xB6D52C8B120D344FULL, 0x93BC6D6B973293A6ULL, 0x3FEF1CEDD96B2C31ULL, 
            0xE0F69329AC220790ULL, 0x71D244CF14D7C7C6ULL, 0x358133ABD8FA9B7CULL, 0x46ACE66BB967B838ULL, 
            0x0AAF80038EDEFA11ULL, 0x9C6A85B98954E792ULL, 0xEF870D22C1654409ULL, 0x115350C098128EE6ULL, 
            0x76E943B0D27742C5ULL, 0x579927DF6813ED00ULL, 0x50C1C069C93D7013ULL, 0xB0A7D888718A2C5AULL, 
            0xAACCB6E702DB1B39ULL, 0x89669B037CA2D315ULL, 0x68DCE03E647A3B39ULL, 0x8A9CE3E2A0AA4042ULL
        },
        {
            0xECC46235CD3D5FC9ULL, 0xBD29957799414645ULL, 0x5E8CDF3AE392498FULL, 0xE24D537459641FB4ULL, 
            0x3D01606160A45C88ULL, 0xF4465B3F4996FC67ULL, 0x381FAAE8FE50741BULL, 0x62EFBF0032595E80ULL, 
            0xCD2BB099495C266AULL, 0x04C17C3EEC73E387ULL, 0x6B68D72D078E824EULL, 0x5B09A7FAE7097406ULL, 
            0xE422728BF0AFBD2DULL, 0xC7A06B7352FC5C04ULL, 0xC4C1AC317E63BA10ULL, 0xA136A1F8A81C4EF5ULL, 
            0x6069629CC75CAFD2ULL, 0xE2B1F5AFB0DDA945ULL, 0x32C0DE5D0F5D1ECCULL, 0x3E177815629C5D51ULL, 
            0xE439E448FEAA2694ULL, 0x6E3E45B4183A0DD7ULL, 0x69D26076A7A530B0ULL, 0x51B598D4BBA95B86ULL, 
            0x2C563A7952076DA0ULL, 0x002E3A55A90A8716ULL, 0x6CFA9D9186348B14ULL, 0x9E15B9BB1F266277ULL, 
            0x3F5629D1C703573EULL, 0x5D4BA03724776294ULL, 0x745F53D409B268ACULL, 0xFE47A26ABED74551ULL
        },
        {
            0xBDE0554C2553DEB5ULL, 0xD600D31AB5E0BC6BULL, 0x0164FBD4B62A8949ULL, 0x92EF0EF9CB28B514ULL, 
            0x477F753F54CB0EF8ULL, 0xCBAD1B3643961C4BULL, 0x0811BD1E36396563ULL, 0x9E71EB6559646109ULL, 
            0xA0F86585E5238F6BULL, 0xD47BD7A6BB13318CULL, 0x1DCED5F48DEF3168ULL, 0x4F068DB8B65E4B39ULL, 
            0x14C1FE013063FF47ULL, 0x6A3746069D19F534ULL, 0x9B1D6E5CF2060A7BULL, 0x3D6B6DA7214F83F4ULL, 
            0xEFCFB8502ABC95A2ULL, 0xEFEFAFB1A9FEBC08ULL, 0xF5EA0ADA3E0BF70FULL, 0x9948F77C63D10E19ULL, 
            0xD8B7EC65F9F0F96BULL, 0xCDD267F7656B3962ULL, 0x70CA526C5AEB92B7ULL, 0x2B581D93C803E2ADULL, 
            0x5E784B435A37327BULL, 0x1FC7AB5CDF2A2CDDULL, 0x14866F374FBA8C0CULL, 0xDE8BB7701D2EFF1AULL, 
            0xD85F4AA2E4AEF3D9ULL, 0x20D6F22501F2ED9FULL, 0x90B1339EB81EE042ULL, 0x8EA29126E1B8EEA6ULL
        },
        {
            0xCA7ED22F8DDDC2D1ULL, 0x3A2FDB9D3BB5457AULL, 0xE89761F072583E37ULL, 0x12DC26498A8E3839ULL, 
            0xAA90CB52669A436CULL, 0x9C95D4CF22DA7843ULL, 0x4441062E492277C8ULL, 0xC650607B25E7A6FCULL, 
            0x147224314E0CF4B6ULL, 0x841FA72302097CFAULL, 0xB30B31CF62845D83ULL, 0xBE80C87DBDD21365ULL, 
            0xF4F4EFB830974DBFULL, 0x4B375553FB1AE5EEULL, 0x7C072FFB44818DD9ULL, 0x62C69964872C03AFULL, 
            0xC945BB722A45E10FULL, 0xCD8711E23A042A60ULL, 0x533E1000166C6866ULL, 0x1C3D682EE885F4C2ULL, 
            0x61C608AE09C95EE9ULL, 0xE1372BC04E959B33ULL, 0x7A2298B9747E750CULL, 0x22FF72500464733FULL, 
            0x8F3F7E532F2A4183ULL, 0x5A3D5A7103D84CA4ULL, 0xDB14EBBE365C002BULL, 0x3C93A36512B36121ULL, 
            0x0884FF62F0F7C06BULL, 0xAD70633D51F19A0FULL, 0xFE4D8FEB2FB48C65ULL, 0xDE8278C1D9DA5C79ULL
        }
    },
    {
        {
            0x7A7B7D2F6783CF30ULL, 0x9878810C6ECF5282ULL, 0x73B8D50F88E330EFULL, 0x517614710FAEF404ULL, 
            0xC213BCBC295FD441ULL, 0x9E4EDAAE9B0CFFADULL, 0xD960AD77DF1D7EF8ULL, 0xF4673DABB3F9C435ULL, 
            0x4F1E146B89644798ULL, 0xD988E659088B8340ULL, 0xA613547029A2FD1BULL, 0xDC769DC52118AEA0ULL, 
            0xD2C5ADA43276F497ULL, 0x721B6D82A8EAC71BULL, 0x6FE804BEC51BB61CULL, 0x172A2A840243862DULL, 
            0x4BEE34C321A05DB4ULL, 0x1F82FA4A0F9C51CDULL, 0xAC4B5794F86D5B68ULL, 0xADA37BA43D6D117FULL, 
            0x9518A74CFF9C2C69ULL, 0x7C12C43527D1408EULL, 0xFE21A5711B0C5F32ULL, 0xFDFC60EC241FE252ULL, 
            0xA3B438E119528BC3ULL, 0xB077255ABE8D1583ULL, 0x3BF007F7565186B7ULL, 0x8F28F49B2BD68CFDULL, 
            0x791EED298841FFC8ULL, 0x8E6AB97716A4AC3CULL, 0xECAAE421FD503B64ULL, 0x717419736CFF4F75ULL
        },
        {
            0x8F76AB29BCBC89CEULL, 0xDC9D0FF9F9E9BAD7ULL, 0x2FB3B5BE9F6C895CULL, 0x0C7D9F9D52CC8C54ULL, 
            0xE1C874D1B7E4E62AULL, 0xCAE3560BA4832A2FULL, 0x3CA9B15BE7BC6B33ULL, 0x9A6AD546D1BF7C2FULL, 
            0x7AB48375ACED87DAULL, 0x48E8D07DCA78DA01ULL, 0x4E4D401FB21EBA0DULL, 0x7F7B6E4A8D1F736BULL, 
            0xD84B50DE3F0967A5ULL, 0x0FB26D94BFA1640CULL, 0x105D30F5CE0FC075ULL, 0x20AEB6EEF6242B80ULL, 
            0x26D929C2C16F7B8AULL, 0xC828BA0CCEFCA912ULL, 0xA3EB9B469F3B626BULL, 0xE1983BA81105D1B1ULL, 
            0x2E5A49F362BEB9C3ULL, 0xC2D8D6DDF4A3E698ULL, 0xB43BFC320C7EDCF5ULL, 0x40326A8598F831A4ULL, 
            0x11C7DB46FB68CA3FULL, 0x3CBE3E805C638D46ULL, 0x23CE8D9CB0AA3BD6ULL, 0xCFE100760BDE4833ULL, 
            0xA39FBA8C15ED3519ULL, 0xB6339811EDD51764ULL, 0x9A692803C3A5081DULL, 0xF3B6D61A442F3EDAULL
        },
        {
            0x5CB9F96DB275A918ULL, 0x00228C3B09A05185ULL, 0x945228870B0DF4DFULL, 0x530110742FCA058FULL, 
            0xA4CC3FCD2FDF8234ULL, 0x6D65D6CF7E8CF4EBULL, 0x54B7292C7977EA09ULL, 0x88DA8179327752F8ULL, 
            0x127B62C75B294FE2ULL, 0x344C39E6DA134686ULL, 0xB97EF213A9FC723AULL, 0x9B99BEB10EBA376AULL, 
            0xD381A472BFFE33FAULL, 0x97972C12CD5BF2AFULL, 0xF64FD5BEA509FA5FULL, 0xFB603344CACECD6FULL, 
            0x378A124CFF6C4C0FULL, 0x14AA4EC84B37D403ULL, 0x4ADA35D1C65F6DC7ULL, 0x66B15CAF34A50E6CULL, 
            0x04ED2DF696AC0ABCULL, 0x80913683DBA0B5E8ULL, 0x73CA5AC9197A3157ULL, 0xC8FAE0FB7A2CE1F5ULL, 
            0xAA12AC0B56A11D00ULL, 0xD126D5CA3A86253BULL, 0x9DA033D6EA9E0B3CULL, 0xACC0964649429A33ULL, 
            0x4DA4F4BCFDB850DBULL, 0x282612B34DD47395ULL, 0x6DC5ACA016B8AD63ULL, 0xF2917EF951ADDE71ULL
        },
        {
            0xFA544936B0CF6748ULL, 0xB997AFFBC3A9A9EBULL, 0x21402596AF2736FFULL, 0x5668DFE38B382A3AULL, 
            0x04877F5C9580AA3CULL, 0xEF0D801EC8586BCCULL, 0x0688D22CDE4B969BULL, 0xF3E6BDDCEDD60DBCULL, 
            0xD1652461182F7B7EULL, 0x12F28CF22398870BULL, 0xC36638FBC6122B7DULL, 0x0E20A56B44473253ULL, 
            0x6E402A919A8870E9ULL, 0x92749601F2E5599DULL, 0xAB9CF6423D271DBDULL, 0x10B1F148549DAB27ULL, 
            0xCF5CE181F7F7B36FULL, 0x72402E27910CC21AULL, 0x3C9D147BA80B2258ULL, 0xAD2854C85F15CD2EULL, 
            0xE923E1B0167F4397ULL, 0xCB8D2F7BEC0D4737ULL, 0xBEFB339AC12A0002ULL, 0x92424FFC871ECAAEULL, 
            0x2D79BB6B620B4DFBULL, 0x2E5DE5DD2F65BCD9ULL, 0xB08934A6304E05C5ULL, 0x3F95853C86512EE7ULL, 
            0xFEDA91C89AD16C0CULL, 0x472CD445183BA2EBULL, 0xC981E979B2291994ULL, 0xB37245B89CEDFF36ULL
        },
        {
            0xE44EB3380D5BE383ULL, 0x7B1478CECF711E44ULL, 0xA99831BCB59E4E5FULL, 0x389BD2E22076BF08ULL, 
            0x1F3F273F10506F51ULL, 0xF997D50838B06FB4ULL, 0x9D6A489CA81ED774ULL, 0x610BE26727341E30ULL, 
            0x6F1FE707115065EDULL, 0x24C36526D89B613CULL, 0x4C44AB04256DFE67ULL, 0x40D68D56CE6FD1A6ULL, 
            0x496F92481178EC2EULL, 0x2D6BFF7BAAA7B961ULL, 0xE16A218D30A6ECFDULL, 0xE03E67DC47734326ULL, 
            0xEF06F2B6B36274EDULL, 0x445D0250DADD18F1ULL, 0xA2DE02A18055DC4AULL, 0xF7445BE83BAC8D80ULL, 
            0x6D6EF5BD4D09D192ULL, 0xAEAC519D593E31ADULL, 0x867C1E836DE04C5EULL, 0x3D8033DD9AB69452ULL, 
            0xB8B55F9C67D228F0ULL, 0x8413AFE811CE917CULL, 0xDD65A42B5EA06BEBULL, 0xFB49A1F74D93A2EEULL, 
            0x5F57D2C77A40B146ULL, 0x6EEA8E7F1B4B8D8FULL, 0x58AFFE2DD9F78CDCULL, 0x33BD3105D5DC66ACULL
        },
        {
            0x636675EBC70308B2ULL, 0x63BF8FA404C2C2D6ULL, 0xCE902D4086911BE7ULL, 0x8E40A43A562B5389ULL, 
            0xBB4F9F023BC55B2BULL, 0x2BFE59DAC4AF9E92ULL, 0xBBFB0007E1B7A2D2ULL, 0x053B4D10B2755FD8ULL, 
            0x13995F6DA7E956C6ULL, 0xE3AB92D24A2785D5ULL, 0xF7FB7710A531922EULL, 0xA9BA012DE9FB1386ULL, 
            0x07F2BB0084E7E79AULL, 0xC5FA2499C8F94E50ULL, 0x5DA1ABD0C24AFC9CULL, 0xCF8812E2DB0E492DULL, 
            0x80063AEB1B9252AAULL, 0xC418AADC47FFB2DDULL, 0x1C3BF0996BEAEB14ULL, 0xD722712F524865A2ULL, 
            0xEE790E4A6F3457CBULL, 0x06DA1121BF283482ULL, 0x6FC10B76791204AFULL, 0x1FFCF0493F41E8E6ULL, 
            0x4A24BEC6D1BB87E5ULL, 0xDFCFE9D803A2365EULL, 0xDCCF876D3205EB32ULL, 0x261BBB0C8C4EEDEFULL, 
            0x1171F52AA103D67EULL, 0xD8560A308253F72EULL, 0x3FDE084B528AE439ULL, 0xFE15244CAD387D59ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseEConstants = {
    0xD4477287141CEFCDULL,
    0x00D582136C4B97CAULL,
    0xE65EC460D26D044EULL,
    0xD4477287141CEFCDULL,
    0x00D582136C4B97CAULL,
    0xE65EC460D26D044EULL,
    0x0CAFE01A65E45BB3ULL,
    0xE688CE663AF97AB5ULL,
    0x63,
    0x8F,
    0x09,
    0xAB,
    0x45,
    0xA1,
    0xBF,
    0x7B
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseFSalts = {
    {
        {
            0x1A0301C4AA1A4871ULL, 0x2F9B27A8CDF0D480ULL, 0x3787FEA8DC6FD042ULL, 0x5FEA202ED6AE8E29ULL, 
            0xD42B92B14981E44EULL, 0x400E9EF4B73F12E8ULL, 0x42A1181FF231963CULL, 0x552717DDBE9B372CULL, 
            0x49FD1048B2379E7FULL, 0xCF878486C230F357ULL, 0xC1E8DB0C530A7C89ULL, 0x3555E6F97E7D6DA8ULL, 
            0x499B9ADE9B7C45ACULL, 0x60515C54C6B46FF9ULL, 0x7D838CECA182AC46ULL, 0x3E6F4F75339017C6ULL, 
            0x40A691379E38E383ULL, 0x2F91756B9AB9D711ULL, 0x35ED589BA42A7340ULL, 0x3B01A759757A6404ULL, 
            0x4D209CEE4816832CULL, 0x2D5B2C35419B55FAULL, 0xAA136BFCDF6B46EDULL, 0x07A38B87BA0B89C6ULL, 
            0xA81033F0FB3CFCECULL, 0xF0A245E88E817A07ULL, 0xFBF1ED4998347A79ULL, 0x40373CF0BECDE6C6ULL, 
            0xD670E4EC215DF76BULL, 0xF219CBC032AB86BBULL, 0x16537442B9A95FDAULL, 0xE126F96FF2CF03A8ULL
        },
        {
            0x73F8065B1A5AD051ULL, 0x232D382FF4E349E7ULL, 0xED1B64451A4064C2ULL, 0xC420307AF20BE278ULL, 
            0x7468738A7EBFE5F1ULL, 0x09A08E92874AF1AAULL, 0x496727CF71B6C9EBULL, 0x6F9849EEC7753CE2ULL, 
            0xBED87A7CF9988E04ULL, 0x8D8764A10F07E280ULL, 0x45F1D98DEEA62D51ULL, 0x944995149C546FE6ULL, 
            0xE78FC908BDE0DB23ULL, 0xDCC8AD576D09E6F8ULL, 0x384254C3E9FA95E0ULL, 0x1A44904ECA23CCD2ULL, 
            0x15DD2872CFE2E546ULL, 0x99765646D3DACA09ULL, 0xE1F17C27A8AFD676ULL, 0x3C54E77E578853A2ULL, 
            0xE72AFED624712C95ULL, 0xF0EA1A09DBE1AD0AULL, 0xD483A8A707DAC423ULL, 0xC4B94F2A0B97AFA6ULL, 
            0x27F1A4FCCD87411FULL, 0x0F8DF61D85007979ULL, 0x0E97B8CA56D20EEAULL, 0x8C30CB1DC003AF87ULL, 
            0x96FD9DD1F67A4C23ULL, 0x2A26C1F97A66502BULL, 0x31788B49C69EA485ULL, 0x2296A125B0397236ULL
        },
        {
            0x923121D883B52685ULL, 0xAAEE95DD8C0D66A4ULL, 0x426E28640B6C3567ULL, 0xBBBEC9625AB40D6CULL, 
            0x5EA50DF1ABDB0DFAULL, 0xD76315E28CAFCA0FULL, 0xB69567DB7261339AULL, 0xF185237E01A71F9BULL, 
            0x7D071E4945763025ULL, 0x435CD54BF1AA55C2ULL, 0x45B7B5DF20E71097ULL, 0x49A82248F4580600ULL, 
            0xE0DF3D6DF4D9B8BDULL, 0x4FCDC96791F8EEA5ULL, 0xD5706FF573B6F383ULL, 0x3E31FE1F3E1B0A5EULL, 
            0x75BE224AC652073EULL, 0x00CE1A0007587349ULL, 0xBDD82E4BC97D20B8ULL, 0xBDA3E941797C5824ULL, 
            0x6D5E1B10C409C361ULL, 0x208177662BAEBF28ULL, 0x5EA2384A429279FDULL, 0x40337F69A5F86C88ULL, 
            0x0417E651FF6FEDBAULL, 0x728C65FBB3ADA585ULL, 0xD7AA949FBC9C8CA4ULL, 0xDB20B5A283F93489ULL, 
            0xCECEDA959DEB18BBULL, 0x9D8D72F862DEAFF9ULL, 0xF564AB63B3978BCDULL, 0xBB3EE2C5BD418BBDULL
        },
        {
            0xA963967D1C53E9E1ULL, 0x440C1019C3949F98ULL, 0x5309AA06454B010AULL, 0xB637F6E6525C654CULL, 
            0xB581FF3A1D47C9A1ULL, 0x956EFD7D945292AFULL, 0xED9F6D80E46B0AF7ULL, 0x527B6171E260466BULL, 
            0xAD80E4262361832DULL, 0x66D09E133C80B105ULL, 0xFB893841F22A0BA3ULL, 0xFF249733503E81E7ULL, 
            0xCC71C55D56F37FC1ULL, 0x1BB186B80889DAEBULL, 0x9271D77FB2AC5CE7ULL, 0x12C66E5F9151E0B6ULL, 
            0x080AD59489022303ULL, 0x3249B4BDD9A220F5ULL, 0xC8A0D7AA91222A53ULL, 0x74010CF5D8A9547BULL, 
            0xF8D6F060361AAEE3ULL, 0x4038BB04B86CE93EULL, 0xC4A6FA8B22AA6E6DULL, 0x1ED2967DDF535988ULL, 
            0x77F5C1E5733FC7D5ULL, 0xE8E1CA73245CBEB3ULL, 0x34B380EBBD2AA46BULL, 0xDA1282D20B3346FBULL, 
            0x3AD4AE30A1B3A204ULL, 0xD2FED94986BBF533ULL, 0x32CE2524E1E94E0AULL, 0x323C5047F32B259EULL
        },
        {
            0x3F6149BCA5941918ULL, 0xAA17E22350C8DD2BULL, 0x8632EFD67F8F43B3ULL, 0xABC7D7A3CB592628ULL, 
            0x044C8039412FE39DULL, 0x3DFBDD034BCAA0A7ULL, 0xFFCF84218A49A342ULL, 0x967C50A337FCC0E7ULL, 
            0x3704CDD89D26066EULL, 0x02F63CBCE76D234CULL, 0xCEB116D4F09F2390ULL, 0x665B0427742B0813ULL, 
            0x733A794F121D46E5ULL, 0x41561C28864E17A8ULL, 0x698C0A2985A80C2BULL, 0xB57FC385B5FFD4D9ULL, 
            0x6435FEE207886E8CULL, 0x40044DAAA27F86A3ULL, 0xD626CBCDD5CE11E6ULL, 0x1F304C31FAF99892ULL, 
            0x3B4E31D1563C4197ULL, 0xAFAA72A84F92C4A0ULL, 0xF3FD3AD88AC6146AULL, 0xBE824B302D541F32ULL, 
            0x19C344A2F8DD8365ULL, 0xAC6E06E84DE6159AULL, 0x14EA15D48004A116ULL, 0x77E2C2B1EE7F4F6BULL, 
            0xE96B114CCAF52421ULL, 0x11E01FB09EF173D8ULL, 0x9941F73C1A6B98C5ULL, 0x552CF12759741F9AULL
        },
        {
            0xD0EEDCC75EE9292DULL, 0xA1A76F6C6A163E05ULL, 0x3507289BCDD67C36ULL, 0x37B2E4C48E7DE7F5ULL, 
            0xE3A37148E567BFFFULL, 0x8D631BD004F48D3CULL, 0x8A97DF0B6D82CF7BULL, 0xF77C43554303742FULL, 
            0x3BCCD22E8F9DFDEAULL, 0xB2C935FFFFAB7CF1ULL, 0x771A01825D5E09F7ULL, 0x867B2CF52275CD7EULL, 
            0xA0CAF13129253442ULL, 0x4E649C3EE2335224ULL, 0xCCA1EE8F261E5611ULL, 0x03C8E78C90C15287ULL, 
            0xCEB6B6228B3AC41AULL, 0x2E0C08A133B9A992ULL, 0x23325370E53AEF62ULL, 0x19A396CD52707043ULL, 
            0x0D0C6E77005F95BAULL, 0x572BA5064F053C91ULL, 0x814374B335798783ULL, 0x4310E140A2E5F15DULL, 
            0x3A3DB978E5F648C9ULL, 0xDBBB3AFBDB75E4BAULL, 0x24110E57515FEB96ULL, 0x539B71BC5D2739B8ULL, 
            0xB1186B8C1AAEE7C0ULL, 0x9EF28660FD69CBA8ULL, 0x3BF46D83F4BC709BULL, 0xEA715EAE07D5EA0BULL
        }
    },
    {
        {
            0xFDD921352278A45AULL, 0x8118AB05180045EBULL, 0x904158520D96FF79ULL, 0xB3C6E378F2B1B9ADULL, 
            0xE3F56179FD3EC49EULL, 0xB437D4278B28DFBFULL, 0xA029E926C3232CC9ULL, 0x4BBC67FECDEA1C3CULL, 
            0xBE40F756BD90D820ULL, 0xCCC1C2D1A2245479ULL, 0x3996AA239C538B51ULL, 0xE95CC985A8C88A0EULL, 
            0x7968DC9B69A6A539ULL, 0x2FBBA4B172436E0CULL, 0x1BB38E30511F1A13ULL, 0x624AB52428EE3063ULL, 
            0xFE5E5CE9B8F3663CULL, 0x8A365BE6F70ADCA8ULL, 0xF5201CA83CCAAFC2ULL, 0x61C450EF556F274BULL, 
            0xE92B6602FB335DFBULL, 0x85AC6A14511F3C1FULL, 0x2C5702866ED67A49ULL, 0xC45E4700AFDDE584ULL, 
            0xDB13EACDEF5258D6ULL, 0x9F5725675573DA22ULL, 0xCAED90DBE57F64C9ULL, 0xA03ECEBEC7F7A433ULL, 
            0xAF65072A74FB9F8FULL, 0x35121AA822C35D38ULL, 0xB3A2653EB5F6A722ULL, 0x6AABCBA60EAEE451ULL
        },
        {
            0x5A835CB52E90043CULL, 0x7410B5C036B97BA0ULL, 0xC6D97C8EC7DF9CD9ULL, 0xC1D53845876CD705ULL, 
            0x3E0FC7F3677544BCULL, 0x5F7DD47DB2A14F11ULL, 0x83B3D191E4CF893BULL, 0x8D63E1FC85958E80ULL, 
            0xA982AC59E02F9FB8ULL, 0xA1603B862193755AULL, 0xC046B2CBEACC7834ULL, 0x643CF81CD8360FC0ULL, 
            0xFCADF6561D4AA7ACULL, 0xFF2A12160191CECBULL, 0x5B5A4A56BE08CF7CULL, 0x8DFAD9D19C5DCD84ULL, 
            0xE57A96AF4ED15757ULL, 0xC4A560657835BBCFULL, 0xA43BCAA745F5BE52ULL, 0x5FD18D1CB336017FULL, 
            0xFF13F18DCD40D13AULL, 0x6CE3B2B90F89C452ULL, 0x5C5F886AACDE1634ULL, 0x88860F7E25A1BDABULL, 
            0x96DBD10CFBBEFC54ULL, 0x5A04F66DAFB48E11ULL, 0xEBACAE97D62B37D6ULL, 0x8AFCA7B69AE4E14DULL, 
            0xD79E76F4A48339E0ULL, 0x02370E7CA068F081ULL, 0xC8971899837E4468ULL, 0x7252A78481E70A1AULL
        },
        {
            0xA756E3FB4ADAD013ULL, 0xA1C80B12E3841F30ULL, 0x02EEBC7994F049ECULL, 0x1751B2E7801F45F2ULL, 
            0x989CE5C871C460A8ULL, 0x5B0F0C381A27FB17ULL, 0x3D27DF7AE8841D60ULL, 0x43D3B6A9C2691916ULL, 
            0x27AAE5930ED6EFB3ULL, 0x164B10B6A7EE2E79ULL, 0x595AE025FFFC5A64ULL, 0x3B6374A7FBF0DF35ULL, 
            0x7910C1741236BC71ULL, 0xA301E8CC3BC45DB5ULL, 0xA5BF1A7E63BB7CF8ULL, 0xBB68BF8AC2FD566EULL, 
            0x3BE8313D2D7AE664ULL, 0x3610785B3600A403ULL, 0x15FDD46C860500FFULL, 0xFEA87CD4C66DF821ULL, 
            0x5701AF704FA0AB76ULL, 0x63D4E272ECAA8319ULL, 0xAC226F87F758AA94ULL, 0xB15260E6285F9194ULL, 
            0x49C64B713229FE02ULL, 0x73F4002C238E120DULL, 0x4B607DF2A689825FULL, 0xE26C32743A52AE74ULL, 
            0xEE56105C4C89493EULL, 0xE020F226CF9ACB8BULL, 0xDD1C1F80069D7936ULL, 0x08A192E3CCC7F757ULL
        },
        {
            0xB37C8D143F0CEDE4ULL, 0x54544D6E48EA2A3AULL, 0x5B352CFDECB56444ULL, 0x72DED28D3D45751DULL, 
            0xD4A9E436EE216B7FULL, 0x79656F03486D2B9DULL, 0x1E4FDBA3D7E4B319ULL, 0xA73DF52787322F28ULL, 
            0x7D970E9EB539F127ULL, 0x85C640762C9F3AA0ULL, 0x65C5F1D0CBFF1BEEULL, 0xD7CD1BE56ABBA4E1ULL, 
            0x0BFBBD9106E5FCE2ULL, 0x6EEFC88031C71226ULL, 0x56C32769B23F7FDCULL, 0xCA8C6CC4F8A20916ULL, 
            0x57823259D18E98D5ULL, 0xFDAB90FE2CED3E0CULL, 0xA0555CD44980D41BULL, 0x9AE09DF6CA95DD61ULL, 
            0xECEBE0C7EA55B7AFULL, 0x1CF51F48AB28D148ULL, 0xD3D430D5328C8196ULL, 0x17377D49BCD0BA28ULL, 
            0xDF236B541CD59062ULL, 0x3D6517078F503720ULL, 0x10EEBEF66A3D23BAULL, 0x91F8657657C71E6CULL, 
            0xD30BAEE9171548E8ULL, 0x1BF429EF267A0446ULL, 0xFB8E62B65D2E984FULL, 0x05A132EC4405BF52ULL
        },
        {
            0xFD62D41BA969EE7EULL, 0xC7D2DABCB0ADB83DULL, 0x1C12E05D7D0F6DBAULL, 0xF9981F406681286DULL, 
            0x90E70C648313F806ULL, 0x1CCEF12F0354F64BULL, 0xFCA3A3B6C97DEFA8ULL, 0xAF3923750AFD46F7ULL, 
            0x7AAF6ADB02928EFBULL, 0xDBDFE9AD77FAD1DCULL, 0xCDA8BDDD03D1A98EULL, 0x7EFA573DAD288F42ULL, 
            0x54FCF5A43B770CE7ULL, 0xBDEA0FFFA0FBE7D2ULL, 0xD5B2064C3226C567ULL, 0x68849ABC74B38A2EULL, 
            0xEC2A9382937D320FULL, 0x3A21472EED4C5BF1ULL, 0xCD939B28AABCBEDAULL, 0xB268F02DF70522A0ULL, 
            0x21F4C373E584084EULL, 0x51794E7415D8CEFEULL, 0xF59EFA6F2DE58DBAULL, 0x29CB9AD0F1EC332DULL, 
            0xA5C710C10D0FE82AULL, 0xE1FCA7732BBB5227ULL, 0x7DB0A417B6158BD5ULL, 0x7AE3B2C10B102292ULL, 
            0xEACD1732858CC1A9ULL, 0xF133C678253C8A4CULL, 0x3CAF58F935ABFA41ULL, 0xABE28C7B09DF01D6ULL
        },
        {
            0x3F4DD9933FC705EEULL, 0xFC0B448CA369B460ULL, 0x0F56ACB389EFCA4BULL, 0xEA835079E23DD0E1ULL, 
            0xCA9485EA3D5544A9ULL, 0x40CA5D9CBA7CD8D5ULL, 0xD0A77A04AAE725BAULL, 0x033A4E97D351EA31ULL, 
            0x4B7DF52200BF3397ULL, 0xF9CD34B4F8E59054ULL, 0x6D44272EC4F0C0CCULL, 0xB5D74CA92F57589FULL, 
            0x79FA291B700F5330ULL, 0xD3DC398926DE641DULL, 0xF2739261E3A0E66FULL, 0x51105E224A556E1FULL, 
            0xE18AE7740046508BULL, 0x32CBBF1E9053924DULL, 0x8E58B94AA9D6332BULL, 0xFA8AB06938E96C2FULL, 
            0xC605A82D7BB4A36CULL, 0xAA612A52A39F2FE9ULL, 0x1E5AE54D937E0629ULL, 0xB6D5C4A51B1080FCULL, 
            0x640D0F39E917FCBDULL, 0x3ED61A72D2409D22ULL, 0xD449B1CBC4BE4FA7ULL, 0xD86AF8E5E1FA4B74ULL, 
            0xC6F73A47911C485DULL, 0x99F3EBF0A78FD697ULL, 0x48711F802C58AF75ULL, 0x3A3E96D794272367ULL
        }
    },
    {
        {
            0xBEBF783E38AB0149ULL, 0x71DD633E3B1E3621ULL, 0x700473856B54D990ULL, 0xF09FFDFE9C221E11ULL, 
            0x61F3D7A7EB329D92ULL, 0x5D5870535FBA769FULL, 0x4444E8072808561EULL, 0x655E252D8DFFA106ULL, 
            0xF35A0861DBA1ECF7ULL, 0x59C340C9E856B9C6ULL, 0x93063BD6423AABB1ULL, 0xCF22C5E606AF8D6CULL, 
            0xB61F23DFB0D4CBD8ULL, 0x39ED372660FEE9DFULL, 0x350D14F62E9BBB7CULL, 0xC4638BA23760AEF2ULL, 
            0xD8F5363160953AACULL, 0x5744123CD8051640ULL, 0x7E690983B9905883ULL, 0x2041654964D29039ULL, 
            0x001410ABDD12E75DULL, 0xE8885070F4E7BB94ULL, 0x1FB7A2DABE577C12ULL, 0x8CA83B01B154236DULL, 
            0x0911B85573BDFAA7ULL, 0xB5DC92D8D6101BC4ULL, 0x5372F3CEFBD492A3ULL, 0x00CC16A7237B76DAULL, 
            0x9FFC92CC7CAAD00FULL, 0x0A7E7738347AB01CULL, 0x6C3169397532F315ULL, 0xFF6F22F407EBE562ULL
        },
        {
            0x5019B4104E283423ULL, 0x9A9F2D69A8B5BEFCULL, 0xCB2A2C0A653E63A9ULL, 0x783974C9C7730AEBULL, 
            0x2906B7AE54DF2500ULL, 0x114CB4A417232EF0ULL, 0x49FEA2B9A500C085ULL, 0xF6B2B8EE1E9EC81CULL, 
            0x29D3E3501CD713B3ULL, 0xB9D463FB211F0C6DULL, 0xCE2E2FE8F8F1C814ULL, 0xD432131E84A95217ULL, 
            0x1E105E45FB349F29ULL, 0xF915FC542B74E2D4ULL, 0x9775503ECDD4AE7EULL, 0xC55D0F0C464AD514ULL, 
            0x36E3F441AD1B5207ULL, 0x54189A5A307C71DBULL, 0x3A5EE50DC43DBF48ULL, 0x6012DF4B502EF3FAULL, 
            0xD38943F5C9FBA55AULL, 0x3D27C5BF60073777ULL, 0xDED6418D8CA2F566ULL, 0x6A70140E98F20D85ULL, 
            0xCEC0CECD156E3C36ULL, 0xF3CD713605517561ULL, 0x644DD3DDEA019BF9ULL, 0x29FB0BBDC2B33C03ULL, 
            0x06B15317FE7EB5CBULL, 0x4BA9C09E798C23F2ULL, 0x0D27B47D7D8612FCULL, 0x78BAAF0C050355C1ULL
        },
        {
            0xB594BF03A43F2B0EULL, 0x3299C02FD19F7F2CULL, 0x9975AB5996C9732AULL, 0x947669185CB11E30ULL, 
            0xC30001F8BD38E6ADULL, 0x736CF37BBB726DA6ULL, 0x5360B00CF255E233ULL, 0xDC06A479C9BE5251ULL, 
            0x682BC8DE054709C7ULL, 0x5EE3F8BA87C0E485ULL, 0x01F349F3AB6093E5ULL, 0x1670B19A92DDA9FBULL, 
            0x6EEC81DC009A1F05ULL, 0xCFC3022285278F66ULL, 0x66F9010D5ADCBABAULL, 0x0C1493DCBFBEF367ULL, 
            0x0A3BFC2944FB445CULL, 0xDFE5C96F446C9314ULL, 0x3531F3D3DA3E3D2FULL, 0x032BF4578064218BULL, 
            0xC18FC3F2149A8FB2ULL, 0xEC6902E0FAF4E8CDULL, 0xD6C22AFC4734F16DULL, 0x29D474DE1369B2FCULL, 
            0x7EBAF6BAE3677B35ULL, 0x022737B959F384A9ULL, 0x1506845A83BCEB73ULL, 0x97605D20A44DD8E3ULL, 
            0xB69F8DB73B340C17ULL, 0x4FB0CEADE82F91CFULL, 0xB4616BF96E93BA8CULL, 0x98CB01E890034609ULL
        },
        {
            0xAC4E6F14DF8F3528ULL, 0x9D1CCC38C8573159ULL, 0x287D07B04FEBBA84ULL, 0x8CDD6C84EFBFA3FCULL, 
            0xC6CAE075F35B785AULL, 0x4C455DA54BDD9D00ULL, 0x074F9154B97CEA62ULL, 0xC71C27C6BD26637CULL, 
            0x74286F25D4B48344ULL, 0xEA4F744336CF9E32ULL, 0x7EDEFEB50857D97AULL, 0xB0C8D31BEB3706A7ULL, 
            0x960DC8CB0928D5A1ULL, 0xF2C62916D870D98CULL, 0xC18E354A33D8577CULL, 0x8394D5B76F6680A4ULL, 
            0xCD20527D65B90FEFULL, 0x1FBEA4DBAA8D6DF3ULL, 0xAEC1C1455B95B20DULL, 0x6E6DCCE172DFD76FULL, 
            0x25180EDE3285942DULL, 0x22ED455F8583E2E7ULL, 0x85F81C9BFC87C772ULL, 0xC1A7B05A97D1010AULL, 
            0x7C87A1D245AE164DULL, 0xC2ED838BDF885CD0ULL, 0x8130896D1D218128ULL, 0xCB4C3269D473CE7DULL, 
            0x292212C490E8146EULL, 0x3E8A33FF72E037D3ULL, 0x6951D484C6B268D3ULL, 0x028DA833161CC4CDULL
        },
        {
            0x72FDBEDE4049DA32ULL, 0xD298E3CD6BBBEF7CULL, 0x7A447014C0EB2D8DULL, 0xDE5C91A9457730C6ULL, 
            0xD0C28244CB580CBCULL, 0x735D5AD761F5DF8BULL, 0xC4E490044B75483DULL, 0x0422E6226ADCA203ULL, 
            0x036F3C50F8F5CAABULL, 0x651EE57A0C9CFAB7ULL, 0xFD4EC58B4AD1F47CULL, 0x096D78AFF5E71074ULL, 
            0x1F914F646E1735B0ULL, 0xBC99F29298663D23ULL, 0x8CD6357927152A74ULL, 0xD2B3054872B50A57ULL, 
            0x2C74D9D64010EA80ULL, 0xA1B0146BB618EE2DULL, 0x9BD428CCBE6BC5E0ULL, 0x09A32F5FAE1A46CDULL, 
            0x6C9460FFBD955F69ULL, 0xACA21F1C7D171BFFULL, 0xCFE4D778F8412909ULL, 0x84FCD9FDBD9C7C70ULL, 
            0xDB43E12C476E5C7BULL, 0x60616702E4EFE6A3ULL, 0xCF4C863634822B89ULL, 0x770D6122FC317B4AULL, 
            0xDFD52086CF901073ULL, 0x40E547C0DAE3BF16ULL, 0xD45E7FC56DC86FADULL, 0x7EC83554523C137BULL
        },
        {
            0xF62C403EF0680FB2ULL, 0x5064514C92E3EB59ULL, 0x8C544A13D393194AULL, 0xD00ABD196A88F6E5ULL, 
            0x9B6E4E28EA20CD3BULL, 0x10D2095BEDF0D732ULL, 0xE297535504CD3D00ULL, 0x79CDB053E3FB9E6CULL, 
            0x63C9C2A120EB2E23ULL, 0xC8F0858477CF2A81ULL, 0x447EA142D8684CAAULL, 0xF7F35B3472EC5949ULL, 
            0xB011B403FC629C62ULL, 0x2CEE7FD5771342F0ULL, 0x42D11F01308173E5ULL, 0x57CEBFCCE8DCD4CFULL, 
            0xFE518F19ED15C9B9ULL, 0x5ECACBBC265A1F6FULL, 0x7EBE6B6D964F409EULL, 0xE4BAFE7CD23E9A32ULL, 
            0xB3FB28B828E2652DULL, 0x4B88556B989409DAULL, 0x08A17B78381D492AULL, 0xFB5B19582EA88E9AULL, 
            0x687EE6FB56BE2A13ULL, 0x3804FA9EB5BABFCEULL, 0x0654AF937527AC95ULL, 0x324AC2B31DC458FEULL, 
            0x844C708C4DC62E2FULL, 0x7FDBE1658B07ABFBULL, 0xE311899A3AE0CCDBULL, 0xB46C6FE46E2BC4C0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseFConstants = {
    0x973BBDCFD1B6CAE1ULL,
    0x16549D34DE9E8700ULL,
    0x19834DAE1657EBECULL,
    0x973BBDCFD1B6CAE1ULL,
    0x16549D34DE9E8700ULL,
    0x19834DAE1657EBECULL,
    0x1773D05EF0DFF7E5ULL,
    0xF984A612019EA4FCULL,
    0x44,
    0x0B,
    0x28,
    0xB0,
    0x78,
    0xB5,
    0x3F,
    0x95
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseGSalts = {
    {
        {
            0x1DB0CA801495AC99ULL, 0xA72A4A6489B03036ULL, 0xD7A53DE9B5EFA136ULL, 0x39EBC88ECAF18D8CULL, 
            0x1EA3CD18D030A23BULL, 0x7D39FCC40C9A5CD6ULL, 0x346A582D0F12F623ULL, 0xADAE1B6B62D19DDEULL, 
            0x89F2F93CE68D28FFULL, 0xC63D237FD10D0A3CULL, 0x396E1C9486022DA7ULL, 0x2DC865DF057320BDULL, 
            0x690D7F57C6918102ULL, 0x553DD919602909A2ULL, 0x1C47827909C8DE40ULL, 0x272D2A2634EC5971ULL, 
            0xE89FB441B5FC45F5ULL, 0xBF9F889E968A91E7ULL, 0xA3E71B5CF5F06E25ULL, 0xC487E0C0ABA0CAD7ULL, 
            0x7E8475A5D44E59D4ULL, 0x2000C54817CACF20ULL, 0x42AAB87407C6545AULL, 0x530F80A4CB36BE14ULL, 
            0x6970E70C8F65523EULL, 0xDF53BE3023CF0590ULL, 0x937110E5C2F23946ULL, 0xB517F3845DF21672ULL, 
            0x2CD73F4EAD860744ULL, 0x181428D5A7A433FEULL, 0x005C08A23072188AULL, 0xA7659619C85D2442ULL
        },
        {
            0x23D978530893F3D3ULL, 0x9D7DCAFEE09B2B4FULL, 0x41F72DB82CAE72FFULL, 0xBB7343E59E5B81F0ULL, 
            0x0586F7195407DAEEULL, 0xB937287A62ACFF59ULL, 0x26DE2611CE82F2CEULL, 0x9037336E40803BC8ULL, 
            0xCA9F4383D3A5EEE3ULL, 0x341AF439B8C683D2ULL, 0x3E5FD9D1E728930EULL, 0x4D1CD7F40B554D27ULL, 
            0x285F38A4EE4323B2ULL, 0x73A3886FD4A79F57ULL, 0x3E16C2E9E7DAB85DULL, 0x58012CEEA02F888CULL, 
            0xAD1A80BAF826AD03ULL, 0xE3904A47D79AE7E3ULL, 0xDA897649D4DD4D89ULL, 0x275F76FB0F9E61CAULL, 
            0xE26F19C49B114212ULL, 0x81A5A2BC3745783CULL, 0x0D468C55170AE043ULL, 0x754695AC563BEF36ULL, 
            0x7949139F3F382D55ULL, 0x3F0C01CD7BEACB91ULL, 0x4307FFA90CBE5D71ULL, 0x611C694883B76CADULL, 
            0x4265EEFA646B3F50ULL, 0x4A7BC758FB2BC647ULL, 0xA94D2799E0E90E1EULL, 0xA9B751E0E613A628ULL
        },
        {
            0x151CECB8CFDB0C24ULL, 0xF332083EB5233B46ULL, 0xE9450ACB27280E19ULL, 0x4D0DAAD3598FD79FULL, 
            0x1D246E98F72DE075ULL, 0xBDE06ACBA544DE29ULL, 0x8A343B9346B1F08BULL, 0x2E5E8DB4539AC923ULL, 
            0xEFBDE1F4E9E2FE8EULL, 0xE2B7A49388295697ULL, 0x50E1378CEED1089EULL, 0x6E5BA471BB8B8DB0ULL, 
            0xC7159BE51B180CF1ULL, 0x24C7131A7B90DD22ULL, 0x98F40E6FD3CBBFFDULL, 0x4D4B3D6EDE8D6FE7ULL, 
            0x15BC8C8C0D60ED33ULL, 0x4063C3CC9A84230CULL, 0x39D5D9508F5FEA8CULL, 0xD38EA8696D02782CULL, 
            0x02073542AABAC4EFULL, 0x6473A9F820B4187AULL, 0xB0EFFC7109127831ULL, 0x13B8C26527845472ULL, 
            0xEF4F81A7F370AFCCULL, 0x357402334D84C7BCULL, 0x8A164DFB739A9DC7ULL, 0x1B9857FA8625664FULL, 
            0x4E7BFC68E6557EE0ULL, 0xF69FA1281E53DABAULL, 0x88459C9B14435C83ULL, 0x52E55F9D197EFCC6ULL
        },
        {
            0x93EBE7754C4BCF87ULL, 0x84066A8DCD75AC73ULL, 0xA7CD502800D10F1DULL, 0xCE7298035E822719ULL, 
            0x599719B5A80A8878ULL, 0x15655F8188A30303ULL, 0x9C8E6D943E2931E1ULL, 0xE80E8FE142BA183DULL, 
            0x967449EBE12AFA12ULL, 0x757B7F1DCA6FE712ULL, 0xBCA8E14CEA9998FDULL, 0x669D3D449CAD95A7ULL, 
            0x6F53B414FA8E3C15ULL, 0x0767D4BC6B723C51ULL, 0xC00F1174414FD69CULL, 0x8DDF691DEEF7D518ULL, 
            0xA49E2656B60B0D52ULL, 0xEF7E4AAB1850F678ULL, 0xE8D2F3D368FB2C43ULL, 0x0CA428B7EF67628DULL, 
            0x724A48CFFB1507F9ULL, 0xB392BD2716DE77EDULL, 0x3A09E3B6E81C80ABULL, 0x6B6CA171933EE0E9ULL, 
            0x23438CF521F0228EULL, 0x09D19FEB8CF6C124ULL, 0x942F532815510BEAULL, 0xFD60A946A25C90EEULL, 
            0x5B282078E7C4A7E4ULL, 0xAE9AECA211E3C02EULL, 0xA3E692D83390BA93ULL, 0x62ACBEB38F188669ULL
        },
        {
            0x0BA9982FA3D7993CULL, 0x6C42B542912B64E8ULL, 0x3BF1598E053878A4ULL, 0x33EDC6C4E9710A23ULL, 
            0xB1BCFE04CA91AD21ULL, 0x0AD6692E85D6D934ULL, 0x5773803CDE7F2FB5ULL, 0xE8EB42B21B5F51EBULL, 
            0x05B56F93653E3A9BULL, 0x96379F5C3629C15DULL, 0xEB40A656D9CBACAEULL, 0xC8DF628F123A818AULL, 
            0xA590386EF5B99D53ULL, 0xE3D23D9BBBAB1246ULL, 0x3E14D11172D4D8D5ULL, 0x5DAF97466A5810EFULL, 
            0xD0328BD167D0EB8EULL, 0x8BB7A46BD02869EEULL, 0x652391B6BC196DE2ULL, 0x0EF4189081BE3957ULL, 
            0x6E7B426980C51087ULL, 0xA8759B63E89DBFD3ULL, 0x7774A82160027BEFULL, 0x3C73D3BC9B97B6DBULL, 
            0x696F6F1993C43893ULL, 0x8AEE5FA3DACF606FULL, 0x4C8D44C8D47BD536ULL, 0x68FAD7EDB42BBE25ULL, 
            0xB651C99BEF9C3BE1ULL, 0x2E14D1B93E42FE7AULL, 0x9BE0AA4C62A85723ULL, 0xBA3AE38B3E969199ULL
        },
        {
            0xC710384E40F631D1ULL, 0x471F2BD33460B608ULL, 0xFA7AA9BADF970622ULL, 0x0A3800DFF23B2A0BULL, 
            0xC95551A8022EF41AULL, 0xB71A93183D469A10ULL, 0x83A8F5EB5B0A558FULL, 0x8C85A48D2937244FULL, 
            0x0249C1CFE4792195ULL, 0x329D1FB3D7FDC997ULL, 0x3649D4D3E0DFE93CULL, 0xF48E69B3D6CAE8ACULL, 
            0x5B4062A663CC522DULL, 0x0FF1AA481AA574E4ULL, 0x7855A0AD575ECEADULL, 0x67982E0C7662603CULL, 
            0x4CA1F01F73667C07ULL, 0xD9089B2D96D5BA2AULL, 0xC000644BA10DC0B8ULL, 0xA33D06B50D6EF89EULL, 
            0x008FC53DA8936BCCULL, 0xDF532F661DE5EF41ULL, 0x7EB535C8AE8D2E29ULL, 0x561AA99F896B3ABFULL, 
            0x68A93C8CC875903CULL, 0x66BC28919B7AC1DCULL, 0x758E47FD4E9302CAULL, 0x0A3340869F58CDE9ULL, 
            0x971A9ECBB9B57F4CULL, 0x645288BE6CF4E6D3ULL, 0x8754A21B8171F0B0ULL, 0xEC0D357A6FEBD022ULL
        }
    },
    {
        {
            0x515192CC3D80E13EULL, 0xF99804CE3BC07ED6ULL, 0x2A3EE4B3AA54D1B4ULL, 0x4F5DE80AF7CBB961ULL, 
            0x5086902EB533BC2AULL, 0x00DC7459A56C2AC1ULL, 0x9E9587F7DFFEEA9DULL, 0x0826F70B2F9991B9ULL, 
            0x5F704F2BAB9FA7FDULL, 0xD1D209760E2C9D3EULL, 0xAEBFD73DC1CDA35CULL, 0x06CC92858048B2AAULL, 
            0x46A69D5531D74AD4ULL, 0x24F7FEB562408493ULL, 0x77DE7D41077010DAULL, 0x6BC1208C6BB5EEBDULL, 
            0xF11EA18F5153E997ULL, 0x5D9AC834C66D513DULL, 0x8AD022974A4012F9ULL, 0x80825560CD30937CULL, 
            0x0D38A091EF31F512ULL, 0x9C9AF278BBE3A8BDULL, 0x503BB04D646A4180ULL, 0x633AB6A0BD55563EULL, 
            0x7F6D9DFBFB02F616ULL, 0xF1C895E2D1BE0C9AULL, 0x9541FF7E3BA37BD7ULL, 0xA8F1C65772032EB1ULL, 
            0x1F0DDB07A56B6734ULL, 0x315A78F47CA0AA7BULL, 0xD64E59B004D8A94AULL, 0x0109155955F5DBFBULL
        },
        {
            0xA691258C31ECC5C2ULL, 0x39A2A83EDD59F98AULL, 0x325C31D8C78A3D0AULL, 0xD8A357DE9DAB38B5ULL, 
            0xA13EF3EE808D3B5FULL, 0xD9669E8EB230E289ULL, 0x7A079F3084F0683AULL, 0x1E4EB94BB43BBFF9ULL, 
            0x2CAEB79A02854880ULL, 0x0D26AB7462197F48ULL, 0xA1454C0E59E5D56AULL, 0x3959EDB5226C7516ULL, 
            0x5B5CFF8E61B5E1EBULL, 0x575403AF466C8166ULL, 0x0BC4C2B78827AD6CULL, 0x95EB8D85B9B41BC8ULL, 
            0x5CAC258208B67EFAULL, 0xD25F8F51EEF8D973ULL, 0xF0D86A3B5EE3FC4BULL, 0x1FBC264D285A4D74ULL, 
            0xBE27C1A9780C065EULL, 0x6BC30F473F4DD4D9ULL, 0x4DF2C32087996E95ULL, 0x9D369DCC81901EF4ULL, 
            0x8C5D5CD11C2C118BULL, 0x96ADE3D5B701369CULL, 0x8D187C36337591A2ULL, 0x450C4EE6A6762933ULL, 
            0x80030337A2FC5BC7ULL, 0xE9676B925DF70E75ULL, 0x459EE241D53CB259ULL, 0xCD22146ECE6453C6ULL
        },
        {
            0xED8AB5E1CF7D14CDULL, 0x41C03F96475F9D77ULL, 0xCB635FCE268FDECAULL, 0x648BFE853C4E1EE1ULL, 
            0x6EE623EC766E3A85ULL, 0x2BB0F14EB85B8ADCULL, 0xEA1E142CFF161E32ULL, 0xB0D02A527EDB911AULL, 
            0x842DECF82CC9A44CULL, 0xC75A445EF61C314AULL, 0x85C7E03CA7EE0687ULL, 0x890462C9450DDD6AULL, 
            0x4D44FD635F800DD8ULL, 0xD0CFBDB39CB05307ULL, 0x605442BB65009902ULL, 0xC5DCDAFC9713A5E7ULL, 
            0xD9469E696EB59588ULL, 0xE1C8DA824F5E18AAULL, 0x6AA5753B8A88DE31ULL, 0x759AD65830F142CFULL, 
            0xCB2DC45D25443182ULL, 0xFFD6670BFDC4526CULL, 0x276AE574F9C81C3AULL, 0xFF7697471133625AULL, 
            0x9445F9C6A7F03049ULL, 0x3940F81161374A13ULL, 0x1913D1D9004F0A2FULL, 0xD01AB4D5D17ECF72ULL, 
            0x401FFB10785C5412ULL, 0x4CD63ACF1B5A4E23ULL, 0x79C348BA94AD0364ULL, 0xC3245C7F90006007ULL
        },
        {
            0x119644A243164374ULL, 0x4C452E2E0FD2FB9FULL, 0xAA5981EF6F9BDB87ULL, 0xA0052BA461BAB2CEULL, 
            0xC97866ACEEED2AE0ULL, 0x556DC788177FB6AAULL, 0xCD1753D04E7D7058ULL, 0x14B301CA110FBD37ULL, 
            0x5B4F82C9E826EABEULL, 0xCEE25800F0449441ULL, 0x1DC2E6469558194DULL, 0x3041E0AE31172798ULL, 
            0x70668273F3B9E5C4ULL, 0x26F9D003552DE6E4ULL, 0xC49461A0B11F933AULL, 0x7749099F25485BDDULL, 
            0x715A61D5C00042ADULL, 0xD0FF7FFF71D90B42ULL, 0x7E548B034469EC11ULL, 0x319F3BBFC9A50AD9ULL, 
            0x6893DBD314503631ULL, 0x32919DC486DB53C7ULL, 0xAC2817278D899CBBULL, 0x160C71D307E5EF55ULL, 
            0xF456997BC8BDFBA2ULL, 0xA2458D4C2B0F19E1ULL, 0x3F377C2B80B3F036ULL, 0x4DA6AAD87B72223EULL, 
            0x0AC7814E10E609C9ULL, 0x45AEB710D4987F13ULL, 0xBADB6B093AF30B76ULL, 0xEA0B1D181967B165ULL
        },
        {
            0x6094D24083635136ULL, 0x7C24B496C0ED63D2ULL, 0x97C04DE912609D15ULL, 0x2B146F91C87C06F2ULL, 
            0xA68782D69603DDCDULL, 0xB2029FB5C85C3CADULL, 0xBABC84DD24B3022FULL, 0x7F62D145591360D6ULL, 
            0xD6E2AF71D3B89632ULL, 0x0ACF6F62700E59F1ULL, 0xF3A8736B745186B0ULL, 0x9F4214D864B19EC1ULL, 
            0x356152A3AA6BD656ULL, 0x1B8EC3B763E0E34DULL, 0x16FE1028B5AD0D32ULL, 0x5F94C2E2A7B6788CULL, 
            0x984D6089E7A827AFULL, 0xBB1DC2C8FE079C8AULL, 0x20102C836BB1AD6DULL, 0xBF26B38EDF210675ULL, 
            0x608D6E066FEB86C4ULL, 0xDDC5DB3C72BBDF8BULL, 0x776FB6ED7065B629ULL, 0x772902D58ECC6E5FULL, 
            0x7894BE431078730AULL, 0x207ABAC9506EACD7ULL, 0xBF33EF8AE6B6A8D0ULL, 0x1C4075909AE869BFULL, 
            0xE6A41602C5440265ULL, 0x430E9625CFF5E845ULL, 0x6D0FD6EFA34FF2DBULL, 0xA9A10D5BAB39D0EBULL
        },
        {
            0x56D306A99E0DBB5CULL, 0x975F4A5FD7608274ULL, 0xEBCC559B56A90478ULL, 0x215A9D4189ABF4B0ULL, 
            0xE3F552C0EDA57EEDULL, 0x8D3D56DFBC11C2BAULL, 0x9EF8DEB63C124979ULL, 0x2C739969BFF7B991ULL, 
            0xB95F0AC3789FE285ULL, 0x7A7454F8E364B324ULL, 0x6744AFED7AB0C7B9ULL, 0x7AC52DA04F8DFD1CULL, 
            0x6997D3ED50A9A07CULL, 0xDC7575CA3A552D10ULL, 0x2E9D9B94E8DA9090ULL, 0x152E5542B61176EDULL, 
            0x2CB9C2A6B8F15975ULL, 0x38091AD2CBAEFEBFULL, 0x77749BC10B130E6EULL, 0x0AC6167AFA00E50FULL, 
            0x8064E8A810FAB2D6ULL, 0x17DBBE0BC58B5510ULL, 0x3B3489A7773BA0DCULL, 0x8252D20C76D06309ULL, 
            0x8522082D2B49705BULL, 0x6B3B4CD0E3F6A503ULL, 0xBD64EF975676243FULL, 0xB4DF1C7FCDD0B3FBULL, 
            0xAB0CE88FC6C85201ULL, 0x05952A20F6C6A2E4ULL, 0x81F547D91BD2ED14ULL, 0x0BA7DDE456543510ULL
        }
    },
    {
        {
            0x67A4AA5BF72834E4ULL, 0x09A7B4310C084525ULL, 0xBF92538E95843248ULL, 0xF30157E8CC398910ULL, 
            0x4E909B938FF02CA2ULL, 0x1ACB8DE1D26241DEULL, 0x4AE75B694C30FB29ULL, 0x067F4D9356178636ULL, 
            0x36EF8C5AEB69A511ULL, 0x2D31EBE763EFE682ULL, 0xD71F44C10CB45E8BULL, 0xED381653640E7890ULL, 
            0x6AA43C5422A96AB6ULL, 0x9AFED456E6C28B5FULL, 0x1BBEC10DB360C05BULL, 0xB3A4C3DCC046102FULL, 
            0xD71E6A799CE26243ULL, 0x2E6E5EDF71E941F6ULL, 0xA4CCF515EBA1D998ULL, 0x2A9C5725837EB3F1ULL, 
            0x825103503074F501ULL, 0x606F45E14EB30267ULL, 0x035C8BEF98C5FE26ULL, 0x41E342E3D53346E7ULL, 
            0x90A9FC3B2E2E5F30ULL, 0x5318241D51CE9B72ULL, 0xB24DEE67C4026B26ULL, 0xE234E919F0BEBD75ULL, 
            0xECEAAC9DB3F6B9B1ULL, 0xD5CA0DC3D158CBB0ULL, 0xF36C8F386495C194ULL, 0x650629646BD689EBULL
        },
        {
            0xE675EB3C06469E38ULL, 0x52B1BE30E140AC32ULL, 0x8AD25A09F83255FEULL, 0xD345A76CFCB4F077ULL, 
            0x708809E353BFB56EULL, 0x2A38A35373279640ULL, 0xC21F2DFD6ECD8A8FULL, 0x00F4E64A10B9D027ULL, 
            0x69D4B399416DBA48ULL, 0xBEAFF1D34A6CE527ULL, 0x1FC68BCEF8D7CC38ULL, 0xE669AF819CBD9D71ULL, 
            0x2DBDEBAF1790F9E8ULL, 0xF910391A5EBE8FB3ULL, 0xC9417FDB6621D5F4ULL, 0x88B194110763A071ULL, 
            0x6CB07681B55C6DC0ULL, 0xE90C3E16CB674F09ULL, 0x7D5A0CF5CBB6E380ULL, 0x522C22D0AA309E1AULL, 
            0x683E4BB65D680A64ULL, 0x69042FAA71F87C7BULL, 0x63A0E2208D293847ULL, 0x3228DB6F9BB2D424ULL, 
            0x89E82AA24301F35CULL, 0x0B7378756D6131E7ULL, 0x34B63DA9C3778B00ULL, 0xF055EBB62DC8A1DEULL, 
            0x37CB0BD54F599F52ULL, 0x4FC503A6EEFF26D5ULL, 0x82C60B658C2F72ACULL, 0x83ACBB57529828D2ULL
        },
        {
            0x57F136F648EF732CULL, 0xE1D04587A57E0A6AULL, 0x4708607099F74094ULL, 0x519B8DEADC0EDDAAULL, 
            0xC26B1B49A6C2FA71ULL, 0xFE74D0328B426968ULL, 0x499FE07BC869D149ULL, 0x29227B714A9F2342ULL, 
            0x259D126C1BB986E2ULL, 0x1DB178A5413936D6ULL, 0xD7657E164F89DD4AULL, 0xAB4D93FB0A0455CAULL, 
            0xC074D1243E268BD9ULL, 0x08BB169388E7BBB2ULL, 0x81E53575A17B6CF0ULL, 0xFEE2A0329B19E066ULL, 
            0xE5B68D289130C634ULL, 0x8E12E8CEB4370367ULL, 0x65A9F9009F086437ULL, 0x2828705BB51D17FBULL, 
            0x8279922789751EA0ULL, 0xC004FC90647FE3EAULL, 0x5CF569FBA4B04897ULL, 0xF565D6B85500489AULL, 
            0x4AFAC488BF7C644FULL, 0x15F07B6912707286ULL, 0x3BA8FBFF21C9C87FULL, 0x5E8A079D3A132886ULL, 
            0x18B60E1581738F85ULL, 0x3AA18402343DDD2DULL, 0xFDBEEEDF0CE76C40ULL, 0xB50DB3D3CA88C8ECULL
        },
        {
            0xD49DC27CCF3C78C1ULL, 0x597E26ADC355D14FULL, 0xD82EEA8BFAEA6D03ULL, 0x2C19A4986DC922B1ULL, 
            0xD7E9AFD8D2483420ULL, 0xADFD7791ABD2B89EULL, 0xE9EFE7A8620D58CFULL, 0xAFEB9E1700EF09CFULL, 
            0xA6F80839A07F004FULL, 0xAEA0C81B24CCBAB3ULL, 0x9F0DB7AC4B13EF62ULL, 0x2994688A5F33F082ULL, 
            0xDB83AD2A2552BB44ULL, 0xF540A74FF09A49E8ULL, 0x471B897A09275E3BULL, 0xDD90029AF7E84A8EULL, 
            0xA459BE1AD6747F0CULL, 0x1A932D140DAAE34CULL, 0x257D421FC7A447C6ULL, 0x7D355EA7E4B70B7FULL, 
            0x6D982EAA66974943ULL, 0x9AC434CA29C65BE9ULL, 0x49D40196C1B6FC2CULL, 0x370B88B51A3CE074ULL, 
            0x7304A9F2300B4AACULL, 0xCE1BD828E979D251ULL, 0x7089482403540C43ULL, 0xC26F45D1691ABE13ULL, 
            0xB6D0AB0EAB90E052ULL, 0x494CA732790DB645ULL, 0xB1BB39A05D157CAEULL, 0xBCCA136595398B8DULL
        },
        {
            0x295BA5F1EFE288CDULL, 0xD4F6B73E344DBF41ULL, 0xFAA7616BBB87A7C8ULL, 0xB783DAE361C672EBULL, 
            0x2F94312D8F3F7346ULL, 0xA2600B4FFB60D358ULL, 0xD1A5137038C2BEB8ULL, 0x4F6D133EA765FB69ULL, 
            0x651464AE45A21303ULL, 0xB7B29977F6DBF7D7ULL, 0x3681DCE687721CCBULL, 0x79A5B5D507AF096DULL, 
            0x349E82DD3D00F08FULL, 0x17B753A7B743C2E3ULL, 0x42801F7E8B6A4522ULL, 0x2B6E56EDA59C82C3ULL, 
            0xD6D816D993DB0A29ULL, 0x247F731FF9011AD4ULL, 0x73107E8ADAE33C85ULL, 0x8D8647854434A75EULL, 
            0x4A675E504B7EB1F2ULL, 0x72012B5D5CD0550CULL, 0x1422F8D3C1172693ULL, 0xFB7E878B7C6E919CULL, 
            0xDEC6A8C9A1594ACDULL, 0x8651192877A9EBD4ULL, 0x784901A5F7020865ULL, 0xB7D7E2D603598883ULL, 
            0x48676D8343402351ULL, 0x959BCE54DB1BBECFULL, 0x8142D464762F73C9ULL, 0x3C6239A8A0D60A8DULL
        },
        {
            0x21990213F0989CEAULL, 0xD15E152671BD9D8BULL, 0x0D9DC6C36D7C6309ULL, 0xE81AB8D02F2C642CULL, 
            0x2587A5F38ACAEFE7ULL, 0x382B38499B9E46ECULL, 0xB5E8B3642C4392D5ULL, 0x61BB70075CB09E9DULL, 
            0x45A836502288ECFEULL, 0x9E83BAB6DBB7D293ULL, 0x01E02C7C6F8A9CB3ULL, 0x87357D500D11589EULL, 
            0x26C11E80811AC250ULL, 0x8780666AE743B64EULL, 0xCE855AF6F678F749ULL, 0xE27C04396A7D33F1ULL, 
            0x3CE36568D9D133A0ULL, 0x85BFA698AED85E6DULL, 0x91A48D81821A66D3ULL, 0xAE0B39286953CDA6ULL, 
            0xFCD6999EF808906FULL, 0x4F7AD2ED65CBF51AULL, 0x4FE8CDFFFC73A542ULL, 0xD77A990B2F5A49C8ULL, 
            0xBF2791CDC9B29248ULL, 0xC404211E7176ECFAULL, 0x99CE2D07C8640093ULL, 0xB5519ADB89314D44ULL, 
            0x0EAF42655B1C3052ULL, 0x91440F40DC6B04C8ULL, 0x4870A6235975BD1EULL, 0x19A50E38D668ED24ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseGConstants = {
    0xF7BD9C56ECBCE421ULL,
    0x30EBD4A9F9984122ULL,
    0xEE38DE86D1128D04ULL,
    0xF7BD9C56ECBCE421ULL,
    0x30EBD4A9F9984122ULL,
    0xEE38DE86D1128D04ULL,
    0x60E8E2EB5B0630FAULL,
    0x2240A5BC67767552ULL,
    0xFC,
    0x76,
    0x77,
    0xB9,
    0xAE,
    0xDA,
    0x4B,
    0xA9
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseHSalts = {
    {
        {
            0x2EC7553A70BE7ADBULL, 0x7A7D91B75BA17AFBULL, 0x829DCF60E2D70781ULL, 0xA7D013DD91DD5297ULL, 
            0x3A0CBB42EBF32FD2ULL, 0x3AA6355DB47956E0ULL, 0x4685861660F3B28FULL, 0xC18CE76E47E74D1BULL, 
            0x29B3CADCFDC3BB58ULL, 0xB7555B41B6C98E2FULL, 0x0470FEE6F66D2760ULL, 0x576DF0262B631F22ULL, 
            0xD30021ED634C8F58ULL, 0x774978BB0A352308ULL, 0x7230852FAE022CE9ULL, 0x0FB19F99117889F8ULL, 
            0x3F5CD0E99D082ED9ULL, 0x04A34FBFB197CE27ULL, 0x2FAD25D4C503E146ULL, 0x8865F3EB3ADEAE2EULL, 
            0x9D4BFE4560707B21ULL, 0xCB1923F67D250E0BULL, 0xC27B88DD024CC833ULL, 0xDB14E8423124ED40ULL, 
            0xB9276DEF8D23898EULL, 0x4801D7B0CA1E9544ULL, 0xD5865975C16EB660ULL, 0xD99E5046557C7497ULL, 
            0xC6761178CA372BA5ULL, 0x662DAECF418FA5BBULL, 0x07B440B2176348D4ULL, 0xBBF347F949B6770DULL
        },
        {
            0xAAC54B0557686727ULL, 0xACC1E09138B8077DULL, 0x66FD7BEEF7495CFEULL, 0xB68BD3AC5C8440A8ULL, 
            0x26B4B7E994949103ULL, 0x74FEF4A41E90E0C7ULL, 0xF6CFD5AA0D73BEB2ULL, 0x4B55398B0F511903ULL, 
            0xBE0C9B8DDDFA5F02ULL, 0x4A7626C9282EBB7DULL, 0x1BB4F6A023922BDFULL, 0x7C666D3A1E499C74ULL, 
            0xDDE77EA4DE5E4367ULL, 0x4980A1DDD9E7E028ULL, 0xB65BBAF1EA7BB634ULL, 0x78ACAF83A34504BCULL, 
            0xEA09ED894C67C376ULL, 0x1C9AF1FD747A34A5ULL, 0x1AB6444F917778BDULL, 0x82A87AC839762BE1ULL, 
            0xEEB970574AC95EC4ULL, 0x9706BA3975B09867ULL, 0x9A43E1A459D44F3EULL, 0xE595F8A36F2B3BD7ULL, 
            0x4404C14481675081ULL, 0x65F26C46C816ED82ULL, 0x378E6E00126444B3ULL, 0x349A4C0F3FB06126ULL, 
            0xC6936AB299FDD3F2ULL, 0xF295181F6FE4906BULL, 0x0B2D85ABEE8CB377ULL, 0xBE3A93F402F98379ULL
        },
        {
            0x3F8AFC702B717AB3ULL, 0x1B166E6988083B6CULL, 0x20C4C9D16D07F962ULL, 0x3B912FCB28432C2BULL, 
            0xDB309B556CBF6CD3ULL, 0x24D9AB7D2CCAA852ULL, 0x8A6616A51CABC133ULL, 0x14338C41D662FE22ULL, 
            0xDE9AAC7C35C4173BULL, 0x8DEEA3E1FCD8AE33ULL, 0x9B338D07454E3CB9ULL, 0xE532DC1DA078EB34ULL, 
            0x23C39B8874EC112BULL, 0x2227BE58884FF53DULL, 0xE02FA8A72E6C1E9FULL, 0x122ECEA384737CA4ULL, 
            0x6396A364892F4A1FULL, 0x30880D06A4EC80B7ULL, 0xB3E1A1FE34A1711AULL, 0x7255F6F48AD21586ULL, 
            0x80D8A8EDA810D776ULL, 0xA542ECA3B4796FC3ULL, 0xD2A7932A05494C20ULL, 0x6B75003AB6046CA0ULL, 
            0xDA8F8473CF2C06C7ULL, 0xEB8DAE1A43987DF5ULL, 0xAFB141825688E33DULL, 0x2F81CBCDB55DECE3ULL, 
            0xEFB32FEC7F945A58ULL, 0x7257020A05794C7FULL, 0x446C3DDCE07F92F3ULL, 0xE246E5D469CFB1BCULL
        },
        {
            0x43ECFB4AFF87E0DCULL, 0x80ED062010162DDBULL, 0xDB006620FF502232ULL, 0x49384C5ECE0946AFULL, 
            0x8104AEBD10F135EBULL, 0x9B3F9A77CBA17768ULL, 0x4652A005C3BE33A9ULL, 0x9674E5B0E5740914ULL, 
            0xB091DB3CFC43304BULL, 0x64C25464CD72BD22ULL, 0x0E96763A224DBEF9ULL, 0xD879D3E6D6825140ULL, 
            0xA47EFC6F1499D484ULL, 0x5DC3376415E4AEC8ULL, 0x163BA942CFB0F638ULL, 0xA56D6A31AD8BE943ULL, 
            0x8AEE8B64EA5F30EBULL, 0xED227853D3E0944EULL, 0x698F15B888538CBCULL, 0xDBD643E605439D5EULL, 
            0xAB56AF56244B401AULL, 0x9F2C5A69DEF21F28ULL, 0x9712E4F586C39688ULL, 0xE6DC2AAFC95B1B13ULL, 
            0xEE9E3FA177D05262ULL, 0xF396977266D4ED10ULL, 0x1A7C133F23DD6114ULL, 0xAF269628306C9387ULL, 
            0xB0CA5DBE494CB566ULL, 0x902494D8A9E58F40ULL, 0xD361FA52D856EDA6ULL, 0x2CB4D90365933BF6ULL
        },
        {
            0x4AE33F3887EE235BULL, 0xE643B1E620B98897ULL, 0x46A3620C6ECAD20AULL, 0xE752F61D4059E206ULL, 
            0xF52E315798410B90ULL, 0x814BDDE5D30EE86AULL, 0x5E122B81AAB10044ULL, 0x05F96FECDE694789ULL, 
            0xDF8270A9B9786EABULL, 0x7355C2C03B607678ULL, 0xC8BD44278EC084BFULL, 0xC749F5FFF56C602EULL, 
            0x758F3B550F908919ULL, 0x6AB9538B30D43D52ULL, 0xF722AE39F044F721ULL, 0x92A4CE4CED32B601ULL, 
            0x70FD234F4DE98E88ULL, 0x3371E093BDB1624EULL, 0xD6F673F16BF4D2B3ULL, 0xD4D3B52141634697ULL, 
            0x6F83661A3C1FF3F8ULL, 0x2B578E4D90FAF7E9ULL, 0xCB5DE59A870008E8ULL, 0xCF89D39E5AE68B13ULL, 
            0x943E9B1B7B52F5FAULL, 0x05A33BF9CEA77CC0ULL, 0x56DC66D48EBEA760ULL, 0xE18B69C675551FA7ULL, 
            0xFD8ABB58DA5A4D9EULL, 0xFB897B132E74B029ULL, 0x66EF0657260D560EULL, 0x274244F1D66E8B7FULL
        },
        {
            0x0FC99B96C59C4F00ULL, 0x12EF2D850123EB09ULL, 0x682883ADA553D864ULL, 0x7FB44F5FECC13BA2ULL, 
            0xB2463B16A8F57DBBULL, 0x468DB9E502C866B1ULL, 0x01794F6171D6C2E7ULL, 0xD6AF5E76E1A5DF14ULL, 
            0x212B861EDDB404D9ULL, 0xD37BB8054F2351EAULL, 0x1B7E7C716284615AULL, 0x07132AC03FCED7E8ULL, 
            0x1496BE24D0C03A8AULL, 0x8F032AA9439569AEULL, 0x2A91C53827A62C90ULL, 0x0BE68E81E2D1A417ULL, 
            0xC43B31B41CE0FAB4ULL, 0x992F4B632CE3612BULL, 0xB2B6A45F304D41B6ULL, 0x995479847A64216AULL, 
            0xB0530B3777B3EC14ULL, 0x333262010841DE17ULL, 0x655589000B01785AULL, 0x7333EFE8C6FA2EE0ULL, 
            0x9C1DE8698E2B593BULL, 0xF447DEFBB84C85DAULL, 0x13F767472690DE61ULL, 0x4BF55574D4C0D61AULL, 
            0x42A03409F9CBD0A8ULL, 0x54CD65940716B607ULL, 0xC6ECB42147507205ULL, 0x101F47AAA58A640DULL
        }
    },
    {
        {
            0xF5C4BB6C400E783AULL, 0x9D0D2D885F378ED1ULL, 0xEB32B31ACF975D71ULL, 0x0A56BC667078A099ULL, 
            0xC615A50A2C5C9D8EULL, 0x04155120A82A25ACULL, 0xE836A902E6CC475CULL, 0x3C3DC2A7BD4D21B0ULL, 
            0xBBF29C38B970FB20ULL, 0x081CE45DA664579DULL, 0x3428FAECA40CD793ULL, 0xF832D47E8DEF6D74ULL, 
            0xA671978A83D805BAULL, 0x1DC238CD86F724E3ULL, 0x820F248665BFC453ULL, 0xAA454B78099C9357ULL, 
            0x89F50F45CD5BE6F4ULL, 0xB46BE056B6F9825CULL, 0xF1153F9C95BC86FAULL, 0xB6CA55FAE9959356ULL, 
            0x7F914593DB09C290ULL, 0x129AD34B1693A4FBULL, 0x07027561F7C5F9A3ULL, 0x48E0DBAF1BEC6B63ULL, 
            0x4ED75524A7B20E95ULL, 0x07C58B16AA5FFD2DULL, 0xD34A7A2E819BF7A8ULL, 0x25D802FA2FC0A761ULL, 
            0x6862A66AE1A2CB49ULL, 0x5BB4E18012615D87ULL, 0x96620C5CCA1856B3ULL, 0x1E928DFD7D0FEE45ULL
        },
        {
            0xF46700019F1BBA59ULL, 0x89756A5460F3F79FULL, 0x4225D7F4A3CD43DDULL, 0x6DA50A687E576CB4ULL, 
            0x6713CB990B33B118ULL, 0x0245E80B3D18724FULL, 0xDF00B1A194FA48EDULL, 0x1CAF3D42F2E93A46ULL, 
            0x70C8A388E9BCC68BULL, 0xFB8D407B1DA88BA0ULL, 0x9E8ACD8D7261BB7FULL, 0xBC1329971464212BULL, 
            0x59E3D194AF74AE7FULL, 0x4DBD733F5B0864AFULL, 0xA04E690A88307FE5ULL, 0xBE9CC07C4160E248ULL, 
            0x99FDFD2B972257BCULL, 0x7238B78885B678C3ULL, 0xA48C5DA01383D2ACULL, 0x669F1E49DA4F6870ULL, 
            0x1B14F13148E281D6ULL, 0x01A1BBAAD5F45840ULL, 0xB31A70629758550AULL, 0x7444C75ACF518786ULL, 
            0xFB0A990638F5A19DULL, 0x3CA8D2E014AEB102ULL, 0x1D0276862247F8C5ULL, 0xD58E52D85C9796CBULL, 
            0xA16529C50A9893F2ULL, 0xF2464891508BA416ULL, 0x1BF16DC76AA80C62ULL, 0xC2D42D022670B74FULL
        },
        {
            0x8FA0EDF58CA2F8C3ULL, 0x9E0D12774DBAE239ULL, 0x1E3551AB83CE6309ULL, 0x9E0D2570F400C8BDULL, 
            0x562227AC0E928FEBULL, 0x842602196A5E0363ULL, 0x551CD29E81AFB56DULL, 0x8EC7F495CE80C69EULL, 
            0xA9BED772E5FA9CCFULL, 0x08A203B9D58147E6ULL, 0x7BC8AD5716FA94ADULL, 0xA86F1F01D916921BULL, 
            0xDFEB09FB7ABCBC49ULL, 0xFB7B6DE738C07859ULL, 0x719F0467143A109DULL, 0xBC06DFC4EF8E281FULL, 
            0xAD703AF99D098DAFULL, 0xBB7988190D8D4082ULL, 0x300DABCBE8C67E6DULL, 0xA947CCDEA824925EULL, 
            0xDA016D6F6DF464F5ULL, 0xC4D311BBFFDDF5A7ULL, 0x80B4183FA799E18EULL, 0x6C84F298A2A64549ULL, 
            0x756F1DF128226E89ULL, 0x791A58AFA77DFE2CULL, 0x022EF7327E1D37B1ULL, 0x69BBB597717AE998ULL, 
            0x94D9A7F9F7223553ULL, 0x906C8E31151E36A9ULL, 0x15F40A31609D4E20ULL, 0x3D365E396ED73D00ULL
        },
        {
            0x1A2F8A424F2B0B10ULL, 0x11A653CDA199B254ULL, 0xF37CDFCABA26AC2FULL, 0x2F1E6BE98CF228F2ULL, 
            0x9400EF5147429F6AULL, 0xA1630935BEC1432CULL, 0x5D47B32471C1282BULL, 0x99F965CA9912BD6FULL, 
            0xE9CABC6256E90E24ULL, 0x2D2A165A1D64CA1DULL, 0xFA2003ED7A5A3FC0ULL, 0x54AC585EB0D27A6CULL, 
            0xE06537BDBD8EBFE0ULL, 0xFCA32EB5994CC325ULL, 0xDEEA6A588C055F5BULL, 0x4CA1F10BF64C689CULL, 
            0x18258A36FA1F5A2FULL, 0x33FBCB1C26BDEA1BULL, 0x6F8AE494C4816433ULL, 0xD77AB3B2A71BA5F6ULL, 
            0xFA9D67FA0230853FULL, 0x83EBA1DEDF8C43BBULL, 0xCD9E3B23D3349652ULL, 0x8A21F30D2D34FDA3ULL, 
            0x179FA5AA62F36749ULL, 0xD95037F1990C913AULL, 0x582D965AB37E81D7ULL, 0x4A6C7D65633729D5ULL, 
            0xAAB1D0C04A5B7998ULL, 0x0BD3FF7104E709ACULL, 0x7C63099DACFDDE0AULL, 0x00BBA9535D9AC766ULL
        },
        {
            0x6BE4B928573CAAC1ULL, 0x70AD370BA88F9DACULL, 0x9D1A621482DDDC2FULL, 0x9450160A9097AFA6ULL, 
            0x46105C13C4B5EC4AULL, 0xCEDB4BD1C16F5A95ULL, 0x154371565C8C07C1ULL, 0x8B296F592C40DFA6ULL, 
            0x5A258C4FC80B76A0ULL, 0x3182F03609F818E4ULL, 0xA935D4903B725507ULL, 0xD14B288CDFBF6DBFULL, 
            0x7482B5808C7BC2C3ULL, 0x963678B5D494E18EULL, 0xB7F715C65ED0F183ULL, 0x6B93D0CDB274C255ULL, 
            0xEFF7BCDBFE6B8E0BULL, 0x01BE6E7B4C6871DCULL, 0x0367297C48065C2EULL, 0x01AAF2ACF09C8131ULL, 
            0x03927ABC71D2DCCAULL, 0x3A88981A55698BADULL, 0x8310D92B8FDEA704ULL, 0x7FFD59BBB20CC00FULL, 
            0x2560E295826C10F8ULL, 0xA1A335928B560319ULL, 0x37ED07ABB817BAFFULL, 0xE09565AC38060994ULL, 
            0xD53A2419ACE6C06DULL, 0xD60F26C66F7C32D3ULL, 0x9E7BFE871DB6E89BULL, 0xFBA84D5E353DFCA0ULL
        },
        {
            0x28109B7E2A527D01ULL, 0x7B84046DBF7640B1ULL, 0x647D20EB5C8E53A6ULL, 0x45AD93573582B1E4ULL, 
            0x85A3931EFAD1A021ULL, 0xCE14F089930BB0DBULL, 0xBFA59B2E1DBF501EULL, 0xCBBF0FDABB4F4B4BULL, 
            0xE8680EE027E0EE79ULL, 0x78F56318C9A065A4ULL, 0x3086E80AF406C5D6ULL, 0x391F8A25215408DDULL, 
            0x0DA07712B5849452ULL, 0x0B8F8CF1D0C9DD69ULL, 0x2D378853828D38C6ULL, 0x3FEF876B7B74A36CULL, 
            0xBAF2734EF4151547ULL, 0x52636FEF34D9F622ULL, 0x981C121398DA633EULL, 0x640EA4EB31DAF670ULL, 
            0x924C37C096DBD47CULL, 0x7477F7EFE6BC528EULL, 0x67C676DFD5037423ULL, 0x95B266BC8AFE3B1FULL, 
            0x35EBFBB147DF7CEEULL, 0x1714C416928D4104ULL, 0x189CC0BC6F556421ULL, 0x9494AC9620AE418EULL, 
            0x39C75E479B3085C8ULL, 0x825C8FD13A680160ULL, 0x92333B5F2D250CAFULL, 0x4A244742C713B3A0ULL
        }
    },
    {
        {
            0x4DC6E21902B36DE3ULL, 0xFD3E93C3C91908D3ULL, 0x4448325BB5A9EFE7ULL, 0xBA27F90D81C87C03ULL, 
            0xAD1EA5C000BBB80AULL, 0x2537F1FEEE9F8DBCULL, 0xA4280C5657061ECEULL, 0xA1EBF3DF09C89DF7ULL, 
            0xCDF5B78E17F59273ULL, 0x330A1FFBE4B2E534ULL, 0x23A08BC34D3E1B06ULL, 0x7580E281516AFC72ULL, 
            0xB47DEF85E4FEF6B6ULL, 0x9FA72B4F7A6300E5ULL, 0x26790311217F6C94ULL, 0x31E97FA8DADC9242ULL, 
            0x7F830417B11483B6ULL, 0x3D17C89FBE7C4D31ULL, 0x6CA29C996189DC01ULL, 0x58B3F3B8D0608AFCULL, 
            0xEB03118E30BF6BB1ULL, 0x9AB4E7A920139AA4ULL, 0xC9FBE3ACF9EF1A43ULL, 0x10115B7DF0686454ULL, 
            0xCD1DEA17089806C8ULL, 0xD50F6680D116659DULL, 0xCE256965E36662ACULL, 0xD8F5220693788AD8ULL, 
            0xC8EE41F6945FC203ULL, 0x0F23FD0EBE478118ULL, 0x19700273BFE55E36ULL, 0x430973CC83DF62FBULL
        },
        {
            0x92E3D20BD1233E3CULL, 0x5814A37C5CE1B545ULL, 0x20C331B2CD0FF75FULL, 0xB4ECE31E9B349F1AULL, 
            0x45C217542ECD5F8FULL, 0x84C79506F9DD850EULL, 0x69BDE5DC92E9F5AAULL, 0xD3AB5D7E85EA26D8ULL, 
            0xDC5A0A2D8D87C9C7ULL, 0xAA0A0A28F8BCFFA6ULL, 0x245D32075E61BFB0ULL, 0x53B0CB0F95633012ULL, 
            0x00345F5F5C7B8018ULL, 0xE4DD05DE826F0EB0ULL, 0xF63CBBDF5C5DD434ULL, 0x28059656A5A4DE20ULL, 
            0x4FECDB0B287FF6B6ULL, 0x08C6981FF1CF8A2EULL, 0x851B251DBA5584DCULL, 0xC586B421EC2B3531ULL, 
            0x73A5CF4BD27EC8CDULL, 0xCB9B30E2E6AFDE9DULL, 0x7AF26E13FDD21506ULL, 0xF419E3312F124B8EULL, 
            0x0E986227FD32C9F7ULL, 0x22EC29D01EE2A180ULL, 0xD774CBB18689369BULL, 0x64603043DD55F106ULL, 
            0x9510E1575C0EA09CULL, 0x46E11C6259905DD2ULL, 0xEC70F5ACE4165E07ULL, 0xBEEE7952AE5FA009ULL
        },
        {
            0x2534B4CF9FB03422ULL, 0xEF2B7A1728DDA238ULL, 0xD8859B79441961C5ULL, 0x101ACA5C01A067A2ULL, 
            0xE63BAF6DAEAFCE63ULL, 0xAAB9D7080689801EULL, 0x0FDA74A4634B6823ULL, 0x13DAB278824F6F71ULL, 
            0x2DE72DAA2FF75FF2ULL, 0x0F79C2B3EB6C730CULL, 0x0FE1BA9A8BA1B92BULL, 0xFA53843411665A26ULL, 
            0xA2957D10732AD35DULL, 0x8754E1A5C1DD10CDULL, 0xBD4D5BD22F2CF9CBULL, 0x53471432E330E974ULL, 
            0x7B2C5C9A7A54DE3FULL, 0x15D6D06459CB587FULL, 0xAEF9CAA7E6233D57ULL, 0x5D5EAF77C3E25BBEULL, 
            0x8E81A2F7849D6512ULL, 0xC4E5DEF93FD20BD7ULL, 0x815457C8D74888ABULL, 0x01AEC527D8948E72ULL, 
            0x37B3556426F8EC4FULL, 0xCF07771DAB37B3F8ULL, 0xD874F0727226AF74ULL, 0xC9169C16B87ADE91ULL, 
            0x651D684F879944F3ULL, 0x930976BBCB6ED98FULL, 0xACE2480F8C39F875ULL, 0x689EC881F7AE74D8ULL
        },
        {
            0x0E5E9704C4269ECDULL, 0x445713CB6F733546ULL, 0x0CB5323AB1E8E28CULL, 0x9AAD20FA711A54E6ULL, 
            0xCC78B08AF06772C2ULL, 0x040AB07F1F16CF5DULL, 0x2A6789CC65F27721ULL, 0xC34B24F580FB4FBEULL, 
            0xA42A13C406DA49BDULL, 0xA878DF09F5E72C2FULL, 0x46FE2A6BEB1F46E5ULL, 0x35E67EB069315C8BULL, 
            0x936AD76B1BD4779EULL, 0x6E981EE38A943D06ULL, 0xDF225C119853C87FULL, 0x5DAB26A2AF78FB99ULL, 
            0xC74230039E844660ULL, 0x125A1C096314035BULL, 0x466ECC54A99362BCULL, 0x9122CE27F251EE7CULL, 
            0xA8D53CB9FAF6FF56ULL, 0x702D6324AE1C90E4ULL, 0xAA14457DCCE0E62BULL, 0x6BFA3051C2B23571ULL, 
            0x231A2AEAC3AB3D21ULL, 0xB60E45BAA70C80D6ULL, 0xC59C5B7BD267A92BULL, 0x3A276B9881F80B25ULL, 
            0xE0EC302E83C73F34ULL, 0xEC07578B736B183EULL, 0x5022F6CA65ADFDD6ULL, 0x982D17BF5C2CAD8AULL
        },
        {
            0xAC456E2C63294F46ULL, 0x0AB2744A6EDBD0DAULL, 0x819761B58E6883D3ULL, 0xBA9E95976DFE3900ULL, 
            0x9DF94A3C9B255459ULL, 0xC90357F10D392A4AULL, 0x67820766775E2620ULL, 0x28B2F05A23C20AAEULL, 
            0xFEC0CA8D1D9274FDULL, 0x5E745C9C8650D1E9ULL, 0xA255C8F38FF9E960ULL, 0x7B8E801D73D24AF6ULL, 
            0xD5D26DAF98FB6330ULL, 0x35FABF674679AC65ULL, 0xF7A00BF861A936D8ULL, 0x2D0EBAEDFB5B8439ULL, 
            0x00C954508CDA0FB0ULL, 0xA7A2DD92050401DCULL, 0x905F4EFC0335FC07ULL, 0x7C5734BC36789E47ULL, 
            0x705DF08316F2612DULL, 0x34682852E109C903ULL, 0x05096635531773CCULL, 0x6333E7D01EEBDD5DULL, 
            0x35F3F8148B614BB9ULL, 0x03573BADCE0F5A78ULL, 0xFC3D20BE8FF0F2ABULL, 0x91EA91F42A3947E9ULL, 
            0x673D8878A506B51DULL, 0x5E40347615FECEB7ULL, 0xC7A9E2293B763271ULL, 0x925C5411AA5B7870ULL
        },
        {
            0xE69D842CC933F724ULL, 0x43EE3C2DC6F0888EULL, 0xE3593C68EFD20AA3ULL, 0xAA91D9BEE6388B75ULL, 
            0x217FE29B748F386EULL, 0xD59C5989A9AB9234ULL, 0x1EF08E8D09A9DAFFULL, 0x7D3D9BA9C281E242ULL, 
            0xAB85FD1CC027CA6AULL, 0x736446FF73B043EFULL, 0xDB0835CED0613E96ULL, 0x4927C4A07D64B0D3ULL, 
            0xF78B9FBD6DAC2FF1ULL, 0x5EB2001C529E0BFFULL, 0x338EDBA8D7AD0499ULL, 0x3862F62F3DCDB3F3ULL, 
            0xD3FCD73B2C1FD11CULL, 0xFB2D68109CF35A2CULL, 0xED10AD527DF88EDBULL, 0x466FCED3147E12EDULL, 
            0xA042315D333C66AAULL, 0x9301265DB2C1B657ULL, 0xA2DC5D4A65C5C712ULL, 0xBA2331F47CA288EDULL, 
            0x30854AAFFBB27A2EULL, 0xC6CC4C7DE7A004DFULL, 0xD22A552164E9E10DULL, 0xA76E0C2154F600FBULL, 
            0xC289F4F7D397CB94ULL, 0xE991991ECED2A92BULL, 0x4D48589D80713008ULL, 0x1BAB81019E58555BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseHConstants = {
    0x72EA9DB175F3FFF4ULL,
    0xD85C380CDE6AAFF3ULL,
    0x6FAE082EE3F00789ULL,
    0x72EA9DB175F3FFF4ULL,
    0xD85C380CDE6AAFF3ULL,
    0x6FAE082EE3F00789ULL,
    0x232396A296F9F7C1ULL,
    0x710849BDD4A4DDB6ULL,
    0xEE,
    0x24,
    0x69,
    0x68,
    0x96,
    0xC8,
    0xCF,
    0x56
};

