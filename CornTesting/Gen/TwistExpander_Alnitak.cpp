#include "TwistExpander_Alnitak.hpp"
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

TwistExpander_Alnitak::TwistExpander_Alnitak()
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

void TwistExpander_Alnitak::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE86D6BE0846A35FCULL; std::uint64_t aIngress = 0xE2F0619F1F9D940BULL; std::uint64_t aCarry = 0xCA5DF66226FCA1B2ULL;

    std::uint64_t aWandererA = 0x914CC39749B061DCULL; std::uint64_t aWandererB = 0xA099D15D01B450C6ULL; std::uint64_t aWandererC = 0xD332D866B9B6A056ULL; std::uint64_t aWandererD = 0xA4352474267D6A90ULL;
    std::uint64_t aWandererE = 0xC48418A1BC7BC4ECULL; std::uint64_t aWandererF = 0xD7420236545FAF74ULL; std::uint64_t aWandererG = 0x82B4E182AB93BD4DULL; std::uint64_t aWandererH = 0xFE595D4B199E1323ULL;
    std::uint64_t aWandererI = 0xD11CE8820552BC43ULL; std::uint64_t aWandererJ = 0xA96D21BD444F678BULL; std::uint64_t aWandererK = 0xF4CC301A7157A83DULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17023026311092083465U;
        aCarry = 9927061471856697230U;
        aWandererA = 9307290131083029673U;
        aWandererB = 13009336885601671026U;
        aWandererC = 17135051071022226770U;
        aWandererD = 9678490185793069067U;
        aWandererE = 16336825230781372493U;
        aWandererF = 11621105486288336275U;
        aWandererG = 16508136382587149050U;
        aWandererH = 13819667927810407336U;
        aWandererI = 12805814640468374693U;
        aWandererJ = 10732632515859631258U;
        aWandererK = 14284079472654073428U;
    TwistExpander_Alnitak_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alnitak::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xEE3FF1868166C9A6ULL; std::uint64_t aIngress = 0xF32A86BB0CCA8E40ULL; std::uint64_t aCarry = 0xA0EA3934F819D4C6ULL;

    std::uint64_t aWandererA = 0xAC1CF8B56279F21AULL; std::uint64_t aWandererB = 0xE13E8A35563FAB20ULL; std::uint64_t aWandererC = 0xE2B2D9495456B785ULL; std::uint64_t aWandererD = 0xE9ED580BAC47CE3DULL;
    std::uint64_t aWandererE = 0x831A5DF08EA2DE92ULL; std::uint64_t aWandererF = 0xA528780CEFB6ACD4ULL; std::uint64_t aWandererG = 0x894F45CFF7BC04B7ULL; std::uint64_t aWandererH = 0xA7A5D6FB5078EC96ULL;
    std::uint64_t aWandererI = 0xC8070D1D8B718679ULL; std::uint64_t aWandererJ = 0xEBB5F9979564EB16ULL; std::uint64_t aWandererK = 0xBE72436A37ADC933ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17172997940980569093U;
        aCarry = 9848249467765636088U;
        aWandererA = 13517087739022488400U;
        aWandererB = 12014150004020771106U;
        aWandererC = 14759544199884973647U;
        aWandererD = 17766471155680293637U;
        aWandererE = 10630787422831442386U;
        aWandererF = 12398844938280436322U;
        aWandererG = 12544148400487611796U;
        aWandererH = 10220331098196520967U;
        aWandererI = 12998298718182530495U;
        aWandererJ = 11484509092158024757U;
        aWandererK = 16349494946353231799U;
    TwistExpander_Alnitak_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alnitak::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xFF4DEB1D51F336DFULL;
    std::uint64_t aIngress = 0xAB808C92FC3E7DC4ULL;
    std::uint64_t aCarry = 0xEF32D8B9B5FAA89BULL;

    std::uint64_t aWandererA = 0xDA88EA72A16D812DULL;
    std::uint64_t aWandererB = 0x8EE629856104D269ULL;
    std::uint64_t aWandererC = 0xE418700BCDC465CDULL;
    std::uint64_t aWandererD = 0x8E09E4A793A4EC1CULL;
    std::uint64_t aWandererE = 0xDB8EA9EBD781D9D5ULL;
    std::uint64_t aWandererF = 0xE5AC4A3B9106B057ULL;
    std::uint64_t aWandererG = 0xD152E674AC55B4F2ULL;
    std::uint64_t aWandererH = 0xE564A10E45304356ULL;
    std::uint64_t aWandererI = 0x8DE3571BFE281AA9ULL;
    std::uint64_t aWandererJ = 0xF5F6AB1249965DE9ULL;
    std::uint64_t aWandererK = 0x9EF31A5DFB62FBA7ULL;

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
    TwistExpander_Alnitak_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alnitak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 6 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1924 / 1984 (96.98%)
// Total distance from earlier candidates: 9668
void TwistExpander_Alnitak::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 237U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1902U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1679U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 460U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1899U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1203U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1881U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1900U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 742U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1283U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1629U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 66U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 803U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 184U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 81U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1359U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 538U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1261U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 709U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 425U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 458U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 836U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 839U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 674U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1710U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1845U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1154U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1295U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 810U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1309U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 732U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 660U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 329U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 960U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1450U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 808U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 777U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1979U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1221U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 160U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 578U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1270U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1635U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 740U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 374U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 944U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 951U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1795U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 728U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 981U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 819U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 377U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1942U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1930U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1756U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 378U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 964U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 929U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1174U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 664U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1691U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 522U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1076U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 451U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 208U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1253U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 942U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 697U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 150U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2037U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1773U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1757U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 181U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 900U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 872U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1977U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1746U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 794U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 102U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1926U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1248U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1218U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 492U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 924U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 745U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 282U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 122U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 49U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 790U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 32U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1092U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 465U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1068U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 756U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1311U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 501U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1576U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 400U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1009U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 801U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1202U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2026U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1928U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1764U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 955U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1310U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 990U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 828U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 603U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1627U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 802U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1534U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1167U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2015U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1729U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1975U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 143U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 304U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1035U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 636U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 920U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 605U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1713U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1308U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 368U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 48U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1696U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1095U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Alnitak::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xCE8958FA2C46C4BDULL; std::uint64_t aIngress = 0x8A64EDCF7008A706ULL; std::uint64_t aCarry = 0xED10CBB60DB40561ULL;

    std::uint64_t aWandererA = 0xD4D7DD40C81A9132ULL; std::uint64_t aWandererB = 0xD60F10D1BDD0385CULL; std::uint64_t aWandererC = 0xE6F54E07AA948D38ULL; std::uint64_t aWandererD = 0xBAE0C5D569EA9565ULL;
    std::uint64_t aWandererE = 0xAF85E6C188F40C42ULL; std::uint64_t aWandererF = 0xDE5751D461F84975ULL; std::uint64_t aWandererG = 0xF56DDEDB25177ADEULL; std::uint64_t aWandererH = 0xCC32CDA0998637B7ULL;
    std::uint64_t aWandererI = 0x8D0D0B2AD49F34CAULL; std::uint64_t aWandererJ = 0xCA87F772F23BB8C6ULL; std::uint64_t aWandererK = 0xB336512F7F4E2394ULL;

    // [seed]
        aPrevious = 14125315338273135683U;
        aCarry = 16451498862054412193U;
        aWandererA = 10507491133519716326U;
        aWandererB = 9627241997700229627U;
        aWandererC = 17739863498541254050U;
        aWandererD = 12446567049080873264U;
        aWandererE = 13273795668966491394U;
        aWandererF = 11142731667452980677U;
        aWandererG = 16445383985773402161U;
        aWandererH = 16613371074694265535U;
        aWandererI = 16658090777601763418U;
        aWandererJ = 16090324199277789768U;
        aWandererK = 13990162156736893702U;
    TwistExpander_Alnitak_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Alnitak_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Alnitak_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alnitak_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 6 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2850; nearest pair: 521 / 674
