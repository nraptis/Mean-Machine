#include "TwistExpander_Rigel.hpp"
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

TwistExpander_Rigel::TwistExpander_Rigel()
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

void TwistExpander_Rigel::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xA404C83CCA0E8C5BULL; std::uint64_t aIngress = 0xB73D4E57E641533DULL; std::uint64_t aCarry = 0xC0BC3EC668C9551DULL;

    std::uint64_t aWandererA = 0xB99038FA76D67572ULL; std::uint64_t aWandererB = 0xD47FD3BAD693EB3CULL; std::uint64_t aWandererC = 0x88B8B2EBF69B7B62ULL; std::uint64_t aWandererD = 0x989BB7C07C0E2ABDULL;
    std::uint64_t aWandererE = 0xA43A33E376CA5C47ULL; std::uint64_t aWandererF = 0x8E2C19B4276E328AULL; std::uint64_t aWandererG = 0x90BA9DED70F4CEE5ULL; std::uint64_t aWandererH = 0x9498F656088AEDB5ULL;
    std::uint64_t aWandererI = 0xC8EF891806CA96DAULL; std::uint64_t aWandererJ = 0xFF9ACD2F0C7AE3E3ULL; std::uint64_t aWandererK = 0xF4ACEFDEDCA217A0ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17088464525339256677U;
        aCarry = 10317610535361059494U;
        aWandererA = 14762788326243645161U;
        aWandererB = 10652274414655852941U;
        aWandererC = 14611645546426825596U;
        aWandererD = 10711238019355291155U;
        aWandererE = 13211615341962060246U;
        aWandererF = 14157157970740652375U;
        aWandererG = 15721756055062411305U;
        aWandererH = 9324100307274928323U;
        aWandererI = 12420876076211132453U;
        aWandererJ = 17749477886718133146U;
        aWandererK = 17640358313927438970U;
    TwistExpander_Rigel_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Rigel::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC72C02D7B280DE9CULL; std::uint64_t aIngress = 0xE3CFA112C861C49FULL; std::uint64_t aCarry = 0xBA0507A868539D65ULL;

    std::uint64_t aWandererA = 0x95E3212E14CE0C18ULL; std::uint64_t aWandererB = 0xD7EBCD6580E9376CULL; std::uint64_t aWandererC = 0xA957137881B06ADCULL; std::uint64_t aWandererD = 0xC992F49769208277ULL;
    std::uint64_t aWandererE = 0x8D1CC1C41D201BD5ULL; std::uint64_t aWandererF = 0xEABFDBD134A3F200ULL; std::uint64_t aWandererG = 0xDC7248BCB8CC2632ULL; std::uint64_t aWandererH = 0xC18713A5322325C1ULL;
    std::uint64_t aWandererI = 0xD263C704BF4D6508ULL; std::uint64_t aWandererJ = 0xBC35F871CD8B0FC8ULL; std::uint64_t aWandererK = 0x8DA416781EC1248BULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10873931261995564207U;
        aCarry = 18076043737989320723U;
        aWandererA = 11792016348291097273U;
        aWandererB = 16070068016058600497U;
        aWandererC = 16705411930965872358U;
        aWandererD = 15350259146570523034U;
        aWandererE = 18217551376436512433U;
        aWandererF = 13518223634445583853U;
        aWandererG = 14293279372610240621U;
        aWandererH = 13928233178494583391U;
        aWandererI = 16949532993570615916U;
        aWandererJ = 9764354026760374162U;
        aWandererK = 17617962060872510298U;
    TwistExpander_Rigel_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Rigel_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Rigel_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Rigel::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xBE1BB362AA9BE998ULL;
    std::uint64_t aIngress = 0xDB5DED9607DDF620ULL;
    std::uint64_t aCarry = 0x917532434108E49CULL;

    std::uint64_t aWandererA = 0xF90A5BDC0655E4AFULL;
    std::uint64_t aWandererB = 0xC4850EF7B6F49108ULL;
    std::uint64_t aWandererC = 0xEFF222F2344875F9ULL;
    std::uint64_t aWandererD = 0xCCD6DAB6BE61B6BCULL;
    std::uint64_t aWandererE = 0xF0B52FEA98C9ABB1ULL;
    std::uint64_t aWandererF = 0x8A3483F221D9835FULL;
    std::uint64_t aWandererG = 0xC3EFB6AC2C1997ECULL;
    std::uint64_t aWandererH = 0xAC687C86F3CEA123ULL;
    std::uint64_t aWandererI = 0x9A8ED4DD3C3DDD8DULL;
    std::uint64_t aWandererJ = 0xE57480ED1B14D2BCULL;
    std::uint64_t aWandererK = 0xE6E3E1A35BC351CEULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
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
    TwistExpander_Rigel_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Rigel_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Rigel_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Rigel_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 29 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1791 / 1984 (90.27%)
// Total distance from earlier candidates: 50974
void TwistExpander_Rigel::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1374U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1478U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 226U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 547U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1839U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1534U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1824U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 63U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 118U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 806U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 672U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 216U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 316U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1015U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 812U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1472U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 960U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 13U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 790U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 994U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 47U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 272U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 39U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1659U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1548U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1592U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 497U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 953U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 534U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 595U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 434U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1587U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1139U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 477U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1767U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 37U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 940U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1006U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 221U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1984U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1253U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1035U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1378U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1315U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 315U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 499U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1336U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 546U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 690U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1732U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1719U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 770U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 200U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 203U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 255U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 492U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 0U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 217U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1300U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1213U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1981U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 199U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 456U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 376U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1215U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1693U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 310U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1241U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 565U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1384U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1658U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1939U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 977U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1740U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1055U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 379U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 414U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 30U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 906U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1861U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1688U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1373U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1186U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1053U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1751U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 679U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1500U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 463U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1607U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1264U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 894U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1596U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 642U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1736U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1298U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1034U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 144U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 508U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 907U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1342U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 284U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 389U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1048U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1608U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 275U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2026U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 580U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1741U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1820U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 75U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 113U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 638U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 397U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1613U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1089U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1114U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1638U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 542U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 911U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 789U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1411U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1851U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1346U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 331U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1070U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1102U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 119U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 693U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Rigel::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xDBC22470735893B2ULL; std::uint64_t aIngress = 0xAD38D37414DB8A72ULL; std::uint64_t aCarry = 0xA705F1AB61F8AF0CULL;

    std::uint64_t aWandererA = 0xD7156FA642A5C9A0ULL; std::uint64_t aWandererB = 0xA5F651467CDF2474ULL; std::uint64_t aWandererC = 0xF8F50FC221EA7ACAULL; std::uint64_t aWandererD = 0xD8D396892EEE0948ULL;
    std::uint64_t aWandererE = 0xF322429944F09064ULL; std::uint64_t aWandererF = 0xE414D6B76F6F8F61ULL; std::uint64_t aWandererG = 0x8944A7B41A2124DEULL; std::uint64_t aWandererH = 0x9AF97316181D71E1ULL;
    std::uint64_t aWandererI = 0xF602EEE20454BBB1ULL; std::uint64_t aWandererJ = 0xB2FE0243F1A3C64CULL; std::uint64_t aWandererK = 0xE4F242DDC3372D59ULL;

    // [seed]
        aPrevious = 10229235996103424392U;
        aCarry = 14690639517228595192U;
        aWandererA = 14341140478598770600U;
        aWandererB = 13859151461638778931U;
        aWandererC = 12763809027129975938U;
        aWandererD = 10918473215075982382U;
        aWandererE = 17201004207333356778U;
        aWandererF = 12021086327600265632U;
        aWandererG = 10311436858507551012U;
        aWandererH = 14762493376567631508U;
        aWandererI = 15218692076163714185U;
        aWandererJ = 15245548385946271203U;
        aWandererK = 9878204606455658740U;
    TwistExpander_Rigel_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    TwistExpander_Rigel_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Rigel_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Rigel_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Rigel_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 29 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15130; nearest pair: 477 / 674
