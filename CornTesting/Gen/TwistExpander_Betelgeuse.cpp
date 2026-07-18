#include "TwistExpander_Betelgeuse.hpp"
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

TwistExpander_Betelgeuse::TwistExpander_Betelgeuse()
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

void TwistExpander_Betelgeuse::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xB36D25275A0089ECULL; std::uint64_t aIngress = 0xCDDB940D78184A3AULL; std::uint64_t aCarry = 0xBE940CF6BC90F531ULL;

    std::uint64_t aWandererA = 0xA1E8F0DC7A3788ECULL; std::uint64_t aWandererB = 0xD654E93F70B3A914ULL; std::uint64_t aWandererC = 0xB3798B2002237445ULL; std::uint64_t aWandererD = 0xB83287A6DE2CC7E8ULL;
    std::uint64_t aWandererE = 0xB788C43420DB4291ULL; std::uint64_t aWandererF = 0xCEF63BF73FDE49D5ULL; std::uint64_t aWandererG = 0x92F36E9FF85ED92FULL; std::uint64_t aWandererH = 0x8813E0A1D4A763A5ULL;
    std::uint64_t aWandererI = 0xB28CD8F25095215CULL; std::uint64_t aWandererJ = 0xD5FB23F5B8313645ULL; std::uint64_t aWandererK = 0xEBAC6095D4523DD3ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17993037816145483491U;
        aCarry = 10554352740301130978U;
        aWandererA = 12655877424463589666U;
        aWandererB = 15263162823136609519U;
        aWandererC = 14969977322263654942U;
        aWandererD = 9451283033268046764U;
        aWandererE = 16386347839129128949U;
        aWandererF = 10218218448991561737U;
        aWandererG = 11308390280293422182U;
        aWandererH = 12521245980388560592U;
        aWandererI = 13349416521515985260U;
        aWandererJ = 13661418142203314258U;
        aWandererK = 11706183140503237463U;
    TwistExpander_Betelgeuse_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Betelgeuse::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x85FCB3B3505FABD1ULL; std::uint64_t aIngress = 0xDDAC6AEDF509C55BULL; std::uint64_t aCarry = 0xE5B932892EFF6262ULL;

    std::uint64_t aWandererA = 0xA8251F812725CC60ULL; std::uint64_t aWandererB = 0xDD779873CB3891B7ULL; std::uint64_t aWandererC = 0x90F2FEFC3AE3875DULL; std::uint64_t aWandererD = 0xA4E77CD514821A80ULL;
    std::uint64_t aWandererE = 0x8400334009BBF367ULL; std::uint64_t aWandererF = 0x9B0E0AF59F311EADULL; std::uint64_t aWandererG = 0xA014DAE723C0C59CULL; std::uint64_t aWandererH = 0xA80DB2D7333AA558ULL;
    std::uint64_t aWandererI = 0xFD60629CB7EB8281ULL; std::uint64_t aWandererJ = 0x8AE8F5BD418A3F4EULL; std::uint64_t aWandererK = 0xB76045D7EF60CCFAULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 14310339611815983511U;
        aCarry = 15856555448764427971U;
        aWandererA = 9351302305701037129U;
        aWandererB = 14704468681855983790U;
        aWandererC = 13455337795943284469U;
        aWandererD = 15357113200445379771U;
        aWandererE = 15329435291175962931U;
        aWandererF = 13291345203390579722U;
        aWandererG = 11826907926182303271U;
        aWandererH = 11563024070817779203U;
        aWandererI = 10420057632629075363U;
        aWandererJ = 14230684121840688054U;
        aWandererK = 10529610696311494915U;
    TwistExpander_Betelgeuse_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Betelgeuse::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xAB1ABF79F2C76278ULL;
    std::uint64_t aIngress = 0xBF93B64380380E23ULL;
    std::uint64_t aCarry = 0xD00B21514C44C0EBULL;

    std::uint64_t aWandererA = 0x930CB5745C20869AULL;
    std::uint64_t aWandererB = 0xB1963143E37039BEULL;
    std::uint64_t aWandererC = 0x9E57588F3FFE08AAULL;
    std::uint64_t aWandererD = 0xD436B0629FFE82AEULL;
    std::uint64_t aWandererE = 0xEC4140D504BDA608ULL;
    std::uint64_t aWandererF = 0xD07AA4CD6E427AA8ULL;
    std::uint64_t aWandererG = 0xF889182C38A396E2ULL;
    std::uint64_t aWandererH = 0x8FD774DE1D6FF7D7ULL;
    std::uint64_t aWandererI = 0x96D67222ADB81559ULL;
    std::uint64_t aWandererJ = 0xC156CCC2FDDDB355ULL;
    std::uint64_t aWandererK = 0xF0D1CF41793E9A98ULL;

    // [seed]
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneA);
        TwistSnow::Sha256Counter(aSource, aSnowLaneB);
        TwistSnow::AES256Counter(aSource, aSnowLaneC);
        TwistSnow::Aria256Counter(aSource, aSnowLaneD);
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
    TwistExpander_Betelgeuse_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Betelgeuse_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 13 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1848 / 1984 (93.15%)
// Total distance from earlier candidates: 22325
void TwistExpander_Betelgeuse::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 224U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 389U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1293U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1387U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2004U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1468U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 779U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1147U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 933U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 216U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 946U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1460U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1359U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1076U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 435U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1530U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1184U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1171U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 694U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1291U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 254U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 911U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1255U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1085U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1539U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 440U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1341U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1212U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1685U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1149U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1664U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1657U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 533U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 365U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 820U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 904U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1801U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 184U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1944U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1683U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1496U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1403U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 928U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1057U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1879U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1516U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 702U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1096U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 330U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1098U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1691U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1216U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1529U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 876U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1286U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1367U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1312U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 616U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 203U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 991U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1617U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1511U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 485U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1144U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1253U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 296U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 654U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1753U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1854U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1773U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 864U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1886U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1636U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1481U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1718U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1522U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 370U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 922U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1898U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 602U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1289U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 98U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1065U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 579U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1775U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 631U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 10U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1418U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 682U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 448U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1159U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 338U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 739U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 686U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1447U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1090U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1207U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 905U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 691U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1844U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1661U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 327U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 670U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 62U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1158U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2024U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 968U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 2008U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1220U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1276U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 996U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 50U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1926U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 517U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2018U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1150U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 797U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1693U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 751U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 273U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 320U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 182U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 695U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1443U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 364U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 218U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 324U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1770U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Betelgeuse::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x910FEFE8131AFA9AULL; std::uint64_t aIngress = 0xCE7509784F49E66FULL; std::uint64_t aCarry = 0xA71073CD65050B47ULL;

    std::uint64_t aWandererA = 0xC161D31544F98462ULL; std::uint64_t aWandererB = 0xE37DA3D503729330ULL; std::uint64_t aWandererC = 0xDEB754065AD0F910ULL; std::uint64_t aWandererD = 0xD0411C93236C992AULL;
    std::uint64_t aWandererE = 0xA1208F5EB5FBC875ULL; std::uint64_t aWandererF = 0x93226E3B6779D68EULL; std::uint64_t aWandererG = 0x85785D091665776AULL; std::uint64_t aWandererH = 0x851493AD2A5859E5ULL;
    std::uint64_t aWandererI = 0xE3D9A4580332FDACULL; std::uint64_t aWandererJ = 0xDB07E6211C577750ULL; std::uint64_t aWandererK = 0x9D56F140458104B9ULL;

    // [seed]
        aPrevious = 13308431026009920959U;
        aCarry = 12232428398741183916U;
        aWandererA = 11446897471171285624U;
        aWandererB = 12243570481825044387U;
        aWandererC = 11313240148841112472U;
        aWandererD = 14316601166265389445U;
        aWandererE = 9397211329224484771U;
        aWandererF = 12770581815203888304U;
        aWandererG = 9872984031865683525U;
        aWandererH = 15077868246526445664U;
        aWandererI = 18380677661159152124U;
        aWandererJ = 16391693206667258201U;
        aWandererK = 18243247187062665752U;
    TwistExpander_Betelgeuse_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Betelgeuse_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Betelgeuse_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Betelgeuse_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 13 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 6596; nearest pair: 470 / 674
