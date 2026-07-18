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
    std::uint64_t aPrevious = 0xC03A6D4FFA23CD8FULL; std::uint64_t aIngress = 0xF345431634E2A369ULL; std::uint64_t aCarry = 0xFDAD3295328962A9ULL;

    std::uint64_t aWandererA = 0xF609080085D57C6FULL; std::uint64_t aWandererB = 0x9941AEA591EB0E5EULL; std::uint64_t aWandererC = 0xE3BBC075B0507EEFULL; std::uint64_t aWandererD = 0x88950999D65751A9ULL;
    std::uint64_t aWandererE = 0xF4AE9B69D3A5AD30ULL; std::uint64_t aWandererF = 0xF7A7637B9642AA3EULL; std::uint64_t aWandererG = 0xC520EF5988FB7F55ULL; std::uint64_t aWandererH = 0xA2B2E624BC6DA5EAULL;
    std::uint64_t aWandererI = 0xDA34CB229BCB2C62ULL; std::uint64_t aWandererJ = 0xB920194DADADCAE9ULL; std::uint64_t aWandererK = 0x953C1B5ED771FF72ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12714393225238357756U;
        aCarry = 14164080547780799547U;
        aWandererA = 9903529577110526304U;
        aWandererB = 16461939001862938003U;
        aWandererC = 12981491979285120283U;
        aWandererD = 15331886993543859570U;
        aWandererE = 12477909430599882320U;
        aWandererF = 15404120187945489207U;
        aWandererG = 17097373860976721770U;
        aWandererH = 12876575630224444671U;
        aWandererI = 14365403919773257540U;
        aWandererJ = 18172668971129749340U;
        aWandererK = 9446560484665249692U;
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
    std::uint64_t aPrevious = 0xD182228E24EC2882ULL; std::uint64_t aIngress = 0xCE929ED741C67540ULL; std::uint64_t aCarry = 0xE59631E2E9DE7DB8ULL;

    std::uint64_t aWandererA = 0xE205C86CE7E6BEE1ULL; std::uint64_t aWandererB = 0xE0F589A9ED7E27FAULL; std::uint64_t aWandererC = 0xF178F0E196147D09ULL; std::uint64_t aWandererD = 0x80A47DD0DAAE987EULL;
    std::uint64_t aWandererE = 0x92FA96B7C53D8FE8ULL; std::uint64_t aWandererF = 0xEB31937FB76C4EC8ULL; std::uint64_t aWandererG = 0xFF3505695CC177C5ULL; std::uint64_t aWandererH = 0xF6588FE4217F65B3ULL;
    std::uint64_t aWandererI = 0xDCD920D0A95821BDULL; std::uint64_t aWandererJ = 0xE93954FBDBA0F82CULL; std::uint64_t aWandererK = 0xCA88242862DCC951ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 18302417525275495427U;
        aCarry = 16468900707181374556U;
        aWandererA = 14783879902537703652U;
        aWandererB = 12677531842339873449U;
        aWandererC = 10344251109572401188U;
        aWandererD = 18135138871997900919U;
        aWandererE = 15607069566702095336U;
        aWandererF = 15495915966990397016U;
        aWandererG = 13550733798976720125U;
        aWandererH = 16167813709503673811U;
        aWandererI = 18216443478593709992U;
        aWandererJ = 16258076472454629779U;
        aWandererK = 18371945120595645290U;
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
    std::uint64_t aPrevious = 0xF1DC41FDEE96EC51ULL;
    std::uint64_t aIngress = 0x93221742242582ADULL;
    std::uint64_t aCarry = 0xB5B660E5CE83C78DULL;

    std::uint64_t aWandererA = 0x9EAE9000ABD93ED4ULL;
    std::uint64_t aWandererB = 0xF5DE6BCAFF642246ULL;
    std::uint64_t aWandererC = 0xA192FA925B6E004EULL;
    std::uint64_t aWandererD = 0xE0749C08F12E10C8ULL;
    std::uint64_t aWandererE = 0xB4070B9B2C4A550CULL;
    std::uint64_t aWandererF = 0x956FD500A5469FDFULL;
    std::uint64_t aWandererG = 0xB8318E4C4AF8DF28ULL;
    std::uint64_t aWandererH = 0xF92821134D4ACC3CULL;
    std::uint64_t aWandererI = 0xAE8A5D462BBF80F6ULL;
    std::uint64_t aWandererJ = 0xDD3F5CEECC0741B6ULL;
    std::uint64_t aWandererK = 0xA757ECABEFD40AADULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::Sha256Counter(aSource, aSnowLaneC);
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseFConstants.mMatrixArgD;
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
    std::uint64_t aPrevious = 0xA90F046EC5289DBDULL; std::uint64_t aIngress = 0xD943ADE1C506A720ULL; std::uint64_t aCarry = 0x8E31406ADCB137D7ULL;

    std::uint64_t aWandererA = 0xDF58EC6C8B3FA7A7ULL; std::uint64_t aWandererB = 0x8EE52BECAAF57936ULL; std::uint64_t aWandererC = 0x8C490AE0FCF342EEULL; std::uint64_t aWandererD = 0xF7131CDFDE8D6EADULL;
    std::uint64_t aWandererE = 0xA85D9D2BA993BD4CULL; std::uint64_t aWandererF = 0xAB53D10D73C60B63ULL; std::uint64_t aWandererG = 0xE2B51166A52CF637ULL; std::uint64_t aWandererH = 0xB7F06D80A3609B4BULL;
    std::uint64_t aWandererI = 0xB3ECB0F995F44D92ULL; std::uint64_t aWandererJ = 0xF67EEC4036063128ULL; std::uint64_t aWandererK = 0xC2DC4B8DBA37B703ULL;

    // [seed]
        aPrevious = 12152892295308592824U;
        aCarry = 14400251016338118947U;
        aWandererA = 17363732868245976112U;
        aWandererB = 14875287417925093316U;
        aWandererC = 16543900506396887798U;
        aWandererD = 13680603819908428062U;
        aWandererE = 14525949944576132456U;
        aWandererF = 10138899651241682263U;
        aWandererG = 11695226533909880389U;
        aWandererH = 12914275443200830167U;
        aWandererI = 17854220380083489263U;
        aWandererJ = 10845357337913071150U;
        aWandererK = 11295543003288586620U;
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgD;
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
            0xA5A10401D291BBF9ULL, 0x77753328253CF87DULL, 0xF7345423209CF251ULL, 0x63B086F8A6D51067ULL, 
            0x497DED587E7224EBULL, 0x4540ECCCE48604D9ULL, 0xEA6BB985EE422005ULL, 0x930D97696CC089C2ULL, 
            0x46384FC31BA2F095ULL, 0x2BA5F39FBF2156C3ULL, 0x145D8CC5BF1BCA5FULL, 0xC5FB47954F3E4328ULL, 
            0xA0C10ABF347B2099ULL, 0x36B28FB0AF6D72A5ULL, 0xCF83890778B4B0BCULL, 0x08541F1671324DB4ULL, 
            0xB639B2FBDDE09C8DULL, 0x802E7C5B682EBD93ULL, 0x037F00C35B9F4EB1ULL, 0x4A411AAB1D109397ULL, 
            0xEC8A2623A1E7F0C6ULL, 0x122802637FA7EDB8ULL, 0xBAB99A4FD227FCBDULL, 0x1BCC0A1D14D3A114ULL, 
            0x6206E6E5E37E55A8ULL, 0x841F61939179C824ULL, 0x10DD62C487482FD3ULL, 0x27CCE78A80890342ULL, 
            0x08B01C5D6C5176CEULL, 0xCA1B77BD4D59273AULL, 0xF3E70A4576F4C4CCULL, 0xEF68ECFBC7E08DB9ULL
        },
        {
            0x4344AB0DD2F098CCULL, 0x6EBA9A39A0ED0C14ULL, 0x9E9456E15C3A3A6DULL, 0xBE21254951178EC0ULL, 
            0xB514CE8923173326ULL, 0x4B52374389554954ULL, 0xC65514F4DD65EABDULL, 0x4ACF8CF7261043B5ULL, 
            0xA735556A61E61C67ULL, 0x25093109F818DE49ULL, 0x9266F44C1B8AF076ULL, 0xC9DA49902A656460ULL, 
            0xC010C292C78227ABULL, 0x619F9100F2840D05ULL, 0xB41277EAAFF164E6ULL, 0x4611D0DBEA01E79FULL, 
            0xA4751C3589ABB49CULL, 0x0994427EEC3A4629ULL, 0x786FC8F9B2DAA99FULL, 0x9465D0D1F452EB07ULL, 
            0x48C0D299D40CE266ULL, 0xCA1F108BF2F7EADEULL, 0x560C268AED107290ULL, 0x97CF2569DDA690BDULL, 
            0x181F884A343F8BF2ULL, 0x0F27F5FD6669C496ULL, 0xC8C8445E81F41FFCULL, 0xF90BAAF5339A762DULL, 
            0x6D090162F5DC06C6ULL, 0x897AF238B4EE1077ULL, 0xBD2C7397781B2847ULL, 0x8E58C44EFC4BA0BEULL
        },
        {
            0xCB5E858D7C5F5F74ULL, 0xA134A095D6C74051ULL, 0x2390C34DF71FC66FULL, 0x2FB8DC796057D221ULL, 
            0xFEEA5125B5457621ULL, 0x585908688F359407ULL, 0x91FA4D077348D800ULL, 0xCD13CE59FE5DFBC4ULL, 
            0x0642876EC8A92DC0ULL, 0x9E19249E7D0934F3ULL, 0x108DB54938A39ADAULL, 0xE1BFDEE65924417EULL, 
            0x4E88BE54AC5986B4ULL, 0xCDFC15568B2F30E0ULL, 0x7AB4911EA6CC58A3ULL, 0xA3A3AB4ACEF365BEULL, 
            0x4FF6AB594D218522ULL, 0xC9FBACFBE1E02122ULL, 0x3FD8184B31CDBCB9ULL, 0x0E66D470D762E34CULL, 
            0x24B9FA1189955082ULL, 0xC7957BEDCFF47192ULL, 0xCBCEF4D92EDF1FF5ULL, 0x176A8E4C9EB8B435ULL, 
            0x3489D37AB501734EULL, 0xA115BDEB1B4BE615ULL, 0xC314FF059B72073AULL, 0x210E2D7A80C84D0DULL, 
            0xBEEA1E03B10CDA55ULL, 0xC3C5243824DC7F97ULL, 0xB71A8DBAD60D157EULL, 0x9F9088365F1348A4ULL
        },
        {
            0x9D7C11B983A2F359ULL, 0xB7B6E999BD5B26E0ULL, 0xA49D5D799812C862ULL, 0x83DF6504D697ACFEULL, 
            0x5FB5F6F1786CFC75ULL, 0x17C70F5F7EC6D499ULL, 0xEDD616868B47B416ULL, 0x5079975DDB0F0793ULL, 
            0x1A7A1AB12F5A1280ULL, 0xEE9E8D566B34B5EDULL, 0x50ADAF630CBDC4BCULL, 0x8E2321C07F781E03ULL, 
            0x17E3DC1833611A2EULL, 0x210D9AB0545F5F4AULL, 0xE1D9100FC154A119ULL, 0x2B74D62DA6E5194DULL, 
            0xAF9D60DF6EC706CDULL, 0xB2747F2801E2A0FEULL, 0x99B2CD50FA2C1FAAULL, 0x4C99C5FFAC9E8496ULL, 
            0x20B7DDA6E25D8932ULL, 0x1419181C1C701C48ULL, 0x0B6EB11F32AFC78EULL, 0x46111254CE099E92ULL, 
            0x2C29F53C9B46B587ULL, 0x8E4352B322760B81ULL, 0x9332F214A6973FECULL, 0xF452E0D4C274D2C9ULL, 
            0xA002B760736301D5ULL, 0x5D71AC3BA42D835FULL, 0x3C14A5FBCB1A7689ULL, 0xF2DCAD40FC85A87AULL
        },
        {
            0x6489FB729185575FULL, 0x4E802A85ADA9CE7DULL, 0x4711F64650A77DB9ULL, 0x9DC5DB22BF2EC416ULL, 
            0x310166A9A269DEFAULL, 0xC6742D1D14628FB8ULL, 0x0862BA0B37A32769ULL, 0x5433B02FB183299CULL, 
            0x84BB3F50F43FE9FCULL, 0xB7219DF084BDB659ULL, 0x9A48B35A91A1C0AEULL, 0x8A0D944BCCD8102FULL, 
            0x619370BBD10B4C48ULL, 0x83E2CC85F1ED1A73ULL, 0x28AD3E6E42DB42EBULL, 0xAF3A8AE7B4301E24ULL, 
            0x5DD23D79D3CD486AULL, 0x2AF208CCB0B61CBAULL, 0x2483611673CE47DCULL, 0x6C8FD9BF18724E95ULL, 
            0x0689A76D55E07EECULL, 0x47463BEE67343B31ULL, 0xC1174D47E27844D7ULL, 0x8115B1F6E8AB15A8ULL, 
            0xC0550F180B452F3AULL, 0x91B1266FFFE89242ULL, 0xC16F1227E41FF844ULL, 0xD0E61345F28BEF79ULL, 
            0x465226E9D733CC4DULL, 0x0A2F86D81CF7AEBCULL, 0xF34FEAF932B47491ULL, 0xBE8B1C549363693AULL
        },
        {
            0x6782DDC7C5D6DAE0ULL, 0xB7B0EBFEA378D2B7ULL, 0x0EDED9F8380B1E46ULL, 0xAC70CE83D32F5CBDULL, 
            0x07F8235FEA07379DULL, 0x78235876A5173741ULL, 0xA524BF106A8AAFF7ULL, 0x1FF2D249E41C1DDAULL, 
            0xE676E04FAE639F11ULL, 0xCF5040C2157BC466ULL, 0x583A9125C2488784ULL, 0x6472F29D335F2680ULL, 
            0xF29309D9094FE13AULL, 0x612B17605CBC2781ULL, 0x5C14D20D0EE94DECULL, 0x4ADBEE1513010F52ULL, 
            0xEDD794107E3179ECULL, 0x54FA6014A021F5B9ULL, 0x411797EC9BB8B645ULL, 0x7D572820E773324EULL, 
            0x3DEEFA6B4F61BAFCULL, 0x9C35C1556CBCC60CULL, 0xAD048123CCDCFD4EULL, 0x1CAC822DA42CF0FCULL, 
            0x5A2CAB3949485AE0ULL, 0xFC20D95CB70B4705ULL, 0x768B8FF72CA4DA26ULL, 0xCEB16CEEF0F8E655ULL, 
            0xCE5AE97D2D8B31ACULL, 0x05251D9D31DA5CB5ULL, 0x102B25E9EF776CFCULL, 0x3CD9EC27ACDC86DDULL
        }
    },
    {
        {
            0xFA50F21881C3DFDCULL, 0x513230C4669D32E1ULL, 0xECB01778E43C4B01ULL, 0x2565E2535C9E14FCULL, 
            0xF91E217E56192008ULL, 0xE0B2589A29DDED48ULL, 0x489CD0CC8AE45812ULL, 0x7DEB8BAD30EDC8ADULL, 
            0xB45CCB3F296D8571ULL, 0x47BD2AF94916FF27ULL, 0x22E973152ABA5816ULL, 0x18D235D32ACAF9F0ULL, 
            0xEB5193CBE34D1F18ULL, 0x13005EBE4C4C05E1ULL, 0x8A78A5FA5431FFCFULL, 0x06D2007308FE15D9ULL, 
            0xECB9A1D734A49EB2ULL, 0xE1552F08C34558BFULL, 0x1981812551905966ULL, 0x07C50189938712EDULL, 
            0xF71249D38FED9D33ULL, 0xF755CE1EFFB448E3ULL, 0x63690F7BF00B6185ULL, 0x83A4E18EA27F0D6AULL, 
            0x5E30DC3DD0092984ULL, 0x0E002B0FC7C1F510ULL, 0x96E2B60B81B1756EULL, 0x820C26A95AAA2262ULL, 
            0x6694B52E7220175CULL, 0x459EEF219CA76FAFULL, 0x7AB4F8C3AD92C649ULL, 0x02A574545B65CBA6ULL
        },
        {
            0x9903C822D5FC07A9ULL, 0x16EA543B68A51836ULL, 0x779CADDFA08B08A8ULL, 0x3FD904ECCD65211DULL, 
            0xF3A0F85BA7FC41B5ULL, 0xAD05EF73ACE6D461ULL, 0x79E0B9BFA388D41FULL, 0x3AEE8F5D0DADA909ULL, 
            0x39C1418B087CC643ULL, 0x68474BC39B360647ULL, 0x94F511056008C414ULL, 0x8A59DCDA4F2F3FDDULL, 
            0x1317B7917E872ED2ULL, 0x2CA5FCDC7A3E6839ULL, 0xD6C70A3C87984F9AULL, 0xF4E499C44F17C369ULL, 
            0xA8567A609050AE26ULL, 0xEB84B0E9C4247022ULL, 0x95DEB2BF33C0ED50ULL, 0xE2AD05D12FF51C44ULL, 
            0x2EDD471A4F4617D0ULL, 0x5C7556B59A9B536AULL, 0x6E55B78A83FA8162ULL, 0x6818E3FDECE528A7ULL, 
            0xA2A843F804C85C8CULL, 0x08D036E1AA9FC179ULL, 0x3285A0A8EA050F20ULL, 0xF59693609143DD14ULL, 
            0x95AEC801D44C1BBDULL, 0x5F2A9754A5185AD1ULL, 0x714643E9BD66EEBAULL, 0x5229B5B447CF092AULL
        },
        {
            0xF7EDCDE5AAC5969CULL, 0x3D367631A3CB64C9ULL, 0x07EF86A3230F1D6DULL, 0x1FEEFE2612FB0B8FULL, 
            0xE8B868CE2D4B00DEULL, 0x5E99B9C37F15D4F8ULL, 0xB1B45F5EEAE8B6BCULL, 0xB41A2A8DE7104119ULL, 
            0xB14790B8CB0ACB0DULL, 0x82BB0E2D19C0B45BULL, 0x234E0262DBE53FCFULL, 0x318176A4E037DF10ULL, 
            0x46816BFC4477B401ULL, 0x259F0DCD52706C3BULL, 0xD8C363D40FA0FF24ULL, 0xBBFF06773686B7F7ULL, 
            0x6E7EF8344BECCB88ULL, 0xBE568C0265537587ULL, 0xBB1095473CCA083DULL, 0x2282E68163A82830ULL, 
            0x73381E0758364EECULL, 0x82A164B8EAFA50BDULL, 0x8B094EFE6D541F3CULL, 0x835B60460910E1B5ULL, 
            0x339D49587ADFFAD1ULL, 0x9C0F919B8D99E67CULL, 0xDBC5849B49C0C2DAULL, 0x9A156C5D1019F851ULL, 
            0x2D1387D7DA3833E7ULL, 0xA35EA735EA729D34ULL, 0xFF54360337FAB8A3ULL, 0x7A54F670E1CC79CFULL
        },
        {
            0xB0D2B38EDBFC7FF3ULL, 0x113685EF62B1528CULL, 0x865905684E00E46BULL, 0x4691D7A3E0F11436ULL, 
            0xB6BDEC7C8DB329C9ULL, 0x4CBA0347AC6C825FULL, 0xC9627F9BDFF31E09ULL, 0x79EBED8CF35A257FULL, 
            0xF6F4271D77DF521AULL, 0x4A5BB9E663B29066ULL, 0xC201E9FDD8144F9EULL, 0x882A31B7A4FDE58FULL, 
            0x4803E8B68553F712ULL, 0x6AD3C650246EF4EFULL, 0x35007CF79FA3060FULL, 0xFB980C4866007154ULL, 
            0x3EA8D72353D425C8ULL, 0x0BF07AF3C5CCE5E8ULL, 0x26BD232E1936BA71ULL, 0xC4D8DCBF71EEE1F3ULL, 
            0x24E90D5FE70DDDFDULL, 0x505D4A3B5FD23A79ULL, 0xC1ACACEB90CEECABULL, 0xFC36DEC8F4F07AF8ULL, 
            0x9A4F2E1A1E2745E4ULL, 0xDC51F536AD4C2DB3ULL, 0x1D579FB681022F5AULL, 0x08F78159DDC98BDDULL, 
            0xA7900CACDBCF74C4ULL, 0x76401B91FA6743DEULL, 0xEE3A9C3179B7763DULL, 0xE413B0D58B98E5EBULL
        },
        {
            0xF3A7574FCFCB5BB0ULL, 0x92D94949D62B1898ULL, 0x411D18CEEE9CE042ULL, 0xE5965041DA2D1469ULL, 
            0x33C6BB8899C959BEULL, 0x398B86E043853428ULL, 0x2001BB1E9C4A9DEFULL, 0x05D5CABDD33EBF47ULL, 
            0x3B37C37301BDECF1ULL, 0x20B67295530BA145ULL, 0x439C46E228332332ULL, 0xF01F63F0BC00BB9BULL, 
            0xBE2DE66A81390111ULL, 0xC0ED813636AF8419ULL, 0x521DCD353BDB0159ULL, 0x49E9327A68BA7637ULL, 
            0x128ED2F749D7B707ULL, 0xC635A65BEC7C5082ULL, 0x9E6F594745B16B2EULL, 0x0C4B1A54CC6F8594ULL, 
            0x83D9BF59EF67ED70ULL, 0x5420D37024FCF9ECULL, 0xAB7482B53D9AF201ULL, 0x863D56BD9C435B7CULL, 
            0x679872466073EC8FULL, 0xED2FA1E2AFE5CB93ULL, 0xD601DAE87AD77576ULL, 0xB4A7DD438F847898ULL, 
            0x96D24CC9CA78D6EDULL, 0x6B7C737F6F0DA351ULL, 0xBA7276AE93D89090ULL, 0x12201E76DB528F76ULL
        },
        {
            0xDEE91231C470035FULL, 0x27741C35CBA5360DULL, 0xA11A1B02C67D55C7ULL, 0x016B70F88A0792DAULL, 
            0xAAFF7EC121D8EED9ULL, 0x76B7567AF4C87E4EULL, 0x1F7836636D6DFD46ULL, 0xA3CD8E9655EE7929ULL, 
            0x93343831B2BFE2A4ULL, 0x658D53FE6B850A47ULL, 0x08971E91F01A282EULL, 0x8A7431DB9351AADFULL, 
            0xCE9A947B58498AEAULL, 0x0F052870428985EBULL, 0x908DBD71A00E86F7ULL, 0x15002D67950F7175ULL, 
            0xAA8AC7D98F7C9F51ULL, 0x2734AF66838A47ABULL, 0xDF4CF11B47FAC784ULL, 0xA26EBD6C0E117D77ULL, 
            0x43F0C66A902CE4C5ULL, 0xF73ED923161AA7BFULL, 0x63152EFE3C4A07E8ULL, 0x3CA5F82F65433008ULL, 
            0x6841212E2870DFD6ULL, 0x4B0ADA943D745775ULL, 0x8BAF6E92579703FDULL, 0x08CDF86684C285D3ULL, 
            0x711D6EF751CA1BA3ULL, 0xA6AF1F314615FAECULL, 0x341136FC08D59A81ULL, 0x957E84CE71E998DBULL
        }
    },
    {
        {
            0x1363BAD97002CB0FULL, 0x44D56EA73DA911DCULL, 0x3F3E61E429FB8109ULL, 0xE1F5E9885098A4C0ULL, 
            0xDEA90AD2F9893BF4ULL, 0xF59B5BD4BC5EADC9ULL, 0xD47BB96046564ACDULL, 0x434A8FB907C348BFULL, 
            0x87F0CA4244BBC79EULL, 0x8D927686E0CB85E7ULL, 0x9C01BC0850E9889FULL, 0xDD8422D8DE54CC3FULL, 
            0x5458785D7E7F9C32ULL, 0x46F1A389BAA718D1ULL, 0xB5EA5EABB03334DBULL, 0x8A597C98C3992463ULL, 
            0xFC228EBEB04F0D82ULL, 0xAE55B874EEB5E73EULL, 0xD96DDB608EECEC9BULL, 0x0BD9464B1FFFAECAULL, 
            0x865C91E61D953BA9ULL, 0xAB51B4EBCF66E4DAULL, 0xD5BCF7A6367BF284ULL, 0xF09CBA95D8E5CCD1ULL, 
            0xFE91E022A1EC0B6BULL, 0xD29C9BAFCA600BACULL, 0xCDCDDB432C551E73ULL, 0xABC65C38275FAC9BULL, 
            0x7A7CE45B03378BFFULL, 0x848836625D134DC9ULL, 0xA15E6B64B6D48264ULL, 0x34F28F31594BACE1ULL
        },
        {
            0x6880FC2A8CC5915DULL, 0x6D488F5A9B0F1850ULL, 0x038B15616E16BA31ULL, 0xC42369DB2BACC667ULL, 
            0x881572CC0CE7A9BFULL, 0x5C2536298ADBE223ULL, 0x84D2352E6A8D6AD7ULL, 0xB4880AA492846E34ULL, 
            0x87CE34A32FD8315FULL, 0xE1CD9AD68B5EFF19ULL, 0x558A676818EFDCCFULL, 0x5162D4A17EFFEFDDULL, 
            0x919C99CA8C421E91ULL, 0x9BA4D81A300FC459ULL, 0xD340AA85F39839ADULL, 0xAE49BC9A7A1B7FE2ULL, 
            0x3DA920A4F387E96EULL, 0x4008D3ADBFAF3012ULL, 0x61F5CDB724B428DFULL, 0xE2F34C1DE506EA85ULL, 
            0x349E903093B165A2ULL, 0x8B0563C828ADD079ULL, 0xFE2B1AAA91AF64DEULL, 0xBD48E9B97DE17C6AULL, 
            0x8290E72DC15F2A6CULL, 0xB99DC8C341DEAD18ULL, 0xD2D3E1870CFB5591ULL, 0x5D5A36A2823B2D63ULL, 
            0x6F04AEC5D76DB350ULL, 0x5C4DDA2EA5024165ULL, 0x0369F63DE5AAF327ULL, 0x10B79EC444A3EE3FULL
        },
        {
            0xD3F76840DE5B6D46ULL, 0x56DE18BEA585DF13ULL, 0x9E9959DC166695DAULL, 0x8A6B76405EC8297AULL, 
            0x5290ABEE112AE607ULL, 0x892A8F965989F88CULL, 0x12E462B43FC3CA2CULL, 0xE40C06CD60257B12ULL, 
            0x0A0528C2CE1DAFA8ULL, 0xD1549D542D466519ULL, 0x376A54503F272825ULL, 0x964F2544F60C4979ULL, 
            0x4874FDAD96815B14ULL, 0xE9874D5D10C4C2FDULL, 0x9531FC3794529E47ULL, 0x86028036394D9241ULL, 
            0x65E47A6A3C944C8EULL, 0x451716B08580B11AULL, 0xD80A852DD90A4BD2ULL, 0x1A6BF2793CA49440ULL, 
            0x34C475910289FBDDULL, 0xB526D04FCD8B3E57ULL, 0x16BE5AAEB4F8B2A2ULL, 0x963BF75433638BFDULL, 
            0xA8827783CB2A20DCULL, 0x8FF57AAD9421AEFCULL, 0x839E15992B3A68BEULL, 0xD469AA45C6FC0DD9ULL, 
            0xE69E06A805AA69F1ULL, 0xABFBE843E7868136ULL, 0x12F67F93AE8615C5ULL, 0x1B485D2F23452563ULL
        },
        {
            0x71685EA4A3B68B33ULL, 0x2E79E968142A49F8ULL, 0x2A5AFE217F4EB393ULL, 0xE96098C315DEADF2ULL, 
            0x48C34C26CC1208DDULL, 0x6E01DF5E117742FCULL, 0x6B0125207844B883ULL, 0xF9247E0FB5BE1A97ULL, 
            0xF5CCF661CB6DE232ULL, 0xAFCDD1E975520D24ULL, 0xBD2F08AEE26AD0C2ULL, 0x4AB5CB2DA183D7F4ULL, 
            0xE5BEC4A993383911ULL, 0xBE4400443D2AA716ULL, 0x7B7821A900FEC26EULL, 0xF69F7AD32CD6D4D7ULL, 
            0x6FF079ACFF5C50E5ULL, 0x13CE1BBDA6F62399ULL, 0x6990D528D531EA1CULL, 0x109A80339CFCA392ULL, 
            0x400A5937BE0FA0BAULL, 0x48E4C0EB18E3B7FCULL, 0xFDE7BB0CE21A0D1FULL, 0x21076036F931ED67ULL, 
            0x23895AE431A2E785ULL, 0xF6DB6BCA42515996ULL, 0x5E63871EB2427029ULL, 0xF3AA6A3B7AD60D32ULL, 
            0x0E307B2311A8A420ULL, 0x3AD41F64664A0854ULL, 0x0B6CECAD9B572FE8ULL, 0x2045A41A65A2900CULL
        },
        {
            0xF8E7C126B27BB9BBULL, 0x03769322F463ED56ULL, 0x787EA0EDB67547EFULL, 0xCDC467E61AC4935CULL, 
            0x0A873EF6FB84F8E2ULL, 0x3905B74D2A18348CULL, 0x97C20F8FA40AB294ULL, 0x5A197C61D1DAFC79ULL, 
            0xA2719C2559B7C410ULL, 0xBB9F056CC5FA254FULL, 0xB6BEB253E094C9ACULL, 0xCFC1DAFD8C4F5157ULL, 
            0xFDB93D7585A356FAULL, 0x8FEA43DBA1030490ULL, 0xEC6CAC71BD510580ULL, 0x29A14970842EAF56ULL, 
            0x72002588BB322CEAULL, 0xE83F370147185CC9ULL, 0x655CB4ED8452C319ULL, 0x2B767B3759DE8257ULL, 
            0xC983028A9711C8D5ULL, 0x0B10E54088306896ULL, 0x4C2EB7D5D18458D9ULL, 0x5EA204D2A95ABB91ULL, 
            0xA6D6CECA2F5C6C73ULL, 0x0F24AD91D132EEA2ULL, 0xF0CB4CC82CB26A2AULL, 0x85CF7FE4C6B0AB30ULL, 
            0x3C2C6FB3F8BFAEC9ULL, 0x8DCE8A66A67DBAA7ULL, 0x496C893914E65987ULL, 0xE9B144E13FBDA439ULL
        },
        {
            0xBC2F54F24F9F802DULL, 0x7915CCB7F9A33641ULL, 0xF66F672C58C1D7FEULL, 0x71343BA36DF47878ULL, 
            0x8C5034B64DD72416ULL, 0x0675325C0EB181F0ULL, 0x83D84D6FDB79742AULL, 0xF569C2CB0C5D84B8ULL, 
            0xA890A9B2E59281E9ULL, 0x0A63FE79BCFF537DULL, 0x4796563866E9F8D8ULL, 0x046AD4CC64056698ULL, 
            0x308D14296A50DE89ULL, 0x1445BACD25396126ULL, 0xAED4A1D31E7C46CDULL, 0x379A3C4C198F7E6FULL, 
            0xA7D84866C420140FULL, 0xC32BF9F0ECDC4515ULL, 0xD6CA8F7B68A100A7ULL, 0x45336E9F9C669521ULL, 
            0xFED3377B10E80FDDULL, 0x2668DFD8E79DA494ULL, 0xC1CC17FA5CA8EA07ULL, 0xE749A9E65E805E88ULL, 
            0x762FC7E28F9A6D46ULL, 0xE33BB6AD2DF87D01ULL, 0x5E263948E8CA195EULL, 0xFABF015F07DF00F4ULL, 
            0xC03199B5F973E21BULL, 0xC245393D07A9964BULL, 0xD8C435D476062229ULL, 0xB070443F71D8D4B5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseAConstants = {
    0xE006FE0BD1D77C4AULL,
    0xBB892C12A61E5AB1ULL,
    0x1D61A76CE445F9B0ULL,
    0xE006FE0BD1D77C4AULL,
    0xBB892C12A61E5AB1ULL,
    0x1D61A76CE445F9B0ULL,
    0x3171021C4570995DULL,
    0x792965350B80ED80ULL,
    0x6D,
    0x73,
    0xFA,
    0xA1,
    0x60,
    0x85,
    0x70,
    0xD3
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseBSalts = {
    {
        {
            0xE8A8630E16C32F8AULL, 0x59877EC6439D1E79ULL, 0x739D24E181F92489ULL, 0x5090905CB4FE0A63ULL, 
            0x0F8FB3648DDC7DDEULL, 0x4DBA10E7A371AD81ULL, 0xF1F333A729E807D1ULL, 0xECE40A29ADC254F2ULL, 
            0xF06D5A79814B349EULL, 0x642397911C742DC0ULL, 0x8B58245C1755F1E2ULL, 0x8E141E29F98B1A5FULL, 
            0x6E6F8F9401B7E9ECULL, 0x7437D552876E61EDULL, 0xE5E32B511A12782FULL, 0x1552A63FD4A47F9EULL, 
            0x059574762F1FED85ULL, 0xA53DF0EF7E248C70ULL, 0x302A3F3E2361F536ULL, 0x9D79466BB047246DULL, 
            0x16A8D2EBE82607F0ULL, 0xB1B8989D403A37E9ULL, 0x51DDDDB9DC7BF629ULL, 0x076805F034BD1786ULL, 
            0x0B846E5F638BD99CULL, 0x985A22D17C4FD96EULL, 0xB42DBA2BE5F80C49ULL, 0x8C0E505DFD180C0CULL, 
            0x92051CE6E72C5842ULL, 0x735C268438ACF0F5ULL, 0x1B6699B11F69F1C0ULL, 0xB78C7D5150B46D2BULL
        },
        {
            0x2747B166296C8E7DULL, 0xB0FC4536035C90AFULL, 0x9F85E8092C22FFCFULL, 0x063BB75E1D7C00A0ULL, 
            0xCB0F12B8A51F2E83ULL, 0xE06DAD9522F1D1BFULL, 0xBDA87FC8F108A622ULL, 0x7BE7E3B46C005445ULL, 
            0x1B3C463BFA02EA2BULL, 0xFE92B3831610F449ULL, 0xC618BF4F1E1B4F89ULL, 0x6E8E0DEBB2926947ULL, 
            0x26D65CB7DB2F5BE3ULL, 0x5473CBA35E4DF6A4ULL, 0xE98AAB7F0F2F6E3DULL, 0xAB669310DBA3597CULL, 
            0xC3637DA33ACE7875ULL, 0xB6AD4831147712A6ULL, 0xAC8164E1EFE6D6DBULL, 0xA1EC770006704C20ULL, 
            0xEA87BB2EB2417768ULL, 0x7DB5EFF1BF118145ULL, 0x297E2235AA14BB1CULL, 0x9BC567915DCAE0CEULL, 
            0x58078A767E0B57A1ULL, 0x30EF369C249C27F7ULL, 0x2E418AA686307CC8ULL, 0x4C5FA3E8E27CFF06ULL, 
            0x394E5E78AB917677ULL, 0x53B259164E44C97BULL, 0xC45C9180FFD65E8BULL, 0xBFDE0CB9D93EE196ULL
        },
        {
            0xB5D09D17D6CC1FBDULL, 0xA054CC0348DF7E79ULL, 0xB1361798241C13FAULL, 0xDE32AE23F210164EULL, 
            0x7FC4013656C01913ULL, 0xCF2D864AE1073660ULL, 0x8C0460E00683AB7EULL, 0xE18B579E4965E602ULL, 
            0x2D8005D4ED399C39ULL, 0x895204B2A059980BULL, 0xD890C11E5E052658ULL, 0x45ECF1EB6AA84175ULL, 
            0x8582336F413ABFDDULL, 0xDCCD51B83EDB7EB5ULL, 0x4AE4123CCA92422AULL, 0xAE09A321E9BFF59FULL, 
            0xCCD6E0C42B9C66B3ULL, 0x50C1F3A35A55609DULL, 0x87BE5837234CB76CULL, 0xE995BA3B36F9F051ULL, 
            0xDBCF03F55F33A2E7ULL, 0x5C351FB9C0138EE6ULL, 0x3F37E618B91BE631ULL, 0xB3641AE6A9A6191FULL, 
            0xF49A989B8D86DCA9ULL, 0x8619333C30D8DA60ULL, 0x3D116114809FFE0CULL, 0x23262BB7A3752EF4ULL, 
            0x765343DECBA80084ULL, 0xD10A326CD565468DULL, 0xC5A0D58E7FC5EF47ULL, 0xF189D76A5A001175ULL
        },
        {
            0x8D13BEF123C963CAULL, 0x1467370B0865A233ULL, 0x1EDDA88B6F5CA123ULL, 0xD62EA98AA6CEC282ULL, 
            0xC10BCDA8077D0C1CULL, 0x575056AF655E76FBULL, 0x02EEB04441F3FBBFULL, 0xD03E87CBDC78FF42ULL, 
            0xB984846F1ACA0FF9ULL, 0xB358D83999BA25E8ULL, 0x66BF847E72617BB3ULL, 0x3917926C4547DCFAULL, 
            0x53091E1395EB960AULL, 0x6FB999A388240CEBULL, 0x95336434B8DA17AAULL, 0xE8187ECA1DA8312EULL, 
            0x5BF25A8ACC31828FULL, 0xEDC3537972E2AEFDULL, 0x5C48D9A209B5E3A0ULL, 0x4BC879635E40457BULL, 
            0xE1BD03975C9CBBDFULL, 0xE9D33340D6B5D152ULL, 0x50F5A3B33A1C77EAULL, 0xDD9485EBF25CCDCDULL, 
            0xA9AE44B739D95D16ULL, 0x43014BCB65530127ULL, 0xC219016D6B000BC6ULL, 0xD30574D7C7A15CD6ULL, 
            0x372751669E2D4797ULL, 0xDB9E9D21C5CD9B1FULL, 0x8328FFB0A0D1FFF7ULL, 0x0956BEF8B2F7C134ULL
        },
        {
            0x3850BE4C33FCC057ULL, 0x268FF787AB992C48ULL, 0x70459ADC5BBAC591ULL, 0xA519C8EB6E73C603ULL, 
            0x4099CC311710AD75ULL, 0x8575E532AE999742ULL, 0x7C9D82AD6AA8A020ULL, 0xC076EBFA667D4809ULL, 
            0x2C2771C56B7584D6ULL, 0xAF51E88667017473ULL, 0xEEBA14CCE5BD821EULL, 0x1FDBB9336FC9D44FULL, 
            0x1E5E8FAC53ADD4B7ULL, 0xEC10B67690A0FD0AULL, 0x62F088C44DE5B465ULL, 0x07B1614C7617749CULL, 
            0x4F30A25CC2192C8DULL, 0x159E41DEF75CE11EULL, 0x19028BB5897AF77EULL, 0x602ACFC952ADAEC2ULL, 
            0xE052879EB1D35B55ULL, 0xD3C2468C6FFEA82BULL, 0xC61116D4BA08D2E4ULL, 0xB85EBE99D2DA1731ULL, 
            0xB31D81012EB54AA3ULL, 0xF384AEC867B50907ULL, 0xF5E79AAAD8556702ULL, 0xC88301E856BC2F3CULL, 
            0xFA4AA8DD7C0D4A4BULL, 0x9E54AE99B1B85DC7ULL, 0xE0DA428D3AC0FEC5ULL, 0x7E8956DEBB29F75FULL
        },
        {
            0xFDDC63F476536257ULL, 0xDA6CA86536603938ULL, 0x4DE21072907CD1F3ULL, 0x0342B168E79BBFF4ULL, 
            0x5329934A6DED4073ULL, 0x2F4AA55ACF3AD821ULL, 0x807A6F35A8F12863ULL, 0x2E3E1039BA0692D5ULL, 
            0x7F47F5A31CFE284FULL, 0x48184D82B6E7D9FDULL, 0xF0E3CBF73C4E7AEFULL, 0xCC9237A16820486BULL, 
            0xA5A792DA91000E9EULL, 0xC01129760533F516ULL, 0x53FE196AC9AADE63ULL, 0xC75B1BF127F29E14ULL, 
            0xC72E1FA00312BF93ULL, 0xF1EE7659D86ECC3FULL, 0x5A529D1B2978F1A4ULL, 0xB73BFE51C426C3D7ULL, 
            0xD9D294C28EEA7BA7ULL, 0xC7B5514D256D011FULL, 0x9CBA769EDF3D0B90ULL, 0x93E9881CFF33C219ULL, 
            0x0D83AB86A3333082ULL, 0x4C9C3414BF1057F8ULL, 0x5C63AEE656FD5707ULL, 0x2859EB1A0519F117ULL, 
            0x58BDD29DF06A76DDULL, 0x175F07990D31B2FDULL, 0x648C0036CF77DD27ULL, 0xE407DEABB7BBC3EAULL
        }
    },
    {
        {
            0x589737F5BD34A6E6ULL, 0x5BB15EFF0471B12AULL, 0xD2F085D34C17D4C3ULL, 0x5EBF1265AD384FBAULL, 
            0xF9E18AD64E11F90BULL, 0x881F3AD535BB5364ULL, 0x530B468B2BAABDA5ULL, 0x3A828F1CDE10ED0DULL, 
            0xB8C5081C65F0173CULL, 0x8BD4E645CC7C12E2ULL, 0x69AF2E427E5E23D2ULL, 0xE7790D47151EF40DULL, 
            0x77BD0D8442AADDD2ULL, 0x73A7E11DC5825940ULL, 0x464A3C8D279996F5ULL, 0xF8AB5499D07626EFULL, 
            0x545397448C2E8D63ULL, 0x70EC2CEE40B4AE8EULL, 0xE030157C456F1916ULL, 0xBB295569C3BA244BULL, 
            0x0C5E3AE1CA2DB850ULL, 0xBCB1BB1AEEBDFE80ULL, 0xFBCFF9F9C1041818ULL, 0xD75A850A5F50F88DULL, 
            0x129482F430910DF1ULL, 0xEF8C760944A51246ULL, 0x8B03F94B735B3469ULL, 0xFF4A5C44E5EA0854ULL, 
            0x333E1990766387D4ULL, 0x0DC33A0B9CD11F77ULL, 0xAA995D9297E00EF5ULL, 0xDF562ED487B80081ULL
        },
        {
            0xE2D9EA907113555CULL, 0x9DD104F6DE838F99ULL, 0x39AD1CA1A6EBA02BULL, 0x62D718E02574725BULL, 
            0xAAF48F884A1D4345ULL, 0x7E1A2F3468C2D39EULL, 0x23558CB2C2085CF6ULL, 0x2045E4E9AEF97848ULL, 
            0x7C7F21676309BF20ULL, 0x263C1E7519FF7B6AULL, 0xA84D1048F4E277ADULL, 0xA308B63D68F7CB3BULL, 
            0x41C63EDBA480D9ACULL, 0xF326EC1A5972324AULL, 0xDC29559D9175EB14ULL, 0x4B2001069E8DC393ULL, 
            0x080855AF511768EFULL, 0xBBFCCD6663ADE9E2ULL, 0x4EA64FB695153789ULL, 0x1879057447A929F7ULL, 
            0xAF5F9D6A2B3B715AULL, 0xDAE4A928DF94753DULL, 0xE4B8D108D92521B7ULL, 0x22A4EFB4F7263A9BULL, 
            0x96F775E8A528FA2FULL, 0x892A28DDAC688612ULL, 0x95D2515DA703ACADULL, 0xDD3A84113E355E8DULL, 
            0xC034C2559C0AADAEULL, 0x384410BFF7CC7F51ULL, 0x1E11AA1632238D64ULL, 0xB93731F2B4266873ULL
        },
        {
            0xA94335601B164FC3ULL, 0x8698B071E16E71C5ULL, 0x698CE6A7A18A4010ULL, 0x203211E5F27A66F4ULL, 
            0xB477304EAFB5502DULL, 0x510003F64A9DF5DFULL, 0x11B846CE46C9FA0FULL, 0x332C9991545AA593ULL, 
            0xB262DD189C1E53E2ULL, 0xDCFE96D16B1E00BEULL, 0xB4B821CA4B4B9A11ULL, 0xBFB74E52B4369B61ULL, 
            0xC68992BF3D776A0EULL, 0xB71883AF035F52A7ULL, 0xB5640F9833020F64ULL, 0x177E70D9473CE7F3ULL, 
            0x721012B745F1BCB0ULL, 0x7046EACE14D9A04FULL, 0xA7463D0C0C5815D3ULL, 0xF10FEA844BD0EBFEULL, 
            0x3BC242C40F34315AULL, 0xBD8B4AF3106E827FULL, 0x41BEE8CD9E5B111FULL, 0xDFD6C106CA0D0600ULL, 
            0xFE5E314EF6C95E20ULL, 0xC5A7C0DBEAC82440ULL, 0x09C207759D87A17AULL, 0xFEC14482A4BDA176ULL, 
            0xD78F2CAD531FDC6EULL, 0x823A3A69E34A2852ULL, 0xB258207B91D5BDA1ULL, 0xF46E3A77D4D64513ULL
        },
        {
            0x0A37BD90D40CF0E0ULL, 0xB9675A399FC46182ULL, 0x5A32C3C40062F23EULL, 0x68473F23D1C644F7ULL, 
            0xC7B6FAC328D2112FULL, 0x573A6C4C9ADB27B5ULL, 0x002BBDE8B713A9D0ULL, 0x5AAD7F7E2723E9DDULL, 
            0x35BE101FD71EE1C7ULL, 0x6FB283A338B5D7E2ULL, 0xA33DCF2DAF4388EEULL, 0xAA33A5872C55DDC4ULL, 
            0x5ECE5E4C85F27544ULL, 0x83FFE28EB130FA92ULL, 0x0575B1F48C0FE61FULL, 0xA1529D05650BDC61ULL, 
            0x994ED257C7832394ULL, 0x4BB306DC40C0CF5FULL, 0x02A965B09C0818A3ULL, 0x27DCF136CCD3F155ULL, 
            0xD20FCA247BD8DF74ULL, 0x045E6931097D4ED8ULL, 0xB2422ED9FF089032ULL, 0x85EF0E010B8297F2ULL, 
            0xB4507F663AE62945ULL, 0x878E23C082CEB883ULL, 0x44B237808434F447ULL, 0xF45D5901943C922EULL, 
            0x87B0CCA5201F1BDDULL, 0x29C772A8EFD04B9CULL, 0x7D51BDF955A6D2F6ULL, 0x48E155CBDCA0963CULL
        },
        {
            0xF2E45FEE4FE507C2ULL, 0x810473C8414E9628ULL, 0x8AE0B09BDA3093FAULL, 0x2D6A7D809DAF0C1FULL, 
            0x609BC1A0F92D4ACEULL, 0xB35BBB44968270EBULL, 0x5B3EA0067EF7D2B9ULL, 0x16721C639770793DULL, 
            0xDCA3D1BB231FDBE9ULL, 0xC677FA0E16442E57ULL, 0x963AEC3E1716DE40ULL, 0xE3EDFC912E1ECE92ULL, 
            0x952C18D189E0D306ULL, 0x84523642ECE8E699ULL, 0x77E0716E72AD9EFDULL, 0xBBAC709E24E1A972ULL, 
            0xD9393D18BA7F230FULL, 0xBF2872FECEBD9951ULL, 0x789E0D46D8F74605ULL, 0xCDEB6411A27501C8ULL, 
            0x718A5A8FCB95B7C4ULL, 0xFA59368C97935079ULL, 0xFA7137F47CD3FA68ULL, 0xDE6BF2977FEA9BADULL, 
            0x2B80CEE30B8A8709ULL, 0xB720965F603C0BB1ULL, 0x558BB4EEDBF15F77ULL, 0x7CE956D5D9084750ULL, 
            0xD1C51FCFB0CF440CULL, 0x4C6BBAEFA99AE2A3ULL, 0x878F94A91A50012BULL, 0x3B6B7AF26395B455ULL
        },
        {
            0x033DAA0A3839A99FULL, 0xE6641B92C641EACEULL, 0x4E59FC8D45A31DD3ULL, 0x2BE7DFEF714B2C9FULL, 
            0x8D6CB45AE9E7E6B2ULL, 0x8F276F00BAB69E32ULL, 0x6C03BD2CCCB944E2ULL, 0xAC6C15BB29859F8BULL, 
            0x7954DE42286B7ED3ULL, 0x192B49D8488B3067ULL, 0x7404D7E075D1035AULL, 0x3AB7ABAD4BC66704ULL, 
            0xB84FB9E9D072C30FULL, 0xB65AB97577678E9BULL, 0xA30220A02AC9186FULL, 0x25726C5796290B95ULL, 
            0x52B7EDAF65390BD1ULL, 0x9603734FCD632231ULL, 0xEEFC4F930D798466ULL, 0x453454B31615FC36ULL, 
            0x4FE4168180E92F06ULL, 0xC26ACCA4A624C4C1ULL, 0x14FC4BA8A1B37E48ULL, 0xC8CD53A09F046658ULL, 
            0xA7BB8FBE794B4D58ULL, 0x4B9C762CA5DF321FULL, 0x71B24EC86081061FULL, 0xC3767EE09D1CAC3EULL, 
            0x084F2196C3A4BEABULL, 0x4AB16914BDB5743EULL, 0xCE41921C0A4638CAULL, 0x04CE75439B8AC0E5ULL
        }
    },
    {
        {
            0xF41ECA1322D61DA5ULL, 0xB9DA9B3E42B2D6FBULL, 0x9E6010B02C611519ULL, 0x320736BCF4CE26C3ULL, 
            0x13491D3CCBCDFA84ULL, 0xE37DB7FDAEE1DDF8ULL, 0xAE1894CE5A0D30B7ULL, 0x5A7861BC27F0376EULL, 
            0xB24F039E0E914439ULL, 0x7D885DFA3B472062ULL, 0x869EE8087D89A9ADULL, 0x1BC729EA6D1EB380ULL, 
            0xB803C21EFCE0409CULL, 0x5F58C676C1219208ULL, 0xD3FE02303CAED1A8ULL, 0x52966E5FA08C8888ULL, 
            0xB896959ED872692FULL, 0xA0C315C0A39F28D6ULL, 0x46B52C13FE2ECAFDULL, 0x07849E5E12FF471DULL, 
            0x56DA268A44E10CDEULL, 0x56C7DCF13AB8C8D1ULL, 0x67AED3A3C4FF9719ULL, 0x421FD3C2A3553B0BULL, 
            0x39ABDEC5C01218C8ULL, 0x15EDF43C8B4CA37EULL, 0x22F0EDF96A7D0171ULL, 0xC27703B70816D2C8ULL, 
            0xF650857D30899BACULL, 0xB21DA744B80AF4D3ULL, 0xEC770685D9C2A2F1ULL, 0x8BA3A1AFFB6732C7ULL
        },
        {
            0x56EC5700D18D5C4BULL, 0x552B5C921FD02387ULL, 0x397708EC82ED94F5ULL, 0xB963BA8F0DC14079ULL, 
            0xB51A8C38926646C2ULL, 0x817A3AC747A1AAF5ULL, 0x7A3DDD9E598627F6ULL, 0x92AAB42CD2D84022ULL, 
            0x4692B4A04123507CULL, 0x715363E9183244BEULL, 0x7CE718B66B868638ULL, 0x2411F1F7FA8AB542ULL, 
            0x87F903B3867973F9ULL, 0x87C7E2F755877A93ULL, 0xF605597312EC8F0CULL, 0x1159D778125F7127ULL, 
            0x4E5AE805743B486AULL, 0x64CA1C92AAFD92E2ULL, 0x16D795A6221AAB3FULL, 0xC4AF646C0BEE1FDEULL, 
            0x57FCBF6436FE06C4ULL, 0xE4FDC968FD868762ULL, 0x6270D142A29ECBA0ULL, 0xB9F357215016861DULL, 
            0x0EF881E2A931C471ULL, 0x2DAC4CDF63254D40ULL, 0xF76F46D87B569C16ULL, 0x69E845E191A1BD02ULL, 
            0xE46AF133E5D1806DULL, 0xEF0C1315169E2360ULL, 0x9F42785CB4F26E9DULL, 0x9EDBF64F7CC20FE9ULL
        },
        {
            0x8114F6732FDD5096ULL, 0x43B31B29E3406E8EULL, 0x0D55247AE70936D4ULL, 0xF9CF8C0AAA03E947ULL, 
            0xE8E3A5476FFC6430ULL, 0x074FCADCA1F8BDABULL, 0x96A13D76A435016DULL, 0x42C895EB73B9BCD8ULL, 
            0xCBA8CA9B193B1450ULL, 0xCB8A5C48B648F9C7ULL, 0xE116A761C71D048BULL, 0xDE3D21C0276D65A0ULL, 
            0xCCEA28CAC754F2E6ULL, 0xA4D21BD9C65197ACULL, 0x20A905C12EBE0317ULL, 0x900943D3A440FE19ULL, 
            0x03A492AC40DB1888ULL, 0x6096A8A7DFF08347ULL, 0x3AEB40496D610DCDULL, 0xC42D8A18D47DE4D1ULL, 
            0xD366415B16695EFCULL, 0xB77F082CE30C8C75ULL, 0xED7DACD3B8AB9D1FULL, 0x5DDA690170E35159ULL, 
            0x6235D90843F07076ULL, 0x3090FB8F4C24040BULL, 0xA40103D7148AAEDFULL, 0x2C2F78004406D3DAULL, 
            0x828CC77894A3351AULL, 0x01C2A7BED532EDADULL, 0x9CACEF4F8EDCE4B5ULL, 0xEBA248CB25FA2F41ULL
        },
        {
            0x3B0D2B0E9FA990E5ULL, 0x8C74D6A58FA65C3FULL, 0x209E4F2C170B4220ULL, 0x508AF2476B3BE78BULL, 
            0xB85D542E6B77A2A1ULL, 0x803146DC0F36F39FULL, 0x3A5D1F5BE6150351ULL, 0xA51AC92A5ADC7BC5ULL, 
            0x24A624F4667F0016ULL, 0xCAFFB537B8894C61ULL, 0x51503261CE0DFFC0ULL, 0x8E3D78EC42CD2F09ULL, 
            0x04DD8B6FF4CCFA9EULL, 0x880C0B948EA5A9FEULL, 0xD565618D16AF5248ULL, 0x5020C28BABD42CDAULL, 
            0xAC10AA3B9CAAF4DBULL, 0xA26E066007D365E4ULL, 0x6102B65F0F970498ULL, 0x2885BEB4EA16D34AULL, 
            0x4853E445D25EA9B9ULL, 0x2417BF2C49C27F53ULL, 0x7F1F9AE7A92E8192ULL, 0xDFF990AA726266D9ULL, 
            0x6C66867B5C581F98ULL, 0x4431747F5606238FULL, 0x81C406013CF155F3ULL, 0x53913B7F0B6A2243ULL, 
            0x969D96C780F2A415ULL, 0x3B2B16310A2FAA4AULL, 0x06F8B0C3456A5F0CULL, 0x2AB97E3846FD7C1EULL
        },
        {
            0xD77F3E8A316E6E4EULL, 0xD5151B6A6A5ABA27ULL, 0xCA63D547D8FB4C6FULL, 0x2F466003DD2A71FAULL, 
            0x2440DBDC86E245F9ULL, 0x31A239E4660B54BFULL, 0xD360EC801EED7275ULL, 0x9F615B0240E95C44ULL, 
            0xCD7819A00EBBF1A7ULL, 0x017152D2B3B21873ULL, 0x4BD3618E33ACA020ULL, 0xE363A079EABE8954ULL, 
            0x01B21D8245D99F0FULL, 0x57942C90C2BA142CULL, 0xEF9F3223CA0ABDA5ULL, 0xB0871FEA73F77038ULL, 
            0x07863C0AF0339742ULL, 0x95027D85D1BBF7E4ULL, 0x07AD7D74671B1292ULL, 0x19E40F568E20044CULL, 
            0xA103399946A3245AULL, 0xAA7B458FC01E6C9CULL, 0x5A64A1C9081C4D1DULL, 0x1F1BEC5DD8AC4C2BULL, 
            0xCB30C319518D2724ULL, 0x1BC8D64A53405CCFULL, 0xE526B2EE4000ED18ULL, 0xDF5818F5E4368842ULL, 
            0x4CB0D73398500238ULL, 0xCA8A02660A01D534ULL, 0x89A18CA5E5B24DBEULL, 0xA844910B98F98D23ULL
        },
        {
            0x74ADDBF170C4D466ULL, 0x3F310A21D991A815ULL, 0xDEE43B037EEE6139ULL, 0x67EAC9B95A0B34F1ULL, 
            0x67378311DB27EBE4ULL, 0xFEE2AFFB9BD9759CULL, 0x9B399EEFAD714E46ULL, 0xAE5EED035F3855A7ULL, 
            0x5CF6A9696B63EE28ULL, 0x6C9DDEC286B216ACULL, 0x46E034CDD15CBA23ULL, 0x7BC06871211FF6F4ULL, 
            0x3203B10C32CBC4EAULL, 0x0AACFC61AB23FF12ULL, 0xAD68D59E9D44DC2BULL, 0x31DEDD3A1ADCCD9DULL, 
            0x13B0BE97A3ED0493ULL, 0xAFB266CC8A2F5C95ULL, 0x68988A1485E7CB7EULL, 0x3EFE73592C0B755EULL, 
            0x12BAAA54B9497CA9ULL, 0x50F3FBF897A913D2ULL, 0xB46AD21B76C837EFULL, 0x88D3265358D5A48AULL, 
            0xCA6AD803E495BD4EULL, 0xF40B8D17CC6124E7ULL, 0x1C511C5905556F55ULL, 0xFDED3087F85ADB87ULL, 
            0xDB3A9A6C522115C8ULL, 0x189E25CADA75B417ULL, 0x188812311531D216ULL, 0x3E0ABFD5EBFB4B6FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseBConstants = {
    0xE234987FB5F16CB2ULL,
    0xEB873E300A7D5E6FULL,
    0x179793431E973D40ULL,
    0xE234987FB5F16CB2ULL,
    0xEB873E300A7D5E6FULL,
    0x179793431E973D40ULL,
    0x08E5812ADC93407DULL,
    0x026520BEA225D690ULL,
    0xBE,
    0x82,
    0xFF,
    0x70,
    0x55,
    0xF6,
    0x84,
    0xB2
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseCSalts = {
    {
        {
            0x6BCD88CDF6B9C432ULL, 0xB53CEAF12288CF26ULL, 0xEE938E3D6EA3F02EULL, 0x382C6F18FBA2EF46ULL, 
            0xEF8DDD32940BD047ULL, 0x21F4EC9F86006AE0ULL, 0x7F9EF2032D3435EBULL, 0xA32B1227A234AA4BULL, 
            0xE15091B2905405E2ULL, 0x4209FBA8EEC07088ULL, 0xA49A36AF82BDC9C1ULL, 0x39C588F90A6EF748ULL, 
            0x75D6A76F36832F26ULL, 0xD6DB156CF37627ADULL, 0x1309883996EF61C8ULL, 0xF99F93F2A2A280CDULL, 
            0x595F18E917B6F90EULL, 0xFDAE5AFEF91087CFULL, 0xE2CCA23B9DC1D3A6ULL, 0xF6C337CFF9F0F963ULL, 
            0xD06CFB04899EB088ULL, 0xD99215F5854ACA00ULL, 0xD75E213D95D8BA43ULL, 0xC641865844AE4678ULL, 
            0x971DE9A1F7E9F5D1ULL, 0x079353B9F99B7BCAULL, 0xD57B84EBC0FCF0DDULL, 0x24FCDF78F5876D3EULL, 
            0xF7684F31C7EB1AECULL, 0x0CC18B76FDA46E88ULL, 0xBBFA9663D1EC9F2EULL, 0xBF1CD8E7CE722014ULL
        },
        {
            0xDC4213D4D50AE2B1ULL, 0x1004A2B4FD80868FULL, 0x853383AC225A9199ULL, 0xBBFEFED05B3CAB45ULL, 
            0x15F47CF6E00E88AAULL, 0xE62619D55B65AE3FULL, 0x04EC39313C288068ULL, 0xF6D9F6641C5446C2ULL, 
            0xF651FF8B8721B4A3ULL, 0x6B4BE2ED63AF5874ULL, 0x1010C0DE3B8F857EULL, 0xD4C525F925D54187ULL, 
            0xB617D99708B7F7A8ULL, 0x3A65E34626BC8CB5ULL, 0x0CBE2110BFE6C28BULL, 0x02E1B5A34A45A98BULL, 
            0x613221C390D3FF7AULL, 0x552DF6FBC4E190A4ULL, 0xEA649DB72C3577CEULL, 0x4DE268D3BDCB9D6EULL, 
            0x3668E96A3A615DF9ULL, 0x2B52AB48DC9094E5ULL, 0xD83E66A40703829BULL, 0xF60047C9414343C9ULL, 
            0xDD482701784E8DE0ULL, 0x7731E32A181DF7DBULL, 0xD739E983DB9648D5ULL, 0xA55003DC4BF763ECULL, 
            0xB7D8CBD589ED1D22ULL, 0x8F7B166B98CC403EULL, 0x6B4C422474DC6FCDULL, 0x2C6A97F8047BBFD0ULL
        },
        {
            0x09377CD2A11CEB4FULL, 0xD37555711D3550F3ULL, 0x46993F372FC42781ULL, 0xC0B92A8E5E59A4F6ULL, 
            0x5674F62E60C390E6ULL, 0x12BC50628EE6A9EAULL, 0x23FCACEFA1B504E7ULL, 0xF7D8340B5B89F526ULL, 
            0x32E174E5E3C8A61CULL, 0xEB9C373FBE9E076DULL, 0x03EA69072A3D228FULL, 0x9F816659F1AA9D1AULL, 
            0xC5115995659D225AULL, 0x1ABFF9A137791491ULL, 0x6A72D7465ED86060ULL, 0x93C48B5A3A0E1C6EULL, 
            0x6182D1D87D3C08F8ULL, 0x90FB69BD9A1047B5ULL, 0xD8BB811158315E63ULL, 0x2368B77889372D66ULL, 
            0x6AD6FE33CE02F8B8ULL, 0x2C9FE7878EC17EE2ULL, 0x991A690237E0197BULL, 0xA6E51762C497A4B6ULL, 
            0x9DC1137A1F208D1BULL, 0xB160B548B3599330ULL, 0x996FE07466A157CAULL, 0x9C15E6A438F3889DULL, 
            0x19AB18BE285C150CULL, 0x5C1595287730B958ULL, 0xDCF4AD86A54DB82FULL, 0x66CCC007A04CFA9DULL
        },
        {
            0xDBDFE57761F48C6BULL, 0x8466368BE9636605ULL, 0x79F72ED2FFA26540ULL, 0xEBB72A2936F2B6BBULL, 
            0x0545309F35C4F1ECULL, 0x6DCA99845D71904EULL, 0x98F8FAD4D4A47389ULL, 0x6B3578A4B6A9F940ULL, 
            0x5F678BBAF4FAD02AULL, 0x5F3E832481CB81F4ULL, 0x83E5DE7BC9AA7F52ULL, 0x6916B765845652ACULL, 
            0xBD7A6B78B2370D78ULL, 0x4CAAD47C4C11474EULL, 0x11EB12FB724CE55AULL, 0x76FF437D55CEAE67ULL, 
            0xEAAF57184F0A9587ULL, 0x78921381C0B777A6ULL, 0xE92727B270250AB5ULL, 0x5B22F1EA19B7FD4CULL, 
            0x5D39DFDB2AD5B4B8ULL, 0xF86507A270B51507ULL, 0x48457FF542501B07ULL, 0x51CDB79E3BB49C01ULL, 
            0x750DF01966D30302ULL, 0xC241970F560CE4BAULL, 0xA10F6D1A93BDF483ULL, 0x4433D184414FA4B9ULL, 
            0x52E253694D4D50A8ULL, 0x0D97D7C2BAC79F6FULL, 0xEC488BC45C567062ULL, 0x280468737A5E7E06ULL
        },
        {
            0x9B98CDB2545C1D52ULL, 0x8B2576C5A1894E82ULL, 0x91CBA4C2D86618E5ULL, 0x322E35F8BD90E77AULL, 
            0x2310E1605408E286ULL, 0x84A24346CD27D864ULL, 0x8AECDA152110AF14ULL, 0xBB74B9F7175F19BAULL, 
            0x7FAECFF46821EF31ULL, 0x68325438789D4C01ULL, 0xFEBDCED1B7B6DC43ULL, 0x8CB3A34DAA5DDA4AULL, 
            0xC26ACFA6600417DAULL, 0x45BA52533DF2D171ULL, 0xBB2A018DDC29139DULL, 0x83DE9B569A4173C3ULL, 
            0xADEB2FD87D41EB22ULL, 0x2CED3AC86352571CULL, 0xF33825A598E1AAF5ULL, 0x3D84139BC6A9EEA5ULL, 
            0xCACE6C391C025FD3ULL, 0x9DA2E17C7C376DD1ULL, 0xE29163084F51E94DULL, 0x0D4F4291494B1AADULL, 
            0x5F28B6631795BB75ULL, 0x50FDC4ECE6527CC4ULL, 0xA2C64FF258B18F91ULL, 0xF1F863CA02AFB257ULL, 
            0x27D8F75EDD35A320ULL, 0x8AC4C258E653AC32ULL, 0x6639F2076EB5CFC8ULL, 0xE9FBB0DC224AE814ULL
        },
        {
            0xA8BBEA4D86461C02ULL, 0x9B7A85532572110AULL, 0xE57BE599F015AD70ULL, 0x4A6D71D9B7068A8CULL, 
            0xDE204F3B5B161CDAULL, 0xE43A1EF36F18398AULL, 0xB30586D2F52A64FDULL, 0xED8697BDB75CF8B7ULL, 
            0x4739A9D944BEC10BULL, 0xD97FEE6D2DD1B692ULL, 0xA97A66B55DCE8CCFULL, 0x1D8F35ACC858EADBULL, 
            0x9C6D366B521C28CEULL, 0x7C54840B96771FE0ULL, 0x108763343E92A560ULL, 0x50221140F4E37176ULL, 
            0xD403C19A4BA05829ULL, 0x94077AC0FBB7038DULL, 0xE8D425B2C0141F84ULL, 0xA9C52E5466B11894ULL, 
            0x4E1D80C02F76A598ULL, 0xA9FA2B16B68A538FULL, 0xC7E8D50086953884ULL, 0x72AEA7C58DAC89A3ULL, 
            0x52CF3EF95EE794FFULL, 0x94D93ECE209CC4C6ULL, 0xB8988E3099833E3BULL, 0x13793FDBE8E89C9CULL, 
            0xA921C50A7B8EDAE3ULL, 0xD6C493C6AAE6B043ULL, 0x90DA4DEFFE7A344AULL, 0xF871C7A2E51773AAULL
        }
    },
    {
        {
            0x9D9ACF53374DD89BULL, 0x7C9B18ADDCDB9A6BULL, 0xEFAD9469B4450DE6ULL, 0xE8887D60DE042134ULL, 
            0x9CD15048E4641366ULL, 0x8E2179490F5C3EC6ULL, 0x78B01D83105C0E9BULL, 0xE55EF0FD36B3E901ULL, 
            0x990433A5A1334F4AULL, 0x8E44EE3CF752B105ULL, 0x1C34E23B27C64E9EULL, 0xBDE91547D49C5052ULL, 
            0x431CF2B9835ABCA7ULL, 0x47DA3D1A9A4990EEULL, 0xDC2DD0E35DB5955EULL, 0x8C98049F185053E6ULL, 
            0x39D0401691BC6B0DULL, 0xFD3FA7D8A779F5D1ULL, 0x795318F830DE6065ULL, 0xD3996E370DF4D1FAULL, 
            0xF633FEDB8072400AULL, 0xB3DDA9E84DBBD0ACULL, 0x28F71CD2776C3821ULL, 0x7BB565958A4CBA50ULL, 
            0x495F4F6F7046FA77ULL, 0xA94BAD6E15989065ULL, 0xB09FF37D89D9F0A6ULL, 0x8CBE01387543D9A0ULL, 
            0xEEC64D1CD0B07017ULL, 0x69722EA8A0201A06ULL, 0x7F71E225E0FAE446ULL, 0x91DDEDBA499D2049ULL
        },
        {
            0x797EE700EC882736ULL, 0x2D95AECFBED6B135ULL, 0xD48697ADE14DE5E6ULL, 0x5FD16BB2C1EF0A56ULL, 
            0x13FE86086CB91843ULL, 0x7F8A448FE3C6ABC4ULL, 0xEFE39CBB9201A527ULL, 0x1127A680E542706BULL, 
            0x9758BDFF25E1BA65ULL, 0x4BB207BDD2295CC0ULL, 0xC5FA766CCCB0DE75ULL, 0x84F558A3D3C94ABDULL, 
            0x7D10D8850B240876ULL, 0xDDE33168536448C4ULL, 0x31EA74C432363BBCULL, 0xD693302DBD8D0676ULL, 
            0xBE9520B7ED484251ULL, 0xEE694541ABE17B2DULL, 0xE08687781CDEDCE8ULL, 0xD44C06FBC633012FULL, 
            0xE69D2A0B66D07B61ULL, 0xDC7B2913C2328C27ULL, 0x089E516F6AF164E7ULL, 0xF016519F267FEAE0ULL, 
            0x421F03F912453782ULL, 0x7EF99FF6C69219D5ULL, 0x08755FDAA5374C54ULL, 0xE584454FAF4E338DULL, 
            0x4F7BB65C0513698EULL, 0xF1C622495DD9909EULL, 0x67104983D0005CC6ULL, 0x0DD64EC4B1A50A34ULL
        },
        {
            0x9770279B105DB132ULL, 0x42D0E5C8E28B0E72ULL, 0x9757A75EC0E79DEBULL, 0x6E9424EC8D02C746ULL, 
            0xFB0206335BE49B6CULL, 0x8AE75DA8900B9D41ULL, 0x80AD998F64E5958BULL, 0x2D2D9B65597E3F0FULL, 
            0x39C6030EE72B0118ULL, 0xEF15DEE7E4172B1BULL, 0x0D9588E7C87D1B04ULL, 0xC6E6D1FDE5C41BD1ULL, 
            0xCEBB55D7E3FCBCEDULL, 0x21FD3EC90C5E5D26ULL, 0xA1249EE6A764E145ULL, 0x4E5042E61CEB3B37ULL, 
            0x33D460F79F8B2ACBULL, 0x99988C1AAD24519DULL, 0xDC18CBF4B7F676CDULL, 0x008929990CFDA61BULL, 
            0xB5EFFA890D3FB42AULL, 0x2C26B15F164CD988ULL, 0x2BA273604CFEDAE5ULL, 0x2B0D1047B6023EE7ULL, 
            0x8AE789BB6CA9B61DULL, 0xFC98F7DDB827A90AULL, 0x7E744888B9B1FF63ULL, 0xE72160FAF7A88F89ULL, 
            0x09E65FE568812548ULL, 0x381DD1D44E6959C8ULL, 0xE4EF3B7983D91010ULL, 0xA3F9C50C1F6CF4E9ULL
        },
        {
            0x68C7B81122D6FF7CULL, 0xCB3979E9E9D7F22FULL, 0x7BA92768CBCE0348ULL, 0xEB6ABA91DB9D7D4FULL, 
            0xC2D80C2C3A814BABULL, 0xE22E1AC9642E2FC4ULL, 0xE01A240A8DF9F9DBULL, 0xB9898782377CCF1FULL, 
            0x9CD10E3BBA69CD36ULL, 0x614F4E037A658BD0ULL, 0x1E66AEAF117E5A0EULL, 0x5EC49CB57EBC05C1ULL, 
            0x044D9184A2C29949ULL, 0xEDA9D87AC31A57E2ULL, 0xF308B685B93AEAE4ULL, 0x7845F47D958010EAULL, 
            0x7EA3D2B1D25E70C3ULL, 0x7B10E1119A184CF8ULL, 0x7EBD4096314390EDULL, 0xAC8AB6C7A675335EULL, 
            0x6804D755E370C117ULL, 0xAEEE4B2D79A4FCA3ULL, 0xA1503A44322DE5B4ULL, 0xF61C4917F6BAFE70ULL, 
            0xB53C5ED275881690ULL, 0xFA6B8BAE1C5FFEA6ULL, 0x2278FA918B45E890ULL, 0xB9348E8C87825C4BULL, 
            0x5104B29983CA5501ULL, 0x3F9AEF477CDCE752ULL, 0x69F145A55B703E0AULL, 0x243281015FB60FADULL
        },
        {
            0x8D673E7CB09E7D5FULL, 0x77B9045B86A82275ULL, 0x9833D6B0D951CEDBULL, 0x73798F2A1901DEA6ULL, 
            0x33B19F64932E7886ULL, 0xCCD0FE2AD14FDB3CULL, 0xF44F04856ECA188BULL, 0xF78EE47C72FD21D6ULL, 
            0xD9896831DB443822ULL, 0xC8B6A57526B727BFULL, 0x263D2302F42FC8BEULL, 0x3816BE335888DBC8ULL, 
            0x197022CA55C74034ULL, 0x17C3B5290A1F484FULL, 0x8246DEA37B1E954AULL, 0xE32BDCD0499BFBE6ULL, 
            0xD66BF59C89B6086FULL, 0x080C6656BC9B5015ULL, 0x7FBAD7720E7E13EEULL, 0xF168A6F51ED3DD01ULL, 
            0x9F62BA58997A3F0BULL, 0x8B4117623FFCC51DULL, 0x77483D7EF63ECB7AULL, 0x5E98CA7365885768ULL, 
            0xB5BCE272EA193A63ULL, 0x056047AEF425DFEAULL, 0xC0964C393FD70585ULL, 0xAF2A2A3C8F427967ULL, 
            0xCA3102FE8471E344ULL, 0x54BAF6E46AA284C7ULL, 0xDB8CBB0A5154FF14ULL, 0xBE91F893D1B145BBULL
        },
        {
            0x961D42AA2D35259BULL, 0xDC564137E5C278BBULL, 0x3633A07EDAC0EA5CULL, 0x1FABFF14C339CB05ULL, 
            0x29AC33024F89ECDFULL, 0x5B33EB008351CFD0ULL, 0x45B6D775BA6BB129ULL, 0xE068CF14BC7D577AULL, 
            0x16084E175B6D68A3ULL, 0x5F8356141DBEF14AULL, 0x8E0D0D193FACD528ULL, 0xD74A2DDEF9CD42F1ULL, 
            0xBE5EC39A78A7F730ULL, 0x295C7F9829211AB0ULL, 0x589A423D9548F3BAULL, 0x6C346915B1B4F416ULL, 
            0xAEB8A1949EA0F138ULL, 0x8C0EF07AC95AA65CULL, 0xF665188B1CDD611EULL, 0x66F8D8B3EB4A8DD5ULL, 
            0x1F968F7315DAC20DULL, 0xEDA3388601DA9317ULL, 0x1D74854190AA4778ULL, 0x8E089E1EE82AB72DULL, 
            0xD519E9C0206A119BULL, 0xB328757DA2B1969AULL, 0x9B1BFC74EC7201B1ULL, 0x9ED9D380C1707004ULL, 
            0x3C1F3130329B6347ULL, 0x0A095956E2137635ULL, 0x16656DC32A08CE53ULL, 0xEE172C11C965757DULL
        }
    },
    {
        {
            0xBC0EB37254B9EFA8ULL, 0x079F9970E7A29622ULL, 0x12E30BF0244C3F93ULL, 0x58643C92600CC26DULL, 
            0x702E56DD55439B56ULL, 0xFB681112BA334504ULL, 0xDF2975C36870049BULL, 0x31E16401D0A4C6EFULL, 
            0xAF8230DC56496E26ULL, 0x0B3F2585BCA96870ULL, 0x0D141AE353BC3D4CULL, 0xB1A3995B910B2948ULL, 
            0x46D7E5AED00D7AEAULL, 0xD9466C47F8312706ULL, 0xD4D5FF3C6C94C882ULL, 0xF7FACFABEEA2C737ULL, 
            0xEA9E73B46654DF64ULL, 0x68C0D6FA73A36BF2ULL, 0x313516AFDC220355ULL, 0xFC3BD7A0DF335F7FULL, 
            0x00D195068FA891E0ULL, 0x7139446EA1FB6AD8ULL, 0xBF23BF777F90B2D1ULL, 0x9C6620D1DEAC1D8BULL, 
            0x6422F2270A47FD40ULL, 0x82255CE2AEC12829ULL, 0x6C9F93EBB439365BULL, 0x304915310927F669ULL, 
            0x25493F261319E1D2ULL, 0x66EB54971229B7E5ULL, 0x05D41EA0D078A955ULL, 0x921CFB3335365F59ULL
        },
        {
            0xD66FF5548B89916AULL, 0x9085FD2BE5721C15ULL, 0xF08ACCDCFB8476D7ULL, 0x5E410708D529A550ULL, 
            0xAC60042BD1631D53ULL, 0x22C9BFA700CF2C5AULL, 0xDB3BF9C3B56CD0DCULL, 0x8DFF1A0EC0A9483DULL, 
            0xB4BA9C14BCDD136AULL, 0x6ED61C45F59EE789ULL, 0xD9E408673F374022ULL, 0x4F74757493997F02ULL, 
            0x1F709EEA8479C41DULL, 0xB660274F8EC04C34ULL, 0x8036E593036D620FULL, 0xB42EE39643629D4EULL, 
            0x74F454192C7F27B1ULL, 0x176BA399D086FE78ULL, 0x0895195EA62EED70ULL, 0x8CBC581ABFF32640ULL, 
            0xDE443740A78051BEULL, 0x8FF1B2C17B9C3A14ULL, 0x8AF6804F03882A03ULL, 0x2C9E81A858D757A0ULL, 
            0x9A5DB90C0AA57C7DULL, 0xE832EC74B95A1364ULL, 0x9278451FF594CF4DULL, 0x1965B6E0AD941CC2ULL, 
            0x3BE85A18875EA917ULL, 0xBCB52E2FB02A76E9ULL, 0x7CFA462A8D1AE54EULL, 0x8C6CCB1AE8444B42ULL
        },
        {
            0x313CC721D3794682ULL, 0x97CDF73E9F6776BFULL, 0x4BB9A0C86FF141C0ULL, 0x6351FDF6AB75FBAAULL, 
            0x340BE2501EF78BADULL, 0x15C90B7A4C91A745ULL, 0x91650F8330994931ULL, 0x28D8A9C6E1B53C55ULL, 
            0x47784EE72FC35B60ULL, 0x83B1E61AD4B0D887ULL, 0x07B67E649F5979E4ULL, 0xA32B7A67EC2C8D0AULL, 
            0x7416FBB035E52EBAULL, 0x015F843BD8A9CF27ULL, 0x376FB5C28BDA10CDULL, 0xDF3744A037281CCBULL, 
            0x71AECBFD0DD88832ULL, 0x27CEAE431B67952CULL, 0x066F0A07182EA8CAULL, 0xFF7C4E3679D2F6A4ULL, 
            0x422B80319C5AFDE5ULL, 0x05F1F64160B57693ULL, 0x823ED05594A29922ULL, 0x6C29D773D28CD439ULL, 
            0x5F241DBAF40A560BULL, 0x8B58C8FB27745557ULL, 0x4C78F1066ED14B91ULL, 0x5D0DA34D9E50B943ULL, 
            0x2A4ABE6D84C0C84AULL, 0x887A42C0ACB2911EULL, 0x2D9DBD3033476975ULL, 0xA8500E27A4CDF083ULL
        },
        {
            0xE6AF739F25EADD42ULL, 0x6C97DC791E8DBD5FULL, 0x8D92FAB5DF55D534ULL, 0xEAE6A9988B217FB5ULL, 
            0x30DAF34773304F77ULL, 0x4BCBEB1383E65DB3ULL, 0x82F497DC1C15596AULL, 0x524A1CFE52796043ULL, 
            0x0B8A14D6EF487AB6ULL, 0xA2085DBFC7A05D41ULL, 0xB1DA38CFEFD5753FULL, 0x1C21F08E634AB93DULL, 
            0xF806648223E4A69AULL, 0xACFB43C33D5B09CFULL, 0x34FB548C009FA48EULL, 0x8EAACF46ED181690ULL, 
            0xF7EC3B200FC8DEABULL, 0x08463140D3D53D2CULL, 0x008F0E6CD201FE00ULL, 0x00B09706EA52DB32ULL, 
            0x811FBFE1F2CB0166ULL, 0x5052B68C9AB03D89ULL, 0x8648147858545CB5ULL, 0x1F8393B650341F59ULL, 
            0x43F59C24E106859CULL, 0x9556DB230FD80094ULL, 0x58BAD5C4ADF0CDA1ULL, 0xBC0B5F115A37477FULL, 
            0x34D0A58F59148897ULL, 0x06DB2D1F77B78E6DULL, 0xFF72814529DA693DULL, 0xAB77EDD0EFC9DEC9ULL
        },
        {
            0xE480BE6E3B04666BULL, 0xE12BD18E82D3563CULL, 0x9C1B83AFB8E1F0A4ULL, 0x7A8204C0189FF947ULL, 
            0xC8A52EF40D17E112ULL, 0x221C3D021588A67CULL, 0x427421B1ED563472ULL, 0xC7FB786EF165CC88ULL, 
            0x69834E4CE193713CULL, 0xD277D7463F9B48B9ULL, 0xE89EE038E8A4EEB5ULL, 0xEA3E6DD2A1AECCCCULL, 
            0xD7BE20CC80FCD4F3ULL, 0x45FC0C2B1B4DF85EULL, 0xB6E63B055ED354E2ULL, 0x93E08E45CF8AFD2FULL, 
            0x707F569E890EA332ULL, 0xF7EBD8CB0F4F4DF5ULL, 0x36F5BD0D2AFCE278ULL, 0x75574507570AC637ULL, 
            0xD5F49F8086558C90ULL, 0x1D8B48594EA59941ULL, 0xCB8955C90B6A9546ULL, 0x7AA03AFAB395C85DULL, 
            0xE8A4880C9AA41FE0ULL, 0xC2DE071AF64D387DULL, 0x6EDF8A64C44F4E65ULL, 0xD2C0972CB17F0548ULL, 
            0x270D326B994AB6FDULL, 0xD33DDC54ED18D7C0ULL, 0x97B4F1C1E6C6E110ULL, 0x8E1DB0071602E878ULL
        },
        {
            0xD3766AC1378A0F96ULL, 0x4EBE4CB9C9395E04ULL, 0x487199FC15C03066ULL, 0x03FDE8611596A9CBULL, 
            0x90D05773C8F0F875ULL, 0x7738BCA56022BD8EULL, 0x15CDCC2882609485ULL, 0xA442AB94EA7A09D0ULL, 
            0x01D512D4E6A6367FULL, 0x610C72951B8C5273ULL, 0x9A4079B145409EECULL, 0x8B404396048534D2ULL, 
            0x58970A0BA87B002AULL, 0xAD82D5AE5E3C4EBAULL, 0xDD8948258750E961ULL, 0x5AA704F2E1D88A01ULL, 
            0x069E2E2AC6241F15ULL, 0x6FB90B5161EAD562ULL, 0x48FC741AC8313C68ULL, 0x3AB63C76B2D9B6A6ULL, 
            0x2449D8BABE4942CAULL, 0x52C3B000442761E2ULL, 0x2DB70851B24A403DULL, 0xFFF6D62D8C597770ULL, 
            0x3AB1E270BB5E0554ULL, 0x52A8D0A9CD52AE65ULL, 0x0DB308AA27C4542FULL, 0xD72E3E42E3905C74ULL, 
            0x739A2A69562DD142ULL, 0xB0A9E846182C2D82ULL, 0x102D059554BBF43FULL, 0xA5C0761B42072455ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseCConstants = {
    0xE4861087C5E2DC3AULL,
    0x89789A77A6255017ULL,
    0x44ADF94E5CEE354FULL,
    0xE4861087C5E2DC3AULL,
    0x89789A77A6255017ULL,
    0x44ADF94E5CEE354FULL,
    0x2F46E45464ACC7DBULL,
    0xB6B6E38BD9664467ULL,
    0x17,
    0x1A,
    0xFC,
    0x7F,
    0x78,
    0xC8,
    0xD3,
    0x3D
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseDSalts = {
    {
        {
            0xBA0C5F51DB34B3B3ULL, 0x86661906B42CC51BULL, 0xBCE093E82C6F5F8FULL, 0x924B579139F427C6ULL, 
            0x49E1835386158729ULL, 0x210B3031A53197ADULL, 0xA30A022EFB7DA8F8ULL, 0x8DAC819C31C23D99ULL, 
            0x07962CC236B54FA0ULL, 0x756707E33F492547ULL, 0xA2BF8531B9DBA349ULL, 0xD2A1AC7DF2FF60F9ULL, 
            0xD4FD9D322950915CULL, 0x094A2CFEEE7B698AULL, 0x96DE7AFC4DD3FE24ULL, 0xF3A95D940AAC0B2AULL, 
            0x284D3C6660369ED3ULL, 0xF8B885317A51D2A8ULL, 0xB866616B94457A9AULL, 0x15AA7688663FC2E4ULL, 
            0xDDE0AD751364C6CCULL, 0xA421BBB05B5BAE49ULL, 0x36BB0BF4C5993FE5ULL, 0x50D6E87694710D49ULL, 
            0x72032D5E7F9D5FADULL, 0x516642E1C803B58CULL, 0x2D8A3A9C81E321F4ULL, 0xD8888881974AE73EULL, 
            0x5B583E975E2FD3E2ULL, 0x528F22DF0375E22EULL, 0xDACEBD907DF5D395ULL, 0x33C1AE5A2880071CULL
        },
        {
            0xBAFBF06A911EB416ULL, 0x7C1FAA7B76BC7DE8ULL, 0x0A2B32173F4E802FULL, 0x3C7941448114028DULL, 
            0xC56731B1C473A4D7ULL, 0xF6C6AD5AE5B3BECDULL, 0x0EEC86F07ACE418EULL, 0xA617D18CD0FB8FD3ULL, 
            0x6AFABD4FFE703507ULL, 0xF5A63DA3311D3B8BULL, 0xE95FCB0C92354136ULL, 0x6C9E60596193AF16ULL, 
            0xE459FF3CE0FD7519ULL, 0x435930050AF94A75ULL, 0x1A84D6E1392421B3ULL, 0xFCF28A078E7F23E6ULL, 
            0x9D94ED2F18FC8A4EULL, 0xF45734488B689249ULL, 0xF863A53736F99DB5ULL, 0xAE47875B80160DD1ULL, 
            0xE90093B6693BF861ULL, 0xD13DED12D193905EULL, 0x98450AEB768EEFA8ULL, 0x59AD5A2D0ACDA776ULL, 
            0x572D01A5B0CFF044ULL, 0x53B6459058DCD8F6ULL, 0x2A99FB65355FEAB8ULL, 0xCDCE442A8C3ED978ULL, 
            0xF5F721DBEF7B56D4ULL, 0x14FD2B8BDD0784CCULL, 0xF69405DDC2F8B0C8ULL, 0x2435E6B6076F5DDEULL
        },
        {
            0x6B697CF6B0C1E9C2ULL, 0xFDA69BA465BBD301ULL, 0x73B38DEC8A8FC042ULL, 0x6E0194B4C54F6805ULL, 
            0x338686B94E1C5C3AULL, 0x6A2C6077DBC394F6ULL, 0x825AA57EB486A48FULL, 0x35BB59D6AE8D88F4ULL, 
            0xB7FC6DE3425C7542ULL, 0xA6E29029E6ABEB30ULL, 0x050D2AF7E99411D4ULL, 0x973943ECF7F78705ULL, 
            0x53BAE20E7C4C3F71ULL, 0x5EAC8F24E764B029ULL, 0x1DE25CA37BEB83D8ULL, 0xB82361B63AAED934ULL, 
            0x194CB0311A9018E8ULL, 0x6792A41EE85D4C9FULL, 0x67285913EE774483ULL, 0x0785CF26B789FDC2ULL, 
            0x5A6BD8E4393484EBULL, 0xBB90A8546B1CD98EULL, 0x22E52AE51E7FD265ULL, 0x5665ED0E41207D26ULL, 
            0xE1534ECC6A127585ULL, 0xCE4704F397882602ULL, 0xF22261A5903E66F3ULL, 0x0A4E4718C569F05DULL, 
            0x333A27A6C10BBAE5ULL, 0x0184405558B5E3C2ULL, 0x8BCB29908F51ECE8ULL, 0x09C7BE8AF8BF31FBULL
        },
        {
            0xEC15D1CA6317DEF3ULL, 0xBF2EAC30FC764331ULL, 0x22043CE05DFE5BE9ULL, 0x580C1CFA4B8CFD3FULL, 
            0x34B0280694CE7B2AULL, 0xDEB287EECA5E4D3BULL, 0x78385C787470D7B9ULL, 0x7D5D4A8CC00E4AA4ULL, 
            0x40492C15C98EB492ULL, 0x429117584425E10DULL, 0xD94D9D61A38B3646ULL, 0xD3DDF688F5CACF57ULL, 
            0x33A46FA165A53517ULL, 0xB5D9C9FEDC79175FULL, 0xF6A6CFD8E134B396ULL, 0xEC11442FF0DA16D1ULL, 
            0x5886F91CCB28A35FULL, 0x532AD1B93EB57B0AULL, 0x4F34B05839148636ULL, 0xCCFD2B647350C1D3ULL, 
            0x716AD10DAF6B5978ULL, 0x25E73D025A853FDDULL, 0xC3AB4AF1663E05DDULL, 0x85CC2A46EAE9C1D4ULL, 
            0x0DDA04DF4B3BE30BULL, 0xE40232FFA916E081ULL, 0xBEB035BE78396213ULL, 0xDCCB21CB976D0FB5ULL, 
            0xC22F6B1BF7F176AEULL, 0x6256B7FE1E19E8B6ULL, 0xAE6F0E9E55A50E85ULL, 0x8114BF33EC244D85ULL
        },
        {
            0xE9AC7AF2D39A0C64ULL, 0x3DBD760413EAFDE6ULL, 0x1C9A9740DFEFFA62ULL, 0x16113EAE2A1E892BULL, 
            0xA11FB820B3ADE64AULL, 0x69530D42103713B1ULL, 0x2B09F05AFC901777ULL, 0xC248A67FB447FC87ULL, 
            0x686D2D10A0CF3FD3ULL, 0xF4D715C0A4F44684ULL, 0x5573DE07E96FB0A3ULL, 0x62BC469AFBF8D4D5ULL, 
            0xA67F35BE67C02EE6ULL, 0xD2D3D63EC35DB366ULL, 0x10231CD5D3F35748ULL, 0x172E1F65A3FB2848ULL, 
            0x7E6F5A4D6C713370ULL, 0x6A102127C345097CULL, 0x78A8A8CFB6C881A1ULL, 0x6E367D12878E969FULL, 
            0xEED6649CF55B6401ULL, 0x9D6B7A4C91C3AB25ULL, 0x5E7EACAB68778469ULL, 0xA60FB91ADEEA33B5ULL, 
            0x5E528E9E775A1DC1ULL, 0xD37C5C52E44A27FBULL, 0xED398DE740AC318EULL, 0x5A5FCD470879EC6CULL, 
            0xD9CDF0247C361D27ULL, 0x3608269C7AB60D0CULL, 0x4F8D7929785FB7FEULL, 0xC9767FEC85A96BBFULL
        },
        {
            0xEF8CC71D3CAD5D83ULL, 0x9F5585A4C58F51B8ULL, 0x401D4AD0FBC76D34ULL, 0xB9D116FF75C1FEF3ULL, 
            0xEE2CA8AEA8E28F34ULL, 0xAB94B89BC4ECB9B0ULL, 0x506869D00746ADA5ULL, 0x4030CE2148B87E53ULL, 
            0x7AE6672CD361EE53ULL, 0x3CA824E568974357ULL, 0x28A6A18C8DEDF5E0ULL, 0xA81EBE1D92C7A86FULL, 
            0xBF1554995D9D0A3EULL, 0x27E14739DD875EE8ULL, 0x0E3725FD322D2F18ULL, 0xF5AB4D37E553E339ULL, 
            0xCD064EF615C4F6D0ULL, 0x953E659C7440B498ULL, 0xA6DCABEE9193E0E9ULL, 0x2CFF86AC291554D3ULL, 
            0xAA8EEEA087FC18B3ULL, 0x30ACAC6A68B745F1ULL, 0x1717EA04606554A7ULL, 0x921421F4FE5D68D7ULL, 
            0xDEB9471E25034D51ULL, 0xA798C7BACAEEFFA5ULL, 0x37DCDDEA4FBC644AULL, 0x445BCC2597396881ULL, 
            0xDA39ED70A2B12952ULL, 0x644D126E24D3DEB6ULL, 0xB1C7D4761FF502F3ULL, 0x966877F9A3F59C01ULL
        }
    },
    {
        {
            0x64A03A3E293FB544ULL, 0x7C59BCF38210C45CULL, 0x23530684316A1DE7ULL, 0x631927BADF50D8FDULL, 
            0x3527A670309934BAULL, 0xDDFA19080B0B8ACCULL, 0xA23CBCF004C958B6ULL, 0x697D79C41BB8DCAEULL, 
            0x64C73CEE6027974EULL, 0xCE79B4CCAD483087ULL, 0xB0052C32EB90292BULL, 0x92185AB52BABC694ULL, 
            0xB36BA0BB79AF6E64ULL, 0xF3A84BA8DE0B621EULL, 0x27396F92386E1C9EULL, 0x37D66A044C639467ULL, 
            0x7AD2CE88CA1577E8ULL, 0x0E6791DF219F81F5ULL, 0xECC5E457D6AE5E10ULL, 0xD23AA3669D1D66B1ULL, 
            0xF9691AF260908F46ULL, 0x089102AFC4F8F705ULL, 0x6E27FA8B0590FE1CULL, 0xE0A015AD86F13E75ULL, 
            0x163000AB947CED02ULL, 0xA2E5507459DDEE06ULL, 0xDDC19DCF25DBFAECULL, 0x121C8174A25A6696ULL, 
            0xF1F971887E780DE4ULL, 0x7B456DC18B4D7151ULL, 0xE9C4F4C52B2F5D79ULL, 0xC22BE1864FA17EBBULL
        },
        {
            0xCA6501784B230784ULL, 0x7BC82A7B39A3273AULL, 0x8EA912DA6986F6F8ULL, 0xC245E5AD374E98DBULL, 
            0xF14C69DDBEE21E2AULL, 0xEFB4406A45F92B63ULL, 0xD5C3893C39F0948CULL, 0x945E605F9638AD74ULL, 
            0xFEE645522E558C26ULL, 0x0D008D275060203EULL, 0xD5CCD8ACE2E7305CULL, 0x3217C9EA44A90EC4ULL, 
            0x26381BA3FEB2968AULL, 0xD91A4A1FD48BA87EULL, 0x67492078D5E1E13EULL, 0x92DD1FE16AE55F69ULL, 
            0xCD59D04AB9022A96ULL, 0x0E1067E01632639FULL, 0xB04F474A90C1DF28ULL, 0x21B9EC559B7064B9ULL, 
            0x1B937A3D4CC29523ULL, 0xE46C812FF09E97BDULL, 0xC7021AEE50D66D7DULL, 0xAAB1604C1C621B50ULL, 
            0xB87B6DB143663C51ULL, 0x759A65F3F607ECDEULL, 0xCE57B73885A8ECFDULL, 0x50945F61CFCD5A5EULL, 
            0xE579E5220079E4B3ULL, 0xAA6041837F802076ULL, 0x4B49338F68E63432ULL, 0x133B40B14C2A9A96ULL
        },
        {
            0xADC5BA459559EDADULL, 0xA241707A4512B845ULL, 0xCF257287249526B3ULL, 0xE550E14A4D9A28F7ULL, 
            0x105D6360561224A1ULL, 0xF42DA2A901FEAEE6ULL, 0x5333BC1CE6875FFEULL, 0xA2FAADA5587ADDCFULL, 
            0x7A2BB0A9D1153A15ULL, 0x91C95C10095A27CAULL, 0x6384A9181CB6E17DULL, 0x6C448B91EBC0F0EAULL, 
            0x017F2510B30230CDULL, 0xD8B13F0B1A73395BULL, 0xB4C82BE1C9A960F7ULL, 0xF5D55A8D9578736DULL, 
            0x93CA67CC6F2CE269ULL, 0x38F800F8D96DD780ULL, 0x3CAA1951070B6AC4ULL, 0xB7D1629506BD6B6FULL, 
            0x6038D996D8B7B1F8ULL, 0x1BC3846ADE704038ULL, 0xF42742AD6ED290B1ULL, 0x8C16F89E7870552EULL, 
            0x20AC0049CA4185D8ULL, 0x373D70F282C9D15BULL, 0xC955B23770AFC665ULL, 0x8B02CC3009D8BF76ULL, 
            0x0B5916E3A5B56C8DULL, 0x6EE273DD5FFC60DAULL, 0xA18A8CE27B288342ULL, 0xCFA173A932FF0DB2ULL
        },
        {
            0x026A56A79E4B5FE7ULL, 0xF7D66F261C5E6D53ULL, 0x4177FD448DE0B7E0ULL, 0x47A709BE763399AAULL, 
            0x84279D2013BD540DULL, 0xC4B47BC16F6C7DD4ULL, 0x0376237F61A8924BULL, 0xF33BDF726D259D76ULL, 
            0x9DE4522303CA71DDULL, 0x1BAFBAB3AFA7B65AULL, 0xC2247D5DF5214BB5ULL, 0xF0770169E3778670ULL, 
            0x76A9DFA1CFF4ADFCULL, 0x736FA8784B6BE459ULL, 0x7563A63DEA221C35ULL, 0x02478367D6F1AD06ULL, 
            0x96C0037CAB206C13ULL, 0x550240EAC14DDCBCULL, 0xECFF40D6A65A870DULL, 0x126A5398E6E92939ULL, 
            0x7EE1F563032601ECULL, 0xB13CC20E53FA8AE0ULL, 0x45B77663492407F1ULL, 0xE413A9480ED36C4BULL, 
            0x5FBF6772464C9250ULL, 0xFC48B486C357533BULL, 0xB066D4057D1A9A43ULL, 0x7CD4770C087BE50DULL, 
            0x6AF8A19017D29548ULL, 0xD39C35865DB49141ULL, 0x7BB17DF97F38D155ULL, 0x81E2A03FB8E8B61DULL
        },
        {
            0x3B05456F84E55757ULL, 0x071DFBA4B13E904CULL, 0x53AF541D9F27C2A5ULL, 0xD5E537230AFCC832ULL, 
            0x80525BC698E3A99FULL, 0xB6FA41E7B2661244ULL, 0x2101BD17E770ADE0ULL, 0x54A6D0AB8274BEC1ULL, 
            0x02CBEA798A22A3D8ULL, 0x2E0768CB2C0ECB5CULL, 0x007E079E4A8F9EB6ULL, 0xC37A605AEF695732ULL, 
            0x21354F2A753F47D4ULL, 0x1E2801244D961436ULL, 0x7005BA3630285CA8ULL, 0x2A059BB434B85634ULL, 
            0x47DA9ED0AC186631ULL, 0xAD6859F46A3D4135ULL, 0x483464218C160B9BULL, 0x83D54037CC6A1A31ULL, 
            0x37D1CA07EE2C45FBULL, 0x398D57FED64D5201ULL, 0x35DFDE2A33C7172CULL, 0xBE6244B120F0A3E0ULL, 
            0x8798A5623DC0AE09ULL, 0xE20B49440A9A02DEULL, 0x7B94FF56124B05DBULL, 0xC665597B60B1473FULL, 
            0x5737E65045C51744ULL, 0x3058B9A8BCD0B10AULL, 0xDD98AAEE4DD91099ULL, 0x9C953D46943BB0BFULL
        },
        {
            0xC50ACFC2AA63BE59ULL, 0x82775EC524FE4827ULL, 0x64810B6338E5724CULL, 0x5360F61594B84E92ULL, 
            0x552C9044A5296D78ULL, 0x56B75BE864E2AD21ULL, 0x2B468AA71DDB8919ULL, 0x91DD3CDF5CD4DEEEULL, 
            0x3964212C34816E12ULL, 0xEC2CDD34D4F0A310ULL, 0x3384A05061BAF747ULL, 0x76EDDBD63B290755ULL, 
            0xA59B6D1F4BA9A9DBULL, 0xD5F1A63991DFB6A3ULL, 0xA854406F8426816CULL, 0x60809F2C9944B744ULL, 
            0x324818039C3FF3FCULL, 0x3CAD64D3717DC105ULL, 0xE7198E856CDA34D2ULL, 0xB433D32AFF8A626DULL, 
            0x57F4D566B8CDE39AULL, 0x1EE58FB82A221198ULL, 0xB8C1D5D36D3A33E1ULL, 0x1DD8E8E227D64EC6ULL, 
            0x547EEA1634CF6F98ULL, 0xB77B1DB62192C2F7ULL, 0xDA82768B38C7FB61ULL, 0x5C2CBBC8D03FBAFEULL, 
            0x38B58553CE44E386ULL, 0x189714DF3124CAB5ULL, 0x8A7DB99A8DA8EE6DULL, 0x5EEBB32FEF8F9274ULL
        }
    },
    {
        {
            0x552C25F24C2460D1ULL, 0x1D5BA98C9D030A44ULL, 0xBBF743775F17620EULL, 0x0BD99ECF95379D87ULL, 
            0x8FE3E64663115DB4ULL, 0x5B9A2A40E7EEAC64ULL, 0x9F5FA5B88E33AF2CULL, 0x746920514DDB7290ULL, 
            0xE2A7D1D894B0FE05ULL, 0xBB97332C7F24578CULL, 0x1921262FA8E691AAULL, 0xCAE609D2D6661290ULL, 
            0x2F4602EB571C2F2BULL, 0x8C40E36D77F8E07BULL, 0xFDCC0C96A4F0CA78ULL, 0xE750DDC3C75F4B51ULL, 
            0x9D0BD55D2C2C225BULL, 0x3D176021481F9610ULL, 0xA316F02A28462403ULL, 0x182C96E81DCD64F1ULL, 
            0xC33BC5CD351E3665ULL, 0x5C93EE33FD630C79ULL, 0x06CB24AA50623728ULL, 0x078097592E382137ULL, 
            0x63F18812F35EF646ULL, 0x28B09D6B034AD9F0ULL, 0x6139677AD9490408ULL, 0xD9D3C6E06D5A611FULL, 
            0xB3E498EB611FB578ULL, 0x2698A1C8734A23E7ULL, 0xC077667704734C06ULL, 0x77A0B26D2759A9F4ULL
        },
        {
            0x08C57E159518CD6CULL, 0x678CD6095F90DEBCULL, 0xBD358E4613C67492ULL, 0x34ABE0831199E5A6ULL, 
            0x57410D0EB2509E64ULL, 0x3A37AED0252271A5ULL, 0x75D802DBCD4D2CC2ULL, 0x42D509BC60AC388EULL, 
            0x5A71311F3D7B43C7ULL, 0x3525111D74851AA0ULL, 0x6708DAFB0A04C4A3ULL, 0xDC3C459F98AE38DBULL, 
            0x411E69C8C186EE29ULL, 0x3138A4BFF52F1B88ULL, 0xBC68AD99F486614AULL, 0xC68819B866616E08ULL, 
            0x96AEBE41D8FA2666ULL, 0xD6D6CB49E70B0469ULL, 0x66C32E639B2BD218ULL, 0x6DAC6C2710C54EF6ULL, 
            0xCFFAC48DBB518B9CULL, 0xE246518315326759ULL, 0x5061045DCDE84F08ULL, 0x91D10D87B375F2E2ULL, 
            0xF7C52A9D2AF6B682ULL, 0x0981539E5A239379ULL, 0xC7FCB821B5B8DBBAULL, 0x079D6F501F80A38BULL, 
            0x3C6E2C2B43D0FA31ULL, 0x80B6743653146B2FULL, 0xDBEE0C69B4B18D23ULL, 0x332C6A79897B708BULL
        },
        {
            0x09C3EE0C60D821ADULL, 0x63B0BD6A88980385ULL, 0x2F765F2EBC4E2B34ULL, 0x3B5A565041C37117ULL, 
            0xE129BB9AA25CA2D3ULL, 0xC2C18619488A2F62ULL, 0x944EDD1A545F9D34ULL, 0x3EF7A7F743AFC3FCULL, 
            0xF69C9EE7EA133084ULL, 0x27A1A5B1A089EA58ULL, 0xB540D20415CABF36ULL, 0x05F0931EC7B413A0ULL, 
            0xA89F7BE54F94AD02ULL, 0xBE0C4C8520BB0A7FULL, 0x4BF44EAB784B8B06ULL, 0x7AB010910AD2D2EDULL, 
            0x2178B9CA34DCCD25ULL, 0x77C1EF0DF2E34E64ULL, 0xBB21442B745B131DULL, 0xF88D8FC91DD01BD9ULL, 
            0xAED912D97808DC75ULL, 0xBF9E1C5498AF4764ULL, 0xB17935BB5A29A8BAULL, 0xDA51FDDA49DA29B4ULL, 
            0x3636A2458DB71926ULL, 0xD72BF3AEBAE6D461ULL, 0x60469E9F69760C0BULL, 0xD9B0BAA9309CE02BULL, 
            0x95B90F88B13739ADULL, 0x2D1C65B41F57D8B7ULL, 0x96A914553DB74FA3ULL, 0x2D6E6F73BD4077F0ULL
        },
        {
            0x82C2F0F15269528CULL, 0xF55157DAEC191103ULL, 0x4D2092F529C03059ULL, 0xA7F907081739EFE8ULL, 
            0xE5F9354643FC02E1ULL, 0xECCEFF6B1FD8DCE3ULL, 0x30C65E6E36597F23ULL, 0xC4ACB8B6F43B2F42ULL, 
            0x9F868BBA068E0BBCULL, 0x3D504E2EE1A0F009ULL, 0x2B5CF4CAFD55BA43ULL, 0xF82CAAFC3A3215CCULL, 
            0x8BAC0CA4A8C2CC5FULL, 0x9D318208C89B12B1ULL, 0x6F5AC43B17B97414ULL, 0x6561D1E5018620EDULL, 
            0x17390FE92EB43232ULL, 0x7CA59C6C2799499DULL, 0x5104C8E884021468ULL, 0xA7F19CC071385C4EULL, 
            0xD6AC51532A22C5B0ULL, 0x4E7A0E305BDDFABCULL, 0x0A80B984486495BCULL, 0xD24961739D8575AFULL, 
            0xD4EDCD9D26C2DF35ULL, 0x6FD6DCC94120483BULL, 0x741222E5DA5CEDF2ULL, 0xC18A6E184578282CULL, 
            0x089F1166964DA938ULL, 0x4479D51A84B00092ULL, 0xB52083D97E204EFEULL, 0x45609A0E14D54502ULL
        },
        {
            0xB4569B7E4B60F1C7ULL, 0x10A1BA82450A55FFULL, 0x2A2D8E710A82D55BULL, 0x1A42B1C1B7464E23ULL, 
            0x0AE29CA377BB91B9ULL, 0x674AFE52122932AFULL, 0xFCF1A42F282D1176ULL, 0x002EE491769DAD1DULL, 
            0xD8D73C66F8D09F94ULL, 0xA196C1C29C50F3DFULL, 0x7E75828B9173A2A7ULL, 0xE91C1494065283C9ULL, 
            0xD68B870714748A92ULL, 0x68A06C9C63B01C59ULL, 0x9C8D1D05F9B53244ULL, 0xF20619166671A420ULL, 
            0x609CEF6881B7AC41ULL, 0xDEF26EB82AD27423ULL, 0xC8FE980B78462135ULL, 0x65F253844ED1D0E5ULL, 
            0xCDBD8A059FF9F663ULL, 0x128FD42F56665444ULL, 0xE1C981067E62DFF9ULL, 0x635AAAECAD3A3640ULL, 
            0xD5B6BE1A3491AB19ULL, 0x81831CA1409FCC78ULL, 0x16DD9736F65A2B19ULL, 0xDB9998DF769353E4ULL, 
            0x4DC5F0D3A7110635ULL, 0x87413D05DE3B0A32ULL, 0x4AC79AD959A03075ULL, 0xD00781D65D60F3DEULL
        },
        {
            0x361C4018F4DA8850ULL, 0xA2408C150112517DULL, 0x572F5F41B5AB1639ULL, 0x14D5317DB42515A9ULL, 
            0xE911111A9C2ABA4FULL, 0x85D035A0958D0D4EULL, 0xAB87926A635BDFA6ULL, 0xAEB1A367F04D8FDAULL, 
            0x0D3BC34ADFB386B2ULL, 0xD4E0B6FFE0F8D4F9ULL, 0x7CF129B05AFC5D1DULL, 0x452BF4A2163E3FF3ULL, 
            0x13C3E50CC8145EABULL, 0x45609438310B93B3ULL, 0xF7AA5875712DFBDFULL, 0x328AFE056885AA72ULL, 
            0xDD932108177C3E1CULL, 0x11FFBB716EDACF34ULL, 0x6E161E3A450357A6ULL, 0x33B4DD717D23951EULL, 
            0x7C936E8D5DAA3EA4ULL, 0x32ACC6726077A647ULL, 0x88D5DC12D3F880CFULL, 0x38D4B005D9B3DF1CULL, 
            0xE396330F3FCCB9B8ULL, 0x3467BD077098343CULL, 0x93D12D972D73B574ULL, 0x781D76546DE1D2DCULL, 
            0xDCC64E4382DD6636ULL, 0x727C00D575517E9BULL, 0xBC9A1EF9A02A1695ULL, 0xCEAC23F552403B41ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseDConstants = {
    0x38B7DEB771ECD320ULL,
    0xE811DDAB1E7CDE87ULL,
    0x6ACFE22D171269E4ULL,
    0x38B7DEB771ECD320ULL,
    0xE811DDAB1E7CDE87ULL,
    0x6ACFE22D171269E4ULL,
    0x5DDBA0A5826B6B79ULL,
    0x0A7D8286BC2D4ACCULL,
    0x01,
    0xB2,
    0x97,
    0xD0,
    0x5E,
    0x27,
    0x20,
    0x0B
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseESalts = {
    {
        {
            0xF59E22C5AD94F0EAULL, 0xE0FD11280CDEDA7FULL, 0x89949DDB18698931ULL, 0xE87AC69525677F91ULL, 
            0x72AB888816D7FAB2ULL, 0xA46D3CA6C094069BULL, 0xE7DF62C627602EB1ULL, 0x919085926E8BC388ULL, 
            0x203530D6856B08FDULL, 0x75B07FD86E87CF4BULL, 0xC740BE557874ADADULL, 0x6CF906D2F245F805ULL, 
            0x0D87BF3AE5D68E9EULL, 0x94EC67FB03E74D05ULL, 0x190D632E9C578E14ULL, 0xF8BCEA0619CEBC67ULL, 
            0x999142DDBBFD9FBBULL, 0x7855690B8B66BE34ULL, 0xD3C73E95BB7324DBULL, 0xA36B4A7F9AEA36ECULL, 
            0x3E90C0939E9C3981ULL, 0x5C4A40691DB45D1AULL, 0xC47FA256AD8B5949ULL, 0xBDCDC1CBFD88B50DULL, 
            0x64E370E458A401BCULL, 0x24E588B6EEFAF0EFULL, 0xD9489507E5027D53ULL, 0x7BBDAE7DEC45026BULL, 
            0x31FBADF3A678522CULL, 0xFACD4D8D5B327BD1ULL, 0xCC51B6FFBCD4835AULL, 0x34970B2610700FFCULL
        },
        {
            0x5F1FD0203CF9B5F2ULL, 0xE481535690D69E7DULL, 0xE158B2982FCE32F7ULL, 0x7E5677EB24066FB2ULL, 
            0xAA725A556D647560ULL, 0x097166D1608CA30DULL, 0xC368864861B3CAE1ULL, 0xE037AAD5D5D6CD05ULL, 
            0xE4AF8DD452366C2DULL, 0x4E759B8927F61AFEULL, 0x773A99B991839806ULL, 0x02677B6D49AFE8FDULL, 
            0xB6C06FD691C9FB37ULL, 0xBB4FB0A616CB5F92ULL, 0x996862C595A50868ULL, 0x86F84E962B36A41BULL, 
            0x9AA7B6397914002FULL, 0x5D0C15E849905DA8ULL, 0xF8AC2B6921F48463ULL, 0x40A76FD1D1499B5BULL, 
            0x3DB01A7251E35203ULL, 0x31055BC0BAFAB226ULL, 0x96E5EE44D4F3FDFEULL, 0xA04268D8A888F5D8ULL, 
            0x2B7006181D4246F9ULL, 0xB982357552C9754CULL, 0x77FE03A62F00BE7AULL, 0x2388B6B6F2A0AFA3ULL, 
            0x3FAA778455D29422ULL, 0xEFB3D38481432D69ULL, 0x1C6735639E85F799ULL, 0x04A2EE1B5574906AULL
        },
        {
            0x6A94FD25FA82D312ULL, 0xD93042FD41F97946ULL, 0x31D3013987483067ULL, 0xC1F63DEDCD2D260BULL, 
            0xBD2B1A4466049FA2ULL, 0xA85C7F7897BA2039ULL, 0x38566AC7A6ECD1C7ULL, 0x1319CCA4FC287FA1ULL, 
            0x6EEC012C9876F3A8ULL, 0xC61CAFA01FC4AFDBULL, 0xF02FBDB3F63FB667ULL, 0x23D0B21310AAFE52ULL, 
            0xC37FF51EC3F3CAFFULL, 0x2474938B6ECABA9BULL, 0x82B04EB2EC62E72BULL, 0xF6971846DBB495EBULL, 
            0x7B825BEE900ED783ULL, 0x5F905D5FC3DD1979ULL, 0xF3450634B0E2995DULL, 0xB819282B0521CC3DULL, 
            0x8E32EFB804D8EF2EULL, 0xD48129B19609E9C6ULL, 0x97C51977527DD260ULL, 0x68E97121AEC4875EULL, 
            0xFFE8679A83BB7E9DULL, 0x8E084DCE96231573ULL, 0x5009430C2091FA40ULL, 0x5840EE920EFAB738ULL, 
            0x206F86CE1A0A7847ULL, 0xF8D5E64BC9433D81ULL, 0x7A862772899CDB8AULL, 0x03BD32ED247EFF63ULL
        },
        {
            0xB3C653AD9F2EE770ULL, 0x6B649FB4CC675604ULL, 0x86CC74320681DC3CULL, 0x4291EBF055795FA8ULL, 
            0x2072603ED7F0E439ULL, 0x1C5C26CE8567A788ULL, 0xE02B896CF5978977ULL, 0x54C519636F0EC59FULL, 
            0xDBDA3B1FFB0F9788ULL, 0x69C8B20E91960489ULL, 0x7A118683761A0379ULL, 0x0B3821744D4AF2EEULL, 
            0x7C54F0E6EDE35C8EULL, 0x8F4FC8C283F9834AULL, 0x2D885A029F94A338ULL, 0xC1008A6BB903A91EULL, 
            0xA41A7D1AA5448812ULL, 0x4D4A36F776EB7A10ULL, 0x9F3793D9E846D05DULL, 0x5138AB528C4C39F2ULL, 
            0x73BBE7E90833EB38ULL, 0x5555BC4E24CDEF1AULL, 0xAE752E872627F87EULL, 0x6A32A25BDED3679BULL, 
            0xA5CC27F00A0876BCULL, 0x316AFD4758508445ULL, 0x6A556AA1B6506670ULL, 0x713DF714E64C4D95ULL, 
            0x1F288758B47A1F8EULL, 0x04D74AEDF1D72C7DULL, 0x9F9B160B064A9276ULL, 0xDA22B03F2D1D3975ULL
        },
        {
            0x605AC5E6EE84F00EULL, 0x5F469B48FB938785ULL, 0x5EBE90BEEC9B17D5ULL, 0x09A84CE047BC8848ULL, 
            0xEC140BD867B1A402ULL, 0x789071C808D0ACE1ULL, 0x78A69DEFA4A3539DULL, 0x7A0041A223365FF1ULL, 
            0xF82EF62831CDC6A2ULL, 0x0E498336C76D587FULL, 0x20AEC46D39BAAC92ULL, 0xBDB5991126BC25F6ULL, 
            0xE8EC9F05620A7B43ULL, 0x5B79FF1116DC2330ULL, 0x98DBE743F2F322A6ULL, 0x6F8C0CAD9A3591A4ULL, 
            0x8D8C8923FE827229ULL, 0x26DE51D220CDF2A0ULL, 0x1647FA69086B9839ULL, 0x796F8DB485DFD684ULL, 
            0x91FDC828A2AFD6F1ULL, 0x380B6B236B356DEAULL, 0x66E31A0A36961EBFULL, 0x938DC7CCAF5FA7C9ULL, 
            0x1955876FF00C8CB7ULL, 0x22985D4876D340A5ULL, 0x3AAF39F4D60D1E76ULL, 0xFE21ED516D44CD97ULL, 
            0x4C7D1A394D9BEC96ULL, 0x2677E4B1F08427B3ULL, 0xDCCC7AB93C910DA1ULL, 0xE2C62F146AE5F8E0ULL
        },
        {
            0xEB905FEA9D8A423EULL, 0x862FF64EAE00BB62ULL, 0x5E093242E574D522ULL, 0xC51467CBD5626C33ULL, 
            0xD902D80A32FFAC83ULL, 0x98A1CB1E6464050EULL, 0x917A8B8AADF0FA64ULL, 0x2BA52D5A30E6D266ULL, 
            0x4DBDC0C48DD27B97ULL, 0x9EE8048C06E2DC4DULL, 0x757FAC240DA7AAB7ULL, 0xC56535D420D66C5BULL, 
            0xABE6572D050E1C68ULL, 0x8E9300E36A0E4EE5ULL, 0x20797C22927F3EE7ULL, 0x2CC31B0A4EF35E5DULL, 
            0x8952DC0852F8CFEAULL, 0x1F3C64CBD7BAC44CULL, 0x0F350A30601EAF50ULL, 0xBEC05D597C068E40ULL, 
            0xF635D2E1B9779CC6ULL, 0xC6ACBE301B7F8A55ULL, 0x7379C68EBF9C5154ULL, 0xD60C798804F862F2ULL, 
            0x4963E5CA0FABDC2BULL, 0xC5B84662B3E108C7ULL, 0xAD957B9E46EED460ULL, 0x1EDD4F6D7E1EAEE6ULL, 
            0x984FA06F4A9E446BULL, 0xED1DC07D9355853FULL, 0xD47EED640FEAE076ULL, 0xDDBC22AA6C1498C4ULL
        }
    },
    {
        {
            0x0AD26C48FDD7CAC1ULL, 0x8FED883A7C2162C1ULL, 0x7BE547294F25C14CULL, 0x6417970E133FA2FFULL, 
            0x0A32DF573D2C44D9ULL, 0x0827ACAECE9FA556ULL, 0x4D197DB6BD147413ULL, 0x206C4816F88300D7ULL, 
            0x7CA1506DA6913936ULL, 0x7BAB70F977EE7D09ULL, 0x4DD66C2166C02BC8ULL, 0xCEF899F90AAC86F4ULL, 
            0x2E0FE8B6F8F40242ULL, 0x783705064129466EULL, 0x0350DC8E40969221ULL, 0xD281A71E60C33B65ULL, 
            0xD83A1C81C11B3701ULL, 0x9A5DE9090A385BD4ULL, 0xE71AA9947295CBA7ULL, 0x2915B7F161A2FB23ULL, 
            0xB4C994DD3E52D878ULL, 0xD7CF959DEFD96AD6ULL, 0xAFB993C119126C03ULL, 0xBE388ACD1FD92527ULL, 
            0xE7C36535B7890E4DULL, 0x32E19FE19B49ACECULL, 0xE2DE7F312FDB2917ULL, 0x4DFD1D799F270805ULL, 
            0x9B8F73AFA36B4F8DULL, 0x8FDBD962AE7893A6ULL, 0x06DB5B8D9868E7CDULL, 0xC86C6BF34CE2537EULL
        },
        {
            0x4CC94EE6E631D0E2ULL, 0xCCBF44254AD94514ULL, 0x288235A152238887ULL, 0x2A36E7C4EE9E57C1ULL, 
            0x922E11FC8A535FE3ULL, 0x746EB0B40C87732AULL, 0x43856ABA162536B2ULL, 0xEB4F3C6BB58760C7ULL, 
            0x3BD5980DA5BC777DULL, 0x2C50967FB58F5CECULL, 0x6D4A8736C9A1B06AULL, 0x6A81ED3B1C33A23FULL, 
            0xA5FE16706211FB95ULL, 0x14B370BBC37A7FCEULL, 0x76E1474E4235B9C1ULL, 0xD70BAFFD3C824B67ULL, 
            0x6E7F540867EFE09AULL, 0x34CC2EB2696BED46ULL, 0xDE1927F5997D299BULL, 0x970571B586564DC9ULL, 
            0x81F49B44DC390F6DULL, 0x3A8557F7F28E6E83ULL, 0x76085D64CDC8AC4FULL, 0xF257FA6BA6EE0344ULL, 
            0x9C590B649F7E9037ULL, 0xA2C6DB59C9D79951ULL, 0x8C66713342192977ULL, 0x30D27CD9B29989EBULL, 
            0x606B309F31B27D47ULL, 0xECCCE6F8B12CF502ULL, 0x4E5EF34B77B5D574ULL, 0x639309E50348E51DULL
        },
        {
            0xC6F396ADFFD8A6D8ULL, 0x5848B2787C21C50EULL, 0x1847EE44384994B6ULL, 0x74AB398B512F36BFULL, 
            0x0366147120786187ULL, 0x5B65D6FBC2811AE3ULL, 0xF3B4C9FA8ADA891FULL, 0x010210146CF1A7A2ULL, 
            0x9B4A38B843BF4BEAULL, 0xB36089D04F8D85E2ULL, 0x05B347742EB5160DULL, 0x1609304E71D5E4E7ULL, 
            0x851BEE9E8E2705C5ULL, 0xAD6DF912D09F6F33ULL, 0xF92B954CB7F7A3B6ULL, 0x4D91E6F2CE2940D9ULL, 
            0x68BC58B166F98F73ULL, 0x404289D2915F1886ULL, 0x1753EAB840633E6CULL, 0x78AE5D45680ECA32ULL, 
            0x191C9231366C4ED9ULL, 0x2278177129B3532AULL, 0xB22469A15CE47728ULL, 0x284D7DDF48D234B9ULL, 
            0x981AED3756AE1832ULL, 0xE9FE754C3B14E64CULL, 0x7F6E73FD0CA237A1ULL, 0xEAA61FA1DB0265CDULL, 
            0x225AB097C8EC1A75ULL, 0x5BD70787D0CDADB2ULL, 0x24D4C368958CB0E7ULL, 0x854138D157459C1EULL
        },
        {
            0xC45E350263EDB3DAULL, 0x2EC8328223AF9450ULL, 0xEC3B98866E3CC3DDULL, 0xB352EDA763C345D5ULL, 
            0x34E2544D89F6EC48ULL, 0x295F19CE57D0A8E7ULL, 0xBFAC89EEC8A507CFULL, 0xA3E8B063FB8B400BULL, 
            0x50A1FD453F11CBF0ULL, 0x650CF03180AEF59AULL, 0xAC63681572D54D5FULL, 0x9765114E021C4B0AULL, 
            0x968F7ECF89FCA791ULL, 0xCC5841C231B26BEBULL, 0x7084678B98F64B05ULL, 0x72988BC3D442D234ULL, 
            0x614A40997175C683ULL, 0xF94511B3623FCCAFULL, 0x65E6CE00A4323B7DULL, 0xBC925284F4D172B7ULL, 
            0xEB1941F0BAB4891FULL, 0x9D06ECEFCC9B990BULL, 0x0A1FC828042F7C5BULL, 0xB9532FD424E5D5A2ULL, 
            0x122F19B9263E17E8ULL, 0x26C09E38C33A0398ULL, 0xE5E7FE2E5D8FBA17ULL, 0x85EB44E72F6484F7ULL, 
            0xDC11F90DA1F54C69ULL, 0x54FFC88D86D7E0B4ULL, 0x695E023998FBECF1ULL, 0x676F64D8FCAF3DE6ULL
        },
        {
            0x2F8C248EC1F17A19ULL, 0xFB0C6EBA18E90034ULL, 0x5218B0E14F175609ULL, 0x5D9EE35864F2F880ULL, 
            0xDF7743C1F0CA61BFULL, 0x322F0489D8418112ULL, 0x9F4795AD31754A87ULL, 0xC6931571AA829AAFULL, 
            0xA01346ACE1E49916ULL, 0x9536B827A8625FEAULL, 0xF22AC0DEA751D028ULL, 0x3C5095794C62FE0EULL, 
            0x63150491A1EB97CAULL, 0x32F6799A55CCE8FFULL, 0x9B4D94AA401EE09AULL, 0x54A21106EBC7C445ULL, 
            0xD480FF0DFB61885EULL, 0x596B352973928712ULL, 0xCF2B72465838B56FULL, 0xBE5F8A887D67DC9FULL, 
            0x5A64770A81DD5018ULL, 0x99135FEB9E520CF2ULL, 0x213EFBF5E828C2BDULL, 0x09426256005D00CAULL, 
            0x5CC3180846764143ULL, 0x9DAC52F7DFDF2442ULL, 0x3CEF024D529804ACULL, 0x5F7E5E920CAE3766ULL, 
            0x0E994C02810B2619ULL, 0xB8611A8E820B6FDCULL, 0x377420D0E042C035ULL, 0x6E41E73FEAEAD031ULL
        },
        {
            0x3E64776B1642E1E4ULL, 0x6C399DFA53FF8A0BULL, 0xF24A92860D2BC7E1ULL, 0xD3D9147AD2AFDBC8ULL, 
            0xB44E20716C1BF0B3ULL, 0x8290EF3D10C3CF8CULL, 0xB8E0CE031AD70E1CULL, 0x294AC0D3F5B02BA7ULL, 
            0x20720430E522DED2ULL, 0x8CD2F1EED0CEE69EULL, 0xD45773697D2A6A8DULL, 0x56252D510ECFA15AULL, 
            0x8700A4198846A775ULL, 0xDBCB6EC886F4E855ULL, 0x9BEC5BAFDD5BEDD0ULL, 0x329853C4BACAD82EULL, 
            0x8B25D2D5143EDE60ULL, 0xDE57622ADDA1A83CULL, 0x791F5B7B7CB5DB99ULL, 0xE8CE598AA9B25C45ULL, 
            0xE81045471E297C90ULL, 0x992575689A5DFC56ULL, 0x3C80B8867718040EULL, 0x6ECF88954D860251ULL, 
            0xC740A743A228C054ULL, 0x7A418782BFCABD6DULL, 0x443BE8545CD14544ULL, 0xCEB65B7C91AEA2CAULL, 
            0x4B30A889C6C40AFCULL, 0x16F840F07B54E19EULL, 0x58D1D00BE88835D4ULL, 0x658523714F4C6131ULL
        }
    },
    {
        {
            0x80A1A372F69E1477ULL, 0x62A1D6EFA1C039FDULL, 0x6439C369086E00EBULL, 0x27078837705C378AULL, 
            0xDB834C9E94B04666ULL, 0xB08926BB1AC7594AULL, 0x3DC19E5063C2E6B5ULL, 0x7636EAC4520204D3ULL, 
            0x4C98C23833BBB18DULL, 0x866FF5D870910E82ULL, 0x6E2B8C5AAC557EDEULL, 0xA437AD43CA1165A5ULL, 
            0x81C99898C013C2A4ULL, 0x202362C35D079B2CULL, 0x01973CC97EC144C9ULL, 0x886203A7659262D3ULL, 
            0x96EFAD3EFBE699DBULL, 0x80A6F02D3DB6A111ULL, 0x46486120FE33B025ULL, 0x614A2DB8EFCF66FCULL, 
            0x819A9549F80F9E24ULL, 0x99110B0ECCA39521ULL, 0xCE2A6F0949391E1FULL, 0xAA3B0557AE90C050ULL, 
            0x8CFDE93697608C72ULL, 0xF4B3D78AADB0BA7CULL, 0x4894D359B0D9EF6FULL, 0x7E65BCF160EC22ADULL, 
            0x9B3D3AA51F934D47ULL, 0x87871C07C003A7D9ULL, 0x8E7DF2178CCDC6A5ULL, 0x75CBB55A570C0BEDULL
        },
        {
            0x8709F63AC0917474ULL, 0x63A571E8C065C407ULL, 0xE35B8AA4E7158F5EULL, 0x3B6BF483848E4778ULL, 
            0x8A557C529F11438CULL, 0xBB3979FE78EDFE25ULL, 0x3ADCD534B63BAE7FULL, 0x943FE32188FAB241ULL, 
            0x694F62C47919D874ULL, 0x5350B1FD121E0834ULL, 0xBE8597C7FAFB7547ULL, 0xEFE1F4941074D720ULL, 
            0x82D653B6D90056C4ULL, 0x2110479C2918D56EULL, 0x7B66C486382686AEULL, 0x53AA14227ED3E86CULL, 
            0xC4A450D4A7434ACBULL, 0x119F995FAB74122CULL, 0x9B302D26DB0EBB66ULL, 0x4325C61B5D5183A2ULL, 
            0x4F84EED831BA34E7ULL, 0x3BE375EBA13D4ED5ULL, 0x0390ABB32229BDEEULL, 0x43EDB2C317EC72AAULL, 
            0xBA90BA6FBE9DB157ULL, 0x07A856CA06666594ULL, 0xAE6C74603032CDE2ULL, 0x5400CC3D472FF26AULL, 
            0x9BEB7CFDCEED5F7DULL, 0xDCD89A8BE43699FFULL, 0x1EB0CF618905C5A1ULL, 0x3119F6194764B8D0ULL
        },
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
            0x6E8B7AF09F8E1B80ULL, 0xE879F4304FCBE210ULL, 0x5D0109DC7493B5DEULL, 0x693FFE834341CF9BULL, 
            0xD9F50C64B82EE536ULL, 0x40F1B64413ED2EF0ULL, 0xCDB0CE9437D06BEBULL, 0x3316B47A2D139F9DULL, 
            0xE7474A7B3B67B96EULL, 0xE6FD6263D8544E25ULL, 0x58D095B89A5F14F5ULL, 0x5B706DEE19CF9138ULL, 
            0xF6981D4F0714844CULL, 0x4C179761E3B0534BULL, 0x25C230B9E9ABB235ULL, 0xD2DD5AF66B8C9173ULL, 
            0xA827EE2F9E7E0551ULL, 0xFAAF3265C6365B78ULL, 0x68D789A7D9495513ULL, 0x16177A7D5ADA66E9ULL, 
            0x37793F2204EC5F54ULL, 0xAAB704D01E20F54AULL, 0x3C7F928D1190C215ULL, 0x221038CF0449F808ULL, 
            0xB0FEBBF99DD0C21BULL, 0x6CA0ACF5A7C30E98ULL, 0x7AEB11F73614B6FEULL, 0xF47819C857B4D61CULL, 
            0xFDE3BDEA174A09C5ULL, 0xB6440D6ABB998A0EULL, 0xDE8C7D44178F85D8ULL, 0x7FDDBA308BD015F8ULL
        },
        {
            0x3B785E583B638DF9ULL, 0x1E3D639703028213ULL, 0x44618B05F33764D4ULL, 0x85463BA98091CE65ULL, 
            0x1C2C4983FEBCA7F9ULL, 0xD5B713413F72CA43ULL, 0xD59A16473EF01C83ULL, 0xE020F0DD7D8F2A02ULL, 
            0x56EBA75FBAC43DE4ULL, 0xCADEE51D72ECD3D2ULL, 0x187D3395BE536FA4ULL, 0xC89913C79DC04A5BULL, 
            0x6BA0142C31DA6C7DULL, 0xFBE5A8C2E917B9B7ULL, 0xD3569BC003637296ULL, 0x8D1626F5A46E21B4ULL, 
            0xD0A960CDD483786BULL, 0x89BAB04243AF95D8ULL, 0x0A61467C7E3C2CCEULL, 0x8C1E959C34C03EA2ULL, 
            0x1BA954A0F3F0B4B2ULL, 0x44790583113C3195ULL, 0x49B706F6A9B1D6AEULL, 0x5214E568ECB3BF8DULL, 
            0x09187238F72C5FC9ULL, 0x7821853150787390ULL, 0x528C55ECCBD2A82EULL, 0x0F22A0FAF038BFF1ULL, 
            0x864B48C57194740BULL, 0xCB84780D6DED15AFULL, 0xAC922841D5430F8CULL, 0xC6024357C24D1C55ULL
        },
        {
            0x456D071942CA6AA1ULL, 0xFA10CEFB7DFA7DFBULL, 0xFA0058FE12F5B3BFULL, 0x9E2267F675BE2EB4ULL, 
            0x72FCFE8EF55375E5ULL, 0xC93FFB0FF431FC24ULL, 0x394FF170B6EF4379ULL, 0xADEAFF1936C8F6B1ULL, 
            0xD4E6A2AF33572DBDULL, 0xDC738FB682496A95ULL, 0xDF98F1359710FF13ULL, 0x994D6FAB5A16D0F0ULL, 
            0xD079758A1B7951FDULL, 0xF4AE069BBD0D228CULL, 0x37B18D3418F69773ULL, 0xB89772B54F392E72ULL, 
            0x3AC467FC3D567ECBULL, 0xAE815AC32575DB3EULL, 0xE7A991F8704CE209ULL, 0x06A10E0252CB0C57ULL, 
            0x5A701E5306B75EBDULL, 0xDB8FA3428283F1FBULL, 0x9F3FE465BB270F43ULL, 0x08754EDD329739D1ULL, 
            0x7E4C3904B0373307ULL, 0x0E497805FCD1538BULL, 0xB404331926D9C23CULL, 0x6ECAD8D4842B501BULL, 
            0x0BC17D269468800EULL, 0x10027C928F8FC716ULL, 0x8448F10C387ABCA0ULL, 0x503D28319F113997ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseEConstants = {
    0xAF92AF1FFA201234ULL,
    0x16267769020E17A8ULL,
    0x9E617EA018AB4900ULL,
    0xAF92AF1FFA201234ULL,
    0x16267769020E17A8ULL,
    0x9E617EA018AB4900ULL,
    0x4C21DF11DEAE90E5ULL,
    0x57BD8C5FBF9C7F94ULL,
    0x95,
    0xC6,
    0x89,
    0x32,
    0x5F,
    0xC5,
    0xA1,
    0x74
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseFSalts = {
    {
        {
            0x23731A584B3FE77FULL, 0x2DBF4EDF4626B64BULL, 0x552F497253CFB47BULL, 0x6E927C0FE42471E5ULL, 
            0x74EC706BF6B0E499ULL, 0x9F14C9DE682D18D1ULL, 0x5A591785B3E09EFFULL, 0xA42FBF18DC02A551ULL, 
            0x99D22520DDA05035ULL, 0xB1ABC7ACDBCDFDC4ULL, 0x00F78110820F0124ULL, 0x24500B0E6BE149D8ULL, 
            0x03E60FA723211328ULL, 0xE868567AA208F514ULL, 0x2154CEEA0A848A8BULL, 0xAC7C776DBFFA552AULL, 
            0xDD6BE6DA59A285D2ULL, 0x1DEFBD246BB8C400ULL, 0xA88E9E51FF704B16ULL, 0xE9712D06D0A92043ULL, 
            0x265DC875F610F617ULL, 0xE521D17FBDC37FF0ULL, 0xC3F3BCBA2B4EEA59ULL, 0x4857018D89BC5CEDULL, 
            0xA36163F13B1ED184ULL, 0x0AB121C3FFC5451DULL, 0xE6FBB2394C767F1BULL, 0x61C95643DCFF4889ULL, 
            0x597C1AAC6DD0D46FULL, 0x31538BA89E23D0F8ULL, 0x4F9BA4716BBDA817ULL, 0x74A36FFB46A37019ULL
        },
        {
            0x81E3EC518193407BULL, 0x3A6C7ADD9D34FEE0ULL, 0x8F8EDF1D954BC2B7ULL, 0x1015491A326A0AC7ULL, 
            0x068C854879107579ULL, 0x1C4E54F0F4B09785ULL, 0x7FBF9F18F4773026ULL, 0xB571484A7A8D1EF5ULL, 
            0xB16874419D50BCE6ULL, 0x9C204D9D8B7697A8ULL, 0x03AAD456479AD724ULL, 0x1D441F5CF2C9B01EULL, 
            0xE8527060F68B2212ULL, 0xD6B72D017885B99DULL, 0x1DB6434A4F781B20ULL, 0x4193428ACCBD8514ULL, 
            0x4475005A0F490FB2ULL, 0x4C36D2AAF9358174ULL, 0x8459C48E5CC3D375ULL, 0xA16F98F5E7C2A135ULL, 
            0x0B3387053D517C17ULL, 0xC5CF928B1AAC8CFCULL, 0x718743633D499D92ULL, 0xE9FFC0FD4D532A0AULL, 
            0x7A5C00EEFB3DD22CULL, 0x512F9E02BA6C908FULL, 0xF1FB2489E608AC81ULL, 0x5533EFC7FBC7D365ULL, 
            0xEAC9C9EA65FC75DDULL, 0x02A2CACABF4F1D4BULL, 0x5B3FC999F4056DADULL, 0xC78EFB0B833F22A2ULL
        },
        {
            0xC39DBD913CA6715BULL, 0x91B539DDF37F724AULL, 0x28FC4201F4064FACULL, 0xF7FE159AC0F12D2EULL, 
            0x50A2CBE018524814ULL, 0x19CB495DE0617FB8ULL, 0xFF279793A1EF90FFULL, 0x9CC8309F7A3A2982ULL, 
            0x517BA1968A91BC8CULL, 0x6EEED7055818F836ULL, 0x1D80CC0BBB2836C3ULL, 0xC4E976544F8B7849ULL, 
            0x54426AE43E338B5FULL, 0xF53458901F16B3E6ULL, 0xBB74E33DE83AE34EULL, 0x6D7ADC2721ADFAB1ULL, 
            0x27BF04340B338C0CULL, 0x7666EEF3A4998A04ULL, 0xE11EB809C29A0298ULL, 0x2CB8A9B31AD12624ULL, 
            0x9C526512E4EBA7E6ULL, 0x03BB66E7D6F6F6DDULL, 0xC62B2A463692287AULL, 0x8366FF893F9C37A5ULL, 
            0x8F50AB5E088F514CULL, 0x46A3F9FFDD43756BULL, 0x028F9303FA7EC576ULL, 0xA70766BE87A30139ULL, 
            0xCC5B4CCCE7D8476BULL, 0xEE2E3B00145ACA92ULL, 0x15ABCE44D753E6A4ULL, 0x25C7A84BB0B7F2E8ULL
        },
        {
            0x063FFA979D258ACAULL, 0xF63DD229584C9B6DULL, 0xAE6732272F08EA86ULL, 0x9E2B39B41D25817CULL, 
            0x074BB0C28D0257D0ULL, 0x817EB59ED15873E0ULL, 0x3DB2ECBA7F7EE75EULL, 0xBD55A2090209791DULL, 
            0xEC02DF1467A9E5E1ULL, 0x7786D16B438CE0B0ULL, 0x58B861DE4044672CULL, 0xEB89C699D4AD4DE2ULL, 
            0x3EB5722C83E1A132ULL, 0xD16B628648B3A6B2ULL, 0xF5201A3D4FEAD998ULL, 0x4E409EA75BC25BBAULL, 
            0x30A6948DF5CE2F6EULL, 0x14D6596444DF775BULL, 0xA546C26BE12E6593ULL, 0x2D0B94DB53D23A16ULL, 
            0xBAFD8A28A4238AD1ULL, 0x87BE9C80BF89F75EULL, 0xCDA4D98A41361D5FULL, 0x5900F0C3C83BFCBAULL, 
            0xD0280FA26459B443ULL, 0x2ECE66AB82A43C93ULL, 0x5796AD7B0B6F73CCULL, 0x8B0E31F9257827F1ULL, 
            0xB3BA02E5F539E1A0ULL, 0x4EAA40989838A73CULL, 0x960C073202413F20ULL, 0xE8159D65FD09D7A0ULL
        },
        {
            0x24D8E3815BBAA06BULL, 0xAF55334F9FD2A94EULL, 0x836131E5EE6DCCB1ULL, 0x47C8A35375EA9EACULL, 
            0xC953B0F2DF0109C0ULL, 0x29A0261106912B7EULL, 0x900479CD1C0E8666ULL, 0xC5E70706266E3E45ULL, 
            0x2C27F64F0A39843CULL, 0xF26F122B3BEFBDC9ULL, 0xF78F1B5DBDFA84DDULL, 0x8E6EFFD9B34BBEC8ULL, 
            0x62B76587E576A914ULL, 0xF13768461DD872B0ULL, 0x6DBE5EB7B0D3D15DULL, 0x1F72D0A21406F487ULL, 
            0xEB1367DD1FC21524ULL, 0x3049DBE7FBF69E6AULL, 0x8087D8D54684858AULL, 0xDADC9A7BA4354A81ULL, 
            0x1903B227B638F9F4ULL, 0x3815FF30453617E5ULL, 0xCC1A25AC28B28C49ULL, 0x82807E3EECDFA4A2ULL, 
            0xADED245C6260C3EDULL, 0xF178373C9A1B04DCULL, 0x632835B52477B4CBULL, 0x17D4DDD5C43E0B35ULL, 
            0xA8A0CE5481182261ULL, 0xA30279D1E7D5671BULL, 0xEC04E23743DED164ULL, 0x7DF74663E8BA7D60ULL
        },
        {
            0xE912B38049F6DEC0ULL, 0x3BE67A4E4624AEF8ULL, 0x1ACEB60774802E9FULL, 0x4F24F4F461C37270ULL, 
            0x735EEF7B93FB9584ULL, 0xE40C98114014232BULL, 0xB2AD5860B46803C9ULL, 0xF19C7DAAA34B2A34ULL, 
            0x3B38D83C93C1A324ULL, 0x1FEC76B67D16F2B6ULL, 0x3D86BEB504F59B15ULL, 0xA3545D923E7217A2ULL, 
            0x3C50F09602125BC9ULL, 0xBB1CA629D9DF0304ULL, 0xA3952D9021FDC096ULL, 0xA0DC5BA975A736D2ULL, 
            0xD5FF1FC6F9E3D3E3ULL, 0xE11A07629992F3EEULL, 0x453A3331C6BDDD11ULL, 0x6371CCD2AC45A6ECULL, 
            0x7FC1AC64567688BFULL, 0x4C8840ABC5C642E7ULL, 0x2F783B6DB21DD295ULL, 0x5F52FA02D4507499ULL, 
            0x9F975C1F43013454ULL, 0x9E9DED8C8D001649ULL, 0x2757FC5CF3B921FEULL, 0x33DF16FBFB109F6DULL, 
            0xCBB224718E73C6A5ULL, 0xFECF95B3466ED750ULL, 0x6A17F5BDDED514DCULL, 0x39729F4E3644C41AULL
        }
    },
    {
        {
            0x1F36A1FADBB21D86ULL, 0x0EB6FDCDE9D5242BULL, 0x897A72E0E75FA5E2ULL, 0x58A9D4BD5658A48CULL, 
            0xBC32AC1B25DE82FCULL, 0x09C08ED70B1FB247ULL, 0xEF5FDD45BDF93F9BULL, 0x463E28A7EF85CFB8ULL, 
            0x6C192790226B3119ULL, 0x9C9AFD2186E3D4C4ULL, 0xA55881D71D0934E9ULL, 0x2AC02ABEBC9E1FB2ULL, 
            0x565655A6277D6C0EULL, 0xAE05DAA95E427F63ULL, 0x5A2DF83E8C66A735ULL, 0xA42FAB1FD18037CFULL, 
            0x2883DBB383158E6DULL, 0x24F8AEB70778059BULL, 0x6414B54F5BFE1AD3ULL, 0xDB4B6772FE9BB1CEULL, 
            0x39CF97FBCE2073A2ULL, 0x5481696B967E5B19ULL, 0x93885310EF914219ULL, 0x5F29CB8CF2918466ULL, 
            0xCAC4400CB219D78EULL, 0xC06D9EDD7D3DE57AULL, 0x3E36958B4DA33525ULL, 0xED10DE63EFC35938ULL, 
            0x74E5D2BAF142EF3CULL, 0x1E49C3642FF5BB14ULL, 0x724EB7B66D76DBF0ULL, 0xB3B43E394CDF5983ULL
        },
        {
            0xB12F6BAFD7B9B059ULL, 0x81077A29C3B4FDB6ULL, 0x8B25E8D81FEF4685ULL, 0x38A735F8543A82D0ULL, 
            0x84E819EFF811C051ULL, 0xF9BF0A6FD902CFBDULL, 0x9E523EFCF18EE8E0ULL, 0x52736588641E09FEULL, 
            0x053186893C5E5FECULL, 0x6F2BCCE73D789D22ULL, 0x355D1C8E556F074AULL, 0x9DD85463CE46D7D9ULL, 
            0x15FD62F932C53F4FULL, 0x8E402784ABC4BDD7ULL, 0x73B546AF343CCE28ULL, 0x5ADDB5F0A01A2900ULL, 
            0x7CE1537FD6100087ULL, 0xAA804B2B7DD23F15ULL, 0x94122AB501C91645ULL, 0x088DF8FE1042D239ULL, 
            0x2C560013EC42D9ABULL, 0x2B23439A6897E458ULL, 0xF30E717BA3ED5B64ULL, 0x9D9C4DF1F30A9329ULL, 
            0x6969C1CFD8BC3D54ULL, 0x91536F79CB399C83ULL, 0x733958BCF5D812B8ULL, 0x26C8EFBC8B9E1978ULL, 
            0x3A82143D1BB1BCF9ULL, 0xE6209DCFB2B37DF2ULL, 0xBC4AC6811D9B4521ULL, 0x373B5C019FADCB44ULL
        },
        {
            0x5EFF69B4AC901C6DULL, 0x7D3C3D62FA07505FULL, 0x69AA9883A919D247ULL, 0x26730D5076806080ULL, 
            0x7645F4B2076D7381ULL, 0xAE7FA5CDE716D369ULL, 0xB11828EAA4E3162DULL, 0xA43C9CDEC8B39064ULL, 
            0x7A5E8B198CCC70DCULL, 0x2F2B8A6DB07F8F02ULL, 0x75C258D57396C7EEULL, 0x5024866D5C812549ULL, 
            0xBF5F32B60DD9C6FAULL, 0xBEF4B48F80E4D132ULL, 0x13F09084614BCF43ULL, 0x0F1E3EE60CD5ABA5ULL, 
            0xC961B2B0B562DCCFULL, 0x889097ADBD3D8036ULL, 0x81C84DDC16EF025AULL, 0xE22BF162DBF6E2A4ULL, 
            0xFD6C7E7681A41118ULL, 0x792407495FAE391DULL, 0xFC076942521AE14EULL, 0x0209DF4CEBDF2797ULL, 
            0x064CD730F8C793C3ULL, 0xF5D7F2D2C5CCC2ECULL, 0xC76330DA4AF7B370ULL, 0x193C1812A2AD0A18ULL, 
            0x0149D464FA5D9599ULL, 0xD584BAE89FED28C2ULL, 0x23333716634583B0ULL, 0x106285D07764DB07ULL
        },
        {
            0x8A0CBC063537D712ULL, 0x93846C676C64A2BCULL, 0x2263414740976BA5ULL, 0xADA350CEC971ED9EULL, 
            0x94B1C29E50FE3A29ULL, 0xDC1BE8B9A3EB8E5BULL, 0x46A02B28BE2239FBULL, 0xA12902F152012659ULL, 
            0xCA67203B39D44533ULL, 0x899CED4A2522916AULL, 0x224BBE56383165CBULL, 0xCF9159C41A32A924ULL, 
            0x932465705392E291ULL, 0x2E42A584755BA667ULL, 0xF3FDBCEE356BB489ULL, 0x1F75DC87B27770A2ULL, 
            0x7963166B698D874FULL, 0x40D69F58EBEE1275ULL, 0x0729D7B28E7A44C5ULL, 0xE8D5605699492A3EULL, 
            0xE22DCA9D05A2BD02ULL, 0xB7DF400A9117F295ULL, 0x86257078242C2BF4ULL, 0x5ADCC4070FFF6A8AULL, 
            0x1FCD5D791A33DD92ULL, 0x6309B4E4B22D2704ULL, 0x00EA6F11389FC3F7ULL, 0xC525084599200424ULL, 
            0x3CEAF81FD327341AULL, 0x3168E6706A9EF6DFULL, 0x6694228A643B04EAULL, 0xBB7F4F4145A38241ULL
        },
        {
            0x8686A0231D9564FEULL, 0xC0882C26BB7298B3ULL, 0x04F8F1B3C1AE2641ULL, 0x29A7E0505A17AF35ULL, 
            0x069D2F18AE0C4787ULL, 0xB988CF535D690F2CULL, 0x6A6949B21CD117C7ULL, 0xB7FB650D56E91925ULL, 
            0x917345C5E7F381BEULL, 0x53E1B3741161AB1CULL, 0x16DB50C475789A01ULL, 0xE71D5A37BB9EF9B6ULL, 
            0x8E3804612099FD87ULL, 0xC0416B875BAC0876ULL, 0x6577B0BB76781F9CULL, 0xA8598C7CD85DAB3FULL, 
            0x5BA15BC094ACF9DAULL, 0xBE93BD73D81E9F63ULL, 0x80E571D37374B26DULL, 0x7D1781743FA3EC71ULL, 
            0x27CA0A49B0E03C89ULL, 0xC2BD866FA6C48F41ULL, 0x52C9D38B905E614BULL, 0xA93D000D18A03AC7ULL, 
            0x57C8B082587BD4A3ULL, 0x4F54AB4A747AD91AULL, 0x147B1DBEB21E2D77ULL, 0x2EB7DD8E6E1C5219ULL, 
            0x6A50219E6DCD1756ULL, 0x0ECF1223722F96C0ULL, 0x6D10426C4F7C7681ULL, 0x7D09767513951ED7ULL
        },
        {
            0x8CC6CC5005E7FD69ULL, 0xCD4BF0017A4B6283ULL, 0x188078D7F66169F1ULL, 0xC9E5251F19FB6B3AULL, 
            0xA43BF21B941296D3ULL, 0x30657F2365C55DE7ULL, 0x488465214031F70CULL, 0x5AC60730DE5B8FFFULL, 
            0x11AED49897FD154AULL, 0x4A5490D8083AE4F5ULL, 0xD7E5D668BF448245ULL, 0xAEEF5657493F174BULL, 
            0x58DE63139A83552CULL, 0xF5F4919266B9BB42ULL, 0x7DAAD38410A74F6EULL, 0xB6B1C71420CB2A2CULL, 
            0x1CF4DBCF4E7E6460ULL, 0x44C37137D403816BULL, 0xCC374A26BC70408BULL, 0xFCA62E59E2789CDEULL, 
            0x3E9FAEEF1286892CULL, 0xB265E8AEC705BA32ULL, 0x7AFD333206D0B8DCULL, 0xB658BC5BAAB98B9DULL, 
            0x8DB8EBCBE19C9D5CULL, 0xAFE3670E938C8465ULL, 0x0AAF8F3795312781ULL, 0xF1D0A93CEDEFFEDFULL, 
            0x0B9A3ABCC99D1AFBULL, 0x144D5EFA4CD37C5BULL, 0x5650E3FAEB489140ULL, 0xB0AA2F88A8C1124EULL
        }
    },
    {
        {
            0x06A61568EA961E57ULL, 0x17AE98A1A8086977ULL, 0xD9A53A8BF881984EULL, 0xFFCC6C7B271D1089ULL, 
            0xF48F09CB825D14BEULL, 0x2F7B687175D48B3CULL, 0x96DFF8C9FD33F717ULL, 0x318F78A045A88561ULL, 
            0xDE2E7DBCFD4C245BULL, 0x505B0D658A3391D1ULL, 0xA109A2D0EF66AA13ULL, 0x7ABE3D4D3529684EULL, 
            0x060D7044B36CF87CULL, 0xE0623DAB0AE2C8A0ULL, 0xEC4905D523908DC7ULL, 0xEA876E693699313BULL, 
            0x8FD4674AF05F08F7ULL, 0x80261CEA09C07247ULL, 0xB2DB206AC1FB0398ULL, 0x219F08119537E11CULL, 
            0xA36C59084D46FED5ULL, 0x1F8B9E4D89B57A8DULL, 0x2FEFDBC0BAF32C68ULL, 0x2100320DCE04C085ULL, 
            0x3070BCB0218C3380ULL, 0xBD65128C59CF5400ULL, 0xDAAF36CE77B363E2ULL, 0x30EE8205012A8A4DULL, 
            0x66DB80D09F4AFA23ULL, 0xC9E48FD3D9D9D427ULL, 0x1916F9441FB46EF6ULL, 0xF3D665F1C82A6138ULL
        },
        {
            0xB5FE7A252BD732FBULL, 0xFB723F7404219F77ULL, 0x507B91509F55BA0AULL, 0x26CF9D1A36E88FA0ULL, 
            0x80431CACC33B974BULL, 0xE05A11F93A99EE44ULL, 0x0B4406FB05A1DB69ULL, 0xAB1D9B38FE44B9A6ULL, 
            0x854A8DE278D626C1ULL, 0x4E4A28AC35686DF7ULL, 0x46204EEE5B81DA80ULL, 0xAEDA97B413BDCD8FULL, 
            0x43E187C02B627D7BULL, 0x5E54FA976268CAF7ULL, 0x8811004DE11A82B2ULL, 0xB14A2A776C559A9CULL, 
            0x56CDF72F954004D1ULL, 0x809C2F017A75890EULL, 0x11DF3B97031B4BE2ULL, 0xEBA9438024DF5998ULL, 
            0x0CD668673E70141CULL, 0xEFB00F59F91A34FEULL, 0x8D1939E7ADE229FEULL, 0x4EBC28ED36D21D55ULL, 
            0xCE934EB224682D84ULL, 0x7085322F6663E9CEULL, 0x8C3BF2F6A6B09D8FULL, 0x87F200AC9CAC20B9ULL, 
            0xCECE04D0405E788CULL, 0xCAD0C7C945427B49ULL, 0xDE0F622600470348ULL, 0x415E675F0EC4575AULL
        },
        {
            0x6DB743B3E4767104ULL, 0x0C504394F134018CULL, 0xBC4759A78D62DE62ULL, 0x42C1986BD1C8BF09ULL, 
            0x300DD49CF42E0610ULL, 0x07FD0BE4A6B997B9ULL, 0x6B42628C47E7A175ULL, 0x9CB7840AB72A38D7ULL, 
            0x65AE7D59488BD343ULL, 0x5A9E86F1D73AD0B3ULL, 0x92EB78A882BAACC5ULL, 0xACC95B188FCE6981ULL, 
            0x0AC4B22355E20D44ULL, 0xE4A637B64B20DD62ULL, 0x64C2E6FF7381877FULL, 0xC17E47127F69790CULL, 
            0x1FC5A4714BFE7E22ULL, 0xA4CD81A8C8C4231DULL, 0xB6F2C0F7B737ABD3ULL, 0xFC9E49E4FC5B549BULL, 
            0x29C4F37C0B736ED0ULL, 0x3769F5950C50EA0FULL, 0x3929AFFB02E56F72ULL, 0x1042615245E237E8ULL, 
            0xAB7ED6F43F65C710ULL, 0xABEBE58C3FD89A88ULL, 0x88C3D655BEF72AD9ULL, 0x4CB4196673C2139DULL, 
            0x1FD3C18304DE9F2DULL, 0x94E4DD059108CC9CULL, 0x5CE9D0E1FD8078E0ULL, 0x1837A71D860B0D40ULL
        },
        {
            0x2DB30984BDD6D8E0ULL, 0xD9F7623C8CE94E2DULL, 0x1A9C9D9E3D2BAFBAULL, 0x398089F03FB4C162ULL, 
            0x350BC14F9210193BULL, 0x85FEB4EEE7F3139EULL, 0xC26CF47218B3E601ULL, 0x2E80F836F5B4ADD7ULL, 
            0x9A1D530B26E90711ULL, 0x3B07F8977548585CULL, 0xF3B6E0F66B138369ULL, 0x4409EF6408775A9AULL, 
            0xE3DF0AF2A16FCF17ULL, 0xAF9E4DAC76D3808AULL, 0x3A6C9BCC14216540ULL, 0x806BE109BE889E4EULL, 
            0xCF60D23E511C9760ULL, 0x0AE8493E79FB40F5ULL, 0x0019312F8B680E03ULL, 0x5CC94060C734AA07ULL, 
            0x7ADF46FEED15E566ULL, 0xFD1FCC2CF5305578ULL, 0xE2A00C1F49357D47ULL, 0x8C8C0CFFDDD22714ULL, 
            0x2451431351FD8BA2ULL, 0x3A3633FD005DB5A4ULL, 0xD6C7A1A54F7E961DULL, 0xD63A518CF5A74B62ULL, 
            0x5CF7379CF2C098A3ULL, 0xFE3FDBA3A4E02420ULL, 0x05A2291B09186E9DULL, 0x73CD9C925903220DULL
        },
        {
            0x5EC4A267172984B1ULL, 0xFBD9A23E3281DE72ULL, 0xBCFABBBD0F3DE515ULL, 0x7B1FC77D94FDA6DFULL, 
            0xA186A40F97B563F4ULL, 0x8D42ACEA2250C34BULL, 0x43A8654B449127D8ULL, 0xBF8424136487A051ULL, 
            0x0C9C15BFAFE2E9ADULL, 0x887A1799AA338D2EULL, 0x97A95E4707B0DA47ULL, 0xB472C6974D68BC33ULL, 
            0x599FD8F61987EBFAULL, 0xDFEAB8FC94C54B49ULL, 0xEEB17D6C2E1C0323ULL, 0x68325CCAC45D9AAAULL, 
            0x7A1FC142BDF72C92ULL, 0x98CD81B1745E382DULL, 0x19BA43A1FA9C9A7AULL, 0xF3839BEB54611558ULL, 
            0xFF673236C74A4DC4ULL, 0xB1AC69480C096F73ULL, 0x52416389F15EB761ULL, 0x06EAD1E53873E31BULL, 
            0x3D65717F06BE44EEULL, 0x8AEE6A1C55B7258AULL, 0x8654D4B7317DE0DAULL, 0xA9D0A2A74B631EEBULL, 
            0xACE952EA31BF2AF1ULL, 0x40D5F59A32B24099ULL, 0xE79F9393A564E57BULL, 0x53CBCD8857617F0FULL
        },
        {
            0x89A0153382CE0BECULL, 0x0090AEBD97B0C507ULL, 0xE0881D552002DBD4ULL, 0x08549BF2881DE94FULL, 
            0x2A754BBD797A7B58ULL, 0xDD24A18CA20C2782ULL, 0x1BB98D9E67EE5872ULL, 0xBCA0996EF5DEEB24ULL, 
            0x3E32B8B01F92B890ULL, 0x888AFE13F84B09A4ULL, 0x858A772F8ECBFA2EULL, 0x2567C2A75AF712AFULL, 
            0xFAB5D083FEEEE2DDULL, 0xEB1365DC41CCE66AULL, 0xBC597AFD7D519371ULL, 0x37FA30FC14EF429AULL, 
            0xEF0D36EE21948B23ULL, 0x5B5C33744A5553C9ULL, 0x2D6ED92A0BD8FA7CULL, 0xC7C24D43D5F0C8FAULL, 
            0x9BDA7CDB61580319ULL, 0x6425349360287DECULL, 0xABBE5E01F3EF3CB4ULL, 0x5FD9F93571CF3977ULL, 
            0xFB110E5446405308ULL, 0x53BC3EE41C9EA135ULL, 0x0E7459A905906366ULL, 0x3DF8276A7F8A52B9ULL, 
            0x9D88FC7F0DCEC36FULL, 0x29C549399147B137ULL, 0x6E1D0685677A879CULL, 0x201FF7CF61694100ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseFConstants = {
    0xF1FF0DACD8795D86ULL,
    0xC1BF949EF26E2290ULL,
    0xEAAB1A7D05449460ULL,
    0xF1FF0DACD8795D86ULL,
    0xC1BF949EF26E2290ULL,
    0xEAAB1A7D05449460ULL,
    0xDBC94283617D38BBULL,
    0x68A97FDA9D89E82CULL,
    0xB5,
    0x25,
    0x15,
    0x02,
    0xBA,
    0x51,
    0x57,
    0x18
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseGSalts = {
    {
        {
            0x5DBDE1E2F9CFEA85ULL, 0x5D5DFDAD245A5EDCULL, 0x8381C818DF272FECULL, 0x7D9462DD7CA72475ULL, 
            0x5E321AAA42F3A333ULL, 0x93BED7BA6CC7228BULL, 0x9C4E0537246C3574ULL, 0x614A489BEA6D43C1ULL, 
            0x4C305F7B67901DA3ULL, 0x3EE0EE3B373215ABULL, 0x509168D233CD2F78ULL, 0xDBDD3FEFEEA7AF67ULL, 
            0x5C13D7F88F489DD6ULL, 0x298F8C21271ABCE3ULL, 0xEE9CB26214637145ULL, 0xF7AE56034FBD4BDEULL, 
            0x5802337FF649C9B8ULL, 0x5EE4D88560FEE572ULL, 0xC31820FE7F634D4FULL, 0xAA11A180B7925DAEULL, 
            0x2D3FC0791CA1F78DULL, 0xD84498885A8224A0ULL, 0xEA2269EC4B5B7C7EULL, 0xF7F23FC3D0060B4AULL, 
            0x41CF36CBEF530D24ULL, 0x0635030C095A8B46ULL, 0xE2B24E6786575AB9ULL, 0x8AE8776F565D4ED3ULL, 
            0x61D009235426BDDBULL, 0xAEC950C1A6B3A45FULL, 0x3131BC8640674134ULL, 0x1B600C6F9314BF03ULL
        },
        {
            0x641A2FAB6B796B58ULL, 0x6E29BEAE46F51151ULL, 0x5FECA1CEF15166B4ULL, 0xF5440C463D7F71B5ULL, 
            0xED02DBA2EBE2B2AEULL, 0x4EF2AD3B408AB116ULL, 0x1FA0A081182F8514ULL, 0x1BAACB8FE9454B04ULL, 
            0x8FCC8E71E204E7F1ULL, 0xD895066F937EEB5EULL, 0x91CCCC9A59209084ULL, 0xD169000899D3157CULL, 
            0xDBB0064DB7051A7DULL, 0x2AD4A617C1D4C495ULL, 0x3A4BD6A3D00218CDULL, 0x7FBC3754F44EF89BULL, 
            0x8644DB7F67411C94ULL, 0x9489E0C9F54A4C4AULL, 0xBA957A34C87C022AULL, 0x3E80549EA890EE0CULL, 
            0x13DF7CA5E9F140B5ULL, 0xEC71F1D81CB6B4B6ULL, 0xF7BD5F6A7C7B9BDEULL, 0xA1F13C6F63000789ULL, 
            0x02BF34178E14C7A2ULL, 0x570B56DD52A1AAAEULL, 0x99BBB4F779F10AAFULL, 0x647DB1E4DA1072DFULL, 
            0xA17FB3EF68DF051EULL, 0x4269312ABE4E7671ULL, 0x9117D715B2F817F6ULL, 0xD4FBA9AFFAB3D57CULL
        },
        {
            0x5B6A92FB721417B5ULL, 0x596037C29FD7C1F3ULL, 0x33C0848AF6037550ULL, 0x86545DDF13C93550ULL, 
            0x0DAC0FAE3E0A8CD4ULL, 0x6AE6045851E21C5BULL, 0x89E039073996DFF8ULL, 0x4390E0476104CCC2ULL, 
            0x3A563AE827CC2F11ULL, 0xBD63D8510827EEAAULL, 0x3710689A9992A06FULL, 0x99752F303DEBB40DULL, 
            0x0B41F9E14FE358CAULL, 0x0A2A817131CAE411ULL, 0x94494B5A48B07AAEULL, 0x308B4930C04D9D25ULL, 
            0x5BFBCF06906B6F97ULL, 0xD64DFCD21DA93367ULL, 0x22237A8C8481C668ULL, 0x821D73833AD54031ULL, 
            0x4702D8C8BA35CC91ULL, 0xF287655172C97001ULL, 0xE7B08346F082E5A5ULL, 0xC500AE32573072BEULL, 
            0x37002283D904A960ULL, 0x20A7C8D041E6AEBCULL, 0x3152DD7C02374257ULL, 0xE17D96BB6437E665ULL, 
            0x1A7B56EBF5703A93ULL, 0x9F602484CDB9E493ULL, 0x4803C863A2816016ULL, 0xFAB2385E63E90CC2ULL
        },
        {
            0x6A3BFD80151F8B9BULL, 0x3942DC136CFF12F2ULL, 0xE30999EA9D9FC798ULL, 0xB29BD0EBF0DACB51ULL, 
            0x8C65D381BBAF2DAAULL, 0xA068877D933E6BEEULL, 0x9A9E8234AEAF32CAULL, 0x090787EDFD4BB746ULL, 
            0x82292E2E8446F171ULL, 0xEAD6D73EE02BE9F8ULL, 0x9887DECEF95E4353ULL, 0x6FC8DFF310E49B65ULL, 
            0xE9E2A4F85FE61297ULL, 0xB7A6FDC381D2117AULL, 0x0AA3DAE8B893BBFFULL, 0xF4C1CB44A79B51B0ULL, 
            0xBF3A21C7158762EDULL, 0x1FE80DC0F6A42484ULL, 0xF1C1DB2AAE9AFA8CULL, 0x287862EFC0DC6410ULL, 
            0x9A95165BF5E5EBEBULL, 0x9DF051CE31D9D781ULL, 0xD40A7AFEDD84E63CULL, 0xF71ECB0E212E231DULL, 
            0x0554EE634DAD306FULL, 0x6E277EC1C77D4622ULL, 0x97D42F04426F7EA6ULL, 0xA11173B31EAE1025ULL, 
            0x2B1F81267FFADBB1ULL, 0xB9B50D2F820E9909ULL, 0x06F3BF6384BF9C8DULL, 0x46822ACE09A11286ULL
        },
        {
            0xFD2D0C762E1FA2BBULL, 0xB2310EC3DFC63600ULL, 0x1298DA0F4E245E39ULL, 0xB2C413F2CF4F9CAEULL, 
            0x41CB409406BE11A4ULL, 0x8B57F646303E4EC0ULL, 0x02E254D5422F451CULL, 0x6C7ECF558A3E1FC1ULL, 
            0x84EF8C77947F465DULL, 0x0C0ACC65157D0814ULL, 0xD4BEEA1BE4B6D512ULL, 0x071C8ABFB9617ACBULL, 
            0xEAA9742282E7A48AULL, 0x2D0CB6A2D6006C8FULL, 0x3362188A4E2F7B72ULL, 0x25D03912387A71E0ULL, 
            0x7FDC62F6AC0006D1ULL, 0x995DB6F245D2985DULL, 0xF907169BA24625A9ULL, 0x437CA50C852E4C05ULL, 
            0x5213B534181E632CULL, 0x6A294FFE2BF4697BULL, 0xB1A8468AC3DE8CFEULL, 0x86A467B05E583F4CULL, 
            0x5BCB3D5C880607A5ULL, 0xCB6A6CE4E02E2396ULL, 0x09D48460961474B0ULL, 0xA03CD407B0ED57CFULL, 
            0xA15F2BEDFA4B6FFBULL, 0x04425FD5AAB51FFEULL, 0x87EF5469B3115238ULL, 0x376E971006A0E73EULL
        },
        {
            0x1E699B0C81953F21ULL, 0xE701D1D2B4D9BBADULL, 0x8829853A0551669FULL, 0x3FDF6C4BF7BD1515ULL, 
            0x49938F1E3CD9FB2FULL, 0xE0EC016FFD757BB5ULL, 0x1B29C7EE91FF93A0ULL, 0x2C87C46575A3EF12ULL, 
            0x3E5DFDEB7D40AE93ULL, 0x209E1E7759D4DBC0ULL, 0xCDF12873EAEF16BDULL, 0x10793141039A4E17ULL, 
            0xB006C5065A6105D4ULL, 0x25F561E76B7754A4ULL, 0x364D85B0A7B7067CULL, 0xAAD1984B4AB009ECULL, 
            0x3850D7824F46633AULL, 0x6C17BB0C491AFBDAULL, 0x7A9158F90CBA3ECEULL, 0x391C955695A866E4ULL, 
            0x6849A67FD4356F6DULL, 0x3F09EF62C17B83CDULL, 0x7856A788E5E57C29ULL, 0x173FD45D02F1CB10ULL, 
            0x46DED100019CDB35ULL, 0x02C7AE08659BD495ULL, 0x776515E8E7F2280EULL, 0x9B84472463B9AD3EULL, 
            0x64829C69952020F6ULL, 0xEE1380A9942070CBULL, 0xAB0AF45854582924ULL, 0xE513A29265B4DFE4ULL
        }
    },
    {
        {
            0x04AC2776D548593CULL, 0xB5AABC0723BDAFF0ULL, 0x69B5668EF008FFCAULL, 0xEA8138DAD939C17FULL, 
            0x87FEEAE8636370F4ULL, 0x106C4E6308CE10D8ULL, 0x9D51E8D6B53BDAA7ULL, 0x5C7DD434393DFA8AULL, 
            0x29367987A3658B72ULL, 0x1D86C02EF9372B67ULL, 0xBF1D9512EA4E9CBEULL, 0x4561A06DE00529D2ULL, 
            0x7B70A5265DBF11DFULL, 0x7F59C51C8343B4F3ULL, 0xCE8074DA7B267DF5ULL, 0x5729CE4CFAB4A0C9ULL, 
            0x17C0F8D3912A3652ULL, 0xB65C698EDCE43086ULL, 0x1F080A63EF75E8BFULL, 0xF2C79FC6C4CA6A32ULL, 
            0xB54DF19520D371DFULL, 0x55E31D56716A3803ULL, 0xA7698ADE9C502C29ULL, 0x32C123AB03D3003DULL, 
            0x4A938BC800AD7D56ULL, 0xECB2E1DC5F29EE79ULL, 0x54F9DE77F7694AE5ULL, 0x547BA3F38CBC3B14ULL, 
            0x908802AE5F89B152ULL, 0x8C109CD5EE5C4FF0ULL, 0xB3D46DC382D90E80ULL, 0x2E11D931EF8FC65BULL
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
            0xBE7DC4CDFC953AACULL, 0x01F5AC602A15BF0EULL, 0x8AD8F1BD54B724F2ULL, 0x4756C2F0009128ADULL, 
            0x1B0707B1CA36B5B2ULL, 0x9FB64D2B58B41F77ULL, 0x9235939D0E384E77ULL, 0x8470FE339F538455ULL, 
            0x7267EB7017C88E7BULL, 0x143B3DFEE6285CEEULL, 0x7F951770C878AFF9ULL, 0xE34CABCE44B14118ULL, 
            0x1EEBB68E251EC2E5ULL, 0xB1F7D21807125475ULL, 0x39DD237D49E2B455ULL, 0xDC5F47E32750CCE1ULL, 
            0x231509655CEDBD46ULL, 0x55A941B6F4D68689ULL, 0xF6BA2F1D021AC3E1ULL, 0xDFE543BA1A4CE093ULL, 
            0x3FB336CE38F00581ULL, 0xAA7BF9A2ACAD9C3AULL, 0x6023EA560111CCD3ULL, 0x2EEF984DD7B10737ULL, 
            0x2CD4DD77BD8C0363ULL, 0xFD8E628B34604D43ULL, 0x37A2801EE24805C0ULL, 0x35CF7C2757C353E1ULL, 
            0xB3162AFB0CBAD225ULL, 0xBF48EBE1CADD9FA0ULL, 0x47ABC6DB04C9E1E8ULL, 0x730FDE9B29170C81ULL
        },
        {
            0xBEAFB14F8D8FAC73ULL, 0xE3147DB45B51C00AULL, 0x25178645EDC691AEULL, 0xF64CB6B805395645ULL, 
            0xDCFBECE5006F2DACULL, 0xAB86FAB6A34647B9ULL, 0x0399E38659CB8766ULL, 0x28E2C8F8B418F1CDULL, 
            0x89E49F2BD031BDAEULL, 0xDBD81A0291778A58ULL, 0x85650F0CEA89AB36ULL, 0x48A01D1073E99773ULL, 
            0xE0942CC8C174B70EULL, 0x54810DD92F8D9323ULL, 0x8539D27DF25F0C0CULL, 0xA47A49CB58AE534BULL, 
            0x8100050BB25D7D8AULL, 0xDF1F50BED9F5CD4EULL, 0x5A582E7E92E5EA71ULL, 0x6B6DB10CB6731133ULL, 
            0x2854FFE225AFAA00ULL, 0x9958DB2178FD3BB6ULL, 0xBC022759F108F958ULL, 0x69F798CD4E7A3D7FULL, 
            0xD425BE38FA767296ULL, 0xFB06C5C77521C47AULL, 0xF635D48E1FA53A15ULL, 0x0FCA2CD6BA36D81CULL, 
            0x9E8B7830E6C1926DULL, 0xAE18766F015DB865ULL, 0x43A873055B4D9AA2ULL, 0x6D5E3139666ED023ULL
        },
        {
            0xF8184A18B14317EEULL, 0xAFE5F101225BE152ULL, 0xD0E5DF7104F19AB6ULL, 0x26C5F0041CAFE428ULL, 
            0x024BE93D3E283BF5ULL, 0x961108A2791DF09FULL, 0x3C5AED2E35C61846ULL, 0x91DEB29BE8BBF08BULL, 
            0x6BAAB7C02CE92A61ULL, 0x2A57175D4D8BA727ULL, 0x376611B782F6CD25ULL, 0xACCA6EC549599047ULL, 
            0x142EA0561649F6B7ULL, 0x081232788F721F9CULL, 0xF042C6C67F34DA24ULL, 0x21394C9EF76CCAB3ULL, 
            0xF7D8D843B7A27781ULL, 0xB5AC7953C184B405ULL, 0x4E7CCB2F60550A5EULL, 0x883D31709AAB6126ULL, 
            0x0B0954700C22D709ULL, 0xE9E96B5D95CC8A16ULL, 0x806D0D9859FF0751ULL, 0x096223A496FED173ULL, 
            0x93DCC232D627B807ULL, 0x5836A4814DC72F6FULL, 0xD8929DB2F4D0D816ULL, 0x9476222614DBCDB9ULL, 
            0x040596500B55F11FULL, 0x6164009860F38B3FULL, 0x1EBAA75979071DE1ULL, 0xF89A19DE9DF02F2BULL
        },
        {
            0x60C4896D482F7848ULL, 0x8A0E5BC3AC0C510BULL, 0xB018BFE015B74153ULL, 0xAFE6999B0BB375A8ULL, 
            0xC97951DCD147D89EULL, 0x2EA4A8419BE75BD6ULL, 0x76FA5DF738D1B9F2ULL, 0xDE3BA90931AD625CULL, 
            0xF33420BEB8AD8CF3ULL, 0x2C4F1BB76430E2E6ULL, 0x7E921880AA147832ULL, 0xF6228638697960F5ULL, 
            0xCC50E527167D059DULL, 0x2218008DED68CD25ULL, 0x5153C1DD9554CA64ULL, 0x445E51BE404BBDB6ULL, 
            0xFDDEFCB8D83A5D35ULL, 0xE658CDC09DF40F78ULL, 0xF6CB0B52B3F7A6ABULL, 0x7B23984263CB38EDULL, 
            0x9FBFB5E0BD5F0872ULL, 0x2CCBA0F26F21D39DULL, 0xD09AB1113AC9713BULL, 0xD6D89E1AE9883C7BULL, 
            0xB1216601229DA789ULL, 0x99D6F45967B4582AULL, 0xADD81703BE1F7C09ULL, 0xD5C7F6500F69A4F8ULL, 
            0x440D8EADCA2B0BB6ULL, 0xFBBF4B081D2FFCE1ULL, 0x5C3D3C6F4B86FB62ULL, 0x0524719CBA8FA16EULL
        }
    },
    {
        {
            0xFE5EE0B693816187ULL, 0xC29AD3D129A657BBULL, 0xF5121AEEBA80DC4CULL, 0xA2E9AD072D25039CULL, 
            0x155A22404F10B206ULL, 0xA3E9F41D3DD1CB1CULL, 0xA92434FF385A32C0ULL, 0x2432906EE98F125BULL, 
            0xCC06F4CF07874743ULL, 0x85784EC505DD4C67ULL, 0xC9101432B89BA496ULL, 0x8758B1211814F2A3ULL, 
            0x4BE6C10B7878B85AULL, 0x7BAD0D6F686392E4ULL, 0x67B13063AA4ADB36ULL, 0xB4493AEB55C12263ULL, 
            0xC2A6BB6AEDB247BDULL, 0x596CB59F3B2C790DULL, 0x2E5EFEC2B74DE480ULL, 0x9C063364E713244FULL, 
            0xFEDE8A8D90E1B9F1ULL, 0x752BEFBBABAC4D4BULL, 0x1304A68B0DA5A73DULL, 0xA5FA42ABCA236466ULL, 
            0xF95E5DECA9CD800CULL, 0xC8DDDFD7B3EE1700ULL, 0x38CD0B5C932B0DABULL, 0x7720EDFCF6C50A89ULL, 
            0x2B468B889B3C2BA6ULL, 0xAA3928D027621B69ULL, 0x8729F819C1686695ULL, 0x110F20B0D4B3BCC3ULL
        },
        {
            0x8C940D82A4FBADCFULL, 0xC9D45997CCA7C6EBULL, 0xCB068C95377CD5B4ULL, 0x4A1ECD0E44DEEF7BULL, 
            0x09E6A253EDFD5E13ULL, 0x1F92ABA28DF4D0D9ULL, 0x55CB49C232163F11ULL, 0x2A4AEEF4E0BBEBA6ULL, 
            0x918957B3FA69CDBEULL, 0xDA9BDD78372ACB5DULL, 0x3A4AFE1156A30995ULL, 0xAEF5BC0B50BF0BACULL, 
            0x86EC9B74A9365B74ULL, 0xB738DD5D5FF8AA1EULL, 0xEEF37CB8FF79CEE3ULL, 0xC5C8C3C4371ED3A9ULL, 
            0x6EF457CE8CEE5082ULL, 0x3A91D5EA352DE15AULL, 0x638D0252F5CB485CULL, 0x6B5AFD450D10CF3FULL, 
            0xA46CD56DF82D62EFULL, 0xD70CBA80112DEB31ULL, 0x1696CD6FA1C1A7A7ULL, 0x7A2DDB2249CB1618ULL, 
            0x9C000A482E8848C5ULL, 0x7964FA6955D0234EULL, 0x55F2CF3F78AFDB59ULL, 0xEA8C1234B6A892B1ULL, 
            0xDC7637262E4C7CBEULL, 0xA0A6901B5C5A8505ULL, 0xC30EA50545432007ULL, 0x3A6A84701B9526F5ULL
        },
        {
            0x8BEBBCD8E70CE129ULL, 0xC870DB2ED764CEBAULL, 0xA519B49CD3AA73FDULL, 0x757CCC7FE973F657ULL, 
            0x7927C56CEC81106DULL, 0x16E25E8AFA8431CDULL, 0xB39DA5F728417E65ULL, 0x5B94282F03579977ULL, 
            0x226D75AF234062AFULL, 0xD1306F19091F01EEULL, 0xAE02291D0836E207ULL, 0x753CD651CCFA3C3DULL, 
            0x695F35420286C372ULL, 0xDDAB6F91CD930900ULL, 0x7521E559B4F1C879ULL, 0xA09FA882D4EB84EFULL, 
            0x0D8F22B46B4E4CBDULL, 0x0F8271311AC3CC61ULL, 0x7DC29A80C48354E1ULL, 0x9FA1C5AFD1FD1312ULL, 
            0xB72A79957429A8B3ULL, 0x39E9101209A0C399ULL, 0x8CEDA0006F0FD857ULL, 0xD753E21E42CF9DE2ULL, 
            0xC7DA6B059E4E314DULL, 0x339C187EDF5309EBULL, 0x98B0F415A11AD667ULL, 0xF206C35D9B12F93AULL, 
            0x906D4ECA98B84B0DULL, 0x92C59A4463DA2C32ULL, 0x9AC13D4330E45BDFULL, 0xECEFBC78190B9627ULL
        },
        {
            0x9ECEC5CD17C8B05BULL, 0xDCE8D436021AFFFBULL, 0xCF4C7B9241E54423ULL, 0xFA201C5FA8442974ULL, 
            0x4F521FA4481651D3ULL, 0xCD8F9E1F38341641ULL, 0x8BFC63221AF66D8FULL, 0x2E206535B7982FC6ULL, 
            0x3107179F29CF4EBBULL, 0xD7C23C540094FCE3ULL, 0xC5A146E17C62FD1AULL, 0xF273D83D656CA0BCULL, 
            0x0E62F6AB2AB60428ULL, 0x1D33546DBB355718ULL, 0x423D859D5C6A9A8FULL, 0xF609E05D2532D2EFULL, 
            0x976FAFFD42BAC67BULL, 0xB389F86016851B30ULL, 0x01D0B58EBFD934A7ULL, 0x1DD10D37755D1D51ULL, 
            0xA85C8A8173FE6D87ULL, 0x4ECA2D85C8F2DEF4ULL, 0xCC10525607CCAD0EULL, 0xC6E48B69E9995170ULL, 
            0x13AB267C353EF75FULL, 0x25DC09B1DFFCB6F1ULL, 0xE8BF566631E6D5F2ULL, 0xF3151716291EFAE4ULL, 
            0xA7AF9BEF923C2999ULL, 0xCE7314B13D55A9E5ULL, 0x0590471BA20D6B65ULL, 0x6594D89102D474EAULL
        },
        {
            0x7887B87DBFAA4C87ULL, 0xE161CB26A3ED13C0ULL, 0xB500B9C3C9CC22E6ULL, 0xEA084133F5770BDEULL, 
            0x2790427612D51714ULL, 0xABCC4F2CA0AFB7FFULL, 0xE567AE60E84C9BFDULL, 0x216D349814C32031ULL, 
            0x4FD719CD655A5C2CULL, 0x8E70A73DE84AB240ULL, 0x302B9653BD83FDA1ULL, 0xDB483174975C2B17ULL, 
            0xDA6BDE2B75E3DC69ULL, 0xFB72A3A97B211079ULL, 0x2739917644F67F5EULL, 0x53C53CE5C53480C3ULL, 
            0xA0C7457DBA6E714FULL, 0x6FC79FA152BC5B5FULL, 0xE45F46D25C8C572BULL, 0x8DCF800DC118D98DULL, 
            0x20AACFCB18090921ULL, 0xEF9AFFBB0FCCC856ULL, 0x4544B9FA6A364C61ULL, 0x80D75DB8D0025C17ULL, 
            0xDB4E25EE2F724B62ULL, 0x8B4A1012D246C695ULL, 0xB2451E951071078BULL, 0x929A11BC08FEA100ULL, 
            0x8C0A41FD799B0042ULL, 0xC0AE7031F61D6750ULL, 0x224F9661D82528D3ULL, 0x5992718B26225EDFULL
        },
        {
            0x44579CD178304475ULL, 0xD66D47CF039C1697ULL, 0x048489FC50F31B4EULL, 0x39A9B301A245E716ULL, 
            0x559473387B9CAF65ULL, 0x49145B2B78995205ULL, 0x5B457DE2728A9AC5ULL, 0x7C281EF1405852E0ULL, 
            0x221AC06A7B497BC2ULL, 0x6E8EC72EF8610A79ULL, 0x1E4B799866899A73ULL, 0x647EA80BF8EFC477ULL, 
            0x56D0F93E450409CBULL, 0xEDD4C7140F175679ULL, 0xBDEE3F07D9DC8A12ULL, 0x12AFEDA6856930B1ULL, 
            0xA82E1E5AE97D5C8BULL, 0x025A2A1F07D1C0A4ULL, 0x068B101870DFD82CULL, 0x54CC1D9C1F7A587FULL, 
            0x72DE309E368D1DA0ULL, 0x180D5B9E78AE8803ULL, 0xF8CB4D5283B7571DULL, 0x369DD1A90CE13058ULL, 
            0xC8A42F79043A6687ULL, 0xB9554720E0DF76BEULL, 0xD0FEC9E4C696A449ULL, 0x3D177ED52C94597DULL, 
            0xFB715A336F67C5C6ULL, 0x6168BFFC90A5BEDCULL, 0x7EC7DA5907295FE4ULL, 0x5B3732EDA5EDC5D7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseGConstants = {
    0x402561806589CA8EULL,
    0x514E7C7A78702ECAULL,
    0x6E69AB8F55B2AD81ULL,
    0x402561806589CA8EULL,
    0x514E7C7A78702ECAULL,
    0x6E69AB8F55B2AD81ULL,
    0xA7214458371F5966ULL,
    0xE254BCDFA3F9CBBCULL,
    0x7D,
    0x7C,
    0xFA,
    0x4A,
    0xC1,
    0x39,
    0x70,
    0xD8
};

const TwistDomainSaltSet TwistExpander_Menkent::kPhaseHSalts = {
    {
        {
            0x89B11E36EDD0B717ULL, 0x0464D05C58F079E3ULL, 0x8DAB0C129AD3D6EFULL, 0xF649A9AF55FC8FA4ULL, 
            0xAA2EDA676FE67856ULL, 0xAE5D37E7F3B22C85ULL, 0xE04042F6A20A9AB0ULL, 0x6A93242870FA3838ULL, 
            0x34AD19E725585C29ULL, 0x5E1C1C516970FA51ULL, 0x06AD469EF484F357ULL, 0x95DDCBE02CA1E342ULL, 
            0x2B841DE77C5843AFULL, 0xE70AFF35FE62B04EULL, 0x4FD3FF4ED44DC2B6ULL, 0x2002B4A4658C7C46ULL, 
            0x1AEAD561CE87FB6AULL, 0xE6373762C8C7FBAFULL, 0xD1BE6AEE462A99C6ULL, 0xF0270DD933098B5CULL, 
            0x3A7F38641301629CULL, 0x6F045F01E6FAD400ULL, 0x3B00E722B5D81FBBULL, 0x67B10EC7557107F3ULL, 
            0xB5D67B310DD614A5ULL, 0xF4962D96F86CF206ULL, 0xC1B9E1E2D104F96FULL, 0x8B0DA7E479AA5AE1ULL, 
            0xEBED570A17F5738CULL, 0x22BB133FCB98E210ULL, 0x95B2E9B5711AF185ULL, 0x89FD45CBF1BFB68EULL
        },
        {
            0x6415BA73861242A4ULL, 0xC5BE95E6DDF068F7ULL, 0x3752090B3A500AAEULL, 0xCE43845FB8B0B013ULL, 
            0x910C7A7EBF19FAE5ULL, 0xB9641BCADE6D96F1ULL, 0x628F81E2AE30912DULL, 0x907BB2931BFB32C4ULL, 
            0x5246818AA5673FFBULL, 0xF511077561194B92ULL, 0x54B9BF4EDEB266D0ULL, 0xE7E2FBF405760840ULL, 
            0x67DA677A2E06FEB4ULL, 0xD24F531CB3DD2E08ULL, 0xC0A85725DAD29AF8ULL, 0x2795F9213C845BA6ULL, 
            0xD75E42AF02A58465ULL, 0x01ED461C9C6A42ADULL, 0xD0890D2191D19A5CULL, 0x17776D3CBA24F856ULL, 
            0x4615E365C93B0051ULL, 0xD495FA693994AFEBULL, 0x28ACC48C5FE49201ULL, 0x809F7B1477584AC7ULL, 
            0xC00B8C8BAE7F0E34ULL, 0xF1CDC19A0606B015ULL, 0x1FAAAFC68B7C2C40ULL, 0x607D1502E8345ABFULL, 
            0xB2DA1293928F9793ULL, 0x3D620EFBA636EC58ULL, 0x927CF0BD179EB6C7ULL, 0xC9752E48E206EC1BULL
        },
        {
            0x34E8234F691371E4ULL, 0x0C93B1118BEB672BULL, 0x2C3FDFE42DA5BFD4ULL, 0xB0E691EC65ACE5B6ULL, 
            0x3BD45C9061E70967ULL, 0xA5EB23D26CCABD87ULL, 0xF4BE8B01451732DBULL, 0x8E54AB1D307A577BULL, 
            0x4985680E82C0D60BULL, 0x1E8F185B77A98266ULL, 0x817144D5D52BF999ULL, 0xAD97E290D118C2EDULL, 
            0x0E4092399C26C6ADULL, 0x73AF41534AC9B7B1ULL, 0xBCC93F1DC1600F63ULL, 0xFC633B5866048C72ULL, 
            0x7E5C50D83A6F1829ULL, 0x1EB5CD7462D90F21ULL, 0xBEBF4CB2E2FC9185ULL, 0x8FD0814B7C9B7E11ULL, 
            0x73BE39735ECE0D39ULL, 0xB95BEB2E163B14F5ULL, 0xC7CD7ABDCD90A3E9ULL, 0x5803ED7C43D0F80EULL, 
            0x633507A6030FB2ABULL, 0xC59C3D64F9CC1257ULL, 0xD15E1FBFB400E688ULL, 0x1891CAF66C73D358ULL, 
            0x4887ED997DD23285ULL, 0xB75ADCF45E58F6B5ULL, 0x44A1F3497202A41FULL, 0x1D814B5BFF7E73C3ULL
        },
        {
            0xA5DDA57B2AB5778EULL, 0x13D03089F0360BEEULL, 0xC3122A48BAAF697BULL, 0xDDF46A4EF8F9CC35ULL, 
            0x09A70E12D45CED13ULL, 0x0702EDE38F997653ULL, 0x5AFC5100AA41C418ULL, 0x08110E86F904440BULL, 
            0x024E91E2066CC424ULL, 0x2505187643BA877DULL, 0x69001C259C615FD7ULL, 0x26EB1B30D108C5B1ULL, 
            0xA3A3E19E4AFD5DE2ULL, 0x08F2AA805302D59BULL, 0xDA583F7B909C880AULL, 0xCBD0E5F0E480D976ULL, 
            0x61DADC1C20359C91ULL, 0x78705E63011D9F4AULL, 0x5383EF06C5FB276CULL, 0x68CC4619A4E786E7ULL, 
            0x965E049232D23A9EULL, 0x22CBE7D1DB70D80CULL, 0x4DFB12BA1ECEA07CULL, 0x83D8DB87AEC2A537ULL, 
            0xDCFB562484FED9E1ULL, 0x167D7A5D3438E1C0ULL, 0xF62B81B333ED774CULL, 0x2B9A5B32C28973EDULL, 
            0xC42679CAD31A1FAFULL, 0x9D18A73A14415BECULL, 0x33889061BD88B9BAULL, 0x48235AE9CB7E9345ULL
        },
        {
            0x504098FA077F0701ULL, 0x070E65547DA52B59ULL, 0x74598D71C8BAAA69ULL, 0x32AB9DB0DD2A638AULL, 
            0x82E1C189EC38B0E7ULL, 0x23EE21C090CD0F67ULL, 0xD3DA616C7D98C8B9ULL, 0xCD57EA4DF95137D7ULL, 
            0xA96A8E11A1F76E95ULL, 0x96CFA7C27B3775D2ULL, 0x06612C22FFC02662ULL, 0x4C1DDDA2FD37F95EULL, 
            0xD23DBDF869A773F5ULL, 0x9945275EF0CB9966ULL, 0xB35AE5CB8DAE1AF1ULL, 0xACDC1483FAAECE6CULL, 
            0x1F6D730B07BB0F45ULL, 0xBA60EB8A442A6DBDULL, 0xCE6C274F1150D135ULL, 0xAFDC81D01A6BBE6DULL, 
            0xA797C0B8F9DB211FULL, 0xA865AB51C1914357ULL, 0x3CF71F2EE72F59E3ULL, 0xD61C0C5CC2D62647ULL, 
            0x9978866B39FB0AE2ULL, 0xABDEB39F5C11B7FBULL, 0xEE571ABF4A40D967ULL, 0x701666BD272CE453ULL, 
            0x3E8221BE50C1CDEFULL, 0x05F79EFCB672D5F7ULL, 0x6E66CBEA7EF19148ULL, 0x7E01DB3C9D785B1AULL
        },
        {
            0xF68C83E65FF8BDA4ULL, 0x5B4BF452EA0F3C82ULL, 0x4E4710CD09E2820AULL, 0x4468BAD0DC61A2F4ULL, 
            0xCF6767C61AF1E24DULL, 0x9B60226F06EA47C2ULL, 0x522A68E1084216A0ULL, 0x501D496CE6B3B4BDULL, 
            0x9D89F7EBBF40B88AULL, 0xB1B89C5B85188899ULL, 0xEAEAC8B17CB2BD57ULL, 0xB2FE85AA7FD6988CULL, 
            0x599A187294BA3ADBULL, 0x4BEC3BEBED038A4EULL, 0x52A5618EC764F09AULL, 0x2773CC99F5E25767ULL, 
            0xB6C1B26A4CAA89C5ULL, 0xE666A1CC7669F6C7ULL, 0xEEBD2544165553ECULL, 0xD78AB4EFAB9A7382ULL, 
            0x66DF7A085AFD4610ULL, 0x0DE2061F5FAF7812ULL, 0xC3DDE436E42D94A1ULL, 0x02E08B4140E664B3ULL, 
            0xB17DD77E30FC79D1ULL, 0xE4950C7599C37F09ULL, 0x022C85125F1A4EE6ULL, 0x7BE52B18D75EA6FDULL, 
            0xB2B4C9F2B214FF2EULL, 0x34E22731D1B174C5ULL, 0x0B7260B0DC81D03FULL, 0xE5E9FE4F71993791ULL
        }
    },
    {
        {
            0xA69C7BA26910D90DULL, 0xFDCAF5985A31313FULL, 0x8EE2757825A3D0ACULL, 0x0EB5574B41630C83ULL, 
            0x32BFFE4DCD29C3FAULL, 0xFC60339213DDA1D6ULL, 0xE23AA9AA02463E5FULL, 0x1D7344C61F233893ULL, 
            0xC2275E21105E03C2ULL, 0xC86E7855FC5CDF65ULL, 0xF4DADC4418D93048ULL, 0x53E08EC8CF786536ULL, 
            0x35E6FAB3DE14459EULL, 0x3C0B44EE34088AB1ULL, 0xD9F68D3F0F3E92D9ULL, 0x953ED58F69814667ULL, 
            0xFF220E125AAF3640ULL, 0x80AFEA3197C5EB0FULL, 0xF925907EE972B252ULL, 0x6074B7E6167BD829ULL, 
            0x804DD0082DECC0EBULL, 0x45F6E59BDABFC654ULL, 0x2BD16CA2AE54595FULL, 0x3472C465B9DA6016ULL, 
            0x15897FDBB353A300ULL, 0x9C94F137834F4258ULL, 0x7FFE6A19C840A0CEULL, 0x509ABD95090B1989ULL, 
            0x2AF54A813E0044E8ULL, 0xC4E79D46886013ABULL, 0xD8DD00A0B52A31B7ULL, 0x05409E02E98B2925ULL
        },
        {
            0x8B67F41CB9734C75ULL, 0x2AB76F768F74009EULL, 0xB13D0DD40F6DF5C7ULL, 0x93731071B8BFF52FULL, 
            0xC54A750E3D9F546EULL, 0xA708536E4A0363FCULL, 0x2D99DCAAB0AC39F2ULL, 0x4E9961EA5B936DB1ULL, 
            0x1612BBC3D27B4B7CULL, 0x5E25F6FD6CFDBE77ULL, 0x396B13A2510F9DA9ULL, 0xAEE0CF4F809DBCBAULL, 
            0xBBCBD08CA94ED2B8ULL, 0xDD8D738466CE4D32ULL, 0x5EE0FDDBCFEBCE26ULL, 0x3ED1F725B22F7397ULL, 
            0xB74FF1C952715335ULL, 0xAC2EB2946D6D2C45ULL, 0x72D5015473F0E113ULL, 0x84BD478D44E1FAD4ULL, 
            0xF3B0289A180BF377ULL, 0x1CC5B31B8612C547ULL, 0x8954A01E32B58A85ULL, 0xC344798BA64614D1ULL, 
            0x6C4AFD28E6ED300FULL, 0x5A0FFD457AF7190AULL, 0xE9394795BFEA44CAULL, 0xEC2DD4C3915ACD2EULL, 
            0x276825F18BB5DE77ULL, 0x081143CABDDE946AULL, 0xAE0263D0434452F8ULL, 0x3F32838B731BECB5ULL
        },
        {
            0x4B144A25FC8A04B6ULL, 0x83A828E0780BB43FULL, 0x614D11F4DB5F53AFULL, 0x509DE8020534AF1FULL, 
            0xDD4A0EF877B4AAE9ULL, 0xF292A25BE4B53D67ULL, 0x5447EA46123A4E3BULL, 0x1EE13D7EDB4D50A4ULL, 
            0xFDC9A23B9462223BULL, 0x835EA9F76C90859CULL, 0x1F41A592D2B47E4CULL, 0x46E7AAB47098CEE5ULL, 
            0xEDFD69E7872AA66DULL, 0xB1D54624D7550AC8ULL, 0xFFF24CD2E06B3364ULL, 0x55B8C976EDBF4A65ULL, 
            0x61CC8209E68B3BC4ULL, 0x53710DDF63B7E7BAULL, 0x8E151D6DC808E645ULL, 0x0F811EF66DF0863CULL, 
            0x3F942D178E72B633ULL, 0x96251CE5DD9EBCECULL, 0x630E740C9626F2F6ULL, 0x83F721966F8D289DULL, 
            0x4193A20ADA8090E9ULL, 0xE18C1995A1C45047ULL, 0x5D0B904878871608ULL, 0x7DF3C55A053C1069ULL, 
            0x210AEAD09EBCFEA5ULL, 0x683B435E1B8214EEULL, 0x939CFE4A454F1D09ULL, 0x4FC03A0CAC3C5359ULL
        },
        {
            0x0905C3224F8177ABULL, 0xECA6C50851CB6293ULL, 0x314C4166EF5F95ADULL, 0x9DBB951DA43C2EE4ULL, 
            0xBCC3279E3D49D2BAULL, 0x47AE23348D0128A1ULL, 0x2FA13D675A23E142ULL, 0x775A4A489143DC74ULL, 
            0x938CA02DCA1AA6E8ULL, 0x2504512572911664ULL, 0xF1D370D1C3D6F86BULL, 0xF4E64E03E102824CULL, 
            0x36E8B49D3055D315ULL, 0x776D85920756D44DULL, 0xE4AE2FBD7AAC0DE3ULL, 0x7A20A0EBBBA9E979ULL, 
            0xB3193A1EB5A02501ULL, 0xF9D21EBEE20C90C0ULL, 0x54DBE0279EB8AD16ULL, 0xD928D134A67A6FC0ULL, 
            0xABAF4F7DBA34A472ULL, 0x1548D6C64C8A05D9ULL, 0x1645C918A795E496ULL, 0xAFD68C53258874EEULL, 
            0x253E37EA6AD5A437ULL, 0xAA99901EC0A187ADULL, 0xD6A40454AD1F11BFULL, 0xAE464420342D8AC8ULL, 
            0xA291F7595EF4939EULL, 0x2579223D95D73C2FULL, 0xE94CAFB71AC5F63FULL, 0x3CD989F84D77C711ULL
        },
        {
            0xE766877CBDB014DDULL, 0xF258FAAB603E01EFULL, 0x6C999C4A11196D8EULL, 0xD283C4BFDFE66C2DULL, 
            0x7EEBE72C82BF9BAAULL, 0x7224C5BE188BF82BULL, 0xEE1684950D7560F6ULL, 0xE93018B401A85776ULL, 
            0xCFF35E96C883C9CAULL, 0xAA1C7670EDACD337ULL, 0x94F3137AFB8E0B87ULL, 0x6CF7F25F59F6A7D3ULL, 
            0x393DD17D80AF1B67ULL, 0xC09DDDF21A33307DULL, 0x15E181B9E673DEFCULL, 0x4D325A884F13CAA4ULL, 
            0x4C25C70D237673E9ULL, 0x08C88FFB2C6796C1ULL, 0x3145DD6760FE148EULL, 0x03CE86738AF394BFULL, 
            0x68CA9779C99178F2ULL, 0xBE2D88283A1F15FBULL, 0x1492B13896949A93ULL, 0x400A357AB849A9DFULL, 
            0x6C01DCC0372F0037ULL, 0x945B602368D90CCBULL, 0x0610DB8AD8C35251ULL, 0x61F36565A0E1EC36ULL, 
            0x6347EB34636DF252ULL, 0x6A8371205AA202C2ULL, 0x088E042F3EB5F59CULL, 0xCD03DC88A3886AE4ULL
        },
        {
            0x6CC58A9A86486BB9ULL, 0x2FB53D3BBF202240ULL, 0xBA4DF31B0DBF40EDULL, 0x2CB4B5EFD1F0B8AEULL, 
            0xCEF96314C4DDF82BULL, 0xD0F521893A2415F0ULL, 0xDEEE2EE8AF52D531ULL, 0x86B001DB0EA7F132ULL, 
            0x91688E02ED3A2AA6ULL, 0x493D94CDE665EA27ULL, 0xF98ED280F2EB3B53ULL, 0xFEE5484C1AC00703ULL, 
            0x3D80ECB5E6A82B9AULL, 0x6AF5066FAD9747F6ULL, 0xD4E24064FE4564C6ULL, 0x7F2124D4F2C25DD3ULL, 
            0x846B173A1094A061ULL, 0x31BFFE3F7803D7ECULL, 0x74CBBEB82F74F980ULL, 0xB3B60FB4034EFA74ULL, 
            0xE050D016CE6826FFULL, 0xE4FD651CAC711167ULL, 0x46B1F02BFD19362EULL, 0xCDDB9590A92C8668ULL, 
            0x68BD3738CEDC3F99ULL, 0x9F578B5E1487A3CFULL, 0x5864C0C633D12EF5ULL, 0xB4CF51B870B88614ULL, 
            0xF660D124D127A112ULL, 0xD188DE189DF0566FULL, 0xDF13231AC468E912ULL, 0x454705D6F543A742ULL
        }
    },
    {
        {
            0xD565513F83A9CE2DULL, 0xAD8E95516D3DCA11ULL, 0x896F220A46D6A567ULL, 0xD0CD893602A631EFULL, 
            0x8C1DD26D0EDBB5EEULL, 0x589E4D9005F4CF8AULL, 0x3CAEE37028C58EDAULL, 0x34A04D3447222FBCULL, 
            0x6D19BBE7BF7107F0ULL, 0x1DDC6FCBA7C44D8CULL, 0xA78F440BFA9FF6D7ULL, 0x78530941AB468C29ULL, 
            0x6344930747F0C0E2ULL, 0x1729FE29017F364CULL, 0x6BE28D2C43A5EEDCULL, 0xED0FC164A96B4F5EULL, 
            0xE85C84E51C7AEDABULL, 0x53DA2D2786531EA0ULL, 0x7C41C02F22526D8CULL, 0xBB9866580B90C8A7ULL, 
            0x222BAB1EAB5D475FULL, 0x952E2BA974E9B436ULL, 0x9AB81DD490459212ULL, 0x0A4788A0296245F8ULL, 
            0x5B4F3D21F8D4DBF8ULL, 0x2210E684450D2631ULL, 0x0AB76E02B03337EFULL, 0xA4E40D317B411727ULL, 
            0xB2B10EF4D94C92D2ULL, 0xFEDCFF6400534058ULL, 0x623570B2F6C3A714ULL, 0x51DA6A2B10785FF9ULL
        },
        {
            0x3C5E965B2AC4B6E4ULL, 0x0787C936156CCFE7ULL, 0x6C34E7AAE544D64AULL, 0x4BA2103A4F82E66DULL, 
            0xAE25042B45222329ULL, 0x0A81E839C210E599ULL, 0x0368805256302ECEULL, 0xECAE0385D6474514ULL, 
            0xA28392835BF499CDULL, 0x27BF80D590A40E63ULL, 0xFD8D65151E282AB3ULL, 0x9E66C8E637EEBDBCULL, 
            0x74297169E73ED15CULL, 0x604672B67FF05AE5ULL, 0xE30CC1BEFC6DC84EULL, 0xCE9188581D32C678ULL, 
            0x9F7139B1462486B7ULL, 0x414345ABCCFF0766ULL, 0xFD84117D47BD8747ULL, 0x838D6634D8E9A2D4ULL, 
            0xBC55F1A4505A9010ULL, 0x1550F1C8756276DCULL, 0x986736CEA79D06A4ULL, 0xF48BA4A24B2D88DEULL, 
            0xE7D1B67B755F0B3FULL, 0xEF5F8653B7E272E1ULL, 0x346B0018488F3EB0ULL, 0xB8793FCF852D0CF2ULL, 
            0x9BE31AD06A1CD6B3ULL, 0x48A0425285238771ULL, 0xEA82A8695384B79BULL, 0x2779364167AC8975ULL
        },
        {
            0xEB93BF03C05D3A5DULL, 0x0EDFF63200F7C429ULL, 0xF2BED05441A0AE34ULL, 0x03431A12FC56D53CULL, 
            0x28287966FD1B8CA5ULL, 0x02608DDACB3E4987ULL, 0x4A9B2F2C83E2B6A8ULL, 0xC6846E746FB8F7DAULL, 
            0x752E4ABC84D4CE70ULL, 0x60B56B87B2B4F22DULL, 0x031DE702CFDD9D06ULL, 0xEF6F61E50A304A08ULL, 
            0x42A59045365A8245ULL, 0xE2848FB7AEF0C43EULL, 0x7D22EB653DE7C102ULL, 0x815A6075547926E9ULL, 
            0x4B856A60F67A313EULL, 0x331441627DE69F28ULL, 0x569A1C0BCE8B0172ULL, 0x5ED063252FC33B9AULL, 
            0x21AA8F856609034CULL, 0xB1E22A7E600D15DDULL, 0x57FBF8B45811AF61ULL, 0xF301BCE13E2116ACULL, 
            0x39A8461FE38F9EF9ULL, 0x2E1C8C6363520945ULL, 0xAA4C9AC496C978FDULL, 0x99784F1E2384FFFCULL, 
            0x51841E255AC91F44ULL, 0x735DEBA6137523C9ULL, 0x127FD94A2D77F5CAULL, 0x030B2B477E13D618ULL
        },
        {
            0xA8B8955C777B9FA8ULL, 0x217185D27C6266FEULL, 0xCF5189006D36234CULL, 0x59BE08D7277F28FAULL, 
            0x6B0CC191CAF76B85ULL, 0x434EE229FD827E3CULL, 0xA0B3B19B9FF4A740ULL, 0xA6CA17E4C66092E3ULL, 
            0x62E6437074A672A0ULL, 0xA74E13EBE6ADBD12ULL, 0xE00DAE554F61C51AULL, 0xD700DE1F690ECB40ULL, 
            0x1718925E54D05530ULL, 0x18176CE4EEB4D4BFULL, 0x1FB30502A1573984ULL, 0xBE1742119FF4874BULL, 
            0x866A10B8DF8FBC16ULL, 0x9539A738F965A4B5ULL, 0xC44EC49AEBD177BDULL, 0x115AFE52918D0283ULL, 
            0x89662AE79354C477ULL, 0xF590FE316B7B380CULL, 0x3FFEA0ADFDD55BE2ULL, 0xB9C2F7B231C3C0C0ULL, 
            0xED0135694E2D8698ULL, 0x0DB21A350C4A5BADULL, 0xDFD886BD3BB6370BULL, 0xC27E8CB5093EE0EFULL, 
            0xB65513F9D088A9C1ULL, 0xAAD49BCFB28660FCULL, 0xCFBFB07214EB5652ULL, 0x12EA7C62ED41D21EULL
        },
        {
            0xD1F5D8E2A66A2233ULL, 0xE98F2856B989D9CAULL, 0x02F1B676287B1AB8ULL, 0x4BD0562E9F01C43DULL, 
            0xD8A1D5E5869E1317ULL, 0xAA9DEA23D72085C7ULL, 0x3CD0B66175F64447ULL, 0x7D8A29200B560A78ULL, 
            0x2D5B92CBE8035E1FULL, 0x319AA466B32C2EC5ULL, 0x7D8C5B4A686E6565ULL, 0xB31A30A4DD001F77ULL, 
            0x9E9C97D706167F3CULL, 0xCFE4DF02E1EE9492ULL, 0x4E357B5FBAAF116FULL, 0x50D470644F3838D2ULL, 
            0x0CB900BBBD12288CULL, 0xF3E289D9C5558B4DULL, 0xAE88C46158BA3770ULL, 0x381B2E3BE04017D0ULL, 
            0x4281C7B14636F86EULL, 0xF441E17E62077907ULL, 0xB450EF7980429D27ULL, 0x2D701926C530BCECULL, 
            0x567CA6A5AA0D5FB5ULL, 0xF872625E54CE6CD4ULL, 0x6B5AA3E3A08165A7ULL, 0x58BC9E0E9DE5BB7CULL, 
            0x875F17F12B3477CAULL, 0xEC4785A1613D4F19ULL, 0xAC3A1E5C3952E871ULL, 0xD46AB015B5BC5895ULL
        },
        {
            0xFA860E5AA61B867FULL, 0x7B71CFC486A3BB10ULL, 0x177640C3CDFF4F84ULL, 0x8527E78B96106F82ULL, 
            0x173130AF05CBBF55ULL, 0xBDC856797865E8DDULL, 0xACFCCEDE8DC96E18ULL, 0x8AEBC55AABDBB01CULL, 
            0xB4E5B28228C8DDFCULL, 0xC0BF663C6D05F106ULL, 0xDBBED131058D966CULL, 0x876D933AEC07CEF8ULL, 
            0x5E5B7B3AACB39F5EULL, 0xA635B64C7AC725DEULL, 0x0FC05C50630FB0B0ULL, 0x8FEAA6274BBC4E67ULL, 
            0x941D61B39A3CE6A7ULL, 0x91C98811E25EF90AULL, 0x1386496D0085513DULL, 0x9E6677004C97A344ULL, 
            0xF6A56CBEF782C085ULL, 0x5ED15F0769B33A5BULL, 0x485D9EA983B871BCULL, 0xF3F7A13337644E6BULL, 
            0x8427A2F5DF0D83ECULL, 0x307CAD222C505F2EULL, 0xEA1C1BFCEEFAD82FULL, 0xB37A700FB6A0257AULL, 
            0x4FEFF373EB376B2CULL, 0xE419F1AC7EB687CBULL, 0x9A822D27D4086DE9ULL, 0xFAFF4306A2A9780CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Menkent::kPhaseHConstants = {
    0x5E68449DE2FE9566ULL,
    0x40517F0B1E30331CULL,
    0x9AD712C9F77A5712ULL,
    0x5E68449DE2FE9566ULL,
    0x40517F0B1E30331CULL,
    0x9AD712C9F77A5712ULL,
    0x00FE355068585251ULL,
    0x13B01392F5F9AE7EULL,
    0x53,
    0xE3,
    0x49,
    0x18,
    0x3C,
    0x18,
    0x19,
    0xF6
};

