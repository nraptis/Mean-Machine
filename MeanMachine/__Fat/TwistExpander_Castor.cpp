#include "TwistExpander_Castor.hpp"
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

TwistExpander_Castor::TwistExpander_Castor()
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

void TwistExpander_Castor::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xCE6027506150CA78ULL; std::uint64_t aIngress = 0xB8D366E37B1825BDULL; std::uint64_t aCarry = 0xD89D60C625D197B7ULL;

    std::uint64_t aWandererA = 0xFDF062E4016536BAULL; std::uint64_t aWandererB = 0xD9F871A66E7628D4ULL; std::uint64_t aWandererC = 0xE59DA951CB113E34ULL; std::uint64_t aWandererD = 0xF06B041D6FBD1A4BULL;
    std::uint64_t aWandererE = 0xABE31DEEF6EBD8C1ULL; std::uint64_t aWandererF = 0xFF878A695C471AD4ULL; std::uint64_t aWandererG = 0x824BA46A0F1E8C1DULL; std::uint64_t aWandererH = 0xB2EDC85A93C2F951ULL;
    std::uint64_t aWandererI = 0xE6A23A29379061FCULL; std::uint64_t aWandererJ = 0xDCF485474AE856D0ULL; std::uint64_t aWandererK = 0xD766DEB698F51E0CULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15140957585901306053U;
        aCarry = 17975092554339990463U;
        aWandererA = 13774268169750759052U;
        aWandererB = 16758012994902563665U;
        aWandererC = 9875663838087788509U;
        aWandererD = 16760746620465465191U;
        aWandererE = 11998086835261554853U;
        aWandererF = 11933178827249317914U;
        aWandererG = 16420548581054190389U;
        aWandererH = 11210842622601545009U;
        aWandererI = 11967791842885391286U;
        aWandererJ = 11156099980147879241U;
        aWandererK = 17434612427188391508U;
    TwistExpander_Castor_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Castor::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE329E763C3512EB1ULL; std::uint64_t aIngress = 0xB0AB09888D749953ULL; std::uint64_t aCarry = 0xEBB5666541D28DFAULL;

    std::uint64_t aWandererA = 0x9A9919804AC13B54ULL; std::uint64_t aWandererB = 0xD1FE118ABD32474FULL; std::uint64_t aWandererC = 0x82F83D39BBAFF00FULL; std::uint64_t aWandererD = 0xEDFC5B116BDD81D5ULL;
    std::uint64_t aWandererE = 0xE978D43146359FE5ULL; std::uint64_t aWandererF = 0x91984E4DF411469EULL; std::uint64_t aWandererG = 0xA3FA6C4D16320FC4ULL; std::uint64_t aWandererH = 0xFFEBB65D4946A02FULL;
    std::uint64_t aWandererI = 0xC3EFA301B0F5C7E2ULL; std::uint64_t aWandererJ = 0xBF3EE9A4840A050CULL; std::uint64_t aWandererK = 0x96F75F9CE54D3F66ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11584429455815089461U;
        aCarry = 17803038650596993994U;
        aWandererA = 10095361593272385487U;
        aWandererB = 14300876778772672408U;
        aWandererC = 10134821991156072442U;
        aWandererD = 10591652431755752551U;
        aWandererE = 11122081894157486074U;
        aWandererF = 15790506989278490373U;
        aWandererG = 16438379168580944762U;
        aWandererH = 15065179905111880118U;
        aWandererI = 16923062542276112347U;
        aWandererJ = 17923093869002884842U;
        aWandererK = 15721210517428756533U;
    TwistExpander_Castor_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Castor_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Castor_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Castor::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE35AB2226559A5B7ULL;
    std::uint64_t aIngress = 0xFADD44838F755E44ULL;
    std::uint64_t aCarry = 0xD0060CAB58CA834BULL;

    std::uint64_t aWandererA = 0x8C19E78B91575F7DULL;
    std::uint64_t aWandererB = 0x801A04490C585F4AULL;
    std::uint64_t aWandererC = 0xC527372F6231567FULL;
    std::uint64_t aWandererD = 0x92BCEC4EB1F1EE68ULL;
    std::uint64_t aWandererE = 0xD392174C0FE14CA5ULL;
    std::uint64_t aWandererF = 0xEFF025FA0F0D8165ULL;
    std::uint64_t aWandererG = 0xCBC534E5A2DF0839ULL;
    std::uint64_t aWandererH = 0x9E6D88E091EF0940ULL;
    std::uint64_t aWandererI = 0xD68131B72DF2237CULL;
    std::uint64_t aWandererJ = 0xD8E246EA26CFD167ULL;
    std::uint64_t aWandererK = 0xD0BE0BB8DB8538DEULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
    TwistExpander_Castor_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Castor_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Castor_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Castor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Castor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 16 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1827 / 1984 (92.09%)
// Total distance from earlier candidates: 27815
void TwistExpander_Castor::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 744U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2014U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1430U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 52U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1227U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1137U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 685U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 398U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1084U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 64U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 739U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1176U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1820U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 343U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 18U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 387U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 140U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 670U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 24U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1693U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 295U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1624U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 257U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1981U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 274U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 291U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1055U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1608U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1818U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1988U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 864U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 657U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1556U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1462U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 230U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1643U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 304U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 424U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 933U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1726U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1734U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1740U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 60U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 589U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1319U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1962U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1286U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 336U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 5U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1135U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 828U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1272U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1910U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1035U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2011U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 796U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1500U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 773U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 44U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2007U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1400U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1331U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1931U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1082U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1574U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 197U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1252U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1377U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2024U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 706U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 3U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 158U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1772U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 188U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 972U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 603U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 233U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 982U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1906U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 477U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1148U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 472U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 338U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 651U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1954U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 640U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2032U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1410U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 789U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1143U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 783U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 812U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 593U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 754U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1600U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2029U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1194U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 379U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1122U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 36U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1898U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 193U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 652U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1957U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 169U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 27U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 199U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1229U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 725U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 204U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1315U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1423U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 702U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 767U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1506U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1317U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1239U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 831U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2027U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 134U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 751U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1944U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1953U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 786U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1975U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 770U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1948U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1815U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Castor::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA0FC83BD9014EBEEULL; std::uint64_t aIngress = 0xB02D5DCA781DF3FFULL; std::uint64_t aCarry = 0xD3EBA44D06BE013CULL;

    std::uint64_t aWandererA = 0x80123B11F052686AULL; std::uint64_t aWandererB = 0x83F37EF64C4C8FC6ULL; std::uint64_t aWandererC = 0xE9D58A01F971FC90ULL; std::uint64_t aWandererD = 0xC88186D1151A1041ULL;
    std::uint64_t aWandererE = 0xD669672C301FAD2BULL; std::uint64_t aWandererF = 0x8F690B5F7303C688ULL; std::uint64_t aWandererG = 0xBFCA45380C2E6E3BULL; std::uint64_t aWandererH = 0xC7B4C1448A468123ULL;
    std::uint64_t aWandererI = 0xF85CF171F59F6349ULL; std::uint64_t aWandererJ = 0x8A7922A74EDADC9CULL; std::uint64_t aWandererK = 0xF0B6D96F927AB3ECULL;

    // [seed]
        aPrevious = 10110458772551078055U;
        aCarry = 9814245518706656327U;
        aWandererA = 16900944231626335641U;
        aWandererB = 12587621828281237156U;
        aWandererC = 11305829048291061112U;
        aWandererD = 16853618894435604889U;
        aWandererE = 12475294672444082918U;
        aWandererF = 14063661669164382058U;
        aWandererG = 9535115493990965332U;
        aWandererH = 12404100254668988445U;
        aWandererI = 16714780610794634532U;
        aWandererJ = 16641533631231845927U;
        aWandererK = 15500120061512885398U;
    TwistExpander_Castor_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
    TwistExpander_Castor_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Castor_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Castor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Castor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 16 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8207; nearest pair: 515 / 674
