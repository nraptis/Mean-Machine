#include "TwistExpander_Aldebaran.hpp"
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

TwistExpander_Aldebaran::TwistExpander_Aldebaran()
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

void TwistExpander_Aldebaran::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD54B707945471673ULL; std::uint64_t aIngress = 0xE115E51C344DBED5ULL; std::uint64_t aCarry = 0xF9CB5EDA1A64DE61ULL;

    std::uint64_t aWandererA = 0xD1EC08012D198E07ULL; std::uint64_t aWandererB = 0x8D0979BA03640789ULL; std::uint64_t aWandererC = 0xE1362AC7C2181999ULL; std::uint64_t aWandererD = 0xB913AE255950057BULL;
    std::uint64_t aWandererE = 0x9ABE626D8F5A4785ULL; std::uint64_t aWandererF = 0x81B9CC348AC75C56ULL; std::uint64_t aWandererG = 0xE589C47BE199B073ULL; std::uint64_t aWandererH = 0xBAC591E194E1BA01ULL;
    std::uint64_t aWandererI = 0x9404987744E2E809ULL; std::uint64_t aWandererJ = 0xBE191827E08E5C60ULL; std::uint64_t aWandererK = 0xB2062E66EDF52EEFULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12862036036876478758U;
        aCarry = 9670347750467393239U;
        aWandererA = 16585600796093714720U;
        aWandererB = 10359651173012539894U;
        aWandererC = 15026603384401385761U;
        aWandererD = 13078450220897445864U;
        aWandererE = 13268552868910486690U;
        aWandererF = 17960803158991305393U;
        aWandererG = 10249916490378639301U;
        aWandererH = 14121591303994411981U;
        aWandererI = 18367261899273108246U;
        aWandererJ = 11034973639604796579U;
        aWandererK = 13090615257977829553U;
    TwistExpander_Aldebaran_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Aldebaran::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xDD918E35A50A4599ULL; std::uint64_t aIngress = 0xE1DE061F78DE4F4DULL; std::uint64_t aCarry = 0xC3CEBEB9B8237EC5ULL;

    std::uint64_t aWandererA = 0xB9F1A1EB6D46510DULL; std::uint64_t aWandererB = 0x8B7D99724D52DD45ULL; std::uint64_t aWandererC = 0x8142F5CA346D948BULL; std::uint64_t aWandererD = 0xC39ACF2CD8C80923ULL;
    std::uint64_t aWandererE = 0xDC6EC34B7FC59A96ULL; std::uint64_t aWandererF = 0xDFE2A23E65C2F605ULL; std::uint64_t aWandererG = 0xFAE5FD3158FC919CULL; std::uint64_t aWandererH = 0xF430B1D61C189F77ULL;
    std::uint64_t aWandererI = 0xAA3E296FA4F4BE23ULL; std::uint64_t aWandererJ = 0xAAE52B14C4D6FC43ULL; std::uint64_t aWandererK = 0xFC5402EC63E7ABDAULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17280824448775974671U;
        aCarry = 13998640153196793996U;
        aWandererA = 18342641800741747098U;
        aWandererB = 13386147853400097640U;
        aWandererC = 11425431126779524885U;
        aWandererD = 16066610636974591650U;
        aWandererE = 14695398429100433869U;
        aWandererF = 15231056398641667947U;
        aWandererG = 10262659748578021447U;
        aWandererH = 13761249166906375431U;
        aWandererI = 14961259794155213630U;
        aWandererJ = 12451922858759229193U;
        aWandererK = 10381283205951834170U;
    TwistExpander_Aldebaran_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Aldebaran::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x8702555563506767ULL;
    std::uint64_t aIngress = 0xDF27ADF571AB8AF1ULL;
    std::uint64_t aCarry = 0xA5DD56E8AC8A1AA0ULL;

    std::uint64_t aWandererA = 0xFD9875E9AC8820ECULL;
    std::uint64_t aWandererB = 0xD26FD2BDE8C80AA4ULL;
    std::uint64_t aWandererC = 0xAE43B188365D71DDULL;
    std::uint64_t aWandererD = 0x8CAB6DF37B15B211ULL;
    std::uint64_t aWandererE = 0x97263BF42655ED97ULL;
    std::uint64_t aWandererF = 0xED9B2C7BD12EDC5EULL;
    std::uint64_t aWandererG = 0xD0005FA926164587ULL;
    std::uint64_t aWandererH = 0xEF3DB6D6CB3BE483ULL;
    std::uint64_t aWandererI = 0xEB363F96D7C8CDF6ULL;
    std::uint64_t aWandererJ = 0xA0BD99090A6FF73AULL;
    std::uint64_t aWandererK = 0xF6AC649FC82B24B7ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneC, 2);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneC, 6);
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
    TwistExpander_Aldebaran_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Aldebaran_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 3 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1972 / 1984 (99.40%)
// Total distance from earlier candidates: 3944
void TwistExpander_Aldebaran::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 834U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1388U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1207U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1376U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1275U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1674U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1678U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1593U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 841U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 916U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1186U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 637U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1431U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 216U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1910U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1211U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 118U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 256U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1410U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1319U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 721U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1626U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 676U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 476U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 720U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1072U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 280U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1358U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1532U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1832U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1725U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2017U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1306U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 659U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 890U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1394U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 288U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 92U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1089U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 786U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 307U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1544U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 24U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 525U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1065U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 572U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 800U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 264U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 826U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 384U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1624U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 814U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 671U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 673U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 840U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1383U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1259U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1281U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1770U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 809U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2006U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1822U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 508U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 870U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1463U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1892U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2028U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 820U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 550U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 166U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 717U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1330U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1514U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 956U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1823U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1884U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1125U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 972U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 451U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1831U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 670U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 388U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1716U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 276U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1262U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1865U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1918U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 767U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 942U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 587U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1115U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1642U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 186U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 817U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 142U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1806U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1913U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1702U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1078U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 793U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2007U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1807U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 458U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 798U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1857U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1174U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 643U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1922U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 638U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1861U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1480U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1401U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2014U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1212U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 930U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 401U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1345U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 35U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1978U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 91U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1500U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1097U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 159U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1782U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 194U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1183U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1943U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1355U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Aldebaran::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xAEC0FB771690F296ULL; std::uint64_t aIngress = 0xD85ADC3BF1D7827EULL; std::uint64_t aCarry = 0xC2926E6F1E1BB24BULL;

    std::uint64_t aWandererA = 0x958C70F13DA7B66EULL; std::uint64_t aWandererB = 0xE1600CF268F60D53ULL; std::uint64_t aWandererC = 0xD811228961009416ULL; std::uint64_t aWandererD = 0xAEC8FE7AF6E579BFULL;
    std::uint64_t aWandererE = 0xA4D9E741298E743EULL; std::uint64_t aWandererF = 0xFEBF66BC5F6BD9B6ULL; std::uint64_t aWandererG = 0xB90B768EE55F3465ULL; std::uint64_t aWandererH = 0xA801CC338C914EABULL;
    std::uint64_t aWandererI = 0xA0C12ACFD01D41E0ULL; std::uint64_t aWandererJ = 0xDD375709BC103CD7ULL; std::uint64_t aWandererK = 0xACA9FF223463CCF8ULL;

    // [seed]
        aPrevious = 14197471763495866864U;
        aCarry = 15313824609483265741U;
        aWandererA = 13113867144655480652U;
        aWandererB = 14478749262087313899U;
        aWandererC = 15514576901317291811U;
        aWandererD = 12725834664901970788U;
        aWandererE = 12419496114631719953U;
        aWandererF = 11671937872490656344U;
        aWandererG = 11626495513674495231U;
        aWandererH = 11405661351525570586U;
        aWandererI = 14214759660900279649U;
        aWandererJ = 12043247430522162345U;
        aWandererK = 9833425496556150019U;
    TwistExpander_Aldebaran_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Aldebaran_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Aldebaran_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Aldebaran_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 3 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 1249; nearest pair: 621 / 674
