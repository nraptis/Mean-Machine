#include "TwistExpander_Mimosa.hpp"
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

TwistExpander_Mimosa::TwistExpander_Mimosa()
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

void TwistExpander_Mimosa::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xC925BADA392CED0BULL; std::uint64_t aIngress = 0x8D0A00814A1AF466ULL; std::uint64_t aCarry = 0x8524D4CFF1961B0AULL;

    std::uint64_t aWandererA = 0xAD7A14580FE7BE1BULL; std::uint64_t aWandererB = 0xA05A730AB86E0FBCULL; std::uint64_t aWandererC = 0xE6B7524794E3BA06ULL; std::uint64_t aWandererD = 0xB8CB1413F682E624ULL;
    std::uint64_t aWandererE = 0xF78AC295E05DCDEFULL; std::uint64_t aWandererF = 0xEF10E2738ED98EC7ULL; std::uint64_t aWandererG = 0xF99007345E67C04FULL; std::uint64_t aWandererH = 0xA437935104F437D3ULL;
    std::uint64_t aWandererI = 0xAFF71FDB456B2E94ULL; std::uint64_t aWandererJ = 0x8F668CD9A25A09C0ULL; std::uint64_t aWandererK = 0xF56DBA4D7E75E5FDULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17621992123537724242U;
        aCarry = 11906485412531953436U;
        aWandererA = 13033246148936474733U;
        aWandererB = 9282111357596234318U;
        aWandererC = 12289431368418506831U;
        aWandererD = 16052560802125036899U;
        aWandererE = 9602498272589087616U;
        aWandererF = 16938482178768130633U;
        aWandererG = 14158331526615540789U;
        aWandererH = 13382157969923955757U;
        aWandererI = 18184244195814196158U;
        aWandererJ = 14215450767360740744U;
        aWandererK = 13159828323618971205U;
    TwistExpander_Mimosa_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Mimosa::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xD1D9B3A95CDCAE73ULL; std::uint64_t aIngress = 0x8113E0A00E83795BULL; std::uint64_t aCarry = 0x8BB65761D464B582ULL;

    std::uint64_t aWandererA = 0xB4BC5512E4B7F6EBULL; std::uint64_t aWandererB = 0xDE7D8E010A284897ULL; std::uint64_t aWandererC = 0xD7D453149DA89B7BULL; std::uint64_t aWandererD = 0xCCB5D6BFC55D58D9ULL;
    std::uint64_t aWandererE = 0x853A9A5523E80623ULL; std::uint64_t aWandererF = 0xCC1C90A7342B0482ULL; std::uint64_t aWandererG = 0xD949C3C7EFD4EBD2ULL; std::uint64_t aWandererH = 0xA928C8B080C24638ULL;
    std::uint64_t aWandererI = 0xD5AF556C2F0D9113ULL; std::uint64_t aWandererJ = 0xFD90E3742CF6394BULL; std::uint64_t aWandererK = 0xBC7CE2562797FF06ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14266738258055698784U;
        aCarry = 9812933427811009305U;
        aWandererA = 11347840005325604175U;
        aWandererB = 10782969977659444855U;
        aWandererC = 10522990693845047149U;
        aWandererD = 18111499477104097604U;
        aWandererE = 15157698166509800646U;
        aWandererF = 17247657208723729390U;
        aWandererG = 15148133030208858702U;
        aWandererH = 9977486893306147701U;
        aWandererI = 15540755903708080113U;
        aWandererJ = 10613283458154242013U;
        aWandererK = 16772398084554828177U;
    TwistExpander_Mimosa_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Mimosa::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE16518CB7FA17749ULL;
    std::uint64_t aIngress = 0x8712D45F5F12B43AULL;
    std::uint64_t aCarry = 0xECE79E8C1B4E968FULL;

    std::uint64_t aWandererA = 0xF6B3161891BA57C2ULL;
    std::uint64_t aWandererB = 0xCAF89429E6477E51ULL;
    std::uint64_t aWandererC = 0xA2D5424958A8855BULL;
    std::uint64_t aWandererD = 0x854D41F141377F6AULL;
    std::uint64_t aWandererE = 0xE35D9E6DADD29ED7ULL;
    std::uint64_t aWandererF = 0xBCA9D2BE6FE01A91ULL;
    std::uint64_t aWandererG = 0x8E45B152AAD0AF4AULL;
    std::uint64_t aWandererH = 0xE50CEC1F6B7FE1CEULL;
    std::uint64_t aWandererI = 0xA93236E0A7A8B921ULL;
    std::uint64_t aWandererJ = 0xED821D93ED75A6D5ULL;
    std::uint64_t aWandererK = 0xF85BE2FF4A10DB2EULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneD);
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
    TwistExpander_Mimosa_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mimosa_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 19 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1794 / 1984 (90.42%)
// Total distance from earlier candidates: 32722
void TwistExpander_Mimosa::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1511U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 973U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 447U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1565U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1310U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1993U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 590U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1510U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 378U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1652U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 928U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 395U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 875U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 358U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1574U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1115U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 481U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1127U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 276U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 635U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 478U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 200U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 163U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 936U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1405U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 113U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 787U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 44U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 485U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 659U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1273U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 902U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1515U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1282U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1343U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1689U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1712U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1855U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 138U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1278U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 719U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1371U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1711U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 632U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1076U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1829U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 729U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1145U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1355U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 624U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 643U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 778U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1631U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1747U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1500U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 147U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 89U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2026U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 353U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 982U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 300U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 683U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 487U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1093U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 556U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 647U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 95U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 925U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 611U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 233U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 929U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 482U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 322U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 107U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1550U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 926U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 185U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 75U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1925U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 193U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1232U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 139U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1675U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1820U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1863U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1473U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 604U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 992U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 90U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 403U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 145U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1544U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1876U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 463U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1116U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1769U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 448U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1206U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1430U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1385U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1774U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1176U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2015U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1193U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1275U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 910U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1258U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 473U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 786U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 170U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 327U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 660U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1337U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 204U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 918U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1920U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 699U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1676U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1471U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1982U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 267U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 741U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1923U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 944U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1311U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1381U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 978U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 35U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Mimosa::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xB036B6870C8DFA12ULL; std::uint64_t aIngress = 0x90000A0482D9EF73ULL; std::uint64_t aCarry = 0xEF4C6594902175ECULL;

    std::uint64_t aWandererA = 0xF4E7FB0600BC90D6ULL; std::uint64_t aWandererB = 0xA7A77E72948704B2ULL; std::uint64_t aWandererC = 0xBA74E45726AE6CB9ULL; std::uint64_t aWandererD = 0xE1E087019A3EA84CULL;
    std::uint64_t aWandererE = 0xB550149907248012ULL; std::uint64_t aWandererF = 0xDA71FB8F85F7B1B2ULL; std::uint64_t aWandererG = 0x8D978F7CFD52854DULL; std::uint64_t aWandererH = 0xC010B108A59CAA53ULL;
    std::uint64_t aWandererI = 0xFC508C0356CE47DBULL; std::uint64_t aWandererJ = 0xF52F4C2C742C362AULL; std::uint64_t aWandererK = 0xEDACCEA906677CF8ULL;

    // [seed]
        aPrevious = 18116284260885044811U;
        aCarry = 15794757347465542604U;
        aWandererA = 14834808158993956709U;
        aWandererB = 12576877707423120646U;
        aWandererC = 13893514521302700728U;
        aWandererD = 11508768712489357742U;
        aWandererE = 17732553376349297930U;
        aWandererF = 15470624242318193730U;
        aWandererG = 17734896583500193718U;
        aWandererH = 9460797434342995772U;
        aWandererI = 15086815992446421247U;
        aWandererJ = 9224725069274463875U;
        aWandererK = 17779539502022938492U;
    TwistExpander_Mimosa_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Mimosa_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Mimosa_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Mimosa_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 19 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9815; nearest pair: 487 / 674
