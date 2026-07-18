#include "TwistExpander_Ankaa.hpp"
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

TwistExpander_Ankaa::TwistExpander_Ankaa()
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

void TwistExpander_Ankaa::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xECD718EE7F1F389AULL; std::uint64_t aIngress = 0xB05D79678D023498ULL; std::uint64_t aCarry = 0xB165900A3D23A012ULL;

    std::uint64_t aWandererA = 0x880FA192DBAE9AA7ULL; std::uint64_t aWandererB = 0xF9528B2B0378AE36ULL; std::uint64_t aWandererC = 0xA1A35E53C9239072ULL; std::uint64_t aWandererD = 0xCD0E93B0AEFEE18DULL;
    std::uint64_t aWandererE = 0x9410A751EECE58A4ULL; std::uint64_t aWandererF = 0xE9F8FAD02B72EE98ULL; std::uint64_t aWandererG = 0xC103D2E463641FE2ULL; std::uint64_t aWandererH = 0xDF1EB01E96965508ULL;
    std::uint64_t aWandererI = 0xCD277BA72993AD7AULL; std::uint64_t aWandererJ = 0xB93CBE15AA37AABDULL; std::uint64_t aWandererK = 0xB96D84F2B044971FULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10789908202585820669U;
        aCarry = 16452988766849597115U;
        aWandererA = 10758839171864476849U;
        aWandererB = 12291306940494373648U;
        aWandererC = 17461414177200173292U;
        aWandererD = 13677043990378134018U;
        aWandererE = 17681504394371533619U;
        aWandererF = 13347203858005439783U;
        aWandererG = 17144453337096991442U;
        aWandererH = 14818359323812892648U;
        aWandererI = 10974301322518610693U;
        aWandererJ = 12729889014592013945U;
        aWandererK = 10711794611207531473U;
    TwistExpander_Ankaa_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Ankaa::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xF74CE7F14E5FF2C4ULL; std::uint64_t aIngress = 0xE63A05B184BB1122ULL; std::uint64_t aCarry = 0xC59CA53C3B0248B0ULL;

    std::uint64_t aWandererA = 0x9019C2429EEB222BULL; std::uint64_t aWandererB = 0xB2A0772516CE0715ULL; std::uint64_t aWandererC = 0xA38306A2B4468E0EULL; std::uint64_t aWandererD = 0xFB1EB07FB54622B9ULL;
    std::uint64_t aWandererE = 0xBBCD0A738F1F4D02ULL; std::uint64_t aWandererF = 0xB6AEC9AB944B2858ULL; std::uint64_t aWandererG = 0x8E630C019A475A34ULL; std::uint64_t aWandererH = 0x972B327BA505DDFEULL;
    std::uint64_t aWandererI = 0xAB4D7C13A1F03BCDULL; std::uint64_t aWandererJ = 0xB87D912E3C8007C6ULL; std::uint64_t aWandererK = 0xC6035BED7813BF4EULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15545505009696294405U;
        aCarry = 14910806498052627610U;
        aWandererA = 14924832550939648448U;
        aWandererB = 12828552124763877084U;
        aWandererC = 13780231421675223555U;
        aWandererD = 18041651681452816430U;
        aWandererE = 18062999419049953037U;
        aWandererF = 16854172932361996774U;
        aWandererG = 13666708415424903573U;
        aWandererH = 16324668344148486575U;
        aWandererI = 11418571230172708160U;
        aWandererJ = 13619601624650503442U;
        aWandererK = 16062046930871501328U;
    TwistExpander_Ankaa_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Ankaa::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x9968695001ABB1E7ULL;
    std::uint64_t aIngress = 0xCFD2BB3CF1931BCFULL;
    std::uint64_t aCarry = 0xD630A97E79009312ULL;

    std::uint64_t aWandererA = 0xA49603433D6D65A8ULL;
    std::uint64_t aWandererB = 0xA307B6EB315C7AFEULL;
    std::uint64_t aWandererC = 0xDB1FA9BF910944CBULL;
    std::uint64_t aWandererD = 0xEB2876DCD15A8055ULL;
    std::uint64_t aWandererE = 0xAEB52A9C4CCEC80FULL;
    std::uint64_t aWandererF = 0x8895ACF693B645EDULL;
    std::uint64_t aWandererG = 0xE254F5389D66200AULL;
    std::uint64_t aWandererH = 0xA9D458099E92CFBEULL;
    std::uint64_t aWandererI = 0x8EF4C39F30FCCEFDULL;
    std::uint64_t aWandererJ = 0x8F7B3678B696F9F8ULL;
    std::uint64_t aWandererK = 0xFDF5C45C15193EEAULL;

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
    TwistExpander_Ankaa_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Ankaa_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 8 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1902 / 1984 (95.87%)
// Total distance from earlier candidates: 13355
void TwistExpander_Ankaa::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 964U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2042U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 669U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 242U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 643U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1565U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1413U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1727U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 284U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1154U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1303U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 345U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 325U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 449U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1582U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1831U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 206U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 804U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1069U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1860U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1332U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 705U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1502U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 129U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 47U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 996U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 214U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1364U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 730U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1776U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1244U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1430U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 295U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 906U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1163U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1017U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1640U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 637U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 797U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 416U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 580U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1487U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1737U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 772U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 64U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1236U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 313U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1726U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 511U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 469U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1898U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1558U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1590U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1873U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1428U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1427U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 594U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1477U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1323U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2015U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1319U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1047U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1187U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1223U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 504U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1104U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 725U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1805U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 755U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1093U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 279U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 285U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 766U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1023U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1815U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 649U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 609U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 310U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1416U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1725U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1853U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 558U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1120U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 347U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 542U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1930U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1952U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1728U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1090U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1598U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 846U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1712U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 155U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1296U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 917U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 250U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 211U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 714U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1628U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1283U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1456U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1229U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 968U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 323U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 539U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1224U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 780U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1457U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 287U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1857U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 945U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1480U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1207U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1143U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 108U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 849U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1434U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1182U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1965U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1114U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1820U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 561U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 252U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 36U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1170U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 403U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1933U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 394U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Ankaa::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE0AFBF76E9FFCD37ULL; std::uint64_t aIngress = 0xC13DD8C61C96F71FULL; std::uint64_t aCarry = 0x8A89DF925B0E0FACULL;

    std::uint64_t aWandererA = 0xF13E2FB5D433CD43ULL; std::uint64_t aWandererB = 0xE14ED062CDD4720BULL; std::uint64_t aWandererC = 0x855279C7C16CC63CULL; std::uint64_t aWandererD = 0xA6ABD133A46B97A7ULL;
    std::uint64_t aWandererE = 0xAD2A858FC7EEAA95ULL; std::uint64_t aWandererF = 0x8A740499E54FAAB5ULL; std::uint64_t aWandererG = 0xABB4158BA6ACAA53ULL; std::uint64_t aWandererH = 0xCFA173C72E068AFAULL;
    std::uint64_t aWandererI = 0xF03ACEE0F9514C83ULL; std::uint64_t aWandererJ = 0x9E89DB795950E973ULL; std::uint64_t aWandererK = 0xDB652E0878C968FAULL;

    // [seed]
        aPrevious = 18205961194437425547U;
        aCarry = 17211070992848714677U;
        aWandererA = 9945965622497890835U;
        aWandererB = 16798536250182255973U;
        aWandererC = 14561253811979690052U;
        aWandererD = 11037608876585836170U;
        aWandererE = 12077054012582300945U;
        aWandererF = 16611484975323682583U;
        aWandererG = 16957454127068583220U;
        aWandererH = 16979700515236133035U;
        aWandererI = 15016596649549460739U;
        aWandererJ = 17505658030675037215U;
        aWandererK = 12762170281820938587U;
    TwistExpander_Ankaa_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Ankaa_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Ankaa_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Ankaa_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 8 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3943; nearest pair: 528 / 674
