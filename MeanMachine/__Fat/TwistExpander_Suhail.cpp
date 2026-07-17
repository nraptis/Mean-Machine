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
    std::uint64_t aPrevious = 0x9F61D4FBEC3F6B8EULL; std::uint64_t aIngress = 0xACC0EE513CEE7C46ULL; std::uint64_t aCarry = 0xB17DFF54399A37D4ULL;

    std::uint64_t aWandererA = 0xDE28AF06CE7F9392ULL; std::uint64_t aWandererB = 0xAE5DEBF4A8305D08ULL; std::uint64_t aWandererC = 0x806C23A59544DD60ULL; std::uint64_t aWandererD = 0xE97D06E635B2A466ULL;
    std::uint64_t aWandererE = 0xDF6BD2D07A172C55ULL; std::uint64_t aWandererF = 0xB96290854294F4B4ULL; std::uint64_t aWandererG = 0x947F142D3313EAC8ULL; std::uint64_t aWandererH = 0xB817E330CC568828ULL;
    std::uint64_t aWandererI = 0xE930191DB1523F86ULL; std::uint64_t aWandererJ = 0x893B11CBA42FF365ULL; std::uint64_t aWandererK = 0xDCA7E04E8F512891ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 11247535076666165148U;
        aCarry = 13699295920875654031U;
        aWandererA = 11443473269404896748U;
        aWandererB = 13092260938517211213U;
        aWandererC = 14686544543978290621U;
        aWandererD = 13806349634420965878U;
        aWandererE = 9665699015053113529U;
        aWandererF = 14988289911102112324U;
        aWandererG = 13089794913443340307U;
        aWandererH = 14199392857096206385U;
        aWandererI = 12611337800402970428U;
        aWandererJ = 12273039814916840145U;
        aWandererK = 12219033949271411483U;
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
    std::uint64_t aPrevious = 0xEA977835F4C3B275ULL; std::uint64_t aIngress = 0xCBF3FBFFA287BB12ULL; std::uint64_t aCarry = 0xD6D30499892F602BULL;

    std::uint64_t aWandererA = 0xFD4C53217C9F056DULL; std::uint64_t aWandererB = 0xAB2BAEE2942FCF3BULL; std::uint64_t aWandererC = 0x9DBF4A785A2C2018ULL; std::uint64_t aWandererD = 0xF6DBC35EAD54AF4FULL;
    std::uint64_t aWandererE = 0xB8DCCADA231B67D7ULL; std::uint64_t aWandererF = 0xF453D1DCE14DD8F4ULL; std::uint64_t aWandererG = 0xB20E3C0B8B60856DULL; std::uint64_t aWandererH = 0x85A2EBFEE3144B24ULL;
    std::uint64_t aWandererI = 0xE92EBB89DA083C18ULL; std::uint64_t aWandererJ = 0xB295F4711588F651ULL; std::uint64_t aWandererK = 0x968CE60157A1DE1DULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9563823453682420970U;
        aCarry = 9573351312746985895U;
        aWandererA = 10343058224190934138U;
        aWandererB = 10115679742555583931U;
        aWandererC = 13453449698959237519U;
        aWandererD = 17387234754734166744U;
        aWandererE = 12574429171945196820U;
        aWandererF = 16304385947206177597U;
        aWandererG = 11177973594683688083U;
        aWandererH = 10003535649638003390U;
        aWandererI = 13654513678531028917U;
        aWandererJ = 16133912135577214995U;
        aWandererK = 13902513171711732043U;
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
    std::uint64_t aPrevious = 0x93378B54EE767AC9ULL;
    std::uint64_t aIngress = 0x89699DF34F929A50ULL;
    std::uint64_t aCarry = 0x8C081849A45816D0ULL;

    std::uint64_t aWandererA = 0xB64F4AA20670A497ULL;
    std::uint64_t aWandererB = 0xB237B0F70E7E0CD0ULL;
    std::uint64_t aWandererC = 0x91AF3356804AD919ULL;
    std::uint64_t aWandererD = 0xAC8ECD0DB058EDAEULL;
    std::uint64_t aWandererE = 0x893A8F157FCD3FA7ULL;
    std::uint64_t aWandererF = 0x8EB5EE1D8F51A414ULL;
    std::uint64_t aWandererG = 0x8B5AF3B2DAA3E785ULL;
    std::uint64_t aWandererH = 0xD3298A7B8B69CFA3ULL;
    std::uint64_t aWandererI = 0xDCFFC4D09E9DC86CULL;
    std::uint64_t aWandererJ = 0xDF4E3EC0A5F4FB0CULL;
    std::uint64_t aWandererK = 0xB5A79EAA2ED566AFULL;

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
    std::uint64_t aPrevious = 0xB1A893EADB856205ULL; std::uint64_t aIngress = 0xA30338D64A633227ULL; std::uint64_t aCarry = 0xC599A9ECF71A0C85ULL;

    std::uint64_t aWandererA = 0xB4F1822DC5E73B43ULL; std::uint64_t aWandererB = 0xDA22B881E8DB38C1ULL; std::uint64_t aWandererC = 0xA783D55FAFEF384BULL; std::uint64_t aWandererD = 0xAA42D64E452C006FULL;
    std::uint64_t aWandererE = 0xC50B26A402999F4CULL; std::uint64_t aWandererF = 0x8FD8D4B087DAC381ULL; std::uint64_t aWandererG = 0xBD9C65FF2F0CB404ULL; std::uint64_t aWandererH = 0xD125F145B94D3AECULL;
    std::uint64_t aWandererI = 0x9F30C1FCD902E184ULL; std::uint64_t aWandererJ = 0xE9A00387E091EBC3ULL; std::uint64_t aWandererK = 0xD2D7307B9C82E4BCULL;

    // [seed]
        aPrevious = 15702330590449126557U;
        aCarry = 14362647094530477786U;
        aWandererA = 12762115852003395347U;
        aWandererB = 17653623379303542395U;
        aWandererC = 12325104708497846328U;
        aWandererD = 18327909689478242929U;
        aWandererE = 11030886109415528738U;
        aWandererF = 17242588639651718978U;
        aWandererG = 13589013303506657909U;
        aWandererH = 13054377987027747688U;
        aWandererI = 15454632594331896899U;
        aWandererJ = 17544475094264724289U;
        aWandererK = 13813592923262910556U;
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
            0x0BDEFC3B704A073AULL, 0x3644B427DA6AF062ULL, 0x41B4D8C47F540B83ULL, 0xAE3E3AA0EA7008B9ULL, 
            0xBF3823539B468D76ULL, 0x39508BD847F2AC3BULL, 0x49103F14E448426EULL, 0xD8397C0B5AAF10B4ULL, 
            0xC6C43BCC9A71555CULL, 0xB0A1A93744A66274ULL, 0x8A0F45D3EF85D68DULL, 0xCFE393FFB37F1DEBULL, 
            0x9A67B6C1B82E465AULL, 0xC510F7758037B617ULL, 0xE798D199CD32904FULL, 0x6244228B6012650BULL, 
            0x727B9F7E35188E5CULL, 0x931406B553FDAA2FULL, 0xBEBAAD168A9D6348ULL, 0x3ADFE245DC2F9BD9ULL, 
            0x76B284E01CF9AD06ULL, 0x87484A6F9595C4BFULL, 0x61552DE7BA10142CULL, 0x5793687762452481ULL, 
            0x443130E676CDF744ULL, 0x188C608AA64749FFULL, 0x4CFE650698FC41D9ULL, 0xEFF2110CFAD564F5ULL, 
            0x94B1EBCDDE955862ULL, 0x334D823B60F0197DULL, 0xC505DD303E1B42FBULL, 0x81FC5C1BBE219A83ULL
        },
        {
            0x84CD211B5CEBF169ULL, 0x2E97F4F566560485ULL, 0x304E15195351EED7ULL, 0xF4820FF1CB079B0FULL, 
            0x4777078C250A4A73ULL, 0x6855179E7865F135ULL, 0x92EF617431671F14ULL, 0xD5DC6728DEF0A157ULL, 
            0x5710A3CC7E53A9EAULL, 0x605CD19D26904D63ULL, 0x14B4BBDFA3F94FB3ULL, 0x9F6E47834AD3F6EDULL, 
            0x09D689427CB156A5ULL, 0x0D5963A3A52BAC58ULL, 0xAD322420D551D049ULL, 0x9281AD71F04A3CEEULL, 
            0xCD40BD893195F918ULL, 0x9A9FE1E2348DC89CULL, 0xD89A59B3E74B74C4ULL, 0x4D5941584DA32092ULL, 
            0x19333F2AFAEF1E9CULL, 0x31222366151830A9ULL, 0x3CDEE7BEC457A4C0ULL, 0xC9D8151F85116F88ULL, 
            0x160B7BC1AAB3D707ULL, 0x209B8EC3D48AB130ULL, 0xEA9B73C7D8EBE76CULL, 0x780D2FAE9E22D290ULL, 
            0x996F4EC265462603ULL, 0x91059C5BFAC44294ULL, 0x0FE7895E33754562ULL, 0xEB0B94630CAD0EE9ULL
        },
        {
            0x4EC3DCED4DA66D61ULL, 0x17D68A4510D044B6ULL, 0x20390C34FBCAE15EULL, 0x3C36A09AFA254962ULL, 
            0xE8E890357F97E233ULL, 0x78FFB04D76CD5A55ULL, 0xF7DA1E8A9FBA4030ULL, 0xCA12DF4BED7A88EDULL, 
            0xC94ADF3BC1927864ULL, 0x8A8362BECB0B8C5EULL, 0x0BB9FF49C91F23C3ULL, 0xACD47A54CA5BC37BULL, 
            0x1251EA1760949D89ULL, 0x1A06A5D172865AA9ULL, 0x1DEDF8A542C6D5FFULL, 0x53F9199C33049B70ULL, 
            0x9D1C8F529F715C0EULL, 0x8E2F480D2BA44413ULL, 0xD452162158125C3CULL, 0xB7CA0E68F67624C1ULL, 
            0x390FCC2609193EBBULL, 0xC673D3E1928C6D0DULL, 0x8EAE0FC2DE4911B7ULL, 0x31153A1EE1B618EDULL, 
            0x8919E30FCBB25347ULL, 0x6D7A2AA4E6BCC96EULL, 0xFAC4C125C142507DULL, 0xD570789EB6CAC252ULL, 
            0xB20FE8AEBD59042EULL, 0xA8C7D27EC36611D4ULL, 0x6CAFCCEC42117B02ULL, 0xD6EE1C2B5EF70857ULL
        },
        {
            0x8768EF442FEEAE58ULL, 0x8B01E68841F81CD5ULL, 0x5F0C5FFBA1C6EF92ULL, 0x63BDEA73FCEE457DULL, 
            0xD46821CB123EB05DULL, 0x9850B64E0AAB8CF6ULL, 0xAECCA581A0899BBEULL, 0xCF4E92AF9D7F8ACBULL, 
            0x5C23864FE331E847ULL, 0xAD186EC0C5FB4CD5ULL, 0xFACFD16E76B4636FULL, 0x325C0ED7F3ABA8F5ULL, 
            0x482AB06549539FA5ULL, 0x8CEDE37B08BEC6C7ULL, 0x74EF512CC97BE0F0ULL, 0xF44CAD546216C819ULL, 
            0x8B6B3C51A9E6AADAULL, 0x4317427F6B84BF41ULL, 0x0ED8F1AED41229D7ULL, 0x366C61AD7F3E3340ULL, 
            0x21EF186C8672F907ULL, 0xCB326E170C12E622ULL, 0xAFAB10DD2C993C55ULL, 0x2685203D89C4ED16ULL, 
            0x83DDB03E1F41397CULL, 0xF804D014E4ED7FF2ULL, 0x328332757CD542F0ULL, 0x37B33BF24FF78402ULL, 
            0xCA797EF52BF8D5DEULL, 0xEDF94B15F7B732F6ULL, 0x369F9FB3D3F72EDDULL, 0x9F41D9DA4E308367ULL
        },
        {
            0x494340B3021AC1E7ULL, 0xDDEED3A4AD9635F8ULL, 0x301ACE15ACF0AE24ULL, 0x1396B30875E7CB4EULL, 
            0xC12ECEE54CA92A3AULL, 0x0DB1A9EFE794346EULL, 0x1E097F9E85DB84CAULL, 0x82CE9FC994483E70ULL, 
            0x7B8AFF0A7B365B55ULL, 0x3DD26B5918DBA644ULL, 0x13F95DF5E017D7EBULL, 0x39A2A974FD9C0043ULL, 
            0x7DF90528110F4356ULL, 0x422065E9455F399AULL, 0xFD4E6AD521E0BB7AULL, 0x0D78B972A3513DF0ULL, 
            0x881128980D90AE8AULL, 0xBD8F0A86104887DCULL, 0x0B0103CB5DF0A745ULL, 0x2856473C7648BC86ULL, 
            0xB345A57D5740571AULL, 0x028EA431A218AB9FULL, 0x454343079D0C54BEULL, 0xBF9CD47F36093960ULL, 
            0x908DA9BC4220EA18ULL, 0x0C0293D749AD408EULL, 0x32CD0FB982229C81ULL, 0xA08ED074E05C0E96ULL, 
            0xC59EDCD5E4D42286ULL, 0x5D74AC7A86F2DF65ULL, 0xEAA300FB93E40D27ULL, 0x30443B1A63CEBDEFULL
        },
        {
            0xB2DB897DCF763D80ULL, 0x53B8BA5783C0EAA8ULL, 0x82211ACE0FD3EA37ULL, 0x6F2743242E9B4A29ULL, 
            0x2A091565600F8D1DULL, 0x44BB43828D61BDCBULL, 0x85A6F90AB5F7CBC2ULL, 0x5C47CB92780A3E44ULL, 
            0xE63E9B36F9A6496CULL, 0x8564B6209051EA6AULL, 0x8D27FAED6D23FAB1ULL, 0xAED3ACB2F3ED377DULL, 
            0x2C7E1E5D36CCB3ACULL, 0x3EF3C39BE163A6DCULL, 0x1A60E1A2499DEF1DULL, 0x4F55AFEC47760AE4ULL, 
            0xD54286B7405E16B2ULL, 0xB727EE4B7884791AULL, 0x0447B1100E407DE2ULL, 0x9F95BB2AC0905B94ULL, 
            0xED4383093E4C21E7ULL, 0x520E7588E7F0C524ULL, 0xD23C63D2A07836ABULL, 0xCD8586594AFCB159ULL, 
            0x23CBF67290B2EDF9ULL, 0xF669AE883ED38BB7ULL, 0x814D77C577013789ULL, 0xCAEC8E23AC2E243BULL, 
            0x1E76AEFD943D012EULL, 0x634777ED0A0F3301ULL, 0x587ADCFBA2AB8E21ULL, 0xA9FB2D2718ADED2DULL
        }
    },
    {
        {
            0x346D10CED1731016ULL, 0xB03C644436AFF40BULL, 0xD170DF57695E2E24ULL, 0x7325CA8C812EFF19ULL, 
            0xC8F999C6E322E2D5ULL, 0xD2D3C2EC14F4A1DDULL, 0x6C8063FF95423694ULL, 0x0F573CF66048076CULL, 
            0xB8763E8D8A049AFDULL, 0x005E38B42AD5604BULL, 0xEBD70C4D86099AEAULL, 0x29777CBF8F5A4BC9ULL, 
            0xBE8B85FFED25015BULL, 0xAE9D3100D5447F22ULL, 0x599B8EAB8273D443ULL, 0x36A284AE8A88F08CULL, 
            0x4AB23FA92FC60FD0ULL, 0x94FA3EF9B679DE12ULL, 0xAF75AAD67A135267ULL, 0xE3DB55994CE34646ULL, 
            0xF21A5F93DFB9EB15ULL, 0x8946D671677C56D8ULL, 0xA766426A05F5BA89ULL, 0x9A79A5AFE04B21BDULL, 
            0xBE91C994A3FD004EULL, 0x6DF3F4771BA77813ULL, 0xA212AA2A495BDE69ULL, 0x15647F7999A3CFB0ULL, 
            0xB01A62EA9415E876ULL, 0xA70B892C50AFEA63ULL, 0x942C42BF029ED52BULL, 0x3353BC91231CFEFCULL
        },
        {
            0x4E277711332DD6E7ULL, 0x9D7A82E0669D89DEULL, 0x548A53C615D0F89AULL, 0xB258492C1538C1B6ULL, 
            0x8C29C424C0AA8A17ULL, 0x3B61F211D3B4B706ULL, 0xC7EA9ADD5C616BC3ULL, 0xACAF798E86080CDFULL, 
            0x9EC16D4032114C90ULL, 0xFB1DDBFDE26BE11AULL, 0x8730F2102B0DBDBBULL, 0x804D45584ACF95E7ULL, 
            0x00A53EE479A2B92CULL, 0xF8C397B79845FF2DULL, 0x455EE7790C1EF4F4ULL, 0x229B467254E222F5ULL, 
            0x12BDE46C479C0034ULL, 0x4BEF037AAB0E2399ULL, 0x20787487AB862A13ULL, 0xB2447EB8A6FBA11FULL, 
            0x7560AD2B0CDFBA9EULL, 0xDB5C41076670CD34ULL, 0x5CBEC7BB1CEC0A44ULL, 0xD4A5F139995F4328ULL, 
            0xB409C627ABB11DD2ULL, 0x142E1873D4FA9260ULL, 0x0188A6EBA0409BAFULL, 0xCC27051711816901ULL, 
            0xDE1824E50ABD8F62ULL, 0x40481289C5611D73ULL, 0xB56D4CF8B8B2889CULL, 0x1D552F4EC5390657ULL
        },
        {
            0xEA2F14710C609868ULL, 0x566FFD9FD2F2EB05ULL, 0x42212A12C8A2887FULL, 0xA19FEE6E0313F81EULL, 
            0x87DC9A8C08764A3CULL, 0x8CD027C454D990A8ULL, 0x4DE77A6998CC871BULL, 0xC6B2D1BEE4E78266ULL, 
            0x1F912E849868C8E1ULL, 0xC919BF67E626C642ULL, 0x4411F174561ADCD0ULL, 0x04EDDC1EDA9AF2B1ULL, 
            0x71954594F4927F73ULL, 0x850D75398F4541F1ULL, 0x88BE9022B1FFCD34ULL, 0x51DAF42E182FCF09ULL, 
            0x40A73A7A44BB55B4ULL, 0x5677BA32BA1DBE6EULL, 0xDDFCA9EB39277B32ULL, 0x19394B3DF97F8BD5ULL, 
            0xBB8BAE4AE35B3F72ULL, 0x389DF16B577C03B2ULL, 0x71B42DF1D8ADC990ULL, 0x85667B67ADEC197EULL, 
            0xC65F7E6002621071ULL, 0x79EDDE6E4293E56EULL, 0x3631F8EBC6262CD9ULL, 0x4413A05C75C57A0CULL, 
            0x5FF6BD137A6E9F99ULL, 0x450F778825F889CCULL, 0x213093232D42A8E6ULL, 0x4F22098A709E2DAFULL
        },
        {
            0xC74051BF494A77CEULL, 0xC72741C8263FD213ULL, 0x86CDCCD68CB39CCAULL, 0x776EE05A9A75BDD3ULL, 
            0x94E573AA9DD9B07AULL, 0x483AB0E0F29BAE12ULL, 0xA86BD567D656C483ULL, 0xEBE255C31D7D88B0ULL, 
            0x681A2B362ECD5ACAULL, 0xAB5F9E2A1CC0BB8FULL, 0x3C19D1D912C1AF12ULL, 0xC4E5723C165259B3ULL, 
            0xBFFAC05E6D63EA8AULL, 0x93493573DFE45FC8ULL, 0xAD57975A3CA6E0A8ULL, 0x6C7F58A7643FB656ULL, 
            0x1D2D83EAA1CBDEE8ULL, 0x1BBCAAAC01666E1EULL, 0x6F5CEAD3F59B1011ULL, 0x9320F2B162C428DBULL, 
            0xD01365450E457E37ULL, 0xE71D4FBCAA33B4DAULL, 0x76CF8F99CFD277A9ULL, 0x6F90323C2DC0866DULL, 
            0x80924832CC19B1F9ULL, 0x2D279AA47077E493ULL, 0x200ABC7F055B68A6ULL, 0xCDC150D68894AE07ULL, 
            0x9E5C78E9652ECA39ULL, 0x14A3C99230937FDDULL, 0xCC0C46F47B5DB4BCULL, 0x27AF333ACD295C5AULL
        },
        {
            0x013FD31BD2D8BC22ULL, 0x65A9D7F1C4C427CAULL, 0x7AB378F05FC5D969ULL, 0x60DC34DA0373DCB5ULL, 
            0xD6767876B626554CULL, 0xF57D7A3D730E76A0ULL, 0x99D10E6C70F27CFBULL, 0x5B5B3D22224A907DULL, 
            0x4A1C2994CFB74C93ULL, 0x9B7F00BE227CF4D9ULL, 0x6C09353CBC6540D1ULL, 0x20C909AF6911E5EAULL, 
            0x94F31C34812E7937ULL, 0xE26190931168B3A6ULL, 0x5D2DC61AA2DA99B9ULL, 0x4FF9E8628C5195DFULL, 
            0x2A299A15B94A1667ULL, 0xD77D5AB5151DBDD1ULL, 0x51572B58FE13F347ULL, 0xE416BA983ABDE675ULL, 
            0xCBBF1CACF05642BDULL, 0x1EA47D56C6F575FAULL, 0x4602866FD080E91FULL, 0x26F3E5A46C78BB4BULL, 
            0x8655B56F47692031ULL, 0x0342B9EBD5999436ULL, 0xA6912041867C8A65ULL, 0x812707A16E66BBB9ULL, 
            0x435DF2EE7E3CB4FFULL, 0xA96226885C838C4EULL, 0x8EE8000A9F3FF062ULL, 0x6C500BC1B5C6D97EULL
        },
        {
            0x5D336DC0AFA7FE22ULL, 0x2CDEED353F680036ULL, 0x20452F304FFD0F61ULL, 0xCA701A50A638ED5EULL, 
            0xC54B6F71388FABD1ULL, 0xEAAF1FC68E57FC53ULL, 0x6AB2BA1C870B6D60ULL, 0x93BCAA668C058F55ULL, 
            0x4B0B01754EF7A459ULL, 0xE16CB5ECE736D5E1ULL, 0xD58616837C3E3B7EULL, 0xCE3ADD29347F8B34ULL, 
            0x11F7B5C2A84F108DULL, 0x4AFA09E80419173AULL, 0x649D70EEEF1C85A8ULL, 0x76A9C915879B7935ULL, 
            0x4CD747E36F160D5EULL, 0xC385878C77F6BA65ULL, 0x559946BA41E1BE6FULL, 0x5B632E2A9F80E674ULL, 
            0x200C8A89B225B285ULL, 0x0A1ED684B35742F1ULL, 0xDD856902981B2EAEULL, 0x99B8F061A02DE839ULL, 
            0x89469E3C200611C0ULL, 0x7917273F7B865A99ULL, 0xB1C714EE4E966A8DULL, 0x93D9782E78F125B5ULL, 
            0xC185958B4DD60A4EULL, 0x892DB5C2CD9A05A8ULL, 0xF0AC15B462D4A2B6ULL, 0xEBCB4AF72EFCA3B5ULL
        }
    },
    {
        {
            0x42F770E6FFCDAB05ULL, 0xB581D4AFF69FE5A5ULL, 0x641B472D507A4D7DULL, 0x6F41344787ADDBCDULL, 
            0xC9125A1D27EF2730ULL, 0x24ED0C4607214E5CULL, 0xE01FFA4A540EEE89ULL, 0x578D3EB8AB7118D6ULL, 
            0xBFF6E5312A075DE5ULL, 0x3C12B1E5060D9332ULL, 0xDB903D629E57FE25ULL, 0xC04374D068F614F3ULL, 
            0x8437363365FDC8B7ULL, 0x8B72E91D55802F8DULL, 0x85CA7B96A07AF407ULL, 0x072348379D5C5E25ULL, 
            0x703CEB69F7BECF64ULL, 0x1EAB8AA5EF926E58ULL, 0xF8E4D107BF294669ULL, 0x37A10560BB7416ACULL, 
            0xE0B4C7BF7F8FFEF9ULL, 0xB172814F878A6D6DULL, 0x7E7098A305D10E61ULL, 0x8A16C2933453E099ULL, 
            0x75E01073969973D1ULL, 0x91E4F8679D1AE89DULL, 0xB043C28913B51B4BULL, 0xFBCBE82205D7A358ULL, 
            0xCC787326EC2C9F29ULL, 0xC4FF99E190F7D2B9ULL, 0x7230E69786BCBDA0ULL, 0xD41D27E85F03C393ULL
        },
        {
            0x32096F2F4D174D6AULL, 0x09EA4FC01AC614E0ULL, 0x05F5F7A4F81E0730ULL, 0x2E668BBC7DEF191FULL, 
            0x2FDF76A266B9E9B2ULL, 0x590B916BC738E3F2ULL, 0x01D7E3D26923B620ULL, 0x0879B85D08F0774CULL, 
            0x696AF86F557139F1ULL, 0x3864D487AD281AF4ULL, 0xA8F28B9762E9B1CDULL, 0x01A1B5CDD6A33EE1ULL, 
            0x440D0419188E0AE7ULL, 0x18D1786A4A6D58A9ULL, 0xA0CFF055A7F86016ULL, 0xFBF5684D0FB2F6FAULL, 
            0x54AA1C02DCAAF7AFULL, 0xE94D998F624FEDEEULL, 0xE6598EE045D1D89EULL, 0x67D11EB43000B45AULL, 
            0xD1D21990B02B5F43ULL, 0x9CECB3291FDFE09AULL, 0x0D31277CE9D90CF5ULL, 0x681BE196D546D796ULL, 
            0xBE1483AE40463BEAULL, 0x91D1179B0530FD62ULL, 0x03A859ABA54977DFULL, 0xC989E1331EACA7C3ULL, 
            0xEF799C347E295952ULL, 0xF90FA107262440BEULL, 0x671CB38424442AF9ULL, 0x0F16D486BCC0F132ULL
        },
        {
            0x4310BF91D34F8245ULL, 0xB9F7E72E02BCBFA0ULL, 0x2355C042456A509FULL, 0x8F86299A42D2BEC0ULL, 
            0x051954DF9A84E486ULL, 0x8E130167322B808FULL, 0xA45F4BB9963BF8EEULL, 0x0B5AC2E94AC5B5F4ULL, 
            0xFE94C02278DD8F97ULL, 0x6195C0FE6FAA85F3ULL, 0x3AFF14CC66D741CAULL, 0x37EF87943C29B816ULL, 
            0x90DBD8E3AC29A34CULL, 0x52494E3728F37DFAULL, 0x3252C2AFF809AA9FULL, 0x247B63A0DE1EC5A7ULL, 
            0x33CC5BA888E23C7AULL, 0xB31E435C160DFB95ULL, 0x1CE139502FB6790AULL, 0xD14F4ABDDF5BD6B2ULL, 
            0x8E819B534B3E0870ULL, 0x7B42638DCFEEDC99ULL, 0xF1A5C0D3CCAC9F1DULL, 0xF98409CA74149D06ULL, 
            0xA592ECBF0368D406ULL, 0x4ED25E6FBC064E7FULL, 0xD1F4CF0DE3C90041ULL, 0xA1B8E69214EE856CULL, 
            0x77EBA25507CAE5C4ULL, 0xB305EDE06B9A6A14ULL, 0x1F7E359AF1811DB7ULL, 0xD8E260905BD9354CULL
        },
        {
            0xDF7F8A3A07D31BF6ULL, 0xF9352861CA8C0E23ULL, 0x9CA9D7F25FA4A497ULL, 0x82E98DFA8908ED81ULL, 
            0xB7362C2574A80058ULL, 0x30F5B1A638189081ULL, 0x4656C4996D15B50EULL, 0x03B66A624D3AAD1AULL, 
            0x96CA1E700174FA6FULL, 0x0AE2FF2FB6CAF4C9ULL, 0x5F04C7ABCC23497CULL, 0x91E724A88EBFA7AEULL, 
            0x5AEB05C2C1D2A02EULL, 0x9C509BA990CF8CE8ULL, 0x6403D088E34A737DULL, 0xF76E1B1EBC4B848AULL, 
            0x97D5AC1452CA0E2AULL, 0x6190CD34E14A8DABULL, 0x8250C2DEF379F0B8ULL, 0xD7D2FB76BDD0EF0FULL, 
            0x8E2DCF09D6C8547CULL, 0x6BDC9C766E883CF9ULL, 0xABE780D720E992D1ULL, 0xB564FCB36D001DE2ULL, 
            0x9FEF4340E6C6C205ULL, 0xB6190F42879FD835ULL, 0xE3909F172CB72563ULL, 0x870C7A14EFBDBBC0ULL, 
            0x40B139EED18F3E94ULL, 0xECAB4036E417E3C4ULL, 0xE31BAE838F8DEF42ULL, 0xA1341DFC5C617C1CULL
        },
        {
            0x71926E9DC3386ACCULL, 0xE1E8573F9F38F9D1ULL, 0x791CE56999F469FDULL, 0x5C158C0525C95C35ULL, 
            0x1D04CBF87B1E29C0ULL, 0x49C275123EE7BF4EULL, 0x7BBC92F1BE942B44ULL, 0x12C921DD7A065C8FULL, 
            0xD66E3E47B5A81919ULL, 0xE46452B7F7774B44ULL, 0x11CD7A128EF0DA9EULL, 0xFE5522D6B360E82FULL, 
            0x53C9657573E8FBB6ULL, 0x29EE488FF0EDBE86ULL, 0x82EFD73FFE58982DULL, 0x42C6B70AB23373EFULL, 
            0x501CA72A314EE775ULL, 0x3252CA45EE6FBB2BULL, 0xB752B5B995061A96ULL, 0xE41BB28B3E8960D5ULL, 
            0xD5CB2FAC80B30781ULL, 0xB6C6D3D0121A27E5ULL, 0x8DC0258499383641ULL, 0x9DF693767AB4D422ULL, 
            0xF6966E742043FCE9ULL, 0xEC357A3C0434B7E0ULL, 0x7571268852FAD361ULL, 0xE41A6507D03F0547ULL, 
            0xAAF450473503D0CCULL, 0x962C4113D11FA809ULL, 0xC52FCB86AFC56936ULL, 0x4A7B152364BD0D75ULL
        },
        {
            0xAB42DF694986036CULL, 0xC7E344C3AA6903FEULL, 0x3426AFB290C5275EULL, 0xBA84C2F75123FA44ULL, 
            0x2A0E0245C5109876ULL, 0xB619F97C4D67F2BDULL, 0x8DF6D575ED752D0FULL, 0x4FFA4824DA72A912ULL, 
            0x9C3E7A7D43D3D9E2ULL, 0xED7C5E1512AD5F9CULL, 0xA47C1D9E7C2D8C11ULL, 0x33A8839A3D623807ULL, 
            0x17A81E030E2711E9ULL, 0x15DADFD7695C0CB1ULL, 0xD8EC9B75AD7410F1ULL, 0x51067D55C6086F45ULL, 
            0x2781B2A0743FD443ULL, 0xC0357998D22DF9FFULL, 0x8BC0C6B33F028015ULL, 0xEC8605E9ABE27A4AULL, 
            0x30DE09486274C027ULL, 0x972F03446295FE21ULL, 0x7E339A152AE440C5ULL, 0x24285C24E1786618ULL, 
            0x643690A434B25DF2ULL, 0x70480833E007C7E9ULL, 0x49508F2E3C648F0BULL, 0x5F1705CBC7443C5BULL, 
            0x7AB5B195BE8DB049ULL, 0xE09085892AED0C75ULL, 0x67FE920025A4D02FULL, 0x21A72BD9F2EB631EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseAConstants = {
    0x341EF9D608C00BE0ULL,
    0x9C26D84A49F41FA3ULL,
    0xCC469D5DCF090122ULL,
    0x341EF9D608C00BE0ULL,
    0x9C26D84A49F41FA3ULL,
    0xCC469D5DCF090122ULL,
    0xDD404A80365F25F9ULL,
    0x2C1FBDCEAD5FB0A4ULL,
    0x3E,
    0x25,
    0x6C,
    0xEB,
    0x81,
    0x32,
    0x72,
    0xBB
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseBSalts = {
    {
        {
            0x168F095AE694D22AULL, 0x7A4DBD01072865CAULL, 0x1B92358186516BDDULL, 0xCEC5E2787FD61320ULL, 
            0x00016F784CCA725FULL, 0x1AC4268F69FB78EDULL, 0x3BC9CEBB24306801ULL, 0xD9FCE66E91386B7DULL, 
            0xF8168536A99BFE12ULL, 0x79A602527B41BD2EULL, 0xB930A0836F4B0A62ULL, 0x0D67AB9A9894BE7FULL, 
            0x6B71EC3EAC42350BULL, 0xA28619052FB9F560ULL, 0x83AC79FA5B5F68A8ULL, 0x3B9B72B3D89FF133ULL, 
            0xB3D0713410EAC59BULL, 0x21BEC99D7808CC41ULL, 0xBABE090D5B241FE4ULL, 0xFA9094F75DA33CE3ULL, 
            0xD8B81BB37DDE5526ULL, 0xFC50DFCA6A5B4B82ULL, 0xF00FA3EF6A2BFA31ULL, 0xEABEF17CA3371E50ULL, 
            0x6619DAC051BD8A5AULL, 0xF692896B40A92F50ULL, 0x793D1D6F4E47F41BULL, 0x66288894EF97D74FULL, 
            0x2614CD7533325DB9ULL, 0x4047250E241A30E1ULL, 0x0294D2488A133AE9ULL, 0x62D2D960DE762DD1ULL
        },
        {
            0x8A292D71C7AEAB72ULL, 0x125DDA027034786AULL, 0x07285E0C9A51D8B8ULL, 0x049DCCD6428B28F0ULL, 
            0x174B360A9C5EBDB5ULL, 0x2BF7A437D7E0AB7BULL, 0x24BED98DA90EFC2DULL, 0x37EEB32760547CF3ULL, 
            0x56B2C3B610285BD0ULL, 0x3FFDEDF7D5CD63BFULL, 0x52D18FB31C71912DULL, 0xB644ADF2F8F5A51AULL, 
            0x292A6FFF1DF1C9A1ULL, 0x3C22DD20AB83B91CULL, 0x7CBFE8EAC47AF82FULL, 0xD802E7B445DFB03CULL, 
            0x92264BC888EC195DULL, 0xD1024BDD13E8F20CULL, 0xD6A0D29BD909DD84ULL, 0x250B79EFF704F142ULL, 
            0xED8E22F8AA497328ULL, 0xAA773F2F5546EDD6ULL, 0xD864AF668778A6B3ULL, 0xD66DD0FEAD6A4086ULL, 
            0x30E47A52E16BF71BULL, 0x1592A500F45F92F9ULL, 0x539D92303C4B154BULL, 0xB4AF28C4EB98BB33ULL, 
            0x2CB533F507F0D54DULL, 0x62ECD853909C0F6BULL, 0x41F979FA0F8F0873ULL, 0xEC28147F9AF8C987ULL
        },
        {
            0xFE1E35F76AF09C5FULL, 0x66CB51C22DF560FAULL, 0x29B2834682B6202AULL, 0x78372D59C42A586CULL, 
            0x5812437C5EC71EDAULL, 0x451CA7E5F3486366ULL, 0x658203962D9FF8DDULL, 0xEA498284041FE0F4ULL, 
            0xAE66036E11D67C56ULL, 0x0F8FA5E1A2816FBDULL, 0x75136D736F0A859CULL, 0x03535D5CDC024512ULL, 
            0x6E6D017783CC86C6ULL, 0x9452D4211DE01C92ULL, 0x69B1F13697E8ADB4ULL, 0xD7982FCE0AC17129ULL, 
            0x61AB3EA216B68E53ULL, 0xD22E80D897FA002DULL, 0xBE4A6C16F91134FBULL, 0x40AEBCD81CFE426CULL, 
            0xB0F5952CC2506D5AULL, 0xD55AA6B83C5B0EABULL, 0x9EC3D63881ABB3A3ULL, 0x1E04B892E7682BADULL, 
            0xC72DC6D2967F071AULL, 0x1408C2DDE16B767EULL, 0x7A4C8A868A7C4C59ULL, 0x404B20714041DCF4ULL, 
            0x9605D6DC0D73393DULL, 0x4AE951EBE6004AFCULL, 0xF59CC1661C1C3EC6ULL, 0x4636BE93D365B26BULL
        },
        {
            0x9B043AEB2021A5A2ULL, 0xC87C46A1F49163CBULL, 0x62BD529DF54E47E1ULL, 0xBADA604F31575A3AULL, 
            0x36A04A5DBC3234E5ULL, 0x58A25A933D17A801ULL, 0xE17F7A0307ADD081ULL, 0x0F475156C34ACB95ULL, 
            0x47DB5E00D0C1D5EDULL, 0x3F7F5D3D81E80F38ULL, 0x4A07D9E349C4C796ULL, 0x7E261A9F9F210618ULL, 
            0xCDE548C83236C44CULL, 0x14DEBECFEF53A41BULL, 0x0A113782DFE2FA0FULL, 0x9E8413C535FAFA6DULL, 
            0xDE8DDF79140B6234ULL, 0xA1CED3E3D8FD1406ULL, 0x152B0720E203ADBBULL, 0x3799757C860B8CC4ULL, 
            0xA6476CF35788383CULL, 0x97035BE5CA961B66ULL, 0x2946E79ED6C8152DULL, 0x0C9B9AD80BE48962ULL, 
            0xAFAF8FE550D5E487ULL, 0x67552E9CF5225776ULL, 0x857787CE1283AA4EULL, 0x7A7ED6AACCBC650EULL, 
            0x6FD276F7D92B65D4ULL, 0xB5DC6EB8B6C4362BULL, 0x7EB9DB836DF6C113ULL, 0xDF9F27506693ED3AULL
        },
        {
            0x8713777880DA0496ULL, 0x109AFBAF02BFDFCFULL, 0xA64142C57E57A143ULL, 0x0D2DA4DB1C5EFB55ULL, 
            0x4DF91D659A175DA1ULL, 0xDAC41AC6F1BCCFA4ULL, 0xE1E4E10FDCE572F3ULL, 0x359CFC74CBEA3AA9ULL, 
            0x4F10B25617D939DFULL, 0xC1476EA52FD51777ULL, 0xE73E3BAA3E1749D2ULL, 0x74F39FA4FE7FC55AULL, 
            0xAE8A337458B3942DULL, 0x7E0B22D78F2765D7ULL, 0x5381A457F72B6C22ULL, 0x0D5C1DD4695E4EFCULL, 
            0xB4B88A70C96CB1E9ULL, 0x3772791BBD2C4CE9ULL, 0xA5DE8F1CDA03109CULL, 0xABFFE43898D4993DULL, 
            0x9E1AB85B062FF76AULL, 0xE55542AC674C5577ULL, 0x35068C51D13BC0BCULL, 0xD752032C23BEC54AULL, 
            0xACFF1639E78B4877ULL, 0xC51EE80A905DB4D0ULL, 0x6C6CA64267699129ULL, 0x9BA46C1C2255ADE1ULL, 
            0x385A3C7C94FB74ADULL, 0x8CA2442BE4DAF0EDULL, 0x0092AF88C6E19A61ULL, 0x18AD16575C24CE06ULL
        },
        {
            0xD4E04CE9AC6A9578ULL, 0xBACBBD0B72DC51D7ULL, 0x6075690508C371EBULL, 0xE0B4639C4223E7D2ULL, 
            0x2AB70344FF82035BULL, 0xF3789825C59B6A31ULL, 0x990E12B4380B8D07ULL, 0xA1799A3C8C2CEC78ULL, 
            0xFB926FD9BC77753AULL, 0xC9ACDF0909670093ULL, 0x0387CC7B668CE4FCULL, 0x6791BED6FE94768CULL, 
            0xD7EB2F928DB79724ULL, 0x727D2F684AC4AA5EULL, 0x51D86DF809C72899ULL, 0x5E717D083298CA4CULL, 
            0x181DEBCE33028D82ULL, 0xFFB1814B8D0F7B43ULL, 0xB1840D1CD0BB297DULL, 0x602EFF9EEBC24CDFULL, 
            0x38BE440B20801F95ULL, 0x286749740D30BBA9ULL, 0xDCB127553461002DULL, 0x85E22004AD6C10F8ULL, 
            0x9EA4485EF6A95F46ULL, 0x3A363003ECDE0D9DULL, 0x50D3728828815CD9ULL, 0x86A03A7663EF36E2ULL, 
            0xE3ECC00932C002F5ULL, 0xBAAD63CC670C30BCULL, 0xC6073D43421259F3ULL, 0xE0BB2396E80D4B78ULL
        }
    },
    {
        {
            0x6A01450053FAB79AULL, 0x61090EB0C6B2C032ULL, 0xFE4403EA40E423EAULL, 0xF5ACA5D6231F091DULL, 
            0xB12C295B64757FEAULL, 0x575BA4F69618DBE2ULL, 0xE46B5CB54122CC20ULL, 0xD36676CE9BC0F4FFULL, 
            0xCC495CA5AF04AF17ULL, 0x15B8ADD55E32C823ULL, 0x3175E51D1873668AULL, 0x5E7A694BAE293E4EULL, 
            0xF142AEAFF33525B0ULL, 0x75B89E7BB8DEFB15ULL, 0xD69BCF46FC1BE919ULL, 0xE3667608AAEF2323ULL, 
            0x4D2A29605BD029ABULL, 0x0DD0221E687518F6ULL, 0xAF62FAC561C122ECULL, 0x1821A3D5796ACA3FULL, 
            0x506F20ADC6056FE2ULL, 0x4041E9C27CFD2811ULL, 0x555DEFDA26BB8FBBULL, 0xDD01E0C82D23FBF0ULL, 
            0x32EF14BD1227161FULL, 0xAE5E340D1FB81CE6ULL, 0x97E05007D1DF3580ULL, 0x6E300A240FD730C1ULL, 
            0x6D975BBC8CA8E2B4ULL, 0x891BD640F892B32FULL, 0x4295A3013D60B11CULL, 0x40F8410DF2C5CA19ULL
        },
        {
            0x21FE60E8D474ED97ULL, 0x61B9FDDDAE91DE2BULL, 0xC12D9DAD084BFE08ULL, 0x9F9005D75B0A812DULL, 
            0x2D2E74A017E6ED9CULL, 0xBDC5D555B8A9D557ULL, 0xC4B48AED63F7CABCULL, 0x55273746351D9CF7ULL, 
            0x6FD8D29913E3DD27ULL, 0x5EC3F9CFF79B919FULL, 0x7FD8B3B6C864CDDEULL, 0x5CD10871ED6DDE6DULL, 
            0x784892EA8DBEE74DULL, 0x115698A4DEF7B3A8ULL, 0x86A0CDB6206B1A60ULL, 0x18393D246974ADB6ULL, 
            0xD7C489613DFD23C4ULL, 0x0F2F764F84F86691ULL, 0xE91A55FA54925511ULL, 0xDB067B177EC837B1ULL, 
            0x70FE8BD35FD3D4E4ULL, 0xFFF9072B5E749715ULL, 0x48D3C2FCB1431F18ULL, 0xB385AF8172316573ULL, 
            0x56EBC5FDC0975596ULL, 0x4DD6CC52B2C20B37ULL, 0xFECBD4FA6A618DD3ULL, 0xE5F83FECE6251B8CULL, 
            0x405DB9C752B328B1ULL, 0x725FBEB306019BBFULL, 0x36844B58AB0900FDULL, 0x344B4574F4F81FE9ULL
        },
        {
            0xF89173F0D04A7142ULL, 0x8EE4054DCEF03C7CULL, 0x6F13A6AFDD7A1EFFULL, 0xDE512220A8665C37ULL, 
            0xEB5D6EB6D459AFD4ULL, 0x15090235DC54A254ULL, 0x28268F42FC1E2914ULL, 0x633AF9E795B65E0EULL, 
            0xBBE99F80F6D71E6EULL, 0x61156F0F68F8CBD0ULL, 0xA48728B53D4CE58EULL, 0x3C40CDD5DEBD0D84ULL, 
            0x6AD0CB114BFBABCCULL, 0x0D335C5385306C9DULL, 0x4005B13C8E138A2EULL, 0xCEDE3AEA429B9E3AULL, 
            0xD7FFF0D0D6276969ULL, 0xFDB8458F6EF01B6AULL, 0x53BF8632B552D7DEULL, 0xF7BBEFE9E8C80A65ULL, 
            0x1061502494E1C767ULL, 0xD2C72CB192FF9576ULL, 0x25F9FD4A694AEC11ULL, 0x3CED9896C37636FCULL, 
            0x86723CA3C1763CABULL, 0xC122955EEB3F54AEULL, 0xEE96C49A6EAE05EEULL, 0xD92A40AE9E77F59AULL, 
            0xE2A05852B9F880B6ULL, 0x613383E789C8361CULL, 0xBD70E577E2843EC6ULL, 0x240C8FA9BAC29130ULL
        },
        {
            0x45F62CFD91BC5B26ULL, 0x5F84D93838D3B61AULL, 0x5B6D58B940FFB836ULL, 0x95C75C6313F29531ULL, 
            0x9C056A91F95A5C72ULL, 0xCDC39C47E50A28FBULL, 0xC85ABD99E49EA517ULL, 0x74997F6DFF3F26CDULL, 
            0xD441018E5F17BAF7ULL, 0xC1AA6BE631B81ED3ULL, 0x92BD33853E0C376CULL, 0x6CD8CEBAFA1FBF35ULL, 
            0xF2D236F2A397F3ACULL, 0xB0FBA6925E47BB6FULL, 0xE50861EE3D798331ULL, 0x3EAFCE928AE9BF49ULL, 
            0x21EC48CA7003DBE7ULL, 0xF3F3436287E29ABEULL, 0x9E9F29605504A7B5ULL, 0x71705D2AFACFD5FAULL, 
            0xDFB0C360AD196D74ULL, 0x93EB6699F8B8ADF8ULL, 0x533664B27B9E137FULL, 0x134836B4BA7DFEDEULL, 
            0x4571C1C708BDD192ULL, 0x1CBCAA7318BDA632ULL, 0xD6919B17DA7F0B47ULL, 0x772645273E345956ULL, 
            0x2FEC00EBE15E4495ULL, 0x20347DA7456D5F9DULL, 0x3658DD43F33B78E1ULL, 0xFB38FB997A5CDE96ULL
        },
        {
            0x20664C4D5C07E465ULL, 0xA12AC6484EC16453ULL, 0xF80A900ACDF10784ULL, 0x76D13F41103E50CEULL, 
            0x8265250374D0FF58ULL, 0xFFD46341B8E2D5E2ULL, 0x6A78E97BC5F08692ULL, 0xB860D739C41C2E99ULL, 
            0x4A4B046CF7B03DCBULL, 0x91913C8C5BED678FULL, 0xFE986C7DE78CAD75ULL, 0xEB6566F330693F9DULL, 
            0xC93EAA2D6A8F5970ULL, 0x6000D932E92077B8ULL, 0x90EEA843D16271C9ULL, 0x194EA41EC0CB8DB6ULL, 
            0x3A02958554553781ULL, 0xF83E1A97767309E9ULL, 0xAC907A3688AB7B52ULL, 0x588FD4AEC47BE0B3ULL, 
            0x230A23DD50A45011ULL, 0x28AF9483F21B4137ULL, 0xC7EA8C408A3B5985ULL, 0xAAF130DFA1089966ULL, 
            0x46978C39363FFA7FULL, 0xDC005A0FA7CC1FE6ULL, 0x3461B5C3C19D9B9CULL, 0x9320967ED3C9D226ULL, 
            0x97D8F0348D13083BULL, 0xC69BAF1DA1CF2140ULL, 0xD76BFBDB84CACC89ULL, 0xAF311E6EC0728500ULL
        },
        {
            0x874E59DACF6120B0ULL, 0x01D1996E468A0ADFULL, 0x6862FE590A50401CULL, 0x6ED554783FC79B5DULL, 
            0xD05B3C4B6C53F5F3ULL, 0x3C84637B11A61755ULL, 0xEC42CD2CECF03873ULL, 0xC294B09412F5D57AULL, 
            0xF9CD2928EB3B473EULL, 0xE1BF4114F6E4FBA5ULL, 0xC050EB4F4DD95884ULL, 0x85F87DCE34492E7EULL, 
            0x2A3394EF67555FE2ULL, 0x7022ABC0089AB662ULL, 0x3E255DD1911549D9ULL, 0xCDC355C8C7EAE913ULL, 
            0x5DB4CFA817FB652AULL, 0x586ED935FFBCCA3AULL, 0x3B381FFB3F8AC38DULL, 0xA0D3470712895124ULL, 
            0x6F73DFBD52DBED39ULL, 0xA816B56A1AFDBDEEULL, 0x541C6BCA3CABFA43ULL, 0xA57FC1D63F5BAC8CULL, 
            0x61B6CCC898370F8DULL, 0xB039A00D7278F6FFULL, 0x1707C4F4F4DD5CC1ULL, 0x93C4FFB3E610186FULL, 
            0xB57A6DA1DA4C7C3AULL, 0xBDEFE1E67506541DULL, 0x6AEAE4F2BF4FEDA9ULL, 0xB53D368B5DD3C655ULL
        }
    },
    {
        {
            0x54240E57ADCD9133ULL, 0x8F93F7A0212DDA42ULL, 0xC3CBCA3A29524427ULL, 0xE32ACFF77B511B42ULL, 
            0x2BB7C69C5BB97AE8ULL, 0xE0EE59D470287EF5ULL, 0x9328FFBC1EA87D87ULL, 0x934DEA7A222E481EULL, 
            0x28958DC5540FB150ULL, 0xB6902F19697D49BBULL, 0x35D648A486C2D914ULL, 0x073E794E55A4E3B3ULL, 
            0x7FF9CE6729EBDD45ULL, 0xCD9F93B6E3D22329ULL, 0xAA103A9BE19E3BD2ULL, 0x1001B4EEF3F65A80ULL, 
            0x823AFD3054EB951AULL, 0xB1E5AA9F97DA7F4EULL, 0xA452F9C4129A5918ULL, 0x3CFE1184E42DC6D8ULL, 
            0x656857AA57AA2D6DULL, 0x0014FA7EF42D6D8DULL, 0xD14CB25A15EB9572ULL, 0xCF7B0C6076811667ULL, 
            0xD077A33AF40F1ADEULL, 0xF11ED616153A1FAFULL, 0x25B4F08EC91A9D2EULL, 0x64025CA2D57AFEE2ULL, 
            0x87BCD8023D9B69BAULL, 0xB4D3DF37BD0233CAULL, 0x7C371E83B749C99BULL, 0xAFA3DE4DF3DB6A40ULL
        },
        {
            0x9207564BA13A8E46ULL, 0x79DBFB28AAD25A48ULL, 0x4A48901C442AEB01ULL, 0x43CE12FBFDBAF0E7ULL, 
            0x80F546B23F89E6FEULL, 0x61538F8F2B2D138CULL, 0x8AD21B3FCDDFCEC9ULL, 0x3CD37E357F32C9A8ULL, 
            0x8ABA65DEC93C5D0CULL, 0x8F65F4C8A6F498D2ULL, 0xB69E37272737F5DFULL, 0x73F6F6EC21C36285ULL, 
            0x12DB4323A8A5D1B1ULL, 0x6688E0D17D8D75CCULL, 0xD1358A9EBE8F4B96ULL, 0x2AA03604E652DC43ULL, 
            0x6CD7C21D83C4C374ULL, 0x90D50E5DB5FA7150ULL, 0x670C74BA095D1FDDULL, 0xB76E87D285B677F0ULL, 
            0xB73043ED85EC1320ULL, 0xBB1E080267E645E2ULL, 0xB7C5F2E8C9D11897ULL, 0xE2AEC4C5D94A875EULL, 
            0x0C18C6C206B44407ULL, 0x4B26B9B5D38C16F3ULL, 0x77C956F27711F99BULL, 0x6972B7C23735CE34ULL, 
            0x188C7565B7EC4DA5ULL, 0x031D04AD53F979D6ULL, 0x64F74F2DAA2E6660ULL, 0x51089BBCDA682AD8ULL
        },
        {
            0x0114E5B05FAD7005ULL, 0x1CE90E00FADD90E1ULL, 0xF43C2AEADD85595EULL, 0x6F5280BF8C6136A0ULL, 
            0x2037ABF4656D684CULL, 0xE0924C46C9160DBCULL, 0xE2F9116919FB5020ULL, 0x49C2DEB29E5F1EABULL, 
            0x8C64CFE9F22DF883ULL, 0x310E3ACA587BC7CDULL, 0x4FB3D88A1AF5B7C6ULL, 0x981C3719CFA0489FULL, 
            0x1E5FBBA447A3E51EULL, 0x5BF2CC5258958663ULL, 0x691948BF08720A04ULL, 0xDBF9F431196D2623ULL, 
            0x3372295AF92264CEULL, 0xBCABAAD4FB8BD1BCULL, 0x46B45912A592FA1EULL, 0x0420CE5EDA4CB2B8ULL, 
            0x189935CD1F1C2D83ULL, 0x3849958F58D8839BULL, 0xEAC528EE6487C40FULL, 0x161A8569E5EFF5F6ULL, 
            0x9B6252094DF57141ULL, 0x31C713E6E54AE54DULL, 0xD99087B494E65DBDULL, 0x225E5C800F042466ULL, 
            0xAAC61D659B02A9EFULL, 0x650D02856AC7DB8DULL, 0xC64835D21149D6FAULL, 0x7E58454AA5858EFBULL
        },
        {
            0x19DB365FF5B85CF9ULL, 0xD322E81CB6B16CDFULL, 0x582A012A53C6BB27ULL, 0xAB2AE5E7B4452E4EULL, 
            0x7665F6A73AA5ADA9ULL, 0x842B61F6EDB8B3A9ULL, 0x699198ACF4D7A9D8ULL, 0xC30587FF6ECCB89BULL, 
            0x36D37172FE571577ULL, 0x7DB1D581C47677C0ULL, 0xA0A45053797764DCULL, 0x0B0BA9F8CA2EF24BULL, 
            0xE244A80BBB30108EULL, 0x8E78295E5FA04B4FULL, 0xCA56323963FAEBA6ULL, 0xB4FA89E760E997C1ULL, 
            0x25996D39A0FCDBD8ULL, 0xFF0DAD969519AEB6ULL, 0x4A67BCCA18E59077ULL, 0xA460ED0591F2C7BFULL, 
            0xC5D611C657D0834DULL, 0xBEAC9B80ACA4E822ULL, 0xA23186FCD3A313E1ULL, 0x73E6459DE4B8F82EULL, 
            0x4065E1C0E4D87A96ULL, 0x00AE6B07D8319D7AULL, 0xFCAF438D522F3E03ULL, 0x660F543141771F29ULL, 
            0x1DE4F74FA2A83BC0ULL, 0xBCADDFEC0E977AA9ULL, 0xE3C1690F02BF0E9DULL, 0x82C793C59AB40A8CULL
        },
        {
            0xB743B665A131433EULL, 0x0327BF8DAA942A82ULL, 0x0EC39F082CC9E946ULL, 0x693C0C38822F1FE1ULL, 
            0x8CE6AEBE39424EE0ULL, 0xF42CDB9570A6BCDDULL, 0x7DA7C4BBD288A6A7ULL, 0x5875BB23A46EEAD7ULL, 
            0xFCBFD693F9FD735DULL, 0x398B298B275899F0ULL, 0xEC75E5FD2D412680ULL, 0x277E4389C54A28EDULL, 
            0x6C991B7D82B60DA9ULL, 0x9BE39F52CB724EF3ULL, 0x82C91DCCD34B9AD3ULL, 0xE0FAA0BA57B5E1F9ULL, 
            0x252029269A5D2ED0ULL, 0x053AC4DAB40B2DE5ULL, 0xC14F0A73469E0014ULL, 0x2BC867F0C5B0B02CULL, 
            0x398D78F3B0FA8798ULL, 0x2973F510F6EE4FA7ULL, 0xAFB2236737F93BC9ULL, 0x985DC750C1767583ULL, 
            0x830576B71B13A734ULL, 0x422A972A896895DEULL, 0xC34F58A68FFF7189ULL, 0x76336B58EE69C12EULL, 
            0x323C099F5C35F73FULL, 0x7D11E43A030877E4ULL, 0x3509CF046FE18214ULL, 0xC3B2CB4AB49B813AULL
        },
        {
            0xD9B3E290AB70DB9DULL, 0x1C1639ABA2D0B39EULL, 0x15750DFCFABA04E6ULL, 0xC19D470073A3FF39ULL, 
            0xFC10FFC3115F806CULL, 0xA558051D5C8CB889ULL, 0xA5C2B505BCD1B6A1ULL, 0x5FC9AB5CD569BF73ULL, 
            0xB1EFD400B9CD98A0ULL, 0xF1729BE5D1CD65D4ULL, 0xE0B9492DC4FAD45DULL, 0x2307AC4DA9816BE0ULL, 
            0xEED5E5AAD6DF902DULL, 0xC7B2F477321FDAE0ULL, 0x811D7654DF0623FCULL, 0x9D5B0648D334AE71ULL, 
            0x6A064D70215CC554ULL, 0x7663009BE8F7BD38ULL, 0x658D90F31CAE47ACULL, 0x179175EE3C2D7612ULL, 
            0x098C1BEACCCBBFBDULL, 0x260E75F92B518DE4ULL, 0xF1928016B7167839ULL, 0xCA98E91100EEDB3DULL, 
            0x9F95A428B7BB135DULL, 0xB43CFC0808FF6922ULL, 0x073A35F6E5CA6800ULL, 0xBD1FEEF45FC5CA96ULL, 
            0x9AFE5CE9D32E0836ULL, 0x4440B698A1E15BAEULL, 0x0D15FAF184B132DDULL, 0x04A733416FE885AFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseBConstants = {
    0x0F0C1325836BEA78ULL,
    0xCFF07AB83D7B9193ULL,
    0xAE1EB79AA13ADBD9ULL,
    0x0F0C1325836BEA78ULL,
    0xCFF07AB83D7B9193ULL,
    0xAE1EB79AA13ADBD9ULL,
    0x4872A3CAF11638AAULL,
    0x28473EC66BE22E71ULL,
    0xE9,
    0xD7,
    0xC6,
    0xD7,
    0x24,
    0x10,
    0x0F,
    0x4F
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseCSalts = {
    {
        {
            0x8AFE1FB3FC99DCE4ULL, 0xEF6A99BB2A014533ULL, 0x678057FF463C3598ULL, 0xFB5C252DD25DE3D6ULL, 
            0xCC4464A7BB77077CULL, 0x29E2BFB724FAEAD7ULL, 0x3B04272DD1EBAA85ULL, 0xB23808DA1C5B8773ULL, 
            0x81D79247ED2A706BULL, 0x74EBBAE6D102601FULL, 0xAA9CB6A887FE7E6AULL, 0x57E3633D06F05F4BULL, 
            0x7AF28E0F2B0185ABULL, 0x9DF86133C11B5D07ULL, 0x9721A8ADC97D78A7ULL, 0xB20425EDA1CA9E39ULL, 
            0x6FDA1017827F03EAULL, 0x99F023667B86A033ULL, 0xA351BC34E7AE6FC7ULL, 0x05E7C3454A8EB44AULL, 
            0x4FB9E2AF0AA8ADFEULL, 0x797C7A262EE8EF76ULL, 0xF652BD57F1F2D920ULL, 0x3B61C03717F56663ULL, 
            0xAB56979207713757ULL, 0x92E48BE127D07147ULL, 0x9D3F69212A41979FULL, 0xF7F6B7D4467F2A86ULL, 
            0xE788D448FE53A3F8ULL, 0x0FE9F9CC6550E459ULL, 0x00F74113EF80980EULL, 0x13B0A0F60F2C5101ULL
        },
        {
            0x46661A3CAEF6C7A0ULL, 0x64BA8BE578616B3EULL, 0x832AF088CD90E2D7ULL, 0x4832901B9366D0B9ULL, 
            0x716195BFB40063F2ULL, 0x7AC1C77EF6C6D4B3ULL, 0xBFDBF5F10A0CE334ULL, 0x514B649ACA5C3DD8ULL, 
            0x9F253452CA747E2DULL, 0xCA9A4A2730BE687BULL, 0xCCDB327491CDCC48ULL, 0x399B92804D6B8390ULL, 
            0x80954BE6F57AF601ULL, 0x38E86F8175A7734DULL, 0xF55801A346B508FCULL, 0xCC58ED88750EA50FULL, 
            0xCF51825A77A8ADE0ULL, 0xEDF596730736CA49ULL, 0x95900F426AC53C81ULL, 0x21C44E066884F78EULL, 
            0x09B1A1D4DA3C26BDULL, 0xFBE20A53ADB97ABBULL, 0x1E5F08FE106BB2F9ULL, 0xF31C3E6B596C239DULL, 
            0x21747C0FEA22D9ACULL, 0x76C6D9140AC2E5EDULL, 0x7A0A4DD33EEEEFD3ULL, 0x532E1989A89381C4ULL, 
            0xF489C292EBF99768ULL, 0xE204535ADE92C4F1ULL, 0x60B7F95546297118ULL, 0x215AEC75803E3AC9ULL
        },
        {
            0x8467C6AD4F4CB8AFULL, 0x2850B8B9F44BBB24ULL, 0xF0E0B369B6D530FFULL, 0x117C1C7BA570835AULL, 
            0x837BB34BC4F9E3E8ULL, 0x869FDF945064DB13ULL, 0xA179B285FF8C343EULL, 0xDC8EEF63B9739334ULL, 
            0x11059E2ED28BCF96ULL, 0xB020EA6CFA1F48ECULL, 0xDBA4FE95339FCF79ULL, 0xD80EFEDFC2E994DCULL, 
            0x2659BD87D1E543B7ULL, 0x7384CCA435C78226ULL, 0x877E04656E56C3C3ULL, 0x9323165DCAC0B17CULL, 
            0xE8C14A90C182CEA7ULL, 0xCD061AC94180047BULL, 0x6557ABF7BE0C7EB5ULL, 0x86429B5016DCEF05ULL, 
            0x04C3E1037613035CULL, 0xBD1ED46FB330CAD9ULL, 0x046FA113D74821D4ULL, 0xBCD9C5E13716423CULL, 
            0x9AD48F0717916207ULL, 0xA89DC85A9B7FC43AULL, 0xAC870BBE822A2290ULL, 0x3E21DA05C7B1049AULL, 
            0x3580AC630CB71BFFULL, 0xBD553B4DAF55C1DDULL, 0x12E03F112AEEA2C0ULL, 0x08E3ACFE5AF169D2ULL
        },
        {
            0x67E83AD5DC28654FULL, 0xBD4B2D6CC7BD46B3ULL, 0xFEFCF445E0765612ULL, 0x89DB358A01A00D4FULL, 
            0x03B4A26193F0F76FULL, 0x670C16BAD2C8D9D4ULL, 0x848DA566356D4C7DULL, 0x55837419D8861089ULL, 
            0x7842664A08729422ULL, 0x7CD17CF6E8DAEBCFULL, 0x19982438EA0953E0ULL, 0x28EEBBFCBDF80B81ULL, 
            0xCD81E5E44E418F04ULL, 0x1C4F1D7C1D4AE8CBULL, 0x80DAC269A4503FECULL, 0x67C5D266C4F7612AULL, 
            0x755BBBA21809CA2FULL, 0x4A4EC51DAE9B0544ULL, 0x275D7E0285D79EAEULL, 0xCBBB363D6B45E454ULL, 
            0xBEC97EAF2DDDBF4DULL, 0xC303F94D034FB6C2ULL, 0xDC9FD7EECD67269EULL, 0x0BC466B502617867ULL, 
            0x2BCDCB53E3EE7E20ULL, 0x85E82B40CD927CE9ULL, 0xBE65EC77418F7715ULL, 0x37299BC49422ECEDULL, 
            0x66572500B028F4BDULL, 0xDA0E73236794A582ULL, 0x31154E366EA7A094ULL, 0x005BDCCE7F48F850ULL
        },
        {
            0xF2B330162E6D4518ULL, 0x2611224A681D205BULL, 0x437A97D4833E5E24ULL, 0x32B3D47CBF86C3FBULL, 
            0x05C562586C207296ULL, 0x8E83E2EAF9C57F4DULL, 0xB2D39DFA59EACAD3ULL, 0x0F9E97C95883BDFAULL, 
            0x45F37F2748DED188ULL, 0xCF379877702D9F02ULL, 0x6BDD960D4283E910ULL, 0xA79E6C9E491D0DDFULL, 
            0x7B07BCA55F90E4F2ULL, 0xC8277674B49D87D4ULL, 0xAA0778AD01F8382BULL, 0xE9A10B1F302F1E11ULL, 
            0x8B2006E296D109D3ULL, 0x860046820272BB70ULL, 0xD4D62C06BB36370AULL, 0x651A060218D8AC18ULL, 
            0xF0BC48B824E8116BULL, 0x806EBA7E3DED2AE9ULL, 0x9B38910564A711CDULL, 0xE29B7DD762D181D5ULL, 
            0x678E825F43033F24ULL, 0xDF8D0BE7593C8554ULL, 0x83545D93BCBB8FDCULL, 0x564867EBD779AFA9ULL, 
            0xB32178B517B345CCULL, 0x2690EE66DA0CA883ULL, 0xA077111357715850ULL, 0x801B3CC548F7A160ULL
        },
        {
            0xB97434565201CA83ULL, 0xD4B0DBEAA6702352ULL, 0xD0959B9B0649B1B5ULL, 0x9230C46B93F0CF12ULL, 
            0x482EA31C083015AFULL, 0x58D58F736AAC22FFULL, 0x4C4C77C1C36E8A7FULL, 0xE19A88355E934A94ULL, 
            0x94DE939832B274D7ULL, 0x61BF15BA22491B96ULL, 0x2F4443B7AF103ED0ULL, 0x9D3F345603B4F5F1ULL, 
            0x91B207489EF21CE6ULL, 0xAEF0F3D5004E802BULL, 0x44BC8B379A56F124ULL, 0x60B245B1411476DCULL, 
            0x339C01B3A4D5E1AAULL, 0xD3F1FF609F049DC3ULL, 0xEEC91A8147B9FBD8ULL, 0x21D09F3665C320FFULL, 
            0xFB96EEBCDD63EBB4ULL, 0xCA149DEA71D6894AULL, 0x28CE4CB33D8A96CEULL, 0x6F7C9056ACAD43CCULL, 
            0x898452943018546AULL, 0xD794C5221E601DADULL, 0x07435DDAD2E2FA51ULL, 0x4B4C1D916352F83AULL, 
            0x78E473B06AF206F8ULL, 0x61A83497931DF198ULL, 0x96296DEDF43D97BCULL, 0x60860DE9EAC05801ULL
        }
    },
    {
        {
            0x6782DDC7C5D6DAE0ULL, 0xB7B0EBFEA378D2B7ULL, 0x0EDED9F8380B1E46ULL, 0xAC70CE83D32F5CBDULL, 
            0x07F8235FEA07379DULL, 0x78235876A5173741ULL, 0xA524BF106A8AAFF7ULL, 0x1FF2D249E41C1DDAULL, 
            0xE676E04FAE639F11ULL, 0xCF5040C2157BC466ULL, 0x583A9125C2488784ULL, 0x6472F29D335F2680ULL, 
            0xF29309D9094FE13AULL, 0x612B17605CBC2781ULL, 0x5C14D20D0EE94DECULL, 0x4ADBEE1513010F52ULL, 
            0xEDD794107E3179ECULL, 0x54FA6014A021F5B9ULL, 0x411797EC9BB8B645ULL, 0x7D572820E773324EULL, 
            0x3DEEFA6B4F61BAFCULL, 0x9C35C1556CBCC60CULL, 0xAD048123CCDCFD4EULL, 0x1CAC822DA42CF0FCULL, 
            0x5A2CAB3949485AE0ULL, 0xFC20D95CB70B4705ULL, 0x768B8FF72CA4DA26ULL, 0xCEB16CEEF0F8E655ULL, 
            0xCE5AE97D2D8B31ACULL, 0x05251D9D31DA5CB5ULL, 0x102B25E9EF776CFCULL, 0x3CD9EC27ACDC86DDULL
        },
        {
            0x45D6A624D4B1072DULL, 0x7C3C60ADDFE86034ULL, 0xD162E5495DA7EF23ULL, 0xC36A5F8431CCC5A6ULL, 
            0x00A8689DE5FFFB9EULL, 0x5FC22A74EE2E32FFULL, 0xDBA17CCB25F32489ULL, 0x829BC8453111A5EEULL, 
            0xB513EF349F1B030CULL, 0x9D5F4BDE372B5DE5ULL, 0xDED125D92EE08A91ULL, 0x0435DC24AC39FE67ULL, 
            0x2BDE064A65457BD0ULL, 0xE6730052920FF938ULL, 0x27D8F9C881CC003CULL, 0x67D7118279590EA4ULL, 
            0xD8FD01545D54DA4DULL, 0x2207180C126BE8A5ULL, 0x2E2393FB9A5D9B58ULL, 0x778B1A1A145EDC9DULL, 
            0x8F38501B149990C1ULL, 0x3372C498C51E5A90ULL, 0x280A0F0CC43153DDULL, 0x0401BCFD270C78A7ULL, 
            0x46707F0D3E641852ULL, 0x0DB17C50C24D67F8ULL, 0x6AEF85A72892FEAEULL, 0xA2CA3E82C0669E91ULL, 
            0xEFEA99F3BBA25306ULL, 0xCB5163BA7D341850ULL, 0x05B6B180CDEDACC6ULL, 0x645D401D7BBF0CE7ULL
        },
        {
            0xE24A6254594F714EULL, 0x5B9B9E13739A78C5ULL, 0xAFA8A87779A25193ULL, 0x25510397098AFBC4ULL, 
            0x77B35D52CA48DEB4ULL, 0xFD3DBFDAEEAA3230ULL, 0x339E7029616094A7ULL, 0x4D9304B3FF9AA59EULL, 
            0x8375B2E044F3034DULL, 0x959FA23FB6C63E19ULL, 0x055AAED345817F7DULL, 0xE9933AE411B2605DULL, 
            0xA713F0E7652B692CULL, 0xDFC8844580A0D8BCULL, 0x9EB9ACD34FD2535BULL, 0x3CF6A09D71692559ULL, 
            0xB6626BC6D4325505ULL, 0x287B16E75C4DCA82ULL, 0xDF6C6A9BF1697CF6ULL, 0x8A7250338639F507ULL, 
            0x2FB6B07E7EF027C2ULL, 0xAAD8A075C5DF8D7FULL, 0x1DA342387B8D3094ULL, 0xFB69FACB27BE21DEULL, 
            0xFE3A789498D41EDBULL, 0xD7583D109B8504B2ULL, 0xF6A1DE6EB3F28927ULL, 0xA64DEEE65B3A5180ULL, 
            0xDA3111972DF3E9C7ULL, 0x5B88171EFAE8CEABULL, 0x5A2E6012218B6D33ULL, 0x86F62E30757C3F90ULL
        },
        {
            0x4471EF46011ABC2FULL, 0x3FBE83BE54597EE5ULL, 0x64A4986F5276DEABULL, 0x9B1FDADDB6FA8C5FULL, 
            0x3758387DFED12198ULL, 0x2C315266D7253B22ULL, 0x940D3A71A63924B4ULL, 0x6C180C78D19554B8ULL, 
            0x8B612EA07E6A5D2EULL, 0x35D005E2571D3A50ULL, 0xDC72F7C2F7EF9E45ULL, 0xDE8728B5A03CB543ULL, 
            0x4217D06F74CF2C34ULL, 0x21D7B16B1F281BDAULL, 0x0EBC02CB14A7C836ULL, 0x83AA5B32EA605628ULL, 
            0x5C9E7CC8A848FE21ULL, 0x7E8C14F6766C01C6ULL, 0x9D68BBBE2868B0A8ULL, 0xEB4B56A2B0FE8A7FULL, 
            0x2CB0AAEE844789E9ULL, 0x2E00BAF95419AC45ULL, 0x739B2F0913A37F5AULL, 0x0FEE837E4B40187CULL, 
            0x09874DAA038E3DF3ULL, 0x08C995EF4E631AEFULL, 0xCB027C289A6C4079ULL, 0xE258BE785B122647ULL, 
            0x7D22E546B6C3D472ULL, 0xB7EF81A59BEDADBCULL, 0x3FFDD421AC285A79ULL, 0x81BCE9DE8DD50995ULL
        },
        {
            0xA2A3043FAAE2663BULL, 0x70F97A589C29FB73ULL, 0x4373CA83145D4E65ULL, 0x1B66651CF0E8A8E8ULL, 
            0x27BB258FA30D90F7ULL, 0x41245A9B53C90B9FULL, 0x7AB52D7F9C203773ULL, 0x3D79A906F1CF21CDULL, 
            0xA1B462DF0568B6C9ULL, 0x5F5E117D30B2768BULL, 0xCD46F68C59DF0CF3ULL, 0xE2FC0E2F5F17606BULL, 
            0xF6BD557BE135A02EULL, 0x7D869C02BB6C277AULL, 0x4B356EB753F03529ULL, 0x4AA5EE8CD9D61878ULL, 
            0x7152A1F0BB763F96ULL, 0xF602F7B0F835B387ULL, 0xF9F14091D5B957E0ULL, 0xEC70E421D0EF000BULL, 
            0xC9B7392821802070ULL, 0xDBA0397EB467AEE2ULL, 0xA5A9BCEF62A0F42DULL, 0xCB860D06E6A94F1DULL, 
            0xF846DBA57761C6DEULL, 0x2707A2998320C2DEULL, 0xCC16571230D1839FULL, 0x09D6FD9A236B17D5ULL, 
            0x2098DFBC5087D034ULL, 0x1B00A6B0FF94E16AULL, 0x12A945604C90B4BAULL, 0x215DDAB43B5AA554ULL
        },
        {
            0x14C4E2DCD8639126ULL, 0x16551B19916D3E32ULL, 0x69F10E925384D0C7ULL, 0x3E3A1BA178139270ULL, 
            0xE9767E566588DF51ULL, 0x873DBB99E7FF5D83ULL, 0x1622C1889D00883CULL, 0xD27E8E2F7059CAE0ULL, 
            0x5C3F5641F30C13B7ULL, 0xE07A71843D3D7B64ULL, 0x25F714A630D193F6ULL, 0x76A765356014D2E4ULL, 
            0xB647AEB6EF763C2AULL, 0x43844A10C4AF0B4CULL, 0x24EBC35A428D9224ULL, 0x393CAD37ADF9750FULL, 
            0xFF2F626002067BF4ULL, 0x241EDF92486A25F2ULL, 0xF4C6D36BC6505782ULL, 0x1849AB4709D66A1BULL, 
            0x840AFE763975DB14ULL, 0x375FBD284AFB9B3BULL, 0x5457D0481099C3A3ULL, 0x8D88E21A6102851CULL, 
            0xED3BDF21BD89C28DULL, 0x579F7E2CED9D66AFULL, 0xB2DE3FD23F73EC0EULL, 0x17EB8A31C038940FULL, 
            0x6FEA2437DBFB5C30ULL, 0xE25F1ADC2EE5EA78ULL, 0x9395BE7D66CEEA22ULL, 0x3E355C2360AA224FULL
        }
    },
    {
        {
            0x7870D677EB372236ULL, 0x75855D2A134851F8ULL, 0x7C081E140F670D7DULL, 0x167EE25B077EFEAFULL, 
            0x15A578B90143F4F4ULL, 0x06483EC29E372D73ULL, 0xF07B55FCC5B6BDDBULL, 0x2A39A84142597660ULL, 
            0x2F180767E7C598A1ULL, 0x16DA96E733D0B01EULL, 0x2E34BCB90578CA9BULL, 0xACBB900AEFD1B34FULL, 
            0xDE7A9C00E0215764ULL, 0x22D0F29E9AEC1517ULL, 0x23AAF98C7E6692D5ULL, 0x5D2323302214168EULL, 
            0xA835DDF5EB2D7301ULL, 0x3FF9AA55A3B1A843ULL, 0xC342CBBE6B88672CULL, 0x23C92E4CCEE7CFF8ULL, 
            0xE2A83C470231AE3BULL, 0xA18F9791B78CD52AULL, 0xB5AE9EBD3D0AE1D9ULL, 0x22B6C9D478DF1579ULL, 
            0x368133AB0337FC3DULL, 0x6DDDF9FEFF543773ULL, 0x514B15A082C354BAULL, 0x416654C12C324A09ULL, 
            0x1E44F8835D63FF6AULL, 0x04ADF813CC22FF87ULL, 0x37EF8EF682542AAEULL, 0xC743D848BFF44F49ULL
        },
        {
            0xCD6A0B065BD84E4DULL, 0x82B3A2E4028B255AULL, 0x886965D66C057608ULL, 0x74FB0816F12FC883ULL, 
            0x1EBF8C8604C3A038ULL, 0xCB6FB0D5349BB243ULL, 0x7BBBE1F142D65339ULL, 0x273E610754761E71ULL, 
            0xDD61DA90C5C49840ULL, 0xA28616564E0220A6ULL, 0x8B3000EDB9811A24ULL, 0x2E8BA18A43112E11ULL, 
            0xAB05A70797A977E9ULL, 0x0BBDE78AD16676BBULL, 0x1428C9A93E5687F7ULL, 0x929C73E66234EF72ULL, 
            0x0BF12DD7F1FE6312ULL, 0x759645FE68DCE638ULL, 0x8484CD106B4F1E5CULL, 0xC5EB934FF8CFD83BULL, 
            0xFB55CD6416BB3E2FULL, 0x40E12852978605C7ULL, 0xD8C7479B92402E90ULL, 0x5663AFF15704E5DCULL, 
            0xA990E57FABCEECFBULL, 0xDBF20D1DD01DDD9FULL, 0x8A95D06C82FA35ABULL, 0x4E33E7E4D61F083DULL, 
            0xBC2D206EC92906A5ULL, 0x24A497825D50E7A2ULL, 0xE3AC424DB6940586ULL, 0xF9546002C9B62914ULL
        },
        {
            0x56EE67B7426217E5ULL, 0x410682E9773531BFULL, 0x9861B7B3A84671D5ULL, 0xBA805CA86EF1669DULL, 
            0xB7C6548A65FBC16FULL, 0xD9A386E525850018ULL, 0x0AE660E9FF714008ULL, 0xACA27B6379D1F0EFULL, 
            0x07F6C8C5034935FAULL, 0x60D0054FDF63CAF6ULL, 0x849B59F536B1AA45ULL, 0x0C638792C2A80BCFULL, 
            0x21DCB23407AD9A06ULL, 0x75E7901155E5B200ULL, 0xFE9C4495DC05F451ULL, 0xFDB7B58503B1E184ULL, 
            0x319DE301D4032FA8ULL, 0xBC8011BA1ADAD223ULL, 0xD6C755E0F29A207EULL, 0xA37FE416A36645D0ULL, 
            0x80A1A411EF64B0C3ULL, 0x55BE060FC2AD5C78ULL, 0x7FD14F29E462B566ULL, 0xF2357D3BA2B68C28ULL, 
            0x2A5C034B30C0E0AAULL, 0xF9DD0F1A2A0D0715ULL, 0x7DFF78D00811F075ULL, 0xEF9D2D293134028BULL, 
            0x1CD235AC5964839EULL, 0x847C5E388B5C6D0EULL, 0xC2E0102DF932A808ULL, 0x0EFDFAB20FD44508ULL
        },
        {
            0x44997F28BB857FACULL, 0xBBB2918387C9B238ULL, 0xEE34CDDEA3C22C64ULL, 0x28B3D29F9941C637ULL, 
            0x3A9E284A2DA992B1ULL, 0x6E7B343B289ADC06ULL, 0xDA395F6500403263ULL, 0xF2D6FDF4E73B6877ULL, 
            0xAD431D3DC57B9C16ULL, 0xEF5EE7CA29903131ULL, 0x782F6F95530EF0D8ULL, 0x4E65B33558A3179AULL, 
            0x49567AFF6AF73905ULL, 0x6239AEA9A1AF3BFAULL, 0xE9623D2453CF8F98ULL, 0x23D5C35B2DC2A473ULL, 
            0x6C3C58A5498CF541ULL, 0x749EA005E57C0408ULL, 0x1C7A4A6D57B69E5FULL, 0x958CF821E8F3A831ULL, 
            0xC5A218DB89B2FA63ULL, 0x5606991203BE83F1ULL, 0xECE0509D194EE225ULL, 0x1626A1DF9F05C7A6ULL, 
            0x23C833F8FB957776ULL, 0x94F5B61C6E2FECD5ULL, 0x9943B25641880633ULL, 0x0C06F9DB0AE24523ULL, 
            0x9F9C2ED654BC13F4ULL, 0xD28F48A197C11DE4ULL, 0x8FD736A30950B818ULL, 0xDF045D97C1FFE064ULL
        },
        {
            0x02ED74105FEA8642ULL, 0x51B7235084C03F23ULL, 0x57DB029AC25497A4ULL, 0x92434115BD2FB727ULL, 
            0x049C0D6A7B8507B9ULL, 0xD02787DCCD212385ULL, 0x6E656E259EE7ACDCULL, 0xDD033AEC2DCB0C05ULL, 
            0xE4655CBAF3EDF38FULL, 0xDE8B97433CE24A7AULL, 0x5C9D1B4B5E5CDEFBULL, 0x98E32AFB1CD520CBULL, 
            0xDBA3EAC3E5277092ULL, 0xC93D595201CAFF05ULL, 0x0E5F7A9C51E9F732ULL, 0x13F0D494FA59B50AULL, 
            0x2A2C38BEC05F5122ULL, 0x4B889DDF124B45F8ULL, 0xC007B083F7B8F70DULL, 0x44C38732266049D4ULL, 
            0xAF623CDF318C572FULL, 0xBE7CC3B27F0E27C5ULL, 0xBFE55EB69FB5F2FCULL, 0xF2E7A67A1DD37510ULL, 
            0x0C97D8C8F03284B8ULL, 0x11F1BC29B9C3A9C2ULL, 0xC35DEEE0475EE978ULL, 0x84C20ED1EEBE98C4ULL, 
            0x189C196D9B6912C2ULL, 0x94BA0DED7A2BAF77ULL, 0x1764CBE224E35BA5ULL, 0x6CAB1962F6FFDB5AULL
        },
        {
            0x5FDFA844B5C5E018ULL, 0x401C99AE92FC74E8ULL, 0x68AED78217FBB555ULL, 0xC52D0CE2E89C6F98ULL, 
            0xDF497CAFC637DA9EULL, 0x666427D15EF9A360ULL, 0x6DC1DABD0EF5BA78ULL, 0x891BA30EE31B6BA5ULL, 
            0xB80AC9C968E11CBCULL, 0x6F4FE712F385EA46ULL, 0x0ED8BCEE6263C2A1ULL, 0xC77D2A119F76A758ULL, 
            0xCC1A344EBEDAC206ULL, 0x3C1FB6A0A9C84DBEULL, 0xFD8083F44118AAC3ULL, 0xB2649DFCC817F3A4ULL, 
            0xD40D3642651F5F8FULL, 0x1C2DA6A636FA2A83ULL, 0x6F950CEE21922B87ULL, 0xCA28E0BE5167EAA6ULL, 
            0x9EE0A832E4652ED1ULL, 0x2755197122C94E31ULL, 0xF60A6A30C7095D9FULL, 0xAA10854AC434BB0AULL, 
            0x011B1B95526DAB3AULL, 0x426FE032A2EC7130ULL, 0xAA14D979A3459BBFULL, 0xDA8E33B9D37FF2D5ULL, 
            0xED52A0F9BC000AF1ULL, 0x75A3DEF3A01B0D1FULL, 0x1971C204C5D00480ULL, 0x0DA280A75B5CE91FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseCConstants = {
    0x69FA8010A2286B59ULL,
    0xE7761B2B63611EAEULL,
    0xB86F562761DCC784ULL,
    0x69FA8010A2286B59ULL,
    0xE7761B2B63611EAEULL,
    0xB86F562761DCC784ULL,
    0xD28B4F2A8982BE9BULL,
    0x25DB56E8CA628A70ULL,
    0x50,
    0xBD,
    0xAD,
    0xAE,
    0x32,
    0x52,
    0x5A,
    0xD8
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseDSalts = {
    {
        {
            0xFB5FFD6E58AAE2D7ULL, 0xDB047952A5161BE4ULL, 0xCF8090BFA019F375ULL, 0xC10B81EADDA48453ULL, 
            0xAE7236687D9FCCAEULL, 0x3EB287094FB92198ULL, 0xF73123E60A51AA48ULL, 0x2B380B9820E0EC4EULL, 
            0x4A08A02505C3C507ULL, 0x4B27B40260EA6588ULL, 0x3CE13EF633F45273ULL, 0x65BF54C5DAF764BEULL, 
            0xC4A3B17769DABFB6ULL, 0xAA2E6693FAD8173CULL, 0xB5A13DFCEEA62A02ULL, 0xB2D11DCB206121C0ULL, 
            0x671E06C8E206ECB5ULL, 0xC03AFF973A3DA1D5ULL, 0xB763892977EB333EULL, 0x89C031FA59B12021ULL, 
            0xE84CD0D56E024B4DULL, 0x9BDE7BEE58DCADBFULL, 0xE964CB5B884316B5ULL, 0x399A418B36450D28ULL, 
            0x2E3FEB3E41A33773ULL, 0xC1B507FD496A7959ULL, 0x36D375192209A6BAULL, 0x7C513E4D6D2841D3ULL, 
            0x7A3078F8AD620C78ULL, 0x3DE39C6F97307F27ULL, 0x89F37E09D5A283ABULL, 0x5CFC37A529FF0AD6ULL
        },
        {
            0x310294676DAB4F40ULL, 0xEC3BB2E46B14830DULL, 0x0864D85685A54670ULL, 0x84FE22856EC13C8FULL, 
            0xDC11C2B02DF9D0B5ULL, 0x09F183CE9FC83B0FULL, 0xECD6A41040CCD283ULL, 0xFB93BEB3F655E3BCULL, 
            0x421620E8EFBC6E43ULL, 0xD365FB7A652CE7ECULL, 0xF9CBFFD139D1030CULL, 0x73E34E9966291197ULL, 
            0x0F90CBC0EE45339BULL, 0xB4AF3F99291D7A58ULL, 0xDC4A12E5F9DDA3E7ULL, 0x8454F36621FDF3D9ULL, 
            0xF3B9E5466ED7E596ULL, 0x4A99A96B039E7645ULL, 0x6BC9B240725E6CD9ULL, 0x4AAAF066E4DBB7DEULL, 
            0x578F5D8B891D00F6ULL, 0xC2B56239160BF972ULL, 0x5CBD97D4954E0F23ULL, 0xDA243576120D753FULL, 
            0x1E14E6B7C49271CFULL, 0x037AE7301644E1B3ULL, 0xD7E41927F2120020ULL, 0x782D2A510DF76970ULL, 
            0x8D8C3F0E8AA5F8D9ULL, 0x55BBADA8C3F56446ULL, 0xB79E18CBD1AB7CADULL, 0x803D2C93CF0EB18BULL
        },
        {
            0xEAE8349B119C63CCULL, 0x5CAE24AA1BC52AD7ULL, 0x1AD78FD48FDA5D88ULL, 0xEF865140BD76794CULL, 
            0x48EE73BA06541958ULL, 0x4CFE8825B1D421AFULL, 0xE029D222AD3F8B2FULL, 0x5AC7DF4CDF41BEFDULL, 
            0xFABBB86649505EE3ULL, 0x8B2CE0FFF752438FULL, 0x2705DE9682499E96ULL, 0x3ADBD4EFA42248D4ULL, 
            0x12D83F81A2902428ULL, 0x61E1191324436CECULL, 0x540E5C4147DD6F7AULL, 0x6EF58547708215C0ULL, 
            0xF460D2EDD27B52E5ULL, 0xFB361AE9822E54ECULL, 0x4D7E1F5FA69218D4ULL, 0x90D1C75D045F5C39ULL, 
            0xEFDC0552D5D37570ULL, 0x817395047C7364B1ULL, 0x18FB140E06056112ULL, 0x165B57EA6780BE47ULL, 
            0x68240E7C157A8CCDULL, 0xB8301532C43F27D5ULL, 0xD65E7EAE1BC0EE86ULL, 0x9DAED5FDCC8A2650ULL, 
            0x2918F31B86214D87ULL, 0xFE8B6450D69058FFULL, 0x211AA5AD64D09034ULL, 0x0F13D969CB8AADC0ULL
        },
        {
            0x9D70137A978BDEEEULL, 0x4C75F8FE73856475ULL, 0xE92FF5309698FF85ULL, 0x8C7EBBA55DBB380BULL, 
            0x68FA6A38C527B785ULL, 0xA3BE9A03520110D8ULL, 0x08E5ABEDFF2507C4ULL, 0x127E67B51A8A98B0ULL, 
            0x5A689CFC9E76F132ULL, 0x5B415B6FF1B7425BULL, 0x75CBDF8F723D7B1EULL, 0x5C7E43F11DCB81CAULL, 
            0x6D4456B0E78D00A1ULL, 0x2AAD336B81F40789ULL, 0xECA919D308346C05ULL, 0x017ED9FBFD8A17CCULL, 
            0xDA8C78790C7547ACULL, 0xCF5B85FC1C8AE87AULL, 0x06A5B660B2CCE517ULL, 0x5A6BA240B17FD602ULL, 
            0x59D959C9F57B6D7AULL, 0x5ECBE5E57379E298ULL, 0x8797E569F6BCA154ULL, 0x007B821225D65816ULL, 
            0xBC378157C69DD397ULL, 0xFEE61796D68A74CAULL, 0x36D21EFC66421F35ULL, 0x112E6694BC64AF77ULL, 
            0x3E9B7FE5AB70E098ULL, 0x6D2C3081C2D4EDC0ULL, 0x947A704F2950B7DEULL, 0x9A79F369909E7793ULL
        },
        {
            0x5EB806E7D84AEAFFULL, 0x6F2F0EA936E03332ULL, 0x9E762F3187D85545ULL, 0x1EC4808DF6ED31AEULL, 
            0x89D6DA87D1BFE441ULL, 0xC79B9840DFC8DB1DULL, 0x5E55A3A7479C9E3DULL, 0xFD05F5E79A797286ULL, 
            0x72E1D7E99EAD1042ULL, 0x404599DAB6F849FFULL, 0x7F6CB709005E6043ULL, 0xA1066D72A8A90A7EULL, 
            0xB1B3657B016E6DB5ULL, 0x98F23011D4CB9DE9ULL, 0x92E863F20FF52338ULL, 0x4B48F91BAC1D86BDULL, 
            0xDA48AA66F88D196DULL, 0xEA40B3719320FEC1ULL, 0xA19421C0499DFD10ULL, 0xA02AFB3972071817ULL, 
            0x655D9E99BF601065ULL, 0x46AE944D991E82A3ULL, 0x1352A5F7058BD5EDULL, 0xB1CE80829AF92E9AULL, 
            0xDEB278F5F8B8B451ULL, 0x3BF9B56F39FA93FFULL, 0x1B47A016518E38B8ULL, 0x4158C19784F6F3FCULL, 
            0xB5060C63C4B47C3FULL, 0xDE1B831DFCE41FAAULL, 0x977CFDF5DAC70808ULL, 0x717667886B9107A1ULL
        },
        {
            0xA68FC1D1A1FF2E58ULL, 0x0AF5FECAC256D51EULL, 0x7038F89B2925E957ULL, 0x11ED131CC6B3B280ULL, 
            0xC65EC9EF72D6756CULL, 0x9D892241F106FB4BULL, 0xBD3F6C344F7A1938ULL, 0x18F33D080445909BULL, 
            0xC2304B55660B9E9AULL, 0xCA006C0FA9A5A852ULL, 0x2440CE716F99E139ULL, 0xEFA119132477D7C0ULL, 
            0x8D09ED3330AB15D6ULL, 0xFFF553385F538FEBULL, 0xE0D186DA8ED2A19FULL, 0x3E594D4B7775414EULL, 
            0xE7664113A84013ACULL, 0xD70D02DCCD38A903ULL, 0x916FCC14829212E1ULL, 0xA4C266A1235FD50FULL, 
            0xA2CC0AF7C0809FA3ULL, 0xE5F7A3800F2E0C33ULL, 0xEB3BD69CD291F10CULL, 0xB6EE32D6DB01C200ULL, 
            0x145EA2E643FE8C0CULL, 0x8D022406F56C6514ULL, 0x1EA7DF01F32179EFULL, 0x1B626A8F2F52F869ULL, 
            0x615988FA3BB1A39EULL, 0x0A32B4941B5087DCULL, 0xC631D217EB435359ULL, 0x6FFB99BCC9BE24B3ULL
        }
    },
    {
        {
            0xAC6A3EB6F121BC5FULL, 0x8577ED03B413A2F5ULL, 0x54F2859F64A117D3ULL, 0xEDCBEB8A5ECE3B79ULL, 
            0x5818E7E6D42D5B51ULL, 0x153C648DEE5E5344ULL, 0x471B0F0E56DBAA44ULL, 0x0981581CDD430323ULL, 
            0x7F76C49BCF00F07BULL, 0xC5ACADD1D4EBE395ULL, 0x608421D89D97A9BDULL, 0xC4FF7C6D576DAB98ULL, 
            0xB867CDAFB6E2D23AULL, 0xF5E55382B66A8195ULL, 0x3A93CFABF834BA8BULL, 0xFE77DB6A7EBD1DDEULL, 
            0x3A6976F268FD69A8ULL, 0xDDF9A9B8D7659046ULL, 0x751D379E8420693FULL, 0xCFDEC595D10B2193ULL, 
            0xDF45D2F84070808DULL, 0x054D531DF536AD3DULL, 0xCA1ADE27AD7A39FAULL, 0x9735952A360C5151ULL, 
            0x235E217E502B954EULL, 0x93C0A7A698CA1BD1ULL, 0xE06530E81B9219C7ULL, 0xE54DF905721149DDULL, 
            0x7FCDA7B6BD26C2B4ULL, 0xC54AF75AD760E67DULL, 0x347FDD7932B305F8ULL, 0x3B710F1B19AC0263ULL
        },
        {
            0x6CB54D388532F840ULL, 0xFC3EEF4472D1D52DULL, 0xFFCC949839F26F3FULL, 0x7629266906BC5435ULL, 
            0xCBF30DB4AD9792F2ULL, 0x8A98510A9E7D2697ULL, 0x7E8526025E94261FULL, 0x8501E04488CB139CULL, 
            0x50A19AAAD9D2BF3FULL, 0x74441BE0949E9C25ULL, 0x975F3E22CFEA740DULL, 0xAA35D67F012411AEULL, 
            0x84463357F50E9772ULL, 0x55540CA032C6FAA1ULL, 0xA83409F77A2811DEULL, 0xDFE529F594ECD952ULL, 
            0xCCF957B0DEC63189ULL, 0xEDEF53B6CCBFC80BULL, 0xB6AF6D7051A6FE3DULL, 0x1FF05F109DA8011BULL, 
            0x75FCD32165DA58E0ULL, 0x27BC8EC359E2754DULL, 0xC853855D85AAF559ULL, 0x9312B5E6ED1A32A0ULL, 
            0xF1FD2AED108F5182ULL, 0xEC00178E42919B8EULL, 0xBA4BB4A260490B9AULL, 0x1D40A07509DB704CULL, 
            0xDA86B1DA3019D101ULL, 0xA98913447B494AD5ULL, 0xB2DCE87026712D7CULL, 0x2EC6B2630F82BED6ULL
        },
        {
            0x18FF1ACB77CA5265ULL, 0x14936F8D66FB346AULL, 0xF6DF36B25135C3E9ULL, 0xB97EB7CDAEAE69D7ULL, 
            0xABD33C6F15C93894ULL, 0xDF7E92EE0989F93DULL, 0xF5020DBA4139F228ULL, 0x809F2F3504341E2AULL, 
            0x3C9C0AD88822AD61ULL, 0x66A7C310C2176CE2ULL, 0xB9EC957BB7F76AE5ULL, 0x474BEDEF42342818ULL, 
            0x290354B655E5A389ULL, 0x59E6EF9067D05919ULL, 0x5DE40FFF45360066ULL, 0x6AC1A62B7D760792ULL, 
            0x65A4408C61A2085FULL, 0x829DAD3519786732ULL, 0x52ABE22F76108AF8ULL, 0x2AC1B107BFB7D996ULL, 
            0x28831DCD31A01B0DULL, 0x272AD4FEB6663BBDULL, 0x8A9F500D2B30D134ULL, 0xD1D88923ECF8A19AULL, 
            0x7DC176CCF8AC3D14ULL, 0xB1930436F0D02687ULL, 0x22BACA3BF518D22DULL, 0xE5867E77EA558B39ULL, 
            0xF88D192A78F010D3ULL, 0x7C767D2E3F924EC2ULL, 0x2AEC5036C93176F7ULL, 0x29A6F4F0F46788E5ULL
        },
        {
            0xA8FE6CDC5ACCDFC6ULL, 0xD4495E6992BFD773ULL, 0xF639EB11807CD1FEULL, 0x6C613D39EF298C08ULL, 
            0x627268F1AAE0DCF0ULL, 0xEE750CF9B825BE5BULL, 0x647B75E5991B4A0DULL, 0xD449A510017CA874ULL, 
            0xA9FB743A89065AAFULL, 0xC266BC1D2326046EULL, 0xC71C397DAD3E1F50ULL, 0xDE533C6D58FD4AFAULL, 
            0x981435D3D0EC5DFCULL, 0x86AC48755F9EFD04ULL, 0x573761A9CC45A4A4ULL, 0x645D99FB746CE66BULL, 
            0x6C02B01975C1B379ULL, 0xD7F2F873DB9A60E3ULL, 0x38007B78B9069BF3ULL, 0x1A99A456D9FEC989ULL, 
            0x39B8E8B3C66DEE5EULL, 0xF8906476E5696AEBULL, 0xF2B60CE3522769C6ULL, 0xA7BC9ACA0A677F5EULL, 
            0xE28BEBBC5037CE7AULL, 0x397612725FE0D7D8ULL, 0x2B11CEDBC0CF3261ULL, 0xB0D58FBE0FD66DB0ULL, 
            0x3973EA6B21383887ULL, 0xB8279D793EC7171EULL, 0x1CDB385A87C49DF9ULL, 0x9AA3EEEFF3E0AE31ULL
        },
        {
            0x2196042B791FE2E8ULL, 0x3CF95D1DB987A053ULL, 0xE7392119F5A2D65CULL, 0x5D6706E757580634ULL, 
            0xE6056605134D171AULL, 0xE163C81D7D328464ULL, 0xE60BF6DC16A7EE91ULL, 0xA5710C95AFC698FCULL, 
            0x75C41037058B5C21ULL, 0x1C48B02A2B174157ULL, 0x227C1239ED21B010ULL, 0x036C300B17589EE2ULL, 
            0x547910A11185BA0EULL, 0x6A7FA0868F1E6BD2ULL, 0x9833473FC5D57212ULL, 0x83890DF3586276BDULL, 
            0xB9F6780B4FA8EF88ULL, 0xBCC13DAA665FE73FULL, 0x721A39E51571C540ULL, 0x0D286F9F2934AB83ULL, 
            0x006F6C5ACD197E38ULL, 0xC32D73013AAEEB95ULL, 0xE484A37AB9BE35C5ULL, 0x9C2FFFFF4AAA5C69ULL, 
            0x0B9FD1707E9DFBACULL, 0xBC29FB679A43B621ULL, 0x4DA488B80D68EAD7ULL, 0xFA3425D103413F68ULL, 
            0xEF74EC37522415E3ULL, 0xEDD870DCB5DE7EE8ULL, 0x4661CF91805D09D4ULL, 0x64CBA4982F5583ABULL
        },
        {
            0x13610640C9B26A0BULL, 0x01E14DD8D2080134ULL, 0x71C444BB98D7411AULL, 0xAAEBB3C12D4B2353ULL, 
            0x7675C92F77A4B70FULL, 0x34E89D7473F9143BULL, 0xF6CC95FC56A4186DULL, 0x42A18CFF62009DCEULL, 
            0x985A43543A3A3BD0ULL, 0x209CD276DE1D5B74ULL, 0x7CAE060ECC60BAB7ULL, 0xDED05C86F49F3F5DULL, 
            0x901D7557B77E38C6ULL, 0x11ED78ABC658B7E7ULL, 0x8CF00D5DB57BA863ULL, 0xD737FF0733A7877FULL, 
            0x4E8F6AFA60B6405DULL, 0x1F7233DD02CD062FULL, 0x89353DFD5EA03131ULL, 0x58A20CE6F50785CFULL, 
            0x9BAF17812BFAB585ULL, 0xC796B58B4DB44BF5ULL, 0x932C13826B0F5A86ULL, 0x33AAB808EED39FF8ULL, 
            0x9F33F770FF678879ULL, 0x040E5E29744B3F6CULL, 0xC6EE676A716F8240ULL, 0xAC62E6B73DF92589ULL, 
            0x2EB983C3F68FE118ULL, 0xE612C6C09D38E756ULL, 0xD211A5DDC51DC067ULL, 0xC9394A0DCA936E49ULL
        }
    },
    {
        {
            0xE476331F66F7F81FULL, 0x4873FF70F6ED19FCULL, 0x230D67FE05F0F901ULL, 0x1F24EC8BD88AA927ULL, 
            0x8CF367A26A0ABF33ULL, 0x12C1159DE1051BC1ULL, 0x7CABB057270E27AFULL, 0xDABF32C11B8A5A22ULL, 
            0x9A6D41ED6A8A1A4AULL, 0x329E409F5E1ECA9BULL, 0xB8007B4B85EE35CAULL, 0x86AC32B13E8B0CF8ULL, 
            0xE71212339BBD0EE8ULL, 0xF6BF78DB44850493ULL, 0xD297579A77896E07ULL, 0x04C2A34C28EB6E4FULL, 
            0xB80DF1220C2E702DULL, 0xB456A1FF431EDA8AULL, 0x8CB62A2823271851ULL, 0x4712BA475C037161ULL, 
            0x30B95432BFFE1D09ULL, 0x13C548958F13C28AULL, 0x97BF533AC056E8F2ULL, 0x15D1753519870293ULL, 
            0x9BC7F1ABB82C3B20ULL, 0x3B50ABE6405DE17EULL, 0x22A3DE19A7787834ULL, 0x1E7DD4D5032DA6C1ULL, 
            0xE289B4B5D5E94029ULL, 0xFE9DBF5005AA44B6ULL, 0xA1990B552254660DULL, 0xA9562AFD502C2221ULL
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
            0x6E3C7E9AB4B9C2CFULL, 0xC24471F54B0D59C5ULL, 0x5581F0E0E06E02D8ULL, 0xBED9192BAAA25B24ULL, 
            0x32A49D389413B5F4ULL, 0xDE52C5FF83881213ULL, 0x5EBF9FF074843E56ULL, 0x02533032B0ED9467ULL, 
            0x60C9F1ECD6D4D1D3ULL, 0xF8254540844F0373ULL, 0x40607472F59B6ABBULL, 0x5D29B19CDB1CAACCULL, 
            0x478441FE55C1BDCBULL, 0x3E7F0555FE34BC70ULL, 0x71820448CC4F7BC1ULL, 0xEA48B2BD22B0D730ULL, 
            0xDE96270F19A92D87ULL, 0x00A3395424C20AB6ULL, 0xA60E7F7578E8B9C1ULL, 0x9518E4D509518076ULL, 
            0x6C79246A5574BF21ULL, 0xE4A776927A2B5E61ULL, 0x7CEC243502746F04ULL, 0xF9B93BE77AAEC457ULL, 
            0x953E9FBEAEA0CA47ULL, 0xE68D1B3932D35D73ULL, 0xE581B7ADFDFABE9CULL, 0xE9B25A8AEFCA0B4AULL, 
            0x01FD62BF9278D7AFULL, 0x039A94685BFBBFCEULL, 0xF0046E31EABE8AFFULL, 0x0753382101CE828BULL
        },
        {
            0x9FCDF11D10298ACFULL, 0x26C09C1B8A482501ULL, 0x12681BF879327913ULL, 0xED01A9A3E02D24F5ULL, 
            0xD4C9BF07421482D2ULL, 0x9DD25E1FAD74DD3DULL, 0x596C3AF3E4FABC06ULL, 0xBE3D6F42EFE838FFULL, 
            0x3F766216C1EFD429ULL, 0x4FBFB981933ACBA7ULL, 0xD1D7258C12A25113ULL, 0x04BC1E01FB0306BEULL, 
            0xC8A13C5E1626D464ULL, 0xCCE513FE0D331944ULL, 0x2A575088E1EE104BULL, 0x962B89AF1196C753ULL, 
            0x51B8A21DB8ABB44DULL, 0x62A495AECA2E55F6ULL, 0xA562EB6B7F4112F8ULL, 0x17B1D997E2421F49ULL, 
            0x2E8A1A5617795A23ULL, 0x64CC45555E0BB2CCULL, 0xA75F65D254FEEF19ULL, 0x00F611D92202C34EULL, 
            0x76A4D6F7D296EB4EULL, 0x8D7E755078117F83ULL, 0x7FDC763AD3551B36ULL, 0x22E353D426F70F31ULL, 
            0x9145C735D232EBFEULL, 0xCC1E967780ACC71DULL, 0xC6BF5C7896420EF4ULL, 0x92C246D6EAE5AB76ULL
        },
        {
            0xBC50DEA7F7837C20ULL, 0x6DC967A022D42894ULL, 0xAB531116C23F0DEAULL, 0x98264DB7D17FDAF0ULL, 
            0xC9125BDDEAA89078ULL, 0x41D6C41DF773589AULL, 0x1C17189C22EC8A13ULL, 0x7DFB2D838554CFDCULL, 
            0x168930E6774B514EULL, 0xF0DEBBF100D99F97ULL, 0xCA79C689E9256EA9ULL, 0x1D9A74E76022418AULL, 
            0xDEFB9550BFD58DB5ULL, 0x417CB67496E9005EULL, 0xBAA23D43128076D8ULL, 0xAF046FF2B0FE88EEULL, 
            0x0876C4A98D68D27CULL, 0xB26087D468B8AEAEULL, 0x3016D342E63AE895ULL, 0x68AF62C1000F8285ULL, 
            0xDCE2A213F6BA63C2ULL, 0xD4EAC809A3F36006ULL, 0x4965E916EC13B9AFULL, 0xBD8E1689B29BA47EULL, 
            0xE45D8D4A028410B6ULL, 0xE46E68CF37D09BD5ULL, 0xB76BC845ED7C48C3ULL, 0x47928A9E10E43341ULL, 
            0xC53CF0907E1CA17BULL, 0x3DA803AB5AE9CB55ULL, 0x79C7C4C106FAA372ULL, 0x2B7F3509FA9B640EULL
        },
        {
            0x3BBCA1EC119D4C6CULL, 0x5B8F49413FE3393FULL, 0xFFF956519CBD0BDEULL, 0x0EFE8838A6A6DA72ULL, 
            0xD0D4835F3D4727A0ULL, 0xB947A31159E9D164ULL, 0x0A31208CF8D255B0ULL, 0xB2962A2DA0DC360CULL, 
            0x6B402F03FEB1B4ACULL, 0xBAEB400A70D16A95ULL, 0xC7FBD2B8E77AFF38ULL, 0xE9302FF2D6FCD09FULL, 
            0xCDF0A3258039CF9DULL, 0x0A8FB0EDF3F5770EULL, 0x7F67ABDAA77086F9ULL, 0x1D88A7D58E5AE2B1ULL, 
            0x0150BEDEFE70B34EULL, 0x7ABB0110C4AC9EE2ULL, 0x8F85506C3E7146CDULL, 0x5C36BD576CD2EE25ULL, 
            0x756610E1E55FEEC0ULL, 0x6321E783152C3DE4ULL, 0x51EB1E965E86F56AULL, 0x0DB521A20CE32690ULL, 
            0x30B9A1C2C4EB9C51ULL, 0x6EFEC415050D6040ULL, 0x2083A5B4B4461F65ULL, 0x0E825504444DEDF8ULL, 
            0xD5DD41E841D555B1ULL, 0xFDAC5375527DD295ULL, 0x9D8E59166D18EF59ULL, 0x0C11D32C6E231A63ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseDConstants = {
    0x9B75A0BEF4E5C45FULL,
    0x3A525E82E9D46F7CULL,
    0x09FCA4A2D4839EBCULL,
    0x9B75A0BEF4E5C45FULL,
    0x3A525E82E9D46F7CULL,
    0x09FCA4A2D4839EBCULL,
    0x4BD94EF73785F539ULL,
    0xB1E4CD0A3936A374ULL,
    0x39,
    0x2E,
    0x6B,
    0x4A,
    0xFE,
    0x6F,
    0x53,
    0xF8
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseESalts = {
    {
        {
            0xE4A18A5A2D35298FULL, 0x4D2CDDB1D968E13BULL, 0x17D8BCE17A3F1365ULL, 0x7A41E5B1A97C9E82ULL, 
            0x37A002DE74EE368CULL, 0xAABEE66E456B2DBFULL, 0x3FC409AD32438B99ULL, 0xBB1728EE92A0EEC9ULL, 
            0x50D472718E879503ULL, 0x3B7246061E60A7FEULL, 0xED6077B46E06CC84ULL, 0xD8D47A8F34C9AE29ULL, 
            0x3A4FCBA3B8AE926BULL, 0x09B68257F7D5BD08ULL, 0xBD5A7D4A19F81FE2ULL, 0x9E875AAD7BE1991CULL, 
            0xCF8334217B0C25D0ULL, 0x81ADC305C52AE50CULL, 0xCF243D8D31D6AFA1ULL, 0x878A7A37068DF897ULL, 
            0xB3B9F6BC2DC7BBA9ULL, 0x769745DC485BD13FULL, 0xE9ED3A68DB253EA1ULL, 0xF187A1B2080ECB15ULL, 
            0x8461C1D2ADC35EC9ULL, 0xC4D043A530E8F1EEULL, 0xA9F337CE67D7641AULL, 0x8EE8FC00D0419AB2ULL, 
            0xD69C39908BCE87D9ULL, 0x0BF65928D2307F72ULL, 0x2025EF9DF1AEDFD2ULL, 0x923031A2B89B2AACULL
        },
        {
            0xA2B69F15714B727BULL, 0xDE06C0FDCA54FBAFULL, 0xCFED399E4EFA2D76ULL, 0xA99CCC2F27F93DC3ULL, 
            0x4200BDADA579D18EULL, 0x088347A6D48DD797ULL, 0x1795CD1AB6CFFCCAULL, 0xB9B7E2A4A334B7F1ULL, 
            0x789C4BACEFFF99DBULL, 0x5AE5837145E2CF42ULL, 0xF1752BA85C1D5D7FULL, 0x2D503EFB5E5DAFD5ULL, 
            0xC048BB03707ECBBAULL, 0x5CEC6AD1EEBB49B2ULL, 0x457CCBC86C14D6FEULL, 0xC189019C36ED298CULL, 
            0x42AEEB7E0A2FA64CULL, 0x424A8141C5AA5E22ULL, 0x575FF70879EEAA35ULL, 0xB80430AFDCA8662DULL, 
            0x725577C57E7616EEULL, 0x71FD42911F93DFC7ULL, 0xF0F317F5FFCC858EULL, 0xECBEF5C53416B1AAULL, 
            0x6C8CFB0833555EC7ULL, 0x82B59C625A05BF63ULL, 0xFFAD85C32E7A2AAEULL, 0x465716C5C05B0805ULL, 
            0xFCB2B382FA88884CULL, 0x25AEB3F06BE595BCULL, 0x7FFCA7B648C52D61ULL, 0x4AD4C677CE2018D7ULL
        },
        {
            0xC487181989895498ULL, 0x4652A4B5B80CCD03ULL, 0x2FF2599FEE3E898EULL, 0x4608415CA4C08D38ULL, 
            0xCBF83D7DF4A713B4ULL, 0x857DCBE19233C7D0ULL, 0x122B1B49FB368092ULL, 0xBC8508DDD54F5CECULL, 
            0xADA5D77F2F3E83CDULL, 0xA841CCCB1C26A098ULL, 0x7CB0D92AFA2A17C3ULL, 0x4C28651DD36E6842ULL, 
            0x36C33DAFF5CE4D73ULL, 0xAFABF2740724D203ULL, 0x3057002CBA4F9532ULL, 0xE31A2F78C765D698ULL, 
            0xBBC51DA57EAA9057ULL, 0xFA1BABF19D9F91DDULL, 0x9527CAE2D2BCDDD5ULL, 0x53FEBEE4527C6124ULL, 
            0x6C51BB494FF0118EULL, 0xDE7A98DE81AF8F88ULL, 0xB9E63821565503ACULL, 0x666EC1AADCD395BDULL, 
            0xC9E4363834FA768BULL, 0x7E748C79CF219ED1ULL, 0x9A81404B5C9BE17BULL, 0x469842C3707EA528ULL, 
            0x2C532564610B989CULL, 0x2B8F0B2E6E20C3BEULL, 0x6819A479E4A85514ULL, 0x50E737BBDA02505AULL
        },
        {
            0x82EF5C9459F2412AULL, 0x2006740B3ECBA894ULL, 0x4E0E2EFDBED965B4ULL, 0x50940056921D7F9FULL, 
            0x57236D242BE9FA44ULL, 0x75F122DC22F15515ULL, 0x62696E72A8FD64EAULL, 0x118CE2BEE577C6A4ULL, 
            0x60C3437E270F7BCDULL, 0x4853CB6B717EC6FDULL, 0x00E84845877ADF9EULL, 0x34CD9D62AC1480D7ULL, 
            0xFB2183213F59E846ULL, 0xC1DC6A2A3F44D15FULL, 0xB638D9F1B1BC067DULL, 0xF8176F1F4A97A1EFULL, 
            0xD2B3F1DC6DC3DAB6ULL, 0x9514158FE8549998ULL, 0xE57E961CBFC50119ULL, 0xA4F669B82ACF09CCULL, 
            0xBFE3C04F69300591ULL, 0x393EAC17EAAB2BDBULL, 0x55B2405451ECED96ULL, 0x733C488D7E9C3A62ULL, 
            0xA1C6BC7A36B1D70AULL, 0x8BF584EFFDB626DDULL, 0xAF70B881CB754458ULL, 0xE99F5C374497E290ULL, 
            0x5EDEE2B4B5056A7AULL, 0x008197A345675601ULL, 0x6AC6EB552D871FB1ULL, 0x122243708404C8CAULL
        },
        {
            0x5E525672DA169F16ULL, 0xFC8C5BD80EC296D4ULL, 0xC2FFC006A670A0F6ULL, 0x7A7A54D085E48AF3ULL, 
            0x18E935D9A038C128ULL, 0xE20931CD88B3D2E0ULL, 0x6FBA683BD96A0803ULL, 0xF7D4D2FE1E1D08CAULL, 
            0x1CDCB899D64E139AULL, 0x6116D572A8A054F6ULL, 0x24C31FE4F7ABD634ULL, 0x4674C949A77CFE47ULL, 
            0x763900EC9B853F02ULL, 0xF32B510734B7F301ULL, 0xCCA1586D433332C5ULL, 0x4A9B225C4FD24CA4ULL, 
            0x15024222BDA0AE41ULL, 0x51E94E2F6FD418C9ULL, 0x24B2EB7D44E2526DULL, 0x6913E49D14683662ULL, 
            0xC14C42A0BF699980ULL, 0x308A60669B1993FBULL, 0x5AAC988DCA59AFBAULL, 0xC2671EA60FD8A0BAULL, 
            0xDBC040DCD69D2EC5ULL, 0x9E6D512FAF75AD7CULL, 0x634D9E3394D8217DULL, 0x25EA62B411D7FB5BULL, 
            0x0BC572FD03994D95ULL, 0xF300E003A5BF74C0ULL, 0x297680AE70C9A35AULL, 0x274559378E071E7CULL
        },
        {
            0x61567643F7FB30A7ULL, 0xCB97DCA337E50157ULL, 0xF7F6B9A3A9314C37ULL, 0xE18D9B9D9E72304EULL, 
            0x1C59CD28CA6B2C55ULL, 0xBA5540F9AED7C6FCULL, 0x6287585FA3C4585EULL, 0x7182E1458E7E5161ULL, 
            0xD713DB03A970CEAAULL, 0xB9A6B204DA795F96ULL, 0xB8DDEE6B2C88372AULL, 0xE74BAB127806EA5AULL, 
            0x973C10CAE01F4E97ULL, 0x506E42D4B3E9C4DDULL, 0x02E03CF118CEF4E7ULL, 0x9528049EB540AE81ULL, 
            0x45F0043DF8AA4D70ULL, 0x0BE59AA8525ED56EULL, 0xFAC5469A5BAF122AULL, 0x45360F19C39F01E3ULL, 
            0x51CFAE0CC9DABD3EULL, 0x89B91296E5F38A3BULL, 0x863ED608CCD2C97BULL, 0xB028EC7978C3F43EULL, 
            0x291328727DBC9988ULL, 0x8EE6FA96C80D8F5EULL, 0x28AC96B6DCEBB125ULL, 0xEECE13B8C38B6280ULL, 
            0xD2C03E73511DB023ULL, 0x24F4094B9162131CULL, 0x2D6BD321956BE9BCULL, 0xAADFC2AACC6923C5ULL
        }
    },
    {
        {
            0xDC8F17ED59F1CD7AULL, 0xB7E12B74B160A8FDULL, 0x8B3AE69B9C1964FAULL, 0x02D42C133A1F8A55ULL, 
            0x07E81D5BE43C3F48ULL, 0xB90E747C042646E2ULL, 0x83DB9FD15013C5DBULL, 0x2EDDBCA6A33BA00DULL, 
            0x64E2355ED604D605ULL, 0xB6A7B1E7A3493433ULL, 0xAEC66A50395BC52DULL, 0xA133DEE310FF3DB3ULL, 
            0x7D1D3550FA54D7B4ULL, 0x88BDE6A7B1D8ED26ULL, 0xA09E50B70BDBBCCFULL, 0x860C40EF0B8BF687ULL, 
            0x7634E4E722DBF75EULL, 0x1C5FCA1D434586C2ULL, 0xE8F34DE12EB1C653ULL, 0x78709A339AE97D9EULL, 
            0xE4930B859E09B5D0ULL, 0x69351420B5B19BDCULL, 0xC815C22EAADC9C4FULL, 0x6FC5528C18233922ULL, 
            0x63AF50594BE27173ULL, 0xE9BDC9404F552C36ULL, 0x5BAB7839331CF290ULL, 0xC762CF24B76C83D7ULL, 
            0x4E3415777968639CULL, 0xFD1C6762BBF517BBULL, 0xE7E03D2332F34AFFULL, 0x9A5FCB40DD6A8EDFULL
        },
        {
            0xC8A32798A63CDDF4ULL, 0xF9DB3FE3264E9218ULL, 0xD1852CCB104F7D76ULL, 0xF20C955F3FF33AD2ULL, 
            0x58CE05EDE23F857CULL, 0x3718981EB4D18DD0ULL, 0x176BE153FA6278A0ULL, 0x1410EA3E88463317ULL, 
            0x9DCAFD2FB6BF0899ULL, 0xC32F3B94DC7F91E1ULL, 0xC00C2E8848C4D1A6ULL, 0x2E4C893B54BD1AFAULL, 
            0x1D6C0D549A331218ULL, 0x8951BDDE2584D71BULL, 0x4D64956FC9973A9BULL, 0x7EB659752A0E5345ULL, 
            0x0843D1B1A5041F6EULL, 0xE679E5EEA811B784ULL, 0x2FD7C5EC73E3956FULL, 0x6C7095F7B87B49A3ULL, 
            0x775FBF7230EEF238ULL, 0x3BB3E8141309C23AULL, 0x0AB135A9FE7C3E61ULL, 0xFC0ADD1E25453EACULL, 
            0x5A116184D43507CCULL, 0x10D2E3A47E2D632CULL, 0xAFE24CED96E681EEULL, 0x1582EADB33A77783ULL, 
            0x2EBD1AD48ED66620ULL, 0x736B6FC2D866D699ULL, 0xAF7CB26211317A14ULL, 0x2DC25C31D1D91C81ULL
        },
        {
            0x7E0093579F74CF4FULL, 0x98BFBF05D2F7BE56ULL, 0x1E8E98D12D29B27BULL, 0xD2202B7531EAEA65ULL, 
            0x6D8CDF7D5A1771FFULL, 0xB6466C7E6DC59809ULL, 0xDACAEE35B0EE6290ULL, 0x716F34071146F0BFULL, 
            0xCE6CBB45C3CDDE7BULL, 0x48F11E4B2D102500ULL, 0x9A870698F1073DE7ULL, 0xD2FCAACA2BC8F507ULL, 
            0x8A4590B189D50E11ULL, 0xAEE267CD21A480A4ULL, 0x26F7863E189BE8D1ULL, 0xFE850EB53321AAE6ULL, 
            0x3DC2C675BF9539E2ULL, 0x39E1F16476F80A3AULL, 0xE55F1B0267750F5AULL, 0x28E01D6DEA344602ULL, 
            0xE22C377F8103F241ULL, 0x1697AD57F6797F0DULL, 0x118C411AA506430DULL, 0xAB625B5552CAF8C8ULL, 
            0xC9E557D389375929ULL, 0x421A837F2302FD8AULL, 0xC8C1067D56B60D6AULL, 0x111896AD4CE51A7EULL, 
            0x977B55431FF7FE58ULL, 0x91CC02C2EAD82CB9ULL, 0xE5E348D463FD8333ULL, 0x7B3825BEA2727A9FULL
        },
        {
            0x6A5503C8B625033DULL, 0x9A5972814E8ED7AFULL, 0x3850F05C9AFC88D5ULL, 0x01168AE3478D8634ULL, 
            0x889A4A2D3F099B7EULL, 0x3D6C6683C9E152C6ULL, 0xCC5B67C7587D144CULL, 0x63A279931EAC0288ULL, 
            0x3DD897A03C133309ULL, 0x8023B8A47626516EULL, 0x7C44661A265063C0ULL, 0xAF13368491900778ULL, 
            0x33DA0C4017027F92ULL, 0xFEAA6E7F291B3F54ULL, 0xA282ED922E726F89ULL, 0x3FC8F3A87F34C209ULL, 
            0xCD1252AE23802989ULL, 0x32A0F47BEF778A8DULL, 0x27A737394FA00D36ULL, 0x3591F73D39187BBAULL, 
            0x76ADE38FF04BFF0CULL, 0x5D6E5F0517C8976CULL, 0xE40DCFC1EA9F3AC7ULL, 0x37FCA120DBAF367EULL, 
            0xD04C7294BB54E616ULL, 0x1AB38BAA6E3AFA6EULL, 0xE18A5AAD359A1428ULL, 0x9385DBB4CDFA44D8ULL, 
            0xC0842F8678820E4CULL, 0x06724612C02635E1ULL, 0x20B99CD359561939ULL, 0x15ABB973871693ACULL
        },
        {
            0x949DBFFB13E7FAEFULL, 0x97BD57CD5CCA5784ULL, 0xEBCD16A71C9C3CCBULL, 0x12A23F5FD99198A6ULL, 
            0xD060370A5F4BB9AFULL, 0xE6F30371F96EE4DCULL, 0xF765927EDE7A3E2EULL, 0x3C0E19966BFE2EE3ULL, 
            0x65F864FAE60980C7ULL, 0x52BD1CAF54D37C9CULL, 0xE4FC7E3DC5F68338ULL, 0x23385CEBF94AA120ULL, 
            0xD034D1BEE01AA82CULL, 0xA915B7749E549731ULL, 0x031F5A05E984F5A2ULL, 0x1AFB74193347E69FULL, 
            0x62C964575B5022A0ULL, 0x89C631E0363F7A53ULL, 0xBE49F71C94FBE3EEULL, 0xE5DECC39D6617719ULL, 
            0xEEA87F007590CD23ULL, 0x635B7ECD7FB2ED9BULL, 0xE86593379661C209ULL, 0x63D6B6C76E2A6E1BULL, 
            0x3E1CBA94AED97D11ULL, 0xBDD9E7F66D9D6EAEULL, 0xE806208F2D5288B3ULL, 0xE0C6AAFE3D6912EFULL, 
            0x6BC4734B9E99CCCBULL, 0x287780729918F71BULL, 0x6B9D0DB2C798C515ULL, 0x11AEE1E1034CF9A3ULL
        },
        {
            0x1BB0500603286E24ULL, 0x36BC4330B7594344ULL, 0xA2DE80A80D11368DULL, 0xEA98F9296E9A50E6ULL, 
            0xF793BE203DF06C4CULL, 0xA9D8A1B101008C4FULL, 0x6A056CEEF5BD4917ULL, 0x84ED1F7724D96992ULL, 
            0x3B2D8394509E4C15ULL, 0x7E04BD77F1E2B58AULL, 0x331EE088C072BA1BULL, 0x45883CDB40170E74ULL, 
            0xE46ADB1CA9BBAB89ULL, 0x3836CB7EE159D036ULL, 0x5AAEA1021D03986CULL, 0x5ED183E50AC85123ULL, 
            0xF2ABDD7330F8B8CCULL, 0x9E4FEAD1C36FC6F3ULL, 0x11949D96814DEBF7ULL, 0xC198761CE700507CULL, 
            0x72C4E01246BB3C9EULL, 0xEF82F0375D356EBAULL, 0x131354255CB4B21AULL, 0x3D5BF1F3C66EF397ULL, 
            0x50BB47A4C1D5B626ULL, 0x3C8E0F6840D477D1ULL, 0xB70FCAD24AE0611DULL, 0x902604FC980BCD2AULL, 
            0x3FE571E72E80B75EULL, 0xC030BE5D929427B1ULL, 0x2618F40298910259ULL, 0x56DF7328F72436F0ULL
        }
    },
    {
        {
            0x92E3D20BD1233E3CULL, 0x5814A37C5CE1B545ULL, 0x20C331B2CD0FF75FULL, 0xB4ECE31E9B349F1AULL, 
            0x45C217542ECD5F8FULL, 0x84C79506F9DD850EULL, 0x69BDE5DC92E9F5AAULL, 0xD3AB5D7E85EA26D8ULL, 
            0xDC5A0A2D8D87C9C7ULL, 0xAA0A0A28F8BCFFA6ULL, 0x245D32075E61BFB0ULL, 0x53B0CB0F95633012ULL, 
            0x00345F5F5C7B8018ULL, 0xE4DD05DE826F0EB0ULL, 0xF63CBBDF5C5DD434ULL, 0x28059656A5A4DE20ULL, 
            0x4FECDB0B287FF6B6ULL, 0x08C6981FF1CF8A2EULL, 0x851B251DBA5584DCULL, 0xC586B421EC2B3531ULL, 
            0x73A5CF4BD27EC8CDULL, 0xCB9B30E2E6AFDE9DULL, 0x7AF26E13FDD21506ULL, 0xF419E3312F124B8EULL, 
            0x0E986227FD32C9F7ULL, 0x22EC29D01EE2A180ULL, 0xD774CBB18689369BULL, 0x64603043DD55F106ULL, 
            0x9510E1575C0EA09CULL, 0x46E11C6259905DD2ULL, 0xEC70F5ACE4165E07ULL, 0xBEEE7952AE5FA009ULL
        },
        {
            0xC7232ECC91DCB222ULL, 0xEF55D454D07C4206ULL, 0x98EBE26A65B8EB81ULL, 0x0AAF9883395276E6ULL, 
            0xE717A9A0BB6CCA03ULL, 0x069E8E127D803E33ULL, 0x38DF3FBD78B337CFULL, 0xFB4D582652552248ULL, 
            0xBE8099C9AF6BA7ACULL, 0x34A65855C62FDBAAULL, 0xCA526C387E07138AULL, 0x57ACDB543BA85A1DULL, 
            0x53F3EF6661EE44F1ULL, 0x8A61880F5142B58CULL, 0xCECC9B70BA5941F3ULL, 0x2EBB598E06FEED0EULL, 
            0xFFEE74031E1EE23AULL, 0x8BDACEEAA7FD85B6ULL, 0x5B0042F1C498C6C1ULL, 0x6AF17003C76082ADULL, 
            0x234EACB4E58FE5D9ULL, 0x2734EE761530B2F6ULL, 0xBCC1471BD2C57077ULL, 0x34CF47ABE034FB2BULL, 
            0xD7EFFB5075604A56ULL, 0x5F32433304986A0BULL, 0x5B6AF5532AEB01EEULL, 0x09FD4B2D11221382ULL, 
            0xDB3BBA1DAF6CB062ULL, 0x13E948257D222EE0ULL, 0xDFCAADE58AB9A686ULL, 0x970BAE277C51D41CULL
        },
        {
            0x5194EF7DEB27C335ULL, 0x09683FFD43A44CFBULL, 0x56C397EEAA3F62C4ULL, 0x8EB2D7174B098BFEULL, 
            0x5209D887B05FE083ULL, 0x83BD32E45ACDD037ULL, 0x4140FD653739EA31ULL, 0x06A6420D097EB939ULL, 
            0xE2DD722AC4D31FE3ULL, 0xFD8065BDBDDFEA2CULL, 0xFEE2180C894A3960ULL, 0x98272EC977761060ULL, 
            0x95C924C3E571D52FULL, 0xA8746B7B15FF5B6EULL, 0x9251AF6E5E8F5861ULL, 0x5830E44F8D4A0F89ULL, 
            0xEE5668F302DAA769ULL, 0xA8B012903C8C1B5AULL, 0x07C12FC236D749C9ULL, 0x7D26707E3EF5BB88ULL, 
            0xD64C87B4C11CC89DULL, 0x426C24F35CEAB0A6ULL, 0x726E4F45FD0A8468ULL, 0x02EA2413C0B930C4ULL, 
            0x2C2F917613D6CAB7ULL, 0xE4D304749E4353BDULL, 0xD7EADEC6AB93AF3BULL, 0xA0A19E997ED56C9CULL, 
            0x6F89C2465EF7E832ULL, 0xC05CE56EC3ED9D1CULL, 0x752F92F0A2075F52ULL, 0x760547528AE666CDULL
        },
        {
            0xE03558BADAB0E45BULL, 0x7542DB761BBDB21DULL, 0xBADEF6092957F7D8ULL, 0x01C680C8096C568DULL, 
            0x0C98266F02A21AB3ULL, 0x0FA5B04BC57966F6ULL, 0x2ACF87AC03DF2EF3ULL, 0x2988DD91A3012D64ULL, 
            0xCEB743E20AE27849ULL, 0x0E13034C14E6F23EULL, 0xF12E52D340CD7EF9ULL, 0x5AFA703B24C460DDULL, 
            0x7349CD928FBF8F92ULL, 0x694CF2B0C16C8DBCULL, 0x0906A1C7BBE0EC64ULL, 0x52EE992CEEFE9D83ULL, 
            0xB3C07E40274FB876ULL, 0x6661B178F9E711A2ULL, 0x1261E485B141CB91ULL, 0x0E09DFF49DAEBAC4ULL, 
            0x961E415FD73ACAE3ULL, 0x883A1C6DDE54F8ABULL, 0x3B3D7E752FCE2F7DULL, 0x5538F466EB67974DULL, 
            0xB3A88C50BECCAD35ULL, 0x6E02694DE233AF52ULL, 0xE9412FE837E3CBA4ULL, 0xABA9A996468ED7A1ULL, 
            0x0C898E97E6C90F65ULL, 0xA2B6D2D746556606ULL, 0xE5DB4CCE10B21767ULL, 0x1F34A2C0C36A8886ULL
        },
        {
            0x92ACD8A1C34B018FULL, 0x5CBC598C813B0F6CULL, 0x43FD4320895B3AA7ULL, 0x064C5CF6523A6F80ULL, 
            0x0EAF651C3CD1FD0BULL, 0xCAA67F3FB8AEE5B3ULL, 0x9EFC60C151A1FBE6ULL, 0xD195A573D65BB5B1ULL, 
            0x6F9E0A2D668B1C7FULL, 0xAF8CF004CE057034ULL, 0x73E18FABDABAAA2CULL, 0x4FCA99995901C20DULL, 
            0x250C85B267A862D0ULL, 0xB2D05CA6C36A1F06ULL, 0x157606BF36368586ULL, 0xB02C0FE9BDE316EBULL, 
            0xBBE3BBB9BD6FFF7DULL, 0xAD8E798C0E8C9DD6ULL, 0xB5339287B74E008CULL, 0x2C14D3A9607C2D74ULL, 
            0x424B7348A046027EULL, 0x82B892115C2E4E6FULL, 0x6D4FB796FBB82F03ULL, 0x8D513A6ADDB204FCULL, 
            0xA90AD03E31113B7BULL, 0x5884EC39CDDD9E01ULL, 0x01526054A8BFE29BULL, 0x0F0E42757433A5CCULL, 
            0x45908D69D179BC40ULL, 0x53BD5C6DF8FC153DULL, 0xAE56FF8487F67604ULL, 0xE6DCE8EA92FA22D4ULL
        },
        {
            0x049905116C30B17FULL, 0x3392E45BA54E9853ULL, 0x3E4B417509C1E508ULL, 0xC62B83155D56A9A4ULL, 
            0xCFD4DBB9E182C52EULL, 0xAF14F12452E6C4DEULL, 0x89F81134E621DDBFULL, 0x112B02DBCA90811AULL, 
            0x223896201795C7B2ULL, 0xBE0BB17B181003FBULL, 0x77D9F6849ECF2FDAULL, 0xE15BEA1401246F0FULL, 
            0x724CAFAD7E8E208FULL, 0x46DB1DC7EB2AD6AEULL, 0xA49852182C6431ABULL, 0x941E984722EAF0C2ULL, 
            0x36FDB28B7D5B19CBULL, 0x3386F2B831C1B303ULL, 0x6174025EE42593CCULL, 0x69273D8CB56EEF40ULL, 
            0x963576CE334443BDULL, 0xEF66DCB8C709CB58ULL, 0xCD84001A1C23D2FFULL, 0x0D5BFFBD5B859D24ULL, 
            0x91A0CFFA8567E4CCULL, 0x25E28E5DA8F64C03ULL, 0x17D0F30521A72501ULL, 0x4C0EE7ADB989C5EFULL, 
            0x9F1A3B3D23CD88BDULL, 0x4D88C26FDC8D71CEULL, 0xBB4A09129C3C8BA9ULL, 0x682222F76C0ED496ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseEConstants = {
    0x29E2014EB56AF90AULL,
    0xA9AC86142A1F8656ULL,
    0xD54B3273F9279871ULL,
    0x29E2014EB56AF90AULL,
    0xA9AC86142A1F8656ULL,
    0xD54B3273F9279871ULL,
    0xD5DCF4DCB4DC0398ULL,
    0xE32BD3BED019926EULL,
    0x4F,
    0x97,
    0x4A,
    0x76,
    0x24,
    0xC7,
    0x2F,
    0x83
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseFSalts = {
    {
        {
            0x77C73094B1FB4A61ULL, 0x3C41D7E164A9CFB2ULL, 0x59F8C999F9733C75ULL, 0x12BFB458E81ED3DFULL, 
            0xFC284DD42FAA586AULL, 0x640DBE1E3365D1DAULL, 0x7FE34FEFE0FE3DAEULL, 0xDB2FAA770E17F9A1ULL, 
            0xF6893D3D6845D72AULL, 0x8E36D500052EC1A3ULL, 0x9DF84AC1BA70C78BULL, 0xA8083772C069DA75ULL, 
            0x6E57390DBA3B64ACULL, 0x739924BAFC4E67C6ULL, 0x5AEF61139C86F671ULL, 0x716DB271E65026CBULL, 
            0x5B2DF9E1ACC84B2BULL, 0xCEC92E829D6DF495ULL, 0xBDCB64EF266C9D9AULL, 0xCB865F1D08FBC690ULL, 
            0x4B5F9C68E658AB77ULL, 0xC39847A994353ABEULL, 0x7FB6B4F0CAF2C528ULL, 0xED703762CE0F6C81ULL, 
            0x01244AECF94862C8ULL, 0x5C4727BD8F0B8AEBULL, 0x2946F5D292E75EAEULL, 0x866953D84A4B96BFULL, 
            0xD882265124FA7DD0ULL, 0xF22D34E74DB6AF31ULL, 0x2BD4DBC344B51EA6ULL, 0xB716A6AC25DF2F3AULL
        },
        {
            0x29057D7AF79784FEULL, 0xFCF2E43EDFC3BB99ULL, 0x0E3B3FBF05D2B9ECULL, 0x7957D3A6D0D019C5ULL, 
            0xD598451A76D42A1CULL, 0x3D52262961AEA228ULL, 0xC95A2908E520C0D1ULL, 0x226353E63D2983A9ULL, 
            0x5A9C89EBDD683396ULL, 0x259706F89039A61BULL, 0xA13D9C168A059589ULL, 0x441A0FD932A378E5ULL, 
            0xB09C4358006999ECULL, 0x393C6CDE0BFF2EA2ULL, 0xDA038C006E28E21EULL, 0xD68849D186CD869AULL, 
            0xEC6767D63145B85EULL, 0xEC692E3DDFE3A655ULL, 0x3FA722A842695904ULL, 0xCDD7307F003AD477ULL, 
            0x44C215C467628906ULL, 0x09645B0BDE03B0CFULL, 0x883320A952E4E8B4ULL, 0x14341AADC3EACA65ULL, 
            0xF3328B5F4EF892E9ULL, 0xCF4061621EB3FCB0ULL, 0xC5BD5F70A229E926ULL, 0xFD5042BF3A03F2B4ULL, 
            0xE99A754D9FD035E7ULL, 0xBFECA191F3655729ULL, 0x41553CF61926AF31ULL, 0x2D17BB2816171E9EULL
        },
        {
            0xDF1C7B8C2960074FULL, 0x2768BB12627EB2BEULL, 0x91A11F3A0EB53F9BULL, 0x4BEEFDEBB72848FEULL, 
            0xC7858C3BE6ACBFBBULL, 0xAFBEC869C54B7741ULL, 0xA3C4E2A10D1D524AULL, 0x1639CE63AFB349FFULL, 
            0x8AE05D2B79C34DF1ULL, 0x9C77659857E13A95ULL, 0x02BF98FD62BA937FULL, 0x50261DE96FF6CEF9ULL, 
            0xC6EE1E9D134F143CULL, 0xEC1E888C578255BDULL, 0x6F66F82CE39A7218ULL, 0x9ED9E53805DF8299ULL, 
            0xD9BA136F3DC30894ULL, 0xF6EFA8A1D4EFC8DCULL, 0x5B96B952F12798A5ULL, 0x76255F4A1BFC0D56ULL, 
            0x07309210C5363743ULL, 0x5B4E8CB929E5414CULL, 0x98C1F54E1597CACDULL, 0x1F6F602C771A569BULL, 
            0x197B430FEC8404C1ULL, 0xF82B10728AB0B255ULL, 0x7898A80F90A91C84ULL, 0x60D5F2938399D50EULL, 
            0x23B2A86394F083B3ULL, 0xA9C84C33A227B53BULL, 0x9EE5479135CFB8ADULL, 0x60DEC4972493BDFBULL
        },
        {
            0xD451D2993D8E530AULL, 0xC02B20FA248C156FULL, 0xB1B3703BE186D8EDULL, 0x0044DD269803DE48ULL, 
            0x1DE51E2B69D6F0AAULL, 0x07D18B9862DEB02CULL, 0x7BF7AE7DA8082CA6ULL, 0x5FDFAA1D7AD343B1ULL, 
            0x3BE2B18AFB109CCCULL, 0xA666393D4E9043A8ULL, 0x9F3D1A548100CBF9ULL, 0x8BD96F5FDD6AC092ULL, 
            0x7D9AAA4BD03FF4ADULL, 0x25C9A442787C0892ULL, 0x2497F91524229971ULL, 0x330C77773762E4B6ULL, 
            0x5802B94C0B388180ULL, 0x48B0A119DB716E3AULL, 0x706BE01EF48D3825ULL, 0x6BD94F3215A58DA2ULL, 
            0x8AF39078542C0FB4ULL, 0xE255B3494E4A5324ULL, 0x0B0CFB566C3F1D2FULL, 0x5FAB99300C7DA410ULL, 
            0x672335A76A977DA6ULL, 0x4B646906C63EA50AULL, 0x9A058FF98CDE7CADULL, 0xBE93609795A07DA6ULL, 
            0x25CB4F6490F91E03ULL, 0xC85B67F8EF7C8B35ULL, 0x2ADD9C8EF05CD4E2ULL, 0xAB54BE069A233CA9ULL
        },
        {
            0xE5FBB23E3C5A5D89ULL, 0x2DC0EDE20B5679C9ULL, 0x47B000874BE802D1ULL, 0x4C7CA2BDA3DB57F2ULL, 
            0x09D4C894F0AF5BBCULL, 0x63337C87AE236615ULL, 0xCED1DB31CCA82FF5ULL, 0xDF07702E1E7121F4ULL, 
            0xB8FF09A7EBB66B8EULL, 0xAA5BFB6643AD7F3AULL, 0x1D0C99CB2B61E9E2ULL, 0x00A5924EF6AFE0BBULL, 
            0x2BD8825AE359C860ULL, 0xC6835975D97134A2ULL, 0x2EF9D16E2AB63B63ULL, 0x4650A8B8C452DBC9ULL, 
            0x9885EB260658ED45ULL, 0xEBA1177A20B98353ULL, 0x9788A169AD90BA96ULL, 0x298AD8BEA56DE7D0ULL, 
            0x47DDE8CF6AE809D4ULL, 0x99E76557BDA69B5EULL, 0x283193A3BB73E1E0ULL, 0xAABA58C013816F2BULL, 
            0x5E10F0192C946BF6ULL, 0xBD992529173C953CULL, 0xDAAA0871F23F0C61ULL, 0x609C694B12CB2DD3ULL, 
            0xFB87AC6130671C3FULL, 0x4517E1C4A0C7ACE8ULL, 0x42309730A0BE5160ULL, 0x5BF7AF63415C6E95ULL
        },
        {
            0x7770EF2804C37C67ULL, 0x40A13F220D4531A4ULL, 0x44C1BF8B5CDB36B1ULL, 0x6C94DB61FA0D9915ULL, 
            0x12AD090B3CE13F12ULL, 0xCB1F00C961173FF2ULL, 0x7A8A50A6F139BDC8ULL, 0x0F440BA62ECE165AULL, 
            0x8E83A3A306F46E95ULL, 0x29BD3E132ED958A2ULL, 0xB4B6B2103FC5ED0EULL, 0x896DDA69149870AAULL, 
            0x56B564ECFEA0EB5FULL, 0xA6E0A5E5DF784F59ULL, 0xB9291A6CE4002B38ULL, 0xFA967C631FB8860FULL, 
            0x570DD2335C9FBB36ULL, 0x6A468410837B17DDULL, 0x5F4FFDD5D440D0D2ULL, 0x59CE3CE2B0F113A6ULL, 
            0xB181DBA9A5588824ULL, 0x6BB40B756F025757ULL, 0xA696043DBC21BA3CULL, 0xC8AB95D9554A347CULL, 
            0x802100EA58414F51ULL, 0xB2F378B886E808E3ULL, 0xB58D3E84225A845CULL, 0xB6549619CFAFA96EULL, 
            0x012AF1A0620E824AULL, 0x975E7A31C8279C91ULL, 0x99B9C2CAA42444F7ULL, 0x4B05685AD8B17AC1ULL
        }
    },
    {
        {
            0x139F341AF422A240ULL, 0x8894E12BC18D9874ULL, 0xD6082EDF61E98CBFULL, 0xC26626A32AFF0A01ULL, 
            0x086BB6253E81492AULL, 0x814EF486F3904633ULL, 0x8C8B914159F0570CULL, 0xA2866E37F73394FCULL, 
            0x0093C49FEEDDDDE9ULL, 0x3977844B3CBBACAFULL, 0x5DAC3179656292F7ULL, 0x4F192AF355B22AB0ULL, 
            0x3CCF8ED30040B848ULL, 0x4FC87E93B3592908ULL, 0x10DAD5C5A3F61E92ULL, 0x0600905FE230F656ULL, 
            0x91FF057C5C5CEEF6ULL, 0x452397EECB414E1AULL, 0xE5C3A2928A79343AULL, 0x078BF1EBC22547C5ULL, 
            0xCFFF665EFF578AA8ULL, 0x947113246851BB4DULL, 0x251E755B0BF4209DULL, 0x804025E8C36C7860ULL, 
            0x7E8CA0DAFAC2CD6EULL, 0x7CC7F049F68F3E98ULL, 0xAEC30306A877477EULL, 0xC9F7D16B31DA7BCFULL, 
            0x417DF8484CAD2FA9ULL, 0x631319CB64AD8AF6ULL, 0x12CC3E6E79A02C71ULL, 0xAD364C51E5FE6102ULL
        },
        {
            0xE6DE99FB4AA00C4EULL, 0xB2B98CD30020BC92ULL, 0x94E6A417BB601046ULL, 0xB29F6225D32189DAULL, 
            0x00E573FB53238D22ULL, 0xD8EBF3905C7CAFADULL, 0x75D2695F7414F63AULL, 0xFE192963FF84C38AULL, 
            0xCE4BF54C31FA59CAULL, 0x3FC6E56F0BFE1ABFULL, 0xED6CB197F1C4FDC3ULL, 0xD2C1388987C595EBULL, 
            0x5BA8451A9705F2E5ULL, 0x9EF8681D361DEBA1ULL, 0x83C75748D203E67DULL, 0xDB017981301B8164ULL, 
            0xCAE015B18A29FE9FULL, 0x1C3BB58AA7993945ULL, 0xBEA3F4144F542C4EULL, 0xA20BB83FE3FA53CEULL, 
            0x7696F76C49BDABB7ULL, 0x18DB4A4B4B7ECF65ULL, 0x3BA6EBDA5AB8270AULL, 0x527C458E4C4917F3ULL, 
            0x6255F65FC3149606ULL, 0xD88EC033DBD5BCB1ULL, 0x735A323692C5CDFDULL, 0x4B3E5D4B5D4590BEULL, 
            0x633E560BD544DFF5ULL, 0x8E88378820824F83ULL, 0x8A9DF26290774516ULL, 0x24C82C3E90AE29FAULL
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
            0xD14EF5A44A495E62ULL, 0x26900F6A8B34D17FULL, 0xC6E454D4705B57A4ULL, 0x134DF72AC923F754ULL, 
            0xF841B86418E20363ULL, 0x44FB36A43528D26EULL, 0xFC572EDD99D6E2CCULL, 0x918203984F778ED6ULL, 
            0x05FBD420ADFA9F9FULL, 0xD750E50BB2C27F14ULL, 0x80A900BD827E98F6ULL, 0x59F783B8FF5C70B5ULL, 
            0x1D00EDCC4C052A50ULL, 0xE0297D09A0FBE5E9ULL, 0x5134BA7C055383DEULL, 0x94835EC8B27AC0ADULL, 
            0x1537DA3E2100B718ULL, 0xAC56DB8E72F30E3AULL, 0x8FC8BEFDDED96F9DULL, 0xA6FADCE62F291DD6ULL, 
            0x9C663DA667B3A55EULL, 0xBB67D42F15C493D6ULL, 0xBFEEBEA352424EEDULL, 0xB9CFC84A9D4E9618ULL, 
            0xD3C2D7A1141107D5ULL, 0x8E2E58FFDEB0ABFDULL, 0x5F66EBFB0EAD61B1ULL, 0x8CEA8543B9D7BCD4ULL, 
            0x58FDEC7D971C4D80ULL, 0x2DD97183169B7D30ULL, 0x3EA0C7E6524DD906ULL, 0xA69688938584DE01ULL
        },
        {
            0x06780FDB866888A2ULL, 0xC90EED98B744A9A5ULL, 0x7760C6E447595FAEULL, 0xB0078F55B9F2EF5FULL, 
            0xD2F61FF1C1740121ULL, 0xD925F3B2C1ABECFBULL, 0x6BFE23A0203A205BULL, 0xA778C379A853A7C5ULL, 
            0xADB5ED89D093F0B8ULL, 0x1F4B695EBA2A19FBULL, 0xF1486B3DE74AE216ULL, 0x3716A3AB8847AB93ULL, 
            0xC049771900BF0699ULL, 0x3FFB7429BF873633ULL, 0x6A4240255424DEA7ULL, 0x04A445931CAB1590ULL, 
            0x8C6D5772F79E19D4ULL, 0xFFB2A8A2B6770661ULL, 0x9765BD9D1DF8D3AFULL, 0xD5E5AE5A02C741E1ULL, 
            0xF411ADD9DB7803D5ULL, 0x4582932FEF79529AULL, 0xB0EB17EC4AE0C9BCULL, 0x5C5484D270FCA614ULL, 
            0x384B70E3CFA62277ULL, 0x2DA0C43ACC231ED2ULL, 0x88481835765CFF56ULL, 0xD195F0A36B313C2EULL, 
            0x558B340290402846ULL, 0x7DC43158309ED845ULL, 0x839BE98D3C0183A7ULL, 0x8ACFB22EE95D7F8EULL
        }
    },
    {
        {
            0xEE4A3205C2E52120ULL, 0x48DB4B6D883E0143ULL, 0xF15D4AE908EA3D2CULL, 0x0458B4095BB3533FULL, 
            0x958C594340BCFA7AULL, 0x9442229E4BD4D3BCULL, 0xA0A182688AF5FE10ULL, 0x3E5AA040C5F8942CULL, 
            0x2F29C4D38068FE4AULL, 0x5E62518613FD2B54ULL, 0x9D014DE1430CFE84ULL, 0x9A37056007B8C8E9ULL, 
            0x2E83D0DB0D18CED0ULL, 0x3CC0E1CAD137C1F2ULL, 0x74381C92BDF04C6AULL, 0x7E17E0AA75455B26ULL, 
            0xF48ECA70BAC16B00ULL, 0x5F2B74F2CB856282ULL, 0xF2CB7E454B993031ULL, 0xD398E7EBD568D8DAULL, 
            0xB9A0A207B19D5AC3ULL, 0xE529CF2FC30E879AULL, 0x24A854407907B78AULL, 0xD6BE152D8F117F52ULL, 
            0x0F2E3A71111F2D9CULL, 0xD66522F2F0E6A025ULL, 0x1C60C8705F287856ULL, 0x952FCDC547C9D485ULL, 
            0x03060B0B2BB241A2ULL, 0x666215B0F041B9E4ULL, 0xE0B5FBAEF8389126ULL, 0xB318B17C4C341DA5ULL
        },
        {
            0x33F301CA66F2E232ULL, 0x36CD62B2E3C0C35EULL, 0x49D0D2CB2A199459ULL, 0x9DC2CC770A167B3EULL, 
            0xA68C11D7EA745D3CULL, 0x600A6DDBC2D82107ULL, 0xC53B7018E191783AULL, 0x0B4943236478E555ULL, 
            0x225C4C9BE244E224ULL, 0x2CB1A503C0744A35ULL, 0xCB0F8DB79DA45F8AULL, 0xC80EB028DDB86F91ULL, 
            0x2D20EDBA2F93D087ULL, 0xCA5B9B5980DDA34FULL, 0x5511C868E7F79B60ULL, 0x75E669BAA0790907ULL, 
            0xBC507BA035C7BF8FULL, 0x6C339B7C645D0796ULL, 0xB8CA6675EFC78216ULL, 0x565EB582FA12624DULL, 
            0x87DDB09E09EE24BDULL, 0x5C0A450B0851568BULL, 0x688AEB1E89FF0FA6ULL, 0xC72D06B35BB75F43ULL, 
            0xA184D9CBAF5169BDULL, 0xDDD2837D815B9869ULL, 0xECE0D44FFD7EB177ULL, 0x4A9CEFC924920308ULL, 
            0x51FA744174A38FEEULL, 0x01845FB4FEAD500FULL, 0x788D16C6B62C635AULL, 0x3B69E073DD25218DULL
        },
        {
            0x219066A6E3956D6CULL, 0x434B9A602A8EBF48ULL, 0x409DB257C86D3343ULL, 0x969702623A3429DDULL, 
            0x62976E22DBB104C2ULL, 0x45FBF26B74ACE716ULL, 0x40B5A15E5D7F3532ULL, 0xECB6725A43D040D0ULL, 
            0x807C165AFB662687ULL, 0xFDB2BF0F78686B6CULL, 0x08ED20537657E523ULL, 0xD3DAD99889F54B44ULL, 
            0xDD2C05E1A30BAEADULL, 0x42F4106908B3A7F7ULL, 0x2A805BCFE8C2E0C1ULL, 0x149261BF3BC7D8F8ULL, 
            0x67D7768D2246FFBFULL, 0xF4789FFDBB8F99C4ULL, 0xD7516B532980CF10ULL, 0xE118E6A112E9350EULL, 
            0x63A102031B5D6AC3ULL, 0xDB28CE345B0FD3CCULL, 0x66DAAFD007D5CE83ULL, 0xF771082D3AD3EE0FULL, 
            0x7504ED7A627BED2CULL, 0x145EB83CD0877699ULL, 0x91E38A622C9C4F0EULL, 0x49F82CAC81390455ULL, 
            0x7C6C249EC4C20DF8ULL, 0x8E9B54DE569744DBULL, 0x54D9758A000D6862ULL, 0x94C761CB21ABC3A2ULL
        },
        {
            0x16A6B53A1F555528ULL, 0x9C442F81A27A2940ULL, 0xCD6EDBE57A401191ULL, 0xED8E941639D5668FULL, 
            0xFF66257AE751C062ULL, 0x0270284C99CA914EULL, 0x1547ED81B90B0BEFULL, 0x2B6BD18448DCBF0FULL, 
            0x0E1F0D3CCC13015DULL, 0xABFA742EE6B0A4FCULL, 0x2C467CF95E662B78ULL, 0xA6D06F6ED184D466ULL, 
            0x0C633F3E54482581ULL, 0xE1180754D58B976CULL, 0x81783E7F8F9D0F6FULL, 0xE43A700A00CF2C10ULL, 
            0x2A4AC1D9BEB3179DULL, 0xA20F98F8990A5BAAULL, 0xEF5B445E187C9885ULL, 0x59E1EDE265C42C36ULL, 
            0x9DDAC429925EA262ULL, 0xA469EE1EDA4C62F7ULL, 0x30EA9A817D7F3423ULL, 0xDA78FC5370C39388ULL, 
            0xDF6CE7410726A07BULL, 0x658DC9DCB58AF1AEULL, 0x8FB9CC9B71AF8D07ULL, 0xBFBAEC0A91CAFA46ULL, 
            0x9F436191218B9539ULL, 0x61CA74B8E584842BULL, 0x96C4412FC08E3287ULL, 0x186C89E80007651DULL
        },
        {
            0xE6DD0A83F69D0383ULL, 0x04D5F054F6D08149ULL, 0x79F56FADF469A1C1ULL, 0x0D30C18E8CC75A69ULL, 
            0x7B7CCAB9BDA9BCBDULL, 0x10EA3E0C4EC88DDBULL, 0xEC24C2AE8231976EULL, 0x0C238E7DE3C1DC5CULL, 
            0x9CA3F2E6F5952DC7ULL, 0xD6CC299BC21F8B80ULL, 0x6A0E6400E7134D25ULL, 0x2C32C062F8526D74ULL, 
            0xEFF4E00DA037CD88ULL, 0x557932330E96FAD6ULL, 0x13495943CB667B5FULL, 0xB4AEACAE76594A9BULL, 
            0xADE222B76CF0D7D0ULL, 0x7D20E9F96717F024ULL, 0x96148D40CC61E900ULL, 0x91097C0B8B060E06ULL, 
            0x2F524FEB7EF5E261ULL, 0x119C7891DCA6958FULL, 0x8090647744CAC0E0ULL, 0xAFFDE93FA891AED0ULL, 
            0x17307B9839726DA7ULL, 0x335A496F52055EBEULL, 0xB520A197A0E5D394ULL, 0xF8AB78259D6EA616ULL, 
            0xF09736B5C52D36D0ULL, 0xF683A9D48503BA29ULL, 0x0E8C7ED854A33495ULL, 0x7F5812B7D20A9E50ULL
        },
        {
            0x8B3341574675310AULL, 0xBCA8D0389B503A5BULL, 0x2C314AA85553D426ULL, 0xF45D77E9FA673EFAULL, 
            0xB79B2B9253E22F41ULL, 0x0CD9E789150215DDULL, 0xD3801304E5A044E1ULL, 0xE7447DC6B7FBA5AEULL, 
            0xD5B2D5D755DFBD23ULL, 0xDFF436CAE8A01E58ULL, 0x7C85AD51567AC46CULL, 0xF2C4141AC97D4224ULL, 
            0xF9D41D18C7A34360ULL, 0x372D0649F6F79F2CULL, 0x36DBDE2187A6BEF3ULL, 0x4543017C84D4FAB5ULL, 
            0x51FAD5E5402A057AULL, 0x827306F4DC4FA75CULL, 0xAC8DE976A7295AFAULL, 0xE8E81E5BFE24644DULL, 
            0x2D3FA6C1F22F3D27ULL, 0x83BCA26E4AFBE200ULL, 0x4992D17754A9DE6CULL, 0x53B7D837EAB6985FULL, 
            0x6CFB5C902CACE835ULL, 0x4D4BBA3D224083F2ULL, 0x67DA0D7C4316A3A2ULL, 0x5160450EBDC6493BULL, 
            0x93446805350100BFULL, 0x8BA50930FD71EDB1ULL, 0x55B651C8F1C483D0ULL, 0xBD68211DB02BA0DEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseFConstants = {
    0x16DB9650DF0D1041ULL,
    0xD5040B36DA58A101ULL,
    0xA09F04E31441A315ULL,
    0x16DB9650DF0D1041ULL,
    0xD5040B36DA58A101ULL,
    0xA09F04E31441A315ULL,
    0x26F328660E33E5ECULL,
    0xC40CC41EE8626EA1ULL,
    0xAE,
    0xA3,
    0x7C,
    0x8C,
    0x6A,
    0x95,
    0xC8,
    0xA6
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseGSalts = {
    {
        {
            0x8B9462F8990E3670ULL, 0x0113D742C8C2BE8CULL, 0x80B8BEAF7F8DCEC7ULL, 0xDF1A00E0D6E3E157ULL, 
            0x9F7502CD80A7C4B3ULL, 0x0D680381D13E5AF5ULL, 0x46F414165F7C32E4ULL, 0x476448D190C3C29EULL, 
            0xA1B29649685FEC95ULL, 0x567C0C80106E3510ULL, 0xC5CCF61332CA5CC8ULL, 0x57C596540FC99664ULL, 
            0xBDF6AAE05B58E984ULL, 0x566E308274F01700ULL, 0x31FE52324D0F3157ULL, 0x08BBC6CD84EBDDF8ULL, 
            0xCF75D011EFD55B65ULL, 0xABC5C501D0A7B239ULL, 0x3F7133E0A0AC4B5FULL, 0x108C1C5695F0A6BCULL, 
            0xEFB33E486401ABD0ULL, 0x742EF878B318A9AEULL, 0x046677430A2D2272ULL, 0x2807542C1A4F2140ULL, 
            0x6AD9E90AC7798178ULL, 0x0772301D39904A6EULL, 0xF313E71FCA6F8A8DULL, 0xD4A7A17F257DFE60ULL, 
            0x1D4BFB7676106154ULL, 0x457F58E1C164B815ULL, 0x0FDB458DA48512B7ULL, 0x7890DDF66237E54CULL
        },
        {
            0xB65DE1FA567B375FULL, 0xC89C1B3F870F4567ULL, 0x01F331C13E6E0AB0ULL, 0x8F455ED7234A412AULL, 
            0x72B4E93E142849EFULL, 0x50906588FEA2DD76ULL, 0xD4FDCF0E91F7525CULL, 0x8338A862162D3898ULL, 
            0x68D52C70ACF246A8ULL, 0x5E6C275B3DD9A338ULL, 0x8A16163B450D1DBFULL, 0x66BE48DF5281C19EULL, 
            0x563A7D0CF283D8FAULL, 0x88D4C4FEC935646CULL, 0x8F22F680E8802B84ULL, 0x9A82E37D0047D549ULL, 
            0x19CAD1DBFB64DDE8ULL, 0x75CA0D306E4336DAULL, 0x7BD37723FCB2A1D3ULL, 0x20A69787F3A20169ULL, 
            0x6A51229C4EBA882FULL, 0x53F810A002A69566ULL, 0x25C033027AF8EF08ULL, 0x43B8BC8B6B0DD6A1ULL, 
            0xCE71EC299BA94F3DULL, 0xE6A3D369D066645EULL, 0x794267C1A7ECF8E4ULL, 0x5701CC8DBF5BAEA8ULL, 
            0x4708DF5944E62DB6ULL, 0x6AF451AAF659BC68ULL, 0xBD890C764357A038ULL, 0x3808970544090798ULL
        },
        {
            0x7E743ACB455DD05CULL, 0xE929DF08C946E023ULL, 0x68CED018E138C176ULL, 0xCEA934F4A6923E1EULL, 
            0xF246CAA2E888A33FULL, 0x4EEE2E45C6539257ULL, 0x8C8A6D9137C3E1DCULL, 0xFF9E41E507A975A6ULL, 
            0xFBD67D52E888BCADULL, 0xF1DD3C1E299C91C9ULL, 0xD7318A26062A36ECULL, 0x3D77E80B7189BC84ULL, 
            0x618CA18986FE840BULL, 0x0BBC61835D722F8DULL, 0xB1C8B52DBB88D9A3ULL, 0xB6AAE45E21933E3DULL, 
            0x80F698B24994FA2CULL, 0x331157E29A43D27FULL, 0xA4BFAF6C9952CA38ULL, 0xA45AD8529A378284ULL, 
            0x03978DE83D4DF0A4ULL, 0xE02C5126E96FFA78ULL, 0xFDE5E1E4A9E1B107ULL, 0x564A28B4CA435CCAULL, 
            0x9C8F2C7D8F956941ULL, 0xF513BF4FF9210CCAULL, 0xCD7DE8A2E5BB4CC2ULL, 0x653E10D1702037EBULL, 
            0xA6A85FF5791074BFULL, 0x18E037EE4929C15DULL, 0x7AF938B15AA6ACE3ULL, 0x5DE9777E3C8ED3E9ULL
        },
        {
            0x67E8118F18F19A8DULL, 0xD61BBDFC53E6DE77ULL, 0xE87779389A70F5C8ULL, 0xFAA192BC96CBFAA9ULL, 
            0x2B93FE0C3146824BULL, 0x8CEE4223761E01F6ULL, 0x257028E3FB6304B1ULL, 0x0727D402C4AA43B6ULL, 
            0x17AB41C21D49C2CAULL, 0x97B311C36F4F34FCULL, 0x5610199A6E8D0E09ULL, 0x981B8D3297027C46ULL, 
            0x639B9A24FD995A01ULL, 0x6662C9ED8E9CD28FULL, 0x06B97C3807E1FDE8ULL, 0xCD2FCE0EE3EBA134ULL, 
            0xFBD9AB73380EAB38ULL, 0xE4C549A8C1C62253ULL, 0x28D98EF28117B629ULL, 0xDFC5F79FE2E151C4ULL, 
            0x404AC171A09C6A44ULL, 0xB22A38DCE934131AULL, 0x20045EC0C6C3B433ULL, 0xAF02FFCBF4A7B974ULL, 
            0xA8E89C7BB6A7F58FULL, 0x18B411C7118EF03FULL, 0xA5173C43BD780663ULL, 0x814D15D6E27B0CC4ULL, 
            0xC072B18A62B3B98EULL, 0x457E455DF6A3DB56ULL, 0xFFDBDA0112C5D3F3ULL, 0x3FEBBADDB095EB0EULL
        },
        {
            0xF73526D21032B35AULL, 0x42081BD7353182CEULL, 0x93E7C2752E7D2A1FULL, 0x7E8DA6860604D6C6ULL, 
            0xFEDE68B700136420ULL, 0x2C941533A7D8D07CULL, 0xA03D11F6C715D410ULL, 0x6BE0D4D340D8C45DULL, 
            0xD12B959D99131C23ULL, 0xC178E4F0C27C0903ULL, 0x00A35BD089BE5980ULL, 0x72F83976882DC7D8ULL, 
            0xA16CDBBA6A736734ULL, 0x8E1874F72B032324ULL, 0x6C4D00F03AEC9AA5ULL, 0x37ED9FB3300DFA44ULL, 
            0x9A544B66A25AD57CULL, 0xA0589D0EAB168946ULL, 0x857C09D6865B9F05ULL, 0x4AD7A457849909F5ULL, 
            0x144230FE50A8C3A7ULL, 0x22FC124A72BB46A3ULL, 0xBC16D500E3E8E40AULL, 0x665EBA4804A92934ULL, 
            0x81B249551E9B1E39ULL, 0x08030C369EA88629ULL, 0x19ADEFB7E91928ECULL, 0x4DB6F50CC4774223ULL, 
            0x51E05ED4ABE2DB43ULL, 0xEB038DC10CE1DAD8ULL, 0x48D38068C13C9EA4ULL, 0x00B9C319761BC2E0ULL
        },
        {
            0xA1AC606EC404A2CBULL, 0x60CE61236ABCCB82ULL, 0x58F77A76FAE443A7ULL, 0x0EA3FBC9F773EBD6ULL, 
            0x3FCD201ADE929207ULL, 0xD98466141C17A273ULL, 0xCFAE64EB9024FD32ULL, 0x887D82EC6B600D95ULL, 
            0xF24CC16B04D1D590ULL, 0xB57C9A6F5D7822AAULL, 0x2DF634E5C6F00C00ULL, 0xBBB145CC7BDA9D42ULL, 
            0xC8203B809FC2A86FULL, 0x0273D8AE85B59BDEULL, 0x48BBB1EFB84F93E8ULL, 0x97DFA734E4AB5842ULL, 
            0xEF8BFE6CA25CE4E7ULL, 0x8687F0B3C2935060ULL, 0xC8F6D59CF7DE8D53ULL, 0x6D852AB085D0F7ECULL, 
            0xB21DE4D38641A882ULL, 0x57B8E011697EEC6FULL, 0x4102E149580BC572ULL, 0x6962D171586123C5ULL, 
            0x283C9784DEE95E28ULL, 0x88A5AF00C0763373ULL, 0x888FC528975AD46AULL, 0x2DDC260758B74F37ULL, 
            0xC3ECFF1C15A73119ULL, 0xBA14F0C8E0E3F8D8ULL, 0xEC845E4B3E988D6AULL, 0xF02CEE641767A0DCULL
        }
    },
    {
        {
            0x6A61342FB6A7C6D2ULL, 0xFF21EC760B80B488ULL, 0xC4AAD1929296D3AAULL, 0x43D801F462AAE660ULL, 
            0x36D356F6F3B41BC5ULL, 0x00A25F75565B39F6ULL, 0xA7697B7C01929AA7ULL, 0x78D864EB19BEAE48ULL, 
            0x704D090C05C273CFULL, 0x4240B7CCF5392777ULL, 0xA459F189EC71CC36ULL, 0x94F3AE4FE28F10EBULL, 
            0x72748E27C479FA8EULL, 0x627B27F577552430ULL, 0x8813E96D54CA209FULL, 0x98BD99E6AE66C767ULL, 
            0xC119E180C82A1576ULL, 0x8BE01D1280340B44ULL, 0xE1AC2154AEEBF682ULL, 0x39AD3F113C00E43CULL, 
            0x34D7FFBB620F921FULL, 0x49CC5B1FB78D312AULL, 0xA6FD75D4BE4BAF9EULL, 0xD2514A612C597470ULL, 
            0x861CE22F70889688ULL, 0xDEE37AAE34DDFDCEULL, 0x88834AB7D0BC7271ULL, 0x2179B74715B053CDULL, 
            0x1FFBD3F47811E1C7ULL, 0x6AE2D5BBA4BBC14FULL, 0x1EF1F0B4CD7ACFDDULL, 0x202D040E0CF1DCB3ULL
        },
        {
            0xF2AEA9BBDD409970ULL, 0xA4E223A2793D081BULL, 0xFCF6A54E232E4697ULL, 0xAE516651CBC942DAULL, 
            0xF668CC43B1033AFDULL, 0x8156FCA69BAA0BFAULL, 0x5B2B00E944AEEC90ULL, 0x699F510353F1C3A2ULL, 
            0xDC5FDA056433118BULL, 0x7B27D2BCDB521C94ULL, 0xD87DC1965E9C1225ULL, 0x86D3C04C16909910ULL, 
            0xBD996466B6EF5C00ULL, 0xB1681330A1E2092EULL, 0x40F91E33505B48D6ULL, 0x012E5E59F98D4BC0ULL, 
            0x5A3FDE71641CA9B0ULL, 0xBD1CD6877C786646ULL, 0xF4C048FD8E11C8CFULL, 0x104BF662CC1755D1ULL, 
            0x988B0FCC14DC8C33ULL, 0xB259032867571EC2ULL, 0xE078BB63A852CC52ULL, 0xCEF8428A2C093BBAULL, 
            0xB344735C3F6CA511ULL, 0xBC99DCEF5039DBDEULL, 0xD91536354D61D2CEULL, 0xF917C4D03AE26DD4ULL, 
            0x290DB37822857B4AULL, 0x198F341264C16BA0ULL, 0xAED6D0347739B5F5ULL, 0xACFD59307076EE04ULL
        },
        {
            0x0FB70CFA4ADD0FCDULL, 0x92D15555EA60BAC4ULL, 0xB01AD6FFE7AECE38ULL, 0x6AAAD153E0471711ULL, 
            0x08A74827326D6D45ULL, 0x7DDD1128D78C0A92ULL, 0x8A4909841F4539CAULL, 0x9D4B1A6353DD1B66ULL, 
            0x1ABB8F75D9182F1CULL, 0x004CFD5394108ACEULL, 0x80FF439C8E6BD8A2ULL, 0x2EE2287039EC6703ULL, 
            0xBBC56058A084CB8DULL, 0x40593546C7D6831AULL, 0x85968DAC0C91421BULL, 0x01C872833093C636ULL, 
            0x9ADF79B42602B0CEULL, 0x4D4A20436DB5C1FAULL, 0xEA1F4115C1EA37F4ULL, 0x3282553AEA7AA020ULL, 
            0x04E5848D2B2B8AA2ULL, 0x2476D96D6E656BFCULL, 0x9DCEE6DBFEEC6A39ULL, 0x787528A49017D2BFULL, 
            0x0DFDA12F0C5A3226ULL, 0x01E36FF4EA18EE88ULL, 0x80D3AAA0F0F13CDCULL, 0x64FC40DFA2C5F175ULL, 
            0x865F38D6BFD2AC55ULL, 0x68459ADDBC8F5BC7ULL, 0x8474D484EC7EBFC8ULL, 0x5D9427ADC52934BFULL
        },
        {
            0xA2AD444DF815907BULL, 0x5E5A519738A2D0D2ULL, 0xB764BFC0A1ACD94AULL, 0xFF1700DE46AD82C8ULL, 
            0xFE6B544F7A492D13ULL, 0xF9A3C526D0B3F784ULL, 0x6CC64F1A8E2094C3ULL, 0x61CBA367992E4757ULL, 
            0xA9FF6BFCEF6BA739ULL, 0x05C816824CB126EAULL, 0x53D4C83EAF05BE66ULL, 0xA20C7FB87CE604AFULL, 
            0xB7D4472DEE5D45A2ULL, 0x538D574F5216144BULL, 0x76E4BACD56B52155ULL, 0xAC0607B44B6A052EULL, 
            0xB03E7026B7DEBF97ULL, 0x43B790193D65AD72ULL, 0x4BD7D65743A481DCULL, 0xED618226ED075B90ULL, 
            0x36929B0757A6E52CULL, 0xFAFE2160DD46E8B8ULL, 0xD98E2461530B5CE6ULL, 0x9A37E2F693831B49ULL, 
            0x29B030D69E311487ULL, 0xE7B204CDEEE80177ULL, 0xD8E0C3878B692988ULL, 0xA3291359729327BFULL, 
            0x7FEB524D9E49DE17ULL, 0x14BCF7C47845AE59ULL, 0xBAAAB0AD4CEF7964ULL, 0xC59F1B5C26271F65ULL
        },
        {
            0xD3199EE829F2863FULL, 0xFD060FB9CA1D4DC7ULL, 0x9040C3F217C8EC0EULL, 0x7E1BF50A110FAB95ULL, 
            0x57BE4AF660DBD85AULL, 0xD04511A3398EA434ULL, 0xAC7CDE18CD9E49F3ULL, 0x9AC64211B06CE6A4ULL, 
            0xF104C195AC0288E9ULL, 0x18B4A9681F4617EBULL, 0xBED4A5DCA723DFB8ULL, 0xAA1B9F449D67CDD1ULL, 
            0xE0993B0B6E2633DFULL, 0xCB34DB707BDBDEAFULL, 0x9B2B310000037C4FULL, 0x016A0F5DBCA94210ULL, 
            0x09B162BC936567FCULL, 0x04546CBFA87031A0ULL, 0x9046A687E221E187ULL, 0x76A4DBE810B5D74AULL, 
            0xF56CEA78B0667E3BULL, 0xF5CCBC35B5946E7DULL, 0x1F140773B68EE4C8ULL, 0x88449A7D26D43BF8ULL, 
            0x5F79FA46304754EAULL, 0x93AD37B884D9F7B7ULL, 0xC8F04ADAD1699D6CULL, 0x35B7EE744108B711ULL, 
            0x22610534D057D670ULL, 0x5D82EB770CE26BF8ULL, 0x4744509BD73F057DULL, 0xC8179D60AC983B8FULL
        },
        {
            0x967B175C233289D6ULL, 0x43AA599C899B0298ULL, 0x46526A74FBDA83C0ULL, 0x0E79D4D8DF796B5FULL, 
            0x283B2B63A7489B79ULL, 0xA849A005BEBE78A1ULL, 0x92A0EAA6735000BCULL, 0x3CBDCE2EDF72CE53ULL, 
            0x5261F726397F743DULL, 0xB03A12B45432608EULL, 0x6C84517270AE4434ULL, 0xE93FE022B8AF79D5ULL, 
            0x8C2D61F251FE243FULL, 0x8DF607B8D24BA168ULL, 0x21FE47981DEF2598ULL, 0x752C9EED5B9D7FBCULL, 
            0x0E6C119B28F5E4ECULL, 0xD141506418936D1DULL, 0x2B2208D5877FCBE1ULL, 0x7A1BBFF8E54487C6ULL, 
            0x7A0F5AE3484E225EULL, 0xC15ADA13AC0A3B61ULL, 0x17A947BF0A2547C6ULL, 0x18F7AC61A063EEBEULL, 
            0xD554AC58D4271069ULL, 0x066EEBF58C1FE82BULL, 0x7817305F46B6A2DDULL, 0xCA678FE1408320A5ULL, 
            0xAFA009161B93D1EFULL, 0x5C75907A5D289E4DULL, 0x7AB3D13E88456A03ULL, 0xE20103D35F5C23C9ULL
        }
    },
    {
        {
            0x7B403978F2C2F973ULL, 0x69B979C9ACF64762ULL, 0x856B3C20717C8178ULL, 0xF76D03D7B5FBFC86ULL, 
            0xBC5694FFA18CDEF3ULL, 0x37B19C690C8606ADULL, 0x3BFE13F5D4E6364DULL, 0x3FFCC108DE320C22ULL, 
            0x597ECCC733D177F3ULL, 0xC5C0FD68EDBFB4A0ULL, 0x77AC5EBDC8B6D3A1ULL, 0x4CBABE476C00588EULL, 
            0xB8CC71A371954AFEULL, 0xF7BB3C6A6E59757BULL, 0x3DF45C5CF38DB762ULL, 0xC3CFC9E3FD5C31BEULL, 
            0xC24034E1CD1957DCULL, 0x080D88A80E54C58EULL, 0xA7C1EF548CA74FB7ULL, 0xF0C5F75A5AC59985ULL, 
            0x5F2CABEADEDEC705ULL, 0xA17331B271EA4D3CULL, 0x9A690727A27AB20AULL, 0x7D805211DD78FEFCULL, 
            0x0985B430E89B4844ULL, 0xB40402B0C4DAB744ULL, 0xA807E51677207972ULL, 0x0FAA56180AD1FAC2ULL, 
            0x6D95975BE0DF767EULL, 0x608534A394F56AE8ULL, 0x58806A4403842835ULL, 0xA8F282FE6982BDC3ULL
        },
        {
            0xB97FBDFCDAB70621ULL, 0xFF595D99634659F0ULL, 0x3B6EECA0B08CA57DULL, 0xB0FC5DD525AF142CULL, 
            0x6F0A552C8F958827ULL, 0x6861581BD73949F2ULL, 0xDB8BF5E0F88D380FULL, 0x35C016B017BF9FF2ULL, 
            0x22FACB44712C2C95ULL, 0xA784908C5848B5B3ULL, 0x452201CC6007550CULL, 0xCA248BBC966C04AAULL, 
            0x4622B6FDA6545026ULL, 0x797E8F34FEE6DC46ULL, 0xDF673E7860B42555ULL, 0x8A309D1A5A7C0178ULL, 
            0x69433BD5846226BAULL, 0xC187F85DB9429537ULL, 0xC13C9530E4F45326ULL, 0x27F2AF7775A163A3ULL, 
            0xAD4BFE176A57E3C2ULL, 0xB221FA9B4FFBBABAULL, 0x46A4337923F3A545ULL, 0x3287F4164AD6BCADULL, 
            0x04A5B7570D98C91DULL, 0x45AD41590FD5F584ULL, 0x8024DCB34B6D09E5ULL, 0xD0656E6C01F2C789ULL, 
            0x8BD18D6DECD10DB6ULL, 0x86E0C0CF7A20E896ULL, 0xD1C56224E1A23A36ULL, 0x2C2C2B8371D0FCB5ULL
        },
        {
            0xB9FB2CD84CEAAAB1ULL, 0x83E1519975148F49ULL, 0xA39A77CB83908428ULL, 0x3C837A6B1130F1F9ULL, 
            0x045E750F53D49F49ULL, 0x7C424CEDC97BCB0BULL, 0x9A643DB34CD7723FULL, 0x63EA228A532BF9F7ULL, 
            0xC168A477CFAC66CDULL, 0x757FCA388576B21CULL, 0x82E44046BCC344E4ULL, 0xF5402BA456019E72ULL, 
            0x7796489E5AF48EE6ULL, 0x89AE08065207A3B5ULL, 0xDBE81979D1AA7EF1ULL, 0x745566DEA3CBA971ULL, 
            0xEAE7D4D8920281CDULL, 0x257EBF55A2F80FEDULL, 0x54CD37FBBE9D72B9ULL, 0xBF4DDE2E4061AE28ULL, 
            0x8D7545CF27913086ULL, 0xE9280EF03EE24186ULL, 0xEFAF5FBCB95E9246ULL, 0x58970B9EA2C2FB32ULL, 
            0x76DEC07E3FD492D3ULL, 0xC845911AFCB1613DULL, 0x38B230EF875670D4ULL, 0x7A312FE2764A5604ULL, 
            0x46B7002F7914AF29ULL, 0x9AB9B15DB5CE2014ULL, 0x757052C10C131513ULL, 0x7551251A184ACADBULL
        },
        {
            0x4986135A6AF7E5FDULL, 0xDB9EBF7D4D67B23EULL, 0x3837EBFFF2458829ULL, 0xFE5ED6A43FE17FD7ULL, 
            0xB8AE795C049ECBE8ULL, 0x6772AD27CF8EB987ULL, 0x2133E567E4C0EEFDULL, 0xA2CB6B8980DC33BAULL, 
            0x25A68B4E20F2BEE5ULL, 0x9F965C5705BFBC0AULL, 0x08630090ADDE9305ULL, 0x029B2CBCEBBC4DC2ULL, 
            0x3B99789718EF021CULL, 0xE0EFC763CD535B98ULL, 0xE7BA12F8473C0330ULL, 0xA2F6AE568BDC865BULL, 
            0x9527E4E9FE33F90DULL, 0x5137056306E168D4ULL, 0x83A4A6272D4032C5ULL, 0x0F06022F684BE00CULL, 
            0xCF14AE22F4B6FB94ULL, 0xF99AF697EB86B668ULL, 0xC2D3569AFB7CD5CEULL, 0x9175699788AAA146ULL, 
            0xD32254A70D888D78ULL, 0x40C1BB7EEEC5E840ULL, 0x449786A69A8393B8ULL, 0x7BA42FFA2A2FE22AULL, 
            0x96E3B21A49919D9DULL, 0x977E59EB3E4D7955ULL, 0x69F99E8FDF3DB90DULL, 0xD5A928BB05793987ULL
        },
        {
            0xDF4172D54D0A2947ULL, 0xE57FEBC30187C69AULL, 0x8CDCDB0CBAC9411CULL, 0x3E1C025AF6266F56ULL, 
            0x7C6D756A2A7375F6ULL, 0x9E8A1A9307FD7226ULL, 0x6EEF082D648937E0ULL, 0x75AFBCAD4729BB3DULL, 
            0x068B371522416CAAULL, 0x083D78CEBB876488ULL, 0x43FD4028B3398F1BULL, 0x01C9BDA2C9ECFC8BULL, 
            0x09C8954978AC1272ULL, 0x4191394AC4F7C34DULL, 0x766966491B0D528AULL, 0x528D286E57A7C0CFULL, 
            0xEBED508A6315F96BULL, 0x883F9E699087B2E7ULL, 0xAC258E26955D8073ULL, 0x6977D354BFD0992AULL, 
            0x26F5836E7C5D7477ULL, 0x7894BE44D027FE8DULL, 0xD4D0E1FED336579AULL, 0x360973F0E951C71FULL, 
            0xE03B94F27026CCE9ULL, 0x89CECCC9C778228DULL, 0x82EBB11E3B486A1AULL, 0x08F88D082A5502B6ULL, 
            0x9FA04F0BA042F2BDULL, 0xE87484E319A80E70ULL, 0x215E672B2E6C45A9ULL, 0x2128B569A63F96F6ULL
        },
        {
            0xF7AA45D1B6B00FC9ULL, 0x91EFA70E267F4C6EULL, 0x29C0F99F6EAC4C72ULL, 0x97D0EBFF00692765ULL, 
            0x6488795964773A5CULL, 0xF6B270E572318A13ULL, 0x8BAD2F811C54DE72ULL, 0xDABADF0CE6A0C657ULL, 
            0x0974798C913EFC06ULL, 0x76C96FEB9FDFBB6DULL, 0xFCC7544055DDF0D7ULL, 0x5E601A7C750742F3ULL, 
            0x96351E64DAB0A55CULL, 0xE1CCBCBDEF74267FULL, 0x387C461CEDE543B8ULL, 0xF0809D6C3EB3514EULL, 
            0xA37DABB77802B29FULL, 0x7BA6C705BD872DB9ULL, 0xB98A9922A99605F8ULL, 0xD59F846FBB4D4C3FULL, 
            0x570984678344F137ULL, 0x5281F0488AF1421CULL, 0x922A5C7C40A17F1FULL, 0xCCF5DB4ECB6AD73BULL, 
            0x573FB38E5E829397ULL, 0x0CD9F64EC9D9D769ULL, 0xE86B69BBFB3DC508ULL, 0x29732EC5928353B2ULL, 
            0x9B3E33B7C3817326ULL, 0x5CF3E1D190D18966ULL, 0x11B5C59456E99440ULL, 0xF5799E1B6E0CD9ABULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseGConstants = {
    0xD456557C7B38B618ULL,
    0x0CDC4CB86A8C736AULL,
    0x2AFC993AAB853870ULL,
    0xD456557C7B38B618ULL,
    0x0CDC4CB86A8C736AULL,
    0x2AFC993AAB853870ULL,
    0xFE68D190CBC2A5DEULL,
    0x71174D555B066D4DULL,
    0x5A,
    0x70,
    0xB1,
    0x64,
    0xAB,
    0x64,
    0x2A,
    0xF3
};

const TwistDomainSaltSet TwistExpander_Suhail::kPhaseHSalts = {
    {
        {
            0xD2DAE327EB021C0FULL, 0xDEEA2139E7678228ULL, 0xD54547EB94A0AC3CULL, 0xD21BCB7A6ADA12D5ULL, 
            0x7EA04E171A3A329EULL, 0xAC3414922F1D27D6ULL, 0x0CA9F80FDA9BFA4BULL, 0x17824265EB50A33CULL, 
            0x9BBF870D40A636D3ULL, 0x390A453AEB718EF4ULL, 0x1592E51431D57386ULL, 0x1DA559902FD17AA4ULL, 
            0xD84CDC6FD28B284AULL, 0xF24A7817EB1E43D4ULL, 0xC7BADCCDA97B0533ULL, 0x3DA8010F9D2E029AULL, 
            0x79BEB9D706836848ULL, 0x35D4B401AB8F8C37ULL, 0x850A192A09DDD4E9ULL, 0xFA2C74331F641A71ULL, 
            0x1BBB7747922CD0C4ULL, 0x51400D4C8700D068ULL, 0x7206324DE0E7BC42ULL, 0xEE4688CA9E3AD2D2ULL, 
            0x4C36D44AB64982B7ULL, 0x30C3CE6AC6A9F2D4ULL, 0x6575A2EF94B7A115ULL, 0x98F063C53B5201ABULL, 
            0x9FAE5AA85D15E9CFULL, 0x661456E99F10EA70ULL, 0x3515252BB9B72AC3ULL, 0x6BBB70ACC1A6A7A6ULL
        },
        {
            0xD078295F92EE6DF7ULL, 0x47676A2D553AE1AEULL, 0x55F92872F98B87BEULL, 0xD640A04241D15B4EULL, 
            0xFB30340275B69E98ULL, 0x7F0AE8CBED63E134ULL, 0xD588129F92373897ULL, 0x0B6403CB0C3999AEULL, 
            0x11CF49A9CCCA8F5DULL, 0x93DEDAE7A903B3F9ULL, 0x2E90C5BAB5BC49F0ULL, 0x996F00FECF9D2114ULL, 
            0x37988AACD8D05D9DULL, 0xB77DE9BBC091AD36ULL, 0x19A76A9C6EBE33D5ULL, 0x2DDA796CC57C92AAULL, 
            0x27BDC24391DE704BULL, 0xAD700C32144142B8ULL, 0x4C7F0A24BDB65551ULL, 0x05BBEB2598296BB5ULL, 
            0x91035ACD31A3CD93ULL, 0xA804FD8C59D1492BULL, 0x60D465EBD6D410A9ULL, 0x5F74094919855083ULL, 
            0xCEF620DD063A0E5FULL, 0xFC753AD8EC08EE4AULL, 0x6226F3BA042C2425ULL, 0x3F8E4DB70F3CE6A8ULL, 
            0x8BCDEC60AE0C34FCULL, 0x78AC74F8CC25CB31ULL, 0x1FF26C637332D65FULL, 0x41234A10C811D756ULL
        },
        {
            0x4FE1A5453F502619ULL, 0x9B157C2B014E8E9BULL, 0x9C9FADC9DD79D38DULL, 0x19063296A3C94C9BULL, 
            0x2F9926DD61586E5AULL, 0x70EEBEBBE57774DBULL, 0x8D89DA0F4EA16FE8ULL, 0x774467C0D1AA22DFULL, 
            0x9B7BE63A8807985BULL, 0x4C6B74C6CD1CE109ULL, 0xFC0EDF9439D185E1ULL, 0xF1B023834F3A09C4ULL, 
            0x6439469E7BCF59F7ULL, 0xF01C9AFCCE81F054ULL, 0x90B19E912EF61101ULL, 0x35E6CF97C622169BULL, 
            0x3F6251A557517B02ULL, 0x0083C3A9B1D6FEF5ULL, 0x6AC2EB7B9746BAE2ULL, 0x3A962453628A9894ULL, 
            0x4732559BFB3FB98CULL, 0xCDB902E67FB3ACC6ULL, 0x6B4654A73988F530ULL, 0x34EB2BFC58A9F312ULL, 
            0xC64D1D644680AAB5ULL, 0x77D8FCE8E4B1979DULL, 0x70E43014462B43D5ULL, 0x0C4972C2BDE20651ULL, 
            0x5EA202DCC68D3807ULL, 0xD9868A75DB28EBFEULL, 0xA6476E9BCC2193D8ULL, 0x1E924C1E0B723166ULL
        },
        {
            0x036D493B0304CDA7ULL, 0xB6829339A787257BULL, 0x72BAE67C5542BAC4ULL, 0xFDD3BFA2CB2F4034ULL, 
            0x8C0FEC8C2AFD714DULL, 0x963355E11EB785EFULL, 0x3A8670C3FAAE51C5ULL, 0x4F3D97BA7706BDF5ULL, 
            0x8136491A10A33B1CULL, 0x60E8A2ECB0FF247CULL, 0xB057E4475B750A17ULL, 0x45573552DEA9AFDFULL, 
            0x9B16DABED4AF30C0ULL, 0x7B3558F69985158EULL, 0x5299A8C7E31F7057ULL, 0xB973F9B909B38738ULL, 
            0x1CCACC155FC906FBULL, 0xFA96C078B34906C9ULL, 0xA9D4B99B7D6F40EDULL, 0xFD00F4B0D67B823BULL, 
            0x8517D62B9E407A5AULL, 0x4AA59E70EEDF7BD2ULL, 0x1616D0183B29CBA1ULL, 0x4401E4903D699A72ULL, 
            0x0C813A6E09349972ULL, 0x51BA9BDC284CE79DULL, 0x0C3EF5F5A3C5B55BULL, 0xB4D23506F0829211ULL, 
            0x67AEBCBB1F1BA819ULL, 0x560E30967EC60DB1ULL, 0xE16D6C84884C3B87ULL, 0x6B57D1A92FA34B57ULL
        },
        {
            0xE951F233D055F749ULL, 0x4A5CE1D42CDAF312ULL, 0x46B6A0A767B55AF7ULL, 0xDF887A55E8D3EB9BULL, 
            0xD192A81DF384DB98ULL, 0xF7B41B4E92C8C665ULL, 0x1A19103E4F29EC35ULL, 0x3EFFA95B5892F3A0ULL, 
            0x46A4AA56B43B75A2ULL, 0xC34B965ED5D730E6ULL, 0xE515D913592D7ADEULL, 0xC1A3B06ED26DD7A0ULL, 
            0xBB95D26EBDF032E7ULL, 0x8F4C0E9E0987C165ULL, 0xB4D798A16CC47D2BULL, 0xB4291000876B01A8ULL, 
            0x080FE840AE7F6CD1ULL, 0xE3BBB0CE01D1F162ULL, 0x507E28A079E2E9C8ULL, 0x1229CD00749A9073ULL, 
            0x309C280F6B88675AULL, 0x7328258AC2A7338FULL, 0x83E8B430F8B953D9ULL, 0xAE620E5104492600ULL, 
            0x86E5F7499330FC66ULL, 0x646B5E430865D77CULL, 0xC8BE40458C922987ULL, 0x49235C752E6F5668ULL, 
            0xBD6EBF7F414B4193ULL, 0x9B1A75BBE38F2C95ULL, 0xA77E36A9E150B71DULL, 0x60BECE44C4C5E107ULL
        },
        {
            0x637C44FC4A075C00ULL, 0xA75C1A36FCA4BC51ULL, 0xFD4052186A97DF9EULL, 0x2E491CE1F6FFF475ULL, 
            0xE8131AB9B6DB1C0AULL, 0x6F472C513026F221ULL, 0x232FECB88C4724F4ULL, 0x4540D0B633D3D358ULL, 
            0x9132227F1FBBBF06ULL, 0xF59F479DE3EAAC60ULL, 0xE06FA4ECCB5C68E8ULL, 0x05ACDD4A812AB756ULL, 
            0x0370CFE8A78B92C5ULL, 0xDD7BEC95EF831104ULL, 0x1C735FDB7B5294C2ULL, 0x34209541FCE5CA77ULL, 
            0xCF991ACAD394F92FULL, 0x95458696F56266DCULL, 0x6E7475D017FA0C30ULL, 0x3255CF49724EF674ULL, 
            0x192F5968B8DC17AAULL, 0x0285C6CF8CB87FB3ULL, 0x1C65A49F99EFDB5EULL, 0x5CABD10DE491F197ULL, 
            0x8F0A2856A04DD4A8ULL, 0x654A78F82F44D9EFULL, 0xFCC311A156916E2DULL, 0x9BD4CA77D582116AULL, 
            0xD2D21A25E63A0A97ULL, 0x0C15FC8AE7358E24ULL, 0xD443EE4A0546FEF0ULL, 0x49EB05DA536455CAULL
        }
    },
    {
        {
            0x195763FC70D6608DULL, 0xDE7F7048F3D1E63CULL, 0x966156598A10B1DCULL, 0xEB759ED93D89FA23ULL, 
            0x98AF70D378229F3EULL, 0x3615F7EDFCB765ADULL, 0x50B18B1CFB0760BAULL, 0x7A2201259FF67077ULL, 
            0xB4C249EEBE072FD6ULL, 0x25052D113C2073AEULL, 0xA395E94B53BA1D4BULL, 0x6E901F4479010206ULL, 
            0xF7475464BE8899F2ULL, 0x45A826D79CF9555FULL, 0xDD5EDC34C4619C82ULL, 0x92D379D75CCA5555ULL, 
            0x1E3A6C90FBDE5DF8ULL, 0x14EAC74985C7E26FULL, 0xB36887782E87D9DDULL, 0x468DBD5FA3CF5C84ULL, 
            0x148932169BBD0A2CULL, 0x5A18482B8D4158E8ULL, 0xC7C4F2DCB425DC7AULL, 0xDDA1081DC537E6D1ULL, 
            0x9CE3E82FA81C6EADULL, 0x48876D71D8397077ULL, 0x1880D8729BA1AE07ULL, 0xE397C1DEDA7C0710ULL, 
            0xCF9C6E7F024CA0FBULL, 0xECEC9FBE2E0BFEB7ULL, 0x04222B8CED7A9F0AULL, 0x259ADF7D42711425ULL
        },
        {
            0xA0B1ACE3F9D0D959ULL, 0x28AEB14D170A0DE5ULL, 0x7FAC79EB4DD3A1FDULL, 0x80E5F82433768F01ULL, 
            0xBDA88E3544D7DBF6ULL, 0xFB9D6CF55EB724F1ULL, 0x65B091C7B28D2D11ULL, 0xF5922999E7DFD475ULL, 
            0x0557796EF272AD50ULL, 0x7FBC79126290CB5CULL, 0xC390BC0AE9C4D4E3ULL, 0x09795F3F4219A947ULL, 
            0x743C9A171F35F07AULL, 0x430EA76326E365C6ULL, 0xFC4C17FBB1779512ULL, 0xC2DE8B5DCBFD5F1DULL, 
            0x3AFBDF33B29DA856ULL, 0x7ACDB9CD6FD99F2EULL, 0xF2175F87FD821EA7ULL, 0x3D7A655DA7A2FBC1ULL, 
            0xB240375E1587E7BEULL, 0xE3043502661D5D60ULL, 0xC2F0502BB3DE9522ULL, 0x1CC542C258AD79BEULL, 
            0x12C62F3A735A6D5FULL, 0x5D44F49F8EB2F78CULL, 0xB092D966A4DCD23CULL, 0xE66569C3B3D398A6ULL, 
            0xFC76466EC607AE7DULL, 0x5746F29FE4817C12ULL, 0xBDC9FFA493930030ULL, 0x3D344BA116478967ULL
        },
        {
            0x0AB1C755AE9423F4ULL, 0xE473249360263DCDULL, 0x5DC76E65EE527175ULL, 0x07DCCEFD523C1F27ULL, 
            0x7C1D74C69D5F6BABULL, 0xEB6E3845B02698E0ULL, 0x3FBFFF2EBADD4936ULL, 0xB096E72409BEE20BULL, 
            0x17A29C0B4FB11103ULL, 0x822F1B1ED7E050CEULL, 0x6C262B6F94DD2CD7ULL, 0x43E2CF8948A14B69ULL, 
            0x7FEAED23AE85A113ULL, 0x8999FFE4391F4CF7ULL, 0x46C729B2AFA89D6FULL, 0x5960A80B47A5B30EULL, 
            0xE94A5539DEC28F22ULL, 0xB2DD06B5F14F8B59ULL, 0x66133C20D49163BBULL, 0x1E7FAE91F5AB93EAULL, 
            0x08EF452604B6148BULL, 0x41C747C5F5BC4401ULL, 0x1DD6383FCC05A7CFULL, 0x701C886FF86E2874ULL, 
            0x060B31738A5241C4ULL, 0x7D723D9F12A44A35ULL, 0x74C4884CBE2C7965ULL, 0xE4985EE3B0622EE7ULL, 
            0x0ED026D522E86CA9ULL, 0xAF5A1CD59227F0BEULL, 0x3DB5226A3D105A94ULL, 0xA99617E732E12209ULL
        },
        {
            0x0D9101E037E2A793ULL, 0xEB6D604E6FECE8DCULL, 0x8EFA09A07D899A7EULL, 0x6DC5F90847F5E729ULL, 
            0x5C8B8A5B51BFFAD1ULL, 0x39EEFE72E87D9858ULL, 0xA78CC53A5FE6EA08ULL, 0x8640BBF4E00F8C9DULL, 
            0xBF0565A9817E0DEAULL, 0xA9CA59B3F10821B6ULL, 0x9D8BB5725DBBA9DBULL, 0x83DED05248CFC600ULL, 
            0x1F448BF290693C75ULL, 0xE33E5F1FAFF4528BULL, 0x1EF439B957BC1947ULL, 0x3B6F7881E0E6F28EULL, 
            0x1214A19DE097DADEULL, 0xA3E51977CCFA315CULL, 0x9070D9B948228A58ULL, 0xD0F84FE2F2072DD2ULL, 
            0xD1D97FE8D508F103ULL, 0x2E5933E739D02710ULL, 0xE6D75AC9B984C43AULL, 0x5BE05AFC01DED777ULL, 
            0xF9740537DBF869D1ULL, 0x0A8E0D5A12E970D6ULL, 0xBAE6B2B8A67CD6E4ULL, 0x4ACB5C8F77E30581ULL, 
            0xBE9641B7296ED32FULL, 0xE23CE1F8DCD6F5AAULL, 0xFF8808DD67B09CB5ULL, 0x39C6E96849980A59ULL
        },
        {
            0xF71DA988E801CC65ULL, 0x42E3F418612AEA38ULL, 0xF54A06AE7AD0B885ULL, 0x0F7CA4D6D13394E9ULL, 
            0xFD546E07E8D28E7EULL, 0x0C518843659DFD8EULL, 0x861CD3260AC63F40ULL, 0x58B29C50DB9A5E6DULL, 
            0xA82CFBD6148932B3ULL, 0x0010A90D5A82B59BULL, 0x9D0D58BAC3F245BCULL, 0xB400F19042944182ULL, 
            0x29C688316AE63B43ULL, 0xFEEB821194E080EEULL, 0x7F37CDF02B71D601ULL, 0x27FDCA453B465076ULL, 
            0x238DA4880A65586FULL, 0xE3DC87C0F44630ECULL, 0xDB39BDF33B251E11ULL, 0xAB4905A021C608A6ULL, 
            0x1A63466A3ADA0734ULL, 0x1FDB329DB456D7B2ULL, 0x5E1FF77AC6744B6BULL, 0xF7F3CE2721D0D1B9ULL, 
            0x448A113762989330ULL, 0x6E92C33E7E67470CULL, 0xF4659E3514110D69ULL, 0x9B8FED1E2AF3AC5EULL, 
            0x10C8C9D43A1398D4ULL, 0x3DC991808E52EFE5ULL, 0xD1B9A2132C97D7DBULL, 0x7F65A963DC0905A4ULL
        },
        {
            0x8D89D3A5008B2118ULL, 0xCD420F953BE6D9F3ULL, 0x01F219FAD39BD5C0ULL, 0x7B4681CA951BAAB9ULL, 
            0xD9601B9F3D627823ULL, 0xD0BF38F9637338F4ULL, 0xC0D9375EEA339BDFULL, 0x0230EC9C4621C950ULL, 
            0x7B12E86DC5F64FCCULL, 0x8F8CA1C764623856ULL, 0x73AE2BCEF51D17E7ULL, 0x7582F34BDDBA8DB1ULL, 
            0x0F45CE27A97D29FCULL, 0xC08FD7735A6A619BULL, 0x02DB1F53503AF445ULL, 0x5FF6D451DCAD4B90ULL, 
            0xA154BDE093A3C531ULL, 0x201723A7D34EF0E8ULL, 0x97519A17DEE00B1CULL, 0xFF5C4A437335E9CCULL, 
            0x621F64669ACC6F52ULL, 0x302F87CDE1C660B3ULL, 0x92947AC891B88D41ULL, 0x9C78AA08AE063864ULL, 
            0x062C20AE8124E4DCULL, 0x48A6FACFFA4E59BFULL, 0xDA2741325AD17078ULL, 0xD4457264863E236AULL, 
            0x351CF770EFBA3D5DULL, 0x7FCBF14861143A37ULL, 0xF6ECB4B93A33D4AFULL, 0xBB064E6611476624ULL
        }
    },
    {
        {
            0xA38773E8BE50512BULL, 0x2E890711C4FFDC34ULL, 0x232248C7DABF3D38ULL, 0xE99CE6B23337D96AULL, 
            0x669EA0B7D71697B3ULL, 0x2ED7816A2B4412B5ULL, 0xF55282173BB4C5BCULL, 0x555643E8DFA243E5ULL, 
            0xF916B65AD931AC2CULL, 0x6E1EBCC737E5C4F0ULL, 0xDA40AA25247AEF3EULL, 0x8CADAA072D45B90FULL, 
            0xEEE1268AB9F0F306ULL, 0xCD730B52D1B1FD14ULL, 0xB9E7F472D44726E1ULL, 0xDBFBA3212C3D78B1ULL, 
            0x45E6703E952BC263ULL, 0x61D5EE292CDFB4EAULL, 0x815FCC44AC22A2C7ULL, 0x95638BE5D17C92BBULL, 
            0xF0EDBE7C16EEE222ULL, 0xCF42EE9F71B23EC6ULL, 0x2C558C1D1B2A6EF0ULL, 0x27CC737A23F1AFAAULL, 
            0x894377EEFBE770D9ULL, 0x223AEEABE7D364C4ULL, 0x0588F8580E52A574ULL, 0x6D7C8DFB596AE117ULL, 
            0x07F11202F5741620ULL, 0x7FCA860B2AC2D840ULL, 0xC29F2D2B3E52FADCULL, 0xA90202F1F68E4005ULL
        },
        {
            0xFD818DBA9BEE73F9ULL, 0xC20177C115E0C600ULL, 0x129068946B82212FULL, 0x04615AEF79A00B85ULL, 
            0xA368338865DE0E94ULL, 0x07EF42CB04AF1119ULL, 0x75676249EB1EEFF1ULL, 0xE4478F61BCE7A7FFULL, 
            0x87A5738B45148227ULL, 0x502AAE0A020BF381ULL, 0xD750AC81E0D56B0DULL, 0x5209553E745626A5ULL, 
            0x8CF76B0D0ED355FEULL, 0xB4EEA55AC99A6520ULL, 0xD48BF4B025C1DC80ULL, 0x4C3E24A92B564F33ULL, 
            0xB900CE6D5D715B8DULL, 0xD5E1556274A4CE7FULL, 0x02DC50F4079B4963ULL, 0xA00FF188B42911B1ULL, 
            0xB8F5377A30FE349BULL, 0xF32046197DF67BB5ULL, 0xEA6F64276E0BDAC0ULL, 0xD70E801175846319ULL, 
            0xB84241F62A915C76ULL, 0xD1268ADC192EE234ULL, 0x2A763F5395F38F90ULL, 0x1625D72FD02BAADFULL, 
            0x62001F39B6F5D4FFULL, 0x86A67FEC8ADF4476ULL, 0x46709DFA51AB9219ULL, 0x4B4968B243357D2DULL
        },
        {
            0x9CA8EA46A2E317BAULL, 0x79C289F36B749A06ULL, 0x9F98EF581336A370ULL, 0x3773B7D839889D98ULL, 
            0xA9F06AB41EB0AFE9ULL, 0x35E10A3990EB11DBULL, 0x3CE69F1035A586DCULL, 0x3926D47ACE08CBD5ULL, 
            0xB9961E6283C5F04FULL, 0x16944AD768C4AC7AULL, 0x2EA0064ABF327EE9ULL, 0xA0815518F2B64B6CULL, 
            0xFC8A52D694C8F974ULL, 0x02DCEEAEAFA3F03FULL, 0xB526B38639C4FE7EULL, 0x7363B843C7F18F4FULL, 
            0x6A0242679CD55DC6ULL, 0xC8C491453D95FB45ULL, 0x076D28C547D3A090ULL, 0x5FA1B1324F60012DULL, 
            0x45A44CCE0D8E6288ULL, 0x3A41D85CB6C1F722ULL, 0x0FE4FEB6D1953787ULL, 0x8A5C19577D26CA50ULL, 
            0x653BF7F636700C2DULL, 0x281D47256EDA1182ULL, 0x7A7CE46C9E00FFB5ULL, 0xEB2C62EB053057E5ULL, 
            0xB73126FDE6F9AA93ULL, 0xD0BE89BFF01EE9CAULL, 0xDB6ED28152C91541ULL, 0xD44CDA6C4C6B210DULL
        },
        {
            0xD036AB60470EA301ULL, 0x28F79CDDDC11F3CFULL, 0x697DE9FBD514AD09ULL, 0xE49F75C814DB456DULL, 
            0x75FC07A085690648ULL, 0xC5FA2CC265FCB1E4ULL, 0x815C842BACECA1BBULL, 0xC3D30236151C60D9ULL, 
            0x1C127D4E15975675ULL, 0x9A26F3A0A16FBBACULL, 0x065C46EFEF150517ULL, 0xA2F429CA01DD03DAULL, 
            0x730715FF2776E55AULL, 0x2173D9C7C727561DULL, 0x128896756C8986D6ULL, 0xB112D5EFF3248EF4ULL, 
            0xB91AE387EFD62344ULL, 0x1A79A6C9FA4BCFFCULL, 0x39200F7D88BBF219ULL, 0x198207582C82F0EEULL, 
            0x82F0EB0B6EE84735ULL, 0xD636ACFB966DDD8EULL, 0x0BDAEEC54A83D972ULL, 0x006057F36D0F8C4FULL, 
            0x767C5D00A9C181D9ULL, 0xECF805AC51223C84ULL, 0x41546CFC6D3FF165ULL, 0x743F9715EE14CCF1ULL, 
            0xF658B171FC411D9DULL, 0xE44C6F929DCE9288ULL, 0x76C37BD34046DCD4ULL, 0xCED2532D69180B2AULL
        },
        {
            0x17DD3571AF567E86ULL, 0xBD0286987D41B61BULL, 0x6A765D96A0979735ULL, 0xC95CC1C66BBBFA0DULL, 
            0xBC32B40235AC985BULL, 0x4676E469919C7FA1ULL, 0x68A062E795A1D9A4ULL, 0xEC616F73AF2D784AULL, 
            0x0986B2DE3CC5569EULL, 0xA97D87DA44B45CF3ULL, 0x3479BD1B0DAA9270ULL, 0xDAB2E7B9BC055436ULL, 
            0xE17A716162F5F87FULL, 0x702CC719E618DCB6ULL, 0xA63CAC5987203549ULL, 0xE0DFFC8DE7391FCBULL, 
            0xDE62C6EFF58786E9ULL, 0x414CE302531290F8ULL, 0x4FF3B54FFB1EFD08ULL, 0xB257FA5B2DB8CA3BULL, 
            0xCFAF07BBAD988C93ULL, 0xA4E1B3B6BD360306ULL, 0xBA3E8D67C9DE3330ULL, 0xFD000FBB23D5879AULL, 
            0x96A71186F9EBE42CULL, 0x1D704D5975ADF9B2ULL, 0xE1D08FB5EB121ED5ULL, 0x2D6C127A6183F8BBULL, 
            0xC79DD459E7DA6719ULL, 0x6A51D47BD323E84BULL, 0x8B0EDEA66A784B4EULL, 0xCC1179CE33762A9DULL
        },
        {
            0xB2288BDD7D88A100ULL, 0xBD9F71FAB4056728ULL, 0xCC341DAD026D9126ULL, 0xC75A510A9F2F27CDULL, 
            0xC587D89F114225BDULL, 0x783528A26201ED11ULL, 0x1151BCD4ECC17443ULL, 0xE48C0C70CDDE943FULL, 
            0x4A627D824EC29DE9ULL, 0x412B1AD92DE5787BULL, 0x12542A2EFF6D792AULL, 0xE7FE0086D7DB05F0ULL, 
            0x6E96257ECBD6C038ULL, 0xB723630D3B497B1FULL, 0xB1FC7B3268EF3A41ULL, 0x17E005DF6277E28FULL, 
            0x3CF8831C261ACF31ULL, 0x007FCAB5D78A151EULL, 0x808994DE8A41D4DCULL, 0x198AA8C48477E84BULL, 
            0xDBA0A21498B9190BULL, 0xE49A61BDB8166504ULL, 0x306E3C4564EAC946ULL, 0xB8177D2671384545ULL, 
            0x34F41456725D4C87ULL, 0xA52AAFBEDA5A9D34ULL, 0x0600605EC50FE155ULL, 0xD52D1DF441533A0DULL, 
            0x594C1D9AE5B14AD8ULL, 0xD86379D6FE8CB1A3ULL, 0xF11ABDF1A4025F59ULL, 0x7EFF04CEB9836B5DULL
        }
    }
};

const TwistDomainConstants TwistExpander_Suhail::kPhaseHConstants = {
    0x1115A54D8F6D7B6EULL,
    0x0F60BBC0D7312ADBULL,
    0xBFC8EEF1B0510613ULL,
    0x1115A54D8F6D7B6EULL,
    0x0F60BBC0D7312ADBULL,
    0xBFC8EEF1B0510613ULL,
    0x7C1086672964E7C3ULL,
    0x2B85EFD549E5D736ULL,
    0xF8,
    0x9E,
    0x73,
    0x7A,
    0x7D,
    0xDE,
    0x11,
    0x98
};

