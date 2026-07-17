#include "TwistExpander_Betelgeuse.hpp"
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

TwistExpander_Betelgeuse::TwistExpander_Betelgeuse()
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

void TwistExpander_Betelgeuse::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB7150EF7F32AD434ULL; std::uint64_t aIngress = 0xF51AE99487D12FD6ULL; std::uint64_t aCarry = 0xE41EB3387A57F66EULL;

    std::uint64_t aWandererA = 0xCF43026B78F7EB2BULL; std::uint64_t aWandererB = 0xC91AA462C597B895ULL; std::uint64_t aWandererC = 0xB931B4D2569124F3ULL; std::uint64_t aWandererD = 0xB81F4F90DB6BCA4CULL;
    std::uint64_t aWandererE = 0x87DA8098C95B5B65ULL; std::uint64_t aWandererF = 0xF016093D7DD7258BULL; std::uint64_t aWandererG = 0xA32A8D3FA60EDCB1ULL; std::uint64_t aWandererH = 0xACF7333F720C4914ULL;
    std::uint64_t aWandererI = 0xE453615F3E469647ULL; std::uint64_t aWandererJ = 0xD3AF5EDB4B6452EBULL; std::uint64_t aWandererK = 0x8BF9518A167FCD2DULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17942174884831704651U;
        aCarry = 9771795075234552191U;
        aWandererA = 15886659163245544994U;
        aWandererB = 17481171575730291496U;
        aWandererC = 14216852435784733274U;
        aWandererD = 9910019059476739757U;
        aWandererE = 14716004405115554778U;
        aWandererF = 11525273169749148561U;
        aWandererG = 14686697354014341318U;
        aWandererH = 16375269966089699104U;
        aWandererI = 15884491866800030856U;
        aWandererJ = 13397840949949167192U;
        aWandererK = 9404149283175971544U;
    TwistExpander_Betelgeuse_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Betelgeuse::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD96DCC667A1DB07EULL; std::uint64_t aIngress = 0xBFBC7C6728CAC64EULL; std::uint64_t aCarry = 0xAAD0AF971EEAC745ULL;

    std::uint64_t aWandererA = 0xB3E7CE7E95B7C35CULL; std::uint64_t aWandererB = 0xD368EACC8BAA4404ULL; std::uint64_t aWandererC = 0xF384781101D29325ULL; std::uint64_t aWandererD = 0xDE3814018305F723ULL;
    std::uint64_t aWandererE = 0xF2033AD1A4954165ULL; std::uint64_t aWandererF = 0x9F8902EAE4EB3BF0ULL; std::uint64_t aWandererG = 0xF41A1E1397B67E22ULL; std::uint64_t aWandererH = 0xED9BA0389C8F36E5ULL;
    std::uint64_t aWandererI = 0x81B572452CB3F1D4ULL; std::uint64_t aWandererJ = 0xEA99C25883024C8AULL; std::uint64_t aWandererK = 0x92F5D477A71FB4C2ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10478043857116018771U;
        aCarry = 15921640471544989510U;
        aWandererA = 16722193491235259897U;
        aWandererB = 9269318711939104998U;
        aWandererC = 16318335564461336198U;
        aWandererD = 10927914410560624973U;
        aWandererE = 13102879021396975118U;
        aWandererF = 14652997954085723133U;
        aWandererG = 9304052692221824440U;
        aWandererH = 11969444441991725869U;
        aWandererI = 9603155708809640167U;
        aWandererJ = 9914732208854811727U;
        aWandererK = 15291364471536674144U;
    TwistExpander_Betelgeuse_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Betelgeuse::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC21DAE3408F8FCE6ULL;
    std::uint64_t aIngress = 0xF21EE43597AB5352ULL;
    std::uint64_t aCarry = 0x8C3193A1E6FA4F33ULL;

    std::uint64_t aWandererA = 0xE87F86B273791557ULL;
    std::uint64_t aWandererB = 0xB383026C98154E53ULL;
    std::uint64_t aWandererC = 0xA683ED5C8C3A1199ULL;
    std::uint64_t aWandererD = 0xCEF9FBBBDB65A128ULL;
    std::uint64_t aWandererE = 0x8076EF2A33013507ULL;
    std::uint64_t aWandererF = 0xC7893E4E9E83B158ULL;
    std::uint64_t aWandererG = 0x96258075763E0D29ULL;
    std::uint64_t aWandererH = 0xC3F64466D750B72DULL;
    std::uint64_t aWandererI = 0x9B4C8007A0BBCE8FULL;
    std::uint64_t aWandererJ = 0xF217214B90301EA4ULL;
    std::uint64_t aWandererK = 0xB88E09DE500860B1ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneA, 0);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneA, 4);
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
    TwistExpander_Betelgeuse_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Betelgeuse_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 13 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1848 / 1984 (93.15%)
// Total distance from earlier candidates: 22325
void TwistExpander_Betelgeuse::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 224U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 389U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1293U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1387U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2004U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1468U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 779U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1147U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 933U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 216U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 946U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1460U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1359U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1076U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 435U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1530U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1184U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1171U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 694U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1291U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 254U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 911U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1255U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1085U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1539U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 440U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1341U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1212U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1685U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1149U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1664U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1657U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 533U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 365U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 820U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 904U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1801U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 184U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1944U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1683U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1496U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1403U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 928U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1057U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1879U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1516U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 702U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1096U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 330U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1098U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1691U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1216U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1529U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 876U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1286U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1367U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1312U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 616U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 203U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 991U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1617U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1511U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 485U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1144U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1253U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 296U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 654U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1753U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1854U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1773U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 864U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1886U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1636U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1481U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1718U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1522U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 370U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 922U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1898U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 602U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1289U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 98U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1065U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 579U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1775U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 631U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 10U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1418U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 682U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 448U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1159U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 338U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 739U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 686U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1447U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1090U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1207U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 905U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 691U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1844U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1661U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 327U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 670U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 62U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1158U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2024U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 968U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2008U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1220U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1276U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 996U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 50U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1926U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 517U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2018U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1150U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 797U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1693U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 751U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 273U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 320U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 182U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 695U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1443U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 364U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 218U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 324U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1770U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Betelgeuse::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE7D7D55CD75DA8F6ULL; std::uint64_t aIngress = 0x8154E92DC67FB16BULL; std::uint64_t aCarry = 0xAB46D8C81F1761E6ULL;

    std::uint64_t aWandererA = 0xEB8BC16DFFC2760CULL; std::uint64_t aWandererB = 0x8BF1CE63882CDA6DULL; std::uint64_t aWandererC = 0xD8585B8C9F604B10ULL; std::uint64_t aWandererD = 0xD8D62F9556CA1CF9ULL;
    std::uint64_t aWandererE = 0xA88032E769EE81C4ULL; std::uint64_t aWandererF = 0x9F5C31574E3D1A43ULL; std::uint64_t aWandererG = 0xEF051834695FA918ULL; std::uint64_t aWandererH = 0xCB4100B22047284EULL;
    std::uint64_t aWandererI = 0xD6A220EA8D420DD8ULL; std::uint64_t aWandererJ = 0xD1089A6F10A23048ULL; std::uint64_t aWandererK = 0xD3336F2CDD8E842FULL;

    // [seed]
        aPrevious = 10514095968244867940U;
        aCarry = 13474576829858782819U;
        aWandererA = 15691969466046252409U;
        aWandererB = 13839491968149289478U;
        aWandererC = 17293252535268257667U;
        aWandererD = 15969454476943385717U;
        aWandererE = 14901040138512273945U;
        aWandererF = 15552805672741879039U;
        aWandererG = 16851907180983605421U;
        aWandererH = 18183891541708326601U;
        aWandererI = 9692170670745328500U;
        aWandererJ = 11859698988603929555U;
        aWandererK = 14296696558393651238U;
    TwistExpander_Betelgeuse_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Betelgeuse_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 13 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 6596; nearest pair: 470 / 674
