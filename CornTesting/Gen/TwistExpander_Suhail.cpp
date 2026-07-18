#include "TwistExpander_Suhail.hpp"
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

TwistExpander_Suhail::TwistExpander_Suhail()
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

void TwistExpander_Suhail::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9C4AE92B30D70D5EULL; std::uint64_t aIngress = 0xE9E8B51DDAFC50FDULL; std::uint64_t aCarry = 0xCE58F92F66C85998ULL;

    std::uint64_t aWandererA = 0xE1A1F4A97ED9B247ULL; std::uint64_t aWandererB = 0xB3A2BA7FE14A250EULL; std::uint64_t aWandererC = 0x8812DD3706AEA607ULL; std::uint64_t aWandererD = 0xB875BF801031653DULL;
    std::uint64_t aWandererE = 0xA7399F321E68324DULL; std::uint64_t aWandererF = 0xC5343F4A0F4B4BCDULL; std::uint64_t aWandererG = 0xCFD1ECFA017379C3ULL; std::uint64_t aWandererH = 0xAECFBF37ADADFD02ULL;
    std::uint64_t aWandererI = 0xA6B3A54CE157C556ULL; std::uint64_t aWandererJ = 0xC2FC4D2B64DBD473ULL; std::uint64_t aWandererK = 0xBE611E14E123E8B7ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14361700002019790108U;
        aCarry = 9733974833666522260U;
        aWandererA = 15282082058086598492U;
        aWandererB = 14476550732610139345U;
        aWandererC = 10100416127951231441U;
        aWandererD = 13964457753578915076U;
        aWandererE = 16108762499690514794U;
        aWandererF = 11769475223606303133U;
        aWandererG = 10133254527663370113U;
        aWandererH = 14214499729295991071U;
        aWandererI = 16834176354486548446U;
        aWandererJ = 17889319295170663090U;
        aWandererK = 10079434898678755952U;
    TwistExpander_Suhail_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Suhail_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Suhail_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Suhail_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Suhail_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Suhail::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB716A856D9430A2AULL; std::uint64_t aIngress = 0x996DBB61F0BF1F0DULL; std::uint64_t aCarry = 0xA225F38FCDF8789FULL;

    std::uint64_t aWandererA = 0xCE5512634D5FCBD1ULL; std::uint64_t aWandererB = 0xECA4F9432645DB09ULL; std::uint64_t aWandererC = 0xD5417819F2A82036ULL; std::uint64_t aWandererD = 0xE5512D5A330D4F07ULL;
    std::uint64_t aWandererE = 0x85ADCDC003AD8F4CULL; std::uint64_t aWandererF = 0xEC58F66BAA851129ULL; std::uint64_t aWandererG = 0xA0F819A7E7206F26ULL; std::uint64_t aWandererH = 0xF83F2FC0448CB1D8ULL;
    std::uint64_t aWandererI = 0xE7F91482C8C93D0CULL; std::uint64_t aWandererJ = 0xD49B30BD96D891A7ULL; std::uint64_t aWandererK = 0xF840C5C77A0572AFULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10484745954120373217U;
        aCarry = 10139663819242596409U;
        aWandererA = 10633307750948102785U;
        aWandererB = 17087320782356712576U;
        aWandererC = 13781246774383311530U;
        aWandererD = 9316695768114382895U;
        aWandererE = 10802017395541935888U;
        aWandererF = 13386403317030713030U;
        aWandererG = 13300962489219447389U;
        aWandererH = 14511150923043704763U;
        aWandererI = 13204280279024260366U;
        aWandererJ = 18149432419815246073U;
        aWandererK = 18242060722590786991U;
    TwistExpander_Suhail_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Suhail_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Suhail_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Suhail_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Suhail::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xEFB54DE450331D4BULL;
    std::uint64_t aIngress = 0xF345E2A7C42DC3C1ULL;
    std::uint64_t aCarry = 0xB0FD7F7E7C76AF5EULL;

    std::uint64_t aWandererA = 0xF5ACCFD608E1B4C5ULL;
    std::uint64_t aWandererB = 0xF2ED599F587280ACULL;
    std::uint64_t aWandererC = 0x867F453FF16A8E7CULL;
    std::uint64_t aWandererD = 0x89DBC58EB48324F9ULL;
    std::uint64_t aWandererE = 0xF5CF39676F0387C8ULL;
    std::uint64_t aWandererF = 0xD71A573470D4BAF4ULL;
    std::uint64_t aWandererG = 0xD1B01ACBEA5B4A9AULL;
    std::uint64_t aWandererH = 0x8A4B78C3A4FB4230ULL;
    std::uint64_t aWandererI = 0xD91C6980C7FF07BDULL;
    std::uint64_t aWandererJ = 0xB72E81A940BD050FULL;
    std::uint64_t aWandererK = 0xAD401CA712995236ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts), aSnowLaneD, 2);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseGConstants), &(mDomainBundleInbuilt.mPhaseGSalts), aSnowLaneD, 6);
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
    TwistExpander_Suhail_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Suhail_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Suhail_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Suhail_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Suhail_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 32 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1788 / 1984 (90.12%)
// Total distance from earlier candidates: 56284
void TwistExpander_Suhail::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 192U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1025U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 205U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2014U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1828U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1491U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 996U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1889U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1368U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1922U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 247U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 213U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1182U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1847U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1028U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1334U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1628U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 832U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 687U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1281U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1726U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 284U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 639U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 295U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1571U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1698U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1363U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1985U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1303U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 708U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 254U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 51U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 573U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1947U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 365U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 942U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1962U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1762U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 691U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 332U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 903U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 572U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1793U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1518U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 629U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 755U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1262U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1195U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 527U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 74U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1737U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1790U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 292U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 831U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1878U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 965U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1888U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1733U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1864U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 214U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 13U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 119U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1249U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 776U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 709U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1037U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1078U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 396U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 677U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1805U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 600U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1348U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 419U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 713U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 61U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1188U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1986U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1014U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 842U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1297U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 16U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 241U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1574U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 699U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1955U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1551U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 797U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 193U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 700U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 829U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1512U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1288U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1013U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 469U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1419U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 561U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 988U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1857U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2046U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1029U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1353U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1124U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 455U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 506U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1362U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 551U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 420U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1407U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 408U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 595U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1659U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 884U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1192U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1522U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 824U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1009U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1378U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1787U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1106U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 625U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1506U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 462U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 412U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1113U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1389U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1783U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1654U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 154U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Suhail::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC491D4ED91A2D25EULL; std::uint64_t aIngress = 0xA63524766A4BB97DULL; std::uint64_t aCarry = 0x9259BFE814DA42FCULL;

    std::uint64_t aWandererA = 0x92B471359FA736F3ULL; std::uint64_t aWandererB = 0xC4542FE5E9A465A1ULL; std::uint64_t aWandererC = 0xDE69EA8A5D606B08ULL; std::uint64_t aWandererD = 0xABE9C6CA9860105AULL;
    std::uint64_t aWandererE = 0x83D44982C674C699ULL; std::uint64_t aWandererF = 0xB66AFD24BDD0EA82ULL; std::uint64_t aWandererG = 0xB505D589B61900FFULL; std::uint64_t aWandererH = 0x80D18B7CF7ABF0C0ULL;
    std::uint64_t aWandererI = 0xC097F4CD34E025D2ULL; std::uint64_t aWandererJ = 0xD302068B08776F0EULL; std::uint64_t aWandererK = 0xF8E09A36ECF51B1EULL;

    // [seed]
        aPrevious = 12490891114789137087U;
        aCarry = 16709482451165613752U;
        aWandererA = 17861608090348954035U;
        aWandererB = 9947280678445498034U;
        aWandererC = 14488530381724173440U;
        aWandererD = 17242756337321523658U;
        aWandererE = 12217661576818054554U;
        aWandererF = 14591809204092791443U;
        aWandererG = 15450475131794930635U;
        aWandererH = 14949031388379079567U;
        aWandererI = 13607047769894462898U;
        aWandererJ = 9454151114967422081U;
        aWandererK = 18115042306190664625U;
    TwistExpander_Suhail_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Suhail_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Suhail_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Suhail_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Suhail_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 32 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 16750; nearest pair: 453 / 674
