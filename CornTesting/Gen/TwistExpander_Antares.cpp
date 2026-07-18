#include "TwistExpander_Antares.hpp"
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

TwistExpander_Antares::TwistExpander_Antares()
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

void TwistExpander_Antares::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9735FCB54A94B963ULL; std::uint64_t aIngress = 0xF07A40AB354FD83DULL; std::uint64_t aCarry = 0xADDCA929C5599097ULL;

    std::uint64_t aWandererA = 0xACDAF3AB30F661D5ULL; std::uint64_t aWandererB = 0xE6B2CEA06508D541ULL; std::uint64_t aWandererC = 0x922E7FC5FAC080A1ULL; std::uint64_t aWandererD = 0x8644CD99E4BBDC18ULL;
    std::uint64_t aWandererE = 0xC5F2E4223C010A31ULL; std::uint64_t aWandererF = 0xE4EBEC5E24F304BEULL; std::uint64_t aWandererG = 0xA75327D2C1646B10ULL; std::uint64_t aWandererH = 0xE8180C769C66996BULL;
    std::uint64_t aWandererI = 0xBA81C9834C5E7C13ULL; std::uint64_t aWandererJ = 0xE94BEBB3FBAD1822ULL; std::uint64_t aWandererK = 0xB7F4DF0F8B97C9BCULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11661099767013222229U;
        aCarry = 10834689988732621617U;
        aWandererA = 10392783708125831435U;
        aWandererB = 11269950356466675189U;
        aWandererC = 16819050805216763287U;
        aWandererD = 16518854538980633399U;
        aWandererE = 9942291108285019122U;
        aWandererF = 14291977611753160634U;
        aWandererG = 9555144681665302595U;
        aWandererH = 10228919260170179321U;
        aWandererI = 15733004801630071135U;
        aWandererJ = 11213632937691877697U;
        aWandererK = 9353025510148985160U;
    TwistExpander_Antares_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Antares_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Antares_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Antares_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Antares_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Antares::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB30EE8FF2397AD1BULL; std::uint64_t aIngress = 0x80BF52DBDE7E5CCAULL; std::uint64_t aCarry = 0xE57E9824C78C1338ULL;

    std::uint64_t aWandererA = 0xABDD924C00FC351DULL; std::uint64_t aWandererB = 0xE7ACE126DA303ABEULL; std::uint64_t aWandererC = 0xDBCDADF55CE20DA6ULL; std::uint64_t aWandererD = 0xC1C4E2BB7284A2BCULL;
    std::uint64_t aWandererE = 0x9115BA9B7F9E3CA5ULL; std::uint64_t aWandererF = 0xE7186E0B92AC8CFBULL; std::uint64_t aWandererG = 0xDDCEF0311B86AD6DULL; std::uint64_t aWandererH = 0xA24F2AFCC90DA90CULL;
    std::uint64_t aWandererI = 0xB4D21E20A1D60AF2ULL; std::uint64_t aWandererJ = 0x93DBFA7693C47D2AULL; std::uint64_t aWandererK = 0xC5EE5284A4BE8243ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11402793833752996937U;
        aCarry = 11708176909508139931U;
        aWandererA = 9931797702411173172U;
        aWandererB = 10869812429760366498U;
        aWandererC = 13764803260374962148U;
        aWandererD = 18203680673199578153U;
        aWandererE = 10672589582253963590U;
        aWandererF = 14590422952017018542U;
        aWandererG = 14957283196713786677U;
        aWandererH = 11854926342887389051U;
        aWandererI = 17128763341983209860U;
        aWandererJ = 10103494883632362978U;
        aWandererK = 13670443126664973066U;
    TwistExpander_Antares_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Antares_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Antares_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Antares_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Antares::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xB988B070A862ECC3ULL;
    std::uint64_t aIngress = 0xEC32D347535C911DULL;
    std::uint64_t aCarry = 0xFDAE191E7DCD75AFULL;

    std::uint64_t aWandererA = 0xBA5B08243745DC6FULL;
    std::uint64_t aWandererB = 0xE2DC7100CCF9CD95ULL;
    std::uint64_t aWandererC = 0x92721AE413A2ACD6ULL;
    std::uint64_t aWandererD = 0xC834AA4D8700A658ULL;
    std::uint64_t aWandererE = 0xD250322FD1E5551EULL;
    std::uint64_t aWandererF = 0xF1E1B2304074F0AEULL;
    std::uint64_t aWandererG = 0xB451F6A09DBAE666ULL;
    std::uint64_t aWandererH = 0x8AB4FB25D16DB6DEULL;
    std::uint64_t aWandererI = 0xA09CC6EAEB5ABFB1ULL;
    std::uint64_t aWandererJ = 0xC9002334FBF5934CULL;
    std::uint64_t aWandererK = 0xF7754CEF536FB60FULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
    ////////////////////////////////////////////////////////
    ////////        Phase A
    ////////
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts), aSnowLaneD, 0);
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
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseEConstants), &(mDomainBundleInbuilt.mPhaseESalts), aSnowLaneD, 4);
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
    TwistExpander_Antares_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Antares_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Antares_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Antares_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Antares_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Antares_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Antares_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Antares_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Antares_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Antares_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 9 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1861 / 1984 (93.80%)
// Total distance from earlier candidates: 14924
void TwistExpander_Antares::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1107U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1450U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 485U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 723U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1440U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 960U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 493U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1071U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 605U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 434U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 116U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1438U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 721U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 672U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 78U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1875U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 100U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1346U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1259U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 349U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 748U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1218U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1201U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1881U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1360U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1640U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 283U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 647U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1124U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 179U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1235U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 483U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 518U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 71U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 949U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1399U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1604U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1163U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1619U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 21U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 301U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1437U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1101U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 77U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1700U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1194U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1095U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 938U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2039U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1712U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 35U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1947U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1920U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1885U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 274U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 124U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 41U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 449U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1096U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 844U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1652U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 335U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1584U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1621U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 691U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1565U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1705U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 3U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 205U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1033U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 989U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1314U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 104U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 635U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 311U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1635U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 717U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 88U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1337U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 61U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 160U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 749U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 558U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1672U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 384U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1097U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 360U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 625U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 122U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 391U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1871U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 744U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 210U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 848U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1421U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1293U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1374U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1427U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 109U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 920U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 324U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1532U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 372U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 649U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 700U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 628U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 32U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1027U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1210U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1452U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 968U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 826U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1549U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 261U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2032U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 440U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1511U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1994U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 803U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1479U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1643U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 868U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1467U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 251U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 299U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 581U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 641U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }
}

void TwistExpander_Antares::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x8CA6784DCC498D69ULL; std::uint64_t aIngress = 0xCBF1D00CCC8E0572ULL; std::uint64_t aCarry = 0xEE1CDC7ED8B0586FULL;

    std::uint64_t aWandererA = 0xB45CD85AFCFCC5DCULL; std::uint64_t aWandererB = 0xCE66C447792C19EFULL; std::uint64_t aWandererC = 0xF0273D16484F603AULL; std::uint64_t aWandererD = 0xEE3ACEC793B9EA64ULL;
    std::uint64_t aWandererE = 0x8CCE8043800587F6ULL; std::uint64_t aWandererF = 0x87076F1F391CBD05ULL; std::uint64_t aWandererG = 0x8F6B8ABD23296E13ULL; std::uint64_t aWandererH = 0x9B1DBEA081808F9DULL;
    std::uint64_t aWandererI = 0xD19E831A46C34944ULL; std::uint64_t aWandererJ = 0xD7F3FB5C17AE6ADAULL; std::uint64_t aWandererK = 0x89F4B269332EB2F9ULL;

    // [seed]
        aPrevious = 12571954423364986193U;
        aCarry = 13733775475267513655U;
        aWandererA = 9429981108298238638U;
        aWandererB = 14851979134467055600U;
        aWandererC = 10302623072839534738U;
        aWandererD = 14095531819522843423U;
        aWandererE = 12151119875863941286U;
        aWandererF = 10950183059217585750U;
        aWandererG = 17735334603023636640U;
        aWandererH = 17940403526914806370U;
        aWandererI = 15281148810519286292U;
        aWandererJ = 16927857948655027207U;
        aWandererK = 15236322810978219360U;
    TwistExpander_Antares_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Antares_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Antares_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Antares_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Antares_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Antares_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Antares_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Antares_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Antares_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 9 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 4469; nearest pair: 496 / 674
