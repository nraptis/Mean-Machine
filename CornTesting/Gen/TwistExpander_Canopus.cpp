#include "TwistExpander_Canopus.hpp"
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

TwistExpander_Canopus::TwistExpander_Canopus()
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

void TwistExpander_Canopus::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xEBCBE0D24E3C08DCULL; std::uint64_t aIngress = 0xF7D441DE3463FEB0ULL; std::uint64_t aCarry = 0xA858802359D0C6C0ULL;

    std::uint64_t aWandererA = 0xD513781B23D26D96ULL; std::uint64_t aWandererB = 0x8C4B486A4E27F766ULL; std::uint64_t aWandererC = 0x95A5A7715613B10FULL; std::uint64_t aWandererD = 0xEC382CEDA57B741AULL;
    std::uint64_t aWandererE = 0x9D99DBE93CC6C8C0ULL; std::uint64_t aWandererF = 0xE965DA89260D6EA7ULL; std::uint64_t aWandererG = 0xE00D467C23176526ULL; std::uint64_t aWandererH = 0xAD6203751D0EA262ULL;
    std::uint64_t aWandererI = 0x8B972711A876FB8BULL; std::uint64_t aWandererJ = 0xD6E66E349029B60EULL; std::uint64_t aWandererK = 0x89128D4FA0D61F44ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13912119446072226413U;
        aCarry = 14879729054011047239U;
        aWandererA = 13660881198105343721U;
        aWandererB = 15802825593350335785U;
        aWandererC = 18256565108376589907U;
        aWandererD = 12942697602498396390U;
        aWandererE = 10437622871380139714U;
        aWandererF = 13640449189486409332U;
        aWandererG = 15672226972353441166U;
        aWandererH = 15669784928198470270U;
        aWandererI = 9587200687049588895U;
        aWandererJ = 9269181849174517279U;
        aWandererK = 15006474228577507130U;
    TwistExpander_Canopus_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Canopus::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xADCDC40297A60724ULL; std::uint64_t aIngress = 0xC7399BF969E08120ULL; std::uint64_t aCarry = 0x98608EB572C83BAEULL;

    std::uint64_t aWandererA = 0xD9182DFECA350572ULL; std::uint64_t aWandererB = 0xD65934319FC97355ULL; std::uint64_t aWandererC = 0x93F72C21EC27FF41ULL; std::uint64_t aWandererD = 0xD1B554B259797CE5ULL;
    std::uint64_t aWandererE = 0xB723DB173E8E5CC1ULL; std::uint64_t aWandererF = 0x87090D6EB6298F37ULL; std::uint64_t aWandererG = 0xA4E12C724B1D4F85ULL; std::uint64_t aWandererH = 0x9453E69046A5C957ULL;
    std::uint64_t aWandererI = 0xE4EA9065BF02CDF0ULL; std::uint64_t aWandererJ = 0xD5A49A78541A0D3CULL; std::uint64_t aWandererK = 0xD9C585918AEEF6C1ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13047018568688067053U;
        aCarry = 9923500060511526683U;
        aWandererA = 16307619684851947902U;
        aWandererB = 14864410646930118884U;
        aWandererC = 10942141296393967328U;
        aWandererD = 12004101019662673158U;
        aWandererE = 14448127976793923613U;
        aWandererF = 13372561468547574620U;
        aWandererG = 10770683233847400777U;
        aWandererH = 14298026508115538749U;
        aWandererI = 9465469862689262048U;
        aWandererJ = 10676682815239977401U;
        aWandererK = 14271599175027043855U;
    TwistExpander_Canopus_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Canopus_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Canopus_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Canopus::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x9C319F2C7EFC7846ULL;
    std::uint64_t aIngress = 0x855F2EBC07DEED46ULL;
    std::uint64_t aCarry = 0x97DD65F22630BB7CULL;

    std::uint64_t aWandererA = 0xA1C06D55FA6EE8E8ULL;
    std::uint64_t aWandererB = 0xDF9FCC2647CDA40AULL;
    std::uint64_t aWandererC = 0xB713E189A3894714ULL;
    std::uint64_t aWandererD = 0xABF1AF235E1A9AA5ULL;
    std::uint64_t aWandererE = 0xD572A2D20E0E3482ULL;
    std::uint64_t aWandererF = 0x861BE1F3DDD8814FULL;
    std::uint64_t aWandererG = 0xDBCAA733B6846BC3ULL;
    std::uint64_t aWandererH = 0x945D189291B26A16ULL;
    std::uint64_t aWandererI = 0xAF70B3182CACF1D9ULL;
    std::uint64_t aWandererJ = 0xB37A5DA996CD6F3FULL;
    std::uint64_t aWandererK = 0x8738A744882B2125ULL;

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
    TwistExpander_Canopus_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
    TwistExpander_Canopus_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Canopus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Canopus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 14 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1838 / 1984 (92.64%)
// Total distance from earlier candidates: 24142
void TwistExpander_Canopus::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 443U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1133U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 101U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1111U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 389U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 433U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1820U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 650U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 982U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 880U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1494U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1515U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2040U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 971U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1564U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 182U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1656U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 799U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1469U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1215U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1594U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 872U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 662U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 858U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 59U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1360U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1122U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1021U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 135U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1420U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1449U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 876U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1955U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2022U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1655U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 891U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1200U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 17U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1809U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1435U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1696U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1584U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 617U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1256U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1796U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1626U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 374U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1312U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1770U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1085U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1927U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 458U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 429U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2023U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 525U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1545U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1811U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1815U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1016U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 0U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 42U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1269U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1003U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1491U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1649U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1349U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1959U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 45U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 868U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 995U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1115U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1236U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1418U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 138U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 234U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1429U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 855U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 800U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 465U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1072U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1322U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 100U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1636U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1279U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 23U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1608U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 648U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 860U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 361U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 104U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1548U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 149U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 249U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1982U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1744U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 796U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 466U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1918U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 131U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 883U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1185U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1368U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 892U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 235U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 231U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 394U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1695U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 373U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 422U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 790U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 642U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 545U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 30U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 405U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1393U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 709U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1710U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 492U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1742U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1917U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 289U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1885U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1238U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 179U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1835U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1908U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1358U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 166U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Canopus::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xCB71C95CE55B9074ULL; std::uint64_t aIngress = 0x842012CA2F38AFEBULL; std::uint64_t aCarry = 0xED22C1806634E186ULL;

    std::uint64_t aWandererA = 0xDE0AE9F186445D57ULL; std::uint64_t aWandererB = 0xAC3142042663B475ULL; std::uint64_t aWandererC = 0x9A974381A3ED0250ULL; std::uint64_t aWandererD = 0x9F6B8DBC24A00003ULL;
    std::uint64_t aWandererE = 0x958906E32A00E437ULL; std::uint64_t aWandererF = 0xA690C7325706273BULL; std::uint64_t aWandererG = 0xDE0A5FADED0E25D2ULL; std::uint64_t aWandererH = 0xB4E02FC9A6E3EA5BULL;
    std::uint64_t aWandererI = 0xA41C035695443667ULL; std::uint64_t aWandererJ = 0x9684FA853E17EE7BULL; std::uint64_t aWandererK = 0xE2C40DFC2EB50C74ULL;

    // [seed]
        aPrevious = 9388282213868925051U;
        aCarry = 9342241007832876289U;
        aWandererA = 9875505172489265204U;
        aWandererB = 13991989355332268272U;
        aWandererC = 13788689983079761023U;
        aWandererD = 14831692250372046193U;
        aWandererE = 10887223760684021623U;
        aWandererF = 9368203967153156590U;
        aWandererG = 13594011569119699131U;
        aWandererH = 17304931857089531671U;
        aWandererI = 13452412519300533333U;
        aWandererJ = 9783385979987071445U;
        aWandererK = 13210549330149230004U;
    TwistExpander_Canopus_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Canopus_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Canopus_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Canopus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Canopus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 14 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7120; nearest pair: 509 / 674
