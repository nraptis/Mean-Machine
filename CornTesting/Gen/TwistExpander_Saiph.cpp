#include "TwistExpander_Saiph.hpp"
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

TwistExpander_Saiph::TwistExpander_Saiph()
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

void TwistExpander_Saiph::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x86924297082988B1ULL; std::uint64_t aIngress = 0xEDBAA739A9F0A4ECULL; std::uint64_t aCarry = 0xB175BCEA86B9156CULL;

    std::uint64_t aWandererA = 0x8622370059C883A9ULL; std::uint64_t aWandererB = 0xF3C0F9038986D09CULL; std::uint64_t aWandererC = 0xB66C50A894BAD3FCULL; std::uint64_t aWandererD = 0xF6FB0161EB0A108CULL;
    std::uint64_t aWandererE = 0x96F3767CC6234DC0ULL; std::uint64_t aWandererF = 0xF0423F57E7541BF0ULL; std::uint64_t aWandererG = 0xB48753236868F555ULL; std::uint64_t aWandererH = 0x97C8FE17A9E1B68BULL;
    std::uint64_t aWandererI = 0xAD7098787124DC14ULL; std::uint64_t aWandererJ = 0x9A98D9563DD0150DULL; std::uint64_t aWandererK = 0x8F440D559076E2B3ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16409960949536170904U;
        aCarry = 12755719442219034222U;
        aWandererA = 12470925374965942232U;
        aWandererB = 13344619650034952600U;
        aWandererC = 17108438646182369520U;
        aWandererD = 15406810417697496882U;
        aWandererE = 15608850975648186023U;
        aWandererF = 9242375772128320484U;
        aWandererG = 10044610074552077828U;
        aWandererH = 11528274685362743988U;
        aWandererI = 12752967193624555725U;
        aWandererJ = 13763759108333730073U;
        aWandererK = 9796033681764786712U;
    TwistExpander_Saiph_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Saiph::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xE3ABD08DB39CD2EFULL; std::uint64_t aIngress = 0x95985D3F4EE79020ULL; std::uint64_t aCarry = 0xB814AED396AC35C8ULL;

    std::uint64_t aWandererA = 0xF268C5DA104D39E1ULL; std::uint64_t aWandererB = 0xEE41A07BAE722B9AULL; std::uint64_t aWandererC = 0xF026D453A145B5B7ULL; std::uint64_t aWandererD = 0xDA694BC93D6F11E9ULL;
    std::uint64_t aWandererE = 0xACBA5EB18BBC74D7ULL; std::uint64_t aWandererF = 0xC6E7C651CE8ABFF9ULL; std::uint64_t aWandererG = 0xCD5E97BCA1F76243ULL; std::uint64_t aWandererH = 0xD6934A999D7F4831ULL;
    std::uint64_t aWandererI = 0xCDE619565C3F58C8ULL; std::uint64_t aWandererJ = 0xD817F0C5E714094CULL; std::uint64_t aWandererK = 0x9F4B43195CBA0390ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16988480765701165891U;
        aCarry = 9248379962703249077U;
        aWandererA = 17139529283531332531U;
        aWandererB = 15794306495117249933U;
        aWandererC = 16325687257343591316U;
        aWandererD = 13641028142200943074U;
        aWandererE = 17544325541415309301U;
        aWandererF = 15093548463065086524U;
        aWandererG = 17370786167100434985U;
        aWandererH = 10451919474245727871U;
        aWandererI = 13915337283755125283U;
        aWandererJ = 9331883471086300691U;
        aWandererK = 11361914575671132134U;
    TwistExpander_Saiph_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Saiph_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Saiph_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Saiph::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xEE128BC4AAB485E4ULL;
    std::uint64_t aIngress = 0xAA68C9430F4D8F94ULL;
    std::uint64_t aCarry = 0xCED1DFCF1543079FULL;

    std::uint64_t aWandererA = 0x9055BD5DAFF9FE0EULL;
    std::uint64_t aWandererB = 0x9E14A6693F65DCC4ULL;
    std::uint64_t aWandererC = 0xE18AF54BE2C1DCB2ULL;
    std::uint64_t aWandererD = 0xE22B8F3E97D89AAAULL;
    std::uint64_t aWandererE = 0xC301B396454D3B40ULL;
    std::uint64_t aWandererF = 0xD6B2B17E44DED9D5ULL;
    std::uint64_t aWandererG = 0xC888EC2134E75E05ULL;
    std::uint64_t aWandererH = 0xAF5289AD0D1A2AE3ULL;
    std::uint64_t aWandererI = 0x988E4BBE7AC4EAF4ULL;
    std::uint64_t aWandererJ = 0xD7A02EA3342B22CFULL;
    std::uint64_t aWandererK = 0xAC2E295FF2285607ULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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
    TwistExpander_Saiph_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Saiph_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Saiph_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Saiph_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 30 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1782 / 1984 (89.82%)
// Total distance from earlier candidates: 52654
void TwistExpander_Saiph::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1064U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 573U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 405U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1781U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2040U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 35U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 39U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 867U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 597U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 142U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1873U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1803U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 269U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1755U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1140U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 609U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 234U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 50U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1713U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 711U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1088U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1733U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1784U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1558U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1715U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 774U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 122U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1632U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1018U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 588U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1654U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 495U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 260U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 22U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 997U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1182U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2029U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 656U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 567U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1875U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 978U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 308U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 505U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1772U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1474U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1334U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1637U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1242U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1025U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1515U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 783U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1495U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1665U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 539U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1255U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1436U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1961U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 520U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1499U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1097U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 54U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1096U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1382U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1508U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 954U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1533U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1331U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 270U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1764U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 551U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1308U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 759U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1037U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 896U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1583U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1073U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1013U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1817U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 714U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 671U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 76U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 379U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1345U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1186U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 979U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 502U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1036U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1830U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 974U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 771U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 453U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 932U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 791U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 289U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1403U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 393U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 295U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 69U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1463U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 326U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 988U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1925U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1045U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1903U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1298U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1880U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 629U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1167U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2024U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 818U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 737U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 279U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1205U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1628U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 703U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1643U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 433U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1027U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1641U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 904U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1919U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 186U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1051U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1117U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1540U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 240U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1615U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1207U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Saiph::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC869578EE0A5B8C7ULL; std::uint64_t aIngress = 0xA8A2D8C551D1E14AULL; std::uint64_t aCarry = 0x914643618F7AE8C6ULL;

    std::uint64_t aWandererA = 0xECDB36F24B7C8369ULL; std::uint64_t aWandererB = 0xDDAF8D61DB940892ULL; std::uint64_t aWandererC = 0x86C4F920A0115F5EULL; std::uint64_t aWandererD = 0x9A90A44AF6279FBEULL;
    std::uint64_t aWandererE = 0xDC1404C439DC64AEULL; std::uint64_t aWandererF = 0x859AAE96D85F7D37ULL; std::uint64_t aWandererG = 0xB56D88CC0C149962ULL; std::uint64_t aWandererH = 0xCD3F293323497F5CULL;
    std::uint64_t aWandererI = 0xC449DBE44C47BDB2ULL; std::uint64_t aWandererJ = 0x8ED6DE3F599EBA0BULL; std::uint64_t aWandererK = 0xCC5E965DCED820B3ULL;

    // [seed]
        aPrevious = 13428549203885530984U;
        aCarry = 15491802018945323707U;
        aWandererA = 11348233443340323273U;
        aWandererB = 14119590221796225779U;
        aWandererC = 16955874029330877365U;
        aWandererD = 13954664118779304790U;
        aWandererE = 13174292031396322900U;
        aWandererF = 12798201046430961651U;
        aWandererG = 11701513744938484707U;
        aWandererH = 17030104670614724116U;
        aWandererI = 16306578146944250256U;
        aWandererJ = 15480813545084542068U;
        aWandererK = 15622014629882869941U;
    TwistExpander_Saiph_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
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
    TwistExpander_Saiph_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Saiph_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Saiph_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Saiph_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 30 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15681; nearest pair: 498 / 674