void TwistExpander_Alnitak::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3634U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4097U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 208U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6186U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2431U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5566U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7779U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7117U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2707U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 803U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1874U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2383U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6844U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4772U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8103U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 907U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 13U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 247U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1833U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1062U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1304U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1013U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1081U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2028U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1844U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 227U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1594U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 577U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 625U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1845U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1554U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 529U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 180U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 122U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 622U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1279U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 6 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 2854; nearest pair: 523 / 674
void TwistExpander_Alnitak::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5903U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5231U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5002U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7584U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6072U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5565U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8079U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3295U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1547U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1098U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2767U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6547U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7270U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6573U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5315U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7556U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 785U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 326U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1975U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 763U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 95U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 72U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1276U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 51U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1663U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 579U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 578U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 23U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 723U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1971U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 279U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 736U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 828U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 31U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 322U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1626U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseASalts = {
    {
        {
            0xF9424B9926915DDFULL, 0xB371835E9FF50720ULL, 0xC1A8B70CF6B4EAA7ULL, 0xDCEF6C7581D27DC5ULL, 
            0xF8C5B714D0C0B795ULL, 0x4C1D9D962AB08785ULL, 0x87C651A6F148213AULL, 0x117F92087A65E16BULL, 
            0xCF3A2B5BFBD7DD01ULL, 0x873A19854119DB26ULL, 0x76B098D12614DE0EULL, 0xC85D520370488DAFULL, 
            0xDD44173FBEE1567CULL, 0xF7692DCA70DBC00CULL, 0x14EBD0904671CFA2ULL, 0xD337C98BB28FFA06ULL, 
            0x79E3F60E06226872ULL, 0x7DF00306A4308D17ULL, 0x489023ECE0245CEAULL, 0xD990E599EDA8AC9EULL, 
            0x2E7B635D81BD3B37ULL, 0x6D029D540C55CF29ULL, 0xF4A174D9CC3CD111ULL, 0x7D71C710EC25A2F2ULL, 
            0x151271C5EFEEF6F0ULL, 0x4D06C738151AFB97ULL, 0xEF4C551F0F8706C7ULL, 0xD2779B32D2A4689CULL, 
            0x43E4FE6D42571202ULL, 0x58071DED781ECEB1ULL, 0xC2632941BC5DBBFDULL, 0xB16F7EC2BDC92D46ULL
        },
        {
            0x097C17DBCD6584E3ULL, 0xE613DEBDFC8C87B3ULL, 0x10B0BB75AC564BCAULL, 0x33C2E12AABD852BDULL, 
            0x11490B4D33BE1314ULL, 0x4F3D7FD2759830ECULL, 0x4AA4A87ADFBC44ECULL, 0x2EE8AE38247F0CE0ULL, 
            0x9BB22E4D7BA6C021ULL, 0x26F60CBC97609B36ULL, 0x521B69220E8D3CF6ULL, 0xCF60B1EEFA27E363ULL, 
            0x398BF7B605A41C3FULL, 0xF99E80574486DFDCULL, 0x26399C12C8775155ULL, 0xA219EAB20F98B142ULL, 
            0x7E8F432939B08D24ULL, 0xAF60A76D148CCA8BULL, 0x5129E406C6C3535EULL, 0xA09D79D93675C902ULL, 
            0xC62DC1763D535ABBULL, 0xA8616872EB15BD0FULL, 0xD5DCB9AB39E47090ULL, 0x662484AA17133FEDULL, 
            0x1AA5426AC98CBF5CULL, 0x66154BAC06C32A5FULL, 0x3D33C72350F59148ULL, 0x43C6EB183B4AFF43ULL, 
            0x6C74FE8A93468929ULL, 0xBE7A56547883D604ULL, 0x632796ED4369D936ULL, 0xE5E42481F1F3DB6EULL
        },
        {
            0x702791A9FF80300BULL, 0x207EF66113CC7FC2ULL, 0x9E3031925D7DA811ULL, 0x3FCF3FCAA0014D90ULL, 
            0xECC4CAAF7C0D6B15ULL, 0xBD5B5E92E11DD1AAULL, 0xB705527824DF764DULL, 0x0EA403EA093FE69EULL, 
            0xBE821CC80D5F2C4EULL, 0xA707A141D6ED43F0ULL, 0x07D3D3D9F932125BULL, 0xD84439D9674D6493ULL, 
            0xCBC7621025246831ULL, 0xDB9C5AC24BB74EDEULL, 0x38D7DFADB0591B8BULL, 0xD649245014A2A30EULL, 
            0x1F0BD0E34BDE9A8BULL, 0x816ED1AD3D550CFFULL, 0xE6B22ACBFA6663EBULL, 0xDE7732BF639782FAULL, 
            0x431E3753CB29F9DBULL, 0x3AB9F93A15E18793ULL, 0xBA9C36A1CCD34C2DULL, 0x683FC7AB0ED2408FULL, 
            0x9AFCABEA94F5E008ULL, 0x59D1D82A65A323F8ULL, 0x3F9C7D36865D4F67ULL, 0x0A2B4E29929C400CULL, 
            0xD8AFA1CC689298D5ULL, 0x70A7058D138734D0ULL, 0xB55E3DA279D99517ULL, 0x8E9872F327A0A79DULL
        },
        {
            0x03FB8F04C54F908EULL, 0x33E58F9E19DD1381ULL, 0x6379412AE4F2BA7EULL, 0xD650225DD0FB1563ULL, 
            0x0DD8D2296F5E47DBULL, 0x009E6B87288125DFULL, 0x9B58AC264DA9C85EULL, 0x58351F9E9A0C7113ULL, 
            0xFDF7C89742980244ULL, 0x3BDC21C043FA67CAULL, 0x2EAC75335570DB26ULL, 0x9C0391E95B8AE4A9ULL, 
            0x470510FD88A64F01ULL, 0xECD4DA8C9E6B6E1DULL, 0x2414911475F6C9ADULL, 0x79D1C5C7FD860390ULL, 
            0x977887A5379B4A5FULL, 0x1BDCA88365977E93ULL, 0x58578F71BF44A2BBULL, 0xD5FA5833FEAD8F22ULL, 
            0x25B809719499E5BDULL, 0x58D25CC086BAADB9ULL, 0x5F79EAF9C7D654A5ULL, 0x8EBAA6DDA27CE77AULL, 
            0x712EE7810C2E9CF2ULL, 0xDB178B706C1874EBULL, 0x89EE858087C1438FULL, 0xDA818AB87B441A3FULL, 
            0xD364DE10ED4E8126ULL, 0x7EFC3DCD4284BD0CULL, 0x9FB486286F2CA068ULL, 0xC2EF3D50B7D6984CULL
        },
        {
            0x701548EDF486F405ULL, 0x0E97807AFA838AF9ULL, 0x931712C26AE6E187ULL, 0x941FCCE648EDBB97ULL, 
            0xAE69F44695D3F479ULL, 0x8327D172D804423EULL, 0xC4C09D876F5D9B4BULL, 0xCFA6BDAF2A9BA584ULL, 
            0xCD884F1A9A6CE8E6ULL, 0x3288B776CAE79633ULL, 0x48F71E9DC3652E2CULL, 0x5AC10A46B67D9EA7ULL, 
            0x2348CC3233FFE0F5ULL, 0x04C2A6A6142D814CULL, 0xEDF280825C27A7D3ULL, 0x0B6B24D01303E5A4ULL, 
            0x08CF7F94AE6F516BULL, 0x302876F0CA4CC3E1ULL, 0xD8131A2CA72C1ABCULL, 0x2FB76FFC231623A9ULL, 
            0xF488945DE03750ECULL, 0xA29D1869AB35490AULL, 0x935C4E8AD1C0FF3AULL, 0x1B404930953095E8ULL, 
            0x7EA7D77B1322DD1AULL, 0x722998741C81352DULL, 0x3D3A932FE899EB8EULL, 0xD7F9ADA773FEBFADULL, 
            0x1C6212D2E736FC18ULL, 0xA3F470D1D16C593DULL, 0x6F78541358120C4CULL, 0x8A3541B5A4D0D29DULL
        },
        {
            0x0DEEC7A086DE098EULL, 0x9D36FACFC6CF9CEAULL, 0x499CFF9FE3555DE0ULL, 0xCF0EE32D9FB05796ULL, 
            0x6803F4D5770B617BULL, 0x129FE149921752CBULL, 0xC2BBA1541F91FD89ULL, 0x1BC3FE0CF7C3AE81ULL, 
            0xCBFC24D97DCA74BFULL, 0xEE4A8C0E9EA8E9F4ULL, 0xD35B41113CB0BA2EULL, 0x90E7E6D5EA7599E3ULL, 
            0xFBA33D7CF8119FD7ULL, 0x23E1D808B8B5656FULL, 0x329BCB3CE25097F6ULL, 0x5C361D515A4F2528ULL, 
            0xCA2A197918657715ULL, 0x41FBF9FA42C7BF44ULL, 0x3AA544BEB98F79C4ULL, 0x84681CF9DCCFDAE3ULL, 
            0x9D5DF615B5CE54D6ULL, 0x783B1549B28E7C0DULL, 0x478FAE9905DD2FB2ULL, 0xBF45B749855D6358ULL, 
            0x95DB87C1764A2697ULL, 0x62D22CA29FD868E2ULL, 0x02D55EB340C32996ULL, 0x9CBBE666328B6BC3ULL, 
            0x1226EBC1CEE88BEFULL, 0x2B2D736FD847CA7DULL, 0x77AF05609E2C833FULL, 0x75BDA6A1754C9E6AULL
        }
    },
    {
        {
            0x846D87305B23F4FFULL, 0x1F1417A34994A64CULL, 0xDAA91DCDFCA510F9ULL, 0x6536E9A5E7AEFC1BULL, 
            0xC5310C776DCFFC0EULL, 0xFD77C114E4C63FFEULL, 0xAD7598DF0A00A8DDULL, 0x8B3822E44A12B4B9ULL, 
            0xD3042576F94779ACULL, 0xFBBA21DE4651DA98ULL, 0x7E5E8186E616E599ULL, 0xC022EF3F8B7BDA41ULL, 
            0x5AE377505D1C3CE5ULL, 0x2E5B91EC34EF029EULL, 0xE8A5A8B4B013AD48ULL, 0xD6953782B0799EAFULL, 
            0x4F7B6DFAD0DD5081ULL, 0x6B75C97EFAE69526ULL, 0xE35F36EF1842305CULL, 0x95AC3B091F419B17ULL, 
            0xB42CA10AC1D42B75ULL, 0xD54BD997809D7CE5ULL, 0x6DDCF2BDC37FF9B9ULL, 0xC6127DD83AB98332ULL, 
            0x3760FA3F6624520AULL, 0x6809E236D85AE7E2ULL, 0x403D59C06280436EULL, 0x908CB8FF7A588682ULL, 
            0x03C64CD532C8107AULL, 0xC87CC1621833B6EBULL, 0xB3D07ACDDC48A1D5ULL, 0x121B060EE9A08893ULL
        },
        {
            0x95DD7C1B121CA90FULL, 0x817D7B93B59C649BULL, 0xD46B2F9617F1C4DAULL, 0xF5858873C126F131ULL, 
            0xE6714E16EC28B1D5ULL, 0x74A900B84D5C420FULL, 0xEC4B3C1D97C62BE7ULL, 0x1B6F8C456BB3BB9BULL, 
            0xA22C8378F6101F76ULL, 0xD89476A0FD9B0850ULL, 0xF01EF4108364D69EULL, 0xCDC9942919B9105CULL, 
            0xBEB44A88B1EBF0D5ULL, 0x84F9A2C0C085A32AULL, 0xDE2F9FA1D6444C20ULL, 0xBF0A0DDE3243C644ULL, 
            0x1004C1FEA6EC54DFULL, 0x849AD20F663144DBULL, 0x7C37C1CE927A2287ULL, 0xCDFD1B0B49700773ULL, 
            0x5FA6ABBE8FBC04B1ULL, 0x5B47C6912FAED048ULL, 0xC0390ECA82D663C0ULL, 0xAA579FB25D86BF6BULL, 
            0x6101222428E4BB22ULL, 0x79D180B0CD9C72B8ULL, 0xD5BBC8228192EE4EULL, 0xEC3A552BA3BCD484ULL, 
            0xF880D969659AFF40ULL, 0x7D70D41D4CEF0833ULL, 0xE03EDEB4B88F6AB5ULL, 0x528E36E2740445FEULL
        },
        {
            0x818A7E44114D1D18ULL, 0x431FE1687EDBC783ULL, 0x114ABDA0F4BA5CB6ULL, 0xD68916CBCA812ABBULL, 
            0x9AD52EC4F53FA6C7ULL, 0xCBF914C87E5E32E6ULL, 0xC38C1D84C699D1AFULL, 0x33E7C3F9D6487978ULL, 
            0x226E20C2C9B6D9EDULL, 0xCFE363F4B3AB1631ULL, 0xC7F2A2FB461DBC74ULL, 0xC3092D704F6D45F6ULL, 
            0x0F4F78AEE991D5E4ULL, 0x6ACE2FFB056206B8ULL, 0x19A332B62BF1B34CULL, 0x38760AA0439CF8ADULL, 
            0xE9E1FB668AAAF3D1ULL, 0x335DCCF442856222ULL, 0xFB52BB8E27A7FEF1ULL, 0xB7F20D1C139100BEULL, 
            0x5C0BB1AAFA1004A0ULL, 0x056A0136142C8505ULL, 0xFCFBEB92F17AF8ADULL, 0x316558D902C2099EULL, 
            0xC7A329C5100E08E2ULL, 0x249AE949BDBDD590ULL, 0x005DA6DA17DCD627ULL, 0x3AE99127C2F61211ULL, 
            0xAC6BE39BFEBD2E89ULL, 0xDDBA0312279C0BEBULL, 0x5EC1FBC82376BC73ULL, 0xB4FB243A5F5D1F36ULL
        },
        {
            0x3A9E775DA1A6C2D6ULL, 0xF880B72A6319E51EULL, 0x785EA00D63C62B03ULL, 0xAE6CB4F7DA0F3DF1ULL, 
            0xB6637305692E8EBFULL, 0xA1CBFBF8D8C49DFAULL, 0x9D782566A6E51570ULL, 0xD5F013BD8335DADEULL, 
            0xA31C7D6537B73830ULL, 0xC64D8761E49008BBULL, 0x4AC2452828A92B95ULL, 0x041C09546E526907ULL, 
            0xF60CD073EC178231ULL, 0xEFEDA62F5D4714C1ULL, 0x63208E154B57C27DULL, 0xA51230E28D412C88ULL, 
            0xD57B148EEA017C9BULL, 0xA0C7E8BAD70A731EULL, 0xDFDC2B8D5790BD3FULL, 0x05B17122403230C0ULL, 
            0xE311C54F719E6406ULL, 0x1C0DE99A538FEB51ULL, 0x51C0D7A967A04791ULL, 0x47F8091263D2CE8FULL, 
            0xC09F3AFF2DC22925ULL, 0x21D797274C87F6DEULL, 0xE7242E33FB6825F7ULL, 0xFC3A15627CD9526CULL, 
            0x36CB066841D40861ULL, 0x3443C7E6C52248EAULL, 0x2C4BC861CE2F5F18ULL, 0x349A01A34D0C5D13ULL
        },
        {
            0x5013990271441546ULL, 0x5537D3396EC57A94ULL, 0x1351428B0AD62A94ULL, 0x3D483F3F485FFE21ULL, 
            0x0634E40985EF1863ULL, 0x5FD8D188C262F35EULL, 0x6B729C5AF939FD67ULL, 0x197AD5844B0DD242ULL, 
            0x49443A696BC8961EULL, 0xD184BB59438E4EA6ULL, 0x6D68EFDF049B3A63ULL, 0x038016AB9C52EDC9ULL, 
            0x8372159205FA155CULL, 0x23077F1EB20EC830ULL, 0x47DDB9CA942B13F4ULL, 0x634C807BC5C9DCCAULL, 
            0x4BEAC08DF817F05FULL, 0x37840A24A8610BF0ULL, 0x246B7E8011078F51ULL, 0x0930B4802DA1C7CDULL, 
            0xDA430F409C9971D7ULL, 0x1FFCA62B1958A219ULL, 0x51C4BE02A3640D18ULL, 0x9E1654ED15376BE2ULL, 
            0x56F1DC43C52FAEE4ULL, 0x3C2C8C329E428712ULL, 0x38F9FB384E56F3ECULL, 0xCFB1D29D325E79FFULL, 
            0x6E6C9B5708327388ULL, 0x3579C56C66EBFDD3ULL, 0x41FFECDC508B991CULL, 0x979E60C965CFB07AULL
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
        }
    },
    {
        {
            0x88120987E28A89A7ULL, 0xCC7A31A2E0842BE4ULL, 0x148E28926FBF779AULL, 0x2E3D9D27E5C72B1CULL, 
            0x1AF6C629F18171E6ULL, 0x37025D6837FDC1FEULL, 0xC46C2C8FA5E56149ULL, 0x768F61A84B7D0496ULL, 
            0x2F3ACF3C4D36DCA1ULL, 0x1F7F2917A96E416CULL, 0xC18C72548B0E276CULL, 0x068BF5D795002D35ULL, 
            0x1B8C06EF3A2CED6DULL, 0x12DDB4E5A0832E46ULL, 0x4B8E6CC162B2AFC8ULL, 0xD7D3577088529436ULL, 
            0xE40E5D5338CD1440ULL, 0x98ADE918B1DB2E25ULL, 0xD6BBC6EE4ECDD80CULL, 0xA5BF4D5D12EADF44ULL, 
            0x0B8DD6B4A772E84FULL, 0x19DC90F7D06DB049ULL, 0xEA773AA9F15424BBULL, 0x1A47CC95CA630D88ULL, 
            0xFE901A80DDE718D6ULL, 0x837D0981C565E5BEULL, 0xF34B90C20E8FFE1DULL, 0xC00626437ABB254AULL, 
            0x151F4E2C11B93A41ULL, 0x0340D08DAACE448FULL, 0xE81F5BA09060F313ULL, 0xA890C3907FF6D4A6ULL
        },
        {
            0xECDD6A24CBA30384ULL, 0x9F9485F97E0CA584ULL, 0x2AD94380B15BB974ULL, 0x42BE26E9B5AB93EFULL, 
            0x12AE403080427CFEULL, 0x43C522934BE34BBBULL, 0x46B5C95F96616619ULL, 0x9337573E50D0CA7BULL, 
            0x290E628A861CCDD2ULL, 0xA7FCC21FAA9877E6ULL, 0x2A3CEBC0E7E84667ULL, 0xBD3ADFFB1341B372ULL, 
            0x36613CFA8F96D22EULL, 0x9FAA3DB3EA10EE86ULL, 0x089DE3915D8DD4D4ULL, 0x3650B16B815BCBFDULL, 
            0xB43A3F622F8161E8ULL, 0xF593AF6A8BBBF064ULL, 0x7348910FA1D96AFCULL, 0x11CE6557DE2733B8ULL, 
            0x6407D7ADCD4769DCULL, 0x28F590B6DCAE4FDFULL, 0xECEA6C531309DBFCULL, 0x61E9ADFE1FEFF92BULL, 
            0x905474A2F4E60CABULL, 0x9A2F5A724E05D948ULL, 0xF5A867CB6557A7D2ULL, 0xFD2BDBFEB17E3DC4ULL, 
            0x879F895DB8425EACULL, 0x95E44F10A5824A3DULL, 0xBA0E16A4B8E28FE5ULL, 0xF9D391FEBE78F58CULL
        },
        {
            0x11C0379532526CBAULL, 0xEAC5636056F8BD7DULL, 0xEA98E17624ED9088ULL, 0xBB5B3B58BFEBC60FULL, 
            0x4843440B0EF71461ULL, 0x6B9720934E14A861ULL, 0x619D6E007B8E1322ULL, 0xCF8C8C0E4B3D5AA1ULL, 
            0x181D223F2D1226ADULL, 0x25657B95460E918BULL, 0xD6725EAE3D38921BULL, 0xFBA8F88D28470CEAULL, 
            0x6EB922839BB7FD99ULL, 0x17254E6D70897504ULL, 0x260B947E7EE92614ULL, 0xF1BAA1E77B9832A2ULL, 
            0xC08F6E6450B6E253ULL, 0xD7675738BC8498AFULL, 0xF39CA221FAF15500ULL, 0x7619BEB989843E9DULL, 
            0x2BF91766C3463F02ULL, 0x98A32DAA778E7C29ULL, 0xB995C6244D4DFFEEULL, 0xCC06E064B2CAFFBFULL, 
            0x6863A272FAE89F54ULL, 0x8CAEF3D906521F30ULL, 0xED0C3F524750FCD1ULL, 0xF117771E06824860ULL, 
            0xF89EA74F6BF94DAEULL, 0xD48F3FDE0690FC39ULL, 0x272F8B860FAA6CA7ULL, 0x06AA04EEF55CEEB1ULL
        },
        {
            0x1592671747F6ECD5ULL, 0xA9DDCAC5655BE95BULL, 0xB0527BDC575AE9C5ULL, 0x9845FDF57AC8BFF8ULL, 
            0x2CDB8A00056CA493ULL, 0x372D50083EB3A223ULL, 0xEE10113D5743A4D3ULL, 0x997474BB9D46B2BBULL, 
            0xCDF39B692429738CULL, 0x9331DF5A47ADFBF3ULL, 0x7C01D394E9A034C7ULL, 0x162D657A7AB47E37ULL, 
            0x01F5A10FA3DE7983ULL, 0x0172CB6D9749C2B0ULL, 0xCB44A694033599C9ULL, 0x772C5C99D782030EULL, 
            0x9C34E06D454B186CULL, 0x5D329F7ECD1F3A37ULL, 0xB89FC2FE200F435CULL, 0x014A0BC56AA8DCCEULL, 
            0x1402D27EBA933CB5ULL, 0x990569F915B3A512ULL, 0x0F8D5B99A28642B9ULL, 0x92E35F580C8767F9ULL, 
            0x2484CA59350F2810ULL, 0xA4489690B9A4B0ECULL, 0x056EC4F7FCDD1321ULL, 0xCAC0E57D3BE1E366ULL, 
            0xF3090E14DAE547D6ULL, 0x6F1533B01B1C6C04ULL, 0xDBC976C3677878D7ULL, 0x734F2DAF25843493ULL
        },
        {
            0x1BA52539E41AC746ULL, 0x9F5CD5FCD50C413BULL, 0x601100036782E967ULL, 0x83CA7AE7B9FC0F19ULL, 
            0xAAC77EDFD22FE78EULL, 0x95D5BBEDFDFE8E2DULL, 0x4681D962E231B657ULL, 0xBCAB71488BE5E9A5ULL, 
            0xA4D729B0FD616B9DULL, 0x7D688679C5A651E4ULL, 0x5AF61C4C22AEF65BULL, 0xAE06186097326C57ULL, 
            0xCC967E4235008B34ULL, 0xFEF1BA3EE54E0B22ULL, 0x203BC3FE4F27EA3FULL, 0xF42808C25A7A6DE2ULL, 
            0x466C519CC0831CB9ULL, 0xF985FA8C710D844DULL, 0xB6956CA3A782784BULL, 0x398B3376C315A60BULL, 
            0xD8A2702CAFF09887ULL, 0x92E2EA4A5E30F227ULL, 0x476AA351B99F1C00ULL, 0x83528561D7E219EBULL, 
            0x072AB3E68E49EE63ULL, 0x34AD101F2FE1EA1BULL, 0x5F6157F7026B891BULL, 0xCF983B4CC6C23A70ULL, 
            0xE113F9F4F56CF449ULL, 0xADF3A3473D5735CFULL, 0x93D60F6923170375ULL, 0xE7868F75DD66F32EULL
        },
        {
            0x0E8A2D6D7B4786A6ULL, 0x1B7034A7D35D6962ULL, 0x8303899AA49902EAULL, 0x32AA96E46D9CE13CULL, 
            0x7F92C8C23C258B02ULL, 0xC198EE0008848A9DULL, 0x4271A64A25A533D6ULL, 0x176063F4351C4F29ULL, 
            0x9F3EACC5202C4505ULL, 0x3AEB8E62EE8B9A6DULL, 0x52B99C9EBAD5224CULL, 0xC7BD6189700F5440ULL, 
            0xE17C2B4B8FB47CC1ULL, 0x873EC94AAFDEC0ACULL, 0x8CC2DD700F69D2A4ULL, 0xB5C0E3F6CB34CCADULL, 
            0xE47F58522BF1B633ULL, 0xB34A1D5093F2749FULL, 0xDB58604231AC061AULL, 0x9BF1C80D0046CC68ULL, 
            0xBE2404CFC9ABA0B5ULL, 0xDCA444EAC9C5E072ULL, 0xC11BD78A2C2822D8ULL, 0xA84E522D2937EA5DULL, 
            0xDED152540B3E365FULL, 0xB8ECCF238339A673ULL, 0xED3BEEBDD1E469EBULL, 0xF6E5AA85BEC076EAULL, 
            0x2D8041254868950FULL, 0xEA3936A1348DDD3EULL, 0x03D2A951078329E1ULL, 0xBF84D6D9BBCFEA06ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseAConstants = {
    0x0214D88739813AD9ULL,
    0x966326CE05304F1AULL,
    0x0482F3CF04E9EC63ULL,
    0x0214D88739813AD9ULL,
    0x966326CE05304F1AULL,
    0x0482F3CF04E9EC63ULL,
    0x7C1C00BA6DDEE283ULL,
    0xF8D4B5D3040E8B48ULL,
    0x84,
    0x01,
    0xFE,
    0xDA,
    0xE8,
    0x74,
    0xBC,
    0x49
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseBSalts = {
    {
        {
            0xE8A7C1FF3D05FD39ULL, 0xA28EF923F8D79688ULL, 0xBC79A318C83E7D92ULL, 0x3D5A769EAA20A84DULL, 
            0x6EA5CB37C6B76C03ULL, 0xD04CCCF584F395FBULL, 0xD678BC10F4FA6AFFULL, 0xD263D6EDB94A406BULL, 
            0x0F4F93BBCFC7497FULL, 0xB9D7AF0F17EDA71DULL, 0xF0323F5801F9C088ULL, 0xADCF5A1C6822975AULL, 
            0xF5671532B6385D5CULL, 0x50AFE71BEF3588F2ULL, 0x29F21B71FCA51322ULL, 0x80A04A3EE67337F8ULL, 
            0x327473CC7C9AB68CULL, 0x3C812B35B2EE951CULL, 0x1B48413B2786D631ULL, 0x6874BE305B238D9CULL, 
            0x033F90C6103BECA9ULL, 0xE83F78BF7CBECA6EULL, 0xA28AA4D2B799322CULL, 0x6579071304CB513DULL, 
            0xB6FBF7F5E1A1B80BULL, 0xE49B364648F0FED1ULL, 0x7C3B710B382FACEAULL, 0x22A9E5614AB9BB24ULL, 
            0xA40BCA001F2FFEC9ULL, 0xD40680B94CEAFA96ULL, 0xB366279BB53BAB5EULL, 0xFB4CF5A7063E2C10ULL
        },
        {
            0x1F809DF3BA91693FULL, 0xD2BD3E8D26A6203FULL, 0xB3C59A29F54352BCULL, 0x814DB73FC1783F4DULL, 
            0x9C8CE57E89B326C9ULL, 0xE30B63D2021B60F6ULL, 0xBDF425AD64D75354ULL, 0xF877D81227CD44E2ULL, 
            0x8913243DF1EE7380ULL, 0x4C492501D74599BDULL, 0x4949E8C4F822859AULL, 0xA011D979A2539CA4ULL, 
            0x438F0B6ACA0A5399ULL, 0x3C630496EAB4E23DULL, 0xB34F9CAC2F2D0049ULL, 0xCF0D7DC30A0F18B3ULL, 
            0x5671A5ADE77C5F64ULL, 0x66741F37AEB175CCULL, 0x260E98A19F8C2B5FULL, 0x6441B65299855716ULL, 
            0xB37951F869832F98ULL, 0x33D3A7863D06E043ULL, 0x588B8E5EEF7083DAULL, 0x01EC0AFA624C8685ULL, 
            0x8C1EF48FF74E9638ULL, 0xC7D576975C00281BULL, 0xBEFF3F3A4D2EB1CFULL, 0xF1ADF0531A2D6EFAULL, 
            0x48347C6B81A9D714ULL, 0x145E511E019A8FE5ULL, 0xB771B2FCE35CE8E7ULL, 0xAC798D48F233E534ULL
        },
        {
            0xD482E2ACC8B8D321ULL, 0x8F9CE80CF3FF7525ULL, 0xCDEA1D7E8261DFBEULL, 0x25B7E3029FCC7588ULL, 
            0xAD17FCA730DAEDECULL, 0xE783E711DACB6F50ULL, 0x24A22F7684D556CAULL, 0x45DB8385446C968EULL, 
            0xDF5D7200AB133512ULL, 0x35332B643C44B068ULL, 0x753B64F66D1DC11AULL, 0x8CAFF93A103D5B13ULL, 
            0xC8787A117D605CBCULL, 0x6941D8C75904A0E9ULL, 0x09C3840D1CB36890ULL, 0x1E1E0A137DA48FD1ULL, 
            0x72DAE73780255F08ULL, 0xA171D5E2D654CBDBULL, 0xD556953137CB3C35ULL, 0x81F921ACAE12CF3CULL, 
            0x0180859236EA5EE3ULL, 0x57D90689F05368E1ULL, 0x98BAA044F6B3919CULL, 0x7DBB69FAAA0E3A68ULL, 
            0x3A15910B7FDC4DA9ULL, 0x0F5A1A40382E2228ULL, 0xF2712A62EB0B31B3ULL, 0x3A521A29CE540EC4ULL, 
            0xC9EF18E3E9458668ULL, 0xB49271F0C1D4668DULL, 0x76DB0D288E6D86AEULL, 0xA6270BA1E84DD3C8ULL
        },
        {
            0x7F6246B7DE5A8585ULL, 0xE43FEEC35F5926DFULL, 0x0FA01136F199569AULL, 0x95D586BBED907111ULL, 
            0x6A53604248C363CEULL, 0x996A599ABDC9038DULL, 0xBDC9312080A00F54ULL, 0xB24A9C67939AAE40ULL, 
            0xA8BE1BF12B99D503ULL, 0x50837F6123BAA6FFULL, 0x738D42DF92AC6933ULL, 0x03F1553218E645BFULL, 
            0xDF2E1D14144EADD3ULL, 0xE8EDBC7DEEB51308ULL, 0x1081D015CCD180DDULL, 0x0C4538188F9E3019ULL, 
            0xF189174FB909B519ULL, 0xB196A5E9017DDB9AULL, 0x564ED4FE74CEDD1BULL, 0xBFD00476326D6B8FULL, 
            0x03CC85ECE90639CAULL, 0x350A1F653DC0742BULL, 0x8D810E44D8DDAC99ULL, 0x8A84936A91EBA329ULL, 
            0x8CC4723D6C8BCA32ULL, 0x05E2C1D84F347FC0ULL, 0x1C8AF4E11D34270BULL, 0x44B8A3DBC431F286ULL, 
            0xA59B3E942A0BBB58ULL, 0x516F1952F857F86CULL, 0x1C9BA33A4A0C4586ULL, 0xF68D053C04FD9650ULL
        },
        {
            0xD5B33E5E046EEF30ULL, 0x00B08CEEF5B890E5ULL, 0xAF0739050728B7F9ULL, 0xD7A1259FD838B9A4ULL, 
            0x4BD3553CC78F88E0ULL, 0xD5F07C0CA572DE23ULL, 0xF971C0B4EC76715DULL, 0x42783FA069F5F32EULL, 
            0x990D20E5EF19D6B7ULL, 0x72C16C06F776694EULL, 0x937857ADBB5909A9ULL, 0xD62B446B8189CEBCULL, 
            0x50EF4E46CB448C23ULL, 0xFA957B10B04E80B8ULL, 0x191198620977FDCBULL, 0x79C0108762EFC7FEULL, 
            0x0E44ACA3199F1553ULL, 0xCA7DA2A851C99B1AULL, 0x341F97DE70739B7EULL, 0x305B8B2AB2AE9BF8ULL, 
            0x63881D33C58D8DE2ULL, 0x6B315E778A4A5E10ULL, 0x1B05C77608CC6E73ULL, 0xCACC43CBB56F0681ULL, 
            0xF755F51ED5BA0082ULL, 0xB613E1E6B8652CFFULL, 0x56C306993CB5F9C6ULL, 0xC7E3E0E0DEA620AAULL, 
            0xF3891C55A1EC939EULL, 0x28822417DC64F611ULL, 0x00AA14F9E85D2055ULL, 0xBBFC95A54A81E09DULL
        },
        {
            0xAC775378B63AE015ULL, 0x11EBBEABFF85CAF5ULL, 0x662D104536D7A71DULL, 0x64A3A4F485652D2AULL, 
            0x8097A37804B57975ULL, 0xCDFE6A1AEEADF6C5ULL, 0xBBCC3AF4E171A45BULL, 0x6CF61E83035D6141ULL, 
            0x175EA2592386B290ULL, 0x3BC6A34DB807C74DULL, 0xAC95D73BABEB7215ULL, 0x4B79757C5BF8BB49ULL, 
            0x8B2B0EF1B6FCB812ULL, 0xA2FE1009DFF1F077ULL, 0x7E14A0FAE21E5CE6ULL, 0xD3F90A9952812D2BULL, 
            0xEF0C0F396A7F1D07ULL, 0x085446ACC7D1D651ULL, 0x84AF0D958E6D6FFFULL, 0x637F2098FCDCF85CULL, 
            0xA9D5F60AABB4C7EFULL, 0xF81BC7D7E75377DAULL, 0x3BCDEE7653836F71ULL, 0x99AF3AC1D63929E7ULL, 
            0x3E7270C73920B217ULL, 0xC3F960E3DE7CD341ULL, 0xFFFA4C63D0EAB626ULL, 0x561EA90C91B2D4A7ULL, 
            0xD8C7C369683E8AB6ULL, 0x5DCF4CD93B312CDFULL, 0x11636135B27855E9ULL, 0x34AA5EDC29B7CBF9ULL
        }
    },
    {
        {
            0xF078748D145216E0ULL, 0x22075A1B927F9B9DULL, 0xE88254E3F920C15AULL, 0x4240177576C3ADBCULL, 
            0x01DC8BA6F3F119B1ULL, 0x76199A0FB58436D1ULL, 0xECD3BD00F8B2EC70ULL, 0x982100F2E321B02EULL, 
            0x7344B50F3746357EULL, 0x1B8514FF3506A125ULL, 0xED58411812B78E80ULL, 0xEE701E4CD09419A6ULL, 
            0x23F3F413C2C12A7EULL, 0x6E84265589CD9545ULL, 0xC42F6C099D08BD90ULL, 0xA88139215151735DULL, 
            0x5C5286CBF01B71F1ULL, 0x10FA14A188A90A38ULL, 0xF675A411FF0E8EC3ULL, 0xAB6A7F9BC0C1021CULL, 
            0x479CE50F1D5C8275ULL, 0xDA1A6570265D70BDULL, 0xAA704B9FEFB3AEB1ULL, 0x1F2466B8C1FA1545ULL, 
            0x64F46A902BF8E0BAULL, 0x7D9407A372C8CEE6ULL, 0x6567F663FA022B6FULL, 0x210343BCB806F7D1ULL, 
            0x59D1303DC3841244ULL, 0xB31D65DFA0AAC8B0ULL, 0x4D1D663C0E7C3106ULL, 0xFDB6F851F4F8E379ULL
        },
        {
            0x547183E3756BC91AULL, 0xE2BC075D3B8E5572ULL, 0x06BDAF8EDDED7FD2ULL, 0xCD73229214E3D4C2ULL, 
            0x44CC619C6F28A7EBULL, 0xEA940DF442348B11ULL, 0x70DA94D8C8C5A2A2ULL, 0x47F984FA8358EDD0ULL, 
            0x12EC616F110F36B8ULL, 0x87049DE3EFAE50D6ULL, 0xC6F6B94CE67B6B7BULL, 0x80B7B69B98D64A95ULL, 
            0x3AACB16EE238F93EULL, 0xED796D9157B43A09ULL, 0x0E4368CB0DB20451ULL, 0x8747B6A361A07682ULL, 
            0xFF3B23521040B64BULL, 0x8B451E0B507602DAULL, 0x346C878A9730A7C4ULL, 0xDCD2E48808A2A5DEULL, 
            0x357222EF5A52A737ULL, 0xD972E0D8ED4B7EA8ULL, 0x7A0A6D6A0DD03FC7ULL, 0x212BBC8F83B089CEULL, 
            0x70FEFDF26B748966ULL, 0x7C50196DB2E620A7ULL, 0xF733990169C6858FULL, 0x12EED13D41168C36ULL, 
            0xFD362EC8CE58C697ULL, 0x920FB5DC748B0BB2ULL, 0xBE7CB82310B3DCEEULL, 0xD05C48ED6BC9D327ULL
        },
        {
            0xC17ECBB69A33F3BEULL, 0x619B9537A6736191ULL, 0x32B811F9A9A234B6ULL, 0x1F419CF1E2284776ULL, 
            0x44677BE57FD3D2A5ULL, 0x2C4E544D22A4C31AULL, 0xB0C9D90B8702B5E8ULL, 0x664452F876CF05BBULL, 
            0xBC559D931EA57112ULL, 0xABBA95327B8B8C4FULL, 0x50DBC986F87A3816ULL, 0xB36195A4021FD344ULL, 
            0x0D5FB44A21ECB299ULL, 0x73D490E464B1AECCULL, 0x18A9B2772697DA10ULL, 0xFB36CACA21DEC00CULL, 
            0x490A78D8208D991EULL, 0x19F1BD92BD15A456ULL, 0x369E73CD02E9E5CBULL, 0x3085ED9FA855B781ULL, 
            0x6FBEE5A8BEF7DF1DULL, 0x6A44F3597C84C6E0ULL, 0x79A06C517B38614DULL, 0xB681B0DDE32F162EULL, 
            0xD6DA291932C79CD1ULL, 0xFF7A451894EC0A91ULL, 0xC87D9F41ED1E5513ULL, 0x595392E8B8DD7919ULL, 
            0x3720F1174155D20BULL, 0x5D90C8C1EEB7980AULL, 0xA7C38391B2F9D5E1ULL, 0x05A7F0DD897AE716ULL
        },
        {
            0xE947C4A63AC0D41FULL, 0x5235E3994B1E87C2ULL, 0x0AA2066A60DA9B04ULL, 0x557636FA558383AAULL, 
            0x8162814A7216FEBFULL, 0x5D887DAE52B65BA5ULL, 0xE422D77F67920C9BULL, 0x84B4FABF15BDE4CDULL, 
            0x65E5BD3D4C13AC16ULL, 0x3BE388F4044D64D7ULL, 0xA8766D92C0F47C67ULL, 0x684B11FAA6278984ULL, 
            0x1E729548BC398176ULL, 0x7201D928CF211C3AULL, 0x229B995884F71425ULL, 0x8164DCA447E75C5EULL, 
            0x9A51316C3B9E07F7ULL, 0x63365478F3B3FB1CULL, 0xE9594369E51BAB1BULL, 0xC7FC2FA2888FB30BULL, 
            0x6B9978CB864831B1ULL, 0xD0B5B79882E8B6C0ULL, 0x9E9BC5D05C9D8DCAULL, 0xF87A1F3F896896D8ULL, 
            0x71018C5C9AD16B04ULL, 0xA44C52EB1345D09CULL, 0x3E40CFE4951D645CULL, 0xBDC334205FA8AF90ULL, 
            0x1D5944948F0B18B3ULL, 0x771D790041DB5804ULL, 0x3DD5530452935EE8ULL, 0x0468D75FFE15425FULL
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
        },
        {
            0x209BB92CA329ABBBULL, 0xBF9258C80746D08BULL, 0x2E2F09FE8C0AACEDULL, 0x94F106A57E44988FULL, 
            0x938F13A25B1B5BDAULL, 0x9168479744C59065ULL, 0x16B9ABA83F023F03ULL, 0xBDACCC7FB5412343ULL, 
            0x8F334F585E1D5DFBULL, 0xCBD47F18E6DBB04BULL, 0x54C379D2B3F4B1F2ULL, 0x6A94531D2A7C06C2ULL, 
            0xC4BF7770897362B7ULL, 0x4E1CC22AB896184BULL, 0x24481AAC11074DA9ULL, 0xDBB86B0EEE1BB8E5ULL, 
            0xC6C7228984FFAD41ULL, 0x0B97663460E9EF0EULL, 0x5819053BF7BD18AFULL, 0xE5032EEC4982B42BULL, 
            0xBA76099110F8B842ULL, 0xB84F22B157C68626ULL, 0x1B9DDBA123E26EC3ULL, 0x7C9E41BE6CA722BBULL, 
            0xDD92C6395CBBDCA2ULL, 0x37D9A36B15E48C04ULL, 0x617066A68C0D76F6ULL, 0x830038991D092BB7ULL, 
            0xFD2A5E1B9B83964CULL, 0x95B0E2F8C018709CULL, 0xD1A3920BF4536179ULL, 0x260E0C43A635883EULL
        }
    },
    {
        {
            0xB65619DE4663A6C8ULL, 0xD2FE2CE794567CB5ULL, 0x9C076DFE7369083CULL, 0x0D45F5CA04B9BA2AULL, 
            0x2A1E92CCB12585ACULL, 0xA6664FF50402D281ULL, 0x2BCB79D4E1198843ULL, 0xB642605758F3F222ULL, 
            0x7FA59130075B75A7ULL, 0x21AAE86F98AF94D8ULL, 0x0BC0F4D026935C29ULL, 0x8D123E25FA36ED02ULL, 
            0x588BF8F42166CEDCULL, 0xD4989406A25ACF4AULL, 0x5C5151E051D5E9DDULL, 0x6025064249BC9AE3ULL, 
            0x5FC15AF8B491BE74ULL, 0xF27EE5515A869390ULL, 0xB944CB1A14501A93ULL, 0x2646BFCAACDA8018ULL, 
            0x1C8D898D2C8D8050ULL, 0xB2EAB664B6131881ULL, 0x4ECC31B8314221CCULL, 0x878604E26F04ECCDULL, 
            0xAF32012249A9DED8ULL, 0xDA8088BCEF1F041AULL, 0x17DA23C67CB50A3CULL, 0x3ED0AB475549AE1CULL, 
            0xF86D93559F9E83E3ULL, 0xCFAC0402DA8BD894ULL, 0x5550ACB7DF1910AEULL, 0x24783AB50D4A12ABULL
        },
        {
            0x0FBC6F4E8A639B5CULL, 0x630931C1D49F86DDULL, 0x92FF656FFA44CB98ULL, 0xD9EC1C418D100AFFULL, 
            0x954B924A6CC124BDULL, 0xDBC727D555CE52E8ULL, 0xF1C6C2DC2CD59ABDULL, 0xAF241DF4CFD9D3AAULL, 
            0xD12668AB5C74036EULL, 0xEE5984C03EA7779AULL, 0x914E7F7E9FC9856BULL, 0x98C17DE7BD9AD90EULL, 
            0x2406EA177E6DD1DCULL, 0x92AD9A1D0E298898ULL, 0x7258F2EB8F19787FULL, 0x539D8C2930131A71ULL, 
            0x6B4EACA2D0DF650FULL, 0x2C5AD1318DECF1E6ULL, 0x19878AD2454B11B6ULL, 0x6EA135D6ABD4625CULL, 
            0xBCA8964173154815ULL, 0x852F6C0525F56B2AULL, 0xAEAB5BA8C049F0F2ULL, 0x6C5711557CBD5B3BULL, 
            0x355E10F7DE183B1EULL, 0xAD691B3C18B70964ULL, 0x878B633DA4A6AF9AULL, 0x92D774C369B45605ULL, 
            0xEAF4E8CBF18E03DCULL, 0xB69A3BA491D645ADULL, 0xF9BDBA18710A44CFULL, 0x46958CCE4BDB273EULL
        },
        {
            0x6F0BA338B2FF3679ULL, 0x8642A6C75928EC73ULL, 0x3F9EAE9C41184A14ULL, 0x9770A6C16E4E880FULL, 
            0xD68F78106FD88219ULL, 0xD65AAE2D6A8BD005ULL, 0x0262A3B483F75205ULL, 0xF1FC49CF9F58A88CULL, 
            0xFB6B3C6046FA3710ULL, 0xC4375CB1A4EE3E6CULL, 0x4CA6CF5A62E343CEULL, 0xC5BC23808E06C989ULL, 
            0xCD9134A18A2AC7AFULL, 0x00815FA2C1B163D4ULL, 0x5E4592164AEFF57EULL, 0x9757C71ACAA0C4ACULL, 
            0x281A5C3143A1E49EULL, 0x2F584547E90DDE42ULL, 0xF5350CE1EA6183D2ULL, 0x7CD1A4C0930D8269ULL, 
            0x0B49FC32EFDDCE86ULL, 0x28F8139D5835F84EULL, 0x973E1CE29FC0E60FULL, 0x0F1A8632FFD3B085ULL, 
            0x1CF97F047154150AULL, 0x105616F984356439ULL, 0x24E0F78AAC4E1E09ULL, 0xFC5F91D622D69709ULL, 
            0xA59ECD7DD2006FDAULL, 0x82911A21DB18190FULL, 0xB086184D968E3AE6ULL, 0x0137C4C049DC4871ULL
        },
        {
            0x0C2E4EA7A4944155ULL, 0xB846656B5C280688ULL, 0xA9C5E9E2DD65B2A2ULL, 0xA347FC15052D7438ULL, 
            0x78D6FD7E21888BA9ULL, 0x92E52246A3E23DA0ULL, 0x25B4658B9DF65119ULL, 0x7BC2057D70723D3FULL, 
            0xF399F7CA70EC2880ULL, 0x3BADE7272037EC99ULL, 0x38469C360A89E943ULL, 0x8B77CB585C31DAE1ULL, 
            0x8C832D31C677BAEBULL, 0x8F2F2DD9A3F6E076ULL, 0x29B6D13345E974E6ULL, 0xC4EDD839A90E0D02ULL, 
            0x65686CB820B19191ULL, 0x89CE503A3A772397ULL, 0xE8793D1B944FF41AULL, 0x153F68B9D58EB913ULL, 
            0x56E4EF761B3678A5ULL, 0xAAD14E1C899B87CDULL, 0x16539F21C7CD2556ULL, 0x9452FE647A6D452CULL, 
            0xF24210028B126809ULL, 0x572CD4DE26F4044EULL, 0x7652F3117B3B3DA0ULL, 0x6F41F8F946A57722ULL, 
            0x58FFA1026086EE9AULL, 0x5C89794312AC3949ULL, 0x995FAA1E430C7469ULL, 0x156E9ABB453EFC1DULL
        },
        {
            0x4CA1144D2B6B968DULL, 0xF435CBB0FF77A338ULL, 0x510D0FB67CE2108EULL, 0x96E205E5546D1CA1ULL, 
            0x4530F6949428A102ULL, 0x9D524CBD9768CE28ULL, 0x61708CC117A83F0DULL, 0xB3462A688E8BEFE2ULL, 
            0xAFD57409028B0DF3ULL, 0x32F48CD2130213F2ULL, 0x10657A97237572B9ULL, 0x58BED4F360B5A971ULL, 
            0x0C6E36C8F3996DDCULL, 0x9996392905A5948EULL, 0xAF46DB4356800236ULL, 0x82FF27DF4D3049EAULL, 
            0xC60F2E50F0C42B85ULL, 0xCDD8103BA030C6A8ULL, 0xEA37BD0A86364EA9ULL, 0xB498542D001A18B6ULL, 
            0xA462A66FDBE6851EULL, 0xAC3BEA01170A48F9ULL, 0x71DD8C22AA7BC645ULL, 0xB6674DF43A33AA7CULL, 
            0xBC6061990BD7499BULL, 0x0E279432DA8ABF54ULL, 0xA39CE525A2D7DEAEULL, 0xCBE0829B1277C1D7ULL, 
            0x076E223A02F2A894ULL, 0x688FBF83D8BDDCDAULL, 0xB518FED5472E4239ULL, 0xD62B01A67969D74FULL
        },
        {
            0x93A8FB2047F2FC6DULL, 0xDC283FE43269D5F4ULL, 0x0045B3462698763AULL, 0x5613AE9679FFD258ULL, 
            0x36F91DD0F5023C7EULL, 0x3FEC7E1F4AC247BCULL, 0xD54C2A4D912D234EULL, 0x962CB9111F3C9350ULL, 
            0x37281D95C1577239ULL, 0x48E0A43A91B68C79ULL, 0x64BC3F201D6C3675ULL, 0x4F12AC234474808AULL, 
            0xE60133C7022E89AFULL, 0xD55DDAE024226DDAULL, 0x2E9B0F14F00F9EDEULL, 0xF767E1892303B25EULL, 
            0x5AF18D9BF38D76D5ULL, 0xCC75283721B90EC9ULL, 0xA1E3FC707B9676DCULL, 0xB5FAF4000E651742ULL, 
            0x41A0E48FE2935013ULL, 0x0537B4DC3B570030ULL, 0xAE794164C0FD2423ULL, 0xD892BA816BFBE80AULL, 
            0xC4CCB0B68C0005B1ULL, 0x4A4BA7FC8B587206ULL, 0x2DC7BBA4FDDD4715ULL, 0x519F7373F0AB43C2ULL, 
            0xD20B35AECD6F13EDULL, 0xBFDA4C1179161F27ULL, 0xB1799E401EA6D434ULL, 0x8073C70A4D3DB559ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseBConstants = {
    0x1D0BA820483A40F7ULL,
    0xF2153178A563A596ULL,
    0xCC04C87E43394181ULL,
    0x1D0BA820483A40F7ULL,
    0xF2153178A563A596ULL,
    0xCC04C87E43394181ULL,
    0xBD37C40F9CC1FD35ULL,
    0x0B31CE66382DEB4AULL,
    0xF6,
    0x35,
    0x4E,
    0xF4,
    0xCE,
    0x71,
    0x9C,
    0xCE
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseCSalts = {
    {
        {
            0x70DE2C9A293074C3ULL, 0x05E6F89552642348ULL, 0xC6BD6E2FAE7E5224ULL, 0xBD410170E42D92ABULL, 
            0x3EDDBDA137B42E1BULL, 0x0CD39C136B3DCF95ULL, 0xFBF8989C0185445EULL, 0x1505AF19B668948FULL, 
            0xC92AAED2401EDD78ULL, 0xE2EF20601C134D8BULL, 0xBC1FC70A8F06364CULL, 0x7381F5A7BA37D8D8ULL, 
            0x34809165AD708BABULL, 0x84F2D4D2F9DB2B2DULL, 0xDE3DFFF1EE1F104EULL, 0x0DA3CF7813A8B7EDULL, 
            0xB43B533E8708AD46ULL, 0x3399ADF6C2458EE6ULL, 0xAC8A0A9F8D72F3ECULL, 0x6B176B6B45D84D7DULL, 
            0xDC54D5880F6BEB86ULL, 0x0BE1A2FC3370F787ULL, 0x6A16E6A6E41349B5ULL, 0x46A7019C29A32E45ULL, 
            0x2F79DD8D1603AE9AULL, 0x1296A89A6270C66FULL, 0xADE8EDA8F0FBF80CULL, 0xD75355788436921FULL, 
            0xB86E11B172F5D9BDULL, 0x564B4229B1BC9798ULL, 0x0D8E548B4A77A45CULL, 0x82AB4C3E94D43832ULL
        },
        {
            0xFB2C2A5F71E184A3ULL, 0x388C373CAB1114A1ULL, 0xE3A48F4234DBA76FULL, 0x27306115CCD3AF3BULL, 
            0x5A86DC0178EE650CULL, 0xA76A534580DFECBCULL, 0xB9DF11D8086D203DULL, 0x67DF56749DFA463AULL, 
            0x5D320B37E9D3A9BFULL, 0x8892388BDA2D195DULL, 0xEE5C2BBBD1BA6147ULL, 0x8C965891BBF2831BULL, 
            0xB50CC3CF34B9B94EULL, 0x1672D4B5561E1C0FULL, 0xD39572740DD3802EULL, 0x77EF5886FF1DF173ULL, 
            0xB88FBF6B8ACB7252ULL, 0x340DFD22C4AB54E2ULL, 0x4CCDDDD153B707F5ULL, 0x9172B50BAF547AA1ULL, 
            0x249AAB565C0E851AULL, 0x8652722C944AD517ULL, 0x42024ADEDBFBA057ULL, 0xBDCBE82C55C11354ULL, 
            0x92AACC6A5E2D86D9ULL, 0x6B1029E874F44C34ULL, 0x2F4CEA4B4C24418CULL, 0x1BA94038ADF6784BULL, 
            0xADBEC6E6974897AFULL, 0x14DB63E4762DC04DULL, 0xFC9BD44BC3EEC203ULL, 0x171A3F1F25FCE225ULL
        },
        {
            0xC0DA19E4E05AA169ULL, 0x740C8759204DFE45ULL, 0xE2E8384E17FB42E7ULL, 0x4BE6011A0B5B6261ULL, 
            0xCEF8977954A11F2DULL, 0xF27D3B1682435FCBULL, 0xFE955AC1A3DB1EDAULL, 0x605809D4AC68F5BAULL, 
            0x0BBE21A898458FA5ULL, 0xE37FA6EABB23C0B2ULL, 0x2D03B90AD31F93BCULL, 0x01FCF04291AF280BULL, 
            0x6D73D6A29C0F5285ULL, 0x803D4351821B6E2CULL, 0x2EF3C04D0C00BD9AULL, 0x152B9AC4DC1A4560ULL, 
            0x6C9CEF40CEFB0666ULL, 0x762511D0D2F22247ULL, 0xB70448025D48804FULL, 0x87484D4F89BC9DA0ULL, 
            0x58668B78837D5391ULL, 0xC1C195542B5D2E40ULL, 0x126E68417E3A7137ULL, 0xDA2023EBC5C3DB89ULL, 
            0xFF1B79828340294AULL, 0x6017804B26351217ULL, 0x73D76CABA6C47364ULL, 0x17D8601C3D836860ULL, 
            0x95DB959D3CC9269EULL, 0x8DAC41C1724F37A3ULL, 0x1D2A28DD1B76F685ULL, 0x6D34A0F2B50312E8ULL
        },
        {
            0x28DEB8910DA5F062ULL, 0xE2AF6969AAD33D19ULL, 0xEDAD2C3F670E26D3ULL, 0x9ED6C7CF72FB5E97ULL, 
            0xF880AF2E23AA83F7ULL, 0xD7775C7043E55464ULL, 0xF57175B23FE9B479ULL, 0xF103768CE30F72FDULL, 
            0x826673FCAD2D6215ULL, 0x68ABE8F7BDBF9CB8ULL, 0x3C93742DC02B8E1FULL, 0xF217D698C7F00A18ULL, 
            0x93A4A979D19938B7ULL, 0x184932BA315D34F5ULL, 0x79DEE70A3DF6BD4AULL, 0x9F2B8D3E7725B986ULL, 
            0x30149B5310CF6945ULL, 0x0D032542E08CFF2DULL, 0x722EEDB36F298D3DULL, 0x82FE612296020B3AULL, 
            0xD88E32751DED68BDULL, 0x1EF05C53411EF772ULL, 0x58A084335E75B7A7ULL, 0x06D64F7D9C2CD288ULL, 
            0x0A1601DF33D35CE2ULL, 0x771444EDDD7082F2ULL, 0x451F1997795DAACAULL, 0x5C7C092F10A2D080ULL, 
            0x6F484C2FC2DF714EULL, 0xEF4E688143E69802ULL, 0x9524B3D0EADE4EFDULL, 0x0F594940101C9681ULL
        },
        {
            0xD092E7790C54DB56ULL, 0x8433C0D6A5970E2EULL, 0x58F760346F4A293DULL, 0x9493ABF37BEB8472ULL, 
            0xA8343397C81C807BULL, 0xAC611A6F8901743AULL, 0xFB72DCAB130850B9ULL, 0x7BCEFC19947311B4ULL, 
            0xB779726F0BF09141ULL, 0x15035038B400848EULL, 0x514A51CA676AABB5ULL, 0x568BC8187DAA397FULL, 
            0xF634F20601D776CCULL, 0x76FAD1571C10B38CULL, 0x22C12804719642FBULL, 0x7229A64E9418C163ULL, 
            0xDF0F6D9A321E3275ULL, 0x729E6DA556A77D7BULL, 0xD3544ADD5F4FF4E0ULL, 0x664A07DC4F4932B8ULL, 
            0x8251CA24C5CB4A4EULL, 0x6C906F47CB04AB19ULL, 0xE630C1C2A73A0C21ULL, 0xDDF71C045F244A47ULL, 
            0xFD57DD1B062392A1ULL, 0x0ED4370DC34C3D8EULL, 0x82CF46C8C1526B34ULL, 0x3FFD4204A883860FULL, 
            0x65F0873B0F767F00ULL, 0xAE272877BAD3BF26ULL, 0x8C0DD4FCE9A229FDULL, 0x4EB8AAEC42C660F9ULL
        },
        {
            0x6BC18A086ADD1016ULL, 0xD9F361175EA675FBULL, 0xE0BF753C79DB38B7ULL, 0x452BC2C7AFC90539ULL, 
            0xF0E9489A7C91D666ULL, 0xA4F8D9444C95B194ULL, 0x13729E8ABBF8B165ULL, 0xE8E0EEBC970EE813ULL, 
            0xDDCC0FCB83C50387ULL, 0x7E29575B61EEFE84ULL, 0x7096DF7BC0535B6FULL, 0xC1135A87807CDE58ULL, 
            0x6DAC0D37ED0C1133ULL, 0x4DF45B208F1B6DDEULL, 0x0E61B05CE8E49CE8ULL, 0x8EFA69C82FA78DB0ULL, 
            0x805E734212C33673ULL, 0x0F5C05B2A113939EULL, 0x72CF77A57B97098EULL, 0x652959E05B36C668ULL, 
            0xABA6BD87FC4D3942ULL, 0xDCECF8D1F4853474ULL, 0xBA6E830EC4D324DFULL, 0x9F1776ABBE5B7A2DULL, 
            0xEB391C3535F38588ULL, 0xFF79F0ADA7C83BF0ULL, 0x53AD008B370D8767ULL, 0xB4092924967D2AA3ULL, 
            0xC85FC9B417C1ABC0ULL, 0xF6B0E7226ED0FF4CULL, 0x10E85E60E5C4DD45ULL, 0xF2B73FEE5ACA05D7ULL
        }
    },
    {
        {
            0x531509F1B213D068ULL, 0x393138BE97F34F15ULL, 0x7D3F7BE403239BBAULL, 0x08EE4A2F98BA59DFULL, 
            0x7FECB4C60E6C049FULL, 0x459032E5F75DBB4CULL, 0xF53EACC80C468FDFULL, 0xD550C8CA259A1DA8ULL, 
            0x81DBEE5ACB6C7F7EULL, 0xD9C8775E2A3314A6ULL, 0xFCCEEC01265B624AULL, 0xC30F9360A2359DD1ULL, 
            0xB02ADFF53B4F80ABULL, 0x783FB35A072F7A4CULL, 0xEFC76925F9AAE8A8ULL, 0xB4494F350F578336ULL, 
            0x85CB8C82960BC2C0ULL, 0x47A21C8A13D42F22ULL, 0x94346608101C2AC2ULL, 0xC2B8EAC4D2C2A887ULL, 
            0xBF980E7CEAA22968ULL, 0x593DF13419D62612ULL, 0x226C0FA5E1B29A83ULL, 0xADD9AB23F4099FCAULL, 
            0xB16F0C92C517B69CULL, 0x956A833D343BC9D9ULL, 0x72E56097E1F0C30FULL, 0x6DF2FC30E4588B99ULL, 
            0x93657D943EB870B7ULL, 0x820E93D5A25BC266ULL, 0xED3B615BC6BB15BAULL, 0x70DBC245CFACA98CULL
        },
        {
            0x1EE6A47C99F55A60ULL, 0xC6EE4A480FDCB905ULL, 0xE46F07DDBD9461DEULL, 0x59BAAB82FFB43686ULL, 
            0xF53BB25549928091ULL, 0x84DE0D3F918BFDE1ULL, 0x724B368AD26DD4D1ULL, 0x8B1F3E9D52856DC5ULL, 
            0x31B4234C755B3340ULL, 0x5E1B4F257091F951ULL, 0xA313DF62801B741DULL, 0xD9A088A5201124DFULL, 
            0xFEF140A2E66A51E1ULL, 0x56D7495AF71AE3AAULL, 0x3FED819FAD42C96EULL, 0x5FC396CC0C7A9220ULL, 
            0xC1005E164834EA7EULL, 0x56EF5A67BA0661ADULL, 0x1A04BA1E2254716EULL, 0xBE028F2C3E6B5C91ULL, 
            0xF0FBA9D111DC76A9ULL, 0x0D394CBBAFD2790EULL, 0xF5A0775F1B1C6420ULL, 0x8513131E3DC1DA52ULL, 
            0xC6807D819848D5AFULL, 0x82ED19F981C2EDD0ULL, 0xAE691A5CAF31F605ULL, 0x1EC637F7FEBD611AULL, 
            0xB0AFE17E657DDA10ULL, 0x4B8EF7B3D5AA7B3BULL, 0x7C7E4A0D696746D8ULL, 0x740710330C68F406ULL
        },
        {
            0x60076C2AC6C570ECULL, 0x34F8A0284E051472ULL, 0xD320F190531B5433ULL, 0xAF8609B2CEC0A2BCULL, 
            0x253AEE25370D0E24ULL, 0x1A82E4C21B0D5CC5ULL, 0xDAD92B83E6D26836ULL, 0x030923CEAE287320ULL, 
            0xE75984F858D69446ULL, 0x899D2968B7F83663ULL, 0x307F846A7B3BE7EBULL, 0x373E78C3FF1A5BCDULL, 
            0x530B088C446F93C6ULL, 0x943BCA57A62D3ABCULL, 0x50BCF1A3D502781AULL, 0x93A03B96BF9D7932ULL, 
            0x697295ACC8192E25ULL, 0xF7379087A81BE3F6ULL, 0x8CFDE597446288B5ULL, 0xBB1759C4E0A9CFF5ULL, 
            0x38500B9A727B1427ULL, 0xA74FA259A8071567ULL, 0x4BB1720F4AF44355ULL, 0x9E46BADF372F7D62ULL, 
            0xEDF43D04E3C6BB73ULL, 0xC70961AB74D59FFCULL, 0x819C2B834CE07311ULL, 0xF791282E51513480ULL, 
            0x90F42D198E65E185ULL, 0xDC2FBBD2EAA2F841ULL, 0xCEB1606721E69A47ULL, 0x33DA3EE5C67F654CULL
        },
        {
            0xAB2CE325E3013089ULL, 0x2D530EB94F3F2AF1ULL, 0x092F12FE43D12C8BULL, 0x9625E9CC781B4775ULL, 
            0x0A13A58882C08D45ULL, 0x3399A3F58A29F8C5ULL, 0xFDCD096D586FEE5EULL, 0x408C21175AA6EB9AULL, 
            0xC5644420F38FE190ULL, 0x6287B95E106D336AULL, 0xCC37E693F0D379EDULL, 0x5A39245BBC0BDCB7ULL, 
            0xA562A551E0A043A1ULL, 0x145925ADABFF6B77ULL, 0xC7E8F48A116A7C00ULL, 0x4578A37667811C8DULL, 
            0xE41A0620652E0031ULL, 0x4B4F389C41003A66ULL, 0x7793FC4EEADCAA84ULL, 0x903056C7A50DF4F8ULL, 
            0xF694F69270C68A99ULL, 0xB0FD5EFEE643140DULL, 0x16D99703A4E243ADULL, 0x7EEDF2AE9A83051FULL, 
            0x80988C7C068AD36BULL, 0x858E2624BDF2F009ULL, 0x61C2337EAEE6F062ULL, 0x8F3B7511233ADD6EULL, 
            0x8A2FA7528A5F0969ULL, 0x8D94DBD287287BABULL, 0x8CF126128DBFB674ULL, 0xEA63B89BCB90ACB8ULL
        },
        {
            0xDC8DECA23CE0D336ULL, 0x700571E69828EBB4ULL, 0x3C4DDB432790840CULL, 0x01F0943224232D68ULL, 
            0xD412AFCA7304C117ULL, 0x5415C42C1D4A38E8ULL, 0xEB9E19194E6E39B2ULL, 0x8940206C41D1D6D9ULL, 
            0x1F01891EC519F509ULL, 0x3A6313C47FABA437ULL, 0x7B336B3ABE651A07ULL, 0xCC4FE23473F20AD1ULL, 
            0xF255DAB3E936C3DCULL, 0x8C524E293E981B6FULL, 0x51B5B6AF2D72C98DULL, 0xDDE0D79BD316DAE6ULL, 
            0xFD1B386B72DC7C00ULL, 0x6446E9297764DCBFULL, 0xBDDA9C04AE3C8843ULL, 0x612756F02C0A71FAULL, 
            0x42BFD60F1BD33F3CULL, 0x0BE1EF4A8881D053ULL, 0xB634220B72AE2358ULL, 0xA7712889B6528896ULL, 
            0x7545DD72B91BA46DULL, 0x4E675D6736DDE2DCULL, 0x2311E4462F904FD9ULL, 0x29FE6F861CA70B8DULL, 
            0x87A92D2FAB66A06FULL, 0xB61CCABC616F60EEULL, 0xE0AC5FC8C112A40AULL, 0xDDB2EB71E4D635FFULL
        },
        {
            0xEE77FC5198D26CB4ULL, 0xB43A9C3F9FF11A0BULL, 0xC7526F949C163018ULL, 0xD2B79490F42D1912ULL, 
            0x50DE7C4CD7C398A0ULL, 0x2C5C6B6A60109F70ULL, 0x51A13364425AC595ULL, 0xE6315CFB79986DBBULL, 
            0xAA7942FA771CE1E1ULL, 0x3DFD9E5623D93E20ULL, 0xE3139216A8AD1A75ULL, 0xC7F326B6A4A0EDD0ULL, 
            0xBA2BBDF269706CAEULL, 0xE28348D8720A818AULL, 0x2791431EB7460DFFULL, 0x3AB2709BAAF7B2B2ULL, 
            0x34DB846E332BBC1DULL, 0x59A723CCE0682AD6ULL, 0x7F51ED742734FF58ULL, 0x76AB8A8864E6ACD8ULL, 
            0x3B08CF69AE55427CULL, 0x51745E8D8D7206DCULL, 0xFF8020CDEACC0851ULL, 0x9DA689E53FA30BABULL, 
            0x2F8C55CA60E55B67ULL, 0x611DAA19E95D606DULL, 0xB38199209794819FULL, 0x0C0085F11D343C82ULL, 
            0x5DF67AAC2B69983AULL, 0xEAB80CCBDB368998ULL, 0x818419434BDB4059ULL, 0x86AAE64E43C1EB68ULL
        }
    },
    {
        {
            0x57EEEF5590D89A34ULL, 0xBEB93A95E05EFD0EULL, 0xF80908E9F2F156D2ULL, 0xB82C202760643891ULL, 
            0x96945F3459FA74C2ULL, 0xF5B6ACCF940AC6BDULL, 0x44D523B16F095992ULL, 0x81BA89A408317FEBULL, 
            0x6822DD76F5E3AD5AULL, 0x5FA2625E8CE6D3D8ULL, 0xD186D729E7A0D3DAULL, 0x0164C020BA0E5FDCULL, 
            0xF02110CEDA55BB34ULL, 0x7EEFEBF356400D82ULL, 0x0FEE1AA7A850AF84ULL, 0xE40383E8B37F6E7FULL, 
            0xD19C03DE810981E7ULL, 0xBCFEE0A82ABB284AULL, 0xF7B64B30F5CA7326ULL, 0x14A805BF48D340F7ULL, 
            0x8EB60E21427BAEADULL, 0x2D7D2565AD4FDCE5ULL, 0x52FA7E427686C90AULL, 0x471EA10948F3947EULL, 
            0xDFF29A8F3114E9BEULL, 0x11A05A0A0B405ACAULL, 0xAD61ABE590A6CFA6ULL, 0x3F8A4493B52F9A88ULL, 
            0x3529D5F55175760EULL, 0x0382DF04F6AA0B89ULL, 0x856AEF74CE6FC2FFULL, 0x7E1B8518E29660F7ULL
        },
        {
            0xD929B3210854F963ULL, 0x928FA1588FC1B7F1ULL, 0x89C34AC569E97AADULL, 0xB2F449A4C14600EEULL, 
            0x511B787240AF5842ULL, 0x4B85E65BAEDD91EFULL, 0xB56A38C905C39EA4ULL, 0x356F6D85430F94B7ULL, 
            0x2CC6E119AC8E604EULL, 0xBC612FAF5CD4657EULL, 0x700D72EA16BBB7D1ULL, 0xB9230A4FC82B398FULL, 
            0x5B9DDACEE2541646ULL, 0x201FA7562F330A3EULL, 0x57E7FF5197F1CF39ULL, 0xBEED3013CA22DEC7ULL, 
            0x9381136792B0753BULL, 0x3BE2915B0CF9944DULL, 0x11A53065297C3B07ULL, 0xDC5372C2B4ABBF0BULL, 
            0x31393A4F21F48B38ULL, 0x6DD070811C25285CULL, 0x57B282A3108E723BULL, 0xB5BD5A023CA5CF46ULL, 
            0x1D77D16E3B4FD320ULL, 0x6E3C64ECA5D501C4ULL, 0x60A837783261BC36ULL, 0x1A1E7049CFEE6913ULL, 
            0x16E11D800FADC496ULL, 0x94B40E02FFE5AAD0ULL, 0x06A071EC0C211D1CULL, 0xCD536CBBCFDDE38BULL
        },
        {
            0xA80E355B2A0E3E43ULL, 0x357FB94E85D7A716ULL, 0xE3E4089F9016670EULL, 0x00EE2F0DC1CD6B48ULL, 
            0xD90705A5DCECC4BEULL, 0xF729B187BF7AEDA2ULL, 0x9926E04BDA0F7293ULL, 0xF28DA1C0448CD037ULL, 
            0x1814145735581C65ULL, 0xB3C0171F43127488ULL, 0x967D702ECBECB6C7ULL, 0xB906D4CC16AE35D5ULL, 
            0x99BF2A6A536211EBULL, 0x8859B20B0F2F7279ULL, 0x09340B521FD85737ULL, 0x74270F450510AA1DULL, 
            0xD3B95D0D3774F339ULL, 0x6EB3EB96480C7ABFULL, 0xE0B412BFEDF710DCULL, 0x5187B1602138FD48ULL, 
            0x16D9B545D9061677ULL, 0xBE82AD01F2614484ULL, 0x9C5588F637BF7D01ULL, 0xD0F98B26CAB24BFDULL, 
            0xF6CEEDC2A67ED8E4ULL, 0x4FEF020E51E24BA7ULL, 0xCB2DDCA4713A6ED4ULL, 0x0B64E0DF38683EDFULL, 
            0x4DB3DE4EA7960C95ULL, 0x0D85A4A52BFD27BDULL, 0xE624C8C278D67B26ULL, 0xAA27851EE5008D91ULL
        },
        {
            0xB838682E7502944DULL, 0x6A4552FBB80B7546ULL, 0xDC0032E735BD63A3ULL, 0x13EFB2802910E7D2ULL, 
            0xDAA4646BC76D3AD2ULL, 0x99311E66467DC646ULL, 0x72F7D105EFBE995DULL, 0xE6615DFF76371E04ULL, 
            0xFD6687C9F17E2567ULL, 0x290FFFC4F08D7CB2ULL, 0x957420F2E7AFC2AFULL, 0xBF307ED04ADEE066ULL, 
            0x992A1B02BE8D6C3AULL, 0x6DC6B25E05A82B3EULL, 0xE83EE6F5E1613DF8ULL, 0x7DA53C532BAEB8F9ULL, 
            0xD4E8A8449036DAF1ULL, 0x680EFCF0A67113A1ULL, 0x524733D5FB6E4A98ULL, 0xE429520D4C7AE92AULL, 
            0x204F9FB86300B445ULL, 0xBFE66889AA3E4474ULL, 0x01DA578C399920D0ULL, 0x97D30B00E7A27439ULL, 
            0x43B25300262A63C6ULL, 0xF83324AA12A99A7BULL, 0xA1C313052FBD5BE8ULL, 0x8E2053F8460F8915ULL, 
            0xEC3C63F152D579F2ULL, 0x8C1CECBDBDFD57BAULL, 0x1413C78D8CC5BD08ULL, 0x939F36BB4F9B1765ULL
        },
        {
            0x348F37AAA7827EA4ULL, 0xF5ED711BF1DE7CCFULL, 0x5459DE973E212420ULL, 0x0E7609965C3A89F3ULL, 
            0x27CBE6CE1C1356F2ULL, 0x4EB640E287A61F7EULL, 0xC90075705EE807BBULL, 0x0D6C33E62E2C9AA9ULL, 
            0xB67BA5AB7139E6A7ULL, 0xEF0E320C4BA2B7CDULL, 0x5DBA7C89B016CDC5ULL, 0xDD4B572CE881DF02ULL, 
            0xD732167AE56313DAULL, 0xD3F9E86EA1993C15ULL, 0xEB795AA4C9DE68BEULL, 0x9156572BA51BA3CBULL, 
            0x5B16E942B244E213ULL, 0x661E514393AA9A06ULL, 0x36C57617A6D20C4BULL, 0x8B9D21DC02EB0899ULL, 
            0xB78DB7AE745CCB81ULL, 0x91404DE4DA724F86ULL, 0x6A41D5BA89727A6AULL, 0xA1818AF747A6243BULL, 
            0xF1F54D849E0A0CC5ULL, 0x9C8250D8C91ADD1EULL, 0xAFCF60B6FA4B9A5BULL, 0x88E4039285EB60B9ULL, 
            0xDD9B53626DD90846ULL, 0x00F382A911441E4AULL, 0x5BAAE5D0F01C198BULL, 0x40F1B07A96049AE0ULL
        },
        {
            0xD808A5419357A3BCULL, 0x4723354A7980164EULL, 0xF64B1E4C79880BA5ULL, 0xB6C4D3B56C24ACEAULL, 
            0xE7E3A8892D59033BULL, 0xEC54C6AEA63B6325ULL, 0xE228429FF56B3F2DULL, 0x6D9F2CDBD50D53A3ULL, 
            0x5C74971327377B01ULL, 0xFF82D670FAE905F5ULL, 0xDF2A4A705618FA50ULL, 0x3CDE82024F65F4FCULL, 
            0x1AA3D777359AAE94ULL, 0x9BBADD93C3A127A4ULL, 0xEA0B5FDCAC1970F9ULL, 0xBBB059A703EC761EULL, 
            0x839DF0787AEEBFADULL, 0xAF27D84A105D3BC9ULL, 0x6EEC18550787A5AEULL, 0x9A9399FE2B096FAEULL, 
            0x03E1D0FBA853AF71ULL, 0x418BA2842ACAFAF9ULL, 0xF3BE0BFF80F3AC11ULL, 0xD93407017BB7847DULL, 
            0x9796880D82C2FF43ULL, 0x273C5768A4E95CADULL, 0x310C50BCCC15C365ULL, 0x8EBF34A0E7DEEC60ULL, 
            0x28CC94D4C47AC83EULL, 0x52B3BD117F13BC2DULL, 0x53291C49F8813F83ULL, 0x901965B8BFA8DD87ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseCConstants = {
    0x2270768F8EDDEEB1ULL,
    0xBD4EC3E054E1E66FULL,
    0xFED3EB097A3C1A52ULL,
    0x2270768F8EDDEEB1ULL,
    0xBD4EC3E054E1E66FULL,
    0xFED3EB097A3C1A52ULL,
    0x949C67483927084BULL,
    0xC780CEA9CE43546DULL,
    0x82,
    0xCD,
    0xBE,
    0x89,
    0x0A,
    0x09,
    0xC9,
    0x27
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseDSalts = {
    {
        {
            0x338A4FA5ADEC3E08ULL, 0x8A730291F8551B3BULL, 0xA781E780D5DF3059ULL, 0xBDCFD7616A0606A5ULL, 
            0xD6CEAA31D0095E61ULL, 0x672D6048B89C6965ULL, 0xC6514CE83938E002ULL, 0xB1B0C0A70D1CFE3DULL, 
            0x38070A02FCAAEB58ULL, 0x1A21617AB1967431ULL, 0xC268102E29171AE1ULL, 0xF3A8DDAD1896B207ULL, 
            0xC1EBEF36A3F765B5ULL, 0xD90252725F9C061DULL, 0xBA9359A6220DA98FULL, 0x6F1C9DC8D94E4F88ULL, 
            0x41A058C0D049A979ULL, 0x0FF486A8E8806F5AULL, 0xD4AC1D1A2DEC523BULL, 0x8AEC768A550571AAULL, 
            0x93EFD7A67A8BA6AFULL, 0xEFED4C3964A44ACFULL, 0x815A8C2B21EB93A7ULL, 0xC7AC38A4BA91E65EULL, 
            0xA4B276617FFD4194ULL, 0x65E38E710C6EEF8FULL, 0x0AA3427698434D3CULL, 0x65E4FC263E517873ULL, 
            0xB2775A5EB1B8B23AULL, 0xD85261043A4ED793ULL, 0x3923922B2B11E695ULL, 0x9491729AFC16D2DAULL
        },
        {
            0xCA122F0360FE34B6ULL, 0x0C42A31B56F436E1ULL, 0x1839778E04B157BBULL, 0x1780B02FF6A57B5DULL, 
            0x055947C3A2A00C9BULL, 0xF59A90B4F34B7C7BULL, 0x4F42BA2BAF5E9145ULL, 0x4692F9FC4595AEC7ULL, 
            0xB606CD29E33F0195ULL, 0x891CED5F2F77D20AULL, 0xB9CC755180EBE1C3ULL, 0x398E95243A50326CULL, 
            0xF46423BA9E0061FEULL, 0x3E2B067BE8F52C71ULL, 0x032D2031BCA18A05ULL, 0x5B62B18B2D8597FCULL, 
            0x36A647964A0AB31AULL, 0x6D9F18C751BD5128ULL, 0x9BB9E251BB2F3250ULL, 0x2F37E19C4BEBE01FULL, 
            0xAD750BEA1977A872ULL, 0x8787EC8775CCE486ULL, 0x1E5539DD880C2CCFULL, 0x3B98B766BA30D58AULL, 
            0x014E2D7E1AA5A598ULL, 0x11693839A67CE0C8ULL, 0x011B83E9F65B1A9AULL, 0x116C78BBA6A29E35ULL, 
            0x06D05A138EFACE89ULL, 0xF1FA6F6137048A32ULL, 0x233A60C14FE2B473ULL, 0xCF02470C408430A2ULL
        },
        {
            0x88F2C0947464B08CULL, 0x9877ED112D4BD1EAULL, 0x9A8EEFBCF408AED1ULL, 0xD89212AECE3C46C5ULL, 
            0x150E7FCAEFB6B6DBULL, 0x851B4890AF927EA1ULL, 0x1B2EC6A5E077253CULL, 0x2063CAE0961D78D0ULL, 
            0x3B6371D7C9A0EB86ULL, 0xBE9EBCC32BD3A8B0ULL, 0x7A4E8DBCFEE71D7DULL, 0x84138F405DDAC544ULL, 
            0x30D6B9BBD8C0D949ULL, 0x0F9861FDBA888F47ULL, 0xC2C68A7463A39F77ULL, 0x453F64175E570596ULL, 
            0x998B78E917C10278ULL, 0x16719F8A7337F63EULL, 0x253F811909F179B9ULL, 0x6250C735B1140724ULL, 
            0xC80AEDFB2CB1C42AULL, 0x346042CCD0756E0CULL, 0x47742F4FAE7F722CULL, 0x5E92A4FF6495F24DULL, 
            0x752A74727328FB8FULL, 0x07656F191C0DD292ULL, 0x1C9F7367C2864B56ULL, 0x0D864540FE535B69ULL, 
            0xB7E1E220EC0E2835ULL, 0x3DA724FA19401532ULL, 0x712E9FF8CA15C5A8ULL, 0x77390D803ADE044EULL
        },
        {
            0xFA2330D5B10EE137ULL, 0xDB86905398FF3B6EULL, 0x49EDD7ECF1076CC9ULL, 0x3B5C37227DB8CAD7ULL, 
            0xB46D5AA33EBBE5A4ULL, 0x470191DE0B1A92BBULL, 0xE5EBD43584191C6CULL, 0xBB9AAA2952B339F4ULL, 
            0xC893F37986B485F2ULL, 0x758E9C4B9DA67998ULL, 0x408698DFCBFCEB8AULL, 0xA2D67EF1254474DEULL, 
            0x5417CB2C88414934ULL, 0x940E4927D942757FULL, 0xFD1507BE5B021368ULL, 0x8B98A8022602887AULL, 
            0x21FACEC0BCB7BFADULL, 0xA4BC1C786285F484ULL, 0x540929457BA805B7ULL, 0xA135D0341149D2F0ULL, 
            0x748026C2D7915A52ULL, 0x4363CAB293A4E5B0ULL, 0xFDEB55ED97E9E436ULL, 0xE7F315EB83E5CE72ULL, 
            0xC5DDF30B71337237ULL, 0xB2AAF60B79D93EE9ULL, 0xDE6D16204E5B992AULL, 0x6DC7B1D04D457B27ULL, 
            0xD0EF275FDFDD6F47ULL, 0x5071A39C2155D40CULL, 0x4F116052284E822EULL, 0x4BB12A1E78B2BB75ULL
        },
        {
            0xF67CFBE85DB7EDC9ULL, 0xCF7D54B8EA64C41AULL, 0x4F307FF9E91C2EE4ULL, 0x73D0009DA41F4D58ULL, 
            0xB53963AC20AF7AD3ULL, 0x82D96FA1F7A8938EULL, 0xD8F2781E6C62E604ULL, 0x503DD780FEC065D7ULL, 
            0x05E1E99AFC98FEA5ULL, 0x3F545CF042C81152ULL, 0x4D18DBCB8C2DA5F1ULL, 0xFA8F43E7B4EACEC8ULL, 
            0x20144482B12A27E6ULL, 0xAB3793E28D740600ULL, 0x655628A47D9AB4FAULL, 0x66207D0D4BC20065ULL, 
            0x0AEE0B93314FAF8BULL, 0x06D7B2DF3355F68BULL, 0x422B83B83EE1440AULL, 0xC27915B28B7AF6ECULL, 
            0x846E9D62EEB51D24ULL, 0x98DCD6D9423C1E11ULL, 0x0C9313188C86E41AULL, 0x0BD15DA99E95A8EEULL, 
            0x83DFEB4CA644CB23ULL, 0x1135281D58230461ULL, 0xF458D9C19950E80BULL, 0x481DE4AC5F9FF3E0ULL, 
            0x37BBE681577D0D29ULL, 0x5F8FAFDA5FA783A2ULL, 0x1B5D9A0F308CD45BULL, 0xFFE2CE18903DFC9AULL
        },
        {
            0xDB05C9F079EB5FABULL, 0xC13F4A38DF73D659ULL, 0x6A36614147130A8BULL, 0x4DD12D6AC3A1DFCBULL, 
            0xB8B47A6445FE72F6ULL, 0xBF1CBAF91B4A292BULL, 0xF21374DA37C96207ULL, 0x03EB78128B1B7911ULL, 
            0xA476D282B7C9953BULL, 0xA64A8439DC3C9DEEULL, 0xB3FF8AE54081520BULL, 0xA260880D490F6269ULL, 
            0xEB190D28B8370B90ULL, 0x765A10730DE06535ULL, 0xECF359B5EC036D6BULL, 0xD1568637FC01B62FULL, 
            0xEF81A522E960E3F8ULL, 0x56594ABCDC8EB030ULL, 0xFC078224F83C8C8EULL, 0x0164132C423C88DEULL, 
            0x0D63F39BC5E221A1ULL, 0x6DF8DD9679861FCAULL, 0x42DE698EA90000E2ULL, 0xE6C6D70E6216128FULL, 
            0x61A093CECBC38C58ULL, 0xEFEC80BAE2BBBACFULL, 0xE8D2EF1DE3859BA3ULL, 0xEA600F8F374ADD40ULL, 
            0x5EBAEF95DCD1A01FULL, 0x9CCC68420985FC22ULL, 0xA54BBC0B8611970EULL, 0x505D81B62F736F1BULL
        }
    },
    {
        {
            0xAD5E117E91B334BCULL, 0xC242EF365414B683ULL, 0xA06CBE84E4E57CDDULL, 0xA8DEFD0C47D2EC7EULL, 
            0x245B54AA8ACC783BULL, 0x5BFB8C72492E04B0ULL, 0xDEF0304052585FDCULL, 0x18DA22F84A65E4C3ULL, 
            0x06C93256DAC9FDEFULL, 0xB8A9E19294D7CBA9ULL, 0x304F0672D8734662ULL, 0x8F89C98E8B454375ULL, 
            0x9F545E3381EF07DDULL, 0xD3AEB39193EFFA09ULL, 0xDD60ACBB1996541AULL, 0x064D6AB2F1EAA0D7ULL, 
            0xD4350621824A11C2ULL, 0xD7B2834D89CE8026ULL, 0x6F0B6FF4AEA260B2ULL, 0xE25E5D5057B042C5ULL, 
            0x07526819D814AA1FULL, 0x7BDE0E7C782DC33AULL, 0x927456461FCAC3CCULL, 0xBEB7B72BFE0D8540ULL, 
            0xAD7872DA5011EEE5ULL, 0x87ED58C6D96B4F80ULL, 0x0A09B943E28371A1ULL, 0xF2FA6A2144694CDEULL, 
            0x92E3C607D55000D3ULL, 0xBFAF914CC38613F2ULL, 0xFB7E82BE3E938C28ULL, 0x16FEC7A41574A994ULL
        },
        {
            0x547777B7B83CD4E0ULL, 0x993FA1E07DF99B7FULL, 0x7AE5C4CB3754292DULL, 0x5DCD660C3FB0A6F8ULL, 
            0xDACAC91EC6CBA71FULL, 0x524F826550E87AB9ULL, 0x8319EFBA3612B04FULL, 0xE2B6A005266442FAULL, 
            0xA3403813749386E5ULL, 0x57B0A1E2065AB3C0ULL, 0xD6BBDAA529E947CBULL, 0x6AEAD476F790F3F7ULL, 
            0x1A8072DB7A376488ULL, 0x30EC750399BAC9F6ULL, 0x23C7DAC928F52479ULL, 0xBC8FCCB2D71320CCULL, 
            0x22901DAC60E1109BULL, 0x33BD3401D581C933ULL, 0x782D900F93CC7187ULL, 0xA77AAE3CA0710CFEULL, 
            0x0CBA0558C9221137ULL, 0xDBAF1FD3956A8A22ULL, 0x5FD5E16E41F9C73FULL, 0x9AC88D3DCF4AD93AULL, 
            0x220646CD80382EE3ULL, 0xFC79BC98BAFA7401ULL, 0xC466CD086FE1981DULL, 0xD2856426D64CC198ULL, 
            0x23E41F30A994521BULL, 0x388F2D87E9F6BC06ULL, 0x39A6627B8ED1F1EAULL, 0x388686BEA8499CB9ULL
        },
        {
            0x3D784954DFD1E49BULL, 0x14C399F7232F230AULL, 0xDCB4D0E8FE6E6FB3ULL, 0xBD0596DFB09D39BCULL, 
            0xEFDA054207A23B9BULL, 0xF7159100BEF57AECULL, 0x154C9424ADC6C862ULL, 0xF33A1321F608A230ULL, 
            0x84418EBB8D813905ULL, 0x90885BB3CD11316CULL, 0x8C9083EC62A99612ULL, 0x5F287E8AC129B663ULL, 
            0x15BA5C9DB61333BBULL, 0x109596B5F9EAC3A5ULL, 0x6E5D490B7A44FB89ULL, 0x63FBE24CF93974E1ULL, 
            0x008E6A3C6DBA690EULL, 0xDFEFA4481796CBC7ULL, 0xD7D03E5D6BF953D7ULL, 0x95A65DB7492A3AB8ULL, 
            0xAFA116D59D9C2954ULL, 0x5322CA235C43867EULL, 0x1B006FE53685E5CDULL, 0xB62D669F5EA40A42ULL, 
            0xF8EA49F124E0E0F0ULL, 0x992F9E71B2EB5790ULL, 0xDB7868AE1DD46B00ULL, 0xE6DDABA84238A740ULL, 
            0x70F97BCB8557E6A9ULL, 0x15F3F6539370C166ULL, 0xD45CEA4FB9138E54ULL, 0xC26C2440AFDADC3CULL
        },
        {
            0x60C91456FF51FD5EULL, 0xD6A49240692CAD8DULL, 0x0B0823F01C526FB8ULL, 0x5D85F9316532EAC7ULL, 
            0x13379052C3F2649FULL, 0x194E0D9AC08DC555ULL, 0x2A2BF8F0CAA85189ULL, 0x958C0F8DE6C7E4C1ULL, 
            0xCE35B8BA1168A5C7ULL, 0x9EA72392C0E3356DULL, 0xA4272770682D16F7ULL, 0x6A4DF77EDCB263E0ULL, 
            0x2CC585B8F532AAEAULL, 0xD7B79C40A98B5C0EULL, 0xA9AB3B314A561241ULL, 0xD8457AAAF0A48AF9ULL, 
            0x3685DA6E1BFFA1A4ULL, 0xB29495A514024D0DULL, 0x30D0E0C70C6BCFF0ULL, 0xAF2A6AE2E019F728ULL, 
            0xD0F90018B84AAAD8ULL, 0xB599F6D2355F94DAULL, 0xB9985F4F1A7455D0ULL, 0xCF98206DA02B2FE5ULL, 
            0x300236F229FFFCBAULL, 0x89A9EF1FA03FA702ULL, 0xE5D872CE4CC48A0BULL, 0x926F2A2FCE0F8B38ULL, 
            0x90608684A52CB4FCULL, 0xA6A17D41BB4ECD46ULL, 0x26AC630C5057E137ULL, 0x3414B934AFC581D0ULL
        },
        {
            0xFF2629FE6F99F568ULL, 0xFE012D74DE53E7EEULL, 0xE8DA2A727BEC3EFBULL, 0x3D39F2DFD7F24A47ULL, 
            0x30228B3D07CB147CULL, 0x32D4241633C611B8ULL, 0xB64E98F88576FA23ULL, 0x0FB997B6D5A39F45ULL, 
            0x8336D13D29472AF4ULL, 0x16A34648789C577FULL, 0xD1641E4A0C8674F3ULL, 0x2843E4BEE7D72E87ULL, 
            0xBEBE86A82FD05468ULL, 0x04BF62892EF065DEULL, 0x6F728822436D566EULL, 0xB1E119B551A73E86ULL, 
            0xA60CEF268ACC3A30ULL, 0x3155075128455478ULL, 0x324E7E0416C052F4ULL, 0x0F6719CE10A0117AULL, 
            0xEBB038DC8095D991ULL, 0x50703610ABC80BCBULL, 0x7F7A6BEDB5F6D09DULL, 0xC4A16E678843B87AULL, 
            0xEE429DE13E959AA2ULL, 0xE15B102247A0C84CULL, 0x25DCC53BA9719ABDULL, 0x0DBCA3D790334666ULL, 
            0x5015779F868A541BULL, 0x06385BAA42DE2908ULL, 0x8BB934F8D23D4221ULL, 0x27A152499470F513ULL
        },
        {
            0x4467A824DBE92399ULL, 0x86A2864FAFFAE15BULL, 0x18CDD7C21F2CAC21ULL, 0x6F66E96A32CA1795ULL, 
            0x18C94453E2810714ULL, 0xC6D7BAB85F6355D0ULL, 0xEBAC0390C8071EEEULL, 0x01058755D31FBDF6ULL, 
            0x21F67C7484CE32A5ULL, 0xD0EC7F0744FB353FULL, 0xE85931198FEDFCEAULL, 0x29B3055EF9C22948ULL, 
            0x24E8BBC3BD8056FFULL, 0x28ED141F17B3F4B7ULL, 0x7196E0F83611B088ULL, 0x3F859141051C95CAULL, 
            0x8E19873E878F261FULL, 0x6BD8C4C58EE7F965ULL, 0x3998C40129ACFEA3ULL, 0x6BF33E84720152DCULL, 
            0x3D434D61EE7C3D1BULL, 0xEB257A4BC5BD4D1AULL, 0xCF6DFC6BD7311EB4ULL, 0xFFA026F692142BDDULL, 
            0x6987C8936BD5D58BULL, 0x050DB210A2650992ULL, 0x69A36B37A891DD14ULL, 0xD245303CA788836EULL, 
            0x43605F4DC099D573ULL, 0xED59F5B27680D62AULL, 0x2BFC9EB57AC59D5EULL, 0xC0DA5F141ADF3FE0ULL
        }
    },
    {
        {
            0xD0B4EA32DB7336B1ULL, 0xB4D26DF7ABAE0D29ULL, 0xDC0594F104D45A55ULL, 0x189C8CD5F5E788AEULL, 
            0x700C8D3696F986AAULL, 0x0FB78D99FC493038ULL, 0x25BB564321061241ULL, 0x53021F8B2A43161AULL, 
            0x9AA2C455F1C28D4BULL, 0xBD174E2DCE55BCACULL, 0x938A1FA47BAF4BADULL, 0xF955B47D4C1569ADULL, 
            0xBC1E24B9ED4B3D6EULL, 0xE54FEB18F46C8327ULL, 0x425F1358B1EC981EULL, 0xDE4BB96A867DB795ULL, 
            0x09261563AA08A5B8ULL, 0x0A93AA2EA88ED047ULL, 0x2B5F577A3DEB5547ULL, 0xD2151230FA55DABFULL, 
            0xBA4B05D9799714E7ULL, 0x03EAE3BB3B3E9F83ULL, 0x2EB45C2627DB56FAULL, 0x6734EDE5FF191E40ULL, 
            0x938AA2B10CFEE7F8ULL, 0xC0B9729C0BD3B1C5ULL, 0x4BD3B307BC46461DULL, 0xAD44553AF99F5120ULL, 
            0x724752061C10F2ACULL, 0x39832DC900E44A47ULL, 0x8591A80893D7EF2FULL, 0x122A03E000EDD6F7ULL
        },
        {
            0x977BA66A021C1E45ULL, 0x31F31BD0E2054D2FULL, 0x8DF3A83222B93515ULL, 0xD193BB6CCCE5F96FULL, 
            0xD95E36AE2A417BFBULL, 0x2AFE2F86A1600D0FULL, 0x6B9C1CE1BAD1C7E5ULL, 0x354354A5ADDBF649ULL, 
            0xF231B069DC3A607CULL, 0x08AD1323C2684F56ULL, 0xD1F5895788FCB19DULL, 0x264FCDBF07CEF50DULL, 
            0x9A16686E53CA457EULL, 0x741DE98549129D19ULL, 0x456DE3B86FC60D3BULL, 0xD8B50F7DEA2E3063ULL, 
            0xC93CCD95036C01A5ULL, 0xC5B67038175D403AULL, 0x1B912B697B9DDE41ULL, 0x835CE33B72882D6FULL, 
            0xE8C564D1988E874FULL, 0x37FC47C87EB7D2B5ULL, 0x8FCE1440CDE70E92ULL, 0x3BDE54A2A2DB2CB1ULL, 
            0x32A105CC69F466F8ULL, 0xC63DB6FAC6B43998ULL, 0x00ABF2912D556064ULL, 0xABBBCCBAD63E84B2ULL, 
            0x4F4C36604D7F6D4BULL, 0xC3D75A025636705DULL, 0x85A2104085A8A458ULL, 0xB7C9EAAA4D020927ULL
        },
        {
            0xBBB6EF942E333346ULL, 0x9EB5CD20D975943CULL, 0xF3DE6E7D6A647976ULL, 0x8C598E74D7658995ULL, 
            0x6F78F35091022A7FULL, 0xBE9549E6DFD280D6ULL, 0x4279C2262CCE9BFBULL, 0xF4E189FEBE315664ULL, 
            0x3224811FB9E70D1DULL, 0x4BEFB3FD7B9891FBULL, 0xB6562910A3364E0FULL, 0x75FFCC77BD034049ULL, 
            0xC86510952A84D3A7ULL, 0xBF335D7D251B7E0DULL, 0x9869F4B841AB9551ULL, 0x6378453CA69013ADULL, 
            0x10017D8BB40B225CULL, 0xB80B8FD02F0F2271ULL, 0x8ACADC7F7FF91D24ULL, 0x513C89054FA0FF08ULL, 
            0x8029B99C326AD403ULL, 0x5805B459B46541ACULL, 0x8A9B870348A367B5ULL, 0x2EA2DAB8024DA25DULL, 
            0x25545911E0B12AD8ULL, 0x6E5FBD447C107B4FULL, 0x6B5C161798D035B1ULL, 0xABAC24FDF63FBC5FULL, 
            0x1A34FBCB58C66E67ULL, 0x7ACBACBFC9B47716ULL, 0x6B26066F3D2A7FE2ULL, 0x20BAD39BCF21237FULL
        },
        {
            0x0572838785B1EAB8ULL, 0x57B217A821569A98ULL, 0x051544FB7C7B19E7ULL, 0x30471E4FDE4555B0ULL, 
            0x598EFB8C33562BB8ULL, 0x653EA645146DD332ULL, 0xCD9A54D2B964E274ULL, 0x0EC07A5510D3D189ULL, 
            0xB8602E33CBC8563AULL, 0x582F23311A435D33ULL, 0x129027D4930EAA2FULL, 0xF1E580ED5EFFD8DDULL, 
            0x7A3553248044885FULL, 0x5E66321F62C5A175ULL, 0xAF969C29E3FAE8AFULL, 0xD18853A94F375A5EULL, 
            0x766D05EBC7378344ULL, 0x42A4A7694C5E06D0ULL, 0xA322983DA8BA7600ULL, 0xEFEBE85769BE8F24ULL, 
            0x0DA8B38C1E70234AULL, 0x614BA228A2A308AEULL, 0x399C20F9C6136E5FULL, 0x0086F33D51818563ULL, 
            0x68F3538965E3A4E1ULL, 0xD21ADB23A6F2E150ULL, 0x35B8DCDE7CE64DB8ULL, 0x5A5B1CDB351CD940ULL, 
            0x57526C110FEC205BULL, 0x81B9515FF86E4BDFULL, 0x8305FA6D70AC6AD4ULL, 0x710A5EA0DC81D9AEULL
        },
        {
            0x5E2C46C601705AC8ULL, 0x7FB5EB76C0F4A9E8ULL, 0xB8B8EA18C36F7F7DULL, 0xBAF62FA045D1C51EULL, 
            0x26F0E99DE2AB4E36ULL, 0x9F77571C3058F1C0ULL, 0x10EDE816081D4C86ULL, 0x0693FBA9727BA9C3ULL, 
            0x1EF33C77582EF139ULL, 0xBC395D2DBEF828FDULL, 0x8CB6D390217FE06EULL, 0xA37BDC06C53EBF64ULL, 
            0x0A68364A0E32ED9EULL, 0xC6A8FFDECAEA6B46ULL, 0x17C56688801B909AULL, 0xCD23AE7C11CDC9C2ULL, 
            0xE140343D7228E054ULL, 0x03D7D9E6A090FA98ULL, 0xC8057968A2EC7DBAULL, 0x676E95619334B272ULL, 
            0x3E6BF2F2FEEB92BAULL, 0x9D97F5D8782A62B0ULL, 0x2AD38781A50CEF69ULL, 0x1F55E8CACA0C5C5FULL, 
            0x930B10751A14BF14ULL, 0x201D913BAD7BD028ULL, 0x9E54D2D0E888F1E2ULL, 0x2A5C1AD8592EAFA6ULL, 
            0x0F288AF782684CD6ULL, 0x61D205F14AF7BB5DULL, 0xD11F877D3184BD94ULL, 0xB7CBC6D23289D698ULL
        },
        {
            0x7EA3D1DB231417E9ULL, 0xBEC00CF84FC5A105ULL, 0x89D532F50AF8E1FEULL, 0x543A880023205F73ULL, 
            0xD1A6D9BAD7011CD8ULL, 0x8C1439DC2200F268ULL, 0xF86609DA6A9432B7ULL, 0xE2474FCC1DCC232CULL, 
            0x6CD184E18BA7547BULL, 0x6DB77F6A425D6D8BULL, 0x501FBF9207806B81ULL, 0xB257017D2C63F310ULL, 
            0x6D26798E9883BE71ULL, 0x145A57DF8636C9DEULL, 0x87DC3F8127D838E0ULL, 0x9A5A0327E21BDC5AULL, 
            0x9E553A23426FEE43ULL, 0x1EC27A5D24B30041ULL, 0xCCF8DE462896DC05ULL, 0x35A6363F8D2F0800ULL, 
            0x24724993FC55D6F3ULL, 0x1C90D61B9CBAB0C8ULL, 0xDC353B3C0BEA8B34ULL, 0xED9A39C330FDB09EULL, 
            0x76EBDE94524F3579ULL, 0x26049121F401A393ULL, 0xE0C75AE69DAB9B8BULL, 0x721B61EFEBA30090ULL, 
            0xEDC70896E171B11AULL, 0xD2F041E467A23EDAULL, 0xCD261A58146F0C78ULL, 0x031CDA6896EB67E2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseDConstants = {
    0x98D5BD91D6FF63C1ULL,
    0x4633903D81F7C0FEULL,
    0x6C95BBCE8D9F2814ULL,
    0x98D5BD91D6FF63C1ULL,
    0x4633903D81F7C0FEULL,
    0x6C95BBCE8D9F2814ULL,
    0xBA5C02CCC037E236ULL,
    0xB68638BDCF79C5C1ULL,
    0x67,
    0x4A,
    0x2F,
    0x73,
    0x1C,
    0x52,
    0xB6,
    0xAE
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseESalts = {
    {
        {
            0xE4E2DDC5B16FB193ULL, 0x43472002AACEE4C2ULL, 0x5BB3CB3689603BBDULL, 0x3CBDC225E98CA724ULL, 
            0xC24D199981E88EBFULL, 0x77D1404202CAB51CULL, 0x709A6FEFF6B6060BULL, 0x9926DE0445143EA7ULL, 
            0x7D0EE8FD1D5464ACULL, 0x0A4FAD1F1B14D293ULL, 0x86F5AB295F1384BEULL, 0x4ACB5DA8E72197D0ULL, 
            0x378DE265C856122FULL, 0xB0FDACCF860EDA04ULL, 0xF532D2AEB46FF074ULL, 0x35EB397BD871B177ULL, 
            0xEF55EC3930BAE5B1ULL, 0xF403826E593E4B88ULL, 0xCF8F76ADC5BA7320ULL, 0x4C1BFBAB2AFF1FA6ULL, 
            0xC6002CC7018489BCULL, 0x2AF648916431CE5FULL, 0x5866CBEDDAC7A8FAULL, 0x53466FEC301CA676ULL, 
            0x37B57A5B04338638ULL, 0xCA1951BD90AE5937ULL, 0xFEA831C488871966ULL, 0xF7CF4FF946622556ULL, 
            0xE60D1B0032C0DDD3ULL, 0x7538A4EFC5DB91A7ULL, 0xCD974BE2452A82E7ULL, 0xD84C9807C94A5397ULL
        },
        {
            0x4155AB832F8A8DD1ULL, 0xC17E7DF13D245145ULL, 0x6132EC0626276A39ULL, 0xC01FCFFF4918921BULL, 
            0xA9B9F73E07168B93ULL, 0x75E04A8EA5CACC65ULL, 0x7CAFE3E0110858C7ULL, 0x05CFBD1CBE2F5435ULL, 
            0xCDDA95FD30F34640ULL, 0xE57B577014699C4DULL, 0x40CACD0C77AEBDCBULL, 0xF64256DB5506B93CULL, 
            0xFA7A9549ED8AB0E2ULL, 0xEF64F009D0804E50ULL, 0x8B066582FC28E852ULL, 0x72E1216387713EC4ULL, 
            0x6E2B8938E0168C6BULL, 0x3400B512002ABC90ULL, 0x3DA1BCA2FE692FBAULL, 0x002193BE7D57FA5CULL, 
            0x23E5E7D332BFAA19ULL, 0x8E0BE78FE4FA2B79ULL, 0x53237883FD37310FULL, 0x0A741C41897A2FDAULL, 
            0xCBB310597472C995ULL, 0x8361D8FF7AB7415CULL, 0xEEEAF8B09A144687ULL, 0xDBFA8CBD4F829E18ULL, 
            0x3266D33E2EB1A382ULL, 0x888AC3306BF604B5ULL, 0x9ACA9944BEE30845ULL, 0xE21DF9731755A8ACULL
        },
        {
            0x44FA38009415A609ULL, 0x600DA2E1F620CF4FULL, 0xDFD5B6C53DD81D90ULL, 0x1F94027CD1B1F55CULL, 
            0x1D16EB1D0A248810ULL, 0x423469DB77283021ULL, 0x09AB2E0F3CF105A4ULL, 0x5DB99E29170CF584ULL, 
            0x358F51EDBCFAF583ULL, 0xAA8D85A9E0F41508ULL, 0x9252B762722FE782ULL, 0x140404128C7C1FADULL, 
            0x7DE52B312D2205F8ULL, 0x315E20A6E06A1647ULL, 0xA47C0CB42D5779BFULL, 0x4993E84EC9042D41ULL, 
            0x556EA19CAB8DD5BFULL, 0x2DE64319A807C435ULL, 0x30ED7D93D13272C8ULL, 0x0BAFD21F9FDEE96EULL, 
            0x8D967B757409EE78ULL, 0xBB893EF2675E8EECULL, 0x8C3C96B88719CBDFULL, 0xC09B5C4EDC792474ULL, 
            0xB6D08FA9D542BCDEULL, 0xB01DACEB7D4EA698ULL, 0x1CE18CB8AD7A4972ULL, 0x2B2F66B9133D8C33ULL, 
            0x45D62535C2B3BCE8ULL, 0xBDAC5ADE2DBCF0CFULL, 0x57880A7678CD1314ULL, 0x47EA2C9560AF6CD9ULL
        },
        {
            0x34EB7874497AE790ULL, 0xA423A9BC39CFB1A3ULL, 0x4C7CC227C2CB7000ULL, 0x4FBB08BF6E5127C8ULL, 
            0xC2C74BA2A98C3472ULL, 0x1C500DE3F0981636ULL, 0xA3AC4B9BA0548FBFULL, 0x34913667CF29FD5AULL, 
            0x806052A3B8713AB1ULL, 0x114D979E0153E7A8ULL, 0xBD421211EC89728EULL, 0x0D76627C8177494BULL, 
            0xEE4FF5E8B28E8BE2ULL, 0x7ECE4406E9CDCDB0ULL, 0xA56CBA00BB4557C2ULL, 0xDDE8C96C9AC94582ULL, 
            0x37891BF38413F231ULL, 0x9B12B0D198F2C884ULL, 0xAB1AF277A7F2F485ULL, 0xA7550696111F9C1AULL, 
            0xF56E06E59FEB83ACULL, 0x1E6604E9983BBB30ULL, 0x4E6540F603FE83F3ULL, 0xE2AFCC69B7DA5E8FULL, 
            0x85C80303EAEE2FF7ULL, 0xAE8647217FB6E2B3ULL, 0x42019B4704FDFD7FULL, 0x3D2F09DECD3AACE3ULL, 
            0x8EDA1D14F89CC66DULL, 0xE0CDB2E1CBC2DA62ULL, 0xCCA910003B2A311AULL, 0x0ED775BE44F0AE5CULL
        },
        {
            0x5CFDED583DF92A39ULL, 0xEAF15D644EE6C680ULL, 0xB02A86B28AF327B0ULL, 0x8556F260F5E94F78ULL, 
            0xC8247E010082CE2AULL, 0xA9886BE38E6436EDULL, 0xBC13E9BA067F2B97ULL, 0xF0190080D766C022ULL, 
            0x3D389CD879D8D256ULL, 0x20417F3616686D92ULL, 0x6C1FECFCCEAF88BCULL, 0xFB5497E13E696EA3ULL, 
            0x5D2A3FD38B1BAA78ULL, 0x7A5A7D531F5FB42DULL, 0x0A79A3E9D3DAC099ULL, 0xD6741E03EEAAADB3ULL, 
            0x0B149B375DE5A784ULL, 0xB50547E426BF31AEULL, 0xE585F3B9714BD553ULL, 0x6B851D8F7D978A4EULL, 
            0x2CB52ADDEEC663E8ULL, 0xF1F92F7A8D017034ULL, 0x7C3CA3E08F0890FEULL, 0xB3613359792DD7D3ULL, 
            0x2043A6678EE3F4F1ULL, 0x446EA8A9C6668DF2ULL, 0xDF9421FAE88F4A58ULL, 0x41E42FF29A12E992ULL, 
            0x89773EFA2E9B7B4AULL, 0x4B40353E21A30DB0ULL, 0x72DA1F6B96F1DD00ULL, 0x992B2181704D479AULL
        },
        {
            0x3396C32E308F623BULL, 0xF5588FF4CB7DC560ULL, 0x12407E62F69C57EDULL, 0xCF0B1C886AEE45CEULL, 
            0xB139DDDAF6DD7406ULL, 0x80B43D41F105701CULL, 0x846E3293A4071A2CULL, 0x878F79F210AE38A4ULL, 
            0xD2512CC89C1EAF3DULL, 0xC7C9C012E7F09EC2ULL, 0xB1E586086AA946B8ULL, 0x2EC8027C0EDEED58ULL, 
            0xCCACE07A45C2A844ULL, 0x968BB4730A9E47E6ULL, 0xF71545C9D212A183ULL, 0x265BA45A2D11897BULL, 
            0x2AD5B1B48A071926ULL, 0xB4F26DF7FACE2C62ULL, 0xBB11AD19FDC0E3F6ULL, 0x5279848DFA86476CULL, 
            0x5D40422EEE77BFB6ULL, 0xC5F327B8441F3533ULL, 0xBA5D55872F83A506ULL, 0xDA85FDA2CB54E71EULL, 
            0x2E1A23B4126BD5B8ULL, 0xAF651E9D006D494DULL, 0x8B17858A6F11EB9EULL, 0x7345FEDCE10C3C5EULL, 
            0x43B404DAB2A5E7A3ULL, 0x75AC7297299703DCULL, 0x783692FD4BF3ADB5ULL, 0xF724A6E5D350289AULL
        }
    },
    {
        {
            0xA5F2375C758A866DULL, 0xA405542EAE39FBD3ULL, 0x031119C8A77FCCB9ULL, 0x118B4CA7B6F8E255ULL, 
            0x5CE3ED398E8CE22AULL, 0x83748B17E3751968ULL, 0x2EBA97C90A34A218ULL, 0xECAA88800C7433A4ULL, 
            0x866C94637FF7E581ULL, 0xFA95A57FE57E5832ULL, 0xFE363D66D25CC07BULL, 0x20B36E3F2892C3A2ULL, 
            0xF7D3D2DD10038943ULL, 0x3FC072A552325C1DULL, 0x530A2220B1223D97ULL, 0x19C7BCB7E734FBC4ULL, 
            0xBAC9A35A01282DEDULL, 0xC0CF3A051BF40F16ULL, 0xC1858E780499E29AULL, 0xA850D8175E32091EULL, 
            0x54F99E4C1D28618FULL, 0x721A72C40B709DCBULL, 0x4030F5BE8D6A70DFULL, 0x4C93BB5173AFD779ULL, 
            0x0C96BF42EAA95679ULL, 0x8185448050CA15EFULL, 0xC7C7740F7CA97999ULL, 0x3D7F4816DF0515B2ULL, 
            0xE4ECD7F07A915BB4ULL, 0x23C2C38D44030666ULL, 0x68397DA8CE721682ULL, 0x5B6B1AC91FAF8D90ULL
        },
        {
            0x26D3787333F4FF51ULL, 0x10CB5FFB0611B780ULL, 0xFA680EE673CB778FULL, 0x52C3B4BAA0837D3CULL, 
            0x1622CC77EDA12777ULL, 0x4A6AF23534B5EC1BULL, 0xE6BEE9DAB544A210ULL, 0xE569D6D9E36CE00BULL, 
            0xEF138A81AC914F43ULL, 0xDB5B6FD1CAB7D248ULL, 0x3B7BF117F0F8132EULL, 0x5827A9730E3E12A6ULL, 
            0x8221A37AFE02C9D0ULL, 0x13BF33B182FBDFDFULL, 0xD94C8FFA69151DF1ULL, 0xD0D48E6C76C27046ULL, 
            0x17C24BA8E39B35D2ULL, 0xBFEBF8F91586B9F5ULL, 0x4ACB9F73CF6E28EAULL, 0xE950284A8F80F627ULL, 
            0xC04ECF9F814B9A7BULL, 0x2E11C6F90C92B824ULL, 0xAA422497C22388CEULL, 0x26A683BB90994132ULL, 
            0x2FEBAC039328C928ULL, 0x207C2978184BE6F0ULL, 0xA65075C150CE47F3ULL, 0x07E49DAD130C6CCBULL, 
            0xA726F0DEEC000806ULL, 0x6C7CC79C5C2085B6ULL, 0xE05549DFDC243A39ULL, 0x5F54A8A80B5F22F9ULL
        },
        {
            0x53DC683802A51D2DULL, 0x2900981AAEEAD431ULL, 0x27DF8332BC7CB816ULL, 0x64CD2B2257FCF554ULL, 
            0x952B342996DAB12BULL, 0x8035CFF4D51ED30BULL, 0x504B6CB6528A48F0ULL, 0xAFF02743E8E50A6CULL, 
            0xF165388094891162ULL, 0x260EB50B1C63BDF6ULL, 0x892330EE215F555CULL, 0x1D2311783F3338D9ULL, 
            0xF5680F9894940E60ULL, 0x3949C7AD6A2D4B24ULL, 0xFC52E4410D66597BULL, 0x7A3DBC683503B034ULL, 
            0x108B0B144FB332BBULL, 0x9BB72E0F9149934BULL, 0x381AC26B7070243AULL, 0xD222881B4E9D2B0BULL, 
            0xBD6C73E80D810ABDULL, 0x1939BFC39D7620EDULL, 0x4EF92344D7D7886EULL, 0xEE99026EBAB2C844ULL, 
            0x8385529EB90A33E0ULL, 0xF240A500CB69CA66ULL, 0xBCE32BA501E54C73ULL, 0x6CFBBCAD526DB757ULL, 
            0xE38D81BB417EF183ULL, 0x06B6545C85236B5DULL, 0x76961A34C4F99BB9ULL, 0x56A2E2E3E22A84DEULL
        },
        {
            0x78B453AA208BEC42ULL, 0xCBA98E263056F28FULL, 0x5168888B9047A967ULL, 0xB9A6A91D5EDDE811ULL, 
            0x27997C310B60EE7BULL, 0xCF57B31ABE1DFDCAULL, 0x366ADF811B15921EULL, 0xB06A4AC4C84C11E2ULL, 
            0x47F7E6EDD7852CC7ULL, 0x2B3197448CFF569BULL, 0xA9E8A75983C58506ULL, 0x7845FA3F417107E8ULL, 
            0x9B424BD9946EB878ULL, 0xB8BD069FA8CFA33AULL, 0xFD5CA5EBC5A7CE73ULL, 0x6B6D76EF588FB901ULL, 
            0x7F40FEFCF7DBB6DAULL, 0x6D2D9709F5BB15FAULL, 0x67A4DF1B997CC52BULL, 0xA42BAD463E1E03CAULL, 
            0xD7EC3DEA4D091F71ULL, 0x1D2A2071E551E6DAULL, 0xE90A1B650A4F44AEULL, 0xCD5ECFFA01DAABB3ULL, 
            0x8C7255E951F3F23DULL, 0xEA94B007C81B41E7ULL, 0xBD13F6F7D2EF6D4DULL, 0xDBBC0AA707CCDA0BULL, 
            0x2E96E6297D04CC93ULL, 0xD305675C03111780ULL, 0x58FAC08F6C0120FFULL, 0xB04CE238BB842B38ULL
        },
        {
            0x788E17854E740CFCULL, 0xD028662DE58ED486ULL, 0xC316724DEB796639ULL, 0x4B55CEFB9B23C1F4ULL, 
            0xBD46A14DA16A5868ULL, 0xD6BB6BF9EF8558B7ULL, 0x658BC08199E868A9ULL, 0x575E86CF8FF9D9D2ULL, 
            0xC94A5AD826E3EBC5ULL, 0xD9C8286386347BD3ULL, 0x037386855C26E39FULL, 0x3984C317E2ED95F9ULL, 
            0xB466AA20770D64C4ULL, 0x30555057B3E234AFULL, 0x6145DAA702F11125ULL, 0x22EF07FA1E99E048ULL, 
            0x7FF31976533A9737ULL, 0x526E7294C7C453E6ULL, 0x9EF4BC5F24BBB41BULL, 0xE4B26F55AD8FCF6AULL, 
            0x54CE70AC432A7740ULL, 0xD191BC7245B0F892ULL, 0x95C195A417FC0B7EULL, 0xDB2D1D9E20709C37ULL, 
            0x7CDAC24149874098ULL, 0x06E7DF9A168F235FULL, 0xED88E0EE3774FCE3ULL, 0xCB1BE6B1C78CC7E3ULL, 
            0x2DB602357BECB2ECULL, 0xFBD735FB96E04721ULL, 0x159FF386DD3F65D9ULL, 0x3997097170257F8DULL
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
        }
    },
    {
        {
            0xAE71587AF12E3EDBULL, 0xC1BA64D333C11189ULL, 0x4AFDE723A252C876ULL, 0xC7ED96664BCFC785ULL, 
            0x0F60D203F038F621ULL, 0x0A5260FD8810E776ULL, 0x1F6219D963B26892ULL, 0xD51F1F957E21DD86ULL, 
            0xB7512E3D8F676C5BULL, 0x2F8FB554644B5D99ULL, 0x864B66E448373A8FULL, 0x062D02D00E9173DEULL, 
            0x257EC54B69D0C898ULL, 0x23878915A1895691ULL, 0x5B4CBFE96FC6BF45ULL, 0xF27264DE7FBA7CD9ULL, 
            0x59742CB87D765ACEULL, 0x2A2ED36CADBAA51DULL, 0xF5994120CCC1CBC8ULL, 0x25586893F2B630A4ULL, 
            0x5CA5A90ECE3EE844ULL, 0xB5A01991A1C22CF5ULL, 0xBD21DA135E6EEB15ULL, 0xC06248AF42440B9CULL, 
            0xB76CB4253AD7D638ULL, 0xECEB6587DA126C3DULL, 0xF6695AB0067ACEC0ULL, 0xC047BF89CFDFE872ULL, 
            0x06AEFBA46C5F3FF7ULL, 0xF2A0018EF86C9DEEULL, 0x18757C5B080C6AB1ULL, 0xF3468A09CB0DDDC9ULL
        },
        {
            0xE20F43747CC8F3C1ULL, 0x094BB37890AC470AULL, 0x43F3478AF926FEB0ULL, 0xEF88BB6A8675B28DULL, 
            0xC79636D03F4E1585ULL, 0x1DBC7AD490DFEA40ULL, 0x745412A8ED04789BULL, 0x739047038993CD0AULL, 
            0xE8B7ADF101403F3AULL, 0xE7FBD21E85675CE3ULL, 0x3679C52CAA7521F8ULL, 0x68C7C9FDAE648302ULL, 
            0xD936BB968AAFC0DEULL, 0x392773DB533A73AFULL, 0x09E5EBDFDFD433A0ULL, 0x70D67D1BB813520FULL, 
            0x41B8A08DB5F9DBFDULL, 0x20B84ABDFDAEEA3EULL, 0xD44BCA1E7C0DF0CAULL, 0x1CA85D1391431EF4ULL, 
            0xD9378D3DC0A3CEF6ULL, 0xF761611CF6A3DF70ULL, 0xAA7FB9D8C3E62D09ULL, 0x6C79B4756FA3E6D9ULL, 
            0xEE2ADCDC079C0132ULL, 0xABC56B3ACFA71CC8ULL, 0x95B1703B728F6D7AULL, 0x52ACCD218A89758EULL, 
            0x5AB6A38B7FE70114ULL, 0x6ABCDDACEB3BBCA5ULL, 0xFE398E4FEC12E9FEULL, 0x580E951B07469CFDULL
        },
        {
            0xC8D02E77594A3E43ULL, 0xBF7A60A437A00BADULL, 0xD397F4B39D29A983ULL, 0xCDE8400510527BBEULL, 
            0x505346C40C652A12ULL, 0x7BE1EE6C4290C23EULL, 0x47E8E7D7C65D415FULL, 0x542FC500CCC9877EULL, 
            0x78685A34E9CB9885ULL, 0x62101E579E7A2CFCULL, 0xB95C29443307B88AULL, 0x58223B7F7F14018DULL, 
            0x6A6C350CAE7EE74BULL, 0xA86443AA39EA19CBULL, 0xB8D4F61094FFDF8AULL, 0x6A6911390F00A76AULL, 
            0x99265ECF005260C0ULL, 0x2EE9320F50916B2DULL, 0x302ED78A591F7452ULL, 0x8D9547D7A85D7995ULL, 
            0x1585626A04546CC6ULL, 0x627D7A2950CB29F6ULL, 0x29A959D84D21949DULL, 0x847F27796AE2E271ULL, 
            0xE48315D2ACA0B412ULL, 0xF9A79D98AA08B0E8ULL, 0x347BA9A0834F8280ULL, 0x5B5D456C9CFEEB33ULL, 
            0x3F91147420D296AAULL, 0x7B056F63B0F1D788ULL, 0x099763354DD09CE5ULL, 0xAC2DFE89FA8BE26CULL
        },
        {
            0x9E0F053493C93BA4ULL, 0xA8392BECBA07718CULL, 0x9BCF0FB975B2F6EEULL, 0x1DEB30AE5592EB43ULL, 
            0x1498419287876AB6ULL, 0xA1F485B2F11776EFULL, 0x5F52B1DDBC0F5E96ULL, 0x53F58D11C8BD78EAULL, 
            0xD351D37F4F6D4557ULL, 0x0C76D525FAB50616ULL, 0xCD2AB9A6FA9F16C4ULL, 0xDFE609FE03014B4FULL, 
            0x3D132892762757D9ULL, 0x129AECDCEE284438ULL, 0x591CCCBEA1B51FD2ULL, 0xAD0CBC2D3E265154ULL, 
            0x32F1802F5C15A02BULL, 0x722857E96C51E346ULL, 0xC2A202D5C2E72943ULL, 0x6C287711137E8AC8ULL, 
            0x0BED49F721624496ULL, 0x1F6C60F35ACB0EF9ULL, 0xF6D8E8461C6416F4ULL, 0x5C4AF45AB52302E8ULL, 
            0xF514AB2CB65E6A60ULL, 0xA814593081CE481CULL, 0xA6C24E6F79A18630ULL, 0xB67B9EB1BC0ED5CEULL, 
            0x166C1F36AB294259ULL, 0xDF86958564276A34ULL, 0x96F7E097A0CBABBCULL, 0xB5DC5CEBDA09B1E1ULL
        },
        {
            0xC8B31DF6341ABE10ULL, 0x7E6A364DAA9A391CULL, 0x874B0140FAE75323ULL, 0x756F06ECF77C3057ULL, 
            0xDC11D37999349B37ULL, 0x8F7CAC6B55F8A101ULL, 0x381C2BA9BD10B26CULL, 0xCC22C515488C46AAULL, 
            0xDA322FA0965F8E7EULL, 0x04E8EE10CB8977C9ULL, 0x5F38B4DC9C8370F0ULL, 0xC70D1E084EB14C16ULL, 
            0xD0828B49B360A563ULL, 0x49287DA1BABB16B1ULL, 0x80B2CEF3C15365C3ULL, 0x9B663627B4DA3656ULL, 
            0xD713098EC26F8911ULL, 0x7DB07266ABECEF73ULL, 0xE2A1E11729A3E282ULL, 0x141EBEACA88671EBULL, 
            0xC980312B555E65A8ULL, 0xF931324DC63BDDCAULL, 0x10E83BAE53CEC325ULL, 0xDE37B53F5770E06BULL, 
            0x234A04D9F08679CFULL, 0x3D5FF91A0D925A5AULL, 0xF4FA8B53F474E61BULL, 0x9038D24AB60DB390ULL, 
            0xED166F031114E8BFULL, 0xA100DD9BE37B04ABULL, 0xB0562E0C9639404AULL, 0x9275F06F743776B2ULL
        },
        {
            0x0BB11E7670A4A518ULL, 0x0C5E8B52EE9860A9ULL, 0xF67C908CC245B77AULL, 0x79E18FD268D1AB8BULL, 
            0xFE60F282F1EC79A8ULL, 0xEAAD58DCED0099E3ULL, 0x3663F033E6E2F7FDULL, 0xC366B81401F46A38ULL, 
            0xF90A5891450C838CULL, 0x4AC4A9AFD4246C95ULL, 0x3C10141144CAD118ULL, 0xA83F961826BAA032ULL, 
            0xA946E09D5F97E41AULL, 0xAA61C7B3FA4B77A1ULL, 0x7397E6EB19E15078ULL, 0x8E9926EB1BFD6ED4ULL, 
            0x2E439965C659AC88ULL, 0x1B7E368E4A56A104ULL, 0x8C824EDB80A8FE4EULL, 0x6269F5F9977E375FULL, 
            0x990940716347BC20ULL, 0xCF98151F124C3391ULL, 0x2C023B9E3E1E220EULL, 0x8F0647318B797F11ULL, 
            0x503C19559D490615ULL, 0x4B3B7D6BB6D690BBULL, 0xC330B46F4A67D147ULL, 0x26A3A324A19BB1E9ULL, 
            0x9FD97FBC5AC8EB51ULL, 0x5291EDDE1818D30AULL, 0x729C51CC2978BE1BULL, 0x85969E46D64E7BABULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseEConstants = {
    0xF9319452530499D1ULL,
    0x4546523A4175E95EULL,
    0xFB976EAE27A3ABBDULL,
    0xF9319452530499D1ULL,
    0x4546523A4175E95EULL,
    0xFB976EAE27A3ABBDULL,
    0x697047E07C6D403EULL,
    0x63E11D28342E69ACULL,
    0x1A,
    0x85,
    0x4A,
    0x3D,
    0x5A,
    0xC3,
    0x35,
    0x05
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseFSalts = {
    {
        {
            0x5030DA2FC3F34071ULL, 0xCD4F7DBA425BBA4FULL, 0x12FC0120CD11B6DEULL, 0xD4DA4027D0B6670BULL, 
            0x3C986BD09815AB86ULL, 0x51E8FC4CDCD0782FULL, 0x15AF47081976C75BULL, 0xEE975372AE25E9CAULL, 
            0xFF726F7783E7E0FAULL, 0xFFBB47FB1CFA9347ULL, 0xAD4010F5714CCDEEULL, 0x80B8D2CA3CEEA86BULL, 
            0xD60FB6B76C603E9CULL, 0xAFC5E14C57D60C78ULL, 0x4072FA563CF56C92ULL, 0xE9927252374226E0ULL, 
            0xE88A011012830273ULL, 0x382AF24AE73A1A6AULL, 0xCCEEC8318EE0933CULL, 0xB7E2861AFD324A71ULL, 
            0x79DCEB0B675B5B49ULL, 0x5F7FFB7223F47EADULL, 0xFA5C35EF16E48E21ULL, 0xFC5841794EA12928ULL, 
            0x6BC307DEE0BD9AC9ULL, 0x3F0CF107759C5745ULL, 0x92C12751966295D6ULL, 0xFF39E4073BC91381ULL, 
            0x5E793F757CA217AFULL, 0x2D9370E27C820364ULL, 0x065F551DE841FB82ULL, 0x2E5012532CD05346ULL
        },
        {
            0x530E45B865265B18ULL, 0xFCC4CACAFB0F59D9ULL, 0x07D9C85D2AAF8FF6ULL, 0xB878C4A6F785D424ULL, 
            0xA7E15E4B9B7F0789ULL, 0xC7BE00861D8D23C3ULL, 0x24E2549A55E61875ULL, 0xEB248C5FE5844663ULL, 
            0x2E3235E65B002F0AULL, 0x6D2A4338922F3FEDULL, 0x7ABF1D47F1AC9945ULL, 0xE762BE585BB6DAF4ULL, 
            0xB488DC20BF93643EULL, 0x65F15EDD1898DE9DULL, 0x049E516982CA7BAEULL, 0xDF8A0EE231322B4EULL, 
            0x407BF455D4C770C5ULL, 0xE8273894EA4412ECULL, 0x4AD665071DBCD8B7ULL, 0x701BDA2EFA641CBFULL, 
            0x07A70EA6A64D5CBAULL, 0x2AF0F63B0C5CFEB8ULL, 0xB45995F501F64951ULL, 0xEFF4389E1E7AF3DBULL, 
            0x9C8FC31ECEA0EF41ULL, 0x0C071EFB9A44E319ULL, 0xCF4CE93B6609169CULL, 0xC372606C3C72DDF7ULL, 
            0x635FFD3D7EF89AFDULL, 0xC86CD8EBD9869A35ULL, 0x57FAE365A2C91CE1ULL, 0xE0464B5F71324F5FULL
        },
        {
            0xA4202E1D0CD2F2AEULL, 0x75DF95CCAED7C67DULL, 0x7A34A8106644FC00ULL, 0x0FE36F2823761FCFULL, 
            0x35CC835FCE4CCCB7ULL, 0x765A37DF51913A79ULL, 0x6787BDA3DBE3F370ULL, 0x510C0FEE569F1687ULL, 
            0xE3C389C1FAEB4E2BULL, 0x42DED907534B57A1ULL, 0xD933CF92B2FC555CULL, 0xFC4B2B7FA2682B95ULL, 
            0xF107337E8D91CDB2ULL, 0xC2BB7B1B4D41DD42ULL, 0x5805E33DEB234689ULL, 0xB497C97881CB884FULL, 
            0x07A2268A9E996A78ULL, 0x6006C207EB099172ULL, 0x70AD084954B8D782ULL, 0xA92D1BA65CF9A9A4ULL, 
            0xC46A825513AA0853ULL, 0x976ECAD526010F58ULL, 0xAF1BB1248732BFCAULL, 0x56D089E685472AECULL, 
            0x4B0AC25A92374AC1ULL, 0x402FD2680C759C0FULL, 0x3D660A55AD6B9F30ULL, 0x4E9BA91D674F9E84ULL, 
            0x76FC61C08D711D91ULL, 0x8EEC94851E6DDF9DULL, 0x4D026250D8F4A0F5ULL, 0xB3E26A1E62493BA5ULL
        },
        {
            0xAFA8F978CF3AC330ULL, 0x4CF90EFE8D1B00E2ULL, 0xBC48574406B5A856ULL, 0xC1F75BA2846D3EB9ULL, 
            0xB8ABDAAB91E1F746ULL, 0xE69C965A0BD062C8ULL, 0xC350028FF7251214ULL, 0xA71B395193B91C57ULL, 
            0x0CE85149856E5786ULL, 0x636ACADCE5003BF0ULL, 0xEBDAAB362B19D535ULL, 0x035DB3EB1A3C4C14ULL, 
            0x453F1E7436707AE2ULL, 0xD8E349ECDB4A6C03ULL, 0xCEC94588E239DD8EULL, 0x164D72C668533FF6ULL, 
            0xA058FCD1AA357B86ULL, 0x17940149B01DE9DFULL, 0x83D0BCD139D585FEULL, 0x39B5272F65A7C139ULL, 
            0x8E58402BE4F66308ULL, 0x2A444E8137EDEE51ULL, 0xB671E5E6065E228FULL, 0x1D03B19DC06D34E5ULL, 
            0xA6E39AE148D06E3DULL, 0x3DA52963EAD0EC92ULL, 0xBA03C638756CA687ULL, 0x2F7EEF9F72BA88E1ULL, 
            0x5105E994727B44CCULL, 0xE16E34408D743BFAULL, 0x8F74F7619FBF5D26ULL, 0xE6A5A43EB50CD2E9ULL
        },
        {
            0x574DB327C40440D5ULL, 0x4CE1D829DEF7713CULL, 0xF5917898A9B51560ULL, 0x9783AE842F4D0BB6ULL, 
            0x0AC8C7F03817349BULL, 0x77D326140830CB8BULL, 0xC38669838323AF9AULL, 0x43673E6B2F201361ULL, 
            0x775ACBCCDDF7F5E4ULL, 0x6D1309D161C55872ULL, 0x7996DA6105685DB3ULL, 0x0D722BECEC137A4EULL, 
            0x89C3A74951C0DE54ULL, 0xD194C329346637DEULL, 0x4B62BAA822979F5DULL, 0x6E7BC64AB47FAF42ULL, 
            0xAB16A43E68A17E80ULL, 0x75AC0078B8E31A7CULL, 0xC27792AE22A78C15ULL, 0xFC3E1AC1F2385C98ULL, 
            0x87462CB6A88674FBULL, 0x40D2228D57416F3CULL, 0xDAA0D130B4F25A95ULL, 0xCD2485AD3E86D649ULL, 
            0xA44F5C5A340E21C1ULL, 0x7CE20BE82F1959DAULL, 0xCE9FE895B14896EBULL, 0x7C24E18407A9B60CULL, 
            0x9233BB6D77D84F99ULL, 0x04A2E59F51777263ULL, 0x56EC323F2B121E6EULL, 0x4A077F8B50051F64ULL
        },
        {
            0x58F1CEA60C84313EULL, 0xD4E070BED80DB9D9ULL, 0x67E64DEBD039BD3CULL, 0x5BD7800F9B8844A0ULL, 
            0x87044FCC7019010BULL, 0x3C01DDC4306AF2F3ULL, 0x57CD4D0183267AAEULL, 0xA8D44F1282A478A9ULL, 
            0xABC8FFE2BF5DFA82ULL, 0x385831266EB462F5ULL, 0x90B4F36920E6C082ULL, 0xE3509829779FA8D4ULL, 
            0xCD31531951A87FB1ULL, 0x68B6292BC88ECA90ULL, 0x26BDCE7BDE204FE7ULL, 0xCDCB7F0FF3F7D5C9ULL, 
            0x1326EE06514EE890ULL, 0x4C074962C3BB82F1ULL, 0xB566C0C1BC9A18CFULL, 0x43974EBC6795D6D9ULL, 
            0x726B6EF7D46470A7ULL, 0xD319F9C2FAEF2370ULL, 0x2C8EB4FB7FAF1354ULL, 0x4B9ADBE1730201D7ULL, 
            0x53717BFD9F0EA7D3ULL, 0x89DCC620CC297429ULL, 0x57CF8F68A781D617ULL, 0xBAE8E94DF273EC58ULL, 
            0xB86FEC79E9861156ULL, 0xDD7321DCA6A7D04DULL, 0x96DAFFBE204B4D81ULL, 0xF0CA5FE80D74EBABULL
        }
    },
    {
        {
            0xE22BD03F3AAE8C70ULL, 0x4A430C48984ECE73ULL, 0xC7B45FF2B3D4D7A2ULL, 0x940554D9A09C3FF2ULL, 
            0xB2AF7C7A9F300D79ULL, 0xB9F74CE591D211E0ULL, 0xDB0D46BE24DB98C9ULL, 0xDB7E5BB778948AE4ULL, 
            0x6D9BCE1CDFE86AF7ULL, 0x8E340BB37E47E2DCULL, 0xE10FE72D35A12405ULL, 0xCD472CC7C6E66420ULL, 
            0x84F77F495124B00BULL, 0x40C3FB6763A8C3C9ULL, 0x8AD57E443772FE22ULL, 0x22C0B3573EF28A32ULL, 
            0xCDB5C685E747B5A8ULL, 0x52093F17F807FAF8ULL, 0x96A4845A0F4EE766ULL, 0xE41DC07E0136A097ULL, 
            0x5AF9F64EF1AA1647ULL, 0x73CF6206F3939788ULL, 0x95AECFCE494F9DD8ULL, 0x386B75B662DAA6C2ULL, 
            0x738468A1D2AC80EAULL, 0xABCE084E1C009946ULL, 0x0F55D52F1086ED1CULL, 0x0249C586C1DBC501ULL, 
            0x0C35E5DAEB527AD9ULL, 0xA34EA97E84321F29ULL, 0xCB92D2352604CF21ULL, 0xBA9B255CB8BC73C1ULL
        },
        {
            0x0B7B899299E7A8C6ULL, 0x07A7118C5108D577ULL, 0xD80C29EB54EB9E8DULL, 0xE2A479EB498AB3C3ULL, 
            0xDF4D1A765DC93A95ULL, 0x9357F3C24F92C11DULL, 0xFBD0476C3CE5D8EAULL, 0x773B50126842DC03ULL, 
            0xB00B592383F3DD0FULL, 0xDD4B8E5DA8904291ULL, 0x16E3C77A5874495CULL, 0x01313082745AAF5DULL, 
            0x89525BA649353839ULL, 0x69C3A04A725A2EFAULL, 0x08A114F4D31855E8ULL, 0x46D3FD819D91C9F3ULL, 
            0x3E3023A86A1B2410ULL, 0xB3213C25B5F60884ULL, 0x1E665242E29BC023ULL, 0x26E3F6DA136C8275ULL, 
            0x4A04485856EEC8F7ULL, 0xD81292531BBDCCDFULL, 0x8F732F1730C9E148ULL, 0xA2039044CC2CC7F4ULL, 
            0x94D2F285DC5B8D0FULL, 0xFD58E17466DA1654ULL, 0x897ACDFFCBB487FDULL, 0x7A1E82216334572CULL, 
            0x30226BD50D000A89ULL, 0xB9516F32B3D46372ULL, 0xE6417F20BBE5CF4DULL, 0xF5ACA1976C925FA9ULL
        },
        {
            0x5C37D412E8EBE94CULL, 0xC5E98A722B890E61ULL, 0x9E99C1B77BAAB092ULL, 0x5364BDBC9A1943F3ULL, 
            0x653B24C2ED53367EULL, 0x24F0CE0CDCBCB66FULL, 0xFAE9A73550A903B3ULL, 0xB3C36E721C1A509CULL, 
            0xFF3F5C5D9F77CA29ULL, 0x3BB55FCA17D39A8BULL, 0xB9BA5C91E5F51209ULL, 0xD1BC7D6548DB35AAULL, 
            0x8ED398CA919247E8ULL, 0x2EB50FF11C70E7F6ULL, 0x96454D3ACF663A03ULL, 0xCD8CFCEA88631124ULL, 
            0x97E265D76676E294ULL, 0x3AC0BE90C6F3C4AAULL, 0xB06572C7A0328C56ULL, 0xFE35B5C07129273CULL, 
            0x91D8A38B3231228AULL, 0xB9D55F39415DE5BCULL, 0x4844E7EDF426BF39ULL, 0x5319D4F0D67DA24AULL, 
            0x767A9E9FD56EDFF2ULL, 0x7213CD73D414A9C0ULL, 0x942AAA1520815F5EULL, 0x752CCEFEEA37632EULL, 
            0xD99F9223920A2993ULL, 0x9422C6509155E75EULL, 0x581F708E27A5357FULL, 0xC416DF4F61A2D5FBULL
        },
        {
            0xE45F7F438DFEBDF6ULL, 0x6A6B6CF3F790C07BULL, 0xDE740C72038FD9EDULL, 0x3BAD9BC80ADC78E7ULL, 
            0x5393A160B442DDA6ULL, 0x4F7640F263088750ULL, 0x4C537FEE6CE37BE3ULL, 0x513B0FA672D1CFEEULL, 
            0xBB564765371EF073ULL, 0x987FF759E2B1D2DEULL, 0x46F580810EF5904EULL, 0x29F655872465AC0AULL, 
            0x5B5AE6FD0052785BULL, 0x54D1423E6131AD80ULL, 0x6A37051AD8F94F8CULL, 0x056F3F11A3FF42F5ULL, 
            0xEC89046F15AA87AFULL, 0x401A34B79C6C9510ULL, 0x9CE0BBAC853376B8ULL, 0x8EF25BEA043C9A4EULL, 
            0x8059CD1ADFD5CDACULL, 0x06AF5402BF389673ULL, 0xF9BC3282AE34FB31ULL, 0xB0F900D1540362E7ULL, 
            0xA6CBD62C0DB2424CULL, 0xD87E5408F873D820ULL, 0x43AE06B60F9E0B5FULL, 0x89D118B634D8365DULL, 
            0xC9D4E63E95035867ULL, 0xE68277E08BB16290ULL, 0x7822B8B8D622845CULL, 0xEEE5362461964647ULL
        },
        {
            0x8729CA168658415AULL, 0x4D8E8BEDF4CE3168ULL, 0x828CE3CC33D654C6ULL, 0x7B9485B333B80649ULL, 
            0x1CB571B79AA58E66ULL, 0x33644A672B8800B5ULL, 0xFD866DA0697A6B82ULL, 0x013DDBC77A3A26F0ULL, 
            0x28C02334D9A7FC60ULL, 0x334C2BB49B2DF1B6ULL, 0x1AC4DDE8F9E8B717ULL, 0x18EB320CE93DFB18ULL, 
            0x1A71CBE16609CB07ULL, 0xA82661BDE1927FC2ULL, 0x639F5EBD1D6C14FEULL, 0x7A92B1A2744F4900ULL, 
            0xB4B40E56A6E652CDULL, 0xC9C55ADC32B97573ULL, 0x65EE33D1A794288CULL, 0xC9E3284784AEDB17ULL, 
            0x098C32F1525F5205ULL, 0x467EEACE50E4A946ULL, 0x7F57D315DBD89785ULL, 0x3D0F96DAD745004AULL, 
            0x148F46FD46E74454ULL, 0xF69C3394D62963B3ULL, 0x4983EB44F3A5E0E2ULL, 0xF29198563AB7E07FULL, 
            0xEA109A26181473AEULL, 0x5418734DF1629AD6ULL, 0x01A886A4625A13C9ULL, 0x39A1E4DA20F9EC77ULL
        },
        {
            0xB33D993D8694D523ULL, 0xE07294DA93BB929CULL, 0x3F965005AAEA7233ULL, 0x5FC1AA24CDF94716ULL, 
            0x0E0C87ED20EDDA24ULL, 0x0AE56D39269619D2ULL, 0xB497A4E444AC8AD1ULL, 0x62674684534C6086ULL, 
            0x6543DFC7A92EF43EULL, 0x10C800409A97005DULL, 0x16ADC38DD2003594ULL, 0xAAA8496D88685FB6ULL, 
            0x4E621C54636E5FD3ULL, 0x519F1C1A1F5FC04EULL, 0x0E2B051999F8F2D1ULL, 0x4D6CCE117952C28FULL, 
            0x7246DAEC25E3F00BULL, 0x838639515CD29DA3ULL, 0x862204B99FBD5220ULL, 0x626820108688D64BULL, 
            0x86F9C014535D3805ULL, 0xA3F64966D360E00BULL, 0x49FCE94E50E631D8ULL, 0xC6ED9895FFB473F2ULL, 
            0x7E8F9E4216877B81ULL, 0x070497F5C7133364ULL, 0x04D678C49CD07DF0ULL, 0x2265B8957545E03DULL, 
            0xD31104982DEB140DULL, 0x813BC4AB28D02C79ULL, 0x8C9B6B35103F7CB1ULL, 0x2D017074A1CF3EFAULL
        }
    },
    {
        {
            0xB1EE7B46344CFBC5ULL, 0x1C4310D11FCFE817ULL, 0x2E1C98F57ACF7919ULL, 0x32F85DB64587491DULL, 
            0x63057C55C1EEF3BEULL, 0x7E37FD101C8B67E4ULL, 0x8A04A453D48F6125ULL, 0x409FD0A49E7359E6ULL, 
            0xE94BA4224E603A35ULL, 0x4956BD0CC78C0035ULL, 0xF40D4EEC04613BCEULL, 0x0646B2CE83795758ULL, 
            0x3D5A8F7C1518C223ULL, 0x95EE03FE9974861EULL, 0xC27436DC3781241FULL, 0xCC4E4E177EA70E87ULL, 
            0xA325C02FCDB703A8ULL, 0x57FB0B7FC198F498ULL, 0x2D1A861B8A15470BULL, 0xF8D1C9BDAFEAC329ULL, 
            0x6D427A826CED9EFFULL, 0xA1EF236AAFB24F27ULL, 0x3B0E8BBD7A4C0AB2ULL, 0x89075CCEA1F89E54ULL, 
            0x124ED86F40EF08ACULL, 0x78D8EDCA637069ACULL, 0x1729886FB377CCAEULL, 0x9A5A787A997C4EA5ULL, 
            0x83FBBE089D1927FDULL, 0xF895662B1A60000BULL, 0x23206553B4CBE51FULL, 0x3267EBD7E8BBC00EULL
        },
        {
            0x5C7EA5039357F67FULL, 0x3006364A16A2EB22ULL, 0xC3BE7748EACFE794ULL, 0x778B4231E9F3AD25ULL, 
            0x08BF014869D2DA75ULL, 0x0B21AEE8C5A158DBULL, 0x06576F4875796492ULL, 0xAD91B88F05CD62B5ULL, 
            0xC6D74B8F50966F9FULL, 0x69A5EB243790F3E0ULL, 0xC8522BE06CD5E65AULL, 0x2566EBC3D23EE31FULL, 
            0x5BE8FC2B528C845BULL, 0x98EF4832D4596C3EULL, 0xBE5887871AA5374CULL, 0x1A6285C55FEA7A90ULL, 
            0x0449A55247DDC192ULL, 0xB3293154586B0197ULL, 0x4332389DF65BC4FBULL, 0xAC8FBE9F2C482659ULL, 
            0x60DF30A74A36E015ULL, 0x8D0671B4071372D1ULL, 0xA8B233C2B683FA19ULL, 0x24874B7E8678677DULL, 
            0x79262AEA45257889ULL, 0x75C31934DB013EA0ULL, 0xA8552A1EE0115B6FULL, 0x4B4D51211757E8E3ULL, 
            0xE550276855A82B49ULL, 0xC05DF4179414B407ULL, 0x7E13F0471E29E3EDULL, 0xE020116E4F60FEF1ULL
        },
        {
            0xE7A7AAEC6DA178A1ULL, 0x95F97F1C42B0B960ULL, 0x4FFC8E91515B98CEULL, 0x8703FF48701DC81EULL, 
            0x4A7A175BC5C00CCFULL, 0x46EFDCA057A0EE79ULL, 0x8F507DA3B58D0028ULL, 0xD83A694F558AEBCEULL, 
            0x73FEC79E6A004B4AULL, 0x5FC83FD6EF91D839ULL, 0xF4C84E25D6029883ULL, 0x3F9A60A478437B65ULL, 
            0xDA7E7C7EBCADB175ULL, 0x92FBFA2E8E342E62ULL, 0xD22B8A29C187FB8FULL, 0x137D53CFCB9DAE4AULL, 
            0xD378DD7F5216A3F5ULL, 0xDF188B0462BFB373ULL, 0x06B1272D8F7FB7A1ULL, 0x2AF0E84C7DD18EE6ULL, 
            0x1D6433A8EE797EECULL, 0x018C35CF25773899ULL, 0x67F37A3832E83A9FULL, 0xEA37CA527E3BFFDFULL, 
            0x3C6B946F3865170EULL, 0x289C2263B7A7D509ULL, 0x1BF1070079F8F29FULL, 0x4A8FE5443CF79CF3ULL, 
            0xADC4B817EA0F19FAULL, 0x945FB6DA72A9512EULL, 0x494992CAE51700AFULL, 0x0C2260173AB16C69ULL
        },
        {
            0xF0AC52EE620BB6DFULL, 0xC86DBC695B737CE1ULL, 0xDA342C045A459245ULL, 0xCDD99BE1DFCB57DFULL, 
            0x951C380FD54B58E5ULL, 0xAE0FA26D3F33612BULL, 0x892BF6549355540BULL, 0x300221F40F9F3099ULL, 
            0xF05FDF0678FB4595ULL, 0xDCBDADB3ECFA6D04ULL, 0xE9625CD714041EBBULL, 0x46A971F53EA7EA22ULL, 
            0x2117A5CC06D2B80DULL, 0x0D38B86467948E2FULL, 0xA41CFBF9F7A3B106ULL, 0x88F2B59CB2155EBAULL, 
            0x6A435C44D71FEC30ULL, 0x457D9D342E8BA3FFULL, 0x7383E108AD350BADULL, 0x9ACCBB28B261B3ACULL, 
            0x00F85C7F11A7FE70ULL, 0x00360830A8B27E8EULL, 0x05F882C9BD2F6E3DULL, 0x96098156C9304F0AULL, 
            0x9BB5DE750E9E1F5BULL, 0x299D434FE3C04BD4ULL, 0xD20E6A4DC241B051ULL, 0x22889BF5EE54C6F8ULL, 
            0x5AEB3820FF931AABULL, 0xA2F8746645E14A8BULL, 0x1959E98E3B1174B5ULL, 0xF2A608BAEB85A95FULL
        },
        {
            0xF9F320D3BE05146AULL, 0x6635134E75CD59A6ULL, 0x6D2710A260F392E3ULL, 0x771B5869537DECA6ULL, 
            0xE4A0E4E2A2715AE9ULL, 0xFA5C80E33D63FB3CULL, 0x9A295574216660EAULL, 0xF43AE36CCE122D56ULL, 
            0xE379FAD24A60AF3AULL, 0x2924E0339AD61BE7ULL, 0x96DD8AC880906957ULL, 0x38CD67DF15DEE291ULL, 
            0x140995662F0A0015ULL, 0x5217BF5D05AEA684ULL, 0x9EBC636B8282F948ULL, 0x773ADAD118191105ULL, 
            0xD434822A0B2FB38BULL, 0xE44099D1066445A3ULL, 0xD170C9F149E55524ULL, 0xA3C206C7F6E40499ULL, 
            0x6CACC7B5E63C967FULL, 0x2A0BE4E3446F767CULL, 0xA495EA446557F2FBULL, 0x7E075707C5C93CE3ULL, 
            0xF14D4D514BABA569ULL, 0x3A42F7463B8777D5ULL, 0xDE1671F40B372755ULL, 0xD03A96BEA9861EF8ULL, 
            0xE0AE41A36BE30F81ULL, 0x013C3DA64C417D82ULL, 0x0AD8C4E1B807A71BULL, 0x3209D6C516C8D257ULL
        },
        {
            0xDE0DE5A111C151E2ULL, 0xE79C80EF67792E5FULL, 0x0BAC0C7867FF6727ULL, 0x6E3E56D831051E16ULL, 
            0xA2F6F267C744F279ULL, 0xAE9100A1506E3942ULL, 0xA6512CC8E314B7D3ULL, 0x3040791D2F4CFCBBULL, 
            0x275EF244B3B01E1AULL, 0x237868C347810F77ULL, 0xB941ABAC68067358ULL, 0x1D74D562EB36CA6EULL, 
            0x3C3027567E336486ULL, 0xEC00C811C9EA3FD0ULL, 0x43BBA04B5353B22BULL, 0x375C7794F13E9171ULL, 
            0x45096AED897C9830ULL, 0x61CEDF09079FCA88ULL, 0xAB4D285D672BE560ULL, 0x356851CA4B499326ULL, 
            0xA3956FFB4B176C57ULL, 0x8B97B8F7E8DA3E79ULL, 0xAF01232D86EDE01BULL, 0x90C40AE05A9441D4ULL, 
            0xDFB2C81CA5D90BD7ULL, 0xED02BFB14B0F31B6ULL, 0x6A3C0303F374CEECULL, 0x16782F4E2D72FBEBULL, 
            0x44554F4BC15257D7ULL, 0x12507F016C045BACULL, 0x20B0E75DAE09D808ULL, 0xC30BD3B0BCFD9EB1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseFConstants = {
    0x4E35B8CEA47F7B0FULL,
    0x5CB12F14A436BA96ULL,
    0x2836CC7BAA01389EULL,
    0x4E35B8CEA47F7B0FULL,
    0x5CB12F14A436BA96ULL,
    0x2836CC7BAA01389EULL,
    0xFA0C34B036A727DCULL,
    0x2CF4C071E67AE2A7ULL,
    0x97,
    0x2A,
    0xF6,
    0x7C,
    0x5E,
    0x35,
    0x88,
    0x2B
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseGSalts = {
    {
        {
            0x37FBC15FC8CEC7AAULL, 0xDB04E927F37B6CE4ULL, 0xC8D669DED30DA282ULL, 0x047923EA87B1530BULL, 
            0x5EAB0DC3AC326833ULL, 0xFC2EC50C679BA31BULL, 0xE9DDF9CAB411B782ULL, 0xB674C0CE2CF9FCC1ULL, 
            0xA46E317A5052A804ULL, 0xB85DEDDD7028CF61ULL, 0x6D1D946ED72FC3BAULL, 0xF03F464ADFC20309ULL, 
            0x0445CBB06DB490E5ULL, 0x7DE0D75E93C061EEULL, 0x35E7112F3D22BFE7ULL, 0x2DD32DA73A4EB726ULL, 
            0x13AAB8732A0B46CCULL, 0x329B3A96179EE6B6ULL, 0x1D117B8B168FC6E0ULL, 0xC9D2A79DD6813909ULL, 
            0x830AF1F2886C6107ULL, 0xAEE05D9BA7CE4C8AULL, 0x285A9D90FE7A96D4ULL, 0x14610115D9A46607ULL, 
            0xDD01E7C6F90A765CULL, 0xA9137EDB99F9884FULL, 0x349A66B33173B7F1ULL, 0xA5F280BE5FAD65B1ULL, 
            0x357F44E4DBEA9F52ULL, 0xB0F45A9945D21390ULL, 0x127D5E46015750AEULL, 0xC94BE6862B9CC328ULL
        },
        {
            0xAFF577E2356412D8ULL, 0x51F03AE0281DCC86ULL, 0xEF804678BD9F122BULL, 0x1010DA44E988BCCFULL, 
            0x1C104F588E1FE409ULL, 0x08159351BAC9557FULL, 0xD6AB5E522C1B6F66ULL, 0xDAC647BD0E9CBBC2ULL, 
            0xB36249958782641DULL, 0x724E02C58A82785FULL, 0xD0A0D4182015E743ULL, 0xBF8EADF64C414F68ULL, 
            0x4673B047157FC010ULL, 0x72D1E8F71F13F6A8ULL, 0x9EC38CFF71341DA9ULL, 0x3B6469ACC226DA12ULL, 
            0x64329610C430E5F4ULL, 0x79692A289AF0286DULL, 0xE3D0E5FB6FB152C3ULL, 0x47FE1F7B9F139A5AULL, 
            0x5202557CFE3135FAULL, 0xD3ED0A30601CB261ULL, 0x2D4C9E4A686D5AD0ULL, 0x6D22BAB30F5C5738ULL, 
            0xA5C3FA9F81A704AAULL, 0x785EC76643480F62ULL, 0x682831D211A45E9BULL, 0x3A474E19D37DD9E2ULL, 
            0x1FFC298CABA9BEE1ULL, 0x4EDD66CE2EEF55CDULL, 0x64EF7A38A73746A8ULL, 0x1C3DBA12AFCFD41FULL
        },
        {
            0x804B249336369751ULL, 0x6C2DD83DBBB8FD72ULL, 0xE9F39C22FAA00623ULL, 0x3F230AE89DCD0256ULL, 
            0xB7232FF283C8695AULL, 0x570BC30F4B1924B6ULL, 0x1FF64B782A08C3FAULL, 0xC3DDD0998F298F28ULL, 
            0xE9D8004F253AED7BULL, 0xA69F375A855F0F9BULL, 0x618734D3CE9DCA54ULL, 0xBDB81F95C4444277ULL, 
            0xCD397CA9C4D11B5EULL, 0x90C1A350F5D5C9C3ULL, 0x7369591CA5F8E631ULL, 0xBF78BBE1E8C3924CULL, 
            0xCD781A383F2616F0ULL, 0x384A874E6C7807ACULL, 0x2538AD5A9E76D574ULL, 0x2F3BF22F0569B9A7ULL, 
            0x18B1E222103DE3B3ULL, 0x05D0E545E6F9C430ULL, 0x1D0BB2AC6AA32131ULL, 0x828525334B28ACDEULL, 
            0x4F8F343F505A394BULL, 0x1076641F858EB332ULL, 0x2C3041FCFEC59659ULL, 0x7C8749B10BD455B7ULL, 
            0xF680990422CF6D42ULL, 0x83ECB5FC47B81EC8ULL, 0xC5647E77A060D2FCULL, 0x9B7CEB3A8D77551BULL
        },
        {
            0xBE4B6F8996E211FDULL, 0xD913FD9F545C2C36ULL, 0xE2C7B4F92992F10BULL, 0x956D41DC03590002ULL, 
            0x532DE86D4A24F95FULL, 0x677C29C60152DDADULL, 0x5D4B55FAB7DF1034ULL, 0xB0974AB6F39A4FFDULL, 
            0xCD546ED44A582327ULL, 0xD6D1A06D32ADC08AULL, 0xF79CC98969A93730ULL, 0x3D702B9DEEC65A6EULL, 
            0xD5D81F7FA265AA5EULL, 0xACE6E7FF6698E03AULL, 0x235FE99BB2DCE262ULL, 0x40EB49A08F997EDBULL, 
            0x3B99F8930F2E13D8ULL, 0x905F7C987CDB868AULL, 0x451FE58CCE39C67AULL, 0xAAEC7E915ED87867ULL, 
            0xAE2FFA58D7756BD6ULL, 0xF771C73D0776B775ULL, 0x1EED1445527B0AF9ULL, 0xC04E95F01F49979DULL, 
            0xB53CC41085289C21ULL, 0x98D04B75002A065CULL, 0xD90E3771CF2B3BF4ULL, 0xE53629330F7AE905ULL, 
            0xF02119C187616451ULL, 0xC60A95C35082E656ULL, 0x917B0FB402ACE59EULL, 0xC91A4235E724B2B4ULL
        },
        {
            0xE20BF7E679C54FF3ULL, 0x85400A768C63708CULL, 0x20C5FB44CD7C8C54ULL, 0x3ADADFC7AA6330BEULL, 
            0x0C49FBE09BB6A786ULL, 0xDBD780D77C4AA331ULL, 0x8543AB129E5408AFULL, 0x8F3074C3D9F18BEFULL, 
            0xE46CA4BAD1D1D829ULL, 0x1C5A7117785A8B54ULL, 0x4E9D182FDDB3BBA6ULL, 0xA11611AD7482E26AULL, 
            0x0E091DE52F45A8A9ULL, 0x21A3F96C1D9810C3ULL, 0x6A9D668049AB74F7ULL, 0x2DC872AF6CA5719AULL, 
            0x965D8D7C2B28A6CDULL, 0x0D01F2604630E94BULL, 0x53D1A5EAE0C6CCB5ULL, 0x04346E7837A520BCULL, 
            0x845FD3E0BB2B5437ULL, 0x63C5316C0B10C239ULL, 0x260BAB7AF52C1C31ULL, 0x79AE5D52E7AFED8AULL, 
            0x39C50495FE32ABC5ULL, 0xB5E73C1ED8FF1DBFULL, 0x4782465A2F448264ULL, 0xA590D2B5EC04053BULL, 
            0xD72B7AD3AD126200ULL, 0x38BA78DF7D566554ULL, 0xA21B6B4F1AA540FEULL, 0x005570CE1E23DEFAULL
        },
        {
            0x3DFAF0AF8F031EDBULL, 0x6F434FDFE2BB93F5ULL, 0xECE0DF18F4BDC663ULL, 0x46C6218CC65101FEULL, 
            0x9775046CBDBE2524ULL, 0x716AC3E98FB262ECULL, 0x44CD69547E3C1D2AULL, 0x883790DF5507F934ULL, 
            0x04787B493986394CULL, 0xD106EFE5F2BA4CA9ULL, 0x9A5549712F558666ULL, 0x8F6E89008581794AULL, 
            0xFDE2F442D89961C0ULL, 0x2B7E1F8F4715D3F6ULL, 0x136B07A586BB4DB6ULL, 0xE3465B83E983CE02ULL, 
            0xE5726CA481C32155ULL, 0x660B07594991E0A1ULL, 0xCBC485A3C54BAEDBULL, 0x48CA58574AE07784ULL, 
            0x16011C0A649B6FFFULL, 0x58DC8BCCEDC0699FULL, 0x536AF78AA2499B19ULL, 0xA53B473123782C58ULL, 
            0x1B3DC8FCFD5E00CAULL, 0x79E4C762FDFDA606ULL, 0xEF8E25600EB7F8B9ULL, 0xE7AB34E06E5CCD61ULL, 
            0x46E825B5844DAADAULL, 0xE4C5570AD2DD6547ULL, 0xE0CEFC3D0C699A6EULL, 0x9C76095562204F14ULL
        }
    },
    {
        {
            0x145DB3AB77F6F164ULL, 0xA4D191357CB1D8F1ULL, 0x6B20FC9CCF87A463ULL, 0x0B03E1A9C931C8BFULL, 
            0x49BCA66C4952DFB1ULL, 0x3C132EED5B0FF642ULL, 0xAC9231C8F289F7A0ULL, 0x186B9B39D2368675ULL, 
            0x59FDD957608F5929ULL, 0xF9FBFAE4041A7543ULL, 0xF9A3B03300939CE2ULL, 0xC19B5CCB489C9D15ULL, 
            0xC5092DF5DB531E89ULL, 0x2DDADBF8A5E55F87ULL, 0x7D9D411543FFB1ACULL, 0x2B96D8EDF9175AA3ULL, 
            0x6F4F2F77CFE6231AULL, 0x3AB6313DE4A2ECC3ULL, 0xD7964085DAF502ABULL, 0x995FBEF62CDAA162ULL, 
            0xB828B2B609677A7CULL, 0xDAEBEDA34C4F5C12ULL, 0x7E524A635AEE292CULL, 0x4F81CBB430025143ULL, 
            0xA4D72F82C06CBC98ULL, 0xEA43E03BB8B50833ULL, 0xED5C208275FDC638ULL, 0xCAB3BE70B06DC01EULL, 
            0x54C1E8071967C0C6ULL, 0x46EE75D196827E65ULL, 0x36016FC097EF0A2DULL, 0xF0A931AB462BD2F6ULL
        },
        {
            0xBC15BAC5EC9F06A0ULL, 0x9DEBEE5BDF24ACBBULL, 0x0AD31BE55F4FED35ULL, 0xC58CAEB4E8DFF395ULL, 
            0x730F22CBE3D7368FULL, 0x58BD3793DE821F65ULL, 0xFEA0E8E2D43F099EULL, 0x347C33DBD6AAEF88ULL, 
            0xD21F3BBF21878642ULL, 0x8DC8A4856CF7CFE7ULL, 0x28AE93309FB7AE6BULL, 0x555C14D14F245F7BULL, 
            0x880EAC3B40EEF8DCULL, 0x39EEE880199DF40CULL, 0xCAADC91BD9AB8FFAULL, 0x2D31B94E16519AB6ULL, 
            0xC218064A756D9CC7ULL, 0x0EFA6AEC13C03A1BULL, 0x6E051E92A07DB4C7ULL, 0x835C937B17F1C42EULL, 
            0x2B97D9160C016CBCULL, 0xD6BA68C28D321342ULL, 0xC40E8080C64DF061ULL, 0x6F6044A064534DB9ULL, 
            0x5BA62778637B0C58ULL, 0xE094F6894ED0A4B7ULL, 0xD9C9069F44E97C87ULL, 0xB60B4F26C9FB11CDULL, 
            0xF0138E9B2E751FA4ULL, 0x5AD59CD264F23009ULL, 0x5F8E3DDEC1724028ULL, 0xF924A7114E46BBF6ULL
        },
        {
            0x507F6498E92DAB8FULL, 0xD15963E50A589A24ULL, 0x658926C78B40C4F5ULL, 0xE1877D6ABE3C7744ULL, 
            0x400CAB23CE637EC4ULL, 0xE72D8E767347C231ULL, 0x31847A5B999D6628ULL, 0xA4126733C6043C7AULL, 
            0x3994E330FC7284F8ULL, 0x2CE0AB0D1C068C14ULL, 0x44B26D8DE1A90D7AULL, 0xB1E151479C119BFEULL, 
            0xF92B0AE0D397BECFULL, 0xED6EA04A64399032ULL, 0xAAA2787628A25F33ULL, 0xFCC2DE028BC2394AULL, 
            0xD047D29BFE3D3CB3ULL, 0x3D1DA214D9B92385ULL, 0x0375CCDDB6DF43F4ULL, 0x0C02EE53A4F88177ULL, 
            0x7483ACD0C7BB2155ULL, 0x6260E2718803F472ULL, 0x60B85B4F7B830ACAULL, 0x861C1939844554B1ULL, 
            0xBA3BDFDF39223568ULL, 0x0E90CFA2C241A953ULL, 0xED17EC09170FE61DULL, 0xB35565C700AFD0E1ULL, 
            0x0E05329228FC7770ULL, 0xB4CCE8478D1DCF6EULL, 0xE328F3F28C7B6AABULL, 0x61BFD43FAA4B7EB9ULL
        },
        {
            0x65BDD297C221BA48ULL, 0x51D16D67F33FFCB1ULL, 0xB232402C26A1526BULL, 0xDA968D1D2E790F2AULL, 
            0x978F00B5B53DADFBULL, 0x980BAA54A7F35579ULL, 0xE02D2C8DC49A0699ULL, 0xA45EB1515757BAFDULL, 
            0x4B209F1D10E086C9ULL, 0x7284B5534EA111AEULL, 0xA8819BD378EE84E7ULL, 0xB77F332FDF0A7708ULL, 
            0xB558F59FB6275DABULL, 0xC9A9CC767BBA7A83ULL, 0xEA198D234AB90EDEULL, 0x3A051F8CB497FEA7ULL, 
            0x8B9BBFE37276C20BULL, 0x0A49FC248D384062ULL, 0xF9D9CE7B59EAAFACULL, 0x1E8C15FE6B26A356ULL, 
            0x5095BC783D4F2866ULL, 0x7A3F9E08713CC115ULL, 0x7330D0124BC991EFULL, 0x3EFB0D6369C01AD6ULL, 
            0x02311965AC04D23FULL, 0xCD5CEA5090A031B0ULL, 0xD81A47622F031D14ULL, 0x923A4E24BE64F458ULL, 
            0x0CE672190EED168FULL, 0x4CD13B9966B4C842ULL, 0xC216128155BE3B3CULL, 0x6D5711E09A135499ULL
        },
        {
            0x835219FCF581AF6CULL, 0xE51B5E3B9014668EULL, 0x9D2BF4A685AFB3C5ULL, 0x6F1F0BE1DB653921ULL, 
            0x41D5A91D9C5C4445ULL, 0x8B8A46BF3571A509ULL, 0x1AE215B25470BF9BULL, 0x98299C5A4579B54AULL, 
            0xDCFB55271CE4126EULL, 0x46318F378A372A2AULL, 0xCF69B10FC8FFDB2DULL, 0x9741ED27FBC727E9ULL, 
            0x11700ADF547034DBULL, 0x6A7D9D58BEE8F6DDULL, 0x03D0D3DDAE174289ULL, 0x5EA22F36A74F5145ULL, 
            0xB76B25F4573BDF38ULL, 0x9FAAC418238ADA60ULL, 0x2FBABD32A7F3F3F7ULL, 0x5912EC62488360FBULL, 
            0xE84A13938681F6C8ULL, 0x8D705CA98AEDD0A2ULL, 0x37C04BD60920F34BULL, 0xF395CFF9191F512CULL, 
            0x816BF31B27284EF2ULL, 0x18E2B3A603F12C6AULL, 0x6B35E8A56928822CULL, 0xAE81767274085A85ULL, 
            0x2829BEA6CE0EED9FULL, 0xA40C40C7E6E3E24DULL, 0xD22349AF15AC0868ULL, 0x485C7085FF75374AULL
        },
        {
            0xCBA0878B87154FCFULL, 0x9621F7A5B256FD20ULL, 0x5A6BDCF2BDC90A4DULL, 0xE5797336E80C629BULL, 
            0x59785F2758C1FFF9ULL, 0xA456AAABF8DD510EULL, 0xF0FC71616D9669E0ULL, 0x1D7451AD3C10CB2FULL, 
            0x616645B6C64D1206ULL, 0x33A058668A413124ULL, 0x0C87999CB25B10A2ULL, 0x54B95C58ABFD041FULL, 
            0x001BE6F2C880BAF4ULL, 0xF61A121C24712CA6ULL, 0x726D3D4FE3FC3AB6ULL, 0x7049630A4DD2DD67ULL, 
            0xDA09A7E41D0D34F2ULL, 0x12D089CCF99BFBF4ULL, 0x8CC633C94688C682ULL, 0x3AAFC435AC673401ULL, 
            0x68CA0AED8F97587FULL, 0x39C0E67E350CA092ULL, 0x8AE8E1917D86FEC7ULL, 0xADAAA9853235273EULL, 
            0x66DBDEE68C43A6FEULL, 0x91015FEA2FC3737FULL, 0x4F625985B50B740DULL, 0x00394900FF19D79BULL, 
            0x1DAA80034088684AULL, 0xCAF6122F32EF2D97ULL, 0x4606DA6AB360F0A5ULL, 0xB174C07CE772E940ULL
        }
    },
    {
        {
            0xEA474D8D916399D5ULL, 0xC1FCCD43FF0FB67BULL, 0x3F9D79360D758520ULL, 0x9EBD3333C11C1B09ULL, 
            0x06B46918EAB1FA51ULL, 0x07B88D0E4D8601E8ULL, 0xC1B1CE3CABD63EF2ULL, 0x552D02BC99451069ULL, 
            0xBEF09477A4C8D3E9ULL, 0xA6031C809F8C449AULL, 0xCA64600B9FCD3E59ULL, 0xEADFA85732D6EC9BULL, 
            0x9A4F8AECBBC2263EULL, 0x5CE2E27C375F76FDULL, 0x4BC1E6B3C6C66613ULL, 0x8B55A1211A4E61F6ULL, 
            0x15209BFE7520A502ULL, 0xD0BF4281DD0C0592ULL, 0x58AF044D648CC734ULL, 0x133F7141BDD8937CULL, 
            0x14C64AD09FE64671ULL, 0x5FDB44487A62434AULL, 0xCE6AFE91585063F4ULL, 0x2E9DFE18A00344ACULL, 
            0x17324B20602CB1B3ULL, 0xAAB540856F2D53EDULL, 0xEF3C01FF2B6F4C6CULL, 0xEBBA3423170D43D9ULL, 
            0x56609CD09D63C43CULL, 0x270B5A161A58FA0EULL, 0xD0F28B22AA377C7FULL, 0x2D4D160209162BBEULL
        },
        {
            0xA310A38CB376F60EULL, 0xB3A566917E4CFDEDULL, 0xB37BD24BE8BBF3A7ULL, 0xBF071D911AA451C6ULL, 
            0xF9A983E97B2252B0ULL, 0x5A8E81B4399BEBE9ULL, 0xE3F09CDD9D88B5AFULL, 0xA7E04EF1B08DF89DULL, 
            0x4F5CF6123D92E597ULL, 0x3A81DF54F036A0A4ULL, 0x05C71C878787FCDDULL, 0x022CEF860C7C967BULL, 
            0xC78B11F3636D6E46ULL, 0x72693128B6F776E1ULL, 0xA1335BD7073BACE2ULL, 0xC616B025A85FB37FULL, 
            0x38D61A9FF65F5CA6ULL, 0x7C060B71BE516511ULL, 0xB6D7A5D97A687159ULL, 0xEAD94790BED2107BULL, 
            0xD99BF244A4D63B15ULL, 0xD294ABFE4305E226ULL, 0xDE7DAAF9935604C9ULL, 0x1424AB692AC66179ULL, 
            0x175BC80E32CD8732ULL, 0x79DC04BC837FDA74ULL, 0x7A3CEFBF52B438C7ULL, 0x513E4407942C3AD3ULL, 
            0xEB5EBD1E051EAA09ULL, 0xFACD6FE4858D466DULL, 0x5E0C2154D032C37EULL, 0x1F14DCD56F4E9A86ULL
        },
        {
            0x1750360EB9582B88ULL, 0xF983C64119FA58ECULL, 0x496FC12C572D1464ULL, 0x00A77C8D5C2408EBULL, 
            0x7BB3F937ACE05EA6ULL, 0x2E449C382F23CD20ULL, 0x43F138C8D0EDDD09ULL, 0x0651D38FD6B9D92AULL, 
            0x97FD14457B2409E7ULL, 0x9F36FBD008AC7959ULL, 0xEA77DA6071B5E44DULL, 0x80C2626F9B1A01B0ULL, 
            0xEEC44AB0C83B4CEEULL, 0x660C1D4151298D62ULL, 0x8134BEEA694CF83CULL, 0x23D9DD21EB2BEB73ULL, 
            0x0A7C80CA029B2D1EULL, 0xCF9F7459D3C6270AULL, 0xDB21BDEF5DA5517AULL, 0x3C08972FAB0ABD3DULL, 
            0xEDF929DB37621461ULL, 0x9DD8F19620C52694ULL, 0xE7958ADCC07D5D46ULL, 0x28EEF5F204DEC64AULL, 
            0x8EFE69367B896A66ULL, 0xAB21528B715C5E1FULL, 0x4D868168D2A9B582ULL, 0x521467DA8E695BC5ULL, 
            0xE7F8448AE110E782ULL, 0x6F2FC947CBE81E71ULL, 0xA27302F93726664EULL, 0x2ACAFAFC4D70CB82ULL
        },
        {
            0x2DF049960DF4711DULL, 0xCCE8AACA42F03342ULL, 0x86438591716228ABULL, 0x033E1A83AF6EE68EULL, 
            0x9054A903469F3B60ULL, 0xC0041A11147B11A9ULL, 0x341EEB70AF87EECCULL, 0xCDAAEBB59EE2A10FULL, 
            0x877257599314BF57ULL, 0x8FC5153D2B8B613FULL, 0x0117CCEBF3FF28EFULL, 0x1860DC327C6D3404ULL, 
            0x2FD30FBFB619996DULL, 0x69544F8F349C6C2BULL, 0x0B403474088EF66FULL, 0x811EB3D88239F445ULL, 
            0xF258AEB6571F773AULL, 0x0732BA21E05B43AEULL, 0xD69EE89654FFA8CCULL, 0x5A1D8FE215B54B0FULL, 
            0xEBA932DB2F0F1E17ULL, 0x1098424388F6D57CULL, 0x85C1E6C24B3AA157ULL, 0xC41CA645805C42DEULL, 
            0x588B6577624D66E9ULL, 0xB3D08D8A8F125896ULL, 0x90E3C2633ED0B03EULL, 0xFE968D1BFE144176ULL, 
            0xD24E75A4B020AB69ULL, 0xF81C8631BAC36441ULL, 0x45DA1B7402594977ULL, 0xE8F5353B305E3F33ULL
        },
        {
            0xD592677BAEDC373AULL, 0xEC9FDBBDB4D198F4ULL, 0xC6A35E201CC81351ULL, 0xDDF5AA3C5FF41313ULL, 
            0x9897E109B254D920ULL, 0xB7D70D90E283EFEAULL, 0x26FF672A6276D000ULL, 0x73E5CF25FC2DA3DBULL, 
            0x3EFBFF3004D059B2ULL, 0xC24CA41B950109F4ULL, 0xC930C76915BABA48ULL, 0x9FDAB6CD2E9B9956ULL, 
            0xCE2C76182082392CULL, 0x1F657349EC66BF88ULL, 0x7C91C1112182D7CEULL, 0x42325E5DD82E0390ULL, 
            0x6B8EB21AEFEB7034ULL, 0xA11465331C862DC9ULL, 0x8CBA65FD86623617ULL, 0x6FBFEB732F99A3BAULL, 
            0x2121FDC5F91C2350ULL, 0x9A2D2BEE54C57485ULL, 0x1977D3EDD540997CULL, 0x5789DDCDA7B2BE47ULL, 
            0x619A47043F8F0698ULL, 0x5661A84981924121ULL, 0x029A66EF63B1E87BULL, 0xE15874E63ABE15ECULL, 
            0x99DB185918CEC580ULL, 0x60909A3CD35EBC75ULL, 0x6701D7AFAD5612A6ULL, 0x3FD53574BB52C391ULL
        },
        {
            0xDFDA968839CA35CBULL, 0xC3A8C7504C7918D9ULL, 0x1FEABE94AC5C5890ULL, 0xE22F8FDE9D6B661DULL, 
            0x794C466A10A9AABCULL, 0xF38DBC3D3DACF170ULL, 0xA762F2765609847DULL, 0x6792DC8DEC7D3CD3ULL, 
            0xC483DA9316DC9283ULL, 0xAEAD510B52E7B2E0ULL, 0x17D6E22984319C3CULL, 0xA0B6E7769292A5C5ULL, 
            0x6A663EBA52C81628ULL, 0xAA5655988684A6E7ULL, 0xE86AD413070FF9D5ULL, 0x3DF78F1CDE75EB31ULL, 
            0x4C3B96105A02FCD8ULL, 0xD3BD3C82B056F2CCULL, 0x58011200873031CFULL, 0x966817369FBE2FD0ULL, 
            0xB8865C9B0CE52ACDULL, 0x2D6448BF6DCE984DULL, 0x04D0CA27BE1842C9ULL, 0xCF26AE169C5A6161ULL, 
            0x330F577716767615ULL, 0xFE6EF354852B64ECULL, 0x66ED44614E655EA5ULL, 0x73F9932BB152026CULL, 
            0x62360A8AAC3DE6A5ULL, 0x803F0D23A592D6B5ULL, 0xF8F57850117BE0E9ULL, 0x0837260731944E94ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseGConstants = {
    0x6217F5AFD68AC8EEULL,
    0xB3057C781E175E85ULL,
    0x1C6CB998C3C55A71ULL,
    0x6217F5AFD68AC8EEULL,
    0xB3057C781E175E85ULL,
    0x1C6CB998C3C55A71ULL,
    0x1663F7E0B7C07CDAULL,
    0xB492FEC0ED3A7136ULL,
    0x59,
    0xCF,
    0x64,
    0xC8,
    0xEE,
    0x07,
    0x4B,
    0x04
};

const TwistDomainSaltSet TwistExpander_Alnitak::kPhaseHSalts = {
    {
        {
            0xBF5007615A7AF509ULL, 0x6297EB4986B19441ULL, 0x7E51AC1D0CCE5194ULL, 0x1FD19E0C009E39C2ULL, 
            0xC2C7604D213FA673ULL, 0x155BD7E3747A3357ULL, 0xEA11B9B5D57D953AULL, 0x560426380813C5FFULL, 
            0x2C3E944FF5E0FD73ULL, 0xCAF07257A4C61845ULL, 0x98A8C06BC15D6C90ULL, 0x003C7876223FB02AULL, 
            0x63F43771290E5FC4ULL, 0x2667441BB937513AULL, 0x1ABFBDD1D7C5AC99ULL, 0x377C0476642A070FULL, 
            0x9DB0217D2E8F564FULL, 0xFBD97BC7C848D663ULL, 0x32163855D65E9A23ULL, 0x5B09A0013395B567ULL, 
            0xCA7271AADC2A4A6DULL, 0x808312E91D21C01FULL, 0x6278C3D399CE83B2ULL, 0xBD159E3406C27FC5ULL, 
            0xD1B23316431EA1E7ULL, 0x33CECAEAC208DC8AULL, 0xFBD346A170740531ULL, 0x42EC20B0B265DA82ULL, 
            0xFCBA1811859AD1D8ULL, 0x931AA81BF2A3D098ULL, 0xD704A889CB3F306AULL, 0x41B0A88CDFACC598ULL
        },
        {
            0x45428F229685214AULL, 0x7B7F0AC7C0766B5DULL, 0x334DCB0D9F6448A6ULL, 0x10E0D81F70AB1EE5ULL, 
            0x4B5AD6C988C8EE39ULL, 0xFCE24748CE544161ULL, 0x550D7B4FC515E920ULL, 0xC6D7CCCE0014A481ULL, 
            0x53CC2C5CCEA2E4A4ULL, 0x85CE585799778DB8ULL, 0xA5B02576433E6C10ULL, 0x25EF365100C2B2ADULL, 
            0x2F695FFED34A5A9CULL, 0x40D8F9B35DA659E1ULL, 0xC5533C06CECED3F9ULL, 0xE4149886C8A36005ULL, 
            0xBA2D955FD8A3A1CEULL, 0xB2F992D232DE3BA9ULL, 0xB83C41B18A616411ULL, 0x2EBF5DA80DB47C71ULL, 
            0xF6AEFE87835AB266ULL, 0x4CB80FEE3134FAECULL, 0x5F4957B1834F319FULL, 0x7A7826806171C274ULL, 
            0x0287B69B63AF8403ULL, 0x0AF816459C2632A9ULL, 0xBB7C89DE5676AC9BULL, 0x12C4EC7B5A787198ULL, 
            0x470CF8099F45B50DULL, 0x066D12F12EA236C3ULL, 0x50F212F5CC353A1DULL, 0x74BE74CE6FB6574DULL
        },
        {
            0x0AECCC187E8CC36AULL, 0x94DE14098B9E9697ULL, 0xD6F79E59BA3830D5ULL, 0xFDCCB1BCAFCF5C67ULL, 
            0x6F084C951C6941F9ULL, 0x1A5FAFB04BAFC2EEULL, 0xBFE0981A27E19068ULL, 0x539767437E0F68A1ULL, 
            0x5CC0104A70ED42CFULL, 0x9F626E9382BC70FAULL, 0x92062283C80A0E6BULL, 0x207E115778F03B1CULL, 
            0x021E0699A28C7493ULL, 0x3432896574D98EC1ULL, 0xB4D89CC15E8640D7ULL, 0xDFC14F1D59911DDFULL, 
            0x8722F10BC0C01798ULL, 0x1A6EC1AC95364D64ULL, 0xD7D462B144EF70F4ULL, 0x099C8648045E246CULL, 
            0x20289E4B04030DC4ULL, 0x8BD2FC27D7DA6653ULL, 0x0167EAD67F869D88ULL, 0x34CD0D7F3220D849ULL, 
            0xC38AAD3C8730235DULL, 0xF60DC99AB0B08561ULL, 0xB05ED3342E007F81ULL, 0xEF4FC9C652E1CE5AULL, 
            0xC48686D4E9F424E5ULL, 0xA8981B55A01F7134ULL, 0x91792B60D8B9855CULL, 0x2C62150B29E6DA87ULL
        },
        {
            0x245AE3A31D8E6CA1ULL, 0xE43A238FE09A53D9ULL, 0x5532B27D9A3B34ACULL, 0x4AE73A3E469176E6ULL, 
            0xC022E76557AACC87ULL, 0xB63903DAC33D5EBAULL, 0x35EB921E39A23659ULL, 0x127F9F80DBD0F341ULL, 
            0x2679F974ADCA809CULL, 0x401ED00F106593EEULL, 0x292F7CEB05EF9999ULL, 0xF454C38561D7EBD7ULL, 
            0x4CE09103E14AD873ULL, 0x4D4D3AD388B5171AULL, 0x922D53117EA6F861ULL, 0x3E26A87E70E1FEBDULL, 
            0x72C9511AA1C10B50ULL, 0x64D1E7CD63BD8467ULL, 0x27D88588AB9A0C70ULL, 0x64E6927D2B0397A2ULL, 
            0x731A88047EA34973ULL, 0x6A91F661ABEFB9FDULL, 0x0501CBF697CE7E3AULL, 0x63E55111563DBD24ULL, 
            0x0A79C104860B06D3ULL, 0x0038F4E93169BEB7ULL, 0x15F19937F063921EULL, 0x083C96705B612FF8ULL, 
            0xEEF4BFE2E6AA5650ULL, 0x52843224AAD396B4ULL, 0x97BB91CF61AA01BCULL, 0x0A48ABF3CCDED2B0ULL
        },
        {
            0x9BE4D8C24B0765C9ULL, 0x65B741E73AB5BF12ULL, 0x0BBD19DFED4BFA17ULL, 0xDD01C7F27028FD40ULL, 
            0xB7A09C41FC03E35EULL, 0x86E0237298F97322ULL, 0x4B719539D2CE5961ULL, 0xB596E21F4F15CFF7ULL, 
            0x41AFB55F5E404DB5ULL, 0xC18D7EF49D88FA94ULL, 0x66A3571E18D478B6ULL, 0xED64FB5504ABE0A8ULL, 
            0x85578F8BBE399F7CULL, 0xC6B9F698ACB9715AULL, 0x86F2EECD28C249F1ULL, 0xF364821557E41822ULL, 
            0xF7BF93392A05146FULL, 0x47C99076B3EE711DULL, 0x0F4AED3532B15587ULL, 0xA68E927C55CEB002ULL, 
            0x5CFB7CE56A72D6D0ULL, 0x2878FD6F15BA6BD7ULL, 0xEEA85A0340BBF57AULL, 0x903E47349CC460A0ULL, 
            0xF2C4494AB8D6B148ULL, 0x3115F94331CA4A7DULL, 0x0D854F7397F4CBE4ULL, 0xF8323DA4EBDAC616ULL, 
            0xA6784D14E5F8E211ULL, 0xA6306D6128FA5983ULL, 0x52BFA3F25C7A9B76ULL, 0x7BA6A979CBCB64BDULL
        },
        {
            0xFD5170220D051153ULL, 0x270FC71EF919D961ULL, 0x06AB7530993456F4ULL, 0x2415CE4A0B6667A0ULL, 
            0x8E6B55426FA49873ULL, 0xA3C93F13ECC0FFDBULL, 0xCD75EB196E112CC1ULL, 0x46E0B4F6D478A7B2ULL, 
            0xB87295D3EB152AE2ULL, 0x748E6F2B2B047EBCULL, 0x72448131D127D05CULL, 0x9A093443A5960613ULL, 
            0x0C0F8B7EB034E146ULL, 0x417007476D13B86DULL, 0xF6C40A9D1BF4416EULL, 0xF819854264067826ULL, 
            0x7C4D0D3C0D08C836ULL, 0xC6A6A7679A38CEE2ULL, 0x942D0B5E498456E2ULL, 0xACA01282BD4BEAC4ULL, 
            0x71250B2545CD6BE6ULL, 0x3ADF3FD28110AAF2ULL, 0x55E7A40D289B7E68ULL, 0x1634F692D58FA661ULL, 
            0x841D0500B96DA053ULL, 0x644D4D42FA9B562FULL, 0xA92E943D8D33B7B4ULL, 0xBD0A8E0B4EF3BE76ULL, 
            0x20CBB49E8AD85825ULL, 0xC4762414507149BEULL, 0xE289B5170BF40F19ULL, 0x47F92766373BDB9BULL
        }
    },
    {
        {
            0xF76A7FA35946B0C9ULL, 0x31A80B167D52C47AULL, 0xACCEA9381BC5AEC3ULL, 0xF297CF9DE1A2F4C2ULL, 
            0xED59E0EC081FD530ULL, 0xAC3740F4333FD323ULL, 0x6C967AABB6D085E6ULL, 0xA3835F7F7E43DE95ULL, 
            0xB9BB1B5F83C39698ULL, 0x8B3396D4E870ED52ULL, 0x6ADDAC0639BE5355ULL, 0xD4F7FB32309DC147ULL, 
            0xF31C8E6D157738D7ULL, 0x707917C8F5541735ULL, 0x83340F80F7DEEBADULL, 0x0C189C7A9CCA4336ULL, 
            0x1479EA04F1C0353AULL, 0x3EF8DE1C23D28BC7ULL, 0xB593269DEB1BDD0DULL, 0xEB8DADE463764137ULL, 
            0xDBA8E76B11DD1E46ULL, 0xC740C1C2C6E139FAULL, 0x54FFEEC496AF5383ULL, 0x4E4727E1CBFD56EEULL, 
            0x764C931707384E55ULL, 0x3C6044C78721186CULL, 0x2C42D9F685A6E408ULL, 0x136702E20D4DA360ULL, 
            0x0C20CACEAD3F34B2ULL, 0xEED9A218912FA20AULL, 0x321A63A1118E9F93ULL, 0x0C7DF580FE73B41EULL
        },
        {
            0xDC87E958D7B74D57ULL, 0x7A3D0B9D6971DB7DULL, 0x74645C0FC5B8D2CEULL, 0xECDD1B8EFAC2240AULL, 
            0xC667E7041F669E87ULL, 0x59657ACD531FC122ULL, 0xA25B6D7D495E0AE4ULL, 0x6B55A7BCEF930AE9ULL, 
            0x8E611B92377053D9ULL, 0x90775E96481430AAULL, 0xB49D398CD117BFB9ULL, 0x11F1EDE5DDBE55CAULL, 
            0x4ED39F301553918BULL, 0xEC7E1D9CE39AC013ULL, 0xD249F1FD85459558ULL, 0xB5CB6DC41D1883DFULL, 
            0xAD3FC094ABC956FBULL, 0xDCCDE84ECCB9213EULL, 0x7F05C4C4FEFE9E31ULL, 0x434CD74A1214B18FULL, 
            0xFB732298412AF9DCULL, 0xE36C602126A14864ULL, 0x9AF350046A671933ULL, 0x2D6DB4435E305E9EULL, 
            0x43693DDCCACB17BFULL, 0x468D1E9C77D3E7E9ULL, 0x0B0A48595ECC751AULL, 0x841C64F3F9A62019ULL, 
            0x20F92D09301DF2EDULL, 0x9B9CBD3C82F4BF99ULL, 0x601EDED3C049E497ULL, 0x3121D1EC501DEC05ULL
        },
        {
            0xFDFA8AA0343EB432ULL, 0xBAF003F60A304425ULL, 0xACF324C48D1920B9ULL, 0x2E03EE01493D5404ULL, 
            0x34DF1F24007A390FULL, 0x7C9EBDDD20518E01ULL, 0x79874260F455E9D3ULL, 0xB4A629FEE780F3E8ULL, 
            0x6DA6171CB5D6D0FEULL, 0x3D5F9B0F28CA52CAULL, 0x7DBD4D48C69F74A5ULL, 0x631045822413B050ULL, 
            0xE5EAEB2F02F3709CULL, 0xB7E032F4D5C291C3ULL, 0x08B5E48F7854FC2CULL, 0x5047B7D4A8D2E2EBULL, 
            0x7A80A50DF31FEC09ULL, 0x2E7B33E3D1A2DABDULL, 0x6EC890F17E0E0CD2ULL, 0xF8256FEE7F6EC67DULL, 
            0xF2FFD8A140742964ULL, 0x3571AA5D9D60A88AULL, 0xE5CE0B211CA06FFEULL, 0xE88A7CC1949B975BULL, 
            0x04A99DCD1D670CAAULL, 0x6FAF28FDCCC15DB2ULL, 0xDDDC181A0064CBAEULL, 0x26CF41607DCF5D07ULL, 
            0x121FC63365038DB6ULL, 0xD8B8327E5067A2F4ULL, 0x1B73B7C4974875C8ULL, 0x75DD45C716528240ULL
        },
        {
            0xF68A749A8C3DA21FULL, 0x02CE7A820CC14CA8ULL, 0x2863FB5BBCDB6387ULL, 0xB197829C966C90F9ULL, 
            0x3DA7136EE63BB4BEULL, 0xBF107C3C85C0DDE5ULL, 0x45ED5636E994EF89ULL, 0x2808F91ECEA5CCD3ULL, 
            0xAD97329736D9B5E7ULL, 0xE43309B1268EEEF6ULL, 0x189CB43C56755881ULL, 0xE1C138CD5B15BDC7ULL, 
            0xF4F6883CCD477EE4ULL, 0x2D749D5BC18CF4AFULL, 0x89620370C4B19F1DULL, 0x1A276BCF1B14FE14ULL, 
            0xC43AB7D097005948ULL, 0x6488C3A58BCAABE3ULL, 0x8ED87680B9F0DE0DULL, 0xAAF5727813A50830ULL, 
            0xA15660E2D2977D87ULL, 0xB367FF947BAC8D64ULL, 0x3ACBEB8D40BED053ULL, 0xB22C034AD62761C2ULL, 
            0x71688199A460B13EULL, 0x5DBD87389A3FE117ULL, 0x68BE5B5DA1384BD6ULL, 0x7FDDD6BFCD344436ULL, 
            0x2ED1390CF435F6AFULL, 0xA1D60B607BFC8F01ULL, 0xD20BD3DBF77643E5ULL, 0x82AF02AC3426D6CBULL
        },
        {
            0xC7F96EA41B424699ULL, 0xB4BB3732110A5A88ULL, 0xF828ED56F521E8E9ULL, 0x6AD5D80DE45265BEULL, 
            0x45607D4B95DD8675ULL, 0xC25D40E14FBC578AULL, 0x2615805F66D55C70ULL, 0x3FBAF7C383FED23FULL, 
            0xFDD1B111AC74B719ULL, 0x5D239261B311DE81ULL, 0xDC1C8B6B21E7465EULL, 0x6C112B35630079CDULL, 
            0x5315887D5FEE0DF1ULL, 0x57D3E2DDC04E2F29ULL, 0x79C2A2E036640897ULL, 0xA0A751E8BB81C4C8ULL, 
            0xE12CB0CCF3991A16ULL, 0x4B5E82DCEFBDF61BULL, 0x86A66B12EBA0F811ULL, 0x6C3D9CDA5D280A42ULL, 
            0x16532192D043F2A4ULL, 0xBE719AB82359CDC4ULL, 0x2FECBADFA1F7EE03ULL, 0x81AFD66AC95490F9ULL, 
            0x5DC1FEFD33D61826ULL, 0xFBD01B87395ACAFCULL, 0x787D4A9F9E3E4427ULL, 0xC512BBCAB8210480ULL, 
            0xF4EAF85B829CFD5AULL, 0x7ABCD3F9E5F50267ULL, 0xC49363C51C2CBAAFULL, 0x5C3D2549225BAE49ULL
        },
        {
            0xB2ECE960BCDBE3ABULL, 0xC1C57050401686F3ULL, 0xD8FA593FB2FA7D56ULL, 0x04AF34519A9E44A8ULL, 
            0x4C06950E7A76A4F8ULL, 0xD3200425F3F59635ULL, 0xFE6724177DE1DFEDULL, 0x3E43FAF93B083155ULL, 
            0xFE934A8EA5142FE8ULL, 0xFC8A02BFEC9CA81EULL, 0xD33E1B24DC3DB655ULL, 0xB1A536E9C8789B6BULL, 
            0x520C38113705322EULL, 0x0FDCC6F1E964D087ULL, 0xCD2B45EFE304B1A1ULL, 0x06AD3C7E0D554B0BULL, 
            0x5CAB88A2B907D1ABULL, 0xD3340B34A4A59A46ULL, 0x0028724EF98DFA02ULL, 0x94B7A95BEDECDC51ULL, 
            0x28E8D39D636319BBULL, 0xC19A7A1C7FFA1C9AULL, 0x76F3AC643DD420F3ULL, 0xB24FB81B6DE77E7AULL, 
            0xE0751CACAAF670DAULL, 0x7224367FAC068F53ULL, 0x6B7C5E71A7F33BF8ULL, 0x99A1006E38E0DDAFULL, 
            0x68D5FE24A1D9816AULL, 0x8E061FCAAFA99688ULL, 0x87CD54E5B86837DDULL, 0x387AA3771D1766D2ULL
        }
    },
    {
        {
            0x8881808B0DE6F607ULL, 0xA7A231F3935494BFULL, 0x69DCF5F2D0AB314FULL, 0x009355685751E63DULL, 
            0x05BB6DDA374CD2FFULL, 0xE67F014D67EC16BBULL, 0xAD2A895906B91DF5ULL, 0x0D3D7282A9AF6C92ULL, 
            0x44BFD02D0598C352ULL, 0xB2CC897EC65E1265ULL, 0x5F6282A61C30169EULL, 0xAF869DB21904EBB8ULL, 
            0x259D2F636ACE1CF8ULL, 0x486C0B00E602CE3FULL, 0x9A429D1A16CC519EULL, 0xE7A8A4E46406E02DULL, 
            0x68E94945B4431485ULL, 0xDD461EDC8F4608BDULL, 0x2FC54A96CB4850F3ULL, 0xEDF974AA57DC1C23ULL, 
            0x39231B81A1305E7BULL, 0x138A3F6B1EDAEBEEULL, 0x3269E606A368141DULL, 0x0B39F0ABFD4E9C37ULL, 
            0x14046B39235FA2C5ULL, 0x2DF9B276614D9BA2ULL, 0x2F8EC9010050AF3CULL, 0x1583957361B783B1ULL, 
            0xD50FF04857BE374CULL, 0x461F8897A8BB7F86ULL, 0x5F6F78257119C490ULL, 0x051A1950579F98FCULL
        },
        {
            0x3DDBD5B1B53C695FULL, 0x1E1093BA453998EAULL, 0xE43753301E844D4BULL, 0xCAB326DBBE36C4BBULL, 
            0xD4F56A00CC9168FAULL, 0xE311C0C7C2DBA7EAULL, 0x186833DC186450EBULL, 0x4E1F2AD06905CEC8ULL, 
            0x76D5EE1753FF04CBULL, 0x67A90994152707F7ULL, 0x83FECCC8EB5EE8F7ULL, 0xA0971ADD02E870B4ULL, 
            0x369C5B72611C99ECULL, 0xAFF7CF6AF469003EULL, 0xAA67AF236196783DULL, 0x3D3EF623DE265B17ULL, 
            0x0C3AAD9636E0EF37ULL, 0x5B65EA926E68891BULL, 0x78453C110309038AULL, 0x4EF33D36EFF30E45ULL, 
            0x9C3D6F3963373719ULL, 0x0586CCC40E7570D9ULL, 0x041518EF752A3B5CULL, 0x7C43C26DC1F5B2D0ULL, 
            0x3CBBA9CD005B27CFULL, 0x2D038F6223AF4A36ULL, 0x55A28147551FDE29ULL, 0xFB9A1FD3DFA46BA9ULL, 
            0x76A293DAC7309DFBULL, 0x5CD536AC8AC3DF13ULL, 0xF4F16FF450359628ULL, 0x816A80A2B4ADC84DULL
        },
        {
            0xA49ACB338AC6B0B2ULL, 0x92B269237924332EULL, 0x96ECF2EB8AD5CC64ULL, 0x52FA1BA722E538F1ULL, 
            0x963B7E865B20AEFCULL, 0x25D0D237110FA75DULL, 0xE5A4A6CC043BA96AULL, 0xDCDDA1D4E5A7E517ULL, 
            0x03BEEF0302351AFDULL, 0x8A23ABB8933787A9ULL, 0xD8DEB9E828F1B5B6ULL, 0x28050A50C6C8C860ULL, 
            0x1AC65FB4964EA7A3ULL, 0x9EDDCC98A8335F94ULL, 0x779D525B130BBDB4ULL, 0xE065D11F331CDE3AULL, 
            0x1AD1292D5DC5ADD3ULL, 0xF043040D2E555A43ULL, 0x188FCCEB2EAB349EULL, 0x6DCCC5EBE3B41796ULL, 
            0xF49814A750077018ULL, 0xE3AA2BD5553225F5ULL, 0xC6DEEA679AFB1185ULL, 0x5B916622B1DB7CE1ULL, 
            0xC13A9AEA9E9B5048ULL, 0xD2A4C9A6D654B60FULL, 0x8473ACB7BF337244ULL, 0x1C7447B8581BA742ULL, 
            0x985662A7E6B80E76ULL, 0x713B8C9A3E240028ULL, 0x6AE52AF77A2BCB7AULL, 0xEA9A62D9FD7816C8ULL
        },
        {
            0x8281ADE6B32A2632ULL, 0x58BE58FFC55B5BF9ULL, 0x472F633F33316B3EULL, 0x44A425B9772D2D6CULL, 
            0x939A28556DDF2143ULL, 0x5DA2F6D40512772AULL, 0x1494C95754A7FB9BULL, 0xCC84F38191C04DADULL, 
            0xC97AD7F5999FF7D5ULL, 0x8B0AC30039B79133ULL, 0x4274FA0C3205F813ULL, 0x73776A76DD3DF755ULL, 
            0x5CB0323F7DBBD071ULL, 0xA58FEC8D03686A06ULL, 0x486BA5D50ECB0174ULL, 0x3A9713042C0F30D3ULL, 
            0xC6DEF4202ABEDCC0ULL, 0x9DC36E4196D64F0FULL, 0x48BEF561CB19638AULL, 0xB3872EEA5A92AF34ULL, 
            0x6A93E10FBDCBB67AULL, 0xAABFC30E64C0E2C0ULL, 0x5CFBCD73458EE0ECULL, 0x7CCCD925EC6C57C5ULL, 
            0x06AC4EDD0758DB4EULL, 0xA3DC49611E27BC68ULL, 0x0977162830160088ULL, 0x3780079F5C92AC8BULL, 
            0xD1D40F791E5606A4ULL, 0x2DB5EED4A3780BEDULL, 0x1C5A173E7E42FEBFULL, 0x052304C3AB6DDAABULL
        },
        {
            0x982BBC71BF7AAA01ULL, 0x3DDF0DFDD0DF9019ULL, 0x85F17C9936765073ULL, 0x8338FF15AC5EE6EFULL, 
            0xA08A08ABF0DFE3CAULL, 0x6A8D6B4D61D1C111ULL, 0x7031DA0E6ED5AA7AULL, 0x21C3FDA350C77AD0ULL, 
            0x593514EA345A32B9ULL, 0x20968ADE88515759ULL, 0x96FCB1F1E918AC4EULL, 0x1504E9505C692387ULL, 
            0xD9910FC4CBD4E9B7ULL, 0x47799B3BC5344D78ULL, 0x0FDA1B271759D4F5ULL, 0x90F7EAE42435AA64ULL, 
            0x3D8FBC847711E5A6ULL, 0xAB9A14C51460F788ULL, 0x59755AE5E2CB8D3DULL, 0xABB1AFF758EBEC0DULL, 
            0xE774FA02C239C963ULL, 0x93B884B7996D1607ULL, 0xCAE88350D5F0176EULL, 0x60B1A6075B50D92DULL, 
            0x3AD08889081238AFULL, 0x15E621E6BE0AC45DULL, 0x2232E000B68C346BULL, 0x29AE0E2F1EED399DULL, 
            0x49D604CE4011D0D3ULL, 0x98A59DF471321B40ULL, 0x2A3FABED52E07B5DULL, 0xA5900F2113425AB8ULL
        },
        {
            0xE19E98B74DE48882ULL, 0x91B7DFB91A913F61ULL, 0x150CC55A02DD559EULL, 0xFE5C10CCB3CA0A4DULL, 
            0x6F33CB6D1DBAE55BULL, 0x65075F4AC9DED14CULL, 0x381EC58659BBDC80ULL, 0x3EDD40DE20681257ULL, 
            0xD54D2D9302EB9283ULL, 0x3E085CB1F20B4729ULL, 0x59A1F0253E4F4D96ULL, 0xC4FA3D6181770B7DULL, 
            0x6E05A6B05355851FULL, 0x5A1ABB4F6F84F1BDULL, 0x4A97F7373F3A29A3ULL, 0x5252789DFB3CDE55ULL, 
            0x7FD86D546FC58566ULL, 0x7108163A6C5B854EULL, 0xC6A100F17101FA0EULL, 0x9D646FE6C0B778C2ULL, 
            0x34C8AF9B4B4B79D6ULL, 0xCC069C8FC01B1B66ULL, 0xF12E174A381AEBBDULL, 0x9D2F9A9622D998B7ULL, 
            0x5A4429167AF6C66CULL, 0xC302C6F7914051ADULL, 0x033DCD61E02FB8C3ULL, 0x0EFC4C7750338E2CULL, 
            0xF91F72EFC957C0C8ULL, 0x3462A0EEEC98033EULL, 0x8D2A7B15DD1A8536ULL, 0x49E381B706D3C993ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alnitak::kPhaseHConstants = {
    0x155BA058E24ED3B5ULL,
    0x784AE24C8A211056ULL,
    0x5F48C7925F761C33ULL,
    0x155BA058E24ED3B5ULL,
    0x784AE24C8A211056ULL,
    0x5F48C7925F761C33ULL,
    0x1FE34D33CE746AB8ULL,
    0x5DD950E6C9319E76ULL,
    0xDC,
    0xCB,
    0xA8,
    0x73,
    0x1B,
    0xC3,
    0x8F,
    0x44
};

