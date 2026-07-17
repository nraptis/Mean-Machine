#include "TwistExpander_Menkent.hpp"
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

TwistExpander_Menkent::TwistExpander_Menkent()
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

void TwistExpander_Menkent::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x8C604AFBDCD719C2ULL; std::uint64_t aIngress = 0xCFCB1BA6FF7BBD1DULL; std::uint64_t aCarry = 0xC4A0799D13BCD58DULL;

    std::uint64_t aWandererA = 0xEAD0935DB9FD8660ULL; std::uint64_t aWandererB = 0x8FD0399B161C0464ULL; std::uint64_t aWandererC = 0xB0369F255D07CCBCULL; std::uint64_t aWandererD = 0xAFABB39B2B426F30ULL;
    std::uint64_t aWandererE = 0x98BE05553DC40742ULL; std::uint64_t aWandererF = 0xB2B7164B1E3DDF15ULL; std::uint64_t aWandererG = 0x8B66E27B4CDFF14CULL; std::uint64_t aWandererH = 0xB17533D509322154ULL;
    std::uint64_t aWandererI = 0xDB982D111987D1B7ULL; std::uint64_t aWandererJ = 0xF3FA63248010CF9CULL; std::uint64_t aWandererK = 0xCF5A08E196F43222ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10906605899400925199U;
        aCarry = 11231554278401608955U;
        aWandererA = 16333511656227280408U;
        aWandererB = 11498538487992277702U;
        aWandererC = 17864178118959967896U;
        aWandererD = 11443243918378857801U;
        aWandererE = 17680918235588838490U;
        aWandererF = 15579130870329343544U;
        aWandererG = 9813216302735442684U;
        aWandererH = 13024209275873195341U;
        aWandererI = 12978064471919475980U;
        aWandererJ = 18423235188584386854U;
        aWandererK = 15935235594827254355U;
    TwistExpander_Menkent_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Menkent_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Menkent_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Menkent_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Menkent_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Menkent::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9E9E9919431F08A6ULL; std::uint64_t aIngress = 0x88AC0C7E9681B8A9ULL; std::uint64_t aCarry = 0xD93E1CB0FB351045ULL;

    std::uint64_t aWandererA = 0xB8490265F0994046ULL; std::uint64_t aWandererB = 0xD3B26FA397634D00ULL; std::uint64_t aWandererC = 0xFBD6968F0495A65DULL; std::uint64_t aWandererD = 0x89EAE65D1677808EULL;
    std::uint64_t aWandererE = 0xAB98E3415316EC8DULL; std::uint64_t aWandererF = 0xF23ADF183531CECAULL; std::uint64_t aWandererG = 0xEB2B98591252121FULL; std::uint64_t aWandererH = 0x8AD31C0EFEB7B731ULL;
    std::uint64_t aWandererI = 0xF51A113173B2B25EULL; std::uint64_t aWandererJ = 0xEA906C6C414C8D73ULL; std::uint64_t aWandererK = 0x9A4403760DF79A14ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10761756856967610160U;
        aCarry = 9331286949321201786U;
        aWandererA = 15093176329696774641U;
        aWandererB = 14530143249634380323U;
        aWandererC = 14334740285993985873U;
        aWandererD = 14621522161542412543U;
        aWandererE = 13859331870076344666U;
        aWandererF = 12720465209065734354U;
        aWandererG = 14779870251331398943U;
        aWandererH = 13558423265371305254U;
        aWandererI = 16841596765820403381U;
        aWandererJ = 13371771407425466928U;
        aWandererK = 17115266412816621687U;
    TwistExpander_Menkent_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Menkent_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Menkent_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Menkent_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Menkent::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xA0D46682F0B14B6EULL;
    std::uint64_t aIngress = 0xD97A734BD8526929ULL;
    std::uint64_t aCarry = 0xD789EACA62601274ULL;

    std::uint64_t aWandererA = 0x9C3D23A695C4B912ULL;
    std::uint64_t aWandererB = 0xADFE09D35340DF49ULL;
    std::uint64_t aWandererC = 0xF991BCD5AB7A945DULL;
    std::uint64_t aWandererD = 0xE7EF96BA5F8F5FA4ULL;
    std::uint64_t aWandererE = 0x954B8B6F675B9CBAULL;
    std::uint64_t aWandererF = 0x97FD04DA85A1F55AULL;
    std::uint64_t aWandererG = 0x9F038325BC72D233ULL;
    std::uint64_t aWandererH = 0xC1C68A377B83DF77ULL;
    std::uint64_t aWandererI = 0x9D13A3BFFB53D5CFULL;
    std::uint64_t aWandererJ = 0x976AAFC3896168BAULL;
    std::uint64_t aWandererK = 0xD90065EB1498FA2CULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
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
    TwistExpander_Menkent_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Menkent_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Menkent_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 18 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1799 / 1984 (90.68%)
// Total distance from earlier candidates: 30762
void TwistExpander_Menkent::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 680U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1301U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1004U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1987U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 843U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 2046U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 333U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1625U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 718U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1102U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1694U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 724U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 791U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 644U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 385U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1251U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1737U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 621U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1123U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1134U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 367U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1227U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 754U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1786U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1232U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 512U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 38U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1319U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1509U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 792U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1261U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 199U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1438U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 604U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1364U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 195U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1141U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1018U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 113U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1427U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1783U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1549U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 386U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1038U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 588U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1375U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 140U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 153U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 268U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 221U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1978U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 345U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1518U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 615U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 467U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 853U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 529U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 883U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1051U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 782U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2000U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 34U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1776U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 610U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1179U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 750U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 915U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 868U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 866U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1237U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1511U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1374U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 232U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 238U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 625U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1653U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1142U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1333U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1926U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1916U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1907U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 390U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1523U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1497U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 65U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 707U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 977U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1779U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1736U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 779U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1166U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1646U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 241U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1691U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1362U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1284U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1340U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 595U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 295U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 650U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 0U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1450U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1419U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1949U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1299U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 36U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 230U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1662U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1059U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1064U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1594U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 422U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1655U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1735U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 249U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 536U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1940U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 67U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1833U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 449U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1350U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 370U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 19U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1143U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1462U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 880U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1888U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 648U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Menkent::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x9BD8207A7F14E8AEULL; std::uint64_t aIngress = 0x80380D28A890216EULL; std::uint64_t aCarry = 0xD3506CD6F7BFC236ULL;

    std::uint64_t aWandererA = 0xBAA84D1253119B8FULL; std::uint64_t aWandererB = 0xBB998CB0451A6D7DULL; std::uint64_t aWandererC = 0xEC58877323B39435ULL; std::uint64_t aWandererD = 0xCA1277A56D534F2AULL;
    std::uint64_t aWandererE = 0x94181DDC0138B213ULL; std::uint64_t aWandererF = 0x8A92C0E47F8DAFA9ULL; std::uint64_t aWandererG = 0xD9259A26879F2EF3ULL; std::uint64_t aWandererH = 0x8A6F0B63FD91131FULL;
    std::uint64_t aWandererI = 0xC2E45E08FFE4E639ULL; std::uint64_t aWandererJ = 0xC849DC51D76D0207ULL; std::uint64_t aWandererK = 0xA3FE6C6553990874ULL;

    // [seed]
        aPrevious = 14993062718224807208U;
        aCarry = 15671065191884858240U;
        aWandererA = 15186978181569037199U;
        aWandererB = 10763290742081830625U;
        aWandererC = 17974623984538453457U;
        aWandererD = 13241394570057092374U;
        aWandererE = 14496649871560033326U;
        aWandererF = 17254942439617512815U;
        aWandererG = 12949064247603365393U;
        aWandererH = 17709195622601420289U;
        aWandererI = 16856259370043266787U;
        aWandererJ = 11787799220239319935U;
        aWandererK = 16246980005173922703U;
    TwistExpander_Menkent_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Menkent_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Menkent_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Menkent_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Menkent_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 18 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9269; nearest pair: 492 / 674