void TwistExpander_Suhail::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4148U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7040U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3256U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 504U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4613U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5116U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1974U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2936U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7352U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5066U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6857U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6624U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6682U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 877U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 886U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1408U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 658U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 902U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 680U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 464U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1496U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1845U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 697U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1320U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1255U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 957U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1020U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1554U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 588U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 626U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 707U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 118U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1772U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 782U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 692U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 32 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 16743; nearest pair: 448 / 674
void TwistExpander_Suhail::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4141U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3104U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4273U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2904U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6560U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6805U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5209U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 919U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5692U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 872U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5560U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2024U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3702U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2800U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7663U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7910U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1800U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 230U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1528U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 809U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 187U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1987U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1735U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 979U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1261U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1248U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1137U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1540U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 296U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1496U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1212U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 469U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1164U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 927U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1298U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 685U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseASalts = {
    {
        {
            0xAADE5A5F08249D21ULL, 0xE69C27145EBDBE68ULL, 0xEF459B80999AA11AULL, 0xF6224D0363DB10E5ULL, 
            0x3E7359AFD1BC421FULL, 0xE39343E629D42CB5ULL, 0xD899F2BCAE7F8DE2ULL, 0x421518A2B1E3DF7BULL, 
            0x8A063C9E938CFB27ULL, 0x730F858F1BB294B2ULL, 0x465CB8627D127CB6ULL, 0x87AC432DFEF2F0DCULL, 
            0x94E1D1F98AAC32FFULL, 0x226F2AAA4AB5F0CDULL, 0xAEC6C658CC6EA5B3ULL, 0x7BB6D31B506A2F08ULL, 
            0xC11A557B2900DC84ULL, 0xE16A0D880F3A5DEAULL, 0x6B994D397D3D746DULL, 0x759E9528BF620C76ULL, 
            0x533F416995ACD522ULL, 0xD6747E0908C0D8B0ULL, 0xA6A7FD7193427B85ULL, 0x91CE0FF34D278C93ULL, 
            0xA70C15531CCD5C0DULL, 0xC1379975D76020CFULL, 0x9699221A660A91C7ULL, 0x3ECA4B4F682B6653ULL, 
            0x58A6427084910EB6ULL, 0xB8508EBA5DECE62BULL, 0x58EBC2E9B1CDA05EULL, 0x9FAF10F42DE99E5DULL
        },
        {
            0xD0F186A60DBEE99BULL, 0x182C31A960F85109ULL, 0x754E57ACCD0467A4ULL, 0x5DDE7143732D9650ULL, 
            0xC9D64FA4DFAC2597ULL, 0x1058870F637A9C4EULL, 0x2C524832024F518DULL, 0x7F1023E8EB7BF958ULL, 
            0xC15FF87ED7CE542CULL, 0xE74417D6CC2F58AEULL, 0xF595B523A21687F9ULL, 0x8C3BFF3711E7140EULL, 
            0x1E089CEA39F05D68ULL, 0xD08A5968147B2FFFULL, 0x0C03ED42A75F6037ULL, 0x84041EC20C5D14B1ULL, 
            0x7D953833C7BFD5A9ULL, 0x88266E8852929955ULL, 0x05DBC2FE39D3AB53ULL, 0xCB22B906AA7331BDULL, 
            0x46C0B0ABD8C836F4ULL, 0x99B040D7A3FE930DULL, 0x1B34E6091702B29AULL, 0x558ECAB1629925D0ULL, 
            0x73934E95BACDA62BULL, 0xE86B24A81030B493ULL, 0xB96066EFB1D3E04AULL, 0x399E3039461A6086ULL, 
            0x6C138B567D28F604ULL, 0x64EA7E773CCF42EBULL, 0x7070715AC3F16B0DULL, 0xDF185CDB47A12F69ULL
        },
        {
            0xF6E07BAEC9C5DA58ULL, 0x0CA4E435659C3268ULL, 0x35B0E6328A7197C0ULL, 0x1D5A88640058B821ULL, 
            0x3751BC81C142E795ULL, 0x16D355E9D68E98E6ULL, 0xE5845A4246013F6EULL, 0xEA61763B43540873ULL, 
            0x035D37437528457EULL, 0xC3B90113A2D507DDULL, 0x972D7AEF210E6418ULL, 0xC2430BF296F8FC55ULL, 
            0xA21A593BD89A79FAULL, 0x2509B5C7F0C10230ULL, 0x19F01587A23E1B4CULL, 0xCDA2E875EA2A0E68ULL, 
            0x7662DE12B89BC60DULL, 0x84A6E17F7CAB706DULL, 0x86B177E0C0B86834ULL, 0xC74D32806F7E2A23ULL, 
            0xCF065489FF2470E4ULL, 0xD5CE515CDEA22DA2ULL, 0xA38622257B2DDDA9ULL, 0xA2A3541355B2FA5EULL, 
            0x8FEDC08C54D7B025ULL, 0x93069045AD07D68DULL, 0x9C95A0B5C13D1330ULL, 0xCC8154949E0E1DF9ULL, 
            0x8F7BACAB3DCD5B7BULL, 0x214531287618FF35ULL, 0x7D049769015126A5ULL, 0x615F87747C98F05CULL
        },
        {
            0x568FBAD75DEF57D4ULL, 0xEC67C4A5AC261B88ULL, 0x0F80F11A9BFD1805ULL, 0x27FB7E75F39563C4ULL, 
            0x5EE8852355EB0999ULL, 0xDE580517CD68731BULL, 0x2F269D4A48A0A62CULL, 0x5D0BAEC938E80414ULL, 
            0x0B0E1638C9686440ULL, 0xC24BBE3979422782ULL, 0xD4E8C16AEDF615D3ULL, 0x8E57BFC17680CEEEULL, 
            0x7DC4919034C95C38ULL, 0xC862D879E0A885EBULL, 0x590C576BA87746BAULL, 0xD12E9909DB823556ULL, 
            0xE4CC4CF77B66D429ULL, 0xA1FC8B796EF455E8ULL, 0x1725ED30FCF79574ULL, 0xF6BFFC36DB16764FULL, 
            0xA9FFBBB92128F35EULL, 0x68388851E41A1419ULL, 0x0CCCFC524BD83702ULL, 0x9C9BC52C2468EB0FULL, 
            0xC6BD52A0DFB54267ULL, 0xCCADBC3B2691C741ULL, 0x36E5CA14BAD228B6ULL, 0x5B3CC24A7C632DA9ULL, 
            0xEC9A8021F579F388ULL, 0x4E46A03E90CA8BC9ULL, 0xD4733434813F46BBULL, 0x72115EA90BA6D514ULL
        },
        {
            0x3CBEEB78D5008997ULL, 0xC4A0C6004DF1C2E9ULL, 0x1952BAD8794BC64AULL, 0x0A05E755BBBCF45DULL, 
            0xAF6822D341D446C7ULL, 0x5B64735BA48317B0ULL, 0xED0E67A837FC3977ULL, 0xF018AA3EA2960DE5ULL, 
            0x6FEEC9E76EA111FDULL, 0x96F1AA8E2ED9DAD0ULL, 0x347CE59F13ACED13ULL, 0x09245D55B9F39813ULL, 
            0xE804AD6770C9A078ULL, 0x2AD8B575D8E2BEDBULL, 0xA79AB253EF982646ULL, 0x9B2DE261487721A8ULL, 
            0x207E65949D27C140ULL, 0x2C90298D54A19834ULL, 0xE66FC1B39A72289DULL, 0x7A236F8ED618856FULL, 
            0x640946E1585E3E46ULL, 0xA24D36CBA3F38906ULL, 0xFB23DEDFCC753BCFULL, 0x6B55E7DA01A42BCEULL, 
            0x9997429BF5E2222EULL, 0x31F34761F59AF4EDULL, 0x1A34954A3BB86606ULL, 0xC68841914B2D49EFULL, 
            0x6E7E5EE5CC2F4BC4ULL, 0xE739BE096993A843ULL, 0xFCBDC2A09B264494ULL, 0x411EF62871E5F491ULL
        },
        {
            0xD7D0C21A222C0269ULL, 0x134D7D753D514BF2ULL, 0xEA4E65C614E24EBAULL, 0x33ABF09E53286DB0ULL, 
            0x186D5751171F072BULL, 0xC99340CCE8E202E3ULL, 0x4E4D5CC9864A2308ULL, 0xAF062FBE90F3E812ULL, 
            0xBBC4D14ED5BEFD35ULL, 0x5DF0E778156E259AULL, 0x38BCB25920915862ULL, 0x4BA2F601310DED0BULL, 
            0x77F40E41D2D20258ULL, 0x5E093AFB93659821ULL, 0xCA364B579DC9F984ULL, 0x8AF00E7D26A01A53ULL, 
            0x5228AEC5087C749EULL, 0x2879A6ADE422708EULL, 0xAF197F26D88E2187ULL, 0xF6291CC615B225FDULL, 
            0xA10D70E3A5B081FDULL, 0x7332CECBDD1B43B0ULL, 0x8EB4035B3DA2AB43ULL, 0x9EBF7E5BB4B5B4D0ULL, 
            0x215B8E1E19DB9F2CULL, 0x8C14468C71FF44F1ULL, 0x58E19E06E751D41CULL, 0x72F9942526A00F8AULL, 
            0x9A249AD3E150FB47ULL, 0xF19DFE80E7889FD2ULL, 0x5008088499B7C53CULL, 0x1E5F2C71D27F35D8ULL
        }
    },
    {
        {
            0xF46CBA5A12AC78A2ULL, 0xE286CAA018EB7256ULL, 0x5A5F91CCA851AE93ULL, 0xBB10C33A4E51A581ULL, 
            0xFA54EBF25A9DD8A5ULL, 0x76671254808E3145ULL, 0xEC98E1BF9DC12039ULL, 0x7AB8FAABDDB5EE91ULL, 
            0x0173449676B29DC3ULL, 0x60BC4ADE7430C36AULL, 0xC9F8BB2C683274E7ULL, 0x07C62CD6F2303085ULL, 
            0xCD73427D7BDABF78ULL, 0xED5B0F73C37C5512ULL, 0x74B080605534718FULL, 0x69B84F2BB3408A88ULL, 
            0xF1E7EEC94EE917CCULL, 0x0C66B43EEC3AA2D9ULL, 0x3856430176C5F286ULL, 0x2D7E7DDAD4B25B8BULL, 
            0xBAC79A136FBEC2FAULL, 0x84AB37C65A72B40EULL, 0x0ABDAEDB4E5E53D7ULL, 0x6C9F7DAF7173EEF9ULL, 
            0xD32235181BE27682ULL, 0xAC8BC0C5B1A3D52BULL, 0xE4626D0B69A5FB42ULL, 0x3E9D75037CA114D9ULL, 
            0x0CFBA7F933B553B3ULL, 0x7D3CDA39E053286DULL, 0xC09DBB290C5522F1ULL, 0x11EE5A0E96CD4617ULL
        },
        {
            0x8CF89D1654B68C17ULL, 0xCB5DFD1B0AE616C0ULL, 0xEBD08E0E7BAA606DULL, 0xEE528617391A9EA9ULL, 
            0xF99FDE1484FCF15EULL, 0x4C68CB3D83D80DA2ULL, 0xD7D53534958AD9F8ULL, 0x20676B0C7B296E46ULL, 
            0xF061600D70E8DE92ULL, 0x48B7FB50CF44AB25ULL, 0x188CF325395B5119ULL, 0x906A2BF401A2263BULL, 
            0x494EFE9A8F64F70CULL, 0xA5890CCB226FDA6CULL, 0xBBF87306A9165452ULL, 0xED18DA196499F6EEULL, 
            0xDAC95976A5E6E7F0ULL, 0x8132C15D30C0BB16ULL, 0x2F25C002E8A7D13DULL, 0x4F52B2389872BABDULL, 
            0xB2E062D2871F5849ULL, 0x5312F4767381E4B3ULL, 0x669FE861E7B36B21ULL, 0xAE514B790E34A4BBULL, 
            0x31D732683F8F304BULL, 0x419FD560D6693C2EULL, 0x0F44DEBAE1C63D87ULL, 0xDD12D3915D456FB7ULL, 
            0x21A13FBB2921620DULL, 0xA6DFEE6939A39375ULL, 0x99C947456DA48856ULL, 0x5AF41403582A9DA5ULL
        },
        {
            0xA04990702B6A1205ULL, 0x651EC2C411C0225EULL, 0x93B6642AB0523D93ULL, 0xE1D81F2093A6A2CDULL, 
            0xC955E847291C81D4ULL, 0x0154793CC694049DULL, 0x193D9642B7BDA327ULL, 0xBA153F4060A051C4ULL, 
            0xA06AB1B0B56B1EC3ULL, 0x5249580333F4FAF9ULL, 0x128A7BB55C2691F4ULL, 0x8C1E80BEB1C798F7ULL, 
            0x6D6A033894369C1EULL, 0x9C099193CD6DB520ULL, 0xBB9FEE2D1D7CDBAFULL, 0x69F747799E4F3947ULL, 
            0x10D70A23BF796F40ULL, 0xD208C7A9CF657E04ULL, 0xC8B44F26A8B2D3DEULL, 0x71D2FA82DA57F3CAULL, 
            0x8FD79CE8004F4C0BULL, 0x94DE2B94F6488A25ULL, 0x1EC5B55692EA1427ULL, 0xB29F4C41481F8783ULL, 
            0x25A8DDA10919DBB2ULL, 0x7B710D797A0A1998ULL, 0x5ACD9A8F323A0B4FULL, 0x34B8B4850C09D8EDULL, 
            0x31C635FCD3B8096CULL, 0x898D9E20803F5924ULL, 0x41EC62812FFCF583ULL, 0x6DE2502CA7B6244DULL
        },
        {
            0xF5574CDC13E1867FULL, 0x3594207FDD592D57ULL, 0xD2E7B8CF6C722F13ULL, 0x3F2A52F2762D904EULL, 
            0x3F0B0A9D02838BF6ULL, 0xE3A4A69E6D92C228ULL, 0x9C795AE5435C75B1ULL, 0x8E77A9BBED58FA94ULL, 
            0xEAE69D4C3D57CABAULL, 0x6FC98E1EA876C74FULL, 0xC75107B16FA6CB38ULL, 0xDC3852A4136637A9ULL, 
            0x06CDD326277965CBULL, 0xE097276CEA28EC4EULL, 0xFB706562A51DE0AFULL, 0x53C8E829864D634EULL, 
            0x2A25510EB7BB8908ULL, 0x7F6947258E40C661ULL, 0x91FFCFBEFB9B091BULL, 0x8F83B09E8BD8768FULL, 
            0xFE0908AE0A0A76DEULL, 0x3AB4B925A87A0028ULL, 0x39541EAFE4B5381EULL, 0xBBB42EE4D1C74DEAULL, 
            0x06A95BEADCE7C8CEULL, 0xA0A0AF427AA07FBFULL, 0xB8C6FCA95CE36690ULL, 0x38D084F23D9EDA81ULL, 
            0x883FE477DA30F58FULL, 0x777FBF94C599A504ULL, 0x736102AE289F6EE1ULL, 0x7B4607A6707E6B2BULL
        },
        {
            0x1C19C8F163B0721DULL, 0x09405F7CCE7953BBULL, 0x4CA2812B57617B0BULL, 0xC3C8E147BDEC89C0ULL, 
            0x66303E74BAE85CC9ULL, 0x213C71B4DA8F32E5ULL, 0xFF6C34975C5B0454ULL, 0x54573857601C1AC5ULL, 
            0xADEB60442F0B67E0ULL, 0x1F5DA292A36225B1ULL, 0x6A36C453DD79FF60ULL, 0xF342344EE7B146D3ULL, 
            0x4CAA45C3BBAB0C3AULL, 0xFF73A6FDB16064EBULL, 0xC9CE5D88C66D7B31ULL, 0x1D5ECC16E8FAE406ULL, 
            0xF6BE91C38AF2CD53ULL, 0xB32B7B79F677D32EULL, 0xFE90D2E16883E0E5ULL, 0xCA40A6A48AAFC643ULL, 
            0xB73A4785F721B3C3ULL, 0x5978F40B5339C10EULL, 0x54257757CFBF5C1CULL, 0xD76DCCCAA182EB50ULL, 
            0x3EA761B2E68B0682ULL, 0xDE79DECB7ECC6C36ULL, 0x5EE6E18763B6D834ULL, 0x62CBC9CC27774A91ULL, 
            0x2AA259581C18BF40ULL, 0x9457D8F29EF1DF4AULL, 0x1A143A0777F45987ULL, 0xA0AFEFC27566D86CULL
        },
        {
            0x3FDA7C146AC82ABBULL, 0x812116FD8F10D498ULL, 0xD73940E883A6ED76ULL, 0xF4F8AAE463044FE2ULL, 
            0x52B721F1A37B06E2ULL, 0x8DBD0A295315294AULL, 0xA4640ED787CD9920ULL, 0x040E40A616F8760CULL, 
            0x6AE16F4BCEE7CB39ULL, 0x8BF60A2E180B3323ULL, 0xCAE3D9B363A550ADULL, 0x2CAD29D1CE58035DULL, 
            0x943FD8F23122AEA1ULL, 0x5092888B4B53E20EULL, 0x3D3BB54A81C5B2E1ULL, 0xAEF772AD4D1D9B5EULL, 
            0x2A3409F4A4B8B315ULL, 0x31DF8632641ED3FEULL, 0x18484A7F72562D5CULL, 0xA4B33A325958C1B6ULL, 
            0xDE908666E62BF17AULL, 0xB8F9BDFB12A9D5A4ULL, 0x599EC5771E8DB9E7ULL, 0x8A1C5CF775EE8B27ULL, 
            0xCA06D3579D329DC0ULL, 0x41A8452828B813F3ULL, 0x05DB95EE6AB9CC8AULL, 0x8C6BEC824C8A743FULL, 
            0x00374CAE9FF865B4ULL, 0x5FD0F25709E37133ULL, 0xD901E986E84AE82DULL, 0xB902F4FA55B6108FULL
        }
    },
    {
        {
            0x0AC5E5C7E355FC1DULL, 0x69D0A798AE2CF22EULL, 0x4128C7C9A126EE87ULL, 0x8A4412641B24A17CULL, 
            0xE585DAFE201B19E5ULL, 0x48709FA8DD56C50AULL, 0x740B027E71021343ULL, 0x61C83FFB66B66610ULL, 
            0x92D154ED7C0131E2ULL, 0xD3DC3ED5D545142CULL, 0x43D88D3B02E4DD7AULL, 0xD7D3B49723D3933CULL, 
            0xF043AFDEDC0906B3ULL, 0x6DAC4F7BB6F6C30BULL, 0x0BE0DFBFA1F91003ULL, 0x43C7CB938CF4DE6CULL, 
            0xE5D49F27B95458B6ULL, 0x9D661320D817B935ULL, 0x5C8F9AE63C395D9EULL, 0x8FCA361D6BEC2889ULL, 
            0xA4DE01BA6DB90196ULL, 0xD58BC8C5CC0D78A5ULL, 0x91B1F64395607567ULL, 0x69888EA6C43974B7ULL, 
            0xCEA39727063DC2CEULL, 0xA8A3A1B31C995CDDULL, 0x54F457B78252BFB9ULL, 0x4080CE14244408F6ULL, 
            0xF6865449C61A2373ULL, 0x49327E1E98008745ULL, 0xB443A2B7929BFB3DULL, 0x05585FAFE0CC8983ULL
        },
        {
            0x451A59B6EF6E5B89ULL, 0x26EE82AF3281C240ULL, 0xA19B9A04E97E81A5ULL, 0xA7D65D7AF31FFC83ULL, 
            0x29F8F72DA15A7EC6ULL, 0x018DA9420D20D951ULL, 0x90C7DF9AB365CCE7ULL, 0xFF00AAE250265AE7ULL, 
            0x0D90574852443311ULL, 0x618539093F1100A0ULL, 0x15097CAA3926EA90ULL, 0xDF189D4A432E4ED3ULL, 
            0x6A0783FC95791EB8ULL, 0x5A22204F1F8421FAULL, 0x01E6B8101CBD7ADBULL, 0x8C5C7E42CD814D6AULL, 
            0xF538FB9CAFD92773ULL, 0xC8EAA5F51FB80F76ULL, 0x2B00051050264309ULL, 0x27FB11B48EA17E4AULL, 
            0x45F51DE532459232ULL, 0x7D240991DBA7E752ULL, 0x3B6D92B495688BF0ULL, 0x12E9E05731E98F2DULL, 
            0x369C4F2F145E3419ULL, 0xEB29286FA55DF1C1ULL, 0x9B21341CC2547592ULL, 0x0CEA67BDCF2B7123ULL, 
            0x393687372EFBC898ULL, 0x4379D4133B4D126EULL, 0x1961F94D6F8B8A12ULL, 0x2056BEE808E4A909ULL
        },
        {
            0x9FE852551DC1FA08ULL, 0xCE4773A0E02D98B5ULL, 0x5F4967C1E6D24B5DULL, 0xB769EFBCF0CCC4B6ULL, 
            0xB39CC424FB2DBD44ULL, 0xC4D45574CB303D52ULL, 0x41F6BC787B3AF416ULL, 0xABA070191297DA6EULL, 
            0x54008A0BF60387BFULL, 0xFFDE949A2EDE480BULL, 0x8C844D38E830C2C6ULL, 0x0747653EDDE73783ULL, 
            0x2DD0919779E81F40ULL, 0x69D2CF60E2C98A23ULL, 0x0B990C8CC3592A93ULL, 0x9B43499AD4FAA655ULL, 
            0x84914A789245BDAEULL, 0x5F7B33D421FAFF6FULL, 0x20D16C84887504CDULL, 0xBAB96AA0888ACC91ULL, 
            0x280EE74F74461B32ULL, 0xA489C312EC581057ULL, 0x224E55B48B2CD813ULL, 0xC1137A4280B56AA5ULL, 
            0x80F88729F66694DEULL, 0x47DDFC15A36D7F25ULL, 0x7C8E4F6D094D84E5ULL, 0x6C0B1209F9741211ULL, 
            0x17B263ECAF13F501ULL, 0x1CA2092BBF42FD66ULL, 0xFDFF4652A66DD06DULL, 0xA90E6A3D4243984AULL
        },
        {
            0x03EA0D42314D43FCULL, 0x047896AD508DC169ULL, 0x700134BB2585B0E1ULL, 0x491A2030C677CF6AULL, 
            0x85B77CAFE4974541ULL, 0x7333F296EA5D78AEULL, 0x5A12199E8395CF36ULL, 0x94E5773BF3C51DBDULL, 
            0x5836BFFD1B9E26DDULL, 0xBD7F099A1E86DFEDULL, 0xB1AFB43F65595239ULL, 0xF289D17BF2729C09ULL, 
            0x369152B6118BFB95ULL, 0x5FBD495ED5AECF3CULL, 0x6E026F61A8413526ULL, 0x290556F5DFAFE91BULL, 
            0x7400E31B9DA9EBE8ULL, 0x23C54490A3704FC0ULL, 0x2A98C7A3C9630A52ULL, 0x5541914ED90F5946ULL, 
            0x2543F9DD3435765DULL, 0x23CE546317B0BECDULL, 0x1FC05DACACAFDCB9ULL, 0xB6EA437E81F860ACULL, 
            0x50508D6E61F3F6A7ULL, 0xA105E7FD16776CFEULL, 0xD02B517034EC9500ULL, 0x18CAC96C0BB7D6B3ULL, 
            0x6C6BC0B727BFA559ULL, 0xE0918603F462BAF2ULL, 0xBD9806E14D40A4FCULL, 0xFE14458DCFB60D54ULL
        },
        {
            0x212FA79B9F9A428EULL, 0xB59F129A12262DF2ULL, 0xA817B621F286F8FEULL, 0x0678C643E4675B7CULL, 
            0x1B0ADE26D9D13BFEULL, 0x27D3FFB8759E2E40ULL, 0x164C38F1FE9071A1ULL, 0x3F4C00C0AB521367ULL, 
            0x311679B5B9DFF7CEULL, 0x75056E0E166E9624ULL, 0x1089B94871AD3D12ULL, 0x7FE0FC03E09DE7E3ULL, 
            0x4F3EBC806881CF2AULL, 0xE9163D9CA7A34785ULL, 0xD1F73ADF3B46C35DULL, 0x095ED0AFF8537BBFULL, 
            0x10D17F8655BABA89ULL, 0x3B1A41A3D4DCA367ULL, 0xD459FE209E155AB5ULL, 0x10D5EA6D29E364D4ULL, 
            0x1EF236A806BA4F16ULL, 0xABBD06A94FAF876AULL, 0xB44BC005B2D8F59CULL, 0x1C36500006D1BE85ULL, 
            0x23FC5E02E6C9984DULL, 0xEC461EF011AE443EULL, 0xFA05FAD1E4664524ULL, 0xAC4FCC140331FD49ULL, 
            0xD158BECE6AD12C31ULL, 0xBC6135DF53295D49ULL, 0x611A32BC6F4623E3ULL, 0x74D730E7659C9226ULL
        },
        {
            0x9386799A638B8159ULL, 0xDE2632851D26E413ULL, 0x6A829D2E9752F978ULL, 0xBEE297F484B144EDULL, 
            0x262831FD2A39CB43ULL, 0x031CB4D15397DEF8ULL, 0xF2A9BC52390BC2D1ULL, 0x44D4E7A3875281E3ULL, 
            0x2AD69D5900F23E1DULL, 0xFD41FD4D6DBCCA5DULL, 0x27CF98D8105434F2ULL, 0x882F8F4FE5D403A4ULL, 
            0x4C35EBCD99D5D681ULL, 0x4FE7FAB3F97F0593ULL, 0xEAC436B243D3BBAFULL, 0xA3E28E354B34BEB1ULL, 
            0xE55E3761AE533FB7ULL, 0x3871AECB9C2AFC33ULL, 0xBC9576DBD3E40D1AULL, 0xC67E9B8E58CEF2D7ULL, 
            0x97DFD0BCBCE19116ULL, 0xA67228303DDEF2DBULL, 0x7E4C994793B0A1ACULL, 0x5A653C29DC9424F9ULL, 
            0x90B09789BEFA746DULL, 0x3F0D2D0453152A57ULL, 0x5BB762BAC30E96DCULL, 0xB66052AD40DAC853ULL, 
            0xE9615BBAD5D44713ULL, 0x06A4701AAEF0375BULL, 0x95FA46A7F49105D0ULL, 0x0108F1C8A1EAC875ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseAConstants = {
    0x0D60E92FF82D4F75ULL,
    0x948E6DA125E8FD28ULL,
    0xC33D52EA99949C80ULL,
    0x0D60E92FF82D4F75ULL,
    0x948E6DA125E8FD28ULL,
    0xC33D52EA99949C80ULL,
    0x3BB01FC6140E9D26ULL,
    0x629AD8F24D9D1C37ULL,
    0x5F,
    0x70,
    0x7C,
    0xFF,
    0xDE,
    0x5D,
    0x57,
    0x44
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseBSalts = {
    {
        {
            0xC6BF5265C2F29537ULL, 0x23C6078F56908F3CULL, 0xD8198B25EC7227F4ULL, 0x9591D30E5687D831ULL, 
            0x83062721F5799F6EULL, 0xFA80BE9750108D54ULL, 0xF8F8E337FA401E8BULL, 0x82261D1A08721871ULL, 
            0xAC5ED72D181E5690ULL, 0xEE74B72A8B939FCDULL, 0x30B13BCC3F66BF46ULL, 0xB05FFBA8A289CEACULL, 
            0x168DFFA8044E6BD5ULL, 0x15D16368606C0D8BULL, 0x03DEBD7070B24730ULL, 0xECB448271F0A0B01ULL, 
            0x59D78A2C4D7DD8F0ULL, 0xE4C38F253F7E65C7ULL, 0xB5657D7AEA59F1D9ULL, 0x9C697342846E8A6FULL, 
            0x74345DD883A23B3DULL, 0x7CCB42CF52DF6691ULL, 0xE2D18FFBAB6A66C5ULL, 0xD7554F13FC589876ULL, 
            0x5BB11A1835302136ULL, 0xAA3A7CB9E2A78AFDULL, 0x9B546205EBA64B5BULL, 0xF77E7610C432AA89ULL, 
            0x9F75E80473AACB66ULL, 0x79AB2D3FF5CE2148ULL, 0x54E875065FCC3864ULL, 0x7CDED58A3B55FF40ULL
        },
        {
            0x46189354255EBFFCULL, 0xCB13AC03C50E150BULL, 0x87E632B111EA1CBFULL, 0xB2B07472092F568FULL, 
            0xA40A0461D102913BULL, 0x5F490836B21E8A63ULL, 0x6176149BE1662C8DULL, 0xCA824C4D1CD9543EULL, 
            0x8263515062BFC81DULL, 0x50481410341D3361ULL, 0xAE045D671205E46EULL, 0xC216F9C4F45D49B6ULL, 
            0xADA906A14E39ACE6ULL, 0xD8740A00695F1650ULL, 0x64434BD57B425AB4ULL, 0x603193EA8511A261ULL, 
            0xC0F8DEF0839057C4ULL, 0xACB40993476F9CD7ULL, 0x372696FA7C47AE00ULL, 0xA3D6AEC8C3B34382ULL, 
            0x7A740B701961C1F9ULL, 0x0D07C098C5AE1059ULL, 0x8C86CB88D3D6853BULL, 0x6EFCB580EE649595ULL, 
            0xE759C6B210FD94EFULL, 0x1CC8288D9189EA1FULL, 0x3CFD8E2F65EC1A2FULL, 0x776ABAE56EA4F4AAULL, 
            0xCD3EE6328B4DBB4DULL, 0xA76DAB639D6A2A93ULL, 0x905EDCF17C6EAB1DULL, 0x9FE297F8EBF91A42ULL
        },
        {
            0xD69B37CEE6A09D64ULL, 0xB7977C2A8D1051DCULL, 0x0D45840DC0993CD2ULL, 0xC3E2C568B7A17741ULL, 
            0xB0D9FD3FA45421B1ULL, 0xBFB0E8EA60D8C44CULL, 0xFABB125746C3C938ULL, 0x211A445F5B9FA9A8ULL, 
            0x0705DA961486C95FULL, 0xAFB5DF7899A6FE59ULL, 0x64F04BF8FCDE3E3CULL, 0x5371358FDE178E50ULL, 
            0xC8903369B9145506ULL, 0xFFA843596D36C8CFULL, 0xBEAF58908CC1C924ULL, 0x2087B7B288E25275ULL, 
            0x790B159242046876ULL, 0x6ABD3DBBD9A0C3E3ULL, 0x8610D3DEDCF824B6ULL, 0x35A26BA8849A87B2ULL, 
            0xC0A49DD7D71B82C8ULL, 0xB334A6A0FF8C5CB0ULL, 0x6EE8446DB9CA3F0BULL, 0x6C78905A1A24E2D9ULL, 
            0xE21AA7DAB66148AAULL, 0x973DD07C1F0AB961ULL, 0x4969FBA1C8CC21B0ULL, 0x51B0623D021A54BDULL, 
            0x25101CBB1F65A2E6ULL, 0x8033E4A626D79C53ULL, 0xDD118BA009CC54DAULL, 0xD24A8C971A858497ULL
        },
        {
            0x2FF32441ED349C66ULL, 0x6E6C840326E11F23ULL, 0xC19780A3AD850F10ULL, 0xD4957558BCF428DBULL, 
            0xB85B756F68A57D35ULL, 0x198370D8C6848BCCULL, 0x23A29A2533CD45E7ULL, 0xE967DAE2D35D91B6ULL, 
            0x637F355093EB7E71ULL, 0xB873E27947B83106ULL, 0x833E06AE580ADC9DULL, 0xC0E48BBE6F92D7B2ULL, 
            0xE154F72F16256E34ULL, 0x75D6E5B2391E632AULL, 0xFD8ECB72C7B84053ULL, 0xC499CCC5E8D342B9ULL, 
            0xAE211CBDAF66501AULL, 0x8C5B9554922919ECULL, 0x483D6DDD590D4E42ULL, 0xA7CDF6328850AA53ULL, 
            0x9F108E0CA188B532ULL, 0x9949BA714D58C70AULL, 0xCC3ACD94696DBFADULL, 0xAA76C10DC0041D20ULL, 
            0xA3EFB1CA142CC2FFULL, 0xF5BAA22B19F0425DULL, 0xB861D05320F097C5ULL, 0xD673338297239816ULL, 
            0xE97F8D3808DE3A31ULL, 0x35123CB83520365AULL, 0x7D3738A38033E8C8ULL, 0xC712A9196530B580ULL
        },
        {
            0x8934D969B97D7D24ULL, 0x16C8155E52C441B5ULL, 0x724335D416762A29ULL, 0xBF9FFDC7B5D18C7AULL, 
            0x319FAF08839C85D0ULL, 0xB94177B057BBB40BULL, 0x89874A659C2BD0E2ULL, 0x9455F150C097BD86ULL, 
            0x314A30F1643431E4ULL, 0xF1DB60D67BE79966ULL, 0x751EC7EA397C1EA0ULL, 0x95136F6BAEE516A0ULL, 
            0x61DD87606252B55CULL, 0xADCC770A1D2D8C1AULL, 0xE2DCB48646D93319ULL, 0x59BCEA11520D57E0ULL, 
            0x5B53F6B7DC7FBA69ULL, 0x232230FD769F4D7CULL, 0xCA0E36FB040E784DULL, 0x7785BF3859103479ULL, 
            0x4591377B313642F0ULL, 0x58ECA3DAE9835F38ULL, 0xE9C860233ACCB829ULL, 0xDBD80440AE3D39E8ULL, 
            0x215A853E0AAAF837ULL, 0x45939D7D18F49F90ULL, 0x543EDB1B26E38991ULL, 0x524F609009E36F96ULL, 
            0xFE57C0C101915E7CULL, 0x28CF5E317AF88FF4ULL, 0x9EECAAF5DDFA16E7ULL, 0xCAA3F7EBB1BF28B3ULL
        },
        {
            0xE246FF9A3E28A2F0ULL, 0x7EEBD8E8F7C3DCEEULL, 0x09EF289C2F1E1F76ULL, 0x9101EB737F69A818ULL, 
            0x203309C1D4D85281ULL, 0xE83706465EFF8280ULL, 0xB8C9322B5C167AF8ULL, 0x0B57A1FF4B58692CULL, 
            0x9ABF160A185752C9ULL, 0x51A5A6F1387EA5D3ULL, 0xB64DED828E14AF60ULL, 0x46ECD21292D59F07ULL, 
            0xC4E73A7EE47C21BEULL, 0x3815A8CA049C2008ULL, 0xB8AEE82BDA97FAD8ULL, 0x46101FD9C1F92B18ULL, 
            0x479DBA2B82C0D126ULL, 0xB4AD1675FB147412ULL, 0x6C7702C312E3A130ULL, 0x8BD340418B14CDF9ULL, 
            0x131DA91FE923B9FFULL, 0xD4BD9F47FF7A23DAULL, 0x8EF837A23D7E3D2AULL, 0x71CF2A403B566257ULL, 
            0x4CA1B52CDC53B61AULL, 0xE410E81278FA4540ULL, 0xF0C8ABC0729A6B49ULL, 0x5D123F6EDB4FE7EEULL, 
            0x52B12A787D6656B4ULL, 0xD1D75946CDD97016ULL, 0x9486B21BF2EB6AC3ULL, 0x2A425D073AD8EA47ULL
        }
    },
    {
        {
            0x7C6EB96004FB3486ULL, 0x7360842FB28C58B4ULL, 0x363AEEF875428A4AULL, 0x285B6377D113B1B9ULL, 
            0xFB0CF3D231AD2F5DULL, 0xBDE12BF122812ED8ULL, 0x9DF7B3E8EF4576F6ULL, 0x899794DD35922BFBULL, 
            0x1DA60DC863C2939EULL, 0x64FDE4B45C7A85D1ULL, 0x296BBE3C43487B3DULL, 0xB72894F5405AF8FBULL, 
            0x2E918D0E748128E3ULL, 0x0936DAE408C41756ULL, 0x0A40971669DC0EC7ULL, 0x7FB456E04E832CD3ULL, 
            0xBEAB3930A2A0CE76ULL, 0x2D4A4258F2097950ULL, 0x86F003F05FD47242ULL, 0xA8CA8036A9035B9FULL, 
            0xB5BC217430F2706FULL, 0xC9E0406BFAA64DFAULL, 0x65364D941E3C10CEULL, 0x54D82B2C1E56B19AULL, 
            0x76CC1B7C12F733DCULL, 0x5F29A464F9AE0AC6ULL, 0x851F1B7F0244BBE3ULL, 0x4F746959B1B1C313ULL, 
            0x2DFA5689A8E5A3E6ULL, 0x20CD2EB5844579A2ULL, 0xC56EF05751065B83ULL, 0xB174CE137139942DULL
        },
        {
            0x6F68A450885A8249ULL, 0xC231BD572D870DEAULL, 0x48CEA65196170EA1ULL, 0x95E970D0A0094FBBULL, 
            0x0FB653223CBC3505ULL, 0x3A648C56D27BD23BULL, 0xFE81367B864269D0ULL, 0xE6FAAE917AF78837ULL, 
            0x6D82E7F8E6EBD736ULL, 0xFFDDF9E4694212FEULL, 0x2B85F04860FA0286ULL, 0x8BE6731D36BD5ED5ULL, 
            0x136C1445977C2248ULL, 0x5AA7F6E7A97867BAULL, 0xBB10306BD34463D5ULL, 0xAE50D0A0ED081523ULL, 
            0xA91BF393B8EC15B1ULL, 0x3DDCE08B67066DD9ULL, 0x050FD9333148C879ULL, 0x639F77282B09F779ULL, 
            0x5C1CEAFACFD27D6BULL, 0x1A4E1BCFF01CD134ULL, 0x132A94393BAA4B13ULL, 0x227DF640D98AD80CULL, 
            0x26B9D370144EC741ULL, 0xB3602C80DE4FF921ULL, 0x38B66895B85B449CULL, 0x73251BDB359B7C29ULL, 
            0x68411498099B4672ULL, 0xED337DF72E49D9D3ULL, 0x5D98CF4F3592E7BEULL, 0xC4FA0872063963A6ULL
        },
        {
            0x26D9AB5AB42656ECULL, 0x933E7B9D448CA053ULL, 0x37A16C41051D6040ULL, 0x6F6B854B774F32CCULL, 
            0xFA78F5E4D5507176ULL, 0xEA1E6C709BE1BF52ULL, 0x9A07019D22A18FDBULL, 0x9A279A9D0DD8A1E1ULL, 
            0x4620B77A9114D152ULL, 0x9AA48BF89B45F2E6ULL, 0xF4EF38E6EA7691E6ULL, 0x36590C08E3E1EB12ULL, 
            0xA0CD252C92A6A83CULL, 0x71B6A88EB0BA2B32ULL, 0x3F8048C73A394CD7ULL, 0xCC0666E4C78E3170ULL, 
            0x7FECAB1300650773ULL, 0x33CC4B099DA7613EULL, 0x3D88AC9101FF7473ULL, 0x259823E53FCF3E78ULL, 
            0x5202054CE3A1C1DBULL, 0x58801E506E1B6153ULL, 0x50B667741E7BED9BULL, 0x30485513B10B544AULL, 
            0xF9C88331B65BA04DULL, 0xFC8ED1573938EC54ULL, 0x18CB09A66C77E8E5ULL, 0x6B18A7898D2CCD68ULL, 
            0x2218A0584EDF4BA8ULL, 0x096E423FBC27E97CULL, 0x8B8CE6839AF3BD40ULL, 0xA5AD9F57EA5F7301ULL
        },
        {
            0xEAA11CE0E6387BB1ULL, 0xEADC69AFB7F63A77ULL, 0xC107B7A69DBD050DULL, 0xA9192C8A0EE80B74ULL, 
            0xFDB416FF1FF256C3ULL, 0x794B7C76AA043931ULL, 0x0AB34DF4C27211B7ULL, 0x5600001AFF7616C0ULL, 
            0xC221BBBAC6514978ULL, 0xAA4E38349AB87622ULL, 0x2F73B4C0224616D0ULL, 0xA4AC31C390724B17ULL, 
            0xEB7E7F9BF1D0D448ULL, 0xE310DB9613ADDFDEULL, 0x9E042225D0D8BD2DULL, 0x7047650DE3289320ULL, 
            0xA61313CE4E3E408AULL, 0x4A1D691E10860477ULL, 0xC4941482CE2B7980ULL, 0xA95F2577752BE1A8ULL, 
            0x561DB6BF3E1FE076ULL, 0x46EC905CF98FA77DULL, 0x7757F47E691D3273ULL, 0x86F282544987CE1EULL, 
            0xB439F0A9AF07BF93ULL, 0x15C646E9D692A9E6ULL, 0xA1342A2127148786ULL, 0x6564FBB92BAEC4FAULL, 
            0x3E6DA6899816B996ULL, 0xC52BB28E59BAC8C7ULL, 0x51ADB31EC5602FB5ULL, 0x9F2391DE389E579DULL
        },
        {
            0xE63905C12508D44BULL, 0x0C24AF03DDA9C0DEULL, 0x88DA68B7DDE59236ULL, 0x6384F63757854986ULL, 
            0x06E754074A6BCCA4ULL, 0x27FA569DF48450F3ULL, 0x0CACAA7F76502A5DULL, 0xACD15A28B9E13CD1ULL, 
            0xD8F360B946766FE7ULL, 0x4ED34037BE0B4FC4ULL, 0x08ECF7AF4A4BC5C7ULL, 0x26C21529BD2F0923ULL, 
            0x5A31E4CF574FB643ULL, 0x612FE425528625DCULL, 0x6258A6498E69D422ULL, 0x4D4CE5C2EFAE85E0ULL, 
            0x5A258B602FB6F899ULL, 0x1DBCF4C879CB4C31ULL, 0x9760AC1CAAFD3693ULL, 0xE9EE7FCB6402AA1DULL, 
            0xCD17DBBE551424F2ULL, 0x0E91F6A4626FD302ULL, 0x98D9F46E4FB472E8ULL, 0x55AE33D430E267CAULL, 
            0x28659EBB6394A6C4ULL, 0x73974E93E525D586ULL, 0x7C0C4AA8A85615AFULL, 0x81B73448C04E8C24ULL, 
            0x2E6FC329284FEBE4ULL, 0xA72F2F15394944E6ULL, 0x9C13D0EA0EAFB39DULL, 0x3DA514F02243D133ULL
        },
        {
            0xCF1F14103E40D020ULL, 0xC02D57BDE47167F7ULL, 0x6A3406B316CF87D2ULL, 0xE4E4F7D33777DC34ULL, 
            0x79D31EF6B2864F03ULL, 0x51D886B2319B96F2ULL, 0xAEAB449F8FB7728BULL, 0x93F58815CE83459AULL, 
            0x56331C9482679B97ULL, 0xA7A1093D58D69D24ULL, 0xE8FD9AD2F7ED1C5BULL, 0x1014DE2144F05728ULL, 
            0xABD7A76DB6835B8DULL, 0x34B446E5A299DFD9ULL, 0x464E91C81D6C4180ULL, 0xF0D6058A8BA70DACULL, 
            0xD127BF7012CB79A3ULL, 0x6F13D203AE26C88FULL, 0xE8E09907B9E50466ULL, 0x434AE3573C8995F6ULL, 
            0x78BDB3508EB5D16FULL, 0xE41A063777AED7FBULL, 0xF545DFACE7D457A2ULL, 0x33ED788296C0AB03ULL, 
            0x8675D2C9A3F8EA04ULL, 0xD9E618B5787A6346ULL, 0x4AD8A433A679BB5BULL, 0xB6C38AD08F14EF3BULL, 
            0x5AB7C7101949D6D4ULL, 0x5D986F584553DDD5ULL, 0x0099482C5E642959ULL, 0x60717B97AF206D4AULL
        }
    },
    {
        {
            0xEACE9F0ECE4B7D80ULL, 0xA2F9097982B3FD1FULL, 0x4C496FCA548349DCULL, 0xF5E7BB7BCBC57722ULL, 
            0xDA538554BE9BB903ULL, 0x2F31C031FEB6395CULL, 0x3E6F511643649664ULL, 0x351567ED3681CE6CULL, 
            0xF2BD517AD5AC8BBEULL, 0xC5EC216C59E7FF5EULL, 0xE27E1072874D24CFULL, 0x685E4F30540BD9E7ULL, 
            0x29A288035B7D331DULL, 0x97156851BF3CEEF0ULL, 0x30E28737B0305066ULL, 0xC97E3BF7B4965D89ULL, 
            0x987D07A90F92F774ULL, 0x8A6F4AC84BF07B74ULL, 0x6ADC028E7E0740C3ULL, 0x54D60E917EAA3599ULL, 
            0xE320C08FC3F5FD35ULL, 0xF331D555DCF1BFFFULL, 0xE68945707AD37FAFULL, 0xAE3EFB44FE84925FULL, 
            0x6040DA4E3FBDCABDULL, 0x7A7414175E5A922BULL, 0x4708A1805F87F0C2ULL, 0x4F0ADFD6746DD4EDULL, 
            0x46964FC88093A4A6ULL, 0x243590CA92340166ULL, 0xFF7372ED3297F851ULL, 0x9C4CF5D912D328FBULL
        },
        {
            0x48B81875981D4B97ULL, 0xF7817532692F5E49ULL, 0x0EDC5D32F60ED5BCULL, 0x85D3E61E647D52DEULL, 
            0x2912C7291A11DDF2ULL, 0x06E3BB51E0E7B55AULL, 0x2E901140A8AD4E52ULL, 0x14442D67A82C2857ULL, 
            0x20905A83FFFC97B7ULL, 0x2C80417D5C5A302EULL, 0xA7EE94320F2BFB6BULL, 0x874B5037A2FB5A4DULL, 
            0x10558A48F8AEB2E4ULL, 0x8A9115034151024EULL, 0x64B3C9411BDC0E9CULL, 0x335380A9C9C5799DULL, 
            0x36BEF04B9C47FEF0ULL, 0xB76E696F8F521CF5ULL, 0x6BFBBAD3BD6BE796ULL, 0xAFB4A1B9EF90FCAFULL, 
            0xE4A8A61E8E5F5C97ULL, 0xB97EC77DB19E646FULL, 0x30353513CDCB1280ULL, 0xF30E853FA4531BDCULL, 
            0xBAF879E84D30C0A2ULL, 0x349EE9C7F02E499BULL, 0x773768E7F6B16CE6ULL, 0x4FAD52006AAC2373ULL, 
            0x7A599A90700785C4ULL, 0xE630A7E9E67445AAULL, 0x4BE3BEBD4FDB1174ULL, 0x280C4A2E564F94E6ULL
        },
        {
            0xA338B7541C2DEAA8ULL, 0x62E89F826D06BD03ULL, 0x14AA4FC3E0B9C728ULL, 0xFCA90680EF65928CULL, 
            0x19EDF2E94A6609DFULL, 0x6C23ED1C89C0A196ULL, 0xA239C6F5FE185B99ULL, 0x607C5C19FE559EA3ULL, 
            0x702024AE4D895C3CULL, 0xBA0E0CF789B2E24BULL, 0x643F807AAA577158ULL, 0x157C77AF228C8A18ULL, 
            0xE4402003BA487C2CULL, 0xA9A81522D2EED345ULL, 0x54709B255F70562FULL, 0x9DF38404D7EC2047ULL, 
            0xD72088492FEB2561ULL, 0x8000C6FB3576375FULL, 0x26488392E58BBE2AULL, 0x96B951A3E9CCD166ULL, 
            0x8AAEB68752AFF912ULL, 0x8AA6091543364D1DULL, 0x69FB79B28431E4FCULL, 0x4CDB3B97B0B6E90BULL, 
            0xC98536B08E21200FULL, 0xD83EE2611087C9D4ULL, 0xE9CF28B7BA571483ULL, 0x556A1A26E5737719ULL, 
            0xDCBA3728FEAE0738ULL, 0x642384F9A80969EBULL, 0xC5F7F6D14925478FULL, 0x1DCA0238EE3BF08EULL
        },
        {
            0x73984F4C074FD1D1ULL, 0xB2D6D269543E8055ULL, 0xF1AA6A5A22D82653ULL, 0xA74EF2B76291B654ULL, 
            0xCEB7D1C95924253EULL, 0xAF8021543D69FE70ULL, 0xE6566917FF27DDD1ULL, 0x5E4D2333E077AF3DULL, 
            0xC536C81D856F4521ULL, 0x515265DCF951B74DULL, 0x1F6C131ACF64AD8CULL, 0xBBE648875310C8C3ULL, 
            0xD4981FF4AA0C8079ULL, 0xB63DCBC6559A68DFULL, 0x61A53B245B724530ULL, 0x54F0DB1EF576C9E0ULL, 
            0xD4F7285882C821ECULL, 0x2843F9187BDFF919ULL, 0x4EE49B6E057B095EULL, 0x8F2594CE334325E2ULL, 
            0xB046ED8C524776AEULL, 0x88AD26FA59032334ULL, 0x2A3362BA37CC5508ULL, 0xF346D230CB95690BULL, 
            0x435FA6E263F80C4CULL, 0x1FFF1EDFBD57E572ULL, 0xBB51283AEB5F7BC1ULL, 0x0A80A4B368A72543ULL, 
            0xD1BF4246EB8D204FULL, 0x351C6D410546DDA4ULL, 0x33F9AC80721391F9ULL, 0xC65278DE6AA1B42AULL
        },
        {
            0x66DA6703F7303BD4ULL, 0xB9EEC5727AA3006CULL, 0xBEEAA8953CCAFBA4ULL, 0xE6533CAB550BC45AULL, 
            0xFB60A3EAB4165BA6ULL, 0x54434224D60AAC3BULL, 0x8FB3389F3E5E8058ULL, 0x4EAB58CE0E097257ULL, 
            0x6D7E2D7130F29BB4ULL, 0x28710D4006E2261DULL, 0xD4B33F8B75B122ACULL, 0x7771580200930079ULL, 
            0x1F0A82F2944F4FCEULL, 0xB1C21B89CB26E62FULL, 0x21C8EA9207303FC5ULL, 0xEF8DB7E5426AEC20ULL, 
            0xC49492F63DC5E9ADULL, 0x4E1527A8CCAA7013ULL, 0x942E317A4B6FE19CULL, 0xF1676BF26AF1F8EBULL, 
            0xD109040454165904ULL, 0x6E878C9E201EF30EULL, 0xF4B50909C4E82BF8ULL, 0x577DC160E99DB497ULL, 
            0xD2234232480854EEULL, 0x273C76A80675EE9FULL, 0x1AD10396CC66B8B1ULL, 0xE6FD0552EA283D50ULL, 
            0xE547EE6258E2E7C2ULL, 0x95E7036F3B0EEDFBULL, 0xE08489404F22081FULL, 0x76C7AC2308C46169ULL
        },
        {
            0xACF46481D3A2CC2AULL, 0x83F4414EAB251A67ULL, 0x6C2105C9D73A260DULL, 0xAE1CDDD48E459317ULL, 
            0x57C0D2A9930A7E89ULL, 0x652EE8F0E327B9ABULL, 0xE917A09BEC9A4569ULL, 0x2E2B4D3B11B7EDEBULL, 
            0xA92DAAC1A782C6F3ULL, 0xD3035C2B6EA96E45ULL, 0x3C2BB057EEB84F7CULL, 0x14F9B3A77D39ADCBULL, 
            0x17EE8D406F9E860CULL, 0xC4D8C2720D8C7045ULL, 0x9673ABEDC32C494BULL, 0x13B728F8FD2EA1C0ULL, 
            0x2AD79A840D14BEBFULL, 0x8CCA937AEEE2CB1DULL, 0xECFAE9A80899AECBULL, 0x18387757DF192D54ULL, 
            0x6C71B5EBFE403B08ULL, 0x73F839DFE6B99E75ULL, 0x5C8CB95A52CAAD60ULL, 0xDA2E3C2309D5D624ULL, 
            0x68EF264F4407737BULL, 0x73C64C5EE08FF9D7ULL, 0x003B1D17BE863175ULL, 0x4860C6DEB305AB64ULL, 
            0x5EDE66FDCBA0F47CULL, 0x54DFF8BB2F73B878ULL, 0x08C5673514ECA440ULL, 0x283E975E8D350F94ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseBConstants = {
    0x68A022E34F32A959ULL,
    0x5956AFA2955FA877ULL,
    0x1E38D3077669E1A9ULL,
    0x68A022E34F32A959ULL,
    0x5956AFA2955FA877ULL,
    0x1E38D3077669E1A9ULL,
    0xED560A0DE088EC97ULL,
    0xC5C6D12B8B55517BULL,
    0xC6,
    0x44,
    0x46,
    0x8A,
    0x8F,
    0xAC,
    0x43,
    0x50
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseCSalts = {
    {
        {
            0x782A7CB6F3BAC56FULL, 0xB1831BB26F919AF4ULL, 0x7AB5454E9F1C142EULL, 0xB4D685151320A7B2ULL, 
            0x2163AB077BAEE990ULL, 0xD0E60AF48246A6B8ULL, 0x335156019B8E6EDCULL, 0x27CF0EC07A29DEC0ULL, 
            0xFBECE484465B2852ULL, 0x37518DA77E162CFFULL, 0x555C1E804BA5DD19ULL, 0x65E43404EE8F9007ULL, 
            0x6F6B4CCD580BA637ULL, 0x24E517E0BFFC3E0BULL, 0x538C322603C5A9F8ULL, 0x0C858038D3A9D29DULL, 
            0xD0D10961366C42A9ULL, 0x7FBCCE81E2AA15F7ULL, 0xA6C47CBE1A1A4681ULL, 0x9950BA78D985A5FDULL, 
            0xE453CA7FD306F70EULL, 0xF301230BD0E33667ULL, 0x6C25D288481F4A14ULL, 0xD129DD6DB764FC53ULL, 
            0x622A450F6BF6E7A0ULL, 0xC55BC083CA1F3912ULL, 0x82016E5EA04659FAULL, 0x224B013E5C9ED3B5ULL, 
            0x57315E75027D4732ULL, 0x846B2DCB2328DA83ULL, 0xDE76A2EFBEF97753ULL, 0x5B71C81429D8472CULL
        },
        {
            0xAB773E3179D3032CULL, 0xCFCC57DEBFEF9389ULL, 0x9926CCA4CA878AF4ULL, 0xE674458E0FDFC63CULL, 
            0x261E61389FBDBF59ULL, 0x92EED42089F48E48ULL, 0x55FEAE147AB5B9BEULL, 0x1F64A1CD4C8BEAD3ULL, 
            0xD546F8608A009294ULL, 0x558D7C8D6D0AE1A4ULL, 0xCC30A6A13B50DA6DULL, 0x2C53C9E508831821ULL, 
            0x1CD14AD563B14294ULL, 0xA9B226889E9E7E47ULL, 0x41C886CDA390D223ULL, 0x9539FC00985AF955ULL, 
            0xE9D4D692D3CF0CCBULL, 0xC4C438AC2ABE35EFULL, 0x5FD809AE3EF34388ULL, 0xBA7AE18FFDEB2E60ULL, 
            0x0F8BF5DD6321B1F6ULL, 0xCBA8FD05096E690CULL, 0x6F7243ACBFABB13FULL, 0xA44CD7B6EAD465A2ULL, 
            0x88D825216474E11DULL, 0xAB4554C57E679F4BULL, 0xEBA99F14989D66BFULL, 0xDAF1199C24FE7704ULL, 
            0xAD572E7EB9B2B8A7ULL, 0xD66B7B88B30D9200ULL, 0xFF5E67DC9D9EF350ULL, 0xDF5BBD5BE0ACD61FULL
        },
        {
            0x23F343250A5F8F01ULL, 0xF5AC87C692523463ULL, 0x1D383613535B5457ULL, 0x15BD61CFA4379B32ULL, 
            0x4759BD40F638DF5AULL, 0x2D15A0536057FDA5ULL, 0x70F23D87182ADCE6ULL, 0x1FCAF3D42F932024ULL, 
            0xE3BFA3842F3D76BDULL, 0xA54B52BACB90D072ULL, 0xB5CCC43661000B12ULL, 0x37BF97B436A62C4BULL, 
            0xF957507F2736EA2CULL, 0x7EEAC07F37932054ULL, 0xEAF8CD7F19F4D3AEULL, 0x85582C1C648FC705ULL, 
            0x5814AF1EFEDDC68FULL, 0x3A2D792B25EED1BAULL, 0x08A32058217A56BCULL, 0x7EEAFD08EEFC7ECEULL, 
            0x14433978E91AC3AFULL, 0xA8F4F69AC2F50FECULL, 0x9CF788B88C8646C2ULL, 0xEE473AD87B82DF55ULL, 
            0xE0950F2524F91CAEULL, 0x1F65D8E3D0224DDCULL, 0xCF49F73C9C4E703AULL, 0x1B4E6B64AB2B2F02ULL, 
            0xF845B3674406ED2AULL, 0xCB998053BC386111ULL, 0x95B2099A7EC4AFB4ULL, 0x9A40A4B36EC5F106ULL
        },
        {
            0xBF4BD3F5AE0B2B41ULL, 0x3094DC818D7C42E3ULL, 0x0B5FB3D0CB87C7FFULL, 0x2445EBE005467580ULL, 
            0xE48134048A5645ECULL, 0xEE95905E91D97156ULL, 0x343483BB20B464F2ULL, 0xA9564BAB87192402ULL, 
            0x7F3EF4BF4F2921B2ULL, 0xAFF68F9C346D7275ULL, 0x99E06E1B3FA7345FULL, 0xAFCB4F7CA883288EULL, 
            0xD3E087F9546FF081ULL, 0xE90DEEF6ECE02E30ULL, 0xBE44649453282F9DULL, 0x18BE4C5E6C4E38CEULL, 
            0xADAA4EC8A7401222ULL, 0xC10A6C188DFAE9BFULL, 0xDC72C6A3DD85455FULL, 0x92A13280BFD8916FULL, 
            0x611B7F35DF0AD906ULL, 0xD114663A8026EF01ULL, 0x714F664EF570517AULL, 0x98798549029E738DULL, 
            0xEA7902001A353ED2ULL, 0x95D5CF0E7302E5A3ULL, 0xAF343D3677D8F429ULL, 0x1157097019B202CBULL, 
            0xF4DAE515CA4FACBAULL, 0x757C8927536D3954ULL, 0xB2FFBA62EDF22CDCULL, 0x6B4016084490FA6DULL
        },
        {
            0x74F60A0D326EB726ULL, 0x0AB7CADC9711E3ADULL, 0x181F2768E2CD9725ULL, 0x958197ECB70E8B58ULL, 
            0x4AC4C3BE57AC36CDULL, 0x3E6C17B7C518CB20ULL, 0xCFA481C1595466DEULL, 0xC362CFE4BD90EEA8ULL, 
            0x23AB1BF34C55F098ULL, 0x5AD4CE31C58B9C5AULL, 0x65AA7FBF11E56221ULL, 0xA6C48C89028314DFULL, 
            0x6F05F96094754E0FULL, 0xC968AD04C2D1B262ULL, 0xECBAF85352EECC83ULL, 0xFBD5554538449E17ULL, 
            0xB8255DB03418356BULL, 0xDAB569D441B3FCD2ULL, 0x664AEB17A57D81CEULL, 0xA429752D77D22E6CULL, 
            0x2847BEB875720FECULL, 0x9E866256591B05D7ULL, 0xAA0D0138E9FEE0EFULL, 0x3A0D7575E7F6853EULL, 
            0x4CD70E690239BB47ULL, 0x43E6E319EBA9A882ULL, 0xDBD6086FE549779DULL, 0x7F366FDF5DA645A4ULL, 
            0xB52D606FF7A3F957ULL, 0x04923D0383730437ULL, 0x975B16CA8D2BED22ULL, 0x6D2063DF490A51F5ULL
        },
        {
            0xF391AD7460AEEE95ULL, 0xE518595C0A250BD3ULL, 0xB81B3F807F0C3DF4ULL, 0xCB9428450C7A4DD0ULL, 
            0xA201AABED906DE6BULL, 0x95A8833AA7B93653ULL, 0x6347D8FCFDAECD6EULL, 0x5EE9567AAD2C760AULL, 
            0x786A8D3A842AFDB8ULL, 0x9A50667F50139942ULL, 0x9DC51E005E4559ADULL, 0x4234C43B25E7D8DEULL, 
            0x0C54A6804163AB29ULL, 0xDEE8514BD524F4B6ULL, 0xAA4F98FA24083927ULL, 0x5EB25CC0D1283F02ULL, 
            0x00F1C15A9D3C0443ULL, 0x81AF245F80B4886BULL, 0xE0386706695F9BB4ULL, 0x0C3BCCBF7E53C542ULL, 
            0x4918F155EB094731ULL, 0x3429424E1C13732DULL, 0xFAF03256F5934E1FULL, 0xD1775F0A77E20F3CULL, 
            0xBA4491506916D417ULL, 0x0131AD08248CDB9CULL, 0x92296979B7DDAAF2ULL, 0xB74C392DEE3C0E96ULL, 
            0x2F7F6F1E8195CBC5ULL, 0x4366C0926389C424ULL, 0x348FC4FC8C38C76CULL, 0x6D6E7140B2D0860CULL
        }
    },
    {
        {
            0x915AE7C41A39D458ULL, 0xE4E7E5E92958C8CCULL, 0x56B4227F688126CBULL, 0xAF478928676B2833ULL, 
            0x9F6B30294D2644FCULL, 0x2A11EFFD76D6F6FBULL, 0x39879CFADFA4EFF0ULL, 0x9BAD0E8830A19BE5ULL, 
            0x5FFE2A2B38E92E11ULL, 0x7C7063A17C80768BULL, 0x866FA52B47715422ULL, 0x093D61CA9E0BBA87ULL, 
            0x99B695E0E4164ACDULL, 0x1ED5ECF532F83B7EULL, 0x9B93093CB9429CF7ULL, 0xAD2A7D09B2CA1B5CULL, 
            0x5137248AB87B76FEULL, 0xB51D678821AE3621ULL, 0x0B629C7A2EEC490DULL, 0x09D8DC878A96FF59ULL, 
            0x59F95236C1509884ULL, 0xF0E3118EBCDC277EULL, 0x9839181FB9C5720BULL, 0x2F38E6B77B3CBEA1ULL, 
            0xF954F089A1A32F9FULL, 0xCA68D5940DF38F58ULL, 0xB4F91E81D06F1A13ULL, 0x7B83DF9748756375ULL, 
            0xC244E017ECA81968ULL, 0x7E4F71E2DDB52E07ULL, 0x9A62837D14EF85FAULL, 0x46762D2DC5137D64ULL
        },
        {
            0xD94EC5C249724D17ULL, 0x621D171C39AAD4D0ULL, 0x8D827211E106E46BULL, 0x39CA513F69BDE6CBULL, 
            0x8BCB245CCF494A1DULL, 0xC52D0189B0F9E013ULL, 0xE4BF3CB986A47E62ULL, 0xE1425979B3B3F034ULL, 
            0x82B0DCE506DC07DCULL, 0x8CC73436EC8A5F5BULL, 0xC947E676BE7A8696ULL, 0xF2252AFC1FE719B4ULL, 
            0x0C8D482225D4966CULL, 0x69B4743809DE0722ULL, 0x6F578A37B95F7F8FULL, 0x707EEA67F47029C2ULL, 
            0x3B4452D3367045EBULL, 0x6EB77A516EB7B797ULL, 0x0C578527A7DA669AULL, 0xC65F7CE6978ADA91ULL, 
            0x03AFE7ACB6C7648AULL, 0x85ACC71913440935ULL, 0x75209040A25BC5FCULL, 0x3D3868EAB164494FULL, 
            0x60BBF82DBADC2813ULL, 0x342128F5F6F83F65ULL, 0x9BABF86D71C5CDAAULL, 0x7A45889518370F58ULL, 
            0x728DFC67B7B6E996ULL, 0x4B651B7A3ADB5FFAULL, 0xD0D0896A25492B9DULL, 0x7BAF0BC85F10DEDAULL
        },
        {
            0x4CAFC6BF8B91C1A8ULL, 0x53FC5BC724C796ECULL, 0x29D487CB3680CF0EULL, 0x2994381AF860DBB8ULL, 
            0x11AB1336EFF433DBULL, 0x9994F15ED4A5C765ULL, 0x1C178DBCC7300AF9ULL, 0x0775C3A7B4CBD5A1ULL, 
            0xFBB29B5C18DB0038ULL, 0x909D0DEED7F548AFULL, 0x6D90245C4E418294ULL, 0xD9CF2EEC7C3AD751ULL, 
            0x2869801533DA5077ULL, 0xD26F77495508B7ECULL, 0x03F58F6159D2868DULL, 0x43569461F8869B0EULL, 
            0xDC7EAC3413740C92ULL, 0x5EE5A34447C2629EULL, 0x41896A3CA4396432ULL, 0x855CEC64A52E5EF3ULL, 
            0xCFDD0E6FAF94C1E0ULL, 0xC415751A03FB0699ULL, 0x13BAD7AC00AF00F3ULL, 0x277D45652932888EULL, 
            0x03B9A9D12A2B0B22ULL, 0xEF81EFD85C09CA1BULL, 0xF45448A40F4A46B6ULL, 0x0C5F1D02A619BAE8ULL, 
            0xC66271BFB58C096CULL, 0x906D200C79C1DD93ULL, 0xCC23E004C8AFA2D2ULL, 0x9992142E6E31C92FULL
        },
        {
            0x9FCDC8E090E48D46ULL, 0xFFC6245E80042BADULL, 0xBFC65B073DEED22CULL, 0x62D883C45B19EF5BULL, 
            0xD4B11B56FEB07DC3ULL, 0x027BD3163F8B501FULL, 0xCA0436D1240D846BULL, 0xF9213DA3D5A9B460ULL, 
            0xCAD66C825358989DULL, 0xF35A9A0B361509ABULL, 0xD55857F00F70E342ULL, 0xA82D190C39832D99ULL, 
            0xEA0F3BDC34735468ULL, 0x2938D097CEF6D151ULL, 0x9074B7453EBDC86CULL, 0x1B7053983D9C65D6ULL, 
            0xB1FAB4F02FAEA5E3ULL, 0x4A54C2A08E2FF9E4ULL, 0xD103541180331191ULL, 0xBB77EDCA25580F6EULL, 
            0xD58F915FB5B8E1DDULL, 0xC7C3C4D9D115BE5AULL, 0xB489710263D9553BULL, 0x70F18C7129BA97D9ULL, 
            0xFF5A63D3C0CD23BCULL, 0xFA2DDF7AF3BE834FULL, 0x2ACC9E7E7632469FULL, 0x6827518C6B295DF3ULL, 
            0x6C841D2CCCD9FCDDULL, 0x951E7F7784532CD4ULL, 0x080BA69E219491E1ULL, 0xB3C1CF83B4639BACULL
        },
        {
            0x12E64490C60F3F28ULL, 0x708F0AAB2478A663ULL, 0x834F90AB99E49B8FULL, 0x02BB7A9D501EF251ULL, 
            0xFB05EEC6AE4F9F57ULL, 0xA964861266B6E474ULL, 0x9BBB0653974449D0ULL, 0x424DE24BA3C74ACDULL, 
            0xEBC0A9FBE8068124ULL, 0x46FA7842EB3B7262ULL, 0x940974AFF34D2B2AULL, 0x36F957EE04C34EEDULL, 
            0x58F30C0DAC666579ULL, 0xE65D013D306D8A3DULL, 0x9CD01D8A11AA0FCCULL, 0x3612BB9074851E56ULL, 
            0x249EF9112F2D8966ULL, 0xE079D01C7F6DE87EULL, 0xB5F2FB48E25A9628ULL, 0x8009B00671337AC3ULL, 
            0xE187181A4357A807ULL, 0x89A60BBA535977A5ULL, 0xDC61A8E0B2B9E5C3ULL, 0xC04A0E2450392FA1ULL, 
            0x7EF5775E123EF506ULL, 0xBDAB7AAE6F5A8073ULL, 0x9EAA77F2C82B80C2ULL, 0xCA21CE2B7866C893ULL, 
            0x817EBDA70CA8A829ULL, 0x15DA462C3BC7E979ULL, 0x65491ED300E5D95FULL, 0x420D457689FF7C7EULL
        },
        {
            0x1F5D68954FCC3687ULL, 0x6C5158670CB750C0ULL, 0xDAA389EA78E3FEBEULL, 0x05F7AE06199C36AFULL, 
            0x49DD930B2D0B9D08ULL, 0xBAAB53D896AAEF7EULL, 0xEAD9798DF2137C49ULL, 0xDBB0C077D5DFF7F7ULL, 
            0xE15EC9042B77B4ACULL, 0x033501BA28E7A738ULL, 0x061558548E4E1B1AULL, 0x5841162095AAD388ULL, 
            0x1B31223132815608ULL, 0xBB7644FC67234D99ULL, 0x9422088ADB2C6E0EULL, 0xE63A6427AB2F9987ULL, 
            0xB897CA352FBA7B1BULL, 0x9A124CED225651FBULL, 0xB33A653DEC97398BULL, 0x4852CC9FF1F7C578ULL, 
            0xE7F9449B45EFCE41ULL, 0x37651492B2A00A81ULL, 0x50E8FF520501E37EULL, 0x36717C0B2FCE5844ULL, 
            0x58C1F375B35A58BEULL, 0xD1560FF6670BF1DEULL, 0xA7974185849FBFC1ULL, 0x35B72B004716A4ECULL, 
            0x2578377B35CB9162ULL, 0xAB9FBDDA5DE01E02ULL, 0x305A8C03FD13BABDULL, 0x2F7AD8997BC8B03EULL
        }
    },
    {
        {
            0x2B52D998E730CE1FULL, 0x9191DCC3CC205ECDULL, 0x29925653EEFD0CD9ULL, 0xF409F4F3946642D1ULL, 
            0xC1A3244A079C05CBULL, 0x7092DB0BE3C4A457ULL, 0x6BA72E69CD59C613ULL, 0x4E162EE1BF9CF8A7ULL, 
            0x2F929B095681B58CULL, 0x188729F83F0EE57AULL, 0x82314F9D59294D76ULL, 0xDC27AF9F02BCF581ULL, 
            0x7F84017832771D54ULL, 0xBFA7F16A709C470AULL, 0xCA02E5F0DF98650EULL, 0xFCD2CE8A86D1910CULL, 
            0x19A5548F899D24AFULL, 0x02F881D93C54B226ULL, 0x90B95FFC4D4B360EULL, 0xFF071B0ADC4974C0ULL, 
            0xD16F6E7E834B9A9CULL, 0x9187E7276D950BC6ULL, 0xDD7872203B6B0805ULL, 0xBA2A4AA53AA5ED5CULL, 
            0xA380716224E5B34BULL, 0x313BA38105CE9857ULL, 0x959F229B53952AB8ULL, 0xC63750EECF544F03ULL, 
            0x4D6C982A3C9DCE91ULL, 0x9F095BD0935D4504ULL, 0x375C362A683C65F0ULL, 0xD953D7BA01400F6EULL
        },
        {
            0x23A3D09F54DDB5C6ULL, 0x6F090F9187F3FA04ULL, 0x21B70965F31BF6B3ULL, 0x0AB1E95942644224ULL, 
            0x494E195A6A6A2102ULL, 0xD55634AA157F6D1FULL, 0x0C19B1560A5C1797ULL, 0xEFC770D428401F51ULL, 
            0x1CB9B04BE4646D68ULL, 0xC9CEDA8293893B61ULL, 0x860D25832C38C62EULL, 0x6500BBF6D7906B3BULL, 
            0x0BCB7204FC0BD219ULL, 0x86068EFC88B67CCCULL, 0x100E8C7FB346B7BDULL, 0x0FFF7F1BA84D5B17ULL, 
            0xD8953CC4131B7403ULL, 0x112A641B72E53D1FULL, 0xC016ADED364DC415ULL, 0x3861E8C6540DEAC6ULL, 
            0x77FD3C029A1CE5F6ULL, 0x29C596B1E3E53FAEULL, 0x3C944065F43DD30EULL, 0x25AE7875EA63EC25ULL, 
            0xF139A3252806910CULL, 0xA70887AA7EEBC0B5ULL, 0xF4B8A88233AC7CBDULL, 0x8D2EB1C29C11BB3CULL, 
            0xBBBB8E40FC17AEECULL, 0x80CE5CFA64C7E3F6ULL, 0xA331CB4ABFD35F8DULL, 0xACB40BDD9F0D0350ULL
        },
        {
            0x63B58F6B29EC4D0BULL, 0x9F2B132CD621D878ULL, 0x499DC0599E3B2E6DULL, 0xF51A94504BBF5FADULL, 
            0xDBDF580FF59729BEULL, 0x94FE071DF363B2B7ULL, 0xE92DFF6189E19B10ULL, 0x5E06797352A43904ULL, 
            0x9B3217052D822C5BULL, 0x5F2C6243A60376E3ULL, 0xC12FD5201C3DECFBULL, 0x7609F6790C9F8C31ULL, 
            0x4FB973B8F4BE6D41ULL, 0xC04E5751801CF99DULL, 0x285CB23C9EE59B06ULL, 0x07F008C5A101D9F8ULL, 
            0x478A85E343D64A3FULL, 0xCE8C6B888AA43B81ULL, 0x185B6EC79D56789DULL, 0x0AEDF81E77EDFA4FULL, 
            0xE9297431FE5A8567ULL, 0x18A4BD41A2F39B41ULL, 0x5727F4F4CCB597D6ULL, 0xC67F46912519ED95ULL, 
            0xCFB99A499215F9F4ULL, 0xCC4ECE8BCB48E35FULL, 0x32C4312D6368B2B0ULL, 0x0C16BBAA11C658CFULL, 
            0xA45DA9353335DF30ULL, 0x823AB0407909B277ULL, 0x071DCC5C254F289CULL, 0x336B94118CED4C61ULL
        },
        {
            0x5953CE1E9E08241CULL, 0xC6721DB436EED87CULL, 0x888ACF9A30C711FCULL, 0x491FBCDC6870C0C0ULL, 
            0xC38D695816045072ULL, 0x7B4761C353E206BBULL, 0x51314AA37B86834FULL, 0xFE5D835BE563BF6FULL, 
            0xC36EFE23D8CEF5B3ULL, 0x5B3ADD9B0D45CC5EULL, 0xEE95805FBA2B49E9ULL, 0xFEF1C119E030A7BFULL, 
            0xE5135E92F4C27ABBULL, 0x328C785E8B8F584EULL, 0x083511ED5C8A2813ULL, 0x15B97BD567E5664EULL, 
            0xCF41CDD0773BD227ULL, 0xBE8169244B83F602ULL, 0xAE24E7CDCCA641F4ULL, 0xD0473F98C7AA5F62ULL, 
            0x14FFDF3A6395E90EULL, 0x8113E51B418C783FULL, 0x9FCDD5F2ABD91670ULL, 0x82BF57A6D6EBD088ULL, 
            0xB84A22CEB75F3D00ULL, 0x0E32DBEB5BB9E701ULL, 0xCB4927A656BB0FE5ULL, 0xDC436FEF5056D6DAULL, 
            0x0B370A356BAEAEABULL, 0x27247AA43C14FCF5ULL, 0xC7BB348258D17D3CULL, 0xC67790249C4B0246ULL
        },
        {
            0x5C216874F76DC9A7ULL, 0x938146BB97E0729AULL, 0xF94097F9AB621282ULL, 0xF84A3602A828C175ULL, 
            0x61263AF589523444ULL, 0x3D484CB37BC3B9E0ULL, 0xFD572208ED2B9EC6ULL, 0xBA2741B590FAE9A1ULL, 
            0x9808406300159337ULL, 0x4DE29765A94BA7CCULL, 0x2F5C8DA05607802CULL, 0xBC85BE8614846D9EULL, 
            0xE9788C67230399A2ULL, 0x3B88F8896E4FC1A3ULL, 0x763843880463162CULL, 0xB80F3171D1E993F0ULL, 
            0x6C93509E3E7BA5C4ULL, 0xE64BECEC0C86CDF7ULL, 0xD39BB2F1CFF38B04ULL, 0xED3361CAF43F343AULL, 
            0xEB113A0F80C9515DULL, 0x1F6012117B34D0F3ULL, 0xF35FF32D841C63CFULL, 0x40F5F18747432F41ULL, 
            0xE97DA7425199D5ECULL, 0x562EC030BE566C24ULL, 0x9F105255A6177847ULL, 0xA39EBC1C971F0FD2ULL, 
            0xCE22401A9CE691B8ULL, 0xA315C6F9A7CCC0E5ULL, 0xD3D8D0C714529B40ULL, 0x5D59A0CC0F0FC0B0ULL
        },
        {
            0x781C13AC54DA5384ULL, 0xB2C6ED595B4F075CULL, 0xD19181F67628DACDULL, 0x58DA456610D0F17AULL, 
            0xA60CB09D694830A9ULL, 0xF6021E3491E3BB5FULL, 0xE5AB6ABB0770DE9FULL, 0x1E97B271E45CDBB8ULL, 
            0xB26DFA23131AA6E6ULL, 0xFAF7A8A30BBDE5F3ULL, 0x59B16F0D4850D248ULL, 0x3993E363A6E86A3CULL, 
            0x3A1EF5BE070D1F8FULL, 0xD28C024C9593B1A2ULL, 0x1AC46FAF8A41C332ULL, 0x3415F00B075FCAA0ULL, 
            0x9613D649EDD798A0ULL, 0x88316BB11F65B46BULL, 0x3AD687D7795C3EFEULL, 0x3EF20AD9CF46B5F9ULL, 
            0x165CD2B402091A7CULL, 0x2746895C8AF4E814ULL, 0x75D1042D12776E27ULL, 0x8871A6714B7DB47AULL, 
            0xB70368F16387779CULL, 0xCA2A84A1D5603E8BULL, 0x0F09F701AB987D58ULL, 0x24D8115F5B69490CULL, 
            0x9054C60739CA4692ULL, 0xB68C40B77CC6C141ULL, 0x02C7507F7C1FE75BULL, 0x52C40A2F8823F13BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseCConstants = {
    0x1162725209A91990ULL,
    0x7C7A1E2A399AD1A5ULL,
    0xA31F12BA81E21107ULL,
    0x1162725209A91990ULL,
    0x7C7A1E2A399AD1A5ULL,
    0xA31F12BA81E21107ULL,
    0xF00595382DE34FABULL,
    0x138D41B0D57E5549ULL,
    0x22,
    0x71,
    0x7C,
    0x4F,
    0x94,
    0x79,
    0x1D,
    0x17
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseDSalts = {
    {
        {
            0x91C5CB1EC08C3C72ULL, 0x10EEB4E172B6227EULL, 0x95D0EAD67AF29FFFULL, 0x24ECFCDC0E00324FULL, 
            0x50EAE0B016A7EDFDULL, 0x619962C926283D74ULL, 0xD45CC1A02A0976F8ULL, 0x2B0E33566D44ADC6ULL, 
            0x804CD58EF0F134A8ULL, 0x27C22888A20F5BC3ULL, 0x4286982F3AA63991ULL, 0xF5A8E0EEFF63A480ULL, 
            0xB3E20AED2376386BULL, 0xE9390FF188878CDFULL, 0x82DD6B690DE8C322ULL, 0x8244194C742ECB5EULL, 
            0x7C6FBB55CC49CF21ULL, 0x41326825D576C5ACULL, 0xAAE97BCD4FD5E1E4ULL, 0x7BF1AD6FF228A854ULL, 
            0xB1318C58EFED509EULL, 0x7C3FC671B5DBF978ULL, 0xE8968855ECFE68D0ULL, 0xD59E76763CE6F447ULL, 
            0xAA914F2C039FC3F7ULL, 0xFBE1F712F7C126B1ULL, 0x91CE58702C943400ULL, 0x5A4C4DFAE50AC5A7ULL, 
            0x471F6A42453D935FULL, 0x4F7B711E674F1B95ULL, 0x7F0A12118980E1EAULL, 0x51E40408CD3D4748ULL
        },
        {
            0xD6CB1CBBE17FA803ULL, 0x4D77113FC61EEE75ULL, 0x95B1C6B4F180C353ULL, 0x0408D97A66DF4078ULL, 
            0x67882421AAAA4B84ULL, 0x104809C97A03B4F7ULL, 0x85FF8F0E4414A4E5ULL, 0x91313F188655A504ULL, 
            0x3EA7B3B46EC83CF6ULL, 0x3AE4BF43F28096FCULL, 0x85295A6272C7040AULL, 0x38A8D1F6DAF09856ULL, 
            0xDAD898F2DA0B5F05ULL, 0xF12EF47D603596E1ULL, 0xF452589DF2158549ULL, 0x9B7DDC23BB819EC7ULL, 
            0x203D6520507C6DFCULL, 0x44CB4FE64690101DULL, 0xFC81F87BC41986E3ULL, 0xCC5C73ADAF559F98ULL, 
            0xB58D21E703674850ULL, 0x40EB1281D20AED87ULL, 0xC5E435B0886DAA1EULL, 0xFDDFBC96C43BAF26ULL, 
            0xECE81CCB3450BC24ULL, 0x5D449FBB3B0982D5ULL, 0x86CF41A617D11859ULL, 0xE29F97406B3824B3ULL, 
            0xF9CC50E5C2BB4F4CULL, 0x7F13E4DDDC2C21ECULL, 0x3B42293218956940ULL, 0x92345C0E0B93E4A6ULL
        },
        {
            0xDA01F148AB2C3C30ULL, 0x7381373AEABEE83DULL, 0xE9283F65B5D94584ULL, 0x7548583D0BE9F86CULL, 
            0x98D455B720BD0D49ULL, 0xE2BF49E4E47352BCULL, 0x036D16E31371ABE2ULL, 0xB8814E4141E2B938ULL, 
            0x99EC30295368BA4BULL, 0x0806ADA58F70BF00ULL, 0x0D29D58153F60E94ULL, 0x7D39F4F36F2C9EB9ULL, 
            0xFBDC957E0A94296AULL, 0x93DDE0A4A54D1CB7ULL, 0xFE02D8077C44B37EULL, 0x2388A70CDF554A07ULL, 
            0x35C2347E40DC8E0DULL, 0xDF8D5FB63CF7E0FDULL, 0x46238BD4C39D396EULL, 0x6486B71E41E7952DULL, 
            0x4F3E79ACBDD263C4ULL, 0x116CFE15E40D48AFULL, 0xEEFFDA56271F1F96ULL, 0xE5FF3261D958AB25ULL, 
            0xE3E7858C789954C6ULL, 0x88985C95BCE50C30ULL, 0xF18D8CB4F7649CE4ULL, 0x90AE49F7196BAE4EULL, 
            0xD4F83BB335195DD3ULL, 0x2F69C8E3F1F64803ULL, 0xE775B62E7CF69580ULL, 0x148E1059F7820A68ULL
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
            0x361F840260EC287EULL, 0xE25486FEE80C51B5ULL, 0x6D5882BDAB30D44BULL, 0xFF8E196DDCB719ECULL, 
            0x7C2A8021C1E0EBB9ULL, 0x7BD87EC46E72A838ULL, 0x0728E4AB2B1A1A66ULL, 0x5DF7AD6A36B19DAEULL, 
            0xE9E93F6603A2011CULL, 0xE43B10275DFF64D9ULL, 0xFB094C6CACD588C9ULL, 0xAAD58C76DDDF1FFDULL, 
            0xB8B1C517693E6BF5ULL, 0x2D0E4035B095FB91ULL, 0x64D663AD40D26660ULL, 0x8F0EE8E6BFE8FC83ULL, 
            0x4E8BAAD1742A05F5ULL, 0xF3DD8FFDBD71AF1BULL, 0x35C0433B82202AA1ULL, 0xC45D8DBDBA3E0A90ULL, 
            0xA56EB1E8F7A97B4AULL, 0x77B49F490F94600BULL, 0xEA986E920A392E1FULL, 0xCF56A67998352885ULL, 
            0x48537006A4FAF08AULL, 0xAE5F64F30AF92367ULL, 0xB5F594853944054AULL, 0xAA3A20BE2F1815D3ULL, 
            0xC1D230BF98DFCCB9ULL, 0x2C46FCDA183C77A9ULL, 0xD1FCED0632F600A0ULL, 0x81F31D6B7B6D7793ULL
        },
        {
            0x1EF14170222F83D5ULL, 0x625EA092883E7921ULL, 0x2F32CA7490361E63ULL, 0xA7DEBC40965DFD4FULL, 
            0xE69EB76B1BC48E4FULL, 0x353D8BE3CCC667CDULL, 0x30935EE422405E96ULL, 0xCA3C20FEACF88C7AULL, 
            0x77E74DFDB1CBF763ULL, 0xEF7FE14A5F9878A5ULL, 0x1B943D63E9DB3A18ULL, 0x2AD2368FF66AEA30ULL, 
            0x83E00CF1BCD2D27BULL, 0xB8558F133AF69739ULL, 0xDF5CC8F949987159ULL, 0x6D83EFD59A32EB3EULL, 
            0xBCEA73281B9A67CAULL, 0x2C69AD617FF5AEB5ULL, 0x5AE5E44C4917A851ULL, 0x265AA97CD73AC421ULL, 
            0x84D6AF87AEA1FEABULL, 0x5736D7644089649FULL, 0x99949980BCCE2011ULL, 0x297A47E4386028C4ULL, 
            0x949C3ABD55750727ULL, 0xCA299B30D4C38883ULL, 0x8F0FF608A9B210F7ULL, 0x637A75B30D325386ULL, 
            0xAAB8C89F13383EA2ULL, 0x4ECBCF874BBD8CE7ULL, 0x3C2A2EA819A2EFE6ULL, 0x96C91169E080F94BULL
        }
    },
    {
        {
            0xF8A174DD418FFEFEULL, 0x9748AB403E8157DAULL, 0x6E2FD2BF83EAA2D8ULL, 0x18705D6C70BB58D7ULL, 
            0x2F0F970CE9984A6EULL, 0x5120C6158E924C8AULL, 0x7CBA47984F38F68EULL, 0x6BFD6072D2189D05ULL, 
            0xFDB5E39DFF0556DFULL, 0x00C70E83CB106F4AULL, 0x655F71CEA7D617F6ULL, 0xC0AB576C58493E42ULL, 
            0x011FCC806ACA2E4DULL, 0xEF0D09FA56612CC8ULL, 0xE0702557B12BB301ULL, 0xDD04AE6C2016B912ULL, 
            0xED51DD266193B7D5ULL, 0x1C226F28DE058157ULL, 0xC14430760A16C5A8ULL, 0x0A0318F3E0B6C5D3ULL, 
            0x1928EB0914189D86ULL, 0x6E6E9D5772C2BA55ULL, 0x9C032CA36368D7D6ULL, 0x1C3CE47AC51CA9DAULL, 
            0xC15FC5CD03EAC174ULL, 0x061B491F1FE47A2AULL, 0x1B8AA87FE361ACF9ULL, 0x145AB9E249C09DE9ULL, 
            0xBC27E9A0C8DECACFULL, 0xB514D9496585B253ULL, 0x361BD72E74D3CC55ULL, 0x3C518DC61199457BULL
        },
        {
            0x146407AB151A1278ULL, 0x35CCF585DD596C68ULL, 0xAC7B04F1A0364936ULL, 0x0BA95F6AC9B5987DULL, 
            0x7A55174CAE0EABECULL, 0x6EBE81857B680BE8ULL, 0xE942D8E66017853AULL, 0xFE83794A7B720063ULL, 
            0x7E49A369F0F5A664ULL, 0x8FD533C418E3554FULL, 0x369235E02B1E192AULL, 0xB826707E775EEF00ULL, 
            0x02F52473F0966341ULL, 0xEA5E7654A65BDDCCULL, 0x634CEA320AF88457ULL, 0x0C509ADF4826CFD8ULL, 
            0x34D76765A6DF9BA3ULL, 0x9E301F5CB55C4019ULL, 0x0BA48AABABBE3F8BULL, 0x898D2A76DC1DEA5CULL, 
            0x56220ADEB47F6DDEULL, 0x2B1E3B4857818BD5ULL, 0xA8E1B261020A78C9ULL, 0x9A10A5F911A17927ULL, 
            0xCCBE61791B2F2D9FULL, 0x2FF6CFBB1416C858ULL, 0xE88245B7C9BF316FULL, 0x0FCF8684F0F4AE2FULL, 
            0x5A00EF4CD550BD9BULL, 0x0A2ADE9DA63337FCULL, 0x38BE002E768F3DE6ULL, 0x59D32ACC1D18A405ULL
        },
        {
            0x2A28E4A974E8B90AULL, 0xD61F761CB6C30191ULL, 0xE0F9BA87A22F8E04ULL, 0x00611560253945ABULL, 
            0xF5BEB8733FD2EEC7ULL, 0x0FE941BFB67F64B3ULL, 0xF3A031BD2D7714B1ULL, 0x4F17E193C15BE715ULL, 
            0x455B3AE3FD043A1CULL, 0x4BFC466FD2C8107AULL, 0x9122AB8F660645FAULL, 0xA5A09F236CD8B49FULL, 
            0xFF51D998E513DE74ULL, 0xD86E43F041AC590FULL, 0xCC1C5B0122ED819EULL, 0xA1CD3708BD128B6BULL, 
            0x523183B6BF9066E7ULL, 0xDA11665E04386627ULL, 0xC798FD482EFA5D28ULL, 0xD50C9C9E0406D480ULL, 
            0xE5BDA47B52637084ULL, 0x05C77BE0590BA44AULL, 0x0F14F7227F948BDEULL, 0xD77ECC2A05D39FFCULL, 
            0x54336552A4D57148ULL, 0x1BA3A7CB9620D24EULL, 0xB1BA2FB16B00AA09ULL, 0x5D5D64ECFA328093ULL, 
            0x268B804ECBD117A5ULL, 0x6E9A2C26A08B4F0DULL, 0x99E2DB4C9D88315BULL, 0x3177D327CBDF895DULL
        },
        {
            0xD3F596B1737889B2ULL, 0xE07B2F7BD8969A27ULL, 0xFC99E2F9205170C9ULL, 0x14A8E388DD6EAD41ULL, 
            0xDFBE74CFB317ACD6ULL, 0x34F41D3CC07E2838ULL, 0x9B657556148C772CULL, 0x57FB0552C5270728ULL, 
            0xBC80D8C7C672896AULL, 0x25EAB620081F88CDULL, 0x7D9273CC2B85AD67ULL, 0x1566575D96AE4D67ULL, 
            0x2A9A9ED061673E63ULL, 0x76FD380CAABD09E8ULL, 0x60BBBB79524DD96AULL, 0x62D788C78E9A4C60ULL, 
            0x703AFA59161A3BA7ULL, 0xA76FCE7B91FEF3B0ULL, 0x81990298DF1BA897ULL, 0xCE65AFACD7051A9EULL, 
            0xD0C2E4F0008BB8DEULL, 0xE4EBA63BDA33F140ULL, 0xE44295CA647088B7ULL, 0xE00279223BCD55FCULL, 
            0xA205F5619AD52AADULL, 0x99314C97C7E8C59BULL, 0x2A462AB0A59B6FB2ULL, 0x55D80A4DA757BD9CULL, 
            0xEBC065C7C5FCC160ULL, 0xBB0FB48B3457B9FDULL, 0xF84A0E4D33B5E0E6ULL, 0x9599E0231B8EC549ULL
        },
        {
            0x36BF9A021EE75C1BULL, 0x365970D9B1545897ULL, 0x00C664EC4CC1B125ULL, 0x182C20288E5DD840ULL, 
            0xC66747FD384CCCCCULL, 0x6789F3A1C99FE7ABULL, 0x4ECEED088D8DC09EULL, 0x935D59ABD0738D84ULL, 
            0x8564DF452263A5BFULL, 0x005CDAA2A2A48A4AULL, 0x2F12ADA20DE47E75ULL, 0x4EBB6A92FAAE5776ULL, 
            0xCF6BE8B10211DFCEULL, 0xD4E7F8BCD36CF89DULL, 0x0DAEA07DD42F74E0ULL, 0xD81F36E437302687ULL, 
            0x597733189B011746ULL, 0xF1D5B6392D409C16ULL, 0x4CEBE1204080DDE8ULL, 0xD9C6EA1C091F52E6ULL, 
            0x75072CEACE850545ULL, 0x57EC8B949AAF8FBCULL, 0x9DA774038ED88E39ULL, 0xD80C67BA44674A02ULL, 
            0xD9A9A1379916934CULL, 0xC2252E3F91727EB3ULL, 0x86FF523015A519A4ULL, 0xD86EF078EA3B802CULL, 
            0x39EDC1546A38FF96ULL, 0xD2F6EEC800889B5AULL, 0x9E22640D87C33AC5ULL, 0xF2E23EC9BD577B43ULL
        },
        {
            0xBBAFC32CBC96F70BULL, 0x8EE4073B24E39313ULL, 0xE98D6326E2AC3B48ULL, 0x97264C2E64C04059ULL, 
            0xF352FE38A8F76FF9ULL, 0x8EF0A16B8758A93EULL, 0xAAF802A07247D23CULL, 0x388D224440E4F84BULL, 
            0x7FC4BC636110B9B2ULL, 0x4763AE9E4707028BULL, 0x6A4972269D5C7A5BULL, 0x0257F6871FD57D59ULL, 
            0x422C3D8BD18C46EFULL, 0x447C488851259E98ULL, 0xD5AF427D5BEDD593ULL, 0x9C7E2846280C1B9FULL, 
            0x60E113D36869B48CULL, 0x4E42CFA25F37392AULL, 0xA42BF1E2542954B7ULL, 0x25C8BABAE4B8FD79ULL, 
            0x77A742E8C7E74B3BULL, 0x5AE98BE442576DB3ULL, 0x96CD76D494C161B8ULL, 0xCBCEB1E33C5BADC2ULL, 
            0xBC29A9D5179FF300ULL, 0xD8D65A599ACB9D3DULL, 0x3336690A900CE0D4ULL, 0x05A896E7F1B818D1ULL, 
            0xA05C53EE89665E4AULL, 0x84C612DCD9F0832CULL, 0x5D6BB9EE5E2813D5ULL, 0xA170FAEEBA926AE1ULL
        }
    },
    {
        {
            0x6AA94238E9689449ULL, 0xC1293B369A6B9B3CULL, 0x96964A29FD5D4328ULL, 0xB4FE4931BCF1FE2EULL, 
            0xDD434EBCFF4D6070ULL, 0xD7530EDB376D3989ULL, 0xF5436CACC372355FULL, 0x15C6FF385CEAD3C9ULL, 
            0x428CC3ED22FA4BAEULL, 0x88BEF6C3F9264F3EULL, 0x4CD0F0B8ADD94EA4ULL, 0xB5859A25CA0FE69BULL, 
            0xC3FEC3FF5E8D6900ULL, 0xD5948C92C78EC566ULL, 0x231DDC3C5FE28179ULL, 0xB41BA71272C71073ULL, 
            0xA88B1B104FF8B053ULL, 0x99BD135DBBAA9A36ULL, 0x0516FD65FAD743D0ULL, 0x9F6A30256E958ADBULL, 
            0xE132514B7EA97F61ULL, 0xDFED1AA1B87AD352ULL, 0xEEED41B159BE316BULL, 0x33DF612995DD02EEULL, 
            0x67F5253A08E727FCULL, 0xC068C2D607AE5BC3ULL, 0xFE1239B55DE090FBULL, 0x69D45FE3B2D23B59ULL, 
            0x642E00B719D32BA8ULL, 0x724B0930D3C57E33ULL, 0x8E76D60388E7C69CULL, 0x5C9E71209E570343ULL
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
            0xE01B3A490DBE97B9ULL, 0xEF057CBA4D5FDAF8ULL, 0x068454C7E471156AULL, 0x4F0CDCFC432399DCULL, 
            0xED41B708EFCD72B4ULL, 0xEA2FAE486C27E65DULL, 0x285AC03FFA2709AFULL, 0x88C0266CF179A8BEULL, 
            0x30BE25D227B633ADULL, 0x6149C3E569B8A492ULL, 0x18FA5AE53AFB7339ULL, 0x8DDBD2323940B86AULL, 
            0xFC8823DC3921AC09ULL, 0xD11AF57957CFABD9ULL, 0x8CDDA5A5F66DF8B3ULL, 0x07D3BFD0AABDB05FULL, 
            0x7B738170ACD12CCFULL, 0x2117FF180393E703ULL, 0x220A9E60DF212228ULL, 0x3C7A0768BA3DD9C9ULL, 
            0x3C51A54C25801C83ULL, 0x128EDB64E24FA949ULL, 0x741E4D4E9F70BAFFULL, 0x2B0E434B3040E463ULL, 
            0xB3630523D7B33094ULL, 0x5698BA92A63DA4C5ULL, 0x056F692C72EF448CULL, 0x1F4F3A775C51E168ULL, 
            0x0F289B6582CACEBBULL, 0x0E21A8C929309466ULL, 0x479277CF461AEF34ULL, 0x4EB0C04E84AEC0A7ULL
        },
        {
            0x21E9EA3134F480ABULL, 0x45824F62FB02D2E5ULL, 0x2ACC4927EE8618B4ULL, 0x598A1DAEB9CB6CF5ULL, 
            0x572F20767646577CULL, 0x9A356FC5AF7F5486ULL, 0xBD5FBC56F58F830FULL, 0x1178A21CD2239337ULL, 
            0x9832543144AD16F0ULL, 0x74A6C2011B1D1589ULL, 0xA39C75DF8381E8F3ULL, 0x93F9247581AF8BECULL, 
            0x1954E47411FE1F1BULL, 0x4FF3AB4E9FA0EB28ULL, 0x0447AE3377B42426ULL, 0xF76E5C8DDE0CE4A2ULL, 
            0x819A1F04017232BEULL, 0xA30A7F3F4C40BAB0ULL, 0x746E40829CA9ED83ULL, 0xD0FB966DAC64A325ULL, 
            0x5A9DAEDE5285533EULL, 0x66238D832D52E7D9ULL, 0xCCE5B29D525C4F3BULL, 0x70D2733DD3FDFA2DULL, 
            0xBF51B8360D61B113ULL, 0xE426F4483B2E5B5FULL, 0x39849E25169572FCULL, 0x4982F0043523A06EULL, 
            0xA8B2DCB46B520523ULL, 0x89C93EFF256A94A6ULL, 0x0EDCB90F3A57B770ULL, 0xA4273811053EFB83ULL
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
            0x14B60BFF2E9A1163ULL, 0xCE7A2157E11A0BB8ULL, 0x8E58B5419107691FULL, 0xA5F35D9AB8B82D19ULL, 
            0x602E553BCB31D33EULL, 0xEC1B257658F1A73BULL, 0xB00BFEF2FCCDDD71ULL, 0xC56EDD9FF06251BFULL, 
            0x1E18AA708D181B02ULL, 0x5868B46F982C6655ULL, 0xABE31C2305148959ULL, 0x3A6F83DCC7E5D052ULL, 
            0xEC12B1A5268D53A3ULL, 0x1A423B2C21B65484ULL, 0x9DC1A75238650F37ULL, 0x1D6F7141FD2E4AA4ULL, 
            0xBAC4C24C752929BAULL, 0x22BC0C778FA849BFULL, 0xF93B186D5B821BD2ULL, 0xE63AF8D7BBF0136CULL, 
            0x35FCD4CE13818F7AULL, 0xCF3B4EACCB9804E3ULL, 0x7B803F473A18A1F1ULL, 0xAE86B23B02F61181ULL, 
            0xCB40642E7F32496EULL, 0xB8CFE4B6CBF10B1FULL, 0xBD3E9A017991EC88ULL, 0x6127F81CE74F9292ULL, 
            0xFA5F023CABD0D6E9ULL, 0x87F72CCE84393026ULL, 0x450C734206A53221ULL, 0xED28FC06F7F3B339ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseDConstants = {
    0x874221D5D298BD36ULL,
    0xC78BB1C9AE381C34ULL,
    0xC0D48D4881945D29ULL,
    0x874221D5D298BD36ULL,
    0xC78BB1C9AE381C34ULL,
    0xC0D48D4881945D29ULL,
    0x0F2D8EC1410EE0D5ULL,
    0x50AC6E6142E377E9ULL,
    0x5E,
    0x8C,
    0x64,
    0x4C,
    0xE7,
    0xA3,
    0x3C,
    0x19
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseESalts = {
    {
        {
            0xAF20B056C9B21BFCULL, 0x2F5088D8839EAE7AULL, 0xEE31A7168854682FULL, 0x12CACD525097DE0FULL, 
            0x3FF7B6B0C08727BAULL, 0x3300F67577C56312ULL, 0xCD2CEC8DCB726E34ULL, 0x01BAEB373E88B225ULL, 
            0xD164344B6977FDD9ULL, 0x48DB0028FEE359EAULL, 0xAD5150EB087719BBULL, 0x7895EE8C613233B7ULL, 
            0x9CDECC0621A72CC7ULL, 0x463AFD9A94F3C902ULL, 0x5D87082D1C5E6CD1ULL, 0x2FDA676F907BA676ULL, 
            0xDAC9474593035EE2ULL, 0x329B1F1D846668D0ULL, 0xE461FE4273F81EFFULL, 0xBF59E81D894F93A1ULL, 
            0x7A5E9457DFE1EDC8ULL, 0x2EEED4F5B00DDB7CULL, 0xA55A0E71E02B5B95ULL, 0x16466E60D8058C91ULL, 
            0x74A296A1D4B6BD9FULL, 0xB0944BC3664ADE2EULL, 0x569A39C05B5E2B79ULL, 0x4BF67972688575CCULL, 
            0x985FD5FB0045A95CULL, 0xB33695ECE055EA89ULL, 0xB09A7EFCB463BD1DULL, 0x60A3E3367936C43AULL
        },
        {
            0x80BF87B3924B96B8ULL, 0xC2C13B3D6A8F5CA7ULL, 0xD00FC9BE76FF536BULL, 0xA6CA7D20CCB93BCFULL, 
            0xCA3BEA51DB609679ULL, 0x6B064B19AA79F4B7ULL, 0x6B4017CD89F9CDD9ULL, 0x50D96B0A7D4153AAULL, 
            0x5ABAD8BF9F71EBC1ULL, 0x6AE96B8CEBE24D0EULL, 0x31C1EC43AEFB98C8ULL, 0x9894ECB80A5E43B0ULL, 
            0x52A85A9FD2756345ULL, 0x72546327ED49CAC2ULL, 0x805BC7BB661CF678ULL, 0x03C468F60A7A384BULL, 
            0x2DDD268EDFC6652FULL, 0xA78C00AA5702D824ULL, 0xB82DE4C1C02B1E82ULL, 0x0AA797B44AA1C69BULL, 
            0x85925F197EC21F60ULL, 0x655B4CEA5D5D5DCFULL, 0x1FD70087570B57A3ULL, 0xDFF4DE0433534E00ULL, 
            0x0973DE34F31F6A94ULL, 0x7C4DB0102B6A16F0ULL, 0xD281DA2AEFCA1CE7ULL, 0x777A9F156FAF09E9ULL, 
            0x13DB2B3AF36FE2BDULL, 0xD5D14A735FC4EB75ULL, 0x1FBB00B2D45F620BULL, 0x90BBB2D0A7F17CB1ULL
        },
        {
            0x3F5DCC5626BA0CC2ULL, 0x5BC36D260205CBC7ULL, 0x88DFE400DE743B5DULL, 0xD8FF6D0283F39691ULL, 
            0x42FD6FDA52ED758CULL, 0x10F5F5790175EE0DULL, 0x9D31CB7F8639B87EULL, 0x2850BE37F435A47DULL, 
            0x0CFE413FAB0BBD25ULL, 0x325D69B881217A7EULL, 0x7E285844C3FCFAA5ULL, 0xA2A3AC853DA20D41ULL, 
            0x1FDE1CE27CC87217ULL, 0x8FD927F9F00BE33DULL, 0xA2031F189D5215A3ULL, 0xF272D6DBF34763CAULL, 
            0x0B5B87B73E16E508ULL, 0x1C9E1AA4EAFC05EFULL, 0xC8AD1F9421C7B920ULL, 0x70204A8E6C4E435DULL, 
            0xB5BB01DFA2DF4C59ULL, 0x28F8C82B59832565ULL, 0xB6670278E9233606ULL, 0x912B46FAFE4F396FULL, 
            0xD6EF7DAF068206EAULL, 0xFC7D42CE58565847ULL, 0xF727E64611EA94D1ULL, 0xB42CDA6E8167A45EULL, 
            0x86586F6916140F9EULL, 0xE36FCEE1110D032FULL, 0x17F3DDC51AB87196ULL, 0x3D670BDA6DD16570ULL
        },
        {
            0x0537B3F2159F6029ULL, 0x0339B89738F62BCEULL, 0x2A785AA52BEE8106ULL, 0x5E6364454B64942AULL, 
            0x13E3EE32F5C14097ULL, 0xD781FE8CCEAE6DB8ULL, 0x12D9BA9E6D979C7AULL, 0x29BD20E9BFDB6E55ULL, 
            0x03771E6B1BE25484ULL, 0xE7A7C542537CDF39ULL, 0x2817FAB41BEA0452ULL, 0x29EF9CE6DE52460DULL, 
            0x73EEEE918739CA5EULL, 0x9F0785AA6AF7E41FULL, 0xB5FDD1AC8B5239C8ULL, 0xD03EF68A47B395F2ULL, 
            0xD473CE69874E81B3ULL, 0xED4D553C9A359BEBULL, 0x3270131E2630DBB6ULL, 0x4F2D4C2BC61B57CBULL, 
            0x1B66C65046058BC9ULL, 0xF1335C6E39D3DE04ULL, 0x7D6E6F734DE54B22ULL, 0x9A0D9E1F51E54E90ULL, 
            0x32E6CD4236E68731ULL, 0xA225AF7FF10BA9B1ULL, 0xF6E7E44B50FBF5CDULL, 0x1E9C61D0A3D24C78ULL, 
            0x3FBDE5F80B7A6C68ULL, 0x5217D525C3FC45C6ULL, 0x2499E62E21480F87ULL, 0x1A229A1D9D309243ULL
        },
        {
            0x967DC1410B55D05EULL, 0xDEAF3105144D0FECULL, 0xD3807A851C95EB4DULL, 0x70506E62D8DEA54BULL, 
            0x25A4EC82365D76A5ULL, 0xBCCA3A13F743BC90ULL, 0x43884C912C9836B1ULL, 0xA57140FF809100AEULL, 
            0xF2B36E6A6C0D0FF7ULL, 0xA87B07F6C559F80AULL, 0x10EA3E8E4EDBE96FULL, 0x67146E083F0519C7ULL, 
            0x8A4EB3A45CEC0F34ULL, 0xE68606B3ADA3147CULL, 0x2147E364CCDFB315ULL, 0x0106D15058DDFC45ULL, 
            0xE89D63BD9C107893ULL, 0x2E69847CE483B119ULL, 0x6331AC294B78B0CAULL, 0x7BC1EF1D2F72E833ULL, 
            0x06BCC3C3E2EDEF69ULL, 0x34D9E4ECCDACA562ULL, 0x8B247CDDEF7C26E6ULL, 0x921FCE503FFF9511ULL, 
            0x4DB9978DE873F868ULL, 0x835C5B1A86C78265ULL, 0xB941DA44B902748AULL, 0xD50573B398C9ADDBULL, 
            0xF558931252C67136ULL, 0x994B702070AACF7BULL, 0x2C4395932F79284FULL, 0x6E0BAC33D361CAE2ULL
        },
        {
            0xA78975688A958664ULL, 0x54FD824511AE0316ULL, 0x3ADFC82F1EC49385ULL, 0x40D17420702B0422ULL, 
            0xC578A187A391203BULL, 0x72EE737CF304D63CULL, 0xCDDD78C2FAF0FE5AULL, 0x068B0D0D2E62F8B0ULL, 
            0x7B31E48C678CD847ULL, 0x04033ECD0BE4535DULL, 0x162CB5B51EAA52C6ULL, 0x4BD1D8ECA224ADA6ULL, 
            0x8A8CCB800C77ADC1ULL, 0x373EC3DEE25B906FULL, 0x9C1134318FD9854FULL, 0x23F92F54C8513B11ULL, 
            0x638E9A11249BCD72ULL, 0x824C9219969A9161ULL, 0xDB5E9AD26AE1A575ULL, 0x19107825CFE9911AULL, 
            0xE182EE0379CB15ABULL, 0x3BCF1082103031E6ULL, 0x1623421E30274B83ULL, 0xBE8145F3B26F5A07ULL, 
            0xEF844D3C014F8943ULL, 0x8E99E2AC3D79B1E5ULL, 0x78BBEAA472F21651ULL, 0xFAE3225D55E9B6CCULL, 
            0x6E7BC0B245E5844BULL, 0xBBF0E738A4E121CEULL, 0x6443B12B5110CE79ULL, 0x1A0AAA3BAEBF9778ULL
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
            0xFA6019B6BA417915ULL, 0x11A1D75B21D00C55ULL, 0x30E157CD886202E0ULL, 0x64994E4562AE31ADULL, 
            0x445285AE537F619FULL, 0xA4F62AB037C7968CULL, 0xE523ABADC1BAE935ULL, 0x7BF0919ED5A7B0E7ULL, 
            0x4B1D553E4C256FFFULL, 0x4D38EB98B1ABCFF0ULL, 0x32C22A8C626F2FF2ULL, 0x7D47994F5886E2FFULL, 
            0x4C2334CC912E9C84ULL, 0x9B8A9638B7C598E9ULL, 0x00C5C789170F89D9ULL, 0x956D04E552C0B2E7ULL, 
            0x9E946F50754D37D1ULL, 0x53723B177F13B801ULL, 0x16BB9D71B1C95B64ULL, 0x8DEDAB81831CCBD0ULL, 
            0x8CF2C872AA96F729ULL, 0x82D8584E4C405686ULL, 0xA1C3FA0107731817ULL, 0x4E5BC18F37B43E72ULL, 
            0xCCE98C89425FF624ULL, 0x6BB55A6B69AFB95FULL, 0xAB22CEEF3D54E6EEULL, 0x50E18C813A3CCFA1ULL, 
            0xCFA4FA448F189F13ULL, 0x8B480F5E842BE76DULL, 0x5F5A3FB218CC2901ULL, 0x62FE78D80FA5A511ULL
        },
        {
            0xA0EA5E1BB28CBC0DULL, 0x8BF2B276BB79454BULL, 0xF2117E87AF5E802CULL, 0x10DB2A782906B357ULL, 
            0x063F7F860FB4E772ULL, 0xA211C69B06A54B74ULL, 0x68DDDDEEE82EB3F7ULL, 0x04BF019C66B9D897ULL, 
            0xFA3F4341E60B7856ULL, 0xEBDD878ACD746536ULL, 0x3EC7C2792293C180ULL, 0xDDA94889DF9EFE96ULL, 
            0x0C5DE7866D902834ULL, 0x900BB204F9C4A7D8ULL, 0x77CB66AAF4A4596FULL, 0x1C14125C647314D8ULL, 
            0xC6F89397546AD3A5ULL, 0x51600221470FC102ULL, 0x26C16E95171CB6BEULL, 0x2E67F0E07A017045ULL, 
            0x9F71DBFCB7423D16ULL, 0x26A86C73F33ACEE8ULL, 0x7B9EE95E01C9CD83ULL, 0x5F9C47A088509A5EULL, 
            0x87122A25C742EBD3ULL, 0xB7B5E8F22E1F59F7ULL, 0xBEF177DA0CB84C35ULL, 0x52197BBD12566599ULL, 
            0xC3733E075592DDF1ULL, 0x00B250A9B844D430ULL, 0x97B4A3D03F6BE0BDULL, 0xE5DBBFB8E95EA9DAULL
        },
        {
            0x9D9D7C4572B14F40ULL, 0x73B3B767E26323BEULL, 0xA758934FAC54E39AULL, 0x42ED6DF2B3FE8A25ULL, 
            0x40523AAD588C416BULL, 0xB09BA08F32A4F315ULL, 0x8E49C7C09934CF74ULL, 0x0C30ABE03EACBC00ULL, 
            0xDFF452FB2CAC2E9EULL, 0xE694E9A92C7A07E4ULL, 0x9C413B65AB302F0AULL, 0x42069A894E168345ULL, 
            0x7F854E5681D11AD2ULL, 0x48857211A3860A08ULL, 0x3A8C4FCCDC3594DBULL, 0x7C67CE5172D761D1ULL, 
            0x08048B18C6C831A0ULL, 0xC70C11A93B2FA908ULL, 0xFD8B2D2BA430F4ECULL, 0x32E3E59EF5E3D0E7ULL, 
            0x4235BCEBD624A880ULL, 0x7DEC200EA4826A5FULL, 0xE695DCE291E258C2ULL, 0x12C3E9F91F454AA6ULL, 
            0x7D64B55F3756356AULL, 0xB1B7E19B6FA1933DULL, 0x9515CDD595184D8DULL, 0x643660E7393DDF3FULL, 
            0xECF231F9BC972601ULL, 0xA92D1806A8616C17ULL, 0x2ABBE544E0496691ULL, 0xB64362955BD7DD2DULL
        },
        {
            0x23322BC65B3AF7E7ULL, 0x169BD7167328042CULL, 0x836E964DAADDBEBFULL, 0xA3CFF220E73921D9ULL, 
            0xB66510150DB468D4ULL, 0xB3289F7C0A724171ULL, 0x596BBBAA04238F82ULL, 0x1B4B56C0A7801DCBULL, 
            0xE9F0FC5849FAB54DULL, 0x07BD066AB836F59AULL, 0x7938B7454A13F553ULL, 0xA1660ADA652CFB81ULL, 
            0xB13E68A8137ECAC2ULL, 0x0ABD3F23FA830EACULL, 0x2CFD1EF6304ADCB0ULL, 0xA58DFBC6633BEE81ULL, 
            0x3D934DF04E9DA0C7ULL, 0x45DFE1BC9DD7E62FULL, 0xD7C2033200723612ULL, 0x59FA6AD4EA4DF06CULL, 
            0x1B11F94E28F2EB04ULL, 0xBA092579A9F5CD91ULL, 0x12624B4A90F67F39ULL, 0xAE8C5A03FD52828BULL, 
            0xD5B8013CDC5E4530ULL, 0x90FAB7FB5CD7D684ULL, 0xC613FAD181EF05CAULL, 0x04E6EE5DE4496C9DULL, 
            0xDC8A54033975C440ULL, 0xB370FA7BEF2A3153ULL, 0x2D61D1142D50C333ULL, 0xC1E6A544CC1AF538ULL
        },
        {
            0x16DA6F09238A9587ULL, 0x6EC55E19BAD33629ULL, 0xC4DB2536E9AA8603ULL, 0x5533B542DEC93572ULL, 
            0xD41FD505607F56FFULL, 0x0AD180C88C7449F1ULL, 0x3519108BE8D99CA7ULL, 0x0230D07766A85E21ULL, 
            0x53B8095E794E4B2CULL, 0x039B6248311BB8DDULL, 0x31BF9F8EAB313EF2ULL, 0xF205AC946CB0AB13ULL, 
            0x9F90C3699814FA71ULL, 0xC6341142AFBF88D3ULL, 0x94575B2FDA07EFA4ULL, 0x62D816FDF1DC73AFULL, 
            0x5939B27A0CF3DED9ULL, 0x96209F26A9B4CB66ULL, 0x2CE802223F36B427ULL, 0x0DAD6B6298939702ULL, 
            0x9379A80EAA7B56C7ULL, 0x86CC6A83C1425758ULL, 0x08CBB17A22E585D1ULL, 0x470E1F9952E95E62ULL, 
            0x7067DCD05F1184E7ULL, 0x42059C4386274B92ULL, 0xDF4248AD65D97BE6ULL, 0xE61C8DEEBE428C79ULL, 
            0x526B58DAB11D5326ULL, 0x0A917F1EEFFC6B01ULL, 0xEC20EC1AE40564E5ULL, 0x96F1AB49A525B836ULL
        }
    },
    {
        {
            0x3AB845BD52CB265DULL, 0x8A76F1E4B26646D6ULL, 0xF607948C589E1778ULL, 0x34396ABFEC677B70ULL, 
            0xD8EA66A15152F229ULL, 0x3A15DAA4454839DFULL, 0x23BF429A4724B3EFULL, 0xEE6420A31F812DD4ULL, 
            0xEDAD5AE3EA8246E2ULL, 0x6DB74B01188774D1ULL, 0x19979161252A0B19ULL, 0xEF775BF614E1C8E0ULL, 
            0x6D7B196EFCBD2518ULL, 0x2C82D6162D972D9CULL, 0xDABA68B348956E9CULL, 0xE81EA44B5B6B83E8ULL, 
            0xF51E44F40D8DDBBCULL, 0xA293AB21727B6427ULL, 0x7075F0D1CFF569F8ULL, 0xAE86CBCE3E30816CULL, 
            0xB8065B1EF88FC144ULL, 0x9CBFE0309FF7FE33ULL, 0xE06D43B9B9D933ACULL, 0x14C38AAB1FE24DC7ULL, 
            0xC7AE3D6236BC1CC5ULL, 0xC87EB24A28D4336AULL, 0x2698DE6DD5BD297EULL, 0xC5C13D0FB0813664ULL, 
            0x8B5A74690C195708ULL, 0x5677DB962DE2D3DBULL, 0x7A2965C194C0F61AULL, 0xCD0782CC772FD16BULL
        },
        {
            0x58D86FCC75AF2E57ULL, 0xD37B457BDF968200ULL, 0xA0F5E8C73C8D6D20ULL, 0xFF012C20C7D7D2A2ULL, 
            0xC53DE927B3C836D8ULL, 0x1691B03690B192BBULL, 0x47D0E1E5EDF489B5ULL, 0xD8A09560909E7E75ULL, 
            0x99DCE21FA6EB652EULL, 0x209584BF3E188B37ULL, 0x62C840B06385273AULL, 0xE96689F2AD1ED8A6ULL, 
            0x0457216811D8EE1FULL, 0x679EAE6A2D6C84A0ULL, 0x8935B82F34D58334ULL, 0x6253A5E0202F8424ULL, 
            0xD24E74DF955B217FULL, 0x97C78D67D7FC519BULL, 0xB1E26B8ACB0E7905ULL, 0xB218A1977AD47722ULL, 
            0x84C326A363808D85ULL, 0x732ED43CE10CF9A0ULL, 0xC2ED3BB144077C67ULL, 0x3E34E49FF3CEE6B6ULL, 
            0xEC6E3C1A5204010FULL, 0x20986F51DF33270DULL, 0x3E5DAFD669D7E878ULL, 0x6496BA1A7A20C5FCULL, 
            0xDA76DFB642A57669ULL, 0x1BF85CE991C7C5D4ULL, 0x45E94BB37C3BA5F6ULL, 0x73DB979777F4D22CULL
        },
        {
            0xA6124723E52C4EE6ULL, 0x05DD4CC4BCAA07F2ULL, 0x416DF0CDA43C5D9AULL, 0x5EF4E6F2E9BD9447ULL, 
            0x9F8FE3E8228114CAULL, 0xFF57293070A759A1ULL, 0x1202BC7F4EF57E57ULL, 0x81AB2C77DC0AB41AULL, 
            0x9B4658ACF01C67F6ULL, 0x958EBE82DF41A1DBULL, 0xACF93622BA2892CEULL, 0x393E85A85E0CFE3CULL, 
            0x213217A71280CE65ULL, 0xA90F206EB9C7E456ULL, 0xEEBB842135795B95ULL, 0x4CBF1FCD49F95221ULL, 
            0xE756D94621CE5334ULL, 0xEE50939D9D06DA86ULL, 0x16BE070AC9596093ULL, 0xE4FFEE227AF76C8DULL, 
            0x10D58AB113F4C9ECULL, 0x2E694220206D1B67ULL, 0x401CEE1CD41BEFBEULL, 0xC36F1EC5D60FEC2FULL, 
            0xBB8FF7D857209D1FULL, 0xF9BC60A732051896ULL, 0x8FD3A2893BDBEA82ULL, 0xC11E05CA52A9D810ULL, 
            0xE8D526CA72365B38ULL, 0x0E4F2CDF2A2650AAULL, 0xF522B8E57E6DCA99ULL, 0x16118446D4D82D3CULL
        },
        {
            0x74EEE7F214B45D76ULL, 0x832F977932CB7BA5ULL, 0x2EB698D7422C2B0EULL, 0x4F31966FC0C1030EULL, 
            0x244091B444DFEEB5ULL, 0x0D6AF429F2780782ULL, 0xAAE65FF3801B28A0ULL, 0x11D7ADB49ABB91F1ULL, 
            0xE6C7B812F4557798ULL, 0xA4FF759FE0CD1B45ULL, 0x99045A8F4BCDDCF9ULL, 0xE170DC5E37E9507CULL, 
            0x10F838CB3BDDC577ULL, 0x36D2313AD0A57AA0ULL, 0xD12BD6BE5EBD8273ULL, 0x59F6156F49AEE576ULL, 
            0xEFC8E01966F4DA5AULL, 0x7E712CCACE918D9DULL, 0x0E148D4FE2E841A9ULL, 0x1F6C4C5F0622DE80ULL, 
            0x3E5302C825EBDC08ULL, 0xCB1BD5F5E8164389ULL, 0x89EDC540CEF8FD0CULL, 0xECA456180C435A08ULL, 
            0x1B530A706F973759ULL, 0x185ED37AE1297AA1ULL, 0xEF9368BE3DFDC022ULL, 0xB8921265409FA85FULL, 
            0x974958F2DC2E2903ULL, 0x36C72A5F9A3E5B85ULL, 0x7BA67DA122159498ULL, 0xD0BAB5F351C1B3E6ULL
        },
        {
            0x719869661B00FAE2ULL, 0xC17D6E6C893CFDCBULL, 0xDCAA3C70ECA8789FULL, 0xBF416E302182C256ULL, 
            0x712DECF07AF8D490ULL, 0xE3C345827C4A8C70ULL, 0x1294D7D66C0384B6ULL, 0xFB63CEBC6FFB428CULL, 
            0x6A90FFAF8D215298ULL, 0xAF43E6FC7DF88753ULL, 0x63E3B9468CDD3C09ULL, 0xA32D442472613828ULL, 
            0xAFB0339FB3A62025ULL, 0x919C01C443904265ULL, 0xDCDD5BB77BDC19F8ULL, 0x1BED16EE273AF3BAULL, 
            0xC2658C228213E18CULL, 0xED68C16178CA4A28ULL, 0xC2466017930AE3FDULL, 0x960E2585FD0B1878ULL, 
            0x1485EC11D3A82877ULL, 0xAB76988F0656C978ULL, 0xBD3E0208216F095BULL, 0xF7513A1F26784EE0ULL, 
            0xD640E99EC9476D63ULL, 0xD123169831655A61ULL, 0x9D812E764B40F2E4ULL, 0x1053E4DE64D50A4CULL, 
            0x42C01192A6DA6C3EULL, 0x1465DF26F7F83D37ULL, 0xA03B52B250B1870AULL, 0x6BECC9AF478B7483ULL
        },
        {
            0x520DF052458F2455ULL, 0x85E2BDE61A936D66ULL, 0x87191CB7C3EF189EULL, 0xC4277803F9B8174BULL, 
            0x6C1F15876AB87EC9ULL, 0x231C3083CA6E807CULL, 0x7FD5548F6E675275ULL, 0x98293F59FD1794F3ULL, 
            0xA0A74BEA6B5088D8ULL, 0x18F919B89C64E308ULL, 0xF3F0090ED6C25BFDULL, 0x66D699CD3A448D4CULL, 
            0xA5EC295688A8624FULL, 0x95A6DBFB64E7E377ULL, 0xCE03203D99CB8718ULL, 0x86010C78D21F7EF0ULL, 
            0x6E28C67B7E6A8027ULL, 0xDF09D6353C10837DULL, 0x67D1EAF1EB5207C7ULL, 0x96C55ADE725B2BBDULL, 
            0x1FB3B676D4F1E68AULL, 0x164453E4412047F2ULL, 0x9440806FE0A084DEULL, 0xF4C89D93D51585B0ULL, 
            0x20F935FE31663B6BULL, 0x7F3594A07211966AULL, 0x734894021EE738DAULL, 0x234FDC62AF7E29CAULL, 
            0x13DD11D6C90BD839ULL, 0x8125C3A26C977768ULL, 0x78142577B40D2C5FULL, 0x363B45EAE408A824ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseEConstants = {
    0x846C6B1E3D6CA569ULL,
    0x187F2C96BFEB915EULL,
    0x84A678E22B07571BULL,
    0x846C6B1E3D6CA569ULL,
    0x187F2C96BFEB915EULL,
    0x84A678E22B07571BULL,
    0x8A3335D2DB0BAC7BULL,
    0xF02BEFD6313FCCC4ULL,
    0x10,
    0xE1,
    0xD8,
    0x9B,
    0x55,
    0x5E,
    0x1D,
    0xFB
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseFSalts = {
    {
        {
            0x78ED69C77141E757ULL, 0x5DCFB7095334D55FULL, 0x024DBAC7F2305148ULL, 0x53E668EA3FFA1633ULL, 
            0xD5CE96A9B9E7D005ULL, 0x6DBE3B383E01BD55ULL, 0xDB11FBA7F842542DULL, 0xE7F986C6A032EC58ULL, 
            0x4023825C1E4E096EULL, 0x49A2286CD71DA3F3ULL, 0x3B0F76DBB16970BCULL, 0x4DEF8CD99EF45521ULL, 
            0x89ADCA7788066AB1ULL, 0x22D9172AFFA0B3B1ULL, 0x84383D1216DDAA60ULL, 0x74E08F4DABC2D361ULL, 
            0xBCA95417741F23B8ULL, 0x12AE6106B931627CULL, 0x538C3786410AAA2AULL, 0x58A31619FBEAC86EULL, 
            0x5A12C5108E8B16CFULL, 0xDE34B4D06ED51EF6ULL, 0xE1049464376192C3ULL, 0x5A9EE1D0980AD654ULL, 
            0x1610CBE71BD769CEULL, 0x693FD2C35601CC2CULL, 0xC5ABD8C589BD340CULL, 0xC7C5B9CA7DF524F1ULL, 
            0x3BEF06C536F2D774ULL, 0xE321118A00E8F87EULL, 0x47148536899CF915ULL, 0xBC5996EED34FA07CULL
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
            0x6D15A9E3F1419974ULL, 0xFCF96A028CC47D33ULL, 0xB37E4C09511E9CBFULL, 0x570D14F835D74209ULL, 
            0x8F9A11FD952D63D7ULL, 0x95331528BE7DB9ECULL, 0x3336D9B2A1F80AAFULL, 0x9E3D1535E1168F01ULL, 
            0xE6DA1B95A4AF42D6ULL, 0xA10ACF2E4EFB7446ULL, 0xD35290D354DC75A9ULL, 0xED859AB4406F5F0BULL, 
            0xFB9ACA7196087E5CULL, 0x55B37C74C7709FD8ULL, 0x042BAA1741173189ULL, 0xAB4351B2131426A5ULL, 
            0xD12AC8F967B56A84ULL, 0x60F51E1BAACBE8E7ULL, 0x2182CE6B6920E9D2ULL, 0x64FB58C8938D74AFULL, 
            0xF1ED28E71B4E9193ULL, 0xD1ABAE2FAE756EDAULL, 0x34BD979544F28366ULL, 0x328F23F35AF32536ULL, 
            0x87794F6CE0DF3095ULL, 0x673096A6216E6870ULL, 0x6B44AE9AEAF5E8E8ULL, 0x8934070BA6DC2C78ULL, 
            0x588DD010A58931F2ULL, 0x3F47D8C89497AA34ULL, 0x1E1E3FF879F1AF87ULL, 0xBC06CDCA4A1F3477ULL
        },
        {
            0x4997A421906F086AULL, 0xF0836D6232D7F039ULL, 0x34BC6E62351D845AULL, 0xBFA0EC93C736D3B3ULL, 
            0x26B6A076D8D5EBE2ULL, 0xF27ACA896DB3546FULL, 0xE4C86812804F2D0AULL, 0xD99662D30DCC66E5ULL, 
            0xAD5CB91BFD048F8AULL, 0x52ED06E67C8EF038ULL, 0xABBF11F82AAFA72CULL, 0xC3CD102F64256585ULL, 
            0x307B4195455B550EULL, 0xDEEAE0EB2DECCC7EULL, 0x141E4F675144875BULL, 0x3C42B968C628FBB6ULL, 
            0x6C44440D27F90FBFULL, 0x6E97C19C052A99F2ULL, 0x6DD1D9CC494AB560ULL, 0xBF57955022450A6AULL, 
            0x3F51620E6A9196F4ULL, 0xC1813049E715FD8DULL, 0xBAF53083FBC2B229ULL, 0x28551E53374B6771ULL, 
            0x90EF12DC66E7914FULL, 0x90AD51BA5783D9C7ULL, 0xF8E2F0226CC1B8A3ULL, 0xA11A8CBEA879C584ULL, 
            0x6250D63E2D0285C7ULL, 0x7D61964CBE73952CULL, 0xB53D21D5D6091411ULL, 0x27B9A955E35FB3D3ULL
        },
        {
            0xDAD23D67E5D5EB8BULL, 0xAE3ECC31809FF9A3ULL, 0xA7DF1527FB972B2BULL, 0xC5F77A30C7E13E02ULL, 
            0x153F96793D03789BULL, 0xB89CF2DA00AE2A60ULL, 0x81FD29FCBF819757ULL, 0x50CA7355D9620A93ULL, 
            0x24AE5C4C7F904A8AULL, 0xD1B6D0DC1E67B7D3ULL, 0xB1A44FA0BF18F30DULL, 0x0402532326934938ULL, 
            0xF75FF170703301B6ULL, 0x009DDD88BD245161ULL, 0x0B0E712A26B6A5BFULL, 0x09F0342ED3C38C0AULL, 
            0xBC43270E7F2A5E42ULL, 0x0B1B063F501D8BC6ULL, 0x1C77C6B3B2A9689CULL, 0x3FA1E46E0781A338ULL, 
            0xCBB85C6083C69680ULL, 0x6604CE3BF44D4A8CULL, 0xE581A063E186C8DBULL, 0xB9B04DBAA313E49DULL, 
            0xE0FADAB589460C66ULL, 0xECBF541C6BC59430ULL, 0xB5A8B8A090C4CE38ULL, 0x6097DEC31C8BEFC6ULL, 
            0x2BED066C232CF891ULL, 0xA3F79E9BB4056948ULL, 0x53995936FC8CFC41ULL, 0x5DB3F639086919AAULL
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
        }
    },
    {
        {
            0x58B9FEFA933825DEULL, 0x61CF3B95CEF8ECFEULL, 0xA660F5B58D7D9920ULL, 0x07E76FCF45308B7EULL, 
            0x210F353CFA579372ULL, 0xD97976879B3AD420ULL, 0x68165902B90E81E3ULL, 0xCCCA18CB4FB322CBULL, 
            0xB53E0E17EF538330ULL, 0xACFB087FCDB572C1ULL, 0xA818607A4D4659AAULL, 0x8A24B15267872E5AULL, 
            0xC8BF15034410EA3CULL, 0x6B0531D3FE684E93ULL, 0x6D1524860A542A63ULL, 0x024F4130D2FCBC4AULL, 
            0x01E9EF9DA2B3A109ULL, 0x9313CB34B409288BULL, 0xE2D4ED888B7B711BULL, 0xECE735C00934BAB1ULL, 
            0xF3758548C58501C2ULL, 0x4F9811396C7EE2C6ULL, 0x8DAC5EE8479EEAB8ULL, 0x17EC0C52E29449C3ULL, 
            0x9BF4F1F3FEC1E17CULL, 0x100ED2F1CD4CC801ULL, 0x28FFE0C63F59A329ULL, 0x5AF4A6D8D0217529ULL, 
            0x743F6A0619385EF7ULL, 0x04150ACD46BFA90BULL, 0x2635842ED29A8EC6ULL, 0xF0F5BFAA9A39CEF1ULL
        },
        {
            0xDDE79DF2CAC49443ULL, 0x3A69DE65746117F5ULL, 0xC5AE562247A559ADULL, 0x72F169EA01A4031EULL, 
            0x24A95239FAAAD8FFULL, 0xD1A35ACB0CD2C660ULL, 0x2577CB5DC2A7ABD9ULL, 0x7E9281E46236A873ULL, 
            0xFBDF3AC0B0461619ULL, 0xA52ADC25E607914DULL, 0x1F93161035883D19ULL, 0x9092E4A686140877ULL, 
            0x0C0F3EA4B5E36996ULL, 0x9EFED22ADC2B7361ULL, 0x0AA544A55BB1CD7DULL, 0x618639991BDB4F2CULL, 
            0x5EC087D195FF25C6ULL, 0x489033EE7F514C3EULL, 0x3E907CF4B3DB90CAULL, 0x79DAD0E4F6974EDDULL, 
            0xCC44017405AA3E5EULL, 0x5494C3F27D2385DFULL, 0xC1B2E70EAFE3A35EULL, 0x6EB3AEC1940ADFD5ULL, 
            0x25EA5EB9491264E5ULL, 0xC20B14A640CEDF8CULL, 0xD2CB58419CB25D52ULL, 0xB07E1B48AD97A5A1ULL, 
            0xA740C937043FF91DULL, 0xC3A368E8C7693359ULL, 0x4688B0B7DD8FF5ADULL, 0x519F4922B559467DULL
        },
        {
            0xBF5BBA3BB4207D71ULL, 0x9419E8684743CE0AULL, 0x6197ACED310F7997ULL, 0x623B7FA5975A8185ULL, 
            0x9808E43EDB22107FULL, 0x515F371E1C783364ULL, 0xDE47E9CF0D121D10ULL, 0x1E964E8EF511A751ULL, 
            0x3EEDD4AEAABB8FDBULL, 0x12E9C0804ABD5A97ULL, 0x54F0B89A8AA17371ULL, 0xE01AC94C73B13265ULL, 
            0x2B2EB1F5709D79F9ULL, 0x2E10F99C28CDF3D3ULL, 0x5564663085A40361ULL, 0xD765A05EE91283ACULL, 
            0xE6864B96B38B8AFEULL, 0x21687BC86800AD15ULL, 0x577D8BB622C89DCEULL, 0x10B4E199A8683846ULL, 
            0x29A5A21B1565E2BDULL, 0x7D8952CFD7F19BDCULL, 0xBA5A2DFBA3FFB325ULL, 0xFB2DBDBA26FA2CC9ULL, 
            0xB7829AD7808CDF07ULL, 0x15CEB240DEE2389DULL, 0x5E8419725CCFBE0EULL, 0x89193C5CFEC5A7DDULL, 
            0xD5669EF1DF6BA3FFULL, 0xBF435D19EE756E9EULL, 0xAA4111B9590DA1A1ULL, 0xC16AACB88ACD356EULL
        },
        {
            0x746FD30356236100ULL, 0x360BA6201B8AD13BULL, 0xA06ECD2FB4A7B4F1ULL, 0x489DF626B7611C1AULL, 
            0x652640FFA680413FULL, 0x5BD6199C96794BC3ULL, 0x5EF96BC29B3ACC92ULL, 0xCC218EE3B4049802ULL, 
            0xEF341272CDC9AA27ULL, 0x12CC7282AFD3482FULL, 0x080C8C7B04CEC450ULL, 0x19F0E4380118E922ULL, 
            0x11F06FBD07AC5F89ULL, 0xFF1B41CE162AF679ULL, 0x7556FBF400A971BCULL, 0x99D27B5DEC41E48AULL, 
            0x0CE91B02535D55D4ULL, 0x97937CB562E539B6ULL, 0xE1ADAD3D137B48DBULL, 0x2C9D58E05098509AULL, 
            0xDAB3559E800B6B50ULL, 0x78154DC77D8F40EBULL, 0xBF6FBB93DAA46C87ULL, 0xBA55D67A819BAC72ULL, 
            0xDD706DDB3DE34F3EULL, 0x230CFC21D4D54C72ULL, 0x82A13DE6DA3C027DULL, 0x6A0DD9D0B658F972ULL, 
            0x1C9A36CD93EFABCFULL, 0x694899078110DD9CULL, 0xA14B6BD2EAB67A87ULL, 0xBA44D40ACC375021ULL
        },
        {
            0xD3BF142003FD977BULL, 0xAF12F36F65AFD318ULL, 0x6BCDA3605749DEFAULL, 0x895B546685A375BFULL, 
            0x665BBC309D9D3CA0ULL, 0xE8CF3D63C3C39748ULL, 0xD5742176F7A6C279ULL, 0xE9086261ACEA24D8ULL, 
            0x86EF1305E9A5D32AULL, 0xEDCDAD95E95A15CAULL, 0x628A655CBAD4AFE1ULL, 0x4B321CE0230740D4ULL, 
            0x2DA3E9EBD34CCF4AULL, 0x6764231C5799C9A3ULL, 0x96A16B4F14998174ULL, 0x7B8CEB9652AF636FULL, 
            0x0C497A345782EDBBULL, 0x1343F06147B0DFC4ULL, 0x5CEE9C4B2A314813ULL, 0x48D133356BA92299ULL, 
            0x34AC35F4280F4D74ULL, 0x44D9B8A49987F6D6ULL, 0x98B68481ADF772FFULL, 0xDA3011AB58B86BE0ULL, 
            0x41D31CE3156D71C6ULL, 0x0788E37A2D6A8102ULL, 0x3C5C2F4A08655015ULL, 0xDD310E5F13416BA1ULL, 
            0x1D8293C6AA3956E8ULL, 0x876F87A5B2F68132ULL, 0x81F9012DC5B740C4ULL, 0x0D47DA135FAD0D2BULL
        },
        {
            0xFC7B44784BACC21DULL, 0x4C88CC9864331166ULL, 0xC3000E7610F253D1ULL, 0x0CA188A180C9FD0DULL, 
            0xA6865DAAB3A49372ULL, 0x4B6022A712F28D5BULL, 0xD066F2EA03B3D5CCULL, 0x840C6F5D7A406D2AULL, 
            0xF7913A7957EA2A52ULL, 0xEBD155619FCB62DBULL, 0x4319C4212C5DA9C3ULL, 0xB25E5A152AD10844ULL, 
            0x38ED363DA9DA9E23ULL, 0x503F86DF0C1DCFC7ULL, 0x8612EE44F39F82C3ULL, 0xACBA5F1E3BA76CE1ULL, 
            0xB4757106313C1865ULL, 0xEE1BAAA3F037937EULL, 0x4C9E22B7490366DDULL, 0x8EFCAA762A69AC86ULL, 
            0x080ACADB32CB26BCULL, 0x02D27B3C89D1A3B1ULL, 0x179C2D2F3D3FD84BULL, 0x90A93AD82BD62CC4ULL, 
            0x81FB6807889AA94CULL, 0xF6FC5AA2A33F1792ULL, 0xDF9CCA90AED1CC45ULL, 0x10A21DEBBD456021ULL, 
            0x722D498106227807ULL, 0x17B93DBFDFAD78D7ULL, 0xF250D84D01EA4395ULL, 0xC65F707DA5B13CB6ULL
        }
    },
    {
        {
            0x553EEA8519E726ACULL, 0xF9A41160A8FF3CF8ULL, 0x717B5828866C8ECDULL, 0x4AD6B62286A086EFULL, 
            0x5DB31DE1BAB6FB20ULL, 0x355F688E8DAD3957ULL, 0xB432F2EB9150E297ULL, 0xD9E39B1E82832161ULL, 
            0xA3E456E8A71629F5ULL, 0x4C57139490847C27ULL, 0x2D6BAA39AB76A779ULL, 0x4DF2F8AC316EE059ULL, 
            0x4710DF44DAF51302ULL, 0xB0CE07EE0AA2E2A4ULL, 0xE7B94373DEE590AFULL, 0xE29535DB43FFB3D6ULL, 
            0x082EF32B8E9B52E9ULL, 0xB5ACFB3AA803159EULL, 0x1AD75600DF598137ULL, 0x972D2568BB0F9813ULL, 
            0x7DCDE2BCEEE38643ULL, 0xBBE6106F469E8F81ULL, 0x9BFE331F8DE29870ULL, 0x1819B4E840B4B5C0ULL, 
            0x9814C10FC7DFDB16ULL, 0xA6C9025640EFA10DULL, 0x6E96BD49D2CB8FF2ULL, 0x7E47D8F1178AADB1ULL, 
            0x2698CBB1622ACB2BULL, 0xC3B8F51695CA59B4ULL, 0x2116A99B8B4B8E1BULL, 0x157FE888CF85E090ULL
        },
        {
            0xC19DF32EF47F4D23ULL, 0x54B57BD749175E27ULL, 0x2B50BE85E9A0B500ULL, 0x2ABA1A2099CF9675ULL, 
            0x5EDC64732FEAB805ULL, 0xA08BBA08A861E1EDULL, 0x6FC6454E0313BD2DULL, 0xBFD71992BC64E325ULL, 
            0xA4D356A635F7840DULL, 0x332B979DC789D530ULL, 0xFB46C8A1621A8099ULL, 0x255E3D40D648F3F7ULL, 
            0x04A299DFA477AFC3ULL, 0xD139C42622B8CC25ULL, 0x3F9C0DDF503DCCB0ULL, 0xA35971006696D3E2ULL, 
            0x2D02FF624E89EEB4ULL, 0xBBC2A2ADA35F2C03ULL, 0xF6394CC339B49F7EULL, 0x69D52BD62A11AEA0ULL, 
            0x5396F4CF271027B8ULL, 0x8C9190E6545FC308ULL, 0x194A2598C74428D4ULL, 0x6B38DB3B77F1BF0FULL, 
            0x4BBAD0214B0CBE3FULL, 0x306ED7BEBC3E8D3EULL, 0xE144AF3DA2EC53E9ULL, 0x846B0722251557C6ULL, 
            0x920EBFA03E4325BFULL, 0x1FF9BC39E35F668EULL, 0x885F36FDC08214B2ULL, 0xF414B62067313C32ULL
        },
        {
            0x45D6CC538DDCD453ULL, 0x522F864B8589CF2EULL, 0x56568FE6604DA6E9ULL, 0x352B7B0C43BE96AEULL, 
            0x56ADB7E85533908DULL, 0xC60AA64782F2B8D2ULL, 0xDA406D3F142D20FEULL, 0xDF6279DC0CF500E6ULL, 
            0x56977063B12C8EF0ULL, 0xB0E5B48E1483EA7DULL, 0xAF5F23193F70A048ULL, 0x405B63FA5DFF0569ULL, 
            0x106A4390ED7EE8B2ULL, 0xF3D4E685E7D0A164ULL, 0x2BD272A8287A19EBULL, 0x7E58F2D049508B3AULL, 
            0x103C5965C3AA0B97ULL, 0xD7C91B04CC776045ULL, 0x921ABD7629075C1EULL, 0x860629F007F46EEFULL, 
            0xA25D364AE66CB3B9ULL, 0xE11ED40C2F238E5DULL, 0x1958D8A5AD6FBBADULL, 0xEEFE6BE4BEC8D9F3ULL, 
            0xC0E31CF7F9268690ULL, 0x0E62590208C9DD85ULL, 0x97B45753C98D76B3ULL, 0x6792A8FAEFC2B53AULL, 
            0x7FF94F0F621FB8C0ULL, 0xD48548541F5EF988ULL, 0x06A9EEF63D5E3678ULL, 0x7ACEA15676F7B03FULL
        },
        {
            0x187255EA708CA10CULL, 0x5E83DD76B4047E33ULL, 0x3CD5556DFF644FACULL, 0x394DED199F99B185ULL, 
            0xABF7C196341AC608ULL, 0x38A0B54044D30A7DULL, 0x48CD83122D42C44EULL, 0x01815D04064AA789ULL, 
            0xAE6FCB0990CFD91BULL, 0xA4D0C5BFD2000C57ULL, 0x9690210ECFE1B6D7ULL, 0x63AE44F280053B58ULL, 
            0x126E643265914E1EULL, 0xB9E3A0C1B841E0EBULL, 0x9EBAB964800FE4F3ULL, 0xEA8732BE4819550AULL, 
            0x29527972B3B87A27ULL, 0x5EE260DE12784419ULL, 0x7280CFAB57601B1BULL, 0xB0B09016645ED1F5ULL, 
            0x50E9FF7593C4109BULL, 0xE78B4558AEC27528ULL, 0xA51D44AB0EBD4D01ULL, 0xA1654FC78DB57238ULL, 
            0x8343AC1ABBDA13FAULL, 0x6156E9F28B81E23BULL, 0x00D9BDBA5E53BD29ULL, 0xDAC4C1BDC68D48A9ULL, 
            0x4E0E78AD021AB4BAULL, 0x07A721830B20D0D0ULL, 0x89158A3A4338423BULL, 0x833D6C8EBB184FADULL
        },
        {
            0x03B49A81F1308600ULL, 0x7BD435ADE738B61BULL, 0x51CFD5B2012B996CULL, 0xE0C99552F7F9313CULL, 
            0x03B283E4DFF92695ULL, 0xEA86F1A8DF4B9EC5ULL, 0xD3D929702D184E23ULL, 0x42EECEDE6DBA1C99ULL, 
            0xE57D00CDB607D789ULL, 0x88DD52641EF266D8ULL, 0x66781C3E3F1A7167ULL, 0x10B11EBA74A614E2ULL, 
            0x17B5517E3FB15018ULL, 0x8B9B84329938F32DULL, 0x77BFAA8D89D4FBB7ULL, 0x1BEB32D528006C71ULL, 
            0x32F65203BC800316ULL, 0x697F93DB8DA9744BULL, 0xA542AA83FCE0D2C8ULL, 0x5ADE73F058C348C6ULL, 
            0xE4AA07E3773A5061ULL, 0xBC3A172DC92A96BDULL, 0x0FF07A5E7F3A72BFULL, 0xEECEB0897A026A0DULL, 
            0xD72176D8ADC07B08ULL, 0x4103A2EFBB376079ULL, 0x179757D5E6C1E0D1ULL, 0xBFE16632668C7C19ULL, 
            0xCEAFE187D15CAF4AULL, 0x6F3CB9ADF295240BULL, 0x078ECE5A3C228963ULL, 0x28527369F47C022CULL
        },
        {
            0x91BA9AB881282C30ULL, 0x4B80664ABEA1F746ULL, 0xBB365E840E9F0DF6ULL, 0x60655813E014B9C3ULL, 
            0x6AF717B8DB4002E5ULL, 0xFDF15C792637BB6AULL, 0x1AE3C1DE3CF90C20ULL, 0x080F9CCE3AFD8F0CULL, 
            0x404B2F15793961CCULL, 0x90C3828C11B79A09ULL, 0x4D4083D50B8C3502ULL, 0x40625345B3644C12ULL, 
            0x8CA9D1FE5FC0187DULL, 0xB0D10B49991C7EF2ULL, 0x130DA598B271FE40ULL, 0xA34894D358B6F4EFULL, 
            0xDDD0DA7375535F2BULL, 0x58DCD6C0DC1E1FEFULL, 0x0E0E7208B8B404F6ULL, 0xF5FECB730344DE7EULL, 
            0xDF4543647108CC52ULL, 0xF242F3B04B896363ULL, 0xDA3BA459B9EF9144ULL, 0x3214FAB263E07E12ULL, 
            0xBF500D30448A2F44ULL, 0x7DFE39AD4497BB2AULL, 0x5391BA1B235FF1ECULL, 0xC0057217992AA781ULL, 
            0x119CD3B6F4C775CBULL, 0x8A2E52BDA26DC9B9ULL, 0xA05489A14F2823C3ULL, 0xA033BC661F80BA1CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseFConstants = {
    0xB809C452C0BF2096ULL,
    0xD52D5CB867DEC448ULL,
    0xF732279566BCEB5FULL,
    0xB809C452C0BF2096ULL,
    0xD52D5CB867DEC448ULL,
    0xF732279566BCEB5FULL,
    0xAFBEC869C54B7741ULL,
    0x7FE319FAA6F7A9CDULL,
    0xB4,
    0xA8,
    0x36,
    0xBD,
    0x0F,
    0x65,
    0x03,
    0xA3
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseGSalts = {
    {
        {
            0x33017C30BEAD8D41ULL, 0x5AAD98B4146F9B3CULL, 0x67682600D60526F0ULL, 0x77E359327D7BCCEEULL, 
            0x1D66E03A775152E8ULL, 0x256B1709496D511CULL, 0xF4865E3A44D72CD9ULL, 0x0A6F63792B73E89EULL, 
            0x2262A56A574FC61AULL, 0xBBC16925DB5161BEULL, 0x7F5A51A71283565BULL, 0xE5A6B54FAC4BCFA1ULL, 
            0x0520084C881A40D3ULL, 0x4EBB9BA2B85CE327ULL, 0x9EBC70A69B263198ULL, 0x53E7D1BC7CBE860EULL, 
            0xEB3F6D3CB2EA7267ULL, 0xE98838286B62AE90ULL, 0x975D6ADA7CAFE8F5ULL, 0x30D1FF851554A21BULL, 
            0x88BDEC1CF04752F4ULL, 0x150BA05FAB5DA8B6ULL, 0xAE9B2D368749D165ULL, 0x9713E297C05103FCULL, 
            0xDD46706D37D11B0BULL, 0xB9F6A2BEFFE5FB93ULL, 0x3AD8BD0E234E3F3FULL, 0x503974A667EDE51BULL, 
            0xEA12CDA753D69371ULL, 0x138DD8DBF7940CBEULL, 0x8E6F59977A40D66BULL, 0x637216284C386CEEULL
        },
        {
            0x3972A96EA9908FF2ULL, 0xC5DCD84021ED8CB4ULL, 0xB6D67D0F3264F39EULL, 0x7F5FD574237E46D0ULL, 
            0x5A45725E7F646C51ULL, 0x59E1AA00CDAF76B1ULL, 0xB52B00739EDFD595ULL, 0x96F15BC02A3E1235ULL, 
            0x58780D2CE17EBC7CULL, 0x9F1045B05107AFD5ULL, 0x883E293BC60AA729ULL, 0xEB4C98904E9701A2ULL, 
            0x23FBBC372EF96677ULL, 0x6A00135EA8B0C840ULL, 0x4B99723C75EDCA66ULL, 0xBA6324C1312C24E9ULL, 
            0xDCEF6AF53573307FULL, 0xFC471AE1779216A4ULL, 0x42AFC669C91A976AULL, 0x245106D4488DBD08ULL, 
            0x64B3013F27391FE3ULL, 0x0764E89282AF0784ULL, 0xCF7BAD0744DB4C67ULL, 0x3296333781A7B866ULL, 
            0xE4ADDD3DD2BFFAACULL, 0xE17A3864132E11CFULL, 0x563485A3C6A15CDCULL, 0x99BD82E91B9217DFULL, 
            0x83CD814597A4D1D4ULL, 0x1D24EE036041F805ULL, 0xB647181BC7020892ULL, 0xAAA99B6AE8E30B98ULL
        },
        {
            0xEE18315ECE5F9510ULL, 0x0267B4D1FDBAFD16ULL, 0x42703709BFE5BEFFULL, 0x886C1FA68530C896ULL, 
            0x047581E1164320DDULL, 0x5B2C64C328046AB9ULL, 0x42567B1E0900C81FULL, 0xF8487B8EA24D5F61ULL, 
            0x198480B11DEDDD22ULL, 0x4296A2B9A132FEB5ULL, 0xF154C9013FA112CCULL, 0x5D242014D704746BULL, 
            0xB50831C7B07A8B85ULL, 0x181EB88E549673DFULL, 0xA4B24EBE892F1FDDULL, 0x4BE50A7A96EDBF17ULL, 
            0xB888C36F520BC560ULL, 0xD9FC817D31F39BB8ULL, 0x3817344EFCE65B8CULL, 0xD16D139A6F2AE581ULL, 
            0x6F2CAE8599E22FF0ULL, 0xB70FDC595A80DC49ULL, 0xACDEADC03255CD03ULL, 0xF85F0E75F93B523BULL, 
            0x51E364BCD1212EC7ULL, 0x8CC3B6A9EA32EAB0ULL, 0x799E60A9E3559006ULL, 0x45157AC9EA1F036CULL, 
            0x4AD874BCD5F3EA0DULL, 0x3BA0EE0295C2C82BULL, 0x016E8048E3041F3AULL, 0x6EF7DBBC248D5F21ULL
        },
        {
            0x77BF7FCC0C44BAFDULL, 0xB84B0FC0E37063FFULL, 0x81D2A2A909F6D503ULL, 0xCD240CA786B1F4BEULL, 
            0x6CC245E7EDCD7CC5ULL, 0xA6219D313E9444C4ULL, 0x174F903B545038B2ULL, 0x81DDDC4BCB1DB271ULL, 
            0xD967E60594A29B4BULL, 0x2C6BD9E70FEE815CULL, 0xF386863E44736B70ULL, 0x41E5AFE4F3559A03ULL, 
            0x47EEA476D3D77B7AULL, 0xB004B8BBED0B2468ULL, 0x2D4F50B0A8A3AADBULL, 0x2C7C0458181518F7ULL, 
            0x6D8A6CA0D857D1D2ULL, 0x870134EB130612BCULL, 0x7ABCC2437D8A8BF9ULL, 0x62E4CEC6CD2613DAULL, 
            0x36461BA7E01E377AULL, 0x72305518D39C5602ULL, 0x1466CBFBFC6B9A4CULL, 0xF1F79CE506EA21A4ULL, 
            0x163301B460DD829FULL, 0xBE36648A2F7E4E28ULL, 0xB88E3C36711003CAULL, 0x838DA49337978BD4ULL, 
            0x5B8F55B992C5EF15ULL, 0x41AF4EAA430EA48DULL, 0x24F722B197199373ULL, 0x460F131E0390AF28ULL
        },
        {
            0x04D0B785ED65D7B4ULL, 0x2D8E1C25D62F8601ULL, 0xA8420239D0BEC442ULL, 0x4F6EF0DDC3A1DCE8ULL, 
            0x881C2932DA275F07ULL, 0x28B47028995B4342ULL, 0x793E6DF534B97DB1ULL, 0x48EEF123FDE629C1ULL, 
            0xF15A573338EA4246ULL, 0xED331EE3C173ED9DULL, 0xFB6378E873936D26ULL, 0x347634980A508CE1ULL, 
            0xDD8BE15E5B8F4C44ULL, 0x7B8367971FB4F3E6ULL, 0x811145452A39E5FFULL, 0x56BFFABC40DF7717ULL, 
            0xE066B82052EB064EULL, 0x1BC37BF8277F3CA4ULL, 0xB7D08DFD11C3C04EULL, 0xB04110421995B6C2ULL, 
            0x097D85102BA34AA0ULL, 0x7CB2C769341E8699ULL, 0x01B758DFDE6B9FAEULL, 0x2CB9822CE8E6B22AULL, 
            0x747611E96C32CCF5ULL, 0x435720A2A8867B4BULL, 0x41BF682BB6B476DDULL, 0x81BEA769E077DB40ULL, 
            0xFD517D6544A63DBBULL, 0xF9626393325728F3ULL, 0x30315B449C1B7A00ULL, 0xF32A832DF6561C62ULL
        },
        {
            0x2690EA4B8BA2E8C8ULL, 0x6F9A9CF3494787EAULL, 0x7DC79CAEE26C5CEAULL, 0xE2697FA6136634E9ULL, 
            0x931B69DFEF54E1B0ULL, 0xE9D2AB11FBC2D5C2ULL, 0xD86A05D46D253845ULL, 0xC0DD920E0CE51C75ULL, 
            0xC3DF012CCC6DB81DULL, 0x4C3F1844B73B171CULL, 0xCBC7943D1728F722ULL, 0xA9F4ABF3713CC2BBULL, 
            0x4387BC0A0A041718ULL, 0xD3A14EEF45498051ULL, 0x95FDF2D55680ECE3ULL, 0xA9FDDC0B6392F984ULL, 
            0xD146F9E2504F87ADULL, 0x24BE8502B9322D9CULL, 0xD5D10248563221CDULL, 0x4E71709C9388AE5BULL, 
            0x6DF3CD3F78FFEE0DULL, 0xAB27A754AC387B89ULL, 0x0A54865AD4A03CA2ULL, 0x9E83186C808439ABULL, 
            0xF834224DFC81DA3DULL, 0x7BEDD41E4131348DULL, 0xDAD771890FA22773ULL, 0xB71C507F9D8A0A17ULL, 
            0x5F399C297DEEA09BULL, 0xD07E2B1BEF624123ULL, 0xD44E78F73BF99272ULL, 0x19B27B1F1073AEEEULL
        }
    },
    {
        {
            0xE6E074CE94E5733BULL, 0xB19061EA1F36A830ULL, 0x2C159A826B06F5C8ULL, 0x30B44D752DB414AEULL, 
            0x0D6532A08AF8C84EULL, 0x90ED7BCC045DE126ULL, 0x2E1A86FE7186B7CEULL, 0x70F81DDA85F8EBC1ULL, 
            0xB97267DC5A101975ULL, 0x750661063174FEC7ULL, 0xBDDF73C740D93761ULL, 0x681A3883E4178B14ULL, 
            0x9E305006D7F44F70ULL, 0x0DE785D311420FC5ULL, 0x958A528156C63F44ULL, 0xA02F5BBDEAC33787ULL, 
            0x7017B74D65A696B9ULL, 0x11A4C04F8E0A41E7ULL, 0x371B4B1D290037AFULL, 0x04D8191A2EA19DE7ULL, 
            0x1917913B689F83D4ULL, 0x808AC7BBD3948627ULL, 0xCFFC0B50464F5486ULL, 0x1A0489F03E5F8A44ULL, 
            0xA99CB5BD823676EDULL, 0xEA5E7C7A92E1716CULL, 0xC70A091B7466BC27ULL, 0xD8D5EE5B5913917AULL, 
            0xAECEF66C68EEEBC0ULL, 0xCC0B1B5589921B96ULL, 0xC95A53E50C99741EULL, 0xAB6ED51B9BB27F10ULL
        },
        {
            0x776BCAF98E598912ULL, 0xAB1600CBCA09C2C5ULL, 0xF92979AD610FEEF8ULL, 0xF8FC1E44B6069CBFULL, 
            0x80B348310D71E1ECULL, 0x137C70AFAF39B1EDULL, 0xF1AFA8901A0B6C2EULL, 0x5D7E50911053C1A2ULL, 
            0x540EF65346866D9BULL, 0x919949EB2E3101A4ULL, 0x5BA3CBB9051D1889ULL, 0x229AC3FEC464532CULL, 
            0x3CCCE16C91438262ULL, 0xF62B2804DDEC58A5ULL, 0xD9BB92954FD6D335ULL, 0x6938DFF1804A9374ULL, 
            0x006099BD1C9B3FC1ULL, 0xBBEFF2957C6B4B0FULL, 0x7C7D308461F63F83ULL, 0x2E14549A70946DA7ULL, 
            0xC2AA0836177D26EFULL, 0xC744AE7785AFF845ULL, 0xE2056295683BCCB9ULL, 0x7255EBF331C30E2AULL, 
            0xACC13314A5763753ULL, 0x89951910D99DFA6BULL, 0x879BCC465120ED61ULL, 0x387CE7BA147EB20EULL, 
            0xFAAEC61E94C9E46CULL, 0xCF2125C8C8B2197AULL, 0xE360B50CAE8F5B10ULL, 0xA3043D4F13F3A4FCULL
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
        },
        {
            0xFC94CAFD51FE2ED0ULL, 0xD10BE6D8DA40A0B2ULL, 0x3D15FAB0FB189DD2ULL, 0x8D58D3B7B46ED283ULL, 
            0xBF98F88833504944ULL, 0xEA948EE7549CFA4EULL, 0x543551E9386AA920ULL, 0x21B9DAA320727DCDULL, 
            0xFD68EB8364F70551ULL, 0x4A0E70328267F3CCULL, 0x338DDF7A8F14274BULL, 0xCE33E2EDF7011F3DULL, 
            0x1420701E3A948D7DULL, 0x6A13263726C8E5A2ULL, 0x88FC69120F852D8AULL, 0xE8CAD87BFCCCD43CULL, 
            0xC01081DCF4571BEAULL, 0x1DC1EB2D690C93A6ULL, 0x34A547C328DBC842ULL, 0x32A61DAB7C6C76BCULL, 
            0x22591D78555C71F0ULL, 0x8021486EF4C8110FULL, 0x5F51EF2E60EE26F4ULL, 0xC8FFEC07622C55A0ULL, 
            0x5321174E616EFA70ULL, 0xE4FF452B54DD855AULL, 0x233427DA89AD4B3CULL, 0x73503209BDDAFB17ULL, 
            0xF5C08CB69A9281B2ULL, 0xC5417836DF7043B1ULL, 0x5F0F74F385DB1390ULL, 0x3C0438BF5F59972AULL
        },
        {
            0x8CF3DBBDE14CB378ULL, 0x04B2F7EFD5B4F13EULL, 0x3533B724FD261227ULL, 0xD8DB5B3BFB70D578ULL, 
            0xCE826B49629E7DFFULL, 0xA8588EA09382F472ULL, 0xA03E0DE3455CC981ULL, 0x9A4F9D908BA7DA49ULL, 
            0x1062DBE8DBF0CFEAULL, 0x0004509B65CBB299ULL, 0xC1E5A4E6E7E5ED6EULL, 0xD93C0103DA74B92FULL, 
            0x649ABDF24EB2F381ULL, 0xDEF16F151F567241ULL, 0xC901E5504D69488EULL, 0x42E28D6E4D3AE609ULL, 
            0xB64DCFCCAEA06178ULL, 0xD56877A9FC5C5C98ULL, 0x7BD1752D4A6B13B3ULL, 0xD1B2E34BD7AB4B2EULL, 
            0x3B0E73B11DC59765ULL, 0xA679DF1250447002ULL, 0x10FD153BB8DC9775ULL, 0x5C37B1C1157091EBULL, 
            0x3589667A5FC17251ULL, 0xA76314C388B01333ULL, 0xE832A517E50326FCULL, 0xC17C5B18298E2C48ULL, 
            0x1206754F85ED479FULL, 0x08D1022EB161C51FULL, 0x104DBE08A7AEA3C2ULL, 0x2FD73211350BA2DBULL
        },
        {
            0x46D8BE028D61868CULL, 0x1B680A1019EB8EB8ULL, 0xEE5882A4E9946EB7ULL, 0xF0A50ECE0C032336ULL, 
            0x73CB4906A8BC305CULL, 0xBB5C25B9FDE8BA32ULL, 0x90A1A10C99086656ULL, 0x1FEA9F2583A96DD7ULL, 
            0x294E7519B4124250ULL, 0xF4F5642D54BC5124ULL, 0xCCF3BF4667FD346AULL, 0x05AB4E280642E910ULL, 
            0x334E45D84D188813ULL, 0x8D5B14ADE970029EULL, 0xDB8CBCE2A11A3E3FULL, 0xD034B29D6E97FC0AULL, 
            0x6503F22A7B30C249ULL, 0x2B52A1ADF69FBAB9ULL, 0x70A68C9640E123CDULL, 0x160ED1AA775871F0ULL, 
            0xE224850DDF3B39DFULL, 0x6C13216BE68C8FEAULL, 0x1FD37D8F19F3B9D1ULL, 0x1B4E3A8E6D376C6CULL, 
            0xB25777A722B90154ULL, 0xAF6C9317E96752D6ULL, 0xC5CC230ECADAB44CULL, 0xD2D1FDC73C84D337ULL, 
            0x2911A2961B139585ULL, 0x1B4DBFF3C9B17D14ULL, 0xF275C9B7498167EDULL, 0x8B5B0918F4CD40FFULL
        }
    },
    {
        {
            0x2956683499E6B304ULL, 0x77D494811BD1FA5BULL, 0xD99BAB99B59B349DULL, 0x391235BD115F2239ULL, 
            0x724E65313A5B225FULL, 0xB197096836AE92C6ULL, 0xAD7E4A9DFD60DABAULL, 0x723756F8D6F8AD3DULL, 
            0x9D949277E998F9CBULL, 0x57362CEE7F36824DULL, 0xB62E5617E2ECD70EULL, 0x92C560B22A1E3F53ULL, 
            0xE719725FBC2C8797ULL, 0x66D4D4AA8BFBF08BULL, 0x5D53F5B31190D2FFULL, 0x225135E519135569ULL, 
            0x97D7BC3FD4DF6210ULL, 0x38BD47C18CD08C61ULL, 0x43C82C504E6DFF57ULL, 0xEE123DDEFB0A5F7FULL, 
            0xDF5D4DE1E4592A14ULL, 0xBBFEB0554F85A357ULL, 0xA0FA947460C08574ULL, 0xA51B09682900A93BULL, 
            0xF2C854B20E79B667ULL, 0x0FC0CE6D59961BEFULL, 0xD04BD54FEAF4F11DULL, 0xAA85BC6E5D4FE2DBULL, 
            0xE3960BB5A21C47C8ULL, 0x14F253CCB70CF2C8ULL, 0x92CBCD8ECFDEFB52ULL, 0x57E8F172037951F7ULL
        },
        {
            0x709891407902F821ULL, 0x457BEF12090032C8ULL, 0x8E00B32BDAF190C1ULL, 0x36309C0641545D8AULL, 
            0xCBF0622F03A40F07ULL, 0xB3F7B054454DC17CULL, 0xFC55420FB18B82B2ULL, 0xC43F697E95B38528ULL, 
            0x8D1FB54EB2DCC6C7ULL, 0x4C0728688ADDB4E2ULL, 0x07678CE983959B24ULL, 0x6033E9534AA10676ULL, 
            0x073AE19E14003EB9ULL, 0xD339891A76B3886AULL, 0x31E8B69C2EA76669ULL, 0x416A997CE822CF38ULL, 
            0x22E85EA820C94A4BULL, 0x9B2B348214591808ULL, 0xF4DC0EB5CEA7EA85ULL, 0xAEF8A2EF3B8F6869ULL, 
            0x3A1CC8C2932083AEULL, 0x95B253B86AE16B61ULL, 0x963C2A4E645F1F7AULL, 0xF715051DC82F1A26ULL, 
            0x5A0234B92B459364ULL, 0x75AF5AF8C3F9B2D3ULL, 0x2242BCD419D7EED6ULL, 0x503E1F6653650983ULL, 
            0xBF7F1CEFDB1E15FFULL, 0xCC964B0F97F14B0EULL, 0xEEC0A3F1F18CB463ULL, 0x479767B72A8F0F35ULL
        },
        {
            0xD7AC37F4893B0418ULL, 0x8761D8C6C4ED4474ULL, 0x5C5B819B864ADBFFULL, 0xD213145D6B0B81CAULL, 
            0xB31CE945FC710540ULL, 0xD1B9846B69F651EBULL, 0xB8405F48A4A78E48ULL, 0x8FF0D4C1E9B40C52ULL, 
            0x4C4565AC1EF9FDE6ULL, 0x15981251503D819DULL, 0x96B431520C56A5EAULL, 0x0EF618B423C18EE1ULL, 
            0x2BF965747DE13243ULL, 0xC181B08F79B71741ULL, 0x69D9ABC40E4E9CB3ULL, 0xA00BEA61D82157D0ULL, 
            0xBF4270F2509A2606ULL, 0x0EE091617A70F4BAULL, 0xFEBC769BB6CA3D4FULL, 0x34DC225FA264FE76ULL, 
            0x584E527E6AC88207ULL, 0xF9ED41A7A46BFF5AULL, 0xC3E3F01F69AFD880ULL, 0xC5B58977098E00B7ULL, 
            0x3CD2BE7C4FEE38E7ULL, 0x674752ECEAED05BBULL, 0xE8796B55711ECA98ULL, 0x8A017A26AA7355A5ULL, 
            0xACC1FDC555168402ULL, 0x75B5C4625D893C53ULL, 0x2762334BEFD870C2ULL, 0x02FB6EEEAD34C2F7ULL
        },
        {
            0x20D74C92C1102A32ULL, 0xF3059F61D384A0AEULL, 0x70A017DEA832E804ULL, 0x09CC00066A53B3F8ULL, 
            0x987490858E2455F0ULL, 0xE4F05DDD7F766C6DULL, 0x1DCFE6BEA8F42F11ULL, 0x7597DF82443A9960ULL, 
            0xB9997D7AB2651783ULL, 0x361625BF4D7C2FA5ULL, 0xE48C28CA09BE243DULL, 0x71695725187588FCULL, 
            0x5D7AD6A1F4CC5F2FULL, 0xA8ADB5FAB688D7C3ULL, 0x6A5FE8FD24E70B1AULL, 0xEE3BBABEDD19BF83ULL, 
            0x02350562E6FDAF2EULL, 0x10C0CA4A1BB8092BULL, 0xDF86B6BDFAF4FD25ULL, 0x5CE134EEC8FF757FULL, 
            0x131B5438E05189A1ULL, 0x692F5128D9F50890ULL, 0x648CEBDF07BBD322ULL, 0x3D3F6BC94041C906ULL, 
            0x13C52419FE90FCFFULL, 0x704805055E9D5B7FULL, 0x12F3BF4B4EEE99AFULL, 0x20DCC35C7E12E3C8ULL, 
            0x4492F17AF3196633ULL, 0x7C0FEAEDAAE6C308ULL, 0x36F2658E9366C1CDULL, 0x5215BCC36297713FULL
        },
        {
            0xE86CAF8958E6F607ULL, 0x251E9433D941787BULL, 0xC4905A87E8B1F0ABULL, 0x7AB3FFA970F60462ULL, 
            0xEB7011D758045086ULL, 0x3B85A55A300C9CDBULL, 0xBD127E91595F24D3ULL, 0xB59276470071D8EEULL, 
            0xE8795BB7A7F0F08DULL, 0x48B152AE9890460DULL, 0xB24EFC88E46CAE97ULL, 0x43B0335EB551C2C6ULL, 
            0xA2194B1850894399ULL, 0x1A30B7AAAF3DA8A9ULL, 0x164F662BAE90F4AEULL, 0xC41BAB997519327FULL, 
            0x73FAEBD23AA97952ULL, 0xFA95361927317F7CULL, 0x7CA1A25DA658AC62ULL, 0x67D4F9DBA5A202F3ULL, 
            0xC16D1758BF1259E5ULL, 0xAB8BEE6B4FEB7C9AULL, 0x2E82C44540B45F2EULL, 0x05322DD0AFE4617CULL, 
            0xAF38D184D722FED9ULL, 0x0D8B9CB3D3A52B03ULL, 0x35E25D57E4EA63B4ULL, 0x0CB2A1BE35F51AABULL, 
            0xD6F9B0F687600F26ULL, 0x92492E612DABD2B4ULL, 0xBF600FF311AC4768ULL, 0x168A8D978AB0B6C4ULL
        },
        {
            0xFDE38A66B1739B82ULL, 0xBD34BAACA8D493AAULL, 0xB12B9DB2164CE20FULL, 0xF6F45BBFC01B4AFBULL, 
            0x46A41C4D6E334D44ULL, 0x37FE055374204189ULL, 0x50A0B54A5093C7E9ULL, 0xCA5E1D7F06878125ULL, 
            0x18E1EACB1E312A16ULL, 0x97D9149A0B6D268AULL, 0x3DF6AA95C0B84F42ULL, 0xE1BB442A39E584B0ULL, 
            0xB6C1CEE0762311A6ULL, 0x95DD8CF0B02BA8D3ULL, 0xE2F43602B20A6A1EULL, 0xCB2D49B52D5867B0ULL, 
            0x6244D663A561CF0AULL, 0xD6795C7E7A4A8FC9ULL, 0x2EBD155A945FC44EULL, 0xF3F495F7AC3249BDULL, 
            0x05692330432EC929ULL, 0x4779EA1A9D4A94A6ULL, 0x90F92F507998EAB3ULL, 0x31F8C63D727B5258ULL, 
            0xC734C1656906C9CDULL, 0x83CCC69FA9BA7060ULL, 0xDEEE30EA3C3B4AF0ULL, 0x0EB42E50FC2743C3ULL, 
            0x7523B2950236F94EULL, 0xCC6F0D1CC350A628ULL, 0x3B4DCBDAB8ABC1ABULL, 0x9CEEAD19C2806ED7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseGConstants = {
    0xBCC042D0A61FDF47ULL,
    0xDBA956475AD6E355ULL,
    0x4AB60C7B83BF5367ULL,
    0xBCC042D0A61FDF47ULL,
    0xDBA956475AD6E355ULL,
    0x4AB60C7B83BF5367ULL,
    0x5CFC583B6CCFFA6AULL,
    0x304F07F11735376FULL,
    0x19,
    0xF2,
    0x56,
    0xF9,
    0x59,
    0xEE,
    0xCF,
    0x2D
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseHSalts = {
    {
        {
            0x6A99DD2EE453215EULL, 0x15876B172508D405ULL, 0xCA9C9DC00A77912FULL, 0x3141883B4F54A64BULL, 
            0x083E51F8691D85A7ULL, 0x577E24BC812535B6ULL, 0x207D8E671CD4FF04ULL, 0x5EE911AF6FC19A0BULL, 
            0x6FBA28BB3698BCAFULL, 0x431A52B396FA1563ULL, 0xD658350B444DB69CULL, 0x188B892C2CD180F2ULL, 
            0x1B909CED634A0AFDULL, 0x6FA024FA164CDB59ULL, 0x2C72971765A09F93ULL, 0xC82C49CB1BE4EAC4ULL, 
            0xB9AC3DB0398E7115ULL, 0x6335E90006ED12D2ULL, 0xFA6896F61E268A46ULL, 0x6248410D9F5220EDULL, 
            0xFFD3E8C404825FEEULL, 0x3721BD51001FD5E0ULL, 0xE2016C02A48E5FA1ULL, 0x1AD14FF0EFE63A42ULL, 
            0x324C6233DD57F04AULL, 0x0182D4DDF81E0ED6ULL, 0x46049B266D632438ULL, 0xC17A2294F2EA86C5ULL, 
            0x53C21EAC179C1993ULL, 0x19D7B4FCC8D8EC1CULL, 0xCAD169FAF7797C1AULL, 0x363C2DAE6B9C83A6ULL
        },
        {
            0x6A03531DFA21E776ULL, 0xA3FE02BAFBD4CB6EULL, 0x01F17DFD9630E369ULL, 0xC26292D389E537F8ULL, 
            0x409C19D7256D50B5ULL, 0xC5702D61A61FE8E2ULL, 0xD758071F80D7CD7DULL, 0xD90415EB1ACE55A5ULL, 
            0x0F087576B5ECA820ULL, 0xB16B0C8753C925F0ULL, 0x9F0B8D5F5B88DEB6ULL, 0x4B4A7C1E0634340FULL, 
            0x66CE8B4BBBA94301ULL, 0x711961D2F91630AEULL, 0x8D4380DAE834C59CULL, 0x8A2561A20C8E8191ULL, 
            0x43C7E2F9F2A91911ULL, 0xD0CF11EE2A98718AULL, 0x99A0ADD664947F3CULL, 0xA3053E75FFB0E703ULL, 
            0xA69C031C61E011D5ULL, 0xF2EBD3C2D811EDE8ULL, 0x189F16DE147D067FULL, 0x31629A5621F38664ULL, 
            0xB2A05C38BE6DD280ULL, 0x4C2C42FDBA280D83ULL, 0xA1F19BB5049D861EULL, 0x1DC16A7E2BAC810CULL, 
            0x890A047EDD05E16BULL, 0xF86746D1C8035772ULL, 0xB40C610B0C645F23ULL, 0xEE3C146D22D9C91AULL
        },
        {
            0x006D556415CEDF01ULL, 0x59BA9D76B40335F9ULL, 0xBFBA8E2BBC29B408ULL, 0x3A8B9626631124B2ULL, 
            0x0B07B92E61908534ULL, 0xDEE4AC9B5A6CAF2AULL, 0x7EE1270C7FBCDE3EULL, 0x3FFCE1009EFEF72EULL, 
            0x0F738B8C0E77E3D8ULL, 0x358F019017D2CC5BULL, 0x1ED68D7ABF79CBE7ULL, 0xF85AF58D1809EBE3ULL, 
            0xA616E8FE9FB1AB13ULL, 0xB24334D82FF0A9C1ULL, 0x703430F824C17988ULL, 0xCB7388F04F2D6634ULL, 
            0xE829A308CBC2DB19ULL, 0x6679D0BBD7AF658CULL, 0x30182BED1E8302DCULL, 0x7EAC2E7230C2296DULL, 
            0x8073A149CA85D2B1ULL, 0x9F0649C1D3FBA679ULL, 0xA306C233656ACF73ULL, 0xE19D13FE2967D920ULL, 
            0x6C2CFB30BEDD3031ULL, 0x58364F7234E64B56ULL, 0x26A52F759C03C88BULL, 0x857F537ED2E2241DULL, 
            0x74D3A3608F7DB718ULL, 0xC39B10ED1AB47969ULL, 0x9A249A222CE9704FULL, 0xB94C4A98FF622970ULL
        },
        {
            0xD356B39AA21E9035ULL, 0xBC3F73BF950F36E7ULL, 0x5718866A39E40459ULL, 0x41F37C526F2E365BULL, 
            0xEAECFC2B1971175DULL, 0xEAFD6ADE1BDBA881ULL, 0xB1DFF30A7543EB13ULL, 0x452C90428F97A451ULL, 
            0x2616F0AFD9D328BEULL, 0x27A51E2DF64332B8ULL, 0x6A615D45C179164EULL, 0x167578A56AEAA783ULL, 
            0x8F6B5AB496ACABE9ULL, 0xD8B96A9D116B6550ULL, 0xE27B4DF823377936ULL, 0x4C89868805D6E930ULL, 
            0x468768AB88C2F8ABULL, 0x4143FA61B6BB6BB8ULL, 0x55CA6AB0251CADF3ULL, 0x83B250771A49C10FULL, 
            0x6973FCB1CFB5F883ULL, 0x3D9162AEFC38A099ULL, 0xF0F388E5586EC5B6ULL, 0x2A5D0665079190DAULL, 
            0x4DD53D950CADF40DULL, 0x89D1A43B10DD7959ULL, 0x5D19C6020EF5A4DFULL, 0x35A1E9A7AF5107C2ULL, 
            0xD60781634809C1A5ULL, 0x26947DCA85D0970EULL, 0x92B240339278ABB7ULL, 0xF5437933192C915FULL
        },
        {
            0xB17571245F749D71ULL, 0x3BEB89F5E312F94BULL, 0x96165EF6D606B57EULL, 0xBD8241E828427701ULL, 
            0x3245DDC6FB463693ULL, 0x456578E6CD2D8210ULL, 0x529EAEFA9F2FA270ULL, 0x4AB57B01A19743DBULL, 
            0x909D2916A631597BULL, 0x994A52EB808DE4AFULL, 0xFE3A7EA6DAEE531EULL, 0xA4A6649E8030A585ULL, 
            0x7F67534F9F6FD41AULL, 0x8FE2BD893B6A6FEBULL, 0x2D4C6229172944DDULL, 0x50EAC58C28D4F63EULL, 
            0xF0B1FF399B3EFB05ULL, 0x1B9F76E0D44F3AB6ULL, 0x8FBB27F804AC9ADAULL, 0x70859342C736289FULL, 
            0x5BFEF87EF55AB239ULL, 0xD3E2ED8F964F1088ULL, 0xB9399D05829117FFULL, 0x2278FB8FFE68CA1BULL, 
            0xDB88B0D57E2C9C92ULL, 0xF7C0C69619AE127AULL, 0xF407446E9DB2E36CULL, 0x1E84670FE69A7B40ULL, 
            0x9F7E85C99A75579EULL, 0x0840C18E289806F1ULL, 0x7318E0FCC3E070B3ULL, 0x91DCCABB98AE53E8ULL
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
        }
    },
    {
        {
            0x3EFC29BFB5AA0C96ULL, 0xD460E857194DBA1EULL, 0x40979E7CDEE258BAULL, 0x7AD69C028785DE2BULL, 
            0xFFB49E7D022C6796ULL, 0x70D0EADC0F894402ULL, 0x1200ACAF91A421DBULL, 0x56B58736271DE97DULL, 
            0xCEB8A538D15D195DULL, 0xAE1FDDBD379027B5ULL, 0x32B009C3EA70321BULL, 0x833B9799C04DF537ULL, 
            0xCBE6485D78339D75ULL, 0x57CA371D84471E77ULL, 0xB5E3EA61590EE864ULL, 0x2BC1EBF5AE2F186DULL, 
            0xB2F7A25EB4417102ULL, 0x61D321E115630AF4ULL, 0x38A023F09D882921ULL, 0xD40A927DBE4AC515ULL, 
            0xE456C2A8C99AF7DFULL, 0x47CB5AA6E7732281ULL, 0x529B7DBCC386ABF7ULL, 0x5282248EB960FF3AULL, 
            0xD20130270CE8BF7DULL, 0xD6B514A67B4D170FULL, 0x35A90CAD957BF74DULL, 0x3F7F497992F22F77ULL, 
            0x6E4942B9A4E6F021ULL, 0x194AEAF7455FDCF6ULL, 0x9B37A92E98969261ULL, 0xC74DBC4670732647ULL
        },
        {
            0xF6B8BA68485A17CBULL, 0x848D25193EB1E974ULL, 0xA2F89B3E5503A3C7ULL, 0x1B2248587616A9C6ULL, 
            0x90B2927937D310FEULL, 0x6CB9D36429E7D868ULL, 0xB492D31F11C3BFEFULL, 0x812F0283579A22E2ULL, 
            0x20F8383A62596F56ULL, 0x26AEB1DC1CA92F43ULL, 0x2779D9F7B272851CULL, 0xB948B2DABBEC8238ULL, 
            0x26552F58FE0F54CDULL, 0x5262249BD35EF264ULL, 0x6BC763EC32F3D556ULL, 0x01D1E9743D9EACB3ULL, 
            0x653E2F0C217DE790ULL, 0x1E40F43EA78B5A92ULL, 0x52376B8BA3A22BDDULL, 0x77C2385319AF708BULL, 
            0x3D0C3F7AA0481BC0ULL, 0x5235987DAAC05CAAULL, 0x6FCED3E26CC53791ULL, 0x43A86998F6C2BEEEULL, 
            0x2F60FE9AA5DC1E22ULL, 0x30384D47E6A842FCULL, 0x2A179FB4E3638262ULL, 0x618B085E06906894ULL, 
            0xDEC65D788B3BBF7BULL, 0xEA548D98FBECF262ULL, 0xEF4BCBF284F93F22ULL, 0x539CA198DF854FC2ULL
        },
        {
            0x4DBBE14927573E5DULL, 0x4FA50064BAD7E088ULL, 0x6310AABF0ACD308FULL, 0x68DC768470754740ULL, 
            0xDD3E160FC6771317ULL, 0xDD6C9AFC395FD7DAULL, 0x1400DC41F52C149AULL, 0xD4E6E0E0011EB68FULL, 
            0xAA773A27EE3A1E6FULL, 0xD7F9BFD19CBF6AEAULL, 0x7D569365C2AC940BULL, 0xFD15F4ACE2ED29F5ULL, 
            0xC9BD3DA7E55F4937ULL, 0x06910BABE07FBB3BULL, 0x12607A24274E2A63ULL, 0xF90CF1859247C2F7ULL, 
            0x3D79D58D969F62FCULL, 0xB0CDBC403C0176A0ULL, 0xEC29683E716FA042ULL, 0xF5AD57FEC0D3B7BAULL, 
            0x8032B0475AAB7173ULL, 0x7AA357FBB0937E33ULL, 0xEE452E4ED9D2A3ACULL, 0x07DDC0F30F848B35ULL, 
            0x86C8D86948ADFA40ULL, 0xBDA3EDECE992144DULL, 0x33F4F03035ACB360ULL, 0x6400BF6A5D701E79ULL, 
            0xCB01E6CE9A77F0E8ULL, 0x08AF62F69C52125DULL, 0xCC5F0C8566165A9FULL, 0x2E46A4C77FF7A673ULL
        },
        {
            0xB3F74832B874259FULL, 0x06553D3EF7C5C269ULL, 0x7C26E72D00D3E814ULL, 0x4BBBBE7539ED0880ULL, 
            0xCAC4A2490EF0EFF1ULL, 0xFC6AF5BD48CE8FA3ULL, 0xFA3FCB8A0D074BA2ULL, 0x2311226A0673A0E0ULL, 
            0x2335D9F0F6168AE6ULL, 0xE1A2C9FE71CFFDA2ULL, 0xF30F22DB7BC92A4BULL, 0x33D1B62D1DCFFED4ULL, 
            0x67B1FB888305268FULL, 0x759A7AD8290A073BULL, 0xA4AB185EF7A009FAULL, 0xF6B4E420649B800CULL, 
            0xACA3DDCC72504782ULL, 0xF25EDF8EA48C5DF3ULL, 0xE16E86D064AAA3D4ULL, 0xA18DBC2A4AD8FCFCULL, 
            0xB348AA5A9DFA8809ULL, 0x3B68170DA46DC0D4ULL, 0xECCA454BFA2EF2C8ULL, 0x83DA97459D6960D0ULL, 
            0xCD8E803F9107D227ULL, 0x823EBC8D65D25401ULL, 0x263C9E593C2DB824ULL, 0x25A3E92557D702ABULL, 
            0xF43E049079EC946EULL, 0x7D59549ADCF3D1A3ULL, 0xF394CB298145B3A3ULL, 0xA614BC341B59CEC1ULL
        },
        {
            0x3A51CA565BF00467ULL, 0x9DF7F1E365EA6E68ULL, 0xE65C1723FEF84CFAULL, 0x3F6789DCA43BEC09ULL, 
            0x21F8FB6BE5C1AEDFULL, 0x062BFC545701BAB1ULL, 0x277FD13D008D8553ULL, 0xA5A02862B4425871ULL, 
            0x2352091D850579D2ULL, 0xBB5CA0E6612B42E3ULL, 0x92B4C3A5498F7681ULL, 0x167D1E28CD1D9885ULL, 
            0x06C189297322C4F9ULL, 0x439053F05DD49DAFULL, 0xAF8D7D9E142D74EDULL, 0x3D4E7A2EACA147ADULL, 
            0x46FE8B2746828D09ULL, 0xB6C3E349A9398ED7ULL, 0x88BEEB52ABAF7EF7ULL, 0x1B01EF13B9CC7B62ULL, 
            0x5118588F913A1512ULL, 0x9BB953A0E792BE41ULL, 0x874897A0343F2FE6ULL, 0x8181A3D60CD577A0ULL, 
            0x94DAE0B7DFA82F39ULL, 0xCC1CBA1EEB64F16EULL, 0x224D7F4F5A1D736FULL, 0x8B71F6AD7054879DULL, 
            0x72A4E4E2D1705A32ULL, 0x5C1C956C70DB32F8ULL, 0xB074EB2EDA3F71E5ULL, 0x0086A05482933C88ULL
        },
        {
            0x5D4FDEB7E2A23A85ULL, 0xA64F83D0F9364B0FULL, 0x72CEAFA98C97331FULL, 0x71D6343645126985ULL, 
            0x8B65DCB39C55928AULL, 0xEA4C36D3CF8B1AD1ULL, 0x20C5C28490630E61ULL, 0xDC56A394A9249F76ULL, 
            0xFF5C6BE7338676CDULL, 0x08F8D35F6DF730F9ULL, 0x1C077E8A3293B8E5ULL, 0x8F091767A1674873ULL, 
            0x314941ABDE0BAC49ULL, 0xD5E1E63210E5861AULL, 0xD5CB5428865264E7ULL, 0x5C304B2703C78854ULL, 
            0xACF7F127333BF01EULL, 0x4892DF039E4DA2C0ULL, 0x1F5BC621F4020F36ULL, 0x63E55154C4F61B8BULL, 
            0x405E72AAB6E5DC13ULL, 0x798889DEE0EFB5DDULL, 0x6DF9892DB0164AE9ULL, 0x8B67FD8CD347456CULL, 
            0x2C66B4BF848ECF96ULL, 0xA20E8B5E1688F680ULL, 0xD8545A37F255B736ULL, 0x1C67AD0EB840D0C7ULL, 
            0xC396D93FE0610E8CULL, 0x3952DB80A9691F8DULL, 0x5D3A453D086E3000ULL, 0x875A3454E1372253ULL
        }
    },
    {
        {
            0x4D78C921B3981837ULL, 0xB860090C09E7E7CCULL, 0x5C3937496504E62AULL, 0xB7C72C145B5DF969ULL, 
            0xDFBDF5C5723EA46EULL, 0x5EA7ED90C89BA65DULL, 0x105F5267C5E013F9ULL, 0x869D843720160E71ULL, 
            0x4FE41419C810E046ULL, 0x4D2FE25BD0238C37ULL, 0x69CD04DBDC857B76ULL, 0xFD4E2E413860A26FULL, 
            0x328739E4DD1AB163ULL, 0x9C8FD33CD56F3FEFULL, 0x78402857639ED1EAULL, 0xF97A85C22E733D01ULL, 
            0xE248ED0A91BF921CULL, 0x9EAEA122C8AA4BDAULL, 0x107023A47FE609EEULL, 0xA5B26380D9C00807ULL, 
            0xFA63E907E3FBDF2BULL, 0xCEEECB2B87BE3ACBULL, 0x5948EC3D5796A4F2ULL, 0x11833379F076CCE4ULL, 
            0xF0DB0ACE745C0004ULL, 0x955FC5AD3C3D2A11ULL, 0x92C39EBA846E2014ULL, 0x7619A22835515279ULL, 
            0x6CBA554AFE7D096BULL, 0x115B98E18D9102C7ULL, 0xE7919D116B500850ULL, 0x75C446200D2043BFULL
        },
        {
            0x72CDD7E393B83A1BULL, 0x862B4F36F8BF747EULL, 0x5B885585FA32A5CEULL, 0x28E2BBF1EF2158FDULL, 
            0x7715F00D9C4CE3FFULL, 0x55B38C227B6934C3ULL, 0xEDA5E744610E7F61ULL, 0xFC958241015A418DULL, 
            0xDED3E0E9539F4329ULL, 0xE88091D2A26BE7E6ULL, 0x5572015A5CDEE15DULL, 0xF3F6D780ECF7AF34ULL, 
            0xF615B28F5A3D0930ULL, 0x127301832B466172ULL, 0x6CB4E7613AEF15DEULL, 0x4325A239DB3B660EULL, 
            0xBC1EF01E0147EEB7ULL, 0xEE29BBB04D36497CULL, 0xA6A4C4EC0458A204ULL, 0xD4634F51AC8A9B60ULL, 
            0x4A18F218179DF85DULL, 0x26C5A8934FBC9A19ULL, 0x87A93127075902D8ULL, 0x8B26469AAB922F16ULL, 
            0x1A8C03FC5ECDDC15ULL, 0xA1EDA1798BD22BE8ULL, 0xF5A7859EDBB0272CULL, 0xE2B703CC42CF2697ULL, 
            0xDD61F11FB06710FAULL, 0x4323A7A8E0FED164ULL, 0x5031D2D7B0F5F8C1ULL, 0x53DBB3B953ED87F1ULL
        },
        {
            0x0882ADAEDEFCDDBEULL, 0x594A71C29B009018ULL, 0xD5A8D9AFC1270D1EULL, 0x253B674C1E3F7752ULL, 
            0x7AF720115C26A3C5ULL, 0xC2FE9910FCF58D1DULL, 0xC9F4C3D375B3EDF0ULL, 0xBA069F814AE638D3ULL, 
            0xA65F620CFA7BAAB7ULL, 0x1A3E0F00CF641776ULL, 0xA70DAEF97C61F9E8ULL, 0x662D5CDA598F1794ULL, 
            0x9F0D7B5E65A3EA3EULL, 0xD5301AA91148C7D8ULL, 0xE9E52B129A90F753ULL, 0xC1782D3738436479ULL, 
            0x7B042DB11DEB0269ULL, 0x4BFEB0EB66109C81ULL, 0x11D47BCAB345BA71ULL, 0x952FE93D789AEB6AULL, 
            0x03B15FD386472C87ULL, 0x7565807096724DD7ULL, 0xE32F861A427BDC1EULL, 0x78B476A0124D682EULL, 
            0xCD59D9DDB4B311EBULL, 0x4432B1229338D7E0ULL, 0xDA4053D403516072ULL, 0x6001ADF9D7EB9565ULL, 
            0x46D5D64BB07214D4ULL, 0x447581D6AD7EBBFFULL, 0x9F713B73B25A71FDULL, 0x0127B28A8989DC0BULL
        },
        {
            0x78722801132B2889ULL, 0x2B1A416D7A1FB6ABULL, 0x1195E32938A1BF6FULL, 0xA4B8C3ADD535C104ULL, 
            0x1CAD4C1FCD70C3B5ULL, 0x35956F223F62CA09ULL, 0x6DC1AAFA5F9F23D0ULL, 0x6998E2817E5E7A23ULL, 
            0x33DC78E6A87B3DA7ULL, 0x1D4120EACABD7E70ULL, 0x483C12FC524920CEULL, 0x7155A81BA5E6297BULL, 
            0x39027BB3F92CBD9CULL, 0x8505FE0C2F737900ULL, 0x0B736C04A77D90F0ULL, 0xEBC8471764B3A8DEULL, 
            0x65207B92EB84B7E4ULL, 0xF9C17B6CF4DB94E9ULL, 0xE9CC753D8225AFA1ULL, 0x0817B0C447514888ULL, 
            0x3A7F44A44581478DULL, 0xC8F52D795416AAE5ULL, 0xABC1BE2A4ADD5377ULL, 0x0B86B84D074468A7ULL, 
            0x2B4A02019C6D26F7ULL, 0x9722BFE9E3B0AA8AULL, 0x9FDC6C4E0521000CULL, 0x6E9EE444C6A3591CULL, 
            0xD04D66E1159ACB66ULL, 0x6D9F1DA1B17A5279ULL, 0x1D90F74F635C2DF3ULL, 0x79F4D6EDB487694AULL
        },
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
            0x5345CE3A7B924349ULL, 0x129A37CC6437F95CULL, 0x2D2227BC0D285F14ULL, 0xE00CD334DF721F7DULL, 
            0x7353943F61B016C2ULL, 0x8DB50A8F23C44FDBULL, 0x3289406594E9BE43ULL, 0x59C602EF75AC574CULL, 
            0xA4CC7C0815A0F14FULL, 0x74E146206037D602ULL, 0x0870B53DF09547B2ULL, 0x00B133F7BE5E464DULL, 
            0xF6DE1AA0F8415FCCULL, 0x7EEBC3C46D6B9621ULL, 0x62D4C2DD3D723302ULL, 0xE1D693596E6263DCULL, 
            0xD02D5FD53A1986CCULL, 0x36B639A77E21091FULL, 0x7BC7A21C8CA1A08FULL, 0x616E60432DC41F38ULL, 
            0x6C5ABEBA5840DD5BULL, 0xB3D225A88B6C7D0AULL, 0x0B9B58053062EC7EULL, 0xB548062503F0F9D3ULL, 
            0xA511E4633120D6E0ULL, 0x309481B82E211D45ULL, 0x12A2A49BD6E14CABULL, 0xFBB7A5CED4C5D168ULL, 
            0xB55687B37DEA5DABULL, 0x84979A09F3FC7F2CULL, 0x1ADFE58E3E7A52D5ULL, 0x884168FBC80DBA40ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseHConstants = {
    0x6EF85F35F06CB3FAULL,
    0x3CBD04324C6C2D3AULL,
    0xF0AC1F934A27D9A5ULL,
    0x6EF85F35F06CB3FAULL,
    0x3CBD04324C6C2D3AULL,
    0xF0AC1F934A27D9A5ULL,
    0x58713503C8C927AAULL,
    0x8F7451445AA3E71DULL,
    0xB1,
    0x28,
    0xA1,
    0x56,
    0xDE,
    0x9B,
    0x21,
    0x24
};

