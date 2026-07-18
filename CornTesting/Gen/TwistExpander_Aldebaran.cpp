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
    std::uint64_t aPrevious = 0xB7FB843BC13F667EULL; std::uint64_t aIngress = 0xAF0D94B630A625FCULL; std::uint64_t aCarry = 0x893BD38F6718FE5AULL;

    std::uint64_t aWandererA = 0xE54AC2316D87E07FULL; std::uint64_t aWandererB = 0x969DD69BA8B61211ULL; std::uint64_t aWandererC = 0xFDF707EBA81EB009ULL; std::uint64_t aWandererD = 0xF5CF94E56F488E23ULL;
    std::uint64_t aWandererE = 0xB1679B2F18E05F15ULL; std::uint64_t aWandererF = 0xF4AE468C0B3C5025ULL; std::uint64_t aWandererG = 0xFEBF41321EA6A6D7ULL; std::uint64_t aWandererH = 0xC3D65F9A7008E973ULL;
    std::uint64_t aWandererI = 0xD284A79F595E52D4ULL; std::uint64_t aWandererJ = 0xE0A0A87B76C7D09BULL; std::uint64_t aWandererK = 0x85FD6F095B8177A4ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12607898441575386454U;
        aCarry = 15813361860207422561U;
        aWandererA = 9552519975260805907U;
        aWandererB = 9763570107684785144U;
        aWandererC = 12705803493743267201U;
        aWandererD = 13461452179658684084U;
        aWandererE = 10476472361345988469U;
        aWandererF = 14573175088944204242U;
        aWandererG = 14652077764627832304U;
        aWandererH = 16667023610013971687U;
        aWandererI = 17852990201440682210U;
        aWandererJ = 14033773810068537362U;
        aWandererK = 15852283372778629271U;
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
    std::uint64_t aPrevious = 0x9EE6A7DD38576BF5ULL; std::uint64_t aIngress = 0xCE5A71A17BACCC37ULL; std::uint64_t aCarry = 0xC3EE1DEE5B30973BULL;

    std::uint64_t aWandererA = 0xFCFAD9EEA7156BA8ULL; std::uint64_t aWandererB = 0xB8388C1826DDE7C4ULL; std::uint64_t aWandererC = 0x8A910212FEF45DB5ULL; std::uint64_t aWandererD = 0x90BA8E01CA84FB95ULL;
    std::uint64_t aWandererE = 0x93EEAF096EAD2615ULL; std::uint64_t aWandererF = 0x9C4C30EEB4E8A20DULL; std::uint64_t aWandererG = 0xF9310641BD2343CEULL; std::uint64_t aWandererH = 0xB8DB03F9A2C3632EULL;
    std::uint64_t aWandererI = 0xF84F350D51D77330ULL; std::uint64_t aWandererJ = 0xD04D0C724B1844E8ULL; std::uint64_t aWandererK = 0xF5751C3C9F3469ABULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12915519102372740571U;
        aCarry = 17483960629450412910U;
        aWandererA = 12251372687022602225U;
        aWandererB = 11305413425823937963U;
        aWandererC = 9305783730784318826U;
        aWandererD = 11182565308719324401U;
        aWandererE = 12103545535610144329U;
        aWandererF = 14275265391765444426U;
        aWandererG = 11298284255985464411U;
        aWandererH = 15056828628250167243U;
        aWandererI = 18215455088059682109U;
        aWandererJ = 12010667469447772899U;
        aWandererK = 12527993429065487911U;
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
    std::uint64_t aPrevious = 0xB9FB74AA21128651ULL;
    std::uint64_t aIngress = 0x955C5872C3ECA3F5ULL;
    std::uint64_t aCarry = 0xA145D99585423C83ULL;

    std::uint64_t aWandererA = 0xFF4CA8A9DDD2D952ULL;
    std::uint64_t aWandererB = 0x817CB3408CDBEF07ULL;
    std::uint64_t aWandererC = 0xDF4A879E2A2A578AULL;
    std::uint64_t aWandererD = 0x9610C34B3B146A95ULL;
    std::uint64_t aWandererE = 0xE937000E4673CF4AULL;
    std::uint64_t aWandererF = 0xCC2610BFC6DF1351ULL;
    std::uint64_t aWandererG = 0x9AC2CCAE797292B0ULL;
    std::uint64_t aWandererH = 0xFD70882F818D980DULL;
    std::uint64_t aWandererI = 0xDDAE09FBBD13E405ULL;
    std::uint64_t aWandererJ = 0x978BC751F0D32B7BULL;
    std::uint64_t aWandererK = 0x9905D388B7FCE47CULL;

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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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

        TwistSquash::SquashB(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
    std::uint64_t aPrevious = 0x9D6065DBDCB31E89ULL; std::uint64_t aIngress = 0xA091B66A0BF92578ULL; std::uint64_t aCarry = 0xE39C82E4EA4B4439ULL;

    std::uint64_t aWandererA = 0x85CA99087F70804CULL; std::uint64_t aWandererB = 0xE10F66D31F7719A4ULL; std::uint64_t aWandererC = 0xBDEF6E84D06718A8ULL; std::uint64_t aWandererD = 0x9EE0943314A63B19ULL;
    std::uint64_t aWandererE = 0x82ABB227B588A849ULL; std::uint64_t aWandererF = 0xED566F4AE4B1B17EULL; std::uint64_t aWandererG = 0xB83518B44B386A6BULL; std::uint64_t aWandererH = 0xB20DDCC277F48488ULL;
    std::uint64_t aWandererI = 0xC6E9F66FBC0A593CULL; std::uint64_t aWandererJ = 0xB6CADC2E6B360D44ULL; std::uint64_t aWandererK = 0xADBD5822BD62A2CDULL;

    // [seed]
        aPrevious = 14661662624562527704U;
        aCarry = 9829053087726418428U;
        aWandererA = 16879516023132721101U;
        aWandererB = 9445453753482531895U;
        aWandererC = 16223613675678104415U;
        aWandererD = 10542159157040255462U;
        aWandererE = 14525606837161534558U;
        aWandererF = 10194031870358638261U;
        aWandererG = 9516695082443271505U;
        aWandererH = 11404359256243084329U;
        aWandererI = 14442325403411695839U;
        aWandererJ = 16882408981260889305U;
        aWandererK = 14574873290506102866U;
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
            0xF97951B868CC0E62ULL, 0xD8FD6B05396C5D9AULL, 0xAF0AFBC0998BBEB1ULL, 0xB6ED14197A3F5D2AULL, 
            0x613DA1085171E6DBULL, 0xE1AC987A384DD03CULL, 0x688C4967FA2555B6ULL, 0xECA5B1E36CD447A8ULL, 
            0xB17703B2915C8329ULL, 0x07A0F38C0B9FD491ULL, 0x2CC91D6D4D21A3FFULL, 0x0BE347414EE2F873ULL, 
            0x061038EE595118B4ULL, 0x68848BF0E4D0AA9EULL, 0xEEA430BA09887941ULL, 0xE44235E875785779ULL, 
            0xD13627A825F09E79ULL, 0x89D6D1960AFFDC69ULL, 0xCEE47A58169B7A8FULL, 0xDAF94F3C6A44082DULL, 
            0x736BAAE3DC17C5C8ULL, 0xD11542E6FB35A1BDULL, 0x6EFBCF0488BAABD0ULL, 0x9F938FF4C43504CAULL, 
            0x40201C065B632AF4ULL, 0xF51CBE7DD44365FFULL, 0x0AB3C69C069C76BCULL, 0x032BFCA05DE8D190ULL, 
            0x015A934EC576DF7FULL, 0x37941693FEA4F294ULL, 0xEA0718DD86D4D383ULL, 0xEAA947479F568810ULL
        },
        {
            0x108BCA687415E34CULL, 0x16DC0E2E6E37F2B0ULL, 0x09C36C87AA5DCD32ULL, 0x899C22DD6D7B6294ULL, 
            0xE9BED1B1D0C946EBULL, 0x68D163FFD008EE58ULL, 0x4D98C3C5A8C35045ULL, 0x623F3B5649B566CFULL, 
            0x2A997C89695E4062ULL, 0xCCEDD70B860B295CULL, 0x85ECFA1D846A7466ULL, 0xBD718D365A365528ULL, 
            0xD50954A94F89585CULL, 0x0199B51D0A3B5F2FULL, 0xA56A16F83EB863DFULL, 0x9EAA8BA01E5ACB99ULL, 
            0xAF19436907A0A1EFULL, 0x70745587FF5D54F4ULL, 0x55F2C00B91B9D0FEULL, 0x907E63E9A86CB34EULL, 
            0xD635B3F95794FDF2ULL, 0xEBAB5B342B640336ULL, 0x68166EF069329D80ULL, 0x2229D5EB2445009FULL, 
            0xE34209AB1D588F38ULL, 0xF4FF7C99C07DFB35ULL, 0x442AAB8C1095D130ULL, 0x855001158101088DULL, 
            0xAA63518F7C5EFD9BULL, 0xBB0CDF27BD03F893ULL, 0x6A5AF27B3FA560BFULL, 0xDF52E393C5ADC993ULL
        },
        {
            0xB94856D9B68753E1ULL, 0x29E4A6A0D6D229C8ULL, 0x6BD8A49B987A92E3ULL, 0x529A96E25E93B33AULL, 
            0xA5C45C859D21D647ULL, 0x4E0D77F7D14626FCULL, 0x30481B9F537A3F40ULL, 0x7132778180603DBBULL, 
            0xFD1E8C64CFD1F61BULL, 0xE379D1EE27A28EA9ULL, 0x292F7848DC617847ULL, 0xA2A99B55D3839411ULL, 
            0xA9D6519063761291ULL, 0x376419C27EE194D9ULL, 0x52B2E7D36B82C327ULL, 0xA31B46670D556478ULL, 
            0x6586D16335F2B810ULL, 0x9F99D20AEBB76F49ULL, 0x28C8753ADA77E673ULL, 0x30243EC4CBC91878ULL, 
            0xC6A4D977DE83905FULL, 0xB27EF99FC07AB77CULL, 0xB712C6C8FEE570A0ULL, 0x8CE48B7396B0ED34ULL, 
            0x57AAAC2F263D90B7ULL, 0xD502A844E0C97498ULL, 0x9255F89A6A8F015AULL, 0x423DB0EA08E45D22ULL, 
            0xC77AD88BFCBCEB8BULL, 0xFD636B4FC39E4CA2ULL, 0xCD79A3BDE849F867ULL, 0x058ED101B997B4BEULL
        },
        {
            0xF61F866294237E1DULL, 0x87B04AB1D18F643AULL, 0x47ECD432D565C808ULL, 0xDCF9CBE49DC7CE06ULL, 
            0x236D87542A7EB4D7ULL, 0x93AE13A9458FDB85ULL, 0x7079F814DC10AFC4ULL, 0x6C38749A22152FECULL, 
            0xEF02820D975AF9BFULL, 0x4F1D3C918CB8C0EEULL, 0x2B0815F30391841FULL, 0xCEE40B96DB3A93BAULL, 
            0x9C5572497D7A441BULL, 0x71352E3F64E16F50ULL, 0xBEB57C208FCFB025ULL, 0x9FA2324273898CBBULL, 
            0x83C47DC2A50109CBULL, 0x3F127D31E55FCAC3ULL, 0xA1A554B09D7EE87DULL, 0xEC28E21625BB796CULL, 
            0x2E429FA724B7F1ECULL, 0x5E9BA9A8FEDB43AAULL, 0xB04E794CD3B2B06BULL, 0x0F59E83FE97D866DULL, 
            0xCA1DDD93775929CAULL, 0x77626D12BB354E53ULL, 0x62E0816AB48B16E4ULL, 0x9A7796603BF6E2EAULL, 
            0xA0921013FE39F882ULL, 0x3C82BD8A1D255894ULL, 0x862C8641F588B7F4ULL, 0xEF5B02D431D39A8CULL
        },
        {
            0x19421F2B52E3DEFAULL, 0xA68C12203DCF421FULL, 0x43C824C52884DE6EULL, 0x09E13B51B6D3A847ULL, 
            0x134DE09070CCBB05ULL, 0x282BE77C151B025CULL, 0x6AA716F6A8AA7966ULL, 0xBF4CAAA28496797BULL, 
            0x3B4BFDFC478AC0F1ULL, 0x31417FF1B5541F8BULL, 0x7B12B46AB4AEEC96ULL, 0x66958E7999924DE3ULL, 
            0x7EB2554296DC5843ULL, 0xF0EC1F97CF329054ULL, 0x279AE2F432C63C08ULL, 0xFF32913632A76E00ULL, 
            0xAC131171AE74BA0CULL, 0xED1A9ED40F1A5306ULL, 0x814867C91B396CC8ULL, 0xE54D4E207F65D833ULL, 
            0x30D5C47D73A41446ULL, 0xE5EEE90C4C79D7B9ULL, 0x5E75B2770D9A9923ULL, 0xA0CC16BC7A2C2403ULL, 
            0xDA86437280D8B921ULL, 0x2235E59B4B017998ULL, 0x5EC2BAE3FF9B328DULL, 0xA5276ABE4062DBDEULL, 
            0x3D580B83A5754CBAULL, 0x637B18725E4D2661ULL, 0xDC89EA78C85A324EULL, 0xF80A05130798F215ULL
        },
        {
            0x2F877CA3243C1828ULL, 0x2CCDADF70CCD95DFULL, 0x0AE23B1A9637F0DFULL, 0x709AD81C08F2A34FULL, 
            0x9396128351D3C7EDULL, 0x728C6224E24CC6B7ULL, 0x8771D10E7B0AECFFULL, 0x751E9F03A46D25B8ULL, 
            0xCD0EAD65899BC3CDULL, 0xFD8B63B0E10C1B37ULL, 0xA02F82F1FD815AF8ULL, 0x2A39A860B25BA5A9ULL, 
            0xEDDC3999CA973AFDULL, 0x7ADD517CFFF2FD35ULL, 0xE1579DC4A1146B5AULL, 0x8B8AD77CB6491752ULL, 
            0xF95E0CA2BB88E6AAULL, 0x3BDC028BE419B481ULL, 0x8BA1AB6528A9E7D2ULL, 0x3B63FBCC5728D8FBULL, 
            0x83A15995E8AA7277ULL, 0xBC693A82F3B4CD9AULL, 0x254B06565036F5DDULL, 0xC8A1E2A84059902EULL, 
            0x26C94F87BC31E979ULL, 0x52F2C194AC70E6CAULL, 0xB59E8869BC043FFCULL, 0x627BCFE4382838AFULL, 
            0x1ADB333A4AB3C3F9ULL, 0x7F1B205805B6760BULL, 0x47D34721F0B37621ULL, 0x597B3021998A2CE0ULL
        }
    },
    {
        {
            0x7A8F2958DD280C23ULL, 0x80B9FEAD76A13DA5ULL, 0xC7B0304B65BABD25ULL, 0x922D56294B4724B9ULL, 
            0x13E409C387392AB6ULL, 0x595726F37C1FB9E9ULL, 0xB0CDA84A27C2DF2CULL, 0x2FF18B27FB11F9A0ULL, 
            0x3A78A62D9CDFFA8EULL, 0xD8288E164ECB1C5FULL, 0xB2DBAE680BDE65A4ULL, 0x1B3B22C3F9E01AD2ULL, 
            0x1C5238F6C5FD1DC2ULL, 0x9790E26D2BC60F8BULL, 0xBAF8E1B8B9A91F4DULL, 0xBC8641024D44939EULL, 
            0xFAE6C982D50B7678ULL, 0x9D263F082E500608ULL, 0xC3AB80453BDC8944ULL, 0xA07400C7DA625B6BULL, 
            0x090854A27FA9D5B7ULL, 0xE48251A608151B01ULL, 0xA239EC7517B5B838ULL, 0xCE1043846475C9B2ULL, 
            0x1C4839257010EBE2ULL, 0x59FCBCAA314CF2E4ULL, 0xA1701EC5290B526AULL, 0x1EB36D8F3D02E64AULL, 
            0x48DFD71658A84DB1ULL, 0xFB730787625DA839ULL, 0x8AF5AD6E3D23A2CCULL, 0x6CEE67BDC8A995A3ULL
        },
        {
            0xC617E9850F6E8B8CULL, 0xEB1EB4F7EA770161ULL, 0x1E6A8E6CE310C9DFULL, 0xD0DB15D47F7FC81FULL, 
            0xD9FC968AB8B01A42ULL, 0x26F328660E33E5ECULL, 0xE5D95D07EFF89BE8ULL, 0x6276D2C4D526E348ULL, 
            0xFEFCA8BB1FD6F216ULL, 0xF96E4038F6E38E0DULL, 0xBB3F5EE1547FB915ULL, 0xD6747EA10D201B13ULL, 
            0xF34BB9F05197C94CULL, 0xEF1DA771942BC919ULL, 0x3CB841C77D67CA9CULL, 0xD54A568E720DDE8FULL, 
            0x918E84BFF05E19E0ULL, 0x6861EB6A9710C91EULL, 0x611DAC79D60E13B0ULL, 0x0550EB9BAC8657BCULL, 
            0xB896CE956973B82BULL, 0x16C7B387FE906B92ULL, 0xFF4A2E47708B535AULL, 0x0A9A454DDC7DCE4CULL, 
            0x5B42FA1CED500633ULL, 0xA610E154A68DE60FULL, 0x6DED5BBF7D2B0041ULL, 0x654B43A272641FAFULL, 
            0x93A282E9BFBB7320ULL, 0xE426A3ED45A1D507ULL, 0x15CC004B9DF4A8C7ULL, 0xD554767C59BCE871ULL
        },
        {
            0x7AAE04E0353CA990ULL, 0xCF1483F9ADBC6AF1ULL, 0x653A1BCB3A0C9B78ULL, 0x549CC3DF15525AD0ULL, 
            0xFCF9E13D3AAD96E1ULL, 0xC8CC4669D0AD26D6ULL, 0x1329D552A8409BF0ULL, 0xF7A8408AAB67EC02ULL, 
            0xA77BEDB324F0D0A4ULL, 0x647E97D9C550B3C2ULL, 0xC4514FB001A949E9ULL, 0x667BCA57A23B008CULL, 
            0x78104ECD79FC28C2ULL, 0xC3DB7CD7BBFFE61EULL, 0x0E1886E926B48322ULL, 0x47B76DDCF0782704ULL, 
            0xB122A6F5541BEC9EULL, 0xAAF28F59C7EF4A99ULL, 0x5A4CF1BEFF8A3328ULL, 0x0DFE90A51FFEC22DULL, 
            0xDA7881CF69B48154ULL, 0x0F285C0FA08F67CCULL, 0xC98567E6C3F57D8AULL, 0x66C96549412D5F9FULL, 
            0x85BC090FABABE687ULL, 0x5BB9510E5C68D50CULL, 0xC8CFEE8D850736A4ULL, 0xA6ECB4862F0ACF64ULL, 
            0x2EB8325B914776E3ULL, 0x9CDCD99E9F4B7ACCULL, 0xBB67467F2C73C7A6ULL, 0xF2D6840B880DCCF4ULL
        },
        {
            0x1CA117B77C307A33ULL, 0x38AC6CD3EDA8C79BULL, 0x2F5CBE05A567BC66ULL, 0x16547AEB05063829ULL, 
            0xEBE2BBE3E21B293EULL, 0x7C33499539852FC4ULL, 0x1BE5066AD987E8E9ULL, 0xD963BA2B4B6FAC68ULL, 
            0x721A8CB651ACF958ULL, 0x80C9518D60905321ULL, 0x158BBFD2561079B7ULL, 0x999A8BDB68CBEC5AULL, 
            0xE4F2DB103B8766BFULL, 0xC088237358139FCDULL, 0x7BCEA9226C6FE488ULL, 0x11904D7C758391CAULL, 
            0x5036ADF42D3BA5ABULL, 0x4FB00625C99CAAB9ULL, 0xDE05B0E3908EC6F4ULL, 0x9224551C30475CFCULL, 
            0xD9AC9A18DDE251ABULL, 0xFD5498E58A6EBF48ULL, 0x056B00CA033AE7A4ULL, 0xB5F17DBD3D2845B3ULL, 
            0x8011575181EF4AF9ULL, 0xBED89CCFBA8A2E16ULL, 0x536FE5A9BD61C875ULL, 0xA77F97CFCEF3F75CULL, 
            0x9D41EDD373CCFBFFULL, 0x432862C8994A777BULL, 0xA7ED8D9BEA700C65ULL, 0xD41628BDB5BBBDA1ULL
        },
        {
            0xA841AB3D249CA99EULL, 0x278136B43ABC389EULL, 0x20A068701F0D59A7ULL, 0x4B58DD42A9487DD9ULL, 
            0x774ED56033BF4B79ULL, 0x8052AEDE415DD8FAULL, 0x0FF0E5C86126E9FCULL, 0x0149710BCCF44538ULL, 
            0xAFF48D4CB91A4B3BULL, 0x6F54436E841E91F0ULL, 0xB312D8157EEBBECDULL, 0x23B6E9121F51A958ULL, 
            0x5B4F791BC6179705ULL, 0xEA804CBCE2F7018AULL, 0x9AC18F1AFF621E7FULL, 0xAE04B8DC0039E669ULL, 
            0x4DEBB1FEC809AD6AULL, 0x5C38B18901D3FF03ULL, 0x9500B458CA9F9F24ULL, 0xB33AC360B7AA0B14ULL, 
            0x8E396A97410BB3B7ULL, 0xDB629BDF5540A2CEULL, 0x12DA949D695109B6ULL, 0x83399C5F21A7132EULL, 
            0x29130ACEF7C12264ULL, 0x1E33A272071CDBD0ULL, 0x5301FFB617BE4D4CULL, 0x2FB640B8E190A715ULL, 
            0x86902AD291CDFA8AULL, 0x80DE1E33E5A2755FULL, 0x9C8728D61311F308ULL, 0x88C633E6B682402EULL
        },
        {
            0xD6EF69654CA5605CULL, 0x7A6D49E6F811EA8FULL, 0x64819526F6A02A9AULL, 0x789628B1D145AD9BULL, 
            0x3FC8594463467F0FULL, 0x5D5BCD85F17348EFULL, 0xDA0E311075B1C371ULL, 0xF335D3D2E0DD1F93ULL, 
            0x9871C11DCE3A1467ULL, 0x9250CF20AB337ADDULL, 0xAD118A1070DD51FFULL, 0x88D9E61278B5DDD2ULL, 
            0x5D8AD0E56865BD61ULL, 0xB70F00050EA63906ULL, 0x4A63BBBA304BCCBDULL, 0x68F43E9C7D11F4FCULL, 
            0x9CC61644481BC474ULL, 0x37BD2E84AC6E91CFULL, 0xD9039C6F280243A6ULL, 0x07984CA625390DE4ULL, 
            0xF72DE532A3502ECEULL, 0x628670FEA995ED42ULL, 0x496AD6D43EA927F5ULL, 0xF5E2D6425814A15FULL, 
            0x6DF8435B4C047C90ULL, 0x1E4E981A37972708ULL, 0x514A57776BD5E0E9ULL, 0xFAB9A60EC81421AEULL, 
            0x505837628C59AB8AULL, 0xB6B51D0BD1A2C68DULL, 0xEA55D3DAE5F4893CULL, 0x1E8D4B7300F83079ULL
        }
    },
    {
        {
            0xED8FE81F06EF4074ULL, 0xE88FB4798AF24842ULL, 0xEF6E373908001FF6ULL, 0xBFFE680181C85155ULL, 
            0x05EC1DC2446F1AB9ULL, 0xAB5B7AD10DD7A7D8ULL, 0x0810B6490195B4C4ULL, 0x7A1DBC437A0FD204ULL, 
            0xF2B2A48EC0A08E55ULL, 0x6CBD85BA640DD41EULL, 0xEEBA0AB539061A03ULL, 0x9F5950680AEDA87DULL, 
            0xB4587F0315879661ULL, 0xC732A8383D0BD919ULL, 0x709A57D7502512DDULL, 0xA78BC69CCBB640C7ULL, 
            0x767F6884ED3BD73DULL, 0x74E5B4DF14E878D7ULL, 0xBC568B0B9559D153ULL, 0x25CB54CFF29590EBULL, 
            0xBFF5FBDDC79523ABULL, 0x00B70B27D6585EF0ULL, 0xB47B780EA12E049AULL, 0x079EAFEBD52EC2D4ULL, 
            0xCF41223B5758D030ULL, 0xFF44D97E139AD5D9ULL, 0x30E4EDF7B280FDD4ULL, 0x0BB292638D5ECB11ULL, 
            0x38A1C7B73DDF2AEDULL, 0x55907124B35A2BAEULL, 0x896B2D8238EA375AULL, 0x50FE8CAC41C877FBULL
        },
        {
            0xC80FF71FC2BD9B11ULL, 0xA06959E334F46473ULL, 0x45E8AF83B52A2D87ULL, 0x26A79E860BA5194BULL, 
            0xB8B9C9FFDA705494ULL, 0x5D2E7320F3931C1AULL, 0xCA9F9EFEE642BB7AULL, 0x269A8EEE2F9CD5D5ULL, 
            0xEC4940B2995F85E9ULL, 0xDC3F2C0C54011F23ULL, 0xA4D722236CE5B292ULL, 0x6E6213F36EACED4CULL, 
            0x5776F595CB022E33ULL, 0x3CDA61FC20C9F165ULL, 0xD4E0CAC37E913C88ULL, 0x0352F8B6864ABED4ULL, 
            0x128B9BB99E73230CULL, 0x473E160D7BE90265ULL, 0x9204BF2A48F2EEC9ULL, 0x0DA1BCA715D9D359ULL, 
            0xE915973C359154FBULL, 0xA92E0489694D6763ULL, 0x8A130DA49C2EB6BFULL, 0x0ED8552D57536F8EULL, 
            0xCC39C3DA4B270794ULL, 0xC080972751918F3AULL, 0xAE9E530E3969D2F6ULL, 0xE9F8DDFBB9AF11EAULL, 
            0x301AA22963E95E98ULL, 0x185D322FA6650810ULL, 0xF4016C3D784764E0ULL, 0xF31D5AD22BC20E30ULL
        },
        {
            0x781CF9793E947C3DULL, 0xF163DB9B007206CCULL, 0x8D21F0C1BFC52DE2ULL, 0x88681A95EB63540FULL, 
            0x4EFC4B8C3106C6B1ULL, 0x18D2F946309FDE22ULL, 0x6A77A858EB8137C1ULL, 0x97B24B3B92484FE3ULL, 
            0x1205C191F7F4CA51ULL, 0xE0B639D9CC928646ULL, 0x976966A16492C536ULL, 0xBC92BCCDAA6B9AB3ULL, 
            0xC2923C6E33023721ULL, 0xABD28D5F5BB400BCULL, 0xE57401EF17DD1694ULL, 0xBD515B06B2323E54ULL, 
            0x79E97ADE7F8C68A1ULL, 0xB75007CBD75686D2ULL, 0x9A119E9A899B3E57ULL, 0xC6DDBDA40C939EDFULL, 
            0x13BD0301C19C3400ULL, 0xDB2E89DC4672F8D4ULL, 0x34A85D4EBFB452A0ULL, 0x9B55C0E274F722ADULL, 
            0x04859CB670B2AF9FULL, 0x862520FB7E3371F3ULL, 0x288EDE93ED17130CULL, 0x353F61F927215474ULL, 
            0xEF985C5EB8CB8BD4ULL, 0x56C10396A8B3F825ULL, 0x37D57F5D798DF9EEULL, 0x5A9AF6CA2263CF67ULL
        },
        {
            0x8D5574813D2DA145ULL, 0xEF459DA3D77A7724ULL, 0xEFD051244CF51E3BULL, 0x6C25D82BEFF8F6ECULL, 
            0xA1A12B4650CD1731ULL, 0x841459DFC9E9B063ULL, 0x667A0B930E559653ULL, 0x85BF8B6DE1154D44ULL, 
            0x83991459132617DEULL, 0xD41A9E6BDA096666ULL, 0x43F807ABB82BADE5ULL, 0x22B63D7C5BE01F42ULL, 
            0x45D9D69323C5E07EULL, 0x42E236890DC8B30AULL, 0xEAA2244685975023ULL, 0xADDFE0ABF2CC6893ULL, 
            0xA8AE994397719699ULL, 0xB1D054A93F477991ULL, 0x222059F6694F485CULL, 0xFA4AE24FF8B0F35BULL, 
            0xA2E34F5EA823D7FDULL, 0x254E03D757F8687DULL, 0xC8B1F7ACC42E2E52ULL, 0x9B0622462E16471BULL, 
            0xD148B0E9D8BC5439ULL, 0x66696773DF7B5B9BULL, 0x31AAEDEFA1E92E33ULL, 0xBFF814FA9DF489C6ULL, 
            0x4C716CA26E2CE257ULL, 0x058A1D811BD5EE4FULL, 0xE24F53141023B816ULL, 0xB3658D6FF9C0D63CULL
        },
        {
            0xA445DB6260B96944ULL, 0x3E463779839A5D50ULL, 0x6FD87442271A6B12ULL, 0x6F72835CCDCE18BAULL, 
            0x96572B7C3AB03EFFULL, 0xEE8BF31339DB215EULL, 0x9B02DCE61FAF0C57ULL, 0xAD9AAA3CC278AB26ULL, 
            0x045898272AEC3A24ULL, 0x21934411FFC4DE3FULL, 0x7490F0EDA6C75865ULL, 0x70CA1B8902B5E302ULL, 
            0x7D1C247A3A1A3583ULL, 0xB2793A135ECE8A0DULL, 0xDE4587E0680224B1ULL, 0xDEE60A8610BC3C35ULL, 
            0xA642FD33E2F94CB3ULL, 0x518B71AE8B2E36B4ULL, 0x4CAEAA1F643E87FBULL, 0xA0FC0F0700F20D2AULL, 
            0xF6306142237C0F64ULL, 0x3A12535DEADA97FCULL, 0x2AE5CF1D0DFC5227ULL, 0x3FCF2D3A363393D3ULL, 
            0xC4848788ABFF4900ULL, 0x2D58B320B6371BA8ULL, 0x3647AF4E7A9E5BA5ULL, 0x680E9605132C9240ULL, 
            0x642878D6CFCE2461ULL, 0xC85C26A1E6FD6F1BULL, 0x1A765B78615DBC92ULL, 0x7CA290550A08B281ULL
        },
        {
            0xE01D684D8B62C07CULL, 0xC986E46C851694AFULL, 0xFA2C7C8E6716C48BULL, 0xF62CFFC0146585A3ULL, 
            0xA77C9F14B25FEBACULL, 0x9FB40C5A5B95BFEDULL, 0x18502064B9A20E1FULL, 0xD63CE361B6B0726DULL, 
            0xC75521983271FA02ULL, 0x8FEA0E750FDE787BULL, 0xEB25290FDD160AB1ULL, 0x50BE6D5D131BCDBBULL, 
            0x4F87B6EB8940216DULL, 0x37E63F49371B8E12ULL, 0xD021280ACD913C8CULL, 0x218DB423DB9DDD22ULL, 
            0x28F2B2DF0721907BULL, 0x09E11D89C1232611ULL, 0x15AE6EF905CDFE14ULL, 0xEC260386836F224BULL, 
            0x5EE75176A48CC2F9ULL, 0x477485732E0F8E2BULL, 0xFA81DC9F23C4159BULL, 0xAC74EA20DD0CE43AULL, 
            0xF519D5C0470152ADULL, 0x5190D46D7BFC9CB7ULL, 0xB170C0804B559445ULL, 0xE8CBC3B8B9E4CA21ULL, 
            0xD904E0BD695E14C5ULL, 0x507C9A4166A7F042ULL, 0x91B5E359F0E699F4ULL, 0xB37733746FEBAB59ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseAConstants = {
    0x681A9A63F7274E63ULL,
    0x047E073ABA81A1ECULL,
    0x795C658E5E213096ULL,
    0x681A9A63F7274E63ULL,
    0x047E073ABA81A1ECULL,
    0x795C658E5E213096ULL,
    0x47098BDAA39826A1ULL,
    0x05245362AEBEAB20ULL,
    0xF9,
    0xB4,
    0xE4,
    0x4E,
    0xEB,
    0xCA,
    0x4A,
    0x57
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseBSalts = {
    {
        {
            0x7518C0311FFF37F9ULL, 0x2011B97BC73F0C29ULL, 0xB1C8523095B6D9AEULL, 0xFAD517C5EA0CA7EBULL, 
            0xEA34F91F4D139554ULL, 0x8BD7E30CB8B1E8BFULL, 0x926F92ED2262521CULL, 0x3CC8162F59E06E98ULL, 
            0xDB437A0D8E7BC38AULL, 0x7ECEA794178A0A46ULL, 0x598FA1E1B54622AEULL, 0xA64042B4961B398BULL, 
            0x05128702E099576DULL, 0xBF48F0622BE55C27ULL, 0xB456D81A763AF286ULL, 0xA7F91BCA23FFFDFBULL, 
            0x2C7889FB23DA79B9ULL, 0x2FEB8A438F1E53FFULL, 0x078D8BE0DB78A199ULL, 0xAA0468E40E358DACULL, 
            0x34693A426F3C518EULL, 0x37C11CA5637B738BULL, 0x430501452774B4FFULL, 0x76B57C6494BBB172ULL, 
            0x3A4E5C1CED6DCD03ULL, 0x8DD13417D5C90601ULL, 0x2A25DA4F991ADF6BULL, 0x32A14F287A635D81ULL, 
            0x2AA0DD33CFEBEA1DULL, 0x1ADD0A65B55716A2ULL, 0x081A0342F2359792ULL, 0x08D3F7644554D039ULL
        },
        {
            0xEA97FAA7A1DD1FF2ULL, 0x9573364AE49E548FULL, 0xD0BCCDCC5432C5B3ULL, 0xEAAE2B20177A02E9ULL, 
            0xE2FC00AF3D977E25ULL, 0x6EF93120400830A4ULL, 0x6AAFBA118D111ED4ULL, 0xEB5B2947DD856373ULL, 
            0x931D7B6C98BB1135ULL, 0xBE1339653EBF49EFULL, 0xC5788F3522355F51ULL, 0x79FEB3FB8673C855ULL, 
            0x47FF872B486C848CULL, 0xF85DD22FF7EBD334ULL, 0x947D9B12E849F6FFULL, 0xF39EB93B38F9B39BULL, 
            0x31C39FA9A57535C1ULL, 0xA7EE7BFDE04B3B9EULL, 0x1BD46D041734DACFULL, 0xC8F88440804A31C2ULL, 
            0x06C5FF37147F68B3ULL, 0xAD6334A5CB281F60ULL, 0xED69ED302020D9FEULL, 0x95E8D3C2DF556688ULL, 
            0x9E203E5109D5B01CULL, 0xD62B73E19CBAE5E4ULL, 0x9519A799C3B9C8B1ULL, 0xF83528BB31CB8466ULL, 
            0xFA3B969D0D792B44ULL, 0xA88624C4B525A575ULL, 0xAC95A8E76497EB96ULL, 0xCA0C60219C6DEDA7ULL
        },
        {
            0x3C71BBA233D8C429ULL, 0x457A91714DEC90E7ULL, 0xB4F1B0AFBF8371CAULL, 0x64648CFCC284CEBBULL, 
            0x1544FE8183C4B6FDULL, 0xDA676F60A71CA486ULL, 0x8D745C983F7364A8ULL, 0x9D4B9BC03947AB55ULL, 
            0xE2ADC1E92EEBD5ECULL, 0xEB4498DFE09AB1FBULL, 0xFE497FDFB9896061ULL, 0xC3BAE7E731C7C282ULL, 
            0xB3EA0652D80C97EFULL, 0xC095FED07849356DULL, 0x2EF3DE105ECACF1DULL, 0x5EB4D7D779EADE09ULL, 
            0xA3B0CA86D26686CEULL, 0x6EB7C4CAFB2CE320ULL, 0x8CF3DD1FA3C88B2BULL, 0x468B3E7D1941EC0BULL, 
            0x3393ACE6FE33840FULL, 0x42A262FA102E8C31ULL, 0x7E9E4B7410E87637ULL, 0xB778D82078953E88ULL, 
            0x646528BDD4DB5D0AULL, 0x70F1E2C50BBA4674ULL, 0xC681F5DDB8F6F742ULL, 0xD2E0678195FC36A4ULL, 
            0xDBECA2AEC8EA25ECULL, 0x44ADA094B252B0E6ULL, 0xE48BB63A05D81DA4ULL, 0xD243C4EC22AF1337ULL
        },
        {
            0x9E3A12BF3D5C96DBULL, 0x34CFA3865BA48C0CULL, 0x80D1BB1C37E1C13CULL, 0x8F6E280744CC586AULL, 
            0x8FEE04F35A347A5FULL, 0x5945D15D3E13D86BULL, 0x4597AD662E8B0DCDULL, 0x900F9F1B004BE7F9ULL, 
            0x98E4368179330676ULL, 0xA31956B87789C4D3ULL, 0xEF4A1884DA207C5AULL, 0x6945E5A36237A3C9ULL, 
            0x56E2BA26145A3699ULL, 0xE87CC6D016D90A42ULL, 0x07B4819D89023697ULL, 0xFC7D4165EF3347F7ULL, 
            0x3F1C66F966496F0DULL, 0xC53222B5DE745F4CULL, 0x02FF28C65CD77E96ULL, 0x79876509E6263DBDULL, 
            0x18E54DEE879D6553ULL, 0xCDC12052E98CBC8CULL, 0x219FD0523AF923A5ULL, 0xBBD25C27F5E24850ULL, 
            0xFBFA318C73F80614ULL, 0xDE5C486D9EAC7786ULL, 0xD30B4C6B7C948161ULL, 0xF029A3E37031D29DULL, 
            0xEF974EC59186F4A9ULL, 0x454C207036A374CAULL, 0xB7E7709742F3CBC7ULL, 0x52AE569C0CC4376AULL
        },
        {
            0x82FEEC40909915ADULL, 0x0989D91421918D35ULL, 0xD6FF051C96649BBDULL, 0x970799B1133A3D08ULL, 
            0xA15474028167AE01ULL, 0x743C98927D641AD8ULL, 0x0C83D18D71960F8FULL, 0xC3FCC48C6F1BA362ULL, 
            0x8C9D863FDEC88E65ULL, 0xC1291C91FB1843EBULL, 0x8D101D0773D0BC29ULL, 0x40BE2FE91E0B3423ULL, 
            0xA2A5A7A6A361583CULL, 0x9636C4729586E5E0ULL, 0x5C5B0C2D62201F72ULL, 0x2416F3BD1F1A2336ULL, 
            0xB10EE6F101BD34C6ULL, 0xE1F7941AB0064C04ULL, 0x20E9C0A4345D7BDFULL, 0xCB2B50E5A344DA88ULL, 
            0x24A1957470695115ULL, 0xA09D5D928E6A1373ULL, 0x95147C1C685FB7EFULL, 0xA9504401D5F2B1B5ULL, 
            0x678A0FAE7C523510ULL, 0xD206E424AAB619CEULL, 0x55E75A9B8F695E41ULL, 0x82EAAFB5B7584788ULL, 
            0x2713F4FD42458FDCULL, 0x3D5288D7EFBE29DBULL, 0x7482887A38AC154CULL, 0xF333BA3F7A5C239BULL
        },
        {
            0xA3536ABA527EA1C9ULL, 0xF18B494F2118AC6BULL, 0x46AF8EDB83C9B46EULL, 0x4A5E244FABE00CA5ULL, 
            0x33F324C191AC532EULL, 0xEF9A2D92CF55D63CULL, 0x5C479448A268D4A2ULL, 0x32DE21464723104DULL, 
            0xF1FB25301D44E3D7ULL, 0x56B540A0E8D1FBE8ULL, 0x0666248DCB4453B3ULL, 0x47AF2D3BD46F502FULL, 
            0xF2BDCD53B41EBA40ULL, 0x20179FB88A9BA3CFULL, 0xA46963844AD71E98ULL, 0xE65BE6B4B4DB8E4FULL, 
            0xC73911E62A5BE11EULL, 0xC7C39AEBC80C483BULL, 0x674532AF8B5348F0ULL, 0xAE5D6E8137448EAFULL, 
            0xFB63BBF9BB328B13ULL, 0x35CDB1FFDCFE2781ULL, 0xCA2C6053EDAD911FULL, 0x46FBF85602A3AFC1ULL, 
            0x6D67C2A72B2E8BFFULL, 0x8438F4BEE30E77BFULL, 0x7724627007BF73D1ULL, 0x2F1CCFBBF4E2EDECULL, 
            0x8A5A6210981B40E1ULL, 0xAD690ECA14D49AECULL, 0x2BCFDCFF0AE6418BULL, 0x2294FBB4B7745BDFULL
        }
    },
    {
        {
            0x7932F0BEEE7F1569ULL, 0x1963B65E35731A47ULL, 0x39087641A8CBC89AULL, 0x3B08A22AD68CBA16ULL, 
            0xAC114E8E1AE3EDC4ULL, 0x63754CC0271840F8ULL, 0x5D92B043A44678D5ULL, 0x546B2A7874560550ULL, 
            0x9F52AF0FABF7DD6DULL, 0xAA64A13F0BA9447DULL, 0x4FE8D7E18B376827ULL, 0x8CF4319CD4EA96F6ULL, 
            0xC1DB617961FE8240ULL, 0xCD81CB44C463500FULL, 0x0C68EFE3CFD735E0ULL, 0xFFC55A379D7C26DBULL, 
            0x2ADB9620EA076476ULL, 0x36AA1F9C201A1893ULL, 0xCA52F0F2DD5A0DE5ULL, 0x7028291E2E4D78CBULL, 
            0x2426D670F2EDBFF1ULL, 0x8C28DE6182A44FFCULL, 0x3B27B06971EC053BULL, 0xB96D1BAB20F10316ULL, 
            0xFB645783E04736BEULL, 0x2BCE3E83B750B700ULL, 0x1EE44996D0DC7AE3ULL, 0x69F408D88ADB5697ULL, 
            0xC268007A1E36BC31ULL, 0x34BD3AB3005628ABULL, 0x3E6D25EA11AAA93EULL, 0x5DA2756FBC28F154ULL
        },
        {
            0x85CF8B74801F0FB0ULL, 0x6E790A88A62572B8ULL, 0x17785F1769739188ULL, 0x06A3DCF77B16C14CULL, 
            0x9BC8723BC0AC6BD2ULL, 0xECF22A9E88690115ULL, 0x9DA678040062328EULL, 0x7152B77CFF187600ULL, 
            0x2DF922B15D3C8740ULL, 0x5D696499DEB302FDULL, 0x7437E619F12A114BULL, 0xE5F48CDFCD034FFEULL, 
            0x9789FBD780819598ULL, 0x6768D310D9A60E5EULL, 0xFF56ED084D1D72BFULL, 0x167476220AFCD1E8ULL, 
            0x747707CCD06D550AULL, 0xFCB0D3507E60BFEEULL, 0xABCD7D52549D624AULL, 0x6E1C91BFD43A03A9ULL, 
            0x64AE90AADE3B82B8ULL, 0x1D9B4A2B2BF4C0D1ULL, 0x021CD66370480C8EULL, 0xE0DC03E0CE13EC9EULL, 
            0x94A46A05F38463FFULL, 0x7FE7CEF1DE3D42A9ULL, 0x77BFF474D36CD942ULL, 0x2D9CF2E83765976EULL, 
            0x2C88F6D6F8BE35AEULL, 0xCF0D3CC0064D6579ULL, 0xE76C9D046199FD71ULL, 0x336ED63EDEBC07C3ULL
        },
        {
            0xFDB5C7CD1DE3A430ULL, 0xC9DA9ACE776D937AULL, 0x96DAA16C7BC9211CULL, 0x70242A5F28EDA441ULL, 
            0x124AA2C10EC5EF78ULL, 0x29C3B3715C6FD64FULL, 0x8EA32C8A8453359DULL, 0xFDFB6FAE18B35F64ULL, 
            0x5819B1E30237114DULL, 0x1E60FC4205E9C58FULL, 0xFA27E50A984DBC18ULL, 0x50DE71429DF6D61EULL, 
            0x11EB024AB19269DDULL, 0xC8BB3CF245C12DFBULL, 0x0C6BC67FA6939CF1ULL, 0x091162C5B4A3CF14ULL, 
            0xA03F623941957433ULL, 0x1EBD5A1151CEEC71ULL, 0xC2054D9EFCD843B8ULL, 0x088BEC31B55E85F2ULL, 
            0x2CC1F30B7FDEAC70ULL, 0xD2E670C5E1FDBEF6ULL, 0x4A4EAC03420DBD8BULL, 0xAE064452334C1B74ULL, 
            0x08A6C04B5A0237A5ULL, 0x7ED438F906CE3C85ULL, 0x0B6602A28988EA18ULL, 0xF6DEAF905F41F4ABULL, 
            0xBD1E0849B375BB44ULL, 0xDB7BE5F56549B8F9ULL, 0xFFCBDAC171C60440ULL, 0xEDFF6A0C79FA5D39ULL
        },
        {
            0x4940C2B9E5193E7BULL, 0x2782B79FCE015A80ULL, 0xD6DEE612F5855A95ULL, 0x4C70F3B63CEA757BULL, 
            0x526673FC75AE04DCULL, 0xBCD2CB911EA0FBCDULL, 0xED0F75D5B92DDE94ULL, 0x9911BCF5BDBF1880ULL, 
            0x3CD973D9C9B106AEULL, 0x75DC522077DBDC4BULL, 0x9785FAB3F55000FCULL, 0x1A108B02371F867FULL, 
            0x73243EA12AFC43E0ULL, 0x4C20D0CFAF74DC30ULL, 0xBDAEFC26674B9E36ULL, 0x74C8E6A976A3FF87ULL, 
            0xA210DD34F5B68193ULL, 0x5D8A25AC7609F7CCULL, 0x15AB962AF4706A80ULL, 0x85F25219CA011FF9ULL, 
            0x58E40264E8030C24ULL, 0xD65BD91E6AA9ED0CULL, 0x7A2675C03BE89B90ULL, 0xD5C237639CB6FF50ULL, 
            0x5933E75B39E0B782ULL, 0xB8A8BCA1CD83F187ULL, 0x18344EDC44450C9BULL, 0x4B09DBF8FBEE9097ULL, 
            0x53543E812CFA6831ULL, 0x0101FC42237D1CF3ULL, 0x0C132EEFA30CCD73ULL, 0x3F724C7552D6875AULL
        },
        {
            0x8A3D373149D2B569ULL, 0x7ECF560C972DF731ULL, 0xDBF72A0B371D0268ULL, 0x30A0362AD694D110ULL, 
            0x3D01176D4ADB4D87ULL, 0xEC2F14E08578298CULL, 0x36D930D559F0D77CULL, 0x3303B967510BFD21ULL, 
            0xF3ACFF0321E4785FULL, 0xDD13CF087FB46623ULL, 0x049BBCFAB8E0A5BCULL, 0xA2987B94DDCD48EFULL, 
            0x6ECD05BAD710062CULL, 0x387AF077290CD98AULL, 0xAA4B1EC4774B375AULL, 0x7D6FAC9A7A7A820FULL, 
            0x6A62A5A466396C8EULL, 0x1227A6F4B7CEEF58ULL, 0xC1951B3F62545861ULL, 0x0D67C0F3B07FF54FULL, 
            0xD2791BD96049CA27ULL, 0x06ACEE3C7D40F61CULL, 0xBA4ECD6520F69168ULL, 0xA63B7ECC5C6D1263ULL, 
            0x02FA347EAA2A17E8ULL, 0x2883DD317C749CF2ULL, 0x6A9B352AAA241B4EULL, 0x6470FAED0538F23AULL, 
            0x59B02726DC2BAF9FULL, 0x9064D5695337C399ULL, 0xDC3E80BFA9E7988DULL, 0xFF1EB6E4599CAC98ULL
        },
        {
            0x1551F48DBFF884B1ULL, 0x548BD5653E3329B7ULL, 0xE3170C7806C86B47ULL, 0x7B94ED7829988450ULL, 
            0x4DF20D14334A89DCULL, 0xB715A97962E204B4ULL, 0xB1DDC8EBF556EEDAULL, 0x8E06680B9049BEF5ULL, 
            0x5E63816D67470D22ULL, 0xA01DF5FADB2DE267ULL, 0x7502E67349F8F1A7ULL, 0xEC40A2737D6F76B2ULL, 
            0x0FEBFED7E1959916ULL, 0x08B612D0F0F0820AULL, 0x43CEE169F029E2F2ULL, 0xE26C67C6CB2151F0ULL, 
            0x0218F8E8227771B3ULL, 0xD916DD8E4684E0AEULL, 0x025EF1678C692BD6ULL, 0x190BE9C7C328A28FULL, 
            0x9D73408BFBA30DCFULL, 0xE552A20AC8DB8069ULL, 0x5F75D57C7966ED10ULL, 0xD3700FA529128F24ULL, 
            0x23368A96CB5DFCEEULL, 0x75E442D25C6C095AULL, 0xD58C43493B86BA88ULL, 0xB0173F09D9A12DB8ULL, 
            0x66ECB203A74040D8ULL, 0x1AB80032B0AB8602ULL, 0x916E5C3619818457ULL, 0x391F26DC9FFE5755ULL
        }
    },
    {
        {
            0x9B4C6DFF74268359ULL, 0x9F2002AD0BD26406ULL, 0xEAAAF30067C4E8BFULL, 0xAE759E37DF20E528ULL, 
            0x07E720CA9775FED3ULL, 0x0104E74574E73F86ULL, 0x453F07C0A4AA7E36ULL, 0x958DBBB4339C7CD5ULL, 
            0x849A25D9990A0079ULL, 0x29BF7E795FD4A66BULL, 0xB66CD9364BD30A3BULL, 0x8553963F5F72B39BULL, 
            0xC6CBC4FBBFCBD9C9ULL, 0xBAC45A3C0D88451FULL, 0x883D826FDF306B39ULL, 0x7BEF7D78497A4A91ULL, 
            0xF88F6B1223FA0AE0ULL, 0x570E92F8E2B0EEE2ULL, 0xF83C461A4CBACD71ULL, 0xB399A17ECE7EE693ULL, 
            0x5E6831D962F27F60ULL, 0x476659B2BEF5BF42ULL, 0x1ECC8F680E97B945ULL, 0x0F3A79A75F948694ULL, 
            0x1182575FF84E0F49ULL, 0x9B41B62AFF52D0FBULL, 0xED04039AAF1E42D9ULL, 0x9723062C0942CA32ULL, 
            0x760E004EE7D031F8ULL, 0x2DC854315DB1A7DBULL, 0xF24EE5B06310CEEEULL, 0x05046A3C8BA66AC7ULL
        },
        {
            0x59113D3B8C8BA98BULL, 0x29D200B915D7CB79ULL, 0x8108B81495A31976ULL, 0xE27A4378E7DF0655ULL, 
            0x868BE24E4CA2B99EULL, 0x5DAEE8730D938CB5ULL, 0x69691576AEDE5AE8ULL, 0xB4AE4ADE32E7DFDCULL, 
            0xF1E04B378200F24BULL, 0x95DD9FDE6906EBC5ULL, 0x27E00CDBC70DE9C2ULL, 0xFCFCF609B0416A7EULL, 
            0x9A1C8D1AE2AD812CULL, 0x2AF7C2A0A4A443F6ULL, 0x4AC3EF5B733B08B9ULL, 0x2AA0D7F7DDC8EB07ULL, 
            0x332F55030FE2153FULL, 0x4A03B62A39306836ULL, 0x9B9CE469D484EA35ULL, 0xADB120A3ABB0B458ULL, 
            0x495A1D2CBA9605FAULL, 0xB780C706B8E231A1ULL, 0xE1F46E099784A162ULL, 0x4F4B33E4B81590BCULL, 
            0x24FF9E2713F083D0ULL, 0x01E311419C3092B4ULL, 0xE28A83782ADA24E1ULL, 0x0005F83AA7AF9133ULL, 
            0x483D9DC1DFF4EDDEULL, 0x97BF64751553D7BDULL, 0x1A48C41AD3BA5850ULL, 0x48C33B886F2D267AULL
        },
        {
            0x4A93BB9B8E472E1DULL, 0x64427B242B91E0BBULL, 0xE39A6B50B6DC6181ULL, 0x724FA3A1422A77CCULL, 
            0x30A78D356B427E72ULL, 0x3F8148CB04CFB571ULL, 0xCACE476BD8585831ULL, 0x22FE4D14B73BF566ULL, 
            0x657433EF57B7D311ULL, 0x0B529DC6096EEDF9ULL, 0x9D072E37378B776DULL, 0xAFB476FB0C3A4333ULL, 
            0x92827ACE1641386DULL, 0x486B1AE4AD4DB889ULL, 0x4C474E22560CC5A8ULL, 0x88D33E196C9C5879ULL, 
            0xB4056E8EA015EE93ULL, 0x5A1C7DC33B534A0DULL, 0x63A8B9DF07E1DE8CULL, 0x61AD4615B63060DAULL, 
            0xBFD6B5E5F31BBD3BULL, 0x2C4E66723E4BB555ULL, 0x158F83BE82C22A85ULL, 0xB45E2D2DDB8BB45EULL, 
            0xBAC920ECB4855984ULL, 0x0334593DC8912EC3ULL, 0x6089923CC28D0244ULL, 0x28B2F34F5CE8BFF6ULL, 
            0xBB210B35989A2DFDULL, 0x028F193AA4CEB24EULL, 0xCC73CC96940D6B9AULL, 0x018D4F7D8DCE394AULL
        },
        {
            0x4C57BF1BDDDED21BULL, 0x772A47D075E1B66AULL, 0x1FD7F52F4E5DB2F2ULL, 0xB20251F74F315327ULL, 
            0x675FB8F09EC9CCAEULL, 0x7346D6BC4954C02EULL, 0xEEA473E58B7656D5ULL, 0xDCB319B9E402A90DULL, 
            0x04F60AF1A4F278F1ULL, 0xCF766FC8B44F54CBULL, 0x209D1196DAAEBFA9ULL, 0x425C4E9C9F5C127EULL, 
            0x972363756E0A8456ULL, 0x9DABAE69DE1988DDULL, 0xEDD78ECE24682BBFULL, 0x1A42A6EB065D5E6DULL, 
            0xE6873B67576E6E24ULL, 0xA26A5D319A9321EFULL, 0xE5CB6C46D3E4BF3FULL, 0x9E6C13435C5EA315ULL, 
            0x91E859605D857A74ULL, 0xE9057C6ACE3207DBULL, 0x08833D1D7E98EEB9ULL, 0x78A5D6C9A26CB079ULL, 
            0x538D17602862A3DFULL, 0x80403E242417BCA7ULL, 0xAC7D5E87F22625FBULL, 0x215392E1E4797B0DULL, 
            0x52ECAD281239599DULL, 0x420EFB8F7023CCE0ULL, 0x5AFCED18B3557180ULL, 0xF96134685EB8918CULL
        },
        {
            0x22F2ABE0047CC3EAULL, 0x1DEE60D8FBD147B2ULL, 0xC2669A186D935FC0ULL, 0x3456341905BAACAEULL, 
            0x512B43875FD0EA24ULL, 0x42B01C50A447AE75ULL, 0x95D24DB1625580CCULL, 0x048BD5456C86E4D7ULL, 
            0x18072DE9D81BB672ULL, 0x716C5F763D3D9A9EULL, 0x0A079C2E9575B836ULL, 0xC5804E1A77ADD1D6ULL, 
            0xFBC8BF80F24062CCULL, 0xC5B4DE742902D5F8ULL, 0xF0DDD8ECAB223A15ULL, 0xDC0A1504225E84E0ULL, 
            0xAE3DC1071F4FBB48ULL, 0x270295E243E2BBB0ULL, 0xCCC6ACD80D8B22DBULL, 0x1E49E010941572B1ULL, 
            0xB7D25B5E13260BBFULL, 0x689E7071858CF4B8ULL, 0xBB7A943FFCD60CC0ULL, 0xCCA41AE20E4A7169ULL, 
            0x511869AE8B605A6CULL, 0x14E56F84270EFA5BULL, 0x6525F05905A9F2EEULL, 0xD14D7B8EFB4FECFDULL, 
            0xC4204AC6699C1AB6ULL, 0x96D61C52894C38E8ULL, 0xCDEFB4A1D3745910ULL, 0xEC3F21103E5323FDULL
        },
        {
            0x7DFA04B58287BE58ULL, 0x7824646F20ABC9B7ULL, 0x774525954B717C97ULL, 0x8D331FF75C4832FEULL, 
            0xB997BA26785B62FBULL, 0xDBBF6F8E2C667049ULL, 0xB0CDD44EF87FD3BAULL, 0x59D355F79333C6A8ULL, 
            0x2F4638A9A3D3C63BULL, 0xF7B043454F511FA5ULL, 0xED3F985CF704C197ULL, 0xA7AEAB63F216721EULL, 
            0xCF936C26EBE9B717ULL, 0xB1E75319A4797D59ULL, 0xBD3687758953E8E5ULL, 0x07069CC067C4956BULL, 
            0x204250A8C1D9EA35ULL, 0xBE4729EA45DBC668ULL, 0xBAA5672FE7A5E554ULL, 0x4A2C73C241042FB9ULL, 
            0x894D2FBA4E40D661ULL, 0x639DB45F2950B768ULL, 0x27A6CD8F014034E2ULL, 0x14A286F115EC552DULL, 
            0x5968B65C3C487DB0ULL, 0x751F07D223EB66AFULL, 0x0CBB8333FA5B2EE7ULL, 0x0AE7C2FE7107A7CEULL, 
            0x27D60D5E9D04DC23ULL, 0x8B3668E6F23CE7C6ULL, 0x9B12039CB4728F92ULL, 0xF309009DE050AEAFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseBConstants = {
    0x466CE85D1CFB30C6ULL,
    0x6CF644862D3C6305ULL,
    0x9C878399BFE7F667ULL,
    0x466CE85D1CFB30C6ULL,
    0x6CF644862D3C6305ULL,
    0x9C878399BFE7F667ULL,
    0x9EE928D988C6C1CAULL,
    0xD18FF35F55E6552CULL,
    0xEB,
    0xE0,
    0x8D,
    0xF7,
    0x60,
    0x8A,
    0x16,
    0x2B
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseCSalts = {
    {
        {
            0xF1C2AC6D38E81E74ULL, 0x4290275F68E41456ULL, 0xF200BA61AF4C7FBDULL, 0x86D6172922F9505BULL, 
            0xD0E153FAD07F43BDULL, 0x3ED46FCF454DA896ULL, 0xA27FD46A02FDB08AULL, 0xA5E6E0D6472A30DAULL, 
            0x394C1640AC4B0159ULL, 0xDE9080F1572A8802ULL, 0x7239E705E7ED6E49ULL, 0xEDFBF075172611ADULL, 
            0x4EFAACD1079E48F6ULL, 0x57CBF6F2E3DBCF93ULL, 0x055773F4131480C2ULL, 0x7EB6EF95632F2B09ULL, 
            0x5B00F0BDCFF4B88EULL, 0xC0CC738C2579402DULL, 0x180784E553772C18ULL, 0x7AB47273A48F97E4ULL, 
            0x829122E3B4D69AA4ULL, 0xFDCA757F3E74BC8FULL, 0xD5F9479D14C6404CULL, 0x0D80A10E85569B34ULL, 
            0xDAFC5322D05F80C6ULL, 0xB6B149248315E75FULL, 0x0EB85F0923216986ULL, 0x75D34C32FBAD55C0ULL, 
            0x936BEA42B3B5149AULL, 0xF6C674CB89C633C1ULL, 0xD7FC84AD61EE8372ULL, 0x0A34AD6208AA8D73ULL
        },
        {
            0xAC0F4E5D9A708CC9ULL, 0x2C1E24E2E85B0CB5ULL, 0xDA3ED0AB212A7E46ULL, 0xC2198293C265F370ULL, 
            0x164BA7744BC1594EULL, 0x93513A510A24EBBEULL, 0x7CFEC03A7AEF8208ULL, 0x6E9B50CF2FB66394ULL, 
            0x6DD547029E06BB35ULL, 0x64C75592A035FDDCULL, 0xE62EEFC2B6B0E1E2ULL, 0x1E8719F0F67A9F12ULL, 
            0x77F62F7DAF6E570EULL, 0x68E150A05A1661DEULL, 0x83A16A07831AAD60ULL, 0xF15763307B70C377ULL, 
            0xE4528EE77ACF1FE7ULL, 0x3D94FD638D888685ULL, 0xB380ED939F05EAC0ULL, 0x05AC7BD0A8F064DBULL, 
            0xF00D2D30073F0526ULL, 0xFCDB97E84D7D778BULL, 0x4C4603577A032EC8ULL, 0x7BBC6FC6EB175181ULL, 
            0xA01D0867C6D7C4F0ULL, 0x8C9FC0546DCA4D6DULL, 0x3A6409140A370EFDULL, 0xE70F1578D220B0B6ULL, 
            0x7A93BEB91185E0B7ULL, 0x061376EE8237EAACULL, 0x679FACC5189207E3ULL, 0x6A5DD2495CA9B698ULL
        },
        {
            0xF064C861ED24898EULL, 0xBE3342F0560E01EDULL, 0xABEF86F2EF9EA2C7ULL, 0x0275E7234D4D3BF4ULL, 
            0xDAA640782FB532D9ULL, 0x8B1C938B1BAECF62ULL, 0x4C1A5D49A03829DCULL, 0x2D17599C913E1B4BULL, 
            0xDEE9B51E9639AD11ULL, 0x07FA0D4F4375AD8EULL, 0xCF989E709AFC9B23ULL, 0x8EA1AACDA26A6381ULL, 
            0xB8E10FB6E83A5839ULL, 0x7F3CBF9F76F5D5B6ULL, 0xE7996CF8EDE608BFULL, 0x1D202918D211E0F4ULL, 
            0x69956E470231FD77ULL, 0x9C04BA362A94017FULL, 0xF1753FB7CB8E58CEULL, 0xE4C80589BA74D946ULL, 
            0xE3B3EF7278CED76DULL, 0x28111F734A178E0FULL, 0x61E6B18DD29FF519ULL, 0x690E2A91A7BE8FFDULL, 
            0x62B24B66F8C16447ULL, 0x2D6EB4CB4D1D4B76ULL, 0x6B9540D4FD3F6541ULL, 0xE14DE51D218CE6F7ULL, 
            0x12DE777217C10593ULL, 0x0AE647A3AB712B02ULL, 0x8546A4C2AB4D1E68ULL, 0x16C3C581C3445681ULL
        },
        {
            0xAD4C90A49BDCDABCULL, 0x2E8AE9A04B36155AULL, 0x552034A115C6153CULL, 0x61353808D30DA0F8ULL, 
            0x7DB528335EE2C882ULL, 0x6ED4C58D476E0B76ULL, 0xCC6D3EFA5215E7A6ULL, 0x17E4862900713795ULL, 
            0x2AC1B4FDE7C6E2C0ULL, 0xAE7A00696530F2E8ULL, 0x4A5FB05CA826665DULL, 0x2E7B61CF48BF812EULL, 
            0x2D73437DAD619FC1ULL, 0x277FD7C9728BB8F8ULL, 0x8D9CB5CA33E33480ULL, 0x49BC8CD711E16AC2ULL, 
            0xA3F4E32A1DD1532EULL, 0x78DF7B602DE98B16ULL, 0x004464894CE5D318ULL, 0xED5CE570F907504FULL, 
            0x6B1EB1A3CD2AAC48ULL, 0x4152468B8526DAEFULL, 0x28F4B7FF4B556AC3ULL, 0xE364927922ACC0D5ULL, 
            0x47C98197CC3A987DULL, 0x3452943D0E2F2C66ULL, 0xD30461E8D5C307F9ULL, 0xB93273BA99BCCB3DULL, 
            0x653247A119AD4C20ULL, 0x67E2A2744EAB4D72ULL, 0xF0A950EAB49E7BD6ULL, 0x4337D46931FD5317ULL
        },
        {
            0x0C8535EC57FB772AULL, 0x732B384779257FC3ULL, 0x90AC983FEF5E0F9CULL, 0xE7476BAEFFAEE6D5ULL, 
            0xFE5CB7423CF8AB8DULL, 0x511DC66712027C50ULL, 0x4020D82B3435624CULL, 0xCE09912783878AFDULL, 
            0x4739AB4C164F93F4ULL, 0xCB34F1EF97FD79FCULL, 0xA65C009B30D06952ULL, 0xC0F3B2AD39FCCBCFULL, 
            0xCEB6C6D0DAF1049FULL, 0x71B0995065CF83BCULL, 0xCEACCF607B1768E9ULL, 0xFE1397750CBE8184ULL, 
            0x9B94B36B8475F917ULL, 0x2525E8A522572148ULL, 0xA6150E619E09385DULL, 0x042894316B749F92ULL, 
            0x533FF1C7AB6EDEDEULL, 0xF1C44F5003B68C29ULL, 0xDD61A55DFE5DA6ADULL, 0x78CADCC6C9A3BA22ULL, 
            0x507458C037A98DABULL, 0x9039CDDC9534D708ULL, 0x5EE03AD577C986E1ULL, 0x0778EBFAD746153FULL, 
            0xF58D5B8C4607B7AAULL, 0x5376E4C2EF330129ULL, 0x4DE5D77CEBFFF4C6ULL, 0x7DE3B97AF7453F4DULL
        },
        {
            0x4F52C347B609CDDCULL, 0x404E3BB2EBB6B2FFULL, 0x967AE24C722286C2ULL, 0x7DE0C7235A367B5FULL, 
            0x40DADBC88935A10CULL, 0x39366F148B4915E8ULL, 0x1D62F64C5AB99073ULL, 0x602211EC73D07A87ULL, 
            0x009653D9E0ABDC43ULL, 0x9C1D67118958C2A7ULL, 0x4112F5667C73CB6CULL, 0x160DCC3D8D82C6FDULL, 
            0x8DE6E2EC44E64114ULL, 0xDDC80B4154B71925ULL, 0x2C06B3594CAAB48EULL, 0x386349D14B742842ULL, 
            0x6AF6E69CFD0E5960ULL, 0x6F28A89E37C39939ULL, 0xCA34FE3B6C38F1CCULL, 0xCEFF2BBD4ECF934FULL, 
            0x1AFB72675FF47E27ULL, 0xC61DE4D8D77FB93CULL, 0x16BCEAFBA87FC36FULL, 0x7494825E856FBAB6ULL, 
            0xA87544A3337F2EA9ULL, 0x16F5DC39F9D0D90CULL, 0xBF1A1065B183D104ULL, 0xE003FAB31F67D4CDULL, 
            0x6AA0204A50527B79ULL, 0x0A1871274C4305F6ULL, 0xE2DAC545575E23A4ULL, 0xE433F84DF3BE5B96ULL
        }
    },
    {
        {
            0x8CB0582A00136F7BULL, 0x095E50EFC0168DEBULL, 0xEA16E947FA212ED6ULL, 0x63766E4865C43DA1ULL, 
            0xC1357248E8CFA6BCULL, 0x059548FC6F47B872ULL, 0x3814C844A5DE5045ULL, 0x6B1B38676CD31645ULL, 
            0x04EA53F01A3B9574ULL, 0x5B9FA32F94C5F84AULL, 0x24FDFFF2E4CC4EF9ULL, 0x90CBA46E81A96F07ULL, 
            0x6FBA26AF87DFED83ULL, 0x8956AB6F5E83C622ULL, 0xBA584959ACB7E120ULL, 0x9C277E33A929025DULL, 
            0x4BB30E7CE2735F76ULL, 0x4920071977C53B08ULL, 0xFF7FE4E466A0EFE3ULL, 0x3DCA5522D65CFB81ULL, 
            0xF89655DD4CD7D2CFULL, 0xD97AF99BE8D97AF8ULL, 0x32F32D00F2EBFC26ULL, 0xA73238F2A145077FULL, 
            0x2DF54F291F11C612ULL, 0xED59222DF2C8803AULL, 0x61AB7E146096FF74ULL, 0xC2E886B6FB668E8EULL, 
            0x44B2CE6232CB1D77ULL, 0x9C340F35B0C36807ULL, 0xC1A44FC4DAD15A67ULL, 0x47DE813511196284ULL
        },
        {
            0xE28E4D0CA6468F3CULL, 0x356E0262ACEC9527ULL, 0x55412E9FE41AD516ULL, 0xEF27846D25F0D6E3ULL, 
            0x575D6B19AD5DDC6BULL, 0x55C8EAD4B0D967D0ULL, 0x55C83A4A10C758D2ULL, 0x290BE98233E0929CULL, 
            0xCD04D72DDFA5EEA9ULL, 0x93F7DC5D7D8DF1DCULL, 0x27FC5D55E9D0DD10ULL, 0x4582C7BBA55EF305ULL, 
            0x1B4AF2B758AC6F09ULL, 0xD134077C3B8DB883ULL, 0xDAFE94C882F43C8CULL, 0xEA724713D7688A90ULL, 
            0x30A856AFCAD75385ULL, 0xF97BF98A40F5298EULL, 0xFBA3DC3DA71EE997ULL, 0x9BF8FC7EB7C6D7A8ULL, 
            0x3AB495488A4E52F8ULL, 0x20FAF4408D2778D5ULL, 0xE94A846D939C6B0AULL, 0xA1DEB95061628DAEULL, 
            0x5A3C9D1F86235FB2ULL, 0xEB6071BFE7A72478ULL, 0x2402845E882275AFULL, 0x54F537D62A7C7F0BULL, 
            0x24CEBD09EF3A0660ULL, 0x356504E6BD1FAC9DULL, 0xDAF37EA2B70D16E0ULL, 0x6220768F90607833ULL
        },
        {
            0xF1C025774DAC3041ULL, 0x9B99813959136155ULL, 0xE98300624437876BULL, 0xF5946390E461D0F8ULL, 
            0xD715E0E1925421A6ULL, 0x25E72D0E7A214564ULL, 0x1477DD39D853D750ULL, 0x682D4759A9B124D0ULL, 
            0xEF8367CCE3B242A1ULL, 0x23265C32BC852E94ULL, 0xD1E25E2485F7A8DAULL, 0x71437698B392E7DFULL, 
            0x23D0223DE67749B1ULL, 0xD349D16F9513F439ULL, 0xF8DC98E681F7A9F4ULL, 0xD71CF8CCB907DD90ULL, 
            0x1D811BD43D3CC48FULL, 0xF63B55DFDF294A91ULL, 0x9C5972689BAAE165ULL, 0xA179A40B0B6C56D2ULL, 
            0xBCF9C8B832B07AF1ULL, 0xB1DD5F37486AC6DCULL, 0x1D7E28CE504A30AEULL, 0x1DD827A91DD1A420ULL, 
            0x9C4ACAF8E28C3BF6ULL, 0x88DEC2178DDB7720ULL, 0x4B3DFF8C71063459ULL, 0x6B71F957F0D2E0ABULL, 
            0x282EA7FBC4CDDBE3ULL, 0x507C61F60A2CFA37ULL, 0xB580E7B586D4E547ULL, 0xE849F4D1E64D7919ULL
        },
        {
            0xABC03F05054AF33FULL, 0xDF346C0A379047B7ULL, 0xA19176AFF90CB8F4ULL, 0xEC187A2396371E7AULL, 
            0x9DAAFF99CC6C264CULL, 0xF255E44D4C74F008ULL, 0xFA553BE27F1B7FD8ULL, 0xC4BB8252A059E518ULL, 
            0x83D3836CA995C3E8ULL, 0x31BF027920B14A7EULL, 0x3D1E841B10679E50ULL, 0x1F4C568D82F19A2EULL, 
            0x3AB1F8AEE7B0BA05ULL, 0x3FB98DD934E5E439ULL, 0x7BE885DEDE9FD88EULL, 0x8C3B385014A772ECULL, 
            0xC11111ECC4DDFC39ULL, 0xFDE5D0CCE6317C2BULL, 0x0B956263D02A98C3ULL, 0x1BB6EDC1E8BF943BULL, 
            0xF57E12F5C3EEECB9ULL, 0x61643969BB65FA45ULL, 0x78F9207E5D264EBFULL, 0x1071BB865311ABD5ULL, 
            0xE47443741C83EC2EULL, 0xAEC2C96AD3A98358ULL, 0x609B082CDD4D10ABULL, 0xD38CD19B6EAF9E37ULL, 
            0xB63AE5FEAA3023AFULL, 0xFA57A3DE065336D8ULL, 0x0F3F96A30A8CFA96ULL, 0xC6A60903524A336AULL
        },
        {
            0x04632E57C61A31B8ULL, 0xBF94CD2E83050662ULL, 0x409B0E15846E95C9ULL, 0x2AD285E48FFB7093ULL, 
            0xCCBC09F8DA18FE01ULL, 0x9129A91942A41AD1ULL, 0xFD0CC7E78BB64FF0ULL, 0xDE9699E537183C23ULL, 
            0x5A98F129CF4C77E6ULL, 0x10199DA6D0CC2475ULL, 0x2BF87D68463A25DCULL, 0xF26D0DB8BADE18EAULL, 
            0x9D792C29B429C1D5ULL, 0xC2B51C9BFC500F39ULL, 0xEDD1A211315DF510ULL, 0x9A3DCDB8BFDCFBFFULL, 
            0x8B9F269CC8632492ULL, 0x689391CBD8EBD193ULL, 0xA9D0E1CCAACAD5D8ULL, 0xFCFC63C1F3EA92DAULL, 
            0x90F33FF178140D36ULL, 0xAEA4E40C2FFCD682ULL, 0x5A8993B6BDA6B09BULL, 0x4344F6A2BAA88A8FULL, 
            0x26E6517C23753C2DULL, 0xBC478A3F27C7138EULL, 0x906B28417F222946ULL, 0xA8BC32D45C95AC9EULL, 
            0x99CE22243F36A029ULL, 0x6FBBB26E88B74B29ULL, 0x9D39B7C5807B62EFULL, 0xBA8FB95F7C50B07DULL
        },
        {
            0x49465CBDE331E01CULL, 0x277B2DF7DF5A8BBFULL, 0x5C1779E3D10CFF28ULL, 0x6FD2F48DF3A7C13CULL, 
            0xDC154B88CB47FB6BULL, 0x96FC50B060998B50ULL, 0x6F27CF8024E49CF9ULL, 0xD3953C5D4E68D233ULL, 
            0x25DF32AC350A80C4ULL, 0x18B81D44C80E82EFULL, 0x5AFEC04F887208E3ULL, 0xD63A3B4A20CEB128ULL, 
            0x8DC1CD876B229044ULL, 0x807DC74910C957E5ULL, 0x056D43ED8808EE0CULL, 0xC9407FF2A6554954ULL, 
            0x316CD1C07CEFF437ULL, 0x03C0EDAAF363E9E3ULL, 0x05095FA5576DA468ULL, 0xA8F84539CE0BFCFBULL, 
            0xE8246971F69E3511ULL, 0x32741CE99A7DF525ULL, 0x501C341ABFBE3AF3ULL, 0xCC0A3FBF1FED238CULL, 
            0x36856CBC1D376850ULL, 0xE0E5F16E03E22B9EULL, 0x38863184F2CAE79BULL, 0x05495E999A20A382ULL, 
            0x9D83E3D8915BB931ULL, 0x788102558385D924ULL, 0x8CFCD1753650D0A4ULL, 0x7072F57047D8EDE1ULL
        }
    },
    {
        {
            0x27DE1C6BADB33F64ULL, 0xD3BB6101A2052244ULL, 0x856720600DBC1339ULL, 0x401E33A07521B667ULL, 
            0x0FEA02C75C0E0844ULL, 0x28D557612C76D8A5ULL, 0xAA590D259F83E945ULL, 0x3AE16EDDBA290DCDULL, 
            0x8F70BC03D9DAD15EULL, 0x2F4CBF3018247539ULL, 0x6220746744A02254ULL, 0x68E7C2C6B24BBBBBULL, 
            0xACE40AF7615A9E22ULL, 0xA76DCE9EFCA02DF6ULL, 0xED8B61F9FE274F2DULL, 0x2837F88A6B42FFD2ULL, 
            0x11C17E4EDD78BD26ULL, 0x31A0FFB12D4883CCULL, 0x3CD20A3CE32B7180ULL, 0x03AEF41FA79AC05AULL, 
            0x7F5C0694EB1D3307ULL, 0xBBDF46780939D54CULL, 0xAE512BBD0EEBE630ULL, 0xDE37CC72AE3DA7F6ULL, 
            0x1493FC34FED870A7ULL, 0xF1157AA25801B6ABULL, 0x08CF35C6A73A5357ULL, 0x31A7B3CCDA28F18EULL, 
            0xCCD83456B88814A4ULL, 0xBB20F2362283F242ULL, 0x8FEF03670B8366C3ULL, 0x25D2CD0344C5ABFEULL
        },
        {
            0x37BB85A8DFBD0F24ULL, 0x7E64944ACE6593D5ULL, 0xFACA78D551327269ULL, 0xEB74731E23F6923CULL, 
            0xD8E60CB26CD3580DULL, 0x27474FF485091A21ULL, 0x1EE9385DCBD05214ULL, 0xD230355C44F4A1C1ULL, 
            0xD99BF4FB95D21DB0ULL, 0x1417E2DD7E2E1087ULL, 0x0C81B7718F83C888ULL, 0xE703E3DFEBE172A5ULL, 
            0xBFDD10D11ECADA55ULL, 0xCDD490F59E25485DULL, 0x319257D49BBD0A31ULL, 0x9F8A42BCADF800DEULL, 
            0xA23FB0FAEB14E914ULL, 0x412CBAF59563498BULL, 0xD91747DFB8B3A315ULL, 0x7B58EA250B122607ULL, 
            0x9CEEAA930CDEC083ULL, 0xAFFBFFD512FF0051ULL, 0x67F714C658FCB4D6ULL, 0x3B59D5F86BAA5574ULL, 
            0x277677F6A177EC61ULL, 0x46E6D89699DFA2A9ULL, 0x53E85678CB167B4AULL, 0x65AE07AFE794E107ULL, 
            0x5F69BB3036E6C15DULL, 0x7146C35E070A9C68ULL, 0xF26D472C1CDAC2C8ULL, 0xA57845D74EC78310ULL
        },
        {
            0x15392D55C99CE95CULL, 0x5DFF64C3472D04CEULL, 0x4C87FA2C3A7EDA39ULL, 0xA9B901873F4FF4DCULL, 
            0xB94BE77E0D65F7DCULL, 0x3433CA2AFB46B03BULL, 0xC50E36214A139811ULL, 0x7299479FC4134D2CULL, 
            0xEC82FCC759E8EF02ULL, 0x888BAA5A602CF853ULL, 0xB0D3732D0E82830FULL, 0x945B7B41FA4DEED6ULL, 
            0xCE28D0290AB02295ULL, 0xDDA34927018FC440ULL, 0x401B39BD7AEB919BULL, 0x5CA725E67B478741ULL, 
            0x2D912A843AD3C715ULL, 0x8EC186519C5F9F3CULL, 0xAB2242A2CE9324D2ULL, 0x2B48567A161CF010ULL, 
            0xA27A53E19C747C10ULL, 0x775F7009E2F1D7FDULL, 0x05D85E8A3CD21CEEULL, 0x755663C5BDFEB938ULL, 
            0xC359FC0AAA0C8E05ULL, 0xC2FC0EB42D9A16E9ULL, 0x0F8DDE288DA032E8ULL, 0x09ABBE43B059EAE8ULL, 
            0x7EBCD78E0162190FULL, 0x7BA0F48C7A1C3D8AULL, 0x3AC59D68EE3298BCULL, 0x4EC7924632CC1567ULL
        },
        {
            0x7E0EA2B7F7E05E7AULL, 0xB539E17327499DDDULL, 0x1D277D45452850A7ULL, 0x11946B816F23D13AULL, 
            0x922C3247AACEAEEBULL, 0xB5CA0DCDEEB582D6ULL, 0x9EAE928BE2D48F53ULL, 0xF3022833C4A445D5ULL, 
            0xC7881990461EA7D1ULL, 0x09EB4BCDCCA0A70BULL, 0xC1C5E943050CF7CEULL, 0x9E6E86D47A2A871BULL, 
            0xE636325A5A1C152DULL, 0x3F1859EAA1680ECAULL, 0x5E1D2CA689E68B7DULL, 0x3F0E6D7B1CAB71B5ULL, 
            0xBF82E183C8889009ULL, 0x5FE6A85C1C85F33CULL, 0xC462901E898F5DD2ULL, 0x23A1CD84792A882FULL, 
            0x887129992F63FAE8ULL, 0xDC409D0E8F4A38CDULL, 0xB9031E3C9F4D51BFULL, 0xBD5CC198E88057F5ULL, 
            0x0D4FD3E29354641DULL, 0xAB3412A7E8FDC084ULL, 0x5EE1080ED2620B88ULL, 0x2E7561E3373D8C48ULL, 
            0xEEC8FC1C3A16B069ULL, 0x84463A466FD84A0EULL, 0x7FBFCFC8E4F5B446ULL, 0x8B0A7F99DFC634F5ULL
        },
        {
            0x2462882BF294036AULL, 0x89418471E7B93DD9ULL, 0x7A1DFE18C8BE326DULL, 0x2CF7E20018C533BCULL, 
            0xFAC6C7A8368E5AACULL, 0x8D45175FA0C9EA42ULL, 0x94C0B0B3700D7D84ULL, 0x1D59D3E34D2C4C19ULL, 
            0x28E1DEAB8E7B75A5ULL, 0x42793E6F1F672F4BULL, 0x80B394954A0AAE96ULL, 0x352C7692BAEF924EULL, 
            0x94470213AE45CF25ULL, 0x29E3B916513DEEABULL, 0x7B23B1C39CE9E343ULL, 0xFC47E0D7EBB35FA5ULL, 
            0x652BDC93851CED58ULL, 0xC99D7D82EE98725FULL, 0x0B34136ADD036CE6ULL, 0xF18A2B621418E775ULL, 
            0x3741090B5C207934ULL, 0xBFF456BD2440663BULL, 0xA853C66A3AA01034ULL, 0xD42CB1A3EC83B306ULL, 
            0xF21DACD67D22E145ULL, 0x98A03FA938BE44B0ULL, 0x8AB09F3593C9EE18ULL, 0x9D8DA254B360B82EULL, 
            0xD2669242D1E40D81ULL, 0x8D47E61AB504FA2EULL, 0xFAD624DC94B94FB1ULL, 0xCAC964B7C60E48A6ULL
        },
        {
            0x8B79C1517894AA01ULL, 0x6A798B89A5660ACAULL, 0x10474611AD9BA406ULL, 0xC0E359700710DD12ULL, 
            0xBB6C0759C2EF5F76ULL, 0x221C4FC0459F826DULL, 0x4C598CBFDA068028ULL, 0xBEB719EAFBD1A752ULL, 
            0xA0C3DA37C19AC391ULL, 0xDC9A13FF8EF6CD7CULL, 0x17D22ACAE45A9AC8ULL, 0x5B889296B416CBACULL, 
            0x9D10DB50B1B70DB8ULL, 0x9997828428A9E3F2ULL, 0xB7813B9758E29C54ULL, 0x6A8FED003B28A7E7ULL, 
            0x1FFECB6E1DC8DE72ULL, 0x68DA544E685C7114ULL, 0x7F912A9ECEEF9F96ULL, 0xAB91B78C9D5F70DCULL, 
            0x7381A832223DE784ULL, 0x3284CB6B75250EC4ULL, 0x9B02BFA362D4A85CULL, 0x8B4CC7ECD43FC7A1ULL, 
            0xE15DC29F807AF6E6ULL, 0xD7E074DE4B096984ULL, 0x09E6046F05ACB896ULL, 0x7DD4514AF827D6A4ULL, 
            0x9864F81CE7520733ULL, 0xAC303CC2F8BEC359ULL, 0xD0B980315B004274ULL, 0x50FE8C1001F7D9E9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseCConstants = {
    0x7290BA625B0C106EULL,
    0x12F9AEF0D9AE8D9DULL,
    0x21DD392D587B9DFBULL,
    0x7290BA625B0C106EULL,
    0x12F9AEF0D9AE8D9DULL,
    0x21DD392D587B9DFBULL,
    0x5C12226564DB3A0EULL,
    0x6D6690773E445A59ULL,
    0x1F,
    0xB1,
    0xD2,
    0xBC,
    0x7A,
    0xAE,
    0x7C,
    0xC3
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseDSalts = {
    {
        {
            0x201C04DCAEB77A59ULL, 0xA31B2F876BF66D19ULL, 0x935C8A890D58677BULL, 0xBD941157E4838B1AULL, 
            0xB8A9333378C22EA4ULL, 0x15D8267EBB008689ULL, 0xD15499BE44849715ULL, 0x4AFE36440C21AF07ULL, 
            0x479F539105D63871ULL, 0x2A6F04570AB1F6F4ULL, 0x0FA889D986D9454EULL, 0x81CC0DFA4CDAA8CDULL, 
            0x85E727D91EDF492AULL, 0x2B7B16BD855263F1ULL, 0xD7A78931239417A2ULL, 0x1073E4FF84632DFFULL, 
            0xCDEC024879868A64ULL, 0x489BF71E2BB69DCAULL, 0x9C6AC342E72407ABULL, 0x734895365E1E1276ULL, 
            0xBFD58B9BE0C39E85ULL, 0xB2323170EC3A599CULL, 0x7476A6590746F72FULL, 0xC5DA018319A3B197ULL, 
            0xB4C0736EC7FF53A3ULL, 0xBC1AF7BD765BFFAAULL, 0x693EF965E78A88D4ULL, 0x7FEA502649DB6C94ULL, 
            0x64B5349314EFAB69ULL, 0x3C9050B01B1E460DULL, 0x475C8FDCFD9F36AAULL, 0xE7F86280BFE83F2DULL
        },
        {
            0xD34C188B9648BA9EULL, 0x17AED7A3F94281A3ULL, 0xD4ADCB716DB9CEF1ULL, 0xC18168C0E1F1F3A2ULL, 
            0x4165694C41057E58ULL, 0x3CC44D747144A8C2ULL, 0x354A2F3994022612ULL, 0xB46F7EEC32C36776ULL, 
            0x99804404B9B3A94DULL, 0xEC4F6C4D9D51A22CULL, 0x386600FED0B92B9EULL, 0x0FD74F6F09468685ULL, 
            0x495E2A6493B364DDULL, 0xED84F5037B153A2BULL, 0xADAE767317C73C7AULL, 0xAD863F117C6948FEULL, 
            0x6465A9A07675C947ULL, 0x66261FAD1C0A872BULL, 0xFD6ABB7143568012ULL, 0x3CF4F7AB07F6DCBFULL, 
            0xCF132B36FD80DB06ULL, 0xA65B8081834DA845ULL, 0x587C88A475F0F5C1ULL, 0x302B49936058B684ULL, 
            0x38765166B361B837ULL, 0x571D8669FAE9AFFCULL, 0x1AC2AB3BCD03441EULL, 0xAF6F8C7EEDD1EEF1ULL, 
            0xDB01BA9361D51F7FULL, 0x530FDB8F5351CF4CULL, 0xA67D8E6323E4F5CEULL, 0xBEBB460CC551FBC5ULL
        },
        {
            0x8D55601F54F90788ULL, 0x279CF325E9B3046DULL, 0xDEAD7E94B71F1442ULL, 0x9E909784AC267532ULL, 
            0x0E4E24429F5B4169ULL, 0x5C06035E0847758FULL, 0x15670AE2B43777DDULL, 0x5DC41B6791BFB3BFULL, 
            0x69821EDB966828FDULL, 0x5CBC351021F76AB0ULL, 0x6C35438E76F14F4EULL, 0x21610294B35001FEULL, 
            0x6DCB4834ECEF8AECULL, 0x07C0FB145A1F62ADULL, 0xAC64C8099654C7CEULL, 0xB0A805D372C53432ULL, 
            0x7565EB63E0914B9CULL, 0x5B7583E88F019CD1ULL, 0xDFF7329E773C051CULL, 0xE1E684047DA975E3ULL, 
            0x4FD3D5D50C429C24ULL, 0xAA81556C0D3DA44FULL, 0x49A21DFCB6B662B2ULL, 0xFD8A54FAD5EC7702ULL, 
            0x9C1E4F2488DCD03AULL, 0x60142A9C12E37568ULL, 0xD824A6EC3AA213BFULL, 0xFA6E8931A0A70689ULL, 
            0xADC9BE5627069B13ULL, 0xDF35E23D7F20861EULL, 0x02A1A1DA1919C79DULL, 0x1C50129E5B3A24BEULL
        },
        {
            0xAB59EE17C4E2A615ULL, 0xD92A720FC5FD7A0EULL, 0x5834EEA39A456D4EULL, 0xB615054DBB0458EBULL, 
            0x0A7C5C206AE884C8ULL, 0x50235F6DB270322EULL, 0x9CC1E59EC782389BULL, 0x73260202744D2623ULL, 
            0x8041F962F5622BECULL, 0x6B80B496430793AEULL, 0x1D58302D483A9660ULL, 0xF4C76968D04C5527ULL, 
            0x07211EB18E78B12AULL, 0x981C6B1296BC69CBULL, 0x012CF0B40E0351FFULL, 0x83CF44AC1830B5FBULL, 
            0x315B06FF125CBAEBULL, 0x7A9BDAAE63DC1F5CULL, 0x151B698813CE13F7ULL, 0x04EDA9F72F02D61EULL, 
            0x517302332CF11FD7ULL, 0xF45DA83675370BE8ULL, 0x7FADB6BF2092E640ULL, 0x877C051B4B2ED2F0ULL, 
            0xE42441F384D69259ULL, 0x03264DE33CA7517DULL, 0x182340E338118B22ULL, 0x42A11D425FC01F0DULL, 
            0xB73E2B187EC4512CULL, 0x59E5BB62199E4856ULL, 0xCE823F4B7FFC9B6CULL, 0xA43810B0EAAB6B75ULL
        },
        {
            0x14D13C7075EDF346ULL, 0x6F95638D1DEA54B3ULL, 0x18F410257875C389ULL, 0xBC6C215A405EC3D0ULL, 
            0xFA10E6BCEA40570CULL, 0xD8FE6EAA33B642DEULL, 0x874D31C64F794176ULL, 0x25699363F33039C4ULL, 
            0x564B934FD0410449ULL, 0xB390554D44D1A6A4ULL, 0x7849AFD9446DEEEFULL, 0x5F233797126900D8ULL, 
            0xE69AACA8A168AC30ULL, 0x2A261252444BA76DULL, 0x1F7A307F59A61052ULL, 0xFEE02218E52B9E83ULL, 
            0x449BCDB96D8364A8ULL, 0xFFE994EBABDF3BBBULL, 0xB330915859646C42ULL, 0x32CA4D9236204A28ULL, 
            0x6A127F7FD1198802ULL, 0x3FA8F302DEB0BB7BULL, 0x2E776DECDDC0EFC4ULL, 0x2ED17EEAE92F33F9ULL, 
            0xC774B7D722F03BFFULL, 0x80B70D007B603F73ULL, 0x1372A13DC7B0EF2DULL, 0x981C0D54CAA174B1ULL, 
            0x875772D3198F8521ULL, 0xEB9DB2747BDB2F97ULL, 0xC759689EC2B4C6BEULL, 0xAAF4F11748E89790ULL
        },
        {
            0x61E63BE99AD36D47ULL, 0x9B1678B247D12650ULL, 0x0A5BD5F1FB6637C1ULL, 0x0EAD07A27F020BC0ULL, 
            0x4846455E1F614D5BULL, 0x011EBF337E846D19ULL, 0x436D33B30A934183ULL, 0x16667BBC37C7D5C6ULL, 
            0x99714BB9B806BFEAULL, 0xB9EAE233C94A21E9ULL, 0xF7F937B2F6EE0C68ULL, 0xF07DBB55F859A4C0ULL, 
            0x7124373F79DD7855ULL, 0x2E4003D2F4425232ULL, 0x46316A0730B59B11ULL, 0xCE61E2F42DB438C1ULL, 
            0x2954CFE66BFED77DULL, 0x58B07F72E2489604ULL, 0xE4F35343366E3A04ULL, 0xA44836714480FDA8ULL, 
            0xE53AA2C65F0A1658ULL, 0xE094E8085304C46BULL, 0x91FEA8FA158E506AULL, 0xAD0EE28A83B7E054ULL, 
            0xA6F39BEC71077340ULL, 0xB646E39568B7D9ABULL, 0xB97D81A177EB5479ULL, 0xB89C6B768D6CB2FFULL, 
            0x08F103F41C864D7EULL, 0xE174E3F482A46C63ULL, 0x84C8179EF67439F8ULL, 0xAE82E701A19E3838ULL
        }
    },
    {
        {
            0x99A6BE5BC0AB5AE5ULL, 0xE1D07D5C2D6D1421ULL, 0xE6D06BA989F2EC6AULL, 0xA89BF8E22BDC3A63ULL, 
            0xEBA53B145C002C8EULL, 0x4E49626090ED390AULL, 0x6E2DE99A72CF01E9ULL, 0xC2D3DEBF41D6B869ULL, 
            0xD4209C9488AB103AULL, 0x433AE9B3F6C14F7CULL, 0xD53CFD95D7F76F81ULL, 0xCFFC817850B3EF27ULL, 
            0xE77CB439A0020EF0ULL, 0x20DA80C6EFF39460ULL, 0x921C65A2DD513A76ULL, 0x9B9E8B307D74A034ULL, 
            0x15CF8C8C8D7C1946ULL, 0x54FC6CFF3AA9F996ULL, 0x9991F8719157B134ULL, 0xBE7E8FC4224F213DULL, 
            0x0742B051FB0DDE6CULL, 0x744ED554E344FB01ULL, 0x41E46E5AEC24B034ULL, 0x2AFA75E099C239FAULL, 
            0x8DCB8832360CE256ULL, 0xE70519F7254F3A5BULL, 0xFE00FA9CE25B2C81ULL, 0x29BF9263C549A179ULL, 
            0xB6D009F375A9D7E7ULL, 0x63198B8BCCD00816ULL, 0xA25928E7823C70F8ULL, 0x0602CB86F21B9C90ULL
        },
        {
            0x8F0B7C60C4E1A95FULL, 0x62E9ABFA8AE9CFB9ULL, 0xDF7207770981EFF6ULL, 0xE6EB5BCF9587A6E1ULL, 
            0x4A9D6D869A6EED03ULL, 0x7CE8113DC0C1C518ULL, 0xEC79EFB64E3F87CDULL, 0x625C8FAB8724BAF8ULL, 
            0x5BBA95DC87C0D8E1ULL, 0xB14D3C4607249028ULL, 0x1C2215D071DF0650ULL, 0x58A6B6ACC6445618ULL, 
            0xCF001E7CBAD4463DULL, 0x8758C86F33FB38AFULL, 0x6E7AFAD20853F4D4ULL, 0x9A0FAA5D72E78340ULL, 
            0x58EEA28920BB8957ULL, 0xD786152A69319ADEULL, 0x8A81866C111D700FULL, 0xB3830C73066D5D18ULL, 
            0xAEFFE91F61B54608ULL, 0x7CC49E33F6923D15ULL, 0x91BDA1DC095B55B3ULL, 0xEB2DD85C60F51C68ULL, 
            0x581BA7EE213C795FULL, 0x1D7251547F9DB0FDULL, 0x4B83DD1AA2C519C5ULL, 0xFA8FFE4B23B724ECULL, 
            0x1229DC0ADD2E5289ULL, 0x6E894C1B2030B105ULL, 0xA2EE685B2F12405DULL, 0x88ED30D31F15B882ULL
        },
        {
            0x00E3C04E6989A814ULL, 0xF4470BA321DB9055ULL, 0x8A69879989F42E22ULL, 0x9D42D31978625924ULL, 
            0xA4E52AFFDF8220F1ULL, 0x95C2B4F98B0DB846ULL, 0xC01AE58EC182909CULL, 0xC16AC7653B75F4DEULL, 
            0x6948F5928E64EC78ULL, 0x289FAA03CC66A561ULL, 0x22BFA0849DBE4F7FULL, 0x48E4F5E2F853793DULL, 
            0x3B43461F79760E67ULL, 0x2CBF4F8128964B1FULL, 0x9AFB6771FA19EB7CULL, 0xE53175B4A1529032ULL, 
            0x71F7D439BAFF4C69ULL, 0xD0E3CBA89DBD3341ULL, 0x1340527FB8A8B840ULL, 0xA71ED182B547E00BULL, 
            0x5C2911F825D78D94ULL, 0x52C478A1D85D586EULL, 0x0FAE83FCD510B016ULL, 0xF78DEB2932E58AE6ULL, 
            0x382744ED9D1D25BEULL, 0x0F2654CD259BAAD2ULL, 0x2B1C48F7DC6D41BAULL, 0xB67F9242F4FB1CA3ULL, 
            0x90FBC8CC8D6750DCULL, 0xE3CE356BF4C44235ULL, 0xEA7DB394EA836038ULL, 0x14B8A2C5569A8E67ULL
        },
        {
            0x8EE61CBC1A5BAE3EULL, 0x9D171A1FF18A38B3ULL, 0xD03CE9AC410C9AA5ULL, 0x436CE007D7AF0C99ULL, 
            0x56BDA897FC44DD6EULL, 0xA778A767C9D9BA25ULL, 0x24AB20667159EACDULL, 0x4CE756A9A136919DULL, 
            0x3E99F4E15AD0B660ULL, 0x67DF4E14276742EDULL, 0x25FF5B6C6CE546FBULL, 0xC55901B67E6ED105ULL, 
            0x6F5E92BD4B015209ULL, 0x88390936ECD40A23ULL, 0xE6F6F856EB308DD5ULL, 0xAF22A381B07549A0ULL, 
            0x56D017E52406B7A0ULL, 0x1ED813E4AC75DC66ULL, 0x158653437AD2BDF0ULL, 0xDC865C3015F4A077ULL, 
            0x11F4C17252355F95ULL, 0xB054CBEA7FBD09C5ULL, 0x3165A7D764E4A966ULL, 0x9943C8FDEC39F568ULL, 
            0x1B0B08FC50F8FEADULL, 0x7C70E89E6B0DE174ULL, 0x6963D92DC296BF8CULL, 0xF7E0C300F9FDD358ULL, 
            0x14C1416804B9309DULL, 0x1938F5D84F53E4A9ULL, 0x7110F0C197CF5344ULL, 0xE68813E3D73E0310ULL
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
            0xA64AC376ACA469FBULL, 0x649530F2BE4936F8ULL, 0x9CC0CBD4917C8F9AULL, 0x1DA574F2981CA756ULL, 
            0xD04C813E6CEA0CB4ULL, 0xC3F60AD67DB97778ULL, 0xA1738E0A604DCDC8ULL, 0x3B171BBB00B8D77EULL, 
            0x01591298851CE47FULL, 0xDDE9559A5CFF0537ULL, 0x543F24EBC28BF53CULL, 0xDD0F7188605A2907ULL, 
            0x737718FBFF9DCB78ULL, 0xD55F80C418E9F5E0ULL, 0x2877A8D554205D23ULL, 0x7E9DA92A8D03AABCULL, 
            0x787EFD1865F6B2D1ULL, 0x491B9A29758FE116ULL, 0xBDA5B09D5EBADEAEULL, 0xDB018FF369DA3BAAULL, 
            0x5088F9F0BA22678BULL, 0x015DD89A3DC169B9ULL, 0x33295BB47884B712ULL, 0x6C5AC7AE7046A823ULL, 
            0xFC38E98726C6E61CULL, 0x4E49A512009A35F7ULL, 0xF7EF9C844A18ED98ULL, 0x5C44700BBFCC08EFULL, 
            0x37B98E7BDEA1CBC5ULL, 0x7EACDF906DCECB7AULL, 0x95EC85827A84F46EULL, 0x50ED1E17D8C185C2ULL
        }
    },
    {
        {
            0x80AC755796508256ULL, 0x51F746E7D33AC3B8ULL, 0xEDF0C2FD4D72B627ULL, 0x0BFF41A952108BCAULL, 
            0xF594AF3B9A4A2D0BULL, 0x5034385F6608C241ULL, 0x81BBE3DB79A67943ULL, 0x2092DEE08DD3E030ULL, 
            0x214318098F4510DCULL, 0x39239DA719635AAEULL, 0xFBB53442AB72FC6DULL, 0x9540AC1474F84EC0ULL, 
            0xD427F71D10D79872ULL, 0x2325232874EEC8A6ULL, 0xEC3CAB431F691ECAULL, 0xC8E7215EA6DB3483ULL, 
            0xE853A95D390BDE00ULL, 0xE1BE00C2B828D867ULL, 0xFE8B6C1182D2701DULL, 0x67C9D1CF85E298F9ULL, 
            0x1F5A748224C78D39ULL, 0xD129DE904E0D18E0ULL, 0xCCDAF2F4E2ADE25DULL, 0x245622DC154E5A0BULL, 
            0xBDF3E46450EB800CULL, 0xEDBFFC83C3F47321ULL, 0x7B40BF42449DBBF9ULL, 0x47EB8EC65565F1DEULL, 
            0x33900CC12F052C21ULL, 0xBCCD9AC7527FBE1AULL, 0xE45CC24E2A202291ULL, 0xF03D12EA55361CC9ULL
        },
        {
            0x45821317588AEDCFULL, 0x27C1E2F3D42BFAA3ULL, 0x806B976CC2F0CB23ULL, 0x4991858E1AB44CC7ULL, 
            0x53348A11A20319D9ULL, 0x5A93DC19DBBA36D9ULL, 0xBFB92B6984AE3E66ULL, 0x7B80757967C21E5FULL, 
            0x37CF3BBF96F77646ULL, 0xD9BA866ED2422D16ULL, 0xAB582A2F0289C3E2ULL, 0x0400F6730AC1F3C7ULL, 
            0x0FC396C9F5F43663ULL, 0x381135A438E5C6A8ULL, 0x38882C9EEE2371E9ULL, 0x29236EFBF94B3257ULL, 
            0xFA027E5E4B025173ULL, 0x11834C91DD6A7999ULL, 0xDF663E78049851CEULL, 0xBAE3681F22BABB30ULL, 
            0x81F5CEC6DF461A2AULL, 0x42D1743AFD9BE964ULL, 0x36BE3FC34DCD1BE3ULL, 0xA9896CC185385700ULL, 
            0xEBBD547BEB702B84ULL, 0xDA395118838FC45DULL, 0x389F938563C6C081ULL, 0xDF23EFB227019DF3ULL, 
            0xB7849C7483968CE7ULL, 0x405B520036830C68ULL, 0x5849D24F659A6453ULL, 0x87C107FF6B4CD9E1ULL
        },
        {
            0x639043BDF55A6229ULL, 0x27C930CCA90D805EULL, 0x2F499263E50B5AF3ULL, 0xD110CB96BB08175EULL, 
            0x63F6AE218641BF5EULL, 0xFC4ACE703E1356C5ULL, 0x277BCAF8459C9E8CULL, 0x787ECA91A1BF494AULL, 
            0xBA1AB9D1C498A1BAULL, 0xE18D84FB3A6BAC5CULL, 0x5767D8CD7310FB4CULL, 0x18BBFEDA63D28554ULL, 
            0x73624047DE4435E1ULL, 0xF59EB2ECDE25B05DULL, 0x0C46772F4232F4EBULL, 0x9E627E679439F110ULL, 
            0x7CC83D7A6034EA55ULL, 0x13C6E1DC7D6F66ACULL, 0x1563EE38ABF1B28BULL, 0x37AFEA06E07A40EAULL, 
            0xA6BC8401404D563CULL, 0xA068633035846170ULL, 0xEFC4772F2D263F3BULL, 0x9CB1DC65E52F8C74ULL, 
            0x1E470229F97336E0ULL, 0xF0C57BA2FAD27404ULL, 0x0A7CC2FDDE37AADCULL, 0xA645C5457A613440ULL, 
            0x1C1347A8E9BB19E0ULL, 0xE76E8293F5B1E5C5ULL, 0x863E6BA5A5454077ULL, 0xCB3626B0635483FCULL
        },
        {
            0x293CC8431BF27D48ULL, 0xBD7D56B280B73ABEULL, 0x226EA86081247942ULL, 0x55BF029E573C63ABULL, 
            0x97D7E36DD6D7366CULL, 0x14ED9CC6A5F4B18FULL, 0x3881214F6C79632CULL, 0x7177E66C7D6FB112ULL, 
            0xFC9B931AFF2B4214ULL, 0xEB75C4E9C5A9D97EULL, 0x3CBE20E032B341BEULL, 0x6B5962B835DA1EBDULL, 
            0xE9D16E5A548716DBULL, 0x991724C9BC71DD1EULL, 0x4A528CE600FCCBADULL, 0x61A1ADB860671144ULL, 
            0x115549226747837DULL, 0xA71B36420A88087AULL, 0x96FB1D8FE5266FEAULL, 0x70D79B76FD3EA4A5ULL, 
            0xBB9B1FA495629626ULL, 0x756DD04393DBE1A0ULL, 0x1B640CE637951A83ULL, 0x9E3316C9F3320926ULL, 
            0x1783DB9B4EEC27C7ULL, 0xAFBB1E51BF65DFD7ULL, 0x5C2FD4FD87D95547ULL, 0x117109EBDC81F7FEULL, 
            0xC924AD047984EA2CULL, 0x3D922FC166039A00ULL, 0x513FC519DF7DB266ULL, 0xB75873466290B44BULL
        },
        {
            0xD8C6032777934ECBULL, 0x6F0A332AC2C8BB0FULL, 0xFF9169BAF29705F7ULL, 0xEEF6B87FB9C8AF2BULL, 
            0x2EF60101FE3F0DE7ULL, 0xEBBC1C4525F82533ULL, 0xF4BACF630B593C9BULL, 0x502B58ECB6F4F918ULL, 
            0xE35F295251C81164ULL, 0x24A0C6140BD16363ULL, 0x650899C46AA2F085ULL, 0xBA2B14BB3646C0D0ULL, 
            0xB8822A2B7D989A79ULL, 0x2146233BCE43DADEULL, 0x0567A125EE1FFA72ULL, 0x6521A7B9B48CF054ULL, 
            0xF457EAECA5A8C840ULL, 0xCCBA954309EE5249ULL, 0x387DE59AF1DA4B74ULL, 0x6D7F37D2CCE0937CULL, 
            0x94E1FE098E61A2A4ULL, 0x9CC31B2661742D89ULL, 0x08B4766B1B060598ULL, 0xBDA4709C2F23F902ULL, 
            0xA4DE9F5C709B8E32ULL, 0x183E4A35CEC71824ULL, 0x781EB80FB2EE6041ULL, 0x720EB280C543F0DFULL, 
            0xBF3C65A7F0CB1CEBULL, 0xE0AC472AF00FD845ULL, 0x3CA69D62C15A2812ULL, 0xEC36FDBFEBF0454CULL
        },
        {
            0x3BBF0273B9D5E042ULL, 0x939B77392EF50268ULL, 0x1EE653FA2D26FE9CULL, 0x432BCBCA7EC262B4ULL, 
            0x3BFC0555B1C5B78BULL, 0x7B79C8016C91A8E4ULL, 0x1D88BB52BE0EC8F8ULL, 0x6E9B474BEE22EC85ULL, 
            0x97F76CE347333DF5ULL, 0xCEF7F28778605811ULL, 0xF0B07E2D3CFBD6B6ULL, 0xE4B5DED5E21075B5ULL, 
            0x8FC46F0AFE2E712BULL, 0xB0B131131359D3CBULL, 0xA89A7FB816358224ULL, 0xD023564D85747F8AULL, 
            0x1751D00E64ED5FDFULL, 0xAE99F41AF87D319EULL, 0x40228F76E0C2F469ULL, 0xB9B8523AA446E3A4ULL, 
            0x103337994278DB9AULL, 0x6A321E53DDC7D4E5ULL, 0x9C1C5B227F434114ULL, 0x21C9A047B5A1AE99ULL, 
            0x6445FCBC3993E676ULL, 0x5A7C967B6427A716ULL, 0xCBC8354A1ADA067EULL, 0x9F37D4BE0526B05CULL, 
            0xBB032AB83472E3FEULL, 0x4C8ABB5CE82DECD2ULL, 0x51AAEA031F0BCB8CULL, 0xD7BBFE100790BC7FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseDConstants = {
    0x07B604F67E5A5418ULL,
    0x498EF9EE684A2014ULL,
    0x5440AB6B660D5EBBULL,
    0x07B604F67E5A5418ULL,
    0x498EF9EE684A2014ULL,
    0x5440AB6B660D5EBBULL,
    0xE42D1F27F00D3B6BULL,
    0xB1CDC4F0FC411A62ULL,
    0x78,
    0x77,
    0x43,
    0x72,
    0x5C,
    0x2A,
    0x03,
    0x2D
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseESalts = {
    {
        {
            0x63C14D3AEE71BD16ULL, 0x55D6223B41E729BDULL, 0xB6DC72F52F889265ULL, 0xB0F74DADA3C2F771ULL, 
            0xDC2E72B928424FB3ULL, 0x5F927C9747F216FDULL, 0xEB5926155E308B19ULL, 0x47FD07F4A18C4DC2ULL, 
            0xEF9AFCF6A1371A54ULL, 0x109D331F6D7C24E4ULL, 0x74DFFEB597DAEBD5ULL, 0x96F8C60A05AE37B0ULL, 
            0x2AD4B2F254C73BAAULL, 0x1F217F1569CC5766ULL, 0x2AE0C045ACF82A23ULL, 0xAF16D7EA1BDC9891ULL, 
            0xE87EA8AB17D7A596ULL, 0xD07F043B09F7C5F7ULL, 0x05B36DFF00E78EEBULL, 0x0531D0E1044A1E0BULL, 
            0x311819F8E09A1804ULL, 0xD5981CFF1FFECDB8ULL, 0xB7A567756A841AA7ULL, 0xC1A956205A85C96BULL, 
            0xFCC2ED9EB64F000EULL, 0xEDDB63C7772726F1ULL, 0x9A82317EB3DF5710ULL, 0x545A698276A89DCCULL, 
            0x50BEB8FBBB46BD97ULL, 0xF3651A1587861B08ULL, 0x404F9743EABECD04ULL, 0xD827330A36E376AFULL
        },
        {
            0x3A71EED4ED93E98DULL, 0xB18AB6961B9F582FULL, 0xA3C01307BD16B0C4ULL, 0x909396B42ECBD871ULL, 
            0x24B791A9EF43081AULL, 0xF0DBAB6A6C4B354EULL, 0xDCDFCCA95204D931ULL, 0x32BA7985C4A2AC4BULL, 
            0x51BF135E2644382CULL, 0xFF699A2822B08D0EULL, 0x6E855B068353B23FULL, 0xBF8FCC15A2A9C2A0ULL, 
            0xF121DED851A43BCEULL, 0x03B59AA5E4C7E43EULL, 0xB466C9A013A0A24EULL, 0xF4A47FB14239008AULL, 
            0x695D00E9490B2FC2ULL, 0x7454103FEFCA9A1FULL, 0x1BF6BDA7C7586010ULL, 0x1E9955E988C4134BULL, 
            0x839C02E03AF53ECAULL, 0xA24A10BFA8C821ABULL, 0x94109B79D02A9E16ULL, 0x2C8F4DB114898451ULL, 
            0x69E465635676B243ULL, 0x03D626BD696BCAFBULL, 0x11A90EA4A99896A8ULL, 0x35E565EB61D8B13CULL, 
            0xD5DD78B0FFF4774EULL, 0x3B05490A8EE405BFULL, 0xDF8F65BB4853EA02ULL, 0x598F16CBEBA52CACULL
        },
        {
            0x8E3D339B95E000A9ULL, 0xA5E5231BF91A5170ULL, 0xB7B5A41B47A4FD0DULL, 0x3B57E26271F3F9B8ULL, 
            0x3850002748684AE4ULL, 0xF4BBFB338FE8795EULL, 0x80745FC1D25B0DCAULL, 0xC535848E85AA82F1ULL, 
            0x53EBCEAD0CE9B2D7ULL, 0x57D676A2CFB23A73ULL, 0x625E4A551EBE0E50ULL, 0xDB49C22DA76C2EB3ULL, 
            0x214EAE8630683C60ULL, 0x9390FC57C66DAA93ULL, 0xF1CBA5122647BA58ULL, 0x451060D73D095E69ULL, 
            0x4C304AF170A99169ULL, 0x8887D3AC1D39FFD3ULL, 0x20AECCFABFDFFB23ULL, 0x95811D5BB3C1E1FBULL, 
            0xE51616A8AB1BB6F1ULL, 0x4DE95E4584EE74FDULL, 0xFF7786E64B56D0FDULL, 0x8813FA7630CAB87EULL, 
            0xF75BC43A5030873EULL, 0xD92BF06140BC5ADFULL, 0xFC1F47C31354C965ULL, 0x9A3F874E305EB42EULL, 
            0x7BDD9FBB3B324B30ULL, 0x4645A0E2F38A6B42ULL, 0x6AE2630029473B68ULL, 0x60E5EB1E82FD1855ULL
        },
        {
            0x4084CAE243F791AFULL, 0x60B64F275A1B99FCULL, 0x11354ECDDB41B44CULL, 0x8AAFB1FF0EB3FDAEULL, 
            0xBBC13F5D736BB80EULL, 0x5AD92F5EDF255AE5ULL, 0x6AF1143E92F38750ULL, 0xD97FD78159F92D4CULL, 
            0x4290B0AA5E8D1BE5ULL, 0xFC9F2D2B7AF802C8ULL, 0xB6BF95B5C0471068ULL, 0xFA674CECE2044D2BULL, 
            0x0A24533B8F1623BAULL, 0xAF9FFB771BF34ED1ULL, 0x2E6D24BB25845CBBULL, 0xD533803923693676ULL, 
            0xE2C418A2C8BEB13BULL, 0x673F4B9F9C170286ULL, 0xF3E2C9D3F47152DDULL, 0x4717B9CA0967C3A3ULL, 
            0x9BB77C735BBEDA73ULL, 0x8B2F8D4406975FFAULL, 0x88E98390E13F8BDCULL, 0xB2F90A5F9649C671ULL, 
            0xD82CCDCE030527D4ULL, 0x1006DF0CD04CC8F2ULL, 0x15DACB1E298043F0ULL, 0x59943F5BBB390439ULL, 
            0xA9B1067998209878ULL, 0xAEF871B4BE9FD007ULL, 0xA62F54B922E2252AULL, 0x77222A5E32667C66ULL
        },
        {
            0xB60A99741733DC92ULL, 0xE0467A883BFABFD3ULL, 0x56CEE319010B98ADULL, 0x006A5FB2491D1BF2ULL, 
            0xA141C779062B99B2ULL, 0xA44C7AA992DCFDE3ULL, 0xF51B84A1731E9390ULL, 0x01072BEF5863DD97ULL, 
            0xCEC546A861190D39ULL, 0xFF60BB32DC094EB1ULL, 0xBF50BCC564BAB091ULL, 0x9A0E754CA45987A3ULL, 
            0xBB9AF63544ABA998ULL, 0x3E1481852D3E6A77ULL, 0x8D7507E7C3C3159EULL, 0xCEB2E2C947A3A9AEULL, 
            0xDFC4766AF966306BULL, 0xA0D63A4D393F72DEULL, 0x4D9E24E253358069ULL, 0x69D76400019FF09AULL, 
            0xC7E8135869D4638EULL, 0x5D29F7261F991CD2ULL, 0xD62F211424E7ADF8ULL, 0x426FB9A87E132B40ULL, 
            0xF8F0886C0A34C5FBULL, 0x90EC104C2442BB12ULL, 0x427053AF5C7D5DD3ULL, 0x48B46315B4BE93DCULL, 
            0xBA9D488AEA4E5702ULL, 0x5C77E875FCE9FC07ULL, 0x6520311F1A5CEEFDULL, 0x206579C4FE237B6EULL
        },
        {
            0xD9852EF24B824D81ULL, 0x3B96D2A2EFBB2A89ULL, 0xA02623317AE117A1ULL, 0xFEA8CF67A68D869AULL, 
            0x82F142F8B4A5AD4CULL, 0x3EC6C301F8AEE8E6ULL, 0x1BF444F5ED88F59CULL, 0x8DEB830B0FD427A4ULL, 
            0xBD4EBB1AF953BA6BULL, 0xD7034AAE2F1FC55FULL, 0xEF7889A3B5D225C0ULL, 0x7814B3C05E80753EULL, 
            0x153E9007A9796DA7ULL, 0x0127E1AE42757F6BULL, 0xC530A17644D19F36ULL, 0xF3A31B80D4AC48EBULL, 
            0xFE2677C820FD6742ULL, 0x40616ACF4872D9EFULL, 0x686928493B092C0FULL, 0xB5C4DC702ACF7E88ULL, 
            0xD2005E2B2337C405ULL, 0x484C9C80BD92098FULL, 0x8B1D69045E22B1D7ULL, 0x74527265B0C47ECDULL, 
            0xE6521760EA55BE16ULL, 0x14EAD87955335BB7ULL, 0xB5ED5A4DEDD32D73ULL, 0xED8D39E3F244D190ULL, 
            0xD1B991DD718A0FE9ULL, 0x4954E76EDFEA6A72ULL, 0xC5C325B96EA991B5ULL, 0x45222051E4B9749AULL
        }
    },
    {
        {
            0xAA20359CFD318113ULL, 0x2781CD6EB3BF57B3ULL, 0xBA0B4D9F45A2FAC0ULL, 0x9F516AC6E898455BULL, 
            0xD19866E5DA50D134ULL, 0x3EA77A1C6528DF27ULL, 0x16922C2FFDB8E8E8ULL, 0x5438249E2715802EULL, 
            0xAB6B50976B9C96ACULL, 0xCDBD08B372368947ULL, 0xF350D7BA6B2B36AAULL, 0x581FCD25127DC35AULL, 
            0xDB70D906DD78104AULL, 0xBEF08CF25AB7C63AULL, 0x033AFBD92D5031A7ULL, 0xA2025B2420BD51BDULL, 
            0xE6A7753A46942C49ULL, 0x52BE53AB400FFA84ULL, 0x470CF972CF3BC29EULL, 0x418C2B8B74636CE8ULL, 
            0xC2195486C9503CB9ULL, 0x50783EB2039FFA66ULL, 0x1683D22574E6161AULL, 0x613631BFBEB77D2DULL, 
            0x30212C859CC3E668ULL, 0xAB4DF4A39FBEAE37ULL, 0x961619B83387CCBEULL, 0xAB33EFEC6541B154ULL, 
            0x724EBBF63C618988ULL, 0x8240AE95BAA10FA9ULL, 0x17E1F517975CDBCEULL, 0xB76C33187C915807ULL
        },
        {
            0x32F6D5A8F8E421A8ULL, 0x4F1E5361F5D31033ULL, 0x1EF5B1C4F3E0F410ULL, 0x0BFBE5C4011E5988ULL, 
            0x0209EF02C50FA5DBULL, 0xC7CC90C6E4EB7C16ULL, 0x5EB3D8646260188AULL, 0x6620F6D5C4549878ULL, 
            0x4B5D04844D25F254ULL, 0x51C23CFD46F33262ULL, 0xCF910A4ACFC8A6D8ULL, 0xEAB2503774F1F586ULL, 
            0x443D619AE451E761ULL, 0x039E5F9AE23348EDULL, 0x30AC712C7CB3DE11ULL, 0x33EBA15F1EB0996DULL, 
            0x627507E23BC4100BULL, 0xFD2C2AAFCB96B84DULL, 0x4414E1AE89F8AA55ULL, 0x52E3B2D24B3E86A8ULL, 
            0x7C01D8AFF042AE15ULL, 0xB05D4DBA82079610ULL, 0x709E547E66C3787FULL, 0x87883351CC588553ULL, 
            0x6FA5F16709490C29ULL, 0x1334DF878DFFEE5BULL, 0x7C7ACC6685B246FDULL, 0x26944A1AFF1DFADDULL, 
            0x5B52BB69A129AD33ULL, 0x091917EE1D8DFEDEULL, 0x7BE46A8070797403ULL, 0x9B8A5D84768B8BAAULL
        },
        {
            0x524B339A73239759ULL, 0x832B148263CE46DBULL, 0x772B893EE63921AFULL, 0xC58EF0F7B67867A0ULL, 
            0x2C3226557F517CE5ULL, 0x6A5DD9CEC81747DDULL, 0x61C7B172914DA6C5ULL, 0x3FDFBEB4E01CBF16ULL, 
            0x186BDEC08B83DAA6ULL, 0x80B4F22FD0A6B6E7ULL, 0x7DEEBCDF2D1D1353ULL, 0xFDB13A06A355C986ULL, 
            0x25FBC15CD7420C80ULL, 0x72B9E1B8E4D05993ULL, 0x7FC496E8CFC8FF0AULL, 0xBEF24644C8A12B3FULL, 
            0x8C7AC81A2368C37FULL, 0xA9FB3495ED437E9AULL, 0xA32B1379D06BDAB1ULL, 0x077EABF2F8F3594CULL, 
            0x01B7F3AFAC258812ULL, 0x1133E36669A07540ULL, 0x25F20FCE939AFE2BULL, 0x75282680DBFF14FAULL, 
            0x240687CC0852D86DULL, 0x7AC4F5D334BBEC2BULL, 0xC02E307A5D1742BEULL, 0xB7526E047CAAB374ULL, 
            0x1B39596B57A1AFF0ULL, 0xD7D73782FE86AF39ULL, 0xEB0238CF6A77C7CEULL, 0x6EB1A8BEA9A2FDA2ULL
        },
        {
            0x9CC9634BC1BC148CULL, 0xBBBC245075DF764CULL, 0x5F2028B8F887E640ULL, 0x47055DB66696D9E9ULL, 
            0x24D1B7AED68DB97AULL, 0x3BF02BCBC8ADDEAEULL, 0xE2BDC040B8644934ULL, 0xA3335E8009E269FDULL, 
            0xE30660565804B405ULL, 0xA097BB01C36C960BULL, 0x20A4A7625E0F3B71ULL, 0x37815CD849DED86AULL, 
            0xA04D333AE2C99243ULL, 0x2D53EA7316078FDCULL, 0x7D562127C0C5FB31ULL, 0x390CB022088BFCB4ULL, 
            0x8E682EACA16E7E35ULL, 0xB46927CF2C0AAC34ULL, 0x81337045DC5BCD8EULL, 0x817BCAA1FF1FDECDULL, 
            0x235E4A24BB062111ULL, 0x1C6C7756587AF2EBULL, 0x4DAE3CE09ED7BB67ULL, 0xFE1156D962BD6F73ULL, 
            0xC4F09924CA0376CDULL, 0xEC3F1F69B82AFCFFULL, 0x9013EBCFBC72A300ULL, 0xBDE57978EEB552A1ULL, 
            0x09864A774650A6B0ULL, 0xA326F8803C8FA061ULL, 0x17CEB1EAE3F6BB20ULL, 0xB13D56FA77DB196CULL
        },
        {
            0x373E525F2B5FDE93ULL, 0xFE55FD8105E2C434ULL, 0x00A68AA699BEDD9CULL, 0x81249A5F8F96B34CULL, 
            0xC03BB2489F3A10D4ULL, 0x588E1F163384A677ULL, 0x44F7E211A2774EC1ULL, 0x5459A406632D4236ULL, 
            0x17883D8CFB19AFDAULL, 0x830E83935CC27CAAULL, 0xF1C9A38D77E868D8ULL, 0xCB8E66324E0907A4ULL, 
            0xABAF1DA963868866ULL, 0x3F2747283415A845ULL, 0x124FD1B110AD41D1ULL, 0x42C695D174AB81BCULL, 
            0x4B3B275974466D67ULL, 0xF8E87DF0658DFEE1ULL, 0xD56FA78D0C1DB3B9ULL, 0x0DCF13B23A8B5AF3ULL, 
            0x8B7DB526C977E5E9ULL, 0xC1BBA79F1268DAA7ULL, 0xDE77EFCBC29E87E3ULL, 0x056FF9CAF2348CBFULL, 
            0x4FE53466F68F20D9ULL, 0xF1226B5DE1E98D0AULL, 0x004248C8BAD519B4ULL, 0x8E25B1109368105BULL, 
            0xDE4B09A6CDC3DC13ULL, 0xC5E631A3F70F09FCULL, 0xEA80D99B0D57C5A7ULL, 0x862517CA3CC237B3ULL
        },
        {
            0xCFBD65343177B95AULL, 0x08BE47C7FC589D8AULL, 0x79FBE99A36AD23DDULL, 0xCEDDB91E43A2E24FULL, 
            0x3920CF0E2530577FULL, 0x7D6F94DBCE010E68ULL, 0x69180EDBC50F8602ULL, 0x81E3C3C55D8062B3ULL, 
            0x452B64DD54FE0490ULL, 0x7C6E531DD53AFA7BULL, 0xBFF7832BF53E4AC3ULL, 0x338D46B9D9062FFCULL, 
            0x1A9306A1FDFFC9B4ULL, 0x345E70A8015848E0ULL, 0x3664F6496421DFE0ULL, 0xC96C95AA52B2E359ULL, 
            0x26A2368433A91660ULL, 0xFA2695D5428F489AULL, 0xB5EC5ECA1ABB01EAULL, 0xA95A40C6CE95ACB8ULL, 
            0xB32C2C22DC384823ULL, 0x6FA512111FF8C3FCULL, 0x5415F22E3C6CF9E1ULL, 0xA7174B1E5D9E22AEULL, 
            0x91539EE9C50BCB53ULL, 0xE14067199AC9B1C7ULL, 0xBAE0E8A31AA2FE24ULL, 0x355B2B0DC298D9A4ULL, 
            0x42FE5748C8274EC4ULL, 0xFC8E9AB60E8FE3F8ULL, 0x5B390957EA18B52DULL, 0x366CBDAC12EA7778ULL
        }
    },
    {
        {
            0xF6BB2BDFCF203F97ULL, 0xBFBEF98A3A248874ULL, 0xD823097C458F90B4ULL, 0x8342004F45C1F74EULL, 
            0x769293D8A8A2A601ULL, 0x4FE243B550719924ULL, 0x17CE3D17754FA62EULL, 0x2CB3DF71D346EAD2ULL, 
            0xDA112D0FA24A48E5ULL, 0xE65AFD9B95A62337ULL, 0x3206071243D79509ULL, 0xF8951CC455156BAFULL, 
            0x633337E1386052D0ULL, 0xA935E4BFD130B26BULL, 0x5C981F52C885B778ULL, 0x19C3C9CD160C2433ULL, 
            0xF36E32EEA851DBF7ULL, 0x91030F6E8643FF21ULL, 0xA0E5C1F5A2E89125ULL, 0x45CE4F48FE4D9E54ULL, 
            0x05E5CF7AA4C2699FULL, 0xB7289EDF42A2CF26ULL, 0xFE1C4C33DA26602FULL, 0xA4BCCA169DE884DAULL, 
            0x85A935CB7C4763D1ULL, 0xF079954E60B93D86ULL, 0xB775CFDDE8F45AAFULL, 0x4D1A99D14A231043ULL, 
            0x246E41DC49483438ULL, 0x36F5B63861F93E5CULL, 0xF8B4FB7D654C16A6ULL, 0x01074EAAC3C9DF41ULL
        },
        {
            0x84513B6A7CDA0875ULL, 0xDB16F11BC8B99DF6ULL, 0x85C0FD44F89B4450ULL, 0x4914DC63CCA41392ULL, 
            0x5C4D4DFDB7E36B73ULL, 0x8097CA95FBF8B891ULL, 0x412F93374C2802DBULL, 0x00C0CA5FC13BC102ULL, 
            0x282379BB0878D7CEULL, 0xC10A4901202D184DULL, 0xF155D93A6E87E140ULL, 0xB0D61047E774881CULL, 
            0x3DE1A35F725A0561ULL, 0x46FA590C55041108ULL, 0x64A0A64016A3FFBEULL, 0x7AD620BDF0271FF2ULL, 
            0x196BEEB0D3EB5CCFULL, 0xC8E00FF8D66A89AFULL, 0x911B3C2D23F69536ULL, 0x927A949D45B0F633ULL, 
            0x03CD1D5BE7202A12ULL, 0x9C72BA669F7CB538ULL, 0x995FB59944B2E30BULL, 0xA50F8283D913E0E6ULL, 
            0x4818CDBD4D477104ULL, 0x50F772E2D6E07147ULL, 0xC25C4B982283D750ULL, 0x0FCBAD4FF14C9209ULL, 
            0xDFC4C034391BA4F4ULL, 0x1431791B9274EF18ULL, 0x7BD8972E425F4716ULL, 0xCC8833FCFF3CAFDBULL
        },
        {
            0x5B1FB4A3AD340A3BULL, 0x83622484ED84BB9DULL, 0x394420521CCBE41EULL, 0x3A31EFB9AE3A72B0ULL, 
            0x056614D7253BC6DCULL, 0xE7CB72E7507F19C6ULL, 0x3F87F03DF16434B0ULL, 0xD8D3EA8FABA82B70ULL, 
            0xEA0737CA6CBFB90FULL, 0x548914162E89E21BULL, 0xCB1685B6014E9D7FULL, 0xA0BC14D0E4337A05ULL, 
            0xA420BE0360BEDC60ULL, 0x900E1B512094E5E2ULL, 0x7817054DF548801AULL, 0x985C9A7645453B69ULL, 
            0x444CB2AD6DBE0873ULL, 0x50C0BA09998AE7C4ULL, 0x82A1965C1638234DULL, 0x4009657BC57BB92DULL, 
            0xC01ECD32D7BD280BULL, 0x1EF6E89EDC886293ULL, 0xFBCE78DB194D8387ULL, 0x0016C500A3F42C11ULL, 
            0x25E17DD3F471FBD7ULL, 0x644EA2D8834777F5ULL, 0x2CB3A4FCA528871EULL, 0xA0D8841138A04BC1ULL, 
            0xD7C9C920371DB18BULL, 0xDB3F2FD6E58D970BULL, 0x474E08B77CDCD9E3ULL, 0x0ECD7F594E845CDEULL
        },
        {
            0x38526A540C991532ULL, 0x8526990891F5F585ULL, 0xDB1FB28DB44BEE9CULL, 0x7CB0A1FFA7E7450CULL, 
            0x1832250F10B58F16ULL, 0xA0B8521D758D7AB8ULL, 0x80A1CBECC086953FULL, 0x541FE57A228344BEULL, 
            0x1E5874AD55C9C0E6ULL, 0xD0155E6056538BCAULL, 0x150673E1C159E5C4ULL, 0x0040EE098D4EF704ULL, 
            0x064ACA0D903831EDULL, 0x6235CB188A65DD34ULL, 0x9DF876A07A1A9EDAULL, 0x393096C8463A4D70ULL, 
            0xB2385B60877642B7ULL, 0x912A2EB996B8D1A5ULL, 0x274709025028E09BULL, 0xE3E9F049DE070F45ULL, 
            0x1167C90017E5D077ULL, 0x0E2CE45CE12E98E1ULL, 0x815F6086B412DFE6ULL, 0x8AF31D9BB3A620FAULL, 
            0x34A7ACF5127BF728ULL, 0xB0B587911A9586A2ULL, 0x951B54E17F8D70E9ULL, 0xB5848B8075DD560EULL, 
            0xD92B1006C278A450ULL, 0x0F3635F3FC565A0FULL, 0x04AABAB8FEF54BBDULL, 0x5FB5D90CAE0AC3D4ULL
        },
        {
            0x32807F0A5BD83C16ULL, 0xEA205CA7AF9461B8ULL, 0x92F9791F90B46AF4ULL, 0x653CA606488DA478ULL, 
            0x0DDCDCF4E53FF699ULL, 0x0B9C441C9700C6CBULL, 0x891551BB561A3F89ULL, 0xCB2E226FD0BDE9ABULL, 
            0xE0647C413234697EULL, 0xDA67D592FBE83AF7ULL, 0xA96114F545EB0C7EULL, 0x51CAE9E8552D38D0ULL, 
            0xA66836E84352C2CDULL, 0x2F19036D66F3FE54ULL, 0x0D9F6C611F689ED0ULL, 0x402B39F7C5DDB3DBULL, 
            0x65DA4153BA1F8F4BULL, 0x4DF0FD6BE7CF4580ULL, 0x1F8E53626C102E20ULL, 0x9277F1775A300D90ULL, 
            0x682712D8D7F3EB9AULL, 0xFE1F77E063C0AF1AULL, 0x0AEC309567251ECDULL, 0x133046BDC9EC5B15ULL, 
            0xC3D78C8A860DAAD9ULL, 0x99EB504AEF355C13ULL, 0x3A0CB23E12E15A48ULL, 0x4543A549FBF97C80ULL, 
            0x91E9469BF5C8BF84ULL, 0x14191669EB84DAEDULL, 0xBF4424D195A5B536ULL, 0x3741037F407D9C15ULL
        },
        {
            0xFB912BD61DAA8BF3ULL, 0x29E4B10368BC476BULL, 0x26A04D68ACF2E88AULL, 0xBEE123F3CF2BBBA5ULL, 
            0xC8248C2B2B242C92ULL, 0x1C1EF16C0E599B99ULL, 0xD8106ABF6B124D30ULL, 0xD47CCE36B6BB1663ULL, 
            0xB8422DD94A698256ULL, 0xEF14D678D2317EEDULL, 0x4852660519B6106FULL, 0xB7E9301D383E450DULL, 
            0x4E1A5DE9F4FFD3B7ULL, 0x533741FA0C0E7DA1ULL, 0xC60B04D367670FEFULL, 0x11311EE6F9B01DEEULL, 
            0x3336E36F2DEE3505ULL, 0xEB4CE9C9B29E8F0DULL, 0x914FE270E3D21F0EULL, 0x6B379D5AFC895DAAULL, 
            0xFE55B60FEA24DF47ULL, 0xF9615CD1208C20BDULL, 0x2D46EC7BAC457AB7ULL, 0x5689A706F0411776ULL, 
            0xAE61181034E2574AULL, 0x51A9FF14666C0932ULL, 0xAA162FA22385508FULL, 0x243CDC6196A9A757ULL, 
            0x149A6F43644AB008ULL, 0x90E7CFE63D1E3B3CULL, 0x11B819EFB367DBDFULL, 0x170633087A44B6D5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseEConstants = {
    0x739742655DE2CCB8ULL,
    0x7DA705B6003F1DD6ULL,
    0x56F8B748E3C9ACA3ULL,
    0x739742655DE2CCB8ULL,
    0x7DA705B6003F1DD6ULL,
    0x56F8B748E3C9ACA3ULL,
    0xABD03D38C2F4D868ULL,
    0x38F9D2BEAE278BB1ULL,
    0x67,
    0x46,
    0xA8,
    0xD9,
    0xBB,
    0xCC,
    0xBC,
    0x65
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseFSalts = {
    {
        {
            0x9D131FDDB8369941ULL, 0xC36B0E5EC19E6ADAULL, 0x5E94309C4C78F649ULL, 0x2B618B8BE9CC3844ULL, 
            0x9E70B39D40739E1FULL, 0x85EC0F2A80A2B72AULL, 0x42BB82BE1706E840ULL, 0x01EDC3EC76150FF7ULL, 
            0xBDDAD57A05CE2A37ULL, 0x3B1F1C3884C93863ULL, 0x0F5152A970C9525EULL, 0x41EF4BC0465ED7D5ULL, 
            0xD270B5D7D44C9423ULL, 0x69B605E15C526367ULL, 0x416FB228C6862467ULL, 0xA44D3BE87E781F3FULL, 
            0x6C4BBCB3846A6BB5ULL, 0x50890875CB107DF0ULL, 0x0633CC439CA64A93ULL, 0x332762448CA3BEA2ULL, 
            0x620FDAEAD9C96697ULL, 0xB28A3725BCEDA5EAULL, 0xB281A9CCFC2B16EEULL, 0x2AA8A4C69480D417ULL, 
            0x7B89E6EE8083EC03ULL, 0x33861B3C18184269ULL, 0x3B2D78824127D5AAULL, 0x4BEC53F3576F752CULL, 
            0x496C8BA98CABAD0EULL, 0x4F38E8A555A9A306ULL, 0x72939A36004149C3ULL, 0xE4603F922A5EE088ULL
        },
        {
            0xE356B70EB7B48D81ULL, 0xCA5F8895C6C41113ULL, 0x611779A07F6DE938ULL, 0x8C4141161E56A500ULL, 
            0xB39DBA9AAB0EDD99ULL, 0x9F9C90AB40A49C33ULL, 0xDAB09760A6E0181DULL, 0x9A59C8AD97F275A5ULL, 
            0xDDAED3C345661F76ULL, 0x60B7C98852618803ULL, 0x000380178C063139ULL, 0xA85E07425BCD0F5FULL, 
            0x1535497522C65340ULL, 0x0A93FF6E7D558283ULL, 0x1728ADB910A47D7CULL, 0xE4DA23854F0EE7A7ULL, 
            0x2DFD1F72505E9C36ULL, 0x745BC8DB46BCB771ULL, 0x1CEDEEA9C1ABCB8FULL, 0xD6EFCACAB59FF964ULL, 
            0x73777AE84491871BULL, 0xCCB490F18544C971ULL, 0x00D5D7009472C559ULL, 0x5A2B06F069427FF8ULL, 
            0x297E8CC6679DBF27ULL, 0xE8E431B584CCAA77ULL, 0x1CF5C67BC1BB4F76ULL, 0x4CC56E4616259387ULL, 
            0xEEC9D177C0128D85ULL, 0x53E0D58B6A3C1929ULL, 0xE839E7698AB96723ULL, 0xD6E01F905A2B5787ULL
        },
        {
            0x9936724620EC6AE1ULL, 0xF6AB09F851C9B270ULL, 0x2F1C97C346BF8B61ULL, 0xC4BA94FC7632F8E2ULL, 
            0xFA60DCDC127D91D1ULL, 0xF7E9D233C195DF0BULL, 0xBAF5E253960A33DCULL, 0x1801CDC9A1EDEAB9ULL, 
            0x4EDCBC1D1605CEF5ULL, 0x31F467D1BD601D74ULL, 0xC3D010301F828A75ULL, 0x5714B490A1B0EB73ULL, 
            0x2237CD1AE9B4C6C3ULL, 0x07BB79E223AB8632ULL, 0xBAA3C86F2CAD2B16ULL, 0xD92027EB7B146580ULL, 
            0xC39C03953E92A96BULL, 0x55D9D598D70D69D5ULL, 0xFFC365ACA15AE1D7ULL, 0xFD91B7FE94510148ULL, 
            0xE063B45901A78E6DULL, 0x6387C8B9E435220AULL, 0xCFFD0B9FDEE619F7ULL, 0x464B05213A6A4B73ULL, 
            0x6B827151C6B498FCULL, 0x4AACFD00904E0656ULL, 0xD80F159246E5FC86ULL, 0x2247939BA5DA4271ULL, 
            0x6DE0039572DA3E99ULL, 0xA1571CC689DB378BULL, 0xA6ECE8D1C92CF71CULL, 0x3DE194A8CA8A3A34ULL
        },
        {
            0x13AB7B3E64766988ULL, 0x09AB1E5DDC301AA2ULL, 0xAB2D3A100BE57774ULL, 0x9E33CBF31F81EC52ULL, 
            0x5C1C30D9AC015514ULL, 0x6637224F5427652FULL, 0x58C08EBBD95BBB62ULL, 0x26E3B30D6FA2F178ULL, 
            0xCC638C07F55730E1ULL, 0x8776926F5F017B1BULL, 0x9DCE4D727CE0038CULL, 0x92A033671B112BA0ULL, 
            0xDF25E66EDE9A1D44ULL, 0xD5A7E72DABEDDF70ULL, 0x297BDA748672847DULL, 0x81DBBF29630FAF78ULL, 
            0x17CAA58D5308BF72ULL, 0xE8785E2350CB00C0ULL, 0xEE4BE6BA70E738F4ULL, 0xBA6C3DC0C77142CFULL, 
            0x0B263AA24D4C5A92ULL, 0x706C827470EC2BD3ULL, 0x5B23A4EB42F0A9F8ULL, 0x443DC62F473F831BULL, 
            0x25E0AC55BB29A8BCULL, 0x73B25648FD4EFDFCULL, 0xEE9AB6D58EDE92F7ULL, 0x9A2246A34543FE09ULL, 
            0x699FE3FD27FEB0FCULL, 0xF335B8439304E854ULL, 0xD80158CFA58BAF56ULL, 0x2616A20BB77C9A43ULL
        },
        {
            0xACE1722E1606F465ULL, 0xD9C25B98D6A4F1D2ULL, 0x03B339C3014F21DFULL, 0xE4CD13A8714BAD58ULL, 
            0xC5ABE27687F61BBAULL, 0xDE7D310FB9F52BCFULL, 0x27D1A8D3851087CCULL, 0xD944871ECF3F781AULL, 
            0x931D0129B554C49EULL, 0xDC80502D8BA80437ULL, 0x897DF950A9458D10ULL, 0xA8B64DEF59344C1DULL, 
            0x70426C3387F8ACADULL, 0x4C605754A31E52B0ULL, 0x2EFD07391285D7A1ULL, 0x2D36FFF4989B8158ULL, 
            0xC1389C0A23364884ULL, 0xE82A59C6EFE43A1BULL, 0xC3E658C9CAFEFDDAULL, 0x56AEF07B5F278050ULL, 
            0x2AE737382E82BE1DULL, 0x20A3C52DE75F708BULL, 0xFED728A906BB406CULL, 0xC2121AFDE0C41F4BULL, 
            0x9A4A4BCBF04157F4ULL, 0x31CC0A06B00D8844ULL, 0xD9AA6CC0C611EE2BULL, 0x7E4DC86D4B41C203ULL, 
            0x101BEC8F71FF8D8AULL, 0x50183FDFFCCA9BC6ULL, 0xEE543B3644D4D93CULL, 0xD6CBA1348FEEE82DULL
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
        }
    },
    {
        {
            0xAB97079968AC54C8ULL, 0xDBA9361467598010ULL, 0xAB0159592F2C4D52ULL, 0xAE2387FE5A4FE839ULL, 
            0xF1924A486B72EFEEULL, 0x852F7B738A750BD1ULL, 0x8E6C62273B9BB389ULL, 0x8FAC8814D63060DBULL, 
            0x47C562343A2B3D30ULL, 0xDD306B9D921C9524ULL, 0x9B2FDC81237D22C3ULL, 0xB8A9BD39CE6AECF5ULL, 
            0x07D66E6BA5F41960ULL, 0x23F85754421072AAULL, 0x46D31387FD8A3922ULL, 0x0AF4E4FD78467BF5ULL, 
            0xADCC1CBDA6202290ULL, 0x44662F24576C311BULL, 0x7BD13DD2E606AA14ULL, 0x4C56B320996D2D95ULL, 
            0x9177EF52245F7FCEULL, 0x4E1FAD7CB5773950ULL, 0xE2F515B567A8F5F3ULL, 0xA75EF0B522529096ULL, 
            0xC28A7FE11617F14DULL, 0xD0C04318799FCA1CULL, 0x2714CB53C43CB9F7ULL, 0x757157A6E3651EAAULL, 
            0x23BE11EF4E93C313ULL, 0x83B9C855B12F7F74ULL, 0xA52207CD41E7CEE6ULL, 0xC72E6FF6AEB0D56BULL
        },
        {
            0xD2875EC71F4027CDULL, 0xBA0B873669609DB6ULL, 0x87EB75BFDA115BCFULL, 0x09D280237FDB1F2EULL, 
            0xEDAD17FDABE2CD17ULL, 0xB1234FBB9F57F2F6ULL, 0x329DDB8A980E2727ULL, 0x6EFEE42D8FDE8A95ULL, 
            0x93A7C2098FAFB46FULL, 0xBF7294A88AF9C4C4ULL, 0xCD8F45DD5968D123ULL, 0xB2CCBD8DDB8711D2ULL, 
            0x57E79074192278A4ULL, 0xDBBF0FE621C106B9ULL, 0xBFEAD685FF47750DULL, 0xF1F4731E6818A10AULL, 
            0x6E321C6345501583ULL, 0xEB57C72BE5A867E9ULL, 0xF3F4A618E00104F1ULL, 0xF8EE05749808738DULL, 
            0xF40F31F901E5654AULL, 0x6B694214A4B6ED32ULL, 0xB07F9FB3007A6C3EULL, 0x8B2CEAF5F778D84EULL, 
            0x78B03A5ED171127BULL, 0x079385E745942E70ULL, 0x194E1CAB61B41F7DULL, 0x22BC44F126265F00ULL, 
            0x9ED56BFF7B6AF70AULL, 0xA0A97FEB0F412D92ULL, 0xF2F9E4D3C7CC57ADULL, 0x933F9DEBED2E6021ULL
        },
        {
            0x392200784D0DC111ULL, 0x28264D491BB54152ULL, 0x66BC3ABD2C3CBDB1ULL, 0x4EA853825C103A94ULL, 
            0x19FE417739D17D11ULL, 0x84C4FC42D96EE919ULL, 0x40722D3FBF77B70BULL, 0x8E07F45AE7BB7F49ULL, 
            0x91D3444C2FAEECC9ULL, 0x6BC9D3F40F78E65CULL, 0x6E4FC0619D74267BULL, 0x700B91878DE72F4DULL, 
            0x1D240C02DFC06759ULL, 0x1651D89183E9FEEFULL, 0x48A79DA0B3A3E845ULL, 0xF92FD5CABA548C52ULL, 
            0x201FE549725056E3ULL, 0x148295472478B98AULL, 0x3CF474EAD93B36A3ULL, 0xBDEC05B37F980AF6ULL, 
            0xEDA1B3E45929636BULL, 0x96225E301FB3EAFEULL, 0x7F1F7616039235F2ULL, 0x9C226483A6B27904ULL, 
            0x6564E6690BCC52BBULL, 0x146746ABB107A9F9ULL, 0xD6C863BF06C334DAULL, 0x2C21DE65243847BFULL, 
            0x3B562AE32F0F1624ULL, 0xCF4C85F3CE6A21DFULL, 0xE8263D53DD4B3280ULL, 0xCA8EE795176F06A9ULL
        },
        {
            0x9687478A45D34AEDULL, 0xD1CE05C8DCD001E1ULL, 0xECF580753558DC67ULL, 0x875FD436EA3779C4ULL, 
            0xB9D21246D22A72CEULL, 0x681B0D215E220FDEULL, 0x1663EC9C4821FA72ULL, 0xD1063D53D8850E2EULL, 
            0x1A5F60A7FD438C6BULL, 0x39BB45CEC63DA4ECULL, 0x4EEB10D8367ADBC6ULL, 0x95D725FD3B99EFA5ULL, 
            0xE9D2BCB81575CCC6ULL, 0x30ADE098D2A93E4AULL, 0x5EE4C1EDBD62DB01ULL, 0x7A4B71E179FC6C2CULL, 
            0x53671698E6323343ULL, 0x95EE705E74E31DB9ULL, 0xAE9B01B9A01C7D9EULL, 0xFE1313039C9D0BDBULL, 
            0xCEFF11061D7F0D04ULL, 0x93E2DECF8DB46B48ULL, 0x94C479F5BE6EE312ULL, 0x200CC66D3F7B263FULL, 
            0xD997F44B70A82812ULL, 0xD180166AD23B708FULL, 0xC3698431368985BAULL, 0x2FF6DBF53C0F5318ULL, 
            0x6B43DA74D8484E7AULL, 0x75B2EA6877546554ULL, 0x77E8E16A0E5C3604ULL, 0x3910337C9985B1E1ULL
        },
        {
            0x4267287A82B08D5FULL, 0xF3769E8211B8CA53ULL, 0xD3D30D75DD0092D7ULL, 0xAF652C9F246365E5ULL, 
            0x1C3C168819A07A80ULL, 0x5195CDA216624ED8ULL, 0x281BB6AD80DC0582ULL, 0xB7523E0FC18A04F5ULL, 
            0x59E20BE1DC6E9C3BULL, 0xDBF0F2317ACF6E5FULL, 0x1D5554452448F52AULL, 0xBFD772B7041500A3ULL, 
            0x70E45AACF9D4D27FULL, 0xEFBB2D26CEE5DFF1ULL, 0x5C35347CC9B0DED2ULL, 0x4149784C78E7FDF4ULL, 
            0x8997A95F02E6A235ULL, 0xE6DAD9325DFA57CBULL, 0xE17B5140B8DDD77CULL, 0xCABA1863DDFB4CD2ULL, 
            0x1672BCFD706FDA9BULL, 0xB4F42F1ED1F9A085ULL, 0xC3E29A6471B72D46ULL, 0x6E7BE7D846776DCEULL, 
            0xF1438810FD6EA15AULL, 0xD3B6EF542D8B4DD8ULL, 0xBA4830B75E8A7422ULL, 0x65DF5179DBFF7EF7ULL, 
            0xB4327DD3484A290DULL, 0xE44EFEA5853AE333ULL, 0x583B4515090BBB10ULL, 0x51F8583B5860CFB3ULL
        },
        {
            0x1D25E12EAE27E347ULL, 0x067831E9237D8E54ULL, 0x1FCB759D0499C379ULL, 0x8F753EB8B1D41A20ULL, 
            0x3BABB1F3F56F18E3ULL, 0x913D9F87A55D940FULL, 0x0B8926833C3AC7D6ULL, 0x7AE4E0FF409EC3A7ULL, 
            0x707B736BE473BF05ULL, 0x1EE5751CCD5ABD64ULL, 0x04214C67D67A24F7ULL, 0x115B8DE9399DAAA9ULL, 
            0x91666A899E6FE7F5ULL, 0x1E40420D093A88A0ULL, 0xFA46D319254A3B65ULL, 0x136439EB0C5976ACULL, 
            0x3C8BE8F58F304BD1ULL, 0xC242851B66A305D6ULL, 0x5E5CC8FA94D510DFULL, 0x43A35A59AFBCA3BEULL, 
            0xFEBD859C56A6F1CCULL, 0x05860CCD376C9B46ULL, 0xFD96581122D648EDULL, 0xDBCEA2C22B1C7F66ULL, 
            0x5073E86103673DFAULL, 0x2EAFCD074CD1B802ULL, 0x68770D88398D9C05ULL, 0xB5045732B7166173ULL, 
            0x7C691A54E9A81B1FULL, 0xF87482D7189024E0ULL, 0x71D7334C243FB11AULL, 0x8AF84DFE9839F3AAULL
        }
    },
    {
        {
            0x4AA51369F519A84DULL, 0x9FB51D101C803C11ULL, 0x48B85248A824B3A9ULL, 0x79EA6A454C8C3145ULL, 
            0xDE445C306F4A08C3ULL, 0x9C6E58E727225576ULL, 0xCB1742AA11EC5842ULL, 0xAF7DDD704CDE30EEULL, 
            0x118F60B3D6D77DE4ULL, 0x95D9BE22CB2ABE5CULL, 0xDE3F612818AC7E0BULL, 0x1D8BD140099C052FULL, 
            0x8575B54CA30D2A90ULL, 0xD09587FC5BE79E01ULL, 0x68CAD9A7E9D2D46EULL, 0x69EFEDDD0970058FULL, 
            0x14F6A21C453EA710ULL, 0x1138F21C71D8BCB9ULL, 0x3DC6602DC0F09552ULL, 0x77E6FA88981C8702ULL, 
            0x7224DF154EDBFF91ULL, 0xFB7D0CD47C67F585ULL, 0x1237592D236AAC4AULL, 0xCB12075DC5A6CBD7ULL, 
            0xD51ECB06818CC957ULL, 0xE1224558E99104F9ULL, 0x58635468E07525C2ULL, 0x2AB1C1D584C55F54ULL, 
            0x57BA22013FB638C5ULL, 0xA072240264672681ULL, 0xD3D46E9D5CA3B2D2ULL, 0x14C8B7F540A8628EULL
        },
        {
            0xA04A6FCA5C5955DFULL, 0x653F1FCF85A1209BULL, 0x0337AD1E48EF0A05ULL, 0xB694E223D9006F2CULL, 
            0x8F9A2611BF364CCBULL, 0xA5AE8E4588B6367CULL, 0x3C345F082300FADBULL, 0xE87E6EF353CC3898ULL, 
            0xE3D8DB8D4A404826ULL, 0x77FC7927AB5AA68AULL, 0x502B1FFEE0FF1CC1ULL, 0x3000E3EE25B97862ULL, 
            0xB4E359978F6187A4ULL, 0x6BE4F31F1A824073ULL, 0x67C64B7A9D356EFCULL, 0x525A605F6618ACCBULL, 
            0xD7A8484C52725AA0ULL, 0xFB23212AF828859EULL, 0xC29D2A5C7BBC4BAAULL, 0x16F1A0D84C357455ULL, 
            0x7A8D0C03C2975B8CULL, 0x4462FF7FD943A3A9ULL, 0xE93BB7FF72AA7F25ULL, 0xBE6814519BA7DDF2ULL, 
            0x374F70800A9FA545ULL, 0x786A43D2B80D568BULL, 0xB75B5477AE04AEA3ULL, 0xA7D0FE4F1CE16466ULL, 
            0xF5E7D539F142B3F0ULL, 0x513D77A7DDF30F17ULL, 0x74F907986D5A0796ULL, 0x3447A4893FC386BFULL
        },
        {
            0xC6B5AAE1FFE4531FULL, 0xDFA04D10018417D0ULL, 0xC342B20B0DA502CFULL, 0x426968F320692E56ULL, 
            0x398CD195D17C072BULL, 0xDA0C403AE955A8EBULL, 0x137448E23106732EULL, 0xCE86F1D476C99728ULL, 
            0xE9A283F4ACEDBA7CULL, 0x457B689C98FD4FE8ULL, 0x56961905CB620901ULL, 0x15E6F1F5675704C6ULL, 
            0x56F96C71E0D983B3ULL, 0xB4DB71A8235C97DDULL, 0x0FF8AF3C37DE1AEDULL, 0x46F53A81572AA487ULL, 
            0x1584ABA798F6E245ULL, 0xB83262F74101859CULL, 0x4C674375DD36D8A7ULL, 0xC51ABE1EEAA40881ULL, 
            0x0D082EFFB8AD48F2ULL, 0x1FA8C2FC2E744AF5ULL, 0x2A12E1E8064C65B8ULL, 0x22A0FCAF1A6B0A85ULL, 
            0xA704994A8DDF42E0ULL, 0x0941997D56C0D455ULL, 0x02E75B15207C19A9ULL, 0xA3F6F79AB217B7F9ULL, 
            0x9E80C6CF7303E772ULL, 0x2E805E2C8F597EE1ULL, 0xFBD80250106381F4ULL, 0x169DAA6649419228ULL
        },
        {
            0x9377048C246C005EULL, 0x8797A6033B20FD3AULL, 0x6835D572BF02E8DCULL, 0xDAA086EBC49B477FULL, 
            0xD5440F0696CB2A03ULL, 0x4F4C61F1AC12E421ULL, 0x00BBC1617CDA5174ULL, 0x769694D37C5FCDC6ULL, 
            0x70C5A83E5529CF26ULL, 0x8297D798FC3786A5ULL, 0xE217A2BA311A0C57ULL, 0x8C58CF31D06FF5F2ULL, 
            0xCB404AA0BE24FB25ULL, 0x335DA7322F3E776BULL, 0xAC1C83F5A494EDFEULL, 0x5B4FEA412F0D29FEULL, 
            0x17BC4EC02D881C48ULL, 0xEB9019D99B2E1D34ULL, 0xC119AF41BE6E1EA8ULL, 0xE7FA414168849868ULL, 
            0x45D1591C37A7F7CDULL, 0x198AED2F0FE9FDE6ULL, 0x6F851C668C42C5EFULL, 0x1450543966F96904ULL, 
            0x1D63846ED35A6624ULL, 0xFACBF0626F1333ABULL, 0x4B0DC25B74319602ULL, 0x98C459415888DD55ULL, 
            0x217A961ED31F93B2ULL, 0x35398BA250CBFBE8ULL, 0xCD08792502ADB7C0ULL, 0x29ED32B2D859BA36ULL
        },
        {
            0xCA222C086599458AULL, 0x5B7C76D4C487659BULL, 0xEB36E1C775568E1EULL, 0x164EA6973FEC0ECFULL, 
            0xFC01E19289037A87ULL, 0x9C38DCEA20DDA164ULL, 0xFC87852845F3C1A8ULL, 0xC0783C72E2D909AAULL, 
            0xA81DD19792BFFD3DULL, 0x8DD6EC7518A0D37DULL, 0xA46127217B1A256FULL, 0x7AD291161B3647AFULL, 
            0x1575CCBDE2B44042ULL, 0xAB00DA61918FEBECULL, 0x5FBCB523135FC246ULL, 0xC55A8510EAA3A5E8ULL, 
            0x09ADA949EB6170EDULL, 0x957DB0CED27F4892ULL, 0x72BC876781F9095FULL, 0xC64F22A9E9D1B22FULL, 
            0xAC5C383348A96F4DULL, 0x9C7CBBC3811BF2D0ULL, 0xA5B41EF6D0539AB0ULL, 0x694CAD722D42969FULL, 
            0x05ADF2A555159071ULL, 0x2626E7E80BF5E2D3ULL, 0x726B8E0EDFFD22B2ULL, 0xB6012DDAEA3AC91EULL, 
            0xE0918AECF62D58EEULL, 0x4F0D43F488D054DBULL, 0x65656A870AE7C198ULL, 0xD324DB4DD3E8480CULL
        },
        {
            0xA6BEF6F51E80A4A9ULL, 0x4B2000DCA9B31B5AULL, 0xE1F1F2E73BC6FE84ULL, 0xFF9F327BE754DFE8ULL, 
            0xD849365D956B5EACULL, 0xD2EB76D203B4571CULL, 0x02E9B5224A5D39F3ULL, 0xFF4D557AFB9610BDULL, 
            0x18298A41ACB0AEB0ULL, 0x6107EABB269CE016ULL, 0x6234BB6EC5022568ULL, 0xAF3A464392F60123ULL, 
            0x615CCCF924F3EC73ULL, 0x082DE9AC9C27D1CCULL, 0x30EB4BA62062D208ULL, 0x9D729746A5459C47ULL, 
            0xA1D368B10A6EE4F4ULL, 0x167F80316019A3A0ULL, 0x14D45CA528E8B5C3ULL, 0xF5BFD8BF2344406AULL, 
            0x3555CF7BD91BA8C0ULL, 0xE59A2B1A8A04166DULL, 0xDF113621DFE01E29ULL, 0xEE3AA2EBFC58770AULL, 
            0x1EA94EE08F0929AAULL, 0x0A5FD55631ADFC89ULL, 0x2CBECD5C746FDC8FULL, 0x1840D068F6B011B2ULL, 
            0x4F1C0E0A1D614CA1ULL, 0xA0A71400B7E58EA4ULL, 0x362C44D65D8E4C14ULL, 0x61C622E1D565C795ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseFConstants = {
    0xCB37C93A5AE442F7ULL,
    0x3469C2347B3D2BF9ULL,
    0xAC5545DE60FF21B0ULL,
    0xCB37C93A5AE442F7ULL,
    0x3469C2347B3D2BF9ULL,
    0xAC5545DE60FF21B0ULL,
    0x894B990030B4AAAFULL,
    0x42AD8D3DC79BB34AULL,
    0x11,
    0xD5,
    0xF7,
    0x12,
    0x1F,
    0x41,
    0x4A,
    0x85
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseGSalts = {
    {
        {
            0x204804EFACD61701ULL, 0x635B03084CF97247ULL, 0x3257768DBBFBE8CAULL, 0x6D76F87B3288A1A3ULL, 
            0xD8C5C8EE40F40FC4ULL, 0x35E05F31D4AB5331ULL, 0xB5186CBED69A0907ULL, 0x06A4259B42C41857ULL, 
            0x43F0D192888BD0F3ULL, 0x81D894E6AB755BABULL, 0x536003C9035066DBULL, 0xDE02C2589DEBF7BDULL, 
            0xD1C4D6D855812E2AULL, 0x9F11F3EB56F0CB8EULL, 0xF1CAEEBB8D8BD6C4ULL, 0x2FCD255C37D25D29ULL, 
            0x69EE915BCA5D6553ULL, 0xC1E51EC4E2C36670ULL, 0xDEC822F75C781959ULL, 0xB58CC99889B0154BULL, 
            0x485AB97B35A7232EULL, 0xA7A143AFDF228CCAULL, 0x87471521D0D56C9CULL, 0xC62D64168961E00DULL, 
            0x33201125F700B248ULL, 0x87E77D703C13E727ULL, 0x47B7895A96316E71ULL, 0x377FFCD4F9FAB91FULL, 
            0xFB5CD9EF63AE8949ULL, 0xCB7AA4C10D7A7435ULL, 0x288B52C877ED4C62ULL, 0x26BFD6577756C064ULL
        },
        {
            0x022EC899E112540FULL, 0xD0CF23F8839B1D23ULL, 0x5D10E4E93FEB6DC8ULL, 0x2AAED7838BBB24C3ULL, 
            0x97498357C5B9AF34ULL, 0x6E426B2DA1569D8FULL, 0x9A0B0857C25257EFULL, 0xAA750D9CBE2225D4ULL, 
            0x02F74C8A3F4AB13CULL, 0x3684B9EF5523B60BULL, 0x5E16A92F8224E2EBULL, 0xEFBED2B670C31723ULL, 
            0x09EDA0C9A06DD31AULL, 0xFB5B92DC3F1780F5ULL, 0xBD21B339CABE3A24ULL, 0x236C2FAFC2333E30ULL, 
            0xE1C0F91500B1B35CULL, 0xBA7FFF768485467EULL, 0xF25362B0202098F6ULL, 0x6919924392C78E52ULL, 
            0xA2A301005239D2AAULL, 0xF268643B76C1BC3FULL, 0x0AF4C7A7476CA513ULL, 0xA7B6AFED25668416ULL, 
            0xFCA9C2E3D43D3739ULL, 0x69E744EBC49FB70CULL, 0x31AF47DCEB1FF29FULL, 0x832CBEC59BA693D4ULL, 
            0xD82563957C519922ULL, 0x0B59C4D205B54075ULL, 0x21CB5B75926DD430ULL, 0x1BAEC78CE36D147DULL
        },
        {
            0x23DE52881FE8EBA8ULL, 0x4984A3FE0A1B5C23ULL, 0x3752D973F972F825ULL, 0x90FEF86916D25B5CULL, 
            0x763B71C3C0DF0798ULL, 0x7470CD368F7164F1ULL, 0xA3DFAA9F708F57F2ULL, 0x54BBF54EF6FDA8E8ULL, 
            0x4336737842BF3F64ULL, 0x59CCFA0C24A3B951ULL, 0xBDC50FB66F0A257CULL, 0xFE29ACCB694F327CULL, 
            0x343D00ADBF14BFBAULL, 0x6B5C6D4796984EC1ULL, 0x2512EE59E5F23650ULL, 0x1B881AFFB7864AABULL, 
            0x39CD2ADC776B5F00ULL, 0x16C7FBB1AA61CAEEULL, 0x3D6D2B7EA417FEA0ULL, 0x0B190CE178A7E42BULL, 
            0x84064AEF8DDF6748ULL, 0x12887FB86CA6F041ULL, 0xA4DC2FF106B0307FULL, 0x22B4CCBDF16F4BF6ULL, 
            0xF0DD8C6465AF2D29ULL, 0x5E51410A1357F35CULL, 0x51F20824964DD248ULL, 0xB52B49B5D0A3E524ULL, 
            0xC0A407853126240AULL, 0x3616F8753CF4BF83ULL, 0x89B75DC4E6407FF1ULL, 0xAC9E5BD54FFB6FF2ULL
        },
        {
            0x9B8C014F40D07BCDULL, 0x79641B835FBB37CEULL, 0x7F2BFF8AB253FBD7ULL, 0x451DA7C43E029033ULL, 
            0xAF494C3D7302AFC2ULL, 0xCC5D3C60D30E13B0ULL, 0x043A4DDD15DEDCD0ULL, 0xE5768DE545330ADDULL, 
            0xD433632CC552C423ULL, 0x89B808D615056157ULL, 0xB7DC8798445FB4D4ULL, 0xB7DC56033F8CF673ULL, 
            0xFCC61F08D7D76C01ULL, 0xC132B5ED53AE739BULL, 0x3CDB5A418ACB6D15ULL, 0x5D82C9AE76AAAB2CULL, 
            0xEE07A1CB9FC9E46EULL, 0x6D25CA36A92D5397ULL, 0x13712CF76E802B60ULL, 0xBA443454504687CFULL, 
            0x723F5FD6CE0A88BFULL, 0xA4405F9D775445CFULL, 0xC4AF2CF115E77D3AULL, 0xBE04C45F4CD9F36AULL, 
            0xE44D9AF1DD1F0A72ULL, 0x35E20950D574EFB6ULL, 0xCE6631B63F0AFCA0ULL, 0x5AEC6E837FC370D7ULL, 
            0xE321B5E162008BF6ULL, 0xAB77A76A94D771E2ULL, 0xF96CE1BEFEA197FCULL, 0xA88E1702F06F408BULL
        },
        {
            0xE8B31D0F468BC670ULL, 0x0FEEE7793F16490CULL, 0x63F6A8F68E856BD8ULL, 0xC886AB244C044941ULL, 
            0x003C65596C9976CFULL, 0xDAFB6927E9B1EB50ULL, 0xE022D1CD76B60667ULL, 0xCC367678904B6FF2ULL, 
            0x66C884EF10F1723FULL, 0x779EA9CB6D17C90BULL, 0x5CC396DC789786ABULL, 0x6AC7BE9F44C7A69EULL, 
            0xBEFA0C92109DE3F5ULL, 0xBC058F79958F2885ULL, 0xB8A63EA49D207786ULL, 0x72104D7D51C12413ULL, 
            0xA9E7727518740F90ULL, 0xEB58954D7B9E3965ULL, 0xC4779DB7B2A3FA82ULL, 0xCEA92343F99ED2E2ULL, 
            0x191D1BEA99BFA34CULL, 0x7E4FA9265C382ED6ULL, 0x083896D733130953ULL, 0xF832DC6F050059C6ULL, 
            0x5103E924279BC22AULL, 0x856863B11D7AD851ULL, 0x779178EDE60C6B15ULL, 0x66A33BBC83177FC7ULL, 
            0xF25261193AEED757ULL, 0xC506B0E539618B6BULL, 0xF668D91C70BE1B7AULL, 0xBD79AC28693B8DB3ULL
        },
        {
            0x9349341F70B279E1ULL, 0x537E0115C62CB87DULL, 0x4930E8C32B4B9E38ULL, 0xAB1B5B1D7A6A909BULL, 
            0x342246672A47031EULL, 0x66E0802910F96C82ULL, 0xE1E58F5938DCBD79ULL, 0x7010AFC60C1DFE60ULL, 
            0xA3944E81D6E667D5ULL, 0x16F5310C61444F08ULL, 0xD8D8970DC33AAD20ULL, 0x824F24486A6152E8ULL, 
            0xE67F55CE7D58BD89ULL, 0xCEB18289DAEF0AB0ULL, 0x70BD84F111F0C1D4ULL, 0x53295DB739998403ULL, 
            0x8A1C2A7844562B80ULL, 0xE4C11715637209C9ULL, 0x16BD8C76ED57EEEEULL, 0xD1A2D53892866910ULL, 
            0x504259EA76B75804ULL, 0x6229932DF3FEE7B4ULL, 0x1F9A360C40406FEBULL, 0xDEB8D477CD9B2741ULL, 
            0x8D65BA720A5870BEULL, 0x1716FE001FAC4950ULL, 0xFA8745DB68A0B2C4ULL, 0x96F5A502225CDC6AULL, 
            0xAC9AB518F3778B96ULL, 0xA946E52F2242795AULL, 0x31891FFEF273FDF9ULL, 0xEFDC1BF289DDF7F2ULL
        }
    },
    {
        {
            0x124B3D07D59104F1ULL, 0x86E666176DD8864BULL, 0x0FF8B63ED41B412BULL, 0x4671B967CD811C68ULL, 
            0xEB37C7B6C946FDCFULL, 0xEAFE36A4BB58C1D1ULL, 0x6AEFC5CD157C2AF3ULL, 0x7E9E8FC4AB341B93ULL, 
            0x522E3027B64AEE3EULL, 0x35EBDDFDF58C905FULL, 0x8EB3C49FBD96CDD3ULL, 0x1EF3B3FADE2DC1FFULL, 
            0xAA7D08B673C9B608ULL, 0x81D3B8988FD6D874ULL, 0x863E98CE4EFE5B6EULL, 0xFC7CD328C5EBF154ULL, 
            0x54D24565C88B26F1ULL, 0x1EEA57F562AB23DBULL, 0x5AD61D447A563019ULL, 0x891CAD3AEB11FBA5ULL, 
            0xE58482455DF7F6ABULL, 0x81E311EE6EBB3334ULL, 0x2E253DBDF88BB228ULL, 0xC37648BDBD08A2C4ULL, 
            0xC4BC805B7639DD9EULL, 0x393903F6C9AF4D71ULL, 0x083F246021017EA4ULL, 0xC37B2AC38973CBD2ULL, 
            0x5A06767D0BA02139ULL, 0x6C4000C4D6C7DB30ULL, 0x6D77D861497B909DULL, 0xC7655DCF35B693C8ULL
        },
        {
            0xF0FF3DC32FC5A2AEULL, 0x507E1FD94149934AULL, 0x442263B6FF050F0FULL, 0x3A1E9929333E0166ULL, 
            0xC000DD490F7FA290ULL, 0xDBB3E2877655210AULL, 0x8117C86B8909E8E4ULL, 0xA10480FE120D652BULL, 
            0xC6161E679A78BAF9ULL, 0x388F2DD5041B4319ULL, 0x594B82E6DBF29717ULL, 0x67375CE6427358F0ULL, 
            0xD31274AE469EC06FULL, 0x0949513B2AC57AEFULL, 0xB11416B9F010FBBEULL, 0xB65106994324CAC0ULL, 
            0x5F6805E2A06FDC47ULL, 0x31FF149578C9F5ECULL, 0xF3E09BF8486FC95FULL, 0xB61A8DA2D41D5DA2ULL, 
            0x248834EACDC4F36AULL, 0x593CC88C928F815AULL, 0x0A7F753DB0E23193ULL, 0xA67B8843A7DFA310ULL, 
            0x50C5A96FBF266E3FULL, 0xA64546AAADA6AC4FULL, 0x5321DD739D14CF12ULL, 0xB0A2A2DBCA13280DULL, 
            0x6DE15F6713C031AEULL, 0xDCC678C8D3A85031ULL, 0xD753FA4DDD52381EULL, 0xC5EFDBA5AB559D7BULL
        },
        {
            0xE127A56BBDA8791EULL, 0x168B5280CACAF7D5ULL, 0x242C714031C49D39ULL, 0x602176D85E644633ULL, 
            0x3CA4896572010DB8ULL, 0x95207BA00B836332ULL, 0xA959085E1D78AB09ULL, 0x3CB9AE55A8C7443FULL, 
            0x90A699E137EE01D0ULL, 0x9544DCE8FE7EC8FDULL, 0x6F28955D71EA8371ULL, 0x11E6F45F254E9C83ULL, 
            0x91318B04A32F4611ULL, 0x46637F83FB4420ABULL, 0x7DCDEFC1491AC244ULL, 0x2FE47C3D35634365ULL, 
            0xA66D17DF830FC185ULL, 0x8D3AED850E906465ULL, 0x31DCD80BD466E3C6ULL, 0x7DB5F326D7D3BDFFULL, 
            0xE4D1E43927ECE3EDULL, 0x34A2918376829268ULL, 0xDE01FB88B5BE7488ULL, 0xFB1E9B70CF8157CDULL, 
            0x7916BC9B98BC350FULL, 0x90B2740A0F34C53AULL, 0x66978AE9D373796BULL, 0x04632E42EEC2080AULL, 
            0x8A631DFAC171A34CULL, 0x78CA7620F414AEEBULL, 0x218244F06A82F02CULL, 0xD386ED3B83BF0268ULL
        },
        {
            0x6F72690B219BD44BULL, 0xB4BBD5EA4BB20A46ULL, 0xAE9A455BB3EA1619ULL, 0xEA62D1D722F65781ULL, 
            0x2A49A483C9F1BAA4ULL, 0xBE440C723E327FD6ULL, 0x93E050630A0D2C35ULL, 0xE071D593CAB7D760ULL, 
            0xB9A73B2E099AACD4ULL, 0x60CBCC9EA71E2E03ULL, 0xC3D2705D0221D8EEULL, 0x5BFC59DFB3EC8174ULL, 
            0x7C61A3BBEA0AC748ULL, 0x35636140C925316BULL, 0xE1C00C53551E61CAULL, 0x3C63BAFC95BC9F96ULL, 
            0x055F88189E5EAEC3ULL, 0x873B06354B609E9BULL, 0xDFAE444F7AEFCCD0ULL, 0x1D9C76422712577FULL, 
            0xF33732FF22E40DC7ULL, 0x5B1BC482DB3B6BDBULL, 0x9B546CFFDBE5CBD4ULL, 0xA30456B23FE485D7ULL, 
            0xA5CA62869A957B76ULL, 0x3D143620544D9724ULL, 0x5B871445A9745F26ULL, 0x016C1910464D3CA5ULL, 
            0x0A3A55161457A070ULL, 0x1F885060C879D292ULL, 0xD9CDC17560BA5311ULL, 0xFE3D38706B2A115BULL
        },
        {
            0xF7690F14E9AC14F5ULL, 0x29E4725C85638686ULL, 0x2F399FF9E8B8A6B0ULL, 0x7969B337C938F340ULL, 
            0xD8C3D2F2EF0F072AULL, 0x3CAE99442C0A3A09ULL, 0x01D6C00F36FF260CULL, 0x0D6BA9CEE790E4A1ULL, 
            0x2B55950125F8C00FULL, 0xA9B3677DEFA3C003ULL, 0x4C5792367997BB6CULL, 0x9F3B615BC69C7070ULL, 
            0xAD52D52B3FD6E7B3ULL, 0xF5707643FC24FCFBULL, 0x2A9A34CD0F4AAC37ULL, 0xA8DB5AFE46B5442AULL, 
            0x9788D41622F79952ULL, 0x8618AB3705944F5EULL, 0x9984B859A9BB26ACULL, 0xAE239E6114FD80F2ULL, 
            0x14466B4073541B13ULL, 0x2940CC8F100ED08BULL, 0xE4245FCEAFA550B8ULL, 0x5533AC587BCE2ADBULL, 
            0x970498E43523C0B4ULL, 0xD7C2F19CDA037809ULL, 0x731A533A139C66F7ULL, 0x38EFE6FFB67734F0ULL, 
            0xB5EB47C2DF7692A6ULL, 0x1F174C56C44EA619ULL, 0x20F4373145EBB403ULL, 0xA0461FD6FC266263ULL
        },
        {
            0x3909F4AC184087B3ULL, 0x11E15967AE166A05ULL, 0xB7678E4F3AFE0F0CULL, 0x027FF24A71DE4C17ULL, 
            0x5514DA642D86C170ULL, 0x73E20EF5B3A91C00ULL, 0xB947C1708A7DF3F7ULL, 0x03CED4DA2D997BC3ULL, 
            0x61C2E65B71800A10ULL, 0x39B7C7B55287013DULL, 0x75871D9DB2A9E17BULL, 0xB350774E95310AB9ULL, 
            0x6B79C473DC085F70ULL, 0x819BFDA42CA0EC7FULL, 0xB64703E7F729FA61ULL, 0xCE3236E1690A8067ULL, 
            0xD130F85DA6505D49ULL, 0xEB0F1E88CB05D639ULL, 0xB7B99A35EFE71EDAULL, 0x06B2F2A08C894093ULL, 
            0xF1976E971B49AE8AULL, 0x7A438CC8B959332AULL, 0x28015A9A142C1CE2ULL, 0x270DB99C3DBC1629ULL, 
            0x543A4154D420BA62ULL, 0x62E539BF47161F4CULL, 0x2093174A893C6C62ULL, 0x4FB246B312F6A299ULL, 
            0xDE59B3EFC252E88EULL, 0x85857F5202E17904ULL, 0x7C8800BA542B6DD0ULL, 0x6AB249F9A942BCEEULL
        }
    },
    {
        {
            0xCF3EE7C95BAA55B2ULL, 0xF39006FD0D7B7D6AULL, 0x568DEE7DAF2C7D78ULL, 0x13FF18BA62B9202EULL, 
            0x67F74C7079FE28E8ULL, 0x297767ABE58A50DBULL, 0xF54FCB92F81CDD21ULL, 0x74B9C0F908C863C9ULL, 
            0xF92338C383A9CEF7ULL, 0x33E6FDF0EB08F77BULL, 0xDFAFE9E71B59C036ULL, 0x103F2EA57083FC6CULL, 
            0x43B8DC074769D86AULL, 0x0273354E9385FDB3ULL, 0xDE0240F2893374A9ULL, 0xBCDB8035E72E49D3ULL, 
            0x9375E9751EA862C8ULL, 0xD34497DDC7360744ULL, 0x08DE485CAFA38937ULL, 0xD06E3C758F6151F5ULL, 
            0x02C0C7281B4CB0DDULL, 0x25D9007232398FDEULL, 0xFA8782CA72B04337ULL, 0x5821B285F120EBFCULL, 
            0xF9104C3DAE8427E3ULL, 0xAB5A3F263C8F58B0ULL, 0xEB19C71F9DEF2D70ULL, 0x2C9B60ED5DA45AE9ULL, 
            0x190275F3B37EE01FULL, 0x317E26A423A343A9ULL, 0xB322821A07BBE52FULL, 0x49EA756FA3E5D72AULL
        },
        {
            0x8E9225364DE8A9D6ULL, 0x48FC62FD68D9B286ULL, 0xA9666531622FAE45ULL, 0xBFA2D4519C1E4192ULL, 
            0x8DDDB6A82DC8CAD9ULL, 0x5C3E7AE76A653C91ULL, 0x4D2D8EC3BAC29C18ULL, 0xC75BAB5CA7E34FB8ULL, 
            0xC7452FB4D7B15CADULL, 0x60755760A9B5F35CULL, 0x804BB667CF80BE4FULL, 0x3894F67867933A9CULL, 
            0xFC73D8D7A1976730ULL, 0x94ADF2C018AE3F12ULL, 0x3B738A4E7A43C16CULL, 0xFF67137A514ABDA1ULL, 
            0x1ED8CCCF502D7D36ULL, 0xC1D561BEA8377099ULL, 0x488DF6DFD0996C51ULL, 0xD510AD6418433538ULL, 
            0xE764E800B566A3FEULL, 0xA0911478F8CA6F9DULL, 0xC44A816B74839F56ULL, 0x17FBDDB85F535E51ULL, 
            0x3CB9300B5D271BE9ULL, 0xFD6B18ED6BD249B4ULL, 0xCC3BEE01672EDEADULL, 0xC53F9C48A862731BULL, 
            0xDC66529BB0798573ULL, 0x5FC36FBAB63AD234ULL, 0x68A4026A32180E49ULL, 0x842D04BB8D20E5E0ULL
        },
        {
            0x1DE7E8560A00B6E4ULL, 0x2FA2E2FEB2C4B668ULL, 0xC3F2EC7BD7A303EAULL, 0x23F4AD033B2F8CBBULL, 
            0x806E7F8D75B6641FULL, 0xF3872D7E3027EB05ULL, 0x8C1894AC6F3D2741ULL, 0x94D0E88B5130676BULL, 
            0x5F79C317D744881BULL, 0xA18AB186F931783BULL, 0x209CE68A47CB1D7CULL, 0x3DC99BE3F9838D55ULL, 
            0x22307B72045E6B6DULL, 0x167B2BAE4403ACE4ULL, 0x279E82860F1DD3A1ULL, 0xEDA86E9D171F9952ULL, 
            0x2ED69E43856857F3ULL, 0xA5F64BE59FDBCA20ULL, 0xB486A19D4B3485E0ULL, 0x55B3B5B6DF1F094DULL, 
            0x23E165BAA6667080ULL, 0x0EA3B22EA6E2AEF1ULL, 0x6A1F0B991A38A909ULL, 0xA76293F046B2D2D2ULL, 
            0xF0B45E5853A2A562ULL, 0x702333456FA90D95ULL, 0x95B9E6C2E9A21B59ULL, 0x94B841EB972A2059ULL, 
            0xC67832D105C0A097ULL, 0xEBF59864135014DBULL, 0xDA89282D2232AB08ULL, 0x7A7B63ACF71ADC13ULL
        },
        {
            0x18D48C3EB4D0DFA7ULL, 0x470B5556F2CDBEE8ULL, 0xD2A2C98EE221AD5BULL, 0x2CCABF7B938345C7ULL, 
            0xA8EA1699D1C524F3ULL, 0x665DB0D729EEFCCAULL, 0xAAB23CD2456E3A5EULL, 0xE6E32D1EA9B78424ULL, 
            0xC643E2238F86F4A9ULL, 0x60E78C1364F3F587ULL, 0xF173D625A009B0B3ULL, 0xAA3C5213A955F9ADULL, 
            0x9B39AF1B059BB08FULL, 0x69F8298F0B9E5E90ULL, 0x7CC5C2C4955E35E7ULL, 0xED088DED8246F8D4ULL, 
            0x5CC01F7EDD85501DULL, 0x0958F0BD3FED062DULL, 0x74235EFE853BD6ADULL, 0xB037AE85037A5BBDULL, 
            0x0FCAF946D0B3AA49ULL, 0xD5686814EC9E16C4ULL, 0x57A9E53E701BCB7BULL, 0xDA99D0649F71438AULL, 
            0x996C685EFA14CF64ULL, 0x974ACB6D60C40858ULL, 0x8FF047E94874D48BULL, 0xEA74A4FE71188108ULL, 
            0x9487B96937E0B750ULL, 0xB7317D55D2FFBB5AULL, 0xA9381E2F8751064DULL, 0x9AE9842896F614EAULL
        },
        {
            0xB8D6314AC5835E2EULL, 0x539DF4CBA7272519ULL, 0xC8225DBED5480ADFULL, 0xA6E24B00E30F4E11ULL, 
            0x5AEEB48CC282DC4DULL, 0x19418EF27B1E14A6ULL, 0xD55E13529FBD4862ULL, 0x60826F0B55A93C27ULL, 
            0x5C74C1CC98DC2945ULL, 0x810C57E0735DFFD8ULL, 0x225F15893968558CULL, 0x19806EC1F1108D9FULL, 
            0xAEB10C5677576E1AULL, 0x7AED51E57302A713ULL, 0x8EBA675F7A015718ULL, 0x6EEEA16D15C62BD4ULL, 
            0x5A0B7CBFC6F03BFDULL, 0xBCD6ABBC472A20ECULL, 0xBDC584F11A89B925ULL, 0x9A757B9EB222A927ULL, 
            0x114639DCFCBF202EULL, 0xB1D991F2F7F53D3BULL, 0x750A7DE918884FF2ULL, 0xC315732CC6B1773CULL, 
            0xA602AB57076E54CEULL, 0x86134561E9589A5BULL, 0x11A8E6BD8BC2714AULL, 0x8CC99589852EA00BULL, 
            0x812D8F789E1B912FULL, 0x50D8F848FCD26052ULL, 0xA62E12BBC6529C3EULL, 0x7C78212536140E3AULL
        },
        {
            0x2CCC2C788C2AC5DBULL, 0x272024A732736364ULL, 0x22EF302A79F2BAC7ULL, 0xE2ECEA228F516947ULL, 
            0x8CFD427389160FD4ULL, 0xC70F25C3F3F55762ULL, 0x086C644B610F3A43ULL, 0xC2E2FA8E90A1BC4BULL, 
            0xDC4E91860E2F7D58ULL, 0xDDF582FBDD3E0060ULL, 0xB8154AFF08F4F0CCULL, 0x336D0686EB859A37ULL, 
            0xBF21F8A1143FD444ULL, 0xEADDC51B888AF826ULL, 0x5316CDE7417FA29BULL, 0x11D00D2DC769447CULL, 
            0xB2E43C2076DC6C6DULL, 0x0540282890AE34BEULL, 0xD04707887BC330F8ULL, 0xF493B8EE149F7A7EULL, 
            0xEA2E61E7CA1F43A9ULL, 0xD4372720E271782AULL, 0x831274CB30D9B78AULL, 0xAB788A05170E8E06ULL, 
            0x8E48E2AEEEBD8038ULL, 0x46551CC79234CB8EULL, 0x94589D3F58286D1FULL, 0xF3A811A2498EADC5ULL, 
            0x6682234837DC105EULL, 0x9A10DD8E5507D04FULL, 0x5FB4C6DF900F7E07ULL, 0x64C1D1F11024655AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseGConstants = {
    0x7F0389FF7AEFECCFULL,
    0x741A0BEAE6481258ULL,
    0xB0DA5E4B3443349BULL,
    0x7F0389FF7AEFECCFULL,
    0x741A0BEAE6481258ULL,
    0xB0DA5E4B3443349BULL,
    0xABF31F67B6E79C16ULL,
    0xA6EFB5E93BE65B61ULL,
    0x10,
    0x14,
    0x47,
    0x97,
    0x6A,
    0xD0,
    0x31,
    0x44
};

const TwistDomainSaltSet TwistExpander_Aldebaran::kPhaseHSalts = {
    {
        {
            0x8978AAD766E59B22ULL, 0x79A408C49332114BULL, 0x0E44DE0277A53887ULL, 0x1D6C124D79414D86ULL, 
            0xCEB7E16F13BE6DA4ULL, 0x1C43788B5F78CB1CULL, 0xFCF5EBF22067E659ULL, 0xF6167EC9569AB23CULL, 
            0x920666AFB8219E52ULL, 0xB6573CEE5975932CULL, 0x3DA8A09379C55780ULL, 0x126522CCBE5860D2ULL, 
            0x1D13D2F00C0B5077ULL, 0xC75FBE25EB0A7941ULL, 0x939F6ED32E42F76FULL, 0x6C8F4C62084DBCFEULL, 
            0x5B9FF459C32C9B98ULL, 0x9858EBDA78A17E69ULL, 0xDAF2956CC6769D5AULL, 0xA2394179389DAB57ULL, 
            0x6DC090B0E19D325AULL, 0x8DA83340EABDF4B9ULL, 0x0ED17335A1D4B889ULL, 0x472DBC7D993D1737ULL, 
            0xB8120958863E4129ULL, 0x33743632A2D1E153ULL, 0x28A8E21F687DAFFBULL, 0x0B8C2B1E3BB7CABDULL, 
            0xCBCB5DCCB13A4DBFULL, 0x6347C843508BC085ULL, 0xE8EE71AD746485A2ULL, 0x8BB09267D66F8A87ULL
        },
        {
            0xF7BC4313A597C4AFULL, 0xB21388CF5B70F816ULL, 0x9B548AED69E93778ULL, 0x9B82A3D5B7B2F27DULL, 
            0xFFB91B1A8E3B5D97ULL, 0x88504AEFED28E5F7ULL, 0x6AE34626A6542D28ULL, 0xC298A865F2EB9885ULL, 
            0xCE9A47F5B40828BFULL, 0xF3B4F18573461875ULL, 0x56F5A532425D4900ULL, 0x47823FCCF356D823ULL, 
            0xBFFB927F2A7D3B5FULL, 0x1D92EC0FAEB60D17ULL, 0x23AC2C67A67AD47BULL, 0x4E19C3AF473BAD79ULL, 
            0x0B601521AD73476BULL, 0x42D196EF358EC281ULL, 0xE7A2B55F6D46EBD8ULL, 0x1000D2D796E33C41ULL, 
            0xF9BDD0192C275DEFULL, 0x008F68459194D62DULL, 0xB0B7BC4CE99C324BULL, 0x3D5EF20FB5605341ULL, 
            0x761FE17E7C52E1E8ULL, 0xD2B6CB0A51CA4B53ULL, 0x91CC20C3F4EB533BULL, 0xCCAC2432186D719AULL, 
            0x8BA392F7EF561E3DULL, 0x6A8129FF2C8E768BULL, 0x19E95828012BA449ULL, 0x3B8546A7AB16682BULL
        },
        {
            0x4D7444FACE916C71ULL, 0xCC99B3D129743DD5ULL, 0x35E7802C777733EBULL, 0x8D79D5C67921BA75ULL, 
            0xF1E66BF10B90C681ULL, 0xBC01213CAC0C7935ULL, 0xB84AE582A01B42C0ULL, 0x8B0B5E8B89357C80ULL, 
            0xFAEEB293750DF5D5ULL, 0xDD7E2BA9F5DE7B4DULL, 0xECBBDA13C21EE519ULL, 0xB87180E4A0ABACAAULL, 
            0x26AC654E7AF9888FULL, 0xEA0988ADD7A22281ULL, 0x5718827611EA4809ULL, 0x1E83FFD874D44DF9ULL, 
            0xFEB725F7B6A8FA12ULL, 0x26885452D59991E0ULL, 0x474D2A376EC686F5ULL, 0x761C244EAA107FB3ULL, 
            0xDC272F242815E393ULL, 0xCA5F48B0D8F40284ULL, 0x9B1D38017BC14AF5ULL, 0xA83DA9C979C866EEULL, 
            0x26106E6F8C412A34ULL, 0xDDCEFE8F8C3856DCULL, 0x77F944EA7D93599CULL, 0xBE5717A82E5FAAA1ULL, 
            0xCF2B46FD6D208453ULL, 0x31B6F10A23C81469ULL, 0x227CFADEA34F2F49ULL, 0x6426AB953B915025ULL
        },
        {
            0xA6846FB4355AF3ABULL, 0x40E8EA2A1C0C2227ULL, 0x6DDD2ADFCA1F4380ULL, 0x12BEA71D63988689ULL, 
            0xE043FC39BD7274D6ULL, 0x195B687EF2FCE46DULL, 0x3882EB08C111BDD3ULL, 0x9014C693CF3372B9ULL, 
            0xE0FAB99DD443EBCBULL, 0xFF35CCE823139FFCULL, 0x153DE1219AB96D28ULL, 0xCC1ED07D93823B8FULL, 
            0x580BBFB69BADEA77ULL, 0x4B5433BF837853DAULL, 0xA586CEDFB9E5938EULL, 0xC4A88487671EB421ULL, 
            0xF0129036189F9BD5ULL, 0xADCBF9D89009448AULL, 0x2A84D1548A041E47ULL, 0x22A07289D4E136D5ULL, 
            0x72D10004F612126CULL, 0x506F2BA937F408ABULL, 0x243CA4FCDB2FE927ULL, 0x2BE79659D54A4D75ULL, 
            0x985DAF1CE8911235ULL, 0x899327931B0F6B7CULL, 0xE14E897A159CFD19ULL, 0xFC55F1B834A2578DULL, 
            0xFC4815E2CE45A3EBULL, 0xCD9B0586783303AFULL, 0xDDE175DA79E9A6B4ULL, 0x6774B37EBE1582E9ULL
        },
        {
            0x546AA564D319B795ULL, 0x6AB93AD4090BFBB1ULL, 0xE807A6F71D38C42EULL, 0xA0D16091AA1B7FD0ULL, 
            0x529FE636A9759303ULL, 0xBAA9054E84EE3DBDULL, 0xF9603CE78057D184ULL, 0xE205D0FCCE591C6FULL, 
            0xBCC69571540D6AD1ULL, 0x9A241291A1CE6443ULL, 0xF02674EE1AF85C28ULL, 0x64D17784D7427E34ULL, 
            0xC98B431AE05F5CC0ULL, 0xB71217304BD3CF55ULL, 0xB6935069827F2B37ULL, 0x22064FAA47730C18ULL, 
            0xFFC6381D436E48A5ULL, 0x28D7D82233EECFACULL, 0x7201544D9E9899CDULL, 0xDC0921A21EB93B8CULL, 
            0x86BBB75095E96949ULL, 0x042FB720A78B4BE8ULL, 0xAD11529E42A8D356ULL, 0xD0C89748BF601E08ULL, 
            0x5F38271D8EE320BEULL, 0xF4556E2497B2D331ULL, 0x9601C9CB451EAE70ULL, 0x3923930519715633ULL, 
            0x13A9ADA582B9B174ULL, 0xA5ED2B996B3DFA90ULL, 0x2FD0483796A9167BULL, 0x014949D8D45DA18EULL
        },
        {
            0xD0C12DB48E5B479EULL, 0x1F83195474C29A4DULL, 0xB923C9903C7A6B3BULL, 0xFC17F84EF7054F16ULL, 
            0x4AEF0B878FD7D092ULL, 0xC56DBE80ECABD436ULL, 0xCD56D82BAAD83AD8ULL, 0x1F8911CBDFC857DAULL, 
            0x21CA16BCB211A129ULL, 0xBB9B2AC040164218ULL, 0x68A9B09B2CC8D5A1ULL, 0xFF2FC762C385E22CULL, 
            0x1EF0ECC552894B78ULL, 0x7100F6EAAB2207C7ULL, 0xAD8E8368F63A0495ULL, 0x4AEFDA634DC89B40ULL, 
            0x9769F9707E8585DBULL, 0x0031A10762CF24F5ULL, 0xA4F9F89082BD9FEFULL, 0x46119E5875C2A71AULL, 
            0x228E7976BD5901F2ULL, 0x1F9401DE509A9106ULL, 0xAE2FE81FFF59946BULL, 0x114F58EEFC263213ULL, 
            0xB4FE2C332326FEEDULL, 0xC705BB59B391CF53ULL, 0xADCC61C74EE70F9DULL, 0x23CF9AF25232963FULL, 
            0x63FDA2DEEF8B7E58ULL, 0xAEA1268382EFE151ULL, 0x977FC51E167AAEABULL, 0x5990B35BB6D27D02ULL
        }
    },
    {
        {
            0x6D3DABA5084D4B2BULL, 0x844938F7094CD395ULL, 0x0C47CC77FC79F4CCULL, 0x757D16CF601FD5FDULL, 
            0xBC5FF18D1B0DFBD9ULL, 0x41DC081257695368ULL, 0xA637D6B509DE0AF4ULL, 0x29F605BD44684D33ULL, 
            0x07E8B88DEF458329ULL, 0x80C5EC7720D1AAE1ULL, 0x3F04E80CF217FEC9ULL, 0xC16E36F1BBB60D43ULL, 
            0x7E2A1847EB86CB74ULL, 0xDDC89F7644E67BC9ULL, 0x4E4D752DC7368DE7ULL, 0x4350EFC806DEDEA4ULL, 
            0x7C813F446CADA565ULL, 0x9A837307B42A3E48ULL, 0x7F22038452237DF0ULL, 0x8CAF578BD2F304EDULL, 
            0xA2B76D98CC435572ULL, 0x53F9BA6F446FAF65ULL, 0x9BD8B8AE01D73CC6ULL, 0x15B42B7CE2A75C9AULL, 
            0xF045BA558BCD63B6ULL, 0x3043FAD91088D68CULL, 0x8533AB876CC98C35ULL, 0xC570285FA77DA20AULL, 
            0x3B3234F59320C0DFULL, 0x653E91F5F4B11B88ULL, 0x800AFA0C092D1631ULL, 0xA79C91AD73A9E644ULL
        },
        {
            0x3391A4EF956C682EULL, 0xB535513E9EA44842ULL, 0x6C38359DE9A1D6D4ULL, 0x518E8812FCA3EA53ULL, 
            0xDF6A15E9332C73C0ULL, 0x20E16C7D37E5C005ULL, 0x1C7A68C3215B7626ULL, 0xAFE2DDCDAEFABE1DULL, 
            0x38C1DDB4DE52174AULL, 0x6BCE13E96569FEFAULL, 0x5C68CA00B4B6A44AULL, 0xC66A9C5248BCF614ULL, 
            0x29279B7E5960B7D9ULL, 0x26F313BA0333D5B0ULL, 0x58370EED3AED9386ULL, 0xC49D940BDB2B4415ULL, 
            0x8064A98A7F11F284ULL, 0xFB6593A7F97629E8ULL, 0x91A34652885C225EULL, 0xDFA3BBD03918E2A9ULL, 
            0xE0154A11600B03D5ULL, 0x1668CEAB1960406BULL, 0xC3A6507B7FAE7150ULL, 0x665411CA8A6F9EDBULL, 
            0x0BCEBB945AECE35AULL, 0x6C4FDBE564F23EFFULL, 0xC1F9E6DB9B0B1DB5ULL, 0x6E0B27B506551A24ULL, 
            0x5A1E8304F9F7921BULL, 0x1EE2844484258153ULL, 0xEB85BA587AA54C78ULL, 0x56F480753B922E4CULL
        },
        {
            0x919C9F9F2DBC5F60ULL, 0xF06BF71A5559A285ULL, 0x23AA9F4CA0D80C04ULL, 0x9FD8107A33A091ECULL, 
            0xFF0FD38673E00E5FULL, 0xFF52F8A2B2C5D25AULL, 0xAF16250FDF9C2ACCULL, 0x077E5C2780E6E064ULL, 
            0x3EDECD962D4E98DFULL, 0x14C93A74EBA940E5ULL, 0xA1D59B7BA9B403E2ULL, 0xBE0A224704D83CF8ULL, 
            0x20DFDA7EBDB4B1E4ULL, 0x82C1FD86E08C896BULL, 0x89D0EB24FB015D3EULL, 0x91D18987520E2310ULL, 
            0xD243690FCBD04D96ULL, 0x36262E2EBBD53493ULL, 0xE65B8CA95EC21FA3ULL, 0x30D2287DF6A20BD6ULL, 
            0x57E0FE894B91A434ULL, 0x946C7A7434E0230CULL, 0x50C21478B2068242ULL, 0x92068FF13266C2D9ULL, 
            0xF59E525BD89F3818ULL, 0x4F4894D40AF43CB1ULL, 0xE1E07B1B4E3C2EAEULL, 0x194795FB44572494ULL, 
            0x5DB88E63E38B5C4AULL, 0xAE6732C0DA3DC6BBULL, 0x8D143C7E48C667F1ULL, 0x72912DEBC88C6B95ULL
        },
        {
            0x1EB60CBE02E3104AULL, 0xF91A0B873668CC11ULL, 0xB61C0BCF8C4E24F5ULL, 0x6CF857F25FF8FCE0ULL, 
            0xC192E094E10963DEULL, 0x5A9DFAC98A12CA72ULL, 0x6E56D47183F26779ULL, 0xDE04E858020BE250ULL, 
            0xB868F25C1F3FDE9CULL, 0x181407A573E41698ULL, 0x1395695F6A9B6922ULL, 0xEE564867B5FEBA2AULL, 
            0x11CAE5A1E87A8320ULL, 0x4D981F2A3784900DULL, 0xB7F40A09C1D689E5ULL, 0x7489ED9288BEDF5AULL, 
            0xAAC1786E43A2569AULL, 0x760930FCCC176773ULL, 0x5F73160C13629144ULL, 0x99FA2DE90BB2326BULL, 
            0x46B5A2F2DFB41C39ULL, 0x188892E60E9A36AAULL, 0x73B8DDB345AA01D6ULL, 0x349ADCCE7C11D3C4ULL, 
            0xF16CF10713F144CCULL, 0xAA8D2F9DD3BA6479ULL, 0x20FC23F25882469EULL, 0xE0D0320FE64F246CULL, 
            0x7117E9BD03456152ULL, 0x52C785452958DE73ULL, 0x0D2F7F039A8CDBC3ULL, 0x38FFF04E76A561D2ULL
        },
        {
            0xAD139C05EAE7C8A6ULL, 0xB801E99EE2A8384BULL, 0x70AFF0AED6618871ULL, 0x42FB015BF21ECB14ULL, 
            0x499EBCEA2303C154ULL, 0x229CF58C57A70DB6ULL, 0x98993E03A102CE93ULL, 0xBA309B0F7CA460C4ULL, 
            0xA19CE9D926221C63ULL, 0x60D2F0AF3B0A6DE5ULL, 0x3BDA2825A252F26BULL, 0x98E1F0A8F29902DCULL, 
            0x1136F266E604293BULL, 0x49D3CED361650D22ULL, 0xDFE7A57F0E1D9E84ULL, 0x5330F300E71C8A81ULL, 
            0xDA37CC8E44440523ULL, 0xD7E0FC605AE5B87CULL, 0xF7FC713770D2320EULL, 0xC117EC35D773862FULL, 
            0x0409E0CF43397859ULL, 0xE14D693729C30A59ULL, 0x5D1D34D3391C0FF7ULL, 0x878AED6BAAE8AE4CULL, 
            0x33E77EFBB4ADF056ULL, 0x81F03BC28354113AULL, 0x322726026218469DULL, 0x70C16917AE32B8C5ULL, 
            0x5CD03E7A3AAB88CAULL, 0x730D25B20F659E84ULL, 0xF87D54D82746240AULL, 0xD88F8D5ACDFE95C3ULL
        },
        {
            0xB0864A5404B61D0DULL, 0x3AE301F8D0F89ED6ULL, 0xA7E054E95DA6C676ULL, 0x30CCC276BBC25EAFULL, 
            0xF3D7AB097616C6CBULL, 0x712C3943B2531702ULL, 0x429885B9C6D8774CULL, 0x778EBA7CDA085C57ULL, 
            0xE8BBA234B9FABA4CULL, 0xFCA464C561FEA55AULL, 0x67C5ED005E40B5B7ULL, 0x57CB31E2F82B9F01ULL, 
            0xEF97AFAB052FFDACULL, 0x13775FC13CFC6B63ULL, 0xA76826823934D3C3ULL, 0x20FCD7CC5F8DAF29ULL, 
            0xDCD7C9BCCA263896ULL, 0x6C32F647722FB489ULL, 0x680E113CC673CC16ULL, 0x77193E7CEA51A62FULL, 
            0x275BBC0744BD3468ULL, 0x340072F5E71950FDULL, 0xBC4EF0AD96FCA0B8ULL, 0xA31B377A5812C59BULL, 
            0x2B0D3FB74082E6F9ULL, 0xDDFEAEE70E9B4F25ULL, 0xC87DBA1616F66865ULL, 0x8C14FF7CD87BC2A5ULL, 
            0x480BA9B6A838D9BAULL, 0x2B3B7B92D5C3DF34ULL, 0x27A57C3F5B782E30ULL, 0xC99144C7EF8FD772ULL
        }
    },
    {
        {
            0x70671122B0F85ED3ULL, 0x84C9BE4416F17A72ULL, 0xE983ECDE34543AB4ULL, 0x76F0F50C29DA8470ULL, 
            0xEAEE1FFC055A42BDULL, 0x8879307650D2EA08ULL, 0x3E8F9A7315F3DE72ULL, 0x5EA9961D367260A4ULL, 
            0xCEB2F9E2D53D9039ULL, 0xA9D2834CFD148071ULL, 0x99FBF78FB692051CULL, 0xF45887B019069B75ULL, 
            0x1693F4E530F60D85ULL, 0xFC960BACD40E16E4ULL, 0x28B19EB30165E871ULL, 0x94B33DCE8FAFF15FULL, 
            0x4344D56131F55143ULL, 0xA109C8E4561EB97CULL, 0xF5DC5153BB05B470ULL, 0x7017E51DA5AB2D30ULL, 
            0xC91167DEFEA19D70ULL, 0x606AC560F1340EF3ULL, 0x8D7A461A2794A5EBULL, 0x862872546654CA9DULL, 
            0x369AB64B6E98D121ULL, 0x92910A1A71256796ULL, 0x61884120486CC4C4ULL, 0x8C34B2EB2C031976ULL, 
            0x00824645C06C7A82ULL, 0xEAF15ACC683A80E1ULL, 0x0B5931C430F331F8ULL, 0x0CBDAD3A3383BFBEULL
        },
        {
            0xB01C7AC2E949CC21ULL, 0x19A26192D4D7315FULL, 0x4AD41C8F36166281ULL, 0xD4193DDDE657ECB4ULL, 
            0x3C7FE7B5E39C3D91ULL, 0x196DC8710D5DC320ULL, 0xE07AE4451CDC3B53ULL, 0xE54B6FDFEF565B99ULL, 
            0xBF520F71638B2939ULL, 0xFB2D73F83F5CA70AULL, 0xED0C7D6380D135FAULL, 0xE7CF780AA7966E1BULL, 
            0x042CF5F7AE139F29ULL, 0x62D2017098510E66ULL, 0x8C88CE5DAB523216ULL, 0x9FD450D0B544C610ULL, 
            0xF3F1662AAD511F6DULL, 0xE5E0AA5ABAC2C9D2ULL, 0x23C68D1E354198DDULL, 0x68DA4C9BBC1075E0ULL, 
            0x3D11B0B6F6903051ULL, 0x529D57EE86E1A1D8ULL, 0xDAB85298A50015BBULL, 0xF478D873595BE0CCULL, 
            0x21516AC073DBCD35ULL, 0x6970FC9E3835E782ULL, 0xE3618C6DC3881791ULL, 0xAA77D57594711B9FULL, 
            0xDF3B406D83830274ULL, 0xFB617689E2343848ULL, 0x49989D4541E23794ULL, 0xB9BE120432055833ULL
        },
        {
            0xE562F057719AF71DULL, 0x993E5753440941B2ULL, 0xABFF567F593E553EULL, 0x990A1D131A601D88ULL, 
            0x9069F97C818F3293ULL, 0x29D39F06E6C928C8ULL, 0xD827369141593106ULL, 0x968CFE2F3C44C704ULL, 
            0xE1FEA7C949B13333ULL, 0x32D80FF8334324EFULL, 0x83404528BA0C0DD2ULL, 0x520422D1A3BE7308ULL, 
            0x9D545DE161DB2FDDULL, 0xF6214215788029F9ULL, 0x4E43DB08DDC6477DULL, 0x8DC2E03A2B5DDC29ULL, 
            0x546EB552F3A2DFADULL, 0xF0B45A3D7EB9E41CULL, 0x8A6D5CCB24D004BDULL, 0xF02D071EF65357FFULL, 
            0x5D87EDD6DCF77398ULL, 0x094DCFE50A8453B3ULL, 0x6D5563FAEC82F753ULL, 0xAB207CFF499700BAULL, 
            0x65739E5A7552B683ULL, 0x94F7C7836173378DULL, 0xE97DD93286C284B5ULL, 0x70B7D88EDC0E682FULL, 
            0xC134171832E2F712ULL, 0xEE07DAB206550C0CULL, 0x79076FEEA7B6BF75ULL, 0xD95B13BA4B5A3E8CULL
        },
        {
            0xE7611CBB44DC96BAULL, 0x69B905886D276AA9ULL, 0x30635BE640F02BCBULL, 0x205CA6F4D3342F94ULL, 
            0x312FE691C162CA5FULL, 0xA8600299B8058345ULL, 0x2B14F3A7A88740EBULL, 0xA53E620FFE7EEE31ULL, 
            0x019FEE389FA090FBULL, 0x68AB5FD59C6B9A4BULL, 0x5AA1ED3B692309DFULL, 0x3B084EBD78386CE0ULL, 
            0xB3DD9D3EB2949087ULL, 0xDEC469EB4F16BAA3ULL, 0xD9E5F25BC24B38F6ULL, 0xC7517F8421F0FB09ULL, 
            0x1F5AB1EEE18FE88DULL, 0x33C9C3CFE6E0CB72ULL, 0xAA7D41BD40F5CA67ULL, 0x8793F42E87487036ULL, 
            0x7EB69944D20C222AULL, 0x3F6778A9C0812641ULL, 0x3931B94836AA9BD3ULL, 0x2B45E67E9101F1F1ULL, 
            0x3CFA315354C98F93ULL, 0x21DCA8C7026A9E3EULL, 0x469315843F99478CULL, 0x208805014030FA2EULL, 
            0xC31D7C87412AC6CDULL, 0x31C5D6A1A345B6E6ULL, 0xA0DBE5D9DC2E5D85ULL, 0x10A06DBD72F4B563ULL
        },
        {
            0x81C7FE6DD4ADDC1AULL, 0x7E3E578DB3D957A4ULL, 0x5CDECDB94B24CE91ULL, 0x73AED24FFB791709ULL, 
            0xB7CC4AE2F40E5B58ULL, 0xDAD911E66D5DCE4AULL, 0x4D810384E5A800B8ULL, 0x0D564EC41633C3D2ULL, 
            0xC517CDD9EDA8AFEDULL, 0x6E2E83F46BC82B01ULL, 0xF6CE046FD2D00C07ULL, 0x07A5AD96415D94ACULL, 
            0x2A5BE8799E67973EULL, 0xA22F84AEDA90ED02ULL, 0xF601A280DE579DCFULL, 0x6C27A4613E142AE2ULL, 
            0x186B421FC1FC17CCULL, 0xDA8BD63AC96ECE6FULL, 0xE13DD76EE6E390A1ULL, 0xE2678702DBEA2696ULL, 
            0x3444D1EB17F78096ULL, 0x32E968079BC451B4ULL, 0x9049706F846AB428ULL, 0x6D1052FD2B68C89EULL, 
            0x913CCA3ECACF490CULL, 0xB56334868C9279D6ULL, 0x58DC7C7961B60A01ULL, 0x4E783B963D848EA4ULL, 
            0x9FA4DE4C64D18AE8ULL, 0x9A97D91599CC5A1BULL, 0x0811B1DE0507FFB4ULL, 0xD9193C19FA9DE304ULL
        },
        {
            0x8B396BBC82ABD8B1ULL, 0x8B99BC566A693E0BULL, 0xDE202F1AAE7251D7ULL, 0x6EC9B8752C6AF0ABULL, 
            0xB4CB15F053A19A09ULL, 0xCC821228729FF2DDULL, 0x12BB2E01C8A9E63FULL, 0x1F705F1A81D4130DULL, 
            0x51DACFA34D474BB5ULL, 0x97F3B5F5283AE399ULL, 0x988279A172AE0E49ULL, 0x2489A674DE990B38ULL, 
            0xE6FC12E16966C410ULL, 0xC26343F66BF58B71ULL, 0xCE54301A5FD5427BULL, 0x892DBA996F50F0A3ULL, 
            0x974D5C50245508A6ULL, 0x4052300CE4C8D0FEULL, 0x1BBCB7F9715C79B0ULL, 0xB4714ECE1EFA4EFAULL, 
            0xA907491416E95A3FULL, 0x1DDA632872EB8636ULL, 0x65D221E433CB567AULL, 0x2CB53DDDB0A260BAULL, 
            0xDDA24904A1DDEFD0ULL, 0x45919FA51D30B8DCULL, 0x84236DF9AB98027FULL, 0x7FDD130B2B8B7398ULL, 
            0xFECD6C2088C9E9A5ULL, 0xF14D446BD5041591ULL, 0x6C505C2EBA18249AULL, 0xE7018F97563B45E6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Aldebaran::kPhaseHConstants = {
    0x21C44B7C34D73BF9ULL,
    0x3F2E183C328FA360ULL,
    0x25C525AB35B4ACDEULL,
    0x21C44B7C34D73BF9ULL,
    0x3F2E183C328FA360ULL,
    0x25C525AB35B4ACDEULL,
    0x2F9BEF202B6C9FBDULL,
    0x56C0627419F8AEBAULL,
    0x1B,
    0xBE,
    0xDE,
    0x49,
    0x41,
    0x56,
    0xB9,
    0x31
};