void TwistExpander_Menkent::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3940U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 115U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4560U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7623U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7644U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7493U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8093U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5450U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5758U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6628U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3790U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5596U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6508U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7594U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6247U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7103U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 921U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1412U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 574U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 332U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1139U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1978U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1264U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 461U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 911U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 57U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 74U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 420U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1571U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 359U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1276U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1134U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1055U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 424U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1562U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1479U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 18 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9260; nearest pair: 472 / 674
void TwistExpander_Menkent::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3257U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8002U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4470U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7581U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7822U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1753U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 469U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4097U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7912U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3215U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5064U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2711U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7154U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3248U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2801U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6667U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 453U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 305U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 429U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 390U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 535U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1968U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 392U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 932U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1833U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 51U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 59U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 391U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2026U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 435U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 753U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1202U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 599U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1753U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1263U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1239U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseASalts = {
    {
        {
            0x59CC4FF0ABD0DA23ULL, 0xAA57ADFA872E5594ULL, 0x838A9646429C66F5ULL, 0x162BD987592FBC04ULL, 
            0x95F4F6ACE89DA1DFULL, 0x2B7C6EC0A477D22EULL, 0x9CE4E5DFF3FA1D32ULL, 0xA2E2AEB00F15C590ULL, 
            0xF5C5ED4E472CAACBULL, 0x598B433FDB0C6C32ULL, 0xC6AADE1B3F8F6A75ULL, 0x648801D442986055ULL, 
            0xE82C3548B1A427CFULL, 0xB4003F4E15A947F8ULL, 0x4CCDFB248BF5E0F3ULL, 0xDB4761FF77E1CBABULL, 
            0x66E10CB7BF23AFBAULL, 0xDB0D1EDE4985D08CULL, 0x90CAB235EBF5619FULL, 0x41622B67CA9009A0ULL, 
            0xDEA929EC38821D9BULL, 0x4FA5D161FE9A1854ULL, 0x9E2F226CAF0D834CULL, 0x838ADA92A69F612AULL, 
            0x29C3244DCD47EA89ULL, 0x6F35DB6FFF8BB5EBULL, 0x1D79E28871AE1226ULL, 0x4773A0C4858919BFULL, 
            0xA9460DB3B0E6B75BULL, 0xCC415D5B2CBE586AULL, 0x78A09F853F3D34B7ULL, 0x3D8F7ECD1178F256ULL
        },
        {
            0x5207FB104F8F75BAULL, 0x05BE72794B0DAD0BULL, 0x7884065B4904C8EFULL, 0xF9035E50DFF226B6ULL, 
            0x3C53BBC4E904422BULL, 0x9FCB1851EC49631BULL, 0xE7B059995C6F70F0ULL, 0x763511256A27A224ULL, 
            0xF41934AC902CDA8FULL, 0xD02F85DC2DAF3567ULL, 0x9D9568E785129D76ULL, 0xF9175D4D14235AB5ULL, 
            0x6AB5E5ABE04EC613ULL, 0xAE6DADC2F82BAEAFULL, 0x7171221365A92658ULL, 0x2C12ED96F39C8AA9ULL, 
            0x877FF6554EEF91C7ULL, 0x4663FF21CE2A5CB8ULL, 0xD7E07362E71E2CB9ULL, 0xEBD3122734EB4333ULL, 
            0x929A79010B0DCB82ULL, 0x6B0EE4A753D5E41BULL, 0x68D51F9FAFF7DE01ULL, 0x96F930BFCE775B47ULL, 
            0x4CD5877F2188279DULL, 0xE577755C56D4CE9DULL, 0x4BFEEA931AB09E43ULL, 0xFE38C0A01252AD60ULL, 
            0x40C0FCA37E6EF2A4ULL, 0x92AD9F2284361C54ULL, 0x8297AF48CBFB6F42ULL, 0xA1A2256AABA887B1ULL
        },
        {
            0x4152EA9F2332BC9FULL, 0x01D6E14DAA73E477ULL, 0xF9F981379AF797A5ULL, 0x354A6C432AAA0DDDULL, 
            0x33D2BDA18724D72EULL, 0x6628F0DB1C1552D8ULL, 0xEF6E309484DF9799ULL, 0x13B1C812D257AAF2ULL, 
            0xBD18E344CFDE84A9ULL, 0xEBBCA1CD45EE8739ULL, 0x020B5C034203CC62ULL, 0xC6F250EA25DFAD26ULL, 
            0x7FB59CC56873AD27ULL, 0xCBAD8AD2CD021F47ULL, 0x9AA528C5FD28D8DBULL, 0x0FE82E036031612AULL, 
            0xD3DF73BF5C9778C7ULL, 0x2BE08D45196EE071ULL, 0x10EA5A5CBA4F90B4ULL, 0xBAA975BF43BFB846ULL, 
            0xF86FBADF92718919ULL, 0xF64CC5EA536C4F90ULL, 0x1C358E6669AD51C1ULL, 0x7068BFE95C06C2A7ULL, 
            0x1E830D8D3868378BULL, 0x219B7F4C7A274993ULL, 0x90D0D0C41C65B15BULL, 0xBDDBD30DCF35A636ULL, 
            0xDAE85C92DBC50A08ULL, 0x620844829E5F86E7ULL, 0xB0A8F0F503C73A4FULL, 0xF23C633A0E0FE12FULL
        },
        {
            0x1F859679FB5A565BULL, 0xFA38D1C722FABAB8ULL, 0x7FA5E4402DBDF4A4ULL, 0x16303805998197C8ULL, 
            0xB5E26563C64794BEULL, 0x09D4DC2362B356B2ULL, 0xEA5C1ABD4AE3760FULL, 0x84E6986AABD59E84ULL, 
            0x62CCC96EFE7E08F0ULL, 0x62F57146DEA2D09EULL, 0xC4C919C9917B668FULL, 0x246A44690F4496E1ULL, 
            0x7EF0F585346780F1ULL, 0x843A58296D66A8C2ULL, 0xE2F1D2D442F8F793ULL, 0x00BB6C21814D1F21ULL, 
            0xBE1084513CC9046AULL, 0x519E4182BE2A6E0CULL, 0x95A2F2F38AB90C19ULL, 0x535BD1F31A2059F0ULL, 
            0xC9B3337285C97ED9ULL, 0xBF8D99EEF00EABB9ULL, 0xB9B0BC9E46107FEFULL, 0x5F293F87334BC9A1ULL, 
            0x7E6774C73B707713ULL, 0x9C8DA33A3DE592ADULL, 0x2FF4C166FAB7DC1EULL, 0xFE9404BAA3FC1E61ULL, 
            0xEE9FDF54A141A5D4ULL, 0xE90B6519D394D76CULL, 0xA1498D7B5A245C97ULL, 0xEE6E0448A705CBDCULL
        },
        {
            0x81DF4E434CF39A28ULL, 0xD6D12C86A93BD6F0ULL, 0x7BDD008D3ECC4681ULL, 0x0DFF8E9211CF5E2FULL, 
            0xA0ACA30024CE29DFULL, 0x7CAE2D38891EDD64ULL, 0xD1B744CDAB7CF9D3ULL, 0xAC67BF35B21ABFA3ULL, 
            0x380F374674C47E15ULL, 0xD4358FE2F8D92E0FULL, 0x69A231A0D6320B30ULL, 0xEAFDBCDDF9A7651EULL, 
            0x2110660E28A00242ULL, 0x894C48FB7BBB23F5ULL, 0xA96588400A0E3A95ULL, 0x13B408E8139E6D95ULL, 
            0x6BEBFBC2722AA0E2ULL, 0xAAC571371215C798ULL, 0xDBAB00E0782163FCULL, 0x137DBF0FB9738688ULL, 
            0x4140794934733FC5ULL, 0xB09CBAD35BD7A06FULL, 0x4671C24E2F68B40CULL, 0x2A1E3B8B11634D7FULL, 
            0xAA2FD87B5B3AD0EFULL, 0x28994962B806BB3CULL, 0x7A8C630937E7298FULL, 0xB755512897C4F206ULL, 
            0xB7D290AED1844D6AULL, 0x877658DD78113878ULL, 0x1B9C0C15F505E7D8ULL, 0xAEAF58F109EBC8FAULL
        },
        {
            0x84E75F335DC8C910ULL, 0x4787E46BF2D57C2EULL, 0xF97D595D6C57E038ULL, 0x993552F571602AFCULL, 
            0x7FCD9CDD48E76B71ULL, 0x20DEA242D12FAC7AULL, 0x1C0A9FE79FA1A2EAULL, 0xDE372A0605B00C2AULL, 
            0x0462F498DC00A2E2ULL, 0x7010F310E125312EULL, 0xCD75C772470BA84DULL, 0x3F1DC11AB29FEDD7ULL, 
            0xB5A7BD84CF9D96ACULL, 0x944884EA1C6FE95BULL, 0x54422494697A8C46ULL, 0x46D2AD6C0EC8458FULL, 
            0xB58D5428C9A8276FULL, 0x26C6E06BD839458FULL, 0x884C3CDC27397CFEULL, 0x88A7A41AB4C16815ULL, 
            0x8682D1A42E6815D4ULL, 0x434E1A8F21D6D759ULL, 0x4FA8C56C79C0F7D7ULL, 0x3F5D2C0ED026B214ULL, 
            0x7050DEE4437B350EULL, 0xCD192C6EE6D31CD9ULL, 0x1076B730B89FEBAEULL, 0x491BB37EFF703720ULL, 
            0xC76034B7D8DA81AFULL, 0xCB4DC89E121E29BAULL, 0xE68C3C9F92386F7FULL, 0x77CF15276FA45244ULL
        }
    },
    {
        {
            0x60AD81F07C4A6447ULL, 0x7E63E5036C458A0FULL, 0xE55AA8969EDFA7A4ULL, 0xE87965C0A4BA51D5ULL, 
            0xC95210B34FA0A34AULL, 0x550D6854C0D694F0ULL, 0xCB4C9E9FF4082C06ULL, 0x7D5075A6D7BF71FAULL, 
            0x5631CFD799298177ULL, 0x6EEEC516EC7CEFCEULL, 0x48237CE4C381B760ULL, 0x3E23623B76B595C5ULL, 
            0xF664D440886E5F7FULL, 0x08A4C903B833500DULL, 0x06726C4CBB90AC96ULL, 0x9B37A8571BC34149ULL, 
            0x2B1B9CE9A82ACD0AULL, 0x9C9249D5FD2944D3ULL, 0xD081DBFB1D3A90E4ULL, 0x05B8C8F47C8EB44AULL, 
            0xAFBFC614F86103E6ULL, 0x3A9ED3A6678D6665ULL, 0x30B71B1AA373CF6BULL, 0x55EE50F04C587E2AULL, 
            0xE2427B4F62D2DA17ULL, 0x2FCB39031217A7C5ULL, 0xE32B05D50312793AULL, 0xEA9CFCEDE2FE6752ULL, 
            0xDC583EA99689FBD2ULL, 0x4CBB985667BC2079ULL, 0x4AB1E24F5C5A6499ULL, 0xEF3EE2F4A95C1FAAULL
        },
        {
            0x2E71053AAF5FA56AULL, 0xB0CA54E135EE59FAULL, 0x54B586C168CF781AULL, 0x1FB6AFDA327EBBA7ULL, 
            0x7D7E2594EC2410D8ULL, 0x7048DFB3E8236B84ULL, 0x29006091960ABD82ULL, 0xEA6B91B1D32D9384ULL, 
            0x5E2AACF750CCA0D5ULL, 0x70F6D1DC03209541ULL, 0x65C68001237ECA85ULL, 0x99D123D37A07BAC7ULL, 
            0x7E473A4BCEA944E2ULL, 0x6900FFF8EA31D31EULL, 0xACF1E0062F9574E2ULL, 0x2F30BACC313A8047ULL, 
            0x56FB9F19B665C789ULL, 0x1528FAFFB940B8ABULL, 0x2FBB221A25AA89B8ULL, 0xD451055A78EA10D0ULL, 
            0x66362170542E3ED2ULL, 0x78CFE41496784629ULL, 0x6D47A55E1288B80CULL, 0xFDB90886B1FED4F4ULL, 
            0xBA0A629649846ABBULL, 0x117F27C9862EE3A9ULL, 0x701105EE120A4F51ULL, 0x4D178104849201BBULL, 
            0xFE4AC135CD71A8A5ULL, 0x8313C07C0AF4FDB3ULL, 0xC5771037BFB2DE63ULL, 0xCBBA39C1AC372DE6ULL
        },
        {
            0x7FC8522BFDAF71B9ULL, 0xA3B2ED243A1CF232ULL, 0x718440C47B3727CBULL, 0x19CBAE78634ECA09ULL, 
            0xC09B0271C0DA0989ULL, 0xC05A6C430AA3B943ULL, 0xE4CA662F77C6BDCAULL, 0x01AAE8F4D3648EF0ULL, 
            0x3B867869E6BEF939ULL, 0xB9C60C0C0D7A0986ULL, 0x7A9152062F98F1D2ULL, 0xC402DF2A40B39236ULL, 
            0xE57EDDCE8E0A2052ULL, 0x8AADF0FC5327907EULL, 0x5FF62C1E57297441ULL, 0xC9EEE23B70B759EBULL, 
            0x55956AB32A35A9A7ULL, 0xA6EB9567D4158BDCULL, 0xF9364F2A0B7C5E5EULL, 0x763EB43FEFBE3CF3ULL, 
            0x27C5A54E16C9C5CBULL, 0x47D1DBEEFB11FA4AULL, 0xEF962D85B62255FEULL, 0x94C85FC47BC744D8ULL, 
            0x01A0FFD6047C5500ULL, 0xC287D9C0C5B291C2ULL, 0x5FF5972290A61FB8ULL, 0xDF39BF9BB1D63290ULL, 
            0x868A1C06E9100495ULL, 0x018510F23D6CC092ULL, 0x638E9EACD202A3ADULL, 0x5BFE484995825E68ULL
        },
        {
            0xD0F464FF3CE0852DULL, 0x735F510A108D60E2ULL, 0x3188C71172AC6BC8ULL, 0x64D24D37756FB7A9ULL, 
            0xF9AA9C311326217DULL, 0x3A9E8E50889E0D04ULL, 0x25F08A255B1E9364ULL, 0x2146DDE1E08829FBULL, 
            0xC9119ABDE198E79BULL, 0x91ABFCA82CDED12CULL, 0x9750682AD17776CCULL, 0x950703977B5BE8D9ULL, 
            0xCC5B67C19192A068ULL, 0xBF3725C9B9D41180ULL, 0x996C7B2D10CB344BULL, 0xE7F0D13748048F02ULL, 
            0xD48C0AEA15519FA4ULL, 0x6B69DE29303A4F7EULL, 0xD248E77B73151904ULL, 0x5A1943C9A2379C78ULL, 
            0xDF1F16DAA5D49673ULL, 0x89DA3A021C551204ULL, 0xD561ABCA315F813FULL, 0x1184E4B38F186910ULL, 
            0x3BA72A29C08C4C86ULL, 0x21D6FB26EC41C1E4ULL, 0xFF0EE0FCF1E92ED4ULL, 0x30884EF2F9580E56ULL, 
            0xCCEBD9DCA48596D5ULL, 0xFF5D58BC380D5762ULL, 0x0A8E9D9F6F2753C8ULL, 0xB417741EAE90550CULL
        },
        {
            0x165C9783AC09B731ULL, 0x7058A4079537B918ULL, 0x52BAF8FD6ED1A762ULL, 0x8FD1B3FF60E0ABF0ULL, 
            0x28CE4D30A91DE7EEULL, 0x55723A94C13B28B4ULL, 0x98981A63B59AF4AFULL, 0xBA613FA960C72991ULL, 
            0xC4EC21AD43E10177ULL, 0x6457E68A21CFFDFCULL, 0xFD2CCF6D4B134FEAULL, 0x4B9107D51EF53FCFULL, 
            0x41D755D4356066BDULL, 0xB42CD94CB46C5954ULL, 0xD3CD5A8E169A6C55ULL, 0x9ACBB4E871166A24ULL, 
            0x12910F8B9D06DED9ULL, 0x9D636C5380C6E431ULL, 0x5CD2C73D6F75E8D5ULL, 0xE62CF34B918D5E15ULL, 
            0x113217C2B2B3E587ULL, 0x5941BF5B29875886ULL, 0xA0A12FAF2D4E0A33ULL, 0xD392A357B51586D4ULL, 
            0x6AA1B67AC6D729FCULL, 0x3C5E6A170CDDF4DAULL, 0xA51CD124320D4B5DULL, 0x229B1499C4D3E673ULL, 
            0x4BBBCAAB94DF4E1EULL, 0x2354C38FD9A009B4ULL, 0xB065FADD8B597A1DULL, 0x3A5948A9EB8D269AULL
        },
        {
            0x25E3655CA3F4EE12ULL, 0x9596C3AAD75DF72DULL, 0x2B366173CCD3F92CULL, 0xA9AC997BB383F269ULL, 
            0x6101E68B96B56734ULL, 0xB7CB7E9274CAF6D0ULL, 0x3A12573A0FEC9419ULL, 0xD3B25E89873EE4FEULL, 
            0x44119FB9433A7A98ULL, 0x6B97DC9FF35C2252ULL, 0x24FA31A4F9FBA4C0ULL, 0x282240F9840BE2CCULL, 
            0xCFECB236C4B7CC4EULL, 0x9D57F317E3EE7C27ULL, 0x6B9B467669F76743ULL, 0xA38D17C1209288EEULL, 
            0x30FA458DF1003EE4ULL, 0x3893E8FB6B913425ULL, 0x6FB5EB99B17D2732ULL, 0xFE7B637315FA8B70ULL, 
            0x71280DB53860019EULL, 0x0FAE382E77DC39C8ULL, 0xE4905144B2BB5D04ULL, 0x20B951CEFD66666DULL, 
            0xDC226CE49DDDA808ULL, 0x02CA602DEAA45537ULL, 0x9DCA224FB2A25D3DULL, 0x97EFB5950A29EE5DULL, 
            0x91BA0A9DC52EEC6AULL, 0x095E1EAF38EEEC3AULL, 0x7AAEC14F99F47F23ULL, 0x322161B631A9227FULL
        }
    },
    {
        {
            0xB67CE8A1A92C1A1FULL, 0xDE48D9FA9EFD37D5ULL, 0x4C825713295035FAULL, 0x60D604F3E91AD20BULL, 
            0x2F3EF6BD51B96718ULL, 0x7D929435D31543C2ULL, 0x4A029DE88A36B384ULL, 0xAAEB97D9AF0507A3ULL, 
            0xC513F89243734578ULL, 0xE3A6F37D4E280D4DULL, 0xAC728F52E32DB1E1ULL, 0x7D9F06F2A1AB1F55ULL, 
            0x2E2497E067F0B725ULL, 0x9B60667EA2317B73ULL, 0x0DDBCFD852E1AF7EULL, 0xA816A4822D72F516ULL, 
            0xA695F15BE1900C83ULL, 0xE00747C0D68F986CULL, 0xC930D9CC7C6A5AE7ULL, 0x7B0A9B67D3101FACULL, 
            0x167378EDBE5FE989ULL, 0xAD5C61CD8CF071C8ULL, 0xBE0562E87B342665ULL, 0xC20D2657935B837FULL, 
            0xB9F0E5557A44660EULL, 0x275F7055DDE383F9ULL, 0xF54D236E81413918ULL, 0xFCA65055EDD33B8BULL, 
            0x131E5F885B05DF16ULL, 0xDECEAA520E9BE1C0ULL, 0x438AC8A1E23018CEULL, 0xD79894191C1C6F9AULL
        },
        {
            0xD443039109D15ADCULL, 0x88DD04CC8180841DULL, 0x91F4C3EB2F4AE422ULL, 0x000AC5F7ED2300EEULL, 
            0x821E4A888171588EULL, 0xF0ED14FEC17DD6F1ULL, 0x91DE694913E6007AULL, 0x986D8AA1A5C99693ULL, 
            0x707F70B58AFA915FULL, 0x515CE0846860D45BULL, 0xA816CB9F9AF7ED36ULL, 0xBBD559562FBC2FCBULL, 
            0x23CEC70F5688F72BULL, 0x926C4A644DECBD36ULL, 0x922078FCF6E1F5ABULL, 0xC8A3C90713014CA5ULL, 
            0x1CA11EE637DAB10EULL, 0x75DEA4A04DD390DBULL, 0xE428220FE0D13EA2ULL, 0x016B30CD26388A4EULL, 
            0xA1F8A451B0097F20ULL, 0xDF33F4DAF8ADEE12ULL, 0x678F92D21271E2B9ULL, 0x5DDCB60E921625BBULL, 
            0x46854B8DF594C197ULL, 0xCEE9C659ADD4F9F6ULL, 0x07D76C2194C26CF2ULL, 0x32E307CCF588A990ULL, 
            0x385D9D2538E04639ULL, 0x531A9E8812525B5FULL, 0x9EE598BFA5D484C7ULL, 0x3230B6CB557EF180ULL
        },
        {
            0xF85D09202DBA3548ULL, 0x1BCD23CC976ECB43ULL, 0x7ED0DCA73BAF4F1AULL, 0xEA279D2007D4F8E0ULL, 
            0xFF0EC8807AC00230ULL, 0x06146282BD03164EULL, 0x571CCFC775CFE7B4ULL, 0xD1270C15039C3C5FULL, 
            0xAD97BA052D67E683ULL, 0xE7015FF7D0211B8CULL, 0xCB6D47713AE00803ULL, 0x1916BD485F01FF41ULL, 
            0xA7B0F0E5D18E8850ULL, 0x54615D3F835392AEULL, 0x090C90086E6D1375ULL, 0xD342788F85552D6AULL, 
            0x9E905C9D441D8A2FULL, 0x97A39494B99A9394ULL, 0xB4DB35FC547F4FD8ULL, 0xE8AAA9023A5ABCCEULL, 
            0x4F06B713D51EBD63ULL, 0x91102C7885CFB7E6ULL, 0xD84CDDD998B1E0DDULL, 0x252EFE43A2319A50ULL, 
            0x54FB002023A1ED78ULL, 0xC77A8EBE28346697ULL, 0xA1FB2C307AA397AFULL, 0x1D7B6C26D01800BCULL, 
            0x20AC0E99A5B66F59ULL, 0x75A30378817BBBFFULL, 0xABB6179407D6BDCEULL, 0xBA753FFD59262287ULL
        },
        {
            0xA32D0C1C8A7855FAULL, 0xE23E3A792945C250ULL, 0xF81BF4100291597CULL, 0x8082C13ED2021A08ULL, 
            0x31C15F648113A930ULL, 0xFC8EFFB67A10FE83ULL, 0x554D6CC7483F2FD0ULL, 0x60D59A8F51E843D3ULL, 
            0x562FF7DD5C6289A0ULL, 0x0ABD7C5693D53D47ULL, 0xAF442675556E86BBULL, 0x4C6DE8CFE4AED6E0ULL, 
            0x631E3F30A278DBBAULL, 0x9341D39A2E0BD87CULL, 0x3E247AB3F07811A0ULL, 0xB53BA8CF85D5F2D7ULL, 
            0x5356E4BEF9F9CFA5ULL, 0xB778DCBF458558B4ULL, 0x993E2A9173810AF4ULL, 0xE01CD6E94E9E8232ULL, 
            0x3CA80DC53A06D64FULL, 0x14B32FF7ED4D4BE3ULL, 0x2EACF6370800E7E0ULL, 0x826C43F212970602ULL, 
            0x73695BE3689A5210ULL, 0x078190F3AC36480CULL, 0xC7BBA70A190E187DULL, 0xACEC8AD7BFFE9460ULL, 
            0xF906D580420D1B35ULL, 0xA40EA01F17563575ULL, 0x9C506A788106FBBCULL, 0x35C0E1D0C24D2B46ULL
        },
        {
            0x45B38A64FF76F8A9ULL, 0xEB598D5D4B9DB213ULL, 0x89A66D0CE709F3CDULL, 0x489F016CE252C75EULL, 
            0xE8E934B21D1A406DULL, 0x0E232B6027917E26ULL, 0x693057A3173A607CULL, 0x0B987E5E9B3C08B5ULL, 
            0x3AE7E1167A246CB4ULL, 0xB51C8A0C0737B612ULL, 0x22EFC088302E9E14ULL, 0xF485F6F4D2CE9E7EULL, 
            0xEC5FB6AA30643176ULL, 0x56B7CD5A2FCA962DULL, 0x65A8C0D7434A739CULL, 0x5D72DF9BCA3FF606ULL, 
            0xFA611808F9604D30ULL, 0x8FFB851E0275EC39ULL, 0x44FDAA444DB00624ULL, 0xB96F3F2849F2022EULL, 
            0xCBBBA15CE34D9528ULL, 0x40848932269C8078ULL, 0x9970180C3A095C81ULL, 0x396A51CABADF72AFULL, 
            0x62C30C96DBB2D24DULL, 0x2BB31C8F5E2A5253ULL, 0xD17D64B12FC4C095ULL, 0xAE1F6871CFD87834ULL, 
            0x7B37D4D1E82DF401ULL, 0xE662EF7381169D37ULL, 0x3414395B1E9C0301ULL, 0x7797945F431B2284ULL
        },
        {
            0xEBEB23A244517E9FULL, 0x0FDA977A0CF0D424ULL, 0xB2A8E90E2505AC0DULL, 0x6A74953B4AF5B235ULL, 
            0x88CF36E6FCD57E47ULL, 0x3A0FB2F0B7F85B68ULL, 0x0F0C6986486011D4ULL, 0x5138E2C30977E08FULL, 
            0xE69EB6B91D73044CULL, 0xFDE36BAB0BDB3802ULL, 0x344C0FBC579604D8ULL, 0xD8FDD628DAA17F76ULL, 
            0x9DA05114E3B5562FULL, 0x4D87FEF0588F81E5ULL, 0x0B997E0EF2575626ULL, 0x034D86C1F2E7F037ULL, 
            0x3B34D1D9659CF3F7ULL, 0xFB8F0F028BC3A462ULL, 0x0FA4876C4F11A8E3ULL, 0x39808934B66CC48AULL, 
            0x9A3D4B1FA18D7C87ULL, 0x388B8D34E657E5B2ULL, 0x93D9A93EF6C6ADEAULL, 0x87C34C5F125495F1ULL, 
            0x23BB14AE52ADAE54ULL, 0xDF4A983C2677DA12ULL, 0x5A16734336FFA13DULL, 0x5D56E41F492BFD7EULL, 
            0x19ED200336BC58BAULL, 0x8621FCA865000C58ULL, 0xE31C8AF011083FC0ULL, 0x5D6FCEA6A84823A9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseAConstants = {
    0x16564519A5592A18ULL,
    0x8F034AC06D549CD0ULL,
    0x86D7F970EFCA8723ULL,
    0x16564519A5592A18ULL,
    0x8F034AC06D549CD0ULL,
    0x86D7F970EFCA8723ULL,
    0xDA627069E64AA676ULL,
    0xA4981EE5417C97C4ULL,
    0x84,
    0x29,
    0x54,
    0xED,
    0xF5,
    0x60,
    0x23,
    0xFA
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseBSalts = {
    {
        {
            0xBF88B716190F6340ULL, 0xD40FF5CAAFCDBC90ULL, 0xA306C87F0BF1BCA2ULL, 0xF7577AFB54129414ULL, 
            0xE6F5CF3947DE7350ULL, 0x3EE65D7650CF3C6CULL, 0x92B85584E8797D84ULL, 0xD009160D8DE652CFULL, 
            0xBEA78E6512489DB0ULL, 0xCB2D6BD4F7EDF828ULL, 0xB7DAEBCD009F4A2DULL, 0x24A31D0BB351B16BULL, 
            0x43F5ED0E23B7B911ULL, 0x74B825D07189CC11ULL, 0x87C46A9DE804C326ULL, 0x43F9FE2793E428A4ULL, 
            0x1D8B50763474613DULL, 0xF6483428F14B2E9EULL, 0x4A625B61453B5ACAULL, 0xD27841716FCE6125ULL, 
            0x0D14C1D1393995B1ULL, 0x3C96CE436CA0560EULL, 0xA6F25C31CBF3D875ULL, 0xF232FFB402F6C62CULL, 
            0x27CF43EA297F6B5CULL, 0xA5B4D7997B749E3FULL, 0x2ECDF4C92F9CFA17ULL, 0x3687FC1B88E2C568ULL, 
            0xAF68B7AABB35D93CULL, 0x99C487BA617FB878ULL, 0x14797BD05D7C2487ULL, 0x101E541369390A75ULL
        },
        {
            0x0F59B79CB7B29CF6ULL, 0x194E1EBA01BE718BULL, 0x972CCB1E1C28F8DDULL, 0x3B1A22A9939FBD68ULL, 
            0x038B367E7C055A6AULL, 0xB96E20D7853509D1ULL, 0xD9250CC9B844D140ULL, 0x0C7D52E5872E9AB4ULL, 
            0xC7A81ADCE2CF3D08ULL, 0xB30937B1ACAEA11BULL, 0x78E99B1872350791ULL, 0x6BD9D3203BD5F23BULL, 
            0x14847C105DC8FE15ULL, 0xBC8941FC8C60FF6FULL, 0x8AF51616137A78FAULL, 0x3A0F189ECFB2C4C4ULL, 
            0x589AEBBF2F592F9AULL, 0x17AC77D4ACDCEA3DULL, 0xC91C9E5BB6178C0CULL, 0x79981786AB0FE549ULL, 
            0x8401484454F28E00ULL, 0x26B4686490E21A03ULL, 0xD2380CC2413F3A79ULL, 0x7034F636DABFC084ULL, 
            0x2BA592F24A519601ULL, 0x584B151BC74CB74DULL, 0xF4063859EF297E68ULL, 0x097B17D2988458F6ULL, 
            0xE231A30ABA97678AULL, 0xEE1BFE1F8CC28683ULL, 0x5173C409217513E1ULL, 0x5C0A2CC2825DDB51ULL
        },
        {
            0xA03FDC79F2A138FCULL, 0xAC8985EFE08AD934ULL, 0xCA4DA69473643FDBULL, 0x97D42863FB08F3DAULL, 
            0x5FFB78A0D215371FULL, 0xBCB7D4FA936ED77FULL, 0x27DB815AD87C6194ULL, 0x347C544B11038DD6ULL, 
            0x0B8A54AD81279AF2ULL, 0x627A54D518089900ULL, 0x8EAF77B0C489376BULL, 0xA9A90E7DD3A04220ULL, 
            0x6ADF0ABF749BCF86ULL, 0x430BB26C3DB9F99FULL, 0x10137AACAAB9DF8CULL, 0x2AFC096ED349F883ULL, 
            0xC5F2A184E65EE6C5ULL, 0xAA1157D544C01B41ULL, 0xEEC0A3C883CABB6FULL, 0xC62D2A0064C04665ULL, 
            0x25DE3E1B4FE4B7AAULL, 0x174F50789DF8685EULL, 0x7C3474151F9B509DULL, 0xD7FFDADEF66A8056ULL, 
            0xB6E760AF0AE73ED3ULL, 0x91BAA5AAB32CF72CULL, 0x69551C5CC5A1911CULL, 0xD5A2C97F230E9985ULL, 
            0x433125AF0563A83BULL, 0x940DDC6D340E42A9ULL, 0x7D7960C0F124ABA6ULL, 0xE00FDDCA34A9454EULL
        },
        {
            0x664A825178317418ULL, 0x43C644A451A44F78ULL, 0x771725D741D29B1DULL, 0xFD4276E16A8AD949ULL, 
            0x07964C21EEAE6934ULL, 0x122FD7EE9E397C2CULL, 0x1B55827627C50EAAULL, 0x913C003CDFB05466ULL, 
            0xAE155EBEF238DC4DULL, 0xB73EBE1F34EF3A26ULL, 0x2D213C2AF38E9EA3ULL, 0x71FB4BA5FDFE11DEULL, 
            0x975EA1BB358F6E01ULL, 0xA180167846398618ULL, 0xADB3B17C9AD89A5FULL, 0x684C64B033AB8DB0ULL, 
            0x73A1C91D02B2024AULL, 0x414244E3468CF39CULL, 0x9E755EFEABB60527ULL, 0xAD6F64C362E86A5AULL, 
            0x8C1985CBCC45BECFULL, 0x6A2466EA4B7D14DAULL, 0x50AFE504B53E5778ULL, 0xF514B599157C3D4CULL, 
            0x60604A547CDB4353ULL, 0x70E90E719D0DC307ULL, 0x2A2AD32B6FC10055ULL, 0xD2E061EFFDC8524EULL, 
            0x05FB34028F016CC7ULL, 0xBB5A52D306771116ULL, 0x0C913E6DE3C67EC7ULL, 0x4CFDEBA12E5D64C8ULL
        },
        {
            0xF58C142162B29755ULL, 0x603682ED39DDA8FBULL, 0x052B32C9916A2680ULL, 0xE06DB7BB9777187DULL, 
            0x90D74DED14DB54C9ULL, 0x6E4F2F54C651BAB9ULL, 0x37C2795F6855E972ULL, 0xB619D7EA85C038C1ULL, 
            0x37ED07BD4241C534ULL, 0x9314E1525C3C2886ULL, 0x03DF2612E21C00E9ULL, 0xC0F2A25F3D16AC13ULL, 
            0x9FB3FB493C81B255ULL, 0xF864F2CA47B563F4ULL, 0x9117567F23153AC2ULL, 0x543048F714F0FC99ULL, 
            0x65DAEBF4E52E7977ULL, 0x751FF57D9612D086ULL, 0xC8F9C8E529211273ULL, 0xB63DFCD94AAD4B04ULL, 
            0x604D134711DC5A0EULL, 0x7E2F473EE001BF22ULL, 0xFA119EB66DA9373CULL, 0xFA5B3A71384A0494ULL, 
            0x817B97DD73057808ULL, 0x55EF9D231FC72BD3ULL, 0x692B8C5643399F03ULL, 0xE50284B8A82C5BF6ULL, 
            0xD39802A5C01973C6ULL, 0xC07276E24BD5EFC7ULL, 0x4DE587F2208D0288ULL, 0xEF96EBF3E2B7D22CULL
        },
        {
            0xFBDA281C4A4AD164ULL, 0xD2F95CF1AC809886ULL, 0xCA59F6F6AD7DC76CULL, 0x90DF73D45542C148ULL, 
            0xD528B1130895BE7AULL, 0xB31012AD9C14F1C5ULL, 0xB287D979D4E76F98ULL, 0x690AABBA688F5540ULL, 
            0x4B354C302D6DE12EULL, 0x23ED5DAC2E139C63ULL, 0x6FCB3C4842116635ULL, 0x978B359841572116ULL, 
            0x8071924DB9D7AC5AULL, 0x070E4AF2AF277833ULL, 0x47771874D24D3448ULL, 0x94D07B35E9C6AC8AULL, 
            0xF2523E1FD8CB530DULL, 0xAC2FFD57AC3C6EB4ULL, 0xD791606779F1BB16ULL, 0x7526FA8A29D123F4ULL, 
            0x837CB2C5E8CE5AA0ULL, 0xAACADAC84A1BB7EBULL, 0x59A15918C6ED510DULL, 0x08155EE9EEE78A42ULL, 
            0x23A337BCCDC28624ULL, 0x56CA3EEDFCC98414ULL, 0xE4615DFE50AE9E03ULL, 0x771EC4E22D4D8D1CULL, 
            0x91602787FFCADAD1ULL, 0xE0070B33964B40E1ULL, 0x5C14A8BD5AFDF324ULL, 0x41F08FA0A8D1CFB2ULL
        }
    },
    {
        {
            0xF79F846E27D4CEC1ULL, 0x7E53161C7DB42249ULL, 0x7F9A5920D8805D1EULL, 0xC15128F43841B9DCULL, 
            0xD4E99434C99531FFULL, 0x0ED0C73A2BF35818ULL, 0xF1DF9ED00FD52045ULL, 0xF8AF58BB6F8B0C5FULL, 
            0x9CB50E78B22A59C4ULL, 0xEE5F3024321EF8D7ULL, 0xCDADB68D8FBE67B7ULL, 0xDB6AA06058A5E3F6ULL, 
            0x40E7EB8AC9BB132BULL, 0x6A68C24C4F877AC8ULL, 0xD3C00EA3783D3BBCULL, 0xD91F330ECA432C27ULL, 
            0x31B51A46CCE6F383ULL, 0x787B6F0EFFA87962ULL, 0x85510128CAF18017ULL, 0x2E10F19F96B43225ULL, 
            0x18D1D306A3067D1AULL, 0xA5A1C71EA4C0AE81ULL, 0x4F136733ADCE7627ULL, 0xEBAC5A12A64EEB09ULL, 
            0x49B970CE3F185249ULL, 0xA71C71B56CEFEFACULL, 0x0B17DC40EB3374A5ULL, 0xD418E3CF72A37877ULL, 
            0x555464A8E0D9FB39ULL, 0xF0540B65056A8247ULL, 0xB591800A0E6F0056ULL, 0xD0A63FF6DF52B524ULL
        },
        {
            0x48DAC3E9A8949272ULL, 0x1830ABA78ED6EF3BULL, 0x8F9EFCB9346973A3ULL, 0xE6C97AE783EB05E0ULL, 
            0x73475636B1F22414ULL, 0x093193C929A37BEDULL, 0x4CD7AA310A25D13FULL, 0xC2ECE295D03E2C94ULL, 
            0x39B15092B5ABCF5FULL, 0xA73369FA2B7E9FDDULL, 0x237FF21C5C946A7FULL, 0xA34DE5213181F5EAULL, 
            0xD78724210A03B6DEULL, 0x72AA924D7C7B2413ULL, 0x8D12269410E9127BULL, 0x0CEE08C96F7D3400ULL, 
            0xB0532D021B0ED29FULL, 0x63680ADC0E1FC0D6ULL, 0x5026101499C38963ULL, 0x92B1B675AE1E75C4ULL, 
            0x0C05972BED544320ULL, 0x351BA74C45E4DB0BULL, 0x1DA46581E6C830F6ULL, 0x2198AE7F993E461DULL, 
            0xE780590B26DFFE9BULL, 0xC6E02E0C0AE08939ULL, 0x42A71811991DB5F5ULL, 0x101C5F082B0B3F06ULL, 
            0xA856478A9142A9CAULL, 0xED60A4091BC01790ULL, 0xF8AF97E83BF4A314ULL, 0xD9DC329A691D37BBULL
        },
        {
            0xC5BBE3563D9D771CULL, 0xA40A85D5EABEE595ULL, 0x0658E7347B65BBB0ULL, 0xDD6049C06FF55210ULL, 
            0x93BAB5295C32E198ULL, 0x339A278E97FAFF3CULL, 0xA89986AB62498A71ULL, 0x3EA368A809C2F714ULL, 
            0xA3D5BCDA172F7696ULL, 0xF44D23D4C1C3C9AFULL, 0x7052E787330F382CULL, 0xD41F58054656BC9BULL, 
            0x12ABFBC0B336F21EULL, 0x9BBA632D4109D4D3ULL, 0xCA229DD943175F7CULL, 0xD194DD4C4AF279C8ULL, 
            0x2D4A17010133C113ULL, 0xD8F4A0E8D0F50DCEULL, 0x4F02D74B1B51CDA2ULL, 0xD3EB8D5D9442A3A6ULL, 
            0x118CA82B3D0FF786ULL, 0x9A6C237C2B4B6B56ULL, 0xB50EA47FBB83A1BBULL, 0x47467AEF4AD4D697ULL, 
            0x1F7EFE0DF3768481ULL, 0x30412E83F27729EFULL, 0xFC9679AF16EE73DCULL, 0xC0C437F6BEA0C1D7ULL, 
            0x284F125EC17CC3FEULL, 0xAE8AAABBA96170E3ULL, 0xB96F2F04FFB045B8ULL, 0x6921E7A38591A3BEULL
        },
        {
            0x166F4974E404FB57ULL, 0xC67BCC7EFAE0E561ULL, 0xE80958B73DD9DE46ULL, 0x30F253C17E4E6A7DULL, 
            0xB9A692332D5B75B9ULL, 0x46442C825F8A7465ULL, 0xAAD95E2319EE3D94ULL, 0x6A849F02B30CB178ULL, 
            0x55EED60B7C68CCD5ULL, 0x3F25C4F55E13A89EULL, 0xA51FC6E8B8D08DA8ULL, 0x39FF5CF2A6C6EAF9ULL, 
            0x0AF0542C99DA63AFULL, 0x08DBD3F5483B3182ULL, 0x243E9EC329FAA504ULL, 0xBE5D13B340ECF451ULL, 
            0x992C9DECA90BF1FCULL, 0x8A14F6B0A7B3EACCULL, 0x1A0FF46524A1BEF2ULL, 0x0FD22E03E79D62B7ULL, 
            0xC43986053EF1A781ULL, 0x8730073949BC8691ULL, 0xDC31ACBB0849633EULL, 0x851AA4F03D530D68ULL, 
            0x828E66D1EC156EF3ULL, 0x20BE3ED8CF8C8499ULL, 0xF080D1352F55B974ULL, 0xBCA10AB7A8D6161AULL, 
            0x0A6AC2211C381A08ULL, 0x5F6CB1F476025AC7ULL, 0x1E500DFF8FE47AF2ULL, 0x8530AA69FB61B93FULL
        },
        {
            0x066FFA7E30990F2FULL, 0xB1AA04D5FB05FA0BULL, 0xABE9CB6A0CFBFA53ULL, 0x3FD232567EC9577DULL, 
            0x18A24EFEDE35F694ULL, 0x6FC7228AC8F55FBFULL, 0xBBC05AB3196B663BULL, 0x4F0E949D5FA03212ULL, 
            0xB62EA8D8694CAF67ULL, 0x89C52B65174F647BULL, 0x77DBB8E83613F861ULL, 0xC983F430F651BBEEULL, 
            0xAFA81A61F9343B91ULL, 0x615082F3D1089088ULL, 0xF23C81F64E183388ULL, 0x7C10BCEF3C9E42D2ULL, 
            0xB37121DC4D9B1BC8ULL, 0x17EF267106D213C9ULL, 0x053E754D8A2F5A01ULL, 0x3EC48B88C51E46F5ULL, 
            0x8CAD27D2772255BDULL, 0x39AACAD5BD951740ULL, 0xD48D381240E9E2E1ULL, 0x4F6C61847AF558DEULL, 
            0x89F160BD85EE2DB9ULL, 0xA36B45225BC96BAEULL, 0xC1CADB7FA4B57C59ULL, 0xB27CB6D44817CC55ULL, 
            0x053D974103475570ULL, 0x3E1FDBD11653FDB2ULL, 0x4AFA8C074C377C4EULL, 0xBF19CC41BA2BDDCDULL
        },
        {
            0x4DE8A84321D62F40ULL, 0x3E2A423DF9D8069BULL, 0x29A8977A60C4A9A3ULL, 0xDB5543429175E91EULL, 
            0x42CADEF0B7767899ULL, 0x92936F2F288BC214ULL, 0x2CF4C071E67AE2A7ULL, 0xD708B81DEA60A34EULL, 
            0xF9C9F2C51B7EEC9CULL, 0x81F744C575CC906AULL, 0xF32995E0313D6CC4ULL, 0x8B622DA9F0CF504EULL, 
            0xC50BCF592E65B5D6ULL, 0x9B80D04D780AB2B2ULL, 0x16C5DB113E89AD37ULL, 0xB719C4103FB285B0ULL, 
            0xDDA4A5D1A037954FULL, 0x47C808E4C6C93597ULL, 0xBAA239404CA2DAF3ULL, 0x1E883B933E28AD78ULL, 
            0x274FD66CDE030D90ULL, 0x6ADB76553CBBB14DULL, 0x42A3A7F913C8BF3CULL, 0xDC136F7596539C29ULL, 
            0xBEBA49F7AD64B81BULL, 0xCEBD8F227A0FE419ULL, 0x8C9361D45F0ED70FULL, 0xBB56F3410D69C686ULL, 
            0xDFB830C80B311FA7ULL, 0xFEDFDCC194C200B2ULL, 0x6EE62953BD6E9AC8ULL, 0x84D6BE8FB08797FFULL
        }
    },
    {
        {
            0xE74F85ECCDE63545ULL, 0xD281176A7171ECD0ULL, 0xC54996D8AC04DA9BULL, 0xCCBF6B98C8C58F5CULL, 
            0x2307E057B46E6F51ULL, 0x601D8F5CA99109A5ULL, 0xC4203DADA2C8AD0AULL, 0x0C7B7E9582AEA002ULL, 
            0x4F5844B2F69DEAACULL, 0x3C7870C1CB23C8F6ULL, 0x5F874758C331BB83ULL, 0x64773403CF3610AEULL, 
            0xB1E251725C840B39ULL, 0x3011D04258126F8FULL, 0x77A96F57022AC89EULL, 0x6A848DC0F43B5BAFULL, 
            0x7E36E506CC531851ULL, 0x747CDF33434103B3ULL, 0x30F11AA981B8B8C7ULL, 0x6450D56181F59993ULL, 
            0xDA934A3C0522B866ULL, 0xA4230BD1C1654557ULL, 0x5695F273CD1942B2ULL, 0x45BEBA0340642429ULL, 
            0x67F749772A3B6E03ULL, 0x3D964CA9A8A33913ULL, 0xC1013BF16A409526ULL, 0xAF31CCE13531052EULL, 
            0x3DDF456212F41FCEULL, 0x6792E235384E1E7CULL, 0x424B6661AB4CB2FCULL, 0x8573CAF8AAAE949EULL
        },
        {
            0x01BAAC83DAA35A66ULL, 0x8239EDBFA3A2F055ULL, 0xC78946335B25CF78ULL, 0xD5388040114C243BULL, 
            0x3BB68589757B3E73ULL, 0x36DA2DC663CA63E1ULL, 0xA4B1771D37AF4918ULL, 0xAA90CC965AFA6A16ULL, 
            0xE1B919A8DDD20A9FULL, 0xF3F6F24BC63AC365ULL, 0x03B3672588C6667EULL, 0x16EEE00AC8AE04B0ULL, 
            0x9974995D74870086ULL, 0x81E2FD8D6C101DFCULL, 0xAA5CC9DC72D1A133ULL, 0xC9D5B68E93BA18C5ULL, 
            0x47DACADE6B0C8839ULL, 0x890BBD001662007EULL, 0x0B28F1B077FDC070ULL, 0x9B8F8E162E136C01ULL, 
            0x552C9AC577960476ULL, 0xDD4DAAC1D8775962ULL, 0xC24578273E0F4D1BULL, 0xA2C23D24CDE4678BULL, 
            0x17B5F7A1FAEE4901ULL, 0x602CD38564D5F3A9ULL, 0xEEF12A36CCE5E065ULL, 0xAA912AA5BB71D442ULL, 
            0x295C111269918505ULL, 0x5195CE302CA44301ULL, 0xD11D29C0380BF20EULL, 0xFC407C326D1557C8ULL
        },
        {
            0xDB781D2610BDEE4BULL, 0x169B7FAB933DB20FULL, 0xAD0E57AFF1FD15B3ULL, 0xA536FE654FC8D32AULL, 
            0x84A42731993CF9B2ULL, 0x49481CA121750B5BULL, 0x903957E01C0F3630ULL, 0xD8518C71F1A7B0DFULL, 
            0x0C73D387007DD094ULL, 0xE23C53A84387D710ULL, 0x73FB47CF03CD47D6ULL, 0x37B4792A55E56247ULL, 
            0x7FD7235DB7A9936BULL, 0xE383F62D70F62420ULL, 0xE6622858E2954EB1ULL, 0xAE40DF4BEBCA40C2ULL, 
            0x9EF5E8B8A9DFFE9BULL, 0x4D00EFDA113BCC4BULL, 0x5C3F9C06B7967708ULL, 0x92FFE22FD4998BA9ULL, 
            0x480CE45B61646257ULL, 0x316BC535EDC6470FULL, 0xDE7BEF202BFBF925ULL, 0x4B860345639A414CULL, 
            0xBF673A0B5FF83A48ULL, 0xA54FE5AA46CDD0A2ULL, 0xA906BBACE729A4D4ULL, 0xB4818057BD63D410ULL, 
            0x828E549925C96ADDULL, 0xD99AAB70C26383CFULL, 0x81A3459F55939D30ULL, 0x9CBDCF2A405FDB1AULL
        },
        {
            0xDA5FE474CEB3077AULL, 0x4E9057E0F000A6A8ULL, 0xF86E5F89E2FBD384ULL, 0xCDAD2C3CE52F87B4ULL, 
            0x6D9EDB36DBFA3B5AULL, 0x916678122646C369ULL, 0x20F9550E3B607E4DULL, 0x08C820329D6132E5ULL, 
            0xD7095221C99D2C0FULL, 0xD7B67DB4AFCF520BULL, 0x5D58641CF6316052ULL, 0x1600076FF65ECD21ULL, 
            0x6CF1523E5D528596ULL, 0x4C58A9587829992AULL, 0xF2C00E1238710A8DULL, 0xD674FC17A51FBE46ULL, 
            0x7290996006F3A395ULL, 0xCFAB671777D82E69ULL, 0xF90840325543B3E0ULL, 0xC9C35DFA0653BF5AULL, 
            0xC2CBBBCC430F1815ULL, 0x728E1C7742A1983FULL, 0xA3546CBF7CB30B65ULL, 0x7D418BE0C5B306F1ULL, 
            0x324840AAD07DCA0BULL, 0xB50B931B997D76D3ULL, 0x6DEF511C1BA75863ULL, 0xCE93DD8EE8BBFAB3ULL, 
            0x44A9ECA06432C722ULL, 0xDB20DA664F240692ULL, 0x90DA6C54D858268FULL, 0x3745174234A7AAE0ULL
        },
        {
            0x2CF0C440B5F6235BULL, 0x2629A289746472F3ULL, 0x5D6C374BB5B4EBDCULL, 0x586328684B92D2DAULL, 
            0x9DE889EE9E6A4D59ULL, 0x01A8402BBB49FAC4ULL, 0xE95F1CE3F5E6C1E4ULL, 0xB832A9AE584BC019ULL, 
            0xAB5EF39C93854891ULL, 0xF36DB1E998F5C847ULL, 0x513B626DF53C8F63ULL, 0x8EF15E7E6D6CE251ULL, 
            0x16FAA8AB993F761DULL, 0x875C391A94DD3F61ULL, 0x60C384FA0B19BEE0ULL, 0x6B4BEFF246CF8ED6ULL, 
            0x70F8C598E553B90CULL, 0x4A881BEF14A6D097ULL, 0x124102D17C97E256ULL, 0xACFF0808DA7BC158ULL, 
            0x72CAC66BD167C4D4ULL, 0x0D2B5935090166D2ULL, 0x0536F4D88C47B250ULL, 0x6DDF44C6380BB45AULL, 
            0x463A0CC47F325742ULL, 0xBFA4351272E7731DULL, 0xD685DB90CA80F575ULL, 0x89C4FEBFEEE8F96DULL, 
            0x4C8C56D7E42E4B38ULL, 0x60E8BD147657C6EEULL, 0xD9188A79136E26E8ULL, 0x93C52ED87610A621ULL
        },
        {
            0xA1C2C5D1A4A6F6E3ULL, 0xE586652476ACAF17ULL, 0x3A8520274F9099EBULL, 0x4369061EDFACC6BCULL, 
            0xE1A313125C9EE764ULL, 0x96B7038C32939C2EULL, 0x40E1C6B45F9EA4D4ULL, 0x042B211F4A3E0B9DULL, 
            0x2C09D208BC610754ULL, 0xE9268C7D7A303F2DULL, 0x171C7493B0375D07ULL, 0x6A2D075288AEF434ULL, 
            0x503E4E44CC4F0074ULL, 0x346E1F8DA92DAD72ULL, 0x961E56A48CEA48A7ULL, 0x2ADB2E666D9E0DA0ULL, 
            0xB12CD0CD41BBC3F0ULL, 0x952C6D580CA22335ULL, 0xAD42AA8196ABBC8AULL, 0x3052989CEDF57DB6ULL, 
            0x0AFCCF173F1AFA53ULL, 0xE845F2747A7A042BULL, 0x3E29CC65CABC4309ULL, 0x8D21DE30B3F100F3ULL, 
            0x998479EC97174822ULL, 0x6B2B5C63D4288704ULL, 0xCB3A3FCFB3757F10ULL, 0xD7B57D6C43DBAFEAULL, 
            0x31115A34D0F91673ULL, 0x45109F620A38E097ULL, 0x0C5379F796290465ULL, 0xE1FABC0BFA1B2A5FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseBConstants = {
    0xC4C028F32DBC4CDAULL,
    0xE07DD408A11CD5C1ULL,
    0x4434C041CD341FD5ULL,
    0xC4C028F32DBC4CDAULL,
    0xE07DD408A11CD5C1ULL,
    0x4434C041CD341FD5ULL,
    0x3AF303F339E9A6A2ULL,
    0xF75F27C7FFF4CE53ULL,
    0xB5,
    0x15,
    0x24,
    0x11,
    0x93,
    0xEB,
    0x51,
    0xB0
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseCSalts = {
    {
        {
            0x2645CD5F41430D99ULL, 0xB76B99B2D9E64214ULL, 0xF35AF1487BE7B6EFULL, 0xF04F1E20BF121052ULL, 
            0xFD01CEF4CC5CC7CDULL, 0x1C905AE1D0BD815EULL, 0xB4107B2287278F4CULL, 0x8D9FB69670F3894EULL, 
            0xD93DC0680112BC4DULL, 0x7A6A5CA8885CF69AULL, 0xF4ADAAF8833A2948ULL, 0x6AB48B8BEB9C136EULL, 
            0x7113A81F514D4787ULL, 0xF1F32D5D160A9295ULL, 0xE0051F06B352CF7FULL, 0xACB044370011DC92ULL, 
            0x1F14D49F7CE38264ULL, 0x98D9F9EA938F7D93ULL, 0x09EB1E86E31310F8ULL, 0xD4E6736DBD2D40B3ULL, 
            0x4B543BA9EC6E0D54ULL, 0x91CD8844C366A55BULL, 0xCF230130D162E1B8ULL, 0xA321556E857E55CCULL, 
            0x8E8D617920B2A8FDULL, 0x56F4B8F573A3C966ULL, 0x0C6004FC7906F117ULL, 0xEC2E41660F7C2817ULL, 
            0xC84FC0C065409445ULL, 0xC511FC0805A7D7D2ULL, 0xD3377062F0E444A6ULL, 0x36D891E7EC741A28ULL
        },
        {
            0x80E2743C9C72CC5CULL, 0x7BB8BB34FD3D07D6ULL, 0x077D64242DB85292ULL, 0x4FF1A3618AC8DFB5ULL, 
            0x95F3AA41CC0D4883ULL, 0x459A0089FE766885ULL, 0x40B6DAACB3269E23ULL, 0xC5960C001C0389B6ULL, 
            0xA720C60EFA2F4EFAULL, 0xB40456AEE91C312BULL, 0x97ED7678FCD373B1ULL, 0x06C0F269FC449772ULL, 
            0xEDDC008C05E0D600ULL, 0x69EDBE714F4D8148ULL, 0xBEB45E726B573384ULL, 0xDCBE27BC86623D81ULL, 
            0x497D7EF504A210ABULL, 0x05CDE923B94BC34BULL, 0x01E795B1B0DE012EULL, 0xAC2AF3D4B9B5F9FFULL, 
            0x28B65B1B3D4E3D6CULL, 0x88716E1081E94325ULL, 0x3652C75B84F07FA6ULL, 0x0C7FF69B87C7A0BCULL, 
            0xD29E12C1DE6FEC2FULL, 0x02093A6CBBEC8CB6ULL, 0x3F1C903CE69CDCFBULL, 0x148F5AD3667D476DULL, 
            0xE8E6C3507C94D408ULL, 0xBCCAC98961445262ULL, 0x62DF45C1AABAD881ULL, 0x2D06C0107B2D0A9DULL
        },
        {
            0x3683E2119B70ACD5ULL, 0x5DBFD61F0A9CC318ULL, 0x74225595315A4CD5ULL, 0xA2AD5CBDFF8A8E41ULL, 
            0x89A12705652BDDC4ULL, 0xFE97BC6F90F667DBULL, 0x90CEC69E3368A592ULL, 0x53C7090C61FEDD9BULL, 
            0x4DC5D2702C0256B1ULL, 0xF5C3DA4FBCFB3FC2ULL, 0x029D67DC8211D79DULL, 0x447DA89727C69D32ULL, 
            0x9EB617E59FB47E6BULL, 0x90B37D362C626C16ULL, 0x3A5D6B28BB459C27ULL, 0xF2046E6EE27D3F21ULL, 
            0x2A235B8E59DAB44EULL, 0x8839C09AE5CEF389ULL, 0x4F18F5FB824E77B4ULL, 0x50CCE97DB510615AULL, 
            0xB57FB83A272CC263ULL, 0x0EB25167192AF191ULL, 0x2AD7FAD2A7E9E19BULL, 0xB0BB02E3769066C4ULL, 
            0x8F982B711A1186A8ULL, 0x543753EA41CD243FULL, 0xE9A4A9EE66D3033EULL, 0x80AFAE02BF5BC07FULL, 
            0x4617E437842AF6CFULL, 0x481943C47362B7A0ULL, 0x45458699A8E35F64ULL, 0x0621AF80AE8943C4ULL
        },
        {
            0x149057C0504661B5ULL, 0x01DAF6AFB80309D1ULL, 0x3D809CBF830819F9ULL, 0xFEAA16981BAA62F2ULL, 
            0x734B7C4AE0AEDC07ULL, 0x030E14CE7ABC48B7ULL, 0xD1EB59DD21ADCECFULL, 0x81962CE7C5813AF7ULL, 
            0x701D2EB5C8C5CCBEULL, 0xAD929277F95AB237ULL, 0xFFD85F82984A4202ULL, 0x23F122353C2C2BB1ULL, 
            0x6F1D9026DBDD70D9ULL, 0x6DC584AF1282F17BULL, 0xDBE1287B14003926ULL, 0x82A904DDF9B4818DULL, 
            0xF2D6E2E0CEFA3F4AULL, 0x6B6F81E53B8D2A67ULL, 0x760667CD5BF35D7CULL, 0x8FDAEC21C26F83C5ULL, 
            0xDA7BADF2A54994F7ULL, 0x41B1307AA00F3BD0ULL, 0x9ECEDC54AB82AA20ULL, 0x207007591747307CULL, 
            0xE52826253C077546ULL, 0x677AD85AA17CB5FCULL, 0xA40F765220B4B455ULL, 0x7E0331337A037B38ULL, 
            0xB0D01F84FAE22E28ULL, 0x707AFDA75D2415CDULL, 0x822A163F091E481DULL, 0x30182F8B521B405EULL
        },
        {
            0xE809D614B9F1BEEFULL, 0xCDB79C3D47AFED99ULL, 0x221F9636EF92C2E3ULL, 0x3410F1B0C8DEEED6ULL, 
            0xF8DAEEED6B731351ULL, 0xD144349E5344782CULL, 0x9586CCF0A47FE642ULL, 0x8C4EE2FE30F660F0ULL, 
            0x1B65569289F7A49CULL, 0xD1D0B812727D1D46ULL, 0x67BD3DA970709E05ULL, 0x94B1EC568F79B79CULL, 
            0xDAF626D59AF57483ULL, 0x41577ECF807AFCB4ULL, 0x2A3640DC77A1E737ULL, 0xDF0F50603A3F341CULL, 
            0x28DF97E1C680D3D7ULL, 0xD6AD61EB6EBE84B7ULL, 0xE6CC5775D5FBA2D0ULL, 0x9CDF1E08F641FD29ULL, 
            0x8F189E7BD7B0B66FULL, 0x63942F4A7195F67AULL, 0x7785E1A7EF386DB3ULL, 0x3F231924A862FD91ULL, 
            0x0037D7289A5EB613ULL, 0x06764E5F5873AE3BULL, 0x81730B74537770CBULL, 0xCEB4B4F9647D5616ULL, 
            0x2514506F06F05567ULL, 0x3C4DF8F6685DC5E2ULL, 0x8B1E76D69FC8B3E6ULL, 0x514F44E6D113008BULL
        },
        {
            0x610108FBEE76C2CAULL, 0xC1D393576845B77FULL, 0xE40299B7763D0283ULL, 0x41F0E5A13715C918ULL, 
            0xC3785C6C021E0361ULL, 0x6BF828EFF721A9C1ULL, 0x276DE03759677019ULL, 0xF0304EF6A4639D9EULL, 
            0xD60B0AE0C4215F13ULL, 0x245BB7886858F2E1ULL, 0x5AAB7356F20A5102ULL, 0x5FDDA432E6A8D84AULL, 
            0xF4AC7E723D68ED54ULL, 0x2441CE99B81C3E6EULL, 0xE2C8B802D3D2D121ULL, 0xF299D3B22598B4BDULL, 
            0xA0E38A9CADE0EE6CULL, 0xD788B320E0A78AFFULL, 0xBEF9D3D5961A668AULL, 0x38256A8AEA00CBB0ULL, 
            0x343BC8BCA118B890ULL, 0x6316316C77DC5D78ULL, 0x310F84C91DAF2355ULL, 0x2235497337E4898DULL, 
            0x410078232076E151ULL, 0x10FFA0F73516EC10ULL, 0x42E51A221D91440CULL, 0x6EEAB2BA464D3530ULL, 
            0x45244DD0E77B718EULL, 0x1FB90E2DA795101FULL, 0x3B3BE81E3D85ED16ULL, 0x6BEFC81A0E005F78ULL
        }
    },
    {
        {
            0x885101164BA900CCULL, 0x9C62407E9E343662ULL, 0x54E22F9BECA15B1EULL, 0xB9961A5A077CB1D2ULL, 
            0x0FF0929ABDEBDF74ULL, 0x52A7B2EEBCD16D12ULL, 0x751409D1EF3A63A6ULL, 0x3766832079A4DB59ULL, 
            0xB100DEFDABAF4686ULL, 0xDC1D3FD0A1E19E64ULL, 0x67E3340B119399ABULL, 0x2DB321AB22402DCFULL, 
            0x4DC21D7235271381ULL, 0x0C6CBEEBA4F1B796ULL, 0xF9A56B4A5B91BB4EULL, 0x17A0F540504FBA12ULL, 
            0xC4CE2D6C6CD0364FULL, 0x53FC8BFA3D356932ULL, 0x838975075F17D95EULL, 0xAA5354CFDC2CDD4EULL, 
            0x54580CB1C6BBD168ULL, 0x7479F61A31359C6FULL, 0x3DDD19C55779EFE1ULL, 0xE773104F34A576F6ULL, 
            0x65AE463F4C53389CULL, 0x5CD3CE2396B65C63ULL, 0x42FE858DDA5F4094ULL, 0x029B4C4EBA713C92ULL, 
            0x24BECEDECE11A064ULL, 0xE0ED07B0AD06AD95ULL, 0x6D3CF310E957EFAEULL, 0xC645D09DB43C8364ULL
        },
        {
            0xDFAC69CA696904F1ULL, 0x4E7F7C313B450C6FULL, 0x2CF3133B67A515A4ULL, 0xE6E993763E7B527AULL, 
            0xCFCDCFD01D180693ULL, 0xD5557BC3B664155FULL, 0x39E1B8836A0F9B11ULL, 0x553F93A940791173ULL, 
            0x2A3F3C614E82A364ULL, 0x97924BCBC5850478ULL, 0xF4AF1DA817854674ULL, 0xCE2AF175C40F290AULL, 
            0x7E0EDA933049E36CULL, 0x164350F17159E37CULL, 0x345AA74C3B9DC80BULL, 0x7A30495E5B1BFDC9ULL, 
            0x71DFF50ED07CB4C5ULL, 0xCF2FC2FD67376C32ULL, 0x93CF3F3B6D4662C5ULL, 0x9EC2168E39BFC593ULL, 
            0x9AF563AE8E96336BULL, 0x481E790CCFE48355ULL, 0xAA2A889D2ED9757CULL, 0xD3CC9CDF728F2605ULL, 
            0xDAEBDC3E3FB2E2C8ULL, 0xEAA47C3723C480DBULL, 0x9CEB7C76E936C16AULL, 0xE33077C39C10983DULL, 
            0xEBDEC608AEC73B22ULL, 0xD2833774A3D44660ULL, 0x13B8CFB1575B2C5DULL, 0xE6771769EB23685CULL
        },
        {
            0x95B40EF4DA89ED35ULL, 0xF0F59866A4A22DC7ULL, 0xCAC5D5915A5AC065ULL, 0x5E1999817F3981EDULL, 
            0xF552C0B1418FB991ULL, 0x28FDB6150C8BF351ULL, 0x0260ED02286E47CFULL, 0xB4ABE4A26BDC54BBULL, 
            0xCED673C1C598C317ULL, 0x47462756157565F3ULL, 0x6CCC0B3E581DA130ULL, 0x8D6296163024D91BULL, 
            0xA963B99FF4460CADULL, 0xC53C0BC196EDF995ULL, 0x812116261D188D88ULL, 0x805FAB3FCC0732E8ULL, 
            0xC14F2330ABFA69BEULL, 0x01D9F231202FF8F3ULL, 0xF38B2082DC969AEAULL, 0xABF91BC72CC84B38ULL, 
            0x7147C327E29921D5ULL, 0x13098DB572CBAC37ULL, 0xEFD14165F535898BULL, 0x286832B3B4E4D4F8ULL, 
            0xB961AD14BD5EBCCBULL, 0x744E8BE103747612ULL, 0x5DC5BD89DE65540EULL, 0xEA0FEDC2F80815C6ULL, 
            0xB73291EC249119BCULL, 0xE2C20584390DC152ULL, 0x5FC00A3EE3CA477AULL, 0x72ED12D657EBC81CULL
        },
        {
            0xD02EA289D026D425ULL, 0xE696DF9F328627BBULL, 0xAD09C1D9BD15D8C6ULL, 0x644B6471B89C4E07ULL, 
            0x503C531971C5D435ULL, 0x5BA8524AA8E9F4A0ULL, 0x3F9E109876463B87ULL, 0xD223C46D655941D6ULL, 
            0x4E1791C9D82DBC6BULL, 0x8AC3880701D72D11ULL, 0x6ED018FC6D20C795ULL, 0xB2FCFF457F059013ULL, 
            0xE7647A42F474EF4AULL, 0xF73E2C6A072C7134ULL, 0xBDA075DA31CD13C3ULL, 0xCF0C9285F1A96E70ULL, 
            0x35277CA687B5C3ACULL, 0x4A2883951BD35040ULL, 0xF341F522EBC44713ULL, 0xB9F815A0C9F32D7BULL, 
            0x66DDF4926F680974ULL, 0x3F67D2F648CF7C7EULL, 0x2EC12B16BE8091F8ULL, 0x75E9B83DF227753CULL, 
            0xD78D725EE72383CBULL, 0x69CCB93E4AD59355ULL, 0xEB763B4A0C053350ULL, 0x93E070AD0FF3B00EULL, 
            0x93A44B7572BEE4D9ULL, 0x7642E2F8457F3228ULL, 0xA0BA6C4A1E67AFC2ULL, 0xA46F0A2ACB2682BEULL
        },
        {
            0x199489FF15337BA0ULL, 0xE1903A75D4B56236ULL, 0xC040DCAEF07601FAULL, 0xA85BDD8A3EDBEF6CULL, 
            0xE7607A6EEE29E4A0ULL, 0x975C1925B6C31714ULL, 0x5D5DEDB8D8E81B86ULL, 0x329E146FD5D695A9ULL, 
            0x42763CC322DD7CCCULL, 0x04AD9D8598262264ULL, 0xC6335051DAC085D0ULL, 0xF9904B8EDAFF6264ULL, 
            0xBC2D3E6B684B099BULL, 0x9CC3262A32D751A2ULL, 0x339AEE5F321A4CEEULL, 0x749F13DAA38AA47EULL, 
            0x0A9D334CC40383F3ULL, 0x9D362857E73CFC81ULL, 0x915E8AAF9D6B840DULL, 0xC75EF350883FCF38ULL, 
            0xCB5235285F3B351EULL, 0x6A0DCA5EC2B97E82ULL, 0xCB6FDA7B367C42BCULL, 0x6F3D58D18B756560ULL, 
            0x87DD3CEBCC170FB7ULL, 0xD45FC07D6C2DB959ULL, 0x93D5210BAD9641C9ULL, 0xD2B4CD7AEADB07FBULL, 
            0x9ED452FC6FA0A60CULL, 0x7921BA3062854684ULL, 0x25F4F40A4B628E6AULL, 0xFB43DE8EB52A5B2AULL
        },
        {
            0x7E0EA2B7F7E05E7AULL, 0xB539E17327499DDDULL, 0x1D277D45452850A7ULL, 0x11946B816F23D13AULL, 
            0x922C3247AACEAEEBULL, 0xB5CA0DCDEEB582D6ULL, 0x9EAE928BE2D48F53ULL, 0xF3022833C4A445D5ULL, 
            0xC7881990461EA7D1ULL, 0x09EB4BCDCCA0A70BULL, 0xC1C5E943050CF7CEULL, 0x9E6E86D47A2A871BULL, 
            0xE636325A5A1C152DULL, 0x3F1859EAA1680ECAULL, 0x5E1D2CA689E68B7DULL, 0x3F0E6D7B1CAB71B5ULL, 
            0xBF82E183C8889009ULL, 0x5FE6A85C1C85F33CULL, 0xC462901E898F5DD2ULL, 0x23A1CD84792A882FULL, 
            0x887129992F63FAE8ULL, 0xDC409D0E8F4A38CDULL, 0xB9031E3C9F4D51BFULL, 0xBD5CC198E88057F5ULL, 
            0x0D4FD3E29354641DULL, 0xAB3412A7E8FDC084ULL, 0x5EE1080ED2620B88ULL, 0x2E7561E3373D8C48ULL, 
            0xEEC8FC1C3A16B069ULL, 0x84463A466FD84A0EULL, 0x7FBFCFC8E4F5B446ULL, 0x8B0A7F99DFC634F5ULL
        }
    },
    {
        {
            0x1810D01083E22E45ULL, 0x9571CF340E821B06ULL, 0xE52AC4B9117CCA44ULL, 0xA96566E8AB351547ULL, 
            0xE243A92E3B802514ULL, 0x7A205A4DB5A91343ULL, 0x79900270F0349C04ULL, 0xE1DCF6F745BECCC0ULL, 
            0x2FAD4BEC678A2FF2ULL, 0x25BC7A2C3864B442ULL, 0xE077C89BE3308780ULL, 0xA002BD4A37BE3CE4ULL, 
            0x48EF5D47FC4C6D1BULL, 0x9AB0CB407ED33B32ULL, 0x40B588F0409D340EULL, 0x9754D8616347F262ULL, 
            0x60DE0B139CF074CDULL, 0xF722B52C7F926407ULL, 0x50C538B83ABA5D32ULL, 0x8992C5FF64A42913ULL, 
            0xA2738A5A2FB165BAULL, 0x66A64A4093A78F5DULL, 0x8449A371849159FAULL, 0xFF5B56E0E47900FBULL, 
            0xD9E4C847E021C6C2ULL, 0x0CF1D38AABD308AFULL, 0xDD596AA9102A42E8ULL, 0x5AFB665FFD05B0CCULL, 
            0x8A044A920BB228FBULL, 0xDDC0BEDA6DF5F376ULL, 0x21F3DBDC6A277610ULL, 0x56A29B3DD6E00DC8ULL
        },
        {
            0x8B724F80273270ACULL, 0x28B1E97D748E9E48ULL, 0xD36E5A45315FD064ULL, 0x2C6049BCBEBFB99BULL, 
            0xC71D5D2069A4AB44ULL, 0x26312832F49AA852ULL, 0xD13B96D03671E401ULL, 0xC9C70555EC2C6698ULL, 
            0x56A15A15A91626AAULL, 0x507EC2A4F8F84BC5ULL, 0x9AA50C5160DA5D73ULL, 0xDF567AE0500B13A2ULL, 
            0x2F3CD2AF146C4CE2ULL, 0x9EB1956CE34618E2ULL, 0x10D7CE42BFD0BE05ULL, 0x1DEDF250E5F50B69ULL, 
            0x1289059DBDDC6920ULL, 0x2F9D92E931CDC979ULL, 0xE909127412F30DE7ULL, 0x0F0512FA16AD5B9AULL, 
            0xB00F4A771AB51162ULL, 0x08C5692171770351ULL, 0x623D6EE56D1E78A0ULL, 0x10043D62DD7FF11BULL, 
            0x06D524A25B8C62F5ULL, 0x3FB947722754CC37ULL, 0x2EE8CC3A57E8BC20ULL, 0xC22CC66D529E4D07ULL, 
            0xAAF3922A4E03E1FCULL, 0x3BB8CE643414DFD6ULL, 0x383BDC3DC8688A14ULL, 0x656FE4D5E1114799ULL
        },
        {
            0x29197175869CFFB2ULL, 0xD33A412EC98E853DULL, 0xD2C464A286C2C171ULL, 0xC91FBE9DCAE81969ULL, 
            0xD8258333DA1B437DULL, 0xAEDE635590711EEFULL, 0xAF1D813076BC6CD5ULL, 0x08B42AB089EF41CAULL, 
            0xC5BC033F4FAC5E5FULL, 0xE6EC58D3744F4291ULL, 0x489B25E9D1F261CEULL, 0xF68711D57DD0F021ULL, 
            0x5E79941B2932E1FAULL, 0x145E0248732F62CDULL, 0x1EC83729E0DF3AF8ULL, 0x324B747A8197FC16ULL, 
            0xC2E0A2F409498321ULL, 0x5FD218BEB32DB85DULL, 0x1C8FC79234FE3967ULL, 0x342E593B04EE9FF1ULL, 
            0x91AA22FE4C807015ULL, 0xB47E3545374FE216ULL, 0x49CBD4E126077F7BULL, 0xD7835655DCD22912ULL, 
            0x2A6C8FF570CE302AULL, 0xD15BA6E4DC911536ULL, 0x497BE971582D31E3ULL, 0x4463D9538F654220ULL, 
            0x77689782F4865379ULL, 0xA8212D7DAD542517ULL, 0x98C8CF0C87D2EAAAULL, 0x38AEAA27D0249EF2ULL
        },
        {
            0x6BB2AAF552795005ULL, 0x32AC51A5F98C34F0ULL, 0x6624F1A9B56170E9ULL, 0xAD0A84779DFA41DDULL, 
            0x82441991085ECB66ULL, 0x0C3DAEDE3BB385DDULL, 0xE2B64866ED8AA9FFULL, 0x9E92139F8ED08271ULL, 
            0xE2FD2EE0CF22F7B0ULL, 0xFDC89FF814F33CE4ULL, 0x0D7F892E7E16BBACULL, 0x809B6E641D51C62FULL, 
            0x0599F5596E39CEC6ULL, 0x2278267F26696EB7ULL, 0x15F8AD767FD60BD2ULL, 0xB7D250595D86FD3DULL, 
            0xE89DBF7C952A8144ULL, 0x7ACC143D96E3A5D4ULL, 0xFED9AF536577A0EBULL, 0x9BE92D75A4483A7DULL, 
            0x07182E03FC0FA8EEULL, 0x7B5CE88321B22773ULL, 0xEF79E8E6C7FE5A82ULL, 0xE53EA0E9B8144970ULL, 
            0x55A03EA0C8B3BEDEULL, 0x869B7CCD416E8F61ULL, 0x215A5F96420AC2B7ULL, 0xF1E10B310411A1ABULL, 
            0xBF053414D27924D3ULL, 0x3D559E31C1598E8DULL, 0x6BA9715FF6D2B387ULL, 0x06F9BD8E8BD97062ULL
        },
        {
            0xB05592E01DD45386ULL, 0x4F57306701EA3763ULL, 0xD3C95603DFB7464CULL, 0xA3E7D6DB26AEF5CAULL, 
            0x3B629A43FC4D26DFULL, 0x07E8267ABBBE3C87ULL, 0x2F28D24D1034F4D5ULL, 0x4489340E91E893F8ULL, 
            0xDA4AB7232832D7ADULL, 0xFABFB1B00A88B258ULL, 0x35085DE926EA4257ULL, 0xD3FA2B33C5CB9BF4ULL, 
            0xCB4BD438F445FE24ULL, 0xE12634B23889DD34ULL, 0x5B44D00A03F8CF89ULL, 0xF68AD2432017D772ULL, 
            0x94329A657276D6E6ULL, 0xF11FE301C25C0C5EULL, 0x5DC5CAEC562B57E5ULL, 0x10A34B08443F0648ULL, 
            0x40CD638A19007411ULL, 0xEB6FBEC8C2AFBBDEULL, 0xA29120C7447970B8ULL, 0x279436B86C31B26DULL, 
            0xAF2BE92708F55EAFULL, 0xBCC5434CD5BD3F67ULL, 0x4475D46B46AAEF00ULL, 0xB70D5CD3FA120599ULL, 
            0x1163284A3DCA4FFDULL, 0x64A930C871CAAD29ULL, 0x00B8024D26E6E4D6ULL, 0xA292CB54FB74C62EULL
        },
        {
            0x8197243AFBE4EC43ULL, 0xF96D6836E8931914ULL, 0x7348524D15673D04ULL, 0x14AE64D50F2B8122ULL, 
            0xF8EFB855C4409F41ULL, 0x6FE97C3816071F87ULL, 0xE8EC5FDE14DD775BULL, 0x033A817F8CC58188ULL, 
            0xA62B45B6DE3B19B9ULL, 0xEB9D3C6123260BE4ULL, 0x984D1233DE642E48ULL, 0x46362690C081CB80ULL, 
            0x0C5632E9E685F706ULL, 0xB7E7024C8935448AULL, 0x7F079F80A2F088B3ULL, 0xCC49B51D95C31CE5ULL, 
            0xC2C4B0A662BB693FULL, 0x7D04E8DA9E963638ULL, 0xBD1DDEF995619CDDULL, 0x9555E4336C037750ULL, 
            0x3C706F34FF1A91F1ULL, 0xDB1AC0A98189A84AULL, 0xB6AD33F24F170DE0ULL, 0x767CD9CF785CCF43ULL, 
            0xAAC59A96E2D57EC3ULL, 0x6FDE56D0E4473943ULL, 0x795B8453ED3659FDULL, 0x299310C2BD3BB0F8ULL, 
            0xA7297ADA67AF6B2CULL, 0x3AAE30135DC9256AULL, 0xDBA6C086D3F8C2B2ULL, 0x35164EA34C346ABCULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseCConstants = {
    0x26E21D75286D3C15ULL,
    0xBAB5374ED86BDCE0ULL,
    0x6606FAAE8630E7ECULL,
    0x26E21D75286D3C15ULL,
    0xBAB5374ED86BDCE0ULL,
    0x6606FAAE8630E7ECULL,
    0x0551F76BCA338389ULL,
    0x21235A6A8169F70BULL,
    0x28,
    0x53,
    0x21,
    0xD9,
    0x1E,
    0x84,
    0xB8,
    0x1D
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseDSalts = {
    {
        {
            0x350952E7A13A7881ULL, 0x380D4B162A072D50ULL, 0xF5245C39A6BF63ACULL, 0x706A00CD5D601775ULL, 
            0xCF28362C40594265ULL, 0x0AF93E9E9937C1F6ULL, 0x53985E4B556AF1BEULL, 0x0732DE63958C0CB1ULL, 
            0x061EDC7957A593D7ULL, 0xEFAC68CD2C3C88B4ULL, 0x5677F4878CC5AF1EULL, 0x6AF5BBD5990A5D67ULL, 
            0x96C28CF4611FECEBULL, 0x4A311EF2EE56B805ULL, 0xCF3D77E5DDB52E36ULL, 0x79B6D111FC3906B0ULL, 
            0xEE5427F81C337429ULL, 0xDCE4A6FC16E5D2BAULL, 0xF3FCCAD06ECD1E95ULL, 0x193DC04BCFED4EE7ULL, 
            0x4DF171E8F4443D10ULL, 0x6AA72251716E2103ULL, 0x49375FD234DC36B2ULL, 0xDEFB76404D3D8D55ULL, 
            0x0D57E37E1DD6A9CDULL, 0x1EE504EF35EE5EDDULL, 0x04561BE1A3A16A25ULL, 0x9A660C0BB7C8DFB9ULL, 
            0x93CE03DE013E67C3ULL, 0xB8D881A65DE8A35EULL, 0x7DBF4F8F2C278E2AULL, 0xF8442BAFE5ED7CABULL
        },
        {
            0xCA122D548A087289ULL, 0x5F972735AEC83825ULL, 0x7099310C0947BC24ULL, 0xDB49008257383A69ULL, 
            0xD7120DCF174E59BAULL, 0x6573EED5E9CE379FULL, 0xA6884C851E4F9191ULL, 0xB2508BDB7D07AFA5ULL, 
            0x4000F7DFD492C273ULL, 0x114C9BF89E7690BFULL, 0xD2EEA091BD2283C2ULL, 0x14BE973FBA186BAFULL, 
            0xF13DFE1D9938296AULL, 0x883707B3D79C757AULL, 0x8AA3D8BE866FFF0EULL, 0x1A0DB081D9C331DDULL, 
            0xD7F0224913FCC289ULL, 0x4AEBFACB3594476CULL, 0x38A9F3245260E3D4ULL, 0x8B6C0AC74584499EULL, 
            0x71CBD8940AF2D22BULL, 0x96912B7D05B6395DULL, 0x9A815B64E2814F54ULL, 0xAA75412164BA3A0FULL, 
            0x956D0BFCD3538242ULL, 0xEBC29641C07D1317ULL, 0xB07E8FE4FE6EFE1AULL, 0xED7F9420D762F849ULL, 
            0xB25CA2D95358290FULL, 0x56E11E5A9FEDB370ULL, 0x39A92B521A2CAD9AULL, 0xCEBD0F44F3A5230FULL
        },
        {
            0x14CF9ACA6458F29DULL, 0x121F96FB606BA404ULL, 0xF6E008ABC14CE5EFULL, 0xE4B6AB6BBD3F064AULL, 
            0xE97A9C72FF8A21B5ULL, 0x72761508CBFCD388ULL, 0xAB38D3B22CF5A708ULL, 0x582E48B8E7D95215ULL, 
            0xB4C8E8C930FCA9C8ULL, 0xD69DF135EB75B391ULL, 0x010C430CD193665EULL, 0x39A25581CA63EC90ULL, 
            0x6A3C59E81D51EB8AULL, 0xA688008AB814088FULL, 0x6FF8B7B10952FA7EULL, 0x5D6550949BEA293DULL, 
            0x8D06ABCAE83CDC37ULL, 0x8A234524DC3E6F1DULL, 0x6F375F30393C1DD2ULL, 0x582A849A6C867CB7ULL, 
            0xA9D8C5929A8BC0ECULL, 0x6B0F4AC711C6497AULL, 0x8AC52BFA17BEB03CULL, 0x3F7BFD45FD353A0CULL, 
            0x16910704EC7C1FD1ULL, 0xC905A017E4A7BC3FULL, 0x7CD72369F80CF77EULL, 0x3B31BC4F11FE8684ULL, 
            0x2844DC5AE67AF5CCULL, 0x9D2E496A1717DD52ULL, 0x510D52033553ECA0ULL, 0x6FF1E6AFF287D68CULL
        },
        {
            0x590C494A231B7AEAULL, 0x1CFB2B95CA00166EULL, 0xA8BB699887D97250ULL, 0x935F2450B7305201ULL, 
            0xCF048847923FB8E9ULL, 0xB602C2CADCBF7377ULL, 0x1158B69F450B6E3AULL, 0x2DA9A9A6712729B3ULL, 
            0x2CC59FCD0FAD8642ULL, 0x5A33AD8E0BBD0167ULL, 0x67351F19003C1D7FULL, 0xFB4815B3444699C3ULL, 
            0x93855ED0894E8F35ULL, 0x325B8A15280DE007ULL, 0x53F6ED0A5C074DA4ULL, 0x740E81DA3DB483FCULL, 
            0x1DE2040DD90C1F09ULL, 0x6897D2C506DCAD36ULL, 0x3ABE221E765CC1F2ULL, 0x5916B44F8BF62F69ULL, 
            0xB836C1EA3C7B3A40ULL, 0xFFA54B2B3B72E8EBULL, 0xE8D5AEEB48D3EF32ULL, 0x6477C0ABDA5D446BULL, 
            0x68BFED321A4B1655ULL, 0xC046A44735F7D128ULL, 0x40EFD69EEE9DA00DULL, 0xFDE4CF0E7E842ABFULL, 
            0x2ACDEE9AB06505ADULL, 0x6FB503EB761E0857ULL, 0x1256B6DC2D2EF718ULL, 0xFCEB881307446084ULL
        },
        {
            0xF62AEEF546E2ADE0ULL, 0xC07705853412E4A0ULL, 0xC7C2C1FD90BD5979ULL, 0x4E12EFBA06139248ULL, 
            0xDD38918D597DEB52ULL, 0xC2D28B0D2C5A777CULL, 0x7C3CA1F18AEE20E9ULL, 0x089B1CBCD3B186C9ULL, 
            0x13885D9AEC7257A5ULL, 0xE74DE3452470CC39ULL, 0xF43A58776317AE9BULL, 0x86B56EB352DB9958ULL, 
            0x8D26BF136E7C438AULL, 0x601ECCB66811AB87ULL, 0x553AAC5206F26769ULL, 0x1E4BD94209D646A7ULL, 
            0xC0DF16E633780A1EULL, 0x45163B9E503E42FFULL, 0xDE2B89D7D1890576ULL, 0xD65FCB5884CFB131ULL, 
            0x58C22629ECC2ED07ULL, 0x17C3D90814F81F43ULL, 0xD70F38939695A6F5ULL, 0xF03128345FD905FEULL, 
            0x7E683382DF59704FULL, 0x9F3AF27FCF5E20EFULL, 0xB076FB349CA0C2E5ULL, 0xAA632DF66DB36347ULL, 
            0x23CFB7BA3E16FA79ULL, 0xE2EAB15D3B01D606ULL, 0x49D03B26530E6489ULL, 0x90835250FF2FF511ULL
        },
        {
            0x5C74BF6731FEDD31ULL, 0x4668BAB69E52FC94ULL, 0x39B0F0C52B756A21ULL, 0x9C517F62FF45F35BULL, 
            0x1B14D9A2621D3F6CULL, 0xED673A30F7B305D6ULL, 0x2000F02DB7C18A4FULL, 0x7652204391D4E854ULL, 
            0x88825426B1C5D950ULL, 0x84569C975F5E00D7ULL, 0x617D3844810CEAFFULL, 0xB4527E9C9AB3694FULL, 
            0x31A451616FDB78AFULL, 0x3730AD4B3EA353B8ULL, 0xF9CE8EC9619E9C02ULL, 0x803BB03A29B7E77AULL, 
            0x4C759C61AC54BA6DULL, 0xEB3F893E282EB440ULL, 0xCE40637CF0E90035ULL, 0xFE7FAAEEE511F288ULL, 
            0x805C881A3AF2054EULL, 0x3C1A7AA4EE438D40ULL, 0xB34558B578FC17DDULL, 0x5FCAB06064550B7BULL, 
            0xB5987DD0B5F8F4BBULL, 0xAA03ED7CD5F5EF7AULL, 0x3EA3FC05CEDCBC0EULL, 0xE941F570BF7898BDULL, 
            0x84593B57059CF55AULL, 0xE2A05DC3D5E2018EULL, 0x9F6B0B377F25194CULL, 0x641A0DF0EB4A9A21ULL
        }
    },
    {
        {
            0x098303FA6C03B220ULL, 0x0783CABC28590446ULL, 0x93CE622A8F545DF6ULL, 0x08C451775A3C797BULL, 
            0x9310227F6E50D565ULL, 0xCCB97D7DDEFDDE98ULL, 0x7BE34349E4AA535DULL, 0x1E4492DA126E3E88ULL, 
            0xA2474230A059AA74ULL, 0x6FA64984E5D2309CULL, 0x72F511C2855971DDULL, 0x7F2EF727D8A1F427ULL, 
            0xC70F0226D716D8DBULL, 0x22C32FA36961D875ULL, 0xB9A89ACC775A2B43ULL, 0xD2669EBBF4C3CA09ULL, 
            0x147FE27614E2B03CULL, 0x0E1EF1B4AD1EBA22ULL, 0x4CF241C4EEE4007FULL, 0x5F35DEF3CC4B6035ULL, 
            0x30E03A079B0942AAULL, 0xC09AD0852754A097ULL, 0xB434C1AAE46EFDDFULL, 0x601F97E99A22EA4DULL, 
            0x3B578D69466EAF78ULL, 0x7559EFCFD02ED465ULL, 0x2EBABA6711F6DCEDULL, 0xF9A18605EF608D78ULL, 
            0x78981214A36E32D7ULL, 0x9DFA3F60D83BBCADULL, 0xB483B6C3C4718FC7ULL, 0x905BFCFCE54C996CULL
        },
        {
            0x1755846F40B8373AULL, 0x0BF5EB0EE8BB6554ULL, 0xB26B33DB8DB7DBC3ULL, 0x9E7B098094CAAFA8ULL, 
            0x4038059EB638B7BBULL, 0xE6480F9F04D3DC4FULL, 0xE2887E88B617C900ULL, 0x5B09C792AA4EFC7DULL, 
            0xBD0B1F25B654F864ULL, 0x559539F51151CB17ULL, 0x203A8B0A9FAF68FCULL, 0x5430973A6C3EC836ULL, 
            0xE9E0C09B9FF7512BULL, 0xAABD474C2385EA7AULL, 0xB488988CFA3E4625ULL, 0x2A125B2E07F686E9ULL, 
            0xE1E252E2D22B1443ULL, 0x975C032EE3AA1B77ULL, 0xC83D055D265B445AULL, 0xF9C8E91E8E7D3323ULL, 
            0x1EE106EDA27EE141ULL, 0xB3BEA4EE88B9A0D8ULL, 0x2F40EA22880A57B5ULL, 0xE9D2F787E78ED67FULL, 
            0x25128F3CCE5548D1ULL, 0x958C52AEFCF40668ULL, 0x901C5D978F2CC5B9ULL, 0xCEAAE6DC06A363F1ULL, 
            0x93A32F35CAF73E4FULL, 0x92791D70BC371F85ULL, 0x0BDFCB4BAE35A209ULL, 0x139DD32FF3C0147CULL
        },
        {
            0x40B3440C799A9C36ULL, 0x198959FBF8BB39DCULL, 0x36915C3E5DF3B659ULL, 0x0716C13AD34978BEULL, 
            0xC3CAF5CE86A43FB6ULL, 0x495FC6BF1BCC2431ULL, 0x6D2BF735BA5C2356ULL, 0x170A870F0470FAB5ULL, 
            0x5E3727B4CD0C861EULL, 0x486568FA40EB306BULL, 0x5EA028852A71A721ULL, 0x9A3CD987C2414DE3ULL, 
            0xAA1B88BFC9226A34ULL, 0x41D5B41639326CD2ULL, 0x5F79DC11488CF311ULL, 0x1D2088C1C29E5601ULL, 
            0x6F031D14CF274DD8ULL, 0xB204B75256C53B29ULL, 0xB98EFF4232DC2A8FULL, 0x68BD8891799E7523ULL, 
            0xC54A85CE43A6725BULL, 0x199A401E0F2CEFE3ULL, 0xC6B2D5344194BC26ULL, 0xF6EC67E7C2903CA9ULL, 
            0x570BAC0991CEE1D0ULL, 0x780EAD20A7340BADULL, 0x7A2D7DAB69E8D41FULL, 0xB032F7DE01590B3EULL, 
            0x203749389807B5D1ULL, 0x242A79218FF0D34EULL, 0xF1BF832F7E384D3DULL, 0x9DBFBA3FEF09FD9CULL
        },
        {
            0xC50AAABF938350FAULL, 0xD9F1AE1DCD9D4A9AULL, 0x0C1E1B205F5B6DF6ULL, 0x54039F5D718BDFC7ULL, 
            0xD3DD6D40F9D10F00ULL, 0x060761A8D0D27B99ULL, 0x8B92270041CA1158ULL, 0x170C294B4335C18FULL, 
            0xF2C003481E69C29FULL, 0xB7DB20EBD8F612D6ULL, 0xAFC22D0DF73F10F7ULL, 0x7AC90EB2955A2261ULL, 
            0xFC5D7A363EC29651ULL, 0x32CA4813AB619DEBULL, 0x2C74328F359B3DABULL, 0xE642655BDBDEDFFEULL, 
            0x1F36528DD551A263ULL, 0x1AA12560C7612EC4ULL, 0xBD1C4B2A08A169F4ULL, 0x622864D4F926F209ULL, 
            0x45D6D8AAB578A329ULL, 0x5844006200ABC0A0ULL, 0x3A50053F5B827DB9ULL, 0xEB356DB49C68EEFEULL, 
            0x2A052F9A0F0A8C51ULL, 0xB1AC163ADB2538DFULL, 0x78CC5BEFE8CB6120ULL, 0x2978DF8DD2099400ULL, 
            0x7FD831AA67DF2E22ULL, 0x95975739B140539FULL, 0x811D196256BB5FB8ULL, 0x226DFD6784D02F52ULL
        },
        {
            0x1492BE8EC663B455ULL, 0xA078CFD229AC3C8FULL, 0x67F5D698AA2E3C50ULL, 0x0C14B25287E2EA2BULL, 
            0x198596963EC19A9DULL, 0x0B195A3211CACD0CULL, 0x85E7C0ABAA60DF06ULL, 0xAD88A7E04F3064E8ULL, 
            0xBD24927D10FD884DULL, 0xECB08B62FDBF6F9BULL, 0xAE39B474771C7D81ULL, 0x60FEDDF5B40ABF36ULL, 
            0x7807C3C87E21D812ULL, 0x0089A8166DB5E1BDULL, 0x4A60221DB93D62C9ULL, 0xA62B23086CC8A946ULL, 
            0x69EC3F1E0029B214ULL, 0x978A8CF9B7469DF3ULL, 0xF4D8146D91E1F180ULL, 0x3245EA39F848D561ULL, 
            0x5132C21BF163DC9EULL, 0xCC1B6A935EAD40DBULL, 0xBB978C55FBD11803ULL, 0x8791D68322E718C8ULL, 
            0xD5EE6CAD5ED43E2CULL, 0xCD671F057B92A6A9ULL, 0x7656C8BED159E282ULL, 0x0FB196E026CBC684ULL, 
            0x6B0EC7D230BB5406ULL, 0x85678693C2CB4A15ULL, 0xF94A16B65FDABC3DULL, 0xE7FFF34AFDD4F202ULL
        },
        {
            0xB919A443AC58E5D3ULL, 0x8E74DB8ABC1DE278ULL, 0x04AB35A58D584F38ULL, 0xE1D84E2E5B5FF014ULL, 
            0x5D5A911D4AB7B668ULL, 0x3F26EFE35CC692D3ULL, 0xA9C979DC326D2BCBULL, 0xBDE2BAB190235E9CULL, 
            0x8AFD91B045BB2442ULL, 0x8F9A777685A96A53ULL, 0x4772A6E0B27202D5ULL, 0x63FEBFC1A1591EB8ULL, 
            0x0E99A55AAE59E36CULL, 0xD552C57FAB710BAEULL, 0x1B9F97EEE91F6A33ULL, 0x741AE3E22310F154ULL, 
            0x269BDA980DAAE3F8ULL, 0xAAA2C2F0FF7B0F28ULL, 0xBD5B156275705EAFULL, 0x83B0BA411D154BEFULL, 
            0x7336DBBA5AF0112AULL, 0xE1DE1A65E90C07B9ULL, 0xF0690CF9A8F8A6A5ULL, 0x0F132E9C15A40399ULL, 
            0x6BFBB52A2BC197DCULL, 0x56B4AA9A171A6BA2ULL, 0x99139CADDF345D0BULL, 0xDC24FC99B8EEA97EULL, 
            0x8FC5A47F454CCBCAULL, 0x3A0657E49A670DF2ULL, 0x921B559C9854CA53ULL, 0x09EB82EC64716050ULL
        }
    },
    {
        {
            0xB0FC31C3A57D357AULL, 0xE60D482430C85334ULL, 0xE40F9EAAC31C1FC9ULL, 0x8FAD07BD49F76212ULL, 
            0xE27A0AE379A3F327ULL, 0x96E0D7174F3F443CULL, 0xCE7A772EFC73C31EULL, 0xC026466A468AE8EDULL, 
            0x13D964EBD5960B43ULL, 0xBB25A70F03D11BE3ULL, 0x04C62B577EC80E6DULL, 0xC50C745D0D634BAEULL, 
            0x098E84D2E2177687ULL, 0x97103571D05EBC78ULL, 0x371EE767A35E231FULL, 0xF46CB104DF687EBCULL, 
            0xE4FBBC4DDEA25666ULL, 0x851627FB9A404F1EULL, 0xDA5790DD06DC38D5ULL, 0x8D3C33A8E01D7AF7ULL, 
            0xD617717F80103F47ULL, 0x4F3E1292554E5025ULL, 0x1A14C352891E23F9ULL, 0xA2BD75F9D7E6E2EDULL, 
            0x59ED6B11F035B80EULL, 0x2D2219335D842799ULL, 0xD7CCC20F16C413EAULL, 0x21F4CF5864983578ULL, 
            0x5078E188978A4777ULL, 0xB324E0406379F4A4ULL, 0xE7AA70AA7C76E307ULL, 0x5DB750CC9A42E324ULL
        },
        {
            0x2F85A8365E4C3652ULL, 0x194087D7C4E90C2FULL, 0x98C02204EDB20149ULL, 0x853C5F949D29F3AAULL, 
            0xF1BD2343D30BBAA3ULL, 0x80F8D7BAB5027142ULL, 0x84A6D1B592F40B3EULL, 0x88D410159284D813ULL, 
            0x462E91116AEC5583ULL, 0xF56713C092841746ULL, 0x5EC1E1FBA4E607E2ULL, 0x1C4C5ED85F3AD90CULL, 
            0xAF5DEDBE2A80A17DULL, 0x9AAF8BCE65334DC1ULL, 0xE882877DCF9D9626ULL, 0x4CCC176669ECA57BULL, 
            0x9B1B77244FAB0518ULL, 0x2593E49020800E11ULL, 0xBBCAB595C85D65C0ULL, 0xB292F9AD7BAE93B7ULL, 
            0xA6D7488A0D5F7FD6ULL, 0x5E6E67089C7F7345ULL, 0x81A90298D916C762ULL, 0xB09F429E4DFD353BULL, 
            0x40EFCFC1238A4B3DULL, 0xCC2A2F4A4A158ABEULL, 0xC7400E94463F0C41ULL, 0x7B8CEAF14585FF8CULL, 
            0x8B7C7A75ADD0351CULL, 0xCF064A00748C1E68ULL, 0xACBA904327472025ULL, 0x4CB70FA657F03979ULL
        },
        {
            0xEAC2A76C7F464C41ULL, 0x5F5F3BCB581C9ECAULL, 0xA2CE64B4AC36F5F8ULL, 0x8D363BD80B41C973ULL, 
            0x64D975A7E668247FULL, 0xB506CE37B341C798ULL, 0x496A90C0DAA7EEE4ULL, 0xF55DDB412D4D4EB5ULL, 
            0x8B78B2C6B5D5B72EULL, 0x90DB7033781DA460ULL, 0x4D58D62870F6D327ULL, 0xA3FC76831C799CF5ULL, 
            0x522BE8D83B341035ULL, 0xB435DC8E3BBED903ULL, 0xB3877FD20FA81BD1ULL, 0xE5A2A11C1BB72696ULL, 
            0x89B640A65B595C46ULL, 0x7DFB4C1E3AF24A5BULL, 0x4141EBE959A208FFULL, 0x57F9459CD56100C0ULL, 
            0x18DA9376E516CAD6ULL, 0xDF3532D96B959518ULL, 0xD017E4CE81AF0FACULL, 0x061C4CC801E2C5B3ULL, 
            0x009B2BC591FF1AEAULL, 0x82A0533DC4957623ULL, 0x8CFAE22687FD8754ULL, 0x377FDC03815F9A20ULL, 
            0x4BDDEB2EC97E79F8ULL, 0xE16B90176D1B09F1ULL, 0x4B3293E6C524FAFDULL, 0xDA7659F37B2A05F1ULL
        },
        {
            0x1D47817E5C2E4165ULL, 0x6C73288F8D4362B5ULL, 0xF1A98D0CFB36747BULL, 0xAE9071B801E0ADB4ULL, 
            0xC162CAD1F30AB5D3ULL, 0x266A76C83EF9B7E0ULL, 0xC4F532024E54380CULL, 0xD784F5DD30ADA978ULL, 
            0xD25698A2A0347BEBULL, 0xD5FEB7D5CF53586AULL, 0xA820541D7E56F48FULL, 0x5416C653BF6BFE49ULL, 
            0x760712D54F8DE1E3ULL, 0x98AEFBCB7A147DC5ULL, 0xA8EA3A3E9A57EF08ULL, 0xC073878BB5E82E75ULL, 
            0xF9514B53B3110524ULL, 0x7B6EA3386EF0BA95ULL, 0xB7A3A4C7EBBC212EULL, 0xA5207CF157D4D1C3ULL, 
            0x3261E02AA956E42CULL, 0x38CA6C308EC00C09ULL, 0xBDC71FDD39F7D5C9ULL, 0x41B245EFE089C2F8ULL, 
            0x0CF5BE154459A1DBULL, 0x0043E2E430B9A978ULL, 0xCF1152668E6C1001ULL, 0x6452E9230C08E21CULL, 
            0x2D637EF11752BDCDULL, 0x31AAD0D6981FBAA4ULL, 0xFFA6C06CF88CD3A5ULL, 0x9D4439FE01E8735EULL
        },
        {
            0x2FCBE3392611491AULL, 0x96720E42CFE03697ULL, 0x2E9B5DDBB8FA5EFFULL, 0x2D65FD01B4522770ULL, 
            0x5516834A9D4D224AULL, 0x60DA69ACAADBF687ULL, 0xA341E71ECD4351F1ULL, 0xF6D3E8D8668FB9D7ULL, 
            0xB0B03C05C9C095EBULL, 0x62CF9A1D4C0DD31CULL, 0xBE1CF4957D5E3DA9ULL, 0xBAC35BA52A564643ULL, 
            0x8DBEBBB90698F5A2ULL, 0x6D20CDB054DABD36ULL, 0x85A1E47C8EA02E75ULL, 0x4DE3EA63EE96B2A2ULL, 
            0x9FB6361959CE88FEULL, 0x4E499B7069DB8EAFULL, 0xDBFA4A01458A30BEULL, 0x0BFE92FFD6621A73ULL, 
            0xE8F0470EAC6A2DEBULL, 0x5B8952C4CBB53694ULL, 0x1329E555C0C3ED5CULL, 0xFC7CF9A1A6D54C80ULL, 
            0x7F27B82E0E4E4192ULL, 0x4B587EBBC55A8FCCULL, 0xC40B07CFEBDD450FULL, 0x3BEFCB6F2FF11C19ULL, 
            0x7FFA523C5605619BULL, 0x973ABB8147BEE040ULL, 0xD96C473E3D7A3DFAULL, 0x7B2AC26C15512D2AULL
        },
        {
            0x186805C0C5B2F6F2ULL, 0x3F3ED58D39BC7F35ULL, 0x5B742539F4D43F71ULL, 0xC2CEEE5C88812D85ULL, 
            0xED3CA4566CFC665AULL, 0x94EA18FB819A802AULL, 0x2B8D496EBBCD3BF2ULL, 0x7FC905DDCCB34A21ULL, 
            0x4E35225A96BB2CD6ULL, 0xDA2CA50DE6ADD1BFULL, 0xB1402E065442AB6AULL, 0x93B0C63D3BE9C2A8ULL, 
            0x80A6A7FB968985A6ULL, 0xD53A18D0666C7665ULL, 0x8E236DB6F15D0890ULL, 0x83978E58BEF463EBULL, 
            0xBF80D8C1EDECBE6AULL, 0x7C0594C39D2B19ACULL, 0x7E2CF42356316B1EULL, 0xC35BDB4499F9F14FULL, 
            0xE4819601421B1E9CULL, 0xC2AAA9E0F75B72D2ULL, 0xA730767B7CAC5B00ULL, 0xB45F2587F4DCAF93ULL, 
            0x0043532527D2392BULL, 0x6564382E3296BF29ULL, 0x88885E7E761D97A2ULL, 0x0110D06FDA1468E2ULL, 
            0x74FD051E9BD6001DULL, 0x6A6B2034F329139FULL, 0x97BA0D7CCC9C594BULL, 0x2B0EF82AF39774EBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseDConstants = {
    0x5B418D7F72A8113FULL,
    0x4396E6CDC36A6657ULL,
    0xB40B54374C3129EAULL,
    0x5B418D7F72A8113FULL,
    0x4396E6CDC36A6657ULL,
    0xB40B54374C3129EAULL,
    0xF53DE00D5C986262ULL,
    0xDAAF6C77D8AC87D0ULL,
    0xB5,
    0x30,
    0x66,
    0x36,
    0xAB,
    0xD8,
    0x80,
    0x11
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseESalts = {
    {
        {
            0xDFA6B9322D42E3D8ULL, 0x77CDF60BCF926FC6ULL, 0xC5BDE502ED75EE83ULL, 0x76C04C8A5E9E940FULL, 
            0xC66FAECD63F4CA45ULL, 0xDB845D05177ABF04ULL, 0xD3307BC975DEAE22ULL, 0x86F47E510930A19FULL, 
            0x0279CBCD7F613A46ULL, 0x38FEBC6A01BEC4D9ULL, 0x288728140E4FADA8ULL, 0x931F1E76A834B800ULL, 
            0xB8B93981099CA88FULL, 0x9A9055D6F0E5E4B4ULL, 0xF980468FFF63FF9CULL, 0xDC904D8E0976D588ULL, 
            0xB21BDE432FBD3EFBULL, 0x444867FCE30D19CFULL, 0x5E5DCE3873096E4CULL, 0x1F23C492F07E0400ULL, 
            0x0124DD1D776087F0ULL, 0x91CE6E3AB5FFF598ULL, 0xD61F3A52EE58FDACULL, 0x21D02403229B9156ULL, 
            0x53E66A88C45B1811ULL, 0x23D5A244937C0B17ULL, 0x2E2A6C907A009541ULL, 0xFF01D7529431CD8CULL, 
            0x2B08599FBD0D2C29ULL, 0xF8C9BD283C7E7553ULL, 0x9BEC726BD82F49DFULL, 0x7431278EFB596D3CULL
        },
        {
            0x4B6E763D572CAAEFULL, 0x8E320088133C4CC4ULL, 0x07237A4BC65F818FULL, 0xF0DE0E103F6FFC20ULL, 
            0x7BE15FBEB7402DB4ULL, 0x21E3643BE3E50D54ULL, 0x4F042B433C8A42A2ULL, 0xA40C949E98DFD446ULL, 
            0x7FC7C2D67D06AAB6ULL, 0x0B7855EC473D4D3DULL, 0x584418B46669FA54ULL, 0xC32C5D42E9818057ULL, 
            0x7351768C21AC0278ULL, 0x173B6FBE26E7C4B2ULL, 0xA61122AB85021D09ULL, 0x90FBBC4DFDEE0971ULL, 
            0x886EEDA01925D222ULL, 0xD8F5AA948C5F505EULL, 0x9B17A657D9DA2346ULL, 0x6F8F5AA103F1D1ABULL, 
            0x84005EF799E2F9C2ULL, 0x0E04C3A883FB42A9ULL, 0x03D802DE1E576BF0ULL, 0x9248BBAD2BC5DEF2ULL, 
            0xC60A885D744335A6ULL, 0xC19697DDDC279780ULL, 0xE1BCE467B57AB93DULL, 0x2409285D67FAC2F5ULL, 
            0x20FAA4C645667333ULL, 0xE256993A687224BBULL, 0x13F7FAE0A0AB6C98ULL, 0x4CDB329D84BCD749ULL
        },
        {
            0xB5715205FD36F82BULL, 0x051255AF29C38892ULL, 0x35722EF65C6943F2ULL, 0x8DA82DB9664CC647ULL, 
            0xC4B4CAD970CC6144ULL, 0xA1CD288D91F88988ULL, 0x4C535364669777DFULL, 0xB290AB4705DC8D36ULL, 
            0x32911068BAB02375ULL, 0x44D710728CB31C3AULL, 0xEA5F583F8C1A9A11ULL, 0x354427CBB11FCD7BULL, 
            0xEBCCD2E7B9995493ULL, 0xF6D7BF361C4FADFFULL, 0x867C1F30B108B81CULL, 0xCEFACEB5EB9AC107ULL, 
            0xF40656CBB704CA0BULL, 0xEC1DA04D884B28ECULL, 0x9237B705EE35DEB8ULL, 0xDAECDF55F6BFFCD1ULL, 
            0x4D54F449C3D16D99ULL, 0x52DABEB01B2963D4ULL, 0x3957E0E596FDB65EULL, 0xA74E5269B57C8812ULL, 
            0xF39B464F64F9BB65ULL, 0x7991FE326AD54E57ULL, 0xEC8D234CAD80DBA3ULL, 0x3D24C84261981AE0ULL, 
            0x714413BF3159919FULL, 0xD68389A4589F96B5ULL, 0xB8C308B9184A45A8ULL, 0xD0D5DBF46706322EULL
        },
        {
            0xC145DA4079EBC076ULL, 0xE196203839A153EBULL, 0x0EE22A550EDE6393ULL, 0xB8055A967F87F528ULL, 
            0x7193AF8A5D9792E7ULL, 0x2273D634F40997F0ULL, 0x8975FDCB9777ADE8ULL, 0x036EFCF78F59ECFAULL, 
            0xFE755275F5A6A969ULL, 0xAC5B4F8A2B651CC1ULL, 0xF2541D38FBE1E035ULL, 0x5D7A9BC64E4C17EAULL, 
            0xE4DD01305B2532D3ULL, 0xF9F9B73D7EC57834ULL, 0x8F6366B68A122D6CULL, 0xAD845518D805EFECULL, 
            0x5483687E82E12B2AULL, 0x99B99F85EF0C0992ULL, 0x2F9C790FFAF1E204ULL, 0xCA41113DC9303412ULL, 
            0xD63D366E2E2E5FDCULL, 0x51EBB34D41395852ULL, 0xBDED566C226B5CFCULL, 0x3201D0EE027E08BCULL, 
            0xD11BDBA85A97806EULL, 0x4753ECEC5B654DD2ULL, 0x7AE67F31CE59C985ULL, 0x85FC75CFCBB3AB41ULL, 
            0x74C714090135DD00ULL, 0x835DF1E442133FDFULL, 0x477452CDB461C1D1ULL, 0x197A3AA8DF7870E3ULL
        },
        {
            0x40497C42B9B01FCEULL, 0x475CDDCF66DD245BULL, 0xD898A4C49B7DEED3ULL, 0xED31037E6374C58DULL, 
            0xE70F7A80EE2C56F8ULL, 0xC763C7C9B441BDA5ULL, 0x860EDFBBA4CD9992ULL, 0xF08BD276780A1FA4ULL, 
            0x983CA3ACCAED20A3ULL, 0x229A1F1586411311ULL, 0x27B32AA5A05C9CCAULL, 0x57A6269AD9C7CBD0ULL, 
            0x6E502E90C23F90FDULL, 0xE43CE57B23941145ULL, 0x0B8D7BC052EC333BULL, 0x087D8CEF3491EE0EULL, 
            0x862538C3E6385EB7ULL, 0x1570529475746768ULL, 0x887AD922589ACBB5ULL, 0x279624392FD3581EULL, 
            0x4661ABCD8D9693E9ULL, 0x0F81814609FBC072ULL, 0x81D3EC11D4838A44ULL, 0x1E7AE74B2AD955ABULL, 
            0xA037AD0BA1AA8934ULL, 0x1C37B6503830B497ULL, 0x9CA70B2555AC318DULL, 0x16BCD12470288586ULL, 
            0xC9F1085A571B1CE9ULL, 0x4697D6FB435954A5ULL, 0xFBFD5692433C5B6BULL, 0xB4BC98E234BB4576ULL
        },
        {
            0xEEDC834B55A60904ULL, 0x44A034E5ECF86983ULL, 0x0131146A5E323E7BULL, 0xEC3A984086CD4B37ULL, 
            0x9C882D12E954F109ULL, 0x8FD20045B2AB911FULL, 0xB5364A642AC6B5CAULL, 0x40F9A85F27E12C37ULL, 
            0xC273D94E117A121EULL, 0x722B9A7C243BD4D4ULL, 0xFB753F12A230A5C6ULL, 0x5059ED6E5CF49FFFULL, 
            0xECB7EAFA89651CAFULL, 0x93415AD854BCA072ULL, 0xEC305629C0702C68ULL, 0xB292D33F60E1A140ULL, 
            0xA466E192081D5C76ULL, 0x2D91713ADC28C3F6ULL, 0x3B0AE1779CEAF684ULL, 0x5CDB7720DF0F793BULL, 
            0xB51BC58B619AADADULL, 0x1DD77A794AB84C9EULL, 0xE243630C5D5C012BULL, 0x2403E9CAAFFDE40FULL, 
            0xD6EB1A7B78C5F26CULL, 0xB07ECBCAC4A39E77ULL, 0x6291E2B8454024DFULL, 0xA7FABD50B2F537F2ULL, 
            0x17A4F4A68FA1C95DULL, 0x1067FEA301F91C30ULL, 0x41C924B002936C3CULL, 0xB718FAC785825EBCULL
        }
    },
    {
        {
            0xD9AE7148978D34B9ULL, 0x60DBD6A3203FDA82ULL, 0x28D6C4DC5A808BD0ULL, 0x1BF62639C7BE4436ULL, 
            0x3660DD914704F819ULL, 0x2171CBB19FA6FDC8ULL, 0xBAF5C8E44FC9DBFCULL, 0x8F79056C2187B0DAULL, 
            0xAC0C4FE1D7502D27ULL, 0xBFD0A32269FF1B7BULL, 0x269FC5A3A74BD58AULL, 0xED45F4A767A207BCULL, 
            0x74D013E8607E5B53ULL, 0x7178569178E711C2ULL, 0xDE959EA5190314A4ULL, 0x96828CE4FA8FDD3CULL, 
            0xB03D89EAF76A8E74ULL, 0x621E45F808F23540ULL, 0xB1A2F47DE7FB6C20ULL, 0x11A158024B1EE4C8ULL, 
            0xE0481C12DA838324ULL, 0x83EF2676D4277CCAULL, 0x80D91F514AC3FC0EULL, 0xC1FD20E0517F176CULL, 
            0x37F90305885FF88EULL, 0x6D18990AB7F2A686ULL, 0xF1116F53E0E6C1DBULL, 0xFE5494A57894CD64ULL, 
            0x4C93A33A5ACAE91EULL, 0x3990912812E7DD40ULL, 0xB709A1DB89966C23ULL, 0x55BF3E810686A7AEULL
        },
        {
            0x1CBB5B00A4FCF200ULL, 0xEC787082C3499B3AULL, 0x93876557B90B6B24ULL, 0x3FCAE8FD5AF89DA8ULL, 
            0x02B1876986BC11DBULL, 0xA860AD6346F158DCULL, 0xDF6EB1C813FD7792ULL, 0xA583481BDC3E6B61ULL, 
            0x7F89AFE00429DB43ULL, 0xC6FA694AD668AA6DULL, 0x3F4DE36B3AC095F2ULL, 0xFD15FEE58E9D3ECEULL, 
            0x1529B5FD95ECE352ULL, 0x0AE48F1B884BD23DULL, 0x90F68E5BA18F6E3AULL, 0x77B66590DAAF8024ULL, 
            0x634BAEBBCD368AFEULL, 0xA48388212279C1F6ULL, 0x896119C0CB3EBCDBULL, 0x9BFEF68708F9FCF8ULL, 
            0x641D32FB75C98943ULL, 0xEA5E12DDEE180C27ULL, 0xE0D7B012788B567FULL, 0xDAF4A894487BC5EFULL, 
            0x38920958037F89D0ULL, 0x6DDBB949CF5E1176ULL, 0xCCC9C456A38E8756ULL, 0x6D76203BD7BDEA8AULL, 
            0x4E5DACFEACE74EB2ULL, 0x26979AC44EC4CDC4ULL, 0xF644FE8CD6174513ULL, 0xDA6CF1577B734EF6ULL
        },
        {
            0x2CDD04996BFA5961ULL, 0x9B8928E00AB5CE0EULL, 0xE815369D48C67519ULL, 0x4FFC91B4399B453BULL, 
            0x069B0473B970354FULL, 0x3F1E70EF685369F7ULL, 0xE9EDD2D997461F7FULL, 0x0F70D9CC8E66CDC2ULL, 
            0xA5CF337BCC4D03F2ULL, 0x771B1D2FAC53C259ULL, 0xFFFC36F2C5DA377FULL, 0x9B8C3E1B40547C3CULL, 
            0xE5F31C6EE38BBC7EULL, 0x3DFEFA2DB30358ADULL, 0x8B4DA82AF930E981ULL, 0x5A425F8DC07A75ACULL, 
            0x8DB1884B9FC07C17ULL, 0x0251986087F5C295ULL, 0x10F2DE5378584721ULL, 0x066EC4D5DB6961D9ULL, 
            0x4C08BBD0EFFF0CE5ULL, 0x0521577B7DDF3133ULL, 0xCAAF19F05065948EULL, 0x7B590AD912984360ULL, 
            0xFCC359A28CBA07EAULL, 0x91A1AF577A50A254ULL, 0xE48367687E1A5B2EULL, 0x0157245949735B4BULL, 
            0x23A0B4B1908089A7ULL, 0xC0A22304A381BB12ULL, 0x7F0A2E6925D13AA4ULL, 0x439C1646926D1762ULL
        },
        {
            0x7460CE68DB215879ULL, 0xD0530D893A24AD11ULL, 0x52382BC5D6635E4BULL, 0xD0FF9B332CD9BAD3ULL, 
            0x94D689F51FB08311ULL, 0xBEE8AAD800035AD5ULL, 0x6EDF437E0F5AE34FULL, 0x7B98726B1D6F089AULL, 
            0x0515425C8574294EULL, 0xA58050BEC4AE2463ULL, 0x83BE60CF1A8B343CULL, 0xAD11853B190FAF82ULL, 
            0x9B1CBBFA76C9AB2EULL, 0x88A2F267F96FD145ULL, 0x0D805F5BDE06776CULL, 0x7D74F73B5FBB1BC5ULL, 
            0xBE252F748E8493CCULL, 0x175BC340DD77174CULL, 0xD2B9256B0FD8380FULL, 0x47180D5D41818A5DULL, 
            0xDDB831385B8F9F3BULL, 0x1F1A014FC98A612FULL, 0x99930AC1063C02EFULL, 0x73425CAE54A1CEB1ULL, 
            0x6F0809139A0A7974ULL, 0xCF958856B9D6A5F5ULL, 0xED964FB1E934AABEULL, 0xC42015DEEF7BB803ULL, 
            0x9C10D56F06502571ULL, 0x513470AA40FB179DULL, 0x4131551111B5974DULL, 0xCA38D208460DED4BULL
        },
        {
            0x5B7385A3D5AEB12FULL, 0x5F49B2BD016107E8ULL, 0x0719E6AEF50C61E7ULL, 0x00CCACDDC9376D04ULL, 
            0x463B19A4CD7361EAULL, 0xC2061A8CA7484A26ULL, 0xDBFE65D2203E1A57ULL, 0x45C20E2DCC8E70A0ULL, 
            0x71AF07695F6D2D1DULL, 0x00D3201ED1D10E2FULL, 0x61CE339DF997DBB1ULL, 0xC61E90181A322034ULL, 
            0xE4E159CCCFEDF9C2ULL, 0xE40ABE8B49B31E04ULL, 0x76CA444338158BBDULL, 0x0D1F92FEA576EA12ULL, 
            0x7D0709881B14BBBBULL, 0x3C8F176E9B573B91ULL, 0x04DB87ADC2B85020ULL, 0xEEC44849D6FAC81BULL, 
            0x88C3E373885E490AULL, 0xB7DE015A8BF767F9ULL, 0xF5A1E2EE7F264DF8ULL, 0xA4D5B873BFD0F8B7ULL, 
            0x87ED355472F65657ULL, 0x5DAE92ACDCAD83B8ULL, 0x3B5901AB63401149ULL, 0x34A420B8A1655B71ULL, 
            0xE83282CE209D4A67ULL, 0x427269AABE7863D4ULL, 0x646378225A9BF9FBULL, 0xD23AF86CB600D93AULL
        },
        {
            0xFA3780490E477293ULL, 0x24C6427C72B99F6AULL, 0x437D5EADE8146F39ULL, 0xBF79D4D8BADC4A8EULL, 
            0xD36F1BF6B2CE4DF0ULL, 0x53A680E0310A51FCULL, 0xDA3A89B093B84157ULL, 0x2180E6870C825A51ULL, 
            0xE5564C227B539C36ULL, 0x002978010AF2E0D2ULL, 0x884409D5AA48B555ULL, 0x6656F9DC396BD595ULL, 
            0x744216697FD1DCADULL, 0x9878244F00974A63ULL, 0x670575D81FA4922AULL, 0x72B3F501D08D9CDDULL, 
            0x79D64EAF1F0668C4ULL, 0x3171D7E42CEDC588ULL, 0xFD908A0123C5B039ULL, 0xADD11BA669EBE541ULL, 
            0xBA04E7E47E159FF8ULL, 0xF9DE2CE7DB34ED46ULL, 0x54E1DD09FA72A86FULL, 0xBCBD7262A83ACB91ULL, 
            0xE6CFF71155238529ULL, 0xA6C431B33DEC5127ULL, 0xBD0AA6F2639D13C9ULL, 0x13A868CD4B4C0AB5ULL, 
            0xAF24EA363E519C9EULL, 0x4A51DB17A57788E0ULL, 0x433BFA4A67424FDDULL, 0xED7B5EE37D640BD8ULL
        }
    },
    {
        {
            0x9000171F2B5FE8C3ULL, 0x95CD84A2C607CA1CULL, 0xDEC9E0EB0765D002ULL, 0xE09C80B196A1F849ULL, 
            0x59F8E94EFF898132ULL, 0xFA1E79E2C1EC0111ULL, 0x2EB0DAA7F6075544ULL, 0x68D37974C2F11301ULL, 
            0x6C36FDB3D71E5152ULL, 0x6C1B31E2C6B9E557ULL, 0xE45019CBA590D163ULL, 0xD4ED6FB8A6E96B33ULL, 
            0x559D0F441B134A40ULL, 0xC1D4ED6893484D0FULL, 0x96523AEBC664A9CAULL, 0xC3FEAEAC0C8D7361ULL, 
            0x424C67B9CAC21874ULL, 0x07FDD57B4F0F417BULL, 0xC35EACD70C903416ULL, 0x37B82E8231A19339ULL, 
            0x3B0BEE8A1AB53874ULL, 0x0D96AF915EE215C8ULL, 0xA35C9FB39045A0EEULL, 0x896AA05B7B8AA63FULL, 
            0xF9932F66E251F7EAULL, 0x6AA4AE4798FE2E0EULL, 0x8E5F9346FEB4D7FCULL, 0x0BEFC4AB77527BA5ULL, 
            0xE7037D8D41E8CC27ULL, 0xCB4817DAD75BC395ULL, 0x3BE282843B7A742AULL, 0x1B1A68821AF80250ULL
        },
        {
            0xFBB88A5AA75312D1ULL, 0xB71AF862F1740097ULL, 0x4D0936A04C5296A2ULL, 0x83567110140E980AULL, 
            0xA32B6C34DF7DCDA9ULL, 0x70DF351C7CDBDD39ULL, 0x8D449EEBD88F8E6AULL, 0x1DB0017A01EF5A96ULL, 
            0xBB7F8F55597CBEE5ULL, 0x70564128F66AA35CULL, 0xB0B25F3C00B6AA7DULL, 0xE6523C02342E03C2ULL, 
            0x994177667540D8B7ULL, 0x230D9A096D28A0AEULL, 0x366F736902C0FE27ULL, 0xBD7C9896887AD0F1ULL, 
            0x0C00D41FE3AAEA92ULL, 0x6C11BACFCAF4012BULL, 0x1347147BB74AFCBFULL, 0x1E162F9DF7C90735ULL, 
            0xADE97E1A31F50973ULL, 0x7FC575EA3C00C1C2ULL, 0x83977A6124C57D54ULL, 0x89F13E5BE7BE9208ULL, 
            0xACB785BDA34B2852ULL, 0x8FD0B62E641CF3C2ULL, 0x36FF073456560463ULL, 0x94F37CB818B67C48ULL, 
            0x39D8391F4E1F563CULL, 0x9824B6974A265D7DULL, 0xF1194F3ECD1DFDBAULL, 0x6BC9B7159374C229ULL
        },
        {
            0xCFEFE59F0CAD26B1ULL, 0x2F5FC887A5A135E4ULL, 0x34C9A58DED49A235ULL, 0xCC290BB5D796C720ULL, 
            0xBC420F4332D61420ULL, 0x820F553F47B3789BULL, 0xE17876801A8C6744ULL, 0x523DD85AEB5D967DULL, 
            0xCB31EBE1518722A8ULL, 0xD26A496C752AE37CULL, 0xEC1E859EB0B87535ULL, 0x1BA81F57953F2C71ULL, 
            0x7636A2D91C30BF36ULL, 0x67219C5447E93C8BULL, 0xC07A3A8B7C56F963ULL, 0x2F56FE9403B0D804ULL, 
            0x8F97BDA3C3C66A54ULL, 0xA0BBFD70646413C3ULL, 0x48AD5D75FE1A70CEULL, 0x43935BB4FF3DE363ULL, 
            0x2D9DEFD5B2D40F69ULL, 0xA0D28F532DE6CC36ULL, 0x514F14467D50A9BEULL, 0x392AB585D1E65C9EULL, 
            0x2FD188A588FF14D2ULL, 0x4BA80A5BCC0A639AULL, 0x50106CE594166CC1ULL, 0xE266FAECA2E671E3ULL, 
            0x5237093B971946EAULL, 0x62773E526908DB30ULL, 0xAC3A168D28CF166AULL, 0x092FAA1EA58FB4DEULL
        },
        {
            0x29E6D66CAD151324ULL, 0xF5CAB3976EBC029DULL, 0xBB99AE809FBE6855ULL, 0xFB6957171D36CFD4ULL, 
            0xDDDE47693FF99295ULL, 0x2FDCCD3C4853C3F8ULL, 0x95B28521F04D76B9ULL, 0x70316A26E88E0D0FULL, 
            0xE4E84BFDE401BBCFULL, 0x4E30740450666284ULL, 0x764282B3021A86DFULL, 0x2EA8D6204E86A530ULL, 
            0x14D5356D20C8B956ULL, 0xE8302293A5601448ULL, 0xAF12208E460B4367ULL, 0xC2EE83A504504D05ULL, 
            0x33A77C17FF02A187ULL, 0xD2164FCC218E1B72ULL, 0xC1B5D24966331005ULL, 0x2DD48EF5628EA4BFULL, 
            0x412714B859465192ULL, 0x6A72A4CB8E99004CULL, 0x223F0B5234F9B532ULL, 0x9D6CC1B8BF812F61ULL, 
            0x52210707D98EC838ULL, 0x7A30A2A3147D4C75ULL, 0x3BA46C6FD8BE4384ULL, 0xDF51BD314B26D8EAULL, 
            0x1B1F20EC3647CC2BULL, 0x8B5C1E5AD2F374A0ULL, 0xE55A3DE37EB76230ULL, 0xA794C79BD6DBDB1AULL
        },
        {
            0xD985BA34DFDB412EULL, 0x882E10113CDB06B5ULL, 0xBC5626043E2AB3EBULL, 0x85F603A512D366D6ULL, 
            0xA899735C02CC6296ULL, 0xDE2CD7055445739AULL, 0x780D4721D4CB4A2CULL, 0xA50DDD4949853B96ULL, 
            0xFE3E5A75C58CB2BCULL, 0x1ABB05EB891BB7B3ULL, 0x2D1347F6B5B24494ULL, 0x4D0F7780E6507135ULL, 
            0xE2B1509F27418BADULL, 0x8B1E25A479E9CE80ULL, 0xB9E2D15E8688FD21ULL, 0x6966C5227A738DC6ULL, 
            0x0E03B1CFDAB89C77ULL, 0xBC0D6B0D0EE80D77ULL, 0x135FFA1193BCDB7FULL, 0x932BD5B4AD6CC77BULL, 
            0x8B82ADAD28B6F4D9ULL, 0x7CB4F6FEF85912BDULL, 0x2934D537744998E7ULL, 0x42224400519567BBULL, 
            0xAE734C2F77EC200EULL, 0x2514B468B600C737ULL, 0x063C509441D2FAA3ULL, 0x3294A3C9EC5B25C2ULL, 
            0x11571FB307D067B7ULL, 0x949C90C4724C2934ULL, 0x54BC79062EBDD942ULL, 0xCF2FAC2651A5BDD9ULL
        },
        {
            0x6BEF869950139C7CULL, 0x0AEBF32E71312B17ULL, 0xCFC4657794D644A7ULL, 0x8E2B403F03A1EC66ULL, 
            0x57901A58F0D6638DULL, 0xD974190205ADCD4BULL, 0xB91CA23C7B3F73CCULL, 0xA36CCEBBCBB8182DULL, 
            0xF075C764DE387F17ULL, 0x7A2A4F62B27C8A65ULL, 0x29B0C16D5AC9B662ULL, 0xCBF48CD05ED5F7C2ULL, 
            0x84F056BF75147F6BULL, 0x303C73C05A93EE90ULL, 0x7096B2EDE012F4A0ULL, 0xDA58A378233B85CEULL, 
            0x07501EC1C229FB1AULL, 0xC202C50EA572446BULL, 0x8492C8DA03B192A6ULL, 0x8500DC21AAD91D72ULL, 
            0x5F756A0C969D3CBDULL, 0x2AC5E62C986D23B8ULL, 0xDA5C53530F628EC5ULL, 0x917E6806FECB29E6ULL, 
            0x793539790A1A2437ULL, 0x12D2359CF9F67D45ULL, 0x26CBECDD246F6141ULL, 0xA51F70EC19995C66ULL, 
            0x5FE70F8159FDE602ULL, 0x18BD75B0F1585E5FULL, 0xBA7884BF08F14E2BULL, 0x858FEBC252786153ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseEConstants = {
    0x35BBA549BBB860DCULL,
    0xAB8A45888EF45728ULL,
    0x254E8B8543519FC0ULL,
    0x35BBA549BBB860DCULL,
    0xAB8A45888EF45728ULL,
    0x254E8B8543519FC0ULL,
    0x61C314094DF5DE77ULL,
    0x2050B39FBCE033C8ULL,
    0xE8,
    0x82,
    0x31,
    0x31,
    0x6D,
    0x51,
    0x9F,
    0xD1
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseFSalts = {
    {
        {
            0x122AEFA1E64894E0ULL, 0xE028814212ACDC61ULL, 0x300334741D1432DBULL, 0xC61EC5397C815CFAULL, 
            0x5A3A259232F34225ULL, 0xA45B700FC45D057AULL, 0x0384FA8AEDC0B368ULL, 0x158034C68E635041ULL, 
            0xCDC1E7E4BBC1F163ULL, 0x6F2231A1CF33654AULL, 0x57EF6B5AD4BBFE50ULL, 0x3F4FCFBCAE12A4FEULL, 
            0xA2F3D493386C6EB0ULL, 0xAE1EA1922221DB57ULL, 0x8DB160B78C1B3165ULL, 0x86F7563420E1083BULL, 
            0x894470CF38562505ULL, 0x5CCA80DF433572ECULL, 0x7B3AA8A3CD84499FULL, 0xD6F1E4C1E004575FULL, 
            0xC40E9A611E2D8C7FULL, 0x64F561140A7EAAABULL, 0xDB6D47BE6125C2ABULL, 0x85F6C5EDC0D07B45ULL, 
            0xFB7C87E9D394F049ULL, 0xA38A25B8F9C14DA9ULL, 0x6EA2C4B47A507BADULL, 0x1B0223D5A9E0C7C7ULL, 
            0x53B1814245706B27ULL, 0x1797A06FF816242CULL, 0xE2254E79AB6C2898ULL, 0x90ED5D456A2C766DULL
        },
        {
            0x502B9307BFE4C62BULL, 0xC8255A4564CC03D1ULL, 0x93D2B29091485863ULL, 0x4BCBC542DC5763FDULL, 
            0x9AE4E31E9B50353AULL, 0xE9672CEE15ABFD3BULL, 0x00B28C2755A8DC7EULL, 0x0B5F46800A8BEEF1ULL, 
            0x3F95834F4E50C789ULL, 0xA3A9DF54471B2588ULL, 0x9684BD3F9991F06CULL, 0x0B263BB779180FE0ULL, 
            0xD9C976021816103AULL, 0xED1543CCCC28C342ULL, 0x9BD87C9CF4030CF7ULL, 0x4EB2414657F19809ULL, 
            0x3B2707F9D8913F44ULL, 0xA871938B286444B6ULL, 0xBE19EBD1B6460822ULL, 0x50E35DF24CE10915ULL, 
            0x3C373AA054A219FCULL, 0x2AE3DE1933A9E86FULL, 0x1EE54A127A2769ABULL, 0x24D1BA6093EC856CULL, 
            0x23BC566414E3B192ULL, 0xB0AC56D23F53C0A0ULL, 0xCB0CBB7582D8483BULL, 0x51DF341021938514ULL, 
            0x618A0B163AF59EF7ULL, 0x05356E61822526B7ULL, 0xC3C595B160C73735ULL, 0x3EA019DCC5190D33ULL
        },
        {
            0xD8F8DC384F4B401DULL, 0x287F5E5E8F6BABBDULL, 0x870483FA49C749F4ULL, 0x2442503627F95B45ULL, 
            0x4A1227655B5C71AEULL, 0x799B14AB3EE68746ULL, 0xCD29FC23964BF066ULL, 0x255C703C712E7B4FULL, 
            0xEFA83687A7274278ULL, 0xC82FC3979E5D9877ULL, 0x47820F30C8470C9BULL, 0x8A18C693B04E739DULL, 
            0x6D52D9031326B71AULL, 0x1C247740B9C830E9ULL, 0x1659DF8508E2C7DAULL, 0x805951960BAB3395ULL, 
            0x4014E9D5C12DAB11ULL, 0x4F7023DCCDC1E8B5ULL, 0x35062847A01142F2ULL, 0xA1F6FA0245C31D5DULL, 
            0xAA08CE1087779E7BULL, 0x716F2C1FC6E7C2D3ULL, 0x03B94B3CFA3C2534ULL, 0x1A9E4D2C20BEE49BULL, 
            0x06A627F1AA6C6D2FULL, 0x75A9F97D8D552E3EULL, 0x802D19F7032BF795ULL, 0x39D5FBC63EC9D728ULL, 
            0x5919D9550EDA10F3ULL, 0xB4540AA9C9B2FC30ULL, 0xA30019B0BC66494FULL, 0x45975C255AE7B1ADULL
        },
        {
            0xF9FF923FF5CEA588ULL, 0x291E468BB405AF17ULL, 0x9ACB0B1339C051D0ULL, 0x35DFC8B23DB027C2ULL, 
            0xDFB7CDF706E8F0BAULL, 0xECCFB6574D321E11ULL, 0xF784B9F12C91DBDAULL, 0xEB5279FD2D241969ULL, 
            0xB367425A08575A0EULL, 0x136A2E0B90C69794ULL, 0x00BAE1F51ACF52E1ULL, 0x413008736B9BA0EFULL, 
            0x487612FA3C435A00ULL, 0x3531D620479EDAABULL, 0xC54692DF49EC34E4ULL, 0xDEE164FCC846FB40ULL, 
            0x36EE64F8A5A152BAULL, 0x306C80E123FC2B53ULL, 0xD1017B56D345F4F9ULL, 0x0D850567EE31077CULL, 
            0xF02FFC05E4A25C95ULL, 0x474C39F3F2171ECCULL, 0x81B91B580E94CC41ULL, 0x9C1F064EA65F587EULL, 
            0x3B1733371C1F4890ULL, 0x8481816ECB61B46BULL, 0xE7315637DCF42AEEULL, 0x5C7DD7F9ACD8CA42ULL, 
            0x86D3678E42239E9DULL, 0xE01C8B22172ED3F7ULL, 0x1A445CE8BCA1033EULL, 0x93D4DF89CCBB5C0CULL
        },
        {
            0x142B084E428B5782ULL, 0x5E6E043679ADFF83ULL, 0xB01524E192B6F00AULL, 0x02EC8DA9661B1430ULL, 
            0x0F12D02ED3F48B58ULL, 0xD34FA7A367FEA784ULL, 0x59BE90D62931DDBCULL, 0x2F2BE5732581F3D1ULL, 
            0xF684E50814551E6DULL, 0x9CDDA6BDD1B74749ULL, 0x72AE02F92B5C2D2AULL, 0x2707B00BB27D30E1ULL, 
            0x46C19957523AF6B6ULL, 0xDF36BC5DCD1B590AULL, 0x8FF8D3AC3157D6E1ULL, 0x157134937DA9D074ULL, 
            0xCF2F691EB7177F01ULL, 0xE9FA20801D78B831ULL, 0x7A24BEF85D25FEBAULL, 0x31C3D62F07A3AF22ULL, 
            0x5B8CFEF8CA089E44ULL, 0x2C9E65163F1CAC92ULL, 0xF3D04EA15E46F711ULL, 0x0A42D0A5EE9CBAECULL, 
            0x1BF7C32175C106ABULL, 0x3C9AD57BD0805981ULL, 0x99E3B20FCC066F78ULL, 0x204FACA40BB51CC0ULL, 
            0x3D1EFC56F3F6929FULL, 0x1A5886AA2135F838ULL, 0xD3E7A16082938FCBULL, 0x888856DD7E464525ULL
        },
        {
            0xBFCCB8B4CCD6D08FULL, 0x3867CF38FA60217FULL, 0xBD89B7DF7FA6B8E5ULL, 0xCBD6A7E0537737FAULL, 
            0xEB7EE4D310539703ULL, 0x656FC072CCE876F8ULL, 0x7C12904AA8EAF25CULL, 0x0F5BA4A15DEFF297ULL, 
            0xD02F4365D1130D7EULL, 0x31D2697F06222D94ULL, 0x860D4AA38FE7A737ULL, 0xFB34D780C8AFA86CULL, 
            0x7E495F3AF015CF4AULL, 0x653D0C5F9B1F54ADULL, 0x84E8C59A3F97BFFCULL, 0xEF34BDD5BE7BCA3FULL, 
            0x6E583CC6BEC294EFULL, 0xE5D290C26219E92AULL, 0x1FA922D089DC6C4FULL, 0x7CA8180E8BB852AAULL, 
            0xB73D1EF1B9529048ULL, 0x9B74A586D87E71E3ULL, 0x6D37459A18AD5CC3ULL, 0x0C0599569C726041ULL, 
            0x8DDF62277DA0AEA3ULL, 0x88DA49252FCCEB14ULL, 0x0BDD8A67385B8EF2ULL, 0xC44B0D3E422AB8EFULL, 
            0xB89FB46AF16739B1ULL, 0x3770D966944EA88EULL, 0x9A7892EB8CF07862ULL, 0x6EE7D148597F9B79ULL
        }
    },
    {
        {
            0x113E638F7CD62285ULL, 0x7C302701C6BFC1ACULL, 0x2AC2F1B1E4E9D2E3ULL, 0xBFC176BB5A7B3AA7ULL, 
            0x36E878B804402FA7ULL, 0xD27DFC693A6B9690ULL, 0xF86A114E5CF7708CULL, 0xD97448CD0F219610ULL, 
            0x4F6F538E308FC568ULL, 0x56CA695FADA564B5ULL, 0xDEC3FB3950775349ULL, 0x6AF80D9951952E6FULL, 
            0x30241E981CAC3C12ULL, 0xA2BA6BCA90E0A3DAULL, 0x14961F15E9413510ULL, 0x3033486D71D7DD02ULL, 
            0x3B746E9F20AAF0CAULL, 0xD9F4C4E8783611E6ULL, 0x36E01057C9D251F8ULL, 0x7D165CED746243D5ULL, 
            0x73B4CD66F895B819ULL, 0x4A79B5F06228ED72ULL, 0xD4E2B3357CF86028ULL, 0xFCC77DC9CF741E8CULL, 
            0x6EA0878608F28920ULL, 0x563D1DBA4740AC4CULL, 0x62835ACFFD08236DULL, 0x1D8FA690E4418D93ULL, 
            0xE49DA39FE00A4396ULL, 0x37BE135EDFFC1E87ULL, 0xD9F01A0D5ACA7857ULL, 0x9CA39B0F088A1775ULL
        },
        {
            0x6708BFDCAD832CAAULL, 0x7193EF8049802FF5ULL, 0xE7CCD8FD7A863C6CULL, 0x8C18371081A2C6C0ULL, 
            0xE8E266F09402FE9DULL, 0x37BB4F68C79BBE8DULL, 0x2468E0E02FDAB3FDULL, 0x8E8916ADDAA85148ULL, 
            0x5982AAC48644342DULL, 0x4AE3A37193BC50C3ULL, 0x7838FE1E1D3B1606ULL, 0xE2C55FC544091559ULL, 
            0xE606D4C78A140B5DULL, 0x35B992F5153BA118ULL, 0x9641A8B72481C9F6ULL, 0x3FF923CA6905FD6BULL, 
            0xA78366008D932A7AULL, 0xC228F52640B0DE9AULL, 0x2B9EBFDCD89128A1ULL, 0x88F42071044CF07FULL, 
            0x171FF4C461756603ULL, 0xBFC9E7E13081BCA2ULL, 0xF107BC5E321978B3ULL, 0xAECD7DADDAA85BDBULL, 
            0xD37CB1B95069A397ULL, 0x91F3C52FBE706A53ULL, 0x21F6C3AE94F9D442ULL, 0xE3DB90219F283D66ULL, 
            0x9C41BA7E03A3F3B7ULL, 0xA5D14999B7114E0CULL, 0x12AB41405561B0BBULL, 0x71146CB2E9203C01ULL
        },
        {
            0xF826BEFF40EC9006ULL, 0xD44E4E3C3338901DULL, 0x65A118D8AE36433FULL, 0xDA7A1E4DCEE0ECFBULL, 
            0x0567B99DAAE85E87ULL, 0xEDBB70313352C404ULL, 0x6BF556E7B0F37DA0ULL, 0x75D862487E1940E8ULL, 
            0x32ECB3AA4A35837FULL, 0xB42B8D487D8F8201ULL, 0xEA3C0532DB5BA80AULL, 0x9B774DB80BA2CD8AULL, 
            0x0AD675EAE93CB1B4ULL, 0x44847DEA6EE11339ULL, 0xF2F9654EB08299FDULL, 0xF07B442236D30C81ULL, 
            0x57FB3DB74DAECF0EULL, 0x914C6A008D57C42CULL, 0x81FB2E654BE3002FULL, 0x71A18F91DFC5F549ULL, 
            0x2898022CFECE9010ULL, 0x8944801B72EDF1E8ULL, 0x854131ABFC190588ULL, 0xAD6C5C46EE49A88BULL, 
            0x5021C84878DB4038ULL, 0x139BF6FC79D17A83ULL, 0xB9A115858E44D636ULL, 0xBDD83CE675D3FF8AULL, 
            0x540E3196DB1A8507ULL, 0x96C2F8ED3F75F13BULL, 0x0F090F03BDA264A8ULL, 0x7B6992ECBA6B9910ULL
        },
        {
            0x1F5CB92C162CFA04ULL, 0x6D113949987A86A7ULL, 0xB9E749CB8D0ECD2DULL, 0x74B92993D8AAEFA9ULL, 
            0x16BA1AC1D30D6232ULL, 0x494521EE40F7215AULL, 0xCC250D187A32C36FULL, 0xF6563CA186AB4465ULL, 
            0xFD8C542F123B7BC1ULL, 0xB98E6AED057B7568ULL, 0x9F157CEA72839694ULL, 0x5B4BBB66496CA6B4ULL, 
            0x64603B93CB08E7EAULL, 0x49270C3F12C345F2ULL, 0xAE070CE9B0B1443FULL, 0xA937BE8FAADF15C3ULL, 
            0xE727445642C4C9C1ULL, 0x1C358DE952B5183DULL, 0x53FE35DBE06239BCULL, 0x2BA00A213C831AF2ULL, 
            0xF96E18DF3295B6D8ULL, 0x5B76AD3487A05765ULL, 0x430F4387D557CA32ULL, 0x976B1DEB163E990FULL, 
            0xA6B3FC9AAAD23A4CULL, 0x46B7AFA96CE63F61ULL, 0x864932607AAACDA1ULL, 0x1CE1848BEBCF5D45ULL, 
            0xC540A09CD9C482FDULL, 0x6328CC676960B050ULL, 0x9C2206A29025BC46ULL, 0xB5A932614A9DDCF7ULL
        },
        {
            0x00DE3B06CB1F3FE4ULL, 0x701C99A0765E6649ULL, 0x736598BD25EE773EULL, 0x2E743D96145AAAFEULL, 
            0xC7D04DDF49C1B257ULL, 0x8154B5C7E9605F4BULL, 0x8B93BEF5206CF62EULL, 0xA2C854034E9A2457ULL, 
            0x1DC9CECB09397ACAULL, 0xC6A720D7712B6687ULL, 0xFFFCA33B70F4F3B3ULL, 0x93C2B0CDBA4DB379ULL, 
            0x7BC0D4B8AE4FBF7AULL, 0xD84C56E89E9043BEULL, 0xB5D482ABB0CD31EDULL, 0x0450170EF010DD48ULL, 
            0xD0ED53E055F712D8ULL, 0x3BA07CB09466B51CULL, 0xD25306F47510CB8BULL, 0x91342B41C6ADEA15ULL, 
            0xAF382D75FD702E31ULL, 0x4E8F13BF80E69102ULL, 0x5AD8802645CC5C90ULL, 0x619B2444AFDDA82AULL, 
            0x0DDAC7D87861FF7EULL, 0xA94A0303130DC11FULL, 0xAA3107F8965DA9C3ULL, 0xF97866E46FBD22BBULL, 
            0x2FFC5DB147465E5AULL, 0xC4A0E25EAFCC8417ULL, 0xE227C8D5C57E4053ULL, 0x4A65C00C0873C5BDULL
        },
        {
            0x18497BE37139B40CULL, 0xABCE7DBB6047EA0EULL, 0xC72D01A263394976ULL, 0xFC554E3EC8840C36ULL, 
            0xDA6FBD07ABF15685ULL, 0xA0261CFCBCDC5EAEULL, 0x69C08CF898A84BDAULL, 0xBB7E87917ED962A6ULL, 
            0x90AE01655804C6DCULL, 0x9ADAD5DE6AFAFC3BULL, 0x988D8BF79E12277FULL, 0x0F9F17DE5CC4EDFBULL, 
            0x839FAA67F20C5721ULL, 0x1ED667208D12127AULL, 0x5668991FEB20DFFAULL, 0xD656B4A03607E93CULL, 
            0xE18B99952FFFECA7ULL, 0x2CB9C4189E799637ULL, 0x90436C753BCF3FE5ULL, 0xA2F284ED4F2E5588ULL, 
            0xA530ED3C14732A23ULL, 0x889B1F0FCFA84610ULL, 0x81D093471B6AD461ULL, 0x7558ED589E947F70ULL, 
            0x29C136AD01F8B014ULL, 0x19A8410816D53678ULL, 0xFF6B7D00B078365EULL, 0x2081C70F5B789AA3ULL, 
            0x8F41DA61B7648B53ULL, 0x3625D9AA36AEF26DULL, 0xE2B20CE3063D6E05ULL, 0x30AF84C462C0FA23ULL
        }
    },
    {
        {
            0x651D7678BE46ECB8ULL, 0x3D5FE9CEABF0EFCEULL, 0x7176E9E9992139D2ULL, 0x22DBFBAB0DD01C12ULL, 
            0x5F836D7C469DD648ULL, 0xD64BE3C71955656FULL, 0x81B702BA9CEBC99AULL, 0xFC28272B1C2A90B5ULL, 
            0xB3B2CDA4F718EA24ULL, 0x8B9EE936ABBA0490ULL, 0x72BDFA3C05424A11ULL, 0x1168368F864B0494ULL, 
            0x3D158A30DF5BEF94ULL, 0xA4CB1E927607E8B9ULL, 0x3B7515AADB05040EULL, 0x245DD283E2857AEFULL, 
            0x23D3E094EF89E9D3ULL, 0xDBFB649A1D087671ULL, 0x3CA9B8E0AF030C83ULL, 0xE7E89B7BCCE59BB2ULL, 
            0x6D663924A6966A83ULL, 0x5F7DA7F8BB1BBAF5ULL, 0x98FAF5EF21CAE0A3ULL, 0xA6E7E8FEE50F2175ULL, 
            0x4FB55DC0B247A7FBULL, 0x890E80D69CFD7069ULL, 0xEF385BA630D7B4E1ULL, 0x3C5C7C14C231D034ULL, 
            0x419CEC4D12B5A5EFULL, 0x2F2ED631DAFE7749ULL, 0x8A403F7DA248E7FAULL, 0x787CB776A3519C83ULL
        },
        {
            0xD19C45C2BADF233CULL, 0x4E7641E3D241897CULL, 0xA072AB4F3B24343EULL, 0x335214F9CB01F17EULL, 
            0xCF44C1AE8588417FULL, 0xFED342A888B5EF3CULL, 0x7CE946A6D22691A5ULL, 0x702CCB6E669F1740ULL, 
            0x1996857DA8F5EB85ULL, 0x6C3E815CC969C231ULL, 0x951B737BC29AE03EULL, 0x8A47FE8CF2315260ULL, 
            0xD63CFD38B8C64205ULL, 0x0B25467E7F380BFBULL, 0xC1DD1E7FB293C783ULL, 0x2D3AD7FEE8C88426ULL, 
            0xE098897351195BBCULL, 0x140803CF1295C5E0ULL, 0xF8FDA7A858EB5E52ULL, 0x678936009C99C9E8ULL, 
            0x45521C49B8B5CEA4ULL, 0x6549F4F5B4C0E180ULL, 0x92FEC03AB8389FF0ULL, 0x5B4D616527C9A656ULL, 
            0x42CAA357527D7C11ULL, 0x8B785C0B31427142ULL, 0x83BE495F96048484ULL, 0x22673459B3A0DE6AULL, 
            0xA27F74BB4F91F302ULL, 0x8C6B305D979A21F6ULL, 0x032261B869EDEACFULL, 0xD8EA362941D93F43ULL
        },
        {
            0x93424B8B605BF4FAULL, 0xDEA5CB7D192F69F9ULL, 0xD149ADE68596868FULL, 0x2EE055BE18453A46ULL, 
            0x9EA70C8F54A626B1ULL, 0x286A08872BCD6BC5ULL, 0x49C55F734B6A56ADULL, 0x1533B152A953DC0CULL, 
            0x4B6E6D55009EC00EULL, 0xC2BBB7E4F6B79B09ULL, 0xBFF394819306E8AAULL, 0xA2EAB57351F308CAULL, 
            0x49B105985627CDC4ULL, 0x3EBB9D6920C97910ULL, 0x2CFED3142CFD7F2BULL, 0x0ACBECDEDDE42FC7ULL, 
            0x67E0D338CBA73756ULL, 0x8ABD14C598CB0727ULL, 0xA0AAFCBFFE7E2F9FULL, 0x4DF24E5EF429D545ULL, 
            0xDF97A1E989306FECULL, 0xF2925342AC891706ULL, 0xF51B416624740DCFULL, 0x49BF52C498EDAF8CULL, 
            0xC3C714A022EB5D7CULL, 0x7562C8013B13FB47ULL, 0x802FDC04286CF546ULL, 0xAFC17010BEA15D8AULL, 
            0x76EF559A6798C44CULL, 0x4C215408FCCF3615ULL, 0x8F4FAE595879DD69ULL, 0x13EBB8F892AAB7AAULL
        },
        {
            0x91208F9DEEC9E7F2ULL, 0x69EB7E1682531BD0ULL, 0xA4E559B85494FD7FULL, 0x3A7D9CB7B60D70DAULL, 
            0x4A37B46C5DFF8AB1ULL, 0xC92EEB8E3B34D3D0ULL, 0xCF8404BA6CC5080AULL, 0x82BB68529A50BB76ULL, 
            0x648BB7D9F8822D4BULL, 0xF82294A9FA2DF5AEULL, 0x7B47E398FA03ACB1ULL, 0x465BA2901482D153ULL, 
            0x00DD4B0F777F877FULL, 0xF61B9EA9667F52F9ULL, 0x5B34C58C935E7461ULL, 0x9B38E2F3B3BC3666ULL, 
            0x33308D173A0D995BULL, 0x1AC818CA09F4A4E2ULL, 0xF5AB36ADF4EDFA92ULL, 0xE4ACF6EE5CD0129AULL, 
            0x271E291AB26D59D3ULL, 0xFB5A1ADD590A029EULL, 0xA7CE15CDAA7693E8ULL, 0x529547B1A4CFF8FCULL, 
            0x905E0A625E29781FULL, 0xC7A06515A2E86D71ULL, 0x003041B8535DF976ULL, 0xD14EA8FF8A06FEC0ULL, 
            0x72DE5B00E5D7AA87ULL, 0xD5A9F7DF1E06AF6CULL, 0x5E42E69F80FF8D8EULL, 0xFEB6564756559DE4ULL
        },
        {
            0xBBC97AD905063B39ULL, 0x48863A5CD6AB7752ULL, 0xD5CA127DAEA8BBE1ULL, 0x729CDAE0F90172F4ULL, 
            0x392F176C2CD4A077ULL, 0x9B9A06A4AA42862DULL, 0xCDC99018CC99F543ULL, 0xC7098B799BFD4F7FULL, 
            0xFD1B95D19888DD8FULL, 0x20E9E12251D50067ULL, 0x27777A7D9C63E51AULL, 0xCBB304166A939816ULL, 
            0x7338ED3077373698ULL, 0xDA9C1E9E68A3FBE6ULL, 0xE2A94CF603B0D5C8ULL, 0xA59A35DE51991787ULL, 
            0x3737649F8473E29CULL, 0x48A3728252D3D265ULL, 0xACA9ACD00FABAC9EULL, 0xAE6EA871B0634077ULL, 
            0xC416602B9516FF31ULL, 0xCDD340698E6E0CBEULL, 0x5C704AD0918E4C8DULL, 0x6361C6AA4C1E7F43ULL, 
            0x5223709D82A5BE07ULL, 0x4607DDB9959D2F82ULL, 0x04E8DA1164636A3DULL, 0x5FC83066C613DBBBULL, 
            0x8FDAC3B66C8BF8F0ULL, 0xAFB92BAE517AE6E7ULL, 0x6B941EF13EB47059ULL, 0xA86157622914D8E4ULL
        },
        {
            0x7D91022F4A7A6775ULL, 0x97CB03F25422A32BULL, 0x6ECAEF2420FC43E2ULL, 0xFF6B47AEE80C9828ULL, 
            0x193BB38169CA03BEULL, 0xADCC5DFDA9CF0C44ULL, 0x3D7660A36C202390ULL, 0xEFE7AAFA5068D525ULL, 
            0x5831EE762156A800ULL, 0xBCC012E686BD5D49ULL, 0x4938AA0EC97C407AULL, 0xD84CF689A88F55BFULL, 
            0x6C28A3BDFB52A625ULL, 0xF5A464F0B63D6BE9ULL, 0x9C697662FECF7A9FULL, 0x2FA41A892512D567ULL, 
            0xAB0BD140EDA5D71EULL, 0xBB91036FEBE272E7ULL, 0xDF4145217F7B35DAULL, 0x485D3094B1EDA8A8ULL, 
            0xBA5181C44B51C58DULL, 0x388AE97FDF396440ULL, 0x7111FE9E766A3F92ULL, 0x32742FED8B59597AULL, 
            0xCCC278C44A08DDE0ULL, 0xCF29C7C0227532A8ULL, 0x2EC1389228A2C331ULL, 0x7B050114C23B0BCDULL, 
            0x25FDF4B7392E1727ULL, 0x783F5D333BC0C60AULL, 0x8705ED62A689473EULL, 0xF858B9E51A6C18C6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseFConstants = {
    0x6BCDD14B61F26BEAULL,
    0x4194ABE20612B99BULL,
    0xF8E59ED238F91315ULL,
    0x6BCDD14B61F26BEAULL,
    0x4194ABE20612B99BULL,
    0xF8E59ED238F91315ULL,
    0x1BFBD382A7D06382ULL,
    0x54A886DCAFEA50EAULL,
    0x2D,
    0x9C,
    0x5C,
    0x7D,
    0x42,
    0x45,
    0x74,
    0x41
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseGSalts = {
    {
        {
            0x4DCB8815EAEC8831ULL, 0x579F15CAC34BBB9DULL, 0x9B380FF9D9C93D83ULL, 0x38B5EE0235E32D26ULL, 
            0x5D414237DD575F07ULL, 0xA8F32D593164CDA7ULL, 0x344E9C9A2D006F08ULL, 0x7392E85E4DA3254EULL, 
            0x861BB69DA385A6D3ULL, 0x4558558BE5ACE0BBULL, 0x6819017AAF269DC8ULL, 0x1032AE1D5E71E370ULL, 
            0x14952F07296ECD9CULL, 0xBA3026A45DE61768ULL, 0x39982F57E04BCCEAULL, 0xEA0239B0B01B9537ULL, 
            0x3357FF158CA5FDDDULL, 0xAB8BF242D344689EULL, 0x7F3E05C89433055AULL, 0x7444E16886825202ULL, 
            0x6A9A2C85831FD307ULL, 0x1C71C120327B6430ULL, 0x1712C598A718AB34ULL, 0x4DC69B80FF9F174BULL, 
            0xF7C8ADA5483238F1ULL, 0x6E6B985FFC073EADULL, 0x55DE928D25F086D5ULL, 0x6FA4D194AB2E9F87ULL, 
            0x81CD17227900951CULL, 0x594616797CBF2FBBULL, 0x9943EB044DE9B7B4ULL, 0x595009402CE68927ULL
        },
        {
            0x8A1643DD6580BFC1ULL, 0x2A09D5A31FEACFF9ULL, 0x8A3CF624EB8C5BEAULL, 0xA91A393C8689480CULL, 
            0x9F19DBC35AEA0324ULL, 0x719DBA2F9F5D8DEAULL, 0x1B4FA90F0EB5F728ULL, 0x8B046A9CD7158DE8ULL, 
            0x9243826553376FBDULL, 0xFBD85FC85EED5BEDULL, 0x61F9D090D14DEFB8ULL, 0xCF23E08CF0A65004ULL, 
            0x91B2F403E8A5E91BULL, 0x2AFA6A84991B9B4AULL, 0xC2DA3CA0F22007B8ULL, 0x7B766B76D4EF4AF8ULL, 
            0xFEB2447001B4FED3ULL, 0xB7E1967108F1EEEFULL, 0x8B25615454E0B10AULL, 0xBC5DAA13E1024F30ULL, 
            0xD47ECC7D92CBFA3AULL, 0x1E0BF1F871E6442AULL, 0x922740E1CF5C2632ULL, 0x05C473FA0AA8F7FEULL, 
            0xC913E9F16522C85AULL, 0x6B77FF734E1C4152ULL, 0xAEAC34CFFB846360ULL, 0x39439031740CC39BULL, 
            0xBC47B3CA4C2E0A4DULL, 0x078EF4797CBBEC23ULL, 0xE1BCB89EEDED0C70ULL, 0xA060C17A501C29CCULL
        },
        {
            0x7BFCBD89CB387A8FULL, 0xF6EB2A6A6291EF66ULL, 0x3ED14C18353ED84BULL, 0x34CD94C265CCDF18ULL, 
            0x1BD3F967A75D4B29ULL, 0xB4579468B8CBD507ULL, 0x4AC6E3E3B9BADF8BULL, 0x75A53EA09B6A964BULL, 
            0x60AEA547D26EE827ULL, 0x927FC6FB1AD41BAAULL, 0xFC79AE97089898D2ULL, 0x9805F35AE3B712FCULL, 
            0xBB9961AC3C00DBECULL, 0x98E4BD1DE694233BULL, 0x75E1FF3F11322633ULL, 0x7451E0A1399BABE9ULL, 
            0x69752112D70043A3ULL, 0x16B0D929C8B3E138ULL, 0xD0D91FFFBB25FD13ULL, 0x796F7A113F637E67ULL, 
            0x2FD59F3F60BD3969ULL, 0x26B05FC012B6616CULL, 0x9354D88E934C1BF0ULL, 0x1EF5A2527975DDB8ULL, 
            0x7F679E9F2BAB2379ULL, 0xF263E0B554FD1B76ULL, 0xA91C5E56BCA5707EULL, 0xF3D2EEA86A4FA626ULL, 
            0x7A91159AAC3F8C02ULL, 0x2068BC8247779EDAULL, 0xAD311274A34E98D1ULL, 0x698E153EAAA2FCF8ULL
        },
        {
            0x1A8A3D3B54FCB5F2ULL, 0xCFAD412A74667907ULL, 0xBD67FE7F943C562BULL, 0x553872A815D0CF26ULL, 
            0xC39A8E93D2B6EE7DULL, 0x62B7B8C4586247FFULL, 0x8C6981A69CC1BF32ULL, 0xD71FEAF2C985009AULL, 
            0x5338D581D7731753ULL, 0x26B26462A06FC0DBULL, 0x4659C0DBC7012E1CULL, 0xFCD8AFD4EE0005E8ULL, 
            0x893AA61757A2E973ULL, 0x384CC35B9672F477ULL, 0xEF88ECED80CD50CFULL, 0x075B028FE9B0ECE0ULL, 
            0x1FBBC4223C41D4A3ULL, 0xC4F3C8357C5BE0E8ULL, 0xF4BB814996CF59ABULL, 0x920D868672A8E55FULL, 
            0x6EB778F88448D4B5ULL, 0x9EA039978C7672BAULL, 0x1C24C974C3B5DD11ULL, 0x44A3D6645CCD4217ULL, 
            0x3E59CEE0BC8F1E74ULL, 0x8C8006D2EBC866BBULL, 0x4A22B0723FC6891CULL, 0x0BBFCEE5A8C0C247ULL, 
            0xF2C2E2123BE05A27ULL, 0xD17DF79150E6C658ULL, 0x1CB897B1E1AD6ACBULL, 0x8E1FF19CBB9D7619ULL
        },
        {
            0xC2A701121FD1074CULL, 0xE87D83AA7B5BCEDCULL, 0x03F063DC874CBF46ULL, 0x876243B68723C1BAULL, 
            0xE331DAE662DAD6DEULL, 0x88F0748091927109ULL, 0x63D38163EC7E3A0CULL, 0x658CD1DEC0009DB8ULL, 
            0xB3C87626810FA8BCULL, 0x3272CB236BDD4BBCULL, 0xB905428783E31705ULL, 0x9F8F1FC215858CBDULL, 
            0x351310D2613E0418ULL, 0xFA18F5CA15AE962CULL, 0x864F12964A94C9A3ULL, 0xE58D8EA67FD96CB2ULL, 
            0xAEE52C4289BBDE8CULL, 0x8AF7BCBA603B26A3ULL, 0x20E795A78920FCE5ULL, 0xB84F4B91B051A0BCULL, 
            0xDF9B91752CC45B3AULL, 0x5E98827CBF026614ULL, 0x51FE7C4F325DCA39ULL, 0x815D7AA983746BC5ULL, 
            0x031B8EE22BE9442FULL, 0x61C0B1B266DA4B4EULL, 0xC31BF29550DD3C79ULL, 0x84143F741F6240FFULL, 
            0xE6628AA6295345C4ULL, 0x5E9747F05A591B0CULL, 0x0955A84547ADB486ULL, 0xA06D5010CF7768E4ULL
        },
        {
            0x5399729C36F9F7F1ULL, 0x424EF24759F6BEE4ULL, 0x1BE11B076DD51580ULL, 0xB81A63359EA7921EULL, 
            0x59E48028E8C7AD89ULL, 0x8CAE1698C9569F5AULL, 0x43FFEC33FC2C806AULL, 0x08B155BB8F007C44ULL, 
            0x2FF653711DC23077ULL, 0xBB333A4568379337ULL, 0xD11B64FF315014F9ULL, 0xF2D4438A90853D1BULL, 
            0xE0A729BA80B0BBA6ULL, 0x67366A896321BAAAULL, 0x751E8EA3B32AC3BCULL, 0xC11A727D20F61783ULL, 
            0x6EBA60BA39478C1DULL, 0xF502B5B3460C70AFULL, 0x6A3941FD3FE71375ULL, 0x85C9B0E0B60E2672ULL, 
            0xE97E2BB2EDF9227AULL, 0x6587E9248333F144ULL, 0x0F2EBF5C41BD110EULL, 0xB09C2AB0C5CE06AEULL, 
            0x5012649B9D6A9CDAULL, 0x863485E9CDDCD31EULL, 0xF8234027F50FF04FULL, 0xC6A219E944F587B3ULL, 
            0x393198F66DF90AB1ULL, 0x81CF5491AB6D3199ULL, 0x0A22E686AF6D347DULL, 0xE3E57EA5D6084F8DULL
        }
    },
    {
        {
            0xC7B1210D99FB4D00ULL, 0x3697C530CCD355CEULL, 0x40EB62B66213A3E1ULL, 0x42DA6165283D88BAULL, 
            0xA5D99791781FB091ULL, 0x6CF28F814ED718F8ULL, 0x99FE9C419E5C2AF3ULL, 0xEA507FA1CF74C38EULL, 
            0x9A2E15AE0A6A3212ULL, 0x94F538CCD450E448ULL, 0xA828DA44B76E4705ULL, 0x3F73C8292AE6A5FAULL, 
            0x9197F289255C1FDAULL, 0x372264634E218001ULL, 0x035E33BC0485EA62ULL, 0x561885CBA670752CULL, 
            0x7CC9074ED5F185F7ULL, 0xACE079294C20D442ULL, 0x540ED9835B6464B6ULL, 0xBD10199EC891DE4BULL, 
            0xDD1EEA674B55A9C9ULL, 0xAF68CC4770F1CA95ULL, 0x278CF6A4C0C620C1ULL, 0xCA9F3A99CD98D564ULL, 
            0xE668B560C0E2B242ULL, 0x1F6310E8EB8F1CDAULL, 0x41E48408E5FB544FULL, 0x8248B7E3EB4E9F6CULL, 
            0xC7DBAEDB0136A775ULL, 0xF9DDFE6E77BEAB74ULL, 0x776FBEAAC770D5BCULL, 0xF91D390FD7DDB2AAULL
        },
        {
            0x642F7303FA6832DDULL, 0x1E4688430D86DDEFULL, 0xE17848F67ADD7934ULL, 0xEFCBECDB2F04FD55ULL, 
            0x8EF5BAD7185E5DCFULL, 0x636CAA7BCFD279E7ULL, 0x6EF9EC38A7033AFEULL, 0xED9FB5BBAD54CE74ULL, 
            0x8979A1E5E3DF4E75ULL, 0x4E4D73F16916D93AULL, 0xBE5E434EE0B67D5BULL, 0x4FE5F1793FD4A6C4ULL, 
            0x9B9567F75E7647D7ULL, 0x3E7E818548AC879CULL, 0xB1490A009C66D40FULL, 0x67634B9516178045ULL, 
            0x42F73DD068EB26EFULL, 0x1C29DBCAB15CE47FULL, 0x32CE9319AB0EA7B1ULL, 0x6925F5786E136FD0ULL, 
            0x10D1611605FD1DB1ULL, 0x27320E7F4318B8ADULL, 0xCEF93C5885AB792AULL, 0xCED27FE9307BF696ULL, 
            0x0C794928FF442D29ULL, 0xABAE7727817B2C68ULL, 0xACDF3E18156BCDA3ULL, 0xA56FD6612A961421ULL, 
            0xCCE4D51FA9832A79ULL, 0x4EED00F4E0CDA515ULL, 0x2DBC6633343457C7ULL, 0x0217F5F8A15B921AULL
        },
        {
            0xD8BD5FC057C7AC3DULL, 0xA7EA91AFCB7B27F9ULL, 0x741E55D54E603171ULL, 0x46F78A148FB30B6FULL, 
            0xC2EBB2560EDE4097ULL, 0xC5157B1C33FAF309ULL, 0xA6613D81F717F66BULL, 0xE0B721B0FC0107B9ULL, 
            0x99839BEBF5779518ULL, 0x5411037B8FDA5D8BULL, 0x8D766D08FA4E5624ULL, 0x0E2AA20AF32AC266ULL, 
            0xF0CEB1FE618C524DULL, 0x8A38D8C317906650ULL, 0x5C3CF4FEE0F015CFULL, 0x8AE3F48731FCF564ULL, 
            0x7DDE5A22747D6F39ULL, 0x1002AF4743FF88CFULL, 0xA9D610EEFE99ED64ULL, 0xFD9E59D1D829A13DULL, 
            0x5E1B03854DC5E6BDULL, 0xBD480B7787CC1925ULL, 0xA0D1F82F82BD5A7FULL, 0x7636C6C09BB0AB0BULL, 
            0x02D1B3FEAE403895ULL, 0xC9DDE7B6D6F81685ULL, 0xD2CF1B0136818E9CULL, 0x7651F745F78EC756ULL, 
            0x98D403942FBE5858ULL, 0xC2FB256CA6607BDDULL, 0x0AD40F624591A87CULL, 0x76F89EA23E8554ADULL
        },
        {
            0x48A860FEA3A0EC27ULL, 0x139700B5634DD3BFULL, 0x6A544A685937B09AULL, 0x3144512A560D5ACEULL, 
            0xDED7973014D3DD13ULL, 0x47424A0C0D0B4D6AULL, 0xB0B96457D36E45CCULL, 0x0E34F9BEEA3DDB86ULL, 
            0xBCFFAD7A0422820FULL, 0xF75A606EB0C90E5EULL, 0x786A531067DAB237ULL, 0xC3AA0ED817EBB199ULL, 
            0x286180DE98AA729EULL, 0xB35B2284CB747080ULL, 0x551D4B0ABE0BAA33ULL, 0x3C0B053F6C316330ULL, 
            0x2FB5E0705C232530ULL, 0x5CC72A2941F864EDULL, 0x38F675A75C03E327ULL, 0x4D0FABBCB5B189ADULL, 
            0x35B36275CD3BE35BULL, 0xE70A02B1CB92329EULL, 0xA04D098BA1E4175EULL, 0x1B57236F190DCB24ULL, 
            0x58362FD30D0371A7ULL, 0x50E59B6250473902ULL, 0x31DA87AC7CECD8BEULL, 0x27A68F827CD4BE93ULL, 
            0xA08B016F96491097ULL, 0x94F7A627E7729DC3ULL, 0xD24C8EC943674775ULL, 0xA05555F9920E7109ULL
        },
        {
            0x902D4E429E01D510ULL, 0x32BAA02B9C3AB4C3ULL, 0xB300908D080444C5ULL, 0xA3B688316B41EBB5ULL, 
            0xE176AEC805765FE0ULL, 0x45C83FD4D0363E84ULL, 0xE6BBB1380EEF43FDULL, 0x4291CAB11D46637EULL, 
            0x73603558D758D4C0ULL, 0x665097369DA01FFEULL, 0xDDFD46DD9C7D9415ULL, 0x950980CDFA9C0417ULL, 
            0x6927EDB0586F521AULL, 0x4CA18911A689785BULL, 0x44EA170817D1AE79ULL, 0x5F1ED6DCC5D5EBFCULL, 
            0x3DB2284512857B17ULL, 0xBB10FC217705B59EULL, 0xDB0D00B3F944B463ULL, 0x3B4893B89E15B74AULL, 
            0x3B7ED117CD236684ULL, 0x3E64498EA66CEC02ULL, 0x9B662C1401BBF475ULL, 0x7BD813F9C539E6F8ULL, 
            0xD70836239773EC5EULL, 0x887600F59F716AB1ULL, 0xA421DE3964E374EBULL, 0x1DB16BCE11A87897ULL, 
            0x46CFD435894EA3DEULL, 0xA6ADE15825551890ULL, 0xD45ADE165D9937D6ULL, 0x4365EA61CFFF9F2BULL
        },
        {
            0x38E02FF3BBE86CA6ULL, 0x27395559559A7ED2ULL, 0x93A4721053478186ULL, 0x3E7B6A2928E215C0ULL, 
            0x95CCB72E35FB75EAULL, 0xDD479B4A6D585DD0ULL, 0x2E05120CBE3FD20EULL, 0x7F521D3CEA8EFB7BULL, 
            0xD5E21EF191325EA2ULL, 0x9B63F13A0FDF9EA8ULL, 0xDD464E765D1A5EE5ULL, 0x596EA99D5F73C215ULL, 
            0x5261844A5555A432ULL, 0x82418CEB2BB55C6FULL, 0xA125531BE86EE3E2ULL, 0xD2ED01CC08FDF881ULL, 
            0xA634CE11AC776CE2ULL, 0xF6F2DB99B8A3344AULL, 0xC03B8E65BF7D7C6FULL, 0xD629AB05E06EA85BULL, 
            0x8DF349741B00386BULL, 0xBB7A9C42D8247EF9ULL, 0x6D2D474165E44827ULL, 0xF7BB7ED903129588ULL, 
            0xE8B99706CE14980AULL, 0xC682F4B46AA19DE5ULL, 0x2AB23EF9B6699A43ULL, 0x65762FFC73F67FD5ULL, 
            0xE88C0BC204CBA3A0ULL, 0x8C801EAEFDFF79F8ULL, 0x2D16FFA14D930EFEULL, 0x7B4D43E5FAC87B05ULL
        }
    },
    {
        {
            0x151DDD0893C5C0C7ULL, 0xF9D4016484BB6133ULL, 0xC5E63F7659BF489DULL, 0x1A83272A06412A1EULL, 
            0x1F5F1F6AB338364DULL, 0x86C3DA3E5EE8E212ULL, 0x670CE76214998400ULL, 0xC46FFCE0B0432B37ULL, 
            0x7DF47A012BCF1663ULL, 0x0047357CF95AB224ULL, 0xC3A0C5D5FC654D48ULL, 0x71A1DE48380D64FAULL, 
            0x70110BA398C5FAA7ULL, 0xE160BA10B3E59041ULL, 0xD992C44712840E3EULL, 0xD1E5A0EBBFA75F0FULL, 
            0x782CB6F042573A29ULL, 0x80B23E849306ACEFULL, 0x0180860C2058FE3FULL, 0x60BCB2B5AB3B12ABULL, 
            0x8B5D1A5B4009B975ULL, 0x919DAA6E887B9265ULL, 0x1B5293F3C5BC4738ULL, 0xCF7A7E5C544D5318ULL, 
            0x377892E6769EB544ULL, 0xA922302B318E8941ULL, 0x14591A3271D11F7FULL, 0x381EF78AFEB355E5ULL, 
            0x6F1AA6D3B85F7FC2ULL, 0x774313CE73ABA4ACULL, 0x1B1D133AED8D2F34ULL, 0x382EC2CC41042C6CULL
        },
        {
            0xE769577C776D1467ULL, 0x0824BBC7744256A3ULL, 0xA4B578F7295688AAULL, 0x2B0BE74BCEF396A6ULL, 
            0x8F4F91BFC7CEF454ULL, 0xA232760DF9722DFAULL, 0x260CD125448BE74EULL, 0x1BAEC614BC2A04A9ULL, 
            0x5C777A28F4385D06ULL, 0xEF62C7D5275B6EADULL, 0xBEBBE3D3F9B57D68ULL, 0x78B706F18DE9C2ADULL, 
            0xC5531421CE1E723EULL, 0x43B6E7CC67542102ULL, 0xE7966AB14C6C3DC5ULL, 0xE5EB1DD9FCAA0FB5ULL, 
            0xF87C533CD5D0D54FULL, 0xF6ECE929B126092EULL, 0xD464BBDEBF4B22A8ULL, 0x560EF4EADD9306D2ULL, 
            0x9547D6435F4F1466ULL, 0x611B33ACBE92F5C0ULL, 0x64EBBDAADE824183ULL, 0x9AB4763762EF88ADULL, 
            0x100BBDE3C70C7FBAULL, 0xE27359009B9E06A4ULL, 0xE8EC92997E82E006ULL, 0x642E1D9DE3D53694ULL, 
            0x9C1A9353865400C6ULL, 0xB46843B6B10CCB04ULL, 0x0316F2997E4657E8ULL, 0xB5A11A1DF90652DDULL
        },
        {
            0x61AFC63631A83AF3ULL, 0xA6A60F43E6F19C40ULL, 0x14A5EBD77ED9B285ULL, 0x6331CCDD7F8B5F4EULL, 
            0xEA43F06CCF85196EULL, 0x77C93E2622ED04AEULL, 0xD0FD7C2C2A352EE6ULL, 0xDF922072F75D5836ULL, 
            0xCBC6715B0514E9D4ULL, 0x23066A1A835B0EADULL, 0xBB273653EFD0BC27ULL, 0xCC7448D48C4F6A87ULL, 
            0x5968A363711F943CULL, 0xEFFBC2D2A25AB915ULL, 0x1ABEC2227306AD25ULL, 0x9CFD1165362EBE10ULL, 
            0x02304AFF7516BF02ULL, 0x694FF98E96F08C8FULL, 0xB6715A4462214C13ULL, 0x291D02E9C571C6E9ULL, 
            0x914A51EEADC31447ULL, 0x155D4717FB9CCF97ULL, 0x0B983B45CE01ACC5ULL, 0x6ECCC0C6C7F4EEADULL, 
            0x051C38CD7C4AE75AULL, 0x3E3527E310E823E3ULL, 0x2A94C90EA0431D5DULL, 0x4D793FD5BDA32B16ULL, 
            0x6D98E6A8296C90B8ULL, 0x23BB93871A28F206ULL, 0x8EF8FE83E9D25BA8ULL, 0xF571C058CE9A7E02ULL
        },
        {
            0x183CF26EF1429C1AULL, 0x1F0C7A1E33DB5395ULL, 0xCFAF0D96724015ABULL, 0x9A3A76B865742165ULL, 
            0xD51E0AEE7FEF5DE0ULL, 0x3B63F852F9B2F983ULL, 0xF54C4AF1876750AFULL, 0xA6ABB02D233A1EDEULL, 
            0x2E192B09E1E115F1ULL, 0x4FC52E878FC6EB5BULL, 0xA8C9A8C249B9BC0DULL, 0x641FA49AF0A454C5ULL, 
            0x36F172CE9A1E5180ULL, 0xE78F017EBEC048AAULL, 0xEACA0072D0A27616ULL, 0x1EFEE88BF407E96FULL, 
            0x4281EC1D744A2770ULL, 0x696F1565F580F770ULL, 0xC0BC1F5F1F407054ULL, 0xB7FB7A884E044000ULL, 
            0x008F4E02F97BE544ULL, 0xD6B0974B35560636ULL, 0x3CA2BA172AC611C5ULL, 0xC06D3BA8BDEFB4F4ULL, 
            0x61E786E2816B3B13ULL, 0x6463DFEFFF38E230ULL, 0xFCCE5930C8E5B032ULL, 0xF29953CE067391D7ULL, 
            0xDB3D66FFE7389C57ULL, 0xC32B69A979F6429DULL, 0xD9F5664C2B5A331EULL, 0x318207D197697FB1ULL
        },
        {
            0xB78A6C1F3FDB64A3ULL, 0x66D08618B804AA13ULL, 0x38B6BE2398FBDDBEULL, 0xD57832A5513D3C86ULL, 
            0xBC150028F1363FEFULL, 0xC2376D8F8706F744ULL, 0x695E47129D7E913FULL, 0xEDB795C9213ED7B2ULL, 
            0x4F3DF1E9C8AC67FEULL, 0x001D68C2D9AA0FE7ULL, 0x70680D44CF6BFDCCULL, 0x454918F1E89BD388ULL, 
            0xD8B3D96BB104298DULL, 0xE57374A8B3177500ULL, 0xD8D6D5AB7FB2CF8FULL, 0x7386D6F0EB0242A0ULL, 
            0xC1921A19646E3BAAULL, 0x90C71F229632AAA3ULL, 0xF006BA7B629A626CULL, 0x1B06F13ACA71E768ULL, 
            0xE504BE353CD672DEULL, 0xF36C0B9278F08FAEULL, 0x509C3E34AAB31F61ULL, 0xA546D8B03B19CA1EULL, 
            0xC80E08F1A4C4DD07ULL, 0xABFAC82CE408025DULL, 0x97ED7E916483ACA3ULL, 0xE59F7BD04CF111D9ULL, 
            0x575A3A3C74FCB858ULL, 0x69E9517C2B15693BULL, 0x3AD49174F2075BFDULL, 0xC33C85D8330A1461ULL
        },
        {
            0x941A7B561B96DEABULL, 0xFD595F82FF8B4036ULL, 0x1786C77F6E87DDDDULL, 0x399A9C5FD2B157C7ULL, 
            0x900E065AAE342EF4ULL, 0x0915790E4CFD474AULL, 0xC6888C99B1898C0CULL, 0x089D309572F6E204ULL, 
            0x3887ECFA83719D01ULL, 0xD9047CDD68E54213ULL, 0x91F59DC088E5BEA7ULL, 0x7880C0189943F6BCULL, 
            0x4883607E0EA43F3DULL, 0x0CCDD5C0C1EB6AE2ULL, 0x22E3AA9C62C8EFEAULL, 0x0D9E88A0FA27DA57ULL, 
            0xF3D75B57B961D7F6ULL, 0x9AF3D3627CD3E0B1ULL, 0x31A17BA00FA7A1E9ULL, 0x11DEC941F44F8FABULL, 
            0xB289081D7DCE3D40ULL, 0x34ABDC13C72E08B8ULL, 0xD194505E1975F0BEULL, 0x01113AE5DE3651E6ULL, 
            0x8CD2A124180D31E1ULL, 0x50B321B8D1B396E7ULL, 0x7FB8B428B5AE3A2EULL, 0xBD05302E9255B9E0ULL, 
            0xCAF7DE1EDF2E8877ULL, 0x58D086C86B744AB0ULL, 0x602066B6DAC14D9AULL, 0xEDD1AA9BCF9F6D5CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseGConstants = {
    0x010F7B96C77F49A7ULL,
    0xB1FFD42E36BA7586ULL,
    0xACDB0D2E6A88D6F0ULL,
    0x010F7B96C77F49A7ULL,
    0xB1FFD42E36BA7586ULL,
    0xACDB0D2E6A88D6F0ULL,
    0x4D6489479D90387FULL,
    0x54A6A67BBB69D3DCULL,
    0x43,
    0xC9,
    0x84,
    0xC8,
    0xB9,
    0xC1,
    0x7A,
    0x73
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseHSalts = {
    {
        {
            0x6766EBB781A4F03CULL, 0xCDC0CF4E93C4AB9CULL, 0xFE20BC2D13E2D5B0ULL, 0x2E39143DFD7DFCA1ULL, 
            0x06977004A77A3969ULL, 0x9BF2ECFC18CEDED4ULL, 0x5FA259A9D9D030DEULL, 0xA2E41FFBAC74E571ULL, 
            0x57D4B10F873E108CULL, 0x5E23288B5CAFEDE6ULL, 0x8136049C817D34E0ULL, 0xC45F373BB7D26729ULL, 
            0x7ECB5A56CFC4AC16ULL, 0xB432AA2C686DCC3FULL, 0x5A5E6CC2708FD80CULL, 0x110971E9BE13506EULL, 
            0x965B43EEE8BFEDCCULL, 0x5A5BC018E4D05096ULL, 0xBD7367A42B9F4B65ULL, 0x15922FE38540D07EULL, 
            0x0CC387E8BA40E7B3ULL, 0xD60CDA3253CEAFA4ULL, 0xA3F4CA76F426B7D6ULL, 0x7CCEFA80A20CFC3AULL, 
            0xBE89DB646A44F83FULL, 0x7D2AB1AE4100C095ULL, 0xAF9AF2CBC383CDC1ULL, 0xF2CF6464389AD09BULL, 
            0xFA51BA4115864CCDULL, 0xF845EAC0B78D5A8EULL, 0x5EF5C43E54FE7180ULL, 0xF6A5C8C69A3591C1ULL
        },
        {
            0x9777C04621ACA987ULL, 0x8E402E43D6DA67A0ULL, 0x5B19D814B7CD053CULL, 0x93E8BD82A66F9FB4ULL, 
            0x1492DFFC2DBCD765ULL, 0x3132A0C80EF5915CULL, 0x3157C01CD296C62DULL, 0x3560F47A41A4175CULL, 
            0xB64DC4F850E7B2D0ULL, 0x0572DC714DAB56B0ULL, 0x75648E8640323798ULL, 0x9204FD373D08BF3FULL, 
            0x65F16D5BAAA478E8ULL, 0xF0FFD58362A098C4ULL, 0x48C9FEAF347C8F53ULL, 0x0D647F5E64CEE958ULL, 
            0xE210C86480298A2CULL, 0x684EA2F2F08093BAULL, 0x5370FD7E7ABC8569ULL, 0x790052C642F30244ULL, 
            0x24059F283F3CC0AFULL, 0x1C716C46BDDE656EULL, 0xB6490C39862B6D88ULL, 0xA277A048D9A1873FULL, 
            0xCFE59CB76C139BA5ULL, 0x6279E5F269551B52ULL, 0x2F11B203AFC3C4FBULL, 0x3ABACFA7E656A1F4ULL, 
            0xF2D8329C5A98BB7CULL, 0xD1FC1AA5A2F0A464ULL, 0x2550134DCD8AFDA7ULL, 0x88D666EDE83B33C0ULL
        },
        {
            0x435AEA767883286DULL, 0xB27547EC9E4FC77EULL, 0xC3A187C7CF45A698ULL, 0x45F058EF5DC09116ULL, 
            0xAD426A07D4F57E9AULL, 0xAE753017D7323266ULL, 0x2BDC1CFBD83B593EULL, 0x4920954516F8D0D4ULL, 
            0x18624DF7C8AE6399ULL, 0x652CA87A62360F5AULL, 0x6548B3A051C2EF5AULL, 0x804344190DB49714ULL, 
            0x9BD77505752C9A81ULL, 0x34DC1D70108E32D5ULL, 0xAFA744F92EA793F5ULL, 0x12FC3244DE5C5318ULL, 
            0x5FC7E0523716C669ULL, 0xCC3EA15A30559CD8ULL, 0xB59AA3286AF1C2C3ULL, 0x2D4C2C3DA719EDD1ULL, 
            0xB60213AB305730B5ULL, 0x5A6ED51EF171096FULL, 0x3AA9A85AECDD1AC4ULL, 0x53DC39BF9E911912ULL, 
            0x3FC8C7A682292AF6ULL, 0x7A2B02A534B2E6B8ULL, 0x67A5FBA28153C694ULL, 0xBE321522965E4BFBULL, 
            0x39656CAE4BED90E3ULL, 0x71BFFC6BB0D31849ULL, 0x2AC1003F3BDD7679ULL, 0x3AD2D748D00F0E98ULL
        },
        {
            0xCC41E78CE8F9A83FULL, 0xCEE0A9230662A37BULL, 0x327F1C4828630891ULL, 0x5EEC67B4581CFED2ULL, 
            0xC738F4FDD6B42C67ULL, 0xAF58344433848BCDULL, 0x3F8BCD374B1E9C75ULL, 0xAA42D447F639C130ULL, 
            0x9DAD6160D51ACB70ULL, 0xCF0708432731535DULL, 0x2C2FDD4A68872F9FULL, 0xAD9220A5AEC09064ULL, 
            0x79D15DED0A3D9F5DULL, 0x7B18B5BD13248893ULL, 0xF773AC9A80DEF2F8ULL, 0xC31FD9541EB3EEFDULL, 
            0xA6FF8BC6DDEC7F2EULL, 0xD3254D901FBA0A95ULL, 0x8AD9E9FFEC6576F4ULL, 0xEDA5102E089AE999ULL, 
            0xF3AF57353BCB7372ULL, 0xFA51C44CDFE928FAULL, 0xE6B97948BFB0C035ULL, 0x091AE36230AFA501ULL, 
            0xF0532D47B8DCA2F0ULL, 0xD5A31704D4F5AAC1ULL, 0xF31D18C4D3D98707ULL, 0x636C561A73CF4388ULL, 
            0xEBAF330E19DEF4F1ULL, 0xCBECC113B1A48E91ULL, 0x9E5AF1BFFB58CAC5ULL, 0xCD7DFC4E595279D6ULL
        },
        {
            0xEEF63FA8F401D622ULL, 0x91DA0BEF706BA221ULL, 0xCDE571EB7E78F4CBULL, 0x0B60507C7AE2DC10ULL, 
            0xEFB025832D933121ULL, 0x54D875763637D9E6ULL, 0x8123952B218352EFULL, 0xCC47F1AA8B3ABF60ULL, 
            0x6356E772E6445BD1ULL, 0x4D277116600D5C7DULL, 0x938A003C12F5CEB5ULL, 0x27E6C1EB7E69C4B4ULL, 
            0x24114E436D9ACD4CULL, 0x342AE9FB25B6D7BAULL, 0xAE83FE03E759FE65ULL, 0x242E0D7963788705ULL, 
            0xC03520A3A3F5E0FAULL, 0x01D5F47C7023605BULL, 0xEC04C367AC374AB3ULL, 0x9001CEB72201857FULL, 
            0x22E1E6F586366F88ULL, 0x16FC9D8A6E700EB3ULL, 0x6FCE67AE41A6AB69ULL, 0x02C69E943AF9C38EULL, 
            0xF164635B8D34B7C8ULL, 0xD4FAC9B9EE7BC408ULL, 0x4B4A12AD54A2F400ULL, 0xB404F9F36E8B2C63ULL, 
            0xA5623379F7C5F8E1ULL, 0x62A5A89AAD134DF2ULL, 0x0269EAE4FAFDA1D6ULL, 0xB4E40EC2C5BE6C6CULL
        },
        {
            0xE9C23D1430B94C4AULL, 0xE4A0AD2DB2FE6509ULL, 0xA59FE55BB5BD0554ULL, 0x63D192B7B098293DULL, 
            0xCFF5719B5F2EA3B4ULL, 0x86816BC89B3129FBULL, 0xABBE5C048AA64A15ULL, 0x924E31D51FEB5627ULL, 
            0x612DCC1E29BE78D1ULL, 0x912C76CA313146D6ULL, 0x8B815759CAC98CD3ULL, 0xD078ADFBD8E13A77ULL, 
            0xE052E1A56D410059ULL, 0x6E46B1E721A7F70FULL, 0x6E5D4D3820B37BF5ULL, 0xFB0CEC9AE4D1B9E9ULL, 
            0x3889D21BCFDDF77CULL, 0xFB6145F3C6B62794ULL, 0xB17291F74CE21460ULL, 0xC5B4CEB5576A8FCAULL, 
            0xB7EB914B05D80CB9ULL, 0x9BCEC10E0A1BC8E7ULL, 0x9A671007489CCCECULL, 0x605B1F5EAB27D194ULL, 
            0x5798DBFEC804C0C4ULL, 0x35E05907FB503EAAULL, 0x6BE2FF90DFFECB06ULL, 0x8AB7416CB5F5D39EULL, 
            0xA0158D81E11FFE6CULL, 0x37B08BC945411A03ULL, 0xC3D102BB2FF871F4ULL, 0x9C837157B45C29D1ULL
        }
    },
    {
        {
            0x96EAF33047E3FC3FULL, 0xBE1C93A934E9B8CFULL, 0x33E00AB724E6A187ULL, 0x5CAD7E2845ACDC5DULL, 
            0x9930B01C35EBD8E1ULL, 0x80C6B42C8C45B557ULL, 0xE5B50AB2B1F72B64ULL, 0x5E68FDD2C595E7B0ULL, 
            0x2D4625EC626732B2ULL, 0x114A37D0EA954133ULL, 0xB6FADAB68214FAC9ULL, 0xADAE7505466CF0F5ULL, 
            0xF9C590D38B8AC761ULL, 0x4E6BA74265D886DFULL, 0x6C4340242D9947F8ULL, 0x75133F110611E6A6ULL, 
            0x637D5672C40395B6ULL, 0x4D559F8EA2031922ULL, 0x0E1B458A3D5A6954ULL, 0x599F38E3C537A409ULL, 
            0xE6A2366553390789ULL, 0xBC5B33173E9E8691ULL, 0x6F31D39133943685ULL, 0x9B396023E1D2C71CULL, 
            0xA9BF156F549C85FDULL, 0x6A1770378F4AFB86ULL, 0xE6DFC7582CCE4AC6ULL, 0x6A17E22169241FBAULL, 
            0x6C0433D4CE586FC9ULL, 0xDFE532EB5D071112ULL, 0x3CDE5E54A201CBA7ULL, 0xC0982CF7F85D0703ULL
        },
        {
            0xA7D77A2280CF6998ULL, 0xB6B2535A78A94C3AULL, 0x63264371CF4A7013ULL, 0x831406EFFEFD5ECFULL, 
            0x7B5F3666A834D6AEULL, 0x06C63AC8E683F721ULL, 0x41429F13EFC25E96ULL, 0x65BA8CFCF8EA42FDULL, 
            0xC7F03C286688B29FULL, 0x7E3498FB2FB3EED2ULL, 0xAF68A78633E55BB0ULL, 0x4F14B2EAF14FED9EULL, 
            0xA46075E236761B4FULL, 0x068D1415BE81A0CCULL, 0xFB8A7B8C9CE84E8BULL, 0x275124E6195BAF6BULL, 
            0x4BE7246829F10894ULL, 0x55025C2DB50FC658ULL, 0xCFA53BFA1806D218ULL, 0x9967D8509CEDE40BULL, 
            0x22E9672AB02551BBULL, 0x9777592BB25096E9ULL, 0x1A8F214AE725564CULL, 0x795768A6F69EBAC9ULL, 
            0x16593BB6102A968BULL, 0xDFB8FB229B984122ULL, 0xA104BED3DCF31118ULL, 0x3C828AD35E2CF5F0ULL, 
            0x89189CC8FF03EF10ULL, 0xD961EDCD364719CFULL, 0xDAA43E54EA2F8D5AULL, 0x2C626B2946E1DC4DULL
        },
        {
            0x00A4BD3D0E69D807ULL, 0xCC1B217320032358ULL, 0x813C993B51ECA6A4ULL, 0xD4B9667D5A3E4E56ULL, 
            0xFD4C55957572C334ULL, 0x01173B95A5BD3336ULL, 0xFC8A279C324C87A4ULL, 0xD7E8BBB16BDF7843ULL, 
            0x60E1532218899D7FULL, 0x02CDBB1512BB00DBULL, 0xC3ABB4342C2C90DEULL, 0xC0A71C96DEB7284FULL, 
            0xF79CC687DD57C537ULL, 0x4E5E9ABE2AA01D27ULL, 0xBDF0E70CE146FE0FULL, 0x2A8B6DAF72359958ULL, 
            0xBDC3459BBFB0AF37ULL, 0x16802BA0AC36507AULL, 0xE93BD65CF76AD0A2ULL, 0x797C47E9873E2059ULL, 
            0x8D9778E21F399DA7ULL, 0x07A4A6FCF9E50DC9ULL, 0x43BF8CB0087BE915ULL, 0x5EC83C64832527D0ULL, 
            0x0EDF1CCAF89F6256ULL, 0x171D00E0BCBA2DE3ULL, 0x8949EDA2CEDCD2FBULL, 0xD64BB61A2EC7EFD8ULL, 
            0x50779ECF6338E95EULL, 0x2449A4D2E53F5C06ULL, 0xF788D45B58396E8DULL, 0x8AC2E0B7CC3CD84AULL
        },
        {
            0xD05FAB7B58196CF0ULL, 0x0544C95299B38C1CULL, 0x7BEDFB49BA6A730EULL, 0xBDB95D82784A7F5DULL, 
            0x4A9D22D62A450B2CULL, 0x5141E33E3A499910ULL, 0x57D3A1733246339CULL, 0x0D6BD19FBA7E8B45ULL, 
            0x9101F5BDAD2DD290ULL, 0x55405EA7D88D535FULL, 0x4DF257818C1E7746ULL, 0x1589FEAB7D6529C5ULL, 
            0x5E9D7D67B9AF946FULL, 0xB2C1C920B37540D6ULL, 0xD1879A3228270C6AULL, 0x3A00B49BD64C4665ULL, 
            0x11CB998BA6F7036BULL, 0xBBEF23E428C094ADULL, 0x15996B25AC1007D1ULL, 0x85CF38F1F3AC0699ULL, 
            0x13E89F889C5BAB63ULL, 0x73D4F697444B8275ULL, 0x77A55F3FE2D2C8DEULL, 0xA39CBBA3183632C1ULL, 
            0x4F74EA5ADB28DEEEULL, 0x823D062C9686F874ULL, 0x4CB6C995BFFEFEAAULL, 0x3277E16E82093324ULL, 
            0xBE6CE988BA05C769ULL, 0xA76B9DFED986427FULL, 0x6E3DC88AA88C4670ULL, 0xD0BAEF49EA2F0E56ULL
        },
        {
            0x7405604A1F176F83ULL, 0xBAB99F7A24C157C0ULL, 0x0F937B00460C992DULL, 0x715F7047EA69BE15ULL, 
            0x8C335CE933563D64ULL, 0x3EC7B4568FB74C8BULL, 0x78ED0B32AB58C373ULL, 0xE32ACD625E9A7070ULL, 
            0x4B43C9F6D93FB017ULL, 0x151EAC8FC7E381DAULL, 0xA992C7C730C0C83CULL, 0xACB396FDBAEEC891ULL, 
            0x07CE711CB589C966ULL, 0x69F7D910E967690EULL, 0x2D0803B65F449401ULL, 0xD03F91CBF227281DULL, 
            0xC8AC938A22AEE456ULL, 0xA92A95CCDAB461E1ULL, 0x0758AE666600D9C4ULL, 0x6FC4AE864E132A09ULL, 
            0xA49128B4345DAA6FULL, 0xE617B05E963606B2ULL, 0xD1CA57C33BFC8BA2ULL, 0x392A1AA6A4A66C08ULL, 
            0x04D8E50087D50718ULL, 0xD2052919E26AC699ULL, 0xC41C2997CE34136CULL, 0x2A4E1EAC4A0AF334ULL, 
            0x7F7EDAAF754B006AULL, 0xFB38F9CCDA1BC750ULL, 0xBC7F9652C844033AULL, 0x3FF4C57F4962D512ULL
        },
        {
            0xA0F21B29A4B20C58ULL, 0x97AE0A59286BAA3DULL, 0x54C7D8FF8527A067ULL, 0xC351D6C8C2582243ULL, 
            0xFCC6D68EA1824092ULL, 0x0A5342EFA5687E50ULL, 0x0BE661FF2F6F6F86ULL, 0x3681B3C95A8925F1ULL, 
            0x812119DB4B56EA8CULL, 0xD644A06A08331799ULL, 0xE268FB60331D834BULL, 0x49CF863F89FE777AULL, 
            0xC3E8E056DE3E3EDCULL, 0xAA46011996608A1BULL, 0x249DE1CD62DC130AULL, 0x501E57BB03F7630EULL, 
            0xF901621740E2E8DFULL, 0x450755DA88F48769ULL, 0x66EF256A61647F53ULL, 0xE40DB23D314C10F2ULL, 
            0x5C2785CFD59BF01CULL, 0x329FD949DF687EDDULL, 0xF1269977EF8FCB89ULL, 0xD1DE8F0154DC8F9FULL, 
            0xBAF5E4DF4FDE2F92ULL, 0x91942629CBD9C9C3ULL, 0xE3146032B51AEC0EULL, 0xCF5E151ED48C2F18ULL, 
            0xD38B8E6A992B4AAFULL, 0xC3B663755ABF83B7ULL, 0x0D0A4AA6A5212B00ULL, 0xCE649A84B752748FULL
        }
    },
    {
        {
            0xED2FABCC670C8820ULL, 0x11FA7FA08C7B940BULL, 0x02184AB6A00BBA80ULL, 0x3F44C20F841167CEULL, 
            0xEF825FCABD653047ULL, 0xE2D5D378F8963DBFULL, 0xBBFDD7215410EC8EULL, 0x5F200201671DB76BULL, 
            0xB1014C33FFA01E0AULL, 0x1CC086326BAC3BF5ULL, 0x6E97FC12A0021E03ULL, 0xB741B1F07833C615ULL, 
            0x4BA2C44F90E3F02FULL, 0xE81EB18738FDC2E6ULL, 0x862CB877E6310D33ULL, 0x7D56F6E5152B8C49ULL, 
            0x7A14EF9BFE050EF2ULL, 0xC5405B7DE146DB0CULL, 0x833185E7D50C6DAEULL, 0x2A63B5F38901EB48ULL, 
            0x7AF276A74EB63BD4ULL, 0x7C1E39E8F336AADBULL, 0xBA15C5FED028CA2FULL, 0xCEFFD05D1007D24BULL, 
            0x7B659AA4B53E1E26ULL, 0xEBF91520354B2E45ULL, 0x4A17A664EAEC42CDULL, 0x50994B2332779EBFULL, 
            0x3D8A12CA971F854EULL, 0xBC8BDBB1820518DDULL, 0x20D160D93C423DA1ULL, 0x82B2BA9A4D09358CULL
        },
        {
            0x93A903EB7AA5747FULL, 0x16DF44A2E40F3C1DULL, 0xD670D546E65A5692ULL, 0xEA421BF8E398A4BDULL, 
            0x392AE0C0788AAA7FULL, 0x44799FB892386083ULL, 0xF59C8D09531975F1ULL, 0x8F73744018B568FDULL, 
            0xCFF617E5811E3FA3ULL, 0xE6F4A49A0981CAF3ULL, 0x64212CB29BF1B203ULL, 0x8A51C298F685725EULL, 
            0x26EFC3727437EC58ULL, 0x87B2E145D30A2290ULL, 0x27FD6FACA387EAABULL, 0xC94BB7C99D1036B7ULL, 
            0x3D40B9CDCBB730E9ULL, 0xF5502CC8769C3B5FULL, 0x6D8A45EC75049AFDULL, 0x30F483327AFB31B0ULL, 
            0xE82C6FED0B04BCEFULL, 0x13C33EA920E58876ULL, 0x852853E6B8B79BDBULL, 0x77E66A82791480DEULL, 
            0xCF0D43E9CD8D3F1AULL, 0xBD4F79EF44721B57ULL, 0x3F4A3165F51D05F7ULL, 0x1348760D9D0F7FC4ULL, 
            0x847D7FB00E4528D0ULL, 0x9D5099C4D7074749ULL, 0x6B941AC68B3C9EFEULL, 0x838B84193D1AD95EULL
        },
        {
            0x8CCA0BFAEA180CD5ULL, 0x670CF513EFDB4A5DULL, 0xC7D1DC06518E53B3ULL, 0xDF8E11F64219B493ULL, 
            0xD91141A7EC21BD96ULL, 0x5BF819565E68D351ULL, 0x997FC1FDC4777DC3ULL, 0x312979E7AF033856ULL, 
            0x4D4732CE923001CCULL, 0x6A7D4AF32C99E34DULL, 0x9A23CD87745FC92AULL, 0x0FFA24DA58660347ULL, 
            0xF40355455CD16D8DULL, 0x88DE555736F148E5ULL, 0x0586551CE8B684A6ULL, 0x6123E06B2EF2E94EULL, 
            0x3DFC5AA317F3201EULL, 0x02EEF7CD01847792ULL, 0xFF69996CD835A95EULL, 0xCAE0E70B8625BDE1ULL, 
            0xF16DF2B68D37D866ULL, 0xADD2A4DBECB7D536ULL, 0xA7934BA9355418A2ULL, 0xFC29A614AEB4A5A0ULL, 
            0x134CA52485836509ULL, 0x85958D80A6ED2D98ULL, 0xF4A4EBAB791D1D30ULL, 0x9D78AD3827C9659FULL, 
            0xBDDD3BDAA7115DC1ULL, 0x0F4581B8D8A6D6C5ULL, 0xAE81A5EAD15DD783ULL, 0xC2946DBC59030659ULL
        },
        {
            0xAF7E103C6D411193ULL, 0xA9B561C2E514E08EULL, 0x3B4EF41B6D99C9D6ULL, 0xF258F47B4A37F087ULL, 
            0x76EB3EC2DE8B6752ULL, 0xC37B585CE0F362DAULL, 0x04EDDFECF386ED4FULL, 0x4BEBF6B2938E2E8AULL, 
            0xEA69DD71F6851B11ULL, 0x5E2C320E741CEE64ULL, 0x52FAFAFA12C9836DULL, 0x21328C6F525B4623ULL, 
            0x588C88F85AF83C28ULL, 0xAF33754C0C965D5CULL, 0x5071DF11A4929759ULL, 0x52ECF262ACE5D2F2ULL, 
            0x12761BE859F6E0EAULL, 0xFA8CEAFAE40B1DA4ULL, 0x0388AB994E1003A3ULL, 0xF23978849E6AAF34ULL, 
            0x76257A627E49DA28ULL, 0xA648B1A543A5A154ULL, 0x7D267AD242AEC80EULL, 0x308FBEB12CDAC659ULL, 
            0x72FB94FCE78C7BB3ULL, 0x06BED3FED5BB2D46ULL, 0x39A0F67CAAE94485ULL, 0xFC204C49C6B3A0E4ULL, 
            0x6E2093B4643C89CBULL, 0xF37B19AEE8E4FEBEULL, 0xDB64EF77B43BFE4AULL, 0xE2DF4414A26D52D5ULL
        },
        {
            0x2A4E7A9C6F57AFC2ULL, 0xA813C803723E7CC0ULL, 0x69D5684A3CC35DA5ULL, 0x0A3443741D7B345FULL, 
            0x3B7FAAC3E26426F7ULL, 0xBAECE2E9973338E5ULL, 0xB9E47E3DAF09EE81ULL, 0xF526BD51A059D360ULL, 
            0x4467439D57D618ABULL, 0x80B2FC7F7F6D7554ULL, 0xC4CCF51A6EDC1BADULL, 0xB34EEED64D95D562ULL, 
            0xF9FC0AA81E91D70AULL, 0x0131302BFEC94934ULL, 0x15466DA027759243ULL, 0x637D01481A6B9A8DULL, 
            0xA31920E005839B6EULL, 0xC0E1E131FC3873F2ULL, 0x1657AD6A5A66ED88ULL, 0xDD598F3350BB34DCULL, 
            0xD6257C986F67C151ULL, 0x62AAE4394F5FA589ULL, 0x8E399AD005FD97E4ULL, 0xA555CF5E4EA87E92ULL, 
            0x2076ABA9A119AD1CULL, 0x330E2429AA4675FAULL, 0xDEC8A48179D60829ULL, 0x394E0B9F2F7D4C1BULL, 
            0x93C34388628F1005ULL, 0x4F06F0D25CAD5F04ULL, 0x38215F4C12C40140ULL, 0x88F1A89961D08926ULL
        },
        {
            0xD520C4FCB9AA2D77ULL, 0x17748AE1A97A2490ULL, 0x23B3225FC103A827ULL, 0x608CB9D9F82028E6ULL, 
            0xD945AA31336C90A4ULL, 0x33387D8E58B7B5ECULL, 0x65B9A1D1EF842B7EULL, 0x03F7C6B361C5657EULL, 
            0xE25034FC5996E2D3ULL, 0x8A1AEAC839F07B2BULL, 0x294F5D0B352580C3ULL, 0xE2C54E3CB3CDB729ULL, 
            0xB6E63FB2DCE5B513ULL, 0xE910A4F04B313B4FULL, 0x203BBD0B906EC2C7ULL, 0x24133174C7BE146AULL, 
            0xDF037E5BF63507E6ULL, 0x61D880AC38EFCC48ULL, 0x9AFE76BD73AE5048ULL, 0xF0DF611AA9B6ED97ULL, 
            0x3309A8B5F4875501ULL, 0xE32DF97519C9E9A4ULL, 0x9A4E6378FA9685E2ULL, 0x1AFFA7856715D883ULL, 
            0xA6AA921B3B4024FCULL, 0x33982C390FE256B9ULL, 0x2FEB2DE8F3D4740DULL, 0x18D318097EBF643FULL, 
            0x1C4D945108B9EA81ULL, 0x69BAC0102FE4B306ULL, 0x1AF5C041CFB14E4DULL, 0x2839A0959B9C92DEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseHConstants = {
    0x39F141CC956D0E2EULL,
    0xAECA5417A5C6DADEULL,
    0xFE0703A8F4EC283AULL,
    0x39F141CC956D0E2EULL,
    0xAECA5417A5C6DADEULL,
    0xFE0703A8F4EC283AULL,
    0xF96041FAD8B9E5F4ULL,
    0x0151DC9004D1B7C1ULL,
    0x98,
    0x10,
    0xDA,
    0xAE,
    0x79,
    0xE4,
    0xD6,
    0x3A
};