void TwistExpander_Castor::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4733U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6947U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2120U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8143U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6712U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6603U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7473U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6962U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4735U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6160U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6172U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3086U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2965U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7724U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7709U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5628U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1653U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 513U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1835U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 820U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 339U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 22U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 485U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1839U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 200U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1679U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 73U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1178U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1884U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1347U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1060U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 746U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1284U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 163U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 947U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 702U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 16 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 8225; nearest pair: 502 / 674
void TwistExpander_Castor::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4990U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1232U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7442U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4652U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5630U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6760U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5025U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2783U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 543U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5470U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6611U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7289U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3268U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1416U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4107U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 269U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 281U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1696U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 185U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1964U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1756U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1580U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1745U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 568U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 837U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1181U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1363U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1958U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1091U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1647U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1987U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1872U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 315U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 513U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1490U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 903U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Castor::kPhaseASalts = {
    {
        {
            0x5A9B5EBEA45133BAULL, 0x3D2BAD588762007BULL, 0x4DBDB71E241DF620ULL, 0xCBE455B61C7822A3ULL, 
            0x40021D3B6D82CE64ULL, 0xF45DF44766A2BC7AULL, 0xB9F5219442F0C845ULL, 0xAAF98AC1A353BABEULL, 
            0xB6F45C183127B24FULL, 0x5C428CE60A3A3834ULL, 0x28E2FC716D61E4A7ULL, 0x833A676F6F903964ULL, 
            0x54A1822ECD9C85D0ULL, 0x203ED0219045E1CFULL, 0xE416C62BB7545C8BULL, 0x1383FBA379B82926ULL, 
            0x3B69B5A494B29C08ULL, 0xFF3782C79EE41029ULL, 0x8B020B58D871F77DULL, 0x0600CC49E1542D98ULL, 
            0x66A47442BB2BA967ULL, 0x86E31D182F048491ULL, 0x04878DCB781C9CB2ULL, 0x03773FF29BD6BAEDULL, 
            0xF3B3F10F3FFD11ADULL, 0x774723FDF1713A4EULL, 0xA54BD627998A1857ULL, 0x3003E2A2DF56C016ULL, 
            0x149A1DD287AF9D1AULL, 0x25D0F33A942EB118ULL, 0xDFEFAC46DC86B33BULL, 0x1AED36B7F640C430ULL
        },
        {
            0x3A61CEBAE01604EDULL, 0xBAB52E98094073B6ULL, 0x206F88CD5091381BULL, 0x7A0AB8EF4957B02FULL, 
            0x915D06C06D7C36D6ULL, 0xC0EA58EB2D0B359AULL, 0x96914428B8AC25D7ULL, 0xB99EAF4574A4BE31ULL, 
            0xBFD46C0D68FC5BD9ULL, 0x35F46A75906D0AAEULL, 0x7BD47F1E5F0CB95CULL, 0x97F23A199E35582BULL, 
            0xEEC8D2D48B92A5BCULL, 0xFAE2FFD3ED4812C4ULL, 0xE40F2E5E153EA54DULL, 0xC953C2B30FBAD6C5ULL, 
            0x5E7A4D6BB84631C6ULL, 0xBBF2D42F57723E22ULL, 0x93CE1B74FB00A16DULL, 0x4811812F30CF717BULL, 
            0xCB8BA80F712F4C2BULL, 0x4208BD14529DCFB0ULL, 0x3B4C625089F50CAAULL, 0x97B691B5C37566E9ULL, 
            0xB7FD3936F3E3FEA1ULL, 0x07F82DE6086E7431ULL, 0x7CAB33165DDA7F42ULL, 0xF4B87A3C095D2067ULL, 
            0xCE8CB00AA80F3530ULL, 0xA7D9691DF24F7C7DULL, 0xC93FB8D48F658D84ULL, 0xEF23A37430B8C108ULL
        },
        {
            0xFDD1C29195413901ULL, 0x9670BBED5861EC6AULL, 0x11B6AB1015FC555BULL, 0x69344496A5D06C78ULL, 
            0x5A588ABB9BD928C2ULL, 0x460A49327EC819A0ULL, 0xA59A14FBA7B9B922ULL, 0xAE4CFDC7FB6CE19BULL, 
            0x31DEFB173C9939E5ULL, 0xDF3BA7B3B0A8F941ULL, 0x9CA80E2DC4AAA475ULL, 0xEBBB1F2583CC1BA7ULL, 
            0x2FFBB31CD2361FEDULL, 0x22D2BECFD09377FBULL, 0x829A4C5FFC9FE7B5ULL, 0x43121B3DA4F447ACULL, 
            0x03945CEA99EAE0ACULL, 0xDC497615B0B7C45FULL, 0x489937F45EF3A398ULL, 0xDBA305A262F7FD66ULL, 
            0x1BB0DE0831EBC600ULL, 0x9ED12768B08F298DULL, 0x010F64443E7DC6A4ULL, 0x6A146C82EE8C2AB6ULL, 
            0x623251F237248440ULL, 0xBC8805FFB210EA49ULL, 0x2E6E48E1B6893BC6ULL, 0xE985375214AF5396ULL, 
            0x5FF33E4ADDCC8C1EULL, 0x0160C4707C1FCC0AULL, 0xAAFF40345F2087ECULL, 0xD08A2775E616C65CULL
        },
        {
            0xBAA4E138A7606B13ULL, 0x1A4E9D36144260D8ULL, 0x71C2EF7D2D14BAD9ULL, 0x49BF393BF975C462ULL, 
            0x2BBBAA981963021EULL, 0x6A2621BF429A51AFULL, 0x54092286C89C6149ULL, 0xA7D9752F6C43DFDFULL, 
            0xA88266B79FA1E0DEULL, 0xA344133D6ECB3CB9ULL, 0x322D834DBE526A22ULL, 0x62764E9E05E144EBULL, 
            0xC7DBE8A3FEB52571ULL, 0xB1C55DC15375E973ULL, 0x3144BFA5E558C116ULL, 0x01BB482421C67C17ULL, 
            0xD5EAB72102DE203DULL, 0x8BE99070136B87A1ULL, 0x2D9BDF13082C1D61ULL, 0x1B02615E8B445671ULL, 
            0xD0947D5318FE304CULL, 0x289147B368735216ULL, 0x16C5DD13735F00B0ULL, 0xE86FD92786623AF5ULL, 
            0x6B62C4C8BEB3AC86ULL, 0x6E490794893ABFC1ULL, 0x180A3A2FF2B08B78ULL, 0x927837A7425D16CAULL, 
            0x82EA0FBE2FE2BF6AULL, 0xB354960976DD0E40ULL, 0x00C4D9AAB2EBB647ULL, 0x5DA7BFDADCAF1D44ULL
        },
        {
            0x12B5080F5FE2C2F8ULL, 0x08F6C7934077052BULL, 0x00948AE103A4C654ULL, 0xEF8385B155C77972ULL, 
            0x562B21E702A4207EULL, 0x9C27B84C46EDFFD8ULL, 0xF0D1175ACA381F7EULL, 0x9C071AB083AFB29DULL, 
            0x2CA8B545C8518DEAULL, 0xFB4973948861CBFAULL, 0x9272A0CB55EB695EULL, 0x412B53EFC583DDBEULL, 
            0x62FFA5CFB4EF0CBEULL, 0x1FB7665DEDFC7C63ULL, 0x7C58D4C9C736A868ULL, 0x1B86905929163654ULL, 
            0xAF70BCF16A607D9FULL, 0x4E22E25BBAB2263AULL, 0x979162104B5F7F8DULL, 0x7E3787A1EE15D20CULL, 
            0xFC558A45F96F6670ULL, 0xF31B2BCED00E0ABFULL, 0xD2A3DFC2020E1274ULL, 0x772BC396DCF4BEF9ULL, 
            0xA7CFDC5B8CFAD846ULL, 0x5C9A2643F4F1BA68ULL, 0x7542F2FBEE97D167ULL, 0x2B96E4B53923AF44ULL, 
            0x8EE4509441B3551EULL, 0x850D3DFFB99A6EAFULL, 0x0EA2E34F11AA3105ULL, 0xC93F676C5A9F2F77ULL
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
        }
    },
    {
        {
            0x66408F01509751F0ULL, 0x1636FCB81B47CE71ULL, 0xC057CD6A4FF0FF6DULL, 0x819730CDF8B2FE27ULL, 
            0xAAA9F5AAE2A19E06ULL, 0x631607A7FE5C191AULL, 0x83E8C73E37FF3518ULL, 0x308734B6E6BB3F20ULL, 
            0xA61E8F8B8302A910ULL, 0xC4BF12631F81BDECULL, 0x52FF2611C0C7304DULL, 0xE84CF933BB521124ULL, 
            0x3D5CAEC8DDFDAB3EULL, 0xB2BB5AFC76CD31B5ULL, 0x8AB3AFB65D3573FDULL, 0xF2E490274E92DA91ULL, 
            0x94F79F2B6E170236ULL, 0xE2EB1BEE3FDABBB1ULL, 0x68CE8524EA2379F1ULL, 0x5B79A0F0DD71D9CFULL, 
            0xC3818F2CFF47ADB3ULL, 0x1BC73AF8895F1080ULL, 0x83919D5BCDBF1071ULL, 0x5C150471CE9FFDE1ULL, 
            0xF3C43DD88335429BULL, 0x365EEE20048C496BULL, 0xE8644085AC0E3C3BULL, 0x0AE83F3A2339AF06ULL, 
            0xD12CCC160ED6F829ULL, 0x3CE2DF3AFD6E97E4ULL, 0xD5568E71CD15B01CULL, 0xA569F5BC3D09CB2BULL
        },
        {
            0xD90670820B67846BULL, 0x451B238FD78C42E7ULL, 0x27D966F5C14657A7ULL, 0xBB714E5F97F2D085ULL, 
            0xC09A3F9DFF00D609ULL, 0xDABF1D69A31FF948ULL, 0xB4E38D4C6C3E8789ULL, 0xFFCB9C96B536825DULL, 
            0xCB4131EEDCD68C8DULL, 0x737C1DC777CFA80EULL, 0x327446AAF98E0CDDULL, 0xCC72BD98392D6A52ULL, 
            0x57BD0E231DDC5A36ULL, 0x0B3FB032DB5164BAULL, 0x6C6675BA38AECAD2ULL, 0xA218C2EDE889690CULL, 
            0x152D699B9EA8EAF3ULL, 0x61B50849B2F4F89FULL, 0x468C83A9BB484635ULL, 0x564E03D260B58D72ULL, 
            0x50F936E757169FB4ULL, 0xE19D1D5FE0F8A96DULL, 0x327AAF947AC261DCULL, 0x7B0666F0DC4BF6A7ULL, 
            0xEE2D71198093B7C2ULL, 0x752669665414A896ULL, 0xB1E69F419C56B20FULL, 0x7941EAC6A0D89941ULL, 
            0x276E4CDE21DAAA4AULL, 0x58061C4635B32ED7ULL, 0xB6DF2F72521436BEULL, 0x5B156D98D3331A20ULL
        },
        {
            0x723C6C33513DFD0DULL, 0x7B130B33FA09E89CULL, 0x96CC88FCC6F5EF0AULL, 0xCF7B6CF57A6567E2ULL, 
            0x87A286CE0012361BULL, 0x1853FC50C245B810ULL, 0x8099187F8E1DC916ULL, 0x068CDDE9BE50DDA3ULL, 
            0x7D8F63A4E08DB427ULL, 0x632EBD0EB1A0D97AULL, 0x4B3F8380A6D1522CULL, 0xFF07990484DBCB33ULL, 
            0xA9373183835D4B9FULL, 0x8EB87210A2117DAEULL, 0x44F87617A171202BULL, 0x51ECC05BCBF89C67ULL, 
            0x4635E4413B6786F1ULL, 0xBF8E1769638DF369ULL, 0x6F8A6C8E8E804CE7ULL, 0x309CDED30DBEF6FEULL, 
            0x0F974FF6C14BD199ULL, 0x86FCDFF710BB3D5CULL, 0x0D2EEB473E60A2F7ULL, 0x06A17B3ECB42AC6CULL, 
            0x1DD4938E3150A5B1ULL, 0x39A8DE17FB50B6DDULL, 0x767A8A63FDA8117CULL, 0xA7B1127F4DE5F617ULL, 
            0xC1D212F738983823ULL, 0xEBD389D19444871DULL, 0x2AEABE7D43966E00ULL, 0x76F1BB8E15338971ULL
        },
        {
            0x48E33DC49E178355ULL, 0xF193CB59F24714BAULL, 0xAD348626F551EF42ULL, 0x283903CB903DD6E7ULL, 
            0xABC55C38578D84ABULL, 0xE92BA4E57601DD06ULL, 0x196E438A3431EE7BULL, 0x70D64EF5E26C1FA6ULL, 
            0xA56A71C2470932A5ULL, 0x4DC1A80319654C3CULL, 0xCB5AC8442761C585ULL, 0x61AA89B84F296FDCULL, 
            0x627FA95970FA104EULL, 0xC78DB7A0A5A97A56ULL, 0xFFCB56C9E758C5D2ULL, 0x0779D84E7A04057BULL, 
            0x86019CDFB7A3745DULL, 0xC45FF19297ACA61DULL, 0xB6A13BCF923D4973ULL, 0x86D217E70B20FFDDULL, 
            0x20A69480D5E551C5ULL, 0x67B5CFF741884DE9ULL, 0xD472BB4C56D35DFAULL, 0xDB265E6479292198ULL, 
            0xF37734CD30B34E8EULL, 0x6525B4B8BA34CD04ULL, 0x6F2F047FCCC0AF60ULL, 0xDDE280A8BA0AF8B1ULL, 
            0x03DDBEF0B090851BULL, 0x664D16F2E3D01FCAULL, 0x29DD2EA243963B34ULL, 0x9A0DB7898633DD07ULL
        },
        {
            0xDD9509724B513A5DULL, 0xE3134A0DD4EDA2DEULL, 0xBF242B7B30B65C7CULL, 0x0F5F6C41ABC11936ULL, 
            0x9B0AFE82740F47C9ULL, 0xFE6A304BC2EE4E09ULL, 0xB9B3B11BBF32FC28ULL, 0x2F11299DC984756AULL, 
            0xF10744ECB69CC50FULL, 0x221110F85B51C34CULL, 0x25708479E99AD18EULL, 0xC5C6C232C8475696ULL, 
            0x5E5F451040849D98ULL, 0xB8D1F4109D8242A1ULL, 0x2972068CD76FF270ULL, 0xA7079395BA0F89D6ULL, 
            0xF6B42666489A84C7ULL, 0x72AF128CD05F5373ULL, 0x15A26C0CA5D34D1DULL, 0x46D547520FB3358DULL, 
            0x7410FB11B19A45C2ULL, 0x3FE269C7351E85F1ULL, 0xDE90CAA90340B5E1ULL, 0x2261273E21F15736ULL, 
            0xA1929F51D9858DCDULL, 0x1DB41296E393630BULL, 0x16730228E63D274CULL, 0xB8145F204B9398C2ULL, 
            0xC70C3F7F956D1D46ULL, 0x9F0EC3D44B379DE3ULL, 0xF0D8904B2DDA0E7BULL, 0x7615BDA7F5840847ULL
        },
        {
            0xAA56083EC3066BC6ULL, 0x1AC590A5C3C32B56ULL, 0x81A15CDC59EFD118ULL, 0xE4511690D0DD3170ULL, 
            0xBADBA615F7440FDAULL, 0xA32179F9903D7249ULL, 0x444E1325283A6D9BULL, 0x491F84EE1EE19624ULL, 
            0xC99E2B396511CDB7ULL, 0x5FB82CE89AF461A5ULL, 0x4D4CE2959300F8CCULL, 0x64B67D2460633E38ULL, 
            0x94766899951C71C1ULL, 0x354AFAA8D6E60E32ULL, 0xE67976A7B458C551ULL, 0x15CBC3D2050CCB0DULL, 
            0x6C1060A7631FFD7FULL, 0xA6783457787007C1ULL, 0x606A470E257D1EFAULL, 0xE4AF570BF18EB2B5ULL, 
            0x3FA32D482BE05CF2ULL, 0x36B742FF7F003877ULL, 0xD8EF8C9E84D6128EULL, 0x3BAC132DE9EEB47FULL, 
            0xE94EB1E72BFD2184ULL, 0x99F24464630DB2FFULL, 0xCA3363306B49D97AULL, 0x0A069BC45D50D61CULL, 
            0x334E9B3135421D88ULL, 0x0D5271E64085DD02ULL, 0x0F2CDD0067B020F9ULL, 0x4ED3CA0F5F611498ULL
        }
    },
    {
        {
            0xF88597C8EBFE8548ULL, 0xD7B2B48170045F76ULL, 0x11850D93A59D52E2ULL, 0x61D435E68AAAD2F0ULL, 
            0xAF39F35A642365E1ULL, 0x80B461E84EECB081ULL, 0xD0F3C4A85D969170ULL, 0xBA8C34EE5465B197ULL, 
            0x0E2B256354BA6B10ULL, 0x4971634B7C1125B8ULL, 0x4EAC7BC020CA4DB3ULL, 0x93C92737B9EB37F8ULL, 
            0xBBAC698CDE6C5963ULL, 0xFA4F06F8D3B61CCCULL, 0xB7934331608D8F48ULL, 0x4A1FD471E092CAF1ULL, 
            0x41E7E3A8322BA956ULL, 0xA85F3E944EC86439ULL, 0xDA4A395B2D381D31ULL, 0xAA7101E6D9FFFF62ULL, 
            0x36B5D81D4F83D106ULL, 0x85C2E5D399E473E6ULL, 0xD4A9574704584095ULL, 0x6327D7E135A2EDCCULL, 
            0xD519504641D874CCULL, 0x9E834C5E67179FD2ULL, 0x8AC3E7F0BAA80368ULL, 0xDB509DA2EC4704F2ULL, 
            0x184C0E8E9DCAC003ULL, 0x19047ABF2956E967ULL, 0xC82A7A2C222461F1ULL, 0x84D6B69B8BEE756BULL
        },
        {
            0xF1A2AB126E49F700ULL, 0x7A7AD31D68C2A7D3ULL, 0xA56583B16441F748ULL, 0x11AA5D62DEE39C68ULL, 
            0x0A3DFDA7843CF74AULL, 0x82725137637FFF83ULL, 0x5B78FCAF88CF06ABULL, 0x4450F6F678001C9DULL, 
            0x67CBC50BF083B8C6ULL, 0x15AA57B57FD0186AULL, 0x61E70C779769A7A2ULL, 0x4D60E6D7827B0F7DULL, 
            0x8FF70A257496CB11ULL, 0x1F2BC893FB3425DAULL, 0x9C7C36516B1709E4ULL, 0x1C54FB02E1A56D6CULL, 
            0x82CE12BE8C53963DULL, 0xE2F7458D89B197E7ULL, 0x192CEDEB2B14447AULL, 0xE9E39C5CBFB6DBE0ULL, 
            0xD5F07C13A7C7C94CULL, 0x3BA7EE74C6B53C9CULL, 0x0AACCF4CF34D36DDULL, 0xBD07F27C28C55AE5ULL, 
            0xE3F5FBAF3455F0A7ULL, 0x6508A17A40DF0C21ULL, 0x353E26F542752121ULL, 0xF92ADEDC45B356FAULL, 
            0xCC5E73B5DE36A9B6ULL, 0x419841DFFA1EE01FULL, 0x1A24B63BCFDCE0ADULL, 0xDEC66751EEAE1603ULL
        },
        {
            0x859D9B01EE483B3DULL, 0xBAC193779CA7EDF8ULL, 0xBD19C426007D6BFCULL, 0x95C5DA94414FBF10ULL, 
            0x55A9CB0F6809CF10ULL, 0x83E9B232BB254A1EULL, 0xB269DC6BD80B95F8ULL, 0xA7EC0C63CD9375D9ULL, 
            0xD56CDC41D31AD7A5ULL, 0x1AFFB3F7D66BA556ULL, 0xE3E5FA9E34F631D7ULL, 0xDB27555B6FA3C082ULL, 
            0xE6252EDAEBFB25EDULL, 0x37E5F0C0102E4B95ULL, 0x43DE7834F356C4D2ULL, 0xAA14AF1F9ADD313BULL, 
            0x50E91E54E3881821ULL, 0xD6A5712DD5B2B176ULL, 0xC50FF4E6D45CBEB8ULL, 0xA48B8218CA1F901EULL, 
            0xA99A2902C0753850ULL, 0xC81F114D8323A294ULL, 0x7543C5CB31D9F4CBULL, 0x4284F3FAB150E24EULL, 
            0x3939F41FF682FA85ULL, 0x93275D58529D38A1ULL, 0x00C96366C6F71E58ULL, 0x9C01795CD5D77F10ULL, 
            0x039F57A8EFE8B07BULL, 0x57E263E34BD820C2ULL, 0x45716DD5E9702A8CULL, 0xFD2D4B35F04C9FFEULL
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
            0x22BB82542DC28880ULL, 0x43A2DC8524B27B1FULL, 0xF66AED04035BFB5DULL, 0x5A290619516BEE77ULL, 
            0x418F06C873199961ULL, 0x3CA9AE3B8BEE7722ULL, 0x4D77F5BB05F27393ULL, 0x8DAD262F8D5E6EABULL, 
            0x2275E2CDCD8D0DADULL, 0xF24EB489CC1147F0ULL, 0xD8F66E4ADE97E2E2ULL, 0xC89C92102116317AULL, 
            0xD7D2E4094441DC15ULL, 0xA51F442288448E65ULL, 0x06B9AF4C6A76EDE3ULL, 0xC870BA40FD8BD534ULL, 
            0x5A6953FC0621AE91ULL, 0xC9B2F45ED6964EBBULL, 0xF32B86F34B0DA038ULL, 0x6059843B17B3C727ULL, 
            0x7D8CD070658EFF96ULL, 0xB10221499B26C44DULL, 0x8F4E6121C7EE430BULL, 0x5A1A58FB24756CBCULL, 
            0x0E199B104D805B44ULL, 0x767319F27AFD2F0DULL, 0xD9979142B9CD4891ULL, 0x4F792F9E76E6A5FAULL, 
            0xF8EBF778930D6621ULL, 0x6083B70F1E7400A5ULL, 0x69696B660B370C81ULL, 0x1C659EFB6378B464ULL
        },
        {
            0xB76A068191ECB0B0ULL, 0xC1E8782146EC908EULL, 0xA3A2C75BD878227AULL, 0xF8494A9AE6AC8618ULL, 
            0x4C25C7763105BE02ULL, 0xFEAAEF5411F4351AULL, 0x1021D18DE0093174ULL, 0xE62226F4E8CFF02FULL, 
            0x1AC69D0C55567E13ULL, 0xB4328D4164554DAAULL, 0xF499A13303503F89ULL, 0x9A5491E12B14AF2FULL, 
            0x48CDFCDC19B27425ULL, 0x8F2F9DE1BE2990A0ULL, 0x7926C426B8EA5FE0ULL, 0x57ABA30D1241C7BAULL, 
            0x0DB7F4E252DFA23FULL, 0x3DBDD73198D8A226ULL, 0x8CB6F58C199F926BULL, 0x72A819E45066FC1EULL, 
            0xF90D4A1F80A0BCA3ULL, 0x38B5E157AE106931ULL, 0x1C5C0505D139078BULL, 0x842BB32DC6E01BD6ULL, 
            0xBD4285EB7DFFC3C7ULL, 0x83AF2E9A0FC225D2ULL, 0xCCC98807DD5E4A26ULL, 0xCEDC955A65AC7336ULL, 
            0x557FFBC12306780DULL, 0xDFA8316EE41589B1ULL, 0x82B1FCC996CA1351ULL, 0xD9B1F01142CD1C29ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseAConstants = {
    0xF5550A14E7D02FAEULL,
    0x7B229AF11047BE8AULL,
    0xE70D263F0AD78663ULL,
    0xF5550A14E7D02FAEULL,
    0x7B229AF11047BE8AULL,
    0xE70D263F0AD78663ULL,
    0x592844E771B45DE7ULL,
    0xA7F0C2EE6E6C0AF4ULL,
    0x9C,
    0x5C,
    0x9D,
    0x3C,
    0x98,
    0x83,
    0x0D,
    0x51
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseBSalts = {
    {
        {
            0xCCC64F056E798691ULL, 0x784C5166F2361D79ULL, 0x05B79A43DA010023ULL, 0x4626F722172ABFFBULL, 
            0xB41EA2CF7074528CULL, 0x5EDEBB4B27C3D5D9ULL, 0x611CEE22E10201ECULL, 0x26834B76BE9CF7F5ULL, 
            0x0FD78E9D300DFB12ULL, 0x8C8C710A1A1595CCULL, 0x1B4E5D48BDCA1295ULL, 0x66A54217BB0A65AEULL, 
            0x367DEB2945CB0923ULL, 0xB493F4FC76351D24ULL, 0x08E1EB8BC5E324CEULL, 0xF29D1052AAC77268ULL, 
            0x3C37D21C063A0967ULL, 0x113794F01BB1A5E9ULL, 0x299A3562FF9D36C4ULL, 0xCAF58A9B80320DE8ULL, 
            0xC5856CF2EDE62282ULL, 0x56C5CB58F5FEA92BULL, 0x234FA30A0C762B90ULL, 0x7DF738BEDDDF02C0ULL, 
            0x936E92A44ADD48E4ULL, 0x5D6D911970CA7D54ULL, 0x1613CB2CCE1044F5ULL, 0x1923416035C6ECD2ULL, 
            0x7C0E2DE10862002FULL, 0x7671736E552CEB6AULL, 0x12F284831AC0AFEEULL, 0x96DF4259F42499C8ULL
        },
        {
            0xA3424322DAC8F2A5ULL, 0xA331E1A399D7B6E7ULL, 0xDE1F98342AF173A5ULL, 0x75007C9FD4539EE8ULL, 
            0x2FAAFB99CE22A094ULL, 0xB59BA852270B1E24ULL, 0x48A80970ADC02862ULL, 0x852ACA8A5257F21DULL, 
            0x78CA69AE2B0F85E8ULL, 0x67E30AFA2F8B69CBULL, 0x6A924509F9C0BA59ULL, 0xF953141A62BC6646ULL, 
            0xD1368E94DDCCFBC2ULL, 0x1640DAF728E5F372ULL, 0x92DF834E76E4C680ULL, 0x4989DB6664C12E4BULL, 
            0x7A2A156D07A20F47ULL, 0x23087894783E059BULL, 0xF1873DBD3B786D83ULL, 0x87B9987EC380718CULL, 
            0xF91269B7F4FE65F5ULL, 0x9B272DC5077B134EULL, 0x95703B5EAD5D33BEULL, 0xEB01E77E92C4A502ULL, 
            0x2D74A552CB9D90DCULL, 0x93C382C127EDBE15ULL, 0x7D95AD552FBC49A2ULL, 0xF86375393EC7921AULL, 
            0x24D64B739EAC3A4EULL, 0x447FD5D02D6D6B5CULL, 0x26A176856763C65BULL, 0xAD5D8855280593E7ULL
        },
        {
            0x27F69407EE4F3410ULL, 0xA2A167783179C262ULL, 0xE810F3D42D16D85FULL, 0xF2B7B3ABC583D8DCULL, 
            0x31770F34F3D9517EULL, 0x46CF1566F4B0E86DULL, 0xB1226C397F268573ULL, 0xE0A41038D708EFE5ULL, 
            0x1AEA2654298EFA7FULL, 0x04DEC3987503C687ULL, 0x49E746F624978223ULL, 0x5326E5085D7CB997ULL, 
            0xAF96908BF6F5A148ULL, 0xA7A0253ECB02B41EULL, 0x3428982EBEB78BA4ULL, 0x8C8572C9509A6CEFULL, 
            0xF6B2C9FF24E1A8FCULL, 0xD64446B7123BE83BULL, 0x29CE40FCA758C194ULL, 0xD9B344DB300832A2ULL, 
            0xB904326D7EA95753ULL, 0x9F8CA5066B7BFF73ULL, 0xD342D5BEE322C3BDULL, 0x55B7028B604A4D0FULL, 
            0xA5DD869A762314F8ULL, 0x28D0654315CEC496ULL, 0x73A8D5907566E42FULL, 0x0C3C60B38A7684E8ULL, 
            0x7EB900ED4D2A9BE7ULL, 0x66B4B32776B7D14EULL, 0xCC5E6B0FC4E7BE00ULL, 0x72AAD19F18F74FAEULL
        },
        {
            0xF1B663117C8B2E81ULL, 0x79B3CBC7B5C7CADBULL, 0xC49F919244CFF9EBULL, 0xBE2AE0F70CD6C08DULL, 
            0xC9EB0CC3ED44CBD2ULL, 0x806855EFCCD44A13ULL, 0x81AEED6AF8A2B3CCULL, 0x1043FBF010ABC6E9ULL, 
            0x2E1761B40357E5A6ULL, 0x91540A051A84A71AULL, 0xCDFA4D56B83202AAULL, 0xF025680BA8E93223ULL, 
            0x409C6ABFB909683FULL, 0x333868EDBBA8FE7BULL, 0xE68EDE19EB3E222EULL, 0xE8AED709F740881BULL, 
            0x667A81FDBD081982ULL, 0x5A66DFE80FA86EB4ULL, 0xEC6176C76B13181CULL, 0xCBDC5BB73B13F51BULL, 
            0x72ADBA62B6C014DCULL, 0x34E504B02FAA9482ULL, 0xF0BE302EDC470F97ULL, 0x3C0D0949C316785AULL, 
            0xF8584DA169C4333FULL, 0xCAE9E226A4F5EFC5ULL, 0x1110E0C3F7D0BE82ULL, 0x1BEFEA13576C7CC7ULL, 
            0x8FA9DC2CB9A843EBULL, 0x21A914A71BB05590ULL, 0xB8D70817E0D4F7EFULL, 0xA81B393BB2D73B27ULL
        },
        {
            0x846D980C492B8C62ULL, 0xA4314AC891DD5367ULL, 0x26AD9FF6B799654EULL, 0xB920DAD1B20A0146ULL, 
            0x8B64870334211C93ULL, 0xF56FA07775A60BF9ULL, 0x008B23883EFA0E98ULL, 0x8D8D0D8CB6077D12ULL, 
            0x1DA86140705D1DC1ULL, 0xA850C31A6B770C5DULL, 0x8EC9BC448DFB5566ULL, 0x924E629E16EAF96FULL, 
            0xE90906D4DFFA9558ULL, 0x0A62BF6B5B290CABULL, 0x4CC6EE61B07AB3D8ULL, 0x189E49161D6B142CULL, 
            0x60243887C618A85AULL, 0xAC4A46747B8FB9C5ULL, 0xFC3F3E741960C0A0ULL, 0x781336DE5043FF3DULL, 
            0x782F7E76BFB12BEBULL, 0xCFBC73D921430860ULL, 0x9D48996E7CAEE0A1ULL, 0x77F0A41A126BD7C4ULL, 
            0x9764E74216DEDC22ULL, 0xB9173AE195953364ULL, 0x3E2F3600E3FA0169ULL, 0xDE3B4C60A7B42E24ULL, 
            0x7A6B142923BDEEE8ULL, 0x6FA2B9AB29A03786ULL, 0xDB389CB20ABC7265ULL, 0xAFCF5FE837205DCAULL
        },
        {
            0x8C207A37F35A3F2BULL, 0x6D04855B631EB2FCULL, 0xC9466CA5A3297AF5ULL, 0x9FC12CC6E44F984DULL, 
            0x1D50DDF070477EBEULL, 0xB00F56DE221DE3DBULL, 0x421C8AC5303CA9A2ULL, 0x0A921E15A04141E8ULL, 
            0xE3303001CFB7761DULL, 0x0F849A1E271958BBULL, 0x1EBA98F2451E41DAULL, 0x0A1FBF391D371728ULL, 
            0x0F8A150C65E563D7ULL, 0x1BCFE16457BB9786ULL, 0x76FAED85440641F2ULL, 0xD17212EA0A0C8D46ULL, 
            0xFB812A320F0414B3ULL, 0x1C5125E2BE393C10ULL, 0x24DA00EEED3AFCBDULL, 0x9F454255A0FD6942ULL, 
            0x8D15385D74CA2323ULL, 0xCBB5F2464742AE71ULL, 0xA2D4DC39E88FBD47ULL, 0x18EA45FAFE7CB878ULL, 
            0xB52C41F7EA2A63E6ULL, 0xA2663A18BE6ECC16ULL, 0xF2B8C331A4052041ULL, 0xBC3405AE759644CDULL, 
            0xC4A83A012AE72BD5ULL, 0x3FBB1C91F24AB067ULL, 0xB2B43E30C8B0B1C8ULL, 0xCD6A85CF36F5FE48ULL
        }
    },
    {
        {
            0xC5E8228E7FD6779FULL, 0xB02AE9E9C19C34D3ULL, 0x4FB95A727B5F2D08ULL, 0x644734D4698EE2EBULL, 
            0x9AE776EEC0E5FA6AULL, 0xF3DA17909E2481C4ULL, 0xB4BD7A35EC3797BAULL, 0x30872A18B54E0BF8ULL, 
            0xB1C4E7A30B55C719ULL, 0xEDC81061CCFC00ECULL, 0x2780BC316D79CC5AULL, 0xB96A9F829C937BC7ULL, 
            0xCB05317C6330FC92ULL, 0x82202B25D0D8E4D2ULL, 0xD418B1047A21336FULL, 0x0151C872B15A944EULL, 
            0xB4E04F6A4EA24B41ULL, 0x352B9D24A198A6C6ULL, 0xC9DACD0994E116C0ULL, 0x0A8301BD32E1C2B3ULL, 
            0x8726F073119919D5ULL, 0xD37EC167680F0B6BULL, 0xE0EA097B893E570BULL, 0x3392D7EC2FED7B78ULL, 
            0x2D5F23B673D01051ULL, 0x9CDF192458843FF4ULL, 0x3527B1FC97ACB1F1ULL, 0xEC9473C8CC635242ULL, 
            0xA2BF885CD1917375ULL, 0x6797E8B8DCA0910BULL, 0x6433FFE8A2599171ULL, 0xC2BC782F985AFDBCULL
        },
        {
            0xC584D2BA010902AEULL, 0x790F64587EE29604ULL, 0xC9F5103CB7E829DBULL, 0x45B6C84328E72320ULL, 
            0xC0BEA107F7A42490ULL, 0xF8010FAB55BAD958ULL, 0xFBFF6636865A6C0FULL, 0xA3E3D7C37AF8CFCAULL, 
            0x91752A8B1F2B5A59ULL, 0x193F00242236D052ULL, 0x7A87785D284A47CEULL, 0xEC20DE0FC2EA11D0ULL, 
            0x960671573C3C4536ULL, 0xC069FA9122EB5C7EULL, 0x2A2BF02536F89D9EULL, 0x9B4A259FEBD81499ULL, 
            0x33445DF3F66DC610ULL, 0x484209DC3EDA6AC5ULL, 0x3D6128F176977878ULL, 0xDB7A9BCC281E803BULL, 
            0xD06E78109F3384A4ULL, 0x97D7F2696FF034DAULL, 0x95258F7C31BE5AA8ULL, 0x36BD00C7FB118861ULL, 
            0x89EB1FE15396836AULL, 0xBBBE0F82AD6022DCULL, 0x051EA4765F3A8E90ULL, 0x7C3AA0553472CB70ULL, 
            0x00320405A209967FULL, 0xE275BF11CBC5AC9FULL, 0x2504492919A7F77EULL, 0x4E967C78F364FF4CULL
        },
        {
            0xBEB8AE1127CDF01AULL, 0xA8B0615FCBE849B6ULL, 0x1EDB7B8AB9AEBC3EULL, 0xE03B06BE96E4B789ULL, 
            0x01C5AF8F5057C95CULL, 0xD7DCEAC016716A7AULL, 0x8A05EB8EEAFC14F6ULL, 0x88468B86C285C42DULL, 
            0xF1D9A9A5955D608BULL, 0x058C309975B34334ULL, 0x335CD2EF2BBF5A49ULL, 0x45F7AC2C76B735ECULL, 
            0xBAEDE5B81B7E73C5ULL, 0xB409426FA8349F23ULL, 0xDB522E6C9BD514D4ULL, 0x4FF29E11556B2482ULL, 
            0xDE098A782312BF2CULL, 0x910122815125B1F0ULL, 0xB5D69DC5A8871632ULL, 0xC024A5730E41FBC3ULL, 
            0xF353BB408D9E9DDAULL, 0xB178909DF86DE6B3ULL, 0x0E84824AF3A2B17EULL, 0xA8BF48E183460E56ULL, 
            0xBAD660CEC06B7931ULL, 0x2264630D2745A3A3ULL, 0x9DE2D48C1ED7419EULL, 0x3FAA6FD284797F8BULL, 
            0x3E1357A345E40642ULL, 0xF25ECBEF46595051ULL, 0x9EBA4FB588AFFFA2ULL, 0xA3583CC1052E7690ULL
        },
        {
            0x9279C0AC0D5D9E09ULL, 0x759F612596BD5248ULL, 0x0B52099967111E13ULL, 0x4C6D2495C5A97917ULL, 
            0x6D7FC7C8A037A1BCULL, 0xBE46418E169BE181ULL, 0x6E8472A4AF769DA1ULL, 0x8CA1332AED7A1AB1ULL, 
            0x837443BE00AEE9DDULL, 0x3896DCB2E789578DULL, 0x4A287EB6144E9033ULL, 0x082CEE5B7AC09052ULL, 
            0xB8F61A7DCA02D696ULL, 0x03CCC5C64C1B3084ULL, 0xFC26402BA62C1089ULL, 0xE2BFDFC269915D18ULL, 
            0xFFF74CCD5B92A801ULL, 0x7370F3160C79E83FULL, 0x958EED5C06F9A00BULL, 0x2ADFF484DF1700C0ULL, 
            0x08F0DEBA8242BDFEULL, 0x8A12765784404AAEULL, 0x0C566C6FDD110170ULL, 0x4E643BFD955060BCULL, 
            0xBA48DD1AF75307C4ULL, 0xAA09EC5742FF8674ULL, 0x4A545A49B78B3BE4ULL, 0x10F0A6BC158340E4ULL, 
            0xADC5F5B1DD02BDABULL, 0x8764DA52D4A40568ULL, 0x3D34CC50E19A77A8ULL, 0x64F2D94D17835E1BULL
        },
        {
            0x2CB58A5FB47A5A66ULL, 0xCC108C3EB673BE93ULL, 0x134543608D806F95ULL, 0x6BEFDBED57B6F6A0ULL, 
            0x26F5B97DC742D1FCULL, 0x3F1684878E8E0A31ULL, 0xBDF7C132DD1C895FULL, 0xCA74E33EEED58377ULL, 
            0xC0628BD9764D56F6ULL, 0xFF65B8E8773C6EEFULL, 0x840065437952226AULL, 0xE5A8E3A6189F98CBULL, 
            0x543C8D2A698E3D61ULL, 0xA2098B7E5A471448ULL, 0x767ADBF8B7B7104BULL, 0xD46CC96C35C9AB23ULL, 
            0x6DF02058C7F694FFULL, 0xA187119782610F9CULL, 0xE09C7763A3A1905AULL, 0x6B4464E0A73D9C54ULL, 
            0x1A740BA206F255F0ULL, 0x841811787E8E7500ULL, 0x94DC3F5C4D5C2011ULL, 0x8A5A3C27A972EC6AULL, 
            0x917AE4BE082DA0F7ULL, 0xB4688F1696DF2DE2ULL, 0x6884BFEDADD67D12ULL, 0x83B0426256E3E91FULL, 
            0x7F4E22D64BCC39B8ULL, 0x5F753C463D5F192BULL, 0x23354ED034A199D3ULL, 0xE2C72BC3CE0C2501ULL
        },
        {
            0xE4FF6CC1488582C1ULL, 0x92FD17B603A2ECEEULL, 0xB3291977DD07C230ULL, 0xDE7240A64E36C9A8ULL, 
            0xC90BC4AADC6F315EULL, 0xF12E69C9B576B2F8ULL, 0x004426458292ACCEULL, 0x0DCAE04BA2F88551ULL, 
            0x47D2D9A54D94C52DULL, 0x0F903A0524F2240BULL, 0xBCAA90AEF50889DAULL, 0xF4298AEDDBDEF5C7ULL, 
            0x56226D3461B88355ULL, 0x6350B066F750F20AULL, 0xEAF7507B036A00D6ULL, 0x9734EF4D177028A0ULL, 
            0xA621321F28C86D0FULL, 0x7202013F47186730ULL, 0x7921EC5E73D375D2ULL, 0xEA396DC445A1E4ABULL, 
            0xA26677720B9ABF68ULL, 0x31367256BA804836ULL, 0xAB5F21D40DE43572ULL, 0x59209BC2AA295E02ULL, 
            0x54375EB662DA6719ULL, 0x1AF8B4B7AE61E35DULL, 0xE19010496E9D781DULL, 0x070EFB96D49EC610ULL, 
            0x6031A74D2760DDEFULL, 0xE44F90512E4CC02AULL, 0x724A1D2F4963E1CCULL, 0x1BE06C3C0EA61604ULL
        }
    },
    {
        {
            0xE6A858602C05F9E1ULL, 0xBF92BE882B7F3E1AULL, 0x330BD65CF7CC8784ULL, 0x0BE40076D7478C88ULL, 
            0x9A44B13E58E0F812ULL, 0x967DD3B65E62E2C9ULL, 0xCEB47E3EA80C7680ULL, 0xF34EB7B61489F99EULL, 
            0x4C50BC301D74BBEFULL, 0xB9B137EFCFEC8274ULL, 0x1CC18BDC11770F83ULL, 0xFE256BC898A5FA19ULL, 
            0x1D250E796F9BAC79ULL, 0x2BF0136D6A0273A3ULL, 0x80C6C0120F16CFA9ULL, 0xB136CFC650BEB372ULL, 
            0x1C83AEF372D5CE73ULL, 0x785B8C8DF31098EAULL, 0x66A43C66AB2FD416ULL, 0xD8974C70D19DE730ULL, 
            0xFE94F70756664E4DULL, 0x5AFB541CD81855D4ULL, 0x398C61EBE17BE765ULL, 0x6310F094BE3E8857ULL, 
            0x5B32DF043B54B4D5ULL, 0x2E106A83B99BC2DEULL, 0x3736D194ED7C3441ULL, 0x43149D608BDE9DFFULL, 
            0x1A3F2FB44DC475BFULL, 0xBA44CA7AB3421EE8ULL, 0x16B8ED4BA5A9A5BEULL, 0x4288B6315FD7265CULL
        },
        {
            0x0DD381A1927B62D0ULL, 0xCE96902112163221ULL, 0xFA224945C234B3F2ULL, 0x3BE561691FB1E7DAULL, 
            0xE6C0BC534B6BAEE0ULL, 0x9FA33A72039F94E3ULL, 0x102AE0424C49035DULL, 0xD00B1CF312950B4EULL, 
            0x78040912C952072EULL, 0xAE33D77F598F035BULL, 0x4BDECD8EB599ECE6ULL, 0x8377840E601372FBULL, 
            0x78D132CCE15BEEDEULL, 0xE2D80C766E649229ULL, 0xA81329B13BC730AFULL, 0x77B2DA3984A6068FULL, 
            0x8D7C56083243495DULL, 0xE045E1CF989B8415ULL, 0x9F14E7513847F55FULL, 0xEDA829C69D6E5665ULL, 
            0x8E3CF3086AC231F6ULL, 0x53429F8177D9C11FULL, 0xF0D5EA4B8BAD50DEULL, 0xAA55959719389FF4ULL, 
            0xE07A5A0626505AE4ULL, 0x31A44B8FFCE46346ULL, 0xA8815EFEA2ACB2BEULL, 0xE25C649CBBFC17F8ULL, 
            0x348BB59C6F7BC194ULL, 0x0F85815E59EF2448ULL, 0xF57A50FB87F39F7FULL, 0xB32B4880046B4506ULL
        },
        {
            0x7FD653557CDCE59FULL, 0x9C3A4C85E03B725BULL, 0x4D3E27C227B0FAA9ULL, 0x17D380A5A93318FFULL, 
            0x4E3DDCB982765440ULL, 0x4771C63A335E54EFULL, 0x4EF80507193B1361ULL, 0xB3A8C37DA8EEF5AEULL, 
            0x02B864D260EAD928ULL, 0xED837AB0994F8FCCULL, 0x42A66ED27B711DD0ULL, 0x766A2B5BE9AAD824ULL, 
            0xE64B01DF561CD289ULL, 0x533A833827D57A7EULL, 0x39FBFD5146503C18ULL, 0x018208B9639CC023ULL, 
            0xF33512D8D1081887ULL, 0xCAD134048A62AC30ULL, 0x1C9966BA31A7593DULL, 0x71CD881B8108E6BCULL, 
            0x914DB61957D7A750ULL, 0xF8672D62590F3F1AULL, 0xFE7D849B4EE5FA9CULL, 0x7DD7EBB07AA4769CULL, 
            0x360F576B839B315AULL, 0x08E5F73796F85CC2ULL, 0xD5AB2D05133CF896ULL, 0xDE3E2D89A25D9160ULL, 
            0xF32AC4555DD13E53ULL, 0xEDD6023EA00FEBC7ULL, 0x926F7732906A18CAULL, 0x1B40CE5CC76E66F9ULL
        },
        {
            0xB47F72BF5E049604ULL, 0x7E074AADA2F48180ULL, 0xF8AF1FBD277E53DCULL, 0x45F1ED0B3EC58C83ULL, 
            0xE53A17CC899EC523ULL, 0xFDBC70BD0475D459ULL, 0xC9A85B121D2B6AABULL, 0x8C55EDCE920BC58FULL, 
            0xFD5DCEFD8D47ADD8ULL, 0x176A096262A47FF1ULL, 0xB17B75B4F2CA68C0ULL, 0xDDFCBF5F97FF6B85ULL, 
            0x69A1C40FD2CC99A4ULL, 0x4DB32C456F2006B5ULL, 0xB6DD5ECE4F32AD93ULL, 0xA4457C0C2C389A91ULL, 
            0xE05292FB257E2E8DULL, 0x0791DBED80ED7025ULL, 0x6FA178EEB1050956ULL, 0xBF1A622F37630DCEULL, 
            0xF5716989DA454CEBULL, 0x3028C52E89390257ULL, 0x152753FF6AAF1294ULL, 0x83E32372E0C113E5ULL, 
            0xD94B9B9838D1C379ULL, 0x2287A3DFEE922E04ULL, 0x20A18509864788C8ULL, 0xA59051D129F2BDB2ULL, 
            0xFFC6052F42E38A6FULL, 0x0CC8579D9C1CA04DULL, 0xC179057FB9E60F1CULL, 0x4D505227A50BEA09ULL
        },
        {
            0xE9BD98E694C6660AULL, 0x106C9F391285997DULL, 0x5881372F29121C7DULL, 0x3130F9B82595A4E8ULL, 
            0xB1ECA7890FDD5438ULL, 0x713ABDBF6C8B1137ULL, 0xFC32BC4F03E6A827ULL, 0xAD1A163F24E14933ULL, 
            0x5A90793E2D9A95F0ULL, 0x665C75ACD2693EF4ULL, 0x7899150E6FCABC85ULL, 0xDA6C184D6C901CFBULL, 
            0xF156270D3CE8416AULL, 0x3F22CD0C5B57A762ULL, 0xA52C850853CAE3D3ULL, 0xCFC26E24D67FBD03ULL, 
            0x16BD70086033AE06ULL, 0xD5E271B75D66CF97ULL, 0x3E71BEA17F9E0405ULL, 0x3067D356BBBB8BDAULL, 
            0x6DD56C9C9C8F7FFFULL, 0x8F0348B9AFAEE12FULL, 0xF5F1B77FE0F3227BULL, 0x0472849C76BEABC2ULL, 
            0x3DCC57FBE141D2FBULL, 0xD78B0CAD90AB1CD1ULL, 0x06540C3D9277EC78ULL, 0xEC740F9FF9DFA351ULL, 
            0x0CA115BC813D41D4ULL, 0x33DB7BAEFF5D3B33ULL, 0x15B17C5C88D89D3AULL, 0x4C8368E5978C27F9ULL
        },
        {
            0x174CE3AA58FA4763ULL, 0x347B17344E53319CULL, 0x8AE93652C4B7B09FULL, 0xE5AD92403FEB8D3DULL, 
            0x6E9F42AB2A7A05B6ULL, 0x3933EFFA53C20E52ULL, 0x5B515C7D0CB4CB29ULL, 0x2C5A2DEB9A7492FFULL, 
            0xAE026C00F17C925AULL, 0x1CB52D0D0DBC0FF1ULL, 0x021647B7727EB944ULL, 0xE95B34092F70A511ULL, 
            0x6B721D76B673EA63ULL, 0xF3AD950B6E2BC1FBULL, 0x3A7F5E370B027F35ULL, 0x1B2A38585B3235CBULL, 
            0xB9DDDDF770F1D92DULL, 0xA194B4E6C2AECE5BULL, 0x787AAA1E10551CA8ULL, 0x24738565E1CE1270ULL, 
            0xFCC4CC7003DD1EB8ULL, 0xFAFE798E2BB48E8DULL, 0xB0E8517650118F3BULL, 0x3BA9D267ACF8B02EULL, 
            0x13190988A2FC0CE1ULL, 0xFAF3738015976508ULL, 0x85DE6742931B0377ULL, 0xB701C3A82C351223ULL, 
            0x73B124F44EA14DF0ULL, 0xEB363D02D9730124ULL, 0x84C324BD1B4B9467ULL, 0x3F977B170D300DC3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseBConstants = {
    0xBE492D5BAF39126EULL,
    0x432FFC6E9CF7E7BEULL,
    0x3713CF1E44C0CC6EULL,
    0xBE492D5BAF39126EULL,
    0x432FFC6E9CF7E7BEULL,
    0x3713CF1E44C0CC6EULL,
    0x996B6ED7478FED3CULL,
    0x55CD71A77A05A089ULL,
    0xEA,
    0xAE,
    0x60,
    0xE9,
    0xDE,
    0xB9,
    0x4B,
    0x47
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseCSalts = {
    {
        {
            0xCBEB2D05011850F1ULL, 0x45522B71405B4F9CULL, 0xDDD0FE2292B59415ULL, 0xC8611AE309631473ULL, 
            0xF428CCEE4DDF41C8ULL, 0x197CDB3DAA0BB4DBULL, 0xFBB8538B692D8970ULL, 0x5E6A1466AAA1AB03ULL, 
            0xB74EC7BB64AFB0A8ULL, 0xAFE2B860F37D12F2ULL, 0x2C035A52B65CD730ULL, 0x840B65A1A7A1A2D4ULL, 
            0xC00F8CDE619B2596ULL, 0xF8CD92E808FF2440ULL, 0x433E55FCBB9C9F03ULL, 0x1B53C465E245ACFBULL, 
            0x2895540AD2CED0FDULL, 0x9C77456BBB5410ECULL, 0xE85416B9FA3EFBA1ULL, 0xEED65748E85AC070ULL, 
            0xC340A53E43AF28E1ULL, 0x447BE6344AE1D952ULL, 0x85AFC91D49AC1DF2ULL, 0xD8B46D831F73E8A8ULL, 
            0xF3DF25992A624B7BULL, 0xE680272E29C1F31BULL, 0xA25FC18F5C275777ULL, 0x2CECC82513E3A56BULL, 
            0xE585CA085F8366CDULL, 0x11D07DAFCA7D28ACULL, 0x05A5E61728C72896ULL, 0x774011A5460FCFAFULL
        },
        {
            0xB180BADAEBC409DFULL, 0x0987A33E3E37A5AAULL, 0xBB5DE87058A717C1ULL, 0x90FC8F48FE642880ULL, 
            0x614DAC239C462E7DULL, 0x5889DE3D47649766ULL, 0xC30D9E4C33F04930ULL, 0x486D9AED6864A626ULL, 
            0x00529C639694C4D2ULL, 0x74333F5B93961D97ULL, 0x188C5754FA48C13FULL, 0x1E1E9E70BB0E4773ULL, 
            0x843BB863E34E912DULL, 0x10299EF96C3118C6ULL, 0xA766FDFB76CA3842ULL, 0x317AD616978B6B48ULL, 
            0xE94560904DE3AA2AULL, 0xC5F0FBABAF43B5E0ULL, 0x9AE7A3C0D3265CE5ULL, 0x9E99ACA1E360F97BULL, 
            0xE9A8D4577F8D36C7ULL, 0x37ABF058FEDBE3E1ULL, 0x300980726070DCA1ULL, 0x903B3D863034D83FULL, 
            0x04DF20815C8691BDULL, 0xBE529AED98986731ULL, 0x488DAE072F235436ULL, 0xC11228C280367C73ULL, 
            0x8F4C68C698482D88ULL, 0x992698E48939B401ULL, 0x196798157755EDA6ULL, 0xFC17745C8AE9ACB4ULL
        },
        {
            0x53E08202FEB9E5D0ULL, 0x1FBBA055971E2D61ULL, 0x9CFD9B79769710DDULL, 0xE6A31E0FB4B9CC7EULL, 
            0xDCBCD14752EE504CULL, 0xA775BDD994FA4D5BULL, 0x0429BB75A584C94AULL, 0x5C43EF784312B593ULL, 
            0xEB759BE5BE5622AEULL, 0x40353375D0025EBBULL, 0xDC1CE85DA75DB702ULL, 0x8D80759FD28C4B93ULL, 
            0x5A1B22160A886E54ULL, 0x8F6A944C451D9471ULL, 0x838720DC4BE56151ULL, 0x34CB399725F42293ULL, 
            0x3E0FF5054AE7B90DULL, 0xC896B15ED9D9F9C0ULL, 0xB652C16D109DB791ULL, 0xC9BB79CE636E5781ULL, 
            0x4CD7AC75609EDC6DULL, 0x4EAF79814E0524C0ULL, 0xB0C52AB8E1D45A74ULL, 0x8C79E88D614D7D43ULL, 
            0xDC7D90CEC34E960EULL, 0x85A4EDC863C41964ULL, 0x71E234ECA27AC741ULL, 0xE7C50FBA9F0023B4ULL, 
            0x53EBDB5DD7821256ULL, 0x671C531865C6C07FULL, 0xDEE98A5D5A6017B8ULL, 0x0311334D526D2775ULL
        },
        {
            0x785B150C0AE0A3DBULL, 0xA5CBC9400773786AULL, 0x34A1EE0326C673BBULL, 0xFE3C66C964684CC4ULL, 
            0x036C39BD59A23456ULL, 0x408B98FD9B1404E1ULL, 0x8F56EF8C4DEC5919ULL, 0x882475C1F6B714EAULL, 
            0xEEDCE99283D38BDEULL, 0x4865795E4D0236FAULL, 0x960633F2E47F90C3ULL, 0xE81123896CAB04A9ULL, 
            0x43655CF092E7BF13ULL, 0x4AA856B8713CD18AULL, 0x457F755B3FA2910BULL, 0x3E48CEC34913ED13ULL, 
            0xCDF3965384CE0413ULL, 0x3BDDF81BEA4A6CE4ULL, 0x1BB32C682AC1670AULL, 0x82C16DA83C2FF742ULL, 
            0x0AFE76EBB76B518CULL, 0x1767A91240CEEE58ULL, 0xBFED4194F4E22B44ULL, 0xC6F5C5DEB6EAE8CBULL, 
            0x4991E23D6C3B96B0ULL, 0x8CC10BB54555E01AULL, 0xF07F54B5A0183002ULL, 0xA9E79E6CDB10AE56ULL, 
            0x194EBE2BFE119F4FULL, 0xFB9312DA7C454EFDULL, 0x43A1881811382417ULL, 0x05F31AD95C6210EEULL
        },
        {
            0x6B733ECBFFFBA5D4ULL, 0xB84214587F60230CULL, 0xD84FB808C68A87AAULL, 0xE6C601AA4DA9C410ULL, 
            0x2AF6A1BD684D7E4AULL, 0xEC11797674F6FEF6ULL, 0xBB76C821368DBF87ULL, 0xF429628618EDEF88ULL, 
            0x725F6999454A323CULL, 0x5276FAFF3F491484ULL, 0x8C9ED5F78A518163ULL, 0xB537302F24E58229ULL, 
            0x75D8C37DBCF6BB1BULL, 0x15E71537C3377629ULL, 0xC7C1F14CA4EA85DBULL, 0xADBA6AD6B26188C5ULL, 
            0x5BA9C4892BF9E81CULL, 0x8D526364DE9D68A1ULL, 0xC318146805867F20ULL, 0xD3F8123582FCCDA5ULL, 
            0x21C06C816E7E7AEBULL, 0x1D8BCEFDA1990EF7ULL, 0x828F355915A2584EULL, 0x9BFD15C79E2313CFULL, 
            0x7B73618545C1230FULL, 0x1784307F477A05E5ULL, 0xA8910511DCAD54DBULL, 0x6A22587B0ADEF6E0ULL, 
            0xCE98FFF47D360914ULL, 0xDE126D1E2D0B9DFCULL, 0x5B249D049253DB31ULL, 0xCDD7C9D75BB4D4C2ULL
        },
        {
            0x5C6AA767F9FD2059ULL, 0xC04736A9AF0E2D4BULL, 0xCF1909AC1B4AC36FULL, 0xCB4FB535AAC39C15ULL, 
            0x6866AA9187AD7544ULL, 0x98DE8F58B89115F6ULL, 0xE2FB94239EA65976ULL, 0xA5E81BC873A26432ULL, 
            0x89EEF0FA5975F461ULL, 0x28D4B3216545C854ULL, 0x21D326B2FC21E00CULL, 0x48AC989F15CF4FE6ULL, 
            0xDC90927E299FE3F4ULL, 0x99F023B2AA96904CULL, 0x7124075F2053A6FFULL, 0x216E931F83A8978AULL, 
            0x0F346E60F5283B7BULL, 0x5EE8A5FAD547406CULL, 0xC602F1688DFC2E16ULL, 0xD8F3EC3D2E0574E3ULL, 
            0xA4E2A18522BDF169ULL, 0xDBDBB7B116B71486ULL, 0x5461866233A6439AULL, 0xA7DC36D09C6FD2ADULL, 
            0x585D28A92A443F09ULL, 0xB67584D8189F3A44ULL, 0x228817DBED1BEAA4ULL, 0xE935FABC2062AE1FULL, 
            0x82EE50C6F1EAE364ULL, 0xEBFA926A5A2ED534ULL, 0x97E6BA5F4DEB5C3BULL, 0x028C1F3316366D73ULL
        }
    },
    {
        {
            0xDB2E7403505CA4D9ULL, 0x3D87642820E76408ULL, 0xC5C43BE296C3169EULL, 0x3CE303C597CD0CD2ULL, 
            0x273EDEA630D3E78CULL, 0x647C98690026B658ULL, 0x95790C05454529B3ULL, 0xA402E288432741B3ULL, 
            0xB8C5950EF3821376ULL, 0xF56C30160AFE626AULL, 0x9344F3DF31E2C62FULL, 0x641D4EF5C3D1A67EULL, 
            0x50465D8274AC54A4ULL, 0xD0A1257996CF9DF3ULL, 0xA67FAB89D1BC5766ULL, 0x58BFDEEF4FBF8EC6ULL, 
            0x46667B0D4B56DCAFULL, 0xB2C42EEE98EBE980ULL, 0x0FDF14531EA720C1ULL, 0xE0264C4F874A77ADULL, 
            0x601EC476DF6B91EAULL, 0x8DA488B2ACF2326CULL, 0xF9534C91A1A2F688ULL, 0x95D9F5844282D477ULL, 
            0x38C65DF535104894ULL, 0xA08613044D1B675DULL, 0x0FBBDC81514C206BULL, 0x953E16EEE94A6918ULL, 
            0xFE3E07D1FA294BA1ULL, 0xFD0813D41F374605ULL, 0xD0C72ECE8E9D21DBULL, 0x934B6C0D658729B0ULL
        },
        {
            0x9352760607A0C929ULL, 0xAB5D557868C38F77ULL, 0xCFD41A070A24F46FULL, 0x5A07C185A3E8CE31ULL, 
            0xE42BA268E7F19413ULL, 0xA4745F26FCE52C2DULL, 0x889C5D5051E530D4ULL, 0x4B52A0B005C0E874ULL, 
            0xE58280C4789BB481ULL, 0x9ED36A1F1DADF29FULL, 0x0363C6A1C838719AULL, 0x3C2F5B5C5567F284ULL, 
            0xB9E32FE8EB69E800ULL, 0xA2CAA6146A7355B2ULL, 0x5FBD3D118468C2B9ULL, 0x989A46F8BFD97EE0ULL, 
            0x3D3D48C934C4F6EBULL, 0xF4E1DB919E2509BBULL, 0xB182F1AB1F59DF0EULL, 0x7CF810E22E1C20C8ULL, 
            0xD518DD7E0E0A339DULL, 0xA42FE82AF96B655CULL, 0xC3F60EA1330DEB37ULL, 0x0ECB0B0587434313ULL, 
            0x6A93D81C66A5DC44ULL, 0x03D3BB20E6F58D0CULL, 0x17AD16A2435DFA5CULL, 0x61525C8A40C4CF21ULL, 
            0x418858679C1B21BCULL, 0xE31EE93B753C43C0ULL, 0xAB0261194442EEE4ULL, 0x73A4238FE4339CA3ULL
        },
        {
            0x10E048D436C705BDULL, 0xA2FABC7288C2A374ULL, 0xE906C8738C489501ULL, 0xBC0B884EA11048E4ULL, 
            0x789D70DE72DE95CBULL, 0xC8ED1BACEAFA7140ULL, 0x7D2D6728D413F2A5ULL, 0x6B93A3F5D465B30EULL, 
            0x65ECC939056E06C5ULL, 0xCA179A2EBFF06FDFULL, 0xF69FBE5AC6E34119ULL, 0x03E4D4576843C46CULL, 
            0x8201845C6D4DFA4BULL, 0x2EFFF900DE596648ULL, 0x956637BBAA6D026DULL, 0x5F5286928F8C3C02ULL, 
            0xDEE185B3F445311CULL, 0x7F6057A99224317AULL, 0x32A1F63FD7438CA6ULL, 0xE1350B2E6F13A086ULL, 
            0x7422A624FBD5DFA4ULL, 0x2FC7EA83D83B47EEULL, 0xDBE46222C489AD03ULL, 0x8FA15C9BC3495190ULL, 
            0xDFCEA490D7DBD20AULL, 0x8E1878A099FC9287ULL, 0xBD28D869227E7704ULL, 0x5EF20FA817F54C11ULL, 
            0xAA1A5C6C352C0296ULL, 0xFB5C6020FE6B3EC5ULL, 0x8AD1E18C7DC849F9ULL, 0x2761AB85E7791F71ULL
        },
        {
            0x9942852EFB9E9A00ULL, 0x4C00F8D0941F7DD6ULL, 0xA66C9A1188554D4EULL, 0xC4EAE8FC8C59984DULL, 
            0x2F3202F627A51E9DULL, 0x536502418EA956E8ULL, 0xA8D81C9EF6A75FDDULL, 0x869914A5BF96F6B1ULL, 
            0x3FB135C075535F83ULL, 0x0F63FF8C0A8F0BD5ULL, 0x2F6AC5BE1667D12CULL, 0x4B7C84C944B498F9ULL, 
            0xCF86C42390706E20ULL, 0x5BAEB4EA06528E75ULL, 0xC7D87932E5980D12ULL, 0xBD29B22A85D51958ULL, 
            0xD24025F495127A38ULL, 0xD0087616142AC624ULL, 0xEC1B5ED42653324FULL, 0x5D2EA6A6E0532E90ULL, 
            0xC009C299B25D03C0ULL, 0x28734842D94292B8ULL, 0x4DF9B223523C7F70ULL, 0xB8D9AD6BEFDE0B5EULL, 
            0x8AB4FB6CE68F6228ULL, 0x3631AA8A3562D31AULL, 0x8C890EDFC66AE046ULL, 0x9C849A98C30CB8E2ULL, 
            0x3AEA29AA2DE3434DULL, 0xE0C7E0F2DB9FF1EEULL, 0xA60C05F767A7B1F5ULL, 0xBD663B048923DB2EULL
        },
        {
            0x1173DA35B4A37466ULL, 0xF3F90D1F8032DE97ULL, 0xB329561DB08F0E27ULL, 0x0BA15829097AE8E9ULL, 
            0x8439DD8015E10767ULL, 0xF1401656AD7FBA4BULL, 0x2F53D44F22DF628CULL, 0xCE15D3C4B8FA727BULL, 
            0x70E52B3A309EFC1AULL, 0xF28A1B71DD94A142ULL, 0x33568716C51608F0ULL, 0xA378BE19A39A4BCEULL, 
            0xD17C94A44FD8E450ULL, 0xCBF972650ACD262AULL, 0xE8B37474A1BBF7D0ULL, 0x892A5250EB8F36EBULL, 
            0xD4F70216514FC06EULL, 0xB6483982EFE6D777ULL, 0xDD5C8A3811A7D714ULL, 0x2F931D3E6A89152DULL, 
            0x6B0AA6DB13D12502ULL, 0x50FA9318F5DAC9D4ULL, 0x62EC16B2984A5735ULL, 0x6D5AD9D01EEFC92CULL, 
            0x01A4CFA44E552D15ULL, 0x3CC5E53BDF88EFEDULL, 0x6583A601090FF9D6ULL, 0x13CA5033670D15E9ULL, 
            0x5E55F2581AA89DDBULL, 0x6020EF12CE1AAFCAULL, 0x92AFAB3EFDDBBC50ULL, 0x34EF6C2DEEE8407BULL
        },
        {
            0xAF796F336B3E8D0CULL, 0x411B91FD7EF62026ULL, 0xC92B224D2F6C14DEULL, 0x2392FA1624C845B7ULL, 
            0x766AF794694263C4ULL, 0x000B0682B6E7D794ULL, 0x0BC15B77585D779CULL, 0xD8E11882CB796679ULL, 
            0x10600D0528C96876ULL, 0xCD8582B7FB7465CEULL, 0x47A935E8F15AA034ULL, 0x5C44D175B7EA76BBULL, 
            0x055C5F5814C53BF3ULL, 0x75753C4AEF9F4B26ULL, 0x514C581A1EAB9519ULL, 0xA09D44CEEBFB30E1ULL, 
            0xCA811FA9920F2606ULL, 0xB7F2F1172C38CBF4ULL, 0x0E7EBF097ABCF83AULL, 0xFA8E9299FB5DDF21ULL, 
            0xFA59DC2EE5E03282ULL, 0x50EAC1150EFDDD7BULL, 0xBA351B270DD1F4AAULL, 0xC5AEBCFA6F2F2A6BULL, 
            0x2FAB095BBECC26F8ULL, 0x0456BC1413FD6D99ULL, 0xCFDB79823FB9FFB5ULL, 0x05325CE03D173B78ULL, 
            0xF52B087D7C04E9CFULL, 0x13CCC26D4A69FD14ULL, 0x43FA6F5CB89C7FDAULL, 0x5D40B48BC60BDD5FULL
        }
    },
    {
        {
            0x033BF50A192815A0ULL, 0xEC492D5CC8EA6CDDULL, 0x1F0BEE75371C87A4ULL, 0x20C504F07950EF1BULL, 
            0xE07758BB151FAF87ULL, 0x538407FAFEC52A44ULL, 0x8453082F9DF8D28FULL, 0xE5AB45AFB4FCB289ULL, 
            0x2EBD641C2F49786EULL, 0x70009DF880865E75ULL, 0xFAA2C8280CC3B867ULL, 0x21B687AEA34749B1ULL, 
            0x1A276BA0490EDE0EULL, 0xB8052274369EA59FULL, 0x38F86AD4C87B4CB7ULL, 0x10DD97019AAA3BA1ULL, 
            0xD56D155F8E07BB5CULL, 0xAB33451A96D68BA1ULL, 0x39470194D90242E0ULL, 0x666355897EB3B9CDULL, 
            0xC19357907BE28700ULL, 0xAB0B5D6BE30D57A7ULL, 0xED5B77EC80DF56B2ULL, 0x4D3B0B9BE86AA6C7ULL, 
            0x139BCF2C1444DD23ULL, 0x76FE0537EF55D19FULL, 0x23501A19B365A381ULL, 0xB3D5BA350BAAB36FULL, 
            0xF69E1F51044E7AC5ULL, 0x5E259AF251748B2DULL, 0xFDECD133B6589D21ULL, 0x0591A21AC20398CAULL
        },
        {
            0x55E9383AC3F6B532ULL, 0x1C4D6902E746B563ULL, 0x70C1E99ADCA08D00ULL, 0x9F06772DE45CD79AULL, 
            0x17DFAF27B931672AULL, 0x033444452BE24C8AULL, 0x8B243AD99BA0A05BULL, 0x832D8F96D3EB3416ULL, 
            0xCAFA40A3627A5CADULL, 0xD4886D5C7883BD65ULL, 0xF39548CC567EDDFEULL, 0xA9E1264C6F81E02EULL, 
            0x7459B135E1F02B50ULL, 0x6C4A2F115B0C29BBULL, 0x9457415624E1B70CULL, 0x8173A8D4E5A7032FULL, 
            0xE1FB1E39D27EE7C3ULL, 0xE5F0C4FDE58FB410ULL, 0xEE7C82FCD4A1BE02ULL, 0x745A2687E3FC978DULL, 
            0xE757C44E890C1B44ULL, 0x22F8F34060A73804ULL, 0x444A3ED5865762F0ULL, 0x6332ED2DA6C47968ULL, 
            0xE9BE9CC91E6C302FULL, 0x59A9C0150E718AFDULL, 0x65BB7DBDC98A603CULL, 0xAB2FC578C6FE4166ULL, 
            0x7230B39290C0C7EEULL, 0xD3904C413CDF7330ULL, 0xEA40F2018C62B303ULL, 0x9C338ACB3549FBACULL
        },
        {
            0xC5E9A4989DB75D06ULL, 0x73F5EBA642480671ULL, 0x905C3665F3CFD68EULL, 0x097A271A03470AE8ULL, 
            0xA085162A5A5C11B7ULL, 0x346380279AE9C36CULL, 0x084F5B70E079BF40ULL, 0x305421F2A8DD5790ULL, 
            0xEC70BDA387DA8E3EULL, 0x38CD9B36D2517235ULL, 0xB01FC7F262C8567FULL, 0xB669306E8D3232E9ULL, 
            0xC0ED9FF84D1F5040ULL, 0x42F1672739CFD2FCULL, 0xD121AEFC5CA19E56ULL, 0x6F63ECFAC372080EULL, 
            0xF26C59FA911F5250ULL, 0xC339E9865C2F5230ULL, 0x01AA84261249E674ULL, 0x41D47808ADB1206FULL, 
            0xABEE8F7F88D6AD5DULL, 0x967748DF3EF0F1DAULL, 0x47697070DFA35DF8ULL, 0x705821F3B6ABAE55ULL, 
            0x5D7A2AC2D391A62BULL, 0x87523F82232E1314ULL, 0x7BF62CFE22A68B9EULL, 0xD5F59890AA7539E8ULL, 
            0x24E65B9F8B5FCF6AULL, 0xDA9D494E631DBD2BULL, 0x3E82A128FE2FCDF9ULL, 0xCF1272D5D68E4B33ULL
        },
        {
            0xAC9F00FE8E36A9A8ULL, 0x2299098AB7C028A3ULL, 0xC1885792FCCDB36BULL, 0x74630863A09A06D3ULL, 
            0xC7DD942C56FA907EULL, 0x15E91AC883ECF62EULL, 0x58D5E1E2C5D782D5ULL, 0x93045B05346E8962ULL, 
            0x43C3E9B86A83B8A1ULL, 0xB62142202B015E20ULL, 0x285771C8DD6B963CULL, 0xD841F332D95D8FF5ULL, 
            0x69EBCB5811158F49ULL, 0x520CBEB39050FF5BULL, 0x9480027BF1FA9CEBULL, 0xB079B81E22BB1013ULL, 
            0x5D0BFC1FC4B67B3EULL, 0x926FC1E87261817BULL, 0x59E3461C27FA4E74ULL, 0xFC648BB37A81E997ULL, 
            0x72830479DB373F6CULL, 0xC198484D7F8DBBAAULL, 0xCDE9F186B8AC4513ULL, 0x4D7051B5E3BAA6EEULL, 
            0x9EB6F33E7E9F1AFDULL, 0xC8A526738071B983ULL, 0x14F5A1C65E490DBBULL, 0xC659C1D7AEC75FF9ULL, 
            0x70B0B73FED540AA7ULL, 0xA9FD64CFBD508355ULL, 0x6618D93801AC3D6AULL, 0x24FD5B6FED84C6D0ULL
        },
        {
            0x146AEF7AE5C2ABB0ULL, 0xF9455B198AADAB42ULL, 0xBFE1EEA308F92BA4ULL, 0x698E7B7B8DC111A5ULL, 
            0x68CA9AC1CF018D94ULL, 0x2CBA2A42DC595AFDULL, 0x7B7AA83E35CEA339ULL, 0x98B3645B403562FCULL, 
            0xCDDA4A818FCBF589ULL, 0xA37FAEF0977DDFE2ULL, 0x1398B6D9CA3F5F16ULL, 0x4FBB3FC17A7DE0E4ULL, 
            0x588DE7541D635884ULL, 0xEC8BBE4DAD680704ULL, 0x8765AEA66B4FB2ADULL, 0xA5784D8214DE0090ULL, 
            0xB98E92F00BE5451EULL, 0x9C79389A5EFF3C2FULL, 0x4AAEF56AC34F98CDULL, 0x69B7721F98841ECAULL, 
            0x9A234EE217CE0EB5ULL, 0x81A46883DBAED40FULL, 0xD5C38FAE8B74D03CULL, 0x931D3F9D2F6E6143ULL, 
            0x2875878D08449409ULL, 0x1B2974F4D7050DDAULL, 0x4DED21628983DFAAULL, 0x6D3372BD1A25566CULL, 
            0x525DA96FC21F10B5ULL, 0xD7A8F4AF1DD27EE3ULL, 0x4EBE379FCAE489A1ULL, 0x808948B35A4413EAULL
        },
        {
            0xC3A721B8067579F6ULL, 0xA42F958A48D7EBFAULL, 0xC0283363EED4518DULL, 0x97B1D56B3FCC17C3ULL, 
            0x78D23FADB6413F68ULL, 0x299A3577C86C99D7ULL, 0x419089C9951EDEBAULL, 0x71D197CCEA3C0605ULL, 
            0x43FE0BB43D518E64ULL, 0x766329A74F348D1CULL, 0xCDF2C8625A94016DULL, 0xCD31F3AA92FD85E0ULL, 
            0x10A45DE0F6F581A5ULL, 0x20DC42919264CBBDULL, 0xE4443F7B63E62147ULL, 0xA01805EBB55DCDE4ULL, 
            0x5F5889B92E9CCC50ULL, 0x3F8681FC924500D7ULL, 0x5F6CA2B1BE643276ULL, 0x325A5EFD2EFCD5E9ULL, 
            0x9EED6D19493AAC14ULL, 0x46742637EAF49534ULL, 0xDBCF5F07105A59C6ULL, 0x30455755E3F20D20ULL, 
            0x4B8E168E9776223EULL, 0x02E57FB19ACCFAB2ULL, 0x016B674D5B9DB011ULL, 0x93D21CF91578C9ABULL, 
            0x5A911D9C0DFE78D9ULL, 0xFDCE2A126427366AULL, 0xE4627A5518CBF05AULL, 0xCB449967D1460FDAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseCConstants = {
    0x265EE998A4211822ULL,
    0xC812E385328E0222ULL,
    0x9F108EC40FCB1411ULL,
    0x265EE998A4211822ULL,
    0xC812E385328E0222ULL,
    0x9F108EC40FCB1411ULL,
    0xEBCC55CD9A08034EULL,
    0x77F4E1E5D7231BCAULL,
    0x52,
    0xE8,
    0x4A,
    0x67,
    0x5A,
    0x63,
    0xFD,
    0x10
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseDSalts = {
    {
        {
            0x41DDF440CA60FE6EULL, 0x8C100D6D830D7353ULL, 0x56A2D6A0F8434967ULL, 0x8B8FBBF576A300B5ULL, 
            0xC238DC5AE3BF8BE3ULL, 0x6C28289FCF10E49DULL, 0x8EC5F32D75E8E5C3ULL, 0x4B3DCE51B31E4E69ULL, 
            0xA1F117A69A709E0DULL, 0x306484E7BC87B739ULL, 0x9CC9345D66D78254ULL, 0x964A0877D75B00BBULL, 
            0x5649888DA05D9C09ULL, 0x05639BE223502946ULL, 0x975262966ED0D23FULL, 0x99B00ABDC3F094E9ULL, 
            0xAE071CDDCF7944BEULL, 0x243769584CB47CDAULL, 0x207B896193C0347CULL, 0xE4D720F289ADEF87ULL, 
            0x44C8C2A22D04C132ULL, 0xBFD0898B9EA876C0ULL, 0x5F3F13F0C2B068FCULL, 0x47D7033AF5D1D2FDULL, 
            0x34777C7BD2D6B963ULL, 0xF13C2C3079E05623ULL, 0x1767A61E47549024ULL, 0xEAC49A2D31FCDE45ULL, 
            0xA16D8C072A26ABD7ULL, 0x9E082BF46D6223B7ULL, 0xA3D51CDAA05A2860ULL, 0x1E08DB4D10CA843CULL
        },
        {
            0xAE12FD243AD6BE36ULL, 0x654D76F8EF32B6F0ULL, 0x183E45DAE2ACBB47ULL, 0x81594C4204A5A93FULL, 
            0xE2148598B7B4611BULL, 0x1F1CE2BED8223E50ULL, 0xE0C16883F8C27A92ULL, 0x8A0AF94DE18F76D7ULL, 
            0x14C4B6E066B3856DULL, 0x0EB74410249B9304ULL, 0x631A64B791E55207ULL, 0xC532CE0A6D2A31BBULL, 
            0x634083A52D7AFAD2ULL, 0xB29017557B76D1A4ULL, 0xCB9AD6EAEC26FC7FULL, 0xE8AD91D55BB1BB22ULL, 
            0x99CEC99AA9925D0AULL, 0x91DCB0B4EF744620ULL, 0x25FC3F54A6356C88ULL, 0x100E6F3AA63176AFULL, 
            0xDBDFD170EA331600ULL, 0xB6DB0F70E7C984E2ULL, 0x37683FD1D5562201ULL, 0x5E52055BB27420E9ULL, 
            0x19DFE342C3456785ULL, 0x16688DB89D134C9CULL, 0x8451A939E5CF9B82ULL, 0x4CD616505DE1D546ULL, 
            0xFC6264605C272EB5ULL, 0xA7D973ED3D7EC640ULL, 0x53F74C0AEFD20075ULL, 0x3C8D0A57F5FBDEFDULL
        },
        {
            0xCCD7D232DE9A28C1ULL, 0x03DB1C16CAB5F028ULL, 0x28C066726FB9CF46ULL, 0x8CF7C2E2A8BDEAD2ULL, 
            0x9A5711840BD71A8AULL, 0xD8C3BB2F0CBDD739ULL, 0xEC0362E8FF94D6BEULL, 0x595BA61DD4F67005ULL, 
            0x64AF333C27513AB1ULL, 0xA1ADAEE444994D94ULL, 0xE4CB96070AE1CC60ULL, 0x7FA82D3965086D96ULL, 
            0x3F1CEC6A38426864ULL, 0x4FEAC450F0F17C69ULL, 0x0D5A1022C80136ECULL, 0xE08D52E1DEB16A7DULL, 
            0xF0C07F6B1499B814ULL, 0x62820D8788288466ULL, 0x0D2EA312F7577DA6ULL, 0x66667604C6BFE2A2ULL, 
            0xDF76CB8B033E85EBULL, 0x8F3A878EF788E5DFULL, 0x5B430DA2BFC7BF74ULL, 0xC0F27AE3D4935BB2ULL, 
            0xB5A4D4EABBC134AEULL, 0x09621380D26A2E54ULL, 0x0987D5C594BA189CULL, 0xE4D564D85421C5E0ULL, 
            0xC9F7F17596364698ULL, 0xBF3298C749F7E657ULL, 0x303334FFE8905F29ULL, 0x89FDB0C840DC7A56ULL
        },
        {
            0xF5B81B5709657B12ULL, 0xEE2E44E32377BF01ULL, 0x472544F7EA19B2A2ULL, 0x0E1652B1E9A70BE5ULL, 
            0xA62181124DC221A2ULL, 0x1A6D0DE7FBA5F85FULL, 0x2462F94898F92EBAULL, 0x1E5A0EB9BC725DEDULL, 
            0x4398411237A87FAFULL, 0xB723771F5ADA8DBDULL, 0xE2A912E25B4B7929ULL, 0xAB3A97A300CDB86CULL, 
            0xB0100DFDB9DE84BBULL, 0xCF1CDD385642326EULL, 0x49D92FAABD50BC2AULL, 0x17D3FCC55765B649ULL, 
            0x10A544705CE230B2ULL, 0x3CA354E75E5A867CULL, 0x0DC27FA164A11FCFULL, 0x1C9C28E1B29B7EBDULL, 
            0xAAB8B595262DAD2DULL, 0x6C3769BC85BEC4C4ULL, 0xBB42DF818776FA9CULL, 0x5EEBB7C382C83418ULL, 
            0x5FE07CDA025C04A8ULL, 0x78407283797C34C0ULL, 0x9CAE899226D2F766ULL, 0x9AB77736F8956ABCULL, 
            0xE916D814521D0A07ULL, 0x1E6C588BAA65B076ULL, 0xA4330CB53E53CA6CULL, 0xBB9C8575FB629B89ULL
        },
        {
            0x50CA70EF60A049E5ULL, 0x5A84179AE6C09155ULL, 0x767E3757EB4F5CDAULL, 0xC64F2800327430CCULL, 
            0x79142FACCD6AE6D3ULL, 0x11398D767780BCE6ULL, 0x9306E5D27EE2FD8BULL, 0xE4541AD6F6271793ULL, 
            0x083470C37B4572FEULL, 0x80CD13CABB47ED3CULL, 0xF6525FBAC1771E59ULL, 0xB2BB7951D5B71A72ULL, 
            0x66BB6129425FEF71ULL, 0xB2AB0056F2FCF1AFULL, 0x5C978C99CB84D0C5ULL, 0xBC02CF6C1FF94664ULL, 
            0x3E2D1CCA8CD08254ULL, 0xF217E6FA98A0FD82ULL, 0xB46F9F2C61C13FAAULL, 0x5A1EC0CDE0EED7E1ULL, 
            0xD2BBBCCAE3906111ULL, 0x1793EE96E875DF2BULL, 0x5727DF0BCAA01FD9ULL, 0xF15AD2BD5FF94BCCULL, 
            0xDABB67F90038FCE5ULL, 0x0C9C4F5969BA4827ULL, 0x5AA2AA6D67477D2AULL, 0x0EB1406AA9C46588ULL, 
            0xE64A0688E51A4285ULL, 0x2A7E700F8B7A3714ULL, 0x795074DB54A94E87ULL, 0x329E9EF35419CA69ULL
        },
        {
            0x3D892BA13C4BE560ULL, 0xB2483C376FD02F4DULL, 0x7C43C549B0A9BAEAULL, 0xFF8FAE64E38312BEULL, 
            0x38074FC7717891E6ULL, 0xE68F41ACBCCB8B2FULL, 0xD09178AE065F21B7ULL, 0x5D7C1E0CEB1D8838ULL, 
            0x7175CE306384D007ULL, 0x59EDC55AE9191B1BULL, 0xFF40050C86F7B464ULL, 0x440E58AA3D2086A0ULL, 
            0xA49B416444262C3DULL, 0xF3EF54AA51795936ULL, 0x455D5E5CC95AAC75ULL, 0x325250D741AC56A2ULL, 
            0x4C037F0F938ECEBBULL, 0x6304EA4250FB1393ULL, 0xEF177EA0DD1D286DULL, 0x2BF6786A338083C5ULL, 
            0xE0F3E8D8122BEDC4ULL, 0xFBD4CEBC1B204D4EULL, 0x3F49D39B56002F0AULL, 0x3C9148C8DB9DBFEAULL, 
            0x036FF011D4ADA8A5ULL, 0xD043338EF60B9FE7ULL, 0xD3827010255A8382ULL, 0xFCE95B771ACBC9C1ULL, 
            0x92760BE59999478CULL, 0xE1FE8317BD2A8EEFULL, 0xE7F6F5CB6E69A057ULL, 0x0EBFEDDE6C2CF372ULL
        }
    },
    {
        {
            0x142250FD18B620D7ULL, 0x7E674433C2F1984EULL, 0xEE212224F7010156ULL, 0x316CA1931ED040ECULL, 
            0xE84B14ACC79DED28ULL, 0xEA8A60A539175338ULL, 0x1DF96A1D36F39493ULL, 0xE58BEE4DCA158F37ULL, 
            0xBC7AEDBCF83980B4ULL, 0x0091C4F751281222ULL, 0xB39C21B35CAE1C3CULL, 0x0AD28CA713B45AF8ULL, 
            0x2FA99479306FF4D7ULL, 0x1EB2BA84B918135FULL, 0x548BF574A6368E9CULL, 0xBD422F03763B5FD3ULL, 
            0x35A51397BB799836ULL, 0x389CC91ABA3132CFULL, 0x8A0D966C9201E18EULL, 0x7DA94F2864683357ULL, 
            0x0DD50E44E9BAA553ULL, 0x2C33D298537F9A4CULL, 0xC5EBF20793D25AC0ULL, 0xF6F4B2C349534A79ULL, 
            0xAEFEC13C9AB4CD97ULL, 0x6956B3D613A8B705ULL, 0xC72F4E4F1C4CF64AULL, 0x0DB6BDDB6E90F08EULL, 
            0xA3192642D601130EULL, 0x61FAF17A20BBB495ULL, 0x224B8920E1C58E73ULL, 0x00823E39C8662CF5ULL
        },
        {
            0x006562DE970F86D2ULL, 0x977327805E74E879ULL, 0xFA2B361043371FD0ULL, 0xD8339B6A3C71DAC1ULL, 
            0xC8D6E7A7E4B0604AULL, 0x31290DD32D9B2950ULL, 0x4A747EBBD518A267ULL, 0xB8B6EDC9A51F9BC5ULL, 
            0x6BC235EDDA244964ULL, 0xB62A99122B8096D5ULL, 0x7357F78997A97F74ULL, 0x68FE7C838784CF32ULL, 
            0xCBC1C43A779481EDULL, 0x4A6DF925A3A96684ULL, 0x3798A17A7CE50D87ULL, 0x17AD30338E9EED20ULL, 
            0x064917AAF990F003ULL, 0x83F86BD5A685DB86ULL, 0x315D9ED70041A0EFULL, 0x5B6A3D92A173DAE6ULL, 
            0x9BA3697E5DD351F0ULL, 0xF57B94FE07CEB3E7ULL, 0xF150FDB711E4B6F5ULL, 0xE8599933347955D4ULL, 
            0x6EBA5CAA93A4EF95ULL, 0xFE6B8F31EBDB228CULL, 0x9FAC6696F8EDA5ADULL, 0x35629C482D4887C8ULL, 
            0x4173225EA58C74A5ULL, 0xC5E2F6B150FF0FAEULL, 0xCEFDBED5D5030E16ULL, 0x11B1CAFFB4F1A530ULL
        },
        {
            0xB3956A214ACEEF76ULL, 0x54BD386AF6DF12F5ULL, 0x3E8FE4ADD72090C0ULL, 0xB09FB02C0806C249ULL, 
            0xCE416F5BCE2745FCULL, 0x3FDF02181AA6E52BULL, 0x551D7D46B840FC3EULL, 0xFD0A73F8D050EB67ULL, 
            0x4C0D3D5083988A6CULL, 0xC7A7521123FD5216ULL, 0x2B7CA5C1C626D21FULL, 0x6CC8F4DFA16374A5ULL, 
            0x758605C4E5A70467ULL, 0xA7163E72A9776AD8ULL, 0x8C811B1ED9E4EB58ULL, 0xDD55F00767D14252ULL, 
            0xF8973AE3C93DACD0ULL, 0xCDADD2D6E668BC83ULL, 0xA820A08C72FD4E4DULL, 0xCB00F89B2A0C373AULL, 
            0x5CD340162FCC8456ULL, 0x788D7165849CC44EULL, 0x6355ED1FA0E10DE4ULL, 0xA534205571E0F0C3ULL, 
            0x4C9FA66F75F13032ULL, 0x74AFF1324823854EULL, 0xD993FC7632FDD3FEULL, 0x50A47A8ED6DA2049ULL, 
            0x109990C06989D127ULL, 0x99CA94B0B59E0E92ULL, 0x8D91D7E11BC02334ULL, 0x4E69B62A5E093347ULL
        },
        {
            0x65E73A9896A44432ULL, 0xCAF64B0C8B404B5DULL, 0xFF679EBEA093E036ULL, 0x0A1ED757BA8CE6ACULL, 
            0x2D10EDB2B3B3A17CULL, 0x79874B8FFC4ECAF7ULL, 0xFBF52754D350B48CULL, 0x4E627756D4B35007ULL, 
            0xE6B3D61C3A91722CULL, 0x1FD97E73F00485D2ULL, 0x84D2C6BDAE61C1D1ULL, 0xDD7C3AB9783C9A2CULL, 
            0xE23FFBE8B728DAF2ULL, 0x9216993B1418915FULL, 0x282CD72604D966E4ULL, 0xC2B7BBFA939D6DFEULL, 
            0xC44F70D987177623ULL, 0x295CECED77407F5DULL, 0x7E807BAD16F9EBFEULL, 0x97F6ECD184B97776ULL, 
            0xC2315D7E44BA4667ULL, 0xAA3A3F01BE9B9B51ULL, 0x5BDC84DA2DD905E5ULL, 0x7DDB5569F71B201BULL, 
            0xD55DF36C531201DEULL, 0x914BE32F6AE33ED8ULL, 0x7202A09DA04995E7ULL, 0xFEDBADB3311AC2D5ULL, 
            0x48FCCB69C3D2448BULL, 0xF9E152B9CEAFC37EULL, 0x82965416F6FF9933ULL, 0x2349F15482B81959ULL
        },
        {
            0xD6C6B0316565539FULL, 0x754E84D578BD3012ULL, 0xF98DA5737418EBE8ULL, 0xF53F5B2484F40251ULL, 
            0xB856C67A7B702A07ULL, 0x2D199469A2B92B5FULL, 0x47B20E8B374A1089ULL, 0x828A4AF473CDD23EULL, 
            0x12200E1D71524E9FULL, 0x2DDB940624136EB1ULL, 0x9B85E7455317D600ULL, 0xE9EAB11A30A175A3ULL, 
            0xF742087414FCD6F4ULL, 0x5B3731D7FAEBDDB1ULL, 0x1616C35CA9432F7AULL, 0xD21DC8744F21E815ULL, 
            0xCC0EF0436BBB274AULL, 0x1C6CED7255CB3820ULL, 0xB5974B6D0495296AULL, 0x12932D92EC9A834EULL, 
            0x35F184F6E936A718ULL, 0xF8F3FAC9B7B5D4C1ULL, 0xDD3CEE16D8F3D390ULL, 0x42F04A9C6C9D5DCDULL, 
            0x04215114B9483380ULL, 0xAF84E39CB3B72D9AULL, 0x40BB1DA455ABE3F2ULL, 0x6FBD2A000533DB72ULL, 
            0xF0EF107A44111C42ULL, 0xC611EDB1173C4A32ULL, 0x49D9FB6E5228E949ULL, 0xD55EE77CFFE0DE62ULL
        },
        {
            0x2DCEB7A1990E4683ULL, 0x9F1DD8348E52251BULL, 0x60808D5921A436EAULL, 0x42E9E3E5491FEA95ULL, 
            0x0D582C1AC470626AULL, 0x295066F5AFFEEC56ULL, 0x082654BFB9F1E249ULL, 0x8EE5534B728D6280ULL, 
            0x2C5AA6875E20EF41ULL, 0xB03AF3B0C97FE86EULL, 0xF8EEA83FEBE655A3ULL, 0x5B67D0CBA5DEFFEDULL, 
            0xCBC9EF3CAA02B419ULL, 0xC6128EE2BA5F9A27ULL, 0x21EFFA18FFB7F3EEULL, 0xD883F96A479A6C21ULL, 
            0x4E27A4CDDB181D83ULL, 0xBCC4A1F7EBA8E9FBULL, 0xE93557DE26D309DAULL, 0x0642A68E822768DBULL, 
            0x40EA96F22D27DC71ULL, 0x584F90A82E127006ULL, 0x5A35C4E676ABAB49ULL, 0x49B53D174DC86907ULL, 
            0x308850194AA709F3ULL, 0xB711DA2FAFBBE4FAULL, 0xE03CFB4434200382ULL, 0x1193FC8A0A697A2BULL, 
            0xDA3436D0F0C30808ULL, 0x5DA71818D1D31EEEULL, 0x5E75674271D1A171ULL, 0x11FFCBA2537E2125ULL
        }
    },
    {
        {
            0xEB427F9889D229CEULL, 0xA9D7E80C0C0679CEULL, 0x61BCC42DDA688291ULL, 0xD84DCB26CD28C624ULL, 
            0x87F3C689EA3CF03EULL, 0x979FA0A9748BB1A3ULL, 0x1F1FF06C2734C9C0ULL, 0xFAEC2ED5819E7D2EULL, 
            0x49525B93191BE707ULL, 0x15E06F9035B52E70ULL, 0x1A24470BEE4F41F2ULL, 0xA9D2B3027EB3C1EDULL, 
            0x6FF1CC2F4721DD16ULL, 0xA2E5C83C15F876DEULL, 0x2A9447AF90C1BCDFULL, 0xFAC8B2E61FB69DBFULL, 
            0x33C7A570DF87D71CULL, 0xA2260464AE0CA453ULL, 0xE4050BD6E8754E74ULL, 0x5A04BE0F9CD498B7ULL, 
            0xBD6E75959BE59BE1ULL, 0x0B23BDE72989C0E6ULL, 0x44494FBF155F7887ULL, 0x80C494B8DB52D6A7ULL, 
            0x491FA94E41FC6715ULL, 0x32AC92502B1BE017ULL, 0x494FA3CDD715F7BBULL, 0x3340E682A971033CULL, 
            0xF43D56E8CC48F6DFULL, 0xE09F0723EFE73122ULL, 0xE340DF40D640C6E7ULL, 0x5DA37B80279D1E5CULL
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
        },
        {
            0xBFE90CFF777780DAULL, 0xCA22FB6717612B10ULL, 0x164768862B3A1C83ULL, 0x413C3FAF1C35A257ULL, 
            0xB87FEF431A0B3358ULL, 0x5467B0197F883E2FULL, 0xA8C0F15DA3D73EBCULL, 0x03402EEAC914C562ULL, 
            0x07007880FE60F998ULL, 0xBBF0EBC50321AFBAULL, 0x7373154CBF521F4AULL, 0x2B1A09EFBE625237ULL, 
            0x307A1E84AC9B5BDCULL, 0x6AB8B40E80789974ULL, 0x79415517E769D8EBULL, 0x23E5FD6DEFDBEBF1ULL, 
            0x3D460A8587440CBEULL, 0x2CB6659EC834C962ULL, 0x3535EF63576AC7EFULL, 0x37C6357BE93EAC05ULL, 
            0x03344D88B885E0D8ULL, 0xCDF84B90EBA9E6A0ULL, 0xDCC0190C9DC2564DULL, 0x5AF1E46CD011318EULL, 
            0x7E759FCBB4F5E9FBULL, 0x1A51E682644D572DULL, 0xA1DC59264376BE01ULL, 0x4C9D98DF4B82BBBFULL, 
            0x0DC21CD4A94ADBEEULL, 0xAAE22A84BDE741A5ULL, 0x43A04312FC557C90ULL, 0x97D51C370E1C1DB9ULL
        },
        {
            0xCE89A38F4CF94F86ULL, 0x35654CF2FEF2C95DULL, 0x47DD503ACAA34919ULL, 0xD80E07E4617BFD5FULL, 
            0x4910294BE0982849ULL, 0x0600D23686011C60ULL, 0x52A897571D9D1364ULL, 0x6F23A40A6DEC1AC6ULL, 
            0x8A1A6742711D36E1ULL, 0xC6CC72642C59E2E4ULL, 0x22C1E60956539838ULL, 0x15655C58DF768732ULL, 
            0x15CF318884951FDEULL, 0xFAD9D9723E8BC8BAULL, 0xF7BC2682A4853A13ULL, 0x18AAF7A737F22F12ULL, 
            0x13AE0BBFD135ED34ULL, 0xA06A1FEAA4421985ULL, 0x9DA546AA8B1242C2ULL, 0x870814B54C6B8AE9ULL, 
            0x1CC1764512B97199ULL, 0x1A7A5E7ADA1D69DCULL, 0x6AFB37854638BDF7ULL, 0xC17CEFA96400FEEDULL, 
            0xDDF80D28FA910B62ULL, 0x07ED5192945583F1ULL, 0x326224815C9F8D21ULL, 0x59398666D6E48ED4ULL, 
            0x04658504CAC6D5E8ULL, 0xD575E985DCD6924EULL, 0x5D7B733D23A5522BULL, 0x8DF3CA0BDAAE0D2AULL
        },
        {
            0x5053B1917A249991ULL, 0x92F1ADEAD5E7A729ULL, 0xC50DD38779047376ULL, 0x3F9CC8CEFB80E279ULL, 
            0xB0081A8D3ED5780DULL, 0x6174F7F23F850978ULL, 0xBA69BA3FF2874C48ULL, 0x8383F6FAF81C6755ULL, 
            0xC98923DE17AFEB4FULL, 0xFDA762429E6CC5DAULL, 0xFEC10D2B2F2173DDULL, 0xF5968EE592F65F2CULL, 
            0x6AF07B2A0286A4F3ULL, 0x19164009AF1CD6FFULL, 0x799CE8D57FD93076ULL, 0xCD5FE395693FE343ULL, 
            0xE2E17F8CC57827C5ULL, 0x7071FBED28EABACBULL, 0xFFD1C7759D059622ULL, 0x6E3A23A9A753A04EULL, 
            0xBA5AC19AF13F568DULL, 0x8BED815F43BA3825ULL, 0xEA0E38A5DB3C0438ULL, 0x6DBC404E9F8DAB58ULL, 
            0x610CCF2630FB611AULL, 0x99987AB51E8C3F53ULL, 0x51857D0960F980E7ULL, 0x5383AC814EA796B1ULL, 
            0x39BF4FCDB8810BD8ULL, 0x0B99C888F43942FCULL, 0xAACCC2216AAC6921ULL, 0x261AEC801D51F9A5ULL
        },
        {
            0x8B70732E73098126ULL, 0x1AF077BE0D85093EULL, 0xC2F9DD30E3D8A17FULL, 0x5C14717C1FC6997DULL, 
            0x8CD457E3AF367383ULL, 0x9EA56128A0953CF7ULL, 0x01BD2A1C11B8AA5EULL, 0xF98815A30121AE59ULL, 
            0x556D9C7AB932C8F5ULL, 0x3136FD9366E70A74ULL, 0xF54043DCF2CF7B59ULL, 0xA2F9CF99792B0D47ULL, 
            0xEE1F703EABF13B10ULL, 0x8A98FB3E1F515BE4ULL, 0x74330DE0CE8FB4C1ULL, 0x77D11AA3180A3FD5ULL, 
            0x772E2CCE7817FFEDULL, 0xA10565A27CAA5FC7ULL, 0x8C046B92819DD6A2ULL, 0xC9D9AF7E77895AA8ULL, 
            0xAE33958AEDD40AB9ULL, 0x46BF34055072F956ULL, 0xA3367B7E3E630B80ULL, 0x8E271AACFC32DAF2ULL, 
            0x2F4209E38B3366D1ULL, 0x378C8A88847FDA17ULL, 0x36B39F31A003956BULL, 0x88F2089FA443665AULL, 
            0xA04FBFD2285DB717ULL, 0x2BF4E258D0E683C1ULL, 0xB65C3207E1CA0255ULL, 0x9C57F271A205D104ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseDConstants = {
    0x0AFCA77E96486F92ULL,
    0x9378EC35B3C45AC6ULL,
    0x45752A1480D5D210ULL,
    0x0AFCA77E96486F92ULL,
    0x9378EC35B3C45AC6ULL,
    0x45752A1480D5D210ULL,
    0x1C6DE32F347DD6D2ULL,
    0xBC76BF8E2A952DA5ULL,
    0x3A,
    0xE6,
    0x22,
    0x86,
    0x37,
    0x0E,
    0xBF,
    0x57
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseESalts = {
    {
        {
            0x1142AC92C0809EA3ULL, 0xAE8BB683E4EB052BULL, 0x319E398079215278ULL, 0xC9BAFCD9D9AF99B3ULL, 
            0x8F404ACBFC0DF2DBULL, 0x54EB912C103FF1D7ULL, 0x9FEBB18B56E12568ULL, 0xFAF3C730255981FAULL, 
            0xD95901D14ED68584ULL, 0xAD44CDFC03616DF4ULL, 0xF4BEDA2EB6943705ULL, 0xBC7F7822C56C1DD9ULL, 
            0xEADDA55152635C3BULL, 0x85596C7354AC3092ULL, 0x9E83D095BE72C169ULL, 0xDE39CE2F6E58AFCAULL, 
            0x0193F0C3DEC074C1ULL, 0x4A1C0396D23085F6ULL, 0x0CAFB8135F8943BEULL, 0x7E1F84D6C7E109CDULL, 
            0x539569792596172EULL, 0xDAD81987F3C3EACFULL, 0xEA62E93D000A0162ULL, 0xEDBE693BB6FEDCF5ULL, 
            0x3FCF17D5F35E4F78ULL, 0x970A9801208637FCULL, 0xFA83A376D4D2CE98ULL, 0x3FBC25AE134ECF94ULL, 
            0xDC55A1B7EE362DD6ULL, 0x40605A8DC7FA8236ULL, 0x598F3F0450F37499ULL, 0x45A96CA9C49E14D3ULL
        },
        {
            0x37F404BD8BFA7D15ULL, 0xFC1FC130C2CAFD48ULL, 0xB5184EC7A89D83D0ULL, 0xD4AFC6D9387F4284ULL, 
            0x5AA99355EED6EEDAULL, 0x23DB9AD251FC284BULL, 0xEFA253BAA919B05FULL, 0x9B8EB99D29F0B3D9ULL, 
            0xC199F7B1760A41BFULL, 0x4999E1A1DA3595F6ULL, 0x6466E1CAA4C65B75ULL, 0xFAB80D4D004921B3ULL, 
            0xB974D22E2A388797ULL, 0x997FA1225E846CF5ULL, 0x01549F013664E0CEULL, 0x43ED0CC26D199EE9ULL, 
            0x39C4CAE9CC204AEAULL, 0x03B6482698D94FB8ULL, 0x643CB650F569D1C8ULL, 0xD75C3B99CF60DF9CULL, 
            0x1DE1C41A8C06C39BULL, 0xBD93107560E93F1CULL, 0x8B3874114135CCA3ULL, 0x2586CCAE444BBF78ULL, 
            0xD1A47BEC93A829F2ULL, 0x3560069B2AB0FC93ULL, 0xE5D5CBC1BFEE4CDBULL, 0x0A086FDE1C209946ULL, 
            0x3911574773DDC77FULL, 0xB0CD46CE5D18151FULL, 0xE587E7667E0A7BB3ULL, 0x09768DBA8B427008ULL
        },
        {
            0x666D8770E8861E3DULL, 0xD020C1F27A028D0AULL, 0x9B8BB88DABC5F934ULL, 0xCCB4E1856AFEF5DEULL, 
            0x691D5993CAC1BD72ULL, 0xAA2F633DDF737041ULL, 0x0E1757F411943CBFULL, 0xECB74E2433847D51ULL, 
            0x01A9CD3DA1E37C62ULL, 0x452B3EBAACE77572ULL, 0x92EB88383199AE75ULL, 0xD7B466FCEF126DC5ULL, 
            0xE5E32F2BE246DBBDULL, 0xD705CAF4BC0B3F2AULL, 0x8F636F2C697A9B6DULL, 0x985A17E1D3638EEEULL, 
            0xD9A8933C0146DAE3ULL, 0xCFA4114834479AAAULL, 0x34357B06DE475DE8ULL, 0x6803C7FB90BAB853ULL, 
            0x1C1FEF7FE5224E6EULL, 0xD5AA05B6AEBEF8DFULL, 0x6C71709472F663EEULL, 0xCCE4BAD1D84B48CDULL, 
            0xEDC171817DCC06DCULL, 0x3E6C9D3A4C89EF82ULL, 0x3A5BF6CFA0DAE4B4ULL, 0xCB0316B990757811ULL, 
            0x7A88C8DFEACEAFD6ULL, 0xE0F64D059918EE18ULL, 0x383612EEA34C5B08ULL, 0xBA39750D281C26A0ULL
        },
        {
            0x8EF2B87F1FECF459ULL, 0xAC7FB802DBB5BEB8ULL, 0xC524211FEA38D103ULL, 0x429363BC2CA1442EULL, 
            0x9789D88E899A95D3ULL, 0xB7D247A2E633C330ULL, 0xE393CB054B6211B0ULL, 0xFDB7EC7F177695EAULL, 
            0xE6EF9AC45C31C96CULL, 0xC8EDBAA464867549ULL, 0xB877F1B5BC2A5FF8ULL, 0x558614AFC692C99AULL, 
            0x3C831CE675460231ULL, 0x6BCE9D4B5A186F37ULL, 0x8F92D6D98A2A2D1CULL, 0x674E83F07F8F4244ULL, 
            0xA015C828707424F3ULL, 0x366931BFC81C8A82ULL, 0x8DB1B057FDB593F6ULL, 0xB2179C314BA60AEAULL, 
            0x6EF1A73CECA43C90ULL, 0xD92AC85AB321A794ULL, 0x5707D36963915013ULL, 0xB5F7B4F944769291ULL, 
            0x94D0CDC4A932AD0CULL, 0xA4E535F08A2131C4ULL, 0xFB4539AF1516EA36ULL, 0xF8E6AA818427BF1FULL, 
            0x09D02AE54E814128ULL, 0x63DFD5934EE6313EULL, 0xF0BDE875DF0F5616ULL, 0x673051AAAAD375D4ULL
        },
        {
            0x745585C8DA6BAC40ULL, 0x26563D2EE05892E4ULL, 0x7F7EE3F177E6A816ULL, 0x3809EFB00B112254ULL, 
            0xB12E751F75948BBCULL, 0xF99612A053CE450FULL, 0x7D44F8AFCD8BF69BULL, 0x4DE818269B80022EULL, 
            0xB0054F7F3EBEDE9DULL, 0xDD466A96E15123E7ULL, 0x7F355189D59156CFULL, 0x6BF21545BD843585ULL, 
            0x8C392B48CF9B1C2CULL, 0xD9152A363C12E31EULL, 0x0DA9C556AE912E30ULL, 0x1475AC3E5CC23536ULL, 
            0xCF8BD36EBA5D7372ULL, 0x0B718A360B77A9D0ULL, 0x9ECA81B52BD98808ULL, 0x138288742877C6F0ULL, 
            0xFD9A3BE54873ED91ULL, 0x22923749CDF6559EULL, 0x850624DE0090A525ULL, 0x1B85DDC6634E2664ULL, 
            0xE82FCA9E71051480ULL, 0xFF3918A2A9D2B10AULL, 0x6E78C4F275EAEA20ULL, 0x0AC6391EFBC2C03BULL, 
            0xFEFD4AD28038252DULL, 0x29E3104AD187F6E4ULL, 0xD1FEB6939F350CFDULL, 0x0532365683644003ULL
        },
        {
            0x6A2178A92F9DC112ULL, 0xF256ED8A2B39B822ULL, 0x4C1062CC7B5BBB3DULL, 0xE995CD47B3C39E2FULL, 
            0xF5F53B9AC8C87B47ULL, 0xB09933A3FFEFDE3AULL, 0xEEFF79E55797B404ULL, 0xD6446B626DBBF582ULL, 
            0xF92245F546B4A9D2ULL, 0x3ADB6DB4FD4F3CA3ULL, 0xA27B9D27A5806DF2ULL, 0xF7FBD6E732A024F8ULL, 
            0x38BA4922540A27DCULL, 0x1F39F4735350AD30ULL, 0x87E51FC7CFD9A693ULL, 0xB96D3EBFF1E0E802ULL, 
            0x84F5B120C222D541ULL, 0xF50D07123F0A5485ULL, 0x74A45408AA34CCA6ULL, 0x518AE270E2CDF6B2ULL, 
            0x345768CECB6D3B85ULL, 0xBB3CBEA934FCB726ULL, 0x0ABD9739B33D0E29ULL, 0xCBF58029F65CC203ULL, 
            0x50DFC8BCCAF60CC5ULL, 0x0F11B46D127FE51BULL, 0x57BD0AD8E2FB4C33ULL, 0x30C3474523446996ULL, 
            0x57FD7132F35D9AA5ULL, 0x057C5110A74DD0A8ULL, 0xF844239CB2B083B6ULL, 0xD15AE8EEF87BA410ULL
        }
    },
    {
        {
            0x1D7F4D3409DA13D9ULL, 0x72559B3F4D7D0C8AULL, 0x546B393218E2F623ULL, 0xD2215416DBA74E5DULL, 
            0xEC287519DD65C4A7ULL, 0x573C3DC39C4B6D5CULL, 0x3DFC9BB2B1428A50ULL, 0x2DF84386F2733FE7ULL, 
            0x353559F09AA889D5ULL, 0x9048765DBC98F5D4ULL, 0x068B4D1B716C4380ULL, 0xA55CBDF784BF8BE6ULL, 
            0x3BB1E51CA6732BFFULL, 0x01FC4C38FFEE667DULL, 0x2A69220B0B59A224ULL, 0x29605D1FC0EB6E59ULL, 
            0xECEC8EF4D1C3E4AAULL, 0x8E0FA017BD5F0498ULL, 0x921762D14B981F9EULL, 0x64ADED199E5F75F2ULL, 
            0x6587E066B14A008AULL, 0x74503220D05B3EBDULL, 0x9EF0606ACB0BB14BULL, 0xA229F9C4F6B46EA2ULL, 
            0xC96FDA20ACEDED3DULL, 0xD1878041CFCAB6FDULL, 0x018494050581A732ULL, 0xCB539B66E263B107ULL, 
            0x933B2C4CC9C46CD1ULL, 0xB1A650D8C1A0332BULL, 0xB7EB9879F6E9829BULL, 0xC47B8190FBF65E4EULL
        },
        {
            0x7F4A48A7B0874F32ULL, 0x3CF3E46FCDAA1140ULL, 0x3DA1F457E50957D2ULL, 0x259807D3333E027DULL, 
            0xDF9D02D640320CDCULL, 0x69BE4051B432F3C0ULL, 0x864875500F7D2C92ULL, 0x7A36DFACC148B4D2ULL, 
            0x73398C096EC81EB9ULL, 0xDD3001933C366661ULL, 0x28C5EC9BB69A261EULL, 0xFBD435DE810A059CULL, 
            0xA6E261A19101DB97ULL, 0x2C38EA745361FC1DULL, 0xB1661DB3F37BA0CCULL, 0x47758678A7EFFFB4ULL, 
            0xCF6D9F4E819A678FULL, 0x101A5EFE7E5D4CEFULL, 0x8486E7BC5962DF12ULL, 0xA1AEA3816B6685C7ULL, 
            0x921EF3937F244E3AULL, 0x34128DDC3E5C9629ULL, 0x9B05C408BA236C57ULL, 0x116F9661A91D317CULL, 
            0x862F6D8344DF4EDCULL, 0xA2A25167AF4B61C1ULL, 0x966EDA500913145CULL, 0x4DC8864A993325B5ULL, 
            0xA86CABBBA9E8AE0FULL, 0xEFE1F45524D7F7A3ULL, 0x70CC9D0066F56880ULL, 0xCAAAFED5F30B3AB1ULL
        },
        {
            0xD22F7735CF06BFC9ULL, 0xB90E7B2A472C57F6ULL, 0x32BAAD664FC1D6F3ULL, 0x5CA0C4705BA68653ULL, 
            0x4CC4844B5AFFA6D6ULL, 0x90160D0E06016B89ULL, 0x39CB978B3BFE0667ULL, 0x00A1BD450CB04231ULL, 
            0xE55BA9F3859EE89DULL, 0x0AEF0D941EE0326DULL, 0x9CA8CB153A565E99ULL, 0x98CECDEE46695F70ULL, 
            0x43A5ADCF9B0998FDULL, 0x273765285FFB5048ULL, 0x26C937178FE578F9ULL, 0x45118003AD160DF3ULL, 
            0x03E2F3DD27EFE8A4ULL, 0xC76988D7E12C7241ULL, 0x36EE282C233464F9ULL, 0x25CCC3F63C7C580BULL, 
            0xFD295F37EF90D8E6ULL, 0x7099C1DEF140D93FULL, 0xFC373056ADC4B6E6ULL, 0xBB9E51953C0DB163ULL, 
            0x4ECC1FE47B73C353ULL, 0x0AAE3DC96153A6BBULL, 0x2542EC8293F805F2ULL, 0x66373E2536BEAD48ULL, 
            0x43CAB1C84CF936F6ULL, 0x6D39BD54F30F8A70ULL, 0x37986C212761D478ULL, 0x895C10F826016286ULL
        },
        {
            0x9854B078A5575FF6ULL, 0x64C76A6011BD14C3ULL, 0x048397D152B1D157ULL, 0xCB5E5ED33B454F48ULL, 
            0x6913F02069A008E4ULL, 0xB4A8F7A34F98CBACULL, 0x0A83268149005480ULL, 0xC517BADE691C251BULL, 
            0x9857F9A9DE945B50ULL, 0x5DFA09111EB85E8BULL, 0x8166BB4CF97063E1ULL, 0xB2CBD6BC8DFB3F31ULL, 
            0xCECE717E27D0F939ULL, 0x6D338F731574EEE2ULL, 0x84F300B44436D03FULL, 0xCC2444E29DCBBFC2ULL, 
            0xD06F6DB0DAB3396FULL, 0x79CA61B4C24D2A6EULL, 0xCA098FA6839D8D02ULL, 0xAE8E9C29FC3FF0F2ULL, 
            0x5963B023C1E309A5ULL, 0x388E25DC74D7CE53ULL, 0x7A197C63CA17D713ULL, 0x9B0F0028EE75B624ULL, 
            0xE66149295D2B982AULL, 0x0CE6CDDEFD2E14CAULL, 0x0ED8C5EABE3F039EULL, 0x6BE42BC1F7FD372CULL, 
            0xE46FA7FEC07D30A9ULL, 0xF1F316F1A15CB21FULL, 0xC688180DB85F48F3ULL, 0xC1D6080C7D65BDB2ULL
        },
        {
            0x253E2DAB3F45B46FULL, 0x709589B4AE8228DFULL, 0x654268462DEE12B2ULL, 0x1ABA04BE119FB21DULL, 
            0x0294725BAE9DA6FCULL, 0x5F12F35EBD94A289ULL, 0x11B877F74F8C3C8EULL, 0x09AA2EB5B85B4C45ULL, 
            0x4FD3C5C2168B6E9BULL, 0x0ACD8B48F1984AB6ULL, 0x1A43E95E87C247EAULL, 0x03C233FDBBCD64A1ULL, 
            0x1FBC7DEBECB0DC1FULL, 0xABEC9450529517F2ULL, 0x5B1ED83FBB693B2CULL, 0x2137EC84B1FB0411ULL, 
            0xAB79122E29B1FB07ULL, 0x4C9894FEA24B2279ULL, 0xBBD49460298DF039ULL, 0xA3DEEE6098EDCDD6ULL, 
            0x3DD1FA549A9314A3ULL, 0x4D54848832A70A3BULL, 0x94483E6CEE96242BULL, 0x743457AEC13DD133ULL, 
            0x82CD34C490410947ULL, 0xD7B1BD218E58B1EBULL, 0x0C8848DDC177FD62ULL, 0x2A1DBD65AB2211A1ULL, 
            0x3FDEF9894B4D79B6ULL, 0xC7EF23BF23289EE1ULL, 0x5E369209A0303EC0ULL, 0x54D32B2D252EB546ULL
        },
        {
            0x36D07C7ACA030580ULL, 0x72FC1F390681BAF1ULL, 0x96E0277D7D6CF030ULL, 0x8E2138C6E4ED4D9BULL, 
            0xB219CBAB0F57306FULL, 0x2843BDAF2E7E5277ULL, 0x9E7483ED8DCDF900ULL, 0x7CEBA28C61BC2F5DULL, 
            0x99B3BCB550288FC0ULL, 0xB46DDB20E94561B1ULL, 0xEA849FACA2B0E786ULL, 0x434162639A412CDEULL, 
            0x57BAD8C468AEFD90ULL, 0xC90305D27B065CA2ULL, 0x5C60D1C3F91EB253ULL, 0xCADCB465ABFDCADEULL, 
            0x2A60B66125C52625ULL, 0x777E68A9367F4824ULL, 0x9990F997F7726776ULL, 0x5256CF93EAC06339ULL, 
            0x2BA3A4ECE2A3AE44ULL, 0x5D85EF006672A3C7ULL, 0x56CF50D34D32258CULL, 0x920ACE02D8F38C18ULL, 
            0xB56D12B5DEDDF08EULL, 0x3A858C8853FF227DULL, 0x9E9A2D2BD87307DCULL, 0xF05A8F37D54AB915ULL, 
            0xCAF2016F5046716AULL, 0x549486148E8FB5D2ULL, 0x63B3C931F27869CEULL, 0x060016054EA88626ULL
        }
    },
    {
        {
            0x01B1A6EC1C6ECD37ULL, 0xBA4326F44C646B43ULL, 0xE4A96454C7BED137ULL, 0xEBB4355D963C9D3FULL, 
            0x7FF52B4225577D09ULL, 0x81278A1B778E24E6ULL, 0x85DD2DED60FE2459ULL, 0x798619211001313FULL, 
            0x1DF2FD00632DBEFFULL, 0xCA940B912CC95D4DULL, 0x94CAE61F94E6D9B2ULL, 0x61CEB83CE934ACBCULL, 
            0xD71DC900A1C03E72ULL, 0xA95114F2569F1FC4ULL, 0xE939BC74C61330FDULL, 0xA611848A0FAF8997ULL, 
            0x46C39D1551B32ED6ULL, 0x641CE5FFA6753985ULL, 0xA5AD54848BD82FBDULL, 0x05F11A4D730CCB36ULL, 
            0x64E4971DB13E9547ULL, 0x7811FD168BC8B09BULL, 0xFAA1B614FB375429ULL, 0x649F202F62D47E12ULL, 
            0x80540B99F80F5040ULL, 0x2BCD85754A5E5CE3ULL, 0x0CDCED2B3874B239ULL, 0xDD129845153B7395ULL, 
            0x59A112E035717AABULL, 0x16D7C3FA87D7FF9FULL, 0x8D45973CBEDC96A0ULL, 0x0E2C7A10FC3DCC6FULL
        },
        {
            0xB7E09A422A4E5C6AULL, 0xC04272AC843183D5ULL, 0xAB3EE9F738EEC028ULL, 0xA06058E0EBDA7751ULL, 
            0x2EE187ED7759CDE1ULL, 0xBE7416A0F98E77E5ULL, 0xDD2FB963EFDEBC59ULL, 0xCB63272DC0D9F59AULL, 
            0xEBB416BB4643E8E6ULL, 0xEECEE3A30D04FA38ULL, 0xCAFCFEBD13850F5BULL, 0x96640DF5A7B451B6ULL, 
            0xA0DBFAF8187DA262ULL, 0x9BFC1FF53F7EBDA5ULL, 0x46BCFA7EA865C7B9ULL, 0xD99577E433E8EBBEULL, 
            0xE94C2EC1AE814F07ULL, 0x89B344B26C1D63BCULL, 0xE0EAB6E120A542DCULL, 0xD0EEE5E74AB10CD3ULL, 
            0x2084EF4D5875B142ULL, 0x06D990F671D82EA2ULL, 0x24C8E33C4EEFED08ULL, 0x4B78A47C000455DFULL, 
            0x84E289ECD5594EA1ULL, 0x0759F1D584C2DBFCULL, 0xB7C828C7C74C1EA5ULL, 0xCEAA7E41F96D5DD6ULL, 
            0x6A301EC2ED201F49ULL, 0x6370A0C0C20F6C7FULL, 0x98D48BDEEF498D05ULL, 0xC26B75DBB65A9277ULL
        },
        {
            0x20885EE73534174BULL, 0x46056866B9EDC60FULL, 0xF1F4BCF064E8B424ULL, 0x6230D79FE98AEA20ULL, 
            0xF9171FA35FBFA643ULL, 0x5DFE6F4DF614E161ULL, 0x0361D62C9385C011ULL, 0x6B3D225F61CFE859ULL, 
            0xE9A2BC1D72783A08ULL, 0x05CC23911F4E5E5AULL, 0x718A524AFD764F8AULL, 0xBFC3A1B2189BF9B9ULL, 
            0x0A16F80D3B782EC4ULL, 0xAA56A0846E0C680BULL, 0xCDE6D5D7DADD1AD4ULL, 0xE58062FBF45E6786ULL, 
            0x102629D77C19AC9DULL, 0x33CA862E1D91402AULL, 0x0E949E4CB0084CEEULL, 0xAEE84F0397E60483ULL, 
            0x66C9CBDE8EDDF777ULL, 0x0CB2193820C93163ULL, 0x59AD3DC6D7A79465ULL, 0xA14D641C1A119419ULL, 
            0x8B737A4F8B522C0DULL, 0xB701F1D14E21B012ULL, 0x3110CD86E7671E2AULL, 0xCC10C439B0EE6D6AULL, 
            0xD6B1C1E045916E39ULL, 0x98967835010C8D6CULL, 0x836FF95C29C5B0ECULL, 0x6C5C85C2B2CBE2CAULL
        },
        {
            0x71534182591C3A86ULL, 0x8F06A08B776CD399ULL, 0xF92BF86D6ABC5651ULL, 0xFDAE622E33DC81C7ULL, 
            0x2F3EA10A139104D5ULL, 0x32D576AAAF2C536CULL, 0x922FB69F62A5AD73ULL, 0x544815CCA750899DULL, 
            0x19E63CFCB4BDEEB7ULL, 0xCCF3250FAA4D2D52ULL, 0x5D238F457E87F305ULL, 0xD09C80FFCB05EF2FULL, 
            0x10C56143AADF56B8ULL, 0xA5D1781F96C3D38CULL, 0xA8D93C9CFE803FB0ULL, 0xB15A5496094D1D3DULL, 
            0x76DDECEA8A27CF2BULL, 0xB74A3781F1FB3DD2ULL, 0x35F9F564EBB22144ULL, 0x53CAFF392FD726A1ULL, 
            0x71E7125FE25DBED1ULL, 0xE33DF001A322DC16ULL, 0xE57104AF03222734ULL, 0xB427591E250AF39AULL, 
            0xDEEEA19E2CD2949CULL, 0x6EBD84B034B7B143ULL, 0x8D7CB8A40BC02FE5ULL, 0x4AF048F8B23425A5ULL, 
            0x15B47A4DAE5BEB2FULL, 0x3DAC1D3E6DAAFA7BULL, 0xE4672EEBA11648F7ULL, 0x3704B8A59496D30FULL
        },
        {
            0x77621CF6359158D9ULL, 0xD760CE0A402134EEULL, 0x8FBD0FBB23FDA6A9ULL, 0x9E54DFD1983D832DULL, 
            0xBCFDB8DEE1900C68ULL, 0xEDB6F9CA94FE093CULL, 0xE0AB4F26112F74FBULL, 0xC9DB675D76653DF2ULL, 
            0x54BD94ED27C55F0CULL, 0xD594AC5C3B4BBBE6ULL, 0x05631E0FC17C9ECDULL, 0x522E7E9C2FA324F8ULL, 
            0xB810A4D3C78F5532ULL, 0x67EB8D4A7BD96D7AULL, 0x4F799FFC3B786A6DULL, 0x1382DF8675447310ULL, 
            0xC94973631439FC30ULL, 0xC5E3B8D491075A1DULL, 0x83B93D758F0206F3ULL, 0x74A11C436CB3E7ACULL, 
            0x24E6BA7D85BDF06CULL, 0x4799820BF9FF2590ULL, 0xB8AAD4C5A7229560ULL, 0x09C940AA61C6B378ULL, 
            0x58CBA0223747E7ACULL, 0xD3D3BB5F2522256FULL, 0xA551048D79E6986FULL, 0x732ABB3930DEF24BULL, 
            0x22266321C354FA75ULL, 0x3EF8331757A01C08ULL, 0xC8BB91BB328BC32DULL, 0x1BA9469791D6316EULL
        },
        {
            0xFEAB485B9848CDADULL, 0xF461B46B68891B47ULL, 0xFE0DCB5BE03DF168ULL, 0x5578B1A72F67D397ULL, 
            0xBFC5237EF9C7A859ULL, 0xFD9F9ABA0CDC7A45ULL, 0x54F56858280713FEULL, 0x842AB5368DA5D249ULL, 
            0x6655903DD669DC27ULL, 0xAA6B3A90BA53179BULL, 0x2D259BEFA979C67FULL, 0x06537713B5E75FD6ULL, 
            0x85DFEA36BA52352DULL, 0x1A7447F43815BEADULL, 0xCEB68C80C4B70E88ULL, 0xB8D064F5C7F2B9F9ULL, 
            0xE1D8665391FCCAC8ULL, 0x7E22F3D28785D419ULL, 0x99B021373E39FB9CULL, 0xF415B981B30A5D17ULL, 
            0x29CBB99D54FF838CULL, 0xCF0249738A9C0628ULL, 0xD7BBA4C2E0D421DAULL, 0xEB285AC08FB81DDDULL, 
            0xCEF306DFE4D0C880ULL, 0xE49E7C60C5743AB9ULL, 0xC08F43F72B5EEE6CULL, 0x42ABB8E89806D864ULL, 
            0xD41D4106742BF6B4ULL, 0x29DD860270BAE983ULL, 0x4761ACC7DAB88F26ULL, 0x225ACC59B6DE0280ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseEConstants = {
    0x0CB85BCBBC679EB8ULL,
    0x3038F79116FAD8CBULL,
    0xB0B9C6BCD61631EAULL,
    0x0CB85BCBBC679EB8ULL,
    0x3038F79116FAD8CBULL,
    0xB0B9C6BCD61631EAULL,
    0x2456971D4B8F5459ULL,
    0xEA4D5D4071DE1C9EULL,
    0x73,
    0xB4,
    0x32,
    0x19,
    0x2C,
    0x29,
    0xB9,
    0xFE
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseFSalts = {
    {
        {
            0xDFFCE4AD56B2EDAEULL, 0x6910C5AFAD0E8139ULL, 0xB2F919C62007D36FULL, 0x6E50F7C90A497C0BULL, 
            0x539A338214A8EA30ULL, 0x5AC488FFAF2E9BECULL, 0x813D6AC4192884DEULL, 0x717267C3379451FAULL, 
            0x7A45C553C82A536EULL, 0x277D0832507E31EEULL, 0x511C25595C17AE1AULL, 0x194DC83120871B51ULL, 
            0xF00E5CAFC83FB4DAULL, 0xB8D96400E83A2DA7ULL, 0x97B3D365E1FBFB1DULL, 0xEAA20B3D9E0D2D92ULL, 
            0xE0F229C137061669ULL, 0x80FC3B046E8BD46CULL, 0x51243B5ACF90F73CULL, 0xA07E0634A9FEADB6ULL, 
            0xCFB18A5C00A3C557ULL, 0x40139024AF6080A6ULL, 0x110F1B35CA476F99ULL, 0xAE175D8D544D0558ULL, 
            0x436472B2FCDDDD4AULL, 0xB43ABFE842ECF5F8ULL, 0x3E4053EDF1FB977CULL, 0x31EE28D6FC05440FULL, 
            0xC56840D6B9E2480AULL, 0x295A596A87343490ULL, 0x0CB25B2A05626E1BULL, 0xE0D39AE967BF090FULL
        },
        {
            0x481100F30DF26684ULL, 0x17753B12FBEB30F1ULL, 0x0538DE2928E434F8ULL, 0x7080BA30337A63A0ULL, 
            0x2BCAA6D400D25FD4ULL, 0xE1E3347953171081ULL, 0x1964AD69D7EBFA32ULL, 0xABBF3E82002EB8BEULL, 
            0x2ACE13ECA4C28E86ULL, 0xC24F7020F6CE56B1ULL, 0xEB43184660088B7FULL, 0x1AF3C5CC55A69DE8ULL, 
            0xDA48286F55E6857AULL, 0xD64D15FDA05103A4ULL, 0x38E08B265F42134BULL, 0xADC49FF90C2BF512ULL, 
            0x35367FE2D37D41C0ULL, 0xA2A7F57604494452ULL, 0xF5648B532B3C460DULL, 0xE4B69F257CCE6955ULL, 
            0x192B9E73C58CC173ULL, 0x3E4504BB86B7CFFFULL, 0x91FD686BB30E1DE6ULL, 0x5FFCA1FE9687ACD8ULL, 
            0x81B881331E845E6EULL, 0x26F2BD42F74BB43BULL, 0x9FBC60EB3D8D14C1ULL, 0x19A1D9AE32B27A3EULL, 
            0xF2BD58A6FD7D10C2ULL, 0x8C9250FD322EE874ULL, 0x1A7224EC41334D76ULL, 0x022E7EE314FE1109ULL
        },
        {
            0x1F396A389BD1439FULL, 0x6A4FD4E3C3E31550ULL, 0x88BB2162BC3752AAULL, 0x77C15DE94EDC7AF4ULL, 
            0xEB246E827EA1C1C1ULL, 0xD5A2C528B69F3374ULL, 0xF9B19C01DE7A4BBBULL, 0xA1534B937D2527D2ULL, 
            0x913EF05E3E90695EULL, 0xCD9466600545E2BBULL, 0xEACF6157451418AAULL, 0x28AB0CBF6261572EULL, 
            0x962A59F814F5772FULL, 0x93F98B6BBEA30001ULL, 0x9BC8314ED818EDFAULL, 0x3BD0C1B74D8D1AE9ULL, 
            0xC83CBC24DE30FB35ULL, 0x42C16D1BFE02B36CULL, 0xA12993BA458AB7AEULL, 0xB0F9DFAD03E9AE68ULL, 
            0x4EC3E1C39EE30AB6ULL, 0xF411DAB9F6CA78BAULL, 0xA172FA9FD58B0639ULL, 0x431E54ACF089238FULL, 
            0x0BC5A57D5E1C8146ULL, 0x994A47DE4063E98BULL, 0xDC6A2EEC7AE9C6E3ULL, 0x59781419B2A16348ULL, 
            0x29A24618A2F2DAE5ULL, 0xC34606BE4253AB35ULL, 0x75EFB4FEED89271AULL, 0x2593027BB7FF9141ULL
        },
        {
            0xC630D9B156B4CFE4ULL, 0x4CCB5F51BD9C4BD4ULL, 0x6354DA6262695B29ULL, 0xCA181696E70ED0BAULL, 
            0xC4657D8CCC3A29B4ULL, 0x53772D5F70AC0D2FULL, 0xDA85424CAAC4D6A8ULL, 0xDE0C9CE35B435197ULL, 
            0xAFC05FDABFBD5658ULL, 0xEDA54872889E78D9ULL, 0x6F40A4D93D3E83B0ULL, 0x4EED22A1BC4DA4B9ULL, 
            0x22182C1E65E30A64ULL, 0x340FA6A9DBF2C4D6ULL, 0xC030C50E33C0570BULL, 0x8A3516757AE9FFC1ULL, 
            0x649E8D5FE9B9AB57ULL, 0x12EA19A9391D22E2ULL, 0xB07B8EF6CA106158ULL, 0x724196CB2067573FULL, 
            0x0101237C36B3153EULL, 0xE45B09B58278CA77ULL, 0x2DCF74509D6DE434ULL, 0xB2A6A82719679C6AULL, 
            0x3B7B81CDF49B03FFULL, 0xE25E63D573C4047EULL, 0x5FE93A08A4CB7B41ULL, 0xADB9066D8B2B4DD1ULL, 
            0xA14BC26AC8B21545ULL, 0xE6ABB4DB8D070F99ULL, 0x361E7581549E5539ULL, 0x58E6A6FDFA5C3DDDULL
        },
        {
            0x8ED1C157AE69EFA7ULL, 0x41CBCD296113CEB1ULL, 0x3746437E286A8676ULL, 0xC96A0DE01387611EULL, 
            0xFA81CB9B5E080555ULL, 0x688FDE2944B5DC51ULL, 0x94C0B73668EF4CC0ULL, 0x86D42737D05EEE9FULL, 
            0x59DF90EA64CDCAB0ULL, 0x890F22E761A6FA27ULL, 0x495938C9FDD4763DULL, 0xDA96F6116CF5ED24ULL, 
            0xAC68FB25D64C3CD4ULL, 0x30FF60798B978C76ULL, 0xF881FA0118B66120ULL, 0xBC9817E5158716D1ULL, 
            0xB1B2EAC0178A1E1AULL, 0x342F16DA6BBA0169ULL, 0x51A0BB11C42EF9ADULL, 0xF9832C539903A847ULL, 
            0x6E13592ABE74DC83ULL, 0xF6CFAEA4FDD61BDEULL, 0xBD2271064CF2E9ACULL, 0xE5BF1AD345C0184FULL, 
            0x35D91AFA32B9813AULL, 0xBD0B693184BC5A4AULL, 0x289863ADFFCD579CULL, 0x83807A58C83FDAD6ULL, 
            0xB2DAC19D76F53FDCULL, 0x7A4604D6EE110642ULL, 0xE468E3400DA91FA5ULL, 0x74DBF7B5DD9291E6ULL
        },
        {
            0xA8A3FF1EF0A0166CULL, 0xC3F66864A8BF4D36ULL, 0x20DDF46015A92667ULL, 0x0E19E947EFDBD80CULL, 
            0xF601C1C7E8B70D48ULL, 0x440CB977E274835CULL, 0x2035E77CC8C6B081ULL, 0x5253789481DAD5A7ULL, 
            0x94E348E546CE15C2ULL, 0xE832DCC0DB9ADF8AULL, 0x51E9FF15C1A06FD7ULL, 0x1C2F0A09842A7CFDULL, 
            0x4CB52EAFE789BB7EULL, 0x5408D1684F527B62ULL, 0xD5B50AE947E5DB64ULL, 0x4A290D580C7F386FULL, 
            0x1CE9BDD7645C0A3DULL, 0xC8A4009842D8A7AFULL, 0xE32396AE6EBF52D9ULL, 0xF4CA637CDCA82740ULL, 
            0x1B40A5053AD442F4ULL, 0x9DCAAA7F9DCD3980ULL, 0x54C8BBDE45E57169ULL, 0xE2654503A140FE21ULL, 
            0xC44484D8F7F083C8ULL, 0x13D144E975375A6AULL, 0xE7D6D1A6F6929632ULL, 0xB26CA0AE6B2B6FAFULL, 
            0x7CE904CB653C73D3ULL, 0x9833C6DBE7A95242ULL, 0xAC24D93179543409ULL, 0xFDB4B3A7A392090AULL
        }
    },
    {
        {
            0xF24F451BCE1653DDULL, 0x58EBD941F6C79DAFULL, 0x7322F23DCA852D12ULL, 0xBC82B6FDD6F3BEB5ULL, 
            0x242488B37C1CC64DULL, 0x226A1A94E611BFA0ULL, 0x65935E5B17D583E4ULL, 0x4BFBD8CDDA8C694BULL, 
            0xA6FE417C0E099971ULL, 0xBBA0BA830F68BDC4ULL, 0x69FCAF8B4AEA8437ULL, 0x6FC27AC230069BA6ULL, 
            0x3627D42F87E23335ULL, 0x59D8AA33513020EDULL, 0x24C88B25CD4EC916ULL, 0x78A7DA58A3885D07ULL, 
            0xC19B8793721082F9ULL, 0xFC23AE71256AA5E7ULL, 0xF0FD6665ADF3C3C8ULL, 0x3915076ABE4CEEF3ULL, 
            0x01BE3DB1801112FCULL, 0x6C9059CC19F5DD1EULL, 0x530FF70ED57E70F8ULL, 0xB085A31BE8FC6333ULL, 
            0x6028413C82197140ULL, 0x295E5206BD4810DDULL, 0xFBA736ED21DAE00BULL, 0x47AEB5E71405A793ULL, 
            0xB28B20B71BDA3701ULL, 0x2D3D69458C5DC5ACULL, 0xBDE518F712953A9DULL, 0x2A50C510CF3647ECULL
        },
        {
            0x8736B20D1F79EF9BULL, 0x34D9AC8CF8C266AAULL, 0x47A5240D24BBFC18ULL, 0x7A6C099DAF44514DULL, 
            0xB1D99E3DE011105BULL, 0xD6AAA0445A51ABE8ULL, 0x7A85ACC89230D6E5ULL, 0xAC9323C65070EA13ULL, 
            0xBF7A5F2B301DD6C0ULL, 0x0EF6CF641E255AFDULL, 0xCE4D618C0E00EA5FULL, 0xD33D8EF1A7D263F2ULL, 
            0x7FB0B63BF1723E10ULL, 0x7EF913E56668F490ULL, 0xD915E2DDEA45DB7FULL, 0x03A72EF40D1292D8ULL, 
            0x6C44D1ED58D27533ULL, 0x215D7FE38839EEE5ULL, 0x686B080030B3A5D1ULL, 0xDC14E099EB61C9C3ULL, 
            0xA45EF67D35807934ULL, 0x141D823AE28069B7ULL, 0xB32B4600F5F67329ULL, 0x8CC4544639485133ULL, 
            0xC233096BB722350AULL, 0x20F7FE40AA52226FULL, 0x48A39C9141E618EBULL, 0x14087C2AD9DD6AAEULL, 
            0x6AF75CB70D158A9AULL, 0x9A531C684AB3FD82ULL, 0x1486FE36F76DBC09ULL, 0x2888CE4193764551ULL
        },
        {
            0x4C3CDFD1288ED98CULL, 0x165BC255B9837838ULL, 0x685DD470AA6DF83AULL, 0x4D02A4ED28BA7149ULL, 
            0x317D97B4A6F21EB3ULL, 0x41A0CD31486C3746ULL, 0x4CE9E46E9CAEF7BFULL, 0xDC5C2FB25283520AULL, 
            0x3000142BB5035EF4ULL, 0xBA7B5B59205AA3FCULL, 0xD6F7912C7282DE21ULL, 0xB66536F021392DA7ULL, 
            0xD6A66CE93F99D851ULL, 0x3DD8E7030C5D16E6ULL, 0x54C94B69D410B703ULL, 0x2DB3C3586389735DULL, 
            0xAF6C9D2966AF7946ULL, 0xA1641DF01EF73A0DULL, 0xF32F9668EA33CC5FULL, 0x732ED301533A545CULL, 
            0xF575E48CCC18E7EFULL, 0xA320879A7F59ECB4ULL, 0xD84560B2951496C3ULL, 0x9274F651F8010499ULL, 
            0x072A24A99A9DEE6AULL, 0x99AAB702C543A627ULL, 0xA039DAEBF0FF119AULL, 0x92C06FA68B3C1CB2ULL, 
            0xCEF2ED3DE364A821ULL, 0x1976838D85643A36ULL, 0x058BD0D6A732A987ULL, 0x13F491E8CA454301ULL
        },
        {
            0xA07C30D9F5933392ULL, 0xC191F1C45F6923A5ULL, 0xDACE51475B5E0772ULL, 0x0A594FEDED287F40ULL, 
            0x80B352BE3C2565DCULL, 0x6402A21FB920CE8EULL, 0xBFF10FDDAC14CD89ULL, 0x6D20CF6A0DA2D02DULL, 
            0x3BE402ABD64954E1ULL, 0x825F9E2D5270866CULL, 0xF8C0BEE2625E8104ULL, 0xA132C94116843925ULL, 
            0xE8B66EDC556F4AF7ULL, 0x38B307BD5D85EE53ULL, 0x32EA35BFDA9F68AAULL, 0x5D6AB840D3E7D884ULL, 
            0x7EEA1DBA1FD3DB0AULL, 0x4A2A4604FA2B40C6ULL, 0xBE19DC77C2ECF10CULL, 0xB5F9BDFD0DBCA08DULL, 
            0xA6FFD9CB990D85F5ULL, 0xDB9575432B256D60ULL, 0x1EDD11BA6AB4A69FULL, 0xA1C6D1ADFCCF030DULL, 
            0xF6E75AE6956C0753ULL, 0x275F030E1F82CDD9ULL, 0x8A0765351AC27728ULL, 0x61ADE0ADA648E92BULL, 
            0x691D081E71CFA89DULL, 0x06C94BB4C7DB344FULL, 0x560307F1E677F880ULL, 0x619F0C801A370702ULL
        },
        {
            0x2B66E294176798A6ULL, 0x7540E3035C918D38ULL, 0xE499725B13944D60ULL, 0x1C2F36EBA2E07A9EULL, 
            0x81A255D5504DCDF5ULL, 0xE323D5177C1F27A2ULL, 0xA2C325068C06EEFAULL, 0xEF0916711003B317ULL, 
            0x765F61E2374EF336ULL, 0x6921DDEC683A6FF2ULL, 0xC5DD1B68C3A11472ULL, 0xB015E00B0A263C08ULL, 
            0xD3528C108E567080ULL, 0xEE564FD29E5BFAA2ULL, 0x91885D6A52D74E21ULL, 0x2365B8E6DDA2FCC8ULL, 
            0xDCC66C9C55B3D58EULL, 0x097DBC1FB410A204ULL, 0x4DAF0AB4F656C98AULL, 0x75D544912216B7E1ULL, 
            0xF9AB7624D8E3F31AULL, 0xDB6E285D45B32604ULL, 0xA291A4ECA8FAD992ULL, 0xA190EF66F6C78B1AULL, 
            0xCEB4A00F2804E3AAULL, 0x677999B4D161A224ULL, 0x06A69FA7ABF3D745ULL, 0x9488D04635A056A8ULL, 
            0xE9F0A31563845AD2ULL, 0xECFFD4E6B6E2BFA0ULL, 0x41C63F28DBA6E8D8ULL, 0xB808008CE8EC2885ULL
        },
        {
            0x418E57D797B809C5ULL, 0x5D105A676813B6DEULL, 0x3ECBA1508F6D7770ULL, 0xC24FA64EFB8EC50BULL, 
            0x39ACBA8038BCB2B2ULL, 0x85393D625CA7E318ULL, 0xFA710507D032C2F9ULL, 0x857AE0DEC7FED76AULL, 
            0x2B7718DCD64489F0ULL, 0x5580AA6A3219AD31ULL, 0x15C37CA33A737DD7ULL, 0xC0E9EE7421664F9BULL, 
            0x8376C635D43DB209ULL, 0x8962BD21E93C9F0BULL, 0x79159E58FC618915ULL, 0xA8CB2505C9484F74ULL, 
            0x6B90C58633A954D2ULL, 0xF27987CBC0FEC7F0ULL, 0x3316A21FAE1A835DULL, 0x92B49CBCBB83576BULL, 
            0x585B1AF8D77297F8ULL, 0x60FFEE92FD3B43B2ULL, 0xE324B5C72C5ABC8DULL, 0x49D00D16CDA530ACULL, 
            0x9D5AB39923F19D0CULL, 0x1625BBEDBA3E0A5DULL, 0xA8691F9CA97F84BEULL, 0xF5446D656077AED2ULL, 
            0x67A852E19573C5ACULL, 0x36C60B6BBAA39A97ULL, 0xD202E7BF726EEE82ULL, 0xC366C5F1E82BCB32ULL
        }
    },
    {
        {
            0x2C63D41977F52914ULL, 0x1CC955D96351AD86ULL, 0x12F6BF159A67C5BFULL, 0xB70EFA0B9C155A81ULL, 
            0x2278227714F11C12ULL, 0xF4939C10C81C2FDCULL, 0x722F72FB91557AD5ULL, 0x35142CEAC60655E8ULL, 
            0x58DFBB376F9AC98AULL, 0x235E4072F51612B0ULL, 0xADB4BFEE634DDD12ULL, 0x501C77C538F09F14ULL, 
            0xC2BCBD726EAACD13ULL, 0x44DB0FE006AF6B95ULL, 0x2A29EE7306F72141ULL, 0x3EC65DBE13C290EEULL, 
            0xB021498E9B06F268ULL, 0x122310076DA85B7BULL, 0xB0089071C963A3B9ULL, 0x3A360428B62D92FAULL, 
            0xF14E891A96FB6588ULL, 0xAE6A1F19F607F960ULL, 0x031A0F209E46F0E5ULL, 0x91F978122E899B83ULL, 
            0x252060DDF506029CULL, 0x9D2E14A44D277C8EULL, 0x471D1F954F9252EBULL, 0x10EC9A965C540D25ULL, 
            0x53A92BA79761FA08ULL, 0xB6261132A3BE93E5ULL, 0x8F0E76959A275816ULL, 0x4C9707050E59494EULL
        },
        {
            0x3D28B3F725475701ULL, 0x490C17969425A963ULL, 0xF820D43C0991AB88ULL, 0x4A5BDB0549622C4CULL, 
            0x6183DE9178D35AB4ULL, 0x5B08665B5B33D30BULL, 0xBE9E988B0F5242FEULL, 0x761875BABB6DB728ULL, 
            0x857AF676775DE754ULL, 0x9EB40B6A3239FE71ULL, 0xF276F5AEED894F59ULL, 0x7C753BB984A5B849ULL, 
            0xF3577D68A60AFD69ULL, 0xD1E85D746DFAAF66ULL, 0xA10DC4A95C3C5460ULL, 0xE726FB6C183BA428ULL, 
            0x3F55260A48712B53ULL, 0x6DE3F0EEA39CE21DULL, 0x36BFABD4DF154C42ULL, 0x85CACCA46993632AULL, 
            0x31D6ED2097FA422FULL, 0x3A1A31224A70E4A8ULL, 0x37FDA7FF15DC53FEULL, 0x6389B33CCEEAD760ULL, 
            0x85E3AAE2C96DF428ULL, 0xA0AC983806225A6AULL, 0xF69CA826E345B82BULL, 0x3769A80C04821354ULL, 
            0xD5FF93817F372263ULL, 0x4AF376E02BA025A3ULL, 0xC1FC852D6B3B7733ULL, 0x6910D67F7DDC9DC0ULL
        },
        {
            0xBA8CD4198E58700FULL, 0x4EF29CEDB20080F7ULL, 0x15F265085A028434ULL, 0xF59C627DC0815F8AULL, 
            0x7D8B35E5269664B6ULL, 0xCCE1B94C10F18D07ULL, 0x9CDD8CAA8C590924ULL, 0xC1BAF94356C13664ULL, 
            0x0E89269F252E54AAULL, 0xE23C020D9357E403ULL, 0x14A2B2A3285AA9C6ULL, 0xDA798364D66A6C89ULL, 
            0x4E5F532CC677AF81ULL, 0x95760EC1AB39DC5EULL, 0x20FE64BD0DC3E4F4ULL, 0x32679DBB9940B256ULL, 
            0xBA15B69F9E11556DULL, 0x1CF91B8EA1E6C438ULL, 0x3BEF1EC662FF08ACULL, 0x4995774AE8C1B9DDULL, 
            0x2A19447417EDD705ULL, 0x0F5BF32F4A3D26ACULL, 0x2D8FE685118045ECULL, 0xFBDB08A6DA56F45FULL, 
            0xB13B1E8186597A3FULL, 0x33A6DC5ACDDDF48BULL, 0xC63C8E152842BB0CULL, 0x6940B6DC83C15D40ULL, 
            0xB7F3DF9293924BFBULL, 0xB5F3140DCFE787DFULL, 0xCFB9F6A0418F2F4DULL, 0x650D665E99AEA2F2ULL
        },
        {
            0x63A48F786EBDB26CULL, 0x6B7C1CA1232C9241ULL, 0x4F8C53816073CE2CULL, 0x03018D72D95FA8A0ULL, 
            0x7B9EB10C57181B6FULL, 0x3ACC8B728558D2B5ULL, 0x224A4B32D63141A9ULL, 0x4C44A99CB989CC76ULL, 
            0x8066E8B13A518D3EULL, 0x40F1674CB3610A42ULL, 0x425185A0547DC4C8ULL, 0x19D6633E32C4FBFDULL, 
            0x142FA079C7717004ULL, 0x4B0BB89218956FCAULL, 0x6D2F5CB5A01A3439ULL, 0xE0DCB9BD8FFB19A0ULL, 
            0xD565706E364B008BULL, 0x440461F4528ECE22ULL, 0x4E2A1B0FF3CBA019ULL, 0x183BA7323BA513A9ULL, 
            0xFDC949333DD9F9E1ULL, 0x4737C56C43C266FAULL, 0x5969D7C4D600A0A0ULL, 0xFC6E22341933E733ULL, 
            0xD470F5FA86AEEB19ULL, 0x620C15311F717750ULL, 0xF5C8CD39B73C5E6BULL, 0x646BB2A6AFFD303DULL, 
            0x695F1A6D07877F89ULL, 0x559CECE990CF8D15ULL, 0x7578F458A4677203ULL, 0x7CB4FEB4E52496BAULL
        },
        {
            0x5D995532852C53D0ULL, 0xF6F763BE27BAA242ULL, 0xDD4183651B793ECCULL, 0xE072C2719118D28BULL, 
            0xDDA851F8AF552EF6ULL, 0x645F74AE4D97599AULL, 0x6A6462A69D692949ULL, 0x3CD5DB6676A40402ULL, 
            0xFF186BABD560812FULL, 0x050D25862D70BA81ULL, 0xCF85A698E465DE67ULL, 0x2928E7C0FAFFCE44ULL, 
            0xAD48F00243352D41ULL, 0x8292403D999BB934ULL, 0x4170F53DE3BC740FULL, 0x6562253EF30FA5D0ULL, 
            0x9ECE0D338E909444ULL, 0x51E7F34A6920E5DFULL, 0x1AA4A06BFDA0BD24ULL, 0x29726FCBB041997DULL, 
            0xF148C55F707AC406ULL, 0x4FF5A0A831212918ULL, 0xBCBD333088A2E1CBULL, 0xF5F2C2E671664861ULL, 
            0xBE96216240774F36ULL, 0x8275A0BB62415FDEULL, 0xF009C2BA66F32187ULL, 0x856AB2BE014674C2ULL, 
            0xD225856293A0D7C0ULL, 0x784AE24C8A211056ULL, 0x7A67C2939A57450EULL, 0x3B44B5B803E2A45DULL
        },
        {
            0x2939A3840AAC7D6BULL, 0x284A1BFCAFA38652ULL, 0x041880DC13EDB1DAULL, 0x6BE2EF6FE0FC79F3ULL, 
            0x95BF2E3F73B805EFULL, 0xE83B9EB6551D0293ULL, 0x4FA1E69E9C959D7CULL, 0xE9BA5090F4ED9B30ULL, 
            0x1197BFC3295CA204ULL, 0xBA30D23F5293ED41ULL, 0x4035385EA692D38DULL, 0xEF6FFC7754EC0627ULL, 
            0x8C9FB723C9D6F9CBULL, 0x25C19973E38C0081ULL, 0x05CFCD89DE88CF0FULL, 0x300572E7B566C2ECULL, 
            0x60FB1C1E34E22485ULL, 0x594B736854EE0392ULL, 0x8D27BB98311918C4ULL, 0x5426F1A286B15523ULL, 
            0xBBECE7A3F4A8378CULL, 0x221921E8D44CE817ULL, 0xC284BEF4E8A61973ULL, 0x5F2E7C1086954448ULL, 
            0x59B94724096C301DULL, 0x4CF8D5E150165109ULL, 0x5FA4E4BF0FD3AC19ULL, 0x773AFF55D6A0424AULL, 
            0xD2CDFAE39BA551F5ULL, 0x9905C06C7A1C2778ULL, 0xED91CE87B545AD35ULL, 0xF3564B9508C877BAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseFConstants = {
    0xECBF3F920ECDD0E6ULL,
    0x5ABB27E17A6DFB19ULL,
    0xE75E202B6690725CULL,
    0xECBF3F920ECDD0E6ULL,
    0x5ABB27E17A6DFB19ULL,
    0xE75E202B6690725CULL,
    0xD769E6C93DC7E7CCULL,
    0x3D557F11DF09F8F2ULL,
    0x92,
    0x1A,
    0x8E,
    0x89,
    0x78,
    0x45,
    0x31,
    0x3E
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseGSalts = {
    {
        {
            0xBC83BDEFB72CC297ULL, 0xBEADE9C6885BF81DULL, 0xB0D707F607C32B14ULL, 0x3FDF9F7CB2C76E7CULL, 
            0xF08D234387884EC2ULL, 0x05B83CD09D2676EAULL, 0xCBB1F1D0B9288D5EULL, 0x9B2E34F3DF3C8797ULL, 
            0x0C4D52AD67AAEB55ULL, 0x6FEE3B3547F4B4B8ULL, 0xAA6086E9E7649F34ULL, 0x1307FA07A78BF000ULL, 
            0x24D90F212B724063ULL, 0x73D96BA1080B6E3EULL, 0xDA00FD798088FD50ULL, 0xA134AA0C911B7512ULL, 
            0xBAAD2C99027E2CFAULL, 0xE41F8423D7754B47ULL, 0xC613DFFC40B4C2CBULL, 0x756D972928BBDCDDULL, 
            0xB0A5CFD53EDA548EULL, 0x83856955873F41F7ULL, 0xCE2401C6908B5C93ULL, 0xF6D55ADE0C8E9DEBULL, 
            0xA4E8164378B97F1AULL, 0x5352575FCD103621ULL, 0x26FAA8D97C7F9EC7ULL, 0xD4967B60E2B4C43DULL, 
            0xFE56DDD0A28DB7B9ULL, 0x8A2A2D717EF9D1ADULL, 0x1A80F26C909F1DB8ULL, 0x1D3B2D8B5D174C58ULL
        },
        {
            0x25D5E98C65ECBAA8ULL, 0x3933CEEC4F1D8182ULL, 0xD52EAC9F14AC893DULL, 0x571057AA898A59C0ULL, 
            0x4DA8270598997A80ULL, 0xD8892886BE27C148ULL, 0x4669256F0A4F2242ULL, 0xCE075435596FF900ULL, 
            0x0B9BA6863EAE2F1EULL, 0xB1063DCB1BD3F29EULL, 0x24F086D4E5219CF2ULL, 0x8531672ACE08E87AULL, 
            0xD2F77BB0AF221BD8ULL, 0x60FE16284F45912AULL, 0x4C18D5478E9F582EULL, 0xC7F892A9B29459E2ULL, 
            0x305709B4971FAB47ULL, 0xA81697FB7EF9178AULL, 0x8D86F04C20D838FAULL, 0xDB478F6391AF2DA7ULL, 
            0x6E4DA8FFEA4D6EC7ULL, 0xCFD6251A26A3570BULL, 0x98E388A176866F87ULL, 0x94482F889328F06BULL, 
            0x20A07C46C573B847ULL, 0x38E0D0F681660DCAULL, 0x03F1A734BCF4874AULL, 0x6CC490FD903DD91AULL, 
            0xC6331F815D96EEDBULL, 0x667373EA039DBF44ULL, 0x8D0C2FE6B013E087ULL, 0x94087FD006B83894ULL
        },
        {
            0xB31A99BE485E4EDFULL, 0x48FF31119CBD56A4ULL, 0x5DAED12B10D13AB9ULL, 0x3D0ABED88C7EFE91ULL, 
            0x1EC1C43B8260ED76ULL, 0x40803663F03D50D9ULL, 0xBE27F88E5B5F6D2DULL, 0x82C9C71438FE1199ULL, 
            0xD6EA461347C5F17BULL, 0x6425BBA2DB7E0FA4ULL, 0x927A720920AA0D8FULL, 0x5ABBACFDBF3AC151ULL, 
            0x3857D6386C0ADD4DULL, 0xFF9A6C65EDA32261ULL, 0xD3EC51DBE4623417ULL, 0x619FD4512AB2DEE5ULL, 
            0xED68EB18D71AFBE8ULL, 0xE2F7AF6369707DAAULL, 0x088A75BE7F099F1DULL, 0x702500AC2817C74BULL, 
            0x0F25F91A11C684C0ULL, 0xE5DF67C5823B4D75ULL, 0x162CE109E8CC3F2EULL, 0x2A687182234DB21BULL, 
            0x1BD1C4C9F7AA9D4CULL, 0xF7A81E19AFBADB88ULL, 0x734AAEA5C171EB7DULL, 0x430A3E36E7DC9194ULL, 
            0xD9E74593EFFB45A4ULL, 0xA6ABA4DA83993BC7ULL, 0x02A12C1CEB3D25ABULL, 0x818830ACBAC0FD60ULL
        },
        {
            0xC4EB61E7511CF314ULL, 0x6843793AA9BF1B8CULL, 0xC82CD6E936BD9494ULL, 0x0D4BB44E3C648217ULL, 
            0xE01F7605B378FD9FULL, 0xF9CBE11D2138959BULL, 0x0DD2D2D9D486DC50ULL, 0xA1C7407E13B929E9ULL, 
            0x9CE07442B9EF9C0CULL, 0x24E3A0AFE3CB50ACULL, 0xA0AC28F07074F014ULL, 0xCC9644FA61568199ULL, 
            0xEB02A2B5B57B8DC1ULL, 0xD1FB45D596965FB3ULL, 0x90250575AAC59C34ULL, 0x2FBBFC7233C4ADD7ULL, 
            0xE4B8E358090C383DULL, 0xB7717EBF2C67714DULL, 0x10FF347199B985DDULL, 0xC76E8B6EFE04248CULL, 
            0x42613B5BA204D8FFULL, 0x6069DEAAD2A09B2CULL, 0x867802E8561A35EAULL, 0xBDD1816BD5D774EFULL, 
            0xF4019A53EFFBDC56ULL, 0xFCE47529612AD9DDULL, 0xD41F791CFE58D82CULL, 0xE480EB01D27D2609ULL, 
            0x99557FF8B14196B5ULL, 0x73B502DBF27C430FULL, 0x9B8CD5389358F0C7ULL, 0x4859B0716864B2D9ULL
        },
        {
            0xD4AFD258EB6F5735ULL, 0x1C009B8CA13A34FCULL, 0xFE5C345E75F750D5ULL, 0x97A15D77F14FD723ULL, 
            0x7DDE60FFC655B00AULL, 0xE178DFFEE903531AULL, 0x9199FAB519B0E399ULL, 0x130F22021F83D081ULL, 
            0x0CF091BF9F7925E0ULL, 0x25E06E19067ECF09ULL, 0x0AA14F7214F507B4ULL, 0x230A2FC9A83B5152ULL, 
            0xA315BA3789F0901FULL, 0xCD5A652A995DE395ULL, 0xBA9EEF139661E1CDULL, 0xC07DDAB11D7669D8ULL, 
            0x1941684DCFA2F8D8ULL, 0x294AB576ACA0D1C0ULL, 0x6FC658221D282714ULL, 0x4848677A47051EA0ULL, 
            0x1D543555361655ADULL, 0x7A59902000C16516ULL, 0xA2BDEE6F8F959714ULL, 0xBF9BD133C4F14164ULL, 
            0xD8647D59F028514AULL, 0xFFEA2EE7EB6E62D6ULL, 0x39BC5B8638593E58ULL, 0x4A1F5039870FD3CDULL, 
            0x20953B3D7D4D4A11ULL, 0x076135AAB7F6318EULL, 0x7B50F59168EA9456ULL, 0xB1A73FD603599270ULL
        },
        {
            0xAD45380E31D0E3DFULL, 0xE427AB281C003378ULL, 0x147CBA404FC0C7A3ULL, 0x164051C779B18DE4ULL, 
            0x413BF1D202DE08B7ULL, 0x11FBC352103C30EAULL, 0x90F43A9B33462F44ULL, 0xDA5CA3C7C0AD1A3FULL, 
            0x23F0410CE57C7593ULL, 0xC99E5DE4B5B7517CULL, 0x575A724A1E411323ULL, 0x64B016508759B5A1ULL, 
            0x457240E06CF99C18ULL, 0x4557544A31FC5405ULL, 0x0E1276C3DD754542ULL, 0xFB1F630B4D49FF2EULL, 
            0xB3DC0210C2FCEC61ULL, 0x9F5627C314E82D2EULL, 0xDDEE6C402C53ADAEULL, 0x088AEF9B30154D18ULL, 
            0x400FE7B72AF2C76AULL, 0x0C132E334C2D04F0ULL, 0x988A9150E17CFE54ULL, 0x44BF7307C27E8AEFULL, 
            0xB1DA990FF07497E6ULL, 0x918E66566FBC9490ULL, 0xC34045AD555B417DULL, 0x5B13BCFB670AF0A6ULL, 
            0xF6D777169AAF6C39ULL, 0x1BCB10452DD3CEE9ULL, 0x1F2C687A56988236ULL, 0x5C9295A1DA2C4B6EULL
        }
    },
    {
        {
            0xAE6D2CF4E967758FULL, 0x3785234E83599447ULL, 0x7785FF693E8CFB03ULL, 0x6E83721B5E72D798ULL, 
            0xDBF4AACAD21033C5ULL, 0xB9F81D53978E31E6ULL, 0x1598D5F778919D53ULL, 0x45D2A2696E73F10DULL, 
            0x4CB377E642D20E4CULL, 0x7C3532FBF96E4CD0ULL, 0xA4950FE5B5BC1315ULL, 0x40152EE930E88546ULL, 
            0x6271E5DFC7E013D3ULL, 0x9173063D90A39F76ULL, 0x19D4908B60F6E015ULL, 0x0807CABDAEFE4463ULL, 
            0xABCE4D8DC27EEB1EULL, 0x83229830158D407DULL, 0x0B2E8A44A6D6F384ULL, 0x160D6BA53588325EULL, 
            0x6ABBBA90BB3B0F6EULL, 0x4D123B90E78D2B38ULL, 0xB3C757D8AD0D9A31ULL, 0xF259DFE3AFC25261ULL, 
            0x45B4C7831D0ECF1BULL, 0x1AE499B60530E822ULL, 0xBBE3B2B6126FA2AFULL, 0x2784A6024391B5DBULL, 
            0x84734CB3DB1EBD29ULL, 0xAE1589C55C5CDF0DULL, 0xAE188F49CB08027AULL, 0x6C747565A6EC27E2ULL
        },
        {
            0xDF7D211CF5C1EBC5ULL, 0x1F1A34606D53C177ULL, 0xE43E36B8F0150FEBULL, 0xCB276D1881BCCD01ULL, 
            0x55DFD3C29CC64EDDULL, 0x3D8519847133A5F7ULL, 0x09B263CC520360CEULL, 0xF11C8D3C71360603ULL, 
            0xDFF6F205219D85A6ULL, 0x10A7A631C583EC43ULL, 0x9B835167452C775AULL, 0x7296F6047C7D123CULL, 
            0xD040CCEEA436AA68ULL, 0x911E0324800F2F1BULL, 0xDA5DE69B41C8423BULL, 0x3D7FB2D5DA3E769CULL, 
            0x4AA0AA30AEB51B83ULL, 0x30CB45619463141AULL, 0x556336995CA6A0D6ULL, 0x6F2BF71FC459F7F2ULL, 
            0x45D278F34E5BE5A9ULL, 0x05C031EEC06242D6ULL, 0xC79682050EBC0662ULL, 0x9DE71E5C37AE9B53ULL, 
            0x033425B6F290BFD5ULL, 0x4E407603222A94A6ULL, 0xB727628E72D8D858ULL, 0xBD5AACD13C085DB0ULL, 
            0x00F7F129A2707F7DULL, 0xFFDE6DC559F0B3E9ULL, 0x50B47BB4A2795F7FULL, 0x3CFEDE146C2F9F3EULL
        },
        {
            0xF8B85B731CF9DA57ULL, 0x49B68F5549CDE811ULL, 0x63A413D8CB30BCE6ULL, 0x251F51C31E462337ULL, 
            0xF9F5ABF6AF649334ULL, 0x3D9C5C38300FF28BULL, 0xE8A6F046941528A1ULL, 0x6A9C9552C471391DULL, 
            0xBFF272988963338FULL, 0x4AEB064A4CF9654CULL, 0x67F91917E1AB4E06ULL, 0x8FA81003567F5382ULL, 
            0x47E4685F5A88425FULL, 0x291F2BB7854EA180ULL, 0xB2F3EE1E07988F4BULL, 0x5830B9DD3694E301ULL, 
            0x7C6DEAB50B5927F2ULL, 0xFA4884CF65111069ULL, 0xD9C66F5E60D4A359ULL, 0x71EA5E9B38E21EF4ULL, 
            0xEE578AF6C42A6910ULL, 0x68B5996C79951865ULL, 0xDF4DCCA8D328E0E4ULL, 0xCAAB330E7B3C9AA4ULL, 
            0x9E045D101C140404ULL, 0x9DA7E9E00C92FC61ULL, 0x2D1EE73D024CBF33ULL, 0x602F6B734904909EULL, 
            0xF71FCDF4890C49D0ULL, 0x9F883EA8C825C28EULL, 0x5C6403FFADB53618ULL, 0x50699E5D61A7D0CCULL
        },
        {
            0x9A49AF7B2AE70D0DULL, 0x3A838D9572D04D4AULL, 0x5BE1877FBE47EB0CULL, 0x207C3ACBFE1D1B72ULL, 
            0xA6B0E2268C765BB4ULL, 0xDF15B87A9FE139F2ULL, 0x41DF01E74F1E87D6ULL, 0x00BCE9162BFCD9AFULL, 
            0xCDDDBA6B7DB5D701ULL, 0xAE42921F5C9F29BEULL, 0x3DF429A18047A1F1ULL, 0x0CE3ECC88BCC70FDULL, 
            0x3F536A8678CE112FULL, 0xC1787FB31A2A136EULL, 0x82FFD4028D1785C4ULL, 0x6C53988D8C6C5D67ULL, 
            0x4989BD2B335DFDF6ULL, 0x6957909EBEFE1D7EULL, 0xB172E9F12B7D5EE7ULL, 0x8F37085D0A4B4C3EULL, 
            0xCB828F517FDC062AULL, 0x7C142DB55B514383ULL, 0x9F12D7A741673FC5ULL, 0x1115258C20FE0FC2ULL, 
            0xFFC7052F8F80D7BBULL, 0x327933CFC5D5378CULL, 0x1687F42105D19006ULL, 0x58C165EB214AB64AULL, 
            0xD947378EA7E15F73ULL, 0x626DEA02D5C870B3ULL, 0x4AC76AEBF1763C89ULL, 0x44B0856ED9BC6532ULL
        },
        {
            0x3AEE645E5417D336ULL, 0x4B3368E6A3014E14ULL, 0x9D5065518AD1E15EULL, 0x0E998819B0CBC536ULL, 
            0x5BCBF60B1131E957ULL, 0xD8EFF48CA1C6B553ULL, 0x25FD0FA426FE5418ULL, 0x5CA3D0B441AD6712ULL, 
            0x22AF04FA66D27117ULL, 0xC34D20D42582C843ULL, 0x591F67B4F2C54305ULL, 0x6FB65A0D9D3A84ECULL, 
            0xA39D29F72CF0A7A4ULL, 0xC49C13B2BC62BEB6ULL, 0x10D5F39E2848FF3BULL, 0xD7B0F89EC857F130ULL, 
            0x61BE118BFF604F3EULL, 0x38079EE9A0FC7EF7ULL, 0xB23233C07087A42AULL, 0xDC7E95E2A05E5D65ULL, 
            0xB704833055A60E87ULL, 0x0A1EA8001C42D2B9ULL, 0x4AC913281587B2F9ULL, 0x84B528AA5A6A2969ULL, 
            0xE4897B3EE903A7A3ULL, 0x83CE902F0EDFA5C7ULL, 0xFD9E74F139ABCDC6ULL, 0x4CB786BE83704D3CULL, 
            0x11A60CF311DA0699ULL, 0x3CDFA86CB5C229B6ULL, 0x90EADE907E82B7B6ULL, 0x1B4E88C7138BF4AFULL
        },
        {
            0x2083219B39F84868ULL, 0xFCB3C1FAEC4C912EULL, 0x7CCFD34C28B03AF0ULL, 0x0CBC008558C89FCFULL, 
            0x481F5E6521CCFCC5ULL, 0xEF847B3141A5FD42ULL, 0x1C69687BC1C8C1B0ULL, 0x7AFFD6611F305753ULL, 
            0xCC252BAA88E599ADULL, 0xBDB82E29BF94C47EULL, 0x37DFE54DF6AAB3F7ULL, 0x886D3AE7B15D5A09ULL, 
            0x052F4B87C1FB8698ULL, 0x57586E8F0069ED84ULL, 0xF16E2C611BB2BE02ULL, 0xA9DA8FC824074630ULL, 
            0x3040CA030F6EFB9BULL, 0xD9B919E6899DF2A2ULL, 0xBAB83075097578AEULL, 0x042C6F9BA0AB2712ULL, 
            0x9EAA1B0D11D31DBDULL, 0x28D7ABD6FEC80A36ULL, 0xECAA91FBD4A3A161ULL, 0xA2FACA3B4F674CD6ULL, 
            0x748FE74792F1822EULL, 0x8E0BFBA1AC6D8883ULL, 0xB7090113544038AAULL, 0xD03CB89954C8FB35ULL, 
            0x0B8F190989B0FD9DULL, 0x65A5EE9764A2B81BULL, 0xAEF95942BBC7C5EFULL, 0x007ABD1B709471CCULL
        }
    },
    {
        {
            0x7A59E1731252CE42ULL, 0x11F3057BBCFC5D4FULL, 0xC4B16817FECAA899ULL, 0x9A781D24A155B5F6ULL, 
            0xCE22FA5791BD292FULL, 0xB867F49CCA677861ULL, 0x522B63E00C6CA564ULL, 0x4092EC9EF56ADF1EULL, 
            0xD7C7D9544CB0058BULL, 0xFA375C247005104CULL, 0xC1DA01C6C627A645ULL, 0x6E06E8B55B84B3C4ULL, 
            0xE41EBFBE71EDA110ULL, 0x53BB9546B09B770AULL, 0xF5EAC6F224DF1A9FULL, 0x725E01929B2ECD27ULL, 
            0xA30B0850DCBED406ULL, 0x1555D580B1F358F5ULL, 0x3A6606936C46C3C9ULL, 0x1AFB93990DA66BD3ULL, 
            0x3C8557CB09CCC86FULL, 0x3F7B9092C36B0EE1ULL, 0x793C8EB24B029E9CULL, 0x30D27B57B45D3DF2ULL, 
            0xB5F37CEEB36AF7C6ULL, 0x7B425AF66D8FBDC1ULL, 0xA083EA1CA1BABF8FULL, 0x8F903D5064A044BBULL, 
            0x12E1E1A97456E1CEULL, 0xD1E91BFC97B8F3CAULL, 0x76ED9ACA7E58D30DULL, 0xBF78F7F5EFC61CB6ULL
        },
        {
            0xA2511C8F4454F634ULL, 0x01FAD70247BEAD58ULL, 0x7362B41A0C7EC715ULL, 0x8B628A68E2142178ULL, 
            0x2A239654DA203166ULL, 0x0153BCC018A9492CULL, 0x40086068972C4133ULL, 0xA199FEE565DC8778ULL, 
            0xFFFE3BBF4089328FULL, 0x1F7D4E0ED45ED9BBULL, 0x5D5EF7E1828C0358ULL, 0x418C24C348FD19DFULL, 
            0x251CA60434A59401ULL, 0x4BF6C9335069D044ULL, 0x3972942C91947800ULL, 0x68D1E2468E16C4C7ULL, 
            0xA814A874AF78BCE7ULL, 0xEC606A9A5BDCD1BFULL, 0xED62FD23A6486B00ULL, 0xE5AF6A12B4F46583ULL, 
            0xEA7590AA4BA9FC28ULL, 0xE3856CA4C93FE4C8ULL, 0xD3EE436379753661ULL, 0x292A4CAA4052555DULL, 
            0xECD0439057A43B7BULL, 0xC0452BF0B9A72A35ULL, 0x2A8791900A6B36CCULL, 0xDFBCEAF46C2E1DE1ULL, 
            0x0455C57376AC3E8CULL, 0xA44F3BD9F167D8E0ULL, 0x4686EFBAA3FC68E3ULL, 0x9C23379D6FD4F5CDULL
        },
        {
            0xA0B3CAEB941D0259ULL, 0x204C195E144CDFB3ULL, 0xC14F56AA07B52464ULL, 0xF7D99C6FB381375EULL, 
            0xD007F34A84253EADULL, 0x9AAA17C4F8C71291ULL, 0x2D8FE79925ADB5A8ULL, 0x72AF7E206E1F0502ULL, 
            0x6A2B9894D877BFA8ULL, 0x0F96AFC9D625904AULL, 0x7E68BD48FFBC32EFULL, 0x03CFB8E2E316396BULL, 
            0x17431D5E28C1A299ULL, 0x1A39420E7EBC0FA3ULL, 0xE8023C84D7A30317ULL, 0x03F6135410BAA4B4ULL, 
            0xBD34211B4F8F67FEULL, 0x7BDFFE40E0A3ECC1ULL, 0x98BACDA56C879AB0ULL, 0x9E8502D94880D9A7ULL, 
            0x9A3C72A6D5038CDEULL, 0x137A265F71D3470FULL, 0x1B4226D7829C8D7AULL, 0xBF255F3C119B4645ULL, 
            0x1611CCD71C4D759EULL, 0x9A502D3C731E3E92ULL, 0x2A323251B99C9DD8ULL, 0x9BE39FAF773D1181ULL, 
            0x3FE59F367D95B7A0ULL, 0x6F186D75D9323088ULL, 0x6ED126E4920806F7ULL, 0x178F0018D5C5D201ULL
        },
        {
            0x75AD7FE5B95C1405ULL, 0x832677C676269935ULL, 0x79C17EE10DF2B04DULL, 0xD31B175965A4E33BULL, 
            0x52200E44D4C14E5AULL, 0xB0FE5304E755E9A2ULL, 0x1D3DA6F705C3D96BULL, 0x49D140800F21FCC9ULL, 
            0xE7EF857918242FB1ULL, 0x9A69616926C8691AULL, 0x582D1C9E1ADD08DBULL, 0x8EA7BCF600F6474CULL, 
            0xE566F426A29A669DULL, 0x64CFB584EBE25DD3ULL, 0x4842AF04511132BBULL, 0x14A1A8D301D51607ULL, 
            0x3E233F831FB11A6EULL, 0xD9FAA44D28EA0F6FULL, 0x7C42C525D1FFEBA3ULL, 0x8CA726F7A5468998ULL, 
            0x350D91CFBEAB561EULL, 0x57914493C1B73648ULL, 0xA8641B097AA3169BULL, 0xBC363F56F7EEF1FCULL, 
            0xE7BBB515BD7C977FULL, 0xFF6A68EB288496C0ULL, 0xC623506C17F9A8B9ULL, 0xD0AA561AF8C35C1DULL, 
            0xD4F399D2E592C0F4ULL, 0xB60F64EBE717411BULL, 0x20D9304D20E911D9ULL, 0x6A7084F51F9327AEULL
        },
        {
            0xD2DB85C69C8A4B5AULL, 0xF85653D51F6862C0ULL, 0xB9225AF0F613E6BDULL, 0x308897705DA000D3ULL, 
            0xB8AAF64146D6DFDCULL, 0x9EDFA9D52ECDBDCAULL, 0xB71CF56F7191C97AULL, 0xD4EEC2C2EFB20744ULL, 
            0xD374599D1D0FA626ULL, 0xEC44C171346465BEULL, 0x5279FB7BEDD21FE2ULL, 0xD5F32CAA2EA76B84ULL, 
            0x71540EDD9BB570A8ULL, 0x44B040D97D75741EULL, 0xD10DC31B7CDA5EC4ULL, 0x71E3C38C6BD01916ULL, 
            0x5FEAA66E2D98EC14ULL, 0x8EE907F5A5B2FFC7ULL, 0x5D16EB57F3E010F2ULL, 0x7C729F1505EFCEA1ULL, 
            0xCD6F92BD274CB890ULL, 0x1F156599F77BD823ULL, 0xAA9ED405A8A85632ULL, 0x236625A43887D29EULL, 
            0x00DBEAEBFCB8D64AULL, 0x47B75B1C9EA26F2DULL, 0x2BEE10FE4EC4DDA5ULL, 0x631FFD5D86713E6CULL, 
            0xD354B7B2C2CEFD1DULL, 0xE64D08CCE3B5F388ULL, 0xFA663E7AF28984CAULL, 0xA5598DCC0F0FBCB9ULL
        },
        {
            0x8A90FD00D78798B6ULL, 0x7DAC773200C5075BULL, 0x7A313E6FB11CBA4FULL, 0xDDCC000843D02832ULL, 
            0xCD6C520982AB8FD9ULL, 0x1F020E364B7D5DB6ULL, 0xBF4300168824F4DBULL, 0xD0CBF07935B1D884ULL, 
            0x0518362057BCEB1CULL, 0x8E92146E59AF7928ULL, 0xE8C3C0562C916340ULL, 0x26AEB3B40ACAD7F1ULL, 
            0xC5EEF6CE6CABEB6FULL, 0x49E3EEDEC03B298AULL, 0x538D78E67AD160BBULL, 0xC21E8B5D4742EBAAULL, 
            0x3628F4E7249BEE12ULL, 0x4880A38800ADF89AULL, 0x0B5D26936597D485ULL, 0xFF96C1E1A18D7CEFULL, 
            0xCB88EC749B7620AFULL, 0xBA3147807DAD507DULL, 0x770887A488703188ULL, 0xF25F73458E73864DULL, 
            0x7DE06051C39A61A8ULL, 0x18CF2790255052AEULL, 0x8760B6EE7FC695FDULL, 0x2B05CBAAB0DCB869ULL, 
            0xBDBA81C84D553992ULL, 0x6313ED577342F12CULL, 0xDF6A0E1F09A7E9C1ULL, 0xA4682C886D22AED6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseGConstants = {
    0x8E080192AA9C4696ULL,
    0xDEE92E31171C8A1BULL,
    0x7538C9C9C89DC8C1ULL,
    0x8E080192AA9C4696ULL,
    0xDEE92E31171C8A1BULL,
    0x7538C9C9C89DC8C1ULL,
    0x5F6A29B3D3319371ULL,
    0x2D4FE2371FC1A250ULL,
    0x6E,
    0xDE,
    0xB1,
    0x84,
    0xD3,
    0x49,
    0xF7,
    0x30
};

const TwistDomainSaltSet TwistExpander_Castor::kPhaseHSalts = {
    {
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
            0xA144543B0CBD5F19ULL, 0x34ABF337B0EE1D3FULL, 0x30453E200FAC5D59ULL, 0x18FE294D4A20FF6BULL, 
            0x424138FD1564FF2CULL, 0x8495CD5303CE82B0ULL, 0x747EA53A7949AD19ULL, 0xF9A8798EBD4BD365ULL, 
            0x4817C32BD2E102BCULL, 0x43A845C6C0B4F091ULL, 0x2C6F92AF56BF3132ULL, 0x6053D87ECBCA33B0ULL, 
            0xBD66EBA7661239C9ULL, 0x0964C24889DF1A76ULL, 0xDE51B806C31FB7EBULL, 0x71868B631B11ED74ULL, 
            0xDE3C9D085384BC0AULL, 0x041A1E8356723B7DULL, 0x9ABC781EBEBE7C9FULL, 0x58B29C1078694C6CULL, 
            0x0B0DDF031BA9EB1DULL, 0x1087826DD1948796ULL, 0x933A8B21AFE75436ULL, 0x737569A9EE7327DDULL, 
            0x0B22A994EFBF0106ULL, 0x813B56C9761F9185ULL, 0xDDE390476FA59997ULL, 0xB1B848C09BBFBCFEULL, 
            0xA9FC9EF03A7CEF55ULL, 0x993A6E6DAE530F49ULL, 0xB942826D431C3CBCULL, 0xFDE842079134BF53ULL
        },
        {
            0x73C0492E3FE1838DULL, 0x6A2D8892D1B541A8ULL, 0xD7C9FC50823D60EBULL, 0xB274DBBD4F2E89B7ULL, 
            0x080D15C29460DE33ULL, 0x7D3FB7866EDB0FDEULL, 0x16C71F0E41C3E9F7ULL, 0x1FE0D00D4D96AFA5ULL, 
            0x2F27832C1D00D629ULL, 0x72F1DCF98032BE80ULL, 0x2F5946F19180147DULL, 0xA3F55A7A8172436EULL, 
            0x9AB280024F72C4EEULL, 0x4CB4358CBFF6751AULL, 0x77A11D94C32042AFULL, 0xA933EE3E0C69D1CAULL, 
            0xE133D93C33068FD9ULL, 0x89604BE412D6BC8CULL, 0x764508B699A01BD2ULL, 0xB329B0E74CD42CBBULL, 
            0x8A6B36535E6360D8ULL, 0x0A75BC15913044FFULL, 0xC468DC878E2F5FBFULL, 0xF1A262727311F629ULL, 
            0x48747A75A848E627ULL, 0x785581CA115F56BCULL, 0x4518AE3298F8E133ULL, 0xB0415E5E6C17AEEFULL, 
            0x697432217999A435ULL, 0x3A0D6B4A204EC716ULL, 0xADCFE3702A90176CULL, 0xD5B6A5B716F383B9ULL
        },
        {
            0x16E750F35652AB66ULL, 0xC1D50E8009471744ULL, 0xA56F3173309D21C3ULL, 0xB3606E88C0716F60ULL, 
            0x5D3A8432E0A07ED5ULL, 0xC19159C17E7D32C4ULL, 0x579E85E757C06893ULL, 0x45AAB4247E3C206AULL, 
            0x9507CFB1453797F6ULL, 0xD154894A36059ADEULL, 0x64189DA365D151DBULL, 0x4FEC730691467C79ULL, 
            0xD471D8F8E6B713D7ULL, 0x95B551782EDE0D27ULL, 0x8BC005FB16BC3B78ULL, 0x11D9B4FCF86C7640ULL, 
            0xBEC7AFC4B44AB1E0ULL, 0x91323F5A45635FC9ULL, 0x0F50276CA0EAC463ULL, 0x003D30D102F16AAEULL, 
            0x9372C212599BE3AEULL, 0xE56FE4CDCEDEF5DAULL, 0xB84B27663B9D4FF7ULL, 0xEB9FFB9684D49179ULL, 
            0xB970901F3EBFE35DULL, 0xFDF9CF0D4FBB1CD2ULL, 0xBDF1C4852C9AB75FULL, 0x6A724AC922889342ULL, 
            0xC7ED356E978C1727ULL, 0x30B13673F312399DULL, 0x2A04937101721E98ULL, 0x706E92550CACA5E5ULL
        },
        {
            0x1EB855D9F64F8442ULL, 0x63AF685588881753ULL, 0xB5AAEBB9FCCD27A3ULL, 0x2FD44CEE2904CA43ULL, 
            0x1C3073F64B4AB307ULL, 0x76B36595A64EE405ULL, 0xB68092359C9C55C8ULL, 0x2BD126FA0A296A82ULL, 
            0xA7E8E46B62D57DFCULL, 0xCEE69EDF19B0A5FDULL, 0xC83477E8FDDF478FULL, 0x2386BC20EF48C288ULL, 
            0x9A1B10327C5B48BFULL, 0x50DF671275E1B09DULL, 0x5AF04B54C554CEA4ULL, 0xD57795C4A75C0FABULL, 
            0xE4A3CCAA4DD91964ULL, 0xE1FB6FBD2194CCD4ULL, 0xBA4AEDB032A1885BULL, 0x6DF40ECA461D0140ULL, 
            0xB4C6FB042CF8DF16ULL, 0xCFFDB507B2436516ULL, 0xFD44AA96DD9E1279ULL, 0x85E7E7C3047B6E60ULL, 
            0x7395BD6264CB99C7ULL, 0x975CB10D87274771ULL, 0xDF514D0F92F7BB26ULL, 0xDAEC02BE392AF44CULL, 
            0x6C450191DAC8A65BULL, 0x010517A72CBD4AB9ULL, 0xD6F220CE95B83AC0ULL, 0x5FF65C8DEFC775F2ULL
        },
        {
            0xE3C15883CB36AACBULL, 0xA257C253E611BDACULL, 0x6609053BB22F09FBULL, 0x296FAD78FCC835FBULL, 
            0x2755933C254CC689ULL, 0x9DEEF408AE75A250ULL, 0xD7C1AAFA93444845ULL, 0x9154AA5C20855D21ULL, 
            0xCE3ECB52EEAE4FA9ULL, 0x94720F73A8C17D1CULL, 0x3237F2C186CDE43FULL, 0x6895A2EE4BA80EDEULL, 
            0x41D89A64DED23D6BULL, 0xC5AAD03F611C62BCULL, 0xEABDF159C9CC1B96ULL, 0x0E2D2FA689CC4A2BULL, 
            0xD9B9F416B5F04750ULL, 0x640B2500C780DFACULL, 0x71FB8039D1194E29ULL, 0x88296B9E2172C157ULL, 
            0xBAA81F22B530045DULL, 0xBAE081EAAB5DB62EULL, 0x8EF331CD55AA2070ULL, 0x71E2CBB92942DC23ULL, 
            0x32AA31FEE505B634ULL, 0x9FE802A5701F6217ULL, 0xF8747B23A08B02C5ULL, 0x8DEBAFAB47AEDBE6ULL, 
            0x92877264F7219C0BULL, 0x1E4E79DBA985A202ULL, 0x1A3DE392CE2ED41FULL, 0x7A73440B5A48BBB0ULL
        }
    },
    {
        {
            0xFE7135BA0E1DFA9AULL, 0x7548B301DD2A58BAULL, 0x83FEEA0CFE7EEEDFULL, 0x488632AA3D91255FULL, 
            0xFE876DA6265B27B5ULL, 0x764D54C93A22A0AFULL, 0x7BA142AD62D760E3ULL, 0x80B4A4B87B50023BULL, 
            0xD38F832043A49741ULL, 0x0A4C74C8587329F9ULL, 0x7A6A43119070F330ULL, 0x5C81B1625127263DULL, 
            0xC5D09370581223D2ULL, 0x9F9FFC6A1E0E512FULL, 0xC45E41A6FD8E6BBBULL, 0x23694081B228B1ACULL, 
            0xB9F6AA2044C50964ULL, 0xF36040747523889FULL, 0x2FD65E6678858A13ULL, 0x3F2E94F93AD63D5EULL, 
            0xA58BB96B4F318B6BULL, 0xA0592F1C8FE7F404ULL, 0x516F4878929AE416ULL, 0x658892945F23BD64ULL, 
            0xD37F9D828644C2F1ULL, 0xA382CD8AB1A4D5C8ULL, 0x2516A98C9A1516FEULL, 0xE80FC3CAA693C870ULL, 
            0x06D05BECC6874D61ULL, 0x0678E074F41C93B7ULL, 0xE88CD6AD54082DAFULL, 0x7C11C799D28BBA12ULL
        },
        {
            0x6A34821B6C111720ULL, 0x5B0BE7D137526991ULL, 0x0D1DDD571323AAD4ULL, 0x24ADFB5257394C01ULL, 
            0x4705DCEAEE1B5CF6ULL, 0x5C758724470EB531ULL, 0xAF874C4B6AA93292ULL, 0xF3B5B05E8AF7F3B1ULL, 
            0xE5E50C5DE06F4822ULL, 0x464890C0E4AB7605ULL, 0x30F38025182BA653ULL, 0x37CC3F1B4B827C61ULL, 
            0x09CE680DD2520E11ULL, 0xDEE612C63BC81A30ULL, 0xE1A3C261C153A7F8ULL, 0x0679FDAB6277C53FULL, 
            0xC9937383954B5A4BULL, 0x76C0DC557742941AULL, 0xB0485215F968AF8CULL, 0x083384E3453BCE45ULL, 
            0x4CAD298DF1BDAE35ULL, 0xB84A6BCF366B7EF0ULL, 0x12F74E4F7D83EC93ULL, 0xA44419ED6F469AD6ULL, 
            0x41C23573F2CA684BULL, 0x54FDF936201A0866ULL, 0x9BA9EB1CE11660E9ULL, 0x730C09FFD9A7F3B0ULL, 
            0x9CD29BC22123E994ULL, 0x067D0A9744DD0293ULL, 0xDE02D990935BCDAEULL, 0x23F9E921668ECAF6ULL
        },
        {
            0x86EDD7789FB4C2C8ULL, 0xC82C6BF9C91A1B95ULL, 0x5DCAF9920E673FFFULL, 0xF26228550F9905E3ULL, 
            0x75A5B2CF84DFCCABULL, 0x79905B8C6D101A8EULL, 0x70EE39C8AFF00387ULL, 0x301947ABF7C4F920ULL, 
            0xD604974EC402321DULL, 0x114633519A7EADE9ULL, 0x4B9AD7089EEEED62ULL, 0xDB525829629570F3ULL, 
            0x82875CD2762CBFC6ULL, 0x05494E82791D3E1FULL, 0x16F0AEC686ADADDCULL, 0x390E7E515FD7E3DEULL, 
            0xA165DB8E060985E5ULL, 0xEC3C371055D57DDEULL, 0xD9BEA5CC8808AEBAULL, 0x40951E7079BCA3D5ULL, 
            0x96B0F147AF3E7C57ULL, 0x74D1E3CCB627162BULL, 0x3DE6466ABD2743E8ULL, 0x357F85256A512A9DULL, 
            0x525B082892939CADULL, 0xB3A561623C342587ULL, 0xCAB3EF00F78248B4ULL, 0xE8D922871F65F4CCULL, 
            0x05A3489BAD079063ULL, 0xA3AD62729AF77007ULL, 0x2CB652B3C5FD03D3ULL, 0x074F198FE10C0D58ULL
        },
        {
            0x94F38F215A8792EEULL, 0xBC5888C6821F501EULL, 0xDAC591A485C70934ULL, 0x9CE42D64FC70AD0EULL, 
            0x724E5E63EDF9FB3AULL, 0x549349CE644515C0ULL, 0x9B77B2EB99FAE9ACULL, 0x7A260E4311EDCD86ULL, 
            0x63146B1A83F94572ULL, 0xC105E672A899620AULL, 0x7E658D24290E87C6ULL, 0xB028E4B6378B430CULL, 
            0x56937541FC81B366ULL, 0x3AA8D67C77C6B003ULL, 0xA1A181F38FB6ADA4ULL, 0xF92F2FEB1D03FB5BULL, 
            0xB9171839DB41F4EFULL, 0xBA1FFBAEDB18D733ULL, 0x310632812D0CD8A1ULL, 0x0FAC213B7FC1BA55ULL, 
            0xF72AFB21C8D048F0ULL, 0x4EBC1BD12F6E3D6BULL, 0xF2B229974B8C274EULL, 0xF5DD81C6F591824AULL, 
            0x7CF261FB19BA7619ULL, 0x3DF13DAD9E286743ULL, 0x5BAF92FBEDADAF1FULL, 0xF567BED77F1C6B37ULL, 
            0xC7C9DF1CF649EFFAULL, 0x0532F006595B2537ULL, 0xA50E3A2925E967B0ULL, 0xE27387BC037586DDULL
        },
        {
            0xA0C685F0CA39EAD5ULL, 0x493517AECA58E572ULL, 0xD90D019B22FA46F6ULL, 0x880D314D924C044FULL, 
            0x0B674A99B813CBDFULL, 0x85BF1BA80E26FE26ULL, 0xAA16853925A426FFULL, 0xA890948343DDD1D9ULL, 
            0x0B41BC4CFF60CECFULL, 0x5F87D13B63EE85C6ULL, 0x6EC7A1646701955EULL, 0xF8A65A28C27C1768ULL, 
            0x9D0096D5A147428DULL, 0xD4744FFCBF9C22D3ULL, 0x5CCB0218439E485CULL, 0xF12A8DB281A53188ULL, 
            0x7BC13FE5853E7F3DULL, 0x89F42B00AD82ED05ULL, 0x85F5C2AC5B9DFA19ULL, 0x12F2670A4BE6EC5BULL, 
            0xE7A173661435CBCBULL, 0x978E666171CEF43AULL, 0x58266585ADD0DD4DULL, 0xF88B5FBDE6327D93ULL, 
            0x06A165009443A4B9ULL, 0x51F28E8E81235D70ULL, 0xDCCC7BF8B476D180ULL, 0x8AFAB5F3FAFA85E1ULL, 
            0xD96B064344853E87ULL, 0xADBB9861E4D523C7ULL, 0x84A8EC1D047EC791ULL, 0x64B705E182A9BD7CULL
        },
        {
            0x11EEEA295A1871DDULL, 0x1E661BCF52FFE06EULL, 0x0284CB87B22011D5ULL, 0x6F39C5660CB4E2DAULL, 
            0xBB690F7A8CAFF082ULL, 0x4BD0B1699B9E9E71ULL, 0xDC1E67D88428F31AULL, 0xFAB36FFC0E3A96CBULL, 
            0xB6FE3BBF3855919BULL, 0x6B3591C05F5C909BULL, 0x27E96F94B69C4E60ULL, 0xFB87245ED599C3A4ULL, 
            0x11C273CC394247D7ULL, 0x7D5B48F7840CFF02ULL, 0x8AF65CDB825D2AA5ULL, 0x9BDDF5BF5025A846ULL, 
            0xC5F2664134AB8C27ULL, 0x93761EF30A64C4CBULL, 0x365939F6D04B0BC0ULL, 0xFCFFB9295EBC0250ULL, 
            0x6FDD0F9D7936429EULL, 0x55C6FC4631E3ACAFULL, 0x63485008A78FE89EULL, 0xF113C28995D07C48ULL, 
            0x6E5FF0221E4EA94CULL, 0xB9068C7DA67193B7ULL, 0xCCE0D69FB716D717ULL, 0xD02D71770C6E7983ULL, 
            0x8D59D63BD60F66F4ULL, 0xC8795D30FC4D6B34ULL, 0xB279749403F03A44ULL, 0xBB1A95C4CBEE1C31ULL
        }
    },
    {
        {
            0x005FD4088831D6F2ULL, 0x59784B2BFED72351ULL, 0x7227385E890D0DDBULL, 0x5D0DD3ABAF2ECD25ULL, 
            0xE6C0FA4E9B108B90ULL, 0x0468A2CA0962C0CEULL, 0x55C1A85102E34EF9ULL, 0x65755CD64A638125ULL, 
            0x5649287C57B9FDCEULL, 0x3F4A3663770BB0F5ULL, 0xD82664886D49AA93ULL, 0x03BBB64E244EB4E6ULL, 
            0x2A4D0C62106DFA3BULL, 0x69E43BDFF7870D55ULL, 0x57571EB502FF1ACFULL, 0xFBA2CAA64F11C751ULL, 
            0x251CB4793E564A8AULL, 0xB4274D6F8A601CB9ULL, 0x520D556A4A72F112ULL, 0x4B127E789485558DULL, 
            0x87DF3806E04A4F6AULL, 0xE34298AFC787B9C8ULL, 0x6E54744B419DCE32ULL, 0xF7DD8EDE6EA2A188ULL, 
            0x3F381EDF8FA7F757ULL, 0xB57C00435755B8DAULL, 0x57525043F53AEDD1ULL, 0x2713AC6DD6819489ULL, 
            0x9D118CC15DDEF56BULL, 0x5D70F6258AE1BEC3ULL, 0x79757E7D7BDE51ADULL, 0x87D5938F6A8681CBULL
        },
        {
            0x537E30A4EC94AE7AULL, 0x16A17CD004E3FD63ULL, 0xE8FD2408A7751A8BULL, 0x72A7AC75E4850455ULL, 
            0x1D11CF6A30D46D6DULL, 0xCDAE03134C905640ULL, 0x48FE2B3F3AC1930EULL, 0x99B749508AF83FC3ULL, 
            0x5730D1639612C72BULL, 0xF804905C65E18E42ULL, 0xE5813655F76A4D96ULL, 0x532CCF63EF85449AULL, 
            0xF162096BA658F64FULL, 0xFBE57C131E047E86ULL, 0x1905F36F46AE0437ULL, 0x83CFC8B8A6E28A62ULL, 
            0x5CA524545A8E36D8ULL, 0x396F9BE5DF85886DULL, 0xD85642153AD3C0DEULL, 0x65452442E29F86D2ULL, 
            0xB22F229583FC417DULL, 0xF319C7CF94696E4AULL, 0x7FCFA5528DA81342ULL, 0xCDD30220ED4E36DAULL, 
            0xFFF6FABD2C43E151ULL, 0x07013BF8214C47FCULL, 0x9E7D95E6CB10BF70ULL, 0x490A6F8206346B4EULL, 
            0x613A7AF0FA4AFE71ULL, 0x51843EACBDF6D27CULL, 0x0C230CDD00F73967ULL, 0x895A00C7CD0B4451ULL
        },
        {
            0x98AB5C874337B5C3ULL, 0x7EB6121C9D9E54AAULL, 0xCA53D90AC41236CCULL, 0x6468904B8D310637ULL, 
            0xBC8DA00687DABBAAULL, 0x999A70A5F5545E80ULL, 0x837389AE2DF709CAULL, 0xBE02B009C17246C2ULL, 
            0x3465E723E5B70A64ULL, 0x46499ED3E286E9FFULL, 0x2A9BA90044A707B5ULL, 0x68F6C1FB8BA088D7ULL, 
            0x450D96A06316A011ULL, 0x3285FE772B29DCC6ULL, 0x2D45C4D103A55D69ULL, 0xA8D3455103B74291ULL, 
            0xDF251D6131A77523ULL, 0x89394AC16CBC1FF1ULL, 0x59819391B9D90850ULL, 0xFEC71598F1206264ULL, 
            0xF5A5E624B7EB446DULL, 0x25BF251CBBA4C748ULL, 0x645DF6A1119FE074ULL, 0x68B61697F18B9AAFULL, 
            0x5EB4D8A620E06596ULL, 0x88EE9FC8B4871316ULL, 0x3C01CE15C3184EA3ULL, 0x2681CDA113CCA467ULL, 
            0xCAAB0D736F683CD8ULL, 0x7D8543735E9B99BCULL, 0x5C9D86E5ADFAF28AULL, 0x800E7645B33599B9ULL
        },
        {
            0x2AD910241BB94C7BULL, 0x39D08672CD030F6CULL, 0x0CA8F336265A5F4EULL, 0x86A32A2364A1BD22ULL, 
            0x51234524F079C288ULL, 0x18E2FAAB044A7A59ULL, 0x4087785AE059674AULL, 0xC6C70C57B0762C62ULL, 
            0x9382F0B89BDEBCC7ULL, 0x1C0C58F5499B2AEBULL, 0x1401633D6F73DDAFULL, 0x7B4AD5D1B7BB7542ULL, 
            0xD6E13C0A8DDC409EULL, 0xE471B6E5DA2DFE9AULL, 0x46321A4CD9A8E083ULL, 0xF7E8B0FC7FAF6352ULL, 
            0xC621EA9713AFD750ULL, 0x525DBAEDDDF6B39AULL, 0xE71EE8FA21AE5D27ULL, 0xD5CC35E95BE68267ULL, 
            0x6B08CB348505B360ULL, 0xA1C8F382DF82173BULL, 0x9A554D6158E33642ULL, 0xB6EEA2C657633D19ULL, 
            0x864076DC51021A28ULL, 0x719BEC767C031FA4ULL, 0x2BF5F21FB618DFFAULL, 0x21B23D7EE51D9DFFULL, 
            0xA862217968647A7AULL, 0xE40E2520D0D6BF48ULL, 0xE99CE2A79F5CD774ULL, 0x08A56442513CFBC0ULL
        },
        {
            0x34A21B22A76643D7ULL, 0x32EE348398E45E6DULL, 0x31A10235B41A1698ULL, 0xEEC9E8C324DCC085ULL, 
            0x5AD828EDAC4340B1ULL, 0x81566A883C3958E2ULL, 0xDEE6AE8B7D38B00DULL, 0xAD2524B4F815DA5AULL, 
            0xEF5CAA272BA51147ULL, 0xBF50667749D10313ULL, 0xDC248DEA294080F2ULL, 0x0BA9EE979EFED9C2ULL, 
            0xEC9F27DCE1E3988AULL, 0x70D6937FFF75EAD0ULL, 0x0ADA11D9A75EF399ULL, 0xE209F5BB61E70B68ULL, 
            0x1FCC5BA4ECFBAA17ULL, 0x4B12AC18194E4000ULL, 0x212EBFAB275B8DB6ULL, 0x49364226FD1E98FFULL, 
            0x44FF502A70E7D284ULL, 0xE2146717405A8BF5ULL, 0xC667018BE5F5EF9FULL, 0x9EB599E60E75354CULL, 
            0xD07F51BE1222375AULL, 0x2591A42BF5425544ULL, 0x09AAD0E668D4BCA5ULL, 0xD2082716D1EED4C4ULL, 
            0x06EDA67FF78DF0C2ULL, 0x2CE4D2FE83065B44ULL, 0x4D136843AF3B8B15ULL, 0x2C0BB45C63B180DCULL
        },
        {
            0x376322D9578E03C7ULL, 0x0B10842B5B360A61ULL, 0x05E1CC95AE0A0498ULL, 0x2F3906F4E34E03BCULL, 
            0x0650DBBFDA028725ULL, 0xF552826285395703ULL, 0x12723F3219EDE328ULL, 0xA4DF0EC874E538C8ULL, 
            0x195873C01706D178ULL, 0x3DE701E818726747ULL, 0xE03B2479762E9944ULL, 0xCB97F78CA9A72068ULL, 
            0x98F0759A24316FE0ULL, 0x0ED117587A96E773ULL, 0x8DBA4E255AC49C8CULL, 0xA6F2C381DA8E8EA0ULL, 
            0xE8F020DBD57755D1ULL, 0x4185FF30D353D2F3ULL, 0x71ACDA47E932E20BULL, 0xC1181AEAAD39E1C5ULL, 
            0xFD8F861C5E33EF97ULL, 0xCE71B2DEAB67BDA6ULL, 0x2675C12C965771A6ULL, 0x83B81A42ACA227E8ULL, 
            0xC81A8DE0279B6280ULL, 0xB4E288687E2DEB1EULL, 0xBB20236E4B5A01A2ULL, 0x1F9D4A88B8F477EDULL, 
            0x494E86A66B6385E4ULL, 0x7CA140E1C7062C19ULL, 0x22BF97D0CC368FA0ULL, 0x6DBAD3572959F730ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Castor::kPhaseHConstants = {
    0x3B2AADBFC54AF2E3ULL,
    0xDA39D71FBD998960ULL,
    0xDE01AF6234CB7760ULL,
    0x3B2AADBFC54AF2E3ULL,
    0xDA39D71FBD998960ULL,
    0xDE01AF6234CB7760ULL,
    0xE32204B9E2D22289ULL,
    0x0F3452DB26470BEDULL,
    0x8D,
    0x01,
    0xC2,
    0xC8,
    0x7B,
    0xD8,
    0x5C,
    0xE9
};