void TwistExpander_Antares::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6817U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1612U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3335U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4953U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1049U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4993U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6968U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7085U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3192U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8037U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2750U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2893U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3999U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7792U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7178U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1989U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1477U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1832U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 523U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 38U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 264U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1672U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1240U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 228U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1157U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1511U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 863U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 72U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 401U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1210U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 375U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1580U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1664U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 617U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 801U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1108U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 9 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 4456; nearest pair: 498 / 674
void TwistExpander_Antares::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7442U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4329U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2730U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5871U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5433U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2726U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5116U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4631U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7424U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3156U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1587U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4194U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5712U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6377U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7097U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2948U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1760U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1847U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1464U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1622U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1167U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1873U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 544U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 581U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 686U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 75U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2035U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 165U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1177U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1188U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1112U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 986U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 2015U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1127U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1008U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 435U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Antares::kPhaseASalts = {
    {
        {
            0x148F0A80BA3521CFULL, 0xE8BD507F69424DAEULL, 0x199522911865B4B3ULL, 0x6F6F84A086E44609ULL, 
            0x99DF2F40324DE31DULL, 0x1D6AD306ED6A5A8FULL, 0xCEC41E0E6270214CULL, 0x8FABCB66F6CAECFCULL, 
            0x447DECA6A6ED9694ULL, 0x44378AFD7571151FULL, 0xC8CD63B0CC496A1EULL, 0xB880B64B1D195A3FULL, 
            0x0602FD5DBF2ACEFFULL, 0xC5D26605EF0921D9ULL, 0xE560868049813411ULL, 0x609F5CCF928E0A4AULL, 
            0x412D6713D28CFF5BULL, 0xD7478AC56961A07AULL, 0x2EAAC7E228C7496EULL, 0xE1A4171425CBAAC5ULL, 
            0x0E4C141AA9F08F8DULL, 0x651FC7380EF39901ULL, 0x8FFD2AAE2E7DAB8CULL, 0x05DC333F71CC922CULL, 
            0x55ED137349ACEA0DULL, 0x0FF135C35E4FCD64ULL, 0x23FE0FC3244DE04DULL, 0x8F6A671578FA4803ULL, 
            0xCC33822CAD6C2AC4ULL, 0xE3A4B1C063E74EEBULL, 0x73742983B8DB208CULL, 0x3016F24216146D9FULL
        },
        {
            0x875CF0CD4F0D6A13ULL, 0x7D9FDF7EAD413469ULL, 0x326298E923C7892BULL, 0x509D36F6286D9DDCULL, 
            0xB9201969FC015155ULL, 0x47E40AE525137E6AULL, 0xE88AC78C8A8E13DDULL, 0x53BA79ED8DDA41EBULL, 
            0x6488D1E5B3B432BFULL, 0x33CA0042323750F1ULL, 0x7997ABE0EEEF261FULL, 0x318AEB0710576A93ULL, 
            0x5F64556A2E574268ULL, 0x2AC1A149B243E451ULL, 0x30AA84A4294D0739ULL, 0x9955C6B32115AD46ULL, 
            0x00A41C08BD6DBDD9ULL, 0xCD5FD1730705AD96ULL, 0x2AC7FD1F1A87101CULL, 0x74E9C53E123A47CAULL, 
            0x284C22B35FE5512CULL, 0x7ACB211BE5E26086ULL, 0x63723A7FB286B8EAULL, 0xA2D989C3556B1D5AULL, 
            0x935A2472A9FC513CULL, 0x66BE435D30573312ULL, 0xB13361FEA463CDC0ULL, 0x3B7684BF6010E62CULL, 
            0x44E25CE3408FCFE6ULL, 0xFCC762994A8A962EULL, 0x16AFE992321FE54EULL, 0x0CFF73E26AF0E229ULL
        },
        {
            0x93CA491F2245D3B7ULL, 0x651F11721EDBC79BULL, 0x47A5C706581C517DULL, 0x30B4085A02BBB1FDULL, 
            0x2F2BEFD48D4A1FB5ULL, 0x9AA0BCFF873F5546ULL, 0x34E5FE9703303A85ULL, 0xEEDCE41BA58906C5ULL, 
            0x24380CF424CB26A4ULL, 0x62D7FB7C7B392353ULL, 0x77DDFCC8F7691DB6ULL, 0x6DD0F176B106CFD4ULL, 
            0xF90F0C66701EDC92ULL, 0x370989E702F201B4ULL, 0xDDEDB0713887BB56ULL, 0x4276C3834FE6E1FAULL, 
            0x88D6E0B95874F667ULL, 0x866B071EEE7F1BFBULL, 0x94D34F46E74899F5ULL, 0xBCE1DCADBD5D0489ULL, 
            0x0932451BBFC8E965ULL, 0x3B102C2412807F14ULL, 0xE0F66173B9E0FF2CULL, 0xB1D4C23903FA1247ULL, 
            0x62881B41E36C95CDULL, 0xF2BFE5DE352790B5ULL, 0xA5E2EE40BC3B70C3ULL, 0x080F187C526234BFULL, 
            0x15FD625FF0CBBE3EULL, 0x0699CD38491EAF27ULL, 0xDFF4BD9853492430ULL, 0x49F545F32EEE9079ULL
        },
        {
            0xB0096844EB411D93ULL, 0xF2EEE1E58979A32CULL, 0x1D1F57BC2F955343ULL, 0x850830D94F27E1E1ULL, 
            0x4D4E0EBFD35816CEULL, 0xF3918637F8379FE3ULL, 0xA647BE154E34351DULL, 0xDEAC69D35BDB960EULL, 
            0x7F35E3918C1E563AULL, 0x9B361D1B0D399D3FULL, 0xACB6B946F287B730ULL, 0x8DD9996A57814817ULL, 
            0x7D0426A7CF1E9CEAULL, 0x88FB34CD2F93C8CEULL, 0xD5C1AF494FD14EAFULL, 0xF5DAD54C730ADF99ULL, 
            0x5B454A94753BA095ULL, 0x6EC0B77C3B026262ULL, 0xAE0D18772FF6ABA0ULL, 0x7A3D34EBA4AFA4A5ULL, 
            0x101DA84DD8954CB9ULL, 0x75A255932259D387ULL, 0x9F5ED441B6FE54D8ULL, 0x7F8FE4899C91E17BULL, 
            0x89A6D2144213F1E1ULL, 0x558504F0063A9634ULL, 0x9C7219C2120973B4ULL, 0xB6F1E7F6FC69FA0FULL, 
            0x1F3E22390E3D6BBEULL, 0x6C0A5405050C047DULL, 0x6452CD75A125DF07ULL, 0xEF7C23AA940532B9ULL
        },
        {
            0x015D6158EFDB93A4ULL, 0xCD11FFC3B4A3C802ULL, 0xC013D19070AB36A2ULL, 0xCB778A150FEBD607ULL, 
            0x0A65E4CAEB1FFE7BULL, 0xB300025FB951DA73ULL, 0xC9C1BDE94BF5247DULL, 0x8CF50BC51819FB11ULL, 
            0xA75314361FEA8945ULL, 0xF639C53468BCDC9EULL, 0x7C6B529EB06A1AE0ULL, 0x587C17CDEFC4AFA8ULL, 
            0xA16DEA85C8115A6BULL, 0xA43842B6F48A19D6ULL, 0x8511B95F37753A84ULL, 0xDCC35D166D034592ULL, 
            0x30E39913D5DAFF5CULL, 0x7FE647E05CDD050DULL, 0xC99070C27E9DC22AULL, 0x448547E6BEEE9F3DULL, 
            0xD99283B74A55AF7DULL, 0xB450E789DDF82213ULL, 0x06D3F54ECB4A9C80ULL, 0x465FB4DD40A9E7DDULL, 
            0xA311AAB171D105A8ULL, 0xFBA4F90B7BA30D63ULL, 0x205C09CF212ABF21ULL, 0x4E67B34A544E9DABULL, 
            0xADBDCE9CBCA861CCULL, 0x0686E8275D724B93ULL, 0xB2F19F29829C1935ULL, 0x28CA6218BB77FC4AULL
        },
        {
            0xD17BA96B3A2E9FCBULL, 0x4E58C74B376E36E3ULL, 0xBD44AB537CD6B8CBULL, 0x583D732A6E2F7E82ULL, 
            0xFD7E7EF90CDA3C2BULL, 0x0B8459800D419746ULL, 0xEF896B229171BF47ULL, 0x83A4B8E8514C5AFAULL, 
            0x9F252C4893DDD182ULL, 0x59AD8314CAC264B1ULL, 0x30C40E8E64ABCFE3ULL, 0x0B808B015DD99F85ULL, 
            0x10BBDE2F3E174551ULL, 0xED3F9AB02262FC7CULL, 0x2738B87E148ACB85ULL, 0xF3BFBA937016B98DULL, 
            0x3B385D06F202D6C6ULL, 0xA562F19B687DD6E2ULL, 0x1612F8602850B701ULL, 0xB2CE188550FC78ABULL, 
            0x4F33A9B93724EB15ULL, 0x2037C76231BA01C0ULL, 0xA84FFD9F7EA3E3C5ULL, 0xAE14AAF63862EF03ULL, 
            0x4CFDA221FF9FBCDBULL, 0xE7B8D61FAC6B45DFULL, 0x80B33182869EB9AAULL, 0x3FFDE60E895CCA9CULL, 
            0x18CB1E559F5B8007ULL, 0xE83ECC42B520D492ULL, 0xC29B653E0C2E5FB7ULL, 0xD720E0402DB6B9DBULL
        }
    },
    {
        {
            0x24C62A49F5565DF5ULL, 0xF461BB84E6860211ULL, 0xA468D33C27898D6DULL, 0x56EF9B48B9D9E5A8ULL, 
            0x226E6428FADCB1BBULL, 0xBDCA99C417E730D9ULL, 0xF78856A7D1818264ULL, 0x8F450A7F6A4B2DE5ULL, 
            0x71193519F7D395B6ULL, 0x3A87DB30FFAF2B57ULL, 0x038AD613EDDE522EULL, 0x56C5B38394F3BDD3ULL, 
            0x0D026E56FEC34DC8ULL, 0xA012B71973E59D6AULL, 0x1BCF105319F0F321ULL, 0xEBA9E007441D53A8ULL, 
            0x668F48E28698E671ULL, 0x6B0143819AD102CFULL, 0xB01C6B4E0C46433EULL, 0xA28457E45929CB5AULL, 
            0x14534DC131E21E2DULL, 0xC2BEE82B638A7937ULL, 0xE71F6AC58E16244CULL, 0x8A3D8F4913D0EC08ULL, 
            0x0C2CD91042950E6CULL, 0x796D2DF11081C237ULL, 0x766B4FE258E9D64EULL, 0x7E3350156FB39E6CULL, 
            0x2B114E6C8B2DE026ULL, 0x1FA4F16243963C66ULL, 0xAD6C504222CA5508ULL, 0x2E64666E12359EA4ULL
        },
        {
            0x1172BF5D3C2A973DULL, 0x34008DB299272BC0ULL, 0xADD3ACEFAD0A9A90ULL, 0xD69B729D1463683DULL, 
            0xEB860E8CA9FC78AEULL, 0x214D201C58C7B823ULL, 0xD4362CDED09112D4ULL, 0xF52B2BF93DA32C52ULL, 
            0xA425967E828A7E8CULL, 0x2C04638FFA4A26F9ULL, 0x4838C17C887E92D7ULL, 0x0AE1150D56178F38ULL, 
            0xCE69977865EBDF1BULL, 0x65EA70D5AE35CBA4ULL, 0xC09F182DC0B228ACULL, 0x430A669BA79CC762ULL, 
            0x2D523703CDBDC8F1ULL, 0x7D97CCF85F6B703DULL, 0x3E16EA32DD0A46E4ULL, 0x8D44D690F84F97F8ULL, 
            0xA4979FC2C6E5128AULL, 0xBFA6E86AAAF2BD9FULL, 0xC69524ADF3B5FFBEULL, 0x29103699E765FBECULL, 
            0x3B3593836D176BA2ULL, 0xFE8548758A6F9061ULL, 0x71F0D429EF7F6673ULL, 0x82C934CC37BCC33CULL, 
            0xBFBAD556207DACB0ULL, 0x49016DF664BF6B3BULL, 0x2FC3068E0FE3C7A4ULL, 0xB92FC91A835DA05BULL
        },
        {
            0x21DC6B7E1DD4D28FULL, 0xD837F6DAADBCAC25ULL, 0x9F3040B2FB23B322ULL, 0x914C3CC2B9FC2274ULL, 
            0x328365EAF5D5B81AULL, 0xDB7D12CDF66A4789ULL, 0x61F0148288A4C043ULL, 0xD3B57A700084436FULL, 
            0x3859662D000EC1FAULL, 0xB3ED203E1B2C1DBBULL, 0x58C401EC3A20E729ULL, 0xA17274AE3DD6ACEEULL, 
            0x15FAF23F81303554ULL, 0x3C2643E7EB0FF0BAULL, 0xE881D8304AE219A2ULL, 0x3E3D3FA56878403EULL, 
            0x1B2E13685CEFBFE7ULL, 0x384F0DDE89600FFCULL, 0x303196CE9F7E816BULL, 0x9D745A49B3BB30AAULL, 
            0x7359AE7BFFD0EF5CULL, 0xAE267B210E0A8DC6ULL, 0x4408ACDFEAB617F7ULL, 0x9101AF4255FA31E7ULL, 
            0xC3CBB1B5E195EC9EULL, 0x7A1BFDA67E715411ULL, 0x0C123DF469C04C0DULL, 0xE457E0BEFA01558DULL, 
            0x592F8C8F22BB133EULL, 0x0144552B7A7F8878ULL, 0x255B3FD9DA769E00ULL, 0x48B42AB3322A4177ULL
        },
        {
            0x1F482DA74AA54927ULL, 0x47BD755D8A23D8D9ULL, 0x5471C5DC5D2F6B10ULL, 0x91A03C8B5BCBF077ULL, 
            0xB74E0AC874759498ULL, 0xBEC98CD6FAF5E70FULL, 0x522747128C629B95ULL, 0x16A36D5BCEBE86F2ULL, 
            0xD66F0E52D73A2AE0ULL, 0xB73E245FECFFE0A7ULL, 0xB25B3FE99C29A012ULL, 0xE4CEF262E8FD9358ULL, 
            0xF9D3ACD81B25EA60ULL, 0xDCC6B15C16EFAD07ULL, 0xA43A0107D3BEADCBULL, 0x7B3F1F3A946AE45DULL, 
            0x73C1D6EE431B08C7ULL, 0x987D33E7E6F03CB6ULL, 0x8C2E295F2D786AB3ULL, 0x204D7926300B9428ULL, 
            0xBE45AC196CB91F46ULL, 0xE0FF6037D09B81D4ULL, 0x64A6A5002FA93AD2ULL, 0xEE70C21D4EE70BEEULL, 
            0x7CD103FF80B24C04ULL, 0xBE44850BEF3E485EULL, 0x50D9F2B3AF4FBC6EULL, 0x618EDB300A936DB5ULL, 
            0x750CA7A982BF4898ULL, 0xEA9A09F8377574C0ULL, 0x438661D95EE6CC69ULL, 0x42237EC6F70FD339ULL
        },
        {
            0x89634CC0E8A131E6ULL, 0xB1682F6A74F1111CULL, 0x87E02603479F5460ULL, 0xF1931EBC635E1971ULL, 
            0x7CBDC7275D410F24ULL, 0x91419E0812AE7FADULL, 0x4E4012873DCCEA6EULL, 0x684045711F4FFC53ULL, 
            0xCD592484CE692871ULL, 0x57DB454B737326F5ULL, 0xDFB74CD7D998D72DULL, 0xFB16981F09971E5DULL, 
            0x00EC81A2403B8F14ULL, 0xC2C3B4869F99ADC8ULL, 0x7C25A7897F119DC0ULL, 0x0A2AE51FFFA0D88CULL, 
            0x795A3C7A128E3241ULL, 0xA0DC9A352BF45115ULL, 0x448BD75D825E2DA0ULL, 0xF01E7270E613EC39ULL, 
            0xC351C368C3A2435CULL, 0x3EFA2D456883612FULL, 0x50625C291D34990DULL, 0x6055A4E4F8B410AEULL, 
            0xD6216ABE07F75406ULL, 0xD0FB2CBBCAB00532ULL, 0x7E2E4E3C2B78FFF9ULL, 0x9D72B674F7D98BFDULL, 
            0x002B22BF9EA0B5FAULL, 0xB40846C8508FA583ULL, 0xA81F587D386A3D73ULL, 0x00E5F065398E18B2ULL
        },
        {
            0x2F9F5D8A56025494ULL, 0x89211AFA7260D7F8ULL, 0x384242DD06769CFAULL, 0x92862FE661BC10E4ULL, 
            0xBD1FA6EBC85C123FULL, 0x889EAA259E117BCCULL, 0x8B9849123B95CF84ULL, 0x59A9A82DE4309B87ULL, 
            0x169C41EF1D043E1EULL, 0x5AB6FFDA57C6C687ULL, 0x271B6B13A5CDAD96ULL, 0x4B17183CF2F6D837ULL, 
            0x8CFC782A3F8AA022ULL, 0x5E46ABEDA09F72E6ULL, 0x7AD10B3189506550ULL, 0xFE03F7E20B43FF09ULL, 
            0xD8712B3F4D5EE0BCULL, 0x147FA3CF2E102766ULL, 0xD0F71DE06914F496ULL, 0x6382BA3DD29BC0D4ULL, 
            0xFE6C92A8B23C664CULL, 0xA9226FC0E4ACE706ULL, 0x5D58E0FD961EB931ULL, 0x1B466C9047532FD1ULL, 
            0x1C59ED3B6516B087ULL, 0x9ABDB21A7D91D583ULL, 0x2C9988A907919C95ULL, 0xE7E862C945C559C9ULL, 
            0x88AF6317C015EED4ULL, 0xE3D8C78CCAB3C176ULL, 0xD2AB9AE6F8997486ULL, 0x6F47C809986F2EB1ULL
        }
    },
    {
        {
            0x3682B948C934FFDBULL, 0x4AC72303ED84BA86ULL, 0x49D52536CE93E181ULL, 0xA822E5F6BDFB5933ULL, 
            0x24B4C72C4EB2A3C4ULL, 0x395B2E622430018AULL, 0x2753DB706375C2D0ULL, 0x56012079904C9BE5ULL, 
            0x26064BDE49D4A406ULL, 0xD428ABDF4B8BCE42ULL, 0x5D923D14CE7437CDULL, 0x19F20C82D8735F42ULL, 
            0xA2F8B375BB46BCC5ULL, 0xB37ADAF9FF7D0895ULL, 0x82CBAF6D14B98349ULL, 0xCE1783A062808D54ULL, 
            0x5FAE81AEE6DD5962ULL, 0x3C3A7E07074665BEULL, 0x7984331EFF9DA39AULL, 0x41A1B242DB271112ULL, 
            0x3CF0D2DAF8A65F08ULL, 0x8F4362FEC2725400ULL, 0xE0D5B35A63264067ULL, 0x2D1CCA00989A8353ULL, 
            0x4F3EF5A38BDB9DFFULL, 0x6D895C36B7ED6EC0ULL, 0xD83EE044C885C10BULL, 0xD51535788B043FE2ULL, 
            0x79415E4CC6243AB0ULL, 0x918E6F7DC89699C5ULL, 0x731A08A2111085C0ULL, 0x8893F51C75B60DE4ULL
        },
        {
            0x2F6B6790CF3A54E6ULL, 0xB8849BDDB3677F2FULL, 0x79C320BD1D167F78ULL, 0x6C8F35DB5EFC6E07ULL, 
            0x8E6DCA570B43F02DULL, 0x946B32CAE9EF4CA3ULL, 0x846A27057625B3EAULL, 0xFABC3F984E204089ULL, 
            0xBA90E0C654B7B64FULL, 0x0711B151DCA8035AULL, 0x225F87B4DFC50E9FULL, 0x0183D32F0FF18ABFULL, 
            0xF0C9007B5A8FEAC3ULL, 0x78D7B0AAB87AE554ULL, 0xB1422B0CE7CD7658ULL, 0xE71192BB9A1FAE5BULL, 
            0x22A05FF77112CE13ULL, 0xD6F4FBD908A491FAULL, 0x194686ADFC1948E7ULL, 0x46341DEE28054E27ULL, 
            0x177C28BCB437D439ULL, 0x8E4277A2256E71D9ULL, 0x07DCB8857457C479ULL, 0xC1993DF7BD9B3D34ULL, 
            0x42312E8F6547FA00ULL, 0x2C24ACEDBCD40EEFULL, 0xA1CDD49D37865BFBULL, 0x9412511BDD5EEFEDULL, 
            0x301F28439BD6999FULL, 0x8B787B952E6F84D0ULL, 0x73C948BDD9130148ULL, 0x9F8E0688001AD380ULL
        },
        {
            0x1B937BDF70450544ULL, 0x1AF9E2203B421362ULL, 0x859D98EB547A7EA3ULL, 0x8A5BD4F07D7224EEULL, 
            0x7022CE1B20637A6CULL, 0x3812DB69CBDBF963ULL, 0x0000DB95B0C6CE81ULL, 0xA8AD442E2B4845B9ULL, 
            0x46467DDC8B5D0AA1ULL, 0xE72E3DD978702F56ULL, 0xA3F8D9AD8DA3C673ULL, 0x4F536DFFD945E1E2ULL, 
            0x27527B7EE02C7403ULL, 0x574FE1AFD661C221ULL, 0xE72B5739BA32DCB3ULL, 0xC8E10F94F7A8D0DAULL, 
            0x50BBF20A31B18D60ULL, 0x4BF37841E2B45FE5ULL, 0xD3D5420E00DCFB30ULL, 0x92716E52ECDA2125ULL, 
            0xA62EB27B4212734FULL, 0xAAB1B4C6E625F730ULL, 0x39C5CA3D97C69CAAULL, 0xB6C85D672683AF47ULL, 
            0xFD105E3F22E9285AULL, 0xFC2C2713A682FED2ULL, 0x5EF422448255BA57ULL, 0xC1F17B03F959CBC0ULL, 
            0x02774737D28FCD0EULL, 0x8C4E358B59EE7447ULL, 0xFFB1C9BB5E735A76ULL, 0x927A774431F2450DULL
        },
        {
            0x39AD030E40738731ULL, 0x9918AC90727A5B64ULL, 0xB517E63E685C40CDULL, 0xAF7EA1036EB06016ULL, 
            0xD5C6E4191A87E0D5ULL, 0x1508BA995682798EULL, 0x36152AD03F6C49DAULL, 0xFEB2EBBD9A037F6FULL, 
            0x57CA71ED98BD5A8DULL, 0xD90B8E624959B0EAULL, 0x33731E3F01D3F211ULL, 0x35D3CA642C046108ULL, 
            0x55ACDE0E98018077ULL, 0xABC4156615279B71ULL, 0xBB57012303F6FDB5ULL, 0x3816B78348BA0CDCULL, 
            0x7649C3C642D0198DULL, 0xA880F36EE9203217ULL, 0x18538BFCEF85C557ULL, 0x86E7040E6BE7BCB8ULL, 
            0x9A7B8E7E6D4F68C9ULL, 0x75A939FAD299450BULL, 0x426D31289F61EE37ULL, 0x851DE7618DCFCDBEULL, 
            0x5005FBBB331BDB8CULL, 0x1D3F0D039968C57CULL, 0x3055BE59034F14CCULL, 0x7CD6107D4FA761AEULL, 
            0x2F1AD079274DA64FULL, 0x9FAB9D1001A73DB4ULL, 0x380C27B28951210AULL, 0xD9231CD106B14A5DULL
        },
        {
            0x5581E72C362DE1F3ULL, 0x41646CF2F7E23527ULL, 0x02359F63BFCF1E47ULL, 0x76B4529F16F117D2ULL, 
            0x8059B302F903B832ULL, 0x52A66DBEE6CA3BFEULL, 0x45CF49E4E010E8B3ULL, 0x66A06380FBA68947ULL, 
            0x50BDB502BB5965A6ULL, 0xEEA5230101F2BF46ULL, 0x23161D37F5BCC0BCULL, 0x6EEB0CAD5AC83B3AULL, 
            0xBC66E1BF425A7007ULL, 0x30E03B5D4EEB3762ULL, 0x260266B415CF7EA7ULL, 0xB5D612526BE054CEULL, 
            0xE501E1CD8B7AF12AULL, 0x826070436F95292AULL, 0xAED71407ED850F29ULL, 0x0329BFE412B678A4ULL, 
            0xE72327CF6CE90D82ULL, 0x1B2BF2A49861CE6AULL, 0x1B513BF6BED30C27ULL, 0x38DDF93F2D4994AAULL, 
            0x1ADD5C3AA0BE822FULL, 0x760132372A0CC1FDULL, 0x5BECCBCD48D86305ULL, 0x77B048B2B7AC225DULL, 
            0xA1A23E93BBFE3B8FULL, 0x6434B1F0C92E9AAAULL, 0x705CC83AC2D1080BULL, 0x8C940131615E4AAAULL
        },
        {
            0x7384059BB1C80F92ULL, 0x1A8E5A34C0436E50ULL, 0xA85ECF036F9B7B74ULL, 0xC5BA90EF7E183C96ULL, 
            0x9C3242944B4F5EA1ULL, 0x4E18D735E4FF9149ULL, 0xE59BCB47DCFE3E7DULL, 0x6B1E54416BF3A623ULL, 
            0x4D2F6205F0CD4FF3ULL, 0x5B46D43375019FFFULL, 0x0FBFDA0E0E469209ULL, 0xA69FCCC2577AF66CULL, 
            0xA8254ECD11AE914BULL, 0x6DC2AE06FBA868BDULL, 0x28C65574D732C372ULL, 0x3D8FC261D308620FULL, 
            0xFF591ECB2829958BULL, 0xBF53CDB6616E7D4CULL, 0x3FA54725544C912BULL, 0x1E99315BC9AE3D30ULL, 
            0x164C0CD1B115B718ULL, 0x63D72CBBD04D142DULL, 0x7B21F6B436E9952DULL, 0x2C4E788BAE6ADD2DULL, 
            0x8085EA9AC7242838ULL, 0x0E79F62C919F3162ULL, 0xEEC851AF176877C7ULL, 0x2AD0E200BC9184E4ULL, 
            0x005FB470771168A3ULL, 0xE8ED20934EAAE287ULL, 0x7204AA2BF19AB922ULL, 0xDDA2192C9D2F43E6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseAConstants = {
    0xF2AC6EA14F721F5CULL,
    0xD84DE2250220B111ULL,
    0xC28AEA5925D26C3FULL,
    0xF2AC6EA14F721F5CULL,
    0xD84DE2250220B111ULL,
    0xC28AEA5925D26C3FULL,
    0xA64973F368F95C70ULL,
    0x38AE4811C52E6D29ULL,
    0x1D,
    0x96,
    0xB9,
    0x98,
    0x9A,
    0x43,
    0x8F,
    0x87
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseBSalts = {
    {
        {
            0x6FA9C44D5A4315E3ULL, 0x1AFD49E97BF26609ULL, 0xAF95215AA30F96A0ULL, 0x83FC3F3E466B5499ULL, 
            0xE983B2F112C25891ULL, 0x9839DE25D67D2C6DULL, 0x968FC88397D6F4EFULL, 0xED51377695A8B822ULL, 
            0xF3B64D3623AACC60ULL, 0x7DB744707E4BB9F2ULL, 0x44820B2741230A6AULL, 0x7D8B6261195AB32FULL, 
            0x95263F56F2762580ULL, 0x18687EBE27657B06ULL, 0x6AE2A05B9B5BB3DDULL, 0xADEBE0EA42A5AB79ULL, 
            0x2A09AEC8840948FDULL, 0xE04286E33D76D193ULL, 0x619D5A576ABD78DAULL, 0x34C4FBB684852341ULL, 
            0x354ABB03519BE7F5ULL, 0xFA341BCDA9A13DDEULL, 0x2AA370C161FBBED8ULL, 0xECC797A0D2C5C3A4ULL, 
            0xCBCC432B1B22494EULL, 0xD1F75126C8544C1DULL, 0x36729E102FF547C6ULL, 0x9D603B34A128487AULL, 
            0xF381A34792B70A0FULL, 0x270587C53E4DF0C6ULL, 0x50FDEF9BDDD12E04ULL, 0x4ACEC00788CC8309ULL
        },
        {
            0x22485A17F3BE85B5ULL, 0xF30363C673099183ULL, 0xF269C8C6FBE118D2ULL, 0xB30447D7F3F4F5A0ULL, 
            0x2593FE9451086CACULL, 0xE6F3CDC0E9A3A2F2ULL, 0xC70EDFF660A1BC1DULL, 0xC3954A0D7B36D6E8ULL, 
            0x10CF4E48A340B5D2ULL, 0x9118FC9CA45450CCULL, 0xEEEA5085F9148B34ULL, 0x8BE8E3864FB8F16DULL, 
            0x441E85DBCD7F7C33ULL, 0xD1DA37CBA51C8240ULL, 0xBAE89B1E4C92012BULL, 0xF142E6B7373A62DCULL, 
            0x8D283A0321E750FFULL, 0xC2BE6F03BB36E6A0ULL, 0xCB62C90F0CE80540ULL, 0xD1BA02D4B63CEAB2ULL, 
            0x7E5D42B87B0AA8E4ULL, 0xE54CDC7646114615ULL, 0x1D7B79B2228C1764ULL, 0x61A58600977EE66BULL, 
            0x59D4CA87761BC688ULL, 0x96AF094C414A47A0ULL, 0xFCF1BF612F16181FULL, 0x663A75337496EBDEULL, 
            0xAAEBE9048CAC6A50ULL, 0x9C8ABB13E62773BAULL, 0x2B5F6E2104210343ULL, 0x1C8502DC5FD08AD7ULL
        },
        {
            0x39BF1B07BEB9F483ULL, 0x691A35ADEB144F9CULL, 0x4A40E63928D0E7B7ULL, 0x7B760D00EA3F5A57ULL, 
            0x2145D815A1C9F3CCULL, 0xE6A3D10B2431DB87ULL, 0x0FF41207B559A71AULL, 0x0D5AB8EB31F9C666ULL, 
            0xEA9F947D23D24C1EULL, 0xB8CBE98E6C95EAF7ULL, 0xD700FD4E82CC2A6DULL, 0x50DB012B7C0BFFA6ULL, 
            0x0E71941071E961E5ULL, 0xA91F7882CF7BFE08ULL, 0x4D22B0F30B1880ECULL, 0x03C12C3503FF3671ULL, 
            0xBA1386073728FA5BULL, 0xF0A14700070FFFE3ULL, 0x431FCFC0102F593CULL, 0x2BCF69FAF36F449BULL, 
            0xE7978B621EEA854BULL, 0x36478F96AEEAF286ULL, 0x0791ED5F48A95116ULL, 0x79ABFF2C5AF6A99BULL, 
            0x54AD846B1A8EA5FDULL, 0x1667D7EFFAA6DBE5ULL, 0x6A1F28BA2CF962F8ULL, 0x77610F89603CB58EULL, 
            0x2E207964D86613FFULL, 0x27CCA3C30C1C5631ULL, 0x5E150664BE008A1AULL, 0x36B8A5E61B35EE99ULL
        },
        {
            0x75E3C9D53408721FULL, 0xC262ABD19C9ED7B8ULL, 0xFFEB2511983C8D8BULL, 0x917D5DE8BBDEF5FAULL, 
            0x88800AF0F079CEFDULL, 0x57CDF918755F38D3ULL, 0xE93A3BC2320D3703ULL, 0x826AE62E6A654364ULL, 
            0xF50693F480004EAFULL, 0xEC254997A7623733ULL, 0x669526D8A14C2AEAULL, 0x51DF8C3F46C167B7ULL, 
            0xBC345AB42C4CB0B2ULL, 0x1C14B7F55A8C2486ULL, 0xB9C0A487FC55B0D5ULL, 0x7799395776A47984ULL, 
            0xD438C7FA3A7FD39EULL, 0xD4042588A85CC5A0ULL, 0xB4CED0BA312E2D9AULL, 0x3CC58B86959E0470ULL, 
            0x339B98DC2D48FBF7ULL, 0x82ED50629C74D38BULL, 0x547AD7A4A6676B0EULL, 0x37C31D436B66E6E5ULL, 
            0xB0413ABB7AD4BBD9ULL, 0xA886D13E2AECC427ULL, 0xBE1DDA56149E330CULL, 0xE4577439A583BAF3ULL, 
            0x135CF3F5B543F17BULL, 0x2B5F88187AF43AA2ULL, 0x1AB17D10DE787285ULL, 0x61F0362833B84023ULL
        },
        {
            0x330A8751BDD32225ULL, 0xBF65AD36F017FE0AULL, 0xB8C0C21FFF1833BEULL, 0xA378F5D0E810EBC1ULL, 
            0xCC1B487435BC907AULL, 0xCC2518AE44EC8BB9ULL, 0x396527A2D652BDDBULL, 0x747D912CE8FA9E2DULL, 
            0xD486E37810D7440FULL, 0x0038A116EA3138CDULL, 0xADDD33EEB8118A54ULL, 0x774D109F113A328CULL, 
            0xF326838FAABF7F1DULL, 0xB5598AF92AA18281ULL, 0xF69E1D5CEFBDF26DULL, 0x09A78419E755D15CULL, 
            0xD65EBE4764CE9F4FULL, 0x51AD72E1793D7761ULL, 0xA1B2B20F3515FDD2ULL, 0x768D8F63ADFAA5B3ULL, 
            0x0FDEF3228C401713ULL, 0x1482EEAB794A0590ULL, 0x694BC512037BB402ULL, 0x8864F18E2AAB00D8ULL, 
            0xBED5B5883A07D198ULL, 0x948334EA1B91AEFAULL, 0xA3C48E850C9CAEBCULL, 0x21A2BC224C3EDAC9ULL, 
            0x130BD122BF41450CULL, 0x62192DAD0A32A22FULL, 0x196AF1E057DFBA7DULL, 0xDC84BBEB64C5812DULL
        },
        {
            0xA8D636B35AF7A2ACULL, 0xF842246B4BD0A4B7ULL, 0x10BD4F6B2AA0C126ULL, 0xF7C063B47167B8E4ULL, 
            0x862CE5DE7D1F8B74ULL, 0x95E88D8298C832A9ULL, 0x5A60A6C9546A7372ULL, 0x0759BABD990A3C93ULL, 
            0x02170A5F4868CE5CULL, 0xC2743C556C28F72EULL, 0x218482158C60AE03ULL, 0x1C16EE2102C85006ULL, 
            0x56478D050088D0EDULL, 0x7B0770AEA18859FFULL, 0x199DA399784F4168ULL, 0xF77B4A8747821C82ULL, 
            0x6BC7968C964D9DB0ULL, 0xF8C1501018F6B539ULL, 0x396B8DAE63E1AD5DULL, 0x3280A726D8AC1D74ULL, 
            0xB0E05B2B047EB46BULL, 0x15C710F4F479A8D1ULL, 0x8F9F4BE82DB78EEEULL, 0x8EF270E792423156ULL, 
            0xD37BF3567ED37BAAULL, 0x8C1C6DF1A8DCFDE6ULL, 0xE958C63328938D61ULL, 0xFF63D4EBBEE7CC54ULL, 
            0x419094E74808BEBFULL, 0x23241ED45B5D3274ULL, 0xD473D3B405D90B3BULL, 0x47411F3D67708DF4ULL
        }
    },
    {
        {
            0xBB1D3A607F4328D5ULL, 0x52624DF500576797ULL, 0x768D0BEF000E4592ULL, 0x05C263D402A12DD3ULL, 
            0x128A56C389BF6D2BULL, 0x3ECCFBE6C6715697ULL, 0x8F372A86831CEADBULL, 0x1A4938D08D633D6DULL, 
            0x069615ABC873AADFULL, 0x7FEEB2848DB14181ULL, 0xBFB57A2849CDD06AULL, 0x0351447F634BA567ULL, 
            0x1837C654FD4F8EF4ULL, 0xB96D299A9F376298ULL, 0x4F54CB4ED0937B2BULL, 0x35E6BD93A24FD175ULL, 
            0xEA3CBD9973C4DA7FULL, 0x4A7FC306164E78E8ULL, 0x2F2EA296C76DD00EULL, 0xC6CEE3453EBC328CULL, 
            0xA98241D10E3185DBULL, 0x76F6C63B8F4FE53FULL, 0xFEEDC6FCAD6A63E5ULL, 0xB7A6D666C90CA774ULL, 
            0xA8D2FA4DE4E27892ULL, 0x80DB832B881D698EULL, 0x29B7A088696A039AULL, 0x8FC616E6A12D7A69ULL, 
            0xF28496378C36F824ULL, 0x033CDE636797BC28ULL, 0x315C3B4F70DD3950ULL, 0xFCB3D3E8BF01CC7FULL
        },
        {
            0xC56AD5112CC40D6BULL, 0xAEC179F472D39397ULL, 0xB5B9080B301E3469ULL, 0x1201A9E3BA0D3007ULL, 
            0x1914FDD0D76A8BFEULL, 0x85A1A1B251147C4FULL, 0xFA0EF4D3B4F556F3ULL, 0xAD9A124EA489CD41ULL, 
            0x62080879A45CD2BEULL, 0x63DF29A7BC044AC1ULL, 0xFC6A413BF6A9A156ULL, 0x520EF949BF5EBC35ULL, 
            0xC2938702FFAB031BULL, 0x73789B68197E165FULL, 0xC81D7EF3D281E9E2ULL, 0xA7F1C244D30275B1ULL, 
            0xCE3ED0C0988308FBULL, 0x4A2418381E6FA6D0ULL, 0xE6832EFEC8C83895ULL, 0x5B612AF6EB2D8B45ULL, 
            0xAB240FB0A5C110B4ULL, 0xB080B14A0CF4BF4AULL, 0xAD3740DACA11306FULL, 0xF15C2E6599E3846AULL, 
            0xDBCD97C22F359C59ULL, 0x93DB9AE087DEDE99ULL, 0xB1C36E5E74FCFBB3ULL, 0x7853BEF3E0D38180ULL, 
            0x2963A3895188B3DFULL, 0xCC4E2DF8797A7F44ULL, 0xAA9236DA554600ABULL, 0x828B2A516FDD8B83ULL
        },
        {
            0x295EA5E49C3CAB14ULL, 0xB93D191C475738AEULL, 0x37B4FFA1BE9524C7ULL, 0x403389952C2A9FDCULL, 
            0x89BCF0CE86F59D7BULL, 0x67C1707E46784DB6ULL, 0x8BC813D0BC873ADDULL, 0xDEA5066B81367F7FULL, 
            0xE764A7CFCF102C47ULL, 0x8A594BB9467E49DDULL, 0x13C233992C2B1127ULL, 0x7B41484B7B81E466ULL, 
            0xE5A72680958CCD64ULL, 0xF32340D42B576F01ULL, 0xE7978D1A63FDE232ULL, 0x77DA0B2D504E1639ULL, 
            0x505C82B0C783009AULL, 0xA928F32720AD9BC4ULL, 0xA10D71A9684E5364ULL, 0xFF2FE2447C49553DULL, 
            0x4324973182291A31ULL, 0x8886F47C75FF4AE7ULL, 0x863CB85056323CEBULL, 0x05A91F50C4BB4DEFULL, 
            0x57FFD2CB6B7188F5ULL, 0x8A0CC7DB8851EAD0ULL, 0x98A3FFB0C2256200ULL, 0x2213D119950D3214ULL, 
            0x75BCDB477FF84FDEULL, 0xA0A9427B0AA4CD6CULL, 0xC0EE927989479754ULL, 0xF724BD7BD6B76D85ULL
        },
        {
            0x5864017E77E6A9D2ULL, 0x78E4D048926C6237ULL, 0xA4800008DBF3D664ULL, 0x6F87705475431748ULL, 
            0xA2E29B362B39A70BULL, 0xFC8F813AB778371AULL, 0xF0CEC0C506742F33ULL, 0x25E3588645F2B215ULL, 
            0xE314ADE4AB8DCC0CULL, 0x94CDD4469E53D88DULL, 0x2062D2F717FA0AB1ULL, 0xD77A7512FF021EA9ULL, 
            0x560169B8A739B3CEULL, 0x9F680D2E3120663DULL, 0x1C099D4D8A8C37D0ULL, 0x6D86342ED0E35ADDULL, 
            0xBE05C1FA0DCBE3DFULL, 0xD3B2EEAEA065077BULL, 0xF9045F0B1266C8D5ULL, 0x5989165DFA24E806ULL, 
            0xAD1EA29449179311ULL, 0x1D7D2C8F6F5EC3ACULL, 0x5BE2D4C395010514ULL, 0x2A9CDFE853890A13ULL, 
            0x36D6CB7F1C72FD41ULL, 0xDE924C2EAD0A0877ULL, 0xAD585F0204DFC014ULL, 0x2AC96AD506A3A32AULL, 
            0x1D5CAC62C7DFBA89ULL, 0x20E775D6B5E37ADAULL, 0x65DC20267EE8E4EFULL, 0x6AAD90AE3C88D55AULL
        },
        {
            0x57BD94F83276A8D3ULL, 0x4DC09B55E82C9F76ULL, 0x948C92814092889CULL, 0x7A7E399B183D5E7FULL, 
            0xB2F384D00E8AADAEULL, 0x0809A495F0E7E72AULL, 0x8304C2AB65F15478ULL, 0xC741B6EDF7ED7856ULL, 
            0x92852B227A665957ULL, 0x84CC966670B24012ULL, 0x52A3A1938496564DULL, 0xC964C1B4668BF15FULL, 
            0xDB0B2685E394A112ULL, 0xF5F4C3DFA5995380ULL, 0x48492005ED6EF690ULL, 0x6AD588C87760BAF3ULL, 
            0xACEBD22758D0527EULL, 0x96631E3360679FF2ULL, 0x74C245DC4678357AULL, 0x7C5DD6256D9505EEULL, 
            0xFFD3099E69D26D73ULL, 0x0DC9E71C08FC6293ULL, 0xE6F4F80B3A2ED2B1ULL, 0x24581979AA2E829CULL, 
            0x4B4723730A791654ULL, 0xDC1BE45C1C3B760EULL, 0xFF1E3E813E91500EULL, 0x0D3E63C1BBA28F01ULL, 
            0x5887F35DA2E60738ULL, 0xCE2E30162B86DA59ULL, 0x7C396ACFF3EE722AULL, 0xD2FD71B25963907BULL
        },
        {
            0x68898B5D69E75977ULL, 0x5DF03486C39A8A2BULL, 0xF21DF7623CD2693CULL, 0x606A186AE071550DULL, 
            0xEF44D186CBB371F2ULL, 0xCC10DD8DFF80CE20ULL, 0x5B48BFEB78692AACULL, 0xCE7BD2586F764402ULL, 
            0xA41664846E3B0C1FULL, 0xD3103342A6805947ULL, 0xB9D641812BE15C9FULL, 0x39D8D44290BC9B29ULL, 
            0x80EC5DE21081EC5AULL, 0xFA605161540C9E22ULL, 0x35A2663516314932ULL, 0x95CF729BF21B09D2ULL, 
            0x821297FA6DEF2C03ULL, 0x65D7DC83CEF51221ULL, 0x8CBB50AB133783AAULL, 0xB841B84A2BD90B26ULL, 
            0xDB7DCEF1C5AC96F9ULL, 0xC90BCE840E186F7DULL, 0x6F1C2D5D1937B72DULL, 0x7BE7E9C7374E294CULL, 
            0xC357B69D0EDBB839ULL, 0x149562B185EEA2C7ULL, 0x380467EB417CBC95ULL, 0xAC241A7180171E6EULL, 
            0x42A9D076F27DC5BFULL, 0x14346B1B31CC271FULL, 0x43561471C4661957ULL, 0xF27EB9E4E28F0EF9ULL
        }
    },
    {
        {
            0x456EF10AA84EA9EEULL, 0xABC4B8486B134AEDULL, 0x13E4B400D56B7906ULL, 0x6617459A93DAFC0EULL, 
            0x659FC6BD25C8D371ULL, 0x356FD2FA18BB5A4BULL, 0x1E8756CD6157599DULL, 0x51CA7967DD85C268ULL, 
            0xA0FBF0A05C711F5CULL, 0x89AD60268E766DC9ULL, 0xE91A3216D49E8262ULL, 0x2BDAF1B8BB93AD2EULL, 
            0x51E578E1A6579217ULL, 0x7D07F98C27E61FFDULL, 0x385F0203D5A7BB08ULL, 0x988AAA8EA14A902BULL, 
            0x75A80CA88C60E457ULL, 0x681A04501662C168ULL, 0xC4ECC69048F52FEAULL, 0xCCE4F8E1CE404D3DULL, 
            0xB24F9B158050AC0BULL, 0x1ADED635618C1106ULL, 0x0698AC2EB953128FULL, 0xBEF8EEC3B75B1E90ULL, 
            0xE35395A494D74F4EULL, 0x6F3FF52B8703C2ECULL, 0xE040AC30F672758DULL, 0xA49226D72A405DFAULL, 
            0x0E1B20F9A34B3FF8ULL, 0x8AF66D6785709CA2ULL, 0x26DE139215541860ULL, 0x813EBAB25C226E7BULL
        },
        {
            0xD14892ACC4625075ULL, 0xBC774F26C4A19304ULL, 0xC76833F4073D23E7ULL, 0x72627361B96AF5BFULL, 
            0x37902CDA401B5B73ULL, 0xA882781F69C9D708ULL, 0xCB272A920C892DB9ULL, 0xB4F5E492C1D9E931ULL, 
            0x15E4A86420095D33ULL, 0xB916B8B4B57A6DB4ULL, 0x1A9BE2180779E1FFULL, 0x0BB21B2918D21907ULL, 
            0x16366209C835195BULL, 0x83884ECC4E38DD85ULL, 0x5BB7ADD44852C82EULL, 0xF97D7B49EC077FB6ULL, 
            0x4BE1147E1171F21BULL, 0xF7E850B92887410BULL, 0x49B4D3DF1A188DB3ULL, 0xD9FAE49A8A297B3BULL, 
            0x0E341702AA84321EULL, 0x9A5CF8AD301B5B7BULL, 0x1095DBF52A8BF3EFULL, 0xB1B5DD57BDD7F730ULL, 
            0x4E474731530A61A5ULL, 0x638380BA296710DFULL, 0x8E97DF8815FF1470ULL, 0xAE415FD7603F1AB3ULL, 
            0xD8787E140D6DB81DULL, 0xB30A9AA2EFFE2686ULL, 0x33759FA7235D3A26ULL, 0xD70CC2D690EFF8CAULL
        },
        {
            0xF2E63A38036C2447ULL, 0x7DFE5218D2FBDB11ULL, 0x528EE27A2B0BAAFAULL, 0x42C5CE87F6E5A59AULL, 
            0x4F82620107315068ULL, 0xD65DC283D07818BCULL, 0xD19B80E8054D5746ULL, 0xB6D8F6E60A29DED9ULL, 
            0x369E5FCBDCC70DF1ULL, 0x1DDEEB82E9780912ULL, 0x06D8261B9E530CF9ULL, 0x67E563F3595D6DE9ULL, 
            0xDA374F3B9226CC83ULL, 0xC5659C3795EFA093ULL, 0xA1AB4246392765BDULL, 0xF2A236A2AAD46820ULL, 
            0x7B8CBBA1A59B27EDULL, 0x6DF33628880AA577ULL, 0x6DBCF997F0D89C71ULL, 0x1F773BFC3FFF9A04ULL, 
            0x80FB045B4423B642ULL, 0xB1C7718613D56925ULL, 0xFF95DC6EB3AE255DULL, 0x5ABA87DBF082FD46ULL, 
            0x72C695221633AE43ULL, 0x4C00B998C58858B0ULL, 0xC107D1CFEF18875BULL, 0xD5CCAEA6A6BF6E2EULL, 
            0xC13A89D4C4524F04ULL, 0x49CC876FCCC09BEEULL, 0x4E65442B2760C73CULL, 0x2145F30F86516E27ULL
        },
        {
            0x5975D9278A22ACE2ULL, 0x06F29459DAFE1AEFULL, 0xB5EC2C2E520C46ABULL, 0xF79B4BDF7A463580ULL, 
            0x0CDB8E7670899E8AULL, 0xD8CD1AFEF63A9BF4ULL, 0x281D966B85299D53ULL, 0xDD5F9230F4A0CCE5ULL, 
            0x3446B711B329FAA1ULL, 0xDFD23BD14D0BB421ULL, 0xA46368B793905277ULL, 0xE0C633EDFEFD9041ULL, 
            0x81CFC57D9536EB94ULL, 0x63FF0D37B8A8DF9EULL, 0x3B8DD5C68C0819AEULL, 0xAFE728807232E1EEULL, 
            0xCCF5432E395155B9ULL, 0x21F3110752ED41A8ULL, 0x135A65AFA17FFDD7ULL, 0xB3433DBC3F83364EULL, 
            0x302A2A59B417CB25ULL, 0xF91C2791650CC5F4ULL, 0xE7C3363C2A11AF12ULL, 0xD73455FE9B3F5DD5ULL, 
            0x7E99D97856D95B9DULL, 0xCFB70D558A878D61ULL, 0x368EE915F3212D04ULL, 0xEC9412EF3D96A4BFULL, 
            0xD084537FFF7A63BAULL, 0x2BBCEBE1995DBF12ULL, 0x669764D669BED24EULL, 0x3D551A4B518A2264ULL
        },
        {
            0x5D777803331DA5FDULL, 0x0319BC46E1ABC814ULL, 0x9238EB25E28A696EULL, 0x91871009B3F6DC72ULL, 
            0x3BA92C563C6B1082ULL, 0x53854DE0D152706BULL, 0x8B167DD045A208E1ULL, 0xB8B3E1832B563794ULL, 
            0x7A7D829A656CCC26ULL, 0x8AFBA08F589ADDB3ULL, 0xACC1BE40DE798ABAULL, 0xE882C30B8006EB81ULL, 
            0x3B04D5FBCE496878ULL, 0xC3E6B4982B1304CCULL, 0xB218A233D220FF78ULL, 0xE491B76FEEE55F91ULL, 
            0x08B2A4DC48CD8E06ULL, 0x0298C7BC088DDA6EULL, 0x8493FDB1360E41CAULL, 0xBD2BA1237706CAE8ULL, 
            0x517386422FFCD654ULL, 0x6D61FD5BD739FCE2ULL, 0x22F9D87111869F84ULL, 0x94753C05010D1D90ULL, 
            0xB6C165D37E987D57ULL, 0x53FC4D34E71DFE40ULL, 0xF71D4E6AA814D12CULL, 0x7DE546FE7A011C47ULL, 
            0x6F414D71D6EB6CA8ULL, 0xBFB38A90D9EC83B6ULL, 0x3F68F25D740B7B29ULL, 0xC6163A551C4F7B9EULL
        },
        {
            0x53B78CFA92546D76ULL, 0xB5BE0279FA79BF9CULL, 0xF485D2DCFA3F46FBULL, 0x5DFC22F2A4C1F463ULL, 
            0x68C54C6B9EAEC695ULL, 0x1F63925A30F1F7DBULL, 0x95D3EC45059F494DULL, 0xC9C957BAF6B62D2AULL, 
            0x18B73ADB19C84CF4ULL, 0x7CDDB82039C3A3DDULL, 0xBCE0F0245FDD9D5EULL, 0xB49DC42E72D4830FULL, 
            0x2AABB71FA9D5CFE0ULL, 0x057EF5275BB4F00FULL, 0xA4118CE28C5B5953ULL, 0x9FC3F4F17BE34CD7ULL, 
            0x90B745F13CCDE7CDULL, 0x2C114EF8AA9DCA7DULL, 0x3DD63FC330AD73DCULL, 0xCE7CB41B5024A4B5ULL, 
            0x6690EA80BF8CF06DULL, 0xD5B48C08EF302615ULL, 0xE5A5955935DEFFA0ULL, 0x2E0CC82CEF8F5154ULL, 
            0x03C0133E2E7DF97FULL, 0xE47A42A040333C0DULL, 0xCDE31ACEF0E53AC0ULL, 0x75B51803A478173CULL, 
            0x7AB1A0CEB85F3481ULL, 0xED40526DBB42A533ULL, 0xA8ED0BD84B10669BULL, 0xEE991A3F542C492BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseBConstants = {
    0x7D9A660AB7A6D111ULL,
    0x84E717E7F01B4C70ULL,
    0x506B9E84B32D8290ULL,
    0x7D9A660AB7A6D111ULL,
    0x84E717E7F01B4C70ULL,
    0x506B9E84B32D8290ULL,
    0x4970542F2FA0D27BULL,
    0xC9D956DE6917EF3AULL,
    0x67,
    0xE5,
    0xDF,
    0xEB,
    0xA5,
    0x8A,
    0x98,
    0x49
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseCSalts = {
    {
        {
            0xFC9C9A82EB9DCD1AULL, 0xFA3A704199910988ULL, 0x1814C22426B55AD7ULL, 0x76012A10982C76A4ULL, 
            0x1354BAF10E21FA80ULL, 0x350B38B9265AF329ULL, 0xF3A676B2B92BA491ULL, 0xD04B860ECBCD059AULL, 
            0x7BBD6E6B2BD22572ULL, 0x9DE248DF89CC0D46ULL, 0xE891AF86B7D826DBULL, 0x62724F8C35FBF6E9ULL, 
            0x04C0867B81805D3EULL, 0xA972994731B531D3ULL, 0x5A7FCFB628B5F261ULL, 0xD998DBAC271D7AAAULL, 
            0xAD876295F4E7C453ULL, 0xE6076EB3114A90E8ULL, 0xA0CD5FB683F47477ULL, 0x947EDB18B6FF83DFULL, 
            0x5B62A8B7214E32A1ULL, 0x02E177CA777DDF56ULL, 0x574041A2FD5868ACULL, 0xED0C2DD4292AB9C8ULL, 
            0xE200B944B8BCA567ULL, 0x50176298EB3E8C47ULL, 0x6CB3494002266946ULL, 0xDB558DD67CEA0BFEULL, 
            0x1544201B6CA9257CULL, 0x57D9FB1D27D14A64ULL, 0x25598916C7F12E42ULL, 0x117F00AD6677A5F2ULL
        },
        {
            0x2EB1F56D85E4AD04ULL, 0x2361CDA56FC13666ULL, 0x4952950719169C8DULL, 0x17E44516541B0663ULL, 
            0x527AF29F8F4377C4ULL, 0x57AB00988F2247A0ULL, 0x35CCDA37BB83A023ULL, 0xEC6931DA8B660086ULL, 
            0xF3AC127A4BFF46CDULL, 0x300CC4D00AE1CC4CULL, 0x4D0E6530FFF8C0B0ULL, 0xE1C34970E6BDF6E6ULL, 
            0xF5C13F62AD4C0ECBULL, 0x428827BD5DCCF476ULL, 0x5795B6E45649424EULL, 0xC62A4D590A7DF8EAULL, 
            0x9E4BC31E0D9A8437ULL, 0xAC10545B982FEA9FULL, 0x4917B7B7EC699BBDULL, 0x424E6F0280D6C835ULL, 
            0x64CA66B12655362FULL, 0xC615BA2E90A957DBULL, 0xB5F34DF65B9868CAULL, 0x7EBD34F39102118EULL, 
            0xD348F0AB49FD9191ULL, 0x6E563063E8E7246CULL, 0xAE8DCC6241AE728AULL, 0xF6ED3FB3009AC54DULL, 
            0x19070A971E1B0631ULL, 0xFA3E3889A1A4001FULL, 0xEC3548A7776AFD4BULL, 0xFF3712041870D05EULL
        },
        {
            0xB40FDEE791D587D6ULL, 0x0B8D323864DDC592ULL, 0x82EF6F4DFB2DF5F1ULL, 0x297735BBF7F42CF5ULL, 
            0x7C75AAE0D09E414CULL, 0xB18AE9F056370E1AULL, 0x10AAE224AAC76AF4ULL, 0x5813F46D60B83691ULL, 
            0x12A8F28AEFB1C3D7ULL, 0xB2EBAFF5FFAA7212ULL, 0x830A3386EB7168B6ULL, 0x482A4701B742F3D8ULL, 
            0xC541AE7F507050A6ULL, 0xA37D5ADFD1A1035BULL, 0xBF9406583A92EE63ULL, 0xF85E18AAEC27C2AAULL, 
            0x799F735EED64150FULL, 0x2B65D34DD5E34A3CULL, 0x905CBCB5B5A6C9A6ULL, 0xBB68E2C879BA8263ULL, 
            0xDCB10344A3DB3CC5ULL, 0x3AA0FC4C7B8DD74CULL, 0x93446DC183DEB46FULL, 0x1574635E4C3A4D1EULL, 
            0xBB0B4B97194035D3ULL, 0x15BBB3D14D7BA031ULL, 0x7851A2BD2A05B6D0ULL, 0x85A8AAC4B2D93DCBULL, 
            0x35C1145272FBA0DCULL, 0xCB112A9B37668B88ULL, 0x57E808EAAEC052DEULL, 0xF925A43C78E484D8ULL
        },
        {
            0x0D304B744439576AULL, 0x051FD75C12890C44ULL, 0x28A1A62FDA88DD3BULL, 0x7813CD3EB1B40340ULL, 
            0x35B903EB26322675ULL, 0x4B27DBF8787CCDDBULL, 0x78A3EAFB660A7618ULL, 0x7665A59E2BEA5841ULL, 
            0xBD5AE4F41888D0A2ULL, 0xAA6D4A06F146C8A2ULL, 0x8FA19F9060AEEC8BULL, 0x5C063BEA685A9E4BULL, 
            0xFCBCF87E736EA681ULL, 0xE25AA57E730FC0B7ULL, 0xF75E6335A1ECA232ULL, 0xC5086106E5840549ULL, 
            0x3F98529818C3EDC4ULL, 0x041C6C04EFACC183ULL, 0x75ACFE62F25E0A23ULL, 0xB387E844960668ACULL, 
            0x949825F7E6519FD1ULL, 0xFE2129531E9E436EULL, 0xD1588A92B63FBD89ULL, 0xA926131A00D4693BULL, 
            0xEC6CB375FB03FCD1ULL, 0x6606A1D6BD4FA057ULL, 0xF0DEA02938101847ULL, 0x57F53A154623892CULL, 
            0xEAEA90AD33AB7AADULL, 0x78424CB89D4B0E02ULL, 0xD73321970DA14B31ULL, 0xE04869F56FCEB616ULL
        },
        {
            0xB5AEA57FC980B52EULL, 0x408BF4C71BA7E0B2ULL, 0x81F904F09EB492BEULL, 0xFF1A534C1571D812ULL, 
            0x94FDE96A6114BE9FULL, 0x0B14E15E82C7FE8CULL, 0x5498E9272E1C0D96ULL, 0x8D328092B62CD4BAULL, 
            0xF3D864200F8BA791ULL, 0xCA045BBDB866B025ULL, 0x24F6269485C42D37ULL, 0x0FC6E3FBC8FB9ACDULL, 
            0x54B26538AD287945ULL, 0xA7E926B2C4B13CBAULL, 0x36A7D0DFE278A60CULL, 0x11A01FAEA3F6F0D0ULL, 
            0x2470EB787744C449ULL, 0x23E264F2751A0049ULL, 0xB5A94EB3CB7015D9ULL, 0x3471BAF1C3EEFBF1ULL, 
            0x2C5AB6A4213F79CEULL, 0xFA3B801C9FC228E7ULL, 0x74C4A384ED4CF033ULL, 0xF4F96B3C3DF2F872ULL, 
            0x351133FC3CDBB9C7ULL, 0x05C5A39F61124A55ULL, 0x00E195A5E7E23768ULL, 0x72235F790B4378EBULL, 
            0x2F28F97BAF90845EULL, 0xB0AF26E4D9A8CF19ULL, 0x70E55C66EF072336ULL, 0x75E2E3125426194DULL
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
        }
    },
    {
        {
            0xF3B48897775BB9B2ULL, 0x9B987F335AA276EFULL, 0xBE87E58BB467543CULL, 0xBBE130EF954D74AAULL, 
            0x5C372F57332789C1ULL, 0xABD558184178149BULL, 0xE8BD9DDDB4307FE0ULL, 0x27D36B6598BF0683ULL, 
            0x7E38B166597B054CULL, 0xF6D1C0BF7583B194ULL, 0xC80ED1052EE92141ULL, 0x170442E00A6CE183ULL, 
            0xBD14CA97FC3DCA0DULL, 0x1D473C6D09706DB0ULL, 0xC7B0A6919A8C080AULL, 0x03712A9F3A57FED3ULL, 
            0xFD69A4422A6A4DFEULL, 0x4AEBCAE72853456CULL, 0x2B0C7737D8F74A30ULL, 0x7E5FBE1437432A1EULL, 
            0x9120178ABA73FED9ULL, 0x9F399ACDC506A30EULL, 0xB3F9FE40A112ACCCULL, 0xFA8453AB60BE5535ULL, 
            0x59321DAC32D3DB2CULL, 0x08098BE0142A08C3ULL, 0x7FAA38943417B477ULL, 0x9596C19D1293F298ULL, 
            0x377C38A85D0C67B4ULL, 0x012F5EEB9182145DULL, 0xB3B0C11C8235E9D3ULL, 0x386AEF28A6F1F50AULL
        },
        {
            0x8F2356E46BE0D1F8ULL, 0x5B22E0504AD3086DULL, 0x578BFA0EBE82552CULL, 0x244BD9970FEC1659ULL, 
            0x3BE2944BACBBEA56ULL, 0x2A86D74A419CBBDFULL, 0x2F62A9FD87904F14ULL, 0xC58A48BC0BA5FAF8ULL, 
            0x07F42090F57099F0ULL, 0xCEF9E1A582D4555DULL, 0x1F9B376BD1C3B123ULL, 0x480A14B30807CFDBULL, 
            0xE91ABC10906B48D2ULL, 0x293A29BDE0BE11E1ULL, 0x4EC974F39238919FULL, 0xD8B0C44DD6FDB9A6ULL, 
            0x671CFDCAE2CBD39DULL, 0xB7AD1F6672B2A45AULL, 0x1B3A68207067B5D1ULL, 0xB6D518DEB932806EULL, 
            0x7CB3F89A2A56BF4BULL, 0xA081EBD830986968ULL, 0x70287DFB94889950ULL, 0xA48D0D2960E03C77ULL, 
            0x97000635DFF8503EULL, 0xEEB1D9CBCDFF7B75ULL, 0x732081D5E7529DC2ULL, 0xCECEDA4CFFF791D9ULL, 
            0x02AF9E3B30321429ULL, 0xC50B15C2AE181BA3ULL, 0xC80B8AE9245625A6ULL, 0xC9AE8D4527AEF9CDULL
        },
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
            0x6968B4A3513D1928ULL, 0xC4B1BF11A6B3B048ULL, 0x02A931648658E23DULL, 0x906382DE96692C5DULL, 
            0xFF887554500D9FE6ULL, 0x582A30979A02886BULL, 0x937CE6280C40F58DULL, 0x1D2D0D113B60FD16ULL, 
            0xAA94E9B172C03EF7ULL, 0x0DD04804F7790505ULL, 0xC8EAAF89D71BF91CULL, 0x9F7853D15D21E232ULL, 
            0x8D989E8F7357346CULL, 0xA34AB2FA2F411F00ULL, 0x7C27354C461BB55CULL, 0xAA92E82A1A7B8F8EULL, 
            0xA82A3EE806E2486EULL, 0x2D1D03FA268B0750ULL, 0x17649F6C0AB5B9ADULL, 0x5FA769D753429CC1ULL, 
            0xE3C64B6FFDD43D69ULL, 0x24DDE5AF9CAD798DULL, 0x3C17C86D3BB32B71ULL, 0x23410609C414FC55ULL, 
            0xF3BA1EB8DE6CB4B8ULL, 0x81E25AEE67D462EAULL, 0xD6574E6B53E66CFAULL, 0xE309DFFC744878C8ULL, 
            0x72E037946639FC4FULL, 0x92AEB69B2335CAB8ULL, 0x140023F8F0C4ADFDULL, 0x5DAF90BC1A8DEC5CULL
        },
        {
            0xB6073662DFD71097ULL, 0x548443F7530C671FULL, 0xD18E27B8CD863C6FULL, 0x92F275DC85DFDD0FULL, 
            0x56795D21C81F794DULL, 0xC0D8556CC97555A0ULL, 0x2D5B637FCE822F8AULL, 0xD0A304A20958B142ULL, 
            0xB5C0E19FE1B3A42BULL, 0xB886288752F7491BULL, 0x7788BAB1AF224CE6ULL, 0xC6CE702E1DC62ED7ULL, 
            0x29D0904D2F55417BULL, 0xCF09A53DF800D342ULL, 0xDDBDB85621FC01AEULL, 0x5BE8CE2326A8510DULL, 
            0xC05AB8AC4983F26AULL, 0x7B5CFC9B4A3BFDA3ULL, 0xACD8B2EABD5E0808ULL, 0xB0B6D76855E11D34ULL, 
            0x87CC3632FAB132A8ULL, 0x5CB3E1E68576D3D6ULL, 0xEF796852A296BEE9ULL, 0xF4DB4129C6526D69ULL, 
            0x8FA7E74C955DD3ACULL, 0x54015BFF5055D7DDULL, 0x3F614F822FEB96FBULL, 0x4AF2FD89E38AD3DBULL, 
            0x1E1E854C4CC67B97ULL, 0xD7FBAA5A2BA43400ULL, 0xB8EE47F30956403BULL, 0x158F033527D72DB1ULL
        },
        {
            0xC1AB3821AB311967ULL, 0xF47DD03D8D849C2CULL, 0xD2E48CCFA9E12C16ULL, 0x28570374C895FDEBULL, 
            0x4CB7F8372356EEECULL, 0x5794BD6208E0B277ULL, 0xB3037FE54C57F577ULL, 0x1AE2324FFFF0A89FULL, 
            0x645532C499F373FDULL, 0xF133AC9CB1C3556BULL, 0x36C33FE8A724424EULL, 0x66D677864B5BE0AFULL, 
            0x168D671C85B66158ULL, 0x23155FF2946C136CULL, 0x4BF2F811040545D4ULL, 0xCA777E7C69BE2BEAULL, 
            0xB8A60721426ADF2CULL, 0x8112EC6F21FC5B84ULL, 0xEA2C23ABD3816BB7ULL, 0x3CDB10116F574D85ULL, 
            0x33AA098F24650610ULL, 0x95FFED50F1A847DAULL, 0x26360E44DB9E5A08ULL, 0x5E5CAFC4032BA7BBULL, 
            0x7DEF03F524973097ULL, 0x46DD802AC5CA5287ULL, 0xD65B5991563EA0BAULL, 0xDBF08A82327B274BULL, 
            0x9E993B1711DFD898ULL, 0x7C90526EB2171F66ULL, 0x3CFEA496F43EB3AAULL, 0xADA53D97337753DBULL
        }
    },
    {
        {
            0x2D5A397BA52EF9CAULL, 0x892449D8D03265E6ULL, 0x1A9C558C9E81A189ULL, 0x38AF241BE0C88359ULL, 
            0x492B8864A916BDF9ULL, 0x4EC6D1E127CD305DULL, 0x30E6AC67A3CA176BULL, 0xA4D9375E03A0F3D0ULL, 
            0x9BE3D787733A3FD4ULL, 0x4D78587AB6CD140CULL, 0x551E183050DEDCFBULL, 0x0310D35C46684A90ULL, 
            0x976DF139B6A2A4C3ULL, 0x4E3852D9F1764D6BULL, 0x3C06386441B0DC77ULL, 0x6D7A7B445DBA3D1DULL, 
            0x071BCD26875E4A54ULL, 0xEBF5E31D034F0450ULL, 0x7FCB8936BD353B14ULL, 0x604E42D22F69A697ULL, 
            0x0D64B58A910B15B2ULL, 0xD3D9753A6F18A5FDULL, 0x88DEFD77B5DBA2A8ULL, 0xE52625BFB0598F1DULL, 
            0xE5AEFDAFE483B54FULL, 0xD253BAE2D24F0A40ULL, 0x57DC3F1A0A5F3A9EULL, 0xA6A6252D0A21601DULL, 
            0x8AB7EF3F92579767ULL, 0xFDED77F310579AAEULL, 0xDF21FB13ABA73EA3ULL, 0x373E273323002350ULL
        },
        {
            0x4A0E745D791DF75BULL, 0x76DDBF039D6D8C2BULL, 0xA1E988C7C7E2BFFFULL, 0xA0FE122286BA5CC9ULL, 
            0x987ADBD1E83A3130ULL, 0xD4DA2D4A5836D141ULL, 0x7266FFC762E29391ULL, 0x9B1769A44BEB6742ULL, 
            0x113C4FF7AD43CBAFULL, 0x5C81F42D93E99AC5ULL, 0x3191A776ABC44FFBULL, 0x954132685C57A79AULL, 
            0x66A7505A6E488267ULL, 0x0F3DB31B28CA3405ULL, 0x61EF58487CD7C2BAULL, 0xC6648966368D1E29ULL, 
            0xAAC20815339179ADULL, 0xD94656E77A15D87AULL, 0xA60E4E058656D021ULL, 0x4441A2285DB41681ULL, 
            0x6087E33910EE6856ULL, 0xCD64D23286EF718AULL, 0xABEB0F9CD6998FDCULL, 0x2CFB0B3F9CE8C964ULL, 
            0x78F8904208C3400EULL, 0x42F634F2506C45A3ULL, 0xC4DF2CB1C451D886ULL, 0x42EF8235A15C05ACULL, 
            0xBD8023A00360A069ULL, 0x18434A42FD9EF754ULL, 0x894FA5EFAE19BE20ULL, 0x42364BC6E81DA5CDULL
        },
        {
            0x3D17E770ABDBD1DFULL, 0xD565DBE3F6E621ECULL, 0x25E5622F8937565CULL, 0x6C1BF9C35E497B6BULL, 
            0x51658874C7331B4AULL, 0x36FCBAD20B51A86FULL, 0x81791024FCAD82D9ULL, 0x114DD574E1719D99ULL, 
            0xB4F54D7F64940174ULL, 0x94F632D0D7281CE4ULL, 0x3CD1020F0C8BE9A6ULL, 0xCB222CE13929E362ULL, 
            0x72A1B221F748E937ULL, 0x0E5AF076A0670495ULL, 0x9EA8CD447B4196A8ULL, 0x9C4C8B73356822DEULL, 
            0xBA40D8D2A548829BULL, 0x3B5A20A0EAA68454ULL, 0xB8B015FD94A4038FULL, 0x0F43ECDC44F81A3EULL, 
            0xE92FD0FF24BF3F2AULL, 0xDFD493AFF6C2F24BULL, 0xA649B541BCC6B75AULL, 0x83FEF1DBE4C84374ULL, 
            0xB05CE74F1C03360CULL, 0xA5637D30FC8ED54BULL, 0xD7D52B7D135B2D2DULL, 0x6F0012EAD6C91081ULL, 
            0x0DAF22DCAAA08398ULL, 0x32E7B0D72E94B9C2ULL, 0x5CB933D2D60EDABEULL, 0x4A782C3ED146C6DEULL
        },
        {
            0x417495EF7C70FA87ULL, 0xFECDD3035B01110FULL, 0xBFF05FAE7673BBD2ULL, 0xF3B13C0E2FAF00F9ULL, 
            0xCAC093F0726C1C08ULL, 0x1C5D2F0BAD627BB6ULL, 0x40402C7A5658AB08ULL, 0xE873FA194B563F1EULL, 
            0x6FA7E35F5A8AFAACULL, 0x939A743136A43D28ULL, 0xED699E9DEB5377FAULL, 0xCCB635BDD50CC5C1ULL, 
            0x4B5FCCC7386C1709ULL, 0xBC7D17F96142C023ULL, 0x05D13D12B8091772ULL, 0x826011C4D6E730F5ULL, 
            0x85AFDC45F68D22C1ULL, 0x93AA0672351B9600ULL, 0xC7CF33E5138E380EULL, 0x696B8CF189795C31ULL, 
            0xE1807877EF779AD5ULL, 0x60047B31A2606681ULL, 0x6BC763A269D5FF63ULL, 0xF5EA9A70E7C07867ULL, 
            0x9AE037A2DECA672FULL, 0xAC00E532019FF422ULL, 0xA5AA8F8D1FC46325ULL, 0x9E052DA61CCFBBBFULL, 
            0xA977849CE59108C1ULL, 0xA0822B546DD7AC45ULL, 0xA6E85CD38374A7C7ULL, 0x02BD9564AA702242ULL
        },
        {
            0x5209C3FE9BAD0B8BULL, 0xFF225A8A1D98DC1FULL, 0xA59B5B259D87D895ULL, 0x89B75D28F2CB8593ULL, 
            0x7B9E5A814920EFD6ULL, 0x53B6899BB7FD926EULL, 0x9FAC7409E96D4509ULL, 0x74DB65A87DBAD09CULL, 
            0xF0537BCF49BDE834ULL, 0x7D31C5E6B1E2C251ULL, 0x064B8B2938088748ULL, 0xA684E45F560EF129ULL, 
            0xFE83B60A3D72814BULL, 0x89540B108762B1B4ULL, 0x24034B470780C577ULL, 0xC16E554BBCE0F9B0ULL, 
            0xA0ADCA297A9295DCULL, 0xDF868699D04FEFFAULL, 0xD49E5BA4FC93E2EDULL, 0x15B8CD11DB72BC5CULL, 
            0x4FFC162F4E2DA514ULL, 0xAEFE81B9510C2470ULL, 0x83628B15770EDE0BULL, 0x631D684505C47438ULL, 
            0xE891256BA2B66785ULL, 0xDE3DD0B807EF7C6FULL, 0x272E5D11D8FC7127ULL, 0x2D3D38CE3BB29020ULL, 
            0x3F328B5C2246BEBFULL, 0x3D5EFE97D86063B8ULL, 0xC6EB043875FF9639ULL, 0xCDE43BF28DBA493DULL
        },
        {
            0x0D1BF31036E1E0A2ULL, 0xD99CDF653D10098BULL, 0x490B9DAA3338E9CEULL, 0xE626A821A2488FF7ULL, 
            0x8D7807E49547F845ULL, 0xC7AC7D0CB41662D8ULL, 0x6888DC6C6B46C319ULL, 0x2D4F0A9D3B15AA72ULL, 
            0x15BF477D644DD900ULL, 0xBC18AE284063C2BFULL, 0xC323725C74C678C3ULL, 0xD311E2E2DC6CEC8EULL, 
            0x1C47D13F8D218354ULL, 0xC4131553AB7CDD13ULL, 0xF76479C9F9228061ULL, 0xBEA5D3DE399AE850ULL, 
            0xE689B57F444586C2ULL, 0xA0C47C8052EBBAABULL, 0x49DEB42923880A6AULL, 0xCF86D301028D10DCULL, 
            0x4374702E3FC9B175ULL, 0x5307E3943E87C2E0ULL, 0x4C295F340B7E9AA2ULL, 0xB1B2505579A452AAULL, 
            0xC9184C22C8337994ULL, 0x755745DB25F8B033ULL, 0xB8899559904ED5BBULL, 0xE18325B8F9ADB3AEULL, 
            0x67BFC43A590B3654ULL, 0x93A217F4924FFB51ULL, 0x3C59EAE70DF28971ULL, 0x946257D1FE79B9FEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseCConstants = {
    0x8CC3C4506A6897C8ULL,
    0xA6FE43892D90C68BULL,
    0xEC0264534FFC636CULL,
    0x8CC3C4506A6897C8ULL,
    0xA6FE43892D90C68BULL,
    0xEC0264534FFC636CULL,
    0xA96359AF62BBD56AULL,
    0xBEC79205F6A91B95ULL,
    0xE2,
    0xA5,
    0x37,
    0x7F,
    0xE0,
    0x0C,
    0x2C,
    0x80
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseDSalts = {
    {
        {
            0xA7C6B75DE4DD951DULL, 0x14A98047ED43E7CBULL, 0xB98B56B086D7E1F2ULL, 0xDABD8BCC3213F701ULL, 
            0xBE067F989CA54D5FULL, 0xEEB3DA6713C316AFULL, 0x00008ECE13A963DCULL, 0xAD0B54501CD82D1CULL, 
            0xA170BA5627D7A517ULL, 0xB8E46D0CD661EFB3ULL, 0x543EB94675265E2CULL, 0x9C32F8A887057DBDULL, 
            0x5C9BFBF46DE46DC7ULL, 0x9BBAD3C1DE75D1EEULL, 0xF7ABAD2170D4ACF9ULL, 0x56ECF7FB6AD9AA1FULL, 
            0xEA878ACA680A1B2DULL, 0x298DB682FE04E4A0ULL, 0xB4BA8BA2B910B348ULL, 0xDEEF9245AF7A585DULL, 
            0x99701AC641707F53ULL, 0x9247D05AF3DAE605ULL, 0xF372B90016B8241DULL, 0xBF36C1CB6E5D9AC4ULL, 
            0x6390014100434EDFULL, 0xCDBAA09CA99EBC9FULL, 0x890338BAE736D946ULL, 0xCD2E38799B2C58DEULL, 
            0x53770435B86A7103ULL, 0x45631F1A3D600EC0ULL, 0xB37BD95206FDB91AULL, 0x97A9CA038B207559ULL
        },
        {
            0x48E0E94DA0BF065AULL, 0x69F7A781F6DA6560ULL, 0x6DD86F477D588424ULL, 0x8952388C3C44994EULL, 
            0x4AEB85B7F0F6E022ULL, 0x506BA940C951A1CAULL, 0xD5435DDD29EFCCB5ULL, 0x33985FDAF5BDA15AULL, 
            0xFB117A3482B5DD93ULL, 0xB81AC742E8D9DF52ULL, 0xA9119833AA32F45AULL, 0xBA1570A9D84C3E05ULL, 
            0x7FEE969C9700A61AULL, 0xB13730E3A27E0AA6ULL, 0xC4623736D377014BULL, 0xD1E46020E2CF6F3EULL, 
            0x770BB418B6DFBA13ULL, 0x663795F3A39E9D2BULL, 0x4CE53BE186B44361ULL, 0x7CF2BDDAB3AB60D8ULL, 
            0x40D56E2378ACAF69ULL, 0xFFA50FFE655EC761ULL, 0x061B7B713CC1D33DULL, 0x51C2FF207FA20445ULL, 
            0xFCF50C9392417894ULL, 0x50CE39A7D02DA7C3ULL, 0x115070D1E457A137ULL, 0x3B0087A07A9599C2ULL, 
            0x78F411B8C28ACFE4ULL, 0xA74BF6C2B258167DULL, 0xF1D1D0B413FD3B58ULL, 0xE2828783480EAD94ULL
        },
        {
            0xDB14B3616BDF065AULL, 0xE7B2FF9637101CBDULL, 0xC5719FD4A4552B73ULL, 0xA3FC85ABC9B017FCULL, 
            0x42426F913BAC77D1ULL, 0xADB33243CBF9C5D4ULL, 0x02FF6F8EB4774695ULL, 0x9AB19AFFAAD77602ULL, 
            0xC85E5B8B1A3D384BULL, 0xEF7E7C692FCB2EE2ULL, 0xEA6F92B7F126C049ULL, 0x8C015A2325834919ULL, 
            0x3C77FA9A3D09D87FULL, 0x7F547C9DBAED6586ULL, 0x94BC6C58E9B1910FULL, 0xD69AF5D5FAA55929ULL, 
            0x30F11F7300B28FE4ULL, 0x2587794D8F32DF50ULL, 0x162D8814D9906B0AULL, 0xC4628A0EAE1CAEEFULL, 
            0xAEB53633D581D522ULL, 0xE1F7855C76AB901DULL, 0xB3284CF44E9849FAULL, 0x6A0221F143C0D41FULL, 
            0x1F3D3E05E4662D38ULL, 0x5FAB292BEE42D46CULL, 0xA794835024E806E9ULL, 0x45B4ED8F920C1A65ULL, 
            0x4FBB954938F72084ULL, 0xBC4AC801529C5D95ULL, 0xAA4F68BE8C114AECULL, 0xFF78365EE1FC1A99ULL
        },
        {
            0xAAD102F4E9ACD6B5ULL, 0x44B6E3CBF6EB29DDULL, 0xFFCBFAEE2D2C8852ULL, 0x33D5BED61ABB2B2CULL, 
            0x2C9E36C598DE5972ULL, 0x6D4CAC88C63E9F5DULL, 0x2EB118AC380A2681ULL, 0xE70B166A3DF8BCB0ULL, 
            0xC39DCA3A3907A16BULL, 0xD45817096E1AF855ULL, 0xC80F49AF032468C1ULL, 0x5D08853A7B6A1223ULL, 
            0x695FA40D9DC90855ULL, 0x91BDA0AEEF646E13ULL, 0x5BC90FECF3E03F66ULL, 0x90397ADC3A1E90D5ULL, 
            0x12EFCF78E4A11577ULL, 0xD260DB6FD1A2AA41ULL, 0x15F033ED89168434ULL, 0xF9F6C7EC2ED6A947ULL, 
            0x8150572A4A1C19BCULL, 0x87EA61DB7385BC16ULL, 0xD4D70FFAEBB95E58ULL, 0x1E5E7AAE35F52C8DULL, 
            0x41C1F89CE06B6E91ULL, 0x19F183CF68521560ULL, 0x647FD6DC110C7B7AULL, 0x9ABF8C97D2DD9B4DULL, 
            0x21069671E8751A12ULL, 0xEE219F5A57820DAFULL, 0x7DE0EC17DF3CF8F4ULL, 0xCDB394A2609D75FAULL
        },
        {
            0xCFB219F22F02E0E2ULL, 0x3E7A329257A620CEULL, 0xE2EEB977FEB26BBFULL, 0x44D1E237DD7FA935ULL, 
            0xC1130C423B9E2EF8ULL, 0x4E95D083F12BCC9DULL, 0x51F0339F91A8813CULL, 0xC8A3F6B90208664DULL, 
            0x452BF3BE209BD65EULL, 0xDA4B23B4FEDF3E8FULL, 0xF389BB8343C20723ULL, 0x7FB5B72599CC22BAULL, 
            0xF996B8F2CCFF45E8ULL, 0x5676EDFA5AFD1F1EULL, 0x4EDC560F6DE8C986ULL, 0x46CE227FD95C6E6EULL, 
            0xCF4CBB5D19D68415ULL, 0xD78D31C6B0A1D315ULL, 0xDEED098AB8D0B446ULL, 0xAD3E2CA6785E3B7EULL, 
            0x93CD7F3AC63253C3ULL, 0x9F6AEDCA6DBCD7FBULL, 0x9F8548705BE1B228ULL, 0xB3780FE3E7303E35ULL, 
            0x1F67160D226C9998ULL, 0x9F4A3E9F9F48A6CDULL, 0x35AF181FA2C7B381ULL, 0x6D50B93DC0429DF5ULL, 
            0x92C88703764FCA73ULL, 0xDA678E7F990EBA8DULL, 0xF415083731758F72ULL, 0xB29C12FCDAAE12CDULL
        },
        {
            0x77CE453F8E9CA39DULL, 0x7B3C587793EA165DULL, 0xCC428DCB549F92A4ULL, 0x0969D88592FC31BFULL, 
            0x2CBA4DDAF6F9AA8EULL, 0x1CC871429D917E7BULL, 0xDA915E3E4B4E5C1CULL, 0xC0449905C713CF10ULL, 
            0xA89F744E6004974FULL, 0x3078B934DC93C2FEULL, 0x312ACEAC061380F6ULL, 0xA263A1508E5DEBC8ULL, 
            0xF1F236E20506858DULL, 0x9AC05EB7B19F44D9ULL, 0x181A450F93E3A613ULL, 0x0334F70C41FEBFEAULL, 
            0x3FAF93EAF6912EBCULL, 0x3880BE508BFC3575ULL, 0x1A44A447085AC816ULL, 0x698E92E4611DACF3ULL, 
            0x169733C477799153ULL, 0x2546B459D9059755ULL, 0xBAD1864C376961DEULL, 0x0F381BB5A3B1167AULL, 
            0x39AA9B7671FAA8A0ULL, 0x6E44DB86BA875524ULL, 0x3AE19034FD006BA7ULL, 0x52D9596BDCD86FF9ULL, 
            0x6535E1C3A6AE0C49ULL, 0x646DE7E2065B0C5DULL, 0xF081AE79EE3BC3DFULL, 0x2C6643516677FF70ULL
        }
    },
    {
        {
            0x63D0E78D985B1728ULL, 0x554EEB7E98130B5FULL, 0x1608F30322232AB0ULL, 0x2173A4F5C4F78BC1ULL, 
            0x7BB677AFB1D6A72CULL, 0x51B84610AED96A97ULL, 0x7AC6A758131F5D73ULL, 0xF348EF44B589C2F9ULL, 
            0x84E673EE85233F5BULL, 0xB26EBBDA627F5DA3ULL, 0xD094A3572EA85952ULL, 0xB61770A8AFB8D141ULL, 
            0x27C820038CEB56FAULL, 0x98C57F81CCA585C7ULL, 0x65C4DE59ACD97E1AULL, 0x827F97B6F4A03FB2ULL, 
            0x7CD409D472F91C28ULL, 0xC093D78D72327014ULL, 0x3133179EFF43C1F1ULL, 0xBECD1EF4BB3A0547ULL, 
            0x477C6EBB55F8031BULL, 0xE13884393F7E69B0ULL, 0x03A1A53FB89FB897ULL, 0x30EA5B2D3BCD6D43ULL, 
            0x110180C677783DBDULL, 0x795F17B3E99C22A0ULL, 0x1A7BA6C3B9FE126CULL, 0x011F82913DBAE03EULL, 
            0xA7F79FC9F2AA68DDULL, 0x7B7C3FDD83CA66B4ULL, 0x92C542804FE7F107ULL, 0x7AFAA41F56CC28CCULL
        },
        {
            0x89CD5E55FD112721ULL, 0x14F14DA32407477EULL, 0x9756F2ED8BAB9462ULL, 0x8768962AD39459D5ULL, 
            0xA9423600BAD461EFULL, 0x5646A6C9A20B0BA8ULL, 0xAE2146B9AA38CF96ULL, 0x829B5542F6424A16ULL, 
            0x6456A635FCCBE519ULL, 0x217809FBD54F1104ULL, 0x3BF5E7175D41106AULL, 0x1A4722C915E5B1ADULL, 
            0x1BCAF05E508E5718ULL, 0xB033AF34D1571728ULL, 0xDA59E06F71603EFAULL, 0xA64047D36E31BC6CULL, 
            0xB367B50766D79DDAULL, 0x044278C24CB1A7FBULL, 0x43DCCE85FF9D34C6ULL, 0x64260F7C8E85DA45ULL, 
            0x801AA8700FCF2D66ULL, 0x2D2D6BEC0E87D0B5ULL, 0x31B17D98165E3BFCULL, 0xD86E368F2B39E950ULL, 
            0x5691FBF817F690A5ULL, 0x3219F4D6E4C63E41ULL, 0x371C23F5DDA98C8FULL, 0x6E9417361B1AC577ULL, 
            0x9D0FAE55DBDE46F2ULL, 0xA6EDABCA5B0BBC57ULL, 0xBB2F603C04BCB7C6ULL, 0x4663AD31A26A10D9ULL
        },
        {
            0x82F1E31C6CB6075DULL, 0xCB04BBEBED8E6A27ULL, 0x72532477CFF3F96FULL, 0xBC1CF37552D05DE2ULL, 
            0xF98EA5893C46FECCULL, 0xCBC67DB14968DD8EULL, 0xB5285733EA55E220ULL, 0xC004A48072FD1CDAULL, 
            0xBECC7D575759324DULL, 0x3CFD95524C032506ULL, 0xCC240C090FF21184ULL, 0x614D3BFFD4EFBF5DULL, 
            0xCF5E332D0F3367DCULL, 0xB18FC4BAE40C61DFULL, 0xE1385C82C841A3B2ULL, 0xB043AA7622EDF5E6ULL, 
            0x651F871E01F4EF15ULL, 0x93ABF9C6A4E3BCB9ULL, 0xA931E62C46CD63D1ULL, 0x4AC4C484DE5295A8ULL, 
            0xEE19D773758FF877ULL, 0x1D311D4F85053DCAULL, 0x0C0060546422F381ULL, 0x833A9E6741E29E0CULL, 
            0x661D31412E25734CULL, 0x62588D843E2E61A0ULL, 0xF9C7F1E5C780428AULL, 0xD6C495121CEFD336ULL, 
            0xE6386ED7819FC89CULL, 0x0EF6FC8580A4100BULL, 0x3B43027E473D578EULL, 0x9C1DFA6874CB0A0CULL
        },
        {
            0xDC5CA1768124319FULL, 0xB470132E56DF46AEULL, 0xCF05D9B81622DDBCULL, 0x4D532D68392E6275ULL, 
            0xF691194B8199427CULL, 0x1898409C3F4F457AULL, 0x503F28C74FB0AF43ULL, 0x7CEDDF380FAE47E8ULL, 
            0x7C260137A948A736ULL, 0x0C8A290D07BD6110ULL, 0xD3FFC8E4DA556972ULL, 0xE55B188135076529ULL, 
            0x92D502ABCE128DF1ULL, 0x0C98CA352464C0FEULL, 0x8A34655BFC85D399ULL, 0x76E886604F08E500ULL, 
            0xF20E64AFEF7B0565ULL, 0xC8E36ACEF6E0922DULL, 0x4DDCB93D26D0F63DULL, 0x2AFA037B8BDB2CF6ULL, 
            0xD803E22967EE0966ULL, 0x843E02D1E911F0F5ULL, 0xA6C742B9AC020339ULL, 0x00EB73C8CA0C18ACULL, 
            0x6374D06BF0C5CE5CULL, 0x1A52FE113557511BULL, 0xB84EB78B2500EA26ULL, 0x2473148B93AE725EULL, 
            0xB0EA1C4BF0469132ULL, 0x134B820B4A6D9870ULL, 0x09B8098A6BA5AC16ULL, 0x23E7954F67B997F5ULL
        },
        {
            0xF6DEF14C1CA0E37AULL, 0x7E29A562462B7BD2ULL, 0xF180DCC2B8C4F1C3ULL, 0xBC678321DD74306FULL, 
            0x4C5292988EFF0B42ULL, 0xF87E77BFFD6EF7B1ULL, 0x234BC82A58702C6BULL, 0xAFEA03016899A9D0ULL, 
            0x7EC487915030657AULL, 0xD3FB3E906160373DULL, 0xFE26702F775B5AC4ULL, 0xEBFE194EFBB0060DULL, 
            0xF9C69220A3B7CACDULL, 0xA03A4E8B3DB9632FULL, 0xF24893A5F665F959ULL, 0x2D6A240C0A6544D2ULL, 
            0x0C0957B5EB216B70ULL, 0xD087AC1EC64B3D97ULL, 0x7B6B8F7C529FDAF5ULL, 0xC770CE4C088357DEULL, 
            0xDE63EDD2193BB743ULL, 0x3142AB735E0614AFULL, 0xAD4E9F420AD61D27ULL, 0x67B338AFDA8A06ABULL, 
            0x77136872AAEB047BULL, 0x5107D2B1D108D3EDULL, 0x553353F08BE2D58CULL, 0x8984D801B0213806ULL, 
            0x6873BE215E39E353ULL, 0xA2CE37A5CEA5CD4AULL, 0x83D7EFC77B3A9C33ULL, 0x0996FC4E8CA878B1ULL
        },
        {
            0xCE10DD78673651A5ULL, 0xC4B0AE5757F7E190ULL, 0x331A5FD01108911DULL, 0xD335445B4850901FULL, 
            0x49098B4E8C4B9F1EULL, 0x40FD9D33A3C52342ULL, 0x778BD3248CE5BF06ULL, 0xDD88433A71178FCEULL, 
            0x96BA751630F7BCC4ULL, 0xC0EBFDFFEEAD4708ULL, 0x3066AA2FC108EB76ULL, 0xF1E25FBA7A007984ULL, 
            0xC4B4F6788529E620ULL, 0x10A1754F1942E087ULL, 0xCF22EBEDE0E7C939ULL, 0x77935871F539C9EAULL, 
            0x0D3A485100FF8400ULL, 0xD55006708DD7A7A7ULL, 0x1EC8B0C0982F416BULL, 0xAA25357C67022FCDULL, 
            0xD93E4EDDBC5F1136ULL, 0xD83C63AADC552C10ULL, 0xBFD0201CBF669519ULL, 0xEA63E5C56F220C40ULL, 
            0x3381FA8F5A9AF30CULL, 0xD3D4FABA52FDBF8FULL, 0x53E14989B8CEF5DFULL, 0x6E2E84C6A4E239B2ULL, 
            0x7303C321AF743B9AULL, 0x296A3FE5F597A405ULL, 0x8925F2D2568D82C5ULL, 0x70ADC8CE966B2AB0ULL
        }
    },
    {
        {
            0x639C725B03289761ULL, 0x53730CBECAA9891FULL, 0xCF47DBE44C1951E1ULL, 0xC325154FA304558AULL, 
            0xDD3AB5DAFEA51B63ULL, 0x863A1850483B3AE7ULL, 0x1209822CAD80209CULL, 0x24EC058B46010596ULL, 
            0x1A1883F671C679FFULL, 0xCEF4D37872DB9B08ULL, 0xA44CC638189A553EULL, 0x43A649B09B756BBAULL, 
            0xACAAE06DE03D136BULL, 0xA4D2D68BEF416090ULL, 0x67C37C5003E4F48FULL, 0x6D62B6725481479CULL, 
            0x9507D3C11A4901EEULL, 0x552AABCDD9D26686ULL, 0x354BDF8EEF934992ULL, 0x88404DE3A0649054ULL, 
            0x418F928ACC5D1285ULL, 0xAFFBCC39AA97E184ULL, 0x471056658E743E2DULL, 0x574F1785566FFCD0ULL, 
            0x14CE5FCC9CCF2B27ULL, 0xC3419F5E84EBF63FULL, 0xF4C65E8044BC72D1ULL, 0x565E3AED6E92ECD6ULL, 
            0xBACAB922554102CFULL, 0x4C09B428CB1F352BULL, 0xC7EF11DC10FB49ADULL, 0x0121F44231BD59B0ULL
        },
        {
            0xDC5155B56293476CULL, 0x84BFF34BE5019E00ULL, 0x77DF0230A8AD2FF5ULL, 0x3CC242529CCBAA56ULL, 
            0xCCF74033554E19DCULL, 0x8E01CF7488C658DAULL, 0x7A97841750A7B233ULL, 0x5E793789B680B42AULL, 
            0x8F1CED75C540BC66ULL, 0xBE8E9A9114624E09ULL, 0x34F27DFC5C8324B9ULL, 0xB27CF5B1EE7A4690ULL, 
            0x97B3C5295D36800AULL, 0xB1526F895E3034AEULL, 0x49CA2FD61E828433ULL, 0xBE98E4C3FC5E8F42ULL, 
            0x182B80CE73480872ULL, 0x62B82CF382AEBB27ULL, 0xC76C479D5671E0EDULL, 0x413758A130CD70DDULL, 
            0x23DEBC749B3A0CA6ULL, 0x0C668229DF29A501ULL, 0x77CADA532D300ED3ULL, 0xB3141457F4A6D013ULL, 
            0x65F28FF9D745F599ULL, 0xCA3F189F148AC53FULL, 0xB5864FD3B55DBEC3ULL, 0xBD41755ACC6CF832ULL, 
            0xF2A51C2EFDED07CDULL, 0x459C570F38B993C0ULL, 0x2925EDB54B104E5BULL, 0x85932D7075BF8C34ULL
        },
        {
            0xDC3DD88214E04CA8ULL, 0x277CD585C89B40BBULL, 0xADB849CEF0D6DA7FULL, 0x22127AD1E0F5DC14ULL, 
            0xA566359A77C6F9F9ULL, 0x317055C1D2CB93D8ULL, 0xB75F2E6E2B2D781AULL, 0xC88C31A2FFFB5AE5ULL, 
            0xCE3A04D2E9CE7891ULL, 0xF02853734E9131AEULL, 0xC24EAB11624E2298ULL, 0xE1E60F7589DD7B46ULL, 
            0x6EA20F67F25B19CCULL, 0x14135095ECC6BA64ULL, 0x2661B6A93647C4B3ULL, 0x46FFEFA41D755007ULL, 
            0x2B8292AF8247BFB0ULL, 0xB05F3F81FF7D8613ULL, 0x1456B3ED16D605A9ULL, 0xF51DF5815526EDABULL, 
            0xE1802AE24A656978ULL, 0xBD3E9A305A28B825ULL, 0xF2BA772D63E12ECBULL, 0x59F947F17F87C6D3ULL, 
            0x694FD7A77160353FULL, 0x36960D695A635DB8ULL, 0xCA13890F97FFC8FBULL, 0x4F58EC9F08341739ULL, 
            0x6D852F8097D3ADAEULL, 0x15882EA9ED0D5103ULL, 0x63A69AF2264E0FB4ULL, 0xF7DC577F550CAA44ULL
        },
        {
            0x50A7DB270CFDBB54ULL, 0xB9449D28E010C406ULL, 0x722A573ACE7C08A8ULL, 0xCCFCD8CFB25FC566ULL, 
            0xEEE4290272E848F0ULL, 0xA808CC0A900262DCULL, 0x5F086ADBD702F993ULL, 0xA66EEF6483E44B64ULL, 
            0x55DA6B9EE8C2C6BCULL, 0x06899C234F1CDF69ULL, 0xAA3FD23369FCE0D8ULL, 0x2C6A757069679890ULL, 
            0x6760BFC68E2A7965ULL, 0x4CA9A2BD3995CF82ULL, 0x7F4313CCA6EA4E36ULL, 0x006B626B0EA0362EULL, 
            0xED6F92F52DC9469DULL, 0xBAFF3471D1F86F50ULL, 0xA6A5D537E690A791ULL, 0x4ECD6A8FADA52AA5ULL, 
            0x8BC948270B655BA5ULL, 0x2000E5031DA13868ULL, 0x3FB5E2DF8BEFA172ULL, 0xF28AEDC73C79AB49ULL, 
            0x1E6446569E4308FEULL, 0xEB75118F2C8F5D6BULL, 0x1F0AF77A9F728507ULL, 0xB56D0BED7A5287ABULL, 
            0x810F13AD14DB2B9AULL, 0xE497E761957C41AEULL, 0x5A3E699CFAB53306ULL, 0x69679A46FE9E32B4ULL
        },
        {
            0xFCEB5A5475E10FB5ULL, 0xA02E3E1F1C505E34ULL, 0x17A5766D56AEA2D1ULL, 0x389770D58A5863AFULL, 
            0xA64A482FBD082626ULL, 0xC453AF0F006EDE83ULL, 0x7BA0966A27E64721ULL, 0x4701B0EC9E8C3BB0ULL, 
            0x6B40457F0393F246ULL, 0x164360A1D608642FULL, 0x909E664D1A88DC00ULL, 0xA2ABC81E6DD38C72ULL, 
            0x02E2C141289704D7ULL, 0xDE3A3D841963DA06ULL, 0x3B611409E21349B7ULL, 0x72EE4612D03F9332ULL, 
            0xA134475657F14A69ULL, 0xF961820AEF7A148BULL, 0x926289D97ADE4FFFULL, 0x2E183629FF360825ULL, 
            0xCFD0EF197325EF24ULL, 0x9C41E8B248575C20ULL, 0xA27BA1E655CEEE43ULL, 0x68CD6F13E49F8725ULL, 
            0xF7BA141E8DA7D494ULL, 0xB45410D37DAFE93AULL, 0x20A38A71FD37A2D6ULL, 0x1EAA4F77618E5FABULL, 
            0xB1EF0FF300613BFDULL, 0x375F473E254C2180ULL, 0x4DD9644ABE9F01D1ULL, 0x2EE7570C6BA9F4BCULL
        },
        {
            0xAFADABEDB2949F0EULL, 0xEDEC78E9BD6865DFULL, 0xAAA95C937F4442B2ULL, 0xDA043DB3884B6918ULL, 
            0x967790925C02A1AEULL, 0xF8331F026F23163BULL, 0xB49849F7E5DDBDD8ULL, 0xB603822FAF55068FULL, 
            0xD11ADAF536F8E19EULL, 0xA15CA7C19797FF34ULL, 0xEDEFD3D334F6D4BAULL, 0xB89A2B69EC8F91C6ULL, 
            0x1880E2B2429EA60AULL, 0x99F9535D2B4F227CULL, 0x9DC1CAE47A15F9A1ULL, 0x3B7E8DB9B07ECA6EULL, 
            0x3C86660183DF6E6FULL, 0xD962CDE2BDC19A56ULL, 0x849DCCA4C824B459ULL, 0x64C19D36ED4D2352ULL, 
            0x80B78A087765E68AULL, 0x441C84818E563284ULL, 0xF2C4EAA062FAAFA1ULL, 0xFD72C5618C9B7A75ULL, 
            0x0E99AB056DE7915CULL, 0x1976E287E670CD2FULL, 0x57840043CC7A2102ULL, 0xEB96997FD290D4E1ULL, 
            0x028973D4F8FFC43EULL, 0x57DDCDC80174724AULL, 0x8136129119549177ULL, 0xE74A2ED74D6026B4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseDConstants = {
    0xDA591C2F602A32D2ULL,
    0x6D1487321B188879ULL,
    0x3CE8ABC33EA8F692ULL,
    0xDA591C2F602A32D2ULL,
    0x6D1487321B188879ULL,
    0x3CE8ABC33EA8F692ULL,
    0xBB7C0A3EE2F45ABFULL,
    0x31601CF6A96B6171ULL,
    0xD5,
    0xAE,
    0x10,
    0x19,
    0xF8,
    0x2D,
    0x0C,
    0xCB
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseESalts = {
    {
        {
            0x96F884DBF434C599ULL, 0x12D9BE7BF0B46668ULL, 0xCF4603C03B02B77AULL, 0x0C0EE2B43687235BULL, 
            0x002EDC743F93E76BULL, 0x16A3A481CF379959ULL, 0x8F3F9B53855B6394ULL, 0xDF978922832F9772ULL, 
            0x61846E4D4CBE34E8ULL, 0x69C1E10B5738F0D7ULL, 0xADCAA6AD408CD67BULL, 0xFD4DAEA466AAC6B2ULL, 
            0xC6DF3AB142E51CFCULL, 0x1EEC31CE6EA2CFA5ULL, 0xF7C9E11A4D968C2FULL, 0xC47C1055BFA733FAULL, 
            0x0A87C561B7C308E7ULL, 0xD5ACA6E9CA938B4DULL, 0xE3D9131FFD72D979ULL, 0x07DC769FEBD45ED6ULL, 
            0x39778DB09DD8AD6CULL, 0x58E1C0BA4DBD6107ULL, 0x9E185B40704EFCDEULL, 0xF3797CD7B932091CULL, 
            0x975636251BF9C9FEULL, 0x20CDBBAEC00712D6ULL, 0x9BFCEC6BA208D734ULL, 0xDB51E662CDBF24E8ULL, 
            0x7128105874990A41ULL, 0x0AD32C089139F0E2ULL, 0x3F2A6CEF96DD5AF6ULL, 0x066365451240FF67ULL
        },
        {
            0xC36F3982788D00BCULL, 0x96148646780BC67AULL, 0xFFAF0C45D648A7B7ULL, 0xD87AD7CF105B4856ULL, 
            0xF3C263407B5F8E43ULL, 0xE2BDBECE4E50C3EAULL, 0x30F013142AD668AEULL, 0xA713C2142F4F2651ULL, 
            0x79F445225D652350ULL, 0xE03406B3B1C30F73ULL, 0xA2F7224D08EE44DFULL, 0xE665AC8E532DDCCCULL, 
            0x5C749E3589FDE9DBULL, 0x3A8DC248A69B9921ULL, 0xB4E4563A7BF9C3DDULL, 0xF674446619C91D8AULL, 
            0xB305DC8D52C385B0ULL, 0x587C0833C035D580ULL, 0xB10F143D38BB0293ULL, 0x2B3867F3C599D6AFULL, 
            0xF2B1290BA353BBC8ULL, 0xACAD2DF32BB68D9DULL, 0x7DBEE16D0BE1014FULL, 0x2CB60F4676F93B5CULL, 
            0x5C7B6F3E203F2FEAULL, 0xD911EB754371013FULL, 0x7771AA7B4B61B952ULL, 0x34730C6082C7E405ULL, 
            0x51BF9C2295FCD2F8ULL, 0xC40886FF688E5A30ULL, 0x2739143E1810EA32ULL, 0x43066D6B2948186AULL
        },
        {
            0xB06181E8F27897A6ULL, 0xD4F3E5F4D3D0A554ULL, 0x25F8DB848D02475DULL, 0x56972A38E20974D7ULL, 
            0xFAA7BBD43C4AAE31ULL, 0xDF43571045DDDA0CULL, 0xD12EFE6382FA07F8ULL, 0x792CA3EC163A6D13ULL, 
            0x290CEBDA10A967C1ULL, 0x263F1FC75E7C45C1ULL, 0x0FFC8E96D1FE300CULL, 0x4F995E04CD0AF5D2ULL, 
            0xDB97A3291681D029ULL, 0x313FF1B1F316A2D8ULL, 0xB93169911696784BULL, 0x3682313749431544ULL, 
            0x8164084AD3045871ULL, 0x8171C802E6C3AFC5ULL, 0xD7709F004A8FAC5AULL, 0x8D9D86CED5FC5844ULL, 
            0xCC8C571B82D5447CULL, 0x0F61D2266F3120BDULL, 0xD7C7874730E01990ULL, 0x2077E183FDEA6282ULL, 
            0xBD16194240DD33ACULL, 0xE6B1CE1BA903973CULL, 0xB99EFAD1DD755F2CULL, 0x5CEFEDD54B018CBCULL, 
            0x8ABB385BC12E23B3ULL, 0xC737F5A6D6E142DAULL, 0xCB39715C360DF1C4ULL, 0x7940015A60520F0EULL
        },
        {
            0x657DC126A32251FAULL, 0x97AEEAFC9F74D989ULL, 0x5F08428367798D22ULL, 0x75CAED44CEE076E2ULL, 
            0x825D8403F14AC75CULL, 0x8C056665DEE5F716ULL, 0x29A68F5D6E69DCF5ULL, 0xAFAA1C8D307E8DFCULL, 
            0x701BF6DCAB0986B2ULL, 0x8B8F5BBE6A652395ULL, 0x5A9573BA601A1F0BULL, 0x9CD27E03E08589B0ULL, 
            0x47129711E37B2ED8ULL, 0x1A9BB73087FA7204ULL, 0x9D2DBA14B0E6027CULL, 0x631A6CF4AAB82D82ULL, 
            0x52B61D5AA2903CFBULL, 0xE7BEBF9C653D2132ULL, 0xBA84C40320F72BF5ULL, 0x9D818F67C8B79CC4ULL, 
            0x1FD55D0A7D0EE209ULL, 0x027804FBFD38D56EULL, 0xA8EF49E128B52670ULL, 0x48E207C0E0E06481ULL, 
            0x0A9C35BC6CF68E6CULL, 0x30EAD20D977F80F0ULL, 0x1AA28B2AAF5784E0ULL, 0xAF8CC0CE8624671AULL, 
            0x7DB77D1609C57E02ULL, 0xF2FEFB62385508E7ULL, 0x445E10651735D545ULL, 0x08B8305200C9BA74ULL
        },
        {
            0x4AD568E0032683E2ULL, 0x9EBB675C831F7EADULL, 0xB4460F8FEFDEEF98ULL, 0xD6E733B861114ADFULL, 
            0x5CDC7B342E8BE747ULL, 0x9EC767C6BD85FD99ULL, 0xD4803D33BEDE84D8ULL, 0x727EC3E61C0B8B56ULL, 
            0xAFCC632DC4D6E5BBULL, 0x59919887FBFE5750ULL, 0x88C11DCCCCD5A5AFULL, 0x13CBFF9BB92FB370ULL, 
            0x2E431514968C30ECULL, 0x8D13F3148F7EEFB8ULL, 0x853DBD078CFD8A71ULL, 0x596A7C1A1F116646ULL, 
            0xEFD54D4DEA1E81ADULL, 0x6975FB191BED31DFULL, 0x094E0C400014E898ULL, 0xFF9CA40813647C5CULL, 
            0x054CEB1701E629D9ULL, 0x4A45B50E4E3920A1ULL, 0x1ED5F302E05C7A23ULL, 0x683A22AB49510F45ULL, 
            0x6C18E736858EE528ULL, 0x7FC26554A40B3275ULL, 0xA729186195AC8C29ULL, 0x213246A01AE1078BULL, 
            0x84580E71C44CE2BBULL, 0x9EB609F8CE0FB577ULL, 0x0AF8381384504F19ULL, 0x37A46B2BA5E19A27ULL
        },
        {
            0x7466ECA39518402FULL, 0x012FCA1022DCFC7BULL, 0x309E107895BA02E6ULL, 0xABCED2F3E5098BEBULL, 
            0xE89D0C7BFD5E6036ULL, 0xDE7F79F364F9124DULL, 0x8D90AC48B96645C7ULL, 0x88B2364B9C4D5D6CULL, 
            0x55DBC9D068FEB033ULL, 0xA5E2728F4FC16C69ULL, 0xC13E03A81BEA4B17ULL, 0xF4409702085E060AULL, 
            0xFDF4E530D593966FULL, 0xB9CEA4C694A7EB05ULL, 0x7BE500F9E9136912ULL, 0x5C4177FB149E819EULL, 
            0xF36DEBC12A0762CAULL, 0x400D851C28782DDCULL, 0x96BD3B75F33ACE06ULL, 0xBD65AEB227622A08ULL, 
            0xC55A423F0121C05EULL, 0xD83A6ADD33989DD2ULL, 0xCC3AA93B44D1B544ULL, 0xFC3ADB02CB54BF7FULL, 
            0x09D248A16FA7E874ULL, 0x060959D0BAA18CE5ULL, 0x15F75B3B01750350ULL, 0xFB6B797A4C0ECAA9ULL, 
            0x25F6FC1FAFCEA220ULL, 0xBF1A18BD3C2D8FA0ULL, 0x97A0337DD9F9BDB4ULL, 0xB0450836B4519F43ULL
        }
    },
    {
        {
            0x1F637545655D26B9ULL, 0x65456C9705848B8EULL, 0x7A04C7827FE27001ULL, 0x3CDDD4536C2B507FULL, 
            0xFD31E760E96D5F59ULL, 0x4A44A3CBC96F1290ULL, 0xACC06FCB07831F49ULL, 0x2666CF834871CF20ULL, 
            0x55470E58E1246B1CULL, 0x1CAF45662A237E45ULL, 0xE4D23B060BA38D7CULL, 0x4FDF28C0FC8FA84CULL, 
            0xF01BD5994548E2EDULL, 0x9EE3F436C9DB3AE9ULL, 0x1F7D9CAB82BF806DULL, 0xEED5A8372DC2D52DULL, 
            0xAF94407B93F37603ULL, 0x43C4A63BADFC0EB1ULL, 0x22A4A697595E21AAULL, 0x12A52087D989CBD8ULL, 
            0xEBB8B40D0EEC3F28ULL, 0x74CB47E678E55E88ULL, 0x62D4B58B7142CF8CULL, 0xB3F99A85CE2C3FF5ULL, 
            0xBF86DD965EEC3A2DULL, 0x1D130E69A11D4841ULL, 0xDDD80F65F65D91D1ULL, 0xF4E73A227E27713EULL, 
            0xAD89E48516F94354ULL, 0xB243BF0D0EB3DB09ULL, 0xE3B9EFB80C5A2E1FULL, 0xB615D1938821C241ULL
        },
        {
            0x8E82985256CBCD8CULL, 0x38148191CF5F32E7ULL, 0x28A0912CB20874FEULL, 0x9E31A48E230798B5ULL, 
            0x7C38D9E8F5EE16A6ULL, 0x385CD91FC63CF564ULL, 0x6BF043CE36718265ULL, 0x48C10FC49BD7E310ULL, 
            0xA377EEE5247C2B2EULL, 0x99018B3EEFF3A385ULL, 0x80A8891FA244A92CULL, 0x2B6CA3B951308796ULL, 
            0x02E38899EA49F406ULL, 0x18DE688AE147796AULL, 0x22F6BC9B319042F2ULL, 0xF871B6D8D5A1D924ULL, 
            0xB36C8CE632CB99D6ULL, 0xEC2267AD71723ECAULL, 0xA18FBD2FF6C4F62FULL, 0x54E8DBF758301583ULL, 
            0x2668CB5E4766B080ULL, 0x6E6EB744F85BC57AULL, 0xD6A87D44525FDD76ULL, 0x495D0A7697D958D0ULL, 
            0x3E95F527E8D86853ULL, 0xBF5ECAB2C31361DDULL, 0x66E06ACE9DBCB4DFULL, 0xB3E0A63FCBBFA951ULL, 
            0xFDCFF3218F9CA399ULL, 0xB1D5DDD4B941744FULL, 0xC73A770AD75BD252ULL, 0x7CEA751587EC0FD8ULL
        },
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
            0xE27D5AB583B0D089ULL, 0xAE628E60EF71D7A4ULL, 0xDD292DD50EAE1AEFULL, 0x2313C8ECD73F8C71ULL, 
            0x38FAFC15A3566BC3ULL, 0x846FA856EC2462D2ULL, 0x4FC5B039440FF635ULL, 0x8154F9DF4798F49AULL, 
            0xE920CCBE55DB7C7EULL, 0x5EA0E829C3F5C819ULL, 0x2000B2114C7A98E4ULL, 0x12ACFED4F775733AULL, 
            0x8B5FAB058C1E5374ULL, 0xDD1C54416B2D6688ULL, 0x7E63F33E158282BFULL, 0xB798B299D887800EULL, 
            0x95A401CEFFB0A1CEULL, 0x557410728FADBD2AULL, 0xB44EA1FB55922CF0ULL, 0xEAA655ADA331D858ULL, 
            0x21D2FA1F6FA24E7AULL, 0x08D3322F96B8A399ULL, 0x103B8C76327A1777ULL, 0x85B1C8E7F96C5D3AULL, 
            0xEBDAE7374631D564ULL, 0x9AA1BC86FC6D1743ULL, 0x72F2C6F63F4E8514ULL, 0x0817272D53334D21ULL, 
            0x740482F03E9B4D7BULL, 0x2E394140C2F8620CULL, 0x858A82B04B6C6D11ULL, 0x549DF7C3EAF94E2CULL
        },
        {
            0xE88BE66BB21CD747ULL, 0x460BAEAC523A0583ULL, 0x08237F9FB803F86EULL, 0xE4E99F8109412C27ULL, 
            0x4BE938885E67F8BBULL, 0x5657F16F5AE89695ULL, 0x4C67BC8498F0E5ECULL, 0x12D85E2C745D670CULL, 
            0xDEAFA05E0A6DF705ULL, 0x739D84FDD41B82DCULL, 0x6597DB08C8FD3306ULL, 0x242AC1E287F7B5B5ULL, 
            0x8C73792A6E0302C8ULL, 0x5BBD0DCB222FA6B2ULL, 0xDFF8D8C580836F65ULL, 0xCCC4EA484DEC2B34ULL, 
            0xC3DD35EE2B043945ULL, 0xC7A6F83DDCED1D94ULL, 0x5F6A29B3D3319371ULL, 0x3B2BD4990714356AULL, 
            0xCA4299A4417E8F9DULL, 0x6ABFA28F23938794ULL, 0x331854E1CC65DD5FULL, 0xC088CD773FF374D3ULL, 
            0xDEEA4F2B15BCE004ULL, 0x1CD49F6A1CD755B4ULL, 0x8EB216B7B40CCAA5ULL, 0x0679BD85C37EE77FULL, 
            0x3CA9BE1C80A73851ULL, 0x39E92FBFB53852D8ULL, 0xDB77F1703F5D04E8ULL, 0x0A057D00BE530D94ULL
        },
        {
            0xD3459532104535FEULL, 0x647303569033EA07ULL, 0x18AA7061FD1DE56DULL, 0xF0EC2C83D025719AULL, 
            0x46C93C05B5EADF6BULL, 0xB81699F9049F8A60ULL, 0x236FF47090A473CCULL, 0xF1DE46CBF4B1852FULL, 
            0x142430216CCA2747ULL, 0xEBBDAC9698E8DA56ULL, 0xE5D8C32F13464B12ULL, 0x9E6D1801AA066F1FULL, 
            0x51D9DFA1D64EE065ULL, 0xC8680117A9510979ULL, 0xC28ECC7267AF67AFULL, 0xFDF025424F7277E0ULL, 
            0x724F50DB9E45B7F5ULL, 0xA9E4BE1813D9D112ULL, 0x92FE7649E4F458C9ULL, 0x90E4F4059236E8FEULL, 
            0x4BD5EB3146C9C8E4ULL, 0x170E439DFAFB3D65ULL, 0x91D7559C03AFEDF8ULL, 0xC5E9E7A0C13B6F5CULL, 
            0x5CAE78FC4B921118ULL, 0x1A6316C3E45471F2ULL, 0xF8DCD9DC25A31BEDULL, 0xAAE1F6582C9B337BULL, 
            0x7969B513B738568CULL, 0x848408C9E0104F3CULL, 0x0B7E8F32F2243545ULL, 0xC18572C254CE7204ULL
        }
    },
    {
        {
            0x7629B2B08AED9ACDULL, 0x77A323892D085E38ULL, 0xFCFF96F31CE0E6AFULL, 0x3BEE5D99529C840EULL, 
            0xD2FC34C17AAD0642ULL, 0xDA3B2C9489C2CD80ULL, 0x045910FE30CA462EULL, 0xB659E20CC4132927ULL, 
            0x26829DD67496F830ULL, 0xBF74EAF38FADAB98ULL, 0x76BCC55B0E4945FDULL, 0x63E9F3C94A40F2F8ULL, 
            0xECE1D3E022673A99ULL, 0xCE85E625A6239FA9ULL, 0x313CE5AE3929738AULL, 0x1DB02F88DC0CA38CULL, 
            0x37D3C4768C2A3A0FULL, 0xFF50513D315CF9F1ULL, 0xF791F2F5AD718E74ULL, 0x3F1689641EEAD38EULL, 
            0x68A952093C95A05FULL, 0x38C2A6D81886EA1FULL, 0x1C6A5C2E66D35B36ULL, 0x76801E664178D2AFULL, 
            0x3D85B4623E39C672ULL, 0x77D2C0567F226FB7ULL, 0x906C8C9CFA145569ULL, 0xAE29DD7C1A9B8708ULL, 
            0x9912AA7BD2990B87ULL, 0x220A4F608CB286ADULL, 0x6732E2420DF9A607ULL, 0x98BEC3BDE5337E0FULL
        },
        {
            0x6FF9D0CF897818BFULL, 0x7B4CE26F60CA97EBULL, 0xD8D0058123750CC0ULL, 0x8FBE00B211760CD4ULL, 
            0x93A324B898400524ULL, 0xF9ABC405BE7426B5ULL, 0x45B0D28138D8B7FAULL, 0xEDC82D756CA09E82ULL, 
            0x0CF7CBB36996C7B4ULL, 0xCE789B46B83BFCC6ULL, 0xD3DFD76BBC895281ULL, 0x743C87FBEE87CB89ULL, 
            0x582DCBC98E63A040ULL, 0x8954090702EF2272ULL, 0x73F706EB01DF3D31ULL, 0xE1D1637F7B63D520ULL, 
            0x512BC83CF33E14CCULL, 0x91FE5214464FE2FAULL, 0x4F705FB3CB27618EULL, 0x772A0DC5652AC8DEULL, 
            0x83706289CFBF6D55ULL, 0x5DEACE139CA2009FULL, 0x55AD6E5452A339DAULL, 0x8AC174C89504B213ULL, 
            0xF33A12A9655545AEULL, 0xBC3725EAE81E9F14ULL, 0xCE57DD0C1D2917B8ULL, 0xDF8143E9DB1FF4D9ULL, 
            0xB0D947BDAB3E8F98ULL, 0x371A90886E2CFD96ULL, 0x7077E3A9576654FEULL, 0x62F3B4C23CEC59E1ULL
        },
        {
            0x25A9540D8D76B874ULL, 0x4630254FE6A9B2C3ULL, 0x8EBC05FAC29A3B24ULL, 0x7F787D0356154640ULL, 
            0xB5EEBE801E2C3C9DULL, 0x9E81DE901544B4B1ULL, 0xFCEBF97C5E538806ULL, 0xF0C2FCEE4F1F72DDULL, 
            0x41C6E26FB7790A49ULL, 0x9667156839DA580FULL, 0x0B3A50418D87A864ULL, 0x7B2612E13F6F6646ULL, 
            0x99E0C811C69C4109ULL, 0xA79044D0FB4F1F9FULL, 0x07B61D15D5AD8B33ULL, 0x13CEA4E719817601ULL, 
            0x8D5D4F43497B4022ULL, 0x476AAC00C6B2CE09ULL, 0x9EC23159AA22D6A7ULL, 0xCAF1C8FD2DAF0CF7ULL, 
            0xAE4FBB96F918B14CULL, 0x3D7E773C77CC3AA4ULL, 0x51394E27FD2C4C2CULL, 0xE71083733723121AULL, 
            0xD71A61A741FC6E7DULL, 0x2923B1B0673E7D5BULL, 0x0486E50E336A9ADBULL, 0x832ED193C362B12DULL, 
            0x6AB3E767029DE47CULL, 0x757F8D2796EEC982ULL, 0x93BAFBFD03CBE72FULL, 0x0B167ACE0FC3B7BFULL
        },
        {
            0xFC87008C9A12F3F5ULL, 0x58ACE0A21DA40B18ULL, 0x5C1ACD4F46CA811AULL, 0x1286FE159E4CC581ULL, 
            0x26C91FC9B5D58146ULL, 0x2475C2E83F7C4B8FULL, 0xDAD00209E09EF9E7ULL, 0xA22B1A0C8187A9B7ULL, 
            0xC33D9115AE964C27ULL, 0xC0A9A555DED98635ULL, 0x166674B8E9975104ULL, 0xD76A9441B9FA807FULL, 
            0x70350631B6E0C6BBULL, 0x68024E29CBABFD75ULL, 0xEE73822EEE14FAA3ULL, 0xB5E12335FBE2EC18ULL, 
            0x5F9EB5F317DCCF39ULL, 0x4C1C63B021278353ULL, 0x17569602B512CDC2ULL, 0x2401664A02863158ULL, 
            0x50D72B88AA85DC65ULL, 0x3B145CE6DB35E01EULL, 0xB9C7F1643EF620D4ULL, 0xCAC0B566F622354FULL, 
            0x3879BB1A00E2E837ULL, 0xC25B8BB0C8C7F21FULL, 0x4BA48659786E0DA2ULL, 0xD710277F5256D237ULL, 
            0x7C71E0FA666DA99EULL, 0xE1693189165236AAULL, 0x3D53778B6302C6FCULL, 0x1550A788683328FFULL
        },
        {
            0xA523D0B00DBFD44BULL, 0x8B40B2B631F25CE5ULL, 0x942942F8E487E172ULL, 0xAF1F479103EEA764ULL, 
            0xAB72B9B0EE135E84ULL, 0xC7EA1C0C2356024FULL, 0x0415A3AEFA83A7F7ULL, 0xF7E45BBB864E2AF0ULL, 
            0x6798F2B972CDE4EFULL, 0x57116751351B6C1BULL, 0xF42188BC00C35F35ULL, 0xCB9F054BB97D404AULL, 
            0x3E6CE476FB25E68CULL, 0xC0DE24A3F91DF811ULL, 0xF46DE82B2AED7E62ULL, 0xCB8E7C426A126C3AULL, 
            0xE8ADDA8A86BCCAF4ULL, 0x08A730769F1402FFULL, 0x0B1A94BF32517640ULL, 0x88C6F2E0006D0A26ULL, 
            0x8C3207D998D7FB2CULL, 0xBCA7F925B3074CA4ULL, 0xB4997413E755527FULL, 0xB47D5C33EF0795FEULL, 
            0xBAA27EBDA0CD0298ULL, 0xEF808565DF795344ULL, 0xC05282A7AAE6FED2ULL, 0xA7C49677A00172BAULL, 
            0x60E2F9B7FEEDF93FULL, 0x15BB68106BED2A4DULL, 0x03771DD4BBF7CE0FULL, 0x7C99FE866B2CB062ULL
        },
        {
            0xB7621E8A6CF3DB09ULL, 0xAF253B4C20321C73ULL, 0x3EB957EF0857395EULL, 0x6F5B11559C3D8288ULL, 
            0xA82F66E42938AF9CULL, 0x493EF60C4AB647ADULL, 0x3E99D29F638196A8ULL, 0xFADEE33D80A1D0FCULL, 
            0x050837A43D955727ULL, 0x9094D24DB28735A9ULL, 0xBB72B87E1014579EULL, 0x919833A359A6F4E1ULL, 
            0x2F5DC3794EB5910EULL, 0x3053C537C7ECD959ULL, 0x1EC794B34B2E1320ULL, 0x2550F0AA7E8F3E7CULL, 
            0x4AADECFF7728D361ULL, 0x2DF0DB8F5DF8A435ULL, 0xDCCE70EB0ACA5727ULL, 0x6B82575CCCE02C60ULL, 
            0x969B03726769BFA7ULL, 0x85DEF2570B672519ULL, 0xA41DA3DA40D93B11ULL, 0xB97716882BE483C0ULL, 
            0xDA0C20E20FE15556ULL, 0x47C98CAFE050A598ULL, 0x50F02AAFE9974FB9ULL, 0xDC548E940EE1AB28ULL, 
            0x24DE54E0B4324137ULL, 0x73F3727A22DC34A6ULL, 0x18E7DE07C1A7DDD1ULL, 0x3B5F53B3A9F412B8ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseEConstants = {
    0xFAC7780E8C5BAE82ULL,
    0x361D9DB14210C355ULL,
    0x615B92EDC8F42555ULL,
    0xFAC7780E8C5BAE82ULL,
    0x361D9DB14210C355ULL,
    0x615B92EDC8F42555ULL,
    0x2C7A3E20062D514FULL,
    0x582B90555AFF1EA8ULL,
    0xE0,
    0x17,
    0xC8,
    0xBE,
    0x80,
    0x8A,
    0x74,
    0xC4
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseFSalts = {
    {
        {
            0x83B292BD0E93519BULL, 0x7CBDAB51D83489C3ULL, 0x3194080E1C4C6C1BULL, 0x2EBC5721797B7F77ULL, 
            0x3386B20A5F8A552DULL, 0x74A085868B3B8F7AULL, 0xB92E0A047BD4C373ULL, 0xAF01DDAB2C0D92C2ULL, 
            0x97D8303A429D4877ULL, 0x649880030B012C4AULL, 0xFF645B9D307D4A8EULL, 0xD9E3D1FCAE8C9C9BULL, 
            0x2C58B8B08059F1A6ULL, 0x5128D084FCC01E25ULL, 0x0999AE37FEAB72F0ULL, 0xDB6284241F803038ULL, 
            0x5BBE5222E876518FULL, 0x09D26928B0F20505ULL, 0x4141395798F7BC84ULL, 0x34C5E07C7E995498ULL, 
            0xB2C119EFAF26534FULL, 0x23CCD74A88EF052CULL, 0x695611FC9E562873ULL, 0x2747D8E530585CA2ULL, 
            0xB7DD7F9F5C9DFE1BULL, 0x99565A1318F4816AULL, 0x0C92A55C8711933FULL, 0xE647CFC04FEBF812ULL, 
            0x15E7DCDA00EEB779ULL, 0x51A6F2A31AF9C058ULL, 0xC949400E8F89D737ULL, 0x959317D077EF2BDFULL
        },
        {
            0x1FCB085C3F2F3C3FULL, 0x2334F128B6CD010BULL, 0x0041CE18C2D56AFBULL, 0xBF32BE5CD80FDFEDULL, 
            0xBBB11C094E968E55ULL, 0x5509870C8714CDFDULL, 0x57D2B206937C204BULL, 0xDD59EF59041D4F65ULL, 
            0xDBD836DFC94864FDULL, 0x8CED7F7AF740C491ULL, 0xE2DD8D345757D29DULL, 0x9678B9BCE3820DE4ULL, 
            0xDE743B670BD51DC2ULL, 0x937ADE6BD49EADC8ULL, 0xDEF7457AC7F1875BULL, 0x21ACB1936934D57BULL, 
            0xED8FA90A4D5ED4DEULL, 0x8A5856CE8CB5F608ULL, 0xBA736E20825C096DULL, 0x8F7F57C6F2D83C78ULL, 
            0xDB49E7841AD4EB25ULL, 0xDC7D3FB755F0FFFCULL, 0x52AE7579E01B6801ULL, 0xF82FFFCE74253739ULL, 
            0x080C558216039A6FULL, 0xEB47809C74371BC9ULL, 0xC3237C78F3F8C449ULL, 0x743FA8D1EB647305ULL, 
            0x36F1B3CBC17C7D4AULL, 0xFDD1E1F15AFD1067ULL, 0xBAED836744A7634AULL, 0x532B78002CA0A343ULL
        },
        {
            0x274276C381AB1689ULL, 0x7D985CAAB5643D64ULL, 0x4DCEB4B86835D5E3ULL, 0x6F154A513508473AULL, 
            0x0BE6E66A281D6197ULL, 0xBC49C2F1E0CA41BAULL, 0x4AC0A8956C03C7CAULL, 0xF3E0A49F9641CB26ULL, 
            0x3B240BBA3F439CF2ULL, 0x111C4305B17BBF32ULL, 0xA9A6D774A9A4844BULL, 0xFEF8D16D699183C5ULL, 
            0x8AF74842ACEEC3FAULL, 0xD6E29FD006473EEAULL, 0x50991A1FB561519DULL, 0x880F83691ECA77F0ULL, 
            0xB49310A17A33BCAAULL, 0x9BFE987AE93465D4ULL, 0x237BA7D7DE54DF15ULL, 0x54B5C7BE7FF57B22ULL, 
            0xC1A0A36A2038641AULL, 0xCC821652E3AA8646ULL, 0xF581AFD68027DBFDULL, 0x9DED1601842FD7A0ULL, 
            0x0064A6772A51AFBAULL, 0xCAC436BEC5A9E89FULL, 0x175AC648A09F2F29ULL, 0x4A5C8303E7D05A46ULL, 
            0x58DAF879336FE80FULL, 0xC4CEB55CE5CB6A44ULL, 0xA5B59094CC92718DULL, 0x6D573BC8A7FED2D4ULL
        },
        {
            0x3EE2B080CCCE3C82ULL, 0x68690EB36D47BF1AULL, 0xA9CDC44A6F2F18CEULL, 0xAFAF695F8CD579E8ULL, 
            0x921F398601EAC4C1ULL, 0x4C083D336FDB4C2FULL, 0xFC9709C1D16F4B84ULL, 0x4BED252A85B1977EULL, 
            0xD824AF8E392CF751ULL, 0xE1EF2121ED24744FULL, 0x679BC849883A5EDAULL, 0x7C9E7093BEB1A81EULL, 
            0x38E6184A8FC59BE0ULL, 0x0CFD9811CE28768EULL, 0xF5AD28589F24E943ULL, 0x9C3549B0E17E2E4DULL, 
            0x1954648F697A7DD8ULL, 0x70D2E7CBC8A889ADULL, 0xA2AB868EED6FF984ULL, 0x83AAC61AC72CC775ULL, 
            0x940CC11FAA8A8788ULL, 0x2636A14A9B70FA16ULL, 0x0306E8FBED21948BULL, 0x5ACD119288872B1CULL, 
            0x232E80923DE855FDULL, 0xE7A197B826B76300ULL, 0x88309CFE651EA0BDULL, 0x988AA8876220BE8EULL, 
            0x77EDB7C5776556E0ULL, 0x258E7D1ADEED8DE9ULL, 0x4076F96832F2D894ULL, 0x345FDF2BF3DED744ULL
        },
        {
            0x235A0A990C49C254ULL, 0xD9EE42236AA9A80CULL, 0xA4A8CF52E2B55765ULL, 0xF5E2F751B0293A88ULL, 
            0xCDC7075594A4F998ULL, 0xF420510A2165ABC8ULL, 0xDE4D4F957C9F3C2DULL, 0x72709908AB2D1646ULL, 
            0xA5BB0EFB39FF6E81ULL, 0x6F602D1AC9D621EAULL, 0xD2D07782743E0FE5ULL, 0xDEDDD5BF6DBD1BD7ULL, 
            0x83D893083006431CULL, 0x53B44BF3DE5B7CF2ULL, 0xC343D0378BF25B2CULL, 0x87DB78D9D26807DFULL, 
            0xD262FDD6DFD47576ULL, 0xF6735BB78E95861FULL, 0x078CA529945A09A9ULL, 0x7E31DDE135977149ULL, 
            0xA13147B83781FDD1ULL, 0xDE1235B26D8484B8ULL, 0x6E0B836578F7B55DULL, 0x5EDB60C364080246ULL, 
            0xEF6152C2CDB76C1BULL, 0x3DD00393605F15CFULL, 0x4AE6782BDBA1BD9EULL, 0xF8612D149657A918ULL, 
            0xF84DD15460AD2CD8ULL, 0xE10EBB87D2F1954BULL, 0x580A8C19B3B1D55BULL, 0x4453169029BDACB2ULL
        },
        {
            0x15349D1A03A364B5ULL, 0x2EE4AD5A45D614CDULL, 0xD9DB495501DCEC34ULL, 0x2F51C93F64325336ULL, 
            0x7EF2B668C31B8BBCULL, 0x09A97DB569770769ULL, 0x36EB39AF740D6F20ULL, 0x010C7A008DC099C8ULL, 
            0xFBE5A1177FE18F96ULL, 0x3902433FDF0C467BULL, 0xA0F358E5ACBC9025ULL, 0xE1C2C8B6D7D122A4ULL, 
            0xCB60550B18095D13ULL, 0xD93723100FD1CDF6ULL, 0xA1B148E4C3CF8F19ULL, 0x65B7B0625AC04AF3ULL, 
            0x1976055FCD2E1327ULL, 0x3F544BE62DC5CD04ULL, 0x4A0ADF04628D73A2ULL, 0x951BEDFB32AC2765ULL, 
            0x50F7C54FBEC832ACULL, 0x5AC133EB63A6CA09ULL, 0x9ADE92DB42A14F4DULL, 0xF431BCF6B14573A7ULL, 
            0x58170BC76CC1FC10ULL, 0xC88C9A27E0451ADFULL, 0xACA278C2CD664169ULL, 0xB87C8D280AD1E3A3ULL, 
            0x8847B2087419B6FAULL, 0x431C4138F34A2DFAULL, 0x11D018FE49DA1B9CULL, 0x4A79B29E2324EF00ULL
        }
    },
    {
        {
            0x2C47BD237239903BULL, 0x2FE5A24F2AD89023ULL, 0x47C9A6B9E0F1B0F0ULL, 0x495E4C41F4CD7E79ULL, 
            0x901383F8FE9F6A30ULL, 0x586B5F4AC2367406ULL, 0xD496CF11A8A675F1ULL, 0xB8FDF4E6A74CEDF2ULL, 
            0x0795DA92C9393835ULL, 0xEE95950DCC738D2AULL, 0xC950D8B583E188E6ULL, 0xED250635FC6CAC8EULL, 
            0x3AFDAD665F653E96ULL, 0x1B67611EC10196D3ULL, 0x71C3A8FC47A81207ULL, 0x75F33E3C7D39CDAAULL, 
            0xE0D3D1C9B81C631FULL, 0x866A2F1AA52D0329ULL, 0x6DE82A39D8B489E0ULL, 0xDBE445C9EE68521DULL, 
            0x95D90745F863C6A3ULL, 0xBF3FBD04DB62C0FDULL, 0x512D55CDAB805448ULL, 0x7D39554A594D0043ULL, 
            0xC09E9C198140F999ULL, 0x467456A3C30586D5ULL, 0xF3FB039791731902ULL, 0xD53DB55ED4691EFEULL, 
            0xABF9D802ABE4F76AULL, 0x0256B00F1CA13C46ULL, 0x81734DB23B67150AULL, 0x3C5581919D9F0DE8ULL
        },
        {
            0xD8B1B5EAAF31A8AAULL, 0x892C796CAADE1C1FULL, 0x35CE3CABC1F64EC2ULL, 0xDB83E8D8CB401F2CULL, 
            0xAD5787C9D91AA7F9ULL, 0x955D043BA52180CDULL, 0x42957E30F5D0069CULL, 0x8C304E607282A82DULL, 
            0x2D49A02D4C502ECFULL, 0xCCA511A06A8BCB17ULL, 0xE0D97AC3D2A9CC47ULL, 0xC119C0C046CCCE26ULL, 
            0x7F0DB48904483FB8ULL, 0x5FB6D3EEBCF80CE9ULL, 0x2A2E8FC71D170D5BULL, 0x8FA59D316D251801ULL, 
            0xEDE473088C58795DULL, 0x37511F1E83458CEFULL, 0xB552A2A734F75CA3ULL, 0x89E7BD86F89BEDC0ULL, 
            0x6FCDD036A0524588ULL, 0xF3433B0B89B53746ULL, 0xB548132468E206CDULL, 0x29729F6F15DD815CULL, 
            0xC195370F6A669237ULL, 0x102365746A2F34B1ULL, 0xF0361F7B61DF5A7FULL, 0x5A53527514636919ULL, 
            0x7B0ACB3F7E6423C4ULL, 0xD444A7F75417DA19ULL, 0x763394773E26967FULL, 0x31A65F66E239D201ULL
        },
        {
            0x837020EAFA42DF92ULL, 0x690F84B28E47269DULL, 0xB2AE9C70C0F081F0ULL, 0xD71C09154A0E4039ULL, 
            0x7FB888A7009DCA43ULL, 0x629EA287407C78FCULL, 0x63BBE3116DB5FBC3ULL, 0xB0D10AADC8D7C5E9ULL, 
            0xAD7AAE12424C29F1ULL, 0x2DAC71216E154D4BULL, 0xCD1E1A554C3D0462ULL, 0xA11AF2BA7216B15BULL, 
            0xC99C111E368EDEA0ULL, 0x3C53DE846C19B011ULL, 0xFFC4D7BECF14F225ULL, 0xC90DD03A27A92FB2ULL, 
            0x28B338E217EF915EULL, 0x0BB46359C5E95DE1ULL, 0x702B6AC07CAEACB8ULL, 0xE5CF3B5CBE124FAAULL, 
            0xDDCB27BE7F89B04EULL, 0xFD5D245EB4110675ULL, 0x51826049539F87E4ULL, 0x6707DAB67788D493ULL, 
            0x0D17FAFB78E92EF3ULL, 0xD70041DA006C2EE1ULL, 0xD094531240044090ULL, 0x22B7B88AD0939725ULL, 
            0x5AF7A2B8421194B5ULL, 0x5CA4B4F0E87B613CULL, 0xDCA033B80C7F0AD1ULL, 0xECDB0865EF31DEE1ULL
        },
        {
            0xBE1AD301F041E425ULL, 0xC88B5EBA44C54E1FULL, 0x6B3F072CC550EE75ULL, 0x396305725023441CULL, 
            0xD1ABBEF15E43AD28ULL, 0x0AC8968B46D1A2CAULL, 0x6633DB614A4A100AULL, 0xB8202FC1B26CAD5CULL, 
            0x4436BB7262DE74A6ULL, 0xA4613F6F14E6EA03ULL, 0x56FD80DB3E4BAC96ULL, 0xAF4685D4D45885B4ULL, 
            0x9486BA19282FF024ULL, 0xC5D57EEDA1797858ULL, 0x8992461486A23197ULL, 0x4B7962366E120443ULL, 
            0x861340D4DC4ED17EULL, 0xD7B2434B22D1EF51ULL, 0xD2F4B23756B8915DULL, 0x45A9CBF45796B720ULL, 
            0x1322DA743AB3BA44ULL, 0xE230755A52F9F53BULL, 0x881D61E28B143AEBULL, 0x3ACD1D2B232DC944ULL, 
            0x32C756C15F901281ULL, 0x06165BF92B63978BULL, 0x4DF4091F27DE0DDAULL, 0x20E0F3C56708220BULL, 
            0x630143379B6A7C57ULL, 0x849325831B282D7CULL, 0x504F291AD6B79EBBULL, 0x1428E914C91B4004ULL
        },
        {
            0x59EB000BFD292F9BULL, 0x3CE0DD81D67F4B0AULL, 0xF86D9BFF898C18CEULL, 0xCD778D9FB6396736ULL, 
            0xB475A76569A89D2DULL, 0xC2FAD302D1CEB4D4ULL, 0xF19019251CA1D249ULL, 0xBBB9E04CE077E90DULL, 
            0x7BE1E5EAEAC7D980ULL, 0x1CA6A7625185B0A5ULL, 0xD4F3B25385127323ULL, 0x80D799C35BCE9D1BULL, 
            0x6364F705D535BDECULL, 0xBE666E0238DBC193ULL, 0xE9DED1E41F95CF24ULL, 0xE86A2D8229592AFEULL, 
            0x68CB8E2D04E9C494ULL, 0x62819088D3E2C89CULL, 0xB4D445991ECF2B77ULL, 0x0ADDE43D969855A2ULL, 
            0x9D39565A6E509D3CULL, 0x80D8A6ACDC1277E2ULL, 0xFA27348B65CB8693ULL, 0xDD8D77F7E487ABB8ULL, 
            0xD7D5BA7540C3BA0DULL, 0x2E47EA2C64EA46A2ULL, 0x7F6D9280D19FD349ULL, 0x0D21EBBAD36A82A0ULL, 
            0x5EB9FEE23F912D13ULL, 0x421C3CB02CDC57FAULL, 0x238A749FBC6B5A5EULL, 0xF07CA51351E22B7CULL
        },
        {
            0x2E233EAAA10A0BDDULL, 0xCA04245F07B58965ULL, 0xA2502711EE16F5C0ULL, 0xBFAA6F55FD0A133BULL, 
            0x1431AE01CD3F8BDEULL, 0x1AB2467453D134C6ULL, 0xD4F4B8DECB32645AULL, 0xD7408700D8356E7EULL, 
            0x2BB627F49611D583ULL, 0x738EFD0FA53F7350ULL, 0x1B3685249CBF87CEULL, 0xDA5D8AA9970976B2ULL, 
            0x167BC6C866094E04ULL, 0x17434397DCD80A43ULL, 0x4AC92D1632FB2A3BULL, 0x273EC704D50DC5C8ULL, 
            0x818F7671FB70F739ULL, 0xCAF6BA1F869BD023ULL, 0xD041F62F0092F0C3ULL, 0x912B373B6D7E6494ULL, 
            0xE1D6D5BD3CD1958EULL, 0x2954CCA653D82CD0ULL, 0x938E10975CEDC685ULL, 0xFBE29B2C06B12EC2ULL, 
            0x1DE7423A471E2F77ULL, 0xCCB47C2F2BFAE1C4ULL, 0xB48CF600CAAEDB9EULL, 0xA60C188BD9DA4F45ULL, 
            0x9232A73E65849B82ULL, 0xBF539E8A9088729BULL, 0xA7E8789856A99220ULL, 0x4F463ED5071D924AULL
        }
    },
    {
        {
            0xAFFFD47E04FFD68BULL, 0x0B823DFAC35B3A10ULL, 0x05D1528DC4D5FC4AULL, 0xAF294E32E623FAB8ULL, 
            0xF080A16B06D4E600ULL, 0x335D9D7D3A68004CULL, 0xC49722E98088CDDDULL, 0x02A08887F5A34C56ULL, 
            0x77DF5E1808675609ULL, 0x187728D394B7819BULL, 0x282EA9BE8A6D8C89ULL, 0xC22F897D21A8BC69ULL, 
            0x3D93FB2DD1311116ULL, 0xC7B37D281CFF6C21ULL, 0x12A2422ED48607EEULL, 0xD6EB9869AAF0A065ULL, 
            0xDF0A280834B26954ULL, 0xC645FC77704C220EULL, 0x77E35EF57B618223ULL, 0x630E7E5E4C63C700ULL, 
            0x71494B625D04CEDEULL, 0x6E7D30EF968CCA3FULL, 0x1FF8D26712691520ULL, 0x633BB6C1AE50883CULL, 
            0xD79951912AFB548DULL, 0xDCD3B7E0B13A284FULL, 0x2D5906A4162EF8DAULL, 0x9AC52E58DBDC9F3DULL, 
            0x6576FD2ECFD551D6ULL, 0x234BC2B77D1140D5ULL, 0xE7DA69D3A9AE68BCULL, 0x90978A529E2E3B42ULL
        },
        {
            0x8FE0697B728319E2ULL, 0x8C6CF7BEA140BE8BULL, 0xE80CE3723374FF56ULL, 0x0C2CACDAAB47466EULL, 
            0x18804282C255836AULL, 0x61FF0F6498E9518BULL, 0xCE20FE5E7FB2C1E2ULL, 0x6753DEACC5C83E44ULL, 
            0xEE867E4AD52C501DULL, 0x89C89541BEC37674ULL, 0x32B58F5FF47167A9ULL, 0xC9629422B385430FULL, 
            0x1B5B0E3A41ACB3ECULL, 0x995B2ED4D4C57D0EULL, 0x34C56F50C9F6F4A4ULL, 0x22C0CFCE03620594ULL, 
            0x67ABD5B0420D6035ULL, 0x50AAC1E500395313ULL, 0xE26FD6022D75E7ACULL, 0xF79FED20473214D8ULL, 
            0x2A61D9D766BF852BULL, 0xA1764F07613DA4DEULL, 0x80473FC0C573B876ULL, 0x648E9C6E32C264ABULL, 
            0x3A8E0734BEBC175DULL, 0x3314E0D20C9D06CAULL, 0x2F18DD97A42CD1A3ULL, 0x3C6A5E7891A4D736ULL, 
            0x78EB455D66935D23ULL, 0xFB5674CA07D36578ULL, 0x84884810B408FF56ULL, 0xF070AD78036C6E2CULL
        },
        {
            0x3798A173377BADC7ULL, 0x67677C93A07FB7F7ULL, 0x952AFDFA3FB83E08ULL, 0x5DEC8F2A68A4E9CFULL, 
            0x0B5D95428E2CB63BULL, 0x7CBD4E824B946825ULL, 0x1F647D65AB0B159FULL, 0xB81C2FE725912A22ULL, 
            0x860DF9C6CA36EEA9ULL, 0x19894D492EB7F933ULL, 0x6A0429407D5EA724ULL, 0xF9C3EDA43CFBC33CULL, 
            0xDBF6B2912849AFBFULL, 0xC59C99FF50F593EFULL, 0x0FBEA9559F52E9D2ULL, 0xBA15622F12931E99ULL, 
            0x9FE0497700D04B1DULL, 0x5D1E1B1BB3EC02E6ULL, 0x8FC3561E3894F14CULL, 0x1D6C240DFD273946ULL, 
            0xC56D811906032F5BULL, 0xE310F085F6A2D582ULL, 0xDDAA7041921071BDULL, 0x85AD68AD6535D5B4ULL, 
            0xC9369E8E44563851ULL, 0x502CDB55B59F887DULL, 0x252E283107F80EEAULL, 0x226E603AFFC18655ULL, 
            0xF92257B49CF4F8ABULL, 0x0799098E2BA23388ULL, 0xBD20306624CE5620ULL, 0x3C0DDA4D7F0365AAULL
        },
        {
            0x735AAAFB4E24127CULL, 0xFB75B8812ED96315ULL, 0xF81F4FEBE1C48900ULL, 0x62954FAFE12C2958ULL, 
            0x255BE9E6645AB712ULL, 0x61FCA599745D8B04ULL, 0xEA19016C4D252F1AULL, 0x993B6E8620307C61ULL, 
            0xBACC54378417BCB1ULL, 0xA392045726D8D0A6ULL, 0x18F3A561C6D06B94ULL, 0x53E0D38E8A70EB6FULL, 
            0xBE93F7BD9663EA75ULL, 0x58296219824309F4ULL, 0xA9B7A620CF39643AULL, 0x4D5FB9DD6881344FULL, 
            0xC9D6509EB76C0D4FULL, 0xD472C79FEAB4E050ULL, 0x1606C3ACDB3A95F5ULL, 0x695328CB34B49AF1ULL, 
            0x8C052159D05436CAULL, 0xC711D3D604D35D52ULL, 0xF226AAA008DF01C9ULL, 0x9FBBDC8E29D65EB1ULL, 
            0x2DCD116831F4EE41ULL, 0x70CEBDA0496BBDF5ULL, 0xDDC634FDC1E858EFULL, 0x46E2394F7C70B0E7ULL, 
            0x7A84D7ADDFD1BF84ULL, 0xA5B41A1B43A81D06ULL, 0x47F5EFEDA497C80FULL, 0xA276CB9197ED91A3ULL
        },
        {
            0xC63D6B572D2B0C8DULL, 0x12A92542E7BA0BAAULL, 0x7AA180172726448EULL, 0x40B0F280CD62FFD3ULL, 
            0x425F1132981A78B5ULL, 0x47A0C919EE3D8F2AULL, 0x03DECC0A4BC5E7C7ULL, 0xC2D83BC08EA19D5FULL, 
            0x5E217F2152B2A16EULL, 0x8FA2C277721AB01AULL, 0x346087FCD1C09ADCULL, 0x9B04F370F710C484ULL, 
            0xB11C5AB813C8B057ULL, 0x51E487C653E3CBCFULL, 0x209C67E43C1D81D0ULL, 0x11C6E0A6EE25819BULL, 
            0x1E77B812C52AB96FULL, 0x7A6DC02A5F7BEA49ULL, 0x10E4C4F1C320421BULL, 0xE350223BBC21F997ULL, 
            0x040F5CFB16135AE2ULL, 0x68978436B63EC553ULL, 0x9A7EB66798105DA7ULL, 0x27FA20C905B5C08EULL, 
            0x14E19A5267559E5CULL, 0x5DC8C1FDE79BBB58ULL, 0x03756B9CCB92A238ULL, 0x6FEA7B9531930E9AULL, 
            0x4A6D8DE8D73C909DULL, 0x5395679346C0B934ULL, 0x39AC1004A58CA217ULL, 0x56C2867AE6B5B136ULL
        },
        {
            0x09ED6BCD9F911A3CULL, 0xEE106E201BC8CA9EULL, 0x775F6DA969E7014BULL, 0xAD1CD2AA78278486ULL, 
            0x41978C631D44C03CULL, 0x01FE0FD644817859ULL, 0x05D1F92E98808B8DULL, 0xB27C6C08026EA93EULL, 
            0x20CFD20F01A4613CULL, 0xFAC09F241F2A05B4ULL, 0x17B9FC1D8909C866ULL, 0xD8DD1E6B1642D0BFULL, 
            0xDDBBD16419D529A1ULL, 0x092CB402FAF36DDCULL, 0x8A57A418BA21FAA3ULL, 0x9390AD738E20192EULL, 
            0xD4B2F816F7D5179EULL, 0x9EC20BF82C454A5AULL, 0x1B2EA206BBB98720ULL, 0x1DA9F6E7EE623365ULL, 
            0xCF31380CFDC5BDA8ULL, 0x16A08A357F3DCD26ULL, 0x52C1D6CBE945D580ULL, 0x9E27B810154566D9ULL, 
            0xAB378E1F6BD59860ULL, 0x0B302EB2CA5C41D7ULL, 0xB46C85A34012D132ULL, 0x610B429AE2A6A185ULL, 
            0x12B210190D55C435ULL, 0xE604E4A068C7AE50ULL, 0x41D5AB0F31D2C5D0ULL, 0x862B782BF0A8F04FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseFConstants = {
    0x26F5F9B06F1B77FCULL,
    0x4BB3286D48FFDBBAULL,
    0xEA9407D55CDFA9AFULL,
    0x26F5F9B06F1B77FCULL,
    0x4BB3286D48FFDBBAULL,
    0xEA9407D55CDFA9AFULL,
    0xE81310A4A6CB0176ULL,
    0xFAE7F4BE2DACD80CULL,
    0x27,
    0xA6,
    0xAD,
    0xB6,
    0xD8,
    0xF8,
    0xEC,
    0xC4
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseGSalts = {
    {
        {
            0x027310AF118F381CULL, 0x455B19DD22E1743FULL, 0x9C8E19AE427EBD98ULL, 0x5764C27854BE7716ULL, 
            0xB81A00539C13651FULL, 0x4FB3DF15B3AD6512ULL, 0xCCB1BFEEBF6584E7ULL, 0x54D41D840A604906ULL, 
            0xABB69E8BA2799786ULL, 0xE0C0CD8392B3B5C4ULL, 0xB35A41D1EC0DAFEDULL, 0xDECA04E3E30ED2D5ULL, 
            0xEED8AEBC79313413ULL, 0xACBEFB74E389D55BULL, 0x9837ABF6DB18B1E1ULL, 0xCF4EBF3D2345FBE9ULL, 
            0x1B57BB117B036B17ULL, 0xC673B7657FE4F5B4ULL, 0x6BB64607B5E06AA9ULL, 0x8DEDC83BB6BB9F8EULL, 
            0x27032FEA8FEC281DULL, 0xF2CD7C7DF841A8B8ULL, 0x3C9412F062C620EDULL, 0xF52F03F8D7F94AFBULL, 
            0xD6AFA82E96016A81ULL, 0x8325D621B31F6B16ULL, 0xE95F6702E9DB523DULL, 0x35EDA457D4F954D0ULL, 
            0x6EE892D9564F3AD7ULL, 0xD5F8505E8B0C38F7ULL, 0x5D51258F264ECD0FULL, 0xE3D1C0BFD22FF9B1ULL
        },
        {
            0x153AE46E9FA1B56FULL, 0x351204E7B3EBBDFEULL, 0xE1F11FE24DB5723BULL, 0x8AEBD61153608B42ULL, 
            0x77ABE784A12141D4ULL, 0x089B1CAF0F916378ULL, 0xE73B4032AC0F451DULL, 0xD2DD2188D8BF028DULL, 
            0xC9819B5D980B731DULL, 0xB86BA0270EFB84EFULL, 0xCB98D43B0DAC5D5EULL, 0x6EFDA1D7DD42DB0BULL, 
            0x018C77F9FDA5D4ADULL, 0xD73EC2F58BD31BDFULL, 0x687C643940ACE0A8ULL, 0x15B6B958B80D887EULL, 
            0x90B757B546B14E71ULL, 0x28A84257154898CAULL, 0x5A60E8CA83EDAA1CULL, 0xC53F890EDC6393DFULL, 
            0x8DB9CA833EA523DDULL, 0x29D9213EE4F52A83ULL, 0x89D094C9CBD2C74FULL, 0xD7A2C9306E1E0B89ULL, 
            0x0A130EE1A49EDEADULL, 0xDDAFEDADDF00D4FAULL, 0xFA641427787684EEULL, 0x73F2B1D36500AA11ULL, 
            0xFE98A5102A7D1869ULL, 0xACBA8955474279ABULL, 0xEA8BBEB29CA5F824ULL, 0xFF8A2D95226A9470ULL
        },
        {
            0x5B286068CDCDED6AULL, 0x807C36E0AAC64928ULL, 0x7352A4AA470C9F43ULL, 0x1A487C8E78DC663CULL, 
            0xA740DBCF798D4F61ULL, 0xF8C9C7F6ED64E59AULL, 0x5527A87A01E8A90EULL, 0xE98A751DC771E340ULL, 
            0xC68106E9979DF650ULL, 0x8CC115B928947224ULL, 0x505263D6BEB82635ULL, 0xEA44FF6A40766487ULL, 
            0xD4F4C54B50A1014AULL, 0x6BE73B1953EC87E6ULL, 0x6CD82CC982A34157ULL, 0x6814F01479045BDEULL, 
            0xEF281CB21DC01B6AULL, 0xC3A8D5C41182DD6CULL, 0x1ED77832C97C6D80ULL, 0x0187BA4D13DC0397ULL, 
            0xFC7C7255545274A0ULL, 0x62EE84B2831D679AULL, 0xE1EFD0D6DFDA97D7ULL, 0xCE78770788D35107ULL, 
            0x7CC1B6AD2B5C2FCFULL, 0x33FFD55E6C35EA29ULL, 0xBFDEC3381F2377EEULL, 0xF9B55E9BB7DD7528ULL, 
            0xDF8293E258128086ULL, 0x9E33885DD157CB86ULL, 0xC93E0986C27078A7ULL, 0xF5707D8F77DCB040ULL
        },
        {
            0x486FCBA292451991ULL, 0x8F24A1ADC0F7CCEFULL, 0xFEA66DABC9E84368ULL, 0x9733B3A33EAECADEULL, 
            0x83603B903BC8F50CULL, 0x1A30B4B566F2D644ULL, 0x45949838196C8533ULL, 0xA63119CCC659AD4BULL, 
            0x6B69EA5E0BF79E78ULL, 0xD586F112BBC190F6ULL, 0x9952F7605ABED9D0ULL, 0x859B691109F522E9ULL, 
            0x5AF67D63B9727847ULL, 0x1521D24F275EE5CDULL, 0x139D46AF344C1815ULL, 0xED4AFBFEE4E1AE0FULL, 
            0xDBE70A1A835C039AULL, 0xFAE7828EC4EEA193ULL, 0xFB801955EF87872EULL, 0x5825FFC4F44DAA09ULL, 
            0x153E5DE573C941BFULL, 0xA820E9219DB545B6ULL, 0xB7DC3B275E996535ULL, 0x7F6D5C5C3B4EB805ULL, 
            0x02587F0AE8D19AB4ULL, 0x1A9E689786C5560BULL, 0x777F2D227E1E06DAULL, 0xB89455B1BC9A5E18ULL, 
            0x665E1E456B9EDE22ULL, 0xE066A9B7C7BE9BC5ULL, 0xBA6A031A74156CF6ULL, 0xDB395ADCB8E7AC3AULL
        },
        {
            0x11F39C3D00AFF084ULL, 0xFED5205F8C3D3A0BULL, 0xB59086892B6E29CAULL, 0x0A800E268C4E049BULL, 
            0xB9A4952952E5BB42ULL, 0x226E0BF85107472DULL, 0x6F585EB4E6F00F72ULL, 0x6CE25797F7A42675ULL, 
            0x234BABD0D606079AULL, 0x48D7264928FA3379ULL, 0x9DB1412F7373832FULL, 0xBAFFEE1135221F71ULL, 
            0x1E206B6CB855ACB6ULL, 0x07FE88511CD3861FULL, 0x63ED8C303193EF91ULL, 0x2985E529E1CCCC5AULL, 
            0x98423DCC95F2BE13ULL, 0x474D9C69D0BB64E9ULL, 0x894123A5551E4C80ULL, 0xC614E10BABB72874ULL, 
            0xFBF4EB4350BF66EDULL, 0xE5857E548B5185DCULL, 0x8BBBF07E4AA5424DULL, 0x010D50F01DEBF5B7ULL, 
            0x88E0799C0D9A254EULL, 0x7CA01E9636B2FB50ULL, 0xAA0988FE6897A446ULL, 0x2E256E303B8E3EF0ULL, 
            0x83CC59B21768EB86ULL, 0x1225606DCC292C53ULL, 0x242DB11E5245CE6EULL, 0xE174BED37285A6A3ULL
        },
        {
            0xEEC1CD28878B68D7ULL, 0x12FF1C6343DB979CULL, 0xF8AB582C42B5A0B2ULL, 0xD1CB84E67FC567C3ULL, 
            0x8BA4F3D56EFC0F7EULL, 0xA9D05E0C5B3ABD69ULL, 0x7BA2AF143B2591C2ULL, 0x9AFC1738AF787AE5ULL, 
            0x0D5F1113394989E6ULL, 0x850ED84D70F87F3EULL, 0xE4917094ED0A976DULL, 0x001F640F138D15E8ULL, 
            0x803170A7455CC5B5ULL, 0x5A7C0DEB46872929ULL, 0x5CD82F8B6E4F9500ULL, 0x9FB129C3731C15C2ULL, 
            0x27369BB05A49B637ULL, 0x1FFB98B9A567C6C6ULL, 0x578B25D5718CC00FULL, 0x61E531D37AD26F93ULL, 
            0x78BBDB2684C13EE8ULL, 0x701F0C959E37B5CBULL, 0x45738A8068984018ULL, 0xCB6B8A7D26436BDAULL, 
            0x19C8D43A7ABCCC85ULL, 0xEEF2396FBEF022C0ULL, 0xECE46D819CC2C8AFULL, 0xE10971C55C0A0B2FULL, 
            0xBE9DA6CA8C6DEF85ULL, 0x0E8FD08E2E622095ULL, 0x3B90E58310070B62ULL, 0x6E22583A69B6B88AULL
        }
    },
    {
        {
            0x6BDF8963F1CF1ADFULL, 0x4F7FF3FBE8AABF71ULL, 0xC613B23FAFF294B2ULL, 0xE8DCC11D70504606ULL, 
            0x935FBF02986AD327ULL, 0x918BC2FA3151F4B2ULL, 0xA8A2DAD4E36C20BBULL, 0xE07B60E5B95733C0ULL, 
            0xD42EB8BB6F6A4750ULL, 0xBE9BC707B67B17E8ULL, 0x7988D7202113A0EAULL, 0x4FAE98B35BCD4C34ULL, 
            0xBBEB317388AE6B73ULL, 0x63060538482D34B8ULL, 0x4E6DEC8BC5BA7CB4ULL, 0xF04EB43382EDE537ULL, 
            0xC70693A61A23CD9CULL, 0x68A1D49B31F8DA4EULL, 0xF6DB6EA7EE5F3898ULL, 0xB0A6FABB01C771B8ULL, 
            0xC6262BB594E3430BULL, 0x5FF4F43AAEA6E95BULL, 0xC007832E21A616EEULL, 0xE2E849DB3A249AAFULL, 
            0x70F5879F5CFAE7FAULL, 0x484208B55209157DULL, 0x44872687DF1D1314ULL, 0x02C698397561AE63ULL, 
            0xB679548A44E4CFBCULL, 0x40FC5573E1AD4747ULL, 0x610DDB1DC5D2563BULL, 0x238D611BC8D3E98FULL
        },
        {
            0x30BC7BFD16ABB1F6ULL, 0x4953497397DA5B6EULL, 0x9B1739390ED25890ULL, 0xA332B8D352B265EAULL, 
            0x3BF247B3164FC5EFULL, 0xC41B9687E16798D1ULL, 0xF8B56620F67D49C4ULL, 0x163360934A07EF22ULL, 
            0x065BE41F296D6E48ULL, 0x7B3C26552A2713DDULL, 0x315002DBFE8B119AULL, 0xB4EFD29951D4F772ULL, 
            0x15FD0CAD03959907ULL, 0x852B3B57BEBBEADEULL, 0x327840AF890543B3ULL, 0xC0A2DA84939BB66DULL, 
            0xBC9A62436F6E930FULL, 0x2CE420B5E2F81C75ULL, 0xCAEC19BF0D3E1A1CULL, 0x6A17A0DC0AA137DBULL, 
            0x0CFBEC5A452EFC35ULL, 0x2603D093FC24F443ULL, 0x9B3002B8E99AFA95ULL, 0x51010ABDF6436A7FULL, 
            0xEE6BEA5D3D4EF2E2ULL, 0x38CBEAB13BEF0992ULL, 0xFCFD5887EDD1DC90ULL, 0x4147CF4AF80AAAF8ULL, 
            0x912AAE7128108824ULL, 0x08415A08A625EDFFULL, 0x025942384F39AE54ULL, 0x43FC23DA89AFAC52ULL
        },
        {
            0xD203248EC9B0EF4EULL, 0x00A0439EE60C9547ULL, 0x7ED95314AF1EC998ULL, 0x1723B09829D8EDD1ULL, 
            0xE1764623DEF90C4FULL, 0x58A6B840141ACEF6ULL, 0x6CA78438E1017CD1ULL, 0x37F34534A3D65F70ULL, 
            0x66DC5957EF4108D0ULL, 0xAAFAB2CAE7670310ULL, 0x8B538176C597DAE4ULL, 0x5A45BF30D6F3D720ULL, 
            0xFC645CAF0B50035BULL, 0xAF94D785449E9ADDULL, 0xD2B446D0A4C1E16EULL, 0xD163FC52D91B71FDULL, 
            0x91C3AB94C2B4C2ABULL, 0x6E880C4EA74B9597ULL, 0x9921E0C300F6FC6CULL, 0xE779B712B763DC1CULL, 
            0xFDD04B5B726427EBULL, 0x804B475FD0390E0FULL, 0xAD9572B84731734AULL, 0x4B54C2784B5A4682ULL, 
            0x5DFF2960EEE05965ULL, 0xF3A6A6EC2AA0FD01ULL, 0x8B9D882E6E8C2FD8ULL, 0x4C09D3CBD19A9640ULL, 
            0xDEDFC5A8A4E1C649ULL, 0xDAB2D1BF17886115ULL, 0x51A722147B3D5CF3ULL, 0x65AE2BE12802972FULL
        },
        {
            0xF0DFDD44BFD1E843ULL, 0x2F20C2E854D13CB8ULL, 0xF3D97C01BA9852FAULL, 0xC31814BF9890B9A8ULL, 
            0xC490444FB785E4FAULL, 0x52B50BD26B2BAF9CULL, 0x290B4729CB3EA9CFULL, 0xE6FA4380E5B26DE7ULL, 
            0x1D12D684E33163BDULL, 0x609250E4EA044E38ULL, 0xC651EFAAA7DFA000ULL, 0x6B7620FA317A58DAULL, 
            0x6A87E25E8349E03BULL, 0x941836EF035B10BDULL, 0x9D2570289EC4D441ULL, 0xAC7D20081CEB82CAULL, 
            0x41B95C00274E6E5AULL, 0xAA0716BEA002B5A8ULL, 0x7430CCBA85C20B9AULL, 0xAF8D72DD296FA14BULL, 
            0x23FEAD34C6007EA6ULL, 0x01269D94484A6F05ULL, 0x8A01B431104E153DULL, 0x41AEFE4DD3CCAAA8ULL, 
            0x01FC338FFC27CDAEULL, 0x6F31775465C18A99ULL, 0x170F61DFF1946FCEULL, 0x339510847F2BC579ULL, 
            0x406C9DFB71672956ULL, 0xE8CBAD628D4C3188ULL, 0x7DF75BDA52395699ULL, 0xA4E7DDB5EE091936ULL
        },
        {
            0x90525BEDC8D30FF2ULL, 0x0C21BEAEA7215745ULL, 0xDAFDA47C7DBFEFBAULL, 0x447E73452295E74DULL, 
            0x6082D6BE19ED9864ULL, 0x0AABC9F89EF3474CULL, 0x7EBEE1CA53263629ULL, 0x7AD0C0C8FB5CA3DEULL, 
            0x00E83CBC6DCB95EBULL, 0xBC5238D60409549DULL, 0x5A0ADF9325453DA0ULL, 0xA584A729047C8621ULL, 
            0xA0F0D4756928BC8AULL, 0xCACC1EB27B02B3C7ULL, 0x452CEFD9DBF068D3ULL, 0x18EC51206162E811ULL, 
            0xD852FFEDF804FA99ULL, 0x17E607E3BD49AB36ULL, 0xFD8BE599C5E2AC54ULL, 0x42257EE74DEF8CF4ULL, 
            0xA4B7DB975A5C3AEFULL, 0xA6F985D88BF74479ULL, 0xFF091D9D2158CA71ULL, 0x69294CB708A6AF55ULL, 
            0xB38556474D3380A3ULL, 0x0717E818114A5D17ULL, 0xC137DE4E6B384F9CULL, 0xF7C28FF22A78A43FULL, 
            0x3B7BA7BD29259630ULL, 0xB2B44CF2C3163DA0ULL, 0xABBBBFF8B6195820ULL, 0x70262FC7E6D918DCULL
        },
        {
            0xA007F7CCB4A93C6DULL, 0xEC368EF48ADFC691ULL, 0x70019BB4B1C0B1C5ULL, 0x40A0E215A3FE61BFULL, 
            0x83BEB02AB9D0A719ULL, 0x24C8AB14793AF1CEULL, 0xEFBE29388583044CULL, 0xFAE096C119920D87ULL, 
            0xF3B7C01476BD71D6ULL, 0xF30E84FE1DB60DA0ULL, 0xF4D5E738EB6AB99EULL, 0x28BDB65AD0840410ULL, 
            0x0FB5E9E7B85B1991ULL, 0xCEDEC43B64F319A8ULL, 0x8203E2AB0195F8B7ULL, 0x33B5510A80F1D700ULL, 
            0x8E7A3C0803E8E09DULL, 0x8044A14C5E595B93ULL, 0x1F29DEA78EF72144ULL, 0x13F0AC5F8DC5D151ULL, 
            0xE770F92E974FD78FULL, 0x7B0C6BD3E9325D69ULL, 0xB0CB0F873A29CEA3ULL, 0xF882ABE644CF65C5ULL, 
            0xAE64DBB4A25F0D1FULL, 0xA38A0674536DD46FULL, 0x8E056F958542DCDAULL, 0xF91D7B800853E002ULL, 
            0x21106404CD247398ULL, 0xC8B5B61ACAEAD53DULL, 0x15DB9DE350CA356EULL, 0xDBA3B370050977CCULL
        }
    },
    {
        {
            0xF31E65A3778BD900ULL, 0xA64D28B5822C87BFULL, 0x5E1DABA85412820AULL, 0x83EA42086B9CE2DCULL, 
            0xBF6208EA49B736A9ULL, 0x6ADBC096B0C2A9B8ULL, 0xB7EA891D9F62C574ULL, 0xF1D48A95EE471AE2ULL, 
            0x655EFF7532AECE25ULL, 0x920E211A75B591EAULL, 0xFA0515E80BE6309EULL, 0xB5EB868E30949C09ULL, 
            0x16FBE43A9B5B9373ULL, 0xECFD1F1D0B54082EULL, 0x2665535A3C392CF6ULL, 0x9A8E4E6142D57853ULL, 
            0xB90F41A5C504ED67ULL, 0x9E2E3DFD46C5A4BAULL, 0xF9FACA2967327703ULL, 0xF8E68F30BF444173ULL, 
            0x34A17693D8FCFF71ULL, 0xC0635EDFBBF0E946ULL, 0x3CC9A64F37B137E5ULL, 0x25BC06BB1A3397B0ULL, 
            0x57741476519F4E38ULL, 0xABF84BDFB519B8ECULL, 0xD9C9B520726185DAULL, 0xA72A4E350CF7830CULL, 
            0x6730ADD2AA554C27ULL, 0xEBB9B18D6EC78048ULL, 0x69ED17C8F8E2ADC6ULL, 0xE7FA880F019F5ABCULL
        },
        {
            0xC5FF7F2ED8E90EAEULL, 0x845027EC41AA8610ULL, 0x043952B3DDA9ED19ULL, 0x36F42DF60DB416CFULL, 
            0xA03EEF37C6AA250FULL, 0x0458D7E6D172E8A1ULL, 0x4CA64FBF451BB6D1ULL, 0xE54A1309FE2585E7ULL, 
            0x4B3BE66AAB93652EULL, 0x908602BFCF910D60ULL, 0x1839B3CAAD6E268EULL, 0xE5F428AFE854C147ULL, 
            0x60DDA2BCE1DD60DDULL, 0x8EA82405D6DE9F2FULL, 0xD764A85B67990180ULL, 0xD4341AA02345688FULL, 
            0x138A7DD4B38F94C7ULL, 0x523380CABD502ECEULL, 0xF17BCD56A7FAE479ULL, 0x89D7B0F0ED1F5C5EULL, 
            0xF87194F22ACFA027ULL, 0x44AFD0A97DB02B85ULL, 0x728B50FC3E38E3D1ULL, 0x115941A7198F628AULL, 
            0x275126369F6B761FULL, 0xA322EB877E5C405DULL, 0x83F9BBE925C20588ULL, 0xE4034E6FD05A6F51ULL, 
            0x87F79096AE1427FBULL, 0x77DBE507099CBA33ULL, 0x759088E749ACBABDULL, 0x8435DAB644C80E1CULL
        },
        {
            0x72C8783455C44541ULL, 0xAF7E540D09FC1F2AULL, 0xD5B7C6AC4B964266ULL, 0xF865A7FDD1591157ULL, 
            0x950900F859D01F17ULL, 0xC67A9A0796428903ULL, 0x88C5668AE9EF364AULL, 0x604B3791F66E139AULL, 
            0x4840895BC4AFC9DEULL, 0x003D4F0EFD25AA2AULL, 0xD37A647C90D2E73DULL, 0x657726026D7B3EE3ULL, 
            0x8DD1DF48DFBDFEA5ULL, 0xD2A6733CA013741CULL, 0x6CA9F39ACE67AE47ULL, 0x8BC8BAC6D7208167ULL, 
            0xE3DDCDF5FFED7849ULL, 0xF6C88AF6F4980F4CULL, 0xC8F9FC102E59D486ULL, 0xABF1F74F25E77036ULL, 
            0x10B63599B3C37C64ULL, 0x3CA238EBD937092BULL, 0x509735DEFCE11027ULL, 0xC079C5C8440F4327ULL, 
            0xD84DE38432CDEF49ULL, 0xAC3ECB9122FBCFC8ULL, 0x0D26C565DF84CD63ULL, 0xB7FA952A81879C5DULL, 
            0x5794F08EEF3250EFULL, 0xC8590FA5ED67BD4DULL, 0x1033C4109FEDFC65ULL, 0xBCF3EA3166098873ULL
        },
        {
            0x016586A9E4ECC5EBULL, 0x8C0BF9F772978813ULL, 0xEEA57FE5D1B7262CULL, 0x0202490B2DCAB15BULL, 
            0x96EC3ECC5D580CA7ULL, 0xF3E3D0674F033EDDULL, 0x1367AEA1979B6132ULL, 0xFED9695E362C34BEULL, 
            0x76FE60712936A92EULL, 0xF915E7DCCD1C741DULL, 0x06013B6B5E1945AAULL, 0xCBA1863BF3BB61FAULL, 
            0xB35C7E016B25E998ULL, 0xF5F277B5B9EA1252ULL, 0x19DBB624BA2AEE16ULL, 0x7252ADCFA524A7E8ULL, 
            0xF2D15B8513DB6E56ULL, 0xBFF28A478D7CCB64ULL, 0xCD55889363E85426ULL, 0xAC7FDAA5D6414A36ULL, 
            0x9FA39E183BD69F73ULL, 0xA74A71BEE9796E0EULL, 0x728242F2CB1B4A5BULL, 0xE68C556CED6B7AA4ULL, 
            0x09185C3ED9381563ULL, 0x655C8682414BE3F3ULL, 0x4006D90714522E20ULL, 0xA4B34F84674596B8ULL, 
            0x8143EB7DD4D989C2ULL, 0xCAEFBB7F03599486ULL, 0x9DCA368BF33F680DULL, 0x26704F2005E829C9ULL
        },
        {
            0x208B0D7199F0D0A9ULL, 0x93B2644120EB3609ULL, 0xBDE317AB2B8A352EULL, 0x05F74B118103992BULL, 
            0xE0355995267DAEE1ULL, 0xE50B30616CC54887ULL, 0x82008FC789029664ULL, 0x2C6CBD50BF7EDAB9ULL, 
            0x906ADC3DCB6E6229ULL, 0x28E310FE54ED86BBULL, 0xA2616FAF49FE634BULL, 0xDCBF1E1959109FABULL, 
            0x42AA80E78E2F99EAULL, 0x4CF4D94786E89BE0ULL, 0x617CFD5D6635E3D2ULL, 0x87CACB72E1AF1E1DULL, 
            0x02BA07E837437E12ULL, 0xE70D87CE2D7C19EEULL, 0x772466AD17FB2C5EULL, 0x46DB4554EB97C5F3ULL, 
            0x8DEEB6D75229A443ULL, 0xE4811E7DEFDC4E1DULL, 0xBB68C3119370A5C7ULL, 0x05CEBD4A68B03A94ULL, 
            0x17CD66ECABF640C4ULL, 0xDA87053CD8E991A0ULL, 0x2A578F7C30B93C3AULL, 0xD1FB58416280094CULL, 
            0x63DD6E2ACBDB1892ULL, 0xE36751CBD698C47DULL, 0xD7FA84EE828C7794ULL, 0xD028D142CC77328EULL
        },
        {
            0x082992BB8939849CULL, 0x1E51356C81433EE5ULL, 0x683FED7099E4E434ULL, 0x9C9E4FC84D09E9BBULL, 
            0xD27A510AF29C2252ULL, 0xBC93D618930611C6ULL, 0x68DD048556A5F12BULL, 0x7279B249077C86D6ULL, 
            0xF11AD1A6F8DBD7BDULL, 0x41CB47CEF746D68FULL, 0xC5BA5C41BE2F423BULL, 0x673B4CDBAB48E491ULL, 
            0x4BEC0EF84585D169ULL, 0x8581FECFBA5645A0ULL, 0xFCD5EAC6843E6AD4ULL, 0xBD5F9757533B4994ULL, 
            0x851E3611B7756A3FULL, 0xC77BC8B07A863FF2ULL, 0x08FF08ECDB6DF330ULL, 0x2E82442BC45B37C4ULL, 
            0x39011459C6F6DF8BULL, 0x3754B3F9C04802B2ULL, 0xAD9A8E10815AF9D3ULL, 0x6D486E3873E1A1B8ULL, 
            0x5FE1A8D4BF2B6607ULL, 0x74215D40616815F0ULL, 0x98C015ADB57D7B48ULL, 0xC00953C8D9131BAFULL, 
            0xD66399FDFF376956ULL, 0x38B769B0F8F3722EULL, 0x519A5A0C0A818F7BULL, 0x8FCF4C117F401944ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseGConstants = {
    0x0BB1248310FD8EE9ULL,
    0x11BF71C2A8318A5FULL,
    0xA9A04BD1430D73F2ULL,
    0x0BB1248310FD8EE9ULL,
    0x11BF71C2A8318A5FULL,
    0xA9A04BD1430D73F2ULL,
    0xD36F2D997B1C1807ULL,
    0xE613AA04EF87E604ULL,
    0x4C,
    0x3D,
    0xB3,
    0xFF,
    0x3C,
    0x84,
    0xC6,
    0xA0
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseHSalts = {
    {
        {
            0x9CA9299CDB968AD5ULL, 0x2C9AB403E3192100ULL, 0xC1D5DEA473D3D819ULL, 0x7F0166B5EF9E2955ULL, 
            0x5702C3E5AA8C7D43ULL, 0xAC44154B9C8D2E12ULL, 0x741AE1864BD22CFEULL, 0x2058DDA3179A9CE4ULL, 
            0xF4411D4E52CA9C04ULL, 0x3733123B751FD025ULL, 0xCE9F9E0AA2ACE429ULL, 0xED62BBFA579DFF6EULL, 
            0x03BEA15536B11D66ULL, 0xF83C0E4B0A1141FFULL, 0xB696E11D2001BCD8ULL, 0x86A57B617BD8D06FULL, 
            0x6B4BF89FCA82FA52ULL, 0x7C6244F55103D77FULL, 0x51D42E67D6A0B322ULL, 0x253E9FBBFA74A5F3ULL, 
            0x3710E458A350F625ULL, 0x2F4ACAF7705A2E99ULL, 0x3E6ADBFE95897CF3ULL, 0xAAADBAF26B721C69ULL, 
            0xD476D3FFC73A8DEDULL, 0xC64C5EF1D8DDE2BCULL, 0x0AB9ED2E89DD78C5ULL, 0x5FA9978E2487404CULL, 
            0xC2C4CA26151330EFULL, 0x7A22B20F64DC7FF9ULL, 0x9F32BC616FCB62EDULL, 0xB9E8EE1762CFE436ULL
        },
        {
            0x9D540C39DA6BDF84ULL, 0x968DB982B7A59DC6ULL, 0xE55FFF0B23947680ULL, 0x9D5DF6D1F2FA9C14ULL, 
            0x1DB46B55AE61B832ULL, 0x7F9A8C26ED7014FBULL, 0xDFAD2049EDF30521ULL, 0xEA0CA4E301EA80C6ULL, 
            0xD938FB720689B393ULL, 0x9A6B59509E90DAD6ULL, 0x8993D3B65573A462ULL, 0x67DDB5F2E99AE730ULL, 
            0x235DC0D4563D2841ULL, 0xFCC6A770E6F1884EULL, 0x3D4340CC5F48B9C5ULL, 0xEA411A7AEF21C31DULL, 
            0x070B684E076104B0ULL, 0x683C479011A5075DULL, 0x0D17C6BF1449D290ULL, 0xFA54597EC8E75286ULL, 
            0x13180B88F4AF8323ULL, 0x85CD652B71282309ULL, 0x3FD13AFE3FA11313ULL, 0x78B17714671C2E7CULL, 
            0x44CD1A2049492239ULL, 0xFFDB209759AAC9DDULL, 0x2EE7051E12084BDEULL, 0xEF93ABF2E62FED15ULL, 
            0x2A15CBA0B555F066ULL, 0x9CEB8C97AE14BE49ULL, 0x544D0D84295EC4DBULL, 0x23B5D95AC32E18AFULL
        },
        {
            0x1CAE8C7F371B6A69ULL, 0x5F19BADD80B9C3F1ULL, 0x75ECF7F612BB4525ULL, 0x02AF4E28E905D2D5ULL, 
            0xCCC6C9CE817CADF6ULL, 0x63B0DA016A1B2AB2ULL, 0xEB564F3E0503E55AULL, 0xD9905F2B55C83534ULL, 
            0xF7FF8EBEA6728DF8ULL, 0x45B810C6D3895A49ULL, 0x358E7BD4EC2B18A0ULL, 0x92169329F9CE8A19ULL, 
            0xCF91DC219677D561ULL, 0xBA350498DF08CB2EULL, 0x8124C0F099D1CE06ULL, 0xE2554B158B7BA085ULL, 
            0xA7E088E5D4941308ULL, 0x94C73715D7585A02ULL, 0x3B866042D0A753C5ULL, 0xEF9F31D8D977E160ULL, 
            0x332C75FC6490ACD4ULL, 0x7CB3A496CC47EF30ULL, 0x475308D5DBC0F061ULL, 0x3926656D91C03C53ULL, 
            0x098FDBC29D289448ULL, 0x08D41AC875F5E357ULL, 0x0214600D996A82B7ULL, 0x8C3D5E73DE96FA21ULL, 
            0x7F2884616C1C3B9EULL, 0x84578A196158CE35ULL, 0xF56C31B6F473789DULL, 0xF060ABCE834C3061ULL
        },
        {
            0x8E77650F091E0FEBULL, 0x330AE185C16784D3ULL, 0x2B75A19751A676FAULL, 0x14649A8A249A2D8AULL, 
            0x8F2C982445E21FDDULL, 0x00CF4899598115E3ULL, 0xC1BF9F8E8A1FDCA2ULL, 0x01D33BB7F3C817FAULL, 
            0x25A337A39DDA3D4AULL, 0x1FA971AA04387FB1ULL, 0x2603097505DA11DDULL, 0xD86F5B3089A44A1EULL, 
            0xEC44C9C4891C958EULL, 0xB305FD2A07E1A277ULL, 0x75A161D391A376B3ULL, 0x0CF997A5B0E48827ULL, 
            0x5D513BEFBFB51DCFULL, 0xDA39A6925FD5C7B0ULL, 0xFF04321C197F30ADULL, 0xF1D84DBDC7846B2DULL, 
            0x93D7DDCFFF672EF5ULL, 0xCEBD0814E129FEBCULL, 0x79F4229DBA792A77ULL, 0xF8783F67FCE64F0AULL, 
            0xD43FEA8DF483B408ULL, 0xCCCE6FFF6E3B885DULL, 0x05AF0ACBD367A1BFULL, 0x01EAB22A0F8D1458ULL, 
            0x2A8F6474BF3C8F84ULL, 0x9735575BAB1ED86AULL, 0x5A9D6529C0720FC7ULL, 0x88F522F0812BA702ULL
        },
        {
            0xA81D4FECCEF4A4BAULL, 0x9E219055F431C492ULL, 0x461484BD63E81BFCULL, 0x8BBB788F79EF70CDULL, 
            0x538CC807BAE128C0ULL, 0xE75682F882BD63B5ULL, 0x804A2AB3A392FD70ULL, 0xA44DA03398055A6EULL, 
            0x00C7A6CD023AFB7BULL, 0x0A579B108E02A359ULL, 0x2B71C7C013843670ULL, 0xE3846E10F8FE11B0ULL, 
            0xD19F7AB67227A85FULL, 0x82EBEF55292F1292ULL, 0xF4517344B3D15D78ULL, 0xE83A8666A38A7539ULL, 
            0xACAB8FCCF43A2EE2ULL, 0x651A2DB62BC64CFBULL, 0xDE5D816799F46AF0ULL, 0x669FC279CDAAC026ULL, 
            0x6864305372A2FDC3ULL, 0x87E34C26A79C8BA8ULL, 0xAC8F439D8057337FULL, 0x1A0676D7EF8D05BEULL, 
            0xABE30F50615C46E4ULL, 0x7375E5026CC56DF4ULL, 0x30778675A99A9553ULL, 0x5432E14344C2F0A1ULL, 
            0x19C7CCA3A6579769ULL, 0x4259A78B4173C78EULL, 0x1F874F5C9633F222ULL, 0x7EFC1F0B20CCC7FCULL
        },
        {
            0xC7F167A4C285D20EULL, 0xF6BC9E708C1CDB52ULL, 0x0B32E86BEBC8C3A5ULL, 0xC25B3F34D0B4540EULL, 
            0x5E84FB11F8313852ULL, 0x23FE0A918A66F2B0ULL, 0x2DA2A63B797B411FULL, 0x645476D41F28004FULL, 
            0x30EE7364CA10E169ULL, 0x696408B934C2AD8FULL, 0x1957414BB0C959E3ULL, 0x3EA4CA68C2F30A69ULL, 
            0xFA1F9E07426F7BD1ULL, 0xBAD9189969F0C198ULL, 0x5CAA28561C6F7640ULL, 0x875F186A0C9A4B92ULL, 
            0x088006B3A49BF756ULL, 0xECC8D64CDC4F560FULL, 0x22FB9AFCE4844358ULL, 0x254061017EB3A115ULL, 
            0x73B78C6402530CE1ULL, 0xA13FC2084F30791BULL, 0x06B59578C255DAF3ULL, 0x543315B0C4B48C31ULL, 
            0x93436D398E1ED4EEULL, 0x5B1FF110556E4A11ULL, 0x6757067C03ECE6D6ULL, 0x91F56423873A152DULL, 
            0xD114CBCD71425870ULL, 0x6230327961CA324FULL, 0x100C700795C59CEDULL, 0x5EE6D5DBA83191A9ULL
        }
    },
    {
        {
            0x427179A4D18D4A75ULL, 0xB80DB3E948BE2D80ULL, 0xEA1A2D03D9A74361ULL, 0x86120DA815E78BB0ULL, 
            0x7D3206A73DC67BE2ULL, 0xCC1FCF88808EFD0CULL, 0x9393CC111DEE55E5ULL, 0x20937F8FD2A599D9ULL, 
            0xF4E017E8A53128BCULL, 0xA8D9E8C0E7C1EACAULL, 0xEE028BF009683AF5ULL, 0x58245159018CE7CFULL, 
            0xDBA229AD6EBC7841ULL, 0x1C9BD1B0F8BCC056ULL, 0x1930E43E76D5E51CULL, 0xD94A9DB487D21317ULL, 
            0x60E2276743CD300FULL, 0xFBC2369F5DDEC41BULL, 0xC1F791926A65AA20ULL, 0xB757FA12CF82BA81ULL, 
            0x726A26D18AE2E9D2ULL, 0x7BFB7620E579E82CULL, 0xFCB42CA72A4E0E69ULL, 0x94D8103D6EB9D2B5ULL, 
            0xA5C2DC4F82A50455ULL, 0xB251ED57E16F041DULL, 0xAC4A765D4C4263D0ULL, 0x0C5261215E25B72EULL, 
            0x6B2DB34F20DC5C50ULL, 0xBD167A6158BACC58ULL, 0xB41A516693E7F8B3ULL, 0xB04EBD9016EE24AFULL
        },
        {
            0xC2865DD9CBE21F3EULL, 0x08313EDD2CC19FBAULL, 0xD918D896F69F1683ULL, 0x8C8929A0585FAD4EULL, 
            0x65B2A6CB82258736ULL, 0xB25AA43346C8A017ULL, 0x9C553E025240CA39ULL, 0xE11C2025E352F54BULL, 
            0xB14BCDC3B1D5E0A5ULL, 0x310A81F65E5D1426ULL, 0xABE44D6F1625C169ULL, 0xCA5536CC67B66AA7ULL, 
            0xBB65949115819A52ULL, 0xA99925CFBDD170A3ULL, 0x3130B8CF09AEA6DBULL, 0xBAF7679E8C61A626ULL, 
            0xF898EF22D6D341D2ULL, 0xF14E9F7332710C6AULL, 0x4F6CEE153D0D6995ULL, 0x1761A12D17A11274ULL, 
            0xDD76ED33BEC1CE4FULL, 0x892A4A13C086EB5CULL, 0x84194A49B630BDD1ULL, 0x8ADB9C45EF3C2FC3ULL, 
            0x589911A7CF626985ULL, 0xFE4489C67DE06378ULL, 0xC15A58BDA9778687ULL, 0x169E96C0EBD2274BULL, 
            0x738598AF67AC260EULL, 0x29C22767004FCC4CULL, 0xC2A67D72366A9E7FULL, 0x6248477DE26E48C7ULL
        },
        {
            0xE5468F9C839767E7ULL, 0xEB8C6987929FC594ULL, 0xAA4CB70B2A07A219ULL, 0xA70FB33E0D2C4161ULL, 
            0x9D418F915221A9A5ULL, 0x3A56166FB8120E8DULL, 0x4A9A4E51E18215A5ULL, 0x232FC95A5C50BBB7ULL, 
            0x9F925800EBBC33D9ULL, 0x28A0949636EE22FDULL, 0x815EF1CACA6380EBULL, 0xDC080EF22DF7C61DULL, 
            0xB9BC11AF6EE818BDULL, 0x4E1B0E47EE37D955ULL, 0x4D05F1BE0ECC2818ULL, 0x00FFB6CEDB5DD5A0ULL, 
            0xC31FE72F0A231E2AULL, 0x452F9926E9A7C2FCULL, 0x02FD2FB665113C49ULL, 0xA700E7C66F55C936ULL, 
            0x4CC137A1C3967257ULL, 0x217FEC6E3954AE6AULL, 0xD61670DE4044A625ULL, 0x89BD7C4E6B7B6E61ULL, 
            0x89CB88AC3C464505ULL, 0xDFFAB55787B10C0DULL, 0x3488C25494B550A4ULL, 0xBD100AAA6FD785A9ULL, 
            0x4C2C3F1417CBC197ULL, 0xE31C6ACD40EE588EULL, 0x7023E5178C476678ULL, 0x5C703117A7A4313EULL
        },
        {
            0x05D934BD4A59B411ULL, 0xE497E330970C7B2DULL, 0x9B29DB2844F615D0ULL, 0x33342B850C66503EULL, 
            0xED53FC618652AA94ULL, 0xFEDA763B0414AB20ULL, 0xE3816A4293D2DCD8ULL, 0xD35F6E1B2129E429ULL, 
            0xF1D00C68D82BFE5CULL, 0x4F865557CC9D1DAEULL, 0x7BD30793378134F4ULL, 0x4598449406316999ULL, 
            0xB8E6B4B7E00BE4C1ULL, 0x6B91F2C5185D2237ULL, 0x68D20644A7D28D0DULL, 0xCB2D796C4AF2A6DDULL, 
            0x2ADA832B3F6A858EULL, 0x61D26247384BA640ULL, 0xF9855ECCC411C9C4ULL, 0xC6E260E9670A7B36ULL, 
            0xFDD98C7CEC3054C0ULL, 0x1444E311CE382036ULL, 0x2F3D26F92694FA6DULL, 0x98C2A004541727F3ULL, 
            0x2CD76E3BA9CB9473ULL, 0x7635A36EE23DD244ULL, 0x9BC42C8A6545F755ULL, 0x4AF3CF0EEFD420D2ULL, 
            0x8C0D887D09509FAFULL, 0xDB488F2C876D243BULL, 0x1EABCAA5FFD184E3ULL, 0x83C629662CD0E3D5ULL
        },
        {
            0xF5D941155197A3AAULL, 0x0592F38D70D56DFBULL, 0xBA20E0A2AF6C5C19ULL, 0xFCB3BDE88D6D2336ULL, 
            0x7FF583586CC4DBD7ULL, 0x91DF5394D5288169ULL, 0xF3796BD531DD1957ULL, 0x183EA11918690238ULL, 
            0x702894F49D211CA2ULL, 0x816CE4031127AD18ULL, 0x052E9CAF8A34207FULL, 0xE8F0703EBA5EC8DDULL, 
            0x3F9B40BF9C709C25ULL, 0x2F90031B80F7BF58ULL, 0x7235B70296E90A87ULL, 0x0E15122F2045549AULL, 
            0x4F54B2EA17310932ULL, 0x913DEED79AFA74CAULL, 0x90BB5EFD0A32DBD0ULL, 0xF76DAE0C0C95011DULL, 
            0x16E153E85D64BFA6ULL, 0x2331B030FBBEB174ULL, 0x86BB63D0FB6D4CEFULL, 0xDECB3D51D68635A4ULL, 
            0x6B9551633BDEA6C7ULL, 0xFF371C1F48612CFDULL, 0xF2E93B0E11DBD95AULL, 0xFB2AE9765ADA1F61ULL, 
            0x84DEDBE251401018ULL, 0x6A301CDB0792AE71ULL, 0xB413EDB04A9B6811ULL, 0x86F81009292FDC44ULL
        },
        {
            0x67D845358E78FFDBULL, 0xBBA81377491FF773ULL, 0xB2C81338D3B70623ULL, 0x14DB1D6BDA69BF11ULL, 
            0xEB9CAD403C367983ULL, 0x67D579054123A769ULL, 0x80D66703E7AE3F32ULL, 0x31F0739DF83EDCF0ULL, 
            0x0DBAD50744DB7ABFULL, 0x1609B8D30409A869ULL, 0x5693F3E72BC91FB1ULL, 0x64737882497B7672ULL, 
            0x675236E8E73B3A63ULL, 0x462266C6AB6A5222ULL, 0x7D41CE1C0BAE89A5ULL, 0xAC4063B7B571053FULL, 
            0xF88A2BD29F2D7C5EULL, 0xFBB77A9B4AEBCEB1ULL, 0x7FF61F71612A6B49ULL, 0xBF29FE46BD347E34ULL, 
            0xC995431A6A8DC5C2ULL, 0xB72ECA03B7CB7919ULL, 0x79BA0C8C8D386B7AULL, 0xFA5A10966B361CABULL, 
            0x0593DEDC09EED506ULL, 0x6ED98EF1051FE591ULL, 0x1A94D20881791E92ULL, 0xDF5FEFCAF21FA567ULL, 
            0x12590177D8B17FE0ULL, 0x3E70E67BECBDF36BULL, 0x61B9FDC01DBB3189ULL, 0x23B5D6C2E1A77ED2ULL
        }
    },
    {
        {
            0x6CF2AF1B9D5BEE1AULL, 0x5644620BA4EF5FA1ULL, 0xA7EEAD131AB8E13CULL, 0x9692B0E8515801E1ULL, 
            0xEB822C551A3D1E84ULL, 0x24EC8D1B59C4631FULL, 0xBE76690D4E971278ULL, 0x447B82FFD1C9D1BFULL, 
            0x08588C26A79A956DULL, 0x114F8F86D16D850AULL, 0xC5704EC4FFAA9735ULL, 0xCADEA528537192D9ULL, 
            0xB2E13F1DAAF9A7FAULL, 0xD2BD03943C1B82ACULL, 0xFA6168FC90310BA6ULL, 0x3A66E46C224E8CE6ULL, 
            0x52B20A88FB8A70B3ULL, 0xDDCD93B0382A4EA3ULL, 0x89EA6C1699C9920FULL, 0xAC0346159D5CAC1FULL, 
            0x4C2B73C0210647A7ULL, 0xFF1C5BFAE6A74EEAULL, 0x09E42A28861907DFULL, 0xEB344857770C4D1DULL, 
            0x143C2B797042BEF6ULL, 0x407F2B85D03594AAULL, 0xF9DFCD314DE65422ULL, 0xC2A0D766B4F0A8C5ULL, 
            0xA09486115E6AE270ULL, 0xEFE605956D66D5B4ULL, 0x18A971B3497BE0B6ULL, 0xB400F0F3012885BCULL
        },
        {
            0x62891849196317AAULL, 0x0858F2DCB3EB45C9ULL, 0x40F88B99A8801FBCULL, 0x00B8FD8B8E212AF2ULL, 
            0x95D1E5EF430EFDB8ULL, 0x57413E765BA35858ULL, 0xD0AA51742DAFBC8BULL, 0xF4D960DF965A795DULL, 
            0xAED25E0D6AF537FCULL, 0x85B2D2E15F55EB20ULL, 0x2CD81B992D3D834BULL, 0x1FD317134D5A98AFULL, 
            0xC37ED905BCCCE6EEULL, 0xAD3C7F3CF64743F5ULL, 0xE42B79E5C37A6C2AULL, 0xEAD925D6451A6776ULL, 
            0xCEA3FA6A682DC820ULL, 0x50C8DE4A00338517ULL, 0x02F5424B7E098FE9ULL, 0xEB5723BF6D9A09D2ULL, 
            0xD36E36D2DD269A1DULL, 0xB42C96B5643BA76FULL, 0x10F51F01D27FF18AULL, 0x012F507FC63561B8ULL, 
            0x096F07964E7C796AULL, 0xD9476587D05E5F9AULL, 0xA1B4797DDE8B0B6FULL, 0x91D439BF23F2A745ULL, 
            0x3A1453C1D3A0357DULL, 0x2836F14BB21113ECULL, 0x69AF59A7DA173AF5ULL, 0x8E4B5C3E799A6313ULL
        },
        {
            0x404A334CB9A521FEULL, 0xAFA262B724C77003ULL, 0xD18DC7BB34184AE6ULL, 0xE2FFDDA5D88F2BE6ULL, 
            0xF3BD65CF354562B4ULL, 0xC4E07DE5275E328FULL, 0xE6A5E046A88752B0ULL, 0x49B0B429A9F7E5D0ULL, 
            0x113B8329E66DFEC9ULL, 0xB67694CC51D4D18CULL, 0x33F59941B471DCE1ULL, 0x032362D149F0BB9EULL, 
            0x7D29F07FAC1DEC0FULL, 0x717E33EF209D4235ULL, 0x568BBAD7CB0E39AEULL, 0x7B75AD46A4C3286EULL, 
            0xDDA97798AD1737BCULL, 0x6F79B07A3A5B9520ULL, 0x62DEDE2FA569DA18ULL, 0x61D19B283D302D28ULL, 
            0xDE824B36E96FB92CULL, 0xD8AF8CBF603A4A91ULL, 0x5E76FA3EFC4E6E04ULL, 0xFB8B58AD722B9514ULL, 
            0x1742EAB109B5408CULL, 0xC49FD83788F8F3D0ULL, 0x2CE9CC2A4DB04EB7ULL, 0x7C7975E1794CA4BBULL, 
            0x40E7F2450B86BC91ULL, 0x699BB0D7ACF87831ULL, 0xFF6434A039DC74ACULL, 0x03579B980AD8F8B0ULL
        },
        {
            0x0EDE0C31DBD64D44ULL, 0x16FA8B3D2F358A8AULL, 0x638FB431712B10EBULL, 0xC59921B2C4A4B944ULL, 
            0xB57E3603011663A4ULL, 0x3DC47F874FD5E270ULL, 0xFB8AEFF7E941EFA6ULL, 0x7031BFF55AACDC44ULL, 
            0x374F9B8AE5B5C39BULL, 0xF1E2AA80E6321137ULL, 0xE4BAA92F0990EB81ULL, 0xDA91D0E478E0162AULL, 
            0xCCA408EF18E2B1EFULL, 0x34FF5E0ACF82FF8DULL, 0x807A2DB6C47FBD84ULL, 0xEEC3A747E7D966B0ULL, 
            0x67DF1BDE92B7AFA9ULL, 0x8B27906EB94DD0B0ULL, 0x28E2466612029B01ULL, 0x2B2733F6E6875E8AULL, 
            0xEE6CD76947D7CFD2ULL, 0x7937FFBDE88DFBE2ULL, 0xE0C52A7B9AADE637ULL, 0x9290EDB0006DF7D1ULL, 
            0x7857C6133AFEAFC3ULL, 0x60946991077166B9ULL, 0x06774B9C18F99AF7ULL, 0x0379C07DBC96A0E0ULL, 
            0xEB0AC246EA24D0CFULL, 0xEFCB236C043558F6ULL, 0x402504A92758013AULL, 0x219A5CC83E51502AULL
        },
        {
            0xBA0C9B2401B1C566ULL, 0x0E76EDDD4061C209ULL, 0x46DC836429EE0BE2ULL, 0xA800C4703732E1F7ULL, 
            0x268D3CE770169F35ULL, 0xC64D4245EA5A0766ULL, 0x20916B0913D84DACULL, 0x19040A920C807261ULL, 
            0x14012717C07EC1B4ULL, 0x39E55FE3E0998A15ULL, 0xE5993D54E98DAC20ULL, 0xD684545B4731244BULL, 
            0x5026480EA06FD69EULL, 0x757A8A5CD1349038ULL, 0xE481B2A8E4133F32ULL, 0xBABC4EF569E8B91EULL, 
            0xB17BB27A3B7D8148ULL, 0x3E01402428CC7E46ULL, 0x8F91BA0B80141C9DULL, 0xF52C72D4580055E2ULL, 
            0x03DE40599E6FE518ULL, 0xEDF723DF467BE788ULL, 0x872E3FD4C675DE94ULL, 0x36CF4AB16C928A79ULL, 
            0x6F66FD94EBB25B6CULL, 0xA041E36A48937A17ULL, 0x611F13C7673D4A73ULL, 0xD020DCD6EC2F81DAULL, 
            0x45C77B37C49CD22CULL, 0x9D320C88A10B1A2CULL, 0x1C18892EE89C2BEBULL, 0x1F194B5DDC988489ULL
        },
        {
            0x51C8B4B3FEBC3A72ULL, 0x47A42EBE808DF508ULL, 0xB85C0A6791FB0D56ULL, 0x84501F2FE7EDFA02ULL, 
            0x4139115059E45E7BULL, 0xB2A69DFE8532D5A5ULL, 0xA1C92F4BE04A0ED7ULL, 0xBBBC48A443704434ULL, 
            0x05F73F41F2AC8CFCULL, 0x3EC4927ED6104419ULL, 0x0207D29A11CCE0E6ULL, 0x2371A0BC3AB396CBULL, 
            0xEEE1872756E9253AULL, 0xBB9ABF0B27685FDEULL, 0xD5D90837A8C80EA0ULL, 0xB76C98E1BF99BB37ULL, 
            0x270A095A27BE1F0DULL, 0x604D1750C73E6C2FULL, 0x849ED9175214AAA0ULL, 0xAC7F7977D890932FULL, 
            0xE50BBBF483972FA3ULL, 0x0584B971791B4DB1ULL, 0x864B43F0759C4220ULL, 0x9FD6D2F0FC66EA38ULL, 
            0x282077F9ECE7ACD6ULL, 0xB6412ED6003D806EULL, 0xED6771233544E5D0ULL, 0x4F89ED1ED36134F9ULL, 
            0x30531CF4C3FE9455ULL, 0xEB7DB221224B6D71ULL, 0xB8C5045AD77746A3ULL, 0x019610273F273B09ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseHConstants = {
    0xEDE8C04AA03665AEULL,
    0x3387C11AE0F59EDCULL,
    0xD164E3F5C1399BC2ULL,
    0xEDE8C04AA03665AEULL,
    0x3387C11AE0F59EDCULL,
    0xD164E3F5C1399BC2ULL,
    0x0522DA5E7310DC94ULL,
    0x08366BBF5C5DF7CFULL,
    0xE9,
    0x98,
    0x06,
    0xC9,
    0xF8,
    0xBB,
    0xFC,
    0xDA
};

