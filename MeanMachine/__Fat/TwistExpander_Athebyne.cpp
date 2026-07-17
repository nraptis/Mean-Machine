#include "TwistExpander_Athebyne.hpp"
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

TwistExpander_Athebyne::TwistExpander_Athebyne()
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

void TwistExpander_Athebyne::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD114D462225F12BEULL; std::uint64_t aIngress = 0xFABB27D4E23A7636ULL; std::uint64_t aCarry = 0xABD5E228F8296FE9ULL;

    std::uint64_t aWandererA = 0xB833F2E4E9BEA257ULL; std::uint64_t aWandererB = 0x96C7886B0346C50EULL; std::uint64_t aWandererC = 0x9F34BEA70FA89D98ULL; std::uint64_t aWandererD = 0xF21500BF28F9982FULL;
    std::uint64_t aWandererE = 0xF54EA7C94C2B8500ULL; std::uint64_t aWandererF = 0xB7F815684032FC3CULL; std::uint64_t aWandererG = 0xD8CF478207971353ULL; std::uint64_t aWandererH = 0xC41EC20F97418759ULL;
    std::uint64_t aWandererI = 0xA0170FA5960DC1FDULL; std::uint64_t aWandererJ = 0xFBDF1F3D5C31C9F3ULL; std::uint64_t aWandererK = 0xDFE7B8D99EC4D5B8ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13289762420738803959U;
        aCarry = 13651590227047939742U;
        aWandererA = 15248522263025428273U;
        aWandererB = 17588796271909304321U;
        aWandererC = 13186505049285097545U;
        aWandererD = 12779266329511281630U;
        aWandererE = 9977592036120917309U;
        aWandererF = 11377612529510918814U;
        aWandererG = 14672597077240904416U;
        aWandererH = 14431673795724076256U;
        aWandererI = 13066058005825309480U;
        aWandererJ = 17380231256713930613U;
        aWandererK = 16574760776124591238U;
    TwistExpander_Athebyne_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Athebyne::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD39F082CC2AED5A0ULL; std::uint64_t aIngress = 0x90A3C2B45CA3469FULL; std::uint64_t aCarry = 0xFA180D68F0FCF6A8ULL;

    std::uint64_t aWandererA = 0x99712465020EE65CULL; std::uint64_t aWandererB = 0xDC3ECEEF70DDDF6AULL; std::uint64_t aWandererC = 0xE495787A775BE818ULL; std::uint64_t aWandererD = 0xD7C051C8B5CB05A6ULL;
    std::uint64_t aWandererE = 0xD0FDA78E9C3A738EULL; std::uint64_t aWandererF = 0xF9478E1A9142C554ULL; std::uint64_t aWandererG = 0xA79BD734D9C59B10ULL; std::uint64_t aWandererH = 0xE56FE99A5B477DBEULL;
    std::uint64_t aWandererI = 0x96AF9E1CC92FE90CULL; std::uint64_t aWandererJ = 0x84AD00C554D261E4ULL; std::uint64_t aWandererK = 0xCBD8B5E7DC6C5CCDULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11977701324581374315U;
        aCarry = 9658745936484489963U;
        aWandererA = 13048996938675954848U;
        aWandererB = 17698405675625319929U;
        aWandererC = 9700310277562743063U;
        aWandererD = 15349670175048350322U;
        aWandererE = 14470036887636545133U;
        aWandererF = 11604880505540973012U;
        aWandererG = 16655079708970851160U;
        aWandererH = 15251484499380829356U;
        aWandererI = 10841159753551179523U;
        aWandererJ = 16635383696130170089U;
        aWandererK = 17217307085501144235U;
    TwistExpander_Athebyne_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Athebyne::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xEE83A1E676437805ULL;
    std::uint64_t aIngress = 0x8BA4CCF1C4CEA7FEULL;
    std::uint64_t aCarry = 0xFCB5ACD47C73BC8BULL;

    std::uint64_t aWandererA = 0xA32136A494922766ULL;
    std::uint64_t aWandererB = 0xFD677B6FBF2339B5ULL;
    std::uint64_t aWandererC = 0xD0C26038E1910EBCULL;
    std::uint64_t aWandererD = 0x813138B57A6A7EA4ULL;
    std::uint64_t aWandererE = 0x865D8BDD34C95136ULL;
    std::uint64_t aWandererF = 0xF5F631A5C337B954ULL;
    std::uint64_t aWandererG = 0xF9D843345203C28AULL;
    std::uint64_t aWandererH = 0xA0C27EC81C7D6C8DULL;
    std::uint64_t aWandererI = 0xD24E549139F113A2ULL;
    std::uint64_t aWandererJ = 0x8D6962166DBAD90BULL;
    std::uint64_t aWandererK = 0xB7A2C957C91B2CE7ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
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
    TwistExpander_Athebyne_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_D(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseEConstants.mMatrixArgD;
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
    TwistExpander_Athebyne_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Athebyne_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 11 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1849 / 1984 (93.20%)
// Total distance from earlier candidates: 18633
void TwistExpander_Athebyne::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 76U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2026U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1015U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1773U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1972U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1178U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1273U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 180U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 416U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1826U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1060U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 104U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 958U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 94U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 805U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1997U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1665U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 447U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2025U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1482U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 871U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1049U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1024U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1429U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 251U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 189U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 566U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1080U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 662U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1841U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 403U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1122U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 595U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1941U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 99U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 0U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1738U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1258U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1922U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 28U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 119U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 982U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1155U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 308U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 95U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 18U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1202U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1012U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1631U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 652U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 232U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1880U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1048U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1655U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 990U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 970U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 162U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1210U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1034U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 698U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2013U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1356U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 526U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1115U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 160U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 230U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1968U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 515U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1742U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 988U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1127U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 381U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 229U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 492U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 868U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 791U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1324U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1174U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1460U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 842U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1110U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1221U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 914U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 100U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 201U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 720U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 794U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 717U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 918U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 935U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1422U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2021U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 387U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 505U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 428U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 171U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1932U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1791U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1082U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 696U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1136U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1411U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1650U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1578U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1114U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1087U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1815U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1391U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 751U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1829U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 457U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 223U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2023U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 880U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1002U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1564U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1211U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2032U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1446U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 314U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 745U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1857U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 985U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 521U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1906U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 572U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1162U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 412U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Athebyne::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA405FED948B6ABB9ULL; std::uint64_t aIngress = 0xC96AD7405C17CB3BULL; std::uint64_t aCarry = 0x881420E2C80164F0ULL;

    std::uint64_t aWandererA = 0x935F454FFF8A3D18ULL; std::uint64_t aWandererB = 0x83868D359EC08399ULL; std::uint64_t aWandererC = 0xD909432172B80C11ULL; std::uint64_t aWandererD = 0xEA116171B3F24394ULL;
    std::uint64_t aWandererE = 0x8C1812F34949A653ULL; std::uint64_t aWandererF = 0xE8506DBF900CCB7CULL; std::uint64_t aWandererG = 0x9843FA0A0D02FDEAULL; std::uint64_t aWandererH = 0x8974D2A8BDF38937ULL;
    std::uint64_t aWandererI = 0xEA857333994C4070ULL; std::uint64_t aWandererJ = 0xDE1D58E449BB9724ULL; std::uint64_t aWandererK = 0xE0848BCEE50300CBULL;

    // [seed]
        aPrevious = 12982061218614781166U;
        aCarry = 12418826958851605760U;
        aWandererA = 11172894153070549250U;
        aWandererB = 15996496562312281295U;
        aWandererC = 9964190067293050202U;
        aWandererD = 11839396750488929314U;
        aWandererE = 14552945796795348174U;
        aWandererF = 15779204091070751484U;
        aWandererG = 13458239406275281021U;
        aWandererH = 10873594679914325468U;
        aWandererI = 14696534047367288311U;
        aWandererJ = 10541345742658985703U;
        aWandererK = 13168348065993869831U;
    TwistExpander_Athebyne_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Athebyne_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Athebyne_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Athebyne_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 11 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 5538; nearest pair: 510 / 674
void TwistExpander_Athebyne::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4469U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6347U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5350U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6183U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1104U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3375U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2140U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3901U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2392U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 978U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1097U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7115U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1003U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5637U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5032U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6448U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1109U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1692U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 502U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 222U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1274U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 869U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1249U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1464U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 49U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 822U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 347U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 735U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 61U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1244U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 728U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 942U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1270U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 191U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 723U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 677U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 11 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 5535; nearest pair: 500 / 674
void TwistExpander_Athebyne::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7783U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3499U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4223U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3554U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4667U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 709U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2860U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3352U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2217U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 575U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2636U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7709U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5571U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6882U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3675U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5484U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 842U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1676U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1986U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1420U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1768U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 985U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 550U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1336U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1091U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1562U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1746U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 419U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1122U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 452U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1174U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1236U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 843U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1938U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1812U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 982U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseASalts = {
    {
        {
            0x89B5AC2F918BE919ULL, 0x1D46FD726E1264B1ULL, 0xE4AD3B69497B807FULL, 0x1B0424E4C2F246A4ULL, 
            0xDB77B34F6F42B2CBULL, 0x28661796E6B41E21ULL, 0x66268A308C9F04BFULL, 0x3E166F2F94B7DA44ULL, 
            0xF2BDFAB2C69E6E0DULL, 0xDF8B72F413EE3CBFULL, 0x8FFC7FE9EDE1BDF0ULL, 0x5C410D4330EB1EDEULL, 
            0x769D12060F4073BCULL, 0x7147DED17BC8502EULL, 0xA20EF49EB8AFD428ULL, 0x30843C922E20835DULL, 
            0x0327FDE45279B04AULL, 0xD99344ED61ABC9E9ULL, 0x21F73E53FAA5E8B9ULL, 0xBE37924302EE4573ULL, 
            0x09E1004F5BA151A6ULL, 0x4AC8DDABF7747663ULL, 0xD9B834E0DB28E266ULL, 0x750871E551AD9117ULL, 
            0x3F36F50D7DE6F58CULL, 0x76EFD45269AE5CD6ULL, 0x08F523144D04CD2FULL, 0xC51555F86F7BDD88ULL, 
            0x075DB3B11243F41FULL, 0x31A6DAD1FAECF0ABULL, 0xC213AF5BF6A9349AULL, 0xD80B6C4DA80D0F30ULL
        },
        {
            0x21E4A2E8D6F503E4ULL, 0x8913D2A64D2B5799ULL, 0x902DEBC093D58376ULL, 0xB6D9BADCF55B242FULL, 
            0x01EB766CEEF41993ULL, 0x687A3F88D073D4D9ULL, 0x29154903C24AE73CULL, 0xEF57DBD863290FE7ULL, 
            0x0A9EC850874DC4EFULL, 0x62AE3F39ACC1AE87ULL, 0xDE7366DA16CA7202ULL, 0x583538ECF2F7075CULL, 
            0x70DDE8A65D3D7F1EULL, 0xC0B4B624387B6BF8ULL, 0x052A89A121A29636ULL, 0x90B02DB54BE42D0CULL, 
            0xBB9EFB8362136BDDULL, 0x806F940EE95AC9E7ULL, 0x48131727359CFDE1ULL, 0x003BEE86BD95D8FFULL, 
            0x2736CFF231A4FCE5ULL, 0x9FAEEB70EB9D941DULL, 0x45C52F1B17AF190CULL, 0x1A369E9767E3DFDBULL, 
            0x4400FE079F1930FDULL, 0x685162A3B4511EB2ULL, 0x0BF09F873AD987C8ULL, 0x916D19E01988467EULL, 
            0x9198332E8C3AD38CULL, 0xBDFAE200D29B8BF3ULL, 0x96F57B0F75605F43ULL, 0x88A069BEA2BCA02CULL
        },
        {
            0xD23D975EFBF1EAB3ULL, 0x4AFCB6DAA07B00D1ULL, 0xDC09196702D0EFD1ULL, 0xEFCA8B98CFDF185FULL, 
            0xB197FB79D1254366ULL, 0x8206E0C1899C5CE2ULL, 0xA2564D17A3C4D75FULL, 0xAB0CDB80B38976D5ULL, 
            0xF700358EB09F92B3ULL, 0x9E9E526E1B223CDAULL, 0x263490D2D52AFCACULL, 0xAE0C18A10630B892ULL, 
            0xD8FD714E96A89685ULL, 0x467FA1EECE79C830ULL, 0xA2E8AF7188A195AEULL, 0x88FE77828AB6D2CAULL, 
            0x313D8DEFDFB7E026ULL, 0xF27CBCD1E488052CULL, 0x31E90E94081718C1ULL, 0x80F3BC642562AB97ULL, 
            0x72CDDBD4657760FCULL, 0x6F59702918B2CDA1ULL, 0x2D6D2AC3C26FDD6BULL, 0xC456009029BA75FCULL, 
            0x494BB3BD82A555A0ULL, 0x737C30841D1B34F0ULL, 0x1145BD312C5CD4FFULL, 0x026B08B4F850DDCEULL, 
            0xBDAD93A987C660F0ULL, 0xE1EE9FD4CFA8D80DULL, 0x12E7B1B216D3C72FULL, 0xF77E0935AE87A423ULL
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
            0xA1CC2CA9263E81AFULL, 0xA8E2EEC7A3FD0EF8ULL, 0xC2DAE75A43F1B3B1ULL, 0x2FCDAF51CC33E32CULL, 
            0x252AAF04C6620CC9ULL, 0x2F890A0FB0084EA4ULL, 0xA0C3540E2C4BDD89ULL, 0x2CA197DFFC99E3D9ULL, 
            0xEEFB07FFFFB2BD39ULL, 0xA0CE6D52A8CD62A4ULL, 0xE707471B64B5EF5DULL, 0xA141F5BBA927FB12ULL, 
            0x0102BA41875298F2ULL, 0x7A44E3099FF5C84DULL, 0x79A80D34D80ADF70ULL, 0xC617B995B67255D7ULL, 
            0x53F02D1406AD643CULL, 0xE5F77353B4277A1CULL, 0xF895808FAA3BC30BULL, 0x81C97DF438477665ULL, 
            0xB09614094D68C719ULL, 0xC3807F95585419D1ULL, 0xC7284D7E086DBCEDULL, 0x785B745B9AAEFB45ULL, 
            0x31417449268045D6ULL, 0xCA49BE6DD698C72AULL, 0xE368D59892281E86ULL, 0xFA932CE353EF3F13ULL, 
            0x3DB0EE94FB21FFFCULL, 0x45773A942877D94DULL, 0xA366DA68B0FA581FULL, 0xDDF325EC63981AB4ULL
        },
        {
            0xD31ACA376DF498C9ULL, 0x1E64035B691F2118ULL, 0x82E9B68D33E6CCFAULL, 0xEEF98EAB90F7260BULL, 
            0xEB66EF823470FCF8ULL, 0x7EE5BEFC1916CFFBULL, 0x493229332C112983ULL, 0x13EA1A1ECA916C22ULL, 
            0x91B3E2FC2BD0CF6BULL, 0xB2B7361E9090090BULL, 0xF1065B93EF741A80ULL, 0xBD35245620FE2891ULL, 
            0x4580FD991D2259F4ULL, 0x238386D59DFEEBE1ULL, 0xA416C60498AC6E67ULL, 0x5A06FEB4CD94E296ULL, 
            0xC088ECEBE5881FDCULL, 0x0D1475BD9A2791E2ULL, 0x9ABC999DC6C3DB10ULL, 0xABBD96FA852C2E12ULL, 
            0x2204A7202AFA7415ULL, 0x5441EE839DFDC4D1ULL, 0x42953D9A3FE0857FULL, 0x2E9F238F7E7A8FE4ULL, 
            0x26DB0A73E3802E71ULL, 0xB86AF5C2EEF57AFFULL, 0x5B4AAD6DFF66D85EULL, 0xFA2FAB92CFD86961ULL, 
            0x8AC6D9E15AF1BD50ULL, 0x819949836F28B7CEULL, 0xACE2E8A30C495EE5ULL, 0xF8DD2CE9ED2A29FBULL
        }
    },
    {
        {
            0x1EF12D91345216E3ULL, 0x6E2FB96C3B526EA2ULL, 0x68D4CD00CB431AABULL, 0x11E69F27D425EF89ULL, 
            0x181EDE0BC2889716ULL, 0x795B7C9F3975EF15ULL, 0x062F334E606928C8ULL, 0x5B255E1FB0B24CF1ULL, 
            0x80509A24F429D435ULL, 0x174F6A08A2D1EE59ULL, 0x20A27748A8666443ULL, 0x1503AD307BC52ABEULL, 
            0xB16447A67C591FD8ULL, 0x55C26E3C4924C46FULL, 0x0CDA30538985D24CULL, 0x6D30495B4403F46BULL, 
            0x4F5236399A3A1C64ULL, 0x6387B9854B9619CDULL, 0xFABF72D4B3A69300ULL, 0xBF6DD1787A085E7DULL, 
            0xA8424B399236885DULL, 0x58D191BA7EC284E7ULL, 0x07963DE4DB4DF89BULL, 0x9411E92E1023673EULL, 
            0x2757B0858D033E04ULL, 0xB7142C47D9999C1AULL, 0xF66CC2BC55703D6FULL, 0xEE7BD440A72DDF56ULL, 
            0x56CB92F08CAB5A5CULL, 0x8D7BE44500CA0DA3ULL, 0xD3199AD0EABB741DULL, 0x79AAA12084435AFAULL
        },
        {
            0x7EC3F4C7134A88E5ULL, 0x9747DCD48C81BCF4ULL, 0x67C2E3C13F068189ULL, 0xDAF434823472DA0FULL, 
            0xC690185DC86BB426ULL, 0x666869974A5403E7ULL, 0x01811C2DCFBA11E6ULL, 0x347D9DE5B1F02FEEULL, 
            0x4E35FCDD2C0BB734ULL, 0xFD79BE2B470549A8ULL, 0xC2C0CFE51DD45F58ULL, 0x17BF5BE2B87244CEULL, 
            0xE8FDCDBB75A916CCULL, 0x389DFF9C69A8AA61ULL, 0x774BF3836881A3BFULL, 0x083CF4A4B6E31179ULL, 
            0xFF88F555644BA743ULL, 0x15F83D836A2D874AULL, 0xD59FCA8029265CB9ULL, 0xB9F877762E5473A3ULL, 
            0xE420EB113BC1E22FULL, 0x1BD1FB7AD4D3351CULL, 0x5A7E288F472E2DC3ULL, 0x5610016D2BAA72C2ULL, 
            0x7096530FDA9FDAB0ULL, 0xDB513AD2599DC5C2ULL, 0xA41BD1725BCF4683ULL, 0xAF4E4C47875AB3C8ULL, 
            0xFD54404E74330B82ULL, 0x80293BF33FBE2609ULL, 0x5A52FDE3569BF884ULL, 0x7906CEBC1FA37564ULL
        },
        {
            0x2FD17AAFDA524002ULL, 0x926710FF1E5444D3ULL, 0x88FDBFB95F27E70CULL, 0xEBECD12620D8BAC0ULL, 
            0xB501D9CD924DD4BDULL, 0xC91A69DB5730E123ULL, 0xA32935FE1D4A38D5ULL, 0xA436CAF5B97273D8ULL, 
            0x54F2570BCC236316ULL, 0x2A4EB24D8BAA20E0ULL, 0x285FD01E37D82FA5ULL, 0x0AD17F47DB7C31ECULL, 
            0x16E5D77CB63DDEDEULL, 0x896CEB32C8D99DB9ULL, 0xAB2D44F3B3A8C041ULL, 0x7985035962B7EAA2ULL, 
            0xEA52DC01C7B9E2D5ULL, 0x6877A74C82514AA9ULL, 0xD48A5FE348F9331EULL, 0xFD811943138E3B80ULL, 
            0x01E33742452869DDULL, 0xECC0F210249E82FCULL, 0xF9B40FFC27990563ULL, 0x82BFE2BA361BACA1ULL, 
            0x932E2906A4661977ULL, 0x9289F3D6A9A49F8CULL, 0xB9EBB93EA1B48CD2ULL, 0x7B5FC716341CF735ULL, 
            0x439FF50780E6D0A2ULL, 0x2ACAB284BA359CBBULL, 0x07A94DD79BE74269ULL, 0xB74CF4CB2D865C0EULL
        },
        {
            0x1BE0978AFE0884B5ULL, 0x4C6E5DEB29418A22ULL, 0xED12C52D8709FF06ULL, 0x836D5CE07F94826DULL, 
            0x14FEF7BAF5079366ULL, 0x82775FEE871C983EULL, 0xD6B6742732AFF81BULL, 0x74200D40233A40C3ULL, 
            0x3ADD75FC4F34FBF7ULL, 0x80A9FA8CA5526D9FULL, 0x886132F0240AA672ULL, 0xB02AD637EFB4DA5EULL, 
            0x9175A8A936810EBFULL, 0xB81524C74BE8E9FBULL, 0x4DC8CCB36184333FULL, 0x2543EA11BCAECC30ULL, 
            0xDCA9B256492AD7F2ULL, 0xD5D7BF48A3E3861FULL, 0x19B55B04DAE61B8CULL, 0x87E2AAA70BC8C3CAULL, 
            0x5A4E1DAF7C769BA4ULL, 0x43B3D4CFC68C6434ULL, 0x97F9A9E0CDB9EFF6ULL, 0x49038A245202DC9EULL, 
            0xD84CEFE4401EEBDEULL, 0xFDFC7677B32EE8ABULL, 0x070ADB9C055030AEULL, 0xF4B682FD98F5769DULL, 
            0x87536451AE7E0D69ULL, 0xB02D426083798691ULL, 0xC2AA64BB915E91AAULL, 0x9FAA3CF8E0D52213ULL
        },
        {
            0x4E4894253D152FB5ULL, 0x9C2D4A5296BB51F3ULL, 0x284ABEA1B4E0C57EULL, 0x4F0346C4C4FB6321ULL, 
            0x6BDB35111192AA8EULL, 0x4410FE0FF393C0EDULL, 0x623CF395D938179EULL, 0x2245AB80DD115A9FULL, 
            0x13304A6A54D175E2ULL, 0x1C1A9C29EB771540ULL, 0xC96087B541D11D12ULL, 0xF837A57749C708BFULL, 
            0x8813FE0700F1B454ULL, 0x6602538E684EDFFFULL, 0xE3FCAD1AFF0BD732ULL, 0xC1EEFC0855BDCBC0ULL, 
            0x5377013315EF8403ULL, 0x70A02939C89045A2ULL, 0x4E7DCC504947C55BULL, 0x3A3AD89E45009C62ULL, 
            0x2EB66C7E99944951ULL, 0x1DB9F8730FB656F7ULL, 0x43B160F83B27B752ULL, 0x6E367D56831FDA05ULL, 
            0xA58C6B46E7A1F06EULL, 0x0F59A16BE3D07A89ULL, 0x4613008E4E74000FULL, 0x95B3DDC049BB90E3ULL, 
            0xED4E79F89C74BC90ULL, 0x188D223129F94F70ULL, 0x2FF8DF8D426F74A7ULL, 0xBF51564D0DAC0677ULL
        },
        {
            0xF924383726ED4023ULL, 0xEBE406CCA5153627ULL, 0xE7B4878D2CD8C0A5ULL, 0x2FA31FADC30A3F4EULL, 
            0x445128A237E9D55CULL, 0x9A8FB08EC5CDAF40ULL, 0x64708CAEEC8A987BULL, 0xEF9E2471B033AD39ULL, 
            0xA2A84E23A7BC725CULL, 0x52D543EE4C48C9E5ULL, 0x2747056A9B6B827FULL, 0xCB583A8DEF6DFF7EULL, 
            0x0A2A2428A16C524EULL, 0xB2CB2A725AFDEC2BULL, 0x6D99FE04FB06E86DULL, 0xFB853F3CB4D2214FULL, 
            0x10D62AF4E3802272ULL, 0x820F47BB2A7AFE46ULL, 0x8DE0A1FA2C45C279ULL, 0xF1F1B6CF8DD8D7A9ULL, 
            0xA522E61A7FE30F7FULL, 0xBDD4BDE2A6EFCA32ULL, 0x24313676C4794B02ULL, 0x55A5AC0F8CF04330ULL, 
            0x304C824378F6730AULL, 0x89B6ECD4DF3FB7BCULL, 0x0FED95E85521C97FULL, 0xE745410364829615ULL, 
            0x6BDEDCE399B3410CULL, 0xE9D251CE58AFB7E9ULL, 0x55DF788CBD39E7BDULL, 0x046BF9383F03DBA9ULL
        }
    },
    {
        {
            0x60227C5CA5EFEB53ULL, 0xBF041211B8B53900ULL, 0xEC00654588F7D114ULL, 0x6F5AFD39F0CF2640ULL, 
            0xD841D9AA03ABB895ULL, 0x1D56C7E7B138FB3AULL, 0x93B62909DDD4A4AAULL, 0x13B3AA2FEDFFB2DAULL, 
            0x7E0BFCBEB879BBD4ULL, 0xDCC4E4E6F5F325C8ULL, 0xF1828876CD85ABCEULL, 0x0EE6B2DF1F1CE667ULL, 
            0xE6D989B882EBE6E5ULL, 0x740379C9F4455441ULL, 0xCB6421F1D199FB03ULL, 0xE4ECCFC06B0BCA8CULL, 
            0x6D99F6344CE01259ULL, 0x5BB9D4B60201160FULL, 0x3EF991EDA10A9F17ULL, 0x8DC60E95280A7CE3ULL, 
            0x4D08EF41C7E92271ULL, 0x9E4830FF44052591ULL, 0xF8D2C7BD7ECC9D6DULL, 0x5D9913398903A51EULL, 
            0xE7B04AED03ECB436ULL, 0xAE776E92FFAD2734ULL, 0x37A39189131C2441ULL, 0x3F9D571870C9E3DFULL, 
            0xB7CA3EF4A8B3BD15ULL, 0x650D8CD3C1017740ULL, 0xFEC7574FEEC93A39ULL, 0x74E6BDD5A6606489ULL
        },
        {
            0xE40283DA51682955ULL, 0xE88964CB8D447123ULL, 0x50790DC617ABF2ADULL, 0xC35DFEAB36637163ULL, 
            0x60BE9764FCAF7EC7ULL, 0xEB7EAE58785F3D8FULL, 0x47582ED8157B7B88ULL, 0xDAB536C55026FD24ULL, 
            0x91505D6B66A3AE96ULL, 0x0FB87CB71E9F865EULL, 0xACE13AEC40F7F816ULL, 0x60FE2D05F52CF80FULL, 
            0x0514F29E26364349ULL, 0x1100DA100F1F621DULL, 0xF46A3A5C513BE8A0ULL, 0xAB1E20795407BF61ULL, 
            0x03FA365429AD9684ULL, 0x2ACEF41C367569B9ULL, 0xFEA715FFC3162E7AULL, 0x3E44CFBEB492FAC3ULL, 
            0xE2B773F175EA47CFULL, 0x8599CC49471F3E92ULL, 0x8F2B55D858BFD7C2ULL, 0xE071B5154FA32AE0ULL, 
            0x18D14316D1749AE9ULL, 0xD657AD9C859417EEULL, 0x9DFBF6270F559A7AULL, 0xB5F83E90C07EED23ULL, 
            0x86E31F1220ABF067ULL, 0xCEF51C9D3EAFB78AULL, 0x8E4A826FEEB695D6ULL, 0x0CC9C21EE879A088ULL
        },
        {
            0x5F97EA224B1A0DA4ULL, 0x6FC75F26351AA14AULL, 0xF9BC515287C7D8DDULL, 0xC4B6AE906CF1977AULL, 
            0x8CFE4B9009FC8780ULL, 0x465A8AA8D259AD82ULL, 0xD4A7C431CC5BB467ULL, 0xF585565F803AB923ULL, 
            0x0F859FCAF58FC55DULL, 0x9D4B0AF9B2F7FF5DULL, 0x11886E63288EEEAEULL, 0x019F0E5D7EBA06B0ULL, 
            0x8D38348FAFF2993EULL, 0x04B02B3C0B316EE8ULL, 0xB67487015119CD48ULL, 0x6B849C353361E864ULL, 
            0xB448D610145224E8ULL, 0x2455DA50F326FF5AULL, 0x3C545D6C37D706D5ULL, 0x1ECB6B01B9D1361BULL, 
            0x8C3DC58443E5C5E0ULL, 0x13DBDC31407097FEULL, 0xC8749C35658FFB2DULL, 0x33A0D7D20E3EB566ULL, 
            0x9ACC0ED965C4852BULL, 0xC707E51C01F7C984ULL, 0x1CEFB422C4E54DC3ULL, 0xB9807640F80CF922ULL, 
            0xED1BC85A173388A6ULL, 0xA4DC3A2651949337ULL, 0xC43E8BB9C48218E3ULL, 0x46C1BD6F4997EFCCULL
        },
        {
            0xAAB27FEABBAD3E66ULL, 0x4845276D4E65CC0FULL, 0x3DC5DC83805169E1ULL, 0xE8318B762A1F38D6ULL, 
            0x7BAC3031FB187CA9ULL, 0x5C102D0929AB2480ULL, 0xCAB747AE4B1B980DULL, 0xA3D08FA07400AD8CULL, 
            0x1C43AD5A1B6C607DULL, 0xBA67136690F0D96AULL, 0xE66A5FD3F49FD04BULL, 0x656D1B13F61F1A92ULL, 
            0xA067712081F99AF6ULL, 0x4C35B36B76F22464ULL, 0x2A433D6F20DA1D4DULL, 0xB292FD5386EEC2F9ULL, 
            0xFC1AC1906B578367ULL, 0x3557CD1FCBE0517FULL, 0xE0E864364CD1ADD4ULL, 0x2410E4D723156F2AULL, 
            0xEE9A779C4A2312D8ULL, 0x34309B79906EB066ULL, 0x88AFF2E484466EE9ULL, 0x0F134E28B7574C6CULL, 
            0x3BD284ED33D56E9FULL, 0x645E133696DAD640ULL, 0x6CD264248147AE1AULL, 0x71017B9384C38DC9ULL, 
            0x445BBD82823DA8EAULL, 0x0973EDA050A969A6ULL, 0x4B48B8488DE9D8AFULL, 0xF4A555AA76EEB767ULL
        },
        {
            0x6ACE503AA6E527C2ULL, 0x6627D675948DDF7BULL, 0x6DCAB2BAE3743FF0ULL, 0xDFD8700CACCA60C3ULL, 
            0x3DD188B0B410850EULL, 0x0F30BF45DF786CE1ULL, 0x393B02082FC4C9C0ULL, 0x50491B1D1E8A850DULL, 
            0xD96AC531DFA1433AULL, 0xB6442917C2368614ULL, 0xC537EA7DCA7F0D42ULL, 0x7AA8049B356B6FE1ULL, 
            0xC781BD4298635C85ULL, 0xAB8758962918C3BCULL, 0x2CACD50B931E7BE0ULL, 0xD7EB4191CBA33DF9ULL, 
            0x971A2F1E0657D337ULL, 0x24968FF36FD7C39CULL, 0xEB16F7D2CBAEAA8FULL, 0xF16FE44EB1B9E34DULL, 
            0xB28CE2674FBE0980ULL, 0x886C6E8EA600E3CCULL, 0x6745FE8CF94033B8ULL, 0x5975B9C7CE1BF426ULL, 
            0xAD7836E66614097FULL, 0x7F9D36FE5AFB46A6ULL, 0xD754DB8024F0F918ULL, 0xDFB4EC04A1B3F4FAULL, 
            0x29AD9410ABCE818BULL, 0x1A0705668BCDEC4FULL, 0xF7CC34647EE4C3B7ULL, 0x925E48C3B91EF835ULL
        },
        {
            0x6903AFCAD1463233ULL, 0xED2CEEC2836310BDULL, 0xB5E6598921DD48ECULL, 0x5554D09BF5ECDB57ULL, 
            0x2E8A5AF8AEC44F69ULL, 0xBED506C5AFE86683ULL, 0xB53268C86D738EC1ULL, 0x306157519019B2FEULL, 
            0x14C40A70E7506DFDULL, 0x3503DBA3157AC318ULL, 0xD0941C8EA9D26A61ULL, 0xFCED4839CBDE9D0DULL, 
            0x4C0C4493FB3DEDEBULL, 0x604D50368F172767ULL, 0xAF9F6C825A2A80B3ULL, 0xE05FA77B411F0631ULL, 
            0x930CEA6E2D4D734DULL, 0xDB59D79C7A27EEE2ULL, 0x38BDB990869ABC31ULL, 0xBC82C7154AD83D44ULL, 
            0x09F5136E4D7EFF5DULL, 0x3554EE47EDEC327EULL, 0x984A647F358292E2ULL, 0xF0E173982918BFF9ULL, 
            0x0581E9DC670C6A4EULL, 0xDE91F1B56A621536ULL, 0x19F46E7517F3414BULL, 0x216FCBDF6B9D5FC3ULL, 
            0xA7BBD386853A7410ULL, 0x608967C8134C2030ULL, 0x86F29A9BA1BC120BULL, 0x006357F6CC86C7FBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseAConstants = {
    0xFC8B30B489B07639ULL,
    0xFD75C07CFF930E35ULL,
    0x3DCC940505A637C3ULL,
    0xFC8B30B489B07639ULL,
    0xFD75C07CFF930E35ULL,
    0x3DCC940505A637C3ULL,
    0x83A9DAF1E0363E09ULL,
    0x384DC97B428208CEULL,
    0x47,
    0x61,
    0x41,
    0xB3,
    0x3B,
    0x7F,
    0xA0,
    0x1E
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseBSalts = {
    {
        {
            0x0ADBE60317CDC919ULL, 0x65DC7925DA0C38B9ULL, 0xD78AD247360837EEULL, 0x73F54CC1C6F99AC3ULL, 
            0xF1F06EDD2F0C33EBULL, 0x31A19D6CDCD303DFULL, 0xE6146F5FD923E846ULL, 0x59B13FD14A5304B6ULL, 
            0x01C36817D6FE0C40ULL, 0xDAEB47BC00051F61ULL, 0xAD469468251795ACULL, 0xBB7DC4B9CEE5D0DCULL, 
            0xBF5163C7978CC389ULL, 0xCEC36AAD10FD6363ULL, 0x7253C6AC841912B4ULL, 0xC1A1E97C5887BF32ULL, 
            0x4228320EC4BB8880ULL, 0x1B336FD8C14E18CDULL, 0xBEB5EF10CEB32424ULL, 0x2FF665D081EE8574ULL, 
            0xA4D21C72829B3909ULL, 0xC8E08BAB394248C0ULL, 0x9D881399E34AF6FDULL, 0x14200DF5B3C72B03ULL, 
            0x93D15B3B9C7A1B4DULL, 0xF7B206262E856E4EULL, 0x9347396095AAB11DULL, 0x53822B87A1BDE74BULL, 
            0x997D4779BDB4F2FEULL, 0x8A7C2A84608034EFULL, 0xEA6F969506A47EA1ULL, 0x0963041E539173DFULL
        },
        {
            0x5187D005D6D0CD08ULL, 0x66800F29BDFD65CEULL, 0x81A26600D926EC29ULL, 0x275488BB85CDB15CULL, 
            0xFED028FC73A65C5AULL, 0xA5FEC69A456544F2ULL, 0x9DFCFE15D0BA814DULL, 0xE45B69C60C7397DAULL, 
            0x7C2B351E441BDAA6ULL, 0xE35D75E27924B456ULL, 0x1DFE680BEC2EF7F3ULL, 0xCB2E3E06BFD1A97AULL, 
            0x21CF129A7230687FULL, 0x8E6578597CA3786FULL, 0x66AB552875A6E267ULL, 0x915396A1EC8B6902ULL, 
            0x6E1E05D1F8D5B53DULL, 0x131135403024D4A7ULL, 0xB145006A7A69CB51ULL, 0xCD565C1FAB7937B9ULL, 
            0xC933E2D8DD9D1B6BULL, 0x0E953A9079AFD71AULL, 0x301283067B2F345DULL, 0x2C6249C8EC587BE3ULL, 
            0xDC9AC8484DBBFCC9ULL, 0x867DDEA1E3EFE467ULL, 0x660F704A06F8022AULL, 0x8F374572932B10C2ULL, 
            0xDA640B61BDB4082AULL, 0x6A8B7D89A9D3D0E8ULL, 0xAD1DD00961290A40ULL, 0x5EC2A71C5F3E952DULL
        },
        {
            0xC866C107EDCC0A22ULL, 0xE67A9F43278E0FCBULL, 0xC4683F793C8F72E3ULL, 0xBE0C608D962810B0ULL, 
            0xDF0AD6B714735730ULL, 0xFA82D0398AB3EF5CULL, 0xB3362405C1F78C8EULL, 0x00ECE46350E14D6FULL, 
            0x89F23A7A9F1A154DULL, 0xC118FB328EFA7470ULL, 0x03C09CEE103FE1F4ULL, 0xBDC1837212632824ULL, 
            0x2329DE0D7FD95398ULL, 0x45F709ED10CF60A9ULL, 0xBAC908318C9DD9C3ULL, 0x2EF1E733CA6A9943ULL, 
            0xF6C292097E179C57ULL, 0xA3D939E02F8A418FULL, 0x7E1BE5B802E0727DULL, 0x0CFD6EDB88AB98F9ULL, 
            0xF69F91209A14B632ULL, 0xD5F0CEFBA7D78BEBULL, 0x1FDA313815D36FADULL, 0x479F4D62926F8907ULL, 
            0xD5453EBC4EBA33E7ULL, 0xDD78BA00A1802FE9ULL, 0xD7F05086DDA6B5A2ULL, 0x5B7F2BD632C08A88ULL, 
            0x5513097ADB55B2BFULL, 0x67296DFF63820D9BULL, 0xDDEE6C5AC9532E48ULL, 0x6AD4BFB98CFF1DB5ULL
        },
        {
            0xCB598E484434174DULL, 0x87EC5DA4661971AEULL, 0x74C476726944B1B9ULL, 0x7DF9DE99D890E949ULL, 
            0xE59D0B78CC4598B0ULL, 0xC0FF57D70ED180E7ULL, 0x53D2121B05924B10ULL, 0x4DD17E3F4285AA3AULL, 
            0x0F5FB5293E208676ULL, 0xD0C7CB4B002F616CULL, 0x5CC396B3E9F242D2ULL, 0x813C95B095F52860ULL, 
            0x90A7B2372FA770B2ULL, 0xA42618D2027C0776ULL, 0xD93580DB04FE5D43ULL, 0xEEF579A15B1AB0A0ULL, 
            0x03FC4EFFE332E8A3ULL, 0x16CF71CF39F4C342ULL, 0x055FA53D34498B9DULL, 0xE287BD0EC6236E09ULL, 
            0x8D8A5392E7C6FF70ULL, 0xA671E38C9E3C0896ULL, 0x8506800B58AEAF09ULL, 0x3515F11DB2CCD2A3ULL, 
            0x54A77B5ED01B6736ULL, 0x98D4C4941D18A921ULL, 0x5C4AD99A559F352CULL, 0x1666129CCF923323ULL, 
            0xB12A4E2DF7E4D19EULL, 0xBF9A2A6EE36C8EBCULL, 0xA32B0ED3719CD32EULL, 0x7FA6AAD7D5061592ULL
        },
        {
            0x4231458E2D6CF898ULL, 0x6CE82442E144B0E2ULL, 0x89976D3E98265F31ULL, 0x8278459CC335E296ULL, 
            0x67B2E4987F0B37BEULL, 0x03C524DEC277E302ULL, 0x5D621DDDB164E176ULL, 0xC7B4CDB4DA3369A3ULL, 
            0x1EAFDA0D07922AEBULL, 0x11F8288640DB6FB6ULL, 0x717C85E0CC7FB36EULL, 0x94A08867C3145E48ULL, 
            0x8C0D0053711A0EC8ULL, 0x91D963C26ED4DFFCULL, 0x772DF371408FE1E5ULL, 0xB505566A84C08732ULL, 
            0x3E6B1687AC25DF5FULL, 0xC9A372C6C85AE1BCULL, 0xBB63A1FA51385CC6ULL, 0xCFB35B275A9CF780ULL, 
            0x26A4DF183B36349DULL, 0xA38B9E9DA37458E1ULL, 0xB2A7E4B4D3F85A4EULL, 0xE98C5AE05D8A0005ULL, 
            0x1C2BD7A65FD97D7BULL, 0x4941B3368F4EAB47ULL, 0xB8196312D3CFD975ULL, 0xFB5D8136EFDE8E1EULL, 
            0x240D5D4000E91BFDULL, 0xDC59ABC96575C4AAULL, 0xBB5FFA008A6F8BBBULL, 0xC2A716067560CF26ULL
        },
        {
            0xE790E4A99AAFC8A3ULL, 0x595CF591E4EEC46CULL, 0xCA1ED6FA8CC3747FULL, 0x38D61A7AB651C9B1ULL, 
            0x65494DC0303B0CF0ULL, 0xF8451E3235A9E231ULL, 0x183166485B0D8DA9ULL, 0xCB1C98C50DC1F928ULL, 
            0x131668F400FD2DCBULL, 0x78B9266DF79A0AC5ULL, 0x38B8D3D55801267DULL, 0xAB90A36A87E2428AULL, 
            0x16BB9F9C62CD615AULL, 0x6F25B8BBFB6731D1ULL, 0xD9D859E670C9C6A1ULL, 0x050BAED7EADFD681ULL, 
            0xCBDA10992DE54380ULL, 0xFC258ADA7F5C292EULL, 0xA9D288B452BAF89CULL, 0x1A7A6932C9250365ULL, 
            0x1DD8C1CA6CA9F489ULL, 0xDDC17D0666463328ULL, 0x3973503607A91869ULL, 0xCAFC709C164F3493ULL, 
            0x2A1891F5B481BBEDULL, 0x903EE672CA13A121ULL, 0x3F85F53ADECB464AULL, 0x70E703A63F147BE4ULL, 
            0xF35A919BF63C366DULL, 0xC22610F878FCE0C5ULL, 0xDE70280683F50DF5ULL, 0xDFF9C0E45BC7DCD5ULL
        }
    },
    {
        {
            0xCE9BFF0676594E5FULL, 0x230BD147559D3D12ULL, 0x916AFAC501182835ULL, 0x7D884781E709F5A9ULL, 
            0x7D3F450499024AAFULL, 0x5E6DF0E40E1FBC71ULL, 0x29FD15B97CA3A3CBULL, 0x0C5A1727F7FBF1B1ULL, 
            0x0CEC7A2661CE0164ULL, 0x644030754CB502CFULL, 0x8F149C5FFB3C4FEAULL, 0xE593DB9CBBAD7C37ULL, 
            0x75DCD8F4FC35DBFFULL, 0xA5DCE48F3C85ECD4ULL, 0x3460E922B3140E26ULL, 0x265F22F70FA0A3CEULL, 
            0x5F95393898F983B3ULL, 0xB99AF7BCFC7C90D2ULL, 0x06C4A5A444FE1B62ULL, 0x2A7AAE92CF4AC9F2ULL, 
            0x4A70122B88AB7EF3ULL, 0x27B7ADE6C79693B1ULL, 0x8FADA302D111C564ULL, 0xF778A1230FECF4C4ULL, 
            0x502EDB563B563213ULL, 0x7870AE48FD233545ULL, 0xDA0441F2DD9DA642ULL, 0xB53D77131FBBF274ULL, 
            0x070E3C2181E5565EULL, 0x0987E6C614362A20ULL, 0xCBA37C8C1F53DF5EULL, 0xBA629989D959FF79ULL
        },
        {
            0x613DA98AA5D1F1FFULL, 0x0E4CF38479885561ULL, 0x40FAE21142B6442AULL, 0xF75824427966E20CULL, 
            0x64E1A99622BA1DFFULL, 0xDB06A0E3424D6676ULL, 0x7442356792AEAEC1ULL, 0x988A6EDB38C46A6EULL, 
            0xDE4C34249A8D026CULL, 0x255472DD60D2006EULL, 0x44048473308DB449ULL, 0x410B83AF601B042EULL, 
            0x7C9E3914AD44AE29ULL, 0xE92EB13C9E74ECB1ULL, 0xD17F2A212D4956E9ULL, 0x1A85DB1EB60A7F30ULL, 
            0x882EED225883212AULL, 0xEC2D068239271DE6ULL, 0x073BB01B4ED36969ULL, 0xCF9F0623F11145B3ULL, 
            0x0B4B8FCFFACD16F5ULL, 0x4E25C59790F11D81ULL, 0xBAE8131E7CA3F919ULL, 0x53571F62F8EFE662ULL, 
            0xEC6CC49406DAAE5CULL, 0xFFC979F3E77DAF7BULL, 0x9DC2C516A4F741E5ULL, 0x6DC0AA2BD8BB5FF7ULL, 
            0x287D50A23FB8EC5DULL, 0xF46E25A522C21647ULL, 0xDAB9F84099A534B8ULL, 0x7954A52CDA77AC38ULL
        },
        {
            0x8B1EC2C3A3B14F45ULL, 0xB8BC35AEA8F50255ULL, 0x3B31FB8929A28F5DULL, 0x5796E23A96794115ULL, 
            0x24131FB3B217403FULL, 0x359E8CE2334F711AULL, 0x4FEC492FBEE726D6ULL, 0x5BC24842ED9EA3F8ULL, 
            0xE202D064C7BE5C98ULL, 0x0D39A16197873FC8ULL, 0xAA7F6DC37FCEFC8FULL, 0x529DA1EF7A8344E8ULL, 
            0xA6D959E47F246379ULL, 0x4CEF36CEEEA1FE4AULL, 0x2E3E36E44AF2E7FEULL, 0x96BE785E0FCC8DB2ULL, 
            0xE2229AE19F43A882ULL, 0xA16F4D7A0D231159ULL, 0x62DE64A461F0C542ULL, 0x4AAD0A85AAC5888FULL, 
            0x95F7CF3A21CD5A3DULL, 0x3A9EC5F4ACBCAEFBULL, 0x1F34A4E210780F14ULL, 0x525F9566A0F65CAAULL, 
            0xC8431FC14D8A79D9ULL, 0x869A5C6A30725FDCULL, 0x4DEE65B1F4DDB1EBULL, 0xFC3B0F8B3BD9D81EULL, 
            0xCDA9642B193641F6ULL, 0xB59B82F76277C349ULL, 0x5CFFF06F95D83CB2ULL, 0x1615F3C0138FBFDAULL
        },
        {
            0x65B531E993A5379EULL, 0x428C572A42A169AAULL, 0xDD7F51DA886E6D49ULL, 0x0FF109680671ACCDULL, 
            0xF3159FDF277B2EFAULL, 0xBC634FBE7D9C630AULL, 0x4F76D34B10AD60A3ULL, 0xB3AFF5863F89594BULL, 
            0x029BE346970DAA70ULL, 0x7365510AB7BB1903ULL, 0x23862BE2AB5F2F6FULL, 0xF10BEAE6A8979549ULL, 
            0x4068C200CCE9EE22ULL, 0x73B9498116F385F4ULL, 0x6BD6A465099FE8BAULL, 0x3D801BB42924B751ULL, 
            0x1EE7D79BB0D39670ULL, 0x1309CA0B2615F7A7ULL, 0x000C6830FD2BBB07ULL, 0xDB4869444571FB20ULL, 
            0x6BB8FBAB17BC6D84ULL, 0x11573FA28379938BULL, 0xA1AA6FD68B9559C6ULL, 0x4096AC7FD498D24BULL, 
            0x8986211F4B4EA349ULL, 0x068BF6BBCA73D97CULL, 0x00562E7B55C99F0FULL, 0x25BCB7A5DE4BF11EULL, 
            0x774A81AD94AF59CFULL, 0x5280F2264E158C81ULL, 0x879250233067547EULL, 0x4C33674641C1731CULL
        },
        {
            0x5B0BB436AD109BF6ULL, 0x2536C78A3D7F24FDULL, 0xF4C931D419BBE86BULL, 0x5E50FC799D925BC3ULL, 
            0x19A722E6B4E69AF0ULL, 0xDAF7772D4BD27124ULL, 0xB7F4D1AFDF336736ULL, 0x91B3FB08FF0F58C1ULL, 
            0x433C9193DEFB79C9ULL, 0xFF0FF2B49109A1B7ULL, 0x25758EDABB8D9929ULL, 0x64E10C3DCD66791FULL, 
            0x77319DB08A44C4A4ULL, 0x71FEF3C9E4E5054EULL, 0x92F73BD6F778AA48ULL, 0xA13EEE88304695F3ULL, 
            0x7D832D1BBD954DFBULL, 0xDDBE37A4A6F29994ULL, 0x1A762C3B9D6C9BBBULL, 0xE7EB7A867234EDB8ULL, 
            0xF4E012188666C2ECULL, 0x41ED5BF771E14F17ULL, 0x7FF31509D1367C7DULL, 0xBD24BBDDFDA3E11DULL, 
            0x5F622D10CA5F4305ULL, 0x99EFFCA3B7750A82ULL, 0x0795FC2334688842ULL, 0xE3F8E360852FBDBDULL, 
            0x7AE0BD39E464D102ULL, 0x8F94CDBB0D086E40ULL, 0x3E2EDAC290261A69ULL, 0xD68BAD30675ED028ULL
        },
        {
            0xD41E119F63FFED54ULL, 0x35F09D4DEA9A7168ULL, 0xB16A32BB9E899ACCULL, 0x49AB365ADE039FC1ULL, 
            0x53CFF6F14603ADADULL, 0x5F14E56519D16358ULL, 0x756E414F3A22273BULL, 0x83B8963EE4718A10ULL, 
            0x738D279D857432F7ULL, 0x03BC252688F4B6C4ULL, 0xD70CE95F9F91EAB3ULL, 0xE694780A370EE1FCULL, 
            0x1583BE136DF78CA0ULL, 0x7388F0E7784FB72DULL, 0xE0A141136417309DULL, 0x95F3D04387F9B255ULL, 
            0x94772A9F3C1BB50BULL, 0x1DEBA05B9919AF37ULL, 0x67535935FF67D610ULL, 0x13A5A801916A8383ULL, 
            0x3C45C2AD37777DD3ULL, 0x62D176BA6E0AD2BFULL, 0xDA8D9BF2A98D4D83ULL, 0x5FCD5FBECDA01032ULL, 
            0xCE3AB0AA94B07B41ULL, 0x1982AD5B64135253ULL, 0xE7B392DCFBBC57DAULL, 0xC0C5E6DEC3B54CEFULL, 
            0x4BF1B318804E7D57ULL, 0x195BC660F30DACC0ULL, 0xC29D27350E25F3CDULL, 0x4BBCCD4D7B09896AULL
        }
    },
    {
        {
            0x43494EF7B1B66EC5ULL, 0x27477AE5CDCCCEF8ULL, 0x5F6F0E89C0E0DE58ULL, 0xB8E2A109E5BEDF12ULL, 
            0x568EE931E5FC52DAULL, 0x39217CF8006C7342ULL, 0x221A549F5386E3AFULL, 0xE6E8183AFB281633ULL, 
            0x4C9EDD3832BF04F5ULL, 0x062B30A566F1590FULL, 0x86F82ED6914625DEULL, 0x03CB16C953A69161ULL, 
            0x84AB29A3D9FFC952ULL, 0xCB48AA95B1C5BF40ULL, 0x8F8BAD7A21FA8DDBULL, 0x6A137F7E1EA4FCC0ULL, 
            0x2F7AB3F29C11F254ULL, 0xF4BCE55CB81B4ABCULL, 0xC1CD315038AD1C91ULL, 0x31DC1E65E63698D8ULL, 
            0x29FB0E85F0FD7755ULL, 0x3BE906EAB1D1BA9DULL, 0x4144B9DC8A23B086ULL, 0x8E8045ED52CCAB6AULL, 
            0x85AE580FDACC95BCULL, 0x20695BDCBD2F2244ULL, 0xCA3A0713787B25B2ULL, 0x098DF33F8F0FE375ULL, 
            0x8723D870FCF64D54ULL, 0x5E09FC6B3CB55EEDULL, 0x96EBD0455358F258ULL, 0x83225B18F0E72D0BULL
        },
        {
            0x4A37CEA033C7E07BULL, 0xBE2B34635C785CFCULL, 0xF4B5111CE4FC9553ULL, 0x17103B8C82865E46ULL, 
            0x1F76771179BDDB3CULL, 0xECF23A0467FDB983ULL, 0x008D902BDF218849ULL, 0xA1B08DAEBBEEE2D1ULL, 
            0xF1CFBE3582DC0072ULL, 0x446CF6D32C17F0BFULL, 0x64FAAEBE0F6B154DULL, 0x33DED8591ED307F2ULL, 
            0xD5407CC0FB66735FULL, 0x2AB7C85742FF3D3BULL, 0x2582A3B976C9A18AULL, 0x9CB2E8D0D7841AC6ULL, 
            0xD3CEFF10A3FB4F14ULL, 0xD88D002336067659ULL, 0x47F1F5F0CDF994FBULL, 0xE048F46E52074C79ULL, 
            0x439372A83D21EA07ULL, 0xAE94C19665B21D85ULL, 0xBA5A0E926E1D6255ULL, 0x43D7AF26BDCCDC0EULL, 
            0xE66F3B5B39FC4952ULL, 0x1EFD5DA2F401573FULL, 0xE196C7950EECF2A1ULL, 0x9FAFDA2AE393ABE2ULL, 
            0xB536B1431ABED7FEULL, 0x850127DF566A59F4ULL, 0x27DE09D9B9C5A689ULL, 0x9D9F9234F6ECFD11ULL
        },
        {
            0x7BA0100CED3433EBULL, 0xCF4A35B7B3F121F6ULL, 0x183C0217AE2CD9C3ULL, 0x71F99D8CCEB0ACB5ULL, 
            0xBDD2D3ACAC1AB9A4ULL, 0x98EBDF29894FB141ULL, 0xE7B75591F5F8A53EULL, 0x9A027DAABD026F4DULL, 
            0xED006E8719902EC4ULL, 0x0E5CD650A1751B53ULL, 0x626D62946BF789E4ULL, 0xE547513C5AE3B080ULL, 
            0x30FACBE96062F349ULL, 0x696B4C95C70F4547ULL, 0x1F9E5B6389DB2EC8ULL, 0x85A0B4B498AB025DULL, 
            0x9101C6098D3D839EULL, 0x96984478C2DF206BULL, 0x87270FF20FD0C879ULL, 0x89ED1AA8B576C55DULL, 
            0xC9A15ABBB1046695ULL, 0x8E0D3A29EE0D954CULL, 0x066AD0782CECA55CULL, 0x4490EAD11F4103E2ULL, 
            0x9175E6F96AF83618ULL, 0x935FD92B44E5D260ULL, 0x3E97E0C5F4C25CC5ULL, 0x7E55F6DCD1C0790BULL, 
            0x23C6E5F589885F07ULL, 0xA5779A24B3170897ULL, 0xBBB4FA09B4B430D6ULL, 0x74E13C414B546719ULL
        },
        {
            0x33DE162F20FF8D25ULL, 0x26146CF0FB3A2156ULL, 0xA78A7F03500E29C5ULL, 0xA7E6AE2220052EA8ULL, 
            0x41A80EC092B5BD5EULL, 0x86B7F88DA9DE049DULL, 0x649DEB83E20F682DULL, 0x530CC1DF9D9F150EULL, 
            0x9523F972C4CBDF0DULL, 0x37EDD2FECCACFA46ULL, 0x04D3614B82FB8FA8ULL, 0x6AF5723F5F96A746ULL, 
            0x7793141447BBBED4ULL, 0x917DCEFF50E97C5CULL, 0x1148F736CF6B5C4BULL, 0x0B3DC0F79C10C2ECULL, 
            0x55A6479789FEB3ADULL, 0x850216AFF6F5A9AAULL, 0x997B4F89066129CCULL, 0x78A62A425E9560F2ULL, 
            0xF70EE546E96CF633ULL, 0x46EA0E77B72A57E2ULL, 0x97588B403046B961ULL, 0x6C3D2D8DB678DACDULL, 
            0x510A9BF92F95C2B3ULL, 0x800329E9E3377798ULL, 0x86D787659DDE7DEAULL, 0x23C1039AC7B95480ULL, 
            0xC6B57DA67105F278ULL, 0x5B9C60C8B1E83FABULL, 0xE09E23DC3813F856ULL, 0xB4981306631D3D54ULL
        },
        {
            0xCCC13C2A774C177CULL, 0xCDB95CBC35623DCEULL, 0xCAB2DE09D55EC910ULL, 0x548E437418B174BCULL, 
            0x5D0B66341332A828ULL, 0x932165DCA0366B2BULL, 0xDD6E62F48E75226DULL, 0x40D4AC028D11F467ULL, 
            0xA7161C9E67E3061EULL, 0xD7082308D3FFA555ULL, 0x2CC9989361C9F580ULL, 0xDE555BD5D938D17EULL, 
            0x7B5E4E29C300F20AULL, 0x1F4DCF63B9580CEEULL, 0x364AC4A48993A152ULL, 0x1A55B6779D00D679ULL, 
            0xCEFE1760E797C292ULL, 0x2FDC018D7352BDD5ULL, 0x8A09D0BD8DFC3C15ULL, 0x568745AB78CD0CB5ULL, 
            0x52AC57D13518DF9AULL, 0x846DE8FEF5514FF6ULL, 0xC6BB9E618D374B3DULL, 0x83682BE10A621E56ULL, 
            0x77BAEC3825FAF844ULL, 0x72A0012ABFB41DADULL, 0x1723B623357AB57DULL, 0xA3A427DE40B272CCULL, 
            0xCA81A987B09AEB89ULL, 0x3F009A7874AF0F84ULL, 0x6A43C4556B964334ULL, 0xA721BC092D3CF52CULL
        },
        {
            0x020EE735EDF96C00ULL, 0xF2AA357BCD7330B4ULL, 0xFE6A58139C09898FULL, 0x2BB5B2E563AE3082ULL, 
            0x07416535FF912002ULL, 0x12FD049056F802C2ULL, 0xECFE76F3DF6F9DB3ULL, 0x27723191AE45FD29ULL, 
            0xC604B52D1DEC8CE9ULL, 0x61AE61A6D285C10FULL, 0x3A17F04067F1114CULL, 0xFDD373F3951C2E71ULL, 
            0xDAF6ADA5D06907E9ULL, 0x9988F7CB7E8052EDULL, 0x4AB983FDACAF5F60ULL, 0x35DE02343BDAA951ULL, 
            0x2CD5E31F374DC5A9ULL, 0x7F5BC570CF113C4FULL, 0x2F1AFC45AF4C4958ULL, 0xE72E0F31365CC321ULL, 
            0x3D8B5452E883AAF9ULL, 0xA9BCB90DE7B75D10ULL, 0x65542DF698050C2FULL, 0x9D973DA7CE3892CEULL, 
            0x61324B85987C30D3ULL, 0x2FCF890AFBDCCA33ULL, 0x212E1C94C9E5D061ULL, 0xB7DA556CA84E9CE3ULL, 
            0xF83DBA45C9755D11ULL, 0xE60FF98DFFEADE53ULL, 0xAB1F398E5AB45BDAULL, 0xDCDCDAFFF27D71FDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseBConstants = {
    0x71023A7512EC17E3ULL,
    0xA219EAB20F98B142ULL,
    0x8AE6D82850DCFF64ULL,
    0x71023A7512EC17E3ULL,
    0xA219EAB20F98B142ULL,
    0x8AE6D82850DCFF64ULL,
    0xEF078FAE4454D789ULL,
    0xA11A8E45B1AB28C2ULL,
    0xD4,
    0x08,
    0x9C,
    0xC9,
    0xF0,
    0x03,
    0x96,
    0x82
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseCSalts = {
    {
        {
            0x1400D8A64B877E5FULL, 0x8F1872997F17D2AFULL, 0x25A3DEFF908094CBULL, 0x7A484EB62779D20AULL, 
            0x9E56BB5F1B4A01C4ULL, 0x42074D64C762750FULL, 0x004C1ECE50A40733ULL, 0x6FC84F7415C40905ULL, 
            0x074245F15759E03BULL, 0xD1164E7AA2F8E068ULL, 0x415875E68453DC19ULL, 0x4EF62C2E88FD0208ULL, 
            0xF1D40910F0D78D80ULL, 0xA35B02C1FFACB257ULL, 0x48DA25668CD42A3AULL, 0x01F821A295FAEE03ULL, 
            0x3EF6D8B089E68FD9ULL, 0x6CE9C42B5CDDD087ULL, 0x7B5C8B1FF2B0C7D1ULL, 0x344345A187693AF6ULL, 
            0x9A195BD94CD7AAABULL, 0x0BDDDC2B2C3D039EULL, 0x46532FA052895A98ULL, 0xA743A91405A05179ULL, 
            0xE0C912712B84C95AULL, 0x2D98EE55660A1BF4ULL, 0x82464E53C9B33488ULL, 0xBAB9C2EDF8171A57ULL, 
            0xC670AF39D8148E88ULL, 0xABB9FB04CC6D54CEULL, 0xE48FF83B6F11FF55ULL, 0xF08E94F341CFE239ULL
        },
        {
            0x3779A75E0FE90294ULL, 0x8E8F158BD0211DFEULL, 0x7B59B38F7CB9F797ULL, 0xE3FE6F17B854CA5DULL, 
            0x3ACE065C0C7E0007ULL, 0xFD427AB375C0DCE0ULL, 0xD64AF30F509C9C04ULL, 0xE009440B66B5BEFDULL, 
            0xD8F7279AC935D8E2ULL, 0xC5A80F3FEAAE5150ULL, 0xBAEBB534E47D9794ULL, 0x73E4683F0401BDB2ULL, 
            0x5E6A1B15B13CF48DULL, 0xEAC13F9BD27F34B5ULL, 0xEBA1D0486CF19EABULL, 0x04CE12D582546AE8ULL, 
            0x2A5A223EF689082CULL, 0x331BE544FDFFE4B4ULL, 0x87FFFC8B0B61E41EULL, 0xE8CE3FF7D8867869ULL, 
            0xE2B75041A3B08430ULL, 0x5E5BD1FDB20A7F72ULL, 0x7733FA6534B01323ULL, 0xAAA3F1E8358BCC05ULL, 
            0xCE4ED845FAD9FF5BULL, 0x7A30E3396CDB7B8EULL, 0x76BFF057A0AE2B70ULL, 0x6D956F9736CB6857ULL, 
            0x74154B50ADAC8E72ULL, 0x70DC8374F461B5A0ULL, 0xC1C6548B9D3F5361ULL, 0x6AAA6D34EFA2BF4FULL
        },
        {
            0xD83B8FAFBF5F8833ULL, 0x90C6B3EEA448DD7BULL, 0x23E200FDBA468795ULL, 0x5A9DECB294B0ACD0ULL, 
            0xDD9FCD84052F4841ULL, 0xCFCFC0737C49DD71ULL, 0x4BE2FC5631B74896ULL, 0x7F301E09C616C5A3ULL, 
            0x36DF36D93F2A8608ULL, 0x065D3C28296C297FULL, 0x7700410C5E779FC6ULL, 0x354FDC6525145839ULL, 
            0xC64FE916B26FB1E9ULL, 0x6360B6E69CCAD3DAULL, 0x64AF934854AE5A96ULL, 0x6130E84175F0ECB9ULL, 
            0xBE9EA5CF7DB45B44ULL, 0x8E063553BEBFDA59ULL, 0x76BF8FC956338B72ULL, 0x42A8AE5B8297C6F9ULL, 
            0x97B503398BF75390ULL, 0x90BE7CE048A60AA3ULL, 0x28852CEE6664B1D2ULL, 0xC906D1A93C3FC40BULL, 
            0xFF3FF5C7D212B3C3ULL, 0x7C07E8CAFB6DBFFDULL, 0x0D013C895F5261D4ULL, 0x81554B34E588F20DULL, 
            0xCE9E7B919F00E051ULL, 0x6AD6687A12C134FAULL, 0x276796915F15576CULL, 0xCAFE5553FCB3F77BULL
        },
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
            0x2100EA387905F197ULL, 0x4D96710BFABF22C6ULL, 0x0D991D1CCA320A74ULL, 0x81A5D10346FEF627ULL, 
            0x4FDDFB584022ABD7ULL, 0xD0DBEE4F595C33B9ULL, 0x889B0EA4403B36BAULL, 0x79FDA4AF42DF1525ULL, 
            0xB0E62666DD5A1FA4ULL, 0x64431C2FD5C2AC7EULL, 0x19F006623E4B2249ULL, 0x05B927A35F9F3267ULL, 
            0xEB3DFB3806071B4DULL, 0x5EA39D31C359AD25ULL, 0x7DF76D7552C335F7ULL, 0xA3A9D5C24C38AA39ULL, 
            0xA1798BB57EA450AEULL, 0x08322A85CE1007F9ULL, 0xB16583B16F229DE3ULL, 0xF5D6CEA0340684E5ULL, 
            0x7B859D941A5D3A99ULL, 0xD426C4BC74621F75ULL, 0x35CA20D37DCF9B34ULL, 0xB0CE44DA24B3637FULL, 
            0x79BEF011E7684582ULL, 0xB49D98B79CCBB3B0ULL, 0xA2D687D4C461498BULL, 0x3397C512BE006812ULL, 
            0x000E39F43603DE86ULL, 0xEE471B3BB3A4C1F7ULL, 0x6001AD9B145B7214ULL, 0x7B540B6829DDD4DAULL
        },
        {
            0x149DCD099FD33B08ULL, 0x528D542981B7462BULL, 0xB6F00FA518E2F180ULL, 0x2009B1D75D73526AULL, 
            0xE8309AD668A704CFULL, 0x9D8F004CB9324023ULL, 0x7F5423279EEFEE70ULL, 0x3C4C5D2226D51977ULL, 
            0x270255512615C0E8ULL, 0xA9AE8C0A29A0DC87ULL, 0x1807BCD46D87BE00ULL, 0xE15C8CEF32FB862DULL, 
            0xB804C8A75711C05BULL, 0xAF88E0FF02B48909ULL, 0x63D2E39EC261B4EEULL, 0x76C703514B4F8636ULL, 
            0xF8E8ECB8FFF62504ULL, 0xEF98289D00AED061ULL, 0x9254FB9CD71F1212ULL, 0x836AC4A2C053D6FDULL, 
            0xAF95BF177329AFC0ULL, 0x03B8D83638CAA1B0ULL, 0xDB6E781D869B7AE8ULL, 0xD28B09C7FC2CCB9FULL, 
            0xB8B7C7E64EAAC0BCULL, 0xC245C86228E5566CULL, 0x7FF1EBB665AD7FFBULL, 0xD8E51CFCA2AF5518ULL, 
            0xB15CDD082FB2CAD9ULL, 0x34462950B16CFF40ULL, 0x0D6567D4D29D32E1ULL, 0x6990A75E9D2E73FCULL
        }
    },
    {
        {
            0x9EAA1B1AC9490247ULL, 0xC90B9D9C1C4B471CULL, 0x7ED5A12CC6497A0DULL, 0xE1A1983CB39DD774ULL, 
            0xDA2A7F2982A2B7D0ULL, 0x4ABB1CDC2E17926CULL, 0x6941729F57A42465ULL, 0x6C408233F4D11064ULL, 
            0xB22066CAF12F3376ULL, 0x50C8B6D12FB273A4ULL, 0xE0FA6BCC58E7415AULL, 0x34382A29532543CDULL, 
            0x18826AB13025C79BULL, 0x857B41294CED3238ULL, 0xE5C123D249B1789DULL, 0x5AC2AC61C90B7347ULL, 
            0xEBD29F2628581905ULL, 0xFF905B69471579C1ULL, 0x8567731FA1CEB64DULL, 0xC48AC6448A12A72EULL, 
            0xF89FAEBADF2ED5F5ULL, 0x5C5D174EC535BE20ULL, 0x4629ED8F441EA3BFULL, 0x402010AE1A89B31EULL, 
            0x1EAE579C3C809192ULL, 0x73E81DD6E148A7E9ULL, 0xD44A2AB141CB8A97ULL, 0x2938A8B8E8889275ULL, 
            0xF03E7D8EE3F998F2ULL, 0x3154B19D0E2A0AA9ULL, 0x12549193A12D2B30ULL, 0xB321F245430F4505ULL
        },
        {
            0x7BF9B62FA0A78B6DULL, 0xEC4C54C2B271DA56ULL, 0xFF447106D4596823ULL, 0xE433DC386525E0E5ULL, 
            0x1F0EC0FDEB15DB55ULL, 0xA49942D40E62949CULL, 0x8B94568CB1AD13E8ULL, 0x0648ED1CA844FA71ULL, 
            0x68771BC8772C5E11ULL, 0x741B5A3B12530EC2ULL, 0x5F2A99F46486CD38ULL, 0xFACDBF1D1486DDDEULL, 
            0x98DEEECE21BB613FULL, 0xAABFEB74A14AE7B1ULL, 0x953D5E40901DAEF7ULL, 0xC8AD51D4ADEE15D6ULL, 
            0x6B73C67A9053E658ULL, 0xB2A73A5B76FC98A8ULL, 0xEFA9ED9D191DCBDFULL, 0x091B45DCE84BA78EULL, 
            0x495C264757CDDE50ULL, 0x7894707221F1DD57ULL, 0x460179B3DB79F2BCULL, 0xA8CC7AFCF5F8EFE7ULL, 
            0xFBFF338B74BDF7EAULL, 0x65789E15B626DB14ULL, 0x8B82E3BE9EC55D6EULL, 0x19EBF18F9C9BD366ULL, 
            0x4095FD1B7057EAECULL, 0xC08DD79F1E0077F1ULL, 0x60209700F9550422ULL, 0xE48172A20683AC9BULL
        },
        {
            0xFA055B4A2D6DB753ULL, 0x92BADBB729E86EC6ULL, 0xF2EC04A76FF8EEF5ULL, 0xA733E5B6326A1D4DULL, 
            0x4797B09FCEC46FC4ULL, 0xECF279F9061F9915ULL, 0xC17352A442B0041DULL, 0x6AF4805D79D10937ULL, 
            0xA401989536A61363ULL, 0xD25430DBEE3DCBB9ULL, 0xEB5933253F674956ULL, 0xE4A70EE914A078CBULL, 
            0xCBD698380C51F600ULL, 0x9156ED2AC075CA03ULL, 0x5C3429F85DC1A867ULL, 0xA2F3A13FBECA149DULL, 
            0x72206BAE600673A9ULL, 0xE90BE5AA7F48F366ULL, 0x18D4F82BBEC5819DULL, 0xCA2129AE46AB6A40ULL, 
            0x9EEF8BF5C01F0ECCULL, 0xB50765D550C6060AULL, 0x26142A1E24A2D3A3ULL, 0x89B9569400B09974ULL, 
            0x4A0D808CCB7A8803ULL, 0x7FA342F4361582CCULL, 0xBA5266DAE95337CFULL, 0xF987FC8EFE55EE5EULL, 
            0xE39C72AB7BDF3194ULL, 0xFF6149C0A54E560DULL, 0xA485866300867700ULL, 0xE2D86FAC9C0D1CF2ULL
        },
        {
            0xD56BBD9208DA4304ULL, 0x6E6F857750992441ULL, 0x269CFAD6D5BFF7C6ULL, 0x7A1DA57B6EDF6CF5ULL, 
            0x3EAF38ED3221031BULL, 0x9E9A53CAB63CF836ULL, 0x88F3DD2AB450F659ULL, 0x294873E177DC3A03ULL, 
            0xACE14C94089F90B9ULL, 0xC5C36BE4CE77E2E5ULL, 0x3202954AAAE200C3ULL, 0x30B6351291137EAFULL, 
            0xCCDDFFCCA008AAF7ULL, 0x8069EB34F11AE71BULL, 0x96A9025ECCDC6D7CULL, 0x9048711932D560E2ULL, 
            0xFE88B66EB33A35DBULL, 0x7648F0FC82B15D7FULL, 0x3FAAE0A9E076D850ULL, 0xF35161E244D7F961ULL, 
            0x032FE35DFD24CB32ULL, 0x3980D1C2EF402845ULL, 0xC053AAE47AB084F0ULL, 0xF8E9C388FE240F66ULL, 
            0x509B8A0CCDA904D6ULL, 0x3937336F3313E81DULL, 0xCD1A4D9EC458D3D5ULL, 0x6842064D36288291ULL, 
            0xBCC2562260787189ULL, 0xDAA60061A1F2795AULL, 0x8DFFA042C7EB4664ULL, 0x8C31C0D7DC29CCA7ULL
        },
        {
            0x157355B7ED484687ULL, 0x333B176742243F35ULL, 0x0D211CC241034E8FULL, 0xAED48363A79C42BEULL, 
            0x169C4A2B3942F45BULL, 0x4FEE4766A58371C0ULL, 0xFD069E955D4DED0EULL, 0xC55578A1419A02E9ULL, 
            0x36EBBAB0EE0A414AULL, 0x4E48C5AD2B05FD28ULL, 0x6B57646090B141CFULL, 0x1382A9AE5CDC4329ULL, 
            0xCB5EADAC2EC26BBCULL, 0x04144596CB468BC0ULL, 0xC4C9AA66F0FEE08EULL, 0xA34058843E918D2AULL, 
            0x0AC7D02A2E297F56ULL, 0x6C2D656EE2141289ULL, 0xA8C76B227FBCCB3FULL, 0x91EEC9C708E87F52ULL, 
            0xCAE434CA0EFC5C6FULL, 0xCB8A8B424C913899ULL, 0xCC5F4E422FFABCDDULL, 0x99F542B6C405489AULL, 
            0x2A1123932FD632EAULL, 0x9165416903525293ULL, 0xCAB9D8244A9DFECEULL, 0x0DEA660F65B280FCULL, 
            0x5E86268CA30F2842ULL, 0x4E3B95ED7846A6C2ULL, 0x74E63DC03F1BEC43ULL, 0x9239AC4BD90DF75BULL
        },
        {
            0x273BFF6EBECBC3D5ULL, 0xA5A25F133561AFC7ULL, 0x022C7A50C055B6A9ULL, 0x89D851D70C62EDC9ULL, 
            0x46BEB4B51A333CE3ULL, 0x14DFC22A93D6A5A2ULL, 0xDA7A2F9929B1D7B6ULL, 0xD28131384A557D61ULL, 
            0x0FFB58EC2F93A729ULL, 0xE4606DAFBB63634BULL, 0x943751361B45EDEEULL, 0x2F567E366C0AF3E4ULL, 
            0xE66A993AE2371766ULL, 0x56F5E61C738081F3ULL, 0x51FE62E3B5F77F64ULL, 0xB0922B6D163F4D86ULL, 
            0xC9EEF68EFEC5B161ULL, 0xB5603C78F3D93BA8ULL, 0x8FAB1BB9D44D2B4BULL, 0x0380FCC1B99EE695ULL, 
            0x5046711B1FC85760ULL, 0x921C3908968D9E93ULL, 0xD6597CC11296E298ULL, 0x2B2252280FD11744ULL, 
            0x03373F7D4C5FC81BULL, 0x1EB2D9DAA7CFC8ADULL, 0xC7C480F26EA5B843ULL, 0x6CC8CE3D756C6E5AULL, 
            0x9B79AE0C6C8C715DULL, 0xFAFA895821CF135FULL, 0xC9CE05ED56CE0EA9ULL, 0xF5A8902E418F001AULL
        }
    },
    {
        {
            0x3ABB474A31A43827ULL, 0x66977E16E35C37BEULL, 0xC786CF233F36F004ULL, 0xD573FE8B55A2EDBFULL, 
            0x565FAF86A61A0200ULL, 0xA67153A5B61376FAULL, 0x45D897CA310540EDULL, 0x5EEF7CBA877D4376ULL, 
            0xB615C1858D604A11ULL, 0xD7B1CF799209EF5BULL, 0x835517DACA656B1DULL, 0x78BE1318E9EAD51AULL, 
            0x2F725A538025F886ULL, 0xAAC3F8F37C26EA80ULL, 0xBF7F8547C3BBE645ULL, 0xA447B56F8E807E60ULL, 
            0xCFAF82BE6B856FBAULL, 0x5A88D52C44126975ULL, 0x9897382DD66DB539ULL, 0x16424265389611B4ULL, 
            0x9010D8C7AACD83DAULL, 0x54BBD4C667D5282FULL, 0x15A184F0729A8D11ULL, 0xB3832ACC9EBF7E18ULL, 
            0xFB191CC5AB133D03ULL, 0x6600C9D9E4BDBDFAULL, 0xC2B8B275249ECEAAULL, 0xFB6B465021279F19ULL, 
            0xF61E286D7BABA399ULL, 0x9BEFDD4C9D2AEDCEULL, 0xB03A8DBE5933B9CEULL, 0x019295A52A3DC2A0ULL
        },
        {
            0x3BD7D22B77AC1D35ULL, 0x11518646492CD7EBULL, 0xD12CCC28322DB1ACULL, 0x073E99DCA5EF1D3DULL, 
            0x3F3ED221707D5EDEULL, 0x0E30DF92E1565170ULL, 0x420C5D15FE5BCB83ULL, 0x4937CE65D75DA1A8ULL, 
            0x1074F12FB8A3BB12ULL, 0x34BA101947BEB4BAULL, 0x2013779C688F89E5ULL, 0xFA9576883A902E08ULL, 
            0x56C2B165790EFE11ULL, 0x4B069218ECEB33E4ULL, 0x95B5E8BC71893202ULL, 0xC1BAA754FDAF53C4ULL, 
            0x2F0382DA5A7F2F15ULL, 0xAF3720509FEF30F1ULL, 0x4134989BEE699929ULL, 0x10FD6C5F0C576562ULL, 
            0x46987237C23A4919ULL, 0xD1189CFC2E6D1881ULL, 0x78E8C3F89F9F8AABULL, 0x2B1E96CBB15BCE78ULL, 
            0x4EC9EF31FEE7D62FULL, 0x196C0F2D9FABDD70ULL, 0xAC2B6CF8D5F8B2CBULL, 0x7CDE7B5AF241A30CULL, 
            0xC09D1C7E0B8FA1BDULL, 0x334BB87FC882BB8CULL, 0x39BB27E854DF9B7BULL, 0x687538ACF0C38CF6ULL
        },
        {
            0xBB7E9321381C0CBCULL, 0x3641824AB66B82D8ULL, 0x887923123F32806CULL, 0xF3B3DE9932F4E1B6ULL, 
            0xE32A30EE7A8459C2ULL, 0x64EE4EBA4848432AULL, 0x7133FC2F235E576DULL, 0xF7E56EFDFCF65292ULL, 
            0xE0B8B6A8E1CB7067ULL, 0xDF5870774DAB44B3ULL, 0xE71B348F4C773546ULL, 0xD4E67EFEE6530E1FULL, 
            0x52FB6D940FCACC07ULL, 0x5C087FDBCDB94DA3ULL, 0xA253D553F53EB8AAULL, 0x89BA7A73DEFE3347ULL, 
            0xC2793366671170B9ULL, 0xBB10040A33B500A0ULL, 0xE2468339FBF20D84ULL, 0x2D958C96B423E956ULL, 
            0x4935F7D61545563FULL, 0x6F71C4E94A634970ULL, 0x9DF06CA9802C57D3ULL, 0xBB3C5AB928522C92ULL, 
            0x7C505D0734003A9AULL, 0x94DF5A6F524D0D6BULL, 0xD4FA614B1E1CDBC8ULL, 0x661399D5022CB94BULL, 
            0x5771055A22E33AC8ULL, 0xEFF462F9E231B70EULL, 0xABA193A44E4D24C9ULL, 0x9C42B55D1CA37A2EULL
        },
        {
            0xCAC08B938B387E95ULL, 0xD566206901737371ULL, 0x527767260C8EAE2DULL, 0x2D8049E98009CEE9ULL, 
            0x279CE76130FD56AAULL, 0xB6DD29CFB140106AULL, 0xA67D4CCC2F2CF615ULL, 0x0389B0B3CDD0AE3DULL, 
            0x30213370B81A05B0ULL, 0x7869D3D4A7B7381DULL, 0xF1FCB692B2BC28F1ULL, 0x974FC154F57B49FDULL, 
            0x4180DB6E0D416C40ULL, 0xC60ADD1991A7CC31ULL, 0x29E0931A5D29EF08ULL, 0xAD4C77E11DE8D793ULL, 
            0x46816D5728ECBA8FULL, 0x70E7E5B03E54A6C4ULL, 0xF74F4D0652B2F28DULL, 0x85CCA3ABB56C8101ULL, 
            0xA7E89A31F4ED699FULL, 0x8A190B4FF12035A4ULL, 0xA7BF74EE1611D5A6ULL, 0xCD47675E3A1EFA6EULL, 
            0x3F3B955312E7EB2BULL, 0x7B9AFFA5A91D7D2AULL, 0xF4ADA630275278B8ULL, 0x86C36E3B968AE411ULL, 
            0xCE681E6E013DC772ULL, 0xFCBDF418673F7232ULL, 0xDFE973B8DF23342DULL, 0xB3A0B01482EDB078ULL
        },
        {
            0x35BD124AF53C18B0ULL, 0x208C43A50A274F00ULL, 0xAB9DB3AA6D58801FULL, 0xFEF7C04A8A02B41CULL, 
            0x54DA318BBB7E66F3ULL, 0x9EDFADD90684DF7CULL, 0x8A5FFD2DB72D7C52ULL, 0x80F461B04E3ACC67ULL, 
            0xBAB134C99E969374ULL, 0x27444A3DECB296B3ULL, 0x80295D0AAF4E0BD6ULL, 0xA84242BD09ADC6C7ULL, 
            0xFD519670180D7F29ULL, 0xA8963E39DF3F4EE3ULL, 0xD3A95CAC4C412DBEULL, 0x3D433B88156FA301ULL, 
            0x710367F3D207686FULL, 0x7D58E712130AAC1EULL, 0xDC2CA1DCD494B987ULL, 0x5D08441417FE1908ULL, 
            0xD3F063F22DA821CAULL, 0x172CD0B2BEED27EBULL, 0xAEC8DCA563D62B43ULL, 0xE125275D28BD6484ULL, 
            0xD12E70C8F7196929ULL, 0x10E50CA87045D38BULL, 0xC71E9CAC94AA2B17ULL, 0xFFFCCAAB40089AD7ULL, 
            0xD471606F95BDFAADULL, 0xD326472825CE4DCBULL, 0x2AC0754218FA596FULL, 0x7379D70C226B56FEULL
        },
        {
            0x2682E0AA08390428ULL, 0xDCF4CD5E0CE4F43BULL, 0x5902C801231DDE82ULL, 0x1C8EB02C9576AC19ULL, 
            0x65D5F875FD363EB3ULL, 0x63CC24A18F166564ULL, 0x5CAE9507AF44196FULL, 0x7A62FC10D6800AE0ULL, 
            0xEA8908B4594E747EULL, 0x35CEC9DB18E4F04EULL, 0x2515BE50B5BA304CULL, 0x2ACA6A2B1C25B3A8ULL, 
            0x126F1281AFC6A92CULL, 0xDD8E01091B6DC86AULL, 0x1F17A33B792A12EFULL, 0x60A8180EF60735DEULL, 
            0xE098B5D37ECA8850ULL, 0x972EA84F413C538DULL, 0x8EDEB5C113B95B5EULL, 0x929E9D5CDEE4682BULL, 
            0xFE4D36388BD61DA2ULL, 0x33FD44FE043ADBA5ULL, 0x043F4FCFBE50B01DULL, 0x26328DC930ED5DF3ULL, 
            0xF6565D58983CE57BULL, 0x39B036E5D5E18780ULL, 0x3435624E38D4C31DULL, 0xECB6A9A4A25202F9ULL, 
            0x85F8E126342330F1ULL, 0xB4464EA2688864F8ULL, 0x00C2418E589D062AULL, 0xDE495CE980E3E671ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseCConstants = {
    0x1A284F86BFB2EDF6ULL,
    0x518EFE537D5A07E4ULL,
    0x7CFE79D0683CB30AULL,
    0x1A284F86BFB2EDF6ULL,
    0x518EFE537D5A07E4ULL,
    0x7CFE79D0683CB30AULL,
    0xBB09AC2D4FC1BCDBULL,
    0x4A1C4C9117D4B969ULL,
    0xA9,
    0xF7,
    0xF9,
    0xBB,
    0x02,
    0xD9,
    0x20,
    0x02
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseDSalts = {
    {
        {
            0x07D87660B3D24B44ULL, 0x05C7E7C5B04118DAULL, 0xF8E253FD0458BB40ULL, 0x693E0354FEF577CCULL, 
            0xF90638EE42AEAC43ULL, 0x0F24268BEFAFBCC3ULL, 0xC932D84F5F52F5ADULL, 0x73F745B4B7A5A959ULL, 
            0xA8CD21F6B2E980C3ULL, 0x492E4AAAAFD073CEULL, 0xB86AFD972EE6F81AULL, 0xC62B25AE13D593BFULL, 
            0x081269FED3F52F77ULL, 0x39952F9E9DD8BC64ULL, 0x656CB87C853AA1A3ULL, 0x813B1D8F1D449B42ULL, 
            0x92CFB9A434A8FECFULL, 0x4DC7F54412A5E349ULL, 0x88A81DC8EA3D9C76ULL, 0x8729FB0EF3EAFEC3ULL, 
            0x8B6C10DE98074995ULL, 0x4FF189B5677C4461ULL, 0x3423BF974317166FULL, 0x6A4724FD58462607ULL, 
            0xF4ADF2B42B8DED46ULL, 0x50B713C15A7C1F6FULL, 0xBBE6CEB527CECBA6ULL, 0x2600FA9AD36442A1ULL, 
            0x1DFCB947CA964D60ULL, 0xE658F912CD78A03CULL, 0x010FECB8C14B0E18ULL, 0x76E75724DB725A1FULL
        },
        {
            0x98044C2918D54BEFULL, 0x28E90B6F551EFC15ULL, 0x1B6643557D9C6DA4ULL, 0x9AB06539113369DEULL, 
            0xC0BD59B87889F858ULL, 0x61D72E97C2304D2DULL, 0x3BD69219F8C12403ULL, 0x7601EBE7523D4A36ULL, 
            0x344CFB16EDC8217AULL, 0xFECAE07920289E9CULL, 0x031C90450A0B4EADULL, 0xA5B522AB44FCCEBAULL, 
            0x19CEFCC094E383F8ULL, 0xAA961D00E36DFBBDULL, 0x21B3AE3BBC4D703AULL, 0x4F427B3FDD3050DBULL, 
            0x60A47783DFA0A912ULL, 0xBE1AA3A77B01FD3AULL, 0xBF126B75E9D48A15ULL, 0x26391F74DBD64697ULL, 
            0x2BEDC16C6E7B3099ULL, 0x1C4EBE46265ED0D9ULL, 0x439E5D349450FC93ULL, 0x5E74ECD4D83FBDB9ULL, 
            0x17E2F2FC897B1E0BULL, 0x4920868C2C74BDCEULL, 0xA2D1C99661F135EAULL, 0xC71EC1B09F1C301AULL, 
            0x274EE6A3FB7FCF6EULL, 0x4949D90A2A48A209ULL, 0xABA67AF59791FF6CULL, 0x1486E95ED7DABEECULL
        },
        {
            0x0A68574EDFAEE76CULL, 0xC50B9B1C2ECD540EULL, 0x75268BD157ABEFD0ULL, 0xF9F637E0BC5A4008ULL, 
            0x53FDF658A64888FFULL, 0xB9F96A43CE1ADE2CULL, 0x4AFC3FB6CE776A4FULL, 0x27FFDC978A913E9CULL, 
            0x5BD525AC629EA00EULL, 0xF920FF2DF2BE8480ULL, 0x95A0A02DA7403676ULL, 0x4232BE5B7C764287ULL, 
            0x257AE0C32E20C216ULL, 0xA5644A2635BC23C7ULL, 0xD7510AE7CCDB9F94ULL, 0x3AE0015A471ECE63ULL, 
            0xE387EBBDC548C9D5ULL, 0xEDF4D4D058C6E916ULL, 0xDA91EA7F931DA93EULL, 0x8D41399075D451E6ULL, 
            0x3ECBAD1E96D48408ULL, 0x6EDB09A2FE4897B2ULL, 0x713F4DFF1F9CB19FULL, 0xCCDE994D634FB660ULL, 
            0x7C5574564881C78DULL, 0xE6ECB887256CAC98ULL, 0x8631FF74C006968AULL, 0xA9303BE6702E9743ULL, 
            0xCB2E02AAB89380C7ULL, 0x0D4D04E4D83C4226ULL, 0x0B1EE35507BCF942ULL, 0x65DF649F72518ADDULL
        },
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
            0xF116647717C2F2DFULL, 0xB43476A2165FD0C2ULL, 0xD398C2281FBF6054ULL, 0xC36D8035E828F7CAULL, 
            0x132EA7640E2108A2ULL, 0x21640DA1CF12E533ULL, 0xF50EB8BC88D9DEEFULL, 0xD69CA6A6CEB7E648ULL, 
            0xC42244DB8BACED91ULL, 0x30BDB9F420122FAAULL, 0xAD7418F5DD4B97D6ULL, 0x33F9AEFEFB398138ULL, 
            0xFD48A21F0D323894ULL, 0x12C10C3B84DD857EULL, 0xAFE911E21E0D5336ULL, 0x8925BE31145FBD65ULL, 
            0x9237E6D7A4C8F8C2ULL, 0x2EDAD844872A07CBULL, 0x59AF9D68E5C062F8ULL, 0xB47C83F8C21B20FCULL, 
            0x366C174EF9FF6260ULL, 0xAA857C162425EB44ULL, 0x03BA0C59D76D1F31ULL, 0x49F988593572E292ULL, 
            0xB046AB7EE7070E5BULL, 0xF1842AE83829D542ULL, 0x0F654E7B25C90DE8ULL, 0x15C1FA387DAAE1E3ULL, 
            0x2C69C1BCB5B4113CULL, 0xD8AA6904422E9446ULL, 0xEDACBE42BDB06AC2ULL, 0xD78F25848C5D61D3ULL
        },
        {
            0xD2E231ED2F97125CULL, 0xD524353F90C3E9C6ULL, 0x837471C0C1C10633ULL, 0x68371045AC871233ULL, 
            0x4E717CBDA477735CULL, 0x80050E5D340D2DF0ULL, 0x5B7CCE977F75C08EULL, 0xE99C9BCC1617ED00ULL, 
            0x443293F98C2F8C4AULL, 0xC938824A3205F5BAULL, 0xFAEF1B681C90E18CULL, 0x1B2F9B5E7C10E23AULL, 
            0x855739E9F4F98383ULL, 0xB4906859EA7FD934ULL, 0x33783D25569A82B5ULL, 0xFC292287F3D1E258ULL, 
            0x0BB81C78898E0D81ULL, 0xD720FE35D1592730ULL, 0xDEE53A7AD826F501ULL, 0xF96401B3222DCCF6ULL, 
            0x59A450723FA1DF95ULL, 0xEA93015DC8770FB5ULL, 0x18998BA1E0532BDFULL, 0x791EC98CCD0168C0ULL, 
            0x1772DEE62EA5E075ULL, 0xC925EB2E979A4932ULL, 0x813A18AF09AAD836ULL, 0x99C257B20FC749C3ULL, 
            0xB516F9A4C00253B3ULL, 0x8DABEBACEE1503C0ULL, 0x2F8AE48F6141B59AULL, 0xEFF71FAB1B9FAAF8ULL
        }
    },
    {
        {
            0x0F8ECDFDD851EEC7ULL, 0xFE5302A95AD08453ULL, 0xFE0C539368BF03C0ULL, 0x7784D903C025B3BDULL, 
            0xE75B5D1CFAD6FA42ULL, 0x03A8E2F75EF5ECACULL, 0x2456F995187BC1A5ULL, 0x589E9476D16B0EC5ULL, 
            0x794BA2344DD08AD0ULL, 0x0C421F53BFAE196CULL, 0x74206E169840CE31ULL, 0xD87B9E6FA1CAF1E1ULL, 
            0x382F26BAE8B33A35ULL, 0xD5DC8FC11D98D553ULL, 0xCBD579EC5C2AB4C6ULL, 0xB373625AEBEC3CDDULL, 
            0x1581138D8DB965A3ULL, 0x00CC503BE07429E5ULL, 0x244334D98EB5C19CULL, 0x2633EB7783CD71F8ULL, 
            0xC677FD977200F8DAULL, 0xAFFBB87CE72D7F1EULL, 0xA3874B4235336A6EULL, 0xC99A2FFE6E1FD83CULL, 
            0x50FBB8767E962CD9ULL, 0x28295F917AE4CC1BULL, 0xF2823EC417F8D14AULL, 0x0B3AD175078C48EAULL, 
            0xCEB0B57C12C689A8ULL, 0x27A6BA55D15DA689ULL, 0xE4B7E7FC4833B478ULL, 0x3405B4B96B86E02AULL
        },
        {
            0x4EDF556386E9F654ULL, 0x847F9C2037DEF72CULL, 0xAF371982C4498E14ULL, 0x9F33A838C9BB9282ULL, 
            0xD97F76B2CE650943ULL, 0xB39A39231E6733D6ULL, 0x7837EA6310B8670CULL, 0x1A15FB8B29406733ULL, 
            0xD6C732A57B9A7DDCULL, 0xAF94CAC93BC92F85ULL, 0xBC7AF6229DA73385ULL, 0x968B7744AE47B75CULL, 
            0x6A655B3504A92DB0ULL, 0x2F6E3DC1DF753653ULL, 0xA749EC0130EDD90EULL, 0x7377925ADB79CECFULL, 
            0xA02F8D0BC415C8E5ULL, 0x86F6F95DC5823CC5ULL, 0x27B536116AF10D96ULL, 0xE7A018C3543F45A3ULL, 
            0x89E95EDF22F889BEULL, 0x1B0762BE71552020ULL, 0x9CFD62ED9F2FC665ULL, 0x321905EB1A5DD249ULL, 
            0x38BEEBA363FF38F6ULL, 0x743B677ED0D1DC69ULL, 0xC8D219EB51715CF7ULL, 0x794B8237C37290CAULL, 
            0xB63B554A51EFCA3CULL, 0xFED52B4FCC40DD67ULL, 0x61651A930EE8AD23ULL, 0xD4ACD00CE802DF3AULL
        },
        {
            0xB06F168E3A6ED57FULL, 0x4586AA684257AFACULL, 0x0797826A3B851807ULL, 0xB8F1A19232FD7369ULL, 
            0x8A1B16FF8D49956BULL, 0xE9D4F0F6818AF8BBULL, 0x36A0969FD0FE9397ULL, 0xD24AC1883167F7B9ULL, 
            0xB0F6BA6B98347937ULL, 0x18CD26A6BC83AA89ULL, 0x75A6E5B1A0336031ULL, 0x86AEB38A60D550A8ULL, 
            0xAD39B85E0FF13FA2ULL, 0xC3A51F229A2EAE2DULL, 0x60534D94EE531E9CULL, 0xF62F73628AD3F04AULL, 
            0x6721A3E937751C1FULL, 0x7C6458B6D430DD6CULL, 0x9BBE503B8DB63DFBULL, 0x28C36EA39516BC19ULL, 
            0x9CABAE81ADCACA9FULL, 0x42B9F12A93BDD274ULL, 0xA0A1180BFAF35392ULL, 0x3EBEE0954B6D21C2ULL, 
            0x9D661D609E21EA8EULL, 0x7C7A69255E95F0AFULL, 0x7F93D69B50D994F2ULL, 0x5359773147CC87F7ULL, 
            0x811F49AF622A2C9EULL, 0x225D014204728209ULL, 0x32CD692C50ADF254ULL, 0xA5CD2DE8CCEFDF1EULL
        },
        {
            0xCF936E0EE97DF5C3ULL, 0xE71A6925737C7173ULL, 0xD34A76B61C2A1F20ULL, 0x5DB79AF4CD765F53ULL, 
            0xB5D4AA294C8D7709ULL, 0xCE3BF36815AF1A49ULL, 0x2C924A3E0D645791ULL, 0xBDB006905731BA19ULL, 
            0xFF6B6F4B85760D27ULL, 0x8C4F78B13811AE28ULL, 0x9A7C4E5F9E8DF00EULL, 0x9CABE922D4807998ULL, 
            0x25BD801ABC9CF726ULL, 0xA3666C53204603A7ULL, 0xC4081A42B5C55A6AULL, 0x6EC5A93BD5626002ULL, 
            0x31FE56F1CE43E3DDULL, 0x864E36597D518697ULL, 0x3EF8CD91D6DA0C5CULL, 0x9DA35441C763219EULL, 
            0x7EEF0F8EC1121CEEULL, 0x38D27E7D2B57267CULL, 0xACE7FD46C6F1EE12ULL, 0x65F7E0D3440E98C4ULL, 
            0x6C2ABAF5A1FC9FFDULL, 0x7A4C9D1FC4B6B323ULL, 0x14F0FB2A058DAFF8ULL, 0xB73A10B16462701DULL, 
            0x8DDE84760EF7F788ULL, 0x94B28E611ABEB1FFULL, 0xF2725CC374A9A892ULL, 0x29F39916EA850A1CULL
        },
        {
            0xB32D5B412A555BDCULL, 0x3A091DDC6DD8664EULL, 0xF82490ACD8E66606ULL, 0xAE2F341FC65BA891ULL, 
            0x0CDD660838EF7A89ULL, 0x47A6F4E33A69D62CULL, 0xA6BF50042C2E7B6CULL, 0x928F9C113068A8A5ULL, 
            0xAF5C0AA73C44CB91ULL, 0xC163D91240B08967ULL, 0x3408BF9A16BA66B4ULL, 0xAD889D4ECA808FC6ULL, 
            0xE3FC2D8BC47B1AE2ULL, 0xD4322A69ACD45C1EULL, 0xC3AB686572DF49A1ULL, 0xE98F0357380923C2ULL, 
            0x0C647DAE45809822ULL, 0xCCA9CB1789828512ULL, 0xD9E942CB729065B7ULL, 0xAA221C52631136EEULL, 
            0xDACA0A56B6DC6751ULL, 0x8BF0E225356252ECULL, 0x15C8FDFA31784C26ULL, 0xD2A889E3F2760114ULL, 
            0x14104612A7D54343ULL, 0xE12491E4AC437FD6ULL, 0xCCDBA6987A44F745ULL, 0x22B58713D1298BDEULL, 
            0xB3A922F078B2719BULL, 0xE72C8AE4833B2029ULL, 0x80F07DAFE1BC918EULL, 0xB6E7BB78CE8EEA4EULL
        },
        {
            0xB6B5418595A26A1BULL, 0xE625E57A8A079BD5ULL, 0xB920F348CDCE7323ULL, 0x835441A6CEEAAD09ULL, 
            0xAEAB26D6F467B58DULL, 0xFEE87FCED20D34B5ULL, 0x01AA924295FC59D5ULL, 0x94448D7EFB227D4DULL, 
            0xC1FD7FA5633C1646ULL, 0x8B1993E8CCF898EEULL, 0x6C937FD77AC90A5CULL, 0x036C06D93C1BE919ULL, 
            0x7AD36EE2738A3859ULL, 0x908C623BE5B3D5DBULL, 0xFDE792A5995C1E36ULL, 0xD6A3F8E0D4A0C006ULL, 
            0xCFBFB4FACBAE143FULL, 0xF8CA566E0631BA12ULL, 0x3B5BFF9CB87F88A4ULL, 0x97E74534D4216A86ULL, 
            0x20F1732FE26F8796ULL, 0xCA7A6AC2BF3295E8ULL, 0x9A9507B9F58F2575ULL, 0x53607DFD5ABD2236ULL, 
            0x1FC179896C93F6D2ULL, 0xCAFE56F0562BFBA6ULL, 0x2FA2FB7CF4243AD9ULL, 0x8D13EC9739609073ULL, 
            0x8BFF1323F3CA0A82ULL, 0xCCDDF7D728D3E782ULL, 0x9C2CF6AA4EC33395ULL, 0x8411859EF3D2C5DAULL
        }
    },
    {
        {
            0x8E9FD81733A9551BULL, 0xEE6B39BF9B10E4CAULL, 0x939F8A733EBCBD52ULL, 0xDBFD063B327EA611ULL, 
            0x253D8199E5A6CDA5ULL, 0xC1A6F7D4256630CBULL, 0x7392EEBD7CD2BFE6ULL, 0x28DDBFFD4E5E0E53ULL, 
            0x325BB50F67422236ULL, 0xEA69B26E7B55D306ULL, 0xFD77FC8168767331ULL, 0xBD876ABCF1A6C8BFULL, 
            0x07E8F82E0F20A18BULL, 0x2F7C52296C52DFCEULL, 0x6761BBFF0CBDBF33ULL, 0x53AEC38A09BE6377ULL, 
            0x2166C311A26D2E32ULL, 0x180B3CB791A29D97ULL, 0x2DEE7D4AFE3138D5ULL, 0x57FE0D0D8D16DA82ULL, 
            0x0929618F49F3F523ULL, 0xB4E5377F20CFBAA3ULL, 0x9FFEE2267D5B7C5EULL, 0x76AC49A25436EA93ULL, 
            0x03D24CFDE036B669ULL, 0xEE93A51A578B9A67ULL, 0x37C2AB9C7EB78D6BULL, 0xB82F6C914793A368ULL, 
            0x59627AEF59B505CFULL, 0x77D9FD1EB7C5BD1DULL, 0x2C51969D93DD9165ULL, 0xE80EDB783EEC9544ULL
        },
        {
            0x8314F4C9588AF721ULL, 0xF4E4B8056ECBD276ULL, 0xEF224D6320E6E611ULL, 0x204DE8E1D47BFF66ULL, 
            0x262ED8C35E315779ULL, 0x993986460A08B5F7ULL, 0x2EBCEE9F961A05CAULL, 0x4D1E0097948EAD90ULL, 
            0x77A8A821BFBB1445ULL, 0xA7C48F0D523D2AD8ULL, 0x49D1E9879D495E2AULL, 0xE1E6AEE67BE26BA4ULL, 
            0x7BC74152D21DF958ULL, 0xE888DBA69787D8C6ULL, 0xCEE1C7A44716045BULL, 0xCFFB5B5237D230DEULL, 
            0xB0A6FC7CA09335BEULL, 0x1A6CF4D7EBEF9C31ULL, 0x871BC9B353A6288CULL, 0x0FFE882ED71C4C7EULL, 
            0xAA392D6C398DEBDFULL, 0xC7E037BE2EB4A069ULL, 0xBE4DDA50C174CA54ULL, 0x67BECFA7F234AF1FULL, 
            0x837875BF5D588B8FULL, 0x3A253F9503663BAFULL, 0x76A3ED33461071D7ULL, 0x4D410ED7B09C6BBBULL, 
            0x85DA4634F9E3585EULL, 0x39E3EA4A51E3E0ECULL, 0x9FE1E322F659D6FDULL, 0x0649E28FD984D122ULL
        },
        {
            0x75A0FCB4AE33C43CULL, 0xE92609DD76AFC5DCULL, 0xBD49AC75F3D91C7BULL, 0x8E69F7B90FFB371CULL, 
            0x65F6A4718C1FF39EULL, 0x902B516E466605E2ULL, 0xC0DAA04D9A4F6027ULL, 0xFFEF0063CD6B853BULL, 
            0xC25CF26A057EB93DULL, 0xEDBAE161CF76BF6BULL, 0xEF2DF7355DF0715CULL, 0xF7D31B1854D94F27ULL, 
            0x43A51DC50260234EULL, 0xFDCC41B723ECBBDDULL, 0x68442BD7484800F9ULL, 0x47EA5425490CE822ULL, 
            0xB83796C0C2463A63ULL, 0x20CCCA3B782FA6E2ULL, 0x4913998E092560F5ULL, 0x097D458D89100400ULL, 
            0xDF8E461E57D1049BULL, 0x87F0885E366B065CULL, 0xDA53868F747B0222ULL, 0xF9D9451DBF414C22ULL, 
            0x3FF9EE7CA209E6BDULL, 0xAFA57D73CCF65B69ULL, 0x74A528AF3DE7724BULL, 0x9651A7090AB91FDAULL, 
            0xD5482A2A2E90300FULL, 0x146AF0EC589C74D5ULL, 0xD30743B54A2CCF9FULL, 0x329CC314890CD3E4ULL
        },
        {
            0x5C9C2B4ED6698C84ULL, 0xCE9BB1775FF9D190ULL, 0xE98B7B0580704083ULL, 0xD3A766128422C88AULL, 
            0xCCC5A08539925A62ULL, 0x1EB5B41F4AF8D318ULL, 0x95B9C09C57BEB127ULL, 0x0A26E5D2370CD618ULL, 
            0x923D73EC8E669E23ULL, 0x225B3C454D1D3088ULL, 0x50DA646D419DD3C7ULL, 0x681BC32B909A6FB5ULL, 
            0x5DC3A5BC29172113ULL, 0x3CF948EF78867C39ULL, 0x60E89E3E61F18FD2ULL, 0x4ADD834C5E027A82ULL, 
            0xE94545740EFF3858ULL, 0x2AA432BD9B51E678ULL, 0x011E5CE1060F337CULL, 0x7BD2F72BE131555FULL, 
            0x871F461918B3BF28ULL, 0xCC883103BE5EB074ULL, 0x4AD7DDA4653DC0DBULL, 0x0E853F305AD1CC69ULL, 
            0x27050781E7B87EA3ULL, 0xFBD8FF41A44F078DULL, 0xA881A0BC857295C5ULL, 0x18AF14D49ECDE831ULL, 
            0x08F20DF518FC4BB9ULL, 0x9DC6E3BDF7539EB1ULL, 0x93F79DE195256EC7ULL, 0x51E9F4D1859765ABULL
        },
        {
            0x8BD807AC775713D5ULL, 0x443FF2E4DF2BE6F0ULL, 0xC285DA63D2DC11AEULL, 0x8F04A7F3CB326BA0ULL, 
            0xE3A60E390E9DBE4AULL, 0x3B9CB4B9AAC8F656ULL, 0x0D5DB571D0B83893ULL, 0x99D1697D1FD8F0F7ULL, 
            0x188D82186BDA90D3ULL, 0x1BDD6DD6C3C46992ULL, 0xF5332EF2E5DDC5A9ULL, 0xF3BA67CBB137E421ULL, 
            0x5C9B4469CBF994FDULL, 0x566D2B3BDB66CB89ULL, 0xC14F17DA9B4750A4ULL, 0xB9CA9613F5A210ECULL, 
            0x32C6D22E3BA1D3C3ULL, 0x891FA19221C8B7ECULL, 0xF4558BE6B5D61FCCULL, 0x240187D26D6FBF3CULL, 
            0x12FBD9C79B1BFF8FULL, 0x91FC6837FE7092D9ULL, 0x5E0610DFC60D513EULL, 0xB445F8D06E5DCDCEULL, 
            0x150284387486D4CDULL, 0xA73E1C9A7530A42BULL, 0xF6E59C12F96E0263ULL, 0xF9417CD5E0319377ULL, 
            0xB7E496269190659FULL, 0xC67C246579A58220ULL, 0xCD9C4FFE43A874DCULL, 0xD379D3AEAEA1A2B9ULL
        },
        {
            0xF75E84C9FB45A54CULL, 0xB4DDFEAC12F34949ULL, 0x78049D133D0012E3ULL, 0x89194889923ACA1EULL, 
            0x6546D5566A9F9FADULL, 0xED6D1059F8C43584ULL, 0x42FEDDFEE75B0250ULL, 0x600479A9C1F1BD21ULL, 
            0xEF5318C97650166BULL, 0xEA885F0C83416227ULL, 0xE3C1479CE10F0222ULL, 0xB082A42503B02F92ULL, 
            0xB53C7EF842678A23ULL, 0x03017B0D2A49A846ULL, 0xD25A99B7D4467961ULL, 0x750383877B998ECCULL, 
            0xFF773BF0F39B509BULL, 0xA13FEF61D2476C3AULL, 0x68EED448FC901134ULL, 0xA107068AC8B8BA5CULL, 
            0x475F9A01C2BC72FEULL, 0xEFC2504CFDA1862AULL, 0xA310BDB4FD9E5582ULL, 0x1FEFF62743EAB617ULL, 
            0xCFDEF64CAC980FB8ULL, 0x92FB56C88DB4D49DULL, 0xF080678DD5F74007ULL, 0x28C7D8DA5F001228ULL, 
            0x7D7DCD3800EC231CULL, 0x84BA08063EDFCFB3ULL, 0x2BE3C017740CD340ULL, 0x9723C9D1AC7C6967ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseDConstants = {
    0x9D6959F01BB8757EULL,
    0x892C1421917A0410ULL,
    0x29B4ED522B45B09CULL,
    0x9D6959F01BB8757EULL,
    0x892C1421917A0410ULL,
    0x29B4ED522B45B09CULL,
    0x7061E501F419E1ACULL,
    0xB87C2ECF2FFC3592ULL,
    0x2C,
    0x36,
    0x7F,
    0xB5,
    0xC1,
    0x5F,
    0x1B,
    0x6E
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseESalts = {
    {
        {
            0x8BE9959118FD520BULL, 0xA8059DAD3362AD3BULL, 0x668EF856DC7B96EEULL, 0x9A8F87732CC198E7ULL, 
            0xECF47C5AB5BC4E07ULL, 0x1372E1CE56DCC397ULL, 0xD0DBC7EBDBBBCEF9ULL, 0x3FCCC589338B718AULL, 
            0x6EB8FA703459BC23ULL, 0x10F5C1C6F38D8F5AULL, 0x2E78F32843BD7560ULL, 0x96CF862D2360E339ULL, 
            0x27ED43EF56547624ULL, 0xE0FC2BBB476695F2ULL, 0x82562B84AD6D292CULL, 0x7917A7A072EA3306ULL, 
            0xAA07EEEF80490F2AULL, 0xD01DA2A9F98CF553ULL, 0x3295811F3E740827ULL, 0xE413F37EA23579D5ULL, 
            0xC375237BC306FBEBULL, 0xD25753D81845BB8AULL, 0x189AA82C43FDBBEDULL, 0x319CB8C169512EC9ULL, 
            0x99258CA9D5FC6960ULL, 0x7574910FC36E2ACEULL, 0xEA59730DCD3B79A2ULL, 0x9A363636AF3711A9ULL, 
            0x78F1C7943C27B41DULL, 0xA34DBFFCDBBE7BD4ULL, 0x87CF46CAA792D9F8ULL, 0x0E19AA9FC78C2374ULL
        },
        {
            0x5FBE175C88CC6672ULL, 0xE211CCBED22A7CDEULL, 0x3BEB40EB97B2B686ULL, 0x5F9E7E160F5F4661ULL, 
            0x100DA161BB6BC471ULL, 0x62B0D63D030728E0ULL, 0xE388725A1357BBA5ULL, 0x128E4C35E613ED7DULL, 
            0xE6885E50A93DE459ULL, 0x9260E9BE235309C8ULL, 0xEF48F61C30AFEDE2ULL, 0x9C28B484C006A376ULL, 
            0x76327C11341565EFULL, 0x65ED6A9FC0CD3E92ULL, 0x55ED0314CB79F91BULL, 0x3E30183509945154ULL, 
            0xCACE0479124B7766ULL, 0xE5EE285974D49AADULL, 0xDC7298A225696E80ULL, 0xDDE4CF9A0D9AF337ULL, 
            0x497D5A8AE0D9A11BULL, 0xB434F9BE82B13AB8ULL, 0x086272AEAF5C2041ULL, 0x5A7ECE6F0D915ADEULL, 
            0x73E8071451196CBDULL, 0xE77EC465FE02CC47ULL, 0x3D81390B8E1B1E30ULL, 0xE2E5502ED513FBF3ULL, 
            0xD4DEBDE7C0AA5DA0ULL, 0x4B5B0D173E97D8A5ULL, 0x10F82E0136AD0EA9ULL, 0xD90092C4551587C7ULL
        },
        {
            0xE315C369D838D843ULL, 0x85D6125C99ECDE07ULL, 0xE1F1208AE369729CULL, 0xE2A4E789B9D0AADDULL, 
            0xC11328B8A5A8CA5BULL, 0x9B2F62A3A6268E04ULL, 0x5C9D818E8AFFCE18ULL, 0x1F56F65A991EB47FULL, 
            0xEDEEAF13BA9CA581ULL, 0x8B62E5281C447584ULL, 0x11AA31BA9C5CB678ULL, 0x97F7EE962AAFE593ULL, 
            0x5A4332E7CBCE6DC7ULL, 0xA4D5DD29F8924323ULL, 0xE151EB327FE1DD0EULL, 0xBEBB42D3D5DC5AA6ULL, 
            0x2AFF49ED52A4C632ULL, 0xE72FB739C1447274ULL, 0x38422B2B1EEDF762ULL, 0xE06F99E743F9A82CULL, 
            0x7510242BD5E10405ULL, 0x6F2CBBA40BDE3A0FULL, 0x98B2AEEE3B2CE199ULL, 0x53B67DD07A84B999ULL, 
            0x4B03EC6330E1B3BAULL, 0x2A2AC6316495CC89ULL, 0x6B7609166716425BULL, 0x2163F3E0E5101B71ULL, 
            0x4BA5E4B833A5E519ULL, 0x2868B7F2A2CA59A4ULL, 0xFFEE8ABB01EDD3E7ULL, 0x0757F11381828068ULL
        },
        {
            0xB57FAC9AB1D304B5ULL, 0x967EC8E7AB57EDCDULL, 0x26B6ECEF7152C866ULL, 0x613CB7F7C9DC5EFEULL, 
            0x92695EB51950375DULL, 0x41017261F2C96609ULL, 0x57BD49C57A72DDA2ULL, 0x9F4874D9C40E715EULL, 
            0x63EB29A728976D32ULL, 0xDBED302F92D3ED08ULL, 0x2A6CDAA850341469ULL, 0x3001057FB23A89A3ULL, 
            0x8334AD9A4DCA9CDAULL, 0xA9CF93E4AFF5DCCBULL, 0x45F26C84634FEA37ULL, 0x1F95DFFD65DF16F6ULL, 
            0x07D02E1E1F0B31B0ULL, 0xF748CD65797A4DD0ULL, 0xC49E54770758121CULL, 0x28DC1D8EC5CE21C2ULL, 
            0x75CF77CBF3D420E9ULL, 0x66E122CC669A6446ULL, 0xAB2BC97274A461C3ULL, 0xDF437856A7658FCFULL, 
            0xBC6994FF06769582ULL, 0xA578AFCF43D42155ULL, 0xAEC32BC1775DA203ULL, 0x62B9FBBF2541B2FBULL, 
            0xAC8F87113B5E619EULL, 0x970324E9C90051B4ULL, 0xEBFD72604C4FD5ECULL, 0x9B3F301B840855C8ULL
        },
        {
            0x90D8463FD40E9E22ULL, 0xFA68B0F22A00D83BULL, 0x3931022AF3639D89ULL, 0xA911CA391223DF82ULL, 
            0x80B56AAAF941F476ULL, 0x6C158E5960833B7EULL, 0x7D0866DA294D47B9ULL, 0x836B43D33E1A9334ULL, 
            0x3145EF5EA13DB9B7ULL, 0x57B4A543E84B6BBFULL, 0x7EB038718C118521ULL, 0xCC3B922BCA5B2192ULL, 
            0x0FDF406CF05F8CABULL, 0x35E65BB2689EA3E5ULL, 0xA3CF8A41D791B6F0ULL, 0xC90AAFAB6BBFB80DULL, 
            0x6D2794B342EFC842ULL, 0x67F0953972EE6A63ULL, 0xE268828CF8EC1CDFULL, 0xDD601E28A60D48D1ULL, 
            0xA27B1953DB8CFB12ULL, 0x40EB5738C91C1CCCULL, 0x93444E8D85A9F623ULL, 0x7804BC124A7141DDULL, 
            0x7BA8DA33F0134D10ULL, 0x2BC1929B45B89F4DULL, 0x5631E83661DFD91FULL, 0xDEBA14E03B42457EULL, 
            0xFD981CCD8F7E1E85ULL, 0x0E1E224DE033B497ULL, 0x0B57F41683E0B951ULL, 0x732D6CBA4D1DC298ULL
        },
        {
            0x25708628508E1381ULL, 0x235278A024F6B2BEULL, 0x75D5453F20BAB9DDULL, 0x74BC0EBAB0320E09ULL, 
            0x74C310225AD8B99AULL, 0x3EC785EE6EE41106ULL, 0x079B0A3D6A6888E5ULL, 0x4429BC61007C8263ULL, 
            0xF0C3D5165F03F548ULL, 0xB46A3335A880CB32ULL, 0x8FE8F77500B16B5BULL, 0x33B3366DC703EAF0ULL, 
            0xD57D25EC15104DF9ULL, 0x9CC393F06695AF77ULL, 0x7C5B6D9EA46FD67AULL, 0x4134D2E0F9B34EF7ULL, 
            0xBF2A19C6BD59489BULL, 0x3B802A080784A6E6ULL, 0x6F3A842411C2152FULL, 0xE59784C9CEE7408FULL, 
            0xCD407D134B14702DULL, 0x039BC634C7847180ULL, 0xF42699D345C5FCEAULL, 0xD2104274B1FBE639ULL, 
            0x201B4A783B6ECC62ULL, 0xF17071B0D1500256ULL, 0x76F01C14D0E764E9ULL, 0x470868E5E552068FULL, 
            0x47FAC4F9822A5452ULL, 0xEDF94B50D21815FFULL, 0xD234DB5F4A7B9784ULL, 0x98300EAE43AB51DBULL
        }
    },
    {
        {
            0xA74AE1CF6E05C143ULL, 0xEA571CCD0A31E7B8ULL, 0xAC431F57ED3D9609ULL, 0xEA9DFC8CA8D6C5FCULL, 
            0x55440C8829E9AF8FULL, 0x731B7EA29047D8D1ULL, 0xE9035A2DCDE0E55AULL, 0x30D5AC364EE58F8EULL, 
            0x7AB83A2310E3BB59ULL, 0xCD922F950BACD5BDULL, 0x5A6E45934B4A8B48ULL, 0xD43AF0E407608131ULL, 
            0x1FDE32605AD9CDD9ULL, 0x6D05051E28D662A9ULL, 0xD06FCD5FC6897A10ULL, 0x5B057A38EEFD0C20ULL, 
            0x69E0C79A204BAD81ULL, 0x776465B650DBC07CULL, 0x38D0F075CF632A32ULL, 0xBFBD1285F04F76C0ULL, 
            0x3415212FA756D1E8ULL, 0x66A634C0F082D513ULL, 0x3BBD71B7776B7606ULL, 0xD9BD5079EE5C7F60ULL, 
            0x5E5D648A8C3C1809ULL, 0x33907A8741A6099AULL, 0x62AEF639B7D84A3CULL, 0x496EB5A342E30F29ULL, 
            0x26B728A7E1F31422ULL, 0xCA5C241FC29690CAULL, 0x048A91115C9718E4ULL, 0x4EA0BFBB86106679ULL
        },
        {
            0xC80D000CAB051F8CULL, 0x3E596FF7316D32A9ULL, 0x2E5906903A036A36ULL, 0x67FF37D4ED79785CULL, 
            0xBE84FCBCE9B812B2ULL, 0x3B60FD153ECA40AEULL, 0x7575D533C99F0B3AULL, 0x895D222BF3AC0906ULL, 
            0x8DFF3A05607BCBF6ULL, 0x0E62B7ACFB3B7BF0ULL, 0x0E0A8B1DD9D51384ULL, 0x27F3F688E4FD835DULL, 
            0xCAE03F29BEFF7DD3ULL, 0x0A118EF2CDDD7023ULL, 0xD10BBC36BA8EDFF2ULL, 0xC22A20657213C944ULL, 
            0x701494DC2C4C55E4ULL, 0xA81D14C14ABE289FULL, 0x6004E5402F4CCD95ULL, 0xE4D20F6A00DFDB84ULL, 
            0x8E80C1642F138233ULL, 0x60103016C91438ADULL, 0x9EFD25C28E41F265ULL, 0xA3839EA6F938A5D9ULL, 
            0xFB9E547EFDA94D12ULL, 0x68B3FE9F74CB7BC8ULL, 0xAFFB933AA6436167ULL, 0x1B07293AB53C4741ULL, 
            0x8F5C414C26BA5C68ULL, 0xB1F99213BB13FBF4ULL, 0x9166D0E7F597D3B5ULL, 0xBF985AA4585ACCB1ULL
        },
        {
            0x0AA2435A9B1A8863ULL, 0x852B2443BA181BEEULL, 0xA31F6A3163D799E8ULL, 0x94E12014E805F72FULL, 
            0x6B3E8BF9893787B2ULL, 0xBCA2F838782DA7C9ULL, 0x2C61E903CAA0072EULL, 0xBAAFEFA8E7C8A4E8ULL, 
            0xA13A59CB98A27FF9ULL, 0x7339EFA08B6930FCULL, 0xAD1FCFA2626C8034ULL, 0x817408FFBDE870AAULL, 
            0x0FF188664E324EF2ULL, 0xDE5D124942CDCF18ULL, 0xB5C7AFDB5D71B71FULL, 0x88D0412CE78A217CULL, 
            0x85C5FBA279497922ULL, 0x8231C52A5D48A62EULL, 0xFEE27F91A7DF3204ULL, 0xCC3F7B78E34EF44FULL, 
            0xAD947AADDF2A9C34ULL, 0xCC2550B8BDA44A1BULL, 0x253C5358B52A6909ULL, 0xA14FAA6BDF5B63BEULL, 
            0x0A4243378568A2DCULL, 0x55F49F53E8428B0DULL, 0x867337AF2B38A018ULL, 0x27FB5E09EEE07ED2ULL, 
            0x7DCD55FA87F0D47CULL, 0x1B8534EB8011A2A0ULL, 0x30B55DAD1F536A39ULL, 0x4636E4B3A8F7109CULL
        },
        {
            0x623866E47D06829AULL, 0xA0C285B2AB07BD24ULL, 0x978B6715020B4737ULL, 0x7CF2DE68F509E890ULL, 
            0x4C6590B743F98D50ULL, 0x45FA574ADE10444BULL, 0x238E9A3CE48C80F2ULL, 0x4B7F4CA4D3C2690EULL, 
            0xDDF3D110504A0239ULL, 0xADBBD724A336DFE5ULL, 0x09376FF6A356204FULL, 0xCDD70750DE891604ULL, 
            0xF990270782828356ULL, 0x4C3C325122C4CB6FULL, 0x140652A95ABF72A6ULL, 0xCA170B926A717C72ULL, 
            0x4A43B1E443A8226DULL, 0x22DFA4D4AF4047ADULL, 0x155407E6A0BF83EDULL, 0x05CD7506F7637017ULL, 
            0x29CED583E88FDA62ULL, 0xE3E409ACAB570791ULL, 0x9F2EA2762BB288D6ULL, 0xF065C42D486823F4ULL, 
            0x027B6E2BA2FDAE97ULL, 0x1F1CC288150DC8E3ULL, 0xAC7D865E0B909FB1ULL, 0x166C05D80ED055B6ULL, 
            0x09CD37B14BF0657BULL, 0x19EDDA5C5F6B86E9ULL, 0xEE19AEEE09E7EB0AULL, 0x50B2F5D174B5BAF9ULL
        },
        {
            0x544A0254E1EA8829ULL, 0x079FA786B5539427ULL, 0x6B37C232B7D2DDDEULL, 0xE500447B7F89D9EEULL, 
            0xCF696721D6C07C3EULL, 0x1FBB3BCC49DA791BULL, 0xD8189A14BD68C8C0ULL, 0xF05C270B2C8A3A0BULL, 
            0xB3697E0355B09584ULL, 0xF65D4C4D117B6690ULL, 0x12A9E520BE9340ABULL, 0x79CD01EA5FD43470ULL, 
            0xD45469760B358515ULL, 0x99166BA7B08B0B3BULL, 0xAE5FB48F0CFEC347ULL, 0x5EE33763DE553606ULL, 
            0x5F5919E20AE22E4CULL, 0x47A6C6FA68A902D7ULL, 0xC98F7C05EE01FB45ULL, 0x24BAE4321D5C9698ULL, 
            0x158F251D9EDD4268ULL, 0x8E9DF2019252FA62ULL, 0x61086E0CC301C8B4ULL, 0xA1B4C8E346EDC818ULL, 
            0x56F6050BA49B170DULL, 0xEE34E051923FD2BAULL, 0x3A9D699D008E8D52ULL, 0xAF1AF366D631DE2AULL, 
            0x61708862E32B5312ULL, 0x1690815178A13179ULL, 0x6DF4354DCB572A21ULL, 0xE19BB75AB27051A1ULL
        },
        {
            0x6E92B45DFFD8A178ULL, 0xAFC0C6AF554CD773ULL, 0x24A1F8D59770BC57ULL, 0x4775ABEB9F0FA974ULL, 
            0xEC51DACF77E5AD14ULL, 0x130762F5D65E4017ULL, 0x8352AA6062975E60ULL, 0xCF62243EE7FBD147ULL, 
            0x04CFF1E00F48B07DULL, 0x3C61ABA8B2144419ULL, 0x325D8CAE400395B4ULL, 0xC1A8AF92A8937B77ULL, 
            0xE60C2ABDEC0AB7A0ULL, 0xD1C38FF16ECE5B2EULL, 0x0D224FBFA2C6B015ULL, 0xB876E47029735249ULL, 
            0xE0C894006D3B0621ULL, 0xB7F98ECFBFC0172FULL, 0x2AF217A38B920814ULL, 0xF96AC3A8D0C3F5BEULL, 
            0xDC64CCF2A8893590ULL, 0xD910921EA7A503A8ULL, 0x4D7A5C2239593446ULL, 0xC5880E36BD3BAD48ULL, 
            0xD44FE6DA07E4816EULL, 0xDDFCA8C1D39CA118ULL, 0x625C1A3E7777C3CBULL, 0x7D0935EFA8184CBCULL, 
            0x7713D0FDEFDD78CAULL, 0x34E23F6334DA674AULL, 0x520EEA72635A4AC5ULL, 0xADEB402AE88B7F61ULL
        }
    },
    {
        {
            0xBEEC87C0EF884C3CULL, 0x02C721186F154164ULL, 0xE9F76E20033F535DULL, 0x8BF23CAB36B11703ULL, 
            0x37C1B4F885A660D6ULL, 0x4FC9B11A5ACD03B0ULL, 0xE01F3F8387934024ULL, 0xAEA1E71CCDC54F11ULL, 
            0x543156462F876735ULL, 0x302447648F426056ULL, 0x28F0D538646C5797ULL, 0x424BFD71450A59D4ULL, 
            0x4647A17394F34FC0ULL, 0xC7C49E0858AC296AULL, 0x712E94210E859354ULL, 0xB094E6F893F7F427ULL, 
            0x2F9AFD24F2AFAF61ULL, 0x94A46686F5EA0E15ULL, 0xAE46DEF74EEA6427ULL, 0xB0CB7323E75BCD05ULL, 
            0x87D9A44F7AE30159ULL, 0xEA5D7D9F89BE799FULL, 0xE51923F257ADF762ULL, 0x4E98EE656A5122E6ULL, 
            0xD322A33EDF6B4646ULL, 0x6923B32FCF0DAB6EULL, 0xC49730D8C1CC9EEEULL, 0x937A3CA50E4A2D0EULL, 
            0x880F06FF1FACD802ULL, 0xD4F59AAFEF489407ULL, 0xBCF311C966EF7A99ULL, 0xEB1D79A82B14C044ULL
        },
        {
            0xF85602ED0B91ADBCULL, 0x837136BD597521D6ULL, 0xE1D489486267AE54ULL, 0xE616F12C4466A1D1ULL, 
            0x810D8A1B195F1ECFULL, 0xB2D4515797A502C9ULL, 0xE08CB7FDE1E2C83DULL, 0xFEA556F8047002A3ULL, 
            0xEA20756118F2C94EULL, 0xDDCA5A4A29166D5BULL, 0xBDD44B00304C6DE1ULL, 0x65FF677755336F4FULL, 
            0x270224117080F49AULL, 0xEFF2311E6806A2CAULL, 0x509350FC2335B859ULL, 0x1EEBD61EE235A78AULL, 
            0x944451A0F396FF96ULL, 0x6AD2B0124674187BULL, 0x90DB279BAD3629A4ULL, 0x632688A4543638A0ULL, 
            0xE711AF90ED088E01ULL, 0xA6DB60D93AE829F5ULL, 0x91B8CF967826A487ULL, 0x5B428C19F3EE0A02ULL, 
            0x91F111369A99D98BULL, 0xD50074D868CB9F35ULL, 0x5EB810760DA28385ULL, 0xFC36C18308D5BCECULL, 
            0xF506E1C7D9FA5DFBULL, 0x9D352CC02FFF4D71ULL, 0x6356F1BF624BF1E5ULL, 0x9E5B9FF91DC56A96ULL
        },
        {
            0x65828E20B4D8D420ULL, 0x231846FF70C886CAULL, 0x57404B15CD2F7E93ULL, 0x57721B9BE57C9438ULL, 
            0xB0E118156621D2C1ULL, 0x3A15B4D3CA0D2A31ULL, 0xD4E3580CF7A53E1EULL, 0xB80AF5BB123278CAULL, 
            0x4F72047739D3823BULL, 0x84FB3A9F4AD858DAULL, 0x23534C12B5813426ULL, 0x8E3D459544827C84ULL, 
            0xA3D17F2E9A20BA8DULL, 0x2F92BB9CDFC309C6ULL, 0x45145042360E8D3AULL, 0x55FB45E4C187D677ULL, 
            0x75F635ADE7356BBCULL, 0x96B4826D8466F442ULL, 0x6031E4FF8CD57EB8ULL, 0xFEA29EC54BA4CDFFULL, 
            0xCD1D78841EE8B7B2ULL, 0x081FD39F296615E1ULL, 0xB2B1F8F9225078C1ULL, 0x2738007F7738ED70ULL, 
            0x7456EEEDBAF86F73ULL, 0x27618433C6774514ULL, 0x174E3DC803B2ED60ULL, 0x60D2146270BC0B5DULL, 
            0x8E9B2B97F89AEDC9ULL, 0x8726C9171AD371D2ULL, 0x3AA89CE26605A9D5ULL, 0xF7862CB600168028ULL
        },
        {
            0xC6E784F3CD166FD6ULL, 0x48AC51DB983B1AFCULL, 0x80A30EE528472140ULL, 0xF427DA7099D7DA44ULL, 
            0xC809BAAC7DFB62E7ULL, 0x98B0596975564E85ULL, 0x7B7E46A6F56222EAULL, 0xCDA462D2C5E78613ULL, 
            0x1EFAAB129D607EB5ULL, 0x0DC2C9EA50FB62FFULL, 0x37B706AFAE856C1BULL, 0xED3F0AE2A7E27436ULL, 
            0x9F1EA3FE4CF21681ULL, 0xDA398AFBB18D572AULL, 0x935F733F69145C3AULL, 0x0EC4D39FC437F352ULL, 
            0x36C9A71AFA68FDAEULL, 0x060416AC3E1A53E0ULL, 0xE41167A451FB5282ULL, 0xFE2FBE92F004553AULL, 
            0x6AE9344E0A7BFAA5ULL, 0xB63387EFFAEF6BEEULL, 0x7FB4486E3EA1353FULL, 0x3C9A4BB47E0A875CULL, 
            0xA45A0B45BC1182B0ULL, 0x41ECD28021E8BE29ULL, 0xED1EDF4185DA82F7ULL, 0xDE1060F11FE2D937ULL, 
            0x617FB899185C9C06ULL, 0x1184D8CDFBAF689BULL, 0x565EA73FED0ADC12ULL, 0x439FE563C983C829ULL
        },
        {
            0xBFE46F81B97FC504ULL, 0x257B2C198E7840D6ULL, 0x214437F2BEF35131ULL, 0xACC5E9D6CB6AC3E7ULL, 
            0x4D954B3ED3665EB3ULL, 0xE560E8AD7E7E43D7ULL, 0x22CBE1646B54A63AULL, 0xEB632C88DBD469BBULL, 
            0x7DE8C321445AA27FULL, 0x2B718D4D377F3127ULL, 0x6703294E17FD258AULL, 0x4B78233F22FCA09EULL, 
            0x36541469B1B649A0ULL, 0x44A2777D9002AA90ULL, 0x4119E1DFA466FB77ULL, 0x4B8DB4450477D7C0ULL, 
            0xA8CB94E7D7DD896BULL, 0xC71F70FDFA2061DFULL, 0xBE9ECE6DD8856B75ULL, 0x7BD5355E9730ED62ULL, 
            0x65561B1FB2DE3221ULL, 0x493077D39C2D25EAULL, 0x5706456C2630CCB5ULL, 0x5572B865408B4C8EULL, 
            0x878DE7421A1031E6ULL, 0x0595199498E655E3ULL, 0x6A6954277C4D9799ULL, 0xF2A1FA23F03D78A2ULL, 
            0x63301B226B5C3070ULL, 0x6225EB983794D5C0ULL, 0x7A139019207BCA2EULL, 0x5AA9A937FCF95B4CULL
        },
        {
            0x96A7E4B1A76F7D56ULL, 0xB4EBC82DCAC9052FULL, 0xE4E464B0F5F5708EULL, 0x599D6E8453526E1DULL, 
            0xAF3DE7566EF5C91EULL, 0x8BD426066120D8CFULL, 0x84F4CC9AB55EB452ULL, 0x85FED230977943BAULL, 
            0xA66A9D46FC745C47ULL, 0xFFABDCB436E8E3A4ULL, 0x24F1836B1522BBA1ULL, 0xF04DCE2A031874E2ULL, 
            0x08627503EF591EDAULL, 0x2330898B6D518B02ULL, 0x97FBA84008350B2FULL, 0x441E1D9378A87DC8ULL, 
            0x3F6832E6459054DFULL, 0x5F74124C503E3C8EULL, 0xBC540AE16B42E582ULL, 0x6AB73D2318F06921ULL, 
            0xFFEF608C8F363FBAULL, 0x69BB4870B6F83072ULL, 0x4FE7A37A48FD291CULL, 0x18081CD29A4E33AFULL, 
            0x52C2146C635A3DBEULL, 0x0C8E589BC245D4FFULL, 0x70CFA17F57F6C0BAULL, 0x97B29CFC345AD79FULL, 
            0x221EBF057E2A2961ULL, 0x88F786386B80A259ULL, 0xF38F1DEC27A6A283ULL, 0x31976BF3724BD3D6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseEConstants = {
    0xAE86CB4BB1311F3DULL,
    0x2400AAA1376EE91EULL,
    0xB20571DD27A63B0CULL,
    0xAE86CB4BB1311F3DULL,
    0x2400AAA1376EE91EULL,
    0xB20571DD27A63B0CULL,
    0x586E529B4E642C58ULL,
    0xF5FF90BCEEA6F703ULL,
    0xF1,
    0x70,
    0x88,
    0xFC,
    0x15,
    0xA4,
    0x44,
    0xFB
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseFSalts = {
    {
        {
            0x3AB601868B66E35EULL, 0xA7FA71DA17944A97ULL, 0xFD54791301CE4B31ULL, 0x1DC731A94A17EBA2ULL, 
            0x2281B1B7D5BC34C5ULL, 0xBAA522635569BB03ULL, 0xFB8EFBED7ED0FB09ULL, 0x75AF056F63C09C51ULL, 
            0xFE9873E89D835E2CULL, 0x3B49701E37EFD39EULL, 0x8AE99E1D6E1C0F4EULL, 0xF7D5F2ACB59C6F21ULL, 
            0xD9FAEE4CD9C48CCFULL, 0x37F5CB244E8EE98CULL, 0x8EB31672FF93911BULL, 0x398741F91F4ED9B9ULL, 
            0xBE5D53F0DDBA8B74ULL, 0xCF82C9BC2D8FF3BCULL, 0x51E74556ABD7E6E0ULL, 0x7811F280B7A75E47ULL, 
            0x086DC99E603544BAULL, 0x182A16B4EA3016DFULL, 0x08491ED720A210C8ULL, 0xCB0092DEE4509534ULL, 
            0xC7053CB4DE678D18ULL, 0xE17F81CCB7149A8FULL, 0x0DF7B67C04EF1539ULL, 0x6820C2C89EDE3A00ULL, 
            0x39FF6D31EBF10917ULL, 0x0DA99416A5BFC627ULL, 0xF7DA3601963531B0ULL, 0x994B805D69B67F48ULL
        },
        {
            0x242B037E9DE3FD15ULL, 0x0E8350106C6E4ACCULL, 0xA649324CC1BDB435ULL, 0x39F9B21726C871D6ULL, 
            0xBF38DF29882EE0CCULL, 0x65A7675F5ED6D624ULL, 0x6ED1F1A8D8C643E2ULL, 0xBC873D25C7307813ULL, 
            0x3C7C5D138DBAE498ULL, 0x7A6AF20FC580CA02ULL, 0xAE390B35C06C3EA8ULL, 0x2B67F107381D8130ULL, 
            0xE18929A28196365FULL, 0x0FF7A11B9CFD985FULL, 0xEA0BA55B3434E36AULL, 0x9D580EBB9C1C9BF2ULL, 
            0xE1BE8F23B6610D1AULL, 0x1D6ADCCF254CCBB4ULL, 0x91283B2EE02CD526ULL, 0x0A5CE81155EDC17CULL, 
            0x574EAAAD77126A4CULL, 0xE8D090A548238748ULL, 0x1CB7C1E7B99C02D0ULL, 0x956AA5EF1C339088ULL, 
            0x76E0822D6688E2DCULL, 0x101F3494DA235164ULL, 0x6D574F6377CCF593ULL, 0xD78AE693E7DE44D1ULL, 
            0x4EB266E487056CBEULL, 0xBD9024C489133D09ULL, 0xF2EA07CC45C33CF5ULL, 0xE07928F76B34250CULL
        },
        {
            0x3143921B1B6328B1ULL, 0x210CB6424F36B461ULL, 0xA86BE853BE60B8DEULL, 0x5A8EFBDAA6B48AA3ULL, 
            0xDC0796E11E7A0142ULL, 0xEFE2B05A4165FCEDULL, 0xC940E9C7FE206E4EULL, 0x1EB3367E2FF47B20ULL, 
            0x7A2E5EB0CBD6743EULL, 0x4D8F3322A7B868F5ULL, 0x6A7CEA225434D201ULL, 0x526B256EAD390926ULL, 
            0xDDCC551DF742E24DULL, 0xAA9ED57CA41D4CCBULL, 0x0C5116823C5A809DULL, 0xCE06C18DC453E31DULL, 
            0x997ECDA9059ACB00ULL, 0x408C8ECF974479F4ULL, 0x9B8B55396AF001FBULL, 0x242C668782828EEFULL, 
            0x585FE846F4A6DAAAULL, 0x08EF236B93753132ULL, 0x3F051D04C24236CBULL, 0x1E43B677AD43C86AULL, 
            0x1ACC25024740BDA3ULL, 0xAEE430809C12C5CAULL, 0x9F477DC84782823AULL, 0xC1FD90E7DC44BFE7ULL, 
            0xFB1817FDCFDAA7A0ULL, 0x0A0E52C14F51E8A5ULL, 0x40DE320E42685721ULL, 0x7D8D09F993A99885ULL
        },
        {
            0xC59BE14CCF253139ULL, 0xBC9B8F51588C3603ULL, 0xCF364CDC617065E6ULL, 0x7A85BEB55718236CULL, 
            0xFE803AA1EC7D550DULL, 0x8E2754D523A707BEULL, 0x1A31CDF2FCD74032ULL, 0x1A84B7B9EA9506CFULL, 
            0x58713348DEAF1C3BULL, 0xE932C50266D122EDULL, 0x6EEA838B3528D69FULL, 0xAFDD855F4916A162ULL, 
            0xC4AB5ABB6EB3D770ULL, 0x161C220D9E492807ULL, 0x9C9453B84B1B7B6AULL, 0xE3AFDDC996562B94ULL, 
            0xA289D5B9B04BD640ULL, 0xE39F76F432A57B48ULL, 0x5555A3C5555A33B8ULL, 0x1613DC5A5BE0CBB4ULL, 
            0x8CF64949DC9021A8ULL, 0x0E12CF50385CF02CULL, 0x7CFF9C207E3BD0B8ULL, 0xC4EEE0AA58E6F2DBULL, 
            0xF0D317FA957D9529ULL, 0xC8A52C3C1A63E8E6ULL, 0xC43593C11E697A5DULL, 0xDB86E96E0FE2A2FCULL, 
            0x3E12A431054255CAULL, 0xB19B8B62E2E03146ULL, 0x14902041A3544E23ULL, 0x2C6434EA785DB752ULL
        },
        {
            0x4F8B6742C5D0CACCULL, 0x91D4F53001BE5E63ULL, 0x920AF4445A156A5FULL, 0x54FFCF720D752FF5ULL, 
            0x98D3678B27F4AA48ULL, 0x6A2DEEE5B916FD25ULL, 0xD99E802B7860138EULL, 0x21856B60B7D4BA4AULL, 
            0xAEBC30A3700361C0ULL, 0xEA4302016D4107BCULL, 0xD53B79365C10553BULL, 0x8FB905253BA120BCULL, 
            0x1F468B5A2A97F993ULL, 0x0C7801AB8E369351ULL, 0x7C4E6B364510214CULL, 0xF45E6FE752B7F12CULL, 
            0xEAA904AAD6139CFCULL, 0x30B3FECA678AE7F9ULL, 0x445188472CB0AF59ULL, 0x9389B6A72126CEECULL, 
            0x43D72E098B02EE80ULL, 0xDC4DFCDF9DD9048FULL, 0x4AA1D4BB39FA1FA1ULL, 0x2DC522A0F0C824DBULL, 
            0x2C17DAC586E9DE1AULL, 0xC479C1D9CCE373F5ULL, 0x2F01DC7FCECE1519ULL, 0x22418D08674251ECULL, 
            0xA8233AD08FC9B236ULL, 0x5BA75BE323873C5BULL, 0x00F86E057838EC22ULL, 0x24E6EFBD6537DC4CULL
        },
        {
            0xF36C773E4FFB53ACULL, 0xDCC86447924D00ABULL, 0x8DB66F945036BECCULL, 0x598092D24CFCEE31ULL, 
            0x947690B8CE5C7793ULL, 0xF9B8BDE9A88494D1ULL, 0x728924149E4CE146ULL, 0x50A842B13DCB27CFULL, 
            0xA74D77F708B1B474ULL, 0x1E0DE8EAA25DBC12ULL, 0xB6B2F87980E242E6ULL, 0x0CF5F18FFF5C767AULL, 
            0x474F279175B14B43ULL, 0xB729F527E3F2111EULL, 0x9B4D908FD6883636ULL, 0x348C9A6D646A1E5AULL, 
            0xB4E05CE12B9D0411ULL, 0x158843F9CB2F0A93ULL, 0x0F5096EBF50A5F3BULL, 0x545248FBE6C678E2ULL, 
            0x722190F3B4628A05ULL, 0x613E72C8A36AD9B2ULL, 0x779A8F0B4C7B3DF6ULL, 0xB8043B1640075A34ULL, 
            0x8022C7690ECC1373ULL, 0xC32053103AD5FBC6ULL, 0x6758595AD17E3810ULL, 0x8C8F1E5E40CE3594ULL, 
            0xCD3DC8778CB60BA9ULL, 0x4F014FB1FE865737ULL, 0xCE5FABD8B62273C1ULL, 0x163268AC960CFFF6ULL
        }
    },
    {
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
            0x0B48C6436A1DB91FULL, 0x20137A5718549ACCULL, 0xAF75C37FBC5B4050ULL, 0x9F417455F7A46079ULL, 
            0x62E18E042FE9F584ULL, 0x5D9996B10EF304B6ULL, 0xEC9C83FA661FE047ULL, 0x0839EA5908E0F2BDULL, 
            0x3B687DCB978603C6ULL, 0x4683F782B2AE2FC1ULL, 0x8461E0C749F4DB3DULL, 0x2B3E952D9A12FE03ULL, 
            0xBEBFAE5F0649424FULL, 0x65313CDA55FC45B6ULL, 0x930D714B0D61AAB8ULL, 0xFF61681BF479C7A4ULL, 
            0x191889ABB100A1CFULL, 0x49B340B7BA73F171ULL, 0x877BF09507DA71D6ULL, 0x7021E24FB02CAD49ULL, 
            0x70C269ADD5263958ULL, 0x6AA57DAE3EADFF1EULL, 0xE7C164BEE6E40690ULL, 0x1BD05A10AFF8142DULL, 
            0x5113A9B150A1BDEBULL, 0x81F3AF477452355FULL, 0x5D1A9441536AF124ULL, 0x287139D227B3F659ULL, 
            0xE7D17612661EFFA0ULL, 0x3F7530FB50F4F4BBULL, 0x82CE0F73D9A48E71ULL, 0x059B215621F03F67ULL
        },
        {
            0x165072AA0F25B57EULL, 0x800EFECD8FB11BA9ULL, 0xE9AB1841AEDF1313ULL, 0x0B32D8237EA37E90ULL, 
            0x33F9FA12AFEFB340ULL, 0x2023B901C0BAA84DULL, 0xBAF37142AA7F063DULL, 0x8855E3FAACA36E6AULL, 
            0x2E59205020769958ULL, 0xC6624B4215C919A5ULL, 0x10294D2047BE39B7ULL, 0xB2BE45FB16A40827ULL, 
            0xAFE610F8CF59A9DCULL, 0x0A247CECBF3813ACULL, 0x53146D32788599C1ULL, 0xF819E87AD35CC8CDULL, 
            0xE60AB907CA2EA609ULL, 0x3742F0A7DE31C81CULL, 0xF207A0956507E1E0ULL, 0xA280F6E902E9EFF4ULL, 
            0x8F90ABD3FC9F29A4ULL, 0xB46A3220C0840F6DULL, 0x52B5A4B6BF49EFDDULL, 0xB2EEE013BCE12EC9ULL, 
            0xDC2EBBEA05E5C1FFULL, 0x1649A3C6F29E2CD6ULL, 0x0D7DEBC0B1BD8E80ULL, 0x5932D49CDB54012AULL, 
            0xFCF2DAE0E604363CULL, 0xB3B05259003F56BAULL, 0xBD8B9DF456997B00ULL, 0xF7B2FAC36DF16546ULL
        },
        {
            0xFCF0291F508F8F34ULL, 0x4B333612F782DB03ULL, 0x267B3044818A9062ULL, 0x2FD258D00BFC4AA3ULL, 
            0x55D6B36F1FE01271ULL, 0xE4064615DB871619ULL, 0x251EA53655E9446DULL, 0xDA9A675DC0A0396CULL, 
            0xE65FD2A2CFAFBF5FULL, 0x683F7E18BAA18533ULL, 0xE48909AAE5166F25ULL, 0xE13FBFA66928E9EFULL, 
            0xFC87AD02AB754D17ULL, 0xC364501B4EEFAC99ULL, 0x58F111BEDC4B3A4EULL, 0x106F4F03494A0721ULL, 
            0xD2CE46D36E10CFE0ULL, 0x5F630645E199FB43ULL, 0x48E9413E97D986B6ULL, 0x2FE74B1E38CFBC01ULL, 
            0x443F6430BDC958C7ULL, 0xD58A4326AFC83271ULL, 0x6A74ED3165AE89C5ULL, 0x3D568E9FE95AD07BULL, 
            0xF0145C5E4667E17DULL, 0xBB45C170FF272D7DULL, 0xC755B1DEBF7BB24CULL, 0x75BA2C4C1DA6ED42ULL, 
            0xB7647EE2C698FDCAULL, 0xBADD683CC6FF2007ULL, 0x0E67859EFF66BAE6ULL, 0x347D3B43B7D7C5EEULL
        },
        {
            0xA4A8B3B8780CC4FAULL, 0x3A79C54C1E50C152ULL, 0x82C903A5A2FBCD7BULL, 0xAB9E1522B0EBB8F4ULL, 
            0x156D454FD338CF65ULL, 0x6377235F823ED922ULL, 0xECB6EA68DF538FE1ULL, 0x77DA17A856C7EC7DULL, 
            0x9E2C436653393099ULL, 0x753812F69684B2AFULL, 0xC2A51981C499FE9DULL, 0xF13C9D7EB9D96F9BULL, 
            0x4F6F5C2DB61380EDULL, 0x8CC31A2A31D25F32ULL, 0x6E5C605AD1AC5448ULL, 0xFDAA68A68D15FD5AULL, 
            0x4FB51FE08A920C44ULL, 0x9CB558313B736695ULL, 0xCD1269E998DEC95DULL, 0xBACF0A6AB0B57F01ULL, 
            0xC6AFEB9356F628BDULL, 0x6BF73774FA481E6DULL, 0x4967781B88D49FC5ULL, 0xE21055E925C222EDULL, 
            0x42F516FAA034562CULL, 0x856C90E9BD89DE0BULL, 0xB000C404BC57EBD9ULL, 0x46EDA849FB27E978ULL, 
            0x1D5657DD417F1559ULL, 0x79690ADA4EFBBBF3ULL, 0xA973556B0612279CULL, 0x7E0066E482137EB7ULL
        },
        {
            0x7FE366F6923ED8A8ULL, 0x7107DC5EA3B5ADE4ULL, 0x93EDE87693D6C6D8ULL, 0xDB4C9452C8D0EE88ULL, 
            0xBB90591BF258A97CULL, 0xC26622FF62D19EC9ULL, 0xFB0CACCE6436F661ULL, 0x2572EA152AE0AD9DULL, 
            0xCF506451D03DAD03ULL, 0xB39DEF86F8C99B29ULL, 0xA2147FA8F89AEB37ULL, 0x71B8F3D97B04FF7EULL, 
            0x712CA58A0B4AF629ULL, 0x383570C7F79C6B6CULL, 0x763FFB242704F17CULL, 0xDCB916EF143F8853ULL, 
            0x7F6CAE83D36C2FDCULL, 0xEC48BE7599CC80A8ULL, 0xC924C45793688BCAULL, 0x5BB3B9EB597A7D29ULL, 
            0xB9A9685662063DECULL, 0xB2095F6B2D51DF76ULL, 0x41EC05BF788C5B08ULL, 0xEDEF092CC78387A9ULL, 
            0x30B8581F542E5532ULL, 0x49380C05F76A42BCULL, 0x9B14B18E43EB4044ULL, 0x2F263E2C43491C0DULL, 
            0xB477D0F680426DF9ULL, 0x3F3412451E1CC5CCULL, 0xCA7DB16E02F483B7ULL, 0xE304D3331691BB2DULL
        }
    },
    {
        {
            0x529932BFC91CF95FULL, 0x4089EAA9E054C943ULL, 0xD64967AF8042C688ULL, 0x869B766DA88943CDULL, 
            0x0838169375695624ULL, 0xCF4B4A8E004CB6E1ULL, 0xB53A27E6695C3BB2ULL, 0x3B7E8615593D7E13ULL, 
            0xC4C02506A3640C2CULL, 0x8F64E1B263FE7965ULL, 0x5A583B04B3AB3EF8ULL, 0xD9BFB89AC597C107ULL, 
            0x56A9CB559BF3DCF9ULL, 0x20555B85809870ECULL, 0x4665B23893E58409ULL, 0xB3A2130BC695472FULL, 
            0xC95C96F78AE1127AULL, 0x19061A860A016496ULL, 0xD611E92BED1CFA5BULL, 0x8075098BBD0C2822ULL, 
            0xFB7C4AFA00271E11ULL, 0xBB94B02123CA7DF4ULL, 0xAA5E794F1761BF7FULL, 0x39C321386A675539ULL, 
            0x42089374303D3C82ULL, 0x5DCEA11F25DF1C64ULL, 0xD492432CAE6DB95CULL, 0xA24DF72112B44C6DULL, 
            0xA9F2D00174C84DA4ULL, 0x2422284834102FBFULL, 0xA167720E48C76535ULL, 0x27E98AB7835D30E8ULL
        },
        {
            0x8F7451445AA3E71DULL, 0x06973DC9A0EB323AULL, 0x6C2586C846C96C18ULL, 0xE387AB1CEB6569FFULL, 
            0x3BB7505B7683B707ULL, 0x8C2E1B4C43F9982BULL, 0x2A838CC74D3998A5ULL, 0xE92A1A43843C286FULL, 
            0x98A2F0059AC4AFA9ULL, 0x85056755DCA2B39FULL, 0x36C483603865C13AULL, 0x037721FECC82464EULL, 
            0x9EDFEE02E01F29CEULL, 0x92335D47E4100586ULL, 0xB5E97D24B1AA9085ULL, 0x580E464E65AF64C3ULL, 
            0x03C0EEE36EE90D41ULL, 0x54B1CA03F86B8974ULL, 0x0BAF4020946DBCF9ULL, 0x4D4903CD5E72DD9AULL, 
            0x29D9EBF769F676D0ULL, 0xDC54F8A6333FED6CULL, 0xA263C4F209C7D687ULL, 0x75B2B0F66F22E573ULL, 
            0x1F4614A4F6405C62ULL, 0xE6A0BBE0EBC3C10EULL, 0x7841A95B8246161BULL, 0x429448E2C06D64A5ULL, 
            0xBBAE01BFF886EEC8ULL, 0x42331A641262D209ULL, 0x975EF1A4F8B953C9ULL, 0xE5B218D6B1E40877ULL
        },
        {
            0x7D3C8FE74C1CBE74ULL, 0xAAA102DD45834EE9ULL, 0xFF01E90CE2C28601ULL, 0x4B1901B02E624947ULL, 
            0x125C4615C2A2DDA8ULL, 0x1ED4BA64B07ECB81ULL, 0x2605CB7D4BCAC1B3ULL, 0xE42D7C51FB9A131BULL, 
            0xF02A604BB37F5638ULL, 0xE1F8A0B874CD5C37ULL, 0x550293A4DA95F116ULL, 0xA46F8CA16DFE11C5ULL, 
            0xD9352E065CEC3E04ULL, 0x457124B1C303E7CCULL, 0x737E884A2636D01FULL, 0x7E25B1990B036C73ULL, 
            0xBEB741BDFB85F640ULL, 0xA92464086C6673A2ULL, 0xEF49075A850F4FC8ULL, 0x69927A73F22744A4ULL, 
            0xE93BE9EA7C00E53EULL, 0x3845537972026239ULL, 0xF2BA18B7F7943DB3ULL, 0x3E947A2CAD593BC0ULL, 
            0x9995C03C55DD8803ULL, 0xA0002CC8910014FBULL, 0xE1A9D16E16E87884ULL, 0x0C6DCAECDF22BC98ULL, 
            0x828C3E3E80B510D0ULL, 0xD179893422F41D34ULL, 0x8B06C0D172315292ULL, 0xE455E848079BF508ULL
        },
        {
            0x59F2E67530849F09ULL, 0xFAE9618F3763C57CULL, 0x1919A15158497D01ULL, 0x08E67B4FA52CBC94ULL, 
            0x6336E6DA148E3917ULL, 0x786FE53EA5FC846FULL, 0x090821EE4550BB3DULL, 0xF8FFB746B3A1F9ABULL, 
            0x69B8783B1DACCBD3ULL, 0x3B8D00B92CB35C8AULL, 0xFA44429BA1B610E5ULL, 0x113C8A30B5924E42ULL, 
            0xA8FDE679669771BAULL, 0x16052A054CFBFCCFULL, 0x8061EE4434F7FB6EULL, 0xC33D5A00A9C53EC8ULL, 
            0x9B7FEF86C9455E77ULL, 0xF073ECA3E6B19BEBULL, 0xD2147EECF450DC9CULL, 0x436B234256AA785EULL, 
            0x3652E15F30699365ULL, 0x1276C78C04924F39ULL, 0xDD585344D6943523ULL, 0x2726187E3459BF63ULL, 
            0x70A4E0F705C56AA0ULL, 0x30829B2FBD33B757ULL, 0x1EB055E6671890EBULL, 0x99EBF583BB3FD383ULL, 
            0xACB0F86737AE8D89ULL, 0x25C59D7D0A4E1367ULL, 0xC5FD154DAFCFF652ULL, 0x90BAAF758FF6E1B7ULL
        },
        {
            0x9391497D2788A046ULL, 0xA2CFECD33339A25EULL, 0x2CD50581367CA92BULL, 0x11CC096CF490F3D6ULL, 
            0xCF73373B9C17BA28ULL, 0xC9ED003C74E50B67ULL, 0xFB48703BB1DFBB87ULL, 0x813443BB1DC5B5C6ULL, 
            0x9BDC9E6988BA2A83ULL, 0xA22462CF8C90EE8DULL, 0x1F9D47AEE2F5DED3ULL, 0x182266EFF86163C6ULL, 
            0xBDD8B12EDB339686ULL, 0xE091C43025C8A14BULL, 0x4455264603497B3EULL, 0x76A7258E192F5146ULL, 
            0xD961F7457A59551DULL, 0x7D9AC5CDC591E68DULL, 0x497BF165131E2394ULL, 0x40CE0E78926D6838ULL, 
            0xAB87E5540C1EE4C0ULL, 0xBAB71A0A03BF0419ULL, 0x11D3DF8625336C11ULL, 0x89B08D64F7C20057ULL, 
            0xDF419855FBE343E5ULL, 0x358AD690EC3D4D69ULL, 0x3B28A77E2B6169FCULL, 0xD8F159992954A216ULL, 
            0x159138D7FFDB2E8AULL, 0x9EBA1941F42C2D18ULL, 0x247D21A0367485B9ULL, 0xB9ED6A66848700B5ULL
        },
        {
            0xB9E7F1B464F0C95BULL, 0x8B3A1860083B77D8ULL, 0xE03FF123F6B2AAFFULL, 0x56AC9C8DFD5DC899ULL, 
            0x225BC3E8F59BAA35ULL, 0x4E0B62FA137B4618ULL, 0x07C12FF7037E2E8EULL, 0xF1DBA0C7B0272028ULL, 
            0xD3338C456F7FCA7EULL, 0xBAA2A476D592E005ULL, 0xE91888F547DD0DA9ULL, 0xA145331E58C9C6BEULL, 
            0x0E2FE2E8C5C89F26ULL, 0xE3B9653488014D66ULL, 0x993B02CBC7D7FBA8ULL, 0xBD229F2DA481B683ULL, 
            0x59F0C739207BEDF0ULL, 0x635F5559B39720CDULL, 0xC77F8BDFBA9BA349ULL, 0x4DD9D0080832C256ULL, 
            0x8F89397D32198F4FULL, 0x3FE27119899F38C4ULL, 0x7306D2F8DC17EAB0ULL, 0x2624C72B622388A0ULL, 
            0x2E7CB12F61BB41D2ULL, 0x822EFB7910DD2795ULL, 0xF5D74FDC949CB3F0ULL, 0xF12139F38D4138ABULL, 
            0x32EAB109A3E65AB8ULL, 0x6B4009C0BC4BDCE9ULL, 0x3006512C859B6305ULL, 0x574E5FD1AB93C82FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseFConstants = {
    0x2257C40F4E0E6961ULL,
    0x01B2B964BFA7B271ULL,
    0x40DBEDF927415861ULL,
    0x2257C40F4E0E6961ULL,
    0x01B2B964BFA7B271ULL,
    0x40DBEDF927415861ULL,
    0xB0562E839662140FULL,
    0xA551CF294E249F59ULL,
    0x33,
    0xD7,
    0x44,
    0x21,
    0x38,
    0x97,
    0x6F,
    0x07
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseGSalts = {
    {
        {
            0x0B77153FAF405243ULL, 0xE4B343C2A51EABF0ULL, 0x1F36F8E812B227A1ULL, 0x554BAE49BA0EC374ULL, 
            0x74FF4F0C6B75587CULL, 0x1C98FAF89C4C8249ULL, 0x102B7BD7CD009C0CULL, 0x317464F4CFDA24F2ULL, 
            0x775030452DE4D2F3ULL, 0xAA6DB21821A2C62DULL, 0x9CE74A71BCD39845ULL, 0xD0FA30229DC0B24BULL, 
            0x710061028695CBF9ULL, 0xEA30DEE4484BA756ULL, 0x4066B28E265EDB12ULL, 0x97C69DEC2C11C65AULL, 
            0x9C2830A17C1E2734ULL, 0x0F49D7BFFC3FD6B9ULL, 0x7B424876A0AABFA1ULL, 0x105CABAA6AC32802ULL, 
            0x0DD363B023F4811AULL, 0x1A5DC6E5149816E4ULL, 0xA027A9703224D890ULL, 0x395D67C79A731A40ULL, 
            0x0118698BA62ABFABULL, 0x11CC4B4AC6B6D2B4ULL, 0xF0EFD881C5E1C98FULL, 0xFD8D7E705F9606D4ULL, 
            0xE440E8EECBAC352CULL, 0x199CD083AA9C69A2ULL, 0xA7F8082DC0470686ULL, 0x3C698EED55D062C3ULL
        },
        {
            0x4F091EB8FE3FD882ULL, 0x2003C44EBF36BAB2ULL, 0xE32B0301FE2FF2ECULL, 0x2386EDADD53B442FULL, 
            0x17D01367047D9CAAULL, 0x9A630CFB458DA4DFULL, 0xCAC6F35C7F172CD9ULL, 0x4AA6FECEAE84BFC6ULL, 
            0xC7E61F59F555ED57ULL, 0xE7A271CCC0A3C0A3ULL, 0xC91EC49C9792FD5AULL, 0x4CD6229370EAA72CULL, 
            0x741CFD1D2180646DULL, 0x73E874B2308C2E2FULL, 0xCCAA09A2DB1B75DAULL, 0xE8A199AF6EAC24D5ULL, 
            0x38A5AF18C5193501ULL, 0xEE7D4859330C6B30ULL, 0x64E8D2A11DB5C615ULL, 0x1794296E593C0FE7ULL, 
            0x9F4033B0DBB0DCB5ULL, 0xDCAC0757B8A42597ULL, 0xBE488651A497C45FULL, 0x1ED2A82443D2927EULL, 
            0x851A691D58451D9DULL, 0x4A67C2A497D83F40ULL, 0x55F935F446553335ULL, 0x711CCCD70C57B182ULL, 
            0xF6DABDD9CF608002ULL, 0x1C100589E26D7B1CULL, 0xD1EDB69308D98E51ULL, 0x6F92E56F24376197ULL
        },
        {
            0x2CC0887D111968CCULL, 0x800A0477827F6A1BULL, 0xDEE6AD7D13367C0EULL, 0xE2775C01602C60F1ULL, 
            0x54BE07BA9B86257BULL, 0x3FA3603D2CB37999ULL, 0xFDDDB7AD480253CCULL, 0x2E47DBBBDA44D944ULL, 
            0xD32F37ED6931FFCAULL, 0xB137EB7EE98C82C5ULL, 0x7DA4756F06D3D828ULL, 0x7B19CAF589A66C00ULL, 
            0xC531EB08E1516C9AULL, 0xF538232E732D5E1EULL, 0x675517EC4CE7F6AFULL, 0x06CCC8860D7ABB3BULL, 
            0xE39100EB45AC6441ULL, 0xF73CAE547482D46CULL, 0x00B0CA2F186DD59BULL, 0x59413B2C8DDD6911ULL, 
            0x61D8F067F2AE9EFEULL, 0x7BFC82243B0668DCULL, 0x48DD5396BE743DCAULL, 0x24F94C322E19CB30ULL, 
            0xCDC4E252E4DF8B0BULL, 0x0A672192344DE4BBULL, 0xB43831ACC44115ADULL, 0xCBF4BF81295190DDULL, 
            0xF58CE5ED658BB984ULL, 0x1CAA2E1DC1534210ULL, 0xA430DF0E1694793DULL, 0xB0A998E4F82A4C34ULL
        },
        {
            0x8BD505676ECE56F3ULL, 0x43A13741220AE295ULL, 0xA45F46686D0228E8ULL, 0xCE04387E92A76FE6ULL, 
            0xE4B8A28257E4550EULL, 0x3E71D085FB2D1D6BULL, 0x13CFE9FE627D9E04ULL, 0x56724F9F50DDA1CDULL, 
            0x25A571B4B388F808ULL, 0x8149EFF33984C0DCULL, 0x3A94A678F0551446ULL, 0x59CC3575327C5BB2ULL, 
            0xFC08E47F44218662ULL, 0x676B98AAC9FBEE23ULL, 0xFE6531EC3E25E759ULL, 0x897CCE4E41A41952ULL, 
            0x78EFC2BD6431855EULL, 0x2DDA327682473D22ULL, 0x3502EA1136CBF38AULL, 0x9CA3021AB5316B8EULL, 
            0xE482663CA5868F28ULL, 0x0A1EACBB3DD185A1ULL, 0x304CBC649920A037ULL, 0x025A287A3B6BBF4BULL, 
            0xECF15F0793F9D308ULL, 0x5620631FF2027582ULL, 0x40AE2CD114A67D04ULL, 0x4CD7B72D74C8ABF1ULL, 
            0xCB23072685F8CD4BULL, 0x598680B911CDE176ULL, 0x6A8375103CBD73C9ULL, 0x62AF7D7C9EB8525FULL
        },
        {
            0x1DC50B631DE38BAAULL, 0xC2C3682A44262CB1ULL, 0xC33BBCD55BE029D6ULL, 0x3DB4182F776D6606ULL, 
            0x722AB4DAF4798FF7ULL, 0xFE0CAC2DE3918B64ULL, 0x3D7BFC5E9C735D5CULL, 0xC87AD18D630927C8ULL, 
            0x9833AE48952ACB0CULL, 0xF4447BE350741289ULL, 0x9F78158DC234EC17ULL, 0x505FD707C91D2FE7ULL, 
            0xB0DC90B3750C5103ULL, 0x1532EE6764C4C235ULL, 0x44EAB771828D448CULL, 0xD47AEA1A64157A2BULL, 
            0xBBAB39EBE1EAC070ULL, 0x2D7A48DC98C2ECECULL, 0xC90009586E1F2A5FULL, 0x1F6F7810446409A6ULL, 
            0x22C70988D3B54015ULL, 0x5CE53E7250D35152ULL, 0xA39B7049D2F4F67FULL, 0xCA205F0DF509FC85ULL, 
            0x3DDCEE389DD0AA84ULL, 0xC55C1F1E2F05BC99ULL, 0x8B7A77D26297D707ULL, 0x92C3459C71C81ACCULL, 
            0x09EB241EE3C07852ULL, 0x7DD56D580C98BFEBULL, 0x3FAA8213E1C57366ULL, 0xD95FFC6BA8407759ULL
        },
        {
            0xFCD45D52F2AEB2D4ULL, 0x0397D7A1F3CDCA91ULL, 0xAC5C8AC3B46032EBULL, 0x6DDFF726CBAE8B71ULL, 
            0xE8B845F8C9A65F96ULL, 0x728169984DB5452EULL, 0xA4AC38D395EBA79FULL, 0x1BEA0D522E9D82D8ULL, 
            0x051A08C42CCE2880ULL, 0xD0EFBCBEF75E0750ULL, 0x11938395D1EFA1F2ULL, 0x42D2C5322FC8C5EFULL, 
            0x0D74C117544F83C6ULL, 0x7E585322679BE849ULL, 0x4378726F6AEE32F5ULL, 0xF045C163AE717DFAULL, 
            0xAE7157FE40A759A3ULL, 0xFD7E8CAF5360FD97ULL, 0xA9A907BE78B02764ULL, 0xB78566F94060A074ULL, 
            0x63AF85E5FA1A1500ULL, 0x90D91742C46600A7ULL, 0xF0EAF6A96612D77FULL, 0xDA054E92C94C4CFFULL, 
            0xC1ECA5ACAE77DFD4ULL, 0xD9FAB24DC1A1A447ULL, 0x9EBF87EC691BF16CULL, 0x0483EFB64B11009DULL, 
            0x3A87673A68EEC5CBULL, 0xF5EAD16527F1FE37ULL, 0x344C7052D039A8FEULL, 0x9C3BB7C452440D38ULL
        }
    },
    {
        {
            0x7CD0D4D7BE3781D9ULL, 0x3E0FA873070B53FBULL, 0x85269BFA81080089ULL, 0x8AA1442481BB6308ULL, 
            0x2F7B7C04E39A8241ULL, 0x7907FA9CC883E40EULL, 0xF9C9B4623A6F2224ULL, 0x05CB46158CF7F158ULL, 
            0x795777060CC765D7ULL, 0xDC563203AEE8840DULL, 0xDF9F6C0C5E7D4C69ULL, 0x157D3097CC49D602ULL, 
            0x70770B49E2D12064ULL, 0x729CC5079118BDD1ULL, 0xAAC527FE6B79EB44ULL, 0x746EA859A91A15DFULL, 
            0xD2C28B77E5148F86ULL, 0xCCC4C5327F9693ACULL, 0xA375417559E1B880ULL, 0xEC8D66821F2E23FDULL, 
            0x572C4E8590C818CCULL, 0x040CD157F2913043ULL, 0x8218512A6642319AULL, 0xB697F58E521660D9ULL, 
            0xF602CC80254FEC6BULL, 0xD31832F776BAF170ULL, 0xB8B919986C7A38CBULL, 0x0F25007E239D4DCFULL, 
            0xD10E6870DBEDC0CDULL, 0x8AC4975ECC25B423ULL, 0x96CDAE46D030F49DULL, 0x57195087713A9359ULL
        },
        {
            0xEA5920BF0F329FC7ULL, 0xEC2D77F3C616D598ULL, 0xE47D9ED199A8E934ULL, 0xB9C2210B83D037D9ULL, 
            0xE91EB4647A3223A6ULL, 0x99F1152712042209ULL, 0x3DA9C3674449DBCBULL, 0x134CC6F3F203E169ULL, 
            0xA96C23B10DC24056ULL, 0x472438C1D7A35244ULL, 0x2A56DE7D679A3BB7ULL, 0x4317E6973D4EC907ULL, 
            0xD01A210308410D2BULL, 0x7CEF321AAC2CC487ULL, 0x70E826BBD12CBBD9ULL, 0xB34EA2F9D0CA67F4ULL, 
            0xE5EE0240F05E29F0ULL, 0xD94BFB970DF0013FULL, 0x35888DDBC2C4D50BULL, 0xB19527857728F7A8ULL, 
            0xC18C53EC290F6AD1ULL, 0xBC62CAF911ACB743ULL, 0x209639D2A3023E3DULL, 0xF355D57F4DBCD9BCULL, 
            0xD88C09E2ACF5C193ULL, 0x15C4AD148A5029DDULL, 0xAE4F9D78DB9308DFULL, 0x2CC46765218070CBULL, 
            0x56D14FBBE8425BCDULL, 0x33EAA9A82A955274ULL, 0xD4D7193020A8D597ULL, 0x75374761D1E038E4ULL
        },
        {
            0x4650EA9B5DDA2BE8ULL, 0x3318863BC668947BULL, 0x1A9FC2F03D4CAFE5ULL, 0x45684C64F21D8C6DULL, 
            0xDFBC81AEEA744139ULL, 0x87AD2DCC5C2D51EEULL, 0xD0FC48643A038E5EULL, 0x3589FDA063707F03ULL, 
            0xD6A93881AD5CFCFCULL, 0x1D459CDE19C9CB6FULL, 0x92DFF33D304D01FFULL, 0xAFED15ED5F241973ULL, 
            0x3EBCC850E3ECA834ULL, 0x00A744BFA4AD32DEULL, 0x8DA505D391F24063ULL, 0x843F09F54D2B544BULL, 
            0x1746469CF89FDC7EULL, 0x056312A7DC35064BULL, 0x3BECA8598F2257EEULL, 0x258E59EB735FBA92ULL, 
            0x43E3FDBB81B38A65ULL, 0xC0BBEBE004D586E5ULL, 0xCB3496FBC0D1DF16ULL, 0x0A6E8CB34955FD66ULL, 
            0x1ACFA7897447F686ULL, 0x119DC6FE2871882BULL, 0x1EE203A5BCC3D089ULL, 0xBA5B732D9E2875CCULL, 
            0xD910F7E9F5625B1DULL, 0x490EB9CA3AA990BCULL, 0xF54097B4F7A4729EULL, 0x643582F591DA0A93ULL
        },
        {
            0x98E0CF24650E3179ULL, 0xA33E891F3ACAD626ULL, 0x3EB1197CDAC5512EULL, 0x1E5387C0BEAADAD9ULL, 
            0x05998FD340EE5AA6ULL, 0xE8D371177ABE66C7ULL, 0x28ED1ECCF40833A4ULL, 0x75B5EE182BF606A3ULL, 
            0x5D0868816FD65FDDULL, 0x6C1E3B92E3101DABULL, 0xEE2F98BD967864EAULL, 0xE4D5616DF6823454ULL, 
            0x128EE0B482FA48A2ULL, 0x279A6AD4A1D42D1CULL, 0x5028ECE94D5DC158ULL, 0x44D61E4968FFF50EULL, 
            0x61B8E40F0B9FA348ULL, 0xC1E4102B956292C7ULL, 0x9184B00F1370B992ULL, 0x7F48AED90ABA00D8ULL, 
            0xF0765C2B55F2DA21ULL, 0x10C61836BB51074AULL, 0xE3D6A89B32DB307BULL, 0xBC706C02A6D0CA28ULL, 
            0x8B59AD4CFE9A04ACULL, 0xD49E829043CAA0EEULL, 0x80D28275C4E15153ULL, 0xA061E1DAC028C89EULL, 
            0xCDC0387B7989CB17ULL, 0x60935EB2489E4B07ULL, 0x38C358C62B565D9FULL, 0x813DDAE369FEEFD2ULL
        },
        {
            0x2D746D9B95769726ULL, 0x1D4EC23F7A4E325CULL, 0x11ED154EBA64E2DFULL, 0x11D1C537A7C55DC6ULL, 
            0x9FD14E8B6910F1D0ULL, 0x34B18996EDD1B176ULL, 0x9F9F618EA4EE30E8ULL, 0x4BF816AE92BFA694ULL, 
            0x4DE162E124175FD9ULL, 0x669F4C1065D24381ULL, 0xFA5916C08BA90BD7ULL, 0x6D2AF9BCE764D148ULL, 
            0xCEA73D38A69E70E3ULL, 0x479EC0263EA049BEULL, 0x92711E44FE20FF9DULL, 0xD2F6E0868D7E6D8DULL, 
            0x3DF72D7BCF8E5F22ULL, 0x09375A523809A5F8ULL, 0x823841AFE782A07CULL, 0xF68D24EF691A1737ULL, 
            0xC6A743B4512390B1ULL, 0xF9200CCC1ACAA245ULL, 0x307FF8A740945137ULL, 0x09BCD61A651D8EF2ULL, 
            0x82393F1EC0AE6C8EULL, 0x073DBFB1CCCE4E2CULL, 0x463F26D5C0CE109AULL, 0xAA58610C217AFD28ULL, 
            0xCDE095D35CC28ABDULL, 0x4BF63AC2CDA69255ULL, 0x931487F9E6EF0148ULL, 0xE1F195F81D61A2EFULL
        },
        {
            0x3DB1967008833651ULL, 0x8BE66780ABBD1F2BULL, 0x84B2CCFAD663D109ULL, 0x9692A36C4FCD056CULL, 
            0x35F4102FE3E8C92FULL, 0x09B802810AF3C8B5ULL, 0x0F072B5428219AE5ULL, 0x1AC7B00ADF764EA3ULL, 
            0x3883C41780C34706ULL, 0xCBC14F14AA61A3F6ULL, 0xDE79BEB673C503CEULL, 0xC681AEE6F57A8205ULL, 
            0x6B14653939A08A08ULL, 0x11ABA5BBA2ADB529ULL, 0x8F1F4BD81AE04AC1ULL, 0x6F9D67E0655E1D38ULL, 
            0xA529A4B723A54CADULL, 0x46B313E826F5AFF3ULL, 0x84AE16EE1F46D4BDULL, 0xD9920925F095E75FULL, 
            0xF275B0BF48E331A8ULL, 0x26F6CC4B15FE9F61ULL, 0x340CB0AC06F25944ULL, 0x6421517EE2563FBDULL, 
            0x10ED14CD746F17CBULL, 0x72ACFF9A47B862BEULL, 0xA7A8FACD06936351ULL, 0xF4CAA0DC64A6223CULL, 
            0x069B7C6EEC3DBE3FULL, 0x89DF9050DCFBB09EULL, 0x6520A443E004963BULL, 0xB88EFDA0A808E82AULL
        }
    },
    {
        {
            0xD4E1B1E87C090C6CULL, 0x420C66FF95F236DFULL, 0xB09103407D7AF990ULL, 0x4B9793E67C3AAFB2ULL, 
            0x6B7D9DA29B615930ULL, 0x1139E855724236CCULL, 0xF9EC06BF0FC8E288ULL, 0x6DC1CEBC3DA9597FULL, 
            0x8920573C13C04102ULL, 0x0CC2DA313B7C4BBBULL, 0x60DC094CA35512F3ULL, 0x7F0D19FFEE81D4C7ULL, 
            0x8CF680390A9E66ADULL, 0x449E4E70F7789EDBULL, 0x57BCA4583BE26988ULL, 0x5BCA087691BA3DB5ULL, 
            0x9DF04546947EB95CULL, 0x14E78CB299B4FBC1ULL, 0x76F19048DA07848BULL, 0x9223B15356BBDBE5ULL, 
            0xF524756BB029A55CULL, 0x836094696D23467DULL, 0x2042888E6CDC4715ULL, 0xA4EFD45CF2D2604AULL, 
            0x8244271DDD77C2B5ULL, 0x77A3A7AA228DF254ULL, 0x36DD5C04BC10DEB6ULL, 0x1F35933FE82BA843ULL, 
            0x4A2AB6FF731289FCULL, 0xAD42F7A235EA0F4EULL, 0x5D98B5560EC5BCDEULL, 0xE201454E9D7AB85EULL
        },
        {
            0x32D977FC898CDD19ULL, 0xDC4FA4E57ABC3D83ULL, 0x79840C13E4F82B45ULL, 0x0626FD4F31BC17DDULL, 
            0xBA1C9FF41FBCE34AULL, 0xB8654C3508FD6D6AULL, 0xEB002D089C723BEDULL, 0x16F72DA931973C4BULL, 
            0x91C9C6EB2B958BDEULL, 0x5C729BB1188A5D39ULL, 0xE57BA3F5274A69FBULL, 0xDFBDA172E0C09595ULL, 
            0xDCF9B369BFE18B69ULL, 0x24DAB5EC2EBECEB0ULL, 0x413B27D86514F9C9ULL, 0x2DF1213173201CD0ULL, 
            0x1A853C0CDE56C2D3ULL, 0x2616B4C89DC7D290ULL, 0x580983E3C1734142ULL, 0x825FD9DC88C42ADAULL, 
            0xA1C9A05CB9B8636BULL, 0x6AE96B6E4EA57488ULL, 0x0FB9388778D5D739ULL, 0xF4005FBF24A0D266ULL, 
            0xABCF91A1D4D2D7DEULL, 0x3EB4B3CB52AB1F9CULL, 0x05892886716390ECULL, 0x194BBB2289950470ULL, 
            0x828A138EF497A249ULL, 0x69DD642D28171DBCULL, 0x6590485750C91C1FULL, 0xDBCEEA9750634B84ULL
        },
        {
            0x1A2F8A424F2B0B10ULL, 0x11A653CDA199B254ULL, 0xF37CDFCABA26AC2FULL, 0x2F1E6BE98CF228F2ULL, 
            0x9400EF5147429F6AULL, 0xA1630935BEC1432CULL, 0x5D47B32471C1282BULL, 0x99F965CA9912BD6FULL, 
            0xE9CABC6256E90E24ULL, 0x2D2A165A1D64CA1DULL, 0xFA2003ED7A5A3FC0ULL, 0x54AC585EB0D27A6CULL, 
            0xE06537BDBD8EBFE0ULL, 0xFCA32EB5994CC325ULL, 0xDEEA6A588C055F5BULL, 0x4CA1F10BF64C689CULL, 
            0x18258A36FA1F5A2FULL, 0x33FBCB1C26BDEA1BULL, 0x6F8AE494C4816433ULL, 0xD77AB3B2A71BA5F6ULL, 
            0xFA9D67FA0230853FULL, 0x83EBA1DEDF8C43BBULL, 0xCD9E3B23D3349652ULL, 0x8A21F30D2D34FDA3ULL, 
            0x179FA5AA62F36749ULL, 0xD95037F1990C913AULL, 0x582D965AB37E81D7ULL, 0x4A6C7D65633729D5ULL, 
            0xAAB1D0C04A5B7998ULL, 0x0BD3FF7104E709ACULL, 0x7C63099DACFDDE0AULL, 0x00BBA9535D9AC766ULL
        },
        {
            0xBD1E8AF0C80DF973ULL, 0xA90394CA5A3A5C08ULL, 0x44DD676828486F1AULL, 0x974C883B3EB87765ULL, 
            0xB0AA1F17EE587E61ULL, 0x2AC775FFBD19A3CCULL, 0x9763908AB4ECF88CULL, 0x41180B072ECC1A16ULL, 
            0xDD868E2CDA972BABULL, 0x474E684B0D4D8F3BULL, 0xD672557DE16E5D9BULL, 0x499E1AC5302740AFULL, 
            0x948D2B603C16BBAEULL, 0x31BB1ECAF66A4C93ULL, 0x99157B596C65399BULL, 0x72A5CEB7B826E497ULL, 
            0x6F185E785EAAF29BULL, 0x5207350DB365E8CEULL, 0x8B2E7BD13DB092D1ULL, 0xB537E9634E47B791ULL, 
            0x8328B28749869580ULL, 0x90FD8FA13A596659ULL, 0x0D857DBE48716D30ULL, 0x846566D411406600ULL, 
            0xAE16602E47B2624FULL, 0x9FA03771433B0D44ULL, 0x7267679AB0B01858ULL, 0x6874E31A3D9B3286ULL, 
            0x7BBD907F7DF5CF8BULL, 0x3A3918974CA52E50ULL, 0x302194DDC5D11C8EULL, 0x4E59DAC3C7681890ULL
        },
        {
            0xF3400951FC64B568ULL, 0x6E4DB19DE38883D6ULL, 0xE4E002CCF228A839ULL, 0x88149AD900B939DAULL, 
            0xB02D240E940E5257ULL, 0x03CB10EC1B7CE644ULL, 0xD54F505743ED859FULL, 0x37D39840202BE724ULL, 
            0x7333DE3E4F5DC157ULL, 0x31C7D829BB07D8D0ULL, 0x54462348060C21B5ULL, 0x5443CD98FE9E24E6ULL, 
            0xDF9246D581001240ULL, 0x51B4D0187B487822ULL, 0x18C389BC3C744869ULL, 0x9696746FD1DEEDA9ULL, 
            0xF46F01886C197634ULL, 0x6CC627BDD17F870CULL, 0x9A7928BD3931AFFEULL, 0x35A463EBDBAF4504ULL, 
            0x0B720E31B7E3C3DCULL, 0xB9C1E97FE0497088ULL, 0xED8F88BB1891EB33ULL, 0xBF4BE1C88FEC8EA9ULL, 
            0x120F0F3934629C11ULL, 0xBA02B5A8552BF458ULL, 0x224B5474BE807258ULL, 0xCF03C7594B38BB53ULL, 
            0x8D3167D12635F8BAULL, 0xE234D00A83225B23ULL, 0x78468D6FE257279AULL, 0x75A4D15E0E4F77F0ULL
        },
        {
            0x50702816BA9ECE08ULL, 0x83E8C07F9114B2E1ULL, 0x6153F2EFB30905FFULL, 0x34900AB220012A0DULL, 
            0xEAC98090145943D4ULL, 0x3DAEA317A6EFB426ULL, 0x6622C1ED2CF9EF07ULL, 0xDA02077E269579CAULL, 
            0x35BFD736626DE294ULL, 0x1B3E9916F2FB5883ULL, 0x3EC0599D910EF60CULL, 0x506C2F02A840ABD4ULL, 
            0x6A7AB14ACD7A0A17ULL, 0xD61DAAF277DE148BULL, 0x5CA05208B23965DEULL, 0x4429BC4CC868E2EFULL, 
            0x0E5249770A8E2386ULL, 0x8C9A873DBEF6FB6DULL, 0x7AAF704B469D1556ULL, 0xB828BE5A0C5E3530ULL, 
            0x9DDD7629322224ABULL, 0xCF77E445ADBBD61FULL, 0x6BED36A5D7D59CF4ULL, 0xF3531024FA0706E5ULL, 
            0x3268F75AC1CE14B3ULL, 0x897346A800ADDBA5ULL, 0x501AE49628E0A7C7ULL, 0x29419F7D837A7894ULL, 
            0x7547F0134202F949ULL, 0x031BEC8083DBF26AULL, 0x6693F9627B532534ULL, 0x080B3E5432C9BA0CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseGConstants = {
    0xA12F882C78BE5AD6ULL,
    0xE98BAE3AA7B3B729ULL,
    0x78208756A85189B8ULL,
    0xA12F882C78BE5AD6ULL,
    0xE98BAE3AA7B3B729ULL,
    0x78208756A85189B8ULL,
    0xBCBA9E5C7A0B7E50ULL,
    0x637E15E1237D5D18ULL,
    0xEC,
    0x84,
    0x0A,
    0x05,
    0x5E,
    0x08,
    0x98,
    0xCF
};

const TwistDomainSaltSet TwistExpander_Athebyne::kPhaseHSalts = {
    {
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
            0x111C06AC702CE161ULL, 0xE0E8BE7D6F417CCDULL, 0x18FFC7705A4D7363ULL, 0xD44EEEA7DC4936CEULL, 
            0x8A488367066C712DULL, 0x39C8BE5DACDBD6D6ULL, 0x7EBB6635FA7429A5ULL, 0xF6B6AC28F9720A4CULL, 
            0x1AEF3D0EE07AE840ULL, 0x330DE9CB4DB1E8EFULL, 0x5E70420A7E608FF0ULL, 0x63E86A7CD69D9595ULL, 
            0xC5061EDDFAA70008ULL, 0xDA120910702E6282ULL, 0x6CBBF571C9F184B5ULL, 0x6C910F5349BC9664ULL, 
            0x6CADEF351DD94FE7ULL, 0x01C11A84F4BD092BULL, 0x9D21A853C1D1B643ULL, 0xA118994A26214FA5ULL, 
            0x7488F81D66FF0CCFULL, 0xEF79C777E171092CULL, 0xC35418B89F3FCF7AULL, 0xFCE106B01342E057ULL, 
            0x6BAE086B164D02FFULL, 0x092AB0AB4C88F378ULL, 0x8D98D7BAE8DB5032ULL, 0x5C31A28A44CEDCF9ULL, 
            0xEEA253E4FEAB38E2ULL, 0x246B7D7358035820ULL, 0xDA3C9E0574175BD6ULL, 0xB76B4D43D8679854ULL
        },
        {
            0x11651D7D88BA9659ULL, 0xFD55A19A1DC365DAULL, 0x8C875AA0CC63767FULL, 0xD59177C7EC9C14BEULL, 
            0x4A81193369108846ULL, 0x328759F4814DC3F3ULL, 0x47B9BB6528BB640EULL, 0x87F40AFA01C4BF6FULL, 
            0xB5CA30740DA749EAULL, 0x2EB7EA95ED4AD4EBULL, 0x00BCB99B2EE0F009ULL, 0x99592EEFF20E473CULL, 
            0x345A026878FDA658ULL, 0x134CB1C3A8DC0BB9ULL, 0x9DC0C548A7A88CEAULL, 0x612A1834C15401C3ULL, 
            0x0A7F1D869C161C88ULL, 0xA6DA80A84E371EC4ULL, 0x5EE28C137225FDC3ULL, 0x2D113C7C86847D7DULL, 
            0x656C0C3DC6FF3309ULL, 0x2FF29EF7E7F05C63ULL, 0x5B68E7254213BC1DULL, 0x7BD4B5C6CA3AFC56ULL, 
            0x3E4FEBD285093AC6ULL, 0x272FD2C0678DE15AULL, 0x610279398A5E66E7ULL, 0xF4CEB1CAE53140FAULL, 
            0xA28B9152FD67FCF3ULL, 0x6B3F879AF1D5A923ULL, 0xC410A4CAD6A4DFADULL, 0x7020377C35FB5E76ULL
        },
        {
            0x3A8595FE3EC1CA59ULL, 0x9EEEFB5C0D085A10ULL, 0x7A50BAC2A36A9F49ULL, 0x80F18FA587D1C9DAULL, 
            0x741576ED2626354AULL, 0xDBDC3647555005E4ULL, 0xED2878F27A3FBE69ULL, 0xA78578F7DF530A2EULL, 
            0xB0A33DCA62F59FA4ULL, 0x50DF2E8DACBA4E6FULL, 0x362C68398FC95F00ULL, 0xFCF1CABC04529246ULL, 
            0x41679FAE4C6E1637ULL, 0x0984353769A8FCFBULL, 0x8704AF60D6C1763FULL, 0xAC5D568B342D56D4ULL, 
            0xDB62844F7CC66B34ULL, 0x71D082A09D25D83AULL, 0x104F4D39794750C2ULL, 0xF2E68D991DE61DC6ULL, 
            0x69195183E1D282AEULL, 0x4EEA0827613CB44CULL, 0x0396DA432F1170B1ULL, 0xE21ACC023A752EC2ULL, 
            0xB637B5A9ED4FF869ULL, 0x6DE89D019C37C03BULL, 0x47C0E6051EB8BA0DULL, 0x86CB279BEBACB08EULL, 
            0xBB7DDBB4FFB5DC61ULL, 0x64110A59A82551B9ULL, 0x39870BE82B31DB6CULL, 0xD4B2E51BB877BECCULL
        },
        {
            0x49DCDDDDB71DFCABULL, 0x7BAA0607D99B68D5ULL, 0x45D346BD4A9F8400ULL, 0x5808F2AAEB3FAD03ULL, 
            0xEDE4A4E8823CEDEBULL, 0xA83D73D4449570CFULL, 0x4449CF4720523BCFULL, 0x58D1036E93505B4BULL, 
            0x9EE6B259A898A5CFULL, 0xDB3557B1E2F815F2ULL, 0xD774D985A5541348ULL, 0x69186DB3C399C607ULL, 
            0x4F4302145C883C62ULL, 0x270F5DF2C282CAD2ULL, 0xE34DA24E6D4433F9ULL, 0x81D4F28A93FABEC0ULL, 
            0x0C07462706295BD7ULL, 0x058245A2A11452E1ULL, 0x2050C55CCF439CAAULL, 0xFDA72524DC8A26E3ULL, 
            0xDDA6F21C9208A95CULL, 0x8B6E9D3F278D04E2ULL, 0x5EBF44D0C0CFB18CULL, 0xCD601AE8D5D20E2EULL, 
            0x7740122B6A71C5C0ULL, 0x0AB094FF64A2CF62ULL, 0x592B0FF7E9C278CBULL, 0x7DA12669CFA7CE44ULL, 
            0x40F648A997FF7188ULL, 0x936D9FB4DE49FE76ULL, 0xD2F3A25F2800C17AULL, 0x5526950EE8FDE435ULL
        },
        {
            0x8995ED6ED81AF215ULL, 0x7D7AB56985A462DDULL, 0x37489E221E0A821EULL, 0x8211937E6656CA9FULL, 
            0x5610DE82A0C5C05BULL, 0xAFA936E4B35D4069ULL, 0x469803BF87989E56ULL, 0x58B316970B8D0740ULL, 
            0xC73ED806A35DBB75ULL, 0x26476ECF13BABA53ULL, 0x30BC574D57B59F43ULL, 0xF3E1D9BA4E1FFCB1ULL, 
            0x13672D256B12D6B4ULL, 0x2DA13C7330C1ECFDULL, 0xE8D207E82947B4EFULL, 0xDE4B213FCFCB4578ULL, 
            0x900B5321BDFC9749ULL, 0xCC9B2738BFB0A800ULL, 0x68801FCDF7305033ULL, 0x9D84F41B8268FAF5ULL, 
            0xF47AAF1F727FBD15ULL, 0xAF1BEC7F304CDDF0ULL, 0x5F98F64879CBE7B9ULL, 0x616C2D137765F31EULL, 
            0xD4B277E074EAAB56ULL, 0x06C2BAEC00BBE37EULL, 0x5C7FDCD5A199BA76ULL, 0x1593291B8472FA14ULL, 
            0x2023947C02901798ULL, 0x4BBB3A1E1D8D25E6ULL, 0xEFD5CD2DD60F8D73ULL, 0x707D489A5CA8F5DBULL
        }
    },
    {
        {
            0x87DA5CE1DF64E97BULL, 0xA6F33394D76A42E8ULL, 0x3BE37AF620D40307ULL, 0x5D31D79E50722CE3ULL, 
            0x4C1DAA9E0C0E343AULL, 0xC36D52BBB1861258ULL, 0xF41E35965D64208EULL, 0xE88EF49FC91EB280ULL, 
            0x470D7D9C4E7E9F49ULL, 0x9A2BB3CAF411471EULL, 0x4E24051421F13A7AULL, 0x2CD43D8C8D9347E8ULL, 
            0xF661A7C7FE9A6F48ULL, 0x2CDD0B0B6D22B16CULL, 0x3A8FD6A3F74202ADULL, 0x58C4B5F4F2519524ULL, 
            0xCA5C63A4E33BF944ULL, 0xD5227DB852762FCEULL, 0xC2FA920FE1FBA46CULL, 0x62D671147410CA6EULL, 
            0x38A247326C1A33FBULL, 0x13810F71D37C143BULL, 0x17FB9C559EA4145AULL, 0x9BF2B63F2BE793A4ULL, 
            0x97E00BC28C313E2CULL, 0x898275237D79D1F4ULL, 0xF0D2F75D42C2D3E9ULL, 0x70BBB4BE0D47A1D5ULL, 
            0x2984C53FBEB5CC5FULL, 0x59E9046102127E53ULL, 0x7F4405C6190C2A13ULL, 0x84F413B950648DC7ULL
        },
        {
            0x1D6ECA1BB2E5BAF7ULL, 0x99DAA7F763737E14ULL, 0xD5A017022421E9D9ULL, 0xEAF602160C3DD71BULL, 
            0x001AE9FF25D27D93ULL, 0x3F9026F6EC0182CEULL, 0x59F78F6643F4CA89ULL, 0x9E6C7C82427A23C6ULL, 
            0x18826E87328B672AULL, 0xAA3075C8FA6A4737ULL, 0x4488E38A61863A77ULL, 0x70F1BB860A875F0CULL, 
            0x04F52D9A94AF0E30ULL, 0x24E783BACBA8F38DULL, 0x35094DF995E156CDULL, 0x8AB4D3E98830CAD2ULL, 
            0x52B64A38D5782910ULL, 0x334C9D83DDE20002ULL, 0xB186CE5D37A4987DULL, 0x6489347E9626E6E7ULL, 
            0xCBB9F58693761A39ULL, 0x95C9FE4BDBF122E3ULL, 0xBE56C693A4556417ULL, 0x2C8783FE770BD26DULL, 
            0x93B091BB9ACE0633ULL, 0x12A36F034C426BACULL, 0x0DF749143015F6D8ULL, 0xB79F856E51460A2BULL, 
            0x3E97F7ED05F06995ULL, 0xEFD727D41F2043C2ULL, 0x487F9A76E54CF169ULL, 0x14599D8253132AA4ULL
        },
        {
            0x399CCAEEC96F639EULL, 0x1B0301F08556EA1CULL, 0x158E3BAA771443FEULL, 0x7AB253216B3ABF46ULL, 
            0x7EE4D3C3CE81EC6AULL, 0x5335BD867EE11E6AULL, 0xE653F0BF9A24A5E3ULL, 0x7FB56F33D2A354B0ULL, 
            0xFF58379831658B1CULL, 0x98F1DCAC00B0E35DULL, 0x125CA497A2AD71F2ULL, 0x3AE253BF4B7F1E5EULL, 
            0x170C5AB80B702347ULL, 0xB9F092D432B55CB3ULL, 0x8684E02F1C9FFFA8ULL, 0xC0CCE6B2A85C49F1ULL, 
            0x841D256AC7AA321EULL, 0xF8C55AD87AC5E505ULL, 0xEADED2BE5DEF53FCULL, 0xBB3DC0552C442118ULL, 
            0xE78B54C5C46B9E44ULL, 0x59EEBBC7543CB706ULL, 0xA68C5F95BB39E428ULL, 0x019F570836EC32D1ULL, 
            0xC92A6E460DE43C91ULL, 0x75E8DB694361CA3BULL, 0xBA27C0419280371CULL, 0xAEAE4481C314B3F4ULL, 
            0x48AA7ADFD416A696ULL, 0xAD397410379CF4B0ULL, 0xE5544F37E76C4F66ULL, 0x4E2157F355EAB5F4ULL
        },
        {
            0xF94DAE523481CE4CULL, 0xDCF4D65210050499ULL, 0x7BA9A8A4FF8C6137ULL, 0x55C6EFE41A16E925ULL, 
            0x7BE50F3DE41003D8ULL, 0x6B2C3CBCF8AE777FULL, 0xC4B692CB9A99A89CULL, 0x5188CC9D83A5A0CBULL, 
            0x748D15A4C5653A90ULL, 0x04171A5BD76F4200ULL, 0xEBBF756101235323ULL, 0x09723A190712598CULL, 
            0x58835E6AFFCCA5F1ULL, 0xA228A9DC8B1C087DULL, 0x2BB8EE5E0709536AULL, 0xC7B29B3179A83220ULL, 
            0x88D0A4A1BAF375D5ULL, 0x2075088FB2F69180ULL, 0x36D50E48C2EBA7AEULL, 0x35D3A81983CA7A14ULL, 
            0xCEB8600450127662ULL, 0xA647CCF8929114B4ULL, 0xC1076237B2FB1F62ULL, 0x25CE2D0165F0B7B8ULL, 
            0xEEDB766B7618C7C4ULL, 0x4D32E76327BB985EULL, 0xBA4DC46BCD58B415ULL, 0x3B78FFEB1981AAA4ULL, 
            0x4C801D21C0CE5E97ULL, 0x4F4AD5BAE7709958ULL, 0x88A68362A2113E60ULL, 0x4060CDC4CB80FAFFULL
        },
        {
            0x35B880DEC647C3D3ULL, 0x725E534564CC965EULL, 0x4F6BCAB91D1069B3ULL, 0x4256A643993AD564ULL, 
            0xA4D27DBD3589685DULL, 0x5DA51805CD752978ULL, 0x420EFD680DDE74DEULL, 0x41C24B6085BA2824ULL, 
            0xB13AC22475130DFDULL, 0x910F3C70BB8ADAF2ULL, 0x8485D810A0717681ULL, 0x1E71786A44F5405CULL, 
            0x71BE5B66D5C723B8ULL, 0xB1453959AFBD19B6ULL, 0xE9015D7A0B325ADEULL, 0xB56B71C87410D4A0ULL, 
            0x3465FD1420F5AD91ULL, 0x4CCAC57A6B205BA3ULL, 0x80F787EA0194E428ULL, 0x6D601240B8B887F1ULL, 
            0x2FD5CCAE516D9E1AULL, 0x2080375C22F144E9ULL, 0x20797A9F6E846A5EULL, 0xAB57C85CC2AA131EULL, 
            0x6D0EF7B983FC2185ULL, 0x7BF0766FBB7083B4ULL, 0x1642D8A2680769E9ULL, 0xBC27E6F968F6BB65ULL, 
            0x838FDCC2ADED50FFULL, 0x4F8B5CEC0140E111ULL, 0xFE521F9C5F771F1FULL, 0x02632C7327F0256EULL
        },
        {
            0xCA983DCA52B6A36DULL, 0xBD80659D3D0E08B1ULL, 0x4CEFD5D2DF28679FULL, 0xBF4724474CCE2EFFULL, 
            0x66BF319C2CBF756DULL, 0xE1F13EF6D6A13BC0ULL, 0x84C85FA9A6859907ULL, 0x67A8A712E1E73BD8ULL, 
            0x74B7106B5DE47ADFULL, 0x2B8679292B3517F9ULL, 0x03FC20649D08BE42ULL, 0xCEBD5447061205C4ULL, 
            0x8FF54A0FE5A69396ULL, 0x9E92EA01BF55349DULL, 0x75379205767A5F28ULL, 0x2E1DF298725671B7ULL, 
            0xAD4C5F2E21621EFAULL, 0x32583EC923110440ULL, 0x3B2FB4EC65AAFC74ULL, 0x43645475E89A8C1BULL, 
            0x8B404FC2AE07DC4FULL, 0x565435945AE9EF43ULL, 0xBC1815FABDCD7E7DULL, 0xB8BD8A9F7335C77FULL, 
            0xB4E31D9BD7369CD4ULL, 0x044D4E3F1D7F701AULL, 0xC3F94DAA03278B75ULL, 0x69968E0A9C74132EULL, 
            0xB16B292636E753E6ULL, 0xC694FA5499D2AF69ULL, 0xFAE10176937123D9ULL, 0xA7514DB74C1FE0EFULL
        }
    },
    {
        {
            0xA756E3FB4ADAD013ULL, 0xA1C80B12E3841F30ULL, 0x02EEBC7994F049ECULL, 0x1751B2E7801F45F2ULL, 
            0x989CE5C871C460A8ULL, 0x5B0F0C381A27FB17ULL, 0x3D27DF7AE8841D60ULL, 0x43D3B6A9C2691916ULL, 
            0x27AAE5930ED6EFB3ULL, 0x164B10B6A7EE2E79ULL, 0x595AE025FFFC5A64ULL, 0x3B6374A7FBF0DF35ULL, 
            0x7910C1741236BC71ULL, 0xA301E8CC3BC45DB5ULL, 0xA5BF1A7E63BB7CF8ULL, 0xBB68BF8AC2FD566EULL, 
            0x3BE8313D2D7AE664ULL, 0x3610785B3600A403ULL, 0x15FDD46C860500FFULL, 0xFEA87CD4C66DF821ULL, 
            0x5701AF704FA0AB76ULL, 0x63D4E272ECAA8319ULL, 0xAC226F87F758AA94ULL, 0xB15260E6285F9194ULL, 
            0x49C64B713229FE02ULL, 0x73F4002C238E120DULL, 0x4B607DF2A689825FULL, 0xE26C32743A52AE74ULL, 
            0xEE56105C4C89493EULL, 0xE020F226CF9ACB8BULL, 0xDD1C1F80069D7936ULL, 0x08A192E3CCC7F757ULL
        },
        {
            0x74CA9C7DA05BD86DULL, 0x2F36FC6946D6F7DEULL, 0x1DFBA88D7B520D02ULL, 0x3513904A2888A643ULL, 
            0x8CF4F3E296D90D52ULL, 0xC0AFC1B84B1718F7ULL, 0x0B88E54DBF5C8B25ULL, 0x30605CDF1D28C194ULL, 
            0xB0F60F271BC9C6B3ULL, 0x98A3273BAAED1FC2ULL, 0xAC4DBECFE0C5CBC6ULL, 0xAF55F08DB9138F50ULL, 
            0xCFD001F278155F2EULL, 0xF6877084BF97AC0EULL, 0xD2E163A7FDAE9FF1ULL, 0x836EC0E1E08BD0B9ULL, 
            0x95F65A6FB2D87173ULL, 0xC67043365F3A61E5ULL, 0x42F8BE1AAD09C1DFULL, 0x0E62C92E1931802CULL, 
            0x7664C3BC3A9D3445ULL, 0x74FB4FAECCDA20B2ULL, 0x5C83F550C10FE282ULL, 0x0F656294AC8EBD8FULL, 
            0x6E256E37B7ABB792ULL, 0xA9DA26459E8FF1ADULL, 0x37DFBB1463AB5674ULL, 0xD18FF793E998E472ULL, 
            0xC3D34C4D614BF2A6ULL, 0xAFE898A4E190AE30ULL, 0x9E39028FC6476E0FULL, 0x07B1E4662A96396FULL
        },
        {
            0x3B89EFD61E7962A1ULL, 0x7F523DA9CA926DE6ULL, 0xCD62C6DAA75F7150ULL, 0xAA8723D24EBA5089ULL, 
            0x0164017AC92AA0BEULL, 0x9E9379B57C436BAEULL, 0xE85949636F7309D3ULL, 0x10C09077923CA188ULL, 
            0x2F61BD0F4E5F5C42ULL, 0x84C81571FBDFB1D3ULL, 0x43DD887A82392212ULL, 0x58F0AF04E8FC85DBULL, 
            0x39A430B0A1F81362ULL, 0x69244EAAB8844265ULL, 0x40DFB60A0F0FC411ULL, 0xC524C1B10F41C172ULL, 
            0x9E347658D5A780E6ULL, 0x54717E9F960E4803ULL, 0xF806232165D98B42ULL, 0x9C5B41AC95F285F7ULL, 
            0x4671C50C2CC01252ULL, 0x13B70A16CA0162BDULL, 0x7F4813F02CAEE19FULL, 0xFDBF17223921806BULL, 
            0x09758FD960DB19DAULL, 0x575FF0F95B559F71ULL, 0x64098E3C35602D90ULL, 0x008D0DF3CD5E086BULL, 
            0x84A9997EDCF8F2C6ULL, 0xBEF141265A46EEFFULL, 0x03B412367D0B7558ULL, 0x439CFDE83E8B5558ULL
        },
        {
            0xC3A971F420483213ULL, 0x0035C68CA9E425ADULL, 0x58B3865DB2EB6254ULL, 0xB495DE13CC9E0EA9ULL, 
            0x7A2EFEE9604A0BD4ULL, 0xDCD07A14C2ABA10CULL, 0x4FF524DD6133FA49ULL, 0x2867647540D609D2ULL, 
            0x2A29EBC423447DFCULL, 0xD136381022E2F045ULL, 0xAD03FDEC46BA620FULL, 0x7F9EBF3A8C7394B0ULL, 
            0x37B0620EABE2F876ULL, 0xEE1D77D7C38A8B6AULL, 0x5E1D7A60AE09D358ULL, 0x32086220E9D58407ULL, 
            0x102F8146EBE33F9DULL, 0xE67B936D9AE5F5EEULL, 0xC46CE15BF98AC367ULL, 0x756C68231101CD8DULL, 
            0x09E73B0F6EFDC9F7ULL, 0x1FEB9A802C23B75DULL, 0xBE5985706B5D39D6ULL, 0x1E4A67F78CD2BB94ULL, 
            0x52628A41BF87B049ULL, 0x5F841E7F121560DFULL, 0xDA3A4CEB6C94898DULL, 0x8CB6929999E91D23ULL, 
            0x611F34614D1A482DULL, 0xFAA860F63605EB0CULL, 0x90EEFAC69EA350CAULL, 0x2B1E5FF20869C95DULL
        },
        {
            0xAFF49C26CA242D1DULL, 0x141A1CFD532E3EF0ULL, 0x157A9E6B4C0D80C4ULL, 0xC94B8D7676E4853CULL, 
            0x92E0038A7CD0B0B5ULL, 0x35DF9DBA51D03649ULL, 0xE3CE7A504596AE6DULL, 0x68D8A6F0782B620EULL, 
            0xDF9D9D807C45E797ULL, 0xAD88744855192682ULL, 0xA0983D5BE62BF732ULL, 0x2390E72F5A0CBBD2ULL, 
            0xF755D9DD0FFDE517ULL, 0x4B3175D4FB4C7889ULL, 0xFEC6F52D4D166905ULL, 0x2A74DECDB5D63A76ULL, 
            0xF3460180BAA40E5EULL, 0xEAF4646F6914274FULL, 0x67ADC699DF8D19B6ULL, 0x91301370CB379A88ULL, 
            0xF411DC708B5D08E2ULL, 0xDF462017E36E6658ULL, 0xB6673C055443CF12ULL, 0x6BDD9CD901BBBC75ULL, 
            0xDCD570B2E48A44D2ULL, 0xF320D27AFE0E61ABULL, 0x4AD920264A855E79ULL, 0xB2094F98D17356FEULL, 
            0x07C70E31E6FE8A12ULL, 0x052D7F50687EAB9DULL, 0xB24D0653DEE8FA76ULL, 0x43FE41D7C44D7527ULL
        },
        {
            0x4571830479E965BBULL, 0xFA259498AC214FDDULL, 0x34DAF4F53C7FC3F7ULL, 0xF45D147C6B17DBF4ULL, 
            0xBA4A692FD4C824F8ULL, 0x200117B9BFBFE674ULL, 0xB28BA7ED9BF8DB97ULL, 0xA3B3F1C1BAFD2670ULL, 
            0x547B590E4DBAFCECULL, 0xEDBE65A1A8F99A20ULL, 0x4F4494832D83428DULL, 0xA72A13FEDD0899A2ULL, 
            0xBDE3AE2F96C77D69ULL, 0x280ED062B8828916ULL, 0x87A5BD5D184196A8ULL, 0xB4D882A38733024DULL, 
            0x42BF9DF27858CA8EULL, 0x40F281F41248F9C6ULL, 0xF773B84A5DE82E0BULL, 0x4C214C17871AF186ULL, 
            0x6A38B64B28A9595BULL, 0xB53FF6AAB5033E3EULL, 0x000233F9FB09B547ULL, 0x1FA5C2267A59368DULL, 
            0xED20B6930A9F745DULL, 0x6F3D24031A215FF7ULL, 0xFB23A6F00008B3C0ULL, 0xFE77987C0D10E87BULL, 
            0x8ACB6A8FA10A32C5ULL, 0x2AF7A34F202F5113ULL, 0x945A507F91E8456DULL, 0x3002974CF833616FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Athebyne::kPhaseHConstants = {
    0xADBEC6E6974897AFULL,
    0x84F1BCAAF2D3D3E0ULL,
    0x5F6F78257119C490ULL,
    0xADBEC6E6974897AFULL,
    0x84F1BCAAF2D3D3E0ULL,
    0x5F6F78257119C490ULL,
    0xC453BEA681B51939ULL,
    0xFA59D7EBBABE131FULL,
    0x4F,
    0x4A,
    0xA4,
    0x71,
    0xB7,
    0xD7,
    0x87,
    0x65
};