void TwistExpander_Mimosa::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3698U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5865U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2451U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4319U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4191U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8144U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 8040U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1584U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5829U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 499U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7167U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4508U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 8015U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8138U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1148U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 301U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1958U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 342U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1718U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 593U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 604U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 897U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 395U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 407U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1459U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 652U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1997U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1983U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1526U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1907U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 900U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 248U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1822U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1591U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 92U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1734U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 19 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 9794; nearest pair: 451 / 674
void TwistExpander_Mimosa::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6848U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1786U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2103U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3997U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6525U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2927U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1476U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2547U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5580U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7580U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5153U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5893U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6167U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1477U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1668U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1519U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 425U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 755U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 147U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1869U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1516U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 914U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1842U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1186U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 785U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 595U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 10U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1057U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1797U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1043U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1001U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1368U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1334U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 7U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 860U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1721U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseASalts = {
    {
        {
            0xBB82A315703AF11FULL, 0xF22AB945D1156157ULL, 0x5635CF14597E9EDAULL, 0xF464D4AE4D051410ULL, 
            0x1D2785C41ECE4817ULL, 0x9142CD19E109D727ULL, 0x0AF062732A3BD713ULL, 0x2A5CC13EAFAD0934ULL, 
            0xE57FFCD7623AE024ULL, 0x50D5D7EB7A501DAAULL, 0x00ECA2F0891DD565ULL, 0xCF319456BE42C027ULL, 
            0xC4B20071206DC675ULL, 0x6AFCC2E7FDD4916EULL, 0x6BB8EB3631DD4B6CULL, 0xD1DEEE7DC45820BFULL, 
            0xAD9F180555353EF4ULL, 0x9D68BE64CBBEEEF4ULL, 0x769CD4E1E06AAFE6ULL, 0x8B5E906A278D66D8ULL, 
            0x1614F6DEF8EA88BBULL, 0xFB2C8F6EF7DE2BECULL, 0xF4799D259EBD906FULL, 0x03FEED8BC95B9565ULL, 
            0x7C988626BA0D7003ULL, 0xCF2ADFBF55B4F6C1ULL, 0x37404EFD5A2E2A25ULL, 0x343038C4BACD6F8AULL, 
            0xA4B5F25EADD7B687ULL, 0xD146E8FCF2EE315EULL, 0x7156440AF1D6DD54ULL, 0x58BC2D4313707B80ULL
        },
        {
            0xABA6780D14BE2489ULL, 0xD32FA45C9622F75EULL, 0xB97FDAD7733491EEULL, 0x87DF49A8BBC884E3ULL, 
            0xBDBE190779250842ULL, 0xF3F972C107CBD5EAULL, 0x5F0E679967123512ULL, 0xF946491BD9DFDC50ULL, 
            0x7B0257D57C91AFA4ULL, 0xE6F88E5E34F9FE38ULL, 0x19F6B7912334E203ULL, 0xABE333B6FF781DBDULL, 
            0x474A4B3A3FFB3C5FULL, 0xDE6C7D4E0EAC7C8AULL, 0xCBAEA99E6A692B06ULL, 0xACDE5F6FE8888B1EULL, 
            0xE1E2111960E5A973ULL, 0xB36A303C1FAD2898ULL, 0x259EB21260FB2AD2ULL, 0xAB022B4B3F4D508AULL, 
            0xB8032F7DAEC1F201ULL, 0xEE075626E4364251ULL, 0xEE5C335EA23D2BA1ULL, 0x14CF1EDA88487EBBULL, 
            0x7B2E0764CF08FD4EULL, 0xE13823DE2B49686AULL, 0x1BB9743D8C136931ULL, 0x789EEDC04253573CULL, 
            0xBD5EB149F63C79E4ULL, 0x148BFFCB8A6A1A16ULL, 0xED9A3A06A9F72662ULL, 0x110D445BEBF053BBULL
        },
        {
            0x1CFD6DD036F4E2F3ULL, 0xFBEB59D99C7ADAC0ULL, 0xB2071AD4719714F5ULL, 0xA221B1B6EEB40AD8ULL, 
            0x31AC253EEC86B690ULL, 0x244BD89FCBAB968AULL, 0x6FE97D0E013118F8ULL, 0x18D104A6E66EFF44ULL, 
            0x9B2A90CC9DF51671ULL, 0x9F9ECF12B40E8EB1ULL, 0x7FB4BB684D4941CEULL, 0xBADAA78AF53AD551ULL, 
            0x67A12893934DF90BULL, 0x6B724D3AAD98699BULL, 0x78E0CA7FC971B510ULL, 0x6D2ECD04607554B1ULL, 
            0x8FFF58EFF26C21EFULL, 0xC900AB57DC2B86BEULL, 0xED7A940770B333C8ULL, 0xAAD161A40C8743B3ULL, 
            0x6B45157289328DE8ULL, 0xCA0FC75C1A674152ULL, 0xB8A45521279AF611ULL, 0x8845E8B86D1B3651ULL, 
            0xEFC0DF8CC91A079BULL, 0x35E2C1BEF44F014EULL, 0x88EDB65D5262DCDEULL, 0x0E5A1BAA479B49DFULL, 
            0x34148BF9133483EDULL, 0xE57CC78F24BAD153ULL, 0x9C4C81ACD69A9B94ULL, 0xE087E52625548F48ULL
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
            0x909997F814FFB508ULL, 0xF3F30EAD97C98641ULL, 0x95153B2BB7A42B9EULL, 0x5DECFCBDFBF03C90ULL, 
            0xC61EE65C1EAD268AULL, 0x0A85DF19884B3BBDULL, 0x08167F21EF10A8A0ULL, 0xF1475A098BE43CAFULL, 
            0x380E0124BD944BDCULL, 0x1689FC24BECE4C41ULL, 0x7756CB45F56911EAULL, 0xD0BEDFA1713AA418ULL, 
            0xCEDB5FAC410B9877ULL, 0x274A5D851A59EC55ULL, 0x203EC02EE673DFB5ULL, 0xC88FBBD8E659C7BDULL, 
            0xD0C4DE7624BA5AA4ULL, 0x4188D6A7EA7E466AULL, 0xF7DD5532BFFD73C2ULL, 0x01AF9B9940A700C5ULL, 
            0xC232237104E4DBF5ULL, 0x999CFB36497C56D8ULL, 0x3668A86AB0D64005ULL, 0x3E87EC46C115C389ULL, 
            0xC9186EB7B1C9A133ULL, 0x054B868D7C560612ULL, 0xEA482CA3A05BB3D9ULL, 0x32DAA446A9D27437ULL, 
            0xE6B96806CD50F7E9ULL, 0xF0E44C895D2AF98AULL, 0x87CF592B2BFD9CB8ULL, 0x976BDC3B92A8B7E9ULL
        },
        {
            0x2D446AA4CF592B43ULL, 0x226A797E19AADAA6ULL, 0x499B6295330AF342ULL, 0x097B9AF0CB482F7DULL, 
            0xC1F402B0858CBB7FULL, 0x6A5EF2B4D56D56EAULL, 0x5EA87238BE6AB9EDULL, 0x3A22389ACD2726D8ULL, 
            0xEC87F69BFAF01F33ULL, 0x1B9AB008714C2CE8ULL, 0xA3B4169995C5CE5FULL, 0x9BF0E15471180BEDULL, 
            0x44FAE39729003D9DULL, 0xED04CD5EC58BD146ULL, 0x5434AB41EAD19D9BULL, 0x7BF983F23EE375CFULL, 
            0xE0E9906CD4D2D12BULL, 0x24F9F0C9672647F6ULL, 0x832D675D8F0896C5ULL, 0xB051594101BC9B11ULL, 
            0x842711E0ADD671DEULL, 0x596EF33D325AF4BCULL, 0x3730E60979BF711BULL, 0xB35975BDB6A6666CULL, 
            0xCEB505F93F318228ULL, 0x0B76C0441718F776ULL, 0xB5B55A35CC4A0FBEULL, 0x71C236809B19045CULL, 
            0xAD1068C046C3B5DAULL, 0x65533571A29B8A5EULL, 0x5004BA856E1E647AULL, 0xBE394578D54543C6ULL
        }
    },
    {
        {
            0xB50DA791F676CAFCULL, 0xAEBC735B14E751D7ULL, 0x681F91E394AA8D3AULL, 0x3C0C4A584D1A38D4ULL, 
            0x166FD0E49C2AD661ULL, 0x8869AA252940DB69ULL, 0x9CF4AE909CB8C54AULL, 0x1CCF08930677ED4AULL, 
            0x512AAD0F69E43F12ULL, 0x6637C0D8D626D4F5ULL, 0xCB585354C5C2502DULL, 0x65F684D4D419DB28ULL, 
            0x226B9D6FEA6F8B27ULL, 0x4FB503C688E14BFEULL, 0x7D031E3588DBE75CULL, 0x57281BD2FB3958FDULL, 
            0xB5C56617A62535CAULL, 0xA8C9B1DBB1E3ADB2ULL, 0x378110AA77736CB2ULL, 0x965B7256DAE75252ULL, 
            0x0F0FD1420C16CF1CULL, 0xF8B6D3A1B6A432F7ULL, 0x603A3BE9A1DB1B12ULL, 0xC80D3F7F2AF14CF8ULL, 
            0x101789D9CA410701ULL, 0xD952CFBDB0924506ULL, 0x2CAFB7A34A7AECE4ULL, 0xBBE4A0C16B66B952ULL, 
            0x9AB2B1CC108F3E1CULL, 0xB7F6D21C01E504D0ULL, 0x461D2647AA6A7C02ULL, 0x243EDADED8E4CE44ULL
        },
        {
            0x10896EF1CC58707DULL, 0xE2DC88F0E8634F8BULL, 0x53011A79568C8EEDULL, 0x68CE8E294455E313ULL, 
            0x3D0E29E8DA5D144FULL, 0xBE4A595D97FB1A95ULL, 0x972F288A93628E91ULL, 0x930E28C868FAB0AAULL, 
            0x7EB79FFBFD63CDD9ULL, 0xF871B6B40A4ACBBBULL, 0x5D6892A39E5C324AULL, 0x937FDBAA7691E1C0ULL, 
            0x021E531C296744FAULL, 0x45B5BB4628CC6FADULL, 0x439D8A5DCC8608EFULL, 0x9494CA2483A4F6C5ULL, 
            0x326F924F415879BBULL, 0x61F983A0F0770E55ULL, 0xB7E522CC04AD0086ULL, 0x8098D3B9974C2B23ULL, 
            0x3838634AC5C1EAA7ULL, 0x19DF7E8445EDCF6BULL, 0xD125ACBCBEA421C2ULL, 0x82A8533A63517924ULL, 
            0x85D72AE341A7580CULL, 0x3F281642DB363D86ULL, 0x19CA2E1AEA266094ULL, 0xDC4417425436EDE7ULL, 
            0x61955B82A33B5613ULL, 0x00F5D65243CC3AA7ULL, 0xFFF4D4BF05B71DF6ULL, 0x1F00B488C36411E9ULL
        },
        {
            0xEE8DD583E8FD4380ULL, 0x1EEC38FF9366218FULL, 0x82665CDE6132F2F7ULL, 0xFE2EBFD88F88872BULL, 
            0x32926E13B96CABEDULL, 0x034D4CB73544EC56ULL, 0xFC7BB7F3D4975771ULL, 0xFE0F64F10AA49092ULL, 
            0x6A6CFF2995981D42ULL, 0x6B7FA5D5C1B53D9FULL, 0x29A8C6CEAB3D0950ULL, 0xB762F56209323584ULL, 
            0xE870FB07E2E6E64AULL, 0x5275CBEA4DA26DB0ULL, 0xB5C84643146CABA5ULL, 0xCEC1E76860D55AE9ULL, 
            0xAB9C81ABDBA32B8AULL, 0x26B7929A1A73813AULL, 0xD1019F77CED738F4ULL, 0x0C823C010C28DD94ULL, 
            0xA1809AE0D29BD37AULL, 0x2945FE18CCCA4065ULL, 0xC4AF64F1192511D4ULL, 0x4FBB65D8D9598A9FULL, 
            0xB0C7B0B3895B7B6DULL, 0x551C74134D69FF35ULL, 0x28749FDCA628AD2FULL, 0x41F524188BD9D994ULL, 
            0x2FF777F21F68A3A0ULL, 0x0E43CF75A0221BC1ULL, 0x52E538E09F1DAB3CULL, 0xBE8A5E0D124F6E0DULL
        },
        {
            0xF7AE8EEF4933610CULL, 0x70F2A7FD39A65B46ULL, 0x94486141209D8482ULL, 0x061F62325BAA193FULL, 
            0x6D791889279C16D2ULL, 0x11A055E02F7A2D5EULL, 0x87E777EBA287DA9EULL, 0x6F4754CF80C0E5C6ULL, 
            0xA7B3A64189FF277FULL, 0x65C21C7E05D59E8CULL, 0x2B7EC15F5F91D722ULL, 0x8BD844573BA808E7ULL, 
            0x03314F60A869C86EULL, 0xAE10F50169C6AE4FULL, 0x9B2B57A16BE21A15ULL, 0xEE98A36A23A30932ULL, 
            0xFE573A5E9AEA3A94ULL, 0xCA8CC108A73AE3A1ULL, 0xA5F9CD2711D6F87FULL, 0x72AA9A836C5E53E1ULL, 
            0x627AD544FC0CE83AULL, 0x13BD734504EBE881ULL, 0x350D5D2B1F4C95B4ULL, 0xE495CD217F6037A9ULL, 
            0xA0806FFF1A6211BEULL, 0xAEC1E759C4CE1F47ULL, 0xBE4375ED766D0DA9ULL, 0x5A47CAB84D39BF67ULL, 
            0xA13E1298DF7C81DFULL, 0x7DABD8344E1FFCAFULL, 0x2485CA0AFFA9C540ULL, 0x5B8B3EA501CBFFC8ULL
        },
        {
            0x662B1B87B2B08395ULL, 0xD06768BF33617A21ULL, 0xCEC30960D0078E48ULL, 0x73AC34DB552C1063ULL, 
            0xA6A5904D9393EE93ULL, 0xA1549F009B1F1535ULL, 0x2688D24238254D14ULL, 0x95258A9998F2CB82ULL, 
            0x49B6A8E3FF5EC9EBULL, 0x6594FB05ECDFFF35ULL, 0x51E0D13F5C5BF2B0ULL, 0xD408C365F49D587FULL, 
            0x6F79CAF7562E8E10ULL, 0x3E7ED1F82ED192F2ULL, 0x9AA4F457E34ACC34ULL, 0xC259B4450D7EE418ULL, 
            0xD66269CA64056B41ULL, 0x0C7CA683A7B9141CULL, 0x0B1B84ED3D3BA273ULL, 0xEC1D87A4A2838555ULL, 
            0x69B0F2EF6E95DFE2ULL, 0x9A06FC68593B233EULL, 0x13C6E927BBEAC449ULL, 0x351534C5151960F1ULL, 
            0x06629BBD3657D4DBULL, 0x14C6C81BF00ABAA2ULL, 0x966D49339BD730E5ULL, 0x85C937CFAF29DF94ULL, 
            0xF10907E9FACA287FULL, 0x2EA1A9E1C2AFCC73ULL, 0x0E84162FB62E0977ULL, 0x769609BD668B3899ULL
        },
        {
            0xEDC5AD39F8607A2FULL, 0x80D34A23FFED9C8DULL, 0x1217B69B1078527BULL, 0x88547C51714BE855ULL, 
            0x6EA47B1796F796ADULL, 0x89EC8BCD678F9FC4ULL, 0x15FF2DFE09D74390ULL, 0xF59FC12166BD50B7ULL, 
            0xDA89FA1E0D2FE6CBULL, 0xA5A53CD65E327973ULL, 0x4EDA71134EA09C33ULL, 0x1FCD03176E182B5BULL, 
            0x06E9732A1227BB91ULL, 0x11553197D7971006ULL, 0x561958097C6106E5ULL, 0x2424EF8100B3294FULL, 
            0xC487056D6109A65FULL, 0xA2511715983E0B2AULL, 0x042ECEF190E0BA1EULL, 0x78C6869FAB3E548AULL, 
            0x4A1F906864CA8CB2ULL, 0x3E3AAD6575079279ULL, 0x6D3B14965460D8F8ULL, 0xAA15753CBF3D1F49ULL, 
            0x7839B19F6AE5611CULL, 0xDB4E6FC943245EC8ULL, 0x1B7395D526423A53ULL, 0xEEA8542F31891DD6ULL, 
            0x1CEA0FC53FA4422CULL, 0xCAA24A70F0FD0F95ULL, 0x5B765105BA5E0293ULL, 0x8DAD69F9D94D2136ULL
        }
    },
    {
        {
            0x4D6194694D65C979ULL, 0xC3BF9549AC4B39ACULL, 0x5BA7747AE10DD990ULL, 0x2A08A49F233A982DULL, 
            0x624887AC07A599FDULL, 0xE75E9324D03A4771ULL, 0xA6594498668BC15DULL, 0x80801B650140337FULL, 
            0xC19B23122C236343ULL, 0xDC93580AF292BF32ULL, 0x381AF7A2BA9934E1ULL, 0x9B328FEC03383683ULL, 
            0x442C1A5457952334ULL, 0x551CDE378B2C32D8ULL, 0x422873A88E2CF29BULL, 0x0F9366CE0F6BD04AULL, 
            0xAAC015ECB99EF71CULL, 0x0A7AA8166CE8FE97ULL, 0x5E1A1B7BCC58EFA6ULL, 0xBFECBFCCC0ABE55DULL, 
            0x0D849683C8D6B47BULL, 0x4E7E636BCCB5498AULL, 0xF0A1DB3973789098ULL, 0xE11496643B6D79D6ULL, 
            0x90750CA04ABB8FBDULL, 0xA4E3A5BD13CF11F2ULL, 0x5002528C907D640EULL, 0xAB320E8B26B635BDULL, 
            0x8E9AB871388406A3ULL, 0xDCB3639896FEEC89ULL, 0x3D28DCEA2A91C872ULL, 0xA0398B694577B9E8ULL
        },
        {
            0xC67332ACF3206C57ULL, 0x77701786EA0DC683ULL, 0x2D1086C3371AEB28ULL, 0x05733C844FCA3772ULL, 
            0x4F660132768017BAULL, 0x6AED3B3180F66DE9ULL, 0xA703DB0866839DEEULL, 0xB04536B8CF648778ULL, 
            0xDA14A3BA37760C40ULL, 0x90EA970226DD499CULL, 0xE05CD139E927635EULL, 0x844C65C11ED8F177ULL, 
            0xF437630C0FCC3BCDULL, 0x578890770FA2D742ULL, 0x064454D03BE1108AULL, 0xCEDB7B1F05D392E0ULL, 
            0x489D53C201379C66ULL, 0xAFA8B0F5E54EF11AULL, 0x19E010A77E6D328DULL, 0x4F50C7258B335E75ULL, 
            0x14ED4C377D5A71DBULL, 0xA5B43B2947D4432CULL, 0xFB795A037D5A56A3ULL, 0xA5AA4EFBF0F5E8EDULL, 
            0xE513B21BC7E0122AULL, 0x7881131DDE7376D3ULL, 0x1BFB4B659D4FD794ULL, 0xB1F685388C5DA08AULL, 
            0x2FFB1214821B3B9DULL, 0xC18E2D3747042872ULL, 0xF49B9B597AC362FFULL, 0xABBE59CD854FC0FDULL
        },
        {
            0x78484CAA3CB16262ULL, 0xD92FE64F47D93266ULL, 0x5EE3D3F6A67D36BCULL, 0x65FAFC428682CE8AULL, 
            0x53AE5DAEDA95F97BULL, 0xB26BF8E6B95713BAULL, 0x369AC3F20F6812E5ULL, 0x1184D99968B6AA7EULL, 
            0x36882CFD84E89228ULL, 0xF8B3351F00D50C23ULL, 0xD0B091AA02BDEBBBULL, 0xDCE5D7A42984568FULL, 
            0x302676EE0D38DB39ULL, 0x1A78643A9444F3C4ULL, 0xD8D611B066052E37ULL, 0x025E4BB3141F50FBULL, 
            0xD4B9ED7AA8AE5C8EULL, 0xF6447F069788F29FULL, 0x8058B7010C8419FEULL, 0x9B2FC87B1B968FBFULL, 
            0xE4DB2DC64B316F1AULL, 0x5D8E7966996BED62ULL, 0xA50E96E88D853C24ULL, 0xD4A33E36613435B1ULL, 
            0xCE41697C14CF9ABAULL, 0x17A5A0078E8EC565ULL, 0xB6B6B397904D6C41ULL, 0x0BF1C0536849AD74ULL, 
            0xABDBACFFA5DAB7C1ULL, 0xDF050B3F49ACA4CEULL, 0x358BF879C3A46E69ULL, 0xA4AF6603484355ABULL
        },
        {
            0xCCD3C06477DCD97BULL, 0x93E60412923A5754ULL, 0x480BDDE2F045946DULL, 0xBB0C5146AFB99C62ULL, 
            0x68EC2689B608621CULL, 0x9908BF69450652A2ULL, 0x69EA511198551FE7ULL, 0xDC51F0472EBDD8C8ULL, 
            0x6AE06080CC3DCE48ULL, 0x0A71D9DE2D74270EULL, 0xB92C3728D4C0A610ULL, 0xB905E1B8D33C4656ULL, 
            0x7D509C6A631CAC7FULL, 0x5B2C2DB2BF92BAFDULL, 0x23F209A8858BC009ULL, 0x502F7866E91CB22BULL, 
            0x686CAFC4765208A7ULL, 0x9B372C6573D31917ULL, 0x4EC4C68DDD0F7E10ULL, 0x1CEF6B75441E233DULL, 
            0xF04E6E69A25CA0A2ULL, 0x74C589ACB373B113ULL, 0x53044ED20708D7CDULL, 0xE59CDC42C51D81EEULL, 
            0xAB2A7A28AB0802ECULL, 0x56B43C622C07C445ULL, 0x93FB3FB6CB6B6905ULL, 0xE0FDBA72905EA68AULL, 
            0x871B2A8BAC70384CULL, 0xEFA474F79F80DA9FULL, 0x8DB59675C9945241ULL, 0x4C919B109A9FB6E5ULL
        },
        {
            0x9EC60590F48289CBULL, 0xA362BA33160DF849ULL, 0xD0CA989144FC2496ULL, 0xAD7EED0F458F0367ULL, 
            0x73ACE4D1205F2C18ULL, 0x9DEA76DD34C528FEULL, 0x8C621A942BE8CD52ULL, 0x8CC4F03CB73FDE91ULL, 
            0x381B949AC6A3006BULL, 0xE1EC12960C587A77ULL, 0xC74DD16A4E64CC68ULL, 0x375AB2555A590DF6ULL, 
            0x3C344B81C0E94897ULL, 0x2D9BAC13583397B6ULL, 0xA27B47EB29DD8CE8ULL, 0x859B0D7F116F7616ULL, 
            0x40E9A908E5B0A583ULL, 0xE753494B316A4B51ULL, 0xD53CC59721EC3491ULL, 0x5B930C64D1E4F0F1ULL, 
            0xACB4EFE15AE0CEB3ULL, 0xEF71E6B084F33DE3ULL, 0x0261846A80B79108ULL, 0x6BF6E6948D52CFF8ULL, 
            0x8292288550E888EBULL, 0xF77E0780182D59E4ULL, 0xB775D2FB5F847434ULL, 0x330F2968F99A7402ULL, 
            0xD9137DF170A38DE2ULL, 0x07E3F9227669F9F8ULL, 0x9A4BC381FD6D6703ULL, 0x671E1FBFD37F789BULL
        },
        {
            0xB26847C193B4D6D2ULL, 0xB0434DECCC09A885ULL, 0x337FD24344DE942FULL, 0xE6497DAEE085B1FBULL, 
            0xEC18239235266B81ULL, 0x9547B71213DB3402ULL, 0x837199264D419EDCULL, 0x0B2E860BC96BD2A1ULL, 
            0x61A1E13CF96529F4ULL, 0x5935798284D9C344ULL, 0x5B6D7228ED2B724AULL, 0x377C42544163A4F1ULL, 
            0xD8560EB2C0E076C0ULL, 0xA27D05594F60708FULL, 0x6C54E45FA6ED7804ULL, 0x26F3F9C372780F9BULL, 
            0xD8836BCEBC3AF8A1ULL, 0x1EA085600FAB11A4ULL, 0x5A3EEAC7B0CCC38FULL, 0xAD7314C6FE6FB79AULL, 
            0xC2031F2B36AC8B70ULL, 0xA195AC59116EED06ULL, 0xA6C4C648CDAECF56ULL, 0xAD24FB1D03257704ULL, 
            0x60FF0CA86412F587ULL, 0xD54C05CF332ACC95ULL, 0x5D20EE4D2FC372F3ULL, 0x245CB5E6AF9A82D7ULL, 
            0x8EDDD45D33209DD2ULL, 0xAA7FF545A90C78C1ULL, 0x9584E15C7A109F7EULL, 0xCFC43F3E3501F320ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseAConstants = {
    0x6183522738F3A1C6ULL,
    0xE72C13D905D6F49FULL,
    0xBDE7A77503D26845ULL,
    0x6183522738F3A1C6ULL,
    0xE72C13D905D6F49FULL,
    0xBDE7A77503D26845ULL,
    0x2CB34864EEF5FF72ULL,
    0xB45635B7B2A90CCBULL,
    0xED,
    0x2C,
    0x66,
    0x28,
    0xCE,
    0x4C,
    0x8B,
    0x73
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseBSalts = {
    {
        {
            0x4F0C75F410304344ULL, 0xA0E29F0AA64B7A46ULL, 0xD230569A667BEA17ULL, 0x6ADEEAB5BB973D57ULL, 
            0x4D18C570F2708C30ULL, 0xE5AAAAC2970D1889ULL, 0xB661A65E969AC8B4ULL, 0x5DA4971482228AD7ULL, 
            0xEFA199DFDDD5BDD6ULL, 0x6E39CBC9F8FC08C5ULL, 0xEA26AF65EEEA3ADEULL, 0x22E12B8FEA2057A8ULL, 
            0x3E0382CA7FD2CE28ULL, 0x4833F00F8ACD91EBULL, 0xD0392CED6CFEE2C1ULL, 0x53DF19E571D5924BULL, 
            0xF95BE72261EE09C9ULL, 0x1864A3D35EBFE373ULL, 0x7341DED16E850607ULL, 0xB103B21CA04C29A8ULL, 
            0x928B7CE21C8AE7F9ULL, 0xE1C4B8790C3FA1F0ULL, 0x704AE8B516D4AB9DULL, 0xBD348576E3129E57ULL, 
            0xE41169C6027BDE8BULL, 0xA921B108489CC4C5ULL, 0xB92482BA8909E1ABULL, 0x1F7003CD96C3DF05ULL, 
            0x1FE01C0FBBC7216FULL, 0x3134D33EA239B9F3ULL, 0xA2DC69DE6800C4E5ULL, 0x96533E04BEEF0A8CULL
        },
        {
            0x057E51696F7FDFB4ULL, 0x3F9442E8A12ABAA1ULL, 0x6A42EA0860169672ULL, 0xD838F1A117E3544BULL, 
            0x3C3694BC91831002ULL, 0x40550AA7596A6479ULL, 0xF9AC0E746E068270ULL, 0xA245EC0B035F524CULL, 
            0x2376F588AD58A4C8ULL, 0xC717D7F433E455F8ULL, 0x977523C018F5B566ULL, 0xFC5034141934292DULL, 
            0x5DC2865904F2C198ULL, 0x4DF4BEC143513E75ULL, 0xD6E25E9D1B65BEF1ULL, 0xE550069FB07F2B69ULL, 
            0x222CCF02D7E8AFC5ULL, 0xBEB52EBBF5454FB3ULL, 0x75B9181F9A6B3D57ULL, 0xD6B239E77F76F80BULL, 
            0x85E49311172C86C6ULL, 0x71271C786B3BC8D6ULL, 0xD6DA6CB291C25549ULL, 0xA8B6A1E26FD45B5EULL, 
            0xE07D1C8F0C733305ULL, 0xB4697F5CBDA24AABULL, 0x1A46F943DF96447EULL, 0x8BAFFC303D979B77ULL, 
            0xDED42A3F74304154ULL, 0xC5AAEAC9E647EE07ULL, 0x185AF6B1E136A6A3ULL, 0xFDB1F9E9F6A6C863ULL
        },
        {
            0x8C985FD06809976AULL, 0x2026FB395F2C98DAULL, 0xA1786BC5F168639CULL, 0x35FBECBB1A80BEA6ULL, 
            0x6A6EC0286DF6B450ULL, 0x6F94F721468390FCULL, 0x80AA5FA5C1F9B00BULL, 0xC799E045716BDDEEULL, 
            0xEE12C3E3C0A34986ULL, 0x25372D211CEE037EULL, 0x0D6F0BE2EEC76429ULL, 0xE9AEA21208114090ULL, 
            0x4E0341750CC82597ULL, 0xC9BDC3BCE5413CACULL, 0xD7A7E199BE0009CAULL, 0x08507C739D195B9AULL, 
            0xB06BF64B74A50DC5ULL, 0xA0E51E11DB10C8F7ULL, 0xD94DEF2034EA389EULL, 0x52126E425E7E82EAULL, 
            0x4A6A66BFD5BFD411ULL, 0x82EFB31EBF8799ABULL, 0x4470A58963FC1D0DULL, 0xB759678FD60C8992ULL, 
            0xE00AC7310B5105D2ULL, 0x9473469C7CF8789BULL, 0xC7488A6BF15FB775ULL, 0xF388128524980F92ULL, 
            0x951F124173E33289ULL, 0x0B2300CA89CC4102ULL, 0xD27A688FED66518EULL, 0x98DE626F8353D0C9ULL
        },
        {
            0x4824C1B726E64DE9ULL, 0xAC394A605C108EF5ULL, 0xCDF47296ED812613ULL, 0xCC6264A75A26A816ULL, 
            0x250DC47CDE076428ULL, 0xA8DE370C37151361ULL, 0xA344D9F0C1A1B25CULL, 0x6DFD772F57A6CB48ULL, 
            0x62DEF2E76355ADA1ULL, 0xFFCFEC3E9F7AED4DULL, 0x7CF9089C75F636A2ULL, 0x28D2FAA9F29B41B5ULL, 
            0xE6176A2FFF9C325AULL, 0x27AFE86CF6AF2E97ULL, 0x5233C679AFA32BDEULL, 0x43D8B4B023FAE029ULL, 
            0x03B2CEAB5D6F64FCULL, 0x147D42B94747F508ULL, 0x764EDDF60FFC7BBDULL, 0x9C083F7C5929990CULL, 
            0xDF67D195C684F7ECULL, 0xEE8CEC216802AC99ULL, 0xA35E08A2AC1FAE8DULL, 0x93D66A5C5D19530DULL, 
            0x9629529CFC3D7631ULL, 0x4C81758B2DCC5442ULL, 0x92BB9B2A8D53EB6AULL, 0x522C37FCC9774436ULL, 
            0x361DFEEEC630C90AULL, 0x3E241D7A2E9D735BULL, 0x922025F8632C6EBBULL, 0xDD2B4D31BCA79162ULL
        },
        {
            0x0F114B9BDE0DA6DFULL, 0x824306F3E93E25D2ULL, 0xF9FBD6500358B46AULL, 0xA4B4CE35610BC8AFULL, 
            0x52FB471AD548B018ULL, 0x3446C506645E00BFULL, 0xA78136FAD621462BULL, 0xF5CE82809B120379ULL, 
            0x2999F2C43F270DB9ULL, 0x599BC313C3B7995BULL, 0xB7309C3AF5CBBF62ULL, 0x51AFF03BBFF03BE6ULL, 
            0x83EE8F611E68185CULL, 0xF39DB01FE7860A1FULL, 0x9E53DC8AE78F8921ULL, 0xF41D275F22C78F81ULL, 
            0x826B61F04F7AE584ULL, 0x2C7D95AC0D7B6933ULL, 0x2A81974DEF1C9538ULL, 0xF1AAFAF13DAFB8F5ULL, 
            0x7C191FCEA933724DULL, 0x82096F98D0881226ULL, 0x104DDD874350A1CDULL, 0xA80E604578395B6EULL, 
            0x25F97237D76FC1BBULL, 0xA8E223AE5C8A286BULL, 0x9989B3F2E0EE9005ULL, 0x81AE0C89937C6407ULL, 
            0x659BED2BCF625482ULL, 0xB1F940902FCAC00EULL, 0x787B0834A4C33BB0ULL, 0xDC8F56218D53BE42ULL
        },
        {
            0xA71C28E97CF09AD4ULL, 0x18B6A4F1512AF935ULL, 0xBE0B60092D9919EBULL, 0x54C1B3AA22A26560ULL, 
            0x85FB81C547406AFEULL, 0x624A1E8B6F844760ULL, 0xBB9B92E0C6385B53ULL, 0x1A531E31A5C5E114ULL, 
            0x25195B9BE1A72659ULL, 0xD334BC04BD3A37B4ULL, 0xB05DBA78E1D3E736ULL, 0x35E1E963B67F8283ULL, 
            0xB6B0AD26F44B3CE4ULL, 0xEEEF4F438C75F406ULL, 0xB5DECD439DBDA89DULL, 0x473D2DDB7ADA3F79ULL, 
            0x300DBC274D73713DULL, 0x0AB2E560D87A171EULL, 0xBC48FAFCE131A1B2ULL, 0xA1B313E9E36925ADULL, 
            0x538D985FC1520734ULL, 0x16615B61884A857DULL, 0xB798F3E1563D4BB8ULL, 0x30CBA6E08DCCDFF4ULL, 
            0x0F4FA2F0D84F443DULL, 0x7AF2C9479D2155C0ULL, 0x6F94EE14CE4E18C0ULL, 0xF1EC3D0D2D9B5573ULL, 
            0x8C915B11F5402A2CULL, 0x5CFD6AA81596BFD9ULL, 0x11D5AA7212BA0B13ULL, 0xA14E3B278CEDD41DULL
        }
    },
    {
        {
            0xAC8FCC6DFF8E3DC1ULL, 0x2D89B0BDDDCA12F5ULL, 0xA7220901C6453E5EULL, 0xE9D2D255F8EFA60EULL, 
            0xEA682F8F2413090EULL, 0xE1218FB6B17C2A99ULL, 0xE7BBCBFA4FD0E684ULL, 0x53EBA87C6C95A278ULL, 
            0xEEAA927C5750881AULL, 0xE2EDF8DBF71AA6B5ULL, 0x0C76C995EAB4A14EULL, 0x60370DADC0879230ULL, 
            0x47429497DA144BC7ULL, 0xAEED77AEFE7AC3A4ULL, 0xBA2F24298E1986DFULL, 0x7C566E1635C6482BULL, 
            0xEBB6CF24773C465CULL, 0x5E8C611C02410F99ULL, 0xEF6BD18CA36AEB08ULL, 0xE8025463A7D85E21ULL, 
            0x500A4674AC05A0C4ULL, 0xDDC0EFB3DA7C7B13ULL, 0xDD8EB0090CF2ACF2ULL, 0x6AA7BCAD080C9510ULL, 
            0x4D3059CC36D3B182ULL, 0x2471DA0A127ABA4EULL, 0x4A566DD5A71FCABCULL, 0x8509CB383DBD53D2ULL, 
            0x9F73D8BAA815070FULL, 0x4E653972CA7EB49AULL, 0x032D3E9D122789C0ULL, 0x30484EE5E9FCE792ULL
        },
        {
            0x84E625DD560D51E0ULL, 0x9C11373C12C7B7EBULL, 0x3DA4073334404289ULL, 0x430580693E60F2C6ULL, 
            0xDFE0D14097482A36ULL, 0xDF07A5746A34B13DULL, 0xBFC1EF85CD70A8A8ULL, 0xDF01C64E90D3548BULL, 
            0x5FE8B23A7C70DB3BULL, 0xC08BA9634C166EB0ULL, 0x2DD0B680FCBC2ABEULL, 0x02B3622177119E47ULL, 
            0x585201902D8FD9ADULL, 0xCBA7E31585566F50ULL, 0x11833A8DB146BF9BULL, 0xA14A0688584FEACEULL, 
            0x885B14E076E6E184ULL, 0xF626FCFC9AFF8FCAULL, 0x3497FB89EF0B7DF4ULL, 0x9B7627848CB7238DULL, 
            0xF07E88CA37080056ULL, 0xABE45EAA1D7C8F2AULL, 0x266EEC96B0FA8009ULL, 0x1BEEE8410874CDCCULL, 
            0x1A56041F5F8D6089ULL, 0x506C9531D2940F9EULL, 0xAFBF0F355D0569CCULL, 0xD15BDEC098EE07D6ULL, 
            0x1B6BAB66DA24A5B1ULL, 0xE1E8E9822223167AULL, 0x09FD1FD48252B3ECULL, 0x3A2A283A27FEB97DULL
        },
        {
            0x9153B4F4DCD16D87ULL, 0xA40C6F603CADED01ULL, 0xCBAEDCDE5756ECE6ULL, 0xFEA749767758F0D8ULL, 
            0xB2A38A06E1026D37ULL, 0xBD5887E340704E8CULL, 0x9A255673F5362075ULL, 0x02FBD377AAAE5980ULL, 
            0xA7B8E954651000C7ULL, 0x9FC164030E16BB8AULL, 0x7EFC423EEAF85434ULL, 0x6B068862D96333BAULL, 
            0xF4DADFE414684634ULL, 0x5D03AF6EBC0AC014ULL, 0xB5271C098E7BDA77ULL, 0x4B91231CEBE4C207ULL, 
            0xD45AFCE439555F1FULL, 0x31F3C6217BE48FBCULL, 0xBD07160DDCB4430FULL, 0xB4166C9F60C43E18ULL, 
            0xD0EEF4A942CCB141ULL, 0x027BC2861222ADF6ULL, 0x5B71083E6E810927ULL, 0x74C755E2E3085D8CULL, 
            0x716D05A5622460E2ULL, 0xD0D3F53DBB8F5082ULL, 0xC2B977A22F24A2E8ULL, 0x23508B9D5B6335A3ULL, 
            0xA428640FFDE15293ULL, 0x11C6EDAD32A70560ULL, 0x2AEFA08783FB8A27ULL, 0x20CC1AFC6D98418CULL
        },
        {
            0x7B0425F6C04D5F8AULL, 0xAF1F495F77B37335ULL, 0xE6ECF678356962FFULL, 0x4698FABAF5D07C37ULL, 
            0xB1B52C9FC530D50CULL, 0xD34C2EF1B4427CC9ULL, 0x95AA909A71B321CFULL, 0xF92357E4060D649CULL, 
            0xCEF0C8687B5D4D65ULL, 0x39FFF104BBB0B6D2ULL, 0x66EBCDD75D0EB905ULL, 0x4A9AF649B18894EBULL, 
            0xA9CACC8985EA2909ULL, 0x91BEB851C2D54E3DULL, 0xC7122D7A7C792179ULL, 0xC1240933054CA50BULL, 
            0xDD12A1914A047DEEULL, 0x6BFCEFD4BA18820DULL, 0x550C40143F46EE66ULL, 0x582BCF17D48F45BFULL, 
            0x4EE13EEA5FD7D871ULL, 0x18001683A7250739ULL, 0xA9C4E22647768D32ULL, 0x2F6472A0855A83CBULL, 
            0xB4EA9EFA0B8FD95BULL, 0x01930D10B33D357CULL, 0x0ECFF377919911DDULL, 0x0E59B07821DBC51BULL, 
            0x8755E7BDBA758BF9ULL, 0xF4BF389B22DBCC12ULL, 0xE1B470F023557EC2ULL, 0x690C362151E5C16FULL
        },
        {
            0x038E2FC6A9470337ULL, 0x6E07D7E0D77A3D83ULL, 0x237D0378626FB7B7ULL, 0x25EBA751D2DB2A99ULL, 
            0x161DDB9B2C1980BCULL, 0xE1B2D82BD418C830ULL, 0xF4744F2C740E45BDULL, 0x6AB4556D02511344ULL, 
            0x4ED501A0EBA5982BULL, 0xFC8EBF2A7572ECC3ULL, 0xA9A165CF06477315ULL, 0x333A0390640771A8ULL, 
            0x5C1364FC17B84187ULL, 0x7A4FFB443E714B35ULL, 0x8BBB089D0B1DFFE3ULL, 0x8D5A9133A0FE4957ULL, 
            0x8056B8F8F7FCCBDBULL, 0x3DEA546F936FD52BULL, 0x627160DBA8732937ULL, 0x3BEB54D96FC98A6BULL, 
            0x2E7DD35742163565ULL, 0x7389254386781B7FULL, 0x5128D9D9E660F831ULL, 0x4C94CDE29FEBE242ULL, 
            0xD0BECF6FC2C76A90ULL, 0xDDB69B19C319B1D0ULL, 0xEF41BDA72A643A66ULL, 0x9DB2DE182E872C39ULL, 
            0x6B48CBAA5454B59DULL, 0x744B86BC3394F178ULL, 0xD2C321F83DF75EB8ULL, 0xA2BDB7B39351FE8FULL
        },
        {
            0x4389D892B91B22CCULL, 0x7268EEBD47DCC77DULL, 0xBB136853EEF604CFULL, 0x8737133D8C4323ECULL, 
            0x2F491C137036EFACULL, 0xB7006AF350A02546ULL, 0x86D396FFB9FB1841ULL, 0xF0BD91D0516A865FULL, 
            0xEC49C590BB46793FULL, 0xFAF12159BE06EE1CULL, 0xE5BD89B7D3F7D7DBULL, 0x01DEEB7900509DBCULL, 
            0xC4E34F06573A5732ULL, 0x202A587E0266A2D7ULL, 0xE13A320A0F3C1E87ULL, 0x260F76DA34BFE5D3ULL, 
            0x405979B03A49674AULL, 0x4B79FFB8FF549B43ULL, 0xDD345863AEC588F4ULL, 0x651D28B5C7495158ULL, 
            0xB0462AAB7B545936ULL, 0x2D94FADC52A87D96ULL, 0x0EF848C2FA99E86FULL, 0x78B9206E48FA9E76ULL, 
            0xB1FB1137E948D7AFULL, 0xDA4CDB078D382D34ULL, 0x56FA081DB565A038ULL, 0xFD6CEDB3542CD74FULL, 
            0x736F68E3A21821EAULL, 0x4180EE7EEE53D1AAULL, 0x5EB999AAC4DED887ULL, 0x2C88858FFF5B4128ULL
        }
    },
    {
        {
            0x4BB0D1505DC21925ULL, 0x06AF54EC5DE7A195ULL, 0xF4124827A255784FULL, 0x1617DE20E0C757E3ULL, 
            0x9D2E74BE5C32D0AFULL, 0x0082E68658250B7DULL, 0x6C11540E62A96DDAULL, 0x2F904998AA5A3B5DULL, 
            0xA2FC4FF1BD426467ULL, 0x5DC13D79D14B39B3ULL, 0xF702C27BC6FF9869ULL, 0xE992883D1CDDD215ULL, 
            0x8F5207EF3CB3631BULL, 0x70C1618A261F4ADCULL, 0x5B2970CF8C8C72FEULL, 0xE9DD7ADA6D7072EAULL, 
            0xB9F22E91B1049B0AULL, 0x93F5503D2A84A8F2ULL, 0xB6E683BAAC99A81CULL, 0x0BEDEB29E0F94DF0ULL, 
            0x6F8123DF3354A2ECULL, 0x7256C94785316532ULL, 0x4EB496F746D7857FULL, 0x39372C48CCCF0DD3ULL, 
            0xB13DCF48139E3D69ULL, 0xCB76D30FAA2D97BDULL, 0xA9B28044984F2DFBULL, 0xF1C0B4689C150745ULL, 
            0x0CB973552E93C540ULL, 0x2054F30CA01AA73FULL, 0xB18E57445772AF74ULL, 0x5E1A9672F88A9644ULL
        },
        {
            0x42FE05854AD29016ULL, 0x08DFA5A45C1349E4ULL, 0xB98AF9A6ADB8C0EBULL, 0xF4B41CCAC439CA9EULL, 
            0xFC7D7F020102D45EULL, 0x25D5A4C4D468E882ULL, 0x82C784460A0E1643ULL, 0x74E5F9C7FC477AC1ULL, 
            0xEA97937D3DB653ABULL, 0x6557C5D6B20F0655ULL, 0xAAE35DDFBF7D28BDULL, 0xB30BB1E27C3DF311ULL, 
            0xA25E4B5333A55570ULL, 0x6E1C3EDCB05E31B5ULL, 0x32B569669690FA36ULL, 0x14F42C2C6B4EFD0BULL, 
            0x0736C481666287DFULL, 0x531B8C33380A28ABULL, 0x2E3D638335AE4D86ULL, 0xCD51C984BC1E10C1ULL, 
            0x9AA0C39A12620CCDULL, 0x299CFF32F6163783ULL, 0x83BD3C54BA76DD1AULL, 0x8E41699BBD95D6D6ULL, 
            0xE9D1020F3BD3F02FULL, 0x49FF0B476035CB2DULL, 0x6327211CFDF1F7C1ULL, 0x9BD9651CC327C11DULL, 
            0x45C461735FB8C051ULL, 0x1E7F736264219816ULL, 0x2418CAA7F184DBFBULL, 0xA1765F37ABBD370FULL
        },
        {
            0xD37738F8DF598FB6ULL, 0xF1EEF05DD43A70AEULL, 0x8C5E1C6E6E18CE6DULL, 0x848B43F5B2CAA569ULL, 
            0x5A0C81499E1C7D60ULL, 0x2E9B0F5140FA7F58ULL, 0x788D66F07BEAF86DULL, 0x3EF8D0E9D91D68A3ULL, 
            0xB05618F4D53676CEULL, 0xEBCF748D99459B2DULL, 0x23157B5A84092698ULL, 0x61FA25ED61C12BE7ULL, 
            0x0B7DF9DB748FEB64ULL, 0xFC9311FED712AC67ULL, 0x270AB6CEC0ED604AULL, 0x069DEFB4D261276BULL, 
            0x64812C885C809CB6ULL, 0x57C81E4DE3E07605ULL, 0x848DE75222209E15ULL, 0xDEFE67CD90EF400EULL, 
            0x86C24969945C35EAULL, 0x973B23D6F2C95759ULL, 0xB5DE9F9674117FBDULL, 0x54CE962C51C98387ULL, 
            0x540275735E7FE984ULL, 0x254143BBFFF7D863ULL, 0xF2BA21F99D8E4C24ULL, 0x53D476273A50D2BCULL, 
            0x0C43069D52871801ULL, 0x8B02F55B70C1B392ULL, 0x94ED78CAB3B12C25ULL, 0x16FD887CB2C5DCF5ULL
        },
        {
            0xFEB9939F3E2CD03DULL, 0x25C454AA8E5969BAULL, 0x1A3691FAB8F41996ULL, 0x571469FD8BB5A407ULL, 
            0xFFA5A54150AD479EULL, 0xD02EB28D9CB4A4ADULL, 0x15C35DB43FE7809AULL, 0x469BE6C51B9C6C66ULL, 
            0x08768F6A5A3B4FF1ULL, 0x7AFEA309C1768B95ULL, 0xD13101AC419FF619ULL, 0x6790CD6D049F9F94ULL, 
            0x4AFD83AAAC136CF4ULL, 0x97332D374218BF44ULL, 0x0AE9D0ED8EB3929FULL, 0x9BCB5EDEC6691E15ULL, 
            0x5289F7D5EE0CDF43ULL, 0x333B1A7D9EF1C8DAULL, 0xCD2791265080F8DAULL, 0x26B20291C4909219ULL, 
            0x72781729E47CF05EULL, 0xF1316FE604689A2CULL, 0x177EC8DA59E000C2ULL, 0x5E8D7AFDA6C79685ULL, 
            0xBE59A2224ED74FFCULL, 0xFC8479E92BA408CAULL, 0x06AFFEBAB143893FULL, 0x70405E5421F3D7F9ULL, 
            0x2B8CAAB3678BD1DEULL, 0xC21B71C0635BEDDFULL, 0x8C40B66D962F5FF8ULL, 0x57BFBDF8968DA054ULL
        },
        {
            0x334DB22C03679AA8ULL, 0x673B2D67CAFF26D3ULL, 0x49A81F1AA010097FULL, 0x48001A6495832ED2ULL, 
            0xE0828D20D5DA8D53ULL, 0x438070B468B66094ULL, 0x249745E4E8F8EA1DULL, 0xACD292082EC3976AULL, 
            0x704D75DC5F335191ULL, 0xE0247E62A8090FE8ULL, 0x5B4D9D6CDE2FE493ULL, 0x823FF9845491E5D8ULL, 
            0x177D7A9155FC4566ULL, 0x91150A3669622862ULL, 0xAB0E50221FD5028DULL, 0x82027575B0D699B1ULL, 
            0xB950E1FE1F7AF184ULL, 0x82A2A57457F82D56ULL, 0xF7FC76DA2D74A94EULL, 0x690D0A328E3DD16BULL, 
            0x83B238CEF8A74CD1ULL, 0x8E922999DFD8D929ULL, 0x90B341B6329416DDULL, 0x1B615455F616171DULL, 
            0xB9AD9E9D214EB9CCULL, 0xA9860D6AEBC28F6FULL, 0x234644AE094F46D2ULL, 0xBE2F92B72D621AADULL, 
            0x122AFDAD59F72D0EULL, 0xA71104363B71932BULL, 0x4F00BE9972B0CD64ULL, 0x57FBB99F490773DCULL
        },
        {
            0x4DB6B79211871735ULL, 0x2B123C7403AC2896ULL, 0x14C3F86008061F4AULL, 0xA0AB832731C69B2DULL, 
            0x1751A060010AA695ULL, 0x4E944207A5701697ULL, 0x7C98491FEB99F516ULL, 0xF537E1897D8E6895ULL, 
            0xD4684E779751B465ULL, 0x381F106807154BFEULL, 0xDEDCB22CB757D40FULL, 0x7CFCE9DD0A0965EAULL, 
            0x426B99D476B69D3BULL, 0xBC31628DCB4ABD64ULL, 0xDACF3146D6473979ULL, 0x0ABCDDD5657008C8ULL, 
            0xEA3CCAA0A656DF14ULL, 0xA86E38E1C3CB0473ULL, 0x854F1EC46CE35590ULL, 0x7509EF62FA44E6F0ULL, 
            0xEBB91E560EC137D5ULL, 0x0685B29F9EB29473ULL, 0x345C867B8650D09EULL, 0xA28F4F5B567B6B5AULL, 
            0x18897BFD4394841CULL, 0xF199D25C2E07AAA7ULL, 0x7FF018ABBFB75E10ULL, 0xAFE64BC27D41BBEFULL, 
            0xB5E42980ACF55DE3ULL, 0x614E400E47247375ULL, 0x63198EB959BCA4CDULL, 0x6E2F9D626946DCF1ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseBConstants = {
    0x0824358142553751ULL,
    0xB97337B792E3391FULL,
    0xCCF69EF8A3EE53FDULL,
    0x0824358142553751ULL,
    0xB97337B792E3391FULL,
    0xCCF69EF8A3EE53FDULL,
    0xEE7316F0117E019EULL,
    0x879F7E45D010827FULL,
    0x24,
    0x17,
    0x84,
    0x96,
    0x7E,
    0x2D,
    0x71,
    0xE1
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseCSalts = {
    {
        {
            0x2948B53782B864AFULL, 0xF5A2E1AFE34615E4ULL, 0x513A3576650A6EA4ULL, 0xE0DBFAA5BE61B4A0ULL, 
            0x8C8A60FADAF59429ULL, 0x1A53125A29D008E3ULL, 0x6741268CBBE4D5F8ULL, 0xA04E7F83F517CEBCULL, 
            0xAE56296C4B3EF577ULL, 0xA4A1BCB89B8429CEULL, 0xA9D27B8E2389D088ULL, 0xC2138A56CF113AE1ULL, 
            0xFBF5AC31D18E11FCULL, 0xF8835E63BD93AF57ULL, 0x6A76CC74A45321CCULL, 0x431B625622706605ULL, 
            0x13EF28DA90E60988ULL, 0xD9CC492169AB86B3ULL, 0x35F596B9D8759526ULL, 0x2AF8C35826F4C03FULL, 
            0x8DED6A4DB8B06B4BULL, 0x1D7966941F8A2EE9ULL, 0x2FA428B1797CC6E9ULL, 0x791EA8D2A1926218ULL, 
            0x7EDB04E42072A1EBULL, 0xB3C7FCE3C288E5DBULL, 0x1A7B6AA31654360CULL, 0x14DF4B9B5149B9F6ULL, 
            0xE40EA3DC6FD54410ULL, 0x2F62D6F501550132ULL, 0xCFA9262DEF62B95EULL, 0x4118DBBDC17B8D66ULL
        },
        {
            0x8D13B05F5C40A51AULL, 0x757F48A4FC34F37AULL, 0x6190B1493C087C8FULL, 0x7EBD6336DAEC588BULL, 
            0x05564CFF2DAC7CD3ULL, 0x388DEE6502B50EC1ULL, 0xBE72E713DDC8800DULL, 0x1115676542FCD3A1ULL, 
            0x5A4A51CD4DA8FE8DULL, 0xB34D02448E82EE92ULL, 0x06B22F0B65D373E2ULL, 0xF511B20EF74B8749ULL, 
            0x4543E67E65EDAFA6ULL, 0xD5AF1681330BA6D4ULL, 0x48CBAFACD7A03620ULL, 0xAD4F9A69BA8F246EULL, 
            0x1014225B5396ABF8ULL, 0x4457EA70477583E9ULL, 0x433FFB000A73C9EBULL, 0xDB4FCCEC15BC662CULL, 
            0x38A63C5D0E4D9EAFULL, 0xB269C2733BA4459BULL, 0x9E19A8940A2F1B7CULL, 0x3981666578EE62F8ULL, 
            0x1DC8BFF70EE0FC3DULL, 0xF13F175761DBF4D0ULL, 0x320E947080B5B4AEULL, 0x01ECC1DFEBB5A1EEULL, 
            0x611D6FA56865A27EULL, 0x30EDFC7AAA500870ULL, 0xB9029BB252B769E8ULL, 0xC36CF06FCFE2B0A1ULL
        },
        {
            0x1CD957B6349E1203ULL, 0x6E7B144326ABA605ULL, 0xEBFE73015A59F4D2ULL, 0xEF4141AC788ACC6BULL, 
            0xE8A99DBC10404511ULL, 0xFEE973AE19568A25ULL, 0x9BC14F5F4CA941FDULL, 0x481F36714A28132AULL, 
            0x9A796A768BFD7928ULL, 0x592FA94683016322ULL, 0xE884ECCA399D0313ULL, 0x7DA80C465116689CULL, 
            0x90C699B9AAA842B9ULL, 0x71B34DC193834E06ULL, 0x476B6039E0805D09ULL, 0x36234F847A2A7CC5ULL, 
            0x216FEA4C43D3C963ULL, 0xAE8EA1120357AEB7ULL, 0x209394F13863CEABULL, 0x956D4F2E1209C544ULL, 
            0x635373E5292505CAULL, 0xFDFB1AEBB16FA3B3ULL, 0x14D06786B26A83B3ULL, 0x54AC923EFB753421ULL, 
            0xE266ADFC144BFDF9ULL, 0x72664A5BDE0CD6CBULL, 0xA6017E94B9B1DA95ULL, 0x00F4626A1CEEB8A4ULL, 
            0x3CB021189E47170FULL, 0x5DC912DBB7090A77ULL, 0xA3DD3E76C65909B0ULL, 0xA183CDE5DA8B2992ULL
        },
        {
            0xD3FD149130D963F8ULL, 0xD02F464B67644F2BULL, 0xBC3385F3BD68CD90ULL, 0x4B50405A24A636DDULL, 
            0xC12F8E35256676A7ULL, 0xEAF79F13F5F980C2ULL, 0xE22551F27BE90F77ULL, 0xC66B17CC05AA5C52ULL, 
            0xA816AE349616A4F7ULL, 0x2DE8A6252A336F69ULL, 0x737DC8DBF1EDCD32ULL, 0x9C9B9C2E07DDE727ULL, 
            0xB6B0BFD4A21ADC18ULL, 0x2F7D6870C6936104ULL, 0xB47F0AAE9C8DFFADULL, 0xD7CEA010FC99D202ULL, 
            0xCD8D292FA1251A29ULL, 0xB3C6A83D11CDB635ULL, 0xB221325E3996BDDEULL, 0x02132982BCDC2C75ULL, 
            0x54CD648C1D1E199BULL, 0x3EC7C489F518EB27ULL, 0x1E9D528A8B14DE85ULL, 0x9BC87F2E510201FBULL, 
            0x3E5770347270A0A3ULL, 0xC32443D800C18314ULL, 0xFE101A2C9934A8C8ULL, 0x31029EF3236AFD2EULL, 
            0x5C29C9C60D271751ULL, 0xE3748ACB8BDBDF57ULL, 0x2400EE80BE3305DBULL, 0xB5D45B0017B51177ULL
        },
        {
            0x16E3B52110302983ULL, 0xA44FF54EAC886CAAULL, 0xAE1B8BD86F921B8FULL, 0x713596F10798DCA0ULL, 
            0x180D9AE0BB18164EULL, 0x8263FB4EBBF9ECDDULL, 0xA215BE69337ADE0AULL, 0x47F7271C032606AFULL, 
            0x9C986F18B6377A1EULL, 0x0C7A527F090009A3ULL, 0xD54CF9D8AC31B76EULL, 0x6A6C5A9C2D2C6BA2ULL, 
            0x443D2217A4ACBD09ULL, 0x8077DCD944DA82FFULL, 0xE004E114E53E2555ULL, 0x2827DDD560634291ULL, 
            0x08F964A2215F7AF0ULL, 0xCD091F5FB43CE944ULL, 0xD0FDE72785D98C7AULL, 0x5866425238592790ULL, 
            0x00449FF84C3534D3ULL, 0xE64A20C2424F72DAULL, 0xE89E9D841C7F0794ULL, 0x79AEF3BDB2C45B9AULL, 
            0xA158ED6B2D7236C9ULL, 0x73520747C1CC4C97ULL, 0xC802E5891461DB74ULL, 0xE325A471686CE329ULL, 
            0xA9470E8DE8C61A75ULL, 0xD97777098E943411ULL, 0x85E1A1AC90F93857ULL, 0xA552EC827AD80C11ULL
        },
        {
            0xF36DC971FE3CCE12ULL, 0xEAB60D887CB6FE51ULL, 0x6393E56037C93343ULL, 0x40A032634195740BULL, 
            0xA2267881E2D476D5ULL, 0xB86DBBACB5F11A6AULL, 0x160546000A5E1D2AULL, 0x2207D5A19533754FULL, 
            0xA4747817F33BFF0AULL, 0x434C401BFFC5532FULL, 0xD233C76E417046E1ULL, 0x6EB79FA62D56DCEEULL, 
            0x02E3B92147C0A28EULL, 0x9150F445C6AE3B89ULL, 0xCB739C630DEAD9EDULL, 0x0E90CAEEAC072224ULL, 
            0x12CB41C5471A1B11ULL, 0x654BEDCEDBC68743ULL, 0xAE2BB55515377726ULL, 0x668302CB93A6E3B4ULL, 
            0x8AF79C7D393381DFULL, 0x7854AACDC1FA99CAULL, 0x7554DE521E539094ULL, 0xABC9BF230B2BC34DULL, 
            0xC6F7E1717A05C981ULL, 0xA4B3A59563E4CA83ULL, 0x9C7DAF6DE45F70D9ULL, 0xCB624C57A8BDED73ULL, 
            0x887F265AD5C96F98ULL, 0x1B27BBDADC6AC7F8ULL, 0x3FE6EC9DDBA59E48ULL, 0xDE9E6798206028CAULL
        }
    },
    {
        {
            0xB3D4C3844C53EFE2ULL, 0x7521BE2F9DA9822FULL, 0xA121E3DD7F2534CDULL, 0x29F032C31A7ABD4EULL, 
            0x3B0D7CF07A69214DULL, 0x47DC908DD9A1645DULL, 0x8FC318354ED1571EULL, 0xA8E7FF865E6CAA63ULL, 
            0x7DB76A2B50670330ULL, 0x8C512D1CF6D1199BULL, 0xA95FFADD9216783DULL, 0x394649DE4054EAAEULL, 
            0xE7179F8AAA3B5D52ULL, 0x81AC330547A86269ULL, 0xDF1A1BA518059FFEULL, 0xBF7BD72A407FD1CDULL, 
            0x079A59D9BF0FA2EFULL, 0x05BD54888963CC87ULL, 0xF20C23E1EFAD4F6FULL, 0xA3693565FE90C6CCULL, 
            0xE28A47F9772D98AFULL, 0x403DF8809090188DULL, 0x9086B5AF3376C70BULL, 0x57D9A112A1293A6FULL, 
            0xD1BA92479A6564CBULL, 0x35198EBE3269CFBDULL, 0x3A07FB727457EE2AULL, 0xEF73FAD3639C4B46ULL, 
            0x986A30F1A1B5D1F9ULL, 0xB8B2B434481D13A7ULL, 0x7C222467283C33C8ULL, 0x59D9AA095DF9B1C4ULL
        },
        {
            0xA2AE60AE99CE0F82ULL, 0x56D37D3F27DAF206ULL, 0xFAFE9771919A74A1ULL, 0xA13093C56A10C7A9ULL, 
            0xBA8982B1F6535BFEULL, 0x878DC3E119BED5B5ULL, 0xDFE5776271B1F917ULL, 0x672094FAC7CF3357ULL, 
            0xB281D3802514BD80ULL, 0x57032C7C5BAD6344ULL, 0x6C9AE32B1E037A7CULL, 0xFF67D531F9508A60ULL, 
            0xDE5CD7704899A412ULL, 0x6DEA0BFF03709120ULL, 0xA299B9F6B4A088AAULL, 0x13485A77513F323CULL, 
            0xA8351CBB11687F33ULL, 0x5252AE9D3F703534ULL, 0x4F56E3320C83298BULL, 0xF2BFA8C7CF0B1B52ULL, 
            0x9830FAC204D99DF5ULL, 0x421B3F05F33FC121ULL, 0x1D76F6163E13B3DDULL, 0xFB24B0BC6048855EULL, 
            0x7E30F4C27C9252A3ULL, 0xEEFEAAB54D36E6C0ULL, 0x4FE53F36A43249E8ULL, 0xCC9094E20AD1C48EULL, 
            0xD78A0A9BA2D4AD15ULL, 0x68B80AB8DF839F0DULL, 0x0232F237A4E1B432ULL, 0xF8B754620469A20BULL
        },
        {
            0xE5E3FA9C234B842DULL, 0x93DEFF400AE6130BULL, 0x4A315A41B5193D0FULL, 0x1B0AF416EC51F10FULL, 
            0x53D2E904C69705EAULL, 0x1C110D321DB4E4D5ULL, 0xBA10034C7CDB5842ULL, 0xB82F70C06020A96EULL, 
            0xD7BCEE83ACE198A3ULL, 0x88A478DE82DAECB0ULL, 0xC422FEA25EC104C9ULL, 0x39C5ADE3572A83D8ULL, 
            0x24E3A0471629FA76ULL, 0xFB5E91813D440674ULL, 0x030E3B292076D3D5ULL, 0x556288FD69C1D6B0ULL, 
            0x45D2B67C3FCCFDC3ULL, 0x70D7BB1F30BA1AA3ULL, 0xDE3CA14BCED5208AULL, 0x2763F433CBE383E4ULL, 
            0x7A29BA247247A6E0ULL, 0xCB490E4651781A1CULL, 0x901D7D88ED261765ULL, 0xA14C0A0279381CF7ULL, 
            0x1070628ED6219834ULL, 0x13E45E0F13DDEA81ULL, 0x81AEFDE297A08A37ULL, 0x3EC83DD68E3E47DDULL, 
            0xE3C7293BC1FB26CFULL, 0x2C9BE78B21048779ULL, 0x8AE8A5B1058FA926ULL, 0xD348E6B791B79D0AULL
        },
        {
            0x80BF595268879DBAULL, 0xAD3D7F3C2DC33BA4ULL, 0x3118C833CD390370ULL, 0xAD05C99EEECE7F1DULL, 
            0x05665E32D4D517C9ULL, 0x186286A5CD9C3D4BULL, 0x36CFFAA4D0564ABEULL, 0x0B12E9F2EC9552E1ULL, 
            0x8B328DF444E867B8ULL, 0xAF7A88393DD7EC31ULL, 0x8B1FDE4B24C18890ULL, 0x42031F6A42C1C497ULL, 
            0xACEEDE7A1B364E73ULL, 0x96294C64D5D78CBFULL, 0xBA99DF8F048EEF51ULL, 0x045D1CE939900F64ULL, 
            0x46E6B01952928F33ULL, 0xB6C35FE6B4D368AAULL, 0x75AB9EFC612E8996ULL, 0x39A4071F06B318D1ULL, 
            0xCE523ADC14E5845AULL, 0x69BC8A10222375FDULL, 0xB8A27CF75B945A23ULL, 0x7414E66B11458652ULL, 
            0x3849BCF5B4088954ULL, 0x6A694CDF263BF2A5ULL, 0x9697E22ABF861463ULL, 0x52B6026BAA7B0822ULL, 
            0x1A98E5689E79C7D1ULL, 0xB70D65E6187B7274ULL, 0x1C2E8927CD4B4BE6ULL, 0x2EDFB20550D9D438ULL
        },
        {
            0x659F90073775CA86ULL, 0xF58604BFC3172586ULL, 0xA3E7716CD9431F08ULL, 0xB5ECC8AB4871B534ULL, 
            0xD073F100FD5A9EF9ULL, 0xC48A218ADACFB4F1ULL, 0xD5A1AB7BD17381BDULL, 0xC0EEFE2931DC6CB1ULL, 
            0x4D057C4AB1F2157DULL, 0xA19495D8D0F22BD2ULL, 0xC2F388BA66076CC5ULL, 0x4DDEB0382FB2CF51ULL, 
            0x640E65020DDD0D31ULL, 0xA946FBE46428560FULL, 0x504807A2E9F857E7ULL, 0x65FDD2110DD7E0F4ULL, 
            0xFC11DD3BF5E65744ULL, 0x7BDCA35A2CA89109ULL, 0x38762221C5B9189CULL, 0x7C3EEEBCF338132EULL, 
            0xC19F0FC88BDF7FA6ULL, 0x058AF602CF014222ULL, 0x7D41C4973E60910FULL, 0xD8AF057DC61BFF63ULL, 
            0x156250C0DC90BCB4ULL, 0xF8473040091F0774ULL, 0xA20E52343B57570CULL, 0xDC972FE1F73BEBB7ULL, 
            0xF1DF5D6688473153ULL, 0xD3795F8969165493ULL, 0x4AFE06FBAC13B095ULL, 0x6EE6758F782A78CDULL
        },
        {
            0xA50645005BA53464ULL, 0x87714E9E4AFABCF1ULL, 0xF8BA8EA92EB835ECULL, 0x72D3B90DB11774A7ULL, 
            0x73094023CC0D416BULL, 0x5167BD2457DDC891ULL, 0x91D8050DA37D734CULL, 0x08D1AAAC7B2E6D9DULL, 
            0xF2461DE4F97F8910ULL, 0x47F0B9B6988720D9ULL, 0x3ABC92A8778A8103ULL, 0x711C0CD441F01E9BULL, 
            0xC0368E848F78E012ULL, 0xF87A121F06EDE5E1ULL, 0x19D4BE0DBF92BB77ULL, 0xD5DD5AD48BCC322FULL, 
            0xCA40DAA34B9617A2ULL, 0xA91689B4044CAB33ULL, 0x2ECB41F260653000ULL, 0x7825CCD2B76B1C64ULL, 
            0x378412AE789CB41EULL, 0x8C5ECD1BB09D6961ULL, 0x39FE7ACB80A7D4E4ULL, 0xBFFED1A63E076CB1ULL, 
            0xC26A1E44C589858CULL, 0x3965187886432843ULL, 0xBFE0D79F9363E0FBULL, 0x216D7C029C5A3B23ULL, 
            0x54A96A24A1603B87ULL, 0x06B819A783F093B5ULL, 0xB8CA06E0162A21AEULL, 0x5DD75C565AF80E52ULL
        }
    },
    {
        {
            0x7C54C13B0106A527ULL, 0xB7A22A52CC2A5EE7ULL, 0xB8D44307D743A31BULL, 0x4C8DCA6CDB298E82ULL, 
            0xA8B597E1D09B96C3ULL, 0xA8A4AE1544E8F876ULL, 0x10546CA63FF5542CULL, 0x77D9FB1FCB26A4C6ULL, 
            0x9BAE3F24C0F1EF18ULL, 0x1A03F146DC614739ULL, 0x379C9E02628A8189ULL, 0xF726D041B9F3BA0CULL, 
            0xBE131CE12FFD28B3ULL, 0x29B27BC443961B38ULL, 0x040D9CA1D3EB9524ULL, 0x93D2080A13104DC1ULL, 
            0x820A30EA691755E4ULL, 0x665C4FA26A8978FEULL, 0x7AE3E3FB4634707EULL, 0x83D2AE7F61D7D3E4ULL, 
            0x05CC3C6C7EF407A6ULL, 0x682B87DE00A4E3D7ULL, 0xE00C4D177D8567AFULL, 0x742BE48DD7675446ULL, 
            0x6FCDD90DA2389FF2ULL, 0x68535073ED806E78ULL, 0x24E284F3566BE94BULL, 0xB052B593FCE00322ULL, 
            0xB055ECEBFB21B059ULL, 0xFA8E5DE33ECD038EULL, 0xA28A1A7DC624356AULL, 0x7F13779053C33553ULL
        },
        {
            0x2EF8D2E5FC6D8AB1ULL, 0xCA9DCEFB258D34A1ULL, 0x1CB4F000082520DFULL, 0x34102ABC21CE4F19ULL, 
            0x6A07EFBC143BD6F4ULL, 0x16F4803190F8C199ULL, 0x72CD38618F2DE5D5ULL, 0x60FF8F43CABD34B1ULL, 
            0xC5A6ABF2576AC302ULL, 0x7B849CCE34C1C204ULL, 0x2EBC9682A9CF2802ULL, 0x55D684CA81B2D437ULL, 
            0xAE7B172A5352AC52ULL, 0xA1E1909053FBA283ULL, 0x46BADFB8E74D8A9AULL, 0x49958953B647F7D5ULL, 
            0xDC79090EA0507CD4ULL, 0x62708B0DC72213E5ULL, 0x24B2BF3052FA1549ULL, 0xE0C7DADB3556F96DULL, 
            0x270F7E8BFE7847DFULL, 0xA4CA03EC772755A9ULL, 0x629AA304D31CA37CULL, 0xA6D17279CE48794DULL, 
            0x64C290554846D02FULL, 0x5DBCB4F7D8B74BF6ULL, 0x7DB76D884D42FE4DULL, 0xE76912AB4D5A22E2ULL, 
            0x814863D152FA3012ULL, 0xF31FBF26C524D6C8ULL, 0xE4344BBF334867B5ULL, 0xFB55B3EA371CFDA9ULL
        },
        {
            0xBF8CBA083755045CULL, 0xDBDE4A3BA3027A02ULL, 0x6824767BA90EBD34ULL, 0x1A28C7C461A78938ULL, 
            0xD8CE18E8BB3E04F6ULL, 0x136834535BD90AB9ULL, 0x0DD1ABB35D1E369AULL, 0x25839C6FC5D94674ULL, 
            0xF24EB655E0A29B06ULL, 0x0574F0A41E9250B3ULL, 0xBD214D0897688374ULL, 0xD96F587C340C1926ULL, 
            0xBA800F5952996197ULL, 0x8EAF57823E55D1EAULL, 0x6ECD3387FB17888FULL, 0x01D699327A3B4DF4ULL, 
            0xC8E5D51AC7543951ULL, 0x3DE41E43EE71C416ULL, 0x6EBCA7DA3034A66FULL, 0xCBA5DC7AAD915CC2ULL, 
            0x78D77CACAC0BE27BULL, 0x5751F11944CAC5F0ULL, 0xD9995D766F5F3668ULL, 0x0168E02A190F8F8CULL, 
            0xDC768A9480B49B3AULL, 0xCDD41D924F85165FULL, 0x6DBD362200D2ED1AULL, 0x75467E623FFC37D3ULL, 
            0xE6B7C3F4F8B9B04AULL, 0x6417DD0F128945D3ULL, 0x39C5FC3AB98DD9EEULL, 0x75D1ACC9142A7917ULL
        },
        {
            0xBB374CCC6446EF79ULL, 0xAF7868ED4CA6F02FULL, 0x1751F8C76B6CA940ULL, 0xB0ADF7504AB683EAULL, 
            0x85304F02B5583ED2ULL, 0x7B5CE1FD052710ACULL, 0x40C7B4F9E70EB1E8ULL, 0xC89D396CF3C4D50EULL, 
            0xA615C66960A819DDULL, 0x85A88D0284CE9ADEULL, 0xAF2DACA87355240CULL, 0x4A658F15A1CBE0B4ULL, 
            0x8A5B6B980C9FA3A9ULL, 0x50E9C8C5C712272FULL, 0x39C4A54229010B7AULL, 0x3A847B56300084FEULL, 
            0x7E7B963E6738ABCFULL, 0xEF471969260F4254ULL, 0x1236B189B4D4C323ULL, 0xFA42F2B739AC681CULL, 
            0x07A9B78739B7CF27ULL, 0x117A8B74F9B8DF60ULL, 0x6D2F59BF6CBDF5C1ULL, 0xF109601C625BF2F5ULL, 
            0x79D959029646DD50ULL, 0x520B83FF8AA09E1BULL, 0x0CEC682B3A5BF191ULL, 0x29E5AF7970F73F43ULL, 
            0x41AE662DA80B63CBULL, 0xEA62CB1E8D26AD5CULL, 0x2DD87172CADAFFE0ULL, 0x29F8FCFEC8B9E20CULL
        },
        {
            0xCA96EB69C8B360CEULL, 0x43523947772F0512ULL, 0x8BBE925B9480B4BCULL, 0x8A967DCE17CC10A6ULL, 
            0xDE6A4AFCC0C460A4ULL, 0x5E3FF31A6F82FAB5ULL, 0x0DCAA2786F155253ULL, 0xA8EA6D661582455CULL, 
            0xC88B11655FD63F15ULL, 0x3480D2FDADF45BD3ULL, 0x5E43ABACF42F86ADULL, 0xE9CD8A5BDF05D166ULL, 
            0x14ACEE08E13DA4F6ULL, 0xD355DD053A2C09C7ULL, 0xE091EE8A203F34FBULL, 0x594F373AB6E9986DULL, 
            0x8B4FDA925713181FULL, 0x80547C17BD3DBAB4ULL, 0xC04F37761F28A3A3ULL, 0x59C30C4EF2BDCE24ULL, 
            0xAD9143ECDE2D0EB9ULL, 0x1D86F800359DE548ULL, 0xC2D3BA9367C8AD36ULL, 0xE3B7D08200705D56ULL, 
            0xE6D9F43C05A4A05DULL, 0x53701DBCAFCCCAEFULL, 0xBAAF2918272BC420ULL, 0x59F258AB96FF7DFDULL, 
            0xC389D8EC5641662FULL, 0x68EE7D0235A41E12ULL, 0x806B3A87341AD1A6ULL, 0x91D9D5DCA6A3D50CULL
        },
        {
            0xFF5B139E829A7E76ULL, 0x817A315B69EABA13ULL, 0xAF5EB193003948C9ULL, 0x6B07076CAB7137D7ULL, 
            0xC21ABDB322681753ULL, 0xE866A84B1ACF2563ULL, 0xFFC8043FE219AAF0ULL, 0x340C1EB22A946924ULL, 
            0xA3BF5C50E22D90C7ULL, 0x0D6C46B5E5906DECULL, 0x198CED410DC9C4F3ULL, 0xAFDE0602C60F2DFEULL, 
            0x68654870B9FC0C46ULL, 0x83E6A26D30CC4905ULL, 0xFFCBABBE75AF9670ULL, 0x41DA5BDB62430233ULL, 
            0x4A4544CAB3839924ULL, 0x9EC5CE453FB72CE3ULL, 0xFDE5813FBEF27C60ULL, 0x426B29A93715DC5AULL, 
            0x1CA84D48243A351EULL, 0x5B196C5A5DF4DF76ULL, 0xE2591D02675EE5E7ULL, 0x9B425970A1C0520EULL, 
            0x2EAD220F302CD621ULL, 0xBFE4C611628DA4F6ULL, 0xAD9E6B932B2AB964ULL, 0xE5FE7A1CC6794465ULL, 
            0x696B569536C2A293ULL, 0xCF2781E11AFC78BDULL, 0x1C156E6169F2611AULL, 0x8E18388594A8B88BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseCConstants = {
    0xC96D5A64FED7465EULL,
    0x53F0E4CF707AB5B8ULL,
    0xC5EC1CFC3C188C6CULL,
    0xC96D5A64FED7465EULL,
    0x53F0E4CF707AB5B8ULL,
    0xC5EC1CFC3C188C6CULL,
    0x93E92C41B3DB67DFULL,
    0x94467BE913A55001ULL,
    0xDE,
    0x39,
    0x49,
    0xBD,
    0x22,
    0x74,
    0x13,
    0xD8
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseDSalts = {
    {
        {
            0xB09F05959FD55038ULL, 0xEEDF0137AB8269AEULL, 0xC44BB75E8DD41016ULL, 0x9C9E71A007766F43ULL, 
            0x50AD824708899B05ULL, 0x96C60A606942ECFBULL, 0x1CD15E5CAC240792ULL, 0x847A14BB34291453ULL, 
            0xD9001ABBB90F757FULL, 0x8DD3C87B46EEF288ULL, 0x6FDD15E13C472BCCULL, 0x033738C505FC7282ULL, 
            0x176D9EC3E5F0FE63ULL, 0xAD863D089BCD3C5FULL, 0x5C877EDA8460A7EAULL, 0x520DA9D7561BBDADULL, 
            0x77FCE733AACE0D01ULL, 0xBF5E30D62B86087CULL, 0x97B45E9697651435ULL, 0xB23C568CEDCEDC06ULL, 
            0x30B0602286CC0A11ULL, 0xB473035738C05E9AULL, 0x79EC90AE4A8CA182ULL, 0x6660F4840F54E4F5ULL, 
            0xE707C5A83BD958D7ULL, 0x6BEDDE4EC656C864ULL, 0x56114874165E8ED0ULL, 0x065C0230497EAED4ULL, 
            0x15C44F0C437C48DEULL, 0x173AF9557C04BBB8ULL, 0xAA77F89B6E73C3C2ULL, 0x668529B4D5D3720DULL
        },
        {
            0x33065E7829B1D3D4ULL, 0x1D076AF5B9237762ULL, 0xC1531A4F871BC565ULL, 0x227179E9A89E49C4ULL, 
            0x1A922048B0951266ULL, 0x69496CFD01091C0BULL, 0xFD91C1E3E9BA8151ULL, 0xBE96B99F3565F90AULL, 
            0x5F39CFA0DD58F27FULL, 0x0D4CA88990B7A884ULL, 0xD4C59179CF71E05CULL, 0x656A8832FEA9A434ULL, 
            0xE07C0C9A68702F0CULL, 0xF4118113C16C746AULL, 0x3AE535857E1D46C6ULL, 0x78FA0FBFDE05B63EULL, 
            0x1F34B6D3C448FE84ULL, 0x3D08A222403EB579ULL, 0x34FBDBC82DC8AC13ULL, 0x792AFAD730D6B094ULL, 
            0x3633AAC240946C94ULL, 0x3F3981BE627AF3F6ULL, 0x5482071AC0A4D8C1ULL, 0xF54AA03927253EF9ULL, 
            0x2699E233BF7FE7EDULL, 0x046260B03407A91BULL, 0x66CA1D23B8C25492ULL, 0x163AE2EE2B87EC87ULL, 
            0x4C34F30B3746A19FULL, 0xE21169CDFF078A42ULL, 0x6A6E43C61601810DULL, 0x4249D324059FDAFEULL
        },
        {
            0x7641D54AD8859D22ULL, 0x353271817DD573ADULL, 0xB6E512B2A86B4F31ULL, 0xB1BB2361745B4905ULL, 
            0xD5AF3A4A3076B79BULL, 0x1C411740AF5DF6E7ULL, 0x57524A23061089EDULL, 0xBC6CE330424AB695ULL, 
            0x90D81D44C5C47C0EULL, 0xD3D511E10C0CCAFDULL, 0x0BDF39D8205A84CEULL, 0x37F6DCB5F6E183F6ULL, 
            0xC3F3D4526E444A82ULL, 0xF78C0C01AF34E587ULL, 0x75570413654CA65BULL, 0x903E94104CDE3922ULL, 
            0x9D55AC50491C73FFULL, 0x2CA712ACA489233AULL, 0xEF985D6BED2C5A79ULL, 0x396E07E4FAE93D26ULL, 
            0x58E42C1BD0721EC6ULL, 0x67EC4CD3ED14A792ULL, 0x9C6F8DBCE69AE6DCULL, 0x9BBE071A28DC4A59ULL, 
            0x88BC236CF8980817ULL, 0xD23CD6BAE6A64572ULL, 0x4F5B28C3B6007189ULL, 0x83E77D8BC44F5720ULL, 
            0x0235BE02A2FF9989ULL, 0x94542CCB446F9706ULL, 0x679C82EC303FC071ULL, 0x06DBAA5B776656DDULL
        },
        {
            0xD7A4A56F7D0C9D31ULL, 0x3D9A90FF655D76A3ULL, 0x49B1DC73A0FD19B5ULL, 0xA47CB87CF8957793ULL, 
            0x0B172D4F5506F6F0ULL, 0x353FFC9674C99ACAULL, 0xA181CF6C74ECA2E6ULL, 0x011895DFD22A3126ULL, 
            0x848F2E0D004B0810ULL, 0x3E1EC61A2C7CBA8AULL, 0xDD7032A6645D0F2CULL, 0x2C2B9F7F6C71EA9DULL, 
            0x01E33FEDDA1075A6ULL, 0x0CCE6FB3CBE51DD6ULL, 0x9D522B7E5ED6D614ULL, 0x49ADB443E023DE1CULL, 
            0x13F69DDD16EC4762ULL, 0xF64DF22DC7E1A02DULL, 0xAB300D83C2151658ULL, 0x80C99E878FC67349ULL, 
            0x25121909BDEBE552ULL, 0xCB8F71C090B865A9ULL, 0x45771984123F20C6ULL, 0x7B762F603DD369E9ULL, 
            0x13E78DDDA5CC80E3ULL, 0x9B45CE3FF9738A78ULL, 0x015E8E8FC28206BFULL, 0xD57915518B2A5B1EULL, 
            0x6B0EB74F89E21B52ULL, 0x3A384C42E03399C6ULL, 0xB9FAD8F99A28EDB7ULL, 0x6B9C588D1C0DCE85ULL
        },
        {
            0xBB478B38BA024DBDULL, 0xCB220315403A6688ULL, 0xF92440F42A6C5057ULL, 0xBBD42F2037132FBAULL, 
            0x68BC9AC200B5828FULL, 0x191D5DF249D3318CULL, 0xB94FA417E2A5AADAULL, 0x7A8038533AD2F694ULL, 
            0x17749A8F7EF36CC9ULL, 0x35E53CD2A0000E87ULL, 0x6B56720D25F96E0FULL, 0x3742443DBA2EB751ULL, 
            0xA836BFA7ABFEF457ULL, 0x1C6D7F7300D112E8ULL, 0x94B8B4FE2C57F507ULL, 0xAC9209155C500129ULL, 
            0x8064467182CA6D66ULL, 0x5AEA7A1F8C34FDFFULL, 0xABF6663DB61EC50BULL, 0xA15046CFC4D32C78ULL, 
            0xD296D81E50A7B445ULL, 0x8ED489B0787C09EDULL, 0xC7D9240CDE0E5608ULL, 0x3A09B28C78D2A5DDULL, 
            0xC628D038E00E219EULL, 0xED239C6AADE082C1ULL, 0xAE478FCB714F4896ULL, 0x8C89D40E8301AFB5ULL, 
            0xC591F3EAA4B5A544ULL, 0x4323CFB67752F5E4ULL, 0x14E2F374FC5BA9E5ULL, 0xCC63B4114100A522ULL
        },
        {
            0x43AEC9DA4DB134F4ULL, 0x89E3FDAFA3FF10FDULL, 0x689F9B5C7C5E866AULL, 0x33B267750A1F7826ULL, 
            0x79B335C33749F8B5ULL, 0x2056CBB67325A5FBULL, 0x571FEE7CD1FCBBC6ULL, 0xC097C4F21203C4F8ULL, 
            0x1D7CBD75A879CD7EULL, 0xFA44461EDDC29AABULL, 0x47211D441DEEF6D4ULL, 0xD3120B032C75C10DULL, 
            0x0443D31032981E4FULL, 0x555F861F9F634C84ULL, 0x9130151EAB64424DULL, 0x594706A0B148F648ULL, 
            0x129774241F988976ULL, 0x517769365E831F8BULL, 0xBD5B976F181D637FULL, 0xD14F54C6CB366463ULL, 
            0xFAF2C12FB9765A81ULL, 0x182F11AF1766E5E7ULL, 0xB30EBE1D48E3BC13ULL, 0xB54AD514E5257F08ULL, 
            0x373A681A8542464FULL, 0x47D41073FECB3CE5ULL, 0x229F24B6D1F1E6ECULL, 0x2738DC8E58377D0CULL, 
            0xBF6F64DF3AB9B196ULL, 0x104F807777B87470ULL, 0x3063981613D6F95DULL, 0x059AA6B02F07F7D6ULL
        }
    },
    {
        {
            0x3BEA3EE1E7E36C42ULL, 0x43423431A660B808ULL, 0x94ECE62E2F534455ULL, 0x2B123085E53F5BA9ULL, 
            0xD2EDE1BA643E9878ULL, 0x76F27778BB5B196CULL, 0x1B1341B3A6963D11ULL, 0xEF23453520F4F0A8ULL, 
            0x1F71B5E591129135ULL, 0x554D9102AB4122D8ULL, 0x899D1EB58221E70CULL, 0x12B53933BC2B0378ULL, 
            0x99C8AC2B15507788ULL, 0xA610ED7BE487C86EULL, 0x0637807C1D4962E2ULL, 0x83844EBF085A3DB0ULL, 
            0xD5B8C505C44DA460ULL, 0x5E4BBD5E4EB97964ULL, 0x876F3AAAF10D1301ULL, 0xD36B3A61A611F9E3ULL, 
            0x6A8EDB438584789DULL, 0x4191CAA74122A15AULL, 0xCA820E523DBB565CULL, 0x3E67CFEDE9E9A4FDULL, 
            0x0132D435D99198E7ULL, 0x32C7667306CE0D05ULL, 0x582496FC00705757ULL, 0xE3695B2DE8886274ULL, 
            0x89ACAED91B5262A1ULL, 0xF2B5F2A0E748BE92ULL, 0xF110E9707F830FF7ULL, 0x29419CB5607F3C80ULL
        },
        {
            0xB8BF7FA511BC4261ULL, 0x69E70380D723050FULL, 0x389283A5B2185795ULL, 0xE0262C330B736C88ULL, 
            0x9B9015DDD496580FULL, 0xE26F62F8A1460A1DULL, 0xCFAD24AF9FDA3B53ULL, 0x45A07815D6217482ULL, 
            0xCDC906DD6A3B24E2ULL, 0x14E0C51E01017BDEULL, 0xA8BE2BF76B7E2DE1ULL, 0xE773CEE1703275A2ULL, 
            0xD64A576750856755ULL, 0xDB97D8E5A8EF1ABBULL, 0x451FE337F8D13155ULL, 0x212182F3A7CC2E51ULL, 
            0xEF25F099532FE4D6ULL, 0x6E38031ECDA57764ULL, 0x6E7DC87F2C8F91A8ULL, 0x05049BC28A8F7EF7ULL, 
            0x9397499EB511EA5DULL, 0xB0472C3DA48D0949ULL, 0x04B66931197047C8ULL, 0x4AE03763BA295C97ULL, 
            0xCD1B3C87FD87C99CULL, 0x2F1650A54FFFF3F6ULL, 0xFA5054BA4C24CF8FULL, 0x79EA0C624B56435AULL, 
            0x3AD6F44C71503ABEULL, 0x4A198F64CA8E6F23ULL, 0xB4DD213BAABC49B7ULL, 0x24EC8A5AB147485CULL
        },
        {
            0xAE72990F556C0DA6ULL, 0xB171A047EDF1E504ULL, 0xC0900F2B63AD8C3EULL, 0x1C99AD89A954B817ULL, 
            0x70D5672ED3796832ULL, 0xDF8F356D09588993ULL, 0x7EC273FD0A59DF44ULL, 0x387597918EAF5716ULL, 
            0xB2D3EE26B9587BDBULL, 0xD8F0016D59094138ULL, 0x891B016E2A9FA3BBULL, 0x8CEBF8B1A3182D1EULL, 
            0x73B2307E7E11EBF4ULL, 0x126ABC08E8CB29DEULL, 0x42AC1E8377170CA8ULL, 0x9F1491B46486E97CULL, 
            0x1BF619123EC51E3AULL, 0x0379C88C5C9680B7ULL, 0xEE7AB8185C8C2FACULL, 0x6D452A785F3A81BCULL, 
            0x3101529CD7A4E464ULL, 0xC6F9AEA03E547455ULL, 0x64E27CEE0228A049ULL, 0xD605066FD0BE557CULL, 
            0xB77D8043ED63C14FULL, 0xF9960F6578E6207FULL, 0x1931E2D9EF508F25ULL, 0x8262F1A6EAFA513EULL, 
            0xFAB53727D0EAA030ULL, 0x277271457566DF9BULL, 0xC7BAEC577C4B9F79ULL, 0xCF091C00DDC31726ULL
        },
        {
            0x57496D215490590AULL, 0x6368E28F2104E0DFULL, 0x358C975A87213899ULL, 0xBCB984F111668980ULL, 
            0xAD9DDE3E3C140140ULL, 0xBC0A34F734C41F94ULL, 0x1852AE90E0070CFEULL, 0xDC70C645E338D412ULL, 
            0x8FA2EC65E9D55614ULL, 0x53129826A46B1769ULL, 0x613B9E5BD3F00701ULL, 0xEBAD9DC367DEE5FCULL, 
            0xDF33107FDA7F56C7ULL, 0x8EDEB8B004E3F078ULL, 0x962E394457E07FF2ULL, 0x8CC29D0E11D3448AULL, 
            0x126D2A926B1EBC19ULL, 0x81C60198B4B81777ULL, 0xDFD85A02E0AE8C72ULL, 0x80B973EE6CDE94B7ULL, 
            0x2B876BE5106A1D8CULL, 0x9958CCDEDE8BA108ULL, 0x48188648522B59D6ULL, 0x5AADA559DA3AE8B6ULL, 
            0x5A6FDCE474C0023FULL, 0xACB6FB18A5FAB662ULL, 0x6352BA802A7EED6AULL, 0x6B027A05D4F02DFBULL, 
            0x9FE9A919BE78DB6EULL, 0xECEC6ECF738D0F3EULL, 0x4ADDA384230495A7ULL, 0x41F1A96DF15752BFULL
        },
        {
            0xA541D72A4DA4451DULL, 0x2B35AEC6FE5DC8EBULL, 0x578B664B3166FD82ULL, 0x8397E07DD76A8807ULL, 
            0x5F7AA43C431F0798ULL, 0x92484977E364C954ULL, 0xA75976A091169665ULL, 0xF2CAADEB3DE1FBF6ULL, 
            0xA78DD8A1974AF0FFULL, 0xE2A66739EE11D8D5ULL, 0x5BD1369292EAAACDULL, 0xE4DA6958802C3F5EULL, 
            0xDDA9E0443B83774DULL, 0x01A14B69178007B6ULL, 0xC4A6E4DA3ADFAD19ULL, 0x9C3CAB7E609B6C11ULL, 
            0xB7BED4421E0C4528ULL, 0x750CC334A7DF8615ULL, 0x2A3942DC8F1E50CDULL, 0x20B4096053628F3EULL, 
            0x992E397EF2AF56CAULL, 0xF6FB824DB7FB1D65ULL, 0xD8C39F2A31A9F5E0ULL, 0x92FCF23E90AA238EULL, 
            0x83F65E54A109D663ULL, 0x671A34C239131B76ULL, 0x1E34782ECFA38715ULL, 0x614B9ED09ED6980BULL, 
            0xB80D4B0F35338FC6ULL, 0xB8B2D38416946045ULL, 0x457E8CC1D3F6F005ULL, 0xF8B865D274262D2DULL
        },
        {
            0x44A0EE2CE0E3C24EULL, 0x49D7DF43657F8083ULL, 0x80D20754381CDB2DULL, 0x2845C8EAD99F8809ULL, 
            0xB775F835A177A2A2ULL, 0xE34A3B4B550E10C4ULL, 0x0F1D97F641778C1FULL, 0xC3DC1B811D01D03BULL, 
            0xC4AEE9A5AD6B9D58ULL, 0xEFDC22D47453F6F0ULL, 0xBC2588354091E5E4ULL, 0x6B0CBBB4BEA465AAULL, 
            0x89E67B77903C4591ULL, 0x1793912E7E8E5005ULL, 0x2828D856ADC7973EULL, 0xE702EF78AAD26641ULL, 
            0x34354ED8E5C4FDF4ULL, 0x3A4E4105A13F5FD5ULL, 0xD8878F3288DFC78AULL, 0x022BD8506EC533E1ULL, 
            0xDC48AE9F86F9DA35ULL, 0x63FE48AA97AC1C3BULL, 0xECDBC50B8E770537ULL, 0x6B6DFD2D9D8E6385ULL, 
            0x3B1597135FC66976ULL, 0xF3B1BFF8D4512C31ULL, 0x44026E824322C4A8ULL, 0xA49CCB2D2A9B3A6AULL, 
            0xED442E7478BA6281ULL, 0xE45FFE40EDD05E2BULL, 0xE2FB2ED037021CAFULL, 0x02221948A6991169ULL
        }
    },
    {
        {
            0x567FA62987D0614FULL, 0xB4C7F4BD7100A902ULL, 0x463664F6BA1A52A5ULL, 0x71F30737F52DFBCDULL, 
            0xC90175D8E4E64503ULL, 0x7D71E8F712C75D52ULL, 0xADB2734591E0BB1DULL, 0x680F4191BB46547DULL, 
            0x1B7CDC9DDBB5EE36ULL, 0xAD299E76BD033F4BULL, 0x844AC608DE8F5666ULL, 0x2BDB202D7F5DE0C2ULL, 
            0xD3AE563C411C307EULL, 0xFAA9DE95B733D4F7ULL, 0x87A36BE408FF8C01ULL, 0x61D9A42A995A19ADULL, 
            0x8280F9572815B6E8ULL, 0xA23435D2C3F3E652ULL, 0xD201C4BB720E2003ULL, 0x23D2DC03FE5B8CC7ULL, 
            0xFF0DD08BE5AAE6BCULL, 0x912864D774EB6580ULL, 0xDBC814CFB318E01EULL, 0xAC3D25FD9666157EULL, 
            0x247641A7314787EFULL, 0x77BB188515B56C85ULL, 0xBBAEC4C825DA9CFFULL, 0xC8E59DD06DFAE6A5ULL, 
            0xA454DB6187940A0EULL, 0xEBDBB3F82E2C305AULL, 0xF2AC4F6908EECDD3ULL, 0xAAD94618FA789A49ULL
        },
        {
            0xCA3D92B3D47F2CF5ULL, 0xEFB63E3EB3699DB9ULL, 0xA768BA705FE81BFAULL, 0xC9F599EBAA15022CULL, 
            0x5BFEB7B128391F8AULL, 0x89A8C15D288A7A55ULL, 0x09CE0EDC84F4B731ULL, 0xC9FDD27A1EBE3F17ULL, 
            0x553DE8F423E3B100ULL, 0x84FE55CA09B82B16ULL, 0x1CC3CB826CE21BEAULL, 0x08FD839C7386AE4EULL, 
            0x7085FD1237ECC108ULL, 0x324AE21625A588A9ULL, 0x664197BE225282C5ULL, 0x8606D4472A49B0CFULL, 
            0xA599B46CF6CF87EBULL, 0x0E802A1F7AD7920CULL, 0x0760283A534A8068ULL, 0xC589A5F1FA20792AULL, 
            0x0100AC907B42AD09ULL, 0x2309229842A09048ULL, 0xD61EA9C83E5D45B4ULL, 0x08DBD5ABBF819B9DULL, 
            0x34CAB2894B5BF4DFULL, 0x46853E5857F54C1EULL, 0x193E28E792CCF0A7ULL, 0xEA7480CCBDB08FEFULL, 
            0x00E3FC1198808E55ULL, 0x0A6153BD384C0878ULL, 0x0D49A9EEAE484A65ULL, 0x972366673C46279CULL
        },
        {
            0x31F4DA07755D5FA4ULL, 0x76E1A437B5BE584DULL, 0xD961DA64CC4FCC03ULL, 0x5BA69775BA5A3EF6ULL, 
            0x349C6E6983C89951ULL, 0x90F0EB2AABF19D93ULL, 0x4445252148C809D5ULL, 0xB924570C554C6A6AULL, 
            0xF98456B4B4F91329ULL, 0xC2EFA98ABC54B689ULL, 0x6B41B5C883118859ULL, 0x8394FE814E09CF30ULL, 
            0x33EB6D19EBAC4B9DULL, 0x7B8D0E9DA09ACD95ULL, 0xC67060D843C2A160ULL, 0x3D1DAC76DB212938ULL, 
            0x938FBA2F8EA21E6BULL, 0x34D66D6D2A8C1B02ULL, 0xCB04CA22FF2BA824ULL, 0xC775F37E8C3E7BD8ULL, 
            0xCD83301744C54A23ULL, 0xC82EF82D14A6E73CULL, 0x6CCA51A29F6750E1ULL, 0x00C01FEB1A0C2FDCULL, 
            0x9538E58BBC9B103BULL, 0xBFF2FBA2E00183BCULL, 0x423CB60E6250A51DULL, 0xB1D10A05FCB08E9FULL, 
            0x5455ABB473E098A2ULL, 0x9D6059B075A3F038ULL, 0x56AA5C20A5B97685ULL, 0x76156E6E45108285ULL
        },
        {
            0x8FA523B850C21CEFULL, 0xBF10341022ED136FULL, 0xBD20EB197921939DULL, 0xF566FF55ABB7F4DDULL, 
            0x2266029DEEAF2948ULL, 0x931567A6083A28F7ULL, 0x1D61FF6584A82A33ULL, 0x73540FDFEC7BF3DFULL, 
            0xDA2F430C35D2D1B8ULL, 0x7C92BE098BA9ABADULL, 0x62E9E0A7633B1CCBULL, 0xEB475708915FB33DULL, 
            0xD2BA6E1DC5FE4BC0ULL, 0x677E012F9475C560ULL, 0x2AF2CD937098B170ULL, 0xB582FE9FF57CE0E0ULL, 
            0x44B34B98C2026C78ULL, 0xE3AE7C767F045436ULL, 0x649E531F96192179ULL, 0xB5CC7CE155AD7FAFULL, 
            0x53FB38974508FD91ULL, 0x52BD19C4D0C83B8EULL, 0x29877DB2B7A9F7E7ULL, 0xBAB1646DB7D9ABA0ULL, 
            0x83B04E32F2D855AFULL, 0xF430A205FA10AA13ULL, 0x0E59BB844474760FULL, 0x53C3727245EF5566ULL, 
            0xDFD97F4A931A017DULL, 0xF99F6E436B3BDCF8ULL, 0x2BB277B6D3124B29ULL, 0x3FD2A94FC211AC7BULL
        },
        {
            0x45095EEA3841BCD8ULL, 0xE8ED2997C6A63ADAULL, 0x29DE8111A850952BULL, 0x4DD68605A6B04526ULL, 
            0xF41D81A1CF707F19ULL, 0x2766D036B30284CBULL, 0x85830F3F305A8209ULL, 0x02376A8F35C8D07CULL, 
            0x1F7970ABE988E72EULL, 0xF3CD338510A09AA7ULL, 0x2A0A57FD8DA9E1B9ULL, 0xA9B25452BEEE6A94ULL, 
            0xBB0AC03ED0B4FC1EULL, 0x91D2CD5382A0A9E5ULL, 0x82A695E8E9DF8AE2ULL, 0xE9B9D03106C3FD2EULL, 
            0x9A97E1F430354EDBULL, 0x73A2BF4C31C96FE3ULL, 0x92E222055409D12EULL, 0xA28737CD269B96BDULL, 
            0xC239791BAC6BF008ULL, 0xE80A424E976BF4A5ULL, 0xE236F014423C1E58ULL, 0x3F1F01B457F54826ULL, 
            0x722D1A6EF99AD04BULL, 0xD2E4E22838A100AEULL, 0xA20C3C9CCD624FB1ULL, 0xFCCD6754F1FD0155ULL, 
            0xD53993DEA0EEB84CULL, 0xFAC925E18A3A19C1ULL, 0x70E1959D0830A3EDULL, 0x8C612826D4C46E35ULL
        },
        {
            0xC0A83F8787C19F6AULL, 0x51F90D46BD35E74DULL, 0xC3FFA0B53F2076C9ULL, 0x8F4AFFCD8F88A707ULL, 
            0xEF45001CEFEF7E96ULL, 0x269122A005B9D6CBULL, 0x8F6DFB04032C0EEAULL, 0x31F3BBF1CAAB7EB9ULL, 
            0xD058A451A804CEF5ULL, 0xDBB40F9DDE93B9E5ULL, 0x799B447933A32547ULL, 0xD79A4C2200ED8F6DULL, 
            0x5F15A1744848F949ULL, 0x4061CE6CCA20A65FULL, 0x479306726CE723A0ULL, 0xA3E716B274811228ULL, 
            0x87EB04CB7ED4417BULL, 0xCAEB6CE35DF069E6ULL, 0x12A527E18AF56392ULL, 0x05703C8A99224974ULL, 
            0x46CFA0891C510AF8ULL, 0xB6353CB65345CEB5ULL, 0xC5642A65ACD8993CULL, 0x0A318A6D74EA6B9AULL, 
            0x21BDDC3743FC1B24ULL, 0xAABB372C4716EF7AULL, 0xA8C5AEFE58DD2682ULL, 0xB2B1799DE83218ACULL, 
            0x2A01AC6876D0A82EULL, 0xBFC103A8A0E943FBULL, 0x7CFD8837C1919D91ULL, 0xE7668055941605C0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseDConstants = {
    0x44645D109FC94FE1ULL,
    0x37FD7E0E1BF77F70ULL,
    0xDD43B2A58554AF04ULL,
    0x44645D109FC94FE1ULL,
    0x37FD7E0E1BF77F70ULL,
    0xDD43B2A58554AF04ULL,
    0xF7A1E1E40408F0A8ULL,
    0x26182F25B5ACFBA7ULL,
    0x5F,
    0x2F,
    0x5B,
    0xC1,
    0x28,
    0x41,
    0x3E,
    0xCE
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseESalts = {
    {
        {
            0xC1EF6A6C0B2D673EULL, 0x5EE13E787450420EULL, 0x6D2A3F362BA63192ULL, 0x33E12B42615EFAEFULL, 
            0xA63C05B8F6AC466EULL, 0xC26A697B3D8CB2FEULL, 0x298E678EDAEC4F29ULL, 0xB54F61AA8A358BD0ULL, 
            0xBEF5B2757908CAD5ULL, 0x817E41A3D09A47BDULL, 0xFD6CDDDDDEE8A38DULL, 0x1496B388EB8CD03BULL, 
            0x5C31C96AE2C06A33ULL, 0xD30B55D389B3EB9AULL, 0x0EE023AF2E11A633ULL, 0xACE636139C500B90ULL, 
            0x68C9A71629272664ULL, 0x4DDFFCDB10B7E155ULL, 0x24AFB99540A2864BULL, 0x03F7BB00626D7ADDULL, 
            0x36D8D7E7EB8D11E7ULL, 0x0A333FF764BDA380ULL, 0x16E8FCBD015E9F7FULL, 0x64654732108F6BC6ULL, 
            0x3120B03EB619CF33ULL, 0xDCD1E83EDA11D23CULL, 0x035ED3A55686568FULL, 0x452A795304404619ULL, 
            0xA715B95C62B90FA8ULL, 0x195E90A26909F578ULL, 0x1E5BF256B65607F4ULL, 0x7FB27F735D81614BULL
        },
        {
            0xD3301A158F643480ULL, 0x4DB0CBCEE7C270B3ULL, 0xABA49A01DACDF93BULL, 0xB066D3E48A8C2963ULL, 
            0xE9124AE30E8F9D61ULL, 0x42E712951762A95BULL, 0x08E9FC8C4D52441AULL, 0xC5E09A337AF9233EULL, 
            0xB5C0580274E5BA19ULL, 0xBC706C03D2999A1CULL, 0x750ED5DEE23229F6ULL, 0xD4C93806BA3846E1ULL, 
            0xE712B65A161171C4ULL, 0xE02CC41DF865E927ULL, 0xBEE08EF60595DC69ULL, 0x4D023068AAB87868ULL, 
            0x06E1801F3E2EE810ULL, 0x3F1E4BD9C0758881ULL, 0x72B05644AAA5B315ULL, 0x8D96C9FC662E42ACULL, 
            0xBAC0B15E7C3F759AULL, 0x9C2A34CA1646C4DCULL, 0x8A9B62B2D562F2F1ULL, 0xF92D023248E97192ULL, 
            0x2E40B18C48BF65FAULL, 0x04E52719F6FA727CULL, 0xB372AFBC40B482CAULL, 0x6E2994A24B15B527ULL, 
            0xC556B4F6B5274C2CULL, 0x096C88C0325503B4ULL, 0xBDF36E89CE74B336ULL, 0xDA95A9E7D119B6EFULL
        },
        {
            0xEE95D5E1D3B2B040ULL, 0xFF3C55A36367EDFCULL, 0xBD170EE65BD16AE0ULL, 0x47DA3DEE937C43ACULL, 
            0xD0323D452669FE2DULL, 0x584246D934B9490BULL, 0x3093F4EC136D5FF6ULL, 0x5117E6A21A2CCFE5ULL, 
            0x1166C026955D95D4ULL, 0x02370B4A6AAF0C3FULL, 0x205F0B1EB7F2EF43ULL, 0x4CE6F1409FF92C3FULL, 
            0xAF89EFC727F2C1A7ULL, 0x9CF4E3F6A9594F32ULL, 0xEF352814697EDB07ULL, 0x55A2C9DDE7760A4EULL, 
            0xCFA60465D79BBA58ULL, 0x487547381A4B5BEDULL, 0x5A5586352097E33DULL, 0xB211544A80EE2873ULL, 
            0x6DF71742EEA7E4A4ULL, 0x945C5A9A8873AE0FULL, 0x7A7CD1440E8DEEBCULL, 0xDDBAF845ED25AB24ULL, 
            0x1D18D45619A1FCA5ULL, 0x2572E6D70F7FA571ULL, 0x293517669E442414ULL, 0xEE19805067F137C4ULL, 
            0x1D8F6BAAD9EA8569ULL, 0x29B5131E2D7D5586ULL, 0x9FCF1994E3B536D9ULL, 0x5437E0083068793BULL
        },
        {
            0xF7FBC599D407EA49ULL, 0x75D65AA36693917CULL, 0x6FC771C92B68EF3DULL, 0x69F7C66572BEF6E7ULL, 
            0xB69B5DB60606E1C3ULL, 0x2D941E044CA4C039ULL, 0xB2D52CB6AE1FD3D4ULL, 0x2E97ABBE2BCA02C1ULL, 
            0x451E9CE471CE724FULL, 0xC2857B8711C6DB44ULL, 0x2F5A7A36872D2390ULL, 0xB12AB599FD450575ULL, 
            0x2BE03CCB4176D035ULL, 0x6B06340B5F3CAE2EULL, 0x3394A1451739619EULL, 0x5CB697C7749141D3ULL, 
            0x87364F319BDC7DC0ULL, 0x4843A888ED99F82EULL, 0xE7715A898E927459ULL, 0xE847A12C4A126C1FULL, 
            0x728D14D2999234EFULL, 0xA27E10CB8EA31FD7ULL, 0xB20023AC2E3BA6F6ULL, 0x4091EAE7AE9587F0ULL, 
            0x5F6BA033378060FEULL, 0x47194ECF637BBD20ULL, 0xDCF3DBF678D24356ULL, 0x356EBB78ABF7C120ULL, 
            0x5A94CAC6A814F91DULL, 0x88954E105D850B6CULL, 0x2568DC965E9E10F9ULL, 0x486B1C4AE8A5FECAULL
        },
        {
            0x34131C3875D5C50DULL, 0xA046272A42D33517ULL, 0xF75166CE98C2169BULL, 0x577792576A037B99ULL, 
            0xD21BC56B5FA6D529ULL, 0xF6D1F8C5CF2D5FD5ULL, 0xF6D4C3605220484FULL, 0xF56F4226EB8D3840ULL, 
            0x5E9B2BCEC7B0979BULL, 0x52726AC56A8F2976ULL, 0x194510CA0AD16BC8ULL, 0xAC623F4AD2A69600ULL, 
            0xE1B4D70CCBC5941BULL, 0xD4CEEB5B259DB809ULL, 0x3D429C4CA0F69C21ULL, 0xF9E666DC514725D2ULL, 
            0x07DD96DCBCE70555ULL, 0xF130F33326664D76ULL, 0x1C35E62FF3B59A5FULL, 0x50B62476959A5AB7ULL, 
            0x9AAD4C5A0774803DULL, 0xA491E7A17478D61BULL, 0x9128585E9D129AB5ULL, 0xDE744251C89CEBB3ULL, 
            0xDC2D0F8B25BF1816ULL, 0xF670F1D48FAC6348ULL, 0xC3F171E3DFD3FAE9ULL, 0xB2334CDF589E8D9AULL, 
            0xDFE9927BE0FF7D06ULL, 0x7032B1FFFAB7533FULL, 0xD5376DBCFA364DB5ULL, 0x1AA5A879E795E600ULL
        },
        {
            0x0116EBD00562C411ULL, 0xAF83D7C983A28687ULL, 0x1FDE1EA4E5570E26ULL, 0xEB5DE5F3D1D55C16ULL, 
            0x7DEA9259865EC901ULL, 0x1F13B8E7680F648FULL, 0x22091D67DECCCC6CULL, 0xB63DA2E9F0D03448ULL, 
            0x3CC214C0C8A3DA51ULL, 0x1025C5AD5D15AA35ULL, 0x250CEB68716C4DD8ULL, 0x9D8B73187B5DEF0EULL, 
            0x81D36BD8E37CA475ULL, 0xD762601687B0F1BCULL, 0xD9823D65B85800DAULL, 0x731CCEFDA550D437ULL, 
            0xF32CE207B3775C18ULL, 0x14C601D262A6BDF8ULL, 0x52E2E15853DB80A7ULL, 0x2233E64E6BBF6D9AULL, 
            0xAFBB2154D37F71ACULL, 0x0C8D0C7BF45D1881ULL, 0x577B9B7F0C98AD7EULL, 0xED3B11991F5BDF9FULL, 
            0xC2B1B63951E1695BULL, 0xEB066E475867BA5EULL, 0x14300B95BF9297BBULL, 0x4557322DFD7B2C52ULL, 
            0xA67AF1098A1E9E60ULL, 0x71D6E35271812A56ULL, 0x63DB1BCD9F39AAE1ULL, 0x78E047CA62EB6605ULL
        }
    },
    {
        {
            0xEAF833EC7FA8D09BULL, 0xAEFEBF7225A5BAEDULL, 0xE8FB4697960375F8ULL, 0xB737DE08F264CBAAULL, 
            0x6E89747EBF53998BULL, 0x9CB0DBC9D406FD58ULL, 0x3CDC8F820CF6A046ULL, 0xB9A25A6C74CC8DBBULL, 
            0x02DD565DACBC1C00ULL, 0x063CEA20D2457FE4ULL, 0xA217667D5C972D8CULL, 0x271BB31AA568B926ULL, 
            0x13A2CB9200E6BDCFULL, 0x4F386768406800BEULL, 0xFF3B353E4CCF84B3ULL, 0x69448B06B5AE02AFULL, 
            0x62B8DF7577AF4445ULL, 0xC954F903E47E6A54ULL, 0x21044A24251DE02BULL, 0x6AF46F513BA5FC76ULL, 
            0x1BAD8E878A10B91EULL, 0x9362BB94EB2A689DULL, 0x98702690353E6A90ULL, 0x84D54FA715FA11CFULL, 
            0xAD1BB494F3A27D72ULL, 0x7FFB37BEA34EDC17ULL, 0xA4F0FFE6955B88C2ULL, 0x6CC9857BC3415726ULL, 
            0x5018D617417EEF09ULL, 0xFBC0359190367C16ULL, 0xC1EDCC8C1FD59D45ULL, 0x0C30BC37F46469ABULL
        },
        {
            0x23F7C17A5E4C3AF9ULL, 0xB51C278527265B4BULL, 0x319894061F8A9F58ULL, 0x61F307A3CD6CCE6FULL, 
            0x69978D3A645CA0D3ULL, 0x3CC6F5CB6ACAFDBFULL, 0x804AF4B15607996FULL, 0xDCF5D1127EF62605ULL, 
            0x637EF0F4C4B1F9B1ULL, 0x6ACE910B02093C41ULL, 0x356FEF233DC080DCULL, 0x7AD9DD94708DB83AULL, 
            0xC177C20F9E00209BULL, 0xBECAA3A57B0F2501ULL, 0x3004D053C8A2B491ULL, 0xAFFC89D70EC4ECD1ULL, 
            0x46391B7F10990BFDULL, 0xF5CCD3D881DB146BULL, 0x56036B1361E26589ULL, 0x6A9EF9801212D81BULL, 
            0x7B7A9283419B3986ULL, 0x4A7E020C53AD7359ULL, 0xD3069A12D34E2D9CULL, 0x2736C7B156C128FBULL, 
            0xD4DB6EEB66264560ULL, 0x61F84CCD8FEF2580ULL, 0x6C8821772188D218ULL, 0x75190EC34887176AULL, 
            0xD18F5B59496C5AB8ULL, 0x937CB0959884CD8AULL, 0x8E5F84711F8D89E6ULL, 0x4E7980834E5EF620ULL
        },
        {
            0xFD634BF8A8F2933DULL, 0x805381F0E8FE02F6ULL, 0xDBD02468039AEFB0ULL, 0x1EB8149EF9488D26ULL, 
            0xE22371F46B95CA3BULL, 0x58BC4F4C80964021ULL, 0xCF3045A7C8D805B4ULL, 0x3C4E1901B48937A1ULL, 
            0x478DE2AF90582570ULL, 0x389C155B53B19B5CULL, 0x8D0025B60F4CFD0CULL, 0x0BEA732717E3DFF0ULL, 
            0x8B41FE308330D56AULL, 0xCD2F1B36FB22D5DBULL, 0xE71D6CD5B4AD64B6ULL, 0x30C3DFB9F6A37306ULL, 
            0xDFDB692DCB110604ULL, 0x40C71CEF40C45863ULL, 0xE3A704EA2E92672AULL, 0xBB3DD7ACA0B20378ULL, 
            0x22C5E98C0DE8D6C0ULL, 0x038B58F2BEDAF9B3ULL, 0x005C55C08A22F69AULL, 0xBE3A59CD52C28268ULL, 
            0x4D37E5F55655DA3DULL, 0x721B2AFE54D21173ULL, 0x865765154BC4681AULL, 0x5B1E03BFEEBC002CULL, 
            0x8ED7DA237F0B8930ULL, 0xDA1C4601D2FF2E76ULL, 0xAC7064B96C996E49ULL, 0x15536288D67EE1BBULL
        },
        {
            0x822022F8B146466EULL, 0x9B67710C7A8F36E0ULL, 0xA3D58B0999428555ULL, 0x1C407519F5109D04ULL, 
            0xECB2FEB44BF12934ULL, 0x9FC21B9F51B83D84ULL, 0x42BFDFAAA540EC9BULL, 0x61CD73CDA75183DBULL, 
            0x8B12D49C64C29FBCULL, 0x10348978B2B4AD47ULL, 0x0EB62C0785BED228ULL, 0xC3B694A4FCDC7E01ULL, 
            0x9BA91927E655E8ABULL, 0x4CB849B527B671A5ULL, 0x0F843870227104B0ULL, 0xD9626486FD023B47ULL, 
            0xDA6B72EBD5A003DEULL, 0xE0469EB3FAD5B79CULL, 0x81B33130F906752EULL, 0x65D2EE2839FCD936ULL, 
            0x7F81D3C0D2385D5AULL, 0xD707C25F2DEC1AD0ULL, 0x9DA31B5949AD494DULL, 0x8EE0867B3DEEC91DULL, 
            0xFB457F736E91D46AULL, 0xE1B14B32FC2931C4ULL, 0xFEFBFFC55285182DULL, 0x40ABDD34B1446342ULL, 
            0x759BCFAFA3DF7157ULL, 0x767A32ABD0D64FE0ULL, 0x32DC8EF1131C09E8ULL, 0xDC88A60A7E3C10B2ULL
        },
        {
            0x40D3C16BE18B9772ULL, 0xE388FB0C7C7CDFDFULL, 0xFF63528B53AC2DAFULL, 0x0F45D4D8AB6614B5ULL, 
            0x00D06615EC9095F6ULL, 0xFA2F84C602A4BF66ULL, 0xE431E250C53E0F26ULL, 0x18CB2AEE5A611D95ULL, 
            0x2867230398A18457ULL, 0xE1C100CFEB494354ULL, 0xAC70503AC95734A2ULL, 0x00117CE66CA3E883ULL, 
            0x64DB841ED18FFB73ULL, 0x96DDBA1927458E85ULL, 0xF2D902C279753CC9ULL, 0xEFA5B52A221677A6ULL, 
            0x68F1477BC89F0A35ULL, 0x3233D3FBF8209555ULL, 0xCEB321D48E023B91ULL, 0x570C3F382C42772EULL, 
            0x313DAE90BBE8BFD1ULL, 0x1A3CC4FCFC565851ULL, 0x830AEED895380601ULL, 0xE14E05A1FFB1D231ULL, 
            0x02203C895300B990ULL, 0xC5EB5077A0922078ULL, 0x08418BA00541C811ULL, 0xED9B94662A39FEA5ULL, 
            0xA81A5897933FDAD0ULL, 0x64B94DC912C8F3E6ULL, 0x0FAE59B242F50C77ULL, 0xC84A631A81502530ULL
        },
        {
            0xF0AF888EE8722A54ULL, 0xFF2071576FD15DDEULL, 0x12F775FE364FBF35ULL, 0x142B78ACD6FE1E80ULL, 
            0xC9DAA235F55CF4A6ULL, 0x503CAFCD4090E003ULL, 0x97849453572B8E15ULL, 0x67EE6599036C2098ULL, 
            0xA6381934822CD2D3ULL, 0x948355FACDD7A720ULL, 0x20AA54D89764A689ULL, 0xB6F4426CFE821937ULL, 
            0x531ACDB116E055C7ULL, 0x9E77BC1B0C163078ULL, 0x9154FE8292BFAEC4ULL, 0x51726D6512349029ULL, 
            0x447DF50D38E2774DULL, 0xB007D9A52C47E581ULL, 0x9E8D6D93D51291F5ULL, 0x1BED2DA6CF0778A2ULL, 
            0xA7DBFD1A5331FAE1ULL, 0x5C656BF17CF464A2ULL, 0x4968511B58B23DD1ULL, 0x9AF90C41C2F2B686ULL, 
            0xF1256C75926E5CDEULL, 0xA95C5D335CDCBC78ULL, 0x89E0FC94656ABD04ULL, 0xA41AAA24983CFF91ULL, 
            0xCD40B4E4994137AFULL, 0x9E328764C484D944ULL, 0x4EE4BA23222A7431ULL, 0x6596087A8AED5404ULL
        }
    },
    {
        {
            0xDD020C48718412ADULL, 0xF18797B9EA2ECB1FULL, 0x3F99286B246CD549ULL, 0xEDD4E59484867CB1ULL, 
            0x99022F40DD90FEF6ULL, 0xD0E9F2F0D1EFDE69ULL, 0x19451BE56A996516ULL, 0x2C172A1FA5127FD1ULL, 
            0xF0EFC827842C30EFULL, 0x8E92D628484E63A5ULL, 0x42C7BC8EB765B85CULL, 0xC3C3396A1C1AFF1AULL, 
            0x110A7A42BBFF2BA3ULL, 0xF87334DC1F556F6AULL, 0x593C460DA7B9FF59ULL, 0xAE2115E3CEE45A1EULL, 
            0xED2BD60CF03E2913ULL, 0xF6E12C504C0A8316ULL, 0x024831D67FE5C1AEULL, 0xD13794376AC7526FULL, 
            0x579B4F96CBC6E33EULL, 0xD3ACC6A8E0B52E3BULL, 0x4DDB8C22F1F27718ULL, 0x5519605783B2AB8DULL, 
            0xD8D664376C24B0CAULL, 0x8C647AAAB9CF0678ULL, 0x75D7712951C09F4BULL, 0x00C4D6443E94613BULL, 
            0x0BEE449486007110ULL, 0x41607FDCB27F4BFAULL, 0x9A554AF262123227ULL, 0x64BA77CDB187F48FULL
        },
        {
            0x48210E361BFC6F40ULL, 0x90C2B967F2780FC5ULL, 0xD9610E8DE34304FCULL, 0xD8A88919E5993AE2ULL, 
            0xDED6A94DE6A96339ULL, 0x3F43AB63271A0DE6ULL, 0x18A82FCE98C7592CULL, 0x50A87B53F9C5AE6EULL, 
            0x740BDA51EE952C79ULL, 0x857390BA0286BF2CULL, 0x474AEDDC8F6DB36EULL, 0x2FCEEB463C197B0CULL, 
            0xB013496C1C3051AEULL, 0x9AFCC17980F5B471ULL, 0x822EC43809921186ULL, 0x42955467D8798581ULL, 
            0xC5C3ED7B5E225BC4ULL, 0x79ECAF43EB52A6EDULL, 0x4D9C3F3CD67D66C8ULL, 0x8E036B1C7C7A6048ULL, 
            0xBF9B9D64959232FDULL, 0xD49CB096F2467AECULL, 0x1EA191DF612A161EULL, 0xEFF53AA1F24A83BAULL, 
            0xA93D1A91E228DA2FULL, 0x8F8E016462B0813DULL, 0x375040250D7E47F2ULL, 0x156894E44A86825CULL, 
            0x7B51415045B2A878ULL, 0xABC3697DE8C2FE7EULL, 0x6B26A4CD36F62152ULL, 0x2BED2E17F7735933ULL
        },
        {
            0xAA8CCF31C72CFE47ULL, 0x519CEF6CF639F368ULL, 0x4F5A16FF2BCAEDE5ULL, 0x494726A66C6D18FCULL, 
            0x8E8AEE95C424DC74ULL, 0xCF7EED9C00E42EC1ULL, 0xA6164614EC0D71B9ULL, 0x30021166456AF7B7ULL, 
            0x1E88E250CC9FE8CBULL, 0xA932EFA1CE2C0768ULL, 0xC7171F197CD4179EULL, 0x7DF286035280D71EULL, 
            0x76A7FFA85C5638AFULL, 0xD96F4BF3C05A6740ULL, 0x6657CB19EB427B0EULL, 0x3128377A925107C7ULL, 
            0x5760CA818F9E3D1DULL, 0x6DF56FAE3B4719E4ULL, 0xC1D5548DD2488203ULL, 0x8CC9E1F6AFFE46C4ULL, 
            0x98B67D4A87FBEA1BULL, 0x4073135691442D7BULL, 0x9477401B9C0C8F37ULL, 0x1F382EA8938867D5ULL, 
            0x07E25D45637229EFULL, 0x517A97050AB3871EULL, 0x3D34E2B7E49F94C2ULL, 0xB023B7E14AD8F7A3ULL, 
            0x9F759E0E1B0E2166ULL, 0x1ECB5F0A1B30776DULL, 0x704FD95E176B20F7ULL, 0x8644A2007760AF83ULL
        },
        {
            0xD8CD3B6850ADCF0AULL, 0xAA195284D1F1B9AFULL, 0x825763BE8F2DEC39ULL, 0x3A1DB00E1A29F9C7ULL, 
            0xD81B106DEB864ADEULL, 0x9F7F1108948D75CDULL, 0x73E22CD0CAFE4758ULL, 0x94A5F5CEB826EDE4ULL, 
            0x439E6BAFDC17C142ULL, 0x8E11E0DAC9A9A262ULL, 0x966DB89F0E8FF237ULL, 0x2DFFA357B6A46DCFULL, 
            0xDBA96AC3884C4794ULL, 0x26DCCC75347CC977ULL, 0x173274371B853FFDULL, 0x88C13A085CEA4A3BULL, 
            0x91C4909AC7A353ADULL, 0x7D2397C8C20062C4ULL, 0x1C3AFAABEE84D490ULL, 0x961C5D4AB13212F7ULL, 
            0x8D5568BBA22A280EULL, 0x6C5A9F9A70B0A414ULL, 0x5B252507906F1034ULL, 0xAB0C93E40909139FULL, 
            0xF8A11826EBF63F5CULL, 0x21227CBE0ABB8E6DULL, 0x8BB1B0338111C86CULL, 0x580DE2871E4251E8ULL, 
            0x9CBA7F882D901E28ULL, 0x5E88F1D1E85C5A18ULL, 0x30E76AFE0E2D49BDULL, 0xEF71EFDEAC20B67AULL
        },
        {
            0xC68104EFC740BD71ULL, 0x8E0B0E9E269ADF23ULL, 0xF1833D0536FA0C03ULL, 0x80EDE44C3B78DCAEULL, 
            0x44B096DA08BD110CULL, 0x7484FF62AC9582EDULL, 0x67622234D1C01D32ULL, 0xE7D24543DDC506B6ULL, 
            0x94175EE1C201A888ULL, 0x43A289D79A640E81ULL, 0xF2DE2A6F5057BEC3ULL, 0x4E626966F0B43D6AULL, 
            0x1FC8A033E92708F6ULL, 0x64D6AB23DC876ED5ULL, 0xB63908D8E18A13E1ULL, 0x5D1649B159262284ULL, 
            0xF075FD88219B5D6EULL, 0x8D136191A4BE1712ULL, 0x8BB10DFDE28BA86AULL, 0x51F6D9365DBDA9DBULL, 
            0x574D134D0BA22777ULL, 0x1501FF174B8F7E56ULL, 0x2179B573E15259D5ULL, 0x173925964B2BA88FULL, 
            0xF913B30C0F35BDE0ULL, 0xE61452468C12D96CULL, 0x4B06FF120CC0E420ULL, 0x3B90316421E4663DULL, 
            0x5E5378FB2492F96FULL, 0xB6A62FFF86453C5FULL, 0x9CB99F276AEAE003ULL, 0xC5D64667A408FE5CULL
        },
        {
            0x3761299D8535E77EULL, 0xD357A824B5D9FC7CULL, 0x35C298EACAFE6A65ULL, 0x7DE26A08914DCEDAULL, 
            0x05E65BA0A13D2966ULL, 0x5E17B5FAE1E299F7ULL, 0x53B5D5D8A1866E5FULL, 0xCE732120C7183C9FULL, 
            0x8C3BC0F2F24C2FAEULL, 0x4A790CEF10CA773EULL, 0x0D62A07A73F684C1ULL, 0xD780F638D4A3E855ULL, 
            0xFF0D05A8202A7FD6ULL, 0x791534818E8E0803ULL, 0xC8E4582CCE899C91ULL, 0xD1D3015F2A1E5320ULL, 
            0x7205A4BA2D0589F8ULL, 0x32EA67318C89A447ULL, 0x5ADD5833AACE2F94ULL, 0x3C2E4637B6CC1C3BULL, 
            0x8B0F842AEA712C7BULL, 0x537DF18EAF6AD4A5ULL, 0x0EB07381AF0813D6ULL, 0x8662B29DA3B2D6A0ULL, 
            0xC52CE09071D11708ULL, 0xA6C42E24803152C3ULL, 0x786DD5BA4F546D63ULL, 0x92AD652AE6F07FBBULL, 
            0x3A7E46F49738F093ULL, 0xCB1B9D1FC9D5CB1DULL, 0x409C598B01B1BA4BULL, 0x15F4C80C89099EB0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseEConstants = {
    0x3B7DEF9E92DE265DULL,
    0x9B1F791506B60B76ULL,
    0xC7A397022887DED5ULL,
    0x3B7DEF9E92DE265DULL,
    0x9B1F791506B60B76ULL,
    0xC7A397022887DED5ULL,
    0x7413C51C301D608EULL,
    0x176139C4AE3662B0ULL,
    0x86,
    0x70,
    0x1A,
    0x75,
    0x1F,
    0x5E,
    0x5E,
    0x34
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseFSalts = {
    {
        {
            0x3D59F406D6BAF36FULL, 0x3D3846DAFDE5955BULL, 0x0D677E59C008FD28ULL, 0xD3040D1794DA82B2ULL, 
            0x02DCEB18713BE253ULL, 0xAF6B85B6B04210CDULL, 0xD73BA86F2423D920ULL, 0xC8947401528A1150ULL, 
            0x7309436ED1B4B582ULL, 0x693C9C4B10BB2648ULL, 0xA9CD2D7ECE4DFD54ULL, 0xFC611E514DD0CBFFULL, 
            0xE9B5E252ECE7CD5AULL, 0x6F7512E3E3499461ULL, 0x7DB97E7D58BAEA75ULL, 0xE5591DB74573AA9AULL, 
            0x7331F82B305F2E5DULL, 0xD43614B012D366B5ULL, 0xB45F8255912FB66FULL, 0x4236AA129CEC0752ULL, 
            0x999D43DBD081894DULL, 0xBC01C8FD55EF9D52ULL, 0x05E8BA346E8BCE72ULL, 0xAEE8BB90DCA0C8D3ULL, 
            0x7246BEC9DB307425ULL, 0x6EBBED973405DCBAULL, 0xF474306A8EBA7CDDULL, 0x6A9C2503F4A84CF4ULL, 
            0x32C36919B39072C4ULL, 0x0411EC4F5C37D6EEULL, 0x150F77343C6CE97AULL, 0x00401758439950FBULL
        },
        {
            0xD18DEF499132150CULL, 0xBAA33BCAD4AD8B9FULL, 0xDF44B30D598F7C99ULL, 0x0EDF2EB4B853EB3FULL, 
            0x7425DEE3E438EE6EULL, 0x4C787A87D563F356ULL, 0x93CCCFAF407C33A1ULL, 0xC5A0002A004BF4CFULL, 
            0x2902D6014FC7F234ULL, 0xCC930F06C58C3C64ULL, 0x603D13FF177FE49BULL, 0xEC82E3E6FAA0059BULL, 
            0xF5F27EBE9FAA25A8ULL, 0x985BCE3329B94B94ULL, 0x4069C68CFA4DDB9FULL, 0x44D46785D2A7998DULL, 
            0xCD134152F3A79C51ULL, 0xE2CFDA0274C89147ULL, 0x52D100559E976A16ULL, 0x7E9BD11CBBE22DD0ULL, 
            0x7B1E155B98C63FE4ULL, 0x0A1353E5B4ECDEC2ULL, 0x380462102797B077ULL, 0xB3D87AEF746572BEULL, 
            0xA4DB581F6276F3C3ULL, 0x1244A9003E022EDCULL, 0xACE598280BC80165ULL, 0x7CF4A5A9A34F20F3ULL, 
            0x709C67E145A29193ULL, 0x11ABB9BDCB97E9A5ULL, 0x04B75C5C14D4407EULL, 0x9B4913D94E4B764AULL
        },
        {
            0x7F0E539714F42A51ULL, 0xDA9B629D7054B28BULL, 0xA00D9AEB4A2712C2ULL, 0xD5B2FC58807E3C01ULL, 
            0x7A65F12878731F3DULL, 0x6FC85B6C8DD27634ULL, 0x4ED2E9EC07104429ULL, 0xF437EFC780A0D8E8ULL, 
            0xE665B39A2574DDF4ULL, 0x55A370EDFBA3783BULL, 0x88BFF15000BE4069ULL, 0x1FA047DA13F53735ULL, 
            0x8AD25BE50A8EF3E3ULL, 0x6353F834A3865E42ULL, 0xB22CD85E37F5F339ULL, 0xD55965765EA31F1CULL, 
            0x0BBFFD91948D4824ULL, 0x1FAF739EAC676461ULL, 0x43E00A9118AF95CFULL, 0xD71F67252320242FULL, 
            0x137641E1A4AD184AULL, 0xB59F7DE80EC82221ULL, 0x6B9A19E5945AE3E2ULL, 0xCCEE6143768CAFADULL, 
            0x6501DA516419D39EULL, 0x5F507143C397082CULL, 0xC8A73A2F97C0B3FDULL, 0x6C8D3EE87B3074A5ULL, 
            0x5AB579D88834CFCCULL, 0xEBC2D2092C156C16ULL, 0x4B240BE819A8C690ULL, 0xF49348573CBDC910ULL
        },
        {
            0x35039F69D08387ABULL, 0xD00CA5FFD14AB53FULL, 0x5064BA150E42868EULL, 0xAA2B8B64BBA78E1FULL, 
            0xE437011353EA6450ULL, 0xFB9B984DB4EC93B6ULL, 0xA2E12582EB93EAB1ULL, 0x171C18FD08A38BDAULL, 
            0x520E05D9B63CF6CCULL, 0x3B965CFC267E9E17ULL, 0xC58A1987DFFC2633ULL, 0xCAE8A6DBF4DDD486ULL, 
            0x7E5613BA9126564BULL, 0x5DC745FDE5174BE1ULL, 0xB15E3499B929DDA8ULL, 0xF1D992B5F3625899ULL, 
            0xF65E406CD7452DDDULL, 0x28C6A08495649AACULL, 0x4DF7810EA056ECCAULL, 0x55834D8961871336ULL, 
            0x34DC5D3FFFDC36D7ULL, 0x71F8B6C591EDF8F0ULL, 0xE20949747C448760ULL, 0x292D256512A45401ULL, 
            0xEEF4422FFECEC706ULL, 0x99BDD8D18B0B823BULL, 0xD156AA725AA21D31ULL, 0x4CF7163FBF232C68ULL, 
            0x8034FC582F3572CBULL, 0xF26E5EB4909B9141ULL, 0xCB1F7774E8F8A5ADULL, 0x66B55F6935DA9460ULL
        },
        {
            0x2DCE9C060FD0B3E5ULL, 0xC2A76A5EA069BA00ULL, 0xC305F7C0D023446FULL, 0x19E095D9D3B8A6C4ULL, 
            0xC8CDB024701014CAULL, 0xA11D74EC6907212BULL, 0x0CAA49EB86B12F16ULL, 0x8F5E8744CE84A9E7ULL, 
            0xBDDCC86C80042910ULL, 0x622F065C4520BA5AULL, 0x9E0D6844E18E2529ULL, 0x6935D7CA1A6D1F84ULL, 
            0xA7C55B5413D71088ULL, 0x3E43838BFC9BB0DEULL, 0xD60B7ECF7B0AEE65ULL, 0xB629797C975CC5C3ULL, 
            0x4460D90A161490F6ULL, 0x2EDC2BEEF63E6E26ULL, 0x2ED802500D17C4F0ULL, 0xAEFDF406CCF51A9CULL, 
            0x742A835DC81F1E42ULL, 0x09C03F28ECF6AE07ULL, 0x4EED1469B2C39FF0ULL, 0xBB7B3433FC9813B2ULL, 
            0xA4345E7676E3EE04ULL, 0x4636B5C1C83060D3ULL, 0xFB7AB0BE5B164970ULL, 0x633BBBACD1048056ULL, 
            0x919487A5E5CAB5A0ULL, 0x84DD99A376E0C04AULL, 0xF0DC7E14D0D6E152ULL, 0x8C5EE3E59DD44CF2ULL
        },
        {
            0x206E20217C4E29ABULL, 0x8DF16319DFD7A298ULL, 0xA5FD802B9C2AD354ULL, 0x57343A9A68A83A15ULL, 
            0x22AE82CCD6CD8E47ULL, 0x452F22ABE1670281ULL, 0x21B8EE89225C85D1ULL, 0x96B03DFEC2FB9E30ULL, 
            0x8C6D092BB7127A3CULL, 0xB83A82C89EC92A7FULL, 0x95964885F4348237ULL, 0x144F374FCA0F41A9ULL, 
            0x461D211060B18D8FULL, 0x31063ED61E74AA16ULL, 0xBF4A32C59A296AA6ULL, 0xC6807156E95A3629ULL, 
            0xD85193FBA185A251ULL, 0xF5AF4DC28FA005B2ULL, 0xB52545F2C50FED31ULL, 0xCADFADE72A5D203BULL, 
            0xBA21133400DA8063ULL, 0x14C263A8D0F3E6DDULL, 0x409A7B87D5847A8CULL, 0x26AE78DB7082EF7DULL, 
            0xFE297806793BEB29ULL, 0x54D06C3821DFCE6CULL, 0x97ADE45D065C8461ULL, 0x7F64F0E7F43EFE46ULL, 
            0x6D6402438CCC1F1FULL, 0x8F7AC561D12ECF40ULL, 0xA6CFCE206169D6A1ULL, 0x48F064717CC3A8E7ULL
        }
    },
    {
        {
            0x5C11AFB37B7DDA6EULL, 0xF7EEDEB8E1B8A21AULL, 0xE8D7437BCB20509BULL, 0x53D0A2B27D1A721AULL, 
            0xC268B5659EC36836ULL, 0x79C4D2A79A0929A4ULL, 0x7C17B14D6AB4F38DULL, 0x4F18E078C511D90DULL, 
            0x95509DFBD15F3E24ULL, 0x9E4E55FA058E58E7ULL, 0x8803E75A41685515ULL, 0xDDE9B3958DBA6780ULL, 
            0x69CA799E4BE59743ULL, 0xBA3D3F0C2C49D0BCULL, 0x18CAE60EB0618C60ULL, 0x7ACDE98C6FD6FA8BULL, 
            0x9782D06231106C0BULL, 0x872AA530AE926B57ULL, 0x82F1D1852B36C7A3ULL, 0x9AFAD188CE8F63C5ULL, 
            0x13789C3019BC5850ULL, 0x9384F095CE0F9B55ULL, 0x053FC5E0E78EB130ULL, 0xD4B64DE8D847E1B2ULL, 
            0xDE9D5B3C3D42B213ULL, 0x3E4922F0B025C929ULL, 0xB82E2C95783393B5ULL, 0x225C7E8D76C2A4C9ULL, 
            0xDEC93D3E7E961DF3ULL, 0xE482D37B472421C2ULL, 0x7A68CF4965994ABDULL, 0xD7D9D67E11BFB7AAULL
        },
        {
            0x1CDCAAB643FABB88ULL, 0x4B9395C8FD35AE90ULL, 0x5AC61861AB749ABAULL, 0x784A414FEB4ACB18ULL, 
            0x04C77B59A1E91C73ULL, 0xC83CD3B06FD7400CULL, 0xF871513572F235A6ULL, 0xE447E63E1C3FF2E0ULL, 
            0x54B49669CC5F1A69ULL, 0x1DEB3BC6D6AF492DULL, 0x49AD22EC1761C8C6ULL, 0xE801AEF56D260CA7ULL, 
            0xF5B804A7E14F28EBULL, 0xFFE660516C468659ULL, 0xFA92D208FD5C64C2ULL, 0x14CE5C51BF13E87EULL, 
            0x29F985EB9355A841ULL, 0xC47776598089D3EFULL, 0x99B965D333D50CEEULL, 0x261F7CC468D81811ULL, 
            0x2438AC5113FF5F8FULL, 0x3134BD7659FB2E39ULL, 0xCC858C5A6D4D39C5ULL, 0xAF79E05923095353ULL, 
            0x0BFB1F5347C5F55DULL, 0xFD1CFFB6FCF8A66FULL, 0x63A58B10C02E390FULL, 0x68BA1915826731FDULL, 
            0xDCDF712EDB659D16ULL, 0x548825D15BCD4027ULL, 0x775703F29DD274FCULL, 0x4AFB3885E56562DCULL
        },
        {
            0xF77F84EC21F81D3FULL, 0xF2FFC8874EFF1679ULL, 0x8D88A81EC4C887F9ULL, 0xD74E3973961CE652ULL, 
            0x309A68F949D0551DULL, 0x87D42BD21E2F312DULL, 0xE3924C025F394EE6ULL, 0x15C5B4089EB7E8BDULL, 
            0xA21E5B8515FFE1C2ULL, 0x8DC2A880CA6CE8C6ULL, 0x1A617F9A582E54DCULL, 0x72775FFD965F7529ULL, 
            0xFE2FB6A192703FC1ULL, 0xF745593BAD4AD692ULL, 0xD9D4860BE8F04414ULL, 0x14CEA851FCFA4F99ULL, 
            0x0FE5E6FDE32BC365ULL, 0xB191691925D1200EULL, 0x53AB859707A958DDULL, 0x72C954239CB9FFBCULL, 
            0xC8EFA1134974EC8FULL, 0x20E045AB0325F61CULL, 0x1D8C5AADFF6BF79AULL, 0x957E6F45AB0288EFULL, 
            0xC6CE604B7456AADAULL, 0x8B6B4DD0136455B2ULL, 0x1659A634D833D0AAULL, 0xA7B3F127706471CAULL, 
            0x367ED23E98F89FE3ULL, 0x4F2AF4F469A9C967ULL, 0xB4961FC4D7C86B3EULL, 0xA2700C3EE36963B8ULL
        },
        {
            0x002E0EE38972FFBDULL, 0xA0A20E1802783DEEULL, 0x487EEECACB1ACC1EULL, 0xFF8C0C3B510901FDULL, 
            0xE7659B5253337F41ULL, 0xF93BC42B684100B6ULL, 0x36666FC524AC998BULL, 0x9C86371366C0FF8EULL, 
            0x849DF9E9A9B91288ULL, 0x99C5860A2EF9A95DULL, 0x666065F98FDD930AULL, 0xB7FA37E7FD43A5E2ULL, 
            0x6321369B3F9492F0ULL, 0x1AF5AFB89E0A7E00ULL, 0x684B08B83F8212E4ULL, 0xCA7784A69435338FULL, 
            0xF21FE7EB9DD33D32ULL, 0x4A2AB0137EF658FCULL, 0x175F084AF0E35B46ULL, 0x9B9A3359A8E5556CULL, 
            0x52E30C91C33E9778ULL, 0xB4C0E1CE7649C1B0ULL, 0xDD7AAA9F8FBCB792ULL, 0x2B6611AE037F1C96ULL, 
            0x8304854BB548FF52ULL, 0xBDB6D79E5D4D80C5ULL, 0xC98B1D07590AB6B2ULL, 0xB82F17E6D834B54CULL, 
            0x2FD9921B874EA4CDULL, 0xCC244C59B07CA75AULL, 0xCE3BD73859765D47ULL, 0xBCCDBB72BF8AD94FULL
        },
        {
            0x87FE56D1F7B3547BULL, 0xA98FD5841177521AULL, 0xBBA408663762469BULL, 0xE33AB453DDCA2DF5ULL, 
            0x284AE4A52B3148F4ULL, 0xCC3A99F7F4B5427CULL, 0xC7C9171D59589900ULL, 0x1569FA7F57F808BDULL, 
            0xB5D0A50AA0ED7728ULL, 0xF157E011ADC98400ULL, 0xA233CF2D2C17139DULL, 0xB5615C1DBF8C7ED6ULL, 
            0x455E5C59EFB07974ULL, 0xD41C1A69FD48C14FULL, 0x2E8EC05C360E5592ULL, 0x3917A224E6C79CB3ULL, 
            0x8FB5CC46DD2B194DULL, 0x518250CF89D15374ULL, 0xFE30C24F2B89FAA5ULL, 0xBAD25B13D937A8CEULL, 
            0x396C9D43BB00B8F3ULL, 0x3AEA84254EBC1726ULL, 0x44C196B1535D21E4ULL, 0x32F124AACCE37DB4ULL, 
            0x0FCF41D5EDDCD947ULL, 0x7C2BBE9061894A44ULL, 0xFE3FE4B1D4ADE3EEULL, 0xF2076430483E6827ULL, 
            0x5EF4ED34BEFE4674ULL, 0x2F94C5B8ACD5FD0AULL, 0xD650DF27911CD46BULL, 0xA492F2763AC01450ULL
        },
        {
            0xFFDAF58972119A56ULL, 0xF90335C1ECC13274ULL, 0x917240B2E565DD8DULL, 0xDA2783DFCEAB1651ULL, 
            0xF5689ACEFA041651ULL, 0x5B8BA0510FF82435ULL, 0x96711FBF7BFD8A01ULL, 0x0DD08AB474244412ULL, 
            0xB85106A099B16E6CULL, 0x54CFDAE8DC163F12ULL, 0xFC2B6F9BA4CB1FB1ULL, 0xBD3E4D8CA9F6156AULL, 
            0x780164E9AC2A5281ULL, 0xC640BEAB8D982480ULL, 0x402B55F888B07F60ULL, 0x969F5F79B95AD1B9ULL, 
            0x9D7ED3B6EF40CC34ULL, 0x0FA9F31E783CAB9DULL, 0x1409344F1D7E13BEULL, 0xA216BA08FA111817ULL, 
            0xF4056FCED1B3B4D3ULL, 0xACC903FE607AA559ULL, 0xB5C7F8B58AEE8E9FULL, 0x229EBF5C668B1C11ULL, 
            0x71DDA1FA2FD21590ULL, 0xE9B21DCF7676CF85ULL, 0xB72281C663F1E682ULL, 0x98987C89A55D4B03ULL, 
            0x997E09D8BE726F3BULL, 0xCB5D2ED642415639ULL, 0x98080FA0C887D463ULL, 0x677A64F8F6F110ACULL
        }
    },
    {
        {
            0x9EF2E7623C885B18ULL, 0x76F76F0F5F22E0D1ULL, 0xD887309D7D9FA2D1ULL, 0xEB2FAC33754F70CAULL, 
            0xE36EA3D6C749439AULL, 0x6BD45080F506C854ULL, 0xC55F959784F0FEFEULL, 0x99B52AA6C77DF051ULL, 
            0x379F4F3A58B97134ULL, 0x41E8DC77523583D9ULL, 0xC6F6F0F74722E29CULL, 0x3335C606BC9D5237ULL, 
            0xCF236C2A5D6F5057ULL, 0xAE35D8D85D8B3801ULL, 0x58342AAB1F700276ULL, 0x2A79B48409249C5DULL, 
            0xC3D76EA99E245883ULL, 0x43D90D38612AD3A5ULL, 0xFFBD4E242F9F8DD8ULL, 0xB945BC76465EF2C3ULL, 
            0x8AAFA4D311E4BF52ULL, 0x4E43F34B72E980A3ULL, 0x792474DB1ED41DC7ULL, 0x19D28172AC972FE4ULL, 
            0xFBE0C14C85E2781DULL, 0xAC2DD9B8EF49C91DULL, 0x70B1E4D0745C003FULL, 0x338E089A70CA06ADULL, 
            0x1DDEF3B1FF2245FEULL, 0x8D5A4D565BDA68D8ULL, 0x59B96EA7E77398ABULL, 0x9C56D0C007CE9080ULL
        },
        {
            0xE37CAC684727680AULL, 0x546D4BBBBDBC4B4DULL, 0x044E6ACBD1EA7665ULL, 0x0A598E37D99A99B5ULL, 
            0x3C55B4D9BD596CB6ULL, 0xD5E320B1ED7C21D3ULL, 0xA30C12E4F6F0F340ULL, 0xE9DF80B51F83D53DULL, 
            0xFCFEEE49D12FE645ULL, 0x6CABBF5009095CF1ULL, 0x424CE7BCEC883334ULL, 0x94E384C15E232E9AULL, 
            0xF8391FFD0A87C686ULL, 0x9676595ABDBC8C0EULL, 0xDE8A0D1388A87ACDULL, 0xCD9A807148C0D848ULL, 
            0x1945D4D1CDF41733ULL, 0x8635FCD5BA9E0DA9ULL, 0xB58F94D31DDCBAD2ULL, 0x833A39016AA201ECULL, 
            0xD4488833CC8906A4ULL, 0x3A779F15D0C9A4C7ULL, 0x97439FC87D2C8851ULL, 0x30D1E6D0029A214AULL, 
            0xABA65B851AE84CABULL, 0x28B3EDB2EA449147ULL, 0x2F1321A965E658B5ULL, 0x8241987D6BECFE94ULL, 
            0xFF3D12F05A71C982ULL, 0xFB2F6A35A47E5BE6ULL, 0x8906127BC1F92E32ULL, 0x261F788BDDA2701BULL
        },
        {
            0x6632A3CDA25DE826ULL, 0x4E0A33689AF21D78ULL, 0x9CB6A545572DC248ULL, 0x156A3C566D700FB5ULL, 
            0x60ADFB9B7E93D459ULL, 0x3E43B43BC36DDD61ULL, 0xC4AE2DA2C4F00DB9ULL, 0x6E9AAD2562CBB6CDULL, 
            0xCF76B010C20F1F3DULL, 0x3E11F08FE5F7558EULL, 0x3E5E6E0607A9BB60ULL, 0x6C09E5EFA779BEA5ULL, 
            0xBB76B5B5001BC1A5ULL, 0xFC0E41AD10274E75ULL, 0x3415C2458C9BE810ULL, 0x4EB1534F75A0B30EULL, 
            0xA948D28F736D0308ULL, 0xF2102A1C1C042547ULL, 0x3756D3DC7B24568FULL, 0x52754CE3F193D8CFULL, 
            0x7A9608477156EB4EULL, 0xE3C2C6A74E9F43D8ULL, 0x444C16D65A4DBF41ULL, 0xC1D08514013E42B7ULL, 
            0xCC54E8C484594E0EULL, 0xF042738620050B7FULL, 0xB059E60EEC815317ULL, 0x10208AA11F999E49ULL, 
            0x989A98DC349F90E9ULL, 0x71B1DC4548201527ULL, 0xDE5000DF9B0B5BFBULL, 0x2068E34EF95D91F7ULL
        },
        {
            0x33682CAE66FD2427ULL, 0xC9382D3A24F5E20AULL, 0x9BA06E33BBCEBAFBULL, 0x4E67A84B132D1857ULL, 
            0x4522CAB28A1DB20AULL, 0x4167AA125B3D57EFULL, 0x088DE73BB236D65EULL, 0x6F22BB1806CBC917ULL, 
            0x5033AE5FE69ED6A5ULL, 0xC974171104E39CBEULL, 0x3123C924AEF59350ULL, 0xDC80533C185C0D9DULL, 
            0xCE8F097B17276C15ULL, 0x1372B94F28BCE5DAULL, 0xF4D7DBCB7339992EULL, 0x88F912DE74024DADULL, 
            0xF88D46911F7DC16CULL, 0xAD894838ED72A76AULL, 0x0E9A1C419D5BF841ULL, 0x9EC77FAD0C7F3886ULL, 
            0x00DEFE60D9D7E96EULL, 0x54E858E70FD69076ULL, 0x4024C976048A328DULL, 0x3AB10043D445828EULL, 
            0x51A9303EC1E86054ULL, 0x882B9196AF687FFBULL, 0x81D9469C6A267792ULL, 0x12B9AF0383FB5305ULL, 
            0x1654B9F20741E3A5ULL, 0x528A54A620C6648AULL, 0xACE363AEE54766A2ULL, 0x2C9751BA5EB5A2A3ULL
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
            0xF7D307BB065DA6B8ULL, 0x9BA40FF3A1EB3613ULL, 0xE753F7772DB3D683ULL, 0x635A51A8EEC0EB2EULL, 
            0xDD9A2BE2937699C9ULL, 0x3D53279B27D7BCA7ULL, 0x249C6E47E5589ED6ULL, 0xF0D0FC3217D439E1ULL, 
            0x65AC95C3754E6B5AULL, 0x6DC2CB67CDD2916DULL, 0xDCBA76642C8799B0ULL, 0x6B47D0042CC8D6D4ULL, 
            0x7D516A0F1484FE0EULL, 0xAF8A2F212E75743EULL, 0x7106B4B2586A2C5BULL, 0xEBCBF07E770ED722ULL, 
            0xEA8643C09B044C4BULL, 0x36B6EE68836E7FF2ULL, 0x4C5F97F9838BD78BULL, 0x3FEE2A609060830EULL, 
            0xF4F2C9348ACDBF30ULL, 0x4E44D432F20FE870ULL, 0xD7415D7DBF61D098ULL, 0x10CDC977CC72F890ULL, 
            0x9D0877F173B50A96ULL, 0x3BCF8D5D9053A4E2ULL, 0xC17AEBF8C94FCAFDULL, 0x8F192200F02B61E2ULL, 
            0x298B0AEBFC597318ULL, 0x3FFA30B69D51B828ULL, 0xA0E5FF788B2E2408ULL, 0x06539283A2835907ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseFConstants = {
    0xF8EAF1B6EF313A0AULL,
    0x96987B50D1CE44FBULL,
    0xF624B5AA752DAF0BULL,
    0xF8EAF1B6EF313A0AULL,
    0x96987B50D1CE44FBULL,
    0xF624B5AA752DAF0BULL,
    0xE1B49E71F88D2677ULL,
    0xB9C66893A172B4CCULL,
    0x78,
    0x6D,
    0x6B,
    0x6B,
    0x87,
    0xAF,
    0xC1,
    0xDB
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseGSalts = {
    {
        {
            0x828CA20B8768C059ULL, 0x4025AFC67FCBB8E4ULL, 0x806FD711396B9145ULL, 0xF68CBEC31412F7ECULL, 
            0xD5C8B84A2254AA14ULL, 0x1E9227B0EC2F148EULL, 0xF333BF078C20A565ULL, 0x8B90256076489A33ULL, 
            0x72E39AD98496ED2EULL, 0xBBE1780E1AFA0987ULL, 0x5C98E75357946EDDULL, 0xF8274FCB4815633EULL, 
            0x80EA872AD854218FULL, 0x71B04AF7F60DAEF1ULL, 0x80497CD2F5ED47F4ULL, 0x1BFA0E043BCE6377ULL, 
            0x9ED4BDDE8E72C72FULL, 0x19EC8CBB572F68CAULL, 0x4702E0428AB9D40FULL, 0x18B232090116EFFBULL, 
            0x5FBFFDFBA2D65626ULL, 0x881B69BC399F4044ULL, 0xA71CAAC76A66DD98ULL, 0xBDC84295BB34ADEEULL, 
            0x41041A49EE2BD135ULL, 0xEBE990AFC9E1F003ULL, 0x2442BB8A8348C4EBULL, 0x306F6F9566B47AF8ULL, 
            0x0BE40A072D0CB6A8ULL, 0xA2FC51107C69874FULL, 0xEDC6B6B0019CA320ULL, 0x2DBC3FA00D46904DULL
        },
        {
            0x8B2F0F312B43B8C3ULL, 0x6FBFC23B1873DC1FULL, 0xE037FE40F280AE2DULL, 0x9325CAC6D35C5CDCULL, 
            0xE2AE3E3CA7AAE54BULL, 0xFDD892B01B1C7E6BULL, 0x4D9939E927BBF44AULL, 0xD4A7D6ED4A2D5982ULL, 
            0x6F8A463BAC2B2A40ULL, 0x05E5E603B65D5FFBULL, 0x2F0CDD2B01F96751ULL, 0x9DCA1011F6716763ULL, 
            0x0E6483342899E3FEULL, 0xCF9EB921B135F6DEULL, 0x8454E5E3D6D28A49ULL, 0x8665888AD7047605ULL, 
            0xC317ACFF70B815E1ULL, 0xA0891A4F165D3A60ULL, 0xF4442A8110DEB468ULL, 0x6F14D13E3836FD1BULL, 
            0xCCE9038124088BD8ULL, 0xDF6FE3CAC8F6C89AULL, 0x350A57BEEC3CF954ULL, 0x08B90031BC9EE2D8ULL, 
            0xE6746A1469C3A0C2ULL, 0x7FCE54DE94D86B87ULL, 0x820F59CF72B98555ULL, 0x680526674E93EE14ULL, 
            0x2AA22A402645EEACULL, 0xCF8A64CC7C425A82ULL, 0xBE6E84C94F6A14A7ULL, 0x1DD3391A8A00B39EULL
        },
        {
            0xCCD19A022DE6AFDBULL, 0x99FFA59CA9905B99ULL, 0x4E90CACECD63C217ULL, 0xE802B97155CA417FULL, 
            0x7D95D2C908AC4042ULL, 0x930767F6529426B1ULL, 0x428BAF81E91BF09DULL, 0x0AC08C0502AADBFAULL, 
            0xCDDE2CECD240438CULL, 0x9FC1EF69842F72D0ULL, 0x4978B8D3C5E93F3EULL, 0xAEB136E798214E35ULL, 
            0x14A95ABD7841DB66ULL, 0xF6D1D0594949CDCCULL, 0x6169F807B7E87840ULL, 0x79F437D852385CD0ULL, 
            0x458537B4106566E4ULL, 0x00A3A503871BD520ULL, 0x57A2AF336F007DAAULL, 0xC4761F8765FDD5E6ULL, 
            0xA74595BB93CC55B1ULL, 0xB03B0E3D64E9304DULL, 0x96C4D6039FD3A1C0ULL, 0x924A9A2320F67470ULL, 
            0x8EB075FB6DC45879ULL, 0x9AC000F313ED856CULL, 0x697D030D08B77956ULL, 0x2EECFF8E0F4015BAULL, 
            0x34DF788566796784ULL, 0x4972BA18C4A0273BULL, 0x89FE1A9BCFC9EE6FULL, 0x6AAC4A6D0A565AC9ULL
        },
        {
            0x0512DD18C1E8E9EDULL, 0x60B7D65A45B60010ULL, 0x34582D22E5458DD4ULL, 0x727ADD74C7D2E73BULL, 
            0x83C1287B768A4167ULL, 0x04DD36DB6C92F8ECULL, 0x1F4596AB49CDB627ULL, 0x053DE8873E910364ULL, 
            0xFBC2BDA52E44F1C9ULL, 0x3384F68E2D5A89DCULL, 0x47A74B9F2F881ECDULL, 0x60C7101F82E95D60ULL, 
            0x46A6B52D9D189579ULL, 0xCB352D2550284993ULL, 0x46405D57B1F0A0ECULL, 0xA7E7677A18CF268FULL, 
            0x38C33AF530B4BE5FULL, 0x60999680E96059D3ULL, 0x051D3482B63A8D65ULL, 0x56849B24A7CD9459ULL, 
            0x90F3237838F1ABA6ULL, 0x5612C0AC291C920CULL, 0x66F71EFDE4AC0756ULL, 0x188A717BE2D007B0ULL, 
            0x5BBB26D241CA2FAFULL, 0x103E3F19B1BBEF0FULL, 0x1EB1A9686D06822CULL, 0xEDE9C6D121ACEEB4ULL, 
            0x9CD948304E70E1B5ULL, 0x7485FF32E2387621ULL, 0xB595C491542EA4DDULL, 0x0C1D5B48A6AFAF6CULL
        },
        {
            0x7DFD3B61C97DBD42ULL, 0xA0CFC6B06C04E7F2ULL, 0x32EC8D44228B575FULL, 0x51AB5B43BFD504A7ULL, 
            0x6761EF1CB693F444ULL, 0x6F1DA4B8D3B6D3A5ULL, 0x75BDD934DABFDD82ULL, 0xDD175923CE6605C2ULL, 
            0xC0AFA2FB3D00FD24ULL, 0x4E653B23DF23BCF8ULL, 0x3A30A8A78A8D91D3ULL, 0x03AAACD184B639C5ULL, 
            0xAA58639B6C843300ULL, 0x125FAA56942552ECULL, 0x9A436773516736E6ULL, 0x672862D9EC2308D0ULL, 
            0x8241869E16525EAAULL, 0xF61F0382AB7C6AF8ULL, 0x0CE26AB0A21A7805ULL, 0x7BF559AF85596C3BULL, 
            0xE1279179614F9286ULL, 0x98F58407BF4B917EULL, 0xFA074C84A7EFC6FAULL, 0x0FC9FCD38E3D8302ULL, 
            0xF6FDEAE9F3CB79E5ULL, 0x553EF7672D886D66ULL, 0xD6D265E99770A170ULL, 0x5E03E17DDB8785FFULL, 
            0x9F9766DD436BC102ULL, 0xE348C07F1A9F5E22ULL, 0x9994FA5958E34381ULL, 0xFD1C605D64534AA1ULL
        },
        {
            0xA996E2A7BF0D73D1ULL, 0x20E49459B0E933CEULL, 0x8E44D4B2CB6A6594ULL, 0x0C4AABE02C4357C0ULL, 
            0x6F0F4D697075B4B9ULL, 0x6AA84ABED1184158ULL, 0x9BEB8B9305903409ULL, 0x9E53CD571050AA2EULL, 
            0xA7696D7AE5BC3699ULL, 0x1B53838716831777ULL, 0xA4FBAE434C2F456BULL, 0x748DC1D4F75AA6C4ULL, 
            0xE7D5F13299A470FEULL, 0x2916C4C057519E5BULL, 0x3F024941B985104CULL, 0x41857322AE72622CULL, 
            0x6BE840864D0D1D04ULL, 0x5B807A7B03343C2DULL, 0x99055619B37A8D8FULL, 0x37D5D5490CFCD32FULL, 
            0x01FE2F5EA8840034ULL, 0x4F4183610CBCED71ULL, 0xF60DBCB24A6DBDDCULL, 0xBFD5FB4678D2CB54ULL, 
            0x808EDACFA615F9D1ULL, 0x7403C1611C7B97BAULL, 0xBF13E5F9432A08A6ULL, 0x1F78B5CDE67C365BULL, 
            0xF8F16BC7F7ACC3F3ULL, 0x2368F96A4E285281ULL, 0x5BF1D13B2F111FB9ULL, 0x7241526D6E8208EDULL
        }
    },
    {
        {
            0xB332D02B819AA6CFULL, 0x7948679A1A59199AULL, 0x5580837F068BD31BULL, 0x69E38CCEFD166647ULL, 
            0x82269260860301FDULL, 0x07E653C5D4D91472ULL, 0x555B6549EAC56C8CULL, 0xEBBB81BFAABFC33AULL, 
            0xA7C18467DB08542FULL, 0xAB79FB6988F169B9ULL, 0xD5BFA7F21AF5CCF4ULL, 0x2794A0F9C41F4201ULL, 
            0x1A70157235A9695FULL, 0xE462EFBC375F0410ULL, 0x32030D4EC4197263ULL, 0x018A4D60DD9E1EFEULL, 
            0x736BD28ED437596AULL, 0x2CB007B1F38644DBULL, 0x082E83CCEDA20C94ULL, 0x3BF02B2FF8012405ULL, 
            0x1D18FC8C587DD3FAULL, 0x43C65A195560E72CULL, 0xA55685EA26146F9EULL, 0x0E919C3A0F253B15ULL, 
            0xE4EB4822D6EAF98CULL, 0x34CAD2628A89420AULL, 0xD3468A5ECBF27F4DULL, 0xDD9DE46BF1D8F26CULL, 
            0x7134999B93B5350AULL, 0x55E28202B1623F54ULL, 0xDC190C743A3237C5ULL, 0xFEC7D78ED59E3743ULL
        },
        {
            0x66F677E2D6204FC3ULL, 0xC9760F7551168F36ULL, 0x4A5939FF8AC363A9ULL, 0xF2BFE31B556A9EA0ULL, 
            0x00C1C3A0670D07DEULL, 0x1CB3AE2A46E543B6ULL, 0xDF31714FE54D5EF0ULL, 0x0EDD02FBD76164F8ULL, 
            0x55CBEC75912697BEULL, 0xAC254715DFEA39DAULL, 0xE59F57C004C88E1FULL, 0x4F3B197C2A555952ULL, 
            0x8CB748C58BBF5FDEULL, 0x103D3310BDB3A1CEULL, 0xBF561DFBA52C0648ULL, 0x69C888ABBA0EFF33ULL, 
            0x77446BBA2057EADAULL, 0xF08A4652BA94E486ULL, 0x64ABEB6B9DC298B8ULL, 0x1E593FEA5745F211ULL, 
            0x09744B340AD402E0ULL, 0x2B4CA84138E20BACULL, 0x39513906177DE8E7ULL, 0xDF03FCAB9DD39192ULL, 
            0x01CC6A0C772BBF21ULL, 0x6CB888612533AE5AULL, 0x7DA154E06DDE98FCULL, 0x5CA756FEF05E7723ULL, 
            0x4E2B6FAB91824370ULL, 0x1DB517A37989BFA9ULL, 0xB1DB1C98B324AB17ULL, 0x697D18819C22FEFAULL
        },
        {
            0x6AA436CD13CA5C0AULL, 0xAF749A0BCB1C55BBULL, 0x58F8C925475023F2ULL, 0x1D2BCD30FA202FB7ULL, 
            0x0790D8BFC03A48C5ULL, 0x16D755FA82843EBEULL, 0x5F0533497CDC4B44ULL, 0xB368CAFA3E8E353AULL, 
            0x258707F2EFC3434EULL, 0xEF5C3D21478EE869ULL, 0x0CEE9749F076278CULL, 0x29497C1592E4AB30ULL, 
            0x350A2883C834DFDEULL, 0xE97419BD105B5039ULL, 0xB95B30DCCDA97EBAULL, 0xC3DB0EBD250D1A4AULL, 
            0x0D47505C8ADAEF50ULL, 0x44C20A280272786BULL, 0xF79272B8FB15DC14ULL, 0xF92CD9D68395F5BEULL, 
            0x089CC68C8739F293ULL, 0xD9534AEFEF313D43ULL, 0x06E8C7C106F1C7FCULL, 0x21C46FE70083623AULL, 
            0x1380C215F65A4407ULL, 0xB3A2DBF08A3BE0B3ULL, 0xDE7E3C2277019016ULL, 0x4797CC1C4FDB6937ULL, 
            0xB21DFBFC7F1BFBE7ULL, 0xE23EC3BF9C1C68E7ULL, 0xE1E63554FF16374FULL, 0xD69654B18C6A714FULL
        },
        {
            0x629D4E0DD61F816CULL, 0x6AE3DA66F313BBFEULL, 0x9F281BDA2275A74CULL, 0x66153CA11AD17C56ULL, 
            0xAD92E3E56F4CD1ABULL, 0xD27563DE10D97669ULL, 0xB01974327102FB54ULL, 0xE92457F1F63A3A42ULL, 
            0x521F0BC695B84D0BULL, 0xD180798A8AB4908EULL, 0x752C18097B5FF360ULL, 0xDF0367AF81FE443BULL, 
            0x999F3BA0F1F7D33EULL, 0x7F41E076FEBF1E3AULL, 0xBE201618B988EB20ULL, 0xAFE1AC6E9D11EC30ULL, 
            0x92832EE0F59F61D3ULL, 0xEBFA2BAA9DF05FACULL, 0x42E84D86FFCE86B3ULL, 0xE8171355E3A2A04AULL, 
            0x48D5D056D97F3631ULL, 0x5EAE69E41A4D7B13ULL, 0x6F11FC50D7C2DF99ULL, 0x4A3657834B4C8E29ULL, 
            0xB4939AE5D4D59678ULL, 0x64E1E72ABA0001ABULL, 0x7D1969B76FDE48B0ULL, 0x0F8898F1EA4AA260ULL, 
            0xB6F920C270628A3AULL, 0x7768737EB2513B98ULL, 0x228197F362957A32ULL, 0x50CB76F25F4ED651ULL
        },
        {
            0x9DA1CC380D2BF5EBULL, 0xE485292A40A3E78EULL, 0x0584EBCCA586E844ULL, 0x94206A844CDE4723ULL, 
            0x1AF7D63ADE3962F2ULL, 0x021FBBE3C9CA9B22ULL, 0x33880DC1D5782B51ULL, 0x5ACBF9DEEB6D029DULL, 
            0x18EDF8C5E3233B2FULL, 0xCAAA680E8796FD54ULL, 0x7843939911056A16ULL, 0xA714F6C0AD2768FDULL, 
            0xDBC0A5B62CC33A24ULL, 0x7180879E5449CAB0ULL, 0x174D66FBD18C9BC8ULL, 0xB6BEA5B8D4D9B614ULL, 
            0x323BFC8DB6F262B3ULL, 0xB70174FE38DFC3F5ULL, 0xD6ABA1350B91814BULL, 0x077C1CD1DBBFF902ULL, 
            0x1C579CB05440D33AULL, 0xD49963C9A699B7DAULL, 0x8F6D889DCD9B0D43ULL, 0xF4BBB3262E57B505ULL, 
            0xC00F137D4D3856A2ULL, 0x20FD58E2865667D6ULL, 0x2BD365DCC32B4244ULL, 0x13A87E8C9ABDA961ULL, 
            0x3507D6B9C5838CE8ULL, 0x88A8D1B861514455ULL, 0x89D12F4D530292C8ULL, 0x0DE6ECCE80767406ULL
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
        }
    },
    {
        {
            0x13EB34C8FA5D5985ULL, 0xD1E96A54BDC6BEFCULL, 0x0AB583D5045A6283ULL, 0x459127A53FCCC4E7ULL, 
            0x9C1BB12EE6A92EE2ULL, 0xBE1DDC62CBE2020AULL, 0x884A6625E4910FC4ULL, 0xA8628F980C6CBCF7ULL, 
            0x6A18F646B347D78FULL, 0xA026A32561D7486CULL, 0xCB567A41A7E3F813ULL, 0xF93062CD781192A3ULL, 
            0x111EE92E59A7BB78ULL, 0x16129719280E023DULL, 0x968540E1C7112BFBULL, 0x4525E5C746706451ULL, 
            0x4D371948D7FAF4CFULL, 0x81D8E8171E3E16A1ULL, 0x89FF32FB3813EE82ULL, 0x19B1ED3C1FFDAE3CULL, 
            0x3913C2A2D1FB6257ULL, 0x0877A0DCFD154E04ULL, 0xA2399369558DB704ULL, 0x2E974D73E3FE094FULL, 
            0x3F8A2903F2060AB9ULL, 0xDDB6262A350DB4EAULL, 0x54B743824735A0CDULL, 0xBCE2681F03739A6FULL, 
            0x8FD70ADC9C0C2CEFULL, 0xD17C230305FAC565ULL, 0xCC31F9EEC6024BFDULL, 0x7BBD3325422CA2FBULL
        },
        {
            0xBACE690D74B5C044ULL, 0xFE8CD94EB1CEBF07ULL, 0xAFC8EDA89A32641AULL, 0xC6D1FD5C2F83FF3EULL, 
            0xD9FC6AE36FF416F9ULL, 0xF184371ACD132AE4ULL, 0xB9D4E2CCB86DA027ULL, 0x811E1728B19752C1ULL, 
            0x6564B6978D98BEDCULL, 0xA679D7A9EE54D699ULL, 0x1586E903C1EAE49DULL, 0x1DAAEB8CB8155304ULL, 
            0xB13EFC9EFD989FC6ULL, 0xC42F3A3D2F9A3A93ULL, 0x490A38C2E95E80EFULL, 0xD26F8DB449E44CF5ULL, 
            0xB269D2625856CF57ULL, 0x8F1CCDC7661CF2F3ULL, 0x03039EEC80484E0EULL, 0x4FE15F132D36866BULL, 
            0xF82C36B4FEE2B461ULL, 0x3A122A402770764AULL, 0xE98334F6853E2B56ULL, 0x1EA202477C616C2EULL, 
            0x7E4A2A56A06FCE8DULL, 0xBDC78146DC8FA4CAULL, 0xEF4736CEAA53E8BAULL, 0x00E20542889FDA0DULL, 
            0xD05D2E04389FB4C9ULL, 0x6376271F6E9A1E96ULL, 0xCA7E4F2E47F00BA7ULL, 0x7C567A161D03CA1CULL
        },
        {
            0x4E30033103B0A0DFULL, 0x2760E9247E34FC3FULL, 0xAAA8248E56723DDCULL, 0xEE00DA68736D8293ULL, 
            0x6B7816B68C0F739FULL, 0xBD9F7D33E224DCB7ULL, 0x48345463AE92851AULL, 0xFA3EEDBA9A4C9D23ULL, 
            0xCC4A338EA931D77EULL, 0xDC6BBEA8214E466BULL, 0xBE62D336020ED4F8ULL, 0x6A4F0A1A6D55E86AULL, 
            0xA5D2C8B1BB435104ULL, 0x03BB75515D74A53CULL, 0x684A9F28BC307E50ULL, 0x577089CF94015B75ULL, 
            0x7CAF9A227F10EA2AULL, 0x3730D764F7D44E28ULL, 0xFE0B355C5CF14DF2ULL, 0x558A13DD9A626C06ULL, 
            0x68E4B5A8B6D7FC85ULL, 0x97DA08CE6D77A1E1ULL, 0x6D45DD42247E1130ULL, 0xFDD24257223F48C1ULL, 
            0x8CF45B1203C2DA8DULL, 0xD00592255DE7FCA3ULL, 0xE8BC64102D4F966AULL, 0xE896BE1D43444274ULL, 
            0x96EDDC5CE597ABE4ULL, 0xF0216E36BEF61F77ULL, 0x355ED00B481570FBULL, 0x721EF0F54F2CDE28ULL
        },
        {
            0xA5678AD5065DDD56ULL, 0x1A0D03410D233A77ULL, 0xABBD530577A1389EULL, 0x8F414A3281968DE7ULL, 
            0xEAAC25F84BC4929EULL, 0xD542B16098B4852AULL, 0x9FEE8396143CC217ULL, 0x5602416F82B4BEEEULL, 
            0x30A6EE3101B0DCDBULL, 0x2AAF64A3FC548CF6ULL, 0xE7105C4B371373F3ULL, 0x6E3C3A0F2137F07EULL, 
            0x42F2C695FABD73D8ULL, 0xEDD0B7C678AA3795ULL, 0xE235B4E4E38985CCULL, 0xA16F58BE61F3D97BULL, 
            0xCA8374DDB159D5A6ULL, 0x036DC6439D98ECC0ULL, 0x532FD2BC6D453FE0ULL, 0x413F42D05E26CA80ULL, 
            0xC20C18B2A7701766ULL, 0x60C314042EBF903CULL, 0xD2A13A08852589A1ULL, 0x3314D8949214AC49ULL, 
            0xA88383C5C67D8272ULL, 0x15562C613D063624ULL, 0x99C95E3765DFEBC4ULL, 0x9ABF02D2A2E845EDULL, 
            0xBAE2360C7F96E01BULL, 0x2CE223E7B9E1365EULL, 0xAA2D5C5066A8308BULL, 0x65FC97A90205BF42ULL
        },
        {
            0x4FE5D2E9580835D6ULL, 0x8A66664E45B55C3BULL, 0xA60075AA8AB19785ULL, 0xA89204ECF8622D52ULL, 
            0x581DA0138CE50888ULL, 0x60B3F1D58B9CC7D3ULL, 0x054AD46A12D036F5ULL, 0x4EBF199B4276B6FAULL, 
            0xD76A636203B22FE0ULL, 0xCEBFDF06D4F1D811ULL, 0xAE7A8616C471F102ULL, 0x19ED33E4B0C20BC4ULL, 
            0x2BC66CBBBC69AAB3ULL, 0x0C339057F75463A0ULL, 0xAE8AF838DC4D4BFAULL, 0xE5652FE7C28E5A05ULL, 
            0xD7A7D6ECB21CC708ULL, 0x86887810BA91316AULL, 0x66EB512454AECDECULL, 0x5D047FDB434919C8ULL, 
            0x3BA8D04E0B4F43EAULL, 0xC5BE02B2106886F3ULL, 0xF9EED0D522A09EB2ULL, 0xC0ABC2531B631790ULL, 
            0x2326A043BE3F18ADULL, 0xA17533BC1EB56472ULL, 0x25B1CEE05A7FFC90ULL, 0x749DA3AE1CE1528EULL, 
            0xB573A12B4038C876ULL, 0x7765C423A4FD4E68ULL, 0x5540C7A74B3DD301ULL, 0x562EA0D252EB53ABULL
        },
        {
            0x0C893BE26447834CULL, 0x4A717AF4A84B366BULL, 0x3428986D158C363BULL, 0x8CE36A90D3A1BD0DULL, 
            0x4B78381AC5D4DB3BULL, 0xCCF8636481F3066EULL, 0x4BC6FD1E0E8E5975ULL, 0xB3EA8D9B5FE6B9ECULL, 
            0x544CF89DFBB3E0B3ULL, 0xF7A5B56050DF2C73ULL, 0x45AA1E5609D1A29EULL, 0x0B087C12A057E42AULL, 
            0x815D279BB20EA9C9ULL, 0x1A3F5D9C1CAA7819ULL, 0xBD9AF762C1CC168AULL, 0x7F68B7E6E2B306A1ULL, 
            0x6FA29E455D42927DULL, 0xB730DFFB09D17ACFULL, 0xAB0437CD058EAA94ULL, 0xC2EC57336F279EE0ULL, 
            0x732F0136FA37BA60ULL, 0x2BD2DABED874AA5BULL, 0xCED7EE6753212FEFULL, 0x3F6E9954CCFCFB0AULL, 
            0x5002F7944AE1B5E6ULL, 0x6DAC66D4D6634F40ULL, 0x5FC2E3AE36CAAEF5ULL, 0xAD34689C7DCFE04FULL, 
            0xB9738FE586A63ED3ULL, 0xFC26C4A5F78B5F54ULL, 0x43713B4FBD3F19A8ULL, 0x6C794A36E35C8953ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseGConstants = {
    0x0E6CFF5079A6FB52ULL,
    0xAFF831F9B37E64F1ULL,
    0xEEEE0C18C7BB16CEULL,
    0x0E6CFF5079A6FB52ULL,
    0xAFF831F9B37E64F1ULL,
    0xEEEE0C18C7BB16CEULL,
    0x24B90F48122A1110ULL,
    0xAD00C65D6B1F4E3AULL,
    0x50,
    0xE2,
    0xBF,
    0xFC,
    0x1B,
    0x5D,
    0x2C,
    0x5A
};

const TwistDomainSaltSet TwistExpander_Mimosa::kPhaseHSalts = {
    {
        {
            0x26097B487BFA93A3ULL, 0x429D568FAD60F07BULL, 0xE6898F4EB631E9A7ULL, 0x03946807EA02A930ULL, 
            0xC3AF6175D40ED680ULL, 0xCBCDCBD25A1EEC48ULL, 0xBC85C0CDA6F264D5ULL, 0xCD717B0D4D920B83ULL, 
            0x7BCABAEC8FA1489CULL, 0xE44117831E78DD6FULL, 0x01C2A3014235A034ULL, 0x618D89B33BF5A1BDULL, 
            0x25E760E5D444AC09ULL, 0x13B549BAB5029326ULL, 0x908581D8BECD63A3ULL, 0xD9D8BF57FBC1823BULL, 
            0xA4958F3447DAD0ADULL, 0x70FECEC61033FD27ULL, 0x299BA5AF5830F223ULL, 0x7EC15E66F7E13A87ULL, 
            0xF303720242CE897BULL, 0xB70F744E3800EC9DULL, 0xA41247B5880D564DULL, 0xE88218DC401D660AULL, 
            0x840C3B4A28F97B3DULL, 0x0D603E811BE11F3AULL, 0x6D01C9C909B6FCC8ULL, 0xB622BD00E92C56F6ULL, 
            0x39A49BDD3EEA86B9ULL, 0x9227C4795B0CC5F6ULL, 0xA27BBB7DC5E6BAE2ULL, 0x44875B59B8341B0EULL
        },
        {
            0xBAC05AA4C7AAADE6ULL, 0x1A6BACC0333951EEULL, 0xCB111BE58438E971ULL, 0x6B7F60A82D57AC51ULL, 
            0x429C9559B8CA6640ULL, 0x3B0FD58C7DA687D4ULL, 0x7D10E63CD94C69F2ULL, 0xA13D002730966F66ULL, 
            0xE730A55BEB91C33EULL, 0x4FC49A41866E4D88ULL, 0xDE600B3F0D65557DULL, 0xE43817DF322E4E90ULL, 
            0x96D271C67B041896ULL, 0x39DA480C330EA1BFULL, 0xA2056C8109411DF2ULL, 0x8CD0B003DCC28547ULL, 
            0x62A3179F75F8E1D5ULL, 0xD8CD0A2EEC9939D2ULL, 0x991AD7D1A56C36AFULL, 0x77402077AF07396AULL, 
            0x99CE26E10E5DDC1AULL, 0x69F104183D13C078ULL, 0x9099DC19780FE827ULL, 0x863B03480B17878CULL, 
            0x787594EBD2CD6FDEULL, 0x2B274346E1FF2D48ULL, 0xEC3FE0A676EF1CB8ULL, 0xBC6D2D45ABCAD0A5ULL, 
            0x573BB56D39A1581AULL, 0x9AB03D36544595ADULL, 0x991A003A75F77CAFULL, 0x7622F59F00D3026EULL
        },
        {
            0x36F53429581D69AEULL, 0xA3C03E5E9BDE2C37ULL, 0xFEBAF1403D80BA1DULL, 0x083BF0B7F7AC8560ULL, 
            0x0F8A326BDA5F7E89ULL, 0xB19D075800EB579EULL, 0xC0C099B87A6CCE10ULL, 0x99CCC6099224189AULL, 
            0x51B093A679D19471ULL, 0x8A602ACDC34E7AE6ULL, 0xDF17C086EA0A05C2ULL, 0xCC2AB95C3DF56560ULL, 
            0x73223FFC1004000AULL, 0x99DCF4E117425CA3ULL, 0x945F9004CCB171BAULL, 0x55425EF0A29AB915ULL, 
            0x48E249F1D108877DULL, 0x11B4C7C5B78B0BB3ULL, 0x20E6363414CA6542ULL, 0x4670803B816BCFD7ULL, 
            0x63A244B3E5748E80ULL, 0x5ABCEF5EF8BD0740ULL, 0xF0B30674F4A12531ULL, 0x8EE786ED9C73E8A7ULL, 
            0x51CA224DCBA68FEEULL, 0x2C1E97444EF90F5BULL, 0xB163A0F1E948541DULL, 0x154E0329B43CA5EFULL, 
            0x8F726CA9424AED0DULL, 0xE2A584BF95305B4CULL, 0xBC89D15BF41F06D7ULL, 0xC33EAC81ADEE5AFBULL
        },
        {
            0x3784E55120D6F55AULL, 0xAF4B60D046A5CB1EULL, 0x7B21B56EECE75BBDULL, 0x9B212DD10FFBC9B1ULL, 
            0xF10E75F948D2167EULL, 0xD9020721C84890E1ULL, 0x7F3F0A49A9871EAAULL, 0x4B90ECD4605CCFEBULL, 
            0x483DF7BFC7AE3EF1ULL, 0xAF14DEA2B9891091ULL, 0xC5AC84AB20AB8532ULL, 0x72E723EFC0FDE0B1ULL, 
            0x70F56C66285EC57CULL, 0xB711A3469425EEEBULL, 0x9D3BC9DCBDF20BB8ULL, 0xCDAD91EA1D04809BULL, 
            0xEAB7E116C738465DULL, 0xAB4F903A2688191EULL, 0x35D0265DF3FFE5BDULL, 0x8CB074C868F94750ULL, 
            0x4E26E7EC4DBB2AF6ULL, 0x5174FDD139C669A5ULL, 0x3A6325FD90DFC899ULL, 0xAAE6578931C6CEAEULL, 
            0x5BD8E1973D62238DULL, 0x729BA559540880EEULL, 0xFFBC10F5E08041E4ULL, 0x890FFB1451755073ULL, 
            0x3EFFD5BB69E21423ULL, 0x3DE6FD0F26F09606ULL, 0x297D479317141896ULL, 0x8401D0A6EBD285BDULL
        },
        {
            0x6B8A8DCB625FD6FCULL, 0xB401A6784C23A3A9ULL, 0x9AAF5B86A26F45BDULL, 0x0E5575D0E0D480A4ULL, 
            0x961284C5768DFA07ULL, 0xF298AC814137BE36ULL, 0x15BF8936637B01FDULL, 0xC495D079691984C3ULL, 
            0x0ECD9F7D346D7D85ULL, 0x98B2816F627ED720ULL, 0x437ACE5FFA78659DULL, 0xC65F4C3A12CB6323ULL, 
            0x04946A04CF80DDE8ULL, 0x7BA4A7DE41D31EE3ULL, 0xEA3E49F0C9270DB6ULL, 0x9199BA67F2C72E87ULL, 
            0xD437DFF944932FC1ULL, 0xC9E19EB20230D4D2ULL, 0x9D6371C576594A35ULL, 0x6589EAE931BB9B1BULL, 
            0xD1203B74F784D029ULL, 0x0CF3B7D87A2AE400ULL, 0x15D54340AE79E19AULL, 0x2183F9639E7A0F42ULL, 
            0xBA13BE166C417F36ULL, 0xA58FBECA8462886BULL, 0x6DD0D13C984D9A9DULL, 0x085A8054D48EA156ULL, 
            0xAE4A59050FAE11C7ULL, 0x11CD103F97A595E5ULL, 0x5851B97BD5FDFF01ULL, 0x79F30ABCB9C7105BULL
        },
        {
            0x8EF2B87F1FECF459ULL, 0xAC7FB802DBB5BEB8ULL, 0xC524211FEA38D103ULL, 0x429363BC2CA1442EULL, 
            0x9789D88E899A95D3ULL, 0xB7D247A2E633C330ULL, 0xE393CB054B6211B0ULL, 0xFDB7EC7F177695EAULL, 
            0xE6EF9AC45C31C96CULL, 0xC8EDBAA464867549ULL, 0xB877F1B5BC2A5FF8ULL, 0x558614AFC692C99AULL, 
            0x3C831CE675460231ULL, 0x6BCE9D4B5A186F37ULL, 0x8F92D6D98A2A2D1CULL, 0x674E83F07F8F4244ULL, 
            0xA015C828707424F3ULL, 0x366931BFC81C8A82ULL, 0x8DB1B057FDB593F6ULL, 0xB2179C314BA60AEAULL, 
            0x6EF1A73CECA43C90ULL, 0xD92AC85AB321A794ULL, 0x5707D36963915013ULL, 0xB5F7B4F944769291ULL, 
            0x94D0CDC4A932AD0CULL, 0xA4E535F08A2131C4ULL, 0xFB4539AF1516EA36ULL, 0xF8E6AA818427BF1FULL, 
            0x09D02AE54E814128ULL, 0x63DFD5934EE6313EULL, 0xF0BDE875DF0F5616ULL, 0x673051AAAAD375D4ULL
        }
    },
    {
        {
            0x54CE739C294E9C97ULL, 0x94A37BC040A8EDBAULL, 0x9AFE084B504C8103ULL, 0x64A26AEB3E372873ULL, 
            0x0AEEB7BBA895D8B9ULL, 0x25446F86ECF00D30ULL, 0xC2EA57A3FF828AA4ULL, 0x218ED65695CE176DULL, 
            0x0C7A4A2579514CBEULL, 0x65585B6465B29E6CULL, 0xC0E27BEAE1206AAAULL, 0x58619D137776ECC5ULL, 
            0xB1BE804B6A5C1B34ULL, 0xEDBAE3FC2E565977ULL, 0xC7796476A9BAD7F9ULL, 0x3865FBCBE149F34EULL, 
            0x99A8266486DC2DC1ULL, 0x8E636E65565DA807ULL, 0x089597AB124B57F0ULL, 0x5E61C498006F8F02ULL, 
            0x55239C70D90713ECULL, 0x1BC381245DF6E53DULL, 0xA78D46B2A9D41BDEULL, 0x5111185130B5149EULL, 
            0x08DBD71C03D5BCF6ULL, 0x5DF83B44DF7B67F8ULL, 0xC18F5578153B5ACFULL, 0xAD85E2EFC9DFDC25ULL, 
            0xEB6AE4346C9DDED7ULL, 0x6AE96937B86C81BAULL, 0xD85971CB412662BBULL, 0xDC23C36465EC4D94ULL
        },
        {
            0xCBEB2D05011850F1ULL, 0x45522B71405B4F9CULL, 0xDDD0FE2292B59415ULL, 0xC8611AE309631473ULL, 
            0xF428CCEE4DDF41C8ULL, 0x197CDB3DAA0BB4DBULL, 0xFBB8538B692D8970ULL, 0x5E6A1466AAA1AB03ULL, 
            0xB74EC7BB64AFB0A8ULL, 0xAFE2B860F37D12F2ULL, 0x2C035A52B65CD730ULL, 0x840B65A1A7A1A2D4ULL, 
            0xC00F8CDE619B2596ULL, 0xF8CD92E808FF2440ULL, 0x433E55FCBB9C9F03ULL, 0x1B53C465E245ACFBULL, 
            0x2895540AD2CED0FDULL, 0x9C77456BBB5410ECULL, 0xE85416B9FA3EFBA1ULL, 0xEED65748E85AC070ULL, 
            0xC340A53E43AF28E1ULL, 0x447BE6344AE1D952ULL, 0x85AFC91D49AC1DF2ULL, 0xD8B46D831F73E8A8ULL, 
            0xF3DF25992A624B7BULL, 0xE680272E29C1F31BULL, 0xA25FC18F5C275777ULL, 0x2CECC82513E3A56BULL, 
            0xE585CA085F8366CDULL, 0x11D07DAFCA7D28ACULL, 0x05A5E61728C72896ULL, 0x774011A5460FCFAFULL
        },
        {
            0x88CAE2D59641818FULL, 0x4D8E38823A7EA81BULL, 0xA8C8C128E7492B3EULL, 0x1A03DFDEB3CDEBF3ULL, 
            0x90194EB10EE62704ULL, 0x3656B083FD1E2AB6ULL, 0x0AF40682CC9173A4ULL, 0x7C142C868D57C4C4ULL, 
            0x57B2403DF5028F93ULL, 0xEE3506E1639506E4ULL, 0xA7F5C5D9CDFB649EULL, 0x609B7158BE64FC92ULL, 
            0x8528C9F8261D4F8FULL, 0x38F2B34A8D2BBFE0ULL, 0xF98BEA617FC44676ULL, 0x7CD9DA745A605B69ULL, 
            0x553B3D1CDB6C7139ULL, 0xAD3B3BCE0814EA50ULL, 0xA85A58F6DE58665AULL, 0x0D02587BBC90B4C5ULL, 
            0x3AF2FCA1AB942DF4ULL, 0x7D715D587C9C6802ULL, 0xC304EBB764CE6A52ULL, 0x9CDC24632EFBB747ULL, 
            0x68067919D25C0039ULL, 0xEB5A8BE07321F27AULL, 0x61B10066E8482FAAULL, 0xACFCBA22E895B553ULL, 
            0xF00E9BA440A0822EULL, 0xEE6CA081226A5C8BULL, 0xE144C648166C9986ULL, 0x3F3E91FFD5D08665ULL
        },
        {
            0xBB6E9D46C2D45DC4ULL, 0x922BD686964E82ADULL, 0x8EAA851F98C5571AULL, 0x2FE55CA631DD3760ULL, 
            0xDB1BB20FDEEB4EB0ULL, 0x6F437AB5B0CC1A77ULL, 0x35F7C2A142821808ULL, 0x8D8D08503B0FD704ULL, 
            0x58AC8F5305148F8AULL, 0x12803142F5586641ULL, 0x9CF33BCA9608603DULL, 0x094FD3CC3D0C0B26ULL, 
            0x93F2C2EC7DCF2D7FULL, 0x247804CE20F8756BULL, 0x3F79A6F2E015F154ULL, 0x02B86645A30D5F87ULL, 
            0x7B5DD8DA69263ADBULL, 0x8707557A1EBAA0FDULL, 0x92C7A522166C8A5CULL, 0xFBF5EFE82E8F4F4FULL, 
            0xECFA9AACBD2FFED3ULL, 0x19C5886FA72F1691ULL, 0x633F8098323C2DD0ULL, 0x0042DF34E6779CA3ULL, 
            0xEF50B7FDFB81E681ULL, 0x063B1701FC156EF3ULL, 0x5385C0D8E4321680ULL, 0xA0AB81C48A7536F2ULL, 
            0x1982FFAFA9A840B7ULL, 0x8D875525E57A0A0CULL, 0xDD010EA7A270770CULL, 0x1F29E67D1D0BBC74ULL
        },
        {
            0xC63005727FCECA3DULL, 0x9296BC346B33136CULL, 0x72D04F2D5D43D88AULL, 0x8E6152F4D1350EDBULL, 
            0x3C38385F7613AFBDULL, 0x9B0968356DF1DF2FULL, 0xEF5D8E3258507843ULL, 0xE770DCC40478ED10ULL, 
            0x98932A858F599B9CULL, 0xAD6DBDAECE7E0230ULL, 0x090C2C70EEA7F099ULL, 0x260A2F896748207FULL, 
            0x0B4297133EB2D917ULL, 0xFA109AF9D49C63EAULL, 0x1886CBC834D1E2D2ULL, 0x7F2255D79D1464FFULL, 
            0x6479E3C6F63388E3ULL, 0x8111ECF70EDE1B18ULL, 0x91F413363C949A44ULL, 0x1CEAC6C2BC1C48B6ULL, 
            0x706E088F25D16B60ULL, 0xFB68D9D45D1C58BFULL, 0x11EE205B10743C0BULL, 0xE8C5383A7A57C88DULL, 
            0x0BF6F44FB8FAF4A9ULL, 0x6C4F32BCCDC71598ULL, 0xA4A98FD5A6E9B4BAULL, 0x10BCD3D2EAF0041EULL, 
            0x8FCC6664EDFE100CULL, 0x42A80D9B1CBB704CULL, 0x69A8CCDBDD75043CULL, 0xEEA5FB7BCC358793ULL
        },
        {
            0xA7136E0C950C4B7CULL, 0x8714A5B32F2C898BULL, 0x07A9DE67DC5A97F2ULL, 0x82C7E968C30B23E0ULL, 
            0x6E0A461ED03DBAC8ULL, 0xE5EAE99FE12F2F3FULL, 0xEC1ACB97DA91A5BAULL, 0x819D88CFB6FEB7C9ULL, 
            0x0B76CC09177BE5A0ULL, 0x374AF0262A55B763ULL, 0x9CBB682473928A05ULL, 0xCBF21F2AE694AF66ULL, 
            0x919549E62687C207ULL, 0x7CD1EB3E17877556ULL, 0xA048687EC5E05D9EULL, 0x45283705A92F9E94ULL, 
            0xCA369E8758C73F6EULL, 0xED981A4755DF4710ULL, 0x4F2500BA917BE97BULL, 0xD09F2A4B0F4E9567ULL, 
            0x936401DF4664AE77ULL, 0x8D91DA0111A19742ULL, 0xF6A830A265F77719ULL, 0xB9F83B9F1429C6CEULL, 
            0xC3ACEC47777E51F8ULL, 0x0FDBBBF66BF6EFCEULL, 0x2FAB0BC28544C17FULL, 0xC9CBAFA351A15969ULL, 
            0x939E25D600CEDA2FULL, 0x4E60E885D56C40D5ULL, 0x8203AD8FD9064EAFULL, 0x5D8453FF038032B6ULL
        }
    },
    {
        {
            0x0A55D530D6D4223AULL, 0x829D525CCBD77EC5ULL, 0xAC63DE930BA9E086ULL, 0xCCECE54893D71246ULL, 
            0x716CF97A9AE3CFB8ULL, 0x265698421EC3583AULL, 0xEA56B759B036F17AULL, 0x75102993557A1603ULL, 
            0xE6F8492BE97B2D0FULL, 0x30898869E6C08188ULL, 0x8B47D2EEF8C933ACULL, 0x3E5A6C309FE93A42ULL, 
            0xCDB1058B75A65D25ULL, 0x147FE0833584777FULL, 0xDC69B83C4FC1F9E2ULL, 0x3DCB133DBAF55606ULL, 
            0x1029E6CA421BBCF5ULL, 0x5CBFF157DB21E8F1ULL, 0x4C4A4A7264F96AC9ULL, 0x7164CDB463F14361ULL, 
            0xE369B5ACD31E99ABULL, 0x8A0502CC06CBFB92ULL, 0x4CD391C39337774DULL, 0xEDA09609EDA07864ULL, 
            0x35EA011D970896A1ULL, 0xEF5AB88B0D88AC09ULL, 0xAEF8E861A34C5AAAULL, 0x3E6EEC98390EE590ULL, 
            0x652066DD5639C363ULL, 0x45CB796B27DB3CC1ULL, 0xC430ABD61EFA0C20ULL, 0x5194C1666EF110D3ULL
        },
        {
            0x3F25B4B1410261A0ULL, 0x8D87BBDDE8076615ULL, 0x097F97852B30BB7BULL, 0x0BF4FA52FB0332BBULL, 
            0x19A10E84C9C4DCDBULL, 0xBF892DF412B69D41ULL, 0x0ADC8160BAE76E2AULL, 0x79698351FE1ED6BBULL, 
            0x3C063F84D7BAFB0BULL, 0x1D42CF83D60E346CULL, 0x6BFFD8F1994E8914ULL, 0xCDDC89082798B205ULL, 
            0x0F6439D0ED27EA5BULL, 0xA319F6A8307ED2E6ULL, 0xEE9538A419BEDA41ULL, 0x30392D82FDA57BC7ULL, 
            0x2BC1D473A2C8AC00ULL, 0x612E7A70AA019E9CULL, 0xA1D825D4A879ED06ULL, 0xA6E250F56D580695ULL, 
            0x9901A03DC34B6287ULL, 0xA3595808B98E7061ULL, 0x164C45895DDFE28DULL, 0x997577F9061600B8ULL, 
            0xE7D7506E58FAD669ULL, 0x6B0309BF741F7576ULL, 0x25FE22C705F7E139ULL, 0xBDE9C8B843B53A7DULL, 
            0xF4B05020CD8AF4B6ULL, 0xF0B16940D9F14955ULL, 0x5486143856F3EA26ULL, 0xB27A4B0C67F48D35ULL
        },
        {
            0x5BCD57CDAA5081F4ULL, 0x991F74E9725AB028ULL, 0x75AAB2C0E7A4C1C7ULL, 0x7D8C9E97FA35C1BFULL, 
            0x235951E4D2953FE5ULL, 0x0695814E011B33DBULL, 0x80BFBB53707F8DD6ULL, 0xB814F7396A308ECAULL, 
            0x86982198BCCD893EULL, 0xD451449A58EFD015ULL, 0xE6F761347D629964ULL, 0xC379D05CDDB2716FULL, 
            0x95C74B02E7E5E4E2ULL, 0x93B0951726F15A6FULL, 0xEF24721B32C6D242ULL, 0xF62F641B878F47C7ULL, 
            0xE0BF76E117021AA4ULL, 0xE0CDC8478E2F24C1ULL, 0x7B464F8DC3591D4AULL, 0x5116B99E21C774A3ULL, 
            0x2F42F9A6B7F58437ULL, 0x80A41C7CDAD83A3BULL, 0x9FED529B3443B59CULL, 0xE302D1D7B79D1823ULL, 
            0x54226859F7292FB1ULL, 0xB99F8FD6070BCBB9ULL, 0xE02555AFDDF8629FULL, 0x810F203F60D48319ULL, 
            0x4B684D1292F5B09CULL, 0xBB80844319FAA2FEULL, 0x4D644A49DF011A42ULL, 0x9D5D253151ED72E7ULL
        },
        {
            0x4361A4DD7AF16BF7ULL, 0xA9C27DA6ABBF76A4ULL, 0x9315821005DD36B5ULL, 0x907D0960F7149A84ULL, 
            0xC2B56CEC0170DA21ULL, 0x6E1FD8549F2DB389ULL, 0x0B21CD4DB1DEC9DBULL, 0x18BB02A8218DB370ULL, 
            0xB1BCEE0EF9E90AC2ULL, 0x73087F66CED198C8ULL, 0xDEDF3CC0FA9D6237ULL, 0x9323059BDE0BF702ULL, 
            0xA0E0F0684188D2FDULL, 0x50F2D18B4538712EULL, 0x6B7B54564D363612ULL, 0x2B1385F10B17F76EULL, 
            0xCCD14C3057EFEE91ULL, 0xA34CEA66C0954D9CULL, 0x4883A0C4AB9FDD1EULL, 0x7917DEA3B70C6D4BULL, 
            0xD380FC532437CF10ULL, 0x937AF888C3F73EB8ULL, 0xF3EF62EAD71394A1ULL, 0x2177C12AAE580582ULL, 
            0xC1951B30AB4DE3CAULL, 0x61B8970DEC5BCDB1ULL, 0x1594F933C180C883ULL, 0x684FC6C099F69F70ULL, 
            0x7C4029531E94EAFCULL, 0x925DE40ED358DB3FULL, 0xB3124F7CE0EA2BE3ULL, 0x665D45E289A66EF6ULL
        },
        {
            0x5A4DA6DC7D031DBDULL, 0x299EAFE8E1EAFB7DULL, 0x4839EAFC3A9719FEULL, 0x47A92E82AD8B0547ULL, 
            0x80E20FB6D80D30C1ULL, 0xC5A828F2B4687ACFULL, 0xD58B40081E444058ULL, 0x68184E60E56CED88ULL, 
            0x9C7DB1223C006FA3ULL, 0x388E06FBABBAB40EULL, 0xE818249E8BEE8D0DULL, 0x19731C88988E6850ULL, 
            0x9F4737661D18D6EAULL, 0xE2247A178D46E64DULL, 0x1C86D2409456E973ULL, 0x87FE7A275DFFD06AULL, 
            0xDDCEFFD4A39C19FDULL, 0x6313E5221A455BCBULL, 0xEA646E271F523F4CULL, 0x6C4B6CBECBBC9E6BULL, 
            0x99FF76E616DA4FD5ULL, 0xECA0C4143B54A0EEULL, 0xFDE49673037A234AULL, 0xAB74C25849B3698BULL, 
            0x36B323104BE91FF4ULL, 0x7E9E2BFEA89D386DULL, 0xB4FAA3F59C08C7F9ULL, 0x0B4923537917CB7DULL, 
            0x748720EFB9E8936BULL, 0xF344F0FA97B62FBFULL, 0x4364781270F52C93ULL, 0x1764D386B5FEAEFAULL
        },
        {
            0x1FE43DCA68DE599BULL, 0x56CE46AE0FBC756FULL, 0xAC3A89E8615C0DF1ULL, 0xB9CE30109903E397ULL, 
            0x360742FEF0B1B01CULL, 0x15C4ADBC22AB0F7FULL, 0xD90E2647A8F21DD6ULL, 0x74A37903009FB87EULL, 
            0x6BF53AE626F5CEFBULL, 0xEF4016D7A15EE8BDULL, 0xD42CAFBEC18098FBULL, 0x28EA1CB5CA221895ULL, 
            0x653257A7F0690464ULL, 0xA57C1EFFC677534EULL, 0x3F071678575E4702ULL, 0x0CB994EC03CCA2D9ULL, 
            0x06C2EC094AB07F8BULL, 0x0C647A786290CD01ULL, 0x09D825A1678569EAULL, 0xB8D451EFB5B5CC1EULL, 
            0x031621370B3E1426ULL, 0xBB51CE2B30EF5DA1ULL, 0xDFB7DF013BCBAF64ULL, 0x31F749BE4A26302FULL, 
            0x5FA61772C687572EULL, 0x4B1AF62DFE3577C6ULL, 0xCF2F3C806534DD5BULL, 0xFEDB7E441102B944ULL, 
            0xCCCCC00ABE20049FULL, 0x4A250B2CE56CE456ULL, 0x506081FB8EAD388BULL, 0x9AC3D97A60551FC0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Mimosa::kPhaseHConstants = {
    0x5FE92438EEE87788ULL,
    0x7CD92B82EFACC171ULL,
    0x034EE07AE711F01CULL,
    0x5FE92438EEE87788ULL,
    0x7CD92B82EFACC171ULL,
    0x034EE07AE711F01CULL,
    0x7C0BD7094E602B24ULL,
    0xAC3FB1BBFFA3ED8DULL,
    0x8F,
    0xA5,
    0x48,
    0x4E,
    0x6C,
    0x2F,
    0x93,
    0xD9
};