void TwistExpander_Canopus::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5994U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2962U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7432U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3749U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3506U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2853U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7698U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5188U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5133U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3863U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4178U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3000U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1275U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1204U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3963U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3710U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 947U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1327U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 604U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 515U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 788U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1565U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1911U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1844U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 170U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 387U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1175U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1785U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 671U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 753U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1285U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 46U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1613U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 217U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 870U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1031U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 14 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 7134; nearest pair: 474 / 674
void TwistExpander_Canopus::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3894U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3649U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6433U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6246U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3606U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4842U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6771U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6940U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6660U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3795U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3369U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4701U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1471U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2528U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2638U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5523U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1192U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1150U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1207U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1732U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 943U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1210U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1862U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1431U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1316U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1907U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 300U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1603U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1310U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 144U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 343U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1681U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1152U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1405U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1754U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1619U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseASalts = {
    {
        {
            0x4FE6935FAD810E99ULL, 0xA65377D28E3E3B16ULL, 0x21EF60125283F495ULL, 0x50551B4B54EFE733ULL, 
            0xE2FECBF1EF7BEC8EULL, 0xDC63CAB51EA989CBULL, 0xC6DA725A81C46AA0ULL, 0x9DFA4A200EB31154ULL, 
            0x203FC9E6766F75B0ULL, 0x19CE1239CC9C677BULL, 0x009E12D325F9481BULL, 0xDD087B6A0BE8C5B8ULL, 
            0xED83AB90492CCB04ULL, 0x4C77FAF28FD6FB3DULL, 0xD19BD9CEFA4CF1E9ULL, 0x0AD1202079B6A2CEULL, 
            0x0E177DDC14B186C9ULL, 0x23EA46B84DB6CB4BULL, 0x831C85C4B769919EULL, 0x86B053B650D94051ULL, 
            0x81C6F33266A12981ULL, 0xB3605C8DA3CA77ECULL, 0xEC79822D630D36FAULL, 0x825754D57CCB4A8AULL, 
            0x62461D26858A5F55ULL, 0x817F79DAAD6BE4FFULL, 0xE028470AAAE6568BULL, 0x02557D425DA5462FULL, 
            0x1EDEA0CD9309A326ULL, 0xACEB5B030AC7E5E3ULL, 0xF4743902B0DCBD50ULL, 0xFF01F1A4FAD96FA6ULL
        },
        {
            0xA0DAFB537B3085BCULL, 0xFE129AEB23AD101EULL, 0x9BC15A4E8B1DB6F4ULL, 0x2BBDE8058EE22F04ULL, 
            0x7496EBF51757A5F2ULL, 0x668A6E09457488D9ULL, 0xFA6C7ED1DCC1B12BULL, 0x2CED28C6B436000DULL, 
            0x2C5DF0D16EBCD484ULL, 0x4AAF6906F7836571ULL, 0xFD7FE0427D3434C9ULL, 0x60C7DBD3ACCBAEC9ULL, 
            0xAB7F0B3B63357189ULL, 0xBC5E64BFF5B579B3ULL, 0x427CD2B154626040ULL, 0xF5EE4983819BB247ULL, 
            0xDE879AB60440BB03ULL, 0xEDDCCA8675E9B757ULL, 0xAF166A397B9951AAULL, 0x8BFFE9DE33F868A0ULL, 
            0xBB40BB278AC9BA8FULL, 0xAE634990C2488663ULL, 0x6D8C090F96422FF1ULL, 0xED6806DE333BB820ULL, 
            0x73D1AC92D064929CULL, 0xD63F41091B63E457ULL, 0xD4A05F93EDB37D7FULL, 0x35CCFD6910D5E321ULL, 
            0xD4829A3829194B3BULL, 0xF506C919B19B4AFFULL, 0x98076D8E341DD528ULL, 0x3CFEC1A992235108ULL
        },
        {
            0x065C5407DDC9A86FULL, 0xE897762279F4B37CULL, 0x861B7EEE1C4562D9ULL, 0xE8461015CDB35542ULL, 
            0xE8335EF38BDD6A53ULL, 0x39266420780F6CBEULL, 0x30864188658CCAC2ULL, 0x4CF3FC82D52590C1ULL, 
            0xFFD05E69797C606DULL, 0xDE754FBB550E832FULL, 0x4D3DCA5DB7E3774CULL, 0x144609948D38B6DDULL, 
            0x38B5043A96085D14ULL, 0x61BDA936F3C370CAULL, 0xD99B43146A5D7C91ULL, 0xB2DF66E7B0A003B8ULL, 
            0xEAB9730B3AD1E4AFULL, 0x0FC5056242CA5DBEULL, 0x671733C3152EC1A4ULL, 0x7951580D02894B4DULL, 
            0xB205135383A9D74AULL, 0x1E0BF713BCFE7B7FULL, 0x3E1C6D566C3BC652ULL, 0xB2507644A9C907CCULL, 
            0x22C0E44505A2317FULL, 0x389FD03996014C01ULL, 0x2846FAF097C52175ULL, 0x962DB006D9D3B4EEULL, 
            0xF2EF5CAD8220A0EDULL, 0x286C7E94946A658EULL, 0xEDC65FD0A58CF899ULL, 0xD53F6F69A6D9902BULL
        },
        {
            0x503ABA370D88E012ULL, 0xC22819DEB1360F17ULL, 0x2AF8DD0989E62F68ULL, 0xC2AD45F5F50F274EULL, 
            0x206262875FB1D9F5ULL, 0x7634F98A23541C93ULL, 0x63CAC59384030420ULL, 0x0B843FC828B5FC0AULL, 
            0xDF800BC3FD4BD340ULL, 0x980763B02BC7E28BULL, 0xC5FBECE25CAA0CC2ULL, 0x0FA60245F75B1E82ULL, 
            0xF4BC7A67E48554FCULL, 0xEF057FB993070FB2ULL, 0xAC39A3AC35791BDAULL, 0x3458B04238884526ULL, 
            0xEF8392E1F15D54A1ULL, 0x6D970F1652DA2BCEULL, 0x1C79BDE60D5454DBULL, 0x8CBD3C0DBB80B523ULL, 
            0xDABE823583492314ULL, 0xF3A1B1ADCFAE01E8ULL, 0x77DD2FB1DA783C0AULL, 0x745D79EB765CAE4AULL, 
            0xA0AC80E3673C12C9ULL, 0xF75E7F39BB1D6586ULL, 0x3FAD3A4641CA7DB2ULL, 0x813A52FA1566725BULL, 
            0x3CFC507714E1D660ULL, 0x74D0F01227E3AE81ULL, 0x294D9ADD0CF82AC2ULL, 0x432F6FBB73580CB0ULL
        },
        {
            0xE1F0ED92A47C0735ULL, 0x7D89FEA84599D1D3ULL, 0xD6832BF3E4F60E91ULL, 0x03FBCC3E3F05AB3AULL, 
            0x0347689981811655ULL, 0xB8E7F0C0D674224FULL, 0x863498FF7E649DBEULL, 0x7E674CA8EB25DF7FULL, 
            0x6A9EA6174A0B3E79ULL, 0x48658765E85D11CEULL, 0xE4D03A02D4763F70ULL, 0xAEE3F40DB2F2BE16ULL, 
            0x25DC29A8268F3580ULL, 0xC29244D407AA3C81ULL, 0x549783FC1A6DA3CBULL, 0x65E7CD986CC4282FULL, 
            0xF80DF48E0D0C053EULL, 0x9FC600C7259A8283ULL, 0x6341FA19C9703952ULL, 0xD6A41C1AB1CBCBDCULL, 
            0x101F1397BCDA1B31ULL, 0x9A37EB20DFD7E43AULL, 0x871C5658C0A60C03ULL, 0x2C559808D686F5A6ULL, 
            0xD8124076C77C04F6ULL, 0x614A60A4B7F7B895ULL, 0xC323782EC8C7810AULL, 0xA6EE1124BBCC7B9BULL, 
            0xC04BA32C86283479ULL, 0x2A36C87C70BC4662ULL, 0x9C28E474292F2847ULL, 0x8073186EA5B8E9E5ULL
        },
        {
            0x736B9CCBE7CF1641ULL, 0x1487F99DD177F5F7ULL, 0xB585151B446D0358ULL, 0x9F55A254328F1A2DULL, 
            0xC151E11775E73554ULL, 0x19EE32AEDB09A502ULL, 0x2B824E57069CA570ULL, 0x25B846C1DC811A10ULL, 
            0xE276A96D37C4E5D3ULL, 0xA1DDF57AD1798241ULL, 0x24A29420B8A9AD48ULL, 0x7195C0493DE6FC77ULL, 
            0x5A13650130F5A556ULL, 0xB0E15A61AF013329ULL, 0x0B269504BD5A6F57ULL, 0x5B2AFFC83071D2E8ULL, 
            0xA7ECEE04B8EEA51BULL, 0xD38D51E2B38A7875ULL, 0x32A63C5B2DD608F4ULL, 0x9806E0E09A1D0ED0ULL, 
            0xB036ED7CF82838AFULL, 0x0E74CD4BE1123662ULL, 0xBE3D04C331FE4A2DULL, 0xDEFBFCB95C568938ULL, 
            0x4B4DE35D01872F39ULL, 0x20741A6BB092FA8CULL, 0xF359F8B74D7CF86FULL, 0x38C3E5CD0DCF7827ULL, 
            0x331B7DB1C088FFA6ULL, 0xB4E0BE9F1F8EFEC7ULL, 0xE60A5DC763AD1884ULL, 0xD85C97F087C1061CULL
        }
    },
    {
        {
            0x501B0D075B681072ULL, 0x973C7E3C895A2C9BULL, 0x8AAAD7EBBD03E653ULL, 0xD8E38CCC34B68E3BULL, 
            0x155446F36EED0594ULL, 0x1C42E7BE6044655FULL, 0x6C29B0678DDEADEAULL, 0x328952996B2AB7F0ULL, 
            0x942431E6241B0C40ULL, 0x3ACF01CB807966D0ULL, 0x4A429376E0901247ULL, 0x261FB5EC21EFBDDFULL, 
            0xDC211AE00B41971AULL, 0x43AC2D46CDD12567ULL, 0x5EA2CF94ABA08B01ULL, 0x6AEA7B5CB545A5B3ULL, 
            0x32538DF03EE35323ULL, 0x98EE3898957ED69DULL, 0xDE9EA9B84E2A7328ULL, 0x26CCED2785C82853ULL, 
            0xBBAF889BE69754ADULL, 0x3BB3B60481B1C974ULL, 0xC9073FF90D0A4D8BULL, 0xEAD5D14515771613ULL, 
            0xB757EE94A995BE3CULL, 0x40C817BBA288225FULL, 0x9A7CC9BF075AF262ULL, 0x5391610BFB6A4AB8ULL, 
            0x2477E17E7D41088FULL, 0xCB6688B5D4279235ULL, 0x6E312B8F33AB7680ULL, 0xCBEB48DB737B6E64ULL
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
        },
        {
            0x79E0ADDDFB988441ULL, 0xD7F4F73886DBB829ULL, 0xEB3FB1C1EDF780EFULL, 0x88B960344A517B2AULL, 
            0x45BCF9514204FBFCULL, 0x4EE494D9EB5DB216ULL, 0xA476F3A9FA5C0758ULL, 0xBBB57383D67C0771ULL, 
            0xB28A2B51E094A637ULL, 0x38CB3EDD7689F6C5ULL, 0xF05D48A9F8057C2CULL, 0xCD9D8DF1E3444940ULL, 
            0xEBAC9F764CF035EDULL, 0x357B90B7AED5456EULL, 0x3D1F9BDE2B9BE91EULL, 0xF6329C43AFCDA591ULL, 
            0x188C40996308764AULL, 0x2BEEDDCEBD44D82DULL, 0xD83236847AEDA3AFULL, 0xF8423E15EF2DA35EULL, 
            0xE514D5F47FE6E7C2ULL, 0x99200999F835AAE4ULL, 0x8D95217020D94C99ULL, 0x9B812573E45AFCCDULL, 
            0xB90007D43143A20DULL, 0x4BDDDAB40D241806ULL, 0x9E8397C1FF474279ULL, 0xC23C7370BD1A177CULL, 
            0x059E7588958A4617ULL, 0xA72ADD3A0FA6355BULL, 0x001F9874E8C6BE84ULL, 0xB1A1F7B35B018B3EULL
        },
        {
            0x23003F96AF7E8DF4ULL, 0xEB11BBC21D53F4E0ULL, 0xA82C56C6B2E29C07ULL, 0xE7BEA686DA9D77EFULL, 
            0xB2BA37B4784617AFULL, 0xC5DFDCC56B526EBDULL, 0x57D1FB2BB224FFCEULL, 0xA6B0695B571804FBULL, 
            0x9E8002900872164EULL, 0xE91520DFEFDC4480ULL, 0x2AC1DD00B35326DDULL, 0xB0416D470C8CCF81ULL, 
            0x4B49F7A3974568A0ULL, 0xE5390B693B10B66CULL, 0x9D16BC57671B4760ULL, 0x484F3522814A0BF6ULL, 
            0xDB8DE9EBCA13C908ULL, 0x86930EC41C7B43BAULL, 0xA1E79F2902B6410BULL, 0xC9706589B7420B74ULL, 
            0xFC95EFA41AE6CCB3ULL, 0xB984650191AFF9ECULL, 0xAA126E29D7F2F979ULL, 0x7BE943FBAEC10354ULL, 
            0x0DE0F95E909C82EEULL, 0xF0A8C31A3AC46BF7ULL, 0x9271B7D946CF853BULL, 0x1D1955B5924E6821ULL, 
            0xF7AB1E39002E02ACULL, 0x4864B4BD6E4D3F7AULL, 0x519AF2DB9F9E11F5ULL, 0x3E5F53CF196A60BCULL
        },
        {
            0xD87847639C2A659DULL, 0x80DE02E65EB93465ULL, 0x6773A36DCC2430FDULL, 0xF982933C7434E987ULL, 
            0x2A9570701619E342ULL, 0x2A07A8B6ABE8FD99ULL, 0xBC959854067A628FULL, 0xD833A59F43C9034FULL, 
            0xF4D62394F98CE200ULL, 0xCB0881AC83049AF9ULL, 0x9C41C67F58703E08ULL, 0x31F54835372E2695ULL, 
            0xD34E22CB821526DCULL, 0xD3ECE73AC8C148F9ULL, 0x88B2EF064C7B30FEULL, 0xB50849598123892BULL, 
            0x15E0BC8A81606592ULL, 0x0DC732E5AF1B0CE8ULL, 0x4069D546B11602B7ULL, 0xCDF002E41C359739ULL, 
            0xD97B54FA2F0051BCULL, 0x2F4C08C5EA65D534ULL, 0x079FDD9F5B239B27ULL, 0xC462466631C83881ULL, 
            0x3ED4111215692988ULL, 0x097D4D7C6FBA6EEDULL, 0x7115A81A85A2FE37ULL, 0x9FF57A0392EDFDDAULL, 
            0xD91334BEF056593AULL, 0x428FBD6C1A8147F7ULL, 0x503C145A86D227A6ULL, 0x9BDDA2BD893B61C7ULL
        },
        {
            0x291B3C1328325A21ULL, 0x2D78AEF061E3DFE4ULL, 0xF5FC27E53CEDED7AULL, 0x86F1C552C92F2142ULL, 
            0x53C54A0C1067B7DEULL, 0x3B32E0DDB08440B1ULL, 0x731DEEBE38184985ULL, 0xB052E44C501AC3C8ULL, 
            0x1357A0314D163F85ULL, 0x2E48653F871C6B7CULL, 0xC6737C15266241EDULL, 0x0C0FA4237C381F22ULL, 
            0xB55742D8F349E323ULL, 0xB44308D87C30ED00ULL, 0xA8ECB0F2E5864C80ULL, 0xBB6F5EDC70828535ULL, 
            0x372B7F3B6E62FD1DULL, 0xFA28D9F617300AB6ULL, 0xB8EE1C6D75B4FDAFULL, 0xFDA4F327CC4D6CA4ULL, 
            0xC5F0EE9A5B6A2448ULL, 0x969F4FD270682D69ULL, 0x28DDB37E1DF72BD3ULL, 0x4EA22B3FEEDC2095ULL, 
            0x192A7FB2522BEF75ULL, 0x62C44A6C814230B1ULL, 0xF7093C40E9B93A4FULL, 0x0FE05F1496229C00ULL, 
            0x916FBC8A6A0EB81DULL, 0x7D8DEAC37AE2F1B0ULL, 0x35857C93F7D809D6ULL, 0xCFCB61148EE9E413ULL
        }
    },
    {
        {
            0xDFCABFA6154FC098ULL, 0x9ABA7D0859CF2B64ULL, 0x0DE9E0FD7F7AE841ULL, 0xA8B987658904F638ULL, 
            0xEEEB3450620FAF40ULL, 0xA9EF177216B97976ULL, 0xD4AEC61B8804C819ULL, 0x4ADD0293FBC06A2FULL, 
            0x319CF40481455C76ULL, 0xA048C7E285A232B6ULL, 0x03029CF11FF1123FULL, 0x3C91A6ABC8497419ULL, 
            0xD48BA77345E725B8ULL, 0xDF466F26BBCF0894ULL, 0xC4F7B90DEFC0E512ULL, 0x399F4181C3933753ULL, 
            0x695E210F34B16374ULL, 0xEEF832D6CA3D6B63ULL, 0x73C397E6FCC52B76ULL, 0xB4BFF921CFCCE258ULL, 
            0xE6366E955639F1E1ULL, 0x23AF1E61EDDC20A5ULL, 0x6B15992F80A3B445ULL, 0xE14AF6037189B5F6ULL, 
            0x9463489AD4C95B9EULL, 0x0B644BC8EEE9BE33ULL, 0x274B01C52EE028AAULL, 0x00880E5104A2676FULL, 
            0x6911740EF1999FDEULL, 0x7CD06295B79BB6DDULL, 0x50BCE11DF3C3DE17ULL, 0x4F4FBDC0A077DD15ULL
        },
        {
            0x0FB6953305F6D670ULL, 0xC32FCCFCC0AFE0F4ULL, 0x41AE696F2DD32232ULL, 0xBFA14B9B3113F1D7ULL, 
            0x513E29C564754C1FULL, 0x654324A7CBE2C50EULL, 0x256D54A4A0EEA8D4ULL, 0x32F0414429D2EA3CULL, 
            0x2AF57B23731347A0ULL, 0x0455CFE00951FA79ULL, 0xE27D34FE43FD4C30ULL, 0xAB566976274CE2B3ULL, 
            0x4494197CF42DC428ULL, 0x67D4800C5233FD9AULL, 0x215CC36185054C91ULL, 0xEE6EC188D99BED78ULL, 
            0x74C3013F25E0A80AULL, 0x20A4FAA208C9E469ULL, 0x9A0694132A540F05ULL, 0x7AB7BF7D40ED9604ULL, 
            0x5B0FF7DC7F220DE7ULL, 0xAE56A7A8072EFA86ULL, 0x97B7C0A62FAB66C0ULL, 0xCB88999D1481D845ULL, 
            0xDA145FEA7363D76AULL, 0x912F91D18E19CDECULL, 0xF373AEFFDA512425ULL, 0xDCD5E6E42E100F10ULL, 
            0x1C00AB35088D8988ULL, 0xB49514A35F3F5BEFULL, 0x12712D18DCCDCCD6ULL, 0x33F83538DD21DD37ULL
        },
        {
            0x41E5AC3FE4DB2178ULL, 0x47CE2AE5AC3AE361ULL, 0x6F2CA6D1FD90384DULL, 0x55181D92EFDB3BB9ULL, 
            0x632C0D92E31B5409ULL, 0x3CCA819AD2355C26ULL, 0xBE9B35BE3E86F55EULL, 0x5944A71DF5465D9AULL, 
            0xC4688E107BDAD398ULL, 0xDA81ECE180C986CEULL, 0x48180660D1FE19D0ULL, 0xB3CE2D95E87B2BEAULL, 
            0xC84315B04E047250ULL, 0xE2E7310EBE8362A3ULL, 0x250F7174DA8C11E8ULL, 0x727D234C91F7EF58ULL, 
            0xF5DDD13AF90630E0ULL, 0x1E0C0BF39280E54AULL, 0x0A89F235567CCDE4ULL, 0xF972E7B4DEDEEE01ULL, 
            0xAB57002023CB92FFULL, 0x00C3724D681DB1D6ULL, 0xF89157AD2EBBB8B6ULL, 0x72D6E4F53D1D4D76ULL, 
            0x1BD23EFBA163DA25ULL, 0x1B91CFA0B7DD2389ULL, 0xEE376C4E94297447ULL, 0x7BA7EF26A2D09021ULL, 
            0x961B19C298E0DAFAULL, 0x7AB009F58A97FC05ULL, 0x8576D3E5A9AC2273ULL, 0x6F94F082D0FA7213ULL
        },
        {
            0x4615013D13C2E938ULL, 0x864AD4FABF2B0386ULL, 0x59DD08333131394CULL, 0x7BEEF5987F60C130ULL, 
            0xF35CCF20622A51B8ULL, 0xDB523E8816AE88FDULL, 0x3800DC87817581A2ULL, 0x765AE09AAB2E07C0ULL, 
            0xBC4C445D0B582C52ULL, 0x4D6E87A27D37B036ULL, 0x9C66154F6647DFACULL, 0xCF1075041D6ADAFAULL, 
            0x184C763DCFA11223ULL, 0x7D90B9B0E3937EE5ULL, 0xD66426D007FF7A9DULL, 0x07B4C0C9169207C9ULL, 
            0xF3C660D2DDFB4337ULL, 0x1C01EB1F9FC291DEULL, 0x96D2EB2CC2259A47ULL, 0x3691C6A67D1ADBC7ULL, 
            0xAFCA2D5804CC2268ULL, 0xFEDA3FB5682375A2ULL, 0x2EAF70414C067E07ULL, 0x82113C195169C2A2ULL, 
            0x50131190398E3299ULL, 0x716D546DE9728FF3ULL, 0x45A0A480B3A0DB84ULL, 0xEC9BEDA729D2A812ULL, 
            0xD4231F6F6E20E56BULL, 0xB735D6E338D5F0ECULL, 0xBE9C9D01D285CBE9ULL, 0x45441829DDAB1FA8ULL
        },
        {
            0x0640548FE7FB86D2ULL, 0xF9D9B242BA4971EDULL, 0x6A44525E51610F7AULL, 0x3DAF14E3E9515B96ULL, 
            0x359F8ACCBC6F6B53ULL, 0x1298414BD046A683ULL, 0x07C6025406F868A2ULL, 0xB4C9B70FE891C1F7ULL, 
            0x281ED3881E1EB3C0ULL, 0xBE2EA07BD92F901EULL, 0x736194283ED3C6ECULL, 0xA0D121B477246E41ULL, 
            0xBF6E8DD968982BABULL, 0xE10C0A4A28EE1E50ULL, 0x02D4BF262392878BULL, 0xD25637E7973E5813ULL, 
            0x8C0F860FCA4D06E1ULL, 0x583CDE1D8C7FD8EFULL, 0x4A41A0A3DA80F38FULL, 0x13B7F75FF321D8A5ULL, 
            0xB71901DEE56C311FULL, 0x7681DB6F294FAB03ULL, 0x721E482ED5AE5595ULL, 0x3393C13730E306E4ULL, 
            0x250DA87B4010A72FULL, 0x622CEB904D7DB5FFULL, 0x9D98B95286709196ULL, 0x558A659365A9E15EULL, 
            0x8B69241851D6A45CULL, 0xFF49BAECEB886503ULL, 0xC11AE65E5653282FULL, 0x9EA99C04B914BC68ULL
        },
        {
            0x92813D7BC88253B4ULL, 0x5E453D1007D586C6ULL, 0x8BB3D838EBF02924ULL, 0xB0ADC5D01CB9AC8FULL, 
            0x46AB195C0F43CB01ULL, 0x6B4CEB175CC932BEULL, 0x454ED42296FB23BAULL, 0x4A71877AD5F444ECULL, 
            0x1B2CB355FAD1A3FBULL, 0xF62C35F346AADBBBULL, 0x205F98C5F0CB46D3ULL, 0x334055E86D54502DULL, 
            0xE62C97EDC86B66DCULL, 0xE7421C8FDB649312ULL, 0x9529764767E337C6ULL, 0xBE34FD358FC2EDF5ULL, 
            0x292FC3E9A4AC9EA0ULL, 0x585D64FC87E74E53ULL, 0x406ADB1DDF3B6643ULL, 0xC0B96A9A1A79640FULL, 
            0x59E40604A79FEF03ULL, 0x0926022345A9C19AULL, 0x2912BB999D60BD74ULL, 0x8056510E05EC7B9CULL, 
            0xC8D9FB3AC41B7548ULL, 0x20DD2AD2A65A47AAULL, 0xC5ED20044215D6D5ULL, 0x2C84E6869E25F7A5ULL, 
            0xDBFA5F53BFE9D426ULL, 0x7E72896F45F48A19ULL, 0x586766B6099C0FD7ULL, 0x97F32E83636A3CA4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseAConstants = {
    0x3172E4D0EC994855ULL,
    0xB9002C8E054FF313ULL,
    0x66F2D6602207A72EULL,
    0x3172E4D0EC994855ULL,
    0xB9002C8E054FF313ULL,
    0x66F2D6602207A72EULL,
    0x56316BA6F2B51793ULL,
    0x015450065B8B3075ULL,
    0xE9,
    0xCC,
    0x9C,
    0xCA,
    0xA6,
    0x67,
    0xA6,
    0xAA
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseBSalts = {
    {
        {
            0x6CF84E062BF78FEAULL, 0xD75545FBC04E2C93ULL, 0xBE180A9C789C1F43ULL, 0xE2364FB76B00CB31ULL, 
            0xD39D10123389C7D5ULL, 0x3D1BA6B6295E6619ULL, 0x6870741FF7411446ULL, 0x48111C414146E971ULL, 
            0x502B5FFE2C9280E4ULL, 0x2F1E8ED463C06C29ULL, 0x208DF6B7A94E3D8CULL, 0xFF525C9A540BE46AULL, 
            0x513D291820EDA8D9ULL, 0x6ED4121E45E8C286ULL, 0x4CB9944D2E689B5DULL, 0x7B76DA27C1217FFDULL, 
            0xF2D0914A23C9BD27ULL, 0x9BB5C0EAA359CEE1ULL, 0xA07BB5B4972F7EDDULL, 0x6D25BC37D40FD167ULL, 
            0x5F40238C17CB47C4ULL, 0xB81D68BFC9C485E9ULL, 0xA6459AAF365DA0EEULL, 0x6B35361BEFF05117ULL, 
            0x91F65175C57F3F86ULL, 0x4A52955A5123110EULL, 0xBE6ED3D4C04F6C17ULL, 0xD8C8DE530082EE1BULL, 
            0x1D0E32D1AA1B34ECULL, 0x8CD46EAE1B759F43ULL, 0x805D89E5FD336BFEULL, 0x8AA5E8904B26B213ULL
        },
        {
            0x617FC9CC06FA3DA1ULL, 0x775879E9D4753CF3ULL, 0xA36630F7543AC79AULL, 0xE284E7870D41F996ULL, 
            0xFE614FBC2E64F847ULL, 0x980CDC096C0160E2ULL, 0x24659F94901D64FDULL, 0xAC8EA9941AC0FB39ULL, 
            0x64569ECF28EF1B21ULL, 0xA9B6E720F9E8E7EAULL, 0x31948D6F61C70102ULL, 0x2E438198479FA569ULL, 
            0x941DFDD228253EC4ULL, 0x7C82876BE9F3743BULL, 0x9773CA58A52EDBD9ULL, 0x6BC02F9C3BC28FBCULL, 
            0x56F0BF8B0BBDC778ULL, 0x8D53FB42181B7BA7ULL, 0x27E4D18F6F7BDA56ULL, 0x0D991F7E6D6F827BULL, 
            0xFE61BBCB08DD3E74ULL, 0xC4582C4611B00F6FULL, 0xE763F67237996C80ULL, 0xC9D64CA6C035D997ULL, 
            0xF4FBB81CDB664130ULL, 0xA05C22E9AD272F3CULL, 0xF63C9B9E5F1FCEA4ULL, 0xBA46F3C2517289C9ULL, 
            0x1296AF610194F64CULL, 0x6DD8BFACCBBC6BB8ULL, 0x296B5C389FD33B2AULL, 0xD4E20A7D2D61B4DDULL
        },
        {
            0x1469061995A40B0DULL, 0xBA0164266C74D181ULL, 0x3AD65BF75F49DD37ULL, 0x30C1730D1C57D68DULL, 
            0x13030734B087F187ULL, 0xCCA17EEC9551959CULL, 0xE7F766706881220FULL, 0xE34512FF211BDE07ULL, 
            0x1295B9396B24F3B0ULL, 0x1E61DCE6FA648E35ULL, 0xA56CCFD005AA0871ULL, 0x1C4F7AA37877CC81ULL, 
            0xDD97C6B05E9ABEA1ULL, 0x56D3D00AC2D9980EULL, 0x9B6ADD2FFAFEBA4CULL, 0x0C16BA6B935486BBULL, 
            0xFC01BCC5E0A6B93EULL, 0x8AA2E091F7D182BFULL, 0x7C4162375173DE81ULL, 0x019E2561A75F030FULL, 
            0x007B44A5A1FF8F66ULL, 0xFCA7BBFFDE6340D2ULL, 0x284654CB7AF0A15AULL, 0x01AB97F29AAD05A8ULL, 
            0xCAECE216C25DB34DULL, 0xFE242EB4FDBB33FBULL, 0xE7899C34271D884CULL, 0x49A7B7D628D66352ULL, 
            0xD9F0F1A6B2D00610ULL, 0x442C19581F537FDAULL, 0x48029933EEAA96DAULL, 0xBAAF39AD547B7005ULL
        },
        {
            0xF5C595C3A6EE3E8BULL, 0x46923BB1160A950EULL, 0x83A80A34B7B85FD9ULL, 0xA993F88F847C30F2ULL, 
            0x3B749377CB9F194DULL, 0x82E0B3BA629FACDCULL, 0x078597F8E57873A7ULL, 0x19D48DD95D5A32D1ULL, 
            0x7C12C68546F6906DULL, 0xDD8FA4A81ECBEC20ULL, 0x924AC439A21FC097ULL, 0xCB574A19F99F8D51ULL, 
            0x53EB9F123F85C5C2ULL, 0xDA5A4AD8884D7757ULL, 0x8AF528D24DF91FDBULL, 0x485F9259D2055368ULL, 
            0x67041E793E9CD38CULL, 0x7E931B6B875461DBULL, 0x7E90436B99E1DB46ULL, 0x7BC541B9ABD0A938ULL, 
            0xB967B20BCB49F32BULL, 0xF7A5B09955B9A823ULL, 0x01A6507B637C66DEULL, 0xB074DB26E54E36D8ULL, 
            0x9FA45B5D387C0748ULL, 0x3A9AB6050D93F7BCULL, 0x2A497F8291A1B421ULL, 0x6E4658B0C38E5C2FULL, 
            0x852F90978234ED0CULL, 0x6B100C3DE5E5DD96ULL, 0x622693DDA7C8464AULL, 0x89A08C536C2B6858ULL
        },
        {
            0x69CCDCB83C40C8FBULL, 0x354EE90FF47A3211ULL, 0x813C0FF31D23BE3CULL, 0x7D746902F7F3EEB0ULL, 
            0xAC7CC17ADCAD5A2FULL, 0x74A59A0D8613A74AULL, 0xBF7BED4871493998ULL, 0x861A26E959C1D8A0ULL, 
            0x895239AB95DCDF1BULL, 0x76B9DC9B2FB34D9FULL, 0xFDFD8A2908AD450EULL, 0x42F33F5CAB82B58BULL, 
            0xBF8D83C9F0302BB2ULL, 0x06B87D70D3F94D1EULL, 0xF82706DF545DFAA8ULL, 0x5251851D346DB626ULL, 
            0x7496AAF96702E9CCULL, 0x43EFD3436860DB4CULL, 0xE92D728D26BAA9ADULL, 0xFBAA0DC498D9C83FULL, 
            0x6F52D014D4242C97ULL, 0x209F511269FE767EULL, 0xC1D326318F545006ULL, 0x8DEB5D4A7B635639ULL, 
            0xF0C37BA19D283FD9ULL, 0x9870533745A24866ULL, 0xC92ECF91FBC75787ULL, 0x98E0EFA50A2A9014ULL, 
            0xE90352AA8A607406ULL, 0x69D33F2C3973A5FFULL, 0x6A308D54BFB6ADBDULL, 0x14BB2271C2BF8A8DULL
        },
        {
            0x5855E92BCFBA775CULL, 0xCA7F1EBBFB6A1899ULL, 0x7F9C316AAE6E2B54ULL, 0xD32EBC66D215F553ULL, 
            0x877F244DCA37A8E7ULL, 0xF6217F1F2C1DC6A4ULL, 0xF3DDB6CAC6959004ULL, 0x49A4BF4C081F3637ULL, 
            0x64B2676EAEC7C0E2ULL, 0x476C09C005C1D9CAULL, 0x95A94DA46010871DULL, 0x486AA29760363B0EULL, 
            0x4033B4A9FA622FECULL, 0x1A3B2DA2757E69F4ULL, 0xC6662AFBC454602DULL, 0x9BA1664303C92155ULL, 
            0xF89E4EB801FE78CAULL, 0x70CBCB65A87D85A8ULL, 0xFBB7869D12B74707ULL, 0x0660A5917DB1E79DULL, 
            0x9A5DEFD2E1380A78ULL, 0x709DB6364A703FA6ULL, 0xACEA52108DA794C8ULL, 0x87A4619931867DB7ULL, 
            0x00D325782EBD5114ULL, 0x052983C428928136ULL, 0x2DEAF918691A6C87ULL, 0xEA12267CC264A71CULL, 
            0x58F71993150AF35AULL, 0x30D089E0A8EB9B86ULL, 0xBFE35BE1B674F512ULL, 0x4C5FA55D012B106BULL
        }
    },
    {
        {
            0x2F9924E3B50AB467ULL, 0xB5D39463604AFE1FULL, 0xE1B948F47B0D5B09ULL, 0xDBEF2206EE70CB22ULL, 
            0xC1290DCAB11F1BE0ULL, 0x8CD20F9CD3D44580ULL, 0x90634FCE9EC66ECDULL, 0xC00F413D87043425ULL, 
            0x98319B0CB69BBCD5ULL, 0x1FC9E4EC4395A95CULL, 0xF100FCBD2FB63D5CULL, 0xAB2BB05AC7DA20B8ULL, 
            0xC9094E1AFF81FE81ULL, 0xBFD9CF3950B8B1E8ULL, 0x186473ECD83C5A9AULL, 0x5C624E713704F86CULL, 
            0xB4E0747647DBC2EDULL, 0x2FF18B193E56F160ULL, 0xB0E154A4DC3A68C8ULL, 0x3795A73977E33504ULL, 
            0x1A363A992A45E80BULL, 0x2A1A3A5A7ACBE5CBULL, 0x3A081FFF453D4A37ULL, 0xE8519260CDDC4CD7ULL, 
            0x2147DD8E04742EEBULL, 0x9A08846D0226C380ULL, 0x9096EFB22D7FECB4ULL, 0x5136F26A771F37F5ULL, 
            0x8A60C49E8FBA7D1CULL, 0xCF78CA497C10065FULL, 0xA5E335F13F44B893ULL, 0x92883D9B3C1E6D28ULL
        },
        {
            0x9CD813147A8F19AEULL, 0x8DBEC024676C3EE6ULL, 0x10233200C1AAAA0CULL, 0xAE0D50DC8562EC23ULL, 
            0x7B3796ACBFEFD548ULL, 0xEAA92D787AFE7AA1ULL, 0x8E5663CFD9487379ULL, 0x2ADD7E6EA9C61BCAULL, 
            0x69208AACB224D10FULL, 0x36EC1A4B8D8254D0ULL, 0x01BC6E53CCF0F73EULL, 0xD9A2A4A8CAD2D649ULL, 
            0x10CEA311BF5F6B52ULL, 0x61F7F6CE35EAF9F3ULL, 0x0EDF5017381D5738ULL, 0xEEC235481AB7E706ULL, 
            0x8C51E8E8E0D424E3ULL, 0x6B62F8CFFB078DEEULL, 0x161D640592A5E43EULL, 0x349F1E63284E7A6FULL, 
            0x3F330467736186F4ULL, 0x076F61759A16EDD8ULL, 0x3ACB0FCA9B623C63ULL, 0x414F9D32C06BD788ULL, 
            0x16B12868D0E1B123ULL, 0xE0A6DA0406993717ULL, 0x72E63FE2223EEFEFULL, 0x0AAF7AF31E6DF71DULL, 
            0xC0FCAEA42C0A0B95ULL, 0xB05F4CE5B24587B2ULL, 0xA2C1B8BD7CB17194ULL, 0xF9ADB1CE3AD19194ULL
        },
        {
            0xD92EDAF46F687E03ULL, 0x78BB252676D4EC95ULL, 0x0CB934576DB32B26ULL, 0x4B229371C9BFC858ULL, 
            0x0538034D8F9D2382ULL, 0xCB9F87E3FFA9FDD3ULL, 0x09A835E545335F68ULL, 0xE12F5AC9A2A160D1ULL, 
            0x5E6F507A49DED684ULL, 0xB83F0467A55EE080ULL, 0x50DE48D9669B29CFULL, 0x0CDF6C425FE530D5ULL, 
            0xA0EFFF4A094177E2ULL, 0x09C6AB27D4046E77ULL, 0xB041C523C7103D02ULL, 0x9C9F3ADF91860065ULL, 
            0x92C6541D9A68BAA7ULL, 0x1673E18091F24640ULL, 0x307B3877AAA73EB3ULL, 0x9CB124AC8C1AF90BULL, 
            0x29E949560CFF79D8ULL, 0xC3AD921985443E2AULL, 0x33873F5D9BB47EC3ULL, 0xA621F7F1699B8B96ULL, 
            0xCF075AA96EB38B0CULL, 0x7D9F335A213DFADDULL, 0xEC2AF38D4158CB9BULL, 0xA2E5DA03887F814CULL, 
            0x36A8FA334CED0012ULL, 0x991CAB11EF54218DULL, 0xE6AC153E4833F3E6ULL, 0xB56CDF52182042FBULL
        },
        {
            0x68FA1CDCCED8637EULL, 0x523662982F843366ULL, 0x46D6164B842BDBE3ULL, 0x61D95F2178A8ABB8ULL, 
            0x2E266033EAC590CDULL, 0xAE7D47BBAFC9C5CAULL, 0xD865FABAC8DE487AULL, 0x588CF1E92FA2215EULL, 
            0x95FD5413ED13EAF2ULL, 0x81BCEED923475215ULL, 0xD43E391E8149A5F0ULL, 0x79D6BFD674132CD4ULL, 
            0xB3F6A309CFB7810CULL, 0x7361AF98ECDFA591ULL, 0xDC5C23DFDB7ADEEDULL, 0x30FD84A8C4142520ULL, 
            0x4C723D25E37AAE96ULL, 0x199E10592E33F4E5ULL, 0x62CF086BA76BAB67ULL, 0xA5BC86CA3E81B8F8ULL, 
            0x5082F6101C5E1450ULL, 0x9020D7745DBC8DBAULL, 0xC766961D27D4CBF0ULL, 0x5CBF199BCB971B79ULL, 
            0x7720302C32963076ULL, 0xD356631970129DF7ULL, 0x23AE607F836079F3ULL, 0x9225245A90028542ULL, 
            0x877682AD239C9A7EULL, 0x168371C4C8DEE9CAULL, 0xE3B0E7EDF89588FEULL, 0xDF807DA048C0CFF1ULL
        },
        {
            0xC8DED31567C348CDULL, 0xDD7F578F8BDF1FCAULL, 0xA60FF5FD30106BABULL, 0xDA3CE0FDCC20B115ULL, 
            0x0AFC8AACA86A3DDEULL, 0xFAE6EB7C04AD23ECULL, 0xEE1E9D543462F335ULL, 0x376EB2D2BA3EBC4AULL, 
            0x2D05FF8A5F4142D8ULL, 0xBBDDB6C9AC842826ULL, 0x60A3E92F1C9F7624ULL, 0x044AF87472CE3BB8ULL, 
            0xAE0F7D96CD063902ULL, 0x680D7BE858A81B49ULL, 0x15A5DDBAC6920817ULL, 0xA438473BB5BD98D8ULL, 
            0x3C03A4384B2D2311ULL, 0x469690080B828F18ULL, 0x38C763A32FA37D8DULL, 0x9E4316972F47BB7CULL, 
            0xB058EE14347683F3ULL, 0x281970879D846992ULL, 0xB9ECAC6140944C12ULL, 0xB2B117461F477FACULL, 
            0x24F81AAB6F839192ULL, 0xFEB98BD5126EF2A9ULL, 0x7592BE8654586322ULL, 0xF6387725DBC687C5ULL, 
            0x73F25597B53B7068ULL, 0xED8F2DF37689D644ULL, 0x59C838D4F3270B96ULL, 0x4E1E7603BFF86145ULL
        },
        {
            0xE6563142FE4A3E34ULL, 0x1B7B7CEEE47094DCULL, 0x1894D53B83BE4636ULL, 0x6F65142F16505C18ULL, 
            0x6A7405B8B8322C9DULL, 0xA77D00497BC97542ULL, 0x99072BCB3EEA7660ULL, 0x11171F53FEDFD2E8ULL, 
            0x53F5FAEBD13D8114ULL, 0x429C4364A38DD9CFULL, 0x33679BE7033A543CULL, 0x89A155B9692F1BF4ULL, 
            0x2D8BDBCFC602728AULL, 0x02877E60B2B9607FULL, 0x33AE7436C0CDFE51ULL, 0x51D0E1F1BB1DBF80ULL, 
            0x1421F94915FDAAB8ULL, 0x608888CA3979BDCFULL, 0x231C2D25CE4F04FAULL, 0x1076FE1B947590BDULL, 
            0x53B372F25C2FEDDBULL, 0x2B23EC3D18459837ULL, 0xE1C698F6A6117A98ULL, 0xC0FAB548829B84EAULL, 
            0xC37BC9A6EF49E39BULL, 0xF42938E2BA64E526ULL, 0xDDA94017D19924CDULL, 0x8E3C1AAED1D923B0ULL, 
            0xB7733EBB2D3AA428ULL, 0xEEECABDA64BFAE26ULL, 0x06846129E144D83CULL, 0x0928ED2C42698730ULL
        }
    },
    {
        {
            0x172686D4B834F079ULL, 0x1CC4261265E93C0EULL, 0xC42CFAB5C7917F3EULL, 0x00B7DF9F71A9D188ULL, 
            0xC9B0A6EDBFCBD2FEULL, 0x00964C3FC042412FULL, 0x121F19AD0A800866ULL, 0x5FDEA1819D876A29ULL, 
            0x6210FD49E57D2985ULL, 0xB4548F79ACEDE415ULL, 0xAC31E938BCC492C5ULL, 0x37C91343D7E6431AULL, 
            0xCA37B83021EFABA7ULL, 0xBF52519CB55029B7ULL, 0x13FDF80220A2BE8DULL, 0xA743476372A7FAE9ULL, 
            0x7367B5D9345007EDULL, 0xD4BD7BFBDB767DB9ULL, 0x8D6709C9F640BB2CULL, 0x85615DC5B4DA9D45ULL, 
            0x5A9A9E803B9EC73DULL, 0xE497D9A96A962A5FULL, 0x0329E3AD7BA73DA8ULL, 0x78BDBFE35ED732ECULL, 
            0x2955A328E604F0EEULL, 0xA1FB5367C5C657F0ULL, 0x5277627BFB76286AULL, 0xE3E0CD8874BA4354ULL, 
            0x3ADE55C884A1DDB4ULL, 0x48317BC6BFD31FDBULL, 0x13254785D288ECE3ULL, 0xF6D31A9CC4D9DAAAULL
        },
        {
            0x75DD6CCDDE36C137ULL, 0x35FF2BA84083D34DULL, 0x13E105AA77CF6351ULL, 0x6BD01C1400FC2451ULL, 
            0xFACE1D69F32654ADULL, 0x897C42741AA99BA9ULL, 0x96F3B6E9EF7BCB3CULL, 0xCF995924D312EE33ULL, 
            0x9B3705BBAC4F930AULL, 0x7CC792354A80FBD0ULL, 0x3BAD5FA5EE2311D6ULL, 0x131E3CDF60479D92ULL, 
            0x296D7EC4F0D24612ULL, 0x55B1B148C09E924AULL, 0xFF822B0C1A5C4DB4ULL, 0x153DB684994841C9ULL, 
            0xDCB83D493CE6F7F1ULL, 0x9DADB7396A01A3CBULL, 0xE0A3D20707DC6A02ULL, 0x4F69FCBB888D961FULL, 
            0x5B3D66E741D7ECCEULL, 0xC39F7B31EA7C9D27ULL, 0x4884375621711856ULL, 0x3B38F30F2AB9D042ULL, 
            0x751003C0D33ED266ULL, 0x102A2653B0568544ULL, 0xEBB6A8D37462398CULL, 0x481DE475A8C1178BULL, 
            0x9963E5C5CB4C48BBULL, 0x47B615DA3C001655ULL, 0xE3846CBF1C79AF09ULL, 0x314E5259E48F24D9ULL
        },
        {
            0xF852524371FE6A65ULL, 0x62742C440705BAB2ULL, 0xF60B24DA0C6052A8ULL, 0xF974D38FF63EAE64ULL, 
            0x1FC76DC28956B5F0ULL, 0xD0EA7165BE909EBAULL, 0xE8A60941D103524DULL, 0x66F591FA60B51F77ULL, 
            0x50D15963CA88CC22ULL, 0x9B4EB655D3BE1F27ULL, 0xBDB5FD74621FAD87ULL, 0xCC941041B2730749ULL, 
            0xDA30217F82155421ULL, 0xC7F20946F7CC14FCULL, 0xA58500201DD9BAD5ULL, 0xB026D012691D7AABULL, 
            0x161D4A7E9455BD34ULL, 0xA5FDC7A3C63DE74BULL, 0xAAE0C2ED1AB25DCDULL, 0x2760A7C5FF099388ULL, 
            0xFECD480B758C56D7ULL, 0xB74F0D4D00F4A0F5ULL, 0x3BC29BAE502ADD15ULL, 0xFB0D5D6030D07947ULL, 
            0x05844A4AF556449EULL, 0x6AA69E7A4036D233ULL, 0x08B23B7A9CB6AFB1ULL, 0xF402A4D6D3C18B1BULL, 
            0x1911A08DDDB987C4ULL, 0x7DA2E54E0AD86A53ULL, 0xD4EF16265F753D05ULL, 0xB7716F808C819DB1ULL
        },
        {
            0x291B29EDC1ABFFCAULL, 0x7B508BF42C874B94ULL, 0x466C9B71E22BE2A0ULL, 0x6522C6D449959B6EULL, 
            0x25717FBF54EFA1DFULL, 0x4D38F82ACB5CD638ULL, 0xCAB539F6016987B5ULL, 0x47DF2BEB9007A96BULL, 
            0xA09204EDDAC3FB89ULL, 0xCBFF9DC100B1CB24ULL, 0x528AA14D82E162F9ULL, 0xAE7C4C10528D9F2FULL, 
            0x5A1ECEDA4B56F148ULL, 0xED9CB52377EBBF5BULL, 0x3A92621DE5A2C7F2ULL, 0x98B3DFE99B0F53E7ULL, 
            0xEE3E41D981ECE146ULL, 0x70D31D3FC4B7E5DCULL, 0x0F8DED61FD2499F9ULL, 0xAE403553C61993F8ULL, 
            0xB44BC5382E5CBF06ULL, 0x69C33A6D0BB496F4ULL, 0x9CA2F3CD6E3E21A6ULL, 0x4A748825AD3BFD6DULL, 
            0x06EB3BB5DB33F9B2ULL, 0x0756AD4FBCBF2308ULL, 0x6D8FC866F1A89E2FULL, 0x74C2A917D22A92BBULL, 
            0xC577B2627EADFFC4ULL, 0xD0865ECED2ABCC56ULL, 0xF1B49507DF436802ULL, 0xFEECE197CE5BFCD5ULL
        },
        {
            0x6035735D348D13EEULL, 0xB9AE558497E12A72ULL, 0xF4B4EBA9280F6A1EULL, 0xE6295C509E64F4B7ULL, 
            0x7F55975765D7AB9BULL, 0x49C534B9D74C33C9ULL, 0x94F862DE8F0AD0DAULL, 0x22703FAC84C31E71ULL, 
            0xCF28C2EF96521E0CULL, 0x45290949E37747B4ULL, 0x073FFCCAB495FE7EULL, 0x70FDC2B02144BBEBULL, 
            0x3AB1FDC1758C01FDULL, 0x359B2FEA938CEE2FULL, 0x3D5C1EAFB9366C75ULL, 0x95AD166E3BB5A4AEULL, 
            0x7FF73C3FD10C9A54ULL, 0x2906E75645A15B27ULL, 0xB9D7CC26493F847DULL, 0x87F097423EDB19FDULL, 
            0xBC4B321E43130209ULL, 0x0411C9D72C297320ULL, 0x25773AC37EE52723ULL, 0x9EFCA73D6C689467ULL, 
            0xA2AA1497648EADB6ULL, 0xFA7F06BD5F9143F3ULL, 0x0E2A4DDCD68E7C3EULL, 0x513C3527AEE7667AULL, 
            0xE4396461F37D5616ULL, 0xFB69D1ED49006E18ULL, 0x85E8A123F51D8674ULL, 0x51C051B38C2191F3ULL
        },
        {
            0x45754868D0F334EDULL, 0xFC3EF47C06775D35ULL, 0x3FD37A66F5D4F8AAULL, 0x5CFD861AFE1F8900ULL, 
            0x873E26B5A7A68F3FULL, 0x81401E64DF0056B6ULL, 0x0D6290A60EE7A7B3ULL, 0x0F254058B2EB0323ULL, 
            0xD956EF6E6D712493ULL, 0x65ABD6E029E6BB34ULL, 0x9E946B809D55569AULL, 0x3C848C9F30AE7850ULL, 
            0xDA616E46966D534CULL, 0xEF10B6AB0B9B7A2AULL, 0x83A5D03983F51EB0ULL, 0x8E37004506C025CFULL, 
            0x9CA9409D27A9E949ULL, 0x9CB4D115CAE72923ULL, 0x2674A0498D4717F1ULL, 0x53814F2B30DDCD24ULL, 
            0xB85C38958D620C12ULL, 0xED790654D4A72031ULL, 0x27115754A6CC96BDULL, 0xAFA57DC7060B763DULL, 
            0xA0DF60F28668D614ULL, 0x020B55348041B93BULL, 0xEDAEE6C731206CB7ULL, 0x20C349D817BA9FA5ULL, 
            0x66D855E2FE2A1A2CULL, 0xBD31C4472BBDB49BULL, 0xCDD11542D57D17A1ULL, 0x623D3255D4827A3EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseBConstants = {
    0xB3671063C2321E0BULL,
    0x1470FFCAD80D872AULL,
    0x183D9174FBDACCC4ULL,
    0xB3671063C2321E0BULL,
    0x1470FFCAD80D872AULL,
    0x183D9174FBDACCC4ULL,
    0x3CA354E75E5A867CULL,
    0x129ADECF4CC23174ULL,
    0x63,
    0x58,
    0xC4,
    0x46,
    0xD2,
    0x35,
    0x3F,
    0xAE
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseCSalts = {
    {
        {
            0xDD600252E815ECECULL, 0x588AA4F7226596D4ULL, 0xF15CB3C2AB5791F6ULL, 0xF4C7990174AA4EA9ULL, 
            0xEF903A4AA82CE691ULL, 0xBBE28873AFC90AA7ULL, 0xA068DA8782D5B760ULL, 0xD1BB8586E6AA3168ULL, 
            0x84543383314B458DULL, 0x8C88A7CE500863C6ULL, 0x21F43B0AB1429446ULL, 0x5AB6760DF361CDB4ULL, 
            0x89DB399F22C48CD6ULL, 0x223DA87ACFE578D7ULL, 0x109568409FD84009ULL, 0x5FF9DDB4505423E5ULL, 
            0x42C6630B9276A832ULL, 0xE496CC0B31309E02ULL, 0x44E3DF607B0CF183ULL, 0xFBF0DC22A1149011ULL, 
            0x4E6B511442931741ULL, 0xA00F078EEA8C15A1ULL, 0x904616C6EA001E8DULL, 0x3CA0C6A8ECCE3B79ULL, 
            0xE1052F1822A380D9ULL, 0xC02F08740DA76DA9ULL, 0x79133D9BFD0F55ECULL, 0xAD77C091651EAC2DULL, 
            0xE50A1729A6B92D87ULL, 0x4AE25643DB5E0B9DULL, 0x81DB332E8F6215ABULL, 0x39FDE16689481A63ULL
        },
        {
            0x6BC3DCBC6CA2CD30ULL, 0xB60616F1D626A42EULL, 0xFB6C1C63A0A6585FULL, 0x6E8C3169ADE6469BULL, 
            0x7FE6EB38F55D8810ULL, 0x784F9DF2D839F89DULL, 0xC118EB6B511DD8AFULL, 0xE6F5439C0FFE190EULL, 
            0xFACBE4EB06514B3BULL, 0x11DB595981E2D3EDULL, 0xB9D3E555D048475BULL, 0xB402778E7018E7FFULL, 
            0x8A073130CE485115ULL, 0xCC173CA56EDB64DCULL, 0x9714BC57F8CCFD99ULL, 0xC5067D5D359AA129ULL, 
            0x29BA175F9A2948BDULL, 0x59E8CF6B8E53116DULL, 0x9EFA6AD8033CCE74ULL, 0x2D200D73BA34616CULL, 
            0x998B1619BE4C08ECULL, 0x2B3D94AA2021FD06ULL, 0x6BB72B2D50690D63ULL, 0xEFBB0B97A6441C6DULL, 
            0x7E16C455E67089E1ULL, 0x1BF309B940153D52ULL, 0x6A75AEA2FD832C1DULL, 0x75493170678D51F7ULL, 
            0xF4106F5442D6FB69ULL, 0x26088C380FC901EFULL, 0x4A0C16AD528F282EULL, 0xC2C4EF299EEF687EULL
        },
        {
            0xD91521A502684CCAULL, 0xDF72E6CBBC704493ULL, 0x458408B748001C41ULL, 0x56A2339E6827A7DBULL, 
            0x3FA19D014A9CDB87ULL, 0x723A91F4F432B425ULL, 0x54AE02CE48775B2CULL, 0x1087565E9C58C286ULL, 
            0x4CB178ED1C46C242ULL, 0xDEE324FADE161F06ULL, 0xFE69D5713551E477ULL, 0x8D1B4800ACE51ECBULL, 
            0x3A0B9C0EFD63753DULL, 0x56F445B00A47A84BULL, 0xBBF42FA01A0EFF22ULL, 0xB926CE0AE4139071ULL, 
            0xEA0741D4B569EFCCULL, 0x80421D6AD7C992E4ULL, 0x287B8194F1BA50FAULL, 0x70E731CC6C56394FULL, 
            0xFAAEEA882DBE6DBCULL, 0xF716F817F40791A6ULL, 0x36BB836EB4AA6EA8ULL, 0x4EFE49F10428D045ULL, 
            0x6FC97AEBB63F19EDULL, 0x3EA5A6767FC066FFULL, 0x69D0CC55FE2D856DULL, 0x35FF8A453AED062FULL, 
            0x85416A71B309CD8DULL, 0x12E7FFA64A71EA93ULL, 0xCBDD1954B4A2E40BULL, 0x6A2693160331C208ULL
        },
        {
            0x4E0126A6A9A65868ULL, 0x9B5D133B0932C26FULL, 0xB91695A92CB56062ULL, 0x58B1BA2B6FB40D80ULL, 
            0x87ECD6F88AD48BEBULL, 0xA48A04BAE06990ABULL, 0x824BFD302032A5D7ULL, 0x506851C72D52F1B6ULL, 
            0x3B669D6E2E79D6FEULL, 0x435BA02EA000D7BFULL, 0xCF93D192677268ADULL, 0xDDB09E54CF2525F5ULL, 
            0x2C80E436F39D9A24ULL, 0x0C28A7B47B6FF4AAULL, 0xD999CA218C24DEF4ULL, 0xC75FAC253F46CAEFULL, 
            0xCCF7054F3D8E037FULL, 0x270AD9F2F95B697BULL, 0x46624865834B7B10ULL, 0x625152CF5976BD18ULL, 
            0x57813F01F8905DF3ULL, 0xD2DF59A7B43749ECULL, 0xA0C5B24E85F6D717ULL, 0x7E7EE0F60FA87A11ULL, 
            0x959A9F0BD7EAB311ULL, 0xA48C57EC45E1BDC6ULL, 0x3504327973904B2FULL, 0xDD21BBEEF3B4F006ULL, 
            0x1638FF5D715CD548ULL, 0xC8824C9A5B42B249ULL, 0xFC872459609C38DAULL, 0x4AA3AEF46AAD6D8DULL
        },
        {
            0x01B2EBCBB1E6FBDBULL, 0x3E056DD371D086EFULL, 0x1C1D7820725E4CF9ULL, 0xEFAC243415FEEEE5ULL, 
            0xF56651214281B4F4ULL, 0x7145EF585AFCFDEAULL, 0x5E5532588FA070C8ULL, 0xC475EC64F0263C18ULL, 
            0x2937AC24888C729CULL, 0x8E159AA88675FE27ULL, 0xED6AE3B2C1477013ULL, 0x5ED644FD5A3478B2ULL, 
            0x38879B84530F6DC6ULL, 0xAF8C562201363961ULL, 0xCA50374392EE5A41ULL, 0x2CE1553471D01145ULL, 
            0x40717AB631D8D959ULL, 0x10905554FC9F4DDAULL, 0x4F02E165146D3A76ULL, 0x94B93F3A515FF95FULL, 
            0x1BB4E4B056AB2ACCULL, 0xB2B7DFE9CF3AD98CULL, 0x84DCD6788522F1FBULL, 0xEEBA48354FE3211BULL, 
            0xB4EFBB2C3CB6F952ULL, 0x2A3AAD7EE5B3CF17ULL, 0x8105BA3C5AA9F2C4ULL, 0x1298C3979DD382A2ULL, 
            0x068C5F3C839628EEULL, 0x279C13C7E1E320E9ULL, 0x24F5F95FEF3064DAULL, 0xCDB19606208F5264ULL
        },
        {
            0xB9A650BE1EE6C38EULL, 0xB877F943B91910D9ULL, 0x3F47DC4C89B71AD5ULL, 0x676C74C51B85F6C0ULL, 
            0xBE38B33A1C01A4D5ULL, 0x2B4B926A7DE4A523ULL, 0x1C2CA4331C7029E7ULL, 0x61AB7BBDB1B80C8FULL, 
            0x98FA55CFC071EF1FULL, 0x5F94D52FC164BD41ULL, 0x68EB923658F72000ULL, 0x053C2FB46006C6B2ULL, 
            0xFB6356AF6496FE8DULL, 0xDA6F63650F228770ULL, 0xF33E83DC5ECE5905ULL, 0x7A3040A770C2C415ULL, 
            0xF05230A04E3CE53DULL, 0x8A20F9F178D56783ULL, 0xF158F6209C6540C7ULL, 0xFA3929125E86D12AULL, 
            0xBF250A6179ED67DAULL, 0x2CC6EEB647BD7A63ULL, 0x29DFD5BCE1D5A55BULL, 0xFBBA5F26722A3A67ULL, 
            0xAFBC004CFC2F4359ULL, 0x13A1B847AD216A95ULL, 0x51BB1315DC4AECF0ULL, 0xD9E8E734532DEB3DULL, 
            0x2495947024C65EDBULL, 0x879A64392BF4E77EULL, 0xB6A15C767203FF70ULL, 0xEAB7F49FB1C10041ULL
        }
    },
    {
        {
            0x52E9F23DDDFCE470ULL, 0xDE73EF5D161476D2ULL, 0xAD0F8A73789C6F73ULL, 0x21879A7435FDD517ULL, 
            0xAA4293806101DCB7ULL, 0x8689081FFF0F58A2ULL, 0xB09F58B5973D1FDFULL, 0x2F3C71CDB51AA0E8ULL, 
            0xC1B9A0B94F9236C3ULL, 0x8A079F2C88819FF7ULL, 0xB0EBCBE34B82054BULL, 0x9F78A6410F44DB13ULL, 
            0xF7AE4742212DEBD7ULL, 0x8FDE7DE25C6A193AULL, 0xAC96FEC62CB7D54EULL, 0xBEEEEB512AE30B05ULL, 
            0x1653D81E3DC9EEB5ULL, 0x8E1F55A855DE2E17ULL, 0x97D89B8B34ECBDF6ULL, 0xEF08E3451A4CFA13ULL, 
            0xC84A742AA6DCB622ULL, 0x0563CDE99443C6CAULL, 0xC8588684295D8EA6ULL, 0x93417E149AB69480ULL, 
            0x53F9F258F5FA26A4ULL, 0xCC6B1EE006186FB4ULL, 0x07C0B327725E21BDULL, 0x4621595D118C9CB0ULL, 
            0x7E8E7D227A10836FULL, 0xFEE938B316D45F6FULL, 0x53382F2D23E90FE6ULL, 0x3EEE5951AC7C5451ULL
        },
        {
            0x3E33B3953D8891B7ULL, 0xFD25A32634871419ULL, 0xD61B4FF5718F27F3ULL, 0x6FC6160063F3EAF3ULL, 
            0x890E86BCA4987C1FULL, 0xECA15956AF07C867ULL, 0xFAF85849572244CEULL, 0x87264CEA8B54AB31ULL, 
            0x507487F2A2A6A3ADULL, 0x8E1F4A697F2239B8ULL, 0x7060726E5BFF31E7ULL, 0x276E018E6D2D61AFULL, 
            0x2DA2320803589AE6ULL, 0xC718661E3CFB058AULL, 0x23B238F9380445FAULL, 0x81BEB0CAA89A560FULL, 
            0xD7CC979262AC3F55ULL, 0xC15DC6EF1038284CULL, 0xB47B6724C23EE738ULL, 0x1B367CDE48DE03F5ULL, 
            0xB77B932BE9346D4CULL, 0x85DD62784F06F0D7ULL, 0x36871825C05F7005ULL, 0x3EDF1A9FC8E2AE87ULL, 
            0xE905731C5ED91248ULL, 0x73D4C9C5D5CB71E0ULL, 0xC6751374C57709BBULL, 0x65DA5F5DBBC8D186ULL, 
            0xA43B356F53A4594DULL, 0x8B56E3384F27C38CULL, 0x27FD6EFEFFD80037ULL, 0x1E79625879185EF2ULL
        },
        {
            0x8E6F05D720349B33ULL, 0x40B5CF7FF5685A1EULL, 0x8D9A6124069BAA16ULL, 0xBA7553254ED1AB5DULL, 
            0x07FFD44CBC20CEA3ULL, 0x38845C4C8E4B722CULL, 0xCAF532313733EA8FULL, 0x9368666BF07517E9ULL, 
            0x7371CC056DD540CDULL, 0xB843FD135288A2CCULL, 0x54D1C58C4277B88EULL, 0x0BEE3DE786DA252DULL, 
            0xFE10D7F412FA9CAAULL, 0x1AF46DBCB5BBEC25ULL, 0x8C9B249DE4E8CBA6ULL, 0xD53B719BF362B429ULL, 
            0x72163003ECE4A317ULL, 0x8EBB0F9D096DEB78ULL, 0x6878ECFE91BAA7E8ULL, 0x0047A9A9B10F3B6EULL, 
            0xDE1A942A00DEE724ULL, 0xF95AA8DAB8C1EC12ULL, 0x9C9E80AC091DBE13ULL, 0xD72EFA0B28CBA038ULL, 
            0x9AB92590BE742CE6ULL, 0xDEB09F67A85EE655ULL, 0x0C0E237542364160ULL, 0x19A2548DFE65119BULL, 
            0x9F5DD00E50A6A4F3ULL, 0xBA8013447E8997F1ULL, 0xFCACF489D479BDEFULL, 0x3104B004AA2AC15FULL
        },
        {
            0x5D3B01F7CFCA4035ULL, 0x2C96B8DF9558BEB2ULL, 0x95E1C0C06D1EE976ULL, 0xACA12FEFEFACCDACULL, 
            0xDCDDD18C2A44CADEULL, 0xED670D5FCE597761ULL, 0xD9DD6C4E31EFA06EULL, 0x56B5CF04C0484378ULL, 
            0x67100EEA0EFC1A9EULL, 0x67EB4F86D978D5A0ULL, 0xDAC64DFF6E5AC9B5ULL, 0x13BB078775B02F67ULL, 
            0x10F3625D06C39804ULL, 0x3B7D7F8AD2F724E2ULL, 0x8AAEC160BCEC62F6ULL, 0x90C11C20ACACD1B0ULL, 
            0xBC0F02B4BF274721ULL, 0xCC846B3F817C5B44ULL, 0xA30DF9F660C833DFULL, 0x2AB27B90C41658D4ULL, 
            0xBA0DFD5234368C91ULL, 0x46E114BE6F1C8D54ULL, 0x3FFDC634B9F66365ULL, 0x294A477EA35FB61AULL, 
            0xF58448E45C3EE6E1ULL, 0xBCF33D19C0E2D913ULL, 0x2591A206A2E298EDULL, 0xBF02D7DD0DF55355ULL, 
            0x72CFF04C0975039EULL, 0x45255F87D7C6E251ULL, 0x223B91F313F18DC9ULL, 0xA5612C4457C7F3EBULL
        },
        {
            0xDF626B22105E975FULL, 0x9D98DD8C5A3D5D6EULL, 0x2A78AE42E7FC090BULL, 0xD0D126FC0EDCCE48ULL, 
            0xF1ACCB6DA341AE96ULL, 0xF53FC7A7AD72B464ULL, 0xD4DF0556F48A58E4ULL, 0x50D2A75695608567ULL, 
            0xB56BED225FCF2118ULL, 0x255BE20C4A82D364ULL, 0xB73B8BC4B8CD602BULL, 0xE33A500DFB5EE02FULL, 
            0x8CEAE37EC3F38B9FULL, 0x1418EB69A640FF5AULL, 0xE6E74977E0F83366ULL, 0xBCE79482D9377EF5ULL, 
            0x04C2EDA3836C913FULL, 0xB503A1ACE08AB2DCULL, 0x4F0D6422E6D6AFB5ULL, 0x632781A3431BB43DULL, 
            0x5FDA4A311670ED09ULL, 0x94BC2FA40A5F6283ULL, 0x4D76EB8407BA0BE7ULL, 0xEAEA7840DD961448ULL, 
            0x11BA6E17C186B142ULL, 0x1B43F1FB082D4B1BULL, 0x8EC10F4ED900C1D4ULL, 0xFBB6ADEBC0E42E2DULL, 
            0x1F99A2FD5AA2560BULL, 0x37392A8C3D1DC650ULL, 0x40AB08BC9459467AULL, 0xA6A3AD3828AB9780ULL
        },
        {
            0x1CDB5B99602361B7ULL, 0xF61D93A5921F2F0AULL, 0x4473569B1F28C23AULL, 0xE703FBE3E2D2AF48ULL, 
            0xB98DB6660F674F3BULL, 0xC79F780C0DC6043BULL, 0xC3E3159244A6E8B1ULL, 0xEC2DE44AE3BF6612ULL, 
            0x560B9F54232ABD73ULL, 0x8D1F558403AEDBC0ULL, 0x2BDFD17EED2B0178ULL, 0x12D28FF9373FF8F2ULL, 
            0x5D363E007606C19BULL, 0x7A5DB045E2E1111AULL, 0x61A7A0323233D946ULL, 0x27663D5BB4852DEDULL, 
            0x9736752E3349E9E9ULL, 0x80B2378DF9A2CD69ULL, 0xDB9A0094E16D4667ULL, 0xE1EF0AD336D1916DULL, 
            0x1E47E672B550E70BULL, 0xC2F838AE1344D7F7ULL, 0x22A4A19082848764ULL, 0x5D9CBFCDEF9946A0ULL, 
            0x63FA81F887F75CE1ULL, 0x940DAD7AD9DD693CULL, 0x8BC3A8719860DE41ULL, 0xC000329814C418B6ULL, 
            0x3B1CB1FE57CAD338ULL, 0xF7C2909E3376037DULL, 0x78D4279768436AE6ULL, 0x81CA9C84177DD4E9ULL
        }
    },
    {
        {
            0x56D8F3E84398CA84ULL, 0x29BD3BEDFE05F6A7ULL, 0x236D1C0B75989605ULL, 0xCBA259559BF8B5DBULL, 
            0xF23690061A5AD154ULL, 0x2F25B39B835D49F0ULL, 0xEF5E246E2C6FCE8CULL, 0x42368B7AEE1D6939ULL, 
            0xA7C51BA068D780DDULL, 0xD8889CD419450C53ULL, 0x0BCA30BC25511547ULL, 0x54DCB439D270353CULL, 
            0xC4C055891201265CULL, 0xBA8B2CF45EA29C24ULL, 0x9F19C81FF7EF5C38ULL, 0xAF08BFD20A25FF60ULL, 
            0xE52152C53C257A32ULL, 0xD7EF9946AD84B001ULL, 0x8B948968F4F6227DULL, 0x540AE08F3B521DC7ULL, 
            0x2945107AB3490BFFULL, 0xBBC7CE0D1D09D2D8ULL, 0x6DA35BACF4FF1516ULL, 0x9FA3FC9B91B57203ULL, 
            0x2D279A09C0AF6B1BULL, 0x3C34D5B8D5AB3294ULL, 0x0565FEE1A415F341ULL, 0x13FB21DA4D64700FULL, 
            0x2780BDAAD9D2FF02ULL, 0xC5631CC3FFA04C8FULL, 0x322365DA374FDA11ULL, 0x51774313DDF3B5B6ULL
        },
        {
            0xC1865F1A69C9B916ULL, 0x44E87D69F5E48A9BULL, 0x8869936C62EC9DB0ULL, 0xC5A27E05C4506C96ULL, 
            0x7CA101664DE7C369ULL, 0x86D996B18AA9153AULL, 0x099CF7FF6276EEF2ULL, 0x42D56A5AF31A2488ULL, 
            0x45941BA22428D45DULL, 0x0ECCD402D7FE4547ULL, 0xEDF909B683DC7C73ULL, 0x02EE19532D9F6000ULL, 
            0x38359C1772A2AEB9ULL, 0x0B6F4220850D959EULL, 0x0876F754117AEC76ULL, 0xF83938E12072858CULL, 
            0xE0CD0E8323024CE4ULL, 0x983BDBF3A2B44C89ULL, 0xB0746CE20FDC0ED0ULL, 0x69CF17A0E9440F3FULL, 
            0xCB603FE1615F576AULL, 0x848F1C25626A4356ULL, 0xD9EB034B75547FF0ULL, 0xBCDA044715660AD6ULL, 
            0xF9730A8E52A7A95EULL, 0xB19107351D12EA83ULL, 0xB2B0AADA173DEF2FULL, 0xC144E022FA35B71BULL, 
            0xC030811D46C19E3CULL, 0xCE6D16A4C7C05B48ULL, 0x62555DF5065B17B3ULL, 0xF79C6078893590D2ULL
        },
        {
            0x7121B729293EA1AFULL, 0xD21853903458E0BEULL, 0x87F212A22F1D3141ULL, 0x4429779971684DC8ULL, 
            0x83ABDC2ADB848E41ULL, 0xEF5DCB8F9DD6DD15ULL, 0x5599D4FD379CF533ULL, 0x3575CACDBA3184AAULL, 
            0xF3507D7754383B6EULL, 0x681F98A2BE1DBEDCULL, 0x62A755C84AC812E3ULL, 0x7A1D183969F4ECDAULL, 
            0xBA6BFC8A5A22B95FULL, 0x452D9D59C484830DULL, 0xD2CBF5C57C994CC1ULL, 0x96B844CF3C42C497ULL, 
            0x701FFE1199AF89FAULL, 0xD568F94872768EEDULL, 0x99B8E419121E47FBULL, 0x24701FA68479878BULL, 
            0x2C5DD3D10A8EE31EULL, 0x520C1281A84A825EULL, 0xC297389DBD7AD695ULL, 0x81D225AB44CC1A26ULL, 
            0x273132A524171C61ULL, 0x3F1C5ACC40202639ULL, 0x8CF33B1CF66BD38EULL, 0xA5E62ABB8E8A656DULL, 
            0xA7C761C64F1400E2ULL, 0x036964F6FE68562BULL, 0xBC344D832DD1E5D7ULL, 0x486A6E920C91CBDFULL
        },
        {
            0x8EAA17D6334762C3ULL, 0xE4BD80B9FD9C4379ULL, 0xFF07AB5BB0247322ULL, 0xE79138693BDDE8ACULL, 
            0x6967A5C92A0D27A1ULL, 0xD2760A16C653A8F3ULL, 0x8E0EC811BE42D81EULL, 0x9D5A78DE097EDE55ULL, 
            0x162EFA4317DCA776ULL, 0xFEFEF52B615BC4B5ULL, 0x3F46E080083D2222ULL, 0x7F96BE6FDA977877ULL, 
            0x8490E33B0E2D67E8ULL, 0x9EC1B40EC692DCA6ULL, 0xA764CCCFBE6D37A1ULL, 0x20016159872CA6C0ULL, 
            0x75151A34B9188B51ULL, 0x908F083237DE0E6DULL, 0x06E35BA50413E9D1ULL, 0xE8AA0C6C0786B8BCULL, 
            0x1ED782E8722BB3D1ULL, 0x8C8D5B507550B79FULL, 0x26FF1E4FF6F51548ULL, 0xD03DF4F24DDA51D1ULL, 
            0x6E93CCF1060ED418ULL, 0x49476198DCB3A340ULL, 0xEB64B4E21A4291FEULL, 0xB6FBF0F9F515157FULL, 
            0xA3E98540059C3D02ULL, 0xC9D867DBE19FB9FFULL, 0xAC474534A9848594ULL, 0xD983DF98AE96B7BEULL
        },
        {
            0x9BEC1FC5032F6371ULL, 0xC1F6C424409DADD3ULL, 0xE121FBE6F09BEFC4ULL, 0x6907283E4027EAB5ULL, 
            0x78FDCE390383E17CULL, 0x6BE9D701148765C7ULL, 0xF883A2D15F853EA5ULL, 0x76200AC64261FB8DULL, 
            0xD177AF5D80A6E3C7ULL, 0x818CC630E2E1FAEFULL, 0x9154B82D26B2EB88ULL, 0x813FE556EB144B55ULL, 
            0x20177F0615B2D514ULL, 0x74D5D2FBDF8474F5ULL, 0x44465D4D086A6573ULL, 0x3F31A44D157FDA61ULL, 
            0x3472BC8A31F4E2DDULL, 0xEB2962CEEDC19262ULL, 0xE7F2C55B032707D4ULL, 0x06596EA9FF1EDDC1ULL, 
            0xCC7FDE0B5FFA5D15ULL, 0x8DC002494E5AF197ULL, 0x4DEF35CBFC7D3B50ULL, 0xD2381AEDEB98F5B3ULL, 
            0x55CC0ECCF223947CULL, 0x17D6F841C7126A22ULL, 0xD65F6AE4FF76BD4AULL, 0x2461DD1568B6C468ULL, 
            0x0C878DBED54665B3ULL, 0x20E746E22E997B3DULL, 0xD46AE0D1D3E5E324ULL, 0xD63EE872D351DC84ULL
        },
        {
            0x4A0C477B8BB2ADA6ULL, 0x35E2BCC833B68376ULL, 0x412C2638EBDF4FC1ULL, 0x17438844FAA5056BULL, 
            0x335FD3344F64DB75ULL, 0xE8727ABF7B8EB79DULL, 0x7C7EF3876566B4DFULL, 0xD02FCDC4281FAE87ULL, 
            0x5FB8799253EAF14EULL, 0xF6B5C5C1EA6A8BF9ULL, 0x3E6F0588CF216564ULL, 0x8F506A006252C3AFULL, 
            0xA77125617C053A15ULL, 0xD26E849EE46FB330ULL, 0x920B9B20EA76D7F2ULL, 0xFFD29F678847596DULL, 
            0x0E0918436284EE49ULL, 0xED6B888E99E70960ULL, 0x7204EC279D1832EBULL, 0xA2183D0442A7A4A8ULL, 
            0x4AD4E770F1746883ULL, 0xB7DAA7DDDC529982ULL, 0xC289F48975087DBCULL, 0x5040F5AD3D6D1C2EULL, 
            0x49B6CFF9527E7D2CULL, 0xD4F7426CB3E5C650ULL, 0x2EF0F37D30D82C61ULL, 0x725D8D3BF5D63F77ULL, 
            0xD968B0583A023CB4ULL, 0x460D05DFD2A1B055ULL, 0xDFD5F3EDD22859E4ULL, 0xD20048171F74AA89ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseCConstants = {
    0x99DF80F8E7DFF2D3ULL,
    0x4CE4FFF59459B8B9ULL,
    0xEEBB765A83772EB1ULL,
    0x99DF80F8E7DFF2D3ULL,
    0x4CE4FFF59459B8B9ULL,
    0xEEBB765A83772EB1ULL,
    0x1326FF5085ADA5DBULL,
    0x8305ACD11D62960EULL,
    0xF0,
    0xC0,
    0xFC,
    0x1C,
    0xE5,
    0xEC,
    0x0A,
    0x5A
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseDSalts = {
    {
        {
            0x085B7471812131EAULL, 0xCD8915F649AF8E72ULL, 0x9783F8C9624F5794ULL, 0x1B83B2507FC35D66ULL, 
            0xB25DAB2078EE820FULL, 0x1AE0C15ED6D83E46ULL, 0xFC8F35CE6CFD4198ULL, 0x35EE3504968C641FULL, 
            0x7FBE61B7BAD846C5ULL, 0x5231381C78DCFEFBULL, 0x4DE03AAD656FDFF2ULL, 0x6C3B3306B82AB456ULL, 
            0x41C885036950AFFAULL, 0x00782044A1E2DC4FULL, 0x2E275023FA6F195AULL, 0xECFAFF05A0A061DCULL, 
            0xC6FF3D5EBF645B26ULL, 0xB4B87EF64A0BC914ULL, 0x8F649E79733E5AE6ULL, 0x631F686BF92D4B70ULL, 
            0x5CFFDBC43657B94CULL, 0x291834837A526620ULL, 0x9D15FECE8DB17665ULL, 0x995A6914CDA1AEBDULL, 
            0x0A55EAF7632F2328ULL, 0xF0A57386A2F054E4ULL, 0x4A3E7C09D48624B8ULL, 0x455F4755CE5B9BA6ULL, 
            0xC82F031C3F2FD506ULL, 0x3F53AE0E60638FE5ULL, 0xED09226426D59F26ULL, 0x09B72C6743CC8284ULL
        },
        {
            0x40BF6FD1EF3E44FBULL, 0x0FEC6525860845A7ULL, 0xA6DB169AF437E619ULL, 0x8AF4F23B38895FA8ULL, 
            0xBF02D143911758A4ULL, 0xC8874C87182A2073ULL, 0xAB2DDAB1F2CA6990ULL, 0x8DC6D56EE25FA8CAULL, 
            0x1DC041524D2BA09AULL, 0xF9414D4768F77303ULL, 0x9AE793431F87B6D6ULL, 0x07ACCBE5DB851519ULL, 
            0x00E263924E4EA430ULL, 0x8C40EB267F5E67E9ULL, 0x519CF147F62529F9ULL, 0xECA0298D745CB5E2ULL, 
            0x0D62E311CB44B898ULL, 0xF43CAE6A57A05AB5ULL, 0x1F9E0CE745F08AE9ULL, 0x6298C59FFA602915ULL, 
            0xC45DA4CA7D17270EULL, 0xAFCB226B6F07A5BCULL, 0x6EB4D2ED6A489D75ULL, 0xCFEB798F1C394B9EULL, 
            0xC154ADCD23F7BFD7ULL, 0xC82549BD2C8C853FULL, 0xF4068F41D9A106ECULL, 0xF16D15BC204E2F26ULL, 
            0x0834A52D6A059595ULL, 0x232C8E5DD17BF19CULL, 0x04708939D4900C52ULL, 0x64C80CEA62B09EF8ULL
        },
        {
            0x4C811B2948CF138CULL, 0xA7478CD42873152AULL, 0x7BDC592761E175CBULL, 0xC5DAABE86BBCF08EULL, 
            0x3A9382D4F6785DD1ULL, 0xAC528D4D4F472197ULL, 0x0B354A9969E3E49CULL, 0xBD3353806A7C46B2ULL, 
            0x0AD3F0F59A5DAB69ULL, 0x10AD4072BA9EE1F9ULL, 0x670E425491C15629ULL, 0xD69362D25E00AA8EULL, 
            0x03261520FD7B88D9ULL, 0x0F7381E63CD24544ULL, 0x4B70E597E916131AULL, 0x6A8A0A659C42E074ULL, 
            0x9087E80BD4EE9A95ULL, 0xA389D29B890D190AULL, 0xC677B00712704863ULL, 0xC548733E34B1E99DULL, 
            0x0104EF7CC5AA4BD1ULL, 0x80F40CE1A9BA3735ULL, 0xA53E89669CFD3B33ULL, 0x4D073D20E8134F28ULL, 
            0x6A1A9805CFDE7CE9ULL, 0x2AA2A6EF9EA6DE04ULL, 0x83D0EEA0135E104BULL, 0x6FBCA21E11BB6A96ULL, 
            0x49ED6CB8CB35E4C6ULL, 0x2A2FED64F6581BF1ULL, 0xF7C45CCC4C4AB82DULL, 0x89DCBD7265E0244AULL
        },
        {
            0x4A7531B750FCD4A7ULL, 0xE0C6F140111DA356ULL, 0xD24AAAB2D2F4DD2AULL, 0x0C37BB70C83DB4BEULL, 
            0x3798D4FE4BCD3887ULL, 0xEF8E3BA107B7539DULL, 0xB0CC0DEC42CD137CULL, 0xDD6BCE248350B703ULL, 
            0x8EF62B69B3F3D956ULL, 0xFBC02BFFE1FF4FF5ULL, 0x5E20D8595168EBB8ULL, 0xE980BA9CD8933D88ULL, 
            0xEAFF81C903B58E71ULL, 0x9FAAB8FECD0F00E4ULL, 0x87A7520EA3605CB9ULL, 0x266BB1E2AC0F640CULL, 
            0xE83A930B02872D4AULL, 0x9610F03DA1A5C592ULL, 0x9E8DE6AE0A1CE479ULL, 0x590EA5FEDA3FD966ULL, 
            0xAC9030BA02F02200ULL, 0x55516E9A55D4FA2DULL, 0x73DF12BA7762EC3EULL, 0x289212E8B86F74D4ULL, 
            0x1778B99E6388F746ULL, 0x696C742DB5CC8744ULL, 0xD1DEF313D581A712ULL, 0xD957CBA1C419769FULL, 
            0x0E63A09D7A2E8B8FULL, 0xE056DF694294536AULL, 0xA8641025BC4F4613ULL, 0xCC87118A363F63D6ULL
        },
        {
            0x435F8652EBF73097ULL, 0x32CE7D20B2492BFEULL, 0xCF4CBF29BC027F2BULL, 0xFBC442EA63D126BAULL, 
            0x7040C917E04EB75EULL, 0x6FE37277CD21DC97ULL, 0xED9B128ED904C4F3ULL, 0xA0E5F8401DFFE72EULL, 
            0x90B5795588EE4E2DULL, 0x48AC15F6D5135A44ULL, 0x163D2150ABD78545ULL, 0x8B4605BC8EA07D39ULL, 
            0xA2098B8E2228AF50ULL, 0x8E7D93A9528F9F75ULL, 0x8E78C96000632141ULL, 0xD76CD455E35789E6ULL, 
            0xEF52BF8AD1604222ULL, 0xC8F43BF6F3DFCED5ULL, 0x1A683FD9CD8E2787ULL, 0xB8CE1EFF3BABC2DBULL, 
            0xA720E8A9DD3239C8ULL, 0xDA95FBD16185BE4FULL, 0xD27FE2249C5587CEULL, 0x289BE526A06E5256ULL, 
            0xD0A7D05D16CF8C53ULL, 0x6C60759ED834FB3DULL, 0x029CFB2E04C45612ULL, 0xDE35DFD8DEF14A7FULL, 
            0xE728D0FF60ED2FB9ULL, 0xA87F5DD2981D0518ULL, 0x9308432DDFDD7442ULL, 0x97452ECAE70C0E2EULL
        },
        {
            0x97300510468C1FB7ULL, 0x50D60DF9144B7C8BULL, 0x08D46772350B5E8BULL, 0xD93D560849A93754ULL, 
            0xE11DEEE38B0CB1CEULL, 0x6B95CFA0F385E9FBULL, 0x1BFC38697B1570DFULL, 0x3D25AB36928F699AULL, 
            0x12E8DC153BAC345DULL, 0xF901381AE2C072C7ULL, 0xE1C071EFFDE38822ULL, 0x6250E1A2F885C16FULL, 
            0x4DE01A151E99095EULL, 0xBF589A8E6EC9B7EEULL, 0xD366820C98B35FEEULL, 0x4947FE6AB2A32D99ULL, 
            0xE00D01DD5DF6CD90ULL, 0xFBFA85E32D8DEE9AULL, 0x14ECB745B6B4825AULL, 0x1577829C532AA87CULL, 
            0x12ABEE2F9DDE3D44ULL, 0x9A5D19BD50B2B54AULL, 0xDF2EA13D57D52B73ULL, 0xFD3662148DB814F2ULL, 
            0xAC8726466E4A037CULL, 0x55C0186628879D78ULL, 0xB61B9A7F1C3838D3ULL, 0x77491346572ED5FBULL, 
            0x54FAC50871B7C756ULL, 0x68FDB3F841AEABF7ULL, 0x9623E343B485C88DULL, 0x7CA868829F909D44ULL
        }
    },
    {
        {
            0x77F08E56FFF3B040ULL, 0x4183EB3540D291BEULL, 0xEE3423FC19587F9BULL, 0x229EF535FF98AE34ULL, 
            0xE4A796726183367AULL, 0x14C54DE4D9899BD5ULL, 0xB704CB31177D551BULL, 0x10E6D35E11F01387ULL, 
            0x819002ADFAFB889CULL, 0x5848D9B0D8C1C473ULL, 0x15B4209F981CE165ULL, 0x3C0C94B357502253ULL, 
            0xFF50A069B6399AC0ULL, 0x7B2E927A6BA6D686ULL, 0x542ECE3E39A87B3DULL, 0xE8C7221B019AA5A8ULL, 
            0xB8883F7B1CAC539CULL, 0x94C94A711F489C70ULL, 0x5F07282F91E50D92ULL, 0x16086BE44560B08FULL, 
            0xF360C610D9383411ULL, 0xD6AE59AC4C04D6F0ULL, 0x9D14275FEEF5BE93ULL, 0xBDA456120BF90DD1ULL, 
            0x2346FF1CA8AEC9A0ULL, 0x19F6D843941CA1EEULL, 0x6106328746BB16F2ULL, 0x77B66057C46678F6ULL, 
            0x5C045F017D55929DULL, 0x6F4D03F06BB7E29CULL, 0x51F7095EE85893DFULL, 0x18384DD3DB907155ULL
        },
        {
            0x36D5EB0B46370FFBULL, 0x21E42DFFEA1BDD44ULL, 0xA903D73F92B1B1E1ULL, 0x338AB347CDCE1735ULL, 
            0x7C2F97A8240E5E1CULL, 0x08B4461E25EEBF62ULL, 0x3D0C59FA54E2C41EULL, 0xEFCA445CD35D972EULL, 
            0x29B471ABF5499B43ULL, 0xAD8CB41972957DCCULL, 0x92298F21C50E0FB4ULL, 0xCDF41DE68F7D6710ULL, 
            0x4025F4AD1F962535ULL, 0xDBDF2F34CF0A69C6ULL, 0xB1446FBDC2DBD0ACULL, 0x2F82AF91C145331CULL, 
            0xB881D8BD6F24CD59ULL, 0x7D2C2C2E2ABF7A34ULL, 0xF3F16AB3A3E57EC9ULL, 0xC14AFED364A63A16ULL, 
            0x52DB12EC624A3F5FULL, 0x81B90CFCB910DF80ULL, 0xEBD5F6B78AC665FDULL, 0x26571C0F34B22633ULL, 
            0x66E1E9209F454166ULL, 0xDBB534E78AE6B258ULL, 0xF7261C322FEB5AE7ULL, 0x1E039AC94CE34C24ULL, 
            0x340C518284C78213ULL, 0x4FDE95A5E717B91CULL, 0xEA39F3B282F672D3ULL, 0x6044902B57B71886ULL
        },
        {
            0x7099570B83151707ULL, 0x6F31BC10DED14A2AULL, 0x637320BACDF7ECB6ULL, 0xE85B3B54B2C6DF06ULL, 
            0x31E05A1D99386B3EULL, 0x99F1C8ABC0CE217AULL, 0xD5C54EB7BD85029DULL, 0x90341A72E0770929ULL, 
            0xA2B3E8A383C942DBULL, 0x8B79524523C43D02ULL, 0xA0D14F81AC239FBEULL, 0x3A304A11B7859E0EULL, 
            0x1C8BCC450A95B49CULL, 0xA01C90AD22FA0CABULL, 0x2367CFECF3FDBC30ULL, 0xF6AF8B1AFA029E7CULL, 
            0x0DBFEB0B56213349ULL, 0x0E0DAE070058D07CULL, 0xD35BDE82849ED52FULL, 0x345E9B8D75A0432EULL, 
            0x20A32AEEEE5EF32FULL, 0xA8D9D1E3B523ED2BULL, 0x0FAEB8AD7852B15FULL, 0xE09871C060614D66ULL, 
            0xF500F7FFEB79F73AULL, 0x79DCA1AA4B125D19ULL, 0xC8AEEADF50156F48ULL, 0x21572A5D8BA3158CULL, 
            0xCC8E801DDC78AFF3ULL, 0xE993C49F22D766C0ULL, 0x1E95584C7F06D1DCULL, 0x52229562F84C191FULL
        },
        {
            0x2B0DBF9F5773804BULL, 0xB0D4C6E4A1A017EBULL, 0xDA33266999ED1F69ULL, 0xD6A7FC57EF1DEA3FULL, 
            0xA5BD4845138D5237ULL, 0xD3841B026FA09E73ULL, 0xAE5627E448B1A7EFULL, 0x0D73EDA10E629384ULL, 
            0x88986431859B0F76ULL, 0x5A8C0072DF707208ULL, 0xC617BD90CC51E11AULL, 0xBA9DEB7D0A222D38ULL, 
            0xA227F9605A326D0AULL, 0x9A2B84C2F69C849CULL, 0xF008FC2B5EC06766ULL, 0xEDD1E555EA5F4438ULL, 
            0x57AC92D7E676E00EULL, 0x6E9027A31FA79D9FULL, 0xF33B285EEDA6749CULL, 0x79A27F17865FBAFEULL, 
            0x6D319A6010976343ULL, 0x3360575C992A3E84ULL, 0x5E1FF22029CFCEE5ULL, 0xF912B9CCDC8BF026ULL, 
            0x6AC6C0A247BB4012ULL, 0xF7555E85157EC51EULL, 0x08C3A6A1471E8710ULL, 0x41435CF3D2CE7D15ULL, 
            0x3CEB0D5D5A872510ULL, 0xD90B16D450275059ULL, 0x210C26AFB7740CDFULL, 0xE1E9672CF5DB21D7ULL
        },
        {
            0x2A68617FB377509DULL, 0x1E9B8154C1BF7E1CULL, 0x0AF4149CBF3C2943ULL, 0xBE2FDE40FCA40D9BULL, 
            0xE280541579106B32ULL, 0xE0868D74A8825130ULL, 0x6B29DF6FD5AB88E2ULL, 0x68BC902D81EC1F05ULL, 
            0x0FD905541997F5C8ULL, 0xBB627A9AB85EB71FULL, 0x530DFB222CBF7E01ULL, 0x490AB36ECC3917C6ULL, 
            0xEF1034B568F7699DULL, 0x4C3C7A44E9F99385ULL, 0x1248C26184A8FEA9ULL, 0x945E29E00DB10476ULL, 
            0xEF71161BB325E1DAULL, 0x20D1222CB6A4F8BEULL, 0x9CD4BF5513FEE910ULL, 0x72187859568159E4ULL, 
            0xE45A0EA2C0FC8B69ULL, 0x543C66AF307781BFULL, 0xFF90896B59DE9565ULL, 0x396787B135F52F1DULL, 
            0x9CA82EC2C6A85CE0ULL, 0xE0679B095FC31543ULL, 0xC0F47ADC6D86BDFEULL, 0xCEF215C28FFFF69BULL, 
            0xA5DF15D490587083ULL, 0x09571D4F03281BE6ULL, 0x038D19544B09CB73ULL, 0xDD6EC1D869A977B1ULL
        },
        {
            0x3D8192D55CF636C9ULL, 0xC4585CFF744643FAULL, 0xAA1525B298AB2CE1ULL, 0x30FD0284A32A1DF1ULL, 
            0xAF95BD99BFABECE7ULL, 0xCB564F63AF3856A1ULL, 0xCD32B5E7C314FC0FULL, 0x19F25C7342FEC5AAULL, 
            0x5A02D5CE9930ED42ULL, 0x2ACA3055F9CDEF1AULL, 0xE29AE9529708BE9BULL, 0x45BCDE6532BDD88DULL, 
            0x8EAD24B6E1BD5F55ULL, 0x27CA7D8A90E533D7ULL, 0xDC0698E3C55072C4ULL, 0xC33FC3D199487474ULL, 
            0xB7591495A9F3C77FULL, 0x1CBD9F4AD22EEF6AULL, 0xFF5722A7C8BCF983ULL, 0xEE2420ADFE84B7D3ULL, 
            0x5E09E1C34BA92A03ULL, 0xA5BD0CA952A72D26ULL, 0x8E1B0A07A4592001ULL, 0x019F416AA6325901ULL, 
            0x743F337ED0F9317BULL, 0x226F19E382EF8EB4ULL, 0x4CA0C23388EB2164ULL, 0x98AFC215FEF0C771ULL, 
            0x3BD5BCE940E151FDULL, 0x1EF1DC5D82515A82ULL, 0x5614060BC03CD9ADULL, 0xC6DDC6CE78D2BA3EULL
        }
    },
    {
        {
            0xE1EEA4526A7CDE08ULL, 0x5C282BA65BA4CD88ULL, 0xEC939847DAE958B9ULL, 0x1B42EF85C7A541E3ULL, 
            0x43CE10E59574759DULL, 0x71AE1B1727F54B49ULL, 0xD38B0E9BEBA4F0B3ULL, 0xBF8F811137AE41F7ULL, 
            0x49CC2C760B4896C8ULL, 0xD93767EB2F34A056ULL, 0xE60E9F4FB4DB7873ULL, 0xF3183441936BA0C7ULL, 
            0x0D6C69E52A1FC321ULL, 0x5904EFE2C0ABB7B4ULL, 0xFF16B02734672D0AULL, 0x5856FF30E7BC6629ULL, 
            0xBFE4B3B570A92532ULL, 0xA4D3EC76DBEC1A36ULL, 0x908CD5F3FC4DB282ULL, 0x6DDF9498801865F3ULL, 
            0xC39B8602D6A5652CULL, 0x49A3ABD2609B3DC9ULL, 0x9986E0A16751D1D1ULL, 0x593CA964C248835EULL, 
            0xAC6EA6202549AF2AULL, 0xD97BFF18E51B62BDULL, 0x5109D4E2B0E6DB31ULL, 0xAB0710413AF6892AULL, 
            0x4F599E7F8C0368B1ULL, 0x7FA81B8E81511E29ULL, 0xE97BB88B6D436980ULL, 0xA1A076D999C37442ULL
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
            0x98F3CE14E9D192F4ULL, 0x6C5D28476A75D518ULL, 0x0F955826046BEDC8ULL, 0x6117458EDFAD56F9ULL, 
            0x355564AC89A41436ULL, 0xDCDDBFC91535958FULL, 0x0D6E287040F29DE8ULL, 0xE357608740486411ULL, 
            0x19631CA6AAD97DE2ULL, 0x9AD77D256C10F3DDULL, 0x413C94D47220EE77ULL, 0x449C912665E4F98FULL, 
            0xEA0E705CD01D4DEEULL, 0x7F286037E017A51FULL, 0xFF331F0D7E9D8F0EULL, 0x91F71D58118B95D2ULL, 
            0x67D54AF65A5B9D1FULL, 0x9CDF3D727F73856BULL, 0xD94C8B35609423ADULL, 0xA3AB3A8DD77E853DULL, 
            0x118E6CBBDDD70B26ULL, 0xDF1CB9CB37859920ULL, 0x8D8D0F08F7D6EA8BULL, 0xB8CAD5FB96FD3066ULL, 
            0x40C3BADEBDA2FD80ULL, 0xAECF0921EBDAACCAULL, 0x53384D86670BDF95ULL, 0x9C99842EB029CF8FULL, 
            0x3C64A77776A5D467ULL, 0xF1437214657FDFFDULL, 0xE7D5F61B3BC29379ULL, 0x8905BB48BBC1DC62ULL
        },
        {
            0x7F58915E7EA51FE4ULL, 0x04A1B96B9340693AULL, 0x7BDAC0EE24FAF406ULL, 0xF4FFE7E0EFF68735ULL, 
            0x8B7CC96CC362F076ULL, 0xCAB4684A78C360AEULL, 0x9F5BFF01DCC2B322ULL, 0xE47C91C576221222ULL, 
            0x463C1014499082AEULL, 0x7673076A9435B40DULL, 0xE31823FBB549301CULL, 0xCE1FD050A6B9B3F8ULL, 
            0x8D3D24A93D5E1149ULL, 0xAFCB20F5EE77D0FDULL, 0x9153701DDB8BC1DBULL, 0xF451C7D2EFD1B546ULL, 
            0x818241A27938E9D3ULL, 0x589BEFD07654A3CAULL, 0x8B8B984B5592341EULL, 0x773F10707660F1B2ULL, 
            0x7F85C02D1A7EACA1ULL, 0x493EB2865E2430E4ULL, 0x3B0F0362EE44E9C0ULL, 0xD58F8BFC0B3554FDULL, 
            0xC46386130A3DFAB6ULL, 0xE4441BD96697F42DULL, 0x14173A48A222DED8ULL, 0x9E15ECCBB9D24686ULL, 
            0xB97EBD60AD4D8E7FULL, 0x494743040D254BADULL, 0xEB02DECC5A4FC1A0ULL, 0x2C2CCDC7DCBAE8C2ULL
        },
        {
            0xD488772A3A37B7D1ULL, 0x17E790A8E6BC164EULL, 0xC837DDF6989D5DE9ULL, 0x13870B2C5C7EC6A3ULL, 
            0x20DB3812719B7904ULL, 0x9D4D25F187C385FBULL, 0x662C986DDBDBBC53ULL, 0xDC7B684F079F9FB5ULL, 
            0x98B5A05A4E04ACBBULL, 0x8183491A5DDD4652ULL, 0xE95DF61F1683DFAEULL, 0x1038DBD7C4D8DF53ULL, 
            0x7C07165D1A738AEBULL, 0xBB371A174E56E881ULL, 0x4AFB73E41A23396DULL, 0xC20666246DB6312BULL, 
            0xC3502A2A93028A4FULL, 0x473A613F73964A48ULL, 0x7BDAEE7813381B4EULL, 0x9ACA9623D5FABB82ULL, 
            0xF2EFF967671DD722ULL, 0x85AE1DCF38CB9B93ULL, 0xB4FD18246DE7C98DULL, 0x372E9B6D7FDA5099ULL, 
            0x6C7FACD361B95682ULL, 0x665EF0F61912C608ULL, 0xCC9EB6AB1570F5E8ULL, 0x5B1ECACCB7324B82ULL, 
            0xCBA9459E3A43A8DDULL, 0xDB00895006947BB9ULL, 0x8BB36A8347C4D065ULL, 0x03D90133045141FCULL
        },
        {
            0x9F39F12CAF41413BULL, 0x621EFFD2446D1A7AULL, 0x4E9F26DE6E028B71ULL, 0x1C023ECC6B455D11ULL, 
            0x7BE50A4922350244ULL, 0xFCB7D5DD50782FBAULL, 0x215945D97BEDC7BFULL, 0x975940A190D889F8ULL, 
            0x8B0119BA8CD2B61BULL, 0x6FEC1E7DA66E8F8DULL, 0x6D6FE0EA533C2245ULL, 0x454BF6D7EBCD380EULL, 
            0x912DAEE21AF8CECAULL, 0xE3EB4C85C3E55777ULL, 0x51D2112A8329C783ULL, 0x343B86772213846DULL, 
            0x0CBB4D13B8A2D232ULL, 0x0466254AFADF7F61ULL, 0x09F88918F11D7659ULL, 0xD31ADB1A302937A0ULL, 
            0x8B1CEE6EF44505A5ULL, 0x2A096FEDEB74F438ULL, 0xD0BE65F2DE2ECD68ULL, 0xA8E895796A016FADULL, 
            0x6F60FDED9699F046ULL, 0xA0F5599B61E26979ULL, 0xB147785BB40B905AULL, 0x2F27E1F8E1CFE223ULL, 
            0x37146FFC48E7A188ULL, 0x0C973F96A64887ABULL, 0x2F6CF5D3B64AB56DULL, 0x035F041BBD15BFD8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseDConstants = {
    0x8673C037E49850B6ULL,
    0x4A811FF069736094ULL,
    0x95527CA67CFABF0AULL,
    0x8673C037E49850B6ULL,
    0x4A811FF069736094ULL,
    0x95527CA67CFABF0AULL,
    0x1C2976214034F8A6ULL,
    0x21AE8E62A734C0ABULL,
    0xF5,
    0xBC,
    0x61,
    0x34,
    0x5B,
    0x7F,
    0x30,
    0xE2
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseESalts = {
    {
        {
            0x2A125140CB6D1AE6ULL, 0x28C80562B955DA48ULL, 0xB3ECC570B8F3403EULL, 0x3526C0BC6130805EULL, 
            0xD559C00BE468188CULL, 0xFB968659AF3270C4ULL, 0xA8DE363687FDD82AULL, 0x207ABDA3BB30115CULL, 
            0xFBA6ABD7F57F8BA5ULL, 0x8E190D7B4E721517ULL, 0xBA8F586EA1F587AAULL, 0x61E7F4623233DDFAULL, 
            0x8E4090DDEA4032B1ULL, 0x464FA02486A180BEULL, 0x1D8365B30E73F4A0ULL, 0x80BAD8594E2E25F7ULL, 
            0x5290E791A7D5BEC8ULL, 0xD0B915A043BF7C57ULL, 0xC10F8D48254D2351ULL, 0xA935781B7524176BULL, 
            0xF5A38E30E6666F26ULL, 0x092BA8081DC7E1B6ULL, 0x50226AB1D43476C2ULL, 0xCC5E414D3A3B4F27ULL, 
            0x7C0F9D1EF4F62378ULL, 0x73DE5B4E9714CCB2ULL, 0x87CDA9C7F149F402ULL, 0x0978AC22CA4E17BCULL, 
            0x47CA758F0BE215F7ULL, 0xA867373601A2F74DULL, 0x4BA00E5778C90BD4ULL, 0xBE62B0B5695682CDULL
        },
        {
            0x1131AA7A643A8733ULL, 0xC52C4FC11AE562B5ULL, 0xBA737118F7D472F6ULL, 0x4276720967CB3041ULL, 
            0x47E9038921C8B0B2ULL, 0xBCCF2120F7E6A85CULL, 0xED739B913A4C0F7BULL, 0x92C53A8158CCF0BEULL, 
            0x1759A8878F10C8AAULL, 0x5917048833AEF024ULL, 0x49A13BCF1125B894ULL, 0x049BD261FEC3078AULL, 
            0x9FED50281810446DULL, 0xBA82F58020812133ULL, 0x7445B9338A195BFCULL, 0x2905C1B55CC945CBULL, 
            0x7F97175FAC422D19ULL, 0xF3D2DC76B5AFB0C4ULL, 0x99A4A94A7A099052ULL, 0x9B5D0BEC2AA36787ULL, 
            0x8E6B4D58A455AA9BULL, 0x510D47D43F5D6E71ULL, 0xF073D1E9DD424B5AULL, 0x6F05DE474ABE0AAEULL, 
            0x33893137FCBBD7F0ULL, 0x7D32685A04A48461ULL, 0xDFC83F2C4687B6E7ULL, 0x2026662A41B39800ULL, 
            0x8F5EAFEA469C42B4ULL, 0x8192F99FD595EC65ULL, 0x559225B3E5B5C2BDULL, 0x1C9EC717BC50CDE8ULL
        },
        {
            0xDD650C2B6BA6F622ULL, 0x24B2C647B78B456DULL, 0xDA7530CB05F33A76ULL, 0xE9B6392C430B8A5EULL, 
            0x527320C4DB5F0650ULL, 0x226ABEFE0522A8B0ULL, 0x37E7BFBDB25A3148ULL, 0xC77E6E6AD8066674ULL, 
            0xBE3ABFFB27BFF3DDULL, 0x4238E279163CAD5BULL, 0x42098B5DF227E808ULL, 0x4C016293EC069272ULL, 
            0x8C61C74C7791C6C9ULL, 0xC096060B65708DC8ULL, 0x098D83F1C43A4289ULL, 0xB18DAE3AA577F1FCULL, 
            0xAEEBA9C95222864EULL, 0x2B48A44444925DDCULL, 0x4E048E918CC73BE1ULL, 0x1355E408B4A99195ULL, 
            0xA6C9CFB69B2EE6ACULL, 0x2D6D01D656093926ULL, 0x4405AE2407DD6DB8ULL, 0x904D8D4F52154832ULL, 
            0x867A374D7DD814DAULL, 0x46C0E628BD728877ULL, 0xE49DCBB2AA82EB70ULL, 0xEE15D75A2CB24348ULL, 
            0x2BBD115C61AB9DD9ULL, 0x415A8BA65B87B091ULL, 0xF1FD05108D97585DULL, 0xAAC9AD8DD9F1F114ULL
        },
        {
            0xC10260C1E665D68CULL, 0xC703FA931BE1B19AULL, 0x25938DF8EEB1054DULL, 0xD9011B6B44A011ECULL, 
            0x81B2260111C760D3ULL, 0x54002385F20ED094ULL, 0x2FF355D2A728E5DBULL, 0x16B42E5803630013ULL, 
            0xA47DAAE7323C7F62ULL, 0x4FED6263F9C345DDULL, 0x3F01A8B69FEF9434ULL, 0xFE8052B980442B8DULL, 
            0x6A104A02DEF4A822ULL, 0x148516E94FE0DAD0ULL, 0x3951B77F56D07A85ULL, 0xE6A17B8FA5C27E48ULL, 
            0x0A87BF6F4AD6157CULL, 0xE2E8EAEE447E6E32ULL, 0x1B8FA2ACC03424EDULL, 0xE52672BB8B522988ULL, 
            0xEE615872EB681FC2ULL, 0xBDFF3FFCACEA616BULL, 0x72B9169A21F4FB01ULL, 0x90C5C526F85B9115ULL, 
            0x0625D1F45082BA81ULL, 0x30B7622410D7C42DULL, 0x58FA987E7F2D5454ULL, 0x84A62854D1F0616FULL, 
            0x8218B22C290DDE51ULL, 0x065AF8DC4415BDEBULL, 0xAEE2EEC5426A0B20ULL, 0x0F247CCDD9C3F33BULL
        },
        {
            0x5D0ED6DE8AEA17EFULL, 0xBB73F008D5DB3CB0ULL, 0x0B94E46640199326ULL, 0x5244781482924CA9ULL, 
            0x4512E32F269CFC3CULL, 0x58E7B622546E1926ULL, 0x8F2181CCBEA15A3EULL, 0xEBF4A1D7FF152587ULL, 
            0xEBF2672B34F11A46ULL, 0x363B9C8D2BC5233FULL, 0x50D06BB5EF795C0DULL, 0x9FA75E19CA38B1EFULL, 
            0xA0CE44AABECA3D0EULL, 0x9BE3FB4DB6256F24ULL, 0x6A10C90E9726BC89ULL, 0x9715C1853769D387ULL, 
            0x8B5860504A02BBD1ULL, 0x5A5245940EF0F2DDULL, 0x6B850D860DB99F51ULL, 0x9E98279AC2E6A3A6ULL, 
            0x725FB5587F6CE32CULL, 0x12E91AF0FFA04A53ULL, 0x150CBE07F258BD4FULL, 0xD535DF1501E533CBULL, 
            0xA73E2845A0140CECULL, 0x684F06BE9A148B82ULL, 0x46C2E14932C5D549ULL, 0x0CD182828EAAD042ULL, 
            0xBD54B3B34441EC03ULL, 0x169DAB551FEF3A1BULL, 0x6241FCAB4F21B9FDULL, 0x15EABCD2BC9893A6ULL
        },
        {
            0xAF82B363F341FE3AULL, 0x08801F7A9E2D6427ULL, 0xFF2256CF1C1C5762ULL, 0xA125AE34F50F2C47ULL, 
            0xF2FBCF0CAA4DB656ULL, 0x5407FFB30E8D10A4ULL, 0x807843F0F00267A2ULL, 0x172E702F64F86C2EULL, 
            0xB0EA2383D71333F8ULL, 0x3D1DDF0FBEF03C87ULL, 0xBB7D4C421EF2E0FAULL, 0xCF6ED3567395D122ULL, 
            0x24F8519957F0A088ULL, 0xAA6FDCF0DB292FFEULL, 0x3E33A089E8F7220AULL, 0x1021F35BD481B51DULL, 
            0x3D114C54A7127D24ULL, 0xA740E235ED8A506AULL, 0x3552EC63AEFECC39ULL, 0x3EE630A8509618DDULL, 
            0x7A40C2C1A87FFAF6ULL, 0xCD1A69DABEA24858ULL, 0x3C43D4C5B8BE4229ULL, 0x373ADD1C6F6568CAULL, 
            0x7695FAFA0BBD5E6EULL, 0x609FA835AE99AC8CULL, 0x877C4046D6910C68ULL, 0x2D1AE12AE9EB76E5ULL, 
            0xD7E8E0F103B22908ULL, 0x2CC8BEA0EE9CA4E8ULL, 0xC6227A114D5EE4CCULL, 0x21778B331E1920A9ULL
        }
    },
    {
        {
            0x60E5CDAF6547F3BFULL, 0xD165101105A93C01ULL, 0xFEDA9DBEDF622C0CULL, 0x12AE42DAB0C775BAULL, 
            0x94A0A4CD12EB6D4BULL, 0xB7DDCAC44A308D9FULL, 0x2006ADD0A22BDF2BULL, 0x688AF33C6B0DEEB4ULL, 
            0xCC8F32EC88C9562AULL, 0xC0DC2145B6749AA8ULL, 0xCA2D529EA4033339ULL, 0xB19A606F0D338504ULL, 
            0x58A6E91F69596B89ULL, 0x4B0307648FD992C8ULL, 0x5D292F2C93EF6AB6ULL, 0x64BBD6AF72CCEDA5ULL, 
            0xA3670D9C3113A2CCULL, 0xE71F6AA3C83315ECULL, 0x4063C9CD583F9FADULL, 0x0906919D6E3DFF02ULL, 
            0x29632FB3A34EAF71ULL, 0xD001C8A174E19263ULL, 0x81E2B8209315C7A0ULL, 0xFC8A7294BE59F29EULL, 
            0xBA8C80C47D413BA5ULL, 0xCE4E1C61FCEF872BULL, 0xD4C0EDC43EDD8DE4ULL, 0xEC6F6A9BCBBF4E87ULL, 
            0x2ED5855F13050FBFULL, 0x45D5A8D99A69FD2AULL, 0xC80D55A76746CA2AULL, 0x2B48742C8A02ADF0ULL
        },
        {
            0x1170EBD304B0AC5CULL, 0x17660224B5EBCAACULL, 0x498024948445685EULL, 0x1705387FF309742DULL, 
            0x7923873E2B05DD23ULL, 0x7477B0B5D80FA67BULL, 0xF121DCFA680CD525ULL, 0xA576B2FAD279B6F1ULL, 
            0x4E80EB0063F0BEB8ULL, 0x9DC1F738F7E733C8ULL, 0xE7408B66E6638AE8ULL, 0xA539D169B6997F27ULL, 
            0xE1AAF0584C801758ULL, 0xBFED99C40054B745ULL, 0x85D814762518BB0CULL, 0x00AC3232E9137ADFULL, 
            0x87AF9F2DE0C4D54AULL, 0x9A8F6A8260A787B7ULL, 0xFF298265E2BCC353ULL, 0x5746EF112EF1AB19ULL, 
            0x0B00CED3CB15A24EULL, 0x6F9DE1FC70B0B09DULL, 0x0AA41EAAA6D3C217ULL, 0x3AA56B216C48DD0DULL, 
            0xD3BBE632138DB6FFULL, 0x21F87B053C5638B0ULL, 0xE110649914848A95ULL, 0xFB5E37A564F7DAF2ULL, 
            0xD2E1FE52D6326766ULL, 0x0660E493C58737ADULL, 0xDA120B89795E07A7ULL, 0x3911320BFC661ED4ULL
        },
        {
            0x4556843F3E19AF66ULL, 0x9A989FE14A2A966CULL, 0xA80FAC439A20CCA1ULL, 0x89B3793AF5E45C10ULL, 
            0xA0D476040FAAD0F8ULL, 0x370ACF8AE3A74633ULL, 0x0EE10704331217B4ULL, 0x4369F4D5E8E70F35ULL, 
            0x463A63FF75664DFAULL, 0x7EFE85C783180319ULL, 0xE267466E7C8830E1ULL, 0xE18CEDD03F09120CULL, 
            0x3D063A5509FAE5BFULL, 0x7F71BBB1FD862942ULL, 0x554D6A2131572907ULL, 0x793F9BC06F842AB2ULL, 
            0x36F16723F2BE2412ULL, 0x03392B801B4CB41DULL, 0xFD9CDDA553E95083ULL, 0xCF390D37E80649E0ULL, 
            0x78478CEEB18D33FFULL, 0xDE31E9CDF35724EEULL, 0x514A8AF96DF92452ULL, 0xFAD199C1B2701FF5ULL, 
            0x96F28219D85497DFULL, 0x36DC7544F07AB027ULL, 0x5886205A1A4739DCULL, 0xC8BBFFED56FF83FAULL, 
            0x99FFA6AD1B4D93D5ULL, 0x57F51F51C0CC3BDEULL, 0x7010A2C79397026EULL, 0x34E6455D32072406ULL
        },
        {
            0x6384582276B4F660ULL, 0x3035A9D375F84ACEULL, 0xB9230B61A3E645F2ULL, 0x14380468326F2A4FULL, 
            0x5F60402815C562B6ULL, 0xEBC084B2EA40F779ULL, 0x24D6B4A9BCADDC02ULL, 0x6B0640D59E70FF9EULL, 
            0xD128C15E19284F08ULL, 0x4ACF037CFEE776C6ULL, 0xE22A2CA5517318F9ULL, 0x7A6F051067590724ULL, 
            0x20AD28EE8B1E631BULL, 0xB0876E556F8BFDFAULL, 0xB62C3B51715A4EA4ULL, 0xC9D7B99B18092795ULL, 
            0x8E1BC26E0194622DULL, 0x774F59FB040120E3ULL, 0xA3C4F1AA45648F61ULL, 0x791FF92EF6CFF296ULL, 
            0x4F5C7C10A712EE16ULL, 0xC6D45F98499CC79EULL, 0xA3DC8B3843E95E70ULL, 0xC4278709B10447E1ULL, 
            0x2E1CBC3AF345D300ULL, 0xA033F6EF61193C40ULL, 0x990CCECF9398824EULL, 0x2DCCB59E226CD2D6ULL, 
            0x50C4C93C0CCEC323ULL, 0x4F30F211B935B7CAULL, 0x9640BBDB55D694FFULL, 0x7C29E143475F367AULL
        },
        {
            0x8313D9B979E03274ULL, 0x7C052427CE25978DULL, 0x6CFC59556D082D39ULL, 0x2E82B4A84081F19FULL, 
            0xF2362AA04D1B5EBFULL, 0xA52236F1D5E0EE57ULL, 0x5C5D3CBDD2427AB7ULL, 0xCCF50E0E6688DA81ULL, 
            0xCB0FAB2F04557C34ULL, 0xC6B1B9923A082445ULL, 0x18BF436961410916ULL, 0x80961F2B12A1BFBBULL, 
            0x5BF710B066CE9D02ULL, 0x5BA5FB9C71353DF3ULL, 0x26EB191DD1A841E0ULL, 0xBB30217DE2D95D44ULL, 
            0x8D8017FC17D02212ULL, 0x34C63FC305CA86BEULL, 0x9D957F978D9E9E55ULL, 0xD293CE828FD75FCCULL, 
            0x801249505F0559A0ULL, 0x02EDA9957AFAEB48ULL, 0x37665E525CEB2AEFULL, 0xB7CFAD8FD9B3A033ULL, 
            0xABD12292A42A971AULL, 0xBCA7D1CD58CB1F07ULL, 0xAB9EBEE2E26F7402ULL, 0x81672F4B62CA0218ULL, 
            0x4063050A28639DDDULL, 0x4A12BFEAB002A383ULL, 0x119CFA92AE258707ULL, 0xFF977BE72A14D29AULL
        },
        {
            0xB841AEFE5CBBF0B6ULL, 0x529DEF0B5EDDC403ULL, 0x2DA77E8A97674D05ULL, 0xCF2AEE6BD52D132CULL, 
            0x593241D4C9B60115ULL, 0x394201506E230C73ULL, 0x8422F432111D6C3EULL, 0xD736DEB7852257E6ULL, 
            0xD287B373850A61CEULL, 0xD00C3026E8717794ULL, 0x7BE46DE97DF810FEULL, 0xBD43CF0767429BD1ULL, 
            0x52753F086BCDD17BULL, 0x54DD404D78AE269DULL, 0xEB31D1D69B274BF5ULL, 0x56532A2251377755ULL, 
            0x10F695646D91598AULL, 0x24AE59C8EE32E04FULL, 0x22C317B1F546E95AULL, 0xC5C485EF702F1EF0ULL, 
            0x6E6B3B71C8328527ULL, 0x8EBCD5E4EEE98019ULL, 0x3B6BEA724C1FD8F2ULL, 0x075CC12253BA931BULL, 
            0x17137C470CD5BDB5ULL, 0x0F98785ADD6C0A21ULL, 0xC2172728EB04668FULL, 0x8A322B0A0B8AEC22ULL, 
            0x6B9DC288A804F463ULL, 0x2DFA4F673BFD0F84ULL, 0x1835C6B22C550D39ULL, 0x48D6CFA4ADB970DDULL
        }
    },
    {
        {
            0x4D4B94C127B10581ULL, 0x111A51C18372BFD7ULL, 0x207A7B6A4D2BD54CULL, 0x973759B8782A903DULL, 
            0x27A86FE8795D9F67ULL, 0xFF659687AD13DF8FULL, 0x39692BA00E1DE60DULL, 0xC2128F1EE631B7D0ULL, 
            0xFB10C0DCAD1C0CCFULL, 0x84E66AA45CBF8416ULL, 0x23E3229A6AAD3067ULL, 0x677E9CC767DA2160ULL, 
            0xDB7FC682C088327EULL, 0xB9E844AB6F3DC29EULL, 0x5DA58E6B3CBA89FEULL, 0x6A02AF7B6F73CEC8ULL, 
            0xC49429F092E43E1AULL, 0xBF75CDE7582672C4ULL, 0x56AA76132EC80E6FULL, 0xB9063278BF6090FCULL, 
            0x5F020F159BC0F1B1ULL, 0x90B9C5DD4EA7854FULL, 0x2EB5B9D1D09806B9ULL, 0xA351CF894FD0D0B6ULL, 
            0x3EBAE0286EA8C14DULL, 0x81A789E4DD9FF9F4ULL, 0xF7C5958E100AFEE9ULL, 0xA25B69995303D2F7ULL, 
            0xFC18111050D4C692ULL, 0x20907AACDED113B4ULL, 0xF9691B3D1DF67F12ULL, 0x3C0EC2E7195071C9ULL
        },
        {
            0x8DAC8AC4CDA020AEULL, 0x3B6FDFD962DA0D47ULL, 0x35CF69EE5AA7CD06ULL, 0xB3CD62689475306BULL, 
            0x45C382ED680E2C49ULL, 0x96E4F3C00E9E34BAULL, 0x41ECD05A6D3CCBB2ULL, 0x4BD32E5549C3BE78ULL, 
            0x45F9991C613589C5ULL, 0x91F2B2BCDF946E24ULL, 0xDCF2CB24AC3E6683ULL, 0x4FEEDBA3A1E05ACCULL, 
            0x8A135E5873B75361ULL, 0x865A0564CB7EBE8CULL, 0xFF5529A594C512D7ULL, 0x4802BEF1B4CCBBECULL, 
            0x74D57E4AB48FEB47ULL, 0x68EEFCF3DD17DB09ULL, 0xCAB672BE276FA0C6ULL, 0x64F4C9C049FFBD01ULL, 
            0x65A2E596F00C2BB7ULL, 0x7F894C589682F548ULL, 0xF09707FC0A1F687DULL, 0xC5909F88E262883AULL, 
            0x352563D59FD3F24EULL, 0x07B8A848CFBA2416ULL, 0xEFE6716BA5E5A633ULL, 0x8EE346357B665B11ULL, 
            0x56B2FEC872F3059DULL, 0xDB505C487DAFD249ULL, 0x798AB8F065FAA0CAULL, 0xDA163A0265D2BA1EULL
        },
        {
            0x3D097179237CDE37ULL, 0x5CF90CD248B57321ULL, 0x608DEDE05E71FD04ULL, 0xA8A5E6E4D4F23581ULL, 
            0x41B8FA94CDE45695ULL, 0x77A508B2EDE9EDA7ULL, 0xF73DEB1CA0C308E8ULL, 0x9448DD02EE734F03ULL, 
            0xF39E24F89630D0A7ULL, 0xADA0B40C57EE7BC3ULL, 0x3FFC17E65320D217ULL, 0x8BEE56F9A133598BULL, 
            0xA89EECC2103A3F06ULL, 0x50F204A6CF9E2DAFULL, 0xD039BBDFEF223081ULL, 0x0589DFFEF6D33255ULL, 
            0x0B98E5902A00CF8DULL, 0x724B668A91312397ULL, 0x286E291B98861E07ULL, 0x299197FB1AAD22A8ULL, 
            0x6E89F026024764BCULL, 0x4C9010B351DA5873ULL, 0x59D7ABE0927A6865ULL, 0xF2983AF05837F987ULL, 
            0x0440E26E81A43E93ULL, 0x3484FE72897D83F2ULL, 0x8C77CED1C02E5F80ULL, 0x9DD392529827467BULL, 
            0x284EF3F2202B7C90ULL, 0x71811EB34B42F9C8ULL, 0x23ED24ACDFA62564ULL, 0x7F9FF9C7214055EDULL
        },
        {
            0xB045A752DC8CE98CULL, 0x4501331BC5D3436EULL, 0x9F54BC7B520211BFULL, 0x70CB645D0B212672ULL, 
            0x55466940074470E9ULL, 0xCD3E070A91E1CC57ULL, 0x7A2B359F09F9527CULL, 0x377483B926C057C6ULL, 
            0xDFC121E3CFA70730ULL, 0x9675DAF695DCE38BULL, 0x9E6B40825881455FULL, 0xD4380DDE67EE74ECULL, 
            0x9C52BABDFA234BFCULL, 0xADD4EFBE444367F8ULL, 0xA26F29713FDC627DULL, 0xFF8A112DE813F5C6ULL, 
            0x46FF92915E606893ULL, 0x8C4135125902BB1DULL, 0xB522DC9EB6011DBAULL, 0xD093508553927E0DULL, 
            0xC471AA80F31CF482ULL, 0x4AAE98631F77E718ULL, 0x3910B8DF9CC202E6ULL, 0xA0EFD28C76D231B7ULL, 
            0x1E39131CCD2D9D2EULL, 0x842BB29CC5C10B1AULL, 0x4130FFC334D3721FULL, 0x47DD0E99344073B9ULL, 
            0xBE85CE63AEFC0B35ULL, 0x35A8CA37B78C715CULL, 0x897AEDA94D10D996ULL, 0x41B356244F304A79ULL
        },
        {
            0xBAB53780009A4FBBULL, 0xEC3C45A9F44B1A59ULL, 0x5A3E2863582AC37FULL, 0xB14BFF1EBEAD1E58ULL, 
            0x4F6D6600CC3B3C79ULL, 0x12F534B996306641ULL, 0x564086C4C764DE81ULL, 0xF5EBCDFCD4EBB6BEULL, 
            0xEA731C8F8C98A9F6ULL, 0xB05AF9418F758783ULL, 0x15BA480E9A9D4C42ULL, 0x619DBD8C25BBA150ULL, 
            0x7BBA0A9F57C0A2F6ULL, 0xBF96C746549ECE37ULL, 0xED7CECF959EFDB8CULL, 0x1EFAC19807860BB8ULL, 
            0x2D83B68CDD68FF06ULL, 0xEF6187838FE307D9ULL, 0x4E6B6A56FC604361ULL, 0x5D6C51C978B1995BULL, 
            0xEECBA4EC35734A17ULL, 0xB1D4A28C68149E7DULL, 0x38D3A0C3AB47D687ULL, 0x26763F81D4CF98EEULL, 
            0xE1C17F00DB29CC9CULL, 0x436019EC5B3F1827ULL, 0x9F63F1AD9497FA04ULL, 0x8303FDA07F765397ULL, 
            0xCAA7932ECB3E7A71ULL, 0x3EADE30129B96F69ULL, 0xABCF4047B59F99CAULL, 0x6181D57BAD73D658ULL
        },
        {
            0x1B16E062F1BEDCE9ULL, 0xFB09E73239ABBDB1ULL, 0x811D073214BA61E4ULL, 0x55BFC6BC117C5E3EULL, 
            0xC6D15ECF7946F5B5ULL, 0x99D2B078FE901D7AULL, 0x74B5F116B2017172ULL, 0x1242834A2310BE10ULL, 
            0x72E5B5CE18164A15ULL, 0x47F468E320759BEEULL, 0xE14E5570059B50C9ULL, 0x1B95A72147BA8823ULL, 
            0xB5B6C12FA7468C88ULL, 0x62FD0B7EAFDD65F9ULL, 0x8CF551B413D8B7CAULL, 0x57F61DD3AF99911EULL, 
            0x00F7575A49177DAFULL, 0x8A8955BF1A601B81ULL, 0x3705A9F4E65CACE9ULL, 0xF180AD234CF62641ULL, 
            0xA2455FBB5708817BULL, 0x5BE0DC894F1B3D4CULL, 0xD21641D7E06F1F83ULL, 0x0B90610456034BD8ULL, 
            0x70D4EE718BFA3C63ULL, 0x1EEE2F9E01E59447ULL, 0x7826134C40DEE7E1ULL, 0xED23743CE5520A31ULL, 
            0xCF58BFFC99D0888DULL, 0x0AFF3EFDD1B1B2B1ULL, 0x68EA2938B80D6B06ULL, 0x0CD5801A26400B4DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseEConstants = {
    0x923EBC48D8F3454CULL,
    0x81BAE89D1D72DC05ULL,
    0xE7EFCC991CBAA970ULL,
    0x923EBC48D8F3454CULL,
    0x81BAE89D1D72DC05ULL,
    0xE7EFCC991CBAA970ULL,
    0x4DCBF7D62CCCCCA7ULL,
    0x2A8AEA24A8D827ABULL,
    0x97,
    0x3F,
    0xF0,
    0xF1,
    0x5B,
    0x93,
    0xE8,
    0xF4
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseFSalts = {
    {
        {
            0xBA7543EF18B21162ULL, 0x5DC83B7BCB4077C9ULL, 0x788399AC78855FE2ULL, 0x0F4DD1C065964ACDULL, 
            0x757E8BD8B5071A38ULL, 0x81DB2938EDFB26A4ULL, 0xFED6DEF143B3D715ULL, 0x98C832995217303AULL, 
            0x931094C0D91B156DULL, 0xD5FD23659D40AA3BULL, 0x6AA23361FA5BE26FULL, 0x9E56371CE9DDBEC4ULL, 
            0x763B2E26C93A11EBULL, 0x2E655DC00BD7A0EAULL, 0x6A6945ECAC9F5469ULL, 0x4907F5D087B36861ULL, 
            0x91F00E60E832767DULL, 0xB68C3BB9CFDF1884ULL, 0xD666507D162FC292ULL, 0x628E9E950FB2DBCFULL, 
            0x00FA8D61D87A1712ULL, 0x2461F688EAC0E031ULL, 0x7D36B125B19C707BULL, 0x8B0185AA6C43D8F6ULL, 
            0x14ABF8FB2AF2E514ULL, 0x7DCCE48168FF75CFULL, 0x4697645006013EC8ULL, 0x1FFB7BFC85AFE342ULL, 
            0x00B37AA5E343B835ULL, 0x9016687AEEB2BD0FULL, 0x65BCFCB1F486956CULL, 0x7BB0E73D31F52643ULL
        },
        {
            0xD42F27B9BF0A401CULL, 0xD07FD35C965810D9ULL, 0xA3E9B0AF2EDF1E72ULL, 0xDA3C7B2215D8405AULL, 
            0x807DFE738E385B38ULL, 0x3F6AFC5CEFDE7110ULL, 0xCCDE764C54E5F783ULL, 0xDAEC24E49584EFA6ULL, 
            0xCEB4A7B89BBA421AULL, 0x1E424BB1E8DF5845ULL, 0x49F815F5E90BB1BFULL, 0xB7D9EEB0F11B86B5ULL, 
            0x82EFAD4E852B8D40ULL, 0x82D7824D1288153AULL, 0xEB4982F97E3AE3C8ULL, 0x140F56280FF03C3EULL, 
            0xAD85F6B12C671677ULL, 0xB440B09FAC2FDED8ULL, 0x00D800B8D28707F7ULL, 0xE60115830C5DB9C6ULL, 
            0xB7ADEF480B746001ULL, 0xD2FB8B2CC8509B81ULL, 0x97C072BA95185877ULL, 0xE6F43E816AD09AA0ULL, 
            0x905D5F5FE2288A5AULL, 0x575326B21CE41C95ULL, 0xD9964D3639002496ULL, 0xFE290C4B90DC57ADULL, 
            0x540DB11572010B2EULL, 0xB5DDA1120054ADECULL, 0xC23F0BA3F2AA22F1ULL, 0x9559B59548012425ULL
        },
        {
            0x61ED1F9E06F430FAULL, 0x63949D715E4432D4ULL, 0x6CB1E1489DA13571ULL, 0xE77D512FD144AE6FULL, 
            0x362DD3FC34ACBE29ULL, 0xE9DF3C76CA351226ULL, 0x64945AFFBA6737B2ULL, 0xB80F98417CAF42E0ULL, 
            0x76A74485403C74C2ULL, 0x5BDC179A0A8CE8F0ULL, 0xA616B13B69E1D26DULL, 0xCD97B5413702FFA5ULL, 
            0x050E1CBE8348407AULL, 0x14610195974F1222ULL, 0xC53FBB247D88859AULL, 0xD58601E13176A770ULL, 
            0xCD54D71C5D940D08ULL, 0x1811DE3D1F621044ULL, 0x2D43D86C1E0F845CULL, 0x863D239A3041076DULL, 
            0x6E3BACBBA7DDFD58ULL, 0xA4C7317E4FA14FBBULL, 0x73569332EC582C6EULL, 0x042EB5AC9D6B84ACULL, 
            0x56B4286BDD45D661ULL, 0x45D68FBD4A5714FFULL, 0xC196410EB11847D7ULL, 0x492B3C2F2BC5172CULL, 
            0xEEF7A33C47D0A695ULL, 0x74315A4AE7D1BEA2ULL, 0xCD642176CC206BA1ULL, 0x70B7FBDB877D6DD1ULL
        },
        {
            0x0767E38116700F37ULL, 0x185FD9C6797BDFD2ULL, 0x663E883FADE89DCAULL, 0x4143C13FB2B5ECADULL, 
            0xF6CC45E2020359FCULL, 0xDFAE6901B606A4A1ULL, 0x189062F93D0897FAULL, 0x786530073A7905C0ULL, 
            0x27B07C7F17B0C45BULL, 0x4BB61FD1CEF6E233ULL, 0xA1415793E9BFC56BULL, 0x00F409626E6D16C7ULL, 
            0x83645982B8ED779EULL, 0x720D6259B477DFF5ULL, 0x9BCB6272F0B60518ULL, 0xFECE17A1EC24C51DULL, 
            0xA4BA5B9C3DA523F2ULL, 0xDB3BA324A34171F7ULL, 0xEE8D087A743041BDULL, 0x028C63B3D524C5EAULL, 
            0xC318BF1BBAECC1A2ULL, 0x9B3A4F0ECD6F04D1ULL, 0xEEA2128DCBEC624CULL, 0xCEFE0AD315E21EBCULL, 
            0xD846A00E7A371AAFULL, 0x08CB0640FB494DB8ULL, 0x22CD5A77152484EBULL, 0xCCF87C0630FAA694ULL, 
            0xE85E75D0AA31C4EDULL, 0x822F14CD19726E6AULL, 0x72FCD992B1A1E8A5ULL, 0xF825962890FDDD76ULL
        },
        {
            0x8B715157DE82AF0AULL, 0xB51DEBD897EBF2AEULL, 0x674D61280EF06222ULL, 0xCB6146AF8D168008ULL, 
            0xD5B3C7FFF20F4FE1ULL, 0x696D4CDFD98DFF38ULL, 0xE3892F34AE6A9457ULL, 0x0243D1809AD50CBFULL, 
            0x18142EEDC68DB820ULL, 0xFB6F99651E7FB22EULL, 0x82631EE45784A9E0ULL, 0xC172A0549EC88CDDULL, 
            0xB80201EB1BBFA1F2ULL, 0x0CEB86DCE2EB8BB9ULL, 0x5495FB8570508E7FULL, 0xE1277B6A3F5DE8B6ULL, 
            0xB9B2C381CEF6BC2EULL, 0xBC0B5AFE7FDA7C9CULL, 0xB5302F89BA30A4EEULL, 0x38D1883C0D93CC24ULL, 
            0x5B69EC7919FA72D9ULL, 0xAE1211661FF2881FULL, 0xDC82742F001F44F8ULL, 0xA17165801A6F6165ULL, 
            0x4A7172D9116A0BCAULL, 0x12122EBA4A0650FCULL, 0x9078713F132B9EB7ULL, 0x88E17D321E0900A0ULL, 
            0xD56980B522B4CE14ULL, 0x0F8F3C579BBA71FCULL, 0xD1CD868DE7BB69FAULL, 0x7F2B585D7EDAC95BULL
        },
        {
            0xE9AABD81DC140D0FULL, 0xEC5DD444033E3C6FULL, 0x8A4B330B9C728446ULL, 0x94CC2642A2BD291FULL, 
            0x85B2FED65A8B28CFULL, 0xAD33DF6485034894ULL, 0x3C79D2ED11045E66ULL, 0x5B6D5D682433C13CULL, 
            0x5797E03A059F3A6FULL, 0xA6101CA3A7616A48ULL, 0x97CDCEB679249F7AULL, 0xD5FDCD38757A8A59ULL, 
            0xC2435C4AEDD06FAEULL, 0x95B3122011A0FED6ULL, 0x49BC2DBEA15F95E6ULL, 0xE33A3F7969E73B17ULL, 
            0x95A3D5F1F65F1166ULL, 0xF979D46A57195254ULL, 0xA3C298401B9C1935ULL, 0x36388106FC017C6EULL, 
            0x526E144CCC124A33ULL, 0xF1AA4ED6D28674B2ULL, 0x284BFAED80F61237ULL, 0x16D8DC6CA557D86AULL, 
            0xE29B72A4E85CFCC6ULL, 0x11702DCFF7D7B6FBULL, 0x2EBDAAA58157461DULL, 0x7BBBF3533384E50BULL, 
            0xD91C7F291B95E71DULL, 0x1C77E51B63D65A5EULL, 0x6BD817AD3D936FBBULL, 0xCFADCC987E563558ULL
        }
    },
    {
        {
            0x96E83AA77FBBB0BDULL, 0xF0272DB15117FF74ULL, 0x06FD538B76ABFDC2ULL, 0x472F98BCE50ED85CULL, 
            0xA7A01501E29ABA89ULL, 0x4FCD1205CE5E7E2DULL, 0xAF3E7FA78682CE89ULL, 0xB1306B47F38BA66CULL, 
            0xB939D2E70576E9EBULL, 0xFC8AEF852E837895ULL, 0x6FFEB5B2A4CAB3FEULL, 0x7FA0CDB0CF590F50ULL, 
            0x87E2E395814AF963ULL, 0x56D588A6F2EAF0B7ULL, 0xA14005B20A92A9B4ULL, 0xE1849177658A5AD4ULL, 
            0x945E47A2AE154D78ULL, 0x556C4A6BC7031393ULL, 0xD10818755CFC560BULL, 0xDF9CB423B8C07441ULL, 
            0x81785D125D755AAEULL, 0x9E7B652C42B5C523ULL, 0xCB95A5F86DC334CFULL, 0xCDB6FF769BB97A8FULL, 
            0xEF28298F36A192E4ULL, 0x89F7787EB9FED60FULL, 0x2878BA5B3DAAB02DULL, 0xD7D77499829E8A18ULL, 
            0x127D7B69DC438137ULL, 0x2D57E79FB7C1A576ULL, 0x06633863CC85BEEDULL, 0xAE14B98554669D8AULL
        },
        {
            0x75E225D6946DC52AULL, 0xBCA73E4BDCEE0ADDULL, 0x51D302334D919919ULL, 0x25AFAB53E0457ADBULL, 
            0x46C82EF8923FF66FULL, 0xC4AAB2ACB5E645DCULL, 0xD7C254B489402ADBULL, 0x8ED3670F2D42C953ULL, 
            0xB4FCA209372F4B75ULL, 0x7463077F0B4F2B65ULL, 0xE81A36F953EC08EEULL, 0x7BD7ECE99921EDF7ULL, 
            0xB63E91F701306ACFULL, 0x0834E918A397AAF1ULL, 0xE5494649A5E85C01ULL, 0x8B7E953F19C2C712ULL, 
            0x5329503A90395DEEULL, 0xC88C504B35488B9AULL, 0x92F579B084C93E35ULL, 0xD248C9472075BDDAULL, 
            0x61BECB53FD9DFAD0ULL, 0xBF5B2F8BE710EA9AULL, 0xB289E391B4DBF364ULL, 0xDA3F940F488E904CULL, 
            0x700F379FDE936415ULL, 0xC98FE29E513CABC2ULL, 0xDFC9EC221561C4BEULL, 0x9C8FCA5065638774ULL, 
            0xD62C0BC1D8CAC9B7ULL, 0x346C8CEE818E117DULL, 0x3F7107197593EA38ULL, 0x9BC020B40E93C7F7ULL
        },
        {
            0x0E262A5F549E7441ULL, 0xC1A205BC637288CAULL, 0x0B961615F0603BE5ULL, 0xA3C35D6CD56E3476ULL, 
            0x2E3B9A15F1F93304ULL, 0x5C71049B108905C7ULL, 0x631CB7BE9A33806CULL, 0x4365A7127F4314B5ULL, 
            0x2C48900EF98D724BULL, 0xE7E6C7E9526063F7ULL, 0x79DEB5AAC2A8A8EAULL, 0xFB244089747A425EULL, 
            0xBF5297ABBBB8790AULL, 0xC646729CCC97E5F6ULL, 0xC06861F0E76273E6ULL, 0x6C57A924F05FD2FBULL, 
            0x94FCAEF81C2225D8ULL, 0xF6C1E3157B8E5B1FULL, 0x4EF75B36DF983976ULL, 0x21CEA970BC8C0375ULL, 
            0xABC86B80C03B841FULL, 0xC777B4D2F02E54B3ULL, 0x1EC13F58274662BAULL, 0xA651C27DFBBD730CULL, 
            0x5E3096B1E5A8568BULL, 0x106B1265EBF8D9BDULL, 0x96C264090A3EF44EULL, 0xD70AD33A097E0AD7ULL, 
            0x695992F81F6BCC59ULL, 0x9FA8804436D5EFC0ULL, 0xBE38ED3A087CC823ULL, 0x398B8A07C8EC9202ULL
        },
        {
            0xB386CC1D9B603659ULL, 0xEC8E2BE75804A29AULL, 0x9841147A9C666430ULL, 0xB5CD1A564AE185F1ULL, 
            0x23C94D648C49F6ACULL, 0x4873D18FFA0604A7ULL, 0x2620909D66D70B36ULL, 0x73105214BDC12E1EULL, 
            0xDEE8865CF0ABFEC8ULL, 0xF671A00D147F55E5ULL, 0x90BB8E557AF1A870ULL, 0xC38A42E27E9F7532ULL, 
            0x84562A093E559224ULL, 0xA770450A236AB4DAULL, 0x6FC951B6E690E320ULL, 0x86531A0F8CC7BBE4ULL, 
            0x563043ECE01218DEULL, 0x9C9D9885DB68D780ULL, 0xE5BDE778EC2F0620ULL, 0x2B02B784F2D2F955ULL, 
            0x12C9966F9FA0C5E8ULL, 0x2430833DF3BB928CULL, 0x500460EA5F26DC6CULL, 0x33E4A53ABBBE31B6ULL, 
            0xF81596EE254B93FCULL, 0x29AD5678D6E3E5BCULL, 0xB23527540790A1D1ULL, 0x64D6D33E195FC964ULL, 
            0x293F1C64463D5D2DULL, 0x01517B76B04CE68CULL, 0xC2D5F91CBED4324BULL, 0xDC41E8A7876681E0ULL
        },
        {
            0x5245FE968756063DULL, 0xD2924116E47FF7BAULL, 0x7FE5EA6481E50563ULL, 0x0A3B8C51E5A448B4ULL, 
            0xC66A1FA661C3F084ULL, 0x296CF6F815B5748EULL, 0xEA3BEF88D2C43C45ULL, 0xB0FE4E47702223F8ULL, 
            0xD756B3252306039FULL, 0x6EB380C468C9107AULL, 0x189F211191BD2DADULL, 0xC9FB1E62E723C876ULL, 
            0x3AB03563789CA7EAULL, 0x9BC86AD07C0A830AULL, 0x33F9ACCBF6F34777ULL, 0xB4CCAC421B310C17ULL, 
            0xD872D6AE64E5A0B2ULL, 0x5E9997D6D34EC4EFULL, 0xBF118D0A91C987EAULL, 0x86A92FEE6F597CFAULL, 
            0xD9DFF73B39D49EBAULL, 0x2E9C3753C17F8534ULL, 0x98F84A7C6A1B2D66ULL, 0xB956007EC73BA447ULL, 
            0x0AABBC14AC682DA3ULL, 0xABC57F37D31B859AULL, 0xE73586B731375A18ULL, 0x900B16628BD4D091ULL, 
            0xD1E5F2D73F42AFE0ULL, 0xDF4DB9CA52ADDBD8ULL, 0x1512FBFBFC77B972ULL, 0xD40A55997731EE68ULL
        },
        {
            0x20FB1293DD2B58DEULL, 0x2A25C8BFE243D072ULL, 0x9DA480EB844D1C67ULL, 0x97574E8E07D7FCA2ULL, 
            0x27182BE159C478ACULL, 0xCF9BC97DAD14F096ULL, 0x88E34E1C6B21693DULL, 0x96C0DD95B071BC9AULL, 
            0xEE0A53411638364CULL, 0x7D214B2F8CE48AFBULL, 0xE15ED93A466ADE62ULL, 0xDA83DA48AEBBAF11ULL, 
            0x945DBB6F93835D2DULL, 0x10769EAE1A1ABA03ULL, 0x60783FB3B6353E3BULL, 0x2096E3F205D66837ULL, 
            0x2645DAE82ACE0DD4ULL, 0x3B27C60071106265ULL, 0x9C61488249A65857ULL, 0x9D74F8CE8F81E44DULL, 
            0xCF13B826F4BDDABDULL, 0x45B8CCDA38810C44ULL, 0x63DC24AAA15DE0B7ULL, 0xCBFFE0DFC4835436ULL, 
            0xEEF4AE5D347960D8ULL, 0x2F6CD65944951F9CULL, 0xC1D54DFD39B7EE12ULL, 0x708691F5327C87BCULL, 
            0x7B3713F8FFF121D2ULL, 0x198AEC5A0CCA1952ULL, 0xDCF959AEF91AF8AFULL, 0x83AF6E37F573E9B8ULL
        }
    },
    {
        {
            0x7B7F9259E969014FULL, 0xB596BA20EAC6F7C9ULL, 0x250AD3B615DCCF8DULL, 0x559D8068D0E7599EULL, 
            0x40D12D91611B046DULL, 0x31CCDE9FA715E9D5ULL, 0x4E143C102E83D6F8ULL, 0x052AED85475DF674ULL, 
            0x290650352A04E59DULL, 0x01072239A72EA697ULL, 0xF7262D69D4EB7F3EULL, 0xAF56F65DBFE5AFDAULL, 
            0xDCB9AEE08248A475ULL, 0x0B58DFB3AA7829E2ULL, 0x52707E2D8D59B4CDULL, 0x784C2F40C1F4792CULL, 
            0x2D79AB5498D4C381ULL, 0xD6C005C96D969645ULL, 0xB0848E1A3575A057ULL, 0x423F52161759855EULL, 
            0x22CB3F03A3AD955EULL, 0x37D8D50751C06105ULL, 0x78D092087B183985ULL, 0xD6AB00335F81C130ULL, 
            0x3CE4853CBFCECC5DULL, 0x9F4A7815E436E6CCULL, 0xCFFFEFF7F3266567ULL, 0x439BDCE1D397C30FULL, 
            0xFF2F2823F52EC141ULL, 0x4D95648617D6E797ULL, 0xDE045AAE0D64338DULL, 0x73EB4A356E0C0770ULL
        },
        {
            0x3EBC167F6F06C241ULL, 0x9F006FFE70818115ULL, 0xC4D21B3C1C7D90F4ULL, 0xDAD98412BD5D7D8DULL, 
            0x68110515365BFF2AULL, 0xD95E7349B9465AAEULL, 0x7C5079616BBC0847ULL, 0xF3C4163F83621A70ULL, 
            0x58FF3B156F715DD0ULL, 0x20E77B8FA79B01BFULL, 0xE7B56FC5064F7CC5ULL, 0xAC7217D85C91332EULL, 
            0x4AEAB51C459040E5ULL, 0x3BA46D0A056C3550ULL, 0x207F48AA831521E8ULL, 0x6E7E2140FB206249ULL, 
            0xE4783887145E4608ULL, 0xA78ED6FF463A68D6ULL, 0xFE14CFBBD9840E75ULL, 0xE8C80F99ED572F15ULL, 
            0x4D819CF69C092D97ULL, 0x063C78C58BF2E3A4ULL, 0x5385802083EF50FAULL, 0x638095A172545CDDULL, 
            0x356CAC18D6925671ULL, 0x2F17F9D8263E3D55ULL, 0xFC94DE93EF9FA9B9ULL, 0xA067013E191A8F69ULL, 
            0xBFF11BB183F47DCDULL, 0x37486C56DDA0B40FULL, 0xE8EECE1F68E3DECAULL, 0xE7DE8EE074D98444ULL
        },
        {
            0x4593A3E3445964F3ULL, 0x56B1326709B3D9AEULL, 0x7187221D9F9B9D24ULL, 0x7C43A30F5F7F876AULL, 
            0xF455EE38E59385C6ULL, 0x100C8FD3E44F99DCULL, 0xFD8EA7C39C32D1D6ULL, 0x8424CC75BC0B77E4ULL, 
            0x87566C362020901FULL, 0x4941945EAC4CE59FULL, 0xEBF80238234815C1ULL, 0xB83B8C0E305AB8C1ULL, 
            0x49B376698C0C8A8AULL, 0xAD9E81A8D2CAB664ULL, 0x4A924243F52244D2ULL, 0x8A17A905C7796D33ULL, 
            0x2E7012F3E3DF4E8DULL, 0x4F6867666F61D63BULL, 0x5BE21E87C3263618ULL, 0xC54007E3FD3A4B6BULL, 
            0xE45548B3E70B206FULL, 0x1801B59D61D28D73ULL, 0x9B5E2125E877A5C8ULL, 0x23FFD64A07441E71ULL, 
            0xCD97A5265B7F9E4FULL, 0xBE80ECE97CFC1278ULL, 0xFBC177EBDA7332C0ULL, 0x5AA4E6EEC29A3A05ULL, 
            0x3671CF1EBB56A617ULL, 0x770485B37F06DB00ULL, 0x590A6DC6B617BD22ULL, 0x5EB4689EB6534AA7ULL
        },
        {
            0xA431A2FA397C8D75ULL, 0xFDA6753183FD7EADULL, 0x7C89DEBD6766EB5AULL, 0x05A60009A7B10B2BULL, 
            0xA2B22531637639D2ULL, 0x133D95BD30041C59ULL, 0xB2432B5602103DFCULL, 0xD2FB4A926BB8BD7DULL, 
            0x6BD1044A75E00593ULL, 0x7FB4DD4D8EB1415AULL, 0x7C991B20A11841BCULL, 0xF9DD068DC2E9F85FULL, 
            0x284C1F24F1D22841ULL, 0x9F42C13550D1D55CULL, 0x213E2B4365732D72ULL, 0x31C8FE12FD59D188ULL, 
            0x005FB76C57ADCE83ULL, 0xED414B3A9E858B79ULL, 0x2197C7DC24A24B30ULL, 0xA2B1A0B96C7049C6ULL, 
            0x8AE6B8B85BBA3A98ULL, 0xED579B110D9CA825ULL, 0x1D6192C898CE5B09ULL, 0x79D276FA13F27B4FULL, 
            0x5CDF72798B1DB334ULL, 0xB51382F3F38511F6ULL, 0xCDF5EEF2D380172AULL, 0x1C51B93F5A8D1149ULL, 
            0xCAF42001EEF455D6ULL, 0x124785D9E3373C67ULL, 0x15F16F33D7E8A05CULL, 0x324E8C793642A3ADULL
        },
        {
            0x4E5E8D7DE85849B4ULL, 0x2192952D2A296110ULL, 0x4B51A37652C6F35BULL, 0x25BE8E5261D9D603ULL, 
            0x2FB6C3EAAB47C697ULL, 0x9482292BD0EA8A91ULL, 0xBE8ABCC8F72201C5ULL, 0xF21D9C592CC0E7C0ULL, 
            0x5EE4D65DEC891B48ULL, 0x2CA69E4BF3239AEBULL, 0x59BC467F43D679C7ULL, 0x6A80DDB0D69ED832ULL, 
            0x58041066957B0A27ULL, 0xDCD472BEE83DD4D2ULL, 0xA981914CEEFB3BC5ULL, 0x2F853475706D1078ULL, 
            0x0D1805B758BE0946ULL, 0x2D518C0D0017B382ULL, 0xD837D13365EEF091ULL, 0x93BAB826C59C184EULL, 
            0xD8416CF3EC4A271FULL, 0xE4AAF8A4DB154D3BULL, 0x7570A525DD3D0C88ULL, 0x499D9CB0A0B24452ULL, 
            0x9FF8DF92ACD65BD6ULL, 0xDBEF71350EFBC11CULL, 0x7A1CA67B39E33C8CULL, 0xC9AE38A23D513A60ULL, 
            0xA49B250848CB6ABDULL, 0x2217BF552C376D5DULL, 0xF26F248468771671ULL, 0x21451295D34F03D1ULL
        },
        {
            0xCFCEE3CA56829CC7ULL, 0xE4146D93AF554682ULL, 0x2D161D896EF0272BULL, 0x060BFEA31A8E1B3FULL, 
            0x2A65AA039D760E30ULL, 0x5E85C5FFE693FA05ULL, 0x2E28139C6C6BF8FCULL, 0x4EEB087442BF3B4CULL, 
            0x7A08624EC6B618AEULL, 0x4079DA295DE7F246ULL, 0x9F4A832B385D03ABULL, 0x2399B7F17FB81D25ULL, 
            0xC40A119FD1084463ULL, 0x81CE83594E5EC2BEULL, 0x8FD5CCC9E0350568ULL, 0x2BA35B71D1D21A05ULL, 
            0xCA324892EFFCB560ULL, 0x60F6E3B5E557001FULL, 0x7CBFB29ABE2F73E2ULL, 0x9E343E5C8FD55A04ULL, 
            0x8BC5F0208A9EB4DAULL, 0x6D0C499E1F1DDC92ULL, 0x09C73E95FCCF51B0ULL, 0xD77F7B19E5CEEE9FULL, 
            0xC19D771106448882ULL, 0x8C0DD72A4A0425D4ULL, 0x7E9F82A6CF91B12EULL, 0x212D5CCDADC578CBULL, 
            0x3EC175B4EC296EF6ULL, 0x858F693A3A7C597CULL, 0x4FDB6FA99E853B8BULL, 0x7FD6BD9374C64162ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseFConstants = {
    0xE96F591E9E1EA327ULL,
    0x1F6739F2EB7A3472ULL,
    0x7C2A61A5F326302AULL,
    0xE96F591E9E1EA327ULL,
    0x1F6739F2EB7A3472ULL,
    0x7C2A61A5F326302AULL,
    0xAAE390DD5C62647BULL,
    0x9E5CA6B6BFD6DC8AULL,
    0x76,
    0x6F,
    0xF8,
    0x58,
    0x1D,
    0x4B,
    0x62,
    0x4A
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseGSalts = {
    {
        {
            0x76EE9046D30183DEULL, 0xB8ED4FFBCF302E7CULL, 0x95B4DB21BAA20F42ULL, 0xE7C034224CA6A7E2ULL, 
            0x7DFAD5AE1EE6FAFFULL, 0x98E457BBC1B1A683ULL, 0x114B0E6C34E40A2CULL, 0xC8F878F5926BF8BDULL, 
            0xEA152A14D513BBFDULL, 0x1D1B88BD15086E8FULL, 0xEF15D0CFA4AA8ACBULL, 0xAD66440B4FE9EAC1ULL, 
            0x603C38CF38BA6B51ULL, 0x663999A3962CF056ULL, 0xBF5938CE34CDCC93ULL, 0xD402A99EB2BC8864ULL, 
            0xAA982694DC958D8DULL, 0x246AEB06E709C5F5ULL, 0x8E05EA02ADF51795ULL, 0x6B091D44AF467A26ULL, 
            0x90F48750167FB507ULL, 0x358FA281240F5215ULL, 0xD0E778065D7E5543ULL, 0xC405F33A39199DAFULL, 
            0x28A8E0E0F6946132ULL, 0x3C5FB054E08E3BACULL, 0x503FCF9722CD41E3ULL, 0x7875191349249C6FULL, 
            0xD1449AF1573C40BEULL, 0x8233F532D103C06CULL, 0x568A8DCD7C451AF8ULL, 0xB5BE91831C34FF4DULL
        },
        {
            0x63CEC7CAD1186C64ULL, 0x7C4D1F3BBC98C6E2ULL, 0x76AB3E12B3D03451ULL, 0xFEED9F6EBDC0F8BAULL, 
            0xD69B006203ABFED8ULL, 0xB018F75B1185818FULL, 0xCF2D8FE0CE62528BULL, 0x9B8B4E10214773E5ULL, 
            0xF4FA8C4570762B2BULL, 0x8D474554BC3B8064ULL, 0x368C3B2E0778D20AULL, 0x45D46E50DE306C5AULL, 
            0x4FE2F84E41E84354ULL, 0x3C7FDFDFF9210385ULL, 0x23E08CD61DC70BBFULL, 0x44C748FC01CFDB8AULL, 
            0xED5FB07E799BE190ULL, 0x4B00E1A52DA5CF34ULL, 0xF298C2B0DED934FFULL, 0x636A60A6F18F0646ULL, 
            0x2FD02F1A99866377ULL, 0x124EE6F1CBB66D73ULL, 0xBDD396313370EC3AULL, 0xAF425423C583F312ULL, 
            0x39462F9B058CA2BDULL, 0x2E224A575D992D38ULL, 0x6F3C760E1C07D1A5ULL, 0x9ED34BBE3292EB81ULL, 
            0xC6DD31F93DDAB2D5ULL, 0xECF6896C390BE2D5ULL, 0x9379AE2E5E0189B4ULL, 0x26347FAFDC8E5575ULL
        },
        {
            0x2BECBB6D23A8CE02ULL, 0x9B3A9090B9D5220CULL, 0x8538FA2BE904E465ULL, 0x25832783C283AD7AULL, 
            0xBDF308457E6B2BFCULL, 0x1DBFCC5E30912FFAULL, 0x4AF948806582DB77ULL, 0x2EC0DC995B639554ULL, 
            0x42EF3EBDBEFA4A5FULL, 0x25F27F9CC8AD3E44ULL, 0xC3E4A54CD1FFEE0CULL, 0x9FD4B4D08AD90EEFULL, 
            0x85960AAE17B4A436ULL, 0x2ADEE30739202A20ULL, 0xAB5423490551D21BULL, 0x830949DF3A8B49E9ULL, 
            0x8E2B4AD762535BA4ULL, 0x050E44D50B460136ULL, 0x79E31F296D11EBF8ULL, 0x30D579EDE602E061ULL, 
            0xA9438F5A025A2072ULL, 0x1248B356ADC95DF9ULL, 0x4C01F43A4B80BB7FULL, 0x8D8AD4333670D15CULL, 
            0xCE2918EEE140BCB9ULL, 0xEB22DFD73DF3FC7EULL, 0x92F72437D99CDE8EULL, 0x147E82844277F9ACULL, 
            0xD3402E2DC774F049ULL, 0x501564648F3ED5B7ULL, 0xCD54C546DD96D766ULL, 0xF0EBE9F26E580F7CULL
        },
        {
            0xA3270854C9DF2D4AULL, 0x000A393291C0E99EULL, 0x1A69888ECBBD14CDULL, 0x52057C1C16A66825ULL, 
            0x3689781E10AB43CDULL, 0xEB5EA3404DE7A537ULL, 0xD9B88B7AE13140E2ULL, 0x80FF7811178AA1CBULL, 
            0x257CEAC3CB43E1ACULL, 0xF3ED4F9FBD48AB42ULL, 0x00B88B7A9B758A53ULL, 0xE0E088B6D6CE6405ULL, 
            0x6EFA94563F34A88EULL, 0xA4E8C0F9BA54AA94ULL, 0xEFE1171B9895F244ULL, 0x161A9CA33C6853CBULL, 
            0x4B626C988381A359ULL, 0x7429C8AFD169876BULL, 0x2B4789D995E5C595ULL, 0xE1BD76F20868A0C7ULL, 
            0x44E05D11E9F5101AULL, 0xCB231A458CD61423ULL, 0xC6FB2002E8559FF6ULL, 0xCBCD516E2DC9BE0BULL, 
            0xE02911C1C65FE701ULL, 0x83D79747BDD0944DULL, 0x17664DB36C8662EBULL, 0xDE9C3CF789374E0DULL, 
            0xA4D5238A4D625FE0ULL, 0x362AD8D7234316DAULL, 0x4AD852BF123D0EF8ULL, 0xE289BE91915D71A7ULL
        },
        {
            0xE95A1B23631D8179ULL, 0x371B3AEE0417480EULL, 0x4A6B39B814DD683AULL, 0x53FBA7D7FF144B24ULL, 
            0x06D29DE24094CA09ULL, 0x3FFB61E7A89ABC40ULL, 0x00FA87D067339BEBULL, 0x6EAA2331570043C0ULL, 
            0x89773BF674BCBD8CULL, 0x58E9F00B14DF0602ULL, 0x27534812395EBA97ULL, 0xFF14DCA71D8D592CULL, 
            0x64661D43F7D27A5CULL, 0x08251BC9FC363871ULL, 0x0AB2F03222355D6AULL, 0x2DE1EC5F281D8CA7ULL, 
            0x7BB391CA284F0FCAULL, 0xE4F3BF9B5BB03C10ULL, 0xA3F5DF1C39D726A6ULL, 0xF84B656B92659F2FULL, 
            0xC0CD568B943FBC8FULL, 0xA6C91838F1A4432CULL, 0x07B627B7872E3AEEULL, 0x262C586ED4AC7B6AULL, 
            0x8B5DCB2AFF2ED1BEULL, 0x420B44E89A660F32ULL, 0x1B32619624D09CE5ULL, 0xBE0759E7AE4518E4ULL, 
            0xAB0AB9A45EC76455ULL, 0x1FAB684F083E9ECFULL, 0xFD69C37F5EB69FA6ULL, 0x99AE2C147784A8B9ULL
        },
        {
            0xB438C079033ACFFEULL, 0xE9406AE205F52F41ULL, 0xEC810548B7119910ULL, 0xCD6DCE9FF84D2717ULL, 
            0x2EEE4479B3655B3CULL, 0x12160AD9FB670E79ULL, 0xBCA81C84345E50CDULL, 0x18382178470769C9ULL, 
            0x6CB63D183956A163ULL, 0xA8A7606F4C380AABULL, 0x64A3B9BBAF68464AULL, 0x87D6E811539D914DULL, 
            0x14835D09010B2FBBULL, 0x9B04038CECB8A9C9ULL, 0x3CCF984C51B19456ULL, 0x8D01170D65195A6DULL, 
            0x98AFC0D707344DECULL, 0x72DA5DBAF1DB4A3BULL, 0x66392D12787DC6D4ULL, 0x9DB0089A6E5D92E0ULL, 
            0xE09678A5B923C34FULL, 0xF96695B70F3702BCULL, 0xC195EF3996775B18ULL, 0xAE98471DBD7956D4ULL, 
            0xBDFAA7D38A99D2BBULL, 0x2A38A413936950B6ULL, 0x1591D2D4846167DCULL, 0x89E0FC391378B180ULL, 
            0x69A85E5CD617AEFBULL, 0x028ACE1049727655ULL, 0x8EC60C5444DD2DD1ULL, 0x01242B0F4E57561DULL
        }
    },
    {
        {
            0x049AB77D61F23485ULL, 0x8416F341D9365918ULL, 0x6ED901D8C09774AEULL, 0xC124890426F982E0ULL, 
            0x266775A4D87DA7E4ULL, 0xFA2FAF07A158A464ULL, 0x2EFBAFED224DFC45ULL, 0x1A16A1C0677EEBF0ULL, 
            0xB65CD429798A4811ULL, 0xEA5009B9901BB107ULL, 0xD90AC4574F033BF8ULL, 0x76E9B976EDD4DD75ULL, 
            0x4362F027C1B1DA01ULL, 0x06E919E3B9C354B4ULL, 0x3A0719ECB8272225ULL, 0x85E8EE28050EDD31ULL, 
            0x7F6B2443D971F0AAULL, 0x84FBB63940AF330BULL, 0x3290C7F9FC48A24CULL, 0xFD28D0325BD7A75EULL, 
            0x16F0581ED3DB5FC2ULL, 0x2D9B78E3321FA11DULL, 0x939058BCCC7FCBF4ULL, 0xB3E0B86EC1FE01CAULL, 
            0x48EBFEA972435B45ULL, 0x66D60DB31EC52DE8ULL, 0x0D6AEA45CDCAAF4BULL, 0x8B197A3C4E092BC2ULL, 
            0xA8505ED9BD9E7C5CULL, 0x3D6C9D16672EF15CULL, 0x79B496A60C9F309AULL, 0x2B356C3D7F0FE89FULL
        },
        {
            0x9E04EDB231AFD07FULL, 0x08C67E7AA29A4B33ULL, 0x2244B3B21442B777ULL, 0xFDC5A7D787131423ULL, 
            0x749F73ADB4DADCF0ULL, 0x5A03E09CBFB4CF89ULL, 0x4A5CD5537D7380C5ULL, 0xE6887139E9BE3E29ULL, 
            0x2041EEBBB0432A2EULL, 0x29F194B6C6EB1595ULL, 0x6040807475B189F0ULL, 0x96B5F5692E04B498ULL, 
            0x0440B70AF9DEA483ULL, 0x012DCF22685DA09BULL, 0xD2A1BB774F322B77ULL, 0xA94CD2EC39659349ULL, 
            0x76C452206859284CULL, 0xF52E0FB186EA31F7ULL, 0x0264280C983BD714ULL, 0x008706E0FB535BBFULL, 
            0x716046E8C192F7FCULL, 0x219C1D6F62512D64ULL, 0x96CB89FAC28E0D30ULL, 0x2D5E45C056F2BDE2ULL, 
            0x26D58770EC999CE5ULL, 0x033F97DEF86E83E4ULL, 0x8A108E0E9950A643ULL, 0x24A5DB89A842DA5EULL, 
            0x789041C32EE247A2ULL, 0xB1057E9ECE0624B5ULL, 0xE1773E488FD1746FULL, 0xD2AA5B861EBA3CB8ULL
        },
        {
            0xDD8561DEF07BDBB6ULL, 0xC72DE91918A7BDD0ULL, 0x7054A29565304653ULL, 0xB8063C947B640C7DULL, 
            0x8E458629737DEDF5ULL, 0x46A5FBD429C28744ULL, 0x6E40F288CC03E8C0ULL, 0x55CD00AAC909DDD5ULL, 
            0xE82DC420E53C4AB7ULL, 0x349A55FF6C458C0AULL, 0x526A8679AE69087DULL, 0xC6CFD6EBB8772E78ULL, 
            0xE4C9E28FC3B43E01ULL, 0xC1805F689AC27C52ULL, 0x1FE82E27B351B095ULL, 0x85D82758E68FE691ULL, 
            0x583F3ABB53D85123ULL, 0x23FE6F2DCF1ED192ULL, 0xFDB36BF2F2332D69ULL, 0x4C4D2ED4671BE4B6ULL, 
            0xE82142BC8FE81504ULL, 0x4834E5D20CC2260EULL, 0x9A098CC159575809ULL, 0x4B0A98BBA2C12A7AULL, 
            0x6FB2617EF13288D4ULL, 0x68386BF0DD34DD7DULL, 0xC5DC0E15F5D70F56ULL, 0x2F9360B55C674029ULL, 
            0xAB24A6FF3C96B7EDULL, 0x57040974AB215E65ULL, 0xB6B4373066355541ULL, 0x39D4CF3164BD4CEDULL
        },
        {
            0xCF620E7637E160B4ULL, 0x7295EA34F34E2590ULL, 0x1B001409057BA7B5ULL, 0x79373233FBD246EDULL, 
            0x2CA5667AB55FFDDFULL, 0xB02F92F1858A0AD4ULL, 0xD98A69083317C4D4ULL, 0x827F65B2E54FD049ULL, 
            0x6DD3C9FF4A18CFCBULL, 0x98E6CDEFAADCE6E1ULL, 0x362BD473105A8A49ULL, 0x67ED1D48FD08A6F5ULL, 
            0x42A60751259A4027ULL, 0x2A1EEAE35EA57641ULL, 0x76123463A995A6B9ULL, 0x56691DFCD79564D5ULL, 
            0xC647E179D0F9EBB0ULL, 0x033795FE2E7BC928ULL, 0x6047FC653801DE3BULL, 0x802555A3C3EB4E20ULL, 
            0x1483D317ED3BB0B0ULL, 0x6D7AF558CE2C8C9CULL, 0xF05C5FD862003646ULL, 0x19C1709569924DFBULL, 
            0x83071E1A48BEADABULL, 0x63E3AD6895379C87ULL, 0x895D621C364894D1ULL, 0xCB4045ECEA6BFDEBULL, 
            0x52C31C90BCD2B718ULL, 0x6A259E038A6E183BULL, 0x86E5A0A428B23E2CULL, 0xFBF3B12A6848941AULL
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
            0xE929705C243ED7D5ULL, 0xCA5916E4AE167772ULL, 0xB0D0C8BE4D66001FULL, 0x53014FB293719D6EULL, 
            0x53741690066B3958ULL, 0x58D19668D8585B7FULL, 0xB1A619680AA06952ULL, 0x122DE2BBD0BA06DDULL, 
            0x720974E0A8652497ULL, 0x811A1681CC82EB72ULL, 0x99FD8CD0B1331EB7ULL, 0x95AC7610025BE301ULL, 
            0x846C705EF58155FCULL, 0x3D55A0BEB3820AD6ULL, 0x2E40FB6D88521E49ULL, 0xDD0C2620AE8EA5A7ULL, 
            0x7CB8AAA891A4FEE0ULL, 0x8DEDC9380C0DC691ULL, 0x31157071B5E84351ULL, 0x06E53D4414E84FBAULL, 
            0x720D0C7FB376BD1AULL, 0xA225FF3930036BA2ULL, 0x4DC26FF0DC93DA58ULL, 0x1C169F72A3DB68EAULL, 
            0xEDC8AD096E437612ULL, 0xA834D502DF29A4AAULL, 0x059A0AF85A889C27ULL, 0xA3562D9E98ABBB12ULL, 
            0x90C28CF23EC77DE0ULL, 0xF5CF30DE07BDA53EULL, 0xCF66B401E5389548ULL, 0xAA69D4BE955DC143ULL
        }
    },
    {
        {
            0x16F819BCF1FFDFB3ULL, 0xB55B8267F311396CULL, 0xE0ACF22D4B9E9F72ULL, 0x372F97582766884AULL, 
            0x8EBA87FCFB6E28D9ULL, 0xFB8071B1355F3722ULL, 0xD3E997AE25388BA2ULL, 0x047E32983C977227ULL, 
            0xD1A5D7B760A79392ULL, 0xC6E7102185FFDE59ULL, 0xC1AE541329861386ULL, 0x040B303985385DC2ULL, 
            0x6C50DDD6BC79483EULL, 0x6314E95070A335A5ULL, 0x22979F66E352508BULL, 0x56713C8498BB4897ULL, 
            0x1C3FD060916C876DULL, 0x56C2988A99FDCF81ULL, 0x0AC34D9F7808C987ULL, 0xBBD5ADF4E1635F35ULL, 
            0x98041B7BC49108CEULL, 0x0C75CF7FC90A0CAEULL, 0x4039AB392ACA06E7ULL, 0x97B12ABDC29482A1ULL, 
            0x3DADF665D93E2341ULL, 0x3FE7C9B295CF56B6ULL, 0x0AE31DBC11E75554ULL, 0x12B769040BDF9C7BULL, 
            0x24B3402686711F74ULL, 0xF9D4014BF9C75042ULL, 0x0FF243D13E784DF3ULL, 0xA74FC3196E5C1FD6ULL
        },
        {
            0x1D86956BD6C1784CULL, 0x44D450FA938E0BB6ULL, 0x003AF20F9511286CULL, 0xD0C6B83B63F1A273ULL, 
            0xE5C95FC82CA44C06ULL, 0xFF5B9753BD5BD6E4ULL, 0x6B7EEFB99FEF8251ULL, 0x1B5CE28CB1499265ULL, 
            0x06FBB1468E516763ULL, 0xA5DB972B44E491CBULL, 0x71B4036E4688DC45ULL, 0x8B68A0EE9803C0D8ULL, 
            0x309628E86AFF75BEULL, 0x370A49019A5FE427ULL, 0xC445DE478014B7B9ULL, 0xBA535BE863A895DBULL, 
            0xED628D7D3B7211EAULL, 0xF549D52D3D21A29EULL, 0xD686F7A1838F0E31ULL, 0x110F8109BC3F9AECULL, 
            0xE3FB2CFB5C13750FULL, 0x1088E58854A48634ULL, 0xBC5475FA00B3610FULL, 0x428E1E6EB7198EDDULL, 
            0x98CB790D0DB668A4ULL, 0x8D8A1723521804F2ULL, 0x7630E8BC5CE0FC55ULL, 0xC703FEAF839D75CCULL, 
            0xAAF550725B3DE522ULL, 0x8F9AA14120F67927ULL, 0x7EBA11AFFAB170D5ULL, 0x71F53BCA58F8133EULL
        },
        {
            0x8080A98DA9EBB8FDULL, 0x7438E1DDE6AF04EFULL, 0xA38F7590306EE7BBULL, 0x77888DDDA41FD3C2ULL, 
            0x2E71BC66CAE5A874ULL, 0x4CC5B8477B2FDE9DULL, 0x82EA414A0A7F38E3ULL, 0x7B69DF03B202F46BULL, 
            0xC1A23547B42DF5C0ULL, 0x60E9202CA31C742DULL, 0x810705E073C9DF73ULL, 0xF77DB18FB0A28B1DULL, 
            0xFEA05D774070172AULL, 0x3887D9952D17A153ULL, 0x6BAD4C5B2B0DFD83ULL, 0xB218510951AD56CEULL, 
            0xB0DEC3E54A743511ULL, 0x224CA2688F8AE5CDULL, 0x86DFAFA400B0B0F8ULL, 0x99DA6BB67499FB6EULL, 
            0x6FD6B24C81EA629EULL, 0x83511BAE5E2ECA31ULL, 0x83DEA2AD916E295AULL, 0x682E33A647F4FCC6ULL, 
            0x11D39B4A0867B8BAULL, 0x86850AF8C9C3BFF9ULL, 0xAF8CB47A047AC02BULL, 0x14CD6058A67DA5A0ULL, 
            0x23EE0D9C772BD720ULL, 0x926104815C367709ULL, 0x9664B08C544DC966ULL, 0x09987DD05EC5339EULL
        },
        {
            0x2045EEEF16B3345FULL, 0xBC6B1D7D7F289F93ULL, 0x479BEF774B9D6067ULL, 0x939A4B3EEABC783BULL, 
            0x351ED6806CAA728EULL, 0x3FB11AD90EF6D81FULL, 0x9EC0B3DC9CAFF0CBULL, 0xCD909FFD4A777867ULL, 
            0x8ADDECE3E05EE0FEULL, 0x3FE4EF93EB9FE42FULL, 0xDE12589436FFA807ULL, 0x40C18D3FCF4ECF6AULL, 
            0x5A0C90BDDD5E0C04ULL, 0x9DF898DEE6531416ULL, 0xC136A37AFE2DE8B8ULL, 0x2EB7F8E27E386386ULL, 
            0x9BD52CC47BCE4875ULL, 0xDC321B8BA13D012BULL, 0x8822169644444C55ULL, 0xF874B6B7D220F2A7ULL, 
            0x72D807EDD9A67E4FULL, 0x60C772F252E88852ULL, 0xE1ED05D9A63F4375ULL, 0x7A30FFB997329832ULL, 
            0xA6E50374A07F5645ULL, 0x50101624D6BA4FA7ULL, 0x9060193F4240A201ULL, 0xD0A9A6BB593D6E3BULL, 
            0x8AFADF65C187F53AULL, 0x9302874EA5B76119ULL, 0xBCA831F546D9D548ULL, 0x0BE5D264EA9D0301ULL
        },
        {
            0x929F1F46CE95518FULL, 0xD4F2E09AA26D2787ULL, 0x6AEAE996129ACFA2ULL, 0xA65062FF8D4E19C1ULL, 
            0xFD59CED0503C7215ULL, 0xDA363D2D16E38391ULL, 0x208D26AAF908880CULL, 0xD59420ECC2FA74FCULL, 
            0xF2BEE8178006A1D3ULL, 0x75060BD629674199ULL, 0x434C67AC83334875ULL, 0xBE2D345FF91F4AACULL, 
            0x8210EA3463AB08D3ULL, 0xADDB50A1DF8B09E0ULL, 0xBF790B4132C25428ULL, 0x717AA798E3CA1D1AULL, 
            0x2E9C790AFF35A4E4ULL, 0x38A8E4F165A7F81CULL, 0x1A845CD4377D3D3DULL, 0x9AA6E660E83F3127ULL, 
            0x541213D854D416CCULL, 0x98F23FCF5CC64595ULL, 0xC4B19C7194C86C44ULL, 0x1AA7E612D3E1066BULL, 
            0xE24B9E1EE0B4B7D4ULL, 0xC4B5425F94CD5502ULL, 0xAE95E564C106471DULL, 0x181391BACE8A5947ULL, 
            0xCCF882B70A0C5172ULL, 0x17E3760BDF8A434AULL, 0x9BDA7914149951C5ULL, 0x84DB3AFAF5229EFCULL
        },
        {
            0x310A2E073464C3F9ULL, 0x7E4372C40F12431BULL, 0x4FEBB8A78C0BBAECULL, 0x0F253CC2DA71EBB1ULL, 
            0x48B091B8A482CF86ULL, 0x6A58C3BE372FA1D1ULL, 0x4325F02092B6D441ULL, 0xBE3073B765C8DA65ULL, 
            0x070622BEFFA72682ULL, 0xF872D97D0CC4F752ULL, 0x29EB760F1BB134F1ULL, 0x191B7B46DFC994A4ULL, 
            0x71A3D885020BF326ULL, 0x90F59F9780896B30ULL, 0xB32078D788452380ULL, 0x75088BB54850DFBFULL, 
            0x5E4E52C450AD77D8ULL, 0x8C97FB49A20B66F0ULL, 0x41717392B9481BE8ULL, 0xFFB421111D746107ULL, 
            0x400D49B90B1BEBB4ULL, 0x5E44F8D64584AF3DULL, 0xA24565EF0D464DADULL, 0xE9DD0E472CD6C0E8ULL, 
            0x9618F0496392D963ULL, 0xBCFC21BB8D101986ULL, 0x18906540BC32B15CULL, 0x3D2662966EABDBBEULL, 
            0xD02FD225875EBA74ULL, 0xED9FD36A05EC32BFULL, 0xC68AF793712CB1EEULL, 0x6BADED1F62E90107ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseGConstants = {
    0x5AE125219A939280ULL,
    0x591FE29E1467D7E8ULL,
    0x256CD7326292C700ULL,
    0x5AE125219A939280ULL,
    0x591FE29E1467D7E8ULL,
    0x256CD7326292C700ULL,
    0xA9A6E1775F7E2E97ULL,
    0x578AC5AA42D986DFULL,
    0x46,
    0xE7,
    0x55,
    0xD9,
    0xA1,
    0xBD,
    0x2F,
    0xF9
};

const TwistDomainSaltSet TwistExpander_Canopus::kPhaseHSalts = {
    {
        {
            0xFA8E3E59437C3708ULL, 0x5249F81F5D66750AULL, 0x4723DC4664DAC93EULL, 0x6031AC94676FB900ULL, 
            0x955E607D3DA7A2F7ULL, 0xB5C74576529DBC2CULL, 0x45E2094CEF8F8A6BULL, 0xA9FBFF0FF8316805ULL, 
            0x154E0AF98A8AA664ULL, 0xD5F8409303F15E72ULL, 0x6C269371BEF48EF3ULL, 0x99DF467DA687EF87ULL, 
            0xA9B9E20707922EC5ULL, 0xCDDADAA83DE65DFFULL, 0xE71FFADA5FA94D55ULL, 0x4FF6FE4757328F9AULL, 
            0x266D74920F26536FULL, 0x4C43F71994BACD7BULL, 0x7C89B1D3ADE36F62ULL, 0x88C459D737775220ULL, 
            0x5B86FDD84E6B27CEULL, 0xC4A3D744E01B9353ULL, 0x0390773EE42989BEULL, 0xBCAA67FB2650E15BULL, 
            0x82C893388971460DULL, 0xBFB5739E24F5B966ULL, 0xB4654250022C2148ULL, 0x1349402EC393D744ULL, 
            0x095F723E00635F89ULL, 0xCEC6AD2D74507765ULL, 0x2FBF6E2E1BD009E7ULL, 0x811C694C1C622866ULL
        },
        {
            0x89C3473B1B8E8DB3ULL, 0x838C8918D3984CD4ULL, 0x3310300E502A0F0AULL, 0x98855382DB0C10A3ULL, 
            0x9422B45662D428D2ULL, 0xEDF33F58B02B2B08ULL, 0xA254FA9493295CA4ULL, 0xF43D2AFDBA59EA02ULL, 
            0x44E2EDE435DC8F7FULL, 0xD80743C7DE5E126DULL, 0x3EFDFC5BBBB66EF6ULL, 0x8E1F26635BB0C40DULL, 
            0xA409273363E91852ULL, 0xF7CC03CFC76C49D8ULL, 0x36672942AA44C9EEULL, 0x18E068A6CBB061B9ULL, 
            0x512D605F64A8FB2FULL, 0xC3696F20984B3668ULL, 0xCDDB689F4E579F2FULL, 0xE9193B2018E601B6ULL, 
            0xA4B0D98C26F47609ULL, 0x3A1B60DB21A7EF2DULL, 0xE85B281FC76B56B7ULL, 0xA022827639F78062ULL, 
            0xDBA41E37852E700EULL, 0x279D3767D400E616ULL, 0x00EA9AFC121F8EE1ULL, 0x7A7AAC6C7B9F5857ULL, 
            0xDCB22D2E34865E68ULL, 0xA8F9D0684310611BULL, 0xDCC4ACD92EB0EB5FULL, 0x644548A944966A44ULL
        },
        {
            0xAA5EBAC8424ACE6EULL, 0x7341A17A291C5C4EULL, 0x5531E029917D0E60ULL, 0x3EC41EA80D835E83ULL, 
            0x019AC4E59B411DE9ULL, 0x5C1BAF0E934B12D4ULL, 0x7B16DA8CBD8481EBULL, 0xBA8DB5E19DCC73D3ULL, 
            0x7C4682D14345E59BULL, 0xF9C5252B1CDBCFA8ULL, 0x3546466914D5E145ULL, 0xA946C8AE0C408BCDULL, 
            0xAA48A97C34D1DB1CULL, 0x9CBE35A6AF4B25CEULL, 0x12B2F63D34B4D093ULL, 0x42677EE40A1F380DULL, 
            0x7F9D46AF414AEB83ULL, 0xBF279749DE70FE51ULL, 0x92BC4E9568CD0085ULL, 0x77EFE5DC9808DAA2ULL, 
            0x5E1ACB92AB15F3D8ULL, 0xA8AD86E4AAEC9BBAULL, 0xD8676C826C9BD06CULL, 0xA33BA73B4B0D9A35ULL, 
            0x9AC889560E0BC4D7ULL, 0x2D8CBA830B53A613ULL, 0x84C813B5A2F3D6B6ULL, 0x3B49A2B4BE3DF15CULL, 
            0x5968D41F19E606ACULL, 0x2F53469EDA175968ULL, 0xD3052F27A031848EULL, 0xB4620965F5C8A1B7ULL
        },
        {
            0xA32A93919971CE6AULL, 0xF75CDD5E90AD94E5ULL, 0x3FDC232D62A8A9A5ULL, 0xF6B96D1452CB399FULL, 
            0x0DEE74908F735408ULL, 0x45AE04E11A0964A7ULL, 0x8ED442CB88B80FB6ULL, 0x4CC9C072DFD48222ULL, 
            0x4ED825A15E4AFBD7ULL, 0xAE6D50C1CFD86FB9ULL, 0x6A2D0FC5399BBCBAULL, 0xB453BA0138ED887EULL, 
            0xF6A7EF1706F3934EULL, 0xDC8CC92B7934A415ULL, 0xA3DA45E3A1A8D7E8ULL, 0xB01EC957967D334AULL, 
            0xF3EEA8D3E11DFC0DULL, 0xEA6DE94EE2A4703AULL, 0x40EB6952D3C4FA98ULL, 0x8A84EAAE2C41A033ULL, 
            0x46D2251781794BC4ULL, 0x8B6B0F7D428F07F1ULL, 0xFBEA20C714838883ULL, 0x82EFC4ED3922543BULL, 
            0xF59EB3857C938BE1ULL, 0x58AC14091753DF64ULL, 0x55AC0EF530BA1C81ULL, 0x2C35BC8587D59059ULL, 
            0x0701B74E932EA925ULL, 0x30A49B45857DE9AAULL, 0xC71C1F74ABA8ED82ULL, 0xDB1007CCB1F237E7ULL
        },
        {
            0xD577EF0BB0FDEE94ULL, 0x4E0DC950B8B168E5ULL, 0x1A4CDAB5659C45C7ULL, 0xF51E3F13E2B68455ULL, 
            0xD0D62A774EA4E957ULL, 0x3168F753CF286753ULL, 0xEE58A0027C0ED475ULL, 0x33F62D94AA4879C8ULL, 
            0xC0B022E63D82B481ULL, 0xCF00A5BDCB0CC15FULL, 0xBDF5E24ADE30F620ULL, 0xD68553629D48136CULL, 
            0x61E68E47476B5B01ULL, 0xA795E7291B87F221ULL, 0x50F22ECA23A966BAULL, 0x90C0BA3FAD328B76ULL, 
            0xECD409FBF58B6286ULL, 0x17976636861CB05CULL, 0xF59DEF644B54AFD9ULL, 0xBA1AB671A6093A25ULL, 
            0x32A371B67208677DULL, 0x250956D67A1A2B23ULL, 0x1CCC085C822C7B88ULL, 0x2B7866820071888DULL, 
            0x0A88BF45BC102B53ULL, 0x7828221E1C4EAF44ULL, 0x48156AD48CCA71B0ULL, 0x118ABE2735357630ULL, 
            0x879FE56F2120F691ULL, 0x0AAA02BDB732626AULL, 0x63F6B400134CB524ULL, 0x5790D72CEA1B5F40ULL
        },
        {
            0x7F954EBF27A2B279ULL, 0x48358D4AD87A8668ULL, 0x6D9358396269DC46ULL, 0xF0A6FAF1954A48AAULL, 
            0x3A5EAF5823645451ULL, 0xE14F6DAFC6848868ULL, 0x5F64DEAC6DC68936ULL, 0xC5F9D239FD5960A1ULL, 
            0x87B78DF3CCFD7E5DULL, 0xC83F898F9282C588ULL, 0x1E2A724B409DB7FFULL, 0x5D38B1AD2EEC5EEFULL, 
            0xAD6A7EFD0281D857ULL, 0x9795696A60534850ULL, 0x4B7E8F78AAA4C4F3ULL, 0x48EF234882643516ULL, 
            0x3A26312CDDA0EE4EULL, 0x602BF4BF4855C057ULL, 0x6106BA6B62BF60C8ULL, 0x219BC9C5AFED8B05ULL, 
            0x044927C90BF4FB8AULL, 0xD6C6259C9739D4E9ULL, 0x5F3124BBCFF39C8DULL, 0xDDA8D22292280768ULL, 
            0xEEB4ABDD13DD9D87ULL, 0x17621F01F89672A0ULL, 0xA8C7AEFF7CC843F7ULL, 0x380D0D78ADD97B06ULL, 
            0x907E00000A95BAFCULL, 0xA7C6E7352CAEBBD4ULL, 0x8BF615E3B6107B18ULL, 0x7A18F8D260F63A46ULL
        }
    },
    {
        {
            0xEA2867067D16D618ULL, 0xE2932F6C6CF00A06ULL, 0xE24E65B438EB6FE4ULL, 0x9770CC2F225813E2ULL, 
            0x6AA21E41F065B368ULL, 0x3AC72BA430B315CEULL, 0xEDA383F5FDE40687ULL, 0xD0E3C542896D1C59ULL, 
            0x149FB97CF9B8645AULL, 0x4E50D25D8FBB6356ULL, 0x72CA08E7580B778AULL, 0x9A22DA3A3A7523B9ULL, 
            0x85FECAD7DA9F19D0ULL, 0x798FB5297789A0E8ULL, 0x5B69E7D0FDE56C29ULL, 0x20818AD66C08BEF3ULL, 
            0xF20615297C8E969CULL, 0x5C72651F9F3D5713ULL, 0x750956EA623E2738ULL, 0x7F355A9FF598DF09ULL, 
            0xD2F2A0F6E93B8131ULL, 0xB16E48F7182DE97AULL, 0x5CBA51A12822E82FULL, 0x1D97026497564911ULL, 
            0x0C95E917D57347A7ULL, 0xF74B7383E57C1D70ULL, 0xD81CB92314CDC089ULL, 0x20AF7C3D30A1BB42ULL, 
            0xDAF488CFE7F11A35ULL, 0x8637170BB415ACCDULL, 0x9A959DF164D606D3ULL, 0xDB64ADF7088D3CABULL
        },
        {
            0xA64E9DB7B1FF54CFULL, 0x472D060D0E7E66AFULL, 0x4787F486E765C0E2ULL, 0xE06E4E94B754C7DCULL, 
            0x6F1BF0968EFA6768ULL, 0x48D0AE0A1917DC70ULL, 0x917ED3739AA5E77AULL, 0x5DB69972B81E235CULL, 
            0x6383338F0206BE53ULL, 0x571418CF6F6FC3E9ULL, 0xF596F6BE0149306FULL, 0x6D05B70CA9BD76EAULL, 
            0x148613BE8FD2BA64ULL, 0x4906937D2D963283ULL, 0x47CC66D4D3091E4AULL, 0x465E60A06FAECC45ULL, 
            0x448D2CB354FF1296ULL, 0x71FBD94612B48114ULL, 0xF2992557454DDDC5ULL, 0xA7B36E84B1783922ULL, 
            0xCA0296612C7DB516ULL, 0x89BFFA66E862C651ULL, 0x63FCE7EF625A89B7ULL, 0x73F42AAF9DB374B6ULL, 
            0xFF9C4EE30BA2AC08ULL, 0xCF47321BE61600A5ULL, 0x3205A4CA5B837927ULL, 0xC93D1167D6681BCDULL, 
            0x933BB64F27F0BBCCULL, 0xB4866262C7CE72B6ULL, 0x18B2F8D374A11B3BULL, 0xDEE6DCFA5619A939ULL
        },
        {
            0xD860B1AB1353A690ULL, 0xD931F2EF7342D8D7ULL, 0xC537D29164727748ULL, 0x72F157ED46074F37ULL, 
            0x9158CA8C24517369ULL, 0xEE11C85002A54D2AULL, 0xB2E6F0C52543A4D1ULL, 0xA990C64A79A4771BULL, 
            0x0C5F42F86086719AULL, 0x16F04DC4DEF920A0ULL, 0x317C5DC14C751A25ULL, 0x399B357E7C8F33E4ULL, 
            0xD8492A4EED8A484CULL, 0xDB5DB027E110EDD3ULL, 0x64928A4ED777A73BULL, 0xFDFF88661CA5CDE1ULL, 
            0x293BDBACDCC62B62ULL, 0x584BEF2F04C2CDBEULL, 0x94A639F6EFBB6FA0ULL, 0x09CA88BACC96DC06ULL, 
            0x1AF805B6E39A3E52ULL, 0x65AA49890CC3A8E9ULL, 0x63426978920D5E28ULL, 0xA57B91E43D206D80ULL, 
            0xDDFD7E6B9C9196D7ULL, 0x066CB195DA5E1751ULL, 0xB86F6D8DF4C0A58BULL, 0xA35894F5A915412EULL, 
            0x23C938608382B156ULL, 0xA33166B2344E6C1FULL, 0x0CA6F69720393DE8ULL, 0x4A4BB81DBCBAD8C4ULL
        },
        {
            0x0A0729C9A0F5BD92ULL, 0x171315F4B19127E1ULL, 0x2CBF145D0844DBEFULL, 0xCB681CAA06BD4C07ULL, 
            0x1869677EE06168E8ULL, 0xA591E210A239FA34ULL, 0x76509072FDED9D90ULL, 0x5EA636952D38E63DULL, 
            0x19448B0E14EA28ABULL, 0xFA7D1B6F17F2BAA7ULL, 0x130AD45313B3F046ULL, 0x26A2BCBCD5FAC7B2ULL, 
            0xCC69FF46FBAF13B5ULL, 0x18E87C72AAFFB258ULL, 0x5CEC3D01457E0B52ULL, 0x577713196340BA73ULL, 
            0x39BE83A57B8BE2ECULL, 0x5100B1601A435F00ULL, 0x0E8310EF8518E756ULL, 0x7B9FAF55090217F1ULL, 
            0xA199CA0795C2E893ULL, 0xC835AE1258AD6F65ULL, 0x963FEF3DC11DE9EDULL, 0x410D77301C211623ULL, 
            0x1B6EB6F9A8B9657FULL, 0x9090A5FDF46BCDAFULL, 0x2FA8449E59886417ULL, 0x2CEF3BCA3DFF487FULL, 
            0x3A34FD752A1B1C9DULL, 0xDC1FF2FC581CF491ULL, 0x64CDF5A88CD6CE4FULL, 0xDEAF1C9B299CD90BULL
        },
        {
            0x292372971E44A91BULL, 0xAF2203D8AA08E09FULL, 0x033EEB26C544D963ULL, 0xF78083C43C6BBAE2ULL, 
            0x849B078C0FB95F8AULL, 0x53CDBC111A34B6D3ULL, 0xC9C9E464DA595EB8ULL, 0x1F606B47C391C7DDULL, 
            0x6D68F0972FC5AE90ULL, 0xAAB821220472C106ULL, 0x5980FC738FB926F3ULL, 0x252621F126750A8CULL, 
            0xA08530FD59444D5CULL, 0x1C3B1D670F73F0DAULL, 0x353FB5F65E162AC2ULL, 0x8F7264DE3D1EE5D8ULL, 
            0x798442052C590032ULL, 0xD45FED6F0FB96B99ULL, 0x8FFAA0A5AC1AA696ULL, 0x79EDB7E45B93015EULL, 
            0x9C6BE924848E5B39ULL, 0xD54E1FFF650445DDULL, 0xF4E119AB8DD36C9FULL, 0xB2F2D4208F3E1443ULL, 
            0x39BFA5C49C3B92AAULL, 0x95110833D3E944ADULL, 0x1C658377BF6C0B1CULL, 0xD815F60E0690F047ULL, 
            0x060862E4E5463A07ULL, 0x24F3A1DDB7EA0A92ULL, 0x54BA48CBEC6CAAA1ULL, 0x613EA144ABDAADDAULL
        },
        {
            0xA58ED01304FF6A9FULL, 0xCB2028F6B5A9B833ULL, 0x2477F25886CBC34AULL, 0x57C71E31EC856030ULL, 
            0xC69A2A811CCDA085ULL, 0xC5A067217EAEE9E2ULL, 0x54737C47E86D83CCULL, 0xE0C47508893339ABULL, 
            0x40A30AFE9B7F5BD8ULL, 0x25669D0D3F12B4F9ULL, 0x0FC62857DAFFFC69ULL, 0x6C7E33C19D4597B7ULL, 
            0x33E015793C69C3F8ULL, 0x053E0C650F6EBA17ULL, 0xE7C34C04113FB535ULL, 0x79ECC1A106369EE9ULL, 
            0x3CD4CC2F1723ED59ULL, 0x54023886BB7D1073ULL, 0x2D70FAFBD6768568ULL, 0x451647BFACD0FCF1ULL, 
            0x50EA7ED5F7846374ULL, 0x3441C03BE8D876ACULL, 0xA5D84645E63530E6ULL, 0xDE7A1ABB8762C6DFULL, 
            0x89CB8B6F15337881ULL, 0x3F551CD79730743EULL, 0x308010E762B71BAAULL, 0x078E24EC608C2615ULL, 
            0x29ED39700C02C10AULL, 0xB459670BD37EA6EAULL, 0x0933E4A6EB7EBC15ULL, 0xEDABEA1B95723B9CULL
        }
    },
    {
        {
            0x6F7DC1B33497A807ULL, 0xEDFD825146DD096DULL, 0xA5F48E31DC8224F5ULL, 0x550095AF48EB1FDEULL, 
            0xB3AAEB9B3625ABC1ULL, 0xF22A6B850FC6EF07ULL, 0x9D13D835DF001523ULL, 0x34D1FF52A647052DULL, 
            0xF2287C3DF41B1CD4ULL, 0xB2CE94D8066CC555ULL, 0xB05A64F2F5E2E686ULL, 0x8F24B8C29A749229ULL, 
            0xD1EB7DB5C6822215ULL, 0x9E2FD57E99404E87ULL, 0x73E58CD330B67F50ULL, 0xB50BCA04304D9B9BULL, 
            0x73A7A6327452BC48ULL, 0x8ADB70F20FB33B5AULL, 0x0E4733FE6E267437ULL, 0x9801AA17B5488289ULL, 
            0xA9AFCF6262BFD5B3ULL, 0x557FDDDE89D46672ULL, 0x507F6645FE3C976FULL, 0xEAC9FB410191624EULL, 
            0x2500271521454238ULL, 0x8BA25575C3131A7EULL, 0xEF78745F323D2C19ULL, 0x100834792BA18C31ULL, 
            0xCE9BC9DE8F17EFE3ULL, 0x6076B1D1FDADD192ULL, 0xEB9F91B30DF063FFULL, 0x2AD0130D71AE1D1DULL
        },
        {
            0xC2B49018394B71E5ULL, 0x91BBCC3B18C9F822ULL, 0xFECCA9ED9C4048EAULL, 0x289631740C86F627ULL, 
            0x5CAA0F5321B8DDAFULL, 0xC722A96E163B3C30ULL, 0xB0BA031DD760E7A9ULL, 0x4E6E3A182988A449ULL, 
            0xB1457D363E5273F9ULL, 0xFB606EFEF1979930ULL, 0x413E1F6093641B6EULL, 0x30BF11EC6747ABB9ULL, 
            0x6A261D52441AE4E3ULL, 0xA3C16DDC3FF7AA38ULL, 0xFF911D71FF3193C3ULL, 0xEF5F019663518D77ULL, 
            0xEC7044C6902FBA41ULL, 0x618F87654EE8D309ULL, 0xE5684B18BF6C06BAULL, 0x290D7F91D757F408ULL, 
            0x47A3784300BC71DBULL, 0x184FF21D0F76A876ULL, 0x1EA03B37B25C9E42ULL, 0x031C05FB1C4A4F30ULL, 
            0xD18FAC6C4D7C1DFAULL, 0x02024F1C9BF9AD83ULL, 0x479B60FDACFC1B30ULL, 0x00891C2AE48D9278ULL, 
            0xFE30206936E71704ULL, 0x107F67AC5B08B66DULL, 0x47B556B27EEE4E1DULL, 0xE6AC0178BA942C42ULL
        },
        {
            0x889817821663BD3EULL, 0xEC9B89CDEA63A682ULL, 0x204F514494FFDEFBULL, 0x9F55A81C03CB0ECCULL, 
            0x79AA60CC4454C3BAULL, 0x98073F3F0374C5DAULL, 0x39C7560DE4E057F4ULL, 0x344213A7AC47D412ULL, 
            0x13D0AEFC7242B48DULL, 0xE1BABEF72BD28AC8ULL, 0xDC84AFEAC42075B2ULL, 0xB92E2A83C25711ACULL, 
            0x1504A5E54B259823ULL, 0x49B8E707F8A6F932ULL, 0x048F0669E3F35C3BULL, 0x5E8C1E5EFDBC469CULL, 
            0x69024152A5968AD2ULL, 0xA290A7CEDF76266DULL, 0x5B1F75340CF21DA6ULL, 0xBE3174E494295B9DULL, 
            0x1EC72762F7F14A1AULL, 0x19DC2F6564D0A4C0ULL, 0x76319751EDB58A70ULL, 0xED96EDAAC06C4B03ULL, 
            0xF584B1AC40DC28A6ULL, 0xC1C892F5203FC6D5ULL, 0x3A45291F19C50F79ULL, 0xDBB53FE00ED5EC5DULL, 
            0xCC9FB64F659EF4E7ULL, 0xC5E8CAE4A728B993ULL, 0x05C1EC032C4C71ACULL, 0x8A7E7895EF3CB29BULL
        },
        {
            0xF5114F3833EAB0AEULL, 0xC23DF0F25A58A894ULL, 0xF634184A644764A9ULL, 0xFC61162C873E73ACULL, 
            0x6C6E93D432EC5C1DULL, 0xFA8F24611A1DD085ULL, 0x05672BA2A78791F3ULL, 0x3B9A7AB19090F0ECULL, 
            0x99EEEAB2E6F1C7FCULL, 0x326264BE6BF40D14ULL, 0x39D5E406B338B9BEULL, 0x8AFAF4B488C34BA5ULL, 
            0xBAB11E46E5100FB9ULL, 0x44744CDB15DDC20DULL, 0x6CBDCFF17B1BA707ULL, 0x3722CCBD27A8F8FDULL, 
            0x4D42D042B4CF0F22ULL, 0x76ED97B5AD69FAD2ULL, 0x204334B494B9383BULL, 0xE6CB913A64CBE27EULL, 
            0x6D3548C98ABE29EFULL, 0xCE9325E6643FD7EFULL, 0x0B12CA00E463089FULL, 0x3F46DBD1E4A92A9CULL, 
            0xF9F7E5F9FA38E1FEULL, 0x0FF6CAF476CEF3A6ULL, 0x4887A49FAAED06F4ULL, 0xA41F68A8B805DEAEULL, 
            0xBB4F725D24F261DFULL, 0xF51E65D99009EF28ULL, 0x7FE5A63C14C73FACULL, 0x1B27E3E102F0B166ULL
        },
        {
            0x362FF5AA1EDFCE2AULL, 0x8667991A69124ADEULL, 0xFFB2C2EFD68C21F6ULL, 0xBEB6CBE723294D71ULL, 
            0x181356CE3AE01782ULL, 0x4F0F97D252C8184AULL, 0xF2E42A048E1E49FEULL, 0x6D29DB75D3B48701ULL, 
            0x634AE1083A963CE9ULL, 0xF8A09F4338EDB4C9ULL, 0x121791B3CDE9623BULL, 0x442AAC6DCAD53977ULL, 
            0x7EBAE3167B3511BFULL, 0xC5D533DCD6A4FC3AULL, 0x284D68E601E8F180ULL, 0x85239CB1F54BB3BAULL, 
            0x57E4AE3FDB31F1DFULL, 0x00F2A79F84414F92ULL, 0xD361DE9212B581F9ULL, 0xD63857F3062B430DULL, 
            0x557FFBE63E611D8EULL, 0x812B91058CD990BEULL, 0x2AC7B42FA6B2C8B6ULL, 0x50F6686EBCCE6F87ULL, 
            0x4F43C83F8705F30EULL, 0x5087E7BDD19F9CC1ULL, 0xB841575AD8CEA4ADULL, 0x3F4CEC5C03DF8D2FULL, 
            0x74D8D2F7AB9181F6ULL, 0x2EC29FF361E0E777ULL, 0x80464473AB7D6D66ULL, 0x3E23146DD8CFA61CULL
        },
        {
            0x82B9811E3A20F404ULL, 0xF3A48AAA886011D1ULL, 0x7E8448DFA94AE448ULL, 0xD07BB06A6AE838CCULL, 
            0xDE30C905C19441D8ULL, 0x92E7D9A5638AC857ULL, 0x8D9B987F1B29E158ULL, 0xC0D1120AB01CE9D0ULL, 
            0x1C811B501B348F73ULL, 0x53B538196B7C9D12ULL, 0xDE74FE14E10A8957ULL, 0xC301F406DD7106F6ULL, 
            0xAB9B37F851C6CC7DULL, 0x34E4CBAA5E37C4E6ULL, 0xED3FF469DFA5A0DFULL, 0x45009BF38405B9FEULL, 
            0x38326C23D36A9D70ULL, 0x1869FEAD168EB444ULL, 0x841D1D154F718760ULL, 0x6DCD603C99CCE998ULL, 
            0xB626C2285D259FC5ULL, 0x401C5CF2F294028DULL, 0x90EC157A396EB878ULL, 0x7A319B9FEF1CD530ULL, 
            0x14B4213B6A988CECULL, 0xB7820A00301ADD48ULL, 0x3C2FB3B38A611005ULL, 0x65DC82AAF509AD13ULL, 
            0xBCB8DB0E8482BD2DULL, 0xD1AE7118F14F7D61ULL, 0xF2519A9511371982ULL, 0x421605462B46B0B6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Canopus::kPhaseHConstants = {
    0x2FFB162212EFC4CCULL,
    0x0F246A6DC3771518ULL,
    0x36BCD198213937B3ULL,
    0x2FFB162212EFC4CCULL,
    0x0F246A6DC3771518ULL,
    0x36BCD198213937B3ULL,
    0x1AF44882B0837BC1ULL,
    0xF83184DCBA41972DULL,
    0x08,
    0x17,
    0xF1,
    0x73,
    0x70,
    0x46,
    0xD1,
    0x09
};