void TwistExpander_Rigel::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2650U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6540U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1734U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4001U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 395U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1371U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3948U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6680U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4991U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4497U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4920U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6290U) & S_QUARTER1);
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
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2462U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2574U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 500U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 8063U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 216U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 211U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1915U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 407U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1202U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1054U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 473U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 325U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1051U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 829U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1667U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1416U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 497U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1489U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1767U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 657U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1796U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 980U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 327U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1800U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 29 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 15145; nearest pair: 485 / 674
void TwistExpander_Rigel::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1189U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2044U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3010U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5688U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5765U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6132U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6103U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7446U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 577U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7253U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6616U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4135U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7598U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5239U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 891U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3861U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1677U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 362U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 327U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1682U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1322U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2001U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1171U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 932U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1162U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1204U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2029U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 717U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1696U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 148U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 40U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 580U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1891U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 201U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1286U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1606U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseASalts = {
    {
        {
            0x22C508E339CE0932ULL, 0x0E24A0CAFE159B31ULL, 0xEEEE0D019BB4D87EULL, 0x6F20D6A249FD91DCULL, 
            0x06D41F94F9FB9E16ULL, 0x10AAFB171809DC80ULL, 0xDDEF9A792723E905ULL, 0x985D234BB4A2E980ULL, 
            0xF84233208FEAC164ULL, 0x4FEB9B3129E935DDULL, 0x8B130BE18A21551CULL, 0x95115017A2681154ULL, 
            0x026E3A14B233CC8EULL, 0x6382E31A761C4D5EULL, 0x94A234A54348D785ULL, 0x6A9BA49157FB85B4ULL, 
            0x067C30CC3E367F08ULL, 0x5D9ABC371A529704ULL, 0xD6F68F17E353C064ULL, 0x464F3AD77A8D2F98ULL, 
            0x6C1BF3E5A2FE54F8ULL, 0xBE5BA06C8A1427CBULL, 0x48D43DF7AFE01786ULL, 0x670CAA81A136C96BULL, 
            0x8F69D32B16B73906ULL, 0xCD0A43468A7CC270ULL, 0xD8F0E26012D03E99ULL, 0x50CB0EB6E286B385ULL, 
            0x9BB8F3435882847BULL, 0xE2809FF5451F0FCFULL, 0x1C75C6317825C2AFULL, 0xED4F163DFE3324B7ULL
        },
        {
            0x771A3F1088ECC653ULL, 0x3AA7207E96AB3335ULL, 0x8CFC6139128A2195ULL, 0x7A1AE991D8924B1CULL, 
            0x84DF482917ACBB4AULL, 0x59F40B1B304455A1ULL, 0x83309DEB8FA6AD1EULL, 0xD37AAF9BB434AF5BULL, 
            0xDEF4284130534E66ULL, 0x11B2AEF33C494154ULL, 0xC51E93153ADF651AULL, 0x4C703FF2E6238601ULL, 
            0x8D719937A70DC517ULL, 0x563EF0228CAE9A5BULL, 0x5A6911A926EE508DULL, 0x1F2545963134E113ULL, 
            0xA9BFF7CB16E1D027ULL, 0xCF65A7211ABEBE58ULL, 0x0DC3F8F10EF4FCF2ULL, 0x1E5EE4B3EFC68243ULL, 
            0xE7CAD2343B939A8DULL, 0x6BFEE17EF9069107ULL, 0x86712323030547B2ULL, 0x44EEC985114FC334ULL, 
            0x1A303937A30C4173ULL, 0xB2E566FC076294F0ULL, 0xB5B41B63BB7E6E5CULL, 0xC06C037A39813B10ULL, 
            0x67C777E891A87541ULL, 0x80EA8E923B403C87ULL, 0x768A57882741F965ULL, 0xDF5DE6D9E13C08BCULL
        },
        {
            0x21B5A4FD1C5F2608ULL, 0x8ADD35900FF2DBF0ULL, 0xB8196D99FA5E605BULL, 0x5FFE4F93223F12B9ULL, 
            0x866A07F61285AB23ULL, 0xA2F3E5EDA6487569ULL, 0x45E99DBD1C7249BFULL, 0xAC06AE163FF66D58ULL, 
            0xB8913F462398805EULL, 0xFFBEDAC65778291BULL, 0x004AED085729319CULL, 0xBC720B3F0181FD02ULL, 
            0xEBD259861789E736ULL, 0x1481451FA2AFE650ULL, 0xC12A6DBAE2D7CD3AULL, 0xE46F4B3855C0531EULL, 
            0x1B620E43A5AE2F86ULL, 0xE7BE856DE10E919EULL, 0x9C6700360E772CF0ULL, 0xE97A86FA4A2BDFA8ULL, 
            0xE230CF97614E0153ULL, 0xE6B8BD57DA3FA9CEULL, 0xE47F2DFF2459FC9BULL, 0xF1F4D2B39D2D65D9ULL, 
            0x2C03D4E49148ED99ULL, 0x0979881303B789B6ULL, 0x715385E227B91CCEULL, 0x306DD1878718CD2AULL, 
            0x55EE592987468A43ULL, 0x5A617845D40DE06BULL, 0x90BDB94EE6F570D8ULL, 0x1AEF480B7AC8BC95ULL
        },
        {
            0x36393EC002EBD297ULL, 0x29527E58432EE987ULL, 0x8274D57675B84E51ULL, 0x6E838763D848A7AAULL, 
            0x094468F62AE17D04ULL, 0x6D5BAE8637109AC8ULL, 0xBAA18746D77A9BF1ULL, 0xF62562005206F8A2ULL, 
            0x1F657277CC54C936ULL, 0xF521E66677520FB5ULL, 0x1D5129A348A7EA38ULL, 0xA63A1BD7DFC65107ULL, 
            0xACD9B38ADEA80709ULL, 0x0A271549BD78A6CBULL, 0x831F90CF987697B9ULL, 0x4C2890FD4ADEE7DFULL, 
            0x2296F6CE7DE469F4ULL, 0xA3635B656529C9C9ULL, 0xAEF0926042B13764ULL, 0x8874C4ABC2DA08E3ULL, 
            0x0FDDE41C072FB0BEULL, 0xCA5411BD74D7CCDCULL, 0x81CE319712FC8ED4ULL, 0x5AB73706AF32EB52ULL, 
            0x23697DD5E3A59EB9ULL, 0x17E38B3540A7C24EULL, 0x48FBF1DC600D90EAULL, 0xBE0A405B0BDB457FULL, 
            0x6C47BF18ABA12F78ULL, 0x7B7E42A39EB7D1C2ULL, 0x56F7CA5CE6A74D26ULL, 0x16E2DFA06F61888BULL
        },
        {
            0xC212B14074D6658CULL, 0x016351F16CCA4DACULL, 0xC12BD4DFA0D5833BULL, 0x68FF5E0C62EBBB0EULL, 
            0x26DF965B0B5F82BAULL, 0x18364F12336C8CF8ULL, 0xF85218F3A150A592ULL, 0x4DD85EF85F25435BULL, 
            0x79B587C5B0CBF875ULL, 0xE210E4D137F569E0ULL, 0x80A030EA6731D409ULL, 0x4631C06A90B1F9D4ULL, 
            0x1615E72B60E39092ULL, 0xF7BCF3B98D3BD6AFULL, 0xD954593C4C7B980BULL, 0x4D38F352CA9195E9ULL, 
            0xBD0A4AEF4DCF8DC7ULL, 0xBD09D363F6F3C1D6ULL, 0x65B7193C271B6F76ULL, 0xE2663A9DA7F87D69ULL, 
            0x7F8D73B2B5E4D439ULL, 0xE38EA7CF2F07F666ULL, 0x53D83CAE5C967CDDULL, 0x5230AD7C50B26AB9ULL, 
            0x19A94F554B7781FCULL, 0x2CB8E54DA0B7A627ULL, 0x887637C39BDA2470ULL, 0x62DCA1E647EE8BFFULL, 
            0x886FFF40F2D7FEB7ULL, 0xCA8624DF4A484A20ULL, 0xED49A6E1CCC1CFC0ULL, 0x43F0D8B1DCF2FF21ULL
        },
        {
            0xED320273CF20A657ULL, 0x91197D5F57BADA4FULL, 0x3FD32F30DE49CC13ULL, 0x7FE65C9EC0ECF881ULL, 
            0xD23191BF04D2A60AULL, 0x34F894659556F2E2ULL, 0x116010A84F02C8E3ULL, 0x8E9118B0C8C74B93ULL, 
            0x81DEFF80F74C4BB8ULL, 0xB30D84E9F3B1235CULL, 0x91A0441416946249ULL, 0xC0239A0DE59030B0ULL, 
            0x6F201935BDD3CD89ULL, 0x11A79F211BF30D63ULL, 0x07853ABC6FC54C60ULL, 0x085E278414BE0FE0ULL, 
            0xEAAFAEB5A8F2F71FULL, 0x5738FDCBB4CC7808ULL, 0x0D94D11B4CBFC464ULL, 0xD9D4BFCB3E67306CULL, 
            0x72DDB5A10F38FC30ULL, 0xB23517C0B7210C68ULL, 0x4B8C6E8701790C86ULL, 0x2A57A643F3EFD4FCULL, 
            0x5CF5238B1CB81C94ULL, 0x500D00A5CB2A4FFDULL, 0x929620AA64C9BEF7ULL, 0xE51DB46E59266B48ULL, 
            0xC39198AF1EE88C34ULL, 0x491E7777AFB396E3ULL, 0x7D3A25C8AB6D062BULL, 0xDD1EECB27C82C622ULL
        }
    },
    {
        {
            0x58F3851B03994E15ULL, 0xFF2B76065C4E9730ULL, 0xC8697E45EBCC07EAULL, 0xE536B225529F4156ULL, 
            0x8AF95D896642BB3DULL, 0x53335D597DAD09DDULL, 0xEB45F71FC158A769ULL, 0xD1FF9A136B6F622FULL, 
            0x2B5D9FCAFF524BE0ULL, 0x1AEAF3F0D0D84B9DULL, 0x055B17AF29F8DCCDULL, 0x419D29CBBDB75BA3ULL, 
            0x8CF0640EC885C0E0ULL, 0x292DA55122316CA0ULL, 0xDB61F562DDAA1E3EULL, 0x8A778085F8906E8BULL, 
            0x87A91D5E180FD64BULL, 0xC4C6E88090FC77FDULL, 0xAB9101D47CF7A3E8ULL, 0x3C2205AA90738A13ULL, 
            0x30125F76D2799D1CULL, 0x7664BAC82E35E620ULL, 0x67E8A5B1259BCFE7ULL, 0x91F7E6DA12021336ULL, 
            0x94449BE3EC4A8CC1ULL, 0x409DBED9DC54247BULL, 0x56BD4B5036F91B87ULL, 0xB3E1F2FCB78AE501ULL, 
            0x561DBC9074FD04E0ULL, 0xA7C79FA2254F8512ULL, 0xAAAB8179F6989580ULL, 0x1102E497D88D8ACFULL
        },
        {
            0x558877E48BBFBBF5ULL, 0x154CE61F432EC67AULL, 0x22C6D044D18A9433ULL, 0x673D15997B4A0C4DULL, 
            0x86ACD958B92FBC0BULL, 0xAB9D31C423D08BE8ULL, 0x1D9CE1931560B9DFULL, 0x982DF7D662636291ULL, 
            0x08489DDD45801311ULL, 0x3E8AC924BC3FDA42ULL, 0x588E4A556CEA9C6CULL, 0x318D499B5C47EEEAULL, 
            0x9F0EA9D125D39691ULL, 0x3B21C8A791F4705DULL, 0xEDC2CDB11D2F15EDULL, 0x33373EE7B14DA5C7ULL, 
            0x7381C8CA8F6A1200ULL, 0x716DC6B93328E5BDULL, 0x1D8B6D10B488C08EULL, 0xD00999D80D3D6519ULL, 
            0xC5649D65BF4E3416ULL, 0x9994668F2587EB4DULL, 0xA5BF7440078C6B90ULL, 0xEC4C6CA7D78B0836ULL, 
            0x1D66EA4A65FEB15CULL, 0x0FDD49CBFEABBE2CULL, 0xFC5B77A6B489F771ULL, 0x6CD93B8418A9CB92ULL, 
            0xEBA84742466163C4ULL, 0x2A3B550454E94B82ULL, 0x111602BDB029612CULL, 0x689DA9690BE8B2C9ULL
        },
        {
            0x550C061532A459CDULL, 0x90EDAA6DCA0BC5CAULL, 0xE5DE088574A01E7BULL, 0x0BCD544FCD984502ULL, 
            0x281ACD5B9550E623ULL, 0x00A3F310B532FD69ULL, 0xE0D38837D7B711B4ULL, 0x97E608F65F852CCEULL, 
            0x5C7CFA06EC5F5036ULL, 0xAADA2BEA255FF49CULL, 0x6AC2AEA9336C269DULL, 0x0FD0EDBB92902315ULL, 
            0xCB25D6CEB8E34B4FULL, 0x1F2D6638A91FC757ULL, 0xAB2A25C052BEE945ULL, 0xA5C7A81FD4215A79ULL, 
            0xAE9250539A85E9A2ULL, 0xFF5F9D86579D382DULL, 0x1E63A37DB2AB3012ULL, 0xBF0189E9BB263611ULL, 
            0x27D6FBF870FC0A4DULL, 0xC9DC403F296B3DBAULL, 0xF08AC486CEE31A42ULL, 0x047AE40A7475932FULL, 
            0x9D575A15AF188DAAULL, 0x178BDB7E2409E252ULL, 0x2F4BB9294DB20B03ULL, 0xA8262E2DD76F6041ULL, 
            0x70D25B197C8F8A64ULL, 0x4EAC612E96B8FDB0ULL, 0x99F7FF53E7C82874ULL, 0x21D85E6ECCCA5A7CULL
        },
        {
            0x87C64D8DB7FD3DF6ULL, 0x05CCE99EEDE35BE1ULL, 0x0ADE3CEB5E5C36EFULL, 0xA8B8FC016E391135ULL, 
            0x564F37F812978BEDULL, 0x22912F9F55D70174ULL, 0x0527C70D9C89CBC3ULL, 0x374CCA2B3616A0CDULL, 
            0xFF9CA9DE7DE57F3CULL, 0x4FB6409C5B7D0122ULL, 0x33B171CA7EFE572EULL, 0x85563D20DEA727DAULL, 
            0x2EEA41C2E18FB903ULL, 0x7448454442B6542EULL, 0x18802492AF33D639ULL, 0x30D820C0F21356A9ULL, 
            0x2E98820E2CF10F6EULL, 0x7AAB39BF373AACB7ULL, 0xA8AD8D06275E64A7ULL, 0xA69605006B6804ECULL, 
            0x8DA9F4A4E008D5A0ULL, 0xCB61BE54AFE19656ULL, 0x17D0C24425B843BAULL, 0x74A92ABABD16B683ULL, 
            0x889C9DDB4AC7205FULL, 0x4208BD36DCEC1E21ULL, 0x12C5EEA71FB361D4ULL, 0xAF151B26FB5B0FB1ULL, 
            0x734AB1E3B910D8A6ULL, 0x11E80A266A28B5A7ULL, 0x4BC92D45CE3A3057ULL, 0x56C9937883A7A0E2ULL
        },
        {
            0xC0B1EEBC19D6DD5DULL, 0xFBD584C0BE78A378ULL, 0x3861C4FB47ED85ADULL, 0xD0C1648C6133AE74ULL, 
            0x1A2E0758CC04F647ULL, 0x7F4B22E9D2E429B7ULL, 0xD3D3EC37F0F282A2ULL, 0x4A1A80E82926F4CCULL, 
            0xE57E2CC57A5AF193ULL, 0xEA7C9FD1B4DC3358ULL, 0xF1C8E84FCB59B915ULL, 0x9162C5C737831508ULL, 
            0xBDC0C1FF8F72FBADULL, 0x15CBA6A2DB95D3E5ULL, 0xA7F3606B20800AD6ULL, 0xC71637CBB81AC1D4ULL, 
            0xA298A35510538CDFULL, 0xBE96C02372571E86ULL, 0x1CB7F173C932D3B8ULL, 0x0BC7749762FCD932ULL, 
            0x7577CEEAEAFA0CFAULL, 0xE0DB0FC479FCF081ULL, 0xF2ED0B3805776E69ULL, 0x4390BBFEA7DD5BEFULL, 
            0x3F6491AE4CDBCD41ULL, 0xC48A0406F5DB7D53ULL, 0x6234F2620AE53FDCULL, 0xA1823341F0804C02ULL, 
            0xF230A290836D8D4BULL, 0x435E602CB40E9064ULL, 0xD3C61BB21818BC87ULL, 0xD3694EDF2907E472ULL
        },
        {
            0xE5B160D2CC068469ULL, 0x63B3765759430BFAULL, 0x8A5C3160B0122A2BULL, 0x525CA9668CC27623ULL, 
            0xFC71696A132050DEULL, 0x1DE34BFF44CB08A9ULL, 0x83DEB86EF37D7CD0ULL, 0x417EB807E3A23BA7ULL, 
            0x3E94E15B5377FB53ULL, 0xDC69739CC3E52E67ULL, 0x972D1E2A2E5E48EFULL, 0xF045EE24C0112BC4ULL, 
            0xE09B1B37E90C90E8ULL, 0x80C371FB856FCE8EULL, 0xF8FD7E83EC3AD504ULL, 0x82D13B441000332EULL, 
            0xB7AD391FC186B366ULL, 0x9B36D949F9C98B04ULL, 0xD82378108E788DCDULL, 0xDA07E1699C2A0B26ULL, 
            0x8EB53B9A42B47DC6ULL, 0x8352A89FC1813B6EULL, 0x1C04C749EEB8A436ULL, 0x1C4CAC67A0BD91DDULL, 
            0x1958F649A637D3CDULL, 0x122CC1D46D2845A0ULL, 0x2D66EEDDEF425424ULL, 0xA03FA865081E3440ULL, 
            0xEDDA777F6FB354A4ULL, 0x8319DB31343EEB6AULL, 0xD06A3D8070066292ULL, 0xCB1C3DAB724FB4A8ULL
        }
    },
    {
        {
            0x6BFA559978EEC0E6ULL, 0xFE24B64DD8824E0EULL, 0xD9DB3F95B382954DULL, 0x754871283D4EF11EULL, 
            0xFF9C0F478EE6A426ULL, 0x890C4F552DCD1036ULL, 0x88D6725F9A42549DULL, 0x868A19BA446CCEB3ULL, 
            0x89DB3E357F590272ULL, 0xA8B7BFB9AC5DB621ULL, 0xA20A90234226DDA2ULL, 0xF51B0372F0CB1C06ULL, 
            0x2D43670236B0698BULL, 0xB2BC70A03B30F232ULL, 0x3DC9E60F116830E4ULL, 0xC72D80AAEB336DC5ULL, 
            0x2CA2B7947C45F702ULL, 0x100A932F2EC74EB1ULL, 0xFC7ACDDBFF1080A2ULL, 0x9C35CBBA6CD2B02EULL, 
            0xA6E11087D125201CULL, 0xACE429FB96E53D4FULL, 0x17D7DFDC4F971397ULL, 0x5FCD9B7D77631916ULL, 
            0xD0D2F3400BEC878AULL, 0x600717EF3BFE1EE2ULL, 0xEB721C66D0602D32ULL, 0xA3D7E345178C41C8ULL, 
            0x32F5D76CFF4C7E5DULL, 0xAA2490B7A75C7BBDULL, 0xB48A6724450FCB1BULL, 0x0FF66128E2B731D6ULL
        },
        {
            0xDD9DB96416496196ULL, 0xE5B140A166DE77D3ULL, 0xD0A6DD30E2ABECBCULL, 0x6A557744EFC1721CULL, 
            0xCA5E82A1F7CE5F23ULL, 0xAF14F88AEC2F4C3FULL, 0x85B291774AFD08B2ULL, 0x464DACD04E8F3424ULL, 
            0x6537916B9469F22CULL, 0x5ADD29F1882B8331ULL, 0x29A7DCC72A072D0DULL, 0x84D046B989353584ULL, 
            0x766AF2B5C44226BAULL, 0xD53C467053FA7AB0ULL, 0xE376888C8EAF68E5ULL, 0xF92AC2C561ACF33BULL, 
            0x02356EF00F876ED5ULL, 0x753B0FFCCF4B0FBCULL, 0xAB6B2586CFFB76EFULL, 0x504D6CF201C4ADFFULL, 
            0x06D8CA913A5CEE57ULL, 0xD6AE90A8E9BAA3E7ULL, 0xE5BE421A598CC97AULL, 0x1EFAFB8A889F0125ULL, 
            0x0A1E9E05D685DFDFULL, 0xB9720C41DE4F3962ULL, 0x50D34C163272E081ULL, 0xDD4982F2CE3C81E7ULL, 
            0x95CA541E4DC2A0F0ULL, 0xE7A7DB55A3A4ADA8ULL, 0x0F7386D93B32673EULL, 0x0C6137EAF66457BCULL
        },
        {
            0x61564BF34BF280D5ULL, 0x6224DBABC137849DULL, 0x2179F73EC1F1CE53ULL, 0x49F7CA3CF7BA0DEDULL, 
            0x12EBAE562D95BBBBULL, 0xCEF7D347AEE37329ULL, 0xE55BEF75A2807353ULL, 0x92A9C1E595372B9AULL, 
            0x1EEE705CCD64B747ULL, 0xF3AC7679D1D5C2E2ULL, 0x0F715F6B73B7675BULL, 0xCBCFCE21F43EA880ULL, 
            0x148741B6B12A5A77ULL, 0xEBBBE5214691D478ULL, 0x7E6BBD18EC5BA775ULL, 0xCD729F69B74AAB5BULL, 
            0xD2832F5BE6953166ULL, 0xD1D4473F79D0CAD9ULL, 0xAE4AA0F01F23ED0DULL, 0x1C4DAD2EB17B17DCULL, 
            0xE8C1E0FBFADF1B55ULL, 0xC3289A5531FE90C2ULL, 0x634D621ED67605F5ULL, 0xBDCCBE69D2275417ULL, 
            0x23136CFB185C0833ULL, 0x6BCDA62E6B21C602ULL, 0xF800B288CEA2B029ULL, 0xBB4A9A7C4110DE8BULL, 
            0x309D8200E5E4F391ULL, 0x913319E100796C72ULL, 0x2060B212F0668952ULL, 0x37C6B5E71A92B954ULL
        },
        {
            0xFD0F229D59D0AB92ULL, 0x9953F036EB1F6873ULL, 0x0CE2A541707DB233ULL, 0xC3DDFE61792A0BB4ULL, 
            0x611863ACE7327CEDULL, 0xB4CAA64E8754FCC1ULL, 0x84AB1DAF65E4E9B7ULL, 0x52F1CDA7746DD3A4ULL, 
            0x3421C4526DB8079FULL, 0xE5A808D396048BEEULL, 0xA2796B482400D1CCULL, 0xF65F35C498480FA6ULL, 
            0xD8A7B407D6825D0EULL, 0x55F6EEF7B115950DULL, 0xA004F36CAA7E13AEULL, 0x54EC1D4D6C0F6F4EULL, 
            0xCB6A8952ABEE410AULL, 0x6832A43DD0F3E1D6ULL, 0x41F1E4AA23958CE9ULL, 0x7DAFDC4D2910CDD0ULL, 
            0x7F99C7539ABD8D58ULL, 0xF9B20CF7B5940EFBULL, 0x676C8035528578E3ULL, 0x0F208900B19A39E8ULL, 
            0xA9B2F5770EF20444ULL, 0x4F53FD47F5BD6580ULL, 0x0C75A04BDDBA5CD0ULL, 0xAFF92BB81705D255ULL, 
            0x20612F912F14CC80ULL, 0x633483024297784FULL, 0x4CBE424D98CC8D48ULL, 0x8138B85A99B07E45ULL
        },
        {
            0xE3F6D93A9C0F3393ULL, 0x3F76FA53449D79F2ULL, 0x4A7B19FBD27AFFCEULL, 0x5DE297AEC0E777FDULL, 
            0x715316F3D5D77B1DULL, 0x7F7A6BCACC974494ULL, 0x62927136E2CFB38EULL, 0x3A9BFD1CCB0C71B0ULL, 
            0xED505384E93A3A46ULL, 0xAFBB7A6DFF946B4AULL, 0xC0DAAA7432E07D6FULL, 0x1BF466ED1E4F1F1EULL, 
            0x75B098B8FB1B8120ULL, 0xA0033CEAEDEB3EC4ULL, 0xAA4DB53E8597FDD2ULL, 0x13F3FD5885302E18ULL, 
            0xEA66602E98E0E28DULL, 0xC472639709EBB459ULL, 0xFC5FD2A609637E7EULL, 0xC2F3D58230A0BD89ULL, 
            0xFB30EE90DD2BBC43ULL, 0x543E88B5629E7211ULL, 0xA2B3E6E0E9DCE6B4ULL, 0x7E332E2AE06D83C4ULL, 
            0x91124781D8E728B5ULL, 0x1CBCD3616C53F1AAULL, 0xC5B1EB785F1DA18EULL, 0xB5851C16E29EEB0EULL, 
            0xDEB4880D25742AA2ULL, 0x5481E7B931740C59ULL, 0x99083A1210BABE8AULL, 0x96E554106B73B088ULL
        },
        {
            0x5B6948CCF586AE0DULL, 0x69DFF4104B71EBF2ULL, 0x2480665AA35B349AULL, 0x3EE80BFE72E3868DULL, 
            0x70D70D3366422FE8ULL, 0x6E4368F2F2A16979ULL, 0xF478D2B2BE820BBEULL, 0x72E93072627DE3EDULL, 
            0x794BA60A244BE166ULL, 0xB611C8E8798A673FULL, 0x037C87E07ACA526DULL, 0x614534C112AEF987ULL, 
            0xE372BE309D7DF704ULL, 0xF3DE6F24328FDCA8ULL, 0x4165B0D4822FD428ULL, 0x1CBD1F064506B48DULL, 
            0x7EC3CCD746A198D6ULL, 0x58EC4F3DC69D47D5ULL, 0x44D8146669728B42ULL, 0x6752618203BF8541ULL, 
            0x65DE5225869B54C7ULL, 0x22C44772BB0503A3ULL, 0xCFB2047A2828E809ULL, 0x13069B35DAE39EA8ULL, 
            0xF7A9B9E5C257A4D5ULL, 0x6B3285F2FD5CB26DULL, 0x012969FBB5EB3FFCULL, 0x2E894AE3E6342815ULL, 
            0x34A203FEE99B99FDULL, 0xBAE6E986D3C6860BULL, 0x6B24D2EEB900FDAFULL, 0x085213FF2DE6C2EFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseAConstants = {
    0xEE22A23A44CA1A09ULL,
    0x69F60DDC12397B9BULL,
    0x189138D20FDEA5BBULL,
    0xEE22A23A44CA1A09ULL,
    0x69F60DDC12397B9BULL,
    0x189138D20FDEA5BBULL,
    0xE81486C6ECCB2E7FULL,
    0x3D196DAB40F216FEULL,
    0xC1,
    0xE0,
    0x74,
    0x3E,
    0x9D,
    0x35,
    0x28,
    0x35
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseBSalts = {
    {
        {
            0xC219A9E7E6FD58FBULL, 0xFB1E656280D35077ULL, 0x228225011884D520ULL, 0xA07F16F89C5C089FULL, 
            0x621EF88E6D91D29BULL, 0xFBA85349A020C575ULL, 0x1FBCDE6D51F63AF9ULL, 0x0DE039B41A97CD8FULL, 
            0xFBB0EB7037871C7CULL, 0x1979003E5C85E6A9ULL, 0x64113566EF5348CEULL, 0x2DB05F3760AB545CULL, 
            0x7C607C81F3679704ULL, 0x27A9E564A56A54B6ULL, 0x840EEF1E10B3FEBBULL, 0xC95B3A845780D2F8ULL, 
            0x9E8A93D8CAF93BA0ULL, 0xB15D474585436EC9ULL, 0x070E760DA8A9B492ULL, 0x30D768FC7E37381AULL, 
            0x7E1A308F53DC7676ULL, 0x8EEFB9D29E954D4BULL, 0x69CDE11E1569FDFAULL, 0x92F780CDD98DA26AULL, 
            0xB662BEEC5EF8A6C0ULL, 0xFA50C15F688FFBFEULL, 0x26DE12CEE95ABD4DULL, 0x024337C9A788CA8BULL, 
            0x29987F213269730DULL, 0x7141D1013A46F8E8ULL, 0xB5A3E7990164F081ULL, 0xF5EA39C991939543ULL
        },
        {
            0x7E016D54701AEE43ULL, 0xB642E41438B8A321ULL, 0xB7A9D83527D9D5ABULL, 0x6FAB80520CCEDFC0ULL, 
            0x3EBC3508232BB183ULL, 0x90D2B7FAA6344ECBULL, 0x21F69411AAD47EA1ULL, 0xA7092093D6B832DEULL, 
            0x37247769C4FAD9C4ULL, 0xDAC9C4BDE75D147AULL, 0x43BFB5E28D00D771ULL, 0x6970D9167FC5CAF2ULL, 
            0xBE20DFB2A71C7BF4ULL, 0x31EE897544A8DB85ULL, 0x82D7A9A5E15877FDULL, 0xAE7E2E8623C5FEE6ULL, 
            0xFD2292D95E37A33FULL, 0xDD3672CAF64EAAB7ULL, 0x0567A8B899AB9257ULL, 0x51756F70E5964578ULL, 
            0x2C875474F23B7B8BULL, 0xF055A01DBDE318D0ULL, 0xFAF4905751600714ULL, 0x0F5C2824B6DD68ACULL, 
            0x43AB9BD5CDB9F8A4ULL, 0xCDEBE51A61841D7FULL, 0x1555CE9DAF694AF0ULL, 0xCAE0A022027CA1A7ULL, 
            0x5111CD76829B3DBDULL, 0xCA4F55BAE577A769ULL, 0x265ED6CE1C56E2D8ULL, 0x7168D1D76C328679ULL
        },
        {
            0xEBEE4DCFAD1B7C05ULL, 0x2362E6EE22F301DEULL, 0x07BE552FAE1F9F49ULL, 0xA0D804240F1DB27BULL, 
            0x95EF0C39B89F8A06ULL, 0xC9B5A2BB6AB0455DULL, 0x8CFB33C777D061BEULL, 0xFB43CED24958EC49ULL, 
            0x541E504C9F56D0EEULL, 0x9AE3F33ECA73856CULL, 0xA4ECF2648FF9ACCEULL, 0x58F1DB183090494DULL, 
            0x09F5FE49B00A3499ULL, 0x9DE1BE90B7C0C1B8ULL, 0x55B4A25740B5251AULL, 0x1978455FA354EBBAULL, 
            0x71200DD7A1A5B963ULL, 0xCC46A22EF8804663ULL, 0x9E6740700787CBDDULL, 0x575A2712F8B2AD5BULL, 
            0xBCB654C07652DF5EULL, 0x378057F7DB7EC0B3ULL, 0xBA402B12F9FBA165ULL, 0x9F3BB12179D4B2D4ULL, 
            0xADEC1C769F97F481ULL, 0x8BA1202D225603BDULL, 0x7A18CC3AF77369F5ULL, 0x042DD1BBA3F6EC57ULL, 
            0x14D82237153C460CULL, 0x5C72DF613779E430ULL, 0x39086E90DF525D9BULL, 0xB3094D2F4E932A53ULL
        },
        {
            0x6C647D8ADA31EB5DULL, 0xD88D10096B92C715ULL, 0x09A98AF3898E4974ULL, 0x580B59638E07F364ULL, 
            0x9C715C6FF73CD56DULL, 0xA6320AA11EBFE1A1ULL, 0xEEC408A1A6ED0A3DULL, 0xA31CF822ECFDC2BCULL, 
            0xC5E8765E97282106ULL, 0x9B154BA7F483CBDDULL, 0x8DE87F23955F06D7ULL, 0x64CE13200B6FF88AULL, 
            0x1E3D6E4D2929CFD4ULL, 0x27779E9F26EB0443ULL, 0x22D0B37B40A47317ULL, 0x9AF1093870D01E4BULL, 
            0x27CDCEC692623EA0ULL, 0x548FBAF8D34EBF2FULL, 0x6DE953D4C1DF9E3DULL, 0x9D4669ADF077946AULL, 
            0x3DD322D7F5D3C0C3ULL, 0x9D068B5D1255BC7AULL, 0xA3D8F743EDE3CE52ULL, 0xA0D4DBFF1BAFBAA5ULL, 
            0x7BDA6CDE64003E45ULL, 0xC9F88CE36D0426FEULL, 0x6929A52B5D6C1884ULL, 0x4D9356F7C1898E85ULL, 
            0xED843436940DD83DULL, 0x5364FEDBAEBCC921ULL, 0x7BB8D7FDF1A17570ULL, 0x65C2E5445C2BC0C5ULL
        },
        {
            0x4C4E83D19E522EEEULL, 0x3884CB46AEA3B5CFULL, 0x42E6973666B6DE40ULL, 0xD88BCB6027A18773ULL, 
            0x48AACDCB78A1518AULL, 0xC9D49392D978E145ULL, 0xB82E0DBCA7DB8FF7ULL, 0x8D77BD8473A118B0ULL, 
            0xAD834CEC8E21B623ULL, 0x38CB87ED3763310AULL, 0x6B2C58ADFA04C0B2ULL, 0xCE29F4958BFB8F70ULL, 
            0xBAF68C5E6E235EF7ULL, 0xC4823C76BB67A71DULL, 0x80F2AD47048A2593ULL, 0x81A0FE2232926B8EULL, 
            0xE39DCBA23CD07214ULL, 0xF860367E8D9B7A3CULL, 0xF18950CCC05556A5ULL, 0xD587562623A0C3E7ULL, 
            0x064DD001EDC522D2ULL, 0xA8B61F675E1F93FEULL, 0x15ECAF8B8532E8E7ULL, 0xD45F48A35DAA0976ULL, 
            0x941FBD54A37E65BCULL, 0x11721ADDF48F9B19ULL, 0x0F2FEF8321398B96ULL, 0x0651ECAA5C1406F3ULL, 
            0xCDED3186AA145E29ULL, 0x3D3822A305DBBEE3ULL, 0x394AA9C0E203146FULL, 0x905A0A388A32FA77ULL
        },
        {
            0xB8DA20ED9382D958ULL, 0xC67F7F9EF195D32BULL, 0xA63C0788976B9151ULL, 0x2014E84C37209707ULL, 
            0x806B74AC63D93FD7ULL, 0x86D418677B746CA9ULL, 0xDB52C864111898AAULL, 0x054870080D957DADULL, 
            0x1B9B1DC4671BC3B8ULL, 0xA283A8C235428839ULL, 0x4F1A9BFFDC2F2474ULL, 0x98F3D3AE062A63FFULL, 
            0xFFE7541CBFDB1F34ULL, 0x4684AD21D586204FULL, 0xC05F0D2E1B36F755ULL, 0xE780A7B683E8D218ULL, 
            0xDA4BD0A6E4AEE9ACULL, 0xF0E3C4DB622186D9ULL, 0xD43FA8569D682E86ULL, 0x177754C1516CF266ULL, 
            0xB264E7649AF261E3ULL, 0xF878C1B1A26A4D1AULL, 0xF62E25C11BACB08CULL, 0x55ED2FED865BEDC8ULL, 
            0x08EB1EEFD48407DDULL, 0x9CC384B7E4D181C4ULL, 0xCF86C2C947F74757ULL, 0x93B2FC52CBD1B875ULL, 
            0xF966B12BFCB5C928ULL, 0xA411986004E11D27ULL, 0x14C3FCFFD590AF4AULL, 0x3C473EB7188B415AULL
        }
    },
    {
        {
            0xC89FDDEE2F8EE12DULL, 0xD4C0EE694C0B43BDULL, 0x51E5798261BF962DULL, 0x36C442EDBC8E511BULL, 
            0xEA6468308C21EE99ULL, 0xF783DEE891B20A9EULL, 0xCA7D0A918E3A3981ULL, 0xF7C3B50F70F6F49EULL, 
            0x9CFF2BED37481439ULL, 0x884F1BB3C2CD7E5DULL, 0x9FF542BF868CDC85ULL, 0xBF3A49AADB7E3B73ULL, 
            0xC667475398CE9C36ULL, 0xCC98EBF50A64ADADULL, 0x028F80272E46181BULL, 0xF67DF7D99B603914ULL, 
            0x7F0B7306E55BB731ULL, 0xFA972DCE7C896FC8ULL, 0xD8F58C1D4B95CD03ULL, 0xC6FACC359717869BULL, 
            0x83C57BA1BEABBD3BULL, 0xE1DD4CA98368E226ULL, 0x2901693317A40F68ULL, 0xCCAA7CDDBF685179ULL, 
            0x7B3112E8552BE169ULL, 0x7A063731FB7EDEEBULL, 0xBB783099B5E94FC0ULL, 0xE752F83CD37D571DULL, 
            0x29F6720D28AA3DAFULL, 0x2291A2F83C3C98A7ULL, 0xF3ACF25E88F1854FULL, 0x20CD588C5E1E637BULL
        },
        {
            0x2D618954DE5CD3DDULL, 0x49B1787949AC383EULL, 0x08455015D969F6F5ULL, 0x7355F68B7C39126AULL, 
            0x9A5F4F892D2F0316ULL, 0x86C620E554EEF530ULL, 0x227394827B470568ULL, 0x8F38F5B228C7276AULL, 
            0xE16F98472640A5F8ULL, 0x7562A8536C5E4465ULL, 0x2CC16FA581B7091EULL, 0x9F6EF1EE5BA93839ULL, 
            0xD2944728019A667AULL, 0x01AF792EF3231987ULL, 0xCEF821372819F25DULL, 0xE4DF6F816815E864ULL, 
            0x3F529D66D501622FULL, 0xC6FCE18103C35CA4ULL, 0x8D9F5C397D2C9621ULL, 0xCFA71A3A4C7BFD46ULL, 
            0x00561F378DDFD921ULL, 0xD74C414FAE9AEFFBULL, 0xFCD3E696E3A5208FULL, 0x6EFCF75036874CE6ULL, 
            0x0E364BCBEA6E1F2AULL, 0x0237A45F5A0E433EULL, 0x164A60B336703EB0ULL, 0x822DCAC93CD788DEULL, 
            0x7B944E3AD2D6B9F3ULL, 0x86A8425BC01D7975ULL, 0x0780574BA861BA72ULL, 0xA3FBEE6351AA9842ULL
        },
        {
            0x74C7AE02B203033AULL, 0x33B97B8A3BF9D9CEULL, 0xD13796BE0D405EEEULL, 0x210578953634840CULL, 
            0xCBA3265C962471FBULL, 0x3CA7B6B61E679F66ULL, 0x129A029B43173AEDULL, 0x7BD1C532AF0F8AECULL, 
            0x05B80BE659256C55ULL, 0x6405CDE399E791DBULL, 0x6A2548BF0EEFB61DULL, 0x1E0602576B00EB96ULL, 
            0xFF96A70927209D70ULL, 0x93358121B158E81BULL, 0x2B822D2F250FAC0DULL, 0x5B77D64366410378ULL, 
            0x2BDE3FE881C773FEULL, 0xA87D98EE9D3C4215ULL, 0xB60B3E5DE314DEEEULL, 0xF19706231335FE03ULL, 
            0x20927C07E55C88EDULL, 0xABF4C3B2F297A37EULL, 0xADDFAB8B0076B10CULL, 0xC365D3A4428D3403ULL, 
            0x5C3589302A5A0D07ULL, 0x2DCC1ACDF56033B0ULL, 0x59FC4360D429E76FULL, 0xB8721170CE4C22DFULL, 
            0x7DB75EF48C5F712CULL, 0xEEA153C5D85E8A18ULL, 0xFD22CED168B80EA3ULL, 0x4950E198561D3067ULL
        },
        {
            0xE0B4D3C48138E722ULL, 0xFA7899689A8684BFULL, 0x494CF567A33C4998ULL, 0xD1C5D9848B709B0CULL, 
            0x2D5DD8CFBBEEED34ULL, 0x8C4F022165EAC4D9ULL, 0xAE6C771499232F5AULL, 0x9F32CA62AD2DCBD6ULL, 
            0x241E8B7118D2ACBBULL, 0x565728AB828AE61CULL, 0xB25EFF58F67D815AULL, 0xF99C688FC80F2573ULL, 
            0x6A83DAE0979D7204ULL, 0x2A68E64EE04AC9A2ULL, 0x9464B9552A8A48C3ULL, 0x7A11BBA7F889C177ULL, 
            0x50A3C17DD7247509ULL, 0xE6776653A3140DFBULL, 0x2384B8DDB8693258ULL, 0x62ACB2939A81CB29ULL, 
            0x85B55DDA43032DBAULL, 0x2A81F0047D4E89D7ULL, 0xBD7D518F62F6B807ULL, 0x40F06043F7A3F86EULL, 
            0x99937DAF1381A89EULL, 0xA5DA0AB35FEDCCF7ULL, 0x9F5F8BB6B2ED90E8ULL, 0xEEB1DE6EE6DB9B06ULL, 
            0x96AC705B0334F2C6ULL, 0x7EA1B43D7BAEF5ECULL, 0x7603FE3758E0A568ULL, 0x654F5641FA6F8F36ULL
        },
        {
            0x1F19BE57013A2D02ULL, 0x25C21FB8A26152B5ULL, 0x0FB2B82DBB13BCFCULL, 0x80C986E5891515A2ULL, 
            0x0DEA46A6F883F28FULL, 0xE902F6B46CC8A586ULL, 0x668A8829D3C4C57FULL, 0x86EB8834E1BD2C1DULL, 
            0x60FFFBC69BBCBF46ULL, 0xF39DBFF2187B7253ULL, 0x6D60A0B9C461CF71ULL, 0x315DAE4322408F42ULL, 
            0x337286637C1D84B0ULL, 0x96B48937C45B177CULL, 0x0C917C7C9A3D0F6FULL, 0x64E31EE5C462FA8FULL, 
            0xA6D3B3B8C2746166ULL, 0xB9629D07B04033EDULL, 0x333094B01886CB13ULL, 0x0FC086190413969BULL, 
            0xD5B1A9526FDB6EC2ULL, 0x8FAB276386084886ULL, 0xCDFFC83368914E7DULL, 0xDA102A0D704EFEBDULL, 
            0xDC0BC3D92395DA02ULL, 0xC9B8BB8727C16C3CULL, 0x4A512F3F74855037ULL, 0x6A5B4BF63500B3EBULL, 
            0x239372492B14A294ULL, 0x2FDE617C1F253B17ULL, 0xB6885B1D9E1D8BE8ULL, 0xB3D9194D27E68AFAULL
        },
        {
            0x60803D9BFD87D3A9ULL, 0xC2F2C67854ED75D0ULL, 0x224A3BDD1F32BD08ULL, 0x4B845789D0347CD1ULL, 
            0x6FBA07D2F8F44FAAULL, 0x8BED2251673AAEC4ULL, 0xE3C5809117EE0813ULL, 0xF0A66FB7D6467D11ULL, 
            0xBEFB40C7D45AC55DULL, 0x2DA111CFF80281E9ULL, 0x0E9B67B27A8CD127ULL, 0xE1FEB1E635553003ULL, 
            0x55A20F4A67E1D78AULL, 0x8AB94B03D42CA30FULL, 0x62D2FFB95FE47A4EULL, 0x76112C8D114E69CAULL, 
            0x3197407D52911734ULL, 0xE561E9EEBD1B3E37ULL, 0x14D860A96E935266ULL, 0x0082A53AE1C274C0ULL, 
            0xC96CAF1D795408B7ULL, 0x729368B5CDF7813EULL, 0x9FC9728AD9C12590ULL, 0x7F09E660AE54E20FULL, 
            0x418C966BA268322FULL, 0xD26AFBB1F587C1E3ULL, 0x8090D5A9536508CEULL, 0x04E8DA4427095508ULL, 
            0xD5B15D1C15F6BFCDULL, 0xA8EB04FF73A758DAULL, 0xB94AB927FDD7368BULL, 0xF5F333333090D334ULL
        }
    },
    {
        {
            0x911F185A962618ABULL, 0xE66A0591F3A12506ULL, 0xFAC2F5D5A034CEEBULL, 0xE5F4DFF626E6E678ULL, 
            0x1DDFD392CF656BC9ULL, 0x4D768FAC90ABFE88ULL, 0x9A8DDF97EE7181DFULL, 0xAD88F179A2AB4A58ULL, 
            0xE2B29906AA584DCDULL, 0x1540AE1C629A1938ULL, 0x82EF7B0A9087A8AAULL, 0x4E9AE241BC35D953ULL, 
            0x38E0A6E79794C9F4ULL, 0x7FE9A4B67A58D730ULL, 0x85C0BCF3AFE50E45ULL, 0x2CCC4C85AC8B6DFAULL, 
            0xF9FAA1C75B96951FULL, 0xFAD2C539832919C8ULL, 0x6BDC0DA9F979424FULL, 0x821ECB53DE026DC5ULL, 
            0x2E887B721C29E799ULL, 0xF8B683185B9947D4ULL, 0xC0926302EC223E06ULL, 0x979C604DABEC235BULL, 
            0x36E72B7B621060ACULL, 0x87780CCA676E849EULL, 0x1E9B2E3ACED5A25DULL, 0xF2BA84B616E2D2CDULL, 
            0x5E4EB891200270F1ULL, 0x159F5107062DF9F8ULL, 0x044B9D3BA2E53ACEULL, 0x6BEF7703F9FF15DEULL
        },
        {
            0x47DAA1378124B4ABULL, 0xBFE58B3321581538ULL, 0xE494478B7EB61B45ULL, 0xB1525A6D41E55F8BULL, 
            0x441CF532A98D5EBCULL, 0x994B5197935FD50AULL, 0x31476FB34B1C7C51ULL, 0xA09B798A3D805E41ULL, 
            0xE7D6A672E5FFF007ULL, 0x85D38AC449CB46A0ULL, 0xE675D15957E4A915ULL, 0x3D503EE3BD854FE9ULL, 
            0xA8949A920B658014ULL, 0x40AF8791DE477450ULL, 0x9C3C49CDD7EFC08EULL, 0xC7DE1F3D229B6D19ULL, 
            0xD5CE440A0FA4BB21ULL, 0xDF079E77F76D555FULL, 0x23E0C48121C32EC1ULL, 0x36921EFFD08BF539ULL, 
            0x23E62A2FB9F4C564ULL, 0x856DC51889CF3514ULL, 0x2DD4A9FE4F1AB1A2ULL, 0xAEAA697AD9F4D5FAULL, 
            0x9B3B5EBE25002EDDULL, 0x38311C9A4A63A277ULL, 0xC8609EB5E7391E15ULL, 0xAF21171A8887F5BCULL, 
            0xA6CC6889983D10C2ULL, 0x4B032123FBC17F22ULL, 0x0287B2C9CBAE4660ULL, 0xEBC20B1774870476ULL
        },
        {
            0xAFD2B9336C7745F4ULL, 0x77557F871175ADB4ULL, 0x3FED31B15E1C0154ULL, 0x8DD0870FB4A9D137ULL, 
            0x8781295548C03CB6ULL, 0x5938D2F99ADEFE35ULL, 0x6CF0053C4D1FF079ULL, 0xCA6AADB4744D3C12ULL, 
            0x031FE50510527828ULL, 0x1B374651C61AFEEDULL, 0x1B1D8686EEBC8890ULL, 0x323E1C2034AAFEF0ULL, 
            0x1FFC318573DA634EULL, 0x122BA7553AD44FF8ULL, 0x5068F99E79F1F3B2ULL, 0xA6B61E7C7B7B0603ULL, 
            0x3475259D76B1C342ULL, 0xED711BD32A636550ULL, 0xB36C31E07B72D983ULL, 0x55421E8216377ACCULL, 
            0x3E44A580FAD51912ULL, 0xEB0B7C3F2FF909E9ULL, 0x6F82ABB2A64B2486ULL, 0x4F3AA5FFCFAA4F0BULL, 
            0xFD9E74FE427FF525ULL, 0x6224D2AADC7410E8ULL, 0x167CD011E31B111BULL, 0x78200A3BE6D65F1EULL, 
            0x6CB4A7971091D23AULL, 0x3545CFA6496B9D9EULL, 0x2152367406EB580BULL, 0xCB9CB855D22FA8A0ULL
        },
        {
            0xA161244F44597766ULL, 0x7C39C0B950A665F3ULL, 0x9AB5B6E7E766B0BCULL, 0x3345EE57911789CFULL, 
            0x3E152EDFAB073E90ULL, 0x2F8973176E9CB2E2ULL, 0x3EA68916C117B509ULL, 0xF23447DE870D4C31ULL, 
            0x604078F42AD7999EULL, 0xB8665A3BAD9E543AULL, 0x0C298C0BAC8FA308ULL, 0x4D6BB45C398C01CAULL, 
            0xD665A0B3A3A8532BULL, 0xE1C481053779CAF6ULL, 0x89A32D3476612C29ULL, 0xBCC454C61F973DEDULL, 
            0x16AA6E0AEFDFD664ULL, 0xD33F20D1A1AAE7FDULL, 0x8D3550241AC78EEBULL, 0x07D05EEA38E8483EULL, 
            0xBC2727E12990E29EULL, 0x16370D7D7B51455EULL, 0x707F1C9B0499D711ULL, 0xA8E9B893732C4629ULL, 
            0x0CACF03E0054E959ULL, 0xB4C32F4366407912ULL, 0x1BF307398FF0E2DFULL, 0x2FDAB14DE5CEB629ULL, 
            0x67E3415BECD2FBDCULL, 0xFFDE4071248BA619ULL, 0x1A67D561DF9CCD75ULL, 0x3BFC9839D24E11DCULL
        },
        {
            0x9E10B3AE2F57F928ULL, 0x14F681C4D59E2BADULL, 0xE8DB59FF1566F5D3ULL, 0x4C505D5965BE6FE5ULL, 
            0xE3DEDCC2E516DAB4ULL, 0x6CB910627810F058ULL, 0xBCBAD83360B9251DULL, 0x077D0249014B90D7ULL, 
            0xB12B6C9D15314A83ULL, 0x0B30A27574E2B3EEULL, 0xA7A8BC47606E640CULL, 0x68A6D07CBD858729ULL, 
            0x8DADC16C901AABF6ULL, 0x82341DDF4E92FBB5ULL, 0xE51CE70C52DE1B25ULL, 0x7D6D68CAAEC66D46ULL, 
            0xCF3C6FDC98D04F50ULL, 0x8502313C41D5DE8CULL, 0x7AB32893C920D63BULL, 0x0034FE503A604FC5ULL, 
            0xA9B3635EB8537960ULL, 0x3EC9B8B359FA6083ULL, 0x729512CB790069ADULL, 0x6933C7FE324172CBULL, 
            0x58B37549E6D88D4CULL, 0xA847F3309B46D18FULL, 0xE599BC2DDB4C435FULL, 0x1025AD6177FAC961ULL, 
            0x4CD4CF22E487E335ULL, 0xB96CCA37E324B7EDULL, 0x7A424CE193AFB5BAULL, 0xD7E5A4F5DAC07D49ULL
        },
        {
            0xC94445B71721C835ULL, 0x33B1AA24EF0A0E07ULL, 0x71EE911BA61FCAFBULL, 0xE671BDC62E62804FULL, 
            0x9C5E2CE95E0348C2ULL, 0x15201B07B611044EULL, 0x75849FD510F9F4C6ULL, 0x421EF024A5BC7296ULL, 
            0x23409F6EFF3200EBULL, 0x83C7407E44F47C34ULL, 0x79D0084F95E921BCULL, 0x6091D1888BD6EEF5ULL, 
            0x6CBF42139724CB7DULL, 0xE5F6EA9275232AB8ULL, 0xC8BCEC6E41872CC4ULL, 0x4DD02F4E61F96E46ULL, 
            0x7FD78AA6D2B3AD63ULL, 0x297C65F460B42FFDULL, 0x0CBD3ABDBC67FCB1ULL, 0xEA402FAF3641AC4FULL, 
            0x9BCDED0505D04A0FULL, 0x247040EBA415C338ULL, 0xFDFA5101A5443724ULL, 0x395DCCE43CD1A681ULL, 
            0xD06C6468E5EE2F7EULL, 0x42BA33447B8E2667ULL, 0xDD778ACEC022428BULL, 0x013ADA18BE7FB527ULL, 
            0x267C4E56598461D5ULL, 0x57E99B84C6108A6BULL, 0xACDFFD436008A8EAULL, 0x48DAB64DE04E4153ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseBConstants = {
    0xAA2DDB0F496858EDULL,
    0x73FD29295DE1690AULL,
    0x6F2A0EACD17216EAULL,
    0xAA2DDB0F496858EDULL,
    0x73FD29295DE1690AULL,
    0x6F2A0EACD17216EAULL,
    0x7AFB8C4F957F878FULL,
    0x60E67FEB56BA9B91ULL,
    0xA8,
    0x93,
    0xB6,
    0xFC,
    0xA7,
    0x61,
    0x4A,
    0xCF
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseCSalts = {
    {
        {
            0x171AB61FD4F5FE40ULL, 0x503EA60D8AB26FB6ULL, 0x43FA9AC76D9A47CBULL, 0x69312107C2225205ULL, 
            0x69965B45BB93E6EAULL, 0xBFDB0A10FB23EBA8ULL, 0xAE84369E0C421983ULL, 0xE433153A648165DCULL, 
            0x6B9D075908D2A09CULL, 0x660FF73B13AB5AC6ULL, 0x0156E234A609F09FULL, 0x3CAB0D7B8D04CAD9ULL, 
            0x3299DE7E173AB320ULL, 0x82AA9E7BF31AECD1ULL, 0x82B587A8C6943E73ULL, 0xD97EA964EC37EA2EULL, 
            0x49C71158793BDDE8ULL, 0xA9F4BFAD8B4D212CULL, 0x2D294CB3FC6721E6ULL, 0x88A24DCD5E50CE25ULL, 
            0x711752FB5AA03988ULL, 0x5DEE9CB8B5089B1FULL, 0x07A4A6FEB88C281DULL, 0x31052661EA22C416ULL, 
            0xC4FF69D7E23D4FF6ULL, 0x549B2987BA4A852EULL, 0x181D80236F42179FULL, 0x35197E55E5D2F8CDULL, 
            0x138538999A36A271ULL, 0x6628676DD44376C3ULL, 0x405458D22208EBE0ULL, 0x9365C5C20C1596F4ULL
        },
        {
            0x5A056B90C43C8771ULL, 0xE22397611957FA52ULL, 0xB532E5AE9FB2CA9FULL, 0x736D02590A82A8EEULL, 
            0x0C405399E1047B8DULL, 0xFEB52364FD35C42DULL, 0xAD154DB7583788C0ULL, 0x7146DDF16F0A07C3ULL, 
            0x877A1C5E2B4A5946ULL, 0x422663DB450D239BULL, 0x63274BA6C569A56CULL, 0xBACB85EECDE980A7ULL, 
            0x89257FC45C56694AULL, 0x14F3985024FD4101ULL, 0xD4DDAA131583B30CULL, 0xA4C546C71E9A42D6ULL, 
            0x51619C1F7075F817ULL, 0x47D44455BECFC261ULL, 0x0A636DB166BCAE29ULL, 0x34C21D91A8D9FB4CULL, 
            0x53479E1BFE315887ULL, 0x5D40E50B2665501FULL, 0x817DC512F71AB1D6ULL, 0xEAEFA10AC721028BULL, 
            0x672F7BCD99F8B76EULL, 0xC15FA7BFD303EBFAULL, 0x31F0987B3D686BA8ULL, 0x3C61D93CC13938A9ULL, 
            0x67B4A844A30B43E1ULL, 0xAD7F6B9DF95ED1E3ULL, 0x6D22FF36ADCE13A2ULL, 0xE43C7A969950F2C4ULL
        },
        {
            0xF91F6C94F76547C7ULL, 0xDB4021E52DFBAD13ULL, 0x7D8896F96A380554ULL, 0xD950748925B94DC4ULL, 
            0xEDADED3C4B731154ULL, 0x197BA85BB020E146ULL, 0xB53D443CA9D8EF80ULL, 0xA1D24E2C1430BD2DULL, 
            0xE1669B070F7CE4C1ULL, 0x46CCA6A493F238F2ULL, 0xA7C0305FEA15688CULL, 0x87A420D86870E811ULL, 
            0xF507117515082949ULL, 0x2F0AF61907F42C5AULL, 0xA3102D67BC6BD980ULL, 0x8B8BBE5B983233FDULL, 
            0xE406EE41B3CDA814ULL, 0x84BF4136D9923C1CULL, 0x6DFD7BB91CBFAF4EULL, 0xE13A448982F2148EULL, 
            0x588EF8F72B1F804BULL, 0x8F4F12774A4A5714ULL, 0x316F9E7A6CAF7553ULL, 0x27ED97B8559A618BULL, 
            0x2B455FF1CFFF2DFDULL, 0xA300EB8481A692B9ULL, 0xCB06A4F1E8DDDAE7ULL, 0xA08B08642BE72C97ULL, 
            0x593AB69BB0677A3DULL, 0xD65B2D3530D78B62ULL, 0x4F68AD58BDDED44BULL, 0x884B485EA928E5BFULL
        },
        {
            0x514B94610EA8A4B8ULL, 0x77C0DB75B480667AULL, 0xFAA75D646600ED3BULL, 0xBF46B9FAB7BC3D6AULL, 
            0x6D54E5D2AABA5596ULL, 0xC70C31EE3D5E5696ULL, 0x8A26F22552CC4467ULL, 0x64784F1D3DC62029ULL, 
            0x0EA89C9CD3D43288ULL, 0xC8688457C350F365ULL, 0x1ED2D154BA8C4594ULL, 0x01324927E0A41E35ULL, 
            0xD21ACA7A545275DFULL, 0x5BC72CC3F979B98AULL, 0x6AD4BB727BF0039FULL, 0x05D72F6A83012BE0ULL, 
            0x6750F117D046D6C5ULL, 0x89367286C6B7F790ULL, 0xD2E7470B7782142BULL, 0x50F93BED0622CF91ULL, 
            0x199395EAD1BC2C5EULL, 0xA3889C76BBC416A4ULL, 0x444BC2DFFAF6DFD6ULL, 0x8F8ACC00BE889F81ULL, 
            0xF199E8EFD9113EEFULL, 0xA1C392BBCAAAD473ULL, 0x96B45A26E55B51DBULL, 0x340C2C2393E89061ULL, 
            0xCBA7BD5FDB8A316AULL, 0xBAE633795E393B21ULL, 0x71E3013CDAFFA3F1ULL, 0x5F9381F93D819C3CULL
        },
        {
            0x61C9338FB6EC4AB0ULL, 0x61F133442E759913ULL, 0xD707F97A80821689ULL, 0xFE9BB83D068C42CBULL, 
            0xE5AA7E07871AC02BULL, 0x2C74BC58D7F68836ULL, 0x1453A819CEC2B8DEULL, 0xD4E947055BF8EC31ULL, 
            0xA8404C50B1888179ULL, 0x616D754AAA2D5C6DULL, 0x2EADA60F802B1129ULL, 0xCA62DE960D6A03DEULL, 
            0xDE60C04C07AD6AABULL, 0x2803BC0B3568F7B4ULL, 0x0F0D94988D7EC810ULL, 0xD0D9499EF5DFABF0ULL, 
            0x5BD5FD6E0CD672A5ULL, 0xC4794EE45B1B3C0CULL, 0xEA0740F53F5DB2AAULL, 0x0A2587D3ED197849ULL, 
            0xA3C1AE9FF649DB38ULL, 0x9A9F2C308AF069B3ULL, 0x9F0B8B553FD7189EULL, 0xFEC4F1B89A89A297ULL, 
            0x2E9AEB466DF25888ULL, 0xE5CF47AF269DF3C2ULL, 0x959EE89AE086B5F9ULL, 0xC37E5363B58801F8ULL, 
            0x89A41AA0A37F46ADULL, 0xC3BB990835CB45AFULL, 0xE2F012862FCB8562ULL, 0xFAA6BD3F9FE23B70ULL
        },
        {
            0x56387198C43C993FULL, 0xDEC40E0906ADBAB2ULL, 0x3DD067D9F60F1F01ULL, 0xA89602C2B91A62FBULL, 
            0xA49350BB1DE246AEULL, 0x35A0B9452799E88BULL, 0x214749760DD1ED7BULL, 0x202BA025CFC2B567ULL, 
            0x8D662F88A3DB44B4ULL, 0x21323B533449A995ULL, 0xFF049BB06CDE61A4ULL, 0x75E6E9BC0608CF08ULL, 
            0xB6EB085AAA4422C1ULL, 0xF463AA8870300795ULL, 0xBF53427A166B4C66ULL, 0xACA3C1B7AB17FBB2ULL, 
            0x7E525CB60B4F2B82ULL, 0x7A866188FD2C5051ULL, 0xF104FC101837CCCBULL, 0xC79D389D11E59022ULL, 
            0xAE17345FD936E197ULL, 0x96295C90313FB061ULL, 0xD33942AF40E2379CULL, 0x375B1EA79F6EF7F6ULL, 
            0xD51E9950E7057A35ULL, 0x0AD4686A7DE34054ULL, 0xE21C05ECD40C6B15ULL, 0xC4B2B69824A45F13ULL, 
            0x7CE81233D4A5F95CULL, 0x8A753E959664CC75ULL, 0x95D64DF7735A5B9EULL, 0x28660E8B6D09912CULL
        }
    },
    {
        {
            0x960E5C4CAFABBB1FULL, 0x4879956424A8EED6ULL, 0x68DE80CDF6286448ULL, 0x4BEF61EB895791A2ULL, 
            0x2A93B080E6D4CCFBULL, 0x0E1DC3B2E151A137ULL, 0x9455ADA0A0392968ULL, 0xEC612888E93BFCFEULL, 
            0x0596A73FAA3C13DCULL, 0xAD218C7FC0D32359ULL, 0xFFD80EB8D5CC2A65ULL, 0x64B60989DC9C2FA2ULL, 
            0xA4999E7180A1CC16ULL, 0x1EB549F85CD5C1F1ULL, 0x998270B1D7534B0FULL, 0xF45F4C0AF8E2FCF0ULL, 
            0x7D195A34C52DDAC0ULL, 0xC9718436BFB1369FULL, 0xD187ADD5EA0DAE1CULL, 0x3074975894880DE0ULL, 
            0xE0A691FE5A7FFBDBULL, 0xE873CDB8043124FBULL, 0xE9343C61BC8B375AULL, 0xB490E9522496E9EDULL, 
            0xA367041A5FD56A6DULL, 0x2A2ADEE0F2A51521ULL, 0x48CF8798E8F8FDFBULL, 0x108659D5D1C23019ULL, 
            0x7ABD9318367CE7B8ULL, 0xDB8ADBB87758C6BDULL, 0x0A883805C12F751DULL, 0x6B97126D1F405E1BULL
        },
        {
            0x9ACF399E47343BF1ULL, 0xCBBDD8912C9ECF5AULL, 0x842D1AEFF7BD7757ULL, 0xB37D20CFEBBB1577ULL, 
            0x8324F719DFA4275EULL, 0xF22EB5B3D862773FULL, 0xE00D813F3CB8B12AULL, 0xF901378B54EB7039ULL, 
            0xCF68D5827BAD2BF3ULL, 0x009E490B1CD7FB83ULL, 0x9AF665212129B2D9ULL, 0x8B52582F9B8646D5ULL, 
            0xACECFC08ACBB35D3ULL, 0xFBD4344FB7E320DEULL, 0x721E052350030F38ULL, 0x49954960CA8BEFE5ULL, 
            0xC995CB88B3F61B40ULL, 0x7B410CF779A2CF27ULL, 0x5338423348236F02ULL, 0x6B8CDFB3679D0D17ULL, 
            0x22564DEC063B8558ULL, 0x4B9A5B023D115A3EULL, 0x86FCCFD6866C8143ULL, 0xF8C34D81989C70F3ULL, 
            0x422F2E4F62689DF3ULL, 0xC0DBAD34E4BF67DFULL, 0x809EA7148FBADE44ULL, 0x128B905A1D286218ULL, 
            0x119903C7B61F9C94ULL, 0x6F83660307FA7A17ULL, 0x4DB1F685EFFC5BC4ULL, 0xC238E079A0D1869EULL
        },
        {
            0x5445C49406D3AF81ULL, 0x21F827BD76323DEBULL, 0x31718327F231DAEDULL, 0xC142A5B33992256AULL, 
            0x4DAF412EC6811E61ULL, 0xB5840E13190F5644ULL, 0xD31D75689465400EULL, 0xB70AFFA37682BC18ULL, 
            0x19568C9703E5F19EULL, 0xAFEE36DF7B5F0156ULL, 0x3BEB2A002D70E089ULL, 0x531FA407BB5E08FCULL, 
            0x9924CC6FE9B3DD8EULL, 0xF6D9A4FE051A9582ULL, 0xCC4D682F3ACA47E5ULL, 0xAF36D7D692473069ULL, 
            0x196DBFB44950CD3AULL, 0x5E1DA038E7FD18E3ULL, 0xAB48314896DEB005ULL, 0x0000348273C884D6ULL, 
            0x297015CC06A8287BULL, 0x831D68CFE93CA688ULL, 0x6FBFC1D230AFC1FBULL, 0xB515AC90CE63718CULL, 
            0x06803D675438E696ULL, 0x81F7E38CDABA43DDULL, 0xF9C95A0E2A021A19ULL, 0x24AF71DA63B37A8CULL, 
            0xC9204F4641993D93ULL, 0xFEF54CF9641C533FULL, 0xAD453F7267629CA1ULL, 0x877E32BD88FD4324ULL
        },
        {
            0x68E85441517E2760ULL, 0x0D3CE4F0786603AAULL, 0x19E9A398C72B1FCDULL, 0xDF94431A0FB38B1CULL, 
            0xAD6C8AEDAB1E3BFCULL, 0x8497F14281AB11DAULL, 0x0D6CB28DC903DC6CULL, 0x8A4EBC37FFA54FE6ULL, 
            0x009D8E9A4A29263DULL, 0xC97510DDCB7A575BULL, 0xB7423F898E38113BULL, 0x1A1A5589B274329CULL, 
            0xD8315F22CFBE3B9FULL, 0x154EC255BCB8332EULL, 0x26645EF904CA4751ULL, 0xC91073EC4BD7F20DULL, 
            0xBF14567CFEEC1660ULL, 0x4F799749D0748547ULL, 0x00D52A880024211EULL, 0x3640CCAED96F4288ULL, 
            0x2EA9E4C5848102B0ULL, 0x9B23C6195B7A9E2BULL, 0x67825B59F5850A3FULL, 0x369C519F5AB22F3BULL, 
            0x5116FE13290CF384ULL, 0xFAE9E264113AB71EULL, 0xEEC8F02E015B6C37ULL, 0xDFD5F2F841DB2749ULL, 
            0x01405A4DE4060267ULL, 0x0D7679C0C0A83CEFULL, 0xE8BC00813BE2E592ULL, 0x6616D0B4B125872AULL
        },
        {
            0x082F286E9C58CD39ULL, 0xC2EB1A888A9070AEULL, 0x1D8CFABB44622FD0ULL, 0xFAC61396FAA857A5ULL, 
            0x73AEEC500CD7DF61ULL, 0x7EAE59273B6B4F88ULL, 0x1F16D628381941BCULL, 0x01F9A62BE72E1927ULL, 
            0x70F77AD4D37C3004ULL, 0xC83ED31F081CE94DULL, 0x60089D875375DE34ULL, 0xF0F6BE8A924C87B6ULL, 
            0xDBF281247D2DBD4EULL, 0x320C494F212E7351ULL, 0xD7702366CD7BCD16ULL, 0x82DF26E214439DACULL, 
            0xA75E994CC0A93832ULL, 0x7CFD3CA418AE16E7ULL, 0x028F94DFE1EC8877ULL, 0xF2E1DB327144BA5AULL, 
            0x9D06E952145E9A87ULL, 0x726BA19FBBBF4B61ULL, 0x023A6683D38E0F71ULL, 0xD6D1CAA5D332424CULL, 
            0x979876D83A78BA40ULL, 0xAC906D75EFEB7DD0ULL, 0x859A592C7BFB564BULL, 0x425BECD9D53240F5ULL, 
            0x5FCB404F692262DAULL, 0xC0014F1B0B8DB1C7ULL, 0xB8754F4FCB62FFC7ULL, 0x295F4360CE7264E3ULL
        },
        {
            0x3EE2472E26FA034EULL, 0x6E79A707237BF40CULL, 0x7AF957E908CEE879ULL, 0x14B8CFAF2D80DE70ULL, 
            0x8038FC4A4EDBD037ULL, 0x8F6D1254D213F5F8ULL, 0x2D044ED5552FD815ULL, 0x8558111CB57B9F45ULL, 
            0x1E71B83688225A57ULL, 0xBAC14009EFE14781ULL, 0x65C0806EF07589F8ULL, 0xBD62C868911E5B29ULL, 
            0xAED6624FC877FCD3ULL, 0xE2BDF40ED608CF6BULL, 0x0D6F8B050B25B440ULL, 0x0DD5028A22E679CCULL, 
            0x77A04F41ECF0AA22ULL, 0xE744A1BFD77D2006ULL, 0xEEAC7D8B0A9EBB80ULL, 0x9535B17DA8CDFC9BULL, 
            0xCC056F5D70B15220ULL, 0x6BBA6BFD24E3E029ULL, 0x5824C904D4D274DFULL, 0x150BE1B8F04E3874ULL, 
            0x61A13B851752E625ULL, 0x49F2315FB0245D76ULL, 0x713F96757148D5DEULL, 0x61764BEE793523C8ULL, 
            0x92A6DB478239F98BULL, 0x4903868F167753E0ULL, 0x5C4AA00C4C1F9E85ULL, 0x6DA3DAC281E4F583ULL
        }
    },
    {
        {
            0xCEA906B6196A5DD2ULL, 0xAAD03F07F5ADEE76ULL, 0x88B58296F294E565ULL, 0x67273EFD509E8CABULL, 
            0xD05EDA9AB2842F29ULL, 0xD4E6C6071658A051ULL, 0x006B3CA534C3BE02ULL, 0x466B9E1A58056453ULL, 
            0x3D4DE7ECC8884917ULL, 0xCE9A5AEDDD76B610ULL, 0xB63B1EE45DBF22CFULL, 0x9182BAAA4E8466C9ULL, 
            0x2EBE56EA3DC77AEEULL, 0x65CA43E0B4EAB738ULL, 0x211D6F31DC42539CULL, 0x69747DC90018E9D5ULL, 
            0x8F030FEA9636F66DULL, 0x9C263771461514E2ULL, 0xE07D701623D87BFCULL, 0x72736E4B64402612ULL, 
            0xD81C40AC12B00557ULL, 0x6AFE444BEE1FEE2EULL, 0xFC70FA6C47AA1AB7ULL, 0x297793743CD5933AULL, 
            0x10BAC2CD49658C4AULL, 0x85DCF8F1232B6741ULL, 0x820F7A131EC38425ULL, 0x5178C849523EE97BULL, 
            0x923FD1891B1E3633ULL, 0xDE5C0B8F9371349BULL, 0xC4367992DE076962ULL, 0x72970A8525F0BD74ULL
        },
        {
            0x7FA5CFEFD788D8E3ULL, 0x85B677A8B080C66CULL, 0x900BDB68C5430054ULL, 0x2FD30CD6FB6C4BF9ULL, 
            0x90842C74642E0314ULL, 0xBE249C69F2CF8598ULL, 0xF8742E312345B534ULL, 0xB5ED513F0127B2B8ULL, 
            0xC862F571E5C362ABULL, 0x6B0BC983EB6162F0ULL, 0x5B3DA8DAC0EAEF1BULL, 0x86BE9B6ED7E743EDULL, 
            0x3D85B060E7C0D1B4ULL, 0xFD1CC03BE90A21D7ULL, 0x60E741CB727CEE36ULL, 0x996DC695B7CA7FE4ULL, 
            0x307D25706311353CULL, 0x5A7394C548D8F557ULL, 0x068EEB5EE02497FBULL, 0x27E77C8F75A5C9ABULL, 
            0x0390D15D839AC8DBULL, 0xC8C2FB7E5F081C05ULL, 0x3B1898517B3A1217ULL, 0x1A26EE5BF5DFDA31ULL, 
            0x475DF68949C35E70ULL, 0xDE0568FACE83148CULL, 0xDCD0199B63935623ULL, 0xAF285D9249BF05CDULL, 
            0x272F793E3C50F936ULL, 0x34758DFF55D4FE00ULL, 0x99B1763A0A73AF47ULL, 0xFB05ABE1FA7DCDB3ULL
        },
        {
            0x98581C792478B551ULL, 0xF3F2304A349C8165ULL, 0x3EDD91E287A25B9EULL, 0x5D7A9B3579DF57C1ULL, 
            0xEDC75C18CE50AB53ULL, 0xE30733D40EA430ABULL, 0x95E30F47B2888770ULL, 0x12FD9E9624930B29ULL, 
            0x91B7D5D88610A3D8ULL, 0x7D7CD60A3382571BULL, 0xBF6B9BD3DE7F0B5AULL, 0xAB05A40F57FB1602ULL, 
            0x6ED1B4D6ACDC3B0FULL, 0x3AB47E5866D592A5ULL, 0xB12B5B6EE8152BD0ULL, 0x961FBEE964F2E72BULL, 
            0x30B1C91DF5B03159ULL, 0x53B1BCA2C05021DCULL, 0xD9B0BB13A676F671ULL, 0xFD2469E5B622808DULL, 
            0xFAC0DA8C27FDD7D1ULL, 0x924BE9C7EA85F2BAULL, 0xF592D8B59FA23A84ULL, 0x5FD803EE9C5E6EE8ULL, 
            0x5A0251A9707679B0ULL, 0x50984D444B0DB876ULL, 0xA9D22B3F3852346EULL, 0x1F06E59A59870279ULL, 
            0xFBCA309AC7AF65F1ULL, 0x265850434466CEFBULL, 0x50709FABA9E2386DULL, 0x4C3159DBF736079CULL
        },
        {
            0xDDAEE836467821DFULL, 0x72AB71D31A006C1CULL, 0xB7B02D7344EE81F9ULL, 0xFC31A69D26957D49ULL, 
            0x77A41833AE48F9BAULL, 0xC908BAEB9E1DE154ULL, 0xC90FC2F605D46CCDULL, 0xF4A6F7CC31D65FCFULL, 
            0xDF994974EEA93511ULL, 0x0E7A90BE210A3E3BULL, 0x2CF0C1B4523AE4B6ULL, 0x88982AB119CB8768ULL, 
            0xFC2E231CA327AE04ULL, 0x6AAE1FBE200FEAB2ULL, 0x87CEE48326C4CD59ULL, 0xFF72160DC52E58E0ULL, 
            0x597ADA49836C2424ULL, 0xAC1F8CDC59F29AFCULL, 0x972741E7422810EFULL, 0xECBD4406A2A58820ULL, 
            0xC41D06489A22BDC2ULL, 0x74766C7069928C83ULL, 0x7A4F65F25F894C19ULL, 0x5C738A2221F95F7AULL, 
            0x568D9B986D9A1BC5ULL, 0x5BC25F2E60370D3FULL, 0x7412C01988A2E9BEULL, 0x1777531FC20CC8F4ULL, 
            0x4FAA5719522798E0ULL, 0x1D81718EF73E81D7ULL, 0xBF0F1FE55123795CULL, 0xB4E589DF5ED3720AULL
        },
        {
            0x2A742664B76A042DULL, 0xA2352E0157AFC5A4ULL, 0xC212BCCA24F5D1E2ULL, 0xFCF09960CD329019ULL, 
            0x510235057D60FB70ULL, 0x8E7F9D069BDA4E53ULL, 0xCC0C59167C7295FEULL, 0x2957710757A00B75ULL, 
            0xEBDB68D8759EC3E7ULL, 0xA37EF03C2EE5FA73ULL, 0xE83F28A8117FA894ULL, 0xA374610F4EBC57EAULL, 
            0x7C8D44891FBA903AULL, 0x9B38D43BFA53C053ULL, 0x6D402C5FE9AB95B4ULL, 0xB5B31463DB9D6B8DULL, 
            0x432B0ADAAB0013A2ULL, 0x680A4DBCC74D6FC6ULL, 0x6871C3B711F35B7BULL, 0x4EEE79B232395546ULL, 
            0x6E368A387BE82817ULL, 0xC940DF907F13A961ULL, 0xAC6CF04A9C4D6AC4ULL, 0xECD00334B629D061ULL, 
            0x6ED5BF5B976CE26BULL, 0x0D7B2CCF5DC561C4ULL, 0x578F20B6CA363D72ULL, 0xA94785734D74A378ULL, 
            0xBE0D33EB62AA2DA8ULL, 0xA4610410B46D8E19ULL, 0x3874F5AACEC12E8CULL, 0x58398E5E55C42003ULL
        },
        {
            0x774E1DDABE714337ULL, 0xE05804943D0C2688ULL, 0x86EF6697C6648267ULL, 0xCFD36552EAB564EBULL, 
            0xB2199BD6BE3A962CULL, 0xDC5EF06BAF11504CULL, 0x8169DA1CCA459F69ULL, 0x1C86A3CADF9FB80AULL, 
            0x397D76D01898FEFFULL, 0xCC636A8569896814ULL, 0x5B2B09C7F76FF0FDULL, 0x2A219340CB8F021AULL, 
            0x489AA9A2970D1821ULL, 0x6E4537760FF770A5ULL, 0x13CC40D2592CB889ULL, 0x32F6576F99C9A362ULL, 
            0xF9C1D42E8750D98DULL, 0x95B7FA14A920D4B5ULL, 0xFF4CC4FB1518B479ULL, 0x44A4ED2E4B52A494ULL, 
            0x057466DE03CA37EDULL, 0xA51638B29BA415C7ULL, 0x43D2B344306B75BBULL, 0xFED2FE81650521F5ULL, 
            0x648EAD39AFFF577FULL, 0x48E9491F054CD17FULL, 0x0307C9B1F5AA4E8DULL, 0xEE0F2364F42F606CULL, 
            0xB5AF7DB9509D5FF3ULL, 0x0CC50F0157F87BBAULL, 0xDF7F254D7F3C2287ULL, 0x1E3102513C190C2BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseCConstants = {
    0x39716581C7FD7AA2ULL,
    0xC9D5252F63071BA2ULL,
    0x676743C8522CE6A1ULL,
    0x39716581C7FD7AA2ULL,
    0xC9D5252F63071BA2ULL,
    0x676743C8522CE6A1ULL,
    0xF6B7865757AE7861ULL,
    0x99E08C2446BB1909ULL,
    0x8B,
    0x4E,
    0x26,
    0x4A,
    0x61,
    0x89,
    0x35,
    0xA6
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseDSalts = {
    {
        {
            0xBE7BD5DFCCDD476FULL, 0xDFC043E7BE942117ULL, 0xA6BDAE69AFAB0D37ULL, 0xFDF7CC485A5E1AD8ULL, 
            0xBED5A9B872C9B757ULL, 0x0759D56FBC845D7EULL, 0x0A8B4B4FBEF13C66ULL, 0x97C202E6B93FDF7EULL, 
            0x89D93B4B33DA42AAULL, 0x2ABBB54D24E4EFB5ULL, 0x2F6F68B6878B2951ULL, 0xFC7E1F1C2A5070C9ULL, 
            0x879D563E477AEBA9ULL, 0x34B194BF7FC6724EULL, 0x3A0ED85DD7C0308FULL, 0xB2774FA94B478233ULL, 
            0xD30A7F10DA524867ULL, 0xA4F3EE7AA1BCB7A3ULL, 0x7F98EA6F0F37305EULL, 0xF3C9B43653213DB6ULL, 
            0x40DCACCECC86E75FULL, 0x6FFE49A67CCFE78EULL, 0xBC8C324414563A6CULL, 0x9D2B7EC7F273BF3FULL, 
            0xE5418E781FA1B4AAULL, 0x0225A96FEF1BBDFEULL, 0x7470763AF1477431ULL, 0x547E0ACBE13FB1B0ULL, 
            0x6929849DC010D64FULL, 0x0EA23C0057843948ULL, 0x774A8B288A525D9CULL, 0xC8E4D67BFF633C55ULL
        },
        {
            0xE76CFDB7B7BCCF04ULL, 0xF40AAAEF9C1513D7ULL, 0x04B0FF0160ED7700ULL, 0xD883236ECB352D2DULL, 
            0xB043E54245601C17ULL, 0x00E775DBBB7719AAULL, 0xA57D20AFAA7EC186ULL, 0x61AD7FA25144F211ULL, 
            0x1E23D9FCCACCD68CULL, 0x68240FDB0DC48ADDULL, 0x4541817E743CE4B9ULL, 0xD6103EA888BCF1C6ULL, 
            0x45046692F64E3623ULL, 0x7B09446AB6288E10ULL, 0xB72853B192C905F3ULL, 0x95FF942726723D07ULL, 
            0xC0C364CE05198432ULL, 0x6BEEF5D2ACD15288ULL, 0xD76D54213DE98571ULL, 0xD75C8830548F1AECULL, 
            0xA3891FF75CE17949ULL, 0x9D6323426C2A9126ULL, 0x5E3D9497386C41BCULL, 0x8B73FB9ED90DEE9BULL, 
            0x21B6BD242CE9252CULL, 0xE9723597850E0A65ULL, 0xF5C3B09ADACCE54FULL, 0xAD48E17D027DAAF6ULL, 
            0x9664AA4A20D1A68CULL, 0x80FE539E4423D6AAULL, 0xD013BF8F581E0951ULL, 0x4B13DA72B43CDF34ULL
        },
        {
            0xCAC6BC5FC6C3F94EULL, 0xFA4A8FF1DB33EF7FULL, 0x9C0D80A0431FE251ULL, 0x5D54413193B02E7FULL, 
            0x0FF8DF53B779D4DAULL, 0xAB5F326DC5D3A31AULL, 0x709BF948C215283CULL, 0xF77351ABE02AEB89ULL, 
            0x968D5E35B3AC9958ULL, 0x668B43E51BE37DEAULL, 0x1ECB548C54257084ULL, 0xC4F865A072CD547CULL, 
            0x14EA5A145F36A03EULL, 0xFE01103FCA34629FULL, 0x95AD0F0549F8F0FFULL, 0x269BA1D5F37BDAC9ULL, 
            0xC378A9BE2DFA5C24ULL, 0x9EF590678314F3ABULL, 0xFE52EED9DEE75A7AULL, 0x7168B4755287E03FULL, 
            0x79A1F0783DF82ED4ULL, 0xDD1B028958258802ULL, 0x9BF0CFCE76BCDD72ULL, 0x831C4B3E6C85A36EULL, 
            0x06A590BC67722281ULL, 0xF35606C610A6FFA8ULL, 0x159A02DA8BBB72C9ULL, 0x8945AD0B2F5235B2ULL, 
            0x2D6B64C26356320BULL, 0x55C1C72E884E4F63ULL, 0xF59E58452D70D6E4ULL, 0x7A03A6E89C2D7C04ULL
        },
        {
            0xCA7105A5F4D7028CULL, 0x4E313F9CCBA090BDULL, 0x48A0687B5EC42681ULL, 0x4294221E45430914ULL, 
            0x2C02237FBEB04CA2ULL, 0x26F6919D9267A417ULL, 0x0A589031638E3B20ULL, 0xDA1AA03094228E60ULL, 
            0x7091E3612E882586ULL, 0xC3B63B3CD5D246BCULL, 0x1525C1F12776BEEBULL, 0xBC0A8CFF6025B7A8ULL, 
            0x2CC38639F4B64E2CULL, 0xFE1591BCFD48BB51ULL, 0x6DB76281378CB22CULL, 0xE0090A67E08FD789ULL, 
            0x47CFF760D0CB846BULL, 0xE240F7E88BC295C4ULL, 0x4F45D6287F5B1F53ULL, 0x2CBCAF8016A0D5DFULL, 
            0xAFE980CB34C51823ULL, 0x9D0E0515B67DB6EBULL, 0x89E1BEFAC509665AULL, 0x8539297F05366270ULL, 
            0x7A6B883751662527ULL, 0xEB6A26AB3304E302ULL, 0xFB4FFE3880EA430BULL, 0x0571FCDE9B241EDFULL, 
            0xE8BEC1706379BD25ULL, 0xF42928B912DC3654ULL, 0x76BFF8F14759910EULL, 0x0B5DA02F7FAE2A74ULL
        },
        {
            0x65BE6CB1BFA4D0EEULL, 0x24FD4E2BEFD360B4ULL, 0xE6203ADDDAB77A1BULL, 0xA2E16B860183E293ULL, 
            0xC3BD69AF16B57760ULL, 0xFBD83AB13CB0AF2EULL, 0xE4CDC6E0A355920CULL, 0xB64BDE43BADE24A0ULL, 
            0x3107D78C52708D72ULL, 0x5710EEFBC570403EULL, 0x708F365508EC2D65ULL, 0xB2D5B1582C689EE3ULL, 
            0x990EDAC09D6FBA59ULL, 0x52C2A96FC2563428ULL, 0x6BFF88E0EC1E147AULL, 0x2E63F27D8290ABF4ULL, 
            0x6B586D534B2D10BEULL, 0x394B672FCFB508EFULL, 0x47FCAE5FC29199F9ULL, 0x54A82813384A3FE0ULL, 
            0x7F8AF98CF7B0A427ULL, 0x72313B07FFDF17A0ULL, 0x4953CAD56FC5D14AULL, 0xA52467ED81BE4A25ULL, 
            0x432DD93155FD8340ULL, 0x8256F59197C25473ULL, 0x12C49922ECA8C972ULL, 0xEE91EF0BC94F6535ULL, 
            0xD79C52AD5AF9AD98ULL, 0x65E890F2D375408FULL, 0x1B809BE7E1A95741ULL, 0xD9273A45B456A168ULL
        },
        {
            0xD03B21422F85F7E5ULL, 0x53BD67A7CF5A74E9ULL, 0x10713C6B5C004C8BULL, 0xCB4C7324215B17DEULL, 
            0xC43ECC60C0964CBDULL, 0x5B50C0BEDDD1B4E1ULL, 0x3345B06F6FACADADULL, 0x7B9E80D95099C863ULL, 
            0xF1C6A1767CB6F136ULL, 0xE6AF035833036BCEULL, 0xF1C7DD001BB1A84EULL, 0x86013EE99C32EFF8ULL, 
            0x08A6960A86F5BBEBULL, 0xC3E4634E2B918C10ULL, 0x71109C7110253FF2ULL, 0xDC3641724603C106ULL, 
            0xD994940DF8D12492ULL, 0x0C5767CC90856718ULL, 0x7C05069DC1F73FFCULL, 0xA8325CA3C3531A98ULL, 
            0xCBC68202B8229E5FULL, 0x5BD8645CC446D5EBULL, 0x0B33A76F95CC6668ULL, 0x68264AB2055AE6B0ULL, 
            0xB69051F9DBAEA759ULL, 0x9AB8C77DCBCC99BBULL, 0xE4C3DEBE21BB3B84ULL, 0x759344E62FA4F767ULL, 
            0x68FA16EAE6AB0652ULL, 0xCCA5594EFF74C396ULL, 0x364B6285BBDEA7D0ULL, 0x1FB944081CA48E2CULL
        }
    },
    {
        {
            0xE26D65265A326D52ULL, 0x251B8AB948A49D73ULL, 0x3119C3CABEEF01B0ULL, 0x4645CC80BF7C39D5ULL, 
            0xC4EA1B5AC25DD361ULL, 0x541631AEFDF314C5ULL, 0xB3C5C6AD43A6C83FULL, 0xB1A593463F449893ULL, 
            0xC91340F8D358D1EBULL, 0x0CF46386AAD7351DULL, 0x2FE56CAA96BFB9DEULL, 0x265A9F7735843FC5ULL, 
            0x46EE5E3E41705B6BULL, 0xE9C26B0C7C09F3E6ULL, 0xC5F1BDAFB503C669ULL, 0xAB4D874081AC4227ULL, 
            0xFDF78A7AE7594850ULL, 0xA3F4A3846CD95D2DULL, 0x2690AC187355C6FAULL, 0x2CEB680605CD27F9ULL, 
            0x901447E27A7D56BFULL, 0x554E1753CFFBCDCAULL, 0xD3B2D05ACC1016C1ULL, 0xA9B4288D667534FCULL, 
            0xD61BAC40FBFD85A0ULL, 0x7C138E584D0A89F3ULL, 0x68DB7EE4E2608FA9ULL, 0x80D43F3AA471A020ULL, 
            0xDA8924A5910FFDAAULL, 0x3EA745D94D27C9CFULL, 0xAC1F8C6A8A412AFBULL, 0x0A65E285A4A3BA61ULL
        },
        {
            0x81B8636F91AA9F0CULL, 0x54BF3042001F7BFBULL, 0xA27AB5E3AF6FD6CEULL, 0x1B76D0D80EBA3E06ULL, 
            0x10AAF7B40EC462D1ULL, 0x41E36EA9878DB74FULL, 0x3D566920C39AE222ULL, 0x7B6F764EFD117404ULL, 
            0xE0CB83A751031364ULL, 0xF3C0A4BE66A11ACDULL, 0xACC6A21D64A585DBULL, 0x3AA6E10AEE07B851ULL, 
            0x251C9BAB160FCB87ULL, 0xF4A423E7CD5CC469ULL, 0xDCF6DD994681D066ULL, 0xF51D2283D6B9BBDAULL, 
            0x983D7B769D9CC47FULL, 0xD56E76A73BE3AB28ULL, 0xEEE090CC7CA57C6EULL, 0x644D887387FDF793ULL, 
            0x76B34F250AEFF323ULL, 0x69B0650D04933C59ULL, 0x65B8BEC7DC8B9C67ULL, 0xAC33B0AD45C65242ULL, 
            0x3C0C294ACAF972F4ULL, 0x12DB3473F741C5E9ULL, 0xA1AC96A75EADFB68ULL, 0x41995DC4128231A1ULL, 
            0xDB14E480E3F99FF1ULL, 0x7E403172194ABD0AULL, 0x08CAE6F667FFEA6AULL, 0xEAB1414E52AD7526ULL
        },
        {
            0x7D4A02E4205C99B6ULL, 0x5BC924B6AD345F2FULL, 0xE9ED23AB3A58CC43ULL, 0x385930A58DD18E58ULL, 
            0x920AF77637DD209FULL, 0x54758AE8844BA3F7ULL, 0x723F32F0D7055B6CULL, 0x2DDCB9F36888B74DULL, 
            0xAC01C84094FB606AULL, 0x9CD68E32B43A1F7EULL, 0xCE07AF879E5D07F1ULL, 0xA01D353A7E328988ULL, 
            0xBC89605CBB542654ULL, 0x208A9C290F85F245ULL, 0x99A3B1E26F7112BAULL, 0x7FC2881B3AA8DCC7ULL, 
            0xCD7DF3FABDA44F54ULL, 0xB1557768974ABED0ULL, 0xF555B707855FABAFULL, 0xA5F876686078976CULL, 
            0x642C9B6D379BBE4BULL, 0x39C383587DA9CB35ULL, 0x1D0755729C38C07BULL, 0xD3B311998C01E9C5ULL, 
            0x64D161B247E73410ULL, 0x2B0325FD1B868110ULL, 0xEBC0F89831778FBCULL, 0xA18383E6694A7081ULL, 
            0x875EB4E4382A4026ULL, 0xD8ECE5BE5BCD0CF2ULL, 0x6C8BA224EF5EF881ULL, 0xF91AED4979C80EA1ULL
        },
        {
            0x3DE220467DCA127CULL, 0xF953EC5B5F31DC20ULL, 0x27412D6C17345B37ULL, 0x81E54DE38E40DC7FULL, 
            0xA3A6E2BB0A81D988ULL, 0x27CEBAB046FA5721ULL, 0x378FD8D54720187EULL, 0x5D89AAC2A6A9541DULL, 
            0xBE2836D0AC66D69AULL, 0xD9302E392EC6709AULL, 0xA1DA08D6AE84BFCAULL, 0x96B32BC947A306ECULL, 
            0xE5834837D81FAC73ULL, 0x4E07079861F0A0C9ULL, 0xDEFBEB89B703599BULL, 0x83833387270EDAECULL, 
            0xE2AD60210B148EBDULL, 0x5677A07FFC8C6E49ULL, 0x7F471215DE457FC3ULL, 0xF192D51093F74F70ULL, 
            0x1B5147BDB1518FE1ULL, 0x841F4512E2CAA1ACULL, 0x03933D93EF6D1E1DULL, 0x2943894F304AD25BULL, 
            0xAF4EC62AD4853DDAULL, 0xF5FF9282FEE7111DULL, 0x2A164CA40B394DBAULL, 0x48B289212174885FULL, 
            0x4A741A617996DD4BULL, 0xF85E9EB80520741CULL, 0x08C1CCD995725294ULL, 0x034F825461F8A1BEULL
        },
        {
            0xC75916DBE3B8631AULL, 0xCF86E26D15CB5CCAULL, 0xE13B0A2FC8681FDBULL, 0x7EFDE8471C725811ULL, 
            0x495C755F803593FBULL, 0x81F7977E07D0E606ULL, 0x2304CDF18829E630ULL, 0xC8D9CACF072F6949ULL, 
            0xA08F06E10DC9F766ULL, 0xD87DC135FDB32FE7ULL, 0x1CBA7D7FA150F7ADULL, 0xD33F77F47695CB71ULL, 
            0x1A70A3BDDF18E3B2ULL, 0x4F07C8A009FFD5A7ULL, 0x02790646926ACF4CULL, 0xF497D1E639F26701ULL, 
            0x7398A077D01290B9ULL, 0xBB2DBD454D6F4712ULL, 0xCBA14C4177DA1E57ULL, 0x840123F9D54320A0ULL, 
            0x998510BB8AADA08DULL, 0x03FA6BFADC59AB91ULL, 0x922CF3A63BE7753AULL, 0xB804910E4DFE576EULL, 
            0x9E5F9CD4F68E46DDULL, 0xBAEDD5DC2E65E70EULL, 0x0843FF19BCE9148EULL, 0x8B5180DDDBDDA6EDULL, 
            0xA81C62EF58BD3912ULL, 0x82B7EEC65ED3BA7BULL, 0x0B2B1E67856F7407ULL, 0xFC083A9CE17F76EEULL
        },
        {
            0xDC14C00E13B628B5ULL, 0xDF4F38AC43E67D73ULL, 0x706A0313CF535CCCULL, 0xE440DECDA760954DULL, 
            0xD9A5B206B50BF9B1ULL, 0xE706841BCD11D541ULL, 0x59FDAA4D6FDC829CULL, 0x597E8BABA03ECB26ULL, 
            0x7F83A74DA279C80EULL, 0xCB3C068A6DFAA016ULL, 0x98B99DE729DEC84FULL, 0x5575FC1A48237DE2ULL, 
            0xDE07F76F049D5E2CULL, 0xD1921211F2A4F558ULL, 0x3E2C488F741CD8FBULL, 0xC06F55E698BC6B47ULL, 
            0xF0358A77027C0EE3ULL, 0xA8BB1AC933596994ULL, 0xAB87D9BD0E8CB82CULL, 0x3EA61FAB612C3E54ULL, 
            0xDA7E32ADBF766ADAULL, 0x82AB3CCD580BCD64ULL, 0xD644F7695BFDB610ULL, 0xC7776E5CAA759B7FULL, 
            0x8B90065B8DEF605EULL, 0x4813B451364CD9DEULL, 0x287581C20AD01D3AULL, 0xA03ED45A1CB48EA1ULL, 
            0x65BB9BF1456DAFBFULL, 0xC147D42CF50A42B2ULL, 0xBD2A40EEB7D8F8A3ULL, 0xEA9FFE1569A6E235ULL
        }
    },
    {
        {
            0xB24C91413172C9A3ULL, 0x374737456523183FULL, 0x4E9C6ED9CF90DAF1ULL, 0x18A02254A68A00B5ULL, 
            0x064FC655C427E343ULL, 0xE0725766FC0CA678ULL, 0x200A414AEBB55CC4ULL, 0xB9D694292BC143EFULL, 
            0x080622A367AEDE4AULL, 0x138D3D6D679EB40EULL, 0x8AAC12E1967CBA32ULL, 0x41A7B489FA76E4E1ULL, 
            0x8CDB2A69863718F1ULL, 0xAA60CE133BA74BC2ULL, 0x169D2CF647C7B87AULL, 0x78DCA2F6E3B79BDCULL, 
            0x27AF65FEBC85E80CULL, 0x3E0E06CD11CA6BD8ULL, 0x8A2C79D4CC51ED9FULL, 0xF27AA021824C985AULL, 
            0x2B571EAE1547E299ULL, 0x812BD6C76934689DULL, 0x3FFC2D1849057A55ULL, 0xE76E7ADE2D48EF01ULL, 
            0x29D8AE1DDF3BDCF7ULL, 0x708C80300C29066CULL, 0xF6034A33D0D2E50DULL, 0x9BF3CC6F585C553CULL, 
            0x126DA444F786D103ULL, 0xC14188C29E9E84ABULL, 0xFE657EDF12DF9789ULL, 0x3028584E475255A5ULL
        },
        {
            0x01634706C4D905F3ULL, 0xF939E21E44BACC02ULL, 0xC3805878E44EADF3ULL, 0x132E45AEC08AC9E3ULL, 
            0xCDE4D9D57D4FFC50ULL, 0x24483875E171889BULL, 0x008CFBFD95BF262EULL, 0x1DE1EF03D5F01E42ULL, 
            0x78CCB755958B38E2ULL, 0xC0A678A9DA481DFAULL, 0x8109297EEF3DEF2FULL, 0xCFB4A870B67630D8ULL, 
            0x34D6BBF9782C9CCDULL, 0xCE5593E1A16E0A79ULL, 0x5316CD901B899A8EULL, 0x9CF317EACA879269ULL, 
            0x51356CE3C41EA900ULL, 0xFDDACC4A6AAC3E06ULL, 0xF889EABCD21ED449ULL, 0xD125D3B16102DC4BULL, 
            0xE1F2C89CCAFADC6EULL, 0x61B0D7BD6BF6117BULL, 0x6374027227D65FC2ULL, 0xCF941D5BE91AE1F7ULL, 
            0x9355EABE8E8DEAFBULL, 0xC37CA458D15BAE4CULL, 0xB9B39256767EFF63ULL, 0x33CF217B1EDCB73BULL, 
            0x894297CA2F1AAC12ULL, 0x265B66F63FD25C7EULL, 0x6BD96528E43119CDULL, 0x0F9D3D63484EF58AULL
        },
        {
            0x28CC64DCB0A1C76AULL, 0x18B15650A8EE021AULL, 0xFA20A6680081F328ULL, 0x8D80CF532A99FE6BULL, 
            0xD24A51EA622ECB25ULL, 0xB921D6175F2F1999ULL, 0x35A11265E245CA56ULL, 0xEFBE6CC5F6790BFFULL, 
            0xBB8C66B126008A69ULL, 0x7C1E36A9BEDF2545ULL, 0x0963A3FEDC7421B5ULL, 0xC3361CFBD862A56FULL, 
            0x7213521F1CA7E68DULL, 0xFD43C933325003BCULL, 0x13EE5E4B9191FDECULL, 0x786A1433D795606FULL, 
            0xA91C1700F76AE4D5ULL, 0xB3B51A730EC225A5ULL, 0x1A1B479924FDC438ULL, 0x0D24D128568CB1ECULL, 
            0xEFE58BE6F8A155C1ULL, 0x50F48CE86D7C375BULL, 0x3A9ABB4FFE783340ULL, 0x0DE12BAF720F15B7ULL, 
            0x08CF3DC9696561D1ULL, 0x15777F2438122BBEULL, 0x63AEF7C29DEF2CC0ULL, 0x346EC4B9434B94EAULL, 
            0x08F97B2203B0F299ULL, 0x68A871EECC2C53C4ULL, 0x166E95AA29400A09ULL, 0xE24981C675196C6AULL
        },
        {
            0x6B5774F5B1B831EFULL, 0x92836B7BE735B07CULL, 0xABCAF26C74E72BFEULL, 0xC70A52273217CFB9ULL, 
            0xC9F758CE0C440B57ULL, 0xEF9CB60E687757DFULL, 0x664EB9182D987407ULL, 0x036251CF77A1A3C4ULL, 
            0xDB53E3C453B9EB9EULL, 0xA01EEB3D235E9C6CULL, 0x5A21DD5015EF9CF3ULL, 0xE4F0BAD048CA7630ULL, 
            0xF4388AFC5E92ECDEULL, 0x49614729AC9B26F2ULL, 0x366A6832D316202BULL, 0x98EB7A4486E51D2AULL, 
            0xE6A50E8825EAD8DEULL, 0x78639FEDAC0714BBULL, 0x741D10A7FF228599ULL, 0x4F828D1940646B2DULL, 
            0x87C5AA97514500E5ULL, 0x8FAB69E1E4C80997ULL, 0xAE1F6E65348585EEULL, 0x0F2FF78860375219ULL, 
            0xD6281365A9E6203FULL, 0xB88C3EA5D40206A7ULL, 0xA593EDCD00EA5F7AULL, 0xC974028B6CDAC24BULL, 
            0x3AC9891AE57E4DFAULL, 0x8FED3969304621EFULL, 0x7A69ED3F7AC98DF3ULL, 0xED4EAFB7EB333011ULL
        },
        {
            0x4EB839000C79C1C3ULL, 0x48ECE9CBDE38D3F0ULL, 0x73A72F631C5C87D4ULL, 0x65EDE7BF3ED2500DULL, 
            0xEE723A0BE8C8F3ABULL, 0xEA6CC20E5F0BC27CULL, 0x7D646B1123F9A488ULL, 0x9A7E33A173E00AFAULL, 
            0xFC1AB389E35E2DAAULL, 0x5B7F42675FD7758EULL, 0x0384C9501640CA51ULL, 0x7ABDD39EA4780416ULL, 
            0x4C256D1D65A89AFBULL, 0xE3A06ED5594560AEULL, 0x42151ADF091FF5CFULL, 0x7BFE7E6B1679C624ULL, 
            0xB4E09CC67F38E60CULL, 0x9F1FF43AD9EE729BULL, 0x4CB185DB38C79E62ULL, 0xDAD1D89000A6FAFFULL, 
            0xEE84EB7AA286098CULL, 0x26977C7917091AA0ULL, 0x364D9F54271D993DULL, 0x29CDA8D60E8B8798ULL, 
            0xF4E2E417E268641FULL, 0xE17DFA8837655363ULL, 0x51B31132B4D1199CULL, 0x96BE3A43A7096948ULL, 
            0x5F137E9529EE9685ULL, 0xE19D605CA924A313ULL, 0xEE6E4AD769E7535AULL, 0xC8390BCC6E96F38DULL
        },
        {
            0x15D2DEB4D0B10C57ULL, 0xE44A3DE09EDC254BULL, 0x04D41CEF07FFCAB0ULL, 0xF60A6C2D4B84EF54ULL, 
            0x3DFE32CE9C5F8EE7ULL, 0x84DAE9015540F4EAULL, 0x8641DB72FF16D748ULL, 0xD1586D8BB32005ECULL, 
            0xF8CAAD8FF4B6206BULL, 0xF62A4DC63A7F82AAULL, 0xAE5141FC9E9ED192ULL, 0x569A684815410D2BULL, 
            0x437FC1B1AFB00C1DULL, 0xE895728492608593ULL, 0x325B39B5E9995D6AULL, 0xFCBA7AF7DC9990B0ULL, 
            0xF1941CCF742712C6ULL, 0x9510FB70B84C5FD2ULL, 0xD452C7F9E5071EEEULL, 0x39A081C153E93974ULL, 
            0x537448B6157C852BULL, 0x6E571A5BE5113415ULL, 0xB0D5DDCAFC9421B2ULL, 0xD8D2F0C3A18020A1ULL, 
            0xA2422B0E78D4C386ULL, 0x6ACCAEA5302C4BE5ULL, 0xD0F8B5848F779A05ULL, 0xA8E31E44ED64F1BAULL, 
            0x4484DB42525197EAULL, 0xDA3D50FA202D447DULL, 0x94A829C0BFBF2507ULL, 0xB228EE7706ED7A0DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseDConstants = {
    0x3ABFFC3D5E6794BCULL,
    0x70125A4CD9947686ULL,
    0x582CDBD3CEB49CDCULL,
    0x3ABFFC3D5E6794BCULL,
    0x70125A4CD9947686ULL,
    0x582CDBD3CEB49CDCULL,
    0x9D8B02715C8C9C3BULL,
    0x9F72BCE1A9FFF63BULL,
    0x19,
    0x22,
    0xC9,
    0xEB,
    0xCB,
    0x28,
    0xA1,
    0xE8
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseESalts = {
    {
        {
            0x5CA6A6328F3F6FF4ULL, 0x37A3D4BAC894983BULL, 0x9ACDF1BD35E35195ULL, 0xA3D6CA70B2DB3889ULL, 
            0x288EB69002E9E96CULL, 0x806D18CE6EEB6BCCULL, 0x65FE077972F5AD53ULL, 0x7A086971CF94700CULL, 
            0x959DB74D406BD8CCULL, 0xE83A8D606B068864ULL, 0x2A3CE418D9A44812ULL, 0x404064E490B3CD39ULL, 
            0x9B7F2DB2EF461AB1ULL, 0x82F926FD5E5F8EB8ULL, 0x8C69B7BF491EC257ULL, 0xF49D52C1EB9541D6ULL, 
            0x3353272DF5A36D42ULL, 0x36366B0395D76D93ULL, 0x5E69DD674D7B69ECULL, 0x67904B294A875F19ULL, 
            0x198D8AD03A927793ULL, 0x29BD3ED9C5FB9AD7ULL, 0x08A43171E084C473ULL, 0x9967F315F60BEA57ULL, 
            0x021E0790B6B8D75FULL, 0xFAA014D7C7D7E98CULL, 0xF4F4EE674FA073C4ULL, 0x14DA59DE8A982559ULL, 
            0xA0A8B1276B30F6BBULL, 0xC3D6338E39B23EDEULL, 0xD96F38CAE2AF5A72ULL, 0x6E881D41FD3BA7EDULL
        },
        {
            0xAA10CE28837E6BF4ULL, 0x5BB38B9CE2FC760EULL, 0x46EA7A9E9271D5A8ULL, 0x795749A7F667BE40ULL, 
            0x04EB2252910286B4ULL, 0x87D0E0651AD821D7ULL, 0xE0F112396C72BE9EULL, 0x2A5574231C324431ULL, 
            0xC7CCBB7C67ABF962ULL, 0x942BDA10F401865DULL, 0xCCA5097B0317D8EEULL, 0x9AEF02D1644106D0ULL, 
            0x8DBB673249864CA0ULL, 0x9F22F29F790BD6ABULL, 0x3F6BE96ECA30859EULL, 0x3ED187C98C319607ULL, 
            0x687007784EE0BCEAULL, 0xDD91AAC71B40C9AEULL, 0x5A59B1F697A4C12FULL, 0x577B0B7095CB7674ULL, 
            0x50016EFFDDABA641ULL, 0x56A9B9BB76351D12ULL, 0x465EBB51891944A2ULL, 0x6EACE68FF38B4166ULL, 
            0xE02D8375812DEEEEULL, 0x4A1A801DB7DBB3CCULL, 0x664E97EA22566C48ULL, 0xB5A7D85C6B03719FULL, 
            0xEA50E495FB744852ULL, 0x385AC6546BEC5D07ULL, 0x8ACF09FE9AFD8FEBULL, 0xCFC02C68C3AF0185ULL
        },
        {
            0x0E148700C494F973ULL, 0xAA5F4CB95FC7EC74ULL, 0x5467669D40C49A70ULL, 0xF38ABF4EF8C45FE2ULL, 
            0x5AFB235087B9C3B2ULL, 0xEFBB8DDC199A1357ULL, 0x30C2FA4100C2A0ACULL, 0x848E57A15872BA36ULL, 
            0x3180BA05270FBDDAULL, 0x6702B8A250B58E9FULL, 0x77E7D0C9FFB55DB7ULL, 0x72B6CCD87879AC06ULL, 
            0x88075648D52395BBULL, 0xFE24C814B71697D2ULL, 0x39B2B173862AB842ULL, 0xBD306D263900D303ULL, 
            0xF62AB5E787DB27F2ULL, 0x47ADF23378139033ULL, 0xE5EF62894A95AD31ULL, 0xFDB3085C9C28A175ULL, 
            0xB33955F2AB961FDDULL, 0x077B13C85CDB741BULL, 0x6B06817052BBDA43ULL, 0x7FF467405CFE9A58ULL, 
            0x2920B7C974EE3E75ULL, 0x5E5CABCFD3C1F47AULL, 0x1ED80EB49E854DD7ULL, 0xA31DDAF87A4C31B4ULL, 
            0xD0CAABC2F4482852ULL, 0x5DC491C7B313A583ULL, 0x114BF1AFCD02B13EULL, 0x389AA07130DDBA0BULL
        },
        {
            0x070FBE7A50C1B2DFULL, 0x9BBB08DD480CE6D3ULL, 0xBE418538AD7DC405ULL, 0x7E1B89FBAA3E77FFULL, 
            0x99D2BE10CB927DD6ULL, 0xA32CD79F30104089ULL, 0xC1780EAC2FBAE0EEULL, 0xD3CDB5B9A9B61301ULL, 
            0x14E860CAE31CDBDFULL, 0xFCCFE795F190479DULL, 0xCE6B0AF7A83EAC45ULL, 0xFD8EA430FCDDA603ULL, 
            0x0C249552729F7267ULL, 0x04D6613F6CE009BBULL, 0x7C4B8E9E6EC602E3ULL, 0x7E5CFB64AF456B1FULL, 
            0x850B4C5A6B2F0A76ULL, 0x1884F11F4F5EA1D9ULL, 0x70A043BB7C71A2FFULL, 0x0806A53935F8A283ULL, 
            0x930828238934BA01ULL, 0x2481686A0F5582FEULL, 0x594024B369A06D86ULL, 0x53248DD3380C8799ULL, 
            0x564A8151F333E84EULL, 0x6E458465AAEFE3F2ULL, 0xE61A79958F3C0269ULL, 0xD15100EA34CC43F1ULL, 
            0xF80EB7FD940ABA3BULL, 0x58033C775354AB8BULL, 0x969CB8BBE7881FF0ULL, 0x0206325FCAA5367AULL
        },
        {
            0xA856DC9D6BE7A763ULL, 0x922B208066186B12ULL, 0x20986FDC1783E43CULL, 0x299564DA2FE0A967ULL, 
            0x3B3CC609E3E2BF12ULL, 0x96BCF3CD95FDE8C7ULL, 0x50AA9EE8428C3A78ULL, 0xBC12DD02944681B1ULL, 
            0x77473C3FDDABB4CFULL, 0x7796B12494FAF4D6ULL, 0x9E4B956ADF6DF11EULL, 0xDC528B5AFD6CB8F4ULL, 
            0xFA276214A2F5990AULL, 0xDD50091CCBF23005ULL, 0x15BFEA0001B346C6ULL, 0xBA80B6B12D17327EULL, 
            0x7031AF5793C56C8AULL, 0x9F14E22126535F6AULL, 0x347FB08F7537A883ULL, 0xDE7984AFD42C670BULL, 
            0x8904DCB1A50BBE51ULL, 0xB881FCE7C5F3697CULL, 0xD96106EAD41897A6ULL, 0xEC132603671A6750ULL, 
            0x1AAD76FE848E8FFEULL, 0x5A6F11EE36B74BFCULL, 0xB8A24BF9133D0DCCULL, 0x2ABE4A9D70BDAEEDULL, 
            0x12606993E47AC667ULL, 0x38754A3EA6348CB2ULL, 0xCE0AAAC3EA5E598CULL, 0x5765C649812C1623ULL
        },
        {
            0x10640859554AF20FULL, 0x22D51B7E7FA8E0BFULL, 0x543482D1B2A09DBEULL, 0x90D97DA756577150ULL, 
            0x8C0728BA281E0D1FULL, 0xCE292EEDE322BB6DULL, 0x4B4303E5636E4E38ULL, 0x75E32E1514197D1EULL, 
            0x248456D9502E85A1ULL, 0x430DE5E01D4F9659ULL, 0x052769BF26C994A2ULL, 0xE4406D64047C29E6ULL, 
            0xAFA403B14D5F4125ULL, 0x46D582B0C07F4822ULL, 0x9215CB76EF76EFB0ULL, 0x7061CADDA415C6EEULL, 
            0x8CBDA6F994AA950CULL, 0x2BA8428E4B445ABAULL, 0x9DEDCD2D6162B4A0ULL, 0x27F0093AB633997DULL, 
            0x7919A79037C68AB7ULL, 0x8F61138807FAC5E1ULL, 0xDE1F537DF22368B8ULL, 0x28751938B311908CULL, 
            0x009DB7214AA3128FULL, 0x42F595027C4E9C79ULL, 0x90770ED96134587CULL, 0xD98F13E1D785866CULL, 
            0x17C035B01078C88FULL, 0x74478F7C8F6BCBECULL, 0x27BF156C901E3FD4ULL, 0x3CD5858CE63FABA9ULL
        }
    },
    {
        {
            0xBBFE5006BD0476DEULL, 0xCD26308C9AC5F872ULL, 0x745F80AB8F64250FULL, 0x1E08A20A840E0EF4ULL, 
            0x360D8143256326FDULL, 0x3B18E994C75439B9ULL, 0x44E7F33269F2D517ULL, 0x5B077E9DE5951A52ULL, 
            0xB26D19F5A49AAA3FULL, 0xFF1901C6C1FCE51FULL, 0xFC19EA5ADD7BBD10ULL, 0x24016044A81F2015ULL, 
            0xBED4746F0DDE38D6ULL, 0xAAA82D6B17B6F106ULL, 0xBCF4C6B1CB2F22D0ULL, 0x9006182B4C181BD6ULL, 
            0x79773DB9CBC5E756ULL, 0x05B039F32FEEB3E8ULL, 0xD6CB763B27678FD6ULL, 0x54C7F0A7AECFB4C7ULL, 
            0x8BBFCAF89313088AULL, 0xA29BA1594CE6A9F4ULL, 0x79616674965A1802ULL, 0x3D7F3FD9DAC7EE30ULL, 
            0x0EB7C193F07B9522ULL, 0xA1CC71323C996877ULL, 0x4D228C0C76DEBCC2ULL, 0x9E006AC26C4ACF9CULL, 
            0xE363A68570D12433ULL, 0xBC343C313B673A58ULL, 0x9AB1205049E7F9E5ULL, 0xACE3065B37F2EFB0ULL
        },
        {
            0x5652BE539E107715ULL, 0xE2FAE07F686DA540ULL, 0x5569833520022E29ULL, 0xA9C7EC9A9C65EFC3ULL, 
            0xF416A97576BE9EF5ULL, 0x46D8CB630AFD8C78ULL, 0xAC368F6819B8C83AULL, 0xA02FE26E7C15E493ULL, 
            0xE620A377B57F9433ULL, 0x85DF488B1506F1F7ULL, 0xE561C457DC8423B3ULL, 0x9D36068D5CBBAE1AULL, 
            0x3B8425D48803901FULL, 0x7F4EECA271E0EFFFULL, 0x8396251C44E0D11DULL, 0xF19BF630BA341149ULL, 
            0x09449EB6B07EC6BEULL, 0x93E1A4EFC6DBBC6EULL, 0x12305DFDBDD42DD3ULL, 0x6FF748F63C879A02ULL, 
            0x32B12B7CAAE022FBULL, 0xD5BDAC410E2A037CULL, 0xCABDBCA6E02E57AAULL, 0x8C32A9BD421C9579ULL, 
            0x9C2D9A4619D5C340ULL, 0xC300D663747DB5C8ULL, 0x4789A75FF304B149ULL, 0x890E31BE43C61469ULL, 
            0xFBE92A2F8FE4DC5BULL, 0x0E646A8B070460C4ULL, 0xAF8D2358E72D8495ULL, 0x20EC6B2CE1FB109BULL
        },
        {
            0xE59B09BFD87A5861ULL, 0x3F731BC0FBCDB4A5ULL, 0xDC95065D3F0EA334ULL, 0xA38EEB364D5D3525ULL, 
            0x90F7DC9812C8E97AULL, 0x351CBCC10918D5D8ULL, 0x0A463A092554B90CULL, 0x13D0974C437D76EBULL, 
            0xC0CF1279C25D2ECEULL, 0x13863F63DE92FF53ULL, 0x963C7EFB2646D800ULL, 0xA1B86EF160779AD6ULL, 
            0x1755FB141573C14FULL, 0x6FD7ABE7A8704B56ULL, 0xD0D192496FEBFD64ULL, 0x60A2528C69DAA054ULL, 
            0x5140A9918A6664D2ULL, 0x16EAEBA115861D02ULL, 0x946B581AAF04DA75ULL, 0x9D216D0684C0C985ULL, 
            0xF0CD03F28F78770DULL, 0x053D7C090D07E98CULL, 0xFDBC1369BA56A62BULL, 0x65A232F35086BBBDULL, 
            0x3E0E9E2F80EC44A1ULL, 0x7CD231D80800529AULL, 0xB41E8E48640BE05BULL, 0x2CF0A82B63809A90ULL, 
            0xED9FD1E2A84DAC63ULL, 0x3131D6C7FBFD00E1ULL, 0xBC8148AACFA2AA4CULL, 0x48CD6B9E098DF659ULL
        },
        {
            0xB1D5708C4C74E7E0ULL, 0xEF201092BDE7EF8AULL, 0xBFC0884CB47E096BULL, 0x2401696712CB0E64ULL, 
            0xFCAC5CC68B520FA8ULL, 0x7AE54AF81304C026ULL, 0xE8354CF0EBCD3963ULL, 0xAA3096DA4C32A7BEULL, 
            0xEB2DD77A6899D7B5ULL, 0x3E2F8D560FFEA2F9ULL, 0xFA347AA00ABD9E8CULL, 0x04BA6CA39B5831DCULL, 
            0x3FE4E12B18226F88ULL, 0xFA2C5048B51EFBE0ULL, 0x3B11E7C566C01B51ULL, 0x27D66721B392FE07ULL, 
            0x6261A45312FD532AULL, 0xE01D0608E6CF5328ULL, 0x636D3273716808C3ULL, 0xC00F1CBBB34C7CD0ULL, 
            0xFF5483D038F0D5E9ULL, 0x34A197E8C205E899ULL, 0x767857D7CDE28050ULL, 0x7793D5A2A7E6BDDCULL, 
            0xA5A64327AE4FE310ULL, 0x1C9BE0C0CD89AA80ULL, 0x586895D22F769B58ULL, 0x1590EAC246E18F65ULL, 
            0x91DF733B25A3058FULL, 0x5BB1796CCA772D53ULL, 0x07D8B74BCC523E7CULL, 0x7FF486B98692DFD6ULL
        },
        {
            0x477CE77DE793867CULL, 0x5864385B870AAC43ULL, 0xE62AE3403E3A61DBULL, 0x96ADC44DC46CFBA4ULL, 
            0x91AF3ED02BD30761ULL, 0x59E952A72176657DULL, 0xCA99792727FD27D1ULL, 0xB2736AC9ABA2D488ULL, 
            0x2F9DBFE554852742ULL, 0x36BE1EDE9A535964ULL, 0x3B32A2FD44C2B2AFULL, 0x46FE6731544A74DDULL, 
            0x3DE17A3A93A3C374ULL, 0xB78E0D3DEECD762FULL, 0x51A6899B9763ADDDULL, 0x9DC85505F88A7687ULL, 
            0xABF47FB35B980291ULL, 0x5C0AB03E85E5F37CULL, 0xDE33CF28F4BBFA60ULL, 0x67D52A2B4B4A7105ULL, 
            0xA7F68DF2BEE0A8C3ULL, 0xCCF511923C5A0F58ULL, 0x6011156C207D3D30ULL, 0x9C9F4104668A2CDEULL, 
            0xEAED472C9A36F2FFULL, 0x5EC2F5C4BA4DF7B1ULL, 0x26D61DAF3D05BE0FULL, 0x4B86503BBBC8F228ULL, 
            0x38C41ADD42E1F91AULL, 0x8B64AC2117FFD74CULL, 0xFCF471D09CCF5626ULL, 0xDA9428B4CDA68227ULL
        },
        {
            0xFF2D38FA21DCAEA5ULL, 0x0BFFFD208B76906CULL, 0x30AA39811E28C701ULL, 0x3A45C1EABCBCB9B4ULL, 
            0x4B3026F65A3D7F1EULL, 0x544C814440130887ULL, 0x536A0C61608E1543ULL, 0x55A1F2A50383884CULL, 
            0x677B1C655788B47FULL, 0xEDAAE028DC4F4544ULL, 0xA376B7FBEF106A60ULL, 0x7821D29C642466A8ULL, 
            0xC501FBFFC7FDB040ULL, 0xE0827ED6D253CB4EULL, 0xCAF0424939AD1D97ULL, 0xF08B3FD282E065D1ULL, 
            0x2E6A8F44CAAB2DBFULL, 0x58F716F6BB26A107ULL, 0xFD79D9B73314BC50ULL, 0x95B8AA747A1CD176ULL, 
            0x76EF865790B47BCDULL, 0xAEFE87A89BABC758ULL, 0x928C37EE7341B7A3ULL, 0x365409E3EBFE39AFULL, 
            0xFCACDAE5B74794FEULL, 0x9127F84D3AB29C14ULL, 0x54F26F05D514DD82ULL, 0x35D5CCA2B489E731ULL, 
            0xAC022BFB277478BEULL, 0xF1DDEF975E91972DULL, 0xBAE40256D48B928DULL, 0x52CB4ACF52B61188ULL
        }
    },
    {
        {
            0x0582D34C7A49F5BBULL, 0x24494B14B11C7FBAULL, 0x3045CD429EA0ED6BULL, 0xA37E6265A06E34DAULL, 
            0x52374289C3BBE97CULL, 0x96018A7E189ED671ULL, 0xB5C3B5ADB34AD814ULL, 0xAC4C1A996C8A8C89ULL, 
            0x8B6CE8FB4D6B45D5ULL, 0x2F0499D3E7185258ULL, 0x24989B3AD348241DULL, 0x9DD83F71B062C548ULL, 
            0x07E8C5FD1FFDCBAAULL, 0x3E8599553E765190ULL, 0x300DB09DFFA72B29ULL, 0xE8682DAF63ACFC59ULL, 
            0x84E123AA407EDED9ULL, 0x46AFFD10726C5B2AULL, 0x03CBAD9C42DA3558ULL, 0x072E306D9E48C193ULL, 
            0x57129A07184F092AULL, 0x4941DB9DF5FFF10BULL, 0xE3E28CD0D47DBE2BULL, 0x93FBCB5E575DD4F1ULL, 
            0xFE2E4D8A3032B388ULL, 0x7962E2B912407B23ULL, 0xD4FB66E333857CB5ULL, 0xD7ED3DD04CC46DFDULL, 
            0x7E6C1E1347A42B39ULL, 0x55E6FD3B7703F6E1ULL, 0x5F33AB8C81E6A033ULL, 0x6301A910865C5318ULL
        },
        {
            0x63909140F071D5B0ULL, 0x6CE34921B43F6F5BULL, 0x9E3557402DDADE8DULL, 0x485BBF0BFB3F25DFULL, 
            0xFF0E78FF49FD4993ULL, 0x06FE48569FC61682ULL, 0xE5E7E25847664385ULL, 0x8CE7910C9A039A47ULL, 
            0x164C91E07E5B6E4EULL, 0x0B7A7E688B17E3EBULL, 0x21994AAE81E9EA3CULL, 0x3E2D99FA594D1C64ULL, 
            0x49B4A6F4A720FFE1ULL, 0x2AA53DDCF03B2D7BULL, 0x4DCFE6C11D4DFEBEULL, 0x194EF06FDE4E880AULL, 
            0xCC6DF5AAEFB7FF60ULL, 0xB65E4E001C69443EULL, 0x3CB3BF2D7903C80BULL, 0xF63055C47CF25A9EULL, 
            0xEF8D3BEC497D4AB5ULL, 0xFE188132A06DA6DAULL, 0x86A7F54C80DD695DULL, 0xCD98158AFA4D4802ULL, 
            0x8AC315FA3D5144A1ULL, 0x3ECA5E56983C000AULL, 0xAE1DF10F7D1FC6DCULL, 0xF6B3CD3C7B5A3049ULL, 
            0xC91A39682E00A318ULL, 0x3D208D528BF215A7ULL, 0xB1B45CCBE3CC607CULL, 0xD05129978E88EA17ULL
        },
        {
            0x8D200EBF41CA3193ULL, 0xB70BDCE5A50DC9C4ULL, 0xDF04C7CB8D72F410ULL, 0x360B7B95491CBBA6ULL, 
            0xF924A4346A0C4158ULL, 0x4E8AAD4EFC18514CULL, 0xF9CFAF7BA5740974ULL, 0x25D9A15A68F33678ULL, 
            0x48A6CCB93F5E4551ULL, 0x46162D018BB57E76ULL, 0xBA30C258F5614371ULL, 0xAF03D0032D6CA346ULL, 
            0xDED4350F16241C64ULL, 0x78790F2A494A3F2CULL, 0x4102B7215B3DD7AEULL, 0x28C30EDED2F4B420ULL, 
            0xB00609DEBA5260A2ULL, 0x8DFE25B9A6174D0DULL, 0xA29E652999DC94C6ULL, 0x08A3E55E94AC0E2AULL, 
            0x3BC9173CC2F2E184ULL, 0xD6E056470E8CE5C3ULL, 0x7978B06001E8E767ULL, 0x4CA012EFAA074939ULL, 
            0x714614EDF459FD58ULL, 0xC2EF33C63BAB6B1BULL, 0xD86A3E061B03DF60ULL, 0x78D98B672B30C673ULL, 
            0x74249E48F4538E6BULL, 0xFA5B108541605140ULL, 0x9F5AF15AC645F00AULL, 0x214FCAE3E76AA5D5ULL
        },
        {
            0x5A8EEC51594BC47CULL, 0xDD6017C9B7921673ULL, 0x324A8E320DAD6ADAULL, 0xD40A77A554CD9558ULL, 
            0x7566874722831459ULL, 0x05B0582BAA215F91ULL, 0xC32F4B07C6985D7AULL, 0x49F4FC0F64FEFA3EULL, 
            0x7479152228A77B7CULL, 0xEB891D545E5C7808ULL, 0xD3A6DBE3F44A6CFBULL, 0x3008E7CA6F472A74ULL, 
            0x9C2CC0C808BE3384ULL, 0x6B16A4BB1E8BAB20ULL, 0x12FE2C7FB87F95A8ULL, 0x58C8DF6DB81FF062ULL, 
            0x131C748B79C39073ULL, 0xC9C862AEF9CE620BULL, 0xA327378F033BFA9EULL, 0x9A8B302E740AE76EULL, 
            0xD4288B9FF05A9B31ULL, 0x47CDAD35CEE87FEEULL, 0x23D021ECBBE9F201ULL, 0xD2D433C4FA1E2D93ULL, 
            0x481827A48268FEABULL, 0xA2303960855CEDEEULL, 0xA7492BB474FA6C15ULL, 0x5A705B2CF0C55E1AULL, 
            0x237AD9A470D6F30AULL, 0xC10521E1292CF179ULL, 0x18214E432DC05033ULL, 0x91A99C5E018A750EULL
        },
        {
            0x783128FD54626115ULL, 0x1FB5CA957653F963ULL, 0xA9A1E6D6B66DB44CULL, 0x77AD6B1E42C74863ULL, 
            0x09100169985F0C44ULL, 0xE7DE1D0A54CB7C6FULL, 0x8C1372B85068CB43ULL, 0x20E2416B93EEC94DULL, 
            0xC7DBEE1BA7C060A8ULL, 0xEF5268227446D260ULL, 0x946FCE8F5731138DULL, 0xEF4D1D4F2CE69372ULL, 
            0x4FC27AEADC7BDBEAULL, 0x5F5ABF0EBA64831DULL, 0x98C7D4AB292539D9ULL, 0x43C360986A0145F2ULL, 
            0x1FF5366241C863B5ULL, 0x264F2AABB26CFDC8ULL, 0xA918BC362978B8A2ULL, 0x5B8954B58232D875ULL, 
            0x3D94F2D60DC980ADULL, 0xC9FE2578E181D390ULL, 0x65D6BF779DD56D08ULL, 0xBC6EF66C85288AAFULL, 
            0x91B27E569500F0CDULL, 0xDF53D49E5D7ED4B6ULL, 0x976CDBC1462BACADULL, 0x9ACBE07C3C5B1CE3ULL, 
            0x061770B767C11172ULL, 0x628104F98200C408ULL, 0x9EE2C994FF907BE4ULL, 0x1296859FA23C3EA5ULL
        },
        {
            0xB051F59730BBA0BDULL, 0x83640AEA7FCFB193ULL, 0x6F1C28DEF3DB8204ULL, 0x0CF5DBB466238B50ULL, 
            0x31F822B78B33B183ULL, 0x23DBA487072C87B4ULL, 0x59D074C17CFE560BULL, 0x83C2F8912EB9BD07ULL, 
            0x15360FBEEACDA445ULL, 0x94CF1C012529637CULL, 0x939F50307C7F1228ULL, 0xC9C5DB5C5D4790FAULL, 
            0xC70241E0AA9413A7ULL, 0xEEA9E34261EDF105ULL, 0x4C23402B34CF57EAULL, 0x89994788023B630AULL, 
            0xFA5B2691483C99FAULL, 0x91D107AC917E64D4ULL, 0x60B1AA16259C343FULL, 0x9C7A0058D1BEBA68ULL, 
            0x4450FAFAB9E61AD7ULL, 0x62132EA7B5C147E6ULL, 0xAA9114C2E31BD96CULL, 0x622C6D1C4712FE6FULL, 
            0xF55948DBBE052ED4ULL, 0x792BA658E03A0C2BULL, 0x698808140E1AD231ULL, 0x5E600141979C155FULL, 
            0x339C95DB527087EEULL, 0x836E6CAC4B2B7876ULL, 0xFC5D56EC778DA75FULL, 0xB02E54857A0EBA86ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseEConstants = {
    0x12E021CF22B5B3AFULL,
    0x8B1FA3940A41C6DEULL,
    0xFAF5DF54028B7E5DULL,
    0x12E021CF22B5B3AFULL,
    0x8B1FA3940A41C6DEULL,
    0xFAF5DF54028B7E5DULL,
    0x5280F89496EE81B6ULL,
    0xD1268ADC192EE234ULL,
    0x7A,
    0x98,
    0x85,
    0xA0,
    0xF5,
    0x7F,
    0xD6,
    0xFE
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseFSalts = {
    {
        {
            0xAB33433BF0B2ED29ULL, 0x6B7BD741D383C395ULL, 0xC4D76782D9B8032CULL, 0x513AF1128D16F0CAULL, 
            0xF360711B337759D8ULL, 0xA8FF1738CBA71681ULL, 0x69232928CC39BBC8ULL, 0x349D66409BD828F5ULL, 
            0x5ABD069D0494EDD0ULL, 0x8EC5AF37AF35FD8CULL, 0x33DE5122852F52FCULL, 0x33CDAFBD2BFDA667ULL, 
            0x081ADFA23E50C1C7ULL, 0xD3BB4136D68C002FULL, 0x8CD352CE0C57B182ULL, 0x50E957F64F270635ULL, 
            0x49FDD470B7FDAAB3ULL, 0x9442A44042B174F4ULL, 0x0638543B7F023F5EULL, 0x3ED792133FE2F5F0ULL, 
            0xC269E1352ED5F947ULL, 0x3372A2BE5D7E10B2ULL, 0xB5E645A3A397A300ULL, 0x0AE08BCDD93FDFAFULL, 
            0x6240A0E6E9295A5BULL, 0x1721B7176FCD96E1ULL, 0xDC1766ACEE15802CULL, 0x67809F6DA7516E53ULL, 
            0x8D0B3950259E1D9FULL, 0x90D01B75B8C9718BULL, 0xEC0EC1C561659538ULL, 0x35FF31E934C79668ULL
        },
        {
            0xFE23C9CCCCD95DD5ULL, 0x3B6D5CD06B61D398ULL, 0xCAF41721618A68F5ULL, 0x29811F7F80FCBAF6ULL, 
            0xB8319B359AAB96FCULL, 0x9CD9200AFA35BBA0ULL, 0x50C16CD771E96BA2ULL, 0xFA3C91FADACFEA6EULL, 
            0x0332910B57FFE5B7ULL, 0xF5CC71D06B816B2FULL, 0xFA5A31CB3C9828E2ULL, 0x3088DE03D2EFB3FBULL, 
            0x23473277E905E1A5ULL, 0xBAB58C3977E2AFBCULL, 0xA8241D84F216E48FULL, 0x7325876B94147EBEULL, 
            0x3C56E9A201FD187BULL, 0x1AB023B39E1D305AULL, 0xEB3B2763F08EF1B6ULL, 0x1816796CBB1B9A70ULL, 
            0x3660CD260A4EDC3AULL, 0xEC41B75ACD7F4E63ULL, 0xA61E0641D893ADF7ULL, 0x839D51FB0D0E82CBULL, 
            0x199645F80ABB39B2ULL, 0x8B40CF457284530FULL, 0x82CEEF2B01294A9FULL, 0x074CEB83AA65313DULL, 
            0x0ECDB3FE4B55EAF3ULL, 0xAB8ADD3FD5236A38ULL, 0x80E36D82EA0FA717ULL, 0x9FF8B9A2F59B30E8ULL
        },
        {
            0xFC67BDEAD09F6A75ULL, 0x8291CBE5143B0F1CULL, 0x472771B61E01548FULL, 0x527A8B671FABFDE4ULL, 
            0xD3F6D906A51C1EB8ULL, 0x5B92ECC3DF6BD177ULL, 0x4B26132106300AE9ULL, 0x1723CD97DB0E1CB9ULL, 
            0x95752074633D09ACULL, 0xBBCF36B5D92A3F14ULL, 0xC4F22E39AFF2B736ULL, 0x9C1B4B816678A5B2ULL, 
            0x028840996C2BD260ULL, 0xB69DC044B149C7C2ULL, 0xD0E337E684F463B9ULL, 0xE947B77EC3BFCE48ULL, 
            0x67E1F00FFB282D75ULL, 0x23E3EE581BD1FF04ULL, 0xC2C7C5FEFE161BEEULL, 0xB8951275BCD8FAC4ULL, 
            0x90C27FB8F54C8DA0ULL, 0x108635B2764548C2ULL, 0xCE5570DBF65DB4E2ULL, 0x9B3E1E99A0AE5B70ULL, 
            0xF79EFF352ADB41C9ULL, 0x5DA9F9784F63E473ULL, 0xE8B320582262E7D5ULL, 0x7EA0D2EE06BA700EULL, 
            0xF532CFA322C47C86ULL, 0xBAF6710306C4A258ULL, 0x15D407A70B4100A2ULL, 0x1AA9D41EA2FA8FE6ULL
        },
        {
            0x6187AF8B564E233DULL, 0x58DE4A395A74F4A2ULL, 0xBE0FDC9BF2FC628DULL, 0xF8EAE20EFCC74E62ULL, 
            0x742B6271071C742AULL, 0x66EC38E08452B609ULL, 0x08E62B27D85E7815ULL, 0xA2664F0E299233C2ULL, 
            0x21F2FF752EABF36FULL, 0x4CAE443B6C7EAAA9ULL, 0x7CD3C10B423D39FEULL, 0xCBCEBB6747843D3DULL, 
            0xD172889985AC49B5ULL, 0xA7A7ED6F643DD617ULL, 0xA34E96D307872DB9ULL, 0x3F7C4676D291BBACULL, 
            0x8E8BADD10771E712ULL, 0xF2E8538328856EE3ULL, 0xF73D33E5CEEFDC47ULL, 0x08A0398124432666ULL, 
            0xC030C96B1E1D3A9EULL, 0x75981172F1E16D17ULL, 0xE976811FD618428BULL, 0x68DAC70E85970026ULL, 
            0x6E55D2DFED575587ULL, 0x6AB637070C751A69ULL, 0x583DE05CE2C91553ULL, 0xC7AE18C6ED42E541ULL, 
            0x0D598E2332F6C507ULL, 0xB8D2A7961D30C6B0ULL, 0xC003238C645F7D61ULL, 0xC874AC2D42DA5339ULL
        },
        {
            0x2E9C3CB6873BB292ULL, 0x22BCD99A0022BAD7ULL, 0x7128A5B1F51D3FC9ULL, 0xC7B441253014BBDCULL, 
            0xB42A9358F747E43BULL, 0xC4E8F213C7C58987ULL, 0xF1465A80075EA816ULL, 0x861D8CD55BD956BFULL, 
            0x21FDF4D20FCEFBF7ULL, 0x0AECEBE7D8E434ADULL, 0xD4FBB03FB67E14F3ULL, 0x949737F517399393ULL, 
            0xD58E5DFDC6C12EC4ULL, 0x7F901E071B1F3EC8ULL, 0x1093D24CA374CA96ULL, 0xED64DC3B01AFED16ULL, 
            0xB249464208A7426DULL, 0xE0DE6566D6FC35D0ULL, 0xC12ED22C9400A5A8ULL, 0x16459A1EA5165E54ULL, 
            0x4EAB8342C4815A23ULL, 0xE39DF77987218960ULL, 0x18819B74A627FD9CULL, 0x2B3B2E2B16DFA26DULL, 
            0xEC479E58F42ACDFBULL, 0xB087D8142BE489EEULL, 0x1FFE59812BC2DCDBULL, 0x5662C64BD5458D50ULL, 
            0x01936E8E8870176BULL, 0xB884B4EEC22C2219ULL, 0x01AE066122AA6C25ULL, 0xDE1D7CB3BCD37F92ULL
        },
        {
            0xA0D511C6EDEF2154ULL, 0x5BB27857FC8C8D46ULL, 0x759F3F38680325FAULL, 0xFB405FB14BB611E1ULL, 
            0xA89B6741AF223CFFULL, 0xFD075FA49B2BA24CULL, 0x71DA026DA1FF5672ULL, 0xDEC527D474435D6DULL, 
            0x1D333D5267E0B053ULL, 0xF43BB01D8A860BBCULL, 0xFCCCCA221B99F7BBULL, 0x0D354510DB4F5446ULL, 
            0xFE8DA34EB2A767E2ULL, 0x0B08AC290B061BE5ULL, 0x7488F68134D58A4CULL, 0xBAC9C2C535A66A8CULL, 
            0x02420CBFF145FB47ULL, 0x89A7E36EC938E609ULL, 0xAEF9D6F77471EA09ULL, 0x728167A76F08949DULL, 
            0x7863AB8669F2B2CFULL, 0xF8C9250C89DC7D92ULL, 0x92CE77DAAAB0CC93ULL, 0x3F39729477DD8F67ULL, 
            0x56C905F98C5F5BF2ULL, 0x521886E74051247CULL, 0x0BF842213E74458AULL, 0xC9AD143D50DC17DAULL, 
            0x02E540AF05599808ULL, 0x0A28538FC8A542D9ULL, 0x486EA878DA753D38ULL, 0x1D94D0417CBFEEAEULL
        }
    },
    {
        {
            0x52E5A0E457C2B95FULL, 0x7B8F280D4D1439C7ULL, 0xDA6C094BF2728F21ULL, 0xF56FFED3E5D9F591ULL, 
            0x609EF444CBCE01A7ULL, 0x32EE862C7C26B6DEULL, 0x7CE7296102103E30ULL, 0xC6D812996D77CF64ULL, 
            0x0474ED4B4A48AEB6ULL, 0x070256DF98AC5726ULL, 0xFE62B8E056EAA778ULL, 0x34FB149A29FB17D1ULL, 
            0x5979602A971374C2ULL, 0xF0BCA0D798AB5E30ULL, 0xAD951D12C40F9C6DULL, 0x266CB775F4A2C8CBULL, 
            0xD42FECA0E552E07BULL, 0xB9AB9F5B84B24455ULL, 0x946C8C695DB06BDCULL, 0x7056E440FB13278CULL, 
            0x776DCCE209A94DC8ULL, 0xF42D73CB301393B8ULL, 0x2A658F37EF25FBA6ULL, 0x845BA585B6C9D8D9ULL, 
            0x5346867675EF440DULL, 0x883DD7BEFC1439A9ULL, 0xE85C77EBF6865E75ULL, 0x3E3877A506359505ULL, 
            0x1C4CDC9CC7E9215DULL, 0xB007FC5CE2AE4749ULL, 0x15858EE7F5DFF658ULL, 0x200B82391EAB4BA6ULL
        },
        {
            0xB791A7B9FD4E7A84ULL, 0x25620E092D1CFDB4ULL, 0x96FC9E06E3B7AB32ULL, 0xEA99CD9EACE12609ULL, 
            0xB6611F865E7F186AULL, 0x83A38019B1E35918ULL, 0x78447E3321DFD5C0ULL, 0x77CBB574BCF911A1ULL, 
            0xD47F634415CC8846ULL, 0xD7B8886BA4A88C87ULL, 0xABD83569BE9A27D4ULL, 0x973F83978D95DB9DULL, 
            0x7BF38AA67B7A17BFULL, 0x4B3100AC43DAFFC6ULL, 0x186EC44BC09EBC12ULL, 0xF48CCB9B6A94F84DULL, 
            0x0189876C125A2F5DULL, 0x278E141F685BF073ULL, 0x40B4ABB6B1DD226FULL, 0xAB4B44953C409918ULL, 
            0x903DA77EF3AEC27CULL, 0x5B2C37A23F46D0EBULL, 0xBEE1CB5153A0584DULL, 0x3CE1879EA89565F1ULL, 
            0xBE8482B8CAB50162ULL, 0x5FB38F95EDC66811ULL, 0x8B5B8872BA3B2D8DULL, 0xA7A0ABF304BF9A01ULL, 
            0xAD8C60562CC6BB8DULL, 0x7F3AAD762C489A44ULL, 0x5D496AD17B24FA9AULL, 0x6D5BE06C20EAB1B1ULL
        },
        {
            0x45E9FC2E7D03BD41ULL, 0xEB0E700074E32DE6ULL, 0x7478AA403711130DULL, 0x1CA24CDDC04A8EC7ULL, 
            0x805D33349CC6097FULL, 0x6996F146CD597795ULL, 0x60DC2027BFBED2ADULL, 0xC59CE03D42F375D9ULL, 
            0x184DE7DE8CBD760EULL, 0xAB632189F6E43DD2ULL, 0xAA46D06F5E096FB7ULL, 0xD831D8296778229FULL, 
            0xBB4F809EA59B1248ULL, 0x1EABA86ADA07B22DULL, 0x3979366DB6055BEAULL, 0x802ACA2D93D3DA6FULL, 
            0x8B314081A711275DULL, 0x5B4A4804F1CA1D79ULL, 0xF436486B294DE42EULL, 0x148ABD43C008871EULL, 
            0x8CD2283383C039C5ULL, 0xBC221FB1E905449EULL, 0x9CE64CBF979CF44AULL, 0x2151D97DE29FEAEAULL, 
            0xA4E00646A52AD17CULL, 0x4243E1DEA9C58668ULL, 0x2EA966FB0B6095BAULL, 0xC702E70935436F19ULL, 
            0xC53C4E2A8FA57C04ULL, 0x01E1F63583763B04ULL, 0x05B0E299A3F0250AULL, 0x27811C08DD2F15AAULL
        },
        {
            0x1FEDDC922027184CULL, 0xA69F1CB08D9D5ADDULL, 0xE9264F5F2C86EEBDULL, 0x426B27E55B9137B4ULL, 
            0x3666273C6FC9FEC7ULL, 0x01A31EA9824D4683ULL, 0xE439A5C497DBDAE7ULL, 0x3BEA97BD7C2F6C05ULL, 
            0x3838A915BC7FE946ULL, 0x026556AC89EB2E08ULL, 0xD0346BAEBB011159ULL, 0x526478E114729D87ULL, 
            0x39BB61AFDA0DFF68ULL, 0xF5C1E7C28649ACBFULL, 0xC3250E7F52B440DBULL, 0xFB576BF009C79C02ULL, 
            0xF51B057AA6BE9152ULL, 0x2D66BA48782F9814ULL, 0x60EE997ECB3847B0ULL, 0x55C7299AEDB053BDULL, 
            0x697F82D243A34F92ULL, 0x2F805B8884064F54ULL, 0x040E1BD1EB47F292ULL, 0x18289110A5C91055ULL, 
            0x78AFA858A36D4C76ULL, 0x317DAAE6A22F7F2BULL, 0x09EBC376F76BDC0FULL, 0x55B57B4D921FEDA4ULL, 
            0xAF2028F45DF3EACEULL, 0x014B74ED3B906E58ULL, 0x28B1BA7476A17DE7ULL, 0x4D6F44BAE7237155ULL
        },
        {
            0x528EA9E17B1AEDA5ULL, 0x8450168B22EF18E0ULL, 0x428D6811E78E26FEULL, 0x581E0B8BF7D750F4ULL, 
            0x14B1F70769F4E125ULL, 0x4CE137152E378BA5ULL, 0x95B2F7E61DCAB660ULL, 0xBC6A6DB57F403330ULL, 
            0x33E1B19193DC9D3AULL, 0x80EDF57D21CE1138ULL, 0x058B9C563CE1ADFAULL, 0x2E2E2DD60EB0A0C2ULL, 
            0x74A3C465EEC55DCEULL, 0x8ACA270D6746FB53ULL, 0x65FE645058E62630ULL, 0xF1CCE5D3C6A28646ULL, 
            0x0C921FBD020F75E4ULL, 0x35E4B1019F5C3D39ULL, 0x18FEBD46A5AA7183ULL, 0xF6D30C1050D974A5ULL, 
            0x9F0121C4A06554B4ULL, 0xF58CF7242FF3CE44ULL, 0x0E91DD747F81F0A0ULL, 0x5FCC3038FE9FEB9FULL, 
            0x5A066308246F72A9ULL, 0x0F86D4858AC1F5D7ULL, 0x5E6AB148B79189A9ULL, 0x908FAC83FC408FA6ULL, 
            0x99CCE434BB2FEDFEULL, 0xBD6F7EC8FC4C77E0ULL, 0x98B5E6008FC3CE4EULL, 0x7A3C1226491E6EF9ULL
        },
        {
            0x516125D507977DCBULL, 0x4D4C7605CB04ACBBULL, 0xDB16C59F5738255DULL, 0x90862382A27CEE5BULL, 
            0xAC3AD653D99CDB37ULL, 0x407A11979A346BB6ULL, 0x6D7142DA6BA6943DULL, 0xBF6D7D5FC971D6E9ULL, 
            0xE6AF5FFC6C91BF0EULL, 0xA0B91751577BEB0BULL, 0x46BF631AE47011C9ULL, 0x2BD5A313A8078879ULL, 
            0x04508F3C523D7E90ULL, 0xC54AB8C26D8D5738ULL, 0xEBA659D0A26E017CULL, 0xF6BC8C828219B95EULL, 
            0xD0F8F81DCDFA08F5ULL, 0x475C0A5F5BBA5ACEULL, 0xCCF032BEB2E59B14ULL, 0xB3D1F2F99565252DULL, 
            0x9AB49EC4606A49C0ULL, 0xAD825BA469AB1E68ULL, 0xDD44F9C4173148DFULL, 0xF3B809D8A8A0C040ULL, 
            0x4940356CA0D22A88ULL, 0xEE0340A653E3A714ULL, 0x026977468AAF9E5DULL, 0xDB4A14C77F02D453ULL, 
            0x766CE368B78A55E0ULL, 0x03E24005B7DCFACFULL, 0x41773A1DCA0FD351ULL, 0x45F342A48607D7BCULL
        }
    },
    {
        {
            0xE7FC6680FA990526ULL, 0x61B15403F46E5C52ULL, 0x2529BB259C1B4DE6ULL, 0x044783DC1CBD99BFULL, 
            0xFED54CCF82829585ULL, 0xBF64DEB39BC95837ULL, 0x2250ED29D6FCDA9DULL, 0xE9AFFD4D4DD6F754ULL, 
            0x127D30A4C1E4A0E5ULL, 0x6489BC9A22D248CBULL, 0x20E932C565368730ULL, 0xBAAB55A95C90CD2EULL, 
            0xF9E2A5A6F83803C8ULL, 0xAFC316C0A0B92492ULL, 0x7992CB9B75FDDBE5ULL, 0xCA4B08241C3D9E2EULL, 
            0xF39F4C1722B130B3ULL, 0xAC4CD30B554E44C4ULL, 0x6F1413591E9D8A4EULL, 0x0A21480E9E2E11FFULL, 
            0xB0981CF1DF7DA6BBULL, 0x98A53FD9BC53CE28ULL, 0xA3F4018091A40D3DULL, 0x2F20DE9770F43EC8ULL, 
            0x1DA60D15BC8D6E40ULL, 0x3E439C30E7E81A5CULL, 0xEE14BD2662AFF723ULL, 0x3BDE36E672BE893CULL, 
            0x38F10DFB7034FCFCULL, 0xD32B0B70FA917AE7ULL, 0x07FE59C75D06F05BULL, 0xCA3EF1501A254F6CULL
        },
        {
            0x8D8F868304670C88ULL, 0x5A8DCE0A4F70BE04ULL, 0x60B8CF7471E6AD8CULL, 0xABB6016DCC58B124ULL, 
            0x4E3090972DC7E7F6ULL, 0x16793B75D6D2B66BULL, 0x48D03AF9F1FE70A3ULL, 0x5B6C57DD3450A530ULL, 
            0x31F8832E725689CDULL, 0x8A9639D41D13DAF0ULL, 0x1426761F696487BFULL, 0x761D5C82F8137258ULL, 
            0xDC329321F762CCACULL, 0xFA0A4C75E0C7C2EDULL, 0x85D07D7C1AFDF508ULL, 0xC745D81436EA60A9ULL, 
            0x87F4EE3FD2125148ULL, 0x336C6630F885A756ULL, 0x5ACC64B8C9EB21B9ULL, 0xE87298A8D4A17CDBULL, 
            0x270860FDEF6BF1A4ULL, 0xCEDAE043D413CE76ULL, 0x8E7C88AB6D998988ULL, 0x6F97E42BD06FC995ULL, 
            0xDC96756338EFA86EULL, 0x152CEA4EC8366281ULL, 0x39C7D91565D82F32ULL, 0x6384FB4FB3012E86ULL, 
            0x54203EE51FFD46BFULL, 0x9B599FE78AE17691ULL, 0x614BCB73971E06DAULL, 0x182840B6C3DB634BULL
        },
        {
            0x6ADB86DF34239434ULL, 0x45B9EFA0C8DF44C0ULL, 0x1F9815819F89701FULL, 0xD8030B71419F3806ULL, 
            0xBF1E737DBCA88257ULL, 0xD2D6C85F4BCBA3BAULL, 0xC2D22AB774EF7B47ULL, 0x659F2724B889FA65ULL, 
            0x93D62427D7506C3FULL, 0xB1EE85449B43F661ULL, 0xFCE5AAD5BBCEA92EULL, 0x49CAF9FE8AFEA76BULL, 
            0xA7FF46510085D9E4ULL, 0x79D3C72B51F8B52FULL, 0x6DEE5AA9F4611931ULL, 0x20E429870E83785FULL, 
            0xF782DC287B8FFDE9ULL, 0x241BF0FB87239097ULL, 0x0AE37F78B32DBDA2ULL, 0xF2D53C02018D7E19ULL, 
            0x5F8253D328124B11ULL, 0x9FC2B706F37ECC93ULL, 0x27B7514006680F60ULL, 0x0E33C44BD30B7C14ULL, 
            0x3EA1F65AD4455BDBULL, 0x537C277904CB29C2ULL, 0x6136F9F468E7F37CULL, 0xBDF639C09C920B17ULL, 
            0x1F23E9CB04752A96ULL, 0x1CB25BBFD6A4E9A0ULL, 0x8686E6061450DF8CULL, 0x04510AA2FA469E16ULL
        },
        {
            0xA486437883A4F5EAULL, 0x7A262E31D8F6EA26ULL, 0x410AF36D19C20C66ULL, 0xC782F6AAD7BCD85BULL, 
            0x17E25EAA8A31CF0BULL, 0x66D4C097327EA3E9ULL, 0x6CB233FE7B412356ULL, 0xE9AC373E7C8D04EEULL, 
            0x693D4387664A548AULL, 0x57EC22181F85CCEFULL, 0xFE33F0DFAFD4EDA1ULL, 0x2162C04437500C14ULL, 
            0xDCA8D0489ECD7BB1ULL, 0x2DF57889392499C6ULL, 0xA3DB76A5EDEFA49DULL, 0xF60A8AEAC239C03FULL, 
            0x943C56DC1F4AEAD1ULL, 0x8EE4892493EE94C4ULL, 0xD45E5597CEC45AAEULL, 0x47D5466D3187624EULL, 
            0x3152E89C7C9DB57AULL, 0x3E4115937C3D5C5EULL, 0x8F7262468A47ACE5ULL, 0xD964C3F3D58E7026ULL, 
            0xFC2517AA276498A2ULL, 0xEB5D36D5F750FC8EULL, 0xFB7F8BFF9DD191C5ULL, 0x54ABE8C3A61A9C5EULL, 
            0x39627E4AA0BBA555ULL, 0x796289D4D636C658ULL, 0x26CF897B6B0EABC9ULL, 0x5003248E970E77A9ULL
        },
        {
            0x7807003EE4767B49ULL, 0xC7B9029D2F377149ULL, 0x4125638A25288E60ULL, 0x890087AB405B5B8EULL, 
            0xDD92DE4A4C08CF81ULL, 0xCE29E196CB31B5E1ULL, 0x094360593D79474FULL, 0x0F66AE4C83E1CF29ULL, 
            0x4BB0AA36AA834B5DULL, 0xC623EBA33E1B570FULL, 0x0B0C95C1C0AC6148ULL, 0x2A3DF66243818CA6ULL, 
            0xEBD4C04D4147AB2CULL, 0x1A19D4FFB33AF54DULL, 0xDCD5BB72D3C32821ULL, 0x2D73D241B45D8AFBULL, 
            0xF441F8BC59A6DF47ULL, 0xA61EEA6B8FD0E615ULL, 0x99EDF2D2CAD8BD2DULL, 0x6DBEB1BFEB33AB2FULL, 
            0x69740B7C30076AAEULL, 0x56AB092516B3D269ULL, 0x3D08581E431F3804ULL, 0x32ADCA770E7DE821ULL, 
            0x268AEFEA5FA5422DULL, 0xEDD27863755B5A96ULL, 0x6DC6A5473C223E1FULL, 0x6A5267255B6EDC2BULL, 
            0xDEBAC330A584B148ULL, 0x803EA98E31F18690ULL, 0x3433DD546F9EC57EULL, 0x36B13C4FFB5BFEC5ULL
        },
        {
            0x62F353A8F7597DF5ULL, 0x4CDCEE37524D4E69ULL, 0x2975F5BA5F1D2AEDULL, 0x7C06339E6E06BD35ULL, 
            0xF7FD197B1C2BD6D8ULL, 0xC95EB821B5DBE9E6ULL, 0x7DADB818D2D406F4ULL, 0x261122BF515A5160ULL, 
            0x29F8C8C8CFCB651DULL, 0x613C327566CFE12DULL, 0x9C4A6609B447CA16ULL, 0xB3E467DDF5A96DD2ULL, 
            0x5EEBFB470534BA03ULL, 0xAA5CAC1273FA7EE7ULL, 0x36E3DEDB05BD729EULL, 0x80C28450259AF1DCULL, 
            0x91A4F94CDD0420C4ULL, 0x272E8047E4570368ULL, 0x4E9826442FD1DCBBULL, 0x32529D8C769A4FDDULL, 
            0x54FDE3E70182A13AULL, 0x73FD38449E185C25ULL, 0x960C3D26D23CDE10ULL, 0x3013C9BB781B6C89ULL, 
            0x035B6B02F0AE5321ULL, 0x7937892D5176CBAFULL, 0x95D5481A712C4DF9ULL, 0xFB51726DAD7FB0D5ULL, 
            0x9BC8B94C06400B03ULL, 0x3DA3D323A224737BULL, 0x47B19A2BFCDB5C9EULL, 0xC575C119C31064ACULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseFConstants = {
    0x343094AFF8F27575ULL,
    0x1B331743196D584EULL,
    0x2E68EE376690FA78ULL,
    0x343094AFF8F27575ULL,
    0x1B331743196D584EULL,
    0x2E68EE376690FA78ULL,
    0x908C0F6578E9BEEFULL,
    0xA9351841F0792AC4ULL,
    0x7E,
    0xEF,
    0x49,
    0x3A,
    0xC1,
    0xC5,
    0x99,
    0xA2
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseGSalts = {
    {
        {
            0x092899F7E0A0B93DULL, 0x1B8F67C3B62B8EE9ULL, 0xD6CD9896035A16A9ULL, 0x7F5CD9F6AB3BC94EULL, 
            0xBE3AE6AC6FCEFC91ULL, 0xE68E851259A65BEFULL, 0xC9AFDB722003305BULL, 0x1FE5E55250F31047ULL, 
            0x6E0413CEDE85EAE5ULL, 0xDACFB71B1240BB5DULL, 0xED9EAF05D306D9F4ULL, 0xAE387C337AC49C2AULL, 
            0x386DFD64062DFF12ULL, 0x79B6D10C7D2C5220ULL, 0xE31C2C9A29872DD5ULL, 0xEE8F1D657147A401ULL, 
            0x60EAA7F147F6FE2CULL, 0x268256E3C200DE9FULL, 0x74F83893633739A1ULL, 0x4E17B79BA3F3DBC0ULL, 
            0x4F9ADCC39964288DULL, 0x773777FD45358B03ULL, 0x6C665796BD0B3D5FULL, 0x56864518D0CA6F4BULL, 
            0x165A3DDE7CD11653ULL, 0xDCE0E93C4CE675D2ULL, 0x25FE8F186955A79FULL, 0xFF3F4D107A782BCBULL, 
            0x658BF65D0472DA29ULL, 0x668D78D87FEDA944ULL, 0x1010ABCC99E3955FULL, 0x8BE6354DA86D0266ULL
        },
        {
            0xDF1B36A2C659A968ULL, 0x8C572DA2077A02A2ULL, 0x7A2A6573FC2AE6EFULL, 0x9BD9C446A24C7EF2ULL, 
            0xDD5522C4B5274434ULL, 0x7A49C9CCBDFA0437ULL, 0x657384A7FCFFE84AULL, 0x7FA3B85FC413C7C1ULL, 
            0x68026B7593B5EC7CULL, 0xBC70FE35F7F9045AULL, 0x119A90BFABD58292ULL, 0xD458BABED5F89F92ULL, 
            0xCD4405D9CDEC32B6ULL, 0x657A84FC2B50E8ABULL, 0x8D368ECED1B88970ULL, 0x3DAC1B64D8C09AF6ULL, 
            0x05182E5EC25950A3ULL, 0x745D76D5AAA1C696ULL, 0x59FBB042BF661B1FULL, 0x7D89BCB9F755FDC6ULL, 
            0xB44675CE9720621CULL, 0xFAA0581A6D935AC5ULL, 0x549687575561E69DULL, 0x9C2FAED26C2F26ACULL, 
            0xEA0EBCF77A387147ULL, 0x450AFC61E7F396A3ULL, 0x036B9C4C18B8CD53ULL, 0xC4F54513F8BB35D4ULL, 
            0xB37F0A99088C72F1ULL, 0xE8DDC3792926ABC1ULL, 0x515C45B0FD10A0FDULL, 0xB3CB87E3D90E3001ULL
        },
        {
            0x324E2E977E8250D8ULL, 0xE823F17AE7FB82AAULL, 0xBCEA1F27C4F0034DULL, 0x65CE9398E3678B04ULL, 
            0x04C3E7A8736FC98AULL, 0x150AFC7A5876B0EBULL, 0x62BBB3BC64479FF6ULL, 0xE374ACEAECB87EABULL, 
            0xF3E16FBE474A5EA6ULL, 0x9E744680DDFCE8AAULL, 0x20307C270CE8BF16ULL, 0xBA89BE778249B3E5ULL, 
            0x4FCC7912040E99E6ULL, 0x1123279AFC3BE0CAULL, 0xA231744F98EF8418ULL, 0x8B90B3173F51F108ULL, 
            0xACCD75384402245EULL, 0xC612E995252D0AEAULL, 0x602FB2A232A511C9ULL, 0xD5F1731829F0F93CULL, 
            0xE5B5AF341EA684D2ULL, 0x92D7AB7808974DA6ULL, 0x6BCAE9F37B6828A4ULL, 0x012D5EAB2DD94633ULL, 
            0xE40B2DE988EFBFE7ULL, 0x95D5455B5D2BE9F7ULL, 0x20B94B8422FC4F70ULL, 0x67B16A4F07403161ULL, 
            0xC40F1D0DBE5524F6ULL, 0x9811503ECC84484DULL, 0xA87E852388AC7203ULL, 0x27598E1DBEB7FBE9ULL
        },
        {
            0x40815C74B926D038ULL, 0x25CD38FD8F5757CEULL, 0x8456F99ED85E35F3ULL, 0x4EC11B44E8CD1350ULL, 
            0xD0D8F82F099EABA7ULL, 0x5DFD8B0975A520EEULL, 0x3A1FC21A6F6D7A4BULL, 0x23C5C4E09A17D849ULL, 
            0xF60C5229BFE8EE2AULL, 0xC9E5C8CA6AF4A2B4ULL, 0x8AFEC8AE1A3484BCULL, 0x7F28C1073B16EC35ULL, 
            0x35D216A3DBF78561ULL, 0xD31C60C7F601433FULL, 0x9C7A0C4BC0EAE959ULL, 0x61C89B581BD129C1ULL, 
            0x3B8FDD0EC4DABCC2ULL, 0xA312221F2DED9E7FULL, 0x56FA4FB3B1CA5AC8ULL, 0x93CE7E2E9CCAA10DULL, 
            0xAAC11A1D693638A3ULL, 0x7A245202775B51E7ULL, 0x9357B4FAA406A0BAULL, 0xE19F0DDB71FBEB2AULL, 
            0x5A6689708A742112ULL, 0x8A5A912D7D482069ULL, 0x3CAECC97C8FEBA6BULL, 0xCDB74991EE9F3DE6ULL, 
            0xD92B803D2EE78672ULL, 0xCD62A0B30573E651ULL, 0x17E43B262F3C3CC9ULL, 0xFABE69B2ADB0DEC3ULL
        },
        {
            0x1D1C21F905CBFA5AULL, 0xA6116C2B4515538DULL, 0xE16BD0BFD005EA66ULL, 0x134459635B702A79ULL, 
            0x34C89999BF225662ULL, 0x1204961D08B39848ULL, 0xA118445333C6A57BULL, 0xF79A63F2FF88790DULL, 
            0x88931762B6146287ULL, 0x92EA995BC6D80994ULL, 0x50E459D5EA9F50C2ULL, 0x2195C3AB6E99F0DAULL, 
            0x304AA1F39CFFD0F4ULL, 0x5CFA4DBE7F14FC82ULL, 0x8313343D964ABB6FULL, 0xFB094ECE26D6CEA1ULL, 
            0xC77A9D97D72B825BULL, 0xA5361B65C4DD4B1FULL, 0x256332B8D333EC2BULL, 0x4F2FCC3EC245382BULL, 
            0xED13F62C7EA97D02ULL, 0x7A65AC795335FAABULL, 0x97DB2212E3C8B448ULL, 0x28E09C4D1BD401FDULL, 
            0x6FBDB37234FBFF26ULL, 0x908DBD4F0A0DBD77ULL, 0xE76D1A544E3979D9ULL, 0xB8437C89BF91CC82ULL, 
            0x03E4B2239A968C43ULL, 0x0B843AE04E2860F4ULL, 0xDC496A84FB7172FFULL, 0x14F37E578BD8590EULL
        },
        {
            0x72FDB6BB329A8AC1ULL, 0xD37591AAB269C795ULL, 0x64DA13A28E3EE7ACULL, 0xCF89B186F57E1F7AULL, 
            0x7B3494A884DB9FE5ULL, 0x6F2409B807DF24B3ULL, 0x81DC9A7D6A2650DDULL, 0x030B3489BA7ACBADULL, 
            0x3FC1F19A199AFAB0ULL, 0xD41B459AF8D10215ULL, 0x1401083FDCDB4F29ULL, 0x05BB1B2E39D1C006ULL, 
            0x8A721304A04289FBULL, 0xFCCE1A53FC348684ULL, 0x5C8828F5488AA38EULL, 0x170DCA96893EDC4CULL, 
            0x4A48E62D78691CB9ULL, 0x8BAC59F45AE234F2ULL, 0x64B8806DAB073498ULL, 0xC2C206BBC98D929CULL, 
            0x7199943EA6166DC0ULL, 0x4D2E3F84694ECAE9ULL, 0xED06206EA4A88FCDULL, 0x461FF6B2FE145BB8ULL, 
            0x9DFF63444FBC2F54ULL, 0xD1277A5B9E342490ULL, 0xFA9863032EEE40D2ULL, 0xF773DDCFC0618404ULL, 
            0xB7CF49D6D5B50608ULL, 0x558DE66C4F1BF9F5ULL, 0x41676AEFF42EC78DULL, 0x820E4979025DD18FULL
        }
    },
    {
        {
            0x2982600DD87E08FFULL, 0xF62F977DA3FFEFB5ULL, 0x7FFA6D3B6792D9A1ULL, 0xBE71C75A48648FBBULL, 
            0x1C3E580DAB8E1483ULL, 0xC144FC3D91B09C73ULL, 0x6AF7A61DCA186F63ULL, 0x7B6C87062B148AF5ULL, 
            0xC743F93FC6FAFF6AULL, 0xE6141941AA14DB08ULL, 0xFCA96EED4E60CCC0ULL, 0x9914980850E5006AULL, 
            0x659057C767F3EBFFULL, 0xFFF6CFFF0E568DD0ULL, 0xA8EA2203466EA076ULL, 0xD154BAC010BD8891ULL, 
            0xBAFA354B793E646FULL, 0xE4BA599B63762B26ULL, 0x949D114A66F4381BULL, 0x233AC28F0545A026ULL, 
            0x2120CDBD3B055F7AULL, 0xCBB5E6802D468964ULL, 0x43C2C23C3E76357AULL, 0x53F036368F529CD5ULL, 
            0xA9CA2AC7B156FD07ULL, 0xAE53575BDB6F0201ULL, 0x00C597E71C09CF5FULL, 0xB042957ECE302803ULL, 
            0xBDF2FDE791288755ULL, 0xE4DCB31832D7210BULL, 0xF9069724D067B0E0ULL, 0x55A0E413AF5B8B6DULL
        },
        {
            0xF0F01C9AC29AC982ULL, 0xEC7D9CB10202576AULL, 0xB54D991E1F3D85E5ULL, 0xC49AFEC484F956ECULL, 
            0xC199AD3656DA3C9FULL, 0xBDB0A0A41A6F70BEULL, 0x47C2C72B0D054DACULL, 0x3C2616FB025E66BAULL, 
            0x252575917C4BE10AULL, 0x815D1C1E0A254A1AULL, 0x73F205BBC41C45DDULL, 0xEE85EC9908768F85ULL, 
            0x42232281C7C676CCULL, 0xC0E0BC9A6CB069FAULL, 0x6C5BC5E575C60073ULL, 0xFED21A3F942E8DF5ULL, 
            0xF6041FEE1B40F724ULL, 0x0528AD7F229390C4ULL, 0x6420D83752C2510CULL, 0xBE7C947DF33758BDULL, 
            0xC6D63DCA0CA81123ULL, 0x9C28E9D48DA036A8ULL, 0x50BDF1E1807DA6B6ULL, 0x26308C7246CDDAF6ULL, 
            0xDB12D04DA15DD608ULL, 0xBE7A8BA762BA65CAULL, 0xE39A226051874C86ULL, 0x10423BE30A5E8017ULL, 
            0x3609FCF3021844F9ULL, 0x68AA7FAA1BF85DCFULL, 0xB1D0F19FB4AA8657ULL, 0x30CB906A5C05BD8BULL
        },
        {
            0x6493BCCD3B525044ULL, 0x83D1FE3A7B893177ULL, 0xD48A069D42986BCEULL, 0x7DEC60198840EACBULL, 
            0x990D35DCDFFACADEULL, 0x8AF33177688D1298ULL, 0x19BF1938748D57CCULL, 0x56872BF1FCFAB77BULL, 
            0xC7B67BAD94BAEDBEULL, 0x5344BA428B0FA546ULL, 0x6804BBA3764DA234ULL, 0xFCD35E8E29ABE35FULL, 
            0x06847325747D9DE7ULL, 0xEDCC4AE58ABBF40CULL, 0x895EB3CC4D3DA48EULL, 0x1D23C923C16B1873ULL, 
            0x9EC042153E3D10AEULL, 0x5A2B27EFDFDD0C20ULL, 0x5DEB23B26BD9EA8CULL, 0xB84976A72B721C70ULL, 
            0xAC74BA785A356FC4ULL, 0xE3F4C736D29D98FAULL, 0xADFF4C3B28C3BC0CULL, 0x1FC5D7424AEF0246ULL, 
            0x6540E02E168BF7E1ULL, 0x182D11DCFDDFCB87ULL, 0x6BA57EFBC3211B7BULL, 0xFF0CD08DBCBBD423ULL, 
            0x9F20909A2219CFDAULL, 0x9FAA6610C725C603ULL, 0xC1F141D9864ECC0CULL, 0xBF5D30BDF8E1B851ULL
        },
        {
            0x47C871D81B63FA02ULL, 0x52F11B1D72164804ULL, 0x0EE4B38C6FC4EDAFULL, 0xDB01A5BD3F69CCBFULL, 
            0x23655CEFC5AE341BULL, 0x4A2142934BC33FA9ULL, 0x10FBB411E8B093CDULL, 0x2B8D1B7AC752B1DAULL, 
            0xFE8CF4B38AAEBD59ULL, 0xA1CE941A192283FDULL, 0x9E367E37C546FACAULL, 0x988607D1595A06F5ULL, 
            0xC2000EA4E07B8A2CULL, 0x003677BA49843381ULL, 0x1C8230A9BDB03D4EULL, 0x9D7ECA89B90FC6F8ULL, 
            0x101EFF69C3FE10BCULL, 0x537D2A18390ACD5BULL, 0xE9F7F2FCD86E7320ULL, 0x1D9C96FDAB50A6F1ULL, 
            0xDB532277342CB514ULL, 0x409C6B22ABFCF91EULL, 0xD3F89168D4D19BADULL, 0xB1495FC63896D2CBULL, 
            0x06B99AEDE3656F1AULL, 0x95910677FEC7EA24ULL, 0x51FDE6484AB89EA6ULL, 0x56E090974B4C91F9ULL, 
            0x47901E2DBBA57FDAULL, 0x6B0E0EE54E654A19ULL, 0xE2EF6B36CD7A4D62ULL, 0x69A75D3A7EF67543ULL
        },
        {
            0x2CD4CFD0398A58C4ULL, 0x44C855793EFABE9BULL, 0x592A8C91D4C43C5BULL, 0xC2EC796C96D4E094ULL, 
            0x7D0B256BD47DD969ULL, 0x96B15624C1B3ADFEULL, 0xA8BA704EE2B48D62ULL, 0x759153C5450C4C20ULL, 
            0x8CDFDFFBA88BC44FULL, 0x88B4247D6E3D3611ULL, 0x46FA32B0F704256BULL, 0x9133EED07D15BF6DULL, 
            0x1DD90AA75B2E6710ULL, 0x5AB051EF193B5B19ULL, 0x7231BD1A2790C517ULL, 0xCFC3BC841977FDEAULL, 
            0x0CA1A59A97334845ULL, 0x17C0F182479D9C46ULL, 0x36190561BE679DF7ULL, 0xD41842E118888150ULL, 
            0x20D67DEC71E88009ULL, 0x0AD1279B70D7512BULL, 0x3986149BC59C6E57ULL, 0x7EF8EF952E29E44BULL, 
            0x8CE2EC6FF49D0D61ULL, 0xF738753C47C902C3ULL, 0xEAFFC027099D0C4BULL, 0x5F53AF2BBFE25D3CULL, 
            0x303FB112B92AEC56ULL, 0x89766E818A21EB19ULL, 0x0A36C8E42870BD59ULL, 0xD801B14C89F2F7F5ULL
        },
        {
            0x9E279A0FD068AA5AULL, 0x81C25EBE35704847ULL, 0x1B323F83448BFB79ULL, 0xBFFFECA8D118FE0FULL, 
            0x947A241ECEE3B516ULL, 0xEAE61C383566A88AULL, 0x0F5046D4F3BE2C14ULL, 0x08D970A5E592A77BULL, 
            0x8E181ECD641DD711ULL, 0xEDD47C4D90EF70D8ULL, 0xD7DD4E859A8A5DCFULL, 0xAD038D68054CCB98ULL, 
            0x703679B18569DD00ULL, 0x88F5BEE499B8B87DULL, 0x01C9CA104EC03163ULL, 0xF33C167D6874ED48ULL, 
            0xDA106B4043715AF1ULL, 0xDE5BA6DEEB84F40CULL, 0x31200D87DE4D84C3ULL, 0x48FB212068566C3BULL, 
            0x2C1E2005E2CB6DA1ULL, 0x75CCC365B8D4E78DULL, 0xC05853C97D2F08B2ULL, 0x9EA2AFB5A750446BULL, 
            0x03CD6A3FCC6CA51CULL, 0x2812EAEA51A9A851ULL, 0xFD1E45DD79D89086ULL, 0x480058F07FECFB7DULL, 
            0xAB82FD02BF2869D1ULL, 0xCEACD37F603B05FEULL, 0x0F153584C6DCFB72ULL, 0x9E4F56E42E7D3D1AULL
        }
    },
    {
        {
            0x18C7B4BF5345AB01ULL, 0x62BA7803826C1CA6ULL, 0xAA6A205C17998747ULL, 0x5A30E21D3D6D8FC1ULL, 
            0xFA0C7B8DBCB1B1B4ULL, 0x0A5E5F85474E2D92ULL, 0xF6843D13EC944089ULL, 0xED7FA4D7C161381FULL, 
            0x48776276A1EC78E2ULL, 0x9B525247E600DC22ULL, 0xD3245CECC15D9583ULL, 0x473AFD935A95B560ULL, 
            0xEDE78AA6781E87F1ULL, 0x592CD95E2A2478ADULL, 0xEBEB187612DBA529ULL, 0x956BE10094FFF22EULL, 
            0x0A118674EF8EF02EULL, 0x2F0DC12567D2F23EULL, 0x80A46FCAAA7C9D6DULL, 0xCC9BD76753611A00ULL, 
            0x423001BF91EFDE55ULL, 0x245E04D18FE83C0CULL, 0xC7D6AFCFE5DC5A4AULL, 0xFA7C24C9A9B9A6EAULL, 
            0x09DA9DD8080E9C08ULL, 0x7E4369212E1BEFD0ULL, 0xC4F42B452AF8546FULL, 0xE9B5BA33DC1F4EFEULL, 
            0x36385A625D6BA198ULL, 0x6F61A900546D76E7ULL, 0x33A4667D417B8C79ULL, 0x7043D7A841C0878FULL
        },
        {
            0x5E08925B143C0D34ULL, 0x761F2BFE7327574EULL, 0xD4EBED356EE6FAD6ULL, 0x109E69B275F15BBEULL, 
            0x1488473E5715AFAAULL, 0xC0EFB446F51A2C22ULL, 0xC46AA80CA1C0F2F7ULL, 0x39F248B52C0C5EA8ULL, 
            0xE4AB465263B6A7F4ULL, 0xED1B5480DA8C9A24ULL, 0x1A917A36A0B09D9DULL, 0x3E82DBA7F0BFEB70ULL, 
            0xD284880F4EF104BBULL, 0x5244252230275200ULL, 0x394D8C1CEC0040E9ULL, 0xE861BCB0177F833AULL, 
            0xE6FAB174B24B1DBFULL, 0x2DA9A11B30C8AE92ULL, 0xE4ACF9C306DDF4A5ULL, 0xEE02C895D081027EULL, 
            0x5FBBF237F88FD55BULL, 0x8B2166E71445E104ULL, 0xD82BE2A812CDD6F6ULL, 0xD6DABF0644A1553DULL, 
            0x6A9A3CF1D3BFEFB0ULL, 0xDBAEB9116C4DA174ULL, 0xA3BA20D29AF063ACULL, 0x9237AE18002F97B1ULL, 
            0xD3F5BA47CC3928D2ULL, 0xD1E921D8CE9B9EACULL, 0x13CA0036CA01D356ULL, 0xCC827E74F2D2597DULL
        },
        {
            0x44E7E00CBB820D74ULL, 0x41FE45066C738B45ULL, 0xE459A7359ED3FB47ULL, 0x7C52D587C5B9706AULL, 
            0x56D4EA302D0A94F0ULL, 0xE51D93076D51947AULL, 0xF3DF38583A3EBCC4ULL, 0x7DB0984CD2E35B59ULL, 
            0xFD447D96D8E4F054ULL, 0x27FDF531DD9D8FA9ULL, 0x71C6CFC2ACDFCEB0ULL, 0x2C6068CFBE651DEAULL, 
            0x0A4ABE2775B3E776ULL, 0xC5DBA52D5696E471ULL, 0x73B56FF5458BEF27ULL, 0x1840B43455B28EA3ULL, 
            0xF4932F0CDEAC8FA6ULL, 0xAF8923F9EFA6E784ULL, 0xC5A64F1732A16161ULL, 0x95A21CF6685C6BF5ULL, 
            0x32D0BBAA164ACC11ULL, 0x2B81063A289BAADFULL, 0x09873F4316C9F712ULL, 0x3E4561278908EE29ULL, 
            0xCE291B9D03F2A408ULL, 0x995207E57AB61274ULL, 0xC78155785B73A9FAULL, 0x5B5E9FF7E9759116ULL, 
            0x48BD3638707F0202ULL, 0x44F31EDB3850F0F5ULL, 0x89EC209CD93589E4ULL, 0x059AAB5F76D171BBULL
        },
        {
            0xED20FE4CC73096D6ULL, 0xF5281A2EA395D160ULL, 0x99214216DCB8357BULL, 0x8429BDE63FB16763ULL, 
            0xA1437B72AD067A7EULL, 0xA256DB2013A84F22ULL, 0xF8220C91AB48A758ULL, 0xE0379749D70ACD05ULL, 
            0xAC5188A8B79C33F2ULL, 0x68298A9FFD9A04C4ULL, 0x0A5F5EBB916F5CEAULL, 0x302ED57AD2864492ULL, 
            0x819AE99200DD56CAULL, 0xAD9ED1824F6E8E5EULL, 0xF8EAA8D1595CA2F1ULL, 0x47ED8F71BFD87254ULL, 
            0x24801D7CA1A1DCEAULL, 0xB6C793830CDB25F3ULL, 0x2F9CD02F1DB0131BULL, 0x7F29CADD09F81157ULL, 
            0x6242B01A1BDF609BULL, 0x95BD6BCCBA1E8550ULL, 0xE187D54E51EBA5A0ULL, 0x8EA72B4C27B55DAEULL, 
            0xEE203208CE1BF027ULL, 0x394EE8DD091C9210ULL, 0x7BC8AED67C796780ULL, 0x120AD37EF3258763ULL, 
            0x9DD68A982040B97CULL, 0x44653093A8740DE8ULL, 0x6259A3AABBEF515AULL, 0x8611A568DC3B013BULL
        },
        {
            0x8FBCE2A487F1EFEEULL, 0x0D461DAE7564A120ULL, 0xD22DD016C15E02E9ULL, 0xD9EAA8329A67ADFAULL, 
            0xB7E3EB7E2E49975AULL, 0xD1745752011D6C21ULL, 0x5CB032320A0303D4ULL, 0x692F5B9E2C58ED41ULL, 
            0x1135ED63D796B571ULL, 0x0A271E997CEFFEE7ULL, 0x6F494445933EA42DULL, 0x49497277884AE70BULL, 
            0x91F1C4172A830AF6ULL, 0xCC9B8B51D938D49EULL, 0x15470AE1E6B893F1ULL, 0xE0EFACDDE0AD7468ULL, 
            0x07BDFC29FE36E955ULL, 0xE9630DE6A86D882DULL, 0x34E2D31E98814CEFULL, 0x17F0B5C45ECF9127ULL, 
            0xCA64448AEDC6979BULL, 0x06EE25FE9B760D7EULL, 0x06F89DDD5E6F49CCULL, 0x71029DB61635E688ULL, 
            0x4DE39F65C7EDD412ULL, 0x116740B99CFE6320ULL, 0x26DD0959D1A837CDULL, 0x51323DF0F5992767ULL, 
            0x86304ECB12CD6442ULL, 0xC658657F7CED635BULL, 0x9E9AB1C34F2605EAULL, 0x6DAD5EAC14320F33ULL
        },
        {
            0xF9AA64D385A17FCEULL, 0xF0C332DD2318D954ULL, 0x6915BD6BEFE61C65ULL, 0x3EB80C15C27FD656ULL, 
            0xC3FD54EB20341565ULL, 0x4B5187AB2DD1F8C9ULL, 0x9BD97E458455AFECULL, 0x322DFCE36258DD4BULL, 
            0x5C7B5469B49865D8ULL, 0xB07F026CABD932F9ULL, 0x914624C9A2BC030DULL, 0xB454E5F3C17C6AF4ULL, 
            0x87441F1099E02F60ULL, 0xFDD064A03117981BULL, 0xA9253BCBE4DE1917ULL, 0x8F0E983B6420B54FULL, 
            0xDCDBECDC386DD2A6ULL, 0x4606042E26DA72CFULL, 0x3CC7D51EE2D28895ULL, 0x70CCC919093E42B1ULL, 
            0x390DDE18C1473D50ULL, 0x4B891DA3041C5914ULL, 0x8647F84673390786ULL, 0xEB9B27C490311212ULL, 
            0x5FFAEB381A301C15ULL, 0xF63E3E813A8AD844ULL, 0xD2551124016851CDULL, 0x928E7A4DE23082DDULL, 
            0x9D586454CBBF16F0ULL, 0xCA7FBD11B18A9031ULL, 0xF2731294885A7E94ULL, 0xD97409447CCDB07CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseGConstants = {
    0xB4FBA38CBF774499ULL,
    0x535DA1D36ACDB7CDULL,
    0xA03A08990B74AEC8ULL,
    0xB4FBA38CBF774499ULL,
    0x535DA1D36ACDB7CDULL,
    0xA03A08990B74AEC8ULL,
    0xADD9AAE83DBFCF49ULL,
    0xAE528AAD209DCB66ULL,
    0xDE,
    0xC5,
    0x83,
    0x0A,
    0x46,
    0x98,
    0x33,
    0x4E
};

const TwistDomainSaltSet TwistExpander_Rigel::kPhaseHSalts = {
    {
        {
            0x25B0B65DBBE340FEULL, 0x93EC6CF66E28931AULL, 0xB89BA12BAC6664BCULL, 0xC20D9CEDF56283A5ULL, 
            0x8396A9882AD12952ULL, 0x8950E3A7FE48337CULL, 0x7BA1BBEEAD4C1F90ULL, 0x90356D2CC6147639ULL, 
            0x2C2503BBE58F5276ULL, 0x0647E5E52F989FA3ULL, 0x8C20EBF5241FF031ULL, 0x002B4476741B5CABULL, 
            0x38C8A4D8CF6CA754ULL, 0x0B3FEFCE3B1A29B7ULL, 0x6090F4647DDD7B4AULL, 0xEAB1ECE261B35A10ULL, 
            0xE51751240EBDD96DULL, 0x0538C30C4DEC3BEDULL, 0x3E791629DB4E94EDULL, 0x5BD320A6E82DC77EULL, 
            0xCB67BC9052FC17D9ULL, 0x4B183E3DAB2EFC51ULL, 0x63B467FD4091FFC0ULL, 0x603672D4B39C09ADULL, 
            0x5CE405BBB0DDC950ULL, 0x8E186A4B10CF86FDULL, 0xC6B84137B822CEBEULL, 0xF0D45A447B0320DCULL, 
            0xE17E1BFD34D38335ULL, 0x271F631142140395ULL, 0x8889142DAFCE1140ULL, 0x3B16FDC9DC83DDF8ULL
        },
        {
            0x061C0091FB96A1F4ULL, 0xB8B6D66EB3F093CFULL, 0x5709B95C494D9109ULL, 0x080B53518D09C903ULL, 
            0x6EE809FD841A9095ULL, 0x3B7B60D339E066ECULL, 0xDD917EAA39406372ULL, 0xD77F81A13A8012D2ULL, 
            0x63C31749FF65874EULL, 0xF030FA89C7C2E9D2ULL, 0x027B4B713CE66595ULL, 0x4FE39313CEAACE00ULL, 
            0xEC95D33CCA786E60ULL, 0x2CF122EB1125176FULL, 0x9B59CCF5E736229BULL, 0x3100DDB19BF77799ULL, 
            0x978E8B191BF66237ULL, 0x0C2CA559EB78C307ULL, 0x285DBA8E413EAA36ULL, 0x33BE6B59A93D33F7ULL, 
            0xC4900AA8861A397AULL, 0x04BAE57CA8DFB448ULL, 0x681202F013804EF5ULL, 0x0835A61D66386764ULL, 
            0x3907DCA46F8F08B3ULL, 0xD2540117BCF96BEBULL, 0xAEED0507E85375FFULL, 0x7B6EABA69B936814ULL, 
            0xDB8930C63F0FB2E4ULL, 0x62152F7BEA1EF477ULL, 0xACE27DF6E3CFFB01ULL, 0x67035E9247FCF058ULL
        },
        {
            0x1A14268153651172ULL, 0xFC776CF98853B639ULL, 0xC46033C31E82D5EDULL, 0x2B05FB9D65849DB2ULL, 
            0xF363E39B570CF473ULL, 0x3DA20FA9FFB3695BULL, 0xC1656082FEA82036ULL, 0x1449A7C891D12438ULL, 
            0xA904D5A9CFD23AEDULL, 0x940E8ECF10003D93ULL, 0x8C5A61BCE09372E5ULL, 0xD9599782423A4708ULL, 
            0xC4C96D6261C0A7ECULL, 0xD44CBD99F00C5A85ULL, 0x4C33BFF5532957F9ULL, 0x674A9A2CA0DD7F9EULL, 
            0xAAA8A996AF13061DULL, 0x26B5DA2C2557B799ULL, 0xB71D661DFA216368ULL, 0x7C3BD6828431FBA2ULL, 
            0xBD4A67F5F38A3AEFULL, 0xEC045BBC49DFF250ULL, 0x65C6046627D466DCULL, 0x2CDBC2FCB2E0AB78ULL, 
            0x90E64FF21D7CAE53ULL, 0xB799D1783FCAE719ULL, 0x3A074D8DD5A74C8DULL, 0xA14AF4A52245025FULL, 
            0xA1CF9BE661A6D61BULL, 0x86CDB779A7BDE5E6ULL, 0x87DA2EB23C4851F9ULL, 0xBD1A159F8E74D822ULL
        },
        {
            0xDCD63182D6CB3775ULL, 0x82C870FAC5D3CEE2ULL, 0x063707FD5D79AEFEULL, 0x291B02D6745DEFBDULL, 
            0xE12E88C4177DB8BAULL, 0x80ED94865FE3124EULL, 0xD49EC3D23C7BB962ULL, 0xB63B9AD3AA14E77CULL, 
            0x5CCB16BFE3676BE3ULL, 0xED3EFB3275F67BE1ULL, 0xBFA7542C41E5D159ULL, 0x162B8F72F98EB780ULL, 
            0x4B955A96501A8334ULL, 0x5EE073D83A26ADCBULL, 0x8CA38EBFAE92E39CULL, 0xAE066287FAAFA49AULL, 
            0x8FAB502D3707B1AEULL, 0x36909A435CC3D5EAULL, 0xB5BFF370DBB6920BULL, 0x4B3D23C0D2BE13E0ULL, 
            0x06768F01FCDA0B7FULL, 0xD6318AAC9006FB5BULL, 0xAE2961F9A0A6037CULL, 0x4973046E30270ABDULL, 
            0x333A43FB2F717EF2ULL, 0x5F82CE304BFAC41DULL, 0xC18C3849EF342782ULL, 0x46A08A95BBA6B855ULL, 
            0xFAAFDF72AF673C87ULL, 0xEDE6F41C4782A669ULL, 0xF8C5373B0C8D2AC7ULL, 0x7EF65AA16D515D11ULL
        },
        {
            0x0C8928456CA43811ULL, 0xD007A55DDE3080DCULL, 0x855FE3A8CBE5F6F6ULL, 0x408D0A61A0D566FFULL, 
            0xE6238C642B0EB65DULL, 0xC5466A35971EF357ULL, 0x4F43F9D76BC30680ULL, 0x03F878B4180F75BBULL, 
            0x1F967A9E3FFF38A0ULL, 0x7DF8CC59394E4720ULL, 0xBC565BC542A4BCFBULL, 0xC8B58F18577F974FULL, 
            0xC7EAA4A8497E1F8BULL, 0xEB39984A2BE1441CULL, 0xE97FD30482AAF958ULL, 0x495CBFC2F79D63EFULL, 
            0xFACE2A0DE0ADA3F8ULL, 0x9F7787B748C284C6ULL, 0xE6C63FB6A4F805BEULL, 0x7A100839E1C69202ULL, 
            0x062D269E8B2F98B8ULL, 0x28CDFDECD9DB13B7ULL, 0x7B33CC6185A1929EULL, 0x4B4B7B1FD09D926AULL, 
            0x504EA9C3670B174EULL, 0x06A803D34F245802ULL, 0xAC150CAD73FE6F1CULL, 0x2D4039DA12089AB7ULL, 
            0xBC3B271F1E156290ULL, 0x0773DCD9705D50C3ULL, 0xE82688D766B085C5ULL, 0x2FD7075AEBE4F999ULL
        },
        {
            0xB20CF0B69E7E057CULL, 0x64E87990BFC48703ULL, 0x423C4F4E63322EC2ULL, 0x55DE697007E1957FULL, 
            0x51E6A33BB375A9CAULL, 0xF8B93FC879DBCE52ULL, 0xF3A6EC6563244529ULL, 0xC265E6382E15A7BAULL, 
            0x3642A94284B5B79EULL, 0x9261281960BCB8CCULL, 0xB3CFFD8BED29EEF5ULL, 0x7DF2454ECD9DDF42ULL, 
            0xD9F8D43EF7D8EDCBULL, 0x5F4332BA69D2829CULL, 0x2600E610BECF82CCULL, 0xAFF4606839B113A6ULL, 
            0xA2502CC8628A27E3ULL, 0x4F244D0AF956A2A4ULL, 0x9A840ACAD825C9F5ULL, 0x9C4358281C40FA13ULL, 
            0x67D94251A08B0328ULL, 0xDAA84A2775392248ULL, 0x7F43C4AF1F55107DULL, 0xA94CCF1F0A4D3F70ULL, 
            0x5685C80DD0DB344CULL, 0x29A3ECF6B40CAB95ULL, 0x42DDE005962F6BEFULL, 0xB3F03E9A39E6FC5AULL, 
            0xCB4190700E82B52FULL, 0x74A69CD0DB359C5EULL, 0x6923AC5A0FF94F8EULL, 0xDE5F71B91438D55FULL
        }
    },
    {
        {
            0x2225523B023DB634ULL, 0x7892CECB3A03E96AULL, 0xBC7DE9B54F914D65ULL, 0x387AA7C987389788ULL, 
            0x65B0BFDF8215CDEFULL, 0xFCE3464BB4C6A74EULL, 0xD69864F177695D8CULL, 0x6415AFFCE7EB747CULL, 
            0xFA1AD3915FB42A00ULL, 0x98C50F6B970DE062ULL, 0x116CAE54327C1F7FULL, 0xFEE092A9477CE295ULL, 
            0xA0499B591F9F7DA8ULL, 0x8BA31C0F6EE8ADD5ULL, 0x593766343AFDE64FULL, 0xEE1979C8C80C58D1ULL, 
            0x029123E747F43818ULL, 0x654CE7DA2DCC1238ULL, 0xC605619AA9A0404DULL, 0xD9182B5E285623B5ULL, 
            0xD95F19EF47BCD119ULL, 0x63F810AAF9DC0A75ULL, 0x3CFA2C34235568D9ULL, 0xC8CE4AC52AA6AA3AULL, 
            0x5CAE7181329AFA52ULL, 0xCDB1C8CB256A637EULL, 0xE5651CAA0E77FDBFULL, 0xEC07A860642F9EE8ULL, 
            0x92E1DF6D17729222ULL, 0x134317A45F8F0E39ULL, 0xFAED3A5F6D735A0AULL, 0xC8EED7702C5C0580ULL
        },
        {
            0x3209FC477062CA55ULL, 0x0560BB562C93379AULL, 0xD2CA33B9392A78ECULL, 0x0E0CF62D6658A5BDULL, 
            0x3A32143E43CA162CULL, 0x0C91127BCC38689CULL, 0x705698B769E3FA86ULL, 0x24F241C8EF7E9C23ULL, 
            0xE974850B96D50970ULL, 0x98F07074AE40DB26ULL, 0x6A76318DE720EDA6ULL, 0x75B7C6B71007AFFAULL, 
            0xAA7C5E7B309EBFC1ULL, 0x904FB6009EC78E6AULL, 0x28C45AFA44169849ULL, 0x6CB1AAB78568357FULL, 
            0x05938AE9A83360B3ULL, 0x52FF53E7240051E8ULL, 0x053A65DB3B855755ULL, 0xA7360513CC57B704ULL, 
            0x1F7E3D7144887F39ULL, 0xC00EFB62EBC49DB6ULL, 0x0040DA2D2145203EULL, 0x8084426821D64E83ULL, 
            0xFDBF7E76D5F0DAABULL, 0xADA9C67A69BCD2CEULL, 0x08761768BD99BB80ULL, 0x970B85C548F3461FULL, 
            0x521BA06429C10AFEULL, 0xF105478C2356746AULL, 0x85D822797D08A804ULL, 0x1F12B191601EA435ULL
        },
        {
            0xA4097BDA3A7F8E52ULL, 0x49AC47FB7C0555E8ULL, 0x47CF06F4B497D371ULL, 0xAF959EA061704C01ULL, 
            0x4F93D74E52F60384ULL, 0x3E892D5960C70996ULL, 0xCD5C2D3F5D06C4F7ULL, 0xD440351CAD4458ADULL, 
            0x7DBBBD73FC28E0D6ULL, 0x680FB6F495CEFA0AULL, 0x0C4400EB2173098CULL, 0xD669FCC4420C4207ULL, 
            0xFE8C105EBD9B42FCULL, 0x6228D05B0114ED7CULL, 0x55EEEED0768444F4ULL, 0x3396C7DAD71DA105ULL, 
            0x7F2FBAA355506876ULL, 0xE89C72AF6AB20C10ULL, 0xFBFF240B7E768591ULL, 0x771E625CF54F85AAULL, 
            0xDB097D771DF082FDULL, 0x23CE4FFA860CF139ULL, 0xD6C55C57CB3307CBULL, 0xEA811E21EB45A5D1ULL, 
            0x18A411B4164D38B4ULL, 0x0269BE6FF80DD3BDULL, 0xE11DCEF66EC88C21ULL, 0x13FC06240E00960EULL, 
            0xA1EFA23176DEA74FULL, 0x75B0482E30F37333ULL, 0x6734BB97154E0EBAULL, 0xBBF06BE01EEC83E6ULL
        },
        {
            0x4F77501DCA26CA47ULL, 0xA7886231C88DD046ULL, 0xF060CDA0092D9E1EULL, 0x42D1A0AA00193916ULL, 
            0x0A7C79E66759B4B8ULL, 0x053742D932FFF769ULL, 0xF00BAD3E7748668FULL, 0x6E6887AABDC68058ULL, 
            0xD7F4439ECD02EEA7ULL, 0x112D5A6BDEC75128ULL, 0xD7D78C42150A743EULL, 0xB032F31A05615AFAULL, 
            0xFAFFE67A64AF67D9ULL, 0x6684602D68A7814FULL, 0xF3FAF56A1281D832ULL, 0xF2CE67A329594DD0ULL, 
            0x150364D0791EEF02ULL, 0xDF0011510902F897ULL, 0xB06BA316546D3F99ULL, 0x509133721D413946ULL, 
            0x8CBCEB1FCE610BE4ULL, 0x8E9E9DB117AD4E43ULL, 0x43D4508C4BF9A998ULL, 0xB40892CB681C3D6BULL, 
            0x4C81C6B7127F4AE6ULL, 0xD9D6A8755ED7D84DULL, 0x75CB75071A43BB4DULL, 0xDD99584002038BC0ULL, 
            0x260DE92B8394BFFAULL, 0x9DC271F1AC9E5B69ULL, 0x1118CF2011FA3519ULL, 0x56BBA4FB514C580FULL
        },
        {
            0x77016281812E4207ULL, 0x1C64E21FCE1C59E5ULL, 0xC2FEF83251DE24E8ULL, 0xEE825FC54797C528ULL, 
            0xF3BD51F7151E8C65ULL, 0xFB4D9C7E373A1C34ULL, 0x02EBABED85E1ECC2ULL, 0xE6968D5589168D22ULL, 
            0xC2A4CC3926D9D86AULL, 0x6A970D5B35269595ULL, 0x2834547C15A98AFEULL, 0x47E26890B9468D13ULL, 
            0xDB9491BB4D094C23ULL, 0x69D48E28D1706C35ULL, 0x4BDFF90D6BB93366ULL, 0x542DD050733CEDC9ULL, 
            0xC287AF1266463105ULL, 0xA14F43FE251BCA56ULL, 0x7EA9A6EBC888A972ULL, 0x74B53674C3ABF5D6ULL, 
            0x1866B502EFC0A7E9ULL, 0xF1B2580619475814ULL, 0xC2ED1E99027A61E2ULL, 0x171F326E54DA2E4CULL, 
            0x2E76DADDD814EB73ULL, 0x66066470C0869BC7ULL, 0x1D870BBBC170E439ULL, 0xCA59291DE28922EFULL, 
            0x66ED65B6831B44C6ULL, 0xF6641B13C9E02B3CULL, 0x5C3C4DA0E96A6956ULL, 0x6BCEECB11BF3605AULL
        },
        {
            0xA1A4452E610F5842ULL, 0x60E8F28D3319F526ULL, 0xA7064147C4D66E17ULL, 0xDB2D0960CE9BA8B9ULL, 
            0xE3EC9C9CBC019775ULL, 0x0E2A6BF9EBD47657ULL, 0xB94220A59ED74542ULL, 0xA65C8B9178F298AFULL, 
            0xEA064E37B6274293ULL, 0x51F61946408AD5EAULL, 0x64DB8CD6E9F6A2B6ULL, 0xFBE60857FDAE5C80ULL, 
            0xF8C6628329A98E43ULL, 0xE521A42D5B3C3FEEULL, 0x0D770E92B5A5D1EBULL, 0x9EFA23AE19A4FA58ULL, 
            0x9C4B0AF52BE70DC8ULL, 0xF5C7AA768CCFE2D5ULL, 0xF16AC28B835E83D9ULL, 0xFC0DDC5A446FAAD7ULL, 
            0x0E4ED3EC7F828D36ULL, 0x6E2C35DA30293974ULL, 0x58BDFD1F490AA0DDULL, 0x5936507C2B1F03A6ULL, 
            0xCB357ECFCD67D3E2ULL, 0x3747A29441E6A4BAULL, 0xE211E6511AB1D249ULL, 0x7C553F0D8791ADB2ULL, 
            0x5F53A71834290F6BULL, 0xFF0BB7A4AAA9E4B4ULL, 0x944E8B5327FFFA24ULL, 0x0470EAE05AC31569ULL
        }
    },
    {
        {
            0x0F9D228282BBA1ABULL, 0x402260F019806460ULL, 0x309C3FAC70F064FDULL, 0x7A5394C4012CFC60ULL, 
            0xFB8E0DCA47DBBE40ULL, 0x3E5E97009F21A196ULL, 0x91E8A17D17E9FD00ULL, 0x39E4731BF7B5996BULL, 
            0x61338F647A0CFFF6ULL, 0xA8B33FF275D063DFULL, 0x8C1FC31C873B7883ULL, 0xEAAB901C46EFD779ULL, 
            0x32BF1EEBCECAB13CULL, 0x9FC1D877CA8F91B6ULL, 0x80FDFA52C7802D24ULL, 0x09B7F767B72D54CFULL, 
            0x99DE878A92C5DD30ULL, 0xA921043FE4E885DFULL, 0xA6B6CED6C8630C2EULL, 0x58BF53F87B08C28BULL, 
            0x1C79D257F4919B50ULL, 0x8ED095AA17AE5AB5ULL, 0x5B4E635D734A6811ULL, 0xFD2971BE7EC481B3ULL, 
            0xE78C7DEA1080275EULL, 0x38AEB399AD2B7BF5ULL, 0xE91A02D540CB5D7BULL, 0x1DB81988C36FC0E3ULL, 
            0x5E1D86B5D62AD090ULL, 0x3FC73848A2DF6DBEULL, 0x32964250B12A3E11ULL, 0xAE4638D9A7CEF371ULL
        },
        {
            0x7602DC82F9698222ULL, 0x165A0B5CAFDC352FULL, 0x0942E0B42E656EBAULL, 0x2186EEE5BB76C62AULL, 
            0x6EE0F47808A4518AULL, 0x6B2FD79FD05BE2A4ULL, 0x16B7AB8AE2221107ULL, 0x384B02AF09F3EAA0ULL, 
            0x7A8FBEC20ADD5C07ULL, 0xEFBF39FAD7F3DFB2ULL, 0xC239672859AD1A89ULL, 0x0AE82A3C5EE6EB3EULL, 
            0x7FE601FBD07667F2ULL, 0x1EA7EF4F27F5B51DULL, 0x446AC44D1EB239BAULL, 0x9A8AABB2953837F9ULL, 
            0xBF5749D29538F324ULL, 0x4059538EDDE70DD9ULL, 0x1EE4986CB5F370C0ULL, 0x59BEE5975177A4A5ULL, 
            0xC411226609E73221ULL, 0xCDE8AFD2AB4EE321ULL, 0x1EBC85B21670714CULL, 0xE506A1DD88C94271ULL, 
            0x054C76DC35540CD4ULL, 0x5D1F461C7C3A7D77ULL, 0x53A60EDCC5914803ULL, 0x75EE72ABCF18AF09ULL, 
            0xA9684A24E62959C3ULL, 0x91D2EF2B585F3F6FULL, 0x1C0033E591543F97ULL, 0x2E30C8772C8E6D9BULL
        },
        {
            0xF3DB4425202EBB70ULL, 0x3751809CCD4FD582ULL, 0x244B2E874F92A775ULL, 0x67BF9760BDD3113AULL, 
            0x89165E15D11F83F7ULL, 0xFFB28EFEDA890850ULL, 0x1DF07FAD557F8B6EULL, 0x5B1EA460C9798CBEULL, 
            0x0CCB79387A2AC079ULL, 0x39B86A3AF81EF199ULL, 0xB403FDDFBE1215B2ULL, 0xE1E810F51ADCE941ULL, 
            0xEFA1AF9203B41A25ULL, 0xA5A1FC0AFCDF150BULL, 0x868AABBDE2F4BB8CULL, 0xC282D902BE7D4475ULL, 
            0xDBF55B61D3BDFA71ULL, 0xED3695DA620E47C1ULL, 0x27464B57A2994F6CULL, 0xF379DA97748F9268ULL, 
            0xCA6036CEA7511239ULL, 0x69DE96F22268231EULL, 0x99CC0B22FB2C7E5FULL, 0x907915C9827C6C5CULL, 
            0x22BC2FFA0327C7B5ULL, 0xB17EA52B81997A1FULL, 0x006D1378A6698C6CULL, 0x597FB1A7F5F43DD0ULL, 
            0x068170A2DE57CF82ULL, 0xA02DF853E024A64AULL, 0xBAE0908172150399ULL, 0xB18C53E8E683298BULL
        },
        {
            0x26B6F970E65066F7ULL, 0xFEC2FD716A8DA1C1ULL, 0x0D4C8683273E28A3ULL, 0x37C4C9CA90018607ULL, 
            0x50DA33E0A1744526ULL, 0xDBE8E2EFBA6E9F46ULL, 0xE0287C837F13D0FFULL, 0xEFC0E65FDCAF6061ULL, 
            0x17EEEFEBFE7C2E90ULL, 0xC54AC5665A2D63EAULL, 0x18E9868D49834EF5ULL, 0x562F239BABF51199ULL, 
            0x162BEDCD214D569EULL, 0xFA0AA270918F21BCULL, 0x4E5DDB973BDB5382ULL, 0x4DD1CF368623A044ULL, 
            0x388FB241ABF400C7ULL, 0x18C862B8435384E5ULL, 0x594F067E66761388ULL, 0x66CDC655B9D455B0ULL, 
            0x4E8490755148BC85ULL, 0x97E240A39195B373ULL, 0xBAAC5400EAB1E67EULL, 0x0AC0C90500416C34ULL, 
            0xA8EA169D6A93EC96ULL, 0x6CF6399D7DBC14B7ULL, 0xA33367CAA87538C0ULL, 0x9E5D8010ED52C816ULL, 
            0x2F9C51EED52BC483ULL, 0x6118524563E90F79ULL, 0x2202FA6350745E52ULL, 0x867C964D81C87CA7ULL
        },
        {
            0xDAE9A21F21FAD2C2ULL, 0xE8B26FCB4ED83044ULL, 0x95489725D0D7EF63ULL, 0x99678127EA6A8C30ULL, 
            0xB939D55D67CFE733ULL, 0x46F94F607040B5AFULL, 0xF894549132490888ULL, 0x960E0E8C13902A23ULL, 
            0x29B22BBB7AF3A23BULL, 0xBFF76B9664C7AF10ULL, 0x55FC449EEAD4DCD6ULL, 0x737A3B421672CBA3ULL, 
            0x2F1CA37B3305AC75ULL, 0xF78A2B990DDC1428ULL, 0x86AFA5444DA50B47ULL, 0xAB8A5E197DAFB7F6ULL, 
            0xD44F1FF22DE790E4ULL, 0x9758773EDE0A3ACDULL, 0x96BB42EDBF1A04CDULL, 0x669033B0F92E6055ULL, 
            0xEEEC9CA2CCA57FD5ULL, 0x0CAEC3433B312897ULL, 0xA295A66AF5E42CC9ULL, 0x86B35F5472864AA5ULL, 
            0x512A03A95B94598BULL, 0x694719D852BB9631ULL, 0xCD079FC55CE3D50CULL, 0x1D84D089B01E4B0DULL, 
            0x5EDC0B774EFB5BAAULL, 0x6884484F81C1D37CULL, 0x2EC63ABEFC7BECD8ULL, 0x85E4507C067E3307ULL
        },
        {
            0xC1072AD7A747F329ULL, 0xF1740DAB44790AC7ULL, 0x4BB62003EBCA183FULL, 0x2A9DC76BEC90022AULL, 
            0x53C4D7F80B0593BCULL, 0x4AF3C9F0D8F00AA7ULL, 0xE876A41E3D425306ULL, 0x573D2802C02E8F3BULL, 
            0x17C2FA095BA69174ULL, 0x787927B0B13C8DAAULL, 0x8A776908F908FD1CULL, 0x43AB5755FBB454DAULL, 
            0x31C98696E3E3CE69ULL, 0x5FCB47EC6BA0456CULL, 0x9C01C9CA6C7F94A9ULL, 0xEE4B1795BE2395E5ULL, 
            0x043017830C5E2671ULL, 0xA5786D11E3EAB409ULL, 0xBC6EC72D5D500ECDULL, 0xF117D04EBC6D3D58ULL, 
            0x3BDC7F7F2EFB66E1ULL, 0xC5252A319207790FULL, 0xB104EF04108E56DCULL, 0x161FB6BD4020F4C4ULL, 
            0x00810C6AA1ED2955ULL, 0x2AE23AEA57A81AF2ULL, 0x3722061963256389ULL, 0x7491D05951B161D6ULL, 
            0x3BB8ABD564FDC8EDULL, 0xC5DA34CF0E6C1565ULL, 0x56A12B916F0FC124ULL, 0x62EB6ADD13E14E10ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Rigel::kPhaseHConstants = {
    0x5AC943B88806D11DULL,
    0x58002F18E62482EFULL,
    0xBC486D77294CAAE4ULL,
    0x5AC943B88806D11DULL,
    0x58002F18E62482EFULL,
    0xBC486D77294CAAE4ULL,
    0xBE44B22D974DD004ULL,
    0xD68DCA283E73E4A3ULL,
    0x8B,
    0x80,
    0x89,
    0xD2,
    0xA2,
    0x7C,
    0x5A,
    0x89
};

