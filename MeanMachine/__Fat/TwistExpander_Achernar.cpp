#include "TwistExpander_Achernar.hpp"
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

TwistExpander_Achernar::TwistExpander_Achernar()
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

void TwistExpander_Achernar::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB13EED4CD9C90F3EULL; std::uint64_t aIngress = 0xE13845B31171FD26ULL; std::uint64_t aCarry = 0xA2AF61DDCB0C8944ULL;

    std::uint64_t aWandererA = 0x8D4A5E82D4EB18F3ULL; std::uint64_t aWandererB = 0x801BCC9B835011C7ULL; std::uint64_t aWandererC = 0xD9CAE83EE09B925DULL; std::uint64_t aWandererD = 0xEA943A02FDEDA09BULL;
    std::uint64_t aWandererE = 0xD127D9B7EFC5A4E1ULL; std::uint64_t aWandererF = 0xE855AF542603E78EULL; std::uint64_t aWandererG = 0x85911294D16EDB6AULL; std::uint64_t aWandererH = 0xB91CF40972D626B2ULL;
    std::uint64_t aWandererI = 0xE78075C502D7FCE8ULL; std::uint64_t aWandererJ = 0xA94E9BAEF5035687ULL; std::uint64_t aWandererK = 0xB3772A7C57D5D8CEULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17159945745667998328U;
        aCarry = 11827648467596016437U;
        aWandererA = 12135877374193920921U;
        aWandererB = 13808564609231896547U;
        aWandererC = 11552384170878764502U;
        aWandererD = 12648075783749147760U;
        aWandererE = 17190013005575200277U;
        aWandererF = 16224479949558392946U;
        aWandererG = 16408261158558616956U;
        aWandererH = 11871541106129390532U;
        aWandererI = 12103562089205189890U;
        aWandererJ = 11031977425274567666U;
        aWandererK = 15858880372644368683U;
    TwistExpander_Achernar_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Achernar::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xEFE43F27E1489ECDULL; std::uint64_t aIngress = 0xC0F972EA1376D9A7ULL; std::uint64_t aCarry = 0xD47DED474CC2F6C1ULL;

    std::uint64_t aWandererA = 0xC1BF24C32D08FB0CULL; std::uint64_t aWandererB = 0xAB5E8FE6A02A0DFDULL; std::uint64_t aWandererC = 0xB6A603425DE544F7ULL; std::uint64_t aWandererD = 0x9629649CE8E6C6E7ULL;
    std::uint64_t aWandererE = 0xC05FA6C1EC38F05CULL; std::uint64_t aWandererF = 0xEAADE677EC73A7DBULL; std::uint64_t aWandererG = 0x8F93126AE281B436ULL; std::uint64_t aWandererH = 0xF3D490880F20F004ULL;
    std::uint64_t aWandererI = 0xF45E86B850873416ULL; std::uint64_t aWandererJ = 0x92C40CDB0EEBF871ULL; std::uint64_t aWandererK = 0xB52DB94833DC7093ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15862774047754674886U;
        aCarry = 12834080802331743497U;
        aWandererA = 14230568556020862340U;
        aWandererB = 12395005413315093110U;
        aWandererC = 12665795862699885260U;
        aWandererD = 11743764980529845837U;
        aWandererE = 13922656907365810411U;
        aWandererF = 9587035519212936925U;
        aWandererG = 16967258387123745177U;
        aWandererH = 12599277082342035976U;
        aWandererI = 10777189778867676761U;
        aWandererJ = 9981269247932787887U;
        aWandererK = 17762006269706349532U;
    TwistExpander_Achernar_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Achernar_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Achernar_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Achernar::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x92D3F1782EC0440CULL;
    std::uint64_t aIngress = 0x922E803A229EC43EULL;
    std::uint64_t aCarry = 0xD68DCECD890E980FULL;

    std::uint64_t aWandererA = 0x9929BA481CE23A75ULL;
    std::uint64_t aWandererB = 0xA81A0AA4C3D33EECULL;
    std::uint64_t aWandererC = 0x82A5D47FC05C71E6ULL;
    std::uint64_t aWandererD = 0xE9EB7E1360F1B08EULL;
    std::uint64_t aWandererE = 0xFE87191B940944B5ULL;
    std::uint64_t aWandererF = 0xB193D4517374A0D6ULL;
    std::uint64_t aWandererG = 0x86C69B19169ADFE3ULL;
    std::uint64_t aWandererH = 0xF77E5D4DDED65AB7ULL;
    std::uint64_t aWandererI = 0xB15EA4686AEF9759ULL;
    std::uint64_t aWandererJ = 0xB2AD177E1072E7AFULL;
    std::uint64_t aWandererK = 0xD3BE968A7CA7A476ULL;

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
    TwistExpander_Achernar_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Achernar_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Achernar_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 1 of 33
// Exploration cases: 50000000
// Diversity score: baseline candidate (no earlier family member)
void TwistExpander_Achernar::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 768U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 341U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 171U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 120U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 622U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 490U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 34U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1763U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 352U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 728U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1414U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1079U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1136U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 404U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 279U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1040U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 300U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 324U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1327U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 504U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1819U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 563U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 608U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1267U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1081U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 566U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1034U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 379U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 88U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1601U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 316U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 860U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1827U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1983U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1526U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 252U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 181U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 578U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1029U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1265U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 542U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1502U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 321U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 583U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 519U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1052U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1043U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1158U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 470U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 630U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 539U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1342U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 162U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 734U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1118U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1567U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1416U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 418U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1391U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 27U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1481U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1960U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 332U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 307U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1985U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 467U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1552U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 59U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1197U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 902U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1340U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 282U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1099U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1086U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1798U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1613U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 291U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 804U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 845U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1055U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1931U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 713U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 754U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1706U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 656U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 485U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 632U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1329U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1240U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 991U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1644U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1821U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 547U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1679U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1672U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1367U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 878U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1349U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 236U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 229U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 971U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1886U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 326U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 850U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1557U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1955U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 137U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 785U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1637U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1970U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 91U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1302U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1636U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 935U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1120U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1630U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1958U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1686U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 419U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 892U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 8U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 899U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 471U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 791U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1562U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 993U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1114U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 797U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }
}

void TwistExpander_Achernar::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xD03F3FFA3AF712AEULL; std::uint64_t aIngress = 0xCC93A800C4BF4D40ULL; std::uint64_t aCarry = 0x957CDA9B550DF4E5ULL;

    std::uint64_t aWandererA = 0x9DF2B063CAA1ABD6ULL; std::uint64_t aWandererB = 0xE614CEE3F0C492C1ULL; std::uint64_t aWandererC = 0xB68CC6BA74E7A17EULL; std::uint64_t aWandererD = 0xD336ACA11FA3A321ULL;
    std::uint64_t aWandererE = 0x83B3BA4C38C1445BULL; std::uint64_t aWandererF = 0xB36D740CB4A9A896ULL; std::uint64_t aWandererG = 0x8B5A26F08C3446B8ULL; std::uint64_t aWandererH = 0xE3701E950B2D22B4ULL;
    std::uint64_t aWandererI = 0xB5B72E12ECD88575ULL; std::uint64_t aWandererJ = 0xAD64EE848D6FC36DULL; std::uint64_t aWandererK = 0x8CED9DDB79015527ULL;

    // [seed]
        aPrevious = 14568406656436937461U;
        aCarry = 14015417013830935992U;
        aWandererA = 14120638078232590771U;
        aWandererB = 14054822032119569358U;
        aWandererC = 9360930924997630400U;
        aWandererD = 16043634556799502287U;
        aWandererE = 9727461574104046044U;
        aWandererF = 17935900930805578500U;
        aWandererG = 11817265661199817483U;
        aWandererH = 10111196032335207899U;
        aWandererI = 12521451392733485421U;
        aWandererJ = 16390328093252166551U;
        aWandererK = 16642125549836634406U;
    TwistExpander_Achernar_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Achernar_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Achernar_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Achernar_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Achernar_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 1 of 33
