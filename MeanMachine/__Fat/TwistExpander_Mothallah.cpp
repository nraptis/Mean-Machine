#include "TwistExpander_Mothallah.hpp"
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

TwistExpander_Mothallah::TwistExpander_Mothallah()
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

void TwistExpander_Mothallah::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xF0AC976F986B8216ULL; std::uint64_t aIngress = 0xD59C8C072F35379BULL; std::uint64_t aCarry = 0xA70142AB0C7B0F2BULL;

    std::uint64_t aWandererA = 0xABBDE3620BC0E879ULL; std::uint64_t aWandererB = 0xA9475855C68817F8ULL; std::uint64_t aWandererC = 0x80D9CFC86969C7E1ULL; std::uint64_t aWandererD = 0xD891FA91531A778AULL;
    std::uint64_t aWandererE = 0xCAC8ECB749477212ULL; std::uint64_t aWandererF = 0x880E37690F93BEA5ULL; std::uint64_t aWandererG = 0xB79A86AC1EF308E7ULL; std::uint64_t aWandererH = 0x8B8EE741355AA4D5ULL;
    std::uint64_t aWandererI = 0xE7BC3442A35509D5ULL; std::uint64_t aWandererJ = 0xCE31EA0EBB8C0E7EULL; std::uint64_t aWandererK = 0xA6298A6FC0F6F761ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13713284980643380081U;
        aCarry = 16560068685938944354U;
        aWandererA = 9554908521866475406U;
        aWandererB = 9924033810978241669U;
        aWandererC = 15981506286811478898U;
        aWandererD = 12267339662939839037U;
        aWandererE = 15552512462660353671U;
        aWandererF = 14513245092829748399U;
        aWandererG = 12669331661321636271U;
        aWandererH = 16356741230031974298U;
        aWandererI = 15041894218504834612U;
        aWandererJ = 15179489322001445039U;
        aWandererK = 10406683204135905510U;
    TwistExpander_Mothallah_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mothallah::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD8E4791A5DD2B2C5ULL; std::uint64_t aIngress = 0xCA649213407BA59BULL; std::uint64_t aCarry = 0x9F6F1EDDBF23093AULL;

    std::uint64_t aWandererA = 0x8F3A316EFF472310ULL; std::uint64_t aWandererB = 0xDD34E5477D616FBEULL; std::uint64_t aWandererC = 0xDDC7C7CF257B0B32ULL; std::uint64_t aWandererD = 0x8ED2FDD04FE6B1E3ULL;
    std::uint64_t aWandererE = 0xED93B0D9A78492FEULL; std::uint64_t aWandererF = 0xBCB7783D4547F56BULL; std::uint64_t aWandererG = 0xE06159EC81CE5C6EULL; std::uint64_t aWandererH = 0x9B5BB62DF65FB1A4ULL;
    std::uint64_t aWandererI = 0xC19B52919DB80A11ULL; std::uint64_t aWandererJ = 0xCFF31A588F521D9CULL; std::uint64_t aWandererK = 0x8E1B353E0CE113D9ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9419904550896159279U;
        aCarry = 12667667998242509179U;
        aWandererA = 13023979332477438090U;
        aWandererB = 10704739327145286372U;
        aWandererC = 11246296163202521380U;
        aWandererD = 9364017294719594940U;
        aWandererE = 16521478785456660565U;
        aWandererF = 13130119929648333901U;
        aWandererG = 14942184423702895207U;
        aWandererH = 17838177452754029729U;
        aWandererI = 13790675047739558214U;
        aWandererJ = 9784473683975327308U;
        aWandererK = 13484125328006311436U;
    TwistExpander_Mothallah_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mothallah::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xC304DFDD91AC379DULL;
    std::uint64_t aIngress = 0xC4837F012A6E0689ULL;
    std::uint64_t aCarry = 0xF0D1A35AFA7B908AULL;

    std::uint64_t aWandererA = 0xBAA3AC52020D55F4ULL;
    std::uint64_t aWandererB = 0xAD843B29F6160EE0ULL;
    std::uint64_t aWandererC = 0xDAF639D10093C968ULL;
    std::uint64_t aWandererD = 0xB17B44EA5C65D147ULL;
    std::uint64_t aWandererE = 0xADFDA9A169969143ULL;
    std::uint64_t aWandererF = 0xBFD9A2B9CAAC6012ULL;
    std::uint64_t aWandererG = 0xE1D721207E222C5BULL;
    std::uint64_t aWandererH = 0xB25301226D6831B2ULL;
    std::uint64_t aWandererI = 0xD78AFDA4FC25CA79ULL;
    std::uint64_t aWandererJ = 0x8ACD75D18BACC38BULL;
    std::uint64_t aWandererK = 0x9767365EE1D779AFULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
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
    TwistExpander_Mothallah_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgD;
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
    TwistExpander_Mothallah_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mothallah_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 22 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1794 / 1984 (90.42%)
// Total distance from earlier candidates: 38044
void TwistExpander_Mothallah::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2032U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 225U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 573U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 208U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 478U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1495U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 616U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 664U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 583U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 653U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 41U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 350U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 207U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1965U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 79U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2030U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1268U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 160U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 899U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1987U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 994U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1314U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 156U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 326U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1033U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1137U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1265U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1005U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1139U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 908U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 937U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 909U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1722U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 979U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 590U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1109U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 955U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2019U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1234U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1607U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 736U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 738U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1177U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 309U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 406U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1977U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 840U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 227U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 447U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1145U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1409U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 451U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1996U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 476U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 536U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 284U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 659U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1704U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 674U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 556U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1312U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1343U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1432U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1857U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1473U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 574U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 22U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1734U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1854U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 388U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1418U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1388U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1342U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 231U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 468U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1340U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 644U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1890U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1043U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1789U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1439U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 17U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 124U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 578U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1730U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1310U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1068U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1838U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1765U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1834U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1943U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 671U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1929U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1917U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1973U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 278U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1098U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1111U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1328U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1581U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 949U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1001U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1038U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 336U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 40U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 144U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1602U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1240U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 340U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1526U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 200U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 370U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 732U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1552U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1575U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 402U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1238U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1513U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1697U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 761U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 985U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 6U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1376U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2006U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 83U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 88U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 752U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Mothallah::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xFB9108CA3827D377ULL; std::uint64_t aIngress = 0xCB4CDCD20E452B33ULL; std::uint64_t aCarry = 0xD585C64F4E480911ULL;

    std::uint64_t aWandererA = 0xFCA855F05C5B213EULL; std::uint64_t aWandererB = 0xB2F5897793AD2889ULL; std::uint64_t aWandererC = 0x88C3E801878D60C9ULL; std::uint64_t aWandererD = 0xA5246952877F12DAULL;
    std::uint64_t aWandererE = 0xF0DDA2E1B08C5AA5ULL; std::uint64_t aWandererF = 0x9F02A7879E32BD0AULL; std::uint64_t aWandererG = 0xA9FF5BC5BFDF4608ULL; std::uint64_t aWandererH = 0x9DA6564C172FBB04ULL;
    std::uint64_t aWandererI = 0xBC279FD5FA0FD150ULL; std::uint64_t aWandererJ = 0xBBC110D7490F23B5ULL; std::uint64_t aWandererK = 0xC2CA70172F4C4B25ULL;

    // [seed]
        aPrevious = 13639831655984099117U;
        aCarry = 10099241955706940262U;
        aWandererA = 15929884671369667006U;
        aWandererB = 16515928871658083115U;
        aWandererC = 18052019758287538739U;
        aWandererD = 14495495938776924483U;
        aWandererE = 15051773699751762678U;
        aWandererF = 15052710498798999019U;
        aWandererG = 12527878936337717825U;
        aWandererH = 10306937593347751112U;
        aWandererI = 16800186121372422051U;
        aWandererJ = 14642796940884766075U;
        aWandererK = 18047224333146838277U;
    TwistExpander_Mothallah_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Mothallah_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Mothallah_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mothallah_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 22 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11389; nearest pair: 472 / 674