void TwistExpander_Saiph::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5534U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5398U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5835U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5454U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3810U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7516U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 455U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6060U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1172U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1672U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 24U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1560U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3110U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6262U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 984U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3950U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1560U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1443U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 842U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1635U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2042U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1722U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1282U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 12U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 960U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1681U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1504U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1999U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1482U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 818U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1118U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1473U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 816U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 374U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1040U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1744U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 30 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15681; nearest pair: 467 / 674
void TwistExpander_Saiph::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3799U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3536U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1063U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6927U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4310U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6914U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6575U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7084U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1055U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5404U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2267U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 968U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5474U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1384U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3857U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7376U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1564U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1377U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1847U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 631U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 805U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 998U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2021U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 988U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 259U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1909U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 55U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 63U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1980U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 224U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 525U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 625U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1688U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1204U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1277U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1035U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseASalts = {
    {
        {
            0x39291825FB3C6980ULL, 0x42EBF8DF6AE4FE1CULL, 0xCD0CBF9C16102CECULL, 0x9A66748BDED7FC81ULL, 
            0xF3A40CA7C152DE47ULL, 0x23C48497E23561CEULL, 0xF09E46A7761C1D55ULL, 0x509EC2ABE067783AULL, 
            0x6149D03C14511E4AULL, 0xB6646191973BDCAFULL, 0x6B8863D52E891212ULL, 0x54657678FAB7CF2AULL, 
            0xD5D091E91FBD644AULL, 0x6C55ED9325E6607CULL, 0x7EC1C77836A40B99ULL, 0x39441C7E2B635EE4ULL, 
            0x66B953AC9207D3D8ULL, 0xD1734BA9D34581EFULL, 0xCE90EC1D2C28C1D8ULL, 0xFAF45AC97CC2A0E8ULL, 
            0xFB25CCE9834884CAULL, 0x882198FB5D2ADAEFULL, 0xDB8F67E956645E5DULL, 0x7D23DF1EFEC096EEULL, 
            0x005B7A5E8232FBA6ULL, 0xDDDE1C2739385121ULL, 0x7E0BAB5C46EEFD6FULL, 0x312E61E723FBE348ULL, 
            0xDED30F11AA22E2B4ULL, 0x6F2717A9B35994CCULL, 0x3825670AC930C7AAULL, 0x4196B9CB25DA0C3CULL
        },
        {
            0xDBBD4D7BAF0B6C01ULL, 0xF36A4C41DEC8A285ULL, 0xA7F9760B2E66287AULL, 0x9F8B63FF3B99F55CULL, 
            0xCEB75129429499D6ULL, 0xB4E53209C8B46AA5ULL, 0x1F37A6E36BB56954ULL, 0x02AF76EE58B8110FULL, 
            0x773D68E9B8613706ULL, 0x6EA957ADC77261E3ULL, 0x3AE45FFBEDB88CA7ULL, 0x094B4D6AD3ABA462ULL, 
            0x7D43D4743FAFFA9CULL, 0x4CF50601C4196795ULL, 0xB6D863DBB1989A61ULL, 0x88479F466F23AEBCULL, 
            0xC65D1013BFCF38E1ULL, 0x4A5F45F698C7C85CULL, 0x411A9A275DCDEA91ULL, 0xC9A4C302417BAAA2ULL, 
            0xF5E858BE3230656AULL, 0x6D7D7FE68875BBCFULL, 0xCDC109A506665BBAULL, 0xB4084C31426E4A9FULL, 
            0x3DA3BEDB0E561B86ULL, 0x77414B599B98028EULL, 0xAF6E1BD6D8CDFE31ULL, 0x5AEA36B1D464D3A2ULL, 
            0xCA411C214A83E0B2ULL, 0x0864A2C0A1497A26ULL, 0x234EE55E7CB093EFULL, 0x271EF8C84383E4CCULL
        },
        {
            0x849B9B20E3969538ULL, 0x1ECF87E258D34A85ULL, 0x959F8572964F6FB6ULL, 0x0A8CB7262590F168ULL, 
            0x7977D85519D5C20AULL, 0x7CDA5DE612B0E6ECULL, 0xBB27D0CE571FA871ULL, 0xEA0CACE60097AFB3ULL, 
            0x7F2BBA91BA8F95BDULL, 0x1FC31DD408FC3E08ULL, 0x0DA17754666043E1ULL, 0xBFAD7399FACC00E8ULL, 
            0x51995D56A940DA0EULL, 0x866CF6B65984C36DULL, 0x92F3913626A43BE3ULL, 0x4F3F0041FFDE1CEDULL, 
            0xA1171508089DAFD7ULL, 0xA103A146858BC42BULL, 0xF77649E15C6BF96BULL, 0xB56C47182AC63927ULL, 
            0xE938C28D0F373BC2ULL, 0x4B38616F405C0561ULL, 0xFDEE3D2AE6CB1121ULL, 0x1C1FBEF9576C5F99ULL, 
            0x56AF0C41FF63256DULL, 0x75A6F94132E20FA3ULL, 0x448EB9F263A6EE3DULL, 0x62F5A97309379E5DULL, 
            0x99D348A018BF91F7ULL, 0xCDBD6703EFF43785ULL, 0xEAF70408D0F71770ULL, 0xAC43F79E011FD6EBULL
        },
        {
            0xA6C06C356552BFBCULL, 0xF1D8AFB47AC22B98ULL, 0xDF10E31FDA364642ULL, 0xD11F30624A950C86ULL, 
            0xEADDD530DACEC222ULL, 0xD59A7827DFA0A723ULL, 0x1C502310AF3BCB0DULL, 0x5DD3F8415893BF5EULL, 
            0xD11A733AE3944FD6ULL, 0x3B555E9ACA979F17ULL, 0x78546EB7F320A81EULL, 0xCDA6E9C925852E3CULL, 
            0xDFE98B84B1C41764ULL, 0x1EE0891664E0A540ULL, 0x50FB5945C5C240ABULL, 0xD079F4901BA173B3ULL, 
            0x8ADACC3CBBC21933ULL, 0xC95BAE9BFC608391ULL, 0x762BA24A7B204B76ULL, 0x671E32B3A13F0B5CULL, 
            0x7207D5669C8DBBD1ULL, 0xD40F7F90C1437C89ULL, 0x3DC4CB25E329D652ULL, 0x07E4AB7EAB8864A2ULL, 
            0xF2D680322E8DE8A9ULL, 0x66530C70CA10B455ULL, 0x69AAEC11954560B4ULL, 0x84DDC885FD497A07ULL, 
            0x4B35E08279EF085CULL, 0x6CB2936A1F37D99FULL, 0x1F46A5EC915A25A9ULL, 0x7434146D2C724245ULL
        },
        {
            0x092FDAA68033DE70ULL, 0x2B5C596C75E308B6ULL, 0x6ECD9A6091DB588CULL, 0x1E621CA7DD3F5D66ULL, 
            0x24BFB3385EEE845AULL, 0x7ECFE6E1B3A20CC4ULL, 0x767027A5E2A514D1ULL, 0xA9E379FD03F5A23FULL, 
            0xFCC260A76B8BA8CDULL, 0x49B77BA98AA555BBULL, 0x0182C5EA534F02AEULL, 0x24E01219B550F204ULL, 
            0x1721CBCA5BC01C23ULL, 0x8430B7EE4110DFBBULL, 0x0299F96422387AF3ULL, 0x6592CC293348D09BULL, 
            0x7B80118DBAFDA321ULL, 0x2A7224F595F11A66ULL, 0xBB56C1B7E67E1DACULL, 0x3088814668A19B39ULL, 
            0x456918BD748AB776ULL, 0x80BAD5D90F96938BULL, 0x30EF29E94BACE979ULL, 0xED766789D70406A1ULL, 
            0x6BD939C0E8E3D6EDULL, 0xF359C1F58A769E4DULL, 0x3704CC751E53EBF0ULL, 0xE5A91B466E295C44ULL, 
            0x5F77827968996613ULL, 0x47E92A6085D45E7BULL, 0xC98C91D18D0D8DC0ULL, 0xBA5D1C2DCB6A2FDCULL
        },
        {
            0xD5E50A4870BFB5DAULL, 0xB4E7913B57B8A90CULL, 0x2FB026352BF3F812ULL, 0x57A6789F8C8C1A8DULL, 
            0x1668486AC7EDD330ULL, 0x7F9785D386CC97BAULL, 0xA1542BAE3593A07FULL, 0x832FB29AC975248EULL, 
            0x7FE2D4C22B98560EULL, 0x70BDF0C3AEAA6B07ULL, 0x1CA411FB079432C5ULL, 0x0938309FC4357ED7ULL, 
            0xEFFFCAF1C72A7D94ULL, 0x111D749B81C12745ULL, 0x0226304F0A03808FULL, 0x6E039AF9E9B05EC1ULL, 
            0xA2491BE51A072C7AULL, 0xFFAB1096A9852E3AULL, 0x6B98A7D0F6E291DCULL, 0xAF4A4CE9DEF342AFULL, 
            0xBC668300153768C2ULL, 0x72F98566293ACC4CULL, 0x997B116520F117A5ULL, 0x8003E957C45E1E70ULL, 
            0x377110B7E04F5E37ULL, 0xC5B674E3F9BE162AULL, 0xE7150C195424D3B4ULL, 0x99CF2B0E95FAD38BULL, 
            0x75A6066AAFD9D18DULL, 0x81968E5FA3957CBCULL, 0x078703CFDA707433ULL, 0x7563495DA4E642E5ULL
        }
    },
    {
        {
            0xAF315B0FCE5C8552ULL, 0x99B36B9008734395ULL, 0xEFFBEDC1C94056E5ULL, 0x608DEA4A5E040A4DULL, 
            0x0489663C87A2F9ECULL, 0xC2F140B8E72AC7B5ULL, 0x17B7C8EDE4160536ULL, 0x6F07D0E383ED52D3ULL, 
            0xF572D94E7A926E39ULL, 0xCD645D0A5993356EULL, 0x5A175ED22E5DF365ULL, 0x307784382E01A66FULL, 
            0xFCC029C0D25E078BULL, 0xA75A3489C0B74F38ULL, 0x4FD1A46A85E9E1A7ULL, 0x7B62F6625745BE26ULL, 
            0xEA4583E4A6071241ULL, 0xFFCF48AE9792C28FULL, 0x8ABBA65276A4A9C7ULL, 0xA8F30F7B51FDDB8CULL, 
            0xC75E6C3DA3050218ULL, 0xE6E5F9E939035009ULL, 0x27A6DA272AFE0EA8ULL, 0x253E737C22904FADULL, 
            0x7392D3832870E04EULL, 0x5A0F4846BCAAED52ULL, 0x7CBB2B3170FFA432ULL, 0xCA8D66BEF006E0FAULL, 
            0xDB52ED1071690187ULL, 0xA7D488DA6D19FEE8ULL, 0x614D101331A735C9ULL, 0x5BDB0352077CD0DEULL
        },
        {
            0x195DF1167F632FA9ULL, 0x0864FE53E2C2FE7AULL, 0x1D7BC93D759F1846ULL, 0x160FA338D92BE167ULL, 
            0x2AA6E3CF7AC586B3ULL, 0x7975D141CF7D1489ULL, 0xB8A0674A55D54687ULL, 0xA954A2A2499A3D89ULL, 
            0x3CC92DA015AF33A7ULL, 0x7DF8108CE798C1B3ULL, 0x090A917BB61C2093ULL, 0x64F97F7FD16086B1ULL, 
            0x34A3E206DFE9E4B3ULL, 0xB7E56E391E6977D3ULL, 0xB87179E311AE8212ULL, 0x24FB284444C56E78ULL, 
            0xFFE83423E69FFCCFULL, 0x15E2E867CDA4DFE7ULL, 0x652208B5A9CD98F2ULL, 0x1CF27028AEC036F9ULL, 
            0x83EC307A0F6197F9ULL, 0xE83FF4BC70DCEFCEULL, 0xA952931A40A75B4CULL, 0x5D9633379BCA4200ULL, 
            0xC96321BE2F455549ULL, 0xA49E7E1DE22FB9D0ULL, 0x366B6862DC752D84ULL, 0x6385165A5C5B345AULL, 
            0x1FE6DD76704C813CULL, 0x64633B2D472BF111ULL, 0xD6A676995ABD3139ULL, 0x00DC55CC547E11DAULL
        },
        {
            0x3C45619660D06BB2ULL, 0x80DCC4E378F5644AULL, 0xCC2A158BD9F0688DULL, 0x51971C0133340949ULL, 
            0x0C3B5103EF25A95BULL, 0x90F15EF9B30E8782ULL, 0xA591B556BADA194AULL, 0x724DD051D31E14CFULL, 
            0x9CDF8E2D2A2BF8E4ULL, 0x3E9781D24689BF7FULL, 0xD17BEC40FAC8DE50ULL, 0xAA49EDB97F5D4D67ULL, 
            0xD5596EEFCA8C1C48ULL, 0xFE0491B7104EAF58ULL, 0x4EB83B95E89EF69EULL, 0x101337041DD73DEFULL, 
            0xDDE11EDD45EE74FAULL, 0x4D17EC317413413AULL, 0x7D1AFDBE08EE9942ULL, 0x060AC042FEC18722ULL, 
            0x4556C4CE2DA4B371ULL, 0x6689D11ECE8762B7ULL, 0xBEE702E02C84FB13ULL, 0x34496C8283FB886BULL, 
            0x39BD9404EB583532ULL, 0xF4CF29375FAEFC31ULL, 0xCE3ECA7654F4897AULL, 0x0F3AA6380E03987EULL, 
            0x61A55DCFE4F8B7FEULL, 0xC2B8B4B2CCC0D00CULL, 0xF8AF99031466ED44ULL, 0x141F37DCC2C4685EULL
        },
        {
            0x29987846797BF883ULL, 0x2A980FC40ADDEE7AULL, 0xC924FD7513BAC100ULL, 0x5CBF4CF3D8566DE8ULL, 
            0xC37CD0FD668C7AC4ULL, 0x6563C530E5F8F7A9ULL, 0x43DB85548662F1D1ULL, 0xD56ECF6FA743E796ULL, 
            0x5EB65AE24F44B63EULL, 0x9A8621746AC6DF99ULL, 0xEBA7EC1B3A71D555ULL, 0x1C587043100F2896ULL, 
            0xB3FDBB92E8EB3B9CULL, 0xD1EAE49006C37412ULL, 0xC99080E01A47259AULL, 0x9E6555D72B30E424ULL, 
            0x6259FF0041BFDD59ULL, 0x15A42400E7C58A7CULL, 0x34FD4E41CF927AB5ULL, 0x24DEC38E44D7C66EULL, 
            0x50A7A225883F5A74ULL, 0x91C81D3897830943ULL, 0x686680B41378FCFCULL, 0x69822364BB00DF37ULL, 
            0x36BF73330BF491DBULL, 0xA1E8B65AF7FE072CULL, 0x47E152B1E209781BULL, 0xB9ABD9EEC632CF52ULL, 
            0xA30AC37E077803ADULL, 0x07BFE4520D39A376ULL, 0x45B8AC68604EB733ULL, 0x920570D424672AB8ULL
        },
        {
            0x18D63C27A30F5AD6ULL, 0xBF7D38E23DA674ECULL, 0x196C63B305B8575FULL, 0x4C3744DC566D40E7ULL, 
            0xDDAAA0DE626F2FA7ULL, 0x94B1118F7335B7ACULL, 0x73F0FC5BDB919D93ULL, 0x3133B4C7E96EA614ULL, 
            0x6C8C0DF6ED585B62ULL, 0xFB45EE614D9693F3ULL, 0x2A238844FE143B62ULL, 0xF3FC366C6D9B5503ULL, 
            0x486CDC7F99129AF3ULL, 0xDFD9C282F210ACDBULL, 0x701025B7E7792E5DULL, 0x800A7ADDFFC07F8DULL, 
            0x95DDF04F1ADAA568ULL, 0x4F8E77CEB20ADF61ULL, 0x5F5E5DF292FD1432ULL, 0xCE45D9A8D68B27B4ULL, 
            0x45159B147536AADDULL, 0x4F83590D910E5C1FULL, 0x8508A54A42802050ULL, 0x877688E066BC3FF4ULL, 
            0x35802DE56E9810E2ULL, 0xCD36096217549F9EULL, 0x0757929F33093C90ULL, 0x15E667571ECA1657ULL, 
            0x95AD0DB8DE613232ULL, 0x0D1D8FD699B18617ULL, 0xBD5DD281EF0B8D28ULL, 0x58F0F102201FDF54ULL
        },
        {
            0x1D70F6D55E3619F0ULL, 0xFE8874D3268F58D1ULL, 0x5C1D3452FB8026DBULL, 0x0C841B3590CB61CBULL, 
            0x4C83E24EC9E4D912ULL, 0xF8B8C53A6883AED4ULL, 0xCC8980086695477BULL, 0x09F8698FDE939E90ULL, 
            0xDCE6D5CEAE39C1B5ULL, 0x0EA50CAC77BF75E8ULL, 0x88A95B41C33F4D99ULL, 0x3CC7CF8497155F2BULL, 
            0xD64F0906C1AC1508ULL, 0x4FC85068BD258510ULL, 0x366969BC57A4DD82ULL, 0x935C9028D7490E88ULL, 
            0x7019BE44E5E2B49CULL, 0x03346CE146765D76ULL, 0x294C8A73F9967D33ULL, 0x2119073A9C608E9BULL, 
            0x0BDC7C9BAD1BA1A4ULL, 0x110879ADA6F1C8B0ULL, 0x66D867B6499609D9ULL, 0x7CF3EE350DF1B0B5ULL, 
            0x4BB7F846DD125AC2ULL, 0xA02F1D09A7B517EEULL, 0xF46A6B65966A2B15ULL, 0x3A472E2FE156673FULL, 
            0xAE01745E3F3BD981ULL, 0x354316474034CC69ULL, 0xF424608A9A0473C0ULL, 0xC40D8F4663E75484ULL
        }
    },
    {
        {
            0x38CE517DDEE57B10ULL, 0xF052B30D4AFD78C6ULL, 0x7B399E3B6C2EB34CULL, 0xD5806C9489811868ULL, 
            0x010740C73142E47EULL, 0x7252EB052692CA40ULL, 0xD4BAF650A1C1D6F3ULL, 0x737435588D298E5DULL, 
            0x806AC0E5346D6E81ULL, 0x468839DF76090C5AULL, 0x227A27C1CFB22725ULL, 0x68680007651B34D7ULL, 
            0x6E94E643C780B9FDULL, 0x9CF2F2855DA61759ULL, 0xEC2F23F54656FF58ULL, 0x7A2A0618A3A6B768ULL, 
            0x0AA95D36183A531DULL, 0x9B84DFB9D28CA051ULL, 0x46F9B18BAC8E14C8ULL, 0xB1A8F2CF60461189ULL, 
            0x988251CB66C3E9AAULL, 0xFEEDC9856B05B51CULL, 0xA73F6DCD868A0A0BULL, 0x5221AEEF4E3CD7B8ULL, 
            0x660986E1B150409EULL, 0x4022D0951B658588ULL, 0x446DCA5CF0480ADCULL, 0x0013B81A0B344100ULL, 
            0x622BEDB419832879ULL, 0x976A3EECE6239ED5ULL, 0x63B75AAD005E3C49ULL, 0xC463AD674FE44C03ULL
        },
        {
            0x4F3D7A25AF803981ULL, 0xC91E6E38A57FCCCCULL, 0x0640B84FF657EB93ULL, 0xB539580CA76D8463ULL, 
            0x3F02D001581B55A0ULL, 0x9D01F1801A7D5A8AULL, 0xD622B281755B4E89ULL, 0xA9260B7CED40C592ULL, 
            0xBB8381928905280FULL, 0xDC0748E188DBA661ULL, 0xCE9171169DEDFE15ULL, 0xCDC3E49DDB36C618ULL, 
            0xCC37E23D9147C9BCULL, 0x4845B67D6A6BDE16ULL, 0x884829741EF9CFB2ULL, 0xD9C4CACB0E0DAB04ULL, 
            0x648F2CBC524F90BCULL, 0xE048EE8DB1E0B542ULL, 0x18710CAC967E6EDAULL, 0xDBD6764FBF62BD77ULL, 
            0x24B1340F38DC84F2ULL, 0x66BD07235C1F8BFDULL, 0x96C5F0B955314CEAULL, 0x5308310290C4273AULL, 
            0x43B5D2A18BDF490EULL, 0xCD05DA457F439487ULL, 0xF7B22740E6FAAD17ULL, 0x98C3DAA903361DBAULL, 
            0x76A0E004727A0DD3ULL, 0x7FFA961BE3898CD9ULL, 0x0B56CC748E901457ULL, 0xA8E5219AE88AE01EULL
        },
        {
            0x2D0954C436B26414ULL, 0xE3CB2DB5F85E53FAULL, 0x70CA62190F59AFB3ULL, 0x900F6C4B88332B56ULL, 
            0x1AEC35241B950592ULL, 0x92DEECF4F5D5B5CCULL, 0x9CD8C76CA4900157ULL, 0x861905577B7FF060ULL, 
            0x18F8B120F0E16D38ULL, 0x20CC8954A5070664ULL, 0x1644A77D04843A8CULL, 0xECAE1FAAAB596828ULL, 
            0x0AB2E80E6771005FULL, 0xD304DEF90B015412ULL, 0x5E606795355BDAAEULL, 0x7C32A7196E48355AULL, 
            0x389B4FF8D5D39399ULL, 0x5C0AAAF0A5A5CD97ULL, 0xC1037BDEB4589468ULL, 0xE4FD45473CCD7526ULL, 
            0x4711E10D90C2FDEBULL, 0xE99CE1C9CCEF91E1ULL, 0x13F2259586ED788BULL, 0xCEE265AE7BAB7079ULL, 
            0x7292B0A48ABE3F8AULL, 0x1E1DFD9F175A0E00ULL, 0xE4006B0FA72B7327ULL, 0x5BE07BF36A0452DDULL, 
            0x82BB1976C239198CULL, 0x8B358C7FF096743FULL, 0xDCD3E28776102AE5ULL, 0x3D73D2903FD05B9DULL
        },
        {
            0xE7427BD8C133C380ULL, 0xBBABD84686C588A9ULL, 0x596C0517D8D04145ULL, 0xE663BDC49382E5A6ULL, 
            0xD9953FB8D138AD9AULL, 0xD46FDC7C0E92457DULL, 0x8C5CB2638C4A5865ULL, 0x66DA908B98903B66ULL, 
            0x60B524C4DDD01615ULL, 0x40FB8EA3842F3E27ULL, 0x872442E6236A7752ULL, 0x3925AC84B50350F6ULL, 
            0x7E7E6BAC41409F1AULL, 0x171D3BC314441902ULL, 0xA7DC2851F32D95BCULL, 0xF84D5A87249C9BDDULL, 
            0x27721BDF905A50D6ULL, 0xE1F85083C1541CCBULL, 0x5DDD19212FFF6E14ULL, 0x8B10BC5859D942B4ULL, 
            0x12B898A8821D5B3BULL, 0xA0EA01C706A79EB1ULL, 0x34357A4E28C7CB4BULL, 0xC847E67C87E0569CULL, 
            0x1392213018ACB640ULL, 0xD540E20297068285ULL, 0x0B22B2E091E049C1ULL, 0xC826221FA00D8DD6ULL, 
            0xA4D92FC23BBB13BEULL, 0xE9AE416FA7C985D5ULL, 0xC3D4E686CD73510AULL, 0x1F4C1BFE8C6B850AULL
        },
        {
            0x503C81DB4D819FE8ULL, 0x12B5A9AB63BB4C39ULL, 0x2CE48D8EE0570A3FULL, 0x33BEE4297425B043ULL, 
            0x6EF2CAF220B35DDDULL, 0x1D1B77EA04291D0AULL, 0x468F69D91EE4CACEULL, 0x435E85DEE42203E9ULL, 
            0x13456AB140C48F59ULL, 0xC7325C84D922FFEFULL, 0x013708F37041E3A5ULL, 0xC3E42B6D1F25DFFDULL, 
            0xC0D7C2C62E02D6FCULL, 0xF07E68C45F51F6B5ULL, 0x6A939BABEC55B022ULL, 0x139AE44D31575B42ULL, 
            0x7632991832F4BD82ULL, 0x2E7D370D3ACE4810ULL, 0xAFB7945E9BC6E907ULL, 0x25B3142429C28E64ULL, 
            0xDF7CE8F85D807BDAULL, 0x552EED9E9CA17A03ULL, 0x5FF85C0AF4EC9FAFULL, 0x303BCDA74C2FB5C8ULL, 
            0xB64420241D921E91ULL, 0x108A6B9B3E367BC0ULL, 0xF9D1F62EE267249FULL, 0xD57B186A4FAC4E16ULL, 
            0x05E360101492F23FULL, 0x4465BBDFF40E6463ULL, 0x274FBA8D76608148ULL, 0x87A87E6CEC31E976ULL
        },
        {
            0xEA28D90877886D77ULL, 0x969CA759CEDDC56EULL, 0x82D274D5F0A6B884ULL, 0x6E141D03A807303DULL, 
            0xBD7346ED903661CAULL, 0x67FEDA44A4D71EC2ULL, 0x2B172B4C86483585ULL, 0x80EE3AAB03502F0EULL, 
            0x8FCE277469F2DF5EULL, 0x88D7C800A5EC4DDFULL, 0xD134924AF5C81FEEULL, 0x4426560FC04401A4ULL, 
            0xFDCFCF8342A656A9ULL, 0x87AFD4482936A697ULL, 0xA6F01A31E4CC37EDULL, 0x086E6C140F6AB55CULL, 
            0x9D70155D750E064DULL, 0x12ECB159CFF06402ULL, 0x407364CA9F71A0C0ULL, 0x34380C9EB6644771ULL, 
            0x882A26DED9A673B8ULL, 0x0897309683865712ULL, 0xD1664A0DAB65721CULL, 0x091CF3C15A7C78E4ULL, 
            0xAE994B9F9A042C30ULL, 0xCBA91C0D8918F6DFULL, 0x02D6A45BE641CEBCULL, 0xC103CA373681FBA5ULL, 
            0xAC541FEC4CF0E5ACULL, 0x16A135E0C1AF0E31ULL, 0xDE9E94416E05D793ULL, 0xB5471483924E63E3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseAConstants = {
    0x2AE83909CF12CE9BULL,
    0x560CC76383B6AF0CULL,
    0xCA7300BC45011051ULL,
    0x2AE83909CF12CE9BULL,
    0x560CC76383B6AF0CULL,
    0xCA7300BC45011051ULL,
    0x76E979A53C70CF91ULL,
    0x52787BD81FD9D957ULL,
    0x66,
    0xA4,
    0x6B,
    0x09,
    0x3B,
    0xC3,
    0xD1,
    0x67
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseBSalts = {
    {
        {
            0x341888B5DA30880AULL, 0x77F934206CDCAE8CULL, 0xBA6DF0F2B852DFCFULL, 0x08E010DF15A4216FULL, 
            0x8597BD9627CB0DC4ULL, 0x1C500B59287E7F2BULL, 0x0809E1EE4DFF77D4ULL, 0x46FB4E3AEF7FDD4AULL, 
            0xA69C073D2F2BD15BULL, 0xB4E796BC820C0468ULL, 0x3DB1E36E1745489BULL, 0x46AF9D15A72D8E18ULL, 
            0xAB34F912E271E6DCULL, 0x0130B245B1B29B15ULL, 0xD3A810228D2E4608ULL, 0x7FD285EFAEA70361ULL, 
            0xE067DA666120DFACULL, 0x3FDBFE691337BE3BULL, 0xE600EC2CB8962EB7ULL, 0x1474BD983FFCDDB3ULL, 
            0x66EE1CBBE05299D7ULL, 0x903E1E8EE5E62197ULL, 0xEE184D4D05B234EDULL, 0xF8F409DABE7C810CULL, 
            0x95FD463124DD1893ULL, 0x366A108749B75F91ULL, 0x1BFE4C60674C373EULL, 0xA445AADE4FC7A4B1ULL, 
            0x20AC1151D1F47C77ULL, 0x7B7E55F3BE0103D3ULL, 0xED511CF09C465022ULL, 0x33A2BA72CA57A76FULL
        },
        {
            0xC212C1AF60A2489CULL, 0x262E05F076981BFDULL, 0x314DD8031E70F6D6ULL, 0x9DEAA1263E8E8937ULL, 
            0x22DC57C38BC75BE4ULL, 0x3939EE57E8A8CF08ULL, 0x09CBF557AB6C4CE6ULL, 0x723BBAE54A0E203BULL, 
            0x78B5EF56946A1DE6ULL, 0x3DC6F274B55B1E94ULL, 0xFEBDDC55C04BB1A4ULL, 0xECF949C40BF4D3F6ULL, 
            0x5C81C01E5CBCBEC6ULL, 0x3F2C7B8B8DCE8D1AULL, 0x3437D15694677340ULL, 0x9F8DE9504D52091EULL, 
            0xF7616E8A9CA3BB08ULL, 0x5D75FC1B2063CB7FULL, 0xBB301EFB5A2E61BEULL, 0x2FF8BB5D020502E7ULL, 
            0x8D043C0BCA19F448ULL, 0x865A9809D7623DFEULL, 0x2A3476096FF7471FULL, 0xF7C450D3B41BC021ULL, 
            0x45050D4A95706325ULL, 0xA2D1E426881D6B53ULL, 0xC540684954E41D57ULL, 0x9C51FC70FD998311ULL, 
            0xF34F835A5AC37417ULL, 0x566CCC9B20769B41ULL, 0x345564436114FCA0ULL, 0xA1C189FB283B244CULL
        },
        {
            0x3024036F6889ECA4ULL, 0x22FB527593D837F4ULL, 0x4A7D7B87154BE752ULL, 0xC6C424D2F9962289ULL, 
            0xBB01E44F0A5A8892ULL, 0x326A607BDE3C4CD7ULL, 0x1F01F65CA2755ABEULL, 0xF7002FCE428AE9C6ULL, 
            0xE8B86CEC48AB4B70ULL, 0x644F20DB13C5809BULL, 0x7E758D5772BD1458ULL, 0x15EB90A6E178A4C4ULL, 
            0xC5D4A86C142DA2D6ULL, 0x7E15B73849CEB180ULL, 0x2CE1CEC98762D9D2ULL, 0xF7BDD6AAEAF6695BULL, 
            0xA5D3DEEF2ED189DFULL, 0xA8E2D24B1DD9C286ULL, 0xDFE53651A8DAFB02ULL, 0xE77FB44CE8C97E00ULL, 
            0x51C6CDA335473C35ULL, 0xCFAC243A808E68FEULL, 0x5656DF83EB02A52AULL, 0x4E64FE00ADF16D27ULL, 
            0xAF83ECCC2B09F08CULL, 0x7760339DB7FAC351ULL, 0xB5F685FB294E1C86ULL, 0xC15C8F5D554BE3FFULL, 
            0x672969BB4BD11B13ULL, 0xD8896B3DEFC73741ULL, 0x822B2931DB045435ULL, 0x32C610250E10A9F4ULL
        },
        {
            0xF3147A1529F3F5FDULL, 0x2184A662157EB151ULL, 0x39969CFB67344EB5ULL, 0xDF6E99D095AEE647ULL, 
            0xBB2BEF3FDF13DA85ULL, 0x0BD19FE6820887CBULL, 0x414495589059A588ULL, 0xDC43A2929A676F0EULL, 
            0x241B71EDCF18181EULL, 0xFB20905CB2869F22ULL, 0x4D9C0B820D9CF18FULL, 0x76FD7AD606918D2CULL, 
            0xAD2FCAD898ADF218ULL, 0xC73CA589936B0A83ULL, 0x5EFB5C7BDE25FC4CULL, 0xE1F933B070D77312ULL, 
            0xE8DAB4B376E4CD52ULL, 0xAA06D744CB58EBCCULL, 0x5B8400580995F333ULL, 0x73C867E62DDF5E36ULL, 
            0xFA7A44232874BA9FULL, 0xBE04CC008CA8ECF0ULL, 0xEB4F070BEF4D69B5ULL, 0x8F998865C2DD0FFEULL, 
            0x8470541A492F25BCULL, 0xE0296F7FE5E4ED0EULL, 0x8979353CA4CB96FAULL, 0x879EAF5A51C9D9AFULL, 
            0x9D7E9662C3B5A402ULL, 0x6F422C35AE81EBDFULL, 0x312F4B8387641DA4ULL, 0x05E2362939A5CB26ULL
        },
        {
            0xFC4EC0D26083A555ULL, 0xE88B1CD6332C068BULL, 0x485D982ECD24CA0FULL, 0x2C4AAB9D850C0F97ULL, 
            0x823D30A373D9E2CAULL, 0x4F24255D4975516DULL, 0x3012CE47C6E4E612ULL, 0x5A6AFDDA600F99F8ULL, 
            0x97219DB015F06E86ULL, 0xD658B0683E93BB5DULL, 0xC72888D4DFC1FDBAULL, 0x0AE95DABF251C087ULL, 
            0xEE8CB7E19A72A921ULL, 0x3E9630EEE3B7EA30ULL, 0xCFD3CE21F2C8901DULL, 0x7C1CA2A3F37C8AF7ULL, 
            0xF38BCAA7A7F5203EULL, 0x272B35E20D046C89ULL, 0xE41A1B55A9A587E1ULL, 0x5A89F0DDD4549368ULL, 
            0x7EE3B97805116E35ULL, 0xCEE25F6BF1BA182AULL, 0x34751AEF62ACF52AULL, 0x3CCC4943BE908E5DULL, 
            0xC85A3FE791E458BEULL, 0x0CB5679543369E09ULL, 0xADC9C7D3DB1D23FAULL, 0x95DBC581B7C28EC3ULL, 
            0xC4E020A107199B56ULL, 0xF7ACE43E773A4041ULL, 0xEF4D2D201D174F65ULL, 0x5977138570B432DDULL
        },
        {
            0xCDFD63D226535135ULL, 0xFB735A35ACD6E8BAULL, 0x53EAE7547C933CE1ULL, 0x7A9F72F64E778707ULL, 
            0xCB4BA8B149EBEC37ULL, 0x0153DC7D333FD46FULL, 0xBBCE4E7B54F6D841ULL, 0x213E74B12C059C56ULL, 
            0xCA905CDAF4093496ULL, 0xE0EA2C6416DAE7BFULL, 0x15D825F7F1B15A0DULL, 0x3312247DB5FEBC18ULL, 
            0xAEA06C4F3FD6D305ULL, 0x73BD3785B4321C0DULL, 0xFB876E0CF918D493ULL, 0x6E8B0537A0A0B85EULL, 
            0xCB56191E6A226810ULL, 0xC9ADD6F5480B9AECULL, 0x566B3665FC6FFD80ULL, 0x2DD814BC1C8AC477ULL, 
            0xAB61044F4A067342ULL, 0xDEC2CC374D8C6E46ULL, 0xCC14159C66FAFF52ULL, 0xA8F3FF41D773B78CULL, 
            0xF13EFE2D9C13C25CULL, 0xFF9E9EB3617044B2ULL, 0xAA7C71E530B7A8B9ULL, 0xBAA90437870EEC27ULL, 
            0xBBE65B42A96BDB48ULL, 0x000F312FE5FCA8C9ULL, 0x75C8656825367F36ULL, 0x95B5975D140D2726ULL
        }
    },
    {
        {
            0x1688701BFF0B563AULL, 0xAFEC888D04C24344ULL, 0xD4D260DAE1318407ULL, 0x97EA4FF4D372CD32ULL, 
            0xA1E3E20BB1B3C6FAULL, 0x48EF9749016EA1FCULL, 0x0263BD1E58AACDD5ULL, 0x041CD26F9D632293ULL, 
            0xF2D3CEC213A54C9CULL, 0xD96C7F6BC6A104B7ULL, 0x042D0E68CCF59958ULL, 0x2E22E83F289A4DA3ULL, 
            0xEC4AEFE8D9904ABAULL, 0xC6034322C7ED56D7ULL, 0x5DAA7FA9E7E70463ULL, 0x2ED7B8CF49B8C0F3ULL, 
            0x35C545F79259A234ULL, 0x31222ADD9222C354ULL, 0x1480F78ECB063895ULL, 0x61D2038B9430E453ULL, 
            0x46E158CB07B6413EULL, 0x0F59389CBAE21BE6ULL, 0xF6768DC669EB2C05ULL, 0xF95A8124BAE85D35ULL, 
            0x232005EF447442ABULL, 0x67D8F7FA528C75A6ULL, 0x4C1CAA69ADCF629BULL, 0xE65EDC8A19D464CEULL, 
            0xC77238A5B320F500ULL, 0xE548890080B5D678ULL, 0x84725769C9AFA7BAULL, 0x4DDF6989F5A247FDULL
        },
        {
            0x1B2E9C0E89B4BFF4ULL, 0x01F5AEBA75A63161ULL, 0x4EE197EF99FAB4F3ULL, 0xB954EACBF71D3BBDULL, 
            0x48B5A194D3175414ULL, 0xE45F7119CDE9904EULL, 0x55B6CFEBE0A7E21DULL, 0xAF8B9D30842CF419ULL, 
            0x3910FA8611195219ULL, 0xDD17EBA73623283FULL, 0x66901FC68993A2A8ULL, 0x2849247BC885C7C4ULL, 
            0xD237B4EE097C648FULL, 0xF794F1B37EEC4EB2ULL, 0x3A13644FBD527346ULL, 0x2B13921D819C83F1ULL, 
            0xB3A1CF1FDE552059ULL, 0xF9C2C7CBE7E6753AULL, 0x2F4979A3F5A56F6CULL, 0x65F0C20430943064ULL, 
            0xD3FEF1632CA39ED0ULL, 0xD41AE47513664054ULL, 0x98836F56315B3C19ULL, 0x1EFF0B142818A6FEULL, 
            0xBC2DBC93222F5DB1ULL, 0xFC8A89BA7654321FULL, 0x010B3B0F93A09E82ULL, 0x05E62192A1C9A80DULL, 
            0x55585A14179D95C6ULL, 0xB4448596EDDCC50CULL, 0x1D5E346D9D626B12ULL, 0x3D0DE86D88319828ULL
        },
        {
            0x8C2AF4083CDE4F1CULL, 0x7794AFF1B0ACDFCEULL, 0x20FAD8B5D980A881ULL, 0x64789D5A3E76B8A2ULL, 
            0xA59CB8638DCCB64CULL, 0x8E75F9E6D76E242AULL, 0xE07F58D288F27206ULL, 0x8C779221A4FD8156ULL, 
            0x74E260F9980AF629ULL, 0x8D3E87EFD907B101ULL, 0x7F0B69B8BC258F24ULL, 0x30C4E062CC1E5394ULL, 
            0xF723D57264F81776ULL, 0x4E66602B71C6B484ULL, 0xAFE22FAF7EE3C945ULL, 0x23D51FB7DB12987CULL, 
            0xEC265EDB05A07279ULL, 0x2D67271868CF2ED7ULL, 0xB153CA755FBAECD1ULL, 0x6A79A3EAB7325680ULL, 
            0xF2853209B2BBD0B2ULL, 0xF1A6CB38BB80D6A7ULL, 0xC34B5BAEA10E0389ULL, 0xCA04E259E4B900FAULL, 
            0xA4D9A2C3E8D4A12FULL, 0xA20EBB4B124D5CB5ULL, 0x525B6A95041D5EEFULL, 0x10C16B2D600D9F14ULL, 
            0x45B6B713291F0485ULL, 0xCDC207E33885FC88ULL, 0xAA647606F397F97AULL, 0x87012D6C5C2B3E0EULL
        },
        {
            0x9A490FF33E5D5435ULL, 0x3A133E79F49662E7ULL, 0x84C531EDF6411223ULL, 0x1F7D5FDBFD423D4CULL, 
            0x0ABE9E5C7F33E794ULL, 0xF104B67BF0C43A42ULL, 0xBBA3AAB52F6E48C5ULL, 0x2B803C7B0E325E42ULL, 
            0x9B3B008CCE480B5CULL, 0x846813CBAD09EAF2ULL, 0x82BA6B23E8FD6A95ULL, 0x1F878BF3174E1E79ULL, 
            0xBEC9A9F663CAA12DULL, 0x1DE3BA38482D567EULL, 0x9F79E091B9266FC6ULL, 0x24CD802347BDB96CULL, 
            0x34C97C1425219754ULL, 0x91B087C6F84A9DEAULL, 0x7E68CD1EDA15532FULL, 0xE4D1D89359CB9151ULL, 
            0x977D6D51242AA90AULL, 0xA0B6C7EDB88FB5A9ULL, 0x5A1D0DB28AFAF42BULL, 0x4935CC0B84620C7EULL, 
            0xEED0FE3DF08F8755ULL, 0x6B618E8A83E865F3ULL, 0x475B3AE35319D325ULL, 0xF27AF770A3E4A38BULL, 
            0xE2E39AA08AD0506FULL, 0xAF8ADF2C71F19084ULL, 0x8400EAD09D908DC0ULL, 0x3096A43A590F5949ULL
        },
        {
            0x28C966EAE8B3DE96ULL, 0x34CE03331017B137ULL, 0xFB6E4DB6D627FAA8ULL, 0xEA222BDCC231F91EULL, 
            0x2411907C9C101944ULL, 0x1C7F5A61D8BE80EFULL, 0xCCFBAEA580C89B6BULL, 0x9D1176357AAD7313ULL, 
            0xEDC19BAC0319DA58ULL, 0x1E529B23C80F5849ULL, 0x64A4EDDDEFB4FE64ULL, 0xCA355E8C667F2F4FULL, 
            0xDB93D8D420AC0603ULL, 0x0B5181830904379FULL, 0xE0FE8349639B8DC4ULL, 0x20586BF8EC361E17ULL, 
            0x97CE1ADC0AC4129FULL, 0xCDEE73982D651BD6ULL, 0x0489DAFEA52FDC68ULL, 0x1F1ADF3823621085ULL, 
            0xAAF1A593F4C23ED9ULL, 0x00A2DD50A9F886B9ULL, 0x022BAD369035537CULL, 0xE14CA53BBC52F39FULL, 
            0x2456971D4B8F5459ULL, 0x98C14BA3C5E1F68AULL, 0xB24D8C695771B767ULL, 0x620C1DCB6A0805A1ULL, 
            0x70AF592981D8C7FEULL, 0x5F8EB1E3A30933C2ULL, 0xD138945374609939ULL, 0xEA7DCE3927B7ABA3ULL
        },
        {
            0xDF4B0510BA437EC1ULL, 0x8B08AEF6CE8D346EULL, 0x657DA6249D2D29DEULL, 0xB6BB50FB6887FBF6ULL, 
            0xCB2F65A09502EB1FULL, 0x7AF64B7949B6DA6DULL, 0xC52A19C0F6A875BBULL, 0xEA60086DD03B8374ULL, 
            0xF4CB0E30C639B308ULL, 0x0A2C3ACD695E7DC6ULL, 0x45BDF21C90BD6902ULL, 0x2B06974B47DB0612ULL, 
            0xCE688DD62E540E75ULL, 0xADF80DDEFBC74C0CULL, 0xF4CF56A85FA76F41ULL, 0x128DFA917BFFCCB1ULL, 
            0xD95961AFC181F67DULL, 0x8B80CE4C2CBBCFF2ULL, 0x793CF7583C09DBEEULL, 0x791BA746B91F23D9ULL, 
            0xDF2988560C8B6B2BULL, 0x7F0A39AD980F806EULL, 0x047F6E1FB878E7A5ULL, 0xC57DA4B2B76BCBB6ULL, 
            0x12792D37EA771E9EULL, 0xAD9299EAECEC23A9ULL, 0xA4C89C490F400AEBULL, 0xC587A129132C1E84ULL, 
            0x7630978CCD9AC515ULL, 0x9465CF87B371876DULL, 0x90E80E3E89A18977ULL, 0x1691DDE1CB01B449ULL
        }
    },
    {
        {
            0x2EC13B53EF533B3BULL, 0x380C559A66FCA9DDULL, 0xDC4D4220459A2C7CULL, 0xA9A822250F8CB4E2ULL, 
            0xE7462DE26FC4FF86ULL, 0x81B168AA0F76C24EULL, 0x88F7DB36A06C7D2AULL, 0x614B92DDA7D846C3ULL, 
            0x7A361CE28B0F4332ULL, 0x61384207521BA0D3ULL, 0xA5FD70FBC013D33EULL, 0x137425152E47CC30ULL, 
            0x2E3D238995FD7AEDULL, 0x62257390A5D4C8CBULL, 0x4450FDD50D6789EFULL, 0x510002573DE3DD5AULL, 
            0x914A629F9DDD0664ULL, 0xCA8E384DED29538CULL, 0xEBB50555043B3CCCULL, 0x4B97AD91C531BA72ULL, 
            0x13AE59AD561B9A47ULL, 0x2D201009F53080B5ULL, 0xD2617124A14CE98BULL, 0x6775F524967181E7ULL, 
            0x7CE8CB516437037DULL, 0xC5E67C6AC9ECFCFFULL, 0xDEE403613882FC0BULL, 0x4F5C78D35929F3F3ULL, 
            0x35B2F58F85641297ULL, 0x086FDB96F9E7F4EAULL, 0x1C872F64E18FE541ULL, 0x48D5918A072EF1B9ULL
        },
        {
            0xF7D2C78BEEF27AF3ULL, 0x1CC4F7FF4529A43DULL, 0xDB16E0A0FA3F5331ULL, 0xF14558E1BC6E6CF6ULL, 
            0x9A7D85AB9307E200ULL, 0x65C68D9C912C8CF7ULL, 0x852F5FFD8845866EULL, 0xEB342014892691AAULL, 
            0x91EA167E063EBE49ULL, 0x0F90FD37C8EF3553ULL, 0x1A6DAE1E39A1A3BFULL, 0x1F5B2C991568B0DDULL, 
            0x0E475B62C5B07DB5ULL, 0xEB32581F230F2E80ULL, 0x9AEDD7ACE8A28907ULL, 0xF9BD833B5B670181ULL, 
            0x1AC999946B475988ULL, 0xB804F54A5CA71913ULL, 0x476E571253797D70ULL, 0x9554EEB9825E07C0ULL, 
            0xA8F22A953BEF4190ULL, 0x0ABCD98EE21DE0AFULL, 0x49DF694263DD28E9ULL, 0xD065F33A69FEFDD0ULL, 
            0x4E45833E6E08DA2AULL, 0x0D3CFC432F071C5AULL, 0x07F4A71C669A0480ULL, 0x94BC7D5135C97D48ULL, 
            0x1C25A59DD962C332ULL, 0x2A5095828ACB5C34ULL, 0x9C15A1ED220EB917ULL, 0x23E040C172680AD7ULL
        },
        {
            0x8F40152AE7F09F03ULL, 0x9B33719DA19FF2DEULL, 0x460B0AABFB68B45FULL, 0xCE6E11CD1ACCA599ULL, 
            0xE213FFB08F49D135ULL, 0x1037E7DE8058C11EULL, 0xFDD4C91CCF9714A8ULL, 0xAF99BFCF7D6402A6ULL, 
            0x57E9B390D945CDD7ULL, 0x98BB0206F39AACECULL, 0xCD9AF4B7D4CD043AULL, 0x031E9A93F80D3097ULL, 
            0x3A391FF29358CF35ULL, 0x51993709F4A727E3ULL, 0xCDA27F72C514EC87ULL, 0x58195FC03C8CCA6BULL, 
            0x8EDEBFED899C9BCDULL, 0x29BE814B2014CBF1ULL, 0xE49EB0D73D366B73ULL, 0x8A5F44306AF2E192ULL, 
            0xC98F8E4CA9FB509AULL, 0xD29B439F871900A9ULL, 0x80757BEECE4A053BULL, 0x4F69F3BEC5FC7F8EULL, 
            0x0E9E349DCB09F9B4ULL, 0x9C7954F27D819CC3ULL, 0x915D3662C5A08AB4ULL, 0x806A24870A398447ULL, 
            0xAEE2F4581DFF345EULL, 0x81C2D7776472244BULL, 0x0E1E624C57548891ULL, 0xE07CEF37918E8210ULL
        },
        {
            0xF1DDA28E14D9C428ULL, 0xAF846245AB2F877CULL, 0xB11235087AD88DA2ULL, 0x216526090028241AULL, 
            0x48372B51ACC85B06ULL, 0x85FD71A77CC3ABEDULL, 0x8BE0D030A8A0C9F2ULL, 0xAC432CA18B0FE51AULL, 
            0x0AF0D8DF8E23C477ULL, 0x48D31BB75E775534ULL, 0xC55CC07A1122C990ULL, 0xDAF7BDC67BAC8803ULL, 
            0xCD7C5D568EBA01BDULL, 0x5FA5C3BA54958BA8ULL, 0x22150A4D4A31022CULL, 0xCC1D5590AF069344ULL, 
            0x66AF26EF2FCFEC83ULL, 0x3A26B5D3A67F419EULL, 0x4E7237F27D111D7DULL, 0xE0DCCB972CFF3A2BULL, 
            0x83B0CA6C46108074ULL, 0x5F7EA874FC3B4147ULL, 0x438AFAFB00498623ULL, 0xB0B0DDD3A405773FULL, 
            0xC76A65A9ADCBC01CULL, 0x959F63BD50DE6B6CULL, 0x5653659A2B07B970ULL, 0x3700468C68C5EC2CULL, 
            0x3109B40D40B30D60ULL, 0x52E61D4B1769E7B3ULL, 0x9F650D6EF45A0AF1ULL, 0x9ED0B836AD4B52DFULL
        },
        {
            0x33F72A5A478EC6FBULL, 0xAEAB1E20AB16AC1FULL, 0x7EBCEE0B602FE9E8ULL, 0xB2AB5E539FEC1914ULL, 
            0x57A42CC875AAF130ULL, 0xA08CC0ECAEC6DE12ULL, 0x57784DF7E08DC8ACULL, 0x8E6E0673AEFDBB14ULL, 
            0x83C3BBA5C3FD6CA1ULL, 0x831A8CBE4E294515ULL, 0xC32E6AEA426D6832ULL, 0x9C7AD592B7919624ULL, 
            0xC1258B7B66D73B62ULL, 0x47E3D4731ED64FF7ULL, 0x615ADC7AEF0751D5ULL, 0x821E9B92AAA700ECULL, 
            0x316C6407F9BD0354ULL, 0x6A46DA1C26D61615ULL, 0xBA90E9AF40A2E183ULL, 0xFD34656E5B1D12A3ULL, 
            0xB3DCB5B93AC8F43EULL, 0x26B9D71AC5D7CA1DULL, 0x3B49F9619FDBDB49ULL, 0xA57965D5F4190597ULL, 
            0x44CA66EFCEBAF96BULL, 0x7B352BC4C771488BULL, 0xDDD2CE7082498F84ULL, 0x171EB77007B44A35ULL, 
            0x6CCDB6AF6F16DE3DULL, 0xEB72B8B6467C22C7ULL, 0xF45FCAB0C6D9CD88ULL, 0x50C6C859B535A45BULL
        },
        {
            0x13B4B94951ED1EC7ULL, 0x94113F29B0895FABULL, 0xC6500A53BB2655A7ULL, 0x151808E63FB14FECULL, 
            0x11EAE9E1A6D79262ULL, 0x28229C9C96359280ULL, 0xD3D1D9F80F8DEA2AULL, 0x7062DD4E8797A6FBULL, 
            0xBF735EA5B3491423ULL, 0x1B5333F4F19A11A0ULL, 0x0F1CF22422308751ULL, 0xFFF2ADB49B51594FULL, 
            0x77AEFE14C23CE3D2ULL, 0x4649B8876B12DD9CULL, 0x1ADEF42FA1AD93D2ULL, 0x33489AF84BDAC49FULL, 
            0xFEC5B91192F8BCB8ULL, 0x64103F4CBB1C0240ULL, 0x5F6B136ABADA2DD7ULL, 0xAD0C2066FC9A878EULL, 
            0xBC87F432B90C0BCDULL, 0x6D7321E674445F59ULL, 0xA77EB276A5490D33ULL, 0x91DC7ED0AAC5C4C3ULL, 
            0xBBF7A4BE189C8610ULL, 0x4A214003287AC5D0ULL, 0x49686F31A2A2C650ULL, 0x4099B3E149D6C34AULL, 
            0xDD6CBBB83403D6E2ULL, 0xE7C21A90E8967DDFULL, 0x8F0AFA6A98AD1215ULL, 0x658981FF3687DF27ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseBConstants = {
    0xD7BA6443D4034A8AULL,
    0xB685FC3764E04650ULL,
    0xDF1E16A7BA2AD1B6ULL,
    0xD7BA6443D4034A8AULL,
    0xB685FC3764E04650ULL,
    0xDF1E16A7BA2AD1B6ULL,
    0x18CFA61C3E244A68ULL,
    0x119B579168F71C0EULL,
    0x5D,
    0x53,
    0x71,
    0x2B,
    0xB5,
    0xD2,
    0xF0,
    0x0E
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseCSalts = {
    {
        {
            0x70628A1BD60B22DAULL, 0xE7AC2E673C5C4B2DULL, 0x26B070972CE5C82EULL, 0x60A32F1300E0FA5EULL, 
            0x5A9AD3B06427F335ULL, 0x41DC772FF99F5BF1ULL, 0x7D8349669EC4A3EBULL, 0xB4E4E82572B5EA29ULL, 
            0xA1A6F36EB825E1CAULL, 0xEDA11AC98C40F8DEULL, 0x63D9461B48C80F38ULL, 0x9EA244F6281D9499ULL, 
            0xE8BCF1F4C372B237ULL, 0xAFF5F8AA00DFAFF1ULL, 0x82DF0CA3F1CA8A39ULL, 0xBCDAD2102EE7EF5EULL, 
            0x2D64829A491FA9AEULL, 0x8351306DB2F737D1ULL, 0x7DAE5D2CEDB05FA5ULL, 0xE5126E0DA0BCCE9EULL, 
            0xC429F843E23EA3E2ULL, 0xABB480B88D4B96E1ULL, 0xA6FB95D3ABED553BULL, 0xD01F26EE73C73E78ULL, 
            0x9B20BC859313292AULL, 0xD6F0C641F913A86EULL, 0x4C528F3DEAC66AB0ULL, 0xEBB1E2F647291748ULL, 
            0x9A23A63C639F31FFULL, 0x2ED86CA17D78B21FULL, 0x2C91820C532170D5ULL, 0xFB75B8ACB3B4FD98ULL
        },
        {
            0x337FE3EDAF450EA6ULL, 0xF0DF7D929077B80AULL, 0x5D64DB427442DD0EULL, 0x9CC8D2A22EB39141ULL, 
            0xC1E5B31E1D868347ULL, 0xC4D57285EE156374ULL, 0xD673FD7715B5BF87ULL, 0x1FB12BDE4A3228D2ULL, 
            0xB3FD5623178165A4ULL, 0xA099391CBD059F6FULL, 0x2D63E8A29BF87BA3ULL, 0x0C757769A1CABBABULL, 
            0x41BB8C19A62D3C23ULL, 0x30C2AC06BDFF6FE5ULL, 0xB084C7C442926194ULL, 0xACB908DDA45EBB4AULL, 
            0x41171E5312094346ULL, 0x573660C7B42752E0ULL, 0xB41D4EA8BCDBA151ULL, 0x29CD77243EF0A03FULL, 
            0x9563120EBC39916FULL, 0x704A20744D672603ULL, 0xCB3FB644E0C80E65ULL, 0x8D2FF872FF1B1E73ULL, 
            0xA373E1CB206743D3ULL, 0xE22F2241180B82A6ULL, 0xA2ADDDF4D6E767FDULL, 0xED4A67FD5DDE2375ULL, 
            0x9B7B423514F0C5C2ULL, 0x76524D7E36A7A124ULL, 0xD51018E8A250EE45ULL, 0x2B02B3CEFDA454CAULL
        },
        {
            0x24329E1990520B5CULL, 0x517D531713B1CF25ULL, 0x323DE9A6C1406251ULL, 0xA46A7358C9921EE2ULL, 
            0x37329F226BC46BD3ULL, 0x28142DDEA3F7528AULL, 0xB4660A36A2C4D8FDULL, 0x9BEA0ADB07E4EBACULL, 
            0x4085A65030822B63ULL, 0x694B3CC7161B0965ULL, 0x3ECB27BD53964F54ULL, 0x13621CE380A319F8ULL, 
            0x0A6627C02566F710ULL, 0x7BBB4BF4D9F0EF6AULL, 0x6AF4E3AB24652239ULL, 0xD6BC33F16DC04F66ULL, 
            0xE372BA50474FC80AULL, 0x153CA14C20C7D9D9ULL, 0x47798F9CC3AFB23BULL, 0xB99588C5E1A2CB40ULL, 
            0xA2EA95775CC3BDE2ULL, 0x71FAA1835ADB9921ULL, 0x0A1327A7E0D01D89ULL, 0x13541FF3B66BF6CFULL, 
            0x6564DA8FB84E1CAFULL, 0x56D01088E7C094E5ULL, 0x011D4E172FDAC165ULL, 0x895AB4048B35C179ULL, 
            0xC23905C701CDA51AULL, 0xCC6BEF30C0F3BA40ULL, 0xEF1565E4E48E0A69ULL, 0xB315088FD5FC9A7FULL
        },
        {
            0x6124C861F2908984ULL, 0x2859C75A0FADF029ULL, 0x542F2FFCB5CBE0A5ULL, 0x94F067D79B7F042DULL, 
            0x109CD682687F8A89ULL, 0x5E50A98871E0DCC2ULL, 0xA8FBDBECEB53C1DDULL, 0xE7BCC1840E5815F1ULL, 
            0x92EC02553A68C154ULL, 0x42D50A458E36A739ULL, 0xAD34CC447E3A7E1CULL, 0xAB821D1320A62CB1ULL, 
            0x032E7DC41991ABB9ULL, 0xCB895C3AFAC9274CULL, 0x71ABA64853FBA3F9ULL, 0x45AAD43A451AE67BULL, 
            0xAAFDE09554D547A0ULL, 0xD0D058342595E4FBULL, 0xF16170DEAF572BD4ULL, 0x3BB29446004BB892ULL, 
            0x7C72A6B61364F2D9ULL, 0xEFEEB3CE354FA85CULL, 0xF0FEF0161AE8916FULL, 0x3F40782F1D7ABAC6ULL, 
            0x13B298BC983458C0ULL, 0x4F7FB7023FEEEEA5ULL, 0xE6638290C8A5FDF1ULL, 0x0E3AD196AC601BF1ULL, 
            0xFE60B7A831527850ULL, 0x1716724CF33C2979ULL, 0xA0C8309A5346738EULL, 0x0FBC2C1B47A06081ULL
        },
        {
            0x572C9622A8A9DB1FULL, 0x65A191E9642D5B42ULL, 0x096644BBB4CE169EULL, 0x9684EE425D69DD3CULL, 
            0xFF512E734289899EULL, 0xC67F7A52D3FF8F7AULL, 0x15065228F6306D0FULL, 0x99A4F49A0CC5778CULL, 
            0xB83F31C653EC5240ULL, 0x32DD8BC20E250249ULL, 0x585EC7AE83B988E4ULL, 0xD38FCF6B24F69910ULL, 
            0xBB04EF8C1F62F077ULL, 0x77FDF28F45C48706ULL, 0x5083F536E543415CULL, 0x1F3B1CC49ED2F070ULL, 
            0xE3591974FC0E6380ULL, 0x4B9290594543081FULL, 0xD7F703B365BD69BDULL, 0x5BDA0EC06BF36A65ULL, 
            0x4AA2567F6898903DULL, 0xBCA39A886AE9EA3BULL, 0x78D8EA078AE77353ULL, 0x62918006D58A4136ULL, 
            0x2D0C91E57827D9EDULL, 0x490FE0FB4F253371ULL, 0x05B8682FE0237DA5ULL, 0x11CD130BA39D0427ULL, 
            0x7AC0B75CA6C67ADAULL, 0x18AE91BF64FF12A1ULL, 0x600516E415F5BD87ULL, 0xE77DC6F9FCBDB4DEULL
        },
        {
            0x429E5D7952BB09B1ULL, 0x94F9B3ACB5B974CBULL, 0x22F649A75926288FULL, 0x834B1A43418563BFULL, 
            0xD7CD3B7B1EB7052EULL, 0x2EFEB99A5854DF91ULL, 0x22BF5B5539D02007ULL, 0x8203049F9DD5CCF0ULL, 
            0x0C6CF7790D9A2B4CULL, 0x008B1F0C35721EDAULL, 0xBAA583391762E396ULL, 0x78F81E7FF3234C89ULL, 
            0x8179052CF1F00E37ULL, 0x41157B67F6770909ULL, 0x15D2001178418D3DULL, 0x16B0000046C1EF14ULL, 
            0x181ED6AAE1DDE42DULL, 0xADDE377D2BD779B9ULL, 0x525E6597559E861EULL, 0x4F59EE9108EBFF1FULL, 
            0x34543911435BA9F2ULL, 0xBEDF99B4AAB38976ULL, 0x9A266AD6369F7677ULL, 0xC559BBAF756B158EULL, 
            0x89AE21CBA71EE735ULL, 0x015576A9E0D63E61ULL, 0x8990175C5B7D46BCULL, 0xB1F49C60DDE3DA60ULL, 
            0x904A6A73CFDD3E2FULL, 0x244D5BA62E29BA01ULL, 0xCB9AB2912D0BB0D0ULL, 0x8338F2FEFC11D008ULL
        }
    },
    {
        {
            0xFDE41F0E06D0FFD3ULL, 0x2BC0EB17D14075A8ULL, 0x82B252BB303E56F9ULL, 0x967C2D0FC0CF5E34ULL, 
            0xD78AA01B51E11460ULL, 0xDFF2BC43146AD4D8ULL, 0xACD566FEF6BD0C85ULL, 0xB028036EE805587EULL, 
            0xD733BB254FEB5366ULL, 0x98F99C7D6186A7B9ULL, 0xC3CD0E20D7E93908ULL, 0xEA0266CA38D54162ULL, 
            0xFB4804D752D84153ULL, 0x73AC3A25941CC5C3ULL, 0x83075257A0AAFFBAULL, 0xF548A0404E1A834CULL, 
            0xB36CC8E7B2953249ULL, 0x37387981DAD6C933ULL, 0x38FD8E13F04BD9EDULL, 0xF62C8EE3BDABA45DULL, 
            0x4FE28628334A841FULL, 0x02C7B86A4061F02DULL, 0x1754E3FB775C810DULL, 0x91D5B5DEC84EEA63ULL, 
            0x2C452A71B53B539DULL, 0xFED3DF0DF9FB7FB2ULL, 0x39E00B29150A82BFULL, 0x5A25DB46FEDCD99BULL, 
            0x561E4C1ED0AC319DULL, 0x72CD0E63F6BA0D3AULL, 0xA6DA8DA26DD7BFA6ULL, 0x500075C140BF6BD4ULL
        },
        {
            0xC972C8785DFAC743ULL, 0x18E4E5D70A032B28ULL, 0x13DBCBBF14308BC7ULL, 0xC7AF2A11D4A2DC6DULL, 
            0x57B4BED66FF68B60ULL, 0xDF88F595F03BE48EULL, 0x67530022A0BDA24EULL, 0x4FDF7EEAC867185EULL, 
            0x7BC812FB81922FE4ULL, 0xBC1DC5754F73E8E4ULL, 0x715FE9A6B67A3EE9ULL, 0x22E9E7C2BA287728ULL, 
            0xFC5FB78F7893C517ULL, 0x2CEB713709F7F855ULL, 0x4A57BDAEE94172C0ULL, 0x1FAE0B246511A0B2ULL, 
            0xBFD5EA468331C888ULL, 0x329F42657DBADEFFULL, 0xAB736401561E2095ULL, 0x968137D93112244EULL, 
            0xDE19E4C3B2B4E19DULL, 0xDEC873D620DF68C5ULL, 0x595D4B85A780D3F2ULL, 0x64AF4886EF8A4142ULL, 
            0x3127B7DA79B81CC5ULL, 0x4C214E09DECBD106ULL, 0x6BD352469DD3C00BULL, 0xDFA5226539573A92ULL, 
            0xCAA62E890A7A228BULL, 0x5D8A2C0DCB2B2553ULL, 0x10BE44A5024B0EAEULL, 0xFA935AA2A0E0B72EULL
        },
        {
            0x3C2D753B60560FACULL, 0x9B04B13B60BF8455ULL, 0x36509D04C97D3DB6ULL, 0x7EDBF6FCE12FE226ULL, 
            0x3288BF95D48EAC53ULL, 0x0FFCA7E5CDF58928ULL, 0x6DB40CBD3CE263CEULL, 0x7AC073D9A624FF69ULL, 
            0x5016B3584E82CDCDULL, 0x1CA37AA2393616AEULL, 0x3AA1A6E3F598A59FULL, 0xC4FF4815F09B18BCULL, 
            0x0D73CED9CDE44E04ULL, 0xA4CA23FBD3CE7F7BULL, 0x91DD7C80C092A016ULL, 0xF3869DA96F1E85F7ULL, 
            0xDF946C23BB540481ULL, 0xBED265D2E4EC5DAFULL, 0xCE82564ABE5DF7E5ULL, 0x75A668252CBBF30AULL, 
            0xA5E1EE9B69F0F318ULL, 0xA56CF16CD9839969ULL, 0xFBB6810C1D6A27CBULL, 0x4CC8603F50895890ULL, 
            0x06B3B93F905964EDULL, 0xBCF32FD3B9475223ULL, 0x2C08A9E642F47EA2ULL, 0x4195F69FAFB4E278ULL, 
            0x95593DC14A23DADBULL, 0xFED8108A8BA587C2ULL, 0xB6B94F3039957CA3ULL, 0xA3D01717D1F8D3EAULL
        },
        {
            0xF80EFF81E6FAA92AULL, 0xCF61B7AFCBB0C04FULL, 0x41025BE1C991A568ULL, 0x9845B0293EA84C6FULL, 
            0x3EDBAEF2AA6C0716ULL, 0xFE3F6345B12E763FULL, 0xFFF20F859F0E9BC3ULL, 0xF169AF5C4F78F3A5ULL, 
            0x9AB7B22B25E9060DULL, 0xE6D535F91E80530AULL, 0xA5925DC66CD5311FULL, 0x9260923B01A550C3ULL, 
            0x4131F4894DF4C1ADULL, 0xE51851DAF30B588DULL, 0xFCAD96048235F795ULL, 0x0AE067037D6FA91DULL, 
            0x6E7492ECA419316BULL, 0x89939C9526083852ULL, 0x3DA46C6CF2FB10FCULL, 0xF5F6CD13A11DB6BDULL, 
            0xC1EF80BED9542E99ULL, 0xCF1BEC2FC0D603B8ULL, 0xA531111164A9E422ULL, 0x7FF1F8773E1BE3F3ULL, 
            0x3657E694D6C13379ULL, 0xAE7CBE1B29F18EE1ULL, 0x7557ECA266475D13ULL, 0x0F6178513E703E09ULL, 
            0xF4F427B0E28817AEULL, 0x7AAD1E6DB27598CCULL, 0xEAC33D7A623EA1EFULL, 0xBCBE347A106FFE65ULL
        },
        {
            0x7EB5DC02A0A6AFDBULL, 0x70EBDF08A04322B5ULL, 0x9D025AD38CFE62C3ULL, 0x98133EF6F1F0C5A9ULL, 
            0x3644337040BB3361ULL, 0x48EE13D171AEBECCULL, 0x38C3162F9D1A8A06ULL, 0xF5F36F8D6B05B562ULL, 
            0x53D72E07C8D844BBULL, 0x6DE9C45ECBC96EEFULL, 0xD7E6473AD59B91D0ULL, 0xF5516E75EEC013D8ULL, 
            0x54F49DA62C9BBE5DULL, 0xF721BA8ED3F37520ULL, 0x540AD6A62105DA77ULL, 0xBDCDAF35AFE9D636ULL, 
            0xE3EF9A4A28B9DFF5ULL, 0x3AAF32A40160C274ULL, 0xC80BB4075DFE06F0ULL, 0x4E9EE4CD904E6BB4ULL, 
            0x4B96B5774DD55EB7ULL, 0x655B0BE6E69EB5D4ULL, 0xF989767A2221AECAULL, 0x49186D9BDE0C1933ULL, 
            0x5AC0941AC819E58EULL, 0x20CE0C35D1F3EA88ULL, 0x456AAB83BCA18E18ULL, 0x587F8F975CFA8601ULL, 
            0xE8B4CAF2D5A8EC4AULL, 0x88EBE82D7CB42B6EULL, 0x69FED086767DB4A0ULL, 0xEEDD644B0DC21678ULL
        },
        {
            0x260729527BFA1650ULL, 0x4292DA29F328E4D7ULL, 0x57FF37C5DC13599FULL, 0x3F47D281B2ED1810ULL, 
            0xBE78A1BE7E931AD8ULL, 0xD8374B1732925504ULL, 0x30CC3A4058489178ULL, 0x2F390FBC7321EA7AULL, 
            0x8DFB4E709960A20CULL, 0x1A2AB0F907AEF342ULL, 0xA4F7F02DBCD660DEULL, 0x2A070C957FF05C06ULL, 
            0x8F0C9D5CA0189F45ULL, 0x5A276F3856172AC4ULL, 0x9A8A322A27302572ULL, 0xFDD3DE763D0DCEBEULL, 
            0x1E2183EBE48A8162ULL, 0x8112D163FD231392ULL, 0xECF7AE579DE0C48DULL, 0xE86B6DBCAA7C1CF6ULL, 
            0x7F576E20CF64FC8FULL, 0x8AC1CF359C9D0EADULL, 0xB477B34FAA439007ULL, 0x102A440806899723ULL, 
            0x4D9182772762F8D2ULL, 0x8F0BF7C72742F98BULL, 0x61AEAD1F83BB10DEULL, 0xEE49C9EE006A450CULL, 
            0x417B05E332B14A75ULL, 0x41E083A5B074922DULL, 0xE03E6EF023F0DC2DULL, 0xB1DD7C603E1C57E8ULL
        }
    },
    {
        {
            0xF990B3901DF18B0DULL, 0xE660A95E7B392914ULL, 0x275CF6B6C67D914FULL, 0x6E072A24918A1374ULL, 
            0xB9A3E633B65E261BULL, 0x84C7F7310D1778E2ULL, 0x86228BA3245DFF1CULL, 0x711294631E816DA5ULL, 
            0x077277E2AD32638EULL, 0x2DAE6188816C96DDULL, 0xC4D6B9658ABA2544ULL, 0x12831724F87D6BA8ULL, 
            0xD8BCA27755FF57EBULL, 0x84FC34A03ABEEA6CULL, 0x4E002EA78BB098FCULL, 0x13422D0A7D76BDD1ULL, 
            0xCFE8F121F0760AE4ULL, 0xE8C3284976B2990EULL, 0x6D00B95253D7664FULL, 0xEA65670084796909ULL, 
            0xF399F05DB573E605ULL, 0x110B3909D7CA2077ULL, 0x07C660A858EA4B2DULL, 0x5491EE5839377CD2ULL, 
            0xD8A52EDE1099F555ULL, 0x3D83F54C3094AFF8ULL, 0x531687BB4F29B4E5ULL, 0xDD0092FDD3098A4BULL, 
            0x921B67F30EB535A4ULL, 0xCB70F77A9A98930CULL, 0x57BA347036A38954ULL, 0x572F2A3116065281ULL
        },
        {
            0x7E6E5E6E112A95E9ULL, 0xD4A1E1F0FE641438ULL, 0xB9F697DC26C32DDDULL, 0xD5092E04DADDEAAAULL, 
            0x8ADD982519DBAA6CULL, 0xE7316F81E18402CBULL, 0x9AB690B8FCF64D91ULL, 0xAD0BF4BE0EF8CFE4ULL, 
            0x005A0368CAF5E60AULL, 0x96A7714EB7207A17ULL, 0x946F5C475129A48BULL, 0xCFD969429A2131D9ULL, 
            0xD11E8BAF230648B6ULL, 0xE63652BFC47B9E44ULL, 0x3BD277C74AC3B0DCULL, 0x435375BBA6A15B5CULL, 
            0x048880F17E6A9749ULL, 0xE34943DA5F87BCAEULL, 0xAE71F6219AF4E20FULL, 0x4066DC695DA037B6ULL, 
            0x49C166FE38E6BB96ULL, 0x81C164D435CFCF12ULL, 0x16631CFBF77A3AE7ULL, 0xE66507584390C72EULL, 
            0x0A8C087057C10F89ULL, 0xA9E6DDD410BE5A8FULL, 0xE2E7E26F84EE77C2ULL, 0xF10968598D770C4DULL, 
            0x1F3EA08459DBA427ULL, 0xEE14E67DD0EE4227ULL, 0x49D8BE5A110780F7ULL, 0xC14F4A61892ADBFEULL
        },
        {
            0x9290B848D9E62FCFULL, 0xC81F0C5EEE9E65BEULL, 0x4B9A0A80C184159EULL, 0x55858E1942D1BF99ULL, 
            0xDF631A8C26901049ULL, 0x3CF60B16A50E65E8ULL, 0x931E51A1B7CD4D78ULL, 0xFFCCE9B4C1D461E0ULL, 
            0xA5190F2F64D058D0ULL, 0x63AB5A8F5F17F5EDULL, 0x6CDEA01F7474A69AULL, 0x90E92CB4659E750DULL, 
            0xBE3E2950A3372232ULL, 0x59C1F2A499D5D5D6ULL, 0x05EAEEEFF208D8DAULL, 0x4978087F428B3E87ULL, 
            0xA2BE6C000496E890ULL, 0x280D88437D5A7B85ULL, 0xB1E9060C21A2DE4EULL, 0xE352104CA75FC524ULL, 
            0xDC324BA5C6FD02FAULL, 0x6FDFB3D1FFDEDFA2ULL, 0x6ADAE120B2CC08D0ULL, 0xE002C252D4C2BBADULL, 
            0x3BE73CDF585F21AFULL, 0x67DCD271FD7F7EC0ULL, 0x66DEA9EF8067887BULL, 0x439BC0A25EB2181BULL, 
            0x77F1FDC6A8F5CB5DULL, 0xDF64DC41C4C11E21ULL, 0xDC8C02DB0CF665E6ULL, 0x6910B9F88C345876ULL
        },
        {
            0x3E6C428A4EFE46D0ULL, 0x84691644494ACE8EULL, 0xBE3EC61DFA571DF1ULL, 0xE50C293D51D5FCD4ULL, 
            0x7F030E72D760E595ULL, 0x5852578B8362053BULL, 0xC44EB1A6D71594B1ULL, 0x64FCDEF94CE553E1ULL, 
            0x2F55BF890B18A1C3ULL, 0xF5A0083E606529C4ULL, 0xAF532A6597E1EFFAULL, 0xEBEC500666140204ULL, 
            0x983FD1B05A0CC4CBULL, 0x37856833D84C9C94ULL, 0x586CAF659EAFDCA5ULL, 0xB7F4E4ADD924BE10ULL, 
            0x958CC2F01F038AFAULL, 0x7F47D1377E28F21CULL, 0xA93F115AFFB83012ULL, 0x4251A3371105D173ULL, 
            0xF745C4994C1BDE3AULL, 0xF803E3FA928A6C89ULL, 0x39E0742D6EE13C90ULL, 0x0C3E2D6E0E0DA204ULL, 
            0x7DE873DEA0A6758EULL, 0xB2478213982C0BD0ULL, 0x3F02A38CC3B95ED8ULL, 0xCF3F78D09062A975ULL, 
            0x266B6463B33A1664ULL, 0x57F8598732502C42ULL, 0x5735CA80086BECAFULL, 0x86754E56AFD066BDULL
        },
        {
            0x0C7829D61068576FULL, 0xE616D4E651660736ULL, 0x4DDEB693EE07958EULL, 0x62BAC5E963378986ULL, 
            0xAB4C5BEA7D0BE363ULL, 0x30A223F02CCD0CF2ULL, 0xF265F983D885807DULL, 0xAFC5B1A9378442B5ULL, 
            0x92C03E9538CE0672ULL, 0x0160318D48EEA0A3ULL, 0x08C5DB047CD39BEBULL, 0x3EC50EB8359CCDE8ULL, 
            0x8F9229519D01E6ADULL, 0x5ECE5D39F35BF046ULL, 0x0D2CFFC29C31D9CDULL, 0x1BC87B8F0576D96CULL, 
            0xC450CEC60CA9B159ULL, 0x5EBB7102A3845C25ULL, 0x58DBE9DF0A33097AULL, 0xBE154A83E01FF8CAULL, 
            0xDAD268E682CFBC36ULL, 0x1463228E03CBA6C1ULL, 0xED842422628DE2F3ULL, 0x6CECC9881693C682ULL, 
            0x2A68E8F474A549A9ULL, 0xC67A808B2B9CDFFAULL, 0x6934760EABA4A7CCULL, 0x8F3456FE62101F51ULL, 
            0x8CE04CC947E743A5ULL, 0xFAD8EAE132AF9D91ULL, 0x6A23C0FBE8D4320FULL, 0xC147B30FA7989C8AULL
        },
        {
            0xDF1D0130F55357C7ULL, 0x1CDB14EABFDD3AFDULL, 0xD263AF1C08B9F765ULL, 0x287D167C61B9CEE0ULL, 
            0x494BA0C6D007F3A8ULL, 0x973A5935751202CCULL, 0x49B49BCBAAC944E4ULL, 0xD29CF784078C690CULL, 
            0xCD8F7C121B086215ULL, 0x7F3435D6009999ABULL, 0x695FA7C5BA3E2F92ULL, 0xC4D6A80E7BDA3D24ULL, 
            0xAAAE626E56C195B9ULL, 0xF557AD1BA65F87BBULL, 0x5397939EDD1AC674ULL, 0xA8D489F1C1D7CF14ULL, 
            0x49FA599B5920B492ULL, 0xBA2687C5ED123B12ULL, 0x0852C226992F75CCULL, 0x9FA81AC01F4B00F0ULL, 
            0xCA62D0B2BC20277DULL, 0x5FD75574AE1880B1ULL, 0x309D6D117DD0D2C6ULL, 0x856BAE1B4DBC995EULL, 
            0x5ABCB9B7EA8347B2ULL, 0xAC2012FF4A23B3F0ULL, 0x883B8C168DB30EA9ULL, 0x3D7F33EA16E94E1FULL, 
            0x4AAA7117371C2C0DULL, 0x52632F4B049A1D85ULL, 0x97DD06AFDB43EF37ULL, 0x0B308E37C90D2464ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseCConstants = {
    0xE490F9A3A6410E4FULL,
    0xBDBB95128E576CAEULL,
    0x9ABD3B56C14BF140ULL,
    0xE490F9A3A6410E4FULL,
    0xBDBB95128E576CAEULL,
    0x9ABD3B56C14BF140ULL,
    0x3077D4A0D2955E0FULL,
    0x9D540AE70B58F5A5ULL,
    0xD6,
    0x85,
    0x8F,
    0x99,
    0xFE,
    0xA3,
    0x3F,
    0xDA
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseDSalts = {
    {
        {
            0x5C108A7AEF6494E4ULL, 0x3FDCDB8C5A49DA5EULL, 0xC22D0520653D1B5FULL, 0xD3F838C5A9AFD407ULL, 
            0x31C21F2D9BB2EB93ULL, 0xB6BD39982A60E423ULL, 0x1F230E79C36DB37AULL, 0x8BF75E02DB009CE4ULL, 
            0x723E18736AF8299FULL, 0x33373DB41AF78C83ULL, 0xB2EC0F8C1A457882ULL, 0x6ED03E1F73236FB3ULL, 
            0x47EAFB01AD11CE61ULL, 0x9A6882AAF4570519ULL, 0x447479A11067CB05ULL, 0xA98A13D5844A049AULL, 
            0xEEF638F573B81131ULL, 0x8E39A3A0EDF1FB7FULL, 0x5DEE8D3F13E456C6ULL, 0x256B8D61D5A79A2EULL, 
            0x98C3D585C6176F4AULL, 0x96C4DDB8569BF2DBULL, 0x3A5CBAF847C1B4F5ULL, 0xF5CC66A6DCF0DF3FULL, 
            0xAA429373BB9FCC92ULL, 0xDE73D03F75EEA5C8ULL, 0x7F11105C471B1584ULL, 0x6BD68194FD5679B3ULL, 
            0x3726BF8447D38F97ULL, 0x7F85BAB1391BDA45ULL, 0x9B6CB2987D55FD60ULL, 0x6047D74AB979E985ULL
        },
        {
            0x06EA5C1BFDDC6B9EULL, 0xA2A7A88670B42536ULL, 0x5AD14692D2B16E0EULL, 0xF3EA806BE0131A84ULL, 
            0x53F22B2DA5F4EF25ULL, 0xA2C1B4DA31DD05EBULL, 0x820E7FBF9D968872ULL, 0x3ADA6B66CE246B39ULL, 
            0x53CDCC02266964E3ULL, 0x4269D9BD1CC62960ULL, 0x16295FD4396B3C3FULL, 0xAB491447321CBAE8ULL, 
            0xC3A4E51B226207E1ULL, 0x42384D92308E1E0BULL, 0x8ACB6CC5A3E1E280ULL, 0xF67C4E3796C16322ULL, 
            0xA1589A59623E820CULL, 0x661E05768D61E790ULL, 0x81D00047DF6F586FULL, 0xE9C4AD8EE207C1E9ULL, 
            0x7BC00500FCF3654EULL, 0x4542A15CC0B2D4D2ULL, 0x33976F64D05AD3D5ULL, 0x3A816832A35A01C4ULL, 
            0xBB0A985010D9DCFDULL, 0xCC950D7A4ED082BAULL, 0x51893F69DB9E1555ULL, 0xE2BAEAA986ECF2D0ULL, 
            0x6EC28F095F767998ULL, 0x0E94DBE8852597B1ULL, 0xC789C32C9A7F8697ULL, 0x0277FE61CF9FE56FULL
        },
        {
            0x248B6E7795A414DAULL, 0x86173F6EE2790A41ULL, 0xD1DB611EB10795E1ULL, 0x04FFFB83C7F35DD4ULL, 
            0x8F9FDAFCEB7784B6ULL, 0xB31C27F1F7A399B6ULL, 0x3263073E958230B6ULL, 0xCE122AE8038CF4B2ULL, 
            0xCA81090E7B8144E1ULL, 0x600F408B11EC4C39ULL, 0xC4BFC4AF374D8038ULL, 0x1D50ED53330D464CULL, 
            0x9A4CB2DE6A14440AULL, 0x54F43467958BAFDCULL, 0xC2163C27330E2014ULL, 0x288DF01174A1C1D3ULL, 
            0xC9F40FBC03BCCAFCULL, 0x0897E5EC4B4D23FAULL, 0xCA4F9975773A3312ULL, 0xA23AC322E47159A6ULL, 
            0xEE2F8D5920F78C89ULL, 0x21948E6735EB2887ULL, 0x0A74341764980E9AULL, 0x8A460321ACFE1949ULL, 
            0x2C9BA705E2783359ULL, 0x2A54509CA6319C7FULL, 0xDFF76E6F502831B9ULL, 0x798FDA51B451AD77ULL, 
            0x66A273B2C3084241ULL, 0x8691B008FCF61094ULL, 0x43B2B008DA487747ULL, 0x0B24AC41FADEF96FULL
        },
        {
            0xDE84EB8CE987CABFULL, 0xE4330118D5168130ULL, 0xE284AE5DE880D1DBULL, 0x1501D0A5D2700FBAULL, 
            0xB661C7C01A00002AULL, 0x1B81CC843F68D2E2ULL, 0x84295A00803303E0ULL, 0xF2DD2EA606AFBC96ULL, 
            0x001D60A801D9CAA7ULL, 0xCB15E3F6B3598723ULL, 0x236DB6A142195D84ULL, 0x647181596BFF9A73ULL, 
            0x299E9549B7C443F5ULL, 0x8CE1D75E1CF5993DULL, 0x7302E06084498FDDULL, 0x6CC194B2A6F5B995ULL, 
            0xCADDEF0C7627BBC6ULL, 0xC16EB0F5BE49A820ULL, 0x748E22220C804C9CULL, 0x515B5DC6BE4CED5BULL, 
            0x6CF5843E80ECAEACULL, 0x63226AD0F665C6D2ULL, 0x3AB596CAEB0B88CBULL, 0x656BB0025797ED6DULL, 
            0x05DCEA84C728BB53ULL, 0x0243832D6912F125ULL, 0xA56BCAF246023A0CULL, 0x96974ECFF3CD7EDAULL, 
            0x4DB558EA2913A6F2ULL, 0x901B6AFB878A9918ULL, 0x99E6922A061A95B9ULL, 0x0FAD6FF18D8A726FULL
        },
        {
            0xFA525C084BB97178ULL, 0x864E7CD7DDCC4E39ULL, 0x7F212353E099E547ULL, 0x17140541DD728BE7ULL, 
            0xA2976965B83B6145ULL, 0x182B2668B2F8A68EULL, 0xDCBEE2DBE39C4A84ULL, 0x74A93CD490EF95ABULL, 
            0xF27BD97A9C3F96EBULL, 0x2B07F134E0B73500ULL, 0xCA8A9D61D494EC46ULL, 0xD745B36A3092F9F9ULL, 
            0x9A0D28CBBC265331ULL, 0x73EEC69768259233ULL, 0x1DAB0E5A8DD2A3E0ULL, 0xDC09BB7B8825A6D5ULL, 
            0xAFF60EC2902C5EE3ULL, 0xE4029D99125BBAE5ULL, 0x301133680FA272A2ULL, 0x83FC8202E112C37AULL, 
            0xA4EDA4B4BDF46B8AULL, 0x74610F47DC7E0498ULL, 0x344AE486DDB4BEB0ULL, 0x33A6D4129D506C6AULL, 
            0xCA16265B1A714710ULL, 0xACBA14A91EA6360FULL, 0x63F45F63FADEA4EBULL, 0x092092F44C42B559ULL, 
            0xB53B3317DC871E3AULL, 0x156F04FB15D85ADFULL, 0x1B181DFCF8EF2763ULL, 0x9EC427037FE43309ULL
        },
        {
            0xBA4FD7FC1B568C78ULL, 0xEFB3CC0AAFE3A296ULL, 0x8B79CD5D8105B438ULL, 0x24339163D82A9E3DULL, 
            0x32621D8CC25204C1ULL, 0x44D3188D2CD219A0ULL, 0x08DDD24C38ACEEF8ULL, 0x6069DA880E7FEF1EULL, 
            0xDE99A4F2BF8747FCULL, 0x6EC6286A39C5695AULL, 0xB39F6832F5630D87ULL, 0xFD0CB68BFC89D57FULL, 
            0x6B02AC9036B68706ULL, 0x56774E5BCB38B11DULL, 0x4AB234B2FCDE5F45ULL, 0xDC56B575A2035351ULL, 
            0x3BFB87387602276FULL, 0xE644B3E9629A31A4ULL, 0xE8428BB55C70A005ULL, 0xC2D7055106315653ULL, 
            0x31A2433D34FE344EULL, 0x980B244C0C1D2B59ULL, 0x6E15609CB23D4912ULL, 0x4AEAC30CE5DFE116ULL, 
            0x675141265AE7DF2BULL, 0xA7E58465A8685A9AULL, 0xBF4DC01F42AF11FBULL, 0x15D6D0B89FF76023ULL, 
            0xC80C95229DB0FD5BULL, 0xA72549365BD72843ULL, 0xC515970E9EDB09F0ULL, 0x6961EB2E4B5DA539ULL
        }
    },
    {
        {
            0xE79549C64A973C42ULL, 0x4941EFB6B4D96C7EULL, 0xF61F9141EB5431F6ULL, 0x347685F548C4C736ULL, 
            0x40937082DF979769ULL, 0x14D1D7C040E36EE3ULL, 0x006E145181C7B16EULL, 0x264C2103BD4F24C9ULL, 
            0xB3DB473CDDDCC770ULL, 0xE58FE8C0DFA2FF8CULL, 0x1162602F83BBB823ULL, 0xD29F38B19FC27B8FULL, 
            0x39FFC74CAFFA4CD7ULL, 0xB9047DB4F0A06C77ULL, 0x0DF210B17709B85BULL, 0xC88F6AAB51A2A9B2ULL, 
            0xF1FE6DB2602D61C8ULL, 0x59D03AEE436C431DULL, 0x76BB3AF19E2E8899ULL, 0x1C701AC488C7B12AULL, 
            0xB64C7543CCAE2B9FULL, 0x2C577935449BDD1AULL, 0x5D5001EAC3AA5741ULL, 0xE74FE9F1AD23E2ADULL, 
            0x71E5142C6E1C6EC1ULL, 0xFC88168C67D9BFCEULL, 0x4CD9E0DA07510945ULL, 0x26D19DEA4F7E8410ULL, 
            0x70EF1633A6723EE7ULL, 0x960942856A0F993EULL, 0xBCF01AAA69D4E830ULL, 0xB0FB2A2B56972B8FULL
        },
        {
            0xA44217209B1D40D3ULL, 0xFF22C423B529290BULL, 0x5BC77A579F915076ULL, 0xAD74C0305F735970ULL, 
            0xE097F2E3B161890CULL, 0xA931B104E95D50F8ULL, 0x8791FE6E069C97D3ULL, 0x04159D9E22F361B6ULL, 
            0xB7C8CCC0398FEAFDULL, 0xDC0AA09507C8EDEEULL, 0x13B8827240C1BC6AULL, 0xDE66FCE618BC3E6BULL, 
            0xBC08DE2C3D882112ULL, 0x13D6A4E46E4A8E3CULL, 0xC76403E30B339FF2ULL, 0x2262853EA405DC5BULL, 
            0x4D27A530532C75BDULL, 0x00302937379AF22FULL, 0x2AF0D5D84988EB61ULL, 0x7B6450A5FD9E0139ULL, 
            0xA04BECAC6C77B536ULL, 0x2E8C3FD082A4A79CULL, 0x1CDFBBD0094E52D5ULL, 0xDCAE14BE53281CF4ULL, 
            0xF86289E8DCC85006ULL, 0x1925B884355F487FULL, 0xECAE48E7FAF6E81FULL, 0x2AF51B325B5DE0C9ULL, 
            0x5A98EC64BD6BC1F4ULL, 0xB836C5A73FA6224CULL, 0xDFC2BA5FC3F7364DULL, 0xBC3D02799AA60EB0ULL
        },
        {
            0xD3B64D8A4B711798ULL, 0xFE099AFE9B152FF8ULL, 0xB4C8C5357C585908ULL, 0xD7FD05FA50530F9DULL, 
            0x290FFF4EF7270E6BULL, 0x47F1973EEE7C1970ULL, 0x35A7D05438E57A3FULL, 0xF3F5AA1672F7DEADULL, 
            0xF726D67B33EA75D1ULL, 0x68FEE592024C281DULL, 0xDF1374281021CDD7ULL, 0xFDAC598DE34766B0ULL, 
            0xEE5E1A2B7309110CULL, 0x8C5F04751A6D0000ULL, 0x84BC306864CA8012ULL, 0x6EEA8137EEE97E21ULL, 
            0xE42AC6F32F71C6B0ULL, 0x34E5DFBAE2E907C3ULL, 0xCB0757ADBF9BA806ULL, 0x42D76165E5E24B88ULL, 
            0x3707EF3FD51160E1ULL, 0x18644AC23B68BB7FULL, 0xB3ADC339A80698B8ULL, 0x39831969DA85AFA7ULL, 
            0x3F8C919FB8446FEAULL, 0xA379BE81040AC7ACULL, 0x3107555943D15E75ULL, 0x6FC3E64DFAEB7091ULL, 
            0x312165361E29115AULL, 0xA56D3C3F448012BAULL, 0x1746BDD95E86D52AULL, 0xEF66699007568DB9ULL
        },
        {
            0x417AA54B244AD5C0ULL, 0x5527234EE20256AEULL, 0x3F452BBB893242F5ULL, 0x785A30BDFBDCA27DULL, 
            0x75CD38EBF8A3C57CULL, 0x35AB9B534EB344C9ULL, 0xE1C23C4EB914117CULL, 0x872A63B1EA87671CULL, 
            0x79F912C87BEDF15FULL, 0x4EEC630308E4B8AFULL, 0x2DDEBA2A8E7D02D8ULL, 0xCDE7F2ECD0DA55D9ULL, 
            0x8E440DADE4386C6AULL, 0xB354D3080D945681ULL, 0xFA31058179660616ULL, 0x6A433C0DF3D87336ULL, 
            0xF3D4BFCF62C946A0ULL, 0xD956F4FB8E26F426ULL, 0xBFFE7982C0A6E454ULL, 0x3FBA61BB0F68ECC1ULL, 
            0xD1DF845CFC0A708FULL, 0x6BB735C84E4F4432ULL, 0x19E487462A416C4FULL, 0x4BF80A0D790A07E1ULL, 
            0xCDEE2F332161E190ULL, 0xFB397EA63C7D45E9ULL, 0x8C5E963616CDFD91ULL, 0x7C99EAE8CE584528ULL, 
            0xBBF399F61CD9D59CULL, 0x61725109D0ACA7D7ULL, 0x9AC165FD1F37437FULL, 0x02BD4F57868E3500ULL
        },
        {
            0xAE499B2362EBCC5DULL, 0xD1B9B4E3D902AF7AULL, 0xF8FC8F2B2C5C1290ULL, 0x27D7A557BECB5D6DULL, 
            0x2F2DC16637E06287ULL, 0x39B0CEAE1E56F887ULL, 0xDEE378D938612D7BULL, 0x57EA06F91AC2A868ULL, 
            0x15148CE573EBC7EEULL, 0x4A109EEE0D5A9472ULL, 0x2DC5540A33F635D9ULL, 0xB4D518C29ED99DEBULL, 
            0x8891EC68478A3F68ULL, 0x3416EFE4F25101E5ULL, 0x3B294B1190825088ULL, 0x04EEE007CA11456CULL, 
            0xA34B30236788BB4BULL, 0xC247B442AC6E7DD4ULL, 0x7F0BBBF4D105AF29ULL, 0xD38D3D56C878145EULL, 
            0x75A756A57C32881AULL, 0x29F42D91DF0C32D8ULL, 0x5EEFA706209FC22DULL, 0x05832A8DF59E4A55ULL, 
            0x1FB3E2AFF4A6969FULL, 0xBAE209297442C1CEULL, 0x5B6E74FEECFFAAEDULL, 0xE8D4110F1B1E2692ULL, 
            0xE62B6E0EDA5FD5D6ULL, 0xAD6ADF4440B4FDFAULL, 0xC3022D3E78A5CBDDULL, 0x8FFF2FA18C716492ULL
        },
        {
            0x470BAF9EBA665571ULL, 0xBD4744D29EE200ABULL, 0xD167CFE62BCFA8DBULL, 0xC657B4DCD9F67DE3ULL, 
            0xFEDF86FDD8D8C21AULL, 0x1EC3006FC0E76AE3ULL, 0xF883C61178FC3316ULL, 0x7F1760B3306D23B1ULL, 
            0x51FFD35644A2EB20ULL, 0x10C409E9DF822350ULL, 0x297C9D93E9AB0007ULL, 0xE1944D6C16A59C47ULL, 
            0x5EE8752DB4A84837ULL, 0x594E3B07F83275C7ULL, 0x240D53D62BB39E27ULL, 0x5442E7CE76A57FC0ULL, 
            0x682CB9B0AA5C1E4BULL, 0xF3478C54C5A2BDB7ULL, 0x773C9ECF7C3E3B91ULL, 0xD1AAF6BDDB29AA6FULL, 
            0xDB61E6D353541084ULL, 0x803BAB998B3DF5F2ULL, 0x36CC5D149EB59915ULL, 0x58682F6556614703ULL, 
            0x7FECE2B437D7C2B5ULL, 0x13923A095C20044FULL, 0x2CB318049F2BFC52ULL, 0x78BC7B081864EEC7ULL, 
            0xCCB2E662C78BB3A6ULL, 0xF2421C1834B99380ULL, 0xE1BDE41351B2BCA2ULL, 0xAF63F58C2AA6D048ULL
        }
    },
    {
        {
            0x9DCAA939B2261A9CULL, 0xD72E2F5030D344E0ULL, 0x17B807548810718AULL, 0xB5ECA137CE7EAFECULL, 
            0xD21F0ACD3604144AULL, 0xDF7932EEBBC4F9B7ULL, 0x90748A5584EA6C3AULL, 0x798EC688B254ED8DULL, 
            0x7444B18DFDE11280ULL, 0x0D2A61291349C905ULL, 0xF7F9079412950CBEULL, 0x7E716E904776C427ULL, 
            0xBAD20C80E8642872ULL, 0x9774D15036DF2B10ULL, 0x6390AB6947523289ULL, 0x316B6459C51C5E3CULL, 
            0x2EDEB92966682C3EULL, 0x35878BF13B73A2FBULL, 0xF5F447F9B60F6481ULL, 0x6B988A901063A147ULL, 
            0x0DA140AFBFAFE576ULL, 0x9A70A0C273AF7A99ULL, 0xD4F0D45E44DA7EC4ULL, 0x4DF3B1EFFCE546A3ULL, 
            0x4C49E42EDAFCB4C6ULL, 0x7254681BE57E5ACDULL, 0x528AA54F14E48372ULL, 0x7B422D53E33E5C0FULL, 
            0xDBB151292EDF4B0CULL, 0xCCA318F6293084D9ULL, 0xF093FB990669B4CEULL, 0xBFE33EC8ADF03E8CULL
        },
        {
            0xD2E04BA52BD84513ULL, 0xE67E33C833763BD8ULL, 0xD8F930EF49BBFFC0ULL, 0xDB3F369743115489ULL, 
            0x96C701EC18675A14ULL, 0xBDDBFFCB1915044AULL, 0x4FE6044DD88CDCC6ULL, 0xF65EF2F03CFB8FF6ULL, 
            0x971D41BE6A642D53ULL, 0x24B863368FEED970ULL, 0xCE5B6583F6D21457ULL, 0xE8572D010BFBC56CULL, 
            0x0C7F09278AFC69C1ULL, 0x8A8D8B39FA9574F2ULL, 0xC6F32845D44536FAULL, 0xF655245B81821C74ULL, 
            0x5D86BF61F4B971FCULL, 0xB0A8FB11CBFD68D3ULL, 0xFA884329F75DD845ULL, 0xAF1C1822684935F3ULL, 
            0xAD5690E8413D4568ULL, 0x8CE4D1E2625B0E62ULL, 0xE25A5B003AD24FBEULL, 0x68DED4FCFFA1A31DULL, 
            0xD7F0912D25ECFB44ULL, 0x97D8762B571BC2C8ULL, 0x29C740C88093B04EULL, 0xBA8DA0D81436B37AULL, 
            0xA9385F39E8C95C24ULL, 0xA11425B1503AD905ULL, 0x4CAD66A526C1D954ULL, 0xADD813549069410DULL
        },
        {
            0x248D39F4D792E68CULL, 0xDF5EC18364FB4567ULL, 0x52BF046C1B882B63ULL, 0xD94D6B96C410FC87ULL, 
            0xFCC2388CCF821DEDULL, 0xDC6E7D751361DADAULL, 0xAC5B39A3908866B1ULL, 0x066F1784A8BC63BEULL, 
            0xF17251595DD8CB64ULL, 0xF1D347A66075C2BDULL, 0xBEB82468280254AEULL, 0x35F0AF1AEE53AB2DULL, 
            0x90637CCF383A207EULL, 0x334ED14E6EE26BB7ULL, 0xC795CE8B6055DB08ULL, 0x29B3E037507A780AULL, 
            0xBD1160D9A371EE9EULL, 0x268CD6496BDCCE37ULL, 0x5B3D646D7254F691ULL, 0xF1D32635B1CBEFFAULL, 
            0x29618B913E0A09BBULL, 0x576432A11A4C4CEDULL, 0x8C0E628B12C6F045ULL, 0x01AA90060EC5A6A3ULL, 
            0xA85244AF2D8C184BULL, 0x4CF4B1CC99B5E680ULL, 0xD68274D44709CF4FULL, 0x7EA6015700AAD47FULL, 
            0x28D620F998B437EEULL, 0x05E34774E9B8021DULL, 0xD0848BA2396D05C9ULL, 0xB27C9AC09646336AULL
        },
        {
            0x22A58589E5A76357ULL, 0x7A5DE1B3716BA9AFULL, 0x055CA362A054FE36ULL, 0x12F746F1B0FFB7E5ULL, 
            0xC7B127A8FB6CF3E7ULL, 0xD4DB6D8DB79AB9D2ULL, 0xD8F1A0865F56A356ULL, 0x1137AE3212720451ULL, 
            0xCA06FEF291BAF674ULL, 0x1D41D45503F2D85DULL, 0xFB7EE1937E2910F9ULL, 0xB2D34391A836D284ULL, 
            0x32C4B4189F11B250ULL, 0x9A69CD184CCA84C6ULL, 0xD464CCB5EDD040E2ULL, 0x69F0CA4251A714A7ULL, 
            0xA4B5ECBD28319D7EULL, 0x80FAC82B1C5BB58DULL, 0x7719920586537ED8ULL, 0x392AF8A86FDB441CULL, 
            0x716E38CC5CA2435EULL, 0x9F5A21F6F7110A18ULL, 0x2E5C7454E526F774ULL, 0xF8315B40C9C25B93ULL, 
            0xD9C26E8611855250ULL, 0xA0FFE64B84355B6AULL, 0xF944B10D9A02D141ULL, 0x4293D14BE5BE6228ULL, 
            0xD3E01D68A49175D6ULL, 0xEBF2107237A74529ULL, 0x7E9BA361D6BE2297ULL, 0xFE8A14B43D46BA19ULL
        },
        {
            0xD3D5915625A9D639ULL, 0x57FEC8D097F67D69ULL, 0xEB520AC93D9F809AULL, 0x5C9CD0114C82635AULL, 
            0xAC4C61545D102439ULL, 0xE292E05CB4E45448ULL, 0x22711B921E02ABFFULL, 0x0077F7F738E49E50ULL, 
            0x9DA0476628F0FF00ULL, 0x54033C0DE540129FULL, 0x513667837EA874F7ULL, 0x84E0491EFE125684ULL, 
            0x318E7F7E26DB24D2ULL, 0xC83584361F2223C6ULL, 0xDC29E7FC01EABE17ULL, 0x9FC43F821EF57CC6ULL, 
            0x8B93D2A511C73E10ULL, 0xE000B45E8791EF69ULL, 0x17E8AAAD7AC3BCD6ULL, 0x3E0C98CA48BA5009ULL, 
            0x4AF1429D2E28FFAAULL, 0x91EBBFBB4E5F32A9ULL, 0xA47858C5BECD241AULL, 0x0116964F15566150ULL, 
            0xDF5963235BDC3A5FULL, 0x43E258081BB9BAF6ULL, 0x70824D5E0016EAA4ULL, 0xE5F145FE0C0EC4A9ULL, 
            0x54391BDA00784C1BULL, 0x6465BB361E291E9FULL, 0xF999273001FE9FE9ULL, 0xC2A29CB79C07001DULL
        },
        {
            0x454911605D12672AULL, 0xB4E2A026668F9392ULL, 0x4001C068B37F8B25ULL, 0xFDDD3DF8DFFFCBDCULL, 
            0x26BE3B4D95753070ULL, 0xD91AA55BBE43C980ULL, 0xADCE20E5BADF5013ULL, 0xDA1AC97C19160CE1ULL, 
            0x32A1F8B5F7A3E30DULL, 0x8BF3F94CC92AF17CULL, 0xE26E740D8E6F0843ULL, 0xD56D60D33ED21F09ULL, 
            0x1EB38F9D8321B536ULL, 0xD6CEC1399988E451ULL, 0xA547CA72FDBDCBFCULL, 0x8E89D30C7140ECA0ULL, 
            0x835A094FDCAF0BE5ULL, 0x3F9C3A9B87D3C3C9ULL, 0x65FF766F26C2B661ULL, 0xED86BE89DCB46ACDULL, 
            0x50A2199CF979A5BFULL, 0x4EE4686CDC99855DULL, 0x6A129A29A39358B0ULL, 0x4F810F38AF47C0C2ULL, 
            0xCD3049FF9BE52293ULL, 0x9F102DC766B70CC0ULL, 0xDE9346970FC847D9ULL, 0x45FC526F6AFF9A80ULL, 
            0xBBB194E2ACFA012AULL, 0x8089E21A01120EB0ULL, 0xDE52A5323DC6483AULL, 0x142127961EDC2DF8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseDConstants = {
    0xBA27BD04D0FAC176ULL,
    0x056B3B2F3143A3E4ULL,
    0x3F3C6331C986A65CULL,
    0xBA27BD04D0FAC176ULL,
    0x056B3B2F3143A3E4ULL,
    0x3F3C6331C986A65CULL,
    0xB225A7E0577E3C64ULL,
    0x8C50E98CE0CC62F4ULL,
    0x97,
    0x18,
    0xB4,
    0xA0,
    0x78,
    0x6F,
    0x95,
    0x30
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseESalts = {
    {
        {
            0x1A4E040ED3951F89ULL, 0x9D1443B4D2468032ULL, 0x369B2A9403F94138ULL, 0x7B55B9F64578B85EULL, 
            0x63D813446C2C97ECULL, 0xB8296656EA73FF63ULL, 0x61189B45D3CD0E23ULL, 0xED40EA3492ECA4CDULL, 
            0x31E7F065BB69F0DBULL, 0x5DD4EB5696DB468EULL, 0xDC283D55D32466ABULL, 0xEE835FAA2748B3BBULL, 
            0x194011460B65AA54ULL, 0x53177DA50A756C39ULL, 0x9E08DFC54EECC978ULL, 0x0D0DC2D3B948D3F9ULL, 
            0xCD19A2228645C35AULL, 0xDD49BC72209C472FULL, 0x254DF7CEDB369E1FULL, 0xAA29C2C3B5B42425ULL, 
            0x92B3CB45E3BD8F51ULL, 0xBB4C3C7440E8DC7CULL, 0x346F9092C9A265A5ULL, 0x5A655D3A1026FE3BULL, 
            0xCC1E4B6151512349ULL, 0xA3618134220A7A09ULL, 0x402D3FF02705938FULL, 0x9978BE16BB68C4CAULL, 
            0x67CB141B63E7A1D0ULL, 0x0A641049D192EF3BULL, 0xC6191AB6ABEA3B6BULL, 0xE116F02900420311ULL
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
            0xB3744DBFE0438D64ULL, 0xFB82965EC2431D82ULL, 0xC6B780629DB01D44ULL, 0xC411940ABD1C5623ULL, 
            0x9C92664F0F9568A0ULL, 0xAB77B472A0E44CEAULL, 0xEB3A8760A7FE42DDULL, 0xB246F8ECF50EFB1FULL, 
            0xEF390BEAE8CA1A2DULL, 0x4C6F6EEFD8373FD3ULL, 0x2F06CDB9986DBF27ULL, 0xE9822E6F6CC86281ULL, 
            0x450FDE658BF592A5ULL, 0x08697E32321633CCULL, 0x0BAF89BC880F2479ULL, 0x51839FBAF493F493ULL, 
            0x408D72367BAA212FULL, 0xEFD07615C06D7692ULL, 0x5B659909AD3337F3ULL, 0xB2B4C9411C032480ULL, 
            0xF2AF3D8081D0F609ULL, 0xD1D3DC2048C36C0FULL, 0x2B0E115DB77438A7ULL, 0x7485271476EBB598ULL, 
            0xE11BB38921ED8B9CULL, 0xE733C3559425EA97ULL, 0x7F0C1FF48A8514BFULL, 0x6D7BC4685C5C522BULL, 
            0x4552DC5235C5A436ULL, 0x4816E210C105E9ADULL, 0x83C62B6405ABC78BULL, 0x4F15B52EF58E5497ULL
        },
        {
            0x3726CC837D499B41ULL, 0x09A703BB43ECE22EULL, 0xDEC60EAC728159CBULL, 0x32537860B2AF1A8DULL, 
            0x1E8FE17B32C15F80ULL, 0x5A8D92FDEE51FAEDULL, 0x3E00D3BC6A6CA165ULL, 0x0A224F0FEE6FF786ULL, 
            0x2D1226F3D6AD9204ULL, 0x443BC19EF76E5A7AULL, 0x56DE063329541975ULL, 0x0C966755D4EC0146ULL, 
            0x6366ECF185E4B6C0ULL, 0x84DFC3709B34FAECULL, 0xF4588158AA62E57BULL, 0x9EF83E71B3E19958ULL, 
            0x7A9E53444E71D8C2ULL, 0xDD874BEA32595693ULL, 0x2831E7958A062BBDULL, 0x4195F8551BFA31CFULL, 
            0x77D1F1223A0CB7ADULL, 0x731828E0F2249C82ULL, 0x104595CF09AB1A49ULL, 0xBFB8C05F02FD8753ULL, 
            0x0709DE8ECCFF19FBULL, 0xFA73CCF8C6A36757ULL, 0x2A00285398A7F74DULL, 0xC15BF1D4875F5D23ULL, 
            0x4FB99935438EF103ULL, 0x1F5236946D0C8F50ULL, 0xF3538385D057AB53ULL, 0x9578F2443CBC1B01ULL
        },
        {
            0x03E0D6ECD8D4857EULL, 0x607444E34E223826ULL, 0xB4BAA790D540AF6EULL, 0x60F824D9AA42695DULL, 
            0xFA01D104513D7BAEULL, 0x495CB1A91831C400ULL, 0xC19017ACA14787ECULL, 0xD5A666B8A4D8A652ULL, 
            0x54A39C0DE180BB56ULL, 0x1742BC4D450287BEULL, 0xE1E74381B44B5242ULL, 0xAC6843B70C131AA7ULL, 
            0x53146576B0116C0FULL, 0x578B744E01D99E84ULL, 0x7D2DEABD0424C79AULL, 0x7B69067C355B26E8ULL, 
            0xD53A25DC11454250ULL, 0x015CCF5F58059C8BULL, 0x663C752474166829ULL, 0x5B14C5048C221DFCULL, 
            0x60A936D29AE6DFF3ULL, 0x942FECB7CC806977ULL, 0xC241BF174E7879D5ULL, 0xCF3A731FD44B8007ULL, 
            0x26CE05654035410DULL, 0x27E6579C88B3E5E6ULL, 0x2ED44000F8309B0EULL, 0x9C2F83E07B32DA82ULL, 
            0x9839750AF09D40E6ULL, 0xECE53981549B48C3ULL, 0x6F5F98510489FFC9ULL, 0xA1BA8B5ADAC01AD4ULL
        },
        {
            0x9D139DD3DB7AF3B8ULL, 0x7094BC3316E31C80ULL, 0xE5BC03514D41C418ULL, 0x6828635AF2FD64E2ULL, 
            0x26EB63A895C26CDAULL, 0xB195A95D19E9AAF3ULL, 0xDBA52531E88B903BULL, 0x40D4F09E6043C841ULL, 
            0xC618B3033539A61DULL, 0x85CD72E372C35DA1ULL, 0xB04CDB06B6214CCCULL, 0x927A03A44B316180ULL, 
            0xE521B212FE79F906ULL, 0xE75C12964D74B9F2ULL, 0x923ECB435757C8DDULL, 0xACD45D735E5B540CULL, 
            0xD35ED3E9410906ECULL, 0x184A3BA7E5C89CD6ULL, 0x8751FF3A8F30D07CULL, 0x2D53E0ACA19EE4A0ULL, 
            0x3BA73ACF6E47F40EULL, 0xA13DBC174751BBF8ULL, 0x6F6AB75399AD03ACULL, 0x93286094FD8A93B2ULL, 
            0xD5F13C6B36F35522ULL, 0x2EC5557ABF1689CCULL, 0x1EF9C93935CF1E9BULL, 0x1FF3D9926F8129CFULL, 
            0xAA1BD3477EEC86CFULL, 0xB6BBCB7AD43FD9A1ULL, 0x89B405F043F0CF48ULL, 0x982F59ED0100AA20ULL
        }
    },
    {
        {
            0x515737F5CC279FC6ULL, 0x7EFC2B0D0A5A4E1BULL, 0x71FA18F8CC2F749CULL, 0xC5857F7A919FD44BULL, 
            0xEAC2766DE335363AULL, 0x34079A1429EFDE26ULL, 0xA203284D668F45CCULL, 0x5565B1DB04C892AEULL, 
            0xA7F922A6B34A1D96ULL, 0x4FFF491C37832784ULL, 0x4B3B6F0E18679247ULL, 0x3A4DC3775ADE21AEULL, 
            0x0DD5C63E885CC3AAULL, 0xAE4C127288071BBBULL, 0x66A68B34480EF63BULL, 0x7982141E4CC5EAEAULL, 
            0x47A6259D86F3A3FBULL, 0x9E9A9851A6F65C67ULL, 0x7715A4C22F938A4DULL, 0x0FE086370523563CULL, 
            0xA5E6CC222364DE98ULL, 0x622308BD83A169B4ULL, 0x732F7002FBAF4A7DULL, 0x213019A1FF04736DULL, 
            0xB114EBA24BE47095ULL, 0xE367680626DD21D2ULL, 0xF0B0325C343324E6ULL, 0x26ED2987D3B169B2ULL, 
            0x0D9DDAA1CDA1EF7DULL, 0xF8A93B7CCC37B72CULL, 0x468AC27282FA72A1ULL, 0x18128C4364B774FCULL
        },
        {
            0x079DF3BEF0B3C87EULL, 0xCFFB9E2E04956F41ULL, 0x06FDF123BB1B3F2CULL, 0x7D6BC9EED3EE804CULL, 
            0xCE7B7D2B463680ABULL, 0x16F8E77627692813ULL, 0xAD59A21F3E251F7EULL, 0xD4D1792E262D285CULL, 
            0x43E0E19DD20793D5ULL, 0x89928F8A24FC780EULL, 0xD436CE07C84575A6ULL, 0xC0011F44DF9E1B7BULL, 
            0xDD78D5A04BE78EA4ULL, 0x8B3DC35E6BC5F342ULL, 0x3379F79E7E8675BCULL, 0x5EFB97F44D6E0068ULL, 
            0x334A62AD1EA3EA20ULL, 0xF29796E7FD811F3BULL, 0x6CBEB83E1379C868ULL, 0xA0EFF4A56097E3C6ULL, 
            0x45237961F5ABCDC4ULL, 0x76EF02EA2B260C18ULL, 0xCECA52003973B132ULL, 0xAEE03765F68A305AULL, 
            0xB62D678166F26E3BULL, 0x759BA937A08FE76AULL, 0x6F87B8810F484DE8ULL, 0x93FD5E271CFE44C0ULL, 
            0x488C178DDDD5476CULL, 0x9D5758CC5D1F688EULL, 0x35FE68EE886AA35BULL, 0x8BA542EB846278EBULL
        },
        {
            0x20E48E5C55000B2CULL, 0x660CB0B301BAD140ULL, 0xB069DAB4A0660F63ULL, 0x7D9C56DBE89524CEULL, 
            0x665B5604A17986BEULL, 0x1AE29D94320365EAULL, 0xF4BE8A2A5C5DB915ULL, 0x123CA68ADE6AA780ULL, 
            0x4023D40D3C8E171BULL, 0x8113C0866C81E6A9ULL, 0x1276F3BF94C2D1C4ULL, 0xFA2D1BE8EB660F52ULL, 
            0x320B9A5A7967EA73ULL, 0x4FDFB3C720E7F5A4ULL, 0x36668F9A484D7867ULL, 0x047D138E6F308423ULL, 
            0x0C3EA29D96E637E7ULL, 0x05F5E8234D6EF07AULL, 0xE02795F618C25851ULL, 0xCAEF0EB381884E2CULL, 
            0x486B557F0BD08143ULL, 0xB502CFF96E64BF9FULL, 0xFFBBF12921D3C968ULL, 0xBF9D6970BA88C30EULL, 
            0xA74ABB86A988FC76ULL, 0x3C21BCD6D3BDC67DULL, 0x2AC7DB02E2E10F1EULL, 0x4399C8AA6F8D29FFULL, 
            0x89B4609439F5D6E1ULL, 0x62B68906B0673E5AULL, 0xCB14CFEE9489D4D2ULL, 0x02564B68A786DA02ULL
        },
        {
            0x126596C84D844BABULL, 0xF576F2294C416420ULL, 0x63A091FA89D81CE4ULL, 0xFDD2A2B9F1713300ULL, 
            0x6B13655BEC495460ULL, 0x3DF4739FC632CA2EULL, 0x742D92C1EE5409B3ULL, 0xF71256F8B8F125EDULL, 
            0x6F30BF1F01FE70EFULL, 0x42FD79F9FF34E30DULL, 0x92F97D305D32EEAFULL, 0x66D6643822C87136ULL, 
            0x35B7EF5B81E04F1EULL, 0x5F45636F4A9D8EEBULL, 0x47AF5E561A4A586AULL, 0xE9CB4A548C355A19ULL, 
            0xF0DDAF69A6945BECULL, 0xD447C0DA079DDC73ULL, 0x281561C75A0E5087ULL, 0xBC8444D979D8373CULL, 
            0xB8C8D42FE033D017ULL, 0xCE1C422EC3831FC6ULL, 0x40D9C945A34A54D1ULL, 0x03C1509440440584ULL, 
            0x70769C5D3CF15092ULL, 0x5D18D07BAF82A9DDULL, 0x6C1F647C747B6DACULL, 0x844A15BFBA0EC509ULL, 
            0x35FA068EFEF601E7ULL, 0x3372D3D97E92B3D4ULL, 0x90FBE4B3E88E4E54ULL, 0x8305A61D98F9C7B0ULL
        },
        {
            0x82B5DD4A4EB66821ULL, 0xF79722A179589EFBULL, 0xF9A18463B53B8CE9ULL, 0xC86E12562B590277ULL, 
            0xE1C779936059E09AULL, 0x666AAEDE8FCFB718ULL, 0x45E70CF20CD0B01AULL, 0x2B3BB1BC284D6EEFULL, 
            0x6DD814F97804B6FFULL, 0x2FE73FE5EEA0DF6BULL, 0xAB3575DB00AEEB26ULL, 0x0B8EA3A485233AE3ULL, 
            0x8F0B106E942C7E3AULL, 0x1C86D1E8E3AC4E2FULL, 0xEA458C1EFC510B64ULL, 0x144EAF8AFD8287A3ULL, 
            0x641B5AF83194474EULL, 0x80294BB2C9B32BDAULL, 0x352B5D930C05B3DEULL, 0x4715C780B95D2E34ULL, 
            0x74D02840A51F153EULL, 0x1784674DEACB0380ULL, 0x73D0FCE6E9024169ULL, 0x4EE9E84A744A5630ULL, 
            0x079F2FA3F1EFDA8EULL, 0x1DE6CFA53DD8DBBFULL, 0xFC201B5574C3CB15ULL, 0x8FE373B94D447A55ULL, 
            0x4835EC44C5E527DBULL, 0x305715BC74E1DE61ULL, 0xD98EF0E71521D6C1ULL, 0x2A0E4BF099390C6BULL
        },
        {
            0xF424A22C616DAFBDULL, 0xE7F3F7BCD6BCC786ULL, 0xE074A80F9AD9350DULL, 0x42144C0BC8ADE81CULL, 
            0xF10572474E75283DULL, 0xC0C39EB0C771ED6CULL, 0x259C24468B10E4C0ULL, 0x7AD29398D2279DA8ULL, 
            0x3DB1A335E14E1BE0ULL, 0x9F4ECFEBE793C058ULL, 0x0841C99B3E593CD6ULL, 0xCDCF556ABF779914ULL, 
            0x9230AC62C05EE0DAULL, 0xCE7F04DA8FDCE441ULL, 0x5AFFEE3E27B3D19AULL, 0xFC6BB8881DD87E4FULL, 
            0x7D78193A7CB46BDDULL, 0xEF50010F3483B160ULL, 0x1D4F53943E005C0FULL, 0xA1251FA45487453CULL, 
            0xE2F0DE094C7042B8ULL, 0xF1C8033FE66376C4ULL, 0x3F5A681A889E4806ULL, 0xA70A1B8D1845705EULL, 
            0x9AB3EC62D45900C6ULL, 0xC2571B95484EEAD6ULL, 0xCD3BD505F2884000ULL, 0x8779D0156F3D8538ULL, 
            0x6827C91073310D97ULL, 0x865A63BF0C9F87D8ULL, 0x7DDAAE37281CF0EAULL, 0xAE23D72033D190A2ULL
        }
    },
    {
        {
            0x6A8932C84DF8721DULL, 0x8ADAEE003E2A925FULL, 0xE0FF3F89A3303DA6ULL, 0x47198C5319328D6CULL, 
            0x78DF8A1DEE4D009AULL, 0x2561BDA972C2B51FULL, 0x57CF7A1275C1BECEULL, 0x4F997705186C264DULL, 
            0x213143211B64B42BULL, 0x86F0A1DF9A138FCCULL, 0x8CBDB9A0D2728013ULL, 0xF4EACA86BD4688F0ULL, 
            0xBC0F34E48EF68340ULL, 0xCF0694126ADCCD42ULL, 0x9EFAB88846A36BD1ULL, 0xD750CD418C20FA56ULL, 
            0x2AFC6475E4F70E2EULL, 0x62F8F4AC91390206ULL, 0x163C1E313F6CA325ULL, 0x7BCA392278F17948ULL, 
            0x6F93ABA3884F864DULL, 0x149825A0E0B62956ULL, 0xC18EB42EE9B5D086ULL, 0xB4C781BF9E8FC66CULL, 
            0x104EE70F6ACB6BA3ULL, 0xBEB5185D16AB68FBULL, 0xF35FF325FDEF559BULL, 0x32C413AF51EB5CE8ULL, 
            0xB2C502FFC2E03B3FULL, 0x5FC22333BE289ED4ULL, 0x61A34CC071A8DEADULL, 0x615220DDFBC4829CULL
        },
        {
            0x33C78491CDDE323DULL, 0xF81E0E92A3223FF1ULL, 0x47BEE96368086649ULL, 0xE149206D8FDD654EULL, 
            0x81087B145011C8AFULL, 0xF76C8308E9F1262DULL, 0xE97A8A7A7B937541ULL, 0x078892985B9A0EC7ULL, 
            0x5B9B8A97EA2F34B9ULL, 0xAC83B481F34A61F3ULL, 0x6F22B27E8DEA854EULL, 0xD1D388C035244E44ULL, 
            0xD3E0ADDD27432CC4ULL, 0x52D4BF917DB1FDFBULL, 0x8F63C95CC6F6F698ULL, 0x14E91E0D500B1CACULL, 
            0x9BCCE184AB5704D6ULL, 0x5425D6F5703DB2A8ULL, 0xCEFE957504CA5371ULL, 0xEA6DEE391EFCB7B0ULL, 
            0xE6CA75AF822D65B9ULL, 0x47633C9021084037ULL, 0x5C15C5156D333FE8ULL, 0x86DDAEF377772B01ULL, 
            0x923812788E686C65ULL, 0x226E6505D3CFDFADULL, 0x5E3E06B1E372B443ULL, 0x7767D782EE8AAC09ULL, 
            0x99DB1F6637FB5231ULL, 0x41B3F7C8B04AC5AEULL, 0x103700DA74D0178BULL, 0xDA12E17169B1A604ULL
        },
        {
            0x8CB774D87F797574ULL, 0x9E1C2041491219CDULL, 0x3F49606E1C3C6395ULL, 0x44129416E5AFAFC7ULL, 
            0x0BAFEAFB707C77B4ULL, 0x4C5EE598CFCF3182ULL, 0x9DB6572A8263A0A2ULL, 0xF61104DDA41469DBULL, 
            0x9A9B69B8BE72D444ULL, 0x63244DCBC239AEE3ULL, 0xF67F0D5B3F2004F8ULL, 0x1DF66556DFBFACA7ULL, 
            0xCDEBAF80C0E6EA62ULL, 0x6A8E6B4D5965BEEAULL, 0xD0320E0A732176F3ULL, 0xB6703777F10A214AULL, 
            0x03E696C4F0C2ED8FULL, 0x57C13FA92BF50615ULL, 0x36CAC915538B68FFULL, 0x79ADAEF71A1296F8ULL, 
            0x6EE1213761B1AC60ULL, 0xA6E3B1153C22F768ULL, 0xE715677DF8EC919FULL, 0xD4CCEE719A734EF0ULL, 
            0x1670966FA92646BBULL, 0x5B4E998E979E971DULL, 0x0A40AAF0808184AEULL, 0xC2A04707A7F62330ULL, 
            0x2C3989B0775334E9ULL, 0xA3583BEECDE3B4F3ULL, 0xDBD38DB095BE16A4ULL, 0x9DC16A9AF6C32D6FULL
        },
        {
            0x1BDF7C96C36DD33FULL, 0xA0561A2EDCB1A47FULL, 0x861EBE65CC928416ULL, 0xC1936D68C463EA69ULL, 
            0x200D3D4FA3EF089AULL, 0xEDC030D6B83E00A3ULL, 0xE0EBFB49487180C5ULL, 0x23A6C8FFF3470B30ULL, 
            0xADC9D964CB369241ULL, 0x81D6C8FE9BE1EA51ULL, 0x026E78454961E513ULL, 0x17047A9775B07773ULL, 
            0x00B02652020CAA0FULL, 0xE3AEECB9D1CB7EDDULL, 0x567BE7BF87198BE6ULL, 0x638226161DA7F658ULL, 
            0xEA2D884E271AEB9FULL, 0xDD1438B45A0243D4ULL, 0x03304E9D546D6A3AULL, 0x9FC20431943008BAULL, 
            0x526A04010ACF2503ULL, 0x3581E406B49ABFBFULL, 0x448AD45A2E6B2EDCULL, 0x6ADAA0292C6D6279ULL, 
            0x7C5D8352DFBDD747ULL, 0x14AABC5F8E1AC88EULL, 0x5473E295747AF64BULL, 0x5F781BE14A1CA962ULL, 
            0xDF060A955893FCE9ULL, 0xA75123E1E6F285B7ULL, 0xCB5DF849B24F514DULL, 0x51DA2C2204AE1D51ULL
        },
        {
            0xAD8FA7856A3ABD56ULL, 0x3DD5D212EC87C195ULL, 0x1BA1E4DF620D0184ULL, 0xDF3C96C8D141D766ULL, 
            0x81DAD12539DF8EFCULL, 0xF9C11F4068D1D409ULL, 0xB77E9EA4DC359F30ULL, 0x61E6D03A54D02337ULL, 
            0x2A477F547D47C674ULL, 0x15E09034CCA39192ULL, 0x7471D656CDBF5403ULL, 0xC25A0F9B08A4B99CULL, 
            0x7151F34127049A28ULL, 0xB618FA2CD391D9ACULL, 0xABE62176F0FEFE21ULL, 0xBA455C988EDA29ECULL, 
            0xE60750ABD5A28953ULL, 0xDB2C4553C1B0EAD4ULL, 0x6F6CEAE3A0B7D782ULL, 0x6DB5B08F1E8149EAULL, 
            0x8A0CF6D4ACA3EF5AULL, 0xB758DD73AE300214ULL, 0x8E7523B68B253439ULL, 0x8A6F615FFC8FA69DULL, 
            0xDFC0BAA83369BB18ULL, 0xCE35E74B01B6E461ULL, 0x2D4889DA6C1CD70EULL, 0x22EE9430AD95F01DULL, 
            0xD41DC79E7990D13EULL, 0x2A855344296332F6ULL, 0xC67D719BE7E2701EULL, 0x7EC672D4843CDA46ULL
        },
        {
            0x01F0BA6F26DA62D8ULL, 0xA197A384D734CF6DULL, 0x370C7EB85DF76F33ULL, 0x498033E349190DB9ULL, 
            0x1A9D5D38C44FE17BULL, 0x880B4475CFDE9B16ULL, 0x9CD2E9D6EA7FCACBULL, 0x0BFEC01F6CA38BFAULL, 
            0xCFB0BE5CDB38659CULL, 0x224D046B20F8EB96ULL, 0xFC39B67A1DF00A28ULL, 0x0A431B12FE47156AULL, 
            0x2E5EDAFDE3B5C518ULL, 0x98A2DD36B967AD3AULL, 0x3B13FE74D698B426ULL, 0x245A2D44608298D4ULL, 
            0xF2F34A52481E1FBAULL, 0x9531FCBD23BC3EAEULL, 0x57916A100A5E3BA8ULL, 0xA275E5AD0ECB0BB6ULL, 
            0xCE71D085C3BDA1EEULL, 0x86B8AD699BBFE297ULL, 0x5A261E3883D21C47ULL, 0x5C9702FF6E2A6B07ULL, 
            0x9BDF39847B3D43CEULL, 0xB70AC4E83EBFA711ULL, 0x4CD2587B9261C375ULL, 0x034B05918B9A5CEAULL, 
            0x142603C726A8D5F4ULL, 0x9AB35C2020091718ULL, 0x82FB28908DD76E2FULL, 0xCA85842D66A17C04ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseEConstants = {
    0x5EE3AAC922243592ULL,
    0x1A0E996DE2500F4AULL,
    0x57923C2113293C47ULL,
    0x5EE3AAC922243592ULL,
    0x1A0E996DE2500F4AULL,
    0x57923C2113293C47ULL,
    0xCC7756D5B21F3A59ULL,
    0x41C7F53E1A727995ULL,
    0xED,
    0xDF,
    0xD7,
    0x4D,
    0x9C,
    0x67,
    0x41,
    0xFA
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseFSalts = {
    {
        {
            0x2CD3B22DD7C1BCB9ULL, 0xE3C7B99A101AFD61ULL, 0xEA02DD634F604964ULL, 0x03CF442FD5C6811CULL, 
            0x066C0CA334860E2DULL, 0x4980E780E02EBF00ULL, 0x95B7BB44B9475721ULL, 0xFFE88342FD39C3A3ULL, 
            0xC8592058AA1BAB4FULL, 0xD83D28EA24FC7CDAULL, 0xE6BFE55915AF760FULL, 0x859CD2AF16896467ULL, 
            0xA3AE13CCD5B60F94ULL, 0x13EC86CC9FBDA756ULL, 0x421F671782F68C8FULL, 0x4405C7D6C6992D9EULL, 
            0x0300DE532A000159ULL, 0xB6B1FC389E77F12AULL, 0x65F14026A41A56BAULL, 0xCC22D4F2586CB9A7ULL, 
            0xCDEAE96EC1E04066ULL, 0xBE66809FEDCF9F14ULL, 0x116B369A5021B90AULL, 0x4ED72D869FFCDA81ULL, 
            0xCCB86ADD47C8335BULL, 0x0C7FC3750EE5DBCBULL, 0x36B614FA86E75489ULL, 0x9C5790310A4E2F23ULL, 
            0x1BB1932A273F2E7AULL, 0xF5059B0A2CA4BD53ULL, 0x90DC2D6D2C68CD80ULL, 0xA6352F8663A10955ULL
        },
        {
            0xF429043A5F6D7634ULL, 0xF75924E6DC2184B5ULL, 0x6922F75CFD64AB6CULL, 0xD5E375E263DFDD0FULL, 
            0x39EC097CD5A6CDB4ULL, 0x410B42E4E8FAF846ULL, 0x1AA72552C2B8AB05ULL, 0x7E9C4E199C53F301ULL, 
            0x550E071E2BF023BAULL, 0x3674797BC464E7BAULL, 0x1CEC29546D636B63ULL, 0x45606C35C85E302CULL, 
            0x9AB38BC712637459ULL, 0x01936E790BECFFD3ULL, 0x0C51EB9B4C7986ADULL, 0x2CD253CDC82397C0ULL, 
            0x419939738991D3DBULL, 0x1745E5F6F0944F84ULL, 0xDD8B6949F153E230ULL, 0x1D6EDD1EED3B0261ULL, 
            0xEBE99890AD9A0F6DULL, 0x14F238A8106C2424ULL, 0x2B0D634F77BBFDEEULL, 0x585A2A45318738AAULL, 
            0xF2CA989F3DECE44BULL, 0x2EA331ECF9FC2CBAULL, 0x9E928B1EEE0A487AULL, 0x5E047E16985F3848ULL, 
            0xE2769F6CF91624DAULL, 0xE2651712B1BC0240ULL, 0xBE65C91D1036DDF0ULL, 0xAA54502B9E69A8ACULL
        },
        {
            0x4E8C1F83878DB667ULL, 0x18A22CC2794D88A2ULL, 0x28B7E89607579304ULL, 0x4669E3870E3B3141ULL, 
            0xC83D1AB41D2AEA07ULL, 0x5063B4359F4A4E07ULL, 0x3BBE71FE5D0B2B17ULL, 0x8035560A785AEB92ULL, 
            0x4636543DE3F4D199ULL, 0x15EF4C479325A217ULL, 0xB979FA2EE3DFBA2CULL, 0x4DAAB2C20D51F265ULL, 
            0xDC0C391B53A11C6DULL, 0x8149E232371192BDULL, 0xFCD8FA4A3DE9E6BBULL, 0xBB5EFCE8B494C8CAULL, 
            0x9121448AF5E5A854ULL, 0xF410FFAD5EBA95A1ULL, 0x9936B6D44AD02ABEULL, 0x50C52FCF3CE21850ULL, 
            0x2B831A858C616652ULL, 0x0645B678AA5B2290ULL, 0x910950E4D3C012B2ULL, 0x7D21CDEA335C16BCULL, 
            0xF42AB2CAD12F2B6CULL, 0x73DBA49B7663B25EULL, 0x837BAF8A34945185ULL, 0x06CEC458E3B752DDULL, 
            0xF6BAC6E90DFBCE7EULL, 0xBF57F4D853DEE245ULL, 0xD1ADB344B86495EBULL, 0x9093DCBF818789A9ULL
        },
        {
            0x5ADA88873CD5297DULL, 0x2C0DD23F0DBE84CCULL, 0x0AACBCF0F2D8B187ULL, 0x26835199A7F7B4A6ULL, 
            0x27A89CB7C7A96C7DULL, 0x99845F8B8E60B925ULL, 0x463F6DCCC0CEC48BULL, 0x3E9D4C4CCF5618C8ULL, 
            0x716F3CF8395CBE4BULL, 0x82FA853B3AD118BAULL, 0x7AA376F5E569F7A4ULL, 0x1AA44E91955DE453ULL, 
            0x55EBFFDAFF65EC7CULL, 0x74B48CD32999545CULL, 0x5344BB6AE16ECEC6ULL, 0x8D6CF3F0517194EEULL, 
            0xFAD93BF5B4C02850ULL, 0xE7F709A13AF1E8AFULL, 0x51389E3C07AA33C0ULL, 0xB9D1E74087C76045ULL, 
            0x77CF41E6EFD161C1ULL, 0xCA3D2EC80D1B039BULL, 0x4FFC91E9942F921BULL, 0x709ADFEDDA3D2AC5ULL, 
            0x9EFED9E77C6B51DFULL, 0xE8B8A37CDF5DC3FDULL, 0x9D25993EFB431933ULL, 0x0B9826C861EDA896ULL, 
            0xBFB79C4663EDB8B6ULL, 0x8C52EB913D9FCCE5ULL, 0x6DBAB00435692118ULL, 0x7755BC259A3280B5ULL
        },
        {
            0xEA84A1F59505F7BBULL, 0xEF240D8C751424E7ULL, 0x8374B8738F20C305ULL, 0x40C9F8A9E2F88ECAULL, 
            0x519DDDE410C91AABULL, 0xA501E278F6111BF9ULL, 0x71737979507F34F3ULL, 0x245C6482A24C442DULL, 
            0x4192AF805A8F07FFULL, 0x5BE1DA326801A473ULL, 0xD4AC6E06031B1A15ULL, 0xFC416739DDF06334ULL, 
            0x0D0261B64CB7245DULL, 0x6F31D96318255AF5ULL, 0x1D5CFC27E3D65D0AULL, 0x5A0748DAA2FC2D50ULL, 
            0xE6C6FFC811F5C95EULL, 0x9B48A3AF4F315C18ULL, 0x02A5B520947CB5F2ULL, 0xDA0E86D5D78C740BULL, 
            0x526B93ED75A878E1ULL, 0xE344BC5AD6E63864ULL, 0xF3CC6499AB71438EULL, 0x0236CADF1BA67608ULL, 
            0x9D74BDBCC3A13D6BULL, 0x08AA3230563D4409ULL, 0x55F96BAFB756C4E5ULL, 0xB474AACE32742ECBULL, 
            0xC1556A00BBBEE6B8ULL, 0xF56BD8DFC0A621D4ULL, 0x15855B3BB5B41D26ULL, 0x863F9D9008F7A9ECULL
        },
        {
            0x490C8422F8C53845ULL, 0x1ECF8A006BE8B67BULL, 0x304D28B509050560ULL, 0x78CE8DD29EDE2D60ULL, 
            0x66224ED320582A43ULL, 0x189AB7AF90F40B3AULL, 0xAFF7725C7A8CE848ULL, 0x0136DDC2FC2E674FULL, 
            0xE9BBC30B5A992AC5ULL, 0xF661C4CA10B87E3DULL, 0x29CA20FD0F1E294CULL, 0x4DEAEDC81A71C40BULL, 
            0xFA7E22EDA82FF0B7ULL, 0x598D9C5469F8B677ULL, 0x61237AF4DF269638ULL, 0x7FB348BBD1080D7BULL, 
            0x99B1980A970687AEULL, 0x4D08BCFBC085D659ULL, 0xA793BDD835E27566ULL, 0x6B18F3EC53A62E3EULL, 
            0xE8E35E3FCA836631ULL, 0xAD62C651AB5F7DC5ULL, 0xBFBF85A9CAB3D6ECULL, 0x4BBB4DC4CAB8FC85ULL, 
            0x123AFE105907E62DULL, 0x2AD64FF2B6535FFEULL, 0xD8D8C812D3C201E0ULL, 0x4DA370C71DA5B281ULL, 
            0xC6260EF9CDA21B0CULL, 0x3BA31F0BD6B66603ULL, 0x45F4811BCCA3D987ULL, 0x3BBDDF797C6F776CULL
        }
    },
    {
        {
            0x853D4AACA2A2049FULL, 0x889B28BC9CFD7D0BULL, 0x6BB83AEDA4F66183ULL, 0xABC7DC9EC0C135B0ULL, 
            0xF30AC4EE861CB387ULL, 0x5D9376D430896A14ULL, 0x21E05732206227AFULL, 0xACD12E057F36E87CULL, 
            0x31AB01B9463B8BADULL, 0x46526B8393F01BB1ULL, 0x1A3F25554B5F65B5ULL, 0xA698F4F7BF3C5580ULL, 
            0x5CA2334510F59453ULL, 0x689B0CA076F79A11ULL, 0xF2AF76BF2B329E25ULL, 0x3D65C186ED078F1BULL, 
            0x69E4E386907B5E42ULL, 0x3C3020DF28F77390ULL, 0x53B2A8A85681EC83ULL, 0x2842575375C3C4A1ULL, 
            0x7CC5A0558676D41CULL, 0x8AF36AD7E1F731A3ULL, 0x4636515B83542BE5ULL, 0x15858142B8C50A55ULL, 
            0x719B9A599FAE9837ULL, 0x07C33F746F96374AULL, 0xAA3E94CBB5334958ULL, 0x879B1B0C2EE8F191ULL, 
            0x3CC8207ACA7BB5EAULL, 0x587E699A78F92FA0ULL, 0xA6A7453F43355BF7ULL, 0x52E6DDD4677270FAULL
        },
        {
            0x68A43DA6F5DAC3EBULL, 0x35387F9AC40490B9ULL, 0x5AE99D2E419B36F3ULL, 0x27AED5F15BC521B5ULL, 
            0x11D873A08D8A365CULL, 0x9752CAE8B3E518CEULL, 0x1255445A8F4D65C5ULL, 0x1545A520ADF02F83ULL, 
            0x5CE64580829F55ECULL, 0xB8FDFAB964B5686AULL, 0x6AAD37E8C02265BCULL, 0xC6D72C9C1BF3D32DULL, 
            0xC930608EAFD2E710ULL, 0x863D4F7E963E51B3ULL, 0x46B1D8B66C3A7A4DULL, 0xEDAB2E42CC75F608ULL, 
            0x08364D3803970E68ULL, 0xCBD8D3042D38BAF5ULL, 0x4CA7D856B62E4374ULL, 0x7A59E23AEDCAE3C3ULL, 
            0xAC1921CC2CCA827AULL, 0x9A941E7FFD506474ULL, 0x75C34D27E5E56952ULL, 0xC027A70460724187ULL, 
            0x25786A6CD76377C0ULL, 0xD482BD75731D28B9ULL, 0x420D866EB5F295C6ULL, 0xAAD431A8A85E818AULL, 
            0xB08B0A3F40EB2A39ULL, 0x97C1B13C3885AA52ULL, 0x27A2639168D72F46ULL, 0x33FA3E6D27198C04ULL
        },
        {
            0x5A761AB8E1A883B2ULL, 0x76AB94A72E90CE08ULL, 0x41E76D8679E920DCULL, 0x23A015F10FD5327CULL, 
            0x5C2A57D2EF62E3C6ULL, 0x39723E3836A660B4ULL, 0xEB8C6FDEB15DF3A7ULL, 0x46D6E5F0E64D98DAULL, 
            0xA48DBFD385E653AAULL, 0x6CF4B433020CB174ULL, 0xA9FB902DDE674CF1ULL, 0x0596929A50D56672ULL, 
            0x59C4411FFC68C752ULL, 0x373676D86D08E93AULL, 0x954DCFF667864EBCULL, 0xB7ADBAC028F2977EULL, 
            0x0D45A8CD19517D18ULL, 0xC81373683287974FULL, 0x971A4CE23B4E3E03ULL, 0xCC1A020D9A715820ULL, 
            0x17F3426C39253B90ULL, 0xF1456072E59F7FB6ULL, 0x81ED9BEFFF68FCFAULL, 0x7E03E9AF59A67412ULL, 
            0x147029A795927440ULL, 0x81684B365C9541ACULL, 0xAB07352FDD1E413CULL, 0x4D994D8B14FC4A95ULL, 
            0xC9C52BF4617C6206ULL, 0x04A4092BA5B4F3E2ULL, 0xA472EEFC2905200CULL, 0xFD02FFD3AC0CBF4FULL
        },
        {
            0x3DEF0E8025CE0AE0ULL, 0x803EB8355AE50AD9ULL, 0xD0D9D37143E39205ULL, 0xFF3D904392A2CC1DULL, 
            0xFE67FFB6DDDC60E7ULL, 0x7A5A4D476DFB2ABCULL, 0xDAFBBFBCE6606B7DULL, 0xD1F665F87762ECCCULL, 
            0xA83F0E12898E4592ULL, 0x6C05CAAF9257626AULL, 0x2E46F1321B6F22CBULL, 0xF70EE17F1C9812CFULL, 
            0xFA69FA196D82FDB7ULL, 0xA33D6A75FB8B7633ULL, 0xE32234689238832FULL, 0x1760FF109CAB259CULL, 
            0xEB5177B259DC3047ULL, 0x257AAF9918408EFDULL, 0x7E59992E44F3916CULL, 0x423487CA31CB34C6ULL, 
            0xD0E7FF5898B235FEULL, 0x4DCA31FC669367D0ULL, 0x187565E3BB32B4E6ULL, 0xF749001875234388ULL, 
            0xFD9047211A4F7A7AULL, 0x9D30A8B6647FFD7AULL, 0x95C253BAC82B8340ULL, 0x9A323409447BF15EULL, 
            0x9FA2B9CD5C53EBC1ULL, 0x162AD8925C029DAEULL, 0x0A9F83D100F4242DULL, 0x41797AE239C9AD68ULL
        },
        {
            0x6AFCEAD4081D5474ULL, 0x99547D396AD98127ULL, 0x8010477D24CDA193ULL, 0xA2EA89C49AA9D9FEULL, 
            0x4D72B5F69752486BULL, 0x1DFC9DECD61C65BBULL, 0xA6C1CC362AEEEB2BULL, 0x91F1DEB012B113F2ULL, 
            0x420DEF1751017B73ULL, 0x20BF7794B0E2131DULL, 0x584B1E17410D8FECULL, 0xF8A0CC38445203CFULL, 
            0xFF939764EB6AD6EAULL, 0xB223C51014A49CA1ULL, 0x17D5971194B6B057ULL, 0xEE08100F3A26FDA4ULL, 
            0xF407EA7594A9CF44ULL, 0xA6C44ECFB4E0795AULL, 0x9CF47A72EFFF0C36ULL, 0xD21AC776E7E298C1ULL, 
            0x329290A1F0A1315DULL, 0xA50FB7FE313F6C9FULL, 0x30F7749BBF853D79ULL, 0x4742619AA613019CULL, 
            0x01D0186A5359529EULL, 0x4FBD5FA148D76B75ULL, 0x2EC6557F2A07351AULL, 0x870BA3C068E8A85CULL, 
            0x8B5AE70E6B509C54ULL, 0xB8390C483CD85B52ULL, 0x911DA0506AC608EFULL, 0x004850C6C9882FA2ULL
        },
        {
            0x822850CA385D4D65ULL, 0x7571FA244E731AA4ULL, 0xD5AC9A183FA040BFULL, 0x10D1C070ED75EC0FULL, 
            0xC17346902418AE57ULL, 0xE869B11F138E0E3AULL, 0x67BE94874DBCD8A5ULL, 0x57370D8BBBF24CDDULL, 
            0xF76CBDCC862F878FULL, 0x4E81D77808DB6B9AULL, 0x740E9DB36A4EF885ULL, 0x3047422ED832E185ULL, 
            0x355B3C34979D68E5ULL, 0xA88BA26EFE018190ULL, 0xA9B11C299E04DCB7ULL, 0x83ED8BF5D3EC377DULL, 
            0x1ACFD453A2688EF0ULL, 0x1DE688AA03C91D86ULL, 0x95C7D605A5FD8136ULL, 0x7C34AD336608FE86ULL, 
            0x978CAD376A828116ULL, 0xEB2206FC2862173BULL, 0xB489CD48ABA49C93ULL, 0x92FF479DE27BECA8ULL, 
            0x9FBDFCE84014C0C1ULL, 0xF235D5BDE9D4805DULL, 0x568503670077049DULL, 0xA1C43707E456D905ULL, 
            0x997BF1D666D64793ULL, 0x9437515F8E55CAACULL, 0x57C2E872DD649633ULL, 0x6A59A33A4EFC5C1BULL
        }
    },
    {
        {
            0xC623C392C178B8FEULL, 0x5D154799F5AA65D2ULL, 0x46CE6670FA577836ULL, 0x86BFA55DF729B855ULL, 
            0x708EC52B97F3F431ULL, 0x276D82E4B8E6EFB8ULL, 0x3EB54AC6C32931DCULL, 0xED9CF87F8B6F4459ULL, 
            0x2AC18CF89EFA45C8ULL, 0x496E8EAAFCBCF3BCULL, 0xC9460E97B556DC73ULL, 0x513AD8CE175B092DULL, 
            0xDCBCA0AD40C8F8FAULL, 0x41BF2E1BDC39C043ULL, 0x403BB3A93C633C61ULL, 0x15E0264B074BAC8EULL, 
            0xD7CC2B858A9B6471ULL, 0xDA8270B6E4093C31ULL, 0x1707C7742855E2D3ULL, 0x7A6E2BF27C3DD3DFULL, 
            0xCF8D0B296BF04CEDULL, 0xCF12442BF1393F7CULL, 0xB2784D91A6F2647DULL, 0x5C3884033B882AA1ULL, 
            0xFE23F7C096863B5BULL, 0x16A3317F6C7006A2ULL, 0x5FEA38E16BFB8086ULL, 0xDBD49B7C8CB30556ULL, 
            0x15E4B703702ADEAEULL, 0x81325A3026AE954FULL, 0xE737F6E1A4DDCB19ULL, 0xA18CD2586C4A2231ULL
        },
        {
            0xF5B94ED42CDB8088ULL, 0x7643C8051E1A7C6BULL, 0x5E8872F5AB9DF4EDULL, 0xE51D04C6BF70D3A6ULL, 
            0x6720B2B24C45968FULL, 0xF823AEA06F88550CULL, 0x0780FBD6075340F4ULL, 0x86742CF0CEEC3213ULL, 
            0xD7798ED26D38D194ULL, 0xF09DB6E82B61CDCAULL, 0x34BA6822AA8B3766ULL, 0xD86056CE262DEEAAULL, 
            0x5C3CC848D964961EULL, 0x716CB91FA15CD72CULL, 0x2A3F7FA950BAF76FULL, 0x5F083997D1D09A2FULL, 
            0x147C063DD7DC89ABULL, 0x1296F6A737997B9BULL, 0x0CA637584C46C8FCULL, 0x90BEC3FD5138871AULL, 
            0x58DF5F98005B3CC3ULL, 0x10EA8F34655D6BF1ULL, 0xD9C55AD7C1A4BC76ULL, 0xCE8885BBD408C97EULL, 
            0x7E31BABAACF345C3ULL, 0x339D6EA344E67663ULL, 0xEB983D1DA8F13D2DULL, 0x0DCF1F94E011B21FULL, 
            0xCC95AC89130D54FEULL, 0x612F407D230807DCULL, 0x992D7EBD82E9E350ULL, 0xC90638ABE83B6CE3ULL
        },
        {
            0x997B0348F29A4717ULL, 0x5FEDFC794C569D99ULL, 0x3C785D6245B1D072ULL, 0x2303360503237307ULL, 
            0x79EBEC9B87EE6B8FULL, 0xDEBFDCDC8F6C522DULL, 0x36FCABD5BB25C60FULL, 0xD23C0AC9C8686F7CULL, 
            0x952329AD89F10950ULL, 0x23BF09258CD9FB48ULL, 0x3D1133CD455341FCULL, 0xF32AD0BB988D196BULL, 
            0xFF2C355964FB486BULL, 0x68E0312FFEA7A9FAULL, 0x7813F25D862CFBD1ULL, 0x237A13E268753A0BULL, 
            0x26B83808E01C16E5ULL, 0x2875A8F43179AD5DULL, 0x45A933DC0A275DDFULL, 0x5D22402EE586AC87ULL, 
            0xB27C03F93CE21C2BULL, 0xC4B433B6ED6D4064ULL, 0x5344D95A86D6C102ULL, 0xA6B637A9D147E178ULL, 
            0x07B6FA616D740244ULL, 0x4999FF31FCB3FD87ULL, 0xF69A78EF790578DFULL, 0xD3EA3F236A9CC9F1ULL, 
            0x575CF75166C647FFULL, 0xBA37D43FD637F7D7ULL, 0x76131AF088714EE6ULL, 0xB6C13A1D46664B46ULL
        },
        {
            0x139E5917E4254FA4ULL, 0xCAE6A84DBD6AB10EULL, 0x80C9DAAD3829CFABULL, 0x43ADBAC4609F7968ULL, 
            0x235A4864FBAC544CULL, 0x442291209555E297ULL, 0xF1F8522F46D60393ULL, 0x25F2E9142ABD4141ULL, 
            0xA528E23A28E9075DULL, 0x660A5595C55339CBULL, 0xE9F5CBE2E94F1255ULL, 0xC6580A9EF155736BULL, 
            0x7468C38AFF0FC47BULL, 0x3560CE2330748B06ULL, 0xA8C00FCD3684FFA4ULL, 0x277C6BD11EECC11CULL, 
            0xB6F37674698CDD0AULL, 0x445DCBCDE95553EAULL, 0x12003AC06DF35F38ULL, 0xF144AC226F7F092EULL, 
            0x6C7095E7DD55264AULL, 0x4339617B20D3EDA8ULL, 0x539FC8DE156D75CFULL, 0xF956E1FD61ECAC23ULL, 
            0x1CF9AAF36C5677A3ULL, 0xACBF21A6780D1A0EULL, 0x49B6B204D75928B4ULL, 0x10939E3602F6341DULL, 
            0xA262801B776C1E7EULL, 0xFD43AFD58F219836ULL, 0x9B0003CE31B8271CULL, 0x73C16B87BA2BF9B9ULL
        },
        {
            0x88371E023BB8FDF6ULL, 0x65E36270C2D34243ULL, 0x76CFAC92103CA29BULL, 0x3BD6D0A8EF41C851ULL, 
            0x37C7B80B54BC9696ULL, 0x695C5F6E2C51B73BULL, 0xBB4BCD361A45E9AEULL, 0x50D84401DE92C92EULL, 
            0xC892DEAB0E6095D7ULL, 0x4F08F3D29D3199D5ULL, 0xA73814FBDDEBA4F1ULL, 0xC0867EAFD530E9E2ULL, 
            0x08A302A38582E341ULL, 0xDEDEEB5A4D00EE50ULL, 0x18C9758C7EFE035CULL, 0x4D5F1B105537C6BDULL, 
            0x0A682051C3C1C014ULL, 0xFDC12322A9B4CE2CULL, 0x75869396907FC1C2ULL, 0xE29902AE30664AD8ULL, 
            0x42C458C29568484FULL, 0xAA3B8A9B36900407ULL, 0x58B132586B4A33E2ULL, 0xA0A56610141EB024ULL, 
            0xF7DD6AE5C5DE5639ULL, 0x5206C0C10CBE9765ULL, 0xDCBABBAC6BAC308DULL, 0x85D5B9B799268E99ULL, 
            0x989908DDF53F85D3ULL, 0x7B8BA366C660D779ULL, 0xDF16D8C180FECE31ULL, 0xC79DBF0C16B819EAULL
        },
        {
            0xC9FA72BB0C8294D0ULL, 0x7E7D52DFBED24D91ULL, 0xADC05AE2F0817507ULL, 0x79421AEBD22422D6ULL, 
            0x4DF9F0E049898A3CULL, 0x326F91BE0800597EULL, 0xFFB80E88A83043FFULL, 0x9A5D266D6D8FECF4ULL, 
            0x3F61569668536B71ULL, 0xD9C6B78CA4B1138DULL, 0x110E9F3BD547B5C9ULL, 0xCAA12961535D512FULL, 
            0x3416453D53136132ULL, 0x4D356C57A54C57EBULL, 0x54B7BFA12CEC4496ULL, 0x7E75A02A7FB78628ULL, 
            0x0F29204016BCD574ULL, 0x20B6FB7958263FA4ULL, 0x025097598D069E71ULL, 0x9FE4E28EE2F81A6FULL, 
            0x48C72DA23FC68FE6ULL, 0xBEB550A3BFE24386ULL, 0x1C0F586A7E810DACULL, 0x64689DE9923DFC31ULL, 
            0x4176CFE3134A5239ULL, 0x08CA8BFC35DA3A89ULL, 0xEC4FB20DCBC7AB30ULL, 0xF33694AFB0AB9F61ULL, 
            0x11F048C74A80FB4DULL, 0xB99891A327C14021ULL, 0xBDA2222AFDBF3466ULL, 0x75CD8DFA87C004EAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseFConstants = {
    0x1A396D407BCC7A09ULL,
    0x3988C1314FA03C67ULL,
    0xAE28A569FE091AFFULL,
    0x1A396D407BCC7A09ULL,
    0x3988C1314FA03C67ULL,
    0xAE28A569FE091AFFULL,
    0xF1DEE00766F8DE21ULL,
    0xE7DA6A8730C0B487ULL,
    0xDE,
    0x30,
    0x53,
    0x2D,
    0x19,
    0x64,
    0x13,
    0x0A
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseGSalts = {
    {
        {
            0x5B5E29C7E88FDAE9ULL, 0x8042C11A09C1443FULL, 0xD724E5D9A69ABBF2ULL, 0xA79EE9B6BCC9F083ULL, 
            0x00C464757971EB94ULL, 0x5DBF21F435A42DC2ULL, 0xE9DA64CCD82982EAULL, 0x468559B240851807ULL, 
            0x277D1EE1E36C00BAULL, 0x73429AF2CD891675ULL, 0x8CAFEB41EF392489ULL, 0x2EF2A8B8A3003651ULL, 
            0x27842561E156EF1AULL, 0x3F691C8E6D447EF5ULL, 0x92B16B1CD248C507ULL, 0x81B3AE126B252619ULL, 
            0x4A0FBB4FEA3BF727ULL, 0xBA9B00E842FB8005ULL, 0x1A4106B071A4E5C9ULL, 0x78092A1E4F1ADD70ULL, 
            0x577442BCA9457700ULL, 0xEB4256AE76B6B93EULL, 0x672164229C551A0AULL, 0xAD7AD4D385706A42ULL, 
            0x64BE7997EA1D3592ULL, 0xB5A32A688AF69351ULL, 0x229B720BA44E5DF0ULL, 0xC90B417DD7C2E591ULL, 
            0xD9A5977FADD05E1CULL, 0x17B399D1EF7824E1ULL, 0xCB823273B8A1EF78ULL, 0x5865F637AD651648ULL
        },
        {
            0x4C3965718DA0F732ULL, 0xEEFB389A5ACCEDDDULL, 0xD1AB1838FF2EDBDBULL, 0xFDB919C050CBA18AULL, 
            0x4FD57F6F6CF5F630ULL, 0x19A8E162F5178DF2ULL, 0xE959F6CEEB5FBDB6ULL, 0xE5BFD12BB7D42A1FULL, 
            0x80D387A3BF0D2BB2ULL, 0x1720ADF4FBF8F7A7ULL, 0x48E3EE5A837EC4BEULL, 0xA99007F0CDCE3CC3ULL, 
            0xA2D7D1B384F86E27ULL, 0xC2DC9103DD351B4FULL, 0x09D97F149FB1F94AULL, 0x8735B46388A5CA7FULL, 
            0xE039B01C75B0339AULL, 0x1826F6B65626C563ULL, 0x75600D06E792544CULL, 0xC6F72CDF0B2D5159ULL, 
            0x8E3EB9B38D5D52C0ULL, 0xA2A90150A480E8B4ULL, 0x878EC9FB057CEE07ULL, 0xD67A635AF11DE22DULL, 
            0xA50936FC78EE016DULL, 0xD2EEAE4DD10D12FCULL, 0xCE20AE082CD49069ULL, 0xE0D9A587BC3A152BULL, 
            0x42A1FD55FC9641DBULL, 0xC2A43C5DBE395464ULL, 0x48C77E55E0533225ULL, 0x9C4A2F98EB383436ULL
        },
        {
            0xE07623E3B585AB97ULL, 0x331899A3D7565A87ULL, 0xFB590AA82B4E01C9ULL, 0x4D9F14B8A71DB4A6ULL, 
            0x4FBB60CC09EB540AULL, 0x2E5076E552871886ULL, 0x31315BCB9321A8F8ULL, 0xBDF7093A8411338EULL, 
            0xB61E9520D1724895ULL, 0xA23E7AAA0960055AULL, 0xD8CC2862DD226971ULL, 0xE1E05F60A80AD3D9ULL, 
            0x0CDDB72DD9BF6C57ULL, 0x156A0B8E3E217F20ULL, 0x55BFAF9CBBFC18AFULL, 0x714671A8B375C45EULL, 
            0xF1CC8114FDC6F1DAULL, 0x5403C56411DC4BECULL, 0x3D7212F4C82B4937ULL, 0xED97DE5945545E98ULL, 
            0xC27D5E5F95DD5EC8ULL, 0x5660E26390C3B3E7ULL, 0x801C82ADB3113B02ULL, 0x669B63AD76FC4842ULL, 
            0xD0D801816704DC4AULL, 0x31A7B8B591FFB2F0ULL, 0x81A90E70D92619ACULL, 0xEE741E19184E854FULL, 
            0x160466FD98D36146ULL, 0xD9BE23F4DD91624CULL, 0x8160EE92692ACD77ULL, 0xAC2E547F7C1C6EC4ULL
        },
        {
            0x143E0805D0A15FEAULL, 0x8564918C17A5EB40ULL, 0x0B454520B03532B2ULL, 0x23B0DFD0C10D6444ULL, 
            0xECB03732E840A7BBULL, 0x25B7121D40FEC79FULL, 0xD33A160E3F3A6DEEULL, 0x367D8B8021AF598CULL, 
            0x739E5EC8D6E2A05EULL, 0x37B198245689E28FULL, 0x4694D7DFDB084FA2ULL, 0xF45A2C133ABAED80ULL, 
            0xD156FF9F980C7E79ULL, 0x6A0F220599265135ULL, 0x38F066FC05EE0E62ULL, 0x883337355095DA7BULL, 
            0x4C43CC9D199118E9ULL, 0xE685CDA1AC421E5AULL, 0x970D24017FFCB829ULL, 0xD23BB51517DC3E46ULL, 
            0x7EA994B8E20D8C0DULL, 0x980CA0BE56AC50B9ULL, 0x326BB7C3E8BAEB93ULL, 0x54ED4C8101B940FEULL, 
            0xEEE5133AA5C08004ULL, 0xE815F3E0365F16A8ULL, 0x8E141AAA56F82277ULL, 0xC00AD5040672841CULL, 
            0x8A101E9B94637042ULL, 0xF0CED8B9015B6312ULL, 0xFE4C3ED20DD2DCF6ULL, 0xA4CE818987EC2E2DULL
        },
        {
            0xB2598E145C914DA0ULL, 0xCD5C70C4F6F09B97ULL, 0x6911AEF1906AB302ULL, 0x240A937376464BDFULL, 
            0x88CDE3362316DB7EULL, 0xEFB0C2B3423A2C84ULL, 0x077A6BBEF570067BULL, 0xD3915E74B8EAC206ULL, 
            0xAFBE938A1FB32879ULL, 0xAF1C90043CD6F510ULL, 0x7953501B18170B85ULL, 0x77866D4069E67537ULL, 
            0xB8EFD3D278CD2246ULL, 0x3058920D70DD6A05ULL, 0xA662E516EA86E34BULL, 0x033DCF2A015CFB55ULL, 
            0x3ECAB97D1B02023BULL, 0xCD20ADA8AD4B3F44ULL, 0x37ABC4423A5B6FAEULL, 0x53097C08D29D5DB0ULL, 
            0xAB72659E4BA69BDCULL, 0x41DCEB9DAD81D5A6ULL, 0xD8A12CC2BEB3DCE7ULL, 0x3FC2AC041A1169E0ULL, 
            0x168D791E996B02AFULL, 0x780F1CCCACBABD9CULL, 0xDA7F9A91A60B6414ULL, 0x15FC8EF6B8EE473BULL, 
            0xF2090913909E0658ULL, 0x2A8EB760B1B503B5ULL, 0xA9FA38943A26EAE9ULL, 0x4A01A979CF78B52DULL
        },
        {
            0xCF906DB916798FF7ULL, 0x5A7134D551EBEB72ULL, 0x9595EEBEEC655A4FULL, 0x3B27178A1B63BB7FULL, 
            0x2AC0AA6350A20834ULL, 0x7E2535A0ABA879FBULL, 0x132B4A6C36A7A8C6ULL, 0xE5EF5916363BA4A9ULL, 
            0x470DAFA5B6C9F958ULL, 0xAA0D80235F483D8CULL, 0x6162B6C82F061DC5ULL, 0x1CCC4B88C3BDE318ULL, 
            0x5199C36C51DB2967ULL, 0x6913601E725C0A1EULL, 0xBC9732BF592FCA2BULL, 0xEAC4E602AFA12D68ULL, 
            0x9E608F6BFCB43BD4ULL, 0xB61172D401F719BBULL, 0xA8ACEC63C69C05A0ULL, 0x3FDEA7C22F5786E4ULL, 
            0xC025C2F13FB2FA95ULL, 0xA68E1DFCA3BA70C0ULL, 0x0EE54D48383B16ECULL, 0xD13BB3E991FED100ULL, 
            0xBEB822A125A0B81EULL, 0x53A409F30A84A307ULL, 0x1B0D70D78BB45387ULL, 0x7BFAC094622A0DBBULL, 
            0x5715BD2024FB3BA2ULL, 0x48D227628A98F31EULL, 0xD82C630077D6449BULL, 0x7F0DCC76F45D99A0ULL
        }
    },
    {
        {
            0xF5DFD553CC5B38B7ULL, 0xF198396EF606A186ULL, 0xE59DBCE02F88F923ULL, 0x854DFFD67D8ED2E2ULL, 
            0xEA9D0E4F534B7560ULL, 0x6F890DE180274B3AULL, 0x052437147DA13D49ULL, 0xCBDE1E24459A423DULL, 
            0x48B643DC685D3301ULL, 0xE84A4B411D1E654FULL, 0xB9FB611077EDCED9ULL, 0xBD35531CA4CA33E4ULL, 
            0x02C8B03ECCE02C74ULL, 0xCAC8AFE64EE98BD4ULL, 0x44AAA7A7CD3E8271ULL, 0xC08F0B419ACCF4CAULL, 
            0x5C60A0F8E7AAD2F0ULL, 0xC37633154D8FBB71ULL, 0xF6709541625352E8ULL, 0x4F21D8FBC9CAD0E3ULL, 
            0x1A6D3FE54184B776ULL, 0xEFBD80E193189F3EULL, 0x2F0610784F710626ULL, 0xFEC7ABBE537BF663ULL, 
            0x65BE8EB642399DECULL, 0x40691231F2CDFB41ULL, 0x3D1D8A8EB28CDAA3ULL, 0x966C614C16C666DEULL, 
            0x733B293023DBD330ULL, 0x3F6CE51C2EEC0D7CULL, 0x03410C76C3ACB607ULL, 0x1BEDDE1DDF58F6C5ULL
        },
        {
            0xED00448CECAC94A2ULL, 0x30C2A91357C63AFAULL, 0x8B128A5DD3073718ULL, 0x8CE3A71FE301817FULL, 
            0x51CAFBE702792FABULL, 0x9AC16C89AAF45200ULL, 0xFD84C6BF1D30D8D2ULL, 0x2DCE2474BED29145ULL, 
            0x466D7E2C7B051531ULL, 0x5AB2C73C5635F02FULL, 0x91FC5032F46F8C60ULL, 0xF0611C20F55B0B0BULL, 
            0xC15EEE4827389AE2ULL, 0xF55C47CD77F226D2ULL, 0xB611AF8FF580C985ULL, 0xE39BA4AB28C54CFFULL, 
            0x01046EE330C80492ULL, 0x9B1D916B82650794ULL, 0xC666370FB8388E41ULL, 0x15F6901B7DC22156ULL, 
            0x847B601DB43AF43EULL, 0xC2AEDDA1E64F18C4ULL, 0x5F35EA7DDB0C3CBCULL, 0x3E3D5B9EBD9C005EULL, 
            0x33FF8E8F8E2C45EDULL, 0xAB08ACA8AF072032ULL, 0x872725A248562DF4ULL, 0xEAD90776D16E22D2ULL, 
            0xB5402F3C21850316ULL, 0x0AA473EC660F4D81ULL, 0xCBFEC51DC1135165ULL, 0x2A837574743327CFULL
        },
        {
            0x85799CCA9F386199ULL, 0xE244A6B3D6DC6187ULL, 0x8F249DC91AF971A4ULL, 0x505D099983107057ULL, 
            0x04D748D85957E485ULL, 0x300BA24E2253BBA1ULL, 0xF16B8B6DFF41E8F8ULL, 0x604A30771FE75E52ULL, 
            0x5F5CE419906B06ADULL, 0x72376F0C8FCE8096ULL, 0xA43B2EC27AFE433AULL, 0xFC78F3C3F02C6246ULL, 
            0xB81E909B714487CDULL, 0xEFFA9788A8F6B1B7ULL, 0xA066313F85296A0CULL, 0x35CA1192985F743DULL, 
            0x2FB5A9CFC5D81587ULL, 0x2153230E29B71E8EULL, 0x97FD1FCBC69F677FULL, 0x0FDEFF790B8E127BULL, 
            0xBE24306D51EABEF8ULL, 0x9B739BA7741097A6ULL, 0xF2A881B459144322ULL, 0xD53DEE7A7653A066ULL, 
            0x21314CC14ADDE07BULL, 0x6388C751AB195DAAULL, 0x108EE31A39C94DA6ULL, 0x0D67BE926F0051A6ULL, 
            0x43E2362705B156BBULL, 0xA267B8F357202363ULL, 0xF6F7FE81000A27C3ULL, 0xC18FC860110DA274ULL
        },
        {
            0x1442B00BA773E7ECULL, 0xAB50E5B5B0E026BDULL, 0x2A1B95113678F045ULL, 0xC2643780BE8F1B57ULL, 
            0x6BAAE106071CB6BFULL, 0x419F13CC02583960ULL, 0xAFB76C11BFD38CDCULL, 0xC886F972F72E7C20ULL, 
            0x62108EB4CE04098EULL, 0xA678D5675A58376FULL, 0xD953CFAB8CEC792AULL, 0x2BC5C1C6CB3E9A0FULL, 
            0x514744D319A7BD76ULL, 0x0C3D615866A2447CULL, 0x7A83D576F5517E63ULL, 0xDC32248083C70A76ULL, 
            0xE4A2BA453793A9DCULL, 0x785213806F2D1ABCULL, 0x01EEF0DCD70F9E53ULL, 0x172D078C7189413FULL, 
            0x4C31E631313E4E82ULL, 0x0199CE31A6FD064EULL, 0x055222F8479F92F7ULL, 0xE4D51A4B301C2F0DULL, 
            0x2A5E2468C0AE2B72ULL, 0x0BE359938F8A3A54ULL, 0xADFACB6870DF9354ULL, 0x18A443BD086E9599ULL, 
            0x541CBD7C15061FC7ULL, 0x1E9917F433F71397ULL, 0x94BC1A916BAD044BULL, 0x2AFFC74496B70158ULL
        },
        {
            0x1E2024FAF84A5CCEULL, 0x6F27852D9D1DF9C1ULL, 0xB0E6CE0286D0516EULL, 0x1C0E99C84DC28D64ULL, 
            0x9F766B7A7E7EFB4AULL, 0x4CE3066CAB7903D6ULL, 0x62CDE8DC515E6976ULL, 0x5F914DD7E770C38FULL, 
            0xCB518F16CB682EADULL, 0xE08AA9B82CB0B4E2ULL, 0x5A93965D66BAA35FULL, 0x17AE09D5FED375B9ULL, 
            0x3C510084FBFAEAEAULL, 0xB978CCB086EA9164ULL, 0x84DD6385345AB6A4ULL, 0x6AF0ACFA01B5B519ULL, 
            0x4646F928CEB00F6AULL, 0x7B6F5FDE1241CBDFULL, 0xD104F60AFE4E1699ULL, 0x15D892F9F2D065BEULL, 
            0x6979267A7C4124A0ULL, 0xF585D0AC84C49DFAULL, 0xBF7AF4B8F5B034DFULL, 0xBCFBA1C3347F7738ULL, 
            0x10AB9B44CE3080FCULL, 0x1741D38356ACB37AULL, 0xCEB9893ED138F3F6ULL, 0x35E1CC439DA772C2ULL, 
            0x8DDFD609A7996D2CULL, 0xF03FA2AB141733BAULL, 0x7742102AF155D0D2ULL, 0xDDC148BF32548667ULL
        },
        {
            0xDD3BACA11D3D3D4BULL, 0x58CE933662C0897FULL, 0x164BB1363D3B1FC4ULL, 0xD3AA8FF23C2C7E0FULL, 
            0x8F328BF80464CCD2ULL, 0x24AF6E6D2ED2E9F6ULL, 0x825A9C838F4F2C5AULL, 0x2D038FEC358ECDDDULL, 
            0xF002D6F83566128CULL, 0xCA0CCA1B5D3CE225ULL, 0xB1288015B63165A9ULL, 0x7E0B416FD7C07849ULL, 
            0x3A2059C9EF0C8A43ULL, 0x4174E49354A6A200ULL, 0x1A67E0FA4157F20DULL, 0x10DA19985B690E75ULL, 
            0xDB8C94BAD81ABAAEULL, 0x0E72BE7677B314E3ULL, 0xA5443A4F30258555ULL, 0x2EE480E0CF0F2C81ULL, 
            0xCE6763FE53017593ULL, 0x7325936E4A572A32ULL, 0x917887FEC0CDBA04ULL, 0x9F8A86646B0850F9ULL, 
            0xA16935BCFF8F210BULL, 0x6395F25F7C993485ULL, 0x0F32E5F81F84FD1AULL, 0xD41BAA024CD65683ULL, 
            0x0EC24A5FB41F6175ULL, 0x561085295BD271A1ULL, 0xBE64B8B41236DAA4ULL, 0xB4B3C9282E6AA1A0ULL
        }
    },
    {
        {
            0xE286EA42A87EB8BFULL, 0x81D9435FFCA99F73ULL, 0x14AD39CA0A913946ULL, 0x122495F83E3D2FA5ULL, 
            0x14B0E5D4E94A38D6ULL, 0x03CFF73721121B93ULL, 0x1081391AA58D36C9ULL, 0xA9F2B3BD5474E3B2ULL, 
            0x9DEB8455F6C13CD0ULL, 0xE5BC9B78E357FEF1ULL, 0x648E1ECD4D5815A3ULL, 0xD491521C3C744BB8ULL, 
            0xE34B4682CA52237DULL, 0xF28A05B411F53D0BULL, 0x4F0C946B9305A704ULL, 0x506BFEBB1111DE25ULL, 
            0x4ADDC655A5BD4D94ULL, 0x07862F5D8521FAE9ULL, 0xC29A5FC0FEE9C4DCULL, 0x7AD4D28E2AE51B05ULL, 
            0x6E1A41D46B770701ULL, 0x21E5ED8F302C339DULL, 0x42E841E336A5E3D5ULL, 0xB91F786436467B5EULL, 
            0x971507821A5DA7FEULL, 0x82CC97845D536491ULL, 0x9CB3947D39179E41ULL, 0xE92EC44C5E2585BBULL, 
            0xD5265AFB0485833AULL, 0xD778DB3C1CE42A0FULL, 0x6436AE9FDC6F9E85ULL, 0x635BD83228D6E1D8ULL
        },
        {
            0x60C710F224A8A118ULL, 0xC9E9F9CB9A1801E2ULL, 0x61A4B77964851600ULL, 0x74F7EE2CE0010A5EULL, 
            0x73CD8B76FBB3724EULL, 0xE404F02177157026ULL, 0x4CD7DA69FDC1E36CULL, 0x5C3BCE8D4EA208F2ULL, 
            0xE68E3BFC6C1DFE34ULL, 0x9B6DD55E8F7F2A63ULL, 0xB72133FEF4667E14ULL, 0xA7FFF6A127605F76ULL, 
            0xD3C78C9929EDB177ULL, 0xBC75FE29AB9EA3C0ULL, 0xD6DD6E62F4D31C02ULL, 0xCF539999AF785B97ULL, 
            0x8993A34C3B62574DULL, 0xC751B9686C4305F4ULL, 0x47144E8657F6F137ULL, 0x77699EFCF35681FEULL, 
            0xFC5090E3FBFF93C4ULL, 0x2BB6581143EAE047ULL, 0x507E398DBC9000CFULL, 0x338DB784AB3077B2ULL, 
            0x199A0D2F77041CACULL, 0xF205CD3DDDEF0F20ULL, 0x99281F0C06E73D6FULL, 0x1D90249C7F639CB8ULL, 
            0x0A2FA23D8A987252ULL, 0x601AA2416B7F5274ULL, 0x2D53EFC7E7213F20ULL, 0xBCDC5B272F632E59ULL
        },
        {
            0x63FC1DB79492B5A6ULL, 0x1B77E6467F2B043FULL, 0x4053DDCFC6749919ULL, 0x1979E9B28F366DD8ULL, 
            0x5470EDEAC4EC5A49ULL, 0x977CFE655C35E211ULL, 0xEBA6EAA550CBFDCAULL, 0x128BA0B7AF6EE9FBULL, 
            0x87B96EEA11C0749BULL, 0x24BE347D8E4BA782ULL, 0xD4700681D0D87052ULL, 0x3423A3AFDBE92621ULL, 
            0xF8FDF29C88FC7C51ULL, 0xA727C0CC54B0780EULL, 0x2F4B4C3D83929B4FULL, 0xE6F8F03F4FD90FDFULL, 
            0xC45C4903C4168164ULL, 0xC673AE8A4448AC08ULL, 0xD5869385D6D5058DULL, 0x81CC96E625CE0E5EULL, 
            0x1961EF9A3B79E810ULL, 0x848D0FC82A95FDC8ULL, 0xA67EA8FEB9AAAE59ULL, 0xC7FB8EAE63BF0B22ULL, 
            0xA8A2800263DEA971ULL, 0xFF3261BB6072D523ULL, 0xFCC74B8BD0B34127ULL, 0xC9EC4A6CC963BB2AULL, 
            0x67B25ED1A60CF018ULL, 0xF02A10D9B744B867ULL, 0x0B551DD76DECC589ULL, 0x4A2D5692283304E2ULL
        },
        {
            0xA54F70295766C835ULL, 0xF2178BB55282885DULL, 0xBB4CB937F5459C59ULL, 0x2C142CA5B79E0EEDULL, 
            0x32548EA28EE39495ULL, 0x66905CBC2B75CB03ULL, 0x4F7DE169D6B0E916ULL, 0x83B2CF580EFC604AULL, 
            0xD72B54FAA73AD00DULL, 0xF2DB9DBA741AA353ULL, 0xF281443B01A1F5D5ULL, 0x5FD4BF63694E7696ULL, 
            0x762CC0418966969AULL, 0xA1234829DFDB7BF0ULL, 0xCA729D5BB4147D76ULL, 0x31AD476FC31E5042ULL, 
            0x7BAA2EE7FB6C9FE8ULL, 0xF5260B1AD3CB3F7BULL, 0x0DF94599B1C57DE8ULL, 0x68FD75D61BE96B75ULL, 
            0x1777E476A9630788ULL, 0xD54D7AE03ED2A9BFULL, 0xF1FB0912C73D05F5ULL, 0xCF4CC1D0D4A5DE32ULL, 
            0xC7C3984A7FE5C9CCULL, 0xC75274A020DD2478ULL, 0x096900B7BA830829ULL, 0x63D2E7995A2E5322ULL, 
            0x3F210D8374B86FB9ULL, 0xC5D4871EF365268BULL, 0x454323DE796CE277ULL, 0x091C136D9D5D7007ULL
        },
        {
            0xD50203E892ACD59FULL, 0x72A431982ABFEF81ULL, 0xDA0E21211B9231B9ULL, 0x74D1A756660A6C3DULL, 
            0xBECAB68B753089D2ULL, 0xCDDEA13BE57F40EEULL, 0x92FD658B7D966810ULL, 0x0CA99E983FD1C00FULL, 
            0x11111AAC8D6626F3ULL, 0xD8942E9FE8410AB8ULL, 0xABCCDBDDFC522DBCULL, 0xF7105F7411936557ULL, 
            0xC2A365514A71AE4FULL, 0x3ACB51727A9E11EDULL, 0x6D9AB143ED2E3E41ULL, 0xEAF26915BFF6D2CCULL, 
            0xB59312E19273ED0CULL, 0x105701C5064BD759ULL, 0xB347F4575A510DCBULL, 0xF88FFD0DC43F608DULL, 
            0x6315AA4857BB97EAULL, 0x7F24714561818782ULL, 0x4374539349EA7273ULL, 0xD4C7AA0FD41DC92AULL, 
            0xB29B82793C65583CULL, 0x84C4E3FCDA904406ULL, 0x6292E4EE58628B80ULL, 0x7BC599E0ABB4CCACULL, 
            0xF0203C992BA7EA2BULL, 0x8DB1B8E4FBE3743CULL, 0x8F767BF2BB0C09C8ULL, 0x6DD79022C9A86953ULL
        },
        {
            0xA975F296FA244323ULL, 0xC23C12377AACAF7BULL, 0x54F29D193ACD7461ULL, 0xCC640E55E173EEB7ULL, 
            0x352A0CD645507497ULL, 0x8E117B867F07CB39ULL, 0xAFFBBBA77BD381D4ULL, 0x2175C563927518B8ULL, 
            0x52AC985939A0A214ULL, 0x70525589D12FF4E9ULL, 0x29021679A86E5CEFULL, 0x60B2DAC640A50520ULL, 
            0x6302A33536DF0E54ULL, 0xE197EC7BBE62F431ULL, 0xBC38A64DB7482758ULL, 0x54EF4465E77069B5ULL, 
            0x487F6C6F0FFB84DBULL, 0x1E30479D19A793DCULL, 0xC708C375FEA3AF5AULL, 0x5DAD21A23CC62028ULL, 
            0xD3DCF78CE8A23616ULL, 0xA4BC1805CF70DA6AULL, 0xFBB874D15A8987D4ULL, 0x8543030B4C91BE34ULL, 
            0x57333DBC7436C73BULL, 0xE6BD75E7E6E5B8C9ULL, 0x5B891CC9E2D3D296ULL, 0xB9163E02BE9178E8ULL, 
            0xD95A637216A5FBF0ULL, 0x1189F773C18957BAULL, 0x6F0361B2FA727331ULL, 0xEB40A276DFB74A0CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseGConstants = {
    0x2289DFAD9EC901ACULL,
    0xC6A129EA79068ADFULL,
    0x9D2CD1462E6A8E87ULL,
    0x2289DFAD9EC901ACULL,
    0xC6A129EA79068ADFULL,
    0x9D2CD1462E6A8E87ULL,
    0x0580DE754AE8EAB0ULL,
    0x9922CA9CCA5A93C4ULL,
    0xB7,
    0x99,
    0x12,
    0xEF,
    0xD3,
    0x01,
    0x01,
    0xBA
};

const TwistDomainSaltSet TwistExpander_Saiph::kPhaseHSalts = {
    {
        {
            0x7175E2E519BFC111ULL, 0xB1898BCA5B057D8DULL, 0x44A7D702CA1AC894ULL, 0xB8C8818DBE801251ULL, 
            0x1D379A5421CAB0CEULL, 0x4C0A30A17F772556ULL, 0x8F947F8C1424BD20ULL, 0x2A3B7CB5F5C470D9ULL, 
            0x62DBDDD7092DAC19ULL, 0xC249360C23B7770DULL, 0xDF554B39B1ADDB77ULL, 0x0A8DFC888F7CCDCCULL, 
            0xCA25FF26BCB37FD1ULL, 0xE577A42176DDCD77ULL, 0xB4119AC2F99D381EULL, 0x46D283946E78D260ULL, 
            0x3CC7F8C0786D1B73ULL, 0xE8EFA266AAF5B1F8ULL, 0xF1A680E395696759ULL, 0xAAE60368189E84A9ULL, 
            0x078958C1043C3744ULL, 0x338DD8F48CBC5A8FULL, 0x83D63168BB397BC8ULL, 0x1E297FBAA07C3663ULL, 
            0x9D1284201C0A6BEBULL, 0xA19A1A30D9B91A2FULL, 0x71AA11FC4388C92DULL, 0x8D7699A3C90AE7A8ULL, 
            0xF6A32C786462936DULL, 0xB21F9715EDA783D8ULL, 0x3A86F71E81328F80ULL, 0x6BE0764C725B6E27ULL
        },
        {
            0x2DFE6F66B4655E71ULL, 0x0EA44E6C8C6C0627ULL, 0x073A9C84AC2EE59CULL, 0x3A2E03CCEE635F55ULL, 
            0x3E7D194B3D16C6F4ULL, 0x170618AC6E656990ULL, 0x6C05D23957DB501EULL, 0x192B0112FDA82B89ULL, 
            0x309E9FF3A57040E7ULL, 0x4C9EFD19282F0658ULL, 0xD61F1F6AEA85BA2EULL, 0xEECADBE93FA104FDULL, 
            0xFFFB96698946F8EBULL, 0x675475A94FE8115EULL, 0xC1CCF747C8BAF024ULL, 0x851C1BC39A08EF57ULL, 
            0x1BB221E8BE7BF224ULL, 0x28FA23576D5988C2ULL, 0x4E87ED7C14E7BD0AULL, 0x376057F9DF63B2CFULL, 
            0xB98977FAC2894C81ULL, 0x9250E5367A3A5A80ULL, 0x2658CEF71C5D6D15ULL, 0xEF26643FCBC23103ULL, 
            0x3B75C2641757487BULL, 0x576408ABCA7771D4ULL, 0xEA7EAB529C0D742FULL, 0x0B1CD756CD8C53B3ULL, 
            0x9B079C460B302357ULL, 0x1BF44FD15CE36A6EULL, 0xCF6EF8C97C551852ULL, 0xF025724F58A3C3C4ULL
        },
        {
            0x52106DE38896827CULL, 0x7DAC043573EA7A5AULL, 0xBDE95C0AF8C8CF27ULL, 0x0F7A4BA04A39B0E8ULL, 
            0x447BB09795F99144ULL, 0xFD4C4E87A5FD2D5FULL, 0xD44BEBC3A3ACC937ULL, 0xEAB5BF8F3B2B8F23ULL, 
            0x8D6753E2E993D012ULL, 0x56FC2943A5FCEB7AULL, 0x310B623AD0F855FDULL, 0x82832F6218283A5FULL, 
            0x5A428D17ACCFC272ULL, 0x65B735AC16CBB5A0ULL, 0x17CA51ED9F82CE13ULL, 0xB42B5D80ED425AB7ULL, 
            0xC97031D9D5D903B3ULL, 0x62C88ABE97243FCAULL, 0x59AE2487A5A55F36ULL, 0xF674B1410A8AF09CULL, 
            0xE928C2007CF0AD25ULL, 0x611FD35D17CEAA45ULL, 0x76C6A5DBDD7DECDCULL, 0x20F4F33B768EF682ULL, 
            0xBE935ECDCF700269ULL, 0x937D7ABFFE7AE20EULL, 0xE21195AA0360A8D5ULL, 0xF8998363AE479BEDULL, 
            0xF9598849CAE6438CULL, 0x6B5DA630AE779AFDULL, 0x72F04215FE2F2C41ULL, 0x7A34548D3A038F24ULL
        },
        {
            0x63F4E68EFE681D4CULL, 0x88FF5D8FCC36BA4AULL, 0xC205DD2AA01C4456ULL, 0xB9830A77D7BC4D32ULL, 
            0x448D6C4E7D52B5B4ULL, 0xEC883021E1F418DFULL, 0x7ADC31ED891A6CC8ULL, 0x70ED981903A28261ULL, 
            0xDEE45A0C61160E85ULL, 0xC4B14078758529D3ULL, 0x5193A33DF4F0AF74ULL, 0xACE047994E1E84FEULL, 
            0xBA2CC3A5780E14A3ULL, 0x438E96ADBEB39127ULL, 0x313B4498C3FAC3E6ULL, 0xBBE205B5DE57E95FULL, 
            0x84847093CA8753EDULL, 0xF859F64004519A19ULL, 0xDB7AFDE8CF13C71AULL, 0xCBCCE53A7957BA8FULL, 
            0x5FBD668EAF59E36FULL, 0x527A32E0C56E1425ULL, 0x7487D1E9DEC63769ULL, 0xE3603C98C3D0069BULL, 
            0x4858AF69E6D48FF8ULL, 0x9E38FE6C058031A8ULL, 0x72FBBDE05207849CULL, 0x4A41C2F333EA3FDAULL, 
            0xCF0E29D18630E351ULL, 0x92C45F64FE9AF688ULL, 0xD72672CB743664BCULL, 0xEA23D9416F94DA06ULL
        },
        {
            0x07F9AD2342EE4D7DULL, 0x15B1F37312CF3D97ULL, 0x88F7CE003E6CA642ULL, 0xBF467218F5046D40ULL, 
            0x04716BFC06C46749ULL, 0x7CA7FD55C1CA6EBDULL, 0x8C8ABE57D78510E6ULL, 0x07246ACF9BB43ED3ULL, 
            0xA2D53EA96604C24AULL, 0x975E7C6ED24804CFULL, 0x1B2AB5E7DD6F07F9ULL, 0x01631820FDC82772ULL, 
            0xB397E8FB4DB17F53ULL, 0xEC76980A17FA962FULL, 0x4FA8665107F8A66EULL, 0x1C93778FB7795D72ULL, 
            0x18345EDAABB672C5ULL, 0x3FC4999A5BD91570ULL, 0x2F70E80773D69389ULL, 0xE39CF30D0C02C6B2ULL, 
            0xBC87D508769AC4BFULL, 0xEDDA3879EFFE8B43ULL, 0x4A1E98CEF3ABF94BULL, 0xB3FFB3E18DF943B8ULL, 
            0xD14A2D13AAE27ECAULL, 0x85515A25ED1E0B81ULL, 0xEF5A6C0B9EBCB419ULL, 0xB9D2C0BC2FB7140DULL, 
            0xBB2524E138569E20ULL, 0xC65E37472BF837CAULL, 0xA0838DC5475A62B4ULL, 0x99F8FAAB8DA213FAULL
        },
        {
            0xCF2A6C2D063756ECULL, 0x188B1B42EFF3B597ULL, 0x9590A39AB6FD1D30ULL, 0x6E07FA7622B285C4ULL, 
            0x1C4DBF9E8ED4D0C5ULL, 0x72BAC2F975913FE0ULL, 0x1F8C2CAA36010D5FULL, 0xA07B01C89145137BULL, 
            0xDD4D6A923703147EULL, 0x3427D482D6C75E4CULL, 0xF1F17AC4CCCECEADULL, 0x71E3434F228E425CULL, 
            0x0AF545AC1D12A4F7ULL, 0x4AFE3B68D585A291ULL, 0x22F399D98D8CCE38ULL, 0x897A26F0BB50A694ULL, 
            0x0773688AA2B6B475ULL, 0xD1FAE09A53E1F181ULL, 0x13864FE56677DFA9ULL, 0x8CBC72C0F59E6310ULL, 
            0x55292D442185AD6CULL, 0xFB9F855181B645F8ULL, 0x3FD2574FCDEBCEB9ULL, 0x3BC273BDEB2CBA49ULL, 
            0x47DF1C705198EB45ULL, 0x592FA17F9E6963A3ULL, 0x6BA9BA9722A0C11EULL, 0xC7EA426172FFFEB5ULL, 
            0xFD5F19A9CFED1514ULL, 0xB24E850E073F1C54ULL, 0xA536B0F7EE4249C7ULL, 0x587E648D80E6408FULL
        }
    },
    {
        {
            0x7304803EB50F2FAFULL, 0xA3F5605262AF79D3ULL, 0x0EB21A662ECAF471ULL, 0x1B194D15B5E972DAULL, 
            0x9E913E1F5E6BBEC9ULL, 0xA139C633B648F9C1ULL, 0xC48A4F57F7A3A429ULL, 0xBFF9EB4BB4E8CDD3ULL, 
            0x7F2CEEA400F014D9ULL, 0xB72CEB07CC956BC9ULL, 0x6C510726918BC135ULL, 0x99E37695CA16537CULL, 
            0x9BC09830C1ABECA7ULL, 0xF0762810DF6BB6DBULL, 0x1EDADF2F241E8E43ULL, 0xB746D48D87883000ULL, 
            0x9D05DED285DC0A98ULL, 0x17E4D85452A7542EULL, 0xD3D08E509C3469C1ULL, 0xD6FAC7772CEBEEC9ULL, 
            0x49B40158072A8EE1ULL, 0x09E077E3E8D1E986ULL, 0xD3F3B566C6ED8BCDULL, 0x2700E4EA42CA5F49ULL, 
            0x0538BFD4C3E75BA7ULL, 0xA9F47C28938B4E86ULL, 0x14B34A8C46225015ULL, 0xEAF42B1F048C6778ULL, 
            0x5001EB3CF6012A57ULL, 0xD119548C933E160BULL, 0x7CD720586131C26EULL, 0x22F1F6971ACECC3CULL
        },
        {
            0xCE27CAB613693CFFULL, 0x471B8BD76E54FEF2ULL, 0xD1D8152C0081D9A8ULL, 0x3E596E702AAFC65FULL, 
            0xCCAD082C8FEDE0E3ULL, 0xE40B1ED4CDB6798CULL, 0x40179934584BEE5AULL, 0x6F12D3885EBEAEEDULL, 
            0x9AD86EB8FEB76CB2ULL, 0x09A33C6EB305C22DULL, 0xEBE282DAB632B1EEULL, 0x0E86A7EB923DE68BULL, 
            0xFF5F7FDEB0A1B835ULL, 0xE027436D3F2AD99CULL, 0xAEBA274056058C60ULL, 0xF5AE7CD67D1B9063ULL, 
            0x4B0AA9C8EF019D46ULL, 0x4CAFEE634EC7D043ULL, 0x1F230A6F7DC0103DULL, 0x548B7BACE6D03FE8ULL, 
            0x36438AB3AC71E878ULL, 0x437F4B8A1D66F8F6ULL, 0x81E07D44AE4D99E9ULL, 0x04B4A8F5C9C0D6FCULL, 
            0xC3C1B6FF8826952DULL, 0x53424CB3D1E453F2ULL, 0xD86F293BCB60B0B0ULL, 0x1ECC55421FF439D4ULL, 
            0x45FA61E0B3E6AD48ULL, 0x213743AF5B670FD2ULL, 0x0C9FEC85E9BD2A02ULL, 0x912CFB0E9EC87337ULL
        },
        {
            0x80E3C2A1D52A3240ULL, 0x3AD77CC2CEB67E66ULL, 0xBCE8B7D4693EDA15ULL, 0xDD024F8E75EF4F58ULL, 
            0x651EC0D98922C45DULL, 0xD4C72C7FAA46A01AULL, 0x51C9A5E8E60C66F1ULL, 0x82DB479ED15FD4F5ULL, 
            0xBF69F3A950CDEA33ULL, 0x322B5D2A372CF4FDULL, 0x7CF114F801AB564CULL, 0xD6C042346A2DF184ULL, 
            0xEB80D3C4573BDECDULL, 0x8E533E644BBC1B87ULL, 0xB5062C28443FC15EULL, 0xC018EF0FC45D380FULL, 
            0x37F03B256FA7F373ULL, 0xA6A2C055B752F4FFULL, 0xC7A7D6F76B950199ULL, 0xBF8F68F43CF07AD2ULL, 
            0x0899E7503A485D0FULL, 0x0A33D0B6202DC410ULL, 0x8C2973CD9DC327E1ULL, 0xB33797A4D3F9EE8AULL, 
            0xDAFE986900ACA356ULL, 0x48110C894404A064ULL, 0xB7DF8348C72606C7ULL, 0xABA7DB59517C4470ULL, 
            0xB5B3820C2E9E0E1AULL, 0x52A24093C335FDEAULL, 0xA57A1B8F1D570C40ULL, 0xFB91078FDB95CB74ULL
        },
        {
            0x27A364A2DC39F815ULL, 0xFF9BF7DA27A4B482ULL, 0xF2A9FE6830E270EBULL, 0x17AAF269342971A9ULL, 
            0xA61F2C889C53A5EEULL, 0x28310595F742CF31ULL, 0x2886B18AABFDF063ULL, 0x44E2375BD33510E8ULL, 
            0x97FD713058508B39ULL, 0x674033A72909C081ULL, 0x0D0181F82B3C96E2ULL, 0xAC7818226E0D51E0ULL, 
            0x643FFF6CC335C668ULL, 0x5F8940B4E30ABD0DULL, 0x345DA023554085B4ULL, 0xA2E16D78AAF203B9ULL, 
            0x7448F53907D44ED2ULL, 0xB3004FD95443289CULL, 0x97790A10DA2904D1ULL, 0x63FD7F1C4D12772CULL, 
            0x1147FA2DB065EACFULL, 0xA18BAD668EF03047ULL, 0x4AC09F7BFBA3D3D9ULL, 0x9985A1AADF45DB6FULL, 
            0xD50CE281A745EDBBULL, 0x07905E59BA7AD7C1ULL, 0x9C0399D4932C63A1ULL, 0xB11A1EBAE72C7150ULL, 
            0x3220DEAC38467BC6ULL, 0x03BAF8FE5D6698C3ULL, 0xCF56F55F6E292C47ULL, 0x0F08B1509083485EULL
        },
        {
            0xFB721F9D58C1D76DULL, 0x54A4729F591AE309ULL, 0x13E24336908425C2ULL, 0xBB20813683776EADULL, 
            0x83E931067E8FC325ULL, 0x733E3181884D8754ULL, 0xF3DFE35DA9F34818ULL, 0x5CD5728008464F81ULL, 
            0xE2C36CE085830FCBULL, 0xB8B1D38CB1B2ACE9ULL, 0x01364E429EAD626FULL, 0xEE968E20FDAB380BULL, 
            0x3742C133C06797C5ULL, 0xE2274E3E38E31002ULL, 0xC315A6970C405CF0ULL, 0xDAC5BD5AD25C462AULL, 
            0xC5595BFD67964EF4ULL, 0xDE7F9B3206BCCF31ULL, 0x162D0443BB5FF80DULL, 0xE0FA7CACEB266F2AULL, 
            0x73D1B2A0655972EBULL, 0x22443DFA3868BB37ULL, 0x5338C884CB7152E4ULL, 0x83E0222C9688CF36ULL, 
            0xC3A4CFF5D723BA75ULL, 0xC0A2FE7A432D072FULL, 0x51FAB6B7DC25CE87ULL, 0xE647816A0560F1F8ULL, 
            0x565931CE04ECAF14ULL, 0x713EC2D9350DB40EULL, 0x168C9EF17F45D806ULL, 0xC91E5F0976981DC9ULL
        },
        {
            0xCC21F4DDE61EB2A8ULL, 0x01B371BF348C0B6FULL, 0x30DFD8B0D31DA1C1ULL, 0x5EF47D298CC4FA30ULL, 
            0xDC46D2479F2818D2ULL, 0x2260C3FB498C0F31ULL, 0xCA768883F4D05024ULL, 0x5D112A557BF3D2DAULL, 
            0x95638F245B66E408ULL, 0xEA610EE0C18FEAF7ULL, 0xFCCB3CDEB62641E8ULL, 0x4FA036583307B5B8ULL, 
            0xCD8FEF8D1D00D624ULL, 0xA80133354704F063ULL, 0x1665CBF06D7AA652ULL, 0xD5A633F0EF8D85FAULL, 
            0xCC8F5DF079A1B5D4ULL, 0x508E16AF19FB0890ULL, 0xE4A5AF68FF0D421BULL, 0xFDB1BBD9B94514FBULL, 
            0x6914A22B7B0D0C2BULL, 0x6B886F4C602520B1ULL, 0xF1B9924BBC26E8F8ULL, 0x18EEFBC91A3EBF3DULL, 
            0x529A1B2E9C31B418ULL, 0x23AFFB3FFE8C4795ULL, 0x939393CC3D00BD29ULL, 0xA90D79D5EFDDE4E6ULL, 
            0x472E2BC5E4062D9EULL, 0xF86A587CA82726B7ULL, 0x81771677F57A102EULL, 0xB2558AAF81484E77ULL
        }
    },
    {
        {
            0x16A5AF207FDAFFB7ULL, 0xBB6A0BF8614F9E2DULL, 0xAA479B225514AD3DULL, 0xBB91A598E4F3C65BULL, 
            0x4D89E03464CC921FULL, 0xD4A72672832F550EULL, 0x0D682B7DDD112FDAULL, 0x230DEEA878F63F73ULL, 
            0x39B97177E9565C76ULL, 0x790882503A9BC0A9ULL, 0xA384D7847B341019ULL, 0x279FD89DF14AC527ULL, 
            0x351A2191BF1CC0FCULL, 0xF8F334364FB76261ULL, 0xA4522B080829D63FULL, 0x563CDD08EF5990CBULL, 
            0xEF15C7ACA2D5BE72ULL, 0x32AEEC036A8634A6ULL, 0xBC3285134060DFA5ULL, 0xD5CF04A2A7AF66E5ULL, 
            0xD1B4A2FE6279E631ULL, 0x49AD39461B7019A4ULL, 0x5C1360FB88EFFBAFULL, 0x1757311F7441F84EULL, 
            0xCFA6ED20A618C3C3ULL, 0xA428E666CEBD8D5BULL, 0xB968C610F8DBE6B6ULL, 0x5355CD48AE682182ULL, 
            0x8FEECD11B990C716ULL, 0x39D86EEE129CCF00ULL, 0x22CFA3AF957B0F0AULL, 0xCAA6D547B4B62ECCULL
        },
        {
            0xE4FD77A2D069C3B9ULL, 0x70AC83528ECA0F0CULL, 0x99982E9B464D9063ULL, 0xB3C9252A838E6187ULL, 
            0xF0B00EE419525F21ULL, 0x58AF2E26D82652ADULL, 0x83CA30E272371F99ULL, 0x46B3736095DE2B7DULL, 
            0xBD9AB5FCFAAAECA2ULL, 0xE273B95FDDDE09CBULL, 0x91D0DC440DC06C55ULL, 0x8B4195DC7F682DFEULL, 
            0xA573E58414DEC251ULL, 0x35479B9C72C00D16ULL, 0x0F9EA4CE30E460CCULL, 0x3215CB946BA3E2D1ULL, 
            0x2F9E9EA7E5E7EA85ULL, 0xA150405D2315E0AEULL, 0x6496A0B8799F55A2ULL, 0x07C5D631C97211DCULL, 
            0x87D1B4459EBC5212ULL, 0x292C6397CCE9CA72ULL, 0x9B216A05DBE1808BULL, 0x92CDBBAE4C24E49AULL, 
            0x4C9F6D0F8B99EC3CULL, 0xF7BA2D89CFC5F69DULL, 0xC2E4BCE3C99EE54DULL, 0xE8DC04F566C2A219ULL, 
            0xA83374FDE978EAA3ULL, 0x3CF1BA7BB120D134ULL, 0x9161774F91B72DA5ULL, 0x26E4CF25F6B77500ULL
        },
        {
            0x41AA078B151784AAULL, 0x0A0FDE6D36A13BE4ULL, 0x745B65DAF6FE76E9ULL, 0xA35C45B1F4108566ULL, 
            0xA8782BFCB8740C80ULL, 0x725B262ACD8B4CF1ULL, 0xA9DAB2C00ED64B4CULL, 0xA4BF77A90345D197ULL, 
            0x1CC25B9F4D3F2D80ULL, 0x406C83D8568B704BULL, 0x02D0B8E889BE567DULL, 0xF0DAEB32C8B4BF2CULL, 
            0xCDD991C75708DD39ULL, 0x6A6CCB5DD487BF01ULL, 0x1E8D2735FEAE35A4ULL, 0x4957427E59C0F843ULL, 
            0x4B37BF2C1B81B1F2ULL, 0x60771A9A6DBA5D58ULL, 0x58D0E487AB54FF98ULL, 0x8AF8CF0A483382A7ULL, 
            0x0A15BE93ECC5CB4AULL, 0x0C14B3FE0764E64AULL, 0xDCBF498AA417D1E9ULL, 0xB3D889664D4F305DULL, 
            0x2CB89DAE374EFAA0ULL, 0x4340E6D2F91442CDULL, 0x89269405FD78B132ULL, 0x4E6F45B3C2A0F32CULL, 
            0x89DA2D64BEB7D88EULL, 0xC455E3D18CE638CDULL, 0x987247C766249B71ULL, 0xCD000DC5CB401890ULL
        },
        {
            0x1C9ECB58BC3AB3C2ULL, 0xA013621B54C84869ULL, 0x094578B716624177ULL, 0x3342158683017522ULL, 
            0x81D7A32D45B8D190ULL, 0xCB812DB24F8A035BULL, 0xB6BE8128002B71CBULL, 0xA819B5617AF1728DULL, 
            0xD801B351D910C315ULL, 0x0D1220B0ED12DBB0ULL, 0x132E982E0123F590ULL, 0x51F2367F3B2F5E9FULL, 
            0xBD8ACBB6534DEEFAULL, 0x28B9C90D9C55C7B0ULL, 0xDC7DB8A9D5FD5BD3ULL, 0xF287CD499855B053ULL, 
            0xAD228B214075ABD0ULL, 0xF8F8AAA6BF58B53DULL, 0x471BD65096631D4EULL, 0xF4963A657494CF25ULL, 
            0x85D7BD5274B55C1AULL, 0xE80BF376C9676ED5ULL, 0x5679661D99B14493ULL, 0xFC2A177D6559AC9CULL, 
            0x7DDF12905E6FE208ULL, 0xC5449F2C0A4C6F68ULL, 0x445D8307BAC4DC1CULL, 0x041E15F6982A0EFFULL, 
            0x5D868173DF454A1EULL, 0x1DD48450B4EFE6CEULL, 0x50D7DC19ACB4AC91ULL, 0xB0A5CFCC323FCEF5ULL
        },
        {
            0xB98A8771D7B689FBULL, 0x7F2388290D00B736ULL, 0x6A9986B81CB83150ULL, 0x1F5A4E44841FDF53ULL, 
            0x9FFA71EE7748D3B0ULL, 0x60F8DB0D6B4C029CULL, 0xE5F7A211B5756500ULL, 0x1603228BA8B8361DULL, 
            0x6DED21E86A7127CCULL, 0x00A0EF409AD2F101ULL, 0xF5EF1E1F5B33BD89ULL, 0xFD183046905E18B0ULL, 
            0x5C0D20965FF32D33ULL, 0x5AC17B79C2E0E5E1ULL, 0x15E0B9034AC70BE7ULL, 0x083789D10B6426BFULL, 
            0xDB92A575850EF319ULL, 0x4FE5EAB72F150FF6ULL, 0x0D60D058EBBF58CBULL, 0xB131999167C88C71ULL, 
            0xA93BF2188E57EF5BULL, 0xDF415DE33A9BFA75ULL, 0xA28143FC460FC945ULL, 0x37B84C13F9E9C005ULL, 
            0x2077A24753A01511ULL, 0x798068BBCEAA32BAULL, 0x29A9255A7B37E771ULL, 0x3A2BA9A9EEA04547ULL, 
            0xA474BAB0C25BD448ULL, 0x574E51386DC3E7B9ULL, 0x64839A8CC9157A23ULL, 0x3479FF3E67D18142ULL
        },
        {
            0xFB42AC9D68710125ULL, 0xD9939F67DA7F55AEULL, 0x08EC6E5359C99221ULL, 0x7EA5259ABBA7A4F0ULL, 
            0x6DF96D844BE73CA3ULL, 0xE6ECE3DF543FA5CDULL, 0x4E1C2E182D0B294FULL, 0x914CEA53C92E153CULL, 
            0xE3AC626E3D3EB29EULL, 0xE608F05D4F32F21DULL, 0x0CEB68A183C9D659ULL, 0xC929A148576A0254ULL, 
            0xE293701C7F7A632BULL, 0x52BEC13183A35B86ULL, 0x9C23461F6A0D6027ULL, 0x12AE5724F6CDD5EDULL, 
            0x17B1AC6D6D711770ULL, 0x5750B605FCDDFCC7ULL, 0xC6F725286D6F9984ULL, 0x87767D9C32992290ULL, 
            0x755143D1D60AE791ULL, 0x9332A866167BA5F6ULL, 0x69D1445806748066ULL, 0xE83E985C3B833371ULL, 
            0x597920E06A1F8ED3ULL, 0x10DDAA019A4EF1B8ULL, 0x22B4CB820694BDC7ULL, 0xF1843E18EA426AFCULL, 
            0xFEE566638686AB5DULL, 0x6404AA66045EEAEEULL, 0x73DD20D271BC6CC6ULL, 0x08D6FE60BFABD1BAULL
        }
    }
};

const TwistDomainConstants TwistExpander_Saiph::kPhaseHConstants = {
    0x930DA42CAE67D3B1ULL,
    0x4EB35B1CB0717D6FULL,
    0x28CC4F09A24340E0ULL,
    0x930DA42CAE67D3B1ULL,
    0x4EB35B1CB0717D6FULL,
    0x28CC4F09A24340E0ULL,
    0xCCCF193553835FB0ULL,
    0x45BDAA7DBF0DBB40ULL,
    0x2C,
    0xA3,
    0x20,
    0x81,
    0x16,
    0x54,
    0xAD,
    0x57
};