void TwistExpander_Betelgeuse::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3156U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 293U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3586U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3088U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2975U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2955U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3388U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2198U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7666U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2080U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1151U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4974U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2521U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5233U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5997U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7973U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1911U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 231U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 874U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 364U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 880U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 463U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1719U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 777U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 954U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 346U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1534U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 551U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 988U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 870U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 677U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 256U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 122U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1820U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 412U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 204U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 13 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 6600; nearest pair: 505 / 674
void TwistExpander_Betelgeuse::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3042U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1609U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3179U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 527U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2561U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6017U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4715U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 44U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2903U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6912U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 642U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2934U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2090U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4474U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4965U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2523U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1536U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 918U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1143U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1642U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 192U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 606U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 17U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1230U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1914U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 204U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 264U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1543U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1484U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2001U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1558U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1931U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1571U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1138U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 558U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1394U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseASalts = {
    {
        {
            0xC2FA932AE1E3C68FULL, 0x12766D729DB116A8ULL, 0x7A01466BD796124DULL, 0x58991A0540681254ULL, 
            0xB36FF222AE10AC3DULL, 0xF5413A6614971CE5ULL, 0x2F272F253797BAB5ULL, 0x4B4AF4D0D89E5C20ULL, 
            0x3B8EBDE1300A41E9ULL, 0xDBA3003BB3AC7BB6ULL, 0xE4415020E24048F8ULL, 0x1B313A62098FBC31ULL, 
            0x3029F1ACED1EC198ULL, 0x1F07EE3981804A0BULL, 0x0AEC9209A3B27226ULL, 0x0307DE484FC40E91ULL, 
            0x721891D70D17E147ULL, 0xEE9BA4E70DB471F3ULL, 0x4F4E08DBA93D158CULL, 0x22BD7DE62E326A35ULL, 
            0x13500048AE6A442EULL, 0xB83ACEBA9993512CULL, 0x9C8693F44A441790ULL, 0xA928638B94ED9617ULL, 
            0xFDC7B95720B7262FULL, 0xA3C13FABAE9C02FDULL, 0x99DD03BDD6293FF8ULL, 0x6A872873182AA38EULL, 
            0x4518C71121BBB0CFULL, 0xA731C3C45E1D7B8FULL, 0xF70CD9DA19AC433AULL, 0xE53FA40CB05DC4B5ULL
        },
        {
            0xB81428D3A0E71CB9ULL, 0x0F36925C0910221FULL, 0x1B6C8E68559A6A7AULL, 0x489CEA10AA11137CULL, 
            0xA3440EB9455C28CEULL, 0xBDC290915FF68B0EULL, 0x5887F7DE215905F9ULL, 0x2AF07E3D715D0BFBULL, 
            0x502F5DA6C7F5503EULL, 0xAF1FFF8D6BC0594EULL, 0x155548008D6AFC0FULL, 0x994B0154B0065664ULL, 
            0x3B69FBB5F6CB72BAULL, 0xDC305ED7AA308582ULL, 0x171D714CE2F1CC66ULL, 0x72015B77CB33A39FULL, 
            0x464434463BDEE42EULL, 0x8CCAA30999A9A11BULL, 0x303A3B894E54969AULL, 0x93B70233C8C5566CULL, 
            0x5D38F9DAEB7C8C54ULL, 0x8743CCA85BC635ADULL, 0xC847DF85470F89C3ULL, 0xA012392BE53E7B0DULL, 
            0x89A3B1814E9586F3ULL, 0xF50C4CB7E00990E9ULL, 0x6ED38C507BD2586DULL, 0xCFB6FAC58764A412ULL, 
            0x3C6CC99A4D8BB22CULL, 0x8C8DB559B4673C81ULL, 0x0BC29213300E0E61ULL, 0xE267E62778E77A04ULL
        },
        {
            0xD4B0C8C122BE42CBULL, 0x6A0B3D23CC4EB407ULL, 0x1D19EE85903227A4ULL, 0x75A75B1239DFE124ULL, 
            0xAB156D4B18738395ULL, 0x5085F9961AC6D716ULL, 0xA23C8CBC0AB9CFF9ULL, 0x0101492141AAE618ULL, 
            0xC3C1FB774304E673ULL, 0x660165AE25281E50ULL, 0xA1EC905029409584ULL, 0x54F88BCEE2A29719ULL, 
            0x722577B17026F96BULL, 0xF3CBB64EC479AD8AULL, 0xEE598AED2B04D1A8ULL, 0xE77D08C863BC3A2EULL, 
            0x00EC6FD79DB1E63FULL, 0x4957258EEE29FF04ULL, 0xD983933D8AE4363EULL, 0x172B5ED16925A588ULL, 
            0x676111BD19BD7AB2ULL, 0x783F46957B9FE941ULL, 0x60484E9037DA52D2ULL, 0xE6624636E4808335ULL, 
            0x4B1AD1B56E2A94D3ULL, 0xA3C642EFE94285DEULL, 0x0FA168196A36834BULL, 0xC0EDC3479885247DULL, 
            0xA27F61EA71063215ULL, 0x38D7ADBE26E9C653ULL, 0xA6744018F8351380ULL, 0x458F0FCB24928A22ULL
        },
        {
            0xFFB3253DCD457BD8ULL, 0x23A6065F09B45E94ULL, 0x62DF2ADCCE8C285FULL, 0x1D9F2BACFCE1908AULL, 
            0xEF50FD9B030855F5ULL, 0xA734A89136D3A69AULL, 0xB01BC9842397764DULL, 0x485F3D413510B458ULL, 
            0x3FA274DF9ECA096FULL, 0xFB0E3C2E59D9D505ULL, 0x2FEE1CCC94498163ULL, 0x7ED410E82B66C8D6ULL, 
            0x7463888C46838018ULL, 0x48538C874D5A7C7BULL, 0x79EB67EDF321FA95ULL, 0xE225337BFFB937F0ULL, 
            0x6048533B0C73EDC7ULL, 0x629162C2FDE23FF0ULL, 0x27A3A144EE156A3EULL, 0xF73B8BAAC22A321EULL, 
            0xBB3D12EDD898969EULL, 0x24E1DDD4448DEB44ULL, 0xE3C44FCD30753158ULL, 0x79ED0BA6EC225384ULL, 
            0x54110E743737298BULL, 0xA6CC7BE3B0033C96ULL, 0x83BC801560D73E9AULL, 0xE113109226E47B1DULL, 
            0x1DE80ADC98AB5259ULL, 0x429BC131AD7FA422ULL, 0xDB95926E1B0DA4E0ULL, 0xB4627DDD21601FFAULL
        },
        {
            0x7AF74397AE834151ULL, 0x2608AD36D48761B2ULL, 0xC390612E087121BEULL, 0x54B9A7F145F1F1B0ULL, 
            0x4EF386E8787D5D88ULL, 0x6A97E75017DA10E5ULL, 0x7602AE849A32F1F1ULL, 0x84F1B4E5107F3ED2ULL, 
            0x50AE90C13B33FAF9ULL, 0xBAF74C7FD2E8208BULL, 0x4A3FFF8F2DC33F9EULL, 0xD0ACA602DAB88DC7ULL, 
            0xE12B33731706CD7DULL, 0x344C0ECF773987AEULL, 0x1172AAD37B25BFA7ULL, 0x3AF5D84C21A6B5F4ULL, 
            0x4510066DD280D774ULL, 0x2A2E5AA2551E6F5AULL, 0x6D15231B1BC4C393ULL, 0xE98961B6C0DDC5FDULL, 
            0xF80EAC6E0EF7143BULL, 0x970C3668CD122287ULL, 0xD4578E4B94AB9461ULL, 0x9F23D78646DBBB9FULL, 
            0x7764DB0A707FB179ULL, 0xE22E3D528C44A67FULL, 0xDF4B099879CDA386ULL, 0x30928BB7FA3187A4ULL, 
            0x427BCAF33C34A5E7ULL, 0xA4EC1634920E6D22ULL, 0x6DD852558A7E8F0BULL, 0x672EC305FC4122C3ULL
        },
        {
            0x3F5CB8220823A03BULL, 0x60E89EE2E195DD84ULL, 0x7937EB11F9C3F47EULL, 0x21D312B1C716CEC4ULL, 
            0x5943011F3D1DFED0ULL, 0xAAADD7C381815B00ULL, 0x5061F369A1AD29BCULL, 0x83B2EA26220A5430ULL, 
            0xF536DC079023D3B0ULL, 0x4D69239B56BC286FULL, 0x17DDDDAA52BF0010ULL, 0x96E82C2371C4E8B5ULL, 
            0x85CFDFF1FA1395E2ULL, 0xCA30AFC3623D0DAAULL, 0x83F9163032D94A7CULL, 0xFBBADC1C885041CCULL, 
            0x12418BA0B2493F74ULL, 0x23B8CC4327F5190FULL, 0xB48F6E0290BBD697ULL, 0xAE861A2F4AAE1384ULL, 
            0xF5C486D7CB366DF1ULL, 0x62536D5BFF0404D2ULL, 0xA03F8EF08EA302D6ULL, 0xBA361A21CC6F79C7ULL, 
            0x8D1B9BDA796B805BULL, 0x166AD198DC327884ULL, 0xEC45416C89C7195DULL, 0xDC7DEE7C0CD1AC33ULL, 
            0x7BE3678AE873C16FULL, 0x476961757815C190ULL, 0x643D01327DF2BDFCULL, 0x08311CCCB754A571ULL
        }
    },
    {
        {
            0x5B5195480527B5B9ULL, 0x0B876EC78BF7A5B8ULL, 0x7F85D7D673FC2BB5ULL, 0x4DCA1D91638D93BFULL, 
            0xDE28C6E0FDB9837AULL, 0x6C43C356D964E838ULL, 0x9D76CB66463E6C44ULL, 0xB6B7A18112AAD5D3ULL, 
            0x36404132B6CEFB23ULL, 0x583E1A71DFB4E8D8ULL, 0x8E5E3E4C3D7FD62CULL, 0x53A16B476EC40500ULL, 
            0x44359683F8D4CCB6ULL, 0x33B76C65F07D0D2AULL, 0xB5E80C63972F47F0ULL, 0x1092664EF0FEABDFULL, 
            0x204922B620948FD2ULL, 0xE747ECD4A92118BBULL, 0xF1CBFCA4116E6EB3ULL, 0xB9A3A830577218B4ULL, 
            0xE4C1D262EBF4421BULL, 0xF62074F19C643323ULL, 0xB2269F9C61061DABULL, 0x332F0C93D7B15A89ULL, 
            0x6280DE46349EC75CULL, 0xB55B89A2F8B81C5DULL, 0xED1FC2DEAE27EBB8ULL, 0xE5F4C6D4508E8622ULL, 
            0xB861D105AB3823EBULL, 0x8104AF2CE4343182ULL, 0x4DA612807983B706ULL, 0xE19CC07A04691D70ULL
        },
        {
            0xD8B182977343F335ULL, 0x2D402D42A167CA30ULL, 0x7AFB5C1C55C8E725ULL, 0xC7987B4B319846FDULL, 
            0x5B55E73ABBC62098ULL, 0xFAB0793C07D9161CULL, 0x9E24FD37277287EBULL, 0x76211CC0ECBE25D5ULL, 
            0x243447E8EA501146ULL, 0x7458EF03D95A8A14ULL, 0x42707B5F11DE3030ULL, 0xDFE516C80696B743ULL, 
            0x8D9EE1051B734572ULL, 0xB2711FFA13252373ULL, 0xAB5189A9A0435304ULL, 0xE474C015544FE820ULL, 
            0x77F1D10A175579EFULL, 0xA94F33278B164A6BULL, 0x288266CA3703B263ULL, 0xC2510BB1E3E414C0ULL, 
            0x47FAF49764B3F3FFULL, 0xBBF0B18E1EA3664CULL, 0xE321DC5323B5F451ULL, 0x100585B64F36BA20ULL, 
            0x92326D279B2A9A93ULL, 0x8F4D1DEE36DCFF03ULL, 0xAFB8D03832E0382CULL, 0x08933BADD852452CULL, 
            0x1C5538E8F7797E50ULL, 0xB145D7D025369F54ULL, 0x2FA8E884E09069D9ULL, 0xF744F11BD0BEE050ULL
        },
        {
            0x6AD67A3CE1F9E282ULL, 0xD39CC6B3FE1AAC4DULL, 0xC55BB45283E5FEC8ULL, 0xFA0BF5478081CFC4ULL, 
            0xADE608047AC0A2C8ULL, 0x66B52BE96C1AAF4BULL, 0xA0479A10DF03C45FULL, 0x6E9B3707EF4597E0ULL, 
            0xD523C28CE10E3480ULL, 0x2C6903B8EC8278DCULL, 0xBDB43F795DB80BCFULL, 0x880626FFA155FA2FULL, 
            0x40599F7EA6F9918DULL, 0x03C82DAF9C65F702ULL, 0xD5EA85E3A7E829E8ULL, 0x7D4698080D2A501BULL, 
            0x22D3026513BD561BULL, 0x51A96221082F8EBFULL, 0x3D8D446A9BA6D920ULL, 0xC8AF7D1DFB09A099ULL, 
            0x3FAF2D0C82AB1DC5ULL, 0x6B89322E1ACDD81AULL, 0xF48D8FCE1C24679AULL, 0x4BE98D38FC8958E5ULL, 
            0x5107510E6F69EC2FULL, 0x68250ADC2F8A6316ULL, 0xDD64D885E6815E72ULL, 0x8A482F8E829E2478ULL, 
            0x8F5A729043E40DC8ULL, 0xE27EAAFAA5A2DAFCULL, 0x1C2170D9E41F901FULL, 0x4F51D4C25678977EULL
        },
        {
            0x789C50166110502FULL, 0x7D5FBB8521AFEFA5ULL, 0xBD509E029AB954C8ULL, 0x5D746D8013BF63D1ULL, 
            0xBA114EB1A8D4B1ABULL, 0x45443E134B356447ULL, 0x1568E324FE46D0B9ULL, 0x1299E7D67A719685ULL, 
            0xA52198A1B2126430ULL, 0x811B5379269628A3ULL, 0x5B95CE1E14EC8987ULL, 0x4B0410CB9AFFE6F8ULL, 
            0x69005C783A021668ULL, 0xE4D6140B8F303DC1ULL, 0xC2403685257148A5ULL, 0x23AFC6FB0BF43D65ULL, 
            0x68CDD38DA4665ADFULL, 0x48D718002B17F8B7ULL, 0x0459ADC6B316B4A9ULL, 0x0AF477099E29403CULL, 
            0x470AED9A914BA81CULL, 0x7A38F394B5B316F0ULL, 0xBB1C5ED9EA984C94ULL, 0x45FDDCFDA444800BULL, 
            0x17430850FD37E3ADULL, 0x291E6B0F4271580EULL, 0x78D294D76732EDF4ULL, 0x2F50F216DB7148CFULL, 
            0x62E3CC41A2ECD16BULL, 0x64D7108CE88C44F6ULL, 0x217300C9E4313BB5ULL, 0xA7FA1BDF7129526EULL
        },
        {
            0x0A2A9904A1B72B67ULL, 0x91AA3C940A167ED9ULL, 0xC93519F75963F88DULL, 0xA70DA7487E024B68ULL, 
            0x16C769D85CF8E8EFULL, 0x5379C6CA59D0925AULL, 0x95D7A171AB80B8C8ULL, 0x268E9C5996D88D7DULL, 
            0xC352DD9EB7759DEDULL, 0x1CC294CAE5E19651ULL, 0x5ECC0DCB1B4215EAULL, 0xE4D6306D10B38942ULL, 
            0x339B8038D55281D0ULL, 0x6BC0C307D9268F8DULL, 0x1A41BB974CA78120ULL, 0xEAF80267C6A6E5EEULL, 
            0xC8DBFFED88A2545AULL, 0x7473B76D52DD8589ULL, 0x07EB043620E798C1ULL, 0x7D0ABAB5920F53F4ULL, 
            0x0C5C3A0B4AFB8F53ULL, 0xC750BB09AD42F5ADULL, 0x21C50B0930775D6AULL, 0x949BA3F25E1A08A1ULL, 
            0xDABFE454717684B6ULL, 0x4AA2426C29134860ULL, 0xA7EAD0299B47F8B3ULL, 0x1FD3594220311C89ULL, 
            0x0F80879F4C18F4FDULL, 0xA02E8F04DF6F4338ULL, 0x138F9C7405310BA8ULL, 0x78BFAEF1FEC57BE5ULL
        },
        {
            0xD8C5804997104628ULL, 0xF883D7BCDD4305ABULL, 0x8632619713CFB55EULL, 0x8B5BAEB106A96DDFULL, 
            0x147137002AB3607BULL, 0x6EC6E59A4EA40E3EULL, 0x180F44DCDF3DE013ULL, 0x5ED6AD8B44E09DEFULL, 
            0xCAEACD1800725570ULL, 0x59CCAE0FFF01A231ULL, 0x5DC02804BE5A292BULL, 0x99277A5B7B70E026ULL, 
            0xDA425BD77D717F80ULL, 0xFB4FC9EE0099B9AFULL, 0xA998864DB54E03F5ULL, 0xE0DC6BAACD3303B1ULL, 
            0xDBA3FE4AE9374AE2ULL, 0x106764047BE7FC87ULL, 0x6C7D9E6CF532C505ULL, 0x8D1E73B8EE985867ULL, 
            0x6075C2DEB0889B2AULL, 0x188E681C57B656E6ULL, 0x7CB9143FB93CDF67ULL, 0x06D1B80C5BA49C92ULL, 
            0x12C077864202DF27ULL, 0x80FDBAD39C64AEC0ULL, 0x6B77B21745A69B52ULL, 0x03BBB1336AFF0E5AULL, 
            0xCB6F2A267C494516ULL, 0xDF31612BBA392528ULL, 0xDC62FB84A5CD41CCULL, 0xDC54A566949C8E8EULL
        }
    },
    {
        {
            0xC74B4BE9633B4427ULL, 0x124DB5ACD300FFDEULL, 0x2D71FE5AD2C042D9ULL, 0xB9DA522B975F8D1EULL, 
            0x94B68C909AA953A7ULL, 0xFCF0FDDD6BFE59A5ULL, 0xAA6874A6B3BC0DD7ULL, 0x7F9DADD25873CD72ULL, 
            0xF4FCDC48DE2979F8ULL, 0xB9569968CE6F172AULL, 0xD1A547EF341966BBULL, 0xEFC1ED3436791EB1ULL, 
            0x3BB5620BA4B9A58AULL, 0xD818B16464ECA3BBULL, 0xEEF09561EF115847ULL, 0xDB7737D9269FEE10ULL, 
            0xAF56701C0BE88F1CULL, 0xBE0F2FDA5E6BCFDAULL, 0x80BB31337EBD5DD8ULL, 0x163CD7461B0EB4DEULL, 
            0x78AF2F187C806797ULL, 0xD7FA3B95B19F120AULL, 0x4BA916EF62128555ULL, 0x40D13466EADBC9B8ULL, 
            0x52A1F1DF2E0B9489ULL, 0x0DABF9888549B603ULL, 0x40CDC7C11733DE66ULL, 0x113305D00E1A4D45ULL, 
            0xB28C994E94379A05ULL, 0x8C045F495C30F73CULL, 0x5DFB4AC21F0172DEULL, 0x718D14F35354F6B8ULL
        },
        {
            0xE64574475C1794CEULL, 0x8C25AF12611911CDULL, 0xA818983FFC399B25ULL, 0xD555696A601302A9ULL, 
            0xA7F29FC4C0699A92ULL, 0x99FFFE0B673B2049ULL, 0x39AFBC163C7FD491ULL, 0x9C754632787110F8ULL, 
            0xFDC7FE263B884D68ULL, 0xC239F7B3259C1BCFULL, 0x6138E59A4C35218BULL, 0xA0979219514A24ACULL, 
            0xFD6C20A85BC79CB3ULL, 0xA82C23704302705AULL, 0x55E4D7AFEFC1C305ULL, 0x54CAA3286AFBDC75ULL, 
            0xC4FD51C774B8CFEBULL, 0x366CC4CA995F3E22ULL, 0xEB64DFF4AD6183D7ULL, 0x0CCD04A4E206CB3BULL, 
            0xA476F20A137CF85CULL, 0x725FE90C3E984D26ULL, 0xD1C290EABE624722ULL, 0xFA57824E0B2732E5ULL, 
            0x285A4585DDDFCD9EULL, 0x8D22C6E916C03156ULL, 0x169BE6CCDEA0C22AULL, 0x65ECFAC52C6736DCULL, 
            0x009B506C0944DF0BULL, 0x21784FD55CF4FF9BULL, 0x6D4A8228097FBD13ULL, 0x57A20283A0108C96ULL
        },
        {
            0x7FA37EF95F109A3AULL, 0x12237A5DA94E332EULL, 0x8E309BC3DE676C19ULL, 0xD4E0C65AB66A5A04ULL, 
            0x22419A8F87D63DBEULL, 0x3A09DB1242B66FA5ULL, 0xEBECAED8C937D909ULL, 0xC5B164FDC36A5FECULL, 
            0x48FAB11B641CBA3FULL, 0x762756F3E7739DB3ULL, 0xB61024EE3CA264B6ULL, 0x2D1F13683F1A83CDULL, 
            0xC0A290DA19A8ADC0ULL, 0x40541D05D23A14F6ULL, 0x10081DB702BC5813ULL, 0x4EAC90A683E4C7E9ULL, 
            0x337D126C3F64197BULL, 0xED4EDE24C24B798BULL, 0x4FDE82E09FAC56D5ULL, 0xA4C0C7D59BB1BAF5ULL, 
            0xA3A909EDABB03484ULL, 0x03B7F1CAB0658FDBULL, 0x275C169AB2F28FBBULL, 0x6254EF8C92CEA88EULL, 
            0x094B9416C4D63186ULL, 0xB71C6B1D0CD7C64CULL, 0xF65020BE610B349EULL, 0xD0BD25E877C59972ULL, 
            0xB69DC96BE76DFCA2ULL, 0x85024793F3637E99ULL, 0x7DB8529A9D91144BULL, 0x5F595EFC4A937F5CULL
        },
        {
            0x65D7487C02950669ULL, 0x49D100FE96E5116BULL, 0xFB1773F85610ABF4ULL, 0xDC902AF1422F98FAULL, 
            0x9143D37192CF3A29ULL, 0x2FD8F985B70AE52FULL, 0x46730812189EBC4BULL, 0xF14369175DC860D5ULL, 
            0x95D70ED4DBF24B99ULL, 0x265DA200BD303ABBULL, 0x490639D7967AE80BULL, 0x17D245B70E7A0AD1ULL, 
            0xA2A070A85C326AB4ULL, 0xEDECB3A0CF7E6B1AULL, 0x6AD70318CCE3D833ULL, 0x9D5C016EB1AA2840ULL, 
            0xE956E20067C09754ULL, 0x32E8F46EB18A18EFULL, 0x482999D9EF0CC946ULL, 0x27FA50CD1B235B92ULL, 
            0xA239E3D35040DF5AULL, 0x52D42FFDB5654797ULL, 0x99D893847F86FAC6ULL, 0x3C4294533250E2E1ULL, 
            0xBA15735563EB94C5ULL, 0xEB0E72C57DA64C2AULL, 0xBD9F99A24DFB08A9ULL, 0x993A7DCF7B7BEB2AULL, 
            0xE91027936C6E254FULL, 0x76DE000D51CC6641ULL, 0x6DE8F336C5A95DCBULL, 0xED75724044A7E12EULL
        },
        {
            0x988E3003AB21FD80ULL, 0x71E26882C4206AC3ULL, 0x5E386D6053AF6A49ULL, 0x9BB91504A0FA04BAULL, 
            0x3E340BCD45C02FBBULL, 0xE72F0D1112109EB2ULL, 0xD39398624FE2BF9BULL, 0x3D0BFA22E0D618A2ULL, 
            0x8FF7E94D97FD13C4ULL, 0x67C3CB84F35D3583ULL, 0x13CE85B094399965ULL, 0xA79B3329F7891B8EULL, 
            0x414582B0E8C1F6D0ULL, 0x68E1D92FC71E91ABULL, 0x606CC570E1AA8731ULL, 0xE14A9228492983E3ULL, 
            0x8A0942396108A904ULL, 0x236A82F3C39A385AULL, 0x0DEF3BF26DD21430ULL, 0xD45090202A1E610AULL, 
            0x9AD1781CDF6278DFULL, 0x9D9F1A6576600E31ULL, 0x00FC7C7BE80F3284ULL, 0xDBB10DC70AA5C60EULL, 
            0x1CBBF41CE94076E6ULL, 0x4E1F4665B0535708ULL, 0x5695163BA5A297EAULL, 0x2F436F8D13604791ULL, 
            0x825E9F2085F18A0CULL, 0x1529AE19473781C6ULL, 0x65E5BE477CBF9948ULL, 0x455BD74E857A7CBFULL
        },
        {
            0x1315A02A843EA8DFULL, 0xE519B44D36BF2531ULL, 0x68A7E99C817B227BULL, 0x3CFBAB5B7F75573AULL, 
            0xFCC6526339F96161ULL, 0xC28C61EF0D87DDB6ULL, 0xC9ECAF67B6083BFFULL, 0x71AAA958080131ACULL, 
            0x714B76EAB0E23FFDULL, 0x134D50AA05AB11B4ULL, 0x2C4C7C139A41089BULL, 0xE204D9D41EE94D92ULL, 
            0xEF5985F86081E971ULL, 0xF5B81BEC935E0449ULL, 0x967B9C662457FBC2ULL, 0xBB21434D6C383B4AULL, 
            0x8412AA8C8B7E94CCULL, 0xE9F8F6EB57D5658EULL, 0x08CDE40275D7F23DULL, 0x0C7C153B568F74AAULL, 
            0xAD8E2281587C0C33ULL, 0x65D4A71F35680024ULL, 0x06343AC75A4AABF1ULL, 0xA5BB760888776CB7ULL, 
            0x0963AE3AFF951E8FULL, 0xE4BA9D130E315C00ULL, 0xD63BE200972ADBB8ULL, 0x58300C42472A008CULL, 
            0xA0079504BCD54A92ULL, 0x44D9C49128E81332ULL, 0x2FF48ED4284B63AFULL, 0xC972E467E6892BF0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseAConstants = {
    0x4E56215110DD86CCULL,
    0xCCD24598CCF5BD9BULL,
    0x21709589983C1212ULL,
    0x4E56215110DD86CCULL,
    0xCCD24598CCF5BD9BULL,
    0x21709589983C1212ULL,
    0xAF3A5910F41DB62DULL,
    0xAC5F9AD90E39A79BULL,
    0x0E,
    0x74,
    0x56,
    0x2A,
    0xA9,
    0x3B,
    0x9C,
    0xF2
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseBSalts = {
    {
        {
            0x0FB730B437FB3E51ULL, 0x008446A82A3C7181ULL, 0x168F3CE0F07B5EBEULL, 0x9027528534C6BB23ULL, 
            0x16DC69299045EBC9ULL, 0x89FA91204118C3A4ULL, 0x91B12B640D303EDAULL, 0x695DF1EE3A9957F9ULL, 
            0x3E67C35EDBC01C5CULL, 0x4FF428DDB13081D1ULL, 0xFE83BB02087929B3ULL, 0x3CA7F8731B519866ULL, 
            0xD5A8DAE63EAB103DULL, 0xF5470B6F70B219F1ULL, 0x5ECBE61DA76A6C15ULL, 0xDEBBC2C02B38D7DBULL, 
            0xEC06CF967C2D1E85ULL, 0x9395E4F914943106ULL, 0x23CAC9D521F856C4ULL, 0x1ABDC4D4842B9BBBULL, 
            0xAAE5A3F9F8693285ULL, 0xBA02FE1357D94951ULL, 0xBAE339197DE5CFC3ULL, 0x375FB0B363838655ULL, 
            0x34916807B7F8FB48ULL, 0x262ADC95142A0B2BULL, 0xDD82F7D6C61370DDULL, 0x50DB690A2140AD7EULL, 
            0x432FDBB2CE20254AULL, 0xCC309ABEBEBEF679ULL, 0x6FB72122FBC4C692ULL, 0x89125F866D15C449ULL
        },
        {
            0xFA513C0BABE7E6EAULL, 0xB61CAE381D08F9DEULL, 0xFB851060A3C7195CULL, 0x45B21EC01E69181CULL, 
            0x9B9344F627260F72ULL, 0x5A2878C40FBC02C5ULL, 0xA74555C74501B8F7ULL, 0xBBC9DB0F2F57F966ULL, 
            0x0682929ACD76CD94ULL, 0x6BD54893F5E8240DULL, 0x636B59FDAEBBD5A1ULL, 0x61758A7E7EB38EFAULL, 
            0x15C64DEAF59726D3ULL, 0x5E130CE79D45BAB6ULL, 0x134C5CEDF86DF643ULL, 0x1FD318E738FD5DB0ULL, 
            0xD7A0265271EC888AULL, 0xFAC7D3714CA7ECC0ULL, 0x90A8241A0C362093ULL, 0xC9B060DE4B4CF36CULL, 
            0xB9469E352DB7F678ULL, 0x8D74192020EC93A7ULL, 0x6E77DB1D1FA5FC7FULL, 0xC458EB72095F509DULL, 
            0x55440E8183FA8308ULL, 0x7B1CFC896F6D60F5ULL, 0x4766C9F9913C65D1ULL, 0xBC01FA689D86954EULL, 
            0x701DD873EB2A1164ULL, 0x21315D7B0A4446B3ULL, 0x287D90BE5FB28941ULL, 0x19330E9D2FC511EDULL
        },
        {
            0xFEA31194F4712D17ULL, 0xBC4B4BB5ECE9A235ULL, 0x39746D4BBCF236F7ULL, 0xC0B0C11385FACF8AULL, 
            0x5BC985A8E1DDE944ULL, 0xB0AC8669947722B0ULL, 0xDFD85B9E0626D4F1ULL, 0x00CD82FA4C1A3121ULL, 
            0x527D33692393624BULL, 0x57F97762E7898C0BULL, 0xE487A88AF09C9E1CULL, 0xB5F3C30F16843399ULL, 
            0x6F823D2A16404241ULL, 0x28F501D8A5527B73ULL, 0x17A7602B1EBE733BULL, 0xADBB60E57FBC8B61ULL, 
            0x6EE400AC54D5FD72ULL, 0xD4194E57951ACE27ULL, 0xD23400BFB5A62B50ULL, 0x49BC939A4E6F4E6AULL, 
            0x14F14480E9E8B7AEULL, 0xCD8089BDAE18D80FULL, 0x5F119CFC2C9CED11ULL, 0x9D630EE579D5C080ULL, 
            0xB21053F50F217F42ULL, 0xC420D9DF03431F6EULL, 0xF88A450B0A0A8751ULL, 0xB47CEE581724A2B8ULL, 
            0x07328FEFCF2A7951ULL, 0x191870C22080AB6FULL, 0xF4B40C505B007038ULL, 0xB70BAEEDD28C9437ULL
        },
        {
            0x6F4CFA3F76A61645ULL, 0xDCDCC9A7F6B0F210ULL, 0x438AFE06ABD94B78ULL, 0xCE7050C2BC542C42ULL, 
            0x4B9284E1DD8B823CULL, 0xEA0C43D00D69B017ULL, 0xD32EA3AFFDCF28BEULL, 0x9980F13BFE914C6EULL, 
            0xBE13F3647AA3A6D5ULL, 0x47D218609E3FC0B2ULL, 0xBB869B0B65393146ULL, 0xB2ACD70935E6FC2DULL, 
            0x8941D0E766C1A2A0ULL, 0x3FEB01DBD90BCDA5ULL, 0xE5417B0699E7E203ULL, 0x01340007CBDD2EACULL, 
            0xD5317673045565D6ULL, 0x3F53A388D1C216FBULL, 0x2E6466F346E0295EULL, 0xC6212084782A490AULL, 
            0xA5B4EA1B2F13C40AULL, 0xC97E31BAFB8314F8ULL, 0x3CAE44A85D9F82B0ULL, 0x106F0250CA6A4E1DULL, 
            0x6E0DE5777FD15DA9ULL, 0x8D8171BFEF315558ULL, 0xCA7EDD6A821FE6B8ULL, 0x90189835F717AA6DULL, 
            0xCC6646CC8AB1549DULL, 0xE6B0C504EC555A25ULL, 0x0C5899AA8988A75FULL, 0x838ABE26AAE7BD36ULL
        },
        {
            0x86850700F2D2BFBEULL, 0x31BE46E701C3A9DEULL, 0xF155BA41390A42E9ULL, 0x6CBBB21CCF373BE5ULL, 
            0x9719C6FAB5E8F845ULL, 0x30DFEBA145F12CEDULL, 0xDB778F9BA5278AB3ULL, 0x5727BF043E6DDDD7ULL, 
            0x0BFBE5FA6D8A26BEULL, 0xF2DB20C96C50F810ULL, 0xD2BB09A2417DD269ULL, 0x5A0B14C12EAA32D3ULL, 
            0x5B2B9FD6CD44DB35ULL, 0xFA98DE780B0A0289ULL, 0x7B9548DAD1B4DBB6ULL, 0xF8D68D2BF9A6FC27ULL, 
            0xE8A23DBE02D74752ULL, 0x136CDF8D7A48309BULL, 0x618B68E8D6495C8AULL, 0xEF540780669BB332ULL, 
            0x6180214EB65EC3FCULL, 0x27DE2327B284A4B0ULL, 0xAF8CB65F290B4D92ULL, 0x51B105260A91A299ULL, 
            0x0915FE5AF994C7CAULL, 0x9F75EED5106D3648ULL, 0x927A49D80F4CDC7CULL, 0x33089A779AD1DC37ULL, 
            0xE20EC14F30B8FC37ULL, 0x26754931E5F9FAFBULL, 0x60B0BC9CD9673D1DULL, 0xAF5068298BE5223FULL
        },
        {
            0x0965C219D4500F3FULL, 0x341D2E90A12D5FCFULL, 0xE1BF021E250E1DA4ULL, 0x5DEB6C6A9543EE45ULL, 
            0xA0978FA17AC32D2DULL, 0x48D976790B5B1E75ULL, 0x5DC7AD3B86B7628CULL, 0x4DD5C9448684534BULL, 
            0x6010B25F1434EF76ULL, 0x4D904E516BB6E898ULL, 0xA4DBD1EC1423C95DULL, 0x438826D77537FC82ULL, 
            0x0EE3DE7FC4DB56A0ULL, 0xE08EA513E373C5C4ULL, 0xEEBA95C0C22FDCA9ULL, 0x77C1BE5974A3A85EULL, 
            0xA36973B6BFF25DE9ULL, 0xAB3FD0537F803146ULL, 0xA120727B36E523B6ULL, 0xDD32700B5B2663C7ULL, 
            0xFB2BCA3980C67CE2ULL, 0x57FCC97BBCC3E02DULL, 0xB549E06DC78839CCULL, 0x4B6D7BD7D1B55952ULL, 
            0x4EA9F98FD0F9BA80ULL, 0x45D7970BE89FEEB2ULL, 0xEDDFE82FC35FE816ULL, 0x038503E01F46FE4BULL, 
            0x17792DE540A2EE9BULL, 0x48B93F58CBBDE1D0ULL, 0x0C52FAB588B32F77ULL, 0xC6DB00D1A5BD9A73ULL
        }
    },
    {
        {
            0xE5D35D92E5D7F7A7ULL, 0xECAA752CFE5CC133ULL, 0x7DFE5F4E5A20E56AULL, 0x1F50C04E5028EE5FULL, 
            0xB95E2EF3BBF00449ULL, 0xBCE7599AFF9FB024ULL, 0x2DBCD6011E015D7AULL, 0xF53DCC895A6BA065ULL, 
            0x6DF7549F3E1F371BULL, 0x941EFA7CB3CB5673ULL, 0x5DA58C93303CD527ULL, 0x64BB4A13D883A1F6ULL, 
            0x97B20B378B9A3133ULL, 0x7E8A2CEAB8F11BD5ULL, 0x3F8306E64EF1EB8FULL, 0xE0791968ADE3C311ULL, 
            0xA92F9916BDEB40BFULL, 0x551780FCFF312687ULL, 0x6B139B11635DD543ULL, 0x7B5F7BEEE38FA693ULL, 
            0xB726E8B7063A7986ULL, 0x7FC4EEE6AD9799C9ULL, 0xD3C243E062EDEC29ULL, 0xF1790DC51FE3E7FAULL, 
            0xE49F8B2F5DA45DF0ULL, 0xE427B7C501FF51C8ULL, 0x0CE1533FB89D2C41ULL, 0xE129EC5FFDF9A789ULL, 
            0x38F265A034052E6FULL, 0xB14B39532F1A489AULL, 0x266AB40108AB3BE2ULL, 0x405770640DCE17BFULL
        },
        {
            0xE16EBD1840308566ULL, 0x367EF1FA9C303675ULL, 0x6A3B09B276189575ULL, 0x0F10FB825BCD2D3FULL, 
            0x0C5FF0F870E05691ULL, 0xC06F9F84D8F549FCULL, 0x724229624AD34E48ULL, 0x8E03F26AF4C277BDULL, 
            0x341D77F5D01B1132ULL, 0x5C9515AE44203194ULL, 0xD6E80FAB4612B746ULL, 0x9C932EF5720AFDC2ULL, 
            0x6C70661E70D68C77ULL, 0xAFB5C9A159413986ULL, 0xCBDC3C894C6C92C0ULL, 0x92984586E02C565AULL, 
            0xA84C65BC1BE1D37CULL, 0x69C234DE6D0F4317ULL, 0x2986838E3FD77D72ULL, 0x036A4FCB099C86BEULL, 
            0x5885C04010E3A4F8ULL, 0x81D5E04C1FB29C93ULL, 0x579C5BEA577974C2ULL, 0x8B11E1BDAE115F57ULL, 
            0x97D0B63F53E1C838ULL, 0xB47277AEB07DE5B1ULL, 0xE226B39C60BDC98BULL, 0x61C22EED8CF7FBA2ULL, 
            0x2235139AC6E3BD9BULL, 0x736FAE7EB81F9BEAULL, 0x75CC888206E58D33ULL, 0x21E7F50E17D8B044ULL
        },
        {
            0xCEDBCA9CEB506CB2ULL, 0xBB7E0F77B7941719ULL, 0x33ED90177D0BF156ULL, 0x6137A3168E47924AULL, 
            0x79D3F5A034FA0399ULL, 0x2E132C0B99EADF20ULL, 0x02FE0CE7676176E0ULL, 0x398F389E17BDC839ULL, 
            0xA64017A71C08E04EULL, 0x80B887AF403BF8F5ULL, 0x56646ED2BBF03C36ULL, 0xD115A78311FD509BULL, 
            0xFD0D1474DE94E34FULL, 0xF7B3669F47924AE7ULL, 0x2FE8CDAA1FCF9A41ULL, 0x72AA00D6766587FEULL, 
            0x3510D13B4BEE30D6ULL, 0xDE04ACA845DDC7CEULL, 0x0D1F04DFB50D7840ULL, 0x03619325D374B4E0ULL, 
            0xC4D7CDA88ECA5826ULL, 0x4FDBCBDE356369E7ULL, 0x3756F5C710FDDC72ULL, 0x16A5B3151F913896ULL, 
            0x4E46C7C5C3C6D473ULL, 0x82299D6D86ABC47BULL, 0x9E6B40FDA6299F02ULL, 0xC08D49057FC88498ULL, 
            0x5CA12998FC251660ULL, 0xD5E7A2FBD6499393ULL, 0x15ED204319D75279ULL, 0xCC210657D99E40EAULL
        },
        {
            0x78A96A3701DEA9BAULL, 0xED8CB484D74AC4F8ULL, 0xA80ACC8CE7FBA822ULL, 0xE98DAFD137B25E2BULL, 
            0x82DBC6AE032AE2CDULL, 0xEC5983A22BA98295ULL, 0xACBA188A659257CEULL, 0x45FFE7F706EB1D03ULL, 
            0xD7C5244B159E13B3ULL, 0xC65EA4625582A219ULL, 0xD8FD154DB46369EEULL, 0x6C98AD5B41D7B138ULL, 
            0x9DF98BBE3CD00239ULL, 0xF6018F4C55A7F833ULL, 0xCC84FE37336CE30DULL, 0xDC3F443D28745370ULL, 
            0x9E3F56375BC8DED9ULL, 0x52D8DDB0BF5DF0F6ULL, 0x27D3D697627ED429ULL, 0x8E16DF8EB5483BD7ULL, 
            0xD1D1EB99953247FCULL, 0xA9DADA4EABB48D94ULL, 0x54CD95F831B3DF5DULL, 0x21BFDD3DF9D9A397ULL, 
            0xF463795746D3D4BEULL, 0xAD51AC826E0C484EULL, 0xBB90D066C6159F90ULL, 0x608321C6BD47072DULL, 
            0xCED80202F3797BF0ULL, 0x46211B2538372CE2ULL, 0xD85689F0E061A1ABULL, 0xC62695D8EF145E14ULL
        },
        {
            0x8DD8C0AD926F6187ULL, 0xC24B7E517F27464CULL, 0x968A0281E14EDBFBULL, 0xFE5F703E02028766ULL, 
            0x10CCDD31F106C7F4ULL, 0xD842056D7E811C3CULL, 0xD8E7477CDA0F3DE7ULL, 0x52B908B1DA0099D4ULL, 
            0xA6E9F057B313459DULL, 0x82FFDBEBFCB1A97CULL, 0xAB6BA954CCDDE997ULL, 0xD1E8562B08CD5417ULL, 
            0x98B4EC88E14EDC3BULL, 0xD3FEEA344B646245ULL, 0x4A579E9C02873CCDULL, 0xF0EA3F2C1A869748ULL, 
            0xF41ADC93F404723DULL, 0xDE5D326CEEA16CD3ULL, 0xE62F8993CDCE81A0ULL, 0x95C7827B01B7F40BULL, 
            0xAB9669E86D620EC3ULL, 0x10E9189CC466795BULL, 0xB3D04C5115ADF755ULL, 0xDF11C0794600C5C6ULL, 
            0x65AF3D5E155F4A03ULL, 0x6A67CE6107BCCE22ULL, 0xB4A5388E033FFA79ULL, 0xDAE1F81FFAFE226CULL, 
            0x0B78F929D7A63B9EULL, 0xFF28A47D2ECA2CD8ULL, 0x865C9616E6034170ULL, 0x026677B622BE7C69ULL
        },
        {
            0x69F381E49D22B370ULL, 0xB67D988388F467B7ULL, 0x639C6B1B26196985ULL, 0x6D325201976425AFULL, 
            0xDBB78CC164C21356ULL, 0xE7941039FD546FDFULL, 0xEC52B69F80FD8C4AULL, 0x6C87C13ED5A7039EULL, 
            0x7EDCCA8A49D929AFULL, 0x157A43310F4B1C74ULL, 0xD8805ACEAEBB8B37ULL, 0x07EADC838ACD9C8BULL, 
            0x8AE05C46557ECF5EULL, 0xEE108716FCA98DA8ULL, 0xADF0AE2A4DDB127CULL, 0x3DA7BC7680F944F8ULL, 
            0xBA89B46890AB73F2ULL, 0x43E77976EB2F1F31ULL, 0x4AEFE3B5874C9470ULL, 0x2D0A866F87322CB2ULL, 
            0x563669E2BEF5DC71ULL, 0xEA1F220BC2329EA6ULL, 0xF850ACF0DC0CEC15ULL, 0xB3D17BE5E7E4E14AULL, 
            0x207D2E078A2D70CDULL, 0x3F7E739883E17B00ULL, 0x239D7916ED348097ULL, 0x17CC51B5F827CBD2ULL, 
            0xBBD6DC3C5B9D53FEULL, 0x100A6C11D781E051ULL, 0x83710CA25680CB75ULL, 0xB1FAEAC6E86D1237ULL
        }
    },
    {
        {
            0x78B32865687539D3ULL, 0x9F29E7AFBD828C39ULL, 0x0D2660914F22F41FULL, 0x2649F47A1BEDD262ULL, 
            0x3521122A2571C3D4ULL, 0xE6FB3065A879B18AULL, 0x7DF9FD5341903F9EULL, 0x8A6E4E81B058D41FULL, 
            0x3FC91E680E7C5AE8ULL, 0xB3E2107E6988CF4AULL, 0x921F6883D4A58E36ULL, 0xF11AEDC71211C747ULL, 
            0xF7FEABC937CBB600ULL, 0x894386CBDDE82F5AULL, 0x9CB0C2BC8D0E5EB9ULL, 0xCDA1FF4600DE022BULL, 
            0x2EFBC45D53D6CF65ULL, 0x6773E0B27395D5DAULL, 0x11E822F4B75C7746ULL, 0x63570E80E12896F1ULL, 
            0x0DBFA25F57E084CDULL, 0x7D4801A0E7BBB449ULL, 0xB4EACAE813E33CDCULL, 0x1DA662425564E031ULL, 
            0x5979378AED08EF11ULL, 0x9711995B185D3D4CULL, 0x2CD55964FE5C5116ULL, 0xA0AB9835313E7BF1ULL, 
            0xA67FB0369D4AC978ULL, 0x60A062E9E74D53F4ULL, 0xFB45102B1AA8E6F4ULL, 0x5377F3A870070533ULL
        },
        {
            0xBB3AC42F42B50E1AULL, 0x87560FAA3A3F7D49ULL, 0x4F8C9B7927D9CDD2ULL, 0x50C8F0AA26D20D0CULL, 
            0x35CF2BE1C3B0AC91ULL, 0x8FE5E09268B8E156ULL, 0x44D5B08976103707ULL, 0x860BD2DFCA2C71D3ULL, 
            0x2A3EAA8A581611D3ULL, 0xC6CDC699A96FECFCULL, 0x4F01162594E896B7ULL, 0x94B7083498532317ULL, 
            0xD8D7FB59772ED16DULL, 0x7A4A9E873AE7BDDFULL, 0xEFCDACB43AB3E749ULL, 0xD48ACCC0D73E5519ULL, 
            0x0322DDDE71C00E54ULL, 0xDB590F761C81A93DULL, 0x88C463CD3560C46CULL, 0x49A27F6390AFAC47ULL, 
            0xAC356032419D6E31ULL, 0x47558BD5D29D211EULL, 0x296B6B80CCB97E66ULL, 0xA80255BCD046FC11ULL, 
            0x95722883445CAFA1ULL, 0x4F9741E441F52432ULL, 0xA087A0CBAE9BC759ULL, 0x9CCA86286417BD55ULL, 
            0xA9F58468D8E2B630ULL, 0x534308A1FB3AF3B8ULL, 0x297A107046C9121EULL, 0x8E0EBE9625B075EDULL
        },
        {
            0x3146629FBF64F44EULL, 0x41D2B43158F18342ULL, 0x5ED838E623339DE5ULL, 0x37BB047B871F5530ULL, 
            0xFB8E1E178E33DD0BULL, 0x72B3409190F2E760ULL, 0x824DB23DDF345657ULL, 0x0DA3AC40A1EA0444ULL, 
            0xC3592602895B2CA8ULL, 0x48BA7D9BC5CEC38AULL, 0xAF5C4DACA3A9AF8AULL, 0x5426EBEE4C182F5EULL, 
            0x92CD9F1BEDE70CA4ULL, 0x026634C173D875D5ULL, 0xD42FB4EB16EC8789ULL, 0x354038891640080FULL, 
            0xFBAD60C76C0FABFBULL, 0x66F0FF67A889FCD2ULL, 0x4D8A227E116EC100ULL, 0x1440178063DCBB4BULL, 
            0x38E739413B390EFFULL, 0x3CE5F7F0D5EB262BULL, 0x7F25626C9D7335DEULL, 0xB4C32D2533157E4EULL, 
            0xA791BEA1413452B8ULL, 0x76FF3AF8F6316F03ULL, 0x3CD0ED7817800EBCULL, 0xF46179E239909908ULL, 
            0x137E3F523D87AADCULL, 0x6D0B355C98A92F94ULL, 0x9471ADABF5525018ULL, 0xB969F5142EEB38CFULL
        },
        {
            0x3D4EF59B8E7947E9ULL, 0x19D8D568F2DAC03BULL, 0xA345B2AB0575CF7EULL, 0xC5D904B5743A4DFDULL, 
            0xE8EFA93F27F20D94ULL, 0x8052B2C7945B4D85ULL, 0x6D4837559031B920ULL, 0x574C70318CB568D7ULL, 
            0xD61DF51EC280C789ULL, 0xF5969FC551AF88ECULL, 0xA58EB99022B42CC5ULL, 0xE0DE198CC109C28AULL, 
            0xC1AD242E7F6FA80BULL, 0x79BEAFD895129998ULL, 0x5DA9485022F8D496ULL, 0x2EAA97D770EB4257ULL, 
            0x09378FD44720A4F8ULL, 0x5B15C6204C10DB7CULL, 0x2E56C080580A18A6ULL, 0xC8CF21A50AD9674FULL, 
            0x4248A330CE419454ULL, 0x1DF01BD8312FA426ULL, 0xDA64437505F881A0ULL, 0x6A1D75D25C56EC58ULL, 
            0x907F8BF54024F48CULL, 0xB4B09561393536FDULL, 0x6FE9CBB6DC22A50BULL, 0x3CB5DF39B772D325ULL, 
            0x50B6549FC4D45B2BULL, 0x4F8195EDAF7378A0ULL, 0x7CE31C293AE4E287ULL, 0xEA561754065A52F2ULL
        },
        {
            0x52CE24C92A20710AULL, 0x2E1C7C0864C63AC7ULL, 0x6A3EB865F86D72E8ULL, 0x92F2709DE7CA2548ULL, 
            0x7FD8F2A6F1E2058DULL, 0xAD2FD8C8B11A9F2DULL, 0x9B1FAB46D15598DBULL, 0x258444AE325369E7ULL, 
            0xC423EC70B98C6B02ULL, 0xC08E2870319C22DBULL, 0x80747BB5644091B9ULL, 0x41B243C073BFAA84ULL, 
            0x3CEA7FFF3F987290ULL, 0x076E198D9BCE982AULL, 0xC5C836A3FEAA179AULL, 0x636B6AD35D8BD461ULL, 
            0x9B008DB9DCC88A94ULL, 0x0779E2E954CE77F9ULL, 0xD97FFFE0EBE68EABULL, 0x2A419A120ACF5F7EULL, 
            0xF3EBFF7E781F5D01ULL, 0x3659779044FB151FULL, 0x8EF5B46588B3660CULL, 0xFDD6BED37536A7C1ULL, 
            0x2B1CE7A859C941E1ULL, 0x6A44B0A4105C0E09ULL, 0x9599CBD3E683722BULL, 0x0F70ECFB2DC3DD67ULL, 
            0x361A6521DBC32811ULL, 0xB45031C7F598EC69ULL, 0xED254005448784F9ULL, 0x096AC2E25A9964F0ULL
        },
        {
            0x185803C8B40AFB6FULL, 0x364FF6927B5282B4ULL, 0x96EDEA2BC7D3DDD1ULL, 0xC2A61B3BCD6AC185ULL, 
            0x5673CC27D3D6D6EAULL, 0xE810CF0ACB4A4B54ULL, 0xFCC7E1AD22D9FC65ULL, 0x5FD7840C9DE10403ULL, 
            0xBDACAC60AB6EE363ULL, 0x169214A1806D829CULL, 0x625CFBC8E26C5BFAULL, 0x02682953FD7CD089ULL, 
            0x109172FA567C9F26ULL, 0x767F72113D7D7281ULL, 0xB7D08D743AD93A18ULL, 0x5E6738E84C147767ULL, 
            0x18DA10CD23E39FBCULL, 0x3FE78CEECE353B9CULL, 0xEC49350CE877C13AULL, 0xA710530DCC2A35C7ULL, 
            0xC00147286F29F5E5ULL, 0xE0ED42BD6D7701C0ULL, 0xB6A5F340C84100D2ULL, 0x5FCB6E78D026A9D6ULL, 
            0x96C32BC85EECBF81ULL, 0x16817DAAD1DFD8CDULL, 0x5AB60D2910FC9C94ULL, 0x02BBF7839783C39EULL, 
            0x97B8A6EBB625E302ULL, 0x2D3F0BB3EE51D41EULL, 0xABE2DA713C365191ULL, 0xAE42BA28377191F4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseBConstants = {
    0x58CA3B216D8FC542ULL,
    0xBD0E62F3AE5CB9B0ULL,
    0x7F78D0DC755AB6FCULL,
    0x58CA3B216D8FC542ULL,
    0xBD0E62F3AE5CB9B0ULL,
    0x7F78D0DC755AB6FCULL,
    0xD9686EE763313BC0ULL,
    0x03398299B6BFF129ULL,
    0x59,
    0x98,
    0x20,
    0xFA,
    0xE9,
    0x40,
    0xC0,
    0x9A
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseCSalts = {
    {
        {
            0xE92258467CB19BB1ULL, 0x215945693ACC652EULL, 0x34C3E3918DC8377DULL, 0x81F7B9B59DA1FFDDULL, 
            0xB4B09026565BDF22ULL, 0x497ED818D59A31BAULL, 0xB37BD3E577A510BCULL, 0x608119BDAF4B4336ULL, 
            0xE087EAD15C4945F1ULL, 0x601C74C7C9C282F0ULL, 0xB845E19D9E32AF2EULL, 0x86E31EECBA52207EULL, 
            0x501C41D598C8C070ULL, 0x71E56BF1554AC28CULL, 0x17D2CFAE6273F6B1ULL, 0xA4B85CCCF62AA0A7ULL, 
            0xF0B2E8C032EF3EF4ULL, 0x0E3B71EA348D47E7ULL, 0x7B69263C68E042FEULL, 0x92645D610EE38598ULL, 
            0x8F63C8860698E6AAULL, 0xC58C12F22658573DULL, 0xD2AB84452BD9C272ULL, 0x6D9B2EF58F408605ULL, 
            0xF7DC2EAF680F9E47ULL, 0x06428D1EFF134D5DULL, 0xD26AE7FBEB7224F0ULL, 0x020A37EE5AD57386ULL, 
            0x0E116CE47F54E522ULL, 0xF86F054C72C6EC1EULL, 0xCF4458394840DDBAULL, 0x758687A281A56459ULL
        },
        {
            0x1DED2A1BCFFEFBC2ULL, 0x80FA76ADF635A436ULL, 0x309C2542242ACA29ULL, 0x28197CC59E65B112ULL, 
            0xD3DF0436186C63CAULL, 0x12F1685DA697665EULL, 0x533CD406357836D5ULL, 0xE1235BDEB7FFF49BULL, 
            0x0F82A5E9DF98081DULL, 0x8F3AAA212A12216CULL, 0xAF4A332C12E04D6BULL, 0x13F7B14716A7C0D1ULL, 
            0x20D188BA7A92490FULL, 0x4FBA9112039E4F41ULL, 0x6674CEB421B5575BULL, 0xB4DBFDDEB7DB1894ULL, 
            0x7ADDFE426C54F29AULL, 0x902BAE6705264E03ULL, 0x7DA7C9602CDC5654ULL, 0x7163AFB5E0C6BED7ULL, 
            0x9B212D1F90FF9CEEULL, 0xF6D8F35D34EC2DB8ULL, 0xD033AA79FFAA7B82ULL, 0x1C3949C4D25520EFULL, 
            0xF923EF0E73DA28F0ULL, 0xEE0A1279BFBE76ECULL, 0x703167C98AA7081AULL, 0x002C9849F068F507ULL, 
            0xD2E21E9407710CBDULL, 0x297434F0752C4F78ULL, 0x6D8452C7D0B94880ULL, 0xC360F1B1C8828A3BULL
        },
        {
            0x6A7FFEA197E7AA83ULL, 0xE179AA206CCA5095ULL, 0x52653F1218EAA094ULL, 0x778BDCE8DA09BBC4ULL, 
            0x59FFD7060B30F303ULL, 0x4E5DDD63350357D6ULL, 0x264BAE516921D6D7ULL, 0x622CA899972FFBE4ULL, 
            0x336365C62773D014ULL, 0x8A904E9947D82557ULL, 0x2F09AD1FEDE50C60ULL, 0xD41739E0C1C34A67ULL, 
            0x39D4DD04FDC7500AULL, 0x1E20F734D05EE3A9ULL, 0xEED73BF2153D34FBULL, 0x5EF97E99510DD570ULL, 
            0xB15C9506ED402ADFULL, 0x18E189C8EE3FD42FULL, 0x6CC09506F83090E4ULL, 0xD6E02092903D6392ULL, 
            0x546AAC382554373DULL, 0xF3A5584936E4234AULL, 0x0094EB4146E9EB09ULL, 0x6426D09121AE8F43ULL, 
            0xB448056C5542D6D2ULL, 0xFFE5C4BA81CD0B3EULL, 0xAC60F465888362B4ULL, 0xA69434FDC5F848AEULL, 
            0x97EF390DCC182461ULL, 0x5C1B3F852D736D62ULL, 0xF542C28D6D3D6124ULL, 0xCB5661B8171D4861ULL
        },
        {
            0x5DD03CD582EA485EULL, 0x1B5C5C1FDDD00D40ULL, 0x5B9F142B32D3BF05ULL, 0xE7D3FBEB13BAF108ULL, 
            0xCC08EBCEE37DE605ULL, 0x0B2B7CCD830A1C6BULL, 0xFCFBEDEC20285FFFULL, 0x8B422B67B25762BFULL, 
            0xF44FDCEEA33F4B9BULL, 0x98BFBD1E5176E28EULL, 0xCB8E10B144CA04B8ULL, 0xBF760AD8B7EF2F2DULL, 
            0x0396950781077B72ULL, 0xC4917812046DD734ULL, 0x92591E7E647B898BULL, 0x53E1BFE09D8F576CULL, 
            0x022BA6622752CEB4ULL, 0xC1E3783867207D85ULL, 0xA89D36AC94359F50ULL, 0x17826B3ED26B1375ULL, 
            0x354ECB4880F99464ULL, 0xEFEF266DF07419D4ULL, 0xD399A1BB1C789066ULL, 0x75F953969AB32270ULL, 
            0x7BA7485E19045B46ULL, 0x589A325944D62B63ULL, 0xFFB30B52747149BAULL, 0x57425D41BC5B2FAAULL, 
            0x2BE67118E6658ACCULL, 0x4CBB77324949E6EDULL, 0xAA0F527B9B797655ULL, 0xEE9BB19FA301EEFDULL
        },
        {
            0xD32B5F0D825EA2B4ULL, 0xD948AC447243EAF1ULL, 0xBDF941116A4F91CEULL, 0xF713F060611BE412ULL, 
            0xC695B0F5835B6599ULL, 0xB2EC364FE0B29728ULL, 0x7BA178F2ADB755E4ULL, 0xA250458A5143E027ULL, 
            0x8547922745C5D978ULL, 0xA83AD3DD07242257ULL, 0x3ADF95310892B628ULL, 0x246916494A0CFBC9ULL, 
            0x7DB3F43D900F4540ULL, 0xC222012E572D613AULL, 0x6971EF8B71914D75ULL, 0x10B4795915399423ULL, 
            0xE0467F823E5BA3CDULL, 0xCA98D075B5B6AE11ULL, 0x16B9CAF956B830EFULL, 0x997ED029392849EAULL, 
            0xF199760173A6E8F8ULL, 0x92F38478A7BE8A9DULL, 0x5FEFC9296A223289ULL, 0x8C344FCC09139F3DULL, 
            0xD4ECD4E440AD9044ULL, 0xFF0E67DB83BF12E5ULL, 0xAE4762795F109760ULL, 0x1BFD49EB6C114513ULL, 
            0xBAED220124D85932ULL, 0x89B78C88565147DCULL, 0x6687CB4D612C4E11ULL, 0xF3539A3848B5882CULL
        },
        {
            0xD28F9EB6EBF9AC41ULL, 0x8D70C45E8BD173AAULL, 0x2F6EE5263FE33B8CULL, 0xC62B7040127035CBULL, 
            0x91B81DD6D931A1E5ULL, 0xEF5A658483EAF3C5ULL, 0x8DF8CB059A822A9BULL, 0x10A8CEF08C99C891ULL, 
            0x8D10591D3FF9B2D8ULL, 0x078DDBDFB8C450F9ULL, 0x0F29AF9AD671629BULL, 0x6414EC4E6D67850EULL, 
            0x843CB9F545E5253BULL, 0x5FE0C22B3C89572BULL, 0xA35EAD6E0E24F8B9ULL, 0x1C679FF189EE3A13ULL, 
            0x375CF225BA5BE1ECULL, 0x566F7C828BED4E85ULL, 0x2697B07A6CAB24B4ULL, 0x96704D817EAEB08BULL, 
            0xE59A97BA40A89B14ULL, 0x1B8BE344A1E3D35FULL, 0x55A6A72EB4F6D9D1ULL, 0x1FBD3CF2F575B940ULL, 
            0xA861E78F1ED395DDULL, 0xF3987F4366F07870ULL, 0x820D456CB5ACE496ULL, 0x7963C1C014DF6C88ULL, 
            0x43EDA10783E4349EULL, 0x782A9B2BFDD34FF2ULL, 0x900898EB3AD67814ULL, 0x8B334E54F67965F7ULL
        }
    },
    {
        {
            0xD3782F24958F2B1EULL, 0x820762144DF053B8ULL, 0xCFDDB62F8C7E26BEULL, 0x76CA78E7E149F9F5ULL, 
            0x67D3233BA5954A01ULL, 0x62C2D587042717F3ULL, 0x804FB66D80DAC65EULL, 0xF678C6A150E04727ULL, 
            0x788F1A1F49DD8259ULL, 0xC1740C6B797F0959ULL, 0x7E42BA0645B39DB7ULL, 0x7D3BB324F7D8E9FEULL, 
            0x4A67CD371ABBA0C9ULL, 0x6D658899E28267D8ULL, 0xC438AC560CBB2BFEULL, 0x49548939EA73DC23ULL, 
            0x6B189360D628A8CFULL, 0xD2A1E7C005877199ULL, 0x4B97E0C2F20CA2AEULL, 0x9673F73EA622C38FULL, 
            0xEDE57223466A3291ULL, 0xB203F3EA4FAC0E43ULL, 0xA48DE0DF442CA932ULL, 0xA16FEAA59E49A72DULL, 
            0x90FA345916440A40ULL, 0xF418F3810E210E8CULL, 0x3698C48236D7EB6DULL, 0x6038DD25DFCF46F5ULL, 
            0xDB57AAA3427F6409ULL, 0x1B974B66B03148C1ULL, 0xC9A3563A6D0D43E2ULL, 0x319023111006D81FULL
        },
        {
            0x0FAD70074331FDBAULL, 0x9FB2F2B44C2F8EEAULL, 0xBB10B420A3BA714AULL, 0xAB715698415619E6ULL, 
            0xA692EB3F075BD0D0ULL, 0xAFC43D2278CB73A2ULL, 0x36DA114C3EAF3C28ULL, 0x36AFB4CE8BE54819ULL, 
            0x7824CF615A393D72ULL, 0x905FDD6456921A0AULL, 0x8973CD5C30ECBC3EULL, 0xE910FFD157A5C198ULL, 
            0xAFCDD334F7982876ULL, 0x4817EAF21782AF64ULL, 0xB47505A703A7CABEULL, 0x88C72B0C21E2D358ULL, 
            0x00E8524FAF67AC96ULL, 0xB4A68F901B435906ULL, 0x59F084A9ED6D9CB8ULL, 0x2C70E3DA3AA5A2F2ULL, 
            0x70EA496C6755DD46ULL, 0xDBF83CB1AAC99216ULL, 0x2FE1053F1B763B9BULL, 0xAEE9B0AC1399A4FFULL, 
            0x5C60B89908F567CEULL, 0x32D3D81C8206B64CULL, 0x9ACE376414BF5563ULL, 0x5614957FB6DDC0EFULL, 
            0xE07DB936C6F5EE1BULL, 0x2DD62F568C6E905AULL, 0xE80C7EFEE557FAD8ULL, 0x64D06B5EFCA26D51ULL
        },
        {
            0xD047669A8421E955ULL, 0x8034667771020F72ULL, 0xEFE251A04556200DULL, 0x55F66CADBA7FB3A2ULL, 
            0xA0A3C84E5CCB3AE9ULL, 0x62EACDCCF21D5337ULL, 0x66909E2D9844A608ULL, 0x3108F8CB0D92F556ULL, 
            0x58A3D9C4855E7402ULL, 0x4965AB1C33787B02ULL, 0xBEE14B80DF924205ULL, 0xD9404AA6C61B1F70ULL, 
            0x65661DE06DA674FCULL, 0x853B26129FE22406ULL, 0x99EBEDBE6E51DC55ULL, 0xE9CAEB8D34F49431ULL, 
            0x0FB76FA8CA63B858ULL, 0xF2079379A6460EA3ULL, 0x76426F6DB51768C6ULL, 0xDEC2F76E0B2FC0D2ULL, 
            0xAF564E2C792282F6ULL, 0xC85187A2569770C3ULL, 0x3EC97F1D83FDABEEULL, 0xC3D3B3AFFA9AAF96ULL, 
            0x1ECC930F8154D37BULL, 0x95F884808A3C9437ULL, 0x9683AA58FC9CDA59ULL, 0x9F1B3D53721DC0E9ULL, 
            0xB5339322FF997087ULL, 0x8DE6C2ACF7C66312ULL, 0xAF4DE1C8DFC40280ULL, 0x0D0B3846B1D75CECULL
        },
        {
            0xD3F76840DE5B6D46ULL, 0x56DE18BEA585DF13ULL, 0x9E9959DC166695DAULL, 0x8A6B76405EC8297AULL, 
            0x5290ABEE112AE607ULL, 0x892A8F965989F88CULL, 0x12E462B43FC3CA2CULL, 0xE40C06CD60257B12ULL, 
            0x0A0528C2CE1DAFA8ULL, 0xD1549D542D466519ULL, 0x376A54503F272825ULL, 0x964F2544F60C4979ULL, 
            0x4874FDAD96815B14ULL, 0xE9874D5D10C4C2FDULL, 0x9531FC3794529E47ULL, 0x86028036394D9241ULL, 
            0x65E47A6A3C944C8EULL, 0x451716B08580B11AULL, 0xD80A852DD90A4BD2ULL, 0x1A6BF2793CA49440ULL, 
            0x34C475910289FBDDULL, 0xB526D04FCD8B3E57ULL, 0x16BE5AAEB4F8B2A2ULL, 0x963BF75433638BFDULL, 
            0xA8827783CB2A20DCULL, 0x8FF57AAD9421AEFCULL, 0x839E15992B3A68BEULL, 0xD469AA45C6FC0DD9ULL, 
            0xE69E06A805AA69F1ULL, 0xABFBE843E7868136ULL, 0x12F67F93AE8615C5ULL, 0x1B485D2F23452563ULL
        },
        {
            0x0ABBB64A9BAE652EULL, 0x40ED3D258CF98609ULL, 0xAC49599E3DD42D3BULL, 0xC9F6884CEF60F843ULL, 
            0xED85C4909C7B5EB1ULL, 0xCCE2CB6B9EDD7D3FULL, 0x31AA4DCB80E7CF37ULL, 0x977E66A64BD16F2FULL, 
            0x63E23F758044E63EULL, 0x8039AE69472DFC36ULL, 0x39ED04DF7AC58DD0ULL, 0xFF6D17E76CE4686FULL, 
            0xC33CF546D0863074ULL, 0x03AF3A5D05DF2CA6ULL, 0xB3DC8A5905EA7D3BULL, 0xF08443E12C25A205ULL, 
            0x2B9EECA86EDCB73BULL, 0x7D46781767D63FD9ULL, 0x6D41B1124B7AE377ULL, 0x8423AC83764FEFB5ULL, 
            0x3569174D0870E5F2ULL, 0xB557BD3F2D1B687DULL, 0x9E8AC1E057004BBCULL, 0x36D1A4D0C93ADFB5ULL, 
            0x08D011E502BC238DULL, 0x629A2B93538CC63AULL, 0x89D16A784ED0EB07ULL, 0xE106316DF034D296ULL, 
            0xD6CA088326686EA7ULL, 0x0218FCD1C2986439ULL, 0x5BB0009042517B90ULL, 0x19C165C13ED8B0A1ULL
        },
        {
            0x7F441E2AFE0F66F3ULL, 0xDE38E012DD6107E5ULL, 0x866B992A4464D6ADULL, 0xDD7E95A7DEBED096ULL, 
            0xF28BA1625FE3D8C0ULL, 0x6045D8C7E8F25119ULL, 0xB23AFD0CDBAA167CULL, 0x6E1AEDA5B9C92977ULL, 
            0xDC1BC6EAFB7E1F70ULL, 0xFA09B4C35EAE4563ULL, 0x55F1D74CD0DBEC8DULL, 0x80B198629C798686ULL, 
            0x8E4A082EC8951B00ULL, 0xD1FA314551B7EBF4ULL, 0x3FAE2950EB6A6C83ULL, 0x7492D54A5071062BULL, 
            0xF7915B6D381007B8ULL, 0x05CD4FB354A2620BULL, 0x09AFF2244F3C57E2ULL, 0xD25076CA7BDAD3BCULL, 
            0x57828EE586B15D60ULL, 0x920A4A3994E7C827ULL, 0xD61B93BD76AA5694ULL, 0xAC02AB531FA5EB49ULL, 
            0x689C3236A6A48918ULL, 0xE2355C27416512DCULL, 0xB29E4916AD81B0D6ULL, 0x69B0641D5F51B340ULL, 
            0x0C91D08C911B34EBULL, 0x4E4A998A607CE33CULL, 0xA41CB86F7A841947ULL, 0x85E4D3966CBBF0C7ULL
        }
    },
    {
        {
            0xD3EC27175B3EE96CULL, 0xD4087C96EC5CDAFEULL, 0x0DB49811F0D3416BULL, 0x166E9A404D1054B2ULL, 
            0xC98BEFAAC9703A52ULL, 0x87ED86DA1F6EDB4BULL, 0x635D17D68D5E808BULL, 0xF32FBCE9C249E136ULL, 
            0x760EDE052D343D6CULL, 0x9D70FDAAF8AE92AFULL, 0xE3399F2ED3300C34ULL, 0x4FE89D78C59C7B58ULL, 
            0xCB36D1E83485D1AEULL, 0x447D8791153E0240ULL, 0x01627C49A22A1591ULL, 0xB23B13C8C4D2620FULL, 
            0x608944DDC3243A70ULL, 0x9F22BBF675381B7FULL, 0xF6B0F9E1454FE91BULL, 0x6897CE5E21D837B8ULL, 
            0x4322D3DA44730CA4ULL, 0xC7D027E36B4FF8AFULL, 0x8148D6E3BB89CB2CULL, 0x0FE334E461774F4AULL, 
            0x4AC0E2B63B7E51BFULL, 0xA03BD845004E4356ULL, 0x6E102F797EB1C2C0ULL, 0xC5047D19C687354CULL, 
            0x5646A9F597919921ULL, 0xD3BD7D85A0CAF960ULL, 0xDE055C968300F7FEULL, 0xD3F6C5A7C56D6A31ULL
        },
        {
            0x368125DA6F062DD3ULL, 0xB238E3490CC5CD93ULL, 0x95A0AC4FD7006083ULL, 0x34521899EC629596ULL, 
            0xEC5744D8FBF330DDULL, 0x4F8A36F6ADD171F0ULL, 0xA8884234C921175CULL, 0x4F006CF818B1FD4DULL, 
            0xE49CF12150D4738AULL, 0x310F67D751E61411ULL, 0xB4C9B380D2F54088ULL, 0x12CC27957822F886ULL, 
            0xD8CBCA0A3DD3A0F5ULL, 0xEE2B1A112272C241ULL, 0xD6D029A2CD4D4689ULL, 0x5F8EB63B7CE4ED2AULL, 
            0x2C0862017C0EAE15ULL, 0x0CC47C15056F4435ULL, 0x3FF2160D80AFE0EDULL, 0xED3A33631CA68073ULL, 
            0x07A8B58EB43E7D54ULL, 0xBAE8A42D473898C9ULL, 0x76F0A7B3E7D18C4BULL, 0xF3F1A3E27E65EB24ULL, 
            0xA7EEF9B03F1C357AULL, 0xAEAA55AE3D4C00FDULL, 0xB2E80BCDD4BF8443ULL, 0x92E072E2AA329D3EULL, 
            0xCE617C81AF1BD293ULL, 0x4F74CADE8322662DULL, 0x7E51AB0114E314C1ULL, 0x11DAF2226260EB75ULL
        },
        {
            0x5C164F4D0CD66A18ULL, 0xEE7932238B9FFAD9ULL, 0xB8A52AA61AAC01A9ULL, 0x4B6EFDD452197C3FULL, 
            0xF23CAA37B8BF08FAULL, 0x8EC9C706B7E7BBD8ULL, 0x87E4553FF04A621AULL, 0x5F47377ACBD61387ULL, 
            0xA6DC1529B054226BULL, 0x1D6D8D2368C0D7D6ULL, 0x5149D7EA27031843ULL, 0x25F3C4B5EAAF1CD2ULL, 
            0x02FC069445FAE01CULL, 0xEAD71799202F9952ULL, 0x85C5BA894B3FB67EULL, 0xB4ACEF72873C1269ULL, 
            0xA1D93DA2D333B472ULL, 0x2D2FF0DCBF4F4C42ULL, 0xC989F3F3459A60A7ULL, 0x2240A5BC67767552ULL, 
            0x73E54EFAD5C815AFULL, 0x9029D6857B51B1ECULL, 0x5D6E6CA71F8E4F0EULL, 0x86948F15CAECB7F4ULL, 
            0xB38395952BB4FEE8ULL, 0x0B32C275C6E078FEULL, 0x9D3594A34E3911B5ULL, 0x1C69BDF4038023F7ULL, 
            0xDC09D03E0061B69CULL, 0x47ED35796F8860B6ULL, 0x6C3547482B0A7152ULL, 0x3BEEE743CC174838ULL
        },
        {
            0xAC129828BDFE9A6CULL, 0xA9D3B5C92D1C2349ULL, 0x8AF3743919A1E8B9ULL, 0xF6DF9C69E14CB8AFULL, 
            0x599FF09B1D3178FDULL, 0xA3DC82B101103712ULL, 0xEC2642AEC082AF59ULL, 0x58008BE8EF00E6F1ULL, 
            0x81B0D54D61E21A59ULL, 0xF4D6865D3A18A5D7ULL, 0xF5D2FD60CF45C31DULL, 0x82821790E970D990ULL, 
            0x0CDE742538634D9CULL, 0x0809A14DA394D242ULL, 0x3F940C015814F12EULL, 0x30B4D6243960F1A2ULL, 
            0x2558A628964959A7ULL, 0xEFA020398324EA96ULL, 0x8BB6BEF404537B65ULL, 0xA3C3E69C21BA4036ULL, 
            0x90A003B431801A8AULL, 0x332F26A1E875B853ULL, 0x3801EBDEE04D9F1AULL, 0xA3DC8B2BAE374C11ULL, 
            0x4CA36364B9A6C82AULL, 0xD8371DA8746706AAULL, 0x40490BD6F6AD0B60ULL, 0xACDECA6A67BF83DBULL, 
            0x3482F5077ECD13CFULL, 0x67F96C8021F4672BULL, 0x5BDAA452EEAC9AD7ULL, 0x0EF3D31F4D05D954ULL
        },
        {
            0x86F96CE0FBC5A2CFULL, 0x4040E6BE2AD75C9EULL, 0x963B15111F380FB1ULL, 0xDE297894C6F8AC9CULL, 
            0x97D4D39A8F7E8891ULL, 0x4679D7DC9123F931ULL, 0xB0FA4060B0C01495ULL, 0x6EDF5ADBA10B0477ULL, 
            0x2581921E3B2DAB95ULL, 0x5DD135628145F208ULL, 0xC451DC2F5ACB39A2ULL, 0x081BF8589F3FD8A4ULL, 
            0x65BB0042AFF97262ULL, 0x2574BB9FA3BD5190ULL, 0x17D3BD4EDDCA48CFULL, 0xE681F635C47ED8E6ULL, 
            0xF8181E5C112A0ACBULL, 0xAD8852D282032BBFULL, 0x006ABA5D5F4B6C61ULL, 0x496D21247E346EA3ULL, 
            0x335C417CA8DEC4F6ULL, 0x53872D7444263004ULL, 0x3EEAE20D1D1929DBULL, 0xAB8E4AA7F66148A2ULL, 
            0xFFFBB8A628088F0CULL, 0xDEF970259B230F3CULL, 0x01EE50CCC3699838ULL, 0x8CB6FF3BC70EEE65ULL, 
            0xD46273CCBB5D9A10ULL, 0x47C8FACAEFF8036DULL, 0xBE8A533F8D0FBF41ULL, 0x8FC92F63DAA35662ULL
        },
        {
            0x548E4567D7BBAAB1ULL, 0xE5F83916F013259BULL, 0x3B3DE82678C888E2ULL, 0x16854981E63698E9ULL, 
            0x2F78C94A0E6D39ACULL, 0x212592F53FF9B6C1ULL, 0xFD57A3B80E68DB5FULL, 0x4A6C20D13297D890ULL, 
            0x5E6E132BBD0857AFULL, 0xFE6FF403F9B2AC56ULL, 0xAB5E88829867912CULL, 0x16EB2E0421D8326BULL, 
            0x454661AACBAF9612ULL, 0xCCC9DC693E95E8F7ULL, 0xC5DD8FCC8F0612D3ULL, 0x0CCCB01E171AFBADULL, 
            0x25792F5AC982E5BFULL, 0x46031FC6753288B9ULL, 0x5626CE289C0F4420ULL, 0x811C560ED8E7A351ULL, 
            0x710E433E3052FBDDULL, 0x511B390EDC695FBEULL, 0x3FB300403E85962FULL, 0xC0E345421A8DE5C5ULL, 
            0xF1EEF78E9ACB65A6ULL, 0x03C6A5E295C04A78ULL, 0x626296D3E4602EA5ULL, 0xB9B2952F7840858DULL, 
            0x933F59C783390141ULL, 0x0ADEE7C6A14D5DB1ULL, 0x737765303F0E7578ULL, 0xE1DC360BCA7ED01BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseCConstants = {
    0xC57D5A5FD25CBEBBULL,
    0x8DE17BC903A91944ULL,
    0x027E928E344E57AEULL,
    0xC57D5A5FD25CBEBBULL,
    0x8DE17BC903A91944ULL,
    0x027E928E344E57AEULL,
    0x5E4721569FFE104CULL,
    0x59F1E704F5EC4B34ULL,
    0x6D,
    0x25,
    0xD0,
    0x40,
    0xFC,
    0x38,
    0x51,
    0xE5
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseDSalts = {
    {
        {
            0x2DC75807EAECAE65ULL, 0xC2D9C9E7E47BA7C2ULL, 0x32EF833A98125DFDULL, 0x1F6705A730237202ULL, 
            0xB98BD9FC71C8354EULL, 0x40BB9D54758D11ECULL, 0xF9FC390517ACEDABULL, 0x206674D409083CC3ULL, 
            0x248D81785435CB7BULL, 0x67B03916116F4757ULL, 0xD9A509605C2D87C2ULL, 0x209E558E71E15850ULL, 
            0x5A0B803D54C88F8EULL, 0xBC1C9F42ED9A1AECULL, 0x7463243994847FBFULL, 0x52BD8F723164857EULL, 
            0x5F6A270990E9CCE4ULL, 0xD9B0AF8D028DDF9DULL, 0xB611201E30F94630ULL, 0xBC8C00D300E2C7E4ULL, 
            0xC9F24BBA7C4DACAEULL, 0x5CCA7CE7AD472788ULL, 0x3F1834A8B007D68CULL, 0xF04EEE3F42538802ULL, 
            0x5BE5015B80CFB5DAULL, 0x59DF3A6CB8EA28CCULL, 0x2B48B3323623FB53ULL, 0xAE4F4453E86B76CAULL, 
            0x82EF5491D3BB7DEBULL, 0xA2AC4A784C602024ULL, 0x285138E09F96C585ULL, 0xC729F57A3E41EC8CULL
        },
        {
            0x4FA2E28E4D9EF0A0ULL, 0x1A72429ADC4ACF58ULL, 0x1EE696C8951A01FBULL, 0xB3606C64B50008BAULL, 
            0x7289579EB4F99342ULL, 0x106D25752BBF1975ULL, 0xB037D61741635488ULL, 0xEA614B4B71B98BB5ULL, 
            0xE031DF548409960FULL, 0x6BFB8B7B49FB598DULL, 0xF09C5B71F83D9C9CULL, 0x8460D5FCECE73A23ULL, 
            0x82B5499E5485C8B9ULL, 0xD5384B38AA801C4DULL, 0xCF44715A96D185D5ULL, 0x05EFFC09B1FD11A0ULL, 
            0x832998A4941E24CCULL, 0x60D8C221ED20371CULL, 0x75E40EC14AA453E0ULL, 0x42F7CB21B78F3EBAULL, 
            0x7D5F7C096AE7A61BULL, 0xF8E324AD9C6A9E00ULL, 0x38649B0F10731507ULL, 0x38D5ACF2EDF26802ULL, 
            0xF2632D455EF90DEAULL, 0xED0D5BCB085D2E66ULL, 0xF1E224FFEB02FF59ULL, 0xFF4E79F65A76C866ULL, 
            0x1976ED228E68D910ULL, 0x8C3821FE1D99C0E2ULL, 0x43AEF49224EB2165ULL, 0x0129F88B72434D3CULL
        },
        {
            0x58AC994A6C1759F1ULL, 0x6BFD86BFA6EB6C6AULL, 0x9EE5D11BB73EE7EAULL, 0x0CCEF68FC6C089E3ULL, 
            0x7B6D4A6EEFE33F46ULL, 0x0B58E1ADE278EF7DULL, 0x92CEB8D6EBBBD2DBULL, 0x0C79ABBDD8D02E19ULL, 
            0x51F16FD90AEC8D7BULL, 0x64654241AAC32E66ULL, 0x524E5229B9368502ULL, 0xB503C4F0B3D3569DULL, 
            0xA0160105B426CF2BULL, 0xEBF60546E6125133ULL, 0x1063E74B58BB6AFCULL, 0x96697F06520C4F4DULL, 
            0x6292C41F843DE00BULL, 0x8F08FC62CE7FFB51ULL, 0xD33D603999014913ULL, 0x5969181C206129A6ULL, 
            0x5ADBB5E6CE13404AULL, 0x27DD1D28FF9A1ED8ULL, 0x2925FFF895DC87F8ULL, 0x9C481B3697A1F1A7ULL, 
            0x1218B8202909C5EFULL, 0x3983723522FBD2EEULL, 0xA7EBE16693019E3DULL, 0x5E88D7A1C87054ACULL, 
            0x11E6FED359468F55ULL, 0xD58029B176842CF7ULL, 0x869D5D8B99F05954ULL, 0xF7B18AF2C9FB167AULL
        },
        {
            0x6D1DB9F9CBBD5023ULL, 0xEB5015B08C95CFE5ULL, 0x73AD9642D5375F62ULL, 0xF53008DC6418DDF3ULL, 
            0x1F90C4F1B06D197EULL, 0x22D426586F465D25ULL, 0xE771C253ABAD792EULL, 0xCD73D3B86C9D89EAULL, 
            0x867EDE0F1C5F2D42ULL, 0x5F24BA3D125AAAB2ULL, 0x9752AD684E93E838ULL, 0xC80FA6DCD9D5A2F5ULL, 
            0xDAD72B5E14FF2E48ULL, 0xC85D9BC5A58CBE7DULL, 0xB9FCFB2D74E3ED73ULL, 0x401A4A1BDE986F15ULL, 
            0xC8D425F75574A3AAULL, 0x06E8762A1C4F38BEULL, 0xDC038204CBDF6B6BULL, 0x0FF8EE0CAF041728ULL, 
            0xBF39B575C7D7F728ULL, 0xA6F7E8C1690B5854ULL, 0x86359F8BEFE7D345ULL, 0x1327D757CC452FD9ULL, 
            0x5D184BB5A79C720BULL, 0x0375C9DBC360B231ULL, 0xE8E1F5C0F4966FABULL, 0x0891FDE20435EDA8ULL, 
            0x0A5DD9CCE70462FDULL, 0x740709DA6A14DB9CULL, 0x5CF91514954DB857ULL, 0x9C8B8DC02A376E15ULL
        },
        {
            0x26636954FAB6613AULL, 0x76FF33F3A3EF7F46ULL, 0x79DC48AF5C269511ULL, 0x2846D814B47CAF3EULL, 
            0xFAB69B8E2964CCEFULL, 0x2529AB8FBF0A972CULL, 0x5EE109871916ED5BULL, 0xC42912D7B43E9B50ULL, 
            0xBB71F72ABE99144BULL, 0x44C8794265D8286AULL, 0xF2FF6A6BFA5956A4ULL, 0x60DE10A4C2E3BA1EULL, 
            0xAA41876A30260B26ULL, 0x3C932DC31D08AEEDULL, 0xC234A7A9F6CCDD5FULL, 0x37914ACE0370A972ULL, 
            0xE25B27F77FDD2E8FULL, 0xEB3129ABCC1F3543ULL, 0x93025E207061F682ULL, 0x35702206065AF95DULL, 
            0xF2AE1A34A460AC91ULL, 0x696A6018DE7DF14DULL, 0x04050CF8C64AAF53ULL, 0x2DF28CB6EDF856D1ULL, 
            0x5C46AE1583A0566FULL, 0x99DBE2C3AFBC8200ULL, 0x55290C1F4BBD3B27ULL, 0x6BF039991AA03DC6ULL, 
            0x27A998EF9A951B7DULL, 0xF5665F6DB6BC3C80ULL, 0xEAE5559019223149ULL, 0xF766FF12D1FE02ACULL
        },
        {
            0x3A9B8B968CBDD885ULL, 0x084DE51E11FCF8CFULL, 0xC7B75B8531652B96ULL, 0x675546AA349D5F8EULL, 
            0xA151216DFC126C77ULL, 0x2664C143C412C1FFULL, 0xBF9E43769AD0ECB2ULL, 0xB4CBB6D1D5652427ULL, 
            0x7FD99647010D396AULL, 0x54161732EFE897B0ULL, 0x51E91552E87BC7BBULL, 0x7B3B84CA50C5B0DCULL, 
            0x2D766D6F938A072CULL, 0x86798A1CF0ED5E81ULL, 0x7BBFFD777D67E01AULL, 0xACF85FE897673206ULL, 
            0x0AB21D73A00E6D41ULL, 0xA0CFB6D918D0D446ULL, 0xC06CD31CCFE1C9FAULL, 0x4E22C68DF4878EB1ULL, 
            0xAEF324460101CA0CULL, 0x654C152D4BBADAE2ULL, 0xC02C565BA6BE8A60ULL, 0xB9D798291C29A505ULL, 
            0x646250DA40D2390AULL, 0xD26E437DF4C16D7BULL, 0x0F94FFF7564BDED5ULL, 0x31B3642891C1E0AFULL, 
            0xB8C1A5653E1743AAULL, 0x66688F7F2D992240ULL, 0xD6E811C81E437865ULL, 0xDB8069767DFFF93CULL
        }
    },
    {
        {
            0xE7B9B46F86AFD844ULL, 0x5DA906AAE6C3C60FULL, 0x781DE82B7CBACF7AULL, 0xE290298F1055124FULL, 
            0xDA1971C73C5C0BC1ULL, 0x06AA561D25722311ULL, 0xD9757049A190960FULL, 0xCAAF0A296900C9C9ULL, 
            0x48F243E98D7FC169ULL, 0x1F2E5D83748AAE71ULL, 0x795AF5E20B150AC0ULL, 0x2748667F411FFC1CULL, 
            0xE7C3449E9EF1624BULL, 0x6AAB1A838EBD76FFULL, 0x2B5DAB3897CF20B3ULL, 0x8F9A51BEF696764AULL, 
            0x3FCEA5693A90CC3AULL, 0xA38AAD8E0125B8B7ULL, 0xF74A378270D7B5E9ULL, 0x38966575DFC144ECULL, 
            0x1198A63662D7E023ULL, 0x8483BAC639F98CB9ULL, 0xAD32FFE108761F1FULL, 0x472D54635E8DAA0AULL, 
            0x800FD59C3E344EB9ULL, 0xB4B54CC078B64D06ULL, 0x2C1E49306E347186ULL, 0x6DE1606458DC2090ULL, 
            0x9DB72F06752AE12FULL, 0xCB7BE93C817CD55BULL, 0xBB026995B6DD067EULL, 0x9D4EDDF6015D2E66ULL
        },
        {
            0x17E171F4F104406EULL, 0xC87054C91B5A44B6ULL, 0x153584D5C15DBF14ULL, 0x24C0B76B4F894BEAULL, 
            0xC6AC923D55F9C28AULL, 0x4B0E5523387D0624ULL, 0x5DB3CCDC29235EA3ULL, 0xAA414EA86F02DC02ULL, 
            0xCF923A32833E4536ULL, 0x81D572C644A89D97ULL, 0xE8AF9C067BCE2F8CULL, 0xDE350DDA30587DD2ULL, 
            0x41B1C7647387AD8BULL, 0x6B0D44F71D42E5D8ULL, 0x9A18EA51644CBEF8ULL, 0x14764C85433429C2ULL, 
            0xE414F7334EF60036ULL, 0x052830D318ACFBCDULL, 0x581D0246296D7621ULL, 0xE5DFE4ED7DB4E021ULL, 
            0x9F274E312ADBCEC9ULL, 0x9D4BA872765E8BDAULL, 0x096BB97BEAFD28EFULL, 0x0CCC3E0DE132BD17ULL, 
            0x511C82E6B0E512CFULL, 0x31E0FDB683FAA7EAULL, 0x71C442CA57A28C78ULL, 0xB97F76416269A1D3ULL, 
            0xB9BE87B5A0448A87ULL, 0x0DCDF206D9B56065ULL, 0x6B53A05C60C251EBULL, 0xEDCAFF09D3AEB550ULL
        },
        {
            0x0B1A674B8A21299AULL, 0x07D8BA55A1808967ULL, 0x95C3D46173AB458BULL, 0x5DFC919C6A62303CULL, 
            0x930E98736835658AULL, 0x97C6CD323E79D7E5ULL, 0x0E445F5242618140ULL, 0x24A39506A3A181B3ULL, 
            0x1A939A11A3DC258AULL, 0x8935855561688D7FULL, 0x7A6153D62F87653DULL, 0x4C797BBE04C23002ULL, 
            0xC978A3C55456B9DDULL, 0xFF3FACBDD4EC7D3EULL, 0xEA72EFCC1ABBC80AULL, 0x88F71F4C6882DAA2ULL, 
            0x16E018CA73625CD9ULL, 0x4BF94FF2E41A31CEULL, 0xC921BD026AD67656ULL, 0x37394D00C5C4FB71ULL, 
            0x12F6C80DD10244ADULL, 0xB39B11578EC3396AULL, 0x926C0549002F7749ULL, 0xA2C9088013C06E41ULL, 
            0xE885A6D76913C38CULL, 0xE02893EFB32629CCULL, 0x3D82FEF41CF56545ULL, 0x9719B5AE24F140BFULL, 
            0xE4D658240081A730ULL, 0x1820A114D0DB171FULL, 0x9C03CC3CE6574DCDULL, 0xE70B85ABF9D81BABULL
        },
        {
            0xF8E0FF30F350D8D9ULL, 0x4641AEA679FCF83EULL, 0x277B5EEF0B8B2E03ULL, 0x796F778A03DEDAF7ULL, 
            0x163409D16524DAA9ULL, 0x063356246E0E8A33ULL, 0xA435190668602A29ULL, 0x19B9CF8D9D10DA26ULL, 
            0xC41876DA4A3452EFULL, 0xEF740F38885F5E6AULL, 0xCA900BAD0F19E045ULL, 0x6A1D5C33BF72D822ULL, 
            0x19E13F668CE8C343ULL, 0x2B9931B8974D15A6ULL, 0x7A6BD167FC363895ULL, 0x71436437C03AA994ULL, 
            0xBEC2F4329E0F172CULL, 0x04058E7F68856801ULL, 0x81029A20945EF3B9ULL, 0xE77E22C796B36994ULL, 
            0x1F4C315417AD6E5AULL, 0x806014E1D1C73D77ULL, 0x936A44563138D0F5ULL, 0xAE7D1BF7D9E5DCFAULL, 
            0x21CACF688406F89EULL, 0x4D905C31657BEA6BULL, 0x55AF71028380859BULL, 0x737E171A380460FEULL, 
            0xB618AED3727A8631ULL, 0x400D27E1E7D0D035ULL, 0x535539727E24918FULL, 0xB361A0FE190B0E55ULL
        },
        {
            0x62D0AB3B2B1D7893ULL, 0xF7120D17B26EBC21ULL, 0x956B331F3D4C5A23ULL, 0x019522A07EEB86ACULL, 
            0x21717B6438E248B7ULL, 0x99C015E578E70767ULL, 0x2493338C7060AEE9ULL, 0xF45B7785DE0B7C3FULL, 
            0x9BDC53CB53012FF9ULL, 0xBE4468F6A82A2EF9ULL, 0xDAF0B52E1F22AE21ULL, 0xD4FAA3A15EE70509ULL, 
            0xA2514DDD44617C60ULL, 0xE5D1ABD780359B37ULL, 0x9777FE7019BC5F66ULL, 0xD5291C21E34F680FULL, 
            0x11EA6069A425F371ULL, 0x68741B3833C5777AULL, 0x1152F60D2125C4A5ULL, 0x03633340E651D5DFULL, 
            0xAE30FC2B0B0CA70CULL, 0xA1A90195F92F4925ULL, 0x1833C5211B29E28FULL, 0xDD8E45C889A73FCAULL, 
            0x525FF2A0CF8B0E62ULL, 0x6AF36D0041AF358BULL, 0x155106E13F145DF8ULL, 0x405787EF952D74F2ULL, 
            0x8B8357A5A6AB6430ULL, 0x7FDC6CACA6B1B6CCULL, 0x590AB667F67CCEA8ULL, 0x06225F4BE29D39ACULL
        },
        {
            0x2C1C3B1D7265797EULL, 0xA48F8D2C7F5BB037ULL, 0x2D79AF7E54DBD8B8ULL, 0x1B724BBB18779ED1ULL, 
            0xFF40905C099BD001ULL, 0xFB701F64B4CF86A9ULL, 0x9A0317D3A9C03B5DULL, 0x9C07ED2D3AB33C3BULL, 
            0xC51E70E545D93DFDULL, 0x230732A2C11691C6ULL, 0xE78223BE84A4D875ULL, 0xF9BB2E1CB29D07BBULL, 
            0xFBCFCD1C7F59F643ULL, 0xFD2069DC0E6A9301ULL, 0x131F692749A02E38ULL, 0x10382C81A6E8BCEEULL, 
            0xDEB6DE3A34F32650ULL, 0x2C4696AF27D5F9A0ULL, 0x09B0CAB03F12F797ULL, 0xBE7BDC7FD3D7ED02ULL, 
            0x0C301CB6BF038652ULL, 0x2DF4AD8893B87670ULL, 0xB0378648BE14CED3ULL, 0x919F2444DCB09B54ULL, 
            0x91B0B6E0B8240B56ULL, 0x899F82937D90ABE9ULL, 0xC7DA4698B524BA8DULL, 0x0715228E1469D214ULL, 
            0xCAC7A80B59F522FDULL, 0x363A4094A9279879ULL, 0xD650D533A979AFD1ULL, 0x7A0579FA07376339ULL
        }
    },
    {
        {
            0xCDEDEA51943854C0ULL, 0xCED6C88B3B90ACB5ULL, 0xE83AEBE329FE5936ULL, 0xDD9F0F62CD303CD0ULL, 
            0x179F6A9811783210ULL, 0x7070CF8C0C5218BAULL, 0x5553E017E79D2756ULL, 0x9069EAB7F26DCC4CULL, 
            0x386E62C6AA2AB824ULL, 0x1E4B959576A656F2ULL, 0x8672A99B7E968D72ULL, 0x8F831C22933E8ECCULL, 
            0x653BF3EF6C47D28BULL, 0xC230A400462633DAULL, 0x95CF1E54E53FD8B2ULL, 0x5323BD20907E58C0ULL, 
            0xBED3E610B438C95AULL, 0x87552E4C928A97B7ULL, 0x78CF206E6DDA5A7EULL, 0xD2F46387BAEDD84DULL, 
            0x90CE1F514F44A147ULL, 0x6BDFFB13EAB1773EULL, 0x7D73B114DB47798AULL, 0xDE692E680FA77930ULL, 
            0x3C7ABA77CF93D267ULL, 0x0EC9CEC790F47362ULL, 0x5E5C47EA475917A5ULL, 0x9B9FDA2676107A4CULL, 
            0x50941C699929B0D2ULL, 0x2EF412F57EBEE38AULL, 0xE7F9DE0BC6787EABULL, 0x0CBF4F9497379757ULL
        },
        {
            0x73A72DAA4A4758CEULL, 0xD33CD585C72A1963ULL, 0x91094D489B157A26ULL, 0x4235352875DC6A18ULL, 
            0xB227748B2A113055ULL, 0x892F8B00B15FB3C4ULL, 0x2EBB0614B1D33F14ULL, 0x7DC40E65D35CDEABULL, 
            0xAC6C1E2897556D04ULL, 0x78B2B2E298FBB267ULL, 0x2F0F5E3AC94FB240ULL, 0x6A3F9635117965F9ULL, 
            0x104A7E183BC4E96AULL, 0x1ACE269E539EBDD9ULL, 0x5C4B633E9BCCDDC8ULL, 0x4EEFEB89EC5A35C4ULL, 
            0x40D93C89895EDCE2ULL, 0xA7F0140EC53DCAB0ULL, 0x449E09FD24E19808ULL, 0x9558DAA2A2AEAF2AULL, 
            0xB0442D61B4DCBC7CULL, 0x0D82CDB5C1115105ULL, 0x8D6B79B96FC04862ULL, 0xFC7408E182E566F4ULL, 
            0xCEBFA13CC3721B8CULL, 0x7501D6325A2ADC48ULL, 0xBEFFF62050A7C3B8ULL, 0xFA20128DD3336CFBULL, 
            0x653245D2EE96320CULL, 0xEC3B6F56074C6C54ULL, 0x909B3CC12C43C8CCULL, 0x381A690246839DD5ULL
        },
        {
            0x71BE1FAAF1A29EBFULL, 0x2B68119172D9D96CULL, 0x087633A416E134C5ULL, 0x6D0FC817D318914CULL, 
            0x7EA6FBE60A0E86D8ULL, 0x280589A016B2D74BULL, 0x8BA17D04DC70D34DULL, 0x509347D0A56A7734ULL, 
            0xAF090BA00E6F11D1ULL, 0xC58F5923031781FDULL, 0xBF5638CA9C9A7FE5ULL, 0xE1E25113419E9F6AULL, 
            0x40C2A60C975459FBULL, 0x7B6DF8BFA669A629ULL, 0xB6C32CA36B450668ULL, 0x426B729017E2DD42ULL, 
            0xB6F8EB099C6B5806ULL, 0xBDE11CD32EC00681ULL, 0x9E2662D448BD9969ULL, 0x4311C940E7D904B1ULL, 
            0x70500072AEB0713AULL, 0x2F31ED2616F9E35EULL, 0x86DA3DFBA627F441ULL, 0x883543F0F91A1A13ULL, 
            0xDED134F4E2256258ULL, 0xC7367A2C4EFBA253ULL, 0x12A54B50641B1E1DULL, 0xB6049718C424A9AFULL, 
            0x8D2296A46B0A2283ULL, 0x032FFF68B4BEECEFULL, 0x46D71D9F8EBB413FULL, 0x4D60C3B3F56A9E75ULL
        },
        {
            0xAEDC150ECC404383ULL, 0x5014F13E2901971DULL, 0xD04B141D2E83FEA5ULL, 0x5FACEC7A9C5FF99CULL, 
            0x0613BD1059A9E205ULL, 0xDF2B48EE33005188ULL, 0xA966A837BCBBD28FULL, 0xDADE4D1FC9890684ULL, 
            0x10E61C1B4AD13946ULL, 0xD31B84481CDE4A32ULL, 0xB5B78B7BDE7AB1C0ULL, 0x8A3927FCE076BB40ULL, 
            0xCC7F7E06D6EDA96DULL, 0x30249220D9F288FBULL, 0x7E26403A56216820ULL, 0xAD4A1834E04AA683ULL, 
            0xE92AD3FD266805AAULL, 0x5771BBBA3C11C3E3ULL, 0x6193D3F51DBD1768ULL, 0x91756EB6FE21768CULL, 
            0x7720AEE625F96686ULL, 0x79E24466CFEF2AE6ULL, 0x318043BAEA92679DULL, 0xCBBCAA96B3E8E02DULL, 
            0x99B5F45302DE4C69ULL, 0x33E4E5B3D88906F9ULL, 0xC947366A99B78F45ULL, 0x336766B14EF1A479ULL, 
            0x1377637BFAD2DB81ULL, 0x3B956D834502CEB4ULL, 0x43AD59AC84BD8EA3ULL, 0xE7B7722765A9A3B2ULL
        },
        {
            0xEDCF86923156E4C6ULL, 0xFCD56669FA284BBCULL, 0x5E786BCDC3F54297ULL, 0xF8D05335A05405D0ULL, 
            0xC91BA6E19AF2EA43ULL, 0x135351065EEA10AAULL, 0x433D7AF774B13E9AULL, 0xBC9FCBD5A8198683ULL, 
            0xB58C3E749988DD46ULL, 0xC6D955CE51AC5DF9ULL, 0x6A0071D405441B0EULL, 0x52A071E28595DEFFULL, 
            0x3DB9107E1E941A91ULL, 0xE963E240094DFEFBULL, 0x8ADB04E6B5F3237CULL, 0x9A88B79506D918E9ULL, 
            0x70D04C47F705EBC4ULL, 0xC30653E4A39DE8D8ULL, 0xD8A86950BCFBB3A4ULL, 0x80A4C8C25B5DB2E2ULL, 
            0x55C5F05D68D28CDBULL, 0x5CC392C42956B63AULL, 0x7ECB44552C8C6DFBULL, 0xD787058729F15C4EULL, 
            0x2331738634B80F7CULL, 0x6AC365FE7C96E28AULL, 0x1C6C729267DAFAC7ULL, 0x2E8796F406856567ULL, 
            0x656BF251FD31B5D0ULL, 0x9DA2A9DE38785D8EULL, 0x84CDD1F83265E14AULL, 0xB7D5058B6FF1129FULL
        },
        {
            0x03E17F2CBD94E1FEULL, 0x724B70274A9C24ACULL, 0xE3C211B238CCB4B6ULL, 0x7E22AFE9C2D56E41ULL, 
            0xAC38655BD24DB167ULL, 0xDB05F48617019669ULL, 0xD25911FE9DD438C8ULL, 0x47AEEC0C76AB004AULL, 
            0xBB81488C0BF33918ULL, 0x6AE78D13D45DD14FULL, 0x9923B06AEE3C9159ULL, 0x3AEBB3A4DBFCE123ULL, 
            0x6B9DFB7C32457751ULL, 0x88C12D6328079545ULL, 0x66E0095AFE910148ULL, 0xA451A363A69C6723ULL, 
            0xE44F631769F9E40EULL, 0x8D4985848DB4D857ULL, 0x7E11F7AAE296F145ULL, 0x932EF9C68ED5BA48ULL, 
            0x682E57D23462ACF5ULL, 0x5E0DFEE5974BE214ULL, 0x3BFA2064C9BE6B35ULL, 0x4A40CA4ED2C787DDULL, 
            0x63F33F4D88F6566FULL, 0x4FC4946421812326ULL, 0x295D6978A93ECAA2ULL, 0xED7B1FDD5D021248ULL, 
            0x8B028197E437B4CAULL, 0xC7FE3E59E6009F52ULL, 0x0004A47DD174425AULL, 0x24F8E8CD7BDECB91ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseDConstants = {
    0xD8B107B80537333AULL,
    0x47B208D389DDB572ULL,
    0x0E7D1313F930F42DULL,
    0xD8B107B80537333AULL,
    0x47B208D389DDB572ULL,
    0x0E7D1313F930F42DULL,
    0xE38B852A31B31C99ULL,
    0x66A7505A6E488267ULL,
    0x1E,
    0xCF,
    0x94,
    0x6B,
    0x04,
    0xF9,
    0x97,
    0x33
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseESalts = {
    {
        {
            0x78C5676507CBDA37ULL, 0x699EFAD1144B9C82ULL, 0x55F584BB2CF28DD6ULL, 0x09D717D5C18BB121ULL, 
            0x4ABE05A60ED429F0ULL, 0x65DC936C2239C167ULL, 0x9C269B04C8DDB7E5ULL, 0x767716DF26B6F457ULL, 
            0x1FE240592C33C376ULL, 0xC214EB72F1C82106ULL, 0xD14AE7DA5A11D9C0ULL, 0x08206D073DF46892ULL, 
            0xD81FC6B58935D4C0ULL, 0x659C217DA42747FFULL, 0xE96E22946686371CULL, 0xDA21212564BD2953ULL, 
            0xA370D85DB558B15CULL, 0xE4E1FF254F307491ULL, 0x8BF8CF6898ABBC16ULL, 0x8B390D05883F0C72ULL, 
            0x66004C05B1C22CA4ULL, 0x1814BA8B68E251F4ULL, 0xC9CED03146CAEECCULL, 0xA87A98BE32AB6AA7ULL, 
            0x9861873A08118740ULL, 0xD1DE19B47D472B11ULL, 0xD094741193D7C218ULL, 0xD521D2E83DBD979AULL, 
            0xD452E8DFA3D11475ULL, 0xC2CC15D95961667AULL, 0x4345EEC8392714C8ULL, 0xB0007971A8894648ULL
        },
        {
            0xDDF5533A351D3456ULL, 0xA4B61ACB0D6C90D2ULL, 0x0AEA31B7E9102F19ULL, 0x0D12526A1389C456ULL, 
            0x29194E32F9E79B31ULL, 0x8B1A23FE2815B2B9ULL, 0x3DF9D5C4B2552D7EULL, 0xC2107482F13F75C1ULL, 
            0xFD51C5507FCC6B51ULL, 0x46C63E088CFBFD4AULL, 0xADAAB9FB2AD514FDULL, 0x5BC890D4D3729CA6ULL, 
            0x64FEBCD53FE3324BULL, 0x1ACC04ED95F6881DULL, 0x6A203B5EA496B7E2ULL, 0x9CE9A5698541D774ULL, 
            0x27E0666A67D0E30AULL, 0xCE98E82969962022ULL, 0xC3D06114F407DB37ULL, 0x1EA57FD45FA7648FULL, 
            0xC61D549679FA2DFCULL, 0xE51DA00DEBA311B0ULL, 0x278997146CF27B0DULL, 0xA436F2DB51F5208CULL, 
            0x6BF9CA75297F3EFBULL, 0xB1454609C4E65771ULL, 0xA905375B6123E6AAULL, 0xE65E5FBEB9A4F663ULL, 
            0x37701C76ED2F82B4ULL, 0xB0A2A728E222AD86ULL, 0x03F3A443C75C39C3ULL, 0x218F6A0518E4BBB6ULL
        },
        {
            0x1F11133AEEE04EC1ULL, 0x2BC908588F9A528FULL, 0x1836762741A3DD15ULL, 0x74FE292E02EBD384ULL, 
            0xA606EA09F5D1F1DDULL, 0x90011E1D33BA33EBULL, 0xCEE625D8CD4A733EULL, 0x970E530662D639DCULL, 
            0x2313AC44D2B1157CULL, 0xBE545174834152D4ULL, 0xEBE3F18178BEA3D7ULL, 0xFD7E62ADAFF8E3EFULL, 
            0xDCFE4E5C4C878D6DULL, 0x385E36C7EE6FEEE0ULL, 0xEB6FED798A42CC07ULL, 0x7324333B5D77D4CFULL, 
            0xB79EC6B4DEDD7D26ULL, 0x33EE616A43758AAAULL, 0x1FF48E9FF80A79FFULL, 0xDAC4B235CED94E77ULL, 
            0x215EEBF1746B3693ULL, 0xD34FA0C6F9644D72ULL, 0xADFD7D7F49CC0913ULL, 0x01AC7D3FD3E20050ULL, 
            0x739B8F5780D67ED9ULL, 0x53C6B03FC02735F5ULL, 0x1D16306DC1D6C951ULL, 0xABD442ECF2E48BBDULL, 
            0x1D435CB348304B20ULL, 0x71974EBF7562E678ULL, 0x231DE168E9712468ULL, 0x40F63E0CFA4F7D29ULL
        },
        {
            0x82F7E5D327120D32ULL, 0xD8C005A5117FEE50ULL, 0xFD4FC24ECF09123BULL, 0x97E2DEC0E4F186F7ULL, 
            0x7DCB4C276C7E80DDULL, 0x3C843E752B09713EULL, 0x92C471EBA23DBB42ULL, 0x83EC0AD9E4FAA7B7ULL, 
            0xC31C0C73F9AA61D2ULL, 0x7312B4C658D8DCA0ULL, 0x8F18982DCBDB49B6ULL, 0xB9280C02DB6EFB70ULL, 
            0xD10CE577CF5CB001ULL, 0x91C1E843230ED54BULL, 0x31B19381852781ABULL, 0xFC8E0B35D852449BULL, 
            0x055FA631067D7ABAULL, 0xA327DF14AD1DBF2DULL, 0xD26D70CCA09A0E48ULL, 0x99347B0A5D4A3B93ULL, 
            0xA7E4034D5532EBC9ULL, 0x4A68966D38478A05ULL, 0xC16FA3A31002A1B1ULL, 0x80777D826A1E7E15ULL, 
            0xFB58E9293E8F3842ULL, 0x251C8A162CD66E53ULL, 0x08F4ADF5D931CE4BULL, 0x2B529DAAD9DD3DC7ULL, 
            0x42F92A4B0FB137BFULL, 0xD2C2D878AE17A728ULL, 0xF0AE54FB46489855ULL, 0x561188DBC32D26E3ULL
        },
        {
            0x3178439C2870EF98ULL, 0xA6D58F04826AE338ULL, 0x68A549BF62817A7EULL, 0x65A0637121885716ULL, 
            0x404BD066E5A36293ULL, 0x97CFB6393520BE02ULL, 0xC0BEEE168CA69D97ULL, 0x9374391161189A42ULL, 
            0xF1ADC9110BF81AC3ULL, 0xB989BB0E6B47BD3EULL, 0x6EFB07AEEADF9ABCULL, 0x666634365C0C11C3ULL, 
            0x0619EAD9DD36BA1AULL, 0x8F868A3FBB9D22BDULL, 0x2A8C3978E96D3429ULL, 0x03F1C8FB70AE9ECFULL, 
            0x64F13BDA57C160EAULL, 0x13F4C7427381D16AULL, 0xB0B8A8BB0911D2B1ULL, 0xC4E046225DA70FECULL, 
            0x5372EF1561098833ULL, 0xCD3EE1C09995E332ULL, 0x9838DA2341F957C4ULL, 0x4CBA4D9397FC5B3BULL, 
            0x619F66D5BB8481E1ULL, 0x950F1F33C3E50AE5ULL, 0x9CF57A5F79FC1692ULL, 0xDFA94CD93E609B5FULL, 
            0x755B4C6C9AA55BC0ULL, 0xD1839F319A4DB391ULL, 0xF1A0BFDEA7FB8EE4ULL, 0xFDC0E772A186E7EBULL
        },
        {
            0xD2FF66A5AE35C70BULL, 0x2261B2AE8E796CC2ULL, 0x8FEABF29615DB601ULL, 0x3E4B91C1212F3DFCULL, 
            0x7CBAD6CF5F904A1DULL, 0xEB4F5BED7B40FFC6ULL, 0x88F43717AF5A1288ULL, 0x89DE5DB9D29E28B8ULL, 
            0x1F0753B129BA645BULL, 0x477F0C38FF561B4FULL, 0x39A800AFDEFCBBF9ULL, 0x1B3247EB9180106AULL, 
            0x7B7AF32B4A74331CULL, 0xB5F3AB2C231902E0ULL, 0xAF54E9B3501D3964ULL, 0x49DF32E321990D34ULL, 
            0xF0491ED745272032ULL, 0x68ECD18A1C54289DULL, 0xEADF5D9CF353571AULL, 0xFB1FFBA1F8A2D979ULL, 
            0xF8E3733AAC9C8833ULL, 0xC693F32C499CB990ULL, 0xBA57F68D0DF0F048ULL, 0x0E516E239FDB7B43ULL, 
            0x791DD1CE67D32C70ULL, 0xFE7396C0B70569C0ULL, 0x889ED261C5633202ULL, 0x3B451EE9DDCE8FB6ULL, 
            0xAC756DFD26ABD545ULL, 0x4E867B24AB8F3DFCULL, 0x71A4A693F2BCA7CEULL, 0x6898E517C7679E6CULL
        }
    },
    {
        {
            0x32C1EA459868D858ULL, 0x3C08625A1DBF302EULL, 0x37034E591B7C3B4FULL, 0xF76C48B7ADC6552BULL, 
            0x0C4BE67FBB6E919DULL, 0x549A550CCFCBB2EAULL, 0xE68F008CEB7A59A8ULL, 0xC36C3E2B3514FABAULL, 
            0xBA830427933695A9ULL, 0x11D589A69A32CC51ULL, 0x9B8223A9B5FD1930ULL, 0x05F84F065C582D40ULL, 
            0x009EF51B4FB1C3BEULL, 0x83E6604CAEA575ECULL, 0xACFC883597B4B9A0ULL, 0x75ED809ADF34D528ULL, 
            0x1399A378FC4DB8CBULL, 0xCC066B7BFCB6E77BULL, 0xD99F04BD5C5C76B5ULL, 0xFD662F8C8525F5FBULL, 
            0x0E89E4B06753FA9EULL, 0x25DF11EB49E59B71ULL, 0xC7AE74159387C80AULL, 0xB6B4FAC7AEAEE923ULL, 
            0xD551FF3581626C9DULL, 0x0A48FCD61934EEC0ULL, 0xF616531F2C09415EULL, 0x44387966CB13BA25ULL, 
            0xAEB9B1C6FC3E95C3ULL, 0x4656CD6FF8FC5632ULL, 0x3044933A508215C8ULL, 0x1349D7087369BCA7ULL
        },
        {
            0x2990CDA4271D0EADULL, 0xFFB3574BEB273BFDULL, 0x9439A2036F96842BULL, 0x9FE227FAB3F7AACEULL, 
            0x470496E16BD97A6DULL, 0xA329A3DDE10524EAULL, 0x907DABCD53B5046FULL, 0x877847F02DB018CDULL, 
            0x85DE9F64592A8DFDULL, 0xF64ECF0B7AE50C3DULL, 0x7AF64CBA1F3BB71EULL, 0x6ECC5027855E411BULL, 
            0x1FFF20629820B19EULL, 0xEA6D4505BADA4641ULL, 0x430017248464531FULL, 0xB42AF548F31604BEULL, 
            0x50E0948547F9DC3AULL, 0xFD8A14FD61403BF7ULL, 0xA749E2B230E0E8A3ULL, 0x9CB4CF13B174FEAFULL, 
            0x66484810C15533D6ULL, 0xACE7F40BCC60C96EULL, 0xC28CA33FF1928A9BULL, 0x2102B3D1C4378C13ULL, 
            0x00CC7393EDE2C932ULL, 0x89E05FA7F314F60EULL, 0x2DDB1D65FC6FFF92ULL, 0x30196D695F8A76F6ULL, 
            0xC87B760BBB8A0A9FULL, 0x794A92E2BE451BB8ULL, 0xE2765123A45128C4ULL, 0x38E5E23FBB339390ULL
        },
        {
            0x05FF409963F72694ULL, 0xB42A93032BA07445ULL, 0x2C4597194F93889EULL, 0xB6EAF08B9DC4F46EULL, 
            0x4F1C5008277AC5FCULL, 0x484423DE1520B739ULL, 0x7D7D5F4D2D5BB9ECULL, 0x4F426B8903147E29ULL, 
            0xF5895DBF89744388ULL, 0x659DB238CEE6A719ULL, 0xFA934F8789DAF39AULL, 0x61F4B67BBBE1D7B1ULL, 
            0x4BD860FE1835B5A0ULL, 0x7EE4C285F407DD0BULL, 0x04C1E968DD5EDBB7ULL, 0xC8186BF0AF1730DDULL, 
            0x2429859025E2A835ULL, 0x1B50994356B50140ULL, 0xA969B3380986162EULL, 0x3F18F0CF057D5D1BULL, 
            0xB7B4057A9E74D772ULL, 0xD85727A04C56B0F3ULL, 0xDC8507F75ADB48C7ULL, 0x6B84009E98109DFCULL, 
            0xDAF6E4DB21BA282EULL, 0x227641711205F73DULL, 0xBCD6281C9183F339ULL, 0x317CC31854FE9FA6ULL, 
            0xCC0BA7F15ADBFF3BULL, 0x6CA1F2675A02CE82ULL, 0x53A847390F50BE6DULL, 0xD0579FAFA8AC2619ULL
        },
        {
            0xB1712E9BF48E5241ULL, 0x8E21BC74DC6C4AE3ULL, 0x095F3AA770C582BCULL, 0x9121579AFC0B709FULL, 
            0xACF22663CA785BCEULL, 0x55E03C81297B4A19ULL, 0x80DABBA9E34F125AULL, 0x18E08B500F756D83ULL, 
            0xC32BD25DF95D52DBULL, 0x21C3BF1FAA5C32D6ULL, 0x7527A66CBE9E5C8EULL, 0xA54C5C4DEE20437BULL, 
            0xDA8238EA9404AD3AULL, 0x38BCD0077B04D31CULL, 0x0F3890D6CF30007DULL, 0x33C66A32F44D9CB9ULL, 
            0x3CFDB1FBCCD04B44ULL, 0xE1B5298F90BDFBE4ULL, 0x518B057AC9AB5E61ULL, 0x95D8C392B8BC5AC7ULL, 
            0xEE4ABBD30F10E091ULL, 0xF8136AECDE1529FFULL, 0xF1240EF5D3D672BFULL, 0x8C207B0671045C14ULL, 
            0xD5FCB6123E675536ULL, 0x609CB1C699E60F7CULL, 0xBE2F63F29BFE744AULL, 0xB6C5967734B5A49EULL, 
            0x414DF6E155EBF8F4ULL, 0x82B301D261D894E1ULL, 0x1F3C17B75796175BULL, 0x3DD8114D6E433D27ULL
        },
        {
            0x9F111DA56AEBDE42ULL, 0x89E81922175AC9CAULL, 0x777E4A79C2DE4444ULL, 0xA64813AE82DFD38FULL, 
            0x0EBCBCDCF5D3204AULL, 0x58FEAF1B3FADA38BULL, 0xBBD0CB5FDFF9053CULL, 0x34C21CC915976436ULL, 
            0xFACC410954F5BF6EULL, 0x8FAF679B825C2741ULL, 0xE4A195258BCCCF96ULL, 0x7682BC47F1A0800DULL, 
            0x1CD7E99129CAA75FULL, 0x842948EA91AD1C54ULL, 0x13731A6689644510ULL, 0x900A89DF9385CFDAULL, 
            0xDEA5C8D9E2163982ULL, 0xD70575D9A870512CULL, 0x625F10B26B00AC22ULL, 0xE1F786836318653BULL, 
            0x40EA0A0F9057E735ULL, 0x70ACFD80E1ECBEB7ULL, 0xE3CD2C7C6021F289ULL, 0x90EA2204E064C4E4ULL, 
            0xE249DC48A52B4E1EULL, 0x4DE4E517ECEE9CFDULL, 0x6E789BA0CECCBC1DULL, 0xB60DDE3CB702E9C0ULL, 
            0xE058E7D26423935DULL, 0x85729E065E92AB7AULL, 0x434A600F321D7682ULL, 0x122A0E125F1F1900ULL
        },
        {
            0x768695C930550E30ULL, 0x56562CFB59C8C9DAULL, 0x1621C7D7036190C3ULL, 0x0FC7348A824C8D30ULL, 
            0xE55F9E2530702756ULL, 0xF30E0304F4670A98ULL, 0xE187193912B62FCCULL, 0x7249EC887211A9B7ULL, 
            0x1AAFE885A7BE73BDULL, 0xD54390B1D491E349ULL, 0xEF3AB470DA35D517ULL, 0x139EF60A664AE17CULL, 
            0x4820E9B680A35BEAULL, 0x2351E1999D3E4C9FULL, 0xCFC5B6DA6176C44EULL, 0x2F6204A0F3002825ULL, 
            0x75EFFFEF2D4F58C0ULL, 0xAD5D6684C6195DE5ULL, 0xB33C41D684C4D4F9ULL, 0x1C7D05ABDEBC6E16ULL, 
            0x208C048FF0C2F2C9ULL, 0x7E6ECD480BA5F540ULL, 0x5CCFE06B38C1061AULL, 0x9815CB070E686A6DULL, 
            0x9EE70A3A0C716BA7ULL, 0x5C966EF787E189DDULL, 0x4789AC7C86814057ULL, 0xD74A85CDD018B958ULL, 
            0x48C93F1C1BA12523ULL, 0xE86A85EF02CC289FULL, 0x0E20EE97C969D0E8ULL, 0x488091614CD6B2AEULL
        }
    },
    {
        {
            0xB383FAB0B40C8500ULL, 0xF354FF51BE2DF201ULL, 0x195A10A325E2F1A3ULL, 0x85C2830E922341E5ULL, 
            0x4DB8F87B209F1702ULL, 0x6310FAF771521CA5ULL, 0x93E2F9ECC070E258ULL, 0xCDFE50967A8B96A4ULL, 
            0xD2132F59F587CF34ULL, 0xABC0FC3B2279AD7DULL, 0xBB6D64E91FF33166ULL, 0x63DEE4C76610850CULL, 
            0xF7DE252AE06A9609ULL, 0x4645B0B65D15F319ULL, 0x5CBF4E68F5F2D326ULL, 0x26DDF8EB67B790B3ULL, 
            0xD9C3FF16D98CC2D2ULL, 0x194D0D2B7C668532ULL, 0x1A104300FA15CBCAULL, 0xAA480F300FB6461DULL, 
            0x20974E1751678F45ULL, 0xBC79B5C23A9097E0ULL, 0xEF33DD3B56DF54B4ULL, 0x894E8F0965BB153DULL, 
            0xE2DB64D1F90D624AULL, 0xE0B36A397102A613ULL, 0x6F99299D4ACFB83AULL, 0x3C558A1226D35D78ULL, 
            0xA002DCEBF23AE856ULL, 0x90A07433296B86C6ULL, 0xEAD3FD44396B9C6AULL, 0x0516250225797072ULL
        },
        {
            0xA24853AFDD60FC99ULL, 0x064ED68FF64904CFULL, 0x31BCA7A3AD05BD31ULL, 0x34CC0FF8A3BDD297ULL, 
            0x094743F3776E607AULL, 0x978BB3FC100FE8A8ULL, 0x2C9D9019018A01D1ULL, 0x34B548C718209AFDULL, 
            0xD588EF83A8587EE4ULL, 0x064360D57837EB62ULL, 0x780F59199BB5DF85ULL, 0x6E529A69865FF0CDULL, 
            0xD9E2A0304C5C91C9ULL, 0x15D3F3EA529FC9DCULL, 0xDB98B596DB60F2FFULL, 0xA163716942AE3249ULL, 
            0x8EF215CDB86B3BD5ULL, 0x89F2FB3648F50529ULL, 0x6F6167E612EF374FULL, 0xAF31DB9C9E3AEE78ULL, 
            0x90CC688C0D944697ULL, 0x89DF78BD75897565ULL, 0xAB1700FC90E1A92EULL, 0x7F55C4DB88F08BAAULL, 
            0x332E91DDADB92F5EULL, 0xCFBFC49A4EC2EED5ULL, 0x44A57A692F44AE71ULL, 0xD6C0DEF12379DA0EULL, 
            0x61087BF89FEF7FD4ULL, 0x82DE026CD399F88DULL, 0x2BC6DA4A673AFE9DULL, 0xB2FFA972BF863F23ULL
        },
        {
            0xE8C575150952212EULL, 0x68F9482AF5F55F1DULL, 0x73CA5F145B28D1AAULL, 0x49FE2C3575D98A84ULL, 
            0x2F8684869281BCDDULL, 0x594E5E16DD066213ULL, 0x809DD221BE2384C3ULL, 0xD65D8A36CA0A5B1FULL, 
            0x282EB81D260F354BULL, 0xB553E2B7287B08FFULL, 0xA9DC45FA18CBE6B3ULL, 0x58AD3241DA088A71ULL, 
            0xDEB0FF133C0B99B3ULL, 0xD19ADAD9FC96A77EULL, 0x9B2A2846A8D71B4FULL, 0x7EECE2C70DF04A29ULL, 
            0xE90B5A4FE4EC2162ULL, 0x29C76060F7CF2854ULL, 0x6FEFD9842AE1F8FCULL, 0x9742CD0FACEABDE8ULL, 
            0xF0FAC5D371452BA0ULL, 0x8BE22097DC466CF8ULL, 0x818C37E34C6346FBULL, 0x9E16C90A4416B7ABULL, 
            0x12AA28E7970BACE3ULL, 0x5D7B792D95AF28A3ULL, 0x826D8B7E30EB49E7ULL, 0x90CDA8B6D50C60B0ULL, 
            0x8414EB4EC3DBDAD1ULL, 0x105C1316D9DDDF6EULL, 0xD5EC2F3B29BC7CEAULL, 0x62A4F7B8693D0158ULL
        },
        {
            0x80AD6B2662517052ULL, 0xC4C797A4882AD54FULL, 0x1E93AB30180AB712ULL, 0x60B765A7DE74D871ULL, 
            0x6DA9EAA95EFE24E2ULL, 0xC63C2309045FCDF8ULL, 0x0C646FC3421E1301ULL, 0xC402F651D03277ADULL, 
            0x993C2B9521125A3CULL, 0xCB106B33D4C27037ULL, 0x391F7B3C4E5C37D4ULL, 0x537894E3619DB52EULL, 
            0x79CD4DE5472986DCULL, 0x1BDDB936301EC2DAULL, 0xF721AB2C0210F682ULL, 0xADC488297F1BEF30ULL, 
            0xAD6AC0AE2671A97BULL, 0x70AD7E7D92FED8F0ULL, 0x45983883ED8DCDC1ULL, 0x64BAF32F57E2872CULL, 
            0x508FD30585AF216AULL, 0x139A0F01236A6C12ULL, 0x6017DA544425F215ULL, 0x2203BCBA3F2A05A3ULL, 
            0x5FD89AEF6D6FDBF1ULL, 0x67EA27E830408052ULL, 0x03192C334F657B79ULL, 0xD57720D3483306E5ULL, 
            0xF2185C20EAB2F747ULL, 0x458891CFDB447B9AULL, 0xE26921D5780CA6A1ULL, 0x7E221CAC0AD72E10ULL
        },
        {
            0x6DEF1D9BED6D9717ULL, 0x31A4F7569195A474ULL, 0x6B46B995CC467C8EULL, 0x683B5CB6E1EAA32AULL, 
            0x0A0CDE79D7E4F97FULL, 0xEE25E1143EC9EE3FULL, 0xD0AC3C3C1A9127CAULL, 0x98C9A01A98BB7687ULL, 
            0x194F7AF239A22E05ULL, 0xCE5E55B7EEF3E3AAULL, 0x21DC76BF55880F49ULL, 0x95ADE2EB0B551551ULL, 
            0xEC69E87747545033ULL, 0x895EB2E8C366B4AFULL, 0xC16610D35102D808ULL, 0x6251D3F779E9B28CULL, 
            0x29D2D8FA4402A799ULL, 0xBAF0DBEDE2A5117AULL, 0x1C22685B6546BBACULL, 0x55C0D6F537663DCCULL, 
            0x2D5C98235F267A30ULL, 0xD045774B345EE260ULL, 0x40D6583F7101C203ULL, 0xB242B7CB5C014B0BULL, 
            0x6BFA0F059DCB95F8ULL, 0x0C17881A591D0EE1ULL, 0x90B4338A42E59CB7ULL, 0x3A99F813255652B6ULL, 
            0xAABB8A741AC44C3DULL, 0x592E2002C3139D69ULL, 0xC7127C43C335B78EULL, 0x66792035BEF15161ULL
        },
        {
            0x49F70092D938ECC9ULL, 0x4A338CB9E59C6331ULL, 0x8E35EE00D016E61EULL, 0x6ECC94FB37185E05ULL, 
            0xB9458E0F2B803295ULL, 0x07BA851782EC499EULL, 0x0AB9F53D166A629DULL, 0x75B9191887FA2E54ULL, 
            0xF8568DDC8A1448F7ULL, 0xEC8D60D3299ABB4DULL, 0xC3295D419F8DDBACULL, 0xB21050E2BFF9ED54ULL, 
            0xBCC260710DC50116ULL, 0xE4A561D09D85F3E9ULL, 0x8D3CF3FEEDDD8CF8ULL, 0xF9F84FDA3D6377BCULL, 
            0x84B19E9C85C869A1ULL, 0x2B7C624E5C7C3FEAULL, 0x2F3C4EB02B74734FULL, 0x05AE08677B61B01FULL, 
            0x1387196F5A7203D0ULL, 0x9BE9E97E2D053372ULL, 0x39FE9DDB79297934ULL, 0x07D31D1157F5EEF0ULL, 
            0x1938C3399563AD63ULL, 0x634FFAA08F27C624ULL, 0x3CA079694A60AC35ULL, 0x601E733959155E38ULL, 
            0x13EDE87F13AB97B6ULL, 0xD28ABCE4EDC294D4ULL, 0x9DB5819167587A00ULL, 0x4EBB00AAEFCF4AE0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseEConstants = {
    0xE64E8AC22CDA460CULL,
    0xE6F59F907B135E4BULL,
    0x6448E85381B4BD8CULL,
    0xE64E8AC22CDA460CULL,
    0xE6F59F907B135E4BULL,
    0x6448E85381B4BD8CULL,
    0xBDE7CB0C746E1741ULL,
    0x687FFE45AE652C5CULL,
    0x88,
    0x93,
    0x9E,
    0x27,
    0x1A,
    0x67,
    0x4E,
    0x63
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseFSalts = {
    {
        {
            0x3F1D49EEA5A01EDDULL, 0xC70B66D0E7A6E720ULL, 0xAA634F63BFA65672ULL, 0xE6EB3E7E28292867ULL, 
            0xB1D865A6FB1746CCULL, 0xB2001D6836E86EFBULL, 0x22B339C4371AD6FEULL, 0x64AEB768E9D7DD76ULL, 
            0x1CC0A9B9F4710513ULL, 0x2BC625B774B50F35ULL, 0x7A91CB8B4863DBDAULL, 0x636BA3F812668BC5ULL, 
            0xD34173BA72D862BBULL, 0xBB0A076A4EA65779ULL, 0x38A2A78C905BD5C2ULL, 0xE0E6DCBACB98B4FBULL, 
            0xE9958ABA7A85B533ULL, 0x31B5D385FE83C4BFULL, 0x9886CCB0E7B73790ULL, 0x59476820555FD841ULL, 
            0xED9B723D0C248C93ULL, 0xFA2880FBC9AE9B2DULL, 0x072F3CC27B180D12ULL, 0x0816DA3D2BE51F84ULL, 
            0x0314F4B60CCE34D1ULL, 0xB466DBE18A6B9BC7ULL, 0x29687F362B63D607ULL, 0x4F8DFACCFFF63703ULL, 
            0x7C3621483BEA782AULL, 0xB581839AE84D5FC0ULL, 0xD4E3BBA9D8989CBAULL, 0x7E8F5270ED36D0E1ULL
        },
        {
            0x3406E7DEDEC9071EULL, 0x71F9A6C2EEBD0BD9ULL, 0xDC2A648FD0594137ULL, 0x8F34AC464EA309DFULL, 
            0xBA939A1DE9A37EDFULL, 0x802629987D082B31ULL, 0x335DAAAD780B1947ULL, 0x1192B74F96094DA0ULL, 
            0x6C5C960EAFD46EC3ULL, 0x8BB1D8634F71B710ULL, 0x5BE851DEF267D7C6ULL, 0x0AD828CB0A2989EDULL, 
            0xF5437743A9194057ULL, 0x5045476652604972ULL, 0x9D87BAF46637E953ULL, 0xCB4A2CB606A10A96ULL, 
            0x7348BA99C3610405ULL, 0xFFC7908CF637B86AULL, 0xFE871A9C4073F4E0ULL, 0x5413F8C34DC562B5ULL, 
            0x47FB0070C219C992ULL, 0x4099716BF26C0EF4ULL, 0x968FA0371BB42B07ULL, 0xCB9B82223B131DC6ULL, 
            0x95BED9BB9DED6CB5ULL, 0x8852E5A5AA2C2203ULL, 0xF11168CC3A4660C1ULL, 0x21680D5358BB9CC6ULL, 
            0x5CFDE72185AEE3AFULL, 0xD264F8A44F136915ULL, 0x3BABFE2F82096D29ULL, 0x98A0C0D544E63272ULL
        },
        {
            0x808AD1F9127B3E02ULL, 0x41F47D3DFE77D975ULL, 0xFCD20C472C4BBB00ULL, 0xD940DA834E2A3253ULL, 
            0x89896B2034BB1204ULL, 0x35BC466F437FC320ULL, 0xFC612A3B0160CEBDULL, 0x00C5B2DEA534B52BULL, 
            0x325C43B06BACF52DULL, 0x5DA6926B8B54BB7BULL, 0xF78886CEAB298074ULL, 0xCD3DF4B5F48E19E1ULL, 
            0x702ADEC2B3B93315ULL, 0xC86FE9B9EC68569BULL, 0x6D457899B7EC8944ULL, 0x01E0FD8268CD37E0ULL, 
            0x095FAD1D97D0AD31ULL, 0xE01A6AA845DF37A6ULL, 0x08203E6E24719098ULL, 0x0944ABB727066A8DULL, 
            0xF23E1A425EE0A2F6ULL, 0x0D267C6DE77008FFULL, 0x2F751E631A0D80C7ULL, 0xFCBE61D4A3901316ULL, 
            0xE618080F4236D2EDULL, 0x22013B27D7D259C2ULL, 0x4FF162E08AFAC142ULL, 0x7F237879CBFC9AFAULL, 
            0xBA9FE3A0D38ED9E7ULL, 0x83EAC520B407038CULL, 0x43970EFB79917F9DULL, 0xA3D3A6A3C5338C14ULL
        },
        {
            0x63B002E70F3D840AULL, 0x281ECA407AE10E91ULL, 0xD89D49B53A47631FULL, 0xA59D14C5081CCB9AULL, 
            0x173F9732DD6A54EFULL, 0x799C5F29E479343BULL, 0x0FE9D752DBBA7693ULL, 0x0838F1BDC784F484ULL, 
            0xE0BFEAAE59F5F36EULL, 0x52AAD24E2149ACF2ULL, 0x9905BAD185FF0D37ULL, 0xCCF083639318A293ULL, 
            0x4D9BE7BBB72823DDULL, 0x479FC0A9910E3B7CULL, 0x3C62FAA69A5E6946ULL, 0x473675742C0732D6ULL, 
            0x1D6E9DE1807D6CA6ULL, 0xD866A11143ABC4D2ULL, 0x48634408A4A26A21ULL, 0x0C3784F004126046ULL, 
            0x9F9D17C42F6AA6FCULL, 0xF3927F85A669C63EULL, 0xE5C85541BBF3AE32ULL, 0x6ECE1C2F2CB5CEC7ULL, 
            0x3BD85CAF08C8D8E7ULL, 0xE204609993F01CB7ULL, 0xEE79EE799A4FA331ULL, 0xDCA2BA69EE5390AEULL, 
            0xEFF94BA754C35ECAULL, 0xFD710CDC1A5523FDULL, 0x513A60B03CA8CD21ULL, 0x1955DA573976F0E2ULL
        },
        {
            0x100DB63AFF1D5D2DULL, 0xD6DB738E3421E124ULL, 0x354B21FCD994E7C7ULL, 0x46A5FC82E54039B2ULL, 
            0xCF55E80F42A86C4FULL, 0x68C2D67A4E9DC667ULL, 0x6D92B582BBD49CEBULL, 0x9E1AA0896CC23909ULL, 
            0x5F43EC6D50C15405ULL, 0xCA3C20C20BDBB8EDULL, 0x9D71EFD1BDF954D4ULL, 0xCF994B2ACAF02646ULL, 
            0x26A6103AE00AE084ULL, 0x8AB478AEDFC8559AULL, 0xFE58C9D558BC3C9AULL, 0x213972179185EFEAULL, 
            0x6E9262CEF8DC8D1AULL, 0x2F489EF19EF1BE66ULL, 0xACF1342E418127A2ULL, 0x18CE0F6FD2C272D7ULL, 
            0xD6505E1D035A3A62ULL, 0xCF88FDF590B3A020ULL, 0x701335637375DF16ULL, 0xFA7CAE6749A902AFULL, 
            0xF1393C27CA857E1CULL, 0x66D5E3ED22EF0FCBULL, 0x72F87E7DB06B6C3BULL, 0x9E98BD12670FE227ULL, 
            0x00D753ABD2A0F16CULL, 0x6C6C28499FB52DB9ULL, 0x31902CD9054B3B85ULL, 0xF7053F4C1846749FULL
        },
        {
            0xEA69DD9E4CBCD951ULL, 0x841DCDC8CCAFDA4CULL, 0x769EA472B84B8786ULL, 0xA0FF211C6CD5FFB8ULL, 
            0x2214B4F7A1A35F0BULL, 0x31AF8AF233A31A84ULL, 0x86F5E42A3EFFD3C3ULL, 0xC9E7CE0BF0CD021CULL, 
            0x88B648C658E77752ULL, 0x61D542A2DCBCA437ULL, 0x0A53FB6EFE46871AULL, 0x215F696FC2CC5531ULL, 
            0xC2DF83BD938393B4ULL, 0x484A8F530501DE39ULL, 0x624252B7DD85A8C5ULL, 0xF6A06FD5B3DDA132ULL, 
            0xAD166171A2C63803ULL, 0xDCBF7E424BA3B4F9ULL, 0xE1177CB0A815A469ULL, 0x7C4A986919797A51ULL, 
            0x405BA8706C284AF2ULL, 0xCB4F6944A6FB4919ULL, 0x6F55E3B78A2C0B21ULL, 0x7B22238FBB9C835EULL, 
            0x5FFF580ADED54332ULL, 0x427464DC38F98B2DULL, 0x428DFEE9C5A955E2ULL, 0x22783F81B234A541ULL, 
            0x1640E08A9859592EULL, 0xBA9CDF42EA2C47F0ULL, 0x3A141AD6DD04F317ULL, 0x4EFBC442F74F9195ULL
        }
    },
    {
        {
            0xA9575B03C3353D6CULL, 0x9FA0B6728857A867ULL, 0xB08FFB2531E2B385ULL, 0x6A80D3E4F88950A1ULL, 
            0x2220D513A8C5B710ULL, 0xCDF8FF45C23BB505ULL, 0x6FC903C9563737B4ULL, 0x35B42903B244B44FULL, 
            0xEC39490A38B8547AULL, 0x936F5EE756104547ULL, 0x3511B3AB06655771ULL, 0x150CE2A8D55028CBULL, 
            0x95D53F2255FD1A75ULL, 0xADD3C9CBCB7217E0ULL, 0xEE54921F2B72D18DULL, 0xE8D17CEC6F06601CULL, 
            0x1352808BC49ABA88ULL, 0xB02674F75BBFCD62ULL, 0x26C753DF157D72FBULL, 0xBF62960A949300F3ULL, 
            0xE7AA8D898CDFC3C2ULL, 0xC9B84717BA487618ULL, 0x595BF4C7E4D0CE8BULL, 0x30D32CD466210672ULL, 
            0xD1B4430B440AAD4BULL, 0xD194D8F5E8E2699DULL, 0xB24635C7DD5D58F3ULL, 0x3B6E7E0B8F515A17ULL, 
            0x4192784E95BBD5ECULL, 0x12C8094196605C9DULL, 0x8C05502D6C16DE91ULL, 0x0D2F637A22BB2320ULL
        },
        {
            0x623563225418BF69ULL, 0xDE4A297D2A89E6EAULL, 0x4C95633C0F031147ULL, 0xE7A9F7BAA3259486ULL, 
            0x5176DB95DC34B1C2ULL, 0x60C6FD363DC71AA6ULL, 0x1B1293FD593A3653ULL, 0x78ADBB13BEC6701BULL, 
            0x7DC73D09BEDC78AAULL, 0x4AEA78294193C96AULL, 0x0DD18B9185041687ULL, 0xBCE252FFAF57F030ULL, 
            0xB19B682CA89875CBULL, 0x0BD0120FE740C578ULL, 0xB2DAC6E0020098F4ULL, 0x29BF916404CA9754ULL, 
            0x8DE32A7AA7B28F1BULL, 0x930FBCBAEA641514ULL, 0xCF5865CF0DB47DD5ULL, 0x3DD591D4FE5CD3EEULL, 
            0x4BED25CBDEDA1A60ULL, 0x8688EB5CBBA50619ULL, 0xF375186C016301A4ULL, 0x46A21E568D56827AULL, 
            0x1B4D36466970AE7CULL, 0xA1CB5E08AA2E3552ULL, 0x396F79C68932FAAFULL, 0xCC82C8ACB491A519ULL, 
            0x379E5E38849A4A29ULL, 0xC8CA7BAEFBAD4A1AULL, 0xA7D8CEA5FC825863ULL, 0xFE1B7D42CD71A171ULL
        },
        {
            0x413A34BA45E0920DULL, 0x863D1D5BC0394420ULL, 0x62C1DEBA8E948D3AULL, 0x0D1859DE55B7B7C7ULL, 
            0xDAB0139BA45E3EFBULL, 0x9474B7920C4F2250ULL, 0x5D7EA2BBC8BB7641ULL, 0x3CC9CB88DA7C7A44ULL, 
            0xD34C4A2DFD84B6A3ULL, 0xB1A664E364FFF50EULL, 0x532A5624E3254F2AULL, 0x28ACF8520312C32CULL, 
            0xC716107422C0DBC1ULL, 0xB5804A78A619B5C0ULL, 0x0BD2480F7F6D39CDULL, 0xABAF5AF8CC309964ULL, 
            0x07A32DCF30A26558ULL, 0x27968AB1A0899302ULL, 0x05E678669D5F19C0ULL, 0x0170BEB674B4238EULL, 
            0x0D100684D284BF14ULL, 0x25934CE8E46E071CULL, 0x36ECF75B4BD9E156ULL, 0x18CD85AC6FA6281CULL, 
            0x0A124071EC8C1D4EULL, 0x8BA639DE618670ADULL, 0xF4D932A2D792A15BULL, 0x6CA92FDA006389D7ULL, 
            0x1179EF2D5E18CA1EULL, 0xBDA3EC7DF9CEA566ULL, 0x962199C5B8C81253ULL, 0xB0AC3D2A66303408ULL
        },
        {
            0xB9DF34AFDC5F7542ULL, 0x0F6D2618B0E5C721ULL, 0x425E7FDB2F540CD8ULL, 0xF7DC1C2603BDBBB5ULL, 
            0x0E63678F543DE82BULL, 0xC7EC0EEA6CC3AA27ULL, 0xB0D62BAA80715AE0ULL, 0xB8FEBAE3C38281DBULL, 
            0xB23B1B3D381A3940ULL, 0x61AF521D5A26B01BULL, 0xB458B3FC9584FB78ULL, 0xB59A5666C814F2E7ULL, 
            0xF76D91D4EEC7AB3AULL, 0x036C02C0661D4F30ULL, 0x822CDFA3C8473233ULL, 0x8691CB3052C5548FULL, 
            0x6256231DBE7DDE36ULL, 0x519060449E850B5BULL, 0x51262AF66758E730ULL, 0x9239CEE2654F03E7ULL, 
            0xBB517A8328E04B14ULL, 0x143025923F0B0363ULL, 0xFAEBFEE11A92C14EULL, 0x90C102580CD24D2BULL, 
            0xCAD7C8D7C96985A6ULL, 0xFF9F09910CFEE2CEULL, 0x0BF30E94BEF0E696ULL, 0x12C5EBE69C27FA92ULL, 
            0x72B07B4805BBAFDBULL, 0x24C132FE25482DDEULL, 0xF89E582B152D9962ULL, 0xAE2C6672D7A0AB7CULL
        },
        {
            0x6FEE4BDEB03E7BA0ULL, 0x9E8A5BF9B5A4B258ULL, 0x15ADA86DC65D71ECULL, 0x4A8E9143FCCA947BULL, 
            0x5C82608FB84A9BDAULL, 0xFC1B698884D9FDB7ULL, 0xBC3DDD61378C1E09ULL, 0xF72B19983B4BA8ADULL, 
            0x03B40E72878206E4ULL, 0x38877B2294E3D97AULL, 0xB3F1EF40F9021DF0ULL, 0x475502546CD53003ULL, 
            0x784223A3449BFA78ULL, 0xA6AB6519E265B957ULL, 0x8FC2A327D9000717ULL, 0xB0E577ACB5D0D9ACULL, 
            0x62334A222496260CULL, 0x73774F92BDC0C092ULL, 0x2B4DB7AE539A4C60ULL, 0x7D268D4DD0F882ABULL, 
            0x1F114B087C8A6B76ULL, 0xA9BB11E6F09A6127ULL, 0x95EA42919AD3D193ULL, 0x5AEA267387FBAC22ULL, 
            0x62370A84E6B39943ULL, 0x794B8AF75DEF0FD9ULL, 0x79B35961E829BECFULL, 0x4ACC54EF476A7B09ULL, 
            0x66CE8BE6A6872AB4ULL, 0xABA16AAA3CA44438ULL, 0xE43979D78CF34948ULL, 0xB2E702986D75C424ULL
        },
        {
            0xA06C4864C6B46A4FULL, 0x8486EC3CBAE59A03ULL, 0xF71F03C5DB64AC7CULL, 0x6AFE7110B0BEAA44ULL, 
            0x1AE4A327AEA21C1FULL, 0x424BFD2E8B17E9E8ULL, 0x9BBC185F6218D722ULL, 0x4E4266056430AFCDULL, 
            0x8C8B62A532541A0CULL, 0x1BC6F7C0513AAB0EULL, 0xAED5456E10406DDEULL, 0xFBED29E57B1431B9ULL, 
            0xF7A6F95339E34DF7ULL, 0x090ED219CB92ACBFULL, 0xA59FB9B5BD32638CULL, 0x4324645A7E422B74ULL, 
            0x08FB72381344231AULL, 0x8D032ADEFEBA9AABULL, 0x8249CE2D1ABE5938ULL, 0xA3E5A68F41B2B449ULL, 
            0xF1914610BA6E6FE3ULL, 0x80C4634216AF7AC0ULL, 0x72D5A4C23665DB14ULL, 0x54C4260B5528A9B7ULL, 
            0x3FD0CC24727357B2ULL, 0xEE60865F1073FA76ULL, 0x76BEB722BD73BE95ULL, 0x710B6AA73589AF49ULL, 
            0x52270FAC51F5AE28ULL, 0xF7EE9DF6C9AB167FULL, 0xE337EBF9976B8D98ULL, 0x4967F94E1CEE5F9DULL
        }
    },
    {
        {
            0x6734F852EF19A59EULL, 0x674782D46620B52DULL, 0x504413E9E51D68C9ULL, 0x6D5257401A8DAF53ULL, 
            0x38ECB1E766410D60ULL, 0xA2D647062551CF7DULL, 0xCDD58500F08CCEF7ULL, 0xFFB5E65128425EA0ULL, 
            0x63FF409010D13CA2ULL, 0xCF121BC79088417BULL, 0x9B1325441B737737ULL, 0x6C7D41205FC55C26ULL, 
            0xB997AEAB22F33F26ULL, 0xABC4EAD596C92FD0ULL, 0xA9F900962FEF0E0BULL, 0x890379BA74E467BAULL, 
            0xEEF91514006D9C50ULL, 0xE511A26FCCCF2592ULL, 0x96DE742097636668ULL, 0x30A20B575C3AC1C4ULL, 
            0x582B7D3C639C0F9BULL, 0xF2D1136F3AEFC94AULL, 0x708F9E9CF237D550ULL, 0x7F9592B1460A158CULL, 
            0x5D929953A6258145ULL, 0x5C591061FC80BF8AULL, 0x9FF2ED4BA3ED8CD7ULL, 0xB634F00B8DEBF221ULL, 
            0x2971599C2A224DB5ULL, 0x36394419C38FDFEAULL, 0x93575AB6A1F1F7C3ULL, 0x5CB0C8C7D2BA1A96ULL
        },
        {
            0x7ADF2936AE7D44D4ULL, 0x37098B9777463126ULL, 0x16A4FEB920959264ULL, 0xE53351A82A6D975BULL, 
            0xA6E2F1667E4F7E68ULL, 0x06CD24EBD185D75FULL, 0x221482411AC168D4ULL, 0xF291CAAADD5B17D1ULL, 
            0x668741970FCFBD94ULL, 0x783EFB691E593A4AULL, 0x4202CF0207A70E85ULL, 0x4D3AFB7182FA9863ULL, 
            0xAB64A6F13E5280B5ULL, 0x8E77BA46D89D3930ULL, 0xEF2CFF2051A02F0EULL, 0xEA7CC3291C9DD79CULL, 
            0xAF97C01406DC3A52ULL, 0xC731DB0B569ACAB4ULL, 0x659658F91059F050ULL, 0xDB9EB6AE982A999DULL, 
            0x4DA082B6FFDA1348ULL, 0x5E139432B993C30CULL, 0x6AC9A5C06CFC06A0ULL, 0x589E54B453A8B558ULL, 
            0x23F118F177BD4A70ULL, 0xF10E44757A61BC1FULL, 0x028EAF89796C9D46ULL, 0x942B62A95C22E6DEULL, 
            0xC593104E38A6B2C1ULL, 0x317C8B97BFA75D7BULL, 0x50821B46D477AA8BULL, 0x13C6F012575B57F6ULL
        },
        {
            0x25EEC75EBC3D7009ULL, 0x6C9CAB9CC2C4F708ULL, 0xFEB27EE658C64A84ULL, 0xF8FE7F48DB414AC0ULL, 
            0x05FB7C763E65B590ULL, 0x8AA53C9B31AA9B64ULL, 0xA59030ABF6B4662CULL, 0x70C25CD164C7F853ULL, 
            0x74E7BC5DC8066636ULL, 0x5DB1B9BA89EBCA15ULL, 0xFA0307AB1267318CULL, 0x3818A4FEB58A74F4ULL, 
            0x3DD28A5C5F422F69ULL, 0x127EBB8E08259F86ULL, 0x3EDFC068B875CE12ULL, 0x92C79778A856C9DBULL, 
            0x69B23A2D3E21B634ULL, 0x41864C6BA71856C3ULL, 0xB4E0B2E20AC3E92DULL, 0xEFBE0F9CF4DFEFFDULL, 
            0x8997FDC1021F2BF9ULL, 0x6F9164EF359DDC31ULL, 0x405D207089D49F31ULL, 0x6D097D8EBB678324ULL, 
            0xAA0DB9A2E944912FULL, 0x9760A5887285ED25ULL, 0x647BE8C062E89A93ULL, 0x86DF3A7564A15D14ULL, 
            0x3EEF84B19C5EA3B3ULL, 0x625F05174A128E7DULL, 0x8DAF27C1C1AB77CFULL, 0xCBDB4D8D752F9E3FULL
        },
        {
            0x5672625BEDB68B57ULL, 0x8E5F0A4BD486B877ULL, 0x98EEAD21C683298BULL, 0x9676D10A3CB2DEB1ULL, 
            0x53EA3BE0C91560D5ULL, 0x62F4A8977253F58EULL, 0xB14A8BEEAA9F1596ULL, 0xF30EA22320B8EA01ULL, 
            0xBC235D40AB638E81ULL, 0x822FDB14AA85CBB2ULL, 0x722A2434EEA71DCAULL, 0x0A7A07152D991077ULL, 
            0xF1890B4AE1812389ULL, 0x5998FE5CB623DB48ULL, 0x20E8BF5E332B6706ULL, 0x29C32167EFA91304ULL, 
            0x9182173552D3BC09ULL, 0xF07AB5BA3804E67FULL, 0x2CA762FA90C1F320ULL, 0x08843A5C3A98B68BULL, 
            0x56709C4C4DC744BEULL, 0x7A68574789716B47ULL, 0xE7D8840A9334394DULL, 0xF4C425481A6572AFULL, 
            0x8055C38352902C6BULL, 0x1198CEAC3DE0C864ULL, 0x4527AF0451C4FACDULL, 0xE0FBD77183A35C33ULL, 
            0x2830BC36C7B185DFULL, 0xA115A72C0CA25C81ULL, 0x0618309F642A426CULL, 0x7261F70361F045EEULL
        },
        {
            0xECD3849F4E5E31E4ULL, 0xF167B7DD29C21589ULL, 0xAEA3BD7FA57198D1ULL, 0xCA84F07C2C85677FULL, 
            0x83BE44C44CDC2768ULL, 0x22423C7E741CDB1DULL, 0x8B07A120EF9BFB9EULL, 0xCAF57DA108FF7C64ULL, 
            0x69B647C9227F91C2ULL, 0x418C85BD1DDCBFDDULL, 0x817330DB1C95424AULL, 0xF22977B6E1128E83ULL, 
            0x9D2858EF08E7DC24ULL, 0x1E1DAE4CF3572DBFULL, 0x3143D75628A5AB1BULL, 0x935D905076D04E69ULL, 
            0x68B658802AAB21B0ULL, 0xB2A73229C789E3FBULL, 0x74A2DD904AD4343CULL, 0xB4498F321097542EULL, 
            0x755BA0AADE70436CULL, 0x29F2779CBF25BDE8ULL, 0x33E86E6D00441BE5ULL, 0x2AECA666AEF44005ULL, 
            0xD314846627171AECULL, 0xF3BB49E47958BD5BULL, 0x40C78ADC20F666D6ULL, 0xC6E784A886BF9B7CULL, 
            0x7829BB4A6723B768ULL, 0xD27F51F4460BC1ABULL, 0x0F4A17F67621E032ULL, 0x1C7885A31FD57871ULL
        },
        {
            0x0B920C5C662379BEULL, 0xDE25AF72FE6B58E5ULL, 0x67F168349939223CULL, 0x40010A8508826AC3ULL, 
            0xBE3A16BE3E68229EULL, 0x9894C856758F73ABULL, 0x365605DCA083F6FCULL, 0xA8633975E7755E3AULL, 
            0xCA44E9A4B10D360FULL, 0x6DFD8C6B636ABF2CULL, 0x1996B4D5AC0BB359ULL, 0xADCE847492A3E5D2ULL, 
            0xF5DE27B72861235DULL, 0x9C31ED6471E52FA3ULL, 0xD0F48964D9A0DBDBULL, 0xA5965EA351849A9BULL, 
            0x2758D0A9275FC357ULL, 0x0D7045EAF4AB4195ULL, 0x0E23D7CCA68F6240ULL, 0x1EEDFC92EDFB8DF7ULL, 
            0xC22C8568A6C53BDFULL, 0x8EE6871621344358ULL, 0x49EFDCC61C733B1CULL, 0xC89417DC2916A78AULL, 
            0x4FE922E651449D7AULL, 0xBC90609EB3AC3348ULL, 0xBBD13B3FCAF57DBCULL, 0xDF3CBD9B6C1CEB0DULL, 
            0x572E87CD68D691F3ULL, 0xACCFB4C27A745D60ULL, 0xBAE0E410CBB19271ULL, 0xD26824C97B4B914FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseFConstants = {
    0x0F750BCAC543ED7CULL,
    0xA6FB7A295F6CD558ULL,
    0xEE6C6358D20399B9ULL,
    0x0F750BCAC543ED7CULL,
    0xA6FB7A295F6CD558ULL,
    0xEE6C6358D20399B9ULL,
    0x132BD5D0A6233260ULL,
    0x5E286546D208D70FULL,
    0x1E,
    0x6B,
    0x33,
    0x34,
    0x9A,
    0x39,
    0xE1,
    0x7D
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseGSalts = {
    {
        {
            0xE344B13DB9DEFEFAULL, 0x3D146E3C6D5108ABULL, 0xD45CBC4943C93656ULL, 0x5E8E8F79C8D53822ULL, 
            0xB8AB698FCFC6CAD4ULL, 0x9902F94614091327ULL, 0x5FCF2DB78A43360DULL, 0xAE9B68F1468CE8F8ULL, 
            0x9FA0A77ED9B5C191ULL, 0x5A391D28C0C58E0EULL, 0x38C2FD2A87FF7607ULL, 0xD28D37285A2179CAULL, 
            0x2F23589200830C47ULL, 0xE380AB6B147927A1ULL, 0x6ACA2E7F6E89C3DCULL, 0x7E1740B4DE385615ULL, 
            0x77CDF93229F9B08EULL, 0x53C46508E9F5CA6EULL, 0x7CC8B76FD2BB4326ULL, 0xD891774721CA39BCULL, 
            0xA3236663930AB012ULL, 0xA0F7313012EF46CEULL, 0x67624AFDD8E57172ULL, 0x720709D9DA883270ULL, 
            0x912AE9670FFDCBCFULL, 0x90DB1E6548C71C57ULL, 0xE4A17DBE17A133A4ULL, 0xF9685BD75B304229ULL, 
            0xCAA1288E4D282F2BULL, 0x46BCC58782C2C8D9ULL, 0x0DE55B9F89BC112FULL, 0x6B221282475B25E7ULL
        },
        {
            0xDFCAC5AEC2E6D3E1ULL, 0x86578761B53EA8C4ULL, 0x3B0C94BFCA5E59EDULL, 0x7FDB020B164687A9ULL, 
            0x38FD7F6DF511D7ADULL, 0x30129FC9B072B370ULL, 0x4D49CF975A2B8680ULL, 0x9886592BF126134FULL, 
            0x1B2043C4391B3D0DULL, 0xCCAF318579E78060ULL, 0x88981795AB048644ULL, 0x8EB998F5C7BCCB0EULL, 
            0xBB2071D4B23DAFA8ULL, 0xEA49767FB419407CULL, 0x291F7C27BCB70701ULL, 0xEE482209C3FC8DE8ULL, 
            0x761CDEF34863193AULL, 0xD25586EAD1553B7BULL, 0xDE9DB6B87357BE7DULL, 0xED8AFFB2B8D1D2A5ULL, 
            0x6541F5968DAE27C9ULL, 0x622C2A47A8A64049ULL, 0x5BF1E69C9302085BULL, 0xEC92D04FAFD9E1B9ULL, 
            0xB57BD90F0F37A59FULL, 0x11E296DB950E9ABDULL, 0x26DE334E1F26895DULL, 0x423EEFEADB0A5924ULL, 
            0x17BECDC9A9AF6DE4ULL, 0xF0033A521DDEE7CCULL, 0x39A58EA785171E75ULL, 0xD0072F4075F37D82ULL
        },
        {
            0x9E93098A9633275EULL, 0x2B61B5793CBEEB74ULL, 0x71E41A0E1944F0CDULL, 0x99568B3245C64063ULL, 
            0xEB1DF5D93863A78BULL, 0x802D9060697568D2ULL, 0x2D09EE5CA34B592DULL, 0xFC7914C53704BC4AULL, 
            0xD589AA3582473348ULL, 0x173F0175058C4287ULL, 0x85E5717365F922D6ULL, 0x5E09D92350FC1DB3ULL, 
            0x66537D99599ADD87ULL, 0xF4A8769D8465D6F9ULL, 0xA04CABED89A0E382ULL, 0x912790E0D585E0DAULL, 
            0xBDA34B63558B6C1BULL, 0x0F91CB9CE63F0B07ULL, 0x0B5FCA0EEDC5C852ULL, 0x3805DEF7A082C9C1ULL, 
            0x08B4256714E167AFULL, 0x14B4087A8B950632ULL, 0x92FDD0443DA73A46ULL, 0x8E619A2C7817AB02ULL, 
            0x9B27A1C327C06FF3ULL, 0x22B173F72BB435C2ULL, 0x34261CDECC6D01EAULL, 0xCE4C9688D401D684ULL, 
            0x8894703F046D19BCULL, 0x499642873A0DCBCFULL, 0x84CE97CDF3CC1267ULL, 0xE318906E2257717FULL
        },
        {
            0xF10811335A3D39B5ULL, 0xAF0C0785BDD08F56ULL, 0xFE58EB522F981FF1ULL, 0x2347C03031064F89ULL, 
            0xD7283D98A503B733ULL, 0x87689F62D0C09835ULL, 0xDD710BB67C773AF7ULL, 0x97CC595B4C5DBD42ULL, 
            0xE5C6C1774E2CEC39ULL, 0x0FA7BFE8650797CDULL, 0x6F7FA62979A784D0ULL, 0xEF5A5EE2A1E1892BULL, 
            0xEB8A995239E6046CULL, 0xD621189E4930B96CULL, 0xEA61C6D22DE436B3ULL, 0x3DE64D0528769AD1ULL, 
            0x75BF6248198FF0F0ULL, 0x28B03683FFE9D39BULL, 0xB00F22E30AEDB1F9ULL, 0x26A8A497972B502FULL, 
            0x500E65B094289B40ULL, 0x028215B9F5D2C887ULL, 0xE5AFC62BB2DCAC84ULL, 0x74DA2D8EC917097BULL, 
            0xC56214AA1DC255D2ULL, 0xA20C6B08CB14B445ULL, 0xB7CFE7302AD109ABULL, 0xB2541CD1214063BAULL, 
            0x49575ABCBDC919C0ULL, 0xF198E4160D7F8A98ULL, 0x41EBD9D8F4AC2B3AULL, 0xED73010A74B3FCADULL
        },
        {
            0xD761F23B8A06A5A5ULL, 0x7B345B1BA8C20794ULL, 0xB5B52559537106CAULL, 0x0D799A500D9464BCULL, 
            0xF1C0296DD460A64DULL, 0x28626A6A266211C8ULL, 0x10C27E60F54A5DAFULL, 0x1B3ED3F907FCAC3BULL, 
            0xF8F46FFA4F168047ULL, 0x0892F5E0CF54DB3DULL, 0xF2100E86E515AACDULL, 0x08F91D816EF4F021ULL, 
            0x0E101A5A6F9693BFULL, 0x47A845C588BD7FBCULL, 0x20BC159EEEB037A4ULL, 0x88B00ED9B60A0061ULL, 
            0xDCE3ED6DBAB30414ULL, 0x52DED9DC1F04D4FAULL, 0xDBD510B6905230A1ULL, 0xE515D10B76DD39FEULL, 
            0x3E3C88E2E7E78BD7ULL, 0x909DA486F21B2D3BULL, 0x7FB8BA61EF68F3F8ULL, 0x0DA60F9E359DFB31ULL, 
            0x6B909AC862CB1794ULL, 0x5987EA8EDE69147DULL, 0x13927120477715B0ULL, 0xFAE3C36621E879A5ULL, 
            0xEB1FC4171129BB1CULL, 0x8429DB5B95500E80ULL, 0xE67671C1CABD7A8AULL, 0xBD5E5DD795C06510ULL
        },
        {
            0xF226047C33A91A3CULL, 0xE20ACC00A08D44CFULL, 0xDB530F68BE2F6830ULL, 0x3754CA48D075E10CULL, 
            0x89A1B3DDEDEFCD73ULL, 0x08BCF35AE5CE44E6ULL, 0x4C2F5751C8121800ULL, 0x88964F6B00267FA8ULL, 
            0x90D30BEA329D6B77ULL, 0x2D1044C9089D1489ULL, 0x2BB3A513710F0CD5ULL, 0x58B5F9A65C2F4BDFULL, 
            0x3DC63355704EC205ULL, 0x0178E8DA6178ECB9ULL, 0xB91A8EE85B9D909EULL, 0xEA5C10C6EC380E7BULL, 
            0x2C948ED89FFF5A5FULL, 0x10A6B8C1ADB4294EULL, 0xEF21FF92A15CDDAEULL, 0xD24AB766F3527552ULL, 
            0x20E83E671F8BE61EULL, 0xC36B5561286CFB1CULL, 0x772BB77F976AC749ULL, 0x2793255F0854F291ULL, 
            0x38F2378F23EE949EULL, 0xFC2E1F1A2A9EFE51ULL, 0xA30AF19ED13B21BBULL, 0x99E46D5350019EF5ULL, 
            0x4C2959EA1EBDD47AULL, 0xE7B0FC0E56A1861DULL, 0xF3B1803D3F918ECFULL, 0x23CD069DB1B0C4AEULL
        }
    },
    {
        {
            0xA4F601EB110A93F5ULL, 0x95395983AF1AC302ULL, 0xA673B741268B7B92ULL, 0x220C07D128D7E922ULL, 
            0x30A936086B33967BULL, 0xC8CB2477669114E1ULL, 0x5DB0461A09712FEDULL, 0x30089E85F9903934ULL, 
            0xF369AF0D3C115078ULL, 0x3378E6F38B20261EULL, 0x62562B659FE60F1BULL, 0xB4340A2958ABA1E3ULL, 
            0x05D3E96196001B00ULL, 0xD52E08B550A4CC76ULL, 0x2798506034795461ULL, 0x02E8C7DA9742DD2AULL, 
            0x872EC00AFC87169CULL, 0x7561E4EA7DB986EAULL, 0x31F17AC49AFF8182ULL, 0xCDB8C41A49A5BE8DULL, 
            0x91DCDD5C79EE6247ULL, 0x13AF1B23B6B756D6ULL, 0xA669502A1E8F1260ULL, 0x7966471CC508FA79ULL, 
            0x55D0003AAC0703A8ULL, 0x80DFB4D4B9706451ULL, 0xE3872F6092B9BEA0ULL, 0x256363B7E555EAD2ULL, 
            0xCA00737930F42699ULL, 0xA4735EFEEC283694ULL, 0x8332F90025397C5EULL, 0x469562788CFAC15FULL
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
            0x1C7B2EC753492D0AULL, 0x8B1EF5D3F3BDE378ULL, 0xEF59AC11A1E0A543ULL, 0x16B57010A4F63158ULL, 
            0x3FCC14ED90B2BEEEULL, 0x1319DA95D92C7313ULL, 0xD97B3746EF433637ULL, 0x38517F79895FBD39ULL, 
            0x615FA9BB42581987ULL, 0xBB60FBBD079A8748ULL, 0x0AEA775606AFDD9DULL, 0xAFCF9563E5652C73ULL, 
            0x21A0FC0BF0B4B571ULL, 0xCC6923E62CCC315CULL, 0x43BC577E01621B61ULL, 0xCFA94E1B6CB2D4CFULL, 
            0xAA17BCFD03F82736ULL, 0xBDF3B58E912C49DBULL, 0x661302783177B2B7ULL, 0x0C48154717EC271BULL, 
            0x546FA3E4A29BB06DULL, 0xE0764ED7BDAC6F9EULL, 0x4B0B63DB2ED27379ULL, 0x00FE0840E30A10FEULL, 
            0xC311BBE5F59992A4ULL, 0x5BD9CD03D6F3A058ULL, 0xCE8A8DCD0488684FULL, 0x2F0EEB82F4D44BA4ULL, 
            0x17C0705AE8B69290ULL, 0x6E34D19D2453B36BULL, 0x3B9A94048189F444ULL, 0x5D4E200400B937D9ULL
        },
        {
            0xE5C1D4A9DFCE6511ULL, 0x8BE2A635C9DD1CEDULL, 0x3E3E2444B9E98D24ULL, 0xC906744C4F705C26ULL, 
            0x20FC17D835BB24DEULL, 0x8B82D1C11456CD41ULL, 0x29DA4280189BE1BBULL, 0x466160EC0D1209E2ULL, 
            0x5F5A0D876D7EFF28ULL, 0x4180FCF5D2CEEAEAULL, 0x59E2F5A21099C42BULL, 0xDBEF87748BD23923ULL, 
            0xEF9F75C215159C9FULL, 0x4E7D2D493246711DULL, 0x41C979CD3D399A94ULL, 0xECEC4373600317AFULL, 
            0xF82568FFAC3EC4EEULL, 0x15AC99943A670DEBULL, 0x20E9DB4E0CD1942CULL, 0x2D34453CA0E492B9ULL, 
            0x4FDD83086BD3F92EULL, 0x05B27B97C59B966BULL, 0xB566461A38613ED6ULL, 0xF7972579BADC27D5ULL, 
            0xAE6AFB83B817CA15ULL, 0x91E47B102436724DULL, 0x1118E05A3D2325E0ULL, 0xC6DFE99511C896A3ULL, 
            0xBCE0FF2E5D3A104FULL, 0x29AC34B331A3EC43ULL, 0x9476A3B3BDD3BC49ULL, 0x79081EBAEB653157ULL
        },
        {
            0x95958A0C3D25B396ULL, 0xBFEC7AFFC9E6E88FULL, 0xF81C62A86E89AAF2ULL, 0x96B3FF3E0D7F41C9ULL, 
            0x43C0BDE3DDC00EB1ULL, 0x79200FC6F1B54122ULL, 0x243183C37FCBAD0FULL, 0x23472837B55B9F01ULL, 
            0xEC3660094CACCB39ULL, 0xF2AA70BA36DC7E24ULL, 0x318F9F6EAAD46CD6ULL, 0xED65DED2A2C2DBE1ULL, 
            0x3AE9A3D126C47E3EULL, 0x8E1FE4F175E3C464ULL, 0x3BAE52FA6A061793ULL, 0x5A74E86663F686FFULL, 
            0xC30458AB99C3E7A4ULL, 0x87BD06A13E8EE2C3ULL, 0x438E0F60D222EC17ULL, 0xE2D17B85A6B45500ULL, 
            0xB26FD0104EC7CC38ULL, 0xBAC3D01CB4BE8D28ULL, 0xC7D2EA4BAA9AB892ULL, 0xA78C49AC790AB4B3ULL, 
            0xC35D17D8BE6F2C4EULL, 0x14650E37CAAB8E38ULL, 0x7187453A32E9E794ULL, 0x120A0618ED9C0E30ULL, 
            0x293C8F6A60783729ULL, 0xC60F564647199D61ULL, 0xE04F7AF51B074ECDULL, 0x8D567375A21382E6ULL
        },
        {
            0x675D7E1474D007A4ULL, 0x3685C64D6CADE211ULL, 0x22399067D0A8E68FULL, 0x2A4A7E979927833BULL, 
            0x978366316A0FFBD6ULL, 0x12F2CAB802F773D8ULL, 0xF9588935A0AED290ULL, 0x49E80C63ADCFCA93ULL, 
            0xCCF7C1456F938EC1ULL, 0x3972A6E3C6AA1262ULL, 0xCDB9351B01DA7268ULL, 0x0795556AC27E3CAFULL, 
            0x39F2F61BFA06B081ULL, 0x7E303F3A3897129CULL, 0x8CBB684419C76170ULL, 0xB5FD535B01955B8FULL, 
            0x027FB67E137DAC2FULL, 0x7F51B9FC2A882E80ULL, 0x946E9228EF7892B0ULL, 0x976C13FDCB9ED8C3ULL, 
            0x2C4D0B8ADE427A16ULL, 0x8C696C1CDD144E7EULL, 0x421357788B4EC9C4ULL, 0x0ACD9C03705F2C50ULL, 
            0x447630D739A9AADBULL, 0x504A0C42DA71099CULL, 0x9ED2C0375F3002C7ULL, 0x9FAE3923AE2F65B9ULL, 
            0x0976E93032DC4DE0ULL, 0x8594982B9383F82AULL, 0xB49A74AFE8C27142ULL, 0xAE110F6C9579A036ULL
        }
    },
    {
        {
            0xAA4EE5A14A1E6DD8ULL, 0x8EBD39E1ECF9E995ULL, 0x9610CE0F6B5597ECULL, 0x3451CF677A66639FULL, 
            0x54934BDD7D36DAD0ULL, 0x275D160E96A4521CULL, 0x8019BCEC99832612ULL, 0x730A24BCDBC77F2FULL, 
            0x4755EC13B32AB9D1ULL, 0x9B5FF90FD55A208AULL, 0x4ADD019AEC654752ULL, 0xDE0B69B5C2FC0566ULL, 
            0xCEE3EADEE212FF5BULL, 0x9940A3698F7EB831ULL, 0x91D41D509C23FB54ULL, 0xBD2620BA85C1C382ULL, 
            0x6EE887EDF5D5FE8AULL, 0x69DB625E7FB24708ULL, 0x056FA39836EE9186ULL, 0x0B57705E29106182ULL, 
            0x90A571F407B6F273ULL, 0x3ABA6ED3A766679DULL, 0xC9F8D527592C5748ULL, 0xB35E152997685DFFULL, 
            0x2D87F35E96BDB568ULL, 0xCBE9DEAC2B3F153FULL, 0x877C715A89B9398CULL, 0x29BB76214A7788BCULL, 
            0x623C68B7D8C31FD4ULL, 0xF5F32E264E382D07ULL, 0x3D94726BDF6EAD91ULL, 0x6D324A7F83291D3CULL
        },
        {
            0xC7CBAABB365B8DD8ULL, 0x5B13137DB1E2B3A7ULL, 0xF17F332F2DC5982CULL, 0xFC8983D2F0746E55ULL, 
            0xE6CBDE4ECAA1915EULL, 0x06678C66A7C64B22ULL, 0x73530C12AE0B5306ULL, 0x46876486DF328E71ULL, 
            0x60B3D9C7689C726BULL, 0x965C984AA5F29D2EULL, 0x70B821E60B70A9E7ULL, 0x40322B9C82BBD2B3ULL, 
            0xABA264B038BC72B6ULL, 0x6AB5BE2E5B9CFE01ULL, 0x66E6BF36AD59B73AULL, 0xBC99EDC72CF8C23CULL, 
            0xE8078D34057F4588ULL, 0x01729BA272478097ULL, 0x76C19FE0675ABBC0ULL, 0xF5908208BF14CE99ULL, 
            0xC25D93B32EC942ADULL, 0x4A7B0647CC8FFA17ULL, 0x77B66488A7519064ULL, 0xD8C3409913A90A43ULL, 
            0x1F85620EB70E6BFFULL, 0xA8458CE368B5822BULL, 0x3EB3BD0D661B7611ULL, 0xFA7A4BE47FFC354FULL, 
            0xA4C8EDAE59925072ULL, 0xD5E8AA49FB90DBC2ULL, 0x38468E03122D0365ULL, 0x3DFA49FB5EE8A0DBULL
        },
        {
            0x78BA724E6CBF87FCULL, 0x879FCF2AF2460979ULL, 0xDACC8D991C027958ULL, 0xA3572A87CDEE71C9ULL, 
            0x747581A695155AFEULL, 0x4ED42B6C7D3F2DF1ULL, 0x737F05E1CD3E6F09ULL, 0x3EB44AA3A4886961ULL, 
            0x3E1482D8315166CEULL, 0x4CB3AF33541E0D43ULL, 0x2C526B30FDE9A3F3ULL, 0xA2E9C732D59DA843ULL, 
            0x8B9DF3A87DE93714ULL, 0x781545EF06286187ULL, 0xD0DE12B31C42282AULL, 0x98B65683F313A576ULL, 
            0xB56E1D4452978D12ULL, 0xBA5C6770A09F4085ULL, 0x1CE93558955D3BFEULL, 0xCAEE8EE3F5F00E95ULL, 
            0x05F9D3937DA4C7AEULL, 0x54A95E01A5C79DBDULL, 0x92F38FB24F3D97F9ULL, 0x4D78ABE2212B0B73ULL, 
            0x6B7CDBBF765AEBF9ULL, 0x623CCDC2BED95812ULL, 0x7F22DDA9AA7EFA74ULL, 0xBE1572A3D5182962ULL, 
            0x61C9CAED74B914D9ULL, 0x0E3A3D9ADA8EA413ULL, 0xAFB1BAFC8D0A7A9AULL, 0x41A465A00E58CC5FULL
        },
        {
            0xE480E925807AA83EULL, 0x9114A537A1126ECEULL, 0x204BB355A481D005ULL, 0xD93E7A8087AC8611ULL, 
            0x623F9A4E01F17C36ULL, 0xF1EE64D4AF624B9EULL, 0xCF2FA71F4CA308C5ULL, 0x48A06B34BE89C127ULL, 
            0x788018BD1A3074E0ULL, 0x43B1870A2DC41BDFULL, 0x7E1B3FAE4CB9A365ULL, 0x9E37A885E491E2EEULL, 
            0x72D17FE10E076B68ULL, 0xC64BCB0272F71D0BULL, 0x9EED0E661C7852B3ULL, 0xDA0C769D10F6A38FULL, 
            0x7D1AD8489453D2CCULL, 0xF42EC07FB394DFD2ULL, 0x63C0563A050B4225ULL, 0xDE19854578B514E8ULL, 
            0xB0C695E4BD841CD9ULL, 0x65058924BFFA1A5BULL, 0xF7EEE94AAF38C9CBULL, 0x72DF6493C4FE891EULL, 
            0x59096103CD413B6AULL, 0xDD9129369EB673C7ULL, 0x9E0FBDF5C5A0CF00ULL, 0x0E94925664ECD621ULL, 
            0x12047AC671220DBFULL, 0x41619A9B3CD3522EULL, 0xB478B1AD3588B59FULL, 0xF8F72558860E7139ULL
        },
        {
            0x04B2C7860F23EC6FULL, 0xBB18B928F5A88D1DULL, 0xE07446F623746F6BULL, 0x5CA1732843BFD497ULL, 
            0x75060A400BE3C38AULL, 0xCFA39BBB18E44F1DULL, 0x862BA4207E8E4753ULL, 0x57E4FC7EE72C0887ULL, 
            0x79A9119F3338CF19ULL, 0xA55D5B939D4D4A37ULL, 0xB8108485F683C32BULL, 0xACE1CEAB14751A9BULL, 
            0x8297BC6B7A5C1859ULL, 0x215D7C1519E69963ULL, 0x5FAA9F5A721E610CULL, 0x23BAAF859FA70384ULL, 
            0xE6C6941665D5021AULL, 0x78E9758568EC54E3ULL, 0x07F2A22A040FDECEULL, 0x3E9077E1529D1371ULL, 
            0x6D0C1552DCD59453ULL, 0x947DB62493111342ULL, 0x402085866C39F18AULL, 0x62C041F22FA56212ULL, 
            0x47194B46E9FA0FCCULL, 0x7EBFA664643A173EULL, 0x7228AD6AC8769C2DULL, 0xF7EA9BF9CD500E33ULL, 
            0x3DC12FA38E86023EULL, 0xEC3814234D93885FULL, 0x1E602A76EFC43543ULL, 0x795036CE1FAB2FCFULL
        },
        {
            0x5010E6466D96CAD2ULL, 0x4CA24CD6F4094554ULL, 0xF9E2D0F91EF4759BULL, 0x5A36F7B2F5C7780AULL, 
            0x99AD1AB4AF271B41ULL, 0xAF87EF440B0824B4ULL, 0xFECACD2C8514D157ULL, 0xD11E83DC3CE7B6A0ULL, 
            0xD749A4DC320FFD26ULL, 0x7BA497D568030337ULL, 0x6797AE5F8E3272F7ULL, 0xBF0A3D275078A8E8ULL, 
            0xDEFD810A2C0089F3ULL, 0x618212B9BAAA0373ULL, 0xF1FBF70CA2F49B69ULL, 0x58C0B3BD8E703516ULL, 
            0x2D61AEF85D9E8F33ULL, 0xEA994E99E43D363CULL, 0x7FF5663784044A39ULL, 0xC7DC04534426B028ULL, 
            0x4571F03FF673A84EULL, 0x0C136C97EBABBAFCULL, 0xC23A19A4CA003DEEULL, 0x78F2BFE745A33178ULL, 
            0x928C64B0008C5478ULL, 0x2A4D398A9FE625ABULL, 0x67BF7CB76C71253FULL, 0x53021044C7053CD8ULL, 
            0xB19EA73F36017389ULL, 0xC5C34D5270D97B8BULL, 0xC5081634D2A79CE8ULL, 0x3F3D8EA74DCB437BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseGConstants = {
    0x768A92040C9F73ADULL,
    0x30C891B9C0338671ULL,
    0x5FE3AE83DB591A3FULL,
    0x768A92040C9F73ADULL,
    0x30C891B9C0338671ULL,
    0x5FE3AE83DB591A3FULL,
    0x94BCA546D294C1D1ULL,
    0x9B591D947178C38BULL,
    0xE1,
    0x58,
    0xF3,
    0x57,
    0x95,
    0x54,
    0xD7,
    0x18
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseHSalts = {
    {
        {
            0x349D2672AC9936FDULL, 0x69AB76DDBFF44EFBULL, 0xFDE151909B30236FULL, 0x78D015C8FAC7E963ULL, 
            0x36C996AC1CE10138ULL, 0x3F9FB10AFC0DED06ULL, 0x52077D41E0AEEF84ULL, 0xE8B77DF1CA2EDB8DULL, 
            0xD519BB3A5EE57E84ULL, 0x57A58D64E7A19452ULL, 0x3D6B9420D268E0CEULL, 0x8ABC0473CF286967ULL, 
            0xF1096DD25BF71516ULL, 0xB71A1C019479271CULL, 0xF8FA74A2EE1C7754ULL, 0x6215080136A0EDEAULL, 
            0x66F8B95A291B3754ULL, 0x4E879EF436C214D5ULL, 0x053B9BB74D260F22ULL, 0xFF57A49FED46B961ULL, 
            0x537B19004D010FDEULL, 0x607A6570326CB0C9ULL, 0xF8FEBDF350E252F2ULL, 0x2159D7730BC9C93EULL, 
            0x84B87DDA05D0256EULL, 0x39835DD4A2B333A6ULL, 0x4825D62E15716071ULL, 0x9411A602FC72716EULL, 
            0x7FE12179C41C080DULL, 0x1518F967A590F6C5ULL, 0x5D1C626B92F2DB0AULL, 0x4101A21DFFF8F862ULL
        },
        {
            0xFF520FBD10E43B3CULL, 0xD746D9D2C20FA41CULL, 0xB1D0D7A9734822EFULL, 0xA9D800A8E668375DULL, 
            0x484F005310864609ULL, 0x096455A32E03045FULL, 0xFA440901F4B625B0ULL, 0x933AEC8BB99B0B31ULL, 
            0x9DC100BDBD36DD99ULL, 0x5293DCB186FBFA9CULL, 0xF6154B546A8D3720ULL, 0x07EE89D24AD56A5DULL, 
            0x90006D9A0E58E0BDULL, 0x2053D3A4207F837CULL, 0xEAF2529216887F04ULL, 0xB8AC4E6B0107090AULL, 
            0xDBE8436B294CB3C4ULL, 0x3213FA4C0521696DULL, 0x2E62AA88AA80A4C4ULL, 0x530A10DB15597C3CULL, 
            0xD20C2AD6119ADEFAULL, 0x3A9225B7DC9A03E5ULL, 0xF3F10E8F4AE41516ULL, 0x53F6B2D6E3C0DC04ULL, 
            0xFB7FE4B6D7302772ULL, 0x70B1606241CFE214ULL, 0x376F10526D292CDBULL, 0xA668DF1CEB4B567DULL, 
            0x162CF980E93E1A7EULL, 0x979A6BD5DB2B25FAULL, 0xE04ECC47DEF6D5F5ULL, 0x3C93580A1F0A6594ULL
        },
        {
            0xA5984BEC4FEF0FCAULL, 0x5C91F5C4DB90019CULL, 0x4D6C598F8752F870ULL, 0xCD5CAC9F97F45F69ULL, 
            0xFB52A90F82B80CF7ULL, 0x24B34A45DE859969ULL, 0x8104EBFAA8B9ED0EULL, 0x53E7A67DB5FF0B49ULL, 
            0x5038B659CCCE1E90ULL, 0x1D975AA669A509CDULL, 0xCA8F470B1839C34EULL, 0x4C0F322BD26FBDCEULL, 
            0xEA4D7414690F1FB6ULL, 0xF00D432B8961C395ULL, 0xD0F3B924EECD46F4ULL, 0xF82A946787CF225FULL, 
            0x2DA0C735650C1A0BULL, 0x2FD7F104C9CBFC45ULL, 0x84750331A2788F15ULL, 0xD990E9566958153EULL, 
            0x5DCBC63C16277056ULL, 0xE2F0E1F17CF2E825ULL, 0x2BB72F5F60C8EA2CULL, 0xC2155567B10EAC03ULL, 
            0xE0C72AF5BE3EC374ULL, 0x609A8DF50350D75FULL, 0xDD7B042D7C6AE204ULL, 0x19233FCF2C256CC2ULL, 
            0xDD23111F485057F8ULL, 0xA937F9680DAF086AULL, 0xDB14CB87524C61A9ULL, 0xB3641D0A2998C4BCULL
        },
        {
            0xEC1282B0E178F247ULL, 0x3C1006C997E6254BULL, 0x951A8CE9A6BDCA96ULL, 0x4F5CEA31745C3C8DULL, 
            0xC5D2006D44DD5D59ULL, 0xFFF3F4B1D4F7CD49ULL, 0x49253A620CAB9925ULL, 0x2312595E79106A42ULL, 
            0x3F800B738BF2CFF5ULL, 0x0D5799BD6B67C58BULL, 0xACDCABAA83B5BAABULL, 0x413737004AB3DED8ULL, 
            0x2121DC2E9F0DD6D1ULL, 0xC7707E606BC3A9D3ULL, 0x27A11EF802E10644ULL, 0xEC946541A6DDF195ULL, 
            0xE4E5AA3995773CE0ULL, 0x179F89DF17DF1993ULL, 0x6A301690095DB3A1ULL, 0xAB29B1A6F7BE11EEULL, 
            0xB5CD35008583B897ULL, 0x7EA8E7BBAB547ACFULL, 0x13BD95CC7AE1DDCFULL, 0xE5AD52CA486A0932ULL, 
            0x0223750799B3AA6EULL, 0x69E3DF0F9C4C77CBULL, 0x595DF4D91718AD64ULL, 0xAB49C1993351526BULL, 
            0x38E061F9AA1EFBFAULL, 0x63B9F99B41EF4201ULL, 0xAD8A753EFAF587DDULL, 0x9916A8EF64B298B2ULL
        },
        {
            0x1F02124A1DEEABAEULL, 0x89EDD066DC60CED4ULL, 0x1155D8A42D6A9706ULL, 0x5FC4AEAAE0B911F9ULL, 
            0x66CE67FC791B8390ULL, 0x019DB6FF0E991DCCULL, 0x159B7298E4AEB4C7ULL, 0x9744DD997BE1E4ECULL, 
            0x2D4EB9C62696EDB7ULL, 0xAD489AA975CDD449ULL, 0x14372AE062BCC788ULL, 0x470D9EC7EC4AE935ULL, 
            0x3944F096CE217126ULL, 0xB04E1836DDF57883ULL, 0x4EC446D6AD1D5355ULL, 0xBFFAF43368126835ULL, 
            0xF692E0381474BD56ULL, 0xBCBF1CF521A50AABULL, 0x77225B96CA53FFB8ULL, 0xE560CDBF8B1F6261ULL, 
            0x920F2CC772F4250CULL, 0xB8A9AAE2E8F52FFDULL, 0x2DFF702E47E941E7ULL, 0x779E7279FA32964FULL, 
            0x2D99D1443EC62B87ULL, 0xBDF012117D8EAA71ULL, 0x4A45011E924E7906ULL, 0x8F8BD2B40F3766D0ULL, 
            0xCAD10270681D037FULL, 0xB62E6AF522CA7051ULL, 0x410BE240AFD47526ULL, 0x7364842A64337A2AULL
        },
        {
            0x31399FA80A0881D2ULL, 0x216338405B26D0A0ULL, 0xE888BFE50D89C126ULL, 0x0F51D3C4EF4EC7D3ULL, 
            0xA7BA06118C6318B5ULL, 0x2F911D47F880FA61ULL, 0xBFC60294A1D20990ULL, 0x2871CF4FFDCC91FBULL, 
            0xA8ADD0DE14C3FB98ULL, 0x6EDCDF1DBA8BBAB3ULL, 0xA21F52D61CB032DCULL, 0x6B4D1716F87D2DD5ULL, 
            0x35792D91E8C1C5BCULL, 0x88184C6E6AF4F038ULL, 0xC4691AC00502F08FULL, 0x7020A8890AE8F2B4ULL, 
            0xBA42EA5758AD84B6ULL, 0x27839B55A54117A3ULL, 0xEA491E42D18CD720ULL, 0x25E3B1B4B0CCAD4EULL, 
            0x30B96E920BB79DF8ULL, 0x5EF9762FCCFDF3F6ULL, 0xF2D223633C52DF38ULL, 0x59AFCA62EC65A980ULL, 
            0x460A5D201F2F3C35ULL, 0xED9E2AD64DE3C2E2ULL, 0x00FB69A84B58BBBBULL, 0x321B64A3EA0DDE40ULL, 
            0x78416FE84296B072ULL, 0x2F54BF451396BAC1ULL, 0x3DD8F117DC886B3EULL, 0xF77BB217BA098A89ULL
        }
    },
    {
        {
            0x7ABCBDA60CEE582CULL, 0xDCDBF16F94ABBE44ULL, 0x01410015B7EF1C43ULL, 0xF369711C7D9AE360ULL, 
            0x00A0125C318C8A96ULL, 0xE50F5D918873084DULL, 0x5239CC7CD946A274ULL, 0x94BE21251A5F2B6FULL, 
            0x3223727BCF4EB62DULL, 0xA669350E1C800C08ULL, 0x3E12EDAF0B978733ULL, 0xEE23D938E1171087ULL, 
            0xFAD01AAC09D988C6ULL, 0x42C4FC591258549CULL, 0x229301269460F2CBULL, 0xC78BF9E41585487DULL, 
            0x0C75AE8833718E77ULL, 0xE412196BCAD54A4BULL, 0x3C94A7DDC1E3DF49ULL, 0x9127320E080F0D69ULL, 
            0x844C0B41D9DEC18AULL, 0xB0C539F5912D878BULL, 0xED6BBAE9F8B38931ULL, 0xBFB86CA6E8FA79EEULL, 
            0xF473465E46559082ULL, 0x2E79B9E846661119ULL, 0x632974BB5D332CB3ULL, 0x92719A87214F4D25ULL, 
            0x6D2316BDF905AF36ULL, 0xC3A48B16C1756F94ULL, 0x13B11377B36C650EULL, 0x74BDE71778F73EE1ULL
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
            0x8F539E58862074E2ULL, 0x448757977710FCA7ULL, 0xEF12CEDEB2BCEE69ULL, 0xDA850D58052B0097ULL, 
            0x8B512D2CBBF7098DULL, 0x282039B3D057E311ULL, 0x7DDBDB9DE79BAE6CULL, 0x461512CAE7CB119EULL, 
            0xE4EF360FF94FD5A0ULL, 0xE6762799FB64AD49ULL, 0x1091AA52E78519BCULL, 0x6A4FFB614126F218ULL, 
            0xDCB9A21DEE472DBEULL, 0x60C13F564AAB4F97ULL, 0x020F4586AF99B2B4ULL, 0x3E624D29D6B9760AULL, 
            0x832EAF34B038F072ULL, 0xD54C1321DA49D56DULL, 0xA349C067134BD261ULL, 0x15F06F1F88299D4DULL, 
            0x4EE93E1B0B719373ULL, 0x0861A81336C64F69ULL, 0x463A07CEE8F635F7ULL, 0x074BA99501276E25ULL, 
            0x0D3E97F774EB2F3BULL, 0x39BDD4F0634D55D5ULL, 0xE37C6B6689569DCCULL, 0x0CB2B8466A28347DULL, 
            0x30C80C423ACA2B85ULL, 0x01E268DEFD6BEA1FULL, 0x13A126DF2E2D6860ULL, 0x1289249DC8C8A5AFULL
        },
        {
            0x8B466A76690DF63AULL, 0x07B2FEB89FADCAB1ULL, 0xFBB730B5FB7F7050ULL, 0xF69A908574F19781ULL, 
            0x9F5CC704FF534FFEULL, 0xE3D3E9E867447065ULL, 0x3DBFDB455B3ED2E3ULL, 0x51C984E855D0975EULL, 
            0x0A91131891146BDBULL, 0x3050590AF51D0741ULL, 0xFFCC21E5AFADE097ULL, 0x04E516E475248032ULL, 
            0x60186372595171D2ULL, 0x1CD7B71A5CAF9F45ULL, 0x716E34A4143ACE1BULL, 0x4A0B8AFF8B1FDBE6ULL, 
            0x38FA7F2B8032C666ULL, 0xE209BAB874A7C74BULL, 0xB77CC9C94E8C30A2ULL, 0x07C3D9C57DC50699ULL, 
            0xA40012F41A9C727EULL, 0x6474E02CEEF851B8ULL, 0xAB12F273F525BA25ULL, 0x8352E854376C9106ULL, 
            0x2E3E52FEE2592399ULL, 0x491E44F9FF019B3EULL, 0xC9942A364F437B9AULL, 0xD9CC035030D815AAULL, 
            0x4056A95462C33FEAULL, 0xE23B9FFEDDB3F99BULL, 0x9CABCF4809A246A6ULL, 0x5638AB3E610BBF81ULL
        },
        {
            0x7452909ECF3A14B5ULL, 0xD1FBB8A6C6560DEFULL, 0xE380D41E55AD09BEULL, 0x9ED4B3CF070B5AE4ULL, 
            0xCBF32445F7E8E170ULL, 0xCD2E4440C0EA5470ULL, 0x4CC34E03D5DF81DEULL, 0x1E8839FD9C331FEFULL, 
            0xD4D49FE950B83DBEULL, 0x8D02519E33E78B30ULL, 0x99EECC6A7A7C7563ULL, 0x2E87B665899A0D67ULL, 
            0x20CA2F8D829C3AAFULL, 0x79367D2AAED54A61ULL, 0x6076ECF7F2A0E0FCULL, 0xD6B62767DEE7E4E7ULL, 
            0x1809FF0733B6D1BDULL, 0xA18FCD4FD7BDB2E3ULL, 0x97574481948D7404ULL, 0x6675A141D9A3DDBBULL, 
            0x96E112A8667CF741ULL, 0x21C606F8D8F07D07ULL, 0x2E34D5BB097F6365ULL, 0xACB20BC25491B15FULL, 
            0xB852C96F241F3D43ULL, 0x150CE860D0805A38ULL, 0xEA4CD9537BFA6E21ULL, 0x8B4E1781ABA29D20ULL, 
            0x68957E178DC0615AULL, 0xA0FED3D2F35997B0ULL, 0xE6C8C1E79363FE24ULL, 0xFAE878EC0C889CBAULL
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
        }
    },
    {
        {
            0x28C9C5EE180095BEULL, 0x40BE97195970B13BULL, 0x228A0EEC62ED09ADULL, 0x22FAF63050EF59BCULL, 
            0x708F092F62FE95D2ULL, 0x607C6380DCBA8B66ULL, 0x88F39469CC635BAEULL, 0xF3AF1140C9957D9DULL, 
            0x77588F883B29DBA2ULL, 0xD910D2E43F4A8C33ULL, 0x25C90611D3F928B7ULL, 0x86FAC4171E546A17ULL, 
            0xADFEC14B773216F1ULL, 0x5370CE5CA77320DBULL, 0xED07DCFA3C257E94ULL, 0xC0555F8250F628E2ULL, 
            0xBEC34347B83FBCE9ULL, 0xC199503FAFC420F5ULL, 0x7D23693D99C97F45ULL, 0x352BCCF05ED4CAF6ULL, 
            0x0FF79A0128218DBBULL, 0xD9A09769BBF3CA65ULL, 0xDFFC40AFDC213A8FULL, 0x2A120081ED0BF553ULL, 
            0x320ACCD6469B235CULL, 0xC8645F665F53D28BULL, 0x676F19162947C725ULL, 0x1DD13844F75F8260ULL, 
            0x88E45B65BC29F623ULL, 0x610CFCB1C805E0ECULL, 0x956E4653C20DD81CULL, 0x8B269BA90F7E8442ULL
        },
        {
            0xDA99C4C00068863AULL, 0x1982E06289D47379ULL, 0x4CF2B1936290AB0DULL, 0x017A00C9A657EDB3ULL, 
            0x242A2F2473639497ULL, 0x25FB66E22D8A317BULL, 0x35BD54ED37586F1BULL, 0x62F6757231780708ULL, 
            0x762A33900620A134ULL, 0x06B3A115C9350178ULL, 0x1B81F106C1A209B6ULL, 0xE4616F4644A61CFCULL, 
            0x1D20B451EE99907AULL, 0x2DF7955BA0FFD353ULL, 0x47AB8CB56772834BULL, 0x264BD9511132E106ULL, 
            0x304FE734D050C871ULL, 0x5F5F7FE9C1F8DC45ULL, 0x935A17EDFFF7F4F7ULL, 0x948D726EF1AA2399ULL, 
            0xD728217A837A8106ULL, 0xA532319501F070DEULL, 0xE6233B5CE5F4F112ULL, 0x3CE12B247C0E4D80ULL, 
            0x6D98C92A95C237CCULL, 0x112C7C3221DDD0BDULL, 0xB7FC2AC1FAF5F8BCULL, 0xE6609FD000888C64ULL, 
            0x69F43312EB869322ULL, 0x631E593590482A8CULL, 0x0CCB4ADAB8281E9DULL, 0x111519872E59726CULL
        },
        {
            0x71966B87A946CE18ULL, 0x2C3A874033E7A7E9ULL, 0x3C642024D57F7952ULL, 0x71ABDBF2682B9C18ULL, 
            0xE3BE9B390A0D4D92ULL, 0x02B3BA74F52678A8ULL, 0xF6B954756A486D09ULL, 0xE280BDBF28318FDDULL, 
            0x1FF861EDE8CBA7CEULL, 0x59A8CA472BB7DEA5ULL, 0x3929F048B2DB11A0ULL, 0x7ABB4DF1D3E6A211ULL, 
            0x5F4DCE12767FD57EULL, 0x69AF67F8AC5D7E36ULL, 0xA097AE69EED3F121ULL, 0x3C47C96295ED7948ULL, 
            0x10A9AA2397E21E3DULL, 0x1619C18F6286B279ULL, 0xD366319F81F66EAEULL, 0xD3E5429B0D33AF76ULL, 
            0xD05DA0531EDB80CFULL, 0xDE88C8FCB17FA125ULL, 0xFDD366AD8FB46A08ULL, 0xC02118608E9062D7ULL, 
            0x65672749AEF03B11ULL, 0xA82C754B6199FBA1ULL, 0x4E178A1A2607A501ULL, 0xDC154E2C16F27CD7ULL, 
            0x89F04D0BF08737A1ULL, 0x38E0877775034DC0ULL, 0x39A19ACB1A94DCB2ULL, 0x84CAAF03874478FAULL
        },
        {
            0x2FD8DEBFA3C0E2A5ULL, 0x2D91CD0BF4CF6E22ULL, 0x739201B05049CEEEULL, 0x51B1CBA358870A1CULL, 
            0xF6CE20DC50B36ED0ULL, 0xF25E4AE49B4A62DCULL, 0xCC9BAA681139844BULL, 0xEB4B69809B6C51BCULL, 
            0x62229F66C8DF9A43ULL, 0x2C00C2F9BAE09095ULL, 0x1EC7E52D4FF3A830ULL, 0xDCFE6A65EA34ECEEULL, 
            0x448D0BC3419E6CF1ULL, 0x88C0F72D694CC499ULL, 0x764809816E41E477ULL, 0x8A047EAC80C747C4ULL, 
            0x8FC4C7F314F3B37FULL, 0x522FDEF86C134B80ULL, 0x3C4EFB99844E755CULL, 0xBBFFFE3C00364473ULL, 
            0x93A8DE4B3934DF98ULL, 0x29DA05CD019C5B49ULL, 0x53AA02D05FF144F8ULL, 0x75AAC79091ABEB1CULL, 
            0x0958929EA24F3051ULL, 0xAE8CBE56EDE41A2CULL, 0xB0854D2A56132DD7ULL, 0x4AB85D8A6687A3FEULL, 
            0x1D63E5EF0887714FULL, 0x4CA172FB6F4D5D6CULL, 0x06ED28709BA11ACAULL, 0xBB33150533269D79ULL
        },
        {
            0xCAEFA34847765233ULL, 0xCD5736D9FE8FBBD4ULL, 0xA82F901B27B16876ULL, 0xDB8597B7F73FAE58ULL, 
            0xE93CA2280186F529ULL, 0x384A9D6254CF1F8AULL, 0xE9A5AA0E9447850BULL, 0x8CAAB3C0BD643F07ULL, 
            0x235F00C58B6986A0ULL, 0x2162BF40D8BB98B8ULL, 0xF46E7A16D7F30562ULL, 0x3BC54C4D4ABFCBC9ULL, 
            0x7D7C579C15D5497FULL, 0x3A89FDDF8E027D4DULL, 0x26BC020CF87CBBC9ULL, 0xB0F08CAE40A8A6E6ULL, 
            0xE93101F47C5EA6A9ULL, 0x24251F9DD8BECF8CULL, 0xECD53DA51399FA7BULL, 0xF8D41836C8B9296EULL, 
            0x2D662443377068A9ULL, 0x206D989CC1253AE4ULL, 0x9897710CF7A565A7ULL, 0x9C2A2E3439970893ULL, 
            0xCA9744532697E616ULL, 0xE09BF7A77A5880B1ULL, 0xBEAEB6FA738F1347ULL, 0x0AF97A95F5DAD47DULL, 
            0x09A543616FA4C01BULL, 0x728DB608F3339EF1ULL, 0x77940C464AA2FCC1ULL, 0x42397D6C0E38AAA2ULL
        },
        {
            0x1CE528DC35A6D9C9ULL, 0x468C9A0D982EAE26ULL, 0x9572B1702D4B261BULL, 0xA3FCA6DE384C56ADULL, 
            0xEF36064DE52C3382ULL, 0xDCF3DE92E2D85856ULL, 0xE2B68DBBAEA3E5F2ULL, 0xD41CB92170ED5331ULL, 
            0xC7664A835C04FA8CULL, 0x49085AFA50DD83D0ULL, 0x133735DCEC23DB3EULL, 0x363290459F8352B1ULL, 
            0x629D343012F75783ULL, 0x94CBB9F8050262E1ULL, 0xC92EE287A34CB87FULL, 0xC926D750931C18CAULL, 
            0xE8920105DD59E748ULL, 0xD5C0693FA0F3017CULL, 0xDE5EC68B3842BBF8ULL, 0x0F6EB7F1E4BA56F3ULL, 
            0x39BE961F2354FA61ULL, 0xA931DAD8D6372091ULL, 0xB7308257AD9DAB88ULL, 0x4315F3B2909E44A9ULL, 
            0x97604547DB5D4BFCULL, 0x14B9B9F8E7115B42ULL, 0x034BEA03DFA2FC7BULL, 0x863E5FAC505F801AULL, 
            0xFB504CC95B66B630ULL, 0x2D3BE394F6448570ULL, 0xC7FC06BFDE5CDB9DULL, 0x77E7F65112F54989ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseHConstants = {
    0xFAE7F187CB8DA3B3ULL,
    0xBFC728B272CFC994ULL,
    0xDE4919EAB92619B0ULL,
    0xFAE7F187CB8DA3B3ULL,
    0xBFC728B272CFC994ULL,
    0xDE4919EAB92619B0ULL,
    0x4BEA631799BE91EAULL,
    0x8E974ADC0F5A4D8AULL,
    0x4F,
    0x82,
    0xAD,
    0x71,
    0xEC,
    0xCA,
    0x4E,
    0x7C
};