void TwistExpander_Betelgeuse::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3156U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 293U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3586U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3088U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2975U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2955U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3388U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2198U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7666U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2080U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1151U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4974U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2521U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5233U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5997U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7973U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1911U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 231U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 874U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 364U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 880U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 463U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1719U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 777U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 954U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 346U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1534U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 551U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 988U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 870U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 677U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 256U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 122U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1820U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 412U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 204U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 13 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 6600; nearest pair: 505 / 674
void TwistExpander_Betelgeuse::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3042U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1609U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3179U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 527U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2561U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6017U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4715U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 44U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2903U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6912U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 642U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2934U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2090U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4474U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4965U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2523U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1536U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 918U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1143U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1642U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 192U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 606U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 17U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1230U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1914U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 204U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 264U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1543U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1484U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2001U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1558U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1931U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1571U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1138U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 558U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1394U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseASalts = {
    {
        {
            0x5B12D9BAFD411819ULL, 0xB47CF5F4D770AB54ULL, 0x7C8C743C22FAEEF6ULL, 0x20DD7B859A32B7DFULL, 
            0x2907E2886CE6473AULL, 0x1B7EE99A3A9E1698ULL, 0x58A82B029C25FB97ULL, 0xCA4B7146C7A23C6CULL, 
            0x42F4E486168A4D53ULL, 0xB7E89B316C224AE9ULL, 0x05E0913CB522B9A6ULL, 0x3A57F23043D5C78FULL, 
            0x1D56EE68B3A0E4C9ULL, 0xA5100C0742D0FB4EULL, 0x16E1C6F3BFAB6D90ULL, 0x2998A2FE3439A6DFULL, 
            0xFBC5212A221E8545ULL, 0x3D2138222C52E3D2ULL, 0x2F0EC5FAFCDC7AB3ULL, 0x805AEEFF3CB2117BULL, 
            0x1FBA478BAB7FB9A8ULL, 0x2754C5E84EA85E78ULL, 0x54E979A9CF3E63CCULL, 0x9B2322804B1726A6ULL, 
            0xD9A3380B34E447D7ULL, 0x34B4F8F2C62D1017ULL, 0x25FA9DFF31841E93ULL, 0x95158148F1BC0CA2ULL, 
            0x60B9575AC5FB57BBULL, 0x00B763CC2A348698ULL, 0x22F830F85AD2A951ULL, 0xCED6600980A9EC02ULL
        },
        {
            0xA633E3AD23039A20ULL, 0xDB93B783A7CC43FDULL, 0x0B1132E05B7345ABULL, 0x8CDFE8ECC0830F0EULL, 
            0xFE99A6612F674141ULL, 0x4568C9A4B0BCB1BFULL, 0xA7ED8E24A11B2D91ULL, 0x7611151CA5E61196ULL, 
            0x4839FF7BF93390BBULL, 0x86A26754B7902BEFULL, 0x75C1F0CFF8696FCFULL, 0x073D0DF4310FA60FULL, 
            0xC52E9C561A67C387ULL, 0xB9F2EE1CC917F75AULL, 0x462C10BF00B28232ULL, 0x12EAF6BDC49A65F0ULL, 
            0x33F95B18DB70C660ULL, 0xBCB8E706B35CC305ULL, 0xA6B727E55AF187A4ULL, 0x32FE5D975CB85C34ULL, 
            0x6A62CA1EFD75DCB2ULL, 0x34B1AB5928A5C9AFULL, 0x360DAB5B3BBBF039ULL, 0x0FC1FB531BB40EDEULL, 
            0xC5C1A0063A77B13DULL, 0xC24C47BF74556B32ULL, 0x4CE4C9893B87A0B7ULL, 0x133588144E2AE9B3ULL, 
            0x803C259B73CA9226ULL, 0x1582D655F4007E0DULL, 0x8649966F784530D9ULL, 0x30D1A5F50F317B08ULL
        },
        {
            0xCE8C9462235162A2ULL, 0x62A5047093AF1397ULL, 0x668D90083032596DULL, 0x79499831610C4308ULL, 
            0x0508807BCA07670BULL, 0xF6B7F8AE549CE188ULL, 0x107E95DF4B33C07BULL, 0x7129D93A03968DC1ULL, 
            0x9B0533910F015067ULL, 0x636B7B3B01EB1A17ULL, 0xAC46D7E41A58F86EULL, 0x2B702179A1AF6782ULL, 
            0x14967BF2E247B813ULL, 0xFB105F7E94A73386ULL, 0xA64ED936B74786C1ULL, 0x02DC29DC8FD5A296ULL, 
            0x272C25744A5BCB8FULL, 0x37C799C0F7354A96ULL, 0x778F9BA7A1F44F69ULL, 0x96569949B7D11702ULL, 
            0xD7E7B60E867FC3A3ULL, 0xA33E6A2082FAA7EEULL, 0x14B64B075ACF5050ULL, 0x1D9B393FF7B0CBC0ULL, 
            0x6271E5B5E808C18BULL, 0x88E8C0EBDFA23A42ULL, 0x0830A878F817F77DULL, 0x2BF09D938022020DULL, 
            0x9DF533CF78EE6719ULL, 0x226EFEBC2CA50DE9ULL, 0x790B8A7A6833BB87ULL, 0x76FE679FC090771EULL
        },
        {
            0x88A3D4D900B48579ULL, 0x7FA5B0C81C33341EULL, 0xAAF78A658368AB17ULL, 0xDE4B10066BF38AB3ULL, 
            0x66564F8B105D71D1ULL, 0x6614B19C15DD78BDULL, 0xF2B33290B12AF25CULL, 0xDC6C16933D4E4CB1ULL, 
            0x31D96154A99B3123ULL, 0x004CFC5EFA24E337ULL, 0x30F91116A08AD649ULL, 0x680B55F362FCB226ULL, 
            0x54A181838D276C86ULL, 0x4D094204BAC612E6ULL, 0x46000ACC83EAFBB2ULL, 0xE1E6A6EDF338163EULL, 
            0xC224D128FEFF75E8ULL, 0x3C44EA46D635CE3CULL, 0xD0C4A516F005126CULL, 0x149A19608A0204A2ULL, 
            0xB637B49EDB657AFDULL, 0x7F46263361261494ULL, 0x5581B9F620855BC5ULL, 0x97DF615B78A3B857ULL, 
            0xB7F59E9C43F86154ULL, 0x7E9C2A465FF603B5ULL, 0xBD5FA0FA8292E5FCULL, 0xC8005A3BAF51D666ULL, 
            0x99DEDF78007F9306ULL, 0xB2AFDB239CE9F6B1ULL, 0xD4D02E3CAD5CCD8EULL, 0x406DB24937B61A0EULL
        },
        {
            0x3E2324201A41E96FULL, 0x64DFEFF091155FB2ULL, 0x43896DA30055821EULL, 0x18E85E194CDC804FULL, 
            0x3FB9AC3327E7E519ULL, 0xE47979A0106609C8ULL, 0xF64E007FC536CFBEULL, 0xCE3ABF80154C2FCCULL, 
            0x039E65EA86B07C6AULL, 0x3ADC55A0103C09ECULL, 0xE231C72C48B8F581ULL, 0x848E27D1A03ECC78ULL, 
            0x403C52EA24FEE066ULL, 0xF40877CF480D23CCULL, 0x391EAD06273D8781ULL, 0xD431F178AEACD726ULL, 
            0x792FE10383B66014ULL, 0xC9566452713A4F4EULL, 0x05B66C609F0E1BA6ULL, 0x5ECB934C09068D69ULL, 
            0x9AC58B948DBEB53DULL, 0xA4279392A40181C6ULL, 0x6F15BD2912B28174ULL, 0xD034CA9ABF083FCBULL, 
            0x7E3D233C97833FA4ULL, 0xF74B790423BA54C9ULL, 0xB30AF53A4FA242BBULL, 0x7FDACCC21D0ED390ULL, 
            0x0847DB69580C6DE7ULL, 0x46FF6891BAB39802ULL, 0xCB1935E8C32E5BC3ULL, 0x008D3DD7997B67D4ULL
        },
        {
            0x92F3A932FE57A6A8ULL, 0x303AA27366DB3A32ULL, 0xC4748A82A7214CF0ULL, 0xF9016210FB8E78E1ULL, 
            0x39387B87D0CE5DE0ULL, 0xEE0AA5292E7D5D5CULL, 0x539327AF2BEC761EULL, 0x759AF69DB855C8A8ULL, 
            0x120108E38D4C047BULL, 0xA5769B135359CF0AULL, 0x43C001B31BD185DBULL, 0xE01535D83C12E991ULL, 
            0xC0391B3DB4F6F104ULL, 0x3CC54F8B78C611CCULL, 0x653D89C81948CA7FULL, 0xEF27E240D10BA4A6ULL, 
            0xEACC7A5F9E681414ULL, 0x845E1A36C5716964ULL, 0x593C1C6EB9153B95ULL, 0xC8ED2BD94DC07EB6ULL, 
            0x1B6ED2CBA47EFD4AULL, 0x1B1D4C39E2539BC5ULL, 0x330904972D9D2922ULL, 0xE700AF66E35A4F52ULL, 
            0x959A9BEBC2A2470EULL, 0x299ACE45AE24753BULL, 0x357948D61781605CULL, 0x6DBB915D933551DAULL, 
            0x73B1B6303FFB9F25ULL, 0xCC1AC7DF10EAD4ECULL, 0x86C2A64CA8A4C4F8ULL, 0xEF4BF5D7C8E7AE15ULL
        }
    },
    {
        {
            0x0C5E11EC91AE7A5FULL, 0x7B69DFB215E6B350ULL, 0x692BF695B73BF1E7ULL, 0xF66F0E1B8467D67FULL, 
            0xFFFCDA57910DAFCEULL, 0x5E2FF08B8E08EAA3ULL, 0x856FCF1C2E8359DCULL, 0x707522D8C801FD87ULL, 
            0x30AFE15534C689F0ULL, 0xB2788E264FD47506ULL, 0x3EC4926BDACF2481ULL, 0xD51EA02233BB8220ULL, 
            0x0A07514932EA5BFFULL, 0x1F25071D85C652E0ULL, 0x8FE73AA91EA266B9ULL, 0x21F5557584864065ULL, 
            0x47DF13A11F86B92DULL, 0x7C4CA87FFA59BC35ULL, 0x10FED20FBB0CA296ULL, 0xB2F07BE283493A93ULL, 
            0xE47D182FC51506E1ULL, 0xCEDDBEF9ACEFAE01ULL, 0x2523CACE4C799018ULL, 0x1C205D0C8B3364CCULL, 
            0xC005554162A22663ULL, 0xDF8FD017CD2A8350ULL, 0xAE56C5F3F23DB7D8ULL, 0xEC495F6C6DFFFFE2ULL, 
            0x0CB076275BED001FULL, 0x8A8E6AD47FDB347EULL, 0xA6706656193C2BD5ULL, 0xBE44EB706104D65FULL
        },
        {
            0x998BEA8E6AA971F5ULL, 0xAE6BD90430A492F9ULL, 0x9B29F3C6DF0088DCULL, 0xDF1E80CA9ECC9DCAULL, 
            0xCC0F1EA3B0F31254ULL, 0x87064D23F7F31C1CULL, 0xA4E6E7E49D3B4051ULL, 0x1C7D1F2B1336FE66ULL, 
            0xC81CDEA9A49D92EAULL, 0x903BDA33AA9D6C12ULL, 0x946E0138F1D07DAFULL, 0x84AC92A44D33B55DULL, 
            0x306033ADC9687B27ULL, 0xE3F22764C5A3C133ULL, 0xBF37A7D603F9D8A9ULL, 0xB4D6F49AD87AA920ULL, 
            0x437070BC02993259ULL, 0x990E9882EDB93BFBULL, 0x75CF002B5DB8AF2AULL, 0x618871F4DB15810EULL, 
            0x4B0EB795695412A9ULL, 0x720EE3D7B1F71460ULL, 0xBD03E2C3D582A28CULL, 0xD62E90A82453FC57ULL, 
            0x73805278190C872FULL, 0x109866665F9FBF4CULL, 0x9C27647D1C6C2A77ULL, 0x47C43E0042D8508BULL, 
            0x3D5E80F7C255F54BULL, 0xBF7E54B94297E7E3ULL, 0x7DA439872BA79AB3ULL, 0x8AB5EBCBC78F3FF8ULL
        },
        {
            0xD563B1E221DBED49ULL, 0xF40E763F8842FE8CULL, 0x710DAA1F9A998A50ULL, 0x23307B2C1E176907ULL, 
            0x0CC9574633B1079CULL, 0xDD63976CBF70E036ULL, 0x68A02ADA37B5032BULL, 0x68FDA955C12BBAD2ULL, 
            0x85D2C6B68B6E665EULL, 0xFB150EFCBB5E04ADULL, 0xC6FB32B4531FEBF2ULL, 0xAEB8637AE7078C0BULL, 
            0x2917052D128F597AULL, 0x0C921C8455F0E124ULL, 0x0D8BBF71AC0075B8ULL, 0xD3D4E2FDBB872AC0ULL, 
            0xECFB133B19A0D48FULL, 0x68F1D11919EDBC89ULL, 0x8CC5036BB59DF186ULL, 0xD33163E2FC29EDE6ULL, 
            0xF75255D1373A72CCULL, 0xE1F28E9F6531AA2AULL, 0x71D98A756ECE59F1ULL, 0xFC417E21D58E2E6EULL, 
            0x4586308499ACE090ULL, 0xEB7F2458CF1F329CULL, 0x8C528F43F9997EFFULL, 0x019CE100E318634FULL, 
            0x9F964E1FB5356C33ULL, 0x951AF931939153F5ULL, 0x1C4F615A8DB178DBULL, 0x2150B141B98AF09CULL
        },
        {
            0x9896BB0A5655B75FULL, 0x3D397B6448D1F61DULL, 0x3D2DB61814AA8D1CULL, 0xE8124B451C3B8E8EULL, 
            0xDC70AA5A9FF76645ULL, 0xDF4636EF68BC80E1ULL, 0x8A0E49DF71B9CFC4ULL, 0xCDC44237A32513D0ULL, 
            0x46F3352642D085ECULL, 0xFCFD524E31B23908ULL, 0xD87DC56984E30B4BULL, 0x33A2310467F4C7F8ULL, 
            0x107916B31829F9EEULL, 0x769E9E84D19F925EULL, 0x6F582CDFED6730F8ULL, 0x7ABCE6E67E1A04D5ULL, 
            0xF227D37890D95C57ULL, 0x733DB11BB7EC6EE2ULL, 0xB66F1C7978FF600AULL, 0x21BDFB50CB04F031ULL, 
            0x2AD5F41880A1FBA1ULL, 0x5A2333F93514AAEDULL, 0x8973C9C38FEA51C4ULL, 0xF4D2C2557F3223BEULL, 
            0x9AFCF44714C5DE28ULL, 0x3B851C732D53B34FULL, 0xBE1D545352CDB8D9ULL, 0xA26A765A53FC5B9DULL, 
            0x79CF1E5DF78EB2EAULL, 0xFE57AFCFE216EEA1ULL, 0xFE941399F2D865E0ULL, 0xB08A37285C9D320BULL
        },
        {
            0x6DCA8EFABD2C4641ULL, 0xF5A3207E42A703BEULL, 0xAF9199BEAA483E6AULL, 0xABE78521ACF3ABEBULL, 
            0x27CF4A65CB53AF38ULL, 0xDCCD5AD5BEC5C58DULL, 0x92CFD950AFE897C8ULL, 0x16A7FCFABF03845BULL, 
            0x327270B671B6BE08ULL, 0xE657430D9217E497ULL, 0x7210C7F4E0138BC8ULL, 0xB70A5F2D6592C167ULL, 
            0x1132F96919D55D67ULL, 0xBA3CC3F6D13DD8EAULL, 0x9DAE2BA36BBF1BDFULL, 0xDE71CC50DE190139ULL, 
            0x9DCCF742380328C7ULL, 0xF36F1683804CD5ADULL, 0x51BEDC04A5CED9DEULL, 0x54B79272D1509432ULL, 
            0xE290BD42ED6C366AULL, 0x8C4BD37EC936C4EFULL, 0x5B5F2DBED162CB16ULL, 0xC2E80715CF6C9C38ULL, 
            0x41BD6DA1D9C9E83FULL, 0x6F483658F11A3DF4ULL, 0x3BB1CA1498794D17ULL, 0x5D21F12D09236747ULL, 
            0x43516227DBADE45DULL, 0xD48E1594C4F45B80ULL, 0xF4641520FB7A02D0ULL, 0xE7FDFC4B0015D9F4ULL
        },
        {
            0xA5151CF88F4BFF8DULL, 0x1B5481A5F9E2ABA5ULL, 0x98F01A23949315C4ULL, 0x702C88ADB048F807ULL, 
            0x83F755D764775EF0ULL, 0xAB6B6EA07EC00007ULL, 0x532F3AD4EA4C3B9AULL, 0x094412007AC5B100ULL, 
            0xF87052E889C9FFAEULL, 0x0F315D1F7E3EA49AULL, 0xDCACFB04CE836782ULL, 0x234C0B33CE49DA74ULL, 
            0x09A66C4E1D93CE35ULL, 0x16A6038833AF8FF3ULL, 0xA854A0E290428C8FULL, 0x9D9EA3C74FF0D313ULL, 
            0x996116E670675DF1ULL, 0x6B3D63037C28C727ULL, 0xBEFB442DA56F31BDULL, 0xB5AD51B77B4A3628ULL, 
            0x3B12EC75FC0098CDULL, 0x760DDF68029271C6ULL, 0xEE88D34926639F7AULL, 0xE9F6959C6C43E766ULL, 
            0x36D4A9A43A171C29ULL, 0xCF47BA39E4A87B6BULL, 0x3BB967DCB5A9C54BULL, 0xE2BC4124A543BE35ULL, 
            0x0BD8C634AA4A1635ULL, 0x87C99295D8999C1EULL, 0xBE2FEDE52851C70AULL, 0x4BFF9D717D0799BDULL
        }
    },
    {
        {
            0x8912988DF32304DDULL, 0x5A480E628A14A80CULL, 0xD864B303FE3874FEULL, 0x730A4C6662676F7BULL, 
            0xB62FB041A689F5DAULL, 0x13E1B45C0FE3B7FBULL, 0xBB96F752C1470FC9ULL, 0xD08F3DA3AC7C8B92ULL, 
            0x05B6AF07AD19E9ECULL, 0xA84788890642BA82ULL, 0xB550914A075A1704ULL, 0x68011CC02D191598ULL, 
            0x000C7166C8DC93B0ULL, 0xB6ACBA8DFE8F716DULL, 0x16B63FB88295510EULL, 0xB9AE934B01349EECULL, 
            0x00F0E2D85B1959DAULL, 0x30225F49E701EA61ULL, 0xDE8169C1DA067AA5ULL, 0xF65E805DF8A5BB38ULL, 
            0x798D4C4F9650C1FBULL, 0x1D5BFCA7F0CBE547ULL, 0xD4F6FCD1CDA98BB5ULL, 0xE9063C20C9475DF0ULL, 
            0x5A65EF6B46442741ULL, 0x0FCC4D11999BE280ULL, 0xD95F017FB07F17AFULL, 0x01CC7531B062C8DBULL, 
            0x551855B64478BCDCULL, 0xD4588F507398E68DULL, 0x0F1FC246C44818A9ULL, 0x1D24F116BE7CF8BDULL
        },
        {
            0xE1BE441540309BE6ULL, 0x1E81974DD2D15215ULL, 0x1843032CAC723355ULL, 0x1C369A6AD22D85D9ULL, 
            0xC2A26E3B1DB55D4BULL, 0x75D16C96A1C5A965ULL, 0x32D649001229C0D6ULL, 0xA0BF3B15B3B26FD9ULL, 
            0x43C91991E8FCFAC4ULL, 0x17371C642F90ACE8ULL, 0xCFA58E0479BEFE7EULL, 0xBACD83047917F482ULL, 
            0xED7912A58B532BD6ULL, 0x494F5BEF7E6B95BDULL, 0x1CFDAB515F98B576ULL, 0xB58741E4B2648CCBULL, 
            0x0474CA9B5F052A86ULL, 0x3954B87B2B3C9FEFULL, 0xD7959D14F0DFB3C7ULL, 0x359619129836CFF6ULL, 
            0xFED54CED5CBB8079ULL, 0x1A7AB97236A9BD70ULL, 0xAFECD1C748C68F87ULL, 0x3916000AA560954EULL, 
            0x932B8DB0FB119D14ULL, 0xD526A291809086EEULL, 0xCCB15CF7107574E6ULL, 0xE36DD307FB3CFEDFULL, 
            0x41983630ABC16C52ULL, 0x064D0DE8FC8CEEA8ULL, 0xEE801420C50A42A6ULL, 0x373AA426CBFE1222ULL
        },
        {
            0xEE4E91865BC9BF35ULL, 0x14AE6CBE4C1FFD25ULL, 0x5F3689AEEE767213ULL, 0x7886E9664B5C09C4ULL, 
            0xE6C09953C6183773ULL, 0x09C227E5965EDDA8ULL, 0xC3F96BB6757D5B94ULL, 0xDF090C8933BC1BB9ULL, 
            0x40EDB79C398AE022ULL, 0xC8EB0753482ABE0CULL, 0xE762E90C5208674DULL, 0x701975F0E9560938ULL, 
            0xE5C620C1E05B2540ULL, 0x703EAA52DD123699ULL, 0x341E2F5679819A35ULL, 0xA2A2E2E1C8F9A98DULL, 
            0xDE5417103E39A26BULL, 0x314F0CA5E09ADC1AULL, 0x7B9B0BD30D8DEB4FULL, 0xBFA724F99576D5DCULL, 
            0x8A42E512A3ACEF46ULL, 0x8EDB7CB8EF093040ULL, 0xEB34B27A8A030641ULL, 0xAC9AB8E31EB460E0ULL, 
            0x12E164DF8C27625CULL, 0xE3FDF3DE71B740D2ULL, 0x82A80B3E6005881AULL, 0xE6B36AB778B6AF21ULL, 
            0xE9FAB62FEBDBBC15ULL, 0xBED45F49289A6A07ULL, 0xFBABAE18FFA9D39EULL, 0x8DDC2518581B750BULL
        },
        {
            0x20F4209F8C43055FULL, 0xB759CEDED405FF13ULL, 0x02C811B2ED43AD9AULL, 0xFC8B7E8A10F7EF5CULL, 
            0x5198E39B2E719283ULL, 0x6EDED1DE16D9AE0FULL, 0x12C25082960B14DBULL, 0x1236E9C11C2F04D7ULL, 
            0xAA20C2622A03D394ULL, 0xCDF1560F295ADEF7ULL, 0x79D08E8660743FF8ULL, 0xC71E99B10FC0CA80ULL, 
            0x2F634C9276EECC66ULL, 0x4F2EDFF4A4D2E480ULL, 0x10CB35B3E069043EULL, 0x13B5A252B1F6F054ULL, 
            0xC92B636B271972A7ULL, 0xD96A5F94F297513CULL, 0xF44BAE6689B5C6DEULL, 0x681F7D0ED9410605ULL, 
            0x6757B35DB708CA03ULL, 0x50F85B854AFC3338ULL, 0xD6B7539BFB491976ULL, 0xA817A3F7B1A1FA47ULL, 
            0x945E760CCE041416ULL, 0x65B788DB1410399EULL, 0xF4091E46AB39924EULL, 0x435B8ED8E276DA74ULL, 
            0x5E075D30732AABE5ULL, 0xAC672B61B87CCC32ULL, 0x25433194AE460C24ULL, 0x10D13A7E2D55C0D3ULL
        },
        {
            0x2358DBD485887F6DULL, 0x02EBFC5251AE8E35ULL, 0x8FF8E8222AD892E6ULL, 0x71C7EBAD3D558932ULL, 
            0xDD480F52451BE475ULL, 0x0B3FBF08E87B1DA7ULL, 0xF9D6C5BA43337604ULL, 0xE23B82D3A658339AULL, 
            0xAB36178C6311A486ULL, 0x4D6B85F8BEE8817CULL, 0xD0D9183979CD6BBAULL, 0xAFF2A20BABD815A3ULL, 
            0x0B9BFCCBECEB2862ULL, 0x4D5B5079117118BEULL, 0x341F27AFF1576F5CULL, 0x200E21B855D20F3BULL, 
            0x68ED3AF206CCF2FFULL, 0x01D94318D31CC4ACULL, 0xAB03032EEFBB340EULL, 0x0E6D139C29D58C08ULL, 
            0xD80AA40E7183FBD2ULL, 0x9376678632721E27ULL, 0xE2572F1631E5D44DULL, 0xBAF7C45FEC614627ULL, 
            0xB363DD3F2EF1A245ULL, 0x902529F993B7C2D9ULL, 0x2F73D79F66E735A4ULL, 0x58E9A5D1A94A91D7ULL, 
            0x008E10A3B9EFD686ULL, 0x5A564147CC211EA4ULL, 0x059966964AC54DF4ULL, 0x77D5249BC21A1EB9ULL
        },
        {
            0x80C8474CC6DCCD0DULL, 0x1157810463AB485AULL, 0x66B6BF63BBDB1810ULL, 0x3F7A6E4184F5D92BULL, 
            0xC518CF9DF879438BULL, 0x85FE5D9B83E4591CULL, 0x0B9D25C3F7C6001FULL, 0x09748987DDAF8955ULL, 
            0xBF90096438FC6CE4ULL, 0x433986505EFE1983ULL, 0x09DB98DCA9FE1604ULL, 0x33488412A64AE2DEULL, 
            0xCFD1788CA5FCCE3AULL, 0x5AA46CF5E92EF6D0ULL, 0xFD1521D383AEA260ULL, 0x2AA53DE83BADF590ULL, 
            0x61AA766E31392B6BULL, 0xFCADA1635A32FDE1ULL, 0xE674F709E008BC83ULL, 0x9DCC09C94136191DULL, 
            0x7C87E4F2BBF81B19ULL, 0x7A5AD33BECFAEECFULL, 0xEF2858F081A18201ULL, 0x5C4BD7CB0DF066B9ULL, 
            0x14681AB30D1373A9ULL, 0xC8123A4531F242B1ULL, 0xBC08699C16EA9293ULL, 0x9E667D0A61B2C180ULL, 
            0x99E79EF933023896ULL, 0x508A6CB6135B7A3FULL, 0x3050A871897BD122ULL, 0xEF028EC85BE4E6FBULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseAConstants = {
    0x1DCF5C3419827770ULL,
    0x227C11AAE8ED9488ULL,
    0x34955832C35AF27AULL,
    0x1DCF5C3419827770ULL,
    0x227C11AAE8ED9488ULL,
    0x34955832C35AF27AULL,
    0x38D813CCF065B9E8ULL,
    0x37D8D0D17F7E1C5DULL,
    0x16,
    0x50,
    0xBB,
    0x15,
    0x31,
    0x2A,
    0x7A,
    0xCC
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseBSalts = {
    {
        {
            0x2E94189103C10939ULL, 0x06F293152E5F32EDULL, 0x10661D6232AF36F2ULL, 0x0C5F24CBED0F6994ULL, 
            0x1F434CF7B1F1B8C3ULL, 0x3B8BFD69F2244D51ULL, 0xFA39579BC8D3D0D3ULL, 0x7E5E21873233B127ULL, 
            0x1BB0A11C6E2BD072ULL, 0x713597E356EB693AULL, 0x677DCD8BB52BAF5AULL, 0x110F87C8639CBFE1ULL, 
            0x7C34401557E53038ULL, 0xAA9EA2E4D30E5E94ULL, 0xE6B478CBD5B1BF7CULL, 0xB4DBF05A859A46FBULL, 
            0x3FB681A85CFDBADAULL, 0xFE635A3630539252ULL, 0x074348E1BA27F28AULL, 0x92734712F94F9B31ULL, 
            0x1805C4677D09239FULL, 0xAF3B4CA1D7A760B0ULL, 0x150D91BB0337983EULL, 0xA692F14AA1E5BC36ULL, 
            0x87196B3E44C28FF7ULL, 0xF13030C992D25528ULL, 0x43A3DE6C31B143CBULL, 0x9C1F89DA69BE40FFULL, 
            0x755FF7FD5BD5A486ULL, 0x0DA186173819456AULL, 0x4D41D25D1D833FB7ULL, 0xBBE1E6B6B6502BBEULL
        },
        {
            0xC789D82D41DDEB9CULL, 0xAAB45B99F01ADBD8ULL, 0xC27557E485D7C11EULL, 0x296A81CA083D98D5ULL, 
            0x05752C026A1073A5ULL, 0xE0ACA9C0C11A1B8AULL, 0x8F69CBCFEF50B297ULL, 0x48CF42DB5AFC14C7ULL, 
            0xBC502D85F54A31EDULL, 0xB9A5E8035423E7F7ULL, 0x709DDC0CEC9D8540ULL, 0xE41045C45C117463ULL, 
            0x3EF58C323F2AD5D4ULL, 0xAFAC69466CE720B2ULL, 0xC58D35392764F0C5ULL, 0x40C3B2B2316CB1CFULL, 
            0xEC7167CE9AC8A832ULL, 0xA7F40014F87DC484ULL, 0xF9B3AFFF52F201C5ULL, 0x1EFB04355C07D590ULL, 
            0x6F57263AA8BE7351ULL, 0x7E48C17BC962B73AULL, 0x0F08CE71A123B845ULL, 0x91C9C288113D6B85ULL, 
            0x17B879DD993B58EAULL, 0xEEEE58C63DC398F2ULL, 0xFC3130E0D4FDDE2EULL, 0x36E7497FA21F7EEDULL, 
            0x4121610F011B13DAULL, 0x4CAFD595F30F069DULL, 0x7FD9BDF860E65C7AULL, 0x18F2B366ED39DC35ULL
        },
        {
            0x1453F5CE7F32EDECULL, 0x971C69049CB4B3B9ULL, 0x1ECC00DA4C2CC2F3ULL, 0x7AFA7AF5DDCB7F74ULL, 
            0x45B0B6127914F3ACULL, 0x5F0F177BE87D3084ULL, 0xED4717F67B146DDEULL, 0xA0F5B92808598DDCULL, 
            0x5094712A7125E311ULL, 0x76B7F5389360D657ULL, 0xBF2A1EDEA9A9A9E0ULL, 0x7E52DA4214150EBFULL, 
            0x24CB29DCEE67D970ULL, 0x6614A6E8F48791BAULL, 0x195ACE5294FC3D0DULL, 0x29CBA84730FF6487ULL, 
            0x0840BEC9A8916099ULL, 0x19E0FA979E473097ULL, 0x746421F673FC87BAULL, 0xB5E2DADE927C67A4ULL, 
            0xF4299D7092291E3CULL, 0xD7D7DDD4DE696CCBULL, 0x6868601C023A1419ULL, 0xE992126525C97200ULL, 
            0xECB561426691F4C5ULL, 0x8FA581958574C957ULL, 0x7D3BAAB53943D23FULL, 0x26FE5C14D6EE6EC4ULL, 
            0x8B109150B893EB76ULL, 0x430DC705DE92102EULL, 0x73E1C75D51A1B2A3ULL, 0x2ECD6329BAE2D266ULL
        },
        {
            0x4E26E1CA4F0002FDULL, 0xC275D23430136A3EULL, 0x2B636BE1811A0F8DULL, 0xCE0F21B9060C49A1ULL, 
            0xCDCA297E9DFBE285ULL, 0x4305DFB3E3E9E2C5ULL, 0x24FDC5A6D26025DBULL, 0x333989979DE187E4ULL, 
            0x5999597301B85610ULL, 0x7CB561F549B45829ULL, 0x7DC3141B1942B7A8ULL, 0x85D1B366BE3AC7EEULL, 
            0x7AE2D56659B4E9C2ULL, 0x77779CE9AA456337ULL, 0x5D22770857A7AE73ULL, 0x2C328D22785116EFULL, 
            0xAC879B75371145D5ULL, 0x15983C3C7A741D35ULL, 0x9ECA3664E7BF0C41ULL, 0xB00D86FD08517C80ULL, 
            0x2EA005CE2B47F0F9ULL, 0x1D46580D1359A599ULL, 0x18EC857C1D329F78ULL, 0xAE5AF6AA6BF7D8C0ULL, 
            0xECBA9ABDC172919FULL, 0xB1F4D2F83D94636BULL, 0xBC715E7F458788DCULL, 0xDD3191C4105C8E13ULL, 
            0x3FB28F542513CF69ULL, 0x634DF4FEAD11D7F9ULL, 0x9CC48B1A58F1AC04ULL, 0xBBDD2D4C846974E8ULL
        },
        {
            0x533A0A3E5EE8F358ULL, 0x13133540B7587FD9ULL, 0x52992B859CF669B4ULL, 0x8CB11C1D89B78B1DULL, 
            0x624EF3C774934687ULL, 0x62509C5E6D016488ULL, 0x841C0F62FBF171EBULL, 0xA40B355B34ED2F20ULL, 
            0x6EBB9B8FC7A58ACAULL, 0x0C3E0511D38BEBEDULL, 0x88B1005AA73882BEULL, 0x02F18604BA55B7E1ULL, 
            0x1E24FB965A325CDCULL, 0x604870A69A333E55ULL, 0xC31915EE40069C81ULL, 0x3CBE10E749C11620ULL, 
            0xF0B40F44371F5FA1ULL, 0x2441231F5A155553ULL, 0x08174E2017658B25ULL, 0xCCF500774921DADEULL, 
            0x1A9CDC61869CBBECULL, 0x20445F1B80C44235ULL, 0xF4857FD8148128CCULL, 0x4B88CB7EF0F8735FULL, 
            0xA8B3086118F1C045ULL, 0x1A299EEA886A45E1ULL, 0xAC8E82F754625911ULL, 0x5598BA35AAE7532CULL, 
            0x9FE6F06D1D49FFB5ULL, 0x1958DAC496D942EBULL, 0x6CCAFCF3B14B9009ULL, 0x8AFE226AE5A124DCULL
        },
        {
            0x160C0D7979390FABULL, 0xDF656134278E50A5ULL, 0x967801098B71A8DCULL, 0xCDE1D48CC551BF71ULL, 
            0x61C176B38D2195BAULL, 0xFE218C1DB1FE5BB9ULL, 0x9FBE0F5C37BA18A9ULL, 0x2C7EB7405F55895EULL, 
            0x97548EE3283A53C3ULL, 0x201416A26661707DULL, 0xB1B5DC2769070E81ULL, 0x11E598A3F937D47EULL, 
            0xBB710050BDFE7BB9ULL, 0x2CB371B86621897BULL, 0xAF184A31ABCF750DULL, 0xAB77BB3E7189F466ULL, 
            0xAD824E7020072266ULL, 0xA102F29D477052EAULL, 0x05DA9A929CAED9D9ULL, 0x30051E6353B48F76ULL, 
            0xD369A56C1DD4A931ULL, 0xD3D533BC1F890F30ULL, 0x41319E68660D62ACULL, 0xBA322FA3EB942721ULL, 
            0x0F81F3F6DD69661FULL, 0xEA91F40B59C300E7ULL, 0xA79E8B875F1D6863ULL, 0x7223798292F89215ULL, 
            0x36EF120C4715DA9BULL, 0x776044098E97107CULL, 0x0B29284C43C19619ULL, 0xEEA6A8D3EE9D4039ULL
        }
    },
    {
        {
            0x483A9592364D29B3ULL, 0x2E2B7CD32F5566C8ULL, 0xF24B0920CD8C3BADULL, 0x78D5E0615EB0E7FEULL, 
            0xFB994F44E1B47722ULL, 0x9A4EBF68631FE447ULL, 0xE90EBB8E9F7121F4ULL, 0xDDB44A47598CB52AULL, 
            0x01CB48F675031DFAULL, 0x2CB82659CD16F464ULL, 0xCBA846DDA5336F4AULL, 0xCD8543530C371AC5ULL, 
            0xC4C1FDB201EE7647ULL, 0x732B10EA608674AAULL, 0xDCFB5A90081B9DD6ULL, 0x5A5F8969E25BD022ULL, 
            0x64F80F6FB3ECA183ULL, 0x021E79434176410EULL, 0xCCCB3C286189E492ULL, 0x3A89C2C55A788EADULL, 
            0x883AE3BA044732A9ULL, 0x69F786D02C8B1C79ULL, 0x3912C6E991FDB9D3ULL, 0x1F1FF79F0D3FFA1AULL, 
            0x25D68943DBF36FB4ULL, 0xCEECE6CF44682210ULL, 0x1D5AA36A8BA443A1ULL, 0x272AA3F967AD868CULL, 
            0xB737C8A2141272D1ULL, 0xEFE41ED7A2A8BBE5ULL, 0x7E50D0C8689C77A7ULL, 0x2FAFEAB7A6D77E9BULL
        },
        {
            0xC1E7A32E20312A8AULL, 0x22F962E0D3F9ACBCULL, 0x92F1E998F2DF9E6CULL, 0x6D429551B7331892ULL, 
            0x5B00B2FB40F4E9B9ULL, 0x838644D586C64CC1ULL, 0x8E49E860F827E2B3ULL, 0x9E196C6B35695AD7ULL, 
            0x202D770510513A2FULL, 0xE08297AA7E6BAA18ULL, 0x0C1E7ACE2F01C9BDULL, 0x0C722CFC8FC1493FULL, 
            0xA16844A8D089C188ULL, 0xE96350E30BA1305EULL, 0xAF15E32480804697ULL, 0x3981B482AA562CCCULL, 
            0x5A3FF8A071B4FEDAULL, 0xBF046403C48F52B6ULL, 0xAF71E854E0931A00ULL, 0x2C47AF46F4419661ULL, 
            0xF6857CBDA39F2BCAULL, 0xEF509EC72F3BEC7EULL, 0xF57F01F24000590CULL, 0xD98F7797DEB959B4ULL, 
            0x22003E6A7E77C1E2ULL, 0x54BEF0593DFB11D4ULL, 0x1E9C741263B2F31AULL, 0x08ABB41CDEACD38FULL, 
            0xA0CF8B1387537972ULL, 0x37E2F6C7D1FF9E77ULL, 0x8A350CEDFB095307ULL, 0x7D31800F9454C6D8ULL
        },
        {
            0x3E052BF63D33E614ULL, 0x9FFE4E6120C420B5ULL, 0x6057672AB84B4C34ULL, 0x43FBEF96C94F1035ULL, 
            0xD5C99AA454A49775ULL, 0x011BAB047600246EULL, 0xE9669386A086D9F1ULL, 0x66BFE23CAD5B0DB7ULL, 
            0x7260C0C281621BBAULL, 0x41A4EAB7FF989B3EULL, 0x3C97CD00A23FD4AEULL, 0xC6F4C3DD9CB8E424ULL, 
            0x37A95421630A8992ULL, 0xAEF1248A4772B580ULL, 0x5ADE4C869DD9A60CULL, 0x2D38B59FF92AEF60ULL, 
            0x3A4F7DFACF53E975ULL, 0x9FECE155FD225699ULL, 0x23A33DA7C7ED6FA7ULL, 0x6C0542BF2558FDCCULL, 
            0x280964C321A5542BULL, 0x43731DF6376692D9ULL, 0xF3567DAF5CABF7D7ULL, 0xCF3E0F9ADD7C8727ULL, 
            0x559EE863EE7FC06BULL, 0xFFE892C5044A2991ULL, 0x3D214BCDBA0CBE7AULL, 0x23C4305AE5482304ULL, 
            0xB5A176D1F1DC421DULL, 0xA7310F1095A8100FULL, 0xC001C33F28703526ULL, 0x79E1D04E08FC17F3ULL
        },
        {
            0x7FFF1015536F26E8ULL, 0x2208DBA58C669C4DULL, 0x70AF8C7C7FDEB44CULL, 0x08B9FAFCC44A89ACULL, 
            0x9BCA4ED7A05BA52AULL, 0x38F2613EDD211007ULL, 0x9083ED9DAFBCD12BULL, 0x02B670254713D487ULL, 
            0x7E067333D8A297F9ULL, 0x2A0712E38B9DA865ULL, 0x96A7FFBE36DA6DFFULL, 0x865A9579B198630BULL, 
            0x3DD0F0BA99BAC8A3ULL, 0xEBA3EB344008FE05ULL, 0x5B59D0EE7FB045B7ULL, 0x0657FAD3A7D72E1AULL, 
            0x2EC0EBA960286FA0ULL, 0xFB2658D53489DB06ULL, 0x6D3B6F1057C395AAULL, 0x74A6354D778818FAULL, 
            0x604EB3AEA24C4B24ULL, 0x7420755B29629F92ULL, 0xEC714B584C6ADC4DULL, 0xF486C67D52B29794ULL, 
            0xAA740D4B30CA5F5DULL, 0xD0A417915A8CE500ULL, 0x993DA3A95810C18EULL, 0xB4FC70334D147C80ULL, 
            0x9D4ECD8B2D92C2D0ULL, 0xBA13AA7C2BC56724ULL, 0xA381B86240CB0FCBULL, 0xBFE0BB42E94F2E2EULL
        },
        {
            0x8844076351946C6DULL, 0x0E441864B13B6147ULL, 0xBB1AD466FDEFE03AULL, 0x9C7D678C3080B2C7ULL, 
            0xC5A221BC0A8E8E83ULL, 0xB444AB9558E727EEULL, 0x67A42958C251098DULL, 0x7B3A41A687BE4347ULL, 
            0xCE99EEF3002A0357ULL, 0x6764D63BF5EC09BFULL, 0x7B884C7B5D578DB9ULL, 0x175AE856ED077C5EULL, 
            0x4224F3D5D4176B94ULL, 0x147E0409A968DFD9ULL, 0xD019658B944D4E90ULL, 0xF0D2C6BA4BEF863DULL, 
            0xAB66FFF959E5AA86ULL, 0x7A5C109A005770ADULL, 0xC91B7F73C62C6C61ULL, 0x11105ED9D4321CFAULL, 
            0xB6503C8BB1A212E2ULL, 0x8B2DCCC320D4804FULL, 0xA071413F205A7950ULL, 0xEFD1AEFA6F0DD29AULL, 
            0x971DEB428D106EDEULL, 0xCD0089E6D9B7E664ULL, 0x20F79C626B725367ULL, 0xDB9F301F630ADC7DULL, 
            0x6D10A95E0DDAFE3FULL, 0xC7764CEB37C6FF22ULL, 0x7974DCE0AE54F045ULL, 0x25ABDC30C1CE28BDULL
        },
        {
            0x818093E15FF58A88ULL, 0x94524B65184CAE9DULL, 0x72E0B62F3935BE87ULL, 0xA76E0EE356E45770ULL, 
            0x0B75FB30EF90D3F8ULL, 0x0F39B00C4295C0A1ULL, 0x676D9927506CF02AULL, 0xD3BA28B4CE0CA951ULL, 
            0x1E44147A4AFF7B61ULL, 0xCF4C33188D47672CULL, 0x83E57CC6CEE8E8B5ULL, 0x60D59DD3AF6DC620ULL, 
            0xACE2786C5D1775B2ULL, 0xE0F4F26E86A32BCBULL, 0xDA5532FCD1CE10FDULL, 0x0E3D4B4F2419D498ULL, 
            0x682B6954E38F6F46ULL, 0x80562C889333FD6FULL, 0x23E1AC1FDCFEE7D3ULL, 0x8DC0B0CE6F3C87E7ULL, 
            0xCF8433A4FD97092FULL, 0xCAB0CB994A4E0CD5ULL, 0x20F9F0355214EE78ULL, 0x11DC7EB1615499D2ULL, 
            0x6F03A6D9F3603E6BULL, 0x90991C0BA549889BULL, 0xC13FBFE6847D2232ULL, 0x5DA571F3E4CAFA97ULL, 
            0x2F3EB610F99C6B2AULL, 0xCD35651DB62DE955ULL, 0x796CC0E4EAFCC436ULL, 0xA34087434D45ED09ULL
        }
    },
    {
        {
            0x28F64800DA24C9DCULL, 0x096BC0FD31FE5D35ULL, 0xDB13107DFDF0C652ULL, 0x3706355428DC1D06ULL, 
            0xE3A81545544F44D0ULL, 0x5E1DFE1DB96CCF2FULL, 0x1A5B63CC3D374752ULL, 0xB907893773D4E34EULL, 
            0x39E56E01F58CE730ULL, 0x056643522ACC190DULL, 0x8D9EE5BA7CC0E714ULL, 0x546ED5F684B262AFULL, 
            0x2BABF2C2F6188362ULL, 0x8F599955B7688C18ULL, 0x2D726FAA1EF383A2ULL, 0x11506FE9B4455F4CULL, 
            0x3D471B666B3541BFULL, 0x958929DCB5C251D2ULL, 0xB4C24F0F219A2D90ULL, 0xBCF0A3DA2437CA33ULL, 
            0x06A2A8F959F82981ULL, 0xBCAFFFAF2A7B0219ULL, 0x6E30079BF0BFD471ULL, 0xE6FA6AE80E09A1AAULL, 
            0x0689860754D9F825ULL, 0xB30D12EA030CFBD8ULL, 0x81B2B197AF0A1773ULL, 0xD1D3D1167FDA50BCULL, 
            0xD021FA3CE6708B38ULL, 0x9D0AE22D7D922333ULL, 0xBFC2F450146257CEULL, 0xBBE36628E84675E3ULL
        },
        {
            0x1DB1A0E7597FB857ULL, 0xE867F01369E88AB3ULL, 0xA262E674ED6D290AULL, 0x4F002C5CC714DD78ULL, 
            0x84D5A92AE29C937CULL, 0x06CCBBE39A0F95E9ULL, 0xF95AF4AF14095DF9ULL, 0x84AFDBE24616234EULL, 
            0x30DC63538277D05CULL, 0xF48AF6C96CE9151DULL, 0xA69D1C8A4CCC9786ULL, 0x52B5D31EB7AF53F0ULL, 
            0x750F99FF61CBEE3AULL, 0x47267F2F13D964BDULL, 0x501408F777E552E5ULL, 0x8ABB104C0EFD805DULL, 
            0xAAD54DB7FADBCE07ULL, 0xDE8E3DB94C9E015EULL, 0x084520E14492D76DULL, 0x17F9587450082C28ULL, 
            0x531D685B04F89ED4ULL, 0x88ACC6447ED5818BULL, 0x2194987429AA7984ULL, 0x4C7B308D40B572E2ULL, 
            0xFB3794D3D757CC8DULL, 0x45D1DC4560BC09BCULL, 0x6A08B7B25414B8ECULL, 0x47EA65911D5A0E24ULL, 
            0xAA6CC8A806C6AA4DULL, 0xE8CC29710E2663C2ULL, 0x448B5A8A6F2F800CULL, 0xC5AFF318698B4009ULL
        },
        {
            0x2942D260BCBFA45FULL, 0xEAD1056D1EBA06B6ULL, 0xA8C838369D570150ULL, 0x0359A90E0099BF00ULL, 
            0x8878B7619BFF8A79ULL, 0xAE7AB7E15F88DF87ULL, 0x756DB9DBCB5432FCULL, 0xA4870887DD027A44ULL, 
            0x57E2EC92030C30CBULL, 0x54DE49F1F9558603ULL, 0xE2DB146F2AFE669DULL, 0x4BDA56B97DF6FF35ULL, 
            0xF573908290F06579ULL, 0x118A569B0B75EEEAULL, 0xF9E9047CC32FC287ULL, 0xDDA78B8CAECD0B45ULL, 
            0xB01AE7A3BEF4B548ULL, 0x0F17E2184B76328BULL, 0x3F30324BD8B38212ULL, 0x5BDFDE5A59A4785BULL, 
            0x9C576A59D8F14FB8ULL, 0xB19EE3BD65FFE4B7ULL, 0xE896983F94865F58ULL, 0xFAB9B862971F5579ULL, 
            0x20E6D925C5AF5C12ULL, 0xFAF0B9A853AC1569ULL, 0x58578D12DF911903ULL, 0x89AB2AB404C0C9D8ULL, 
            0x503B5993CEBB3EF0ULL, 0xA12DCA1F90945542ULL, 0x8A9D250640BC3423ULL, 0x32983B730E91442BULL
        },
        {
            0xC382149EE40560B7ULL, 0x609E38A3CD4413F1ULL, 0xA3CDFFBF9F841AD3ULL, 0x3A89FDDE75B11F36ULL, 
            0xC93F9E50268B440EULL, 0xADF2DCEB9C093A0DULL, 0x1DB8743D6E9870FAULL, 0xEBA3355FEC6CEB3CULL, 
            0x16D22212BF089186ULL, 0xAF42C4756E1A472AULL, 0x679829CD5578DA0FULL, 0xE54782CA6FA5D6B4ULL, 
            0xB48CDF8F1A5EFC0EULL, 0x94CA8E571D6C95FFULL, 0xDDE0D751EFBA60F5ULL, 0xF35E5F290E4A2810ULL, 
            0x8F0B28FC291F7006ULL, 0xA8E8866C4FAF6A46ULL, 0x2EABCAA585221764ULL, 0x67118D8261C10E2FULL, 
            0x3D765E6B31461DD8ULL, 0xBF91EBAEBAAE54EAULL, 0x0BB6B21D32248F38ULL, 0xC930C36320492986ULL, 
            0x98AB1A4F7150F5A6ULL, 0xADD2BDDC1CCD03DDULL, 0xAD594683EDE01C54ULL, 0xEE2E918691103BC7ULL, 
            0x89FF3451B2946C77ULL, 0x1497FCF27AD9A749ULL, 0x7BED626CC729750AULL, 0x6B015890E00DFF0FULL
        },
        {
            0x185E07314141A479ULL, 0x1C1B927F9F7F27C0ULL, 0x47BFD270AC782FDEULL, 0xA46A364B5D368936ULL, 
            0xFA42A1033525F49DULL, 0x833F1C876138C5ACULL, 0xF1A8E20643DDF0D7ULL, 0x6A0B7F5AEF6EC0FFULL, 
            0xA22DA557D273AD88ULL, 0xBBBEB041933CC96BULL, 0xEEBF2262D9541229ULL, 0x207ACF6D3EDA1554ULL, 
            0x4B21DEC4B0AF8906ULL, 0xDC99947AB6D7742CULL, 0xBFD464EBFF652A46ULL, 0x35C946BCA5AD7032ULL, 
            0x55A804B8737E5CF2ULL, 0x9724982475ECCA9AULL, 0xAFD33E5443451B7CULL, 0xDC068C94B81C45D5ULL, 
            0x967EA916D8BEFC37ULL, 0x383E7EDC9A10AFD4ULL, 0x03A39E584AAA6A1BULL, 0xACFEDBDA43E37631ULL, 
            0xD6042AD7ED32DF53ULL, 0xD6822BE154BDBB13ULL, 0xF901A10E234037AAULL, 0x07A029647E306DD0ULL, 
            0x713E903163069080ULL, 0xD78AE9FF7D9AE652ULL, 0x2CB91A8E6F193705ULL, 0xC335732FE906357FULL
        },
        {
            0xF1F2E988DB3B1446ULL, 0x908903E04799FFE4ULL, 0x3A0C01190714051DULL, 0x62473C42A93237FBULL, 
            0x8510FBBF105811A2ULL, 0x82C9F2F4F322485EULL, 0x4E111CFA30D42FA8ULL, 0x6056D240A7BA8CDDULL, 
            0x621136D7CB6A4661ULL, 0x716F1294ADDA00A3ULL, 0x4C95D64424E56397ULL, 0x03E86D3A5BED2AB1ULL, 
            0x49C3CFC5FEC8AED9ULL, 0x14C5DC429BD19B7AULL, 0x9C29759A18D0F576ULL, 0x72142E4CEED0E89AULL, 
            0x4FBF0C81E61A8FB6ULL, 0xF91A85CAEB0A457AULL, 0x52CC29FF1C7AD274ULL, 0xF19630BACF69A409ULL, 
            0x358C3AC769FD6C16ULL, 0xD0794A033181EF25ULL, 0x5B96938E12BDF87CULL, 0x2336411906623AEDULL, 
            0x6380E8A2A35D2A2CULL, 0xE25309AD367AFE87ULL, 0x3A6C4C749787BA14ULL, 0x1CE955A507B0A03AULL, 
            0x1BE37AB38A71FA90ULL, 0x362B11BE97EDBAE5ULL, 0x24E36A96C9D21F08ULL, 0x45EF323EDA2E02FFULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseBConstants = {
    0x301D0F1137FF81B6ULL,
    0x17E9C4256A16F5D0ULL,
    0xC0910CAD16AD2559ULL,
    0x301D0F1137FF81B6ULL,
    0x17E9C4256A16F5D0ULL,
    0xC0910CAD16AD2559ULL,
    0xA1730974509298CBULL,
    0x8CB62A2823271851ULL,
    0x04,
    0x54,
    0x5B,
    0xE1,
    0x4B,
    0xDB,
    0xE6,
    0x20
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseCSalts = {
    {
        {
            0xD37A1789EB7AF2BAULL, 0x1C17F0AE60BB0260ULL, 0x34FE42E6D3B88D4AULL, 0xDC5AA640F522BF05ULL, 
            0x40A36E7362EEEA61ULL, 0x4283A2E817EF8003ULL, 0xF01EB4E46DA12C0CULL, 0xA671F5E00800C2D8ULL, 
            0x7F0A12B7C3192531ULL, 0x26637043194355F9ULL, 0xA1EABC0F6AC78D7EULL, 0xEB33BDD29BAC32CCULL, 
            0x778F4DDBD9404FA2ULL, 0xB72AD61CFF8F59F8ULL, 0x56FD24CCAD409198ULL, 0x96B7BAED212BF03FULL, 
            0x075781F95681A9D6ULL, 0x319D8D34E1C67CA0ULL, 0x0C4BCC78899D4D22ULL, 0x1BA0FAF9AF1723D2ULL, 
            0x478C5BC0B1FF6A59ULL, 0x0C11E1F843234F50ULL, 0x90DB895C2E6CF093ULL, 0xFBB2513F39E4B89FULL, 
            0xB74277ECD62449FAULL, 0xF02F7B1454B173CAULL, 0x71D3A6B6EC1535D6ULL, 0xFBD622D3E12F1B15ULL, 
            0x0AA75095BFA644DEULL, 0xC03E9393E4D656C7ULL, 0xC047E2E3F820F799ULL, 0x45B8EF00D93CFF33ULL
        },
        {
            0xC1DEF7CE8B0457EFULL, 0xBFD0CCB72F6ABE9AULL, 0xE20493029108596AULL, 0x3DA9C0E4BB3E0839ULL, 
            0xD7F1B062B0ED467BULL, 0xAB7E0BAD7127D962ULL, 0x35806210A9EB105AULL, 0x875DDD9DD5D7DDAAULL, 
            0xDB12C465663166E6ULL, 0xDBA24447AF713C0BULL, 0x09A5275BB21B637DULL, 0x8E3364D052C8462DULL, 
            0x819ED9694685E1B2ULL, 0x5FA5FB5104C8F538ULL, 0x536542B96E0DE976ULL, 0xBE0025FBCD13B488ULL, 
            0x489A17D8C7D8BAD4ULL, 0xC7DB0C03C4164D72ULL, 0x33A75C81F66A82FEULL, 0xF63782407A44E771ULL, 
            0x3D581F11C1E90F5FULL, 0x105620472334B25EULL, 0x19DCD7061743C205ULL, 0xB6F3FB4C4189559CULL, 
            0x863E669D5EB187F4ULL, 0xDFFB2B1F932BC140ULL, 0x4C78051425C5FFBAULL, 0x49D2B89FC5DDAECFULL, 
            0x7A8C6DD40167E221ULL, 0xAAE343AF5656D404ULL, 0x066DF075DE96F675ULL, 0xF418D6A8858B58D5ULL
        },
        {
            0xF2898AFE41B57EF3ULL, 0xC31F5F26D1EC4E90ULL, 0xBA4D89A244716407ULL, 0x922181C7E13777F7ULL, 
            0x8FA2D4AE22849EDEULL, 0xF284924057B5F70DULL, 0xAFC9A3751AD48339ULL, 0xE91EC3CF0905C2CEULL, 
            0xCCCF282F71D01A82ULL, 0x204A043B3F9B2076ULL, 0xD25A3A0AAFD7BB61ULL, 0xE1D6CE1BEC01ACEAULL, 
            0x8E5215C98C7A48B4ULL, 0xB288C5D852B84EDFULL, 0x553C9B470EBCF886ULL, 0x42A5BCCE33AB23E6ULL, 
            0xAEF4CF1982D8F428ULL, 0x617AD8D9D6FCEFA1ULL, 0x832952F260066687ULL, 0x0A4742E13730F9F3ULL, 
            0x23C38AAC8CB7FFFEULL, 0x3AACCBBEA30E4143ULL, 0x23860E414B57CA7DULL, 0xF427039247D37F02ULL, 
            0x2565F75B619ED6CCULL, 0x58CF9DD8DBDF866CULL, 0x7925B553BD359E9CULL, 0x37FC8B86610A6EC3ULL, 
            0xF469D9A7C987330AULL, 0x482F288356F5AC90ULL, 0x80B6395659A933F2ULL, 0x0F6A6BC3872625A5ULL
        },
        {
            0x1155B0E500F08C36ULL, 0xE8D102C36129B426ULL, 0xCC716EE3829B0A9CULL, 0x80B3A77ADD792889ULL, 
            0x59A9B248825C4944ULL, 0x44BD958A7848CD50ULL, 0x4001CC97B9FCE16DULL, 0xE7812351924D409FULL, 
            0x6A3F070E49B42DEFULL, 0x788ED6D4CF6F5F38ULL, 0x9C89A60118E0817BULL, 0x19E87275600C7E83ULL, 
            0x2E141F7E93EED67AULL, 0xE3FD2642C20BD8F7ULL, 0x50DFA5EF2D14CD12ULL, 0xB2C3CCB106F05DD9ULL, 
            0x59D4E910C3D59235ULL, 0x06922656F195078CULL, 0x587C51FB3E2502B0ULL, 0x7AB7CF50DB97537EULL, 
            0x27B806840320ABB9ULL, 0xB80E5A32DF8AFC6DULL, 0x74E7BF97069AB4BBULL, 0xBA917D0FBEAF2A71ULL, 
            0x773F1A5D1FE940B8ULL, 0x11A3E672CA95C287ULL, 0x6A36265ECD54C508ULL, 0x8ED084CF1A7B394FULL, 
            0x007477904E946FEEULL, 0xFF2B196484023861ULL, 0x87F31E3D4E5CBBA0ULL, 0x7C8CBCA39BEC290BULL
        },
        {
            0x36B1FF328FA4CDFEULL, 0x19C13F63EFF70C1BULL, 0xEB8524A851328038ULL, 0x6DE770C9A93BA447ULL, 
            0xCA5C9CD842F39F71ULL, 0x074ABBCB6310866DULL, 0x29961D7920538F26ULL, 0xA3F7763F743C33D2ULL, 
            0x1DB73C2E5F32A906ULL, 0xBACF17CC0969AF6AULL, 0x803543A202F32105ULL, 0xD66D70B54B4780A4ULL, 
            0x8FE042A33AE351DAULL, 0xA5E8492DB6A486A5ULL, 0x01FB8DA2E6C89DB6ULL, 0x1BF881BE0A65F8E2ULL, 
            0xD711DC95EB9856BBULL, 0x5AC96847F01EFCADULL, 0x32649505E1CAB665ULL, 0xB14277488AEED56BULL, 
            0x6CE677CBE0CD4C7FULL, 0x0CDD623DCBC37AC3ULL, 0x3AA7373CA5F3A280ULL, 0xCEE1813BFA2DB467ULL, 
            0xFEB063814CA27F27ULL, 0x3CF33A27CF4024E6ULL, 0xD9AC0E12883C44D7ULL, 0x2BC280E389368507ULL, 
            0xE20690CBB811681AULL, 0xF1AC8AD86610E9CAULL, 0xFE5B166FE401F1F0ULL, 0xA317B7373DC3C51BULL
        },
        {
            0xEF7F502D347C8DCAULL, 0x4AE9AD9BEFD492FBULL, 0xF1FB7D0C22FF3F7FULL, 0x8EF5BFCB9D5E4C89ULL, 
            0x8647245BC0851CE6ULL, 0x9BCC89982BC1CEF2ULL, 0xDC494A0A8DF437FBULL, 0x943F7FC962BCE098ULL, 
            0x4802E8D5291BA097ULL, 0x8BD61A2E820CAAD3ULL, 0xAF18E80D353AFE33ULL, 0x9A3C107BB0E4D658ULL, 
            0x76A12EBBD9CF81DAULL, 0x964CB85AE08E97C2ULL, 0xD93059F877B7CA65ULL, 0x9B1D229B678CE0D5ULL, 
            0xD0187EAAB9B16252ULL, 0xDD3E7840305603DEULL, 0x02C2B4B61F96194FULL, 0x69D51315B7953E6BULL, 
            0xDBC353535C5ACEDFULL, 0x2C2510E63DE99307ULL, 0xC50376A0F2A05613ULL, 0x9CFAE7F394E75672ULL, 
            0x1289937BA947AE9DULL, 0x54496819F21291E4ULL, 0x9BB343C10E42F530ULL, 0x4F99FAE276709556ULL, 
            0xEEC969EF2979DC7BULL, 0x30E794B21ACE5ADFULL, 0xCE876676C600768CULL, 0x09CD0E108D6D1407ULL
        }
    },
    {
        {
            0x17C3B6EE06434290ULL, 0xB45FA191203E0CF7ULL, 0x2B8D1620A2189133ULL, 0xE11C4C9B254D2661ULL, 
            0xE7924943E3A56EECULL, 0x7F6617BCA156133DULL, 0xB33C1F6053706C98ULL, 0xB9FDD8E3D2A1C9B2ULL, 
            0xD89DA3EA0481F2FBULL, 0x1423627E1FFF4995ULL, 0x6B2C320A903E3A86ULL, 0x2B3A287731C562A9ULL, 
            0x415D02EAD16C5085ULL, 0x7164F492828A5A27ULL, 0xA9DCD2FEAE7C9D4FULL, 0xF4F20DE28B3C8514ULL, 
            0x536F2895EDB03231ULL, 0xD13A4EF566C159C7ULL, 0xD33F1066B4F99005ULL, 0xBB2794579F75E5EDULL, 
            0xC8239A62C5D66C6EULL, 0x8F29E0EF959616BDULL, 0xCD9BB94A582EC12FULL, 0xDD6B7D83B1B64362ULL, 
            0x315E3296BC50596FULL, 0xC1FAA5110BFDB210ULL, 0xD4B6CE45458EE9B7ULL, 0xA6E466A06667E585ULL, 
            0x9013B00AFCA142D9ULL, 0xB6F596518B96BA18ULL, 0xA0CCE2384604E537ULL, 0x5B4715F4105F5F36ULL
        },
        {
            0x0121A0774F1F6A54ULL, 0x5B6BB1637B62A40DULL, 0x7E04626B6CEF4971ULL, 0x1B307E4AB70A57F6ULL, 
            0xCA4768072C72366EULL, 0x38414074A5B37987ULL, 0x0BB07E9170AFFF48ULL, 0x3FC829D68E4675AEULL, 
            0xE64FD4CBE517D38AULL, 0xE096FD008F366272ULL, 0x8DF435B9579C8535ULL, 0x1D903EA937B479A3ULL, 
            0xA0BC432B1EE902F0ULL, 0x473661187AA8F0C9ULL, 0x3487B1AB5DA88D77ULL, 0xD4D1F6453C02A9D3ULL, 
            0x4F0DEAD2EBE13C6FULL, 0xA821DA6D0BAA6E35ULL, 0xE5F16E3CDB5090B1ULL, 0xEC00E0AB96959CBEULL, 
            0x6403997DE17ACAA5ULL, 0x61E6DAD69527E4E5ULL, 0x8B05D43AAC1C327AULL, 0x2B057F77A7D8328BULL, 
            0x2571BCB2AB234958ULL, 0x6BD83ED6DD48BD46ULL, 0xF5362A55F8709CB3ULL, 0x41B9CE1162E15AB6ULL, 
            0x76FDB61302C655CEULL, 0x5CCA1D93DF68ABF1ULL, 0xD5FEC3E874E26649ULL, 0xDF7880FFCF626DEFULL
        },
        {
            0x11938561730D2564ULL, 0x0A57B7125F7F6503ULL, 0xB57CF44BACF43D18ULL, 0x6C094A77F205029AULL, 
            0xEC841C9094F3FCBBULL, 0xB3E2E65AA428B8D1ULL, 0xE874E087EF507B43ULL, 0x5AAECFA9ED54D245ULL, 
            0xA2C6A7C53B0F6F66ULL, 0x8BF75C9CE5CA8AEFULL, 0x40E2EF50B9545455ULL, 0xE513247E03E76C87ULL, 
            0xCB08F26302DAB311ULL, 0x8FAE4E50DE3030B7ULL, 0x55EEAD472F53DBA3ULL, 0xA146EAE85D4A1C7EULL, 
            0xA7C822362285BD61ULL, 0x99F09AFC88A7E7B7ULL, 0x5B725DD4CFD69089ULL, 0x305B93D05133B0A5ULL, 
            0xB92A51D237CB4411ULL, 0xBD150AA5B6C01194ULL, 0x80A65D095675814EULL, 0x1851B775F080919CULL, 
            0x43C78E5F148F3208ULL, 0x0AE0E79893F1A862ULL, 0xA0E8AA44CC17D64CULL, 0x6ED0B383C3DA878DULL, 
            0x6DBECCED35653D2CULL, 0x38960B8C25D32DDBULL, 0x574EBBE0DCEF1062ULL, 0xBBC9FB6138286294ULL
        },
        {
            0x4CA1B8E56D671D18ULL, 0x16CC7A808D260577ULL, 0x729B89B7FCF5603AULL, 0xB6FD63862A4E85A2ULL, 
            0x332241DA16FF1C24ULL, 0x0D16923B72283347ULL, 0xB3901880E9D40B15ULL, 0x09A397A91C0300D4ULL, 
            0xA7727AEAE020C916ULL, 0xA77586727B3F37B3ULL, 0x9B430A31BFDDD3E3ULL, 0x89F3D4A0EA1DDBD8ULL, 
            0xE38268568E41063EULL, 0xAD72F8272F01A448ULL, 0x40760A0509BF05CDULL, 0x3274F42CAAE7740DULL, 
            0x095BA1C5D9D74B64ULL, 0x4AB6EF596EBC3C94ULL, 0x2DD6205514B1D4F8ULL, 0xB636A5E7296713DDULL, 
            0x1018ED9F84E5E9BCULL, 0x9671AEC0ACCF1B03ULL, 0xE6BF1A1B21FF50B5ULL, 0x97F4CBE37191614AULL, 
            0x28614C7FBE78731CULL, 0x6D2625BFDB25969AULL, 0x694E4D89B7F00F5EULL, 0xECD93BDD97008AC4ULL, 
            0xFC1C07FC4A0908E2ULL, 0x3E4DEFE289EEE186ULL, 0xF1EBF1079A1E8E4AULL, 0x42B2C82E917E8736ULL
        },
        {
            0xAE675CD689916740ULL, 0x57597B0EA0D085CEULL, 0xC5CF85C765CE557DULL, 0xEBB9253D35407C94ULL, 
            0xD028CA37A4269460ULL, 0xC17C7A701BC29658ULL, 0xCCD5CCA12ED7D0A1ULL, 0x59A4205C35FA0FE0ULL, 
            0x3126A4F5110F2667ULL, 0x15A8FD2EE01012D5ULL, 0x811C252FBB3F6766ULL, 0x0D93C15BE8B0BF83ULL, 
            0x6AE549CFF4B3D73CULL, 0xD5D62F4A887EB29FULL, 0xB24A0D863686C054ULL, 0x1DF3AF859C81D2ECULL, 
            0x2C7EFD51F4E7724AULL, 0x2AA8C8A2FD88F1A8ULL, 0x2382A12672A20E97ULL, 0xC1BF3AE9C27A09C6ULL, 
            0x103522E87D53BDB8ULL, 0x049782C21D593BC3ULL, 0x78EE27F8B9585CE1ULL, 0xD417BBC75C78FFD6ULL, 
            0x247C28E4ADE702FEULL, 0x0C4724DBCACC3C28ULL, 0x350531AF04747D76ULL, 0x2328E27842916061ULL, 
            0xF3E4BC4B45EA857AULL, 0x895171381AEC492CULL, 0x874A05412A48E61AULL, 0xF0796AF877375DBBULL
        },
        {
            0x7AC9B5A337AB248BULL, 0x32B8FAF4FEA9A1B2ULL, 0x82A558F01C7CF8E5ULL, 0x74ADEE97CB00F5D7ULL, 
            0x541FE03DF2C2D528ULL, 0xC22FBFC6199C3BB3ULL, 0x483FA820A4B7B53EULL, 0x86BF64EA7E5B6E51ULL, 
            0xCFA80B93C9980EBAULL, 0x42F83AB171549FD8ULL, 0x4C1D7E0F4F854819ULL, 0x0E36BA6EB904CF7BULL, 
            0x42C495756C1C6722ULL, 0xC745F0D51CD045A8ULL, 0xC21EFE9D0C35796AULL, 0x683CF2CA7CAC0C55ULL, 
            0x373E86748FBCBA31ULL, 0x715F280F75E28B1AULL, 0xFCB238088E64BE0AULL, 0xFF31FAC4BC0B9A2EULL, 
            0x84EF9989E757BB7EULL, 0x32C1F6119BE4F3B4ULL, 0x0A44776BB2C9E4D4ULL, 0xF5245068B4DFD5C6ULL, 
            0x56B219D225221DB0ULL, 0xFEE4CBFA8CA6FA19ULL, 0xB80BA0D9A1045054ULL, 0xF870AE737B4E26B2ULL, 
            0x11820E6AB70717D8ULL, 0xF12D67F4CE572CC7ULL, 0x0B9AA14AD2977E3DULL, 0xA1B7DC6B38C5ACC5ULL
        }
    },
    {
        {
            0x2E96F466D13FD109ULL, 0x610E85258AD6E76CULL, 0x52706FBDBCE8B63CULL, 0xB76A36639EB3644EULL, 
            0xDFFBA4641240BB33ULL, 0x97F23E73766B6B6CULL, 0x2EB62931CAB79ACDULL, 0xD15A4911E2CD15E8ULL, 
            0x5B1916D683DF1ABCULL, 0x56F1B5C4FAA95FD6ULL, 0xEB4E2777954F5A34ULL, 0x6AF25AE037B36BC0ULL, 
            0xC9A1221920A09D94ULL, 0x0ED94E8F3033DAA9ULL, 0x66433ED6DC5CD905ULL, 0xA764C70408A9B624ULL, 
            0x1F4EAE0ABBE463F0ULL, 0x4A64A457033C7C5BULL, 0xF75FCDD721200780ULL, 0xB4526074D9A432F0ULL, 
            0x1AF5B8B04204E916ULL, 0x34A24BFCF2938E98ULL, 0x845DD3C28B2C7EF2ULL, 0xB8829431E2A2DD48ULL, 
            0xC51B134C627F7783ULL, 0xA2B9F46A98E3D564ULL, 0xB8E08E07C56A01D3ULL, 0x71949130778C663FULL, 
            0x2ACBEC5975EF51B5ULL, 0x4D45692CA265F25CULL, 0xC95FACC6E2EE0FF1ULL, 0x56541B5114D204CFULL
        },
        {
            0x778D9F55C48D369DULL, 0x51B88C148AE05934ULL, 0x6629C2309DF90FAFULL, 0x5B3D4FB932CBD46CULL, 
            0xE7DF206E7C1322E4ULL, 0x352E71564080BB22ULL, 0x0076BA17AF2813B0ULL, 0x73F199611CD5BBD9ULL, 
            0x1F4848E38F73AE18ULL, 0x74C06F42B69D470AULL, 0xA56575BE5F2B6734ULL, 0x9E0DEA1A82D15E5CULL, 
            0xA627599E2F4FFEF2ULL, 0xC5CCDF199E32A6C6ULL, 0xF013292F9F04827DULL, 0xB62D30AFA00A4C96ULL, 
            0x7ED2EDE41C2154C9ULL, 0xBE4202156A073C48ULL, 0x028AB476BCB231D5ULL, 0xA281AEDCAFF56B3FULL, 
            0x4008CEBE52B2B9B6ULL, 0xC05361469B1FF1FDULL, 0xA343E1742C3FCAB0ULL, 0x077C4C091371D7E9ULL, 
            0x01A3E0DC7608ED57ULL, 0x02C70D02F57CC2B1ULL, 0x8DB3E993E46F24B8ULL, 0x7D4E786A602F0DA0ULL, 
            0xB68C471EED2179CAULL, 0x15F2C2A08D9042BBULL, 0xC73FE8EF0925686AULL, 0x200C5B15CE5AFF7FULL
        },
        {
            0x64AE5EF8A1FEF4C9ULL, 0xD1683D17A85091FFULL, 0x895C53A8FA945F62ULL, 0xA1C05B8191673805ULL, 
            0xEA4E15027A963858ULL, 0xDF34E6B221E5980FULL, 0x9AC6F76711074C9FULL, 0x8503F06EF9E5D705ULL, 
            0x0350D6B6231E0F7AULL, 0x574D387375FFE1B1ULL, 0x9AA56208E98860FAULL, 0x57A4943E9550145AULL, 
            0x5EBF2CF573F7FD8CULL, 0xADB28BFCC65E68FDULL, 0x3352345AE2972D5AULL, 0xE7933C38EACF83BCULL, 
            0x8B67DD08D8E3BC3EULL, 0xEF751959DEB22E3AULL, 0xF9079E3C6345F7E1ULL, 0xED1A3FA8C07AB4CBULL, 
            0xDA76205EAEA91C87ULL, 0x065A579326304FFEULL, 0xB774DC3786E3A453ULL, 0x2EA528EB31449D72ULL, 
            0xBFAE01F34B763F6DULL, 0x6386ED1D998F78ABULL, 0x226757386DADC2C6ULL, 0x03261A333EAF7D05ULL, 
            0xC438220E94614C6EULL, 0x5C640E1E8B7137D7ULL, 0x4C06EB6C76F480ABULL, 0x90541A918305C03FULL
        },
        {
            0x366FB07FBCCDE111ULL, 0xE7E1461408CD84ABULL, 0x1876AFCDACFC5F2CULL, 0xA712818CF19E73A5ULL, 
            0x54A964A8D9F13634ULL, 0xC20F320AB7FC78F8ULL, 0x493751F63486CEE3ULL, 0x7C844CEB45408EEDULL, 
            0x611BF53E8CAF1F05ULL, 0x790104D233637236ULL, 0x4A0F4A6F98B75982ULL, 0xE67CC217E0F60686ULL, 
            0xC698C6705B4F8F60ULL, 0x99461FE9A2DF555EULL, 0x82BD5229DB9F576DULL, 0x2D8F735C0CBA5799ULL, 
            0xF4EDED6F2D67DC00ULL, 0x558DA6429E54941EULL, 0x08BB7D6617799B30ULL, 0x625C7A68E56FE279ULL, 
            0xE6567D67F500AC87ULL, 0x2E44E36ED9720E36ULL, 0x632A065FB230BA99ULL, 0x08C5CC33F7537EA4ULL, 
            0x302A49926B93902BULL, 0xBCA1494EA4A3AF8BULL, 0x398F994B1A43D1EFULL, 0x383ED86AFD373E10ULL, 
            0xB5E1488AF979DB31ULL, 0x87FDE4D6F6B025A9ULL, 0xFA8B1DAEFA09E227ULL, 0xA1A907A094695AA3ULL
        },
        {
            0xE90880102D0D6F00ULL, 0x16551A6B438CBCCCULL, 0x7974A0912DD1E14EULL, 0x96CF57718A626CF9ULL, 
            0x60748B3A90A036E4ULL, 0x85C55D497FB16E6DULL, 0xE0798500E754D32FULL, 0x4F658107192D7E41ULL, 
            0x32B5D48D99246FC2ULL, 0x03B1E558B831AD39ULL, 0x4E5A63818F4E8C6EULL, 0xC0B4504FCD47EF72ULL, 
            0x3129518E9FE76880ULL, 0x4D4A19EAEE3DAEB5ULL, 0xA3EBD14166A9BC51ULL, 0x1A9E678ACDE0470FULL, 
            0x7CAD4294C0F47FF7ULL, 0xD75B895E1797703AULL, 0x6FD555ADC42BDEE8ULL, 0x2ADC16F68F4D380AULL, 
            0x009BCB07BFC9AC0FULL, 0xE8C243BFBE559775ULL, 0x3C418E1778908D39ULL, 0xFDD7E044ADB6B03CULL, 
            0xF01E8DE4D19F166DULL, 0xA4A5B104B4C7CC7CULL, 0x8A44D1FD53692543ULL, 0xE2E9F94C40C7CB10ULL, 
            0x4AE1AE62AED78609ULL, 0x2A59C278D62D6089ULL, 0xB571E3CE11ED3C94ULL, 0xC84A02C038112BFFULL
        },
        {
            0x21D6685FE9282FBCULL, 0x8B2608A215646CC0ULL, 0x2585987DFA9B11EDULL, 0x231D991020BB74AEULL, 
            0x568102749B0DD0EFULL, 0xFEF243F5D41CE6B0ULL, 0xCA584AD950C216AAULL, 0xCBF1AAF660F82948ULL, 
            0x48FB0D425BB9CEE1ULL, 0x55E37B8C9A747F32ULL, 0x87B9F2AF817509A8ULL, 0xE22C33FE57FC2A8BULL, 
            0x6A13DF53CD32C618ULL, 0xFD74F6352F782EC7ULL, 0x6A2606527E56F767ULL, 0x52AA376AE192D45DULL, 
            0x4690F0E1D3C56D1FULL, 0x05032E21DAA5313AULL, 0x3C5B0FEE9BAF044BULL, 0x6013728EC242731AULL, 
            0xF82469CF643F4D80ULL, 0xFB47DC7D4A62AB70ULL, 0xEF0D4CD870BA62D3ULL, 0x50C949C9E4F12E24ULL, 
            0xA4B2C874E3FAECF0ULL, 0x0B0EA7E0E997594BULL, 0xF565E6CC3E72367FULL, 0xE50D04FF7A943EE6ULL, 
            0xD33CB96B69A8F504ULL, 0x3C76DFBAB57FEE75ULL, 0x7CA90752606E7E79ULL, 0x20804F9826A28A5FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseCConstants = {
    0x5ED7282B4FBFC35AULL,
    0x984F0CD88727A9BBULL,
    0xCBE122034F04146FULL,
    0x5ED7282B4FBFC35AULL,
    0x984F0CD88727A9BBULL,
    0xCBE122034F04146FULL,
    0x58FD8CF67FFC4F7FULL,
    0x5D34F2DF44D4AA42ULL,
    0x3C,
    0x88,
    0x06,
    0xAE,
    0x1B,
    0x08,
    0xFD,
    0x98
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseDSalts = {
    {
        {
            0xA7430E780C051D63ULL, 0xADC118733DAB48DDULL, 0xA54A2FE6070FE5D2ULL, 0xE38B5BFFD322D392ULL, 
            0xFC36C964A4D66958ULL, 0xEBFF3524FD4AFB6FULL, 0x2F994814B6BBB195ULL, 0x0D108FBF8E659CB7ULL, 
            0x13937508D2A10BB7ULL, 0xCC6C49B1D156A06FULL, 0x01C28C0A66EA60E8ULL, 0xDE9C12C7FB4DAD1EULL, 
            0x5EEBDBE4B38A55E0ULL, 0xFC5E20B3AC47CC80ULL, 0xF7036EE12D0F6FB5ULL, 0x6437D37C1D289F2EULL, 
            0x4ADED6D2760F3E85ULL, 0x1701748267736E93ULL, 0x3B7C44A5F6C8128FULL, 0xC1CD486631916F46ULL, 
            0x2E5ED21AF1C50C1AULL, 0x7AE6E02DAFA6E38CULL, 0xD9E2CB12731CD912ULL, 0x6879F6416BB268B1ULL, 
            0x573D3244857CFB89ULL, 0x3CE73B179A8D6254ULL, 0x5166FCD7D54CC882ULL, 0x5108CAD8704F9098ULL, 
            0x416265DBDA74EDA9ULL, 0xCF1ACFF0F4E673A4ULL, 0xB13810F7D187B9E3ULL, 0x4B1AC321CFCBA404ULL
        },
        {
            0x8B466A76690DF63AULL, 0x07B2FEB89FADCAB1ULL, 0xFBB730B5FB7F7050ULL, 0xF69A908574F19781ULL, 
            0x9F5CC704FF534FFEULL, 0xE3D3E9E867447065ULL, 0x3DBFDB455B3ED2E3ULL, 0x51C984E855D0975EULL, 
            0x0A91131891146BDBULL, 0x3050590AF51D0741ULL, 0xFFCC21E5AFADE097ULL, 0x04E516E475248032ULL, 
            0x60186372595171D2ULL, 0x1CD7B71A5CAF9F45ULL, 0x716E34A4143ACE1BULL, 0x4A0B8AFF8B1FDBE6ULL, 
            0x38FA7F2B8032C666ULL, 0xE209BAB874A7C74BULL, 0xB77CC9C94E8C30A2ULL, 0x07C3D9C57DC50699ULL, 
            0xA40012F41A9C727EULL, 0x6474E02CEEF851B8ULL, 0xAB12F273F525BA25ULL, 0x8352E854376C9106ULL, 
            0x2E3E52FEE2592399ULL, 0x491E44F9FF019B3EULL, 0xC9942A364F437B9AULL, 0xD9CC035030D815AAULL, 
            0x4056A95462C33FEAULL, 0xE23B9FFEDDB3F99BULL, 0x9CABCF4809A246A6ULL, 0x5638AB3E610BBF81ULL
        },
        {
            0xBA85C37270A5D1DDULL, 0xD788F158DC557955ULL, 0xFFEFBABFF974B7A0ULL, 0xA1F422416BFF3B86ULL, 
            0xEDC8E12FD17EEE17ULL, 0xF224A35AC82FDE20ULL, 0xE69FB2EF772E0E63ULL, 0x05E7B01A2D076F20ULL, 
            0x3EC33E92C91A43C5ULL, 0xD8E39141B84C7BEDULL, 0x680E2BD0EB3F5047ULL, 0x35B486CB68F6FDBEULL, 
            0x7B18D01C3BBBBEDBULL, 0xEFB7050D0A4905FBULL, 0x6F5E8862C5860750ULL, 0xE6A24D1966DEE136ULL, 
            0x35E5F3EA0F801B43ULL, 0xE8C6AF9A8C226A16ULL, 0x3793C6007888BBE3ULL, 0xA85D3FD25F9E0126ULL, 
            0xB8EA624BE66E2BD5ULL, 0x954E43E25C439D17ULL, 0x2C170DAF0B27E7F7ULL, 0xE93C811E4436F7B4ULL, 
            0x4DB54F48613AFA6CULL, 0x9B3B21873B61DF5FULL, 0x674D5B42D484662BULL, 0x8E95C35A584D5660ULL, 
            0xC10B2842846A1B65ULL, 0xBE894C352FBBDD9FULL, 0x32CFAF762B853C1BULL, 0xF90BFCFF7A5A173AULL
        },
        {
            0x66B0F84258108918ULL, 0xF656497BCF5C60DDULL, 0x949FE61406C0D03CULL, 0xB45B03C8B42783DFULL, 
            0x1C5B03B2E969A6DCULL, 0xDB4AB20ACE7E5BBCULL, 0x31D1015FB668B167ULL, 0xE70D9BA04673235DULL, 
            0x0F009136E60A7A98ULL, 0xB5FE7969A186579BULL, 0x85F2798D003BF2EDULL, 0xABC0C9A89B3E6F4CULL, 
            0xFF741F00FA0CEFACULL, 0xBB1E8174F6B7F0AAULL, 0x4BC9E023A4329B7DULL, 0xCB7B64833BDBF74DULL, 
            0x6112714DB0FB4A37ULL, 0x7FDBD012A8233433ULL, 0xF98B47B18342BE25ULL, 0xF08004168034D541ULL, 
            0xC911684A20D78CB2ULL, 0x5C49FCE75EA12EA9ULL, 0x6D85216E089C115FULL, 0x00B3E839105A6259ULL, 
            0xFF919463FEB1A196ULL, 0x3520778B030D33D6ULL, 0x824AA292B43A9B46ULL, 0xC04BFFF0046E48C8ULL, 
            0x5A66DFFA31A6A817ULL, 0x6AD9EAC3850A89D0ULL, 0x53C59E9A1EA98189ULL, 0x4C3CAAF0190499D6ULL
        },
        {
            0x62CD0DA279F00484ULL, 0x0A0BE862A31E1A02ULL, 0x1A32FAC4AA8EF60FULL, 0x1E5BB6D7E07B05A9ULL, 
            0x44D8F64F4FCFA406ULL, 0x7DC800F20E332E19ULL, 0xFECD0E7A5302CF5CULL, 0xE3CCDD9A60F4B3E5ULL, 
            0x2CE7F316154B1F6CULL, 0xC16347287B0B1DEBULL, 0x8F5D35DD483D1144ULL, 0xA3C272A6E8BB7BC5ULL, 
            0xCAB5F90F57320780ULL, 0xCF6AD0CF5B437771ULL, 0x50A36FC03DA6F6EFULL, 0xE8FADC3DA9904A5FULL, 
            0xA6A633198C922DB3ULL, 0xD645D123471DA851ULL, 0x0C784D8A93FB36D0ULL, 0x0D4959A274638348ULL, 
            0x80E3326D869A998FULL, 0x31B532CC06DB12D4ULL, 0x2CEDE545F5A3CC5EULL, 0x3425000E331B9D66ULL, 
            0x97A96280CB55AB56ULL, 0x8766DB20F9799652ULL, 0xB76768046BA4296DULL, 0xB33C396AAD5BAEA1ULL, 
            0x63FA4BAE8963B370ULL, 0x81043487DF227FFFULL, 0x58B76C4ABCDA0725ULL, 0x6215E923B6F19CF0ULL
        },
        {
            0xBC8BB5369B88BC23ULL, 0x727A2128B392B5E7ULL, 0x479E3C19323B9589ULL, 0x40BBEC386A6BA8DBULL, 
            0x7B32FEF23B90C38BULL, 0x8D16EC807F71479EULL, 0x3A9DF59C1F0C06A8ULL, 0xBADF937AE8599DDFULL, 
            0x9380269F3E78AF3FULL, 0xC4DEDEA29F09FD5EULL, 0x61352FB33BD69618ULL, 0x8D56C2131B00889FULL, 
            0xE5FE03B4916BF3A5ULL, 0x41E6E0C54A844D70ULL, 0x77278B07B15637F9ULL, 0x28F1C5D9FD44F4D1ULL, 
            0x5A6D0CC24546121AULL, 0x001C4F381150AE1DULL, 0x75EE50D6F744C60FULL, 0xC6A5DEE4F4DD2E1CULL, 
            0xC03D0B9F97C16E53ULL, 0xFE5ADE13BEBC3E77ULL, 0xDAF2794D23F30B6AULL, 0xDC7831381C89BD56ULL, 
            0x22910D8AC391C2C1ULL, 0xF38A22AD8FE63B27ULL, 0x720DA59F11C9BD41ULL, 0x34773146981EFFAEULL, 
            0x5D6566431C2710F8ULL, 0x0F3853539D3D0A4EULL, 0xD94FFB1F9B349C57ULL, 0x3E6280BAAC3875A8ULL
        }
    },
    {
        {
            0x29A7B7507E67A1D3ULL, 0xE9721E9EE7B1D705ULL, 0x0516A46627408201ULL, 0xC245B28120C64052ULL, 
            0xAE3116D3AB572DCAULL, 0x9E26ABCD3906F713ULL, 0x5AEC0B61327EFFE5ULL, 0x7830602B566B8CF5ULL, 
            0xE05E0D77B1556187ULL, 0x633DF6CE1ACAF9A6ULL, 0xC9E230F2A040E539ULL, 0x65FC4544DC1A9A0DULL, 
            0x0F80913B10D47453ULL, 0xD5C3F7D26871DB6CULL, 0x1E3764055A8BDA36ULL, 0xD079B8420E749C97ULL, 
            0x764DBA0C857A5A18ULL, 0x892CF8DBD6224D9CULL, 0x059AF7A0FF6F2DC9ULL, 0xC9EBE9A76492C710ULL, 
            0x1475A37DA7775AF6ULL, 0x267794C5200EB622ULL, 0x9535C8626EBA5A21ULL, 0x2352A4118768CCBDULL, 
            0xB0EFCE54BC344C83ULL, 0xBA572CE86EA97842ULL, 0xE29F42A6EAE5AA80ULL, 0x7D0D85E5B4E0FC1CULL, 
            0x4826E453711FF307ULL, 0x9F3DF32CC88DCDDAULL, 0x042C36386441982AULL, 0xB7D1CBA14A9186E0ULL
        },
        {
            0x5D4A8D8E1A3BFFA7ULL, 0xC030AC5A5BBA5C69ULL, 0x0320DE70050A7FE7ULL, 0x8CE4A61B66D5A6D6ULL, 
            0x14C4E2C29D6EC965ULL, 0x3F2716E4B003E5B4ULL, 0xCD98409CF421BE89ULL, 0x41820A0A6D9FDB9BULL, 
            0x4A3F820F651C79F7ULL, 0xB7705B8E4A698C04ULL, 0x2DD5195AF8B6FC79ULL, 0x3B100434790B08BDULL, 
            0xC9F31FCAC460F595ULL, 0xED94170938512396ULL, 0xB4C818597A277F99ULL, 0x78FC81C43D1FA619ULL, 
            0x1CA7C926EA98EF05ULL, 0x40A73E6A1BACDFF9ULL, 0xD7F60CD5F29B1721ULL, 0xCBEF5E1A80EDF033ULL, 
            0x4112B104C032E8E8ULL, 0x8F7C58164407099BULL, 0xFBFBF6137EC44F30ULL, 0x865D86D18C11D80FULL, 
            0x16E0A68A30025832ULL, 0x102A72B5E488FCE3ULL, 0x99A954022857AFDCULL, 0x34731F00B286005FULL, 
            0x62D242CF686EE710ULL, 0x1D670D04CEF37AF1ULL, 0x485B0406DDE4A6CBULL, 0xDB6426133688E828ULL
        },
        {
            0x02302CD390DA42FDULL, 0x9D59F076022392CFULL, 0x4FF82C7F01F0A079ULL, 0x043FA5FF596FCAFAULL, 
            0x7339FA8DC89DCCE3ULL, 0x88E6B14199748FB0ULL, 0xE1FF7CDB4CC31B38ULL, 0x4A57BE5705BBFF9DULL, 
            0x0AFBCCA19D3B9247ULL, 0x764B06D37F9CE45DULL, 0x0757BFCBE59F4C1CULL, 0x765BF6DE551DF590ULL, 
            0x6AA353EC73FDC4CCULL, 0x440724CD571441EBULL, 0x1BE0585EF23AAF02ULL, 0x58F3F6429E3A7DE9ULL, 
            0xEE307561C1AA7595ULL, 0x8E7923419B22AF09ULL, 0x3826F673F5E6BA66ULL, 0x1F82F41CC88C71A9ULL, 
            0x2D37517C79182043ULL, 0xDEBDE2975E4AA0C2ULL, 0xDCA776CF77F32BA0ULL, 0x5FBB0E48431FED16ULL, 
            0xBC97613D9EE5D7D0ULL, 0x756FEF55831ABF26ULL, 0x57C68BD66DCC08D2ULL, 0x8236C8CAA93D115BULL, 
            0x88FCD5AF6E398D3FULL, 0xE0E57FC567B8E224ULL, 0xD9BEA4BA7AFE4B79ULL, 0x692691D209DD065DULL
        },
        {
            0x45ED193457D4CC1EULL, 0x68738F9966CB07A9ULL, 0x13EACDEFDB1574FFULL, 0xD1F235BE3A3E905CULL, 
            0xDFD1B330882AFB79ULL, 0x6CCCE5E050F1AF0DULL, 0xCBBFE546EC18E247ULL, 0x06FBD66FE137CE3FULL, 
            0xF4F4E6BEBA71C872ULL, 0xBF42E623A2343ADAULL, 0x22363E4E28774601ULL, 0x4A04317320F9A69BULL, 
            0x4CDB61CEC7151451ULL, 0x2A45CDF078404088ULL, 0x9C8484C2C2E5FA03ULL, 0x62D57CCED8BA97D8ULL, 
            0xDAA6361E24B7FBB3ULL, 0xDD06C3ADA17BEFC1ULL, 0xCB103622309F611BULL, 0x1AEB1858F0A589EDULL, 
            0x05740582AFC0E3FEULL, 0x724155FABB6DF2FDULL, 0x8546F6A72C432101ULL, 0x493C924CA569850BULL, 
            0x3E5303FA4463F4E6ULL, 0xA86A5584FE0D81B7ULL, 0x16004A40BF8E24F4ULL, 0x96B0B0108C98F9C7ULL, 
            0x7C031605A7794BBDULL, 0x961A5AA783EF7C7CULL, 0xA7F42CFC9E1DD67CULL, 0x4841555F9AE7C8C6ULL
        },
        {
            0x744AA8351E3B063FULL, 0xD5A49105F1930823ULL, 0xB7EF4D9DB560B63AULL, 0xFA3303780856A6A6ULL, 
            0x5AE2B0B8B1EEB15DULL, 0x9EFD30191A2FD323ULL, 0x4D85D907E7332926ULL, 0xABAB0F75C14606F1ULL, 
            0xD28C1CE160EA66EEULL, 0xB5B50623C20DBA22ULL, 0x376B09750E1FBB70ULL, 0x7D0D479DE0A8414AULL, 
            0x1C9B4B4D9CBAB2B5ULL, 0x70B002F8F41B6AEFULL, 0xEFFA9786AB8A8A3DULL, 0x980F85BDB919AFF8ULL, 
            0x8748DE745F426349ULL, 0xF34F6B121186AF6EULL, 0x3DF90AB1EF622A09ULL, 0x4803A3A0F3583DF8ULL, 
            0x41145FB6D91ACA8BULL, 0x9F187B4A0E45D745ULL, 0x141D9885F13736CCULL, 0x1026A8428722F93DULL, 
            0xA7180B8E70CFAEABULL, 0xDC3785EF87417663ULL, 0xBAD84489AE2D79C8ULL, 0xAA43C646A40E2E4BULL, 
            0xA13544BD76D15832ULL, 0x16EA923962C4A703ULL, 0xD6AE0A087177AA17ULL, 0x90328D8B5C2256C3ULL
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
        }
    },
    {
        {
            0xE21CE29AF7A48B27ULL, 0x7D654525F96EE008ULL, 0xF8E3663B2F5C69E0ULL, 0x967FE52ECBADBD29ULL, 
            0xECBEFB1BEB3916F3ULL, 0x7EE1C8E146B2E687ULL, 0x7E3BA4A76E085DC8ULL, 0x5287689E335F7D6BULL, 
            0x48CD515D851FC219ULL, 0x2F68A66F138A3D53ULL, 0x7409D30472005CE4ULL, 0x4C09DAD21390221BULL, 
            0x3E0B48E5719B9349ULL, 0xB262FC84225CD573ULL, 0x7C50B62B1114EC21ULL, 0x849F7357A134B472ULL, 
            0xB5AC10647A98BC32ULL, 0xC493FD3F4997FB8DULL, 0x26EEEBEC784014AAULL, 0x0B92F38B1502C018ULL, 
            0x1883A0A650C8A6BBULL, 0xD0146DF5527CE22FULL, 0x06347241DB160F81ULL, 0x8E9D71AB0F34EB9FULL, 
            0xAFFE87A826D7CD84ULL, 0xA9E6AABC871EFDD5ULL, 0xCF506E6735A105C4ULL, 0x09A2FCB2D92DE4B0ULL, 
            0x4947C71DE43048EFULL, 0xA5811C5F07E3B540ULL, 0x3C8B1A313B80331AULL, 0x96FD23EE5CFCF2C9ULL
        },
        {
            0xE6D5C57470DFF705ULL, 0xC3CE23A74F0F1627ULL, 0xFCB0DEEE3E8723F8ULL, 0x15F3015F527A62C8ULL, 
            0x7FE0F31BD2EDDD60ULL, 0x6D5651D7EE8ACEFEULL, 0x7F807A8FB8F497B8ULL, 0x456F05CD21CADD61ULL, 
            0x74647208F0930D0EULL, 0x418DCA6AD597FD88ULL, 0x0FB5E191EF88184CULL, 0xC4440CBF9A906829ULL, 
            0xFF05C2BEC1D53BD8ULL, 0xB18BDC7FBEA13371ULL, 0x2DBA9CC3AFF2128EULL, 0xC6B6498000A643B5ULL, 
            0xC1CA6E898ED40D58ULL, 0x5792A77BC884AFD1ULL, 0xC2614373E777F4C5ULL, 0x70EDD7F80BF40C45ULL, 
            0xDCA5E7DFB71B5A79ULL, 0xB59086E4198D16B6ULL, 0x09C4D5A0666E484DULL, 0xFF0D79B76A4A4CF5ULL, 
            0xD13080A5B7E914ACULL, 0x4D7509D1583D03CCULL, 0xD7608E00B5F9E6B2ULL, 0x8358D94883902D0FULL, 
            0x51D8E20282B84D98ULL, 0x224109007C152E6DULL, 0xBC91FC8A2FC42A2BULL, 0x9554206FF0A32D94ULL
        },
        {
            0xAF253AC91C8D678DULL, 0xDF938E23821FDD69ULL, 0x206F6E1FD2B083C9ULL, 0x1AB6A760904D2185ULL, 
            0xFD2EFA9341E3DE5DULL, 0x8ACE3D9425545FACULL, 0xC4A4C2F8C062ECD4ULL, 0x8C03616575BB6F74ULL, 
            0x8CE6D36440DB568FULL, 0x23E5AD24A55C5B99ULL, 0x61901D60B145952DULL, 0x135E2BACEE2B7B07ULL, 
            0x41B8A487262B7B86ULL, 0xF626D24DA518C7B8ULL, 0x00FFD7E2BB92C468ULL, 0x864A6A220783A67AULL, 
            0x5FFD37E5832EB4C9ULL, 0x1FEDB56DEA500E70ULL, 0xC3133698344DD5A7ULL, 0xA98204433E4A570EULL, 
            0xC9676453BF2454A3ULL, 0xFF1109D89A2CB93DULL, 0x31AB0DC8560D6637ULL, 0x07A364172DBB24EDULL, 
            0x46EB54B8D1F5606FULL, 0xF3278074DDAC8DDFULL, 0xC28FAD68CD51591BULL, 0xD1B62016D7A7781FULL, 
            0x46074969F1AD726EULL, 0xE4D6463AF64BA89AULL, 0x4B79BFA25A134F57ULL, 0x955C4A7013EFBD94ULL
        },
        {
            0x24D2D54E8E97B969ULL, 0x22C5C0BF34B7157DULL, 0x58DE35A94F5CC147ULL, 0xF9E4FE3838DF1FDEULL, 
            0x531A1731A69EA549ULL, 0xF09E36171B0F83F0ULL, 0x2F89B761004100E9ULL, 0xB3B88D71B0F24D9EULL, 
            0xA927F760028A62FAULL, 0xF5028C2399E04D6DULL, 0xDBA3F44165187695ULL, 0x6F96394A82DB356FULL, 
            0x82E42C24CDF46B14ULL, 0xCF28DC2B2F5C9055ULL, 0x6CFE8323FC97A815ULL, 0x60FF7BF81C1FEDBFULL, 
            0x8E069093B26F82ABULL, 0x234F0015E31E8158ULL, 0x8B6E82EC4DBFD6D5ULL, 0xFABA26008FE486E2ULL, 
            0x5961B4459D3D9BFCULL, 0x6D26C73B0D935EC7ULL, 0x6E74651F89D5CE70ULL, 0x1948EBCE3EF22139ULL, 
            0x63B2F62C0A388419ULL, 0xE8CCFBEE68151F7EULL, 0x961D2E47180A4812ULL, 0xCB6DC3548830E185ULL, 
            0x2E37F77B4809D180ULL, 0x743D5C38E64BDFC3ULL, 0xB42FA1104ADE81F1ULL, 0x0040A86D9EEE4215ULL
        },
        {
            0x27FA4A302AA6DB35ULL, 0x64C278990E7626E1ULL, 0x2C6EB33C977F0EBEULL, 0x31C687B69B0F2BD2ULL, 
            0xAC499FC9A0C9AA92ULL, 0xE5E7148EB2415252ULL, 0x3937583E87FAA46CULL, 0x51E68D11430522EAULL, 
            0xB37EAAC8E991ACA8ULL, 0xF2847181E779F9FBULL, 0x548555F4C8A4B1E8ULL, 0x0EB1798F590C75E8ULL, 
            0x395900207E6A701DULL, 0x4C2CC6D2A32A7AFBULL, 0xD88E972A337BEB9FULL, 0x8A0140B3BA1232BBULL, 
            0x7843704C30B7D1E2ULL, 0x732406F826E41AEDULL, 0x075F5F00FB49ECD3ULL, 0xD7CCCC2A6EC90139ULL, 
            0xE8E73B3FFAE53EE7ULL, 0xC212FCB7AB7DB808ULL, 0x894359537240187FULL, 0xD95CF0C188FA6163ULL, 
            0xDB6FBF2E433F1FBCULL, 0xBEF7914640ED2E81ULL, 0xA2869CCDB7CD8496ULL, 0x7B89290C57BFF776ULL, 
            0xACDF256BA733473EULL, 0x43A4EDBB5406221AULL, 0x9136AA7B0D0D3D23ULL, 0x8C24B3DC166B8F82ULL
        },
        {
            0xBAB651C75B630B82ULL, 0xF587F568FCE61C6AULL, 0x79BF6DC6E39D73D9ULL, 0xC512D28E2ABEBB3DULL, 
            0x3C7B7D62CF2E4BF7ULL, 0xAB8A2A1EC79EA789ULL, 0x9734E8B6616C7AF9ULL, 0x5346D188D168D5C5ULL, 
            0xBF4EC73D7797081EULL, 0x7C7BAC8DE8860739ULL, 0x308C923D70BE97F1ULL, 0xAC32211DCFE0B776ULL, 
            0x79336FD53DF9F118ULL, 0x77E7CACAE2663FACULL, 0xC961F6D4B1A2BFA5ULL, 0x713F80A6328BBE15ULL, 
            0x804F4489B1A29E74ULL, 0x05651BD2CCEF56B0ULL, 0xAD26E67ED261B9CCULL, 0xA3D24E18144AFC22ULL, 
            0x5D86DC30E9EC4A79ULL, 0x092D0C3E2260FC99ULL, 0x5F358D08EC768999ULL, 0x0D91A61173383995ULL, 
            0x945B221BE561F373ULL, 0x0417A748AE7B0976ULL, 0xB78ABDED493EFC14ULL, 0xF4D3BF0E37F11A8EULL, 
            0x285B686822332CECULL, 0xE4B562E14F6FBE39ULL, 0xC0AA0A98DB4BB7A1ULL, 0x9386A146097D4699ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseDConstants = {
    0x29A4565F48DF9F2DULL,
    0xE63CC7FA3D1FF7B1ULL,
    0xFC1FE932C0A6376BULL,
    0x29A4565F48DF9F2DULL,
    0xE63CC7FA3D1FF7B1ULL,
    0xFC1FE932C0A6376BULL,
    0xA71877F188A7ABB8ULL,
    0x48879E1EBCAE73A4ULL,
    0x7B,
    0xB9,
    0x89,
    0x2F,
    0xF6,
    0x85,
    0x33,
    0x52
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseESalts = {
    {
        {
            0xCBA3B95156B9FCC9ULL, 0xC8EE351558B7E59CULL, 0x9D8CD4CBF4053F9DULL, 0x94663A1393BEBA92ULL, 
            0xF9FBA89B86292696ULL, 0x80D7C4C0BE85EE44ULL, 0xF76F2BED6D69407DULL, 0x81E1864665C189EBULL, 
            0x502E1ED1F8A2AEF8ULL, 0x41C97F8BDE77F74BULL, 0xEAF3EFA86516B27EULL, 0x0F62AB341E535240ULL, 
            0xAC2F1671D99EC97EULL, 0xCBA895D6D0FEFFFFULL, 0x6BB2645A2904ADDBULL, 0x3E531B0585C40946ULL, 
            0xD7897FD52425AEDFULL, 0x7EF60D621F0B1D53ULL, 0xD5A722F65006DA67ULL, 0xE0323DA0E59BA8B1ULL, 
            0xB4D4AEC08486D911ULL, 0x90ABFFA15524857BULL, 0xB83603ACD671BCA3ULL, 0xDAF649E11611809FULL, 
            0x25C52A95155D8BEEULL, 0x3E0A064DDC33255CULL, 0x6594D7FA4D45ACFFULL, 0xCD4D6F5865C41FDDULL, 
            0x06D2C95E810065FEULL, 0xD8ADE59AEEE2AAAFULL, 0xA4E16634A2B8F975ULL, 0xE950C294AC9DF7F2ULL
        },
        {
            0x1AEBF11F743775B3ULL, 0x677F4ED4762801FCULL, 0x096238D880D01A9DULL, 0x2C59B1C2E3320AAAULL, 
            0x41697514BFB2A2E8ULL, 0xC294AC4C34CB036EULL, 0xF92A712611B271CAULL, 0x44FA78AFCE1EF759ULL, 
            0x754CC987F395FFF6ULL, 0x1FF600F92E2FC4F1ULL, 0xC09E085229F800B1ULL, 0x51C98219DA7BF485ULL, 
            0xC57C3CFF03A3DE54ULL, 0x1111ACE1902A0D6BULL, 0x80789BFE58BA45C5ULL, 0x83459EC7BF8173FBULL, 
            0x26C3E4035C9CD899ULL, 0x13A4C3D9B8796825ULL, 0x8BE4E3575AB409B6ULL, 0x52DC9869E5E715DCULL, 
            0xC8314F5B509EF28BULL, 0xCFC1D4CDED23DAFBULL, 0x5701E624C1520258ULL, 0x44E1A4BCC759249CULL, 
            0x23067623F8BE42B3ULL, 0x6D860618D3551E54ULL, 0xDAEC574A234D9793ULL, 0x03C9CC9FEF6ABF73ULL, 
            0xD7710C0F32382AE4ULL, 0x3FA99081FC9CD53AULL, 0x256E8EE5E3820E00ULL, 0x06E6DAA93C73B0F5ULL
        },
        {
            0x8B544EB695109126ULL, 0xBDFFCB4F5867B3B6ULL, 0x99C484954D68E192ULL, 0xF64E8F80B4014236ULL, 
            0x3DEC1C05730A1383ULL, 0xECCBA64F4BDBB18DULL, 0x35B44F8924EEE0E2ULL, 0x9584677DCCD50353ULL, 
            0xD18AB989C2910FECULL, 0xEF253D11AAFEB183ULL, 0xC6849EE902456122ULL, 0xA08DA00834C57117ULL, 
            0x2DB5A4DFA6DAD842ULL, 0x4A6BFB30A0C0A374ULL, 0xB01D3C528709CAB7ULL, 0x0FDF0855DE0562BFULL, 
            0xB90E091BEA1C6EB8ULL, 0x5156104AE4F590A6ULL, 0x041EC5C915C6E2DBULL, 0xBCAAC1B1F279BEB3ULL, 
            0x45DA9644B6DE0E4DULL, 0x2B834DF717D2A9EFULL, 0xD5DFCE35277558F9ULL, 0xCA0ED85695780C08ULL, 
            0xE09667129889E4FCULL, 0xC9B39C6EB5E91031ULL, 0x0458877BC1D9F4F0ULL, 0xD735D8224192EE6CULL, 
            0x72AEED6755794344ULL, 0x370B848823F4F1B3ULL, 0x48B4F111C033FF7BULL, 0xB82B15407621BFAFULL
        },
        {
            0x125EAC99E63F07E4ULL, 0x506EBACED94E8B81ULL, 0x6B005987BEE922EBULL, 0xF67D0BDF5C3E1E69ULL, 
            0x80D07832BCC4CE11ULL, 0x8209F1E7AF6E6F2AULL, 0xA90B93851FCAE6CDULL, 0x3D0B5CC7995919CBULL, 
            0x24C6A6CD2F68262FULL, 0x7AE68DC43F3CF76FULL, 0x7213CF6E8729E3DCULL, 0x0A4378F771004627ULL, 
            0xE9F8F0B1F55EE562ULL, 0xA51BDD28BFAA97CAULL, 0x709CA4C99411486AULL, 0x6F9A231E5DAD6EBEULL, 
            0x2A2A1042A4870AE8ULL, 0x4165961C594A25F6ULL, 0x44B521CB89DB77B2ULL, 0x98A44B312964FF2AULL, 
            0xE3ADFC59936D0E9FULL, 0xCD95F9B7C25CBD32ULL, 0x01B9E7B403C123F5ULL, 0x3496ABB07C49AA3DULL, 
            0x5A7B9AACDD4734AFULL, 0xF7E127073765E911ULL, 0xD2B748780FB8B609ULL, 0x400ABB64872253F4ULL, 
            0x9EF4358A0485DA45ULL, 0x37E3682938CC6A6DULL, 0xB19104C578F1D3C9ULL, 0xCC36C4FB34AC3F3EULL
        },
        {
            0x57853ACDA2834D3BULL, 0x3D04A3242BEAFC04ULL, 0x814BF585CB004836ULL, 0x7B3B6640A174220FULL, 
            0x4895A5328D6419FDULL, 0xFE3052646E26232AULL, 0x14C1174376EEA6D9ULL, 0xE8C313D9D468D340ULL, 
            0xCA2912CAB6BB3D81ULL, 0xA3D1835688B76FF2ULL, 0xC7D7EC1E1491D61EULL, 0xF86E44171BB26518ULL, 
            0xBEEA8AE9CD4533EEULL, 0xC2FED6507441860BULL, 0xCF5818F123F0C2A5ULL, 0x991C31EAC6761144ULL, 
            0x385CF6AAA53F7126ULL, 0x1F52FA87EFA77B4DULL, 0x1E99B866DE58508DULL, 0x8907E721E195594EULL, 
            0x1B28B10A4245DDA8ULL, 0xA67D11CBA1B14F76ULL, 0xE4C5E7754E778790ULL, 0xA00FCC9B7909B5CAULL, 
            0xD14CFCF17BE285B9ULL, 0x254212937EB3F21AULL, 0x3864AD903EC16480ULL, 0x3955F24175F0CC0FULL, 
            0x8D80D0663672EC7FULL, 0xD898E74DE655DABAULL, 0x47A24DE930E21470ULL, 0x14CC819916EEB891ULL
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
        }
    },
    {
        {
            0xF40AF24B3DFF1ECDULL, 0xCB3E8B167A6522DDULL, 0x10035C91E3E58634ULL, 0x9BCDBFE2F6FB4717ULL, 
            0x373737612BE382B9ULL, 0x9C080A017E70DE9CULL, 0x5017C63102CD666DULL, 0xC43780B4ED24AE28ULL, 
            0x4A314EF583CBF967ULL, 0x7DE6CB65DCF3CA7BULL, 0xA83869C2DD1D4E40ULL, 0x7DAB26DFCDD76FF9ULL, 
            0xFFBCE94F116138D3ULL, 0xEFFC4FBA72573D0CULL, 0xCE3D83C559318B82ULL, 0x1902BB785151FC76ULL, 
            0xD48BDFB5B8FE8E30ULL, 0xC8ADA3D2258C9738ULL, 0x8075B6DE92E0F770ULL, 0xD974023DC4748874ULL, 
            0xC74734DFE1DF708CULL, 0x9927028AAB702783ULL, 0xE6F29E5BA466719AULL, 0x070963A69672A660ULL, 
            0x8ADF1219A808DD7FULL, 0xA304A5DBD3D16CB4ULL, 0x7D167F124C991E74ULL, 0x24ECD0504AA9ED37ULL, 
            0xE547C0870C0FBCF2ULL, 0x4A417AC4531B0C4FULL, 0xF2D489DEF48BAEDEULL, 0x7805403143F19A3EULL
        },
        {
            0x3A9B8B968CBDD885ULL, 0x084DE51E11FCF8CFULL, 0xC7B75B8531652B96ULL, 0x675546AA349D5F8EULL, 
            0xA151216DFC126C77ULL, 0x2664C143C412C1FFULL, 0xBF9E43769AD0ECB2ULL, 0xB4CBB6D1D5652427ULL, 
            0x7FD99647010D396AULL, 0x54161732EFE897B0ULL, 0x51E91552E87BC7BBULL, 0x7B3B84CA50C5B0DCULL, 
            0x2D766D6F938A072CULL, 0x86798A1CF0ED5E81ULL, 0x7BBFFD777D67E01AULL, 0xACF85FE897673206ULL, 
            0x0AB21D73A00E6D41ULL, 0xA0CFB6D918D0D446ULL, 0xC06CD31CCFE1C9FAULL, 0x4E22C68DF4878EB1ULL, 
            0xAEF324460101CA0CULL, 0x654C152D4BBADAE2ULL, 0xC02C565BA6BE8A60ULL, 0xB9D798291C29A505ULL, 
            0x646250DA40D2390AULL, 0xD26E437DF4C16D7BULL, 0x0F94FFF7564BDED5ULL, 0x31B3642891C1E0AFULL, 
            0xB8C1A5653E1743AAULL, 0x66688F7F2D992240ULL, 0xD6E811C81E437865ULL, 0xDB8069767DFFF93CULL
        },
        {
            0xA2F057A04C31C108ULL, 0xE35333D86811DCCFULL, 0xF70AD6E458A9CE87ULL, 0x4ECF9E7A06D941A3ULL, 
            0x59AEE6B59C4445C9ULL, 0x5AB2F264EB19BE47ULL, 0x22B349FAF951142AULL, 0xE581E1EEF8B5217FULL, 
            0x9BDEA18015925D34ULL, 0xAE732AB9C2756F3DULL, 0x91E6711DC489CEDBULL, 0xFEFBBF891F2C593EULL, 
            0x8F5296CD7828166FULL, 0xC1BF84D746046319ULL, 0x89AE3CA5D6FA5677ULL, 0x4DC121075F49C8BCULL, 
            0x36B5690B58D55C74ULL, 0xE2B796C2678AC4B7ULL, 0x1FF4E5B622AB6BF7ULL, 0x58E2260F917CD6A5ULL, 
            0x85468286A85F2FD1ULL, 0xF260ED6063B4EFF4ULL, 0xEC68DBDB11660A47ULL, 0xA1C3B6632D50BC3DULL, 
            0xA0094D3C9E244A52ULL, 0x9306664887BB2EA3ULL, 0x465921B502210543ULL, 0xBF962B2EF7A0FBBAULL, 
            0x9B1704F679055A3BULL, 0xE9CE9736F1218930ULL, 0x38F61A33D30AE7A1ULL, 0x839DCA751A6EA46CULL
        },
        {
            0x62FD07694A917063ULL, 0xB4E6AFE4142434FCULL, 0x95B4E5F36C519633ULL, 0x5DDAD34704821D53ULL, 
            0x604F02CD3EFFBF62ULL, 0x6A5F1B599EFCAF56ULL, 0x325B56E361CF8DCEULL, 0x1EA5442E5F948415ULL, 
            0x0636F707C79D9F47ULL, 0xF38215A0CE69EFB2ULL, 0x0CED13602D9A984EULL, 0xE69E1E8B66376D1DULL, 
            0x94273E763528FB55ULL, 0x5FACAAF376E0203DULL, 0x1410BD8A1B377B34ULL, 0x41388CE3861629C3ULL, 
            0x5AEFAE8DC6FE40EAULL, 0x260FBADC26A6DC85ULL, 0xE4E79D94ABC9C803ULL, 0x317C1DF86AC1AE50ULL, 
            0xBD2729E9D8B2837FULL, 0xD9FB2B4AE7D655B7ULL, 0x5F892C4833E07D11ULL, 0x2C4B6E23AE880143ULL, 
            0x7DA80D16923C6113ULL, 0x71FCC5CF66B9010EULL, 0x3FC2F766F610646BULL, 0x9A0A237129944589ULL, 
            0xAFD61D062829AEB1ULL, 0x21E12060BDA42382ULL, 0x0BF844BAD8B43B32ULL, 0x743B3A893D656104ULL
        },
        {
            0x9FDAB595CE464BF0ULL, 0x54232B7A3360E78BULL, 0x66FFBB415425566CULL, 0xDE35110DFEA7346DULL, 
            0x5EC2C4E42BB17EFBULL, 0xAB0D781C2259D49CULL, 0xC36BB02257D23E67ULL, 0x67224BFA706A8C13ULL, 
            0xE892EDF708A6333DULL, 0x2FED2DF7CAAE277EULL, 0x91B260D6D823AFB1ULL, 0x8E23405E325945FCULL, 
            0x01A6502E7596574EULL, 0x7C68DA7BB11C4250ULL, 0x2C7553AFE196FE37ULL, 0x7260F6814AF244FFULL, 
            0x7A7A3F2D6D5AB416ULL, 0xB7D61D56BD88F6B9ULL, 0x109976C59DE2D14EULL, 0x927211374EBD1930ULL, 
            0x57E32DEBA9FE51BBULL, 0x3B00340CC921A86CULL, 0x4E51CC263CAA72F0ULL, 0x2C5F271CA7662FA7ULL, 
            0xC59F601CDF2DEFDFULL, 0x84FE9B87A8B4361FULL, 0xB5942E6186A1042FULL, 0x63D9733D9277D709ULL, 
            0x62649152B28D5838ULL, 0x9C9099048C1A6FF4ULL, 0x65C27BD4EE828A2EULL, 0x17FF515AA55232C2ULL
        },
        {
            0x830E93F44457C87AULL, 0x59528EE34E9286C1ULL, 0x872685935A4932EAULL, 0xE0A41CCF16167FC1ULL, 
            0xA21B5D26F8AFEDC9ULL, 0x9A6A7B31E6F33403ULL, 0x78F3BC6B066108AFULL, 0x04E4CF1D703B4A4BULL, 
            0x57E27CB0A05E450DULL, 0x291F89D77F8A550AULL, 0x4B3C6CD469CD5FE8ULL, 0xE144487A1269A0D5ULL, 
            0x06624A05FAE590B4ULL, 0x9FC998ED7E681DFBULL, 0x99BEEF7B323C0DA6ULL, 0xE704F988FC96CA61ULL, 
            0x22B2068F733B095AULL, 0x2359F41DD5E1736AULL, 0x1D7DCAD9345017E3ULL, 0x82A79007ABFD9238ULL, 
            0x37188C5F9AD66160ULL, 0xD6E7AD598D57A8FCULL, 0x3920BD34D538EE80ULL, 0x4C8D5D050B3159C6ULL, 
            0x1716E2CAE6321552ULL, 0xDABD7B1C7590569DULL, 0x3B9F2AC7EAD8638FULL, 0xCE63C68CBDD60A9EULL, 
            0x3480E67A78BDAC53ULL, 0xDC7833AD0E2B2552ULL, 0x5CDB604826C59BEEULL, 0xF58BD8FD57C7FAFFULL
        }
    },
    {
        {
            0xCA223B821A6839B2ULL, 0x47CBF8F586E75064ULL, 0x990EAA57E3B1C19BULL, 0xC6DEA1DD56066588ULL, 
            0x6622E9CC16015EE9ULL, 0x4535B98CB39A4232ULL, 0x58A62A79CA000100ULL, 0xCAEAEF9390FF360FULL, 
            0xADD8AFAA3DE69095ULL, 0x8F15E0DFB284A5BFULL, 0x9F74C983E9D7533CULL, 0xB58163CED79CF0BFULL, 
            0x281E3B9805F3100EULL, 0x376A9909D9AC4B2FULL, 0x0E45DADAF618978FULL, 0x5AAE3B59E1F3F237ULL, 
            0x670187770B9A9798ULL, 0x1355465A52BD3CCAULL, 0x9D43AB5F8BCD8ED0ULL, 0x81FCB2C02CCB0F00ULL, 
            0x58AF65B91B80B249ULL, 0x07B9FB57F008FFBCULL, 0x0870B961E29D8D85ULL, 0x2A3E002A8A65EFFCULL, 
            0xC5145B05DC5E10E5ULL, 0xF14ACF43C1E39D80ULL, 0x239DF427019BE56AULL, 0x56B419783DBFDF4BULL, 
            0xA6EBABE58330106AULL, 0x2C4E8EE2C70A6ED9ULL, 0xF14369E61600BD67ULL, 0x915E1B417623B812ULL
        },
        {
            0x97525A9954678295ULL, 0xACD0243A492A1F32ULL, 0xF0B056A441CD2034ULL, 0xD647B622149D28F8ULL, 
            0x0B397C51ADAD1010ULL, 0x45AAB11C138AA287ULL, 0x070A68684EE8696AULL, 0x2C5CB0C6399E1DC6ULL, 
            0xE17EC038056C747BULL, 0x29B91356F4B9DA5BULL, 0x113CF8FF3D548B7BULL, 0x70806F716374B1C3ULL, 
            0x0691D31773D37E30ULL, 0xDB3041ADBC05814FULL, 0x64F4383FB844467DULL, 0x05323D478E0CAB11ULL, 
            0x5D37F660DC1763DAULL, 0xD5C8FD2BCA4C9DD7ULL, 0x6F8D3E1C8CDDEEE7ULL, 0x4BBF55927FDC2918ULL, 
            0x63AE8D0224CB9B52ULL, 0x1FC64DC613D42C91ULL, 0x8BD60865A23C0714ULL, 0xFC6752B8BF43332DULL, 
            0x3802AEF7B2A1733BULL, 0x8A18C635AC3F5149ULL, 0x6F552563064A5A1CULL, 0x24DE72CB235CB641ULL, 
            0x22222DC59B11AE47ULL, 0x920F1D18D791A7B4ULL, 0x616E8C8806EE0988ULL, 0xFA1C641A966B7641ULL
        },
        {
            0xBE1581C0C75BFBF1ULL, 0x7E5DC7960AFA6580ULL, 0x19C24D323F5C41C5ULL, 0x29656C5E3E276CF0ULL, 
            0x1B7BFD598C4E68D7ULL, 0xFD7CDB34A4AB7949ULL, 0x803583B507B91AC9ULL, 0x8BC5539A0656A28FULL, 
            0xE0BDB167727F13C6ULL, 0x406D1976757182C6ULL, 0x67F81FD83E41A4BFULL, 0x8C9FBC9294B5B870ULL, 
            0x0B8D6340C6CA8034ULL, 0x91ECDD618E3781C2ULL, 0xBB95F9F13AE60166ULL, 0x586D9140BEE056FCULL, 
            0xBE097DF6CB11EC61ULL, 0x6A92C36B578CE0D1ULL, 0x8790BFA5D6CD89FFULL, 0xCF2292F08D4E2A98ULL, 
            0xB0175CF0BF18163AULL, 0x01DE003A060A007FULL, 0x6D9481CC3C717EBFULL, 0xF3B6A85F22363CF1ULL, 
            0x8A996624C87A6338ULL, 0x87438809D0C881FFULL, 0x47F041C1ACA03C19ULL, 0x45CBA419E4490BB4ULL, 
            0x5CF494622991BFD8ULL, 0xA3369729F9A61396ULL, 0xBBC0A9D7E9866118ULL, 0x04E387C18E6FC20DULL
        },
        {
            0x733511D3E3B12EE7ULL, 0xDF081F772526CDEBULL, 0xC5DCC5BE405F30D1ULL, 0x203994ADC1CFE191ULL, 
            0x33BE5E97F44B532AULL, 0x4B1275427F8DB7B4ULL, 0x5A0CC3837F3C4B4BULL, 0x1511457397EC9361ULL, 
            0x2B5A6B0108E0F7AEULL, 0x46755BD69D32B078ULL, 0x0C663C808F0BB6DAULL, 0x03F42CA645CCB5ECULL, 
            0x6207BCF7BADDF0F4ULL, 0x194F235DB8ED92F8ULL, 0xB8746F4AC14BE9D4ULL, 0xD3C35A2E4997D84BULL, 
            0x079880032829CEA6ULL, 0xF1CA91F053579BB4ULL, 0xBD6348E79CAD16F2ULL, 0x68469D189B9F1EE3ULL, 
            0xFA8CB124EF8FCB51ULL, 0x0420922A1F641564ULL, 0x80FDF12187683F43ULL, 0x97A90116D79C66EDULL, 
            0x7DBD0E429F43DB48ULL, 0xB69DC4FE25FEC067ULL, 0x7D810DB65125BAC7ULL, 0xB3AEC00E948AAD3DULL, 
            0xA1AF54B003B9C61DULL, 0xB3C76225E65FE7C0ULL, 0x901A01FA6C2A7E75ULL, 0xA74932AC65EC358BULL
        },
        {
            0x01F9D530C6489258ULL, 0x7BDAAC6C5F800696ULL, 0x5ADCAEC647C0316EULL, 0xC65405B5256998A9ULL, 
            0x4E581F4322192210ULL, 0xD2DBC271051B9F38ULL, 0xFDE8AF6EFD8B203EULL, 0x194D19E6EEC20934ULL, 
            0x85FFE77337579C23ULL, 0xAE1525C8D1C5ADC1ULL, 0xF4194AE58DA1C310ULL, 0x27B147D8D95D1E05ULL, 
            0x37A92E4CCDE58B5CULL, 0xAC0F4BA4F1EC43A2ULL, 0x8A479573000EF62AULL, 0x0535EDE84DD08709ULL, 
            0xA655CF40229BF3A6ULL, 0x2832C594434EB84BULL, 0xBA9F13EC7B947049ULL, 0xEE7CD7344BF9D242ULL, 
            0x3F3AE0A39A9DE976ULL, 0xD2B108662B015D9FULL, 0x1316695DE0A70E69ULL, 0x5C3BE4E1DA3F3816ULL, 
            0x9ED3B25D0FEF63D6ULL, 0xDDD6E5CFC5DD790FULL, 0x2A043800083F833AULL, 0x080361D5353AE835ULL, 
            0xFDAA3B176224B199ULL, 0x58B6768638A5F389ULL, 0x55B8BA23081C43B2ULL, 0x69C738CD867D5CCEULL
        },
        {
            0xAEDFE007D78D44D9ULL, 0x0CEB4D4914C8A7A9ULL, 0xDCB62F5ED04C3774ULL, 0x1071A327EB240088ULL, 
            0x13DCB03A872DEAC8ULL, 0x82C0E217797CECE6ULL, 0xBD1C6DDE726243B1ULL, 0x8F50AFB3036F5B52ULL, 
            0x4FD4B21CA13D1CE9ULL, 0xBD05A80AECD56B31ULL, 0x70E42A5C4C566118ULL, 0xD9058ADDBF51B9DCULL, 
            0x2367EC0794F148FDULL, 0x0B2DF1268F096BA5ULL, 0xC16A0870A05DB6FDULL, 0xD9E2C7348EBAAA92ULL, 
            0x5D14521DD9EAD609ULL, 0xB7BC4A0E04BBA9BFULL, 0xAA74DC707144A103ULL, 0xF873AE61461DF5BFULL, 
            0x359BFCF0A5AE97DBULL, 0x89F338CE45A5E597ULL, 0xE9501D1B90EFB5B5ULL, 0xE782E5E2B6C1DF99ULL, 
            0x30E415237838AF08ULL, 0x07CEB1055EC273DFULL, 0x94CE19D744A23262ULL, 0x103156EF1DAA56BBULL, 
            0xABD1A6F887C6E3C0ULL, 0x1331809D39292494ULL, 0x76C0E53E584CDFE1ULL, 0x65B18ADEC11A38F9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseEConstants = {
    0xDA65284A28817184ULL,
    0x90543AF4191D3E6DULL,
    0xCF21143B3601318FULL,
    0xDA65284A28817184ULL,
    0x90543AF4191D3E6DULL,
    0xCF21143B3601318FULL,
    0x4C3597E762807E2EULL,
    0xFFF58A10380D0C1DULL,
    0xA8,
    0xDE,
    0xAB,
    0x6D,
    0x9B,
    0xDD,
    0x7C,
    0x87
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseFSalts = {
    {
        {
            0x0AE53BFDD9DA9E30ULL, 0xF3CCD0DA28A4B06FULL, 0xCF45EA83A4885DAEULL, 0xBC8DE545E4E58B80ULL, 
            0xAAC08C9909711A9EULL, 0xD322498A08F0A730ULL, 0x7A9C5B7C93DF8A2EULL, 0x9DF3AF877A436D36ULL, 
            0xA9567680F119056AULL, 0x5F39E577C2213A6CULL, 0xDEB7E843E6475358ULL, 0x270CA527A6C27884ULL, 
            0x2A39E763B993FB2DULL, 0x65CA9D2B25C6E65DULL, 0x0F8AC5B0F9DD29ECULL, 0x3B9C4DFC1B620F22ULL, 
            0xE2836ACFA5D7B2E0ULL, 0xDAC2680B105189F9ULL, 0x460E9554CE9FE7ACULL, 0x80215465CC494946ULL, 
            0x267E2A563BD53065ULL, 0xD289CC40FABC8F0CULL, 0xE255433CA93BDD00ULL, 0xBFE843B0A27942AEULL, 
            0x87FCA5355C79E105ULL, 0x598317ADB6BAED31ULL, 0x90EE951D3378426FULL, 0x574F636268986AB9ULL, 
            0x0DFCC6FD1394BF7CULL, 0x9F39E87B511865CDULL, 0x2F99B44FA15EDF18ULL, 0x2FB5494C85152468ULL
        },
        {
            0xB37730CE44682928ULL, 0xC09001321751951FULL, 0x0B34FBDEC035977AULL, 0xA8722F5AE7CE6D0BULL, 
            0x07BF53FAF28B2AB3ULL, 0x7434C85D69208FF9ULL, 0xA53928B4AD788941ULL, 0xFF15CFEF56AE4FE2ULL, 
            0xB940024E3703B005ULL, 0xF3DC8910DBF85F38ULL, 0xA6D6621100B5A600ULL, 0x421BD31618CB3971ULL, 
            0x2CEF4A20B2D00798ULL, 0x7EF320EB2A66F570ULL, 0x48FFC9823E0D60A0ULL, 0x7156D1EEE84F503FULL, 
            0x649A9F5C54DC69A9ULL, 0x8A115A488076FBE7ULL, 0x556C652B9E4DBFFDULL, 0x1F8BCFEE7306643CULL, 
            0xEBE0EC5ABDBC8A74ULL, 0x1C58451015916E84ULL, 0x2A05223B99DB2CA5ULL, 0x21BFE57906547382ULL, 
            0x8541387F6BDA7103ULL, 0xE85474A741CEA519ULL, 0x1A5BD2C1D4180EFEULL, 0x99E6CDA43BF7B405ULL, 
            0x53730E4C7C5DF3BFULL, 0x83C5680AE3C88C0FULL, 0xA794C36B2CC305C9ULL, 0xFA4D833E332D6FF1ULL
        },
        {
            0x5BB3E82065C81EF7ULL, 0x3C04460F0C1D41F8ULL, 0x00FC1AC7B9C468B0ULL, 0xDF821328E48F86D6ULL, 
            0x84CE591D22E75F67ULL, 0x1355435B52656933ULL, 0xFBA461EAF398E105ULL, 0x112F8176C460A608ULL, 
            0x6599F7FD96652247ULL, 0x6E5A444F24E3481CULL, 0x0F2FC1CFF604135DULL, 0x64C64C3810DE570CULL, 
            0x23B3257EA0D21B86ULL, 0x9CC63673EA4F1888ULL, 0xB164D8EB7BED1B01ULL, 0x5C807E8DA7EC78FAULL, 
            0x9913D5CD9874CF46ULL, 0xAAB464743284F0AAULL, 0xD55065EB118BDC35ULL, 0x8BE2715032BF3E59ULL, 
            0x67AF289450323C50ULL, 0x0C9DE993152F93ABULL, 0x5903EE95EC5F38BDULL, 0x753D18CDF9A8CB03ULL, 
            0xF7ED0E4794F33FA9ULL, 0xAFE626213AFE4A98ULL, 0x059FCF834B80FD92ULL, 0xD6987618F64FB346ULL, 
            0x1B5030D708DCED1EULL, 0x3D4D0643277E67DBULL, 0xA248FF7AE9AB0F81ULL, 0x63976671E106EC28ULL
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
            0x1DACBAFB9DC9DAB9ULL, 0x40B0906B4A41B337ULL, 0x196CFBCEFF4ACA5AULL, 0x77496CA878CB8CDEULL, 
            0xA587877E9AB5A78CULL, 0xB4EAB3B06BDF8188ULL, 0xBFDD07D024634B09ULL, 0x1BAF4B26C60D8BC1ULL, 
            0x75FE465AB1697679ULL, 0xF544D026B9BD2A56ULL, 0x115A7160853C5AC8ULL, 0x896C231B05ACB2B5ULL, 
            0x0AB814B555402C44ULL, 0x75D50D7157BAA03FULL, 0xD99EB30422EF6A1EULL, 0x22D2900EE1CA4080ULL, 
            0x435F75858204680AULL, 0x198F465D202F5005ULL, 0xF661F2C12BCA66ADULL, 0xA856D35695EBBD48ULL, 
            0x11813B1F098A4254ULL, 0x607FA7ABA7E8DBF1ULL, 0x45EE243B2AA6471AULL, 0xDC7B05826661A435ULL, 
            0xB8DEF82F87C1C215ULL, 0x0D3AD1962087E4B9ULL, 0xD9B7C53A19A495C7ULL, 0xAC6D44D66C36C27AULL, 
            0xD1B4DE5C481FEF93ULL, 0x570141F7A28E0CC7ULL, 0xAE4799A9899404EDULL, 0x93C277EA4516AD72ULL
        },
        {
            0xA5350BCA768CC228ULL, 0xE108E9DC837BFC31ULL, 0x3251C38DFCC0E3B5ULL, 0xC19E969024413565ULL, 
            0x335ABD38DEC04934ULL, 0xEFD237F3AD4D12F8ULL, 0xF6C8C9464DD2131EULL, 0x73D1F0207D6D3CECULL, 
            0xFDBAC58076CA8D6EULL, 0xA07D9E9F7851F4C5ULL, 0x16719528606714FEULL, 0xE29625004F8ED6BDULL, 
            0x53C2CB7EF346EE18ULL, 0x4E16E455C3F61A58ULL, 0x2751B06058EE3D8AULL, 0x216F4608D7990860ULL, 
            0x87E86E29C257BDEFULL, 0xF0B4B8E01818A5A2ULL, 0xF9DBAC1640310441ULL, 0x42A2F61AE745CFD5ULL, 
            0x2905A43A6F42606CULL, 0xC1EF6D8424CC668EULL, 0x77F9B0419414774EULL, 0xEB411FF161A623A9ULL, 
            0xF653A21B99CC0C1BULL, 0x1F67E04CFBE32464ULL, 0xD9CA5B53716B084EULL, 0xF62CE7635C07F08CULL, 
            0xC5A64D742699A35FULL, 0x679415B5F82C30BDULL, 0x0A1649C9F9150F77ULL, 0x7790734FC7777A48ULL
        }
    },
    {
        {
            0xADAD2D732E34E218ULL, 0x50EAA6D12567B02AULL, 0x0F36C7152B4BDD10ULL, 0x2B3AC238F0762F43ULL, 
            0x7A0DCE3146916E2CULL, 0x7BC1EC1394FAB2D6ULL, 0xCB31204D92F93A93ULL, 0x1864D6A1A8C3C48BULL, 
            0xE9572D66721057B9ULL, 0x0CAB795ADBC9792EULL, 0x04B2A1F09FFFF825ULL, 0x85FC9C9277325258ULL, 
            0x074102096FD0C90FULL, 0x7AD37B87BFBC2EA1ULL, 0x8FE9A011CA95DE77ULL, 0x75D459A5F453AAE2ULL, 
            0x9D528CDD936D4D2CULL, 0xF89C1337145CF88FULL, 0x1940A0C53966E08FULL, 0x43EC7B8691ACFCA4ULL, 
            0x7F75F8E5AE048E89ULL, 0x6492A04006C221A7ULL, 0x0AE90D733B30ED24ULL, 0xDAF5A276ABB7FDE6ULL, 
            0x3A1D1B828C16E589ULL, 0x3F13DFBC977E0C04ULL, 0x823D115E21347FA8ULL, 0xC598953722AE3A75ULL, 
            0xEC8720AB0E816F3DULL, 0x86AB4C599AD359F5ULL, 0xFCFE20B71C2C355FULL, 0xCD757C43B0D2A004ULL
        },
        {
            0xD1FA1BB717EE168DULL, 0x99F8FB725DD58496ULL, 0x35D8C308E12CB036ULL, 0x1083C52E827A5665ULL, 
            0xB78F09F3E5990DC1ULL, 0x7280D5E52D00463FULL, 0x113B0D6C62FA411EULL, 0x31E5E0C6C07CEF89ULL, 
            0x09016AF6C299008CULL, 0x280F80F4B41D8993ULL, 0x2064B80D02B422F5ULL, 0xD2FFB86EA5E3679EULL, 
            0xA47D05D7E3A8F2EFULL, 0x3CDEB421C6DFEBBBULL, 0x96FFC58AD40F6EBFULL, 0x1F48976D5186D5D3ULL, 
            0x4B0F43E93360D70BULL, 0x5E80A82422DD601AULL, 0x7C70BE7512CD0570ULL, 0xA87CCD137208FE51ULL, 
            0x1834A47F259513B8ULL, 0xD9DEB68FDBDEC15FULL, 0xD62340EDAEF08BD0ULL, 0x304EC1404CD326C4ULL, 
            0xCB6033898CB4F0C6ULL, 0x8054C1515C878BAEULL, 0x914CFE836EDA14F3ULL, 0xC8B7CA9A0F29C3C1ULL, 
            0x69F300BC6F3D2B79ULL, 0x149F372D16E5D151ULL, 0xF8AA3B16E8BAFE7FULL, 0x1B1B43A5462A8C26ULL
        },
        {
            0x60D94F0C1A6125B4ULL, 0xC43846409F9C8CC2ULL, 0x16270AADB100F578ULL, 0x7036DB26F24E40A2ULL, 
            0xE901CBE45B5C4C4CULL, 0x93DB472BC06706B0ULL, 0x269D667E5ACB7C44ULL, 0x6B6AEAA0A59857FFULL, 
            0x2FAD297E6E7FBF22ULL, 0x27DFBFE2AEF05BEEULL, 0x4C43570E4430129CULL, 0x528135B764A056A1ULL, 
            0x192B5A43DB42DDA8ULL, 0x749DFC6636CB6D77ULL, 0x41C17F7323ED37F8ULL, 0x2FCFC5B9F04EE354ULL, 
            0x05CB0960A8589367ULL, 0x81E2AC8587C1DC49ULL, 0xB5698F062AF1BEFDULL, 0x59118B794630A368ULL, 
            0xAC3EB06BF5564FADULL, 0xFB02467EF31AC265ULL, 0xC9FDF754462D0D62ULL, 0xF7E9A0906470E339ULL, 
            0x7158662618A85BF3ULL, 0x7F67BE11D9DF3912ULL, 0xE462BA4B5D98C8D8ULL, 0xDDAA00E221B39983ULL, 
            0x753176645CE71737ULL, 0xD7580810B0AA9353ULL, 0x3B0D22A144AC4E17ULL, 0x6241DB480E682BA2ULL
        },
        {
            0x1D7D57F5DBDFEE45ULL, 0xC75214F6D3B6FD0AULL, 0x62277521A11FFDEBULL, 0x15841994F59C8F39ULL, 
            0x4E8097CB43FF1C00ULL, 0xA4771B39C439CF15ULL, 0x96E0802495FDAFE9ULL, 0xC7E75A28BE9A907DULL, 
            0x46903EAA9935F900ULL, 0xE985C5E8113DFFF7ULL, 0x2A7C1DE2CF777DB4ULL, 0xD0DFAD072C53F728ULL, 
            0x6402251C07177477ULL, 0x3B914EC392388B79ULL, 0x37115AEB5DFC3668ULL, 0xA71C704377DDC819ULL, 
            0x4BBC3B0614167A85ULL, 0xA0A63ABCB3A13506ULL, 0xC4AAA7D1E9666195ULL, 0xF26F1E00FF109BB7ULL, 
            0xBF06EE167515466EULL, 0x796151A002E7F5D6ULL, 0xB2EE372C421BCDF3ULL, 0xE2B6F353FFEC5631ULL, 
            0x428E2BA622914CA0ULL, 0x879644ACE2DAC125ULL, 0xFD9EBDACAF2454B5ULL, 0x35F3079139836CB8ULL, 
            0xC54AF15B264502F9ULL, 0x307F71054483E61EULL, 0xB551B4B89E33E603ULL, 0x3170780762C4856CULL
        },
        {
            0xA9950D97A2DF9367ULL, 0x97ACA314F3ACEB89ULL, 0x2547EC2249AA1915ULL, 0xB0D45F34AF9D4842ULL, 
            0x2CB3E3F8D1AADA36ULL, 0x1E95A62D7FE80D3AULL, 0x30A6F95EB05F6741ULL, 0x2C3B1EEE8BD012CCULL, 
            0xDFDE9D364EBF6B4DULL, 0x7AD00DBD33A90DCEULL, 0x07688850793F63DCULL, 0xE9F5833A00623172ULL, 
            0xE3206B00B4881987ULL, 0x2279C1754EA4203DULL, 0xC4B17066F58EEB66ULL, 0x8497C5410652135DULL, 
            0xF10AA5D4DDFA58ECULL, 0xEC673D0043C31A3BULL, 0x6256E8470400747EULL, 0x254BC05A4A3EC60BULL, 
            0xB821E337CC189896ULL, 0x968C49B0E5AB223FULL, 0x91F73786F382DA5DULL, 0xD739B75D81BDE0B5ULL, 
            0x00404F7A9A22FB9FULL, 0xBF4B0747DFB273D9ULL, 0xE20EA23C946CAD32ULL, 0x6E0DDDAE4BAF03D3ULL, 
            0x132017C1615AF82DULL, 0x8278F36D7F6F8F41ULL, 0xDC369D681CC271C7ULL, 0xDE27334C21D7CC2BULL
        },
        {
            0xB4C3AA0C3A2A7ACBULL, 0x32A254B824B2B177ULL, 0x5E5E7CA894EE8A98ULL, 0xCEEE9A2CA6A42A80ULL, 
            0xF69C9A11873324B4ULL, 0x29A413F7A8AAC595ULL, 0xFDBF5D9DE01F4C14ULL, 0xF6413B0D5CC59415ULL, 
            0xD9A53021357ABEA6ULL, 0xA6AA8A355503B63BULL, 0x29993ABA5245FD0DULL, 0xCE7FDAF45478F951ULL, 
            0x498BCB830166F76BULL, 0x7E0500C0568ABE66ULL, 0x99E42E2F7F51BB9CULL, 0x44653AAA17920A74ULL, 
            0x4755FF2446C8005CULL, 0x00E266324267D21BULL, 0xD57CB40744780866ULL, 0x0DFD0758E044E4FEULL, 
            0x13DCADC13188A157ULL, 0xC8F65BB3091BB19AULL, 0xADBC3087B543BD1AULL, 0xA3C4462D2AB36320ULL, 
            0x617AA2A0C53003D0ULL, 0x3F6A238DF8377EB7ULL, 0xF2ACEBA0D979893BULL, 0x23D736EFDED345F3ULL, 
            0x07ECC2C2D532EA36ULL, 0x1807AEB5B07F56F8ULL, 0x62C1C095558BB7B2ULL, 0xC147986E3ABA2BF0ULL
        }
    },
    {
        {
            0x735CF6131B95C13DULL, 0x236446C239969F0BULL, 0xF7F45BE15446A3AEULL, 0x93820215985FB1ACULL, 
            0x23E14B1C1E24D51DULL, 0xC7505B6D97983D1FULL, 0x825AF06049FB18FEULL, 0x3A9182D07CC01020ULL, 
            0x5158E7484C32847CULL, 0x59447169A9E6BD07ULL, 0x0B228020864B74FEULL, 0x13CDD0286990B0A6ULL, 
            0x9AF0C038D8FDA7C4ULL, 0xB836249925F82183ULL, 0x11E4373FF8C8BEEFULL, 0x2F1B865F49610F06ULL, 
            0x801401782CA1BD9AULL, 0x155DFFCB914A2758ULL, 0xE64D74AE500FA24FULL, 0x4A2B48E775EE3621ULL, 
            0x0B8C72E37B3F7904ULL, 0x07DE6154FC72D8C6ULL, 0x8ABAA86B662F1841ULL, 0x2E2C39789DB4B3EAULL, 
            0x8BB84014CAB1C4EFULL, 0xBD8F661AE0D9CBB7ULL, 0x644CF4A245AFB4A3ULL, 0x1ABD59EB435E01DAULL, 
            0x16D8DCB9D4809595ULL, 0x085F70C845AB62C5ULL, 0x5B118D2DBB4F92F9ULL, 0x8B9CF5BCFB22BA5EULL
        },
        {
            0xD0241B1D5A4AF0CAULL, 0xAFA0ACDFD4420ADBULL, 0x84DC63C781EE9FBBULL, 0xC5B3D904A6C29201ULL, 
            0xE5CD9B8FBD6F74D5ULL, 0xCF80E751D4182A51ULL, 0x543AFCA483899288ULL, 0x4F06075F69AA43ECULL, 
            0x5850C8A0894D1420ULL, 0x8D1E768244433651ULL, 0x142B87E0BAF29689ULL, 0x7D600BB3A4B2530AULL, 
            0x1C91576FAE465787ULL, 0xAE19938433E9F2BFULL, 0xD4BA6C3C6DEC33D1ULL, 0x2C130438778115A3ULL, 
            0xE2B5DAEC34C66009ULL, 0xE2368D09948EF6CFULL, 0xE7C570A4922876F3ULL, 0xA5A94B585331E84DULL, 
            0xC41D82B5CAC8C73BULL, 0x1F75F438A5316723ULL, 0x8A24D150426A09AAULL, 0xC5407569DBE3F75DULL, 
            0x74EF57755A422875ULL, 0xA44255E83EA5307BULL, 0xAFCD1A0AC0B82726ULL, 0x90CF51824CA5A84FULL, 
            0xAAD9401CAFAFEEC9ULL, 0x7C730E248D3D41E9ULL, 0x83270562A25C4E3CULL, 0xEF6D47B31A6AF76EULL
        },
        {
            0x6E9814E6CBF9F45EULL, 0x84F5A1FE29A4834DULL, 0x1DF3E82967CE50C7ULL, 0x936DAD2BAE51A8ADULL, 
            0x5FAAF0A1C4E9FF77ULL, 0x2BB905806FDA9325ULL, 0x2B96A8553F8B1FB5ULL, 0x85B5A4C8CF3A784EULL, 
            0x1DA5E8675860FB48ULL, 0x5ED96BA9DB450338ULL, 0x3EEAA3AACA692F82ULL, 0xA9519530919EE87FULL, 
            0x7FABD3CC85446BCFULL, 0x6599A466C5857C7DULL, 0x2ACD9220D3E995E3ULL, 0xEBF1A6D44C8A6C04ULL, 
            0x26A2F464F3090003ULL, 0xF5D5F2DDB108548AULL, 0x7726CED057164619ULL, 0xC84336CB242EE729ULL, 
            0x3986C7AD3DA9E865ULL, 0xDF38A48CF0B503C5ULL, 0x4035823DB679D006ULL, 0xC9689F1D09FE8DA0ULL, 
            0x2ADE83C0E7CBED00ULL, 0x0FA054E3C6C7004CULL, 0x37882D08E63DCC37ULL, 0xBB20AE3FCA773257ULL, 
            0x72EC158B98A717DAULL, 0x674D7E83FAC96B7DULL, 0xC47BF1C6207E3BD7ULL, 0x05404C7A9674770BULL
        },
        {
            0xE63800721692CB65ULL, 0xE930D189582565D3ULL, 0x610136FCFD938563ULL, 0x77C53CF0731DC393ULL, 
            0xD6F2F5150B9DF175ULL, 0x89127345B6920055ULL, 0x4034521AAB445D85ULL, 0xC67D12FA19A46C6CULL, 
            0xFE5A316ED35B79D6ULL, 0x185B456511A1564BULL, 0xDA95B1BC296EAB75ULL, 0xC1E493CBDEA3C5A8ULL, 
            0x5F4C15BE4ECA15BEULL, 0xAEA2C1784A1588FFULL, 0xE8685B5FCA1BC011ULL, 0xCFC436DB094CC299ULL, 
            0x37CAD9B5A71072ABULL, 0x6412808A9A2B921DULL, 0xDF0DA6F4B2D6D8D3ULL, 0x329E8F04E851E96EULL, 
            0x4785E237A3E96C90ULL, 0x75604BF1C4069DC6ULL, 0x3578C01ECFCA3A22ULL, 0x8D2569D01D28A605ULL, 
            0x7BA0E4B37F2E8F21ULL, 0x3330666E56023510ULL, 0x5801F1B9CDA048D5ULL, 0x0BAF19581E7328C1ULL, 
            0x634B56FE07C12279ULL, 0x2C34DA93A7C484CCULL, 0xC9171D6C790F6255ULL, 0x18094E44FB491516ULL
        },
        {
            0xE7B3A63E27BB6CABULL, 0xAC1C4E0941C2A328ULL, 0x8150996F0F2629C5ULL, 0x4218FD03C756968BULL, 
            0x1A13DFE7A34E0B5EULL, 0x7E31B34502754EC3ULL, 0x8B378D3AD41FF512ULL, 0x94E22855F0E2C060ULL, 
            0x1A37F929FBA29F55ULL, 0x2B0186274D339764ULL, 0xC7D91C3204BD6EFFULL, 0x1345C1F8482CB9F9ULL, 
            0xA5E933945B405E4BULL, 0x95FD03A41E9571B7ULL, 0xB9A0DB54FA573636ULL, 0xDC58F9D8BC1A4B3EULL, 
            0x7AD3ED97628EBD59ULL, 0xDB8E8242E0244C70ULL, 0xE52BF6861DF206B9ULL, 0x9DA019C2516F4DE3ULL, 
            0xDCAB1FD1F3004A33ULL, 0xA0CCE35FEB8A90F6ULL, 0x7C0F7DDD0A2730FCULL, 0xA6EF6FF748003F1DULL, 
            0x40651E667F35E960ULL, 0x0F00DC7418EEDB66ULL, 0x4BF85181D19FF66DULL, 0x0112E76FFE592C9CULL, 
            0x26CC13B495DA775EULL, 0x80B41DC02CA96B48ULL, 0xB40E8C239CA382D4ULL, 0x1FFC9F46CEACA9BEULL
        },
        {
            0x6A3A667A3215365EULL, 0x74E34F004FCCDBF1ULL, 0x5858F7E111092417ULL, 0xE23B2B18C9EFBA5FULL, 
            0xDE7710D39532B492ULL, 0xB1ADF842FCE03D31ULL, 0x0727C6B7757F1F6AULL, 0x86C18C835153E3ADULL, 
            0xD0ACAAB4836FA62DULL, 0x65BAC9CB621EF4D2ULL, 0x8A08F3FB1F1135C7ULL, 0x7C7CEA3530CDABA4ULL, 
            0xC234BBC2F58E4FB9ULL, 0x5D9F6CEDBAE5C431ULL, 0xA32D9EAEDCDC53D7ULL, 0xB9EB5FF48C5A02ABULL, 
            0x17F3468D1F4A1474ULL, 0x3699C2BC0A637A4BULL, 0x12A7B2A54036D101ULL, 0xAD100555AB75B74AULL, 
            0xDCD2E9899F5338BCULL, 0x008979A3398FFB01ULL, 0xA14477EC6E8CFBF0ULL, 0xC220739E6F63E936ULL, 
            0x3DC5D543683A419BULL, 0x434A1CB8A86039CFULL, 0x1AC8F4E0F84CA36BULL, 0x515A13CB6FF8D2B0ULL, 
            0x2E37B1CF727DAB7AULL, 0x4FFCA2A347A58E72ULL, 0x9771A01591C1AC36ULL, 0x687C7563E49A5036ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseFConstants = {
    0xDC2EC532D3A08010ULL,
    0x94635B876DABB6B9ULL,
    0x24C306986BC7DBA0ULL,
    0xDC2EC532D3A08010ULL,
    0x94635B876DABB6B9ULL,
    0x24C306986BC7DBA0ULL,
    0x4CBDAADA51CF1D95ULL,
    0xE6E143B1B2987634ULL,
    0x49,
    0x92,
    0x66,
    0x2E,
    0xAF,
    0x0C,
    0x56,
    0xBD
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseGSalts = {
    {
        {
            0xEFC7FA7CA49458A4ULL, 0x1368B07CEDE92D78ULL, 0x7F5A789ACE379066ULL, 0xDED417D7FCE50550ULL, 
            0x2A64A211FDA09679ULL, 0x50B215EB415AC945ULL, 0xD946F090CCAF474AULL, 0x10F5AD3DFC2A31D0ULL, 
            0x85CC9EAAE651C368ULL, 0xC10FCAAE04186413ULL, 0x25FBE3E95E4BE9DBULL, 0x404D7EE977D52C50ULL, 
            0x85EC6BB1F2714837ULL, 0xCC4FE5E4D780873BULL, 0x2165B903552FABA9ULL, 0x0B1582DB61EEE810ULL, 
            0xC83AA94B92A9B5C1ULL, 0x75246060881FDC25ULL, 0x1F94244BC857AFDAULL, 0x5D0D6273DB3B1AF1ULL, 
            0xCF699F4B969C64A9ULL, 0xE1DB96EADB23DA83ULL, 0xF145B0CB1634FDA4ULL, 0x01BE259D251CD669ULL, 
            0xCB0F0FB3C9DE00C1ULL, 0x3E26AEF16CBB6A28ULL, 0x14150D5C790B2344ULL, 0xB2F7EC9546948FD8ULL, 
            0xB083ED531A1B125CULL, 0x1881A56FFAB4D728ULL, 0xBBA6AA7585810F5DULL, 0xA4EF10A3E74B47EFULL
        },
        {
            0xB4012B4208FADF47ULL, 0x5351AF574419E74CULL, 0xA73472B3AE9C0D3CULL, 0x1B06EB29E055072DULL, 
            0x82CE38AA9001B00CULL, 0xEB7CFBF4CA6B8265ULL, 0xD8607D52417B2536ULL, 0x85F2BCE77F192815ULL, 
            0xF57DC38D96A8A5B3ULL, 0x17B6C7784E405226ULL, 0x32B3E336FB1894AEULL, 0xD55311274C1EC08BULL, 
            0xB76A8DF80FB59E9EULL, 0x5B105DB172833933ULL, 0x67ABFC6F9B17BDACULL, 0xD9F1662A539703B9ULL, 
            0x9E31440F414ACBA6ULL, 0x312479E01265B116ULL, 0xF0DEA2C5BCCD0ED3ULL, 0x6E0688F5D2B9549DULL, 
            0x2213463DFB5304AFULL, 0x2F38E38FEEB23794ULL, 0x91E78DD48EA24A7BULL, 0x29CB072DBDE2F893ULL, 
            0x867C04FFCA83D6F0ULL, 0x53D097C7324C5458ULL, 0xD71A372EFE1E357CULL, 0x6CE2EB7F3B1F2567ULL, 
            0x0D3D2444022362C1ULL, 0x1FD9BC523B08BF65ULL, 0xAE31AF662DA819FBULL, 0xB0113724D4358125ULL
        },
        {
            0x4624D46F8BE2FE40ULL, 0xA9EEE45FEF740827ULL, 0x798D51BD59E1A4B2ULL, 0x54ED6291D3A0DDDEULL, 
            0x6E7B7D9205D5994BULL, 0x934954B0A20115F2ULL, 0xE990C7D41F59C6D3ULL, 0x6EEB7363992780BFULL, 
            0x390AA133F6737F63ULL, 0x2B7994724BE89B87ULL, 0xB9F664A265FB478AULL, 0x3F6ED2AE528DFF4AULL, 
            0x930863B3423F0354ULL, 0x746BB3D537BB2D5EULL, 0x345CECA026C8C3CFULL, 0x49018A0AD74BFD62ULL, 
            0x8BB51B0A37821EDCULL, 0x52BEBA6B2D9CCD7DULL, 0x8B64C95C1C85819AULL, 0xC4CFFBD73377BF26ULL, 
            0xF40CAD46E9A71868ULL, 0xE84414CD9723C66AULL, 0x1F0F19B6FA746636ULL, 0xAD08974F807FB507ULL, 
            0xB44058DC831BF7D7ULL, 0x400366FADF757B00ULL, 0x1FAD061C86E69DA3ULL, 0x1EEE39BDAF48F622ULL, 
            0x02616E7B90C7092CULL, 0x93F27CC973848108ULL, 0xE650309395F95EB6ULL, 0x1B83DD82060604EBULL
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
            0xFF03C7B8D1DF8216ULL, 0x3AC9BD02E580D45FULL, 0x99C62E402B35A539ULL, 0x1CFFE07D68B0E157ULL, 
            0xF8EB1A13DCC9AF9FULL, 0x5BD214C448D8A185ULL, 0x784EE0986F6F342CULL, 0x0D4E68FFCFAA1636ULL, 
            0xA2D9B53539B6A2C7ULL, 0xAE8DB7641E07A784ULL, 0x2A48F54E1242E400ULL, 0x991B937EBDE1C5EEULL, 
            0xF1DDB808B1B5CA6EULL, 0x309B929B32090188ULL, 0x10502DEE027A8E11ULL, 0x245A4D5FF95EC34CULL, 
            0xB9D5CC88CF4D5347ULL, 0x4A58D6C21A5C08CFULL, 0xFCD70F2411C5A0BFULL, 0x1DEC34750F8E23E9ULL, 
            0x9689D5FC22CEDAF6ULL, 0xD33FE37312C8537BULL, 0x4D6B7ACB01E7E09FULL, 0x15E12907A27D88D6ULL, 
            0x0A1BFC8D6A2A23CCULL, 0xECD6327049FB8353ULL, 0xC70C17C4D666D921ULL, 0x5C6E22634CD27267ULL, 
            0x7239A9BBDCD9C177ULL, 0x7DFD143E94D32027ULL, 0xD45BE295BA10B843ULL, 0xC9BC5F3E7120DEF0ULL
        }
    },
    {
        {
            0x2F762838FBAF25E4ULL, 0xADDE90ADD9DEE80BULL, 0xD162A80BB2D50670ULL, 0x669758D06879DDB3ULL, 
            0xA275D2E33D27A455ULL, 0xA60FAB9922DA543AULL, 0xBEEE1C01A8EA1436ULL, 0x6702F37C508031DDULL, 
            0xEB4D073B225DD710ULL, 0x13AEF50F6212A353ULL, 0xAAB714854339D19CULL, 0x1388EA2FB592AED3ULL, 
            0xF1AD147059067153ULL, 0x3FF53F271AB25843ULL, 0x49CE3DF5581C3048ULL, 0xF986E6349503B883ULL, 
            0x49F92386547F9505ULL, 0x635CC5E2548D9BA1ULL, 0x921A0DC403003FD3ULL, 0xF35646EA833DF876ULL, 
            0x38C4A73194F4BB61ULL, 0x58AD4F0CD3376422ULL, 0xF79F2133606EB553ULL, 0x32B03DBB2FAABFE8ULL, 
            0xDD813D10A53043ECULL, 0xF3315A4562D55F48ULL, 0x4D2E25C60CAA20CDULL, 0x1C253B63CBDCC462ULL, 
            0x15673492AD1AFE61ULL, 0x2A10883AA3616371ULL, 0x132191D18F646D2FULL, 0x27B971D9B4CEF412ULL
        },
        {
            0xABF2B23AE4A9DB6FULL, 0x4946D7AD3EA69337ULL, 0xE6DF4E5B453D2342ULL, 0x2D27649843D6E767ULL, 
            0xA4C8328A8C21B6B0ULL, 0x3C592933C716601DULL, 0x3B7E79B2C4AE30DDULL, 0x9C6511C99DCCACD5ULL, 
            0xBD3CF79CB40CBF31ULL, 0x8BB0915BD669321BULL, 0xCF2D7B53A10D80A0ULL, 0xD3BA7C020F6654C4ULL, 
            0x413AEC90D2A4AE27ULL, 0x81CE300AECF32550ULL, 0xC4836E05424C7CCBULL, 0xE4EB8265C4687CDAULL, 
            0x9D7024AFBD73D94FULL, 0x38033A7C8235FA5CULL, 0x19FF6AA89F647DE2ULL, 0xA757604206982D5AULL, 
            0xB845ADA45B5DA0E4ULL, 0x66178C92BCAE2988ULL, 0x879B317EF56D473EULL, 0x6C28FBE37D674C26ULL, 
            0x56272636DB1D9DD0ULL, 0xC192378F87BC3CA4ULL, 0x1D2367F4CF2FD6A0ULL, 0x67D95EA15E6F534EULL, 
            0x76518FFEBE3239ADULL, 0x0A8E8581EDCCB102ULL, 0x669BF5B213588C6CULL, 0xBB8767619AE8CC6CULL
        },
        {
            0x97F86BB7C6B3B632ULL, 0x4E487141BCB88777ULL, 0xF3C0E61A58011560ULL, 0x8CCA13A48BAAD740ULL, 
            0x20A3F61A62FFD0C1ULL, 0x426CBD7306EAAF47ULL, 0xE5CC15288A1BE0CFULL, 0xE28B702A38BFC66DULL, 
            0xC89699D05A22D057ULL, 0x0D09224A661C3F8AULL, 0xA5332CCD1A0EF7C1ULL, 0x837D98C3841D8D39ULL, 
            0x79BB686B85307418ULL, 0x2C7ABDE9FCED1C5BULL, 0x1A98AA89991F6A24ULL, 0x6311972C1FF890F8ULL, 
            0xD10E04A029CB3543ULL, 0x2DE7D0AD64B91B31ULL, 0x554B9AAA54F1FA81ULL, 0xFC9974A84F5DD907ULL, 
            0x48C60E1C3237D904ULL, 0xAF5BE0BE20BBD0B2ULL, 0x5B43EF22257582CAULL, 0x574F0F84DF6A269EULL, 
            0xC0DA11289B83CE9BULL, 0x5B8CC8C28E5619DEULL, 0xB19AAC1E0F3E475AULL, 0x3F181741E0BF06A8ULL, 
            0xDB8F1509325C87B0ULL, 0xDA70F7C7F1BEF7A3ULL, 0x3ABB9888C5521027ULL, 0x5DAF92CC7E902A82ULL
        },
        {
            0xA2E734DEB389599EULL, 0x7F8743CAC10ADB9AULL, 0x4C029626F4A3D165ULL, 0xDC2CF21CBD978EAAULL, 
            0xAFF2327839A230C8ULL, 0x2D6600120B3E404AULL, 0x6F90929CD7A836EDULL, 0x023790C78BA60033ULL, 
            0x49C71227ED09FABCULL, 0x55FA79CC09461582ULL, 0x4C25DEB3667B2354ULL, 0xEFC6912B621804C5ULL, 
            0x1BDA5E8BE522155AULL, 0xEFBD78751C3CAAACULL, 0xD3622377E8F840A5ULL, 0x14A7F81DF2395708ULL, 
            0x3B34659E6BD0ADD8ULL, 0x323517F848C3D2D3ULL, 0xBFF598E249578BA3ULL, 0x85067557B1CCDF68ULL, 
            0xE8E75970FCC9FC53ULL, 0x067D3412531D32D1ULL, 0x5358A54AD475425FULL, 0xD551864BE7FAB817ULL, 
            0x0EDE8E4EDBA75D97ULL, 0xF95E12D1EC2B9C05ULL, 0x41CC06C8315B3C94ULL, 0x4C243D2013B7B8FFULL, 
            0x423D5CBFBB12E161ULL, 0x08F16216696B0E08ULL, 0x7E310A7AFB7E7BE7ULL, 0x747B8B6408A9C2E9ULL
        },
        {
            0x8D5FD8CF98DCF2DDULL, 0x13DB69827C15F94EULL, 0x1D7E88AFC47F5276ULL, 0x36BC74FDB40B7D2FULL, 
            0xA6CBDEC706DBBBAEULL, 0x3A2B9DEDB2645ECBULL, 0x36730B0BA7E747BBULL, 0x5BF0461A978971F0ULL, 
            0x60967C5D8BD71120ULL, 0x3351A5C7F8085355ULL, 0x1CDD5257A237E9F7ULL, 0xAC3DB275A1F892DFULL, 
            0x27CAD158C20EB3A0ULL, 0xDCDC37724E1A585BULL, 0x8D843D1BE012091FULL, 0xAB270889976275BDULL, 
            0xE046D3E287BCDD41ULL, 0x7B48572EE1BF434EULL, 0x9C599F26D0A862A2ULL, 0x2BFCD35F6AC954ECULL, 
            0xCC5EB81415E79F43ULL, 0xCE07A6F15470ECBEULL, 0x435BDE1BF79DD5F7ULL, 0xEF68EEA8D126269DULL, 
            0x0C989A9FAE73C4C3ULL, 0x258F77EE60E6701AULL, 0x61F7AC32AF2D6164ULL, 0xA8F633BD61498066ULL, 
            0xF501737563362B03ULL, 0xB4BE257261DE5DBBULL, 0x8A018599739C49F8ULL, 0x8D100237F3ED5E4BULL
        },
        {
            0xA6425A0F602E02A0ULL, 0x9D7C47759AB0BFE1ULL, 0x149DC65156749560ULL, 0x1AF29308F4EC423BULL, 
            0xA51A7E2C06F1DD1FULL, 0x1EAD2B119A0BC202ULL, 0x946ED0B7AF57FB8CULL, 0x4F73D2669AA67ACBULL, 
            0xF415B70B552E97B5ULL, 0x87DB37D583DF592FULL, 0xDCACAB6712722375ULL, 0xA94A8124D72907FCULL, 
            0x534C347C297C2E2BULL, 0x2C889B214FEAB5F3ULL, 0x93C6F360B4B02CE8ULL, 0xD312DD2C25B09D00ULL, 
            0x54DB5B18FEFFD5E2ULL, 0x3451ED0AD7E76212ULL, 0x0A248427F7A7DB84ULL, 0x2AEAD457A82B0CCAULL, 
            0x0FE632E485B5443CULL, 0x3D856739CE12C3A7ULL, 0x3E61E369DD7B3C3EULL, 0x753F9BF4AE020882ULL, 
            0x4DB0379BF6B9A86AULL, 0x7AC6AD59B862B876ULL, 0x396927B2095C0647ULL, 0x9AA8CCDB5ACD2ED2ULL, 
            0xAB499178606C7667ULL, 0x87F2447DC26871A8ULL, 0xF2C60C5A9E86A339ULL, 0xE6CA8C3F81C4174FULL
        }
    },
    {
        {
            0xE535377946A1EC3EULL, 0x2561EB6FA3E20E58ULL, 0x9B150759D5391627ULL, 0xA22A2A73BB172B54ULL, 
            0x68254D5D4E6EEC77ULL, 0xD374B0BC15562FC9ULL, 0x7E8B3785F325F42FULL, 0xB5600FAEA3CBB197ULL, 
            0x9C01B36D8E7252ECULL, 0xC38BE92E593C2917ULL, 0x4CD33D149923737FULL, 0xBC5FE61B7EB21DCAULL, 
            0x708242328DC6A975ULL, 0x648ED614BA772EC9ULL, 0x417EDA6637E8503FULL, 0xF17FB2C9C235E425ULL, 
            0xDA0B75F09C521B15ULL, 0x3AD3A4CA06C51EB8ULL, 0x4B53E4870163C29AULL, 0x3400B26D2B7EC0F0ULL, 
            0xEC8A20B72F9C2B49ULL, 0xCE1FBD5519D7B4E2ULL, 0xFB2666A74A3A73A0ULL, 0x8A71EC318E862813ULL, 
            0x09EEDFBFAA813F99ULL, 0x12471028A7FA3D0EULL, 0xCC49C2DF5DF66869ULL, 0x2DE5394C9C19CE26ULL, 
            0x5542C15AE19F446EULL, 0x8E92FF99896DC4A4ULL, 0x0E5EE2FD79D9B13AULL, 0x0C687F7E36BFBCA8ULL
        },
        {
            0x6C0082786873AA83ULL, 0x27E3E13B22EF5680ULL, 0xD2D949B54BE4A31BULL, 0x69DF7CDBABDE9666ULL, 
            0xBF486F6A938DEA18ULL, 0xA4981EE5417C97C4ULL, 0xD4CB70D1A9981C80ULL, 0x1ECF9472FBC891D4ULL, 
            0x187F79322619B0DDULL, 0x73ECDCDD501EE1D9ULL, 0x1E77291FFDCE53A6ULL, 0xFF86F38ADE5EBCCCULL, 
            0x0419C7A5B788FB6BULL, 0xD6D98D3D5F2EB0C3ULL, 0x8E48862237C67789ULL, 0xD9DBE6CB77B503EAULL, 
            0x869E718E8E05F043ULL, 0x7AC1A42F1BCF5092ULL, 0x0DDFD25866F8C18EULL, 0x3CC83341A2A1F38EULL, 
            0xA1649CC9B88A90CAULL, 0x3B796A77831FF275ULL, 0xF584B29239D65DADULL, 0xEF81239B7BADD7BAULL, 
            0x86EB6601C5B6BBF2ULL, 0x0BCF15694B1A0BC1ULL, 0x9BE24124FCB75A6DULL, 0x1C8906475BE85EB9ULL, 
            0xC82918A1F341C4F8ULL, 0xD130C1D075336EE6ULL, 0xBE323C1188F47C9AULL, 0x40B2287DA8EF416FULL
        },
        {
            0x347B677C013E5BA5ULL, 0x9BD0DB94C87B2AE7ULL, 0xD7A99806330BDAAFULL, 0x73F29177B15A4124ULL, 
            0xB82F1E2725C4F845ULL, 0x8E61FD8C02317880ULL, 0xAB9361D1D610B2D4ULL, 0x184B3C8316DD2744ULL, 
            0xE87F3DD18DB00C69ULL, 0x0250CB4BD4487F5DULL, 0x4FCD8BD11BDC5185ULL, 0xEA1DD42120B61391ULL, 
            0x26B05786B3AE046FULL, 0x20A04CC1B0660689ULL, 0xD4C7CBF0FEB0C9FAULL, 0x1C01B4620A531620ULL, 
            0xD64511A4B24668D3ULL, 0xAA0F57DC60EE32FEULL, 0x33140CB3C70EBC0BULL, 0x0A6341474892255AULL, 
            0x17B6C5D0172798D3ULL, 0x1841D3CE9664EE8CULL, 0xE8FC5F11A4DA8614ULL, 0x499950A0CD90AE05ULL, 
            0x983D5DDDCC6AE181ULL, 0x75162CAB27C21BE2ULL, 0xB819635C2F593D9AULL, 0xBFCDE79AF3BAF2D4ULL, 
            0xBA227CCADD28389AULL, 0xC6C19795698CC9A0ULL, 0xF729B259CF3CC343ULL, 0x285B6CCBF55F0767ULL
        },
        {
            0xCB76E418ED7F1EC5ULL, 0x095164D47970158EULL, 0xD8D741932934D48EULL, 0x56968E40D665A7CFULL, 
            0xAB6037FC1EDE9B8AULL, 0x26F3733D8393FC33ULL, 0x326BFF76760C1FBEULL, 0x2E84A582AB7DE4ECULL, 
            0xEA4073C54BD603DEULL, 0x28816E0F9CEF6DACULL, 0xFC18D737B0C6FEABULL, 0x84A0F2A8B29B0F1BULL, 
            0xEA6C3AAA7D04ECB5ULL, 0x2C624ED6702013A6ULL, 0xB3A46D6E94FE67D3ULL, 0x35504A308E4D2F0EULL, 
            0x85C212FEA47C59C6ULL, 0x558C460CF8117404ULL, 0x08FA79EA54B00BA5ULL, 0x6184394A54E8755AULL, 
            0x07823E43948CAA8EULL, 0x869089B84542E5D1ULL, 0x1A6438E9C3B05B1CULL, 0x5B57E1868B90187CULL, 
            0x96E57A4D84845CCDULL, 0x017742A7FC1ECCD6ULL, 0xCB94712017FE4BBCULL, 0xE6660F84CB8424C8ULL, 
            0x63604D2E9A84C028ULL, 0xE1FB2F570B5ACBE1ULL, 0xDCB86ED5E8B0613BULL, 0xD5AB794DA592C614ULL
        },
        {
            0xEBD711EF32C21B21ULL, 0xBA1664131FF16282ULL, 0xBBA7CA26C3664E16ULL, 0xBE34BC92A068CFFAULL, 
            0x4B4CE9139C0127CAULL, 0x091FDA7C3E7FC52BULL, 0x543C01FAC272703BULL, 0x087A4E1D02090F14ULL, 
            0xC8A307668C555B4AULL, 0x22A39C4014D6D687ULL, 0x436603BE7A7411EFULL, 0xC2F9594A87CBAD9DULL, 
            0x8EE2ADCECF0A3CD2ULL, 0x846CECEE7F191AD5ULL, 0x470E10DC7375AB88ULL, 0x5721F9F3D3112509ULL, 
            0x32CE3EB217464C1BULL, 0x5A9DD18726E65028ULL, 0x2CE3EBCB80F31BD1ULL, 0x5FD99E7DDBA306B7ULL, 
            0x39A0038E51C88FCBULL, 0x5DE6CEC60FE4AC83ULL, 0x4E6DDFB6D658B938ULL, 0xB70DA83211F7AF4FULL, 
            0xA5D4088374A8C433ULL, 0xFE371AE42399A6F7ULL, 0xAFE4BBE52731C1C3ULL, 0x2868A74F960B6B05ULL, 
            0x4FE79FD9F90C2269ULL, 0xA18883CAFD00CDA5ULL, 0x917EE3257EFB7FB8ULL, 0x3690C972AE0BA201ULL
        },
        {
            0x52D09C72961D06A9ULL, 0xD4CA5FE8E36AAE9EULL, 0x4CAA84583B0E0E8CULL, 0x6FBFB09321668F09ULL, 
            0x63C291175F867227ULL, 0x13F6CEC8409D4584ULL, 0x145D2792BBFFE9E4ULL, 0x3FC22C30B7746836ULL, 
            0x0E943CF6C7FF5A83ULL, 0x8C80A0F5D7168FA7ULL, 0x59263EBBD1445BDAULL, 0x365124262DF53C60ULL, 
            0xF031D606E52372BFULL, 0xEAFFF15F05E9D2B6ULL, 0x1ACF1CF7E2F52096ULL, 0x5BDA3EA7BADE8C5CULL, 
            0x47BFCCFE3779AFAEULL, 0x8BBDAF9ECD968DF0ULL, 0x4151F3825D86E6FEULL, 0x73EC65255D32521DULL, 
            0x199BBD78774DAAE7ULL, 0x768BF6279D2E1511ULL, 0xFB7067A1C9F8A968ULL, 0x999B896E3B3FBD79ULL, 
            0xA8B44F193698EE81ULL, 0x8452D3B742DD78B2ULL, 0x18DD423BEC3AEF9AULL, 0x681B695166702A84ULL, 
            0x9DC15678946B9543ULL, 0x1359F15FE8EF0EA7ULL, 0x694A2DCB6D58E807ULL, 0xFD3BA760505AC17FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseGConstants = {
    0x01ABCF4D7729E148ULL,
    0x8F024A2F6959E5C1ULL,
    0x2ED9AA93D61E9CFEULL,
    0x01ABCF4D7729E148ULL,
    0x8F024A2F6959E5C1ULL,
    0x2ED9AA93D61E9CFEULL,
    0xA5479403D3105EB3ULL,
    0xB774A83450FCF952ULL,
    0x66,
    0x26,
    0x61,
    0xFA,
    0x0F,
    0x72,
    0x2B,
    0x93
};

const TwistDomainSaltSet TwistExpander_Betelgeuse::kPhaseHSalts = {
    {
        {
            0x8DBAFD399FC0EFFEULL, 0x0E172F82180BB636ULL, 0x541A88C5D6A8EB0EULL, 0x789F78C8F0F7CD01ULL, 
            0x91736C1B043D807DULL, 0x88D5E64E5C005787ULL, 0x0DC127000433A808ULL, 0x444EAF9C38204037ULL, 
            0xA7B8D55AEFE5DDF7ULL, 0x0BC2A08183ED6B9EULL, 0x3DB88E0445A63666ULL, 0x61174B165949AE9AULL, 
            0x5528B30DFFA9D8A3ULL, 0x3DD0B3E9DFE4826FULL, 0xEC6989A346962527ULL, 0x04FEB9543BE543B2ULL, 
            0x6FA5B39D1FDA125DULL, 0x135FACC503BA29E1ULL, 0x6AB8A049392A1747ULL, 0xA9632350F8D5B8EAULL, 
            0x3013DD5189118524ULL, 0xAC9A53A30BE9BCF2ULL, 0x9D01819F1953F3E4ULL, 0x3AF278666F79CC4EULL, 
            0x3E5ED297CFF31521ULL, 0x9FC015CA725FE73CULL, 0x21031B5BE2E33429ULL, 0x87A529FB9B95F220ULL, 
            0x289F91AA0FE76E76ULL, 0x8B20BA8CC673670AULL, 0x45F2521FC51CD815ULL, 0x0CBE95C07241B5F0ULL
        },
        {
            0xB87D7BC52C03BC06ULL, 0xACC48FC30F21D475ULL, 0xAF0996387D94608DULL, 0xCCF0CEB2077A79A5ULL, 
            0x51B3FB273B8A26E1ULL, 0xA89A69B735946381ULL, 0x290CEF5AB9FB3994ULL, 0x85BD34FBC0C6FD18ULL, 
            0x00A88BF30D8BC51AULL, 0x2EEA406BE6820146ULL, 0x8796C4666AD86614ULL, 0x5F3DEF24BFF642C3ULL, 
            0x8F728CAED3938944ULL, 0xCE048CAFA2698A3FULL, 0xAF43ACBF9267F7C9ULL, 0x5965FD05FD19D5BCULL, 
            0x80A2923F792726EDULL, 0x3B6486EC366344BAULL, 0xA955528A7ADB8663ULL, 0x663D713A345CD243ULL, 
            0x16E707D64F265CC7ULL, 0x159EA91F62C0F227ULL, 0xF4B806DF9AD07291ULL, 0xB34206F5A5531A45ULL, 
            0x6D7E312381D21A59ULL, 0x3000B199396A3B1CULL, 0xCEC41428917684F3ULL, 0xC08D2726CB23AF4DULL, 
            0xE90CDF72E2AA4CEFULL, 0xE5D90054153C74FEULL, 0xA4DD19E69CD84FF8ULL, 0x0B8A8CD44D34EE5DULL
        },
        {
            0xAC9F00FE8E36A9A8ULL, 0x2299098AB7C028A3ULL, 0xC1885792FCCDB36BULL, 0x74630863A09A06D3ULL, 
            0xC7DD942C56FA907EULL, 0x15E91AC883ECF62EULL, 0x58D5E1E2C5D782D5ULL, 0x93045B05346E8962ULL, 
            0x43C3E9B86A83B8A1ULL, 0xB62142202B015E20ULL, 0x285771C8DD6B963CULL, 0xD841F332D95D8FF5ULL, 
            0x69EBCB5811158F49ULL, 0x520CBEB39050FF5BULL, 0x9480027BF1FA9CEBULL, 0xB079B81E22BB1013ULL, 
            0x5D0BFC1FC4B67B3EULL, 0x926FC1E87261817BULL, 0x59E3461C27FA4E74ULL, 0xFC648BB37A81E997ULL, 
            0x72830479DB373F6CULL, 0xC198484D7F8DBBAAULL, 0xCDE9F186B8AC4513ULL, 0x4D7051B5E3BAA6EEULL, 
            0x9EB6F33E7E9F1AFDULL, 0xC8A526738071B983ULL, 0x14F5A1C65E490DBBULL, 0xC659C1D7AEC75FF9ULL, 
            0x70B0B73FED540AA7ULL, 0xA9FD64CFBD508355ULL, 0x6618D93801AC3D6AULL, 0x24FD5B6FED84C6D0ULL
        },
        {
            0xE75328819D430425ULL, 0xEC9BD35C1303A831ULL, 0xA79FFB7532F8A5A0ULL, 0x37E56EA807CEBC5FULL, 
            0xB0B0CF3F678A29D3ULL, 0x016EC140CF36DC8CULL, 0x1DC5B7985D29F866ULL, 0xD1F33844098429CEULL, 
            0x48B7019FD021E12EULL, 0xAAAB73490FA704FFULL, 0xDE9E69805EB7DA3DULL, 0x45AC467BD9CC246EULL, 
            0xA6D97B0D93BED8BBULL, 0x4617F2C93EFD5433ULL, 0x6D5FE039ED470532ULL, 0x1B28F9E7745F45D3ULL, 
            0x7D1A0980968DAE64ULL, 0xBF66C8169749EE88ULL, 0x9A56D32A4FCE5C21ULL, 0xB83DEB9B78A8E4D3ULL, 
            0xBCD189F509BB39EBULL, 0x35A2892DAD9A4C3DULL, 0x0082017692E4DD94ULL, 0x49F2F1433A8158A1ULL, 
            0xACD2BEFBB7AA8B95ULL, 0x0126F8CD8D1B1638ULL, 0x85A0EB45FDA2767DULL, 0x3B05ED0CAC5AFFE4ULL, 
            0xE155F1541DD858B0ULL, 0xC298CE08173373B0ULL, 0x1EA7851A7BB6BD13ULL, 0x3D728E599000E9C0ULL
        },
        {
            0xECF1822CD08C2F7FULL, 0x1EA14C60ACAC5E01ULL, 0xAC5CB4D62D7F9F5DULL, 0xD18E97BF61232AF3ULL, 
            0xC37FFE029066D316ULL, 0xB3BE440DA568E2D0ULL, 0x1AD952D910F87AB6ULL, 0x6FB187335BE0C19DULL, 
            0xC05E2FF449C13020ULL, 0x2DB6B845077C8A49ULL, 0xFF722A17043248E2ULL, 0xBD9C05F670FC4AE4ULL, 
            0xF5DB26B7B89CDFF2ULL, 0xE7A6B14F7615088BULL, 0x91D41EB93D89EF4CULL, 0x38F251D17D50CA60ULL, 
            0x53D28D9C06BB19BDULL, 0x2EAC415B8A1D3880ULL, 0xFE1CB9DFDE4D1699ULL, 0x3A2AB0BFCE580302ULL, 
            0x743172C5FE4FA430ULL, 0xA98BE41E39B9FFD5ULL, 0x644C21EFF3DD59C5ULL, 0x0986D0118B36AC97ULL, 
            0x1E213E3E6B12F45BULL, 0x20DE78DE41E76E63ULL, 0x8C2665A2AC0488B4ULL, 0x1D223C55BDAA356FULL, 
            0xFAF4E5373067A4C5ULL, 0xBE1861B200CD0EA3ULL, 0x82CEB690FC0C7415ULL, 0xBC6EEAC9153411D4ULL
        },
        {
            0x02F2308665169E24ULL, 0xF8F10763D6456C50ULL, 0x0F5D468DAD7BCBA5ULL, 0xD5C33B82A16FCFACULL, 
            0x402267154211901EULL, 0x7DCFA5208EACC624ULL, 0x934CA02681262A22ULL, 0x9633BE74D356379AULL, 
            0xF6C22C685C7471C0ULL, 0x84A335C367E25E09ULL, 0xB84A57E961443728ULL, 0x6BFA75527D3C0713ULL, 
            0x01B50B879EF824C7ULL, 0x434F23354C57A03DULL, 0x6FAF43EF4E885FB2ULL, 0xA8487714C85415BAULL, 
            0x9E154553DD087646ULL, 0x27DEF4503BD82C1CULL, 0x09D33BA45F73F8ADULL, 0x6A7AE7D9837889FCULL, 
            0x40845E0B8854A7E5ULL, 0x4C1FD60EE01C0A69ULL, 0xE71471C988DDE6B2ULL, 0xAB36C9CB19F67580ULL, 
            0x118A519D64E71D10ULL, 0xA006498E00DFD9F8ULL, 0xB714DE75F98517EDULL, 0x4FD2243B69C20FAFULL, 
            0xAD495BFC0C3EE034ULL, 0x783A888E9898CE10ULL, 0x52ED0E42B74D0173ULL, 0x7C7C7D7A11C5FD82ULL
        }
    },
    {
        {
            0xD62E03433D3307F4ULL, 0xB3BF111684194D04ULL, 0x025E3D7606F13CF7ULL, 0xFA2CD6D0CDB80F8AULL, 
            0xCBAA21A42805C975ULL, 0x4C406629896060B7ULL, 0xCDFFF6A563DEE803ULL, 0xD5838B0F2603CE64ULL, 
            0x13097EA0D73C1A1EULL, 0xACECC4D62DB0A08BULL, 0xAC955E09AD1FD92CULL, 0x75F9C0DC3BC58C4AULL, 
            0x2F570FE190804A5CULL, 0xC621203964F0CC00ULL, 0x84A0C62A59AD045AULL, 0x1E443D4AD267BFF4ULL, 
            0xF23E649B0805FAC4ULL, 0x91E3934BA3C29FF0ULL, 0xFD58D7EB48F706EAULL, 0x0DF489A2857C6022ULL, 
            0xCB5A53146E20E3C5ULL, 0x7CD9D3FA9FA902AAULL, 0x07BE56EB2C8DE5D7ULL, 0x26C169415A474741ULL, 
            0x385D34F2F34BFF4EULL, 0x39D013BDE67D97A8ULL, 0x61AA956CB609FE68ULL, 0xBD6448D7ABA200FDULL, 
            0x5D30A370FF38AE6FULL, 0x522F19126E3FA5F0ULL, 0xEAED4152119DAF26ULL, 0x170D48B272714092ULL
        },
        {
            0xFD3D8100B9A4B22BULL, 0x2B4647FD13E77F07ULL, 0xD75E91CA4BD3AA61ULL, 0x76D3FEB99341FE5AULL, 
            0xE4F7F6057D0D2E48ULL, 0x293925C941DBDC65ULL, 0x311D46789A9967C3ULL, 0xFF569A6DBCE601CFULL, 
            0x4A05B59B68CEE690ULL, 0xF0C6D764F0D15056ULL, 0x7603E96BF7A1D4D1ULL, 0x10524FF3C5C7E148ULL, 
            0x9274CAF34CF6EF06ULL, 0xA4E289AFD3F3D207ULL, 0x364538D3321F7898ULL, 0x3EF5B815A5CCED57ULL, 
            0xA8FE027551EF1850ULL, 0x5140056D685B4696ULL, 0xC92A0C28165263BCULL, 0x38AE66FAC1C38714ULL, 
            0x5D5A7A57BCB5DA25ULL, 0xFC44C509429929AEULL, 0x2DA614F2F75F2AA6ULL, 0xCA155598C7462F99ULL, 
            0x2F5829607344F6A3ULL, 0x674394870778DF2DULL, 0x9AB359D9A6B18908ULL, 0x427D979B40B9BD14ULL, 
            0x51734C6513C69188ULL, 0x433F36DA62FCC5C4ULL, 0xED19EAC69F303171ULL, 0x32DBC2D02FFCC678ULL
        },
        {
            0xCCD9DA9416F73CC9ULL, 0x8E7152ECCA95BA2DULL, 0xEE4681D7015F42C3ULL, 0x82A1B961A0AB1B47ULL, 
            0xFA6A7C6A374E63BAULL, 0x70BE4A4B4EC19000ULL, 0x68F28AF9ED31B648ULL, 0x5B8AF4DCC7E9223AULL, 
            0x98BA7B4BEA1D614DULL, 0x40E5A9E217F31A34ULL, 0x5D8E9AC21F2E84A4ULL, 0xF83CF192977FD46EULL, 
            0xD8991D97F1FD2E53ULL, 0xE3054B82C7366871ULL, 0x96AA6DEA42F26CE5ULL, 0x6C5A282E18240040ULL, 
            0x0932942BD0329B94ULL, 0xEF5EE39AFC9BF779ULL, 0x9A118FCBAEA4A96DULL, 0xC6D14F644E17C541ULL, 
            0x5F6A0EDC74C59D9FULL, 0xD77BC615EAA8664AULL, 0x9F9C2E1CA785DA4AULL, 0x231EA7116F905B23ULL, 
            0x312857EE8A858E1DULL, 0x558D5B7A335BE295ULL, 0xA9CEDCCBBEC26F0DULL, 0x768D4CD643F4AF26ULL, 
            0x3A77ED7A9A9966F1ULL, 0x2F2AA4F5A25BB4B7ULL, 0xAF255704F9FDE8A7ULL, 0x034B4E43F3EABA88ULL
        },
        {
            0x5381483B846034B9ULL, 0xBF717CD447A57CD9ULL, 0x4B1497BEE0D4C72BULL, 0xC9211F83D0804609ULL, 
            0x2C3A6C6036DC0A79ULL, 0x3E511EA4015AF31EULL, 0x7D26B624EDAAFF10ULL, 0xE975FC458E0F9425ULL, 
            0x441F880A340FC58EULL, 0xE83C98085D53D5C4ULL, 0xA8ADB680C50C2B83ULL, 0x4AC8A95B20DA217CULL, 
            0x46AD2D47E2C5F957ULL, 0xE99538A0F8914DC4ULL, 0x9356200ACAEE6E65ULL, 0x9498D7CF7E1E6254ULL, 
            0x22FEC8236A2F5DA0ULL, 0xB353D1B975CF0E20ULL, 0xB5CCF0AEC4BEC31CULL, 0xF4463EC4EA78BA89ULL, 
            0xC42D264B39BE9F51ULL, 0x81096A93F71F300DULL, 0x71B3D1B1A7854ABEULL, 0xA2CF03701EE0D857ULL, 
            0x688AA945E9B128F9ULL, 0x62F1759AE4C62E78ULL, 0x326B68D35F67A6CBULL, 0xB6C0FF835F8B01BCULL, 
            0x27C69C187E5534D5ULL, 0xC712995F2E8F6850ULL, 0xB30BDEF0EF8BFCF6ULL, 0x92A8A609EABA163BULL
        },
        {
            0x74CAAE34E9044771ULL, 0x95BB0E452BDEE145ULL, 0xD13416A9440C94A7ULL, 0x40AF385C0526B61EULL, 
            0x9C19B83E38C14A7AULL, 0x86B6101015B5B5A9ULL, 0x75B6D824EC492672ULL, 0x5BCD63087561DF9AULL, 
            0x80FADA61285948ABULL, 0x455627E538F1CA04ULL, 0xBE998B27C6879EC4ULL, 0xDD15FED017567F35ULL, 
            0x7CEB27A3588E5940ULL, 0xA928BB4FEF9CEC6CULL, 0xB7157DCE8987B3EAULL, 0xF23D0C770D18B57FULL, 
            0x0A2ECFE727A213B2ULL, 0x4A48E359BF463D58ULL, 0x92B1CF3D068B55F4ULL, 0xAE4EF47BD31529C6ULL, 
            0x8404B2BC685DACC7ULL, 0x49334994C99A9217ULL, 0x24B8B0C2AAF48D71ULL, 0x5727003C5469B15BULL, 
            0x2B7C2F6B5B49AB85ULL, 0x716548AFABEFFD6FULL, 0x4D44CEB17711F6C4ULL, 0x78140F64FA1B6188ULL, 
            0x8ECA4DA153FC5B3FULL, 0x50518BB2AE906BD8ULL, 0xE8AB1CE4B66E4DCBULL, 0xFD7887A3841FC790ULL
        },
        {
            0x19E8B7C6D147160EULL, 0x4034DE1732A5BA6FULL, 0x57A12AEB4F83371CULL, 0x183A879D3AF24094ULL, 
            0x05310A70CCCF9134ULL, 0x00200A59365C7E81ULL, 0x2D51C87B67B3029BULL, 0x4803C523E261FB7EULL, 
            0xA5EC5D65D0DFBBBAULL, 0xBB74CB3275C75A80ULL, 0x0BB43CC56AB246C9ULL, 0x2E9725275E928438ULL, 
            0x7613B58BCE8C658BULL, 0x18C3893AD765638FULL, 0xF9DD2D20E5D5B4C0ULL, 0x71052859360E8B08ULL, 
            0x11FDF6470BAFF019ULL, 0x518CCF919A37EAF9ULL, 0x856270FEA5FA7C3AULL, 0x0085818060D80D44ULL, 
            0x01FB15479487A6A7ULL, 0x31D4727783E43F13ULL, 0xDB1472F5B621EDF4ULL, 0x66C507D0E08C644EULL, 
            0x73AA2F1BDABBD9DEULL, 0x53D08671143B4746ULL, 0x29DD199E41B94630ULL, 0x537851785506C97AULL, 
            0x8A0F400E4D9B1753ULL, 0x76BBBC49E0117A2BULL, 0x208CE00EB2BBB3E0ULL, 0x190A566AB47E76B5ULL
        }
    },
    {
        {
            0x15F3B3C471E1DDC7ULL, 0x2EC113E9ED969C18ULL, 0x649C40F0C6A739E7ULL, 0x0FFEE741AFA9806BULL, 
            0x9DD1BCA7BD3A6B51ULL, 0xC727E98F8F9B5E2EULL, 0xBDB9FEC874C2DD94ULL, 0x878A2CF0D93318E4ULL, 
            0xA735BC70B4D99036ULL, 0xAC4AA6F1EFCB9070ULL, 0xC3DF8B20A95246B3ULL, 0x4266C63F87A1BA23ULL, 
            0xE6CED2100D2806A6ULL, 0xA549FBD7CB46F8C6ULL, 0x83ACADED8023391EULL, 0x352F1FFE6AF61951ULL, 
            0xF2E071D443EF80A1ULL, 0x31BB101CFA8E3925ULL, 0x85CCE6E9691D19B4ULL, 0x81AA4D321AC75557ULL, 
            0x424A40ACF8F85DDFULL, 0x019C604B846AADA0ULL, 0x203BB69C2991671BULL, 0x6FC6F9D30AB6B150ULL, 
            0xEF7FFF32BC43200BULL, 0xAF5524CB3FACF422ULL, 0xF40A5CD3C722B9D2ULL, 0xBCEB1DDB361B745BULL, 
            0xA4F6AC1368B17694ULL, 0xAFF229FC5285CC81ULL, 0x657C570823507021ULL, 0xC27C6873F6A472F0ULL
        },
        {
            0xC946C8539D26825EULL, 0x4288CA397E2CB227ULL, 0xE033DA6F2F413566ULL, 0x6E5035CBAA3D96C9ULL, 
            0xBD0422B2F9A32891ULL, 0x49B613919F3E68FAULL, 0x00A04A79803985FEULL, 0x134B78E4C2241486ULL, 
            0x6949A9D756AF0F64ULL, 0x1EE7F7C870F53EE5ULL, 0x0F945841021604EFULL, 0x5565AE8018A7E625ULL, 
            0xB11C4F91146486A2ULL, 0xFCBB22BA0DE908FFULL, 0x66F8591A670BEB5AULL, 0x53D8C0D865A0F758ULL, 
            0x5244645404044517ULL, 0x46E1DF59DB79B331ULL, 0xAB00028A860DA8C7ULL, 0xDB1BA76B67D0B85EULL, 
            0x30498E3B25B37335ULL, 0x9954E9FBF30E1197ULL, 0xB6F147CB65CC9503ULL, 0x66A7E11DAC006B69ULL, 
            0x48D08676F3204B41ULL, 0x4BC1C9C5D7ADE951ULL, 0xECDE9FC18F058504ULL, 0x675665C6F148B1F9ULL, 
            0x8CC484C8829017E7ULL, 0x080F11E1D455811CULL, 0x54375157CA77767EULL, 0xC2CB6B7ED7D1C458ULL
        },
        {
            0xEFCF7FA74C1A5F7AULL, 0xB7F94A2B04AEC317ULL, 0x9CEA900C2D722D7EULL, 0x1F52042F865B5308ULL, 
            0x67BBE73E7D54DD3FULL, 0x83062216DD2B2F1CULL, 0x0C98740250C26887ULL, 0xDB46015BF813EE6DULL, 
            0xAE22C99491D5370CULL, 0x302EBD3D948FED94ULL, 0x1B4F1E5C309F5667ULL, 0x9B05D9D03900D194ULL, 
            0x8079939022420737ULL, 0xEB75151CC5CC9421ULL, 0x8ED21F9AF8E3F038ULL, 0x0AE7CCB7F5D2DB18ULL, 
            0xB5B0AE1D28D5FCF7ULL, 0x88A1B3E493D96B13ULL, 0x3650AB170B9AB34CULL, 0x814232296762FEADULL, 
            0xBE5D1048AC44CE11ULL, 0x968C1623F4F9EFBDULL, 0x5E9B41270C9B8A65ULL, 0xC372D844F58D1062ULL, 
            0xF4013D34553CB7CEULL, 0x986624AC7FDF58DBULL, 0x4055F4E77EB3FB0BULL, 0xD79BC6F6CC0592DBULL, 
            0xB4F9B7CF9028937AULL, 0xE3A0FBE4695601ABULL, 0x88F15296F43E1FA0ULL, 0x9673A5496220123BULL
        },
        {
            0x16E750F35652AB66ULL, 0xC1D50E8009471744ULL, 0xA56F3173309D21C3ULL, 0xB3606E88C0716F60ULL, 
            0x5D3A8432E0A07ED5ULL, 0xC19159C17E7D32C4ULL, 0x579E85E757C06893ULL, 0x45AAB4247E3C206AULL, 
            0x9507CFB1453797F6ULL, 0xD154894A36059ADEULL, 0x64189DA365D151DBULL, 0x4FEC730691467C79ULL, 
            0xD471D8F8E6B713D7ULL, 0x95B551782EDE0D27ULL, 0x8BC005FB16BC3B78ULL, 0x11D9B4FCF86C7640ULL, 
            0xBEC7AFC4B44AB1E0ULL, 0x91323F5A45635FC9ULL, 0x0F50276CA0EAC463ULL, 0x003D30D102F16AAEULL, 
            0x9372C212599BE3AEULL, 0xE56FE4CDCEDEF5DAULL, 0xB84B27663B9D4FF7ULL, 0xEB9FFB9684D49179ULL, 
            0xB970901F3EBFE35DULL, 0xFDF9CF0D4FBB1CD2ULL, 0xBDF1C4852C9AB75FULL, 0x6A724AC922889342ULL, 
            0xC7ED356E978C1727ULL, 0x30B13673F312399DULL, 0x2A04937101721E98ULL, 0x706E92550CACA5E5ULL
        },
        {
            0x27825A116A656DBFULL, 0x9D1E25A7D2D71BDBULL, 0xDFE14330F560E1D8ULL, 0x15E1B723D0520189ULL, 
            0x33D585F2F0A4E427ULL, 0xF08C97D69706F435ULL, 0x666CF31529E18AE9ULL, 0xB512A3D92FD7BB1AULL, 
            0x78D16D46BED83A1AULL, 0xBF9CFCC2033A8B54ULL, 0xA13610D1C2D6EE24ULL, 0x6A36D468A30F73F5ULL, 
            0xC02FD02328257DE9ULL, 0x2BDE1459BB522A0BULL, 0x4C3A3A6DE0BAA59AULL, 0x6B6C1725DCFB0D04ULL, 
            0xE687C212F23D5DD6ULL, 0x952DF1091AD917C3ULL, 0xDBCD40FABD221370ULL, 0xC0540CD47EF889D3ULL, 
            0x4943C1700A40E879ULL, 0x2E62D76BCDFF541DULL, 0xE53D826092559445ULL, 0xCFF11E5C6FDDFC09ULL, 
            0x8EE4A0E2C640B129ULL, 0xAF853AACAA33A4FBULL, 0x537114BCD31B32B9ULL, 0x83F11D6BBD9C1C0EULL, 
            0xA1C059CFF975304BULL, 0x1D420DEB618F6BEAULL, 0x0D405E2A66324809ULL, 0xFC1086642CCD7729ULL
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
        }
    }
};

const TwistDomainConstants TwistExpander_Betelgeuse::kPhaseHConstants = {
    0xCC94B6B4E2368C8AULL,
    0xFE84BFBD996EED8DULL,
    0x0803E19562C21DB1ULL,
    0xCC94B6B4E2368C8AULL,
    0xFE84BFBD996EED8DULL,
    0x0803E19562C21DB1ULL,
    0x00D9341E72A05A18ULL,
    0x4E0B0708EDE1F4E7ULL,
    0x22,
    0xE8,
    0x1A,
    0xEC,
    0x1D,
    0xE8,
    0x95,
    0x77
};