// Exploration cases: 50000000
// Total structural distance: baseline candidate
void TwistExpander_Achernar::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1255U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6354U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1878U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2148U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6739U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1069U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3370U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1422U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5071U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 560U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3627U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5330U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 753U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5731U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6626U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3580U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 387U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 286U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1985U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1114U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 401U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1285U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1071U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 316U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 526U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 767U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 517U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 659U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1807U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 507U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1109U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 96U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1030U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 485U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1346U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 966U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 1 of 33
// Exploration cases: 50000000
// Total structural distance: baseline candidate
void TwistExpander_Achernar::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1199U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 704U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5970U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3590U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 63U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6818U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7190U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7332U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7148U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3049U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2557U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1609U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4023U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6964U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7875U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1082U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 757U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1378U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1274U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 383U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1568U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 884U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1857U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 429U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 300U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1763U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1137U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 504U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1868U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1046U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 448U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 480U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 667U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 947U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 250U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 345U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseASalts = {
    {
        {
            0x1AD1031CFD2C24C7ULL, 0x69E57416FED425C6ULL, 0xEBFA3EDC21D44E03ULL, 0xB854E72A97A03CC1ULL, 
            0x019E0D7394E0C33FULL, 0x852F75F8C829DA31ULL, 0x1F6891DA87E5C360ULL, 0xBEA28A00DACB67B8ULL, 
            0x40CF7B15F4194C77ULL, 0xF88551AAFCE0CB1CULL, 0x933B08151310CDE1ULL, 0xBA8573EE26193FC5ULL, 
            0x657F007011F5BCB4ULL, 0x754673C682AB85C3ULL, 0xC6E69AEFD7D5BF32ULL, 0x1DC9725917A70101ULL, 
            0x50C355F47B15EEF0ULL, 0xCFB22351BA4E40F2ULL, 0x5A5B332881F1EB76ULL, 0x23AA5AB6699822CEULL, 
            0x251672A90AA0B1CBULL, 0x44FB07FBDC3ECFB9ULL, 0xE8C45C093F575A60ULL, 0x3A1B94F96D0894DFULL, 
            0x6458AE7AE3420FA6ULL, 0x0D2EABDEB04FDA13ULL, 0xDBE6595B1E151502ULL, 0xB5C0D23F682B07B5ULL, 
            0xE5A866D0B8237E97ULL, 0x34CA756939475147ULL, 0x229EEA1B8A59FC21ULL, 0xE69421FD498CDD04ULL
        },
        {
            0x29BDF410AA8B5587ULL, 0x185CFD1E54DD40F1ULL, 0x1F60FEF7358C4999ULL, 0xD81A654F65587BD6ULL, 
            0x7ADA38A083513EBDULL, 0xFBB93D17FB761886ULL, 0xE4B20E1223648506ULL, 0x022C50BB9F5171E6ULL, 
            0x49F24BD59EEADC51ULL, 0xA50C144FE53AD2F3ULL, 0xEF1BA516F330F239ULL, 0x01F0E8F278E43465ULL, 
            0x46BA2922D58F669EULL, 0xE498FD14E11A3A2EULL, 0xE272202DBDE670F9ULL, 0xC819D0D163319A34ULL, 
            0x760A22B05720650FULL, 0xDF0567DA9E662234ULL, 0xD9E86E1B05564499ULL, 0x5E14701E4714A111ULL, 
            0xAE4432CC2B1ECEABULL, 0x2E20AC0C9BAA792EULL, 0x8DB09B5A4A320273ULL, 0xA296A3AB7897FBCDULL, 
            0x4579ABDF4377ED10ULL, 0x9B3B4F77B83FC580ULL, 0xA6B30A70DDE931A5ULL, 0x7EEF67213149D19DULL, 
            0xB31AE8978562A112ULL, 0x318371D4A8A246DDULL, 0xE785565528AD6D11ULL, 0xA199616BCDFB6FE1ULL
        },
        {
            0xCEC889986172F53BULL, 0x6183522738F3A1C6ULL, 0x142270892A6FF3FCULL, 0x0BA0730CD92CBF84ULL, 
            0xE2933C931930AEBFULL, 0x7D727BFAF87F2B8DULL, 0x5E60F1C25F83468CULL, 0xAC64ADDA9FA7E1AEULL, 
            0x47833F3F2D1A25A3ULL, 0xD29938AB13AE311AULL, 0x7F1AEE59696FD141ULL, 0x47CFC146E6DE1E63ULL, 
            0x5937283C6F444391ULL, 0xA731D5BFE470AF7FULL, 0x615AAF44FD6EE20CULL, 0x950A2B6DE2CC955BULL, 
            0xA9E1B76F800D89A4ULL, 0x04C7ABE0CA254288ULL, 0x643003A265370D45ULL, 0x2339210782790856ULL, 
            0x118B22699AA01A16ULL, 0x8050983759109786ULL, 0x84409A2FBE659C73ULL, 0x0A017FFCDB81CF52ULL, 
            0x83643DAA2DFCADF4ULL, 0x2DF06CB6643D96B1ULL, 0xA082F32EA27D642FULL, 0xCAB81096AE1AE790ULL, 
            0x0FF7D903710DDF31ULL, 0xD3853E20C49832A4ULL, 0x607174FBEFB974A6ULL, 0xC17B64517054D594ULL
        },
        {
            0x0E54C15634F26327ULL, 0xBEFAFA39CD9A4295ULL, 0xBEF088D84AD81451ULL, 0x8B857E719394124EULL, 
            0x8CA0E73036A68019ULL, 0xE9A3D8385F353C4DULL, 0xC62691967DA4CA0BULL, 0x23EFA4B259AEC3F3ULL, 
            0xF543BA7728C1F65CULL, 0xA9E52B98ECEDDE3DULL, 0x935B9A13FC480656ULL, 0x1C7CB7B1C9FC42EAULL, 
            0x6FC08862346F3CFDULL, 0xBAEFBD64EFD41394ULL, 0x2CC4E4FABB1E2FBAULL, 0x9832B85B9B135992ULL, 
            0x5A046230EF052BBDULL, 0x69A88844D48FEDA7ULL, 0x9E60207B4E8B501AULL, 0xE0240BD9068FFC9BULL, 
            0x79AB3E520370C452ULL, 0x0A61F77EB7C461B9ULL, 0x1FA6E73CA42CBB28ULL, 0xB05B33513F0B886DULL, 
            0xB554F86F7746FDDAULL, 0x7B17C4DD03126A6EULL, 0x225337C1CAE38EEAULL, 0xA143A0714CFD0718ULL, 
            0xA40082CD26754733ULL, 0xD5B969584C3B39D9ULL, 0x9BABC1D0144C5A66ULL, 0x7F7C8206434EF9CEULL
        },
        {
            0xE2A6CB37A03AC2EDULL, 0x0720FA07FE2045DBULL, 0x5B98571FBD3B23D2ULL, 0x8447231A94B9E96DULL, 
            0x1633F3B265A57C33ULL, 0xFD6AADA755EFA00DULL, 0x242FF173E0AFC233ULL, 0x233F8486F73F924DULL, 
            0xA34B5D2F5ED00CADULL, 0x33B6C45910FBB05EULL, 0x05526994D73E0F6AULL, 0x52CFC0CE56003C40ULL, 
            0xD2C8173FF6330A28ULL, 0x94A89DDFB828C492ULL, 0xA971E180978FF0AAULL, 0x47C6786ECE2BB0ACULL, 
            0x57C97F30003D7CEDULL, 0xBF9BCAF5E9E71467ULL, 0x93ED20FC3251DABCULL, 0xBD88FEC1D5ACCD74ULL, 
            0xD90F60FDF460919DULL, 0x78A321D41AF2BA97ULL, 0xEE4C7401D754FAA4ULL, 0x3B63378898003A66ULL, 
            0x91520C0171268856ULL, 0x4E8756820E94D17FULL, 0x2E832DAACEABB985ULL, 0xF963F1F5CCBE31EFULL, 
            0x606F7ECB1FD2A92AULL, 0xEFAA7E45E7D4487CULL, 0xF55E7BDEAFBA084EULL, 0x00A56A7F3B65685FULL
        },
        {
            0xA5E0B36016692F16ULL, 0x8B57F1C9DD1AE7D5ULL, 0xDA08AB6FCCEC58E4ULL, 0xA8324625A92E97ECULL, 
            0xEE3320EA8E06E59FULL, 0xBCFA37D4AA77DC74ULL, 0x18676ECB05F39AB2ULL, 0x2F53C47E5F6CBB4DULL, 
            0xAFC18182DA2715B6ULL, 0x6E44D01C67E2DFF3ULL, 0xE3EBD07D43F0AAA0ULL, 0xB384D50CE0AFC842ULL, 
            0x764F599908D5FC4AULL, 0x3BE2E7FAE4AEE6C1ULL, 0x6B23937C3BD05006ULL, 0x9DF1B4310399B6CFULL, 
            0xA7B01E4FBE0A1139ULL, 0x0A2E95B8AB289B65ULL, 0xE1830AD83A48672FULL, 0x61A2627846F2423FULL, 
            0x3090EF1EC9ED5E01ULL, 0x84EEB3A0F9037977ULL, 0x0AFAB8979C776C10ULL, 0xAF3F4242A9EA730FULL, 
            0x87F6E43BCD511EDEULL, 0xAD57F923E9107D78ULL, 0x185FF541341249CAULL, 0x785013287C7AAA89ULL, 
            0x3DF77C4F873B9467ULL, 0x1C91B00AC3CE77B2ULL, 0x95631DA7DA792A5BULL, 0x31BB9BD61D7ACA59ULL
        }
    },
    {
        {
            0x895BAEB60E354BBEULL, 0xD4FFABC7CEE68008ULL, 0x64ACA8F1403EC227ULL, 0x1E92D274BAA11DEBULL, 
            0x0D5BDD290B05ED6AULL, 0xAA2A138D56B36F9FULL, 0xCF34658380D11F17ULL, 0x989C47C0DD49B456ULL, 
            0x1DB008E059216B43ULL, 0x6CE351C751978EA7ULL, 0xB1665BF3AA633EF2ULL, 0xEE2E6A2AC090486BULL, 
            0x1C62651EC6E51EAAULL, 0xE0E94CE0E125D6E1ULL, 0xF3B7DA87155D0B0CULL, 0x168FF19E8725F6D6ULL, 
            0x0BE0731F1ED8EA92ULL, 0x360B0EF8097F78D3ULL, 0x51002E1254A1D0F8ULL, 0x18FA4924495009D0ULL, 
            0x15862A61E2C80B21ULL, 0xACA6A30C8A845310ULL, 0x955A9AB125186209ULL, 0x7FF5FF1FFA9BFC76ULL, 
            0x4F59300A0B8AFAB9ULL, 0xEC7CC1F1F36E1AF6ULL, 0x54DDB0C9B8612E0EULL, 0x8A205DF4CF6CC170ULL, 
            0xCFBAEFABF17872D5ULL, 0xC3A061B596600E3DULL, 0x83C4C4BBD82A3030ULL, 0x2318E3A46ED1775CULL
        },
        {
            0x78F3BC21F45249A4ULL, 0x32EE4D99FD763769ULL, 0x643D79BC479DDC68ULL, 0x6652AE4EE6635643ULL, 
            0xA781AC2539381F4FULL, 0x63431080B2071728ULL, 0xFD72F1184D72AA6CULL, 0xA8778E544BF6DF8AULL, 
            0xD5EA3F6C17BE512DULL, 0xC6F8F1F23BA7D204ULL, 0x73B36B4523366943ULL, 0x62F1DBED9E2769D2ULL, 
            0x330DD41D3D4563EEULL, 0xE84DC2A43E43882BULL, 0x7ECD003306B42DC2ULL, 0x316AD225EF132ABDULL, 
            0x265B84F6119BF1C2ULL, 0x1E1ED444FF1E6C77ULL, 0xC943871395794EF8ULL, 0x901F5B8A5C69BFCBULL, 
            0x677394478DD639BCULL, 0x3AC8B17D9BB706ECULL, 0xC082ADBB916E3AE9ULL, 0xEC60603AE46A7E85ULL, 
            0x3D073A2AC64ED2E4ULL, 0xBCCDE67A5AD1C350ULL, 0x199EEF24612D7F76ULL, 0xC631A3D0984AA795ULL, 
            0xD554697D15009DB5ULL, 0x233DF2CEC75601A6ULL, 0x171D4416945E2FB6ULL, 0x50E50661D9077A41ULL
        },
        {
            0x867EB2421E732901ULL, 0x249F45B80BC8AA33ULL, 0xD6EE0F1958B822C1ULL, 0x04BD6FCF2D593038ULL, 
            0xF48570F6B6E6E767ULL, 0x5B23287A94365C03ULL, 0x03A123C88CA90561ULL, 0xA5C2D64D51B59583ULL, 
            0x1F640B9ECC937AFCULL, 0xCF81A14F68A88409ULL, 0xB2B86BD9157E10E9ULL, 0x0C820308EEEC1F85ULL, 
            0x8E9D5D0C86595677ULL, 0x90D08ED19197A01DULL, 0xAAE0DF6FAE9923D4ULL, 0x236A47AA98FD80D7ULL, 
            0x930E0BBC8744D261ULL, 0xEB6347BC0045280EULL, 0x22F682C71CF942BBULL, 0xFDCB2C72FC77136FULL, 
            0x8230915EA2CE01E6ULL, 0xB6951A22E81F10AFULL, 0x864C37257A95535EULL, 0x90CC32EF674B99F9ULL, 
            0xA8557B729F21D6B9ULL, 0xBD587153588F26F0ULL, 0x77216017884925D2ULL, 0x24DEF70079C4341CULL, 
            0x268C5AE498002D4FULL, 0x475349C030B33651ULL, 0x55CF6196588B4925ULL, 0x2445E63C13944191ULL
        },
        {
            0x7EC9AAB97FB786B7ULL, 0xDDAEDC04991B640CULL, 0x7C37426445F3AA97ULL, 0xD5462D70115FA39FULL, 
            0xC1575B343047C1E9ULL, 0x70A2DE70262E72B9ULL, 0xFE292EA4FA8DC301ULL, 0xE106117F24D78B6EULL, 
            0x8E90D8CD65A98BDDULL, 0x8CE8026C9189E60AULL, 0x80B9BC4F3A0582B1ULL, 0x9856C6C9749A90D3ULL, 
            0xD44E6E4FF6DFFB16ULL, 0x770E1275C8EC73C8ULL, 0x932EF857DE6767DDULL, 0x1605C804FBEB6AA0ULL, 
            0x985F6BE0A85B0785ULL, 0x18164DCCB0F004FBULL, 0x7F76944FCEE1EA52ULL, 0x8B9C7A8542884402ULL, 
            0x75DD3951AA1BF572ULL, 0x48685AE3A1007A78ULL, 0x85D50480AA48DC1EULL, 0x1B866858599CCA45ULL, 
            0x7BEDF415DD24E0EFULL, 0x679F991109A390F3ULL, 0xB180DFDA6688281BULL, 0x24FABBF35B9CF916ULL, 
            0x38F70926889C146EULL, 0xA30B21022072DDADULL, 0x2840D1367ECF529AULL, 0x64A7FAFA109C3867ULL
        },
        {
            0xA03BF5DB08ECDEA4ULL, 0xDACAA8002BAF49D4ULL, 0x3908D7FE3B2F8159ULL, 0x6958802C043541B7ULL, 
            0x303AA26F0520C18AULL, 0x17D62E381B92F7DDULL, 0x394B32B199BA9D95ULL, 0x37FCC1B3FE3F6131ULL, 
            0x60DB1A3AF2B61944ULL, 0x7905C9A22F2D11BEULL, 0x7C4BAFF918A09D1FULL, 0x911100E0D3F4027FULL, 
            0x284AAB930CD323BFULL, 0x2EA076D67E0345B8ULL, 0x7D9D2C65721CE821ULL, 0x910435AAE1CE2DC3ULL, 
            0xAAE353A33E54C809ULL, 0x96535E9B3B9D120CULL, 0x51D8FF823E7CE573ULL, 0x2691BCA160323B49ULL, 
            0xBDED5B08685D07A7ULL, 0xCDBD958CAE42CF46ULL, 0x845958CC2C66964FULL, 0xC89894F50BACFB20ULL, 
            0x5E1A402576A8A6D5ULL, 0x48330DF357E58690ULL, 0xF2D550F2C8E86160ULL, 0xABDDAF3899AFDDFAULL, 
            0x39DEC4C3307C08D7ULL, 0x0084EDB197E38D76ULL, 0x964A01901A68EE95ULL, 0x5CAD62AF7AB77177ULL
        },
        {
            0x9A37CA650D41554FULL, 0x7C65C54E05CB044CULL, 0x7A67C99EFA98EE5AULL, 0x3E4B535404E40DCCULL, 
            0x2C51F66CBCBBC100ULL, 0xB621967ABE5D241BULL, 0x35D7413ACC0C92C3ULL, 0x1D245D3D0085A111ULL, 
            0x1E56A38FAF8EAA66ULL, 0x2FB4B344DFA7E60EULL, 0x53D30005D7F985A0ULL, 0xF3BD84A1E5D9669BULL, 
            0xFF5BE4F935C64747ULL, 0x284858B5817365AFULL, 0x84C4552F2C263C4EULL, 0x73787D792E834353ULL, 
            0x4242CD55E5B867ECULL, 0x888DA663436929A3ULL, 0x04481638C1BBC129ULL, 0xB856D7FE40CF4C8CULL, 
            0x00B00106256684DBULL, 0xFC97DC8B7D499546ULL, 0x9353CA6531E101F1ULL, 0x2269AA44E10E545FULL, 
            0x6327B68120B1CC4FULL, 0x5A482AC44BC790B3ULL, 0x6C9B6A95DC73BE2CULL, 0x6CF4F87AAE69D189ULL, 
            0x41FD9F7B5C9B8CC0ULL, 0x2A699A122D771E9FULL, 0x80DFBDEDCABBAA4CULL, 0x94467BE913A55001ULL
        }
    },
    {
        {
            0x6F46F19FCCF30A88ULL, 0x8DA5F229D53406C5ULL, 0x78F68984B5B190F5ULL, 0x0A9AE1416AB431D4ULL, 
            0x15162C345D6F1DBAULL, 0xC82A49A713D94E0DULL, 0xAAE0A7F0A1CE0F8DULL, 0x1C82D6BBD700D843ULL, 
            0xFA7A0C194B0CB0C4ULL, 0x8E69AF99DD529C91ULL, 0x353256C2608E3496ULL, 0xC486893DD8DB647BULL, 
            0x719B4BA27BD476B5ULL, 0x2D5619924A25D61BULL, 0xB0DB57EDB25B3224ULL, 0xBC53A339ACEEBD71ULL, 
            0xC67DCC2720618B14ULL, 0x792045AFC455D7C5ULL, 0x2618097F3619C42CULL, 0xF6EB524D2DE7FE41ULL, 
            0x1EF69E83AF8DCF18ULL, 0xC32876EA243E29CCULL, 0x8FB298A2E7142C5AULL, 0x1D106E62C18B3EB7ULL, 
            0xB8B8635309D031EEULL, 0xD913F84A3404E206ULL, 0x7400B52FAC1F7589ULL, 0xDFBFE39ED72028DDULL, 
            0x68D4D53569610409ULL, 0xB4B8E7C16B096CF0ULL, 0x07563594EC2A609DULL, 0x994B819EBA03AF23ULL
        },
        {
            0xDCDDB6BE34F3A12CULL, 0x285572EA46CB5A5CULL, 0x819EB2BE41590AAFULL, 0x8F121D37301084D8ULL, 
            0xF279A31AC4E3A5D9ULL, 0x4469D3B0775EF4DEULL, 0x9BDA16675F1427C1ULL, 0x11EEC2C624189D2AULL, 
            0x0747C00EDB2CDB56ULL, 0xCF34FFFA25A7CA3CULL, 0xADC964797CBD42C2ULL, 0x43F2B14B99007D46ULL, 
            0xC55953FDDDAC1C69ULL, 0x5973C35370E1EE50ULL, 0x80C75C481AF2B6E1ULL, 0x07D0E5831C441BD0ULL, 
            0xE571F11B93FB577CULL, 0x75F33AAA5A498D06ULL, 0xA52F898AADB195E4ULL, 0x24264EDB631AD5EDULL, 
            0xF217FFDA08DFEE51ULL, 0xDB797EADA0A0D664ULL, 0x1F28AC7E04E04558ULL, 0xD1B2EF6E9559DEE7ULL, 
            0x82767961540033A8ULL, 0xD24DD68F47969D45ULL, 0x044B5E90B1C43A8CULL, 0x2EFE666686CF6AB5ULL, 
            0xC6AD04764062DB97ULL, 0xE7159BC8BBFB8AD1ULL, 0x9E5400C4312D06C1ULL, 0xF73A6194396541E1ULL
        },
        {
            0x05433829C875BF67ULL, 0xC484308DEAFCC0CBULL, 0x353E4503AFA0B84CULL, 0xC656973BE26DE94EULL, 
            0x54EE9F4D1ED4474CULL, 0x4254271B0D9E0997ULL, 0x2F8F8C8F362C602CULL, 0x33A95F3C9A15A44DULL, 
            0x03639D479FD3CD88ULL, 0xC058298072D04E89ULL, 0x54AB0D699AF07134ULL, 0x0C6CC7A5643848A1ULL, 
            0x2D5739EE8F4B5F26ULL, 0xC782E70FC8F70B59ULL, 0x57D1A84ED5E44296ULL, 0xD49A85FFA85BEFD8ULL, 
            0x428255860073EC2EULL, 0x8F86E976B5FD428EULL, 0x8C23DE7E64833798ULL, 0x36B07AAC4BFE0ED6ULL, 
            0x833476E172985E8CULL, 0xB57D2A5594392FFEULL, 0x77E1702C028FABBCULL, 0xA3FE8C70921FB7CDULL, 
            0x86D0378D647BB27BULL, 0xB7AD02CA8CF2676DULL, 0xACD1786400412924ULL, 0x5DCAA29A0AC56D77ULL, 
            0x0E4E941ECCC2636FULL, 0xA867550822AE1BEBULL, 0x752548668BE4E100ULL, 0x682A3D73A9E1F8E7ULL
        },
        {
            0x3748B406FA0C8AD9ULL, 0x90661A422B20EA94ULL, 0xD7CF9F03F06D11CDULL, 0x2352BF9ECFADB0A0ULL, 
            0x18747CA0D12D74C0ULL, 0xEA19C3F17D7AFB47ULL, 0x2943C43559387E5CULL, 0x466FAB7F9BCC0370ULL, 
            0xA3E80E0E0220D321ULL, 0x4E2C8646254BA45EULL, 0x43DA4BD5516A4184ULL, 0x1B48059B87A66983ULL, 
            0x9F06EDDD492533C1ULL, 0xA13B10756D733A0DULL, 0x840BBA72EB6F5DC3ULL, 0xA8A18BBA80B050B5ULL, 
            0xEFAA087638FD945FULL, 0x510FC3F4D3F52E25ULL, 0x96824ECF485E6BE1ULL, 0xFD6FA9BA99AD45BAULL, 
            0x5255B6F4F0D066BBULL, 0xDD5BA2F56F6FFE79ULL, 0xB8B9F2FC4AFD30C6ULL, 0x961F23DA032509C1ULL, 
            0xCA22145C68F883A4ULL, 0x13787D4AC7CC32E5ULL, 0x32934D2677B9318AULL, 0xE4932E57CAEF04E4ULL, 
            0x1AEE21267E77C361ULL, 0x1E9D91BBFFFEA964ULL, 0x2A81B1D2B9A213E2ULL, 0x280E0F5F3079F2C5ULL
        },
        {
            0x5A52A03BE874A15CULL, 0x50AD68FC5BFCBF71ULL, 0x472B303BF9F5000EULL, 0x388B4557CCD7576FULL, 
            0x3E7947BF4F6D4EA8ULL, 0x27571AE93BF0E186ULL, 0xBE16EDFDF1F1847CULL, 0x1FFFC9E2FFC8CDA5ULL, 
            0x8F5D2910B534FBE3ULL, 0x8C107401EE68C232ULL, 0x59914A9C825459CCULL, 0x75E2509DE4663EFBULL, 
            0x51DCA63C913D14F9ULL, 0x707C5089E0183B6DULL, 0xE4D8A6EBE33E7255ULL, 0x1CE509E29D1AD177ULL, 
            0x1C7FEF044E8B353DULL, 0xD7E8AEFA7EE18AD1ULL, 0xD3D228C9763CF368ULL, 0x1DBC8A60CB7A65FCULL, 
            0xE6478902DCD102F2ULL, 0xE57E62F5865668A5ULL, 0xCCBE1FD61ED5A492ULL, 0xD75C141D1C68FA1BULL, 
            0x832EE516695FF19BULL, 0x613D3A7887B52D92ULL, 0x4A743B0B1BB33C51ULL, 0x6B0C4A132C8AEC0BULL, 
            0x44548ACF8B1A5F2DULL, 0xD8AA7EB96BE94CB0ULL, 0xE21DE4765B0F5245ULL, 0x6F6737E43B16D828ULL
        },
        {
            0xBCB3B6DCF6E2BD3CULL, 0x9530B8D900B66004ULL, 0x7313B3BB3B7DC40FULL, 0x025047B31FF40505ULL, 
            0x3F7E83BACE484E84ULL, 0x6CDAB6583D3B2FE4ULL, 0x1F01F15DFC7114D9ULL, 0xD4D611DE776AD924ULL, 
            0x0F2CACB7E2DCCB1FULL, 0xD4BC5C9ADCA994CFULL, 0x310758D3BEC33AD8ULL, 0xB5EA6F61A5A5FF28ULL, 
            0x3385BDFFB55FE36BULL, 0xFDA257954EA888C7ULL, 0x90E4982CFD6293D2ULL, 0xFA0735F05568EB5FULL, 
            0xC396698128603F13ULL, 0x8A5622E114142FABULL, 0xAF367DE9435637FAULL, 0x1A1BEA480AEB702BULL, 
            0x7608EB8B33ACB7FBULL, 0x55CD73AB05D3B5FAULL, 0x8BBFA389B51AC9FAULL, 0x834A1ABE22684D34ULL, 
            0xB8B9BE55A436AC0FULL, 0xA6CF4F342F6A98D0ULL, 0x07DC772F6020A3A6ULL, 0xE17CDF6182D00469ULL, 
            0x3B881E459168540CULL, 0x9520F1EA29FDFE66ULL, 0x6D9DEEBF3CC6E0BFULL, 0x982BB618694C56BFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseAConstants = {
    0xE4B11273E0F2463EULL,
    0xA4CB500FD0D489E4ULL,
    0x9E2267F675BE2EB4ULL,
    0xE4B11273E0F2463EULL,
    0xA4CB500FD0D489E4ULL,
    0x9E2267F675BE2EB4ULL,
    0xBD45FEA368D7CE67ULL,
    0x1378E962D6A45F43ULL,
    0xEA,
    0xDC,
    0x26,
    0x39,
    0xA6,
    0x79,
    0x62,
    0xBA
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseBSalts = {
    {
        {
            0x687A10D83E83F391ULL, 0x32D4CD68B3174B4FULL, 0x6ABE5168A128A11BULL, 0x5F81A4A618F21BF2ULL, 
            0xE745760B815CA064ULL, 0x15DB60B250201C2DULL, 0x1EC474120D02B060ULL, 0xF17A071C4803CFBEULL, 
            0x166B21E3AAB6B167ULL, 0xD4D0076F6DDA6605ULL, 0x5A3AA55CB33F0AE4ULL, 0xC561ED7503F1A863ULL, 
            0xFB7B9463397B0916ULL, 0xD0B05C8C725B0E88ULL, 0x46A99D6EA729F552ULL, 0x863023BB0252F364ULL, 
            0x2D47B62EE16CF145ULL, 0x9F335FA9F21B71F4ULL, 0x23CB29C674B77AA8ULL, 0xFAE9D0970751FA30ULL, 
            0xC8E71EA48A0B878EULL, 0x71D1A4C65DA943E8ULL, 0x858D94AB67FA04D2ULL, 0x3456F78E7BF0D3D9ULL, 
            0x6DA0B18EE56D98B2ULL, 0x436C2FAACE451ADFULL, 0x90631C5ECAE77C99ULL, 0x040493EB8EFE882FULL, 
            0x184FE29EF751FF8FULL, 0xFAE67964E77D6E78ULL, 0xB0FF6C642353AA80ULL, 0x9771E4CC054F43D1ULL
        },
        {
            0x95E0771A02276B3AULL, 0x59DA9349653C7D0AULL, 0xCEACDFF8604C89A6ULL, 0xF29A8121928862D9ULL, 
            0xB9E9E9AFEE935419ULL, 0x8C0A3DE0DC83FB83ULL, 0x53F8A107E50B957FULL, 0x78EFA8752D009E2EULL, 
            0x311CD9EDBC36C573ULL, 0x0E2472A994E771D6ULL, 0xB17C8606CFC56ECAULL, 0x6F040149C7166086ULL, 
            0xA9F64C779DF975FCULL, 0x2ABA19F8E6E74E13ULL, 0xD5F1B08C06B6DA0CULL, 0x7DABB88DAE96F058ULL, 
            0x97D7DDC40FB27033ULL, 0x5FCD6F8F0F9FE342ULL, 0x464F474BA00F8F22ULL, 0x5AF1A7B2C9F960ACULL, 
            0x2459ECF73695250DULL, 0xEB0C333CF4F0DB12ULL, 0xD85D9746A37F2579ULL, 0x35810E30FE418C86ULL, 
            0xAFA48B40D22ADA24ULL, 0x6D95821C4E12E105ULL, 0x2C10F705DADCA8F9ULL, 0x87F4F95D3063AFBCULL, 
            0x17E445F97605DB45ULL, 0xF2E80CE69699E958ULL, 0x56FC6CB0F3E16FB2ULL, 0x307DDF0A48B792BAULL
        },
        {
            0x3719CC72E803761AULL, 0x9BF16C9608C40FB1ULL, 0x2791105D90CF7F66ULL, 0xE6D10216D44135E0ULL, 
            0xB2ED280470CAB712ULL, 0xD6394D64D140E3FFULL, 0xC17754E0D2BF0F7FULL, 0xF8A679E67DB25376ULL, 
            0x5F9B9AE5AD9E2E5BULL, 0x98F1942642849324ULL, 0x6D925E08D393FD3FULL, 0xA19C675E67F7756BULL, 
            0x2CFAFFBB3D9048ABULL, 0x7C960BD8DA67311AULL, 0xBE0AC7AE592E74A2ULL, 0x0BE4E52C72205129ULL, 
            0x86AB2F1F25E41179ULL, 0x493908CEA2B29ABFULL, 0x5FD4F68FD4934466ULL, 0x011C69A040E45BE7ULL, 
            0xEE5E930F61754E34ULL, 0x7AFAC5D782F9AE6FULL, 0x92D9F0A18BE26B86ULL, 0x579FFCF35780826BULL, 
            0xABB8711ED775A71AULL, 0xBD403B93E2D92D25ULL, 0x3FE11224D0C4B0A1ULL, 0xEB106D41B848F1FBULL, 
            0x6E863AFB670FA536ULL, 0x26FDB0F8CD05E498ULL, 0x6C77FA958DA898C5ULL, 0x6B862BB42B135073ULL
        },
        {
            0x43814FC77C1A8D64ULL, 0xB8A32F9213F95B94ULL, 0x5F2963FC9A37DA15ULL, 0xE677C0E206901088ULL, 
            0x4F3896F59581B9F7ULL, 0x4057C1E28B578E8EULL, 0x6DE64F2EC936977DULL, 0x417A7F712B065999ULL, 
            0x12DCA70163084830ULL, 0x8FC7A524EF17DEE2ULL, 0xC500826E030942EEULL, 0x1B20AD5A920299DAULL, 
            0x192BE0CB72CB6218ULL, 0x7FC9E8AD055C7C64ULL, 0x2331502570F93493ULL, 0xEC24DAE484723242ULL, 
            0x04242B70D4617FCEULL, 0xBC6FA8FBE392A7E7ULL, 0x77ABB8E9D1AB2CFBULL, 0x872482987237B0F3ULL, 
            0x35DE4215904F36AFULL, 0xB9829A9F29D9AD4EULL, 0x377A4C90D5D3265DULL, 0x75629BDF95153A2CULL, 
            0x65572EFC3745B8C8ULL, 0x9E5237C54FD1CE3CULL, 0x4480325FC77EE825ULL, 0x0FA892EC1626E45CULL, 
            0xD6747A9B633DC996ULL, 0xA8E5873BB0EF5490ULL, 0xFCFD7CF52909FA61ULL, 0x0E0F340195F4760FULL
        },
        {
            0x01C13E4DC3D777EFULL, 0x70F0DFDC5CAF0BA7ULL, 0x72FF043D65D5B168ULL, 0xF807E9FEBAD41EE3ULL, 
            0x163713FCC1EEA56AULL, 0xB8D46E1AE7A26BA5ULL, 0x1F339D6502EA7A40ULL, 0xA0D79DE174B03C54ULL, 
            0xD45DA18D1F432EA8ULL, 0x6D4B286A4E0A7B26ULL, 0xA9D1B44945061E62ULL, 0xC8D1A98A82A00CB0ULL, 
            0x6E35EDA9206903B8ULL, 0x43D80FE898B1E2A2ULL, 0x29D6D58003E82B9DULL, 0x0442CF69E1C9C041ULL, 
            0x2577CA86868C630BULL, 0x86010A32B89EDBC3ULL, 0x0DCA3BCE22FDBDC7ULL, 0xA0B8C7B059216B19ULL, 
            0xEBED856E664F3A17ULL, 0x95B01026132F68BAULL, 0x601CFEA8F21573B8ULL, 0xEC7C3D5F9E482448ULL, 
            0x62BEA0F950A8C40EULL, 0xD1B3868F455F0BAAULL, 0xDA7A255E2E5342E0ULL, 0x76264EBBE29E5106ULL, 
            0x135FAE5AD850370AULL, 0x41E9720ABC2954C4ULL, 0x7265455D78E72741ULL, 0x299019904D3D553DULL
        },
        {
            0xE2584764FAE13DB9ULL, 0xF13239918D330069ULL, 0xE57067003C3FB984ULL, 0x0D9A59F2A1278FA7ULL, 
            0x4CDAA1FCDFB3B8E0ULL, 0xF5EE772E63C151F3ULL, 0xCA7C61881FB34058ULL, 0xFAB68ADCCF14BD25ULL, 
            0x7DDF8F75DE63550EULL, 0x6D8D3D29BF0464CCULL, 0x9F8EB50265A7DCFFULL, 0xDB0FCE1934E5A7AEULL, 
            0x4A6A97329A44470DULL, 0x6757D9F7307DB25DULL, 0xE284EA33543C2052ULL, 0x8464D8A3A7909D11ULL, 
            0xE8D3BB1B9452674CULL, 0x81B5CF713F96D19CULL, 0xD8FBF62103F2B42EULL, 0x40051697726F187BULL, 
            0x033686D2A1D02118ULL, 0xF2E72A0823F082EAULL, 0x432C6C251D814D96ULL, 0xF327CA98EF5099DAULL, 
            0x5D3D67100B3E7426ULL, 0x8505BEFE544EBC31ULL, 0x10494665EC26CFA4ULL, 0x6D127DB08531537CULL, 
            0xEC75E3F1EEC14895ULL, 0x5B68B99D2BE25BD7ULL, 0x40FA2BAFCC28A9FEULL, 0xF029F1C47B5EC912ULL
        }
    },
    {
        {
            0xDE6F2FD8A0B3424EULL, 0x7DC5A3620C40D85EULL, 0x2DF0A4F60990CC8DULL, 0x583F7FF5E7AEE2D8ULL, 
            0x91CC91B7E6FE288DULL, 0x84E6EBAC479D8845ULL, 0xE4DFF5B49F88A9ABULL, 0x21910EA7BB30DF52ULL, 
            0xCE76FC10CEA69208ULL, 0x2230C733E966E389ULL, 0x0EB8CE821D75B19CULL, 0xE5EC1D666B8D4C1AULL, 
            0x09A3F755C4EB0BB2ULL, 0xD8A4728DDFAA0B28ULL, 0x6E8986BACDDF75F9ULL, 0x0640D649E958EA95ULL, 
            0x0F91D378674DD062ULL, 0xA058D92038315718ULL, 0xD2FFDBD9A1810E16ULL, 0x98C7CA5FEA887B15ULL, 
            0xF0E302B9FBFB0337ULL, 0x1912D2D4BD4B5401ULL, 0xBCCD4757D25B0A6BULL, 0x9CD8648BCBF03054ULL, 
            0xD6B6C1D7F61F3FCEULL, 0x68C5AD19510B21E4ULL, 0xD449DD7D5B67EECFULL, 0x67A8E4323DF05B17ULL, 
            0x83EE44EDA4974517ULL, 0x4D7D20B921F3AF8EULL, 0xEBFEFD9CD5E41294ULL, 0xD592733FF2EAB043ULL
        },
        {
            0x21C76E0FDC769B1CULL, 0x4476F404248AF902ULL, 0x9A409D3ECC980884ULL, 0x4E3B5B0751303605ULL, 
            0xCBFFBC6BD7415646ULL, 0xD8CFC872DF6058DDULL, 0x898458BE10892E74ULL, 0x3DB8E4BF0FBA32EFULL, 
            0xD89CC1715A63077DULL, 0x8CD25C48766A845CULL, 0x5E3C09C7EE151EC6ULL, 0xCDF3D1FFB8117BBCULL, 
            0x0989759A07F4B1F0ULL, 0x5AA46C12F1E79C3DULL, 0x939DB622C8CFEF61ULL, 0x8C3B9B322B5C2006ULL, 
            0xEB04A97B04A6C7DFULL, 0x14520B84AF5A2D64ULL, 0xDDD4C29944EDFC0AULL, 0x084E14D0492D39FCULL, 
            0xFC038FF468FCA176ULL, 0x53148B0F706D0D98ULL, 0x23E435E14E1C515EULL, 0x5F32FF2460A437C5ULL, 
            0xC41F5C9E902CDCD7ULL, 0xBBD2FC1183E07602ULL, 0x36D6AA26AF30F737ULL, 0xAC0060BE26919750ULL, 
            0x6D5049C147985829ULL, 0x466F0B3D8B8F1F84ULL, 0xF61C5978F50FAA03ULL, 0xAAFE5567C72B2605ULL
        },
        {
            0x8D77071F20E74E19ULL, 0x520E3A3435056877ULL, 0xD8C0326BBABA18FBULL, 0x7D5E869A0C98F106ULL, 
            0x58CB6E29BED6E533ULL, 0x027D2718C04446A3ULL, 0x1CB250F31EAA10D8ULL, 0xBA5A6471201B0109ULL, 
            0x45A64B229D8225C1ULL, 0x44CF401AD7A08618ULL, 0xE6966DBD2C3225CBULL, 0xDD8F830C9F912C76ULL, 
            0x9CF7E719F22EAB71ULL, 0x0713CC27FD2ABB3DULL, 0x111E38F11E018236ULL, 0x2755C12F9A6FDCE2ULL, 
            0x4AEE3FC61D52FF5EULL, 0x437F68D952E4646FULL, 0x78E2046592437664ULL, 0x4808BB3A13B4358DULL, 
            0x09B000A9ACC20C2FULL, 0x4562A3C76D686E23ULL, 0x654D0055EFDBD5F5ULL, 0xE247E55A80A74AA7ULL, 
            0xCBC35889B6B0C085ULL, 0x6E6DE73C9376FDFBULL, 0xD946A79AC4E041FCULL, 0xD5A08865DB5D7608ULL, 
            0xFBAEF41474BCCE7CULL, 0xF3D9FED698690A3DULL, 0x84E461EAF3CB7A20ULL, 0x905A11684248E378ULL
        },
        {
            0x5097510FD9363A98ULL, 0xC0A908C415C618F6ULL, 0x942F95624F847463ULL, 0x6002633F9042C4A4ULL, 
            0x1B403259ACE5370AULL, 0x98B1605A7D1D1BE9ULL, 0xFCCAC7D553990546ULL, 0xF70A72EF79373B10ULL, 
            0xFBB9DA23BD61C572ULL, 0xFB82DDD8B77BC23EULL, 0xE8CB73A44621BA5FULL, 0x454DB0DC6B807FF2ULL, 
            0x42F99818BCB6B3DDULL, 0x2FB8EF446A497BBDULL, 0x138CCAC9E82351BCULL, 0x0296D21042DA1672ULL, 
            0xE286409EA70C5BFAULL, 0xFD0DD6E7FF698E95ULL, 0x3FEAB919C787100AULL, 0x7E32C1E6BEB32CCBULL, 
            0x58C887850075C9D3ULL, 0xB1D47B5DCCA5CDE8ULL, 0xFFCAF0E6DBAFC7E3ULL, 0x17304F71F199C9ACULL, 
            0x9AD345E3E98D8631ULL, 0xA09EC97760EDBD45ULL, 0xAB1BA1EAA6C95250ULL, 0x662A864A1F1145C4ULL, 
            0x2C7255A0D73204BCULL, 0x7C33B7DC5BBEFA2DULL, 0x8F50AFA9ECB986DEULL, 0x0FD6954AA0999CB3ULL
        },
        {
            0xEA727028E5030713ULL, 0xE070D29C06541178ULL, 0x99BEBF61A4DE7D25ULL, 0x88D4E5018D774A9FULL, 
            0x408E1A746443696DULL, 0x3793625B0857AA5CULL, 0x57D99F8EDBE6DBFAULL, 0x718C4DE4ECABB233ULL, 
            0x115FF4BAFDF8C800ULL, 0x4CC775A2C5294613ULL, 0x535EFCAA0F3CC1EEULL, 0x3AF1B002847B973BULL, 
            0x2A95915432389D45ULL, 0xEEC114AC2F4CAD12ULL, 0xAE4DA776C64856F0ULL, 0x3A080206F874DCDBULL, 
            0xC3B8EBFCE75656D9ULL, 0x6267F7C11633CA8DULL, 0xA5276F30D5DA4D3CULL, 0x464237287CD436DBULL, 
            0x95926DC143E6C7CAULL, 0xE881D7F5D0D72650ULL, 0x167B08DD27659578ULL, 0xFABD6D20549A491BULL, 
            0x92D8346D2583B28EULL, 0xA190A56790BE81E2ULL, 0x94F4B37CEEC58938ULL, 0xD94787E4746211C8ULL, 
            0x6B2C8C8FC6FFA173ULL, 0xB0E35336F1B22038ULL, 0xE3EFCAAF04A34F0BULL, 0x0520595F11B99CF9ULL
        },
        {
            0x1B1D9FAC49AD7B02ULL, 0xDBBC92B7547A2C74ULL, 0x329A1EC545380D12ULL, 0xF63390846498999AULL, 
            0x1D5D2AEB5FD10AA1ULL, 0x3A23684DB3B5DB9FULL, 0x1364D3985AC863A2ULL, 0xECA878BDF57F36D1ULL, 
            0x2502612EC795FB03ULL, 0x8CCF4F7097DD68FFULL, 0x976ED20A7DC530E1ULL, 0x4F7F21FBAC782DC2ULL, 
            0x51066E6322E2900EULL, 0x6824D31FE61F45F0ULL, 0x1E4AB3E6619DD112ULL, 0xC7ED5FF213CD4FEFULL, 
            0x30FBA8E6CB31E6D3ULL, 0xADD35082BD6E41A8ULL, 0x005629E9A18C38BBULL, 0x08A1DE880A4AEBBBULL, 
            0x663DD8265D4B811BULL, 0xBF5346C5D7502903ULL, 0x8BBAD82E2A114778ULL, 0xEFACE06EABE898A6ULL, 
            0x282E5E22A1EAC17FULL, 0xF298444DF0844313ULL, 0xB897F05210D958E6ULL, 0x8068C7A35A171FC9ULL, 
            0xE18A5097CD37005EULL, 0x6BC807A0B0B674E7ULL, 0x08F332699507DD0EULL, 0x1DB72FC193CA00B9ULL
        }
    },
    {
        {
            0xD20C5839EA44AF5BULL, 0x03F38F157314F96AULL, 0x24B195C725BDF6E2ULL, 0x6CBF76F3CA7EE331ULL, 
            0x39D9196D43D8B812ULL, 0x0A49EB0647071C97ULL, 0xC9B033FEA70C4A1CULL, 0x290C78E0B6FF6F41ULL, 
            0xC05B1B1EFB474B88ULL, 0xDCC6CF6C6EF7598DULL, 0x11799009758373E9ULL, 0x1F20BB9DA35F36EAULL, 
            0xF34BBF86253D1361ULL, 0x967A68B47519EDCFULL, 0x7A45E7FE8B7C37A2ULL, 0x6B163E4AC2902749ULL, 
            0xF17B1CA25C342A84ULL, 0x137CCFDD66AD1DF7ULL, 0x0D0F4BC65421715AULL, 0x695F532C54B134CAULL, 
            0x769EEDCB312E88A4ULL, 0x79BFE978685ECBF3ULL, 0xB00B194992A9A2E4ULL, 0xEBC1F797BFF3DE1AULL, 
            0xD74CA063B2DB8D92ULL, 0xD95BD639D0DDBE60ULL, 0xB512353A70263890ULL, 0xBF2DD778ED4FCD09ULL, 
            0x6F9AD0B439647AF0ULL, 0x0265870835245D04ULL, 0xDF9479E3910BB567ULL, 0x55560E046FB62F4DULL
        },
        {
            0x74275624BC93CA50ULL, 0x1D4B2AD9CA832CF5ULL, 0x49898B70F160877DULL, 0x2A4A5282C774F61AULL, 
            0xBFBB6B3592C9023CULL, 0x238034E82BE9EFDCULL, 0x83B72AD0BC89F700ULL, 0xB955CC5F631F271DULL, 
            0x5AEA2949070FF11CULL, 0x6D264F75EE29FB47ULL, 0x78923EA32B6F1CCBULL, 0x7DAFA3A0CCEB2EC2ULL, 
            0x2AD23C74DEF10526ULL, 0xFE6E3B8DA4166EEDULL, 0x6F82EBE2AE7EA3F3ULL, 0x076FFDC762105D68ULL, 
            0x54B73ADAE0F8DEC4ULL, 0xA8A9DDF07BF200CBULL, 0x82062A6B20440B04ULL, 0xD3BA7A199403C422ULL, 
            0x1FC1358767511C7CULL, 0xD6065172A8D8E575ULL, 0xE2C0BC5B6D6A1EEDULL, 0x3479BD95DDFCC488ULL, 
            0xA2C8BC5A8AA51C66ULL, 0x801BC5053885AB9EULL, 0xEFD67DD6790ACA5BULL, 0x7777EF794BF45B0DULL, 
            0xE3D2533A9A54459FULL, 0xDDAE0AD2AFB7F2A4ULL, 0x6A73F7D64F6E1545ULL, 0x3B7B5ECFF9C22C0CULL
        },
        {
            0x1ABA9DE09C42FCD1ULL, 0x4680B5365AC8D8E6ULL, 0x78240017B6774F0AULL, 0xF89D2C8C85D38083ULL, 
            0x87BA123E64983089ULL, 0x8E435B1B81A8C416ULL, 0xCDE422161B04B5C0ULL, 0xBCDA4A4020D98BAAULL, 
            0x13E9F32196391B37ULL, 0xCFD305EF1B9BA54BULL, 0xBBC960C7DDE9D171ULL, 0xDACD41457E1D2490ULL, 
            0x7197E20A6275CC7DULL, 0x94A1B64389288F3DULL, 0x6A5AFEC1A5DCD683ULL, 0xAC3324941F46F20EULL, 
            0x866DEE8785632264ULL, 0xDB594BB64AF7F673ULL, 0xBA80615FFD0A264EULL, 0xCFB947527F55B182ULL, 
            0xEB60668171879644ULL, 0x91DF4CCFD96ADF2BULL, 0x3D7F63C532E60B56ULL, 0x84B4C3EFA0185FF0ULL, 
            0x9606EF6FA3A076BBULL, 0xF236A2D4B0EB9C5AULL, 0x81485702EB7103B9ULL, 0x2BAB06F13C922277ULL, 
            0x4DFEEEAA16D1C0E2ULL, 0x49455F286B98DFF5ULL, 0xBCF891F551B33FCFULL, 0x5B3CB65BFBD3C9BAULL
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
        },
        {
            0xADA4A6574DE2B5D7ULL, 0x1611F1ABCA3BDCFBULL, 0x3A93656B9AAF9B64ULL, 0xB59FBD38B30E89C8ULL, 
            0x63594ADEEB79F566ULL, 0x6DC76F06DC7CC08FULL, 0xA52578EBDFB4466AULL, 0xD48CF67291A082BDULL, 
            0xB9B2097882F71176ULL, 0x304F138F11644E42ULL, 0xD682F81DCEF93DC1ULL, 0xB0E494E2596BE778ULL, 
            0x51AA2083082CDB4DULL, 0xA3E435B1AF660007ULL, 0x3E0267B1A2B83807ULL, 0x35B163CAFF3CEEEAULL, 
            0x7D8C4131DA5B4F69ULL, 0x76DC7AB67DD8B3C0ULL, 0xA9DE329E1242A568ULL, 0x9545DFC4FF0B8294ULL, 
            0xFCB379178F473DB4ULL, 0x1ACF60D5D827FBC6ULL, 0xECDAED930525D968ULL, 0xBF1F323CBF50EC77ULL, 
            0x1D93CA8625E3C0B1ULL, 0x89184F70392D2BB9ULL, 0x5EA82B7809737027ULL, 0x10567F3B008736BDULL, 
            0xBD882017DEFFB801ULL, 0xF1B3A9BF649A2CB7ULL, 0xC0D727131AC989DDULL, 0x03BAC3D200F2BB42ULL
        },
        {
            0x276A77A450332EEDULL, 0xDA90CBD14D529B8BULL, 0x630ADCF9632B37ACULL, 0x4C73BC62BDC578BEULL, 
            0xF945BEB94FDD42D2ULL, 0xA3BC7E595BF76029ULL, 0xF46FE31FB6CF72C8ULL, 0x652D90B612CC1E14ULL, 
            0x74F7C4C981A347A6ULL, 0x115E4A9D5371777EULL, 0x6985F111B8432587ULL, 0x45E450F5977FB568ULL, 
            0x63434B97E59566A4ULL, 0x8E300C1F61F01A34ULL, 0xAEF8C98D7A091EB0ULL, 0xD7DD312E0616D680ULL, 
            0x2BE6654A9C4D5B17ULL, 0xF79B268F44160E84ULL, 0x18391E1F8FB2F2E6ULL, 0x595D044E7A331618ULL, 
            0xE389E0EE499CE27FULL, 0x214002546BC75515ULL, 0xD073396C1FD611D9ULL, 0xBDD883722EDF0233ULL, 
            0x6AC863F3AC3AC42CULL, 0x708740822B52D0E3ULL, 0x5671FF2267693301ULL, 0x98D0F9F2BAF60D98ULL, 
            0x7C6207DD445E644FULL, 0x4995786B083E31D4ULL, 0x49FDD158309F999BULL, 0xB01848A5A6DE08EEULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseBConstants = {
    0x1D30A090259BCE62ULL,
    0xA49C561ECB1EC182ULL,
    0x1EBB5443E428B600ULL,
    0x1D30A090259BCE62ULL,
    0xA49C561ECB1EC182ULL,
    0x1EBB5443E428B600ULL,
    0x7AAAB04007D5D784ULL,
    0x93D3E99B93EFB34FULL,
    0x04,
    0x04,
    0x5E,
    0x37,
    0xF3,
    0xE5,
    0x92,
    0x2F
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseCSalts = {
    {
        {
            0xAD9D49A67FD41504ULL, 0xD8B0012F02A50303ULL, 0xBB8066ABA039487FULL, 0x6258A9130F5647D9ULL, 
            0x1B2AC0852963ECD3ULL, 0x2F01DC35C416A0F9ULL, 0x95DD7F14827AB015ULL, 0x6CAC3B35A8F1A57AULL, 
            0xEEB12D667EA2518DULL, 0x7AE481BE9B051555ULL, 0x74146532EA2DDB5FULL, 0xDD07C976500D3BD3ULL, 
            0xE5C3FFA2E40C4146ULL, 0xFDA9F40A4F08F6D1ULL, 0xFEAB715D2E425B01ULL, 0xCFB70484FBB6CB40ULL, 
            0x5C0FD489B9248910ULL, 0xC4BACBCDFC7DDB83ULL, 0xD8226E66069C2205ULL, 0x13952E133F19D3D2ULL, 
            0x74ECEDE3763E33F6ULL, 0xFA117813949F4AEDULL, 0x707AC6FA722B7477ULL, 0x6D677F7F511A5C3DULL, 
            0xA2E883CABE1FD5AEULL, 0x225297190FEDF4BEULL, 0xE6D17CC7D1EA4DFFULL, 0x6C6269FC6B8AA7B9ULL, 
            0xD3400176943FFFE5ULL, 0x895303F54276C3CBULL, 0x8086BF945A56D626ULL, 0xDD6C3BCF7DA54E03ULL
        },
        {
            0x6DF82C70056588FDULL, 0x19EFCC25C126078FULL, 0x3E584E857DC701DFULL, 0xB18E896A61502802ULL, 
            0x7CD5BD64EF8F887CULL, 0x53437ED6D31FB94AULL, 0x2E3BBC0C5FCD23D5ULL, 0x13F29BB419624E90ULL, 
            0xEE7B3D6C1712CACFULL, 0xD68DDAFFC25DD6FEULL, 0xF2FBC1C72B6C7879ULL, 0x9C2D16C42D9B673EULL, 
            0x0D7D52A6CD76DAF5ULL, 0x0ED184F4FC43EE98ULL, 0x85FC07FD8CE14335ULL, 0x6A16AA14793277E0ULL, 
            0x250D1C3BBAFCA7A7ULL, 0x5FC25A48620563FAULL, 0x9B7DEC3550917E66ULL, 0xDDBEE2A149ED18CDULL, 
            0x9AA6B0FD387FA3B5ULL, 0x7B9B31D6347D2C29ULL, 0x248CA44605B63518ULL, 0xBB7C9906B17957CBULL, 
            0x9BA6E157AA0AE30FULL, 0x4040AABD9FA57960ULL, 0x8842944DD8AB8A76ULL, 0x9D43ED7202FB0CE5ULL, 
            0x0171D02877EC9FF7ULL, 0x35B017418C35D5F5ULL, 0x16A0DF7B91392D6EULL, 0x898AB8F15E8CBC41ULL
        },
        {
            0xD86E82ED060542B9ULL, 0x8556AB9F793D3E1DULL, 0x068F0B455F9A3568ULL, 0xD78D33AA37561877ULL, 
            0x18DCB123D44FBCE1ULL, 0x358CB02181BCAB4FULL, 0xF2A70F58D51E7C0BULL, 0x192974F4DE212C2BULL, 
            0x2823CCF3217AC293ULL, 0xB3C645A6BB66A35FULL, 0x1D70B2129C3DD7F8ULL, 0xD7A9FCBFBB486DBDULL, 
            0x200E58CDE971FBC0ULL, 0x2A574053304137F1ULL, 0xF9BD9B812055C6F7ULL, 0x89C518477C54572EULL, 
            0xB08B2CDAAC428584ULL, 0x7CAC7F1FD178422FULL, 0xBBDF9D05A1D7FC8DULL, 0xB9C085711F80C68FULL, 
            0xB776C8B2F255A127ULL, 0x1F14DECCE363F424ULL, 0xCD2633BEFD295627ULL, 0x4B4DFEF1FB4B7952ULL, 
            0xEA5C5370BB1FCBF8ULL, 0x31803982BC83CE1AULL, 0x1C02E138DF730CC3ULL, 0x1B549CDDA5A0BBF4ULL, 
            0xC8191E39782B98D7ULL, 0x592A94AC9392BA9EULL, 0x7129EA8E7C956462ULL, 0x85748F19A4EB9F74ULL
        },
        {
            0x06DD9966FD7FB64DULL, 0x18DF2C30C2206558ULL, 0xF1DE582D9686FB82ULL, 0x11C2B5F092553061ULL, 
            0x954E63981D67C55CULL, 0xCF8ADFA94428EA60ULL, 0xE12484DF2280D204ULL, 0x13665C46FB65BC51ULL, 
            0x4912E82D29109CBCULL, 0x5B7C521DCAAF58D4ULL, 0x2F0699BE8ECF60DAULL, 0x077A38A547F60B97ULL, 
            0xB2FA2F8F8BA85D93ULL, 0x443491708E36CEC7ULL, 0xD8598BC437368997ULL, 0x80EF3C98F831D64AULL, 
            0x662DEAAE82056123ULL, 0x551A50F459C4597EULL, 0x315A04BB30D8841EULL, 0xD33632AED19AEE44ULL, 
            0xB261CFE146EE31B1ULL, 0x6268AAAF7BFA48E8ULL, 0x018F520D46862ADBULL, 0x263DB0E4A47CB9EEULL, 
            0x5A74D24271358B57ULL, 0x4A4B777D2A83CD26ULL, 0x33ABCFD426BF8F56ULL, 0xCF902CBCE25C6C9DULL, 
            0xB71D20C824CC5E98ULL, 0xE57986C5E78B537CULL, 0x842BACDE1D67DECEULL, 0x4AB9A6587E25A506ULL
        },
        {
            0x80FB2AB3A9224B7CULL, 0x8C8594AB88AAC302ULL, 0x3691DA519118746CULL, 0x647404146AF6D327ULL, 
            0x34F0CE6CFEB645E7ULL, 0xEAC95148BF2EAD3DULL, 0x3BF4273ACEF3E776ULL, 0xED9C990A229805AFULL, 
            0x575410620A1229D5ULL, 0xEEC6D11641091B3CULL, 0x7597E0C3CE41A270ULL, 0xC17AA7F0FF78FF6CULL, 
            0x1AC364BE95ABFB3CULL, 0xE0C05C0E42991687ULL, 0xE53DDE4E9F0FA574ULL, 0xCE40E02337A9106CULL, 
            0xEC267C65E23FA3ACULL, 0x95667B645755D98FULL, 0xE63BC07CFF94BFEAULL, 0xDB65AEA12E81E9E7ULL, 
            0x848E07711EDDEF62ULL, 0xEFDC1B5C87748F5AULL, 0x21E11B7ED8B4FE8BULL, 0xA3212583EF989635ULL, 
            0x42D5D518516DBFBFULL, 0xF50592769C3B5304ULL, 0x9D65A950C01A68FBULL, 0x634C28C076D6D253ULL, 
            0x79963524971022F9ULL, 0x9157D807B7633630ULL, 0x4DEB15C3845863A5ULL, 0x735C59992962F6E4ULL
        },
        {
            0x085E4AA19B316C34ULL, 0x96BB6C2DEF528115ULL, 0xB444488E92A0C237ULL, 0x496179ADCDAB57E2ULL, 
            0x8DC8A9F2A2813893ULL, 0x7F2070AAD81E684EULL, 0x721BA7A62B196C5AULL, 0x102BB7225EF6EA48ULL, 
            0x4E5E9305BF9B5263ULL, 0xA5C7698BBBF6C59AULL, 0x118DA4168EE5D177ULL, 0x707B9355A183B010ULL, 
            0x9B98047672F3629CULL, 0x74694A32BDF62943ULL, 0xA87850FF8B11719AULL, 0x83248A6D274EBDF8ULL, 
            0x02D4319C228C46EFULL, 0xC3838E116C1F4E90ULL, 0x754D5F86F0B4F735ULL, 0xEED45AC52A9AA421ULL, 
            0xDCD51FFF4D4D32D2ULL, 0xAFB7162B8BAF5646ULL, 0xF110403232DCDA67ULL, 0x00D47BEB3808EE30ULL, 
            0xE80968E130691E1AULL, 0x8AC41335E87FFC0FULL, 0x8B7FF849C651CAF0ULL, 0xA5ED4EC518BACCA1ULL, 
            0xC610FE70C31D72EAULL, 0x909661F596C31C85ULL, 0xC40A15FF62A4B45BULL, 0xEC6C760CABA239AEULL
        }
    },
    {
        {
            0x8F8363741FF61F83ULL, 0xC8989C280FF78D30ULL, 0x9A7031603C887098ULL, 0xA7C7A3B9A3A4BB2AULL, 
            0x48889210783DA909ULL, 0x8EE6252531F6F4E4ULL, 0x68FEC409EB2DBE44ULL, 0x5AFE510F1A96A532ULL, 
            0x6A41B7579AB1B50FULL, 0xD6CE27A0134678ACULL, 0x53D001E133979605ULL, 0xA5DD3643E1D0F7E3ULL, 
            0x413DE4FEA4A7F386ULL, 0x719E748EF1F888DBULL, 0x00D830635FB0054FULL, 0xA44BC238DDC1252FULL, 
            0x8F07BD5AAA0D5DADULL, 0x2590091DCE4E29E3ULL, 0x5EE0353215F91BCFULL, 0x777A98617FB4F92AULL, 
            0x5A406A6A2F949A18ULL, 0xB887918F5BCAC4DDULL, 0x44B8C5168319C831ULL, 0x18FC5A525E50FBC4ULL, 
            0x4257D5B2284A60ADULL, 0x6552EDF624F7EE1EULL, 0x6465B5C0A4919886ULL, 0x9747171F1B58685AULL, 
            0x8B560731EDFE928AULL, 0xC55B4ED1DD1F67E9ULL, 0x6B31186D0C5DD1DBULL, 0xBB97FB6E3B45600BULL
        },
        {
            0xC719C0D19E82E746ULL, 0x8430821EE5B7EF32ULL, 0x20E90940258343A1ULL, 0x5548B8B9C30DB6D2ULL, 
            0x9DBFAD43983E4F29ULL, 0xFDE8D4D0F06CC94BULL, 0xD32A77B29AFB675CULL, 0x3A0B6673D3087FD8ULL, 
            0xE1AAF2BF2716482EULL, 0xDB57BAAC04B77751ULL, 0x7848535E13590EC1ULL, 0xD63FDFB458977438ULL, 
            0xC6FE2723DFAEC522ULL, 0x32621BE4EC7EEAC2ULL, 0xA4B3A90B717774CBULL, 0x0718F6BAE3A98A56ULL, 
            0x01A02E9F4EE96CB6ULL, 0x84CF4BEA6AB6095BULL, 0x90683C8FC22929B5ULL, 0x5267308645F265C5ULL, 
            0x70237349186B4E77ULL, 0x6FD64796C9765BF7ULL, 0xC4FC0DDA24DC2487ULL, 0x3832F356781EF45CULL, 
            0xAFB7FACA3A5D7CBBULL, 0x56C65D9EB4FACD2FULL, 0x4CCFBE0C76714809ULL, 0x26ACE1211601F621ULL, 
            0x067DD01A3B73C876ULL, 0xE54C5F2DD2E209AFULL, 0x5C701D21CD274900ULL, 0x935663B622D8946AULL
        },
        {
            0x9A39FCCA61E2A7A0ULL, 0xD3852B7533051F1EULL, 0x2429D1534E377C94ULL, 0x4932FCF2E22D4A01ULL, 
            0xB29FC3F191BAD603ULL, 0x8DA5BCADB4B4D1A5ULL, 0xFC4BD4C60A27BB16ULL, 0x87DD829C12F394C3ULL, 
            0x1839AB77F8080E52ULL, 0xC19E0BFFFA73C477ULL, 0x4555BDB601E7812FULL, 0xCCA109C909B48F58ULL, 
            0xB930DD2E01FBA3BFULL, 0x6D47DA22FBBA67ABULL, 0x7D769A13332CBC78ULL, 0x80BC46CD23986CAFULL, 
            0xAB14076FA3B6D28CULL, 0x56C475B81C1C80F8ULL, 0x3D65404B244A3E6FULL, 0x9215732F958CAC1AULL, 
            0xD419ABB051D5B075ULL, 0x6B3CC35799F10DFAULL, 0x35A1892BA3FE6192ULL, 0x924624154B3A1D96ULL, 
            0xBCBAC59A39CF7903ULL, 0x03AF14B7E9BF0432ULL, 0xC587C7F75F65945BULL, 0xD8F782110D8E8B8BULL, 
            0x30AD7C808C41D57BULL, 0x14B7015FAB5438E1ULL, 0xCDDBB82BBC17D0E8ULL, 0x2A9C81E40589B4FDULL
        },
        {
            0x1D11062D41B20BB2ULL, 0xBEC34004FB19AB4AULL, 0xB2826A77CC1B7D78ULL, 0x5B00899AB9624B61ULL, 
            0x9427AE74BDAE5E35ULL, 0x1DDA6B44F876673DULL, 0xAEE2D84CF61A5A0CULL, 0x719647EC080273D4ULL, 
            0xE2B1A6E4C6583A14ULL, 0x17C62C3C78AD1404ULL, 0x71DA8E41389A1C61ULL, 0x1D693FD90C577772ULL, 
            0xBBAE18D6529DFA3DULL, 0x1BC40129AC8C817BULL, 0x0D619F9210BDD984ULL, 0x1C2DF7C558C08A4BULL, 
            0x23F594B081B6727AULL, 0x26A18862ED73A752ULL, 0x0A8A293ACFF8981FULL, 0xB220B1A187793560ULL, 
            0x2A845D7324F08780ULL, 0xD90D4EBCFEBACCABULL, 0x2132B5D1C969983DULL, 0xD1847FE4E15932BDULL, 
            0xAC2A87FDAAC6C31AULL, 0xBB5B85815E377F63ULL, 0x2EB06E17C6849DA0ULL, 0x4B6F02A47AA85A42ULL, 
            0x48136705FEDE477AULL, 0x99148972C977049CULL, 0xFAC38469A6521F36ULL, 0xDBA37335304DA22CULL
        },
        {
            0xCCFB5BF8B9CECBEBULL, 0x0B876D4FE44F4EE2ULL, 0x78BC575B5F1B02F8ULL, 0xBB583331DD0FAA71ULL, 
            0x9BE7B38AA470CD11ULL, 0xE009D37D8376A981ULL, 0xAC5197A46964AE66ULL, 0xA2F6649BF25132F9ULL, 
            0x7312C186AD384F23ULL, 0x00AD20D992C7FC83ULL, 0xA2E83CC5B3C35C02ULL, 0xD836F21BCB2DA0F5ULL, 
            0xE5A664F14F38F03BULL, 0x2E88D6DB4A5E928CULL, 0xAF9A758C04CD558AULL, 0x16152415D2A884B9ULL, 
            0xB8311EE754F4BDADULL, 0x289A04113F252C7BULL, 0x6CB57855B3D7621DULL, 0x4A6405BA2223BA19ULL, 
            0xCC788C639458C435ULL, 0x2B196EE6F478DE9AULL, 0x0D86F255739E34FDULL, 0x72A73F7F03AE2B70ULL, 
            0x6B5A3F3795E10B23ULL, 0xC3437EEF6F747063ULL, 0x08B63283F1FA60D4ULL, 0x876C13AFCA078C62ULL, 
            0x830EE6EF6314F9ACULL, 0xE06CB1E6BD2F40E0ULL, 0x28A1314958B67058ULL, 0xA5F5AB581C78FCC5ULL
        },
        {
            0x625DFF68A0DD67C4ULL, 0xD44C78475563A1ABULL, 0xC8EEB1965E841795ULL, 0xD7F56574833DD698ULL, 
            0x1D35DA2042613A57ULL, 0x0DEBC6FD36689D4EULL, 0x161ACEEF6FDEE390ULL, 0xD8AAFF147A6BDE55ULL, 
            0x607D9E53A41781D3ULL, 0xBF5456B818FB9181ULL, 0x2FA523570B5EA976ULL, 0xAC445633A93A3EDAULL, 
            0x59B3CCCD1F0FF624ULL, 0x6921C0D3A185FCD2ULL, 0x7A899E9F4759270BULL, 0xAA4E10E4AA19FFB5ULL, 
            0x616BBD44E08DBC68ULL, 0xCCCC934F04FE2F99ULL, 0x229045D005842837ULL, 0x448AE41272250528ULL, 
            0x2C8712823324105CULL, 0xC0CEBF1F784CCBB7ULL, 0xDA26BAB1ED38B6FFULL, 0xA6F38C7B3A336BF3ULL, 
            0x8B177ED167E7F33DULL, 0xE4F8E150891D1297ULL, 0xE2972F38D0FCDF52ULL, 0xE81995E6C4C7A7E1ULL, 
            0x0F324E61329BCEC9ULL, 0xC31ABA0DAD1965D3ULL, 0xEAED13B26ADDF4E3ULL, 0x924B49B604BEB520ULL
        }
    },
    {
        {
            0xF61766231FD3E650ULL, 0x8123858CC4B36AF9ULL, 0x6C62A2A85D3725DBULL, 0x589F7CB4A1ABB701ULL, 
            0x7377A2D89BEDA813ULL, 0x1D1E5131E16982E2ULL, 0x31B9825DA89EBF82ULL, 0xC3FBD2D4F9413982ULL, 
            0xF9759CBB05CDA496ULL, 0x5ED8D10ECC8E6790ULL, 0xCA0DA44048BC9E4DULL, 0xEA4502096CF0CCC2ULL, 
            0x2D0953E02DE72B31ULL, 0x1A4312EA19980395ULL, 0xBA05A0092B211211ULL, 0xC730B7B3C2AB97D1ULL, 
            0xC43BDBECEEAF9159ULL, 0xD4C8A7FD3EE5B512ULL, 0x0F8C1503DB492D37ULL, 0x0BE369C98229DB85ULL, 
            0x8EB12D949CE8E2A9ULL, 0xB1DDDFC6386436E3ULL, 0xA08578C0990926DCULL, 0xE60153778E5E995FULL, 
            0x685231C18D477700ULL, 0x19E45BB318228752ULL, 0xDF912C130EA76742ULL, 0x43B8C9CF0D16B777ULL, 
            0x799B9F948CE85399ULL, 0x7F2C73332B1B6219ULL, 0x2B9E4A0D7BB1C6EEULL, 0x35B14958675E22A4ULL
        },
        {
            0xC02FFFC199A55FD9ULL, 0xF14FC05F6C3AAC1EULL, 0x13A43CA37CD74B15ULL, 0xBE88855B6CA04CDBULL, 
            0x065DDD814DBB21E4ULL, 0x74425353F4B5BF3BULL, 0xB301AF37F64D2DE8ULL, 0x1542C1CDA08AC4C6ULL, 
            0x6089CB115F189B2AULL, 0xB4CAE92A4F28B43DULL, 0xCB3B068B84318A9DULL, 0xF8D48EACAF1DF5C0ULL, 
            0xA548F1C7394CBA8EULL, 0x9468A65DF4ABC97BULL, 0x53CD1064B845CD93ULL, 0xC0EC07EEE67250B9ULL, 
            0xD289EF8869E03C0AULL, 0x80D1576DEBB52E7DULL, 0xD07E7EE7326F0AEEULL, 0x5EBF257451CF2F84ULL, 
            0x0194F9073E47D802ULL, 0xFC427DC1833F931CULL, 0x082D21F5571F2A36ULL, 0xDC5EE56789454698ULL, 
            0xA635DEA28A5D3E05ULL, 0x9E69E9EA7759C69DULL, 0x2629368ED86835CBULL, 0xA3158E8BBD1A0196ULL, 
            0x5F98F1B695E8D969ULL, 0xD372059F9D7C9C3BULL, 0x49CC298E5D6D2A3FULL, 0xBFBA8662FEE8E465ULL
        },
        {
            0xCEDEC7D28C88567FULL, 0xFAE12F6C56EAA19AULL, 0xCA9A12D2DD95CDE1ULL, 0xA04E0C569A7CC9DEULL, 
            0x985779EB86360CD9ULL, 0x69966BE8D717B2A0ULL, 0xD1B38FA4BD4CB6C6ULL, 0x43BDB6F9205BC6C0ULL, 
            0x5C83780399BFC50EULL, 0x6D518FA0A555E2B8ULL, 0xB12B8C867E281BB2ULL, 0x45F6B9F5C6A14980ULL, 
            0xA6683BB2E5A714C0ULL, 0x07FFF1E05992DADBULL, 0x2D16646B945F39C3ULL, 0xABE0873393ABECDBULL, 
            0xCDAFFC3494517A99ULL, 0xAD9FFA5537D70FABULL, 0xA3C9AE0B0B94B7B2ULL, 0xFDDBFB7C1076AAD9ULL, 
            0x5F4A5BC5FCE5FB40ULL, 0xD99D48D597DB8852ULL, 0x86B7FFD25161F244ULL, 0x00ACFD878F384AD6ULL, 
            0x30515CBD8D64D48CULL, 0x5BE3516ABE6145C5ULL, 0xD02FA8BA38186BEFULL, 0x81C9C3E249E7550AULL, 
            0x0600D625D369C229ULL, 0x7462C9876D70D20AULL, 0x48606755E9B21AB1ULL, 0xE70ECEB0A825FA82ULL
        },
        {
            0xAEC33CFC93DC60A3ULL, 0x0DDF73ED93B35DDCULL, 0x9C82EB4E21918E43ULL, 0x1F3CE86A26AA347FULL, 
            0x1D25A04DEFCEE8E9ULL, 0x635BB546639B0B9CULL, 0x5C13067580548BFEULL, 0x516AC912CAC5208EULL, 
            0xDA1BD17C55849942ULL, 0xFE4FCA2DDD930429ULL, 0xC680442A359B21CAULL, 0x8C3CD8A88A8DF186ULL, 
            0xA7B3617AB76010CDULL, 0xCD4E251C2B278D38ULL, 0xD7512E5A816A4662ULL, 0x5560FD3097BAEFA3ULL, 
            0x7AB47BDA82282E04ULL, 0x10B2F82C62C44A13ULL, 0xEF9CA91062FD88A3ULL, 0x6AB8E2CE91E0F65EULL, 
            0xCBF3BAA75DA32B36ULL, 0x6E023B80508E006AULL, 0x250DEAE5B1BFE6D5ULL, 0xC1CFBA389B8C8DCDULL, 
            0x3BB7EC62A3A6E2A0ULL, 0x34B48A413129BF0EULL, 0xC3ED88FADBDC5A92ULL, 0xFA80F7DFF92F5A0FULL, 
            0xBA1C3F35C4772C7EULL, 0xDC9B4672727FE436ULL, 0x489866F1D714F42DULL, 0xE68EE6BD8D59DAEEULL
        },
        {
            0xCE7D90B0FFDBD201ULL, 0x897DB753FC1EC654ULL, 0x1918BFCB47E5BA72ULL, 0x55FABA00BDF49F94ULL, 
            0x8E56691415F29FB1ULL, 0x51660C15F51A1278ULL, 0x241D116F1BCF5A3EULL, 0xECC18377B7BAD30EULL, 
            0xF877E8C93F5FFFF0ULL, 0x7C079AB1CA19859FULL, 0xE5730D3222D2A2C3ULL, 0xCA06F3969C2987E3ULL, 
            0x43B72C66B863F99BULL, 0x5A4466AF4FEEC5B8ULL, 0x04169874746408F9ULL, 0xBF73B69D36E8A9FEULL, 
            0xA85EBBA4533FBCA9ULL, 0x11C8538BA69F5865ULL, 0xB8CD02D69D78E97BULL, 0x68C4C92A5425AA43ULL, 
            0x385EC0AE37A004E9ULL, 0x981E3280B014008AULL, 0x259EDA15B8238949ULL, 0x2F6DA2F12B44C4DBULL, 
            0x54DCBE174127C756ULL, 0x5ACAD4BF56420337ULL, 0xEFFCA802833A38C8ULL, 0x5CE3659B9DB16D5DULL, 
            0x852EAB3C4891E678ULL, 0x835D5ACB4D1C4477ULL, 0xE9281A74A586A167ULL, 0x0F0CD84B25A77C1EULL
        },
        {
            0x501AD3FE3D8BC2C9ULL, 0x0B9F4FDC670DF7A3ULL, 0x9470020F09390108ULL, 0x17EBA04295FD4751ULL, 
            0x404A1827A0CB5043ULL, 0x979D3042251F2159ULL, 0x66B7BCBDDF947010ULL, 0x8423415CDD64F5DBULL, 
            0x251A515C165F9346ULL, 0xDA901D1201B47901ULL, 0xAF670A18E88DDC8DULL, 0xF44B77DD48CE82DBULL, 
            0x64841E419BDAB259ULL, 0x13D9654A10D30561ULL, 0xB4892305072BB641ULL, 0x6FE25ABCD1492CE7ULL, 
            0x2B9B88E007C77C35ULL, 0x2469CEADB4E2C03AULL, 0xCD538B652E618738ULL, 0x46E22DE6E52B100CULL, 
            0xF91D35DAC9D1431FULL, 0x06529D955D0A6BCEULL, 0x28579FD93F1ACC92ULL, 0x899C8BE59CDC6359ULL, 
            0x89DD842A710302F8ULL, 0x76E84B6001C7E211ULL, 0x1C4E05621A2532F7ULL, 0xEC60775EEBF270F3ULL, 
            0xC5B8B497B0A9EEC9ULL, 0x4F87EFD8EE4EFFF1ULL, 0x30DCCAE196F5C15BULL, 0x8B31F29690E7D575ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseCConstants = {
    0x5E6ED6775A555B56ULL,
    0x8C2C6A2B903473ACULL,
    0x6820A532CAEFE689ULL,
    0x5E6ED6775A555B56ULL,
    0x8C2C6A2B903473ACULL,
    0x6820A532CAEFE689ULL,
    0xBA5262AA45444E2EULL,
    0x850EF6E9C3A990EEULL,
    0x82,
    0x55,
    0x6E,
    0x51,
    0x04,
    0x10,
    0x40,
    0xE9
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseDSalts = {
    {
        {
            0x6577C8E3AAAA3A2AULL, 0x1CAAA639807E6A01ULL, 0x4C7FF66122D79D22ULL, 0x88385F494053B658ULL, 
            0xA107A5A494534AB7ULL, 0xF2B8FC86012040D5ULL, 0x0DAFF95FB303CE53ULL, 0xD79271DFC9448480ULL, 
            0x98AAA1FEE2D92506ULL, 0x1B63F247957B643DULL, 0xA0D8E940E8DD33A9ULL, 0xD67FD37161E73FD7ULL, 
            0x638545047FF2FF8DULL, 0xD820C0E889941849ULL, 0x54FD4BA58AFAEFE1ULL, 0x2C7D9A1AD006A207ULL, 
            0x6889481C1682D9EAULL, 0x7154D10D0C3875F4ULL, 0x617767459E69EDF5ULL, 0x29EE9323071047FBULL, 
            0xD411CF5A5EFB85B1ULL, 0x6719D3BB49CC4ACDULL, 0x3E55F94E1AD1C790ULL, 0xA2653DC2DBDDC1E3ULL, 
            0x7528DCE3DD30B3DEULL, 0x54E1559CF5211476ULL, 0xA743395EE05DB30EULL, 0x0A3CB6AA56DB6A2FULL, 
            0x85E6F132835CDA10ULL, 0x5882D92E0B085FA8ULL, 0x6ADF99258F573125ULL, 0x9287FF68C0337F4FULL
        },
        {
            0x748A4A15542F45B1ULL, 0x4F1068496DDB0EA4ULL, 0xAEBD5C8A46CBA23CULL, 0xB9F5BCFFAD23ABB4ULL, 
            0xAE8E83F76E4F4C2BULL, 0x45ECA48B7C44AB41ULL, 0xDD0D974B1216BC9DULL, 0x873C11BED1A27FF8ULL, 
            0xE7B095B2A14B529AULL, 0x6EF0B63DD74E8087ULL, 0xE739A8A82EAD0EB0ULL, 0xA3825D0FA96D8443ULL, 
            0xDEF5A16251C7C35BULL, 0xE0FBA072D1BF3852ULL, 0xA711F5A5B042FA1BULL, 0x9A6944E53192FFE7ULL, 
            0xD703F8DC3967A861ULL, 0x32A1810C2234E520ULL, 0x2993B0E4A465B845ULL, 0x7B847179E8D11D8DULL, 
            0x9DC6F7B3F9552BE7ULL, 0x14614C606B08AAE9ULL, 0x0857EE73A8C9B793ULL, 0xE7F28BAACC554201ULL, 
            0xB60DE49C38169545ULL, 0xAEF96CD5DAA55A02ULL, 0x50DD53A728953750ULL, 0x1F58B0FF9719E689ULL, 
            0x24DF560EA3A3E4ECULL, 0x6B7289B8C9B5C830ULL, 0xEEDD1B6DF94A42EEULL, 0x6ACD31A7C685E270ULL
        },
        {
            0xA0FB9C2A040E027CULL, 0x19D75A6EA9A70483ULL, 0x723210C91D694B36ULL, 0xD55030ADBCAEE225ULL, 
            0x354A9965A8362DFAULL, 0x5CF3FFE785A9ACEFULL, 0x11F1780A42D6763FULL, 0x83A644DE44BC35E8ULL, 
            0x9D2B85960251F3ECULL, 0x2061363807640301ULL, 0x3ABE496647C65DCDULL, 0x43D5CEE6EA7D687AULL, 
            0xC134F4EC7183C08FULL, 0x1D30565E942A5A81ULL, 0xF0EE44D5964C73EAULL, 0xEC25C54566CAFEF7ULL, 
            0x70FA6EDBCD0E9DC4ULL, 0xBB14C4176A9FA162ULL, 0xCAEF2E0C69D259D7ULL, 0x822F486AE1FEAF73ULL, 
            0x33725E57ED10E572ULL, 0x4C0AB4A25AA4BEB1ULL, 0x89B63A9868CF1AC1ULL, 0x9E05B11B9B945E4BULL, 
            0x1E1585A18640A2DEULL, 0x2F92DCED8C141D76ULL, 0x3E9737726C0DDE81ULL, 0x86B4CD35247C5FAEULL, 
            0x274FC7A84A563FFEULL, 0x71A83720731A662EULL, 0x145ADE6224E1F314ULL, 0x7DEAC4E258D7A57FULL
        },
        {
            0xCB995CF6FC5DB8D5ULL, 0x3BF016A6464B793EULL, 0xBF82F349CC2481AAULL, 0x8984D27A8D96C4EBULL, 
            0xBC2032642B250786ULL, 0x99F5F7459F97778DULL, 0xCC331A5BAACCB0D1ULL, 0x5DDEFD64D4606BCFULL, 
            0xF88ABE2FD462CBA4ULL, 0x26C6822C06173561ULL, 0x884CEAD3CCF051ACULL, 0x0B7D89B819F0AC93ULL, 
            0x1091C31517B05C88ULL, 0xC81ED7113A14A20AULL, 0xBA1B5032CBE944A1ULL, 0x5764FE2686D6D79BULL, 
            0xCC31FA15ADE33702ULL, 0x8ECB6A5D7D8503D2ULL, 0xB102F5D031D3BE84ULL, 0x3CCB0F9982B1ED3BULL, 
            0xAFC84B9C829734B0ULL, 0xF4077F8B0223644FULL, 0x017BF11395FAB3CEULL, 0x0AD654CF0B8A9C02ULL, 
            0xB38A9C9633C771E8ULL, 0x5BA83CB335CEDBBBULL, 0x1A9B382DE1906865ULL, 0xFFA76E6E9A021D27ULL, 
            0x68E6FC765F5F44EBULL, 0xC4C7F5C49038094CULL, 0x721903F2059C69D8ULL, 0x323CE186B20A2A09ULL
        },
        {
            0xC5A65622582BE09CULL, 0x817FA85AEB788E49ULL, 0x9D6974F248AC0308ULL, 0x58570C691020764EULL, 
            0x795FCEF722AADEFAULL, 0xE62CBD4D652DD21AULL, 0x2A78E63C8C3C4FD7ULL, 0xDDFCB899CA7759D3ULL, 
            0x8A6E1D3D0B2F4F9EULL, 0x6C95A3E0ECDF87A5ULL, 0xE2497706587E6C21ULL, 0x6B98790B82FA1ECBULL, 
            0x6EED8BEFECA0875CULL, 0xEA6183B3EA5E05B2ULL, 0x7E9D8349FFBA65C2ULL, 0x728BD1C90F374F53ULL, 
            0xB9FD682BE564CC3EULL, 0x95E12C4E3F51AAF6ULL, 0xCFA5D4007D727D5CULL, 0x0BAFE1778FD33133ULL, 
            0xB880B6CF25813672ULL, 0xB1EB75AD037A43D5ULL, 0xC524416BB92A5909ULL, 0x9F094E4C31D1B664ULL, 
            0xF5AC75056D94DB92ULL, 0xC095239686893A69ULL, 0x05BA2FB0CA99997BULL, 0xDFAEBB8A469C5A12ULL, 
            0xDBE986E0FD4C3E4BULL, 0x2DB81740475057D7ULL, 0xF7AA19AA20384FFDULL, 0x623C4D6767996DD9ULL
        },
        {
            0x3D1657D6AC3E9AB7ULL, 0x30A1C4270FED4923ULL, 0x27A5D692ADA94748ULL, 0x8C9FE98478D908D0ULL, 
            0xC70DF3A8D05CDBA2ULL, 0x26B46B140A599423ULL, 0xDB66B5DB8FAC5B50ULL, 0xCF821716FB47E22AULL, 
            0x6F468B90D8220E73ULL, 0x0A95B500DEEF165DULL, 0x851469B77B5AC283ULL, 0xD2192C7883F40CC7ULL, 
            0xB4ECE4CE85AF6213ULL, 0x4B9F88AF4062A693ULL, 0x3BA1046B6FFCC6F7ULL, 0x969AA24E9E31B3F8ULL, 
            0x084B32A482FD86B6ULL, 0x8DDC9625270233C2ULL, 0x947426735D937E05ULL, 0x4A232FEF253A1A0AULL, 
            0xB9D95F20864A8C40ULL, 0xE1393C3331CEFC6BULL, 0xE2F60F07BCBC7166ULL, 0x7C27DEEFDB73A0ACULL, 
            0xEEB552AFB906EAE5ULL, 0x080B69621F0ABFB0ULL, 0x19D1FAB7023E4A5EULL, 0x059603FD4B2A8D3FULL, 
            0xADA025DD9474214EULL, 0x5C52BA73B6CDE333ULL, 0x64BF9A23509385E5ULL, 0xA0133CA63871306BULL
        }
    },
    {
        {
            0xB92428E14AAB73BBULL, 0xDF7818F9CF77ABF6ULL, 0x741D08845BCA7B26ULL, 0x08DEDEA53F1EACA4ULL, 
            0x323295A8CA345D62ULL, 0x1127F6ED375971CAULL, 0xCBC6115C3590CE93ULL, 0x8712519494E78294ULL, 
            0x18E04962F51B017DULL, 0x4C66889D99589B70ULL, 0x874B0FC1E0B0CB6CULL, 0xEC2F3BE402D4271AULL, 
            0x66C13960551923E3ULL, 0x49F591D6CAEC99ABULL, 0xB668C5959D643545ULL, 0xE4CEC0E77E66D03FULL, 
            0xEED9985B48571064ULL, 0x465D3E26E776D54AULL, 0x2078C2FC10C64988ULL, 0xA2CD756B32E57A04ULL, 
            0xD06E5A712359D436ULL, 0xCBAF0C452FE8D579ULL, 0xEF7A098778F40F39ULL, 0x8E8992E4C50F1081ULL, 
            0x54092FDFAB4CD42FULL, 0x8B729081DE84E72FULL, 0x4C72D33626C7900CULL, 0x486E2FF108035AF2ULL, 
            0x83DA61539AB4A22DULL, 0x49FD4E79A6D9F4CAULL, 0x2ECBCC37F40F15E3ULL, 0x243225D748A8D381ULL
        },
        {
            0xE8DDC40955316FC7ULL, 0x7792D3C4DFC0561FULL, 0xC74DE13294D850D7ULL, 0x7FBA7D1AA3610916ULL, 
            0x1C506E66FA62B074ULL, 0xE1785DD2D01F229CULL, 0xF7292971E0BCBFD9ULL, 0x6E67F3DCBF4F3171ULL, 
            0xC61674065DF45DB8ULL, 0x3C89FC6CCC3731EEULL, 0xE1ABD2DFFE7499CBULL, 0xBCD0A42278D42630ULL, 
            0x720D86A8F281C563ULL, 0x2DD314624C173860ULL, 0xF8F9CE0E324E3234ULL, 0xD5CF056C0B91B479ULL, 
            0x439649B5FD44017AULL, 0x101D652FDA4BEC9DULL, 0x077F914D3441497FULL, 0x97B351F3E50B5568ULL, 
            0xE09142D64A61D446ULL, 0x7EBEF0A0DED7AEF5ULL, 0xB9A1BF713BD6E4E1ULL, 0x53315D7E7706446DULL, 
            0x29A45090964F3B34ULL, 0x5FDAE502F44E1047ULL, 0x8CD3AF5A4CBE2AA5ULL, 0x07F0372E744D8F38ULL, 
            0xFF94C5187DF39387ULL, 0xC70D7210A23FB325ULL, 0x6B29D2890A2F3DF8ULL, 0x1F3AF5F6FFF4FF6BULL
        },
        {
            0x7915C9C439B5AFF5ULL, 0x2A140C17B1FB580EULL, 0xC19FAB2EADD0FF7DULL, 0x5C7E47B5A8FB2ADCULL, 
            0xBC01E15C84CC9D0CULL, 0xAFCDED8EBDAFBE31ULL, 0x33BB1ADDE95ED3EDULL, 0xE981315CFFD3CBB5ULL, 
            0xF562AD078B694D57ULL, 0xCAC9F6009976629BULL, 0x555AC0A6EAC1E0FEULL, 0xF2F3938593E2BCCEULL, 
            0x3D6AF453D6C3EBC7ULL, 0xE22E477E6809E8ECULL, 0x4E5BE7C06602AF1CULL, 0x5DB4D1199533B486ULL, 
            0x4F9B8779F411EBC9ULL, 0xD6613B961AB1D6F5ULL, 0x3D04F5DA88ED3A20ULL, 0x2F88BB7F14E41802ULL, 
            0xDBE884402D6ED165ULL, 0xC66074770C715FB7ULL, 0x8C43FEB26CE12C02ULL, 0x6192553614E8429EULL, 
            0x3A26625F0840BBD3ULL, 0xAF5F9B5CDAE593ACULL, 0x7926A8FF5CF32D13ULL, 0xC3008DC130A3040FULL, 
            0x2DA37D38CACF35C1ULL, 0x35168FC61FAF89F7ULL, 0xAC612EA687107A2AULL, 0x302B574F1151B198ULL
        },
        {
            0x695040873C113BDBULL, 0xB71656686904526EULL, 0xCA6FE5FB50E0673BULL, 0xDAE2F7375685BED5ULL, 
            0xD206BF8A7F21B7AEULL, 0xA41D799D8E9A5D69ULL, 0xB367C33E369C988EULL, 0xEDF5EB013DFCEF2AULL, 
            0xECE6D8B0B10F2DDEULL, 0x65F6FB3C1AEE18A5ULL, 0xF08CF8E5C64D6262ULL, 0xF9D6F74C8AC04DCBULL, 
            0x6555720CA5EB4EBEULL, 0x826811211D69F37BULL, 0x9405EF2E04D47BB8ULL, 0x477519DB66F32838ULL, 
            0xAA7BE7F6BD15ADEBULL, 0x86AC69725B51FA00ULL, 0x8C41AE93880DCD66ULL, 0x58624DFC67EAE2D4ULL, 
            0x8626C0D4CE66F262ULL, 0xD30E8FB6A8953B28ULL, 0xB9CA658F8A3E7411ULL, 0xAFAAF2C9B5677F75ULL, 
            0x2B17EC9A9114A8CBULL, 0x2B8DED9E92614C20ULL, 0xE5EC9EACBD41EBEFULL, 0xC1E827DBE3551364ULL, 
            0x621F4A9CBA351B6BULL, 0x4A8552B2FBB4F72BULL, 0x752E9DFEEE302C81ULL, 0x7890F953C0803B7AULL
        },
        {
            0x5DF0248D449C28D8ULL, 0x3610BAD309651E29ULL, 0x3D39BE8DC423986BULL, 0xE413A28F5383E69AULL, 
            0x2E886E2FBDD0A199ULL, 0x93FD793649FB014CULL, 0xC93145BBCBA944BAULL, 0xC351F950398979DBULL, 
            0x3E1BE66AD0C54A15ULL, 0xD2DD544BC0AE47BEULL, 0x189990A6C3842A11ULL, 0x83E9213EF0AF732EULL, 
            0x586C10F9D0E8D1E3ULL, 0x341A50ED00FDF449ULL, 0xF7121E7AD44AAF76ULL, 0xF54F8F0E1385F9A8ULL, 
            0x853124C676B86091ULL, 0x600F8872BB90D812ULL, 0x1618DFF0C300BA86ULL, 0x45B8A0536FD08CC3ULL, 
            0xD10223C5CC654049ULL, 0xABC5954C9A4B9717ULL, 0xFBC92ACD850946E2ULL, 0x587C746C538710C0ULL, 
            0x7F19F69BE7808D08ULL, 0xBAF7FAB4952F1530ULL, 0x151F45847C838908ULL, 0xE7A2D19F97E99074ULL, 
            0xF0CCA63E8C5EA6CAULL, 0xB16480259F055717ULL, 0x43D4ADE5AD9192F6ULL, 0x9C18C5AE5A4578C5ULL
        },
        {
            0x2D7707C9C07E6C18ULL, 0xEF45E3C099876253ULL, 0x207CEA3313507BC8ULL, 0xCD86A2D933E67153ULL, 
            0xF33908279DC34B8FULL, 0x29978C1E36DC2953ULL, 0xD7DF1A0ED1D1CE4BULL, 0xDF161B9F37A4F31BULL, 
            0x70B29C5BC55BF91DULL, 0xE21366C2BB7BFD55ULL, 0x6FFFACB5FB2C32A3ULL, 0xA708D4AA9863D629ULL, 
            0xAB5E5DEBC0AB2E67ULL, 0x5829B368DE5E5B1DULL, 0x4070DDF7B0F90CBBULL, 0x63496EBC0A0D2FD4ULL, 
            0xC024BED40F2757F3ULL, 0x9EAEF4420C667A52ULL, 0xFAA1A7D9BD896884ULL, 0xF8934AD257C83F6EULL, 
            0x00CBD7812AA7C5AAULL, 0x420973384E9A83BFULL, 0x5BF5AB9432120511ULL, 0xAA717494E3F38A20ULL, 
            0x7E72C59B95D46CAFULL, 0x6E2E2380B12CC208ULL, 0xB8A52F9E7D865D72ULL, 0x04B03D5B1AEF16B0ULL, 
            0x047AC4E98F06931BULL, 0x4F0C76742C5487BEULL, 0x90599DE40B58366EULL, 0xAEF1F16800A3879AULL
        }
    },
    {
        {
            0xC0D3F1179E72BCE1ULL, 0x1DB499A7421179A0ULL, 0xB4C7A9F7F1E31D5DULL, 0x5251B9439B721CF3ULL, 
            0x2EC23DFC63EB0398ULL, 0x85D50ABF37E4A292ULL, 0x8F6E9DE8F277A27AULL, 0x635EDB09E8C365FEULL, 
            0xC65FDD0BFB4D6972ULL, 0x8FA8C407CD2A134AULL, 0x73764A5BA347924EULL, 0xB7EAEF4A8148EB8CULL, 
            0x08413BA9DF000EBBULL, 0xF3E262A7B7FDBCBAULL, 0x7A7DB1E2C11F658CULL, 0xA20F4AD812B8B2F6ULL, 
            0x3B2178EAF72684D9ULL, 0x4F1DA92CAE31C83FULL, 0x566CAB52BAEF9CEDULL, 0x31B636B0AB101EDAULL, 
            0x2173D044774A22D8ULL, 0xFAD32B7CE831DC93ULL, 0x8C80EDD014C56395ULL, 0x81B0F98A651A5396ULL, 
            0xE071234BA6955286ULL, 0xC43D0D4FE3FD67CFULL, 0xE808B863EE8B249BULL, 0x821D3A7A998A1C45ULL, 
            0xF27D3B211D839FDBULL, 0xDD5B5E53CBAC494CULL, 0x20572E96DEFE0E19ULL, 0x9101B3FBFED312A3ULL
        },
        {
            0xD726352E706ACCCFULL, 0xFD12B7B0593D72DBULL, 0x64239AEE41C524A3ULL, 0xCC348179FA702343ULL, 
            0xBE4279BF4D81F50AULL, 0x665D86A06A7F4DC8ULL, 0xDA837715ED390007ULL, 0x38D4D27CC9662FFBULL, 
            0x8F68EE08902FF846ULL, 0x871E1E940080B1FEULL, 0xB4BC26A5B00AF619ULL, 0x7CC23488A2F5853EULL, 
            0x67E03B6BAE877A42ULL, 0x863C197A025D0343ULL, 0xC3EE8E9E46B2C222ULL, 0xCB30CD5D31214D32ULL, 
            0xEF8F9CBFBCF414E7ULL, 0x3F9275F0A622BCD4ULL, 0x43D5BD9ECF9A3F7EULL, 0xEF1E272C45F52010ULL, 
            0xC1662B0704C6C0D1ULL, 0xBE5E8615F2AEA458ULL, 0x7AB8B7232B899E8AULL, 0xDA97CE044272EF9EULL, 
            0x2A61AB016A7A575CULL, 0xDAFDCE3C7F9A0E18ULL, 0x31CD64136BBC4881ULL, 0xA8D217BE08C6B28EULL, 
            0x43593DB3A5E943F1ULL, 0xD4D21CEE07B9D817ULL, 0xF002E49587E02284ULL, 0x52C76863A707AE73ULL
        },
        {
            0xCCFAFD2BF70CEF14ULL, 0x117FC18FE00115A9ULL, 0x4BA278F5469B655FULL, 0xFC235442B5943116ULL, 
            0x572EFE096C3DB914ULL, 0xA1913DB834E73B47ULL, 0xCD1AE31F2AF56DB4ULL, 0x56214434961B1044ULL, 
            0x548DFB258F23C1E0ULL, 0x701A3274FAF170C5ULL, 0x7FDF8170715F71E1ULL, 0xE344C25D4AA9A84AULL, 
            0xC5168D577B59CED4ULL, 0xA470A64B5D36DD82ULL, 0xB88CBD0F8911F807ULL, 0x4846F10438FCFA08ULL, 
            0x75FB422C7D6F8B89ULL, 0x2471D47547D5B918ULL, 0x129AB0ED4BA104B6ULL, 0x1C7519C374CFEDBFULL, 
            0x42321E264877B345ULL, 0x227948D034272F25ULL, 0xBACBCCBD78E8CB92ULL, 0x06A23311B62B2C3FULL, 
            0x7F8BD7A2FE33B816ULL, 0xF8EE91651C3967F3ULL, 0x6121D4F9D631EC1CULL, 0xC137C3DEAC491A40ULL, 
            0x87DB014DABCC6B31ULL, 0xA120722247647488ULL, 0xF90B641B04FAD646ULL, 0x9751D992B8A96A2EULL
        },
        {
            0x8F96E8620D7BFAE5ULL, 0xB7EC4575A45A38C4ULL, 0x0549C1337B435044ULL, 0xC6BF2CEDA9AE82B3ULL, 
            0x2D08AFA0E044211EULL, 0x40ADC3D5103DD58EULL, 0xE9BC2C69288C4CF7ULL, 0x7591ECA0C3ACF611ULL, 
            0xB36E747B498D5FF4ULL, 0xF53AB7E912B57474ULL, 0x8E50BA644C8BC062ULL, 0xE61129DE507F80C0ULL, 
            0x92722536087B78DFULL, 0xD34982E172ED3445ULL, 0x976C3FBC4DDF585DULL, 0xCFE5F1E413C496A2ULL, 
            0xFCFE532C80D84E5CULL, 0x74D4D890B37CAD29ULL, 0xB6375DBE07A18262ULL, 0x59E5009C83136AA0ULL, 
            0x6DD178A4110C6F82ULL, 0xEF38205B04A00B43ULL, 0x1184EE8DDE8DA74BULL, 0x136DE7CEE9FBA362ULL, 
            0x0771B7B02F8A3D79ULL, 0xFC494D29CC3890DFULL, 0xF80859D506F9F0F7ULL, 0xE4ECE241D7174BAFULL, 
            0xEC19FAB13CF9E0FAULL, 0xB5D5102AD8F2B210ULL, 0xF5496C947FBB0382ULL, 0x2CCB1C6B4CB4478BULL
        },
        {
            0x94FACD86A4C0B34EULL, 0x0B2957D603A0029FULL, 0x729B02D1966C13B0ULL, 0x45CFAA723FD57E48ULL, 
            0xC0D490A6E3165A71ULL, 0xB7D86558B9DA74CFULL, 0x4ABD48F4A136B86EULL, 0xEFC48EAB140A9192ULL, 
            0xF441B2B47928CCCCULL, 0xFDC803BB8A28125FULL, 0x78EA3C3C3249ADF1ULL, 0x6CE3A93A2ADDB140ULL, 
            0x9978ED7CCD810E80ULL, 0xF9CB2948BFDCB3EAULL, 0x99CBC7A9B22D5D77ULL, 0xCD7A3C7ADDD95953ULL, 
            0x5E4EFE9E467ADE60ULL, 0x5E82FD69E2F37D94ULL, 0xDF7AE50E26A3AF6DULL, 0xEA930E5AC4C61BADULL, 
            0xB5828AFAB2CAC07CULL, 0x824F4094BBA2B549ULL, 0xCC9837722150F272ULL, 0xBFE33134E6DFCE8CULL, 
            0xE1DE16EA615D344CULL, 0xF452895D27B63A2CULL, 0x06B1BB240173531AULL, 0x514A04926B1A76D8ULL, 
            0x6AA964DFB5DF3C54ULL, 0x9021C8D82180711CULL, 0x2F5EAEA5EC26092FULL, 0x7189B2B832B27BDFULL
        },
        {
            0x5077F82AE1F3031CULL, 0xBFB03713D5C0751EULL, 0x8A791977E0ADCAEDULL, 0x37C2C5B563EA78FCULL, 
            0x080072B022818116ULL, 0xC2F6CDDA40697EF0ULL, 0x777EC87F85F32F70ULL, 0x07EA35EE32AE338AULL, 
            0x332C4909C7D915B9ULL, 0x66F22E8F2A9A7E9AULL, 0x7665AB9E9B8343DCULL, 0x499F1243BAE8CA56ULL, 
            0x2A1268117D268970ULL, 0xCB0DE2E329BBBC12ULL, 0xC0725BDC0F687C98ULL, 0xD7256B9B54447653ULL, 
            0xF72B5B334952D634ULL, 0x3B705A684C157FC6ULL, 0xD2F5E380B7AA7233ULL, 0xA6CAB590EFD6DB75ULL, 
            0x76DBE171FEE49F86ULL, 0xB240C7D8FD974D54ULL, 0x8A4A2E7950272CC7ULL, 0x2119E3ED8D65A01DULL, 
            0x93FE6DD1F6DD47EAULL, 0x560FA4112188B4F3ULL, 0x55D013D75E7B06DFULL, 0xFB102A598DFFD5BAULL, 
            0xD4F4B7D47508AAE2ULL, 0x10F3C5FC34D78088ULL, 0x968792AC58619B6AULL, 0x39F54D0F27E96604ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseDConstants = {
    0x9F9BDC676639FAC2ULL,
    0x1472F3335A530DA6ULL,
    0x2472D6514BB4BF77ULL,
    0x9F9BDC676639FAC2ULL,
    0x1472F3335A530DA6ULL,
    0x2472D6514BB4BF77ULL,
    0x7309DA6DC5347857ULL,
    0xAD63717AF8C43563ULL,
    0x07,
    0xC6,
    0xE7,
    0xDA,
    0x6C,
    0xF5,
    0xC7,
    0xDE
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseESalts = {
    {
        {
            0x33946F9EB6A05801ULL, 0xA6BED59C93DF7707ULL, 0x4D42366CA9512F7AULL, 0x6EBB9B99DE44E871ULL, 
            0x349BC3A7DFAD2FAEULL, 0x2EE112F90F1C5D0BULL, 0x84476E0FEF1F566CULL, 0xCA78175AFA51997BULL, 
            0xA30608ED8A2438C0ULL, 0x5301903C779643CEULL, 0x9BF9CC32F082DA3BULL, 0x0CA1A500CF93693BULL, 
            0x30D4BFFCECE29804ULL, 0x1313112FE400E8BBULL, 0xC52D8B769B0BA5ADULL, 0xD99F6BDE98676345ULL, 
            0xE88AED2F756ACBE2ULL, 0xE697BF0DCE572D6FULL, 0xB3B717371533568DULL, 0x0310223E1C6418A0ULL, 
            0x529E453CF1606EBFULL, 0x0F5DB602F51687DBULL, 0x815E209B694DA07FULL, 0x18A88D4D588D2B7BULL, 
            0x6E5BF6E0CE18086BULL, 0xF2E890B88AEC400BULL, 0x1359AAC4FB7600D9ULL, 0x0B325482081272F6ULL, 
            0x7136E798EA5C7E89ULL, 0x4A3BC2FB9402822CULL, 0x8031CF4730F3CC9BULL, 0xFD3B3F3BCFBB3813ULL
        },
        {
            0xED5B431E9A5B4276ULL, 0x77A5F44A96A6F2AFULL, 0x05AA6FBCE33B9FFBULL, 0xD11982DF0596A669ULL, 
            0xB89E4EBF68F9822EULL, 0xAE538AFD5626C89BULL, 0xC1D271EC8E311D88ULL, 0xDA043F5554EB8647ULL, 
            0xD724BB224C4B1785ULL, 0x3D555DDF47C83063ULL, 0x88564F4028A2C5A6ULL, 0xB7D87D61C22ED4EEULL, 
            0x58078A9072622B19ULL, 0xA637D4F01AA3DF85ULL, 0xC0B9B7A040832F33ULL, 0xD1EC6DB4CC0317D6ULL, 
            0xAF4561238AFA9137ULL, 0x8704761F6C5C4D75ULL, 0x822438DA0C207AA2ULL, 0x2B62778B5BC02400ULL, 
            0x7E0BECBBF806E880ULL, 0x12012FD32666779BULL, 0x65239BC41390FC6EULL, 0x67E7B30597421D01ULL, 
            0xEA9A2340E1DDC327ULL, 0xDE7747992ACC04C2ULL, 0x7D148CB247AAF392ULL, 0x3EA7CB9CAC863D5DULL, 
            0x9F60D3D719C1BF63ULL, 0x2FE742D8491CF5CBULL, 0x50CC1625417F7BADULL, 0xA0E95B6F8EB7EE6DULL
        },
        {
            0xBB5B551DB551FF6EULL, 0xB63CACED59D32DFEULL, 0x3FF4F3350734A33CULL, 0xF78E6A13CB87F42AULL, 
            0xFAA291F9839A349BULL, 0x14D081975A38C53BULL, 0x778C1C5E64FFF6DDULL, 0xFC978D1E5173752FULL, 
            0x4EACDA77A57DF7A6ULL, 0x6AE06A5A30FC313FULL, 0x052A95D4AD267EF7ULL, 0x56AC839DEA8CB284ULL, 
            0x0B4731D6FA47943BULL, 0xF1B516DDA77FF386ULL, 0x31F06343EAF8AAD2ULL, 0xDC65CD1E6EAD7170ULL, 
            0x879C8BCF694935A5ULL, 0x66F85FB76985D14FULL, 0xCEE375E40BF2BCA9ULL, 0xC889611038138A14ULL, 
            0xAFAADCAAAB671265ULL, 0x7F2DBBE8C95C1586ULL, 0xA0A1B0BF3EF298C9ULL, 0x700733E537AA0B33ULL, 
            0x9DBACBF5F5F74753ULL, 0x27B5BBC8FFB76013ULL, 0xA55B1114C2285527ULL, 0x3586C9299DBE5C06ULL, 
            0xD569BABE2F455DBFULL, 0x0A8BA48BC10E3019ULL, 0x1A1B370A3BE7CC64ULL, 0xC3E5F6D49B68CDD1ULL
        },
        {
            0xB467D19F519CE483ULL, 0xEF4E58467BC95A9FULL, 0xB9C4FE5A29AE2180ULL, 0x5C60E72AAFC41058ULL, 
            0x066850F0896A12ACULL, 0x96F286A1A2182B4DULL, 0xA649A406117CEAF0ULL, 0xE5A37A9989533AA8ULL, 
            0x0D79EFE2AA88796EULL, 0x595270280C4B172FULL, 0x1F436E893663510EULL, 0x06EFDCECB987DC01ULL, 
            0xE712785AE2F6934BULL, 0x9E7B3C7FE6EFE3EAULL, 0xBA7EC1A0AAC2E03AULL, 0x76EBB66AF7251904ULL, 
            0x2401789BBE4A4A76ULL, 0x5C9F783B862986B5ULL, 0x4BEC16ACA9917069ULL, 0x8A6AFAE473CC7573ULL, 
            0xB73F37802696AFFBULL, 0x0D5E70DDB2CD8D8AULL, 0x89D4CF6C7042C0CBULL, 0x0A33BF286A9B2BABULL, 
            0x230E60177E927877ULL, 0x0631FFA303443CE0ULL, 0x3C42AB8A98CE81F5ULL, 0xA3E1CE1709B0C848ULL, 
            0x3104DBBCB5274642ULL, 0xAF7C39A7D16A04BBULL, 0x84F28ED59A758CEAULL, 0x93B3BB45A2950583ULL
        },
        {
            0xCD517C769FF773A6ULL, 0xB578752010FB04AFULL, 0xFC9FA71A051016F8ULL, 0x866C6BF819B7E3C8ULL, 
            0x41CADD98D377F7BFULL, 0xC94BCAF858E83120ULL, 0x6DA6EBDEFF5274BEULL, 0x71B5E855D0EEA2CFULL, 
            0xD6AA42E3BBCDA398ULL, 0xB54E1B6BCAA6797AULL, 0x9A1A4FE4F152CDF7ULL, 0x5DAEBB6F5F8421CCULL, 
            0xF2218AEC97486CD3ULL, 0xAE52EFC44E4319ACULL, 0x98B3B0856AC12BFAULL, 0xC521A3C63869F322ULL, 
            0x741A0BEAE6481258ULL, 0xFCD72EDFDB40096DULL, 0xF0C65FE645862CBFULL, 0x519F6681EA8A9997ULL, 
            0x03D37D7EBA0A587DULL, 0x9EEA1F778F6B9BF0ULL, 0xFD059DFCD8F6C3A3ULL, 0xBC5D2731755FE9E1ULL, 
            0x2013011CE6F4FC54ULL, 0xE06ACA900647E60CULL, 0xC8ADD2B5EB5088CCULL, 0x1EB4C50D7B771349ULL, 
            0xEB6C8E2A5D53DBA5ULL, 0xC8EA3F48271F00BFULL, 0xE1CEDC356963A4B1ULL, 0x822826784DEF3EA2ULL
        },
        {
            0x142671F8A71E338EULL, 0xEBACB28CD1D246EBULL, 0xF31DC286203BAA5EULL, 0xE6A0606EF35D4E71ULL, 
            0xF8F894ECF7D511FBULL, 0x67C93D93BAC1C400ULL, 0x40869C53E48BB351ULL, 0xA5E595F65AB4FCE5ULL, 
            0xBD7B17B659F81785ULL, 0x5891D661BC66FC0DULL, 0xE19C670D1AAC3D56ULL, 0x590CB044C7775C7CULL, 
            0x12A1AA354FC0899FULL, 0x1235E9E66EE2AD98ULL, 0xCBE9E5839A4037FBULL, 0x7F78C6E76B848A8FULL, 
            0x5C284806C00A5EEBULL, 0xFF7306C124C26A5FULL, 0x6B1711A20A3698BFULL, 0x98B33174BE644B8AULL, 
            0x0634DB358B31C0DBULL, 0xEB690A4DA04BB0ABULL, 0x62F323B0B7F8FC23ULL, 0x5F7161BC3CA01A19ULL, 
            0x54282250C08C53A6ULL, 0x7A8FEDB5D6A58D24ULL, 0x9B2102AA6117333AULL, 0x2BDAF253D87360CDULL, 
            0xCCFE9ABB46F1DAD8ULL, 0xF17DA19AD238F7A3ULL, 0x68A7E004FF4963F6ULL, 0xE898A9FC3D1DA047ULL
        }
    },
    {
        {
            0x602ABDBB19489E8CULL, 0x7AAE7BA81CBAB18DULL, 0x5F6E999BED78EB21ULL, 0x1667127648E0A681ULL, 
            0x1CC6262B85402339ULL, 0x0266086344FD36E5ULL, 0x77AAC37F43531EADULL, 0xEB25F018E516C88EULL, 
            0x39F42483F8F18B54ULL, 0x0232B5E97C3CDB84ULL, 0xE8A13DA23A7042A1ULL, 0xF35DBF5ACE26FD1BULL, 
            0x0FC1BBCB0EBFAB62ULL, 0x1FA8A159C965F9F0ULL, 0xC3909DA27BFA9D33ULL, 0x9532BD6C6AF7BE68ULL, 
            0xA0FCEC6220CEECACULL, 0x1D01A383B1CF6B91ULL, 0xEA20C9D49574B17BULL, 0xBA11BFB9B93F6F5BULL, 
            0xD22F7AE15622D55EULL, 0x70C312619E6F17D7ULL, 0x5C3B8B6824B8E8C3ULL, 0x9D7775D7DA62CDADULL, 
            0xD9C6BD4B6B088C2EULL, 0xF8CB5ACDF0A5C5FFULL, 0xF06C488276795E41ULL, 0xD8E93BE4AC004420ULL, 
            0xD5089737BE278CD3ULL, 0x0A6CADF331B8D93FULL, 0x39527699126E4681ULL, 0xEDB58A66934B4C3EULL
        },
        {
            0xF289DB114CF8C6B2ULL, 0x269EDB453E7EE55AULL, 0xD18B43CA48272D85ULL, 0x3B525BE32EAD1FFFULL, 
            0xE305F82624C15AF3ULL, 0x6F922A297566F174ULL, 0xAF462C1DABDF8160ULL, 0x73F5938267205FCDULL, 
            0xEAA8A6327DA9D8D2ULL, 0x597D9E744AC64170ULL, 0x2CF087C068B30E9FULL, 0xE19EB309784B3C0CULL, 
            0x1155FAFA8899A97AULL, 0x62FD5BA6C9F6CD5FULL, 0xDD5D78845A1E93D0ULL, 0xE73651E5DDAD7275ULL, 
            0x51EEAAC3297CB2DEULL, 0xEA39AF0C87659DADULL, 0xB098CBC0B816DF68ULL, 0x0C87B679C08453E3ULL, 
            0x99283579D58166CAULL, 0xBA556C2FF8C36C09ULL, 0x9896A4124B41DE40ULL, 0x98274B0D556F5041ULL, 
            0x746BDB4F697DCCFBULL, 0x2BFE47C672AA21D6ULL, 0xE3C835400A4B5BC1ULL, 0x633E34650FAD5077ULL, 
            0x4B819F6DB8E2AB7FULL, 0xDBD75B5C1BECD82FULL, 0x7CF3EAB65757FEF7ULL, 0xE90451A4307BE801ULL
        },
        {
            0xC09DF065068D511AULL, 0x4530E1C0FFE60874ULL, 0xEA947EDBBEE2D1AAULL, 0xB7F42A622F4D1AD3ULL, 
            0xB850A46C06AA4FDEULL, 0x836EB288BF5A629FULL, 0x9BB078899E05C903ULL, 0x7E595C7C54CEDE7EULL, 
            0xA8181F480C6AF298ULL, 0xDC8CCE2453D151D4ULL, 0x184D772C29E0B69FULL, 0x63797DD0F69F3031ULL, 
            0x612A6BBFC062422DULL, 0xBC6DD9167FB0C800ULL, 0x6CC065DA8D75634BULL, 0x32918C5A3862A438ULL, 
            0x115F0A8475DC3455ULL, 0x5DE5917667B704EFULL, 0x360A3FF24FC891B7ULL, 0x7D2D0485514A67D6ULL, 
            0x68193AC7EB6C5C53ULL, 0xFABF9B9D6C0B3C27ULL, 0x64DED77D498C6D6AULL, 0x551CDBEA93B793FFULL, 
            0x69C6589F29A9261AULL, 0x6A025E11AADFE4BCULL, 0xC1DC8B10163D11D3ULL, 0xF5846FC3E1C8CA90ULL, 
            0x8739B125396C6A52ULL, 0xFF1F4D2A618A1F7AULL, 0xDC6C30E492EA04D4ULL, 0xAE25B0F94210BF58ULL
        },
        {
            0x1EE4095B314AC5A5ULL, 0xF50CE6CCD167FD6BULL, 0xE9D4EBE0F2F6B69EULL, 0x03B10CAA5CEEB676ULL, 
            0x0DE6CA51871178F7ULL, 0x39B5A4DC1B259D88ULL, 0x3848C28F6E2E930AULL, 0x999D46895557E984ULL, 
            0x99DA45BEC164BACFULL, 0x08A4156B5FD4C905ULL, 0x6758AE5FD61FFA3FULL, 0xD3BD322247FC3142ULL, 
            0x8A8C6D517A6550B9ULL, 0x67D232469B459A73ULL, 0xBE9EA414C705D8AFULL, 0x3CC96475934E89CFULL, 
            0x9778C331FD4B3565ULL, 0x5F989337A575DF2BULL, 0x973FA7176ED5A40DULL, 0x58CBF0FA064D4388ULL, 
            0x7923D5C6FA7CC119ULL, 0xCB08E3B98E9C9A19ULL, 0xEC57E3D8F8D1EDD9ULL, 0x2595A501354059B4ULL, 
            0x3C78892FACA18E37ULL, 0x6ECF824487BE67D5ULL, 0x9559128BCB36F061ULL, 0xD4F6827896127D77ULL, 
            0xD4CB90D0F340BB3BULL, 0xE3C4494D1394B40CULL, 0x9995BD8E80CDA69BULL, 0xC82D7BE0185FB9F3ULL
        },
        {
            0x15508C21F7D235DEULL, 0xFFB18186E65FBA77ULL, 0xF42DFD26D77EA9E2ULL, 0x3F4C19A067FECF1FULL, 
            0xF54EEA4FDC73C507ULL, 0x4D94DEEF27D78C9FULL, 0xB5E2B80FF6BB9AD3ULL, 0xE698BE0B57A82272ULL, 
            0x977A18684EC29AEFULL, 0xCFF6462F6A63ADBDULL, 0xE3F018BBDDF63DD7ULL, 0x0DF365045897D254ULL, 
            0x1948C3C837F59454ULL, 0x74A2C651FA3B0E6DULL, 0xBA8DF23C8E409674ULL, 0xC85647FF0BA958E7ULL, 
            0x938BBE10C66782CCULL, 0xD0F1C75F37D0F624ULL, 0x7E688B6A1B52626AULL, 0x99894A23CDB09C36ULL, 
            0x6C049E4165A48E6CULL, 0x658901A55A456944ULL, 0x6974CF8BF6038DB9ULL, 0x46A8B1930E1FA352ULL, 
            0x95C7DE053CCC7BEDULL, 0x9FD4CC12793C1D2CULL, 0xD6DBB2BE08287603ULL, 0x22D6E37C253792BBULL, 
            0xCE699AD1C439FC97ULL, 0x5569C34DE64255D6ULL, 0x29FDFF1F7FDC05D9ULL, 0xA68C537C7681AEC4ULL
        },
        {
            0xDB18AEC757B4AA61ULL, 0x9CB02186A35AC625ULL, 0x4188C5D9AF12B24BULL, 0xEEF7BE34F6E0BF37ULL, 
            0x1D900ED7FFAFB5A4ULL, 0x77E20317F5797268ULL, 0xEB3F024D36F1EB13ULL, 0x4556844036A76D42ULL, 
            0x7A96D8719EF5FE24ULL, 0x3AA946222ED3462AULL, 0x15BB9F5B36CE532AULL, 0x558796F0569AFE79ULL, 
            0x6CAA2D42BE53AB6DULL, 0x1AB5FFAA044D0CD3ULL, 0xA41C2A29F3D38640ULL, 0xC722F2F11CCBDF35ULL, 
            0x6150F5A8B41FAC06ULL, 0x9FFB292752E7B38BULL, 0x681A3F3FBB7894C8ULL, 0xDFE17516CCA41E39ULL, 
            0x5F87D90D61CA18CCULL, 0x744D4D096DE8A9E7ULL, 0xB18FB4366B7CAAB1ULL, 0xC697997639D960E6ULL, 
            0x3B5AB3B0240AB133ULL, 0x3C144F970CAC1F1EULL, 0xB04A23FF21C2913FULL, 0xFB2604898EF1F188ULL, 
            0xFAD948FBEAC30009ULL, 0xBE903CC6B57B4031ULL, 0x0CCCBF4EBC687BA2ULL, 0x8136D16ABEFF29F5ULL
        }
    },
    {
        {
            0x136C4CEB730B1AAAULL, 0x4D610A50E224841DULL, 0x26648BD70C446272ULL, 0xAD4B2CEA512BC049ULL, 
            0x7F0DAE14EC74EEE7ULL, 0x40AEC17569494150ULL, 0x86DCF35DAC602572ULL, 0xD1DF046C92531775ULL, 
            0x2F408B9255402844ULL, 0xB55CBD0E414C96C6ULL, 0xC818571931D6D563ULL, 0x5DD87D893C41774DULL, 
            0xD2099DC2AC6A9A3CULL, 0xB795CD55D93984E4ULL, 0xCFFE5403E704FE33ULL, 0xFF809B8EA41A6E47ULL, 
            0xDA2D128547C2932EULL, 0x864B000B63D3AF41ULL, 0xCA316EBA869DC2F6ULL, 0xF15DB76246D2C62CULL, 
            0x5E27B14907DF4FD9ULL, 0x9AC794119B74B2A0ULL, 0x49BAB14624F04614ULL, 0x4DDB03BCE4B86FCFULL, 
            0x64B019DA7D2AB676ULL, 0x91034DA6CF6BB959ULL, 0xD9E9842F717AC9A3ULL, 0xC083DED9BEF91A6EULL, 
            0x3DC20F031EC64740ULL, 0xE552F9A7046100E4ULL, 0xCF824B0E8D62105FULL, 0xBFABAA60A64062DBULL
        },
        {
            0x3D0FC1AABB66733AULL, 0xD829A2593A28C2B6ULL, 0x6A04AA22EF1F55CFULL, 0x251CB5D6DF0139C6ULL, 
            0x4D5D25E8FB6830CAULL, 0x3C0156210FD201D2ULL, 0xDC3DF5F2059AD62BULL, 0xAF77F97B2132828CULL, 
            0xC9BF94D95816FFF1ULL, 0x31FB198634853E21ULL, 0x0BDC547300754D7BULL, 0x3AE166CD7CB31F5AULL, 
            0xC82377A43CDFE090ULL, 0x6BD167270232181BULL, 0x690A7137A78FE2BFULL, 0x3679297298ED9CBCULL, 
            0xF70471FC1C8C325DULL, 0x3EF57E58B95E4732ULL, 0xF2FF7F6A792AA97FULL, 0xF5B463C58AD96C2DULL, 
            0xCA006A4DD31ACDF6ULL, 0xC9F30487A81C755DULL, 0x07A16EFBC53FAD12ULL, 0xA02937559EBD10E2ULL, 
            0xA6A83B799BCBA821ULL, 0xEC69EB0637DC6A59ULL, 0x228CFE9F160C887AULL, 0x8FE692E08C2C92BCULL, 
            0xA03EFD7D0097D4C7ULL, 0x7F701EB43F3220A9ULL, 0xEA848CC2BD8F0E29ULL, 0x44B27F062E6F961AULL
        },
        {
            0xCED45793B9AC2169ULL, 0xFBDB842FD400D3E1ULL, 0x66C92C72378E94B3ULL, 0x1249318FC531B15AULL, 
            0x2D07591817BA9E51ULL, 0xC9C6D55EB5F59ECEULL, 0x62A65A3B2820DECFULL, 0x8CD955C7D80A0107ULL, 
            0x6DB35647F93D4668ULL, 0x00AC042D55C5B96DULL, 0x4AFE5842BD012556ULL, 0xFFCB4208E3EA7913ULL, 
            0x5EB0CA638C331C53ULL, 0x4957E8CD787B47D8ULL, 0xF965C8A40A56C8BBULL, 0xC0166A5E8FF2A4E3ULL, 
            0x0CEF9EAD91C0B689ULL, 0xA9CE475519E2C5D5ULL, 0x67DB1B9213BA1441ULL, 0xDBCCBC5E171CD939ULL, 
            0xE436DB50706FD054ULL, 0x2BB25C787C4F7B87ULL, 0x0FC118CA551BD023ULL, 0x251562367610D6C2ULL, 
            0xF9DFE6BBBDFE1136ULL, 0x7778534887D84C27ULL, 0x3FAAFFE794CDDF20ULL, 0x3710EB78D0DD5C12ULL, 
            0xCAC9241275676DCAULL, 0xA44528620A788708ULL, 0x52C1CBADC5BE34BBULL, 0x5395DB7E7A6B4132ULL
        },
        {
            0x6885D3AD06B7F211ULL, 0xCCFE6F9F183C5DB1ULL, 0x2DEBA2BC3BBDB1EAULL, 0x46E0E9DF29721632ULL, 
            0x3409FC9E84D9499FULL, 0x6A3725697797819DULL, 0xE045E562C7A9063AULL, 0x610B494D8B28067FULL, 
            0x8F7242292A32742EULL, 0x7E2599DF606856AEULL, 0xEFC68B0D1EF74F6AULL, 0x98CC951F1DDB9BFCULL, 
            0x907AEF5DA2120DB3ULL, 0x19B8CBFC684759D3ULL, 0x0A570AA9865344C1ULL, 0xD16B1761A178A256ULL, 
            0x5F99ACBDB3B01D61ULL, 0xD523BF864A30521FULL, 0x49AB422D5C46B2CDULL, 0x4749ECD087508A30ULL, 
            0x757F0F2352F54F43ULL, 0x6123593C72D183D9ULL, 0xB33E68135DF7CD1BULL, 0x32E3485DDBB2CAC5ULL, 
            0xA896077A71D5AFC8ULL, 0xACA2B96870ABDB28ULL, 0x3F21D83E811B2515ULL, 0x288B3766BE4AFF4FULL, 
            0x5C0789A501219A6FULL, 0x817FE8B2D54F62BFULL, 0xA5822EE4CA34E5F0ULL, 0x39ADD056DFFFDC4DULL
        },
        {
            0xDF367960E55EB3ADULL, 0x8370474295EAFB8FULL, 0xD9AA5E506E75F4A7ULL, 0x84D86C1900A96C23ULL, 
            0x43247DF8ED440E67ULL, 0x1700D454FE821D36ULL, 0xFA440F628888DAEEULL, 0xEE1FE890B24C02A3ULL, 
            0xDDCC6C6C42336B48ULL, 0x7D422DA2A4934597ULL, 0xB948DEEE4B3158FAULL, 0x00A73D56E52B3E0CULL, 
            0x6C6A13B38D5AA563ULL, 0x3055F8F42F2A0E31ULL, 0xA6C373176635A4E9ULL, 0x299A3918648A6D77ULL, 
            0x9A6683A9ABD1D50AULL, 0xD5EDF83963564741ULL, 0x110A62987C86FE6AULL, 0x7360DA14D65D50F1ULL, 
            0x629F0E902810537BULL, 0xC51AF852AABEF81BULL, 0xC23A6F842D1155D2ULL, 0x611F3A98034B9411ULL, 
            0xE083712A6CE3112AULL, 0x2C75D5B9CD34CE32ULL, 0xEFCA208310C569E6ULL, 0x9D8200869E301F19ULL, 
            0x54F9121ECDEC3583ULL, 0x8C4F60B9B673923DULL, 0x4798823CC769B0A4ULL, 0x0BB4FA4CD207D012ULL
        },
        {
            0x050BD7C2DB34819CULL, 0x5824C71966538278ULL, 0x14B3BA8D76F5B4EAULL, 0x8599A911FBE16CADULL, 
            0x3E7B70AD47E9DE49ULL, 0x595FEA76354AF0CCULL, 0x2073EE4F77729275ULL, 0x41CBF9D00C41E306ULL, 
            0xBB88EB9DF4D9CBB1ULL, 0x0B62C90F5D5C85C5ULL, 0x8FAC1E6F02500669ULL, 0x96238AD61B43DEC8ULL, 
            0xF9D89663BEEEB04EULL, 0xA9462CA662F44BF5ULL, 0x8FD993D6D824FA0DULL, 0xC540B52032120ACBULL, 
            0x68EF1F0DB2CAC1DAULL, 0x3AF6766192E7FECCULL, 0x65765087B1C3AECDULL, 0xD2276C814C1D7E26ULL, 
            0x75384D483B24023FULL, 0xB6F27C44A42329A0ULL, 0x49E92759B0533EE0ULL, 0x3DF5EABF94BE634CULL, 
            0x1C8F2EC8D1B15097ULL, 0xFD7E3F136C380495ULL, 0x138C947CD2A32D4CULL, 0x97B47C2FFE0E3DD8ULL, 
            0xC7311AC3B407C325ULL, 0x5050FE6C98A29113ULL, 0x242678C8BBABDAA7ULL, 0xB49C2410034EFB67ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseEConstants = {
    0x664D5E3D661C12C4ULL,
    0xD5BCF7A6367BF284ULL,
    0x2EF48EAC9A854244ULL,
    0x664D5E3D661C12C4ULL,
    0xD5BCF7A6367BF284ULL,
    0x2EF48EAC9A854244ULL,
    0xD56594BBDD584210ULL,
    0x1BD558CEE28A9570ULL,
    0xCA,
    0xB2,
    0x20,
    0x36,
    0xA5,
    0xC0,
    0x0C,
    0x8C
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseFSalts = {
    {
        {
            0x878B165016377B29ULL, 0xA6FE20523C1B1B11ULL, 0x7083F2FC2FFE0679ULL, 0x6AAF5D788B8266FBULL, 
            0x93CF0DC2ACDB055DULL, 0x29FD64E48C53761AULL, 0xCA59C467728D5636ULL, 0x0E86B668DD64D824ULL, 
            0xA501663AFD4AF411ULL, 0xF3BEE3153C149FEFULL, 0x894373BFDEEFC83CULL, 0xD1B186FF10086F35ULL, 
            0x8D24FB459C4B53F6ULL, 0x8D283B20C2B0FF43ULL, 0x75B791AA19E6F7B1ULL, 0x6E0736EE0DADCFA1ULL, 
            0xEA17D416BC62E9D1ULL, 0xFBA5ED2AD57AA622ULL, 0xCE0C9488DAC40084ULL, 0x3ACA911BCEE26503ULL, 
            0x441730688B01BACBULL, 0xC76E1C5FCA2D8BFCULL, 0x744CEE25B45B4860ULL, 0x359F03EEE515C5BAULL, 
            0x7D77F1D746329FECULL, 0x27D18408FCC446FFULL, 0xBB4AA30A6FAA3443ULL, 0x97AD6E1C578439E4ULL, 
            0x486D23D98360FBE9ULL, 0x96991E4E832E4FA1ULL, 0xDE18D63B6656ACAEULL, 0x713889D504834A65ULL
        },
        {
            0x0ACDD3CF25BDE2B5ULL, 0x308C56A7227A62E8ULL, 0xF1A41FBADC9F22D5ULL, 0x95FE16E20D32DA0DULL, 
            0x97D2F6AAF788ECBAULL, 0x4CA1C3BEE29C6071ULL, 0xE030A6633C94D95AULL, 0x989FB669087324E5ULL, 
            0x1A94F88C4DAE05CBULL, 0xEF92ECE1983184B2ULL, 0x3FCA49CD03A39577ULL, 0x831EB7C8EA684714ULL, 
            0x44A4B111B7BA8E9BULL, 0x9AE52BEEB5578A15ULL, 0x41633BAB6883D32CULL, 0x206A19D4D3E3F866ULL, 
            0x292376CB469925B6ULL, 0x89C9770205739DCCULL, 0x38A21FE770306076ULL, 0x7E02B67061C1A17AULL, 
            0x9726054CBDF6294DULL, 0x45F010403E05862EULL, 0x3120E656C25FCE73ULL, 0xB13FE1F2D3606A72ULL, 
            0x6A0BD613CF3A31E0ULL, 0x2A13FD9C0F89221CULL, 0x5E2BD27EE50BF203ULL, 0x63E8379536D307EEULL, 
            0x4F13AE7696B37E30ULL, 0xB62614A1C9CF4D8DULL, 0x76C097C030182D21ULL, 0x90A395717C1D796DULL
        },
        {
            0x6E3C1D7EAE69AE68ULL, 0xD59D482E9705E374ULL, 0x09F3105AA280B573ULL, 0x520CFB00F11C0E97ULL, 
            0xAABABD81D2490307ULL, 0x82DC67CB8868640AULL, 0x021E35529D154431ULL, 0x94C592DF51511038ULL, 
            0x9E01F9B194E663DFULL, 0x98350ABB09CAC12EULL, 0x04CA9B4080D645BDULL, 0xDA30429C07DC3CB1ULL, 
            0x02C92D840CDF323EULL, 0x387E9F7138641335ULL, 0xC63BD28D1585E820ULL, 0xD6DD3D25694AA12DULL, 
            0xE8DC5B2BE0020B2FULL, 0x337061B2B9CA479DULL, 0xDB50B299A3A410BBULL, 0xFEB4A189CDC42E45ULL, 
            0xE594F310F024144DULL, 0xF747B0C384757F9BULL, 0xF24815893352D00AULL, 0x81955BC3CDE81080ULL, 
            0x9CFB7CDD8DC538EBULL, 0xE09E91EE077E1963ULL, 0xD821A8DC057B0AEAULL, 0x9A0062A8A197775EULL, 
            0x199C6009A5C7E10FULL, 0x7CB9DEB1B7E0E16EULL, 0xDF0F32D6F040E89BULL, 0xF2C28B5521DE4554ULL
        },
        {
            0x0AC3CB15943ACDC3ULL, 0x0367815E0D3B8098ULL, 0x83EFF4E9AA242A65ULL, 0xA712F4F1DA50C648ULL, 
            0x2E67602BF923EC11ULL, 0xBAF76990801527BBULL, 0x81754A2DB25C358DULL, 0xC87D2B13A611A947ULL, 
            0xB864E86EB08F56B9ULL, 0x9325A67B4F1B631AULL, 0x9F73C28918331E6AULL, 0xFFE5DD8428BC3CF6ULL, 
            0x940CE21FF8C3E0B4ULL, 0xAC4EF78D3DB54BF7ULL, 0xD2B2689333B46740ULL, 0x9FDEB9E4B92FD80EULL, 
            0x3FC7F8040AAB1FF5ULL, 0x1287AF662062F6C1ULL, 0x045048899F129CF8ULL, 0x02528045D0FC4F13ULL, 
            0xB31C3B985951016AULL, 0x2BFFEA96A22A8979ULL, 0x7FBF55EEEC9BDA4CULL, 0x3836E7DF2D0F7912ULL, 
            0x6DE5B606DA1C9AB5ULL, 0xC3430E4AA041B751ULL, 0x2F5097B7859C8B02ULL, 0x9E96A7A87697C52FULL, 
            0xF9E114ACB4E28E74ULL, 0xE94C608A367AD8BDULL, 0xCBE3A4E1557AFCEDULL, 0xD3E5120CA05D7C0FULL
        },
        {
            0xFD269F50C1B07DE7ULL, 0x9790904B11F4C2E4ULL, 0x64A370C846EF86C1ULL, 0x86EC5E39764FD15EULL, 
            0x940D975A343DF931ULL, 0x87F5E48FD8EC0A6EULL, 0x1F41E2C93FFE482CULL, 0xE9AA30937CC260B9ULL, 
            0x39CA45EDAC43043CULL, 0xAFE34C776355B405ULL, 0x147757AB7EC97B87ULL, 0x31900D414A0A6C85ULL, 
            0xB5B97D185BA00C52ULL, 0xBA0AAD6B70E4EA39ULL, 0x12B65456FA3B02ADULL, 0xA4765BB53E25B6DAULL, 
            0x440FCD3808EC6E22ULL, 0x50F4187D618BD116ULL, 0x88D3DD5F5B50B19FULL, 0x2E2C7407F6DE0488ULL, 
            0xF52FA5BD4AAA7A03ULL, 0x167C6D19B2FFBA00ULL, 0x37505C04280C9967ULL, 0x36841E1EFB16A420ULL, 
            0xEA2CACD11FE2413DULL, 0x66E6B5BAA818EF9DULL, 0x5AC92E58E5385EEFULL, 0x5FFA82ED9D7A41E6ULL, 
            0x1759FDABBB37D7C4ULL, 0x7EDF4288D8E3823CULL, 0x5BDFF6C45B209CD1ULL, 0xE98C749E9E80DC69ULL
        },
        {
            0xDFAC159479964ADDULL, 0xEB9D7312EA55AB81ULL, 0x991AB1270B901228ULL, 0xD2C71476951FB030ULL, 
            0xFC8E76BF9761E740ULL, 0xD00B14AA4C02B522ULL, 0xDC81F33E106D5F25ULL, 0x013F2DEE4C122C77ULL, 
            0x098F65B3A7F58DAAULL, 0x8A2736830FD1A67DULL, 0x6063C04F84F873F9ULL, 0x8D16BC4E05E0278DULL, 
            0xEA8313655928A498ULL, 0xA43A1F79F8532A1CULL, 0x83F6AFEE9160FC61ULL, 0x8E913D5EF0EC25C3ULL, 
            0x28B337501C9364A0ULL, 0x5A261F8FFC89D155ULL, 0xA5479403D3105EB3ULL, 0xD1080501C6730250ULL, 
            0x877932530F1DF7CAULL, 0x1E839D146E696012ULL, 0x7506C8238EAB61B9ULL, 0xCB4072DA62BEB1C5ULL, 
            0x06DD11885D64DBD9ULL, 0xA25CC91D9B8FEB84ULL, 0xF5B2089E51DFBB0BULL, 0x4D30B61410ABB5CAULL, 
            0xEBDF471CEE98D489ULL, 0xD2B5242F0372F51DULL, 0x12AD0918EBBC88FAULL, 0x0EC8BD95772FF41DULL
        }
    },
    {
        {
            0xDD41EDB1B1AA17FEULL, 0xC49EB610E72E856DULL, 0xFCC8C2E65BF40AF4ULL, 0x2218BCF66E568073ULL, 
            0x073B4CF89E68ED16ULL, 0x29DD1DE118DD9E01ULL, 0x3EE0B16746EAA7F4ULL, 0x25C741A6B20B517EULL, 
            0x6B9999AED78A3A2DULL, 0xC4F613C8176F417CULL, 0xD63D899DC2A0DD9AULL, 0xA36FFFA5AE40B313ULL, 
            0x42F6A377C1A4CD18ULL, 0xEACBEDE775893B3CULL, 0xB1CDAA8BEADA2669ULL, 0x6616196F29476966ULL, 
            0xC3FB8379DA2687BFULL, 0xBE57904A172F37E9ULL, 0x0C7CA083DF2D7AF2ULL, 0x73DFBF48B5679732ULL, 
            0x46DE7BEA56201F2FULL, 0x410A2CED2051B780ULL, 0xBA0677298BCA13D7ULL, 0x76732F2C39B43BAAULL, 
            0x995A8D8EEABC9701ULL, 0x090D1C8FD5433CE9ULL, 0x2EAF5A826C824549ULL, 0x999D65E2BE6B5B2FULL, 
            0x62F36EED44034A1DULL, 0x00C7DA9EE8E4E43EULL, 0x96273B5EF9DB3A29ULL, 0x6E46F35ED5E01E34ULL
        },
        {
            0x4A8352937D77387FULL, 0x7E04011F45368E32ULL, 0x0B8D2AD99A3939BDULL, 0xD1F90116914E18F6ULL, 
            0xA129CD7B2E80C926ULL, 0x76A8A96B3E485C71ULL, 0x579FADD455011D9BULL, 0x8678EF8E75F6208FULL, 
            0x96FB984F300E9C33ULL, 0x44614AA4325D271BULL, 0xF8CC5895099D7911ULL, 0x9CE90D471C1C1F8AULL, 
            0x706DBA0E90D3340AULL, 0xE2B618E846E9B4EDULL, 0x080C0BA13B3FEED9ULL, 0xDBDFF42858675492ULL, 
            0x5440F70A930EAB99ULL, 0xF1A05A23CE21649FULL, 0x954B44D7B186C1DFULL, 0x503989A1E4E0764BULL, 
            0x69A8D68DD020E75CULL, 0x5A7F6F301D73E408ULL, 0x177CF4A2A8E459B4ULL, 0x47A1075124A4AE4AULL, 
            0x59E4C7A6B21462C0ULL, 0x97FDDE55F6E7329EULL, 0x0DFE69E5A3B5BD50ULL, 0xF13091C09BF272D4ULL, 
            0xFE9B53D15BC43D06ULL, 0x0BDD40DBE50DC43FULL, 0xC870CF38872FD01CULL, 0xCDA48D53C859F319ULL
        },
        {
            0x2EDBB9D17A893690ULL, 0xDFEBE85D3E125573ULL, 0xDD112FFC05B939EAULL, 0x3A8A9A20EB18E91CULL, 
            0xA7AF32544B3504A5ULL, 0x5628D2F95DDD73A0ULL, 0xCDDA85CFD39E93F6ULL, 0x1346931785944678ULL, 
            0xBABFA27B2658FDB2ULL, 0x1AFB4E42DDD57955ULL, 0xBAA50EFFB8610958ULL, 0xFEB22A399A616F11ULL, 
            0xEDDA22379FB57068ULL, 0xB371C431851D31D5ULL, 0xE5849E391F39886CULL, 0x26E988906B69018AULL, 
            0x522D12FAF1A00EA2ULL, 0xA3E4128B5583D46AULL, 0x0098CF76308ACBD0ULL, 0xFF4D9DE5C1B5FAD7ULL, 
            0x972EDB65EB0EF5ADULL, 0xC8D140BEC7953666ULL, 0xCC1F4AB49B2FA5BDULL, 0x65F3E8BB25265F7CULL, 
            0x8E29A06F646B0F27ULL, 0xE3724B154BFA1BCDULL, 0x31E760EEDC438639ULL, 0x63680071E52445BBULL, 
            0xC7DB10A424D5B6EEULL, 0xBC9FF3D17CAF815AULL, 0x9D2CF3EFFC9F5691ULL, 0x8CCD5302B2BE2A56ULL
        },
        {
            0xBF3D5A4B923B3792ULL, 0xD998C0973BE8C4BCULL, 0xE3F7F5076AF4CC9EULL, 0x8DEE41090115DD84ULL, 
            0x7929316445E104C2ULL, 0x0431F992C3A8770FULL, 0xC96708CDFC2A1B1EULL, 0xAD12157EF125572EULL, 
            0xA3918A39FE8569A5ULL, 0xC03C4F6BCBD0C64EULL, 0x104D4C205B72F86CULL, 0xBFACFE4B8F4C4F48ULL, 
            0xCB77C523A1EFDB59ULL, 0x20D9D9C71C7FEE08ULL, 0x66A3361330B68DA8ULL, 0x8DA7015291FED221ULL, 
            0xFB97F55F01F783C8ULL, 0x5B403507C9C351A2ULL, 0x79781A68E4A523A6ULL, 0xDBAF28FE6BC78F37ULL, 
            0xE15E978A4158C634ULL, 0xC5B9CCA2D0B3880CULL, 0x12A134DE59426FC3ULL, 0x79E192657568ED2BULL, 
            0x62373FA6ECA8250FULL, 0x6A0435697F4A31EFULL, 0x8B21A08264A0A5C6ULL, 0xA121CDD9255F51EAULL, 
            0x4FCFD5ECB1A22735ULL, 0xA31F12BA81E21107ULL, 0xD7D453361FDD2F84ULL, 0x285816E1E431BFDFULL
        },
        {
            0xB59BBC0646946861ULL, 0xCF5E893E01B273BDULL, 0x8BD059A183A61C92ULL, 0x4B58407BAA82FCE8ULL, 
            0xD91A1ED90B1CCA26ULL, 0x790CE8DA94ACA13AULL, 0x3B50B2630D0E946BULL, 0xCB4B6E6462C932B3ULL, 
            0xECC30305925461E0ULL, 0xF107F69AA6560783ULL, 0x6DDDF746C7F22ECEULL, 0x56802B91308723BDULL, 
            0x1BCFC0EBF000FC52ULL, 0x3A95E9BECA7B6F62ULL, 0x03ADD3AEEDCE5B5CULL, 0x1C8509B48152A184ULL, 
            0x6AAC22B1BD1A0A5AULL, 0x007A7A4F0C243AD3ULL, 0x346BA6995B0E2148ULL, 0xE40972E430060C18ULL, 
            0x3E885FB39F2F6EE9ULL, 0x5D7B741F456AC0EEULL, 0x7900D3DEEEA0F38EULL, 0x64A2AA571B0F618CULL, 
            0x7F411BA2C35AAFACULL, 0x405127CF62E8E514ULL, 0x228B7A3F4D4E80A6ULL, 0xCA37682896E36FBCULL, 
            0x155F56D15C908EB8ULL, 0x9C15A81313753772ULL, 0x6049F2FF877ED368ULL, 0xCF189FEAB82877ABULL
        },
        {
            0x19D7C0684328EB8EULL, 0xE5E35F1DAF9F0C4AULL, 0x985BBD05B5596266ULL, 0x9D71F8226456CE6EULL, 
            0x88F53FB0A6348D06ULL, 0x2D91CCFA0AE51CE5ULL, 0xF48EE3A9EFB7C2CBULL, 0x679C30FF6CEBE337ULL, 
            0x148D14FA3874CA16ULL, 0xD2D6B60C993F2AA1ULL, 0xCD8D6D4CB453B0BFULL, 0x0E8ABC1388CF9FA8ULL, 
            0x376978B457377754ULL, 0x34E150FE6D2B5B6FULL, 0xE2E5EBD640197089ULL, 0x7826B3302E55534DULL, 
            0x6E3389567EFA930CULL, 0x657E65C92FF88FEDULL, 0x688B4A3332FF0937ULL, 0x6CA3AB682445982DULL, 
            0x1899008A25ECE858ULL, 0xA47854376E93BEB8ULL, 0xB16CC1AC85F74592ULL, 0xC3332726FFA2163BULL, 
            0xD4204D7074112429ULL, 0x4986D8B5952A2497ULL, 0x5C36844402BCCDE0ULL, 0xC02CB040B93742B7ULL, 
            0x66EBECA2311B087BULL, 0xA6B574DFE06E4500ULL, 0x0B0C3E999192FB26ULL, 0xD4E659EF62492B3FULL
        }
    },
    {
        {
            0x3C0355080CF36D1CULL, 0x88AE4C3BD21B0DBFULL, 0xD2E4BA6CBF0E159FULL, 0xB1FC2F85398C27B1ULL, 
            0x8D9DAE36E99956D6ULL, 0x15973060AB0843B0ULL, 0xF21353740176809AULL, 0xE208A1634844F422ULL, 
            0x3071E9733AA61CCCULL, 0x4E0C467AB405364BULL, 0xD5889A93279FB79FULL, 0x4E8D8DB17A2DD42AULL, 
            0x929BCD499A4DE8DDULL, 0x3B95B56661CCB0D1ULL, 0xB1515C3EAA4F1FFFULL, 0x23BBBBE8ABDD0264ULL, 
            0x67E1857C1DC99D54ULL, 0x8E4A64029BBE65CFULL, 0x9857397216152BFEULL, 0x8CFFBD227701D85FULL, 
            0x3B9716DFC30EBA86ULL, 0x853214A4F850EF2DULL, 0x139A83866B46E604ULL, 0xC64ACA809BB4E8FBULL, 
            0xC88546CD712E10F5ULL, 0xA18B578C6CFF4429ULL, 0x9942D2FF4AE61B38ULL, 0xC3EE8A6A41E73142ULL, 
            0xAED97399341D82F6ULL, 0xF75188FA2936C312ULL, 0xA9850AE62EED0A59ULL, 0xCC67EF23F3C61E73ULL
        },
        {
            0xF9B8FF39CB810572ULL, 0x2A3B252CAD3C2E01ULL, 0xBA5EC9B1DC16D973ULL, 0xB8F7474BB67689F8ULL, 
            0x4E11DF5A4F1FF9DDULL, 0xE8FF963482C8CC73ULL, 0x9935E49B5B89AC1AULL, 0x9EF770A80E94311BULL, 
            0xF1D0FF33A4F06023ULL, 0x4C4EEAF08336A179ULL, 0x4A4A4B15A9A4E628ULL, 0x75A17FE6552C71ACULL, 
            0xBFDB836D9E0F59DAULL, 0x4872CFE906C2156EULL, 0x58B10493B0C8AEBDULL, 0xFD3B60A1E591EFEDULL, 
            0xD58521543B8A2477ULL, 0x55A0DA0D46E8D83BULL, 0xDDA26322E26C8747ULL, 0x9AEFF6FD45DB3226ULL, 
            0xA400E95860DC44DCULL, 0x043F975A69CE66A0ULL, 0xFF08BD788C5DA5B2ULL, 0xB0182458C597EDBAULL, 
            0x96E0ACD730C4DB5DULL, 0x376D9F40FD9E02C4ULL, 0xFD28FFCC8A25C850ULL, 0x0D2944AF30207641ULL, 
            0x70E28EF022B72278ULL, 0x5BC0CABE894A5408ULL, 0xDECDE2EAFB271741ULL, 0x8D5BB11FFA4D957EULL
        },
        {
            0x56E75FFFF39166B2ULL, 0x14A245CA8FB2A5FDULL, 0x1CC596FCC881C144ULL, 0x129DBBBA82228105ULL, 
            0x12365A5D1B8439B1ULL, 0x60BCCAAAE0C20A05ULL, 0x5D05309F2C62D4B2ULL, 0xF134482802377593ULL, 
            0x742B9A063F0A7C7EULL, 0xFAEB97077A599E55ULL, 0xBA485DB86B5FF6DAULL, 0x3B7D090D2ACAF833ULL, 
            0xC25940612DC433F4ULL, 0x70D28BA23AE7FCA5ULL, 0x26C1C1ED61E76F07ULL, 0xD0714BEE3364C688ULL, 
            0x40DE53FCC7ABFAB9ULL, 0x3718B4E03EC6318FULL, 0xCEF17F16405C981AULL, 0x2E5F0507A14E6E46ULL, 
            0x973E351A2ADEC2B3ULL, 0x5E96F9DF4D77A9A9ULL, 0x6C7CDB98F9C1C491ULL, 0x5B54633E1A574734ULL, 
            0x249D2FABF8BC5731ULL, 0x7AD1B2BE6BFA95ECULL, 0xF9F160B15561F945ULL, 0xC327C2146D7231C7ULL, 
            0x410BDBBA77520E87ULL, 0x2475E1C4DC2E524DULL, 0x00A79E6BC7700D47ULL, 0x1BA7CFEBBFCB48DBULL
        },
        {
            0x301B143C427AB9AAULL, 0x413E79526471B1D9ULL, 0xD3D3BAF9E6B88ABAULL, 0xA2611DBE667E091DULL, 
            0xD74A79B1109D4F33ULL, 0xB6DB12A428FD0B7DULL, 0x09C7A43EDA2692AEULL, 0x141D1D4163FFE24FULL, 
            0x3EB12FE8194C7D0EULL, 0xAA454C58F9CF3246ULL, 0x0355BB48F214D80FULL, 0xD50922AECA928E42ULL, 
            0xC14CDB3F81FC1377ULL, 0x201D8E6AB2D5AC37ULL, 0xE15430270559E850ULL, 0xAB931C8105F77F3DULL, 
            0x9CD7FC24350E7AA0ULL, 0xAF96201023A2CDFAULL, 0xEA775DE8E7FE6892ULL, 0x7BDCDAC968AA067AULL, 
            0x547F2D842DFABC76ULL, 0xC72F88062FE1ADDAULL, 0x5D2C9C75F471DEDFULL, 0xC4F3ADFA5ADF61EAULL, 
            0x5CBC997F1D874104ULL, 0xF0EA3359FB26AE6BULL, 0xE841F4FF51180B8CULL, 0x13EFF65410358FFDULL, 
            0x3915F83E234EE55FULL, 0xC227DFDB316FF283ULL, 0x99B5A4C386FF63DEULL, 0x591605C9FCB7D507ULL
        },
        {
            0xB78678AED3CB9EE3ULL, 0xE5B4FEBD08F6E8E2ULL, 0xEE155AD1F3DE5F5EULL, 0x5AE99C77B01A867DULL, 
            0x65E4CB4526338C89ULL, 0xE240F8102D88D470ULL, 0x776E0B73304DEEB9ULL, 0xD0DE658050A3AC18ULL, 
            0x21A47151C43FA56AULL, 0xEF4518EEC7436618ULL, 0x0B903E1721FEC792ULL, 0x9D127F3CDB497D4AULL, 
            0x985290D12AF3BAD8ULL, 0xF8AE9CD4746B633BULL, 0xB3D14F3FA392DE49ULL, 0xDF028C71AAA0D4C5ULL, 
            0x87BDE32BDAF77606ULL, 0xEF5434BA8709158DULL, 0x3C9FE4AFBC7CC538ULL, 0xB78E028161A9BEA5ULL, 
            0x3FAFBFE6B13AAEB6ULL, 0xC4813E260F45F4CEULL, 0x16A84EE34CBAE8A0ULL, 0x70A06411E6D8435BULL, 
            0x1F77B3297C731223ULL, 0xADC9776761798967ULL, 0x9D03220B1D645427ULL, 0x7312D4D56EEFB6A8ULL, 
            0x425A352DB08CCC66ULL, 0x4A8F60A43E75EDD9ULL, 0x52EADCEE64F21973ULL, 0xB06DC850CC748E8BULL
        },
        {
            0xDED0B5BE6A54D788ULL, 0x9CC52FAF2F5F43F2ULL, 0x574EB99D91774CB8ULL, 0xF9768FA4A76318C4ULL, 
            0xEAB8878AA927E028ULL, 0xCC28FF5FE38A8BA0ULL, 0x001AB82736D86EFEULL, 0x1F684EBD796C59F7ULL, 
            0x187F4B077B7484A4ULL, 0x478E50ECA1D8BC58ULL, 0x4A02594C988CF9B1ULL, 0x989175CF6AD7CA18ULL, 
            0xF14399F6B54AA7AEULL, 0x9EFFA18BCE7C6645ULL, 0x6CF58D8F15380489ULL, 0x03355181651F26AFULL, 
            0xAF4AE1D1F9C8FC29ULL, 0xBB692F514EF90573ULL, 0x3B4048719B13F054ULL, 0x92A8FB7055D4E327ULL, 
            0x6A3C5CE2F5A709FDULL, 0x4C04DA4674F7CD08ULL, 0x258F0AEBD4E90817ULL, 0xFCAD3C7F4AD2992DULL, 
            0xAEB2684FC769EA2BULL, 0x7C252C7C9C1536C0ULL, 0xB7AD3FC6D376447DULL, 0x056F40914B31751DULL, 
            0x68BD1845501D62C8ULL, 0xDA4E4C7A925FC823ULL, 0xC08E4E0BA643468BULL, 0x85E524CAC381E0D2ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseFConstants = {
    0xEA4B2B750ED580C3ULL,
    0xCAE28A7AB0F197C0ULL,
    0x2CA59F25DD04F56DULL,
    0xEA4B2B750ED580C3ULL,
    0xCAE28A7AB0F197C0ULL,
    0x2CA59F25DD04F56DULL,
    0x1D3329A0BE499E91ULL,
    0x926235EE96369248ULL,
    0x90,
    0x7B,
    0x5F,
    0x3E,
    0x3D,
    0xFF,
    0xE2,
    0xEB
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseGSalts = {
    {
        {
            0x63B9D8370C8C0F2BULL, 0x2ED56F659C3F2DDBULL, 0x900B898E1EB07903ULL, 0x260FD5B8D5202901ULL, 
            0x1562909B3DA40231ULL, 0xA642560DF3F06207ULL, 0xE34F32791736A7F3ULL, 0xDFA0D9DD3E3A828EULL, 
            0x0673DECAFB3AC518ULL, 0x24DF7BE4616330D4ULL, 0x9B00D6BBAA66A2C4ULL, 0xF0C3ADB545B64964ULL, 
            0xE9A3659549FA6E92ULL, 0x3166592FB141453AULL, 0x1DA3A66ECEAF733DULL, 0x1139F35C321D3558ULL, 
            0x3CD3E29188DCCF70ULL, 0xA4FB1F937F4F272CULL, 0x239753A912EC7AC1ULL, 0x8F9974C589E783CBULL, 
            0x48074B716ACC107DULL, 0xC935EDFD4FD7A9AEULL, 0xAA097D18D8B2A96DULL, 0x3B9E624DB4470986ULL, 
            0xA3D4639089C55B94ULL, 0x3AD6315AA93CA481ULL, 0x9152E49714498F47ULL, 0x39D689E7DE595584ULL, 
            0x9DED703A85AAE397ULL, 0x041734D217F687DDULL, 0x273969974FDF9EC8ULL, 0x0A565111BCBE7C77ULL
        },
        {
            0xD8DBABFE41F3FDA3ULL, 0xEDE6EC15FA4F58CBULL, 0x4A16826489317EFFULL, 0x165BE54E426A0979ULL, 
            0xF0F70EC6C6E3EC39ULL, 0xFB636A21A56B96F1ULL, 0xBF8AFE2E3482A705ULL, 0x81C878CD88D5CEC0ULL, 
            0x48219D7DB1A4B150ULL, 0x4497E99559C3D04CULL, 0xB5EA3D980FB9F130ULL, 0x4278EDFDFD514BBDULL, 
            0x786028FF05333D38ULL, 0x024C78EEE280D603ULL, 0x7B6994149E1DBC74ULL, 0x86E26A64E292D4B8ULL, 
            0xB765495E65927801ULL, 0xA86C9ED6FDF0D697ULL, 0x55DA471E20ACA059ULL, 0x3B0BECD553BBCE3BULL, 
            0xA5C912C7098596FBULL, 0x04EB792BD8C2AC9DULL, 0xC4D6C18CEDCE7677ULL, 0xA464B2E3E50BC49BULL, 
            0xC833506FD0DE7BFFULL, 0x77799C9A37F2192EULL, 0xDEF902221F037347ULL, 0x46615D0E54A4746EULL, 
            0x4F65EB2F8A5C2F7BULL, 0xBA771F4D6BBED9E0ULL, 0x721138226A519E42ULL, 0x999FE3756E5F2260ULL
        },
        {
            0xFAF6ABAA24D63E66ULL, 0xCD8B307E4D68D8C6ULL, 0x5D09FB31DBB9F5ABULL, 0x1A9A5962322C55DBULL, 
            0xC3E7D8C37AAEB5F8ULL, 0xB35B186469FCE75AULL, 0xD61FD9DF8770717EULL, 0xEFAB857404A135B1ULL, 
            0xB40E4248DDC65EA0ULL, 0x7A21EBF9433025D8ULL, 0x499AA1FA13938169ULL, 0xD1C731AF2C2B8DB9ULL, 
            0xCE5810EB82906551ULL, 0x532982229AFDF81BULL, 0xE95AF2BFB8D3B913ULL, 0xBC469D0358AEA100ULL, 
            0x13E0B635E9DEF0EAULL, 0x2D6D9C41D0E19AC6ULL, 0x11A742F22AB48179ULL, 0x6DD130CCF7EFECA7ULL, 
            0xF7184667F4334EDDULL, 0xCA0F168F5ACADA75ULL, 0x55192F654DFDD815ULL, 0x6D8DE2CB96CAD4DCULL, 
            0x17A76BFF018CA862ULL, 0xEDAE322F2CEBD06AULL, 0xC8F64C75E706B1FAULL, 0x8CBBCD04B46FE369ULL, 
            0x361C64E28C51034EULL, 0x97D2C6297F08ABCFULL, 0xAB1DF238209A0223ULL, 0x754657BAA71F760FULL
        },
        {
            0xD897AA36F36B2B64ULL, 0x454954BB3FD84A76ULL, 0x0D22A4B64532D9C7ULL, 0xADB3DB1DE23A3448ULL, 
            0x860BA8D3BA6527ACULL, 0xA9D3E3F597AC46EAULL, 0xB8A506582B2AE8DFULL, 0x630B1214095B651FULL, 
            0xC1971690D40CDC2DULL, 0xE233DD73B21E2F16ULL, 0x9E439F4F12B790FCULL, 0xCCE1300FA3A27096ULL, 
            0xF248CF3143423095ULL, 0x605D6C67854DDBAFULL, 0x7097018B616C1127ULL, 0xCB70E14ED69FFA5AULL, 
            0xE97BEEB36803CDB3ULL, 0x4B9227A7028E7DFCULL, 0x7690E83E6DFF237CULL, 0x432DF74901BEA115ULL, 
            0xBCCB80D41B83F420ULL, 0xFC13CFDE9D8CA5E5ULL, 0x1E9B41E6C345B42EULL, 0x2F3BD1BAE0806F07ULL, 
            0xB33C4984FBE6BA5CULL, 0x0ED6B6A19681D5F1ULL, 0xE8F772FE6D7EB512ULL, 0x3B1CF0CB157B5D60ULL, 
            0xD10B83FDC843BC2BULL, 0x1E9CB2CBBF8C2FE1ULL, 0x86DD4AF39B34D7BEULL, 0x5CAB6C9615DA2F00ULL
        },
        {
            0x62CF4C95F7295C93ULL, 0x584611189681045BULL, 0x0BCE57573CE7E026ULL, 0x739C124FEEFA14A4ULL, 
            0x9619D35BDF91702CULL, 0x93F39FFB3EB2514CULL, 0x4872D1F632AA6A78ULL, 0x2B49BD910B3C2632ULL, 
            0x8F7F260B73942CA7ULL, 0xE2F3EB688F89C8D8ULL, 0x2D8D898D7C718D8EULL, 0xC8D70F14FD042683ULL, 
            0xB745ACFFE384216AULL, 0xBDBC95DF9CC6377AULL, 0x474755B58DE57C01ULL, 0x98A7D32970EB5C5FULL, 
            0xE8DBEC898A00D978ULL, 0x8B62E9C99D723C43ULL, 0x23C22758EC1C7AFAULL, 0xBEAFE65CFA9D7156ULL, 
            0x5E51943A315E25A2ULL, 0x2DE5A03B545607A4ULL, 0x9168CD7FE2BE97C7ULL, 0xD21C2992104F0D45ULL, 
            0x908034B53E468209ULL, 0x96A1C6B8E40ECA0AULL, 0xBA9167EF6ACD2FA2ULL, 0x78D80AE60B15996AULL, 
            0x0A8AF37153534FB2ULL, 0x15171BF6C3866CAEULL, 0xA6CE9EB9BAFD7055ULL, 0xC196FF81E602E0C6ULL
        },
        {
            0x18D48C3EB4D0DFA7ULL, 0x470B5556F2CDBEE8ULL, 0xD2A2C98EE221AD5BULL, 0x2CCABF7B938345C7ULL, 
            0xA8EA1699D1C524F3ULL, 0x665DB0D729EEFCCAULL, 0xAAB23CD2456E3A5EULL, 0xE6E32D1EA9B78424ULL, 
            0xC643E2238F86F4A9ULL, 0x60E78C1364F3F587ULL, 0xF173D625A009B0B3ULL, 0xAA3C5213A955F9ADULL, 
            0x9B39AF1B059BB08FULL, 0x69F8298F0B9E5E90ULL, 0x7CC5C2C4955E35E7ULL, 0xED088DED8246F8D4ULL, 
            0x5CC01F7EDD85501DULL, 0x0958F0BD3FED062DULL, 0x74235EFE853BD6ADULL, 0xB037AE85037A5BBDULL, 
            0x0FCAF946D0B3AA49ULL, 0xD5686814EC9E16C4ULL, 0x57A9E53E701BCB7BULL, 0xDA99D0649F71438AULL, 
            0x996C685EFA14CF64ULL, 0x974ACB6D60C40858ULL, 0x8FF047E94874D48BULL, 0xEA74A4FE71188108ULL, 
            0x9487B96937E0B750ULL, 0xB7317D55D2FFBB5AULL, 0xA9381E2F8751064DULL, 0x9AE9842896F614EAULL
        }
    },
    {
        {
            0x652046668C23CA20ULL, 0xB5748165F78CEE67ULL, 0x33A93E0CC659807EULL, 0xE468CEF37ADC33A5ULL, 
            0x86D03493E0C4F621ULL, 0xDBD48F76BFD6915EULL, 0xD45342F7A4906283ULL, 0x453C44A26E7CE4F2ULL, 
            0xD5CE1159E9DFCB1AULL, 0xF673B3C72C3289EAULL, 0x84A92C1F13BF5EE0ULL, 0x5D9104C6ABD634DEULL, 
            0x1C2F9C374CE832AAULL, 0xBDB3A2E29D5B01EAULL, 0x04E9ECE8E43D03C6ULL, 0xBC3198080C00A749ULL, 
            0x392D3D6D8CB555D2ULL, 0x668C3145FF046BF0ULL, 0xA143D388A1E3950AULL, 0x30F92749E5E620A0ULL, 
            0x45F94B71BCF27460ULL, 0xD9224D9F3EADB86EULL, 0xCD08983534CC776BULL, 0x623F24DDF97D8BADULL, 
            0xE43CF0BF65ECD0C1ULL, 0xC1E9730880F15A5DULL, 0xE7E9420BA99A8562ULL, 0x8D2B2B0C5B4D24A3ULL, 
            0xA6FF3BFDD1AE5BD1ULL, 0x396CFDFC23AD7705ULL, 0x85C1FF9A17494BA0ULL, 0x4EA02BFDEB43BB97ULL
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
            0x7FCE3E3704FDFDBCULL, 0x766C95E4C9D9BB25ULL, 0x1FF9F670F3B13024ULL, 0x4EF518C9D5BBB075ULL, 
            0x702C0560BA4E7650ULL, 0x32A0026518933363ULL, 0x027CAADE8AE24F26ULL, 0x55DF9BF80D4884C0ULL, 
            0xF9542EA2E51BCC03ULL, 0x4C94D0922DDAE309ULL, 0x43194498A94CE3C0ULL, 0x9D3D33100833CFEAULL, 
            0xC1384AB981D8B572ULL, 0x8056C5716A5261C9ULL, 0x1BE66647BF7A4D0AULL, 0x477EE9E74832959EULL, 
            0xEEBA9EC96B4C7BC3ULL, 0x15E610CA80032AF1ULL, 0xDCE7D34CC2C30E57ULL, 0x08DE07EB7C7DD2DCULL, 
            0x3717478CD474D786ULL, 0x8322D03BA5B0EF31ULL, 0xC0C4564171B3802AULL, 0xC39F13F17FFE7CB8ULL, 
            0xB7B76EAC00EC144CULL, 0x4FF2FE029C63B484ULL, 0x4DF50D0A9F53D5BDULL, 0xD8EBF2E5AFD59341ULL, 
            0xDFCCAB6F436BEF4EULL, 0xD1324724C3E2B816ULL, 0xC0BBC3787495FF44ULL, 0xC7022B4216F4E5DFULL
        },
        {
            0x85F9BFC1A369DC41ULL, 0x80C6C3A022A311DAULL, 0xE5D50D6CCB121282ULL, 0x7DE04B7E0DD89A1AULL, 
            0x810E1069A858D1FDULL, 0x5B1A654689B3026EULL, 0x39213D914F575A67ULL, 0x4F27AE6B9823F0A5ULL, 
            0x725D1844506310F1ULL, 0xD2E42E5A528602C8ULL, 0x9CBF6338F865E1B5ULL, 0x785D893DC5E53113ULL, 
            0x93E3910FE02C8535ULL, 0x1515E1AC18DDEE80ULL, 0x31EF950E9C919E65ULL, 0x46D9EC04D7EA896BULL, 
            0x195A86BC65131C0FULL, 0x99E82D29B04D3938ULL, 0x82A0BE0D7419AA50ULL, 0x25AD3C5B65442258ULL, 
            0x0CC6C8B60C52F3F9ULL, 0x8A96723B1B5DE776ULL, 0x62F3AC7AE12B3998ULL, 0x3FF870E343A403B6ULL, 
            0x5EE19F8C8DD76C2CULL, 0xB24D09A26D4AF11EULL, 0x78F48D46D40827E3ULL, 0x3F1D8E075699E37DULL, 
            0x1250A70091D1763BULL, 0x95A15D037F526C4EULL, 0x7F2A7A41EFE6937EULL, 0x0714C0FD9D3A5B57ULL
        },
        {
            0x7434F590A5665374ULL, 0xF2073779E692B1CFULL, 0xE4E46A01DE5740D7ULL, 0xB32594C97B120CC6ULL, 
            0x2DDDF54E49902C1BULL, 0x6A4A7E0217B4993CULL, 0x76D3AFA544E7CD8BULL, 0x5D022ADE36AEC694ULL, 
            0xA59A7C54C567EF3FULL, 0xEDCE6BB05E97EE9BULL, 0x048169885C58C2A8ULL, 0x79A5338A83B5ECFDULL, 
            0x7F5FF2E9EEDBF2D1ULL, 0x966C7CB626649007ULL, 0x0D8A9621D9369610ULL, 0x082FCD2F8351E273ULL, 
            0xF4EB2D8E5A33AFA9ULL, 0x268CEF462C43AE5CULL, 0xCF6651C35238F5ACULL, 0x7331852BAA625D96ULL, 
            0xC62EF5E1425AD73BULL, 0x66B41DB23BA5E048ULL, 0x43681CD10CF623A4ULL, 0xF342F31A68603310ULL, 
            0xB71882B8C2E92508ULL, 0x217E7864788368EFULL, 0xD2D034340F3ADB1BULL, 0xC656A0DE84FF7C70ULL, 
            0x1ACC74ED7CE4EF39ULL, 0x58A0D3C4E6E4556DULL, 0x65A3461B69CB1258ULL, 0x594EB106EEF74CEDULL
        },
        {
            0x9EB5DA70EE032D2FULL, 0x4400EFE41CD14695ULL, 0x2A6305ADB3F4A978ULL, 0x4A9BDA1FCB405011ULL, 
            0xDF453E55B3659E1FULL, 0xFF1DE4F3CD426C58ULL, 0x38F56FA0DC08A308ULL, 0xAF7E4BA48C9656EAULL, 
            0x5F3AE0BEF88EA464ULL, 0x3E11998650CC2728ULL, 0xA925AF8FDD3D0805ULL, 0xC593CB81EB60B4F5ULL, 
            0xCC8DB60D1E0FA3CAULL, 0xE079B91FEEE4BB54ULL, 0x6AC2BCA4CF7EED9AULL, 0x2285150749DF39D6ULL, 
            0x2B19D011E51BA3CCULL, 0x6B625AC3070034BCULL, 0xFDC22B99625D4E51ULL, 0xB6728707E0B40656ULL, 
            0x63C83ADCF6E33B68ULL, 0xA984C74DD4650933ULL, 0x85BFFA41B305F8FEULL, 0x99B8DDF88EBDD9F3ULL, 
            0x9EA09DF97BF5DDC1ULL, 0x717F1155059F9A37ULL, 0x0359266C7D1FE246ULL, 0x2D421C52A67A259EULL, 
            0xF929FD2900B9C6AFULL, 0xEE96151ACF884B0AULL, 0x5F76CCE9DD253CA4ULL, 0xFD8321471F805BAFULL
        }
    },
    {
        {
            0xF802ED75BCA29063ULL, 0x892968AE06F550B6ULL, 0x98926DB9611532D7ULL, 0xB5BD665780F6AD73ULL, 
            0x415C549D3F5D1F7FULL, 0x2A0EC692E214203EULL, 0x5A43742319D98DCAULL, 0x565F6877498E0EA0ULL, 
            0x3B085FF3B9DA5E1DULL, 0xF8B5705DAE56BBA6ULL, 0x14300BDCABF51CB9ULL, 0xB6A25AF722529F49ULL, 
            0xDDCC37428660F4F4ULL, 0x7B5E6C5BA21615C8ULL, 0x0F0C63B586F8DEECULL, 0x6C5AEDBC3936E628ULL, 
            0xF3E35E9EED077D4FULL, 0x4B67C66978D49297ULL, 0x5107FF16CF451D2EULL, 0x97D59AF04175F785ULL, 
            0x80D497DA49270322ULL, 0x146F8FB55F41CF84ULL, 0x14192C0124B3F7D9ULL, 0x9167C03A02A49F08ULL, 
            0xC6B587938CCA3D5AULL, 0x6EB72EC6A75C8B2BULL, 0xAB32340AC2BDE01DULL, 0x6B202733C8193815ULL, 
            0x49880B706DE2A026ULL, 0x701F407EACFC096DULL, 0x0AE69614B8D206FFULL, 0xC34D6685219D58D9ULL
        },
        {
            0xA0462EE1EA8198DFULL, 0x1E7A0DE0918C3DB6ULL, 0x5843DA668B4DEDCBULL, 0x27534C312C627BFFULL, 
            0x285DEE64B8E58100ULL, 0xDB9F8AFCEF464E5FULL, 0x87A788FE406DB5E2ULL, 0x536606A642FC30DDULL, 
            0x5D45A4F4B739489DULL, 0xD7901F73428E2533ULL, 0x23C366C6E1D8A312ULL, 0x1BC866C22F443FD1ULL, 
            0x1CC3AE3EDE75A466ULL, 0xF9D080D4EEB004DEULL, 0x0867065AA9A1F042ULL, 0x6EA8AB108B612919ULL, 
            0xEA52ADCD99DD6A4EULL, 0xD97E3F544853D364ULL, 0x2E6B47D1D0BD544AULL, 0xB8E39FA1E6E70BA7ULL, 
            0x612CAC1A02B5E5F7ULL, 0xE1A71A501F047CFCULL, 0x0F994160E5CC1BFAULL, 0xC56C944365B1551CULL, 
            0x78BC0612E53649A2ULL, 0x6F0C7DD0005182B7ULL, 0xBF9CA5799868F411ULL, 0x7007858831EE9E8AULL, 
            0x13C7DFD258ACC489ULL, 0xA31DFA0F57256AA2ULL, 0xCF1E33163A3BB07BULL, 0x1191EAFFBF00528CULL
        },
        {
            0xACDD94C468BEA8AAULL, 0x72EF002FBD2C853DULL, 0x81A612984C117967ULL, 0x4380D578A64E4BAFULL, 
            0x714EA8F210BC477BULL, 0x114CB29526DB040DULL, 0x3501AD0EF67B088EULL, 0xAEACFFF020476A65ULL, 
            0xFC1DE13AC415C2ACULL, 0xF5C2F6661ECDB84EULL, 0xB9B3401A29282CF6ULL, 0x0289AFD3655DDA77ULL, 
            0x25E0EA3D5CB6AE92ULL, 0x56B70EE96675AAF0ULL, 0x077787643E5E2D1AULL, 0x753305205BB48C1AULL, 
            0x85D7F650ACF52197ULL, 0x1D28DDEE74BFE8D1ULL, 0x3749490635A24B38ULL, 0x62403244429778D3ULL, 
            0xFAEAB5CE2C8E5817ULL, 0x790E7B8FC8FC18CCULL, 0x5DFE5E115734DD45ULL, 0x549B691F46B77C1DULL, 
            0x898DB3A547A934B8ULL, 0xDA37FC29BFD7D691ULL, 0x838F2354F440F61BULL, 0x0D41E1BB687329A2ULL, 
            0x1F227F49877D6F64ULL, 0xEE529F1C6C9947DEULL, 0x438665968EFB68DDULL, 0xBADF416632B5B391ULL
        },
        {
            0xE154216DD0AEC1D4ULL, 0x3FF07B8C265E61ABULL, 0x454BA0A6A19BF770ULL, 0x4A230378883F08BAULL, 
            0x811F5CB80D132C7AULL, 0x07DF2437804A8443ULL, 0x04F5AFE27FACD2EBULL, 0x675A15BB6AC682DDULL, 
            0x846571115B747875ULL, 0x161261A5B85C46D5ULL, 0x1B526AED1CFBDB11ULL, 0x91E37C8E3A843ECCULL, 
            0x52B72FFFD4CCA3EFULL, 0x38A64397E58153F8ULL, 0xF89220C25CD34BE3ULL, 0x93D4DD925BCBC20FULL, 
            0x796D098FD3D789C6ULL, 0x206AB73290C35182ULL, 0x29A665910803715BULL, 0x91CF190E4CF2C110ULL, 
            0xE11A1F356089FA83ULL, 0x5A4579DD25BBB19CULL, 0x592BCC8428F4CFE1ULL, 0xD20DD5A3ECA70CF1ULL, 
            0x0B4B04CDE69A3F94ULL, 0xB16318A9EDAA8827ULL, 0xD8A04DAD9211F406ULL, 0x49E5AE2FD818B0B2ULL, 
            0x2D65237381142F8FULL, 0x03DE6523873EC111ULL, 0x8BC319B39295621DULL, 0x2F094255811964A1ULL
        },
        {
            0x91210F41EC3B637DULL, 0x0ABEF370A4E9EAD3ULL, 0x1BE271A9DA288FBDULL, 0x68328021986FDF38ULL, 
            0xFFBD735F23F18A7AULL, 0xED131A1990D4C6B7ULL, 0x67C215326F65DE57ULL, 0xC83423C2BFAE8F01ULL, 
            0x25539D3D6DAC8015ULL, 0x3C5A3EEB983EDD67ULL, 0xDC3D9FF322E02BD4ULL, 0x023EE78483938C18ULL, 
            0x73018B92174D6C2CULL, 0xDCA59A8F98C7011EULL, 0x601DC8624C85F5A3ULL, 0x9AB8770943221D6DULL, 
            0xFD478C967CBBE377ULL, 0x1DF16FB9CAAA9DF3ULL, 0xF820171F0232E5DFULL, 0x18832AD452AB4FDEULL, 
            0xADBD262B57143FDEULL, 0xBA1D73C78AD34AB4ULL, 0x5C467CB17A580D50ULL, 0x7BFBD33140564702ULL, 
            0xD59D3EFBE5C965CAULL, 0xDF9A07AE13EDA31AULL, 0xAF39511C68BA2FEFULL, 0xC972DE09C7C45079ULL, 
            0x72EB28E40DA0C7E2ULL, 0xA21E9485963D8B45ULL, 0xB0692CA1BEA47682ULL, 0x03F7B16FC58B4F9EULL
        },
        {
            0x2857318849EA3F67ULL, 0x6F26B9C248689364ULL, 0x5DA34D6D3A03C0E1ULL, 0x3DC8452AEDA1A385ULL, 
            0x7C7CAEDA2F6B5C68ULL, 0x3A687E311714BAE9ULL, 0xE03B7AB6392000FFULL, 0xB2D8F760D9698D90ULL, 
            0x7A93DCDE64F373EEULL, 0x5DBCB9662577D653ULL, 0x27724030EF7F8EBEULL, 0xDE9EDAE8FCCBA726ULL, 
            0x904790A9F50D2D3DULL, 0xC7A558E41D891D44ULL, 0x0ED1C671969250D0ULL, 0x6D0AD9C798D6988CULL, 
            0xA3A27DBB5786385FULL, 0x7E4D7F4DB9124C4AULL, 0xC0A3142C1AE9BF1CULL, 0x4A5E8253D3704E67ULL, 
            0x6A89519DE22ECD32ULL, 0x57A0A840700FF072ULL, 0xCE25D3F8093FC140ULL, 0x29E34BDAA4E8F00FULL, 
            0x50962A5709775E34ULL, 0xB1160989B392EED9ULL, 0x8A55287452EBA0ACULL, 0x27CD39432DC1DC02ULL, 
            0x16CD1C48DEB9E1B1ULL, 0x1A518406FE85A3F3ULL, 0x5279471F780935B6ULL, 0xC8170EF1FB32C9B4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseGConstants = {
    0x9B44EB4BC23BA6F2ULL,
    0x1BEAEA7017488F86ULL,
    0x2BDC0358A91CBD44ULL,
    0x9B44EB4BC23BA6F2ULL,
    0x1BEAEA7017488F86ULL,
    0x2BDC0358A91CBD44ULL,
    0x9CE876A7A4531DECULL,
    0xF5F11F6E3F1E99F7ULL,
    0xAD,
    0x53,
    0x4C,
    0xDF,
    0x98,
    0x4B,
    0x82,
    0xF7
};

const TwistDomainSaltSet TwistExpander_Achernar::kPhaseHSalts = {
    {
        {
            0x905C74E329A1B64EULL, 0x1B1A457FC487759BULL, 0x72D2A073B4AAC412ULL, 0x7E4D3901DE028099ULL, 
            0x328FA292E17F8105ULL, 0x87B2150186FDCC66ULL, 0xD0623ACB2DE34871ULL, 0x2A5B70E178590A73ULL, 
            0x98AAACA1295D1719ULL, 0x0E41D6ED6D5B7B09ULL, 0xCAF3AF9BB9CD6D13ULL, 0xBA093EF540248F37ULL, 
            0x3D0ED7ED1EC99C0AULL, 0x80881CB67A858B6AULL, 0x7112E69501AB2D5BULL, 0x01C73BA8F9E89A5EULL, 
            0xA996CEB26ACDB2F1ULL, 0xB6B608FCD1917FD8ULL, 0x837D353341233321ULL, 0x9EA1D086E7B2C4B1ULL, 
            0xC394D624C73F42EAULL, 0x659580AED758CEA4ULL, 0x432ABF4062A5C42AULL, 0xAB6B27678DE85A4EULL, 
            0xD458A5A64C5F336AULL, 0x4D8D45A54573BC11ULL, 0xA88AA8580889D9D4ULL, 0x61C36AC501FBF71CULL, 
            0xBBF0F0CDAB29DFABULL, 0x90E2492D28E0E73CULL, 0xC57727E31CE087F1ULL, 0x518417EEF42ECD7EULL
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
            0x7AADE8ED6F72C3B2ULL, 0x8FB582DDEC7E991CULL, 0xBC6B302C16C23653ULL, 0x8DE51B6E1CA238FFULL, 
            0x40CDE01705E3659FULL, 0xD73D3F68B5CB73DBULL, 0xE768C47377D761EEULL, 0x7C69AAFC010F75CCULL, 
            0xDD4D447CA6F0B282ULL, 0xA85BD9FB5434C47BULL, 0x270985F1EE1FF5A8ULL, 0xE9FA7D17A5C13836ULL, 
            0x864D3FEE1CD3F440ULL, 0x6FABDAA1D710A09AULL, 0x8E95F756127073D9ULL, 0xEA3C05734B8504D4ULL, 
            0x9F1A1C02649115EFULL, 0x5F1C0B98C4F12321ULL, 0xB05CCFC7DCC8D2BDULL, 0x6B7B8AA29E72B1DAULL, 
            0xA1E873F7B958737AULL, 0x6ACED1DE4D987C24ULL, 0x0C5EE5E3C349D4A2ULL, 0x4C596DE51BCFBE9FULL, 
            0xE21153B8E3461DFEULL, 0xEF5FA8A179B1B3F6ULL, 0x12903F5FD194F8BEULL, 0x1777E2F4A7ED0F37ULL, 
            0x8D4C26C2C7142828ULL, 0xEDF0BC6AC737C5ECULL, 0x0C1B28A3BA467E4EULL, 0x150AA2B875F5A7ADULL
        },
        {
            0x4876C39569A9921CULL, 0xFF65621FC7945202ULL, 0x759DB21F6465181AULL, 0x63D5F199D1C4A079ULL, 
            0x19755BCE26195E46ULL, 0x57390EC89B65D5DBULL, 0xF4D4ED875F9EFF76ULL, 0x231FA28246E765F6ULL, 
            0x0F328769951D6B29ULL, 0x415C2A71FA281605ULL, 0x37F9F51811FE4EB2ULL, 0xC1420F97B894D0D4ULL, 
            0x6379DDA3464627F2ULL, 0x16B2A44CF867C2BAULL, 0xC957767AE7F86C89ULL, 0x2798C24B20BA8647ULL, 
            0x387E2921C5D7A787ULL, 0x42353B773033D5F6ULL, 0xD23FE33FC27A49BDULL, 0xF605BF40FA2CF578ULL, 
            0x38071451A9830C8EULL, 0xFAEEAB0612F2EC1CULL, 0xE2099A87B0A93F1FULL, 0x639108DC85AC467DULL, 
            0x7AA80A69AC5D5307ULL, 0x36B1D2F0992E0750ULL, 0xB56BD37E5555CF3CULL, 0x1230AEE27E44D199ULL, 
            0x49F153F2DC491E0AULL, 0xF8A3D2BA007623E9ULL, 0x95249896DDBEBA16ULL, 0xA4B75D1C0DFFA43DULL
        },
        {
            0x7EFA9CB9E6CDD9F8ULL, 0x99E4F3E291215CAAULL, 0x0DA7595B2856A216ULL, 0x110CF184789CAE14ULL, 
            0xBD0604C17C11AE98ULL, 0x41168302263FF24FULL, 0x4300E4E5CB8B4224ULL, 0x83A3FB3B06896675ULL, 
            0x49F4C519840B3308ULL, 0x068258B988FF8DFBULL, 0xCBFF3F8F176F3B40ULL, 0x8FBDF325C024E385ULL, 
            0xDA0AE1A393A8765EULL, 0x459C66276734F881ULL, 0x69C74311E3985E1CULL, 0xDF5965BA60966124ULL, 
            0x202FEB1CBFC5846EULL, 0x7715B97A15AEF71DULL, 0x3B649013CEADC99FULL, 0xE12A420E2D16F278ULL, 
            0x2966561D5077E261ULL, 0xE8FCECE3287E2637ULL, 0x3DB367E9B37FC645ULL, 0x9F80359B22F61B3BULL, 
            0x2BE0CE33D8E67786ULL, 0x2C258DE5DCFA7B59ULL, 0x9663301824B2EA8FULL, 0x14BBADDAF87D9104ULL, 
            0x557C65E39FE5BB68ULL, 0x6E3F30E29E5E44B7ULL, 0xAAC44A854D00BE49ULL, 0x5DB08ED49CE2BF5DULL
        },
        {
            0x58A1A7D89B3BBBE7ULL, 0x15B717A277C1C84FULL, 0x85E7475A18F60671ULL, 0x31F35B1C8F57AFE5ULL, 
            0xC20B4D6CB8B165A9ULL, 0x6BEEAFD606B52804ULL, 0xDB477EBA5046AA51ULL, 0x877925F161CDF51EULL, 
            0x8B4685DC1CCB5208ULL, 0xE0860714967271F7ULL, 0x57598F7A2AC006FAULL, 0x9429C5FAA96B0FDEULL, 
            0xDE1D629842CB5B48ULL, 0x287177CCCB7C6D48ULL, 0x833593B8CBE825BAULL, 0x55FE4CA338D507CFULL, 
            0x044260702C605B72ULL, 0xE4C7A16E9228D297ULL, 0xCC23BC125B18EC6CULL, 0x2F32F140299E3A75ULL, 
            0x74EBD75E9E859FD3ULL, 0x2DDE715DCED4B2A8ULL, 0x5F42591576943777ULL, 0x36A5FA27A20A0B7CULL, 
            0x704895F48696E877ULL, 0x1ED8CB8823BB3F67ULL, 0x1FAA9087FA5488DEULL, 0x0908DCBE4F67828CULL, 
            0xE647909867E4643AULL, 0xEC6B3A57F0A4DD80ULL, 0x8D8F39C094A52C96ULL, 0x52E677514CE211E0ULL
        }
    },
    {
        {
            0xE77AC1876C53E9A4ULL, 0x56986A4A77E73832ULL, 0x56C27E604DBBE178ULL, 0x781FD293374CEA61ULL, 
            0x1344ADE95A7913FAULL, 0x0E4E0177314525D3ULL, 0xC32ADF8E5B582FDEULL, 0x92F4CAC6C5ECF638ULL, 
            0x8638D7B7EE27F423ULL, 0xB202382752A4A56DULL, 0xFC1CCDAEC0A76C21ULL, 0xD39F688D90BBEFADULL, 
            0x15FF5FA474B996FFULL, 0x8A87961F146F756AULL, 0x87EB5A00947D8EEFULL, 0x0935B55D063539FAULL, 
            0x68628D127F3C286CULL, 0xA5FA50D4559D5C5FULL, 0xC8F29CF0E7F804D8ULL, 0x3971D3C9C2459FC9ULL, 
            0x8BA1D874677B7260ULL, 0xE37FB30FBDE4B3F4ULL, 0xE93BEA336D1D9ACDULL, 0x2F12178B676963A4ULL, 
            0xF1830268D8E98B1DULL, 0xFBAE79960535E035ULL, 0x08DD92AFA98180F5ULL, 0x8A1C90B34D6DB389ULL, 
            0xEEA5444E2F96045CULL, 0x7A394092118E0C31ULL, 0xD36F053C6387FE6FULL, 0xAEEDD64173E2A538ULL
        },
        {
            0xED199B49E1ECE336ULL, 0x6BE1EB839346CA1CULL, 0x6BBC0CE79597FEEFULL, 0x7287E39E8E56BBE9ULL, 
            0x9C603344E1C234C2ULL, 0xF2D8F5EB38427A18ULL, 0x7A2A981CA419A568ULL, 0x5A66C02AD6EFDC9EULL, 
            0xFBBD497B30B4E041ULL, 0x4BA02742D6C54AA7ULL, 0xAE91CCFE1281B1B6ULL, 0x62DB7DEC7C1EA20DULL, 
            0xFA5CF9B1EBE096A9ULL, 0xD23806DE3ACF53C0ULL, 0xCF549DD4CFA3D748ULL, 0x2D4ED7C6DE32332EULL, 
            0x4035EF5B2FB3F47AULL, 0x7C4E845FDA82FC4DULL, 0x11297A8051CB36E7ULL, 0x33812B406CF6359DULL, 
            0xFFEF051BEA1C9CBDULL, 0x5A0A7143F8B5541EULL, 0xC94502000B4C904BULL, 0x167432BF8216120EULL, 
            0x7EADD50F53A8FC4AULL, 0x79156885C8CA6111ULL, 0x8834DF987FBD79B0ULL, 0x40140F14418B2AC7ULL, 
            0x806F38373669064DULL, 0x3D1462E1A15322C3ULL, 0xB8F9E53947D35282ULL, 0x862E9AE38662D12AULL
        },
        {
            0x258F7A990405706BULL, 0xB4A41FA4882590F4ULL, 0xE933040D1857014FULL, 0x5B7920BAFFA6142FULL, 
            0x086BDAB042FB4BAAULL, 0xA43C11E297504902ULL, 0x980088F1EF52DC0DULL, 0x4CE710ABDD7D9186ULL, 
            0xC63E5EFE5682845AULL, 0xA15E9B5CB3A8CB29ULL, 0xD01EE4734A375124ULL, 0xAF482B391BD93CDEULL, 
            0xA07AF0777591B104ULL, 0x9329C0AB67EA2DE6ULL, 0xF669A8E272D93384ULL, 0x3816D9500CE20DE2ULL, 
            0xB59D5807BB567AA5ULL, 0x01A2DC4E8F4E0503ULL, 0xCAE0F78097C5ABDEULL, 0x765E5714FE727C2FULL, 
            0x3D9598871A37012BULL, 0x88F7A195BC4374C2ULL, 0x353897A5BB527FEEULL, 0x5813C321CDE064EAULL, 
            0x4E9FBC3BCC580B41ULL, 0xA8BA99FCEA109229ULL, 0x6A425A58D316EB34ULL, 0xBAA771A64FAED811ULL, 
            0x1E599CD4D55C6419ULL, 0x634A872FC6B32B99ULL, 0x051E29D85905B09FULL, 0x654AC0288265DE7AULL
        },
        {
            0xD2460921934337BDULL, 0x8F593F63EC0C25E4ULL, 0x6AA714C124DC726DULL, 0x8B2B757B3DC00CE7ULL, 
            0x14AA9A167D00DBE8ULL, 0x22E01692D359D6EDULL, 0x5D94B1E5E78C342DULL, 0x58355DEBD5B87642ULL, 
            0x958670819ED4F69FULL, 0xD1CD339E2B35F4B2ULL, 0xF602915F3BD3F00EULL, 0x1C76516333039D08ULL, 
            0xC00F36B686CF567CULL, 0x15BBDCAAEA0C09CEULL, 0x5273D6A52B011305ULL, 0x7255F69F211A5F8CULL, 
            0xA700907B4FE29E53ULL, 0xBFE8AE51E2FE2CAFULL, 0x27BA7553A27C0426ULL, 0x02FE890971ABF4EBULL, 
            0xA909BDD33664579EULL, 0x395487315D0BE39FULL, 0x7E83E7F7831FEFDDULL, 0xD5F858C176C10DD2ULL, 
            0xF5EE9C5C43312058ULL, 0xDA929D6841326F38ULL, 0x2487E356A1585E5BULL, 0x00601657618A9FE8ULL, 
            0xE9E219D3E0002944ULL, 0x4CF7666FEFCFC6CEULL, 0x11512B0495401C00ULL, 0xDA552395CD0C54D5ULL
        },
        {
            0x9001AAC2624F5A96ULL, 0xA2C1A073DD09B034ULL, 0xE4E2061645CA4460ULL, 0xB536D57BB61FF319ULL, 
            0xE15A360EB41FF83FULL, 0x084447DC0F553A82ULL, 0x5809C8815F3AA4BCULL, 0x8B757579B22A05C9ULL, 
            0x436A5C83EEEA93A0ULL, 0xA9D8DB900BF7DBE8ULL, 0xF3C2F2DDFDF7F36DULL, 0x86CC107321D7B470ULL, 
            0x1BC84318AA60DFF9ULL, 0x555EF260695DE610ULL, 0xB152D90F67293414ULL, 0x4678D75616B037F1ULL, 
            0xCE871A47BE2A8CF5ULL, 0x84EFC548C69DEAA1ULL, 0x09A88FBEE23F8D5EULL, 0xA3552C770B163CF2ULL, 
            0x7A7B23CF0EDF0D99ULL, 0xD37503F164B7A822ULL, 0xDF75B41DD195DC74ULL, 0xCE78CF4AADDD4C61ULL, 
            0x98FFF2D1566E8B97ULL, 0x8D752C60C3EF503CULL, 0x062835D6CD274A18ULL, 0x779A36D51960E61DULL, 
            0x6CE677634C27E694ULL, 0x7A62190BB7C3FC3AULL, 0xA4AF97604BA0281AULL, 0xEDB7FB914D4E44E8ULL
        },
        {
            0xEE8E8B99CD275FB5ULL, 0x73CF72AB00EB2F4CULL, 0x28D44414D9F226EDULL, 0xF1F136D57C3F5D73ULL, 
            0xE991CE7975A28C87ULL, 0xDFD15E55F54C6BC0ULL, 0x633CEBBFA6E76E1DULL, 0x5CDFD80939E8E932ULL, 
            0x7515E9EFABDD55E5ULL, 0xAB7D3EBB22D8A366ULL, 0x43F92835C48A157CULL, 0x6408814251BD07EFULL, 
            0xF642947484C22583ULL, 0x09C02CCD938406F3ULL, 0x4A3973BF5570A9E0ULL, 0x6D416BCEC67960AAULL, 
            0x4D155D955EA15E7BULL, 0xAD0626BCAA5670A3ULL, 0xE479715910A3E34AULL, 0xBA8019757DDBD0D6ULL, 
            0xC398EC7E0DD66CD1ULL, 0xB1EAC4DB4A6AB92DULL, 0x44F9B23D75AC98E2ULL, 0x1616F051BF893197ULL, 
            0x2C4F9137B247958DULL, 0x14E9340A8CD92C74ULL, 0x700A4F3371C91ABEULL, 0x1C203F164548A39AULL, 
            0x5AB168A6C3A4C92DULL, 0x780391609391D27CULL, 0x76ACEE06F8E4C302ULL, 0xDA21D50C9BA52276ULL
        }
    },
    {
        {
            0x641FE63882CF433AULL, 0x842A1AA61C95A7ADULL, 0xA40D34E4E75E3E8FULL, 0x1157A8AE1CC3332BULL, 
            0x70E96825ED750FCEULL, 0x40E4E08AB4FB57ADULL, 0x6B2DF8308FEDC70BULL, 0x6CF69AF653ADBD07ULL, 
            0x2741DBE5E1AAB7B9ULL, 0xE45705148F0363E5ULL, 0x30EE1B865FFD72BCULL, 0x6A7BDD8A640F36C0ULL, 
            0xA82A794466481C2EULL, 0x9ABF86AECFCCC8B0ULL, 0xB1A95C19865D3C85ULL, 0x44776BC2516B440AULL, 
            0xBA84D83CE83D085AULL, 0xF6F37E8CE65D55B0ULL, 0x4874222256C09AFEULL, 0x385CC3152F8C59B3ULL, 
            0x5707651928CFC708ULL, 0xCD80F6E5FC09DD7EULL, 0x48F553B34C00325DULL, 0x3098F1BAFD428252ULL, 
            0x6C474E92D4B0811FULL, 0xD1086012E6123C56ULL, 0x5BDEF57F97FA5DC7ULL, 0xF0C11FFC4F475EE1ULL, 
            0x2FC49A4AD5487EF7ULL, 0x3F05F40EA9B50D53ULL, 0xB79F7523BEE8CF41ULL, 0x8F1A63A944607B77ULL
        },
        {
            0x8E176DAC5D8F1F78ULL, 0x222DF951DDF73CCAULL, 0x8C713A49FF619686ULL, 0x407D637CD40D6CE7ULL, 
            0x16CCF55EF8D833AEULL, 0xC092018FC2CC278CULL, 0x267068A3C2047FDAULL, 0x0D14AFC73F0BB6F7ULL, 
            0x971DF7999F76CF65ULL, 0x0C8AF02E802BD43CULL, 0x9F0EFD1CEAAC54F8ULL, 0x7E13203F6E471D49ULL, 
            0x2BA7E378098A014FULL, 0x5D56B850213EE066ULL, 0xD5B7B2AE99C00DADULL, 0xC78B7440141B6D30ULL, 
            0x8FDA616ADC457547ULL, 0xEBB2148D1CFE8223ULL, 0xEA9ACE120D33003AULL, 0xAA8EDA7809498D4FULL, 
            0x04CB1B059A312282ULL, 0x07ACFB3302802669ULL, 0x72C89BB2BBCA71F4ULL, 0xA7C4C1A1FD4CD67AULL, 
            0x7330E4D9922268C4ULL, 0xB2442266A74FE2CAULL, 0xE764B8D85AB1D493ULL, 0x6C8B16365F988467ULL, 
            0x23E2D4DE24EC1527ULL, 0x811BC3B371EC4837ULL, 0x0E39490F736E3309ULL, 0x816ADE33C59D62E5ULL
        },
        {
            0xC059ECF60D223BABULL, 0x27173BB981DD3779ULL, 0x743E55025231785FULL, 0x969DB64896483CA4ULL, 
            0x70C73BBD1A7727B0ULL, 0x8CF77B5A0208779EULL, 0x55D1AB95583CE481ULL, 0x3B3AE00F006F11F5ULL, 
            0x7C98C3E4D450527AULL, 0x7B6B1BEBB9FAD07AULL, 0xA66BD4225FD1F3C9ULL, 0x8F8D1D7F8D496907ULL, 
            0x67FBF3EE9E50AE09ULL, 0x10A7C73D40210FD5ULL, 0xDE9615E3C698BCE4ULL, 0x701CBD2C3528833AULL, 
            0x333CFAD2A95FEAD5ULL, 0x77274CB122EF2786ULL, 0x217AD1F699F89A54ULL, 0x8C26CE10B8B71E67ULL, 
            0x0AD50DF0894BB373ULL, 0xDCEEDCA86AFBD1D1ULL, 0xC7DE286E3871CF13ULL, 0xA65E611D67BC506EULL, 
            0x514DA9D18DA1A9D5ULL, 0x928AFD7A82F570C3ULL, 0xE7C222B9E10A873AULL, 0xD7683CE270AD4CD2ULL, 
            0x42329A734D8B2410ULL, 0xE5BD3175C3E0E3C9ULL, 0x714669CC22E451F4ULL, 0xC3A55674CFB336C5ULL
        },
        {
            0xF7BC4F49564F8D0AULL, 0x4BF69776C03389F9ULL, 0x6E460DEC70EE7E0FULL, 0xAC318C86F365B638ULL, 
            0x048E4A666CB1057EULL, 0x762E2A116F5F5763ULL, 0x7364C8A6AB5C1D3CULL, 0x77F7038891550FF6ULL, 
            0x71E2F9D7B2E2AD9DULL, 0x7B2A876E19ABAAAFULL, 0x0831C0396D347944ULL, 0x75C2607CC2AFE47CULL, 
            0x4001F5876F099F07ULL, 0xA192F40F300942ECULL, 0x2E0124EB3501F3A6ULL, 0x2092AA28F00EE985ULL, 
            0x8D4B7DD3AB5BE07BULL, 0x69E87D7972E766A9ULL, 0x0984BD78FAF98BE3ULL, 0x18A254524B098AE9ULL, 
            0x09925E83772A95C7ULL, 0xB4CF053F37EF00ADULL, 0x4CD168ABB31F394DULL, 0x351D728069046E89ULL, 
            0x0F12FE85B16CAA5BULL, 0x5E82C00B9C243E89ULL, 0xAD1B8FEEC795CE54ULL, 0xD9EFF5D9F48D761BULL, 
            0xFC7C42BA2FCF923BULL, 0x7E3902639D71CA8FULL, 0xC43042397E25AC3BULL, 0x5DAFDF049525CDA3ULL
        },
        {
            0xE12BDECCFE23E137ULL, 0x493B2C13E658157BULL, 0x80B9527A85B5A644ULL, 0x4F032ED87FEB3AFBULL, 
            0x6121BA1B8342311CULL, 0x8F4B783AD008C1BBULL, 0xDC22B8EBAC201C6DULL, 0x4B7999EA4D4B8FA9ULL, 
            0x082A8A30C9865C29ULL, 0xA71DD72E8E701DC0ULL, 0xF889F70CEF6F08EEULL, 0x8E7F72BF07C05E56ULL, 
            0x6186AFE2A009E6FDULL, 0x7A4210E9C4053D42ULL, 0x6482E8C8A4455097ULL, 0x3D7D8D37B0B62D94ULL, 
            0x0B712FC010A5A634ULL, 0x80D81193B7CCC45BULL, 0x0DCB2A368D45FB56ULL, 0x05F447836303A50DULL, 
            0x9DCEE8E338608A22ULL, 0x010C217A2442C3EAULL, 0xBCA7C3742BBA3DD3ULL, 0x445BFB12FE157711ULL, 
            0xE92D168F8B2E5D30ULL, 0xCE677226C9D6B86EULL, 0xBC48E591EA3AD1CCULL, 0xDCF179446AE77F71ULL, 
            0x842287974351F3ACULL, 0x0FAAF95DDA77CC37ULL, 0x21B88C8D94A8587AULL, 0x08A7FD8464EB17C2ULL
        },
        {
            0x15DB6267B31C2AFDULL, 0x419DEC464BE983D9ULL, 0xA973F204D3813BC9ULL, 0xF8B1BA15F4014F9CULL, 
            0xBA3B626B5CD2E7E7ULL, 0xB9311416DA59196EULL, 0x7836346BCEB23C5BULL, 0x349D2FC42C2CA3B7ULL, 
            0xE47F9937EFED59AEULL, 0x696B219A2E747A27ULL, 0x661F66080CA37949ULL, 0xA82549058017504FULL, 
            0xE5E45E65C3FDCFE0ULL, 0xA135ED1F09D179BFULL, 0x4936162C0DC6AC42ULL, 0x674210CA0E389E4CULL, 
            0x1E9FA00697CDAC83ULL, 0x2E8FBAA8F19AA6DEULL, 0x27A7DF662133A130ULL, 0x8EDC962702F0CE29ULL, 
            0xC5EEC5C94BEDA2F1ULL, 0xD3737D093AF86335ULL, 0x8F62A8FFEE76B2F9ULL, 0xFAF758C272E94B37ULL, 
            0xA5493C79B91E9B20ULL, 0x5F827D0341B21F88ULL, 0xFCDAAEA77295FFBDULL, 0x034AB61C3BF9E1E6ULL, 
            0xB771251D27A66A2AULL, 0x1DDB9D9478A12DA4ULL, 0x70E614D193F7A5B8ULL, 0x5734BF3637941CF4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Achernar::kPhaseHConstants = {
    0x348D77F73721990DULL,
    0xDAE9AE95F760E618ULL,
    0x81B8081C36F2F0B6ULL,
    0x348D77F73721990DULL,
    0xDAE9AE95F760E618ULL,
    0x81B8081C36F2F0B6ULL,
    0xC65B752EBA1E23DFULL,
    0x43B98EE70B648925ULL,
    0x04,
    0xB2,
    0x2B,
    0x9F,
    0x30,
    0xD2,
    0xEF,
    0x89
};

