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
    std::uint64_t aPrevious = 0x98AA047D6CB43A8EULL; std::uint64_t aIngress = 0xCA7F9DFABD7465B2ULL; std::uint64_t aCarry = 0xB4D0B42D22A1DF03ULL;

    std::uint64_t aWandererA = 0xA4C2BC804187B543ULL; std::uint64_t aWandererB = 0xA89B5F7B191B23B3ULL; std::uint64_t aWandererC = 0xC20A2FD4B861E851ULL; std::uint64_t aWandererD = 0xB0301BD0BC08DD82ULL;
    std::uint64_t aWandererE = 0xCAC7921814AE0945ULL; std::uint64_t aWandererF = 0xAF539323C374710BULL; std::uint64_t aWandererG = 0x9B3B391674C12310ULL; std::uint64_t aWandererH = 0xC899686FFB6DF473ULL;
    std::uint64_t aWandererI = 0xDB38415E7110694FULL; std::uint64_t aWandererJ = 0x94C29F17C89BEC60ULL; std::uint64_t aWandererK = 0xD017D1C9B24287C3ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17995143821014073325U;
        aCarry = 15847916527846557896U;
        aWandererA = 13312292731958933129U;
        aWandererB = 14053089029893234131U;
        aWandererC = 10351205088422288094U;
        aWandererD = 11627514187450732168U;
        aWandererE = 11328938598840207800U;
        aWandererF = 17469503356290107251U;
        aWandererG = 11331793127288181262U;
        aWandererH = 9724980530263984837U;
        aWandererI = 10794816564819310228U;
        aWandererJ = 15527686006237863827U;
        aWandererK = 15665734695134438341U;
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
    std::uint64_t aPrevious = 0xC43BB5C9F2D98556ULL; std::uint64_t aIngress = 0xBFD87AF2B3C7D1A2ULL; std::uint64_t aCarry = 0x97B65439ADCC0731ULL;

    std::uint64_t aWandererA = 0xA9523AC54DACB224ULL; std::uint64_t aWandererB = 0x8066F86FBCD64F86ULL; std::uint64_t aWandererC = 0x82F6C7AB3D53FCFBULL; std::uint64_t aWandererD = 0xEE9D0F29FC5C5AB8ULL;
    std::uint64_t aWandererE = 0xE26065874F423598ULL; std::uint64_t aWandererF = 0xB0288A573430CBFCULL; std::uint64_t aWandererG = 0xF4BA7DADFC0D30F1ULL; std::uint64_t aWandererH = 0xB15C238F081E67AEULL;
    std::uint64_t aWandererI = 0xE097147DE00A4E85ULL; std::uint64_t aWandererJ = 0xA5ECE78EEE47B433ULL; std::uint64_t aWandererK = 0xE15E85930A3DA606ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15687756239696619772U;
        aCarry = 11478462951585663898U;
        aWandererA = 12635635049444384996U;
        aWandererB = 15735361115061156437U;
        aWandererC = 17371541343116150666U;
        aWandererD = 12429683144974945713U;
        aWandererE = 11929417462978682026U;
        aWandererF = 16494827455018911198U;
        aWandererG = 11619315956676360365U;
        aWandererH = 15382838626654559261U;
        aWandererI = 11375575213980025305U;
        aWandererJ = 16953888895538207714U;
        aWandererK = 11063103660672389189U;
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
    std::uint64_t aPrevious = 0xD1322D7AE1CE4615ULL;
    std::uint64_t aIngress = 0xA0C6BC8EDCACD39CULL;
    std::uint64_t aCarry = 0xB30356981D156969ULL;

    std::uint64_t aWandererA = 0xED1B02070C743DEDULL;
    std::uint64_t aWandererB = 0x99D271800EE16328ULL;
    std::uint64_t aWandererC = 0x94C9854BC6EB9021ULL;
    std::uint64_t aWandererD = 0xAAE48880F851000FULL;
    std::uint64_t aWandererE = 0xAB49A34CDE69D261ULL;
    std::uint64_t aWandererF = 0xA026F98818179146ULL;
    std::uint64_t aWandererG = 0x8B3F271DEF2C39C6ULL;
    std::uint64_t aWandererH = 0xBF57C6C2F9D81D12ULL;
    std::uint64_t aWandererI = 0xA5747FA737A41013ULL;
    std::uint64_t aWandererJ = 0xB5C35F1F95CBB8F2ULL;
    std::uint64_t aWandererK = 0x8E9509D05E78BD48ULL;

    // [seed]
        TwistSnow::Aria256Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
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
    std::uint64_t aPrevious = 0xEC38026266E08554ULL; std::uint64_t aIngress = 0xC6FA6723EECCAB50ULL; std::uint64_t aCarry = 0x93FC35FC104279D4ULL;

    std::uint64_t aWandererA = 0xB8BEC3A82F731DAAULL; std::uint64_t aWandererB = 0xE1E4570BDB950F1CULL; std::uint64_t aWandererC = 0x971183685562B6E5ULL; std::uint64_t aWandererD = 0xB742C67C138989EEULL;
    std::uint64_t aWandererE = 0xA8AAA6A547599749ULL; std::uint64_t aWandererF = 0xADDE577D680435ADULL; std::uint64_t aWandererG = 0xC9B7E2B2EDA37410ULL; std::uint64_t aWandererH = 0xDDCA5A69932DB931ULL;
    std::uint64_t aWandererI = 0xC1FD694F36483A1CULL; std::uint64_t aWandererJ = 0xB57F810EA6B550C9ULL; std::uint64_t aWandererK = 0xCD21CB36C2752E0EULL;

    // [seed]
        aPrevious = 15332134458124673747U;
        aCarry = 12939673637763063922U;
        aWandererA = 14001157770125142209U;
        aWandererB = 12445983403402128954U;
        aWandererC = 9669147795869860138U;
        aWandererD = 16509829158893174361U;
        aWandererE = 15603161464176631803U;
        aWandererF = 11026548561030295362U;
        aWandererG = 15287538182677853260U;
        aWandererH = 14025584935759916160U;
        aWandererI = 12054617193611181262U;
        aWandererJ = 13876084476207625634U;
        aWandererK = 12557538065423858316U;
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
        TwistSquash::SquashB(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
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
            0x356A08D170E052C8ULL, 0x78D8892A23EC3F2FULL, 0x429DF8473CCAFCEAULL, 0x4AF87FECC565D4FFULL, 
            0x8AD2FB4116D547FAULL, 0x2E57E3884D291CF7ULL, 0x7D2E1E15D8B51CE2ULL, 0xF290BBAF41E22888ULL, 
            0x5ED0CAB6364374F2ULL, 0x9CD8CD37744ABCDDULL, 0x94E72CBD24274393ULL, 0x64FE93A4E6CA833EULL, 
            0xAFCC14BAFEE9ECB9ULL, 0x2AB56231196D4B28ULL, 0x0050265AA34C858DULL, 0x384F37417FAD6040ULL, 
            0x76DC8970EFA062F0ULL, 0xCACA20388CF00518ULL, 0xE7DA6D38224FEC0DULL, 0x54710B031E221176ULL, 
            0xE70E0F708BA65C7CULL, 0x2CB31F415BC1E52EULL, 0x6750CBBA8A5DB561ULL, 0x912B02D2E23B1582ULL, 
            0x8C8BD4240C0741DEULL, 0x7C13227FEF537CE9ULL, 0xB99A781C70A9D241ULL, 0x67CC963651F1DCEFULL, 
            0x2E9CA620F3E14D4DULL, 0x8D2422975C9C4008ULL, 0x688747A2575D8A00ULL, 0x245D4206D7D6F0FCULL
        },
        {
            0x551DCC484508B206ULL, 0xB1EF7FB57537C0BEULL, 0x98D2CBE08044879AULL, 0x11F8F7DFB69B5E21ULL, 
            0x7D400C3F8BF00CA2ULL, 0xA07B0C15FDFEF0FDULL, 0xDE73B01CEF55E199ULL, 0xCD11872515E1562BULL, 
            0x437E39CE1E7F209BULL, 0x52303CCA2C378B05ULL, 0xF5BC8995842525A8ULL, 0x949B253DFD5DB206ULL, 
            0xA099ED0476047CF6ULL, 0x74E1CD71A202A65AULL, 0x2CA8BAFBC74584F5ULL, 0x8ABDE43A9C9240B6ULL, 
            0x90BEDCA33E33B648ULL, 0x94F54840782C6222ULL, 0x00A186C9952FBE34ULL, 0x5BBE3EE90FB66522ULL, 
            0xDC5252815D760FC6ULL, 0xD56E5CEEF147E9B7ULL, 0xD68DF9AA41DB7BB4ULL, 0xA3ADEAD53D8B89D6ULL, 
            0xBE594B9C39BFAA81ULL, 0x4F3D76FCA1B026BBULL, 0xC5AA9440FB4CC35CULL, 0x7119EB3B8A87D26FULL, 
            0xDA99A5432DDD3CDEULL, 0x7A7146D08C9FC8BCULL, 0xBFC3F78C8ACCDD44ULL, 0xADE79DEEE610145CULL
        },
        {
            0x7BA30B0631AD5302ULL, 0x13001FC53FE5E513ULL, 0xFE53D3695F89AD25ULL, 0x835A173EA654457FULL, 
            0x03A6DD364BB86AB8ULL, 0xC9CBD76D568AC0CCULL, 0x784D4C63A5AADF9CULL, 0x06DE1EF993076997ULL, 
            0x36B141443C7B078FULL, 0xDDF91A944F0828EBULL, 0x6743971F6187E589ULL, 0x41DD186FFA901A1AULL, 
            0x01DA56A0ECD78AEBULL, 0x2531408DD4DE9BEDULL, 0xCFACD01D61E56213ULL, 0x8F93052148280BCFULL, 
            0xA0F9055BEBCBD7A1ULL, 0xB6CB251FAD665A82ULL, 0x332BA3EBC2E340A8ULL, 0x7C1FAD5E97158E13ULL, 
            0xE18597D4713EC37EULL, 0x2BB7E20DE2BFD82BULL, 0x247A1E05C43667A4ULL, 0x8A7408ADE6D27D2EULL, 
            0x4AA56D34B25E6DABULL, 0x42AAFF92D0F5613CULL, 0xE44C4B91BBF5A29AULL, 0x55CED3E804EBB85FULL, 
            0x7988D4B1FDF08EF5ULL, 0x539A833D1FDBC8E6ULL, 0xEEC7C5521381871BULL, 0x521BAD85265DF72EULL
        },
        {
            0xC7E78C2003DB0101ULL, 0x17CA0CD0051B8ED1ULL, 0xBB883BD793DCEC7EULL, 0xBC84D83094378141ULL, 
            0x634F9BA219025DBFULL, 0x900FC5299DE09DCEULL, 0xD0EB22072B368255ULL, 0xE07C4ABAD5B526A3ULL, 
            0x8FFEA09BECCB6545ULL, 0x0C5938A62D596FDBULL, 0x0BBB98F0EBACD3B4ULL, 0x9545C45D5EE41BFDULL, 
            0x50A93CD2D5512858ULL, 0x4E9170BC04722388ULL, 0x6336A405CA63D928ULL, 0x8AAA303F511217C8ULL, 
            0x14648C611B86CEE7ULL, 0xB96DC4AEF9CD1128ULL, 0x7A939642537CAD6CULL, 0xDABE5CD637BEA4A4ULL, 
            0xCB6C5088C89484C6ULL, 0x80D3DF808F0FFD39ULL, 0xE7862B1326B6A1E4ULL, 0xD0C12AAABAF364BCULL, 
            0xDB38E9D0DB629019ULL, 0xFB3A893A541ADF88ULL, 0x36B33495F390C24DULL, 0x0122306A7D08AF4FULL, 
            0xECA9389F7FAA5692ULL, 0xC36E776FAA4344C2ULL, 0x3A95A1EE34F80D4DULL, 0x55C5863343B87DE3ULL
        },
        {
            0xD04C13ADB06C7818ULL, 0x0292E1C98A64EB47ULL, 0x8CAAF06118B3EB0AULL, 0x2DB520E21CAAEF41ULL, 
            0x603351F58BB32422ULL, 0x7C47022AF2C49978ULL, 0x41EE5DBB66A4FBF6ULL, 0xFE096CC08F1085DEULL, 
            0xB43DAD2AA10D60DDULL, 0x6161FFBE5D74B23FULL, 0x155AA3750011E34FULL, 0xEE87BA10D655515CULL, 
            0x9004077079A06A71ULL, 0x1D2018E793642C53ULL, 0xDF958FDC9BB06B76ULL, 0xC42B6F1769B95627ULL, 
            0x00A62EC209625533ULL, 0x86AAC3DA5876D1F2ULL, 0x11D394E648764677ULL, 0xF8D937C431200DD7ULL, 
            0x6CD6DA526E5F2533ULL, 0x8140616E42DFB13EULL, 0xDFC8A0A359A00C15ULL, 0x93F4BDF6848EF9E4ULL, 
            0x75A184BBE1CC666DULL, 0xA9E95B9B0E5071E0ULL, 0x3D3D79315CCAF27AULL, 0x3AAF449D3C904EC5ULL, 
            0x6189C8F2815D18E2ULL, 0xC2D1FDB8A7D7EAC8ULL, 0xCA32DABFF1A3390BULL, 0x2C34B9052785F3A4ULL
        },
        {
            0x4A25764C3C9EE890ULL, 0x02D2305D90DED879ULL, 0x4E1D3CF4E4371375ULL, 0x89CB94AA97887088ULL, 
            0xA6937F2BDE27FD86ULL, 0x43C113453B902DCEULL, 0x10B4F49EC42B2BEFULL, 0xE567EFFE91242D06ULL, 
            0xEF803B211176569AULL, 0x17F69CEC672E7DAEULL, 0xFC12E17239B4D09BULL, 0xF899381E90E19FDBULL, 
            0x8E149DA5645A1851ULL, 0xFE874F72F2D43239ULL, 0x47E2D344A10AE9EFULL, 0xCAF64EC01B0919C6ULL, 
            0x06D99B8C3EFA50CBULL, 0x8838A79CE1B6594FULL, 0xEF2F1F70720224D1ULL, 0x83E4DB2D6205CD7CULL, 
            0x5E17D63E2E6A6953ULL, 0x72E31C90154BE60DULL, 0x3F5107F6BFFFACFDULL, 0x17A497121B15585CULL, 
            0x1AB93A1EA690DC15ULL, 0x6130FB5C40F0BAF2ULL, 0x3635324F01E5885CULL, 0x3AA73A65A3752B2FULL, 
            0x47A8448733DCAD1DULL, 0x240EBC73A7FC0732ULL, 0x13B018A747EB309EULL, 0x49DBA0A17BEB8665ULL
        }
    },
    {
        {
            0x18DE8046A0D2724CULL, 0xF4B2B5C1D01AC62DULL, 0x1D358200924E8A28ULL, 0xFB5DC84C36BF8617ULL, 
            0x3F8445736709CF25ULL, 0x9ED713A1ED372772ULL, 0x40FD46C96426AFA7ULL, 0x8E4962A4B612487EULL, 
            0x34D1ABE8D7BC6041ULL, 0x0513E39EC1EDFED2ULL, 0xF9BDDE7BDA7B7E45ULL, 0xD28F9BFD7AA2FF2AULL, 
            0xAFB6A4D7EAA1E779ULL, 0xA4A4F5CE605AF559ULL, 0xD846334750261579ULL, 0xA589C7B01C89D179ULL, 
            0x81AF2343115BC28EULL, 0x6BD57A11C6D5B08EULL, 0xC44DE69C3D246ECFULL, 0xEE86ABE6A7AE2AB1ULL, 
            0x3E79DE739285381CULL, 0x73F9C38D27D85EAFULL, 0x1A02EC7FAA04AA85ULL, 0xA5DAA312535AC8E3ULL, 
            0xA224837EB15FC170ULL, 0x164C7FD2EDB4E671ULL, 0xD3BB2FB420DB7CC3ULL, 0xDBBFFD3FB75A9D2AULL, 
            0x0834662C8EB7069AULL, 0x6A3D43582BECA179ULL, 0xB1D43CCD10E76825ULL, 0xB97D49C791D753FEULL
        },
        {
            0x960F858C6742073CULL, 0x30B9771B12C8DC20ULL, 0x7028FC2C76AC8201ULL, 0xCDE481E547B7E17CULL, 
            0x724F1DCBD2F8BA62ULL, 0x14B8623991E11E94ULL, 0xBF5A44BBADD9FD3FULL, 0x961E0A35FBE6AEEFULL, 
            0x6F118AAFB3EFB9DAULL, 0x502FF6877A4D03F6ULL, 0xDDBD4A55A6F12249ULL, 0x9015686D6BC6001DULL, 
            0xD38FF23D1C2B9243ULL, 0xB1E21CC5DED351B8ULL, 0x1779350945495421ULL, 0x1C8BCD40339C21E5ULL, 
            0x3B7BC10A5EF1DCA7ULL, 0xD427289AB591D740ULL, 0x95537C69689B654FULL, 0x5485405903CEB585ULL, 
            0x13E264A8790673A6ULL, 0x80573D3FA726BA99ULL, 0x9FCA019C7A88B0F0ULL, 0x3BDA37D8372EB4FAULL, 
            0xF2BD499983419E2CULL, 0x60075F6BDD36D3C6ULL, 0x105CE2365B806173ULL, 0x4A293518DAE01387ULL, 
            0xA6941C2AFC2CCA61ULL, 0xDBA2FF8E13EAAB3EULL, 0x8E6D38BE801CA234ULL, 0x143123EB5BF5AABDULL
        },
        {
            0x94B5C099D061F5B7ULL, 0xA09E4BFDB6F9A678ULL, 0xFF9B8F20B1C12D7FULL, 0x0108976B07A23E2BULL, 
            0xEA0446681557F1E0ULL, 0xFE28D89731051641ULL, 0x9529DCC02C80739FULL, 0xCB8592202794D8F3ULL, 
            0x94D2A452CAAC1FC0ULL, 0xB696BD1B77C7FBAFULL, 0x3BE63814CF8A142EULL, 0xD6A6826C1C14D171ULL, 
            0x39F8EA76588D29ADULL, 0x4E147D9CAA88A72CULL, 0x68D11C75528E2B04ULL, 0xDC5086FD1392AA97ULL, 
            0x60B2BCDA23A2AE19ULL, 0xBDEFE993DFD11AC6ULL, 0x33A4A92A03CFA5DEULL, 0xF7131C31D05B68F4ULL, 
            0x3DE3989BCF056F17ULL, 0x0BF7CA1634FB500CULL, 0x2EA510432254DCF5ULL, 0x863CEB68A0DC9E20ULL, 
            0xD1B665AA2BCCB6DAULL, 0x56597CEE643DB411ULL, 0x823B49F7CFAA632FULL, 0xC0B31B9658107493ULL, 
            0x5D76C74A353EE578ULL, 0xBCAEF834C7BA10DAULL, 0x98C5F7CF91598205ULL, 0x8B05EA320F5EF021ULL
        },
        {
            0xA0516FD53A0EA00BULL, 0x289157575469679CULL, 0xF319400EFCBF6CC7ULL, 0x8254DD5CB8E338D2ULL, 
            0xF73DD3B7B30AAC39ULL, 0x4315DC69026E2BACULL, 0xCBABACEE9F119980ULL, 0x0EF636B2D258F889ULL, 
            0x4EECAD81F12C3EF6ULL, 0xD66089991184E0A5ULL, 0x71C5BE5D00C68CC7ULL, 0x30CB6545BF2F09E4ULL, 
            0xA9C15CDB7E5F9CD2ULL, 0x9BF1E9DDB55EB440ULL, 0x7B293E9071572AF6ULL, 0x3567DFF953D4FDD6ULL, 
            0x361BB95FBCAA339DULL, 0xA556F79ECD9A86E3ULL, 0x78DE8439705ED9D1ULL, 0xEAB68FC8F18ADEBEULL, 
            0x0ED5F61CDEB64106ULL, 0x1CABC1673B82F597ULL, 0x3795B7095BD16746ULL, 0x1271334AAF108E2FULL, 
            0xA89DC2DFA44EBDA9ULL, 0xB7BC62136B264408ULL, 0xBCBB989E997A241CULL, 0x4D7B37A515CDB060ULL, 
            0xB087D40C61C768B2ULL, 0x6A2A5A99888128F6ULL, 0xFFB6FFBD2195D9B8ULL, 0x439F9A377E5069EFULL
        },
        {
            0xF6930D81BB4D46DAULL, 0xB9E91440B2C90D90ULL, 0x49716089F40D64AFULL, 0xABFF274C4382D06FULL, 
            0x25860297E38E3AEBULL, 0xAF0A5EEEB28D8364ULL, 0x8727575E36E1A499ULL, 0xE846ADB68FB3C5ECULL, 
            0xB760589445A40D10ULL, 0x2F575F83E3E86398ULL, 0x79CCE4A468F9FC92ULL, 0xBBECA7E92DFB8D4DULL, 
            0x96BB6A5E4FEAAD6AULL, 0x2B7E3144523BE358ULL, 0x1A2EFCCFD457E1F0ULL, 0x349D9B2C82EECA72ULL, 
            0xDA4E32A0588AA0B2ULL, 0x65DAF0C3BC2C1A1DULL, 0x463D11B187D16704ULL, 0x2B74AB3F97FA5603ULL, 
            0x0B5CB36CE609E5CEULL, 0xEAD2D4967E7E32A2ULL, 0xD1BBF9F14EE87C6AULL, 0xBF9A3D9CED12FF2FULL, 
            0xE8CEC75CEDE4E9F2ULL, 0xF4A965B83BC7F27EULL, 0x27C46B74D945F605ULL, 0x5FC05B084DC80F8CULL, 
            0xBA0548CF1E461A17ULL, 0x97A0FEC2BF5CB0D5ULL, 0xFBE59B0A1B649858ULL, 0x7E14097CF24CC97AULL
        },
        {
            0xB6510CBC8C48EF12ULL, 0x2318D0960D257F0DULL, 0xF4D318238969BF0AULL, 0x420B8010F156D41BULL, 
            0x9A93D9DA9C629870ULL, 0xE175099C7A4E806BULL, 0xB12F5B8E524A7155ULL, 0x1CC1BF748C692090ULL, 
            0x165F5F55EF39BCF2ULL, 0x751EED08CB78C43BULL, 0x8E3A5AEBAAD59FCDULL, 0xF349659577AC7DB8ULL, 
            0x03C3238BECDD0552ULL, 0x90A760F89B9E0CF7ULL, 0x9F70E5E9736E936EULL, 0x6887E84E077CDD3EULL, 
            0x87406141919D0E26ULL, 0x10F646F35E606884ULL, 0xB85B76DDF14AB0B9ULL, 0x064ECFC5205F17CDULL, 
            0x7A2E6719F1118618ULL, 0xD86D0CF7CD7678C7ULL, 0xE0A3C0FC2BC2269FULL, 0x0D62485484847172ULL, 
            0x039886E20F321342ULL, 0x223B7D3A76B54B79ULL, 0xFA116E08CF93BD99ULL, 0x47A3C1C740B039C4ULL, 
            0x72DC76784BE81A72ULL, 0x2F40861082911715ULL, 0x025BD4F7074BA204ULL, 0xB761EC87A97BA7C8ULL
        }
    },
    {
        {
            0xFECAC70192376B18ULL, 0xB83A1A7D18E00030ULL, 0xD7E7CEBFCAF14D87ULL, 0x3D2D9F2D1B9F72D9ULL, 
            0x6F2E814E55B2D927ULL, 0xDAC7F19DC8B58C57ULL, 0xB9FDE21AA1183B82ULL, 0x60BA0ED403AB356DULL, 
            0xCBDC7BF04DB07C94ULL, 0xF6F96D0EFB1838ADULL, 0xA4DBD64AC6274890ULL, 0x96D83FFE8E4F75B0ULL, 
            0x65CCC13CA11A0776ULL, 0x2E1249948021867BULL, 0xCDC81741061C9B37ULL, 0x925C92D57B0B7C3BULL, 
            0xC08F2061F5161A7FULL, 0x8C8AB3FDD0D77EBDULL, 0x609ABFCB63161A5EULL, 0x4A5512A08C41D490ULL, 
            0x2719608F1387BB92ULL, 0xDA14604AC6D3463AULL, 0x0426664D513F3D8BULL, 0xDC21821802692835ULL, 
            0x5A49B3077BC1F616ULL, 0xA25A7B775B52B1F9ULL, 0xC9B99FDCA3B8036DULL, 0xF3B10F31AE10B632ULL, 
            0x47A4CCAE8675971FULL, 0xEFD4471AC1D0C94DULL, 0x940026B5D6E1EF81ULL, 0xDE7BDBD98E517AA2ULL
        },
        {
            0xC09C127B33E6C0A7ULL, 0x58B8BEB751265E12ULL, 0x697C3CA3C74C38BCULL, 0x8FE022F13158AC7FULL, 
            0x34CB45A877ACCE07ULL, 0x7DA6973669D0D461ULL, 0xA06BC92CED38C9F6ULL, 0xCCA2F71DA85B26D9ULL, 
            0x9A9EF558E27325F4ULL, 0x1C113D6FFEA643DDULL, 0x65D855E1C34108D8ULL, 0x1D62364B664A48E6ULL, 
            0x26698E4C1F7E8112ULL, 0xFBC5DD5F4017E27DULL, 0xCE0BA5CA4F667D8AULL, 0x81069281514C3442ULL, 
            0x2EF36E88A4989437ULL, 0x1059CCA32E5FE2A2ULL, 0x8E78F33B858DDD7DULL, 0x57077EE8D332301CULL, 
            0x209BEFA5030CB1F5ULL, 0x4D88F3D40A066D1EULL, 0x53D17AF3427986C8ULL, 0x9B7D6B333CD90566ULL, 
            0xE8503D81C9865DB5ULL, 0x55DFB0BA2DCCEBF2ULL, 0x64950823B9654A59ULL, 0xFAE061B7C98D7334ULL, 
            0xF8CBA960ADD3CA15ULL, 0x7F5FD2A145FE053BULL, 0xF7D9FBDD5034275CULL, 0x66774E8E5BA10C6DULL
        },
        {
            0xD1CD4BB7D720518CULL, 0x19297D3B3216C03AULL, 0x0974DAEE2762DF74ULL, 0xCBDBA7E71F03EDD2ULL, 
            0xD53B45C1AFDA0D0FULL, 0x003E21269908C1AAULL, 0xF17DEDFCD434C962ULL, 0xCCE10132ED102F58ULL, 
            0xEE97C0D51FF33601ULL, 0x165C9605A87BB786ULL, 0x8257F042F3F3D4A3ULL, 0x2AFD8F2CED452F8BULL, 
            0xBEAEB0CC49A16FB5ULL, 0x472676AB32F6FE39ULL, 0xE5C3762189341F8AULL, 0x6330CF88FE7FBBF2ULL, 
            0x8BD218F48F05379AULL, 0xD30D8568BCAE0590ULL, 0xCBB668AE3D28881DULL, 0x34083D9948586519ULL, 
            0x303DA9E3F7BECAD2ULL, 0xDA08D16911E57DB4ULL, 0xDBE34BDF81446DA6ULL, 0xF7D9C062739230FFULL, 
            0x6A21BA21132E3CEFULL, 0x29FBD0F8581459BBULL, 0x3BF88AD8CC5D2D3BULL, 0xED2BA96140E58921ULL, 
            0xB2814930DC6D0E43ULL, 0xD2AD3D2E186C2353ULL, 0xE711BD9FC91DA01FULL, 0xA34D67D2BEB6E6FBULL
        },
        {
            0xC4CEB137719210C9ULL, 0x3D6D0837CCC85624ULL, 0x2FF529062B295163ULL, 0xD6CD3FC68488F78FULL, 
            0xDD01A342108A117AULL, 0x3650E2226985C083ULL, 0x5AE5027ACD3CA103ULL, 0x6AAEB20D9B16D4FCULL, 
            0xD98DFBBF4447DBF1ULL, 0x1567A6522CC7A93EULL, 0xADF4087C55E6289FULL, 0xD5C8B505E2D6D59DULL, 
            0xC993E7EE2A2238ABULL, 0x794809300147AC6EULL, 0x580E1747A24797E7ULL, 0xC8097CB9B8BE6D2CULL, 
            0xE006C5A18FD8612BULL, 0x092200321E5E5290ULL, 0x563F9E0232530895ULL, 0xD0BDE12FB440415DULL, 
            0x227376BBBD8D503DULL, 0xDEF710134BB684CEULL, 0x0A752FE76D81F7D2ULL, 0x1878518C79360CDFULL, 
            0x4966E12A83075C35ULL, 0x2EF6D9CBAEF8A07AULL, 0x8A5DD307ADE7A856ULL, 0x4B1D687443D47498ULL, 
            0x7E7005897DE6D690ULL, 0x7FBDBFE54DF58799ULL, 0xDD54677180456A45ULL, 0xC6652E872AD89E1BULL
        },
        {
            0x7DA85F4F0D6CFCE9ULL, 0xB9D77860D55C8B13ULL, 0xC49B115810B5B2DFULL, 0xFB5780A5738AFA18ULL, 
            0xC040C8EAF4C93024ULL, 0x3F04DE5C4B2FF9F4ULL, 0xBA4FD3A1B17F2C2CULL, 0xE43C6BF6FBBCCB00ULL, 
            0xB845C1F268A83F85ULL, 0x67672A343401142AULL, 0xAE1B14A245208484ULL, 0x364654B59156ADB2ULL, 
            0xE79087F68E0FA3BEULL, 0xCE53AA8F2F30861CULL, 0x8A122A9EC27A4CACULL, 0x70B842C80CB7EE3BULL, 
            0xAE37326B784261BBULL, 0x67123A4B7641BA94ULL, 0x251F57B8F7745DFAULL, 0xE8309F525A4E397EULL, 
            0xDC63063F98AEF062ULL, 0x7DD99093B8E90412ULL, 0xF936299D60CFA3BEULL, 0x3136D8C9DDEC245DULL, 
            0xE38DF11ECDD91893ULL, 0x1D22A17569CA2509ULL, 0xFB2DABDAEE8930B8ULL, 0x6591E475907CF5ABULL, 
            0x9E66C65A2FBD34EFULL, 0xCE3CE06481FAF4A2ULL, 0xB64C19240D276DA3ULL, 0x556CC9C5992C3A73ULL
        },
        {
            0x0759E2FC8F94CB0AULL, 0xDAF93728A6371405ULL, 0x46E30272EFDB11E1ULL, 0xADE4A123167FB4A9ULL, 
            0xFD5FDB1C703CE39CULL, 0xA15F7E64DEB8BAFEULL, 0x055C1EE05D5E1F09ULL, 0x6CD00603B0213006ULL, 
            0xF89D76B36F3D8601ULL, 0x17CD4312DD12891DULL, 0x497DCAE8EB8DA250ULL, 0x18D412EFE0245A9DULL, 
            0x67DAF4845A9CD324ULL, 0x41326E919C49A93AULL, 0xEB4AD82952582984ULL, 0x0B3C9713C430A8A4ULL, 
            0x10C50EAF20A4886EULL, 0xF910FBFB8B556923ULL, 0x3EB50BCE0006AD36ULL, 0x0F768D87C8BFB2A2ULL, 
            0x98AEDAABE400B18DULL, 0xD937C2362450173BULL, 0xAF6AA7DEC7546AFDULL, 0x96B7A5CBC5B22FACULL, 
            0xCCB0A4C6826ED75BULL, 0xDA60520D511946C7ULL, 0x1BFD77441A54D9B6ULL, 0xCBB04A9807242BDCULL, 
            0x7D856E16D715F9C8ULL, 0x02B51CF9F38766BAULL, 0x220E0E35ABD63942ULL, 0x5AC9C04690FD853AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseAConstants = {
    0x9F0BCB9E94626416ULL,
    0xA1806E5D3E4C05BAULL,
    0x9C99A07BFD6FFC25ULL,
    0x9F0BCB9E94626416ULL,
    0xA1806E5D3E4C05BAULL,
    0x9C99A07BFD6FFC25ULL,
    0xB8F97B87E7711A7CULL,
    0xC728161B24466847ULL,
    0xBB,
    0x64,
    0x04,
    0x42,
    0xB5,
    0x66,
    0x82,
    0xF3
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseBSalts = {
    {
        {
            0xE89393B145DCEEC7ULL, 0x45C5AFF167393C09ULL, 0x4CAEE2600D5A4D16ULL, 0xB56982A6CB9966A7ULL, 
            0x4A602657110FF8A8ULL, 0x25748FAA67291A20ULL, 0x209E0E12A54A980CULL, 0x535472134F19F80BULL, 
            0x045AF45D9B42C933ULL, 0x84C39EB7E7CF03FFULL, 0x5FE478AA03808313ULL, 0x3A586847D0394DE1ULL, 
            0x8435FA10FB176CD1ULL, 0x68DF3FE1266B6CE7ULL, 0x704F1BEF54E3B575ULL, 0x16BED71F00A25B1CULL, 
            0x3384DE49C615935BULL, 0x0111EDAAB651261FULL, 0x782F07A762B5ABAEULL, 0x1A31A676CFC9237AULL, 
            0xC434F049E6EF47E7ULL, 0x599D89BCD398F05CULL, 0xB1D2699400C28CFAULL, 0x58B8EA57888AC57EULL, 
            0x7271E3C7A12DAAFAULL, 0x0ADBD23E194B52ADULL, 0xE471A02F93873134ULL, 0x93078AC1E939C90DULL, 
            0x8C5BB837C715ECE9ULL, 0x48A1F38AA64D0BEFULL, 0x8973B2EA08DF7911ULL, 0xA110CA165947BC4CULL
        },
        {
            0xFE3C48D080B1E733ULL, 0xA5A5B11878DF0C60ULL, 0x065727299AD8101AULL, 0x64CF4BD19168D917ULL, 
            0x7CC9710BE12AEA69ULL, 0x2FE65383C2A26074ULL, 0x5BCF4F6B3B2E1D51ULL, 0xA1F2ABBE8D1611A6ULL, 
            0xBECA9880B94F1459ULL, 0x416A29098862DA85ULL, 0x34E2BBEDDF9DE056ULL, 0x7E6B2F380DA577ACULL, 
            0x57E6CBA26430D461ULL, 0x1C7A5C7B551323DBULL, 0xCAE23ECE8C6A088DULL, 0xBC3B8136B950634DULL, 
            0xB5525485CEF3673AULL, 0xEC8F0CDCC6891535ULL, 0xE9D61BC4F3CF75FAULL, 0xFC3304F3837842ABULL, 
            0x16AF6F2076E2340EULL, 0x7ED515276DCABC97ULL, 0xFD93EBB7D91FE70EULL, 0x7743C4865126C13EULL, 
            0xB429754B11038633ULL, 0x0E0C91513008C892ULL, 0xBB2AB71BF27B2017ULL, 0x4A5B6F0F4AC52728ULL, 
            0x6270813098BEF847ULL, 0xFB55066296863CDEULL, 0x0DF15D818981ED36ULL, 0x1BC967E4615F883CULL
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
            0x1CA67397A3573267ULL, 0x28A562726C01C74CULL, 0xEA3D1C2DEDB5D4E3ULL, 0xD45C0D7CB7CE949CULL, 
            0x32DA45F62E114A7EULL, 0x8200387AA83A94D6ULL, 0xD7474F1873FFFBB8ULL, 0x06751979B46AB50FULL, 
            0x80395F0105990162ULL, 0xE8BCE5063D8660F6ULL, 0xCB1F57C748C54063ULL, 0x7F9E1D3E0CF3E3FAULL, 
            0x2B3C673D36D3D3D5ULL, 0xAB65376DBECACA1CULL, 0x4BB920363B9C201CULL, 0xC3698412E2047296ULL, 
            0x15E78825BB3C93E6ULL, 0x053410280FAF0182ULL, 0x09207DA45081167EULL, 0xA9E6A811414BD76DULL, 
            0xF2ADDF79BE5E03BDULL, 0x6F508A5B5382E6F5ULL, 0xEF07538F5C12A29CULL, 0x8CB1D763093582C6ULL, 
            0x5DCDF4E37EE60005ULL, 0xAB086CC3DB663D89ULL, 0x2FB265637BAB4007ULL, 0x496CA87D0E6A751FULL, 
            0x4B0680B41C5C23DEULL, 0x88F9E7CCB4621132ULL, 0x8AD50B81B708F447ULL, 0x1ACAFB8124EB0CC0ULL
        },
        {
            0x230E9D7ABD981A73ULL, 0x6266CF67080B0307ULL, 0x98886C69E2E712AFULL, 0xCE1FCF8238B0D2D7ULL, 
            0x4A91D1EFBDA46DA3ULL, 0x7F183BAC2A3ED82DULL, 0x6C2CFAE8735C2BC4ULL, 0x0F01F08C31DC9C7CULL, 
            0x8E1D3E4D87F47B67ULL, 0x71A5F4E1701E1B61ULL, 0x22F48C4F00809E87ULL, 0x16723ACE9E6CD72DULL, 
            0xD938E5920C8E4D44ULL, 0xB0BEBF04C534FDD6ULL, 0x533B126C164D1E48ULL, 0xAF7C0E6C3C814B8CULL, 
            0x8AE3CD32BB61B3C4ULL, 0x4C5B0F13C4CA5E8AULL, 0x7C813795F3E44FA9ULL, 0x8AC1C9C0EF5AA237ULL, 
            0x13D7B9F13F201B13ULL, 0x66E2F7175F5E6DF9ULL, 0xA07BAA1CBED16D10ULL, 0xD64315B6CC2CCC98ULL, 
            0x16A461CB9FD1C425ULL, 0x32B560F3A62180A6ULL, 0x9B595E0DA487DA26ULL, 0x49CB5E037A3CFB07ULL, 
            0x28D3E42DE8EA0708ULL, 0x87E1332B3B4BC56EULL, 0x2F0280B734FE8377ULL, 0x58EE8CE9935AD3DFULL
        },
        {
            0x6A4E20595F0CDFF7ULL, 0xE6B8D6668BBA536DULL, 0x6B8799E62884AD8DULL, 0x7C824294698051D8ULL, 
            0x1E2081D15CD208D2ULL, 0xB5FDD66A400A3444ULL, 0xC4C6D0E773A220C3ULL, 0xB7A378B00289A8A0ULL, 
            0xB65FBC8F5B2813E4ULL, 0x88DA25BEA9B9E981ULL, 0x47440D11C66B3587ULL, 0x4FA090F5DEAD0250ULL, 
            0x9F0C597DD3F71C89ULL, 0x4E81D2FCF2AEE44EULL, 0x9FA298252C40CB1DULL, 0xFF47B5E0EF9D1753ULL, 
            0x08D52EBD9CDB2B37ULL, 0xD81EA25B33F27904ULL, 0xF4B51732A3EAFE6DULL, 0x4CD20425884D90D6ULL, 
            0x9AF534FEFB8B7A3BULL, 0x2FC4B1F5E3DB7759ULL, 0x42F79FCC52EEB1C9ULL, 0xAF1ABA387BB8C560ULL, 
            0x80003DFC423AB253ULL, 0xDB6055C8BBE89891ULL, 0xEBE97C660162E9BEULL, 0xF5CA9D98C56BEBEEULL, 
            0x8A06BDD3E7D58378ULL, 0x156F05277A220212ULL, 0x60D75C7056D81B3EULL, 0xBD43D0966ACC5FF3ULL
        }
    },
    {
        {
            0xE28F0ED547188F8AULL, 0x4E25BB304EE04AA7ULL, 0xFF50D3D668D13BA7ULL, 0x891E80C0C56018FBULL, 
            0x18EA263DF532625BULL, 0x92B567EC092F9EC4ULL, 0xD74EC9D39036D31DULL, 0xA5D86F94AE84F94AULL, 
            0x9D2EF4E3119C1470ULL, 0x17C763A105CD7657ULL, 0x9937D657FD9973AAULL, 0x1C9088116470A3D9ULL, 
            0x3446CD5247CC9A45ULL, 0xFB237378CFD707DCULL, 0x045C4E443945E263ULL, 0xDA3D6A1166AE39B5ULL, 
            0x09541B52F5FCAA03ULL, 0xBBC4C77252676E08ULL, 0xB2F98E308DDD2C4DULL, 0x88164DA22352F453ULL, 
            0xBE876E1270DF9C9AULL, 0x8507FA1DBCE4B56CULL, 0x9C9DFDE514723E37ULL, 0x1095E62A23420EA2ULL, 
            0x47D9C2EA967C9159ULL, 0x24456E978C10EB65ULL, 0xE487FA5C9C39E15DULL, 0xCE5C29A49521374EULL, 
            0x4D2CBBD17A7A1D98ULL, 0x5688DC7744CE3C31ULL, 0x125D4543E73DDB1FULL, 0x74AD20DE05950798ULL
        },
        {
            0x36A8371D81A1EEEDULL, 0xFA8716E6A48D1733ULL, 0x0FDE7E58152D4854ULL, 0xCFDC0FC758634777ULL, 
            0x26C94D738E72E8BEULL, 0xA6D56614E9FD7D1AULL, 0x38004D076FF97C38ULL, 0xF794FF409E9F76A5ULL, 
            0x781C92AB62FAC251ULL, 0x615277B4B2EFA58FULL, 0xC7300CB8D74762E2ULL, 0xC08324FF87955323ULL, 
            0x50AC6E6142E377E9ULL, 0x7037373585252156ULL, 0xB8B3A4FBFCBED548ULL, 0x28769FA787BDD3B4ULL, 
            0x2243B4003333EE51ULL, 0xB5A432F99BC3039FULL, 0xE9EBEC2F4EAD3E70ULL, 0xAD73EFB59472C9AAULL, 
            0xE35C2BC28D4DC595ULL, 0x4AABDF576B7775F9ULL, 0x8CEACFD6878B7D4CULL, 0x5345E68056BA4A89ULL, 
            0x52C6E0612C7E552FULL, 0x5619627732D48710ULL, 0xFFB44C9742337DFBULL, 0x364FA096C48E0E65ULL, 
            0xDDBBE4442E4CE0D6ULL, 0xC1777771EC6273ACULL, 0x0AA0BE8153214AB2ULL, 0xB46A33E47E49D886ULL
        },
        {
            0x0484A574EDB19890ULL, 0xF552A7EE2DE36332ULL, 0x64D284FB2306E171ULL, 0xA126B397EAD57DF8ULL, 
            0xBEEFFA026C473BDFULL, 0xC929DEA1F8B79694ULL, 0xCF7F8D570A80545EULL, 0x4B5DE935A38A6B33ULL, 
            0x33E63D038A5900EDULL, 0x73EDFB1E586B2FF2ULL, 0x987C1F7DE6704B6CULL, 0x6FFBEC00C47DE102ULL, 
            0xB2A7FF0218668BC3ULL, 0x74D5ED1CCE54D4CBULL, 0x96E594D156DA49FAULL, 0xBE0D56FB74888BA0ULL, 
            0xE8FCF032FBBB558FULL, 0x38C33C544A587A32ULL, 0x623DCB0817DC818BULL, 0x42ECFC2D0A49995CULL, 
            0x2F1D02C42AAD61EEULL, 0x16E7A46CA8017F10ULL, 0x7E85B90B509E0CD6ULL, 0x908C0F02ADB6BC1BULL, 
            0xAF05BDA93F0CE67FULL, 0xAEB8EC5CEC404690ULL, 0x6B947128CC1EF510ULL, 0xC840D75153AD9D1EULL, 
            0x2EF4E8FDBEC58D2EULL, 0x3789F03D89A87731ULL, 0xF91090774CC42539ULL, 0x350FC4CE75B6B1E2ULL
        },
        {
            0xB238B8DBDD94AA7BULL, 0x21B677F813582394ULL, 0xAC979F55B63A4BA7ULL, 0x7DB61695779D7C5CULL, 
            0x868D6453C7940F60ULL, 0x9E974CCBF8D57FADULL, 0x95A33E5DB0CB20CFULL, 0x76A3E1F67B0475FBULL, 
            0x95F0D58A435D639AULL, 0x0B976439C8755D83ULL, 0xC23B5ED943C3CCD7ULL, 0x418323AA1897B55BULL, 
            0x2640A33BC933C72EULL, 0xD10CF84A1B1C9901ULL, 0x2CD34E4C80E5ABA2ULL, 0x2190262AA4D09831ULL, 
            0xB67F059DFC2E0C22ULL, 0x70CB411971A47A77ULL, 0x922EDD6289B82C02ULL, 0x7B254514E8FCEF56ULL, 
            0xC7561BE1111291C6ULL, 0x8D1B26E9D059B457ULL, 0x0E1B353DF947D39CULL, 0x89EAA6B44C0AEE0FULL, 
            0x756F6AB21A9EA08AULL, 0x888526C1866CC203ULL, 0x0B44872B384E9215ULL, 0x5ECA67D66878E6B7ULL, 
            0x861BF9F99D3F181CULL, 0x787A871370AFC653ULL, 0x97EE9D5ED13B7749ULL, 0xADEA598C29CD4449ULL
        },
        {
            0x84DD1DA69AA2663CULL, 0x97D9192804B45C83ULL, 0xE07FAA46387F9DD1ULL, 0x1FFAF8AA39DA906EULL, 
            0x2F2BF4999AC6DA44ULL, 0x3A90E767DC377DE4ULL, 0x2B2784183860663AULL, 0xADD3387E17B880F6ULL, 
            0x6F826D7CE3AAA052ULL, 0x66FF5695E14AE1FEULL, 0xB2210FCA09F66759ULL, 0xE140C27738B77003ULL, 
            0x4F142815F623EE97ULL, 0x99697AA9F7DCFD4EULL, 0x405AD2C48B5B9B90ULL, 0x09BBE3AFE7FAD34CULL, 
            0x42882B8B381CA9CAULL, 0xDC614404164FEF68ULL, 0x07AB621611E17940ULL, 0xAFAE71D683BBC737ULL, 
            0xB62886458E3993A8ULL, 0x88A580FEE8D8AAB7ULL, 0x5EA3273D1B7A4310ULL, 0x371D85BA49A9605CULL, 
            0x79AEC9C7A43657EEULL, 0x13908BA4C3008273ULL, 0xB9780CDC7A60BAB4ULL, 0xC684EE0D3D123220ULL, 
            0x04BC321093943795ULL, 0x1E99265DC0F7F9EEULL, 0xEEB547C9A5BE7306ULL, 0xAD2011B6A95B04C5ULL
        },
        {
            0x64E4580D3D74FEC4ULL, 0xAE2C4E9CF35F51D8ULL, 0x73A885C979E08A7FULL, 0xD7AEE35F3A0441E9ULL, 
            0x7B9871F3E1A5212BULL, 0x657CB4A8D958460CULL, 0xEE8DE4B4F58C7EB4ULL, 0x43B5DF81395F87F9ULL, 
            0x2EAAF47FAA98F9D2ULL, 0xE783E5434E9856AEULL, 0x9284E99859379F86ULL, 0xBF8C7DC556FF5CB7ULL, 
            0xB8A79F4E930B66D2ULL, 0x1D189EC17389D9E4ULL, 0x8E20AA058A5D7CCFULL, 0xA5A9DACDE11B0F3EULL, 
            0x7E9E9207671B0A93ULL, 0x33A14F1E3EB5C536ULL, 0x7D2108DBFDD6FFD9ULL, 0xC6A5FDE73E62107DULL, 
            0xDD3B8F0BC1020093ULL, 0x1BE6D9B4415839B5ULL, 0x306731E130D06319ULL, 0x1474BD565B431AB1ULL, 
            0xD0AD704396C77D47ULL, 0x5BD37B9826CFE216ULL, 0x438DA7480BBCAC3EULL, 0x75D3BD9DA935945AULL, 
            0xDDC376FE101B581EULL, 0x681EC214E25FE96AULL, 0x994A818969E4F52DULL, 0xD79B0B9B1AECC7C0ULL
        }
    },
    {
        {
            0xB93C644F216AA47DULL, 0x5C3CAE35BAF38C2CULL, 0x1F4228ABCFE8B081ULL, 0x8127CE10F9811C3DULL, 
            0xAF58DD28BBBE6DEDULL, 0xF2C4F850086462DDULL, 0x0A913CD1DD73419EULL, 0x42F9FBD3DE8329D4ULL, 
            0x8715F5F6B0928B08ULL, 0x813E97B15BDBFAB6ULL, 0x78FD0CA6CC3163C2ULL, 0x8A5FAEE7AD06C2F6ULL, 
            0x7BACBD702AE0856CULL, 0x164386FFD1441307ULL, 0xA78F13A44AA3206FULL, 0x00D0926858015B2EULL, 
            0xB0A482E94B44DAB5ULL, 0xC0D993D576A58CDEULL, 0xE8E5FD0B39865AD5ULL, 0xD0D2E0680356B47FULL, 
            0xEE025D936B03DB6FULL, 0xBE0AA34424C03F6DULL, 0x41124ABB2D3F2FEBULL, 0x412320D9A1834B6CULL, 
            0xF49D5B5E0054BB06ULL, 0xB3AC3E57FC9B5215ULL, 0x90BE57322A7C0FA0ULL, 0xC71420C48995B5A1ULL, 
            0xCBFC72B05B4971E5ULL, 0x937895228690A99AULL, 0xEAE8A338822AFDE7ULL, 0x3E02050D8003CD04ULL
        },
        {
            0x5584983E8F1F9FABULL, 0x9E0307706D6A548DULL, 0x7FA92A276D55CDCBULL, 0xC4AB6D4C4A62150CULL, 
            0x65DC5CA55A965167ULL, 0xE42E56F6EFE58772ULL, 0x417E87372F2166D2ULL, 0xA4DEFF8677EB3451ULL, 
            0x41D636755312AAB6ULL, 0x117192FA79017970ULL, 0xFD524DB3D1FFDF24ULL, 0x1BD81599A0B370DCULL, 
            0xEB329673B2C17C3AULL, 0x4928A65608573B5FULL, 0xDDE8E33AFC742F3FULL, 0x7BC47E9F775F4DCFULL, 
            0xC663168DDD04B5C9ULL, 0x343DC4CD0773BBB7ULL, 0x8AB2664A5CB527E5ULL, 0x90C93461DA4E177CULL, 
            0xAA2AD3C1E703F2BAULL, 0x96ABA53DE6768242ULL, 0x39A891C02CE5FF7DULL, 0x6CA60C87136837CBULL, 
            0xCA36AA0E5C89E8F8ULL, 0xE0CE1D9379B135A9ULL, 0xAC51EA4C44C95803ULL, 0xE3D5997EF33DC67BULL, 
            0x73035CDE4D33B3E8ULL, 0x9D7856F52AE1D910ULL, 0x340E558894C37E65ULL, 0x92E2402DDCAFA10DULL
        },
        {
            0x3C796D6463266409ULL, 0xB219269F01594B34ULL, 0xC30604FB84D1D079ULL, 0xF03A8B207DC4B613ULL, 
            0x8740316F295CB995ULL, 0xDEA3C71636132357ULL, 0xA042EEA2021F3CDAULL, 0x96A5BB1729D9D61BULL, 
            0xC34287F928FA7D38ULL, 0x6B4347DCC784AFD8ULL, 0x70708387195957FBULL, 0x18A8DA7567EFAD76ULL, 
            0x752562BC53FCB145ULL, 0xE8D12F9F77F97F2CULL, 0xE637F497B4C0BCB0ULL, 0xA7E35B39A45F6727ULL, 
            0x54A6191543CCA964ULL, 0x9FDE199AFA6693AFULL, 0xEDA1DCF649DDAC6BULL, 0xACB06F4CBC0442B6ULL, 
            0x871D4DE9DF70982CULL, 0x74E6E882727D5BF7ULL, 0x1BD0FE84B2457BC8ULL, 0x7630EEB4CDC9C248ULL, 
            0xC4CA59A6C1FB5335ULL, 0xFC7737A6D78B9FEEULL, 0x9573883A3CF7D816ULL, 0x79C9CCAAF89E45FCULL, 
            0xF5AB760D62EBC303ULL, 0x483B4C8EC0BEFF64ULL, 0x10D5509472D2C68DULL, 0x1DD358875018A75EULL
        },
        {
            0x318BF2BC480F8B84ULL, 0xB699005C6D9C61E3ULL, 0xC3A44A2F7DAEA43AULL, 0x9EA21F2FAC3EF4A6ULL, 
            0x9FD08644FBDCEF0CULL, 0x08126E16B1E0BA8AULL, 0x15FF7AE22DAFB27BULL, 0x70E18A0E96676C4DULL, 
            0x91287DDFD5EF3895ULL, 0x0358F2F6F3E66566ULL, 0x2B45B6E7A8F122CEULL, 0x0D91CF97053DB404ULL, 
            0x2384C3D07C1EE1DAULL, 0x86075AEB4EDB505DULL, 0xB63B0B98D6DF1072ULL, 0x54DB44751D97760EULL, 
            0x5B89EED8BF89F85FULL, 0x580DCE44C9863F45ULL, 0xA6B5B7642512B32AULL, 0x1660463862CB1A96ULL, 
            0xB838E8130DD64E5DULL, 0x89B9D3021542A0EDULL, 0x7763C47A151AAC92ULL, 0x97026B6919B5E7EFULL, 
            0xA57872039F8CFFE4ULL, 0x715D539C38669B43ULL, 0x12022B28E91E4312ULL, 0x0623D0370281073CULL, 
            0xF7C5DAF1CB101E5FULL, 0x03695E54C5E13207ULL, 0xA323F6F472471DFFULL, 0xF88FE6884C725564ULL
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
            0x9C0348BEBB53D58BULL, 0xF0A8243EF936B396ULL, 0x28AE25CA84B0D700ULL, 0x12F5998F5447E9B5ULL, 
            0x355C0EB7869B0542ULL, 0xFE4234B95BB3D20CULL, 0xD4448C723EE68949ULL, 0xDB6CF2F7A90484D0ULL, 
            0xA2689775FCBFC3A1ULL, 0xFEAE129E71489AFCULL, 0x33FA2854AC1B253EULL, 0xFC59668925D8A6FFULL, 
            0xCAFAEF3089BE98F2ULL, 0xA973BB75FAA16D1DULL, 0xB243DD3DCED3EC94ULL, 0x5D8AA720B51093E2ULL, 
            0xBC74A15BDAC2CF3DULL, 0x64A41C63F021110FULL, 0xE5D08D0C842090F0ULL, 0x8129CFDFC47544F0ULL, 
            0x90579D6C2B30FA11ULL, 0x33DDDDB406A9DE8DULL, 0x603E8FDE879E7F58ULL, 0xA70F754B12AC20FEULL, 
            0x05EAAEB67F892A62ULL, 0xA2389A94A49FED68ULL, 0xC650D20BEC49A20CULL, 0x0528FA6DD9353233ULL, 
            0xB67B856D943661E4ULL, 0x333E5CC74AFC8C7EULL, 0x3468D4321CC6FB92ULL, 0xE028CC93B4FA1DC8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseBConstants = {
    0x693EC140AA597AA2ULL,
    0xBD86C15E1FF34B45ULL,
    0x0196A98587F96170ULL,
    0x693EC140AA597AA2ULL,
    0xBD86C15E1FF34B45ULL,
    0x0196A98587F96170ULL,
    0x84AFCC37A4D64DA9ULL,
    0xFBAE1C84B1C733A5ULL,
    0x07,
    0x3F,
    0xC3,
    0x69,
    0x4F,
    0x73,
    0x9D,
    0xF4
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseCSalts = {
    {
        {
            0x04FEC9E888A5B5A6ULL, 0x35908E062D903837ULL, 0x77E541A5F01C33C2ULL, 0xC46874C098147BB2ULL, 
            0x3F6C942CCFAB529CULL, 0xE6A073AFE68EB3B9ULL, 0x1DE4A991B195C742ULL, 0x73682F98B227C500ULL, 
            0x707DB14D385407B0ULL, 0x7443FD88CE1A5774ULL, 0xBB5D0523270BE59AULL, 0x2CBDB1BC0609B5C7ULL, 
            0x653D9285BD318857ULL, 0x7132C17B9667DAAEULL, 0xEF38F9CC34AD487EULL, 0x7577F66333CE2F76ULL, 
            0xD3C98F551E652922ULL, 0xC1EB86798FF9781AULL, 0x282B1EDF59C6780BULL, 0x7FF922E2B51432A0ULL, 
            0xFC42B765ADE7471CULL, 0x6B5EAF479D4DA71FULL, 0xDDD2B51A8BFF65CEULL, 0x0E85B9800C90B9EDULL, 
            0xE8ABF4AD79D7B6CAULL, 0x4F1E5E05E59C00F9ULL, 0x85711C7016C64485ULL, 0x542A8B30C691E51CULL, 
            0xFD39F8FE14B7CDC2ULL, 0x235AC2C91CA2A491ULL, 0x4C18103542963D06ULL, 0xCC16C697BD832B01ULL
        },
        {
            0xF6B3AA97FCE2DDE7ULL, 0xD0DCFD801FFDD9ACULL, 0x88CD3AB04F6B8B67ULL, 0xFF659CFDFD2BE640ULL, 
            0x07C5735D6AC1B4D7ULL, 0x513F4FFC6DF7CAD6ULL, 0xCB92DE705C822929ULL, 0xDA131531085B9E11ULL, 
            0x3D9D5DDF2FFDC30DULL, 0x44B11FA516CA5E74ULL, 0x5E5EFD2C495BFE83ULL, 0xF283570E23274A9FULL, 
            0xEC0EFD5E2EFD711EULL, 0x70B4DABF6233F4FAULL, 0xBD7BC372CF249036ULL, 0xE112B8C178F9AF5FULL, 
            0x018448A0E97C96B0ULL, 0xE1A2F34467E8DB0CULL, 0xB8CE2F7E937230BFULL, 0x6E3AFDE618D499F8ULL, 
            0x7FBA9E7BBB21A3D2ULL, 0x57C917154750E0B0ULL, 0x4DD1AAE00EF86899ULL, 0x1F8A498EA352FED4ULL, 
            0xA16FC4829401AD51ULL, 0x1A8C3991CA66864CULL, 0xE6807F5B37F8A52DULL, 0x03E927A40E06E4DFULL, 
            0xA9BE429256249638ULL, 0x90C810D3ED02BCB8ULL, 0xCD16D0E39ABA7873ULL, 0x7C1C5B32695C6282ULL
        },
        {
            0x4EF6C72C12DFEA28ULL, 0x1F8B2944BCE8FA3AULL, 0x9B644D62C1F82C5DULL, 0xA9D7B0EE364F87A6ULL, 
            0x797AD3A578CB6FE1ULL, 0xB7796BC631E0D18CULL, 0xDFE65B0C363031BAULL, 0xB083C3818821887AULL, 
            0x1DF3CC52EAEDC69EULL, 0xD877BA3392DE2AC5ULL, 0x200B681894D88996ULL, 0x4052DC78797222AFULL, 
            0x338D0733B77F6AFFULL, 0xFEB0CD558E799823ULL, 0x3E8270C56E217FADULL, 0xD8CC8E0027F1D1B5ULL, 
            0x2EBD84D5B4762D52ULL, 0xDB4F82C4B9B7A787ULL, 0xFAF2E7E68D51AFCCULL, 0xD4942F0F7C19B19EULL, 
            0xE5A4A128F257EE38ULL, 0xD731309EDC5C421CULL, 0x04C7F8302F73F120ULL, 0x49FC49DB5A3A2278ULL, 
            0xD38C8C41AF934898ULL, 0xA63BE5587A85870DULL, 0xE05F2F801919BA78ULL, 0x1C3BE2A6A3722EF9ULL, 
            0xBE52DEDC5DC8F6C1ULL, 0x283B54C88937B234ULL, 0x6125BF7DAE675BCEULL, 0x700248BA19C638BFULL
        },
        {
            0xBFA1036ACB68536AULL, 0xE1099894DEDB1704ULL, 0x8D54056D86E9EBA2ULL, 0xFFB4D3AD2770CF16ULL, 
            0x8486AE4F93A0710AULL, 0x9F18980FA0882449ULL, 0x909D8471A5585760ULL, 0x9805299DF53AE136ULL, 
            0xA01288AFBD006208ULL, 0xC142D05BCFDC6805ULL, 0x6B83C412660D3408ULL, 0x9177A6CAA6682E24ULL, 
            0x4DDE90AF3B66D802ULL, 0xA678F9FC7AD5E5ADULL, 0x1F052BBE2E784DEFULL, 0x235EE872FC47CEECULL, 
            0xFDBF47E6C67C0F78ULL, 0xE913CA3FC2905957ULL, 0x8CB7C1A0428DE268ULL, 0x7B966A49544B94FFULL, 
            0x4A59361F1037F53AULL, 0x695CC9EF5AA792AAULL, 0x53A78F7D8E447683ULL, 0x592142AAB72DB809ULL, 
            0x61CCD4BD168ABB28ULL, 0xE41145D6AF68D823ULL, 0x4A586A9DCE93ACA9ULL, 0x903ED63175998B5AULL, 
            0x09B919C7CC746EC4ULL, 0x06244B2813FB5107ULL, 0x70474A26E1E97B65ULL, 0xDEE42C17027E251DULL
        },
        {
            0x874D21C0C2CFB5A1ULL, 0x51F46F494E4091B5ULL, 0xAAD78353C06A5FF0ULL, 0xCD1C7B85D185D004ULL, 
            0x9FDFB0CD46598DB9ULL, 0x38583E5DCC9C077BULL, 0xA23AC6A4A1C8FA11ULL, 0x832A652763505E2BULL, 
            0xB88DEFEA283B1B96ULL, 0x9FF3F90D3963B00DULL, 0xB690931F43A29DFEULL, 0xE38D5CE855FA8840ULL, 
            0x01F86C6824A2FBBFULL, 0x090698A3BE0DA7DBULL, 0x23FE48A183B58B28ULL, 0xD9AF3DB13FDCB6EDULL, 
            0xED599CF15FF5ECE3ULL, 0x79D8C3FAAC96F013ULL, 0xD8FFB4645633FF72ULL, 0x4CBC78A177393108ULL, 
            0x3F15FEB8168A024EULL, 0x16074022CA85B0A8ULL, 0x4D11223BFA78164DULL, 0xDCD1E9D5E697FF43ULL, 
            0x7DEB5C62BE343DAFULL, 0xC27A076F4A6538BAULL, 0x868CF5ABCE594670ULL, 0x31CE14665C67B8C5ULL, 
            0xEF951428736476D9ULL, 0x835826D7452DECA0ULL, 0x0BD6A4B9C3F8AC51ULL, 0x92ABFAA963DF92D0ULL
        },
        {
            0xC8F535F7B8BC9B4CULL, 0x5D5A3D4ECD3A726DULL, 0x1B1A94169770C5A9ULL, 0x4F4FEA9488317535ULL, 
            0x894917BF85E6DCB5ULL, 0x7466E3ABE055B90DULL, 0xEBA94798E6D64198ULL, 0x51EB7120238E820BULL, 
            0xD920B301BD984FDFULL, 0x8CCB8B884CB6A482ULL, 0x405341E101588B2EULL, 0x3282BDF00AB57F52ULL, 
            0xF7C69D1604C47F3EULL, 0xC0CD800B52B02990ULL, 0x0F7BECBB474C6583ULL, 0x8EADA21C5D0B4CCBULL, 
            0xD91A60010FD47B94ULL, 0x961950707D108FB8ULL, 0xE9F25847EF801D7FULL, 0x32F60DF635081071ULL, 
            0x8E9F625C5DA1F014ULL, 0x8BCB4E4E66B3E64AULL, 0x2B41714BA358A9B8ULL, 0x97FDA58E438EA62AULL, 
            0xAD012BD1EAE12CDDULL, 0xECD1B0DACD290358ULL, 0x6FCC6FB1B56EA1DFULL, 0x2E92089C00A97ACCULL, 
            0xF5F42E3480CA703BULL, 0xF11316D5D82C8E3AULL, 0x1C0766CFB79A3B82ULL, 0xB3DCC6D9D1F00C69ULL
        }
    },
    {
        {
            0xC2B1382D5B1EA7FBULL, 0x37BF3AA2836110AAULL, 0xAC02BC90DAA68199ULL, 0xF4B1072F52189896ULL, 
            0x537B44E658742A1AULL, 0xFCA09369732446BBULL, 0xB31066C6C01154A2ULL, 0x5FBFDBA44C93107BULL, 
            0x6A6227FDC65DB4F6ULL, 0x92A8FDBF800B0076ULL, 0xCF157E22CB574C83ULL, 0x99704A300FEB9076ULL, 
            0x6EDCF3EEF159D632ULL, 0x4AC30E900C50EA94ULL, 0x6CF62A25B92D2DE0ULL, 0x6DDA260A8B418B32ULL, 
            0x04C4C0D1E3F569C9ULL, 0x6A8F2ABB064A2E1FULL, 0x7ADCE4C7759CA6C4ULL, 0x49DA3D748138C312ULL, 
            0x8ECCA85D42455152ULL, 0x9E4CE51FC46210B3ULL, 0x60A3FDFAD3ECDAA1ULL, 0xA130D2C14D02359CULL, 
            0xB641D27338F13989ULL, 0xE2848D274CAA8E70ULL, 0xC873DB1988FD5CA5ULL, 0x9EE03A74432082DCULL, 
            0xB4E8294503548C6CULL, 0x6A2AF8BD9ECCEBD8ULL, 0x68F2C278AFDC0D43ULL, 0xB72F948E872B9C6AULL
        },
        {
            0xD08F6B64AC48119FULL, 0x0ADF3257AAEEB1B4ULL, 0x9A586DBB52D6B873ULL, 0x1746337797FC4549ULL, 
            0x5D719A8CA6987920ULL, 0xF06CF8AF5BE7D479ULL, 0x1868E622D7984093ULL, 0x72C6D7089061B93EULL, 
            0xAC8CCEF6A99491F4ULL, 0x8816859AC155CC80ULL, 0x52655C88062DA322ULL, 0x077DBE3301B727C1ULL, 
            0xBEFB463F4F1CD574ULL, 0x506269354610E4CBULL, 0x6E1BF594FB47D5F0ULL, 0x624C2A120294B6FBULL, 
            0x8C78ECEC07D69A80ULL, 0x8A1893F0900A92BEULL, 0x79946C347A48845EULL, 0xB3B0A0D1FF6FB8DDULL, 
            0xD6A71F2D99B29DC6ULL, 0x21F8618816E0CFCCULL, 0x364340F9120806E9ULL, 0xD07AD2824E71699FULL, 
            0xD1C22B1763E3EE75ULL, 0x77D5D503766FAF34ULL, 0x0262A393735B91B3ULL, 0x970FD4296BD3D969ULL, 
            0x5B995D4ED20AB2EEULL, 0xE4EFEE318E998E6CULL, 0x5FB48AC0718EAA8CULL, 0x771866F273122BDCULL
        },
        {
            0x4ECBADA7A3C58A83ULL, 0xEA38CF0270BB7FE1ULL, 0x76A586968E3765B8ULL, 0x06399B0927733FC8ULL, 
            0x1C177D48FCF295D2ULL, 0xCB327AFBA14F3F8AULL, 0xB7651D78B480DC9AULL, 0x22F3F73410319807ULL, 
            0xD2C889BAB9A7B934ULL, 0xDBB3B5459F5C9A80ULL, 0x0EF7E46AEC17F597ULL, 0xEAF115AE84EE23D1ULL, 
            0xCF8C8B682F72ACF2ULL, 0x75532F065E4D231DULL, 0x7F380E147C69BF17ULL, 0x37DF1FB6C48DA092ULL, 
            0x0B3853D21B24E6CDULL, 0x6B0D8D9A96BBAD33ULL, 0x86E45DED78F2735BULL, 0x9D9D3C161747B3E6ULL, 
            0x73FD07F6E99D6259ULL, 0xAE1114054FB3F2B6ULL, 0x14F1C5F9B423133EULL, 0x2180875093A02063ULL, 
            0xD4C133198D19A31BULL, 0x1376138C82EB270EULL, 0xAB22F22AAE93278AULL, 0xCE202F977F7E407DULL, 
            0xC6017A6F2DFC3546ULL, 0x20655DE0D8F82FC1ULL, 0xFF7461B85A9C87D6ULL, 0xF45B19A2489AFD13ULL
        },
        {
            0x2A5A998115363FD2ULL, 0xA5803E2FD118DBF3ULL, 0x34FE42E82EE1CC97ULL, 0xEB224AE928A1FF8FULL, 
            0x0A583FB1A3A543A4ULL, 0xA94E143F7CBF7BC1ULL, 0x6FFADA652405340FULL, 0x9EFB23629D163F14ULL, 
            0x496F4DBCE933972EULL, 0xF6309DE4C19F7890ULL, 0x44ADEEEE5A09187BULL, 0x6EAFA64154179F5DULL, 
            0xE078AB6672AE5749ULL, 0xE8C7AEF017209EC0ULL, 0x7907E654D2E55DF3ULL, 0x89C9AC1EB2CAA689ULL, 
            0x0542875BB513CF04ULL, 0x088168C48019C92BULL, 0x4B60915709E54BA0ULL, 0xC632E0C8A22E28AAULL, 
            0x643CAA00A2707B7CULL, 0x1D1F989DF5A979B3ULL, 0xE31CC27C1C27829AULL, 0x2410E2EB902FDF81ULL, 
            0xE681F2FF95734608ULL, 0x684667B433C282DBULL, 0xEBB08D3EE4162BD4ULL, 0x753205A2E497FDEEULL, 
            0xA8285430B4F90BA6ULL, 0xF39A783CDDE0C135ULL, 0x31D6604405B05486ULL, 0x1CA17333B51F4208ULL
        },
        {
            0x705D4A1774396493ULL, 0xAF3E6538D3058764ULL, 0x1277777D1F430147ULL, 0xE4A217BC7587F615ULL, 
            0xE2DE6A3EC8155A43ULL, 0xF80C190F03B8AC1DULL, 0x397988C911BFD97BULL, 0x54097535AF117E81ULL, 
            0x4891E5DC345EB49AULL, 0x0C9AE8666B9F6DB8ULL, 0xA6BDD8C5EEC332AEULL, 0xF35AA021CB71C45FULL, 
            0x50699443CFB33C08ULL, 0x1F6C5387A2F51A29ULL, 0x4098718D67E122DDULL, 0xBC912310FC50ACFAULL, 
            0x3B3A589C2FD51246ULL, 0xDEA37D953B24C88CULL, 0xFBA2459B583505D4ULL, 0xAA5A023CBBCF3BACULL, 
            0xF1C81B729472ADACULL, 0xC509A9D835C3DD27ULL, 0xAE657DC326BF5B42ULL, 0x55D812D02A9D0FD7ULL, 
            0xEA03F38CD74818E1ULL, 0xF125FA352B388409ULL, 0x3FBCA493BC71E76DULL, 0xDF8F1CFDD808C746ULL, 
            0x7F0C412D84FE9BC3ULL, 0xD3BDE94C37DF790FULL, 0x2F6DFE64F0527D98ULL, 0x631B7267B5DE8F80ULL
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
            0x1F238D5E93527BF8ULL, 0x2027C35DF14B17A1ULL, 0x68BE807B85247E5BULL, 0x2DC168B284761920ULL, 
            0x117647843D4F659BULL, 0x9DCFC712CD5BB1D6ULL, 0xC21FA24642269DB4ULL, 0xE9579ECEB0DB3599ULL, 
            0x7718101DB8D5FB85ULL, 0xF577977FFDE5519FULL, 0x973A16DCA715955FULL, 0x4CE511BD965623C9ULL, 
            0xB4D13E0074567E4DULL, 0x5AAB3261B730A8F9ULL, 0x1466E9CC21C34086ULL, 0x8F01F09E71E63723ULL, 
            0x2C9D25F5698AD54DULL, 0x1E0A82FE01B574F1ULL, 0x8FA4E3FC804B7ECFULL, 0xFEDA48F82B1FB83FULL, 
            0xAA3977FF20457EF3ULL, 0x7F3FD00F32E5E917ULL, 0x04C7F00A98CB16CFULL, 0x035F3BD25477E734ULL, 
            0x4F127D9EE66523B5ULL, 0x83A7B03D8695BBFDULL, 0x69B3083B186C32C5ULL, 0xD96E9731DE589AC2ULL, 
            0x66DB7AE31CF610A8ULL, 0x82550831D796DF37ULL, 0xEF7768783102EC75ULL, 0x9668F743F4936CF7ULL
        },
        {
            0x3DDE43331C9CFA67ULL, 0xBD9E02C7D3FF0E1DULL, 0xDB2D69053E51560FULL, 0xAF65B6D7F32585F3ULL, 
            0xE36332DAA3E2B4BCULL, 0x91C0694F057ACF8CULL, 0x23377E9051C42DAFULL, 0xE1383D6601DE2058ULL, 
            0xF09D8F991D5764C6ULL, 0x429B0BB630357E99ULL, 0x05D20C27C7520D4AULL, 0x642323A8BFCD8D5CULL, 
            0x548988D31225DE43ULL, 0xDFDAB8B9724FDA1EULL, 0xF058128FAF093149ULL, 0xD99E55D76C0BE758ULL, 
            0x7968DF11EA98DD66ULL, 0xC3F86758F862DD05ULL, 0x4A6957356D38E2C9ULL, 0xBC6FB9D69DAAD6BAULL, 
            0x52A6E67DF6813C1DULL, 0xF43EFBA150DF6F1AULL, 0xD27909B0EE7C5298ULL, 0x958CE2A2284B6F6DULL, 
            0x81CAB0B27B03B40DULL, 0x3FBCB9BA4ACB6519ULL, 0x174B670A390F06D2ULL, 0xB0DC2B13D10293C6ULL, 
            0xD67A77072C303170ULL, 0x794DAE5D985BCC0CULL, 0x63C547EB92B81687ULL, 0xB3E33BB01E0BD17DULL
        },
        {
            0x3A2E1B84626A5BBCULL, 0xBA127125CFF8A8CAULL, 0xBACE94E6AA2C1040ULL, 0xC4CB3A9D8A57159FULL, 
            0x5B2E1F74D81061D9ULL, 0xCDCACC040D60891EULL, 0x52A98E1CC0140D98ULL, 0xCD98C7A0CA531B64ULL, 
            0xC43042624D2112CCULL, 0xE36D50D153A6D6DFULL, 0x05388BB1FF479ECBULL, 0xD3B3C3E4BE7DD4C0ULL, 
            0xE0F5D5C6269CC487ULL, 0x202610E56CC40453ULL, 0xF926D1A555474AC4ULL, 0xA7069D1701B7DF19ULL, 
            0xF90067167664EE3CULL, 0x6F83340F4D50B032ULL, 0x291C6C901BE09109ULL, 0x733EAA2975501657ULL, 
            0xC81A507AF7EDE670ULL, 0x4BDDBE5F6EF65F15ULL, 0xB4EBB427A9154FC2ULL, 0x9026C0B7331C4624ULL, 
            0xEBEA2B5D40B524A7ULL, 0x9C655DC1B7341395ULL, 0xBDE734E36AEC8AA7ULL, 0xCCD6EC9741888F87ULL, 
            0xADCA38F177E5288AULL, 0x081C3FF157C2BB26ULL, 0xFAF4214093618BA5ULL, 0x570F4261A683301AULL
        },
        {
            0x27BDD985C4134FB4ULL, 0xBAC165C9F34D01F1ULL, 0x9C31204A5E579610ULL, 0x95BABEE7BE47A274ULL, 
            0x88BD76211004D851ULL, 0x93D88A50FFCC93C8ULL, 0x3C587A9B2CB25B91ULL, 0x55CE9ED648C1B714ULL, 
            0x23042E1B5C9F4315ULL, 0x8B897928EAD9BB71ULL, 0x120188EF2D42EA06ULL, 0x908B1A9A69732EB4ULL, 
            0x1CE1B3EE354844EEULL, 0x302C8B2719C2A42CULL, 0x3B4695BB512D4F1EULL, 0x50B8E912399ED220ULL, 
            0xA139BF5D7D7B2E3CULL, 0x023B2C5F2373FCE5ULL, 0x52396D8664D4AAC2ULL, 0xC18A3189E56F67E1ULL, 
            0x542F1867550399DDULL, 0xC596D41E05F24744ULL, 0xEF981D0E3ACB7FE7ULL, 0xD48592FD00F16D3FULL, 
            0x1D0FAC14836A5DBBULL, 0xD8AC2465029E6232ULL, 0xE45598FBE8963510ULL, 0x82BEDA9DE5F60BF1ULL, 
            0x1D2F0A97AA305353ULL, 0x146F7D8B3B449A7AULL, 0x0997E0C4CBF88C2EULL, 0x160222F6C72699E4ULL
        },
        {
            0x289DBBFC4C40D87EULL, 0x850CCA1B7DCAD180ULL, 0x80BA348256F396E5ULL, 0x73252B49FDDB87BFULL, 
            0xF67FF9E040F2DAD9ULL, 0x6E096AFDCD32B4ECULL, 0xE468C5A19EF08859ULL, 0x45133020C4B63391ULL, 
            0x8694E019D264288DULL, 0xB1B2E1450C630187ULL, 0x8C82AF884091C12FULL, 0x974AF89DD706EC72ULL, 
            0xE74A3FFC66DD6108ULL, 0x09DB86E690114105ULL, 0xD6C6B4E2F3036D3EULL, 0xFFAC82700B8026DBULL, 
            0xBBC984F75C838F4DULL, 0x4454991292626D8CULL, 0x5B7F334674DA1CFAULL, 0x52754B410F44C52EULL, 
            0xAD3BA88AA70DD9C0ULL, 0xA49A090AF246FF9BULL, 0x47B56FB5150E63AFULL, 0x2BAD58E3FCB999AEULL, 
            0xC3A2761DD3965592ULL, 0x8E40318539FD21C9ULL, 0x29FAB2250277F6FBULL, 0x9EA77F7BE5DF433AULL, 
            0x7A3139305349C91EULL, 0x3EF0BFF71F43F9CEULL, 0xE4ED1EFD4C81C0DAULL, 0x416EC144BED184D1ULL
        },
        {
            0xDC14EFA0BFB501DDULL, 0xD910151060C0CD09ULL, 0x8B19911F3E2390E5ULL, 0x5DDF6F42BB47478DULL, 
            0x39349FE2DA27F024ULL, 0xF822AB7FA3F944B4ULL, 0x194C208EDC38DD76ULL, 0xD0A16EA5886E5232ULL, 
            0x7A2060025BE78AF1ULL, 0x146C7D997357AE03ULL, 0x7CB90686B03C4168ULL, 0xE2AF39598493BBF6ULL, 
            0x22847EE7D709BC9EULL, 0xB435C4C7558FE5A4ULL, 0xC8180BB11E32B9F2ULL, 0x2F0FCB18DF57975FULL, 
            0xB1188AC4553E1B00ULL, 0xAC7167C65D48FBA5ULL, 0x34817BB04DF38598ULL, 0xD2D095C3522D1024ULL, 
            0xD2EAD68874EB292DULL, 0x82A630E0A90E3DE9ULL, 0x69648CEF99E8CE24ULL, 0xAFEEF3A5B2C1823AULL, 
            0x6CFEC8CD3804EBE3ULL, 0xD19105A3D4CD7361ULL, 0xB584495FDB044E79ULL, 0xE97ABAF4BFB93EDCULL, 
            0x579994C659CBF253ULL, 0xFF7FEF63FF49B4F1ULL, 0x93E92C41B3DB67DFULL, 0x91C12FB184550BF8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseCConstants = {
    0x42484CBF39AD8E4FULL,
    0xEA749675B95921A5ULL,
    0x7FAAA0631FBBC970ULL,
    0x42484CBF39AD8E4FULL,
    0xEA749675B95921A5ULL,
    0x7FAAA0631FBBC970ULL,
    0x3EF533FBD3A214B5ULL,
    0xB042E29A469B153EULL,
    0x01,
    0x78,
    0x0B,
    0xD5,
    0x39,
    0xEE,
    0x6C,
    0x78
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseDSalts = {
    {
        {
            0xE81D14EF3D56BD97ULL, 0x81404CCCFA8CDADAULL, 0x7F0D11644DB22D53ULL, 0x97CB4BF706BBE48BULL, 
            0x5A36A1E1D7753C05ULL, 0x25E7D41D5446CEEEULL, 0x002248EEDA8B7B77ULL, 0xD07EE2635AF8247EULL, 
            0x8F6FB9FC980B2454ULL, 0x2F745B038E906B08ULL, 0x03E50E0C66CE211AULL, 0x2DAED135F128525DULL, 
            0xECEA5C1D099E1539ULL, 0x0DB4D66C160B40C7ULL, 0xD9D9B37FEC37EB32ULL, 0xB4192CE815092A66ULL, 
            0x210D16216F7DF026ULL, 0x21D72E687EA63912ULL, 0xB5F8430BF22C63F1ULL, 0xFC07416B5B3C4C49ULL, 
            0x5FCE0852F96B6F05ULL, 0xC84388917D20EC9BULL, 0x735A86AACFDB6850ULL, 0x1F5CCE103C82EF89ULL, 
            0x9632D8F2F5F83BF3ULL, 0x1D4C5C2C09457AC9ULL, 0xFF617FC1C2819C89ULL, 0xBDAFD97E9AD8BEBAULL, 
            0x1DC3106256FDA918ULL, 0x1AA68B6B209E855BULL, 0xCEF8085267A77472ULL, 0x0C021FA3A18D842BULL
        },
        {
            0x45D51EFE2BA2BDF5ULL, 0xFFC1E1FB24C35084ULL, 0xA9A53C79E7663771ULL, 0x03141AA3DB0DF9D0ULL, 
            0xA257E9FA0C97B0F7ULL, 0xFC442BACAA20F01BULL, 0xB71CB05A3DFA7C52ULL, 0xAAC9B67F48835DEBULL, 
            0xFEA42FB10A5805B1ULL, 0x365F36FEDCFD5B9DULL, 0xE86FDCFB6EE56FFDULL, 0x495C8CCA15EC9B9DULL, 
            0xA2FE12FD7832A1E7ULL, 0x910DB1A9590226C0ULL, 0xE522B533E399B88EULL, 0x299CB3A68AA8149CULL, 
            0x4E4A994D7225EBEFULL, 0x53DEA4D41C7CCF8FULL, 0x41DBBADD99AF2215ULL, 0x764AB761C053FE2BULL, 
            0xF1A23630FCD407C8ULL, 0x41B7D9F810C855ECULL, 0x942E905424CD03BBULL, 0x1E5328C931DC444BULL, 
            0x2D68E0AC344DB1F3ULL, 0x64805D0E28AF9E57ULL, 0x4AB95C713E0B44BEULL, 0xE32D3C7989A2E541ULL, 
            0xD2F95824FA3FD892ULL, 0xD096B29B647C34C7ULL, 0x7314F5EFA24C6D64ULL, 0xF7CC8AB65C0EB9FCULL
        },
        {
            0xBC976CD54FF4743EULL, 0xEE46E3F3EBCD6CD5ULL, 0x86AB069BD6104CD4ULL, 0x3C31075D556D4BF8ULL, 
            0x79F18CDE3718D9A7ULL, 0x16ACD31D0AEB621CULL, 0xBF388CA00D57DD20ULL, 0x3708E3DF73413839ULL, 
            0xBAB0B8934603613CULL, 0x9F27691316D74756ULL, 0x6968141362DFF41BULL, 0x4C7A6A8B92B158A6ULL, 
            0x76991A7395AA9774ULL, 0x6F94A0D671B2E019ULL, 0x33B0E4283912F932ULL, 0x6A2DFD0A2B2B4E98ULL, 
            0xB093E515EA6F0725ULL, 0xC1B9EA653961202AULL, 0x6E887519C6901B4DULL, 0x504E08F0CF819814ULL, 
            0xE8048E127653CD46ULL, 0xCCB67D8C43E1C685ULL, 0x50F1DD187050555FULL, 0xF01F9BFEEA52E9DBULL, 
            0xE097F8444893F84FULL, 0x55D8727758F16DC3ULL, 0xABD591E1C7E283E0ULL, 0x60882DE9B95CD88DULL, 
            0xAE6022F7700E4D90ULL, 0x7CD975E6EA564D43ULL, 0x091B6214E72F4575ULL, 0xC973305A3B1AF314ULL
        },
        {
            0x8E99C6E73799CEE9ULL, 0xCA36BFABAC163617ULL, 0x8F8D0F5BF26B7216ULL, 0x82C2AD7619F81EF8ULL, 
            0x639165FE5D52C292ULL, 0xFDE48B803F587AAEULL, 0x341BCCE8D8B6036CULL, 0x423CF5204A376AE3ULL, 
            0xE58EE0B0ADB65E4AULL, 0x8B7E12E4E7FED8ACULL, 0x496BA0CC25CF4DBAULL, 0x74563B01A3167A97ULL, 
            0x64C43011A7E26B46ULL, 0x850E8E92397561FBULL, 0x841C90C603583ED5ULL, 0x6765E95B9A2AE861ULL, 
            0x9FC2C6BCC5AA4E40ULL, 0x9EF468A4AFBB0895ULL, 0xB04EF8301F64F942ULL, 0xD1DAC5BA2B769618ULL, 
            0x6D84226AD22F2FE6ULL, 0x6CAB9F1CED39CF72ULL, 0xF44E392DDAB964F4ULL, 0x03A8D3DFE4FD7A0EULL, 
            0x60362ADD523733A1ULL, 0xF41A961188F5C005ULL, 0x1E98D318466A5B9FULL, 0xFCC1C86943C8A0D6ULL, 
            0xFE6D40C1BA8A6C3EULL, 0x5360A3ABE8A6C10BULL, 0xE7FFDE1576617096ULL, 0x1D0DADDB28A46250ULL
        },
        {
            0xF95CEDFE81D7DE0AULL, 0xC94772A8E1F00701ULL, 0x26B70CDD8B4BDDA8ULL, 0x0111F1ABE362E670ULL, 
            0xD49EC8C9A26763AEULL, 0x6DFEE9CFF5EBB4C3ULL, 0x925769F96933776AULL, 0x007A0E04E428EA34ULL, 
            0xFB6A0A35061B9209ULL, 0x43D5317451C698F9ULL, 0xBFDC7680B3E8858EULL, 0x6114C783C9BB449FULL, 
            0x1CFD57E24145E6C5ULL, 0xFC76819686FC5280ULL, 0xC4916CED06C8977AULL, 0x5FEE9D94E628F7A0ULL, 
            0xD6AB1A8C0835CA80ULL, 0x0B284CF521FE340EULL, 0x07026FB22BA72762ULL, 0x046A1648AB5FE03AULL, 
            0xEBC5C93FBF193254ULL, 0xFBC8DA66232C490BULL, 0xFA8F10B53B8C2996ULL, 0x02FAB61B06A2120BULL, 
            0xBCEA941547CD4954ULL, 0xBC0CEEA76C05EFCFULL, 0x10AA7C859A3AFA8BULL, 0x6A7E53392790E471ULL, 
            0x0EFB0AC99A7BFA57ULL, 0xD8E20C163580D788ULL, 0x22DD63861EB75A28ULL, 0xC0E1F0335A43F6A0ULL
        },
        {
            0xC55BD222A0675F6BULL, 0xFD5CB3121B027F6EULL, 0x6E68EAFB89CD791EULL, 0xF87F672E739C6815ULL, 
            0x15718846B1138043ULL, 0x130D99D546558817ULL, 0xDC08E3442EF627B4ULL, 0x270BE24E67ADFE48ULL, 
            0x5E6BB6258A18877DULL, 0xB22AF0A20AF3C0AAULL, 0x14266E15A17C9F03ULL, 0x00E82C335A7627F8ULL, 
            0xD3738ED63E75BF9CULL, 0x2B2A2251D3C32888ULL, 0xDE691C7CE8EEBB8EULL, 0x5DB00E1B55EC1642ULL, 
            0xBA2397B0CB606B8AULL, 0x67551A740CF6BC54ULL, 0xF56F5A52FED3C30EULL, 0xEE3C3A9FDAF6E213ULL, 
            0x871D100BD9981D4AULL, 0xD3CB9D74634A1573ULL, 0x6300692429FFA30FULL, 0xF1D04D9542B89B39ULL, 
            0x1F53D46F806E39C2ULL, 0x321D85C32D61F169ULL, 0xDC5DA00E82110BD9ULL, 0x52B0F8514D690DD2ULL, 
            0x756D4E6CE2CFD507ULL, 0xE52C72A83F10739DULL, 0x9F9C93BDA65454D8ULL, 0xC3077200CCC330FFULL
        }
    },
    {
        {
            0x095FA471C6AF2929ULL, 0x092A0923B2F959AFULL, 0xAD9F585C55A32797ULL, 0x8893EC3D58928C3BULL, 
            0x2BA0E6D6CC06339BULL, 0x0ED1C3528CFBF9B4ULL, 0x3A945C279D121031ULL, 0xDD2713C0ACD27432ULL, 
            0x65C622CF2A91E035ULL, 0x3BC0F3931C047E56ULL, 0x4FF2BD295044D18BULL, 0x2FE625FA3D849717ULL, 
            0xA65D3376354FAC61ULL, 0x29FAE0CC88D53F88ULL, 0x85559F33600CCBC8ULL, 0x349753362107E3CEULL, 
            0x8D2A540680F81EABULL, 0xDDB7C389BE061E9DULL, 0x07C2A875067B7E38ULL, 0x4BD6C0418FAF043FULL, 
            0xE9876410B7CF8C48ULL, 0xACE7729BAD520B54ULL, 0xD108415BA2DFD344ULL, 0xF2C04171BB5E1181ULL, 
            0x1FA8135FC95B5550ULL, 0x6FCD47E0FFD77F30ULL, 0xA42B2E44C1B588CDULL, 0xC0DAD71C36433E9BULL, 
            0xE4DCBE68DF92E601ULL, 0x5F7435E6F60B9DEAULL, 0x917ABDEB679275D4ULL, 0xC21AE8AF339B9A14ULL
        },
        {
            0x4B8CE3D3EEB5AB0BULL, 0x25FE284F7FF8DF64ULL, 0x7420FDE376F4BC44ULL, 0xB2A961908D7A585AULL, 
            0x30ADE185B2A329ABULL, 0xA98CBC11AD2F3AE0ULL, 0x4B88536DC72C0329ULL, 0x6BE636E8D084FF34ULL, 
            0xB268FABFEFCAB376ULL, 0xDFF0C26C7982BEA2ULL, 0x68911867120EDE13ULL, 0x8A3B78E9CA6FF7F9ULL, 
            0x6E55D9140A9523B0ULL, 0x1DF66856656B5D55ULL, 0x0C949E1D0BE433BCULL, 0x5E349FD49F012F06ULL, 
            0x3BBF43164E70281FULL, 0xBBFC4FCF0286EABDULL, 0xC830BBCB34FA4D09ULL, 0xE514729F4D85A564ULL, 
            0x5EB4E071394ED5AAULL, 0x4CF50A5326B10060ULL, 0x2254265C329C2801ULL, 0xCD69C62691A5EC8AULL, 
            0x9C7C25548B6BCDD5ULL, 0xB8821E7A2EBB5724ULL, 0x5A6EA856870D06BEULL, 0x9D417B1FAE048B78ULL, 
            0xB127E0DA9126B669ULL, 0x34CBDABA9F45D103ULL, 0x95ED585D05A6FE9DULL, 0x891608112E262700ULL
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
        },
        {
            0x46ADE14EAA61F158ULL, 0x7FF9D4E07D22B1AEULL, 0xCF917F61F82C8122ULL, 0x7F320AC480FD118BULL, 
            0x8B1082480F740257ULL, 0x0A5245F7E02B71F2ULL, 0x6956B3B4FD165518ULL, 0xC12F335E3A365116ULL, 
            0xA3FAD58E98E6E24DULL, 0x2775204C65736E0EULL, 0x4501E9F16E35A246ULL, 0xF504850FDEB07A60ULL, 
            0x5A36508DA6DD5994ULL, 0x886C0D4A141EEDD1ULL, 0x84D199FC993E5DF8ULL, 0xA1213CDB02D2D363ULL, 
            0x7E69C9C8E18D96C0ULL, 0x50541BC37BB1B921ULL, 0x81C65377E3D34ADDULL, 0xC15BA0FB2D5E4102ULL, 
            0xFF55D33F79180D78ULL, 0xCB7EA7CD10D8F868ULL, 0xA6C6C8E7431EFEA0ULL, 0x31F72BEA35703112ULL, 
            0x657DDDC9D665EFA2ULL, 0x477296E58BE72484ULL, 0x5FFDD7254549E116ULL, 0xC40CC2B8289CD844ULL, 
            0x6281F16719F3050CULL, 0x138BA0F581287D55ULL, 0x71424F8A97AD6575ULL, 0x4954B54687135A9CULL
        },
        {
            0xE878FEC962AF7864ULL, 0x2989F8B0741322FFULL, 0xD45B5980B599634CULL, 0xD9505A6B4B930958ULL, 
            0xD9AF6315AF0138DAULL, 0x5E9AD34435F5523BULL, 0x65ECBC0118C4A0FFULL, 0x91C293BE8775621AULL, 
            0xF484815B694DE90DULL, 0xBB76D83D08962768ULL, 0xA7FC47F00911F394ULL, 0x55E89AE6A90ADE97ULL, 
            0xFD1C3E980E61A7A3ULL, 0xE86ACE14C2EEE375ULL, 0x57381F937874908FULL, 0xBA01BAC755F6EA21ULL, 
            0x0227B6DF1A2F920DULL, 0x99885651466B8F27ULL, 0x2CA1665811D7315BULL, 0x84F6A9C20C6517CBULL, 
            0x44356A8792233F39ULL, 0xC2C4887489F61700ULL, 0xE16E033B885A634AULL, 0xF23FF3FD73CB6BC4ULL, 
            0x7E57D9F3F47651DAULL, 0x3D6200B0FAB79A0EULL, 0x27212BD3A5846E26ULL, 0xFC24E257F5236951ULL, 
            0x8D547C35AC672824ULL, 0xC4974C6102816AAFULL, 0xC7055EDA69179721ULL, 0x1804F109FDBCCBE4ULL
        },
        {
            0x94E74F95EE5018ADULL, 0x398C54BF09A2D16BULL, 0xF9C7CCC46A004021ULL, 0x8670016F10F0D3BDULL, 
            0x1812FF4810BF069AULL, 0x4A22C8BB9C0DA490ULL, 0x2AF02B66C52263EFULL, 0x0100E17F05FE9B98ULL, 
            0x7B087EC7DDFCA359ULL, 0x7BFD669A4DE7DF6BULL, 0xB252AB5B8772035BULL, 0x072C1AC6225BB156ULL, 
            0xC82F45D4B1A35E11ULL, 0x850CF6D3A62F62ACULL, 0x19EDD0B11B800094ULL, 0x8FC0CF11F09BE042ULL, 
            0x10C3D1562C6F5A61ULL, 0xF2EE7BAB2911F21FULL, 0xD798E19DECF83DA1ULL, 0xC6523574FC6BCEE8ULL, 
            0x3D1BF39FEBA6DA23ULL, 0xB374B8E6F56C1C22ULL, 0x7A476E6A96BB147FULL, 0xAEFE0FFAF0504D36ULL, 
            0x5EDFACF2AB22F1BEULL, 0xCC7E42B20067CBD4ULL, 0x72EC63CF26B2592CULL, 0xC430E87ABA36EB57ULL, 
            0x0890CAE6DD261611ULL, 0xF0309EE9A7AFE891ULL, 0xCC1E01A9964D8422ULL, 0xBD795EF105952C13ULL
        }
    },
    {
        {
            0xA4CF3C5BD49843D6ULL, 0x64CC56CBDECF2AE6ULL, 0xCF0C9A833D6A3977ULL, 0x9B443FA94C17D34AULL, 
            0x878B622638F82B24ULL, 0x7FC3FA9ED683EBAFULL, 0x35E5ABF6C7CB595BULL, 0x3F0BBFEF3A36F999ULL, 
            0xE9C5A1BC087369BFULL, 0x800A4CFFD18AC430ULL, 0x09B5B189C081236EULL, 0xF29015FF08004A2DULL, 
            0xE0D9987C2C20AB5EULL, 0x4F54C2B37491A006ULL, 0xD5FAB90728ED1705ULL, 0x217C1BE2038E6103ULL, 
            0x187A962ACE9A973FULL, 0x984605E82D953FABULL, 0x9151998187F2D865ULL, 0xAD4AEED435EE3A9AULL, 
            0x02C991539DE642DEULL, 0xCA7A6C2B2B9E9037ULL, 0xC2058EAA7C6038D0ULL, 0xBD68AC01028DF511ULL, 
            0x3CE691A4EE6FAFA1ULL, 0x68703DDC99E53CE7ULL, 0x2B8A65A9F8D8B9C1ULL, 0xC3F70F3F9DA6A584ULL, 
            0xA942504D2D6353B3ULL, 0x00D4E8BB6D711D9DULL, 0x4729357E6A1DCD9EULL, 0x2E5FE994E7DC87A2ULL
        },
        {
            0x7190BF6E66FB0E73ULL, 0x8F56A60CC0637FA1ULL, 0x9FF4F870BDFEDBE1ULL, 0xD718C89CBCAA643EULL, 
            0x5D8253E9A2C929A4ULL, 0x580EF47359C72402ULL, 0x63D295CA40F3D9B1ULL, 0xF19DE9F007E4F4C6ULL, 
            0x44CF22CEFAB90509ULL, 0xAC60486B8AB99E32ULL, 0x006C5A044ECB2F0DULL, 0x338A06E303FA8AB1ULL, 
            0x4BFADD1DF0AD925EULL, 0x48494F00F90836BCULL, 0x470DDAEB401D3FCEULL, 0xAEA6928BA6331D77ULL, 
            0xDA4ACDC73A45680DULL, 0x1B9F3201FA3F455CULL, 0x0C0CE4EA1C503AF0ULL, 0xEA5B9F58E5ECB38FULL, 
            0x8E1FF80712971ED7ULL, 0xA6F6FC37BBC3001BULL, 0x0828D2CD5CFBCE22ULL, 0xA91210CC5280A996ULL, 
            0xE6D32397E71FAED0ULL, 0x5CF269A226930DC0ULL, 0x81385689C487D059ULL, 0x35632DE9DDA91D48ULL, 
            0xB3A76E3EB28EEEF7ULL, 0xBA205E205A0F408AULL, 0x9D2FF78DD532EB25ULL, 0xA473EC470996D9E9ULL
        },
        {
            0x08FE05504CD4C1FAULL, 0xB95B105529756721ULL, 0x5D4E454B059F0859ULL, 0xBA474D5702432FF8ULL, 
            0x5D8A7559197910AAULL, 0xBDC7D0C747612FCEULL, 0xDFAA1C615BC01168ULL, 0x6BFDE3E362A6BD4EULL, 
            0x3E4E3096663318B6ULL, 0x8F5282D92D7B9585ULL, 0x021B07E818CEC33CULL, 0xD4CB5889DE1CEC69ULL, 
            0xEC1D28CCEC3CC65FULL, 0x8A5B28F644772A93ULL, 0x32EA24C016B48F72ULL, 0x82B5A5CEA59B99E4ULL, 
            0x65B922013D2EDFC7ULL, 0x226FE47522454C21ULL, 0xED5EE78FC365C339ULL, 0xA107E75EE606EDDBULL, 
            0x726F6203BDC913ECULL, 0x3F65914AEC759F0FULL, 0xCC41D8F8AA09E48AULL, 0x4F874DA5E92DE628ULL, 
            0x6066D0CBA21826C2ULL, 0x2F3029CDFC5E9EE1ULL, 0x7537F0876B9487A6ULL, 0x8CA60D334D43E0BBULL, 
            0x74CC45A5C58D3FB9ULL, 0xD0DE719E28B9AF1CULL, 0x1C8A4A957FE83D60ULL, 0x88844E77B8EA75C2ULL
        },
        {
            0x934B53C48F4C3459ULL, 0xA5AEB7307B8B99F4ULL, 0xB1D9BFCD60EEF218ULL, 0xC3123FC173DD8F27ULL, 
            0x1CB62A7B186B9A24ULL, 0x10E29F34F03F24F2ULL, 0xE2120430E60D834DULL, 0xDC0F0E9462EA7AF1ULL, 
            0x1F5DECFB90D73DA5ULL, 0xB21B63FA6E7A0C17ULL, 0xD382D6835D25418DULL, 0xAC67A98F6FBCAEC8ULL, 
            0x201EBAB19EE758EAULL, 0x30807B840F2F1D89ULL, 0x334857D6DA5C4193ULL, 0x4FD57998301AD914ULL, 
            0x676BD5B0F352E2D2ULL, 0x3F71E3FDC9CFF9D4ULL, 0xC0936D3C288D38F7ULL, 0x4CF71185C0525754ULL, 
            0x1F3E73830CF3DE16ULL, 0xB161A9AD7FA22CB9ULL, 0x82C1E832C8D0DD18ULL, 0x0BA6A9BB13BDAB88ULL, 
            0x7291366DD8A0319BULL, 0x805BA5D67B76552CULL, 0x6F74A1911A0758C2ULL, 0x106F72D91DF96A91ULL, 
            0xE4167C8AE7E6F912ULL, 0x5D1B79CC3CEC9119ULL, 0x5F7C3128C5504D46ULL, 0xC826694B92D0CDFAULL
        },
        {
            0x96F256A8AC3D7AA2ULL, 0xF56F64154238E689ULL, 0x1A960EFCB34E91D8ULL, 0x72DD4F43F9C4C7CBULL, 
            0x729E72EF1E048E89ULL, 0x29503E7713540BC9ULL, 0x6CC09CD58A766DC9ULL, 0x1BFE376A157B890BULL, 
            0x5EA1EAB6C80B1870ULL, 0x85C81EE30BCF51F8ULL, 0x367105BD03891EFBULL, 0xBDE230E277D13635ULL, 
            0xBA22D99CF0D92B74ULL, 0xFCD5B1BB8DDF5E0EULL, 0x26ECD5EB2237A826ULL, 0xFE204F5351370DB9ULL, 
            0xB4A62E4E0740D35AULL, 0xECE5F460C9E0E743ULL, 0xA99F3DB0D45D9FB9ULL, 0xDA62E58FE5B464B4ULL, 
            0xEA64A3D48FD6CD52ULL, 0xB01638FBC618B862ULL, 0xB553FCFE2D21D472ULL, 0x55A96C143510D128ULL, 
            0x167CDA8ACDC29F37ULL, 0xD407952F5189FE16ULL, 0xBFE6E76F55E1249FULL, 0x00965D7084A4CB6BULL, 
            0x41DE20EC49B9FA14ULL, 0x91C078A1D636F768ULL, 0xAD0C20F0A7C61154ULL, 0xD1A81D6A5D35BE7DULL
        },
        {
            0xF504104A178D0753ULL, 0x53A8C299453C7355ULL, 0x2D5771F95B32D30BULL, 0x63B8CD4DF66CACC5ULL, 
            0x36EC659E9DF1CCACULL, 0x3035150AA92FA1D2ULL, 0xAC8FCCA87D53785CULL, 0xC2E6669C58FFEB8EULL, 
            0x889791C18F1071D5ULL, 0x120F6F6E91FF1FB9ULL, 0xCC93C67270CB9241ULL, 0x7CB3A441D3EC288EULL, 
            0x7EC56482FBA78CABULL, 0xA85A413FBE93F5EAULL, 0x3FEF623ACB759203ULL, 0x246023F5E81BA023ULL, 
            0xE86BE992BC5221DBULL, 0x5225979348F7C6FDULL, 0x892AAA842533C329ULL, 0x6098E95361804968ULL, 
            0x90937DFA95F242DBULL, 0x99B04D28EC3D6F9DULL, 0x3367F9AF6BA980DBULL, 0x2F322096B51724DEULL, 
            0x72128E548E78080FULL, 0x317522E697A85152ULL, 0xE7BDD7BD03B3AD10ULL, 0x00D3BC7F6C1AB02EULL, 
            0x7A0C627524C5A8A0ULL, 0x9BAE652CB0FF6187ULL, 0xD6D6A0749A3B91D8ULL, 0x209C31B61EBBCE25ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseDConstants = {
    0x40F458B7C13E321BULL,
    0x1F012AFB4BED45EDULL,
    0x2E81A7075B7A3D9BULL,
    0x40F458B7C13E321BULL,
    0x1F012AFB4BED45EDULL,
    0x2E81A7075B7A3D9BULL,
    0xDD998AF64731D211ULL,
    0x9DC0B354BEBFA7AAULL,
    0x7B,
    0x30,
    0x32,
    0x55,
    0xBF,
    0x30,
    0x3C,
    0xB9
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseESalts = {
    {
        {
            0xE7120959587AA13FULL, 0xE960E7D44A20344FULL, 0x1423E80CFB61F36EULL, 0x6E436D340E9FABD0ULL, 
            0xD01C2802091FCACDULL, 0xC8134FA9B933FE2FULL, 0x5F78E942BCF4CE7AULL, 0x3FBF73BAFE3BC242ULL, 
            0x0D11B732E04E035BULL, 0xDBD00B06D12CCDFEULL, 0xB9E6B85932957920ULL, 0x3AF596FAAFC86F51ULL, 
            0x83FE3155ACCB2B42ULL, 0x642B286515B9AE28ULL, 0xEB54B9C46A7872DAULL, 0x1F1CE9ADA7CA3FC5ULL, 
            0xB7F62591B9EF70A2ULL, 0x6DA8FEC9E60F8955ULL, 0x363560116F1970E9ULL, 0x90575D5FC49E28DFULL, 
            0x652383FCDC71C9A9ULL, 0xE89CBE5FAA3E1794ULL, 0xBE216C96BE454471ULL, 0xC9C91EBA5D0C6A94ULL, 
            0x19A7B6E86000EB47ULL, 0x57DB2E8FCFBABB1DULL, 0xA3D04641CD58433AULL, 0x7DD5A14BC85BB38CULL, 
            0x8F805CEA6EF525E9ULL, 0x47C8E807311BF4E7ULL, 0x2CDA9BAA8045E429ULL, 0x4964B19C25ECA69FULL
        },
        {
            0x4D6B748456599576ULL, 0x0CD8E93C17DB89F3ULL, 0x9B4CDD7BC588035AULL, 0xA6DCEDC3E7C415DCULL, 
            0x9C4C7C0700B777E4ULL, 0xFCC6B26400511687ULL, 0xA40C7CAE2AEDF847ULL, 0xC5FB73A791AC2B83ULL, 
            0xC31F168F51481462ULL, 0x01FE5A0254D2AA71ULL, 0x97C043841140C53AULL, 0x2B92A41CCE817C7BULL, 
            0xF7F531B43D04D968ULL, 0x56ABD698F19C7DF8ULL, 0x8B5596109910E2B5ULL, 0xE9211452EEE240B4ULL, 
            0x1EA188AB7DF378A6ULL, 0x3B65CC966AE56878ULL, 0x48E42E0E71D51DBBULL, 0x76D21B480F735F0CULL, 
            0xFADEC5FFE5C7CCA9ULL, 0xB9EFD76DF189BA27ULL, 0x1D64466678DF31DBULL, 0x33B21D2E9D644D66ULL, 
            0x84C5F174BBA0CE09ULL, 0x3F96FB0E14AC5281ULL, 0x96F8B139E95F490CULL, 0x5C49036FF8AF5EDDULL, 
            0x139ECE7D56412B8FULL, 0x80A7CC91F6FDD287ULL, 0x905B6D43371F3492ULL, 0xE708A88ED4DE1F06ULL
        },
        {
            0xB0DBC0A8DACCD1A8ULL, 0xC1BA36D4A27B510DULL, 0x609D412419D4B668ULL, 0x98739B9373947BB8ULL, 
            0xC916100A4E2D3465ULL, 0xD4ACEA87F13099F5ULL, 0xB3ECD73D908DB5AFULL, 0x22364582CED155A8ULL, 
            0x76E9BFFAFF80FC0DULL, 0x0A2DCA62EACA2151ULL, 0x6577B062E2558886ULL, 0x65353F4174E7F781ULL, 
            0x9C385116DF40D028ULL, 0x2A387AE258CEEE36ULL, 0x96C15E6042F7CA3BULL, 0xD99F91021D8591ACULL, 
            0x71C1125FF731E516ULL, 0x490E8ED95DA47FA8ULL, 0xB84A2A62309C99A7ULL, 0xA0F80E2EF913B301ULL, 
            0xBC01C401AD63B24BULL, 0x8BA97D48AD5C60C8ULL, 0xEC3F7FF589A8CA3DULL, 0x9AE154ABD31DB492ULL, 
            0x0B39C236CB8F2A38ULL, 0x3B693E354C4B2DA0ULL, 0x9473B9896D778B3FULL, 0x6D540E37257DBF79ULL, 
            0x528294ED8FDF045BULL, 0xD7A01928AD4AB064ULL, 0xB33E137B9E59F8EDULL, 0xC85A2B3B7D8647A0ULL
        },
        {
            0x6795C31D98C96D28ULL, 0x82632DE4959028A6ULL, 0x7060B41A0C6C9B85ULL, 0xBD50B4E38CCD421CULL, 
            0xF0D0F0AC76D3C2F8ULL, 0x6806EC5553997FB2ULL, 0xDBB9D89997ED1890ULL, 0x73173871F490FF25ULL, 
            0x27133C2834D2A2E1ULL, 0xBFDD7EA769C5AD4EULL, 0xF150D5E8BB0E84F1ULL, 0x1CD0E980E4B86E1AULL, 
            0x198A283792CA2258ULL, 0xC0FF52960BE4B624ULL, 0x0CA89416AE106FC9ULL, 0x61CDDF244E48A486ULL, 
            0xF8D4F646FB66CB9EULL, 0xA2BDAF6824086885ULL, 0x1DC1AE397D9C0060ULL, 0x2520033C8C456E42ULL, 
            0x9F0FA67AFD6F90AAULL, 0x04AB14DD4D500274ULL, 0x3E28A722593361FFULL, 0xBD9AE0813B3DB316ULL, 
            0x2DEFF6E6D4D92087ULL, 0x6FE26A470B0A6586ULL, 0x5E2362BAFAE33A03ULL, 0x948402F6E0ADB20AULL, 
            0xE1D6F45487707CEDULL, 0x5FAE9F52B281C9ABULL, 0xC1C19AD40871078EULL, 0x5FBE979269F2431CULL
        },
        {
            0x1B059E7F1FAE03A4ULL, 0xE12782499026595AULL, 0xC2688092E0B65BCEULL, 0x20313E3A59433EC9ULL, 
            0xA75A1517CACC967FULL, 0xD22B60D407C00261ULL, 0xE50935BB9865AB66ULL, 0x5129D2D6A193127FULL, 
            0x34D6CFE8CEA3A886ULL, 0x192FD55BA1AB2CBFULL, 0x607901AF4EDB6F0CULL, 0xDC272AAAD35CC9C0ULL, 
            0x86B05FF680C737EEULL, 0x5937756547593C3EULL, 0x4A331DCAEFA7419FULL, 0x1A8FD5C6853DF282ULL, 
            0x8979767758646A97ULL, 0x030A08E1703CA79AULL, 0x1EDC90D74AF57903ULL, 0x1C92B8F6471EB011ULL, 
            0xBBB1F32E2D2E044DULL, 0xE1041870D3369773ULL, 0x7D5122D25D4E5DC0ULL, 0x046B17424F621BBDULL, 
            0x9DF513CE0099B1C2ULL, 0x7309702F5D7C4FBBULL, 0x145E5E4D37D6DE85ULL, 0xB1672092BE307705ULL, 
            0xB9061818B5FB8E70ULL, 0x82A001D72EEF21FDULL, 0x083E89F9DFB91364ULL, 0x9AC8FCED9775BB0CULL
        },
        {
            0x45FC0D2096136A44ULL, 0x865900C63384BFF5ULL, 0x6465521736CB7723ULL, 0x8E4123081B53079EULL, 
            0xF704B061474EFDFDULL, 0x68860866A0E473A1ULL, 0x026D2D7B8CA41DC0ULL, 0xD8E1DCD7AFC41FA3ULL, 
            0x1369D91A13A7E8C5ULL, 0xF7A8200D02AC4E89ULL, 0x2A80BE930F4D22EBULL, 0x5787E6C8E410A0A1ULL, 
            0x20A577C7AE1211F6ULL, 0x871181D3758538B0ULL, 0xE3EFF7911B555EF8ULL, 0xAB79E29BBDBF7948ULL, 
            0x73991C24BFF3D5B1ULL, 0x230DEC8D53501386ULL, 0x5AB46EC71DCBC48FULL, 0x602155E4A7A2A4AEULL, 
            0x84B8745AD5461470ULL, 0x26C3215E689721D4ULL, 0xE7C919A7EB3E4DFBULL, 0x3DE80429C05DB32DULL, 
            0x7DCF515DACCB57F8ULL, 0xE1B1A719AB9FC6BBULL, 0x5B715B6058A6252BULL, 0x40ADA4E29D27F3B8ULL, 
            0x43EAB2580A7D911DULL, 0xB1D3AAA806A3DD49ULL, 0xF74C5059800D0C71ULL, 0xE9ECA84126820B50ULL
        }
    },
    {
        {
            0xC18EDE27407D9110ULL, 0x017FA4DD8088A1EEULL, 0xC6BCF5EE700252C0ULL, 0x396F29D7AE5FCC85ULL, 
            0xCC2C105F6D298974ULL, 0x206B6ACAAE7F7B38ULL, 0xCC4EDC2A4E50E795ULL, 0x9EF13C8330F9B6E7ULL, 
            0x7D5DDFB1C0CFB7DCULL, 0x680FDC5BC0F0BDD8ULL, 0x0A918D9CC2895084ULL, 0xB4543843CE03C177ULL, 
            0xC2F09D5AF67550C2ULL, 0xEF54821A00EFFB42ULL, 0xF4013FB7213EED9CULL, 0xE19D2E90D426A80FULL, 
            0xDDE7589823925010ULL, 0xCDAA071D58CD8FB6ULL, 0xF6CFA4141AC361C4ULL, 0xC1EFC81F8B86CAA7ULL, 
            0xB99E09B637A55324ULL, 0xA031B8F2404C09BDULL, 0xCFC07A07E16E63E6ULL, 0x3724C86A4F1A6A8AULL, 
            0xE3A4AB4B65F7D152ULL, 0xE67E9612A6A06C9BULL, 0x3127C11B7F33D67AULL, 0x9B8B35660A90BFF1ULL, 
            0xDA219C8F6C54DACBULL, 0xA8B6D984207BE95AULL, 0xEC2BBAFCBCAD050DULL, 0x54855EE12B3E9CF7ULL
        },
        {
            0x7041688A31C0913FULL, 0x0EBA055C09A6F90CULL, 0x5FD9DC10F7254791ULL, 0x4974936A265B563CULL, 
            0x012F0EE364A88453ULL, 0xC1C4C7CECF4D46D3ULL, 0x1FA9A2887067A1C6ULL, 0x440229F7745F46C3ULL, 
            0x6F6DA2FDB194C0C3ULL, 0x50ECEFF1EC6AEB06ULL, 0x41B0DEEDEA95E909ULL, 0x3AE60BC361753BCDULL, 
            0x6FFCB63C0453A489ULL, 0x26C7FBEC56106892ULL, 0x1CED43BCF24A6C44ULL, 0x2081187CDE9176B6ULL, 
            0xB68872C44F3C36A6ULL, 0xD24D9D955F92F342ULL, 0x7D1E7130B7EE6DFFULL, 0xB5D918F4DBD36FC7ULL, 
            0x2A37F2EE51921ADBULL, 0xEF930936D6CD9447ULL, 0x01680DFFA2D7E500ULL, 0x4895657A8C025A1CULL, 
            0x81BABB6E836DFDEBULL, 0xAB25E97F7B9A5C44ULL, 0x356B4CFB12CA86BCULL, 0xE5A49928DA93C3B2ULL, 
            0xD6CBED3D57A64778ULL, 0xA03F52D308223C4BULL, 0x0095EE2940C598F3ULL, 0xE86657D82E3F3AF2ULL
        },
        {
            0xE26AEFF5A194503EULL, 0x2FACCA6FA58C9A63ULL, 0x624F34AB717EB8DCULL, 0x959BB12A8ACBEBDEULL, 
            0xBCE889EAF9D4C5ACULL, 0x2613BF76CD629165ULL, 0xD148675B431CB94AULL, 0x2F21D02E1E79715AULL, 
            0xC30ECAE6D46073FBULL, 0xB17D98ACFAA8AF4AULL, 0xA96E59BA70C46531ULL, 0x7A6ABFEAA596FCF2ULL, 
            0x6BEC83D12229A13BULL, 0x202125BEB1E47396ULL, 0x41312C83FE79C19CULL, 0x4459603AEFA7EAECULL, 
            0xC9D2F22551E776ABULL, 0xBAAA261F1A363D7BULL, 0x72DD76C8CBAACDEEULL, 0xD35767EA2B047AC0ULL, 
            0xD9A51418DD449E49ULL, 0xA0904A35F1F486E5ULL, 0xC1326DEC6F7119E0ULL, 0xFD2A8E5081D22086ULL, 
            0x283AEBC01D170A88ULL, 0xA8DF28BBF04D0EA5ULL, 0x56F3B12E887B1636ULL, 0xC13DD33CA7088F83ULL, 
            0x4280E7094489E5EAULL, 0x05E9C777A294EF04ULL, 0x186E048A44FE5427ULL, 0x8F26B6C701E9387CULL
        },
        {
            0xAE04D7AFF3652D67ULL, 0xF9BB163C45795871ULL, 0xCFACF2D9A756CC5BULL, 0x99E08CCEEB545830ULL, 
            0xEDFDB096EA90886FULL, 0xAB58DA9616A4872EULL, 0x409BBE9F159034CDULL, 0xAA15833D058BE9BAULL, 
            0x8CDB36067947FB07ULL, 0x0C5F6CB296BEAC0CULL, 0xFFDC91C90314EDD0ULL, 0x270BE6A73AC1DAFDULL, 
            0x30C25228F9614F1DULL, 0xD82396691F8E488AULL, 0xFFCACC1013909F8AULL, 0xB18DA64FA95ACF42ULL, 
            0x13DF8BFDD00DA6F9ULL, 0xDE1584AE693EB4BCULL, 0x6F5D39C8835EAC2AULL, 0xCA16669056D1959AULL, 
            0xDE6546C882EE8561ULL, 0x21AB92CA506F0803ULL, 0xAF0B70A2B72409C8ULL, 0x20F9AF03566742F3ULL, 
            0xA8AC97293A59D8E5ULL, 0x3556F5AA543690F7ULL, 0x234E4F8CF55E5C91ULL, 0x1E360B69F2255C11ULL, 
            0xE6C67B154EE0AD9DULL, 0xF23ABADD964737D5ULL, 0x62AAECB637845C9AULL, 0x2813EE7D5F82287EULL
        },
        {
            0xED8D4C7517BAA2BEULL, 0x3BE33A80368B1628ULL, 0xB7FE6CD33682FBD7ULL, 0x520E722468474680ULL, 
            0x937E3336D4A5A1DDULL, 0x7F32222CF07FC82FULL, 0xDE0C98F706B97C4BULL, 0x9229284BB941C3CAULL, 
            0x8FE01F144340A602ULL, 0x9406D74DB2CFD152ULL, 0xAC276C56E60B12FDULL, 0x3C84CC103BD47A80ULL, 
            0x93D5D75F3BEFBD1EULL, 0x18FF6E9B45612481ULL, 0x898DACCF49B14A9FULL, 0xA4810E9FFB916550ULL, 
            0x081C8047B1AFCA4DULL, 0xA5C569398451F109ULL, 0xD43CE1B545E8120CULL, 0x64C8835B3984C491ULL, 
            0xB68DA430C36859C9ULL, 0x8C7F10DDA7EA8619ULL, 0x3302F0F23E71E77DULL, 0xA63C47E7BCF0A0A5ULL, 
            0xCD14453F51684F19ULL, 0x05D91BA7235150B0ULL, 0x6405DBC9EA94A9E4ULL, 0x9F40DF25536D83C3ULL, 
            0xBF61F7959277C20FULL, 0xFB98021F7D76D41EULL, 0x29FEDF3F393864CAULL, 0x7105FB28B35512BDULL
        },
        {
            0x68DCCB466EB5C8C0ULL, 0xED3F0885D952B080ULL, 0x6D5BB161A7631F2DULL, 0xF2292229580CE9C2ULL, 
            0xDA55CB9E86B15999ULL, 0xA7047DCB778C9A83ULL, 0xFCCCA161ACD7F6A3ULL, 0x15696C0962C3B7F9ULL, 
            0xD6FB2FDC6A81DE2BULL, 0xC0B998EC45EB4D42ULL, 0x7100A135E787B6E2ULL, 0x02141E64F520DC97ULL, 
            0xA7F69856F5BCD0D2ULL, 0x14F887D9141EAD67ULL, 0x96E2640E658FCFBCULL, 0xA1ED087BA4D8C15BULL, 
            0x36B8AC11F8A583FBULL, 0x665983C77B8D05CEULL, 0x8BC7E790071D612FULL, 0x706E717E4AF37A83ULL, 
            0x21CE1F55B1317332ULL, 0x62D956C99BC9647BULL, 0x2EEB64D6393BB48CULL, 0xCEC6EEE11EAB49A3ULL, 
            0xA009547500D00831ULL, 0x79FFB40647BA5D83ULL, 0xCA0E463E4EF86B3CULL, 0xFDC1056967E15709ULL, 
            0x1BE29FA000729771ULL, 0x68AB31258C9DBE3AULL, 0x70153B32F786C97DULL, 0xAA754A76E276D03CULL
        }
    },
    {
        {
            0xDAE296B964AF7191ULL, 0x9CE567A444D75DBFULL, 0xDA9DF7BFF99E27BDULL, 0x15605BA5A8B930CBULL, 
            0x7C174867B9497695ULL, 0x000567A0B431118FULL, 0x42E00DB0AEAA55A0ULL, 0x1BBB0032B3BBF6D3ULL, 
            0xF7C3719C6AB29C17ULL, 0xF4C29E8F6A5EC0FAULL, 0x459C57E5AB596C5CULL, 0x214551F51B62E5F6ULL, 
            0x8399C8ACDDC8CC18ULL, 0xE0EFDCE9179939D6ULL, 0x4BC6FCA5C6759767ULL, 0x0F06360F0517FEC8ULL, 
            0x45B2FF29F524FE87ULL, 0xA5936A9470CD2CC1ULL, 0xB9C3005F03E55F54ULL, 0x8732B441BD7BF7C3ULL, 
            0x0D2AEB7B36F0AAA9ULL, 0x10C455771B677429ULL, 0x039C9576920E9312ULL, 0x08041654F0870D70ULL, 
            0xCDE25CDD77CC68D9ULL, 0x000E3D372B8CBC9AULL, 0xC491D65477DDD29EULL, 0x9BF552E267F2B8C6ULL, 
            0x0D5687D97FAD4E4BULL, 0x578ED84E7C815260ULL, 0xCA5551E50488489AULL, 0x61CAFEB9DCE206ABULL
        },
        {
            0xF1389AF491376016ULL, 0x5DD35F879B825500ULL, 0x9AC98F42D0B7EC0FULL, 0xBA0422F5903BA11EULL, 
            0x5B2B58D17151168CULL, 0xBB8B58582C2B1C27ULL, 0xB662C01D967C105CULL, 0x7C018B156BA7C2EAULL, 
            0x3E8769EDADDB8DF5ULL, 0x79812691B4DE17BCULL, 0xEE6DE2A155A2CAC6ULL, 0xB5183BD6D0FCE4EAULL, 
            0x4F1FAD4ACF86F04AULL, 0xD2F769746AAC7E76ULL, 0x28973022F6F18662ULL, 0xDA15D491055A64ADULL, 
            0x0F5FE62201A0F07BULL, 0xEDEB9037B16F097FULL, 0x72EE8394FDFD977AULL, 0x8D38CB6F41585FEDULL, 
            0xEA00B3E78CFF1949ULL, 0xCE763C9CDF8EA4D5ULL, 0x08CFE8D00AE5DC0BULL, 0x0A53AA62E1DE454CULL, 
            0x100FF2ADA4B9C0EEULL, 0xA8F9C957911BA876ULL, 0x20FBCAC424CF9BBEULL, 0xF73A11AA9C616127ULL, 
            0xC8FB6B7062D4734FULL, 0xE432E25D1E3A0052ULL, 0x8AC68695E6D4B651ULL, 0xC21D00FA6A5DC93DULL
        },
        {
            0x67F8C45DEA4F2571ULL, 0xF1BADB94405B0D3BULL, 0xCCD66A630C3F54D1ULL, 0xF12E539D7DA74299ULL, 
            0x3B6B044431371C65ULL, 0xCEDAF2CDD95F1E25ULL, 0x02D006014E5C65E6ULL, 0xFD1FEA0111BC6DE9ULL, 
            0xA56DEF9D3D56968FULL, 0x03922804B6BDBE67ULL, 0x131416F11893DCC0ULL, 0x7C57879BF41666F5ULL, 
            0x1AB32A10EA51B7EEULL, 0x67060233BF2C8AC8ULL, 0x2B56803D86AFC1E7ULL, 0x06F44377B1319062ULL, 
            0x81DEA06BC27922E6ULL, 0xAD2BAC1CEA15DC2EULL, 0x8CC1FB8D3BA94DA0ULL, 0xF7A6AD46E35A1C60ULL, 
            0x0CBE0EF3DFF4B6A9ULL, 0x4A9163FE7C2C78C5ULL, 0x80DAA284DFDEB6A8ULL, 0xCF03415AA0A5B275ULL, 
            0x79F798D0764B41F3ULL, 0x4DBCDAF5D5422B34ULL, 0x5AE21A1354B3009BULL, 0x80DE5E60E7492786ULL, 
            0xC255DA8CD5F66AF3ULL, 0x2492A8FFC5D2536EULL, 0x2E07EEA59EB54F59ULL, 0xCB74B69F2785FCEEULL
        },
        {
            0xD6AA34B994D7979EULL, 0xA510D656FD417FEEULL, 0x3AF7FE1B2353797DULL, 0xDB73653D2D4CED50ULL, 
            0x930FC625D6D7EA20ULL, 0x234C31926B3B4FA2ULL, 0x2A88FD8DB99D82BDULL, 0x551402E6F5CF1C38ULL, 
            0x600882C2307C737FULL, 0x81CF9F9DD4C8924EULL, 0x2E761C3D4C19A06BULL, 0xED08A429C1330ADFULL, 
            0x1AFC4C5C12E5A1C7ULL, 0x2682EA1C64BF1114ULL, 0x619407E9682C317EULL, 0x4C53FF94DBCF5581ULL, 
            0xF11E3AC7935D3E1CULL, 0x93A6D01C1F42D5ABULL, 0x7FA481AAF579793CULL, 0xDC2C44D5F3AA0716ULL, 
            0xAFC07CD8E7C02D69ULL, 0x9377B44C52DEBE7BULL, 0x42D5783CD0BF0787ULL, 0x4492B0139F3F9106ULL, 
            0xE3A63B654EA4FB9CULL, 0xC73D1A080A92462CULL, 0xFE20715C234B64CCULL, 0xC7D2270D4496861DULL, 
            0xA7E031E92483F101ULL, 0x5275FD9333CEAD05ULL, 0xBB0834B83FCE05C2ULL, 0x61C67954650D16ACULL
        },
        {
            0x022B49317F8806DFULL, 0xBC1EDF8BAA78699AULL, 0x8304C9983F376652ULL, 0xEBB4ABD4B5B866F2ULL, 
            0xBD581B0CAE5CA206ULL, 0x19B1443BB357722BULL, 0x4933A6336735510EULL, 0x1D02FD3324D75EE7ULL, 
            0x0F30D1470E17DCD6ULL, 0x48129F9F06F0B801ULL, 0x43A077B56C122A89ULL, 0xF68BA62CB0203CC0ULL, 
            0x8E635813AB508FFCULL, 0xE455B783EEB06C5DULL, 0x6CD61253BF85A197ULL, 0xFC192D5632BEAC1DULL, 
            0x09E803D429708107ULL, 0xF2D0EA23DDD00854ULL, 0x880C2AD4CAEB838BULL, 0x27E44B619FBD8565ULL, 
            0xFE8765AB69FFCFE9ULL, 0x3D035D3A2649AB15ULL, 0x0DCFC1850DBEA118ULL, 0xE77DE074DCA0BC75ULL, 
            0x56A8DB82165E3602ULL, 0xDB88E92B64E3C76CULL, 0x5E161D6DA6ACB57FULL, 0xCD71DD0C204D7ED9ULL, 
            0xA2F008D38AA635F2ULL, 0xBF45DA38E8B7119BULL, 0x1386AD8293FB529AULL, 0x4E5C2CE71E3FAC73ULL
        },
        {
            0x1A8D37A07510A9E3ULL, 0xA4C30DF0EFD138C4ULL, 0x06F1BD86199FF19EULL, 0xE433B2BBE3903AB8ULL, 
            0x3A9D7A12BA70321FULL, 0xD01707343970F07EULL, 0x64ACC8693443E162ULL, 0x821B5C0937A4D612ULL, 
            0x54C0B1AC3627231DULL, 0xA9911ACE63F45B3AULL, 0xFC106830106B163DULL, 0x4031D975F13B1488ULL, 
            0xC2A049A5248F826CULL, 0x1324AB892F7DFD94ULL, 0x8F0B0EF8119846D8ULL, 0xAF520653F28659C2ULL, 
            0x1E39677E57464B3FULL, 0xAA1E0B3490C98B6EULL, 0x85BE943913BA3D39ULL, 0x94E7F202D7EA188DULL, 
            0x0C7D50DAFCB394ADULL, 0x54DBC032A5A99D98ULL, 0x4BBDE1E80A9E4BA5ULL, 0x65BA032CA38115EBULL, 
            0x765A2A381B235D42ULL, 0x6259F5DA7785F3FBULL, 0xB56C236643849688ULL, 0x9B6E5FC6F96525DEULL, 
            0xA0871D3A5165DBBFULL, 0x504209529EF70CC8ULL, 0xCE2F287B39C0458EULL, 0xF43BC20B2558860AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseEConstants = {
    0x2425929D31EA56F5ULL,
    0x97279F948BA8CEA4ULL,
    0x40AFAF5D759C2D0FULL,
    0x2425929D31EA56F5ULL,
    0x97279F948BA8CEA4ULL,
    0x40AFAF5D759C2D0FULL,
    0x2012CCE8853F724EULL,
    0xDBC282EFB20973CFULL,
    0x3D,
    0xAA,
    0xAF,
    0x61,
    0xC9,
    0x8B,
    0x0D,
    0xB2
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseFSalts = {
    {
        {
            0x07BE0B0E83226FDFULL, 0x8510983608383F0DULL, 0x4C9E3D34097A6D6FULL, 0xC7EBB4A4E705CD36ULL, 
            0xD27C1826D8EED829ULL, 0x404E652424424FD6ULL, 0x880DA8D00BFEBD70ULL, 0x36D181B39AF157BFULL, 
            0xC3EE0F34631E23AAULL, 0x7E9B049A79FDF253ULL, 0x89CB50ED6E1DDEFCULL, 0xB3763DEB467D0421ULL, 
            0x2C99C404BAA58C1AULL, 0xA7DA0376F418E080ULL, 0xBA2068625132DF38ULL, 0x3AB2703DC26D4490ULL, 
            0xC6B71076C8A45643ULL, 0xCDE2E7957691BCCBULL, 0x40D93EB11DF8E4B3ULL, 0x99BC100DD581BB06ULL, 
            0xBB0CC0CC1897EF2EULL, 0x70DD619985844B1BULL, 0x3AED6ED8259D3F12ULL, 0x552D90CFEB512CCDULL, 
            0xBD7383A0704A8B3DULL, 0x2FD976B9CAE83553ULL, 0xED20F9DCB133F1C9ULL, 0xB26BE3541B6AB1AFULL, 
            0x7937477E1B6A3AE1ULL, 0x29725D312ED28B56ULL, 0xBAD8EEF8F5A54BB2ULL, 0x838BC9CDCFED7CB7ULL
        },
        {
            0xCBFF6B891029565CULL, 0x2C6D22374184D4A0ULL, 0x3C85B6ED6AF4E7A8ULL, 0xD1E974F447AB1C2FULL, 
            0xD09673326C0D42DFULL, 0xD79055AB83EE26DBULL, 0x284A348AB7508A4CULL, 0x63E473CC0185E2C2ULL, 
            0x54547A933F786124ULL, 0x32CD9C8D37C3046BULL, 0x7F86FDC90C0770B9ULL, 0x5B4E2B3992521E7BULL, 
            0x26D2E24FD9B3774CULL, 0x16CC53B04D0E9F80ULL, 0x1D03D10A33DE53FCULL, 0xEB9568F93FBCB398ULL, 
            0xDB4ACB199E983753ULL, 0xAC5F613B68186DCFULL, 0xF80E8F7ECA4EF315ULL, 0xE4A237C47D869AECULL, 
            0x0BB729F28BA03408ULL, 0x455AAFFF83E29CFCULL, 0x5D1768502074FE9FULL, 0xC84A2A1FE27DBA63ULL, 
            0x6050E527CF6FC95AULL, 0xF1C579494C55B75CULL, 0xFD9CA9605C48F871ULL, 0xE260E0F5B54CD2AFULL, 
            0x28C265C9346D091CULL, 0x4C738D1C2C2E194BULL, 0x8504654EC69803E8ULL, 0xFD6BDDAC62342361ULL
        },
        {
            0xA522B6344EF199B0ULL, 0x26CA423A41851992ULL, 0x000CD32538EEE7EAULL, 0x45FB8EED03215C0AULL, 
            0x61F3C4E9CB19A654ULL, 0xE00D7FC76B489364ULL, 0x396D06F03B9637C5ULL, 0x31430093E1A1DD14ULL, 
            0x35CC39E4B03AB586ULL, 0xF7BFC34D1FA7C793ULL, 0xA6FD480B6B0983ABULL, 0x570B7163A8C840C6ULL, 
            0xB87200D6664B56ABULL, 0xBE983A0C46A6AFDCULL, 0x39AEC7F6960FA15BULL, 0x307D6A1601864994ULL, 
            0xA03D70DE8D4BF8CDULL, 0x982BBD4D18C2408DULL, 0x4CFC54FFFE6E725BULL, 0x40C902D4EDA55F01ULL, 
            0x6F67FA8E2546099BULL, 0x5EEC8F096801B597ULL, 0xBBFB449ED48B1961ULL, 0x057C03BBD3ED6935ULL, 
            0xF39DA0A487A6A0AEULL, 0x6FFDE2C3A017BB6AULL, 0x9DC04CBD02415860ULL, 0xF31AE8663330AE03ULL, 
            0xFEDAD03A5066AB7CULL, 0x46C46F46EC1AEFFBULL, 0xB114078AA8329C82ULL, 0x31F95A0839C560F4ULL
        },
        {
            0xCDC5CD4F9029CCCBULL, 0x1EC81660D1528646ULL, 0x4AA7AEC0F9878089ULL, 0xD146AA7216BBE922ULL, 
            0x22AD11B23C2ADAFAULL, 0xDF2D51BFD1750D55ULL, 0x9714677883AD5512ULL, 0x5D561E39F54AB360ULL, 
            0xDA3EFAFF980540BEULL, 0x4D62D608FA9548A1ULL, 0x51CCE095A4FB45DBULL, 0x4BCB1B5FF94CCB83ULL, 
            0xD054062AC472F0E7ULL, 0x17D0DBD2D9C97307ULL, 0xDFA7FCC40B2B72C9ULL, 0x96C0F38AB2E9D3D8ULL, 
            0xF2FF763135D80DE4ULL, 0x92073923306A6A82ULL, 0x3964CF67EFBE7D56ULL, 0x7FC985582ABDAE8DULL, 
            0xC9D2378DCD7DA358ULL, 0xE4827063374CDE0AULL, 0xC931A793C3B17BDEULL, 0x557588C02A468DA4ULL, 
            0x595332C52E7ED56FULL, 0x2AEC1FF3F2F6AC35ULL, 0x769FC2D5243B0078ULL, 0x9DF9F28E7F9A6718ULL, 
            0x3419D9904588B752ULL, 0x72C9457F2B1D4233ULL, 0xCEDA747040FA1310ULL, 0x4C7B1DADF642967CULL
        },
        {
            0x30B244FEF45ED292ULL, 0x8A8D4D492D5FE8E9ULL, 0x3BD30498F6061FAEULL, 0x157D71E21ABAFB13ULL, 
            0x6DCB1CFED29F6A8EULL, 0x87C45562544F67F9ULL, 0x5D74B3775211A16CULL, 0xB85D7E49A3F9CEC4ULL, 
            0xB01D5A32C47B7EDFULL, 0x6F218ABC83E0B3F2ULL, 0x6D9316A5FF4A36BCULL, 0xEA52116B6BCBB4D5ULL, 
            0xDA6787368C75ABAAULL, 0x7FF0980F7163D0FFULL, 0xF12C333F9D998826ULL, 0x319D8F84B7525425ULL, 
            0xE2951B8512FB3E75ULL, 0xB508A49318E0DC0DULL, 0x96043C011BA5164CULL, 0x87C4D3679A0836B1ULL, 
            0x94BC0556E319AFC0ULL, 0xBD2A0F1EE769777AULL, 0x9EBD33DD3E733754ULL, 0x1C93F7724B15D057ULL, 
            0x79AC0C507E11749CULL, 0x4DC56A0F48EDBB54ULL, 0x3C97A4855CFCDD9AULL, 0xCFCC957376392896ULL, 
            0xC3A2EFD7A1CF5EECULL, 0x5BC45D4CC8951F48ULL, 0x8E2224CF3140DA98ULL, 0x7DF796561648CA6CULL
        },
        {
            0xC3D34954901FD446ULL, 0x6E2133E854317DC6ULL, 0x7526A431063D0FD3ULL, 0x9429B8500FD28E5CULL, 
            0xC63C3D0F5292C003ULL, 0xFCAC7291A41AB1BEULL, 0xFF000E52A3D1C281ULL, 0x3D2B6F0DA349018BULL, 
            0xA9EC09AC3382F08FULL, 0xCF9E06EB9841679DULL, 0x386D467C74FF002DULL, 0x4029E7E19896DC86ULL, 
            0x2B648AF2C52823CFULL, 0xDEA4F5FBE9A26A68ULL, 0x20C62285589DABEEULL, 0x4BC4AF4A54EAA5D1ULL, 
            0xE43F5F3D66544757ULL, 0x132C1E833376D65DULL, 0xAE865663D2703B2AULL, 0xEB43D1C221E7810CULL, 
            0x2289BD791514863FULL, 0x19607F5341BA8BD1ULL, 0x51847498A48EF1B8ULL, 0x8A0DE028B8DB1DB0ULL, 
            0x9973771C8B22C9E6ULL, 0xD54BD08CA05EA846ULL, 0x74850F7358E328ECULL, 0x3178E4E3CC454CACULL, 
            0x805BD397694D6798ULL, 0x2937C2B33C7409BCULL, 0x222197786DD4593CULL, 0x38879942AC823E4DULL
        }
    },
    {
        {
            0x2173BC0017487C65ULL, 0x8C19726E685F67D1ULL, 0x96FD225D94ECF3A0ULL, 0xF8B35459B16F95E7ULL, 
            0x3AFE980A92BAF6E5ULL, 0xC45D39598F6D6297ULL, 0xA98A3AF155F90175ULL, 0x6BCCC68A171923CCULL, 
            0x74DD5356C9B05FB6ULL, 0xEE7101FDC0EBA1D9ULL, 0xD5BC6EEB181FDD9CULL, 0x408B68D195A8CA95ULL, 
            0xCDB1D10B6CA9124DULL, 0xAFE5E4FDB6984A2EULL, 0x6F4830BAB456E91FULL, 0xC87B1DD935B7B018ULL, 
            0x42CE96BA88D68589ULL, 0x13CBA4FFA1F8E9CCULL, 0x8091AF3FCDC34591ULL, 0xBF3363247817C937ULL, 
            0xD0C38B08E9F2CB0EULL, 0x9C679528A6DDA173ULL, 0x11887233FC180ABCULL, 0x7C1110A71869A278ULL, 
            0x1590353AD20BB211ULL, 0x610B9304B281873FULL, 0x33613D3C4FEEB515ULL, 0xB4869B64CDA3889AULL, 
            0xEC2CB06364DF45C9ULL, 0x5E12BDB824BF6971ULL, 0x5A24C361D5913DB3ULL, 0x5BF4E795515939D1ULL
        },
        {
            0x470635A0484932E7ULL, 0x789C94558FEF1B05ULL, 0x22FE6A06C092DFF4ULL, 0xC6DDC83F290CD640ULL, 
            0xEFD128A38EDBCB04ULL, 0x3E7218C2075F2407ULL, 0x69296F32C53B75CAULL, 0xD8D82A85F3757A1DULL, 
            0xF6665D4825C43701ULL, 0xCCA31C50A161FEC6ULL, 0x0911B9D0BE677956ULL, 0x6209FEE8C90F9936ULL, 
            0x2FFFE8CB2C152975ULL, 0x6C428F98AA33703AULL, 0x84A24AEBCCA12F02ULL, 0x1B99B110190CF5B8ULL, 
            0x774F434339857D4BULL, 0xEAFC7A8F32CED248ULL, 0x70C550C678B24BC6ULL, 0xBA02E0090B3241F8ULL, 
            0x67FC3CD23450F351ULL, 0x5D0D3E20C9A63247ULL, 0x1E2C81C28C9604DAULL, 0x68F4D22BB9E2BC8EULL, 
            0x12A022E82F370D2AULL, 0xBD6B177516BA2FB6ULL, 0x1A64ED10B8789235ULL, 0xD8F2F3B8ADE6F1B5ULL, 
            0xDBF2EA45BBF243B6ULL, 0xDF4BC727E28B5704ULL, 0x1AD184461934DE77ULL, 0xBC1D610D90071204ULL
        },
        {
            0xB43E8A3B94BB70CEULL, 0xC16D50DE43E63D44ULL, 0xDD12CD8C1F9B0B19ULL, 0x84BA2B8C4B0DBC9AULL, 
            0x663E3F622C0A1DE6ULL, 0x582C37F5F8810075ULL, 0x14E51E5A08EA80FDULL, 0x6D2E79FEDF8B0EE5ULL, 
            0x214EA09B4D5B0895ULL, 0x2850FF6B8347BB4BULL, 0x23DCC85883A8C0F3ULL, 0xC65A8BEB98798EBAULL, 
            0x7C87BC7112321D39ULL, 0x6B7708962D675C91ULL, 0x5AAC10E6CDB8855DULL, 0xFB5050241A474417ULL, 
            0xE4679855E6329A18ULL, 0x9E4D645029A240FAULL, 0x9AD3009B4663102BULL, 0x5011C5A0F3BC9D4EULL, 
            0x797A3CA8C2E1F065ULL, 0x1492DFD12053D0FCULL, 0x9CCB27E3DF2631ADULL, 0xE89EC6A09E8CE889ULL, 
            0x961139AC15212AA4ULL, 0xD077669674418075ULL, 0x3E09B74A90F1708FULL, 0xD85B0BDDD51204BBULL, 
            0x0A0E90531856EDECULL, 0xA3DD47A3337C1AD0ULL, 0x17C40D752C7F13BBULL, 0x6C85811A3914BFA5ULL
        },
        {
            0xD96E49ED55EE9A75ULL, 0x98BA276AA4675676ULL, 0x4BF2B3633380E391ULL, 0x23E3AFEF1D1B34C8ULL, 
            0xAB7B380B904D8730ULL, 0x274F62AC542AD3FCULL, 0x0CA08C47ADA01860ULL, 0x60094BB420FC1ED4ULL, 
            0xFCC38D68BB6FE14AULL, 0xEFFCF9C327191F2EULL, 0x8671D34BD4A9DF55ULL, 0x070B70E02E3AD48FULL, 
            0xBE6B3BCECE76CF61ULL, 0x9C271BF6243C52F5ULL, 0x7F74206DEC20D110ULL, 0xE9A3052710BF617CULL, 
            0xD13A254AAAFC5E79ULL, 0x26C2C1D7074C9081ULL, 0xB744455F6F1C5F9FULL, 0x37E996E89FD78133ULL, 
            0x3102D254AEA9CD83ULL, 0xECE48B9CBD3B8FD8ULL, 0x3ED29927A7AC3AAEULL, 0x159455F6EF41A359ULL, 
            0x77B5E4D6E401F928ULL, 0xE68E246C546106BDULL, 0x13819E0065D4F486ULL, 0xE0833213A802D39FULL, 
            0xD5F0DE56F4A83574ULL, 0xFF2ACAD3445D61C1ULL, 0x469D4872A0974C21ULL, 0xF1EE71E7EAF56D23ULL
        },
        {
            0x7BCA9D62760D2E3DULL, 0x4D1BA5F52D5191DFULL, 0x24C7DD74CB645486ULL, 0xE9E2BAC6AADEE02DULL, 
            0xFAD20D8F81B65F71ULL, 0x04EB9C04D8456F08ULL, 0x27A600C80EC47ECCULL, 0xA4369675E444DD90ULL, 
            0x0B45319CCE816B09ULL, 0x09BAE414DDBAFFDFULL, 0x67D667DE09387132ULL, 0x37AD06E19838483AULL, 
            0xAD80A36193810BFAULL, 0xE7952D1A69473FA1ULL, 0x5A707DB99105BA8CULL, 0xA97F49C942E478E9ULL, 
            0xAE39C3CB993BD9C4ULL, 0x535B73E3B718A190ULL, 0x2380A2869E256C2EULL, 0x64B878A1077CEED5ULL, 
            0x32847D697D76A6B1ULL, 0x453C47AC98A8E224ULL, 0x0AB5011103BAFB5DULL, 0x6778F4946C22624CULL, 
            0xBF5C8E6B1F068DDEULL, 0x5B4C7128DD69A022ULL, 0xA7B6015981E8352BULL, 0x3224B73BA3CB6E87ULL, 
            0xC573F1C17A7B2D8EULL, 0xBB457A596DFFD115ULL, 0x044EFE171F79A39DULL, 0xE02BC65D15F5A2E0ULL
        },
        {
            0x7FE14B59C57A159EULL, 0x8628DB5D7C21AABEULL, 0xF3AEB696F27BA174ULL, 0x74669E896DFD5AD9ULL, 
            0xAC2CC47393D25036ULL, 0xAD5F3C6446EC0598ULL, 0x77F5EE5AE6D94125ULL, 0x34239527C2C6F4D3ULL, 
            0x3721587C926FB54FULL, 0x96F2127F63A9762AULL, 0x5502E7E794EBC89FULL, 0x635D3C564274749DULL, 
            0xD5C22DE9F23CE84FULL, 0x42D3B8FD90ACEBE5ULL, 0xB2C34FD49CAD9EF1ULL, 0xD58F4ED027D16BB9ULL, 
            0xA02CBFC22F02502DULL, 0x404F9768EC249742ULL, 0x7B76A2A54FAB7F29ULL, 0x0FBA53C52A773CF9ULL, 
            0x383027EA3770E763ULL, 0x5AC02C3FDED1F8CFULL, 0x888953215B0D0992ULL, 0x881D8C19A4EE2809ULL, 
            0xB24427E0877258DFULL, 0xDE31A52E693992F2ULL, 0xCFFF9C243200A90DULL, 0xFA4A46F21B2BE2E1ULL, 
            0x7796C309E5946520ULL, 0x31C17C4EC3F82765ULL, 0x3055C5505BE4D717ULL, 0x31CFFB04BC62FD58ULL
        }
    },
    {
        {
            0xD152630E1F634044ULL, 0x0329B695B103F28AULL, 0x7123CD6B81F95AE5ULL, 0x3F9F8B5A135B9A07ULL, 
            0x5357302DB1745151ULL, 0xCC85867A5B51402CULL, 0x534510CEBB10D858ULL, 0x35DB952EFE30CC46ULL, 
            0x5519876CEB8CBE49ULL, 0xA220F6DAD35DF5BFULL, 0x580933CDD64A240DULL, 0x27900090377E07CFULL, 
            0x67EEDC881DCAAE65ULL, 0xBB6EB5B2CBF757BCULL, 0x2088906021D99164ULL, 0xF81D268E935B37B0ULL, 
            0x08C0D8C04CB95744ULL, 0xF7EE2FD48C21E90FULL, 0x5CB8963B64C53253ULL, 0xBAEC58229A23F1D1ULL, 
            0x00B3482F8C164255ULL, 0xD452C9F73DD92D75ULL, 0x23C4178A470C8593ULL, 0x03C45FDE4147DD70ULL, 
            0x1BDD9F38C72D919CULL, 0x12BC8623177CBCCDULL, 0x3A4A386F1E557D2BULL, 0x31D87427E28DA219ULL, 
            0xFBCBCFAB7B22E66CULL, 0x9FF8B759C75254A1ULL, 0x82CD60B2758F464DULL, 0x259A0A4B28387B38ULL
        },
        {
            0x30928673496C8861ULL, 0x40D0E628C0C722D7ULL, 0x6C8C03FED1B2DD28ULL, 0x12376C2B8BE9E5D6ULL, 
            0x7290C5E97451D379ULL, 0x0E135D8B7E1817FBULL, 0xBBFFD5E986E43F19ULL, 0xB6848B8B60093964ULL, 
            0x8038EF71BC430F7BULL, 0x8378FACE7E16E99AULL, 0x6E50F03DAD384E2CULL, 0x69678BF6E0050311ULL, 
            0xCE4C62CC27BEDFADULL, 0xB57A3C06BB606C11ULL, 0x08FECA25CD7ECE43ULL, 0xCDC1E21112CE62D4ULL, 
            0x0618816C321F2022ULL, 0xC4C4EC928F7CE542ULL, 0xF50712A913059DADULL, 0x7458E0427B24D798ULL, 
            0xB6EEB5AD3A1E933FULL, 0xC2E9893E0DD19E7CULL, 0xFB7A36489D4A6101ULL, 0x67AB03F613692A19ULL, 
            0x3A5B4D1988A4780FULL, 0x3CEA0AF19180B494ULL, 0x920EC5B2FD2470A0ULL, 0x0136DCA9AE87008EULL, 
            0x663ABE601396FCEAULL, 0xBED022E0FE8CA13EULL, 0x734A2AA65BD73C6EULL, 0x2AC3E6E7A1DBD5E8ULL
        },
        {
            0xFE326F7A46396E2BULL, 0x9D80812424F10DB5ULL, 0x8651195151F1D373ULL, 0xC60E10936EDC8753ULL, 
            0xAEE1F8B6B140EC08ULL, 0xF5BC369ECB4AD2D6ULL, 0x4231F4736380A287ULL, 0x8131BEF942F46223ULL, 
            0x74DB4EDF13BA0A61ULL, 0x36B8038C5CB19D70ULL, 0x820B93B03FD1006EULL, 0x64FE773A0041B8D8ULL, 
            0x7F73C5FA9360F053ULL, 0x33F206A697CC7B9CULL, 0x98B4CD561AFAE6E0ULL, 0x735B309AA4851E0BULL, 
            0xFE310AB9FF964C25ULL, 0x519006E5E8985635ULL, 0xE28F9B73F2553131ULL, 0x47C2B07A076AFDA5ULL, 
            0xA544FFC4433C3D8DULL, 0x3B1B5EE8C238A4F2ULL, 0xE95274E711125B42ULL, 0xAC7F32875EB866A5ULL, 
            0x4AD1DAEE23F96AAEULL, 0xAF5CBE481E056E16ULL, 0xC2D8C112502F7189ULL, 0x2A38E221F3085A34ULL, 
            0x670A84FE49DDB2F7ULL, 0x7ECC8437709D4C70ULL, 0xCA7BAED2FEC8BCBAULL, 0x4E234F03110772CDULL
        },
        {
            0x479D6A0AB7E2C710ULL, 0xB413A3F89E2D599DULL, 0xEE4464B4D655AD27ULL, 0x629CAEB488C94A95ULL, 
            0x986E061BD7418D69ULL, 0xF4D5E58201EF3B1DULL, 0x42B9CCDD0506E6F1ULL, 0x5C244B2A9E62477BULL, 
            0xBD8D962DA7C48546ULL, 0x32C68F1C153FFFA6ULL, 0x80BD9CF402FE5629ULL, 0x5E7FB1B67B087B2CULL, 
            0xE0FF67E413EE2C61ULL, 0x679E738D2F4ED17AULL, 0x46F72918CC11915BULL, 0x3803E379EAAF5BB1ULL, 
            0xC2173A53566DD1B1ULL, 0xC8F276BC019771E6ULL, 0xCE25DFADE5C4981CULL, 0x56D43FAFC01BBA49ULL, 
            0x2CEE5E546880AE07ULL, 0xB39CEED52D0A4A4AULL, 0xF0059447459971A9ULL, 0x31D4ED11E3A72CE8ULL, 
            0x71AC8177D4E89135ULL, 0xDAA9C2DEB208B8FAULL, 0xB884D520C85FEE97ULL, 0xD3E4CB7085637713ULL, 
            0xD6CE7F185933C52EULL, 0xD8A860133E0BD886ULL, 0xD17E7953CFA38C83ULL, 0x18A5A65CC71BD3D6ULL
        },
        {
            0x72551094D648FCB0ULL, 0xBBECB7A6AED95F9FULL, 0x567843F655F93E19ULL, 0x4D8D5174276DACA9ULL, 
            0x29504536CA195BD1ULL, 0xDC5D534CCAC83A64ULL, 0x6C823AA9A8A68706ULL, 0x754BB92607BE07F7ULL, 
            0x8E5FFDFFCD08177EULL, 0x48253138EEBC99B5ULL, 0x081048EC2D11AC1BULL, 0xD031B4A192486734ULL, 
            0x1D6E7F19ADC4791EULL, 0x2FC1589E0F2E9D3AULL, 0x75654AD8F40C752FULL, 0x678CE01F3256462DULL, 
            0xA418158A86D19506ULL, 0x77CD21FC153B10EFULL, 0xF6D921A762BC7FCAULL, 0xE441EE710D5038E5ULL, 
            0x7D5F40CD8D0CEBCBULL, 0x8D7F9D574DE1ECDEULL, 0x80D29BA35A1819EAULL, 0x732973F152835988ULL, 
            0x9DF86D395663A093ULL, 0xD509383971C3CD15ULL, 0x09011A3E9EBC6C90ULL, 0xBA00392F78760B3DULL, 
            0x724F45E102943752ULL, 0xF1F710D4562FCF9AULL, 0xC65DD09A86DD89B6ULL, 0x71624A4BAAF2D28FULL
        },
        {
            0xFE25F34620EF134CULL, 0x79769E3DA261E72AULL, 0x1AB7483564E15418ULL, 0x1E9986C7E41D2A9BULL, 
            0xA731678667C736DBULL, 0x63AB2FC71D635D8AULL, 0x15A8FAF550905BF3ULL, 0x6C21D93CD7E6F894ULL, 
            0x252A622E15172CBFULL, 0xF85F50AA156142AAULL, 0xA2B0E4D374BEF0D1ULL, 0x6ABB9203A30D39A4ULL, 
            0xE0151E4889DFFA49ULL, 0x59726FB97CEEE70CULL, 0xD9BA5941E94F96CDULL, 0x64A836B4288F3DBFULL, 
            0xA8E4F49091552E0DULL, 0x6F2E86C51BA3A5B6ULL, 0x7EFA7E3BCF485EDDULL, 0x01069CFCE740845CULL, 
            0xCC9563D7CB512E6BULL, 0xEF3A6FCF02C13CD9ULL, 0x928243D591B9CE93ULL, 0x23C7269783F48867ULL, 
            0xDFF41981F457A384ULL, 0x2922D7E2B34CE714ULL, 0xEE26070A8389EAACULL, 0x981573EC4945F0CDULL, 
            0xB892C4E00224491FULL, 0x30EB6ADA2A62770AULL, 0x029E5E61F693863CULL, 0x105E2884B029050AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseFConstants = {
    0x87573057D2A0101DULL,
    0xCA550ECACBF53779ULL,
    0x97EBA1672EE331E6ULL,
    0x87573057D2A0101DULL,
    0xCA550ECACBF53779ULL,
    0x97EBA1672EE331E6ULL,
    0x3196ACB6D76721FCULL,
    0xDB4BAE6BBAE62F89ULL,
    0xC4,
    0xB5,
    0xEA,
    0x2E,
    0x59,
    0x91,
    0xE2,
    0xB6
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseGSalts = {
    {
        {
            0x5D4FDEB7E2A23A85ULL, 0xA64F83D0F9364B0FULL, 0x72CEAFA98C97331FULL, 0x71D6343645126985ULL, 
            0x8B65DCB39C55928AULL, 0xEA4C36D3CF8B1AD1ULL, 0x20C5C28490630E61ULL, 0xDC56A394A9249F76ULL, 
            0xFF5C6BE7338676CDULL, 0x08F8D35F6DF730F9ULL, 0x1C077E8A3293B8E5ULL, 0x8F091767A1674873ULL, 
            0x314941ABDE0BAC49ULL, 0xD5E1E63210E5861AULL, 0xD5CB5428865264E7ULL, 0x5C304B2703C78854ULL, 
            0xACF7F127333BF01EULL, 0x4892DF039E4DA2C0ULL, 0x1F5BC621F4020F36ULL, 0x63E55154C4F61B8BULL, 
            0x405E72AAB6E5DC13ULL, 0x798889DEE0EFB5DDULL, 0x6DF9892DB0164AE9ULL, 0x8B67FD8CD347456CULL, 
            0x2C66B4BF848ECF96ULL, 0xA20E8B5E1688F680ULL, 0xD8545A37F255B736ULL, 0x1C67AD0EB840D0C7ULL, 
            0xC396D93FE0610E8CULL, 0x3952DB80A9691F8DULL, 0x5D3A453D086E3000ULL, 0x875A3454E1372253ULL
        },
        {
            0x7106F81C24387333ULL, 0x2AA1FD8CE3EDF7EBULL, 0xA62E02CE91B63A8FULL, 0xC2E3F7D456643096ULL, 
            0x0F03C86A810226F7ULL, 0x264EB29FFCA97299ULL, 0x917FF4AE37E7390DULL, 0xF269BBF05D468AE3ULL, 
            0x3A03DCBA758EFDE2ULL, 0x2BF1E460B2032C94ULL, 0x504008E1116A1EABULL, 0x61FA06032F1E2548ULL, 
            0xEBCDA0DB29C5798DULL, 0xFEA535A5D99BDFBFULL, 0x4981DA3E8DAD3D1DULL, 0xF53CCFCB11282CE4ULL, 
            0x66BD031D8846A41AULL, 0xDBA05EE413FAA643ULL, 0xCFD5F7AA2FB27F4AULL, 0xCA3683A64D08E641ULL, 
            0x175E4E95DDC0B445ULL, 0xC5785853A952B3A4ULL, 0x787216FBF9F103E5ULL, 0x223655E3473CE060ULL, 
            0xC7D58A56B33B77C5ULL, 0x6CCD9D9176989C40ULL, 0xCAD4AD96700C5729ULL, 0x196DF928B8D4FFBDULL, 
            0x7609B188BFDC17A7ULL, 0x33EB5043F3B957E4ULL, 0x824E379D301ECDF3ULL, 0x0A82B243DF1368CDULL
        },
        {
            0xFC9D4562271BC171ULL, 0xED0C06E24BB8ED4BULL, 0x39656A1C50AD0782ULL, 0x495847AEE76FBBC6ULL, 
            0xE066643CFB4F73F9ULL, 0xDE4F5219B9590AE6ULL, 0x2ADDF0A8B371910CULL, 0xDDBBD6012D1927C1ULL, 
            0x30CF23D2F03F7508ULL, 0x16AA437F20936985ULL, 0x7D579442C9B3E0A5ULL, 0xA502B54C08DD73DDULL, 
            0x45E1AD21F4030384ULL, 0x427F58B0E02CE721ULL, 0x91ACC2363DFD20F1ULL, 0xF9E7A5A1B99F5787ULL, 
            0xF99F17C5EB4F47CDULL, 0x2D208DAF25DC9C6EULL, 0x18E17A7B63395A33ULL, 0x860781985056E8E4ULL, 
            0x25AC6CC33A7FF6FBULL, 0xA3A3BD939D1EFFE1ULL, 0x9CF308EA12D9C341ULL, 0xA655489B931B233EULL, 
            0x5465FB06DF495B7EULL, 0x86C7AAFAC13C031FULL, 0x32D108A6D384B2B0ULL, 0x70050B51843631D9ULL, 
            0xA288532804644A55ULL, 0x9FF3D53E4BE05152ULL, 0x87EFB209869A7EA8ULL, 0x36E35F44991A3F44ULL
        },
        {
            0x81F9EDDBADBAA2E5ULL, 0xED0F24D22E3D95CFULL, 0x6DB99005F9FEBFC2ULL, 0x86BFF2CDF5921B88ULL, 
            0x0CAE152F72BF4D45ULL, 0x1074D2395DEFD229ULL, 0xCFD499C7A1DA53A5ULL, 0x46A12183DB073F61ULL, 
            0x3A8C267586FF68B7ULL, 0x3618BD8C9F22C6C4ULL, 0x8DA805C63B9DD7FCULL, 0x64692ACD2D7F38ACULL, 
            0xCFA65EC362382532ULL, 0xBEF9CB45912882A5ULL, 0xA3ACB0BD1DD5D9F1ULL, 0x7FF0D7B7070876D1ULL, 
            0x02620811376C79AAULL, 0x7E9DF0BD425B44D1ULL, 0x32A3570495378F3EULL, 0xA76DCC5512C278ADULL, 
            0x531C5EC4A32F24AFULL, 0x4BC69241B7978A23ULL, 0xBF7B15FB8A11566FULL, 0x28866FAD17B64272ULL, 
            0x83ABC485F22F0965ULL, 0xB6A6EC649A351151ULL, 0xCE1AA13FA37A1796ULL, 0x3801206E5312793EULL, 
            0x9466969F7A56C066ULL, 0x5A5EBB5B1F8F4DEDULL, 0x95B000B97D83830AULL, 0xADC8638A160F026DULL
        },
        {
            0x843D6CFFD7356E08ULL, 0x70E09C820586445EULL, 0x2701242AF420332CULL, 0x4E29508AE8848AA2ULL, 
            0x66C0CC8EB3F93E91ULL, 0x2F91F12FD505A0ADULL, 0x418D964319A562AFULL, 0x6E435D8B3479657EULL, 
            0x914FE44931F1DCF0ULL, 0x3CC1143C6B231EBCULL, 0x2F3C6802A320DB5AULL, 0xC5C0F21F9CE64980ULL, 
            0xC4E445C33F729583ULL, 0x6EAA34DA3285B118ULL, 0x16CD1DF200651893ULL, 0x6A16E354C9CDEBBBULL, 
            0xC3D1EA23E635075DULL, 0x8622F8BFB1FFBC43ULL, 0xE881002CEFBAA382ULL, 0x6FA721E5B48761E4ULL, 
            0x2325EBD38DD39151ULL, 0x6BE3B77EDD667CC7ULL, 0x65B996C45671CC23ULL, 0xF68ACAD9F1D97023ULL, 
            0x999C5BAF5C172DCEULL, 0x2FC5EB23FFD82E3FULL, 0x88B29B5C9AAAC1DEULL, 0xAB41D34168D98CBDULL, 
            0x9749CB54779F9479ULL, 0x7033D31C30AA5C33ULL, 0x6CF13934CA716404ULL, 0x65C15E21F68AA499ULL
        },
        {
            0xA559E6E3699CD160ULL, 0x26CB90FC061E8918ULL, 0x4EB7C34B69B87033ULL, 0xA106A5E73C77B648ULL, 
            0x80C9D933DCE2A709ULL, 0x974E287A66E66638ULL, 0x99A73214F189AB5CULL, 0x3491A3F252E8E89FULL, 
            0x639D639DDC41BC0DULL, 0xB02AD321DC82AB1EULL, 0x14B1306F979A3291ULL, 0x402E4E611EE52396ULL, 
            0x066BABEB75C04A83ULL, 0xE7363AF6C21C5E64ULL, 0xD214A2416B4D7B7BULL, 0x26A7E33AB90B8FB9ULL, 
            0x47E5248932777312ULL, 0xABF27D7C1B0DBD5BULL, 0xCD9EF797D794953EULL, 0xBB842A7392537776ULL, 
            0x4924A818E60B1004ULL, 0xF3855CF98243203AULL, 0x56BA74039901D834ULL, 0xA64CECD8BEA18ACFULL, 
            0x000900482177D186ULL, 0x1F82803CB0D6765CULL, 0xEEB82AF5012795D8ULL, 0x25E44EC6EE4E2BF8ULL, 
            0x94999DB92957D50DULL, 0x0E999A74F099D637ULL, 0xC7DF69A260D5A24EULL, 0x4ECC94589DE032ADULL
        }
    },
    {
        {
            0xBE4646D0EBCCE1DBULL, 0x58836151F671BCD3ULL, 0xC0DF7E3DA31ED0C3ULL, 0xDEC544AADD6E294EULL, 
            0xA5A673C378A18170ULL, 0xDA4D23C532DFC172ULL, 0xB06610011CA26D6CULL, 0xA582D54E0833B1FDULL, 
            0xB35B66D3925C6FC9ULL, 0x0E8410DC9AEAD160ULL, 0x86A9F6FECB5AEEC9ULL, 0x8927A27C4FA54AE7ULL, 
            0xCB9B5A670F76112EULL, 0x2D2973858077DB90ULL, 0x288B047A2E4AEAAEULL, 0xD996F50457560614ULL, 
            0x03135AFBAF8904C7ULL, 0xCB0DE1819E644097ULL, 0xBBAB21F18D85802CULL, 0x0F585BF7AA188FAAULL, 
            0x9163ABA86F964840ULL, 0x969D2E3D26236731ULL, 0xECACEBEC5FC97984ULL, 0xF26731AED04FCFFCULL, 
            0xF92058931BEC0F55ULL, 0xE7245585EFEF6245ULL, 0x793DE5AEE501789FULL, 0x5599EBF622F002BEULL, 
            0x65F3A2A3F7B1D865ULL, 0xC7555E0248E6F287ULL, 0x80028D0211DBD0CFULL, 0xDD5129B6EB726C97ULL
        },
        {
            0x4F6E3E4BCF091AAFULL, 0xDB4B48AD11F1DEA8ULL, 0xE4389272587CB556ULL, 0x59F129530F701424ULL, 
            0xFC91F40178EA047DULL, 0x4BBB184395EE683EULL, 0xD5254343FBFF370DULL, 0x5FED81958AC14E5FULL, 
            0xE5C28E1C1A802F2BULL, 0xE7DF9C566945DDEBULL, 0x1A68745E6D7A521DULL, 0x86B2EC4165B58733ULL, 
            0xB7D2DBBE771C917BULL, 0x1589EAF5EB0A1D86ULL, 0x5AED4BE0B22F035FULL, 0xE3D9793D8480A166ULL, 
            0x625517D4DE01FE4CULL, 0xA5D909B25AA654CFULL, 0xCDE549C769ACEC2EULL, 0x448A024B49705DB2ULL, 
            0xED6CA12F03F9AB5DULL, 0x2BDE67D92812A585ULL, 0x03D001A81ACEC8C8ULL, 0xAA0646A06ADB8947ULL, 
            0x850C124536610153ULL, 0x1153C96B347E5C8AULL, 0x4455133C9BBE9F63ULL, 0xC9F1ED81B04231E2ULL, 
            0x1331688E3C5FC0B6ULL, 0xC108E5BDA121BD32ULL, 0xA86F66B70E6984A4ULL, 0xDCC53EC80359189EULL
        },
        {
            0x8F99297E97EA7041ULL, 0xF53427012A67649EULL, 0xEF0624D8F045397EULL, 0x8B77CBACA1256B55ULL, 
            0x68AF7DC3204C0912ULL, 0xB2FEE77406795E49ULL, 0xFC017A1E18537C21ULL, 0x5C4FB8DAB880B801ULL, 
            0x79BF7331CAEF2150ULL, 0x84DF9A2103E3B833ULL, 0x8F22D7DBF9ECDC43ULL, 0x6756951FBA16FE93ULL, 
            0x419CAA2C5D5DB902ULL, 0x8868D848F11660CDULL, 0x660BE549728CFC8DULL, 0x6500AC5F243E2E71ULL, 
            0xD4B62DC17F1B7E67ULL, 0x382A06B2B29098E0ULL, 0x6B71A95DBFAA21E6ULL, 0xEB2308F16320E0CCULL, 
            0xEA2060044A3CA394ULL, 0xF86FE3ECCDAAD184ULL, 0x12F54DF4D9A0ECD4ULL, 0x2547F416CC01ED23ULL, 
            0x681C4EDAA568E152ULL, 0x1DF98425BBA9EEB8ULL, 0xC263ACFD4F3FD2E0ULL, 0xD61F7D8E0B775D6FULL, 
            0xB1BE171693A9D99AULL, 0xE7BB53E684E68E72ULL, 0xB3B13BBEB3E8C4E0ULL, 0x5C001CE20FC691A3ULL
        },
        {
            0xEF640F1B13B3F22DULL, 0xFA32A035BD746B3EULL, 0xA24A0BE8A62F9E45ULL, 0xEEA03B4EB96EE040ULL, 
            0x555646083EE65720ULL, 0xB3E45F73E56918E8ULL, 0x2F943E1E9A5E1D3FULL, 0x652140A482BAADFDULL, 
            0x15D7C9FA0B67FADDULL, 0xA7C40CF577D607D2ULL, 0x19C6860BA2F9B96AULL, 0x7E153E798CA1FBE0ULL, 
            0x5F1BDCAA13FAD206ULL, 0x3788C0FE645D9D22ULL, 0xB4875C4A72F94FF3ULL, 0xD0AC50F26C290C39ULL, 
            0xC41D01B63DA83BBCULL, 0xA0AC36EBD52937E1ULL, 0x4A3DD75974A7A6ECULL, 0x78D46497AD8BB9DFULL, 
            0x7EF3318DB6AACDACULL, 0xCD7E81581AF5C36DULL, 0xFA6452EF0594FE09ULL, 0xF9CEDC663FDCF467ULL, 
            0x242BEA3BE89F1751ULL, 0xB09F37A191E87046ULL, 0xE10FC634C24BA202ULL, 0x8F4EE0BA4A38A6EDULL, 
            0xFF96F37984E88FD5ULL, 0xD51FF09F4C085A85ULL, 0xC330F62B1A52CA25ULL, 0x2C00A0AD4680EE03ULL
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
            0xA4CDEB5F986D36C9ULL, 0x0D8AEBBD29574CEEULL, 0x148CB21477829BE0ULL, 0x4DA5C1042D395EA3ULL, 
            0x406E4A26F7ADEDF8ULL, 0xC39D7A2162B51F9EULL, 0xB2D1FE7F879FEDFCULL, 0x1F8BC83C364F0619ULL, 
            0x6FAD2143DDFF52BCULL, 0x59D20C792FF0223EULL, 0xBAD88E910C434421ULL, 0x2E1227EA593134EFULL, 
            0x745A9013B71A9997ULL, 0xB61B3F25CCEA70ACULL, 0xDA5D105218D68EAEULL, 0x306F1A216B5DE44DULL, 
            0x818D904B3C74EDC4ULL, 0x6F0F56B49974E957ULL, 0x13636F3A1A5C8876ULL, 0xD3177C77FADC3FBBULL, 
            0xA6882DE98A36DDBAULL, 0xBCF148115EC257B3ULL, 0xFFE4B473BC6DFA28ULL, 0xC794E71977DC057CULL, 
            0x9DB0002B32E6BD11ULL, 0xC5B0B553791CB3C5ULL, 0xA2BEEBFEB0C0C5B8ULL, 0xB0E81F7B3AB250A6ULL, 
            0x2520C426D66C5E51ULL, 0xE860C5A117B6154FULL, 0x028DEF9A535724D2ULL, 0x263D572B5CF14B07ULL
        }
    },
    {
        {
            0xDC2624E2397D6C57ULL, 0x19041EF0B1C0651CULL, 0xB37829E6386BE573ULL, 0x147C81405BA82CEFULL, 
            0xB8D9E1786CB8AB05ULL, 0x584BE7E32A5A1780ULL, 0x154FE1F3A675821CULL, 0x3BF9BF1D9F53B23DULL, 
            0xD3E21BBA075D913EULL, 0xDD096F35AF4219E3ULL, 0xC2217344679A11F3ULL, 0x3FFDAFCFF619E0D7ULL, 
            0x7FBDFDA8D4A72AC3ULL, 0x0A9FF6A9A9DB5E98ULL, 0xDAC7AA3A621EA71AULL, 0x4CD1E2288FD5EA88ULL, 
            0x12269688F90F5042ULL, 0x6F2770D93981989BULL, 0x9EA28DA8A1DE8FB3ULL, 0xA3D28D93B413AD3DULL, 
            0xA9F42552F135280BULL, 0xB60B65E5FDFBA63DULL, 0xA7167265E02C1228ULL, 0x5F871D5BA1CCAD62ULL, 
            0x12AF5B95FAB6121AULL, 0x27F381B4CD9D535FULL, 0x0D116055FAA61D80ULL, 0xFBE9D2B24249035CULL, 
            0x7028A5989F426EEEULL, 0x1B2360AE456E5393ULL, 0xD387DE6AB792520CULL, 0x0FD05DD8E3A78410ULL
        },
        {
            0x2CCC2C788C2AC5DBULL, 0x272024A732736364ULL, 0x22EF302A79F2BAC7ULL, 0xE2ECEA228F516947ULL, 
            0x8CFD427389160FD4ULL, 0xC70F25C3F3F55762ULL, 0x086C644B610F3A43ULL, 0xC2E2FA8E90A1BC4BULL, 
            0xDC4E91860E2F7D58ULL, 0xDDF582FBDD3E0060ULL, 0xB8154AFF08F4F0CCULL, 0x336D0686EB859A37ULL, 
            0xBF21F8A1143FD444ULL, 0xEADDC51B888AF826ULL, 0x5316CDE7417FA29BULL, 0x11D00D2DC769447CULL, 
            0xB2E43C2076DC6C6DULL, 0x0540282890AE34BEULL, 0xD04707887BC330F8ULL, 0xF493B8EE149F7A7EULL, 
            0xEA2E61E7CA1F43A9ULL, 0xD4372720E271782AULL, 0x831274CB30D9B78AULL, 0xAB788A05170E8E06ULL, 
            0x8E48E2AEEEBD8038ULL, 0x46551CC79234CB8EULL, 0x94589D3F58286D1FULL, 0xF3A811A2498EADC5ULL, 
            0x6682234837DC105EULL, 0x9A10DD8E5507D04FULL, 0x5FB4C6DF900F7E07ULL, 0x64C1D1F11024655AULL
        },
        {
            0xDCA428545866A245ULL, 0xE8029768C9FAE6F0ULL, 0x0303DA31B4080E71ULL, 0x414EF23E85C6F28CULL, 
            0x8D859B59323A9231ULL, 0xC7AC8AB1CDA0DCE1ULL, 0x7497DC0D0B7A0B60ULL, 0xC1AA224B294BB747ULL, 
            0xC58A28CC2BB8E553ULL, 0x3D29579E0DCCBBC2ULL, 0x902A64D71CBA8CA8ULL, 0x004E6257B33B97E1ULL, 
            0x78C2DF421169BAC7ULL, 0x4E6555DC5695EC91ULL, 0x0DC0E5F785C755A2ULL, 0x1B5D1D8669938554ULL, 
            0x6D6899EA5ACF414EULL, 0x10FD6EFAA2E7255CULL, 0xA547E99DAE559BCBULL, 0xD894D38BC3D82264ULL, 
            0x4376AF3ACCA95E5CULL, 0x75539F96067FD19EULL, 0xCE1B499D4C31CDE7ULL, 0x2972276EE3784F05ULL, 
            0x9A4B5D6BE2A56038ULL, 0x791456426D851657ULL, 0xD959FA0A103D32F1ULL, 0x11DD1C78271DAE74ULL, 
            0xA6756D2E20A64515ULL, 0xE2A2FA769A47B3DAULL, 0x2C86D90BF2491738ULL, 0xB8ED3E3343407728ULL
        },
        {
            0xE4F90F5AB80DFFA8ULL, 0xA7D5594BE6927A84ULL, 0x2FE45B547A60792CULL, 0x5C9BC276E88F7D8DULL, 
            0xB9070DA5669629CEULL, 0x3AF496389B39EFDDULL, 0x3B89404D3A7CAE33ULL, 0xD1938C742977FA2FULL, 
            0xCB725A4630BF3777ULL, 0x2A8ED69D03B373B8ULL, 0x0A28F519E4EE4B69ULL, 0x120BC1B61A28E80BULL, 
            0x314875F55C741158ULL, 0xEFD3E96DAA8CC0A5ULL, 0x47D0B76722F97625ULL, 0x5221A2AE6DC3079EULL, 
            0xA573DA960160C6B6ULL, 0x982FC9E9BEB44180ULL, 0xE10A95B1A8D93490ULL, 0x4AAA063335F731B7ULL, 
            0xEE2F4AD9D02218E7ULL, 0x109EE7ED309A416CULL, 0x959E2B300ACEA675ULL, 0x50156BBA2203BA7DULL, 
            0x27E203CE321A02DFULL, 0x38E4BB6D420B4948ULL, 0x34CE7BDCFB7DBBE8ULL, 0xB95712F829E7B62CULL, 
            0x8670B89F14DFA5F6ULL, 0xB59AAC92796D42ABULL, 0x877B6E839A73FB13ULL, 0x832C0752335785CAULL
        },
        {
            0x98E68C48F63D13ACULL, 0x0B50BA6305CA7400ULL, 0x3ABE9E7C65294D0EULL, 0xEE7AE99DA2474050ULL, 
            0xD56693CD455AFA9DULL, 0xEAACD2D7E06D2625ULL, 0x1509C3577E210A1AULL, 0xA21155D2044FDBA0ULL, 
            0xA416D2E3262D0108ULL, 0x857090A4F1C0213EULL, 0x388EEA6B6FEE16FCULL, 0xF6F2FBAF93061956ULL, 
            0xC23600993C575428ULL, 0x3825E438149DA8F2ULL, 0xD9F5D336CFA6BDD2ULL, 0x5192A40DD1CA1639ULL, 
            0xE193EC23EC8FD1E0ULL, 0x818676CC05C07683ULL, 0xF307476E9143AB12ULL, 0x258EDAE68807FC7AULL, 
            0xF0BAA42C394A7407ULL, 0xCAEA1FEFD9B7C4CCULL, 0xF8DE9C4C04B5A1E4ULL, 0xA820DB760FCED5F9ULL, 
            0x70BFE61F0366FEB5ULL, 0x275B5AE145B357D5ULL, 0x1B0A2DA2C9116628ULL, 0x0D630191AB206D7CULL, 
            0x3A19CA246F35A6FDULL, 0x9983B86E9F38D13DULL, 0xC31653157BFB38B2ULL, 0x31AC82C4F3F71507ULL
        },
        {
            0xB942B7F39D2EBEB0ULL, 0xA22D79E10D546A30ULL, 0x01164C2C26A1D232ULL, 0xF89737ED9A1C78B8ULL, 
            0xB79E5FBCBBF05128ULL, 0xCE0C9A3508EBB83EULL, 0x1655BAE0E679572FULL, 0x4FC141ECF6F9115FULL, 
            0x64D2E30A9D99438AULL, 0x108D12020CCF81A6ULL, 0x0CA6736FC1E92501ULL, 0xB0EA79943D9DC687ULL, 
            0xC23A57D1290145A9ULL, 0xC3ED1C4ABC987734ULL, 0xCF9EBACC36012E7FULL, 0x6B3B5C7E2C0BC2D4ULL, 
            0x114D75CC4EC37D3DULL, 0x51812C8B312CE13FULL, 0x8CCD352208938000ULL, 0xEE9D300D1D8C7100ULL, 
            0x094A29570A9C99E7ULL, 0xFA626EB845438BE8ULL, 0x9DC8B9AAC94E6E2BULL, 0x435EB7394F9C5B51ULL, 
            0x916C58015D334E38ULL, 0xCB0E0B7AD331FD4EULL, 0xD037D8E57B83503FULL, 0xE8E27B227A2B9C25ULL, 
            0xD6CDE0140475CC3EULL, 0x24B35E9EFE4B2789ULL, 0x06C1C932754F8F34ULL, 0xE71042FD470ED1A3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseGConstants = {
    0x377DC051AF5BACC0ULL,
    0xA0D3EB73852DEA0EULL,
    0xAC9E60B622F93C3EULL,
    0x377DC051AF5BACC0ULL,
    0xA0D3EB73852DEA0EULL,
    0xAC9E60B622F93C3EULL,
    0x6E958F3BAC50855FULL,
    0x882315A9B5E8FD4DULL,
    0x36,
    0x0B,
    0xB7,
    0xC5,
    0xC5,
    0x1E,
    0xBF,
    0x5E
};

const TwistDomainSaltSet TwistExpander_Ankaa::kPhaseHSalts = {
    {
        {
            0x358AA498D63006CDULL, 0xE762F1553063B09BULL, 0xE40A80486016089AULL, 0x56697D8DCF996590ULL, 
            0x34C0D49B021A08E5ULL, 0x03D5545D9B4AF6ABULL, 0x884CC3CC24515450ULL, 0x2274E9B393F9FD6EULL, 
            0x04D07F0469A70088ULL, 0x88652478D3C45F98ULL, 0xAE8F66093D246AFFULL, 0x46469F3EB5CE6048ULL, 
            0xDAEFE0148874D61AULL, 0x50F747E2FBB615DAULL, 0x8BFCC9A2B1385149ULL, 0xAE66CA6EA39C1961ULL, 
            0x5B980D4900073E0AULL, 0x5D6C412B45B56A47ULL, 0xB54A7071362A9AC6ULL, 0xFF89CFBE370074A0ULL, 
            0x9C9A626A92E63973ULL, 0x109B1E3FDA96F99CULL, 0x6023573B70CB3FC6ULL, 0xCDB7A75152B268A2ULL, 
            0x054C0AD347E5D28BULL, 0x5E523061EE4D86B6ULL, 0x3D6DCA91BDD0C58AULL, 0x225A13F0532312D1ULL, 
            0xBEF7F6709D810D68ULL, 0xBF396CFFAAD05081ULL, 0xD45298EF16A14B61ULL, 0xEC72AC814AAF32C8ULL
        },
        {
            0xCCD3C34CDA5D20C3ULL, 0xF8AFF716A5F71CA6ULL, 0xC53231B8438F0AFBULL, 0x14C4CB64AF370C35ULL, 
            0xE88A1D00661E06BFULL, 0xD97E32293481D6EBULL, 0xFAD8DDD4C0E37F89ULL, 0x100197550350CE45ULL, 
            0x58E65C9CD8607477ULL, 0x5A93E213513A16B3ULL, 0x510A423E045E929EULL, 0x0B997355BA3E15D1ULL, 
            0x2D0D21723F53402FULL, 0xFCA43E0AF3A9F3C6ULL, 0xAD8257D4D978ED48ULL, 0x9604B81EAE592106ULL, 
            0x32A7C9519992A63DULL, 0x819050DBED64E2A0ULL, 0xC18E0781AF7C0CE6ULL, 0x937B1656A875047DULL, 
            0x66CB782DE502E472ULL, 0x87E8962C24702E64ULL, 0x8770DB8E7315F8A3ULL, 0x9BE896BFD0F9ACDEULL, 
            0x9BA3F7FA561FB3FBULL, 0x642B4FAE4A3F319AULL, 0x1C824CC16DEA3FF4ULL, 0x7DFF55199B153D0BULL, 
            0x50071BDA553D1D72ULL, 0x575D4F7627132C94ULL, 0x80B9A9D49895B298ULL, 0x8E6A69F27013654BULL
        },
        {
            0x84260748F1AF9774ULL, 0xD7B219AF84176014ULL, 0xD7672F1D9004E32EULL, 0x23AD9086D2D95CCEULL, 
            0xC6FB8581BD18D375ULL, 0xF3BF945EBDAA8937ULL, 0x0256177EB746BECFULL, 0x1AEBDF5B0FB0B472ULL, 
            0xBBB71944C7E049D7ULL, 0xA130DF595E27FA22ULL, 0x6724B5A4A3E2DC58ULL, 0xDC51D7B2BCA998BEULL, 
            0x644DE33B10A9AD6BULL, 0xCFD32D32A7309933ULL, 0x53829F7541AF7359ULL, 0x0A39DA180D634B67ULL, 
            0x00DA8DCEE6EBAFDAULL, 0xBFD801AD635D2204ULL, 0x2AC3AF6D07C2F470ULL, 0xED46C7AE852E41BDULL, 
            0x2A7957D2C026D05FULL, 0x152DFE21DD96E29BULL, 0x77B3F3021829BD59ULL, 0x86B3C0B5DF5D6CBEULL, 
            0x79F83A2978E2E0E9ULL, 0x51CD237DD3BAB8A4ULL, 0xDDC648EDA575EEACULL, 0x78E421E58B5050FDULL, 
            0x3856331A3618E666ULL, 0x9ACA84F87B15AD78ULL, 0x7EED22FEF4994CCCULL, 0x1882A225E20B3231ULL
        },
        {
            0xA3C273AC2D1C72E6ULL, 0xF609D6790D5916A2ULL, 0xA128589FB6DBE719ULL, 0x6D9FD380B1CB8AC0ULL, 
            0x7BFDACE2854EF417ULL, 0x12E8DBCC820CCA66ULL, 0x00083C41638CD05EULL, 0xA4B25BCFABE39C61ULL, 
            0x3C5389F60023139AULL, 0x50A6DE4D3727D790ULL, 0xE05D46FA2D7A5251ULL, 0xC6A4E2B3FDEF5977ULL, 
            0xCE282EE7895D2779ULL, 0xF20E0CE05D79671DULL, 0x1EEF1808CCA04B6CULL, 0xE422C23C450914E3ULL, 
            0x2DBD393F5B16FAF4ULL, 0x8C652001B5BDE78CULL, 0x59B2D4FBB77B8F83ULL, 0x0705E55F7C6BAA14ULL, 
            0x003AD2102402EB62ULL, 0xCBC7733148F07303ULL, 0x1C382EB593D2648AULL, 0xD8F7E098C156F0F8ULL, 
            0x3596C247A03D4916ULL, 0xED4D6DA911B215A1ULL, 0x91FBECBCBBE0D695ULL, 0xEA690967DF60F278ULL, 
            0x1DF3625D20BC14F4ULL, 0x467917624FBBB930ULL, 0x1F36DD9BCCA13532ULL, 0xB0C8203852D730A0ULL
        },
        {
            0x244A1DBA08E5E998ULL, 0x29E6E52B0F21FA42ULL, 0xC514B04AD9FB44FDULL, 0x9B401A1CAA6D5294ULL, 
            0x49578B8DD047A17DULL, 0x7C3DF9258F975F93ULL, 0xF19281FA81976A3BULL, 0xA892F7509CF224BEULL, 
            0xD1791E2A150D5952ULL, 0xC1955BF0A35FB494ULL, 0x1F3E29883D570BAEULL, 0x0299954B7EC2ABBFULL, 
            0xE1AFAC27092C9122ULL, 0x693977BA4775460EULL, 0x5C91D55061B2BAEBULL, 0x86327F704F9FF8DBULL, 
            0xDCE20594F762B6B8ULL, 0xEF8799260B52B249ULL, 0x2CC82A0C4E857741ULL, 0x7464F6CE910C3CA6ULL, 
            0x74FD0D1A690DFA2AULL, 0x4AF0DB577DDF140AULL, 0x4D4D1352F6390D09ULL, 0xA1747AD192EFBB7CULL, 
            0x818CD0A9AA3B8155ULL, 0x98049A843DFF7557ULL, 0xB5A792FABF7F16C8ULL, 0x5DF8F6086778EFFCULL, 
            0xCC91E186883D9D32ULL, 0x3C24C1A8F0F7421AULL, 0x189D70A3DA147B00ULL, 0xE2AD01BD203571A9ULL
        },
        {
            0x5530CB90E7B3C60DULL, 0xA8FE957BC95D5889ULL, 0x64CDE5E04CB7C1E8ULL, 0xA008BEAF2093C0BBULL, 
            0x5A2C61F2DFE7F861ULL, 0x4E8032EB4A59486CULL, 0xE65D6910223E2C66ULL, 0x89CE19BF05238D39ULL, 
            0x4D38E6FEB17B7CC9ULL, 0x87FCAC6CA42ADC5DULL, 0x0D520AF5D1573593ULL, 0x49B495ABE7CB06A2ULL, 
            0x44BAD697DF9747ABULL, 0x72B2492B187683D1ULL, 0xB865D7927295C8E5ULL, 0xD217A2A1976A8029ULL, 
            0xC603468D52085D21ULL, 0xD02917D9DB784D21ULL, 0xB41CBA1914C571DFULL, 0x7401760BC5B545F4ULL, 
            0x67C7CC20B2F6AE84ULL, 0x901543167F2AE472ULL, 0xD9BA0F4C42D89C64ULL, 0xA191FA66BE01B444ULL, 
            0x8A45E32813220FAEULL, 0xCE6B28F7D648AB79ULL, 0x81F83CFD25BE54FDULL, 0x0BEEC6B454077F5AULL, 
            0x2E1FD0507190AF45ULL, 0xA65FF8AFE55656C4ULL, 0xEB961C10A583204BULL, 0xECDA00462BBDD075ULL
        }
    },
    {
        {
            0x0D64146D8F28EE27ULL, 0x3399489845DF4C54ULL, 0x7A1A01ED4F01215CULL, 0xB538C378900FA073ULL, 
            0xFE4B62B00F1778C6ULL, 0x12FC49054285A986ULL, 0xC2E3A7A7EC4E729FULL, 0xD8DC3DC6707CD0AEULL, 
            0xDB197836D3BA984DULL, 0x3F5F88D74DCB87C6ULL, 0x92CA16D607881620ULL, 0x7E6F2F0581C7397FULL, 
            0x6A858D336D379E62ULL, 0xC788371E62A69872ULL, 0x136E43E183B13E5FULL, 0x0D3F9E452D53AA98ULL, 
            0x6106521979C15B00ULL, 0x0A76375DFEF344ACULL, 0xDC899C81FA467476ULL, 0x59B3F5F004F5C8BDULL, 
            0x0C4AF243927E55F8ULL, 0x1CF412773ABDDDA8ULL, 0x7418AFE365DB1159ULL, 0x20355948EDA97FC8ULL, 
            0x4DB17F5A9C4FFA72ULL, 0xDEC30B0E02365CEBULL, 0xB97E8A4378218615ULL, 0x6F5226EEB1C120CEULL, 
            0xD7C6A013241FBA2AULL, 0xABF5E2670B1ADE00ULL, 0x354952BC745317A3ULL, 0x991676BD38769866ULL
        },
        {
            0x9BAEF9953C32F557ULL, 0x1C37734FE2D89EE4ULL, 0x93D799CF6C96C093ULL, 0xAFF04103E6C0C164ULL, 
            0x65C0BAE7419A4880ULL, 0x401215A6EFAD3C50ULL, 0x344A4190B6F9C785ULL, 0x07FAC8634DBC8B8BULL, 
            0x54E434F7EFEC983DULL, 0x62D973EFF87BBCD5ULL, 0xF5002370EADE1E44ULL, 0x90802D596C9482F4ULL, 
            0x33CB5CB735E1C919ULL, 0xF9BCB292AC6A990EULL, 0x5A70FFA6DC5577E5ULL, 0xE73AF259BFEAD402ULL, 
            0x46F55708A19FF6F9ULL, 0x5C0693C20FAF2CA0ULL, 0x648A3CD1A6F20ED7ULL, 0x77F1525ACDFB2CF1ULL, 
            0xC7E3DBF46807B932ULL, 0x66696BE091E34A7BULL, 0x11F8054BC4A43421ULL, 0x21FB27C05D2A3547ULL, 
            0x40AFABD4E9FCD7FFULL, 0xA4D1F9A75D3AC7D2ULL, 0x114F57CD4078FB45ULL, 0x0C8799E0AF6B4DF0ULL, 
            0x5EBBE5D7D08E0B21ULL, 0xA6AAB796A846D54AULL, 0xA092248AF56C2C88ULL, 0x7A81D70383436ED8ULL
        },
        {
            0x25EB612E3A72DAAEULL, 0xC3FB1FD7961AF924ULL, 0x91A49D99701E9DCBULL, 0x517788C49D518B83ULL, 
            0xBFAA6FE18DD1A397ULL, 0x69B967438A12729AULL, 0x2FF696D400C2A53DULL, 0x92D0289C3C2299ADULL, 
            0xD4502365CD34925CULL, 0x5BAC2A0CF8DBE45AULL, 0xE556DBE2ECEF49CEULL, 0x578F5CECCDA9B733ULL, 
            0xD8B93F0AC0E7B498ULL, 0x6F02F2298308ECADULL, 0xCE8E5831245E40F7ULL, 0xECE236E592054970ULL, 
            0xB00F02A28F1508C5ULL, 0x26BCFC4E42673A45ULL, 0x239389BDBB46CEF9ULL, 0xDFF88ADAD87BE7CEULL, 
            0x29734978BCC91F83ULL, 0x6B4A2584F11DEA5EULL, 0x12E4E51529C2CBB6ULL, 0xEDCF3DE23E9BD8F3ULL, 
            0x971162180F32BCEFULL, 0xD6EC13545CE25B75ULL, 0x734258BBB1D31298ULL, 0x53789ED39BEBB379ULL, 
            0xE535AF30A0F0339BULL, 0x54D3996B7D92C538ULL, 0xFEA0F8609A6E50D3ULL, 0x5FEEBAD930D2B9B5ULL
        },
        {
            0xD893C7626F1C9D55ULL, 0x2899864709A6C7E5ULL, 0x2D0CFEC5A8C175D2ULL, 0xEC198BE91BAC3BA6ULL, 
            0x4C43C9BAF83C3A80ULL, 0xDBC1ACE1ECAABFDAULL, 0x1A0839477ACB7E69ULL, 0x7E70C23BF0E6D319ULL, 
            0xB101B66DEA2EAC9BULL, 0x5F87869ADE5C6E1BULL, 0xA2129F52B9DE96F4ULL, 0xB8EC64BD1E4C2FCCULL, 
            0xA48AFD45012D2BEBULL, 0x463D76E29E4FF49FULL, 0xF229A1036F2D78CAULL, 0xBEFA31CC2EFBA103ULL, 
            0xD8377AF17204AEFEULL, 0x35C168ADF69BD753ULL, 0x4C7D52FC756E48E1ULL, 0x76E5F77C4D2C283AULL, 
            0xDC7930B4F0467380ULL, 0xAB8DFEEE1E72D0D4ULL, 0xFEF7BB8627AD9B6BULL, 0xE5CBFE1746EEC842ULL, 
            0xA9E0B9377E756211ULL, 0x7085339F4297B39EULL, 0x621E0E9CF5A5CE4DULL, 0x00FDDA462C947464ULL, 
            0xAA52936745CEC155ULL, 0x992C1E59AC8D7F23ULL, 0x09CBB54418E7C2ABULL, 0x87EA0D983071F6E1ULL
        },
        {
            0xCAEFF547396E0BCEULL, 0x06E71D3855F94A59ULL, 0x3CA93655FB7BE5F8ULL, 0xD783B4F39E95A4CFULL, 
            0x1C475B5E291E7382ULL, 0x49ABD71DE06A8C17ULL, 0x0302B6E12E89EDEEULL, 0x2B962BFDB3E92C74ULL, 
            0x025AE4DABCDCA24DULL, 0xAE6629A7872C6178ULL, 0x840A5C2230AE063DULL, 0x1ACBB455F6D4B93FULL, 
            0x4A0F3D8C2BC7AB7DULL, 0x8DC221633C5FF7E6ULL, 0x20C349ACB8333259ULL, 0xB670D35C716931CFULL, 
            0x921BDC96A9C1D514ULL, 0x2F0090FBDB810689ULL, 0x501C74F2BEF4278EULL, 0x812585D6343AE6C2ULL, 
            0xF7C7CC4824F86418ULL, 0x224D89E6C1093174ULL, 0x501C3783F34E719CULL, 0x43EE1F805B82B554ULL, 
            0x84583E362D5B15F2ULL, 0xBDC10A788B3E0006ULL, 0x7FB54ED24A402F16ULL, 0x99A9F03F7B1342F3ULL, 
            0xF229C0003FEF1D59ULL, 0xE8D43B18B537BC26ULL, 0x161B736F2941F13CULL, 0x8AED457B207CEA67ULL
        },
        {
            0xE83D73C7A08BD99AULL, 0xF96C3B569063E96AULL, 0xB9B35C607A3C5891ULL, 0x313D7AAB08CB092AULL, 
            0xCCB4F70666D63D9CULL, 0xD26D7B86BF839A9AULL, 0x905F1204579D7FFFULL, 0x3E6FF5F40222778AULL, 
            0x84C126C46A4A8E8CULL, 0xA91D73BCA473F850ULL, 0x7FB7A4F710C759CFULL, 0xDCD8C812BF821270ULL, 
            0xAAC501351773FA01ULL, 0x1FE28D981F15A90EULL, 0xF96ABAFB28A76B24ULL, 0xBE1378E73380C3F2ULL, 
            0x4670C99D96690A4CULL, 0x6B8C3FD5CA97DB17ULL, 0x634987E25C29E743ULL, 0xFD3CFB67D51CC160ULL, 
            0xDE7802C82625285FULL, 0xF592D81D24B11F65ULL, 0x769398637A3DDDE1ULL, 0x43371D9B05A0F7F6ULL, 
            0x4EA843C5F6EA17D1ULL, 0x288DFC63A7138FB9ULL, 0x22B8F83EF9EBB208ULL, 0x909FC8BD394C002CULL, 
            0xD84DDB977126137EULL, 0x7099483624EC8EE6ULL, 0x9295888AF7D43460ULL, 0x5B50506F042EBD0FULL
        }
    },
    {
        {
            0x9DC5A1B9E7E4CD57ULL, 0x7D566060D7640A13ULL, 0x0589D8B1E8FC13C9ULL, 0x1F3FEA9D5A30E5F8ULL, 
            0x1DA7F6769174DEF6ULL, 0xEBF2D6EF2DD366DBULL, 0xF4A3CF2981F128EAULL, 0x405374AD80769516ULL, 
            0x3EB6C896FBF99C47ULL, 0x1CE166A69AF8182AULL, 0x7154731999F73581ULL, 0xA93E4C591AF3B6FAULL, 
            0x3CD617711BEEA4C0ULL, 0x3BF9B158C965B7D9ULL, 0x8CB184CCE8BDDF24ULL, 0xEF20CFF86E2172ADULL, 
            0x550A2F1704B875F4ULL, 0x9D9522B8596A276CULL, 0xE4033AB8F3B07F0EULL, 0xC0FBABF907FD8235ULL, 
            0x2966A279CC1EE1A1ULL, 0x308AA42D49FF0274ULL, 0x83AB34FD89AB57E0ULL, 0xD06060C672B7E999ULL, 
            0xC4474D0E91360A2AULL, 0x82A5D8F9DD9BB454ULL, 0x5937B44409803C4BULL, 0xFE7EB9462F7D29ABULL, 
            0x0805F07222060899ULL, 0xF2BB94317FF99A78ULL, 0x089A2E9BF9544882ULL, 0x23DBA0464C4EC20FULL
        },
        {
            0xF5ED192186E6A12EULL, 0xB3A2BC8E9A73D118ULL, 0x554513CF6E4C9534ULL, 0x2910841098AF6936ULL, 
            0x827EFD92F0DF527AULL, 0x322037498F0BE0D2ULL, 0x315000ED64E8197AULL, 0x47833B5F8E341913ULL, 
            0x8DBCF29B52B7D775ULL, 0xE6877F883777765DULL, 0xBF8796D72CBB341AULL, 0xCF1D5D3CEF8BE209ULL, 
            0x62D604642E7723C4ULL, 0x4A2EEBBE43A906D9ULL, 0xFD26F4B230031692ULL, 0x0C04AC354485683DULL, 
            0x17387C71FD2766B4ULL, 0x6CA89806E787829CULL, 0x51286E4B09E8BEFDULL, 0x931A444C869ACEADULL, 
            0x46D60626B0DF4A0CULL, 0x0CF4778CA81C241CULL, 0xF250ED0E4870018FULL, 0x87EB770580FAEFD8ULL, 
            0xDFF52D20631B30BBULL, 0xB94C8332224502DBULL, 0xD73A47AB7B17EE0DULL, 0x87DDC05EDD0ECCF3ULL, 
            0xB1D151E8A5013961ULL, 0xC00EBFBADF5E93A6ULL, 0x9E71C060A9AD43DDULL, 0x009743ECE0434267ULL
        },
        {
            0x3D55A8816763A174ULL, 0xEED0B20F9FD13822ULL, 0xE09184D20AD90DCBULL, 0x5C89AB558C8E0B6CULL, 
            0x081CC59462AA2439ULL, 0xD04E94781EDF9F73ULL, 0x6A6D61B58CD4D0FBULL, 0xAE4338F7C9E47703ULL, 
            0x75A99E0B1032FA12ULL, 0x6068761FC634D292ULL, 0xCA0CDFD24C30D183ULL, 0x5082172D4D62D362ULL, 
            0x3B503CF8B07D9DA4ULL, 0x3081635E09D9A4CCULL, 0x2F8CFEC0D07DCC0EULL, 0x7AFA28631B87E820ULL, 
            0x05A511A9E8349291ULL, 0x251F9606B09677CBULL, 0x90BD892DD763CDB6ULL, 0xC3B694E043BBD147ULL, 
            0x41FE043282D37CB3ULL, 0xD113ACFA114F7D87ULL, 0x3059BCDC60BEB17FULL, 0xBD3B1A7F5BCD4390ULL, 
            0x072532215709D86CULL, 0x96FB2685BFB06C14ULL, 0x34750AA8DDC6BA88ULL, 0x6E8478155EDE84E8ULL, 
            0x545B2D04764BC4C6ULL, 0xAC5B11FADAB82D54ULL, 0xEFA1FAEBF0D3E9E7ULL, 0x6F0EB93AEDD99F40ULL
        },
        {
            0x85A96DF9B4A06737ULL, 0xDBC44A43CEB32D02ULL, 0x991DC92A85168A4DULL, 0x857474C7D868AB3FULL, 
            0xA961BE72DCE58890ULL, 0x274ADEDCFE48112DULL, 0x7B6AF4629E213B90ULL, 0xCFC5BB2EB90085B3ULL, 
            0xB6650F49F49B2F84ULL, 0xE09E05972FEBAA27ULL, 0xA805C03148841D2AULL, 0xC08BD436CF0EDC79ULL, 
            0xC5E32423B01C866DULL, 0x1701585017E734A7ULL, 0x61A3545662F27C8DULL, 0xC9D6B4F6015A68C3ULL, 
            0x2C27CC385A3A4B64ULL, 0x69836D6745F207DEULL, 0xFBA393783E1745DAULL, 0xD5CA5B314A6E2B35ULL, 
            0x6AA02FF67141ED26ULL, 0x086DFFCDE3819D4BULL, 0x3260D5D7113FF7E4ULL, 0x19F7EBCF5734D989ULL, 
            0x156C52651CA052FDULL, 0x27F97679BA662529ULL, 0xDFBE2B5005E028F0ULL, 0x1B60E369BA8EAA55ULL, 
            0xA856E220F874F1ACULL, 0xA6C3F5EEC960E578ULL, 0xBC0683250F271320ULL, 0x208C350F781BEC0CULL
        },
        {
            0xE5DC6935831A1A6BULL, 0x340BA021480A6456ULL, 0xEDC41895E1B96A81ULL, 0x2328EFD9AB4D4782ULL, 
            0x9F617D8D60BE878CULL, 0x2B2E2CCDD0EA7FB9ULL, 0x3A469C99E055C55EULL, 0x3D91A523C7012B3DULL, 
            0x787743E443D73803ULL, 0x4AEE6D701E58368DULL, 0x084A8F8E49133082ULL, 0x52DAA0BBB68FE8AAULL, 
            0x7746D7D9E89E40F7ULL, 0x7DE6A0A9F84CC1D3ULL, 0xC27D9209E3ECE2E4ULL, 0x8DA4967DB24E926FULL, 
            0xD9942B5AF3627C63ULL, 0x8A5E58C7FFE7ED72ULL, 0x321B332A44E10497ULL, 0x5329B278E92A55ADULL, 
            0x08026FCABDF3C455ULL, 0x59D46E08070D56B7ULL, 0xD31835FDD15C8EC0ULL, 0x5A4501222793CCF0ULL, 
            0xD664D4B97FDBC2EFULL, 0x068E66935C98BD8AULL, 0x08C43358358B36DCULL, 0x8290D43DAE93CA4FULL, 
            0xD237BED3564E88C3ULL, 0x1BBB607820E2AB36ULL, 0x2E0115216A27935FULL, 0xCFC162C6DD1D3572ULL
        },
        {
            0x8EB1F655E440FFBCULL, 0x16E687CAEC48D213ULL, 0x2B5CEF014B42DBADULL, 0x2E967B1916A624D9ULL, 
            0x4D28DC64D2F21C19ULL, 0x3D08B86EA05A65AAULL, 0x5AD32CA6DA6C9F66ULL, 0x98997F41091B268EULL, 
            0x04F644B5F77053B7ULL, 0x761812F71378B34DULL, 0xBAB80DE90B461AB7ULL, 0xC46EFF522F32FC00ULL, 
            0x6244864A1B4D3176ULL, 0x3AFAE83822CE3456ULL, 0x9A81EE6511807075ULL, 0xFA4CBC94A39C066CULL, 
            0x640D135301BC9715ULL, 0x5F016D2358AF680CULL, 0x20FD2C3E8C500D29ULL, 0x68B6B6F3CB47528CULL, 
            0x2E0A8A0BD7C185C1ULL, 0xB82D1C2AAE525308ULL, 0x533338A5B5A1BBCAULL, 0xD035AFD1B0D2CE53ULL, 
            0xD71A5A179ECAC62AULL, 0x9073331573089985ULL, 0x6B0C4E42207FC2BAULL, 0xC043CC4F4E6947A0ULL, 
            0xC6CA4F3D311A0234ULL, 0x23F05E9E3612FAD4ULL, 0x29E6B05B29B29683ULL, 0xCC060FDABA8CB394ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Ankaa::kPhaseHConstants = {
    0x3E7EB473B5B94F6FULL,
    0x080E15817646C0ECULL,
    0xB771B2FCE35CE8E7ULL,
    0x3E7EB473B5B94F6FULL,
    0x080E15817646C0ECULL,
    0xB771B2FCE35CE8E7ULL,
    0x6792A0E4B12AE6F9ULL,
    0x244B33F2E9192CA8ULL,
    0x16,
    0x2B,
    0xD7,
    0x1A,
    0xBF,
    0xF0,
    0x1C,
    0xC9
};