void TwistExpander_Aldebaran::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6151U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5385U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2269U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7480U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2933U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1918U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 115U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1389U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4992U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2319U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1744U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1261U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6179U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2642U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3980U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2861U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 171U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1833U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1809U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 396U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1786U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1881U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 412U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 325U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 417U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1663U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1736U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 311U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1455U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 991U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1516U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 482U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1165U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1619U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1975U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1090U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 3 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 1264; nearest pair: 625 / 674
void TwistExpander_Aldebaran::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7379U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5386U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5488U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3742U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3373U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1706U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3008U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2680U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3365U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2183U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5087U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2746U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7724U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5297U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6966U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 695U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 690U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1082U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1057U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1307U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1352U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1851U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 817U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1887U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 33U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1102U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1598U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 423U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1159U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1187U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1696U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 356U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 2036U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 250U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1176U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1497U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseASalts = {
    {
        {
            0x7FFC409A7A5406A7ULL, 0x1C446CC69742516DULL, 0xEC0FDC29833FC7B4ULL, 0x507FB4042B8E57D0ULL, 
            0x6F1A30FE71EB7A03ULL, 0x3477C75AB71BD07AULL, 0xF38CF74BE637EAD6ULL, 0x01B11FE6A5427ED8ULL, 
            0x073B3AAF106F0111ULL, 0x9711805F1C51D317ULL, 0x1BEA44239E9C0DE0ULL, 0xC3B20D04F2347F00ULL, 
            0xDF4BF8DD8A14B8B3ULL, 0x468267925C8C756DULL, 0xDDA1D55F38B2FF2FULL, 0x9A7286AAD4C24532ULL, 
            0x033899979D0359D6ULL, 0x06B84B5519022CB9ULL, 0xFFDF503430DC4942ULL, 0xAED7AA0EF17CA443ULL, 
            0xDC1640330DF3D7CEULL, 0xC219C38F7685F9D2ULL, 0x8CBA076A4C6417ECULL, 0xE204190D81E9C83DULL, 
            0xF5D173F5D43C6945ULL, 0x14BA45B3C45559F3ULL, 0x0563B8A1616F8E9EULL, 0x190AA90C316E83DCULL, 
            0x595DB999419B1653ULL, 0x6EB627661437AE6EULL, 0x8AFF19E73A7C38EFULL, 0x9F2540C0BB635BE7ULL
        },
        {
            0x1FE52A10801FA312ULL, 0x85160399422FE321ULL, 0xE848E6F7FBE1330EULL, 0x28B899855C873052ULL, 
            0x96760FD54281C614ULL, 0x50DA49A739702DFDULL, 0x263AC40628DF775DULL, 0x4BFC0571F3D5D01DULL, 
            0x9806A84B4C0510D3ULL, 0x35FA78F001DEAEA6ULL, 0x876A044569C4EE43ULL, 0xB1EF69AA9A39E46BULL, 
            0x030C803D31F854CFULL, 0x0E1A2A9A99540CE4ULL, 0x906DC2C2F94E2A59ULL, 0xC6E96AAE7671FC16ULL, 
            0x440246BD7F906DF7ULL, 0x8BECD8673FAA3E98ULL, 0xE081B8A1E6D0BDFDULL, 0xE06F6427CB9241ECULL, 
            0xA59322A19101E2CBULL, 0xC4A98145C064195FULL, 0x022A634FC5F10C2BULL, 0xBEF26B6E9B6F9023ULL, 
            0xDF2716968B2F2140ULL, 0x5C95AA251ED76449ULL, 0xDA4E9A859C1C029AULL, 0xAB0C32C1AD37CC43ULL, 
            0xF239DFABD6665760ULL, 0x2F853770F1D717F1ULL, 0xDA4E3DB27D11EBF1ULL, 0x434609CF284B1D85ULL
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
            0x234191C51984D150ULL, 0x4AA6257F60FD2A1BULL, 0x12CAB6F840E45798ULL, 0xBB0529C0FE8AE0B5ULL, 
            0xAFD21000255370CDULL, 0x2BDA0C6C1C2FFFF1ULL, 0x71F70F8B4390D8FDULL, 0xFC68950188F55FC6ULL, 
            0xFDB2713B078B76BAULL, 0x3C3D456379146D6CULL, 0xEDC9029FB571610DULL, 0x4759F8127BE3E044ULL, 
            0x5826E6C471682CACULL, 0x0AE3249DDB4B51D2ULL, 0x689E2ED5C0FF745FULL, 0x7B3E854628CDC55AULL, 
            0x09CB1430BC91CE88ULL, 0x8757E8EED07560D0ULL, 0x0B8F84C93C5FD432ULL, 0x7484BB4583129E0CULL, 
            0xDAD62E09BE19D0BEULL, 0x6461AA644335B76EULL, 0x5B6DE571460C6B20ULL, 0xB275EB241EE48F2DULL, 
            0x7A7D7FD69AA1BA5BULL, 0xAA67434BD0758138ULL, 0x15EE69436ABAEC65ULL, 0x387A0BD79C96FCD4ULL, 
            0x7D4C1D096B373571ULL, 0x4567F97D5336D6D2ULL, 0x2C708902007920FAULL, 0x552DA744ADE5B233ULL
        },
        {
            0x07F5084DAE54459AULL, 0x1B693F71402EF0B8ULL, 0x7DDB694D51AC0C42ULL, 0x37BC83B9795E6F71ULL, 
            0x5CA9FDB0BB8323D7ULL, 0x34C01BA2A9A84C66ULL, 0x6EF261D11087F0A6ULL, 0xA489B6F7D2DA2CBEULL, 
            0xF4CD394B5C1DE59FULL, 0xB965038325F6EB62ULL, 0xDE081093BDA444B3ULL, 0xD0245CCFD50C3019ULL, 
            0x75FE567AB9F3DCEDULL, 0x96A8E7A1753C8615ULL, 0x0C3FB6C8E1F98384ULL, 0xBAFF0E68E9A73070ULL, 
            0x69AB04DD5BF6DBC7ULL, 0xF5F443BA47823924ULL, 0xF70B9411D0E679E6ULL, 0x715F32349D31B956ULL, 
            0x679AD180991B468AULL, 0x5387D071A21A3154ULL, 0x3043BDFCD7849C16ULL, 0x26914FE79A1A10B7ULL, 
            0x7200649B276F35F6ULL, 0x08DE2F7097385DDDULL, 0xDEA715565BB30423ULL, 0x195E89621F49484CULL, 
            0x5802CD55C385A9EAULL, 0xF7917AF6BE79DBEEULL, 0x5C753741F9A29350ULL, 0x1E522BC3D5BA1F6DULL
        },
        {
            0xB0F7F0EC186DAEE8ULL, 0x2D5A09FC2BCF7E84ULL, 0x6F57186AC09FD929ULL, 0xF68BC31DAA54794EULL, 
            0xBC5785CDF77795C9ULL, 0x6914BD4231043D44ULL, 0xE21FCF453D247ABEULL, 0x93A526738514A56AULL, 
            0x7D123F3C9A326822ULL, 0xDC2A5898E4B82DE9ULL, 0xAA70E3109E72BCA0ULL, 0x9C83098114DE26BCULL, 
            0x97F686B9333A4786ULL, 0x8B98EC9AB207B2CDULL, 0x0FC64F5FFDDA2288ULL, 0x28542402F9D9CA73ULL, 
            0xBA2D9DE664B8781EULL, 0x30E2427CBF14DE54ULL, 0xB3FD7FAF472B29F6ULL, 0xD859484897B5C543ULL, 
            0xDC8FE15632B5E0C1ULL, 0x55DEFBF38C52A615ULL, 0x45DC8400B7EC84FBULL, 0xF8C40699F47411FAULL, 
            0x3A55B67EACFCF9BAULL, 0x35D3A7B9C29DCBE2ULL, 0xD7E778F3797E00FDULL, 0xCD52AC2A09B3ED39ULL, 
            0xF36102E7F6A01E5EULL, 0x251B0E828A7C619DULL, 0x81707D373972127AULL, 0xF45AB3E727B98559ULL
        }
    },
    {
        {
            0x77E07C756F522A31ULL, 0x1D4C7EBC5D4B1ED8ULL, 0xC20833D82422124DULL, 0xD3CAB7A2B0AAD052ULL, 
            0x70A07B616FF3F2E9ULL, 0x0CF6F39A951CFF14ULL, 0xB4301A66A3EF3586ULL, 0x8FE58B74B1B27052ULL, 
            0xB46544064E01D901ULL, 0xF1C2516E19FF3370ULL, 0x83B22689C8D5CEDBULL, 0xE204C71270D8F9EDULL, 
            0x14BA7588C5F9FFE0ULL, 0x4B4CCB5D1C32CFC2ULL, 0x8AF98BFBE713FEBBULL, 0x89DAE6C6C632890CULL, 
            0x5E624B248C6CF235ULL, 0xFAED7F85542E95A2ULL, 0xB3B0DD28EF546EF2ULL, 0x1E278B4D4D285756ULL, 
            0x4ED35ED800EAF332ULL, 0xC41A3B1074EBC060ULL, 0x3B783467E03DF0C1ULL, 0xC9EB9CEF7859A573ULL, 
            0x9FEC8B37DF71704CULL, 0x1EC539B1CB0E27C0ULL, 0x94EBBC723B2FFCE4ULL, 0x551900FBF13B9529ULL, 
            0x23FA618A160CACCAULL, 0xCC483CE57906B314ULL, 0x18EDEAD7C1A71834ULL, 0xD090C4B29BDEE7CAULL
        },
        {
            0x570DC1B78690930FULL, 0x3B9C77948EF4DCD6ULL, 0x0BA04E6C667ED7F1ULL, 0xB3522C820A96C4A6ULL, 
            0xF6F523E20152C53BULL, 0x1A07DB65E7328B2AULL, 0xCE5CC4A8B08D0929ULL, 0x0A05C995A924C034ULL, 
            0x587CD1B244496FD3ULL, 0xCCE47C6A93353E1FULL, 0xB5A2A546C7B9E008ULL, 0x1C6980F16FCF2EFEULL, 
            0x6B4805D6727347A9ULL, 0x43162DECC0D2F1BEULL, 0x35AFD2E1B20FEC10ULL, 0x2D9232FB2FE868C1ULL, 
            0x397674AE502E5C07ULL, 0xEE7EA170146B72B7ULL, 0xB44930CD0C8A7D67ULL, 0x862E3024C72137A5ULL, 
            0xA80E7CB0D4283502ULL, 0x27B8A272314DA13DULL, 0xDB31378D1C3CFBDBULL, 0x2322308516642397ULL, 
            0xF0D84FBD9E2A05A5ULL, 0x523BB51053F093EBULL, 0x67F84EFD20916447ULL, 0x506B8ADC47F8512FULL, 
            0xF0CC53ABC692B0E3ULL, 0x4B06C123AEF59159ULL, 0x0472E40CC62DC859ULL, 0xD9A5907B856FD001ULL
        },
        {
            0x5F547678D05B8848ULL, 0x823570263988001FULL, 0xDC780C7EAA8FDAB9ULL, 0xBCC56E952B88E7B0ULL, 
            0x912A28A646DFDB6BULL, 0xFD0E3B13BF56F0B4ULL, 0xC4291F9667A74BF4ULL, 0x9EF6E98A85391FE6ULL, 
            0x30F56ACF29339D7EULL, 0x2CBB2C5E7696A92DULL, 0xD82EF75299B479FBULL, 0x4EA25C551A2BA585ULL, 
            0x89AFB6EC3F8BCC6DULL, 0xBB81065347588B53ULL, 0x5C08F536D6A21565ULL, 0x294696EE2F0A3F9AULL, 
            0x706FFB47DDFF8E95ULL, 0xD2E2096516A8138FULL, 0x2EBFA79308D72FCEULL, 0x31260266414C8C80ULL, 
            0x91F579EBA71DBED0ULL, 0xD0D9967494B55E2FULL, 0x5C97946C697B177CULL, 0x81F44A6E5283B00DULL, 
            0x3A6810F62D85AF6DULL, 0x9E63B9A5780B7B56ULL, 0xA403E536EBDA9984ULL, 0xA00B8EBA4C5681DFULL, 
            0x5DBD847069190E5EULL, 0x390B6C48832B37B0ULL, 0x26D0DAF9095033D7ULL, 0x8ED014458B70042EULL
        },
        {
            0x6A50C299255ED947ULL, 0xAFA359470B1BF835ULL, 0x719FF2951073C65DULL, 0x02C0CDF9C80CAAB8ULL, 
            0x18D4C542F35FDD44ULL, 0x6678C72AF02A380EULL, 0xA53732E93401FBC9ULL, 0x3E7467A5201DC341ULL, 
            0xD4C730BC89EECC26ULL, 0x9C384AD70DB073A4ULL, 0x809619E9F8AB9139ULL, 0xCDF6B4B2339E04A8ULL, 
            0xF11D3D356FE93B51ULL, 0x503BDDB6EE55928FULL, 0x64E86FEDBD69D65EULL, 0xB5ABF80A75CB1373ULL, 
            0x5441AF180CB971B1ULL, 0x65030D7DCD05CDDFULL, 0x3F84FBB8249EC9ACULL, 0x2199AB5FD662BA79ULL, 
            0x72FAF3E125259D91ULL, 0x3AA0E1B4FEFC2BDAULL, 0xB7281B9FD4EC8B2BULL, 0x268400C0BA040FEDULL, 
            0xBE4E5003F6A5FDAAULL, 0xEC1939392AE83ADFULL, 0xBA7BCB13142DD9BCULL, 0x013AEBA8746DBA55ULL, 
            0x455E36BF3CC13A75ULL, 0x7D59828AF071284EULL, 0x9A3498745E332F3FULL, 0xD17E56C220F2AFE7ULL
        },
        {
            0xF696B2C504DFB16CULL, 0xBCDEB8B8B993D698ULL, 0xB01F1EA4FA6238E2ULL, 0x729224D648590CB1ULL, 
            0x94C6D7FE6E0EB479ULL, 0xEED58E69F0ACC65BULL, 0xFFC9AA86639F3024ULL, 0x669DE09E0DD848B9ULL, 
            0xBF10867E6AF2FF8FULL, 0x56E4C7BAABFB5E3FULL, 0x0229439AF33092D1ULL, 0xA3EF8FBA18B90EFFULL, 
            0xF9BD74295C9F0178ULL, 0x16F732B05DD3D74DULL, 0x6B97E55CD9BC31FDULL, 0xB18FFBFC57648FC3ULL, 
            0x40CA3B98BA73DDA6ULL, 0xE06D2AC36D441D51ULL, 0xF34A0672E426D5DEULL, 0xBD0340BA3DFC6355ULL, 
            0x8556186E2E23F114ULL, 0xB080828CF2E49DCBULL, 0x04C133603BECE3F5ULL, 0x5CB2B3379F75283EULL, 
            0xC5D913B8839EBE6BULL, 0xA0A9AB7DE20D3790ULL, 0x04BCDD7EA462EC14ULL, 0x5A8C7F8164411AB0ULL, 
            0x2B53354BF0ECAB2BULL, 0xAFBED92E554A9572ULL, 0x4499B7863475A35EULL, 0x650863F4625B815EULL
        },
        {
            0x4A5143C04DB0C5CBULL, 0xA565FA4A7646D35EULL, 0x03AF632A123396E3ULL, 0xC1C94BC1C92A047AULL, 
            0x88717727BFC7F6DCULL, 0xCD04A5E0AFA51315ULL, 0x75523F1783B35AFBULL, 0x10C6AC1A7F298D75ULL, 
            0xDD692822A2855748ULL, 0x8EF3208995619225ULL, 0xDE89FEB88C38B6D7ULL, 0x8FC3D132B9BE3C7EULL, 
            0xAF7177ED10C6F721ULL, 0x040F917551D215F4ULL, 0xDA95E0AB7D073DCAULL, 0x9ED090B48989F078ULL, 
            0x946A7EA4F3F3E465ULL, 0xADFA05DB1D6B284CULL, 0x46C62B98CEF0AA02ULL, 0xD1D3D486E1CD730DULL, 
            0x47EF040421BA4CF3ULL, 0xC3EE3F2AE5AA2D72ULL, 0x3839F50644F8DB6AULL, 0xFB83A28E7D5A8768ULL, 
            0x5FD46CF8622A9B48ULL, 0xBBDCB9AE34ADBA12ULL, 0xC77AC816B1A2857CULL, 0xA1958A6C48954C10ULL, 
            0xE6234A3D3DFA2247ULL, 0x79F32F70A5331696ULL, 0xE6DF4C1B3BBA9BECULL, 0xACEF9A6BA6F67306ULL
        }
    },
    {
        {
            0x46F7B1697A54B1FEULL, 0x13A6CB67DB81D748ULL, 0x5DB1A1716132E20FULL, 0x1D510E242402684DULL, 
            0x44D7B360DD55021EULL, 0x0F27869E5CF5F70CULL, 0x2F600B402DAB5CCDULL, 0x126D583368905B98ULL, 
            0x9DD6AEFBF3689DB0ULL, 0x3EC17069AFF43958ULL, 0x95E11022EA4C4B82ULL, 0xE67D5EC4F13769BDULL, 
            0x096A15148ED964EDULL, 0x1D2B8E4622C3D118ULL, 0xD6891751C0A8500EULL, 0x4267F085A1529981ULL, 
            0x51332E00192A4907ULL, 0xC54B1E36C96D4EBDULL, 0xEB665EE304167593ULL, 0x004E3EF922C65936ULL, 
            0x42995CF827D0FF87ULL, 0x6BB47CBB3A03D899ULL, 0xFCA59DC41DC8C737ULL, 0xC01162D3EDCED7C2ULL, 
            0xDC338B383CDC8B33ULL, 0x574439D5FBE0844AULL, 0x83AC5145A35A7E50ULL, 0xCB5485DBA1D78D5FULL, 
            0x3BA2930C96C31272ULL, 0x8F08BB8C44B3D4D6ULL, 0x9198D19B60CC56B7ULL, 0x801900E04E3D9CB5ULL
        },
        {
            0x2C5EA7CC118A0FD4ULL, 0xF7FEECADD07BBDA8ULL, 0x071241944115474BULL, 0xE805A5CF3A7FFEE9ULL, 
            0x8FEE5E81D77F2512ULL, 0x469AF78B22FB0ABDULL, 0x40E31664574CEF17ULL, 0x5931606E6982A945ULL, 
            0x6B9097D93F7FC9FDULL, 0x5D313905B2C2D86FULL, 0x78A2EFB554CCECC8ULL, 0x37396525FD65281CULL, 
            0xC071357593DE3F0AULL, 0xCCA2C9B096632280ULL, 0x6BE2ED4D20B7DD37ULL, 0x0019DFC418083FC0ULL, 
            0xAA443F8A01D891D8ULL, 0xD85143AEC8EE30D1ULL, 0xD55B49456F66D9BAULL, 0xD9EDB1E413693C04ULL, 
            0x8F4E16925614A337ULL, 0xA873918E8E90853EULL, 0xBE22C0BA15827506ULL, 0xA36EB728FA0F702BULL, 
            0xD4CDED055078F926ULL, 0x296B31B3BA635805ULL, 0xF235C48D11C839B0ULL, 0x853CCAC740F4A3A4ULL, 
            0xC4E5C2AECA37EB39ULL, 0xD9A495B6DE45CCD5ULL, 0xAF0A77B476F1F1EAULL, 0xF834C6233CE2B299ULL
        },
        {
            0xC9B3A3807633665FULL, 0x5EA2B062D28AD054ULL, 0xAA858AEAE16AAF47ULL, 0xABC060C1F02262D2ULL, 
            0x52900988946F8D27ULL, 0xD549FD7F24EC93D4ULL, 0xD2D395D304723E6FULL, 0x68959C4DBD58C5C3ULL, 
            0x9C5D898A3E301E85ULL, 0x9CF524B6B9A39B9EULL, 0x73AC315B067E7C8DULL, 0x76EB255FA187F3EEULL, 
            0x1C1DF7F09E6BAF0CULL, 0xC688767849873201ULL, 0x7851E0878D01159CULL, 0x0B2839C0B8B9FF87ULL, 
            0xCF5179A9E5DAB9E6ULL, 0xF83093085966B6A1ULL, 0xF2267A08F119D50EULL, 0x1CC5E7FE6F1BE64FULL, 
            0x9F3EAFFCCFC6A59FULL, 0x944AC31529924750ULL, 0xF2B9CFE21FC16B5EULL, 0x76CACE9A7FA94438ULL, 
            0x64FA41062FDDDF4BULL, 0xE466D113859E90F4ULL, 0x786C5127286E8A50ULL, 0x5EB367C48CDBD981ULL, 
            0xCA71A33BFD8183FEULL, 0x49DBEE029A0A52D9ULL, 0xF10A77E42151FAF0ULL, 0x9742B1BD895C5397ULL
        },
        {
            0xC06EA4C1BDFC1DA1ULL, 0x587295BFF83CAA79ULL, 0x8FDB0CF889BB1DE7ULL, 0x30AACDF24C2BB229ULL, 
            0xA68A156B1474D525ULL, 0xF713228B9F365560ULL, 0xE7E1322B3203DB77ULL, 0xA97CD45A35214245ULL, 
            0x5D44F1DE463009DFULL, 0x0E92740997E2C0F4ULL, 0x1858036A366F8677ULL, 0xCCD4938C33E874E9ULL, 
            0x12CD0952F80A227AULL, 0x2D104442C7E52B03ULL, 0x81C8E287F85ED118ULL, 0xD2B3C28A7323AC80ULL, 
            0xCBE28CA42C688F44ULL, 0x816B0816393AF0AFULL, 0x228B5004395310B8ULL, 0xC056E38826AF3105ULL, 
            0xA88177E46F569422ULL, 0x1CAE4A71C59A409AULL, 0xD8FB6FC0C852F228ULL, 0xDDC6E4488C9A0FFEULL, 
            0xF39E7562FB293341ULL, 0x812262510BE191A9ULL, 0xE2255D4E91F2C0C2ULL, 0xA8A79F5327C5D368ULL, 
            0x2E711348E0FAF990ULL, 0x25B9E35AC685D16CULL, 0x22050A7F8A5A878CULL, 0x250873E441A49254ULL
        },
        {
            0x3840F3B1D2B98575ULL, 0x5CC6CFCA62587D99ULL, 0xB9D7E24EC964B680ULL, 0x8BEE9294C9EC4738ULL, 
            0xC4647357E4E30F5EULL, 0x6500CC55AABC7E2AULL, 0xFA8C2711C78214D6ULL, 0xC1F6F1DAC030F79EULL, 
            0xFA587C81ACFC5C63ULL, 0x285A6C677968DFBFULL, 0xC05ED2AEE8FB290DULL, 0x8CDC48AE6E9AEAD8ULL, 
            0xE57083C2A7E56ECDULL, 0x52DCC5E8CE6D152EULL, 0xC4C825DC70ED9D15ULL, 0x67B68E34453366E1ULL, 
            0xED6BE96957C2A299ULL, 0x72FCF861CB8336D1ULL, 0x75387D74931D3E9AULL, 0x27413AFA8E8A6D3DULL, 
            0xC8EFFAC4EF2DE31FULL, 0x3168483A13D4A5DBULL, 0xE443DC2F19C6B54FULL, 0x8397A6D757EF81ADULL, 
            0x885CC731151AD83FULL, 0x60836D32CB63B55AULL, 0x08E1129AEFE0B7A8ULL, 0xB632812480775C05ULL, 
            0x5C1432204516D176ULL, 0x069A9EE7D1CFD297ULL, 0xEB10F40D0D1DF75AULL, 0x97592574829CD60AULL
        },
        {
            0xA1AAEBA28D839E95ULL, 0x1F061253A3D45BDCULL, 0x9934795689488756ULL, 0x91B4E36F48C7F9A1ULL, 
            0x59AB73CDE4F305B0ULL, 0x426727B42A67B3AEULL, 0xC3A3B19C5C3A8B7DULL, 0xB0940ECA51A4BDF3ULL, 
            0x68067CEEFDC480BBULL, 0x0B94DCE774648301ULL, 0xBBFB69CA6AFB4DDBULL, 0xB97189F9E9380579ULL, 
            0x3777B8BF859231E6ULL, 0x1551714EF949C249ULL, 0xD35BC91AB193B469ULL, 0xE23016322404CAC7ULL, 
            0xF600B01220791992ULL, 0x7A5AD8AF4F485266ULL, 0xC3EE2B68FC22342BULL, 0xD800EE50820A7AC6ULL, 
            0x95001CAF120A9C84ULL, 0x448F79BDA9C4E4A9ULL, 0x9505D790A34B0F02ULL, 0x4088207271318E5DULL, 
            0xD5A9E920619A400EULL, 0x071804DD72C6EC31ULL, 0x3604881CBC7C2CD9ULL, 0xB9CBBAF669A47A92ULL, 
            0x2C549B6A0C7B6235ULL, 0xCF435FE5551E0998ULL, 0x9B4FA4AB88DE1986ULL, 0x78A4FD957220DD76ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseAConstants = {
    0x1F4B29DABA7D681EULL,
    0x1A37F441420C1217ULL,
    0x7DB09F50FFE0788EULL,
    0x1F4B29DABA7D681EULL,
    0x1A37F441420C1217ULL,
    0x7DB09F50FFE0788EULL,
    0x77C4F82EB773DE5DULL,
    0x808A617226E52DC6ULL,
    0xC0,
    0x26,
    0x02,
    0x88,
    0x9B,
    0x67,
    0x7D,
    0xDF
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseBSalts = {
    {
        {
            0xC97AA09580CF64B3ULL, 0x32E081C790778766ULL, 0xC671994277B8D8E6ULL, 0x3BFCDE2E168ABB50ULL, 
            0x1E21A0B11655E10BULL, 0x8DEEAD654CBAB727ULL, 0x47E5BBCF24328DDBULL, 0x241368B4C295DECAULL, 
            0x8A37959E6A2DB3ADULL, 0x46795C7782DBF9DAULL, 0x747B3BD848BF4E6FULL, 0xEA3E4A05DE160973ULL, 
            0x8157397A6D4AFCA3ULL, 0x03FF97534093CFB5ULL, 0xB3015FF894FE96E4ULL, 0x68670D947BCAC3BAULL, 
            0xBB07A2FDA0AC9F08ULL, 0x8D572666B63BE3CBULL, 0x020D65808E9002F5ULL, 0x6F2CDF75C1B3FAFFULL, 
            0xFC021233581B0D6EULL, 0x9D2579890106E567ULL, 0xF150B1921A32252FULL, 0xF944F8160FA97772ULL, 
            0x6D383D37AFA2D8FAULL, 0xD4266AF47ED028CAULL, 0x37950E25C979CD4DULL, 0xEF5CCADFDEBC48F1ULL, 
            0xCE02E5E78638E1D0ULL, 0x90C3AE5FE78DE1EBULL, 0x9357E7621F082E43ULL, 0xECEA2E64D42BBA94ULL
        },
        {
            0x6FCBF6E627B617F5ULL, 0x3224282E6A6D04BDULL, 0x37822B8F2EE7831CULL, 0x0F80058FE71D99C6ULL, 
            0x54C84D7231F51C1FULL, 0xBB0A4FB293659266ULL, 0xFD04296C710A4824ULL, 0x7D9AADE4554973BAULL, 
            0xD67B684CF79E30DBULL, 0x4150D18CC70FB01AULL, 0x048BD99D310D0A6EULL, 0x475998F0C6FADE94ULL, 
            0x652D88BA8306A259ULL, 0x8CC2B16084C20AA3ULL, 0x6F2834A4ABE4C230ULL, 0x51C96F3B9097E6D0ULL, 
            0xDEB940ED89CF17B8ULL, 0xB7C96A94C57F41ADULL, 0x670A0A66992ED49DULL, 0x6F5D0AD8C57B9F86ULL, 
            0x9C7B6FCCC928FCC1ULL, 0xC5048C02987D2BE2ULL, 0x1998D216F634156EULL, 0x2414617290B3AA73ULL, 
            0xBD2A7E822DCE0E61ULL, 0x8D9FC69862E77160ULL, 0xB64AC03C5A0C4100ULL, 0x9965412837FBFF6EULL, 
            0xCE675D32FF9CD9E5ULL, 0xC18AC8F08F0BAB0BULL, 0xDB113AECAC501D85ULL, 0xA34C7F402434710AULL
        },
        {
            0xF5CBF94F514B34E4ULL, 0x40CB743D61A5609FULL, 0x32EA2C7A374B0228ULL, 0xF30239B6A20B861AULL, 
            0xE10B791A95727478ULL, 0xF4FA7BDD94C92910ULL, 0x4063A1668BC2CE4FULL, 0x24197CCF8D36E3B0ULL, 
            0x0F27BC2DB5800119ULL, 0x4DDFACD3F0BE16F5ULL, 0xAF899CD57C851078ULL, 0x9DE22EA50A719557ULL, 
            0xB2300A05322F2946ULL, 0xD8F9F6359DA475F2ULL, 0x9CA53880F959191AULL, 0x5C64001BDADC3D27ULL, 
            0x5B5B634C27218175ULL, 0x0DBB6022ED0FF928ULL, 0xC0D55BA93B1CD760ULL, 0xA358D8D9C20D5FA4ULL, 
            0xD8EE07D55741D68BULL, 0xA351E589DD91477BULL, 0x5E9D91EB90BA024EULL, 0x392CDA4E3957A00FULL, 
            0x7484AC611E0A5418ULL, 0x46D4BED3902F7CBFULL, 0xE1AA8C2D0487F90EULL, 0x02ABC31F4BE83C07ULL, 
            0xA9DFCCA8C635A76CULL, 0x86547EB6B6EAD1F7ULL, 0x3566F43B3BC5E78EULL, 0x0363E4822BD46838ULL
        },
        {
            0x9B66DD6FC1064E8DULL, 0x16DF8B085482894DULL, 0xF918EA4DCD2010ABULL, 0x9A6875B742255DEAULL, 
            0x6BFB2578D27AB1FAULL, 0xFD82193E1A8B7689ULL, 0x412FB24D1DB2E2A4ULL, 0x46B89B49287F9806ULL, 
            0x5EB3038363C5B728ULL, 0x8556A1F37F4C9929ULL, 0xFDCFB00EFF3395E4ULL, 0x6C7DEA28636BF7E3ULL, 
            0x4E275F6534EDB65CULL, 0x81F5477AA6C56A80ULL, 0xD5EB54CAADC92A7AULL, 0x4D6F1B0073D572FEULL, 
            0x681370E89E1AB8A2ULL, 0x245AE9E99836B0DAULL, 0x76E151C5535EB1B5ULL, 0xA8018B42D5AA32DDULL, 
            0x45B5A04BCA829655ULL, 0xEADA5746C9D16FF0ULL, 0xF127EA093E3A9903ULL, 0x4DF28539EA6CA84BULL, 
            0xE208E2ACF26D4C9EULL, 0x8BFDB2F0347D7C50ULL, 0xC6055207AAD17776ULL, 0x32D1DF04C5853098ULL, 
            0xC0C7ABA401DCA1EDULL, 0x59092D981DC54351ULL, 0x252948F6828639CCULL, 0x5DF072D23F6091C0ULL
        },
        {
            0x3D21448F5D9E5D64ULL, 0x5E0E8D59FDC2F0FAULL, 0x71096F9C9D7123E6ULL, 0x099F40E77F91216FULL, 
            0xA138553A67641C96ULL, 0x4ED7D366678F41EBULL, 0x9DF6DC572FE377AFULL, 0xCAC1CD19E25206DCULL, 
            0x8D7B49814B0020EEULL, 0x1A549F16889092A6ULL, 0xA137477472D87975ULL, 0x4783E92CDBF5E4FDULL, 
            0x1D9B65C1F1EC578DULL, 0x4BE7F4F0225C18D6ULL, 0x58F2025821B6E90CULL, 0xF67D306F876D6ED8ULL, 
            0x9592471A9B58969AULL, 0xE338304FEF1A7C08ULL, 0x44ED3D7AFAD14A26ULL, 0xA00FBBBD6F0F4A9FULL, 
            0x293D70048E667315ULL, 0xAF01BBE48A77D208ULL, 0xE03F0BBC648FBCE4ULL, 0xC7849960525C163EULL, 
            0x57663FC7720D04BBULL, 0x5EE098BE328428BCULL, 0x50A5306DB85BE75FULL, 0x8A235DCDD72531E6ULL, 
            0x2C582AA452CAC823ULL, 0x064078AECBE93D18ULL, 0xFD02F9243ACF6717ULL, 0x9828B8F01B1DBC1BULL
        },
        {
            0x1ECE0C317EA34721ULL, 0x9DBF60D7893D961CULL, 0x2E7FE6C4B67B0096ULL, 0x946FD90A67C47D78ULL, 
            0x5757E06381F3C1E9ULL, 0x49B76BE93DDF4DD2ULL, 0x7EF29B70A16CD867ULL, 0xC0A1CF13ECA1932DULL, 
            0x318D3F3E50061874ULL, 0xC56382AFFA2E6B76ULL, 0x82535E92CABE7843ULL, 0x1A2FD3D187BC2D77ULL, 
            0x67DD4FAEB2A880D3ULL, 0x509EE9CE1C44F53EULL, 0x4F02189BD10F6492ULL, 0xFE0CA7563538247FULL, 
            0x3671F72C3F20DB08ULL, 0xFA75ECD5CBA7C3AAULL, 0xFF524514ED674543ULL, 0xEDD00DD6AF6FFAA5ULL, 
            0x0F9021A8E9D4F279ULL, 0x0401098E276BB770ULL, 0xA8A523D82C167163ULL, 0xF684EA61B1BC3086ULL, 
            0x948A2D2A76B85CAAULL, 0x334BE7F8A74BE042ULL, 0xAE3CA5A1C7E57583ULL, 0x6F8A6161994140EEULL, 
            0x9137BA0D9747E075ULL, 0x4A2414D3D3D9DEAEULL, 0x0C2B7460204CD27BULL, 0x46338962C25FE7F4ULL
        }
    },
    {
        {
            0x0495104FD67576C5ULL, 0xD976228F5F8B150DULL, 0xBF5E18D4A19F4617ULL, 0x0E672A3E75FDE5EDULL, 
            0x8A8078E3A3A8C213ULL, 0xFFF74A041B17BB3CULL, 0xF2C8B922503C27DBULL, 0xE6DE4E311E5539A7ULL, 
            0x6D6F17A56EEBDBADULL, 0xA690828C0929DD9DULL, 0x25EA696E64D8B10CULL, 0x2D6DA718676404B1ULL, 
            0xEE29919F232C1EBCULL, 0x0633B96BAE7A53DCULL, 0x837975FC740615C8ULL, 0xFFFEBDD033BC8B88ULL, 
            0xA2255C73A1E7A0AAULL, 0x2E0797AAC6646EA8ULL, 0xE424FD2272448BF1ULL, 0xEC228E0B49845E64ULL, 
            0x978B98CE2F3370CFULL, 0x3871F573E926E0CDULL, 0xE9076CAD25D9AE22ULL, 0x8839B8788B9C81B8ULL, 
            0x85C84F957497FBF4ULL, 0xB2C2141BAD2FD0DDULL, 0x1C2E1B972C4A04BFULL, 0x3D1C91A39BA3BBA5ULL, 
            0xE40F0F8EBAA28E35ULL, 0x48DD41ECE1247F4BULL, 0xDB9554BB748BFC45ULL, 0xA6FD97B6E6B850B2ULL
        },
        {
            0x716814E6099154C1ULL, 0x92CAE35AD2E69AC5ULL, 0x1BA8C8D20A9CE19FULL, 0xD3F7EE79C80BD19FULL, 
            0xD1EAEFD53EF0DFCFULL, 0x9E761584D9F6DCCFULL, 0x6025CA93E3F78BA2ULL, 0x84BD1DC94808EBADULL, 
            0xCC12274B095C0E3FULL, 0xA5386542F4FE4E99ULL, 0x0F3341CC6CFEEC63ULL, 0xA0BAA77EFCB64472ULL, 
            0x08D9A8A6057AB697ULL, 0xCF3210F695D2805EULL, 0xC494A1C8AB179039ULL, 0x9F095DA1F0BF977FULL, 
            0x4FAEA0A5B0125FBEULL, 0xB78B1D9738E0B44CULL, 0xD3FCE31A0DFEDBE7ULL, 0x84CFFFDB98556DAEULL, 
            0xA292F3A65B6BE01FULL, 0x1B7FC3FE251F2037ULL, 0x76CE82205C898610ULL, 0x4DAD36628ABE7479ULL, 
            0xBD92A69624F431E3ULL, 0x0320B66A51D40E23ULL, 0x789301815CFC1D7FULL, 0xFBFDF21F58CAF3DDULL, 
            0x3F056E4DE349DBF6ULL, 0x21581D249364C965ULL, 0x0735A192CDA251A5ULL, 0x4FB270972C13FA4CULL
        },
        {
            0xE1901D2BB9AE15E8ULL, 0x2EDB1D93C9251C1AULL, 0x46E55F2715F53101ULL, 0x909C68E8828D6440ULL, 
            0xB40BBC205EAF24FFULL, 0x09B88D6E488A6F63ULL, 0x6E36EDB0B76914DEULL, 0x93516D4123F0B7DAULL, 
            0x4480A692CDA946B9ULL, 0x03244058CB2C1795ULL, 0x3104192C16CAFC0EULL, 0xACAF05E352BCBA66ULL, 
            0x547E4D34D676D354ULL, 0xF603AA991F0CB3CCULL, 0x7121ECBF2BB75EB9ULL, 0x13773F710BBD1FA6ULL, 
            0xED08D88E3906B1C8ULL, 0xCD9BF6840FE4E9AFULL, 0x1688A4E2FD65EAAFULL, 0x83FD2AA5DC872CAFULL, 
            0x37A6AE670B01E3D3ULL, 0x6B4A58901325F2BBULL, 0x9E3CA4A708266EFDULL, 0x26EEF4AF9D175A71ULL, 
            0x309BF6D3637068C9ULL, 0x8F278A72879507F9ULL, 0x7175EEB1DA412E7FULL, 0xFE1CBA9718A13575ULL, 
            0x77C83212D5CA6C45ULL, 0xCDCAA05E43D0742BULL, 0x78BA9E084CEDC8CFULL, 0xFB8158870AEA03BCULL
        },
        {
            0x06C77CF183E386C3ULL, 0x4FCC024BE9107577ULL, 0xED3457D5D1CF46CCULL, 0x01BD84433D7CB127ULL, 
            0x68FF893A922861CBULL, 0xEA2EED3CC7BF839FULL, 0x958501AF6A666D33ULL, 0x5366C96622E7EC22ULL, 
            0xB25F1CC8E7FF27E5ULL, 0xF9997A155338B02BULL, 0x6E279E87E42B84F7ULL, 0x5B7A5517F1B3A561ULL, 
            0x3A6643B36E39C82DULL, 0x7C8DC5D95321BDF6ULL, 0x518DD252701EEED0ULL, 0xF446D483FE438442ULL, 
            0x061E5684DB7C2882ULL, 0x65412675FD39EE36ULL, 0x97BEFF9DEE3D20AFULL, 0x22967EA104AA5A80ULL, 
            0x667C4C7B0A67E8D3ULL, 0x2743F7C56DA65089ULL, 0x8638120E9F81D66DULL, 0x04456EAF7E41C9AFULL, 
            0xB3A04B7AD17CCDA4ULL, 0xA4F58BB53DEE213AULL, 0xEC76E16717DD939FULL, 0x016E79F8FB19429EULL, 
            0x9757FACBAA1D0F9CULL, 0x89D693E589DAE557ULL, 0x574D568CF6F95167ULL, 0x66FC29073BE4D62BULL
        },
        {
            0x2E9EE992441DFC9AULL, 0xAD6F3116C0CBAC97ULL, 0xFFFEA7B23B1CAE74ULL, 0x1C26B446D834F99BULL, 
            0x8A966CFBB236D06CULL, 0x08EBA72AD101688CULL, 0xDDF0FE789A1801C3ULL, 0xDA4398F4A5384079ULL, 
            0xC4DF3652D463337BULL, 0x1F03C490A4E2A29CULL, 0xFE4C15BC59D9B84CULL, 0xF3C186B1EBA267AAULL, 
            0x6C2FFB4BE70DA3F4ULL, 0x7E629D233C5F121FULL, 0x9A31205697ED0A89ULL, 0xA997ADAC93E647AAULL, 
            0x2DBAAFB28DEB5B7CULL, 0x98DDCF35B7D5F471ULL, 0x24F90DCD17F3C4EBULL, 0xDADD2C5DC5DDD51EULL, 
            0x9BA52B22098BE8F7ULL, 0x0A9C06F36EDDB64BULL, 0x24D08FFF5F93322DULL, 0x0965EADD225E405DULL, 
            0xF0FADA81F265AD2DULL, 0x88D79A7615371092ULL, 0x34F2EA1AA86BA4B1ULL, 0xC3BEBF464D660692ULL, 
            0x8BE0EAE303567CAAULL, 0x8D5C6BF80C894116ULL, 0x9B56201EE01046B0ULL, 0x88AE4DA2623FC278ULL
        },
        {
            0x21DE6C2A7036DE27ULL, 0xAAF897A2F318E7DBULL, 0x9E6A218A43730C0FULL, 0x4DBD653F0C6DC140ULL, 
            0xDF3F902A2AC91573ULL, 0xC76A27D0AFCD070AULL, 0x9AF71BC0745B9043ULL, 0x29CAD6ABB34393C1ULL, 
            0x42DB1C22E9233E98ULL, 0xE21692BCC527BC90ULL, 0xD9170F4725EE3032ULL, 0x859A0ECD332C16B0ULL, 
            0x7914D20FEDC4DAF6ULL, 0xDB87530EDC887078ULL, 0x2C7E0F10B8E5CF89ULL, 0x0059EF5277A0C5DCULL, 
            0x9E78E213BB9E0083ULL, 0x732FC8CE0F17F432ULL, 0xE7A19B9DA2CC6AD0ULL, 0xFED887B3367E27ABULL, 
            0x46ACFC4E5344CEA7ULL, 0x378902EE12B90F92ULL, 0x68C0D3551FF39250ULL, 0x470D00F9BE2A8CB1ULL, 
            0x8B2866B97BC093C0ULL, 0x5B15F77B451C5DF4ULL, 0x7FA27287561DA5D8ULL, 0xF0B866BC9E8C601CULL, 
            0xB4549D5CAFEA5681ULL, 0x4BFA9BEF0A1E52F5ULL, 0x63CABA0FFF2505B4ULL, 0xF393E325F5B04285ULL
        }
    },
    {
        {
            0x304D343C956C3108ULL, 0x357CBE517DA6B082ULL, 0x186A96808EAEF74BULL, 0x0EF32AED28D224D3ULL, 
            0xD0CB68505FFA71DAULL, 0x4EA7B859D34D14A0ULL, 0x26E58F4E9748E810ULL, 0x20334EC4BAC3FE53ULL, 
            0x355310B905D579FDULL, 0xD7200E98CB87901CULL, 0x58B3065378EC5A8CULL, 0x39C6162C99380F22ULL, 
            0x58EDE50B26C23189ULL, 0x124B5C9C87606AD1ULL, 0x5F308972B9826CDBULL, 0xF4EB6EAD72ED7A41ULL, 
            0x5FF5BCC03A4753A6ULL, 0x65945A83AF547525ULL, 0x9F33F2DA9DDDB229ULL, 0x2A6AE9A8785963E9ULL, 
            0x28C86A236231276CULL, 0x9DBE79C237CCA28AULL, 0x7549B7A95F873FD2ULL, 0x32DBF086C5A5C321ULL, 
            0xE6F13512538EC3FEULL, 0x11025C10BA0FA9B1ULL, 0x1B6AE0A373C47183ULL, 0x8B2D95B5133B458EULL, 
            0xDA0C280D74576EF1ULL, 0x9DAE6398E782190EULL, 0x898B44985E3B606BULL, 0x293B07F5FD4EFE62ULL
        },
        {
            0x586069E13073AE9EULL, 0x12360F638C854EDEULL, 0x8B82E317BF822224ULL, 0x7E9434E17BC1DFAEULL, 
            0xA58B39D0E3D870A7ULL, 0xBDFBB4EC4CA4DAF4ULL, 0xABDC6EB453CE89F1ULL, 0x966D9CA6AA0EB081ULL, 
            0x745280C2FE9CF9EFULL, 0x6971145A51B6DAFCULL, 0xC94683E65401B47CULL, 0xED1B9E2AFD5AABBAULL, 
            0xDC1921638FAB0304ULL, 0x4A79021CEE49B452ULL, 0x062688D5D413BED3ULL, 0x735A130FDD6D857DULL, 
            0x1F93F7B17076625CULL, 0x72E166F81EDAE0BCULL, 0xED3CF62A792D2D4CULL, 0x5256815428602A33ULL, 
            0xA1CA79E27A1E8F64ULL, 0x27D493243E971C24ULL, 0x766504FFE0009074ULL, 0xE9ACE08B0564AA3AULL, 
            0x188D51D09D8D5656ULL, 0x0A1E44DDCFC10A61ULL, 0xAF7A0BF1F3CC2EE1ULL, 0x535C6D1D6B9E00C1ULL, 
            0xFDC9E2F4FBF23C41ULL, 0x153E5986C13A9209ULL, 0x90A8913DFC5A10ACULL, 0x7594662CD46E3D1DULL
        },
        {
            0xDEC6F4D63F859878ULL, 0xC3F165CF3B89A611ULL, 0x149D91F658F34832ULL, 0x952C0038E08AA891ULL, 
            0xE141EC7B3BA68CC7ULL, 0x4E821046344A5ECFULL, 0x0237F2B9EAC9495DULL, 0x97160F2895C0070EULL, 
            0x273F2CB77788E064ULL, 0xB8F684B6717A7D11ULL, 0x3637B6CD8C5C9E52ULL, 0x582F860AC111C73FULL, 
            0xDBE5D16716C3E7C8ULL, 0xD0C045C0075F5171ULL, 0x23994A4980337997ULL, 0x4DE81DD0F1624A5CULL, 
            0x42C4371FC6624DFBULL, 0xA3C64C3CBEEEE053ULL, 0xE15547102EBEF2C0ULL, 0xBCDBD9E553DC590FULL, 
            0x2C4A12F7D60F47E6ULL, 0xBE8D3AECA6CBD4F2ULL, 0xA69782C97EFAE0B5ULL, 0xAE9BE1C173EF398DULL, 
            0x8EB7D966DA178BDCULL, 0x28F060526CE7FF90ULL, 0x4E2F26B01451C3DAULL, 0xE35A7FF71E9D0900ULL, 
            0xD4F129880C2402ABULL, 0x13D4BEF137A6ADBEULL, 0xFC60FF2946FF74B9ULL, 0xEEA3BDA7C99C0FE7ULL
        },
        {
            0xB9495771BFED53A6ULL, 0xF0EBD412F5C1B2ACULL, 0x2A7697AF03E504E6ULL, 0x46A902D562E4170DULL, 
            0xAED40E26903A3D6DULL, 0x31DD797651144149ULL, 0x136725788B6E4DE7ULL, 0xD8AC9F432F90A75EULL, 
            0x42F0D01B26956AA6ULL, 0x608820DAAB088E2FULL, 0x584F07A93703D748ULL, 0x92F75FF902CF7462ULL, 
            0x3C33C89A2C3AF8C7ULL, 0x23D1B14C57DA001BULL, 0xD1EBF104020D9383ULL, 0x2075217C75E0EB45ULL, 
            0x22EA9032499B030DULL, 0xA1887F6AE59F6858ULL, 0xE1F1314031AFEC52ULL, 0xEEC0FCAFEA59E02FULL, 
            0xEE48CCF6D46250D5ULL, 0x5C9E68CBA3C84C50ULL, 0xB88B952222AB4DE0ULL, 0xE8D15F1C484BDF26ULL, 
            0x0FAAF2C183677E7CULL, 0x09A0A3F18FCFFC63ULL, 0x57E0E01B362F6F3FULL, 0xB3F087304E555E0CULL, 
            0x7F88EF5B26803404ULL, 0x400A0EDC1F5B98D9ULL, 0x277FEE63052F4840ULL, 0xE523D77368C67EA7ULL
        },
        {
            0x5A98C67AC12E0FDAULL, 0x408AEC4D7DC54BF3ULL, 0x9FD1D7EFA58D7573ULL, 0xE321451DB8293DC9ULL, 
            0x30A2E60576D95305ULL, 0xE9B4F9BF5F5D0BBEULL, 0x7E45E1A506055F0BULL, 0x62EA8ECF7EBAEFC3ULL, 
            0x011653686FEE93F3ULL, 0x009B0DCA12984A0AULL, 0x7323804C53D3F387ULL, 0xC72C76B5456DFC0EULL, 
            0xFAF58930BC163576ULL, 0x76C99F3285429133ULL, 0xD6D990C385821132ULL, 0x0D1E12A850B55799ULL, 
            0x27D60B5523E76F66ULL, 0xE8309E07AC1ED38CULL, 0x3A16CE258E67011AULL, 0x0F19271291B3CBB8ULL, 
            0xF9977ACA4445F7FFULL, 0x5D6D4BD9B02AD518ULL, 0xD4F152BD1BA3D3D8ULL, 0xE903F0B35DD576A1ULL, 
            0xFBA359FBE19ABE0EULL, 0xD491ACF541DEF07FULL, 0x272121215306AA69ULL, 0x979CE68AF8206801ULL, 
            0xF62928BCA89CF7BFULL, 0x1478A2ABF5BCA984ULL, 0xC6B6E09E6AC12C64ULL, 0x7E4634FC8482F1E6ULL
        },
        {
            0xFF53D88FC546E01EULL, 0xBB2EEDCF73688388ULL, 0xF7D5320F8A89A830ULL, 0x290E9E3A58447333ULL, 
            0xBB232CCA6CD454A9ULL, 0x50C621003D6B8F0DULL, 0x23D76411ACD07B1CULL, 0xF39285F6F5F6CD27ULL, 
            0xA979E2315C22AF1CULL, 0xCBEB2386DD53FFEFULL, 0x9D9DF392123C434BULL, 0x90BA00081E05ADBBULL, 
            0xFCA3AB1C8D207E8AULL, 0x302BD624C51F6204ULL, 0xED4325D4BF06C49EULL, 0xA8497C3736040807ULL, 
            0x4A346D3B1450B14BULL, 0x5B220DAFA6530EDAULL, 0xBA8E66ACB2ED40D1ULL, 0x35EB84D83DC08BD7ULL, 
            0x44732AD39D1655CCULL, 0xD0D0295B6CE26AB5ULL, 0x8D9300A795F1F7BEULL, 0x3CF2C6FA458BF4F5ULL, 
            0xBCBFF080828AD70CULL, 0x7240CC631C70B732ULL, 0x5223AC06511960E0ULL, 0xEE6D2C38C6A8E8F3ULL, 
            0x17219F45BA53A3A9ULL, 0x3FD7001DA4E7669EULL, 0xFD8950630DAB7A39ULL, 0x972C65C9D1FF40BCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseBConstants = {
    0xBFB5D481DA3F5E6FULL,
    0x7767E14ACCE5FE16ULL,
    0x0932942BD0329B94ULL,
    0xBFB5D481DA3F5E6FULL,
    0x7767E14ACCE5FE16ULL,
    0x0932942BD0329B94ULL,
    0xCC3C0E03C1F1439CULL,
    0x3341FC71484BF1B1ULL,
    0x65,
    0x14,
    0xE2,
    0x8B,
    0x9F,
    0x29,
    0x26,
    0xBE
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseCSalts = {
    {
        {
            0xC4641B5449477055ULL, 0x16D6F6A45FB9BFDEULL, 0x4AC9F87EC0009EFAULL, 0x165DC13CC6D1C5F3ULL, 
            0xB8B0A95443329DBDULL, 0xD41CD671D195B95EULL, 0xDF631031B4761C2AULL, 0x749A99B876A6813BULL, 
            0x3F8F5EA60F391CB4ULL, 0x4CE01AC3D4BFEDFCULL, 0x9A1B8556826A8E50ULL, 0x7047B42DA26C6144ULL, 
            0x844069224344BB74ULL, 0x24FF7D06495B57C6ULL, 0xB2A303725A47A1E8ULL, 0xFA6EB20B539FA6A4ULL, 
            0xAA2F78ECFCC10D9AULL, 0xD526626415CE3FB0ULL, 0xD085B5204872AF88ULL, 0x58B2825E5E2A889EULL, 
            0xD873C0BDEC601E2DULL, 0xEFDDB0184BD702DBULL, 0x16969C9C59DB9E21ULL, 0x7C8EF69169922B3FULL, 
            0x89AA338C15E44CBBULL, 0x2F25AA0F25CA8400ULL, 0xD7A7B472DDADA818ULL, 0x71010E05E2595C0EULL, 
            0xC0B5A09AEA0989B5ULL, 0x4125545DEB5F21D0ULL, 0x88D9168B4A635957ULL, 0x6DF0401ADCB85617ULL
        },
        {
            0xCCF339170A24D26FULL, 0x30DA5FC09830D9B8ULL, 0x78448AF786150333ULL, 0xE6C1C2210E1055E3ULL, 
            0x58CB3A7538B84FE2ULL, 0x2082D3209673E90CULL, 0xE25EC039EE5C64DBULL, 0x60A219BFA27BD1D6ULL, 
            0xB9029DF6DD09976BULL, 0x7F7A7FE7C19EE1B9ULL, 0x9477F2E89105D88EULL, 0x17A0809575633C81ULL, 
            0xC76C6DDF3F24DDA3ULL, 0x8502420F4DE894EAULL, 0xDE0A940C85C86BC5ULL, 0x40AA6297F7B832EDULL, 
            0x600049389A239824ULL, 0xF1900C0D5407124EULL, 0x4C4823BB429AD7D3ULL, 0x7DA1B3AAF1294506ULL, 
            0x5E6B1A97CD09B3EDULL, 0x1FD67A3028C10C77ULL, 0x7930DAD407A137B5ULL, 0x4A249A99A3A0B979ULL, 
            0xC82EF02807E4A6D7ULL, 0x829A5027BEC8A3E5ULL, 0xDCF346FFD5040DDBULL, 0xBB739EC565B480D3ULL, 
            0xE836EB403124C135ULL, 0x0BD2C6B3DD8DA38CULL, 0xD52FF1FAA2775633ULL, 0x09369C6532B53368ULL
        },
        {
            0x39154232BE5D2DADULL, 0x7978385640AA1062ULL, 0xDC663E8E4F019956ULL, 0xBC259E9E40BBFC66ULL, 
            0x7BDA7006A01A6482ULL, 0xAACB6918A21AA744ULL, 0x2B0BA3F828F483C0ULL, 0xFB166AE3205200BDULL, 
            0xD64CB697420146FBULL, 0xF960D77E0971EC0DULL, 0xC2340E195CF6AB1EULL, 0xF9C23B7DA79C03B7ULL, 
            0x32D2382C141A1C0FULL, 0x91474E64A8260173ULL, 0x5042407E59B611A5ULL, 0x59B47CBAFDDCA460ULL, 
            0x7DBB0B72AA068C9CULL, 0x57DF2DE49EB2E665ULL, 0x719DFFC2BA1FA46FULL, 0x0175C318B30A772AULL, 
            0x978B1D0CADCC6551ULL, 0xBE314D249B0603AFULL, 0x11123DB63FCF4F48ULL, 0x59AE606A386EB09AULL, 
            0x94C5D0417019789EULL, 0x7AEC4416684B9388ULL, 0x167C6B7AF532EFD2ULL, 0x2EB95A8A3C7F0DB6ULL, 
            0xE5993896D0E211F2ULL, 0xA9FC7FFCED49E589ULL, 0x565A55C149888D54ULL, 0x3BC0F90E0B9DCB2AULL
        },
        {
            0x080ED543D6BFDC06ULL, 0x96BC0FC645F70431ULL, 0x4AF38A39E50CCBDCULL, 0x34EEF9EDC3A0C7D0ULL, 
            0xC58D1FCC1D21B218ULL, 0xAE6B9792334BE281ULL, 0xC08D137CB39D459CULL, 0xBFE7B4D34B0082FDULL, 
            0xEA53D4984CBE9CF4ULL, 0x629BC9BBEC9CFE0DULL, 0x9CA5F0AEC8C88975ULL, 0x65E4E57224B80198ULL, 
            0x02F7769E8EB5B6C4ULL, 0x8B0AC01DD1A10BF4ULL, 0x674CF79F1CD980A6ULL, 0x03DC335B38D8D0D7ULL, 
            0xE606C8FD2B209535ULL, 0x790F378B339872B8ULL, 0x0D17CD739AC10C47ULL, 0x1A9DDFF3C24ECE79ULL, 
            0x8807A3FD8D19EDE3ULL, 0xC069FAA50643257AULL, 0xAE555053D33D05EAULL, 0xAEF0D056E33D1FFBULL, 
            0x5292BBD0078D6511ULL, 0x5FBAB2E6345C46A6ULL, 0x13B42CE3042C829DULL, 0xF8242B0807D2D1DFULL, 
            0x0BA4D12BD6942C53ULL, 0x361834604AA993EFULL, 0x8348FD593500E782ULL, 0x2DA72C0254771539ULL
        },
        {
            0xCCB919F9F9747648ULL, 0x33C0DB00B022BDC9ULL, 0xAFCE73209062EDF8ULL, 0x60D623BCFD500124ULL, 
            0x6BA9F474376D4F17ULL, 0x75F7EEC446FB98FFULL, 0xF497C93165793D74ULL, 0x6B56062982E80E0FULL, 
            0x813AB5C1022A8BD4ULL, 0x1B54740751198AACULL, 0x4B773B2B203CCF10ULL, 0xF234720F81243324ULL, 
            0x95EC91728A359B62ULL, 0x0110640EFC1356E5ULL, 0x437763A9D3694FBDULL, 0x261AED883378CAD3ULL, 
            0x84D68BA577806EC1ULL, 0x58E54ACF29FA8849ULL, 0x2A0113A57D9046A4ULL, 0xA5B31EC15198FC85ULL, 
            0x3A4371F3FDD0C1B4ULL, 0x48F60B31F3664FE4ULL, 0xC48FE0DB2CF2F4D7ULL, 0x48788FF8035CC604ULL, 
            0x772457A05EBEF80EULL, 0xC67BDF127ABD3C8AULL, 0xFF943949075BF9F1ULL, 0x70999F510E7DFA3CULL, 
            0x9D5FCBF06DFDF008ULL, 0x3D1E1C8827D128C6ULL, 0x40A5BE966911B769ULL, 0x13712B7D6DBBFC40ULL
        },
        {
            0xE48090D7EB4C24E4ULL, 0xD63E649702A0D5CAULL, 0x7F544AD7C8074876ULL, 0x95041D94E93CC0DDULL, 
            0x8EA7D74020E3A57CULL, 0x94C92BCEA5DD83FFULL, 0x1CB348E1A509952FULL, 0x8AA9893F68C1EE8EULL, 
            0xD7AF94FAF1C558FDULL, 0x1FC2866E7BDFEAA2ULL, 0x05266A487358C8A9ULL, 0xDB866018A56E7012ULL, 
            0x5675C14AE1098C49ULL, 0x677B3C04A05F00EAULL, 0x66315F997B45D63DULL, 0xA8B2C549CD1C82B6ULL, 
            0x8623DE95106E6156ULL, 0x94A862A95D4BAE20ULL, 0xD8A6006622614F0EULL, 0x11FD109615BF5845ULL, 
            0xA83A419F9D4E78E0ULL, 0x69E3C6D61703D1A6ULL, 0xF51079B514911D8BULL, 0x4466FC90391D339EULL, 
            0x2B4819B8FF2336FBULL, 0x33EE990506AEC1ECULL, 0xD9185204126B7A11ULL, 0xC3984F66DB16AE34ULL, 
            0x7779DEE915D4C74CULL, 0xBB1794DD96D8E95FULL, 0xF6B7865757AE7861ULL, 0xEAE827B1F8AE6F7CULL
        }
    },
    {
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
            0xA4A36B8274C3584AULL, 0x3FB5098C64A599A5ULL, 0x67F09B8358D31AC3ULL, 0x4B6837E3883EC568ULL, 
            0xBC07411FAB87C0F2ULL, 0xF7C619C244C583E7ULL, 0x2EEB2A9C26FD0708ULL, 0xB58D95C88C7812B2ULL, 
            0xFD929D1CBF9D00A9ULL, 0xB55E37B99081397BULL, 0x521781EB86E9FFE7ULL, 0x396A9E4624DE1F6AULL, 
            0xB1CDC4F0FC411A62ULL, 0x370CD057E3D68B6AULL, 0x70D7E45C379C5189ULL, 0xDD57B2EC6279E660ULL, 
            0x6163201674D62A37ULL, 0x12820FA29E7A8D2FULL, 0x9A8D9A1987AA5EB2ULL, 0xAECF17E5B2870766ULL, 
            0x89EA2A331B71989EULL, 0x679D55D18A326154ULL, 0xD5A94DF60B8DCE15ULL, 0xDB4FA2A70252F70DULL, 
            0x03D6BE94BBE04292ULL, 0xB3754A9D14FBB33DULL, 0xBEED7C4301EB35A1ULL, 0x01C89A381CB5160FULL, 
            0x05D58FD431D948BAULL, 0xB5047A3185057204ULL, 0x7715F6F51A24F507ULL, 0x4F0BC175F2DC3D06ULL
        },
        {
            0xCCC7D36627AD2667ULL, 0x80512214F8891EA4ULL, 0xAB2ADC3068D5FD17ULL, 0x0A0FE27F25BD6EE5ULL, 
            0x059FC44A5C1E7319ULL, 0x66BA06C739E0F027ULL, 0xBAC25011F7F4E8F6ULL, 0x5836D4D5335AB13FULL, 
            0xCB1CFE9F4249280AULL, 0xC097BAC2F6AA50E3ULL, 0x84C36E8D5B5F3251ULL, 0xEDBC5F7D6A562CD4ULL, 
            0x55FCBA10E703CF27ULL, 0x2848E6780DF672E9ULL, 0xA210376DA467A4CEULL, 0x540915CDA3E3D75CULL, 
            0xDD776E8F11934E68ULL, 0x4936CE51107CCD04ULL, 0xBF91B14FFF088C8AULL, 0xA7AC6AD283EB77A6ULL, 
            0x477D7451CBB3422CULL, 0xE341E220FD520DE6ULL, 0x6BE3060A9D879C7AULL, 0xE45BA1B70074C327ULL, 
            0x1BAC389AD169A3EAULL, 0xF28E1B604E3FCB83ULL, 0xF2B9145A0A055553ULL, 0x9F5781620B3171FEULL, 
            0xA546B39F78FBED03ULL, 0x9FD60A1574929AE2ULL, 0x1F63B104D5387924ULL, 0xD1BA24DF28C18696ULL
        },
        {
            0xFD126DCEF1EBE3D7ULL, 0x0CD2D36C5F28DDE8ULL, 0xBA92AC70F15DD000ULL, 0xCFF30B2A960512B4ULL, 
            0x102E833008628A8FULL, 0xD773A2B526B40439ULL, 0xD6FCC10DCAFE6955ULL, 0x556177AE59D26C60ULL, 
            0xA6399088375010D4ULL, 0x96F5C065FAA92EB2ULL, 0xF94C9B5A69775194ULL, 0x1C8DCC18AE823024ULL, 
            0xF409384280F3521FULL, 0x105FAD7F0F4DA3C3ULL, 0x3AEC2C2900CF7922ULL, 0x9407FB5034E4260DULL, 
            0x838965A83F1E1310ULL, 0x9996F67378B13396ULL, 0x7FDF7FC1A2F8331CULL, 0xF7B7883C4F60B4EBULL, 
            0xFBB42FD4CDDB7AB1ULL, 0xF09AE9C66162D583ULL, 0x15C7B19CD837F1A1ULL, 0xD29BEF22282DD46FULL, 
            0x8B48066B1ABB4115ULL, 0x1179590BCFC69872ULL, 0x92CF05EEBCB4EB9FULL, 0xCC734BD7D4530324ULL, 
            0x5EBE1791835A6D2CULL, 0x52B3476B222A9E91ULL, 0xC25F994F530EAA3DULL, 0x929CAAB43612DBCDULL
        },
        {
            0x695186C706657B56ULL, 0x0C42AA5305D774B3ULL, 0x389E682BAEE77E82ULL, 0x4FAF7D9C0AC6309AULL, 
            0x840CAA1C1FCA5E9AULL, 0x899CB798ED0F1147ULL, 0x0F3175C292C0E1C0ULL, 0xEA2C129429CFF4B3ULL, 
            0x765054ACFCA268F7ULL, 0xC4D3C45C9B034D6DULL, 0x58D4224088C0CBD7ULL, 0xD38ED0D11F1F7601ULL, 
            0xA6F63A3162914AE9ULL, 0xD4347E3FDC39ED7FULL, 0xBE833F115CDE4047ULL, 0xF743C5FCB6020AA1ULL, 
            0x9C739A4DF2C115BCULL, 0x8912060BA7186892ULL, 0x06462DDC413AA3F7ULL, 0x8FA931A30C7A5AA2ULL, 
            0x699078C86EF80EFDULL, 0xFB533BD0C40596EBULL, 0x6EF30DEEAB3A6101ULL, 0x7BC61456189E57CEULL, 
            0x56DF0340BE2C0F03ULL, 0xC83F62793BC504A5ULL, 0xDD5E52ACEE49316AULL, 0xE9B1C81AFC16C9A1ULL, 
            0xF939C3253DEEA444ULL, 0xD25863FB841C147DULL, 0x425FD2FC307D9394ULL, 0x191986FB6D90E085ULL
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
        }
    },
    {
        {
            0xC00BC7FE6E05CABFULL, 0xE0EA339FA6FE51BFULL, 0x6E5614738AC82AF9ULL, 0x808D5B88343DB6CEULL, 
            0x701C489E56B2BDA4ULL, 0x6B5E366AF36C50C4ULL, 0x0AF6A08B403624E0ULL, 0x1CFCF8FAE868148BULL, 
            0xBA7647C6CA16F149ULL, 0x385362F922B57E1EULL, 0x0CD8EBC26FB8E059ULL, 0xFFB79F8C8FF35F18ULL, 
            0xE48E86B496F1BA46ULL, 0x030BFC4F75C7375CULL, 0xEA11E2AA6B711967ULL, 0x0D5083018AFB3156ULL, 
            0xBA880B5A44F2A3C4ULL, 0x701A88A69C4877FFULL, 0xD18FF35F55E6552CULL, 0x4332CD2F7C71DA00ULL, 
            0x390A3B9E0F9C09AFULL, 0x5E7E9354789C5EA6ULL, 0xFDFE57CCE750D4B6ULL, 0x6A5461D7DB8C437DULL, 
            0xF9B1AE0C12BEAA4AULL, 0x1518ECC6FE8BDFCFULL, 0x63ADE51104311554ULL, 0x469B8F710CF44FA6ULL, 
            0x2FD410E65C611D86ULL, 0x6C5E0D105DF76392ULL, 0x7299C15338C1B081ULL, 0x5445B9C103748D89ULL
        },
        {
            0x53245405C605387EULL, 0x4BA6A3FF7CAF82F2ULL, 0xFEA776BAB26FEE00ULL, 0x90802629C37A9D27ULL, 
            0x7E87B9BC5F137484ULL, 0x4709102DCE9227FCULL, 0xAA1DEF16A585BD49ULL, 0x2703989AFB0A9389ULL, 
            0xA1C96FDD62510F11ULL, 0x61A62455EC3705ECULL, 0x381D6941027BBB8DULL, 0xFF3768016A1F6449ULL, 
            0xFD298D075793CBFDULL, 0x4F77E4BF4FA26B3FULL, 0x5FBD78D00030CA92ULL, 0xA5F1683A7F801A26ULL, 
            0x1896B040C0971F63ULL, 0x2958E7926016AE42ULL, 0x31C1B9BF0B8D2F48ULL, 0xD84764B7F1E8C0E2ULL, 
            0x99FDB3A12C9A83ECULL, 0x7FFAAF22703255ABULL, 0xC287E0C222FB3365ULL, 0x0486DE32544E0FD4ULL, 
            0x41921493911A7E33ULL, 0xE42147753DE46A54ULL, 0xA6DADADAE35384B6ULL, 0xCF4CBDF4CCAE1689ULL, 
            0x3080283C3BE9DAA5ULL, 0x5EDBB206D9175282ULL, 0xFAD7B9C84E65C8C9ULL, 0x4E917DFEF612B392ULL
        },
        {
            0xB271DBEDC2207B3CULL, 0xA3776552C572F77FULL, 0xA9FEEC569DFFDC05ULL, 0x44EFAB5FB4D75F2FULL, 
            0xABBCA490E242D99FULL, 0xD303A5323F62BCC2ULL, 0xBF049A9EB499E5C6ULL, 0xD4742B2D07DBC513ULL, 
            0xDB6700DF84C6AFCEULL, 0xF57C07DF0AACA2DBULL, 0x5D37AD2C73C0539FULL, 0x6B367FFB90B5566CULL, 
            0xB65D114D6546D4F0ULL, 0xC9F591E8FF7F4C6FULL, 0xD19ED0F985B0C381ULL, 0x6FF51B0D05EF6194ULL, 
            0xB527E2B1F0E23AC6ULL, 0xDE8AA8DC955192EFULL, 0xA3C3D94094BC3E7FULL, 0x27FD51BFB0891FC3ULL, 
            0x56A4D39985EFE34CULL, 0xAA20A63EF6C39650ULL, 0xAB5DF839B5F28346ULL, 0xDFBEAFFB92774A14ULL, 
            0x29B6439384F11140ULL, 0x74E22E8131FC2E07ULL, 0x351EE2C5E5163D67ULL, 0x317F563B8D63BA30ULL, 
            0x990A13690A8894EAULL, 0xB346849E4B6C8D81ULL, 0x6D01E3EC7C4173A6ULL, 0xB081DEE9E8E87F43ULL
        },
        {
            0x377CD9B758FC14D1ULL, 0xBC090378D977A912ULL, 0x0C61C2EB62C34419ULL, 0x2E0CF5FADFBF0101ULL, 
            0x138CC406AAA9CB5BULL, 0xE302B787A209A603ULL, 0x7250B1248789C134ULL, 0xB25EC05695B7EE56ULL, 
            0x6F4E58484766A73DULL, 0x35D66A3B19B066AAULL, 0xD82CCF90554AD888ULL, 0x30AD3166F03EFDCBULL, 
            0x2AA97CF1F95AB408ULL, 0x37BB9E5DA76B48DAULL, 0xE19CFCC4CFA1C0B8ULL, 0x2A8CC0702240F2B7ULL, 
            0x9A769CA6CA070126ULL, 0xBC620A28B43934CDULL, 0xDB9DB5515C13D53AULL, 0xA48BD9AFBE27A2BDULL, 
            0x76F8977889AD50EBULL, 0xD55CBE5E31899D8BULL, 0x4A374AC5908C78C3ULL, 0x139B231F959AF5CCULL, 
            0x93BDC4C9E3E98307ULL, 0x7DAA5FB25071B4B3ULL, 0x539F7A170C1A9610ULL, 0x6C1887CED8857BA2ULL, 
            0xEAA1E86D96009DC3ULL, 0x203FF679EE61A8B2ULL, 0x5838FEE9AE4A2E3EULL, 0xC4561577660D792DULL
        },
        {
            0x54E821A050CE5761ULL, 0xA400B17106770097ULL, 0xA180A82A0A422230ULL, 0xCFEEDDC592BD2C4AULL, 
            0xC4C368F3E0912168ULL, 0x82810F626474E159ULL, 0x780A9F81E6E37977ULL, 0x8D02262AF34D3924ULL, 
            0x3908A094627B4DC4ULL, 0x2850C04E2A607FB6ULL, 0xA6E5DA8955B800AAULL, 0xAF9F316A96F59069ULL, 
            0xE2193F86CD990F0FULL, 0xBF450F2F71EB19BAULL, 0x71BE237C746941A4ULL, 0xB493B1C85D1294D9ULL, 
            0x6436F0D9CC250039ULL, 0x2DEBC0CFEFD1BA32ULL, 0x81E90DD53CCFC038ULL, 0x0DD3CAFD47FDF583ULL, 
            0x785C93FAF4FFE08BULL, 0xFED3002E73B07831ULL, 0xC3A61070508CA14EULL, 0xE4445FE77C844082ULL, 
            0x4B9C0BA931C47397ULL, 0x4A16AB4581F6B3B7ULL, 0xDEDED685E44CF196ULL, 0xA3AD42ED6DE1A0EBULL, 
            0x6B2B5C78830A3877ULL, 0x5D19416028B7C376ULL, 0xA7FA2CC0EBD52C67ULL, 0x9A2EBEF4014DD4DAULL
        },
        {
            0xF0477460464BE71AULL, 0x4037A9EA3EB429FBULL, 0xD8A1E2CB2568B6F1ULL, 0x3255703A7B04AD03ULL, 
            0xD4E5C6AE25B35DAAULL, 0x2CFCCCB982DF3FEDULL, 0xDD64C170589360F7ULL, 0xCE78C7CAD4AA3695ULL, 
            0xD033E1A555F078A3ULL, 0xD72122D9C71324AFULL, 0x6C05EB6DFE98DCB1ULL, 0xB4B3B33ED3998D53ULL, 
            0x58521B424886D1F7ULL, 0xDEF53D83269C1AD7ULL, 0x4EAEC406279FE81CULL, 0x3A1491633E3AF574ULL, 
            0xECFC1EBA92DC4678ULL, 0xC3CFB51FBC08A46AULL, 0xFF8E4C0730153ED7ULL, 0x60BE8F67D195C1F5ULL, 
            0x1EF0D9CA9A52F7EDULL, 0x99D7707F1ED0E62BULL, 0xFCEBA291B36AF670ULL, 0x0FEC77121FAD7451ULL, 
            0x4A2DE39749CC502EULL, 0x9687CBBD522187B1ULL, 0x4FB619C44D21F59AULL, 0x381D20CC9F8E9E8FULL, 
            0x2F6CA0612B86841EULL, 0x010ACD923C0069A0ULL, 0x8524FC0B7C9E346FULL, 0x16AFF6425BDC7E7AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseCConstants = {
    0xCC4C5CDAE2CDC53DULL,
    0x51C89D47E779DA36ULL,
    0x883A6F975AFABB42ULL,
    0xCC4C5CDAE2CDC53DULL,
    0x51C89D47E779DA36ULL,
    0x883A6F975AFABB42ULL,
    0x02A2C6DBFD94113AULL,
    0x3AB5FDF0182573F6ULL,
    0xE0,
    0x4F,
    0x85,
    0x7F,
    0xC0,
    0xB2,
    0x95,
    0x14
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseDSalts = {
    {
        {
            0x6D021CA4BB71FDE3ULL, 0xB28532607C8F8510ULL, 0x541D3B61D3DF3ED9ULL, 0xFD6866B39086BBA8ULL, 
            0xFA884990FA469C08ULL, 0xCA51DDA4CBEDE6AEULL, 0xA9CA2BD95CBD8861ULL, 0xEC24B2C4286304C1ULL, 
            0x741F24ADE11248DFULL, 0xDEE1B15F698BA8E0ULL, 0x2A0BF3B357EC3D51ULL, 0xA2FBE27CF66FCFDEULL, 
            0x184A45AA9C67234FULL, 0x7FC5341C1258E12BULL, 0xCE886F97175C21A8ULL, 0x474BDD6747D997E1ULL, 
            0xD103A122D981A492ULL, 0x62FA6DDB86D4BB49ULL, 0xE5A632D7C7DCC4C2ULL, 0x56FD6F9543491777ULL, 
            0x0FD9F192C94BC4DAULL, 0xD77F5358F807FBD8ULL, 0x0F53611B9544DC81ULL, 0x3F3617274EFF3625ULL, 
            0xA8B9DD5B92CC676FULL, 0xDC3537968452897CULL, 0xC455313893282ADDULL, 0x712646EE3256EBA1ULL, 
            0xB349A5D18CAFED56ULL, 0xC98385538B0B9539ULL, 0xE1D6C6435855B53BULL, 0xE077ADA9333D1BBBULL
        },
        {
            0xB7775790A1202320ULL, 0x1177E31C908BE7E6ULL, 0x313118213FE668E3ULL, 0x1CE7FC42DC816760ULL, 
            0x6536E4636B80DE16ULL, 0xAE2440B03352CCB1ULL, 0x989BCBD71A0D745EULL, 0x5E91F54DEC86B426ULL, 
            0x3758DA57F72E8D7DULL, 0x7A880E087CF8D0BDULL, 0x6FF928B8F6858307ULL, 0xAE2908C1DD4DB5DBULL, 
            0x98AC1899F3F2E7E3ULL, 0x0DF24355F5C12765ULL, 0x7AE5FDED01655B4EULL, 0x969F13C23B86D0D7ULL, 
            0x342B67BACD16722EULL, 0x0A9F7C67E2563C53ULL, 0x17FBF46A0239268AULL, 0xA28C808D00990C8DULL, 
            0x405A35EA54331ECFULL, 0x010343C702BF4DBCULL, 0x10685E6D55FAB94CULL, 0x0A045C0C8B018FF7ULL, 
            0x5EA86962234D5333ULL, 0x964BB03F88EC56B2ULL, 0x0F66519FC4C09DD6ULL, 0x2E614D85C7443800ULL, 
            0x8C0B5C787C6977B7ULL, 0x66BD1B1C051A4EC0ULL, 0xF50452C01A4EA4B3ULL, 0x27329981CE486237ULL
        },
        {
            0x39C7A8C4BDD927BDULL, 0x819065BCB62B1D9AULL, 0x87DF9504E1078B60ULL, 0xA38612533533F849ULL, 
            0x5B2C62C82406DA95ULL, 0x6D4C2E73F960081DULL, 0x3574D0A92F081486ULL, 0xB229CB463E3D9A76ULL, 
            0x66730B7513E6D54DULL, 0x2093C7E1D4966EC3ULL, 0x1E2BEA109DAC190EULL, 0xAE5BCE474A7619F3ULL, 
            0x4B9108B0F6089359ULL, 0xF8BF92D9FCDECF2BULL, 0x3ABE3C50B11E7CC2ULL, 0x02C5FC9F80364935ULL, 
            0xE14BB9C36D9B235AULL, 0x25C78F8D7018163EULL, 0x8F3B7E2496064157ULL, 0x45D086EB4A306C7CULL, 
            0x9A789E3F290C9D46ULL, 0xD5A3DC771FDF6743ULL, 0xCEDB02DFF5EFA090ULL, 0x2C612FD5EBC46708ULL, 
            0x6AABF5E71BA2D157ULL, 0xA1E43797E563E6C1ULL, 0xD1745C06B432A9BBULL, 0x76529E6D063B4007ULL, 
            0xDB6232CE40D8410FULL, 0x719522CE0544AC3DULL, 0xD068460C92D2E35DULL, 0x40F8E53B46DC9009ULL
        },
        {
            0xAAF08C2463A870C8ULL, 0x5A09C82DA6B7CF11ULL, 0x8E01832D894493B8ULL, 0x16DFE57DCDE18291ULL, 
            0x4B6591F3BD6C7A6CULL, 0xD69D32B76650E7AFULL, 0x01D60A7348C31D42ULL, 0xB194DECB80F52B55ULL, 
            0x9A913F987DA2771DULL, 0xD671B88A631DAAACULL, 0xFE8E51E9D6DDB548ULL, 0xE48413EA6274E4AFULL, 
            0x9F7F69A00D92ADBAULL, 0x63AE4564578E75AEULL, 0x951E4F7A98FCD06FULL, 0x75468D3781D01C1AULL, 
            0xE91E8C4736AF1E3BULL, 0x4E0507BA82813EABULL, 0xF26D7F6BB4609CEFULL, 0x913DAF455E295B18ULL, 
            0xAAAAD990DA93AC8EULL, 0xBCCFE37F7A7D8265ULL, 0x5902D1E1F0FCEFA8ULL, 0x20AE7E0909D90252ULL, 
            0x098D92ACAFB1006AULL, 0x8B8609BB7287E486ULL, 0x2B70A39A5ABA1D23ULL, 0x41ACFBACC2BE6670ULL, 
            0x74164718DCBABD26ULL, 0xFF368690D9D2438EULL, 0xC9417B20EC6573D6ULL, 0x30B892BBA0426AD4ULL
        },
        {
            0x152604A1166DEFCFULL, 0x06186FAE6FDCEDDEULL, 0xA15C0E1060B2890DULL, 0x783C6F91333E1775ULL, 
            0x4AFC3383C1D9B543ULL, 0x51C7E3E4341C5099ULL, 0xFB8679DED66566E0ULL, 0x9F6DF694BAD6DBA4ULL, 
            0xD2966D5F8FBE2B3AULL, 0xE05650C05FC33D8CULL, 0x03EEC9554537D2F3ULL, 0x85352012CADCD015ULL, 
            0xDB4DAB840E43BB69ULL, 0xD0BF01A0E969062BULL, 0xDC3935669157561CULL, 0x104701A7C0FE382FULL, 
            0xF7850564473720D3ULL, 0x11C97D8BD0ECBB25ULL, 0x56653884E59E5DBCULL, 0xB6BB3F465F574F17ULL, 
            0x3CBA980733E9C36EULL, 0x7548B15442348FD7ULL, 0xC5ED47F81134753EULL, 0x0438F749C412E979ULL, 
            0xC9A341847E4C3F41ULL, 0xE7CB2A98115AF395ULL, 0xBC26290CC2B409D7ULL, 0xAB2CF44B1013BD74ULL, 
            0x09049004921EBAA9ULL, 0x0693D7ACF0C11CBFULL, 0x2AB8CB3E0969658BULL, 0xA7499C793C33CDB3ULL
        },
        {
            0x8A92A5E7B6E8ECE5ULL, 0xEFF05CD9C252D79DULL, 0x5817188334428C3CULL, 0x130F601B623F9799ULL, 
            0xB12D6E60A55AC1B9ULL, 0xC0061AF31A401059ULL, 0xD13C1678EB8B6D4BULL, 0x14A5173C1724C3BAULL, 
            0x8B89E8C2997C96D8ULL, 0x579BD619119BBE1EULL, 0x65D1CCBF2CEE8DBCULL, 0x46621A18548EC70CULL, 
            0x6AD0FC67FCD66CEFULL, 0x9BD830E5A4442A58ULL, 0x5F5BFDA1F7609845ULL, 0x392C50C0BD88DC59ULL, 
            0xF12F65DC75B5892EULL, 0xD729F7345B2FE41CULL, 0xD175B911BEE112D3ULL, 0xE5F7A148D998A566ULL, 
            0xAEE32B46C9288DF2ULL, 0xE41509B07BD180A1ULL, 0x3D4C6E7366B1FE3AULL, 0x8D8AAB10D58C5854ULL, 
            0x05F377148EBA95B1ULL, 0x39A7D3BC1DF93FB6ULL, 0xDDA84169EF0BD010ULL, 0x8875B7014A48094EULL, 
            0xDE7698E6AA78A487ULL, 0xCCA990307EBE8098ULL, 0x59717E8758E9F109ULL, 0xA173AADB68BDA871ULL
        }
    },
    {
        {
            0xE386034729B0B409ULL, 0x6DAF46D37EA99F4AULL, 0x20D41DC2C6D6A342ULL, 0xCD31C49A17ECE4B7ULL, 
            0x2E242B3471F8B1B4ULL, 0x79006DB0E5768D9FULL, 0x93EA4799E8FB8AEEULL, 0x779C274C66FF6F0AULL, 
            0x632FEEEB8AD2BCB5ULL, 0x2A25DC06136ED0A8ULL, 0x2550489C1E4511EBULL, 0xB56E58AFD44E9A7DULL, 
            0xA21A83A2AA17E10DULL, 0xAA7AF5B6716DA2C6ULL, 0x2045F42B711C7142ULL, 0xDDD4A6C30E962926ULL, 
            0xEEE5DE21652FD5C3ULL, 0xD9B3DF41F51F931BULL, 0x00E108E818D95C79ULL, 0x390AD115DB35BB7AULL, 
            0x65E248A1FC370F76ULL, 0x2BD4B0157DF903BDULL, 0xBC9E82B20617A03DULL, 0x6A4AA3FA71F1F4E2ULL, 
            0xBD17EF94D7C0760CULL, 0x8B25D15E7C85D5BEULL, 0x2A6069A82B9A4BCFULL, 0xB7429CAFA3519D5DULL, 
            0x568523CCD57479ECULL, 0x1759D2294EA075DFULL, 0x36CC06D32D2329F0ULL, 0xF9C657A395680712ULL
        },
        {
            0xCC896716677A6994ULL, 0x77AE0AED01508A7CULL, 0x6A1DFA11B2C7AA8DULL, 0xC49D525FADC343C3ULL, 
            0x52A9ACB6475D8F2BULL, 0x359F9971F0D45E64ULL, 0x68145601DFF27974ULL, 0x6E0DAEAD3865D574ULL, 
            0xE59587F217722847ULL, 0xAC9D363AF7809925ULL, 0xC3BBF3ADEAEEE77DULL, 0x57CBF3E9644A9C65ULL, 
            0x991B57311768FF9FULL, 0xCCD2BAB1E81D1548ULL, 0x9964A3BABB9BD189ULL, 0x3C3CAFA5528349ADULL, 
            0x73E61AECEB8FCA4FULL, 0x57D143AA163117F3ULL, 0x4A264A77058E3873ULL, 0xDD1CDDB0859712F9ULL, 
            0x8F1A73FBBEA70BE2ULL, 0x3DF0EB19EBE43966ULL, 0x27306ED2EB656FA7ULL, 0x1114D405EF3EB11EULL, 
            0xF05916ACC864F8D9ULL, 0xC50CF61254DC4A6FULL, 0xF09EB3C369167556ULL, 0x8D127FA6B6148479ULL, 
            0x64F1D84DA31DAC4CULL, 0x02EB89685415335AULL, 0x8F64B8F534DB859DULL, 0xDD0CAC322191C723ULL
        },
        {
            0x775893839843C2F2ULL, 0x9FE023FDACB4A428ULL, 0x50CC4D03AA4A03A4ULL, 0x89C557A7A4EE8534ULL, 
            0x5F71E1ECC54916DFULL, 0x8166CC6FA9D4DC68ULL, 0x27473FD2C80A60C1ULL, 0xFD983EAAAF1176CDULL, 
            0xF5B39A63390EFD43ULL, 0xEA79F49723A42230ULL, 0x952059E5012B8A25ULL, 0x96EFB6B760714477ULL, 
            0x2BA17DCE043430DDULL, 0x4E2EEC61FAD38E91ULL, 0xC14147E096486DECULL, 0x481AE786FDC12470ULL, 
            0xE12B08A0A196572DULL, 0xE22BB55B27D06213ULL, 0xC19E2629B1B72039ULL, 0x02E535F1B22DEF46ULL, 
            0x4E6501401645580DULL, 0x14DDFF54AC485734ULL, 0x8157F54C0C07257EULL, 0x2B4369C684440716ULL, 
            0x4639ACC1B753BCD9ULL, 0x8B967AFA4914D542ULL, 0x6555E63DA714DFC8ULL, 0xD70C830278B386DAULL, 
            0x3936A8D2EC9409B1ULL, 0xAAFB46FD5FBBA5C0ULL, 0x519726D3C98195E0ULL, 0x98DFA2429F13AB05ULL
        },
        {
            0xF784570103A0C8E6ULL, 0x45FAC55BAB34478DULL, 0xC18DAC607A185DC8ULL, 0x00642A439453707EULL, 
            0x2C73D67C5A182F12ULL, 0x1E0B3D30D29D009AULL, 0x0868AF9FCECE8485ULL, 0x887BD18C93D95C3AULL, 
            0xCD46815E05076D75ULL, 0xF71FA32E746BAC81ULL, 0x93271A1BF4004E8AULL, 0x81F524FCC0767F69ULL, 
            0x90578388C1EEAB36ULL, 0x6E68E40DE113FC9CULL, 0xE0B0A0702D50DACAULL, 0xB7014FB253AAC235ULL, 
            0x5689BFAC0192483AULL, 0x927311BB562C19A3ULL, 0xF72292A1254A8261ULL, 0x9AA33988C76B32BBULL, 
            0x233B70AD91EB3CA0ULL, 0xCF1F4B680A4F5B78ULL, 0x7FB30A90796AE860ULL, 0xBCB7AB9EBBBB54D2ULL, 
            0xC5CF6B558742AC33ULL, 0xD5C85757541F3B79ULL, 0x54BB8F60D552E903ULL, 0xC13691593A38CF9CULL, 
            0xAC9A1A37A0171AE5ULL, 0x4D3B7E0D300FCAD2ULL, 0x481683F533F7655DULL, 0xFB4A6A4071249FB2ULL
        },
        {
            0xEF5798033E837796ULL, 0x141B926F701868B2ULL, 0x5ECA7CB023A5DE1CULL, 0x573CBD78C28BFACAULL, 
            0x8C94F97C24499359ULL, 0x39122CC953F3BE07ULL, 0xFAF2E72B740C346BULL, 0xDB959B099FEFE6CBULL, 
            0x2F48BD7D785741C7ULL, 0x71A8FB8748538D76ULL, 0x627C66B65D826A07ULL, 0x31E8F0626D1B9217ULL, 
            0x926E77757C4DB67AULL, 0x630A974034B9705BULL, 0xC14620A5B144F8FBULL, 0xF0133C5DFABEAB36ULL, 
            0x2F59E3758C03EF91ULL, 0x8C0C20597682F357ULL, 0xD43689E77BFA59DCULL, 0xE83035BDD49FF4ECULL, 
            0xFE2F99C2E78D8E1EULL, 0xDD2328840ACA05AFULL, 0xAC8C6D57AB1851AFULL, 0xCB730840E65F7317ULL, 
            0x80B552B254560B15ULL, 0x485E877D2AD6C569ULL, 0xC0464CD3B4281E05ULL, 0xB65897C0A7CD04B0ULL, 
            0xC36CD73F085EEF0EULL, 0x28BCAC2A34C9D854ULL, 0x83778587347096ABULL, 0xB93C63FD4C6BED53ULL
        },
        {
            0xB7B530B255736ECFULL, 0x7C84908A8A5D2911ULL, 0xE2CE5892A4E8BB4FULL, 0xA906D84A1A31137CULL, 
            0xE05326150292FA94ULL, 0x5D49145522424F13ULL, 0xA29C92E106165D3CULL, 0xFCC2F5B0A5375312ULL, 
            0xA625D995D41A64FFULL, 0xA31858FEB5094141ULL, 0x05D1F942FC45F7EFULL, 0xFA9E4C27C369591BULL, 
            0xED6F8EBD808252E6ULL, 0x1A08A74698D63FACULL, 0x6622B88F0B4DFC8DULL, 0xE5A5F61DD115F0BCULL, 
            0x158B96104DC71381ULL, 0xE3400E2D38DC57DAULL, 0x0BB6C7CF60998F1FULL, 0xADEB1DD52F8CA924ULL, 
            0x947599F1BBF5F48DULL, 0x20299A9775C083FCULL, 0x1ECA11C9A0AF36AEULL, 0x50327D3A28C0167CULL, 
            0x5BDBF81892297D6CULL, 0x87CF5A9B31E4F41AULL, 0x4CDCDE6CFDED140CULL, 0x5654FCB5D796252EULL, 
            0xB0D817493CFFB982ULL, 0x72DDD8E1737E06D9ULL, 0x0A19C54578C2FFFAULL, 0xFB596DBD8569181FULL
        }
    },
    {
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
            0x7B4FF8F47AD271D5ULL, 0x23135D164F50835DULL, 0x1BBDCB4DB928630EULL, 0xD628A0AEDDBB3B7FULL, 
            0x7BEEE524F3096EE7ULL, 0xDA82C6F9A24D8C96ULL, 0x045F5642EBA86ACEULL, 0x17A9E5B0F28BF681ULL, 
            0x65956986D0230765ULL, 0xD9B81CFCA13EA9CCULL, 0x20CF04378181017CULL, 0xDCD83F5A64C42E01ULL, 
            0x6101ECCB99596CF1ULL, 0xC7F1E078595C1BD8ULL, 0xA80831AA6B64C59DULL, 0x8804E30E51D6DEA3ULL, 
            0xB43FB89E3DB33963ULL, 0x22DA2DECD8E27FC6ULL, 0xFA38863CF2DC48FAULL, 0xBBB5B682F73D2697ULL, 
            0x82FF0733E8CD10D0ULL, 0x2A41FF8A4E149C40ULL, 0x974E9E79D125869DULL, 0x65CDBAFD647CF522ULL, 
            0x308AD6673378803CULL, 0x2DCA9E7ADA58DFBBULL, 0x8C619BEFFF951D60ULL, 0x62C9935DA105E667ULL, 
            0xC35A72BACB9699E0ULL, 0x066FE0137AC2BA75ULL, 0xB9013C814C0B10A7ULL, 0xCCBD417AFCBDA27FULL
        },
        {
            0x946A1F4107454B20ULL, 0x683BD3F293B96FC5ULL, 0x773971DE4B594B48ULL, 0x75E26A0F6E4EAD25ULL, 
            0x8C636029E578A02AULL, 0x2000C190706693BCULL, 0x6E59DDFF9DD6DFECULL, 0x5F07FD406342331BULL, 
            0x27CEC7953A639678ULL, 0x75C8361F39770ABFULL, 0xFE6A6E4549480EAFULL, 0xAD38FF4CF29D5A04ULL, 
            0xB41CA8D37BBE8328ULL, 0x78181CB086129CC8ULL, 0xA6EB715FCB5A33ADULL, 0x1975934FFED8B2FDULL, 
            0x21BA5BE832B11366ULL, 0xA4F904219777085CULL, 0x3F232F1B6AF2D4E2ULL, 0xD64777080ECAF8F9ULL, 
            0xA5AFD29275788A2DULL, 0x675393079E803EF6ULL, 0x6E2C2950D0B0B1A3ULL, 0x1AEE6CE60D35DCC2ULL, 
            0xB7383B33FFD166FBULL, 0x1472D4A936327347ULL, 0x3142038783C5907EULL, 0x1D673AE5CB02AF80ULL, 
            0x51BF982D3EC1E938ULL, 0x629C48EBDE2258C9ULL, 0x08DBE1674A717CADULL, 0xE5A2021FF23C9CC9ULL
        },
        {
            0xFC515DFC71C6F3FAULL, 0x92EAC6D0BEFE88DBULL, 0xE47ABEB162611744ULL, 0xE2980237E5A38A17ULL, 
            0x410BE8976BE8EF94ULL, 0x6819AF6DF8DB890CULL, 0xC3628D57419D9956ULL, 0xEFF5CB19681E6D97ULL, 
            0xB6B4972982991DCEULL, 0xACE473C274664034ULL, 0xE438238C7691AE48ULL, 0xA8E74FB34F53BBC5ULL, 
            0xCB893F1D0050B09FULL, 0xFDF3A6D2591F4CE8ULL, 0x5B6AF4D521639264ULL, 0x11F2F83D4EB0A8CEULL, 
            0x260AE20D20F72E09ULL, 0xAEB8DCD72974E693ULL, 0x54E29CBE12CBC57AULL, 0x6CE49FBBD752A76EULL, 
            0xF9F633A4EEDAD455ULL, 0x8E1E9AB6253F8F5DULL, 0xBECEFCE7AA7CE5B0ULL, 0x7A691D6323D614E6ULL, 
            0x1935B0CD992E6D61ULL, 0xABAF227743622D2AULL, 0x18ED0C85B544FDCCULL, 0x1E195F8CB05037F1ULL, 
            0x1B6CAE91E47C8E7DULL, 0x48FFC7178D1576BCULL, 0xAEB3352D7DEEDDD0ULL, 0x7F1B3D21BA33E638ULL
        },
        {
            0xE10B6ADB77A991F5ULL, 0x28CDBC4338381E20ULL, 0xBD224BB258C0F244ULL, 0x8E56385418A0ABC4ULL, 
            0xA8A15858522E3F26ULL, 0xAA5FE1B87C3F1DDDULL, 0xB9E16FE265043AA0ULL, 0x3770643E5759BEC7ULL, 
            0x15A4C3404608941EULL, 0x55CACF9E2D553004ULL, 0x0A22C28178DD445AULL, 0xF9DCDE134A282775ULL, 
            0x635246F0DC719FE8ULL, 0x2860F1F4BFFF9469ULL, 0x5C6A1DEED88AEDD8ULL, 0xFBDDECC6E506672CULL, 
            0xA5D638F6F6F58628ULL, 0x5A6EF1A881E4BC19ULL, 0xA4934E70D0E45BB1ULL, 0x4C6161B0C86739C2ULL, 
            0x7BBE295E0A3F0041ULL, 0x23A5ADB8A7128C5EULL, 0xE1E77EB30B4198BBULL, 0xD8B2C840EA4A8002ULL, 
            0x073941F9CF23F39AULL, 0xEADE0C8C56ADE5D7ULL, 0x373338FFB40282B2ULL, 0x5B9C014FDA181FEAULL, 
            0x18B563B3F6541FE5ULL, 0xBAADEBCB707F694AULL, 0x8ABD692E3FC3E623ULL, 0xDA595E2053134CFBULL
        },
        {
            0xCAA71C5AA54FAB6BULL, 0xAF238B8B7DB98A23ULL, 0xCDE47D08CB0E85A2ULL, 0x1003380B63EA2FBBULL, 
            0xBAC4499CB18308F8ULL, 0xCFFDD933B47268CFULL, 0x520AD09E628DE96BULL, 0x551E3EB031BD7BDEULL, 
            0x1BF3DC743FD01832ULL, 0x72643087309DB87CULL, 0xAC75A05568F1E578ULL, 0x06CA7608AF26487AULL, 
            0x739A443A15DE16BBULL, 0x9D1962F33C943C7FULL, 0x0D2D384A5220B3D9ULL, 0xF9E7714C07E2B80AULL, 
            0x11B3638DE74A05E6ULL, 0x031C1C7483CD0F49ULL, 0x8E4669BE1DD24DAFULL, 0xF4BA8A79CF633C5CULL, 
            0x3CCF1690F6CA8C97ULL, 0xBAB7910635384905ULL, 0x07E9AF7A05463BFAULL, 0x8116FA189202D9D0ULL, 
            0x82C716C591984E38ULL, 0x221B23FBE1E2451AULL, 0x18A73124DCE21845ULL, 0x69B174B73775AEB1ULL, 
            0x24F6BFE1871BC978ULL, 0xBC7439767E5F5B11ULL, 0xC2CDC17B5652472EULL, 0x5F4D6EE3B9636C48ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseDConstants = {
    0xF9C97E59E64F56FAULL,
    0x021F2E34E8EA85ABULL,
    0xAD4061C19B0E1553ULL,
    0xF9C97E59E64F56FAULL,
    0x021F2E34E8EA85ABULL,
    0xAD4061C19B0E1553ULL,
    0x46AAE2D1978E9150ULL,
    0xEA95338FE3414BABULL,
    0x5C,
    0x81,
    0xB5,
    0xA3,
    0xD1,
    0xB8,
    0xE1,
    0x49
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseESalts = {
    {
        {
            0x14EAAA621DFABB54ULL, 0x363E4B3E06A0AE6DULL, 0x04AE94AC7A2B4C32ULL, 0xC17C288CF7C6FF49ULL, 
            0xE31DC0BC6C7D9DB7ULL, 0x6CF2A386F73261ADULL, 0xA82D05CB6D4CA00DULL, 0xB5A43547268FC663ULL, 
            0x2299FD70FD6C4B5CULL, 0x70D3F3B4C1297839ULL, 0x61E36A7551C8A48AULL, 0x728F4DC5095BFD0FULL, 
            0x920DB9D31D39A563ULL, 0x93E7C1F469877BDEULL, 0xAC1B29F0A9474976ULL, 0x1113E2E1E17E8F8EULL, 
            0x29F6B5F12FD54FB8ULL, 0xD7215C72B4E1B2E4ULL, 0xB6910F15E238DB22ULL, 0xB6C9A7A2CF4A010DULL, 
            0xA90E697368B50339ULL, 0x7C1B66920BE1ACD4ULL, 0x3CDDC464F256DA49ULL, 0xF18F0113DB89A11EULL, 
            0x1EAEE10DB589A7D0ULL, 0xE5D6B2AE418D43C5ULL, 0xE954F80EA90EF5CCULL, 0xF3407183E43BFCBFULL, 
            0x3C7031CC8C524217ULL, 0xFB82A54DED928B87ULL, 0x9F8C4538822E78E6ULL, 0x967E1BCF0B090C4AULL
        },
        {
            0x92BA979E678266DBULL, 0x1EA40E4937D4273AULL, 0xEEC295356685F6E8ULL, 0x674AC93A4AE12103ULL, 
            0x92EBC109F1008D43ULL, 0xE5291FFDC23D6DADULL, 0x33A6B6CA7AF0753AULL, 0xB4E5BEFADCC14FC0ULL, 
            0x4DD6CF09A2835477ULL, 0x82D571250699E142ULL, 0x85400CD1B2939C20ULL, 0xA98B04D3B09F3E70ULL, 
            0x396284B98F5A237DULL, 0xEA4F950FB4A18621ULL, 0xAD96AE8E8FD44530ULL, 0xC3EAE486FDEE9445ULL, 
            0xEEEE0E35F37CE945ULL, 0x02976B6A3D27105FULL, 0x793A5385DDA7EE9AULL, 0x8E363D4BA356E14BULL, 
            0x04E154E2C8AFF79AULL, 0x3757CDDB4C0BCBBEULL, 0xB813DF67141D2C2CULL, 0x75A932A1B80040F3ULL, 
            0xB984897C8F57AD89ULL, 0xA5DEEEB87EC9D9DEULL, 0x2A92FFACA029A6F5ULL, 0x434C3E0CE390B284ULL, 
            0x2FB86F1183D0DCD2ULL, 0x77889AF3C6C48A3BULL, 0x9DC1AB7D73A48AA6ULL, 0xC2C12864D46E37E0ULL
        },
        {
            0x4332BEBCD8B07848ULL, 0x8A7F0760566834A6ULL, 0x464464A540ABAE54ULL, 0xE5FB2F23D40E7747ULL, 
            0x0B153114A634973BULL, 0x84CC6B658953BD9BULL, 0x909E053C1908E66FULL, 0xB3F43CA91833EFDEULL, 
            0x91A7B96E2130F00BULL, 0xCCA3A127705592A6ULL, 0x7663F2953D7FD857ULL, 0x5B83C6C1C64AEB91ULL, 
            0xD73E4B3FEFA4BA0AULL, 0x45AE9398D542954CULL, 0x9B910ED9F07D038AULL, 0x6EB2E2E2403FA52BULL, 
            0xEE8F280963D310F5ULL, 0xF62F3D3BBDF53EDDULL, 0x86BADBCE475511A6ULL, 0x156CFC60E897F73BULL, 
            0xBD292AB80A89A89CULL, 0x39424C46E10D007AULL, 0x038346CD6FE58060ULL, 0xE5BCA42B62BF003DULL, 
            0x0C78D3ACA2E76728ULL, 0xF781E5D1D0DAF2F2ULL, 0xD50185CE32D40D51ULL, 0x79C21F1C2D9376E8ULL, 
            0x184683D2FB4583C2ULL, 0x76444AF2A8E4DAE2ULL, 0x6E19CCA6D66C0965ULL, 0x0E935B7022DDB6DEULL
        },
        {
            0x9574361308E6ED91ULL, 0xA5BF9E6D52A50D28ULL, 0x7660317369550A9EULL, 0x5C99064962EC4992ULL, 
            0xC0A288AA3E78BCEEULL, 0xE1F45884C1513C95ULL, 0xD31B351D84FA684FULL, 0x15382D7B1BC7C7E0ULL, 
            0x669094675663E507ULL, 0xAA19D0559DEED8EBULL, 0x1234A8E3F495F35EULL, 0x21694D9B43525782ULL, 
            0x291CAFEDB143E764ULL, 0x952C555765CFDED1ULL, 0x3D51399F18B51267ULL, 0x9E22E47C33B967DBULL, 
            0xC6269A3984395151ULL, 0x1BB1B290EFEA63F3ULL, 0xC5B1042EF7EB8D24ULL, 0xDDEF06EA1F15725BULL, 
            0xAA48D2C7B37408FBULL, 0xDBB72610F8B38298ULL, 0xF732C50F8966730DULL, 0xE4D1C53CAEBBE089ULL, 
            0xE820A5ECCE6324A7ULL, 0x20B2375576603B70ULL, 0x861D7817F633C9E6ULL, 0x07236D1EC5BEC117ULL, 
            0xEA1B5ACA698A0C50ULL, 0xCD2666D1F7BE11BCULL, 0x289E7ABE1F23FECEULL, 0x9F17F7D0FC4945D3ULL
        },
        {
            0x686C98C4A2E55477ULL, 0xA7A62BCB05D32728ULL, 0xA63581FFC2754626ULL, 0x583889A866F636A5ULL, 
            0xC5B1C7E2BC9A2903ULL, 0x06352488FDB06BF6ULL, 0xA5AE006CFF6A0D32ULL, 0xBA31C2E648ADAC62ULL, 
            0x00062161EB7C71E4ULL, 0x750B64922298682DULL, 0x002CC7DF1D3BEF1AULL, 0x0B8E67E258080A5FULL, 
            0x073A2381E7895E1BULL, 0xF4B04BD2F3E7DEBEULL, 0xBE1A1E2ABD20A23BULL, 0x9D8FB86FEE031173ULL, 
            0x76E351096B834F76ULL, 0x669DFC2B92676A52ULL, 0x5BAF041122C448D8ULL, 0x462D08F231E7C38BULL, 
            0x29FAC7FD949C4459ULL, 0x4DB88DF15A711590ULL, 0x2421CB10EE481C8BULL, 0xC201458D35DA68D7ULL, 
            0x25C078ECA0F8704EULL, 0x3CA11B0A36DF7C31ULL, 0xFCA9593E192669E1ULL, 0xEB99FB4896D5642DULL, 
            0x9D7D8E31BB8CA0EFULL, 0x80962538281B00E7ULL, 0x68E819E4CAE57EE9ULL, 0x2F7738906660828DULL
        },
        {
            0x8D3A064DED779D71ULL, 0x006DB64AF3BF649CULL, 0x537699FCF24CB971ULL, 0x3FD2D78F71218AB2ULL, 
            0x500D0C4407E3E13EULL, 0xF9F4B46645799D74ULL, 0xE976B6C3399B7F28ULL, 0x5226AC3623509166ULL, 
            0x2C95CD97A0FE713BULL, 0xA1CDB692A416706CULL, 0x5D1A6FB3DD6B1E91ULL, 0x0CB4142D6A8CDEBBULL, 
            0x851EA7D83D1E310FULL, 0x42E7EDCA9870C01EULL, 0x4A06B8D6DEEC7EF9ULL, 0x8DF753E5D3CCF752ULL, 
            0x9F55C61770EB5397ULL, 0xA8F0A5850F0EB296ULL, 0xE284C12A6AFA4F28ULL, 0x20AE1B757123FE33ULL, 
            0xFDEB9DAFA602CE15ULL, 0xE14BB260F7FEFF24ULL, 0x514FC6F5A3F45C68ULL, 0x9052750910B1DEB3ULL, 
            0xA9C49D03847D9396ULL, 0x8C88F553E053AEBDULL, 0x64170BBD0A9C9DA9ULL, 0x7D7B5E9334967452ULL, 
            0x0D0E389C181944E1ULL, 0xE00B916A4F60B8D9ULL, 0x5A36300AB489414FULL, 0x81968EE47EDC7D0DULL
        }
    },
    {
        {
            0x454B5A0E625238AEULL, 0x98FBBDDAF04264A2ULL, 0x9C29FA9F95A5BC28ULL, 0x716D4CC08B5030A4ULL, 
            0x7F261ED3D7FCF877ULL, 0xA9F7AC50CF69CA01ULL, 0xEBC815FEBC1296E6ULL, 0x8657BFBA191CFF43ULL, 
            0x335B2BA5CCFBBBEAULL, 0xE35AD1B2F81D9BDFULL, 0x1CE7B4659C24381CULL, 0x5015AFF2DB03B6FBULL, 
            0x84B8B66128519ED1ULL, 0xDC8F7B37952233FCULL, 0x002B21F1C64413EBULL, 0x65B9F870C6D94022ULL, 
            0x8C27BE624A76F63EULL, 0x097AF421B856F6E3ULL, 0x1CDD538A762722FBULL, 0x927AD11D1412E98AULL, 
            0xE14E14D961A62C2EULL, 0x70B1013D87FBEB97ULL, 0x0BE16B04A2A4297AULL, 0xFF84BCA8FAE30530ULL, 
            0xA80768306E50140FULL, 0x41CC84C20C6CB23CULL, 0xE8644141483C0933ULL, 0x747AD22FA73CA4C1ULL, 
            0xC2DE7535A61D3882ULL, 0xFAE7D2FFB8D5C7C8ULL, 0xB98048100002D472ULL, 0x4DF1A1455784C87CULL
        },
        {
            0xE918E0C7B7E89C0EULL, 0x27BD7819F7A13810ULL, 0x869F2D03B6DEB23CULL, 0x4483870AF0435865ULL, 
            0x4723EFC172D18B18ULL, 0xBDCDBF061ADA05F8ULL, 0x3AF0FDC0780844E4ULL, 0x4F0CE9D0334C56CCULL, 
            0x6965D66852F4B0E0ULL, 0xEBD382B8D52D0D1CULL, 0x6118BA0B55CABCCAULL, 0x3F9D313733059308ULL, 
            0x3AA46A0ED37ADF87ULL, 0xB53328B70A48ED5DULL, 0x3CF30EA82FEE47CCULL, 0xF5D60B1ADF8E32CFULL, 
            0x0F784E8D0DAAC4FDULL, 0x98D999F92DAEA7BAULL, 0x7E7F0AFE611F619CULL, 0x17A8FB2F5D2E1C9BULL, 
            0x430F634C99759C4AULL, 0x4759C3E33B2F130CULL, 0x946DC7BD90F15F0DULL, 0xEAA5D48FDB4A5682ULL, 
            0xFCDCE20BADAE7FEDULL, 0x1DAA47D57E46AA26ULL, 0x5396B018D4D78B66ULL, 0x1C69C6A6953CC148ULL, 
            0x666401F8E62C4FDBULL, 0xA4A5A617B6B979EFULL, 0x82C6BE4FE17D2D82ULL, 0x31F0AD412E48DAD1ULL
        },
        {
            0x9257773086512FCCULL, 0xBEE27DE8B4CFB374ULL, 0x1510021EF2E65211ULL, 0xFAABE3C1B700A35DULL, 
            0xC959E01CA84CEB00ULL, 0x55B0B8E4F63F9EDFULL, 0x2F066C80815FF24DULL, 0xA7738AC8B2D4BE80ULL, 
            0x5B4DF15BC412A1A4ULL, 0x359E9F09A06278B4ULL, 0x15AB9FC152121CA4ULL, 0x32B035D8E03EE42EULL, 
            0xE3E29D46F0511617ULL, 0x0B8E8D2953C66FC5ULL, 0x70D9C54406C4005AULL, 0xAA1DF35E52BA83BAULL, 
            0x131495D051680B57ULL, 0x4B5338040D50F6D9ULL, 0x7F4A1E070903AE1AULL, 0x897FE6E3E77B252DULL, 
            0xD3DEEF9926D076E3ULL, 0x3FF9951582F282D7ULL, 0x88861AC06E870712ULL, 0xD3C1FF867B7A2D0AULL, 
            0x81959C6ED44E6916ULL, 0xF8BD576D00E8D88EULL, 0xE576F6DBCA1CA0E2ULL, 0xD9F961709247C616ULL, 
            0xDE6A99B0988E10DFULL, 0xA578DDE540CE2DCDULL, 0xFE1A191D4D6BB0B8ULL, 0xC2FBE6DB345880B4ULL
        },
        {
            0x0454F1E69842B588ULL, 0x5BDA0ADC99873831ULL, 0xC782CF3F6E59024CULL, 0xDBB3FB841E1ADCADULL, 
            0xFEB2B385628437D6ULL, 0xF28EC08B5775B6A3ULL, 0x438E04672C1D88F6ULL, 0x505D93E0D1B2F523ULL, 
            0xFB9E186BA6929927ULL, 0x5DDB477BEFEF6283ULL, 0x9EF76BF4BEA6EE6EULL, 0x4765EEC98B6D7911ULL, 
            0xA6608E2F3CAF075EULL, 0xE48C85F54E990400ULL, 0x15E25CCE09D4A1E8ULL, 0xB30C4487057D2D4EULL, 
            0xDB4D286566A90B79ULL, 0xBEDB1AB8B4194C42ULL, 0xBE65D225ABCBF539ULL, 0xBC3B3564DC9C47B0ULL, 
            0x7CE074488679F8EFULL, 0xE1A4904E2E37CCF5ULL, 0xE1D8E64BD85B3FB2ULL, 0xBAF7427599797223ULL, 
            0xDBA4C2BD1ADECEAAULL, 0x80BE6C96489B4D2AULL, 0xA0EEE7A027EDDA5AULL, 0x433A45928ED2DC00ULL, 
            0x8A940D5D3B4BDDB3ULL, 0x47D6449597236A49ULL, 0xDD906DB867910D2AULL, 0xC48B5DC44354BA9BULL
        },
        {
            0x2632E937CFC01D40ULL, 0xAF4E976730B57D4AULL, 0xF611212F8212F59EULL, 0x5DE0EAF3BBD62C76ULL, 
            0xFB6A5877E113691CULL, 0x42D3C5ACE15D71F1ULL, 0x9FCC0C3845C948E4ULL, 0x05C6871F00CCF024ULL, 
            0x2640061BB4CC3110ULL, 0xFB08D94596D6BAB7ULL, 0xD309BDE1F6F96839ULL, 0xED4AAAB70DFBC9CBULL, 
            0x7A888047302344A8ULL, 0xF362A8CB8F39AAA5ULL, 0x13E89E6BE3CE78EAULL, 0xD6F47D3685FC0783ULL, 
            0x114C2F94B115AB41ULL, 0x227DEBD014BC2F18ULL, 0x5FCCCE94166658FFULL, 0x2B45A3AC00262678ULL, 
            0x08F17A8937DF6B69ULL, 0xE18225FB89F475C4ULL, 0xCDFD6A0A876D7498ULL, 0x4D2DA2D90C098A8CULL, 
            0x2FFE5AD7D8C23189ULL, 0xF9900B65C6A89572ULL, 0xB70171CC38324D7DULL, 0x26F9AB507AAEA80FULL, 
            0x698E0DDFD3C66CF3ULL, 0x857BC3FEE2BB4BFCULL, 0xB34856A315CA31A2ULL, 0xC74BDFA7345EB214ULL
        },
        {
            0xF5452D30547F8C28ULL, 0x6040A03E556B4D7DULL, 0xEA541D597243880FULL, 0xC3B5162792C6ABE6ULL, 
            0xF91C982B332AF086ULL, 0x1002453D3B30E438ULL, 0x768CD69CDDD9BB6CULL, 0x3E8F1560B2DE5698ULL, 
            0x8AE84EFE01B93009ULL, 0xA89590A15EF87186ULL, 0xF2EA6BA38CE5DD05ULL, 0xDAA595E6129C4BBEULL, 
            0x321957F212111182ULL, 0x06F134692658F9DAULL, 0x240E0EBA42390CF3ULL, 0x2F700688D6926BBEULL, 
            0xC415E035731EFDB3ULL, 0x4725438D8EC3BC17ULL, 0x63A794810868D234ULL, 0x55B9B47273FC4216ULL, 
            0x3D8170E85F730949ULL, 0x603A5C8561A61EA8ULL, 0xC0A8C038926772D9ULL, 0x453B9F6524AA1C88ULL, 
            0x97A330E4F3EBE080ULL, 0x23855DA7385E2D97ULL, 0x90EB7A0EA5B88B51ULL, 0x7AC53786C2ED04D0ULL, 
            0xB19E97E52456578CULL, 0x661B2641D825A3D3ULL, 0xF9983F3B9C5BBDE5ULL, 0x15480733D7C7DBEFULL
        }
    },
    {
        {
            0x5AB79EDC6E3AA3AEULL, 0xDD316347437CADD5ULL, 0xAA06B0EE401A8E9DULL, 0x32A6EDE2DAFD54C5ULL, 
            0x1C70BE53B836E731ULL, 0xD58A9C5F22D7ADDFULL, 0xE75B65CA8A0DF399ULL, 0x15F0EAEB1E0060F8ULL, 
            0x362F67F62E114BE0ULL, 0x54D8F785A7FAC13BULL, 0xA5CB3AA334981A92ULL, 0xC2CB19217FAF2F2EULL, 
            0x3105A0EAA476F805ULL, 0x7A88FF14CBC4E6E4ULL, 0xA406C1BB55FD3CB2ULL, 0xE6E5E284CB083295ULL, 
            0x2EA34C1F1430580BULL, 0x75DA3369E19C5467ULL, 0x49E95A32EB8B1209ULL, 0xA33A398AD5F2B10EULL, 
            0xDA68A83EEECD22DDULL, 0x496381093EF635CEULL, 0x0D3EF7287A47E091ULL, 0x01275BA7401EF5ADULL, 
            0xEE7E13AFD479F815ULL, 0x67535B5AA6FBCBDAULL, 0xCFAB00ED43CDD1AFULL, 0x34F12A9F215BFBE1ULL, 
            0xA3171CB9B97CBF4FULL, 0x6262E1E7E05EB990ULL, 0xFA45B9EEC07036E5ULL, 0x071DD5DA6D37575AULL
        },
        {
            0xC7EC69B50ECCDAB7ULL, 0xE3157A192EFD7B3CULL, 0x317DB9C72ED43768ULL, 0x892EC94D94D9279FULL, 
            0xA4135438D7465040ULL, 0x939457A36BEAC524ULL, 0x627B26C5482FBBCDULL, 0xDC4E0D820F9726DFULL, 
            0x5890A8A7D147E0ABULL, 0x616B4442CEA78168ULL, 0xCC270B1651E37338ULL, 0xF661AB2C6DD9D63AULL, 
            0x711A2EB142E9978CULL, 0xD39EF3F077227FD4ULL, 0x10B8F04D0D2FDA39ULL, 0xF78B72D1CBDE2F36ULL, 
            0xDA06F93BB1665445ULL, 0x656F734AC38325D1ULL, 0xCCD40A78589DF077ULL, 0x68B7AE961DA0CB5AULL, 
            0xD7231FFF25444397ULL, 0xA2F9F63A3DDA0A2CULL, 0x5E07256E6F86D285ULL, 0xE559FC7558FBDC3DULL, 
            0x714D60053E04A05CULL, 0xEF1D0308075F3921ULL, 0xD4382C6F9462969AULL, 0x6A94B1C854984AC7ULL, 
            0x8780788D6A3E690FULL, 0x9A9C18B4813626F9ULL, 0x4D51118703C38B3EULL, 0xF0C1BB190646EB25ULL
        },
        {
            0xE4F60F5339511817ULL, 0x1DCD96DFF9EA12CFULL, 0x655FB699D6D81A15ULL, 0x4FE2ED68FDFE5ECDULL, 
            0x3313ABEB1C25B92EULL, 0x2170962CFE24DA66ULL, 0x11D93996489B1E51ULL, 0x1815EEB421AF7011ULL, 
            0x738DDFDB8781A3B0ULL, 0x8D9C008AA30B98D6ULL, 0x4A48C320DB90006FULL, 0xF617FC8A9C4AF90AULL, 
            0x20DFB9696BA384F8ULL, 0xD48914AB46FD9982ULL, 0x481831D58E3F8B39ULL, 0x461B5664B231FFD5ULL, 
            0xAEB7B454C879ACDFULL, 0xB00951E8A22CA3C1ULL, 0x6C08B7883DF1A3C1ULL, 0xBC0DA9EF7183A877ULL, 
            0x1DB176BC8C66B9F0ULL, 0x402E417FACE66BFDULL, 0xE661C1329B43D038ULL, 0x15F97B156328976AULL, 
            0xBF08811EBDDB0752ULL, 0x22F2BD3EBE2A7447ULL, 0xAFDA1B5722E9FBF5ULL, 0x8AF46BB99F9EA894ULL, 
            0xFC5A897022D49AB5ULL, 0x75E04E498B6EB520ULL, 0xC6FDA173DADD71E0ULL, 0x652B3EECB915A3D3ULL
        },
        {
            0xF9BA7A57DA360F6FULL, 0xC106F60EC6A0C622ULL, 0x2D8EF2DB0892FAB8ULL, 0x1D3C29BFD715B924ULL, 
            0xEA714982AF1F0E48ULL, 0xA7FD14671970152DULL, 0xACE1DD51009E6353ULL, 0xE7053CB2D7E61F80ULL, 
            0x7D8EBC10AFDE51D0ULL, 0xD01D6FF1D01A4CD6ULL, 0xAB4C32A61FAD3E1AULL, 0x25F8928FE751D78FULL, 
            0x63828078C50DF916ULL, 0x18A76A92CC60F487ULL, 0xB3B93FDD8C8D2BA6ULL, 0x9BBCFD48641BF310ULL, 
            0x5C113796BE2C1F2AULL, 0x8F04581FB3C79B7EULL, 0x74472340D47DA9E1ULL, 0xD034A70DC4285707ULL, 
            0x170F1F2DA0EB9174ULL, 0x4B8BB76B568EE1E7ULL, 0x05703FBB43DB67C6ULL, 0x0E9BD8E493E8502DULL, 
            0x9B3494DCF10468B0ULL, 0x3AAC8988D9F8E621ULL, 0xDC2364E03C5A4D0EULL, 0xF17424F964755C99ULL, 
            0xC263DBAEE2B0DD8CULL, 0x455232F0727FDC41ULL, 0x0201907EC4E153DBULL, 0x80232AE1A9F62BACULL
        },
        {
            0x82727F5DD6124E03ULL, 0x4FB4B52AFA1ED7CFULL, 0x635EDBA4F3932D39ULL, 0x2EE1D91CAFA33045ULL, 
            0x1E1FE8A271458576ULL, 0x6D1E0B41B94642F1ULL, 0x440C2F75927A493EULL, 0xA8E547612CEB8C11ULL, 
            0xABEAF9E75F1989E1ULL, 0x1162A09E58A07F6DULL, 0x3C3650A9F1BDE515ULL, 0x66BD742F2918240BULL, 
            0x43A9402FA5EC094EULL, 0x420F1359C226690CULL, 0x9C258858C5E47908ULL, 0x2590BD1B59CD28DDULL, 
            0x66FA57B785BEA441ULL, 0x6699F6867191BE71ULL, 0x62767CEE5EFA9560ULL, 0x09CCE2B632133046ULL, 
            0xDE8506CAF9377B0CULL, 0xC5127176AB47D4D6ULL, 0x9407EAC4F8F85D0AULL, 0xEA97CC0F4F66130FULL, 
            0x1CB37DDDB0CBFB0CULL, 0xB23BD9EB319B0FE5ULL, 0x1CD617529725B3ADULL, 0xC34B016AE9A73BEFULL, 
            0xF13F70C9D0FB8E4EULL, 0xCCD87CA2EE517A91ULL, 0x7DB5E4FB61851488ULL, 0x81E77187393F2A51ULL
        },
        {
            0x2664617E7576BA4DULL, 0x9374BB75B6D1A3ECULL, 0xE7D3F6346DD0A950ULL, 0x6CD868C0487643B9ULL, 
            0x6AE599DCA951B733ULL, 0x3F2CFE388EBBE1EAULL, 0x9C2C5C773DE2C572ULL, 0xC038F26A62237B13ULL, 
            0x000D08758CBEE689ULL, 0x6E16E20AB2F7AE74ULL, 0xAE7944FD72E5680BULL, 0x293CD08522E5778BULL, 
            0x342990C30904E025ULL, 0xD33878205206A26AULL, 0x66B46FE2383B1CE8ULL, 0xF28A15DC2E00E1E1ULL, 
            0xCC862CB3DD61809FULL, 0x80F2EA850FDE01A0ULL, 0xFD83E5E47ED9489BULL, 0x0F629C93A524BE6DULL, 
            0xD98B97CDB6B24705ULL, 0xF92126544153552EULL, 0x99777764C4DA8661ULL, 0xBCE1B2CA2FE4A743ULL, 
            0xC6A254F57F232BFFULL, 0x5732BCE3BABB89ADULL, 0x00F9A6D391CF57FDULL, 0x41068FC3A0E9760EULL, 
            0x7830243801BB0311ULL, 0xD80AAE347C7E469FULL, 0xC538A652A61D5DC6ULL, 0x2A8A1C4B015F1787ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseEConstants = {
    0x10E0927E3CB38469ULL,
    0x8A220F9AE4AC818EULL,
    0x5C97E898E652028EULL,
    0x10E0927E3CB38469ULL,
    0x8A220F9AE4AC818EULL,
    0x5C97E898E652028EULL,
    0x9ECA56733B3E396EULL,
    0x5B8CC8C28E5619DEULL,
    0x7A,
    0x99,
    0x21,
    0xC3,
    0x46,
    0x81,
    0x2F,
    0x48
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseFSalts = {
    {
        {
            0xDA01053B96A227F7ULL, 0xC90B563D444B6AE7ULL, 0x5AB591C87C30DBE5ULL, 0xFCD75F994520515EULL, 
            0x0D1E5C3066A7E9D7ULL, 0xE2410CE67F1D94D4ULL, 0x16965345E8CBE5C6ULL, 0xDA46838EDCC73E15ULL, 
            0x3813B8F12E7815CCULL, 0xBED76ABA2C76E7A1ULL, 0x884AD4E905D883B3ULL, 0x66F9D11F5714296BULL, 
            0x9336075826E65A29ULL, 0x3836204EE87D0B68ULL, 0xA2DC9E407A6F69FEULL, 0xBD9DA9145ADC9207ULL, 
            0xFEAC5491C9129157ULL, 0x287EEF749E19DB29ULL, 0x3EB42DA69D2C6BDEULL, 0x51884706D431712BULL, 
            0x92793C3E6ADD2E5EULL, 0xE0AB5B334C496237ULL, 0xC0282802769E825DULL, 0x94102994F8FC3D34ULL, 
            0x99F943288A6E03C4ULL, 0xF42805A938D6D677ULL, 0x5AEBAAF16C666683ULL, 0x637E17C1A82FE046ULL, 
            0x7053BD12BDB1D5D3ULL, 0xC3F7D1DA40D4992DULL, 0x2D4E095ACC75D35BULL, 0xB4061EE3E4598918ULL
        },
        {
            0x248CACCC440D05CDULL, 0xDC42D505D85132FEULL, 0xF0F6D732827B09C6ULL, 0xB66CFD1F8C75F33CULL, 
            0xE425C05C78980B32ULL, 0x5589D8C70F2DDFB4ULL, 0x1AF982FFA4D61F2BULL, 0xAEBE71535CB016CAULL, 
            0x42B791418B6C3DA0ULL, 0x61926C35A8C84E23ULL, 0xCB7EA130F45912F8ULL, 0x5BD767CB828B4ADBULL, 
            0xC0A4ED03BE8B926CULL, 0xC6A003CF26E859C4ULL, 0x35945183781B2B8CULL, 0x7D991D2734B03692ULL, 
            0xBD4D195C08C88313ULL, 0x37A0C9EEB3BFA107ULL, 0x8267ABFB2F2430DAULL, 0x9C2136BEC36205EFULL, 
            0xAB2D8CA889F664E5ULL, 0x70E970AD0C916819ULL, 0x240A42B36165CA2BULL, 0x699CF7E1B9C999F8ULL, 
            0x2E7C169C5D22BEF5ULL, 0xE11158CD3B1657CCULL, 0x81F74E82D9918B0BULL, 0x35285147CAE0EF92ULL, 
            0xAF35EBCD94B5FFBFULL, 0xE32C27B71079E1B0ULL, 0x84B98D3B2959135CULL, 0x6002B90EC691BEDAULL
        },
        {
            0x61EAB7492A6D1E73ULL, 0x5C3B6FDE15C14914ULL, 0x0F8D96D4B651BE13ULL, 0xA8865AE6C9DC4EE9ULL, 
            0xD477B1B030795984ULL, 0x8323E36EA1388C77ULL, 0x1FB523867238F6FAULL, 0x9F9A1DC01ED8590FULL, 
            0xD19F2AAF3CDBE642ULL, 0x6E793CEF3215FFE4ULL, 0x065D9960476CBACAULL, 0xED441C403AE7AEEEULL, 
            0x2425E74F7A2D0634ULL, 0xE51481AB60B52C24ULL, 0x3E1300EB58AC9F04ULL, 0xC3E0D2A6DBC0B324ULL, 
            0x979F8A9E99D58F26ULL, 0xAE0FBB6A9A9ED47EULL, 0x026520BEA225D690ULL, 0xF69B0F7B4BD9066EULL, 
            0xBE0FAEC40801C2A9ULL, 0xEEDAA5E094326D87ULL, 0x378397969FAFB18EULL, 0x2C57C54956E91540ULL, 
            0xDC98C81AAECD3B3AULL, 0x263207B0E9A9A50DULL, 0x6AF96CDD061D2AEAULL, 0xD92AC4123B11FFE8ULL, 
            0x56AB908E69ED9839ULL, 0x9D2BA5E15EA0AA94ULL, 0x293CEE8FA2DFD540ULL, 0x4E9861C15960B5E3ULL
        },
        {
            0xFD04560A31140713ULL, 0xED41AEDE6C1AB906ULL, 0xDC157A59B1FB898EULL, 0xE02620E1328CE479ULL, 
            0x1FAE0A20095A1541ULL, 0x39DA251CCED2CBA3ULL, 0xC6702BAB9CF504AFULL, 0x5DF777FF6651460AULL, 
            0x5D8A8F4E67122B37ULL, 0x92E60E4B45F7DE7AULL, 0x9B9761F9E1A8266DULL, 0x31118008263F38C6ULL, 
            0x9E20D91E15DD3505ULL, 0x940C000D14353069ULL, 0xF99CC22652F1BE97ULL, 0x7BF0C06F6664E80CULL, 
            0x39AF84431172BF08ULL, 0x81B82CE5B27314D6ULL, 0x141519FDD396BC26ULL, 0xFCC5CE94AA5C1C47ULL, 
            0x8ECFCC8E7475A825ULL, 0x81CCF1E8B76A4C81ULL, 0x284C64CE8B03FC80ULL, 0xC4960AD94FA23B95ULL, 
            0xE0BCFD303F0CC65EULL, 0xB622D3E0E0E0F1F5ULL, 0x7C0B3043809B97B1ULL, 0x929354684D66D611ULL, 
            0x65A5AEE87C65ADA5ULL, 0x76C11CDA9BDD1971ULL, 0x50C2355A6F5A43AFULL, 0x818F7C9733DA1EF7ULL
        },
        {
            0xE2520EB603C92C30ULL, 0xBD7D3EC3D2E6162DULL, 0x5BADB1703DD1F426ULL, 0x2F06C40605189B98ULL, 
            0xA24E195782017E98ULL, 0xB4B775D8DB5324E8ULL, 0x7F8BE63E3C9EDB14ULL, 0x9F3A760CD987FDB0ULL, 
            0xC50A24FE1A84BEC7ULL, 0x5E93CBFEC712B2D7ULL, 0x2D4FF685DAB10A1AULL, 0x4279FE71B533DBF0ULL, 
            0xE683D98157C3649CULL, 0x532B28C71CB78CF8ULL, 0xC090056DFFEF1E55ULL, 0xAF6D6F64C70CB483ULL, 
            0x6DC84A0CCC6508E2ULL, 0x3C14DFE5752896FBULL, 0xA63A570D85AF5D20ULL, 0x5FEE1DDAA25AFD59ULL, 
            0xE83E7836A709A691ULL, 0x1BAE72925B22692CULL, 0xDE5073D6E6CCA38FULL, 0xF680D996D081C058ULL, 
            0xFB62199A09DCF48DULL, 0x70535F44E1D589E4ULL, 0xEFCE7A8C50168DB3ULL, 0x5BD7458D41271421ULL, 
            0xEC16676E074DBAB7ULL, 0x603A4AA13368D5E8ULL, 0xCC7B19CE6700F5CFULL, 0x075CAAFC3CB5C4E7ULL
        },
        {
            0x0CFF49D5C51160AFULL, 0x78579D2ABC105DDAULL, 0x7113109FFE84EFA6ULL, 0xB81CD3050199ADD7ULL, 
            0xE20E64C3ED9F00B0ULL, 0x61D02316D046E355ULL, 0xD2583F6E67D55CD0ULL, 0x6AA88BC1BFBE9724ULL, 
            0x1D61A005C59EEA47ULL, 0xA27FDF9D48F672D0ULL, 0x30402ABC8A1D6E0FULL, 0xC9D913EE09FF1292ULL, 
            0x285C3FFF1BBA58E8ULL, 0x04604DDE376C8B2BULL, 0xE51A461606A23408ULL, 0x924CD6DEE5033CB3ULL, 
            0x9FE12588204592F7ULL, 0xE5302CC840629553ULL, 0xE776CE6EECD9EE78ULL, 0x7C73835E7E45F6F8ULL, 
            0x8498E771EC1A78A0ULL, 0x424BC76BA3874DD8ULL, 0x0DC1D48D4DB2743EULL, 0x44D2D8E5AA71B9FCULL, 
            0x385513C74A5F1AF8ULL, 0xDD086A78053DF38FULL, 0x50F4B2C408F1A9C0ULL, 0xAF553FB00F19C5B9ULL, 
            0x423E61316169DAB1ULL, 0xBF8A6DFB8B551C51ULL, 0x1471626FB7B9CFD6ULL, 0x219A1EE3C8F9824BULL
        }
    },
    {
        {
            0x23DA1D63C511A834ULL, 0xEB68CD914215E7F1ULL, 0xCF311F459686EF55ULL, 0xE61DB3C2CCF5FD37ULL, 
            0x6983C6C08FC850BEULL, 0xF702C311389B7005ULL, 0x9338F3D8FCD526F1ULL, 0xD31DC291B5D1F6BBULL, 
            0x5133DC94F430A6D3ULL, 0xC3C89F841334DC3FULL, 0x0F0CC8524AAC7E01ULL, 0x6CD7BA39BF46AE1FULL, 
            0xE05F51127DFF31E0ULL, 0xB51E239EAF6A9E6EULL, 0x57FA5AC4D441CF94ULL, 0xDA06442A4E523989ULL, 
            0x4BFC2AA31A018352ULL, 0x63DADD95A50E7774ULL, 0x5285E3BD314093BBULL, 0xF8107517F1B5659AULL, 
            0x1609E52441F6426BULL, 0xE73BF40FE71769B0ULL, 0x944F95DE652DD9ECULL, 0x6DA8965A7C709487ULL, 
            0xA2E2AD45E9FA1FB5ULL, 0x761F6BEEC36935E8ULL, 0x0E20EB97ED79AC4BULL, 0x4B8EE2EDA68BD65FULL, 
            0x7C387A4CD153FFB0ULL, 0x375D11FF3D870191ULL, 0xCEF449640AC4B0C0ULL, 0x9D0E14106E3353A1ULL
        },
        {
            0x8D205CE97296815DULL, 0xA721E8530751F953ULL, 0xA4E598C83BECAA55ULL, 0x96CF89E9B0A3DF8CULL, 
            0x5960CF46BA1B69E6ULL, 0x4F5D2DBA8E4C488EULL, 0x7729B3DD08CC6859ULL, 0x394CA3231BD0D7C1ULL, 
            0xD078786270BFC14FULL, 0xDB3FF3836A2EA828ULL, 0xE691276EFA98C868ULL, 0x791C88D88188BEFBULL, 
            0x42A14C1917E1A467ULL, 0xEDF2BF5CA3B85AA2ULL, 0x0F592DA3959C14BAULL, 0xED035743AE55C6B8ULL, 
            0x336C177B34D52719ULL, 0x7A387CDF0988F011ULL, 0x6A2AD413691CF6B9ULL, 0x3FE7FD681C573F42ULL, 
            0x2A86437014F45D4CULL, 0x741F651A47E67EFAULL, 0x33B64595E1B0F1B1ULL, 0xB5DF9036518D8E1FULL, 
            0x038180C3B635F01CULL, 0xDC29CAA81ECC9D90ULL, 0x5E3955FB2696EA1AULL, 0x286DE7B5AFAF9AC4ULL, 
            0xC238F23C85CAA5A2ULL, 0x23A1BD8D25D5B939ULL, 0xF21847D476A26466ULL, 0xC814E0183A26D6F5ULL
        },
        {
            0x3AD1655AEC7B765FULL, 0xA992D3FD8EBDEA0FULL, 0xEAAE74FC78D47187ULL, 0xECF76BEA2844D1E1ULL, 
            0x461AA03DDED69FAAULL, 0x721FFC2E8DD8E78BULL, 0x079798B2C88EB242ULL, 0x29CB3DEFB535C89EULL, 
            0x99499630F57AE217ULL, 0x31CA35BF8EB03A1CULL, 0x7E3FC319833D4BE0ULL, 0x225F1FE8F4D0FBA3ULL, 
            0x6DC03006E7F2B9F5ULL, 0xECED62F8A4416A50ULL, 0x80EB2CAE450603E4ULL, 0x35B5DA33979E005DULL, 
            0x8DB518F0F873A355ULL, 0x6E4C5E597C4D1EC8ULL, 0xD52DE0EE63467C68ULL, 0x7A3156DD46619FF8ULL, 
            0xDB27925E5760D940ULL, 0x7AFAE2AA598E7488ULL, 0x91932D43C982A478ULL, 0x31E1BCF874462012ULL, 
            0x26F701CABD403DFAULL, 0xF2A968B0D39EE881ULL, 0x635D6ADD833C7D0BULL, 0x2A053C9AB710E61DULL, 
            0xBCF58FD787EB4B54ULL, 0xC5D7D06EAE8B1157ULL, 0x7017778ED91018B9ULL, 0x0FE90EFEF70724DBULL
        },
        {
            0x05039FA066DE8042ULL, 0xB5C478C628741B94ULL, 0x5FD3B27E800905AAULL, 0xB196C2597D875502ULL, 
            0x1702C6F151DBCEA5ULL, 0xF86ADC9460C654D5ULL, 0xE52469D67D96E952ULL, 0x99DF593D9B12B54DULL, 
            0x6D7D70D64401CDDAULL, 0x62774E181F180CB9ULL, 0x59E0D34D5A7E678EULL, 0xBBBBFC8492933220ULL, 
            0xAB0A693E9C134AF9ULL, 0xAAC5DB2C6AC32497ULL, 0xBA0D09026753C4EDULL, 0x33D345A9BBD1D828ULL, 
            0xFD50BE5E6B367C0FULL, 0x6ABA83A9A90CFE16ULL, 0x299EF0BBD29D9D42ULL, 0xB0FF824266B89A07ULL, 
            0x5A8709841BA420E5ULL, 0x4CD1BA500471BA7DULL, 0x98D757A5A37EBAA2ULL, 0x6A9DAF0F471C22EFULL, 
            0x42640207F50EBE38ULL, 0x4273B991A0816940ULL, 0x58D5DAC6C2FE91B9ULL, 0xBB257BA1E5FF65F1ULL, 
            0xFA04AAE90A16B50BULL, 0xBF9D8ED91F03229CULL, 0xA5D2F8E09E80263BULL, 0x89D836BEC2A148CFULL
        },
        {
            0x342D4F9A508154FCULL, 0xF415F4704628BD57ULL, 0xBD9F47562750D59FULL, 0xA8C235932755C4F8ULL, 
            0xD1EF9AD9EFB2E9ABULL, 0xF53A387C5F44DC5EULL, 0x4F35BC7F73EB835BULL, 0xC7FF804E92F695FCULL, 
            0x33F83E79E7C37788ULL, 0x6030419D8B50595FULL, 0x2D7EB08028C271BDULL, 0xDF2F78BB5B855D73ULL, 
            0x2523C4EEFC366BB5ULL, 0x1848117A0409D6C2ULL, 0xD1D83D2C8938480AULL, 0x2D484A86E559114DULL, 
            0x0BDC10E9BF433C5FULL, 0xFDC89DFD239C1014ULL, 0x65E112785C441FCAULL, 0xF73892B92ED7ECACULL, 
            0x552E88849AFE9499ULL, 0x99365D5C98426088ULL, 0x4E83FB6BA5ECD918ULL, 0x021991928C7E461EULL, 
            0x13B97FA4344CD9CAULL, 0x9EDAE2B730A8C24BULL, 0x53150B3F919D9B36ULL, 0x6422F46C01194DBBULL, 
            0x7F7C76B01DF21987ULL, 0x3FA288FF940BB73DULL, 0x367EAEAD53379EA7ULL, 0x1BC7E7FE4228F49BULL
        },
        {
            0xA5678AD5065DDD56ULL, 0x1A0D03410D233A77ULL, 0xABBD530577A1389EULL, 0x8F414A3281968DE7ULL, 
            0xEAAC25F84BC4929EULL, 0xD542B16098B4852AULL, 0x9FEE8396143CC217ULL, 0x5602416F82B4BEEEULL, 
            0x30A6EE3101B0DCDBULL, 0x2AAF64A3FC548CF6ULL, 0xE7105C4B371373F3ULL, 0x6E3C3A0F2137F07EULL, 
            0x42F2C695FABD73D8ULL, 0xEDD0B7C678AA3795ULL, 0xE235B4E4E38985CCULL, 0xA16F58BE61F3D97BULL, 
            0xCA8374DDB159D5A6ULL, 0x036DC6439D98ECC0ULL, 0x532FD2BC6D453FE0ULL, 0x413F42D05E26CA80ULL, 
            0xC20C18B2A7701766ULL, 0x60C314042EBF903CULL, 0xD2A13A08852589A1ULL, 0x3314D8949214AC49ULL, 
            0xA88383C5C67D8272ULL, 0x15562C613D063624ULL, 0x99C95E3765DFEBC4ULL, 0x9ABF02D2A2E845EDULL, 
            0xBAE2360C7F96E01BULL, 0x2CE223E7B9E1365EULL, 0xAA2D5C5066A8308BULL, 0x65FC97A90205BF42ULL
        }
    },
    {
        {
            0x2D7095447D81572AULL, 0x973640677BD84179ULL, 0x6FCD0F1C8167EA83ULL, 0x1C8FE140D0365E53ULL, 
            0xA7B448FFE9B57338ULL, 0xD584EB1F65EDFBECULL, 0x1818FDCD1FA595DBULL, 0x6D704C604ADF1526ULL, 
            0xFD65BE2214705132ULL, 0x5A30E6F1751A1A09ULL, 0xED1536452A91FA18ULL, 0x88DD03567CD7E7CBULL, 
            0xDE38E0DA6A1C83C1ULL, 0xC6F639EC0348683BULL, 0xE7A097259578E31FULL, 0x6D6736CBB4DB2B5BULL, 
            0x83B2BA6583F5D0B9ULL, 0x6D765B4E957A2DA5ULL, 0x1C688091AECBB492ULL, 0xFCCB6DA94196ECAEULL, 
            0x0CB1840441C46FD2ULL, 0xB5443DCFEB2B2CA8ULL, 0x02C17DBC00C24D20ULL, 0x73EDF6F6593ED430ULL, 
            0xD5CA146213DC6B02ULL, 0xFCDC0C0268A58C39ULL, 0x4F22042E637D95E4ULL, 0x2F448F7BC0900BA0ULL, 
            0xE4DE27CF56F76D13ULL, 0x1C333BD3F177C836ULL, 0x7F71697A2475372DULL, 0x727BAE61F8808606ULL
        },
        {
            0x04E16B4282ECD680ULL, 0x607D050F29C26FBAULL, 0x9C2553CF0B2D6120ULL, 0x2E64302884F7D68DULL, 
            0x1212E73F89A48F8BULL, 0x66FF3D3D5C3B0A97ULL, 0x3BA23F0E67CC34C7ULL, 0xB7706106B6285026ULL, 
            0x46FB2FA5EC83933EULL, 0x28BFC1AF1186D766ULL, 0x0466A43D1983E438ULL, 0x77D74029BF91276CULL, 
            0xFD2194FAA1F3B0B8ULL, 0x2BBAEB300D9064A9ULL, 0x1C39057969FBBF35ULL, 0x20706B09120A0BBCULL, 
            0x4E5AB914ABDD45FAULL, 0x44D679219641ED78ULL, 0xD7A2090892473555ULL, 0x1D984330FA725FFAULL, 
            0x115F49EDCF19AA3FULL, 0x4ACCB1A0621CE2E9ULL, 0xBD026440DD52D6EEULL, 0x6E8292AC3EDD34A3ULL, 
            0x9B166215759C4CF2ULL, 0x18C4CFD1D8B31345ULL, 0x3395EFFFBEB400D4ULL, 0xA195F707401D113EULL, 
            0x9411E8779E0EFE01ULL, 0x8CC19D729CEEDC9EULL, 0x28ECE4A50445BC8BULL, 0x330D0CE76E641BFCULL
        },
        {
            0x1E41B1DA2BCA88A1ULL, 0x5BA3E8C5B303E793ULL, 0xA91F6B7270FBF663ULL, 0x4E8B7E1BACAE01B7ULL, 
            0xF02C289B06753A7AULL, 0x5D83FA78A77271BAULL, 0x2A2FCA981F588094ULL, 0x47E97A13BFC4C056ULL, 
            0x5C864605CAE4BF87ULL, 0x71B984057C719FDEULL, 0x7794ACD30EBD868BULL, 0x63D21D04B16B746FULL, 
            0xEB1EE8EEC64E9CEEULL, 0x2244A0FA296A65B9ULL, 0x6CDA84B192EF5DCDULL, 0x96FF4B3374DEADFAULL, 
            0x8AD4802412846D0CULL, 0x665D6C35261B7A4EULL, 0x8C027B6462A3166AULL, 0x35AFB6FA33F88B99ULL, 
            0xF7AEC1D68633999EULL, 0xDA7BACFAB98C0F24ULL, 0x29ED77E70BBA9F9BULL, 0x68DB2A254E8D01D6ULL, 
            0x242A4E53BD1FA035ULL, 0x9D2A121C28500F2AULL, 0xE25C34CEC3E2196BULL, 0x61AAC529818CD0BFULL, 
            0x8F03FC18827B4DFFULL, 0xCD8E46A4B7DAF927ULL, 0x9A6D51FE83AC0920ULL, 0x824B8B5D43CE1943ULL
        },
        {
            0xCB834DE053C62FCDULL, 0x8ECA6747072CF0EEULL, 0x928F786E59FBC046ULL, 0x2484E2DF5D9A1EDBULL, 
            0xBF9CA8893EFBA1C8ULL, 0x454F460C83729F80ULL, 0xA834196084BD49C0ULL, 0xC6315708A26B45FDULL, 
            0xAD47D49782904A9BULL, 0x0D5CC32809231B58ULL, 0x8C662B91D9A36547ULL, 0x1E069A9DD6B96772ULL, 
            0xEE2A6A124B02D49EULL, 0x9FB1FC6160166A62ULL, 0x27CDE1552517DB84ULL, 0x7C7F3A724783845AULL, 
            0xD33070B7B3E8488EULL, 0x3A74813EAFC3DB7AULL, 0x4948E3E90759FCDFULL, 0xA8DD67D2B25F0F26ULL, 
            0xCA6816A5C4958866ULL, 0x256433EE0393EAAAULL, 0xA5AB6FB92F2CC173ULL, 0xEB3CF6D2AC42EAAEULL, 
            0x35880ABEA731E737ULL, 0xF1612986E8A9E79CULL, 0x2BB5B7C0A27A6E8BULL, 0x63C8CA545C1DBDDFULL, 
            0x72150F43B9698B16ULL, 0x97EADB0681C8AB48ULL, 0xDEF14E6ED5B416FAULL, 0xAF8F8CDEEEA3D64FULL
        },
        {
            0x2AAEB44AC4DF75E5ULL, 0x89F833DC9D7A3AE1ULL, 0x9ECECD2ADE99209EULL, 0xBDDFE1BF9CAF37D5ULL, 
            0x138C2D16E2F230D8ULL, 0x53F0ECD9F07655BFULL, 0xCA45ACC163F3BC33ULL, 0xAC4BBBC359EBE34AULL, 
            0xB1326D456D8A6720ULL, 0xD143645801D244F7ULL, 0xE3472D18C00B4249ULL, 0x0CBB248A6CCD3E63ULL, 
            0x13A970D2CC9CE793ULL, 0x904953D1C3FE1C34ULL, 0x399C724ABCB127CDULL, 0x4C184FC9974A456FULL, 
            0x216FA489E98B16BCULL, 0x466CC5DFB5450E93ULL, 0x67F1801A1582122FULL, 0x33BEC94150D8831CULL, 
            0x848AB29BD00F6E59ULL, 0x68DBF9BF563462FFULL, 0x45B826E382744DFDULL, 0x0530C4F5EAF96614ULL, 
            0x319F16576B400C81ULL, 0x0C902DCA0C3788A4ULL, 0x53BBC9D1E96A5541ULL, 0x09A5278306C2E9C0ULL, 
            0xB5EF61D0D5DFBFF7ULL, 0x73D7D4BCE0223B47ULL, 0xC8F5C08348181749ULL, 0x9EEBA2CBA45710EBULL
        },
        {
            0xFD969834DEA4B829ULL, 0x3A7ED005D31F4E69ULL, 0x81085788BFB039ACULL, 0xB6B02F1C3012CF46ULL, 
            0xD248374B14471007ULL, 0x2FB85812792FA4F2ULL, 0x6CE61A6AAB4E48D7ULL, 0xEFD7E865CFD727A4ULL, 
            0xE5ABE5E9230AF9A9ULL, 0x81290DBF923A456AULL, 0xF219B201D383BD7EULL, 0x5D30E0398A8FB2FAULL, 
            0x79E0639DAABE97D8ULL, 0x29135316C07312DFULL, 0xAC927C182ABEB6DAULL, 0xF7347D3BE5824BFFULL, 
            0xEDA3A8C827C08990ULL, 0xC069E58090EA93B6ULL, 0x31F8E2F6B25F3F45ULL, 0x49273B0CC09825FBULL, 
            0x46FC6AE357D3A4B0ULL, 0x17462B2835F24242ULL, 0x17492F839971C167ULL, 0x29AB47245A29DAA7ULL, 
            0x705A95534EB215E7ULL, 0x91E5D7C92075AAA5ULL, 0x3DFAABD583C46C4EULL, 0xB02732AAEFE4838EULL, 
            0x6AF4D4AB0E1D990FULL, 0xF2B1DD8DA662876BULL, 0xB111562D1C88054EULL, 0x3B952BB17D355906ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseFConstants = {
    0x1CA71C81BA44C94FULL,
    0xBF634DEBFE798825ULL,
    0x3B3CF273CCDA094CULL,
    0x1CA71C81BA44C94FULL,
    0xBF634DEBFE798825ULL,
    0x3B3CF273CCDA094CULL,
    0x9815E9E4C37C9CEBULL,
    0xC9C9E464DA595EB8ULL,
    0xAF,
    0x11,
    0x41,
    0xBB,
    0x31,
    0x92,
    0xA5,
    0x6C
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseGSalts = {
    {
        {
            0x10546695068AEB7EULL, 0x59EB0140BC2A4FE1ULL, 0x2A2A3FB21D21CDE5ULL, 0xCA8A7B90327591C3ULL, 
            0xE7AB0E1F54388481ULL, 0x2AD45DA4C7613647ULL, 0x2DC049140DA033A3ULL, 0x00A4BA0C1B907A86ULL, 
            0x98D4B63C7EBB48A5ULL, 0x3B2F158225D1024FULL, 0x1FD46ADBE3735CAEULL, 0x6286B0D1E169B89FULL, 
            0x0384A81BAF495C90ULL, 0x357DEBF5C74C89E6ULL, 0xD921A982D76A805EULL, 0xE0EDE3B065AAD13FULL, 
            0x5CE6FAE468D7D46BULL, 0xB03BA3853A587DE5ULL, 0x89CFD87FEE21628CULL, 0x05104D9FB85EA829ULL, 
            0x3585F9C65C342692ULL, 0x46597A76D68751E0ULL, 0x9CD81B6D93626DADULL, 0xB8C2EB8B5E2F8F45ULL, 
            0x41BDE96EED20992FULL, 0x7037958B2E6CE0C3ULL, 0xF11F050B26B82D92ULL, 0x0E86C1C6B3883CA4ULL, 
            0xB4B188300B5430CAULL, 0xB18C6777E8AA8D1BULL, 0x1BB2F2117D71D1EFULL, 0x97888314B43E46D4ULL
        },
        {
            0x5A9FD08604DD2E85ULL, 0xDC1A7995CE91CB0BULL, 0x5CFA55602C57E1ADULL, 0x5FF670958AF9A413ULL, 
            0x9905C8F670BCB428ULL, 0xE0DFF6A959FA91A4ULL, 0xC1343D192DD46C39ULL, 0xC7A89DFE82403516ULL, 
            0x6376C7909C8BBB0EULL, 0xC7ED1747A4FB7755ULL, 0xABB172C8927B9118ULL, 0xD89844C0AFCB202CULL, 
            0x40713B5E2430BAA3ULL, 0xFDE43723995558BBULL, 0x9BFB77A8184E1694ULL, 0x44AE92B09F90352CULL, 
            0x4E7568458678DE1AULL, 0xB50A81D4BB490A5DULL, 0xE4B45EF7510426C9ULL, 0xC48CF9B1D6750873ULL, 
            0xAABEFA482D652757ULL, 0x0AAD578CDC139AE8ULL, 0xF6891D157C6A1C55ULL, 0x35E34D9A965F9134ULL, 
            0x2228A21E90E9E009ULL, 0x5CEA557F0F227B7AULL, 0x05276034390B2867ULL, 0xA8E0FF9B7B5CCCC9ULL, 
            0x211E2E622A9E8078ULL, 0xA3F65317A1208BD9ULL, 0x7C36592757F4F64FULL, 0x13FBC9FCA5285831ULL
        },
        {
            0xE991FF6705EC92DEULL, 0xC81CE40D2B4B2DF0ULL, 0x985D0195A64E2564ULL, 0x94A1BDCDCF60AEB9ULL, 
            0x8116EAA5CF5C4045ULL, 0xAABB863F9FAD86FCULL, 0xF7E4F7DDCE432C28ULL, 0x48A84AF27D1FFFECULL, 
            0x8FA421AF1D3CB452ULL, 0x2A638EFA976E76F5ULL, 0xFF757EC4126F4214ULL, 0x7B3FC2F2E469373CULL, 
            0xD1817223B3913897ULL, 0x723C59DDE3591123ULL, 0x63DC82D138F3AB97ULL, 0xE1B2AE092FD22EA9ULL, 
            0x52D089F14FC99352ULL, 0xBFA590463A9D2776ULL, 0x5C84A1A122293DEBULL, 0xC140DC142E242E70ULL, 
            0x5168F851BFD9CCF6ULL, 0x1D62CC8A10FF5DE7ULL, 0x7F739534044A7016ULL, 0xAA0D46C8C8D8029BULL, 
            0x30DB58E315448CA3ULL, 0x29B6F5788FB4E5F3ULL, 0x17DB6A72BA96A75FULL, 0xFF6233041F40B260ULL, 
            0x731D19D4CFBBE983ULL, 0x09D1067BE112909EULL, 0xE52D145DC13B1470ULL, 0x211B1636325731F1ULL
        },
        {
            0x76C7FD81BBC1BE7AULL, 0x0D10DBD23AC9ADDCULL, 0x46CA94BCEF0653D3ULL, 0xDBE6B228407C7885ULL, 
            0x22AA9D2CD87ADD1CULL, 0x50E1FC7BB5F7064AULL, 0x36CB4E2BD020ACF1ULL, 0xCF26F48C3F17DA1CULL, 
            0xA593B37A2B4CE3C5ULL, 0x3309E2D61370BD77ULL, 0x3D3255D966152D1EULL, 0x078D5EA3B6372304ULL, 
            0x2E860CC1B01A9F0EULL, 0xAEA77E77B244710AULL, 0x496A008A643FA31AULL, 0x9958AA5518CC5234ULL, 
            0x00148D05C3D06150ULL, 0xC4B49B8523C2436FULL, 0x1FC6D435E3E69172ULL, 0x1D220E8F1FB778A5ULL, 
            0xD5292DD585A4A65BULL, 0x94B657C916014856ULL, 0xB41BD04DF1BC9861ULL, 0x0CB7535E3220219DULL, 
            0xA5CE286CBD07E330ULL, 0x97DF28FD603E5634ULL, 0x26551724FE6B1056ULL, 0x2D0E77BA9403BFBBULL, 
            0xB2AF94F8B422B7BDULL, 0xE4CAAD5A5276C7E5ULL, 0x7E9A1E62F0CB3F2AULL, 0xC58DB99BA0AD3E83ULL
        },
        {
            0xE37C58D410957BCAULL, 0xEACA9CDBD446412AULL, 0x5EBEAB583E94918EULL, 0xE1FC91E72BDFFDA5ULL, 
            0xE84421F1DB1948CAULL, 0x904BF93EA644868EULL, 0xE66F9087EA2681BBULL, 0x44EF1C6453F709D0ULL, 
            0x8E2D0F1CC78B4616ULL, 0xDFE08C94F9472840ULL, 0xE463E5AC30DFD2B2ULL, 0x08FA6D6E8A3E6140ULL, 
            0x1F5CFEFCFAD0151BULL, 0x03C06CE300A120F4ULL, 0xDC2B5702442824C3ULL, 0x206ECECAA310AD78ULL, 
            0x56EFEE569592A43DULL, 0xBB35165C2D7263D7ULL, 0x13C079329D8DBFBEULL, 0xF24D1A6668EEDECBULL, 
            0x4BA14F3FE21EE3BFULL, 0xB1D46A438A93C1E1ULL, 0x9A439C2CD2006209ULL, 0x87B598398507CADDULL, 
            0x429060F21C5D708CULL, 0xA56A9D2ADB2D1EE2ULL, 0x6D61AF9E9359B8D3ULL, 0x1C5CEB71CBD0331FULL, 
            0x70C2C299FB5D1BC8ULL, 0xFB0D72961897048DULL, 0x3CB615320EAC7917ULL, 0xF19A024C594BBEA1ULL
        },
        {
            0x19E4F0CBF339CCA2ULL, 0x728F1262F96ABA7AULL, 0x7037BF9CFDAE52BAULL, 0x37F03E992A9D464BULL, 
            0xDE4DA6CF3E037F34ULL, 0x89E679CC2401F0E0ULL, 0x6962C5724BB58BD2ULL, 0x694F953A9670FD78ULL, 
            0xE4A96CE0F4D0F7ABULL, 0x48AEC3CCF4758F57ULL, 0x32B7149F97144402ULL, 0x988CE9916826D8E2ULL, 
            0x81B9D57DB8953C9DULL, 0xFB1899BBC1D8C9A2ULL, 0x6EDD6F750DD591EEULL, 0x85016428DFE46DE2ULL, 
            0x6E4B141CC8352281ULL, 0x7B15F86ED990D3C9ULL, 0x208403D33B237952ULL, 0xCE49B1E36FC98499ULL, 
            0x8BCC6439169FFDB2ULL, 0xCAA78C8F4CACA8AAULL, 0x33C08855EC275E16ULL, 0xD9B30F259D4E2075ULL, 
            0x22FF3ACB6A0F8B44ULL, 0x35CBE787099EBC55ULL, 0xA7B865C6EAFD7A68ULL, 0xCCFBB76D874B1BF2ULL, 
            0x2C07BE9A0230DCD7ULL, 0x715295D007D51135ULL, 0x8E89E28D3DECE3B1ULL, 0xC5A92D30EBCB4E75ULL
        }
    },
    {
        {
            0xC937AF2210431F31ULL, 0x38FDE5E60E04561BULL, 0x070E63D7C01C630BULL, 0x50AB5A99A01B21B5ULL, 
            0x8B34A423AF4F176EULL, 0xEF6422F5C98C050EULL, 0x23A294625214F316ULL, 0xEC9EF9DD710E182BULL, 
            0x59037D456CBD85A2ULL, 0xDD4F45C5CB0FD7EEULL, 0x29D89C0096904A09ULL, 0x84BACE4C5A88CC7AULL, 
            0xD65BEA3C81C8EFE2ULL, 0xA5E678403AB5486CULL, 0x5C450160745BB0EFULL, 0x92DCFE56DCDA61D8ULL, 
            0x06713E7F127388A4ULL, 0x899CBF67EF0E5DB4ULL, 0xD4AF9A9EDC833018ULL, 0x1150C9443B4BA689ULL, 
            0xF5DFDE90DD34253FULL, 0x81B401EAF000E117ULL, 0x70D4A8E749014522ULL, 0x867552E48E35DCF9ULL, 
            0x1D23F037A097E20FULL, 0x583CC63BA1A26FACULL, 0x7315C7B117202B4CULL, 0x5001E5DC2499A4B4ULL, 
            0xF6E670A12BB81947ULL, 0xBC093A0B28A2DE6AULL, 0xAACE872E4095FCCDULL, 0xA9FC191076059BCDULL
        },
        {
            0x210848B63917D025ULL, 0x163FF35C9F82B642ULL, 0x4BA98CA31C8D1D0EULL, 0x529869D7CC691BE4ULL, 
            0x695E5E3734132112ULL, 0x06E30210A9D67227ULL, 0x25467CC0E3A7D136ULL, 0x7B1EE6D2681B1A2AULL, 
            0xFF5A0DFE227FA4B1ULL, 0xBBAA01383C1B4EDFULL, 0x4F945A6CB41804E5ULL, 0xEBB5C288B8C22967ULL, 
            0x28B3638383DD4059ULL, 0xEBAAFA362DD71154ULL, 0x37BC81882B848181ULL, 0xF6F3C0D766C9B3F5ULL, 
            0xDA4CA9FEE38CD15DULL, 0x751279D7DE424EC5ULL, 0x9044DA173785061EULL, 0x61DB775D21916C66ULL, 
            0xC342E82FB2C4D918ULL, 0x2E09ABB7492EA91EULL, 0xBA4378FDF07EAB44ULL, 0xE2FFE2538F1FD50AULL, 
            0x7C4532DB0002B60EULL, 0x51FE62A8289577C7ULL, 0x744A3AE0EF310ACEULL, 0xD3177D7DD15B9B5EULL, 
            0x3268F60852DFB72DULL, 0xB30ED92B1A886CA4ULL, 0x0DC1767EDCBB71FCULL, 0x4DA00E9D01720314ULL
        },
        {
            0x627C9231AF32C6F0ULL, 0x1F722750CC17C91EULL, 0x039B62752C857DFAULL, 0x95308FB7F5B7A030ULL, 
            0x33B0E312873315E7ULL, 0x27076641CBCB0916ULL, 0xEDBA14ED12D90E30ULL, 0x45E4B90A6F18A0F6ULL, 
            0xEC94C416EF195757ULL, 0x5C74275A15A078CEULL, 0xE1433712345828D9ULL, 0x0847D5BDDBCF40B2ULL, 
            0x5D007E39A47BDC34ULL, 0xDF547CBE607C2EBEULL, 0x7F6931DC0F43534FULL, 0x056C1B635E5E2484ULL, 
            0x20CC661D99A75579ULL, 0xAE6B3CEE309B4EEDULL, 0xA9464240601BAEB9ULL, 0xA94D22D63348B1DFULL, 
            0xFBDCADF77CA1596FULL, 0x54904AE231C8A9D4ULL, 0xF4A149A7DAAB1DB5ULL, 0x5E4D85177D6B3879ULL, 
            0xAA5EFD74ABAC24D5ULL, 0xA3A4EDA7A508549BULL, 0xF1B23BF40089F440ULL, 0x032AD6183C312364ULL, 
            0x36AF36EE351E3ED8ULL, 0x0EAC64457929A0ECULL, 0x13351FB1E3B1BBA1ULL, 0x2864297FE89DE97EULL
        },
        {
            0x015B1B6E5383AF35ULL, 0x0E89D33E24709CF0ULL, 0x1ED076E7B166C4EAULL, 0x7E5B758EE05F4D58ULL, 
            0xBE4388765765C9B4ULL, 0x7CD7317C2F8B049EULL, 0x307BAB8CA27A50C6ULL, 0xAE75CAC8DBDA787BULL, 
            0x764F3131C9CCEEE1ULL, 0xFC4EA6B29B0850BDULL, 0xDF1E266D9041190DULL, 0x38FCCB9B46C4B306ULL, 
            0xAD37947F9A2D138DULL, 0x93ADDF6617DC0F82ULL, 0xAF21062E3893791EULL, 0x7DAC524750E133D2ULL, 
            0x1A5FB28DEC016719ULL, 0x47378F07B3331845ULL, 0xF554370219149C9FULL, 0x2BB4D99371C35163ULL, 
            0xD9EE5220CD1B1E33ULL, 0xB9E2CD6D6BD28207ULL, 0x53DD65731ED53084ULL, 0x04962F0DFC9F17C7ULL, 
            0xCE2DD71CEC41A7A9ULL, 0xEBCC18F1DCCCAAE2ULL, 0xC90250BD0B570D1FULL, 0x011808FAD8068625ULL, 
            0xB37A62220D8FEF44ULL, 0x8AE5C87841D1262EULL, 0x86B16BAD3B308EF8ULL, 0x07CB060E69317A7FULL
        },
        {
            0x3877DDBBC8EC3A28ULL, 0x00780F5C23626226ULL, 0xA9B52068D1D2F013ULL, 0xC682D8964E9795E9ULL, 
            0x7B28D616FC634A32ULL, 0x33FC80F1608221E2ULL, 0x51B835ED2E17B014ULL, 0x4A7D81D2FFCDE98CULL, 
            0xE70F03352EEA9FAEULL, 0x76DD15CD6CF6C17CULL, 0x2DFB24D4345854CCULL, 0x0FB1BA8D6BFAECDFULL, 
            0x354171B2D57D8C57ULL, 0x3CECA2F2C4FE8F82ULL, 0x1F38B4F1E961E962ULL, 0xE0BD23859B672F0EULL, 
            0x5432E5B365EAC493ULL, 0xD023F67B095F82C1ULL, 0xAAC12C0C6CA69AC9ULL, 0xF358658A9BD0A981ULL, 
            0xB074E85390FE3892ULL, 0xFF69EC8DE5708489ULL, 0xA2E2EEF985DF60F7ULL, 0x2FD740A6D88D2C18ULL, 
            0x3CF4C133B91FA80AULL, 0xBC6CFED7DD5AE4F9ULL, 0x3E20CBEC076F9911ULL, 0x5F209F02C75F23DEULL, 
            0x23350CFB7A03AD70ULL, 0x97CB97BBCD2AC371ULL, 0xD383F70921EAEBBCULL, 0xA9D7E6CE1B010982ULL
        },
        {
            0x7058732A18CF739BULL, 0x4EA6ECD600503E1CULL, 0xA86F9A11A85F584FULL, 0xEFB3B1C21C9FDCCDULL, 
            0xA80502B5526AEE1CULL, 0x53A477726436257EULL, 0x768FDED4B4FDDB9BULL, 0xFA08FFED033FA026ULL, 
            0x433917D2A42B4948ULL, 0xFAEB3509F9CC093DULL, 0x00B3FE8511893AFBULL, 0xDC3FB9084E65B6A3ULL, 
            0x7DC1145FCFF7B7C7ULL, 0xC33DACA34F81581AULL, 0xD502E10340343FA9ULL, 0xC852852BC551BCEAULL, 
            0x7389C3E4F4F46530ULL, 0x45183199A39AE0D4ULL, 0xCEC93586C36062B9ULL, 0x7F7F4E7CC5F4F42FULL, 
            0x7EACB999D1658BE3ULL, 0xD1C71F44ECB2E805ULL, 0xD906D266CD0F346CULL, 0xE39EF4CCB37B8D87ULL, 
            0x14266FB774690A3DULL, 0xC6E5B97E06C4F4C2ULL, 0x60B31016FB0848EAULL, 0xB5D97DA2B5BF6EDBULL, 
            0x4AFD770DCF823B21ULL, 0x643424210449A0CEULL, 0x1668F37A13FEFDF7ULL, 0xDD177CDD0B5824EAULL
        }
    },
    {
        {
            0x92F729ECDC64E361ULL, 0x23AA7FB89B026D7EULL, 0xE8120D83C1C8E51AULL, 0xFA87F64674EE8A08ULL, 
            0x708B42BBC9DB0F87ULL, 0x1E68BAEC322EBAB9ULL, 0xEF157637F913B1F9ULL, 0x6484A09721D039CAULL, 
            0x70BC6E247C00D990ULL, 0xAC61453C1B02DA45ULL, 0xD9CA09DB0D72D1CFULL, 0x7400CBBC331D50EDULL, 
            0xE2D6542728DC2F72ULL, 0x7B5943F05A5E0021ULL, 0xC910706B501C3AC6ULL, 0xEE5D5A91EBF7FD98ULL, 
            0xF476FF024F2C7B82ULL, 0x7ABA2121F525DFEFULL, 0x31B964BA7D22C70EULL, 0x46D89C43884AB2C6ULL, 
            0x7E730FAFE010419AULL, 0xB77B4A1A96985B66ULL, 0xD5299728D614924AULL, 0x0BCE461658204316ULL, 
            0x5388916004D7C98CULL, 0xD887684AE3E46A37ULL, 0x64FC2545BACD3A71ULL, 0x62DD9636BE1DDC59ULL, 
            0x46C5A641C714D7C4ULL, 0xFBC00B29081DDB87ULL, 0x1A3926651479CC11ULL, 0x99D8641EFB21549EULL
        },
        {
            0x6A3BFD80151F8B9BULL, 0x3942DC136CFF12F2ULL, 0xE30999EA9D9FC798ULL, 0xB29BD0EBF0DACB51ULL, 
            0x8C65D381BBAF2DAAULL, 0xA068877D933E6BEEULL, 0x9A9E8234AEAF32CAULL, 0x090787EDFD4BB746ULL, 
            0x82292E2E8446F171ULL, 0xEAD6D73EE02BE9F8ULL, 0x9887DECEF95E4353ULL, 0x6FC8DFF310E49B65ULL, 
            0xE9E2A4F85FE61297ULL, 0xB7A6FDC381D2117AULL, 0x0AA3DAE8B893BBFFULL, 0xF4C1CB44A79B51B0ULL, 
            0xBF3A21C7158762EDULL, 0x1FE80DC0F6A42484ULL, 0xF1C1DB2AAE9AFA8CULL, 0x287862EFC0DC6410ULL, 
            0x9A95165BF5E5EBEBULL, 0x9DF051CE31D9D781ULL, 0xD40A7AFEDD84E63CULL, 0xF71ECB0E212E231DULL, 
            0x0554EE634DAD306FULL, 0x6E277EC1C77D4622ULL, 0x97D42F04426F7EA6ULL, 0xA11173B31EAE1025ULL, 
            0x2B1F81267FFADBB1ULL, 0xB9B50D2F820E9909ULL, 0x06F3BF6384BF9C8DULL, 0x46822ACE09A11286ULL
        },
        {
            0x862890794BAF7F60ULL, 0x0F00302ED09AD207ULL, 0x90CD2A75B61F9726ULL, 0x7E20257FA8F081D3ULL, 
            0xB49C0DED710E35DCULL, 0x50CF4ED0CE4E5685ULL, 0xEB536A7395A90C5FULL, 0xD4C69AB0C9ED4988ULL, 
            0x6A63B5669834FE3DULL, 0x34419C82FB40A234ULL, 0xB624B31900763B12ULL, 0x93F56E32686D0610ULL, 
            0x212E9A996C84DD0CULL, 0x6C7C96AC3105E870ULL, 0x21C27B68FE9C2AC8ULL, 0x370DFED65F9FB7F7ULL, 
            0xF8AC395D06D32AEBULL, 0x19C9C66B3774CD3AULL, 0x37A2272ED2C9AE5FULL, 0x7212270534049389ULL, 
            0xE235BD036DB7BA5CULL, 0x027EF10AB6DD1BA5ULL, 0x7930BC9337CD1DEEULL, 0xD67F71368A14A400ULL, 
            0x1DA59726923A1976ULL, 0x8CEB0902AE8D69DDULL, 0x4D5B3944A30A82A0ULL, 0x536F7748FE3448FAULL, 
            0xD419C8FAE22BBDA7ULL, 0xA59E02B6404F41EDULL, 0x03567D6C8CBDB94EULL, 0x5441BB6B2920CD14ULL
        },
        {
            0xD8115CB7D92EFB56ULL, 0xC8939B1E4ECF9A26ULL, 0xEF67F922C07CE8BAULL, 0x94637150A639C125ULL, 
            0x246D6BD8B4A546DCULL, 0x1D2093EA75D36D8FULL, 0xDA6C0EB9A66C7109ULL, 0xC02B63A7D6CCD377ULL, 
            0x0443F54CB888CFA0ULL, 0x12CBA034EC795D9CULL, 0xC103EB9AD0087F60ULL, 0x59CADDC4E820611FULL, 
            0xCF26CDC9FFE7F42CULL, 0x3458A5F13362A301ULL, 0x758A0E7783273F69ULL, 0x01827BB7E61E0CB0ULL, 
            0x6BED8914E2BD8182ULL, 0x260E9035384B6365ULL, 0xE64A8D43D00513E5ULL, 0x93F79FD4B45EF8BEULL, 
            0xAC26B4DF553FEBA1ULL, 0x39153A16AC9DA99FULL, 0x88D9D8DF7771BB71ULL, 0xE993CBF12370B92AULL, 
            0xA3A30BD49517DE58ULL, 0x637A4D91724C8BBFULL, 0x5471FCA17590A6E2ULL, 0x857E491EA85DA233ULL, 
            0xC7CB1906E2C7327DULL, 0xF8F6AD2E30F647E3ULL, 0xCDF552FDB292876EULL, 0x7ABFB1431F24CEA1ULL
        },
        {
            0x3DDD753FAD16AC4EULL, 0xAF32164A4214D3BEULL, 0xF1D6590E2D81EC08ULL, 0xBD203C03B758E554ULL, 
            0xB390B8A528579405ULL, 0xBD7BA97D67A69815ULL, 0x6EFA453364F10B4EULL, 0xE85626A90FFFD001ULL, 
            0x4AE1CDAD88BD80A1ULL, 0xB50D45D08A72C6F3ULL, 0x25EB158BAAD080BFULL, 0x51ADDDEA7EF84C00ULL, 
            0x055F8D3585522FB6ULL, 0x7808D2E94225B98BULL, 0x4B18F2C595A8E53FULL, 0x8E6002B925DF0FB5ULL, 
            0x6DA81476D0BE0767ULL, 0x26ECC3B595FDC33EULL, 0x6F33A7EE90BFF01AULL, 0xBE4BDC3CD5EB10EBULL, 
            0x21AD9E2A9414333CULL, 0x966C43ACEA1C5F6AULL, 0x9084E26CEADA1AAFULL, 0x9E9D960858F85CE4ULL, 
            0x6ED3819D91B9AA21ULL, 0x28BB3F680CB0DDE2ULL, 0xA45207765C7587C1ULL, 0x7C6F3D7AC18A6967ULL, 
            0x58413FFE04D4AD02ULL, 0x279B1E386754DD23ULL, 0x3835A35C7FF13B25ULL, 0xB2AFD6B899229128ULL
        },
        {
            0xDE867D66BA8B2707ULL, 0xABCA0D5F7EE26335ULL, 0x90CC3522BAF88E01ULL, 0x6F7207FE6751E252ULL, 
            0x9626985130CD31A1ULL, 0x927D5D5EA021F6F2ULL, 0xA624E92BAE0D2E00ULL, 0x2E6C77560AF6677EULL, 
            0x9ECF548DE4AC6A08ULL, 0xC0528140BE2C7A75ULL, 0x3BAC6BFA9A7F3D85ULL, 0x95DD9093899C0905ULL, 
            0xDAEA4205177BCD6DULL, 0x03BD9B2796B256F6ULL, 0x97647D10AADC95ECULL, 0x1BE67096291373D8ULL, 
            0x054B65E82B8DAF99ULL, 0x40EAC41FA808DE7AULL, 0xDD54122033645C53ULL, 0x794C929640C6B48CULL, 
            0x692516B471A978CDULL, 0xC6222972F96F540DULL, 0x53FF5F1A502E26CCULL, 0xB5C6E2EE95ADFBBEULL, 
            0x526AC1CBBAAD1129ULL, 0xAEAF606CAAF97873ULL, 0xE4890D511614C483ULL, 0xEDE3AD1F2B2DF7F4ULL, 
            0x324D0997B3A645AEULL, 0x13042BD944076A82ULL, 0x7F17C39235C2D6EDULL, 0x01330D7CE3B4B033ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseGConstants = {
    0x11748BA64FCE9888ULL,
    0xD6C7471562441BF1ULL,
    0xB9E0D557E9A512A1ULL,
    0x11748BA64FCE9888ULL,
    0xD6C7471562441BF1ULL,
    0xB9E0D557E9A512A1ULL,
    0xA9E8683310D8EF85ULL,
    0x262206E05FB9505EULL,
    0x25,
    0xB4,
    0xDD,
    0xCD,
    0x91,
    0xE6,
    0x5E,
    0xA8
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseHSalts = {
    {
        {
            0x216288EB34E0B6DEULL, 0x3CCFE5953B1147F5ULL, 0xCA204C266CE2FBB6ULL, 0x5B316C32C35737ADULL, 
            0x59FA07C5768A2287ULL, 0x42ED33AD9442F906ULL, 0x35A1626E42BA07E0ULL, 0xFAF8334D72AB198CULL, 
            0x0832CBBE4E8CDA47ULL, 0x2170F367CE4BD814ULL, 0x571C75F57DEB460FULL, 0xAFB2F8682F8D8BC6ULL, 
            0xD74D3B7311084C54ULL, 0xAFA0FFCE67504C1BULL, 0x35A82836C1E7F134ULL, 0xA006148FE2773DC2ULL, 
            0x1C2A334C7F8B8CBDULL, 0x8F4E99F4BB87DC68ULL, 0xAC7BBAA71E3F7DD7ULL, 0xA72A661A522E55E0ULL, 
            0x459A17F1E3A5C83AULL, 0xC08BE92163E78383ULL, 0x3BE4A04096626C4DULL, 0x9A54F0EF1F4D9FCDULL, 
            0x5DB702496190BE39ULL, 0xAFF88879688DD1D7ULL, 0x461B154B6CB9D34AULL, 0xB65A9C7AEB51859BULL, 
            0x0DAA5E08FA606C93ULL, 0x1C04647A904D9369ULL, 0x9841C198C5B11B0DULL, 0x36F5CD48F8C76018ULL
        },
        {
            0xE1369F04301C5470ULL, 0xD93D7006FF346786ULL, 0xF9021A40B50A1A71ULL, 0x4BF3DCD7AF85A152ULL, 
            0xAFB39B0526951EE8ULL, 0xC841D30A6BC79462ULL, 0xFD12EEC1FFB528EEULL, 0x1E1934A01E5FC762ULL, 
            0xE27A44FE7E4FF464ULL, 0x7B8848F1C8ABAA8AULL, 0x856BCE8CABB4407FULL, 0xF37C7714CBA6FCFAULL, 
            0x3A7551D9C56EA9AEULL, 0x5CB57FBCD00E8DD6ULL, 0xEEA8F97CF9DF5CA3ULL, 0x32B34B0164705970ULL, 
            0xBAA8F1E973E53C82ULL, 0xE2DB4B045CFA5838ULL, 0x6B40055DE89ACED7ULL, 0xE9F9E09594436FE0ULL, 
            0x4F253CD9C587AAA2ULL, 0x24FC88CF5AF23543ULL, 0xD83BAF4816149D90ULL, 0x3A38E611C3ECE375ULL, 
            0x9BAD65B6BDC6B406ULL, 0xB46899860F22E7F1ULL, 0xF1A418D9B763CCEDULL, 0x7444D638DAAD4AA1ULL, 
            0xF897E8824E9E4F74ULL, 0x28EB159880A8EF3BULL, 0x7FB1360FDF4EC4E8ULL, 0x8D732D333403AC23ULL
        },
        {
            0xD8DD7981C3D7A2A9ULL, 0x7198ADB2895A6628ULL, 0xD9400F8EAD2F44E6ULL, 0xA9597111EF9EFFB8ULL, 
            0xEC0A290698CCD390ULL, 0x86B48AAB1324AC63ULL, 0x8BC09EC8E85BE380ULL, 0xB2F3E4AADC36DE0BULL, 
            0x4E5200209B7E1535ULL, 0x14924258850BCFACULL, 0x1BD1D320A49BA545ULL, 0x9C1B6E19FE91DBE1ULL, 
            0x1C0FD7C72DA600B2ULL, 0xC7C5014A7E2D65C3ULL, 0x9F2CD9026F9357D8ULL, 0x2175BD6EE668A298ULL, 
            0x2986632BA499DA42ULL, 0xF8D7CCFF98A6E525ULL, 0xC11ED46E4660E858ULL, 0x6634978433401BD3ULL, 
            0xF00CE4A884181250ULL, 0x1EB1E33EB28C278EULL, 0xADFAF259F7CF4CBBULL, 0xBE2B8D78CFC87BA8ULL, 
            0x966C849B5D037CD4ULL, 0x9B7C36EFC8CA5615ULL, 0x873EEDE726142517ULL, 0xC3DD720294617667ULL, 
            0x5A74CA5830098E2CULL, 0x254FE0F161FA72C7ULL, 0x501B19262EA1C28AULL, 0x8D4655A40049E3DAULL
        },
        {
            0xA44F778952899441ULL, 0x08AB63D99B9735D0ULL, 0xBDDC3C4F5BAC90BEULL, 0x530228035FFA949EULL, 
            0xE7720FCF92A9CF6DULL, 0x61973D2FA3A5FF64ULL, 0xB0AA5938F1F20E1BULL, 0x3BB13B056928AA59ULL, 
            0xE3D8CEF45FF3393CULL, 0xF2F9F982095BF520ULL, 0xF2048D5A1952D973ULL, 0x64A8DBC239C379EFULL, 
            0x880EEF25B9D07F92ULL, 0xC95B4A6C12E6A4C1ULL, 0x3CC1C2EDE77EB3C2ULL, 0xAFE911B612151735ULL, 
            0xCB8B5D338381D189ULL, 0xDC3E2526E1AF0DD1ULL, 0xB8ADB0A9334971BAULL, 0xB664FA1A3C877A77ULL, 
            0x346CA15782C05653ULL, 0xC37CE282F9F9631AULL, 0x1092CD8FDA6D0527ULL, 0x7803D2BB46DE4899ULL, 
            0xFA598DEDE716812EULL, 0x0978402664E6D273ULL, 0xF03282CCE6DBA9F9ULL, 0x4E1009A1456D4A6AULL, 
            0xF890EA3A9BD878D4ULL, 0xB955FF86808C3AFBULL, 0x8C99CBA9E65B273FULL, 0x17A7A39E43EBF5EEULL
        },
        {
            0x4FA00F7AF02D9FF6ULL, 0x6C5F96F55E0905C3ULL, 0x459E4A6FDB47DC46ULL, 0x81AEA730B732C65CULL, 
            0x00171F83E4C6AF27ULL, 0xEFB397175FC65746ULL, 0x30543E6C6EF34E3CULL, 0x6D510A4930D9186CULL, 
            0x0CC6B1ED8D511154ULL, 0x98BCB632B18B958CULL, 0x44BC180347B91D62ULL, 0x31155794A2BA0301ULL, 
            0xAB8BEF9B9F3C231AULL, 0x4563C86D87AFA34AULL, 0x148A352A3E351E16ULL, 0xD2B8D093378315B9ULL, 
            0x404B672F8A812E7EULL, 0x0778725891C13F78ULL, 0x410BB66552CAFCECULL, 0xE82EB4DE6DD3FE01ULL, 
            0x6954EC7D9341859FULL, 0x09832F6DCF8EE23CULL, 0x04A24AAC9EE0A7F8ULL, 0x5C3C2DBAE3BAF1A3ULL, 
            0xACABBA59D696190EULL, 0x4404F4BC1989BBD4ULL, 0xF368190FAF28E267ULL, 0x177951DB08B3AB17ULL, 
            0x0CCBC7BBB7BECC5EULL, 0xE3DE83FC5B39E0C7ULL, 0x2ACDAA6CB5A63071ULL, 0x6AA49F9429EF4C2EULL
        },
        {
            0xE46DA02E274BDF79ULL, 0x2CD26E56291CA138ULL, 0x027A75344C1A2F6EULL, 0xF7E7C3E603014685ULL, 
            0x05E7B6AC0E441355ULL, 0x55325A9AE4CA9A0DULL, 0xE29CA89317BB957AULL, 0xFFC27957FE992E70ULL, 
            0xAD26F6B2CF27561BULL, 0xC6E30B48DE6818DDULL, 0xE314F84FF832A319ULL, 0x37A7FB457799DA14ULL, 
            0x3F6F8C5040140A6BULL, 0xCD1805413851A440ULL, 0x8E254D41D42FB559ULL, 0x715A17A3D190F855ULL, 
            0xE230B6B2BA7CC31DULL, 0x599CFD61D28E4D99ULL, 0x7198E243F114C013ULL, 0xF37DA73FA64DD574ULL, 
            0xD8C14689D9A9452BULL, 0x1D0FD71979712601ULL, 0xE9437EBF2DD8234AULL, 0x1767E6F4BC2D4FDEULL, 
            0x07CA6ED17574FA47ULL, 0x3AE66FB3E6C57044ULL, 0x928449D2A134E975ULL, 0xEE6EAC6C3C4C5FD4ULL, 
            0xEF5E5030EEC6418AULL, 0x94ADF89466CBA198ULL, 0xD92D1ECD816849E7ULL, 0x42ABCF2718EEF211ULL
        }
    },
    {
        {
            0x82BB72575DA086B8ULL, 0xFFEC103E454A9BADULL, 0x5545F9320A16F36DULL, 0xF527B7B6717191AFULL, 
            0x4FC0BDA1B53618B6ULL, 0xCC6ED3C5DE403F59ULL, 0x114960960C4623D4ULL, 0x4C1A595A698E3D41ULL, 
            0x52C6B71176943012ULL, 0xD1253BBC1AE9014AULL, 0x51CDC7F27F741257ULL, 0x34DA9F4812A0C7E4ULL, 
            0x3ECC07D8C33FCB7FULL, 0x8D47BA8A40EF1629ULL, 0x150C415718306479ULL, 0xDE674BEE0062EF5FULL, 
            0xF78808F3B16AACB5ULL, 0xE30C2CE2C2A0F858ULL, 0x6E51C4F1253021F5ULL, 0xC6FCFD44959C1E8CULL, 
            0xBFB5AE93E3630BEEULL, 0xF859E5E6A4C70606ULL, 0x3E1F2F94A5F4CB80ULL, 0x5398ED48EEBAED88ULL, 
            0x6408D2AEE2427585ULL, 0x83FE2599D76CBEA3ULL, 0xC2DC7A7389A78D34ULL, 0x86291132631E71E7ULL, 
            0x3C18CCE541FF6CF9ULL, 0x12E350CC5F538383ULL, 0x97FC974F851A720AULL, 0xFFA831C8EB8C51C5ULL
        },
        {
            0x88D97FA7D1A559C5ULL, 0x7097FE4A9886F479ULL, 0xEF0CBBFB4DB73703ULL, 0x68CFE709357816AAULL, 
            0x42470912CA57E9B7ULL, 0xD2AD9B5AE92BED24ULL, 0x087BC3B6086A99F3ULL, 0x8029B290185417C7ULL, 
            0x703501FB5022F482ULL, 0x7F1973FD4A3F3CABULL, 0x78A0B291F155089FULL, 0x3776F0CA380EC5B6ULL, 
            0xF33B29844581D602ULL, 0x4BA30D295F49E5CEULL, 0xAA499303E48F814DULL, 0xD48521FF3719C39CULL, 
            0xAD17CFFDD9209E95ULL, 0x4E354E829E3FDFCAULL, 0xD04C02D4FB5088CFULL, 0xBE8C337464959A01ULL, 
            0x8651A30301985605ULL, 0x085CB1A81C66AF04ULL, 0x64DA2808E4A61DCBULL, 0xD39BC4855EED0E89ULL, 
            0x9F17D16C3CDF77E7ULL, 0x65DB385DF0EF4BEEULL, 0x4822263492C2EB5FULL, 0xA541C48AE5D31C62ULL, 
            0x0D2F1443B2D887B8ULL, 0x77C6EFC6B5CE5EF6ULL, 0x948E36FDBF4E0C9FULL, 0xD78E53281ABC88C1ULL
        },
        {
            0x21A08BD147631AC5ULL, 0x75C0F9E322199692ULL, 0x90B7E91C0A643987ULL, 0x42AC3ED329A7B039ULL, 
            0xDE77DE0938C4FFF6ULL, 0xC8F20C18C0423D5CULL, 0xEF5C71C92CAC7D02ULL, 0xF84E6716AA938915ULL, 
            0xBBD2E81C7E1BC448ULL, 0x49267A2716446136ULL, 0xB0957F7D6D800AB8ULL, 0xFBBD94F9595C6003ULL, 
            0xA25E4B68E654A980ULL, 0xB7C653AC48ED9F8CULL, 0x59CF7C343AA6C256ULL, 0x1E433421E64DCB19ULL, 
            0x275C769B78377573ULL, 0x57DBF0EB77CD1E01ULL, 0x824716468B7CC9ECULL, 0xAFB9443C386E25F2ULL, 
            0xA8E72DE922F4D938ULL, 0xB5AD7ADB07DA0E78ULL, 0x66D02FF1F932DCDAULL, 0x077D5B729284EA70ULL, 
            0xF3E847C61C26C7A2ULL, 0xFF2D073029F5BF2BULL, 0xC858E031EC702D0EULL, 0xF7431EA0C947AB12ULL, 
            0xCC3D668614F5C2C3ULL, 0x2D12E344EC5AE9A2ULL, 0x5CD3DD798AAD39B3ULL, 0x39F122088E7A95B9ULL
        },
        {
            0x87F9D87A3C6C44FFULL, 0xFDDEA3722259DDA3ULL, 0x53A81913CA0BBBB2ULL, 0x749F296CF8BA84CBULL, 
            0x922D573F321A03F0ULL, 0x63AE54AE3D5F054CULL, 0x310B26F36295AB46ULL, 0xA42A8B83DDCB5150ULL, 
            0x2B072A6190DC8844ULL, 0x55976793FE83AF8CULL, 0x6B33F1A7CC8DD550ULL, 0x71CDCA69383D13DFULL, 
            0x0F4600E24212F9F7ULL, 0xAF488950802D515EULL, 0xFCD8BD9B62337D8EULL, 0x48FE4CDF6565E4DEULL, 
            0x796F50F1DBCB89CBULL, 0x0F6226563056FBCBULL, 0x6175CA2479972A26ULL, 0x045C52E97577FDA9ULL, 
            0x707C34DDDCADA15DULL, 0xADF78347AB06761AULL, 0x7D8704AC8D96FB23ULL, 0xAA13195FCBE03099ULL, 
            0xECD15BD73C09C89AULL, 0x1AE47A2ECBAF7699ULL, 0xB8AF451CED077963ULL, 0xA4B867569FAF1929ULL, 
            0x0C580801EBB06FD4ULL, 0xDF3D597E443C39FAULL, 0x9E69D53231354527ULL, 0xB9875D397D8F12DFULL
        },
        {
            0x787B320C4B88BA4FULL, 0xB52A49BE3FA2954DULL, 0x789CC790568D6C10ULL, 0x4FD1CC5E1234B382ULL, 
            0xB13C67FACC5CD396ULL, 0x200100A83FF9B083ULL, 0x264760D14015A81DULL, 0xC96E50E0DEC09417ULL, 
            0xC3FCCB8EB12CCF3EULL, 0xA974926BC4B1C66FULL, 0xE764583DFD6007ECULL, 0xC736FAFCF6C2A309ULL, 
            0xDAA7A13CE0668CCCULL, 0x4E0290E85C9391E2ULL, 0x4243BE816F999BDFULL, 0x1CE5BBBC376F390DULL, 
            0x007D25D9B1248397ULL, 0xE3EDEAE11F7F8A3FULL, 0xB7A06E0192A8DCD4ULL, 0x92C9DB5A08BBF97AULL, 
            0xCF3115A589A989BBULL, 0x774E6755F75C8352ULL, 0xBD578E0B53075C0EULL, 0x8864991FFAA994A3ULL, 
            0x703776503FCF6B52ULL, 0xDD0D1582DF6D2703ULL, 0xB38EFD2F873DEC02ULL, 0xD9A2352DAE2172C0ULL, 
            0x755B60343BDDC9A9ULL, 0x3E1C8CD8968CC1ABULL, 0x757BE88FA1D296B5ULL, 0x88E14C6D0D3ED9FAULL
        },
        {
            0xB357A11164B86FE5ULL, 0x44C96C8F3ED6AD71ULL, 0xC87808665A31BD15ULL, 0x785CDB6DDF74DFCFULL, 
            0x3C59FA2A05CE17B1ULL, 0x4220105568657894ULL, 0x2A7FD18EA2B864BEULL, 0x45E461648859DE00ULL, 
            0x5168191E5EE2BEF5ULL, 0xE8FD33329B9B60FEULL, 0x2598A70D28393F4AULL, 0x27EF7DA31E2183F9ULL, 
            0x2ABFDBCA17D65B32ULL, 0x2A6190739DC29CBEULL, 0x44FE4F39674EAFECULL, 0x9E6012D0DBEAC88FULL, 
            0x7B1302B574F467DEULL, 0xC5438DFF57A4079DULL, 0x9C8402F1E7CBD75BULL, 0xC271BC055C228873ULL, 
            0xCE2CF481C8E4FA7DULL, 0xF62C12DFD5BE117DULL, 0x408CA5FF8F2B4C3CULL, 0x1D398FA0BE7780B7ULL, 
            0x86428DD6D4849682ULL, 0xE0F7EC48D85772D2ULL, 0xAE7644AFE46437B9ULL, 0xC394E2E4EBBCDD9CULL, 
            0x74A8B418E441112AULL, 0x3EC8C920A8F0264EULL, 0xD388479810716072ULL, 0x3094773C4E94B190ULL
        }
    },
    {
        {
            0x4467A824DBE92399ULL, 0x86A2864FAFFAE15BULL, 0x18CDD7C21F2CAC21ULL, 0x6F66E96A32CA1795ULL, 
            0x18C94453E2810714ULL, 0xC6D7BAB85F6355D0ULL, 0xEBAC0390C8071EEEULL, 0x01058755D31FBDF6ULL, 
            0x21F67C7484CE32A5ULL, 0xD0EC7F0744FB353FULL, 0xE85931198FEDFCEAULL, 0x29B3055EF9C22948ULL, 
            0x24E8BBC3BD8056FFULL, 0x28ED141F17B3F4B7ULL, 0x7196E0F83611B088ULL, 0x3F859141051C95CAULL, 
            0x8E19873E878F261FULL, 0x6BD8C4C58EE7F965ULL, 0x3998C40129ACFEA3ULL, 0x6BF33E84720152DCULL, 
            0x3D434D61EE7C3D1BULL, 0xEB257A4BC5BD4D1AULL, 0xCF6DFC6BD7311EB4ULL, 0xFFA026F692142BDDULL, 
            0x6987C8936BD5D58BULL, 0x050DB210A2650992ULL, 0x69A36B37A891DD14ULL, 0xD245303CA788836EULL, 
            0x43605F4DC099D573ULL, 0xED59F5B27680D62AULL, 0x2BFC9EB57AC59D5EULL, 0xC0DA5F141ADF3FE0ULL
        },
        {
            0x1CD95FE750081914ULL, 0xAC14D406D183BBD9ULL, 0x8611A33BA3704E7EULL, 0xEEFC7D7A7497A674ULL, 
            0x6C366A5D283DBF0AULL, 0xF8364E952213A5D0ULL, 0x6366C6CF4CA8E385ULL, 0xA92608D588808E92ULL, 
            0x8744CBC7D367737AULL, 0xEB0EC4E868C5B3A7ULL, 0xD80FD3C291DF67B7ULL, 0x56B1230BDA61A11EULL, 
            0x63803C59630053CDULL, 0x8D3DDA122EAFFE5AULL, 0xFB4075EE77C52A36ULL, 0x95D746E3A7ECAFC8ULL, 
            0x819E80FAFB1803F5ULL, 0x76418735C42AB830ULL, 0x691D2263ED7DD52DULL, 0x505C34F8CF1AAF4CULL, 
            0xBC67E3E561EFCB79ULL, 0x355D8DF90BCAF832ULL, 0xB2693E74F68F4984ULL, 0xC7C7661AE504881BULL, 
            0x1C36216EE5BE276BULL, 0xB8825F56DDC160B4ULL, 0x600DF954C3B636D0ULL, 0xEF9BAE2A9E448F77ULL, 
            0xD2441EAF0B179FC2ULL, 0x9E2B0EF4E6746B1DULL, 0xD3D56723D34B69FDULL, 0x9468C2026862B35CULL
        },
        {
            0xB9EFDDDE342ECF91ULL, 0xC07996D8A9F00484ULL, 0xBB9D85590C0B16BAULL, 0xDF9E6F9A6DEF6ED3ULL, 
            0xCAB4240EA8450BCFULL, 0xA14BC564957E123EULL, 0xEAB114BA8B5BC4A7ULL, 0xFDB92602D4DD6CB2ULL, 
            0xFF61A7EBDA429D75ULL, 0x8CC35906A3D7E4C4ULL, 0x4193A518E1684353ULL, 0x6D7C1B3D082116D5ULL, 
            0x93F93619280A3116ULL, 0x12049BBA4817C055ULL, 0xA13334AFC97FB422ULL, 0x88EBF146741361FFULL, 
            0x8CD3CD31946BA5EFULL, 0xCE9DCDF906588AA5ULL, 0xFF38FF487B29146DULL, 0x53B820571FDE13DFULL, 
            0xF5C9A2D0CAE91552ULL, 0x8FEBCB6FEEAE6234ULL, 0x5840154D7973C2C6ULL, 0x55167015F7F19969ULL, 
            0x006E731925F8FE47ULL, 0x8436148EB63698A7ULL, 0x0B20D2EE92BA771CULL, 0xBC01B00C4B50127FULL, 
            0x4FCCE4876E377347ULL, 0xE8870C791A64B88EULL, 0x571DB38B1E22D01DULL, 0xCFA10BDFCB8B7044ULL
        },
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
            0x7D3B79E56FDA3EEBULL, 0x9EC2482FDBD78E34ULL, 0xA22D4C5BD0B83EDBULL, 0x8646B2691203F91BULL, 
            0xA96456D0D6E7D243ULL, 0x8A8839D39D0C2B6EULL, 0xA58B0A05224C864AULL, 0x8B70F43151949FEBULL, 
            0x39CF39DBD6161E8FULL, 0xF86A45D9048F38DAULL, 0x88BD7FC8A9285C4CULL, 0x0283C455E62A8E09ULL, 
            0xBC14557237C620B8ULL, 0x92EB5B36E5DC4AD8ULL, 0xF8B118EE3382A5C4ULL, 0x58E0AFD0A5FED8E7ULL, 
            0x89DFDA359998E4E1ULL, 0x677AB94D0082F36FULL, 0x36CDE8411729AA2CULL, 0x5E17CF89C827A1D5ULL, 
            0x821447E7F9CAC870ULL, 0xAD84999DC0A62891ULL, 0xD86996A773DF14F1ULL, 0xD809F9691D0BD0FEULL, 
            0xB4AC048151EAF756ULL, 0xDE783F4F6A7C9AD7ULL, 0x64CC390A7D17E1BDULL, 0xF308C4C52E264E60ULL, 
            0xB05EC207DA4A8E3FULL, 0x46CE2FFF9CFD4D77ULL, 0xCD09EAA594DD1E8DULL, 0x7CF7B2750B802AD3ULL
        },
        {
            0x51504284EC8FB4B3ULL, 0xCCA16CB942DDB3C5ULL, 0x288BC8B2EDD820DBULL, 0xEAD7475DABD0D3A5ULL, 
            0x960206765A66A6ADULL, 0xF8947E66969B9832ULL, 0x012D40FDFF8E010CULL, 0x959B15BAD2F7D2EDULL, 
            0x2E8469643540D14AULL, 0xA93F255EE9FB2605ULL, 0x20A4CF22E75D3154ULL, 0xADF3247850B33E65ULL, 
            0xE14A970FD7A6F754ULL, 0xA4B5EBD15C9B1B80ULL, 0x9D4A8AF9A4B7AA70ULL, 0xB2152F88FDC9F31AULL, 
            0x1DD2EF625D2674E2ULL, 0xAB2F53C180A13CCCULL, 0x23B58252C340B2A4ULL, 0xC33537732E819BB8ULL, 
            0xD1EEC5BCB00920B1ULL, 0x135FEA3E9F9C80C4ULL, 0x83AFAD2B151E487FULL, 0xD9A8C8FAAF7D25A3ULL, 
            0x66DC185F59C38F9EULL, 0x32F8A77FC7D98B9AULL, 0x8FE8793FE62D3B44ULL, 0x3C3860573A92C53EULL, 
            0x8E6FB954550796C2ULL, 0xDC8ECCAD75F778FEULL, 0xD1C62F462994015CULL, 0x582E518213E557ADULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseHConstants = {
    0x2BCC08020ACE9AE1ULL,
    0x6585FB251408ED7DULL,
    0xA8CCF7CF2C804809ULL,
    0x2BCC08020ACE9AE1ULL,
    0x6585FB251408ED7DULL,
    0xA8CCF7CF2C804809ULL,
    0x9D71FA8250F4E8CDULL,
    0x288B1FAC7F8351FDULL,
    0xAD,
    0x56,
    0xBC,
    0x31,
    0xC8,
    0xA8,
    0x50,
    0x24
};

