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
    std::uint64_t aPrevious = 0xBF951011F1A5E3FEULL; std::uint64_t aIngress = 0xE3C1AFD544460844ULL; std::uint64_t aCarry = 0xB37DD56A4F743F45ULL;

    std::uint64_t aWandererA = 0x8B16547BB1325407ULL; std::uint64_t aWandererB = 0x864222E7C1756AA4ULL; std::uint64_t aWandererC = 0xBAB5378B9C23DE30ULL; std::uint64_t aWandererD = 0x966CA446BE98B52EULL;
    std::uint64_t aWandererE = 0x9FBBFED23A0C206EULL; std::uint64_t aWandererF = 0xC239E5F881FE83FCULL; std::uint64_t aWandererG = 0xDF9DC768280A3FC5ULL; std::uint64_t aWandererH = 0xB64EAFA0E9E783EAULL;
    std::uint64_t aWandererI = 0x85188CC9AF4E37C5ULL; std::uint64_t aWandererJ = 0x89BC0635430DF63FULL; std::uint64_t aWandererK = 0x9DC5EE5DED908C64ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10995324902546063469U;
        aCarry = 13729993485358785270U;
        aWandererA = 9600360440553936139U;
        aWandererB = 9444355767530183365U;
        aWandererC = 16966490063035858790U;
        aWandererD = 13258348233888003877U;
        aWandererE = 15706901725236575757U;
        aWandererF = 18439832499920077319U;
        aWandererG = 15709201635645218341U;
        aWandererH = 14792937856977407209U;
        aWandererI = 9810888859043059671U;
        aWandererJ = 9553034023797707979U;
        aWandererK = 14161352944820401462U;
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
    std::uint64_t aPrevious = 0x8013E0ED92A56B77ULL; std::uint64_t aIngress = 0x90F4735884CF12E3ULL; std::uint64_t aCarry = 0x88AE4975AF67A97FULL;

    std::uint64_t aWandererA = 0xBAF0F1006699D89EULL; std::uint64_t aWandererB = 0x9727A0C25F5AB454ULL; std::uint64_t aWandererC = 0x96A88FAD5B362DC2ULL; std::uint64_t aWandererD = 0xF57281A562825897ULL;
    std::uint64_t aWandererE = 0xC36357709EF3188CULL; std::uint64_t aWandererF = 0xC4547B1670107C78ULL; std::uint64_t aWandererG = 0xC17FB02523469A02ULL; std::uint64_t aWandererH = 0xFB0E41E970BE4D74ULL;
    std::uint64_t aWandererI = 0x9A39CC716945A3F6ULL; std::uint64_t aWandererJ = 0xEA2716E6D0C601DFULL; std::uint64_t aWandererK = 0x9650D39DADB4BB75ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12233255390292899256U;
        aCarry = 16737481196462718657U;
        aWandererA = 10472874872166829249U;
        aWandererB = 14692824034660671963U;
        aWandererC = 10323146281609283412U;
        aWandererD = 13409380641365837405U;
        aWandererE = 10407851522943404229U;
        aWandererF = 15666353274688464603U;
        aWandererG = 12710563290798741620U;
        aWandererH = 14519276886392103337U;
        aWandererI = 17970720281906568159U;
        aWandererJ = 10565989982888887470U;
        aWandererK = 11290963854699403315U;
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
    std::uint64_t aPrevious = 0xB40E3911DA993B75ULL;
    std::uint64_t aIngress = 0x9EB5B1E75929C97EULL;
    std::uint64_t aCarry = 0xCE6E91926048ECCDULL;

    std::uint64_t aWandererA = 0xA8FE48E83321B419ULL;
    std::uint64_t aWandererB = 0xC4FF24217A1BC627ULL;
    std::uint64_t aWandererC = 0x80F97B01B6C45979ULL;
    std::uint64_t aWandererD = 0xD89C8599DFE5CC66ULL;
    std::uint64_t aWandererE = 0x8209492EBF0D2A29ULL;
    std::uint64_t aWandererF = 0xB0ECFB5FEE0422C9ULL;
    std::uint64_t aWandererG = 0xA6C38AAC36DA89C8ULL;
    std::uint64_t aWandererH = 0xB8BEDBD0CFEBDC62ULL;
    std::uint64_t aWandererI = 0x9F8F56CCC4F1F782ULL;
    std::uint64_t aWandererJ = 0x87BA5CE9D80A8502ULL;
    std::uint64_t aWandererK = 0xEE20C635CBF9C820ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
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
    std::uint64_t aPrevious = 0xCFE50B02349679C9ULL; std::uint64_t aIngress = 0x87FB9C6C1DBDEC95ULL; std::uint64_t aCarry = 0xDDA64EB15DB7A328ULL;

    std::uint64_t aWandererA = 0x91E624BAB206149CULL; std::uint64_t aWandererB = 0xCFCE585E8C1F2BB3ULL; std::uint64_t aWandererC = 0xD9404215187A6A4BULL; std::uint64_t aWandererD = 0xEA9EC72DF13FF529ULL;
    std::uint64_t aWandererE = 0x86A70236EBD844BDULL; std::uint64_t aWandererF = 0xE70813A39AD86BD6ULL; std::uint64_t aWandererG = 0xC936224FD5A956CCULL; std::uint64_t aWandererH = 0x89D0B2C08EE582A8ULL;
    std::uint64_t aWandererI = 0x9EE850F66EA444B1ULL; std::uint64_t aWandererJ = 0x8BE7236801A62B94ULL; std::uint64_t aWandererK = 0xEED498E443EF4E0CULL;

    // [seed]
        aPrevious = 17980848947454807589U;
        aCarry = 16064109778999891278U;
        aWandererA = 9426419581588799273U;
        aWandererB = 18159758931507187355U;
        aWandererC = 17466834639611434827U;
        aWandererD = 9290669484476065102U;
        aWandererE = 14126512762657211624U;
        aWandererF = 16829720191719248086U;
        aWandererG = 10702229661084787750U;
        aWandererH = 12336839528512320118U;
        aWandererI = 10128892379812603517U;
        aWandererJ = 17887669040714733530U;
        aWandererK = 18200382294086474652U;
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
            0xFD65CDA6F12A43F6ULL, 0x728CE3F93C44FFADULL, 0xFF41AD52AC394E8CULL, 0xB396B181EC627AB0ULL, 
            0x926DFD25CF85B353ULL, 0xDEB89281BFE829BDULL, 0xEF0F0D26FEC428C2ULL, 0xFE63B39A5A9AB2C3ULL, 
            0x3E21AC172212C62AULL, 0xD5EEEEA164DBABA9ULL, 0x8FE48A16642EC96DULL, 0xE1776FC77766E067ULL, 
            0xD23318E8D7FD2CBCULL, 0x972AF4B1454A683DULL, 0x875330452E2C0F42ULL, 0x682DF712780FE7D0ULL, 
            0x81AEC16853364482ULL, 0x641B9189E963E8D5ULL, 0x9DA9177EF14D195CULL, 0xDE89D44DB4D88DEDULL, 
            0x30A7CD6522904235ULL, 0x14D1E364B61E5C9EULL, 0x6FDD952C08E1E4EEULL, 0x84B754F3E9334758ULL, 
            0x7BFBCE3FAA6C87E1ULL, 0x66FAC5D8AB94558EULL, 0x9E61E935C3723AE4ULL, 0x40AD4A1735D054C0ULL, 
            0x71CE7E2D1615A374ULL, 0xDDB646BDCF855CEBULL, 0xE201CC1F38873AAEULL, 0x12A247B6425C4238ULL
        },
        {
            0x1B6F0B2632A9D475ULL, 0xFFA9C8890CC2946BULL, 0x31B639752FDB2A0BULL, 0x5DE5E44B0B7A59E5ULL, 
            0x6C5CA790AF581819ULL, 0x55E7B1C97BE03371ULL, 0xECDA9651E59F7427ULL, 0x76CB1D2982A81C1EULL, 
            0x2B9ED4B6B4704B47ULL, 0x74E83267CCC3A847ULL, 0xBCB2A04DB3ADA0ADULL, 0x2761E3237AB11F2EULL, 
            0x4E64E879AE6423F8ULL, 0xF5235A014844E67BULL, 0x84F32689C29C6E95ULL, 0x0F0BD0191BF172AEULL, 
            0x09840BA9F92FB9DAULL, 0x973AB1165AC59709ULL, 0xA205E112FCA091E0ULL, 0xC48A6CA1E514523BULL, 
            0x2494BB486E78006BULL, 0xC543601D663C194AULL, 0xB82CE5C13209E737ULL, 0x8A7871D9DC83D599ULL, 
            0x3E3EDAA36BBE3B3DULL, 0x95CD106367D0A61EULL, 0x57FEE2BC0737CCB9ULL, 0x55431ABCD4E341FAULL, 
            0x1BEC0F2EC7CC18C2ULL, 0x137C056F0749AB1FULL, 0x15C2B6F3076B03A3ULL, 0x34E9C03394D9E9BBULL
        },
        {
            0x662B167BAF38B49FULL, 0x282AAFF19FF7113EULL, 0x67CE894CB7C67BFBULL, 0xE80C9A96BDFADB3FULL, 
            0x9C63FBADF2EA5379ULL, 0x7366DA039CED3DB8ULL, 0xF3C9686940F501C4ULL, 0x047DCC087871B390ULL, 
            0x5771524E1FC5C97BULL, 0xE2B177A8D7AEDE17ULL, 0x5B84B7CC942BB254ULL, 0x73B83209D1A6325BULL, 
            0xB22392333C10EDB3ULL, 0x4D920E94BA490625ULL, 0xF1BF8369DB2B480FULL, 0x4769BE9E60A9EE63ULL, 
            0x16D71B231D4EBC7CULL, 0xD46840B7D8DFACFAULL, 0x7AEC014672AE2D1BULL, 0x36094180A753DF00ULL, 
            0xFAF6976C77ED1311ULL, 0xB134874D0D5D7F28ULL, 0xC89D3322D377E1FCULL, 0xD23567D5DB5F1E3AULL, 
            0xE022BEEAEC4C3916ULL, 0x7D95444CCE9D8241ULL, 0x588E467A35C50E84ULL, 0x3FF65EA0D36A46C7ULL, 
            0x965B68CF03904C7AULL, 0xAD1A251667C5CAA9ULL, 0x33B29E0BD886C2E1ULL, 0x183EBE1F199437E7ULL
        },
        {
            0xA48EE8BA0172FC6BULL, 0xFA6722544FBCC2EFULL, 0x9DA8B3E7C127983CULL, 0x643725922B7FE5AAULL, 
            0xCC1ABCD0692370C0ULL, 0x8AAC558446AEF082ULL, 0x99FBFBBA56204DB0ULL, 0x2635C19E5D8E4CE0ULL, 
            0x0D86F008DF4BBD72ULL, 0x97A263537E131C58ULL, 0x6916F30091CE9406ULL, 0x8A2695BDFA8F67D9ULL, 
            0x5E94E52495D282EEULL, 0x7CA121EA760904ADULL, 0x113E9DE2EB7E636CULL, 0xCE60CBBB8D8EF8A2ULL, 
            0x891C913074530514ULL, 0xE9CA9CBC34E4A6F5ULL, 0x9319E3A88642819CULL, 0x88102A2FB99CDCD5ULL, 
            0xC1581F41699BEF68ULL, 0x22CB9664CF1370A9ULL, 0x26B686193F37C684ULL, 0xEBDF7ACB9C1AF8C5ULL, 
            0xDEB646E74730BED1ULL, 0xFD6DDAB4D7F15C7EULL, 0x668B2D4A8737B4F2ULL, 0x46620549DB701E4FULL, 
            0x23647CF7C3B7680AULL, 0xE94A95D0A5B29C2CULL, 0x297FFE173780B4E6ULL, 0x394886B87145643AULL
        },
        {
            0xEE5691A6E5BD1D66ULL, 0x8856BE25BD4363D4ULL, 0xC61816A06F268E27ULL, 0x5E19112724E46D58ULL, 
            0xD205142F472BAEB4ULL, 0x6A0B1BA9E98E89A2ULL, 0x5D5045FDDD169E39ULL, 0x67B47B571355ACEBULL, 
            0xE42C433D4D0EAF03ULL, 0x77473426B25CFA2BULL, 0x1D21A90A44C5111EULL, 0xBC04EDF0E4BC2D5CULL, 
            0x942CD3FDB8BC6F21ULL, 0x518A96CACADF6557ULL, 0x0AE4C81E44088BC2ULL, 0x9EE5020867864178ULL, 
            0x0E110B3AE4353CABULL, 0x5E1D87231D49D581ULL, 0x5E8915D73172EA82ULL, 0xD0C74A6EDC67F066ULL, 
            0x3D95C5A5CEF1C01DULL, 0xD1593FD9E7777317ULL, 0x8EECE41F3B755A30ULL, 0x62185DB8738AD661ULL, 
            0xF8733F4FF8F16D1FULL, 0xC5832F0BCDB7DF8EULL, 0x70212294A36FCF35ULL, 0x10835B49E036A912ULL, 
            0xB62CE78CF1634C63ULL, 0x1B82E6450127BE50ULL, 0xE506D596660A42A0ULL, 0x41AAA06F4630290EULL
        },
        {
            0x5FDF34CCD9F73D8DULL, 0xCA13EDB27137DA3DULL, 0x06D963CA87B57002ULL, 0xB52B20EF8E2C3F3CULL, 
            0xB88064B4D4B3FC5BULL, 0x4DC6FAB7CBD53030ULL, 0xD0B95BC26B83A1C4ULL, 0x88BE7E9A17E655D7ULL, 
            0x2482EC8CCF526D7AULL, 0x3E37DAFB059623EBULL, 0x8BBC8C6A7A07922DULL, 0xE6DF81218B66C372ULL, 
            0x40F02FFABD0F095DULL, 0x33F30D02FABABE4AULL, 0xEEA34D3C2D014E8EULL, 0x7A7A28BA8E95ED7EULL, 
            0xD9B08D410A5F34DDULL, 0x98BF31BFB8BBA05AULL, 0x4299DF99ECB9E6F8ULL, 0xF57565B47FD43BD0ULL, 
            0xE283DA919D5A6258ULL, 0xA657C7B0404FE301ULL, 0x61D1E53649024845ULL, 0x9CEEE01BE794463CULL, 
            0x11E561767845D666ULL, 0x45DD88E3E9DECA8FULL, 0x85DE3890D7A855CEULL, 0x8C063BF153C05AA3ULL, 
            0xBCAC261FA7EAEB2EULL, 0x916F5ECF67F7A675ULL, 0xE30840E93E53356FULL, 0x837E20A6B01046DFULL
        }
    },
    {
        {
            0xBD0D0D1A0881A3CDULL, 0x79EC2EA1375A4B98ULL, 0xE925879F75BCBA14ULL, 0xEE12373C41AE80FCULL, 
            0x5EE0586634DB4943ULL, 0xFF6F685C9CB7DB8EULL, 0x93570F66E3AC3D5CULL, 0x6226BBD4200266F6ULL, 
            0x04D0C28C8EEF9638ULL, 0xDFF91D43F014E212ULL, 0x370709C3E223E479ULL, 0x555BD1ECD65A9695ULL, 
            0xEDAECA2782D874EAULL, 0x89F1A32DC6D2EEB3ULL, 0xF15F43963A4EAE02ULL, 0x514DBFC04D6BFF7AULL, 
            0x20BFCD5B84C95804ULL, 0x300194F7BF290F2DULL, 0x427475707293E741ULL, 0xF19B1CB2805C6859ULL, 
            0xDC627A7E14757A42ULL, 0x5A5B2DBC77C557D5ULL, 0x19CA439355A28E8DULL, 0x8BE19DA6ACEE311AULL, 
            0xF22B3359EF17C84EULL, 0x4DAEBB5FAA977E6DULL, 0x10C7D0C1F9D307F1ULL, 0x526D612C5CD5FDC0ULL, 
            0xA3D538CA34D9F229ULL, 0xBB29BB647C09C01FULL, 0x92FFDA857C347DE6ULL, 0xC5EF9150B888B209ULL
        },
        {
            0x630045534ED95679ULL, 0x52C33C35E22AC143ULL, 0xB006DE9724798270ULL, 0xAF6ED08110807530ULL, 
            0x2276F15BF16E7E02ULL, 0x30EE5BC516B2AEA3ULL, 0xBEACF3956504D866ULL, 0x86343D6B3B4383DFULL, 
            0x2CD0F295A19B6E6AULL, 0xCD7D6F54ADA5606FULL, 0x535DE7DA4A269F48ULL, 0x17D183D99F00024AULL, 
            0x75D16C0F726136FDULL, 0xE15368172D1E5BAEULL, 0x67D1392F423AC256ULL, 0xF7B57A1446F148F1ULL, 
            0x7E4D26024706C497ULL, 0xC1881D595958AF7CULL, 0xDB9A8841FA3404CFULL, 0x372918E0AE1B6F20ULL, 
            0xD718069A855C8AA8ULL, 0x5BFCAF842F4F811FULL, 0x37979B73C64D82F5ULL, 0x0E62C3ADFE3F463EULL, 
            0x79A4040CA0DE7878ULL, 0x70CFBB1DA7F97301ULL, 0xF524447CCA429848ULL, 0xC9F69D6BF4C4DF01ULL, 
            0x2DCC9A5E90A4E428ULL, 0xB146E8CF3A89F906ULL, 0x436C83A25C1679B2ULL, 0xD03A2AEE57B5EA46ULL
        },
        {
            0x9B9C6AD6C0A79CE4ULL, 0x8814AEB09C1FB144ULL, 0xF276B4BFC0E08A9CULL, 0x0B437EFAE711C335ULL, 
            0xB880579EA3F82B6DULL, 0xF775EAC460BC6B3CULL, 0x28EF8115AD912DADULL, 0x2014B8BEF3A49A59ULL, 
            0x897567700253B419ULL, 0x42F32084D35D29C2ULL, 0x9C8E9DDD86728C00ULL, 0xADDD33F7F7EA33F9ULL, 
            0x18308951C6F060BBULL, 0xC40FB62C711FEF95ULL, 0xC0901D49C4CEF740ULL, 0x8429B194A1BCF22EULL, 
            0x9917D531327A385FULL, 0xCD6E41E35B176DEEULL, 0x08FB5948A728C40FULL, 0xFB757B2D9CE7F503ULL, 
            0x935F7C9EAA1AE1A5ULL, 0x0646D9979140F1D5ULL, 0x2AF3EFE09A093680ULL, 0xB5D6F2FD06AB5FBBULL, 
            0x86B5CAC834F454BCULL, 0x101DCA88B755B4E8ULL, 0x44B81DE88E7B04DCULL, 0xC8DB59CC53524114ULL, 
            0x24CBF3C61AD13F21ULL, 0x8D438DAF23454BD2ULL, 0xBCCBADBBABC9CFF2ULL, 0x2289D7CCDB2C5A6AULL
        },
        {
            0x259124A20C9A70BBULL, 0xFC9E5844A4061F6DULL, 0x7E00B4098AA18A6CULL, 0x63BF6F927F067522ULL, 
            0x475C80A1849C0164ULL, 0x9737076D46A74B3EULL, 0x2D168AF62B07A672ULL, 0x44978FA10D02A7A4ULL, 
            0xE63BCF3BCFE1CF37ULL, 0x43227117BA01752CULL, 0x80303C0DCF5478ABULL, 0x8A7E349B24955BFBULL, 
            0xF0A253019A59D4CEULL, 0xEED5876365C7CFF1ULL, 0xE1325B8CE1187186ULL, 0x25F9B66C8DAE863FULL, 
            0xA9738B75BC105B96ULL, 0x5524C4A343184144ULL, 0x8D06B226D69BC728ULL, 0x74809052E99E2FA9ULL, 
            0x0CD87217F84E65F9ULL, 0xBE1B243C059737D4ULL, 0xF5770FAD0B0E4475ULL, 0xB2EBDAF3EC107A30ULL, 
            0x7BCCDAA4DEDC434EULL, 0x024BBE0A9B85E0D4ULL, 0xB391E86FDF0D39F3ULL, 0x79A3846679542447ULL, 
            0x758010B9077F431EULL, 0x0AA85EE9E7712883ULL, 0x326202A0244B35DCULL, 0x55D02A73B234138FULL
        },
        {
            0x7DB94D4EFC41F144ULL, 0x708D56193832E808ULL, 0x597CEFDD703C7C72ULL, 0x240DB653C04F249CULL, 
            0x17DA552EF5085217ULL, 0xFA1594171D31D839ULL, 0x817208A681D98EDDULL, 0x55C50A0D1E9EF74EULL, 
            0xC2E0CE9B472FFAB2ULL, 0xB97CC1AEF3393C85ULL, 0x1ECB8ED9A2232DADULL, 0x1BFDDACD947D97ABULL, 
            0xF3D85C660AD7895AULL, 0xE8A41013A9439E2EULL, 0x3741B78305CDC618ULL, 0xDCD4AA793B241483ULL, 
            0xC70C866DF4342516ULL, 0x077E5657ACBBABB0ULL, 0x454371ECC434F186ULL, 0xDC9A81ABE632CD62ULL, 
            0x3DA97351D122959FULL, 0xB6D4402A587EBA31ULL, 0x2A9E3BF9FE06C243ULL, 0xBF0AEA7E17377B93ULL, 
            0x1B14CC90BD9929D0ULL, 0x7FE3C6C60B14C933ULL, 0x9FB3FAC8AF5D5F59ULL, 0x02B3A89E2F0D3372ULL, 
            0xF51D699A353AD4CEULL, 0x821A32061369999DULL, 0x48A9B6B54D7F4A09ULL, 0x6D8B1AC7A70F5459ULL
        },
        {
            0xC2446FA9A95C2F0CULL, 0x3C3F0546DE4D1D97ULL, 0x66CC5BF27A0111ADULL, 0xCD002E166E18583AULL, 
            0x1DCE5B77BE6E7C22ULL, 0xDFFF22D164A7E9BDULL, 0xB605A50CE4809A65ULL, 0xBC1075E413695535ULL, 
            0xB578EF2247E24D78ULL, 0x3E8A23061CC93C2CULL, 0x6784976702056379ULL, 0xA75062801A5598F1ULL, 
            0x0C27EB200CFC57F8ULL, 0xC86939BD1695BC55ULL, 0x84D89780BED8873BULL, 0x8C368A032AE9D5D1ULL, 
            0x0F46C6A3195CE7FBULL, 0x81C775CC402B92CEULL, 0xCB58C6AE4892244BULL, 0x583323690A381980ULL, 
            0xEC3152D1F6E5D31EULL, 0x50193D5890B5CAA9ULL, 0x23CB9F4E21E52444ULL, 0x85C88C16695F886BULL, 
            0xC2E26D0243489D77ULL, 0x025E9C56CB89B34DULL, 0xA8D897EF9D58417DULL, 0xECFF977A7DA49954ULL, 
            0xE33BAB16B006F361ULL, 0x2DA301D1518486C6ULL, 0x5CCF3C8C37796635ULL, 0x037193489AB1C4C6ULL
        }
    },
    {
        {
            0x23E17DBCD1DD8331ULL, 0xA7F19E919D60BBC3ULL, 0xF13B77C9B04A8135ULL, 0x3437C9486260F7D7ULL, 
            0xAB1CFA6B910F8B09ULL, 0x26C201098DE3BD49ULL, 0xF6AEB0AD43C47105ULL, 0xF6419E7A39235EBCULL, 
            0xD8AC6E81F61339FDULL, 0xBA675CA5077E8DE9ULL, 0x44FD0AB2F06A81B7ULL, 0x23081683FE7D98DFULL, 
            0xD0A024BDF012E02BULL, 0xCAC545AE6B3AC858ULL, 0xD62EFF7B90446D7BULL, 0xDC9404DE63E0A5E1ULL, 
            0x2B3527D885C4B7DAULL, 0x7D6A52EC95B5654FULL, 0x99F3A396F70B68E5ULL, 0xF8C6F4E153ED78CEULL, 
            0x67EDDF2330C23760ULL, 0x8A55B1BA8AEC5F7FULL, 0xB73084A089215422ULL, 0x466A48517DB40F78ULL, 
            0xDF8DFAA589C3E925ULL, 0x0A7E0FC25CFBAD0EULL, 0xFD040D59A2C03BB4ULL, 0x623EE0D7098C5E3FULL, 
            0x3B94E610107D269EULL, 0xBE55662A5A33DEACULL, 0x5517AECB7374BE12ULL, 0xBF1B7FF035D6DA25ULL
        },
        {
            0x01E24DF0488D5A16ULL, 0x80979F1D41F02E12ULL, 0xE5945904C27CAF9AULL, 0x9AA204D72963475BULL, 
            0x274C01AFDB04FD06ULL, 0x0FDD7DF7FEA55B56ULL, 0x10FC5928D8A907E5ULL, 0x923A33332239EC93ULL, 
            0x788AAA73023A9189ULL, 0x189EABAC20CA2527ULL, 0xE7FDD87E269C8A08ULL, 0xC703EFECE1961592ULL, 
            0x8DE01CCB60FD89D7ULL, 0xF06D7DCF7A300A1DULL, 0xD1324B3F7FA5537EULL, 0x6C4712AED64971C4ULL, 
            0x734FEC1E0E23D9CDULL, 0x03DDB7F16087DB03ULL, 0x48E70A69EF59CAA7ULL, 0xC1B6D3DC7BD1F43BULL, 
            0x7EAE82286D349729ULL, 0xB13DB3A478D25C15ULL, 0x3F89FC0225E36185ULL, 0x0ED4AB36D700321AULL, 
            0x1E0D33F076A3F42AULL, 0x8D05E53AC73748BFULL, 0x4AC25A8C30EBD0C9ULL, 0x29AD1CB5FE140A98ULL, 
            0x4BDF268239A94ADAULL, 0xFB8F4A55E9489CAAULL, 0x858B9DB3E06AC78EULL, 0x4D239B2A4B5ABD21ULL
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
            0xEF7C2FBB3AC7536AULL, 0xD7EB6834BEE25230ULL, 0x31B65A31268B8F0DULL, 0x091C8C76057A162AULL, 
            0x846D8C310976FF17ULL, 0x9CFC708C57F0F86CULL, 0x215A786794E4546EULL, 0x76A0F6C4E8C33D4AULL, 
            0xEBEE029E1660A61CULL, 0x8B090C2A884D1332ULL, 0x6AF2BCC56C57A4CEULL, 0x3C3F4B04A753B458ULL, 
            0x6FACD27124AAB37FULL, 0x6584B171855A1D92ULL, 0x93E4F3FDF56CE276ULL, 0x4D63675368D1D720ULL, 
            0x594DB8CA23079311ULL, 0xADE33C7C64DB3E55ULL, 0x456A814F46858004ULL, 0x9F11A29FA80BB3ABULL, 
            0x5779CEB393436C30ULL, 0x7637394DD603C9A6ULL, 0xEEB457262D2DC457ULL, 0x352CACAAD5033B69ULL, 
            0xBA0ABA6FF42E6356ULL, 0x13F737CC2B3666B9ULL, 0x84668DDCEFF413D0ULL, 0x793F0F4E5F032873ULL, 
            0xE9836CEB5DABD7ADULL, 0x498ACC057C76235EULL, 0x5EFE2C0015A34E65ULL, 0x13499FA9B10ABC63ULL
        },
        {
            0x96D3CBEC920E5A0CULL, 0x77A310F602EC7FCAULL, 0x92911A575873149CULL, 0xD1429B7EF4D194F9ULL, 
            0x75652CB8D7793ABAULL, 0xB1453C205D5259E8ULL, 0x552DD188C6B5EDF8ULL, 0xAA5BA69B6734EBB9ULL, 
            0x05ED00B861F1316AULL, 0x19F0B473F92133F6ULL, 0xB9DB688905A2AF7BULL, 0x5BF3DE28682484DFULL, 
            0x1A54CEBB8B637F15ULL, 0x9E10E4BE1714CA48ULL, 0x560E47A848F5DDCFULL, 0x082BC0C6DE4CBD0DULL, 
            0x42E0DBDFC3C24FBDULL, 0x293B15179F9A096DULL, 0x3F4F75C62496D3F8ULL, 0x763B7EC73CA0ECFBULL, 
            0xEE6EAF80E4A05FECULL, 0x7BFBAECA12FFCA9BULL, 0x49A57B561A124034ULL, 0x09E410333A9BB17FULL, 
            0xCC3F329082819B37ULL, 0x2C1970430AC61F49ULL, 0x2C4DBB407266CC7DULL, 0xFEA4AE0B52612B13ULL, 
            0x696D47B7A11734CBULL, 0x736D086E3296B5B6ULL, 0x9425012BD2D7BC70ULL, 0x2773D1343ACEA1FAULL
        },
        {
            0x05A7F3C5B9574808ULL, 0x368C5BD565BA7354ULL, 0xA21BDBE23B784113ULL, 0xA4E423728E230DFFULL, 
            0x238B3D0BDC7E9AC9ULL, 0xB96057D5267D7B93ULL, 0x7032D8AACE788755ULL, 0x3FF9F362604F06BDULL, 
            0x5E2F4E22757BEA5DULL, 0x408636FE6E5ECC95ULL, 0x8678ABF2060EECE7ULL, 0xDE5F09E1735B4C37ULL, 
            0x75E194BDC91CD57EULL, 0xBBD186E733756781ULL, 0x088C1DD66FDB7A10ULL, 0xABECDDC4EC96B2A1ULL, 
            0x2571ADFFC77376F7ULL, 0x3763D9EDBB82110CULL, 0x88B26791F349DEE0ULL, 0x590AEDFBDE18DAB4ULL, 
            0x7E2673E525A1A906ULL, 0x9FD2AFCF2DE08578ULL, 0x49D6DD640DD1CBF5ULL, 0x12544EDFCC48D6A4ULL, 
            0x612D059DA2478922ULL, 0xE2E7B02ED81F6D54ULL, 0x69ADC3F99C0AF47BULL, 0x80460D7E945F55C4ULL, 
            0x7EA2C95311086B6EULL, 0xBE58EB9DCE21BB06ULL, 0xA73AA9879DA50B07ULL, 0x46EE0D2BE193BC4FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseAConstants = {
    0x7CED3F9967BBFCF7ULL,
    0x92F9791F90B46AF4ULL,
    0xA42F524D76C40F8FULL,
    0x7CED3F9967BBFCF7ULL,
    0x92F9791F90B46AF4ULL,
    0xA42F524D76C40F8FULL,
    0xF7CD9B140483E740ULL,
    0xFA4F4E70400453ADULL,
    0x72,
    0x19,
    0x82,
    0xC7,
    0xFF,
    0x41,
    0xF3,
    0x49
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseBSalts = {
    {
        {
            0x0A0DAAD04E0B9349ULL, 0x9E5F386AAD29F33CULL, 0xA855394660AF3278ULL, 0x8129FD0D9EA9CE22ULL, 
            0x582C351FF45B88ADULL, 0xE547E1DBF39A5656ULL, 0xD69CB7E5D4C25291ULL, 0x41D5469A8928547FULL, 
            0x6F362003DC249725ULL, 0x8D20C467C9B23FE0ULL, 0xF6F9B43A16FDCFABULL, 0x8EEF335623F409DDULL, 
            0xE23B33DB3397DBE5ULL, 0x5EA08D0DD7D423D3ULL, 0x4AB178AD8AE75121ULL, 0xA12E6B2EC5947B03ULL, 
            0x28F0ED70DE32FBC7ULL, 0x81EAD8298C6721D0ULL, 0x8B69CAB237CC7FE2ULL, 0xBA84861DA1DD775CULL, 
            0xC18C214185A3A4E9ULL, 0xD67FE87ED57D8809ULL, 0x47F811331A885072ULL, 0x0E9E24276124C898ULL, 
            0xC2387FDB58B4FF93ULL, 0xD307A92D5A1F1C22ULL, 0xA6EADB1A123833B4ULL, 0xD31D3D8152D96517ULL, 
            0x762E8273D113B6ECULL, 0x2C67005036CDF564ULL, 0x70570393A31BD295ULL, 0x8D6CA9B415C8367EULL
        },
        {
            0xC68D91AFEAD91B5CULL, 0xD85C51F20DDDA710ULL, 0x55523F9E48413ECEULL, 0x7312DEF33A42846CULL, 
            0xDE09E49A1CCD0A03ULL, 0xFDDE79F2E75EE98CULL, 0x91786062A0BA2FD9ULL, 0x782A24C768C91577ULL, 
            0xD4EE9DFE121A6364ULL, 0x3FEB07A60EC5787AULL, 0xA17077373170A387ULL, 0x7B3D1952FEB61494ULL, 
            0xC77E6C5145B3C68AULL, 0x54056DDFA841E026ULL, 0x4FD4B963089501E6ULL, 0xC018EA0AFA6DF555ULL, 
            0xBF743CCC6165ED6FULL, 0x5EBA2108286B5E57ULL, 0x38D6A695B6A459DEULL, 0xAF8E099D381B9958ULL, 
            0xBD5EFE41D1DA5F9CULL, 0x7EA350312429DD2EULL, 0x721B6BF806514145ULL, 0x0AD323453C018862ULL, 
            0xBE3AC8848B0BBDB5ULL, 0x21741DAF9E2EBE64ULL, 0xDD90E603A9BC540AULL, 0x92554B08440A29A1ULL, 
            0xD4D72F19FA8105CCULL, 0x85B178D82C96F63DULL, 0x3071AA0E2BC8090FULL, 0xC6AEE81B89A31501ULL
        },
        {
            0x7FE2FFB8B6EF2FFFULL, 0x78615E3E7F02C4E8ULL, 0x096437F4A0F9ECEAULL, 0x06D55137F565C263ULL, 
            0x5B0C7EAD7F8E2BFCULL, 0x60C506D05595ECE6ULL, 0x0E38C32B4C7D66C3ULL, 0xE3A3407A1C49CFAEULL, 
            0xF7EC1CC5B82F95C5ULL, 0x55FFF48E3E9C7160ULL, 0x46FB2A475B777DF2ULL, 0xBC4BD71ED54F06E1ULL, 
            0x3CB86EC0E7EF4D8BULL, 0xF294397FD936E0C1ULL, 0x391CC0106CE5C29DULL, 0x37567FC29DC7124BULL, 
            0xF90EB95757262440ULL, 0x1DA077A3802CDDD1ULL, 0x0065502BF2862D0BULL, 0x5A29087533E3DCBEULL, 
            0x72F853B41FA82988ULL, 0xC8AD807FCA54669EULL, 0x352A2093800A4900ULL, 0xBA2AC9ECE7F89CE5ULL, 
            0x1D7A9F880FAD7D1CULL, 0x4DB0C8FF9BD5EC8AULL, 0x78921ADBF95D0FB7ULL, 0xCD0C8CE06FBDC3FFULL, 
            0x48B864F574834070ULL, 0xD99E5B7A99DC4818ULL, 0xD747F7013C4E3069ULL, 0x32047397DBC238CFULL
        },
        {
            0x3DB066CB3F893A3FULL, 0xA3B7B6C004AA1EC1ULL, 0x7F062490918BFF9EULL, 0x411E2C1FE717E547ULL, 
            0x3F333FE51F5CCF44ULL, 0xC7EE06307F6E358BULL, 0xA446A7BB3016B30DULL, 0x83EBCE60FA4D2118ULL, 
            0x02818A72D0DC5E3AULL, 0x79AA4D08145C96A4ULL, 0x31C12C6517FE450AULL, 0x0D2D818421F3BE3DULL, 
            0x8E4E85557A219E08ULL, 0x331B952821F2EA14ULL, 0x62A7295D13E79698ULL, 0xF1682CDEEB5755E2ULL, 
            0x68C6161BA3CFB096ULL, 0xF69CC4DEFC8C2A4EULL, 0x3135E1874991CF75ULL, 0x6982C50924079782ULL, 
            0x2268D99EC29E1B2CULL, 0xF6896379D2B0CBD0ULL, 0x30F2A37EDD4B0C99ULL, 0xB616B3D171B7F834ULL, 
            0xA99FC45E6DE46EE2ULL, 0xC60A04406FB0B4D6ULL, 0xAF37F428E18D5E83ULL, 0x90E1EE1ED0466607ULL, 
            0xC562C4D9DD6E14B0ULL, 0x0A820CF6CCB4D6EFULL, 0xDEF848B8612D3D7BULL, 0xDFED1ADB863AAF03ULL
        },
        {
            0x05042E23A8FFE031ULL, 0xF4679F127E403E96ULL, 0xDE1ACED9408F3E7CULL, 0x8E4BAFA6C4326885ULL, 
            0x2B7C624AF7DED3A9ULL, 0xFF6CB72750001FECULL, 0x7E78759C6249697EULL, 0x281E8A0E582F5B5BULL, 
            0x8E44803F7520C594ULL, 0x37769E5AF39C929EULL, 0x013BA5250456375FULL, 0x972110C037E9D26CULL, 
            0x99114145407BDBD7ULL, 0xB7D02C04ED5A1BC6ULL, 0x94B460BC7B4B44E6ULL, 0x11BFB15F731C5EB7ULL, 
            0xD392A37BCE97E291ULL, 0x0E3EF3CCCA18D64CULL, 0x18C471CF6F1A6194ULL, 0x88673AA36A96B749ULL, 
            0x3807D01A39B91A42ULL, 0xF2ACA5057F7BD9BEULL, 0x46FEBFEB5794CC9AULL, 0xF1EB4A407D59BF7AULL, 
            0xF5B010C52EEDFAA6ULL, 0x66B70F0D79791397ULL, 0xEB5A9D269C25134CULL, 0xFDCE34E83F5BC950ULL, 
            0x6D421688D46DEDB2ULL, 0x0D48E0157E8A4802ULL, 0x42BD63CE387A1166ULL, 0x50F94BD7185B1EDAULL
        },
        {
            0xC186320C6738E827ULL, 0x8854D4138895A5C9ULL, 0xFF1617CB4B70AD3DULL, 0xC70E0C41E2701B1CULL, 
            0xC1834D73E0AA8320ULL, 0x6D4767E931C22D6AULL, 0xA5CE1C6B2B798E48ULL, 0x1901ECCDA71BFCD4ULL, 
            0x70D8C12FB06E57FCULL, 0x769ECA58C4651B17ULL, 0xE19C7408AD09CA97ULL, 0x2894F1F53124DBCAULL, 
            0x55CF49290E1B9050ULL, 0x0701B0FCDC40D9D8ULL, 0x51134B4B1B6AE85CULL, 0x7BD2971C3E032743ULL, 
            0x9FD2484A1BD136CFULL, 0x080D9FF4AF86E106ULL, 0xB56FF6DF396C0A29ULL, 0xEF4270905653BFCDULL, 
            0x1D0543F9675300C9ULL, 0x1FC2602A4DADF6D2ULL, 0xFD6EE60C6F5D539EULL, 0x729C993C51B6AECFULL, 
            0x205CB21244B74D27ULL, 0x4DD294CAF5478066ULL, 0x88D9CDA7B602D881ULL, 0x220922792AC4FFD8ULL, 
            0xCEE1FC872A534BB6ULL, 0xA8E4BFEA70D8F3A6ULL, 0x10BDC9DE85967A94ULL, 0xBD89B1B19E429A9FULL
        }
    },
    {
        {
            0xECEFF997D6EC5758ULL, 0x09BC2F6A9D3BDA18ULL, 0xD7B648614534F738ULL, 0x00039736F46D4A3FULL, 
            0x6762713302003AC4ULL, 0xBBD7CCE277E41A88ULL, 0xB49886836CFE3F0AULL, 0xA3BE881271DE8CF3ULL, 
            0x52FB490C87C291F5ULL, 0x0074641FD71CF9E6ULL, 0xAA687EC5E26A600CULL, 0xD77433FE4CAB84FAULL, 
            0xC21C241CA29279D8ULL, 0x67786709F647E21FULL, 0xA7A37D6DB4351C9AULL, 0x8B7D784CFC7407F8ULL, 
            0x1021A2BEC9292F90ULL, 0x33CC131A12025F55ULL, 0xE00DB4E575A9885EULL, 0xC6E4B0959C621D08ULL, 
            0x185AE277B7FB9644ULL, 0x5D83B5DB78939922ULL, 0x6230765575830AE8ULL, 0xF2C24D0C75EDD8B8ULL, 
            0xC4F91B7CB28CF99DULL, 0x4EEEB90D3050A433ULL, 0x454D64EE671DDEF2ULL, 0x5EFF315AD75EEA0FULL, 
            0x696C4BA0C824A0C5ULL, 0xE4C716C5F455BA40ULL, 0x01AC806837B5EFE1ULL, 0x144FCCB8936D629EULL
        },
        {
            0x9555E1253DBAB550ULL, 0xE470A3857A5091AEULL, 0xCA640B68A6BDC096ULL, 0x8761990D8E67D5D4ULL, 
            0x21C11841F02A311CULL, 0xAA2986B28C407861ULL, 0x248137CE7C8F1BCEULL, 0x283E4C81F23FE4E7ULL, 
            0xDF00CF1100C91BBAULL, 0x6936FB8738F16FA0ULL, 0x507FD18E7407CF0AULL, 0x97B4679B00F82641ULL, 
            0xCE0544BA2F3F42F5ULL, 0x0343B28C1D35C6CBULL, 0x998E31BA0513FD41ULL, 0x60DC8B6DFF5707C0ULL, 
            0x27CF6BDF9BDBCD90ULL, 0x4C630B81035F973FULL, 0xB11741A614E7232EULL, 0xA79191AF9FC7162CULL, 
            0x3A0B7946122EB0E7ULL, 0xBABA84C19BC02CC8ULL, 0xEDF6514928312A9AULL, 0xDFCA0B234BB13848ULL, 
            0x0B03A521B4B5FFF8ULL, 0x11A023381F0D53E4ULL, 0x487E93E5D2D312E5ULL, 0xA5A42AA07635375BULL, 
            0xD13091E8D7CC20BFULL, 0x39AB1845DDC1F64FULL, 0x873C9D1525B468F1ULL, 0xD4D1F9624E42FC6DULL
        },
        {
            0x2D09F2E44D8083B0ULL, 0x63E08560959621D8ULL, 0xDB9D027E8D3ECCA8ULL, 0x992CE77C3184ADB6ULL, 
            0x7C2A61A5F326302AULL, 0xE48EBC270F47AB03ULL, 0x9523A0961DE5F67CULL, 0xD8B41E0226F82D7AULL, 
            0x5699F2FD8873C9D4ULL, 0xC49EC9F206BA3857ULL, 0x21B5BBB18190FE51ULL, 0x419BFDC86F934073ULL, 
            0x38A8441514C17BFBULL, 0x41AB74101557F855ULL, 0x710CC5605A1B0E62ULL, 0x23A982A55B6EDC91ULL, 
            0xDBD5FBF02FF59057ULL, 0x0DCFB1332F40EB53ULL, 0xC154A2C884986180ULL, 0xCDE878656BEC073DULL, 
            0xEF1440C049B6A3C3ULL, 0xCED3D1733AB70AAEULL, 0x6456ED449DAF6EF0ULL, 0xDFD6B33B7820ED6FULL, 
            0xDF880A5EAA758E53ULL, 0x578377F42025E1EBULL, 0x6EE2416780FA49CFULL, 0x27C17471F5FF24B5ULL, 
            0xB7DB25597D2D27D6ULL, 0x55C291633265671EULL, 0x769FCED841B70D56ULL, 0x4FBC59216B62DA73ULL
        },
        {
            0x93A1DC03A66BC6ADULL, 0x808DF5D83A7D5B84ULL, 0xC5B41DA73046823BULL, 0xA3FDC4A3308F117CULL, 
            0x90AF200E740FD400ULL, 0xE8AC224349F6844AULL, 0xD7D6E88FE0BC64A8ULL, 0x0716C8CE103585C8ULL, 
            0xD681EDA49D88AE89ULL, 0x9384A5B3D39FDDF9ULL, 0xCEF0834AA470F00DULL, 0x39C7B35C6C28426AULL, 
            0x6679169FF9132826ULL, 0x87C8344C7925C8B8ULL, 0xADDA4C355C7193AAULL, 0x5EAA7C359C35C0E4ULL, 
            0xFF175B69DEE42ED8ULL, 0xF6894DED64B96865ULL, 0xFDAB73104D72F618ULL, 0x9A91102E85D6D535ULL, 
            0x6EC8D64A2C9E391EULL, 0x83E438DDCFC08D3FULL, 0x86C95AB84E969AB3ULL, 0x5E2FF3DEA4E1261AULL, 
            0x35D0DC0263FD5BEAULL, 0x05825738838BF6AEULL, 0xBBEE2AA05CB5F622ULL, 0xB4C5484589D32E18ULL, 
            0x625EA498AAAF20F5ULL, 0xA157609F26CE6B2DULL, 0x76CE0A27F493CB6BULL, 0x4CBF4BB7C9C93A0CULL
        },
        {
            0x67D845358E78FFDBULL, 0xBBA81377491FF773ULL, 0xB2C81338D3B70623ULL, 0x14DB1D6BDA69BF11ULL, 
            0xEB9CAD403C367983ULL, 0x67D579054123A769ULL, 0x80D66703E7AE3F32ULL, 0x31F0739DF83EDCF0ULL, 
            0x0DBAD50744DB7ABFULL, 0x1609B8D30409A869ULL, 0x5693F3E72BC91FB1ULL, 0x64737882497B7672ULL, 
            0x675236E8E73B3A63ULL, 0x462266C6AB6A5222ULL, 0x7D41CE1C0BAE89A5ULL, 0xAC4063B7B571053FULL, 
            0xF88A2BD29F2D7C5EULL, 0xFBB77A9B4AEBCEB1ULL, 0x7FF61F71612A6B49ULL, 0xBF29FE46BD347E34ULL, 
            0xC995431A6A8DC5C2ULL, 0xB72ECA03B7CB7919ULL, 0x79BA0C8C8D386B7AULL, 0xFA5A10966B361CABULL, 
            0x0593DEDC09EED506ULL, 0x6ED98EF1051FE591ULL, 0x1A94D20881791E92ULL, 0xDF5FEFCAF21FA567ULL, 
            0x12590177D8B17FE0ULL, 0x3E70E67BECBDF36BULL, 0x61B9FDC01DBB3189ULL, 0x23B5D6C2E1A77ED2ULL
        },
        {
            0xF73584E1B0A7A2DDULL, 0x0FC526A25DA5D1CEULL, 0x711FBD215B533C47ULL, 0x46EBC63A7309D953ULL, 
            0x405E6686BE739F69ULL, 0x64DF0DBE09A44EEDULL, 0xDD6E50194F2411AFULL, 0x8537C04ACE1E48C0ULL, 
            0xBB16519346DAE940ULL, 0x9A6EC250C4561918ULL, 0xD680FF38A8020F36ULL, 0x673D48DEA4784E10ULL, 
            0x46C9935F1863CDEBULL, 0x4B9D40BFD0E2544EULL, 0xC5DD00D1BB6CA937ULL, 0x3DCA29F347A61DD5ULL, 
            0xB8EA85E8C5C7A74BULL, 0xF8B3B7F5FF3E4BB6ULL, 0x21249AEE60116C1EULL, 0x5D01821C0CE08D0CULL, 
            0x7ABDE397F0E437E5ULL, 0x65EBDF10294800C6ULL, 0x48862D6E5C7B172CULL, 0xFE22693151AB6B52ULL, 
            0xDB5AE9483B4DEFF1ULL, 0x512FF51C3275FBCFULL, 0xDF1E5AA89E33BF48ULL, 0x6EBDD482CAF36551ULL, 
            0x13DD7FF2552A2B8FULL, 0xE7D373F6D1A09FBEULL, 0x4E5F85AD86D498F0ULL, 0x263FBCB1E5F60DD7ULL
        }
    },
    {
        {
            0x9FAD33EC73EE38F7ULL, 0x8CC78173A2149465ULL, 0x8FE230EF2E4C9627ULL, 0x3EF2601F8201BDC9ULL, 
            0x0C28756B1C23DBE9ULL, 0x1107E865F5EEBDFAULL, 0x4FE2DF70CF57ABAAULL, 0xEDDD5E77A7496F7DULL, 
            0x64AD6B40D39DC457ULL, 0xB54097036CE56633ULL, 0x8613480B3329137DULL, 0x6B3B364216F5EB87ULL, 
            0x4A0CF7B6086F3415ULL, 0xA2B4788D7791908DULL, 0x9E3510CAD6F126C4ULL, 0x264007B179193106ULL, 
            0x355AE685C8CEF165ULL, 0xFF6EC8BEE088EC89ULL, 0x8B22481CD3578C4EULL, 0x2F82949349EBDC29ULL, 
            0x0743135B62161CD5ULL, 0x1230893C0911FC68ULL, 0xC57E2F8FCF8F8E7AULL, 0x47B46560014CEA42ULL, 
            0xDD84ED6A8B090ADFULL, 0xA02BF707CD7109E4ULL, 0xD3609CAA6854CAA9ULL, 0x253457FB979CB2FEULL, 
            0x02F9008C86E6A6D0ULL, 0xC1099C0005D456D4ULL, 0xC3D306A29C6F71B2ULL, 0x0EB4713C19D71B31ULL
        },
        {
            0xB5403E9E2523DDEBULL, 0x52427640B81C76C7ULL, 0x0914B0F996C504ADULL, 0xC1ECF87D0973C1E5ULL, 
            0x330AF400357D55CEULL, 0xCD618CC27501E940ULL, 0x3818048919A19F6FULL, 0x6EB1706D28E15080ULL, 
            0x7007344232F0FB6BULL, 0xEB814ABFCC4EA900ULL, 0xF7330A74EC722AD6ULL, 0x5DFED80D5CF2426AULL, 
            0xEC38552F94EBAB42ULL, 0xEEEC99C6E301921DULL, 0xAB60A05D96092B5FULL, 0xDADD2886B78AE973ULL, 
            0xF47F5E843FFF4626ULL, 0x741E2FF2B87DD07CULL, 0xA2F8019C3FF15C87ULL, 0xD7CA8F8082824F74ULL, 
            0x4D0A576EF9DF5293ULL, 0x54585E5A11340A30ULL, 0x4FE70E9ED0F472ECULL, 0xFB25A403E5B703C2ULL, 
            0x9AF2CF11AA20F223ULL, 0xC74C32A289B3D3D6ULL, 0xDC5CFC597F0C2B73ULL, 0xB70A884740382A31ULL, 
            0xDAE0AB47E4E32D7EULL, 0x8A197C4FBD275F70ULL, 0x6E8DB727FEF1D922ULL, 0xB352C861F0E9905CULL
        },
        {
            0xDB417650713CD8C3ULL, 0x73E5BF2D212ACCD5ULL, 0x89B7BD423B14F52FULL, 0x0654F0D7CD68542DULL, 
            0x2577E7DF43EC91CFULL, 0xDBB05E6D963BAE8AULL, 0x5C893FAEBA584960ULL, 0xED7909CBF10E7B2CULL, 
            0x52FB735AF9702AD6ULL, 0x7F4440B1AA0998FAULL, 0x77AA7AAAFFA257C7ULL, 0xBE32EA8F6271CFA7ULL, 
            0xC9C9B645064B71ACULL, 0x3307B5B658A6E860ULL, 0xAFA7C1F3A05D952EULL, 0x4968A97515B02CD0ULL, 
            0xC05F974D0E5DB524ULL, 0x2E681B372632A0C2ULL, 0xB673491D6C613CCCULL, 0xF4CB931B61ECE598ULL, 
            0xF39C215C77483491ULL, 0xDE138D197C134906ULL, 0x4A755D02627142DEULL, 0x9130F1C3C5F14346ULL, 
            0xE481DA490CE25D68ULL, 0xC9DCC8A230BB6B31ULL, 0x29F4B4DD6BBD9E10ULL, 0xB8E8C6BE889EAF7FULL, 
            0x47D72AF5A33835AEULL, 0x71FC1EB6B640E7F6ULL, 0xC26F9C203DDA10A8ULL, 0x878CA0F58AB9B9EDULL
        },
        {
            0xD496B7265C3AF463ULL, 0x4E1B4C7B0658AE36ULL, 0xD7D1DCA92D9356FCULL, 0x63834D811FB018AFULL, 
            0x39433FD7D27FD375ULL, 0x6FBC26D4083D3208ULL, 0xDE951DF1568C0193ULL, 0x92BBEDA74C96AA10ULL, 
            0xDFEB189B0BFD8D4BULL, 0xD0688ECFA3EC0A11ULL, 0x2B3002211984226EULL, 0x4024EFA10F47597AULL, 
            0x332D921779389308ULL, 0xAC56B2899802923DULL, 0xE7C311FA251DCFCDULL, 0xFA059383E841CB25ULL, 
            0xC58F66F7DC878C9AULL, 0x57401C0ED9D3D5B2ULL, 0x7C1292201DDB8DF4ULL, 0x1E3E171982364873ULL, 
            0x285BFD9386393A4DULL, 0x00258DF340F3B5F6ULL, 0x33F078CA4D3CA29BULL, 0xB7396A819AD672CBULL, 
            0xA19F8ABB8A1360C2ULL, 0x40DB301CC8CFEF2DULL, 0x2D15009DAB265501ULL, 0x229B56900D9D779DULL, 
            0x340FB9FB78CE67C2ULL, 0x93A54F26C757C668ULL, 0xDC69DF4B1EE07F4CULL, 0xF0D6D8189449BB82ULL
        },
        {
            0xBE0DE4EA1BB40602ULL, 0x2ECFCF2F9D09B841ULL, 0x04E227F6685161B4ULL, 0x4599D6386562AAA7ULL, 
            0xA5CBE70C0BEA787EULL, 0x4D199FB6B683A1CBULL, 0xEDC2C8BF188D2108ULL, 0xC6783B43D1C7D958ULL, 
            0x6C1F0DCB116910E4ULL, 0x3761808C0686F36CULL, 0x31B2BD7B2FF93776ULL, 0x2FD727FF6957346DULL, 
            0x56E4A9A7F68549E0ULL, 0x6EA7CD937CCF1D2AULL, 0x9328580AB0A69FB3ULL, 0xA902CEA87E8F0114ULL, 
            0xF5265ECC7697B718ULL, 0xC4EF9B75A659A211ULL, 0x860234C42FE0360CULL, 0x6E5938C67E433468ULL, 
            0xBE4FC67E31F8C531ULL, 0x56446C8351F46B8EULL, 0x780D6B8EC9DD5999ULL, 0xB869D1799CDC92BAULL, 
            0x8B088C239535715BULL, 0x3239A174003B7BB1ULL, 0xA1E044D676F5C1CCULL, 0xB3BB2C41B1F192D1ULL, 
            0xB7E402C623EB94BFULL, 0xF85AD377262D1509ULL, 0x3554B232DF87E13CULL, 0x168C4F3A408A79A0ULL
        },
        {
            0x06B47BBB4A0D7F12ULL, 0x27B42B392FDF0967ULL, 0xA1AF67590AA4F07EULL, 0x80D730069F613373ULL, 
            0x6574ECFD392F868AULL, 0x279DC1DEEE7CB7B1ULL, 0xE2E1623A7DA00A1AULL, 0xF48C463563C1A9B5ULL, 
            0x26E94037799CC283ULL, 0xB6A2E800BE559DC6ULL, 0xD27556E3717AFB7DULL, 0xE020FB73FE2E1B6FULL, 
            0x23A0C6405274FB1EULL, 0x480CBB23C0DC1DF5ULL, 0x0173F1E4D1C516D1ULL, 0x0FEEC7A6ADD16C89ULL, 
            0xCE5F6F2806FDA54EULL, 0x84E1BEE93576521EULL, 0xE8B13BB940DD804FULL, 0x0C0E3FBE774D5347ULL, 
            0x0DC344DD37A02B5AULL, 0xBA481FA0F31B14BAULL, 0x3523D7D36F783870ULL, 0x900AC0E168E2D324ULL, 
            0x2DBE60652A53EBCBULL, 0xEB1CA7E7A717E00CULL, 0x5B3F08D7FE7EBDD1ULL, 0x6F7A32066F4F3AE9ULL, 
            0x61412EB2852BE43BULL, 0x89753257BB43DE03ULL, 0x8C2D4149C83D6C2BULL, 0x6CADFCF4EC418FC7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseBConstants = {
    0xD7DF9BCBB6492661ULL,
    0x88239E977EE797C8ULL,
    0x0B2022D03C358E38ULL,
    0xD7DF9BCBB6492661ULL,
    0x88239E977EE797C8ULL,
    0x0B2022D03C358E38ULL,
    0xA790D624B00D51C0ULL,
    0x2CBF818719823D96ULL,
    0xA9,
    0xF2,
    0x3D,
    0xC1,
    0xF6,
    0xEA,
    0xA5,
    0xBC
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseCSalts = {
    {
        {
            0xF76D1199B72ECFA6ULL, 0x9AF552742EAE5BCCULL, 0xE98FA0FB68BCB141ULL, 0xDB47BA25A6151B10ULL, 
            0x42EAF2DEB6AFD174ULL, 0x5741E51BB61C5753ULL, 0xDD6B0A60FD103973ULL, 0x5498F6602EEA613CULL, 
            0x4F4D4CFDCB5D30C4ULL, 0xC1402434E831BCDAULL, 0xFC4E113F74AA05A7ULL, 0x9ACC39E646FAC445ULL, 
            0x01A1541E443D8E12ULL, 0xF2E67565F04E2484ULL, 0xC423E3D908EF2E74ULL, 0xFDA6DFCE92DC2ED2ULL, 
            0xD890F80364242823ULL, 0x77BF07CEA972FF68ULL, 0xED99A47F51B5392DULL, 0x2BBE74B68B10F40EULL, 
            0xAC6BE0B9B42ADB90ULL, 0xDA1BF57362BB3D0AULL, 0x3E3239FB50BAC758ULL, 0xAE2D4153566632DDULL, 
            0x25B9064C198264BDULL, 0x2A250A7062D19EB0ULL, 0x0A1B5E9E7ED9C223ULL, 0x4332451644F897FBULL, 
            0xC630E09DF0BD9189ULL, 0x4E5EB0D6F1194656ULL, 0x004D1074D4EB6A05ULL, 0x2258F09E7CCD9A0EULL
        },
        {
            0xF4E6FB6A109C12BBULL, 0x4C78D21ED0B83C13ULL, 0x81518929186F08A2ULL, 0xF25A262DC5194B4BULL, 
            0x169F66A31D8C288CULL, 0x634A086D2175C606ULL, 0x50DC57F0043D3883ULL, 0xFE8D85C124B05DE5ULL, 
            0xD78F6D497EB3620CULL, 0xB28DB3B2315DE246ULL, 0x119FC5509B513B4CULL, 0x8A1158038BD2DBC9ULL, 
            0xC28E774365F50545ULL, 0x74FF367FC6CE8F42ULL, 0xA73C9DA83784B2B7ULL, 0x1C04A9B95AF3CCFFULL, 
            0x7130382480240426ULL, 0x88A1A50386467A95ULL, 0xD0F5FB5E3DC35A2AULL, 0xB97BD07F4D0E5044ULL, 
            0x0B1F137452C09315ULL, 0xCCE36F9F747CB45AULL, 0xB2B95ECDED0EA845ULL, 0x604E9B1D3CF2BA33ULL, 
            0xAFA52F0BB8C3ECD3ULL, 0x755E7B6214A77446ULL, 0x76C1789898B14C05ULL, 0xFBF247BA3A6D0B90ULL, 
            0x9F3FA36EDE28AAE3ULL, 0x847AE0EF6A4A7B19ULL, 0x465505CF32BE941EULL, 0x51C490F12EA78BBAULL
        },
        {
            0xF97F24A0275BCB1FULL, 0xE29D438C5E3B2618ULL, 0x3AF3E69975AAC9FDULL, 0x42BDA333AF571CC8ULL, 
            0xA8BCFA9006ABE152ULL, 0xF82104E6279B53F7ULL, 0x6CA8E8BACE300E0BULL, 0x11BFB3865AF54153ULL, 
            0x1BD54BC1499D2602ULL, 0x3C669EEE0F8BCA90ULL, 0xA780B0E74260D2ACULL, 0x8C17E14560CEAD37ULL, 
            0xC1B8227E63AE4067ULL, 0x7D5C3BB0ACD9DC97ULL, 0xB8E89D4905A36780ULL, 0x9849D057C057936CULL, 
            0x3565D3EFE7D9C75BULL, 0x8903149E60CE0327ULL, 0x161503170AA98271ULL, 0x15F6A09AF83799CEULL, 
            0x82C0AEAD95FC0E20ULL, 0xF03C87B20D6C379DULL, 0x759A2EB51723F75DULL, 0x512B490002E1D4B5ULL, 
            0x11691513EF5900AAULL, 0xAFD0700E911A3789ULL, 0x637771A404E0056EULL, 0x3D5626B793A0F1CBULL, 
            0x92943C54CEF5F67CULL, 0x280A8BAFD270515DULL, 0xFB0ED3E95B373C7FULL, 0x357C4F2D5A189495ULL
        },
        {
            0x821041F429F1D95DULL, 0x090EC06F5405D062ULL, 0xD0A9CDA56FB46A87ULL, 0x58F5263CAEBFEEA0ULL, 
            0xBF16646C6528EBDEULL, 0xBEFCF40C94F9BC6CULL, 0x95A9E0487E55892EULL, 0xC5BC911B9688CD4DULL, 
            0x58A0F2A3DB6C395DULL, 0xEB31C326ED86AACFULL, 0xBC975F7000070DB2ULL, 0x3B5A10ED3533587EULL, 
            0x3DE3BF6A03A81893ULL, 0x5335D34517BB4D56ULL, 0xD967933D533483AEULL, 0xC36FB672A17460FAULL, 
            0xDAD4D7A7C643986FULL, 0xB128749D5147E4ACULL, 0x1343A608127088F4ULL, 0xEAC27568FE3BA1A5ULL, 
            0x188B16A654CC87E0ULL, 0x68258E13F2A56E59ULL, 0x2BE588AA1C3D06E2ULL, 0x507F3A83BF0BF302ULL, 
            0xB61A5AF210A2DB9DULL, 0xFD78441FCDC77E93ULL, 0xCE6D3736553CEB5CULL, 0xB6079BE94297AF8DULL, 
            0xB7516B1805CC75ECULL, 0x35B45E9439174FB7ULL, 0x133E4F762A78CB65ULL, 0xCBC1917EB251C62BULL
        },
        {
            0xC5306DFF8C8F1D06ULL, 0x9CA2C38125D596B9ULL, 0x6839C696EC408B0DULL, 0xC36FCED631A11A1AULL, 
            0xE3FF25D8E18E9297ULL, 0x4BD3692A95764186ULL, 0x12DFDC3A92230503ULL, 0x34D0ABA3A08F0FDEULL, 
            0xFB7EABEFD3368FE7ULL, 0x77FB2009402E5626ULL, 0x0A9349929BE9457DULL, 0x099D2F8933E782E0ULL, 
            0xE9C61BAE429ADF61ULL, 0x029F3B34938FEEF3ULL, 0x57F6CDFB76EE0D18ULL, 0x34FA7B8BB228C3E4ULL, 
            0x9EB7194388F10288ULL, 0xF09D0B895F981C61ULL, 0x1C490D6F1F35AE54ULL, 0x45E97B2E271AD2A2ULL, 
            0xC881E5C0AEA606DDULL, 0x0323CBF29156A184ULL, 0x1993027ABD5E3B30ULL, 0x1A9C0724A1478D09ULL, 
            0x939A37EE48EF4F43ULL, 0x76B021C93E6D404FULL, 0xEB1A225CBAB6E510ULL, 0x3C55A0389609D146ULL, 
            0xDF8A21BD1BFAEAFDULL, 0xE1AFE252CCEAE728ULL, 0xBCA2169865AE859DULL, 0xEB3DBB3A987EC2A0ULL
        },
        {
            0x56E48E0EB09F1164ULL, 0x8FBE908DF621BFBFULL, 0xB9BB1505CFB75873ULL, 0x33D1CD2A2D71D72AULL, 
            0x4A47F504584E3B1AULL, 0x6FC244478B4C4891ULL, 0x5981A6252A89970BULL, 0x4678CF9B3362407DULL, 
            0x81B59CF7CC18D65BULL, 0x0752FB8B1B501A25ULL, 0xE0DFE8E633059671ULL, 0x36BB3938A768CBF2ULL, 
            0x325A06997251A6FFULL, 0xF09C77F7B7B6AE17ULL, 0x68B125C2958054BAULL, 0x6E2B26C875F5F273ULL, 
            0x682A692A871C6E6AULL, 0xE2A00727EA72DA2DULL, 0xA8B06B47EBBBE970ULL, 0x8C7F7BF05EBD8523ULL, 
            0x8BFAC9BDCD54D937ULL, 0x47DF1E4D153FAA8FULL, 0x3C65FB25E718A111ULL, 0x0C6EA39EB8E25390ULL, 
            0x9597EDF6B5F504BDULL, 0xB8395C3DD8967A1FULL, 0x693AB986CAC72293ULL, 0x9BF8DC0F36DA92FFULL, 
            0xEF3A50DE4B4436B2ULL, 0x295461E307B5B33CULL, 0x01AD753B90132949ULL, 0xB714BE0EE907E145ULL
        }
    },
    {
        {
            0x74ABBCC79A231718ULL, 0x7F9F32AF8885B651ULL, 0x5945443DC2DDB9CAULL, 0x738E4D3C4D7655F2ULL, 
            0x4095D2BA788B655FULL, 0x79A412C45F945FCCULL, 0x80DACD7CCAF6C339ULL, 0x8B994A39D44358F1ULL, 
            0xFF875DC4080595B5ULL, 0xECD11645A0D9AB03ULL, 0x8D6475194A022897ULL, 0x71F25FEF79C4C2AEULL, 
            0x44086704E87A234AULL, 0x3969E0CCDA47234FULL, 0x4E4EB6984FFAF60AULL, 0x66BD447225A19A8CULL, 
            0x33E0AB39F11CC81EULL, 0xDC71E7D8ADF8749CULL, 0x17546CFEE1D11A8BULL, 0xAFB86168CA502392ULL, 
            0xB8D860C535229239ULL, 0xD45BCEE78D67B27AULL, 0xCC663FA037132538ULL, 0xD6AB5461D43995EAULL, 
            0x3DA18BC595FB1E1EULL, 0x0220D5F51582EC79ULL, 0xBC012D6ACCC2AB30ULL, 0xBB54655BA209E84EULL, 
            0x3A60C6307C8F91DFULL, 0x9B07B5AB44251276ULL, 0x3CEBE9A8CE890FCFULL, 0x895D3E2F47DB818AULL
        },
        {
            0x4A089F16197CE395ULL, 0x1C07651687A78D17ULL, 0x48A81EFCD0B3E779ULL, 0x91BE32295868449FULL, 
            0x9962798383334538ULL, 0xC76ADBB3AFFABBE5ULL, 0xCC6CB869A25AF47FULL, 0x9A6E0515259BAC81ULL, 
            0x36EC6181458090D6ULL, 0x31C4E6433F52186EULL, 0x0B84836C21834030ULL, 0xEA57E4B208C11AE7ULL, 
            0xBDB57F5D3F8EEB8DULL, 0x1BF5BF7D84376052ULL, 0xC4B41DEA53D6736DULL, 0xF93E27A0E26ACE4FULL, 
            0x32731574CA5646A9ULL, 0x1279C4138BCF2F86ULL, 0xD389EC1523B61E01ULL, 0x9D0C09A1119F23E1ULL, 
            0x4AC28290E803844AULL, 0xCD98CB8CEE2CE0B0ULL, 0x6E7F538E72C55598ULL, 0x43FAB1150C6B0E48ULL, 
            0x021F15A96BCD5431ULL, 0x32AA803CE51AB7DCULL, 0xE5D8022244E80560ULL, 0x97262B7D96F39ABBULL, 
            0x846C239770755C3CULL, 0xBD2BB098253ED751ULL, 0xD4925E859040A0C6ULL, 0x1974EE281A02B5D3ULL
        },
        {
            0xE29C3C232F6D9D00ULL, 0x69CCA03F0042E067ULL, 0x18DE034DD43DA421ULL, 0x25A6A4ADF8A89163ULL, 
            0xBA61476FBBAA9EF7ULL, 0x14067817133D776CULL, 0x7802FCAA675BCC88ULL, 0x2E64753776C4E5C7ULL, 
            0x8AD6FDCC727E04BDULL, 0x9760E5954F0CC8E7ULL, 0x00AE3E85D55766ADULL, 0xB99D1DF6355A3DB7ULL, 
            0x43C33D11823F2592ULL, 0xCFF9D408889B099AULL, 0xA48CD203B97E5FFBULL, 0x551344057BA9031DULL, 
            0xA51FD28BD89366EDULL, 0x8E68B8F0CDD5EAD6ULL, 0x45FF476CE6549FD0ULL, 0x1464C5AE68EA9431ULL, 
            0x2B5529A1D97CC1C3ULL, 0xC563EC89A57C7FBFULL, 0xDA0B09DFB9A5475DULL, 0x3DD22AF57824E20EULL, 
            0x13E58B209A541A41ULL, 0x478D3E9E2F34A9E6ULL, 0x30F9E6F5227EB05CULL, 0x2A2AF908CE319556ULL, 
            0xCBE26D7CA26C75B3ULL, 0x5AE3398F5BDEF862ULL, 0x2D057A71B43C0B1DULL, 0xDFF86278218413B5ULL
        },
        {
            0x9B78918052C3571EULL, 0x547F1B0BC7EB889AULL, 0x6CAB17B8CA231317ULL, 0xE91D62F9DA1C7720ULL, 
            0xF26BF84FF9DD6835ULL, 0x0EA07C7DEA490271ULL, 0x5DA69751D6058F85ULL, 0xE61A56966A8D065EULL, 
            0xEAD7BDC94F0E2046ULL, 0xE857F2953D1305C4ULL, 0x4074AA585D8AFC2EULL, 0xF7F96A2F63357EC4ULL, 
            0x650426B176E76A02ULL, 0xB9E31863437239CFULL, 0xA15911065D5033DDULL, 0xEC643AD3DDC0DDCFULL, 
            0x8CEE19AD0FAA6DA7ULL, 0x0DA6028FC7C79302ULL, 0xB745CD9C027575B5ULL, 0x30A8AE7340BD7EADULL, 
            0xC9C47DA10078B204ULL, 0xF41EE05D07A0C94AULL, 0xACBE4FC48A8077C7ULL, 0x75CF404FE2265FB3ULL, 
            0x136BFAAA3D7E44EEULL, 0x751208141CEA9CFAULL, 0xDF78374AE7F883E8ULL, 0xEDA9B3544C174A51ULL, 
            0xBDAD2B713A0F322EULL, 0x3AFF42FB848E6C99ULL, 0xCF61ACD3D25DC33EULL, 0xC30E4696C9C86955ULL
        },
        {
            0xCB33D6E136E0A4D8ULL, 0xFCC0DD4E476090CBULL, 0x77598279419B4167ULL, 0x659D24CE62557AAEULL, 
            0xC9E04F54D287C0D8ULL, 0x61CA5D7C4157127CULL, 0xD1C5E50B7DE18AD7ULL, 0x66E2956AE1788733ULL, 
            0x80BE1B671B693C1CULL, 0xF022B6AB38FDFC04ULL, 0x2F73B621F2FB8A7BULL, 0xB718DE2787312CA1ULL, 
            0xDB6BD3A59CCE8C3FULL, 0x510DCBB6FF0EF1F6ULL, 0x2467130F656AF3A0ULL, 0x472B895889648F06ULL, 
            0xD62EC87D5611B660ULL, 0xA5235FB733BAD8CCULL, 0xFD4318294DDA718BULL, 0x345295B16A32AA9EULL, 
            0x5F2B7BA970BC8B4DULL, 0xCD54D6339FF65A95ULL, 0xBD838F490551E421ULL, 0xB94DAB1A5F9EB88FULL, 
            0x1D38BD29DE64A580ULL, 0x495D8E1BD2678B76ULL, 0xD6168CC19D74E49DULL, 0x936153B9750C9D26ULL, 
            0x8BB98388D8D97E32ULL, 0x283EE23E7B0D51A6ULL, 0x2B70FA96B31CB8C8ULL, 0xBBCD37638DCAB635ULL
        },
        {
            0xA8D636B35AF7A2ACULL, 0xF842246B4BD0A4B7ULL, 0x10BD4F6B2AA0C126ULL, 0xF7C063B47167B8E4ULL, 
            0x862CE5DE7D1F8B74ULL, 0x95E88D8298C832A9ULL, 0x5A60A6C9546A7372ULL, 0x0759BABD990A3C93ULL, 
            0x02170A5F4868CE5CULL, 0xC2743C556C28F72EULL, 0x218482158C60AE03ULL, 0x1C16EE2102C85006ULL, 
            0x56478D050088D0EDULL, 0x7B0770AEA18859FFULL, 0x199DA399784F4168ULL, 0xF77B4A8747821C82ULL, 
            0x6BC7968C964D9DB0ULL, 0xF8C1501018F6B539ULL, 0x396B8DAE63E1AD5DULL, 0x3280A726D8AC1D74ULL, 
            0xB0E05B2B047EB46BULL, 0x15C710F4F479A8D1ULL, 0x8F9F4BE82DB78EEEULL, 0x8EF270E792423156ULL, 
            0xD37BF3567ED37BAAULL, 0x8C1C6DF1A8DCFDE6ULL, 0xE958C63328938D61ULL, 0xFF63D4EBBEE7CC54ULL, 
            0x419094E74808BEBFULL, 0x23241ED45B5D3274ULL, 0xD473D3B405D90B3BULL, 0x47411F3D67708DF4ULL
        }
    },
    {
        {
            0xDDFBF2BA928D3145ULL, 0x580B511D3EC8FAD0ULL, 0xEA74E36FA478BDA1ULL, 0x4F8F0488C1C7E2A0ULL, 
            0xAE095D66DB0895C7ULL, 0xBEA9D619AD5AA977ULL, 0x2C22490BB372C867ULL, 0x178FF171F6B5025CULL, 
            0x13B524AE5E179EDDULL, 0x47ADF83960D9AB5AULL, 0x1D446D8A96F56A58ULL, 0xB9B41E12683979FDULL, 
            0xE69E72035FB9B597ULL, 0xBA20E35E549854E8ULL, 0x41DB7966B8BDD0C3ULL, 0x8130C74F9C3A68F2ULL, 
            0x97323087AB7BB421ULL, 0xBC0ABC64EF6A129CULL, 0x2257D87B7829013EULL, 0xBFD62D7310ACEF61ULL, 
            0x2C4C6834FB89B2D3ULL, 0xDE22CF53C5633AC3ULL, 0x2C5703973FD02F49ULL, 0xC9DC23CDAAB3C3C1ULL, 
            0x6F15CD404F5F1FBEULL, 0xC06DBB4CD0B7D293ULL, 0x5AFC24E66A2DC7CAULL, 0x402216958BA5E7ABULL, 
            0x3008DF35EE627A5AULL, 0x2BB279DEAB82933EULL, 0x328E51A608EC2644ULL, 0x3B51D93BA4D83D96ULL
        },
        {
            0x813D53015E084816ULL, 0xE3F119F15F466D2EULL, 0xA49191E319C864B5ULL, 0x92DACFA74D3CB46DULL, 
            0x7E6E0F5B0ED84254ULL, 0x7A6AF2565813FF28ULL, 0x47D7829FC9F52A9AULL, 0x96B1C9ED142EAE53ULL, 
            0x236352608C487819ULL, 0x90235E35206CF377ULL, 0x07A1FA0E44058E36ULL, 0xE817F313D568224AULL, 
            0x30FCB227A14D459EULL, 0x09583D351A0E47EAULL, 0x5DB08E948708D8C7ULL, 0x69B845EA96713AD6ULL, 
            0x5C7768E4C8B9C90FULL, 0xFD80BD695F77357FULL, 0xA7BA20F52B922443ULL, 0xB284D482F067146FULL, 
            0x1F9F4B2E8D135816ULL, 0x40490BF7B27A51DAULL, 0x65A35E9E5B51E029ULL, 0x45A2E0C395749334ULL, 
            0x0BC0A56DFD34B8E7ULL, 0x4A751164A5275489ULL, 0x5802165FE195026FULL, 0xE56FB5245C6D604EULL, 
            0xCC595CF0F8A3F727ULL, 0x07AD14D114F041AFULL, 0xCB6D2C254E6F06E1ULL, 0x09004D9944DAB00BULL
        },
        {
            0xEFB40745EED51B9AULL, 0xCEB382D7F167E143ULL, 0xC286AC8DE698B4B8ULL, 0x2B7CA7D7C9695C94ULL, 
            0x43FE5A45D396DAD4ULL, 0x8B2177713FBBD441ULL, 0xF6131FEE99F0A061ULL, 0x677855103FC5D373ULL, 
            0xE0220C74AFBE8235ULL, 0x3D3CA2804FA9390CULL, 0xC4F727658E352C02ULL, 0x435C534CC70839C0ULL, 
            0x058205A47BE6F356ULL, 0x27BE2AD24A8868CAULL, 0x1358AE225E9483E0ULL, 0x63A0F3D7AC9990EFULL, 
            0x23DBACD47152112FULL, 0x8D0F842F427339C0ULL, 0x275EAED20C2E7B1CULL, 0xD994E34AA966E50BULL, 
            0xBD8D7DAF70710668ULL, 0xA82909B7E1F720E9ULL, 0xC5D8289F5710E965ULL, 0xECB460CC70F3DE21ULL, 
            0x43BCFC01AC02614FULL, 0x63D6C0A6C0BF72D2ULL, 0xEF6CD30AC5E06006ULL, 0x38BDE8F21D04AC23ULL, 
            0xEBB72E158AB5B701ULL, 0xB33DABFBBC31BDB7ULL, 0x5AB947BE584B15F6ULL, 0xB0EF796F55DCB6A9ULL
        },
        {
            0xFA7100A92F98F71EULL, 0x78B957B35835563CULL, 0xDE977A23485CC2C5ULL, 0xA8C08EFA4C365760ULL, 
            0x1C2D9C15A89AEEADULL, 0x9921655F23AE15B2ULL, 0x066E5DA1AF6C2B63ULL, 0x365F815F448A3D29ULL, 
            0x1B38479453A3903CULL, 0x658213A0D74D83E9ULL, 0xEF8E549854ED7C46ULL, 0x05DCD2BEAE3F0BD8ULL, 
            0x3DDBCC92B7B364E0ULL, 0xFADCE16035763C32ULL, 0xF5603BD478A60C79ULL, 0x5956AFA2955FA877ULL, 
            0xF2731CFE3A7990A4ULL, 0x88BD97D0A9F2877DULL, 0x24C9DF972CE1292AULL, 0x33ABB6FCACBBA96CULL, 
            0x64B6AA21EFBC91CBULL, 0x36CB02B26A3CDA76ULL, 0xCF9FBCE46F36FF72ULL, 0x51418BDF615B4A8FULL, 
            0xE23F2695D9D8B30CULL, 0xADFBB7C4B379F866ULL, 0xB77AC4406B06BB8EULL, 0x7F49C8BB158D36F5ULL, 
            0x61DF1A6D0F2F6099ULL, 0x747746750D9AD8E8ULL, 0x4792E4964670D949ULL, 0x52E7F3991966D9B4ULL
        },
        {
            0xEF840C8A75EC7D02ULL, 0x802FF80CF70453FBULL, 0x75AAD822E0498EC5ULL, 0x1085FDB2F2BA9FEDULL, 
            0x93F6EC9E75EC37B9ULL, 0x9DBC8326F90A5DC2ULL, 0x3B06E57554CBBD72ULL, 0x778EDDCA24DC11D2ULL, 
            0xE0D9D491504DAD9CULL, 0x25630040467FF612ULL, 0x6E16652E9A2D67A1ULL, 0x3C4517AD1052B44DULL, 
            0xB04A4A45239A35A0ULL, 0x19B7881D43CEECE3ULL, 0xFB071FC31870261BULL, 0xCF9B52752A3CB234ULL, 
            0xCFE8DB7409B9381CULL, 0x6152B691B88BC8A5ULL, 0x16625EE23565F95DULL, 0xD9C4565A955B9C41ULL, 
            0x71FC3238AC46E226ULL, 0x82F0D5E1F865B197ULL, 0x71ADB6663F83633DULL, 0xCD6BBA96EFAC19BDULL, 
            0x7F7DB831F6FC04D1ULL, 0xF54DDDE2CE298EEFULL, 0xA9D2CBB5549DEF02ULL, 0x07C5F3F2D8682B56ULL, 
            0x46C0D57B7B99C8D5ULL, 0x69855470F2F70082ULL, 0x9E320BC21E87CEA7ULL, 0x8F0445B6ACC1E46DULL
        },
        {
            0xA687AAB9877D90FBULL, 0x853FAC610AC99F9BULL, 0x6582A99FFA0C5EA6ULL, 0xDD33A3BC3188A368ULL, 
            0xAF627F8A1EEE8CBAULL, 0xE29EF7E023B9A8E2ULL, 0xA8D6805F2F19198AULL, 0xE85164072AFAEBD2ULL, 
            0x2531179D0D1B3571ULL, 0x7268AF52AC2E058FULL, 0x730E5A2D3556C9E7ULL, 0x86C85D8F7AB74D3AULL, 
            0x2E0139DA143BCBF8ULL, 0x1E10AC92E6A0F909ULL, 0xAB130C2BDDB7AA99ULL, 0xD4CA8CA236187264ULL, 
            0x95E0E41526834DCDULL, 0x18E799D026B950B0ULL, 0x3284C209B229B787ULL, 0xC74A8B6E7F8DAEEAULL, 
            0xD4C3AEDEA75434BAULL, 0x65FE0930D80AE30BULL, 0xFD339643FC3FC090ULL, 0x597FDED27E21CE56ULL, 
            0xBEFD27C03280EA93ULL, 0x3C1FDB42692AC288ULL, 0x48459946070D3212ULL, 0x75D2E385FE19E6C9ULL, 
            0x700575B0FD6B41EEULL, 0x2047126200C5530EULL, 0x1D56600F1205E232ULL, 0x6811171974ECFFFDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseCConstants = {
    0xE32A61CAF40A4839ULL,
    0x6CE961F2408E1B28ULL,
    0x9855451520C6FAECULL,
    0xE32A61CAF40A4839ULL,
    0x6CE961F2408E1B28ULL,
    0x9855451520C6FAECULL,
    0xCB9391A0C452FC3AULL,
    0xF848324731E314A5ULL,
    0x39,
    0xD1,
    0x97,
    0x4A,
    0x32,
    0xB7,
    0x95,
    0x43
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseDSalts = {
    {
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
            0x41F9C59DD2CFCD8BULL, 0xC2985B11F7E00CECULL, 0x2C3FB30505D9064BULL, 0x25E6C99DB8C89CB6ULL, 
            0xFC41F5A9AD9427E0ULL, 0x88EB7B9B735C18A3ULL, 0x13421E1D0E7FEEFAULL, 0x88339DC3302D7759ULL, 
            0x426A7526926E9B8DULL, 0xC0532BF5A2B68FB0ULL, 0x5F29875842C642B3ULL, 0xADD564114270E17EULL, 
            0x942A97C933554D00ULL, 0xE17A81B3E71C8CE1ULL, 0xEEFCC46025AAB880ULL, 0x2E2836B5D92008CDULL, 
            0x3192A4A2491EEE6DULL, 0xAFC3F7F60E266AB4ULL, 0x660204F4E4E7FE25ULL, 0xF63F6614D323D0D9ULL, 
            0x6F018BEB6161D130ULL, 0xD9BBCBEBED5357F4ULL, 0xC813F928E05DE475ULL, 0xB0E36AD104BA3203ULL, 
            0x5402F3067B9AE9BFULL, 0x0EEB2CB1657B91D3ULL, 0x755D768B9560BEBBULL, 0x3CBBB05539B66B45ULL, 
            0xCCD49EDF8A74606FULL, 0xD0B268FB0A16FF61ULL, 0x929F29537C1DCB64ULL, 0x74FAECB772A96956ULL
        },
        {
            0x2F130A56F7953D58ULL, 0xED0FDA8990A372AFULL, 0x595BA0CA885CB4C9ULL, 0xA336053B8B70FBC4ULL, 
            0x0BF0B341CF53CD14ULL, 0x0BC58F7C4AA22EE7ULL, 0x0E004C935F5DBCBDULL, 0x7C5EC15D1E64E37CULL, 
            0x92EC1AAB75231E5EULL, 0x80B94A26A67B7098ULL, 0xB7B3448AB4E2CA24ULL, 0x81773C951B44ECBFULL, 
            0xB841D260C85ABCB4ULL, 0x256FBCFA3FD65823ULL, 0x77D3D6ABD005072EULL, 0x6EFE6207D2EE9EFDULL, 
            0x3B0A7A7D65DAF07AULL, 0x8C7836B894A450D2ULL, 0xB23DF9F32050E3FAULL, 0x21360BA6F72DAB16ULL, 
            0x6A930FC451DD85C3ULL, 0xB58B9158621F95CDULL, 0xB9B9017B4F8C0E67ULL, 0xD8FED769AD83D62AULL, 
            0x7B221DE8A11B7CC1ULL, 0x3F81281FAB8A7177ULL, 0x8FED454A34DBDDD9ULL, 0x73938BDEE6884240ULL, 
            0xD3FA77B5C1724FD5ULL, 0xB514C68CD6C979BDULL, 0x89A4FCC1506EC3A3ULL, 0x58FD91EA0B539B8FULL
        },
        {
            0x4D984B623056F16EULL, 0xBE639B638DB89A5FULL, 0x0AEEDE1574740627ULL, 0x41BF173CDEC009BFULL, 
            0x45363001E07FDAB8ULL, 0x4F4C9A3B02CC043AULL, 0x3A8F3E20C3CBD72FULL, 0xD7FB7D13F45C51ECULL, 
            0xB5DE3EB3EEDF0F90ULL, 0xF250A6AA5DC889BDULL, 0xAD44DD6D755C5C54ULL, 0x69C35F0FE8C5A3E1ULL, 
            0x447DE553F1A92FFAULL, 0x8DAE55A7D20DFF88ULL, 0xA935D4D1EF396CBCULL, 0xE4FA676C2253570DULL, 
            0xD6F64396A68A45D1ULL, 0x623CFE6D4439027DULL, 0x7CF7586769ED7739ULL, 0x7C891C91F4534D34ULL, 
            0x7565DB25125EF1BEULL, 0xBEF8369E7E67BCBEULL, 0x958EA69BF85C5198ULL, 0xABD064828B668EEDULL, 
            0x57AE175129ADB174ULL, 0x891561D7D3D44DB4ULL, 0x10C2A84A07AC3605ULL, 0x62CEEE93DCCB3621ULL, 
            0x98EA568B97290A5EULL, 0x3D21334718ACAB05ULL, 0x576D470D3CF2DCB5ULL, 0x84286CE158B03D0AULL
        },
        {
            0x623BBBBE1565D68FULL, 0xC4AB870D4D6DEB3BULL, 0xE710B7D99690B66BULL, 0x4E427CA156428503ULL, 
            0xE1D1B1FC080A42DDULL, 0xEFE668C6DF34437EULL, 0x5B65C63ACE8BB0C7ULL, 0x591397B63C520443ULL, 
            0x1490E67661F7E9E3ULL, 0xB7A71D2AF10F9D63ULL, 0x611A05BFE9C488B4ULL, 0xCD30919F166BAFBAULL, 
            0x503A06002B3D9B79ULL, 0x4E16A3C16224F496ULL, 0xFD720D2410BBFF0CULL, 0x2CE5028B36D7EF99ULL, 
            0x86FD70329939D19BULL, 0x80B59FCF31E25FDBULL, 0x30FD4E717B072E5DULL, 0xCB2CF02D1798A438ULL, 
            0x2FD00512948197A3ULL, 0xB560E248DCBBEC3CULL, 0x95E3622F3017A2F1ULL, 0x9502DACDA91CEB99ULL, 
            0x678A31FD3F158327ULL, 0x655EAE08A0B99D06ULL, 0x8079C4E09F2FBD4BULL, 0x35F76BBAE6F87EAFULL, 
            0xA7EFB1601D768391ULL, 0x9AB389B446BE0B69ULL, 0x8B106C1DFA1A5624ULL, 0x3477AB98A6668609ULL
        },
        {
            0x2A5314B082D308AEULL, 0x1986511E4E0A8F64ULL, 0xCE41FB9A4D5089EDULL, 0x859AFAB718677A25ULL, 
            0x1B7AAA3279A1AA29ULL, 0x7E7439507712832EULL, 0xDE487FA0828E818EULL, 0xDC1FA0F06C8B279FULL, 
            0x462C9BA08DB852D0ULL, 0x4BCE748CAB548EC2ULL, 0x797D953654C98E77ULL, 0x2D435F31026A6DEDULL, 
            0xC95E607F84058CB6ULL, 0x49235BFAB5D4C56AULL, 0x0891081FB5187F08ULL, 0xAC3BB34EE3AADD8FULL, 
            0x93421F652CBBE61EULL, 0xAB117A0D09C8D493ULL, 0x979B28470658B9E6ULL, 0x79C6DAE5382BB88DULL, 
            0x3116FFC574370DB1ULL, 0x5C01265BDDCF620DULL, 0xC9C9BF65C837216FULL, 0x72AFC21959F96D9DULL, 
            0x02C22F183EEEBC84ULL, 0xE7857058B5FF6EDAULL, 0x07238BBDF48E4960ULL, 0x5B95C4938F8C3447ULL, 
            0x19D5C4457EF99DBAULL, 0x76A41C5CF665170EULL, 0x6353367C0A347D63ULL, 0xAB4F1E92AAF12454ULL
        }
    },
    {
        {
            0x65CD612E5C65B196ULL, 0x8036197EE01B3D60ULL, 0x692799FB76449E0CULL, 0x1B3D29F7695BD26FULL, 
            0x8C27BDE3111E7EE5ULL, 0x0C2A760F76D4744DULL, 0x6AB4FAFB28372DF1ULL, 0x37D6BA4CAD3BDD04ULL, 
            0x8B9D2E164576E77EULL, 0xFD8CA536FD03E259ULL, 0xE1B0198248B88AADULL, 0x17622F761045FAFBULL, 
            0x96551458C52C8777ULL, 0xF6F145F18B0BDEE0ULL, 0xFF6213FEFFD10C2BULL, 0x5A5EEEF88359E9BEULL, 
            0xBA9BE77412809573ULL, 0x8C9189E035FBCD71ULL, 0xC62F7B2895BF321FULL, 0xD4DA696242725629ULL, 
            0xF25B9926129BE882ULL, 0x821916254916D5AFULL, 0xE9F7CCC2B32C31A6ULL, 0xAA36D13E95E9F91DULL, 
            0x4A418403B44DC1D4ULL, 0xFB08E0451CF9A2DAULL, 0x6495A6D5C590B617ULL, 0xF73DBF06CA29F066ULL, 
            0x99613EB1338C0ED4ULL, 0xC1C2B3AE2E2008EBULL, 0xB90A45083E572CB8ULL, 0x17D785173030C161ULL
        },
        {
            0xDEFD4ED9062D203CULL, 0x3D81E835C9E64241ULL, 0x6B0EAA0ACC5ED0EEULL, 0x2D2049FD2FBA1A97ULL, 
            0xC61CD35E97080E6FULL, 0x8E9AF05DA4162424ULL, 0x4087D6A851A67350ULL, 0x093DAB0A08AB1A80ULL, 
            0x00726C6EBDBD0906ULL, 0x025691BD61946CEBULL, 0xDB096B96E4AABACDULL, 0x2A1EB0FF029CCD7BULL, 
            0xF9C659E3DB6DFBFBULL, 0xF5A6F93B827AE338ULL, 0xAD1B842697FB5F20ULL, 0x007691307D41D6F4ULL, 
            0x0C642AF9ACBA30A2ULL, 0x1DF759B043F70BDCULL, 0x917D06F6A1949392ULL, 0x72C66CEED426F4B0ULL, 
            0x29A590E168152A38ULL, 0xFA562DC2D102CFE2ULL, 0xCAAA31BEF61BDA4CULL, 0xC22A5D30F2609FEEULL, 
            0xB1F848F4539E7465ULL, 0xC7BB43AA5DA0A2BDULL, 0x90158BDBA340486AULL, 0xB6D241D6281CE2CCULL, 
            0xFB023C8E290391DEULL, 0x4633D1590ADC9953ULL, 0x68C80B213C5ED6D9ULL, 0x1DB6FAC43AF97347ULL
        },
        {
            0xE4CCBE76D7853B65ULL, 0xFF97B54FAA07A0D5ULL, 0xC2A69D91FF7095C8ULL, 0xF0B00EC5C28BC89DULL, 
            0xF962B6AF438EB397ULL, 0x248146A3ADE21E12ULL, 0x82F6173F879ACD61ULL, 0x4F7567BAF2E1ECA0ULL, 
            0x416F9191E3AE80B5ULL, 0xE44E779B61E9B6A5ULL, 0x7D43FC731C7DE780ULL, 0xE9FDB60C354E4AC2ULL, 
            0x4055DB261F35F54AULL, 0x03D50684A4D81A35ULL, 0x5D8A0A24E4FDC62CULL, 0xBEA677A27A2ACF8EULL, 
            0x5CE117D295A506CEULL, 0xA92C54EABF84EE96ULL, 0x3E8C3BA904DBC1DCULL, 0x3B596F424E674A24ULL, 
            0x849E3C893B058A52ULL, 0xCE9F50D9968DBE47ULL, 0xC4C12AE02AB7F126ULL, 0x8888095167E09BF5ULL, 
            0x970216BE212746D1ULL, 0x86D8F2B3F3DFC1D4ULL, 0xD466EAC472248DDEULL, 0x100466566337BB6CULL, 
            0xFA8817A9E77B9C41ULL, 0x302B1CCC3858D543ULL, 0x11F456BAA003AF14ULL, 0x85FCF8E4533353A1ULL
        },
        {
            0x3A5775D6C8D6BDD8ULL, 0xC4C5B5E0C36ADE24ULL, 0x529ACA84B5506F15ULL, 0x7780C3E565DAFB7AULL, 
            0xBB34AC8035E1DCF0ULL, 0x95CEB86CE458AA23ULL, 0xEDEFF4A1CD9DBC94ULL, 0xD26A601EBA310672ULL, 
            0x373F1F8C471CEA3FULL, 0x9C33A0815E9256B9ULL, 0x6C9F2CE020F213B0ULL, 0xC35EE860AAB3465BULL, 
            0x71F91A1DB93AB803ULL, 0x657AA73AADFB096BULL, 0x1195FA1AFAF649BCULL, 0x94A327A89F7B0DF9ULL, 
            0x0CBECF1901533CE1ULL, 0x966B0A3777478E59ULL, 0x3227F62C89EA7A7BULL, 0xC2269098AE41268CULL, 
            0x8757B5178398ABADULL, 0xF93EA3D1912922D3ULL, 0x9C10EB9F179FE5D9ULL, 0x8C66676C50BB4340ULL, 
            0x737F40AC639A832BULL, 0x1222E1F9D3BE5582ULL, 0x125028F97CDC065CULL, 0x34A3BA25169188B8ULL, 
            0xB7B3CBC39084DB8AULL, 0x83263F71133B4F94ULL, 0x3D447111D06D726EULL, 0xF9E836D9688EA747ULL
        },
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
            0xE818FBFE06C3A7E9ULL, 0xED48251E257B8E24ULL, 0x86F80937883A96AEULL, 0x0025E5B0C8328D91ULL, 
            0x2E87656108A5AE4DULL, 0xA90D076D3B1A04FCULL, 0xC3E9D0071B5CA163ULL, 0x63D9AC3D6D43D432ULL, 
            0xD195B764BA655ECFULL, 0x5BFA7FD8ADE1CAD5ULL, 0x679BB3D30E97EDE3ULL, 0xB1BDD136720AD4A5ULL, 
            0x491F3F1D8E3D9C94ULL, 0x13F0007321DADA66ULL, 0x07504CCA6BD9D342ULL, 0x95DC28D13D86636FULL, 
            0xB250DF9646B833B5ULL, 0xDFC31169EA6AC940ULL, 0x7E409C24EAB402FCULL, 0xF5107DEEE995C656ULL, 
            0xC7C0187DFCB3035AULL, 0x90A149B876BB0CD1ULL, 0xF7F4DDCC04F39E44ULL, 0x5D9E55C61C04B6F4ULL, 
            0xD2BC3908EAC044BEULL, 0x18BFEBC972A9823BULL, 0x909BCE61E5C40CF4ULL, 0xE290F82D5D2668B2ULL, 
            0x303FE3CDB96F179BULL, 0x80C170D114896F13ULL, 0x16EC423CEBA62274ULL, 0xE29782918CFAE92CULL
        }
    },
    {
        {
            0x81633DB0FD0B4C07ULL, 0x225EC9EE4EB25151ULL, 0x86B5C9425BADAD74ULL, 0xC1FB37B1BBF0DF0DULL, 
            0x1BBCB5C3EBB9DA59ULL, 0x62A54A8BB3B02968ULL, 0x2F6BC7460B662346ULL, 0x2F12303CBB8B07F6ULL, 
            0x2CE4AE65E400F176ULL, 0x63572A4342B7153AULL, 0x95002A1CA7F37C4AULL, 0x8691D29EE413AFD5ULL, 
            0x5B6B54D3949B9B50ULL, 0x41FA24D6549F4D36ULL, 0x64CEB50CE4DD66B8ULL, 0x0D8C5C54778E1C07ULL, 
            0x35D2C2CEC9F55D1DULL, 0x4473B053FE31E5DAULL, 0x58A43A7507E22848ULL, 0xE375EFA0D0B3529BULL, 
            0xFB25F166F250DE86ULL, 0x44510ECCD7CB508FULL, 0xA29965856FEFA267ULL, 0x3DB1BA630F3D3342ULL, 
            0x564BA34E005F420BULL, 0xC02886DAA0777627ULL, 0x25E408011A501E44ULL, 0xF6A5D0EE9B849476ULL, 
            0x29FEB6E28FADB38DULL, 0x556F4AD15336FD38ULL, 0x477C37C149CB7F3BULL, 0x97D858BF0781D12DULL
        },
        {
            0xFA1797F8E3B90B16ULL, 0x8C22237FB25B8FCFULL, 0x9FACB072AEDE3AE7ULL, 0x703268BBA641B600ULL, 
            0x15432A517F40617CULL, 0xAD47721352315FA0ULL, 0xD83DE717EBE515A6ULL, 0xCBE63FF6F987BD3DULL, 
            0x6BF07AE0253000B8ULL, 0xC326ABD3DA55AAD5ULL, 0xF4B89CF5FB3C4757ULL, 0x0825EBF6AD826A64ULL, 
            0x95C7D601B4681E63ULL, 0xA3811417B7CBA69AULL, 0xDABAEBEDE36D8578ULL, 0xADE2B8A982A1A165ULL, 
            0x1CEB1153AFC88395ULL, 0x42548ED28BB4E786ULL, 0x08150F672023CD28ULL, 0x8AC91D1EF60D59F2ULL, 
            0x44D0EFEFAB7C5B7BULL, 0x3F098C52D3B25A6DULL, 0x6C0606950F776CBEULL, 0x2A4DE40809A7064FULL, 
            0x820C596FA1A02C40ULL, 0x08573FFD9F93D906ULL, 0x7251B68130292AA3ULL, 0x0E30331C32204CB1ULL, 
            0xC002E2F6B340AAA7ULL, 0xB11B028BFC3DDF61ULL, 0xDE6A1D128F1E31BEULL, 0x4E722EC69736C972ULL
        },
        {
            0x878E73F8A78DC006ULL, 0xF2E2FB0147C159D1ULL, 0x8D95F9B78E71DBA9ULL, 0xDFFFF50024C1D4C9ULL, 
            0x94AFD414B775075AULL, 0xF587B67F2D569138ULL, 0xD6ED0533A8DDDE96ULL, 0x8022A15D4D6F2657ULL, 
            0xF005654FD829EAC5ULL, 0x9BE57705EA64FD17ULL, 0xFFC95DE945F56FE9ULL, 0x37D043F52855E081ULL, 
            0x6C05C83957177E55ULL, 0xE5EF9D5C613B33F5ULL, 0x24EEC603F75AB58CULL, 0x7B66D7E9643E0740ULL, 
            0xAD384F3479D1132BULL, 0x76C3A1AE3D5F2FD2ULL, 0x974FB142DD5F7B6CULL, 0x06680E933F6F4FEFULL, 
            0x3736B7AB89B7F49AULL, 0x4638716EDB55BF24ULL, 0xEF3E6BF13EF9D1A4ULL, 0x6215E056ECC46CE7ULL, 
            0x54D6B25E8AF89265ULL, 0x8CB80B284CEE6412ULL, 0x7BAE162E183287DFULL, 0x47921B12392AF268ULL, 
            0x43DA7C661BB45617ULL, 0x7AD28F6297C8449DULL, 0xD2976AD924D3E7DDULL, 0x047A30FF39220C21ULL
        },
        {
            0xC9A24EA926B5ADD8ULL, 0x4E38405046B07BC2ULL, 0xBC7B0772D0E7F7CEULL, 0x43EC629DDF2CE962ULL, 
            0x709C19EBC736F906ULL, 0x6DB112837AB5B8EFULL, 0xACC893E401ECDD81ULL, 0x66E5ECA6D44232CDULL, 
            0x746CF55D411D625FULL, 0xC7EBB7E3D5820DA0ULL, 0xA3520F6C6A9FD262ULL, 0x9AC965E94249E569ULL, 
            0x0A16EA89C5B10E0EULL, 0xAAAD118BA193734EULL, 0x7544B18B73C3EC52ULL, 0xB697965C77F84AADULL, 
            0x8FA1067E36D4EDE4ULL, 0xF8A33875560A8A96ULL, 0x1D00E2042D08B587ULL, 0x74EFE001DEF4C5F6ULL, 
            0x216DF8F50A744FE0ULL, 0xBFDE98C5E9DEAEFAULL, 0xC11E19AE8400E505ULL, 0x70896F08A0CADD16ULL, 
            0x401751A15F132802ULL, 0x449EF643F02207EDULL, 0x213F6160A73F5BB2ULL, 0x4A8A8474285F7C7CULL, 
            0x5902641D8C8CBDA8ULL, 0xCABDB1564216EF43ULL, 0x5A0F018D7BD5B2E6ULL, 0x162753AAD15C720EULL
        },
        {
            0x68CE7C77E699446AULL, 0x8AC62CDE1B92BEADULL, 0x7067097D249ED1E8ULL, 0x3AC52A18CD174086ULL, 
            0x4B4F91B86C3B0039ULL, 0xA636A10F5C3FFF58ULL, 0x4E010395A1CC4BD2ULL, 0xA7517CE4E206ECC6ULL, 
            0x76A8D87E977E7F81ULL, 0x584A0015FA14330CULL, 0x33A449C2DC433972ULL, 0x5AEDDDA25A787E15ULL, 
            0x6D04788AF8D6605AULL, 0xA3EBD977CC9EFC94ULL, 0x390E78FDB07826BBULL, 0x548EE0E7D52AC717ULL, 
            0xC3AE0C20D34C9F39ULL, 0x6782B2F22E86B847ULL, 0x2171FE6AE51C3CEAULL, 0x5D11BB35F3892956ULL, 
            0x965D57930B7B395AULL, 0xBC780B3727CB903CULL, 0x077AABF3921A7F1FULL, 0xD66F2858F7CBD5CEULL, 
            0x70FAD961D1139DCBULL, 0x0FDF581A38E455EBULL, 0xB1EDB1CBAF545163ULL, 0xFB2FA384CF58A5DDULL, 
            0x50AA4C21F01DCB6DULL, 0xEACC640D64710FDFULL, 0xA658A4F99869E48AULL, 0x9BEE746B5326480FULL
        },
        {
            0x41EC97CE35EBF6A4ULL, 0x27E988FB6F576154ULL, 0x7E211B0899DE74F3ULL, 0xB72D8DC59684886AULL, 
            0xA12A3FA55EE18B8CULL, 0xE75BC5503B30D6FEULL, 0xE8DCC9373D9FAAB0ULL, 0xBB600DD22256B204ULL, 
            0x4C45A79E524B6367ULL, 0x6F660DBDAFA01CCCULL, 0x1407C9EBF85040F6ULL, 0xAD4B766098E78C45ULL, 
            0xEC1AC21D2532CCFEULL, 0x23245A2C4D7ED6A4ULL, 0x015C144459ED201FULL, 0xA6B57241E9277B50ULL, 
            0xD72CCD254E2B4B75ULL, 0x9530FF80DF6548F2ULL, 0x685BD06EF1BA7AF9ULL, 0x53045DABF82E66D6ULL, 
            0x27430D7E4E2571F7ULL, 0xE9E2E37664FBD0F6ULL, 0xB285E78B3ADE19A2ULL, 0xE23064D99AB5882CULL, 
            0x6F07D8A918D4990AULL, 0x05A42294049A6430ULL, 0xD1355F6DC677C96EULL, 0xECB5DDF78C283393ULL, 
            0x61C3F1BD318AFB67ULL, 0x5B46CC465B707C7EULL, 0xDC17C91995112749ULL, 0x4D893EDCD6D81938ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseDConstants = {
    0x2C6261A6C95D5965ULL,
    0x30C301911C223B32ULL,
    0xF83AE235A186F886ULL,
    0x2C6261A6C95D5965ULL,
    0x30C301911C223B32ULL,
    0xF83AE235A186F886ULL,
    0xFC416739DDF06334ULL,
    0xCBEC20B564595FD0ULL,
    0x4D,
    0xE5,
    0x3B,
    0x74,
    0x58,
    0x1A,
    0x08,
    0xCB
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseESalts = {
    {
        {
            0xEC94AD9B0524C10DULL, 0xDCD2E45D90D32F54ULL, 0xBA5C45D02999C658ULL, 0xA7DC232A97D0DE62ULL, 
            0xCE41C5A8B1FB1A09ULL, 0x018DA75CF2D8011CULL, 0x7968462CF4F82B81ULL, 0x170EDBF1862E65A5ULL, 
            0xBFE7715D63FFB807ULL, 0x964958B692D3754EULL, 0xE89E4BDE3EAD5861ULL, 0x1598E30E24F83D53ULL, 
            0x55B329F141B35AC2ULL, 0x0B64331FD369FA0DULL, 0xA6FE1B4DE858BC90ULL, 0x699AAD867E73FA3CULL, 
            0xFB8A0CB5007D75A8ULL, 0xEF43CE9285042BCCULL, 0x2DA361B37D69A1E7ULL, 0xE1D98CD02A3C599CULL, 
            0x5BF38CCDEB5B4207ULL, 0x20131F5A99A7FD5BULL, 0x79B4C82EF1C4717BULL, 0xFDD1FDF6243469BAULL, 
            0xEDE08E94AEAEA423ULL, 0x4DD95809544720E7ULL, 0x3F41C73E7C738D70ULL, 0x4EF9BA2E27B28164ULL, 
            0xB58DB6AE70A97302ULL, 0x003F0AD1877CB465ULL, 0x7EFBD62E95380E1DULL, 0x8DE8FF3D489E1829ULL
        },
        {
            0xFBC8DB7D99F14E92ULL, 0x843BE3413ABEE52BULL, 0x23C30FEFAB1D419CULL, 0xEE9ED22991E5B7FAULL, 
            0x7B6F3FA8DEC2DC48ULL, 0x38BD7ABF6EC0FE4BULL, 0xC30E9CEABBF8E0D0ULL, 0x0AB4000D201C7628ULL, 
            0x16690007CA4A7C73ULL, 0x6ABDB25D7F3E4476ULL, 0x5FB2B8B49514E187ULL, 0xF7172217B48013A3ULL, 
            0xEDBC93E265FD3303ULL, 0x4C3316518C8AF886ULL, 0xA46E5D5077D43F1CULL, 0xA8CE2689A5E53BA5ULL, 
            0x67FA05D2CF3B7590ULL, 0xF2A0CEA3ADE4DD5BULL, 0xA65EB72CD29D8494ULL, 0x7384B9E00908D57BULL, 
            0x594BE8F83D6C6B1AULL, 0xFA175874E8D6349EULL, 0x252B789FA2EEBABEULL, 0x0CC16C5654CDD0A2ULL, 
            0x05B077B469F6E14EULL, 0x4B8B93CD5509AA34ULL, 0x81F6481F59664F29ULL, 0xB21D7ABF0ED04C0CULL, 
            0xCA7EB024116BCF75ULL, 0x18716F723075A1D6ULL, 0xEDBBC8ACFF8BF698ULL, 0xF84F4F9E951990C6ULL
        },
        {
            0xD58F167F25D6D100ULL, 0x9E9348938F1370E2ULL, 0x7B0849A6D49998A8ULL, 0x2C525E7CEF622AEAULL, 
            0x71AAD0E2F04845F7ULL, 0x8EAA24687A8ECB52ULL, 0x5F47752E3446B3CAULL, 0x840D22E470DD0933ULL, 
            0xE542855343A2BAD2ULL, 0x0F529830F1468293ULL, 0x9459A998F62C7F5DULL, 0x6E64A6A8AC6E0B6CULL, 
            0xBEAE0748162E539FULL, 0x4A101AE8E2C2E437ULL, 0x5D8AD60625F04043ULL, 0x851BE4C210089464ULL, 
            0xF891B5E54315467CULL, 0xAD0B50DEE2A0C656ULL, 0x70B1683F0B638957ULL, 0x95BDCD396A866ACFULL, 
            0xDA5D70157C32517BULL, 0x786F8CB82D62147BULL, 0x7B05F7D860C1460DULL, 0xC19DA5FB3EC719F2ULL, 
            0xBD8CB9FA92E4FA80ULL, 0xF6A6F5D62D2A8B83ULL, 0xAD1254BC61770898ULL, 0xFF9B12F31A7CC457ULL, 
            0xE3A21BAC08344166ULL, 0xC92934225A32E9E1ULL, 0x00DEC0926BD04650ULL, 0x9D83ECFCD7BB8247ULL
        },
        {
            0xB5ABD55CC82E6DEDULL, 0x1197643D36B4B8E1ULL, 0x374F2BDB088E8216ULL, 0x35DC1C26ABFF9D53ULL, 
            0x1C53B05705976FD2ULL, 0xDAE858BE34269654ULL, 0x5EC14F8C91659995ULL, 0xD8B2A72228775AE4ULL, 
            0x06D235133B77E30BULL, 0xE65474D839503F1AULL, 0xB72076CC24422BE7ULL, 0x48DEBE0077B0623FULL, 
            0xD17472D18749A0EFULL, 0xC1C5C48CE7D4E7EDULL, 0xE5EDC1276E266677ULL, 0xD4B7515083433FC6ULL, 
            0xEDEDA1B7873AE262ULL, 0x1F15844D85297B74ULL, 0x8B3E056CEAF13D4DULL, 0xB3D5A56506409C0FULL, 
            0xF0BF725C369EF6EAULL, 0xC7EB5619822D5A87ULL, 0x7AB7349FE100965BULL, 0x0EDF86FC3C52D62FULL, 
            0x7AE2DB6F19FB44FDULL, 0xC2D0F3C3D12010DAULL, 0x811A8D95A2063290ULL, 0x1DFC39E4EF6CCAA2ULL, 
            0x68BFCB510601BDB5ULL, 0x303E58D0107986C9ULL, 0x6D4C086825B7EE81ULL, 0xEB8CBB9F3C140614ULL
        },
        {
            0x15B5720E1E643E0BULL, 0x98F924568A2A0C3EULL, 0x77BD021886D2B9EEULL, 0x372C1DF245FFBDC7ULL, 
            0x7211CB92786E4A49ULL, 0x6DA86CB1F093163DULL, 0xD9E9424BAF9F16A2ULL, 0xFF8AB5949FE93C1FULL, 
            0x9F21542332721DD3ULL, 0x81F4739DB6A15C9BULL, 0x519754298BEB6D2EULL, 0x0F14B2D796A1F9E1ULL, 
            0x0A33A30AF80A63D7ULL, 0x1874F82F04F6ECA1ULL, 0xAD3953DCA5EF7E78ULL, 0xAD43C438C020B2DAULL, 
            0x7934E97C3AF6F6D9ULL, 0x7B00D6210085E72FULL, 0xD36A59DD6569475DULL, 0x6E14A1E11D98A6F4ULL, 
            0xD5C090B5BA3A2D0AULL, 0xE6DC6B76721BBC51ULL, 0x91ACFBE6D42944EDULL, 0xB3F877A4B6C7446AULL, 
            0x785914667F5C85BCULL, 0xF8117843ED2BD534ULL, 0xCDCCCD6CE31A3AD3ULL, 0x66EE40507A617DB8ULL, 
            0x472FE6AE8DCA3C53ULL, 0xBB73B653EF5DEE93ULL, 0x8B11FCAC924B968AULL, 0x70832C84B44F5DDEULL
        },
        {
            0x8D43FDC09BAFEC22ULL, 0x95802EB069ABFDC3ULL, 0xFB39DD332C907366ULL, 0xD3FF6D02CD39CAAAULL, 
            0xC29819F004ABE5CDULL, 0x4B44292437F349BDULL, 0x67BBE4A7748C5F8BULL, 0xC2A1502D115081C2ULL, 
            0x76779FD1C83B995AULL, 0x6A27C322BE654052ULL, 0x48372AE6C21ADEE6ULL, 0x6A9B486CED67EA35ULL, 
            0x4E25180E6E3C5D79ULL, 0x2173EB0B9AECB49BULL, 0xAEFA5B3D02721DD3ULL, 0xB5EF74395886872BULL, 
            0xC32C4D34DF43D8ADULL, 0x7964920D76939894ULL, 0x2E2105D1323E12CDULL, 0x5D35AFFFB25A051CULL, 
            0x8B28828D450AD009ULL, 0x0AE045B404AF4D82ULL, 0xB42A24600DA7B99CULL, 0x8B0DF3FF099CB6CFULL, 
            0xA702364A4FBAEF96ULL, 0x4AA8F230EAF1F81AULL, 0x4C92709D959A96F4ULL, 0xF912707EFAB0BE6BULL, 
            0x20949D31C4DD4F2FULL, 0x4D2CABA9B88FEC04ULL, 0xD9428BF339EA98B3ULL, 0xB543C79ECB62F8A4ULL
        }
    },
    {
        {
            0x9C9BF729918A33BEULL, 0xE476368E473C5285ULL, 0x6153ACA0F591FA5EULL, 0x78CC1D9485102D61ULL, 
            0x66843E74EFCDD878ULL, 0xF7B958F65452C352ULL, 0xE6998EEFC8893D51ULL, 0x01B898159058EDB2ULL, 
            0x7C5B1363F1897183ULL, 0xD024DEF79ECCC549ULL, 0xBDE880E867665C2BULL, 0xE71638A9308EDCC1ULL, 
            0x321EB6EF30DCB6ECULL, 0x5A144F34899F577DULL, 0x2CE5A3BF76723A4FULL, 0x84FF61C2EACE003BULL, 
            0x8613BF4D60549F16ULL, 0x4D4DF858BBD5FDFCULL, 0xED8B430BAF3E65F8ULL, 0x846855CAB26892FDULL, 
            0x9F21B97F747D0C64ULL, 0x648026255B6DFFDAULL, 0x363EDDFEBF57F1E3ULL, 0xB72D78D0CA10428CULL, 
            0xCC6667860EF41526ULL, 0x5B606A8D5A4A11F4ULL, 0xA89063DA59308E78ULL, 0xC66852843329895AULL, 
            0xFC5BDBF2500A48D3ULL, 0x322FE17437F04CB5ULL, 0x70379C5130B53E8CULL, 0x1A1C21A295F03664ULL
        },
        {
            0x1B9746655633DE9EULL, 0xCC09FB29537B2FD3ULL, 0x503D3FBD1242F9F2ULL, 0x47814934B9E70630ULL, 
            0x555AD9054283F830ULL, 0x22A8BDBFBF35E23FULL, 0xCD43315B1BC970AEULL, 0x9704157E88D2FD56ULL, 
            0x6E2E1D357FE00691ULL, 0x8B3CDB6488FD9C86ULL, 0x4D212EA6966CDA3BULL, 0x60F85362F635328DULL, 
            0xBF92D3D649B9D848ULL, 0xD1AABF6F615005F1ULL, 0xF73AB514EF8DC2EEULL, 0x0FA1A50487F6CD15ULL, 
            0xED7D3578EF895936ULL, 0x98A63A57A18FE0A8ULL, 0xB2D96C8D9283CD12ULL, 0x2795C7B0376346D6ULL, 
            0x1CF9BBBF5E7629B3ULL, 0xAFE2976C8EB18AE5ULL, 0x5A188E17A07738B8ULL, 0x476F3A1E418A43DDULL, 
            0x69A5C6B58908D5E6ULL, 0x3A0662480DECE019ULL, 0xC2B1FB69C996BF6AULL, 0x3755408C531312D4ULL, 
            0xF022D02B1FEEAFF6ULL, 0xBCC2DD09E4AE4FF5ULL, 0xDFF4B366A4CCF803ULL, 0x3C334EAC9AB339C6ULL
        },
        {
            0x0610E78778509A51ULL, 0x4D62BF508A485F3FULL, 0x182CDC238075A76AULL, 0x5BD62E0CA1B8ED5AULL, 
            0x00888AD4318347CBULL, 0x399B6CF7A2AE9668ULL, 0x75EBC5BA2295D07BULL, 0xA043DC699E3FC76DULL, 
            0x7DE49B50BF671078ULL, 0x8024BD5E91F7D9B9ULL, 0xAE51E404F67F6A3FULL, 0x52A0FC96214AE848ULL, 
            0xCD2EC9F7D3F9CEF6ULL, 0x891856880F15C4E7ULL, 0xEDE6ADD0C11964BAULL, 0xC774B3D790EA9A4CULL, 
            0x111945CCD9F6A757ULL, 0xAEC38798CCA58007ULL, 0x87CD01D358A2D8CEULL, 0xD4B26BA5376930D4ULL, 
            0x61BF12F5B4018EC7ULL, 0x99D17FA58D9EFB5EULL, 0xE2B4ED5035A664DBULL, 0x6A48A3EF2566F858ULL, 
            0x72B9ED36F3B45CC8ULL, 0x6892445D354857F2ULL, 0xBE557E1EE5560CB3ULL, 0x67B7AF0DDA8883C4ULL, 
            0x8DC90C4BE95A47B9ULL, 0x296460476BBF9174ULL, 0xECEAEE5F8A10454AULL, 0x042F2476BC896F9FULL
        },
        {
            0x054EBEDDAC143154ULL, 0x0A5C063E9C8A81CFULL, 0x9F6C19D79CF148C1ULL, 0xF06C21CD764E800CULL, 
            0x5BD43893B81D16F5ULL, 0xED507777336BF655ULL, 0xE45B213FAC85C571ULL, 0x9330758D3888D058ULL, 
            0x12474A9C62D27D16ULL, 0xDB65B08292AC93B9ULL, 0x1041BB651424466BULL, 0x54E2198D3550413FULL, 
            0x3515703DF02C7D3FULL, 0x273905C2FC2BECABULL, 0x82811584C8F2EF3EULL, 0x9F577EFF163D660DULL, 
            0xD27AB8385DBC2422ULL, 0xB32105C514B30E6EULL, 0x4F1E1864F9FA8389ULL, 0x63D55958F7FB3498ULL, 
            0xE3CAA1C66A6A42A4ULL, 0x2FE9391EFC32EE9CULL, 0xBF055C11955F1B8CULL, 0xD342E0EE1F9FED71ULL, 
            0x9F6C618C6369BE1CULL, 0xB7236C68ED0E8C30ULL, 0xFC376D3B6A3FD79CULL, 0x7DF2BC4F31283462ULL, 
            0xD1A54BC73283BBEBULL, 0x5392B73862B1AC73ULL, 0x49F9CBDC99C9CFAEULL, 0x638CE10417E26B82ULL
        },
        {
            0x8F2356E46BE0D1F8ULL, 0x5B22E0504AD3086DULL, 0x578BFA0EBE82552CULL, 0x244BD9970FEC1659ULL, 
            0x3BE2944BACBBEA56ULL, 0x2A86D74A419CBBDFULL, 0x2F62A9FD87904F14ULL, 0xC58A48BC0BA5FAF8ULL, 
            0x07F42090F57099F0ULL, 0xCEF9E1A582D4555DULL, 0x1F9B376BD1C3B123ULL, 0x480A14B30807CFDBULL, 
            0xE91ABC10906B48D2ULL, 0x293A29BDE0BE11E1ULL, 0x4EC974F39238919FULL, 0xD8B0C44DD6FDB9A6ULL, 
            0x671CFDCAE2CBD39DULL, 0xB7AD1F6672B2A45AULL, 0x1B3A68207067B5D1ULL, 0xB6D518DEB932806EULL, 
            0x7CB3F89A2A56BF4BULL, 0xA081EBD830986968ULL, 0x70287DFB94889950ULL, 0xA48D0D2960E03C77ULL, 
            0x97000635DFF8503EULL, 0xEEB1D9CBCDFF7B75ULL, 0x732081D5E7529DC2ULL, 0xCECEDA4CFFF791D9ULL, 
            0x02AF9E3B30321429ULL, 0xC50B15C2AE181BA3ULL, 0xC80B8AE9245625A6ULL, 0xC9AE8D4527AEF9CDULL
        },
        {
            0x00DA3A328E30CF6FULL, 0x93DBBE4660AD47ADULL, 0x9D597CA6E4B1FE41ULL, 0x509F712EE5952AEAULL, 
            0xB70846632BC419F7ULL, 0x03257F69493EB81CULL, 0x284AB00F5510919BULL, 0x18320032DB61F27CULL, 
            0x9BEEAB4FFA52989FULL, 0xC2209A63D00FB5D4ULL, 0x61C25A2B55B55A6AULL, 0x7DF6683E45F658E4ULL, 
            0x20B481432641B024ULL, 0xA7BB7C637B3A6DA8ULL, 0x54F5AD1E1957D428ULL, 0x56ED2A36D73E7F86ULL, 
            0xDF34A1CE722D3D1DULL, 0x3E057B9A3689D71FULL, 0x99A055A93A63F6CFULL, 0xDD2A38C98427332FULL, 
            0xB5DA2E375D8CF278ULL, 0x28425D2DA179AEA9ULL, 0xC3575F4E925C47E3ULL, 0x11DAA0AD4B461097ULL, 
            0x1E446EA024D386B2ULL, 0xCDE9AD8EDAA8A8EFULL, 0x299240094C4BBCE5ULL, 0xDC833B48AE6140C4ULL, 
            0x14557E517FCA2647ULL, 0x22DDBFBA775FF494ULL, 0xE3D53E1B2431F607ULL, 0x7FE600266C12C276ULL
        }
    },
    {
        {
            0x2187BC903A7A25ADULL, 0x87EF2BDFDD78D83FULL, 0xFA937C86D7254A2CULL, 0x3B4211C6FA155C5AULL, 
            0xF05F6728555E2EAAULL, 0xE93C5FB2F66573A3ULL, 0x141CD60FBC105DDFULL, 0xE2C7012CB2771C5EULL, 
            0x58DC21D24417FD44ULL, 0x1CDEAB8B91D801CBULL, 0xA2EC34A63A665CFDULL, 0xFDE83DA26D510958ULL, 
            0xB2F84DEE6D164A74ULL, 0x14E7F13623EEC9F9ULL, 0x0CA8840647FCC6D5ULL, 0x224C7A09754B27A9ULL, 
            0xFEDCC554D94D7AABULL, 0x139369BDA58E2DB4ULL, 0xE192DD6706C54564ULL, 0x5E3CBE1CE77D615EULL, 
            0xE4A5EAB21D7607D3ULL, 0xC5749C742A1B9B58ULL, 0x34A13BBF05B98945ULL, 0x7C2404466B530BDFULL, 
            0xEB8A09AFD479354EULL, 0x0BF38541DADCE58FULL, 0xB34F8A00C11330E6ULL, 0x44D9DCFF85C96EE8ULL, 
            0xDC11FB33009FFBEAULL, 0x55BE46F27FD35BA0ULL, 0x8046C5F8B37F31CAULL, 0x66899AAC425DA576ULL
        },
        {
            0x6BCD88CDF6B9C432ULL, 0xB53CEAF12288CF26ULL, 0xEE938E3D6EA3F02EULL, 0x382C6F18FBA2EF46ULL, 
            0xEF8DDD32940BD047ULL, 0x21F4EC9F86006AE0ULL, 0x7F9EF2032D3435EBULL, 0xA32B1227A234AA4BULL, 
            0xE15091B2905405E2ULL, 0x4209FBA8EEC07088ULL, 0xA49A36AF82BDC9C1ULL, 0x39C588F90A6EF748ULL, 
            0x75D6A76F36832F26ULL, 0xD6DB156CF37627ADULL, 0x1309883996EF61C8ULL, 0xF99F93F2A2A280CDULL, 
            0x595F18E917B6F90EULL, 0xFDAE5AFEF91087CFULL, 0xE2CCA23B9DC1D3A6ULL, 0xF6C337CFF9F0F963ULL, 
            0xD06CFB04899EB088ULL, 0xD99215F5854ACA00ULL, 0xD75E213D95D8BA43ULL, 0xC641865844AE4678ULL, 
            0x971DE9A1F7E9F5D1ULL, 0x079353B9F99B7BCAULL, 0xD57B84EBC0FCF0DDULL, 0x24FCDF78F5876D3EULL, 
            0xF7684F31C7EB1AECULL, 0x0CC18B76FDA46E88ULL, 0xBBFA9663D1EC9F2EULL, 0xBF1CD8E7CE722014ULL
        },
        {
            0x69BA34E9ACEE505DULL, 0x4ECBACA7A0DDEE39ULL, 0x51271E11B8C2270FULL, 0xE9EFAF694F2C49B2ULL, 
            0xB044D913910DDCBFULL, 0x1C48D0F55B99C45DULL, 0xBD6D61A92C8C8993ULL, 0x72E6D30770D1AF28ULL, 
            0x79E88D55AEAEC696ULL, 0x0592D7DF62F7E9C0ULL, 0xD4CF2C6A36CCDDC4ULL, 0x81561B939BA581BBULL, 
            0x2AA6E74454532B4DULL, 0x083E9AF8AAEB16D1ULL, 0x4121D94844ED74C1ULL, 0x5FC7D30211D358EEULL, 
            0x0FC198A25C8B9D87ULL, 0x382694AD1DEC75B0ULL, 0xFD0B73799E6629B4ULL, 0x1405970FE96F4AFCULL, 
            0xBC71A14CA8DCB60EULL, 0x87EADE3C2B8FB288ULL, 0x50E08A0667F268DAULL, 0x28E5CA5B909323EFULL, 
            0x3A6C78CBBD315DB0ULL, 0xDD95EB6D71622024ULL, 0x81F44FED09871398ULL, 0xFC8652FDCD6D8003ULL, 
            0xF3E6C16771B0FBCFULL, 0x56738B22A547E213ULL, 0x247E88A7A9B3586FULL, 0x81F7078AA58AE11BULL
        },
        {
            0xEB72C367F9345795ULL, 0x5DE56D688D0E7A2DULL, 0xEDDBA0A38C7E3151ULL, 0x5D4F0A87FEBB5A46ULL, 
            0x3881F589E100AC0EULL, 0xBAA06FBF2AB63614ULL, 0x0BE064D888797D2AULL, 0x81641BA689C343C8ULL, 
            0x3533B10E096B0A08ULL, 0xC31726B70EC3E8B3ULL, 0x52D1123901822A5BULL, 0x2F103505163535E5ULL, 
            0x8B51398ADADE857EULL, 0x6AF3FD79F4F95448ULL, 0xB85B961795B12CECULL, 0x5AD67D1ED6412EDDULL, 
            0x21BBC38755EB0D89ULL, 0x94E40F608B2840B7ULL, 0x7670D9307008FD9DULL, 0x20C7E78B1AF6F1AAULL, 
            0xD13EA8BB8E23882AULL, 0x70EB68C9F6985CCEULL, 0xE85C68ED68AEE5C8ULL, 0x8F88EAC106E760CEULL, 
            0xBC4CE0BEF2D00389ULL, 0xF222F93AF0469DF3ULL, 0xAF2AE0766AEC7C4FULL, 0x8A3AD4524197EE41ULL, 
            0xE376F62C5B8DB1A2ULL, 0x46F80CB815F8BB4AULL, 0x9A253FF2B02AF428ULL, 0x8DC908B0A88A6186ULL
        },
        {
            0xA29DCCF02FE882FFULL, 0x6FB5D311BD9C7A10ULL, 0x0E1BDD4A9A2A90E5ULL, 0x6A1F2DB4FC74AD19ULL, 
            0x8BA0E4E725DFA92BULL, 0x404A2D327E3845E3ULL, 0xEBA6D05619E37C2BULL, 0x06B6EF2F022F543CULL, 
            0x2F17FE133CBB871BULL, 0x178AF60DEE08FBECULL, 0x2657BA75707B91AAULL, 0xE3CA049789E2DDADULL, 
            0x80A24E706B431469ULL, 0x6C2F168AA0116248ULL, 0x79B3AEADCB50E19EULL, 0x746ADD24E0CB702DULL, 
            0x8EA76B5D4DC1CCAAULL, 0x2D93AB03F338F85FULL, 0xCD6D89CD33D7F463ULL, 0xFA056D623637410CULL, 
            0x4DE2ADE178E56D7EULL, 0x5BF1853596A5F87AULL, 0xD5EA059B9B3661BEULL, 0x5BE529EEA26A03D0ULL, 
            0xA8EEE27189948CAFULL, 0xB25890350E00C7C7ULL, 0xF0B25F82E8F1E5BEULL, 0x3617BE04C4DC7C32ULL, 
            0xBC6DAEA62FF0243AULL, 0x9D900ACCE0B3B30EULL, 0xD8E58BC509208ED7ULL, 0x60434BD534C8B8E0ULL
        },
        {
            0x0844CF7AF20C12EFULL, 0x7FA12B0F81E58E70ULL, 0xABF29DB2E4C4814AULL, 0xCD94F07E4081DAF1ULL, 
            0x45AE542FA1041504ULL, 0xA0925A60C4095E8CULL, 0x551FE1A55A4DE564ULL, 0x78EE63FFC62C67C3ULL, 
            0xD349258259CFA63CULL, 0xF7AD38858ECB8DDFULL, 0x96E604C80392D7A7ULL, 0x2A5E1A1F5D922366ULL, 
            0xC9A826FF461D4357ULL, 0xD593B7EF7E44644CULL, 0xAACEE32DDE089FFCULL, 0x9A55EA5948E818CDULL, 
            0x0F0C1601CBC08651ULL, 0x678D3B68389576BBULL, 0xEE58F0560A8CD08CULL, 0xC7EAED15F706EBEAULL, 
            0x2A8A772C8F3AE05BULL, 0x25D72449F51C0480ULL, 0x0D94B69F91DB8B3AULL, 0xD11D4B8592FF7A79ULL, 
            0x9B371BF2217EF71FULL, 0xAEAE215AD91C9B65ULL, 0x45BD9EFA78E10CDEULL, 0xD56771D3B151E0C8ULL, 
            0xFF03A38BEA7B7FB6ULL, 0x4C9C3E96C19A95D7ULL, 0xA6219AC3BB2F51C0ULL, 0x9F586D2027B6F969ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseEConstants = {
    0x20F42EE77878AD4EULL,
    0xCF6D2148EDCA2C16ULL,
    0xD0407DD9619EDAABULL,
    0x20F42EE77878AD4EULL,
    0xCF6D2148EDCA2C16ULL,
    0xD0407DD9619EDAABULL,
    0x26F7AEACC147F126ULL,
    0x1D766CBBDB75D120ULL,
    0x56,
    0x0F,
    0x0C,
    0x3B,
    0x1C,
    0x14,
    0x3A,
    0x52
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseFSalts = {
    {
        {
            0x95A0A86A95AC84C1ULL, 0xEFB00F7833AD54B4ULL, 0x0A5C15E88919E9D4ULL, 0xB0587CA5172E2C7CULL, 
            0xD26019453099094EULL, 0x5A0CAA1F6257B4B0ULL, 0xABE21256C26BD515ULL, 0xF80309F963E5F5A2ULL, 
            0xB3B5A7C63F1805B2ULL, 0xE179FAD550AD1CDFULL, 0xF50E16075AC2FB2AULL, 0x9E40D800FA9849BFULL, 
            0xEF2229E2104DC42BULL, 0x31C9BE7207B57C77ULL, 0x69B1118ACDB5EAEEULL, 0xFBB30A8D58071145ULL, 
            0x1E33582008C2246EULL, 0xE459BE50378C9069ULL, 0x0C2C36013D9B9F43ULL, 0x3F99FA93C2E97D1BULL, 
            0x9512DF3F2A6A605BULL, 0xB3E9F4299231471AULL, 0xE21DC35A823642ACULL, 0x60BAFF13EFA80B00ULL, 
            0xAEC9D146559FE6FDULL, 0x28264304D5C3CC82ULL, 0xDB356E9850AF7394ULL, 0x6982A7FA8609B085ULL, 
            0xB423F2A82F6AF50BULL, 0xD9BB99832FF2AAF8ULL, 0xF99B5856614AD483ULL, 0x50559A1126199A8BULL
        },
        {
            0x3FF19E3451EC4DE1ULL, 0x98CFA8AB02F1C4D4ULL, 0xF4AD851E64917EDAULL, 0xF8486A4CEEC5F599ULL, 
            0x3E20E13FF928BB51ULL, 0x0277E69FA4538975ULL, 0x5B12EFB1EDBB7568ULL, 0x5700C6F82185325BULL, 
            0x98CB227C4F3FE337ULL, 0xAAC51EE239848ACDULL, 0x3470CEB8834E0296ULL, 0x9423AD3F108B9F26ULL, 
            0x93A38430A1800B9CULL, 0xD2BBFBD9DB7FA14EULL, 0x6B28F65FAF4E12F8ULL, 0x8094E81055E47AC2ULL, 
            0x7E0636CC7BA2F8CEULL, 0xB688D1D64EF3F3FAULL, 0x6172A5A098A9DF6DULL, 0x88040A6D3D5B561CULL, 
            0xD9534C4EAA766CB6ULL, 0xC38B3A734A0B39E4ULL, 0xA39D72EE6A463094ULL, 0xC8A144F2DD1C85A4ULL, 
            0x7FDF84B51EBC13C0ULL, 0x6E8972A146F12FCAULL, 0x06EF4CC1C8755ED3ULL, 0x482B1394BC27D3D2ULL, 
            0x261EC3B5E3D42B19ULL, 0xFB10C26B7AA285BDULL, 0x288876436773A316ULL, 0x55091F6C311256C8ULL
        },
        {
            0xD647196456568128ULL, 0x8FCCD83C865559E5ULL, 0x8D93CC73A3263A77ULL, 0xCCD39A26243C1BB9ULL, 
            0x2F5B8DC8BFF85018ULL, 0x47D255168CF63250ULL, 0x5C839E08DD8FC0F4ULL, 0xC13A3A62D31CDC5DULL, 
            0x91A3EDBE9A8FFB8BULL, 0xF6B4DABA148510D9ULL, 0xFA120EC770F6DB3DULL, 0x2F2A681A82E6028BULL, 
            0x4A4D2BC5B6C8C9F8ULL, 0x7E9E1CF58B0D7B95ULL, 0x014F9A92303C1136ULL, 0x686767EDC8CD723CULL, 
            0x99704673E9933A77ULL, 0x11DEA79ADDFA6347ULL, 0xB422D93D3A9E5388ULL, 0xD80EEC4541B9E5CCULL, 
            0x1C38A361F79484B9ULL, 0x1FC83D1C3257078DULL, 0x656378B0B55FCA2FULL, 0x597008D3210B268CULL, 
            0x9C087FE3525F97B2ULL, 0xB9DD81CE542C395DULL, 0xC4282502F6124738ULL, 0xB278FA832591776EULL, 
            0xC6A632634E66040BULL, 0x6AAED142F68B8E03ULL, 0x5FFB41CCEC5A5F74ULL, 0xE2DDB55E6B6BEB47ULL
        },
        {
            0xA73F061BBDB6FD37ULL, 0x0E1926FC8A53A0E1ULL, 0xE4A445A7586C9244ULL, 0x21AEC0EC7065EFA8ULL, 
            0xDF39D1515E80D42EULL, 0xD071400BCB63BAE7ULL, 0x74F00A7AD1A7DD84ULL, 0x457222AF05542968ULL, 
            0xF5DCF22D0493CC49ULL, 0x4BADEE6C00A3023CULL, 0x86E48EFA2572F700ULL, 0xFA5B29F44B1E822DULL, 
            0x12F53D8DF51255EDULL, 0x859331225E6C763CULL, 0x75EB21B15B9232A3ULL, 0x03D3167E54B4FC9FULL, 
            0x16F32D15A81CF950ULL, 0x3BBCFE482D48C077ULL, 0xE1905D9167690D55ULL, 0xBC3281DE94275D46ULL, 
            0x43E657A703E172EAULL, 0x1094943EA003EABBULL, 0x005F562C57127AB0ULL, 0xB335F1B00404B7CFULL, 
            0x151042EAC690F84EULL, 0x7B6FA512E235E3E2ULL, 0xE4499C19B557800EULL, 0xBE795D02E1FFB370ULL, 
            0x06DAB16253E6FEFFULL, 0xEC6BBEABA1B0A752ULL, 0x1395A9656CD417A1ULL, 0xF5FFA7477C5AB58FULL
        },
        {
            0x5A360086062F93F5ULL, 0xF448D001F0C410C6ULL, 0x55F549F1F8C42E6BULL, 0xA0FD38E4443641CBULL, 
            0x78FC977DDA0AD8A5ULL, 0xDF94318500217F7FULL, 0xCEBDC7D2ED2851D6ULL, 0x1644987E209F5FE7ULL, 
            0xA0FF3CF4916F5673ULL, 0xB6239AD04211A61AULL, 0x5A82C46A1A74B573ULL, 0x49819C19E3B5C198ULL, 
            0xBB8FACE5D25088E6ULL, 0xAC5516696E2FAEE0ULL, 0xD2C5938A5706038AULL, 0x5F5BA10614409FEDULL, 
            0x1215FFFEBF943E38ULL, 0x72D6234327643D28ULL, 0x19A6FFF729F0E103ULL, 0xF67E34292DB8761BULL, 
            0x4452414BBC6C5E26ULL, 0x29B45C02FF8C7162ULL, 0x637694ABA6770B6CULL, 0x19EC83D1CBF9C1F0ULL, 
            0x5C4C9A4550FCC55BULL, 0x530FAB4447A7F89CULL, 0x154C9639BADC1159ULL, 0x161E66DF2463720CULL, 
            0x905E8D7EE917B3F8ULL, 0x4EC02C5A85A8A3F2ULL, 0x269F52ABCD39EF20ULL, 0x211B529C35DD3CB0ULL
        },
        {
            0xEF82F2BA6E706EB9ULL, 0x5F9869499EFCC168ULL, 0xE028DFBD30B3054EULL, 0xA488489C4BDB7690ULL, 
            0x569EF35D5598EFDEULL, 0xD79B23EFD120C497ULL, 0xFBF8BD13049F8A8AULL, 0xF3464A3451638766ULL, 
            0xB75EB5F090A8E331ULL, 0xEAEB84DD2AEAC679ULL, 0xD4FEEA8186681D7CULL, 0x0BCE8BF963790917ULL, 
            0x5E8EAD3B24BC61C1ULL, 0x241EAB54DDA2279BULL, 0xAE526527525E2DE1ULL, 0xC66EF3F58ECEA85DULL, 
            0x12242E5F54982107ULL, 0x941109AA4E7B8DCEULL, 0x6CB99C7A47FB6B76ULL, 0x52CB591F7675452AULL, 
            0xFC5E38C3F154BD39ULL, 0x475D77CC009A565EULL, 0x6C6C9D4B1B82E30DULL, 0x00ADCB48440F087CULL, 
            0x11E28C9564541E06ULL, 0x9A28C93E6369B2CBULL, 0x31CAEF0674A14AAEULL, 0x1EB651CB3DE39216ULL, 
            0x25EAEC086512A9B5ULL, 0xD8363D77882E7FE3ULL, 0xBFD933377C3AB1D5ULL, 0x202F8894AC9C738DULL
        }
    },
    {
        {
            0x8BA904F0627A3931ULL, 0x73028F7457D4B8E0ULL, 0xF0F184320FEA1E7DULL, 0xB547C2EF9A814EA3ULL, 
            0x6AEC343830711452ULL, 0x6179C6D7E62FDDF2ULL, 0xB264500F840C3812ULL, 0x32A8A3440DDEC791ULL, 
            0x8786493F3F0081CFULL, 0xC38ACF18E840F331ULL, 0xB94A26B9151CE5FFULL, 0x04C5A3CAE7EEB12EULL, 
            0x9DD4C201084DD3A7ULL, 0x7077EB6CBC2E8AC7ULL, 0x64EC5A97549255E0ULL, 0xA707AF2D99D2E8C1ULL, 
            0xDEF8BD39D301E6F1ULL, 0xEA901FBDDA731776ULL, 0xAC5DC4263B028518ULL, 0xA0171FBD2AED8590ULL, 
            0xA5C0B7FFA35073FEULL, 0x895EE2664D082140ULL, 0xA76DCEEE1EE2D4D0ULL, 0x517AEFDC982D2EB9ULL, 
            0x212DEA1C0A0647E1ULL, 0x1C1C6FE1CEF14886ULL, 0x330175951D595FA6ULL, 0xC4CFE9D461DB9F64ULL, 
            0x24CF7F1E1AEE66A7ULL, 0x529F8CE2B7446266ULL, 0xAE588C0E9C5417DFULL, 0xB5AD3527EC01FE10ULL
        },
        {
            0x3818E3063BA14E6CULL, 0xAD89D7951C028112ULL, 0xCE3F7FA7D2D894C8ULL, 0x4ED75D012E600538ULL, 
            0xE7BDECB3868C2355ULL, 0x5319EB1D0C32A315ULL, 0xC663ED20507103BCULL, 0x26146F67DE16CDB2ULL, 
            0x58051DB3272B2059ULL, 0xF76F242295BB7262ULL, 0xC9ABCC24E511DBC1ULL, 0xA27C74B09294957AULL, 
            0x8D9FF4C111B972EEULL, 0x4937D657E5F9CD25ULL, 0x77D2E05F366B6241ULL, 0xCE93434A0C3EB578ULL, 
            0x994525F848658CF0ULL, 0xD60551539B6531A8ULL, 0xE37F98A3C68672FCULL, 0x43E79D94F00E1855ULL, 
            0x3126F48819022C2DULL, 0x4E9DA90EE9DF7E55ULL, 0x4E484BCC00C136D4ULL, 0xE7271AB0CA655F58ULL, 
            0xA727D6E086C0B71BULL, 0xF3B2633C7EBE77A3ULL, 0xC34F4493F7AC1773ULL, 0xF179726FB7EDE44AULL, 
            0x4DF845686C8C76EEULL, 0x6E083C1C364EEAC6ULL, 0x20F62F5B9A02BC79ULL, 0x87ED16C059E6EBF4ULL
        },
        {
            0x8D6498F4D29335DBULL, 0xB18A5416445BFDFEULL, 0xF6D8F7547FCF38AFULL, 0xE37933AF8937C485ULL, 
            0x28A10BA74A798322ULL, 0x8FBE20CE4F393272ULL, 0x899F74E97B95206CULL, 0xE8232DBF7F40A1B1ULL, 
            0x9255182D6DC9BD8AULL, 0x2BA869CFF4D4CE29ULL, 0x2E32B24B153F5609ULL, 0xA5AED3D4375AA18AULL, 
            0x1B08B79EE2ECFC75ULL, 0x24C0D22C6F0678BFULL, 0xD552ECC568124EA6ULL, 0xE040970C0D7DCF0DULL, 
            0xF0879F2195437A66ULL, 0x075BB75D5A7EE6F4ULL, 0x75AD3943E2D67042ULL, 0x2EB303D1530B0B96ULL, 
            0x2EA084BC4C135A44ULL, 0x89DB6FC12363923DULL, 0xBE7235161270B957ULL, 0x72535BC386ACC33AULL, 
            0x31A59C353DCD3EECULL, 0xF355BBE1A19C526AULL, 0x1DF459166EF38F9EULL, 0x217FAB44B5BB566FULL, 
            0x016AA6884B692896ULL, 0x3BC94E7A854DD13CULL, 0x07BB10473365FBB8ULL, 0xA2C71588BD0BB092ULL
        },
        {
            0xC04376F3192DD1B0ULL, 0x7A49EFCF169CB6A8ULL, 0xA925143165EA8578ULL, 0x876383B46F9329D5ULL, 
            0xA6DD9DF42E8B436FULL, 0xE4948D999BE1774EULL, 0x1918BFE81AC390DCULL, 0xB52D72534498153DULL, 
            0xA6D94C25203A3E07ULL, 0xDCAD6E4DA200F050ULL, 0x23490B0389F46308ULL, 0xB3A60F2270EC6DFFULL, 
            0x46387CD067FCC6FBULL, 0xA5F9B19B8C72DC64ULL, 0x77F4B6000FC6B1D5ULL, 0xBCB91676AD65AC6BULL, 
            0x29962A5163FE32AAULL, 0x50458D008E0AA9C6ULL, 0x39D29854A852A822ULL, 0x6985084B293935D8ULL, 
            0x89E12EFD74AAF44EULL, 0xE02D31D93DE71783ULL, 0xBDDA498289BDB6CCULL, 0x74F8219185A46AEFULL, 
            0xE7738E6DD74B4CBAULL, 0xB67B349538FD863FULL, 0x6635591DCBE85F40ULL, 0x246FF23A7F92ABFDULL, 
            0x47B25B711FEE664CULL, 0x08C80D0D628DE1A5ULL, 0x8457ECEB99A7681BULL, 0x3452F3C03C297D0EULL
        },
        {
            0x34359C99F9AF8AF6ULL, 0x860C7705D55D3E49ULL, 0xC58A18F625E10CBBULL, 0x0834906E455C262CULL, 
            0x746A5E8E42016A97ULL, 0x6F14A0241C7C879CULL, 0xFDB02F3C619822FAULL, 0xA9E3C308578B3FC0ULL, 
            0x61B55DB7AB46281DULL, 0x4742E0540B980C8DULL, 0xE6FC046340F1D724ULL, 0xFDA2F0E5AE50527BULL, 
            0x1F90E3188E5FBD2BULL, 0xE54B4B03B211C0ACULL, 0x0984064B489F211FULL, 0xD6AFAC132AA34227ULL, 
            0xD3A01A979999BD5CULL, 0x2A94AB03B472233AULL, 0x746A5E3DFB7AB8CFULL, 0x567D6414C8A613ADULL, 
            0x270C45FD57FA7EA9ULL, 0x656B62BD46B4883CULL, 0xAB4324B040CB028DULL, 0x281668CDB9C77D5FULL, 
            0xE117D04EB907D6E8ULL, 0xF3DF5D2EC1651AACULL, 0x6CB7731818E3F0DBULL, 0x9288F3B86ECC08D5ULL, 
            0xF283BA962D2B6036ULL, 0xA893FFEFDE2365D5ULL, 0xFEC345DC51083BC7ULL, 0x57528527EA6C403BULL
        },
        {
            0xC973D2B8DF721747ULL, 0x4B74EEEE07250D49ULL, 0x56F265DFC1C61159ULL, 0x41EF6C564F4CED6BULL, 
            0x58E8ABE5E2FD9E4AULL, 0x65CA4A5218706053ULL, 0xBBDCCD7E478D2C3AULL, 0x3ED6E0289B5E96F8ULL, 
            0xCF0ED25C20BE82FCULL, 0x0A6462D767E55A82ULL, 0x52A83C8CA26C5FAEULL, 0xFBC69426E0068B96ULL, 
            0x8F83387AD381007DULL, 0xFDA744D4D6985D58ULL, 0xA9068B938484F7CEULL, 0xF471209773270EA7ULL, 
            0x3C791E0D3A757DABULL, 0x758E8E2FA1C4A281ULL, 0xCDC11D1921922405ULL, 0x5E02082F48F7634DULL, 
            0xCB70FD3715B0B157ULL, 0xD125163A441F4998ULL, 0x20090989AD8C7F98ULL, 0x3105207633F40206ULL, 
            0x99FB5B0AB2B70B33ULL, 0x6CEBA4AD99D9BEE2ULL, 0xF2D4310C36C8225CULL, 0x6E26C188DD2EC527ULL, 
            0x9FDDBA6AC06B5B90ULL, 0x18859EC48C71720AULL, 0x613EF3DE06C59201ULL, 0xECB9A3D933970739ULL
        }
    },
    {
        {
            0xABD95DA6DB38E6AFULL, 0x00A898B40AC4D659ULL, 0x92DF680E42AC68E8ULL, 0xAC5A83CF4A9BD46FULL, 
            0xFE2498A951B2B672ULL, 0x6459C38DD5A67DA8ULL, 0x21CAF4D3DAABDA98ULL, 0x51C97ADA2BC3ABB1ULL, 
            0xF41E771726C03043ULL, 0x3FD9248784011FB9ULL, 0x755C970BC7408DF7ULL, 0x1599CD3FE8F5A4A0ULL, 
            0xF857F3FC003104DFULL, 0x19D92F138F98951AULL, 0xE78CA0B483135495ULL, 0xE3BE43AD5BD49BA3ULL, 
            0x2FFBA20030571E70ULL, 0x28AAB1F62ABC6DF4ULL, 0x59F6A297B16358A2ULL, 0x4FD93EA353F85658ULL, 
            0x9093DAB112D57690ULL, 0x17BD4EE1702F3C9FULL, 0x0AB9B7AC8A6048C3ULL, 0xAFCA153051E81BF6ULL, 
            0x342BCFEC3302C047ULL, 0x30A41934A07CEFB4ULL, 0x7D8F4129D8B79A83ULL, 0x4B328434A26F5660ULL, 
            0xB9A82E4F40176202ULL, 0x6D74C9B2285F77BEULL, 0x02C083F1A9E12CF4ULL, 0xDDF721EC6BAC1997ULL
        },
        {
            0x24A9EE77F96ABC5BULL, 0x7279C9AF08D24086ULL, 0x08F64EA67E6C2FA0ULL, 0x5A44185719765643ULL, 
            0x774E46F33DE726D6ULL, 0x28EBC18005136A53ULL, 0xD83AE3F8024BC507ULL, 0x068CA2530FB15070ULL, 
            0x43A97FB0BB1F56D7ULL, 0x35DD7C259B8BE889ULL, 0x59E1DDB884C39F42ULL, 0x052C4BA0F0DD4704ULL, 
            0xD0E9E8D324FEE975ULL, 0x77D4B485D4EEAE35ULL, 0x9B24C40497A965DCULL, 0x2512BCEE129309F6ULL, 
            0x9D85EAA6E50E0624ULL, 0x1595F9C346586AF0ULL, 0x764E9C952084E7CCULL, 0xF41FA276998EF2A6ULL, 
            0x375A416CC2E8B3EDULL, 0x73E79F135373AD73ULL, 0x737221F6B0A6DC0CULL, 0xB27D5F45906223FFULL, 
            0x39609FF4A226DBA9ULL, 0x384C0A5FFACFB486ULL, 0xDCA66E4E20DB807CULL, 0x567DFDF16D5944E6ULL, 
            0x389EB66E095EF7A5ULL, 0xD63F1C1B9CA8BDF7ULL, 0xE95EDFC262004C20ULL, 0x4ECFC65EC7F276A6ULL
        },
        {
            0x22B4F62EEB67DB7CULL, 0xEA43DC9177E02DA8ULL, 0xC68422B6093288D5ULL, 0xC9F167D5D4DA521AULL, 
            0x23C241EEF609A1F7ULL, 0x2C81781EFF846191ULL, 0xDAFB0BBC3851B151ULL, 0x0840C5781E5561F5ULL, 
            0xA4F65C729A582831ULL, 0x4009386F49F52F56ULL, 0xA42D2A013BB2AD81ULL, 0xC6066B7D40F0C35EULL, 
            0x2AD52EEBC7F4BBBCULL, 0x5F899A7D301194A0ULL, 0xDC44E0143BB0B83FULL, 0xA7A5F18DD44EE816ULL, 
            0x49778E09521F08D7ULL, 0x9E4E91B1205E09DDULL, 0xE60FA97F579F49DFULL, 0xAAC1797183FD240CULL, 
            0x02C9E99BF03D1BD8ULL, 0xED36DD0BB945EB49ULL, 0x579986BD8BFFF996ULL, 0x00FBFB6486E3E0FDULL, 
            0xBD76DF24D1E3DFA5ULL, 0xFF994546B7DD3C52ULL, 0xAC278942AC326067ULL, 0x237E3C76A5A91193ULL, 
            0xD928F7D495589B0DULL, 0x731412C7BBFC5A82ULL, 0x819C5732BA523AD5ULL, 0x830AB0A546AAE5BEULL
        },
        {
            0xB5B1A8492811EBE4ULL, 0x5C508673F74D11D5ULL, 0x6609987FDB42D768ULL, 0x2BBFE2258B976123ULL, 
            0x5B33B7AE6960E387ULL, 0xAE5DBBF4070819FDULL, 0x830E1E4F841BBF60ULL, 0x360DF9B526292730ULL, 
            0xD5B6AB946E32FA8EULL, 0xE431B17EE0292329ULL, 0x8A0DAC483448AAB7ULL, 0x59951054BF4D2571ULL, 
            0x887F427A181DEB6FULL, 0x071CED9DBB682835ULL, 0x658A48C73594AD7FULL, 0x8BA8FC52481F64BAULL, 
            0x4196FAF4AC4F8853ULL, 0x3911115A7B3FEC18ULL, 0xE07EB8C4020D8603ULL, 0xB498CA0F0F48185BULL, 
            0x397D210C460869A1ULL, 0x8ED4426BCA2D5071ULL, 0xCEFF3DE45EE09108ULL, 0x03D7B20237751086ULL, 
            0x3FCA340AFF82853BULL, 0x76D00D32E57D9633ULL, 0x6678E0C65BF09143ULL, 0xF9D3702FE89E6F44ULL, 
            0x31A5F20A355AC1B3ULL, 0xFBF73751FB2F2C2EULL, 0x11E02C58A51E80BFULL, 0x9D01D4C9C0350D7EULL
        },
        {
            0x70AB05BDCB08F1DAULL, 0x573FD59FD4ECD7D8ULL, 0x3397C483853D1921ULL, 0x5FC4EBB124DF780AULL, 
            0xFCB88EA65EB4C307ULL, 0x042C4AA8B6151AD8ULL, 0xD8BAB9748505B145ULL, 0x1F45648A0CC75869ULL, 
            0x3785D80B16235BA7ULL, 0x0E9F0091754C3DB4ULL, 0xCFDA6F48564DB02FULL, 0x5C8EFBD50147AF5BULL, 
            0x45342EC96738EE67ULL, 0x5AEAA1124E8C99D6ULL, 0x57CD38C8639320DEULL, 0xEF4D8EB8B2431B9DULL, 
            0x86C60FC717FACC7EULL, 0x6770EB6E80B20BBAULL, 0x3EEE4BADFDA7C5B6ULL, 0x9432652C5ECFAFCCULL, 
            0x702BB40493E2B0D5ULL, 0x3765441F43885725ULL, 0x86DB54D5583E1218ULL, 0x3A2BD6EBE7F3746FULL, 
            0x09970ACCE9556DBCULL, 0xADE04DD4B3A083F0ULL, 0x98455E81DD5ED3FBULL, 0x3B2B2641914834CFULL, 
            0x8034B7E2444FA798ULL, 0x1A2C4003A398B6F2ULL, 0x3357C11D07FCA971ULL, 0x5B899D0420A38BBCULL
        },
        {
            0x5E184D2A712AC534ULL, 0xF82388563CC54320ULL, 0xF1D1296FD54DCC5DULL, 0x1F1E50F720971C89ULL, 
            0x5FD95F16693010E7ULL, 0xFE9219036011E48DULL, 0x92EEFBC3CC35CF0DULL, 0x7E1E5A1EDEC4B942ULL, 
            0xE917C1DC406E016DULL, 0x42FF06CAF855770DULL, 0x425D111AA5866DA0ULL, 0x4CA2FA9103C70D42ULL, 
            0x9C17773B31F78683ULL, 0x9AD929AF92607249ULL, 0x89F38286AA3190D5ULL, 0xFE8DB6467AFDC6B1ULL, 
            0xB9F9CCD02265BB78ULL, 0x435FA93FC4ADBA00ULL, 0x1A6004E1E8EACE22ULL, 0x1E1D257C1196F6ABULL, 
            0x5A10D33E71E5CBEFULL, 0xAADA0E844871815FULL, 0xDA29812AB19568A8ULL, 0x32F02FD9375F1F0BULL, 
            0xB1737BEC71811A5DULL, 0x4AD72B33931A978CULL, 0x33A421F97032B131ULL, 0x608E67782C170774ULL, 
            0x50ECF524069E95AEULL, 0x6DF05C5EF922062CULL, 0x5EE6DF2FA28F2CC5ULL, 0x3623A075ADDBCE95ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseFConstants = {
    0xA7CD502800D10F1DULL,
    0x027C515F09D41C76ULL,
    0x43DA48BD336440B7ULL,
    0xA7CD502800D10F1DULL,
    0x027C515F09D41C76ULL,
    0x43DA48BD336440B7ULL,
    0x2986061DAA847BA5ULL,
    0x1C65820FBF0D2E48ULL,
    0xB8,
    0x29,
    0xA5,
    0x86,
    0x61,
    0xEE,
    0x84,
    0x2A
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseGSalts = {
    {
        {
            0x0E18FF33D8E1258BULL, 0x79F7BA51A7D0A7B1ULL, 0x3C714AEC44DA67ABULL, 0x6D57EB6306EA9BD9ULL, 
            0xB9C1C88D9D2E2383ULL, 0xC3E8B5D961A51BA8ULL, 0x67E473C30CB9949AULL, 0x374B265DD110A055ULL, 
            0xF3A9D0CA5AB1060DULL, 0x4A68A6141F72C016ULL, 0x0290F6342E21785EULL, 0x7FFE98C816A8FE97ULL, 
            0xB672F9772E753DFAULL, 0xDD961BA385D7EBA4ULL, 0x5EE251D2656C4ED8ULL, 0xD415236398B7D687ULL, 
            0xD171A37802209D14ULL, 0x893DC753203087EBULL, 0x9115406EE1E5F8BBULL, 0xD8914B195797F96CULL, 
            0x8E9409712B4DEF47ULL, 0x2F46DC56C0EC06CEULL, 0x4FC8FD8DF7A1332CULL, 0x75B9338867F5F56CULL, 
            0x769A3EB8CABFA20EULL, 0xCA041021496E8578ULL, 0xD18FF1F78B7B676CULL, 0xB4C36FFD7A1D8743ULL, 
            0xC104B7079A889B52ULL, 0xC6E1296DE5763E82ULL, 0x1D2897B157549145ULL, 0x42A2A083E124D5AFULL
        },
        {
            0xBA50C055A792A833ULL, 0x9E3B977A1F8B4F2EULL, 0x4E253E5BB8C24120ULL, 0x5FD9475D741C4650ULL, 
            0x875C4F2AAC1DCD6EULL, 0x84A8D0995BF80F15ULL, 0x622E9B4FA86C28EBULL, 0x926E825D7204B4C1ULL, 
            0x61B3936E8BCF8658ULL, 0xF0C7F65C1B586AB3ULL, 0x5BAC917265CBB08FULL, 0x2471C71DD3FC7149ULL, 
            0xCF6C10CE09F7A2A6ULL, 0x106DDCFC931AD323ULL, 0xEF6543A23B3F7DB3ULL, 0x95C93C823706B51FULL, 
            0x7650F91D59493094ULL, 0xE2BEC5AA68DF3C9EULL, 0x64E2791ACC975892ULL, 0x3DCC07CC5B4BD914ULL, 
            0x4AFB17709A78D74AULL, 0x02078F81E82F0260ULL, 0x18390AB9FE471BA1ULL, 0x365B367946B5D261ULL, 
            0xA2E29192FB9C670DULL, 0xBE48FDEC0DF6E181ULL, 0x67CC1D271EE9C577ULL, 0x4953C04604C413DFULL, 
            0xEA338FB1F75CA2F3ULL, 0xB6F5D192F3A6C844ULL, 0x26B7E7864F52BCCFULL, 0x409EFBE7D7DB0885ULL
        },
        {
            0xECD657876D163911ULL, 0x289DFFF0DA84F176ULL, 0x7C2F055EB6D775AFULL, 0xC46256E914D58DDCULL, 
            0xD847DF4F73041984ULL, 0xE4929A6E28EE8196ULL, 0x7CC7F509EC1A0E35ULL, 0x081BAE60DA8FEC63ULL, 
            0xB315C301C9F35CD6ULL, 0x72A9170C4758834CULL, 0x7A9BE4C04C7CCE9BULL, 0x509E99F492F03614ULL, 
            0xD7FEB8E80DF2B933ULL, 0x9B7514183DF3AFC0ULL, 0xCAF8BA9BC63767AAULL, 0x46765C95F2115C7BULL, 
            0xB00D300B2569A67DULL, 0xC07EA372F9A7166FULL, 0x12D613791D064173ULL, 0x93DAA18D90728AE5ULL, 
            0x2A25107156D199E7ULL, 0xCBA737B0E2919FFAULL, 0x001CF7D26639516DULL, 0x684E579ED651F7EBULL, 
            0xD92B24D2ABD02C3AULL, 0xE5FF77B1A491F2EDULL, 0x3F8E304F59010A96ULL, 0xA646CE39E3BF72BAULL, 
            0x50EEAF2BAFB4C098ULL, 0xC42DA198BB09F4ECULL, 0xDD5C6C0CC12CD885ULL, 0x63F5AAE4040E106AULL
        },
        {
            0x94397BF0C2589229ULL, 0x15DA41E555471D9EULL, 0x7C19F8F620FC24B0ULL, 0x36B2BF78A1CF1F40ULL, 
            0x82FE7A7B2CBB5039ULL, 0xE2775D73A32A5B30ULL, 0xE69BCADFA72B9C78ULL, 0xFC2027E0D3ECEB91ULL, 
            0x40E7AB5EABB1A74CULL, 0x9B7FA77AFE9A1D6CULL, 0x93F727F2D81CDCE8ULL, 0x0D5E31FC9145A449ULL, 
            0xB60D16417D02084EULL, 0x839F24170607A823ULL, 0x76608008E7AF02BAULL, 0x603FDA44C9639362ULL, 
            0xF27F320ED554E6CAULL, 0x3F3ABC4A5C1790B7ULL, 0x606488643675557FULL, 0x164ACC3B08C8FCB1ULL, 
            0x86EC66E26B8DFCAAULL, 0x6DA87F8D155F5B49ULL, 0xE41E740F4B6A6320ULL, 0x3B7ED1F6D31D366FULL, 
            0x34F02B6C4B0B7282ULL, 0xF9D52A24AD974E84ULL, 0x7F0EF39D3B731563ULL, 0x5DC34B9F0E6A2EEDULL, 
            0x6EDDEEB2777B0B01ULL, 0x88877BE38361CA3DULL, 0x03A1BABF65C8A56AULL, 0x2C976927B7E91596ULL
        },
        {
            0xDCA89F9BA84022B7ULL, 0x80A04C6B2414AA01ULL, 0x9E3E6ADF558ED99FULL, 0x29F109C41B1C51E2ULL, 
            0x5FF6B68BEF62A158ULL, 0x71C32F30F7D9F191ULL, 0x91DAF71E5FE26E4BULL, 0x1DDD02F152CF7039ULL, 
            0x6902B9F832CBD2B1ULL, 0x99EFF4095AE9EFB3ULL, 0xBFD4CBD3267F552DULL, 0xB3CCA1F1402A5A6BULL, 
            0x553F1F3EA85E9DCFULL, 0xA4E89FF7192CC3D9ULL, 0xA403D4DDC65187E5ULL, 0x6F5371E870BCD700ULL, 
            0x210F56B5F0BB4CA3ULL, 0x15A348F147EE6A4BULL, 0x9585C1AF3B710661ULL, 0x2EB04F7674099D19ULL, 
            0xCD560EBAE661678CULL, 0x69E3002F6C91C91EULL, 0xB431B23D035E5BC8ULL, 0x3A85D4511F04FCA6ULL, 
            0x13F4B348C70881D9ULL, 0xB3EB2EF3F5FBD962ULL, 0x5F3F7A1E314914CFULL, 0xC30AAB7BC8B9987EULL, 
            0xCFD3A44F5B771AF9ULL, 0x7559AFFF78AED3E6ULL, 0x0A3E2823467E4292ULL, 0x409527A7DA005F3DULL
        },
        {
            0x1ED1DC13B7353BD9ULL, 0xF5629DAC9862070FULL, 0xEF72773EEE7A423CULL, 0x7B0A27D00C4553CBULL, 
            0x97C0DB0C7A7B765EULL, 0x1E5D983064FBBE3BULL, 0x525EE31F2DF6E72BULL, 0x9F8CDA6617B65A6FULL, 
            0xCE040A66CBF5919CULL, 0x0C23859F9F6CA269ULL, 0x18609C345372E558ULL, 0x29570F2927FF714DULL, 
            0x3008EC133F1A695EULL, 0x340550BEA3A69926ULL, 0x20E1BD2D0C8D7F35ULL, 0x9DCE0E984A4365B3ULL, 
            0x0200A409FCD4FC91ULL, 0x63944F639150D27FULL, 0xC922D9123D0D0110ULL, 0xCB7FA479519BA381ULL, 
            0xB9BAE8BB21A454B8ULL, 0xAC9B91F4C5A9769DULL, 0x414123D630EA31D5ULL, 0xE7DCAC73FA3AF716ULL, 
            0x44652247F515E44FULL, 0xB6ED6FD0F3993BA1ULL, 0x1E6916B7D57AF458ULL, 0x514B7BCBE7B1063EULL, 
            0x1E37FBF29EAA7F2CULL, 0xED57EFB86868BA47ULL, 0xE18EAB2EF36F27C5ULL, 0xB2B2AA41D1FE51FBULL
        }
    },
    {
        {
            0xAC881E1412F3364CULL, 0xC2EFEE0A0D0D4F3BULL, 0xA165FFABC1E9489BULL, 0xFA0A93258AE0A789ULL, 
            0x5509C2E523D0AC5DULL, 0x5CC6CE38E0CCBA0FULL, 0xEF7586C6F5E8A169ULL, 0x35DFD4936EF8CE8DULL, 
            0x8AE2CA13ABF56621ULL, 0xDB725180ED2DB7D9ULL, 0x5C3C88730E66D930ULL, 0xF37FF6EB986641B7ULL, 
            0xF5E7FA48457BD4C4ULL, 0x4A644C6912D4660BULL, 0x973CD874F5F2E17CULL, 0x1C48C46EF62F423FULL, 
            0x937668AFDB17B7F8ULL, 0xB8551CDC82969B7BULL, 0x0D933EE1EAB21758ULL, 0x099FDB994770D260ULL, 
            0xF5F987E2F23EEEF1ULL, 0x68F276DFDB4E3B50ULL, 0x8C20327D71967927ULL, 0x484BAFAF6C2332B5ULL, 
            0xAA86B042C8B931BFULL, 0x5DA0AD724521E5CAULL, 0xCDC9B6EF0D9E8112ULL, 0xAC779D2655BC59C4ULL, 
            0x9AAB9658AAF4CB68ULL, 0x9ED84CF7843A2DF0ULL, 0x133067AA1D78B9AAULL, 0x8221158BEF472F51ULL
        },
        {
            0xCEEF16D6E72B704BULL, 0xB34E16C5098639F6ULL, 0x112D7DD80D5074FCULL, 0x75234E9D340DB367ULL, 
            0x2B64A5A1EC720540ULL, 0x617A774887572F45ULL, 0x6AF13945B472815CULL, 0x18B7957278CF5BCBULL, 
            0xBB8CCAD357D6F921ULL, 0xAB3EB6ECA7AF06D8ULL, 0x519DF8BE30D022A2ULL, 0x8EBE4B2536790739ULL, 
            0xCB7F39026D68F7F7ULL, 0xB47211BD4C17EB78ULL, 0xF93EFBBF0E5A2A15ULL, 0xCF8647FD7214A7E9ULL, 
            0x823362180BBCE660ULL, 0x0D3E89B45CB03B9BULL, 0xCB57FADFFC028327ULL, 0xDFE503D21CB2C775ULL, 
            0x53EB28E044BFF84EULL, 0xB212EE968DEF118FULL, 0xB2994CD01F01D70CULL, 0x1DF04A75642962A9ULL, 
            0x14AABEB15ECA733FULL, 0xFABE15A45DDFA1E6ULL, 0xF85EBE8FF4413F24ULL, 0xC8A48DBA4D160851ULL, 
            0x30DE16B2A0287B20ULL, 0x308F3D5747F3DD65ULL, 0x6E285ED29F9C680DULL, 0x0B76886BAB4E2D8FULL
        },
        {
            0xDA17A19EC586F12BULL, 0x4C24150136A22300ULL, 0x4C97825CFD3AB5D0ULL, 0x81887CBCF97DC64FULL, 
            0x9164362E66259B2EULL, 0x24A2EBEB77ABADF0ULL, 0x3AB097F35EBCD081ULL, 0x016C42B1AAF4EAB1ULL, 
            0xB9B4CDB445951A04ULL, 0x1D7D1451D6322797ULL, 0xE7F3569A5DD95542ULL, 0xC46D42595E6599A6ULL, 
            0x87B1C989E20D0E23ULL, 0xB3494E8831A76A16ULL, 0xE8EEDE050EB589D3ULL, 0xD85AB2121B5BBC52ULL, 
            0x1FB68BB0794AD7F6ULL, 0x751F75099C5F2630ULL, 0xDB293E46D05756FDULL, 0x6C6A6680A7B33DFDULL, 
            0x754D80A13D860A2CULL, 0xA4CD19A020B14C05ULL, 0xFE12D104EFB00B81ULL, 0x15C7DB48EC5A6ED6ULL, 
            0x3FC61A9EFDE5F43CULL, 0xAE10EDCFE114BE71ULL, 0xFCE766363D9F1B44ULL, 0x839A667A0D89994FULL, 
            0x961B7326F3F0C447ULL, 0x2E42EC0766C666E2ULL, 0x606ABED634145183ULL, 0x4EF39A60CCD7852EULL
        },
        {
            0x124C1BC0FE0874ADULL, 0x61E2DD9B6B534C45ULL, 0x47610A636FBDFD71ULL, 0xA4152987405BA59DULL, 
            0x6657E53AE57A211BULL, 0x9FAD63B357BEBC27ULL, 0xF54CF306C5BD3251ULL, 0xE2AAF0F82FE812A8ULL, 
            0x7C67466AA7A1508FULL, 0x43068CE1EEB603FDULL, 0x35F6AFC756E7A385ULL, 0xE72DB57B42949313ULL, 
            0x2CA0D12793815E24ULL, 0xF97920AAE32A7883ULL, 0x4F81A80957622CF4ULL, 0x51DA3CF958778043ULL, 
            0xE889111FFC88BC49ULL, 0x127C244631281D33ULL, 0x35C699D4029DDB8FULL, 0x527AA5BA729F6811ULL, 
            0x601F5FB0DF336C18ULL, 0xDA489BA43DA1C8AAULL, 0x98FADB6954FB9F08ULL, 0xDA4F088A407D17FEULL, 
            0x9BBE83798A15E8D0ULL, 0xC274953B29C5FCC4ULL, 0xD7F2A3C37C5658BEULL, 0xBF641E00AEB47E4AULL, 
            0x6A86B0C3C41ECC80ULL, 0x3F583FC3CA6F7CCFULL, 0xFA517BC50DF2FEB8ULL, 0xD30A220F17BA1E69ULL
        },
        {
            0x83F86EB6FAA01202ULL, 0x2A5FE8F1F7A2A324ULL, 0x8911213AA02FE635ULL, 0xFA03802A0B58CD23ULL, 
            0x7C8182DE0E6E8418ULL, 0x53CBDFFE85A6A915ULL, 0x13C5272B9F74F8E0ULL, 0x06D68BF082D6CFA8ULL, 
            0x145601EE77A80C03ULL, 0x8A547B2D07E533A0ULL, 0xA1D8C73F55FB6D04ULL, 0x72410DA17C294D47ULL, 
            0xFF2347C6A8D53BBDULL, 0x9FB65D92BD4D3149ULL, 0x70D4B95CA379AC84ULL, 0xBD7241FDD07AA684ULL, 
            0xE95283135C39255CULL, 0xC30EB36048DFB788ULL, 0xA63AB15ABD4B4C7CULL, 0xA245CA86324F3B8DULL, 
            0xCAB57B5C5015BD3CULL, 0x8FEA8AAFF8DFED0EULL, 0xB28856E13C22111BULL, 0x6AB4197A9BE7CAB2ULL, 
            0x57BEABD53F608AADULL, 0x3F5BA34C7E8BDCA7ULL, 0xD36FBD3D3C0EBC25ULL, 0x135E47FE6997B0A9ULL, 
            0xBA0588DBCC5FE8C0ULL, 0x7BA22F44B479A9FFULL, 0xD06EB418A39476BEULL, 0x92D06A49AF022B39ULL
        },
        {
            0x63BF5418CBE8F3A7ULL, 0xE0E42DBEC5F83BB0ULL, 0x2CFD14653EC58015ULL, 0x2D42BA722E521325ULL, 
            0x6E57CE4C7249E9ACULL, 0xFDA475496CA232A6ULL, 0xA7ADCA249C8E2A39ULL, 0x3FF3C5EEA0A7D191ULL, 
            0x7A039CB96FB78492ULL, 0x049F2EAF3240C435ULL, 0x78D68431EB129354ULL, 0xEACC83916C08F9BFULL, 
            0xA4B6359C27FA52ACULL, 0x3DEAA508A17A5B11ULL, 0x0ED4D4F87F67EDCEULL, 0xDB1C5586D7C4D3BBULL, 
            0x76680A60FDB246A8ULL, 0x3B784CC8763AF84DULL, 0x891C63C2ADC6863AULL, 0x0E934E60CB71B3B1ULL, 
            0xD6A9D841472A0443ULL, 0x620443E155DA44D3ULL, 0xFB614CDD679B554EULL, 0x989E16A104FFC138ULL, 
            0x0013EEB3E55F6AA0ULL, 0x5D7D3678C454C0A5ULL, 0xF68A168FCF1B82B8ULL, 0x3574464609850106ULL, 
            0x959917278F019700ULL, 0x6E126032EA3952C0ULL, 0xD10E150DC68A997FULL, 0x6BCE6073AEA77965ULL
        }
    },
    {
        {
            0x399095FA325F7EA7ULL, 0xCEB6DB06C56FF701ULL, 0x8A34B1F4DE336F27ULL, 0x36FDE87CC7D08219ULL, 
            0x81F101D4BF4BF441ULL, 0x5C56F3EBB15D7C7DULL, 0x9AD353A4E95E074EULL, 0xB591808993FC198BULL, 
            0x8EDF987231AF3058ULL, 0xEE637D4BE8D0AA0CULL, 0xAA4F68B2EAEC9E92ULL, 0x9007A160603511A2ULL, 
            0xD022616D579EE59CULL, 0xF7A7C10DD3243597ULL, 0xB081748926992F1CULL, 0x3CA2DF041EF7FA76ULL, 
            0x572005DCA9637C5EULL, 0xAFF34FBD57506A25ULL, 0x3584215E0186B0ACULL, 0x205295A6F2B66237ULL, 
            0x9E89ED929A8064ADULL, 0x418CCE56891E5AEEULL, 0x6D2B9B9F53D3AD32ULL, 0x0C0F2621D7E1C37DULL, 
            0x17D6E8A66BD49D1CULL, 0x8F656527609FFC2FULL, 0x4FD5F92D40C7DFE9ULL, 0x5CA5E6CBC2B92F03ULL, 
            0x190FD6C51DC0927EULL, 0x26212CCFBD797400ULL, 0x83A89DF9A1FC5F49ULL, 0x82C6238826EE7E86ULL
        },
        {
            0x9B9C8838CF9DF9AAULL, 0x6304AA9B6CBF1CB6ULL, 0x18E6522F919E1070ULL, 0x73D255B36EBE5EFFULL, 
            0x82E236D6A478CAF9ULL, 0xDAC4677B54C457B6ULL, 0x54D60A3CE8976172ULL, 0x9EFFE9456193C2DBULL, 
            0x63CF94C136073673ULL, 0xB20E9B4715179B0BULL, 0xD2FD1B591111E228ULL, 0xBE32E8FF9F1C3138ULL, 
            0xBE6D11CFF936C981ULL, 0xF8C833C738303B50ULL, 0xC7749C8FFF015813ULL, 0x44209FA4A32B0E1DULL, 
            0x952A67A1B8FB67B7ULL, 0x89F12623466EC11BULL, 0x0E9496F93DB971AFULL, 0xD1A0A597A04D3AE1ULL, 
            0xBA298165615B1C2AULL, 0xE5EEE9F63465C871ULL, 0x558B681D7CC9D166ULL, 0x82BAC0FB2181AD5CULL, 
            0xE193328484814C29ULL, 0x9A48ECB61E43D04CULL, 0x3296B90FDD611102ULL, 0x994F2D993CA44CE4ULL, 
            0x5512752CBD3DC430ULL, 0x8629DFD310062C6BULL, 0x283E7DBAD8A1A52DULL, 0xD7EF750A2EC44BDFULL
        },
        {
            0xEE05F1194E92AA47ULL, 0x18792BF725C5CA8CULL, 0x0FCA55F136BB388CULL, 0x4B670107C114786BULL, 
            0xE03900632B7A3191ULL, 0x48A624CC1EC2E024ULL, 0xFE6F3BBB0876A082ULL, 0x1E37AB2E3CD901F0ULL, 
            0xA763BF0E4DB4511AULL, 0x996F73FDFE9E1439ULL, 0x19A1E79CA135104BULL, 0x81EB2AE8376342E1ULL, 
            0xC7190DCD433BBCBFULL, 0xE77AC25EF9FFE7A1ULL, 0x274B4A30344AB861ULL, 0x5967D9AF224DE1F2ULL, 
            0x66BE55C68138E6B8ULL, 0x47871F4FA5157139ULL, 0xDC6A1C6DC9BECB91ULL, 0x5C02178AE2298D9AULL, 
            0xFCBFAC66974DF506ULL, 0x4BAF2D84D88A4334ULL, 0x8B002D03B85F86E6ULL, 0xCF9085EB4C765039ULL, 
            0x6EBA3407BDFAF68BULL, 0x071A2A56FB023BB3ULL, 0x2E098A85E9CEE949ULL, 0xC41CF43D2E191130ULL, 
            0xEE0DDB25A10E8ACAULL, 0x7D3391DAE7ECC670ULL, 0x0E2A433CAE4938EEULL, 0x0F6EF8881434B48FULL
        },
        {
            0x19D9A77346002063ULL, 0x1B156488FD049C68ULL, 0xAF487C53148198FEULL, 0xD9CDA9595B5A5767ULL, 
            0x475C51FB5F453CB5ULL, 0xDF8C16F4587DC37FULL, 0xB2FD554353A69EF8ULL, 0x0BCFD44E4AAB9B35ULL, 
            0x6E7323DBD7B44FF5ULL, 0x95C6ED91EAF59592ULL, 0x062901D7412686C5ULL, 0x35F7CCDBCC7F16F1ULL, 
            0xA8AD6CE09468B99AULL, 0x90CB8192456895F4ULL, 0x756C83D521690265ULL, 0x9FD9BD270C3E05FEULL, 
            0x9FFDF3F46C855EA2ULL, 0xA5AEC99D5E0C79E2ULL, 0x522B96A34DC9AE85ULL, 0x6F4CC3A4BBF39ACCULL, 
            0xC420B40C02E14D6EULL, 0xB1855F1F107754FEULL, 0xA334406022445883ULL, 0x92756DF3A2ECE2B5ULL, 
            0xB25F782147128FD3ULL, 0xF1C67DABA7A88FD0ULL, 0xF6F0163C459F1D2FULL, 0xBF43BCC7A8595D73ULL, 
            0xEB7E8013D5E3C32AULL, 0xDC60F6719AD8C848ULL, 0x350F2CBB7E0C0DCAULL, 0xD55DAA948A277EA6ULL
        },
        {
            0x22F43D681F752DE1ULL, 0x572E579A5B962C40ULL, 0x24969F8EB86D53D9ULL, 0x2AA2485FE83A6D14ULL, 
            0x751F98FBB84E0FC0ULL, 0x576DE7FB33CEFA4FULL, 0x3C3DDC9C1E7F8516ULL, 0xF334D533CFDF5CAEULL, 
            0x0770824776E0E9B4ULL, 0x4FEB813E7DF51A42ULL, 0x46A6F414415D57D1ULL, 0xAFB400CDAF0D5473ULL, 
            0x8771860A5EACA297ULL, 0xC66CF6D99DC1F5BFULL, 0x1434B5207EBA5E4DULL, 0x725596F8AE41683DULL, 
            0x5DE3511BCBE709B6ULL, 0xD4027EF3BEF6885BULL, 0x3D6D1D03A7F8EA30ULL, 0xFF3336FF3CBB8B25ULL, 
            0xEE4B5771CF247CE7ULL, 0x1D436D81DDB9CFCEULL, 0x39C80B03AD7D4AEBULL, 0x935F35E3A06A5412ULL, 
            0x25239CFEA088686FULL, 0xBB2BB3714936E70DULL, 0xBD3A96BA88E0C102ULL, 0x0A6C3B276E53B2F6ULL, 
            0x5D37B2E0492E38D2ULL, 0x282508D5B7D0A664ULL, 0x3485C0EC560AB32BULL, 0x094B5001BC1F9AC5ULL
        },
        {
            0xF6C0CC73B1734B83ULL, 0xCF5691ED2AF4F750ULL, 0x3A52D96548062E36ULL, 0xE774E8C68989B1C7ULL, 
            0x02B0E615B3D5E7FAULL, 0xD02FAA74FBA87117ULL, 0x88F808BBB533AB99ULL, 0x6C7063EE70B757F6ULL, 
            0x2404B44DB2DC5496ULL, 0x04A0CB1FE7202326ULL, 0xFDEE8E3C8928BA72ULL, 0xB82D8252F60FFB1BULL, 
            0xFFFF5F3D934E7F3FULL, 0x594EFBC6A4DBC005ULL, 0x2C3702EC3E8B80D5ULL, 0x3E685A101D3D220BULL, 
            0xE7C2E2C2F58A0D49ULL, 0x9B2E12B869774D43ULL, 0xA9E8E625EC17A59DULL, 0xF5DFC5D659059CA4ULL, 
            0x826731AE75FE0DD5ULL, 0x767365C746EFED0FULL, 0x49D2F00F477BAE36ULL, 0xEA913FC3DBE78412ULL, 
            0x151F1414515C4CF2ULL, 0xF861249C9541407EULL, 0x3F0390C00D80C12CULL, 0x50E55FF7877E0FADULL, 
            0x986C96A6E87525BBULL, 0x00EF35A7D587A51AULL, 0xA4E4F919C1459A80ULL, 0x3B5CE051528FD4CFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseGConstants = {
    0x8A7E9662BA7C44FBULL,
    0x49388D9EB253863CULL,
    0xFE8B7855A1425BE3ULL,
    0x8A7E9662BA7C44FBULL,
    0x49388D9EB253863CULL,
    0xFE8B7855A1425BE3ULL,
    0xACAD237ADD374338ULL,
    0xD7D4CFC60970BE08ULL,
    0x93,
    0x3C,
    0x11,
    0x8E,
    0x99,
    0x31,
    0x4E,
    0x96
};

const TwistDomainSaltSet TwistExpander_Mebsuta::kPhaseHSalts = {
    {
        {
            0xFD4C2D063322082FULL, 0x747FAAABAF407A8DULL, 0x2FD1915CD322D0E4ULL, 0xCCC128E18A57EC6AULL, 
            0x9F2A5A56844874DDULL, 0xFA98BE2F0741D226ULL, 0x4B726F6205AF93DAULL, 0x0F443E3CDF3B09B3ULL, 
            0x09E774911A1A063FULL, 0xBE65156ED54EDFD4ULL, 0xB715A0AE103AE13BULL, 0x87AA0F506A8BC623ULL, 
            0x1A1DAF48382652B0ULL, 0x23124A2329AE8D72ULL, 0xCA7328E821D9B3A6ULL, 0xFA4602DF718C015EULL, 
            0xC6CC087CD96C0D73ULL, 0x5E6EA3B8DDBB2B52ULL, 0x08BF0A51DC618D50ULL, 0x4523A36EA72C770DULL, 
            0xE538A8C9930E6100ULL, 0x9DF045B16041C595ULL, 0xA7A2C49E765E9F59ULL, 0x57AAA3C69081F076ULL, 
            0x3BA26BF959456EB7ULL, 0xD324493DA20058D6ULL, 0xF682F58FD296B208ULL, 0xDF5021397CAF2EDDULL, 
            0x15BE33DD65F77F99ULL, 0x83214A14EFCAF129ULL, 0x1DC0F8C7092B9E8CULL, 0x1C0B824A9D4D3C8CULL
        },
        {
            0x3B1790AD3278A048ULL, 0x1438CD8C03D3B128ULL, 0x42484AEE22A2D810ULL, 0x7F00E90D477E5215ULL, 
            0xC34B9812B9008C71ULL, 0x973D904D0BCBFE24ULL, 0x18C298EA1534B411ULL, 0xA2F4330BFC67B8E0ULL, 
            0xF6A9241F0BFE4357ULL, 0x2731EC05E51891C2ULL, 0x89B133A11F2D1FEEULL, 0x8FD08EA0A95929C1ULL, 
            0x8A328A618B5AFF3BULL, 0x4D92F3A4E63E1B38ULL, 0x8B4FCDB7B041EFA3ULL, 0x7BB4F3E9691196D9ULL, 
            0xA7D317953AAB339EULL, 0xB28E5764557F7D8EULL, 0x74DF80F9E9BB8A9CULL, 0x12822C1EE97587E2ULL, 
            0xE1EC55BDD09A8E8AULL, 0x3FA1FCB427C021E9ULL, 0x05C8DF3D5DC81E56ULL, 0xFCE3102716FCA9C1ULL, 
            0x7C5628C423355476ULL, 0x25B6F4313B3823D4ULL, 0x45CAD9E43AFD2B42ULL, 0xF648B2B6558B51A0ULL, 
            0x3F72DBC1311B88B7ULL, 0x052357C983F0B168ULL, 0x6F031EC69392943FULL, 0xBDA67A4D8BDD07A5ULL
        },
        {
            0x6D8C76A3614C91BAULL, 0xA8E97114B036BDD1ULL, 0xAB7639D34B2C7D1CULL, 0xDEA085E256722FDAULL, 
            0x3D1D52E001B0754BULL, 0x22890778F0028794ULL, 0x46D09DA410CF14FDULL, 0xFC5E57DF775383D6ULL, 
            0xC60B8B7F514A006EULL, 0xF6A2FDAD21EB304FULL, 0x98FCEED3523FC2B0ULL, 0xE66D6AEEA285B8AAULL, 
            0x6B835612FF507F9EULL, 0x26F9E0E9D111804FULL, 0x933A638635038F6BULL, 0x3BD7D834A339435AULL, 
            0xC843B14C84151892ULL, 0xD7DCC4F8CED5A6F2ULL, 0x48DAF2C67974EC33ULL, 0xA33A2053C0375593ULL, 
            0xEBF61EB8068AE14DULL, 0x5988C640C9239783ULL, 0x95F7C50F0B1B78A5ULL, 0x1AF24AB6D49662C3ULL, 
            0xAE3C8A427C201232ULL, 0xAC02C85031E2BAB2ULL, 0x309DFE34A1E102EFULL, 0xE955DE7CEAAF94AFULL, 
            0xAA0D4DB758D80A2BULL, 0x9BE42F202BD7FE35ULL, 0x02BF6898511D86B1ULL, 0xB12F47C3A88FF2BEULL
        },
        {
            0xBAE9052F8C41A900ULL, 0x9CE6FAA657A50597ULL, 0x620F5953934F4264ULL, 0x6DB52080B5D29D93ULL, 
            0xD1B6791458C7C4DAULL, 0x346E80193C716408ULL, 0x1A3C27E580EA0207ULL, 0x16C1BEDE2B6F1A92ULL, 
            0x9D55EAB41A1249B8ULL, 0x8F12995B09B89A6DULL, 0xFC9F448BD5A066A5ULL, 0x4025D09ED31A1A85ULL, 
            0x00E181F3DC683AB2ULL, 0xD8485AAB7CA88F4FULL, 0x9CF081B40F465ACAULL, 0x7B594D35C7CDEAB5ULL, 
            0xD77E3EE0BF80D7E1ULL, 0x209F1D282FB1A6A2ULL, 0x3F1158DD3FD53EE0ULL, 0xBA4BC46F48F93CB5ULL, 
            0xA1B0ED4D7422A3ECULL, 0x14EECD08A5BDF5EEULL, 0x6157A2FDE11860B6ULL, 0x18A7A48B5D2EA212ULL, 
            0x481AF40C4F96FCB6ULL, 0xF37F9C5B347292B3ULL, 0xAA3C11D6AFDE51A5ULL, 0x2C34A3BE6E93CE91ULL, 
            0x57B3E4FF52447EC5ULL, 0x28CC8682C6AEF1B4ULL, 0x173D7B03AA00ED30ULL, 0xD315222F4527631AULL
        },
        {
            0xD8027C7E0C34AA00ULL, 0x6359ACB6222A9285ULL, 0xE2DF8C5AFC7A49D4ULL, 0xA8D20807426B6F9FULL, 
            0xDD128F54C167B6E7ULL, 0xD6CCF79961AB03EAULL, 0x0ED95F76EC6D1B2EULL, 0x215CBF169E0A5A80ULL, 
            0x4C9E65522BA047D5ULL, 0x4016F8BDFB7590BAULL, 0xE3F2166D5CD7B5F3ULL, 0xC3B40E22D08D5804ULL, 
            0xE545DC2153BFCAD7ULL, 0x1A2ADCB7F9CD96D2ULL, 0xA96D3521E3AE3618ULL, 0xF141BAA6ECCB30B0ULL, 
            0x4105046332311DB0ULL, 0x5B3191C5CF2EA0E8ULL, 0x75F1707FEF7E7B74ULL, 0x6A00049E1625CB41ULL, 
            0xCAEEC389AB08E1FAULL, 0x6040FC45F8FB9F28ULL, 0xC322E8839C45FFEAULL, 0xE978C0DB7E460824ULL, 
            0xF26A632F18225AE2ULL, 0xA24A72EA82FB14C7ULL, 0x56E1965EA9E33389ULL, 0xFC556CB0FAAFCD9FULL, 
            0x041ACF1E85C8DE6AULL, 0xE91937AE89899983ULL, 0x7DD01FA79298407CULL, 0xA64AC5F47D7D3A30ULL
        },
        {
            0x8B12846D2D145464ULL, 0x0745948BC604B5A8ULL, 0x32EE80FAAB79B8D6ULL, 0x10B4B4225A0C0788ULL, 
            0x0363B9D93987EE8EULL, 0x689FD3BC9A0B89ABULL, 0x02948657306A06B7ULL, 0x9F819686433F73D9ULL, 
            0x6CABF3220A0F8348ULL, 0x2F165DF70E080C25ULL, 0x48721E7354D84C0CULL, 0xABCFB1EA800A590AULL, 
            0x4B88CA81E2158B0FULL, 0x7B4672E9D0C38C50ULL, 0x7DE83681B03B5850ULL, 0xE6B6858E5834E3D1ULL, 
            0xDE44091D3F4A2AB9ULL, 0x65A5C1A7F7A46D50ULL, 0x7D5306167441F261ULL, 0x8ADE63B958596A14ULL, 
            0x400EE12CC4534910ULL, 0xA1C48CCC2BBE8774ULL, 0x729223B19F17377CULL, 0xC015F37DA1B5792EULL, 
            0x23E37B0B1DAE2501ULL, 0x8DBC07AEE173FC64ULL, 0xAA82557FEBDD1651ULL, 0x4505F49DE6821B18ULL, 
            0xFF1033B23ED6AFD6ULL, 0xEE558DFD75989B3DULL, 0x99669A8CAF2B378EULL, 0x9C771F524E8D7E90ULL
        }
    },
    {
        {
            0xE6F450A9C6D28BEFULL, 0x05FEAC047B2291E2ULL, 0x934ABD5E58DD78DFULL, 0x15A97FB6FAE24660ULL, 
            0x8F7CFF7AD1680507ULL, 0xF48D28B954BAB6E4ULL, 0x46E9DDFD7EF5F891ULL, 0x71B4674BB390517AULL, 
            0x3C5DBC67C582B089ULL, 0x2E0E9426077A58FCULL, 0xFB1F648D08DCED7FULL, 0xBC37FB5EBAACD016ULL, 
            0x00E3824EDDFC7D5FULL, 0x81247A81BB2CF6CAULL, 0xC44153B7984BE200ULL, 0x8C6F51286430ADB1ULL, 
            0xA2775F51F2F01317ULL, 0x639353B44C5FA8A5ULL, 0xE74A8A245395B8BBULL, 0xE2BCF54CF01F4E19ULL, 
            0x7070349CF4732B3AULL, 0x252D0ADD74D1186FULL, 0x95699EADD60F4084ULL, 0xB20B1B5E9C665ADAULL, 
            0x0D91BCC26030F3E1ULL, 0x1708B1E8C886754AULL, 0x750DAE3224918B5FULL, 0xBCB589BF52839867ULL, 
            0x6B1DDF4680F51001ULL, 0x47A7851DDE336A74ULL, 0xF319727AF0324E9BULL, 0x038E55862F46D001ULL
        },
        {
            0x0F97F6DD014DC911ULL, 0x57797DF3299C4783ULL, 0xDEB30D22FE9A7624ULL, 0xEF6AD7DCD3B4F5C7ULL, 
            0x0F2E15EC4C3072EAULL, 0x449A74E273620B5CULL, 0xA7905BD66F7FC0A5ULL, 0xE5E5955B84F8C84DULL, 
            0xE128F4AFC43727BAULL, 0x4DC5146D75B00F4AULL, 0x02CE04EFCE9993D9ULL, 0x10B3BE01C4DCD2A7ULL, 
            0xCDD618084E6E391BULL, 0xE58FBF6A254FBDE8ULL, 0x1398DCF1EF7C9118ULL, 0x6820E8C0177AE7BBULL, 
            0xEF1F00425B51AAC4ULL, 0xE928EFD78C5FB283ULL, 0x9F101862F8945C89ULL, 0x0E0AC8557108FBE1ULL, 
            0x86F2EF8C5818E47CULL, 0xE7039847D8D33B9AULL, 0x7A11DC2534D6364AULL, 0x19EBCF3F40897093ULL, 
            0x952A95B58F762B27ULL, 0x02914F0B70264382ULL, 0x7032F8691B184122ULL, 0x26FC835B0332E854ULL, 
            0x69FFFF49EABE60CEULL, 0x112E596F0A9C4998ULL, 0xE0F8F98DCAFCDA6EULL, 0xC0071845D1FABEC9ULL
        },
        {
            0x4CA1B8E56D671D18ULL, 0x16CC7A808D260577ULL, 0x729B89B7FCF5603AULL, 0xB6FD63862A4E85A2ULL, 
            0x332241DA16FF1C24ULL, 0x0D16923B72283347ULL, 0xB3901880E9D40B15ULL, 0x09A397A91C0300D4ULL, 
            0xA7727AEAE020C916ULL, 0xA77586727B3F37B3ULL, 0x9B430A31BFDDD3E3ULL, 0x89F3D4A0EA1DDBD8ULL, 
            0xE38268568E41063EULL, 0xAD72F8272F01A448ULL, 0x40760A0509BF05CDULL, 0x3274F42CAAE7740DULL, 
            0x095BA1C5D9D74B64ULL, 0x4AB6EF596EBC3C94ULL, 0x2DD6205514B1D4F8ULL, 0xB636A5E7296713DDULL, 
            0x1018ED9F84E5E9BCULL, 0x9671AEC0ACCF1B03ULL, 0xE6BF1A1B21FF50B5ULL, 0x97F4CBE37191614AULL, 
            0x28614C7FBE78731CULL, 0x6D2625BFDB25969AULL, 0x694E4D89B7F00F5EULL, 0xECD93BDD97008AC4ULL, 
            0xFC1C07FC4A0908E2ULL, 0x3E4DEFE289EEE186ULL, 0xF1EBF1079A1E8E4AULL, 0x42B2C82E917E8736ULL
        },
        {
            0x71D78F715484507DULL, 0xBDE09227E1CEB724ULL, 0xB2FD92E4AAFBBAB0ULL, 0x5BF7D50E786EF06DULL, 
            0x2D2D6571D123959CULL, 0x69659F635F2D59D3ULL, 0x434AE3A1880CCCFFULL, 0x2738647D50887259ULL, 
            0x21AC01C32470DFA1ULL, 0x7649E5FBFA71BAC3ULL, 0xE4CFC1A99FBF774AULL, 0xBA8F219040833C38ULL, 
            0xF553AED14CD98983ULL, 0x63A58E4A69F786EEULL, 0x228757BE373FBC81ULL, 0x3638DC3575C51334ULL, 
            0x9859D986580C027BULL, 0xE30409FBD25F3C53ULL, 0x502576B75EB68D2FULL, 0x910A71D8B986796CULL, 
            0x8705AB9D4C443510ULL, 0xAB7400CF455D19A3ULL, 0x740C2853CBA65607ULL, 0x27687332B3ED4E9CULL, 
            0x6B814852C5F1FE1DULL, 0xC4C0B5B1B9ECC7A4ULL, 0xCD79B2FFC943626BULL, 0xFBD83DEEEC06F2FEULL, 
            0x8FDBC20636D15ADCULL, 0x6A919DB4D4854ED2ULL, 0xAB54154E7C465464ULL, 0x87195551CB08C245ULL
        },
        {
            0x5180329DA507A7AEULL, 0xCDD84F7E68E74CEDULL, 0x4849F89066EA0D45ULL, 0x13DD367E689F62BDULL, 
            0x6C8FC7B23EBE132AULL, 0x54A5811308BD20C8ULL, 0xB3B379FC1368153AULL, 0x023DE4377C9C88CAULL, 
            0x5E512BAFDD2A241CULL, 0x348943AE5BB03CC5ULL, 0xCA90E90C331BA787ULL, 0x180EBFB7A1F8769CULL, 
            0xE69D3BD0EB33A529ULL, 0x3F296CAEA9379157ULL, 0xDCB135E4E83B594FULL, 0xBA29DB05150E0FD8ULL, 
            0xA5D9D146E0E70314ULL, 0x112C6D9FC2CF8827ULL, 0x701649E59A246B9CULL, 0x6CE81C49C6EBB3DEULL, 
            0xB0C0FD490EEC6156ULL, 0x3703CC20EF3E3A26ULL, 0xA32C1049F4908F73ULL, 0x2711C687DFD216AFULL, 
            0xC4B9407127A4C451ULL, 0xB0557FE395F91236ULL, 0x03900ECAE888495BULL, 0x637456FB5919CC93ULL, 
            0xC08E49C20C4D597AULL, 0x98BC9C2B21FE21E1ULL, 0xA2823B64BA4BBB2BULL, 0x491687DFBED885CDULL
        },
        {
            0xE890FD3D1AD04276ULL, 0x108D50FBE40216B8ULL, 0x3C0824E90500ED9FULL, 0xAF9D6088CA910D83ULL, 
            0xED230B1F14030CBCULL, 0xE8C1FAF5C078D580ULL, 0x9B1062803EB77662ULL, 0x53776A3E556D2FEFULL, 
            0xBFCBF37AC51BC68CULL, 0xB436B0785B44CA6DULL, 0x05512BF635B44E3AULL, 0x9DC7E6B206C9B45FULL, 
            0xF250198BC38B2DD2ULL, 0xE12C18395A61EE6BULL, 0x8FEAD89F30A05B55ULL, 0xD1D4F7AF1BEEACBAULL, 
            0xE5BE690F565A422BULL, 0x7C7B2678A9EB47D1ULL, 0x9B97E55C3E487FEFULL, 0xC52EED73F9683348ULL, 
            0x79F3D721D7EF8F3DULL, 0xC110BA3658288430ULL, 0xBD3D8BCE1E7CF811ULL, 0xB28FD9E03CC9C941ULL, 
            0xC945838752CBDF06ULL, 0x8761638A05D2D119ULL, 0x437926D4C559CBDAULL, 0x86EAF8EC3EB3AE01ULL, 
            0x2058C699FA39C0F7ULL, 0xD1109685BA166BFAULL, 0x9C0FA94F99277AAEULL, 0xB51AE6D93D0FA204ULL
        }
    },
    {
        {
            0xB6BC884DF0676D1CULL, 0x58A01A1130D22D17ULL, 0x861D25CE36F46C23ULL, 0x89A01AC736EB3400ULL, 
            0x403898448B4129E7ULL, 0x7A17C1A328182C79ULL, 0x46BB05DA8570B2FAULL, 0x90785910CD2D463FULL, 
            0xBA41F7BA206956ADULL, 0xF8638F77E544D2ABULL, 0x0DFD0BE8ECE5CB4AULL, 0xCBD6384C84CF679AULL, 
            0x1DD4DC78CBC854A4ULL, 0x3B7866157147A42BULL, 0x3DB8545F08235F2EULL, 0x6F17000E6627F850ULL, 
            0x79C7C55D93B47D04ULL, 0xA0DD004B541DF80AULL, 0x988759A3E3F1DE94ULL, 0x2BC00374FE3D1D71ULL, 
            0x2C7716B52B527329ULL, 0xB49F0DB2B8668278ULL, 0x1F02AB6C06BB61F9ULL, 0xF3ADAAAEA8B67140ULL, 
            0x86758EF525EC00F4ULL, 0x540188F0679D996FULL, 0x84393D838BB926B1ULL, 0x5919B7BA0261057CULL, 
            0xC76ED9D552A7D50DULL, 0x36B75F223DED7881ULL, 0x3B133DBC291B09DCULL, 0xB4A2DCDEFEBD0A68ULL
        },
        {
            0x7E928B58CDECA706ULL, 0x4F19EA49C45177F1ULL, 0x90AD3939CAFC1939ULL, 0x8B2FC43D23B4320EULL, 
            0x6D86A4E5D5BAD892ULL, 0x451FBD24783BFECEULL, 0x5AE2BC7DA567CB24ULL, 0x6875D2414424AFE3ULL, 
            0xAED789D8AC1A264FULL, 0xF8CC141F42FAED3AULL, 0x497E6518ED5E042AULL, 0x70D49FED58B04ABDULL, 
            0xD0195B4B1009F9C9ULL, 0x945BCB4917D11877ULL, 0x1A6742621A992E73ULL, 0x5849CC39D1900D07ULL, 
            0xBB0D79C5D3FFA426ULL, 0x63F491A490398A88ULL, 0xA3D92461950DD3D9ULL, 0x009AB481D13AE9DAULL, 
            0xCA0F717684FE8785ULL, 0x71FCB24366F1E647ULL, 0x68416F9E6E2EC6DBULL, 0x0F98B129EA257915ULL, 
            0x9229611640A0DA49ULL, 0x9A1F5DE54B053D30ULL, 0x4A3002EFC685B80DULL, 0x486A43161A004D53ULL, 
            0x9F4BA75163651858ULL, 0x2CA8F1A9297941C5ULL, 0x9FAC84F387EA08A9ULL, 0xD207ED1F683B9C0BULL
        },
        {
            0x59020B47BD1921DFULL, 0x406FCAA46DCCB505ULL, 0x24BBAFE73052B9BEULL, 0x5C1E9A4348444364ULL, 
            0x6A2571FF72D77EA8ULL, 0x62E8EAC45DE8DC07ULL, 0x33CF68641017ADF3ULL, 0x47CAE6CB66C992B2ULL, 
            0x1747E79E391A82AEULL, 0x0326AC831D3041C4ULL, 0xC6F78D8544CDEF5EULL, 0xA365AB1FCFFA0027ULL, 
            0x02065583D47955C4ULL, 0x1CAA35736D515946ULL, 0x4FECAF8439AEB451ULL, 0x74108B9E094724A9ULL, 
            0x72FA7DE984F8BA9AULL, 0x2C4A18F29BA2B05DULL, 0xF89C817BBBD65CBEULL, 0xE83D5169F8E07E86ULL, 
            0x164549156D3D04A8ULL, 0x7193D51B787F425CULL, 0xEA50D6C15DC66F53ULL, 0x70C456E4964FBD36ULL, 
            0x2AFBD9A475D9677EULL, 0x652D447B2F05154CULL, 0x8FD2690B345C0B66ULL, 0xB67EAE8AD85C983DULL, 
            0xF088F612FD7DE0A0ULL, 0xCB63CCA3D5197A8EULL, 0x1EDAA3DF22D67A58ULL, 0xB89BF2AD9EB09703ULL
        },
        {
            0xC217270DD6D15933ULL, 0x29E397EF6BC8F97AULL, 0xCCFB8B425466AC68ULL, 0x6D461DD04E785A58ULL, 
            0x0590D45659DD2F3EULL, 0x6E0B05C5466AC934ULL, 0xCD2AD676BD2BDB93ULL, 0x3D7C45A4235B3907ULL, 
            0x1A434A191FDD3A16ULL, 0xCC8DE8E7478E5C60ULL, 0xDA87E1695A7828F2ULL, 0x43A03814DC5C22A1ULL, 
            0x3C51318A809F41F6ULL, 0x04E296A4C01A31BFULL, 0xF799E132B204DF06ULL, 0x3F4D77115DE57610ULL, 
            0x29F8E43B3037BB2EULL, 0xEAEFD56B163EF039ULL, 0x029C5B4AFBB1F62EULL, 0x22FCAC495C66DB55ULL, 
            0x7782898A9E979D1CULL, 0x00EB17E0CED3F07AULL, 0xAA0D90140520C458ULL, 0x0ECB7C2C82FECBE3ULL, 
            0x78B70F1C72A1E39CULL, 0x0E0C02AD6D87E646ULL, 0x7FCBC3745B843188ULL, 0x0D3E6D27A3B8133EULL, 
            0x0BB742BBFFE37E9FULL, 0xA586DC19D448AB2BULL, 0x5DBF8B29DE9F2FFAULL, 0xA35B94ADDFFA1123ULL
        },
        {
            0xADF6AE1CB150156BULL, 0x03BEC43DDE133CCDULL, 0x89356F742B8DE265ULL, 0x6A6DCF5981DFE715ULL, 
            0x08F9967C54F1B71BULL, 0x5A67E51DC13E24CFULL, 0x4B871B1B0F612309ULL, 0x6B40BCDED538E086ULL, 
            0xFAECCDF4E05FC725ULL, 0x4644DA3C0EED7515ULL, 0xF3B0B998F933A400ULL, 0x1E30FE3263B09A45ULL, 
            0x127EF6FB180F154DULL, 0xEE0B2B49B5A22540ULL, 0x1D21E8460427C5E7ULL, 0x3F59BF885C374118ULL, 
            0x5BD3F2C4FC97EEE0ULL, 0x96437866199B5922ULL, 0x457B85632086917AULL, 0x0AFF6EC86526A39CULL, 
            0x764D04DEF9E44E1BULL, 0xAA3DEA0A2B5D615EULL, 0x89F04D9826CD1463ULL, 0x8A8F0293A638E86FULL, 
            0x99E3D82458AFCF9FULL, 0x71D323F5D686F783ULL, 0xFBE4DAF7642F92E3ULL, 0x7A95CC7F78B86FD0ULL, 
            0x25F42292A279FB4BULL, 0x40526AB5EF3FFEA7ULL, 0x50A2C3578B058BE2ULL, 0x5D942B3BFA6163E6ULL
        },
        {
            0x2C551C99ECD878E8ULL, 0xCECB75AD62ECC830ULL, 0x2A9B914C6ED1D7CBULL, 0x740A748A7F277ED8ULL, 
            0x8A62B6E62F113357ULL, 0x9147FC5ADE8A54CDULL, 0x53BC64DB31475B03ULL, 0xCD0F869B27F270DCULL, 
            0x7B3621E6CDA75C01ULL, 0x4E615D40701DB5B9ULL, 0x5B8DD1EA8C471553ULL, 0x948577B3DD044CAAULL, 
            0x6302DF157741AA09ULL, 0xA88081FA4362E1FDULL, 0xCF9E660A1D56D8A3ULL, 0x4898B7CB6C232AE3ULL, 
            0xEC769514CFD68D0EULL, 0xB0853E3DC464AC2DULL, 0xEDE6B5890D6272E6ULL, 0x71767017101A9DD0ULL, 
            0x00691963414278C8ULL, 0x2F94147A7D51C80BULL, 0x1F393677609C0F39ULL, 0x4336912944D90B82ULL, 
            0x76834C65251A708CULL, 0xC3C7D9967156BD99ULL, 0x0F5EA0A438091F48ULL, 0x1DEF358FA2CF0A32ULL, 
            0x552559FC1D6751FBULL, 0x8A9ECBB92E12C4B7ULL, 0x59EDC300A160DD7BULL, 0xD6508881D89C8948ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mebsuta::kPhaseHConstants = {
    0x5313A747C29CE6C6ULL,
    0xB60C1F6C92A12F43ULL,
    0x929121661CADAC98ULL,
    0x5313A747C29CE6C6ULL,
    0xB60C1F6C92A12F43ULL,
    0x929121661CADAC98ULL,
    0xDC6E84F529265DF7ULL,
    0xEB2886F8E5B542B6ULL,
    0x19,
    0x54,
    0xC5,
    0x05,
    0xB6,
    0x96,
    0xE9,
    0x0C
};