void TwistExpander_Mothallah::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1311U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5849U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1842U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5531U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6890U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6561U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3965U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2359U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 150U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2954U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 887U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 628U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3686U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2499U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7543U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7680U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 310U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1832U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1418U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 19U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1858U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1611U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 583U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 813U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2010U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 343U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 740U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1535U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1118U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 112U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2040U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 180U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1718U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1084U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 773U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 108U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 22 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11397; nearest pair: 457 / 674
void TwistExpander_Mothallah::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1093U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 688U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 109U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4339U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4166U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1973U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1951U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7607U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7943U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3294U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6961U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3967U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6978U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6799U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3516U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7162U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 623U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2014U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1832U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 240U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1120U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 356U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1265U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 447U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 417U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1478U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 555U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 456U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 622U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 41U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 396U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 50U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 35U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 923U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1044U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1068U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseASalts = {
    {
        {
            0xF00F0F4334D76F84ULL, 0x1AE835D7876D100BULL, 0xCCC38F8E40C43D8EULL, 0x1E69935E2FD3C725ULL, 
            0x64FE023F16A4C754ULL, 0x3A8D6509EA907CE0ULL, 0xCE88DF17BAABCF4CULL, 0x8A025D2F2C28BE7EULL, 
            0xA86D9A76DE12884FULL, 0xA46FD36002C5A6D0ULL, 0xBE3087DDDB1B749FULL, 0xB3F6C8D64EADD777ULL, 
            0xB98E80E9E03F158DULL, 0xF32112BE700AEB6DULL, 0x043CFA0573B73FA1ULL, 0x7F9D6802F5003C02ULL, 
            0xD0BD888FB8500095ULL, 0x11E7BE8A26FD39A6ULL, 0x02382BE40A1A9929ULL, 0x50B617EAE193D70AULL, 
            0xD21E2198B1E75B3EULL, 0xA061C804D8410F98ULL, 0x75AB1B660C863AE0ULL, 0x3CE7D1131AF4F448ULL, 
            0xD9392AE63625B92BULL, 0xD91A0B18153C66E4ULL, 0xFEBAB6CF80116369ULL, 0x4DF5ACABF312FFC6ULL, 
            0x1EA34AE5B0D9C7A0ULL, 0x45221A041C075F85ULL, 0x83BAFEF23FC119F3ULL, 0x63FD75DB443E1150ULL
        },
        {
            0x4B1DD78FB67D49E2ULL, 0xEE62820C61E766E9ULL, 0x3F1BAC301E6A25ABULL, 0x6007BB03A7472A65ULL, 
            0x9281F88CFCFD99C7ULL, 0xF9FC6816A8029684ULL, 0x0B1D6BC6320E99DBULL, 0x76E5CBB2F1915738ULL, 
            0x718C0678314229E3ULL, 0x862F337EF8DA64ABULL, 0x65B07D01F05D6342ULL, 0x0FF1635157D80407ULL, 
            0xE90B102D148776FCULL, 0x735C2BF6BA0A25EFULL, 0xF79EB879BFEEEFDCULL, 0xB1957F3C70E8844DULL, 
            0xF2CD8CD5DD5DA9F8ULL, 0x9E6DC520252731B7ULL, 0xDEA724DD22873380ULL, 0xC067FE5031FFFB45ULL, 
            0x516C78CF193D8F3BULL, 0x80FEBE21E870CD85ULL, 0x79F639B0FE6EE7D2ULL, 0x29462133AD79FBB8ULL, 
            0x32948042458DBA2CULL, 0xAF2E779829F92180ULL, 0xA57693F410EA486FULL, 0x2C4A9E3EE52E48F2ULL, 
            0xA5F4EB31B7CB0BC0ULL, 0xF41E146CA1289B99ULL, 0x71DDAE8B388A6E46ULL, 0x48239AE96E703001ULL
        },
        {
            0x4ED87BEDA36E29EDULL, 0xC552421650008D55ULL, 0x96260EFC85C43F87ULL, 0x7463466A6DCC968CULL, 
            0xF2ECEC0A25FB052AULL, 0xFB1A6B81561FB97BULL, 0x75B382E7FA00BCBFULL, 0x2C7D5BAB797A4318ULL, 
            0xCEB23F6FEFC5EB83ULL, 0x4EECA622D54E788AULL, 0xB210B692C7BF1A78ULL, 0x16294F5FD4E0C7C3ULL, 
            0x980E2A462E5F9714ULL, 0x7ABEE7604775CA1FULL, 0x639E7DF6EF06DD99ULL, 0x61A572F72DECA1A8ULL, 
            0x904BEF2AC428A7AAULL, 0xFADE6144F15B8F9EULL, 0xA4948C3DBD030A07ULL, 0x9BDA7CB90979D4C3ULL, 
            0x9A8870B6EDE39201ULL, 0x48ABEF12AE7A8730ULL, 0x52FBDB0B76BDEF22ULL, 0xA5F11CAE721574E3ULL, 
            0x53145F0053F36C0FULL, 0x637313A2575FD823ULL, 0xA619D80FAD68AF2CULL, 0xA05BCA39C04B26D9ULL, 
            0x4200B804E5E12EE5ULL, 0xE941F450DFA791DFULL, 0xD8FF56B0BCB2B469ULL, 0xE2958E51EDA24DE2ULL
        },
        {
            0xA6B515B01073508BULL, 0x911B96EEC125458BULL, 0xE35ADDE3AAFD56E6ULL, 0x74AD4C814AD86945ULL, 
            0x4C8B06D1D1AD4025ULL, 0xE702662348195CF0ULL, 0x684A6096B4FACBEEULL, 0x23C422EAF33D9623ULL, 
            0x6AE1F021F444EBDBULL, 0x67699C5292BFD58CULL, 0x98BA3485E97F8B92ULL, 0x83931081B063255FULL, 
            0x3064E017DD77EB74ULL, 0x75ABEB7535D05F88ULL, 0x81048DBB5A0876CBULL, 0x5BFB8FDAC1EB4B8CULL, 
            0x6C2C213FEC843050ULL, 0xF40D0542FF8917C8ULL, 0xFD26B3AB7C09C725ULL, 0x2EC24144A70C39E0ULL, 
            0xFE73259E5095F1FBULL, 0x7C3C5D45B5BAE45EULL, 0x9EEB93A27D0B9A21ULL, 0x6E5602C6C4B73DDEULL, 
            0x3BB568C373407A49ULL, 0xCE61FC1342006FA6ULL, 0x7350A314704FBF2BULL, 0x169C24A4A93DDD2CULL, 
            0xB60D01123AB51716ULL, 0xD60B9F8B104AE39CULL, 0xD2B7392AF80E3C70ULL, 0x2F170AACFC1B7757ULL
        },
        {
            0xFDA8C5B2FF3E3E8EULL, 0x6D4406FD68FE06CDULL, 0xD68BFF77CE4DD6FDULL, 0xDEE0B8C0E992113EULL, 
            0xE40C2A723170E3CEULL, 0x3AD10A4B642EEFF9ULL, 0x2212BAE5533C0624ULL, 0x09362DD833D14263ULL, 
            0x2494178E1238890EULL, 0x161E8F7B38C7ECCEULL, 0x2EC862B115AFC778ULL, 0x9B70C64041B4A80FULL, 
            0x161DD72CF2BFC5D7ULL, 0xACB9D22B5AC1E059ULL, 0xDACEC29183F6726DULL, 0x538E3A907EB6B712ULL, 
            0xB55ED5AF29542F2AULL, 0x141A7C991005E098ULL, 0xC67BB2AA111A87F6ULL, 0x3EC3011D86B25336ULL, 
            0x8B58A234B5E4A1C4ULL, 0xF8C7F0AA19863D61ULL, 0x3B4559AB110AF6CAULL, 0xA7E7AA35066314DDULL, 
            0x4615F8B80FB6900AULL, 0xD28157865C4FBE72ULL, 0x57E2F65317431C05ULL, 0x930509F72774E744ULL, 
            0x1B6BA0305850AA9CULL, 0x1FD0A7181535293DULL, 0xC9C0C903967EDCA9ULL, 0x783C4EB598A02DA2ULL
        },
        {
            0xCBCC56502FC077F8ULL, 0x69A0D1EEF81F1FD3ULL, 0xF072F6B6BC1C9286ULL, 0xC31E2F93CA9FF842ULL, 
            0x963E03D5EB2F678DULL, 0xA50ED0CFF7753D4AULL, 0xF234805CB8C6D58BULL, 0x071680FBBFB47EA2ULL, 
            0xD8EC695C48821862ULL, 0x60271C13E529704AULL, 0x3205240E4D3B81E0ULL, 0x010F2865A60FE78AULL, 
            0x7627AF4286018348ULL, 0x6E7A9B8C75FD4C7AULL, 0xD7DE2488A37D6EB0ULL, 0x05EECB9CB64FC909ULL, 
            0x45E7286B6861DCDDULL, 0x830555FBFA1A8314ULL, 0xCB897B86F2CB9ED4ULL, 0x9B088A29D4C11A96ULL, 
            0xCF8F3554977A66E5ULL, 0x83CEF6F850E75FA6ULL, 0xF9D883EE74C44831ULL, 0xF978470F296EF652ULL, 
            0x8639805B4C1EC360ULL, 0x0277FDFB8CF45924ULL, 0xEEDAABDB1B985CEAULL, 0xA22A6A748478B4DDULL, 
            0x605C6463C1DE92F7ULL, 0x466153840A74D67FULL, 0x97CC10B4C7FA3D9CULL, 0x4906BCEC32725E67ULL
        }
    },
    {
        {
            0x83E15BB9E8849BD6ULL, 0xEC95BE1854C03E90ULL, 0xD855FAD7F97D475FULL, 0x76044FAA66D5E1A8ULL, 
            0xC6264049401116C3ULL, 0xE10B04915D5D9D09ULL, 0xE7BA686B6B13D132ULL, 0x30E4C86F5DB92F17ULL, 
            0x25FD095702B83A14ULL, 0x71AA924C22668F79ULL, 0x6834F741FEBF1246ULL, 0xCA52A8D314697B28ULL, 
            0x44862D74BD23A3BDULL, 0x50E416B11CEA8B11ULL, 0xEB2057C19A348927ULL, 0x4A8488F32638695FULL, 
            0x6AB290217A59DD47ULL, 0xCC486585DE96CBF2ULL, 0xDBB851AA7475827AULL, 0xC3EE79AB33F72332ULL, 
            0x681E8A84C2987205ULL, 0x3CDB9640803EF3E5ULL, 0xFC4C265CA37D0FE4ULL, 0xF2D12B880C8135CFULL, 
            0x8F151F7406ABAC1CULL, 0x82668C034AAF3D39ULL, 0xF40C19F5AF740B67ULL, 0xA9A3265F025A496AULL, 
            0x5968639F8F9F466FULL, 0xADB09CCE4EB396EFULL, 0x3F88B99D3FE2F1BAULL, 0x406D1A367AD239A3ULL
        },
        {
            0xD2BE89E8484726B8ULL, 0x98A72F5FEF4BC6C7ULL, 0x38F7C946ADD71C92ULL, 0x80AA070B3F1EE247ULL, 
            0x1352B5ED7EB51DD2ULL, 0x509BF1DF9E740215ULL, 0x89297AA46E236C55ULL, 0x8CB43B5E45E2D9C4ULL, 
            0x5385F029F661CEA3ULL, 0x9EFC7FDB4B4A48F4ULL, 0x3C85D6E056C34805ULL, 0x0446969366D34704ULL, 
            0xD2F92AB23565EFA1ULL, 0x1B245296455B7911ULL, 0xA9D49355E7163F26ULL, 0x2915435EDDD0A632ULL, 
            0x1EA597B9672BBEDCULL, 0x90BAFF7CBF9F9172ULL, 0x64A076184E946C00ULL, 0xB763AC38D36E9AE2ULL, 
            0x4C51DAD4EB7F385BULL, 0x402268233163969FULL, 0x17A5C6AF0BC6DE3DULL, 0xBF330FEB5561FDAFULL, 
            0x4DBE4FB608985E43ULL, 0x87C2E1BFD09189F6ULL, 0xBC20106B1A59AF6AULL, 0xCA43267991F94B19ULL, 
            0xD53A6EFBA75CC90EULL, 0xE1EC83788B344462ULL, 0xA031AEA0F2A52B5AULL, 0xA911494CEB749128ULL
        },
        {
            0xD29611C538761139ULL, 0x13B8E2932CF8421FULL, 0x0642F7E65EB5CFDBULL, 0xE57DBE4E2CC5A04EULL, 
            0xBCFE8E665281CC82ULL, 0x457DADCA18D15977ULL, 0x49483511C35D0790ULL, 0x6EB4F0317F49E41BULL, 
            0x2FD198C11EC7A725ULL, 0xB9A4C9EA61B12154ULL, 0x631D2AFF52412686ULL, 0xFF2D5EE4683C9BBEULL, 
            0x18F1D01A02AA82E1ULL, 0x824CAD64D892C43AULL, 0xA32207AD1E2233FBULL, 0x34FE135C22E923C4ULL, 
            0x9AFCC652AC18857DULL, 0xC4D46AEE90ECCBE6ULL, 0x8EC7D5FCA9D478E9ULL, 0x7D6A87B839E412B9ULL, 
            0xD6167477BFC167ECULL, 0x3DD85B9D8C13E15CULL, 0x9F6EDBE8C76A508BULL, 0x1D33A6B8AF2644EAULL, 
            0xF11E5331F7BDEACAULL, 0x420BA434605CD20FULL, 0x1A66DBE53A9F2063ULL, 0xB405855FC5D42B13ULL, 
            0x184DD8CCCB56F48EULL, 0x28B963EF2E85764BULL, 0xD3A13A5D59D1451BULL, 0xCDE5F00CDA6E50B1ULL
        },
        {
            0xB87A59FEAE2B7428ULL, 0x1A27855239E27D45ULL, 0xC652DE3308BB11E4ULL, 0x8CE5964FBC811573ULL, 
            0x94B796CF5E97704FULL, 0x65182745C18647F2ULL, 0x0C58DA96F306E1B5ULL, 0x8D86F99D20A190A9ULL, 
            0x942F0732AFCEB893ULL, 0x7B15ABE8DAC68D95ULL, 0xA9C8A8F70E49D575ULL, 0x1E0F231F681BA0A2ULL, 
            0xE7B3DFE76BEC7C3EULL, 0x1A75ADC0F38B1B21ULL, 0x6996E8BD3C574322ULL, 0xB9519CA3C5DD7A37ULL, 
            0xD0C7AB867AB5DA5FULL, 0x993803916E64962FULL, 0x2102679836FC1176ULL, 0x2DD25558EF4CC581ULL, 
            0xF9C314508F09C3F6ULL, 0x0A4ABB812AA5FE32ULL, 0xDE39FDB882F0F65BULL, 0x83B5EA2594066882ULL, 
            0x14C6E245362A8DD9ULL, 0xB35E9BBC26078D4FULL, 0x68DF00C70DF80634ULL, 0x29D0EFADD6F641FBULL, 
            0xA748A6E1ABB16F22ULL, 0x073C4FC0B642FF60ULL, 0x2CCD76EECC716C4CULL, 0x3904BFCF96DF8468ULL
        },
        {
            0x281D660E6EB87FE5ULL, 0x719BA14372A98DBEULL, 0x84643876CC26676AULL, 0x4729282B465B9AE4ULL, 
            0x562C160398B75380ULL, 0x0FDC7DBFAF4F030DULL, 0x57111C962A8577EDULL, 0xE0B9F1232F87FD84ULL, 
            0xA851BBCC4688C393ULL, 0xD3242CC5E4585CC1ULL, 0x5F978E0B60D7881EULL, 0x6B2FD5F9FCFDC6C1ULL, 
            0xBABA5D80A74401D1ULL, 0xE5FD56BBB0F3C0CCULL, 0xC18646A486A6B1C0ULL, 0x56F2EC49E28DDF25ULL, 
            0xC63D2082E44599BEULL, 0xCFFA342A7528B46DULL, 0xC78AAA30D7AED864ULL, 0xA618085C04E97D4AULL, 
            0xA8E66CE11E955F1FULL, 0x45132CE6F6C8088FULL, 0x428C3977DBE1BB9FULL, 0x6919A7EC1EF920D4ULL, 
            0xFC1FBF6D26E3AF0BULL, 0x269BBE2CFE310CCDULL, 0xAE7A0F2F1382559AULL, 0x93EB86007B017FF1ULL, 
            0x6BA792B4AAD02136ULL, 0xD497CFDBBEB8D74DULL, 0xBE2FD13295465CD4ULL, 0xEB19A26F5A70318CULL
        },
        {
            0x716FE79308544DB8ULL, 0x18A9745E0AEAF551ULL, 0xF788BD14094A5BBBULL, 0xB8FF043504DCA8DEULL, 
            0x01E0C4A90B1E623AULL, 0x968039C797C5200CULL, 0x946F98A95D4D6ADCULL, 0x8496147DB59B8A18ULL, 
            0x26622F36BCF39D80ULL, 0x0C3AA2C613DC3225ULL, 0x3CA98925FBDF6F6DULL, 0x79DF5B153C4E690FULL, 
            0xDA062CC91B23C4DFULL, 0x61E28A0E71CE8553ULL, 0x2C2968619BCF2FBAULL, 0x74591A394A526FA9ULL, 
            0xABA57C1020719D59ULL, 0x0E55712D75E8F049ULL, 0x350F49410E828824ULL, 0x647F3F6E62FE1668ULL, 
            0x981B348DAA651838ULL, 0x24D0F9A1D2139352ULL, 0xE9A209A9787D7061ULL, 0x56F3EF634D7846FEULL, 
            0x0512B70D08A6ED58ULL, 0x0BF15F094AC1DEC8ULL, 0x94EB90144FCDAE66ULL, 0xDB5A07BD39347F41ULL, 
            0xF853FCD1983CC956ULL, 0x5B6D0EB31B1F4116ULL, 0xB88E36D63EE1C60FULL, 0x5AF604EF2AEE79A0ULL
        }
    },
    {
        {
            0x2C48B08E089D8FB9ULL, 0x58D5F35C10D6B138ULL, 0xEA841A4959D4E8E5ULL, 0x57782011BC5C5654ULL, 
            0x7E051457BF041A2FULL, 0xBE35FDFEB51BC769ULL, 0x56BB935C257219DCULL, 0xA12438AFE0CB448CULL, 
            0x9B5E8B92514F682DULL, 0x34296611E1818341ULL, 0x000F3C518C00D09FULL, 0x1A4C07ED8ABDED91ULL, 
            0x87C4521725C241F4ULL, 0x6A0F2292D449EE2AULL, 0xE437BC761AA62A4EULL, 0xC9F0551111EB57B3ULL, 
            0x6018DADD301778F5ULL, 0x6F0327087E54CFACULL, 0x8209B1667AF32D24ULL, 0xA7EF2981D5E781ECULL, 
            0x217AA8B1F7E1A4ACULL, 0x2DC91EC3F7CEF1BAULL, 0x7128ABAF21043C2BULL, 0xE935F318FA7F7365ULL, 
            0xE54024561519AD1EULL, 0x7CB2005E8A2B0586ULL, 0x2893892798CEB6BFULL, 0x1B0D5DFF4A3BC68DULL, 
            0x734B0FED8BBB7A3FULL, 0xF10AD28AEA0843E0ULL, 0x1C4BF3770E274C48ULL, 0x5E8C94AA0FDB960FULL
        },
        {
            0x14FA9DE98717848BULL, 0x0E1C2E2A04040BDFULL, 0xC60C2205B791D1A5ULL, 0xBF3E10083CD205C4ULL, 
            0xC2B7A53020CE4D39ULL, 0x4F23A44655AE5BAFULL, 0x6DD5FD9C83299F9DULL, 0xC234E4E38460485EULL, 
            0xD571C01C32B17611ULL, 0x5DD9C728AF7CE603ULL, 0x55B82D9A59BB9A57ULL, 0x97C596FFDED8793EULL, 
            0xBF34C517FFA65CF0ULL, 0x6AD9305CDEECE092ULL, 0xC719556C94781D92ULL, 0x77C233F874437E8AULL, 
            0x7523F1A6E7CFCDE8ULL, 0xE2585841B68C4B33ULL, 0x0142B46CC7B7E308ULL, 0x79810A2DFAA3954DULL, 
            0xBFAEDAE756C214B6ULL, 0x346D5ED13068715EULL, 0xE62F09659EBD2057ULL, 0x70E0E006CA1B6C5EULL, 
            0xEEAF48C6B89D8E8DULL, 0xE6A275098B9E092BULL, 0x78BFF5E0C6088B09ULL, 0x4B91D6FEC97A3CC9ULL, 
            0x569DECD2BC987816ULL, 0xE358611A941C6A24ULL, 0x455650D9FC11F70AULL, 0x3836BAA4A9039460ULL
        },
        {
            0x810E5BFC224A1657ULL, 0x54BACA05094A7513ULL, 0x3BA0964D08E2DB28ULL, 0x139033DB6AE853B1ULL, 
            0x397BFF5E70AC544FULL, 0x9372CAE04157D068ULL, 0x0026C4FA883112C3ULL, 0xF8461BC6793C1EBDULL, 
            0xE7995624957EFB6FULL, 0x0F41BD699AC97A5AULL, 0x404171B431AAAE17ULL, 0x795507D5E2257BEFULL, 
            0xD35227B61A805D20ULL, 0x58823D15597A0219ULL, 0x68BA3096353DF0A5ULL, 0xD21925ADAB16CEEDULL, 
            0xC109C5A08CB77E2CULL, 0x7AD6021F5FE1C29DULL, 0x9420C29D798D5797ULL, 0x56ED3136C7998BEFULL, 
            0xEBB4AD5D5FF9E704ULL, 0x0BA2D1F3F29AE52EULL, 0x5A10732FAAA99CCEULL, 0xDFBB058C1A9197E2ULL, 
            0xA9F1B8FEF1423DD5ULL, 0xEE238AB9A2371873ULL, 0x3D2C45DB3247DB6EULL, 0xDB12D25860860300ULL, 
            0xB1076D2F4C8E30C4ULL, 0x2797747BAD4E4EF3ULL, 0x6BE6FD346CCE410BULL, 0x62E53B6731E277B3ULL
        },
        {
            0xBE1C9EDC3886497FULL, 0x1EA25A2D956A2390ULL, 0x14A348C94F98139DULL, 0xAB270D4C5D75FA24ULL, 
            0x593531E8AA749D51ULL, 0xCE3F13594A23B00BULL, 0x150EF74062B23371ULL, 0x4E0ED73939F5185EULL, 
            0x2C593022B892DDACULL, 0xE65854881A220859ULL, 0x7D4E28D1638DA753ULL, 0x2FC56D62C4752663ULL, 
            0x638CBBA957DB4806ULL, 0x4CE414133DEDF559ULL, 0xA75B17635A10DCF1ULL, 0xFC93FEFD4A460A8FULL, 
            0x7F388FC857D7D418ULL, 0x4D8B7C5B3EF31B94ULL, 0x92C19C56E7F087E2ULL, 0x51A3CB3324C5A98FULL, 
            0x35E984F6ED238A91ULL, 0x063591E387A8E9E9ULL, 0xF3CE0F2B4FAD1FDBULL, 0xD70600AB321AA25EULL, 
            0x9B4EAFDBD0DCF602ULL, 0xDF3BF41F75655B22ULL, 0xDD593750BCAE5F94ULL, 0x27F31790B229A72DULL, 
            0x14112322B451CFA1ULL, 0xD7319D0398CB9BA1ULL, 0xDAF2D891FC51BC55ULL, 0xD62530178A0D6650ULL
        },
        {
            0xFB4E5A1467E11513ULL, 0xC633E3DD2CB55782ULL, 0x01DFFA6589B17A7FULL, 0x6E97E938AF31F595ULL, 
            0x471E46C61D56E6FBULL, 0xFE8879D50192DFE2ULL, 0xA882CDEC90E51925ULL, 0x7F8F732C6E6E09BDULL, 
            0x9C0D9347EF0206FAULL, 0x612A397138A146E9ULL, 0x0D34AC098615C123ULL, 0x8C72AAAEEE164E77ULL, 
            0x848AC642D5C894ACULL, 0x9716F56E65A7B14EULL, 0xEB4C3909E3F9C80AULL, 0x677ED8604F25F108ULL, 
            0x9BDF39E4FD5239A8ULL, 0x5BAB69283DDC134AULL, 0x6FF9CDD5B86DBDDAULL, 0x1394381E1EBA29EFULL, 
            0x03161F09FEDC5DB1ULL, 0xD387C7E98F01E4E8ULL, 0x13E2BDD71A999522ULL, 0xE8B909D01DF49B51ULL, 
            0x92C2195CD9D91955ULL, 0x68541CDB8E238181ULL, 0x85006257C98A657AULL, 0xB82076603E14DF5FULL, 
            0x0D6FCC576921A6CFULL, 0xEA149B482ED9FDABULL, 0x45AD5EB8994CF75AULL, 0x8BFA1BD68E06685AULL
        },
        {
            0x0B1A3C807E22678AULL, 0x37D1A9C85E5C2FD1ULL, 0x8802CA75F743D587ULL, 0xA34D36C77EFD02A0ULL, 
            0x993544C577004FA3ULL, 0xB153631D7620A5E2ULL, 0xBDA428E72CB28B9FULL, 0xF43BC4CE46AB28A7ULL, 
            0xC87B8E8521220EF9ULL, 0x31DA1BEE5555BAE2ULL, 0x7AEAA06C18AB1BE4ULL, 0x3189456991D8DBF2ULL, 
            0xD945FC80BA6F742DULL, 0x51A2D46133621C29ULL, 0xF62D06AB027F534CULL, 0x7C89BD34C716FB62ULL, 
            0xB561D410A0E041A6ULL, 0x292FDD8ED4274821ULL, 0x1CB3A26507E4CC7AULL, 0x9B12779627B0F04EULL, 
            0x81C1BDD587794FE2ULL, 0x76B446D29E84D030ULL, 0xC95490CE88869285ULL, 0x54286280B95B25E9ULL, 
            0x20B413C82A328950ULL, 0x377DFC944D157595ULL, 0x744F26E39DD1C05BULL, 0xEA3454B1AFA3CDC7ULL, 
            0xD557BA5BBA8F797BULL, 0x9FADEB63DAE8ED40ULL, 0x34059ECBB2219DE7ULL, 0x652344F611A59D47ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseAConstants = {
    0xA1AFA2587F0CE954ULL,
    0xB46E9893507E81FCULL,
    0xFF61476F98A0D791ULL,
    0xA1AFA2587F0CE954ULL,
    0xB46E9893507E81FCULL,
    0xFF61476F98A0D791ULL,
    0xEB2D9553501BBC2BULL,
    0xBD1A3A3174DC7B27ULL,
    0xCD,
    0x78,
    0xF3,
    0x12,
    0xF4,
    0x11,
    0x50,
    0xFB
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseBSalts = {
    {
        {
            0xD7D42036A36EEC30ULL, 0xD67E0364691AEFFCULL, 0x0330BEB0488D8CD9ULL, 0xC94CB303819674AFULL, 
            0x786524D579E0A7F7ULL, 0x2A26ECD78418699BULL, 0xF034426962DC4EFDULL, 0x03C6BE21D4E08D3DULL, 
            0xE9C63129E14F5327ULL, 0xB012DAB85E3E7290ULL, 0x0DDB08071AF9A1F6ULL, 0x69F972C179AD9FA4ULL, 
            0x831EC56422C2594AULL, 0x2B7FACEFAA45710DULL, 0x459ABBB41F4798AEULL, 0x2FC1CE17EE14D414ULL, 
            0x7B4CB79960DAB8B2ULL, 0x4B16F36045A009C0ULL, 0xC38F816EEE5F0985ULL, 0xC2D6CF1446BF302DULL, 
            0x418F40363C1AD085ULL, 0x986FC6D96CF13454ULL, 0x0D14312DBD9CFB22ULL, 0x0765EAA3AE598722ULL, 
            0x136F0A1E434D0213ULL, 0x15A4B8B0BC7578FFULL, 0xA11D24C469A1DA85ULL, 0x15FD1C45B171903EULL, 
            0xE6C1FBD70E3BA13BULL, 0x2B12E95634C8F490ULL, 0x86DBF7DCA40F4FA9ULL, 0x321717A99759FE35ULL
        },
        {
            0x62483F94929C0554ULL, 0xBBE48D453CC4666AULL, 0xA5B82AED46199583ULL, 0x00C069D43998D9DFULL, 
            0xE2AA1793BA23B944ULL, 0xEF90AE065BE08D3EULL, 0x2C065E6510D8E48BULL, 0x95F0F0BD9639CD97ULL, 
            0x650020AE25D1F4F4ULL, 0x989C5ECD5A77BFD5ULL, 0x807513E4E420F0BEULL, 0x8198E22B685BA8A1ULL, 
            0x1D5BF1A0227895B9ULL, 0x767F062BA66A2398ULL, 0x8D361CC855AA0E34ULL, 0x0D2BE68EB91B5BD1ULL, 
            0x3F0C927C4B623692ULL, 0x3ADB1FD0E0FCECF3ULL, 0x26E1DAE3EE94BED8ULL, 0xDAE4094CD518E267ULL, 
            0x51AE2A3F3908513FULL, 0xBDE6C1A1CB3C69ADULL, 0x401C77FBECA1B559ULL, 0xCBFA098DA5B7D83CULL, 
            0x79A19FF51DCB85E7ULL, 0x22A3F2BB5EEE9030ULL, 0x2A7326DE4AF29A87ULL, 0xAF813CA3DD781317ULL, 
            0x68302BD7B633EC11ULL, 0x72EC284DF4B07D66ULL, 0x039B9BA4FCD209B1ULL, 0xBFE04B2752A29B18ULL
        },
        {
            0x33B5555384998583ULL, 0x04E775F5612F6867ULL, 0xADA21C83B761296EULL, 0x7340B600D1F93ACCULL, 
            0x9AC3DD34064F87DCULL, 0xF8D9986ABCFAE7E4ULL, 0xE342F089B569B35AULL, 0x13258A83214A3131ULL, 
            0xF8EA9EE73EB3AAF4ULL, 0x19178F11A9A29002ULL, 0xEB9F2140D2A566DDULL, 0xC6488EBAFDDBBB3BULL, 
            0x9E4C1520A76C5FB6ULL, 0xE989EDB826203D14ULL, 0x9065C74E521EB08BULL, 0xCF10D3454DD3DCB4ULL, 
            0x4A65323923BEC2C4ULL, 0xB0EE2E1DD94D8CEEULL, 0x5C0536829CE49261ULL, 0xCCC74FD809CAACDAULL, 
            0x82844B755A7F63A2ULL, 0xFE5A78D81B9204D5ULL, 0xB088B9A9F68F3A9DULL, 0x0EE8F0E2973B9BD3ULL, 
            0xF6D07705E5076DD7ULL, 0x7373DBCFADC65E1BULL, 0x8105C6970490809EULL, 0x4B15601F1B18E87FULL, 
            0x4576618687D16079ULL, 0xE2EC291EF40230A9ULL, 0xFD4603E8A4638A62ULL, 0x697826C11745EC3AULL
        },
        {
            0xEF674DADE2973573ULL, 0x4AF250B9CCCDF2C5ULL, 0xDF1AABD08D378BABULL, 0x7CA3A6522EB8524FULL, 
            0x4C77BF82DFE12055ULL, 0x88D5DF8DE64D00E2ULL, 0xFC043F7B5D8744F6ULL, 0x226BC297759551ACULL, 
            0x9BE186F9E7933112ULL, 0x46BDD20C77698B5CULL, 0x2E35D16028D19119ULL, 0x9AEB4AC271DB7673ULL, 
            0x32DDB27ACC77375BULL, 0xDBDCB3E01A592358ULL, 0xACF6814616293EA3ULL, 0x6EA2BA90C25D60F4ULL, 
            0x68167ABDD1AA7D86ULL, 0xAA7B5259FE40ACD7ULL, 0xEB3DBC7EFAE16650ULL, 0x3A8CD7E5330F128AULL, 
            0xF8B260CEBCB31157ULL, 0xD8E8D96BEFAFCB01ULL, 0x8CF080A712C50DF7ULL, 0x4786F25A72F22B27ULL, 
            0x07CFE4EBF408E2DEULL, 0x1DC3BB624486DD63ULL, 0x2F8F4A04548BB120ULL, 0x98531438F9558FADULL, 
            0x30D876720F9B05E8ULL, 0xF4F609798F14A1AAULL, 0x9BEE7F98D2528A40ULL, 0xD44C1766A148717EULL
        },
        {
            0xADB683D907B6BCC4ULL, 0x44BBD6298C2FA2BFULL, 0xBE59ADF0CC63541CULL, 0x3CBE6DA1503FC909ULL, 
            0xC6C2B2F57CE5DBE7ULL, 0x4BA3847EC60092A4ULL, 0xA5F126B97E23842DULL, 0x9A328981881D31C0ULL, 
            0xE7FB8FDE7B2BB3D7ULL, 0x2E3FDC9FC74591AFULL, 0x960030DEA5375EBCULL, 0x4F67C103D2B4BA66ULL, 
            0xED6BDAF7EBB6BDFEULL, 0xF3C1C13119C721FEULL, 0xB91FF95A0E0F63E5ULL, 0x06414F522B1FB42EULL, 
            0x9EF103DD707C87F0ULL, 0xAC81447034840B77ULL, 0x0F5879CD6C4331AAULL, 0x67A420C20FD445C0ULL, 
            0xADB8040A61604193ULL, 0x46AD4CEF18BEFECDULL, 0xB4E4A101DEE5D54FULL, 0x7BBBCCFA52EB649BULL, 
            0x5A38B5EF2A5F7437ULL, 0xA44DA2308DC8A62DULL, 0xBD5E10B573761D20ULL, 0x7D13C009E3FEB02CULL, 
            0xA33FDBEF57059086ULL, 0xAAE91EAEE542B44DULL, 0x9111BB37A3EDFCB1ULL, 0x75406D356190278EULL
        },
        {
            0xB0AF040B78FE0404ULL, 0x732711DED8FD8137ULL, 0x9167EAE540C78AF7ULL, 0x00DB2E1AE7396D05ULL, 
            0x987CAAB929280F41ULL, 0xD04F332EA1D232BDULL, 0x4AABE4114FE54347ULL, 0xE0625792C5A551B6ULL, 
            0x47E5AB8C2EAB187FULL, 0x13DE6D149AC7E67FULL, 0xEA279B82683E7D12ULL, 0x7D9B2C1F20166460ULL, 
            0x45EAC68E7487B7FFULL, 0x0322DA01DA13E028ULL, 0xEB1DBB9150A35667ULL, 0x2FD0DF47CBD18073ULL, 
            0xE5AA4FC8BF919DB7ULL, 0x8D819ED9305DAD28ULL, 0xA8E7C471F8A7C19FULL, 0x38395BCDC0F9C8A0ULL, 
            0x77410A40EC747C22ULL, 0x6F77F33551CEE3A0ULL, 0x4680F1055E71E6D6ULL, 0x247DCDCE94EBAA51ULL, 
            0xA84B7A6403CF1C1DULL, 0xFA609CB16B1F3E07ULL, 0xA8D6D5518EF18552ULL, 0xFDF74AA07981AB59ULL, 
            0xB03191A18E736DD2ULL, 0x3CD212A1787B1707ULL, 0xD8DD2F72A81B4A13ULL, 0x37BE34A7D5A393A3ULL
        }
    },
    {
        {
            0x720430AE1C86F6AAULL, 0xB2EC60EBC0C6B158ULL, 0xDF1280C39309234CULL, 0x7B1C4C1AA6ACE688ULL, 
            0xA48420C128804EF4ULL, 0x8FC8B1B70A4E2FAFULL, 0xD2FBCDD55D826BBCULL, 0x7FF0911306926864ULL, 
            0xFCF17916C53AD633ULL, 0x65BD24F655B40E79ULL, 0x642C9406F9CED18BULL, 0x5C542AB89E14C601ULL, 
            0xD575FC1C4DE4C560ULL, 0xF02A2BD659B5FEB9ULL, 0xE26F53A1564AE948ULL, 0x9A4BE65DD23D3C60ULL, 
            0x085BF9ECC581BE3FULL, 0x61E53E9CD5B20896ULL, 0xBA45E00F9B7E0522ULL, 0x6EBD87F374B59AF4ULL, 
            0x3F4236E3CA37A4ADULL, 0x1E240004120B6835ULL, 0x2465AB5DBAB79FF4ULL, 0xA6D4969F637FBC3BULL, 
            0x3CC53C02D49E7E24ULL, 0x18E11E6E97C7EC61ULL, 0x0DFA5BF5D855343AULL, 0xF2471EB5CEE1A9D6ULL, 
            0xC68EA382D64244DEULL, 0x885F99486D5B8B2BULL, 0x22DDC50EF519EEA2ULL, 0x25FF1D8860930A11ULL
        },
        {
            0x151B38ACB22F1D9FULL, 0x3272D7F4DF1997BCULL, 0xCEC654BCFD02D78FULL, 0x8C9C8F3CA61F7A86ULL, 
            0x7D9D59BF0850C238ULL, 0xDA4DD1C9200A549EULL, 0x2EF42EC0739E49D6ULL, 0x7D513D474F8A3E3CULL, 
            0x6E3900CEC906D134ULL, 0xFE10683459526EEEULL, 0xEBFF6D10A0D0DC44ULL, 0x1F403AB1AF618852ULL, 
            0x4AB37B6A8FD99C4FULL, 0x431B7249022C9BDBULL, 0x70A2C9586EF7F472ULL, 0x64068EEB5B1F2597ULL, 
            0x9D388C8E17665018ULL, 0x93FCF11DCE7CAF1FULL, 0xD7B3F09A6AF21C2EULL, 0x2AAB6505E027B26AULL, 
            0x9B166E8417AFB053ULL, 0x638D48C7DFB7BC57ULL, 0x72FEC2D507FB7B80ULL, 0x93BAC483A65C56F6ULL, 
            0xBFAD4C90C3558D91ULL, 0x2D8710DD517E59D6ULL, 0xF37FE073DE36C36CULL, 0x850DD944EE924C6FULL, 
            0x601005E84244EC28ULL, 0xB88CDB95A93F1B56ULL, 0x412D65AEB619D031ULL, 0xA5A03860189E7FB6ULL
        },
        {
            0xFCE6F13C198D29D0ULL, 0x772C523F19971AAAULL, 0xBCDC39EAB903F21EULL, 0x6BF4C2F8E442723CULL, 
            0x74F35754C4C76107ULL, 0x14E9C99B655EC928ULL, 0x36BBE0F7D301C556ULL, 0xDF0DE0760E9C63FEULL, 
            0x112C9C23F8565973ULL, 0xD1784BA9E1E2B59BULL, 0xE521A2146860AB5AULL, 0x2234C51D0C65E999ULL, 
            0xD02DDA744A4E1E34ULL, 0xA8E6EC86CEA47CF7ULL, 0x0CA6B88F6661B06EULL, 0xDB51EE2F4FC4B6ABULL, 
            0xE8F8003011BFC709ULL, 0x02A8D919BFC63EFBULL, 0x77409C942F50963EULL, 0x094B16188EF3C758ULL, 
            0xA2C6D0C920A6D926ULL, 0x2806D696C1150E87ULL, 0x55670A93FF3B3C72ULL, 0x9DDA4DF39250F056ULL, 
            0x2E7537A0A3EC545FULL, 0x2658EF722468A57CULL, 0x0169C4490936EF25ULL, 0x1B5D81748EE96E6EULL, 
            0x7A49150B2896C783ULL, 0xE239C169823EED8DULL, 0x5CE967AB76149854ULL, 0xE4CA1BE2F7392439ULL
        },
        {
            0x6A4F178BCB4750EBULL, 0xFB2D62820AA3EF84ULL, 0x6EE4B63A9F52DC0DULL, 0x882A924EFADD4A55ULL, 
            0xC850D4877A0C917EULL, 0x7E83F53E4BB79CBEULL, 0xE5E85A06D2B551E5ULL, 0x7F15C23F97BEDFFCULL, 
            0xBFF91D607E373313ULL, 0xE330333A7E80F9C2ULL, 0xF5AC272D803224CFULL, 0x2427D71635D251B5ULL, 
            0x3727F1C89D68E1A8ULL, 0x6B8F906806620527ULL, 0x5FC39B883B6F5D0DULL, 0x9B30AB13D786E6C8ULL, 
            0x03732EAEAADB0962ULL, 0x58CDB46700A5334FULL, 0xC3FE8AC2EDA2014EULL, 0x7E4A0862626E4027ULL, 
            0x2202A6FCAA443C76ULL, 0xC1DE3D952798494BULL, 0xB4F63D29F2A3CD11ULL, 0x5D4E89C957392C1FULL, 
            0xC0C997FAA24FDD6CULL, 0x7E2741CF5A672998ULL, 0x8FA9F2ACE607D5BCULL, 0xB2A667C38F94DC61ULL, 
            0x9A45FD7D14E19984ULL, 0x57D1A30ECAA471A1ULL, 0x1D8F4B389C47D78DULL, 0x75114F7AA7F9C802ULL
        },
        {
            0x8CE8FB7F9EFFCC65ULL, 0x0A532A3A26FCE5CCULL, 0x63C72C18C7588E9FULL, 0x179C491DFE21BEC5ULL, 
            0x8C2F3CE95A176F6DULL, 0xDEF0D5638253CE52ULL, 0x531F41D7DA29CEF9ULL, 0x6BB36D1E0B3901F0ULL, 
            0xA13069E58F7224C7ULL, 0xCA2929A8F136DE0EULL, 0x75DD0D3BD57EAD0AULL, 0xC749A8AA93480203ULL, 
            0xA72EB943EB7C0EE5ULL, 0x953AD43EF133319DULL, 0xA5ACF611FC4F54F4ULL, 0x0018C52ACFC997D1ULL, 
            0xD1F705959B3D77AEULL, 0x84360BCDF90EA377ULL, 0xF65F934A2B0D73C3ULL, 0xD67EBBA386661B0FULL, 
            0xB97D52FB05154B45ULL, 0x527E9AAC7FA38526ULL, 0x8780D039B780356BULL, 0x95C958970F65D691ULL, 
            0xA012518D779D6D22ULL, 0xE8F3C0490718E71CULL, 0x46982815E1D93596ULL, 0xE876E3AFD679CE53ULL, 
            0xE4148DD2FCF105E2ULL, 0x4D7E7C263E9AEF11ULL, 0x1E27E0860A308050ULL, 0x9A90E675918E1458ULL
        },
        {
            0xAC2F553BF5778E5CULL, 0x8EA30BBD5AFE4634ULL, 0x134629B8F78BF3F2ULL, 0x3954F49DD77F6B15ULL, 
            0x1C1A6AEF5282D755ULL, 0x35E2824F371F98E7ULL, 0x8F5A98EB7E84BD80ULL, 0x6E6292B3CC525ECBULL, 
            0x5498AA9B5054AF31ULL, 0x8EE0F66664AA1ACDULL, 0xDFAF9600FA746DD4ULL, 0x512CFF5B4BE79B80ULL, 
            0x010E05CB3DB1E7E0ULL, 0xD4EFCFB81B398278ULL, 0xF7332A4D8412A2FDULL, 0xA1227B6AF6932AB9ULL, 
            0x4823CDAB2ABEFA48ULL, 0x6506B51F091C1E45ULL, 0x0C00FCFE834D8468ULL, 0xBF09A4095AC3A570ULL, 
            0x1AA6BB9FFE643543ULL, 0x3375C0E52F499F16ULL, 0xB54CF058B912F716ULL, 0x57D8025FBA9F828DULL, 
            0x62BA3E82EEA3F987ULL, 0x7733E577B33A53FDULL, 0xE016F145D93C17CFULL, 0xCAE802140EA19BF4ULL, 
            0xA8D33C4E16DCD5F0ULL, 0xCA826EEB87C1E5E5ULL, 0xCAE6DFB17BB95E58ULL, 0x4A57881E2304FCEEULL
        }
    },
    {
        {
            0x46758D5254F0EC98ULL, 0xB37E910CE06B7CF3ULL, 0x947B4A1201C02312ULL, 0x1DC191BC5170B9B5ULL, 
            0x51E73C349472D33EULL, 0x0846A7D8FA43E965ULL, 0x0988EE8899928AA6ULL, 0x9083931B49C6BB6DULL, 
            0x1F4F79096C575545ULL, 0xA9EB4FD224977A3EULL, 0xDDB10DF39600830FULL, 0x3BEDE5671B5A6750ULL, 
            0x4E2C65C9E877364CULL, 0x8E29138A37C6464EULL, 0x67C35792C1B3E2BDULL, 0x6E20FF4BD62EDB16ULL, 
            0x59EAADF37F9ADB0DULL, 0x6C5B74FDC996B986ULL, 0xE53BFD1E0C4C94EAULL, 0xF07814DF2147462AULL, 
            0x3DFE1A9A5D3853C9ULL, 0x5B710CFB3850BE64ULL, 0xBF69B2B52EFF011BULL, 0x2C2E1825D0A19A64ULL, 
            0x11BA1F7544FEFB10ULL, 0xB5604DB70F510ED1ULL, 0x97610C4CE59046A9ULL, 0x00B78190959523D9ULL, 
            0xD2AC4B0A8B4DBADAULL, 0x1D9A49E71EDC608EULL, 0x6BB80A82405CC180ULL, 0x33DBF56A7462A25DULL
        },
        {
            0x578A21D97572DB1DULL, 0x5A0193304187E07AULL, 0x842FA9E20BEAE4ECULL, 0xC3F662B99F055FACULL, 
            0xEC5E9BF6E67135BEULL, 0x8253B3666716D525ULL, 0xEC7314E2AF242803ULL, 0x2F4BCDCA6077FF1AULL, 
            0x79C92FEEAF75DDE7ULL, 0x84A67DBDE366193AULL, 0x5A142E76BAE78A25ULL, 0x67E3CC2E1D7243BAULL, 
            0x71B8A2FCC6A4081FULL, 0x94A9E3865AE75933ULL, 0x8F4E80A1618661BCULL, 0x19AC74EB22359F27ULL, 
            0x0373C485241D4F3FULL, 0x6C81FB18B5448ECAULL, 0x6FD2F3274EB02DE9ULL, 0xF35CF74FBCA67216ULL, 
            0x6946D18B4E9A2383ULL, 0x45E7EACC95E6AD00ULL, 0xE56ED8B712F241D2ULL, 0xAFBDEEBD6D7F2A81ULL, 
            0x3BD8B695694012F4ULL, 0x945449FF126C4420ULL, 0x4D3A6B31F167916FULL, 0x2BAFA2892BE73891ULL, 
            0x15DB29D231C2469BULL, 0x3E79C575146A650EULL, 0x6AB905FD0C188D54ULL, 0xED5857ABA6F351F7ULL
        },
        {
            0x0BE458564AD56F0EULL, 0xAC2689A72697D1BCULL, 0xFA77F1A204F84F25ULL, 0x430AF7031DD83E03ULL, 
            0x87191A7D6A7F433AULL, 0x684EA581C263C60FULL, 0xD2C92C8D002B8286ULL, 0xC4B83B6454D673A9ULL, 
            0x3B79BC60348508DAULL, 0x271514176F44BAA7ULL, 0xD373E73F4CB2CA92ULL, 0x67499F33403E7925ULL, 
            0xBA5144E522EC5056ULL, 0xEBB4575F2BD28E40ULL, 0x03A9A4A35735CBA4ULL, 0x276265F161D44DE4ULL, 
            0xD7277EB101587985ULL, 0x257D73F6CEC80F01ULL, 0xF2BC583D1B75C3A7ULL, 0xB2F24221D507F85AULL, 
            0xD304D3B1F89175B9ULL, 0xDB9BE8E7BC974B80ULL, 0x633A06F326976481ULL, 0x70A7D07DA3A59562ULL, 
            0x63BBE20EA6464ED4ULL, 0xD8EC8CBC0604E613ULL, 0x8C11E66F44E3E575ULL, 0x7BED81503C580A30ULL, 
            0x1CDA39EB353453C1ULL, 0x04D7EA8474E92E4EULL, 0x44C970093E2C4776ULL, 0xEBC910367D9A5DBDULL
        },
        {
            0x80DEA6A12C8AD92EULL, 0x0B6C2BE9903E6F6BULL, 0x171580463CF149CBULL, 0x5BCB4E5714F1D637ULL, 
            0x030AB1ABFA6B1CEEULL, 0x59449B6CF1990B70ULL, 0x84825E479F8FC6EAULL, 0x21A1AFD3B911225AULL, 
            0xE03CC194742700A8ULL, 0x2D4B5D4A12126BC2ULL, 0x1DDE9260323C4DB4ULL, 0x8F6E51A183029837ULL, 
            0xDB5C19D2F24A2235ULL, 0x7376680C27B6150FULL, 0xF1AE2A50F433E801ULL, 0xC06633B8D5F9D316ULL, 
            0x49047D96BC35568CULL, 0xFFDBB2A74C6D8FB3ULL, 0xDBD827CD933C099BULL, 0x8B07E899E988DCDDULL, 
            0x3A5B3ADB9E939B15ULL, 0x2B70893872667674ULL, 0x1FC17273AE3717DBULL, 0x332FB20C093627CCULL, 
            0x00FA237A56DA94ECULL, 0x45DF45F2DC39067BULL, 0x6886A89BB93D75B9ULL, 0x0363BD2E4FFB644BULL, 
            0xAA246BA40330395DULL, 0x277766A63FADE41EULL, 0xF2CE1B951F7C7461ULL, 0x14E1BFFFEAA27144ULL
        },
        {
            0x0F41B5528804201FULL, 0xD624518373990958ULL, 0xF322E7D1F215684CULL, 0x971C0315DB445093ULL, 
            0xF901D8247433E77AULL, 0x545C9B1E9402DA55ULL, 0xBBC28EA056345020ULL, 0xC00B3F650D2BE41CULL, 
            0x44F51146752F608AULL, 0x886B9BAAC95A68EAULL, 0x5A6F8C44308D3B43ULL, 0xDF09E82A81941B11ULL, 
            0x719CAC40E7943B65ULL, 0xD7FC33CCC8439C41ULL, 0xE352B34E0BA9D104ULL, 0xDEE3EDBE2F6FCEF1ULL, 
            0x8CF7514FCC4E566CULL, 0x0F15217987D59D90ULL, 0xE7AACFA4F0584B77ULL, 0x4439347E7F2AF950ULL, 
            0x8FBD84D44A88FFB7ULL, 0x40D2E10B39F08DABULL, 0x93DED5DA665CF2A7ULL, 0x3C6886B33E50AAC8ULL, 
            0xE691E0E93AB30957ULL, 0x7B131068403FAFA3ULL, 0x322E66420B54AF8CULL, 0x5D398DE878839F17ULL, 
            0x0D378AC0635DFA5EULL, 0x92B55338F7D7F63AULL, 0xA69D29F79FF146F8ULL, 0xF3404DA0EF656C39ULL
        },
        {
            0x72B3536B221D4747ULL, 0xD26CC1F9D26B378DULL, 0x1AD01F7E58B3CD50ULL, 0x5FB3C146BD4C3CAFULL, 
            0x7B02F4528BEAA3C2ULL, 0x2565A92AE645C23DULL, 0x709A20CB49E3E5A1ULL, 0xECB71C29DCAC4EAFULL, 
            0x3F78797CA65CE833ULL, 0x871BFFBA540FC640ULL, 0x51105269E8398014ULL, 0x812C9DD30B12EA07ULL, 
            0x6DC8D0C3B1704843ULL, 0x7AF2604A9A88C04BULL, 0x0FFA0E263EEE323FULL, 0x0142359B2B372076ULL, 
            0x20A74E59BB9AFCFAULL, 0xB6EB64972CE53790ULL, 0x0AD9A598C896AAFFULL, 0x87C2408498A5CAC3ULL, 
            0x4DD18CF66B9C98CCULL, 0x2D18FCDC0D4D8D6BULL, 0x8B3475ED9E909BD7ULL, 0x81CE7D0152D78521ULL, 
            0xDF6AD2C459487E04ULL, 0xB7FFE52E6A4342CBULL, 0x9602C58033F41592ULL, 0x3FC6A9297AE0896FULL, 
            0x80DB383BD632BAAEULL, 0x1079BA4DDF030FB9ULL, 0xBA6B270AC9D00C68ULL, 0x2A74623CD6B7C2C5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseBConstants = {
    0x9430F2D783EDA339ULL,
    0x8BABAADC8AF65889ULL,
    0x0FDC00EBACADE918ULL,
    0x9430F2D783EDA339ULL,
    0x8BABAADC8AF65889ULL,
    0x0FDC00EBACADE918ULL,
    0x6EB14BA559CF42D9ULL,
    0xBE02724426229D02ULL,
    0xB9,
    0x04,
    0x0B,
    0x13,
    0x7F,
    0xF9,
    0x5C,
    0x2D
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseCSalts = {
    {
        {
            0x2830DBA4877E8CF7ULL, 0x06DCCC16FD1A70A1ULL, 0x629C379DA4F9247AULL, 0xD3A44CFBF02308D3ULL, 
            0xA7193C673C2AC1F7ULL, 0xB962E032887D3077ULL, 0xE75484D894640B9DULL, 0x4CEA664D09873F62ULL, 
            0xFA3DF9BE724477C7ULL, 0xA252DF7FCCA212D6ULL, 0xA1A467C0839CDD7EULL, 0xBA7E4DA1A4105EEEULL, 
            0xCC2A793337223D4BULL, 0x7050CFA97958791DULL, 0x9B11200BDB9FE9A6ULL, 0xA7BF947545406313ULL, 
            0xA321455A0D0E95E6ULL, 0x2FC5046F32ACC1ACULL, 0x0E4DFC9B9759DE2FULL, 0xE12A1F8E28A60508ULL, 
            0x90F710341A6175BBULL, 0xBB387EF635601AA8ULL, 0xA4DADB2F1E5427B6ULL, 0x3001624BA5AB2C5DULL, 
            0x0114D7A017EC312DULL, 0x989A2440B8788A74ULL, 0xD15E6785426F4169ULL, 0x859FC196D146A2B1ULL, 
            0x8CEA288EA25FA80AULL, 0x182AE623B177A4B3ULL, 0x2EA5494AE91300BCULL, 0xB0E4BAF5AFE2D574ULL
        },
        {
            0x5B2B908B63CBB0ACULL, 0xF86B3085F58F1E9CULL, 0x8209E85B9F99F267ULL, 0x62E4C2AE4DADB118ULL, 
            0x268236B9B194F930ULL, 0x4D36B359A24B13D6ULL, 0x54F4C19D2E3E0345ULL, 0x8D6E4240E2813C97ULL, 
            0xAA7B027F4FB05221ULL, 0xBC22DFBE7C736F42ULL, 0x80430E9CA6A8D481ULL, 0x33E16023434D6FEBULL, 
            0x1CF89DC497FA5B22ULL, 0xC1892819947D070CULL, 0x8FFE195EAFDEAB02ULL, 0xE9264A9629F4EFD7ULL, 
            0xDAEC7D8D722EF59CULL, 0xE42F8E4894F56DD2ULL, 0x42A51D75384B3B03ULL, 0xB74E77E2A940FDABULL, 
            0x0AFA4C27C0E53EA5ULL, 0x37661EF7DAC5E9CBULL, 0x9EBAEDC00179CDDBULL, 0x770B314FC61EF43FULL, 
            0xEDF45D7638D4BF47ULL, 0xBF97FE4310745ED6ULL, 0x3AAD52FF4408F5F3ULL, 0x05B52F45EF8ECE4BULL, 
            0xF502109571CCF69FULL, 0x3E1DBB60E83EAA03ULL, 0xFDD1C11891CAC8DCULL, 0x67275C844246247EULL
        },
        {
            0x741306E47DD79B6FULL, 0x6A8D6E88A3BFE8FDULL, 0xD437D57D8E6518E6ULL, 0xA92476FF54EC2EC2ULL, 
            0x5A354AEF9313257DULL, 0x78F0822330FA70FCULL, 0xD68528A8884D1264ULL, 0x320E4228A3A797A9ULL, 
            0x8F839727383C5EA6ULL, 0xE7794353B95C8741ULL, 0x563F7A01FDA2EB3EULL, 0x26F072C191930CD0ULL, 
            0x4EBC1532FC5408C1ULL, 0x111319F8216913D1ULL, 0xA854511CE3047C35ULL, 0x9ED10A8106725A41ULL, 
            0x5ECFCA7E76945C90ULL, 0xCD864129CE6101EAULL, 0xC38845FB3CAADD4BULL, 0xD9251F50AF8FDCFFULL, 
            0x905B0BD700C449CDULL, 0xDEE325CA68532ABDULL, 0x0C5FE852817E00D0ULL, 0xB57F85078C3C213FULL, 
            0x9EDD48962947C978ULL, 0x21A744DEC1FE820FULL, 0x7313A31EDC6DADC2ULL, 0x442C938C39D7EA13ULL, 
            0x14B15D8FCD1F9574ULL, 0x526B94FB6D6E3DC6ULL, 0xDC583EDA91BFFB79ULL, 0x6264564B3CB1EC30ULL
        },
        {
            0x3F16E1A6436D34E6ULL, 0xD4E0FF85A1C9AD65ULL, 0xD71984E17335793CULL, 0x61FA493115D599ADULL, 
            0x2F3EF09868196EABULL, 0x16A36EE1ADCC7AC1ULL, 0xD5065E7FAADA6CFEULL, 0xB1C171DCD2D5AA65ULL, 
            0x367FE0C92B6A4E46ULL, 0xFF9A4E1EECBEA2CFULL, 0xA4B050ABDBCCC481ULL, 0x5CB93C91E99EEC3BULL, 
            0x0C2AD4274844C082ULL, 0x27D5CA38EE356BADULL, 0x1E07DA9AA3216321ULL, 0xD6A3213462BA4EEAULL, 
            0x79E4327512C81D87ULL, 0xDDCE973D52C98735ULL, 0xD379474D41E40A90ULL, 0x084AC57FF2FCA9F2ULL, 
            0x7ECD8B8E07761BDCULL, 0x013D47265E82FD74ULL, 0x5A553A91A5916BBBULL, 0xF539175FC55A5CA8ULL, 
            0xED6F211D3F287FA3ULL, 0xF111C213D64DCE5BULL, 0x87B2C92B192F963DULL, 0xFABDD79C96FC2F14ULL, 
            0xC78383C22704D970ULL, 0x4436A748D86E3995ULL, 0x0177B6FF62BDA12EULL, 0x146603FA15D5BD99ULL
        },
        {
            0xED4567886796BCC1ULL, 0xC83A4B45AC651A28ULL, 0x33E3179EE63689D3ULL, 0x76CE6645925A7BA8ULL, 
            0x5D2FE9917B23854AULL, 0xA9705E4B9466A27CULL, 0x6B8412529BB22712ULL, 0x0C6B0F273E2DE858ULL, 
            0x815B1E7227E17183ULL, 0xFBE5E4349A7AAA48ULL, 0x55F744FAE023E974ULL, 0x4483681305AE54F7ULL, 
            0x679BEE80FE84112BULL, 0x9CCCB4C2F9F1B9A2ULL, 0xCDD180A74CB18E7FULL, 0x00368E7D0FF81ECBULL, 
            0xA7B3BD2B49B191C8ULL, 0x84B0FE3640CAB1E5ULL, 0x28E20FEE89500A00ULL, 0xBD42DFB364716505ULL, 
            0x076E865462FE3D1BULL, 0xC1E39C5D963B1F49ULL, 0xE0C3E3E8C9475834ULL, 0x88D26D0A72411639ULL, 
            0x92D0F64C1470BA26ULL, 0x7EABBAE9F136A364ULL, 0x1DA031C1CDB32226ULL, 0x4BD3AE99FACAE733ULL, 
            0xC67297BB0F266326ULL, 0x3DDD0327B7E6E7DCULL, 0x034D5B6C3BBCE13CULL, 0x236843517D5321FAULL
        },
        {
            0x1565D16FA3175C89ULL, 0x67AE0B7B6D8161AFULL, 0x3027803B7A6B3B86ULL, 0xD17034B8EC936ECEULL, 
            0xB582865694C8B66EULL, 0xBD6E480A881F5FAEULL, 0x05973AC99B050EFCULL, 0x64BB2672CC79082FULL, 
            0xB0E76BA61F7E83D9ULL, 0x79E59B4DCC7C5FA3ULL, 0x02B3EFB8EFE01CD6ULL, 0x77567542211AF04EULL, 
            0xA3A1E2B23DCF2C0CULL, 0xFE832088335A98F4ULL, 0x73BF523E311D6ED4ULL, 0x21298C37868F28EEULL, 
            0x02C699168ED7C964ULL, 0x24C556A0D77EFAFCULL, 0xE2FA9BC0D73CF5C7ULL, 0xD7902774268CA886ULL, 
            0xF60A490350A42CB9ULL, 0xE0D062199FB2170DULL, 0x6F1B36CE19A611AFULL, 0xB09A8D9B46EB0721ULL, 
            0x667295CDC9A494BAULL, 0xDE311B7BA9D04E10ULL, 0xDBE8F536BC79D282ULL, 0x701FB4A57F744A54ULL, 
            0xD5BC62CDD1B143DFULL, 0xD633DD307F0B3349ULL, 0xE3D3E343483C0F6AULL, 0xED5ADE77539710ECULL
        }
    },
    {
        {
            0x77284A77C3FDF985ULL, 0xC59A6FE5449C4E03ULL, 0x5F8705F325733BD0ULL, 0x2B9A65BC98D47B1DULL, 
            0xBFC98A2D1BCB620FULL, 0x5E7CAF454C8609ECULL, 0xB2A6D368702C4A64ULL, 0x76178E783A278F2EULL, 
            0xF6EFBE75FE10F42EULL, 0xB24DDE7904374664ULL, 0x2B415B591B624682ULL, 0x9DDE93EE94E97947ULL, 
            0x4137627E2756F5D3ULL, 0xE7BA28D46F07BEE6ULL, 0x9A032C205151B801ULL, 0x233F57B27A2CD75CULL, 
            0xED90ACDB98F7D874ULL, 0xC39015863C781DDAULL, 0xAE2B3D1F97E77D02ULL, 0x928D9A89CCC22ACFULL, 
            0x492AD13CB55BEF0DULL, 0xA8405F171698F41CULL, 0xCAFD766DE81EC34BULL, 0xC8D8717D3CAAD93CULL, 
            0x90CBCC3AB4ACE83EULL, 0x7096BCE9A95D0D3CULL, 0x9695BF379DCC43C0ULL, 0xAB5E075D40B33982ULL, 
            0x6C936A2F0D8D73A1ULL, 0xF2256FA9B66603ACULL, 0xE1DE6A1F95D5FCA0ULL, 0xBDC468C88979E900ULL
        },
        {
            0x591B09B62CD2A0ACULL, 0xECC49E618C84CCDDULL, 0x885E452BFCC00EE9ULL, 0xC33E0B2B5841DB2FULL, 
            0xC1757FC27C3C7EEDULL, 0x3A17F31F917147C2ULL, 0xC226BDE4B9258645ULL, 0x1539F29301369EFCULL, 
            0xA6068C19475BFC71ULL, 0xEB55B788A5C0164EULL, 0xDF5F107938EFA384ULL, 0xE6CFC20FE026D308ULL, 
            0xE56EF207CA28648BULL, 0xBF41D97759047EFDULL, 0x5D5D9A0FAF8699BAULL, 0x634A402784D91945ULL, 
            0x138EE4D831925395ULL, 0x0967A13D02BE6642ULL, 0x38DEF98781CB5C6AULL, 0xE5547F27E72B5CBDULL, 
            0x807A1018195A2079ULL, 0x7FA4A78FA1D7FC16ULL, 0xCECE6EFE0DF73143ULL, 0x4DF99195E9EEE445ULL, 
            0xFDA7D9E65703AF21ULL, 0x4DC0F2D31ACCE7BAULL, 0xB446D1E32632122DULL, 0x1E7251EE1DE0428CULL, 
            0x28E0E3BA069946B4ULL, 0x42DAEA6FBF6D389EULL, 0x593EDB497E363766ULL, 0xEAFF9852143E2FBEULL
        },
        {
            0xA44B29EC057F6A20ULL, 0x051E6424EB3E9423ULL, 0x4B0AE6490CDF484EULL, 0xFC74E37E77A234EFULL, 
            0xE37D9320389C1958ULL, 0xC5776B3A6B032023ULL, 0x7BFC41BC35B800CBULL, 0x4A7078589D6096D2ULL, 
            0x1B4F27C86873329BULL, 0xF6C34150B286A26FULL, 0xE46F6DC5AFF443DDULL, 0x98E2436EBEB8CDF1ULL, 
            0x634F28E798C72BD3ULL, 0x126A141DA4589B72ULL, 0xBAA29890D35F1323ULL, 0xF7FE9C815C6F4C58ULL, 
            0x4A93808B074FB303ULL, 0x49EBFEF586D6DADDULL, 0xFB2C5FDCBD748C7AULL, 0xD0BC45FF9D0325DAULL, 
            0xA2C6901820D3F2D7ULL, 0x020C952ABB3E8036ULL, 0xB3AD8C748B253B61ULL, 0x196BA59CF59C94A7ULL, 
            0x09510A38A028C904ULL, 0x3B5791FD1E36652AULL, 0xB8FA9C47985F4D4FULL, 0x764D63B985D2C995ULL, 
            0xA531EBC62D29826EULL, 0x4F1F1071CE3E111DULL, 0x6D0B78A96F9137DAULL, 0x2315F57775743808ULL
        },
        {
            0x93C1A64935B1F6B2ULL, 0x468736E7E7A949A6ULL, 0x36EED5BD8D98D58AULL, 0x6A073BAEDCA345C9ULL, 
            0x27A909DDD347773CULL, 0xE7F669AFF0208AD6ULL, 0x59D7711388B50EABULL, 0x0904D3A7A9BCDA26ULL, 
            0x42B51073229677E2ULL, 0xB0DA4702EEF1B735ULL, 0x62230D30B1A7055DULL, 0x4B9E56E2AB09EBCBULL, 
            0x52695A58F01DFC58ULL, 0x70389816EA2E69AEULL, 0x8E0F0D5791B50661ULL, 0xD700783A86F8AD03ULL, 
            0x01213009BF4950ACULL, 0x883F42DC07B82D2EULL, 0x32FAF050B3AF0D30ULL, 0x12FBDAD0DF00AACEULL, 
            0xFB29F37663E2F99CULL, 0x26238336C1662111ULL, 0x4D54DBAFA2AA4DA6ULL, 0xD3E4F0C18F39EE07ULL, 
            0x2E3CA70128D1AEEAULL, 0xE7E620A302707797ULL, 0xDD98BABF27B69B60ULL, 0x00F1E7EE3B26CD6BULL, 
            0x5EFEB88D3EFD7F17ULL, 0x8AC57B0B40E8733DULL, 0x6583471D47710D2FULL, 0x20509CE44A66C24BULL
        },
        {
            0x7EB6D3ACC868B5A4ULL, 0x3FBDF85D9220EC69ULL, 0xEAB41F597F2575C5ULL, 0x3AAE5D9B1081D1C0ULL, 
            0xD13CE781E632B551ULL, 0x9AD680D576FC0B86ULL, 0xC48CB9A5ACE5E279ULL, 0xD1E0C6A05F17CA50ULL, 
            0xD11DAEF2EE71AF53ULL, 0xC5B87E7CD79F2177ULL, 0x9867D61AB904CE12ULL, 0xA906507BF751CBF1ULL, 
            0x5414DAAD3817263BULL, 0xBBF2AD374DDFA853ULL, 0xD7EC8CAE7408A1EBULL, 0x975C998D72D3B6B0ULL, 
            0x94BE56B86FCEBB88ULL, 0x5377138B45461B75ULL, 0x4721262BECD06A73ULL, 0xC745592D9D3C427AULL, 
            0x84AD2EDEED0E306EULL, 0x0C9D2CB3C2F7EEC0ULL, 0x880ABB7164C83F71ULL, 0x4EF95B1EB7929C05ULL, 
            0xEE757CD42181177FULL, 0x6A0B399A8BA0F555ULL, 0xF4BE5511038E56C8ULL, 0x501A41B16C46885CULL, 
            0x532D1FA40EC35871ULL, 0x051544B9B002C87BULL, 0xE8635FBF8BCB13AEULL, 0x3E329BFFBDC02FD3ULL
        },
        {
            0xED5DE1E0B81E8E80ULL, 0xFEE638DA2B9C0DEDULL, 0xE58C7BA399269431ULL, 0x6DFCFE475D4B9F9AULL, 
            0x88DB6E33A12DDF59ULL, 0x310F37DA1EE55A17ULL, 0xCC8B8C0C66E310A8ULL, 0xAB9616636D54A477ULL, 
            0x87008A9E21785C56ULL, 0xAA9A74E99EE5A5C2ULL, 0xA74B560DE65EE4EBULL, 0xE579F9BB322627CFULL, 
            0xD837D80CAF896687ULL, 0x552A8DA2F04FF937ULL, 0xFB14DEEE4384E3D5ULL, 0xD25C41328A68350AULL, 
            0x5871ECC07CE9FFE9ULL, 0xAB7D5C99A3CC19CFULL, 0xBA815BA5DD1728CBULL, 0x3E8A7D15695181CDULL, 
            0xD4E1BC4CC7FBE0FCULL, 0xDB9AA2E036B43E66ULL, 0xDDFCECBAA0531361ULL, 0x8D09DD1321990A95ULL, 
            0x9F26F90AE75A9EDBULL, 0xD5C3CDE202068B51ULL, 0x93A6905642FB53FAULL, 0x5DDD192D0D4B9C0FULL, 
            0xF1D5BAA3C358A44BULL, 0x23E06C8E7C48D2B7ULL, 0x695BF058FF5B183FULL, 0x49DF659767F03C91ULL
        }
    },
    {
        {
            0x74E7185FD82DB261ULL, 0xBA810ECBE958209BULL, 0x8553C89D60120D67ULL, 0xFA8B95393D50AC05ULL, 
            0x62E74B8EE8978AC3ULL, 0x657C3A771CCFF1B5ULL, 0x4D300CD4911157FEULL, 0xF94BB64255300F23ULL, 
            0x380E2C58356BEFB6ULL, 0xB542EE0EC814551FULL, 0xF7F110A8DE22FC97ULL, 0xAEB6FF4D4E4C59A9ULL, 
            0x434FC49410A60B43ULL, 0x1A7F7172E852B394ULL, 0x1337056258D71B47ULL, 0x0E87986F9DE45264ULL, 
            0xB149D60B4059DE3DULL, 0x5CA7A02C7FD01AB0ULL, 0x3722351F2DF233F5ULL, 0x65D6181B6881FF97ULL, 
            0xB75B6D2B1A819D70ULL, 0xD332BDEC2298B68DULL, 0x68FA9BC11BC6B56EULL, 0xA876D5D305C8FD25ULL, 
            0xA6A1448FA11611B2ULL, 0x724F5DAA2D465E90ULL, 0xCCB66B734B29BBD3ULL, 0x8BEFBAC31C216D54ULL, 
            0x8A88CC242A4B9435ULL, 0xAE4B5199EC24214AULL, 0x11F4AF1BAA060DB8ULL, 0xEA2CA29239BB36F6ULL
        },
        {
            0x2CEC1B1A25B74F58ULL, 0xF18CB8FA0393E0D3ULL, 0x6E572D4634E45B68ULL, 0x1765FF0E1463FDB9ULL, 
            0x16DF29D756220AC7ULL, 0x7405EB467D4B05CFULL, 0xC7F985B615A2BC21ULL, 0xF28A511BD06FD417ULL, 
            0x2A6316B6481175AFULL, 0x0E7B36BDBDB7BBC1ULL, 0x35FE4D3EA7EF63C0ULL, 0xE4EEEFFD282EE2F9ULL, 
            0xDB211F913F5AEEE5ULL, 0xE8F1CBEC8A1F8A99ULL, 0xF32E296C5DB8C843ULL, 0x83050AF06A256CECULL, 
            0x32F51FFA45C0F155ULL, 0xA743AD4BF35F7C5BULL, 0xCA2D1D64127D4C52ULL, 0xE5FD7627547CD2A2ULL, 
            0x00EE964AD6A198EBULL, 0xC2A524ED2EB9D8E3ULL, 0x13D1EA30F95F5217ULL, 0x5038CD409274DBB3ULL, 
            0xA2BB0206C65A4E03ULL, 0x21136563E934CBCAULL, 0x98E2E905BAAF4858ULL, 0x6150AAE8D0BDC9EBULL, 
            0xB918BC85876DB4E3ULL, 0xEBFD637CE2ECCC35ULL, 0x2AB22D688F551480ULL, 0x1F3B678EBA1F4FBBULL
        },
        {
            0x1439846605EAFC98ULL, 0x4CE8E1FA1964D614ULL, 0x46CC948A0D60B12EULL, 0x5A27D9385F88B0CBULL, 
            0xD4AC2E509082B020ULL, 0xE8ED1C5028E48522ULL, 0xD4281A620FD8C9F3ULL, 0x035C464F14B95A5BULL, 
            0x120ADCCB7E9FF6AFULL, 0x004451E513FF1D6FULL, 0x8E3A750C2860954AULL, 0x87B320B3E3BA40A9ULL, 
            0xD7CE35273AE09AC2ULL, 0xF73C03D5ED5467FBULL, 0xA105C428BA6F1E37ULL, 0xEB956E3A1B5D65E7ULL, 
            0x76B21592A26652FEULL, 0x92B6B6467EF56548ULL, 0x4F37E323A5B8DBE5ULL, 0x8B4986B5D2DC5803ULL, 
            0xE3663AA70FC74843ULL, 0xC20824671D86728BULL, 0x7320F3FC6FCEED0EULL, 0xEF056192592AAB80ULL, 
            0x8DAD43F36C756DD8ULL, 0xF433D1FABC395728ULL, 0x0495DB3B24187DB0ULL, 0xAFFCACCE2BD55CD6ULL, 
            0x3663F6DE9CAF37F6ULL, 0xECBA46AB61FD4A6DULL, 0x4687D6A2C06809E5ULL, 0x1F8777F50BD9A2D6ULL
        },
        {
            0x264E9AF7875D98D6ULL, 0x670C0D6CA1D6F434ULL, 0x1AF5D6AB3265533FULL, 0x450C49916159C9B2ULL, 
            0x325E07836D2615FDULL, 0x5B4F545AAA6D268FULL, 0xE412C540D9C36A16ULL, 0x3C143F80BC48FF7EULL, 
            0xA6A1A27241A75B32ULL, 0xCD1969EA699E531EULL, 0xB6AC97059FD2C987ULL, 0x5B401C3D95116ED3ULL, 
            0x62E7D867B256856BULL, 0x5B6F5B3477666752ULL, 0x0B10E7DF5C7A947EULL, 0x00FCA3C7D6EECB2CULL, 
            0x8844B25FC469CFCBULL, 0x9A2B887C1539C78EULL, 0x98B85035124E0A75ULL, 0x732B60CBFA50CF05ULL, 
            0x107773E831B109E1ULL, 0xE426CE04D9052BF6ULL, 0x356F86970F6C22FCULL, 0xBE33C47EB9F9336FULL, 
            0xF95552E6F42065EEULL, 0x3052B7EE94CAA5A3ULL, 0x3C3DC9A7556696D8ULL, 0x5749212C44BCA816ULL, 
            0x0C9B2B3842CF8B6BULL, 0x5D340B9500F230E0ULL, 0x7131150FEE4504A1ULL, 0xD1A4BC0119A755C1ULL
        },
        {
            0xEE2ECA82124EF867ULL, 0x009B5A331AE7A3D7ULL, 0x1FECC6A5F1023619ULL, 0xA5C9C2990938C0A8ULL, 
            0x34E3D6B7C7B0D7FCULL, 0x27AADF725E41F597ULL, 0xD28FE3081ADBD7C4ULL, 0x6C744A23C0A39EB8ULL, 
            0x37AC8C67DA90D22AULL, 0x28E7C86717A65385ULL, 0x3215FF003292A38EULL, 0xC10C70AAB4883FBFULL, 
            0x0DF3945F7E357EB3ULL, 0xEFD5A401D9506652ULL, 0xCFB55B01604897A9ULL, 0xA30626C0080A842FULL, 
            0x51494819A760AA34ULL, 0xA8DF5BE316DA0FFDULL, 0x2DA6101437B7BE08ULL, 0xD52C013EAFA58236ULL, 
            0x03B1CF1ED90096E2ULL, 0x0AAE85DC0329BCE1ULL, 0x2B42BB92C4864143ULL, 0xD4DD7F937091DE31ULL, 
            0x1F1D3097567433F5ULL, 0x4CDDE0E04E1B55FAULL, 0x125CD8B2C54B7E98ULL, 0x9A05899BFD03029EULL, 
            0x336D54A21464EE41ULL, 0xA10DBD166816E7F3ULL, 0xEF3B04FE1CD404BEULL, 0xB5510B03970DA374ULL
        },
        {
            0x66E2E8564FE35388ULL, 0xAEA482E03CCA30ACULL, 0x5D0A7DE973AEB96BULL, 0xDA38F17D575976CEULL, 
            0xB87124B9312CFCA3ULL, 0x263BE7BB537207DEULL, 0x5F26069561DD4698ULL, 0x1F634736D3CF4A97ULL, 
            0x12929D40D15AE5EEULL, 0x76A57CD450F7AFD7ULL, 0x3D3D604F8560C6AFULL, 0x3D36C4D8A242C407ULL, 
            0x5564C9A60CC6F3C0ULL, 0xF8D018DCA4117583ULL, 0xAF1444024BF3B718ULL, 0xF9867DDAC623F9D9ULL, 
            0x862DD8F6DCD8F169ULL, 0xA5149EB8AD9425B2ULL, 0x1896101A2456FBAEULL, 0x98C8A429C8039074ULL, 
            0x0FC26484988AF6D4ULL, 0x13A946E877D62EA1ULL, 0x915D3DE1313562CDULL, 0xF60698736918EA59ULL, 
            0x4DA2F43327514D1DULL, 0x950AB763E8DE6732ULL, 0xF8C139855CB460D0ULL, 0xA79956DF5F4A93B9ULL, 
            0x3F087B7C906DE553ULL, 0x10B74EC769AF9491ULL, 0xB07E06EC54BF59B6ULL, 0xB97E5E367040DC14ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseCConstants = {
    0xDFCC706B666C034AULL,
    0x1EA4CABAB9E3B2BBULL,
    0x80C9DA2A25F75BCCULL,
    0xDFCC706B666C034AULL,
    0x1EA4CABAB9E3B2BBULL,
    0x80C9DA2A25F75BCCULL,
    0xC8C821893FF25D5DULL,
    0x7FA72E418057DD97ULL,
    0x21,
    0xF2,
    0x92,
    0x3F,
    0x1C,
    0x96,
    0xB8,
    0xDF
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseDSalts = {
    {
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
            0xB5F4BF3169427B5FULL, 0x214EB08CABD05BAAULL, 0x2BE34BAA030B2C7EULL, 0x38726A56DDD99E49ULL, 
            0xA8FDD1993B47F572ULL, 0x686CBE8851ACA95EULL, 0xC5F610F2C58D737FULL, 0x76105BEA7CDC3C3CULL, 
            0xC32505D83CAF0596ULL, 0xF529409581583FFFULL, 0x8508E8F7618AAB1AULL, 0x4B62B39D5DAE758FULL, 
            0x6C0DE6ACC9121D8DULL, 0x472D6FA757304ED2ULL, 0x44FC5334695B1713ULL, 0xF991A3007E315459ULL, 
            0x4BE1885F1F3B20AEULL, 0xCE6D2D24B4670AA9ULL, 0xA6F32E05C1C0EE0EULL, 0xD53E60953722C67DULL, 
            0xB942195C0CC1179AULL, 0xAABFCD627B1C4095ULL, 0x0B983FDD3D73A141ULL, 0xEFAB33C20837C084ULL, 
            0x24CC67F7C96A259FULL, 0x099377D0220042CCULL, 0xAD2D9CAF85C441A2ULL, 0x0CE697C015B3DA74ULL, 
            0x9683B7A60F9F5C25ULL, 0x9B7CF0EB6294318FULL, 0xEDC779F8360E3E9FULL, 0x78F1659F8BDF8CBFULL
        },
        {
            0x0CC654AB090E909EULL, 0xF5C54C5117CB3F0AULL, 0x6DB524FD0335B942ULL, 0x7A314B0786AD4A24ULL, 
            0x97DF0D75C55BC464ULL, 0x04A8E7C52468A62FULL, 0x17A438E06BC177B1ULL, 0x5130A5B7B49D482DULL, 
            0xB514BFB82C0D00D6ULL, 0xFB5C5606C11F6AD7ULL, 0x1464287506E73F2AULL, 0x631775F0CF88116BULL, 
            0x0C6E3C80B86E111CULL, 0xC97ADD5CECB9A31AULL, 0x66F9AD5FC21CB7EAULL, 0xAA2DCF7510C5F1C0ULL, 
            0xF56B835D2837CC19ULL, 0x072E6EF5F3F2FAA8ULL, 0xCB70DE898DA6CDE5ULL, 0xD81C296862F85844ULL, 
            0xC18B899A7EA9FE7FULL, 0x77BACBEF98E5F105ULL, 0x63EBA3284D433B80ULL, 0xDA967F3D0B601BA3ULL, 
            0x2438B5FF83B22D07ULL, 0xA621BA2A46D005A7ULL, 0xB50C59F93A8347BAULL, 0x8FD0550061562048ULL, 
            0x6DD78256E233CA42ULL, 0xF2F664B0A9DE0E70ULL, 0x34368A6A191942B3ULL, 0xB0DED26C518218E5ULL
        },
        {
            0x9D569032D4FADAC6ULL, 0xD8097A1504B1CA17ULL, 0xBC75818905F2AE2DULL, 0x65E96C6BAF7300EEULL, 
            0x27D95827B28C4BB0ULL, 0x9ED5A169666521DEULL, 0x9DCD5595AAE73588ULL, 0xAF481518F61D892DULL, 
            0x22847D27981AF83FULL, 0x54884669C9609A82ULL, 0x97675D4F7630967CULL, 0x877103BEA069663EULL, 
            0xAD4327E98C7A87C5ULL, 0x260D6DC5E8BD1F77ULL, 0xAA63DE4016A50500ULL, 0x8D4731D8C7C382AFULL, 
            0x9F6EE1F19A680FB4ULL, 0xF6B6564E1482C34BULL, 0xBA0E656006FD1C9DULL, 0xBA50256708FA74D6ULL, 
            0x9D264F3817914006ULL, 0x5D34FB5E43476100ULL, 0x1542A8DFE0184850ULL, 0xAB588A3B04833314ULL, 
            0xB547F7773DD3954CULL, 0xC0596F5832533F62ULL, 0x4D5980E8939F7572ULL, 0xB0FF203F4AAB4D1DULL, 
            0x68F488D74E18AFC5ULL, 0x8004A104E2E93286ULL, 0xC981E8B4826C86DBULL, 0x6C8034D0E15AD653ULL
        },
        {
            0x8150030E8D81A034ULL, 0x6A34B65FE802556DULL, 0xEF756235A338EB9BULL, 0x8672FF81ED744C0EULL, 
            0xDEEE5FBE688F81D2ULL, 0xF0E68E433359CA01ULL, 0x17F689BF028D9BBEULL, 0x32DFBC2ACE6F268BULL, 
            0x9A751CF568360B60ULL, 0x73599EBCFB27CEADULL, 0x33C395281F73D94FULL, 0x6456B1B3B66C7E3DULL, 
            0xAE449927F14755CAULL, 0xD81FDDACA457C7CFULL, 0xE72E3F5DADF8906AULL, 0x08341D37AFC24135ULL, 
            0x08133020D3A3D999ULL, 0xEA04BAF0C91DC223ULL, 0xF751FE5309D40D60ULL, 0x6B7D401F00AA98DCULL, 
            0x51F18E12F8A032EEULL, 0x579DCFA434B5862DULL, 0x9EF03436DE19B0B0ULL, 0xD8327E631DDDE8F4ULL, 
            0x5C58A36D7C966078ULL, 0x820FA2444459605CULL, 0x8D74B3A7DF850E39ULL, 0x971F8EF6CD7D7814ULL, 
            0x214EA306FD6B64D3ULL, 0x65306331AB965914ULL, 0x4E6BE3C34A578F28ULL, 0xDCDD4B5205476075ULL
        }
    },
    {
        {
            0x50D0E76AD5EBCEE6ULL, 0x8A58352A6DD19611ULL, 0x7903E0832A38AE20ULL, 0xA0B7CD232098D2F6ULL, 
            0x395B11CD868EB5C5ULL, 0x386DDE583F7F3D2BULL, 0xFFD9067CFFD2F971ULL, 0xED2431E575AAF2E7ULL, 
            0x064AB52792CEE256ULL, 0xD89F8B31E0596DCCULL, 0x33F8704B168E71EBULL, 0x19B585B7CC966A5FULL, 
            0x2A785169ACA5CE4CULL, 0xE6178A33AAEED04EULL, 0x51F89F66B0975240ULL, 0xD972C8E33AE814FFULL, 
            0x470EB9E5C123EDF1ULL, 0x799246667A5793FAULL, 0xB892424A29BB5B6BULL, 0x74E076D30284B0ECULL, 
            0xEA91280ECB172501ULL, 0x8D22C5257D1B311DULL, 0xFEA9343CD22DC638ULL, 0xF7D25DB5DB69A13FULL, 
            0x96815D11C875094EULL, 0xD142D84E642F51EEULL, 0xD49AAB866993D1AFULL, 0xB22D6A5574C9CA91ULL, 
            0xCD5F7276DCB04102ULL, 0xD599B7C69523CEECULL, 0x7FD5486EFD3A21E5ULL, 0xB867C17DAB7EF612ULL
        },
        {
            0x2EEA8EF7CCB94A03ULL, 0x9694F3779CCFBA1BULL, 0x27AA8EE7EAFDE752ULL, 0xA1EE6FEAD1753B58ULL, 
            0x05D76A5C1765D1B9ULL, 0x9A50276D4503F5BAULL, 0x48EFC3EDE82EFA0CULL, 0x195AAEB63F8D0792ULL, 
            0x4F4C128B04E02AC2ULL, 0x8B2D0381B9F8077AULL, 0x31C57C1FFDBFE21FULL, 0xADE0B6244BEE58EFULL, 
            0x62916C15E2F68A97ULL, 0x93766320D2DDD915ULL, 0x8A158D3F1EC623B1ULL, 0x6C59804F9289C3A2ULL, 
            0x48E7100D9BE149E8ULL, 0xC764285329F08EAEULL, 0x0A2561CE5E375280ULL, 0x319E8008BDE5FB86ULL, 
            0x774A3621624E90FBULL, 0x4C2A3E97842429A0ULL, 0x9C62B861450C1436ULL, 0x7FD3E4F5EEFC9472ULL, 
            0x94DD8309DEA16196ULL, 0xA3C5CD22D4CC59F9ULL, 0x4E79A595FDE680C3ULL, 0x848D64089FDF2033ULL, 
            0xF16C17138A478F63ULL, 0x2CD8BECC20B3C3F0ULL, 0xFC05B63285BFDC54ULL, 0x1B03E9A898553055ULL
        },
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
            0x6D0CAFB3D2958EEAULL, 0x9950F2D2630EADE6ULL, 0x4CD9ED596C0282F5ULL, 0xD78BD95EE2D44574ULL, 
            0xA1E6E43C5ECF595CULL, 0x9EB32A6B1E7BD87CULL, 0xC7C348BE6C78EA81ULL, 0xD0571D6171C49C06ULL, 
            0x268AA557BB525EB5ULL, 0x5BD1FE939FD56683ULL, 0x472F1491D5F813D5ULL, 0x1F4D04093B06F742ULL, 
            0x768D8C0A71B3F6E1ULL, 0x31F26688D2D19EDBULL, 0x88B18D627BA97885ULL, 0xE1F3C590847B5D3DULL, 
            0x046A6F6C1BE5E06AULL, 0x5C8C74E601061FCDULL, 0xC8C98C494D2F0ECEULL, 0x312B364E7039F910ULL, 
            0x2BA7CA4C3482C07FULL, 0xFF8B2E292D84B3C1ULL, 0xC9D922DB4D5BE67EULL, 0x06A7698B50517F4FULL, 
            0x6B11B6DC2990A588ULL, 0xA192D9E5CCB9536DULL, 0x978B112155D7B59BULL, 0x7018C648385A23E0ULL, 
            0xCEB809FEBFF5054CULL, 0x0DB50E12A26FC635ULL, 0x2E58C4E6F7E714E6ULL, 0x295CCA021A955FB3ULL
        },
        {
            0xAC3ABCB3375B6E96ULL, 0x50EB9FD5F799A4B0ULL, 0x924C45B7ACAE334BULL, 0x945EB55AED462A02ULL, 
            0xF5E7D3CAEDD590CCULL, 0x02E61D7FB3DE43EFULL, 0xEEDAC3479FB15477ULL, 0xB37B260C4A37A7EBULL, 
            0x60FFC5B7B60723A6ULL, 0x5366075F3C7A3B00ULL, 0x0D630DB6847B41B7ULL, 0xBC795F0EAFC7E6C1ULL, 
            0x567B9FF78B3278FEULL, 0x7659507BC36F6CF8ULL, 0x58EB895EA5651A40ULL, 0xC9A454F689C9285FULL, 
            0x542D75FAD6E90392ULL, 0xDC0D0594468BB7F5ULL, 0xA157A53BEA7B2FBDULL, 0x11699DAA6F9AE7C5ULL, 
            0x7C231D97EC7B5D5BULL, 0x0F90B342F749A268ULL, 0x0EBBB11FDA48A3FFULL, 0x17DF19EF061E6E9EULL, 
            0xA1BB6F2907C07699ULL, 0x44592621E253AB99ULL, 0xB0B1C441325D0EBFULL, 0x9C6CC1708E1E0C48ULL, 
            0x808902E97355AAB4ULL, 0x3142D45814B8D8F0ULL, 0x68EF1A7A106AF7B8ULL, 0x55E19F697201B5C0ULL
        },
        {
            0xF50E535DF5CA308AULL, 0x23388C1EA8DA7F7AULL, 0x32FC1DAC3D72CBE4ULL, 0x43EA18019B5C2018ULL, 
            0xB1030DA6674A546CULL, 0x7864EF318A4A8B3FULL, 0x705370FE289386E9ULL, 0x9E3D2D08E6EF7D25ULL, 
            0x504A8B9303DC00F5ULL, 0x604A33C76593D0AFULL, 0x1AA5B3BFCDDE02E9ULL, 0x65B4AE34A27A9541ULL, 
            0x5AA1B4E9FB25C373ULL, 0xF65F962519F1CA4FULL, 0x54150C4370A802ACULL, 0xAEFB19D22673FBD7ULL, 
            0x3866E9A37427D90DULL, 0x0874AE51B683C9D9ULL, 0xBB0ECFFF6FC8CAEEULL, 0x89CE4114D0C053D0ULL, 
            0x5866058DC25AF485ULL, 0x8410491EEEFD05A0ULL, 0x47CB0A45FFE127B8ULL, 0x11C6A46CDE027C00ULL, 
            0x79D5CFE4EFE13C14ULL, 0x540238B72A6ACD44ULL, 0x6BE0D0C2C4C62042ULL, 0x78C6497E363C2197ULL, 
            0x716D06B1FD4C8D2FULL, 0x6201EB51F3A159AEULL, 0x7AEFAC08F55F58D5ULL, 0x085690CABCD5F9CCULL
        }
    },
    {
        {
            0x86FBE9B3083EC716ULL, 0xC5FC27EF5F32056CULL, 0x46B801B6D4EA55CEULL, 0xC0A5686F2411074DULL, 
            0x855396706779F925ULL, 0x3D764D82A0322A8BULL, 0x048FD1519F9D975DULL, 0xFFB1B444E660EBA1ULL, 
            0x1E58199D04ED07B0ULL, 0x0913CAD36D486AE7ULL, 0xFC7E8ED2BBD334F0ULL, 0xC19E0A9A3190CAA5ULL, 
            0x1522112E7AB6B6ECULL, 0x421DAD102C2427D4ULL, 0x6143AFD4CE466785ULL, 0x81A2BD9EBC62583CULL, 
            0x9154CC927CA0B62EULL, 0x5FDA1D6228FE694AULL, 0x2033FE27B6A8E80BULL, 0x36D9E0DCBF8D54D6ULL, 
            0xCD983E147658E1F3ULL, 0x9E0EC5D7F32A27B2ULL, 0x74D7453E0BEEFC1CULL, 0xD173901405144984ULL, 
            0x121E26705820DC0FULL, 0x413A0AB56DA0724CULL, 0xADBC4C5BA27053EAULL, 0xF0A4CC37C5AF5B6DULL, 
            0x57388A24455E90CEULL, 0xAC4AFBFB10A55919ULL, 0x3AA54FED4582ACC9ULL, 0x1D3408C322E5FC4DULL
        },
        {
            0xC411F3DAF5C56E78ULL, 0xB5CC0544C73168E5ULL, 0x9453FD561FC2D893ULL, 0xC28EDC9C129F9EFAULL, 
            0x58FBF3F24D39F8A2ULL, 0xBAA7ECA9EDB86630ULL, 0xD8DB51E255EFA2E2ULL, 0xA1BB05BE1845181DULL, 
            0x4A0EA4B07B1CEFA4ULL, 0x62D427F70668A567ULL, 0x4BCBE0E3E9A80F2AULL, 0x7B237C7E198B266AULL, 
            0xCC451AFAD6F46087ULL, 0xDEA6FD3C48821806ULL, 0xF60BE7094D48EF69ULL, 0x3583C030658472CDULL, 
            0xE15B1F70B427A3B0ULL, 0x366B990B9E38D01BULL, 0x13DA62D5C09C92CFULL, 0x67A06CC36DB0856EULL, 
            0x974D4237238C8D72ULL, 0x7CA45FAC6570DC69ULL, 0x56DC99BBA29CDCB2ULL, 0x1875956776016AA0ULL, 
            0x1AE6EDF4FF30E7BBULL, 0x5FCAED76A81456C7ULL, 0x62F4710F537D35C4ULL, 0xA3CA3EF3C2DB4349ULL, 
            0x28E60BDFDEEAEEFEULL, 0xF1C6A2C2F55B0B6EULL, 0xFF5EC8331F4E4E99ULL, 0xE7EAFA9E387D748DULL
        },
        {
            0xA9DF6274C170227EULL, 0xE990E5F892228C9FULL, 0x543B5E561F6B8536ULL, 0x86B824CD8E1C16F1ULL, 
            0xB9DD873917A798B4ULL, 0x1AEB0C766903F501ULL, 0x872DEBC17B135AB3ULL, 0xD09DDAF6A4B31B9DULL, 
            0x334EC4CA7D97B634ULL, 0x7EF8EEC1B480DA68ULL, 0x3C3E3AC20119878EULL, 0xDFA5E1518CD58C03ULL, 
            0xAA44326648A0959FULL, 0xA84789CB6610C92EULL, 0xF3E62B55231AA397ULL, 0x8A8A4A8F05211E98ULL, 
            0xE507A6CE7567B993ULL, 0x60C1C37CBDBB56F6ULL, 0xC4C3092A29072626ULL, 0x1E235476F134326FULL, 
            0xCDC850079C1A064DULL, 0x7D8E4D6278C0CCFDULL, 0x94F43E3D16E0B76AULL, 0x0EA9549C97B4B4EFULL, 
            0xC1DABD039F9BB45CULL, 0xB869FAA98833C1D5ULL, 0xDB8766A0FEA3B9FBULL, 0xC3530648592B242BULL, 
            0x8C9EE35231F81346ULL, 0x0C72FC2FF80A3DFBULL, 0x85A27D78DEACF4FEULL, 0x12719A7DE5022650ULL
        },
        {
            0x00197188A48763F8ULL, 0xE200C1F3173021D4ULL, 0x2C966CBC2BF24D3DULL, 0x9CFA9A489E4DA6B7ULL, 
            0x3A4C3E660505AEC6ULL, 0x77068885C45B7210ULL, 0xE30AD9607194B7F3ULL, 0x451CEF206BAF1811ULL, 
            0xCF57CDFE33A14CE2ULL, 0xE786F09C17F5186BULL, 0x51C7AF1D8ED17B7FULL, 0xDD11E787F6132013ULL, 
            0xC8E23086662627AEULL, 0x0BAD4C412D101D61ULL, 0x1E68A7973ACD3293ULL, 0x94A8592CD94DF12EULL, 
            0xD6459FAEA3C9601CULL, 0x91A9E4855A7D8D31ULL, 0x8C88F88D9B6A0009ULL, 0x3E5DC9E5538928D1ULL, 
            0x2C5B9E1BE4ADA15DULL, 0x75D9DBDD4856AD41ULL, 0xE73F993AA8E1DD97ULL, 0x541AEBBB90D4F9A2ULL, 
            0x420274A617006AACULL, 0x961975534138DD8BULL, 0x342BF9098C85CD9AULL, 0x2DAC75D1EA339B7CULL, 
            0x4E9E09D11804B00BULL, 0x3C6AB2C111D8B330ULL, 0x9FA046066AB9CB50ULL, 0xC73DBC65F2110C04ULL
        },
        {
            0x3D615E4D02356305ULL, 0xEBC0189BE34434DDULL, 0xEA2F4DEA8C3D8B44ULL, 0x2D0148A1F3199444ULL, 
            0xBB78A2F7DDA66352ULL, 0xBF95B55519AB640CULL, 0xF52213357BDF8DD0ULL, 0x01E70C27F3CFBF3DULL, 
            0xA2356294F45C85FDULL, 0x8170932C47D83228ULL, 0x39949CC0B3FCAB53ULL, 0x7B7CCAF03C8EF284ULL, 
            0xC84ABBB1BDFEDD25ULL, 0x025CB0835267BB80ULL, 0xD1C43244E7516FA1ULL, 0xEED55EFC9820A6C4ULL, 
            0x679AF3FBD97750CBULL, 0xB933B00C4B64433CULL, 0x173FB6307EA197FFULL, 0x66C5C03F33C766F9ULL, 
            0xC8C6203FF0C5C969ULL, 0xBF732C5E2574911DULL, 0xF256C9EC2CBADCD2ULL, 0xA936F7BF84FB5D28ULL, 
            0xDFBA9AF4E97D2AADULL, 0x4A962E1CE1F95144ULL, 0x4B60A8DDCB4E9971ULL, 0x9B2F49BF92A385B7ULL, 
            0x4C363B87051C7DACULL, 0xA42C577FA56ABBCCULL, 0xC009C71C829FBF3CULL, 0xB8F5036F77970AD0ULL
        },
        {
            0x0DDF826C1EF57286ULL, 0x8AA4952740226A9FULL, 0x8E76E21F9272AD3DULL, 0x25B133DEC3EA0512ULL, 
            0xD1D36721FCD809CFULL, 0x5A259751AACB2F58ULL, 0x7893A4CE62C7CDADULL, 0x3B123B3B5EF4BE83ULL, 
            0xE8E6E4FDED315009ULL, 0x6E8ADCFC8C369AAFULL, 0xB41B06B57EA7718AULL, 0xABC5E15D93C71342ULL, 
            0xB29C6C9F13D00CF1ULL, 0xCC68BE02C12C6068ULL, 0x135D5C43D4F7B0E2ULL, 0xDBE8DC778F9C4AFBULL, 
            0x4E86AFF06CA58B60ULL, 0xB48CBE10FA023BD4ULL, 0xDBA6AEA43310CB53ULL, 0xAB923F8F5D8D5291ULL, 
            0x21ECDAEAD5764263ULL, 0xAA15720D6F96DB8DULL, 0xADF90194B0722EE6ULL, 0xC1630708756025F2ULL, 
            0x56DCB911378FEE96ULL, 0x90F089881C15F175ULL, 0x38BB578C007EE0ACULL, 0x5D6C07108B1AB408ULL, 
            0xD181024AB13E8AB3ULL, 0xEB8989AA5426E174ULL, 0x0F0357A967C55E5CULL, 0xC2DAECCBE836A12FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseDConstants = {
    0x839952D6A9BAE871ULL,
    0x1C639D9907B58C7AULL,
    0x3B0A277F3A062957ULL,
    0x839952D6A9BAE871ULL,
    0x1C639D9907B58C7AULL,
    0x3B0A277F3A062957ULL,
    0xB91DEDFD7A74A0E5ULL,
    0x72A003E236EDAA16ULL,
    0x7E,
    0x8C,
    0xCC,
    0x8C,
    0xFF,
    0x33,
    0x34,
    0xF0
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseESalts = {
    {
        {
            0xE98BB3DAA20DD5CDULL, 0xFADF64560E312D97ULL, 0x58110D8B3B7F5E1CULL, 0xF9BD4460E4AAD9B0ULL, 
            0x12EB3D73B73EF07DULL, 0x4190BFE7C46084BDULL, 0x59D532AB6DFF7B60ULL, 0x499F8833716FD39AULL, 
            0x65ACDCD9B394BFD5ULL, 0xD9B7FFCAD7904C3DULL, 0x6F2A6D9175CCAB27ULL, 0x8ECAA3060A98F99BULL, 
            0xBBE383DF5C889E6EULL, 0x5DBF94D9BBA34F68ULL, 0xDEB5B955BD59E9E5ULL, 0x3F7E33A2F3BB314BULL, 
            0xDC44324ED4EB3EDCULL, 0xCD8FEAD07EE9E5C2ULL, 0xA4CCC0795FEAFCCBULL, 0x1394863DD74CF253ULL, 
            0x0F5804F61AE2F470ULL, 0x81D2A3BDDA7D0ED1ULL, 0x85CDB414519AC2F6ULL, 0x54EFBA64B1F4C919ULL, 
            0x16FBA6CBB2E63256ULL, 0xEBEC331932F172A7ULL, 0x2078C51EF829B14FULL, 0x1FB1448AEDB05049ULL, 
            0xC8B2CAFD844ED955ULL, 0xA73652F5DA64CCC0ULL, 0xEEB73156074F22B9ULL, 0xBAA82BEBA9B589F7ULL
        },
        {
            0x866A63124D0B854BULL, 0xD8E52ECB5E00940BULL, 0xAA2733E420D0866FULL, 0x42459EFB1EC4A1BFULL, 
            0x6963B88846806673ULL, 0x90620F3D60AE16EBULL, 0xA5E3E4FD7467BCEDULL, 0x4CE0438BDDF65B51ULL, 
            0xBB0D7170CB62F824ULL, 0x793D880457CC0B81ULL, 0x8630C1D500DEA96EULL, 0x2B54BFB974A72CCDULL, 
            0x4214A827006E6F47ULL, 0xCD0425D774E3D6E2ULL, 0xAAA2B58858F84203ULL, 0xD96A60EA8C5C66F8ULL, 
            0x0A438EFA074F36B2ULL, 0x897E5B3175F01C78ULL, 0x36564875E0A4AA60ULL, 0xD11287F5B1D9FDCFULL, 
            0x7B33683601894020ULL, 0x48D44467E5E85E03ULL, 0x3CCA964628C1B749ULL, 0x5A93D9D0DF7C65FCULL, 
            0x1AB03735BB82AB76ULL, 0xAB79D90BC55544A5ULL, 0x3F2AD6B7EDAF23A0ULL, 0xBEA77FEF2B8125CAULL, 
            0x63C95ACAEF212732ULL, 0xBADDB7E04F0C8EBEULL, 0x62ED5CF36010CB4CULL, 0x2BF82173BF02815EULL
        },
        {
            0xF42D3EE6DD963CC4ULL, 0x466215FEE24F00EDULL, 0xE956C2E8A100F048ULL, 0x4C128D335590206BULL, 
            0xD52CC4298FA27F1EULL, 0x6BE89F28DF9E61FAULL, 0xB6BE8B9633077246ULL, 0x16CBF8A5B7E12A97ULL, 
            0x93B154774014BFF3ULL, 0x7B86FF49CF1E3DA1ULL, 0xC96A29DC809200CEULL, 0x19181F70E7DFD7CCULL, 
            0x617C35E0CCCCBA5DULL, 0x280843611F3A1CD2ULL, 0x492996152C43FE93ULL, 0x813AF934CDA2AAE7ULL, 
            0x4136D52F1E90F6DAULL, 0x09510BB65EAC02ACULL, 0x00D9A5736AF1F9F3ULL, 0x3A5F5D555926FB42ULL, 
            0x403D151A6C66DC67ULL, 0x9461FB11C5E4DE4DULL, 0xDBC3B73145D0450DULL, 0xDF734CC41FDFA084ULL, 
            0x6D2D9C17DA214073ULL, 0x8F82CC1AE77EBFEFULL, 0x2A924F8C529A209EULL, 0x5DA85F86E7C43DE3ULL, 
            0x8BAA18EDBC11A7F0ULL, 0x02E1421DBE20616DULL, 0x1C0368D2B4B3B84FULL, 0xE5859467F28475F8ULL
        },
        {
            0x99EA64CDEF4F3078ULL, 0xBDA49FB575B14250ULL, 0x7EF1A75D05A1836EULL, 0xE37A0D116BF1CA08ULL, 
            0x73249DB1FA0A7DA3ULL, 0x6815EF19D0E2DB46ULL, 0x9F2ADD1B6373BF09ULL, 0x116598EC84802C11ULL, 
            0xDFDFCA188184EC74ULL, 0x9EEDBD3BA56E7A84ULL, 0x5F2783BA38240609ULL, 0xAFC8FDB96A2C2428ULL, 
            0xDD10D146A7989080ULL, 0x2F9A9D4EAD0122C0ULL, 0x346BD5771E448425ULL, 0xA7A6A5A5AD187FEEULL, 
            0x0BE0655A8AF50F08ULL, 0xAA9F44F5E039A2DAULL, 0x8F79FA67B9522F0BULL, 0x90CDF9BB82E3108DULL, 
            0x5B77C24AA38B6473ULL, 0x1F51722A4F71EDCEULL, 0xCE46916156798F64ULL, 0x1AA91979B90E85CAULL, 
            0xF4C62A12A8E4BA8FULL, 0xBC309D89AF8E10B4ULL, 0x50C8EA86F151B5C0ULL, 0xC3990FC629B78EB6ULL, 
            0x78008E257C85FB95ULL, 0x33D3851E91A16C8FULL, 0x41BF775E7F6C5162ULL, 0x15D62B0517466779ULL
        },
        {
            0x10EA78E3D7BB90AAULL, 0x2CECFF92B9EE0CC4ULL, 0x7701A82169A71A35ULL, 0x9B62622EDCE62ED5ULL, 
            0xF7A515479DD3A902ULL, 0x5FC52BD8677C728CULL, 0x4B45881EF4EDF163ULL, 0x0FBDFDEE83ABE61BULL, 
            0x10BB0878B8A4BCE9ULL, 0x0DCA00DD8242968AULL, 0x6BE3B8C473BE7BD8ULL, 0xBD2F3626754FA4B0ULL, 
            0x7FE474E2FBC887BCULL, 0xC6480C7A3450A336ULL, 0x1F9A1E05AC8273B1ULL, 0xA1339AE591B408D2ULL, 
            0xD17F4661DE31C1C6ULL, 0x8F29FCCCDBF09C9EULL, 0x08D043438C0D3BA5ULL, 0xC0DAA4B74CAC0CE0ULL, 
            0xDA1AB1E0A7CAD575ULL, 0xA5B59B146BC228D7ULL, 0x6B32634DFB1D7BCBULL, 0x3B72819AC3C3827AULL, 
            0xD8709CB81AB616C7ULL, 0xC0B020BC459FBC73ULL, 0xF983FAB49E3E9D71ULL, 0x64BF0FE36D4015D5ULL, 
            0xF5AB68C722E47FF5ULL, 0xBE8637C57ABE1697ULL, 0x425BCCB062A50F5AULL, 0x17CE4DFD0C44F0D4ULL
        },
        {
            0x4541BD74D51C69C2ULL, 0x6C914D3C40799649ULL, 0x2CEBFD8B16422824ULL, 0x576C9D0C21333D16ULL, 
            0xB00C2919155B22F8ULL, 0xCAC9DE8720AF0101ULL, 0x9248014D650FC59DULL, 0x78AD87CB1857A3D9ULL, 
            0x283FFB6D9330581DULL, 0x866778DFA368E498ULL, 0xB7A16833625D5805ULL, 0x0BBFD2DC016CE63EULL, 
            0x615D62C6E324D073ULL, 0x74CE846CE0406885ULL, 0x8CD90F747263E31CULL, 0x4658C28C595AC1F8ULL, 
            0xB981399928037A59ULL, 0x3303052770C42A91ULL, 0x0E433F6E534F369FULL, 0x3CBD2617A032746DULL, 
            0xF8AA0871D39C2DEBULL, 0x9DDE593CB5CF9996ULL, 0x0AC13A646DA79C9EULL, 0x0AA3303A451F5D5EULL, 
            0xEA4BD9EA29E61E30ULL, 0xEA676D834604E96EULL, 0xCB376C15FC1550CEULL, 0x66C837A829582B01ULL, 
            0xD012A30FF945A518ULL, 0x26E11D17BA894A71ULL, 0xFC48F82136D76DE3ULL, 0xFE586FFBDBE3CB07ULL
        }
    },
    {
        {
            0x38248EBE0BAB80ABULL, 0xCA0D5328695B05B6ULL, 0x2C2EEC3ED95E8EF0ULL, 0x197008B0DD335170ULL, 
            0x251C590F3D8A0653ULL, 0xBDDCC5A5DB0BEEEBULL, 0xB6D1B783E30D08B5ULL, 0x2D42002351D3B279ULL, 
            0xAB123E381E5A6EDAULL, 0xFB973D6D9AE50043ULL, 0xDCE2F8445181D013ULL, 0x3EF000FD6AC8CFEEULL, 
            0xF1B8B542A42168C6ULL, 0xCE14CB0743D3E726ULL, 0x0B327FBEB333409DULL, 0x95AF51E6C52D5155ULL, 
            0x75E7138F6E054CA0ULL, 0x9F7AAB5B39CB685CULL, 0x1D42A168EA7C39A7ULL, 0x8CAE7A5D8001BED0ULL, 
            0x9C1DE4276AB5F40DULL, 0x69C93B1E9C54A032ULL, 0xE0EA1E9C485839F0ULL, 0x4E794103FD607449ULL, 
            0xF8B56FDAE291E0E2ULL, 0xA1A21CBD6DF33330ULL, 0x594F4C1A2B89889EULL, 0x9C2387F9F2F9FAF0ULL, 
            0x1627C58CE9128141ULL, 0x69A751245E56E9F4ULL, 0x07C582915000503DULL, 0x209BABFEF279CCA7ULL
        },
        {
            0xB5E38CE8D7D53390ULL, 0x0F59B04F2C808027ULL, 0x463154DA2AC909A2ULL, 0x1918C90523B45ECBULL, 
            0x55102A8368943E9BULL, 0xFE9D9652F68B617AULL, 0xD55735A08B0D14BAULL, 0x5952B00012930103ULL, 
            0xF552EF09567B6F98ULL, 0x01D42F24ED5307A1ULL, 0x01E06396215B8E79ULL, 0x3A2E4166B0F3C829ULL, 
            0x7B1928B8AB4F3EB8ULL, 0xBD5D4685D274EE5EULL, 0x90A3061EE40E2248ULL, 0x16BC017C23B367CCULL, 
            0x7403A56FD5D56F7AULL, 0x80024E79488C74ADULL, 0x254F7EBC6E0C1572ULL, 0x55B04AB70C8CA565ULL, 
            0xC607EC77DEC6C1C4ULL, 0xBE1FF8C93DEFBA3DULL, 0x2B5EE4721BF45621ULL, 0x516A139A03014751ULL, 
            0x9E066FCA66902386ULL, 0xE70F86118FC33C00ULL, 0xBDFF37D9D9446445ULL, 0x44CC0ADF4D7A0D92ULL, 
            0xAC6587D98C5FB807ULL, 0x6AF070498A4DD196ULL, 0x20D262EE9B1290DBULL, 0x11D5C7C6E56DA952ULL
        },
        {
            0x4A881BD95920FE13ULL, 0xB6DD5A7300F63187ULL, 0x19AE4455B73D463FULL, 0x2ECD63E606C5528FULL, 
            0x4D1F2791C1BA8504ULL, 0x75660DDCD6CB5F19ULL, 0x699137AE63A0FDDCULL, 0x5DB0BCA6ECE42A72ULL, 
            0x4F6877F1AC637D50ULL, 0xF94258586A7D6CA0ULL, 0xEE0A926AD0FCDCC7ULL, 0x155260C729BECFCFULL, 
            0x529F478F2A39AE10ULL, 0x859D7D61C0BA9FC2ULL, 0x807BC4F66C9A9678ULL, 0xBE420BA5F871E322ULL, 
            0x6C252C19A120CF1AULL, 0x1AFDA0A67F9C013DULL, 0x93382AC7858CA8E4ULL, 0xF53CB4B78A405886ULL, 
            0x4BAD6E9CB80F03E0ULL, 0x2CBA0F635B55A195ULL, 0x9CCC41E1A68BFA5BULL, 0x1BC378D7AA2BDAECULL, 
            0xBD3A6143E5271671ULL, 0x091C7717407A2999ULL, 0xB823BA584D45724BULL, 0xB708AAC26A1BEFA0ULL, 
            0x7CDCB5DADA495CF5ULL, 0x742B1B7C8B99E2D8ULL, 0x99580F44B1C00E4DULL, 0x28857A4B3D9F74E4ULL
        },
        {
            0xC2B62A293C45B634ULL, 0xF701B92567CA428CULL, 0xC3322DC0ECAC9F87ULL, 0x531C7A616F12FEDEULL, 
            0x541ECC20B72DFF0EULL, 0xDECD28ABD00DEDB7ULL, 0xE2B88F4134130206ULL, 0xE19D501AE6423081ULL, 
            0x506F3ABBE1F3A74EULL, 0x63515428BB1A54A4ULL, 0xA186A9090D2796CCULL, 0x7B34D935D0D3A764ULL, 
            0x89C2A0D969A400B2ULL, 0x7A001771D5BF54FCULL, 0x9CDF08A0CCA22824ULL, 0x8B59B0EB34D6C138ULL, 
            0x80D395D6B4234761ULL, 0x2F1C6EB2D5AAAA31ULL, 0x5EA0B807A5EAA6F1ULL, 0xF1E8B4614139AEABULL, 
            0x7921C2FA649D10F2ULL, 0x75740AC696DF3400ULL, 0x87CAC1ADB75EDCE0ULL, 0xA5ABD1FB40CD09ECULL, 
            0x6924A317612BEAF2ULL, 0xC88019B918342064ULL, 0xA15ABF9D41845B37ULL, 0xEB8A431B2347772FULL, 
            0x0935856AA0D4C253ULL, 0xE761DCCCFF274178ULL, 0x629DCC2C7709C1E5ULL, 0xF2BE85DEE974D1B3ULL
        },
        {
            0x0EAF4F4AD956141BULL, 0xFE9AF478CF382934ULL, 0x4C9E89FC353550DBULL, 0x20BA73F36EA762D3ULL, 
            0x0B5DB2953B4B8A4AULL, 0x0456B865E4121FEAULL, 0x75349E73D0C58BDFULL, 0x9CCB413E786D6FEDULL, 
            0x71D96466C9D67B9CULL, 0x7FE4CBD2140E999DULL, 0x8F114BEA4A5FA131ULL, 0x95028F1BA3FCEEC7ULL, 
            0xFF4AEE165670E56CULL, 0x64F01EE71028F2F2ULL, 0xCDBF8B77059B3591ULL, 0x1F33700AB4FC675CULL, 
            0xA2816D6C1F41F95CULL, 0xC570A6DD93D4EAF6ULL, 0x8D5F30F7BBF7B68FULL, 0x28991FF2CC69130BULL, 
            0x2A07B2713D3BD78BULL, 0x3489CBAE81B5D7F1ULL, 0xCB0D2540FB91483BULL, 0xB052B76B688A1881ULL, 
            0xC1C2769FCB6EC7EBULL, 0xC98503AE81537750ULL, 0x159418AA5AA1014CULL, 0x128CB40F293C06F7ULL, 
            0x6A9E1EDC3CDB51A9ULL, 0x897D12D8F651137CULL, 0x266C845DA8C754A3ULL, 0xF13CBE6AE337B942ULL
        },
        {
            0x5CC0179218170D3CULL, 0x45F13FF4CFBE36FCULL, 0xB2A7DC50C3CF041AULL, 0x7580C607B7EE05D7ULL, 
            0x13CD2EE44F11A786ULL, 0x1F427F1F5C87B605ULL, 0x1F8E2321B950D90FULL, 0x91D62D0D38A7FA0FULL, 
            0x46523734E4C07F29ULL, 0x1D1A0E5AB2F68077ULL, 0xF0B8E0EED6777A6EULL, 0xECA2E7AE8461FDADULL, 
            0x3BC8C44A10F68C7BULL, 0xDFE8C01A0B27E9D0ULL, 0x1F26B5C5BDFD2A20ULL, 0xD3C573345CA043E0ULL, 
            0x825F3AB97662CDA7ULL, 0xE879DC16E3342686ULL, 0x0D920B31F2FC3C83ULL, 0xDFC22F83755DF014ULL, 
            0x45E9D7E4EA0B661CULL, 0xC141098DD62525A1ULL, 0x97A278BB25B0540DULL, 0xE54A013726B21A28ULL, 
            0x4F67117B45B8EA39ULL, 0x896A13B949A58345ULL, 0xBAF62ADAF62E0D20ULL, 0x4261669371FD5842ULL, 
            0x810B2D9DBFF32267ULL, 0x10DAA72D2659B545ULL, 0xD30D7C614B24FB88ULL, 0xA87C9331C1131ECCULL
        }
    },
    {
        {
            0xF5BC2473BFF16FB6ULL, 0x105AEDE753326691ULL, 0xDBCE2528D41A45E3ULL, 0x3886FF2838166C3DULL, 
            0x4FB1B89CBD4A73BBULL, 0x2BB0B0E72CF02575ULL, 0xFB1CC80B6C3E5436ULL, 0x9B03D8DCF8C18A88ULL, 
            0xE48DE4BDF12E5288ULL, 0x0C475D43C3A619E3ULL, 0x27AA256B386D29D2ULL, 0xC87516F55E87D595ULL, 
            0xC6C256C7EFAB0360ULL, 0xCC91AB9419747531ULL, 0x4BA0A06209C48822ULL, 0x39C788AA71BE3A82ULL, 
            0x153665BCDBF4D393ULL, 0x02D1E0B48D2ABB24ULL, 0x78B1DD7A92B35CC1ULL, 0xA92B426399DB20CBULL, 
            0x14FCD7C23097297FULL, 0xE5C8CE4990D8DF53ULL, 0x84DE9AD8728AAA9CULL, 0x4CA25AFE31910AEAULL, 
            0x03C0593031584305ULL, 0x0EC73054A63EF472ULL, 0xE703F4D20BC28280ULL, 0x7E97D9562DD5F4D1ULL, 
            0x950E9C50C17038F9ULL, 0x81655610A71489CCULL, 0x59BC7C75AF2F8016ULL, 0xC4F8704495006968ULL
        },
        {
            0x1AFD9E36664CEBD5ULL, 0xD88C42995D56B21BULL, 0x7478A6CE0EFB484BULL, 0xBCA7A567DE0DAC62ULL, 
            0xE9F94086B63B87D4ULL, 0x6FE5A40A6E5FF575ULL, 0x6A1FEA68530CDEECULL, 0x09460F5DA72202F5ULL, 
            0x7B5E78484D3C7CE8ULL, 0x5EA30B0F4A4F0017ULL, 0xDEB7D3B79E7171B2ULL, 0x506338ED88314383ULL, 
            0x573FFE242BD86B03ULL, 0x74A26FEA8F844ECAULL, 0x475568D37DC38420ULL, 0x565783AB27443342ULL, 
            0x2DC031EB671B2DFAULL, 0x42ECC3F06D6CF343ULL, 0x3E3D92C1A8E42268ULL, 0x1E1949377DDA8C17ULL, 
            0x47E3F02E3E7656E8ULL, 0xE3DE9946FD8146C4ULL, 0xD23CA881BFA49467ULL, 0xD9651224AFE7755CULL, 
            0x0AC232E5D6498ECCULL, 0xDC181F8A2F751AAEULL, 0xB673D15C2B08F84BULL, 0x0BDB51368CF1C812ULL, 
            0x5F00D145D432C2EDULL, 0xAF27D59CD42EF386ULL, 0x993058C7B0758A08ULL, 0xDC66531A164CC5B7ULL
        },
        {
            0x3B204DAB8F6B1EF9ULL, 0x2CED8FE014945C96ULL, 0xC204EAEC0F6DFDF6ULL, 0xB52ECEDEE0538CD8ULL, 
            0xF88AFFDE563B4B72ULL, 0x509026498098D3B8ULL, 0xAA08873EA75DAAADULL, 0x844CC99D79B2C531ULL, 
            0xD0E3DF8D33B19B83ULL, 0x4AA55423F2D4A305ULL, 0x4E78E9645823D1F9ULL, 0x09361E7ADDF26A64ULL, 
            0x49CA18A5488D8449ULL, 0x77F1C445200FB87DULL, 0x265B7E08EEF1D393ULL, 0x911381EFFE111E89ULL, 
            0xC151351F6071E3D4ULL, 0x35B3B4F1C9C84183ULL, 0x31EB7F084A397BB6ULL, 0xC684E0193B21A17EULL, 
            0x44ED29C26FE74052ULL, 0x87CE6A744D7E49DBULL, 0xE02FA19AED67F44AULL, 0x35EBDA16F8DB50D5ULL, 
            0x844F2C3F6BFBC79FULL, 0x3EF650693FD35975ULL, 0xA30324A53D08B885ULL, 0xB66F0695E3B5530CULL, 
            0xEC4CDF532DAC1F3FULL, 0x298F958D21B9E53DULL, 0xA32FF07B82F7039DULL, 0x3EFDDA935ED4C50EULL
        },
        {
            0x67D23E3EA1E050CDULL, 0xF705692ED5922B9FULL, 0xAB9D4B0A2772F005ULL, 0xEB2C288DB8E25FC2ULL, 
            0xECCD00CBDA3624C9ULL, 0x956FD87D232899C5ULL, 0x1CF16AF40E0CA555ULL, 0x52E8C8B008B51112ULL, 
            0x8E0CEEEF09C5DFE4ULL, 0xCE6C48A6822EF271ULL, 0x3DA2BF12E6DD19B4ULL, 0xFFE85BE57F3E91F0ULL, 
            0xD050AD4B2AF206DBULL, 0x21ED9E5875A7C924ULL, 0xB1DCCB4A35A03F87ULL, 0x01911ED04AD0C28EULL, 
            0x2F54CC33139C9517ULL, 0xEAE5AA2EF19A5DB1ULL, 0x04634465BCE0981BULL, 0x64CDE28F4398FB4DULL, 
            0xFC76BE5602F0F028ULL, 0xBD754E5117183EF2ULL, 0x3E40D98037F7BA14ULL, 0xE8060FF3FFBAF076ULL, 
            0x42B169E76642C75AULL, 0x8AFDA548B607867CULL, 0xC22D8A0481C30A37ULL, 0x453983E711009538ULL, 
            0x9F24C5DBB1612715ULL, 0x90482B2805249DA7ULL, 0x10A4CFF17BEE046FULL, 0xD985B00BFEE3C354ULL
        },
        {
            0x094BCB53D8F572BBULL, 0xA66A50C6E0FB88D0ULL, 0x49CDD6CEBBF60125ULL, 0xAA11043AFAE0FBD5ULL, 
            0x9D7F06C3BC5F920BULL, 0xBA1ADF55CEE50EA2ULL, 0x7DDF4B0C9BC29DE8ULL, 0xA09242BCD5F284C7ULL, 
            0x42FB0569F96DBFD0ULL, 0x5541B2DC7FBEE143ULL, 0x821B331107667876ULL, 0x014E477CB84F7759ULL, 
            0xCAA534BBFA444615ULL, 0x44E18CD53ABFACEFULL, 0x9522DA46531A711BULL, 0xABF5E1F2C8996672ULL, 
            0xB3F50A7388A45887ULL, 0xB1A0ED71043D59E6ULL, 0xE9EC2863E8DA9E8DULL, 0xA55319D43D5E1E3DULL, 
            0xCFC6C01BF6DBCE08ULL, 0x917A44ACF29954F3ULL, 0xA82C1EDEE7C23658ULL, 0x63A920B67B63C270ULL, 
            0xAA2D55F8531AD651ULL, 0xA46A3D97E72B3540ULL, 0xEE6D5D562D8E75A4ULL, 0xC1BE9FDE46FB0F83ULL, 
            0x473C04D270A42ABAULL, 0xE384F49F6ED55D0AULL, 0x7011B8B46DC6F9D4ULL, 0x24DCC51D837F00D8ULL
        },
        {
            0x301E72FFD1A5F6F9ULL, 0x495633C138A5AB3EULL, 0x9959B5F845707038ULL, 0x66ECFFA516DE6383ULL, 
            0x1A699B4A3470F4A5ULL, 0xACCA0FC0E2A94285ULL, 0x1049617BEC3A3383ULL, 0x9DF8E8440AEBCFE9ULL, 
            0x072A148DBBB943CCULL, 0xF8424262ECB28B85ULL, 0x34B6FB642A997E98ULL, 0x83080BEDAF4E1DD4ULL, 
            0xB1AA28EC7163C12CULL, 0xB20D8666CB300169ULL, 0x2ADF97292C9810D8ULL, 0x11434EAFEF097662ULL, 
            0x199E1006BBAEA6E6ULL, 0x176F4DD82F5993B6ULL, 0x2673FD6107090F5EULL, 0xB1784D08D4D96740ULL, 
            0x0890319021BF1AE5ULL, 0xC20C1143A9747AACULL, 0x872A43E67773CC40ULL, 0x7CA39A099FC6C873ULL, 
            0x22E388AB12BFED06ULL, 0xBAEF6D83270132A8ULL, 0x2BAB4B2DEB480B52ULL, 0x2E5CDA39A384AC04ULL, 
            0x73F19878F19CBFD4ULL, 0x39ACF82F306A5BA0ULL, 0x0A97E92006FE04C2ULL, 0x5F24D9B69E5B7262ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseEConstants = {
    0xC39B58D9244B1B08ULL,
    0x255A8F0C97B3DDDAULL,
    0x77E38FA01A1B327DULL,
    0xC39B58D9244B1B08ULL,
    0x255A8F0C97B3DDDAULL,
    0x77E38FA01A1B327DULL,
    0xBFA023CC73E370C7ULL,
    0x85A4D0A367FF4129ULL,
    0x56,
    0x3B,
    0xB3,
    0x08,
    0xE5,
    0x1C,
    0xA2,
    0x2F
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseFSalts = {
    {
        {
            0xAFEFC35DEEEB5D0AULL, 0xC28D27C613ED2CFDULL, 0x30863D8D525840C8ULL, 0xAA09441DD6EE865CULL, 
            0x07E175372499525AULL, 0x1D423A93584B5455ULL, 0x8CDE98D916266773ULL, 0x16C9EB3845448340ULL, 
            0xA3326D2EDBCA466FULL, 0x9B092F86F6BF5940ULL, 0x016E25ABEE4415A2ULL, 0x8A96EB1818CD458DULL, 
            0xBDBFA2945D4032C2ULL, 0x4C064135D879A87AULL, 0x82A032E3D246A841ULL, 0x09D10B79D0D7A4B8ULL, 
            0xA3FD4D88C9649E75ULL, 0xE3EAA8C45B5B8DB3ULL, 0xD415A6864FEB1381ULL, 0xEDEEEA949AD7AE72ULL, 
            0xDE393969EAC1A0F0ULL, 0xB0C90E524C954BC9ULL, 0x9A13DCCC23910DC8ULL, 0x79536AD7292B2F6CULL, 
            0x780804703E2D2780ULL, 0x37B26536EE77243BULL, 0x1A2C9AB9DD92BCF8ULL, 0x3FC3E8ED553D2481ULL, 
            0x362E3DC0BB4CA8AFULL, 0x0C28447784483541ULL, 0x05E6E06C2C343F67ULL, 0xD9CFB18579FF6581ULL
        },
        {
            0x229D749ADC38A6B6ULL, 0x16B3BBF136052BE5ULL, 0x0B1B6DA78319A62AULL, 0x00CDE0E05D3224D1ULL, 
            0x91CD6D560B16EC5BULL, 0xC8726C65AFBC710AULL, 0x0F0EFF41D22DA605ULL, 0xC8D899B9995C28BCULL, 
            0xB5C9FA4F627BBE86ULL, 0xEB3E84AE8B303771ULL, 0xD03ED277FDAFC7B7ULL, 0x6A2D6C8502C6F1BDULL, 
            0xE5B7325589100DFBULL, 0xC623534D755D619BULL, 0x0DBEDE18E976809DULL, 0x3F870F53909F0B29ULL, 
            0x75EF2FBCA6566928ULL, 0xD974F19C4A2B496EULL, 0x184965760B71FEADULL, 0x9F7C7595D010E609ULL, 
            0x830FFA71EC8A647EULL, 0x1D4764DC294D0BC4ULL, 0xC43F6FD8BA8BF53AULL, 0x9DFFA7E8EEA09B9EULL, 
            0x2074459748CB19CBULL, 0x5C9AE02E908A2BD5ULL, 0x98FF05A08CD9AF55ULL, 0x400BECC36DC0C30BULL, 
            0xEFFE6EFA05C81A5EULL, 0xB48AB38338D27833ULL, 0x0E280EDE388DEA4BULL, 0x3825B8CA24CF9FC6ULL
        },
        {
            0xD3CB60D8748AD451ULL, 0x3F9DBE22248CA3D1ULL, 0x678BA1521BD6EFD1ULL, 0x17D558BF9F2320F7ULL, 
            0x6B52BD4032052919ULL, 0xB3A3E3CB7AFFED20ULL, 0x8E8750923411EF88ULL, 0x523A36E77EC5FB65ULL, 
            0xAB345D21942C903FULL, 0x2158E657CD0C5699ULL, 0x9C8762B2DF7CDCA5ULL, 0xF66DD80F77A6A8C5ULL, 
            0xCAE352B2BE175968ULL, 0xFE16DE7F8EEBBA21ULL, 0x9142671C1CCFD25FULL, 0x57C4565B02F37A7DULL, 
            0x0634AC33CCBC23C6ULL, 0x8FFEE186DCDBF01CULL, 0x2416A456CCE31207ULL, 0x695AA9A3F6FF74BCULL, 
            0x543AB47B99F24A0DULL, 0x9C534069B6CD4961ULL, 0xE208EA201539D2D3ULL, 0x3CA8CCF56AE4D8CEULL, 
            0x6E7E8984E0D9364DULL, 0x6F575518BC02783EULL, 0x5FB6B895796C213FULL, 0x9EA98D8727A6F3EBULL, 
            0x3C548CBD796E008EULL, 0x564023FD151C426DULL, 0xF942CCB3646C8E72ULL, 0xCBDA86E513940301ULL
        },
        {
            0x2913E4C01B3201C4ULL, 0x6487FFF2B1FBAD8EULL, 0x7DD84BB792191B74ULL, 0x693DE0432EC87E91ULL, 
            0xB4B557FF2E324913ULL, 0x5D727B66DBE2EE08ULL, 0xFCA5B05A0A8F1421ULL, 0x2D7B0CB4005B05FFULL, 
            0x2E91654DFFF80171ULL, 0x8F356B202635DD60ULL, 0x689411EE14B43ABAULL, 0x2FA1614E6BC1F1FAULL, 
            0xAC1966C25623C65DULL, 0x1AAE29CA01C651E5ULL, 0x51B2350592918A43ULL, 0x344D82264D731F80ULL, 
            0x1C3BD1441776044CULL, 0x1892B75538DA7060ULL, 0xA8EEA7375945A055ULL, 0x69160974D52621A1ULL, 
            0x81BC599DA96D3E29ULL, 0xDF5F1E891E291CD8ULL, 0x40F88704A619AB77ULL, 0x24FFAE67AF43BB28ULL, 
            0xF708F271B10BE3DBULL, 0xBC38A5C3DF4B28E4ULL, 0xE989309BB38C340DULL, 0x20524CC6AA7D8A05ULL, 
            0x3354DBEF36F9B2A7ULL, 0x469231DA07356266ULL, 0x214ED1CD1061E6FDULL, 0x874ACCC38EE6A3D7ULL
        },
        {
            0x7DD16C04EAC9EA24ULL, 0x747A8B298201B673ULL, 0x3197728769EBF49BULL, 0xB0AC6A67CDFEBFD6ULL, 
            0x5644F6E5313D25DAULL, 0x04E3BF8A62BF221BULL, 0xDB8602D8C485BCD8ULL, 0xEA224DEDC4D07105ULL, 
            0xD2F95F1ED8DFC5A7ULL, 0xCDCA0DA58F868589ULL, 0xCC909F5436FE7C44ULL, 0x67E25D34B17AB4EEULL, 
            0x40F0070C98B4E5B2ULL, 0x44F9EF0DC744F5DCULL, 0x434BC5EE0E3FF5ACULL, 0xACAD8A7F49A1E0BEULL, 
            0xD30C5466F55B7C05ULL, 0x4DBEFA899B5F7469ULL, 0x02AA6DAF38912B93ULL, 0xE3A082CA8DC13E17ULL, 
            0xC28D50C27FF24863ULL, 0x1ED8D7CAA9257218ULL, 0xE94F2EA40885AA1AULL, 0x044B522A50646D56ULL, 
            0x0DDCE926E34F2817ULL, 0x4C6A6F9EAB61A756ULL, 0x94842B7E4E4F692FULL, 0xFCF699B8020DF358ULL, 
            0x27EBF0FD94CAC15CULL, 0x4C9441A10D059C51ULL, 0xCD475056EDB99766ULL, 0x7DFB2BD3FB76E367ULL
        },
        {
            0x4D66E14354A6A3EAULL, 0x2566F3F1A06AF11DULL, 0x62D684BD74273579ULL, 0xA484305781AD3FA1ULL, 
            0xC4538214CA18161FULL, 0xC9CFF71B04725039ULL, 0xE8B896D312FFF4E5ULL, 0x7746030C43BC6983ULL, 
            0xF07E6BCE64B665C6ULL, 0x3628B10D88135BC0ULL, 0x92CF292322896511ULL, 0x36FCAA5369233C6AULL, 
            0x821A4BA81BDE1DBBULL, 0x8CD852946A2C28D1ULL, 0x31927A7A60FA4929ULL, 0xEB3F50978DC1E3D8ULL, 
            0x2D5F79C69A67E348ULL, 0x0C7DEE68974E3C7AULL, 0x921F2465D51EA75CULL, 0xDCDF40445ED958C5ULL, 
            0xF2B084E572D307DFULL, 0x0559DDFD0738576BULL, 0x94359AD8A1913A91ULL, 0x4DD6F4C909ADD43BULL, 
            0x4397FA23DFB8B471ULL, 0xE73B27B497609CBFULL, 0xF0D820625A0F060CULL, 0x808740A09F8732DFULL, 
            0xD387A2EA36FF99DDULL, 0xC518938FAA626438ULL, 0xB3D4D06AC3CDB3D3ULL, 0xFBFB8C5E0444092AULL
        }
    },
    {
        {
            0x5B8F3363FB3CEF17ULL, 0x1FA2EB2FD0086CA0ULL, 0xE0EB6C1D1BB83A77ULL, 0xCCC92B3B06B9BC4BULL, 
            0x3E71DC4BDA99F277ULL, 0x3CFA73601617B4B9ULL, 0x7BB1E812E1381EE3ULL, 0x4BBA1CCB1F27135CULL, 
            0xAE61EEC8F850272BULL, 0x442892A5A4BDB2D0ULL, 0xBB27C5762B7AC53AULL, 0x5E1CC4D38A919A5EULL, 
            0x9BA94E0BEAD0976EULL, 0x58D1F6C4A6B3EE96ULL, 0xF7C1774C8415DE62ULL, 0xBEACBEEDCC5F056DULL, 
            0x00EDBFBABF24371CULL, 0x51D68F69282781A4ULL, 0xEE3E11E66FFC9002ULL, 0x2CB198757FF8610BULL, 
            0x79060CF0D5CEDB4FULL, 0x63D0327499A6D5E8ULL, 0xE48AEB8FF07C8B8EULL, 0xACCB3D5B49A85233ULL, 
            0x44110784933E855BULL, 0x0C972A9E7803E38CULL, 0x5DBAF0CB5A8A7321ULL, 0x4720B59C827EBE82ULL, 
            0x5078556D19B4673DULL, 0x6A04CCC749DBC6B3ULL, 0x43A81AB05C5326BFULL, 0x89ACDB143FD405F6ULL
        },
        {
            0xBE35A3AF1E04AD7DULL, 0x2A55DBEDFE4B714DULL, 0xF3C5F6800E0689F2ULL, 0x4D5F9E23FD6EECFFULL, 
            0xC7E300A91ED0276DULL, 0x70780F2CDFD95903ULL, 0xF9853AA882ECA481ULL, 0x2200DEB0BD79D5A4ULL, 
            0xCAE63D083F8FC539ULL, 0xA29932A9920A6C61ULL, 0x8733B68330C2C4F8ULL, 0x810918AED991D011ULL, 
            0xDFB0A2C2B68DEF63ULL, 0x4B5278F662A1404DULL, 0x10A3F6BF3A36B323ULL, 0x99B7F6139E7DA1D6ULL, 
            0x89040CE9461C23C7ULL, 0xD515E1AE5962967CULL, 0x49097D7C7AF9D032ULL, 0x860B0817D65133C5ULL, 
            0xD22E737D707098DBULL, 0x9B5766F02FADD2DBULL, 0xC6C8CA784B3F4D9FULL, 0x26E812218992C2E1ULL, 
            0xF82BA1BF0DA9D94EULL, 0xAB36FF73ABF3475AULL, 0x0A5378C85F3F26FCULL, 0xFB5CB7970F87F8FDULL, 
            0x3C7760D16D23C142ULL, 0x9EBB8AE249F58C85ULL, 0x45F7432301DB84C0ULL, 0x57574BD1EE4BB596ULL
        },
        {
            0x8DF63A6F0CF9BEE1ULL, 0x112DC02790B667EDULL, 0x97AD64060C80E22CULL, 0x61C1ADE013D2E448ULL, 
            0xE1E9A1353A54EC25ULL, 0xDF3DC3E59D9A1B89ULL, 0x572A47894A4C6F20ULL, 0x25721C8EF2CD95C8ULL, 
            0x9CEDCA243083BA47ULL, 0xB70F5808D3AED280ULL, 0x80D742E7916ADABBULL, 0x440936A53865D8E0ULL, 
            0xCFE0D2118AADC5F3ULL, 0xCC3F675DCD197BBAULL, 0x4EF7B60BB9926C8CULL, 0x9ADA844EB600D402ULL, 
            0x4C49E0EAB624A8FEULL, 0xC3CBB79761085E95ULL, 0x60731FFEF0C4A93FULL, 0x02F75571F3FDE3F6ULL, 
            0x0A1FC0F90C47578DULL, 0x2E71A93CDE91271CULL, 0xB82432769AC58757ULL, 0x9F89502A7F202ECFULL, 
            0x2E224B3A499B0C58ULL, 0xDF24F717E52D679CULL, 0x0F2A9244DC921060ULL, 0x64A3F346CAE4FD48ULL, 
            0x7C5921FA0ECF01BEULL, 0x975E1762A45B0CC1ULL, 0xA4BB05FDBCDC293BULL, 0x72253CFCF8C6FF19ULL
        },
        {
            0x309A38193F5ACAB4ULL, 0xD9E65243E70EDCA1ULL, 0x7779FE491324D76AULL, 0x7F6E868E36F615B6ULL, 
            0x236D968CD58D68D2ULL, 0xAC879FF560F6576FULL, 0x3EEDBBD707214F98ULL, 0xB92F567183D8967CULL, 
            0x377CAFE2311624E9ULL, 0xAAAD69FB683389D5ULL, 0xDA2D58D9C705C8C9ULL, 0x4718155B852DAD55ULL, 
            0x75D46623C6B57258ULL, 0xE7928BBEDE6CCF38ULL, 0x6467211DA2D4F785ULL, 0xCDDA6E685BB4B0D9ULL, 
            0x2458F3C6DD2B2B3CULL, 0x3A7A155FFD122E3EULL, 0xA1B0067E42A0D1A5ULL, 0xF34086346AAC9483ULL, 
            0x3701748987CF5A80ULL, 0xFF638FCE4EFC2F65ULL, 0x6C28852A99B50513ULL, 0x2117866C231B9FA4ULL, 
            0xF6372C493C7581CEULL, 0x1EDC9C80E5638880ULL, 0x010771CDE9DE6C9CULL, 0xEFEE081B427EA0D2ULL, 
            0x128801BDA7D19F2CULL, 0xBC6D50DC69921139ULL, 0x063AF3E3628F3912ULL, 0xB8040FC20719CF8BULL
        },
        {
            0x91BDED291DF1D5D6ULL, 0x515B1E78E64F6C54ULL, 0xBB50E1E3BDAFF365ULL, 0x36F714701B599B09ULL, 
            0x0A24E71259916ED4ULL, 0x2DA35597307C2B19ULL, 0xC382BFA3290C7A1AULL, 0xE85830AADA1F3D74ULL, 
            0x416C47210CB10434ULL, 0x72F88559A0624773ULL, 0x12CE6CFFC9670467ULL, 0x02A73BDF66177CCEULL, 
            0xC1AF5CA3AFDE96F3ULL, 0xB9EDA313F348ACE3ULL, 0xFDBE630F69CC77CAULL, 0x8F7DAED4CAC8DE84ULL, 
            0xAEEAD29030653B9DULL, 0xCD0B85BBEE6AE4E3ULL, 0xE18D2D4F6D24091FULL, 0xE74AD6881CC624B7ULL, 
            0x91B81C116677402CULL, 0x92119CDB3D48E650ULL, 0x44ED6D6CC090C917ULL, 0x7F0A6B178B6F2728ULL, 
            0x4974F8B8322D5ADFULL, 0xDF8A3395AB5549D4ULL, 0xA9BB30B3F28A8BB8ULL, 0x7E3D406182A64C98ULL, 
            0x922908706312AB05ULL, 0xF2E348D55A1BDD63ULL, 0x419CFEED66EFF049ULL, 0xCF303F8BEAEC71F9ULL
        },
        {
            0xB0EC6984ECBE9F50ULL, 0xB5DA6AFF9CEF14E1ULL, 0xA6434C67BA59D3EBULL, 0xB3C2E126A0BE5ED9ULL, 
            0x77ABD2F5DE1EF7DBULL, 0x0900D35B9D0F2FA0ULL, 0xD0765B934EA36E19ULL, 0x076947127E281F3BULL, 
            0x4468ADA0BA0253A3ULL, 0x827B94FC1D7B590BULL, 0xEC9553CE0E02847DULL, 0xA2BF937B268EE8B9ULL, 
            0x03C32C2176C6425FULL, 0xFCF986AE86CA53F0ULL, 0x1B8C12EA0E5503FCULL, 0x7B0582C55C27556EULL, 
            0x0F584EB4F9112808ULL, 0x398C6617EFAA44A0ULL, 0x791ADFA10D2929E7ULL, 0x06C85BA6E327B340ULL, 
            0x4C5A599B25B644D1ULL, 0xE94B3296F596512EULL, 0x159CEA14494B2628ULL, 0xED9E49A00A5A0F18ULL, 
            0x919837AF36E9D3E1ULL, 0x35F14EB7452EA4C6ULL, 0x9033C4776A0A35E8ULL, 0x86BC82AD7D33A05DULL, 
            0x5F8D604B5BD46673ULL, 0x22A253350D0DEC0CULL, 0xFC1BD031092350C4ULL, 0x2BEE1305D2CC56F1ULL
        }
    },
    {
        {
            0xBA8BE438F0226596ULL, 0x3E0A7C570ABB4926ULL, 0x23B875A5A6D7A41FULL, 0xBB09F957EB35C314ULL, 
            0xED70FC66F26AC0BFULL, 0xA08E22501F1A49EFULL, 0x674EDE1359B4F6E5ULL, 0x0E66690932A253E6ULL, 
            0x0E0955C72D1A1418ULL, 0x30552D1C0AAD64EBULL, 0xDD55C3A3CBDDFA15ULL, 0x215192C6EFD1955FULL, 
            0x582D05F4BF91B402ULL, 0x2926854FE2C72E94ULL, 0x1D7EC1687B64C882ULL, 0xFE334725560EA813ULL, 
            0x10F536B090B5DF97ULL, 0xCDDAB9192CC91119ULL, 0x0F27231A64F8CEF3ULL, 0x8584E226902A35A8ULL, 
            0x40D3C6BD0ABE6E25ULL, 0xC416464A63ED8B76ULL, 0xFE73D8A397A51C50ULL, 0x772EAC6D27F89C87ULL, 
            0x63763B37490D156BULL, 0x8C10017724947CF5ULL, 0xBA3418FEC46937E4ULL, 0x7379C83155A2F53BULL, 
            0x196B2C6FA935D993ULL, 0x70F792275F3B0829ULL, 0xAADD1E62584CB3C2ULL, 0xD4CED9D4A1ED05AAULL
        },
        {
            0x72273615B6BC0BEDULL, 0xA1946EDF34F055B2ULL, 0x9B01D8E2E085C9B1ULL, 0xCDD8084361787559ULL, 
            0x6DFA9DF31463FFCCULL, 0x0F8CECBDA9F56228ULL, 0xC2E5B82D65754695ULL, 0x5A297E4DF78E1A80ULL, 
            0xFDF1FC8E46B6E00EULL, 0x4DA62309BF82E351ULL, 0x004887E19487000FULL, 0xACD5B92E3820984BULL, 
            0x4BF88F5F6C17254AULL, 0x08F117051DD45E2FULL, 0x24DD88306CF54D59ULL, 0xFD135877C5A6F5ECULL, 
            0xD33C25A2992BDA28ULL, 0x50704F5DDC70C14AULL, 0xBB1393B61EB877EBULL, 0xCF2533A2B946BF5FULL, 
            0xE9C7D4695D25E9A1ULL, 0x6AF02BE3DCB3FCCEULL, 0x465085ECF6584B9BULL, 0xF34E9C5B54592A72ULL, 
            0xF4875A94E87E3464ULL, 0xB70A4122687E3F0DULL, 0x75FC1123DC22F843ULL, 0xA11BC978015F5BC8ULL, 
            0x7655FA5C74207336ULL, 0xB2FFA8581A320B22ULL, 0x85C507807C9BE150ULL, 0xB360B5275CDCA40BULL
        },
        {
            0x8007F773E53B74FBULL, 0x21FEFA76FA8C55AFULL, 0x7FD2B29A6B2FB63CULL, 0xF06EE77486338553ULL, 
            0x11BAA5009BF9FDFAULL, 0xFE1F51A80E225D09ULL, 0xD88050100B0C7755ULL, 0xA6AD4F58382073FCULL, 
            0x411490D8CBD80C2EULL, 0x6E5922F79464C9DAULL, 0xBE59E682EA21C307ULL, 0x79714A0095FFAAC9ULL, 
            0xB401F5F1B3BD3F74ULL, 0x74FB5065B6B78430ULL, 0x54AD1FE4C0708D9BULL, 0xCECC97B262721651ULL, 
            0x6741FDAADB722B5BULL, 0xCA9EE3CF36771B84ULL, 0x7E49B337A16DD297ULL, 0xACDEF3E32B7DAEC6ULL, 
            0xD16965BB6C4BB189ULL, 0x1969EE18DA53CC06ULL, 0xE72C0F97C4FEE33FULL, 0xD690A76FE6A68A82ULL, 
            0xABE42314558528B8ULL, 0xA06E3143EE749963ULL, 0x13575125B1C7AE24ULL, 0xC23A3A5E4EA2C81BULL, 
            0xF7B17C8B0EC59CCDULL, 0x88F9C0797D4120DFULL, 0xC9C62706DC7562C1ULL, 0x996E37B27DDCF78AULL
        },
        {
            0xACC77C90FD134304ULL, 0xA6AFD9F24E6C296FULL, 0x3E14E3D3E2FBC151ULL, 0xE34196D21D864B18ULL, 
            0x2569F9B58E5401A8ULL, 0xA2DB3BB20561A694ULL, 0xA7A6CE17A1024790ULL, 0x575DDF1D3FC9915DULL, 
            0xF52E5F8A7E0B23C2ULL, 0x983C1408267CA339ULL, 0xED9339EA2C156373ULL, 0x15EE1661D693BB99ULL, 
            0x68273361DB3380AFULL, 0x7824B44EFBEF8CC3ULL, 0x7A8989F682196AA9ULL, 0x4342F6E972ABF4B7ULL, 
            0xC69C240E8805EBACULL, 0x0389FA46BE9ABEA5ULL, 0x3AEDFFE3D625C9E3ULL, 0x9E04F919F4AC5006ULL, 
            0x775C3629B489D77EULL, 0x0503193D54AC346EULL, 0x038C63E96E7EA3F4ULL, 0x36B011380EB7775DULL, 
            0x79CC274BA5BCBF05ULL, 0x1E2F220B2B57385DULL, 0x834B69F4675B90FBULL, 0x7A89345A63F8E490ULL, 
            0x35806F2C4608191DULL, 0xEA88888C0BA00722ULL, 0xE5F20316DF24358EULL, 0x998784D525F2A49BULL
        },
        {
            0x9EECA6539989DD5DULL, 0xF698962C049C5622ULL, 0xE7E1DAB95E80C67AULL, 0x8314EC2470B189F2ULL, 
            0x46CAB2032B68E39EULL, 0x33B8B8C602E2872EULL, 0x1013EA86A9ACC8EDULL, 0x539BE57C4595B18AULL, 
            0x3C045687CBAD4E2BULL, 0xBA5C1D8ABC67955BULL, 0x950196A5C8DBF29CULL, 0xDE3F65FB9D29E29FULL, 
            0xB161B9C408CD3C1DULL, 0x3AD7D64ED5E04949ULL, 0x29C9DE61A41372BAULL, 0x40FBFE86BFEE938AULL, 
            0xA6F0D88278BF871CULL, 0xABD726684F5F911BULL, 0xC53D84AE2C3ADE62ULL, 0x274A72F235D8FC51ULL, 
            0x1B1BE1678FE52A8FULL, 0xF65A2AA139F78DECULL, 0x5EAD40FBB336C63AULL, 0x534016021C3E3CFBULL, 
            0x239016B014F9A4F9ULL, 0x21FB9BD94F93F7D1ULL, 0xEF3532DF9A7AC3D2ULL, 0x5B474B04957FCF1EULL, 
            0xFE5F6651D1E4064BULL, 0x331BB0F9888D4E22ULL, 0x3B9C4946707B8970ULL, 0xBF6E03781521D24DULL
        },
        {
            0x861220CBE0306D9AULL, 0x2EE11BA448A4369EULL, 0xEC3F509A5B906BD0ULL, 0x2E3591205C7BACC2ULL, 
            0x850BF87400643D00ULL, 0xE46575E9A047906FULL, 0x7C2D635D5A6265D6ULL, 0x95BAB861EEAFBF5AULL, 
            0xCF123C6AA2A6B307ULL, 0xF93A7E54238E46F2ULL, 0x3778BB16E2A1ED8CULL, 0xB9543DC681392F59ULL, 
            0xD78E0CBFFD42AB1EULL, 0x6B43D9D48AB6897EULL, 0xA915B6BCE526E848ULL, 0xAA6AC3AA9E8FAEECULL, 
            0x66B159433C67D842ULL, 0xE5DC5EAF9F2C0ABBULL, 0xF962411F70B432EDULL, 0xE069E3A76710A9F4ULL, 
            0x45591CC1818AB1C6ULL, 0xEAC3C0BEF4416748ULL, 0x96A7E149DEE27F08ULL, 0xF91A618D1E4B35B9ULL, 
            0xA497B5E299D8AA06ULL, 0x70EFB9D107DA7840ULL, 0x50BF37A8FA402F4AULL, 0x8DE3BE3657F7DF13ULL, 
            0xA4B9C82B38164DD0ULL, 0xDA067E4225E8D5A6ULL, 0x6B19CBDF2AA39A78ULL, 0x12E3EBDB7833769AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseFConstants = {
    0x1EA4DE1039B44513ULL,
    0xC57804506CC2F7CAULL,
    0x33BE5E97F44B532AULL,
    0x1EA4DE1039B44513ULL,
    0xC57804506CC2F7CAULL,
    0x33BE5E97F44B532AULL,
    0x7E6F0C2132A2887AULL,
    0x5725F497304EA9DEULL,
    0xAB,
    0x1A,
    0x11,
    0x9D,
    0xF5,
    0xB2,
    0x2C,
    0x04
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseGSalts = {
    {
        {
            0x429645F5B96B5BB3ULL, 0x24AA6BAFAE92F2D2ULL, 0x831AD3D5B5661E39ULL, 0x6EDC537210336701ULL, 
            0xEB9DC5F831CDABCDULL, 0x0F7DBFAB8E47EE0DULL, 0x3EEEF24DD3117E2DULL, 0x27043D79F77D18E2ULL, 
            0x7B8CA956F2A68DBBULL, 0xD364088500CDD954ULL, 0xEDCF39C8F42F1C7CULL, 0x5D224B9422A3AF07ULL, 
            0x2B7CD9C32A80A33EULL, 0xFD764DEB508D7496ULL, 0xD9DA3724072D5EF4ULL, 0xD7B5B6A9DF400A94ULL, 
            0x129624AE9C521452ULL, 0x1A2B1410CF9826F6ULL, 0x0A11A0899FC9A995ULL, 0x1C81FB54ABD133CDULL, 
            0x005C57C4C1EA7E22ULL, 0x93F622E850D546CFULL, 0xAA814ADC0E706CBFULL, 0x7511D5C318F58ED9ULL, 
            0x9FB3722C7950C7F4ULL, 0xA8BA8EE9B1B41494ULL, 0x060725DBEAA0D094ULL, 0x08054383DBB3FBA0ULL, 
            0xD264DAB9DCB05EF8ULL, 0xA412C84D7F11231EULL, 0x4762B7D7F15B78F2ULL, 0x4CEE3B6570B09B14ULL
        },
        {
            0x88F9471F94D088E2ULL, 0xE201DA5AAD49D7B5ULL, 0x6CF30DBE2C9E5850ULL, 0x1E1EA5B896C68739ULL, 
            0x64DCE3331FD438E5ULL, 0x8E01F947A40D428BULL, 0xA8746B3A77E38672ULL, 0x1B0DBDAF5E1824D8ULL, 
            0x9D2FA1FE9AE60E59ULL, 0xF4068290D33E450EULL, 0x81184EF42DE6C5CCULL, 0x4133718EC60E7A1AULL, 
            0xB06B907353E3CF75ULL, 0x3ECF204D3CDE4C45ULL, 0x9EE9E6509116A136ULL, 0x5588A74475207FDBULL, 
            0xCF7D71C9D9729AB8ULL, 0xE4A681B6CB09C238ULL, 0xB365F81F8990B30CULL, 0x1F341332B8DE1961ULL, 
            0xA1E85C8F47FE1DB0ULL, 0x3C7123DE1E10BBC0ULL, 0xAFEFD0EBFAA0083EULL, 0x727219273F3C3F8DULL, 
            0xC11A9D7C2B507F48ULL, 0x4A8337F00DA9EECEULL, 0x71FBCBF2DAF479ADULL, 0x23609CF8CDA82C9CULL, 
            0xA4C32A25CC8E2098ULL, 0xF9ECEFB864729545ULL, 0x09838B23082B9F8AULL, 0x827C13C694D2A2BEULL
        },
        {
            0x213BD810B7D65CCAULL, 0x44799379025797F7ULL, 0xF82B9833AB6CA437ULL, 0x32AA7CFB7EAFAEA9ULL, 
            0xAEF3C063663EC0AAULL, 0xCC9B0507F837C212ULL, 0xD501EF992D13F9F0ULL, 0xBAD699999782613EULL, 
            0x9FE43B8EFBF2E638ULL, 0xF55086D7E4C9FCBCULL, 0xAD6BB0738EA40EDDULL, 0x4027C7BE7C486D34ULL, 
            0x159BE1CFE9641B8CULL, 0x5E4173E1F13CF498ULL, 0x1AEBE8DD3DA107D0ULL, 0xC4439EC37E2EB629ULL, 
            0xD4772A8CC78ABB93ULL, 0x692EDABCB03BBB83ULL, 0xE90975EEBE73F60EULL, 0x570ED8D0BCF52172ULL, 
            0xD09E5827E2D1D0B0ULL, 0xD5E1970BE6CDF55DULL, 0x087CF97DE42BE9D1ULL, 0x061A80EBA879856AULL, 
            0xF443BBB7B8C086D5ULL, 0x9E0348F6ED440B04ULL, 0x1F266C4BE9369ED6ULL, 0xEEF5D1067A74D9C2ULL, 
            0xFC27AB399A6EBA98ULL, 0x8E00F53DA385CF35ULL, 0xED1DD6781168864DULL, 0x776C1873B61C9EE0ULL
        },
        {
            0x825770D253271E50ULL, 0x4C7AC7AAA92D6067ULL, 0x252E28A064B52117ULL, 0xE56D5FD768530166ULL, 
            0x5DEC6CD169318A03ULL, 0xB1799E0A1E9F344BULL, 0xDF1C4191455FC5B5ULL, 0xEBBE96D37BBE6E76ULL, 
            0x252DD6DB16A7D62FULL, 0x0CFB66D3E757EC08ULL, 0x34823CF4B5E4A071ULL, 0xC0F48534E285EB04ULL, 
            0x4D536335E7458A2EULL, 0x2E7A7C5170757F9EULL, 0x94823C0AF4A99FE3ULL, 0x7BBAF17A02324E95ULL, 
            0xD2A5E515B7E4C8D4ULL, 0x5F1755F5B2ECCBBCULL, 0xFA84BE59B41BA602ULL, 0xB51AFF54BAEA44D3ULL, 
            0xA6324B17523D7352ULL, 0xC3AB152CEF831271ULL, 0x9BFFA410A9C6013BULL, 0xFA64B5B855E2D573ULL, 
            0x788B1D119269B40FULL, 0x68B86218D2A9435BULL, 0xBC086C6DAFBB7111ULL, 0x582ED86A81A3D065ULL, 
            0x3A5C13F83C07FEDEULL, 0x85FF9129A8A8F116ULL, 0x2AE020DE7D8B3AD2ULL, 0x588BE8C97936FC4FULL
        },
        {
            0x067F775AD3502FEAULL, 0x5719EFD840BB239CULL, 0x741876070DBC5119ULL, 0x807762B6A451928DULL, 
            0xCC52043145E49836ULL, 0x60F628B803FAA23AULL, 0x593E0AD8DCAD1978ULL, 0x64ECA99EE3767317ULL, 
            0xE862CFA14630854AULL, 0xACE8FB059A34230EULL, 0xDA5D9E1D6AC30C51ULL, 0x4EC64A56E2B3C980ULL, 
            0xA71E62213BE6E096ULL, 0x9EC0A68A7451580FULL, 0x6A6362A566FDFF35ULL, 0x0126D92A17DDF5E7ULL, 
            0xDF48453B24B30FD0ULL, 0x849D0A9E42A221C7ULL, 0x352BC1021A760CF2ULL, 0x7525274AE22D5CA1ULL, 
            0x46C5482CC6356099ULL, 0x494FD22F273E17F1ULL, 0x12AF3611E3998507ULL, 0xDA592868ECDC83CAULL, 
            0xA3EE8AC1863C38B5ULL, 0x9B65CD314EE61EA9ULL, 0x64AF7E55C78E79B9ULL, 0x7CF733E5B5F82C1EULL, 
            0x1CB8065FBD17CB96ULL, 0xB67948B9F1D1C89DULL, 0xFD115363ECC81CB7ULL, 0x5AA351F56CA0CC99ULL
        },
        {
            0xD80A7BEE5F7E7DB1ULL, 0x803E5F7D12149D57ULL, 0x909355106B70015FULL, 0x9E470E396A406A76ULL, 
            0x5FA9CD9BA6B465DAULL, 0xBECE81D9BB3E41C4ULL, 0x4E1ECA808CBAB92FULL, 0x21207505337F665AULL, 
            0x1AE4ED02D3AEAF90ULL, 0x9AF84C842501B4FBULL, 0xD8E58E76D7B86AA2ULL, 0xA76A223F324A5B77ULL, 
            0x9E9FA73DAFF1B467ULL, 0xEF6065857A8371BFULL, 0x1381D9E55EB15548ULL, 0xC026004A4C9C7CF8ULL, 
            0x8C91C5BB8E3DCCE7ULL, 0x3B1428C5AD50CCE9ULL, 0x9C8981A88D1C46D7ULL, 0xD93E7407169FAB09ULL, 
            0x9D9FE043C764A786ULL, 0x03A794A1B11B6B98ULL, 0x061C4741AD8F7E6DULL, 0xEB31511BD58074E9ULL, 
            0x17E12969DC0B1CAAULL, 0x61534F3B1943AB14ULL, 0x0DF7FC87C119D195ULL, 0xDD239EDAD75AEF7BULL, 
            0xE08D3783F2FF9320ULL, 0xC8D182187972468EULL, 0xBC0D97AE814ACC1EULL, 0x95E489B37A47A6F1ULL
        }
    },
    {
        {
            0x9D454F6D9A60AA0FULL, 0xBA07E494E0D6F607ULL, 0x92A1914A1AE6168EULL, 0x3A4A72B65890C5EDULL, 
            0xE0281EF36EC1E230ULL, 0xCD16FCE59D0EAD45ULL, 0x231D96E1493A28C1ULL, 0x4D3097E70F3A86D5ULL, 
            0x4422FA1EF249C922ULL, 0x681AF855BC73E1E7ULL, 0x38DC75397F7D7622ULL, 0x89DD5413E17ED54FULL, 
            0x97EA10B5F43BA4ACULL, 0xB34A4DCB72D177A9ULL, 0x06202920D4CCE0BDULL, 0x272FC17E7DCEE296ULL, 
            0xF539394B6A92BA18ULL, 0xD82EA8E2447D49BEULL, 0x10C641A12C0A4920ULL, 0x208096BCD2AC5534ULL, 
            0x4A842BABB88052DFULL, 0x0A611963AD72D181ULL, 0x53F9D9DF2EE3E40AULL, 0x7A0B10599FFB0F83ULL, 
            0xF6FBB522EBADB815ULL, 0x7EEFF573D1B46C17ULL, 0x6F506A3719D63808ULL, 0xA51C9102EAA091BFULL, 
            0x143930DF61CCA2D3ULL, 0xF075AF0EEED1BF49ULL, 0x389F9D9EE63C23E0ULL, 0xB5C4D3E206AE5586ULL
        },
        {
            0x0AB0BFC7A4EC5D27ULL, 0x12D7ACC04AAE8A1EULL, 0x921D1B1EB907DF0BULL, 0x6FC613F6111C5D10ULL, 
            0x38EB345ED134149FULL, 0xDFA6D03EE227AD44ULL, 0x46113ACE306635BAULL, 0x47E06B9F8416B60FULL, 
            0x5F2AD0ED79236B63ULL, 0x0C3C088FEF6B5BFEULL, 0xF75E327C671679FFULL, 0x22F229D8FCDE00B1ULL, 
            0x6C9B71314DE2AB0EULL, 0xA555290CFDA885E1ULL, 0x717E7E3934A84B7CULL, 0x8007E709C038B782ULL, 
            0x75DA4AA6AA6DAACFULL, 0xA60D142867DB797CULL, 0xEDC0A52AE89BCC32ULL, 0x6D31B0E6AD253EA3ULL, 
            0x944B92AF0DB1116DULL, 0xD21D6FBBF2090798ULL, 0x12DFAC030B7D7FAAULL, 0x8DE6953B58ACF14FULL, 
            0x02BA1E6769356362ULL, 0xE3DA718322E9BD6BULL, 0xD3DD15759D4E3B73ULL, 0x6D9FB82EC000DC0FULL, 
            0xE9BD31E0DC660A58ULL, 0x3414E0F0C5B6EE3DULL, 0xB798750C82A262F6ULL, 0x67DA1E939EA9FFA6ULL
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
            0x3C1A3ED66CCC24B7ULL, 0x9E4E44FF422D8DA5ULL, 0x0CF966EB8F7E768EULL, 0xB84257DF42E1D95EULL, 
            0xD44A3D8224649525ULL, 0x5FECE5FC9FB49CA7ULL, 0xBECF8C6C5333E6FFULL, 0x6125754B9C0C91F4ULL, 
            0x0F08A3F3BC55C2FBULL, 0x2D3CEE8E231A9AF3ULL, 0x2D07856D6D156EEAULL, 0x5BB622B69B89A942ULL, 
            0xF494DDFBD37FD04FULL, 0x736578E53207579AULL, 0xE2931B624D13B798ULL, 0x4BE328D8C353758FULL, 
            0x6B522D04022A0909ULL, 0x47EDF921F760046FULL, 0x965D1C6A3138E064ULL, 0x9C88BE01A0B345F8ULL, 
            0x42B46A3E7E1EAE74ULL, 0xC2D05DBC554BA729ULL, 0xFF1258286DB8F02DULL, 0xEEA865D760CA4E44ULL, 
            0x9F956596812BB29FULL, 0x6B0B22195E4D68F1ULL, 0x037AB71ABF248739ULL, 0x613587E90C883CCEULL, 
            0xFE27F1F7A7C81ADFULL, 0x1EC439331A4A110BULL, 0xFF0A3BFE5E6AB404ULL, 0x8E1B4DE9F373729BULL
        },
        {
            0x9413FFF97E338B26ULL, 0x42B570D49F7F446BULL, 0xD642CF0DB5FB21B6ULL, 0x55A8EDF0D2F5CFFAULL, 
            0xE17B0EFA938BA90BULL, 0x21FCA7408F47F0E0ULL, 0x5ABCEE2F758A1E41ULL, 0x4F973C28295E522AULL, 
            0x7507929C8E047498ULL, 0x060A3D74550FC6D2ULL, 0x98B395E4E9A4E347ULL, 0x740281FF8D346102ULL, 
            0xAA965A4A68D889D5ULL, 0x87D0AC2AD5888E2DULL, 0x151D797365F37F53ULL, 0xAACFBEFE80F71143ULL, 
            0x5F84662344C911C7ULL, 0xCEC9D7E46C716A01ULL, 0x8AB7CB429DD500DBULL, 0xE6D76A09E68FCF84ULL, 
            0x06BB3719FA392717ULL, 0xA188CB06537208D5ULL, 0xBDEAAF5FC9863BC5ULL, 0x012EDCE054F4E6C8ULL, 
            0x9F0CB3DA43285A45ULL, 0xF73EA0550A33E27EULL, 0x424E8498B70B83F3ULL, 0x6B9B41AF82C4FD12ULL, 
            0x6B43C6EBD446C235ULL, 0xBC53A0EC80E902AFULL, 0x81B0DDD3D188A13BULL, 0x32EFC0BFDCB71944ULL
        },
        {
            0x9A84589109DA44EAULL, 0x87223C57493A542BULL, 0x4301114EDC75650AULL, 0xE1A4AB0E145091DEULL, 
            0x2B1E942D83A60838ULL, 0x4FABA6C3E1F06792ULL, 0xC2E44D8B858B0C0BULL, 0x66AE1768DDC8D861ULL, 
            0xA00F640C8268020CULL, 0x67A53B0F16A9F60EULL, 0x66521D4E9056F5B7ULL, 0xD4666CD9AECE341BULL, 
            0xF92F6E99B156AA06ULL, 0x92E6D869EC9BB6A3ULL, 0x5F86013DD9FBFFDCULL, 0xA3EDD33E417C8A58ULL, 
            0xBCF15A355993660CULL, 0x449873EC6B71DC2CULL, 0x22D415899B519B41ULL, 0xEA6DDB330FB544B4ULL, 
            0xDE41AD67345A3681ULL, 0xD9BB6433BA148A90ULL, 0xD054B3D42EE1BDBBULL, 0xFAE5F170F07408B2ULL, 
            0x1A9763DCE15DCB9FULL, 0x654DDE3EB664E9B7ULL, 0xC5AA87ABF09C9662ULL, 0x9E74ECED198C6538ULL, 
            0x75AA25E56F30FC21ULL, 0xE0F04EA38150F5F0ULL, 0xC97921A2B2AC4326ULL, 0xEB801CF185DA4371ULL
        }
    },
    {
        {
            0xF71A6EA1DCE7630CULL, 0x831E741C0EECA5BDULL, 0xB769D8A3DE6B4BEFULL, 0xC746456CD38BBFDEULL, 
            0x2DE9928A491AA04AULL, 0xCFE2111FB7C1B058ULL, 0x80CECD24B6B88BAFULL, 0xE517BBF213F88BD2ULL, 
            0x7EE025CC33CF5530ULL, 0x54090648B40679FEULL, 0x2E3D5C1A1C333D32ULL, 0x6C0A24D27E3A0DD1ULL, 
            0x4E9ECB69A644C81FULL, 0x4F37C52AABCDE3C6ULL, 0x0171D86D1E62F648ULL, 0x2135104C847E5937ULL, 
            0xC1A324DF6346219FULL, 0x90F0D41D480B6569ULL, 0xC6230CA61BCDC6ECULL, 0x390E7792DF26F56FULL, 
            0xF17CD027FF1D4B02ULL, 0x12C37A04DE281F53ULL, 0xC92FADAE9BDD19D5ULL, 0x47E77836317018DDULL, 
            0xAEFEF2B969ECF2C0ULL, 0x7F70AA2DCF6F67DEULL, 0xE4372FE796208EE8ULL, 0x2C7E655E908E08EAULL, 
            0x77A965711A43FFECULL, 0x3FEE60E118F1575BULL, 0xD241AB766E412BC8ULL, 0x37C13D2DD5DAED3BULL
        },
        {
            0xFF5A7D720B8AF258ULL, 0x30882E1FD5360B50ULL, 0xDDBB1F0109E451E1ULL, 0x38D544E40E1B1E38ULL, 
            0xEA03DE8CE028A651ULL, 0xDCD141F755E15AFAULL, 0xF7CC92979ACE9600ULL, 0x97D77391BAE1175DULL, 
            0x1B6C7E8C5E5710B3ULL, 0x63C33642EB2D18EDULL, 0x66252D110FE64909ULL, 0x6265A7901C0783E2ULL, 
            0x52DC248FA15ED69BULL, 0x5C3635FDBDD7454AULL, 0x37AE5FDBFA2DB87BULL, 0x0B9FBBD21F1AFD97ULL, 
            0xDB85F937CFFE6E59ULL, 0x056648F41FB855F2ULL, 0x3BE0D3799A3C7AB0ULL, 0x6D4479AA9C85C0D1ULL, 
            0xF8ED26A7157D0CA2ULL, 0x9FCD324350B91E01ULL, 0xC1DD7D8217062BC5ULL, 0xA185041E9439404EULL, 
            0x5A15CD9D3E3A2617ULL, 0x768D2338E30BEC31ULL, 0x8FF9549DD9D8732AULL, 0x92C32E9431491421ULL, 
            0x5E1DC5F3A4DC87FCULL, 0x33D77B0DAF8C5D6CULL, 0x8E78F9A6A89F380FULL, 0x89C5B8DF6F55AF56ULL
        },
        {
            0xBBC08C572D1CFED0ULL, 0x9E8B784B0BB1604DULL, 0xE6D278D992616491ULL, 0x347EE6B3CD5F8B2BULL, 
            0x59B8E4F077B1F4C2ULL, 0x6954E6D4539A9592ULL, 0x19241C93F0B122EBULL, 0x8F04E3ECA93EF4F8ULL, 
            0x367AC8A03CC4DE25ULL, 0x8F04BC0AC6737B57ULL, 0x149BF475188AC66EULL, 0x2017C5CF1EB94F96ULL, 
            0xC4C0C8F13C17344FULL, 0xDFBF1F618EBD9635ULL, 0x1DD7A05373813851ULL, 0xADF5C9A5798F1589ULL, 
            0xE856BBAD25F5A5B5ULL, 0xAE5592F1B6D8E143ULL, 0xC1EE80EA090EA347ULL, 0xCE1B8A82F42369EBULL, 
            0x7FE1B5178F4B828BULL, 0xA78CF0552D5AB191ULL, 0x4CC89CEDCE167756ULL, 0x2800C42121E83C85ULL, 
            0x2F1E3ADF943ABD18ULL, 0xE354EE45C2EE945CULL, 0xF6C3359C744F8C36ULL, 0x1FE38176F7051FF0ULL, 
            0xED2084408A643840ULL, 0x98BA04474DB1C92DULL, 0x915F73B08595A18FULL, 0xC2B1B41822C2BB87ULL
        },
        {
            0x0B02839C8971F8A5ULL, 0x3DB2BF98D076DADCULL, 0x30052834A72320A1ULL, 0xCA0B13B12D3476C7ULL, 
            0x92B5523C976EA328ULL, 0xE1E06A881C87C691ULL, 0x0AB221542BC6AF3FULL, 0xC9D2BD3804D49E4CULL, 
            0xF7272F8EBF5613BDULL, 0x4B4BE9EB4BDE75AFULL, 0x811197BDA0B0EF31ULL, 0xBD837FCD9A1636B2ULL, 
            0x5BF8A5F37EB8653FULL, 0xF41A386E220F5EE0ULL, 0x8CC746BB2118C6F7ULL, 0x9DB334FC4A164491ULL, 
            0x453E87F1AFF8F631ULL, 0x0798FE2366D2072DULL, 0xA1E78BD05A28B711ULL, 0x12FE91CBEFB9E079ULL, 
            0xEB543D16DFE34B02ULL, 0x7093CDC7F6A48C40ULL, 0x71AD98917BAE12B5ULL, 0x14FB47A7065092B2ULL, 
            0xBCE319CF2596356AULL, 0xC7918013CFF4E913ULL, 0x39806508EBD15001ULL, 0xED66171CBBABF1B9ULL, 
            0xC1C3824F0F780D77ULL, 0x2BC86608F2DBE0C8ULL, 0xAE27099EE44B1545ULL, 0x83ED1EA2977DB7E4ULL
        },
        {
            0xE9E732009F1A8E6BULL, 0x5FDAFF8F4B1AF2FBULL, 0xCED14C5C9ECACD10ULL, 0x54A9913797852CBDULL, 
            0x303069F466A8ED00ULL, 0xEDB0F47A3D91DBABULL, 0x2A584A397864EB63ULL, 0x37D7212CD2C56403ULL, 
            0x3C73C0D86544AC6AULL, 0x543ADFFB644F4F06ULL, 0x0251F4DA7EB996CDULL, 0x55066991B3EB3E53ULL, 
            0xFE45403FBA633749ULL, 0x2CC1C556088D0F2FULL, 0xFA70039B122FF1E8ULL, 0x949F94DBE97DF3D2ULL, 
            0xF8E4EACEB5234173ULL, 0x6ACC64145093F93DULL, 0x7835905FA9F6803CULL, 0xA02BDF0B3469EE4CULL, 
            0xD96E26344B3DBA2DULL, 0x7077A245E756B2FEULL, 0x286D16E3016E7F96ULL, 0xB2AD8D830796BBB8ULL, 
            0xDD6833B988772800ULL, 0x59383D8419915579ULL, 0x04431CEBF9347ED5ULL, 0x9BCE1D3FD74808A0ULL, 
            0xFE1DE4194DC2C624ULL, 0x8C4C3E42DC22F1ACULL, 0x18FCD2D441EBE97AULL, 0xD4F3BFEADB2FA902ULL
        },
        {
            0xF9CFD4BAD38B1EF0ULL, 0x2E00C6F6A3585678ULL, 0xC274D1C2E7379A0EULL, 0x8AE5B05C74C39AA9ULL, 
            0xCE7E3BC6DD3F5A6CULL, 0x36BE8AB687C1546AULL, 0x0667A5D7EFD20705ULL, 0xACEDCB77EDB1A03FULL, 
            0xE1C9AC38DA995481ULL, 0xDD999A21F8EE96F2ULL, 0x5C601ABD7A879FD1ULL, 0x2B40E756E3121475ULL, 
            0xFB245585062A5909ULL, 0x782846ABD2B1F922ULL, 0xFBBEAB29B5AFA2ADULL, 0x3A3F16FAF99A5760ULL, 
            0x67F625B98E97125FULL, 0x8E179B5894EC9173ULL, 0x51805FE90E7DEAB5ULL, 0x202DF05A61D59760ULL, 
            0x5DC27FA0FEEF5792ULL, 0x9FF1F04C8093EE2BULL, 0x3AE6520CA0B9E55AULL, 0x785E5EFA3290F575ULL, 
            0x4693C2F9AC9FA45BULL, 0x35612335A67DB1A4ULL, 0x9062B4EAB7EEB69DULL, 0x7A92E4B577489835ULL, 
            0x78F2A77D2FD3D9CCULL, 0x1E9E791B700A4E66ULL, 0xF0219EEC3BED684CULL, 0xBB18DEAC7CBE014AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseGConstants = {
    0xEC7D28C37835ADD3ULL,
    0x425BFFDA23B787C7ULL,
    0xA4C92AB328A7C1A2ULL,
    0xEC7D28C37835ADD3ULL,
    0x425BFFDA23B787C7ULL,
    0xA4C92AB328A7C1A2ULL,
    0xBDA0F25C7FB52BB6ULL,
    0xB6FB4D951E0E69FAULL,
    0x1B,
    0x98,
    0x8B,
    0x2E,
    0xE6,
    0xB8,
    0xF9,
    0xD6
};

const TwistDomainSaltSet TwistExpander_Mothallah::kPhaseHSalts = {
    {
        {
            0x242B03056DCFC65CULL, 0xDDD5593F1D285846ULL, 0x056F360E61F5153EULL, 0x333CD6F00293014FULL, 
            0x2A4EF107F97BF54BULL, 0x4BEE7EE45BC043AEULL, 0x9BB2047C335BD536ULL, 0x02B374752705A7BCULL, 
            0x80E5AAF4ABA8F7B9ULL, 0x9E456F3359441B25ULL, 0x1DF56348BE85674DULL, 0x89F2A8DFF995CE7AULL, 
            0xDC046FD8182E0F75ULL, 0x688AE00A9AC34859ULL, 0xFD0BDF1635FF3C39ULL, 0xD8EB4BF7E4E29F59ULL, 
            0x90F8AE8EE6033275ULL, 0x3918CF57A6FACBBBULL, 0xD71075890D2D5FE2ULL, 0x1ED026006D8CDD11ULL, 
            0x77EDC0A9501F9D1BULL, 0x888283E3879F2DBEULL, 0x7D886DD1D62DC123ULL, 0x5C72D48EC1950AD0ULL, 
            0xC07D330F93C5133BULL, 0xB912011692B72BE9ULL, 0x99B20EE275DA0736ULL, 0x9FE04C4D8BC80710ULL, 
            0x490845E4F7D83D46ULL, 0x3B0357467C283B00ULL, 0xD25921477A3193E7ULL, 0xD2120A7A3868C7BDULL
        },
        {
            0xC759C9E4385271C4ULL, 0x884A181ED9E40662ULL, 0xB26538975FAC99AEULL, 0x3390B21C7666C061ULL, 
            0x300773FE3066B3F0ULL, 0x9A1142F30B47B4A2ULL, 0x31385E21F3E7E12DULL, 0x79D93270D36FEDD0ULL, 
            0x2537F9470ACB7790ULL, 0x3966168C1490A097ULL, 0x7AA9D9EC9526FA1AULL, 0x89A35E388BC72808ULL, 
            0xBCA09E26F2E3819DULL, 0xC11F67D0F2C29E8BULL, 0x91D36EF77F4C7A4BULL, 0xF8BD62C44B87033DULL, 
            0x75BE40F2311F7AECULL, 0x2107A5A09AC25ADEULL, 0x03046D21D2786E64ULL, 0xFD92D1B9B786C3A0ULL, 
            0x08B7DC69189652C8ULL, 0xBF305A1A5896C963ULL, 0x282C1184D54E31C0ULL, 0x2280197A77779100ULL, 
            0xDD4C57E0A4C82A8BULL, 0xD83AC4B25878A31FULL, 0xBE8BE524851B47E5ULL, 0x6E88222D552B22C0ULL, 
            0xD71E9A7C2BD02030ULL, 0x6107125A101049FEULL, 0x303997543ABB1F2EULL, 0x0901A756A18358F0ULL
        },
        {
            0x66A801CD72C38E14ULL, 0x4B1FA2769A483D27ULL, 0x967DDDC8B3B56B0CULL, 0x777B4E70956816A1ULL, 
            0x712CE59E16A5468AULL, 0x278E2FFE1E30DB58ULL, 0xC4F5535FA156168FULL, 0x76B1F6E3042B9E4AULL, 
            0x44947ECF24FA91FDULL, 0xC3AB8E8B37F5C1C4ULL, 0x970157EB276413DCULL, 0x674FFA01A6CB46ACULL, 
            0xABC195AF18EFA305ULL, 0x9E4A421B6ED8B904ULL, 0x5E45DB106D292D01ULL, 0x6D86860C2CF9E279ULL, 
            0x0EC5BDA2FEAE5C68ULL, 0x866065A2CEB042B7ULL, 0x0F9285BF83638BF7ULL, 0x04CA83557FD487D5ULL, 
            0x62555E3CDFE940E8ULL, 0x4144774C370D6189ULL, 0xDE16742AB0F8603CULL, 0x0317638D1E74DCDEULL, 
            0xE9C52CED4A3AC795ULL, 0xCFE4693ECE11742EULL, 0x2A9A6ED904C96D4AULL, 0xB89E4502CAE4A2E4ULL, 
            0x7A55E8443AE5879EULL, 0x7CAA36AB468148A4ULL, 0xC4A84B4E795BC997ULL, 0x4833D4210871187DULL
        },
        {
            0x9C2D8FD970AA24D0ULL, 0x57D83B1E08DD97CAULL, 0x1751CD73CB0854C4ULL, 0x68366C57EAAF84F2ULL, 
            0x210F0C717285AE52ULL, 0x7AD74C0E556CA9A5ULL, 0x38015C0E63013219ULL, 0xF79F1C75590AA7D4ULL, 
            0x2FED0C2F5C893926ULL, 0xC082B5CB95CA15A8ULL, 0x35CA02A5E1AF0CE5ULL, 0xBB65DC152F84892DULL, 
            0x3795583D24EE4145ULL, 0x3DBBE7CFDAA320A6ULL, 0x823488F7063F7449ULL, 0x57EFB1418CAE1AF1ULL, 
            0xD9530E3A457206ABULL, 0xF3FD59B6C094F195ULL, 0xC6ED64EEE56CFC30ULL, 0xFA74941104367211ULL, 
            0x0B1161669CD3EE3AULL, 0xED44874759D6B818ULL, 0x6219207F97BC1E55ULL, 0x8087C5E5CA68AC53ULL, 
            0x622F21A3953CBAC6ULL, 0x254BFE06446A2739ULL, 0x2B74AC41DE58BFF4ULL, 0xF1D6BF06DA8CB7AFULL, 
            0x091E07147D667D0DULL, 0x74703B81401CAB3EULL, 0x28B700BF579B0CC2ULL, 0x9AAEE702ED057F18ULL
        },
        {
            0x83624FF03E106D1EULL, 0x097AE348FE4C96A8ULL, 0x4D94B1533552CFB4ULL, 0x482370AB1E64ADB9ULL, 
            0x78C56D9D75EAC74DULL, 0x58C5C69C68C1AC07ULL, 0x1F9D66ED598052F7ULL, 0x2AF28FF3FE185055ULL, 
            0xB2D3F107C64ADA6DULL, 0x0ED58934DEE6066BULL, 0xD8E10FC176A8D381ULL, 0x570EBDBAB870C198ULL, 
            0x93DA874ABCC3AB6EULL, 0xD514595FD47CC5CFULL, 0x74751DD9023707E0ULL, 0x024D7C3DCA46FAA1ULL, 
            0x46FF19A3DE8FCF0DULL, 0x629093928ABB116CULL, 0xA882F78F17D3F9AAULL, 0x022D68D98FF48B30ULL, 
            0x279651519AE6A253ULL, 0x6F0530AE71BDB230ULL, 0x99DAE1F6C9B0B878ULL, 0xF0DD211BAB702DCBULL, 
            0x06BF334AA2BBE9C2ULL, 0xB475055F8857E6B4ULL, 0x90EBCB0A20D73443ULL, 0x839A2C105F88C9A9ULL, 
            0x1298DC1A0F6C88A3ULL, 0xA97A1384A0429EEAULL, 0x9245FF374464BFC5ULL, 0x37BC09E3ED9B76F8ULL
        },
        {
            0x118A6F7AAEA7A910ULL, 0x8879215C1F913148ULL, 0x8F59E32703D09A3DULL, 0x5154792E58C7E77AULL, 
            0x23AAA101F3040EE6ULL, 0x509102C671F6B200ULL, 0xC334B98F7F551676ULL, 0xF530D8472D0A8FA7ULL, 
            0x18E52B2E69C7F6D2ULL, 0x9569762F1CC9F6E5ULL, 0x5CBDEB388628E801ULL, 0x9BFF56178848C2EEULL, 
            0xDA19456A3AC3576EULL, 0xF71744538E34E464ULL, 0xC33A15D09639BAB3ULL, 0x40D4C0921838667FULL, 
            0xB11596BFEBFD170EULL, 0x01EDE510E8E86491ULL, 0x0FA05CD4B614D652ULL, 0xF9C8E2176C586833ULL, 
            0x038F12AC6B9645ECULL, 0x09C949661B622B0EULL, 0xDBB39420B9E77361ULL, 0xF15CA9FEA2EBE2D1ULL, 
            0x0DC59D668CE0F8DDULL, 0xA727A48B5BC3912AULL, 0x45E8DCF006108BD5ULL, 0xD96E9D8AFA467867ULL, 
            0xD011CBB00034CB57ULL, 0x73A95092ADBF5C6BULL, 0x533A90A0F6BDD8A1ULL, 0x4E9D1F48E40A5358ULL
        }
    },
    {
        {
            0x3679E6C99732ADD3ULL, 0x331F9A3FA1FEE220ULL, 0xF44D7B57A74F732DULL, 0x11DC19663E70FE67ULL, 
            0x7B98D14ACD42D96AULL, 0x4D681CA2D0A7F98EULL, 0x710997F94BE58D35ULL, 0xD473A128B60F9516ULL, 
            0x187F8C7E6872BEB2ULL, 0x4D587685BAD48095ULL, 0xF5D0FA487BEA4428ULL, 0xEA463043D9F992E3ULL, 
            0x3E411F4F5E4409EAULL, 0xA73D43DB9FC5C966ULL, 0x9092159153B5FE65ULL, 0xCE4A36AE440BCBAEULL, 
            0xE46983DC58EFE240ULL, 0x7A04B55757AC200AULL, 0x486496BA58DDFF2DULL, 0x2A1D2A81E55A4343ULL, 
            0x2B46FC87E3983608ULL, 0xB8A10B5ED8D0DB8FULL, 0x6BB658660A75B840ULL, 0x0778F87BE7CE96A6ULL, 
            0x2AFA4192FD9092E4ULL, 0x71BDC0C853BA6A72ULL, 0x7C7450E216906ECCULL, 0x054EBDB38A6381D2ULL, 
            0xD854FE54DC12D0FFULL, 0xB5A58A95F7B30AF6ULL, 0x160DA3FC690DDC3AULL, 0x4433728794B502FAULL
        },
        {
            0x84CEF010DB4098A2ULL, 0x060D931F1CF2D562ULL, 0x0EE218E5F0AD1CA5ULL, 0x8F542E8EB0EC7211ULL, 
            0xFF669D3A7CC4018DULL, 0x753E839A60EA3869ULL, 0x1D93AAFC5D6E1145ULL, 0x4BA231D6DA62AB29ULL, 
            0x0DD1C6485540AE98ULL, 0x28E9D80EB71B8D4BULL, 0x78104241C1AC1A4DULL, 0xD0B968A82011C9B3ULL, 
            0x889144E101D36EE9ULL, 0xE699F47087EBA86DULL, 0xD30A39E8820C234DULL, 0xF770924D762731E2ULL, 
            0x4ACB3783149FD4DDULL, 0xC4DE877256E1D013ULL, 0xE9022FA556EF228DULL, 0x885BC0252EE5C88BULL, 
            0xA6B0D6DF63E6FDDAULL, 0x31E084A919066486ULL, 0xCD27485953B6B5B6ULL, 0x9CDE69FBF146E593ULL, 
            0x4B15CAD103F369FAULL, 0xF1043B02268B5EF7ULL, 0xC656A6F327097086ULL, 0xCFBEE7A4146895B8ULL, 
            0x6894EAEA72B5F29CULL, 0x7F47277E6726DEF6ULL, 0xE7F399371CC1F46BULL, 0x0B025CB3F898E589ULL
        },
        {
            0x82D5BEC854334BC7ULL, 0xC5D032D4F42317D0ULL, 0xF0CE95C73255ABFEULL, 0x7CB5B26DF402CF73ULL, 
            0x708B711FAA8860E6ULL, 0x4433C07C65FFD7B2ULL, 0x2155AB459AD2F5CCULL, 0xCE3E6BE52420D396ULL, 
            0x9C1EAA67610741F3ULL, 0x3DD7ED14639C95E5ULL, 0xFB4951A140CC2B1EULL, 0xEB4120162B72D7AAULL, 
            0x91C91B12322ADA21ULL, 0x8C7648F608552C3FULL, 0x4278B017209558DFULL, 0xF9A67298F0B29DB1ULL, 
            0x31FF740F389C542AULL, 0xD5FA4BBEB8EB3EA2ULL, 0x42922B78CA8A3C72ULL, 0x93257E61990D347CULL, 
            0x7BF553CE511262DDULL, 0xE6EBAD4619E1DED0ULL, 0x10D87D48B6A1ED52ULL, 0xDD76B1CB18AE6A5DULL, 
            0xB3A5F7A69FDFF160ULL, 0x7A2501D7B2D8F725ULL, 0x513313C047E1B7E8ULL, 0x53DC588C5A3D0DC1ULL, 
            0xB98195B86C57AC11ULL, 0xBBAD58B8006CA7D2ULL, 0xDD860054819BD22CULL, 0xBE785A2FD8F21D30ULL
        },
        {
            0xD8A6DEE0677E43A3ULL, 0x8EB2BD657E9422EFULL, 0xA28DFF15FA128690ULL, 0xDDF47F3C1FCCFD60ULL, 
            0xFA6E1C452413A1C1ULL, 0x777DD375F0199A8DULL, 0x2FE75E53CFB4B464ULL, 0x5AA068339EFB67DEULL, 
            0xE1018AFE0DEB29B7ULL, 0x926B07B1862E8C4BULL, 0x4404F22E2C907D58ULL, 0x8B416C9117CF888FULL, 
            0x9BFCE34FF60C9996ULL, 0xF66302A6094BCFBDULL, 0xA00CF42AEC6C6C53ULL, 0xCB27C884445D1848ULL, 
            0x93556A6E69E9A0F7ULL, 0xF1A1516B51865F3BULL, 0xE4262FBF19B8A8ACULL, 0x7082645C3BB6FF41ULL, 
            0x007697C1E3976979ULL, 0x930410AB62EE5F1BULL, 0x991C39CCC3705EAFULL, 0xA5645AC090F7DD7CULL, 
            0x56D72F602C16B3DEULL, 0xBABA5292837CF79BULL, 0xC59D80581DB0B81CULL, 0x4D6C1B8E4D4E3CE4ULL, 
            0x599A4450E0C028A6ULL, 0x9D82D30BBB5CB180ULL, 0x642797677549E053ULL, 0x89B6F7E993140BB3ULL
        },
        {
            0x0FB952E3F811EBD7ULL, 0xA48417C3D9EA442DULL, 0xF62E279DDE049B17ULL, 0x8F19710DF1F9FC71ULL, 
            0x32BB024E294B9954ULL, 0x762530D5AC444B7AULL, 0x1EF4B053FBA99C4BULL, 0xA0DF9CFE97F3426EULL, 
            0x31D7BC1F71BEC2B9ULL, 0xC1C7DF593E6209CDULL, 0xFB03F31437DBD119ULL, 0xE0078285F2656C3AULL, 
            0x43D2EA1626E21556ULL, 0x7E1F33CD772FF7E5ULL, 0x3CD5E4117C103233ULL, 0x7CDFCABF54C494BEULL, 
            0x18B1801658324AB7ULL, 0x0EA049F1855B6808ULL, 0xB1E5DEAA76A9C7DDULL, 0x669E562207A2392EULL, 
            0xE46F276A6FAAC6A6ULL, 0xD340E5CC397341EBULL, 0x8972847F574E4B82ULL, 0xA15ECC9EB2C237B5ULL, 
            0xCCDB8D3A1176F29FULL, 0x43085693F882CCBFULL, 0xF139CA8BE26F31DCULL, 0x55E8F6DBDAEEA5F6ULL, 
            0x2F6A70348898AFA5ULL, 0x278366CF20D13C81ULL, 0x139F54E09BA2B7C7ULL, 0xC4F2F6CF12A9855FULL
        },
        {
            0x7093476CA3BB5AECULL, 0x11F608FD285AE152ULL, 0x5FCC2E5000EAAC1FULL, 0x21CD39E01E546C06ULL, 
            0xDE550EEBEC4C852FULL, 0x7CBE47011D60FD00ULL, 0xEBC771508894623FULL, 0x72BB13FFEE34E4EBULL, 
            0x8DF9918460749B9DULL, 0x3E51F9AAAD11F135ULL, 0xFAD2B7B45BE5E3F5ULL, 0x5EC96B01D44A2235ULL, 
            0x1B3A0268B72DB2E4ULL, 0xF9C625C42590B3B8ULL, 0xFF3ABF405E383EC0ULL, 0x8968BEEEE0446542ULL, 
            0x1323AFC871466A0EULL, 0xE1BEFB958DD4B93DULL, 0x69D81332CA9817ACULL, 0xAF19C08FF4E0D929ULL, 
            0x7DE712CC5ACD32C9ULL, 0x14B09CEC6F87AF6FULL, 0x4DC3AE9999562C2AULL, 0x6BB76050FC60AFE9ULL, 
            0x54ED399D8B748974ULL, 0x7FD2428876CD05DBULL, 0x11BA8E8E4ABD9365ULL, 0x7DE78FB07AD016D5ULL, 
            0x0D20140F608F4027ULL, 0xE9B923B5A5C95505ULL, 0x9629E4BCE1729866ULL, 0xA57977D39B90CD89ULL
        }
    },
    {
        {
            0xDD6033030EEA849CULL, 0x07ABD9C8EFC9A37FULL, 0x17A582B46BB1FDBEULL, 0x6C485C163AD699B5ULL, 
            0x5735BB0E97CAF417ULL, 0xB0053F7EAB8E87FFULL, 0xF2B99333772E535EULL, 0xF7DFFE058AB39F88ULL, 
            0xAF862576CC33A0ADULL, 0xFA1A36E65E130C90ULL, 0x6D846E894C80F877ULL, 0xE7EDBE9BC1CDAD57ULL, 
            0x89225EE853FFC60BULL, 0xF8190BCA105FA085ULL, 0x1F6D594440EFCE60ULL, 0xE9D32DA26C064BF4ULL, 
            0xF7B13153380D92DCULL, 0xA506D0EB88C56AA4ULL, 0x6F847384EDD7BEE7ULL, 0x3CA30363316CDACEULL, 
            0x5C37E2F09524725AULL, 0x04B6DFA03D0905D8ULL, 0x87C6A6BB3441A7F5ULL, 0x5AD38E24803B1508ULL, 
            0x6455FC798EFC9E05ULL, 0x96C5B1EDCAAF8C62ULL, 0x0C96450C6F2502EBULL, 0xD6FF028B1C5D345DULL, 
            0x07DC8A8FC781708DULL, 0x0A83EADDD3CA5235ULL, 0x7B99FB3F7722654BULL, 0xE26A21BF864ACBACULL
        },
        {
            0xF5DFDB5F9B99C4DFULL, 0xF33EA08BD33A08FEULL, 0x767937AB337BE762ULL, 0xC49A16BD7D41165BULL, 
            0x060D56B2B8550F31ULL, 0xB45635B7B2A90CCBULL, 0x139C1A028D21F89BULL, 0x641212B5F59553B2ULL, 
            0x2279178FC6D912C9ULL, 0x390795B77788DCA2ULL, 0x5434E8836116979AULL, 0x723EE6CB38A85A12ULL, 
            0xAA79DFA5C4A0B0A8ULL, 0x0B8B20F2AC79C958ULL, 0xB6887A3B2A832738ULL, 0xBF5201E8313674F2ULL, 
            0x12165821C366A678ULL, 0xC098C8C05F2E85B7ULL, 0xF965C6A8F2CFC065ULL, 0xF21A3CF50BE58FE4ULL, 
            0xF4AB227769B37A20ULL, 0xEC61B3DD7CB74514ULL, 0x9CD8E24D356D72C6ULL, 0x81F956AC9DCE8A2CULL, 
            0x52CEBF419029054BULL, 0x25D6D8C15DF7E197ULL, 0x48FA2BBC14F83FEEULL, 0xDD101C643CC852A6ULL, 
            0xCFB084163798C0F5ULL, 0x7C4D3272F56C7246ULL, 0x9328C515F58930D5ULL, 0x79C721156AD1FD3EULL
        },
        {
            0x9F0E7F8AF62DA9B2ULL, 0x787867056A6F8CD6ULL, 0x5C83B8622C719329ULL, 0x7862907D8E02CF1DULL, 
            0x1FDB994117A5EE18ULL, 0x9A22D3641D7E700CULL, 0xDCFF9DC020B3F3C2ULL, 0x2CC98DAEC53ABB15ULL, 
            0x26677C3BD609BBB9ULL, 0x879C6C7C6F3EC03DULL, 0x776FBF367EAEBE79ULL, 0xFEF5D82A34081163ULL, 
            0xB99474ACF7CFB023ULL, 0xBD2BACBC1321FB67ULL, 0xC810EC38905B1B2AULL, 0x20557FD9E4E48EBAULL, 
            0x12B0291089D39D5BULL, 0xDF00DA44F840BE02ULL, 0x946B8655E33ECC58ULL, 0xF2243FD0DD525807ULL, 
            0x0A77308F05A76D39ULL, 0x623F6149BE8A852FULL, 0x1365DFB4DC8CDA5EULL, 0x96E9047080B1997AULL, 
            0x629F7335CC110B38ULL, 0x86C3BC87D0518AB8ULL, 0xF4A87A2B4F28EA3AULL, 0xBB4703622515B012ULL, 
            0x27D5792DECD13412ULL, 0x97D36F174B6ECE40ULL, 0x7CDAB5F4109A078CULL, 0x7F1712C478347BA7ULL
        },
        {
            0xE017D6339EF505E0ULL, 0x0E3857FEE3381B5FULL, 0x0BD6F6D8014DC4F6ULL, 0x26A8794DBA8293A5ULL, 
            0xB05237D1ADF0490EULL, 0xFE53BC98789678BFULL, 0x305537063087794CULL, 0x5C78E74832282291ULL, 
            0x4C159E6D48C797E2ULL, 0x92F7A11DC0F9D41BULL, 0x160E66E182409A1AULL, 0xD87E4CAB64808C52ULL, 
            0xB794849CD6C55F97ULL, 0x414E5015993278A5ULL, 0x52093C39FFBEC770ULL, 0xEA404C01250D24B4ULL, 
            0x42F75D86A5ED90ADULL, 0xF954F6C153709587ULL, 0x5FA146162066B18FULL, 0x918434B496C58CCCULL, 
            0x58A5C6B2D3D83A2DULL, 0xE9D87712FE2CACE2ULL, 0x57F77EFFE39E2E5EULL, 0x2E0ED2917A58A31FULL, 
            0x66A9312EE80847F7ULL, 0x7777B59664C6844AULL, 0x50AA8640093DB8F5ULL, 0x139413615BBE3595ULL, 
            0x4D89407F1298E7E4ULL, 0x8C8E346008A308A3ULL, 0xBE60FA5E7455986AULL, 0x7F46664A4D0D6C59ULL
        },
        {
            0x66C6C5602591568AULL, 0x6227567B3936C1DEULL, 0x04FFE6F2A49EF9FDULL, 0x23FF19A06D008087ULL, 
            0x1FA83613C7413F67ULL, 0x5A4F4F7007E0EAC6ULL, 0xCA4FF7BA8DD6BA12ULL, 0xD1ADC99D2F174694ULL, 
            0x0B3D3063D4A7EAB4ULL, 0xD5688AEB59186682ULL, 0xE13ED4ECEBFA8738ULL, 0xF3C4AA0915D4C745ULL, 
            0xB761B4099D505884ULL, 0x936A74A1076A62C3ULL, 0x37B6CFB040147011ULL, 0x9C625FDA497A5F00ULL, 
            0xC839FE453291CFACULL, 0xB6198A27963B551BULL, 0xB0ECBD00D142E024ULL, 0x058AFE0EA15A3930ULL, 
            0x352E68DBA55D9820ULL, 0x1EA286D49A689043ULL, 0x5327853C43D144B2ULL, 0xBE2759FB55EF27D1ULL, 
            0x07C82E003C72947CULL, 0x6675DD334CE682F0ULL, 0x7714BBAC69D8C9C1ULL, 0xA31287810C339CB5ULL, 
            0x91063767E24F45D8ULL, 0x1E0FF077D1C8C139ULL, 0xDB0A07724B096EF2ULL, 0x2D2A2B917517634AULL
        },
        {
            0xA688BD400B3BBB2DULL, 0x6157F82FB603CCA8ULL, 0xA71368E51D01D9B9ULL, 0xFF39130A94A8FD1BULL, 
            0xDD734D7193880BABULL, 0x9EF5FB003073E39BULL, 0x57AE62465CD7D64BULL, 0x12390E41878E4FD1ULL, 
            0x0A0215C680CC5E9FULL, 0xF3CC4F7F511F001BULL, 0x3EBB8F0DE9AF30C0ULL, 0x759018C22CC6EA73ULL, 
            0x013992A0833E330AULL, 0xB2B03B7D31C8E4CDULL, 0xEF9499438B9FD57DULL, 0x036AEF5EC3405748ULL, 
            0x2BC518AEF0447E84ULL, 0x9F4540563BA7A119ULL, 0xC6807A1D527ABE56ULL, 0xA5D507607B8CCEFDULL, 
            0x60873B6D90E2866EULL, 0x2937DAE64BEC462FULL, 0xCE4DD9C1E03DA633ULL, 0x9ECAD11AA16BB2BAULL, 
            0x700AF422481757E1ULL, 0x9C2864347B60166CULL, 0xBD24E0BEA8648C98ULL, 0xE36FA9C1C47DF03BULL, 
            0x6008BE02BFB81D76ULL, 0xAA2A4A22FF3D6475ULL, 0xC88166F16C1CCF47ULL, 0x23D65A86EDD14A0CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mothallah::kPhaseHConstants = {
    0xC6EC0D13B518D2F1ULL,
    0x3A5B59A65CB7B8D0ULL,
    0xEC934BF50C408278ULL,
    0xC6EC0D13B518D2F1ULL,
    0x3A5B59A65CB7B8D0ULL,
    0xEC934BF50C408278ULL,
    0xDE9571311BF4C268ULL,
    0x1C6315C71FB7CDB7ULL,
    0x84,
    0x24,
    0x24,
    0x57,
    0x7C,
    0x3F,
    0x8C,
    0xBC
};