void TwistExpander_Ankaa::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3339U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7691U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 659U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1355U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2010U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4670U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 685U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 941U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3256U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1480U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 163U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7520U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7329U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7857U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4922U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7777U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1789U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1674U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2004U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1889U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 428U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 108U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1804U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1259U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 277U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1715U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 73U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2019U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 501U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1634U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1438U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1249U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 102U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 380U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1840U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 835U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 8 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 3950; nearest pair: 533 / 674
void TwistExpander_Ankaa::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7162U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6438U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 907U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7289U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4042U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4307U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1620U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4415U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6137U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3117U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2194U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3345U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3776U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6513U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6439U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2429U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 129U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 776U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1929U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 38U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 850U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1370U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 691U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 455U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1553U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1722U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 797U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1895U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 417U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 631U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1578U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 361U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 973U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1928U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1138U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseASalts = {
    {
        {
            0x1960DAAF9856C1BBULL, 0xCB9FD2BD4E491460ULL, 0xF0FDA311A51BC97EULL, 0x5B1F7FDE5528D300ULL, 
            0xA599B8AA0BF5A0E3ULL, 0xB658A6D83D7CF6E2ULL, 0x28755C1EF364C701ULL, 0x8DA05E9BFFFA7196ULL, 
            0x560FB663636EEBE4ULL, 0x94A70699420092D6ULL, 0xD92D339D9F1EF671ULL, 0xD2CB750ED489A694ULL, 
            0x4DC47B2447AC4119ULL, 0x2245D241B280B167ULL, 0x933A9EFF593983FCULL, 0x93F01DC91EF0CA48ULL, 
            0x28476E649EE612C5ULL, 0x7497AECC9D926F95ULL, 0xF53DB7381CA57E7BULL, 0x33197CD446C5D099ULL, 
            0xC4C540EA119AD45EULL, 0xEBA47E96FA736342ULL, 0xAEDC18A77F51B63CULL, 0xE94529126DA056DFULL, 
            0xB848F9DC9517819BULL, 0x0476B0962FD1F93FULL, 0x18DA247B30AC8D45ULL, 0x49DD5ED7F82B0AC1ULL, 
            0x2E04926C993DBCCBULL, 0x0852EEB5DC15B5A0ULL, 0x875987D367F8C677ULL, 0x32B0069B94DC97B7ULL
        },
        {
            0x88A704C22C2A652DULL, 0x6C5B7BB8F1DB0FE8ULL, 0x7D909F83A90BA0D4ULL, 0xDC8246107472B8D0ULL, 
            0xAEC662DB5AA6881EULL, 0x84BACBA9A07F7E66ULL, 0xCD7A5836102239D2ULL, 0x4A3325642CE46D49ULL, 
            0x548BDE72D1E063F3ULL, 0xB55F6989B2E9E76AULL, 0x6CEA2E9AA6708AF1ULL, 0xADE78EB9A0C677E6ULL, 
            0x310C5810C037A6CCULL, 0x02BFFEC488F9B16AULL, 0x428492D34257B96AULL, 0x5F6B190003CA1A13ULL, 
            0x5EFEE6298BCBF856ULL, 0x6EC4CF74C116C8A6ULL, 0x5DD4BFCE64172A21ULL, 0x66F5D54B200DBBF6ULL, 
            0xB574F919EEACF182ULL, 0x9C2714295C8D7D24ULL, 0xB8AB517CFB0CCFECULL, 0x96182C741541725CULL, 
            0xA3EE17A957EE0C0AULL, 0xFC5AC4A55F6242CEULL, 0x6F65C7FAD3ECF3BAULL, 0x109135E235EDB2F4ULL, 
            0x1456E98FFA3FDDB5ULL, 0x19F6827BE0EEA119ULL, 0x9B15E1C3996FF1E0ULL, 0xC77FEFCA6770A1D7ULL
        },
        {
            0x98825E5199FE6EF8ULL, 0x1B323F20410F2CCAULL, 0x762D71DD07CBBE70ULL, 0xBC111EE4EF09C026ULL, 
            0xF4BDAEEE833AD33BULL, 0xAEBE01C83FF713A1ULL, 0x9F8AF03176A491A5ULL, 0xA598D460FCF7B394ULL, 
            0xE132A34E84D7553CULL, 0x090A10A2D92B67F5ULL, 0x8205C9A778340D13ULL, 0xCADBB7718A01942FULL, 
            0xE8050E8DE3A3FBC1ULL, 0x5D119DC6A115688EULL, 0x1BB9A70A0210E48FULL, 0x9CE5EB7B5745BE28ULL, 
            0x543A170E7F63CFA8ULL, 0xBE2DCB4C64C32459ULL, 0x00F87FD8C71EBFB6ULL, 0xEECA813629E241A7ULL, 
            0xDC8775C228EA9BE8ULL, 0x06A57F746963D343ULL, 0x4491E6CA86DC3FEBULL, 0xEB1520233B73E8F0ULL, 
            0x6255FC4942413B2EULL, 0x0FAD8AC26A112350ULL, 0x26F673965D26339AULL, 0xF3B21A60F8F96494ULL, 
            0xFFA6D6116A32B255ULL, 0x35A386D1888593A3ULL, 0x16A5D6DDB75A4972ULL, 0x0B77B8C614D54167ULL
        },
        {
            0xCF9B522C5A200BAEULL, 0xE1CD63D0675159B4ULL, 0x592CEF2ED7456030ULL, 0x60C82B1C653DB802ULL, 
            0xE88EF8371C6B4451ULL, 0xB375521E217DCC20ULL, 0x32EB9A3FD7E5D49DULL, 0xCE6894B40B1D1C7AULL, 
            0xEB2435D26B65606AULL, 0xCCD334C0F23E6B79ULL, 0xB0E46CCF0878F770ULL, 0x9611589F2E5F7F42ULL, 
            0x103B2D27A589CF02ULL, 0xC1E7766672EBFBA0ULL, 0x74300B1FE9551F08ULL, 0xF575A9E91222A93BULL, 
            0x02F6F8D92F0FD269ULL, 0xA9C7428012E7C76FULL, 0xF04B309574D7C171ULL, 0xDE1C2CBD147AA087ULL, 
            0x20761A0E2D51837CULL, 0x400720BA17E46D88ULL, 0x34C3CA8345254B31ULL, 0x4833CF4F9EBC7F0FULL, 
            0x7E0396C62434B1CDULL, 0xBC8CEC4C8D653111ULL, 0xFFF248C9E5A132C0ULL, 0xFDAD7F7429C300DDULL, 
            0x8D668E665957D649ULL, 0x0540D54A41065E03ULL, 0xA01163EF46CAE4BFULL, 0x0DCDCC18BC910B19ULL
        },
        {
            0x61AFC63631A83AF3ULL, 0xA6A60F43E6F19C40ULL, 0x14A5EBD77ED9B285ULL, 0x6331CCDD7F8B5F4EULL, 
            0xEA43F06CCF85196EULL, 0x77C93E2622ED04AEULL, 0xD0FD7C2C2A352EE6ULL, 0xDF922072F75D5836ULL, 
            0xCBC6715B0514E9D4ULL, 0x23066A1A835B0EADULL, 0xBB273653EFD0BC27ULL, 0xCC7448D48C4F6A87ULL, 
            0x5968A363711F943CULL, 0xEFFBC2D2A25AB915ULL, 0x1ABEC2227306AD25ULL, 0x9CFD1165362EBE10ULL, 
            0x02304AFF7516BF02ULL, 0x694FF98E96F08C8FULL, 0xB6715A4462214C13ULL, 0x291D02E9C571C6E9ULL, 
            0x914A51EEADC31447ULL, 0x155D4717FB9CCF97ULL, 0x0B983B45CE01ACC5ULL, 0x6ECCC0C6C7F4EEADULL, 
            0x051C38CD7C4AE75AULL, 0x3E3527E310E823E3ULL, 0x2A94C90EA0431D5DULL, 0x4D793FD5BDA32B16ULL, 
            0x6D98E6A8296C90B8ULL, 0x23BB93871A28F206ULL, 0x8EF8FE83E9D25BA8ULL, 0xF571C058CE9A7E02ULL
        },
        {
            0xE11AF2E2B11C46DBULL, 0x44DA7E2A5175D149ULL, 0xBE6128713182F636ULL, 0x36A75A967AA99CE0ULL, 
            0xDC68E61E84518D34ULL, 0xEF82363E7961E634ULL, 0x9292EF26562D4D35ULL, 0xB14779A2B14FBBF7ULL, 
            0x2E13C87C277C998AULL, 0x212B804960C74CA1ULL, 0x0CADAA6886F2524BULL, 0x981FAC5E1D26A2E4ULL, 
            0x8927BC1BD6A6AD93ULL, 0x9598EE87752947C9ULL, 0x9F7A272DCA6A98AAULL, 0x61E25B7C2EEC4EB6ULL, 
            0xA41112095E02A5A6ULL, 0x8F3271ECDB0375E9ULL, 0x5DC379911E0238D4ULL, 0x38884C268BC2084FULL, 
            0x1C86A59AFFC2FB56ULL, 0x2DA9719D24371544ULL, 0xFBC32D3BE5A372CDULL, 0xC5D96ACAD3529D98ULL, 
            0x235327B6EB0A92A8ULL, 0xEB86DC66DEE683B2ULL, 0xA73D38D657204D1DULL, 0xC3E62F1F11C0DB22ULL, 
            0x9D86DAECD6071321ULL, 0x5E8186E66D12A13EULL, 0xBA7F7C1A2036303DULL, 0x26C146B28B122C9FULL
        }
    },
    {
        {
            0x59F154234F5C649EULL, 0x95183A8DF153FD89ULL, 0x1F379EB19BADF3F2ULL, 0x4874E00852C5ABC7ULL, 
            0x93DBF72B46C6733EULL, 0x76493056DCF1A0F8ULL, 0xB4CF80BFE5B3CC5AULL, 0x2311723FAF47B7D4ULL, 
            0x1F7FAA10E5387DFDULL, 0x6ECC82D623848CB0ULL, 0x3B374424C951769CULL, 0x64794D7A18FDB673ULL, 
            0x9F45A42A0035F142ULL, 0x12F09A535641623BULL, 0x9DF85A22B91CB8BAULL, 0x63F44305E6D93950ULL, 
            0xA612C23F6DDB0751ULL, 0xFEDC07A98EE0503DULL, 0x71BD272E86D865FAULL, 0xD2382BF8DAF395B8ULL, 
            0xB878E52BBF9D0B88ULL, 0xE72075A9D0DE25A7ULL, 0x1BFE1DE8B9DA57B0ULL, 0x551E439F8D6BC8A5ULL, 
            0xB7CBD6E27DB638D2ULL, 0x9D397BA8C6CDBD54ULL, 0x78B51018A72D5847ULL, 0x3C1C9E6DC33DCDA7ULL, 
            0xECD37F88C26C3FD2ULL, 0x6C78694E9FF8763CULL, 0xB540F7E3AC6FDCD9ULL, 0x606E4D16B57393E2ULL
        },
        {
            0xE2B22F4AE180ACCEULL, 0x3236E903FF9B5BB5ULL, 0xECF27A6E6878B99DULL, 0x007EAF014946D291ULL, 
            0xCA1F6F07EDF2AD7FULL, 0x99F297C6DA715A65ULL, 0xE37A1A3F160CCA08ULL, 0xB880352FE0C5F4F3ULL, 
            0x96DF6EDCD855848BULL, 0x75DE9C6BFE58972DULL, 0x290ABE22F6CA8963ULL, 0x8F8CD1EDD72EA946ULL, 
            0xA8003A863EB0071EULL, 0x40CDFCDD5CB10878ULL, 0xDACDDAA8500CF87CULL, 0x616EFF7DD3FFAA7DULL, 
            0xB5FA686FF45F7648ULL, 0x4F23C13977F5B84EULL, 0x1C5ADFFDBF9C1063ULL, 0x29DD44B47543FA28ULL, 
            0xB63FF54D4BF2A45FULL, 0x4469687D117F894AULL, 0x0AB498B82D7A861BULL, 0xCD2EB934929515B9ULL, 
            0x5163795808ECBC89ULL, 0xC93FCFE556211301ULL, 0x00476673EA12CB78ULL, 0xE49657726C443090ULL, 
            0xF069AA1F596C0785ULL, 0xD60F52FC44B9330EULL, 0xE81EACEF745E3E0CULL, 0x8D7766FEE6D4400FULL
        },
        {
            0x5F53BD9E7EE145CAULL, 0xB1D95F643C301D27ULL, 0x987BA280482271BAULL, 0xE32A029E0732E221ULL, 
            0xF3EBEB3E566B075BULL, 0x7B44CC7EB2BF4F66ULL, 0x083F1C41A83D17FAULL, 0xCB36BB649096381FULL, 
            0x61F303F64A784770ULL, 0xF9B2F77136D54CCEULL, 0xE1E7444C17CAB127ULL, 0xE74D4EF9963B5A34ULL, 
            0x736945313E56134AULL, 0xB6142202DA616C8EULL, 0xD329B1A019CC6D3BULL, 0xF5D13E86FCCA6B90ULL, 
            0x7B4258848E8471DFULL, 0x5A1AA506428B5508ULL, 0x5D8C2F9A8BBB05D9ULL, 0xC10FFC61FAEAB02AULL, 
            0xADF22B22B62D85EFULL, 0x58B8BBEE8FE57546ULL, 0x555770FB5B5F6420ULL, 0xDCB011227C70F642ULL, 
            0xE6B3C6603BCA772EULL, 0x909FDC498F720F5AULL, 0x8E1DB9C4475FCCCEULL, 0xE98D0C5193B0E964ULL, 
            0x3675560968D89F55ULL, 0x964DF0E3BC8CC052ULL, 0x080A7DBB91DAADE0ULL, 0x933F095DDEE5EB4DULL
        },
        {
            0x17C92F946EE687DCULL, 0xB834165B9A55C4D8ULL, 0x6FE0717CB0AD8538ULL, 0xB0AA8C6DF5601256ULL, 
            0xB4D5114640714636ULL, 0x3077F8A2C5378B62ULL, 0x2FEBEF9DEF42FF71ULL, 0x47E62EE32B291A07ULL, 
            0x2E84F98136BB2C41ULL, 0x55A70951C1E592ADULL, 0x4F3A63700299E062ULL, 0x1D01E6354E332C78ULL, 
            0xCEEB4AD3B7AB4E75ULL, 0xEC75D66A8985BB1DULL, 0xA73BF8A6C96FE9B9ULL, 0x33388E6829B5207BULL, 
            0xAD6DF61711ACD378ULL, 0x2B37FC7C85194670ULL, 0xEDE29EE34BEE9299ULL, 0x5408C1D5093326E0ULL, 
            0x7A8A5CE4A809B1ABULL, 0xDA79CDE7592D00C9ULL, 0xB8133AF36A77B2A3ULL, 0xA165D1D54EF4E760ULL, 
            0x6C6D959B8AED586DULL, 0xEC4901C21FF1D267ULL, 0x19EB63E03DD6FF0DULL, 0xA2D5626255718034ULL, 
            0x4B0BCC9F05989DBFULL, 0x40AB8537F3B0303CULL, 0x2B4E0EE6FE08CB6AULL, 0x47CEC18FA40FBACEULL
        },
        {
            0x8C90A35534B2BE52ULL, 0xBCF2F713BF69DC7EULL, 0xEC49D8A99CD47A71ULL, 0x0F3A86400376CDA9ULL, 
            0x9C91BE37D5696F6CULL, 0x70A223CF2A3BD982ULL, 0x0C9E4FC67CD8D8E7ULL, 0x811C0F822D9413D1ULL, 
            0xA42686C21D54F373ULL, 0xB3466019C8F778ECULL, 0x1DEA8A3BF4C97F18ULL, 0xBF97D19EA001B884ULL, 
            0x7C074939F38B75F9ULL, 0x8D2FE088A28DF3D0ULL, 0x2AF1891122D00BE1ULL, 0x612D327F749026B7ULL, 
            0x503E061F8110F84BULL, 0xECD8B9405D0A71ABULL, 0x37A3FA6C59AC74C5ULL, 0x11CC75581FC4ADB0ULL, 
            0xF27A80BEDF5DD714ULL, 0x2698FA23B7304E80ULL, 0x68ACBE87E21FCF93ULL, 0xAE319A2E9DFE4E53ULL, 
            0x0EB90657B6438AD9ULL, 0x2E450139018FF261ULL, 0x17F28EE923FBC102ULL, 0xCA7DF1B0D066D893ULL, 
            0xF7ACA3FCDB341C05ULL, 0xEC25E84D6215179CULL, 0xC0D0C2C8484AAF4FULL, 0x3C81612D86F3E0E1ULL
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
        }
    },
    {
        {
            0x716D1FE1F72EBE3DULL, 0xB19A4D5632A15499ULL, 0x4856209A0CFBCBE7ULL, 0x4CEC84ABA5F5D4DFULL, 
            0x342C149C4E157D75ULL, 0x8777824EC71D3D60ULL, 0x6FD656C53F4C6229ULL, 0x6EFE096D94369444ULL, 
            0x1568841AB068F2CBULL, 0xFF70EB08AB1BEF2FULL, 0x59033BE71DE3D9A6ULL, 0xD431BF7CAAB0CD4AULL, 
            0x333706B24F5D174FULL, 0x16510F87B10CA5C9ULL, 0x8417B8DE7B7003A7ULL, 0xD4594176C3BFA01DULL, 
            0x2B149B47317C6EA2ULL, 0x9B4C7B2FF0D7C985ULL, 0x2EB264D46E46FDEDULL, 0xB38C691BB68F86CBULL, 
            0x8C50C5692E66FF57ULL, 0xDB46591F2AD7DE0DULL, 0x516D513F66AB5A67ULL, 0xDC402B05E6CDE043ULL, 
            0x8077FE457EDA775FULL, 0x2B90932D9CC7734DULL, 0xE8C8615C41ED38CFULL, 0x8E16EA58729A2B3EULL, 
            0xE9A723FF1602CF88ULL, 0x4A7A7A57295781DFULL, 0x41671B1CFC11C13BULL, 0xCFABD0B101390346ULL
        },
        {
            0x4D4DB54A82A562D8ULL, 0x5F46180C6F243C28ULL, 0x41DEC1B541D3E010ULL, 0x09727BC05C8C0CC5ULL, 
            0x66B998428D632C66ULL, 0x2908369ABDFEBC55ULL, 0x7B23E41607177733ULL, 0x5DFCB779C7A8BFE5ULL, 
            0xA3B4A5A5EC940AF1ULL, 0x2D110C55BBD8A625ULL, 0x0D8D6C17977A934FULL, 0x53E31A4577CA4CE9ULL, 
            0x7398170105B729CFULL, 0x94B1EF44EA4E8636ULL, 0xBEAA7EB0BE239639ULL, 0x3E20F24C57D2B056ULL, 
            0xCA35E3F681DD3665ULL, 0x4A7E358D7EA7822AULL, 0x33624A1AC177FAECULL, 0x19E907117780D807ULL, 
            0xDBEE4BC1625FBF72ULL, 0x5B7E0A1E31727FB7ULL, 0x424882BFB2A05D89ULL, 0x9E84BF72C1508935ULL, 
            0xD171AAE32D03327AULL, 0x48FF12F8A2414C9EULL, 0x5F2B05BF4BC22757ULL, 0x59DFEFC42ADB6B8AULL, 
            0x52FEF4D021256021ULL, 0x8356C4C6836FB39FULL, 0xDC76167BBC069CA3ULL, 0x9825DF5D63B08C73ULL
        },
        {
            0xFE6DBB7CE0C347ABULL, 0x836F68B453547D1EULL, 0x8BB5DAD57C8DFEEDULL, 0xF918819511FF63DFULL, 
            0x7C93890D8C571605ULL, 0xCE8222C0B755BE01ULL, 0x4715EA6C79278651ULL, 0x360D271110FC8755ULL, 
            0x57B75A31C5BFCAF8ULL, 0xD40E7D2523A10C3DULL, 0x1EBB46B6D4502ECBULL, 0x74D59C549576A462ULL, 
            0x09960DBE4658D6B6ULL, 0x25DE4196A360E247ULL, 0xE3E708E93EC247F3ULL, 0x29479D4769DABFBEULL, 
            0xB08EE9CCAE494A16ULL, 0xA69F010BE220E58EULL, 0x95514B5DC20215F7ULL, 0xBB424DF4E3B706D0ULL, 
            0x79E868B81FBA78CFULL, 0x36DFF00A1DC3CE1CULL, 0xC4682E3B16D0E21EULL, 0x61B8AE7D18728238ULL, 
            0x8EECB743E8EE782CULL, 0xCBBE3AEE2927F559ULL, 0x0BABAEAD2C3221D5ULL, 0xF537CEEEB8D74173ULL, 
            0x2A533FD39BAA10E8ULL, 0x2AC447D979C43329ULL, 0xE8C9C31569660E37ULL, 0x317CC772000EFAC9ULL
        },
        {
            0x13D185A1AA1410FFULL, 0x24AFB2BCA84CE24DULL, 0xC858737AEADA777BULL, 0xC8B8CCF0006A63FAULL, 
            0xB5DE02096F932A5AULL, 0xB514E477CA0CB46BULL, 0x71E149597CB781D7ULL, 0xB806DE7E691A15AEULL, 
            0xCC4C5DA3108899BCULL, 0x5EE6D5C3C98700A6ULL, 0xA578295706D0457AULL, 0x1EA88C705AA26655ULL, 
            0x5B25831C90AADDFAULL, 0x33F51468F6F5E67BULL, 0xEDAE986A46DA6F69ULL, 0xC3870AEB60BB1F69ULL, 
            0x8F308EC41D5E7F69ULL, 0xFE75BE03932AA398ULL, 0x037CBA08BE347149ULL, 0xF1E00A51224092D5ULL, 
            0x54B9735FA5A30F5FULL, 0x34591E4FE2AD76D2ULL, 0x5E606050C4A5CA85ULL, 0x9676EFB1F3F85586ULL, 
            0xB97906DAB44B7955ULL, 0xF289FC28A78F7822ULL, 0x3770C9E13BDF1320ULL, 0x5EB0F0609E0B7F4AULL, 
            0x4335E313410CF9B6ULL, 0x7EA27F5EF70D8AB6ULL, 0x75216032EA068CA7ULL, 0xAFC73356C0160BA0ULL
        },
        {
            0xBC8CCDC410D23786ULL, 0x1992899C3FA08C55ULL, 0x00CA0EE31DB8CC40ULL, 0x475451FE44295AD7ULL, 
            0xCED3BD8F3A90F226ULL, 0xC2FCADCD61E68A2CULL, 0xBBDD3478FE5E1BB0ULL, 0xB4A4FB23AF29A7D9ULL, 
            0xCA7AF043D9860A9AULL, 0x38ACD337A861D7A7ULL, 0x00807A3F4ACCDD96ULL, 0x89B00B9F17BEDA9EULL, 
            0x00E3FA5778C67FDAULL, 0x2C994E9CF93E9D55ULL, 0x0502AC2E01A8D432ULL, 0x30BE26B94E8A980DULL, 
            0x72F2562455C30B51ULL, 0xDE6690B9E57AF43FULL, 0xA0ACD6A933F5AC41ULL, 0x760B5A4A4C8ABFEFULL, 
            0xDD287199355C773AULL, 0x7EA16B1981B9DAA5ULL, 0x2AF6B054E8E98228ULL, 0x7623BB9A7904F227ULL, 
            0xE8783957D992B749ULL, 0x99DAC3BDA33819E3ULL, 0x4D8C68208BF67A0EULL, 0x1DEB529E803FAE24ULL, 
            0x55CAE38AE6A9B809ULL, 0xFBC5391E1D18990CULL, 0x0653D0AE3DB26433ULL, 0xE68FFEDB7B6404D6ULL
        },
        {
            0x504F45C0DB940CF2ULL, 0x96C8015CCC84B210ULL, 0x26BB5B79A0ACCE58ULL, 0x760ABAF73390D90AULL, 
            0xC22A611E7D3EAA9CULL, 0x074DE43F6E555B3DULL, 0x2FD3E7AA315E12EAULL, 0x485BEEEF7EF5F4A3ULL, 
            0x92B708F03840A868ULL, 0xD5C56BD493FA62F6ULL, 0x4C7BFEF53F7831ACULL, 0xA4ED6F54F2A86133ULL, 
            0x160FBCD1060DCF6EULL, 0xA52F95573986D386ULL, 0x5B137625F1E0A05CULL, 0x99C44FF5AA859CA0ULL, 
            0xA9B93679A415CE78ULL, 0x4921E31EA9FA460BULL, 0xF6F30C9E6029E855ULL, 0x12D26EBD19CB9F0EULL, 
            0xA1EDA402EE87694AULL, 0x9073A66554E946E9ULL, 0xE16CC39E3FAEDD7FULL, 0xA030811048A57F0DULL, 
            0x3B270C354E125238ULL, 0x8A01635B112FA998ULL, 0x503333D030C0E4FCULL, 0x3791AE5198739A59ULL, 
            0xDD744AC885A564B1ULL, 0xE6D28F016EFAFD15ULL, 0x653B55A3A87B681BULL, 0xA14F1F0F69149890ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseAConstants = {
    0x078955A32692DAB3ULL,
    0x243E330224ED1C8BULL,
    0xAE974D09B977B780ULL,
    0x078955A32692DAB3ULL,
    0x243E330224ED1C8BULL,
    0xAE974D09B977B780ULL,
    0x9FA335EB71EDE443ULL,
    0xC8CB2477669114E1ULL,
    0x02,
    0x35,
    0xDA,
    0x3B,
    0x15,
    0xEA,
    0x19,
    0x57
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseBSalts = {
    {
        {
            0x7EAABFE7DAF068F4ULL, 0x0971F146EA26BFC6ULL, 0x1B0136CC3F088421ULL, 0x02B06F9E6F6710A4ULL, 
            0xB7F66A60560E43D5ULL, 0x1CC4AC2FFE6B16FFULL, 0x392965483E225FDBULL, 0x52AF2B5152657C81ULL, 
            0xC08977CD0432FE23ULL, 0x94D9EA2260D30F02ULL, 0x5DAB3649D909A2A2ULL, 0x5567CAC13E9227B5ULL, 
            0x298F48638F61275DULL, 0xE08167053A6CB4CDULL, 0xE11164D9A8C49B62ULL, 0xE96712DD6A5B7FB3ULL, 
            0xBD6F2E8345D9399AULL, 0xA8716CF62BDF2DEBULL, 0xFB605A5EC55F1ED5ULL, 0x8B787C3ACFB98317ULL, 
            0x9FBD94175CB23B29ULL, 0x1C78014F7DA2082CULL, 0xE09CDE896186D9B8ULL, 0xC97126D6B092A2BCULL, 
            0x00A3F5FEA51E1B59ULL, 0x4A214DCEB19FDE08ULL, 0x361CB66AD194E899ULL, 0x02652F4838A9EB43ULL, 
            0xCEEF15D5042A5587ULL, 0xCF8BF4FF69F9378FULL, 0x389FCCDB5C60269BULL, 0x3E6BA6D4991594E2ULL
        },
        {
            0x410543D33CF1D2F1ULL, 0xAE0AE8FE0422C2CDULL, 0x623BF0B387A87B74ULL, 0xE2E9AEF59FD7AC85ULL, 
            0x9F1942E4B4BF6EC4ULL, 0xA95F73CE5A5A4372ULL, 0xFCBD2855AFD29CE3ULL, 0xBF3181754CDE9E9BULL, 
            0x907AC3A013809E48ULL, 0x729EC3067B614F87ULL, 0x1357A5ED17811126ULL, 0x22BD2285A5107E17ULL, 
            0x2C91144659DAE679ULL, 0xF31F2A0A89E301B5ULL, 0x7F2F20E5CC84177BULL, 0xE39122C58E7AB74AULL, 
            0x3CB5918268F9F653ULL, 0x6BAC82E857A824F7ULL, 0x0BF3A552833EF96DULL, 0xA7FDED317B8E79DAULL, 
            0xD53D0C34220F3F5EULL, 0x362FA7576D12C15DULL, 0xCAEE7D96A065AF1CULL, 0x25AEA40A48E0FD8EULL, 
            0xF09CC459BB3689DAULL, 0xF628692A6F5BDB0AULL, 0x7DBFFBD027947554ULL, 0xA076A91F6972C8ECULL, 
            0xF8AD843F8C214B0FULL, 0x96784946B877921CULL, 0x48B9782B52A573E7ULL, 0xB4B5DD3038818758ULL
        },
        {
            0xC02A62CCB346E0C2ULL, 0x5ABB22FEB08C7232ULL, 0x6729F1C8172EFE38ULL, 0x701250286DA09924ULL, 
            0x5827CC7D56727194ULL, 0x875FD0082BD107A4ULL, 0xCC4651EB767091CCULL, 0x873FB1CCC6FC0B9DULL, 
            0x74AEB39D24361731ULL, 0x7712A17F6A2C9ACBULL, 0x9E1323A5E11C6D02ULL, 0xDE979F0FFEC1A297ULL, 
            0xBE51CC1E69CC38C1ULL, 0xABCF0A03FE519478ULL, 0xDE347952A68AD48BULL, 0xF7FDDFA2AEA7AF1EULL, 
            0x181F004A4C8FD640ULL, 0xE6887DE8AD9097A3ULL, 0x2714C62336F642FFULL, 0x36B2FCDCA3ED090EULL, 
            0xB0059AD46FCED7C0ULL, 0x2DA016398CBE2FB9ULL, 0x4CE6AC1193957020ULL, 0x490B9E21CF0CF839ULL, 
            0xB574C4D606CB29C3ULL, 0x596640C8908DE18AULL, 0xC1B77CEB843BF107ULL, 0x2806CB62B0111D48ULL, 
            0x266996FE06EFC383ULL, 0x4C0ECA60F355D642ULL, 0xE6739F72C90E99AAULL, 0x29D8F25D3C554AB1ULL
        },
        {
            0x4367B6678F1E3E35ULL, 0xED51B0C1FF3A2127ULL, 0xF7E5487EBE09E314ULL, 0xACDBA1C29E798B3EULL, 
            0xB62B1DAEBD11DA01ULL, 0x29A4F42E0DF923D7ULL, 0xE0D0B18B239F6A96ULL, 0x29BE2EB783046808ULL, 
            0xA2027F63706376AFULL, 0xFF2B127AF3C7FC97ULL, 0x55288CB6AEB9CEBFULL, 0x91E0962DFD817273ULL, 
            0xF87242723C5FAF23ULL, 0xE29C9DD21C856042ULL, 0xD897CE11B87F8D0BULL, 0x84800FFBA44BE69AULL, 
            0x3BC6C8293DE74FE9ULL, 0x312DFEDFF9EA1E8CULL, 0x37A20B32ACC8C8AAULL, 0xFCA3213E613F1AAFULL, 
            0x9AE94ACBB3B5DE2BULL, 0xE79DA2B0FAB668F6ULL, 0x5E0F90C73D5F382CULL, 0x6D19B9DD33E1A6DFULL, 
            0x1EC139EF165BBF4AULL, 0xE5D093021FD3E5B6ULL, 0xDB1D2AC55D032AB8ULL, 0x3C606FFBB8365A97ULL, 
            0xFDE8866684D23E69ULL, 0x26ABD020BF71AAE5ULL, 0x0070391891597F51ULL, 0xF654528DAAD91CE0ULL
        },
        {
            0xA8A6C411CD7D5976ULL, 0x9F1C4AE3D6A801F2ULL, 0xF156975063627645ULL, 0xB59A66B5A6025E93ULL, 
            0x42EFDAFF50D7D371ULL, 0xE3C7DF5829103A49ULL, 0x2A67DA6E23616062ULL, 0xAEBA19AC0A888950ULL, 
            0xFC24426DDA866009ULL, 0x638BA5742FCED1A9ULL, 0x51B9219F0F093297ULL, 0xEB4E3D4670A2D4BBULL, 
            0x978924AE08759296ULL, 0x409930F5E34799BEULL, 0x2C7501871AA47A1DULL, 0x41B776F47B9C523EULL, 
            0xD9E49F37A5C98CEAULL, 0x126372485B0CA167ULL, 0x5AE745A3CD2BC2E1ULL, 0xEDD91CA9A6535FF0ULL, 
            0x87AAE5609C74BD02ULL, 0xF8FA0DA204A5143CULL, 0xB726F08219699264ULL, 0x9BF6E53B33A53206ULL, 
            0xDC94E016CE958E88ULL, 0x68CB68698EB7AF78ULL, 0x9EE15C9170EAEDD3ULL, 0xD111F9AC09F0E0D6ULL, 
            0x5C14019C01216A24ULL, 0x7931DD3542B1081EULL, 0x1755DC770DDD9CBAULL, 0x92ECE2C7958D5069ULL
        },
        {
            0x7660131E519085B6ULL, 0xAFF71104B6711D2BULL, 0xBCBBDA27E9EC6F4FULL, 0x6612244EBDFCA16BULL, 
            0x2DE91180AD23B4BCULL, 0x7FF1131C26F41E12ULL, 0xE8EF52C6FA7E811BULL, 0x4AD789497C6311D6ULL, 
            0x36DF9264349B64E3ULL, 0x052CDDA2A6DE6380ULL, 0xCD8DEB557381F3B9ULL, 0xB36252EF27357A63ULL, 
            0x3921B3CA5777E02DULL, 0x1B508DD1D6F89A7CULL, 0x5EF44CB062FF70DAULL, 0xB1361548CA0129F1ULL, 
            0x97592CF4D6EC7190ULL, 0xB40E98FD0846D5F9ULL, 0xEE7997B39E9C2108ULL, 0xB6DBEB28FD2DBB23ULL, 
            0x87D44F7F661A47A5ULL, 0x3D8EC43B81F9A97BULL, 0x5DF44D85ACE13FDFULL, 0x8983FEF93FC1F3A5ULL, 
            0x792C1D6F61210BCDULL, 0xB2E55C646DD69AE6ULL, 0xAC290003CD14A76DULL, 0x426F1555428176E7ULL, 
            0xEE962B876F805AB3ULL, 0x96F4973DF448A223ULL, 0x7138811619CCEF02ULL, 0x44026A0232F52A79ULL
        }
    },
    {
        {
            0x21FD7F58596D60F8ULL, 0x4E7DB7EF25B6BF69ULL, 0xD1DDC3283BC4C3CAULL, 0x7D0E2324D6989610ULL, 
            0x300ADD86215691C1ULL, 0xA007E42C29F9C97CULL, 0x278CF0AD2739FA1EULL, 0x275CA1AAEC1B732DULL, 
            0x5A86F5CAF1FC309BULL, 0x7322DB3044B5AA86ULL, 0xB229F02E133B865DULL, 0xEA7E860932607412ULL, 
            0x8FE49D97D8F5C299ULL, 0xA97ED045E0D424B0ULL, 0x9C94B7F136AE95F5ULL, 0x4586BB7E04700A6FULL, 
            0x5C6309F33ED0FF49ULL, 0x33C0585B7465E0A3ULL, 0xBAED849630812D8EULL, 0x5CBD315E16775033ULL, 
            0x0937B6C47E32A3A8ULL, 0x29C969B672F93F35ULL, 0x19C206F113431A2CULL, 0xABACE7667F80F25CULL, 
            0xC139903078FBFBCBULL, 0x5D8443DFB6AAD134ULL, 0x082DDE76F62DAEF4ULL, 0x4696BA5506A9FD16ULL, 
            0x5602832B1CE337E7ULL, 0x81B1819E3F8FE7B2ULL, 0x1BDBD9A8C3E5AC18ULL, 0x2DC1A17BE01B6083ULL
        },
        {
            0xBF5156B88E470DA0ULL, 0x9EB2F14E2DEB6D88ULL, 0x3BB2EBC3B8BE7AAAULL, 0x2A1868BCB46E3673ULL, 
            0x0359465BCE10757AULL, 0x4B5509D1EBA50AAAULL, 0x83CE26F23DB5925AULL, 0x96A8FC8FE9395DDEULL, 
            0x9328FC5DCF818481ULL, 0x9F84BC96C24A8529ULL, 0xF44CA693B840AA48ULL, 0x261BEFD051A3BCA8ULL, 
            0x9327748AE28CD03DULL, 0xA23F57539CA95954ULL, 0x5556542389DCB665ULL, 0xD8E86EEFC769C21FULL, 
            0x7E814D4A30104EBAULL, 0xE58FB8B483499876ULL, 0x6C26957EDFE372D7ULL, 0xF6462AF7E082B2ABULL, 
            0x8DB8B86D4EE74F63ULL, 0x1E8A57C6B2261CDBULL, 0xD5CCB70C0F968EC3ULL, 0x42C8CA96D03EB5D2ULL, 
            0x59FD80C14589E8DCULL, 0x6BFFA92171B331F9ULL, 0xAF3706E87F721643ULL, 0x299EDB494421D9A4ULL, 
            0xFFABC76A9A394173ULL, 0xCAF101684011AE9FULL, 0xD8E3C2200F9ECAA4ULL, 0x48D60D729962991AULL
        },
        {
            0xED8C5CC27ACEEA68ULL, 0xC36115D015327F48ULL, 0xE542B7194B64244CULL, 0xECF9DDD20A0A421CULL, 
            0x589E483D7492D03CULL, 0xCB148ACD68577BCBULL, 0x8D0BED78E286EDB3ULL, 0xA7C6378729A9924FULL, 
            0xC9CD744F9F15002BULL, 0xA64528625F3453A9ULL, 0x1D3C9B75DA281E36ULL, 0xD7979A1F2CE2101FULL, 
            0xC3984E04D21CF4CCULL, 0x30A6097992862C30ULL, 0xA8318AAF7012E8DCULL, 0xE6D1D741451EA5F4ULL, 
            0xC1FD57BA56046753ULL, 0x7CD8965D10851F41ULL, 0x235C8DDBDFA0C4BBULL, 0x4B8F2A68419EE116ULL, 
            0x44E573FF9402FA98ULL, 0xC6E7D81D11CEF084ULL, 0xD681CFF0D9BDF192ULL, 0x254EAB91B2D6D914ULL, 
            0xC493238EB62CC08FULL, 0x128F4C73F169FB3DULL, 0xAFE0E5DCC4582EA4ULL, 0x7DE3E84F720D2CC2ULL, 
            0xCBD2BF9154C1D763ULL, 0x4FBB0C0C2684A042ULL, 0x2CA654FE596FAB2FULL, 0x3AEA4936A9943F26ULL
        },
        {
            0x4F6E6D231E6433EEULL, 0xBF4FF1E83186892FULL, 0xE34933CCC965DD7CULL, 0x76913D8F5C4A938AULL, 
            0xDF5F18B86A6B3A03ULL, 0x7C42EED794839B22ULL, 0xEB8A84BA27D5F051ULL, 0xD29D4D160EB2C661ULL, 
            0x21A2131B96638095ULL, 0x3CEAC2748A5AD77AULL, 0xC915E4A47F75845EULL, 0x2D5CDF2DAA8F9AD9ULL, 
            0xEC29CCA2D583C823ULL, 0x16F93A93C4779E7DULL, 0x8FED626D03188BF1ULL, 0xD46C3A7BEF8B1B64ULL, 
            0x221886FEA4EC82BCULL, 0x105A71EE2C62AB46ULL, 0x531617D7B61243C3ULL, 0xABA70702E86C0268ULL, 
            0x807AFD03639982D0ULL, 0x08C7896F0A648163ULL, 0x4F949B1292705D46ULL, 0xC2864C862D4BF71CULL, 
            0x68135242A10A360FULL, 0x6C896A4673E1087DULL, 0x25A59AD07442568AULL, 0xD2B4A4C6D29B7C04ULL, 
            0xEA7ACF8573BF9730ULL, 0x56735E27F3E34C68ULL, 0xC5FF9B1FEE11F6AAULL, 0x9AEBDFBA3A77BE37ULL
        },
        {
            0xCB218112D8902AEBULL, 0x6F8332415D4F555FULL, 0xB475227906A230A4ULL, 0x587C709B045A632FULL, 
            0xC33076772109B1A3ULL, 0xBF9135C8B4121E6DULL, 0x771C4AC000C6DC43ULL, 0xEDA75B66511CB0C0ULL, 
            0xC87C9BBAB687320FULL, 0x7C95578FFB1902C2ULL, 0x131618E622E38AA7ULL, 0xD5527383F360A836ULL, 
            0x93B8D8157D653DA5ULL, 0x0ABC0D4BDF0498C5ULL, 0x7310BFFFF522068DULL, 0xD6ED72CED6B45CCFULL, 
            0x2B0AC46EC6A3BE20ULL, 0xB1FBDAA1424E7E52ULL, 0x75C27A4AA812228EULL, 0xD188F0B793B22584ULL, 
            0x653A55B5A6FE73A1ULL, 0xC8B4598F327F2734ULL, 0x325FED5BE207FD4AULL, 0xBEFE4008231E9CE8ULL, 
            0xA8A58F2CF3D836AAULL, 0xBCD86B4BC6C94A69ULL, 0xD276DDA49D3DC201ULL, 0x316615AEF0D34A22ULL, 
            0x4E5DEE6173706268ULL, 0xFE92332FF4AFB6FCULL, 0x1B4D6E91E5C1DEACULL, 0xBB3D7B4FF084C456ULL
        },
        {
            0x04B462127EE77B07ULL, 0x1E259F1B15065043ULL, 0xB755CA6CE1057839ULL, 0xBE01C8BEE715C905ULL, 
            0x9EBCC21A14788FD6ULL, 0x9CD3679A378648FFULL, 0x5EC898C3F75784D6ULL, 0x43E1C98D70D3E9D1ULL, 
            0x9A190EEEFA3894F5ULL, 0x98563CDC875B163CULL, 0xD3E29764D44673F9ULL, 0x14F7D33954DBD095ULL, 
            0x143EA80EA190EE1BULL, 0xD0A6BB15C444F40AULL, 0x09625A3C5850C8A4ULL, 0x2DF49E3FFC003543ULL, 
            0xE67C175CC56C9778ULL, 0xF3FDC8E58DD15DA9ULL, 0x370B38C03B4FB679ULL, 0x1621D10F99EB3EE9ULL, 
            0xD5BEF002EC32B811ULL, 0xACB86554698A662BULL, 0x1FB619507C7CEE33ULL, 0xC21B1BBE22B4B02EULL, 
            0xEAA6B10A1919D26CULL, 0x4E21C932FA8453C2ULL, 0x3725875DD0ACC376ULL, 0x847E380B006BA856ULL, 
            0x3F066C4C67DA6E53ULL, 0xA1EB7476027E8B37ULL, 0xB1A6FFE137F369C9ULL, 0x1662F987B3E046AEULL
        }
    },
    {
        {
            0xAD76722C8C7DF2C1ULL, 0x414E2C28B8000431ULL, 0xCD2058CB11FCE912ULL, 0x1C41A18FC439BA66ULL, 
            0x44238A6DC6FA9CE1ULL, 0xFD9FFC88E0CB2D1BULL, 0x2935403B50B0BCD4ULL, 0x1C3EBFD3668D49FDULL, 
            0x888C0B7F80552D88ULL, 0xBDA2A51C9753E139ULL, 0xC7EB99E2C791CDACULL, 0x4BDADBA581877B9AULL, 
            0xDD2D7A0377F6DECDULL, 0x3E0F4A280C11879AULL, 0xBDF5260BC80F4F1BULL, 0x7A171607BBA04149ULL, 
            0xBA900D04DE883793ULL, 0x93ED926C34003B8CULL, 0xFEBEE052F11A52ADULL, 0xDBDBFA65127902A7ULL, 
            0x2D58FCC5C57AEF7DULL, 0xF0B349F4E929BB03ULL, 0x6E9B6ECF21C359E2ULL, 0x751BE05550ADB93FULL, 
            0x5167D5EA5C56AE04ULL, 0x27C88849FA6E1FBBULL, 0xCEB9141E9BBFD4F9ULL, 0xDEACA107F36766D1ULL, 
            0xA941A759C68D875CULL, 0x49C6FED0B23C783EULL, 0x70A20C302F46301BULL, 0x1E5A69ECB3DA5417ULL
        },
        {
            0x3AD0507FEF08EBE7ULL, 0x0A816FD948D49F29ULL, 0x2412E580A0666F70ULL, 0xD488C593042E9D7EULL, 
            0x47D98D3FCD08B225ULL, 0x49A5ED3671DCB61DULL, 0x2C7987E9D336CA65ULL, 0x4C94F89E81EFB948ULL, 
            0x1FD3818075267031ULL, 0x8083FE0049D459A1ULL, 0x4F0494012106022AULL, 0xBA77980D0C6C5E52ULL, 
            0xF7059D8DB4597BD7ULL, 0x1BB6BA5FD852F4E4ULL, 0x88F4F2EC8B4D6EE9ULL, 0xF42538179471C5FCULL, 
            0x60E209EC2EA35A7FULL, 0x780CC9AE8BE37DD7ULL, 0x4EBEAC82599A006CULL, 0x38ACDE4D6A5EDDF9ULL, 
            0x911F887ECF3947C7ULL, 0x9F9B1C87D4913D70ULL, 0xB9BBE1201BB3AA80ULL, 0x35AE79FA3BA382CBULL, 
            0xA192A20431DBBCFCULL, 0x3DB6E469B9A3C7CCULL, 0x9B07FDFC9ACEC1CEULL, 0x70AF268CA20C31A1ULL, 
            0x88F3B55B6DFC1C10ULL, 0xAF1338F1DDBD9B96ULL, 0xCAA804444753001DULL, 0xEF1BF685D9C7BC10ULL
        },
        {
            0x1B90C4F1D61DAC14ULL, 0xFA3F34DF25BC4D41ULL, 0xE218F57274AFE6D2ULL, 0xD672FA9E92263087ULL, 
            0xAD23BC0B817653FEULL, 0x44620BD2BF809FB2ULL, 0x1B9893E539CD444CULL, 0x387DA92A9DE23C68ULL, 
            0x5466A84F812652CEULL, 0xEE21C0FA04C410B2ULL, 0xCA8731A8F4CFB41BULL, 0x79D8C97AAA4AC18DULL, 
            0x921C885746DADE1EULL, 0x0C0A5A15E1FDD158ULL, 0x2CFF78207EE6C52DULL, 0x755016F0462EB4EAULL, 
            0xEB8C7654530976F5ULL, 0x4E755AD4CE0B9813ULL, 0xBE5D318D6E22CD8DULL, 0xC4328B4F6A58013DULL, 
            0x6159775252213B14ULL, 0x34B2DF7CEBB3DB84ULL, 0x4155DB08D0AC7B77ULL, 0xA5C89E1DADA907E0ULL, 
            0x9F34D5A9A868E9CEULL, 0xCED5BB971801CEFFULL, 0x6741D9D42572281DULL, 0x3905B9C37E205079ULL, 
            0xFB77047521C54ED8ULL, 0xAA73559A85E6F4FFULL, 0xC90208698C9CAD95ULL, 0xDD2A0A5437E9B85EULL
        },
        {
            0x543DE2FF578C77C6ULL, 0x06DD98016E05B73DULL, 0xEBC11D56242C3C0FULL, 0xA53D9BF94776DFCFULL, 
            0x8F473421D71452A8ULL, 0xFFBCEF73AC35529AULL, 0x47FB29513E42F3ABULL, 0x1BB728DEA31D7FE6ULL, 
            0x232248DBEEEEFB03ULL, 0xB9A3674E617237DDULL, 0x4A14BE8B2D187F8AULL, 0x59A7130E2D54A458ULL, 
            0xA4AF297E3090125AULL, 0x1F47452B4BC4EC79ULL, 0x4CF83A89E8EA7A61ULL, 0x8136FEEC12B46CA9ULL, 
            0xD3003ED3F8EC355EULL, 0xF63B163EDF90252FULL, 0x6FE36827DF609A43ULL, 0xB63BFC4016E2AF9EULL, 
            0xBB64438AB6E8FFCDULL, 0xB157CCE96F8757D4ULL, 0xAB7EFD2F307CB0DFULL, 0xC5C09CCCBA099AA0ULL, 
            0x441AA7F32B8F6F35ULL, 0xB5D784CBF37C2A90ULL, 0x51108C74B9AF954DULL, 0xBC730D69718BBF6EULL, 
            0x0BBC2234D43AEE65ULL, 0x3C2CADFAD48E49F3ULL, 0xF59ACA1AB394173CULL, 0x9A5BD1FCD2E97700ULL
        },
        {
            0xD12FCE3C8994AF03ULL, 0xA77945ADB3D88DC8ULL, 0xACB6C07EE1E03F69ULL, 0x0C1204E51C908BD0ULL, 
            0x1C15A855825B7027ULL, 0x2FD0235EFA4D4F32ULL, 0x82A9B0D68D50E036ULL, 0x99A24EB831646338ULL, 
            0xA2BA6A25BA4344F6ULL, 0x814CF54EDEBD1CCEULL, 0xECC21F6571FCCD80ULL, 0x119B9E6A6ED6016EULL, 
            0x9743B4E1B2CE0B6BULL, 0x83F092544F45844AULL, 0xB8F8105DFCC2A207ULL, 0x3C41B12833205090ULL, 
            0x9A85A53CF9F55CE4ULL, 0x248B6A5CE80606BDULL, 0x736F1C9EF15272D0ULL, 0x9E4079E884D9DBC9ULL, 
            0x40CF7A3A91957E67ULL, 0x4F48E56A40ECA1F2ULL, 0x5ADB998E813F05E3ULL, 0x45EEA741326A6F30ULL, 
            0xD2D05C09F491DC29ULL, 0x26B74858EEB06FBEULL, 0x1A8A281BA16CBA26ULL, 0xE0E7B86AAFC2654FULL, 
            0x21AE18D518125E0AULL, 0x41176C3C78DC4A33ULL, 0x6E7F8037DAF2D965ULL, 0x9F47168173412F66ULL
        },
        {
            0xE21565EF0D73EBCDULL, 0xF055B626352E73D4ULL, 0x35103574810BB472ULL, 0xA86F20E2270D431CULL, 
            0x64045159AD596F22ULL, 0xC63B5DDA37EECE7EULL, 0xA58B13BA2EFDA145ULL, 0xF2E0AF797C5F968FULL, 
            0xA249DB6412AF4E12ULL, 0xA898BE4FC657268DULL, 0x4260C9049600BA49ULL, 0xA98E332D3CFFCE1BULL, 
            0x5F3ECD22B194DBF7ULL, 0x68B8ED52B309B90AULL, 0x867507B7088F6CDEULL, 0x8BDC37948C60BBC7ULL, 
            0xA023A19762916E01ULL, 0x24759FFE38A68D91ULL, 0xC7CD137F042BF9B0ULL, 0x9A239807162CC417ULL, 
            0x8797ED9E84E5A66AULL, 0xEDF1940ACED799D7ULL, 0xE6511ED95A083210ULL, 0x06595394AC66FCB1ULL, 
            0x5F3EB9D7CD931863ULL, 0xCA832A925696F5B2ULL, 0x160A5E5C7A1B2612ULL, 0x024F2C7534FB191AULL, 
            0x9BAECCD44E883D3AULL, 0x7F1466025E4850A8ULL, 0x05A5E4A03FD3175CULL, 0x8F3389685908EE4DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseBConstants = {
    0x30BE8FE497996220ULL,
    0x494A0F0DE4A137D4ULL,
    0xCF05C8FDA9091029ULL,
    0x30BE8FE497996220ULL,
    0x494A0F0DE4A137D4ULL,
    0xCF05C8FDA9091029ULL,
    0x44D679219641ED78ULL,
    0xDED99BF17BF63CC1ULL,
    0x27,
    0xE5,
    0x81,
    0xDD,
    0xB6,
    0xCE,
    0xDD,
    0xC6
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseCSalts = {
    {
        {
            0x253964E8BFC6FCC1ULL, 0x1E3ACF88452C304EULL, 0xECFE467C61900D07ULL, 0x19E0D2E8DDFF7C9AULL, 
            0x18DF28D88B776ED3ULL, 0x96E482422AB6AA69ULL, 0x02FFFBE7AFC4CA35ULL, 0xC8662B1C3C219D7EULL, 
            0x987AC79BA7682E2EULL, 0xC18C62C5B5FD2F30ULL, 0xEED7366EE85F4232ULL, 0x550D3BE6000271AAULL, 
            0x2F923883AA931278ULL, 0xE69BF04D0148C0DEULL, 0x338AF115D8FF9A97ULL, 0xA41406CB297E036DULL, 
            0x0EBAA0B37B0DA212ULL, 0xEF1C964F18E19F4FULL, 0xE7F3CABF829FD975ULL, 0x70877052F76605E9ULL, 
            0xED69A582A001D51BULL, 0x6CCA9C163A554580ULL, 0xF94E1052735F1F83ULL, 0xE277577DD4DCE003ULL, 
            0x45B929D3F37991E5ULL, 0x609C6B639F7A65D9ULL, 0x981CC159ACD8A89FULL, 0xB207C43ADB41BBE8ULL, 
            0x448CD0424850DAF5ULL, 0x865CBA9F815D4A01ULL, 0x22EBD080F1D6FF28ULL, 0xE842BA1A58E80633ULL
        },
        {
            0x232F050F26010802ULL, 0xBF7FEA001BF60AFBULL, 0x87EF7A4F4D78A22BULL, 0xFC50D99427ABBD78ULL, 
            0xFA6239C4DF418977ULL, 0xEA5377AB7BA7F8C3ULL, 0x7A0578142E68D8A5ULL, 0x86FD4F6049A04B9DULL, 
            0x13FADC929C402827ULL, 0x4EEC941FE873D202ULL, 0xBCA639D71C100123ULL, 0x74E8DD7339D9E5C5ULL, 
            0x206EDA7480E2D17DULL, 0xDF213B3B52DE3706ULL, 0x231359A8EE622CE7ULL, 0xAF2AB0DBC2E4FF6BULL, 
            0x27E676670D8176DBULL, 0x23E7547CA0A22DEDULL, 0x8E973FA8691D61A7ULL, 0x1484FE5DD354FC37ULL, 
            0x26F91A09978C7836ULL, 0x1F0297B57C5361E0ULL, 0x85BFB3772BEEC893ULL, 0x2F4DA0B9A86981E3ULL, 
            0xDC3429A451EB9753ULL, 0xDE11C7584FE05541ULL, 0x43CD5E12288DDBE6ULL, 0xAC56C3622D045C48ULL, 
            0x0D28C365FCF77E09ULL, 0x7B395CB19F97F79CULL, 0xC41B097C3C6ABB3DULL, 0xBF4BBB5217BC6B71ULL
        },
        {
            0xE402A3D83A985756ULL, 0x2B0FC3EDCB13A9D0ULL, 0x643CBC591166D13EULL, 0x48ACC4E895A2DF05ULL, 
            0xD01C70743CB85EB2ULL, 0xD54703B98FEC98F2ULL, 0x40E27B5D83A5711CULL, 0x020A4421DF38C942ULL, 
            0x32ABAEF151CB83AEULL, 0x1CF685F0D82F0C49ULL, 0x4F05360B14D27068ULL, 0xC2F01CE60A781D77ULL, 
            0xCBEE4AD45BCA3A2CULL, 0xE6391266544D1084ULL, 0xA6A226C2BB9D86FAULL, 0x12B67F691A395559ULL, 
            0x24E3FBE7C7E7E072ULL, 0x7126FC6DFFA15D8BULL, 0xFCAA92EFC33C50D4ULL, 0xE6AD7C36B7D849C7ULL, 
            0x652158FBCA70B88EULL, 0xDDFF9AADB1DD7A08ULL, 0xD1154535AB3D61F4ULL, 0xCDDA39295755D474ULL, 
            0x98F9D17C5E061097ULL, 0xCFE74FD244956B12ULL, 0x90209C1EE9BD64E7ULL, 0xBD38E0D297DE1F03ULL, 
            0xA06AAA8BD0C39FA1ULL, 0xC949461C7CC77BB8ULL, 0xAF4F17100C5ABB4AULL, 0x4251DFE6C79570AFULL
        },
        {
            0x4BA94CDA35105ED8ULL, 0x1E0D7B77DF52FAE5ULL, 0xB19E8EB3F7BE2904ULL, 0x43F8A3801E142217ULL, 
            0xB0FB30470D23368CULL, 0xD7ED11D8A8516367ULL, 0x2F3906DF9C08FD1AULL, 0x00A1F8BDE58588B2ULL, 
            0x76B145521073515BULL, 0xCF422E02697E3AE7ULL, 0x03441B57EB81BE2BULL, 0x4CC345E147C72DF7ULL, 
            0x615DA290CC5EEED9ULL, 0x0E68CB6F7C54959DULL, 0xC7D4293E7E21B777ULL, 0x01AFD32DF78F9E50ULL, 
            0x845330B6320F8796ULL, 0xEE8E799790025191ULL, 0x9D40CB50412388B7ULL, 0x6AA134526583A73CULL, 
            0x3D1E05389DB0A7D8ULL, 0x14D7BAA7639EF2F5ULL, 0xFECB7450A1F49711ULL, 0x4847F069633D6B49ULL, 
            0xBD7A6DDF78DD6243ULL, 0x2B436F4A3527088AULL, 0xF1CB7A6ED3EBAD08ULL, 0x2A5A3856A94D17CBULL, 
            0xD32F3E465CE58013ULL, 0x58D3DF8AC95B5AA2ULL, 0xB988A636ED0F42AFULL, 0xCFC4BFA8917F76D9ULL
        },
        {
            0x6749951A450AA69BULL, 0x5F53F83EBC26BDFCULL, 0x491E6F8538EE0B1FULL, 0x4F2C672777079127ULL, 
            0x15FD9654382980DFULL, 0x050C9FB66A828A0FULL, 0xE25EBF15FB3718A7ULL, 0x5B78727ADDF7175BULL, 
            0xDC6B0DF010F9F0EEULL, 0x2AA98C41E8CDF59CULL, 0x61E252DE10CD4A4CULL, 0xCD1603129757BF0FULL, 
            0x6B14179DA79E1063ULL, 0xAF9C78B3ADFB7F58ULL, 0x26820AC8E5A81E0BULL, 0xC8F225DAF5F46F5CULL, 
            0x8BBA310C30A670BDULL, 0x859FB9DB96C93E3BULL, 0x8EA4F5CD19DCB81FULL, 0xBBB622B605234B00ULL, 
            0x23682B12564E9AF7ULL, 0x8B075677148361CDULL, 0x1A30CFA0AB112719ULL, 0xDFCF0CFFFF79E29CULL, 
            0xDA9C1ADA5E07E58DULL, 0x12B399C5968A12FDULL, 0xFD26D8036B3EC806ULL, 0x005CE302281B43FFULL, 
            0x6CB0969BA4525CB4ULL, 0x6B108264249C440EULL, 0x1219A482C9587E2CULL, 0x55B0141930906F53ULL
        },
        {
            0xD3703672A7BBF4ACULL, 0x4A85D7D36F0DF73CULL, 0xCDBEDF34258F04ADULL, 0xED91C459CBC86386ULL, 
            0xA68148B49F7F5A00ULL, 0xA9986F49B8D33730ULL, 0x1F35D61030CC02C8ULL, 0xF2457F814D929A85ULL, 
            0x4577B45A289C0F8BULL, 0x33BCA0D3AF24D600ULL, 0xDF94352AE4168F0EULL, 0x4001BBB38661CDFFULL, 
            0x8BD34A4563BD56DDULL, 0x6483EA92EA5164ADULL, 0x6191C60D06454339ULL, 0xB38C7A06180B09C8ULL, 
            0xE6416382EEC67EF6ULL, 0x0E03E99B2DA4E8BBULL, 0xCD82382B1053AB80ULL, 0x895FDA9AF033AB0FULL, 
            0x5FD542A5325FD9AEULL, 0xA8A216D4D5DE0537ULL, 0x81BECD5CEE4EAE57ULL, 0x267203F20BD1FBD3ULL, 
            0x25B4762A38BC2570ULL, 0x55BB3880BA0549CCULL, 0x3DBD1DBE3A49A26AULL, 0x271192188729AFD7ULL, 
            0x8222589FE70A1A21ULL, 0x8971DB482ED85D3DULL, 0x07111ECB901693E1ULL, 0x246BCC6E1E76AAFCULL
        }
    },
    {
        {
            0x07FAEE5243CBBD98ULL, 0x4BB92A62EC2DE60CULL, 0xFC4EBD45B8FC99F4ULL, 0x19DA908E713212A1ULL, 
            0xC16D8A969312CC19ULL, 0xBBA47C23C7717F3AULL, 0x1FA85363AB8826FEULL, 0xBF208690BDC23FB6ULL, 
            0x6151A05F8F4A66F2ULL, 0x11445B91C815F4DDULL, 0x38BFCAEFB47356CCULL, 0x2291EDA1AACCB00DULL, 
            0x90FCC428C279BADAULL, 0x8D904D02E00797D1ULL, 0x66210C566D6495E3ULL, 0x06F55C1E5E50A51AULL, 
            0xD98F2A9D13DAEA51ULL, 0xF309AA7D5CFB41E4ULL, 0xC570EE1E57512E99ULL, 0xA63D43EA019C529CULL, 
            0xE48D2112928248E4ULL, 0x081AE8A0CBFC178EULL, 0x44B869BEC7B93BBFULL, 0x850ECF0D72C2D732ULL, 
            0x96F97BFACA85EBA3ULL, 0xB6CA3D8E75110116ULL, 0x9A41A6E697BE575AULL, 0x5C4B5EDC15C23338ULL, 
            0x9AF5A38E7D4BAC16ULL, 0x73F4A1F726769448ULL, 0x1D466FAED2036D75ULL, 0xBCA395E6D5898EDBULL
        },
        {
            0x6FCE7DB02DC21692ULL, 0xFE91DC89AF0FD310ULL, 0x2BE4B89AA703B855ULL, 0x20EC2AA11EF58322ULL, 
            0x0D70B042F2998BD4ULL, 0x11CD55437B13A91FULL, 0x7D7B9BD04DAC22DAULL, 0x37993FDB648FD195ULL, 
            0x8D73B42D3C743490ULL, 0x65DF4ACE94CD60D9ULL, 0x9F3E268DA429E88CULL, 0x48053275AEF7BCC2ULL, 
            0xA32E8CC92973E4A1ULL, 0x0C3E5FCCB2230A0AULL, 0xB91712A9AB5BE99FULL, 0xC91A333AFBED88A5ULL, 
            0x29AE16A22705CE08ULL, 0x1FF02B41D83D9AF8ULL, 0xF96278714DECF869ULL, 0x21AF26768344D0EBULL, 
            0xE9C49AC5A703136DULL, 0x70AA4BCB0EB93BE3ULL, 0x2F10F4EAA0ECFF0AULL, 0x5FA54753862D6976ULL, 
            0x98C964668CE32C4DULL, 0xE1976C1A82C30720ULL, 0x2B1958D9DF32325BULL, 0x466C9A90C0EC03B0ULL, 
            0x31B6D1AA4ABF6221ULL, 0x38BA0BAF40C49FE9ULL, 0x588477F41B0B75E0ULL, 0xA1A292E907530478ULL
        },
        {
            0xBF29240D77DFD413ULL, 0x57DBD4DF78E1CDD6ULL, 0x1F2EB8FE241368C7ULL, 0x1D5A39262E0C9579ULL, 
            0xDE4DC6DEED81501EULL, 0xCBBDDB7C3FC2648BULL, 0x18C39E218E102658ULL, 0xB9BC725790395D35ULL, 
            0x46FEA433FFDCBBD6ULL, 0x9C3049601E6E132AULL, 0x88FE8D7CEA1FE76CULL, 0xF8A655FA29E92E9FULL, 
            0xC22651C674BEEEFFULL, 0xCB5EA458B2FDFDC2ULL, 0x9C638FB83E7CC8C0ULL, 0xA6C6AE5D824A2506ULL, 
            0xC869ED0BDEE80A4DULL, 0x911246C24B282534ULL, 0x9E51F8657AA18D59ULL, 0x8E9482DE94BAE988ULL, 
            0x42FCA0246682FEA7ULL, 0x4DE43558870AD9E5ULL, 0x36FF745B7B9E6077ULL, 0x7C609DDA39743F2AULL, 
            0xDDD0AAF503EC2281ULL, 0x5FDA15827C7155B0ULL, 0x069286A980AF8AC1ULL, 0x0B01265809093029ULL, 
            0x9EF40AF8B5264B42ULL, 0xF422D1BFC34767ECULL, 0xDAF1803B950D184CULL, 0x06F011BD3F92BAF5ULL
        },
        {
            0x630DBC59A0EE446BULL, 0x7499AC09ECF0344FULL, 0x019EBE430405EE2CULL, 0x4A678A1B572756FDULL, 
            0xA39ED549198EDA5DULL, 0xFD4B7C725473F06FULL, 0xA4F22A49AC6FECEFULL, 0xC6E64110A79AC435ULL, 
            0x8831D0F1668AE58EULL, 0x356B32D1A280EE97ULL, 0x2724CA55DF585F3FULL, 0x3961716EA1167F23ULL, 
            0xF6AB57B9DE5C1685ULL, 0x00ED39EB8E814F61ULL, 0x847BDFC527126AB4ULL, 0x3B12620D02ECDB79ULL, 
            0x9560B4631D41FAD5ULL, 0x14A140A2855F852CULL, 0x3B193A58538A0ED5ULL, 0x3A62E633F3AE2357ULL, 
            0x40B658736C8F4359ULL, 0x4E2D0B843A14E9E6ULL, 0x6D357E14866ED3C6ULL, 0xC4D511EF996B3260ULL, 
            0xE0655FD7C52B4DDEULL, 0x5DE492FC00DFFF01ULL, 0xDF9259206E225A92ULL, 0x452F016EBBA1BF20ULL, 
            0x14DD7FC576654EA1ULL, 0x8EA42CCC7BCDE82DULL, 0xB47A8BCB52893AEEULL, 0x734690AA8A7DBF1AULL
        },
        {
            0xAA614743E009BC7BULL, 0x40A661201434FCCFULL, 0x3DF01434A5D64A92ULL, 0xD87DE97368AEA6B0ULL, 
            0x50B6035633D49AB8ULL, 0x5965DC8C2915F790ULL, 0xBE038A4712227047ULL, 0x1B83B5BD6CC74C03ULL, 
            0x84718F473AE012E2ULL, 0x252B3A665C989582ULL, 0xD653889876D35BF8ULL, 0x4D6B58626C7654EDULL, 
            0xB158A454CE7FF2FFULL, 0x08AC89CFD08E7EDBULL, 0x90B44D71CE3EB6A1ULL, 0x82A5F54369B82471ULL, 
            0x7F9B23DDCA199DA3ULL, 0x4FD409C8D236E331ULL, 0xC95716F4193995C0ULL, 0xA31064E07103B5FFULL, 
            0x4B99B20925C377AEULL, 0xEEADFBC35EC702F4ULL, 0x2D4EFECE85EA0174ULL, 0x67D09912878A79D4ULL, 
            0x3CB753DCFB81D44DULL, 0x187390467B2D108DULL, 0xA8A12AFD1C4E594BULL, 0x400FFA19E361FA63ULL, 
            0x005B54175D106517ULL, 0x15F1DF10A16DADA5ULL, 0x6F5BF7758288F3B3ULL, 0x5B58AED2703222D0ULL
        },
        {
            0xE89ECD3249CB0AFEULL, 0x8E2078D558A7331FULL, 0xEBFAB9BE4270D692ULL, 0xA74612247A7F2039ULL, 
            0xCDC8B15EFACF8964ULL, 0x362B453CCED77587ULL, 0xB55E8209F350A1D8ULL, 0xE2760C00734BAC42ULL, 
            0x09CA626E927F3607ULL, 0x16F256935866C3A0ULL, 0x70AD32305B63E662ULL, 0x798904ECDCEA2A2CULL, 
            0x8A0737E921ABBB2EULL, 0xF9D704B2B82984DDULL, 0x275B82D4A856D898ULL, 0x3E229992905FA95DULL, 
            0x2A9471DCFFD65D7DULL, 0x517C160025FC325FULL, 0x60ADE49CD610F90FULL, 0x47B75AA9D263E8A4ULL, 
            0xCC00C5A3A88BB0E3ULL, 0x249B1C4760A4A77BULL, 0x6FCE0EA41B9CF7DCULL, 0xAD67484FFFAE9CF1ULL, 
            0x650134A7D52F258DULL, 0x1B9C6510C70865B9ULL, 0xD7754307FD8010C9ULL, 0x03FBDED9F22B126AULL, 
            0xFD01E1BCE0DCB678ULL, 0x7D63B3A11702FC47ULL, 0xCC069807B7DF47AFULL, 0xC4D54877F91BB129ULL
        }
    },
    {
        {
            0x7EF3AFCA375ED75BULL, 0x3E657CDAE60455B1ULL, 0xCA16A7D7EC1389D2ULL, 0x8F00E783B778D0DDULL, 
            0x6662A5515496BDD5ULL, 0x6B3DAC2EC19B7779ULL, 0x75AF23994F48CDB1ULL, 0xC0C7348AB4DD8B3BULL, 
            0x4472CB56601CAE29ULL, 0xF5C22B18256998EFULL, 0x49687EBD2AB2096EULL, 0x26F54D942A8A7353ULL, 
            0xB296CC26DB14F5DBULL, 0x1620CEEA20AF4706ULL, 0xECD2332BEF65DED6ULL, 0x9F440EA5D38374F3ULL, 
            0x35297F02EF8E5D1AULL, 0x225CB0535A2CA5C3ULL, 0x1FA33BB10F86E4ADULL, 0xF2CE7AA7344331ABULL, 
            0x308C1AF18466DFF2ULL, 0xD588EDF60E8896AEULL, 0x4F26BF58AB05A3DBULL, 0x1A143D86F603EF4BULL, 
            0x63A5C502A6AAC569ULL, 0xE8265CA725871392ULL, 0x334B0106D2D7956FULL, 0x6A21CABB1C7E754DULL, 
            0xB7442B39692FF789ULL, 0x991464227B6CBE52ULL, 0xFC819E536E3102D2ULL, 0xEF2F67440DDCB567ULL
        },
        {
            0x08CAA5EBA11CC05BULL, 0x2FFCD9BC41D15445ULL, 0x9BA41534F4DA12A7ULL, 0xBB415D7D28F85C86ULL, 
            0x486BEA9FCA61BE96ULL, 0xD9EFBA6795245EEDULL, 0x94A695D726B32AF3ULL, 0xED3F96CB31CCE536ULL, 
            0x1455DF9477436532ULL, 0x438E7BC0DBB9889BULL, 0x3937FB3CF5FA6653ULL, 0x7F5F0E47D631B5AFULL, 
            0x460EA66888B80F7DULL, 0x3A46640D4B74BA45ULL, 0xAAB9A7B6C8BBD596ULL, 0xE6CC245392E09422ULL, 
            0x9CC7E004175790F2ULL, 0x28E7C63207461D78ULL, 0x9682C234C750185EULL, 0x552E8C8F7A93C1D0ULL, 
            0x5F7EC5F3C416392DULL, 0x21E3A08E2DA24F0AULL, 0x143C3F62669DAEEAULL, 0x347F4E64DB4F867EULL, 
            0x84A24C129EC67600ULL, 0x058A6E5F51E88923ULL, 0xCF3D52118EAFC7B7ULL, 0xBC50728B4C517162ULL, 
            0xC8C030C08A61BC6FULL, 0x412CA8C5B40CB8BDULL, 0xA871A23FE10B4F64ULL, 0x613A59B113C0DBC6ULL
        },
        {
            0x7327BA1A0E3E7CCFULL, 0x5B52C0F3BAE78313ULL, 0x40A6443B8578BD6DULL, 0xE7C33023308C6EE1ULL, 
            0x53C428EB7ABFD974ULL, 0xD6DDD5FE01A33FFEULL, 0x2B70D65C42F8D1BCULL, 0x9D6DBCF4F45C8F35ULL, 
            0x332A722DD44F5953ULL, 0x039B90D89B7B2750ULL, 0xAA5F5F9FC0F4323FULL, 0x0CE8E449CB8FB93FULL, 
            0x22AD7AA1027A369AULL, 0xB31128683BEB0A2EULL, 0xA56F4C05E57BDBC1ULL, 0xBF63869AA1B06719ULL, 
            0x1E5F712909ABC800ULL, 0x7B8AE4F59C969541ULL, 0x8C62D707C036CE17ULL, 0x9A7DF0E9ABDDCF74ULL, 
            0xFAB7590E3CEFC03FULL, 0x7B11BA8E0685CB5BULL, 0x802B2E55CD57E476ULL, 0x4C865F510E7B9776ULL, 
            0x022B9D15A5335CF7ULL, 0x51BB9EEB5BB11277ULL, 0x8495FD07690D07A9ULL, 0xA861E1124C80C147ULL, 
            0x72E0C162AB1F7CE1ULL, 0xAC9040B79DB3295BULL, 0x97ECDC83F260A5A7ULL, 0x539DF4982D67F32FULL
        },
        {
            0xE12CFD00FB2EB7A0ULL, 0xC26EB64B904004CEULL, 0xC7B607A76CF66584ULL, 0xFD7CF487C951E310ULL, 
            0xE899ABF4992E9A64ULL, 0x947F3C8868E66BEDULL, 0xB032E52C3F1009E3ULL, 0x051AEDBE4D77819CULL, 
            0xF99A1EA4F3D7D26AULL, 0xA3CAAA0BAF6D0FD9ULL, 0xB2B977480AF571C3ULL, 0xEA95CB5DB33B0390ULL, 
            0x16A2A13126681E28ULL, 0x1825B79E1211AEA6ULL, 0x388395478E227A29ULL, 0xB51397BCFA466681ULL, 
            0xB6C6CEED1099F969ULL, 0x297C18A9E647A759ULL, 0x4E39E98BFFD8C427ULL, 0xA60871023927D64FULL, 
            0xDA4E905C15E66B8FULL, 0xD4A0229D70EED79BULL, 0x2655CDE8DA78113DULL, 0x55442C39B7D0450BULL, 
            0x33FD3EBBF775A150ULL, 0x88C4D2D32BE9F3FDULL, 0x8E1BDF343F6A9ACFULL, 0x988AED350759A836ULL, 
            0x1AF2C5441989B1C4ULL, 0x0A25DD6C8045386AULL, 0x6F471CC3EBB0CB1DULL, 0x8559DFE6CE046097ULL
        },
        {
            0xBCC9B5C30702D98FULL, 0x086D8D2AC867F31FULL, 0xDC32855198C17015ULL, 0x67FD284C1F642C65ULL, 
            0x798855D09B484325ULL, 0xA88C80DBC412C9CAULL, 0x83778DCF79A61DDFULL, 0x03B3453723669486ULL, 
            0x09BCD3BEAAE44BDBULL, 0x7B28D860095224E3ULL, 0xB3562F8F60F51F03ULL, 0xA382F4DDC535E19FULL, 
            0x6E1D5E0689A2406EULL, 0x76F3849C636C31FBULL, 0xB99881ED2E9AC129ULL, 0x015E084F7BEB421FULL, 
            0x1172A918A2D639E1ULL, 0xCC6A861291A9333AULL, 0xFBEE6233D2B7C593ULL, 0x06AAD583288FBE66ULL, 
            0x40DD4DFCC1599EF1ULL, 0xE6AA95FA3A7EA535ULL, 0x6CEE77E943D325EBULL, 0x66F3DB7CA481B120ULL, 
            0xCC80F8BFEAE195D3ULL, 0x37DE6979385887A6ULL, 0x7644A89750FCD455ULL, 0xDE6C3CDF3F682011ULL, 
            0x9AB4682F5DA6AD93ULL, 0x5B87023190AB2ECEULL, 0x42DD37A6B8FB3686ULL, 0xF9F17683A4CEC65AULL
        },
        {
            0x91780714E5C004AFULL, 0x9C78376B2D47E261ULL, 0x6489695BCCFCD976ULL, 0x5A98BFC7B7555A26ULL, 
            0x4580265ADE54FB0AULL, 0x9D5A8D50D4009B51ULL, 0x498907BC2927F495ULL, 0x77D8EE5423B7BA33ULL, 
            0xCB713762ABA63740ULL, 0x2E04D3C6C5E3C3F0ULL, 0x785ACAAE6D8997E9ULL, 0xF281959EC0765AD4ULL, 
            0x47C153FFAF7C0410ULL, 0x3BEE38707A65D245ULL, 0x1B3EE296D1F41D45ULL, 0x386429E5B3B1CE10ULL, 
            0x97C4A970A85272B3ULL, 0x3E2BE5FC19C68890ULL, 0x19B2F919578BD28EULL, 0x41938EE79E7D1650ULL, 
            0x72F3F8B844B258BCULL, 0xBC7F2B532B200F26ULL, 0xF51C76116BB57554ULL, 0x0AE4A39BC76C50E9ULL, 
            0x6DAF494C76B1CD17ULL, 0xE8837FE915085E18ULL, 0x0374AAF9B46ED629ULL, 0x8A965A9BBC945EBEULL, 
            0x91C2A6A2D9E4717EULL, 0xA50E00333432E7F5ULL, 0xC20B589A81241414ULL, 0x49C4D0352D5B6E25ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseCConstants = {
    0x905780CE6561225DULL,
    0x56737713136FA13AULL,
    0x5F277861C0025D0AULL,
    0x905780CE6561225DULL,
    0x56737713136FA13AULL,
    0x5F277861C0025D0AULL,
    0x22DD63861EB75A28ULL,
    0x730DC477595C8366ULL,
    0x3A,
    0xF0,
    0x69,
    0xE5,
    0x3B,
    0xB0,
    0xCF,
    0x12
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseDSalts = {
    {
        {
            0x3154FDDD8FE70BD3ULL, 0xBF2CC59A93576BA4ULL, 0x8DFCE06FA788FF4EULL, 0xBA98BA09640B433DULL, 
            0x0AE7FD0C9E38134CULL, 0xD304E846B1C2EE7FULL, 0x4FA7D28693D3A22DULL, 0xC1296946D41A7848ULL, 
            0xC55B8204019FAA2CULL, 0x53FA23AE945A7F1EULL, 0xCD1501AC6BAC25FBULL, 0x4034384F374A9D87ULL, 
            0x4523BCD5F995A1C3ULL, 0x5138E7981A3E129BULL, 0x91CAA3746ACC922EULL, 0x56CFF29417D54C32ULL, 
            0x5074ABFB9AF3545CULL, 0x1628FF7F4F8011CCULL, 0x79A2C28CA9AD87BFULL, 0x67D304E795A9B74CULL, 
            0x2309EA740EDEB58CULL, 0x0FB0DC1F55FE59C3ULL, 0xA76DA21C4CA628A4ULL, 0x040596A2068ADD81ULL, 
            0x0A9DE416F845BA0CULL, 0x75D5AD806BE2DE7BULL, 0x6BCA60E8EDE35972ULL, 0x801736812EF93DABULL, 
            0x14898FA603D38EFEULL, 0x0F83C075DC67E32DULL, 0x57D1A5C8242730E9ULL, 0x2E5F552784900C8CULL
        },
        {
            0xB566D83A1482A1ABULL, 0x4D4D2EF19164FD6FULL, 0xEEF07103421536A1ULL, 0x6FC3D863F331C3A1ULL, 
            0xA9755480782F69DDULL, 0xB96B80AF9D377677ULL, 0xDE477ADA9046C3B5ULL, 0x2FDF22CD3EF4634CULL, 
            0x46305AD0F86DCBADULL, 0x112FBD2A2D97A2A5ULL, 0x3F28772C9D724F94ULL, 0xF16B7DBC2F4A0194ULL, 
            0x303E88284F394902ULL, 0x31AFCF51A08D46ECULL, 0xEF82295C2E60F71FULL, 0x1FD53AE39014EAD3ULL, 
            0xD059F0F0781AC997ULL, 0xBD58B7A3540BFA18ULL, 0x7F4B7BABABCCF55BULL, 0x97917907EE5958F1ULL, 
            0xF40FAB3703D58B70ULL, 0xAF8FA4415681F603ULL, 0xE8057550D697018DULL, 0xF2A45A5A3804AB9FULL, 
            0xE99A74D298BF0F21ULL, 0x0277ADE3177F7B7FULL, 0xD3A5EFCF76B26399ULL, 0xA3473BCF90BEA04AULL, 
            0xE91B0511406508BDULL, 0xD9FBC12F0385BBBDULL, 0x40631AD4F80228EBULL, 0xD8EA5FC042C56505ULL
        },
        {
            0x78643EB9C6748451ULL, 0xE9FDAF7F80B2012FULL, 0x9551EB2F913AD4B4ULL, 0x3D8956DDF2561B9AULL, 
            0xF5B9DF0A868F08F8ULL, 0xF3A0EAE73FBE6DE3ULL, 0x8590A446520F53C9ULL, 0xEBEA8919A6D0934AULL, 
            0xB89BCD54CB582592ULL, 0x2A83082415858C79ULL, 0xF0EE43ABEC9CF8A3ULL, 0x270D0A55A10EA79BULL, 
            0xD91F01794A4CE495ULL, 0x53BFFAEF36F0DB7CULL, 0x648708C3E04BE964ULL, 0xEF0EFFC2427BA63AULL, 
            0xBA5F9059B3F6E389ULL, 0x22E157194320ED2FULL, 0x2A5BBD73DD4D7B0CULL, 0x08C2968E081E0C16ULL, 
            0x606B1F3B4AB2FAEAULL, 0xFBCB517487B2C24AULL, 0xBD49F7ADD64EC24FULL, 0x3BCA77D828294F15ULL, 
            0x92974914C2ADCC59ULL, 0x9CA908E7D6838D24ULL, 0x1952C3E03831806EULL, 0xB4FD68A2013EB748ULL, 
            0x4F2AA7251EBC0F63ULL, 0x7C17C4DDC565297CULL, 0xAB5F102C8501264BULL, 0x5CB088605845B9E1ULL
        },
        {
            0x8746AA84CAE814C1ULL, 0xAC6BE743965C551DULL, 0x8C3C6481B2FFA9C6ULL, 0x2CB5FEE2FFFCE761ULL, 
            0x294974B4A2D633D4ULL, 0x5734F9D82FD5619BULL, 0x519FA93073367AADULL, 0x36CBF235A44E53DFULL, 
            0x6080CDF030D508BFULL, 0xAF237847E659199FULL, 0x86717DE0623D9BC9ULL, 0x0FFE3BB11C6549EEULL, 
            0x6539894ED3F3439AULL, 0x2089388C44787F5DULL, 0x5E6558B7E8D07D65ULL, 0xA1DEC43479C6BC88ULL, 
            0x39E1E5BA7DCD2ED2ULL, 0x8AA456201E3C5DD2ULL, 0x1D6CB4C207ED526CULL, 0x0357FEA24062D729ULL, 
            0xC7E02220B9761A81ULL, 0xF9D8CF7DD533ABEBULL, 0x8B9B8571F8F29254ULL, 0x06A2BEE52519BF3FULL, 
            0x4E1DFDA504EF15DFULL, 0x5C40FF463DF772CFULL, 0x1F060AC5EE0CF966ULL, 0xC68EBA49895C9FC4ULL, 
            0x023407E9F125BBEBULL, 0x45EFB4099E353994ULL, 0xD0B728704FBA9083ULL, 0xAC1AF298CCBDA1C1ULL
        },
        {
            0x2B1DE11E99434DDBULL, 0xF81E013F531B8843ULL, 0x6036D5008D49A509ULL, 0x3E4D3883658D85F7ULL, 
            0x8F982DCEF7C48B48ULL, 0x56DB5444D2378378ULL, 0xD3EAFF55E841B6DCULL, 0xBA57AFB32B0BBC05ULL, 
            0x018AB06B2C1E7049ULL, 0xC06ABC2FE02C9991ULL, 0xF26449B4E343AE75ULL, 0x89276D8CA85EA265ULL, 
            0xAF070C48B7A4AA0AULL, 0xE2FB6A82D99FB89AULL, 0x9BFC458839051E1CULL, 0x3E80D9B55C5C67D6ULL, 
            0xEC86E181582D6B85ULL, 0x10EB2A50931A6BE7ULL, 0xB814D55D5B232483ULL, 0xA1E12F75FDC0FA1EULL, 
            0x4B53F7CF77B9AB8BULL, 0x6019C0BA5B71F989ULL, 0xA01658897C6D3ECFULL, 0xACCF8E654CBD7054ULL, 
            0xB23133404FF8831DULL, 0xABD13A32C5E20635ULL, 0x23BCDE82E0B5AABCULL, 0xFD3658E528D1C9CCULL, 
            0xBC92656F36355D4BULL, 0xFF3C2699C8F5BBEBULL, 0x1C0BBD6347E028B7ULL, 0x7A8AABDCD1F17B7AULL
        },
        {
            0xC43CAAD4742DF787ULL, 0xE5E2A970CC19655BULL, 0x9FD9E8AB40989CC3ULL, 0xCB723334B25AE80EULL, 
            0xE5E76DC839118F54ULL, 0x5369D0E9B3F55BF1ULL, 0xCA7468ECE80B658AULL, 0xF2C7312193456CADULL, 
            0x9B0D68752E2E9651ULL, 0x7F9D04C5D33A8CD6ULL, 0x7E3B168E5B3F56AAULL, 0x1A4BBDCBD7F3DEB1ULL, 
            0xDA52261B222C3190ULL, 0x78E9D108D2104283ULL, 0xE5DFF076D6DFB66BULL, 0xC151394D30781F5FULL, 
            0x1A5BBD0B39E12809ULL, 0x1FD175A2BA2163ABULL, 0x6467D4F5448BA04FULL, 0xE0A8EC564FE2F4DFULL, 
            0x793CDB7DB5061785ULL, 0xE2A672D41F896CE2ULL, 0x0B7972298B5E67FEULL, 0xB3FA17FB066DBFA8ULL, 
            0x5EBAC8A946629863ULL, 0x218D21DB907617C1ULL, 0xFBAC906556E7E58CULL, 0xFBE23300FDE3613EULL, 
            0xD2CC105689952FB0ULL, 0x1CC7CC0463C4E3FFULL, 0x9CC9D7FF8171640DULL, 0x621D69DA15CA4D34ULL
        }
    },
    {
        {
            0x5EC3E1D7C5E520D9ULL, 0x49FE9B65D5A62494ULL, 0x7E1B739FD6365CD9ULL, 0x627BB9D6EAB6A364ULL, 
            0x865BDAA40FA3A5FBULL, 0x0CD63ABFFAFA3458ULL, 0x67EE17084FD2A295ULL, 0x6F177727B42CA8F6ULL, 
            0x734084B8F3804810ULL, 0x30D33E9288339E89ULL, 0xB343EAE15687033BULL, 0x7AC92C064F4E39FBULL, 
            0x0AF6E2E74269D21BULL, 0x13486C06E927741AULL, 0x9EA62E913FCF8289ULL, 0x621410ECE3D7B2F0ULL, 
            0xB2572B6A881E2BA7ULL, 0x0091E47BF97558A5ULL, 0x625E89A2E305A77FULL, 0x07F7894386008829ULL, 
            0x5AA87E3F623AE41BULL, 0xB665209B21ACF934ULL, 0xB4C21D82317B7228ULL, 0xD3D624CBB3BA0816ULL, 
            0x2795C3158FB27C46ULL, 0xDCD7841B776760CBULL, 0x7BC1AB899EE877FDULL, 0x239428BBD7E3B900ULL, 
            0xFBCFD1AD5DEFF533ULL, 0xA6DA6164C31718E3ULL, 0x44D626A32CC988C5ULL, 0xB56DD4390E14FDE6ULL
        },
        {
            0x19A18C672F95EF43ULL, 0xCD8D2B46A8C40DFFULL, 0xB86C7BB75834C93DULL, 0x70565117FD8A5856ULL, 
            0x93F3C868F71805A5ULL, 0x8CAD731D70BF7FCFULL, 0xD536C9305748B167ULL, 0x2233C051C8D9CD20ULL, 
            0x07F6A0610BB28576ULL, 0x2AA86E5A3EB9C338ULL, 0xCEAF6202415E19C2ULL, 0xBB48548AE2DD2CD5ULL, 
            0xF77D1C5F6E4153C3ULL, 0x616E818B12526EDBULL, 0x30DCB291BE0E36C3ULL, 0x7BA46A6AABE87508ULL, 
            0x5C007A8FC99CFFD5ULL, 0x9E454490EE3C4D1EULL, 0xC1B27207D6F60E7FULL, 0x65D6D871122B4474ULL, 
            0x055DB2A8C916913FULL, 0xAE4E77895AF4C80BULL, 0xB62160F198098C1DULL, 0x76E8991E69B2F7BDULL, 
            0x4F19BE96F15FB69FULL, 0xA6997FA12A69844CULL, 0x2E10464E8E80DF29ULL, 0x4F45C7B7F3E083D5ULL, 
            0xD9AEC4B063A643CCULL, 0xAC7B6BD4EA300392ULL, 0x929D5E9651DC7967ULL, 0x554A0D32B1FE398BULL
        },
        {
            0xA550FF25D0932A04ULL, 0xD81626E4805AF4C2ULL, 0x3079BCE814C7AE1BULL, 0x4D076F04D6C91EE2ULL, 
            0x68EB7FA9CAE411FEULL, 0xE85FEFC060B8BF6FULL, 0x447473FF23E80E8FULL, 0x6D1ECF9F5C03FC1AULL, 
            0xF2431C4040516692ULL, 0xE83A0B9F4D0CD132ULL, 0x00972B1E2156E018ULL, 0x2E46F0D706D7F8E2ULL, 
            0xD508082D17F81A44ULL, 0x34DB921D7B126F45ULL, 0xCFB68328C5611BB9ULL, 0x6464E71C9E63EA18ULL, 
            0x134110A332E93E95ULL, 0xDCD4AF43A44BFB4BULL, 0xD0307D54CDBEE45AULL, 0xF0A6580540442828ULL, 
            0x1225BBC6529D51DCULL, 0xCB7DA9DE87190C49ULL, 0xB897604897BE337AULL, 0x2827E2B6230CE74AULL, 
            0x6ED0E5BCD78FDD77ULL, 0x3962823F54CF6C10ULL, 0x60E189664A2C4549ULL, 0x5ED84F069995A72DULL, 
            0x7428906D909616FBULL, 0xB39AADCDB5E222B3ULL, 0x28E3A8404163B5FEULL, 0x6F4CEE92E2A2CECDULL
        },
        {
            0xA4F5C4D89929857EULL, 0x6E4B78363466CCF3ULL, 0xCC6819DCDDA941E5ULL, 0x24B28840506FEEB3ULL, 
            0x56E037D6D410094AULL, 0x10D89B00EE1254ACULL, 0x149E90EEE2C62231ULL, 0xFECDCC9FCE9008C9ULL, 
            0xC13E06DF840CA500ULL, 0x62F066850A8C4733ULL, 0x80CBF954D1ED666FULL, 0x1257E353CF3E6141ULL, 
            0xF8FDC4526E85366DULL, 0x0FD74120BED2425EULL, 0x82AD9E0C937A86A4ULL, 0xDF6E94226E7F0371ULL, 
            0x0204D9891AAB6859ULL, 0x7A964A53265B45BCULL, 0x58D24BE2FE668C47ULL, 0x298A6DD14717061BULL, 
            0x0E3AEF1C313E96B2ULL, 0xC6BA5704947ACFDBULL, 0x6EF8A3E547FEB5F0ULL, 0x0B3BDE67862909C8ULL, 
            0x001C14CF13FB2849ULL, 0xBF59A3D841605E6AULL, 0x80E2569CE02E7410ULL, 0x78E3EB5B57C22AA1ULL, 
            0xFFF1ADCE9D676DBBULL, 0x48FE0DC45A3E148FULL, 0xB4BD39A70C36E886ULL, 0x786EC7F280D7B703ULL
        },
        {
            0x2B93B4EDAD758BFCULL, 0x5B77E5070E392969ULL, 0x88F957AC7D08CBF0ULL, 0xFF439925FFEFE7B0ULL, 
            0xC92E97C41C4B17FFULL, 0xB3228B49782A3A21ULL, 0x8ABC42B403CE95F8ULL, 0x15514D6D3D113B0EULL, 
            0xC0A003B15DA6F86EULL, 0x67BE641983B69D2DULL, 0xDCE964D5309A4AE8ULL, 0xE6B3A3EFF38464DFULL, 
            0xA96A4AAB93DE90D1ULL, 0x3A55D3B7F2DF1C52ULL, 0xA863624912CBE1CDULL, 0x6E61EC801EDDDE2FULL, 
            0x561E1BC508389C51ULL, 0xAF895EC9EBB57E96ULL, 0x7E813995CB98A86DULL, 0x718EE9001B627097ULL, 
            0xCE510A3C2CFF5819ULL, 0xF60BE51404E01BE3ULL, 0xA9E2F33321FC199BULL, 0x87DAA87C6AB4D76AULL, 
            0x6FB472DDD51696B1ULL, 0x01BC1B79EBFCB115ULL, 0xA20F3C5A81B0CED8ULL, 0xC50FBB5EBF17ABC9ULL, 
            0x7D5C5A462BA3B236ULL, 0x1F1B25E651A25F32ULL, 0xE822977933AE9D12ULL, 0xD6691A11C51C3886ULL
        },
        {
            0x7A6AAA41AC2775D4ULL, 0x8127C56857EA6B36ULL, 0x4C762406DCCB15DAULL, 0xDBAC5D4C86146C87ULL, 
            0x29E4498CBDEACD86ULL, 0x7E12498218AD42BBULL, 0xE60C6D51A4A6B2C7ULL, 0x8313E19C828EB63DULL, 
            0x961001CE39D86D9AULL, 0x2A66B5B43C966E78ULL, 0xFB5960E4E90E24DCULL, 0xBD1EE731DD11E1C6ULL, 
            0x50DBE1CEA6C4D858ULL, 0xA14A9BEB7E8B46EFULL, 0x3664EE568C73FAF1ULL, 0x987E065816456491ULL, 
            0xDD99F99F21668C3DULL, 0x8EFC5C147ADE00EDULL, 0xAB578B3CB87E697EULL, 0x90E55EC7833BE40CULL, 
            0xCBA8535B32620119ULL, 0x7ABFAF740F75EF15ULL, 0x98A165866134B495ULL, 0x0062F86FE54D0691ULL, 
            0x2010D8DB9308F9B7ULL, 0x8E4F087BE0B41D95ULL, 0x1086D17D3E484E0FULL, 0x7DDE06E7F5709CC7ULL, 
            0x1289B85A0B85ECE2ULL, 0x38886848CB24E16DULL, 0x19C0796E1A05C7C3ULL, 0x42A17994BE7FC1C7ULL
        }
    },
    {
        {
            0x710F942A6B2D4311ULL, 0x0AA3011D3631A854ULL, 0x03E1C9385D361BB4ULL, 0x2B2D4D2237DC9CC6ULL, 
            0xA2B90FC91AB54E0AULL, 0x867310BE264ECEE5ULL, 0x9E3532C57A9867DBULL, 0xECD482B5B19B3EC1ULL, 
            0xA9D85DFDD9F94859ULL, 0x3CB1765AF36215F7ULL, 0xF4164D65A5496EDDULL, 0x9129BC61A9358EA7ULL, 
            0x3F3F7943F21DDE5CULL, 0xFBF6F8ECB4E72578ULL, 0xAD8D5B336C7AE8E0ULL, 0x3BAE924D73B9EA20ULL, 
            0xB468A09B16A6E0E0ULL, 0x9C61CF8E9A2FC2B6ULL, 0x5A0B78B07DA77603ULL, 0xBA556A2AC2A4AF92ULL, 
            0x5A519E3EE2371463ULL, 0x012985695CB45694ULL, 0x88E553B2FAF60A21ULL, 0x69C29F690CFBB5E1ULL, 
            0x20B45C2E99A75E2FULL, 0xA85408F2A8BC99C8ULL, 0xA74200B68C657C80ULL, 0x212166D633727393ULL, 
            0xC71C23ECD7355D8DULL, 0xD6839D9CD7D56F8EULL, 0x74E6338E716C204CULL, 0x8E5E8E42B0D14B08ULL
        },
        {
            0xDE59D9A6FDE966CAULL, 0xB2E2FA465FDEE074ULL, 0x6B43470BB422C2ADULL, 0x0EE9383C74A793A1ULL, 
            0x3C8324C607719B1AULL, 0xCF43BE308CD8996AULL, 0xC21AED80FC9A8629ULL, 0xD07B9FD2A5829638ULL, 
            0x94CD0AC87A29C9F3ULL, 0x2295CD7D1F505904ULL, 0xF4A69F8EE0092F83ULL, 0x2CEDD9983F7187E8ULL, 
            0xB61373527896FA3EULL, 0x12498E3865D14511ULL, 0xDE44C40816802274ULL, 0xAD07224C5DD3320EULL, 
            0x8CFBF4F86C570CFAULL, 0x8373449026D2C190ULL, 0x4A5FF2DE7770859DULL, 0xFB4ED6DF8EFD7A7FULL, 
            0xF51CEA8419806D86ULL, 0xC1D13F087B0B5825ULL, 0x885CC083A5CE1153ULL, 0xAE3EA84914C44856ULL, 
            0x860463A0FED195B0ULL, 0xA765BAE57D84DE91ULL, 0xD3B596EA59DDBFAFULL, 0xF9DE851D2F2196DAULL, 
            0x24FDBDD5D1FFEE3AULL, 0xFCC99EF2CFE2FD78ULL, 0x21919C364678C270ULL, 0x0B955AFC557BFF9CULL
        },
        {
            0xC0DC80FE29EC5DCAULL, 0x9B6FA01DBC7D3DF6ULL, 0x5430E7EB7590F3DDULL, 0xD82343990D0C015EULL, 
            0x2EE81690CD16C4D9ULL, 0x976F99DC3A5EF09BULL, 0x890C5455565DF7C6ULL, 0xB5FE508190930593ULL, 
            0x678E3FCBB213AADBULL, 0x1ED21C6A5FDDF90AULL, 0x2F18769691816A3EULL, 0x445EFA11CA846884ULL, 
            0x8EF7DE9145D1163EULL, 0x6ECA8C6117B981A0ULL, 0x68203AD7FA661404ULL, 0xE4D8752C6EB014DAULL, 
            0xF840CC515F11C738ULL, 0x2BB4DD2BD6722A6BULL, 0xD4A6BF40252DBB81ULL, 0x5016198FC790AFF4ULL, 
            0x058EC7DA63A5D6AFULL, 0x58FD564582313554ULL, 0x475A85BF7B482EC9ULL, 0x653E961D55AB6191ULL, 
            0x3B7579641C2761D2ULL, 0xA18D783EA265460FULL, 0x445F4862CAA8F403ULL, 0x5A39EF384E0708D5ULL, 
            0xDA35E38EB9BA6411ULL, 0x75F5A2583A04245EULL, 0xF6DDA627ADE30688ULL, 0x7F436F50924FDAC9ULL
        },
        {
            0x6684A021262F9C74ULL, 0xEF3D2BC9BC954E99ULL, 0xB8000C48E6457C3CULL, 0xE66A0DE04B6499EDULL, 
            0x43B2D1D7B0806896ULL, 0x1D3DEB0063AF397BULL, 0xF8B7C7C0CFB73F5FULL, 0x9A21239F9E6A9D5BULL, 
            0x575482072BA0BB96ULL, 0x014FC095645A21FDULL, 0x8CF638B80306C3ABULL, 0x2972E1060C085EC2ULL, 
            0xCFA2EC21F3D37675ULL, 0x46EA85E562A4EE02ULL, 0x8951C0D14F81A3E7ULL, 0x6FEAA3D1FD58436AULL, 
            0x415ACB929F11DC04ULL, 0x670AFC8A2A84419EULL, 0x9511159FA5FCC3EDULL, 0xBC226892EAACB2E9ULL, 
            0xE0509ECE8BF74DB2ULL, 0x0386D8D1B2FC4969ULL, 0x2EBE4B67159E8AEBULL, 0x9A72B7E5F76C026CULL, 
            0x1642EBBD3E9A3427ULL, 0xE10AE6C3502222DBULL, 0x61E9E1F387998A98ULL, 0x97A3348497411A9EULL, 
            0x2D10A303EF89CA65ULL, 0x45ADC4B91A7F9EE2ULL, 0xB5B3A30E492343A4ULL, 0xE6BF2F3EA9CC168FULL
        },
        {
            0xA4937BB09E96061CULL, 0xF3A117EA1BD57A3BULL, 0x068B03B23966F5FBULL, 0xEEC79907B340F36DULL, 
            0xC3412C61DC8D2498ULL, 0x89890B02ECCA5519ULL, 0xCF3FC8C8A5FAC51BULL, 0x0E67E3A93C4794EFULL, 
            0xDB4BA654C91C7565ULL, 0x2894C22BC5ED1C59ULL, 0x7907335DC7A0210BULL, 0xA9FFDF8CEEB5386FULL, 
            0x0238D9D873021D7BULL, 0x1211B1603EBC9FAEULL, 0x554334F53C7D623AULL, 0xF272D4F213B3062CULL, 
            0xB0A8B017612A0F85ULL, 0x05FF336634B559F4ULL, 0xA342D54C1557A3E0ULL, 0xEAEED2FB877B4164ULL, 
            0xCE572FE86699FB93ULL, 0x903A51F0A45E6735ULL, 0x3D10E2468D84644CULL, 0xD7AA8FCCF7B9C218ULL, 
            0x46EF8842DE778FEBULL, 0xEA4D5D4071DE1C9EULL, 0x66E093EA3E11D41FULL, 0x87CB83B0FCC6AAC0ULL, 
            0xBF81E77AE0791850ULL, 0x4862594BB03B8936ULL, 0x7CEC51212359E26DULL, 0x9CC2CAA23106AB0EULL
        },
        {
            0x052F29B6C84CFD65ULL, 0xB39D81980D369843ULL, 0x83C8250B96FA2C96ULL, 0xDC36A76EB76405BCULL, 
            0x68FBE89DC281A62DULL, 0x463F61A79852CEC5ULL, 0xB8712143F9943D53ULL, 0x3CF3A021896F1C7CULL, 
            0x7FF85E8E79505061ULL, 0x44C9AD8A6E745C97ULL, 0x2626165146BB8DB5ULL, 0x3CFDEA82BF290DCBULL, 
            0xF38B937015547DDEULL, 0xE62B4DF84CDD7ACDULL, 0xC53EC6358A425012ULL, 0xB43014E78CD47D15ULL, 
            0x5589718996D074C2ULL, 0x099C59AC2AB1CF25ULL, 0x8EA55D66CAED0323ULL, 0x7EDBC2C0EC727249ULL, 
            0x215B094C114386E5ULL, 0xCA218390ECFC525EULL, 0x8612A5E943DD50DFULL, 0x68D2DE022EF0806BULL, 
            0x619E89022FFD4ED3ULL, 0x2F4C21DB7F5F6ED8ULL, 0xF7C61C217FDF525CULL, 0x8266D83FA52A669EULL, 
            0x44EC6512AD0AF829ULL, 0xD97BC8C5322C7A09ULL, 0x9C02C2CDE0A693F6ULL, 0x3D4292D826B85346ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseDConstants = {
    0x78B579E6A9B001B4ULL,
    0x9C63CB76254EA203ULL,
    0x697A0B26C357D4BAULL,
    0x78B579E6A9B001B4ULL,
    0x9C63CB76254EA203ULL,
    0x697A0B26C357D4BAULL,
    0x94A02695D58F72F5ULL,
    0x9CDCC41BC095CC74ULL,
    0x90,
    0xE1,
    0xA0,
    0x41,
    0x6A,
    0xD3,
    0x1B,
    0xA6
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseESalts = {
    {
        {
            0xC611BB5C43B7D5CEULL, 0x0FEE3D6A6310C790ULL, 0xB5DC9146B4B36439ULL, 0xEECD4B32E0C6969DULL, 
            0x9D441C02D58D63DFULL, 0xD07368DC3CF8ECF2ULL, 0x5821E90DE1CA5A21ULL, 0x0668957393D68873ULL, 
            0x7A9B6F1E18EBD708ULL, 0x03E11AB04E7A77BAULL, 0xDEE20A65A4180898ULL, 0x508DFD18FC0B5657ULL, 
            0x51EEFE61C5AB8243ULL, 0xD1BA8E10BFF3DA93ULL, 0x62DAF5262D937BC1ULL, 0xAF8E2995B7B54F8FULL, 
            0x1799F84BFD3ED26AULL, 0xC46B68527E2B4B2DULL, 0x9F4941B74E6A28D5ULL, 0x716B445FD05BBA12ULL, 
            0xB8EDE6831E729AAEULL, 0xFAFF05095B3E7677ULL, 0x245709C1CF0AEDA6ULL, 0x803BED5B8AC79E11ULL, 
            0x698D96790D0BC276ULL, 0xEED89F57492E64DCULL, 0x78BE7EE95B469DD2ULL, 0xA7F92706369615E2ULL, 
            0x9BFA1E4128B9D292ULL, 0xC58336299F878F42ULL, 0xEB1849DB4C21B315ULL, 0xCBD4B3E48F81A6A6ULL
        },
        {
            0x65B1BB6E820529D6ULL, 0x45137AE98AA2FE3FULL, 0xB6A75241D2C48E7EULL, 0x0E5F9FA0E5BC9862ULL, 
            0x7A45E4C43FBD7498ULL, 0xA686F0DE7B67452BULL, 0x3165E16357162949ULL, 0xFF906622F9DB8842ULL, 
            0xECB20D27970DEEE8ULL, 0xA44C3447EBAC8E6DULL, 0xD4D634FE14CD9BCEULL, 0xC178D3DFA423C840ULL, 
            0xBD338A8F77FD2E0EULL, 0xDB5362DEB54BE8FFULL, 0xFE20605E7BA48329ULL, 0x3CE5662BF5208732ULL, 
            0xEE443584A32937DFULL, 0x1FB14457D1278248ULL, 0x0EACB710C6DE3A41ULL, 0xB00BB512DFBFC842ULL, 
            0x6C5633860BED4E6FULL, 0x7D4FF2EA46FAE852ULL, 0x65B33C18492490F0ULL, 0x1B504BC72DC2AC7AULL, 
            0xB9499260C27184B6ULL, 0xE4D3D3BAE9639AA1ULL, 0x21349AA5B0191A05ULL, 0x882C4B188DDADDFDULL, 
            0xF2275425B1395B31ULL, 0xD95E5992374052C3ULL, 0xA291DDCF5953E6C8ULL, 0xA7F1EB56BFBBF0ECULL
        },
        {
            0x906ACD49BFEA2EC3ULL, 0x0B75F335BCA9D03FULL, 0xF7179C209D78EF74ULL, 0xCEBEE6DCA1C2ED69ULL, 
            0x247B4EF396CE14C7ULL, 0x35FCD92E2143B0E6ULL, 0xBB4BDDE5EBC73966ULL, 0x19B798E733F27499ULL, 
            0xCA7AD687BA35C72CULL, 0x7A4CAE704240BA2FULL, 0x5AD81BC10B887617ULL, 0x6F069DF58902DC55ULL, 
            0x12CA1015738CEAEAULL, 0x4978E0E9796A0FB2ULL, 0xFD6273278587F381ULL, 0x920161C10DDF4EF3ULL, 
            0x6ED8E575F9DF62FAULL, 0x1C50DFDC1FBAC570ULL, 0x03783377967A03B5ULL, 0xD5232E60D0CF0924ULL, 
            0xD4595A33A6157492ULL, 0x9483DAC95C46FCF4ULL, 0x72BF7E7DFA7DF453ULL, 0xC90C41EA7AFDAAABULL, 
            0x4DCB867FB011294FULL, 0x5A8B60AEB9177F78ULL, 0x998488D0084F35F8ULL, 0xAC48F5AD15A9050EULL, 
            0x88C9D2B9B8D9418EULL, 0xEAD61D8656A16F0CULL, 0xC52F8BF07E6EF19BULL, 0x5AD902127C211AB3ULL
        },
        {
            0x895E047436F1E9EEULL, 0xE4494A340064C63DULL, 0x101B03557BE84739ULL, 0xA035A3C6E56E6510ULL, 
            0x28FB35C57EF3090FULL, 0x9FFF4A9F01043837ULL, 0x2C897EACBB9133B4ULL, 0xF92C6A27F6555352ULL, 
            0x7A524D2D3C0B349CULL, 0xFD87136811E1E386ULL, 0xD152C0337701EBDFULL, 0x48425CD424979FEDULL, 
            0x952DE7BC356BB747ULL, 0x2229308813590405ULL, 0x983BB8B02CD9FB84ULL, 0xE80B3F03C6D561BBULL, 
            0xC04A8A9C7C53DE90ULL, 0x556251685E15EE07ULL, 0x128CBA9061157D4CULL, 0x77A598B1A036BE1CULL, 
            0x0FE8C7815A442446ULL, 0xEA42F2561BC7D082ULL, 0x13115D9455DB46FDULL, 0xAD87E7A1D92C9346ULL, 
            0xB273E9C95A33EBD3ULL, 0xD72F2449443EAE45ULL, 0xD165148D276DBFFCULL, 0x97FDA9D483F2CB18ULL, 
            0xE8C78223C4A24891ULL, 0xDD1AE7170775874BULL, 0x6B425AE07825190DULL, 0x9458C80AE3C0BCE2ULL
        },
        {
            0xDACBB8A0B6616965ULL, 0x6FCA70849B5BBC77ULL, 0xEB30A5FD33F6F6EDULL, 0x8BF91A56FC9DB78DULL, 
            0x77A810DBBF60BC7CULL, 0x9E75FECD7DA13AB8ULL, 0x1E2D6236C0856D9CULL, 0x7368C289279D5729ULL, 
            0xB61B24AAC9C23A50ULL, 0x2B4F73A82E9FE4CAULL, 0x6B5B417D3F4D878EULL, 0x6B40F3BA1C9DEE9BULL, 
            0x3F4EA36A9395FF49ULL, 0x40F64019EC3B4591ULL, 0x78ECEBE17BDB2E2FULL, 0x7A4C836F43C76E2BULL, 
            0x7090748FC5E77651ULL, 0x2C5F1BE79359EB6BULL, 0xE1755EDAF93C2656ULL, 0xC623320170539ED4ULL, 
            0xD1F1FCCEB9DF8915ULL, 0x67B1B248FA29C178ULL, 0xFDCF74372A66F27EULL, 0x961A91A5090586B0ULL, 
            0xCBDB6777702AED0BULL, 0x282798479F688E37ULL, 0xB895511440AE6B75ULL, 0x63F58B486D58F689ULL, 
            0xDEF57F2CB0B25C53ULL, 0x14EE11494459C597ULL, 0xAF4290D9594BF972ULL, 0x1C63BE61E5604007ULL
        },
        {
            0xDB4AEE18F989A6C0ULL, 0xAC0D47BCD3366B82ULL, 0xA169354D7B337D57ULL, 0xE414C1DE9C06E7E6ULL, 
            0x083CDB1E2DD09E26ULL, 0x17727F8DD724531DULL, 0x8F35DDFB5E05B6C1ULL, 0xF5AE8BA1021547DBULL, 
            0xBB2CB2EC5EB15C7CULL, 0x228DD9C9A04663D6ULL, 0x63298DDACAB9BC75ULL, 0x38787039F0D8DDD0ULL, 
            0x7D867F5AF3DFFD3CULL, 0x14992840CB95E64FULL, 0x487DC18F96B6A6EFULL, 0x76C983237735BCD2ULL, 
            0x0B7C7E940EE66965ULL, 0x46FFC1D64E39757CULL, 0xB88C685B8CF2672EULL, 0x70AB62D787E363CFULL, 
            0xE5FF9F11DC04D068ULL, 0xE2E3372D2018DA5EULL, 0x2A71679D483EA742ULL, 0x94FD0C79BD674D94ULL, 
            0x2CE74BBFE87AAC32ULL, 0x9145777172D067D9ULL, 0xC838D2632C0BB5EFULL, 0x0FFE6B7A82B3153EULL, 
            0x7342203E70A12F4DULL, 0x965E018E58F44BEDULL, 0x55DD2C640F5D08B2ULL, 0xEE6F7B6E35DDFFA7ULL
        }
    },
    {
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
            0x731C044E932809B4ULL, 0x42D1519D8A3067F0ULL, 0xA335329D6646B8B0ULL, 0x5C57238966FA9A88ULL, 
            0x2AF0CFFF4CA17707ULL, 0x020E2BE8875F9F2EULL, 0xCD11FBC59080C14DULL, 0xA20537CC06E8DDD2ULL, 
            0x4F66CF2563F5507FULL, 0x62CC3B142586F811ULL, 0xF0F456E6063B7801ULL, 0x387AC735F83E562FULL, 
            0x3922AA9E512B2D96ULL, 0x2DA2E4A1019C599AULL, 0xFDD8B4C44BF46EE9ULL, 0x54558C158D17CF62ULL, 
            0x0C25F3C914FE0058ULL, 0xE0E6604F95C81AB7ULL, 0x647B2B78B339CEBDULL, 0x27028E4074589A3DULL, 
            0xD6A3E9506FC061CEULL, 0x1AC394B7A97780FDULL, 0xC02DDDF831BCBAB8ULL, 0x856E6FE5641A427BULL, 
            0x5D75ADF80EB81F19ULL, 0xA41291596A5B54D2ULL, 0xDDE01A2ADAF3C8EDULL, 0xB28D72FE1EC02791ULL, 
            0xB20C6D9A11224689ULL, 0xEDE0C7EA646C4AD7ULL, 0x8D68B1F228B7A9B7ULL, 0xB79B1DACADFFBBB7ULL
        },
        {
            0x0600B18084E4E9BEULL, 0x284FDD0AB1FD1EDBULL, 0x1DA0DEAB72F0C003ULL, 0x851B0E5C45248342ULL, 
            0x1E9AF2D94440CC03ULL, 0x14D396F5DD4C27C9ULL, 0xCC764213BC8418BAULL, 0x990A50F48E97E895ULL, 
            0x56A65810883B1E0EULL, 0x0E6931DBB9C20F6CULL, 0x5CE61AEADB60B8C2ULL, 0xC8B946732D0E2E6DULL, 
            0x7848F8D81E1D8584ULL, 0x4759654FF6C8E569ULL, 0x436545BF4C4B8FA6ULL, 0xBD86C15E1FF34B45ULL, 
            0x49D75CECA29C17EEULL, 0xD088226535DA0C0CULL, 0x0250FE5E11A5A03FULL, 0x0FAA144369156E6BULL, 
            0x64876F20E56C2FD9ULL, 0x3824F8E5E71573C0ULL, 0x4F73E7F9A6A9FB94ULL, 0x07EE2EBA0D95499BULL, 
            0x208B8899B345C508ULL, 0x1AB30DE828F983CBULL, 0x283FA0D8445279D0ULL, 0x739F7F14C39D0E06ULL, 
            0xF20FDFBFEA1608D0ULL, 0x58405CD34D9ABC1BULL, 0x891E29875C108D5BULL, 0x49A51AF2B52E0437ULL
        },
        {
            0x6BADEF3D7E346D81ULL, 0x9540AA847958C04AULL, 0x6AB7B22282064FF1ULL, 0xE417D89C04C3DCA3ULL, 
            0xC4FC07555D9B028DULL, 0x263A7F91C8C685F0ULL, 0x48074EECEA305AAFULL, 0x86837106CE08D9A1ULL, 
            0xE06E824AEE9A33FDULL, 0xD96248CD1B2EB729ULL, 0xF797AB209DDD1EEFULL, 0x7B530A1C2CD70749ULL, 
            0x1B764B68BC646808ULL, 0x6A47F965C5AE6B2AULL, 0x0250106A2830FBE3ULL, 0x792D6F609B420E75ULL, 
            0x439E0D426B49BDE3ULL, 0x647AFEE235082FC5ULL, 0xAC2BD1EE759FD0A9ULL, 0x5962EF82B22ED46EULL, 
            0xD81B9612DD7E5BD3ULL, 0x06A0E33A4BC13DFDULL, 0x7B81F84CE220DC76ULL, 0x8EA3CE89BA5B3CEFULL, 
            0xDC1677A64DAAAE6DULL, 0xF002B65D867CC4ACULL, 0xB52CA3C9DD51D4FAULL, 0x5A0291AF9957FA26ULL, 
            0x935D30339E4CACB0ULL, 0x1E0BF624B67B6F5DULL, 0xC065A9ECD7506DF1ULL, 0x68D2823D5B324700ULL
        },
        {
            0x185A93C0E8C0ADF9ULL, 0x7D64B4DF439D4B72ULL, 0x4FACFA3563733C13ULL, 0x0F59799C6E26C843ULL, 
            0x222231E2368E813CULL, 0xCA377BFD4FC52E94ULL, 0x542422E6C3AE336CULL, 0x29CC2493EDBFD5BBULL, 
            0x86D0C6EE66358ED7ULL, 0x1013BACF35D77C52ULL, 0x6A509A515DD03FC9ULL, 0xDCED0F112A910902ULL, 
            0x2D1C6ADB32B95B5FULL, 0x289F3F624BD7CA95ULL, 0xAB497BCE0B2613C8ULL, 0x437DE3009EBA551AULL, 
            0xC76F04BE1123B1FFULL, 0xB3461285783CD0ACULL, 0xA62CB5C64EA0FDB8ULL, 0x0427D37456806A2DULL, 
            0x30A48C2F76E64349ULL, 0xB4737AD577EA7A16ULL, 0x07C176F3471EAE69ULL, 0x1913E66C77F252FAULL, 
            0x63200F38C4DE2286ULL, 0xE292D7BC211ED5C0ULL, 0xDD97BB899779A69AULL, 0xC393CA0C0F35003AULL, 
            0x8924A71706EB9A6FULL, 0x8B7876017F5D8254ULL, 0x912CCADC9D16C0E0ULL, 0xA6E57137292E924FULL
        },
        {
            0x3BEC56719F1DA244ULL, 0x007598D5650D8C53ULL, 0x0835ED25A303FE57ULL, 0x805518C8DDC9D3B7ULL, 
            0x2A5459BBB1333C79ULL, 0x1C1CC2692CBF46E3ULL, 0xFE6DF8D701959810ULL, 0xD5237EBC699B136FULL, 
            0xE95106DDDFD493D8ULL, 0x3D779F16F6DA311EULL, 0x563AC71683C14CD7ULL, 0x76BAB2B2BD8F5FE5ULL, 
            0x27899D77E6BB4829ULL, 0xE6983225C050AC54ULL, 0xA443C15ED6DCC0F5ULL, 0xE1B8C6F0F70144A6ULL, 
            0x3C10E25A85815868ULL, 0x3E4719F146A387F4ULL, 0x1EE5C66E7F7A86C5ULL, 0xFF9D03FFC5F2587EULL, 
            0x8DB5D1AE5BA5C05FULL, 0xBE736F2DCCC27A90ULL, 0xDDBCA27561B89351ULL, 0xBA7C642331B9C8AFULL, 
            0xD550B70DC6EFABDEULL, 0x9DB9F3977018046DULL, 0xB2F87478BC3276A8ULL, 0x570913E86A5EF6D3ULL, 
            0xBC1F937C5C9BBD66ULL, 0xEF39DB6D74C2F616ULL, 0x3B7DFE74553B9C9CULL, 0xE0CD7A46DEF53612ULL
        }
    },
    {
        {
            0x53FFB9B562BA1094ULL, 0xFDCC5811EC24184FULL, 0x1E1B825FCA618B6DULL, 0x2633595FD238F56DULL, 
            0x17F1CA0E3658FF50ULL, 0xF4096BC7D6E0CB10ULL, 0x994277CE871F6F1DULL, 0x749EE04321F14DD5ULL, 
            0x1E97950E25945001ULL, 0x9801D30D8C882A52ULL, 0x041D413324780BB7ULL, 0x1BC0E3DF93F50667ULL, 
            0x20F69C5C132E0020ULL, 0x1720B87EFEB78051ULL, 0x5D9A93E8D6F4A5BBULL, 0x0932049B0A74A088ULL, 
            0xBA653E8ACC09A76CULL, 0x1FAF3D8C35281217ULL, 0xC406D3E9E7FA1480ULL, 0xCA9F32AD687CA65CULL, 
            0x0586ED19E849C53DULL, 0x3E839025950700D9ULL, 0x1BC6591056304EA2ULL, 0x92EF0B850F2429AFULL, 
            0x7738D86E4E6930A1ULL, 0x4F3E2EB46E13BF0AULL, 0x2131A1C658F377B7ULL, 0x9149583452E64DB4ULL, 
            0x7D275217B7D9D046ULL, 0x40BE7779DE8ABFFCULL, 0xA5D6FA866ED5DECCULL, 0x402DFD127A76FBE3ULL
        },
        {
            0xFDFE77D1FA9786AFULL, 0xC90A7AB11C8C0964ULL, 0x499EFB5F16EF8755ULL, 0x8E0813464A59078BULL, 
            0x73B09FD16D46A63EULL, 0xC1ECFD9CE8CE29D8ULL, 0x491DF5960B3E2A8EULL, 0x2FEBFF0D50A60644ULL, 
            0xFB7BD0AC33157C7EULL, 0xF969BB8010F9EE81ULL, 0xF4AAFF19BBD31514ULL, 0x5F6AAE49EE155A0FULL, 
            0xA9A8219A3C12C1B8ULL, 0x5B5484EC2D4111E2ULL, 0xBBF6310A5D9245B5ULL, 0xE322490999CB738AULL, 
            0xE1AC8F0A619B03F7ULL, 0x4EA3459E333CA377ULL, 0x29FB7BA098B4FB5CULL, 0x36907B01FAF0C0B5ULL, 
            0x16585684AE411C13ULL, 0x5319FA72D75D8ADAULL, 0x3169E880DA99836EULL, 0x51028ADC7F446328ULL, 
            0xFEF4B5D4F2A6EA36ULL, 0x4EE4404EBBBD17A8ULL, 0x7E6A730F2B82BB57ULL, 0x6E6A779993DD7F26ULL, 
            0xD6D6B65E26A7E7EDULL, 0x5CBABB5633BE5156ULL, 0x393C21AC4BF801D3ULL, 0xFEB5B3E9CB86DFE2ULL
        },
        {
            0x1187FD5AE480EC52ULL, 0x30C666574FB20AE1ULL, 0xAE0C75A2CE982105ULL, 0xDDADFDDA763120FBULL, 
            0x6FC728200FA43F15ULL, 0x63647D5A1BE913F2ULL, 0xC44F0D74E917F65DULL, 0xD4D065C4F15671FCULL, 
            0xFDBE1C5E65C74E71ULL, 0x9800169F14AF30C0ULL, 0x233D37A4332EEC03ULL, 0x7D5B09ED4478CA8CULL, 
            0x8A7395A590761D87ULL, 0x58EEC69473FA40CCULL, 0x89FE15F3C7FD2A12ULL, 0x2AA07DCCC77E9A21ULL, 
            0x636506B06F8EB89CULL, 0xA126C190CF885558ULL, 0x76D9C13E2F4A9E0DULL, 0x555E696D7986F333ULL, 
            0x278569EA52B3BDBBULL, 0xD7573FF0207F1199ULL, 0xDE8E033EBC8449D6ULL, 0xA59EEF6B9412859FULL, 
            0x27DA751DF447949CULL, 0xB64A8960F2AEF248ULL, 0xB52B3FE65DF76858ULL, 0x7D5F4860C9148B0AULL, 
            0xB4AA2C535BD5A9AEULL, 0xC28A0F5A092F3A3DULL, 0xC578D9005D09EA74ULL, 0x6FF9571BCA54C646ULL
        },
        {
            0x6847B2D6EC002276ULL, 0xADE2DD78C0D81A7CULL, 0xB9B5B6E063D596C2ULL, 0x2D139E364FDD65FAULL, 
            0x079E435CAA42F794ULL, 0x0537F5795DC8CEC8ULL, 0x1AF95A73091FCC0BULL, 0xBD6F89158A0C0DA4ULL, 
            0xF81B6683A538CDC2ULL, 0x75EFA948AF4AE81BULL, 0x5F45A7B54FAC4931ULL, 0xB9913A83F9568B4FULL, 
            0x1582C4B47A3CE0C0ULL, 0xD5089F10CC7BFA99ULL, 0x48C05DAC10997654ULL, 0x31004D0AB79EEE18ULL, 
            0x534A8DF9CCF351FEULL, 0x2FC2181ADC00B51AULL, 0xD246A37C5A8919FAULL, 0xAEF15CC149E6E11AULL, 
            0x27260A38FA62E1FAULL, 0x7FF5EADA371460D1ULL, 0xE3FB3F775411CADCULL, 0xE6B17EF6B95DCB71ULL, 
            0xDE4409C57DB78119ULL, 0xF11C176E70651AB1ULL, 0xFA3D0E583258FC64ULL, 0x21B82029043F6EE1ULL, 
            0x607DB7B0E035B742ULL, 0xEC2ACA73419C91B7ULL, 0x45C2FA2EEB7B62AEULL, 0x79E22907690D8A69ULL
        },
        {
            0x88268DA5234C7B46ULL, 0x138651D27F30BA52ULL, 0x63977522521518ECULL, 0x5CCDC82E30D00DC7ULL, 
            0x9E09C13C745F02B7ULL, 0xFD3C8DA018D2706DULL, 0x6A4A6833902DD40EULL, 0x850E6E2E640077A1ULL, 
            0xEDD6C99A69D03182ULL, 0x97349E4260EC9012ULL, 0x826731EFDFD4488EULL, 0xC24900FE5A6BB40FULL, 
            0x6EA0FB2C16BCAD71ULL, 0x9DB722731AC9557EULL, 0xCBE5465723EF1D51ULL, 0x774837B218572761ULL, 
            0xFCD08BF9F434420AULL, 0xC9C8E3683E103AB8ULL, 0x81BB21E2E3731E03ULL, 0x7B13F917E8FC8056ULL, 
            0x6FCF5715D6438B47ULL, 0x9CCEB59C2761BD83ULL, 0x4937CEC4DE36D33BULL, 0xC51C017B165EF18AULL, 
            0x60C5F25A42C26FBEULL, 0x2311C18E6EA03E4BULL, 0x066652A4C8437076ULL, 0xC5202B14A4D49F78ULL, 
            0x1BD41CEDCC0C7B7EULL, 0x2A493F66E0E468FDULL, 0x19C70FB59E70124BULL, 0xC4F410F3428676A0ULL
        },
        {
            0x9DCB32D73714235FULL, 0x667B06EB3DCF4676ULL, 0xD8C9DA1FE0DD5CA1ULL, 0x27103FD3817D5BC2ULL, 
            0xAE9CCEFAEFB37437ULL, 0x00A1CC522D8426D3ULL, 0xF6FA2C20CF1A442DULL, 0x14CEAD7ABBC4B787ULL, 
            0xBFDB122BB2DCBD62ULL, 0xE0FFA1B035D51142ULL, 0x222DD496C125D24EULL, 0xDF02E141FF8D901DULL, 
            0x23C4FBE5D621A2DAULL, 0xA81B270122466E74ULL, 0xCABAA33061E4AEFFULL, 0x739D974ADEC07CA0ULL, 
            0x6A4A18DDFC6900F1ULL, 0xAF2242541A3CBFF1ULL, 0x17CDC8A8C5834A26ULL, 0x8F266C2C4943F240ULL, 
            0xE7C7A737EB64FF57ULL, 0x235F70B0EB7156CCULL, 0xC9B0DDAC822449ABULL, 0x1003C68AEDB94D64ULL, 
            0xD8C8E89A18CBD91FULL, 0xB062E49BF7975E07ULL, 0xF48D2FB14F352044ULL, 0xB45EE5CFA9B5B186ULL, 
            0x59CD5F137AE3B7F7ULL, 0x3C4935CBF99EB359ULL, 0xE8DEC70CD8DBEBBBULL, 0xCDFBD54FF9F8E7D2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseEConstants = {
    0xB1751625B3CA521BULL,
    0xF9E6647CE022CFE5ULL,
    0xC5664B7FCDA36655ULL,
    0xB1751625B3CA521BULL,
    0xF9E6647CE022CFE5ULL,
    0xC5664B7FCDA36655ULL,
    0x5AD5701F6249741EULL,
    0x12ADFA3303C53892ULL,
    0x7D,
    0x20,
    0xA9,
    0x5D,
    0x07,
    0xB3,
    0x1B,
    0xD3
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseFSalts = {
    {
        {
            0xD1F0B867DF09E645ULL, 0xE8D5487BC813081CULL, 0x1171A737A7B35D29ULL, 0x3FF4EB3A2D030CE5ULL, 
            0x338965B5E2E65082ULL, 0x74DEBF4AD2119E10ULL, 0x4CD7923A3D5B4305ULL, 0xE9E7BA1629D2422BULL, 
            0x96FE2EFEDFA7BA53ULL, 0x25A3DE37F5C0E5E2ULL, 0x1B97BC85C95FB822ULL, 0x798E2A336CDEA94BULL, 
            0x698FBCBE677326EAULL, 0xE2D54802431C17F9ULL, 0x369CD41C52B99AA7ULL, 0x4573E2987BE007FBULL, 
            0xAC82472841563939ULL, 0xD85B28AC94E9D8C2ULL, 0x1A5181DF23553BB7ULL, 0x8BD1C8BDB2CA122AULL, 
            0x227418EFCD927320ULL, 0xAEDC85F321DFFB64ULL, 0x5480479424E397DBULL, 0xB61D6F52D1A6A747ULL, 
            0x6F79B063D5A7A522ULL, 0xC1AC3F073676485AULL, 0xCC95B1BE6F063858ULL, 0x0C857DD77AF7FEC0ULL, 
            0x38002BF59FBCBF32ULL, 0xD859CEC5A7C24D35ULL, 0x83A7BFD96DB21B32ULL, 0x3E1C9D1AE1B51D99ULL
        },
        {
            0x5D54CA1296FF6421ULL, 0x32532F19B3D3102DULL, 0x931E79150F0E7AAFULL, 0x41603D812645265EULL, 
            0xEC149F96B7E4A892ULL, 0x36F7D9F7B1AE4963ULL, 0x314EDC1C12D3F541ULL, 0x9AB66B00D9DF16B5ULL, 
            0x76502AB43BDAB23AULL, 0x774AEA4A97BAC384ULL, 0x11B06EEECE015697ULL, 0xF59A98AFE99CB62CULL, 
            0x2D3B56A33C0C1720ULL, 0x6B6F0031B347F053ULL, 0x4CC0BB64F64C7635ULL, 0x16123CF7DA178E13ULL, 
            0x4E6792C15AC74AF4ULL, 0x2987C0BF371C5F83ULL, 0xE235903B30544B37ULL, 0x7F8304716AF4146FULL, 
            0x56FA2C344DDC8557ULL, 0x1206D0B50CF36490ULL, 0x37444C6A9A9F556DULL, 0xC2661C8F9F8C92F2ULL, 
            0xB3DB2E08FF8DB092ULL, 0x11707508026ABA52ULL, 0x9D1375E8BE80CDB7ULL, 0x3F7DE1B94D86B2D0ULL, 
            0xDCB0A2BAD1E19985ULL, 0x517A06F9ED19C2FAULL, 0xA80DEC1BBABCEA3BULL, 0xFD95B30069756832ULL
        },
        {
            0xEB30E456AB68886BULL, 0x1937274C24EE2E39ULL, 0xD9C21192A07F504EULL, 0xDBFA95316775A0D2ULL, 
            0x47F776D2AF289835ULL, 0x0109EF12B67A673AULL, 0x867585F7D6FD91DEULL, 0xDC7D708CBD14199BULL, 
            0xE74158AB69C0221EULL, 0x208B95ED1418AB49ULL, 0x26D24B0F1DCAB7D0ULL, 0x069D0DA2FCC20899ULL, 
            0x32E769C625FB1061ULL, 0x8F34A66A50A89BADULL, 0xC7E86D2C3BBFF989ULL, 0x567C7D78D24202FBULL, 
            0x92CD0B19CF37EA8EULL, 0xE85F16E28F3EC375ULL, 0xCF95A27E0A8A443DULL, 0x3D74367C225FDFBAULL, 
            0x69C0AEC0EE535743ULL, 0x49376835A81D6B67ULL, 0x7940BF9E006771C5ULL, 0x59E1F9ABDE1B71A1ULL, 
            0xA477E6A56ED66F3FULL, 0x3EA60FC7D9E9A007ULL, 0x921B7FFEBF3ADF42ULL, 0xB049E9684FA09BBAULL, 
            0x87EA899FDE426512ULL, 0xB0ACEE14EB0C8560ULL, 0x616F8A08E463AC4CULL, 0x5263ECFF6FC1A8A0ULL
        },
        {
            0xA5AFB79F4398F296ULL, 0xC74833E28C4F50B6ULL, 0xF0B6B0A36BB4C561ULL, 0x04A165934D97BFF8ULL, 
            0xF23854E4FDF58531ULL, 0xAA4B8080B94807F3ULL, 0x06CCECD1B24C075CULL, 0x4BEC4CDAB603FE36ULL, 
            0x059CF2ED6255190EULL, 0x3D8AC937344F4F10ULL, 0x77CDCE08B171870AULL, 0x0A5303C2F695E74FULL, 
            0x1D44D98B53BF3604ULL, 0xC60EAAE59712AE89ULL, 0x9FEFEA1C7923C4BFULL, 0x75BB19511077ABF0ULL, 
            0x0F2F718C2CC98766ULL, 0xF5EA586CED7BAA4CULL, 0xE735B5957C3ADF23ULL, 0x440C20AB48DE75EBULL, 
            0x6C708064B4D3DA3EULL, 0x1997CB07A93AFC1FULL, 0x1BCF854E103662FFULL, 0xD2DC7E37F97A70B4ULL, 
            0x9323E4FE59A5113CULL, 0x117A709E9D4802E0ULL, 0x5C1F1864E0787ACCULL, 0xBE0F768D0C3862D5ULL, 
            0x426BAB9410770705ULL, 0xAE04238C47C09FDDULL, 0x82FEA258F3820912ULL, 0x3FC023515B4CAFC1ULL
        },
        {
            0xD87DD2E1BD56F5DAULL, 0xE4FFD8FCB61DF5A3ULL, 0x21508E09113A3B0EULL, 0x15949B2533B31650ULL, 
            0xF1899FB89FEB2D2BULL, 0x3C70D260C4FA95B6ULL, 0xA20FFD542655DF51ULL, 0x66447050CCBE1EEDULL, 
            0x09F7FDAB4F3024EEULL, 0xEBF74D57F1ABFF7EULL, 0x55FC4FD0438F2F22ULL, 0xF835E00E6CE0F798ULL, 
            0x9E642FFE6D0CAC3DULL, 0x944E2FEC0A319C6FULL, 0x9AFE6284A17B6B87ULL, 0xEB4D69408700EA03ULL, 
            0x329BBCEBF54943B7ULL, 0xA5A2A3FCD813E52CULL, 0xA7F3AF80897DF881ULL, 0x586AB8319517C5F4ULL, 
            0x0E5D0E3E9DA5B103ULL, 0x51447389A6BAA724ULL, 0x5CBACCBE2E353BDEULL, 0xED4D698A3011F61BULL, 
            0x94E3A1D090BFFAEFULL, 0x8E5F996A9D18CA49ULL, 0x92A9C2758101FE97ULL, 0x39394725558EEAD9ULL, 
            0x8BCAFD1169E8627CULL, 0xBCA6F9935E0B3477ULL, 0xE59CCF93CD60B640ULL, 0x6DC10D3FCC53CB9AULL
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
        }
    },
    {
        {
            0x4B704212383D7901ULL, 0xAD49A7A7A6DE9AA4ULL, 0x30772DAC8138C55BULL, 0xB92648279E1D270AULL, 
            0xE4314D20C89E45B8ULL, 0x1F8AA65DDCB15C46ULL, 0xDB2DF0BA68D76832ULL, 0xDCB3D4D3DE1B1ADFULL, 
            0x66789FDEDD69BABAULL, 0x20B6BE8ADDE0D9F4ULL, 0x264C5BF0BB139C58ULL, 0x26EEDB4D98E8F2F9ULL, 
            0xE21067CC46C8C877ULL, 0x042DD32565944947ULL, 0x2D37F37808C9082FULL, 0x70148A651D64EDD1ULL, 
            0xB6D03B7D41049364ULL, 0x86748DB23B52F298ULL, 0x00601CEABACABDEDULL, 0x032138B68050E03EULL, 
            0x7437F37392989099ULL, 0x3029B2A4ABCCA1F5ULL, 0x71D1E663DD60C17CULL, 0xA269993C8A2F6999ULL, 
            0xB98A376B77FA3C48ULL, 0xA5CCDB6D97F12D57ULL, 0x55DF1A595E29F485ULL, 0x379ED1451349B834ULL, 
            0xD24CFD161D65E75BULL, 0x5C6115923DD524DDULL, 0xFA37DE199DD2D6B0ULL, 0x9AAFABC5189073DDULL
        },
        {
            0xC417E9BCA3383ECEULL, 0x4040719FC8A3A51FULL, 0x456984537F8AA2A4ULL, 0xC27973E5A4E63EC9ULL, 
            0xA05535383359DBBCULL, 0x4A3F708D78D31C09ULL, 0xBFD4BB431043EEC7ULL, 0x0C41AD4837EDE171ULL, 
            0x70805E19DBC53105ULL, 0x75EC1A24DAD6E2BCULL, 0xD4CCAF0D69258A3AULL, 0x3C04F647D2656D02ULL, 
            0x3B6347888B741BACULL, 0x3130740B2ECE73E6ULL, 0x67FD73B115AD2018ULL, 0x5DD1C9E442E3A8B0ULL, 
            0x6CD86B7402F17848ULL, 0x581B869C871C7392ULL, 0xDCF53EC9CC63E76BULL, 0x230AEB4E51BD65C7ULL, 
            0x34BFEEA265269ECBULL, 0xD641B2E422DE117AULL, 0x5E32EEFA9AE82801ULL, 0xC0D75A1F6996DAD2ULL, 
            0xF4346E0342274FC4ULL, 0x02A9BDCA7AD45891ULL, 0x48956B19BA88F313ULL, 0x403676DBA19AC534ULL, 
            0x78B197A153746470ULL, 0x4FCE2440A5B0DC69ULL, 0xC71C84712B2C6225ULL, 0x49D2989577120032ULL
        },
        {
            0x2FF6466F953C8530ULL, 0x049341E58B06F19FULL, 0x8284B01EDB7D5561ULL, 0x61AF2793B2575DF9ULL, 
            0xED8CC2785547A490ULL, 0x24CD03CF94DAA946ULL, 0x0B7909C0B4E58339ULL, 0x12FF83DFF213CB18ULL, 
            0x40F18B1C02FCE975ULL, 0x7C341C379294ECFBULL, 0x99024830ABA7C35BULL, 0x5C8BAB05681C8CB9ULL, 
            0x39F5FA1645EF9799ULL, 0xCDC004BA49D66C89ULL, 0x4A517CF45246D9FEULL, 0x71BD3205255F9744ULL, 
            0x634D13C49C4EF171ULL, 0xB10BCD7EE82915A7ULL, 0x3B1357122186A6A4ULL, 0x83CA7254120C7E8DULL, 
            0x9315FF0AC203A508ULL, 0x581007342FFDE182ULL, 0x51F01395E8D41554ULL, 0x7F046DC7693E8816ULL, 
            0x9120043420678C4FULL, 0x6D80AA6465439471ULL, 0x685D5299A1B98996ULL, 0x11B6788768C45653ULL, 
            0x92770DA19AB81022ULL, 0x2F8E02323E73F7FCULL, 0x0D213429D6FD5CBEULL, 0xFA44DE2519A2671FULL
        },
        {
            0x409341FB02E642F9ULL, 0x0ED7B32A6A860A6DULL, 0x36FEB2586DF1B648ULL, 0x16B545A40F267245ULL, 
            0x3B3461171FAD7473ULL, 0xA89F37BD4D911357ULL, 0x93D0350859DFC631ULL, 0xE04770FC44A4C926ULL, 
            0x0AEC5DC8AF224076ULL, 0x0BBA56C68C2F072BULL, 0xF720A1E7E6E19BC4ULL, 0x5B72F393C233D697ULL, 
            0x6A4ACECE5EC3E66FULL, 0xE034A75D6829D8C4ULL, 0x5455B337CC446AECULL, 0x70853D09849161A1ULL, 
            0x6FEDB98D5A51D2A5ULL, 0xB877548CEA8DF278ULL, 0x0CF746BE41D0AB7EULL, 0xB90D845E3DE3DB79ULL, 
            0xB3D756F954D7C6BBULL, 0x80FF3EF88B8A3753ULL, 0x52F0AE4961AB6845ULL, 0x2AD0115FD8C83F44ULL, 
            0x532614024D0C9D33ULL, 0xEBB04B836AB79755ULL, 0xD1A5E4A52D6D8A65ULL, 0xC46A985C4F97636DULL, 
            0xD946E94D4194DEC0ULL, 0xFCA02EB2150CBCAFULL, 0x19E393FC844E44D5ULL, 0x27815325103EF149ULL
        },
        {
            0x92F95BF0EFA92394ULL, 0x18616BD500CF6DA2ULL, 0xC0BB68C0CDE46F77ULL, 0xE5210BC6475C5DAEULL, 
            0x2CFE61323BE928C6ULL, 0x2386C1C9EE92D442ULL, 0x9A383F62A5DA3BFDULL, 0x3DAA0E7BF38130BDULL, 
            0x86261030836BCA80ULL, 0x9080BD4D0E844D34ULL, 0x90F76D9B2DDC6133ULL, 0x96C4BE9651F41B6CULL, 
            0x35F1678FBDE11CBCULL, 0xF840A8923AF9071EULL, 0x7FCD869594C83335ULL, 0xFA9ABBF173AA8162ULL, 
            0xADFF7CB85B51C961ULL, 0x4C3591DCD3D28756ULL, 0x09B504B7EDCA256CULL, 0xAA85D135F56F1B2EULL, 
            0x4D837315E8924434ULL, 0x52C6DEEF30A50D35ULL, 0x2EA5C6B17B8075B4ULL, 0xD31EA0ABAF37F1F7ULL, 
            0x1159304DCDFA8C89ULL, 0x7A341B28451764C1ULL, 0xD9B3459C64892A3DULL, 0xFF9B7D035D1D70B3ULL, 
            0xECCECCA8902BDA97ULL, 0xD4040FAF8FD8B30AULL, 0xF90269825066C257ULL, 0x8E51507A0843BFA8ULL
        },
        {
            0x4A112F9461156AF5ULL, 0x8C56FB45A37ACCE3ULL, 0xF3A116C5D1B21135ULL, 0xEA1875B699B458F3ULL, 
            0xDAD63E02CFE9FA56ULL, 0x3ECAC2AF84E1517AULL, 0xF8CBF24EC14E85A5ULL, 0xB93FD4FFAFE4C0CDULL, 
            0xF60428DD841C1F06ULL, 0x1AB20A2DB6697BFFULL, 0xA65B5F5A313479D7ULL, 0x424662E21324FA7DULL, 
            0x4793B0A33873F001ULL, 0xEDEACF3115A46350ULL, 0x01E39D0F116B2AE3ULL, 0xC4587FDB83C0C275ULL, 
            0x8E5B3965062C0EC3ULL, 0xEA7B46AE83542420ULL, 0x49EEF7D2FFE59829ULL, 0xB1E21A66CC866988ULL, 
            0x53DDE09D8466FCDEULL, 0x01A2B87B3EC2D487ULL, 0xEAE4FECC99E3EAA2ULL, 0xAF7BE97BCC2DE567ULL, 
            0x2EFCE0358EF15056ULL, 0x947A025348326911ULL, 0xB1626E2AB9A26AD2ULL, 0x37862FA90129C184ULL, 
            0x7EF49FB1C3DBD5D9ULL, 0x07C51BB13D9EC5EBULL, 0x388189C9A8570598ULL, 0x2FFA170EA89EC49DULL
        }
    },
    {
        {
            0xB75D20EAB75ABF7EULL, 0x26FBFF6E96397D06ULL, 0x63C76AE8D34B465DULL, 0x4F0CEF67BEB818CFULL, 
            0x66AA75DF073E5B77ULL, 0x21BF4845842B4078ULL, 0xAC8C952D9AEF7909ULL, 0xFC3031BB07605425ULL, 
            0x1BB9523FAEE25D7BULL, 0xBFFA3A593DC98949ULL, 0xE20D2DCBC5F0661AULL, 0x9D85BEBC158BBBF1ULL, 
            0x719166AE25CBF4FAULL, 0x6D6B9C9D03D886FAULL, 0x2F98076EE83337B8ULL, 0xEA6E43473E5ACF79ULL, 
            0xDFA4BEADF7E26770ULL, 0x960BB479590E1D31ULL, 0x89DF6CD9674A8988ULL, 0xB00EEA1B8345B358ULL, 
            0x810175A105B56B4AULL, 0xE410C0CA1D8D9424ULL, 0x3957A272DD9A5DDCULL, 0x34FF40FD59D40FB5ULL, 
            0xED49B77C54A55D0FULL, 0x544903948392C899ULL, 0xE6B992ABB7FD8D1FULL, 0xD32DDB5C87D41555ULL, 
            0xE40572B6721F828DULL, 0x040D7E88A9570909ULL, 0x32B98E86457AFAE8ULL, 0x32B32EBED294C065ULL
        },
        {
            0xA536B1F174A0CAC0ULL, 0x7A4D248F3E131541ULL, 0x76EC256C02A70B6FULL, 0x001E00C41D970C6AULL, 
            0xF87618651A87B103ULL, 0xD93EF5DE39FA57DAULL, 0x9F11BEDEA4A6A47CULL, 0x4FD62057D8BC4D24ULL, 
            0x73026F7BDC42BFD9ULL, 0x57E8A4CB4429A8B1ULL, 0xD7FE78F0F7BB7F0DULL, 0xF336D6D9A07AC0FCULL, 
            0xD8CD9FD7C9285882ULL, 0x83FC34D71CB9FA05ULL, 0x60D59D4BBF52804BULL, 0xA607E2B1254ECDA3ULL, 
            0xB5F28EEE198218BAULL, 0x2AAADD8317B628B3ULL, 0x41903F43AD7B3EB0ULL, 0x55782DF41A95AF1DULL, 
            0x948A0404B4C5C671ULL, 0x873AD79A0279302AULL, 0x4951B5A9B91FB508ULL, 0xE061D0DB0EBCAFEEULL, 
            0xF391FFC47A546CEEULL, 0xF8E8DD3B31078BDFULL, 0x1BB18EF18252D830ULL, 0xB3F2C376A675689BULL, 
            0x49772FBE5510B128ULL, 0xCB51907BF4BF2A74ULL, 0xEA19F8150BD9BA59ULL, 0xCB5AFA32188C91ACULL
        },
        {
            0xF57CA4627378CB1CULL, 0x9FC9B8EC97E54063ULL, 0x80D68F19026EE13FULL, 0x03542A72D8FF67CBULL, 
            0xA6308FA6026E56A3ULL, 0xF1ABCC9FEAFB5715ULL, 0xB175D153F5B6F3B0ULL, 0xE9EF2182DDE2F160ULL, 
            0x253F467A326BF185ULL, 0x1BFC21259C8C1EE7ULL, 0x714C9CAC6E52DE60ULL, 0x151FF7A6BDEF7DA8ULL, 
            0x8D54D4DC5AEC631FULL, 0x1FA940256F5806F6ULL, 0x023D331D39770AF1ULL, 0x94C3F0C0158751A6ULL, 
            0x99B65DD8B4EB4032ULL, 0xD66CC25AE8EDA412ULL, 0x4CB8AE37134E04E0ULL, 0xA9F411DDF51583F9ULL, 
            0x6CCA2F5A6499EE17ULL, 0x0480010166B97DCBULL, 0xAA075C2EA8194480ULL, 0x379E6395F36A2CB8ULL, 
            0xE71D33CF305F2D9EULL, 0xF0B32B9EEBA249FFULL, 0xA1921FDDBED44502ULL, 0x72D251729955466EULL, 
            0xE8F9C67F87A5C23CULL, 0xE040EAA7A510C932ULL, 0x9801284143CB3845ULL, 0x049B587C962EBDC6ULL
        },
        {
            0x8BC541C2F22167F6ULL, 0x54D887E3D58E7080ULL, 0x6995E47C708E0068ULL, 0x5D6DF3FF94243D19ULL, 
            0x4F80FD8670B1E3DDULL, 0xB3F990F49323CF0AULL, 0xCF31D81148845F5DULL, 0x7FCE6A6C7B473EC1ULL, 
            0xC2439C2C9EA60330ULL, 0xF20AF13F0E225FEFULL, 0x4EA666BF7E206135ULL, 0x9395E27B9EC1263DULL, 
            0x2ED7DF023C47D2BFULL, 0x6BD59702E1997B6FULL, 0x5479E528AA13751AULL, 0x6CF5F05A770F2072ULL, 
            0x860E2F4155F046F6ULL, 0xE851CBD94A9C74AEULL, 0xF2A8F918D894A7CAULL, 0x1DC517E8A2A3701BULL, 
            0x674425595DEA6F40ULL, 0xBEE7F974F04B28ABULL, 0xF79A30161488E37EULL, 0x5C459F1A263283A6ULL, 
            0x5605E0CE7DDEE376ULL, 0x9F5E337EADEE0E90ULL, 0xC212D5A3650709B1ULL, 0xB9CE35F982F3ACC4ULL, 
            0xDEA9C54123819AE8ULL, 0xC4F45183DCF39D51ULL, 0xAFE13A5DDF02BBEAULL, 0xAF37D8426CA909E3ULL
        },
        {
            0x22A0ECD0B75A17BDULL, 0xC22D974F7F1BCA82ULL, 0x5BB2FD7684FF5FF1ULL, 0xAE069E57052EAE08ULL, 
            0x53DFBC55F1B7CF78ULL, 0xB5A603425879B566ULL, 0x94244702CAE69921ULL, 0x87C5EAF074AFE399ULL, 
            0x03FD1C15B1291747ULL, 0x662D762E9667D70FULL, 0x1AEBAFCB7F60AA55ULL, 0x02D0353383867E2DULL, 
            0x1511BA3DAC07819DULL, 0x3AA3A965842D7913ULL, 0xC25B7450A5B6B4C7ULL, 0xD06A994EACE7C037ULL, 
            0x5DFDF1348C87870FULL, 0x79B104B966006A95ULL, 0xC59FAD3CF4ED3BE4ULL, 0xB6B524B951822467ULL, 
            0x091C6C84825BC03BULL, 0x77B1747680E2E6FFULL, 0x4CA1E743ECF13E70ULL, 0xCEC3460C049E26C1ULL, 
            0xA442E4D653A00457ULL, 0xB1026599DA156558ULL, 0x3482D871A6415D64ULL, 0xC3BD41439A44EFB3ULL, 
            0x59D5D81042607327ULL, 0xAD0EDAB6D501767FULL, 0x645A738768517CABULL, 0x484D16C0D6F50CC9ULL
        },
        {
            0xD4B1FF8D97A7CD34ULL, 0x594B91521D1D61C9ULL, 0x4329EF887AFCBCE3ULL, 0x31BC070BBC779E6EULL, 
            0xE4CB3A666EE57834ULL, 0xCD91947E151930D2ULL, 0x2940A7598839ADDAULL, 0x47F4C25302A55C4AULL, 
            0x158B6F1CBB0AFFF7ULL, 0x46D93A54EB2054B5ULL, 0x6C0984CA21FD4D4FULL, 0x5A03D4C0AB3795CAULL, 
            0x296DFD81C833BA7FULL, 0x166FD73E9493642EULL, 0xDB8E714E1BD04F03ULL, 0x258BA1D92AB673C9ULL, 
            0x6459BDEC98F884E8ULL, 0x72C96F4A7C5302B2ULL, 0x17161F625344BF44ULL, 0x9823A1CEB86DC344ULL, 
            0x06EBD630F34B29F9ULL, 0x8400F7BEBA0B1D1AULL, 0x038C88E968BC43D4ULL, 0x9AEFD4F5B7F8D017ULL, 
            0xBDA1CAF2494BA3D4ULL, 0x6365206956239126ULL, 0x57FACF733E72D873ULL, 0xF1E56EA651933281ULL, 
            0x60DD6293477F2811ULL, 0xD7A4D37993249ACDULL, 0x1D66BA2224610456ULL, 0xF6D6199CDA92C5C5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseFConstants = {
    0xAA34936E00BA4384ULL,
    0x97B621205ECE83F4ULL,
    0x58FD456FE9AF2696ULL,
    0xAA34936E00BA4384ULL,
    0x97B621205ECE83F4ULL,
    0x58FD456FE9AF2696ULL,
    0x4DCFD2749E5ADEB1ULL,
    0x1BC551DCCB313084ULL,
    0xB1,
    0xF5,
    0x9C,
    0x4E,
    0x67,
    0xFA,
    0x1A,
    0x99
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseGSalts = {
    {
        {
            0xF1357534CC3514F4ULL, 0x0DA759324CDD3A08ULL, 0xA35C00D7C3B814C6ULL, 0x0B57647668C6672DULL, 
            0xF2FC4F7C84E87169ULL, 0xDD4C75F87527B78FULL, 0x103B0D6F379B9D5FULL, 0x1704085D6A6717F5ULL, 
            0x57D036A296E39A5AULL, 0x099DB62276D6ED97ULL, 0xBE60B874A961731BULL, 0xE0D6B79142106C01ULL, 
            0x483DD2FFD2B19B8DULL, 0xB4D3426D5DC990B7ULL, 0x5A98C967DEB274D6ULL, 0x86FC17E204DA9962ULL, 
            0xA210B9349119C74BULL, 0xA23496928A28C78FULL, 0xC42837850C8AE866ULL, 0x684F6AFC85726697ULL, 
            0x5BC197935584D0B7ULL, 0xFECBFA342D632132ULL, 0x062D3C1467D5CE85ULL, 0xA69C9E3CFEDE97B5ULL, 
            0x5B8393597E132588ULL, 0xF2B7525D02067BFCULL, 0x15F38CE11C94578EULL, 0x6D330DFF480947FCULL, 
            0x1FBFFAE68A9354C2ULL, 0x4E3BA1C6E91482B6ULL, 0x7255005E10E0E0FBULL, 0x395A3F7701111A79ULL
        },
        {
            0x27D9EE1B534CD253ULL, 0x75896798612EF70AULL, 0xB7530E3ED7A5385EULL, 0x6171D75EC5A21695ULL, 
            0x9E631784AF4217B6ULL, 0x3515AFF35416775EULL, 0x48D6DCC221061C02ULL, 0x4AD542EEE0BE64C9ULL, 
            0x2D82394700A139E5ULL, 0x60A0793EA732BC54ULL, 0xE796300B1137DAA4ULL, 0x1734534129108914ULL, 
            0xD44908B681E858CDULL, 0x90B0F764C657A2C9ULL, 0xDB40078DDDFFB715ULL, 0x50B99FCFEAD64D76ULL, 
            0x6DEB99CD332FBE12ULL, 0x98EE2D5A5E8D9B28ULL, 0x8034B3EB2C65ADD0ULL, 0x6748E3CA3036265FULL, 
            0x343BE6FF19D25F1FULL, 0x5758FFD483D0C8E6ULL, 0xC37E69F78822446DULL, 0xED53CAC94D06DEA7ULL, 
            0xD24FBA7F2F62404AULL, 0xD3C611113381E9D9ULL, 0x2EE62B1E6FBE9392ULL, 0x830F6C4D36FE0D16ULL, 
            0x1F25E497B54C3522ULL, 0xA51CDC5621CECCF7ULL, 0x4FD1D300B332FE73ULL, 0x5674D237D8DB17FDULL
        },
        {
            0xE6AF3E24CE28F269ULL, 0x9443692DEBE2AF0FULL, 0x4B29421E3D4D6159ULL, 0xE1945AC8F348AF6DULL, 
            0xA103CF24D3C34F42ULL, 0x5186C7FBE74ACD21ULL, 0x5CF0191976EFD227ULL, 0x3F5B5367F25E6201ULL, 
            0xC6E325B542BA3CECULL, 0x2067EC36F8FF626FULL, 0xDD678EC0AE52355BULL, 0x57EC87D072F01832ULL, 
            0xC0CAB7FD4A621196ULL, 0x4D82D2CBA9CB5347ULL, 0x290194B0E97D18A1ULL, 0x45C8D144F22DF762ULL, 
            0xD7C8BF05B4259DC1ULL, 0xCBA0D668376EF7F1ULL, 0x549F29F6D1A49F4CULL, 0xFC224528D4BF31E5ULL, 
            0x5EBE302F9DBF999BULL, 0x08CAD6715433DAC1ULL, 0x47B3D23ABC6CA4C3ULL, 0x9ED2CA76F03534B4ULL, 
            0x9DAD6A5CC893430FULL, 0x8395240BEFF1BCD7ULL, 0xD728AB044D22815AULL, 0x2119A8223EE1BB22ULL, 
            0x333B1CADEF02CF34ULL, 0x65174069106F524BULL, 0x3AB3CFC43E378E40ULL, 0x4BEA631799BE91EAULL
        },
        {
            0x7731746F26038801ULL, 0x442D676D14144B91ULL, 0x065470A49EB13E30ULL, 0x5FABDDF199814FA3ULL, 
            0xE4B8CA282DD397B6ULL, 0x06C83E93CD3159F2ULL, 0x94CEC3FC2C7363DEULL, 0x56D5701769C75450ULL, 
            0x393C6F8C647BE79CULL, 0xA196E9089A1E9628ULL, 0xB18CA5173F187BAEULL, 0xBB5A7759EC91EF5BULL, 
            0x127F1276562E88D8ULL, 0xB259F721FFB12745ULL, 0x5DB82CEB2876225FULL, 0x16D0425A8A39EE8DULL, 
            0xF912822700D66465ULL, 0x2AF287ABC6C9C531ULL, 0x1133C18F60BE6A2DULL, 0x9EF3E9DF2737A8CEULL, 
            0x9E285267E255917EULL, 0xAA838C94EEDD7C8EULL, 0x3BB453C75BB0CF8DULL, 0x8D6D4F6FA27B6384ULL, 
            0xA43B91534C418F09ULL, 0x761D458C20200DBAULL, 0x86B1B8C09C3B3567ULL, 0xF1D8898AAEA4DC3FULL, 
            0xF588B73AB41A104EULL, 0x8207B3209129B78AULL, 0x41078DF72A75D0E3ULL, 0x78BBD2DE02322E09ULL
        },
        {
            0x02E48FF1B2BA7293ULL, 0xC10BAB93B90CE0ECULL, 0xFBF7CED2DEE102B6ULL, 0x559BB968E4E6F440ULL, 
            0xF7F01752382378B6ULL, 0x3AD20B1C30430A2AULL, 0xDD015470A841892FULL, 0x3235FD9C7205BEF6ULL, 
            0x21351B1CE7B1318DULL, 0x8CE17133EF74CB5BULL, 0xD9B30B777E4F66FAULL, 0x46AAE2D1978E9150ULL, 
            0xA08727F9A8802702ULL, 0x73651EAEBD30FECBULL, 0x6AACDDD75ECE6708ULL, 0x8EBE3F25480511B3ULL, 
            0xDF99E25320DC90DBULL, 0x9D0E942652763B6BULL, 0x2F14C88EC45CDA5AULL, 0xB45CBFC9DE46AAF2ULL, 
            0x98A3C6708D97BE93ULL, 0xE3F5ADA531A080ECULL, 0x4C8068E8092BF992ULL, 0x679227931BCA9497ULL, 
            0x9E55DE1C74753C54ULL, 0xB7DF000370A7433EULL, 0x52C296949C95F0A0ULL, 0xAA7659D88986137CULL, 
            0x50B35F36F4CB4240ULL, 0x4E3D9AD502B88AF7ULL, 0x4C845747F02FADFCULL, 0x485C7CF07604F694ULL
        },
        {
            0x759502369DA16879ULL, 0x41C72D5EDACC4704ULL, 0x6F5145D24F35D347ULL, 0x1224CD70307E1F2BULL, 
            0xA01DFA1E77C5811CULL, 0x827D178619D24353ULL, 0x58B7756D66B11F21ULL, 0x3E41415E27B19183ULL, 
            0x544E44D720649EC5ULL, 0xDF0E04169B8177AFULL, 0x8950EFB2E70F3AC8ULL, 0x0179D4CB2F355470ULL, 
            0x583860BAA41DBA7AULL, 0x0C77202F967EA106ULL, 0x8C68B7D100CC0519ULL, 0x11EAADC2CB9C7BB6ULL, 
            0x015AB59FAA40452FULL, 0xD35EE4ACCA1861E7ULL, 0xB3032C94B8F0C44BULL, 0x80FBFC6F6A8B7658ULL, 
            0xB5CDF42D05A58E61ULL, 0xF8EA27F94CCA5540ULL, 0x1E370499EC567ABBULL, 0x02F21C8A140F38A5ULL, 
            0x4BB6134C8C2A8752ULL, 0x244602147DA8532CULL, 0xD47636FD6E67EFC4ULL, 0xA14B6353F7C0D1BCULL, 
            0x3A76C143ADDEA9F0ULL, 0x3585889799296521ULL, 0xDA94488DA9B3ED12ULL, 0x0BD1DB5F29E4C661ULL
        }
    },
    {
        {
            0xC763A61671D68A85ULL, 0x2DCC552998DEC20FULL, 0xF9C6E817E5192284ULL, 0x8B3EA4D1054009F9ULL, 
            0xC3B882386886710AULL, 0xF1E27B4C273CEA70ULL, 0x5C03519450DDE33CULL, 0x5386F7F80E0FA2EDULL, 
            0x2294B6194F46048BULL, 0xB1B1F0CE68994150ULL, 0xD5E4EB06DDA2B244ULL, 0x9477EC5F7858234DULL, 
            0xCE8AB3261D4AF722ULL, 0xB6D5138A4D864AB2ULL, 0xC888CD9A7F0FFA0AULL, 0x947795DE7C8AB52AULL, 
            0x82CE5229F442BDA0ULL, 0xC5377C5A18803450ULL, 0x9B15660EB4A600FAULL, 0xDE79A1470C0494F4ULL, 
            0x0722B94DA72FBC00ULL, 0xB59E1157E528263DULL, 0xE680AA5EFB165536ULL, 0x3AFCA0E6A7622D7AULL, 
            0xB6328B9D01248738ULL, 0x02F7F9EBB540192AULL, 0x43E218358099B016ULL, 0x527E0621A0AFEE80ULL, 
            0x95A92E85C3B0A1A6ULL, 0x587D5CEE22E7B847ULL, 0x24618601A3CC4976ULL, 0x92D5CC67B51C2686ULL
        },
        {
            0x1E2EE4EF7C5759A4ULL, 0x73ACDAB2787B0767ULL, 0xFEB122415CFEDF8DULL, 0x5CC7DC829B20ABCEULL, 
            0xCCB15D96EF0AABDFULL, 0x4074FC28C7ACA8A9ULL, 0x54A120AB2D124699ULL, 0x8EFF86D849B7DEFEULL, 
            0xAE058E5870BD9096ULL, 0x6090D763CB3B9796ULL, 0xEBE23AD163DE9636ULL, 0x3BF46C908E36C774ULL, 
            0xDAF7472954CBCB37ULL, 0x7A546FF629056876ULL, 0xE558217F441E8DD4ULL, 0x1157714A033FEC04ULL, 
            0x78EA4D3A7001F738ULL, 0xB60CC84F4F9FCEF6ULL, 0x46AC21C13312D05AULL, 0x7330B2A843CB6011ULL, 
            0xE5CEACD8FDC22EE8ULL, 0x64548D4E6960E1F7ULL, 0xF2220DC2202C75C0ULL, 0xEE7C158C68AB99E3ULL, 
            0x33CF68934102A761ULL, 0x0E295F16263A5984ULL, 0x33C5934A5504CA2AULL, 0x425F8E067E4C7595ULL, 
            0x519B44A7E3C5CB3DULL, 0xA83ED469EC66F4AAULL, 0xAC819C9718AEA860ULL, 0x6A82A29D97C910CEULL
        },
        {
            0x9712228371439F04ULL, 0x2B95E6DF35259D6BULL, 0xFCA657DC3E6FDDC7ULL, 0xE2B5C91C6E6BC2AAULL, 
            0x6E89580BCB9C48CDULL, 0x05DFB0B42A59CBA0ULL, 0xF8CD7EBBD8220A18ULL, 0x141B6354320A11B9ULL, 
            0x265C1A475FEB1AF0ULL, 0xF73A3F71BDC643BBULL, 0x4010BE493F0E8948ULL, 0xC9DDD97A8310FA01ULL, 
            0xABFE0BBEDD2FA355ULL, 0x92D701005BE781EEULL, 0x16DE645BFCDE4391ULL, 0xA54B59193AE07089ULL, 
            0x341B311CC290C86FULL, 0xAD827C37D4396702ULL, 0x6E8713E640792B0FULL, 0xA19A4461A44FD716ULL, 
            0x4F2E4022CD843B40ULL, 0xB44B205BDD74B231ULL, 0x144C580D782B6A97ULL, 0xE7725DAA077C6DBDULL, 
            0xE1FB991C073C9900ULL, 0x12F4612BADFB048BULL, 0xDC2061444A5B6BD7ULL, 0x6CEA2FC432283CE4ULL, 
            0xFCDBDB8B33C902F9ULL, 0xDDE90A09D9264503ULL, 0x91726C0D30B06D7CULL, 0xF44BC9A276E68164ULL
        },
        {
            0x186FCCE64E36413CULL, 0x9C33025F6F20ED2AULL, 0x8B3162DE1F65F686ULL, 0x193A4BE421DAB133ULL, 
            0x0957C825821D02A1ULL, 0xBE232C3C9280137BULL, 0xDD9AD6DC59D667C2ULL, 0xD255E545DBAF4727ULL, 
            0xAF2BBD14328B1BA0ULL, 0x89B446E30E85BD8EULL, 0x4B062730739E5911ULL, 0xE4922F84D8F2276AULL, 
            0x962D51FAC8AF6081ULL, 0x805E213484F8F449ULL, 0xA76E8EC1EF436FF5ULL, 0x646B41E01601F4E3ULL, 
            0x3831A4A37DFF2F94ULL, 0x87B423F40A7A6DACULL, 0xF94F07142DEDB06DULL, 0x3A60FD2D39F3F8A3ULL, 
            0xB4EA11A3FB84BC94ULL, 0x607CA67923945FF7ULL, 0xE2FC95B30D12DE47ULL, 0x31C94878F9552FADULL, 
            0xFB75CFA00E9A70FCULL, 0x20533DF26DEDE6D3ULL, 0x800C0E19B3DB9FAFULL, 0x945A0D46FEFC4325ULL, 
            0x0AFF311A60C35286ULL, 0x88CAD8E384EBE2E2ULL, 0x21C990731E1E1214ULL, 0x739EAE8EBC6C2C67ULL
        },
        {
            0xB3E3B5A3B32CAFD6ULL, 0xD706090BCF0063E9ULL, 0x9C99D24151701560ULL, 0x60BFFBEE58E52967ULL, 
            0x7AE1B5E0163F75E7ULL, 0x058FF80101560407ULL, 0x4885184DC68B036FULL, 0x6AA70A37D7BB89B8ULL, 
            0x08E1B486FEC1A496ULL, 0x0B10F857C91F96DEULL, 0xC233E8976870FED6ULL, 0xE48A7CB1C09F6830ULL, 
            0xA1CBDB0A13E98060ULL, 0xC82396B7C4546820ULL, 0xD445F767D1739B8BULL, 0xEEFEBA86C3988E2CULL, 
            0x7F0B5A24E03240F3ULL, 0xCD82560ABFA54092ULL, 0x0601B2EA9A78D39AULL, 0x29D83C7FE6DD0FF6ULL, 
            0xEE8468D352A17751ULL, 0x91F6012DE49BCF44ULL, 0xAC6862BD204B63B3ULL, 0x413465DA08E5C77EULL, 
            0x1AA98B0DFAF4F09DULL, 0xE48D60C26E825EF3ULL, 0x532C01B0C9C09F3FULL, 0x0BD3C61A88EF3970ULL, 
            0x2467178DA42DE39DULL, 0x381B3A7F73A4056DULL, 0x09086BEC5D5ABC90ULL, 0x5BB13DF78D3AFDFDULL
        },
        {
            0x69F61225FF40474EULL, 0x5B60F3102A87935FULL, 0x9FC4DE4BABC9B81FULL, 0xAC0BED7C3E3B4353ULL, 
            0x4AE854F986EEC3A1ULL, 0x757850D8A3E853C8ULL, 0xA4726B3C6367CD90ULL, 0x553992868C53DCE6ULL, 
            0xF90D0D6F3B816819ULL, 0xF505026C4ABE4444ULL, 0x7BA895B67B00E634ULL, 0x7B43E2662382FA3AULL, 
            0x961C600D6EFD2E7AULL, 0x67E12B1456B5C201ULL, 0x5E0C860BDBDD1494ULL, 0x33119FEBDCCB8884ULL, 
            0xBE292951FE2A67B3ULL, 0x1903DFFC5582CCB8ULL, 0x3A3AA62C3296B661ULL, 0x3B963B08632D25D9ULL, 
            0xAD32F428960A1673ULL, 0x97E20B03CE67888BULL, 0xD7F6685E9D287FC4ULL, 0x067635153B73E719ULL, 
            0xDC97D164E5CD6867ULL, 0x50956CE5403A3BF2ULL, 0x4F95A18BFC540C0DULL, 0xFDE3794CCC408696ULL, 
            0x510344980FAD1A8DULL, 0x036432FE1735EEEAULL, 0x30810D90B9D54DE8ULL, 0x5743292DF965D49CULL
        }
    },
    {
        {
            0xB16A623EECA8E9FBULL, 0x3C4C5B3B94E8C6B8ULL, 0x1AB34D04B8EA5BE8ULL, 0x9FAFCA935B3B6031ULL, 
            0x3ECE4DABB73DF2A5ULL, 0x7E382F01CB2F2538ULL, 0x1B78B7987C21F46DULL, 0x8F19D3D9E41E737CULL, 
            0xC72B239BB0BA8081ULL, 0x28BE385F6090A0A5ULL, 0x4BCC46CC3D9DA185ULL, 0xED6AD252DF3BA754ULL, 
            0x9D592F1E21567308ULL, 0x4DF3350FE3F809EAULL, 0xA172795966741FF6ULL, 0xB3586AAB2542AF10ULL, 
            0x68851B34283A7CDBULL, 0x8A7761B27EA263C8ULL, 0xCA3B7DE10668282EULL, 0x985216B178A296C6ULL, 
            0x064AAEC0F78A4FBEULL, 0xDAA2C773381DCD09ULL, 0xCC106BD92DE210ACULL, 0xB2D07860878693FAULL, 
            0xA36354A12E0B678FULL, 0xF87B9A25E92C04BBULL, 0xEF0EBEC01A4B2DFCULL, 0x91EB510318F52B43ULL, 
            0x638FC384EB1C546EULL, 0xB44F44A97DA3556FULL, 0x123791C27F7C333BULL, 0x902C2EEBA461E458ULL
        },
        {
            0x3B3A57A64F06E2BCULL, 0x28F13451D0C65F94ULL, 0x58A54B77B620F158ULL, 0xAB37226AA4619635ULL, 
            0xE9DAE3D5578A3F32ULL, 0xED7DC9816AD9F6D6ULL, 0x54A7A0C99798656BULL, 0xD1936764BAE6BB20ULL, 
            0x7B4A288030F28884ULL, 0x885CE92E5E9BEBBCULL, 0x46C785722F7C4B1FULL, 0xB8C469B91CCA6F0DULL, 
            0xF0A5645009C38801ULL, 0x89753906A3A628CAULL, 0x14596C0564CD9C48ULL, 0xFE495C3CE3AA1BB0ULL, 
            0x67B3F5FBFD2ECB63ULL, 0xAE63207E3AC61F7DULL, 0xCA4B49A8B19E4716ULL, 0xC9E228150D8BEFB2ULL, 
            0xDF436EB402932E9EULL, 0x498CEE4BDAF09973ULL, 0x9A9B55A8385A5E89ULL, 0x9F5DCD41FA78D027ULL, 
            0x4D4BB609A9EDA76EULL, 0x3781C11F4B1D6F58ULL, 0x8C15875B74BC6F96ULL, 0xDC61582DA06CC9C3ULL, 
            0xCA51782F26D34DBCULL, 0x22541CBCDBF9738EULL, 0x4632AAE92592B826ULL, 0x29323C6D6BF7FACFULL
        },
        {
            0x871FDBD397A3E750ULL, 0xD11CFBB3974CB85BULL, 0x607D22D5E0BD8703ULL, 0x2D73AB1C08D5DF40ULL, 
            0x7A2967B45A6FA0E7ULL, 0x1E2705F193E74357ULL, 0xC163041F81E1DFE5ULL, 0x94BA683D6F7F048FULL, 
            0xE8A914784F700091ULL, 0xEF39AD79E422FD5CULL, 0x6793AF0865373A54ULL, 0x1B42B2FF027CF929ULL, 
            0x53B753A74A3B5D4EULL, 0x9F12614425DDC389ULL, 0x986007A6F27F76A7ULL, 0xF4A10C1A48629C2DULL, 
            0xC328BA7460653794ULL, 0x467092B6166F5278ULL, 0xFCDB52A1BD9CE2A4ULL, 0x2685008302A9BE93ULL, 
            0xB5246BFF45A5A957ULL, 0xF945E7E7AE3BEE9AULL, 0xB30ECE054C68442DULL, 0x8271507EF49EDA19ULL, 
            0x9BC1BCBEC66E7818ULL, 0x2EB77E13A350D537ULL, 0xCC42FB070A504700ULL, 0xEFBEB66E8A6CE13FULL, 
            0xE3263EAF5D0D338DULL, 0x59822FDD9823F3E6ULL, 0xE174DAF33F0058E6ULL, 0x7DE82BD2A75B8A26ULL
        },
        {
            0x6FD472B296F044F5ULL, 0x82B9AFE4A8D3B680ULL, 0xD9176B9D356C3F12ULL, 0xA3C24CE57466AED7ULL, 
            0xFEDA15874F7861F4ULL, 0x118FC9D65D56C459ULL, 0x7F07232B001B14A5ULL, 0xB9848D06CCBC1BF0ULL, 
            0xC32CDF591C39E90DULL, 0x59441922F6A9699FULL, 0x2913533FE9BB8221ULL, 0xE0965F894928EF47ULL, 
            0x3C4BC39746B47B37ULL, 0x14F5970312AD8861ULL, 0x1C8678B73416F1F3ULL, 0x5944FD55F4637679ULL, 
            0x2C17BA349D6F6A6EULL, 0x4D0EB1B3C8E8456BULL, 0x2059D018B5C59020ULL, 0x81532D15FBECBC16ULL, 
            0x146EE0C5791FBACEULL, 0xA81B6CE6DCD7F82AULL, 0x6208180145446BFFULL, 0x83A2FBA46AAFE295ULL, 
            0x1CDA7255451938DDULL, 0x4D9FB318363E4B89ULL, 0xEDD0FE9B9B25EF6BULL, 0x3E6351E1AD95C584ULL, 
            0x048AA1D216B840F9ULL, 0xC2F7382B4FFC869FULL, 0x014E547A63882397ULL, 0xB3913593BD4B3DB6ULL
        },
        {
            0x44D535F2BD196AB7ULL, 0xD40E5899EAE98ED2ULL, 0xBB2A7AB474EF92D7ULL, 0xA162AC81ADB0C248ULL, 
            0xBE0D8E6314644178ULL, 0xBFEC213DA8E92B51ULL, 0x6940C89C731A4B77ULL, 0x3FA2D0C4E2B01082ULL, 
            0x353F3F7095A38749ULL, 0x305D6B19F530A793ULL, 0xFAAC088B2AD7CC9FULL, 0x50603E2DFDC66169ULL, 
            0x26FE84017B5B13C9ULL, 0x67C76F9F8FF7FE16ULL, 0xED441DD447154909ULL, 0x9E215B26472EDAF1ULL, 
            0xA7C55620A15B952BULL, 0x9C14777C11B1031EULL, 0x0B06273C4AED71F4ULL, 0x549209FE1DB6A697ULL, 
            0x2E5891CD2A94F8F5ULL, 0x0F87391311304535ULL, 0x1DC42DC8E8D87DE9ULL, 0x4E11C7474E84916BULL, 
            0x216C36792164CBC7ULL, 0x6E8E0C1D83836A55ULL, 0x53F3E0501A306D51ULL, 0x872FFA8C056A607EULL, 
            0x9D221A0B3566B152ULL, 0xF2DF7BE726CDCD50ULL, 0x313A49992A189165ULL, 0xBBE1D9CDEF773F55ULL
        },
        {
            0xFD14F04D23BDB73CULL, 0x486A6FEA8E21DC81ULL, 0x4C247BAF9F115122ULL, 0x5D786EFCEDDC7A45ULL, 
            0x7E45920F30808604ULL, 0x5D6053C373B3E1F6ULL, 0xF9FBA45C17A62476ULL, 0x8D6628285224FC46ULL, 
            0x391A4ADCEC74ABE7ULL, 0x5FCC1DC58249D118ULL, 0x86B3CB596254A859ULL, 0x236633D11DD05F4EULL, 
            0x9B23CB9166855B9BULL, 0xCBFD1C0AA1891742ULL, 0xF71E7F66678656B5ULL, 0x5774109714B773E5ULL, 
            0xC1FA678D5614AC56ULL, 0x4944C81C44EA0EE1ULL, 0x6CC683300C7AD9BAULL, 0x8EC3C16091A970D3ULL, 
            0xA1238349BF2527FCULL, 0x968EDA526B36C096ULL, 0xC4663AF40A1009D5ULL, 0x3B01BE7F094D62C9ULL, 
            0x2560E45D63976815ULL, 0xA1EFBB4D78E600E9ULL, 0xC02239F80C72D23CULL, 0xBCBEC4482EF81A86ULL, 
            0x99D95E2650D91666ULL, 0x7B8830C1F127E1B5ULL, 0xD938627A134A3552ULL, 0x056BC250620A989AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseGConstants = {
    0x0AC6496BD183D710ULL,
    0x3788177B468234C0ULL,
    0x5840E2B453951182ULL,
    0x0AC6496BD183D710ULL,
    0x3788177B468234C0ULL,
    0x5840E2B453951182ULL,
    0x47B5E71FE3CFA450ULL,
    0x631330E12222952BULL,
    0x39,
    0x68,
    0x76,
    0x44,
    0x51,
    0xF5,
    0x9E,
    0x27
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseHSalts = {
    {
        {
            0xD81FCE902CAB678FULL, 0x0C231851F831FD4DULL, 0xF54DA5F4DA351131ULL, 0x4B8D84E56A404AE4ULL, 
            0xE32293074C588086ULL, 0x8385C9817DAE86F4ULL, 0xC2B8C54C34AD5B01ULL, 0x028865B5D8598306ULL, 
            0x12DEDE955D25EF05ULL, 0x6E2F948D545480AAULL, 0x95608EFF412000FBULL, 0x4DB427DA7CB03519ULL, 
            0x27E6290A7FB3C611ULL, 0xDCC0F9E19D7F0ED1ULL, 0xE3D09F440DDFA460ULL, 0xB9AD5C11888F1E86ULL, 
            0xABAE28C38672E06FULL, 0xF2523DBB7292BB5BULL, 0x355465FA9A6CC059ULL, 0x053EF3FD84041590ULL, 
            0xEE746D5DFB8C477CULL, 0x7E68BD326FB0C377ULL, 0x0BF76723C5AC11AFULL, 0x5742ED5B5EDC9099ULL, 
            0x4C6331573CFFED32ULL, 0x79AA43737BF312E5ULL, 0xB7CE146164D011C5ULL, 0x681753484940D9C9ULL, 
            0xA3AFC3933FAE343CULL, 0xE71D724ABCC1A0D6ULL, 0xD17C486245989930ULL, 0xB7890C9FC2EE2EB8ULL
        },
        {
            0x0E66865E95E6A954ULL, 0xBB74B7E176E7CC6AULL, 0x892711313AB958CFULL, 0x81A04C30AA418708ULL, 
            0x5939EDB5CC6A666AULL, 0x4000DEFE00F7B336ULL, 0xA7460D248651FC23ULL, 0x6409C4CE3B72DE9BULL, 
            0x6007D6BCFEF3A00DULL, 0x543410028A9F2774ULL, 0x5B90520C0401DCA4ULL, 0x762DD1FB4D8D7324ULL, 
            0x44D27743D82B413BULL, 0x01CE23C100B6DED5ULL, 0x839ECC9DBB0A3181ULL, 0x0B717FA356F7F297ULL, 
            0x0F2EAD173E8E5A0BULL, 0xA436DA452D47CEBCULL, 0x2F7FA74C7BD104B0ULL, 0xA316AD323FCCDDE1ULL, 
            0x96EF2B28CA009733ULL, 0xDE7A049AEE9A414BULL, 0xAAAEA9D6C4269CD3ULL, 0x9B76D91D2004A8AFULL, 
            0x1B21759DDF9165D6ULL, 0xF6979F387684C8B3ULL, 0x196A98BBBB847577ULL, 0x999BEDED70A22329ULL, 
            0xB710EFE533A6A2AEULL, 0x42BF662905AE2262ULL, 0xA40DA0432F999E6EULL, 0x43B585883D6AEE20ULL
        },
        {
            0xB9DC4BAE05DD7EDEULL, 0xEF850302A1B8F9CCULL, 0x88E6A16AF088B503ULL, 0x611839A5087C777BULL, 
            0x82F88FE252F5403FULL, 0x7BF85B8634D30FBCULL, 0xF8429829DD8A3903ULL, 0x4DF2D94A10D102BAULL, 
            0x151EDE016BBF16F1ULL, 0x588329A1A6A20722ULL, 0xBB5F29EE3B65B283ULL, 0x03D132860436A85CULL, 
            0xF3BF16A4A56DD194ULL, 0x399DD9B726FE83A3ULL, 0x5DB93C81C9000390ULL, 0xFA7B51C8843BDDE4ULL, 
            0x9FE88B6995F61A27ULL, 0xC7CB07A3823A4472ULL, 0xA5CB7E22E52E8CB4ULL, 0x04CE2BE8169E9F88ULL, 
            0x202F0E3393C3304FULL, 0x8B02272D06A860E5ULL, 0xD36C2B2327A45613ULL, 0x1FE591D511BE3448ULL, 
            0xC6A3F85A6DEB43D8ULL, 0xA581A611F2AC6311ULL, 0x267690F08E79BBEBULL, 0xC5EA04348B44AD77ULL, 
            0x0B9B35122F521F87ULL, 0xFA584342D5E88F77ULL, 0x159EA7D418912686ULL, 0xB8E5B69582A9A913ULL
        },
        {
            0xACB007EAF1958E86ULL, 0xD0966D93B6AE7311ULL, 0xB120E7E8E13CC9C7ULL, 0x8DAA4B1546BF7C5BULL, 
            0xE3D30A79AE746B47ULL, 0x3E96BDE51821FBB8ULL, 0x38279246AD5EB7E8ULL, 0x0BBC2BBEC977C454ULL, 
            0x68B3443F7C81B375ULL, 0xC70C3AB9CD9CFF28ULL, 0xE563065F0F03F5C9ULL, 0x6E8F301AFA5C3F0BULL, 
            0x9ABC28BA0376E801ULL, 0x471DB4441BE9BA0BULL, 0x2EEAD3379957B15CULL, 0x10D2656BC5E007B0ULL, 
            0x96052FB350C10C9DULL, 0x64618055ED15431CULL, 0xF43D1914CC12B389ULL, 0xED2E0C8F874F039BULL, 
            0x8213E577993251FBULL, 0xE8E9849EA0993DA8ULL, 0xFFC297CE525B76EEULL, 0x2D7D728574E37CECULL, 
            0x1C28C64BA7F339D8ULL, 0xB162B7DDF62BA0FCULL, 0xF43E72B39AAF6AEEULL, 0xC3AF0C28EC97518CULL, 
            0x523FB7DD57E62DABULL, 0x23E9A254ED5DAD48ULL, 0xC493172F9F0A8C04ULL, 0x3B3277B103891A91ULL
        },
        {
            0x5B490805A85CDC19ULL, 0x92268259991CB0C8ULL, 0x61B99FA5900FB64FULL, 0xB8B49CC559F7586EULL, 
            0x01F65E202F47311FULL, 0x17ED498D9FA53E74ULL, 0xF5A3AF56BEDB5123ULL, 0x06E386E621C281AAULL, 
            0x2BF4FDFCBF80A043ULL, 0xCDFA837CAB494047ULL, 0x1FABDAFB5BDBC20CULL, 0x5F84FCFB3D7E13E9ULL, 
            0xC8A79F1539C449EAULL, 0xF605505D5216407BULL, 0x4B157D20CF54E0CDULL, 0x189F9B916E2491BCULL, 
            0xF300C8B3312A955BULL, 0x7B84ACDFD876910FULL, 0x6C93470781F9F1BBULL, 0xAE677304FD394A31ULL, 
            0x6AFBC42F5AD757A2ULL, 0x700E4A51427BE8D2ULL, 0xAC3C25405AF6F1CDULL, 0x199D5B334CF1F4D8ULL, 
            0x785B84BC440249CEULL, 0x2161BF4AD7392D12ULL, 0xFBA62145E57E3C2AULL, 0xDC08ED7DE934C557ULL, 
            0xA5FE081670D530A2ULL, 0xA552E994B0965AB0ULL, 0x696B8E419B906150ULL, 0xA8D50A72CA1BC3DEULL
        },
        {
            0x6835EF75845339CAULL, 0x63036238F4D74FF6ULL, 0x6237146BAC427A8FULL, 0xF708A286E73560CFULL, 
            0xAC970998EDC95518ULL, 0x81040A9C9B0D1197ULL, 0xEDB389C1C672F637ULL, 0x4826FC2A40FA5E4CULL, 
            0x3CAC8879AD1E0C3DULL, 0xC1741ED258C6D7B7ULL, 0xB89161302D805ECEULL, 0x8E00770CEF737A4EULL, 
            0xAE4D5986923D1EE0ULL, 0x2F5D5CB3A2D02AC3ULL, 0x71B9A30C1DC4EB8DULL, 0xFBF16B664D968EBDULL, 
            0x1A3E868E64F49CB4ULL, 0xF94568F29D5AF0F6ULL, 0xF33A6E6BBF1505E0ULL, 0x2D1FBEC990C3DF24ULL, 
            0x9FE1E8E92DDB7EE6ULL, 0xE3DC9D5E70DFA2B3ULL, 0xFA7455FB7BAD8892ULL, 0x7EE046E1F8A060CBULL, 
            0x7811C5301B3A8878ULL, 0x705B7DA18AA7B77CULL, 0xAC47E727252FAF4CULL, 0xEF3962D25C0F09E4ULL, 
            0x65C10C75F9D0B88AULL, 0xF94E7DF587334928ULL, 0xF0088E4472D78FB3ULL, 0x919B77FFE5A256EDULL
        }
    },
    {
        {
            0x6695D7BE8A6A41CDULL, 0x537E8E5B224D8099ULL, 0xF4CCF240A2DE21F1ULL, 0x470003D547784B98ULL, 
            0xEB26F063CD6B2C76ULL, 0x37774B638E8EFFE3ULL, 0xA48B32449A0AC0F3ULL, 0x3ED2F18D9672FEBFULL, 
            0xBA38740DF329409CULL, 0xB9CD1AFC47635683ULL, 0x2345A5D5D34431D4ULL, 0x22F96F155D19BCA5ULL, 
            0xF8004DD75CC93B8DULL, 0xE481D289B55FACA0ULL, 0xBCA0215508709F6FULL, 0xB013DFBE5331447CULL, 
            0x92C5F9A0EA05EBADULL, 0x3E59B3F182ECAF05ULL, 0x62C2FA937EA61E12ULL, 0x7621B0CE48DE8840ULL, 
            0x233023951704142AULL, 0x98CC94569BF7D4E8ULL, 0xD0C33D691353E08FULL, 0x8C715C6AC851BD2CULL, 
            0x4CA1E93DB8A27DEDULL, 0xF83602FF887B0848ULL, 0xBCD8CB7C462B3D75ULL, 0x9EA44EF2BC590C9CULL, 
            0xA9EE30E8DD909641ULL, 0x720E7E70A13935BEULL, 0x5E1E237FF60F5F7AULL, 0x5D524E6A46489643ULL
        },
        {
            0xF4AD458C278F0337ULL, 0xC3633063A28BD11DULL, 0x450E1DE6A80D4AD2ULL, 0x799CC12A87A685A5ULL, 
            0xA4A60875868F3A66ULL, 0xFB9989F2EDC60180ULL, 0x1BFF793371E3B354ULL, 0x3CC9F7E6C563B1D8ULL, 
            0x2BDE85C5F501E162ULL, 0x30143A4103D6F484ULL, 0x0B13E65CFEFBEDA3ULL, 0x465F65FC992C1D66ULL, 
            0x7A72B35F11A77D6EULL, 0xEFF9D5AD58825087ULL, 0x894DF32D046D06CDULL, 0x6835440C035DE70FULL, 
            0xA0BD2B50532B69AEULL, 0x7262965F7DE4B8CFULL, 0x8D0F26E89F36398AULL, 0x79ADCCC354490119ULL, 
            0x0C4CEF9DA8C49A17ULL, 0x8B34E1F5444532EEULL, 0x349471CAE44E72ACULL, 0x1045AB939A3B6C36ULL, 
            0x25ED16694EBD97DCULL, 0x0A0BA9C943FFB175ULL, 0xA073AE4EA6EAB03BULL, 0xFBA3359604DA33DBULL, 
            0xF67A3C4191F62099ULL, 0x94A5C024A01D800FULL, 0xC86AB09D51E8A49BULL, 0x648CBA84CF18DDB6ULL
        },
        {
            0x60BABCA3E1ED26F6ULL, 0xCB7FA174450EB4CBULL, 0x9C23C201A1DD2AEBULL, 0xA985494F492EB08FULL, 
            0x44D04B711218509DULL, 0xB9A60FB657A90D95ULL, 0x6A74943782A3A231ULL, 0xDB348A96D10FE8BFULL, 
            0x25782598FCE88275ULL, 0x3273AFCBFF76AEA8ULL, 0x4A952398C21FABDDULL, 0xD4893D6E6E576237ULL, 
            0x4AB2384CB16E6666ULL, 0x9B05361A9191C117ULL, 0xE367166C3D7A4D33ULL, 0xDD3A302300C09AE8ULL, 
            0x859C06145877C23CULL, 0x4B6049F885565BC1ULL, 0x1DEBEC98BAA438C0ULL, 0x8D9AD6801B84C357ULL, 
            0x0BC7E1DA66244A37ULL, 0xB2A90CB9ECC32D88ULL, 0xD98E6835BDEF986CULL, 0x72983204F26DA6C4ULL, 
            0x7BB2A16798C3D9DFULL, 0x4CD396924F0FE6E8ULL, 0xCD9CA1BF82A52830ULL, 0x1448ADE3E0E8C7F6ULL, 
            0x4ADDF73E87292D52ULL, 0x05D34ACF4D9386A3ULL, 0x0FFE45B91CCA057EULL, 0x588265C32B1A8AE7ULL
        },
        {
            0x93BB535121DD570BULL, 0x78CDDEDFA7666023ULL, 0x07A59AA5C5F27AE7ULL, 0xD1033B69B3257BE4ULL, 
            0x4D55D64DF27C71F9ULL, 0x66BEEF9E67004ED8ULL, 0x238F420FFDC3FF29ULL, 0x84A48E14EEBA82C8ULL, 
            0x5B6E2CBAE38F7447ULL, 0xB4A75C7BA045B6F4ULL, 0xF3870ABE6E4704D1ULL, 0xB05DBCDBCDB70314ULL, 
            0x6682F2B2BE249583ULL, 0x0606D6F024A670E3ULL, 0x0C3554B58F161EFDULL, 0xB4632279CB3FECCCULL, 
            0xEDF65D2586E96FC4ULL, 0x0F1ECAF327ED527BULL, 0x09AFDF3ECD8AFEE5ULL, 0x743E48973560BD60ULL, 
            0x31C99135786348A9ULL, 0x2B38FB903E59DAB9ULL, 0x475E40BD9BC8F4D5ULL, 0xE91591F66C12871FULL, 
            0x58950324ED082F6CULL, 0x1B4382CB694AD0D5ULL, 0x66017A1CAFA8EF35ULL, 0x7F7F78C01BAE758EULL, 
            0xC4576C100C86A70FULL, 0x30141275C9631295ULL, 0x84612A771FEFD446ULL, 0x59E561DAB4B2263BULL
        },
        {
            0x4F49CFE716CE1AA7ULL, 0x19827928C45E956BULL, 0x2B53505703C8759DULL, 0x6AEC35FB0909AA70ULL, 
            0xD1CAC09B370D37D8ULL, 0xF1C7E96B4D69C97FULL, 0x3308D9637905251CULL, 0xF74E011C5F46F77EULL, 
            0x52C28FDAFF3D4D98ULL, 0xAD5FF998353AAF47ULL, 0x01C013AF12B06C99ULL, 0x3E82D83B048753FEULL, 
            0x72027A4F1C5A7040ULL, 0xC14A4232CDAF234FULL, 0xF5423AFBE9387ADEULL, 0x17D9C460B4ADC15BULL, 
            0x6C646D03F8159683ULL, 0x0598AF1EEF0C39A1ULL, 0x31C648EBF66FBF4DULL, 0x8A1801BDF446F26FULL, 
            0xFDDBBB22FA84AECAULL, 0x8FC792040EA73C4FULL, 0x9551CBA6FC74261AULL, 0x4EF5AA8831E10AB5ULL, 
            0xB305FA5B0A59EC63ULL, 0x8DDBA547BBF0FA8BULL, 0xF5B6874A1389A96AULL, 0x115CD910325D4C54ULL, 
            0xDEBE95FEF1FFF75BULL, 0xF5C7624A53BB4FE5ULL, 0xE434881325EB410CULL, 0xA3862B417F4BC2D6ULL
        },
        {
            0xB586F3CA24382877ULL, 0x77FCF7C5AEA17858ULL, 0x2724A5DA32173FABULL, 0x54FCDF4202B9F2D7ULL, 
            0x442E9134B6D316B5ULL, 0x6563A212E3B8AB0FULL, 0xAED542E5FDEA0F2CULL, 0x0354979CB9FBED70ULL, 
            0x76D58D399F101F10ULL, 0x5A80D4848EEA0A62ULL, 0xA3646E0162E74522ULL, 0x027BA4B889436B71ULL, 
            0x8A45A98F545B3781ULL, 0x619AEC7B11AA9F08ULL, 0xEC466848EE300253ULL, 0x29BA352300CE5E56ULL, 
            0x3ACCC39F5526766FULL, 0x8EDD48777B805398ULL, 0x7447EC8687B308E9ULL, 0xFD75819C9BCAC319ULL, 
            0x48C73C95EDC2E008ULL, 0x70A1D4FE05FDE975ULL, 0xFFD95E121E88B357ULL, 0x569CF77C8FAC95D0ULL, 
            0x5EA3E64A50A245FAULL, 0x90E50236F2F7A452ULL, 0x81E76FEF63741108ULL, 0x28B0440DF69D8541ULL, 
            0xA8535A1CE2D4CCBBULL, 0xEF83DA59183D1DB0ULL, 0x3EE5C57BBED8E3EEULL, 0x3779D55866CDEF65ULL
        }
    },
    {
        {
            0xAE4811372D547B32ULL, 0x84059E5171E1259AULL, 0xE7F4B9F20D20F8B2ULL, 0x532E4E482E63A494ULL, 
            0x0A9DDFF3CB515904ULL, 0xEA1A55D3493186E3ULL, 0x2D1BDC64F186AF4FULL, 0xA9A9F4DC671BF2D3ULL, 
            0x8208BEBE72D7D9FCULL, 0x0E95B796371C1AC2ULL, 0x2960020EB5789576ULL, 0x19560E415619C78AULL, 
            0x18E39D074F8B54ACULL, 0x4653297A79B74A9FULL, 0x20E7A2B70697455CULL, 0x055EE76DED85C6ACULL, 
            0x62408849A08FF06DULL, 0x215106ED9D9D82FAULL, 0x7AA426406E928488ULL, 0x665A08120E6E6B87ULL, 
            0x0D8BE11A95DBEE4DULL, 0xEE5603471BC11D67ULL, 0x3EC8AF6A58D72DB1ULL, 0x3BC576C69493C3AEULL, 
            0xA0D7C70524219446ULL, 0x9D54E05016B8872FULL, 0x8F47652ED44F7571ULL, 0x8AC8ADFCAB9FDD90ULL, 
            0xAF4D53533A836C8CULL, 0x7FE10BFC68F7AF23ULL, 0x69D3388595A85648ULL, 0x9173BBF75162210FULL
        },
        {
            0x2DDBE219EA90125CULL, 0xE64C243947FB8897ULL, 0x6D3C1FD9BA0ED6D3ULL, 0x7891B8A0F26E4289ULL, 
            0x4C814E78DB35E038ULL, 0x945C2FC99E172E7EULL, 0x88D808971B35BFD4ULL, 0x05C5E329A7E54BC1ULL, 
            0xC21AAF750D4B4580ULL, 0x89725C6E91FF02AEULL, 0x9E1A99573CB4C93CULL, 0x18119D3E6F054AE4ULL, 
            0xCA3D81B624EB4937ULL, 0x422B74DB4D9B54D8ULL, 0x4B964B3D1AD43C1CULL, 0xFE59A314417D8AF2ULL, 
            0x1AD10F262A635B40ULL, 0x51CA79A7A807AAFCULL, 0x0FEF592E310A4CB3ULL, 0x923A464127C14C9EULL, 
            0xD03B401C1D9C53E0ULL, 0x1CE37797AF37506CULL, 0x19A95AD802C5BC94ULL, 0x4B1070B3FDFD4C41ULL, 
            0x60179F4389C362B6ULL, 0x4CB4412764E323CEULL, 0x77B6ABA9F323DFDBULL, 0x4E3ADA7B77E9A805ULL, 
            0x94F227FB76949194ULL, 0xBB16C8903E14ED8FULL, 0x7973CC5E8CC77E79ULL, 0xB54AF7F75F6FD79AULL
        },
        {
            0xC88F1567DC80C355ULL, 0xB908FB08BD4CA504ULL, 0x91EAD04869E60825ULL, 0x3F6D8F47864BD2E7ULL, 
            0x4F9B9D95B94201C4ULL, 0xE4FE4852E1A83DBAULL, 0x911D3D4292F2B4A5ULL, 0x521782A1BD33E28DULL, 
            0x74C15BFA883403C7ULL, 0xCB217024F40A1749ULL, 0xE2348C80B86DD902ULL, 0x9C1560D272BAA460ULL, 
            0x11C7B26C49A86F0AULL, 0x829DA4E56FD50721ULL, 0x00BF231767A51879ULL, 0xB2EC41441B38BB17ULL, 
            0x6D6C963FA329ABC4ULL, 0x493A53FA97E912F1ULL, 0x2693C46C380D7AABULL, 0xED0F4D7A93FB98D3ULL, 
            0x018E5521B041F13EULL, 0x3844A352596823FDULL, 0x517C0EFCD46EA3B9ULL, 0x2BC383D901F326EAULL, 
            0x3BCFFCF9C9E5DF84ULL, 0x0EA16EE548434CD5ULL, 0x016E4B9D9C67D1F2ULL, 0x9D4EF35B29927CFFULL, 
            0x37C69A3CCB3D408EULL, 0x23F8937E4248910CULL, 0x5F7FEB08A8FF6EAAULL, 0xF3469B2E5BAE299CULL
        },
        {
            0xE1249AC1F5C84F5CULL, 0xF6E0008DE57B9A1EULL, 0xFE66F16ABC9F56DFULL, 0xD853853BFB479DA1ULL, 
            0xFB87C901742BBB7DULL, 0xDD240012F790601EULL, 0xE5F74738173EC14CULL, 0xBB0C899EC41990CFULL, 
            0x14FBDAD58CA3952AULL, 0x1CCD540FB1B69BC7ULL, 0x689E6387C0C17094ULL, 0x2CA34CA9DB442279ULL, 
            0x72F9891374D2E9C7ULL, 0xB41FA759D66997A5ULL, 0x1E9CB7815DF36BD8ULL, 0x097B8E2D1BC84505ULL, 
            0x1D96BDF14B6D7BCAULL, 0xEF0E6941234FC5E6ULL, 0x2A5A43F3F120B41DULL, 0xED32BAEFDA0226D7ULL, 
            0xCADCB33DE998FEC6ULL, 0xE1ADC7A974C47161ULL, 0xD93D8A22D88858B3ULL, 0xCDEA5B94A1A3FB12ULL, 
            0xE9613B16E097E440ULL, 0x665945FEF977DF49ULL, 0x10FD31ABE288792CULL, 0xB6A8E2EF6C58BBBDULL, 
            0xAF27F6989A4CFFBAULL, 0xEB2C134DD8315FCCULL, 0x2CD77721D8E109BFULL, 0x5EF81A0380B2D5DEULL
        },
        {
            0xEEF796E4DD1FFCDBULL, 0x251EC857F94DF347ULL, 0xDBE4EDE1E17E7878ULL, 0x9528F6803DF96027ULL, 
            0x4FE06A965F8E3B3EULL, 0x9154CF38E7A40F3DULL, 0x870B9FFFDB40CB9DULL, 0x24096295D18B533CULL, 
            0x5AE9D123A320D34AULL, 0x1DD2568AAAFC75EBULL, 0x05666F7288B2CA59ULL, 0x8E9FF19B816913E4ULL, 
            0x05BE382A6EA1D441ULL, 0x8783EA7AD9E40AD8ULL, 0x2BFD3B35E8E36397ULL, 0xD13AE0AFD9C0699FULL, 
            0x4341D136EFF33771ULL, 0xE8ADB88ACD7E4940ULL, 0x6A443883B9387571ULL, 0x4DEF6B788729621EULL, 
            0x4E5547F40D1CF5BDULL, 0xA84999B16795BEA7ULL, 0xB6C6CD7379B6744BULL, 0x879BB0BFD9AD4211ULL, 
            0x4C3EB6B3C17E95CFULL, 0x829777D507C24F5AULL, 0xDB7C4E6468494BEEULL, 0xB282896DB74FD048ULL, 
            0xAD918B7554F4207AULL, 0x8F078927350E8189ULL, 0xD91BFE94F9E77B1AULL, 0xF680B97936832293ULL
        },
        {
            0xE94534ACC0FA442BULL, 0xB9B5BB52A9808721ULL, 0x542C0CDC04A8E75FULL, 0x8763D08175ADF360ULL, 
            0xA710D9ECAF076A26ULL, 0xB84021A8B9A45392ULL, 0x97FBBEA2C689BD82ULL, 0x3F2596462F867417ULL, 
            0xF90191B547653699ULL, 0xB80CB47DC5E2380CULL, 0x739DD4EA1A80D04DULL, 0x814D03547D42430EULL, 
            0x0731A79B589EDCFDULL, 0x7AD713A38F06D3C4ULL, 0x4590BC129B5D65BAULL, 0xF4D23B0BC3C2D53BULL, 
            0xA3AA62DA9022CCCDULL, 0x57DD5BF45BD71F58ULL, 0x2651865E55F86858ULL, 0xC2EB097DCCD26A67ULL, 
            0x84327A2FEB1BCF53ULL, 0xE09AA94A3375E11DULL, 0xBB1A140A09CF98C7ULL, 0x5D4252D384AE619BULL, 
            0xEFC3101C22961E7FULL, 0xB418F9BA53FAEA20ULL, 0xAD65D4F709ADEE25ULL, 0x0B66D36344EF0D18ULL, 
            0xF7AAC73A0BC33A0AULL, 0x3C561F3D2A7FA76DULL, 0xC5128690AEA0471FULL, 0x1686C9D2CFAB7B36ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseHConstants = {
    0xF663620D263DEAF4ULL,
    0x34064B4C7E937A46ULL,
    0xC6A598F0A3D9C099ULL,
    0xF663620D263DEAF4ULL,
    0x34064B4C7E937A46ULL,
    0xC6A598F0A3D9C099ULL,
    0x31815EE3C9C0F766ULL,
    0x4EA847062940A8E5ULL,
    0x57,
    0xD3,
    0x8B,
    0x6A,
    0x30,
    0xC3,
    0x55,
    0x83
};

