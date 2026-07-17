#include "TwistExpander_Arcturus.hpp"
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

TwistExpander_Arcturus::TwistExpander_Arcturus()
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

void TwistExpander_Arcturus::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x9495AF4774E1CBCDULL; std::uint64_t aIngress = 0x9C3A42CE1AE9B873ULL; std::uint64_t aCarry = 0xD7FD582404CC5FF9ULL;

    std::uint64_t aWandererA = 0xBE8333F6C45E0F0AULL; std::uint64_t aWandererB = 0xB7B6A01C3F9140BCULL; std::uint64_t aWandererC = 0xCE1E1A333392598CULL; std::uint64_t aWandererD = 0xD2466C0CA32D865EULL;
    std::uint64_t aWandererE = 0xC8B2231C1139AFD6ULL; std::uint64_t aWandererF = 0xC7D3F1AC9F98FF1EULL; std::uint64_t aWandererG = 0xFA3B49B94EB836EAULL; std::uint64_t aWandererH = 0x8FC10C7A01EB3929ULL;
    std::uint64_t aWandererI = 0x98ABA50D3AD31914ULL; std::uint64_t aWandererJ = 0xD1B92C29F7DE73E2ULL; std::uint64_t aWandererK = 0xD4D1975D57E69667ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16725350037177992518U;
        aCarry = 17597201198539179388U;
        aWandererA = 18245387301779711672U;
        aWandererB = 17951090423571293164U;
        aWandererC = 11539895004028617596U;
        aWandererD = 11546165186029292565U;
        aWandererE = 12377943338914703816U;
        aWandererF = 16737795052047889983U;
        aWandererG = 9363774936081722828U;
        aWandererH = 9276008736268828690U;
        aWandererI = 15924413839043171478U;
        aWandererJ = 12000881537648884336U;
        aWandererK = 13129732326029847034U;
    TwistExpander_Arcturus_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Arcturus::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0x84A200052D9B611EULL; std::uint64_t aIngress = 0x872DE46E82739390ULL; std::uint64_t aCarry = 0xF5C850B1F9BB1FB1ULL;

    std::uint64_t aWandererA = 0x8D59E1E8509D114AULL; std::uint64_t aWandererB = 0xE7B5E12BFD97C446ULL; std::uint64_t aWandererC = 0xEB58633C68C1E35CULL; std::uint64_t aWandererD = 0xF7BF3863E39D33FEULL;
    std::uint64_t aWandererE = 0xD9255A40C550CBEEULL; std::uint64_t aWandererF = 0xB7D6B0EDD8C0ACE5ULL; std::uint64_t aWandererG = 0x98024543D1F227AAULL; std::uint64_t aWandererH = 0xEBA0F0490D4DC389ULL;
    std::uint64_t aWandererI = 0x8B406C2C8A2F00B3ULL; std::uint64_t aWandererJ = 0xA78C71544DCB7950ULL; std::uint64_t aWandererK = 0xE72C59FC5EFD802AULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 13345995245289264562U;
        aCarry = 10088564206615778242U;
        aWandererA = 11792122541918986135U;
        aWandererB = 13305881511831279877U;
        aWandererC = 14686244451618681842U;
        aWandererD = 13708383711530231977U;
        aWandererE = 11845871927632454068U;
        aWandererF = 13637786540936808879U;
        aWandererG = 17257639656878414223U;
        aWandererH = 10393224028330407724U;
        aWandererI = 11231209097327425749U;
        aWandererJ = 15440988111045862928U;
        aWandererK = 18071039378337358212U;
    TwistExpander_Arcturus_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Arcturus::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xE81CBF21C1CB66BEULL;
    std::uint64_t aIngress = 0xBE6747AD94857032ULL;
    std::uint64_t aCarry = 0x88649673E4AF2A59ULL;

    std::uint64_t aWandererA = 0x81E6993FFE84304EULL;
    std::uint64_t aWandererB = 0xD12DF941135B72BEULL;
    std::uint64_t aWandererC = 0x84D77278EA298789ULL;
    std::uint64_t aWandererD = 0xD7A006E48513AA8DULL;
    std::uint64_t aWandererE = 0x8C7813E3477AA3D8ULL;
    std::uint64_t aWandererF = 0xBE9583D806F82E72ULL;
    std::uint64_t aWandererG = 0x9F6190EA02EC1486ULL;
    std::uint64_t aWandererH = 0xF7BE0F2911844262ULL;
    std::uint64_t aWandererI = 0x8491A8DF77F228F0ULL;
    std::uint64_t aWandererJ = 0x99314DB8419A73A2ULL;
    std::uint64_t aWandererK = 0xBB49BD926CD19267ULL;

    // [seed]
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
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
    TwistExpander_Arcturus_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Arcturus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 10 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1851 / 1984 (93.30%)
// Total distance from earlier candidates: 16701
void TwistExpander_Arcturus::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 101U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 664U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1098U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1968U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 50U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1902U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 639U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1167U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1456U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 684U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1724U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1841U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1885U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1815U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1371U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 620U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 490U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 326U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 256U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 723U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1444U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 891U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1054U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 711U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 2019U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1215U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1786U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 258U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1982U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1850U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 930U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 488U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1123U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1243U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 34U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1637U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 99U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1577U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2004U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1479U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 51U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1331U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 925U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 154U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1917U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 333U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 748U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1816U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 83U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1734U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1771U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1117U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1903U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 622U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1038U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 743U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1730U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1177U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1498U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 561U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1708U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1415U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 313U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 959U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 648U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 90U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1045U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1195U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1406U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1199U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 973U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 918U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1370U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 788U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 646U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 708U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 296U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 13U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 605U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 540U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1466U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1202U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 645U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 519U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 180U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 678U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1289U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1134U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 654U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 875U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 629U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 425U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1735U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 148U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 737U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2027U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1431U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 591U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1409U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1183U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 632U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 232U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 124U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1471U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 160U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 963U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1527U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1950U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 282U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1362U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 371U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1428U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 728U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 701U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 933U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 638U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1610U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 150U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1667U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1440U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1325U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 582U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 389U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 894U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1548U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1818U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 426U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 889U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Arcturus::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xF2DA1B1233B425FFULL; std::uint64_t aIngress = 0xE95E247B720C1D54ULL; std::uint64_t aCarry = 0xBB522D8594ADB0B5ULL;

    std::uint64_t aWandererA = 0xB3D83D52C0085959ULL; std::uint64_t aWandererB = 0xE8C0685BD6AA911BULL; std::uint64_t aWandererC = 0xB86ADBE0245202D8ULL; std::uint64_t aWandererD = 0x9BD647B28795D002ULL;
    std::uint64_t aWandererE = 0xC8F55EB87EBF20DBULL; std::uint64_t aWandererF = 0xC990940AE9EA68F3ULL; std::uint64_t aWandererG = 0xC93616902A49F0F8ULL; std::uint64_t aWandererH = 0x8F3EF0E2A49673F4ULL;
    std::uint64_t aWandererI = 0xEE423157EDE6FE25ULL; std::uint64_t aWandererJ = 0xEB21C07C45770BE4ULL; std::uint64_t aWandererK = 0xF5F7F14BA4219849ULL;

    // [seed]
        aPrevious = 12113212909632904838U;
        aCarry = 16748827056683185209U;
        aWandererA = 17564542632522999722U;
        aWandererB = 12727511504246903253U;
        aWandererC = 17976492644355079757U;
        aWandererD = 12434451132385610966U;
        aWandererE = 17972131564676114176U;
        aWandererF = 12410572527053778303U;
        aWandererG = 16122850688976969169U;
        aWandererH = 10482502021375177093U;
        aWandererI = 16045692852917312575U;
        aWandererJ = 14824147520347571208U;
        aWandererK = 16058699486434298070U;
    TwistExpander_Arcturus_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Arcturus_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Arcturus_Arx::Twist_G(pWorkSpace,
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
        TwistSquash::SquashA(aWorkLaneA, aWorkLaneB, aWorkLaneC, aWorkLaneD, pDestination);
    TwistExpander_Arcturus_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Arcturus_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 10 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 5004; nearest pair: 494 / 674
void TwistExpander_Arcturus::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2622U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5147U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 770U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3306U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2483U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 8129U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5086U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 5275U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7210U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6553U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7064U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6392U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2207U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2630U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3429U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 985U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 999U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1561U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 250U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 90U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 231U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1972U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 176U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1729U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1991U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1640U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 403U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1216U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1915U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1643U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1577U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 743U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1100U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 842U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 787U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1433U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 10 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 4986; nearest pair: 516 / 674
void TwistExpander_Arcturus::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7563U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4797U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3039U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 7810U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7884U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7029U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7628U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6498U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1815U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 6970U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 2874U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6407U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2321U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1195U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3578U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6044U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 218U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1020U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 830U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 467U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1048U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 27U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 472U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 795U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1240U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1214U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 915U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1627U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 583U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1490U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 82U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1411U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 459U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 29U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 170U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1040U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseASalts = {
    {
        {
            0x5B729C744B7D7647ULL, 0xF648D9E37059B109ULL, 0x08A88D294108BFFAULL, 0xA52DA27A362B74C8ULL, 
            0x15C3552302D333A7ULL, 0x28BD71E17FD0A74CULL, 0xB45DFC6C1FD4D42EULL, 0x8C3D2DAD7F794673ULL, 
            0xC90B178834B131C0ULL, 0xB5D5C0F944AAB72BULL, 0x98B071FD408C55DCULL, 0x7B8A69F6FE8B6E6AULL, 
            0xCB3443FA76770223ULL, 0xD63A130705A5861AULL, 0x26B5D996D07BB37EULL, 0xD0D2824A4D4E4397ULL, 
            0x6D62525943C7735BULL, 0xD8AA04001BC9F730ULL, 0x92EB562544FEE550ULL, 0x79AF8DAB0A132B3CULL, 
            0xE7C77DF685EA111EULL, 0xB7C1597C8F91EB5FULL, 0x86DE2F61298621E6ULL, 0x9A46260D6D93D2E9ULL, 
            0xB285F394EE1F76FBULL, 0xE6B5A268E12D0712ULL, 0xE80E54DCF8F89051ULL, 0x0F4BC5CED39E3E79ULL, 
            0x0FDE65DF36FB8EDFULL, 0x6267158230937741ULL, 0xCFBCF5FC81616402ULL, 0xCB34D92FBA21CC82ULL
        },
        {
            0x64B70EE19E9244A2ULL, 0x83316CCEA0E2DBA0ULL, 0x05796916EB753467ULL, 0xA26A854C35016147ULL, 
            0xECBB7A9E0C24FB13ULL, 0x2059773310D8758BULL, 0x37769F3300716EB1ULL, 0x1CCEE8429FA234EBULL, 
            0x0E6A16F221C2807EULL, 0xE67A9CC826272045ULL, 0x27D4A6D95A337019ULL, 0x61850DFC2B60AADFULL, 
            0x4D51D6CA0354BE4FULL, 0x72454B34662015CBULL, 0x1423F209EC7BB600ULL, 0xF9826006F3C565CBULL, 
            0x2F4A25AC236261D5ULL, 0x70D5B4737EE61C0BULL, 0x08E2BA31FCFB037DULL, 0x7EB2D416A544DC6AULL, 
            0xF689BC88AFFC3A98ULL, 0x78D061E0FCB59A15ULL, 0xB9C6DB75EE5FC97FULL, 0x43E5DAA413C470DCULL, 
            0xD3EB1CBD2B8B8900ULL, 0x15749A7AA971C2F8ULL, 0x173A6CEB8B8C239AULL, 0xC521E61C525B9190ULL, 
            0x27CEE718B19898FBULL, 0x4A95AF00C5A6B9DFULL, 0x0459A85AC8D12DC3ULL, 0x11DA9FEB0A982AD2ULL
        },
        {
            0x39DE7B9820987712ULL, 0x2B9C5DB31BCDB5D3ULL, 0x7C85E30362BE453DULL, 0x061E648F378458CEULL, 
            0xF213E55FD8D36A78ULL, 0x90BCA01EF6F777C3ULL, 0xAD8793F8D184CE32ULL, 0x3DF460806B8C710CULL, 
            0x720BAE33B542424FULL, 0x3E5896C155AD94A8ULL, 0x60EA0D8C031AA0DDULL, 0x3F380F49E940C295ULL, 
            0xC012E86CD6E5BFBBULL, 0xD3FAB2739EF3EDB0ULL, 0xE09CE351E79E6154ULL, 0x2167B1717211ED73ULL, 
            0x8DA6A46D8D38BD45ULL, 0x4B6949246967A808ULL, 0x75845E03888E5D66ULL, 0x02CA970E37F7840FULL, 
            0x99FDB8C34C540431ULL, 0x207515F0A456E2B9ULL, 0x0ECF8F77CEBA1FB1ULL, 0x995F0179DEA03831ULL, 
            0xDA97EEE1AA90D4F3ULL, 0x5B451F753755CE52ULL, 0xD33AB5D0750520BCULL, 0xC5B37A25C782E64EULL, 
            0xA7DE3B7A84B0FCB6ULL, 0x8CAC27FED8200D75ULL, 0x883D0BF8193B85A3ULL, 0xC3E55FA09ED31E58ULL
        },
        {
            0x25342D23E48AA4C8ULL, 0x9C3E47220E22B4AEULL, 0x686FAF16B0E1DB70ULL, 0x6EBFF5DD35CDEF96ULL, 
            0x6A331BB2E758E944ULL, 0x0576C0AA858D0311ULL, 0x045C8C1080E127CBULL, 0xDEC5A4DD0ABCE19FULL, 
            0xACA1311F71AD35D4ULL, 0x6D80569A8894AA92ULL, 0x2DB7F0154F401124ULL, 0xFA7DCDFB075462CBULL, 
            0x2FF5B5A9DB83CF46ULL, 0xDBAF356E77DFBDCFULL, 0x3462348FA41DE07CULL, 0xCC2DFEE403E706CAULL, 
            0x454E7DF3C52164A2ULL, 0xA9D22184FC605EC9ULL, 0x59F13B5C4889BEBBULL, 0x47D4413F17041C47ULL, 
            0xCC16FBD891618EC7ULL, 0xE04D6D95D2AA6289ULL, 0x8FAFE16479240211ULL, 0xE12A8097424EA577ULL, 
            0x92CB5D2870F526C6ULL, 0x9E5CDB97C7C5A553ULL, 0xF61ECA33EFB30237ULL, 0x745902A12E4BD9DFULL, 
            0x747E94635FBDCA35ULL, 0xCE68E5961DB69996ULL, 0x73AEF848D7007F5DULL, 0x14801FB2B957FAD5ULL
        },
        {
            0x8782CE9C9FA94F80ULL, 0xBD63A1CD3F4B73E7ULL, 0x841C7A6BB5D9C82DULL, 0xE1353BD32EFE2E34ULL, 
            0xB7FB0CF8A6601B50ULL, 0xD976B59E68FD6B00ULL, 0x474D6C4A7E0AEC0AULL, 0xC46D7A4E2EF87989ULL, 
            0x205892A5B1AD23D0ULL, 0x4EBE165B9F4C89C9ULL, 0xD4916C4F3D3BD608ULL, 0x78DA18B91E966323ULL, 
            0x01DF3A3376CC536EULL, 0xBB50CFE68C0590B1ULL, 0xC1F36650CD96B620ULL, 0xD2B29AD4323A73FDULL, 
            0xA8320E9A606A10EAULL, 0xFA4E3F2CD7F2ECDEULL, 0x1F8182ACF9946531ULL, 0x32A4FC9A7676D320ULL, 
            0x7C1CE9FB22E74BB6ULL, 0xB4BA146E976F1E25ULL, 0xD106964F72CF31BEULL, 0xB53A77BD807DF360ULL, 
            0x27AC547CDA0B9AC3ULL, 0x69F7BDBECC4E406AULL, 0x538F321DA77A1096ULL, 0x33D68E0058B93BBBULL, 
            0x7DB7A9CB08EDAE66ULL, 0x08A8243864C31D55ULL, 0x941489FF3A6208CBULL, 0xDE90FCFD273C2CD2ULL
        },
        {
            0xA77C2C8D6D91484CULL, 0x3ABA59B74DA152A0ULL, 0x06694D32994AA185ULL, 0x7E92301957FB6486ULL, 
            0x26542934D67801B9ULL, 0xE0B74F59B15EF9C2ULL, 0x7832ACC6258E8EFBULL, 0xA590286899CFFC31ULL, 
            0x6425F6CD675BB393ULL, 0x0738605E8B110652ULL, 0x289F43DD1DC68509ULL, 0x288128C3F9B4610DULL, 
            0xA699E95F0240362FULL, 0xA90020AF76E1559DULL, 0x299C7BDBE3A6A45FULL, 0xAA04E36EC42A2D24ULL, 
            0x67B5D8F3E390DB10ULL, 0x644490FCE2717C82ULL, 0xA89D81CC9C17FADFULL, 0x0A26796866335774ULL, 
            0x185BBFD486DCC6F9ULL, 0x2FF08B05A4186547ULL, 0x75DA82D2C45B1C9CULL, 0x5590B759B2DE7EF0ULL, 
            0x4B8EA0BCDC2CE4ECULL, 0xECFCC3411860A581ULL, 0xE7F252EBCA9E3CBDULL, 0x3F7D133D21B80819ULL, 
            0xC20DC84DA2EA293DULL, 0xE80DD9AACEB64DA5ULL, 0xA5E3B180E50AAEBDULL, 0xA07A7B5D84F5B5FDULL
        }
    },
    {
        {
            0xC4CE46AC13482AD2ULL, 0xECA56B9E556D2E2BULL, 0xF6BC9A3C9E5770BCULL, 0xA129D480AC60F79AULL, 
            0x8015A29DC26FDC41ULL, 0xA203775F89F37367ULL, 0xD4BABBFB9F6F00AAULL, 0x2AB048FB019F38B4ULL, 
            0x7D75FB8846CE827CULL, 0xCD7588D13BCBC868ULL, 0x9753425EF6457AADULL, 0x72F7B586D355C015ULL, 
            0x3F513248D3B9D6D6ULL, 0xD9C145702B35FF4BULL, 0x69DFD25AA54C2699ULL, 0x885A0171B58557C2ULL, 
            0x43B6375EB88E0506ULL, 0x43771966C8774A69ULL, 0x224B388F9DDB03B0ULL, 0xB4236EDB56AFB1B7ULL, 
            0x158D6D142EE25390ULL, 0x8A647F44671D5C9BULL, 0xFA95573AF882C551ULL, 0xDAC5B469E465151AULL, 
            0xB20E710F2739A0B8ULL, 0x6479109301094AA0ULL, 0xB44B8092339E8386ULL, 0xEF434C8CEFC875F1ULL, 
            0x2F87A38A70445C33ULL, 0xA28384AC39325F22ULL, 0x9B2CF6FE34AA9598ULL, 0x546E60238166F729ULL
        },
        {
            0xB58C33B7F1416B4AULL, 0xCAC68E345BBB4476ULL, 0x8B0699F6ED4B7E68ULL, 0x4480DF21034516D1ULL, 
            0xA8C400FF4F0C5B86ULL, 0x11443C3E48CF21D5ULL, 0xD4747CC0ED3083DFULL, 0x5DC98DFAE95517CAULL, 
            0xD640351AC612CFCAULL, 0x06E592779B99E695ULL, 0xD68F6090993AF3EEULL, 0x5C4231B03727021DULL, 
            0x83E030E3C1727A0DULL, 0x8216C4573E16190CULL, 0xBF19372DCC8B6257ULL, 0xAC06E1AA5B713E24ULL, 
            0x68B86309C7B8C1A9ULL, 0x96AE556FE803B848ULL, 0xB82CAFA2EF4AB4F0ULL, 0x868A42F6FA45812CULL, 
            0x474AEEA79786F0A1ULL, 0x6F63797726237660ULL, 0xE56517B3A4079F83ULL, 0x5A86D724FD0BF77BULL, 
            0x1765E894BD558C4EULL, 0x766EB7E2A94A0642ULL, 0x31F47177C10D51BCULL, 0xB8FED60EE5D1F012ULL, 
            0xB0D4A870C2AA61E9ULL, 0x1D9E74DB3D7FDED2ULL, 0x8D575AFE5C7AE237ULL, 0x7DA25C71069DF867ULL
        },
        {
            0xF4DB8E8238B6F6A4ULL, 0xAE28C151BC5912D1ULL, 0x72BE65E632CA9BBDULL, 0x93742B880E0AEA0DULL, 
            0x73D137B6BD9D8715ULL, 0xCBEE5AD1D1D2AAECULL, 0x77C43ACB2BD2DA52ULL, 0x361A1EBA50C19A1CULL, 
            0x8DB0A877B3B2129BULL, 0xD9956A089195364CULL, 0xF63F4235E538CD75ULL, 0xE1FA7D4BFDFA4A92ULL, 
            0x919CA421A139CAB1ULL, 0xCCC839A27DDE9A71ULL, 0xD9380A191AE365F4ULL, 0x7801CAC17D126755ULL, 
            0x1D8563157D31E1CCULL, 0x3BFBFA32EC8C90A2ULL, 0xD3FC138C4D3D3B5CULL, 0xC2E057A5E6BC9564ULL, 
            0x4CA27E8D873B8872ULL, 0x5C1B17E300A4FFC2ULL, 0xEBF7AB73DE5E03E5ULL, 0x1309855F89143FBAULL, 
            0x201EA153BA63780DULL, 0x2FB0E7AAEFBA4B94ULL, 0x6F351473086CB659ULL, 0x7BE52FCD942451D3ULL, 
            0x10D09A685439B851ULL, 0x9C895AB8CC4D7951ULL, 0xF42BFEBF421BE102ULL, 0x2409E023EDE8423FULL
        },
        {
            0x3026C629944ACB5BULL, 0xE6D629DA1B55106DULL, 0x9D136C7511C04C9BULL, 0xF91A3B171428E2A4ULL, 
            0xFD4F2B12D2AE5135ULL, 0x9D251BF104CB7372ULL, 0x014A1DEFEC82CFD8ULL, 0xC38771FC17D92B04ULL, 
            0x99DDE955BC24A9ACULL, 0x5517A825243E9C19ULL, 0xB73CA807023BFDC9ULL, 0x239821E01A9E7A07ULL, 
            0x04169B08CA9BAB62ULL, 0x0468AF7A935A9EB5ULL, 0xAE7B716899E62A59ULL, 0x68FCB8BA321937EFULL, 
            0x2589DDC98EDB5313ULL, 0xB6C6055C2154058DULL, 0x859C0498CCF092BDULL, 0x705F1A2118567858ULL, 
            0x928623CFD38B7300ULL, 0xB58A1258A8AB9E7CULL, 0xD44C56C0C79F3132ULL, 0x5BBA41FAF6250A5EULL, 
            0xA080C75D7A0AEE77ULL, 0xAD4249B3BAC24E9DULL, 0x1A5E83419E950A5AULL, 0xB81F1D83FF757DFBULL, 
            0xE1C420DFB61BC741ULL, 0xC9125B683C09751FULL, 0x78F17DB2283795A1ULL, 0xA695F54FF87DC473ULL
        },
        {
            0x28F4B72EA701415BULL, 0xF7418A975757FC5BULL, 0x26245FF3C99891E1ULL, 0x3E58C468EF606556ULL, 
            0x4A8C68859F7276B7ULL, 0x3CA4CB1F5DA860C9ULL, 0xE54412B54C6FB9F7ULL, 0x115609143459C99AULL, 
            0x90B2836F0E57A3DDULL, 0xF89A3FA15B5848F7ULL, 0xE02F1EBE06AF5E9BULL, 0xD3A5681FE7AB63CEULL, 
            0x8F38FD958B6EBBFEULL, 0xD81D831A525D1C0BULL, 0xCD200E9FD58B2E43ULL, 0x95545CD83A53CF7CULL, 
            0x648DFB3EEF568505ULL, 0x7CB6FB7263C69151ULL, 0x18E5E23CB49102EEULL, 0x239D394699F326F1ULL, 
            0xFF5B5B704BAFBCBAULL, 0xFBDEBF69C46AFA48ULL, 0x67B488B5452191BFULL, 0x8F184B1B5D4CA7C5ULL, 
            0xA81AFB24F57DD8A4ULL, 0xC6441FC7CD0851E4ULL, 0x7D148D9E32C7EE1AULL, 0x5BD93FAA84BCF164ULL, 
            0xEC00FF72EA0957DAULL, 0x525DED39CA0A6B2CULL, 0x4055A806D44AE96DULL, 0xBE6E101E331214ABULL
        },
        {
            0x4AE993B5F55BFC23ULL, 0xA1040E0C8E802B23ULL, 0x69A460434068B19AULL, 0xDA2239DAD9948207ULL, 
            0x5B9A3707F77E4D91ULL, 0x8AB467547E66970DULL, 0xC188FA61F5FD9F67ULL, 0x9A71A108DB9940F5ULL, 
            0x8217F76A9ED33938ULL, 0x4BADFB4DEE0C9C22ULL, 0x89CA40C62C50FC6CULL, 0x072BE8F4A42DCDDBULL, 
            0x9865DFFA3B711EF1ULL, 0x86D3338EC5B0C81CULL, 0xF7756F16B5D1B192ULL, 0x9358EC74B1D29346ULL, 
            0xDBD4FDD9AFBA3EF9ULL, 0x7BC034DD58FC2AB2ULL, 0x75537F7DBB98A1C3ULL, 0x55A7F6F0A51470B3ULL, 
            0x3888BD3592C1A0A2ULL, 0xA80779F0690946FCULL, 0x62BB23F7EC1F1F1BULL, 0xA8DEC96F4ADB5F56ULL, 
            0x70B5894A975049BEULL, 0xF6521F9388F17978ULL, 0xD3990852147C75BDULL, 0x7C5CB19E58F59180ULL, 
            0xBDEC60EC974C845DULL, 0x14129CCAB30319C0ULL, 0x14173857EE7887DAULL, 0x511B67D91155F804ULL
        }
    },
    {
        {
            0xCF76D80C7F4B214AULL, 0xE6548B7FD2248369ULL, 0x092C901CDB12D822ULL, 0x18264D4737479542ULL, 
            0x6415B7DE703360A5ULL, 0x636E165FB170E896ULL, 0x474483200CA55DA0ULL, 0x8C12747D1331D1A1ULL, 
            0xE7AB0BA5D3B7E9A7ULL, 0xFA0AF3C676D1D290ULL, 0x4558853ED187FFFDULL, 0xD5558C528031B571ULL, 
            0x34C88D3D179A788BULL, 0x8CE5F70FE37CE9C4ULL, 0x450E429D8254881CULL, 0x30E7273C259B4562ULL, 
            0x9B1766C8DD1A390DULL, 0x7B2951907F7A5973ULL, 0x0885B500B279FC9AULL, 0xF80F57FC4F0E5E43ULL, 
            0x28DCBB31579A7723ULL, 0xF7CFDB72054E0B0CULL, 0x311AA6CB810D5CB3ULL, 0x3E5E5BC4F724C9EEULL, 
            0x760F1FE513C62F8CULL, 0x1D7FB4B040265FFDULL, 0x6B0B679A3F84494EULL, 0x5F130E93649C67EFULL, 
            0xBA2743A5EF518DC3ULL, 0x6F5AE1BFC7F7EC84ULL, 0x198BDB2E88DCD4B7ULL, 0x20C30B5FD7C004CCULL
        },
        {
            0xB7EB59B179B2739FULL, 0x09935CB3D44E8C9DULL, 0x93E5747E068EF05EULL, 0x45B9FBF2180EB553ULL, 
            0x55EFDE69FB5F1255ULL, 0x42C1CE346E38AA8FULL, 0x72BD1CD7DEDFEE74ULL, 0xF39F793F457783B0ULL, 
            0x8A65890B7245B340ULL, 0x7926D129DD0280C6ULL, 0x3FD6108985EE2034ULL, 0xFCE01111EB201273ULL, 
            0x5D3DB71F903FB4F0ULL, 0x42D8FA50836387ACULL, 0x2B2810F39B5E16A7ULL, 0xE303B8E0880EC2BFULL, 
            0x4D5E614F0903877BULL, 0xD3BA709690FD93D0ULL, 0x03C499DBE93253DFULL, 0x1839C479850C103AULL, 
            0x05BF23142F6158B7ULL, 0x6E15C87B49C3A3BFULL, 0x9AC79979452C6E96ULL, 0x0DEAADDCF5AAB73AULL, 
            0xBE57C6CDD7E7746FULL, 0xED73410BFA0FAC49ULL, 0x6A5E8061825F9E00ULL, 0x916238A2D5E34FDBULL, 
            0x01B2A274138F3307ULL, 0x156D70597D3FC39AULL, 0x2955A5CB60CCE8C4ULL, 0xDFF1D4BDC998D6D8ULL
        },
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
            0x8313D9B979E03274ULL, 0x7C052427CE25978DULL, 0x6CFC59556D082D39ULL, 0x2E82B4A84081F19FULL, 
            0xF2362AA04D1B5EBFULL, 0xA52236F1D5E0EE57ULL, 0x5C5D3CBDD2427AB7ULL, 0xCCF50E0E6688DA81ULL, 
            0xCB0FAB2F04557C34ULL, 0xC6B1B9923A082445ULL, 0x18BF436961410916ULL, 0x80961F2B12A1BFBBULL, 
            0x5BF710B066CE9D02ULL, 0x5BA5FB9C71353DF3ULL, 0x26EB191DD1A841E0ULL, 0xBB30217DE2D95D44ULL, 
            0x8D8017FC17D02212ULL, 0x34C63FC305CA86BEULL, 0x9D957F978D9E9E55ULL, 0xD293CE828FD75FCCULL, 
            0x801249505F0559A0ULL, 0x02EDA9957AFAEB48ULL, 0x37665E525CEB2AEFULL, 0xB7CFAD8FD9B3A033ULL, 
            0xABD12292A42A971AULL, 0xBCA7D1CD58CB1F07ULL, 0xAB9EBEE2E26F7402ULL, 0x81672F4B62CA0218ULL, 
            0x4063050A28639DDDULL, 0x4A12BFEAB002A383ULL, 0x119CFA92AE258707ULL, 0xFF977BE72A14D29AULL
        },
        {
            0x21FCBBB72D8A106FULL, 0xE61145EFE727BDAEULL, 0xF381B559DC748C8CULL, 0xC6F07D5EC7FB4AB9ULL, 
            0xE8963AC3BB4C3371ULL, 0xDED84FDDBF031499ULL, 0xFA37AD9857EDE4A6ULL, 0xB95150815D883010ULL, 
            0xB1869D1E056709F9ULL, 0x2F6DAA4326E70356ULL, 0xBBB8213E6F38B361ULL, 0x006E2DFFE176CBD8ULL, 
            0xEEDA47A3750838DDULL, 0x70AC2793F47708ECULL, 0x66D2870DE11C5872ULL, 0xCE57D17933CCB86DULL, 
            0xEAE2B086AD9556F6ULL, 0xFF568FD1E26E2152ULL, 0xEB28F729CE347C09ULL, 0x25D535A6EA8B455FULL, 
            0x7CB27D206CDA52C8ULL, 0x3EACEF97E98DC917ULL, 0xE961C0755F7E2363ULL, 0x3B52BC4E99D5B6BFULL, 
            0xAE6FAEDA84B74A2CULL, 0xEB91EA7B9AB8219FULL, 0x4665152C601BCD68ULL, 0x3E3A91AE3554559EULL, 
            0x0467D54D098936ACULL, 0xAA242C56D164460BULL, 0xDC4A4834FE9FFC4DULL, 0xDB0026AD29F2F035ULL
        },
        {
            0x60A028EEEEA25DC1ULL, 0x1C5B83D985BE5246ULL, 0xD0B990C70485EC35ULL, 0xF969C9E6FCB62331ULL, 
            0xEDE5640134C614F2ULL, 0x73F679759AEF1FA8ULL, 0x15FFF04B6F826CC7ULL, 0x470292621D14CF45ULL, 
            0x6D69D8BE8B625E7FULL, 0x7BD337D9306DBAEAULL, 0xACAAA7AA4F83BF64ULL, 0x21C74484ACBAA7BBULL, 
            0x2EEC61A3DB3A1258ULL, 0x5DEF68465E2B1769ULL, 0xBCB3A8D4432264FAULL, 0xBD3483B8000DECABULL, 
            0x290B88039CB53C0FULL, 0xF53BAF94DEB07961ULL, 0xDD0FCB3CABE5284EULL, 0x8B1E536741C179A3ULL, 
            0x16EEA3EF1591B517ULL, 0xCDAD5819F6D390B6ULL, 0x0BB094ECF83D8CB8ULL, 0x3D0DFA0DC501828BULL, 
            0x73F61BA797B7C762ULL, 0x7618780192A3616CULL, 0xEFD74F730EEA2E8BULL, 0x59709597AB341C76ULL, 
            0x2DDC990677BB51E5ULL, 0x9D4E081CC3E6AB03ULL, 0x6270437AD89EA415ULL, 0x90D1E904C5528721ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseAConstants = {
    0xCD8EF631CF14E240ULL,
    0x612119C9CF10D158ULL,
    0x1AED787C88A7537BULL,
    0xCD8EF631CF14E240ULL,
    0x612119C9CF10D158ULL,
    0x1AED787C88A7537BULL,
    0xB5282A2AD333CA27ULL,
    0xC17DA3899DDB9C28ULL,
    0xE3,
    0x28,
    0x07,
    0xDE,
    0x2A,
    0xD6,
    0x4A,
    0xDB
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseBSalts = {
    {
        {
            0x4B11DBF24153C95AULL, 0x956A21B1F497837BULL, 0x5F58A114F183FEEEULL, 0x92330247E7E06F0FULL, 
            0xEB848A1AA6D16C7CULL, 0xAD6E08800FDABEAFULL, 0x760A7CA4E7CA06ADULL, 0x9805F6802A26EDDDULL, 
            0x543A732EC8305209ULL, 0xA46B829E5D1B4D5CULL, 0x6CEC3AF2C6267C7CULL, 0x8EE9CCC984AA25DAULL, 
            0xBA5AFDDCA896E29AULL, 0x30163C73AABB9C10ULL, 0x101D0CFEB26CCE0CULL, 0x38C3C1F21E403ACFULL, 
            0x8677E36BD6981C98ULL, 0x7DD6369D03602D6AULL, 0x7E00C707ABB48707ULL, 0x56FBC14BD4E2537BULL, 
            0xDBACA1A9FDBBF9B7ULL, 0xD07735ED78A8CDFAULL, 0x5EC16A6E20D2417EULL, 0x977726628F1E0614ULL, 
            0x1573E579A8AC4AC9ULL, 0x40D12F6F30157B92ULL, 0xDF555D8E6CED0394ULL, 0x3242CD4963C3992DULL, 
            0x02DCA7E43E957A47ULL, 0xDF8C0C9F6146B108ULL, 0x158C5A962F92DE4BULL, 0x8730AEE5A712AA4EULL
        },
        {
            0x1CEAAA916140E0A8ULL, 0x0CDF7F647783AFDDULL, 0x9D4E155CE04FDFE9ULL, 0x793FD75FBB0EAFEEULL, 
            0x328DD450D256D708ULL, 0xA8FE40EB5A3D1D86ULL, 0x6358E8DEAFB74246ULL, 0x60830741804D0EA3ULL, 
            0xFB4DAA6D17451FB8ULL, 0x9D63A3C0B792D197ULL, 0x45280665A4D9270BULL, 0x4FF10376533BF418ULL, 
            0x8451D154276AD76DULL, 0xD1BC712BDDA1214EULL, 0xBD63C90BE1CED746ULL, 0xD5C319DCF8957CD7ULL, 
            0xCF2C2F7C9C8BDF60ULL, 0xF7DD98520EECD069ULL, 0x0526795EC9FFDD66ULL, 0xF300ACA15FEE915CULL, 
            0x6C9E09DBCFFE3C79ULL, 0xE9B843B8A439AD90ULL, 0x7AF58A09FDCA088EULL, 0xC89D740430206B6CULL, 
            0x66771C7428972CF2ULL, 0xFFD106F3204A54FDULL, 0xDB00DCD9404259C8ULL, 0xD21BE4730E3B5074ULL, 
            0xB6D804EC1AF56B41ULL, 0x694DF4821D2772BAULL, 0xAAF3F475B4532EF3ULL, 0x110E3B2EC704E667ULL
        },
        {
            0x41C2BC6871313752ULL, 0x3A3426EAC6B0ADEEULL, 0x80CA8DD218BDFB89ULL, 0x868E06CD24F44A48ULL, 
            0x2C0DD16FFD145811ULL, 0xA75099F52F249E5CULL, 0x37B5A21E7FC81E11ULL, 0xCB5263D1CF457B2FULL, 
            0x9D9D5524BC9B076EULL, 0xB22B806BB7BFAFCDULL, 0xD0F5C04F61258D1BULL, 0xA32A418EA9FAA8E8ULL, 
            0x74C3DCA2B7FFAC20ULL, 0xC9BE41D211CC0DEFULL, 0xE845ABF00619FCEFULL, 0xF2153178A563A596ULL, 
            0x64FC287CD2AF04DCULL, 0xD39221817BF00FA1ULL, 0x8C869A011C9C57FFULL, 0x1F20E6358094F77BULL, 
            0xCC52D2A077962C26ULL, 0xE4C9635BB2355F5DULL, 0xD741DC8719CDBD68ULL, 0xD6F99E2AA5BE6D68ULL, 
            0x19446FB508E7357DULL, 0x43650204D5A8DB5FULL, 0x0E79AA212D4DF956ULL, 0xE84BB20630DC49D4ULL, 
            0x2449D11B3C17972FULL, 0x0ECEF5BB878779FCULL, 0x59E2B7E328AD7538ULL, 0x33790580D5B7301DULL
        },
        {
            0x9500B6851515A6A5ULL, 0x6180F105633A563CULL, 0xB6F5A4264DD4C1B6ULL, 0x51ED28E1F79AEB47ULL, 
            0x7EA001FCF3C0EFDCULL, 0xC123FD4D7A9EECE7ULL, 0x3596857DD44E7711ULL, 0x14756365B542833EULL, 
            0x97850CE461F17EDCULL, 0x16AFB72FEB33AAD9ULL, 0x936AA0F9ABE40B82ULL, 0x2E95F397A5468C2AULL, 
            0x5B7A4D789A54C0A0ULL, 0x87B222D76C8236FCULL, 0xAC3F335FCC8D7E8DULL, 0x9FD2C0C04E88BC32ULL, 
            0x45B1EA94EF987565ULL, 0xE6A1C30178AEF27CULL, 0xD945BC7168D10653ULL, 0xAA741BA2F373AC63ULL, 
            0xC7590E729B319C6EULL, 0x16D81B21EC0E864BULL, 0xCA409FD449D5F2E7ULL, 0xA01900E2E145C7ABULL, 
            0x284DF153CC7D5180ULL, 0xF6644584B0FDD0A2ULL, 0x6524F5FDA9744F8DULL, 0x64F780DD8EFA3CE6ULL, 
            0xF044A14EFB558ED1ULL, 0xFCB97A87348A5094ULL, 0x8E1D1FBF1A3E6DEAULL, 0x92C033E496687373ULL
        },
        {
            0xD634AA54B7CEB400ULL, 0x6953D1BE78C6C599ULL, 0xFC02FE0E6422D2D7ULL, 0xC2824F8850CD547BULL, 
            0x855779CA92A279C2ULL, 0xB9B84CCA37EBEA7DULL, 0x93D8E4A3FA1B5497ULL, 0xE69BAAB48117C1F5ULL, 
            0xFDC38B862750D22AULL, 0xDE226029E26E33A1ULL, 0xAD5F3F2CDCDB4280ULL, 0x557F3D0660C9122DULL, 
            0x672CC010DEB04E79ULL, 0x5BE338988E708631ULL, 0x4F293C97252E1527ULL, 0x84EA503E1E7A14B4ULL, 
            0x408CE8A3B154FEA3ULL, 0x172A834B42D1BAAAULL, 0x00BACB44CD24009CULL, 0xA82C6DA16CF4A1CEULL, 
            0xDDD227375B922216ULL, 0x761F505E25BA0073ULL, 0x9B80E7157E5FA66AULL, 0x374255BC24EBDD8BULL, 
            0x2FAFE7D70B9A2AD4ULL, 0xB931E4989A8321E8ULL, 0x6057206DD1654D01ULL, 0x9DC0020380165941ULL, 
            0x054196D637851BC9ULL, 0x94CFCC8D4E2C1E7FULL, 0xF0D1D5252E7A95C3ULL, 0x99416067EA34E39CULL
        },
        {
            0xBEAB0589141E7DC7ULL, 0x36445F134EBF2989ULL, 0xEAB77DB70D039BBDULL, 0x1E41E3D2C852DB95ULL, 
            0x04D0FF1B1AC3468FULL, 0xF9A4B6DD13216AD7ULL, 0xD05E296FCF101BA2ULL, 0xF6044F4F1156AA1BULL, 
            0x8105B39ABD9D669FULL, 0x4619CFCE0F2FE4F0ULL, 0xA5AB04A50071F6A7ULL, 0x8CE31B7FDADC3D53ULL, 
            0xD00926559E6E8E1CULL, 0x49C710F8F3557F45ULL, 0x191DA5523E55D232ULL, 0x7A3DF8DA0377E2B8ULL, 
            0x6202765844ED7A9FULL, 0x03933EAF64BC4895ULL, 0xB6B2FCF3B6EA966BULL, 0xB3D209D86C482D86ULL, 
            0x05EAA56DB6A3E955ULL, 0x1166E8780461EAD9ULL, 0x222174D8E41B6750ULL, 0x607E911B998F7FD7ULL, 
            0xDD4BD1BE4ABE8848ULL, 0xE493E61AB1C01444ULL, 0xD69C0F7B4E5D843FULL, 0xFC1AB5123A3B1082ULL, 
            0x7273673F5D57D517ULL, 0x56133367F170AC63ULL, 0xB20CF5B89CA9DB6CULL, 0x5E8DEFF6357BE76AULL
        }
    },
    {
        {
            0xD2D3A2F594C99024ULL, 0xF0BA83C266A72843ULL, 0xFB3F2365C3E0B870ULL, 0x6AB798B611AB928FULL, 
            0xBD359FEFB2DA628AULL, 0xE3D625218E892123ULL, 0x2D5C80AA7EB3800EULL, 0xD34B7C0F41C50E38ULL, 
            0x125EFF87ADF06505ULL, 0x2E990041CA202B7EULL, 0x57A6BBEE1A3F2239ULL, 0xB66C11861158E5C3ULL, 
            0x4BAE81BCE8A015B1ULL, 0x7BF7430C829B5381ULL, 0x75B48987271537E8ULL, 0x8E5DBEA2F3986BC0ULL, 
            0x3D9693A49F8D883BULL, 0x6FA7E8CF2965383BULL, 0xD562CC809394F71DULL, 0xE9FBA47FA2EF80D4ULL, 
            0x181452EF56173F7BULL, 0x28B93BD6C6E2AC60ULL, 0x91C856801FCF8F86ULL, 0x4003C5DF62F4A884ULL, 
            0xA6A6DF56EB09A232ULL, 0x4BFF8E760438CE4DULL, 0x5CB0B4B5D9756866ULL, 0xC5862CDDA91E0E42ULL, 
            0x3DBC37D3A6117252ULL, 0x6A9593F0740F87DDULL, 0x44040E5F05F24112ULL, 0x9556866D74E0A524ULL
        },
        {
            0x54D0C0C5C0806086ULL, 0x71D857DAD3452B52ULL, 0x8C51C9E54A1E6644ULL, 0xB9B39DBC25CD1CA0ULL, 
            0xC76E8D7C28D139F3ULL, 0xE883C960C328570DULL, 0x363CDEB956BEE524ULL, 0x3007CBB280B19198ULL, 
            0xC252DBF6AEB5C7F5ULL, 0x3271B037A40D5522ULL, 0x40BD84A20D8E23BDULL, 0x3CFB4271BD556214ULL, 
            0xC1F30D9933F8D10AULL, 0x21D4D18191EF1CAEULL, 0xD128643A650A135FULL, 0x59CB99A79B91B301ULL, 
            0xBF2A2EB842D3E1DBULL, 0xEEDCF2085E8BDF5AULL, 0x270DA2DAC3E94DD2ULL, 0x0D962B76E7DF2102ULL, 
            0xC07CD778F6C98AE3ULL, 0xF24459FC08A88701ULL, 0x5473DBD221122876ULL, 0xBC9E9AAE006E23D1ULL, 
            0x98B6752BC116A824ULL, 0x01F068416210FEC7ULL, 0x7870CB098CBE535BULL, 0xBAFE389E9BACF316ULL, 
            0x3AEFB3DDEB276B15ULL, 0xCFF3E1C64A487C2FULL, 0x7A10201D78B87A38ULL, 0x87D555577B39D178ULL
        },
        {
            0x0F0FAB9B6A59D34CULL, 0x1AB1330DE354914FULL, 0x79E9894D9C230651ULL, 0xE0C128F192D6C252ULL, 
            0xEB204D4F85EFA9FDULL, 0xF9FB6D4D7526AC0FULL, 0xD9F8BA88C5D942D7ULL, 0x9C91BB9FE3DC73C4ULL, 
            0x02F9F86ABB3722F4ULL, 0x2F4DDD81E2092825ULL, 0x6D81C9F2EE4AF5BCULL, 0x674959BC58938F52ULL, 
            0x3E72D87F95564936ULL, 0xA3C82C61D9B91701ULL, 0xB050D56E165A9E0EULL, 0xB19E4EC19DAF33EEULL, 
            0x488F506AE5910913ULL, 0x13FAB40B825A55CBULL, 0xB3F3F62EF815ED2BULL, 0xA74345C2310DBD44ULL, 
            0x8D84B1AD29E71755ULL, 0xA3EE2EEC05BCE7D6ULL, 0x9A6B1E2CCF933430ULL, 0x84A86A895B94D501ULL, 
            0xB768DA38F257996EULL, 0xB589800247EB1387ULL, 0x786397F2705C2CF5ULL, 0x665A538B5C8DD5B3ULL, 
            0x95CA86C288F13665ULL, 0x779C77AEE2FF38B5ULL, 0xDA0E5BF3B143B10FULL, 0x003FB81F07A639FEULL
        },
        {
            0x0A50F128442A6A4BULL, 0x840BB27622E6298CULL, 0xF43BEFA152FF0E7CULL, 0x56F9998554F67AD8ULL, 
            0xDE5BC40C30E04F2AULL, 0xF8FFB6D58BADA90BULL, 0xDFC98D7817B60539ULL, 0x420F62BA5D64EE14ULL, 
            0xC290D8074460A1C3ULL, 0xB7F3E8559E46F387ULL, 0xD8FFFE7DCC3A559DULL, 0x531CFE10B0F9774CULL, 
            0xB78796A42646306BULL, 0x617871C7DCCE67A7ULL, 0x55D2A4837AA33AFFULL, 0x937207962A62C2AAULL, 
            0xBBD194200C1A7747ULL, 0x8460FB3EC195AA66ULL, 0x9CD2EB7CB7783824ULL, 0x6634C884E8632D2FULL, 
            0x09EE0956CC290F3FULL, 0x54EAFA049AF6478FULL, 0x16D7BD80C36947BBULL, 0xE4A36FAD545A9A90ULL, 
            0x1070D3D5C9C7F7C7ULL, 0x17838BFA279809A3ULL, 0xEB20801A98FABA12ULL, 0xBC66997C595E6D27ULL, 
            0xFF8016D6EFC3259BULL, 0x424E665F837D8768ULL, 0x704C562A64A82DA6ULL, 0x021E7242DDB3FEA1ULL
        },
        {
            0x33EC5FC467E8F95CULL, 0x773859E534812F4FULL, 0x1213425BF210443CULL, 0xA21000FD901CD8A5ULL, 
            0xCB4AC9674CA60F72ULL, 0x8B9A1A7D260F32D0ULL, 0x41ABB0B63BEC0B6CULL, 0x1948F2EB00541F43ULL, 
            0xBDD0B26435A03223ULL, 0x1C79E5F961AAEEBDULL, 0x75C44361B613F9A7ULL, 0x8EFB2666665E5726ULL, 
            0xB512A93F1B874D67ULL, 0xD3541D957761284CULL, 0x0C7C4483B84DDB1AULL, 0x22C687FFD41DD4BBULL, 
            0x294E6058EF3BCD7EULL, 0xC1FE5384FFCFB5FEULL, 0xC2B7194219BD2EE2ULL, 0x2A199FB22B18A0CBULL, 
            0x50399F815ACC5BC7ULL, 0xB7EA9257F25646A1ULL, 0xCE2A0F4C125554B1ULL, 0x067236081A7244F4ULL, 
            0x2D3917DFE003D8A8ULL, 0x55BD0290AEE0A222ULL, 0x1F774C910CAC5857ULL, 0xAF58FFCC8C2418D3ULL, 
            0x9118706742C9EC5EULL, 0x2B344B38C6B3EA85ULL, 0x6D80D953B8BECBABULL, 0x5CC9F0AE1A2F1813ULL
        },
        {
            0x21817C261E9976DAULL, 0xEF96658DA2D3166CULL, 0x5AFCA45560E9E0E8ULL, 0x3699BBD1F5B39E97ULL, 
            0x4AA379A8CB160830ULL, 0x00FC1B3F49A8FB9CULL, 0x43999E2416D90551ULL, 0xE29E35161CCB3C92ULL, 
            0xD3030D119E07F8ADULL, 0x92AF09FC6D113226ULL, 0xC0EB4A90632EE0CAULL, 0xBA8631E5518E23B0ULL, 
            0xC94C7C919802E7ACULL, 0x22DEFDE4F90EA756ULL, 0x75DC527445EEADB6ULL, 0x5DA93C87723627A7ULL, 
            0x0688A4E633469FBDULL, 0x26C92D411B11A56BULL, 0x375CBB3DD28A9992ULL, 0xE995A65F8EA1A628ULL, 
            0xAC929CB02D22E8B7ULL, 0xB30C12C5076E844CULL, 0xA5F0AA42C4901EACULL, 0x291BA00205F22FA3ULL, 
            0xEBC5F20FC51BB9FEULL, 0x85D7FCD6D4F034DDULL, 0xE31048C079F6BD47ULL, 0x021FEDECB86F8870ULL, 
            0xB27770AA02A93E4CULL, 0x7C5B56630FACADE6ULL, 0x6FC2CBA88F618687ULL, 0x52AF84E161C6972DULL
        }
    },
    {
        {
            0xD5AB71BF227599E7ULL, 0x1326E4020EF41DFAULL, 0x43265721B0536D2FULL, 0xC791D8A56E13B8E9ULL, 
            0x9E73552D53BD8ADDULL, 0xB2B632EE068D3FF7ULL, 0x2746BF4D9140947EULL, 0xE8DB7E7BB4DEF74AULL, 
            0x4F8773A6EDD3F1D1ULL, 0x2768C3C8FBC40C9FULL, 0x914E8BA2A60125A7ULL, 0xAB94BF6C2CE89719ULL, 
            0xED67E8088AED57DDULL, 0x8343920DD16A900EULL, 0xC96C5263ED981698ULL, 0x673FB455C1ABBF67ULL, 
            0xFF4F68A692F77891ULL, 0xC12C3C6E19F3043CULL, 0xE8B258980CD26CEDULL, 0x91FA1EC4A169317FULL, 
            0x471D6B784ADEA537ULL, 0x71EFB6CE84FC4D10ULL, 0x6A8281D0E5C1D32DULL, 0xA87BB0A21B562DE6ULL, 
            0x8BE8824E85DA76C3ULL, 0x7A0F48439BD2811EULL, 0x12878F5CDCEC4DB1ULL, 0x81918172126FC619ULL, 
            0x7A60470A064479E3ULL, 0x68E15400046F5408ULL, 0xFCA6A4E26BD5113CULL, 0x045A9F8E1AF1049DULL
        },
        {
            0x5FDA97DF2A6EE829ULL, 0x123A61E4375C409CULL, 0xAA563E9312AEBCF2ULL, 0x76C82A41FBEEEBE5ULL, 
            0xF69CD565858990E5ULL, 0x540D843816BE19ECULL, 0x56A8A16E59363DF8ULL, 0x75B698133D6EFE39ULL, 
            0x9DEC9CB31B166351ULL, 0x298287BE65D1F10AULL, 0x9F91ED99C6BCA8FEULL, 0x540BFD62F56DDD89ULL, 
            0x9C80644771F02D6EULL, 0xF4EB0ECCBDAE1926ULL, 0xF945979EA6A08BA7ULL, 0x20C20FBF125CA5A2ULL, 
            0x3A1FCAFCC0EA866EULL, 0xA3FCAD592F0CB6D7ULL, 0x1FCA51947DCB9004ULL, 0x9477B477820961B1ULL, 
            0xBA02E7BC59B6CA60ULL, 0x4C6AFF90B0D4A641ULL, 0xC5AFADA64B459130ULL, 0xD5250855DA5392E3ULL, 
            0x460E9572B30F46D7ULL, 0xFC3AE8DC1B513953ULL, 0x3B6613C9D7194C70ULL, 0x590342F0E92C7BF0ULL, 
            0x050713ABA89FA3A5ULL, 0x1B21ED6D9CE7B2FCULL, 0xFDB5824977C58DCBULL, 0x9AFB6AA78A38068BULL
        },
        {
            0xF4F334D8A61B7238ULL, 0xFB46023794446C16ULL, 0xB3142BA92637E2EFULL, 0x75CA06867FD132A6ULL, 
            0x7ADC20CD856132C2ULL, 0x27C49A9023F02C23ULL, 0x5C55255508FC4C5DULL, 0x6E458952EE3FE992ULL, 
            0x5731AC5F723E4D05ULL, 0xAF4717C7EB6D56BAULL, 0x0396A02F3213DA45ULL, 0x81BF7031B6FA56FCULL, 
            0x06DB76E341AC6272ULL, 0xF4EC5C435A3597AFULL, 0x85D69EA8B84236AEULL, 0x8FCC9D4A4B5FFB30ULL, 
            0xA069306950F3A807ULL, 0xE7C9368F934B6869ULL, 0x88C56641C4CBF914ULL, 0x295514CFECB48184ULL, 
            0xE106FD3A31F269ABULL, 0x75DCFAEDD3C9D889ULL, 0x7A873BB119B84D2EULL, 0x3F1F6E82D275F4F5ULL, 
            0x47A759E77BC06364ULL, 0xA4BE1AD5D398A81BULL, 0x4A51F1C8532D0B61ULL, 0xBFDEAC99E2EDF2E1ULL, 
            0xC8112CCDC15ED46FULL, 0x58493E3CB7975318ULL, 0x824B2CE783AD8140ULL, 0xC898695A217B953BULL
        },
        {
            0xFD9A3AB2FCC6EC4AULL, 0x649861E19454AE65ULL, 0xEFF741E5D125CDA6ULL, 0xDE95EC4B463D5110ULL, 
            0x1795E89D8DCA0E8EULL, 0x6B964C370E225615ULL, 0x4CD10A6D93E382E3ULL, 0x405DF207B28F25E6ULL, 
            0x7262AB3A6A6A7EA5ULL, 0x0BBB8DD55C9314B3ULL, 0x55649835E93EB4CCULL, 0xCB2D3D5D340F91CFULL, 
            0x0474C23FDD2778D9ULL, 0xD17B0BEF10457BD6ULL, 0x7335FEDD5D7157D7ULL, 0x553FC2AF79CE8564ULL, 
            0x570FE9AF3013CD0BULL, 0x8A8DA3FEF2B433E7ULL, 0x26E230CFD27C4A26ULL, 0xB79094C4DBBCFE61ULL, 
            0xBB8878B9D9D23A2AULL, 0xEB43FD1976866ED4ULL, 0xC4AFEA2589894B8AULL, 0x7D6FFDD3AFB58E85ULL, 
            0x92523DC3762969F3ULL, 0xCEBE1AA9EE5BBE4BULL, 0x43E35357DA45EBB5ULL, 0x671CB3BB5A7D2381ULL, 
            0x8D99FC04628ED764ULL, 0xF7B5BACF7011BE6BULL, 0xD3E05C868C61C13CULL, 0x4D5C5C0BA20925CCULL
        },
        {
            0xFC9B079D0D85EC1BULL, 0xE44FDCCF12B80DA3ULL, 0xF62CBD7FFCC987FBULL, 0x5D6A4F9F1EDF0154ULL, 
            0x6FEE330D92197305ULL, 0xBF3AE3802AD642C5ULL, 0xA144989739AC2FA2ULL, 0x545B079CEEC8A8BFULL, 
            0xABEFC8C7C36642D9ULL, 0x295CB509C74D196FULL, 0x533EE811BA4064B2ULL, 0xECFFACFD8028CAB0ULL, 
            0xE13419ACC511F240ULL, 0xF455D6071BA7595FULL, 0xA06838DEDABE4238ULL, 0x5410F8A1983A5296ULL, 
            0x4E27447B20DDDEBCULL, 0x89840E052A3754CFULL, 0xAC6E396E110CCA95ULL, 0x95FCBDAAEC52EA66ULL, 
            0x0BBA64B0B5B87CEAULL, 0xCFE6D2B2C08001F7ULL, 0xA3257E8B0850BD62ULL, 0xA825985BFBD1561AULL, 
            0xD47CDC57E522B99FULL, 0xCD6DEF1E896C26BFULL, 0xFB57D6385041FD72ULL, 0xAE432AAAB1264E81ULL, 
            0xBCB99149948ADEA1ULL, 0x47A48D34C52BEB00ULL, 0x0F7431F8F1785B0CULL, 0x5A20728DE87D51A9ULL
        },
        {
            0x7D80E7BAB8052F8EULL, 0x3AEA0EB38A626740ULL, 0x945C2899492E3F83ULL, 0x5C0C6C1D3E527C8AULL, 
            0x4561FDD2B9DE5C72ULL, 0xA5DCAF8D575B08BBULL, 0x03EDCEE78C1A0FCAULL, 0xB5DBEC0F59A4A103ULL, 
            0x2B62F178730F6D10ULL, 0x322D23922DB6B6DEULL, 0x10E430FCBFD2E5D6ULL, 0x20ADFF8674F93ADBULL, 
            0x16BEC8C53E93BC6BULL, 0xC5F290102935A7BCULL, 0xAA9AA8526C29C127ULL, 0xDFA5DCAD2A03DBB3ULL, 
            0x0AF7827EA39A41C1ULL, 0x0A93D40498A0F52BULL, 0xA259A7DE9FC3D27DULL, 0xE68E6251F28D5B50ULL, 
            0x8E672574CC4D21F0ULL, 0x936379055416506AULL, 0x6CBBF8253EA1023FULL, 0x4E1E5CD0E22693FDULL, 
            0x0501098AD885D9A2ULL, 0xC646678EAFC124AAULL, 0x441327BADA1AA484ULL, 0xCEF09890B1F99753ULL, 
            0x28C4E291CA05045DULL, 0x33E18465897B0484ULL, 0xEF66ABC817AB39D0ULL, 0x087AD51E589AE2B7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseBConstants = {
    0xEF7339387CA168DDULL,
    0xA336366146114186ULL,
    0x55ADA66451BFFE7BULL,
    0xEF7339387CA168DDULL,
    0xA336366146114186ULL,
    0x55ADA66451BFFE7BULL,
    0x5D0BA6060F76AB23ULL,
    0xC358B5B067F793DBULL,
    0x7D,
    0x1D,
    0xD9,
    0x17,
    0xDF,
    0x63,
    0xE4,
    0x38
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseCSalts = {
    {
        {
            0xC8DFDED1E527A23CULL, 0x00859FF96C6EE38BULL, 0xE406E0CD0A90A606ULL, 0x696858E0D78F70B9ULL, 
            0xED78763E58E38439ULL, 0x78CDEC6F62C7C2E8ULL, 0xCCC468DF64C2A674ULL, 0x4D6CEE3ED2979B80ULL, 
            0xF89769404E18D0F5ULL, 0x4E612B6B38F8648AULL, 0x1033CAE3B42A4CEDULL, 0x825330B7EB38E177ULL, 
            0xA140A1DAF5EB0652ULL, 0x8688EEF95D5994B1ULL, 0xA1DF973148EA4A92ULL, 0x1F1600303FF1A70AULL, 
            0xA0426A7675E8EEFCULL, 0xD8A9C2410CF5E05AULL, 0xEA2E811489D7B22CULL, 0x83DD2AD89D82DA6AULL, 
            0x894C82CC4849537DULL, 0x6530529AC4486D56ULL, 0xF84E69FDB57B168AULL, 0x346E09654F15B377ULL, 
            0x37499273EB0BE1AEULL, 0x1781697C81D11B4CULL, 0xF9A7E2BE9652494FULL, 0x0682B70B802CB4B2ULL, 
            0xD6A2EAE207CE8AC6ULL, 0xC6EFA59974A5CF33ULL, 0x27F47AB6CD97203BULL, 0x74D6488888E0C03AULL
        },
        {
            0x4104F45F0253A549ULL, 0x6A342487FBE282D8ULL, 0x7F096D2872CE8C8CULL, 0x82801F62596EB686ULL, 
            0xE2613FC56FEE06FEULL, 0x3A1B5BC589076E21ULL, 0x209BDB15B0481567ULL, 0x79B6F3C07424E3A6ULL, 
            0x4CCA4E86F7DB5F5FULL, 0x87643D32CF23AE6CULL, 0x5D90B42A5507F183ULL, 0xBB4B0F3ABB4B33E7ULL, 
            0xC432E0E277998031ULL, 0x51A016F3C4293F99ULL, 0x2F25BAB86C420178ULL, 0x0A572F6690B4C4C8ULL, 
            0x2FAC71A2061DC69BULL, 0x634C7CB248536195ULL, 0xF74C445F2E02BF1EULL, 0x38BF8D501870B732ULL, 
            0x87A04643B4A8F0B5ULL, 0x0206001E1DE26A4DULL, 0xFAFAE50206092513ULL, 0x39B638A09FC10919ULL, 
            0xA0324F2FBAA315C2ULL, 0x70889ECE89A16D4DULL, 0xA30F988C930D7507ULL, 0xB80B23FCE7535B60ULL, 
            0x42A94D42B4B2A6F0ULL, 0xB147030CB3A13C79ULL, 0xB6DB3A14774BAA61ULL, 0x2554EA01EF99B3B3ULL
        },
        {
            0x62F0E884166626F7ULL, 0xF6330E482A6E395BULL, 0x6A3B0CADE308F9D9ULL, 0xFB58E5B576AB122FULL, 
            0x12C160F1E2CD259DULL, 0x765FDB43B6AEDF0EULL, 0x89D05164FE7F4CFEULL, 0xBBDFEB007D394995ULL, 
            0x2476F8EF29174D19ULL, 0x9BD78923D8A563B2ULL, 0x6D3570EF917A568AULL, 0x0C5FAAFDEA41759EULL, 
            0x65623F9139880D55ULL, 0x726B8CC9090353DFULL, 0x7F10A765FC108EF9ULL, 0xA1E5A69D8F2B5473ULL, 
            0x53CBE5344060E1DBULL, 0x6C408843EDB28EA6ULL, 0x5CFC583B6CCFFA6AULL, 0x02C587C9BA1F3A63ULL, 
            0x3BBF82FE861D725BULL, 0x62AFDAFE79E9CE54ULL, 0x5C7F25178410AC38ULL, 0x6EA42520B25712E8ULL, 
            0xFC7A7828EA03AE48ULL, 0x4DDA3741C1E81D90ULL, 0x250495CCF6A35DA7ULL, 0x37B427F128798F04ULL, 
            0xE646C246CB0718A7ULL, 0x4980AB8A94DC3555ULL, 0x40742055ED8C2B11ULL, 0x623872518C149928ULL
        },
        {
            0x66CD8152E71E8FC9ULL, 0x6218934E50E20DE0ULL, 0xBC529530AB6ECA18ULL, 0x27B91405FD111F45ULL, 
            0xC74E56D5277AEB80ULL, 0xEED88D4B35E22E7AULL, 0xCDEF31EF76D0D904ULL, 0xDAE0A9E41D965D26ULL, 
            0x6A85399A9E03EAC2ULL, 0x1A47AE1BE6037609ULL, 0xDF4D133F800FB074ULL, 0x7EF3466B12C630D9ULL, 
            0xAF8834C2A76400A4ULL, 0xF9A0843E4056B622ULL, 0x730C24127877C553ULL, 0xFAC7CFE70738763FULL, 
            0xF0DEC6EDA74BDC56ULL, 0xBD0088E5D8F462D7ULL, 0xF80EE300B7E5ED93ULL, 0xE8CC0AFA975A966CULL, 
            0x8E77D91EE5B3B581ULL, 0xF17FD2CAF79DCA02ULL, 0xEB3AE0E61E27B97BULL, 0x15C28F16864A8180ULL, 
            0xFF9D80FBB051B220ULL, 0x238348542CF4F1B4ULL, 0x54F45BCA6939DF5FULL, 0xF871C29FB5689C0BULL, 
            0xAB5CBC591D044E75ULL, 0xC4C3FFA661496F5CULL, 0x513BF420E486E38AULL, 0x3593CCBBC712249AULL
        },
        {
            0x7B510028E8785178ULL, 0x7FB09A71E9BF61FFULL, 0xF06296709E3A1C65ULL, 0xC438BC880F6F372EULL, 
            0x054408416E2BC84AULL, 0x79CDBB8AA2D17145ULL, 0xCD66F3DA4B331A5FULL, 0x27EC162743C81DC8ULL, 
            0x7D87D5EC76CE28FAULL, 0xA23E9E03E30B2EBBULL, 0x3725B9863B07A8B1ULL, 0x7917250EEB0F3388ULL, 
            0xD027A8F3F57ED4D2ULL, 0x2BFC1C80FE37A188ULL, 0xE504CC8C0DDF56E1ULL, 0xA0B09635D8194BC1ULL, 
            0x4B770764A95B0635ULL, 0x598C56119E555772ULL, 0x76D4F34BDB9E4FAFULL, 0x132F105039810304ULL, 
            0x8A9B04A0F54E6677ULL, 0x912B094ECF86D7F6ULL, 0xA72C8A05D1FDF9D5ULL, 0xF9EEC780A90053FDULL, 
            0x1BEB03453CF032DBULL, 0x67CEB686FE1B3283ULL, 0xE1021D0B7DB5016EULL, 0x12E1BFD6CDB7618CULL, 
            0xD3945AA8C06A91F7ULL, 0x3B4D366260577C1EULL, 0x7E467D5A6A642AF2ULL, 0xED0AD312B73BEB33ULL
        },
        {
            0x2447AC42CA7A681DULL, 0x7EF1856A35F83E56ULL, 0x15616A4DA575FE9EULL, 0x57B0FF422699E5C9ULL, 
            0xA0B8E141E4D7FFF4ULL, 0xE8FF29AB056A21A6ULL, 0xC8EA85B06B5CF71FULL, 0xB0B2984838383104ULL, 
            0xD1CAF8043850B5EDULL, 0x3241C12E03F2E2D7ULL, 0x1DCBEAAD078F09DDULL, 0x4C237D17379DBAD4ULL, 
            0xBA8391D9B33093FDULL, 0x5F10682C00E8BDF6ULL, 0x5178AA9BD54962EFULL, 0x5F253D42E15656F0ULL, 
            0x626D74C28CEE5071ULL, 0x956A7C0C8E630942ULL, 0xD02394C6FB70C73EULL, 0x000FF909612E0627ULL, 
            0x1F95503A4E12A951ULL, 0x1573BCBDA28284FDULL, 0x2B4DD8ACCBC9E3C2ULL, 0x672DC7E04A171AC3ULL, 
            0x81B7AA0D8F9943FDULL, 0x0C6AF8F819F5A55FULL, 0x2F1748C05E9015BFULL, 0x565B93879A43C5F7ULL, 
            0x9E04C4AC45A89E3EULL, 0x6F38993B79B0031BULL, 0x499F4AE6B25C6749ULL, 0x71089F0611FD3107ULL
        }
    },
    {
        {
            0x3886BAA6105F3673ULL, 0xCFD6DE0D48417AB5ULL, 0xC7705656DF3CB4A8ULL, 0x73CD2A76E6AC80C4ULL, 
            0x0157D9D834C3EC96ULL, 0xFABA4B13445CDDEDULL, 0x3247EB93B667C8E2ULL, 0x0F4D2D5B331071ABULL, 
            0x617AC290C0AD0B06ULL, 0xE6D1697BC509596BULL, 0x4A7F9B0F0DCED997ULL, 0xBB92CB995AE43038ULL, 
            0x679B579DECF7EAF6ULL, 0x9E73AF55464BEEBFULL, 0x64E5E0495270411FULL, 0x9907D0F55E4A764BULL, 
            0x4BDE2CD89D37180FULL, 0x62D1F944E42207D3ULL, 0xCE49C9960C10B5F2ULL, 0x22E3A4CE125AA678ULL, 
            0x6F53EA552CF2C35EULL, 0x71E7CD96F24C0404ULL, 0xC50A4D354F0CC7D7ULL, 0x4587D57E2DEF41E6ULL, 
            0xDBD5D330BAC64963ULL, 0xF550875B62F956DEULL, 0x13AC0C508C85EAEBULL, 0x67F3BCE9A7ABC011ULL, 
            0x5D4BFFEF169CC0C7ULL, 0x1D1FDE7625973CEFULL, 0xEBF12E94CC36B78AULL, 0x998FD7437BE7D050ULL
        },
        {
            0xABD3084C931DC458ULL, 0xDA5FC739D509D9FEULL, 0x65F4337235E50D73ULL, 0x830DAA987CF138E6ULL, 
            0x0B887B7BD7A19266ULL, 0xC152A747BFEDEA9CULL, 0xE5FD729D3A2DAA30ULL, 0x868FC0295D45CE62ULL, 
            0xF861ED6E116A81B8ULL, 0x39CA7AD2F342E430ULL, 0x723F83EF2B6C49D6ULL, 0x423F28F3C54F92D5ULL, 
            0x506E654B809A4433ULL, 0xBF18367C8607C4B2ULL, 0xC77E2EBC021AC6A5ULL, 0x6BFB611351159268ULL, 
            0x1D13F79BB41FCE30ULL, 0x8D0805382C660034ULL, 0x8008B91A7C42B80AULL, 0xC434B53DCB8A59DAULL, 
            0x1CD6D09FBD6263C1ULL, 0xA46B76F6C958686AULL, 0x916ECAFC1B68270AULL, 0x7EBA392BB192CD01ULL, 
            0xE56CDF26B1776B42ULL, 0x3C121C67238F6370ULL, 0xC9FE31B667CEE579ULL, 0x25F0EDDD7F3FF508ULL, 
            0x7E7A65357D3C4964ULL, 0x4C2E0326150C7696ULL, 0x47FC906D071E0BAEULL, 0x4DE13DD1F9A927BBULL
        },
        {
            0x502AD11278E98786ULL, 0x5DDF3798E94C2FF2ULL, 0x2D39A13B58FC8077ULL, 0xFB08B3A079ACE8E5ULL, 
            0x578E1F120F156C08ULL, 0x6239CFC392437D2FULL, 0xDA141D66E5AF1D3FULL, 0xDA03F10C7BD77E94ULL, 
            0xB4BFCC1073F771BBULL, 0x65D5405C0B5577FFULL, 0xFE36E8690BE46629ULL, 0x995CEE91A1CEAA4DULL, 
            0xC5FAF8D9002900C7ULL, 0xDF57EA824D461869ULL, 0xA66EFCEE5E18C0F7ULL, 0xCCC5EFD3851AFCECULL, 
            0xF43AF007C2D22D5FULL, 0x4CA2B156F2739E52ULL, 0x053DD59495B97993ULL, 0xF3ED99967DD27EAAULL, 
            0xFB01A6FDF84C273DULL, 0x441BAB2D1D4F707AULL, 0x74CB1122717044EBULL, 0xCBF2190A1DD67C86ULL, 
            0x10553D5B2B83FEA7ULL, 0x9AE67992B111F0C2ULL, 0x0B4A91C350A28ACFULL, 0xF0692F5599776E3CULL, 
            0x2D6E86D125E4C570ULL, 0xA27CFCB3631BCBCFULL, 0x6E5DDA8652B4EBB0ULL, 0xE30B4745CC496D51ULL
        },
        {
            0xB0C9BFDDDF575558ULL, 0x34690DA9D5D59755ULL, 0x8F8CEFE401274E1DULL, 0x1BEAA7B769109D78ULL, 
            0x3672086011AA1998ULL, 0x32B49B38F9C907FDULL, 0x086B2149739BB131ULL, 0xA59B64CDEFA70B8CULL, 
            0x8509639D09FF148BULL, 0x20D64ADBB58844C0ULL, 0x04C76BD6E3A7CCAEULL, 0x722081E80A6F1A3EULL, 
            0x97FD1264BDD520C3ULL, 0x6CF928E402FFB565ULL, 0xE0142959F98EB74FULL, 0x99DDDFDC9EB3F2A0ULL, 
            0x78AE5B4DD41DFD5FULL, 0x38750A0B19ABED9EULL, 0xFDFA5EB321128955ULL, 0x0ACCEE2C9AF71D6CULL, 
            0xE6D45198E2184A90ULL, 0x31C1759092FCA3D6ULL, 0xDEE548E5ADA9B1DBULL, 0xA9CEFCB8514FC7C8ULL, 
            0x20B2D5C45591458CULL, 0x8D105D534ACB78A4ULL, 0x45EABFC765E9B0B6ULL, 0x2E91F4F46081FDD0ULL, 
            0xCEC9CD626523417BULL, 0x44446B47CB824574ULL, 0x270E9427E9DA5A6FULL, 0x01251529E93C9187ULL
        },
        {
            0x501D291FF82E483CULL, 0x69F809761232C715ULL, 0x820B562B3848ABA4ULL, 0xCDC306BC7EEEDAC3ULL, 
            0x52781979D8B006D3ULL, 0x5B7C7588CA0576D3ULL, 0x01A48148CF28FD8BULL, 0xF7BB9FA77EF22FCEULL, 
            0x206256D83D0050BCULL, 0x16DC5C3A068818F1ULL, 0x25DBEC275C3E766FULL, 0x415369E92F3F97B2ULL, 
            0x17C1C6A15983FCA2ULL, 0x47B5B0F8EFB599DEULL, 0x4D38315D5E2A7193ULL, 0x2A88A7E7D5DE009AULL, 
            0xEAE5A74F4FD55AFEULL, 0x98C681E3CB9CDB98ULL, 0x3A0C3879AA278698ULL, 0x65986B3E529FA106ULL, 
            0x24F1B960FC7EF033ULL, 0x8EC758785D71D6FCULL, 0x48E7534B32D96360ULL, 0x7F14AEFDE5178108ULL, 
            0xEF908E9DD5917DB5ULL, 0x3682855F9DC6156CULL, 0x60382F51EB7B9822ULL, 0x0EA072596B4F899AULL, 
            0xB552A9F0F1DB97ACULL, 0xD4C769DD74705EACULL, 0x250E75CCD2B74786ULL, 0xA8A27EE62A612A97ULL
        },
        {
            0x17910A1977434903ULL, 0xD0D81D9D42A9EBC4ULL, 0x944E522CD8D0D03CULL, 0x4092AD5C298B89A6ULL, 
            0x47CA5A085D57DF87ULL, 0x583DBA7C8324A21BULL, 0x753EF3C1139EE971ULL, 0x1138167F500F8B33ULL, 
            0x20A80B62A99002E4ULL, 0xD77CB2DC752EDE25ULL, 0xA4EC88300F5136E6ULL, 0x272A660D25BA8F92ULL, 
            0xA9AEBB725E976E46ULL, 0x7DC4EB1CE68097A1ULL, 0x83198CE787BD57B7ULL, 0xE6BCE321CBED0AC0ULL, 
            0xC7E6D6043F3B04D9ULL, 0x832A4D297C82A34CULL, 0x699F2A320937EFA2ULL, 0xF4FF34532C2B113FULL, 
            0x2CFABC7398944775ULL, 0xDFD6AF05058A1C1FULL, 0x8382A964AE585948ULL, 0xC3C7B14617EBC865ULL, 
            0x02F567E8CFF6C9FCULL, 0x0ED1205A49CC3799ULL, 0x05BCCA6EA1A5F8EDULL, 0xE60BC6482A43E574ULL, 
            0xB5EF39F8CE6A597AULL, 0x3DB03B214E29C992ULL, 0xA71FF983AC939F9DULL, 0xBF6A3849C25D5211ULL
        }
    },
    {
        {
            0x67D69D7B80AA9C5EULL, 0x982C92D7702B8307ULL, 0xBE873EF292BF0E67ULL, 0x53AE7305973D9503ULL, 
            0xB364390F0E34F006ULL, 0x1037F2C70613AD49ULL, 0x727A1442F36D7E99ULL, 0xC5B00AC98B360D5EULL, 
            0x8BCA05DF2595AAAEULL, 0xD8E20B95C184FE90ULL, 0x84A0D30B845AF6D2ULL, 0xC72F5F7D2815FE36ULL, 
            0xFF6A7CE99347A2DBULL, 0x28C7D76ABC157438ULL, 0x151CFE9E126C84BEULL, 0x7B661F15152B3FB9ULL, 
            0x6F346D96DE947AC1ULL, 0x3289606B8FAA7835ULL, 0x72CF9BCE0813F973ULL, 0xCB416275EDD49A92ULL, 
            0x453C4A09774218AFULL, 0x046C5241CBE1087CULL, 0x8946A916A2AD3312ULL, 0x992EAD371C5E4888ULL, 
            0x275EE924EFD059BAULL, 0x2BEC9D3B0DC2FDAEULL, 0x7790F25455080303ULL, 0xDAAF55D247955EE7ULL, 
            0x82DA970A3F4F8378ULL, 0x9B558721D55C73A8ULL, 0x42EEAAA962B741C9ULL, 0x407100B48AF4810CULL
        },
        {
            0x1242F06409F5C5A7ULL, 0xBCF9B82CC2DE20EAULL, 0xD7C2CC0F5AC63390ULL, 0xAA904222E79F7769ULL, 
            0xF1B67D994819F02AULL, 0x6FA1880148F163F3ULL, 0x8AF8CD9DBC5AF745ULL, 0x016A17D4E3C2326EULL, 
            0xE5C3DAC921A3805DULL, 0x613CBA97F8F39C49ULL, 0x78B63764A0BA8017ULL, 0xF8B143282773A84EULL, 
            0x33252D45222CA876ULL, 0x57642002DB4CB215ULL, 0x88EE32A6CF834AF0ULL, 0x5B92F7A4E5E2F682ULL, 
            0x1923D732B06A975AULL, 0x2C77D4C973BA6904ULL, 0xCA775AE0D52ED2F6ULL, 0xDC0330AF8FF1F499ULL, 
            0x8F54B9778011F759ULL, 0x3BE6A1EB2AB766DEULL, 0x50153725BC6BD5D5ULL, 0x7E7468A2D96FCF0FULL, 
            0x866C8D55601E1B04ULL, 0xD99CA84ACDF52F28ULL, 0x0D72240418F24EBAULL, 0x03BF26617310083FULL, 
            0x2ABEDD9A00816CC6ULL, 0x5E6EC514C2269C50ULL, 0xFE03939160191882ULL, 0xC6CC9750F5839B76ULL
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
            0x25DF33FEEFDCBC32ULL, 0xC34B72E0CC854CB4ULL, 0xEF9BB74121D2A910ULL, 0xBD6497D5FC2A5514ULL, 
            0xC1D91204BF8C81F4ULL, 0x66BB9E5676074EB0ULL, 0x4C733AEF1A8778A7ULL, 0xB99B1E537B0B95ADULL, 
            0x006256854A47B03FULL, 0x5533BACF0558FE31ULL, 0x69931EDC473AAFB5ULL, 0xED7131EA7D24828CULL, 
            0x47DD551F1A4FD6C9ULL, 0xB37D0C7CF5FC3819ULL, 0x5DF05D054786D722ULL, 0x246B17A5230F37C0ULL, 
            0x4B8CC49B01BD8260ULL, 0x6F3144614991EE86ULL, 0x04373C10EE1071CEULL, 0x93B91EC7E81C8128ULL, 
            0x94B1C37211D60E0EULL, 0x67479FD63D10FE3AULL, 0x07B51DFD385667DCULL, 0x2C1E918119886ADAULL, 
            0x39FFB60C75849EF6ULL, 0xCF05475898C616D7ULL, 0xECF1DBCAE64B9CB2ULL, 0xCFDB84FCA32C294BULL, 
            0x8D00A82E241BF24EULL, 0xD73C51B5BAB1FA14ULL, 0x76C08631AFBDA196ULL, 0xF743DF8D33EB8B9DULL
        },
        {
            0x390FA184C04BCC49ULL, 0xB884548428F5A70CULL, 0x930826888AC45A3FULL, 0x98FA9C489C77D722ULL, 
            0xCE15829746E9DFC1ULL, 0xB3406618E924BE93ULL, 0xB69C4021042CABD9ULL, 0xC110DC649A888848ULL, 
            0x2C389015029F9995ULL, 0xBF48CF99D4F6F25AULL, 0x3B1ED9F8B1F55772ULL, 0xE850C968754D3E9FULL, 
            0x1B06366A51629535ULL, 0x6B80D31C704B75A7ULL, 0x9A286557C9EF8C1DULL, 0x562ACD3F5E6F6CD9ULL, 
            0xB570660F3017A57FULL, 0x13CAAD5CF1FFEA7EULL, 0x7374A88500A51F31ULL, 0xB2EBD6157EC66C42ULL, 
            0x07EC741410CAB355ULL, 0x9DEADCC7CDE5E4A7ULL, 0x4E88D11F7C929B2EULL, 0x53AAAEFF23729461ULL, 
            0xACF2EA734A731153ULL, 0xD34E8BA61F3F72E5ULL, 0xFB39647442F22C83ULL, 0x0CE2B720C46059C9ULL, 
            0xFD788D13BCC686E5ULL, 0xF1178DBCA5584F15ULL, 0x911956C03EF88DFAULL, 0xE7972B2F9C15AD05ULL
        },
        {
            0xECFB1501623BACF7ULL, 0xCA3EB291A571F097ULL, 0xB537C33F9EC6ECB6ULL, 0xD7E8FD8910F53C72ULL, 
            0xCAA8B210D4EFB271ULL, 0xF6C171786E88A867ULL, 0xAFAE6EA7C7C6E2F5ULL, 0xD1A2C710D70D2FD2ULL, 
            0xE747CDF0B62F8E2AULL, 0xEE265C7E7748B42DULL, 0x66C5A99C0473CDB7ULL, 0x3454469D38692527ULL, 
            0x23BDFD1EA04F7FCBULL, 0xA18EB2DD202953FDULL, 0xF36D6A3CA2179D18ULL, 0x935D01D40CB1E513ULL, 
            0x6BBC03AB6F4F5527ULL, 0x957309657AF7F3FBULL, 0x1F9224D148F5F578ULL, 0x07FDC4799BB67E3AULL, 
            0x80E43F1A9A129986ULL, 0xBF030C3CE6FC49C7ULL, 0x2D6B5A277699BCB7ULL, 0x8B6C2F8AFAC65092ULL, 
            0xA60947A0B9C1BD7AULL, 0x6DC44DC7C1EFF97BULL, 0x389DFC7BB5B79A12ULL, 0x64FC22A6535DF367ULL, 
            0xE3915FF3C54D6AC1ULL, 0x74C9C32A2CC4E35DULL, 0x1D925868D7C38FA2ULL, 0x0C4D28193FE4D2D4ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseCConstants = {
    0x6353CCE833AAF3E7ULL,
    0x969D96C780F2A415ULL,
    0x1EE2844484258153ULL,
    0x6353CCE833AAF3E7ULL,
    0x969D96C780F2A415ULL,
    0x1EE2844484258153ULL,
    0xDBEE0C69B4B18D23ULL,
    0x5AC21A354267E77EULL,
    0x23,
    0xC9,
    0xF4,
    0xA5,
    0xFC,
    0x09,
    0xBE,
    0x93
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseDSalts = {
    {
        {
            0xE86EBB7224327A20ULL, 0x5AEBF2F4E790F76BULL, 0xF80DDFB51CFFFE68ULL, 0x23214BF33ED1903CULL, 
            0x7F2B7D6580B3EDFCULL, 0xCD9592A3D1978478ULL, 0x0873CB94ACA66366ULL, 0x35C159093FA5F586ULL, 
            0x78B396109BF3D60DULL, 0x7FD18A7554B805FDULL, 0xEC364A676D6C2C48ULL, 0x9789B60C32DEC475ULL, 
            0x62F26354F60AF1C6ULL, 0x0F6368D606FCA680ULL, 0xC7E522FE5E67FFB2ULL, 0xCADD57BABC8C2CB3ULL, 
            0x882A3223DC9D88CAULL, 0xA93B7989DCE7899CULL, 0x4CDA89BB4C54750DULL, 0xC8F2D614CC04C712ULL, 
            0xE121D4048D83AAD6ULL, 0x0572CDBA9500990DULL, 0xCC3CE0584E89FF24ULL, 0x40E55A5E2C230549ULL, 
            0x8479A5DFF0540F05ULL, 0x00E319F586EE21CEULL, 0x66A271B04118F0F9ULL, 0x95162990010D1099ULL, 
            0xB7C929376C3CF5FCULL, 0xA6489055FBD18BDDULL, 0x837432C2F6DF91AEULL, 0x4038771C3B570AEAULL
        },
        {
            0x5E85712ED029788AULL, 0xE1E1C11D0057A2A6ULL, 0xDA49E58456A4A078ULL, 0xE71D33FE7684EB51ULL, 
            0x2BFA80ADC41DF19AULL, 0xD4398630DDDEE774ULL, 0xC7BEA279022B96C5ULL, 0x5A6242EA365DBA66ULL, 
            0xE0463AB065F10846ULL, 0xDE10869E11D6D8E5ULL, 0x42D58FB51AF1F313ULL, 0x06F12DECC3773CE0ULL, 
            0xABCEA7D87BA2C0B1ULL, 0xD50779A57F2BB76AULL, 0x2004AA2D6FC3DC7EULL, 0x0B4E36A520302944ULL, 
            0xF4C4E6163E6FC9B7ULL, 0xEFD25947033B31F4ULL, 0x5895C081E2B9F177ULL, 0x8C3B4774309C543DULL, 
            0xB8DF662956132642ULL, 0x1E435C0D3C0974D2ULL, 0xA5AA5A32E5E7EB22ULL, 0xF29CA2FBCC2C1F06ULL, 
            0x3DC1914F0A454B59ULL, 0x1588E4BB75511B29ULL, 0x628D6035FB616F03ULL, 0x207CC438E08D3FCDULL, 
            0x8645E1D80AB71B7AULL, 0xB5336690ECDFFC5CULL, 0x9A1C388D7A27A34FULL, 0x5E87B38421619811ULL
        },
        {
            0x3AA11F9E9E5BC996ULL, 0x809843EC3F4086AFULL, 0x6BC9D5A9E6563697ULL, 0x952F78415BE45B00ULL, 
            0x39B8E5EDF00E8297ULL, 0x701D688F5416F869ULL, 0x42F4C8E1A4FD3547ULL, 0x9F198BE02974707EULL, 
            0x0FA90D16185545E2ULL, 0xF5FECEBDD4CBE594ULL, 0xB2D22AD21759D162ULL, 0xC83E3327D5812DDDULL, 
            0xD8ECACFF3183990AULL, 0x1BA3A055FE9C9AC3ULL, 0xCC4F1954A77ADE04ULL, 0x1785A773A084F805ULL, 
            0x5C33CE812255BB27ULL, 0xBA024057B7A8354AULL, 0x00A8A20D5A7348E1ULL, 0x976384F709FFC699ULL, 
            0xBCF103C09BAE01B5ULL, 0x77464ACDFA5192FAULL, 0x1498A1A7A9AB18CCULL, 0xD33E6DE051A266CBULL, 
            0x48CF8DAA622C02ECULL, 0x135E168C92BB88D3ULL, 0xABB02D499D3E1BA9ULL, 0xDDF00B8945CC597FULL, 
            0xA87325967AF45F0FULL, 0x823DB4913FDF4FCAULL, 0x93CB208D530816BCULL, 0x9F20A97EAA3C55DFULL
        },
        {
            0xD95409C8668B5F2FULL, 0x04BAF5977D042BAEULL, 0xA7D33BB936A69710ULL, 0x08248BD86CD2356FULL, 
            0x645730745B399734ULL, 0x1A6BA37E0D0B2F5DULL, 0xBC370686D03F1B1CULL, 0x55A12B6BF5BC5D02ULL, 
            0x28AFF44F0839CCFEULL, 0x85DDE77A0B81EEF4ULL, 0x8C169814ACE8200DULL, 0x4B23629B4C250B37ULL, 
            0xFDB77DEE81AF7A13ULL, 0x338A33B27184A786ULL, 0xDF8C08E9A8ED98ECULL, 0xDC028F1B079302CAULL, 
            0x752EF5B33A0271E3ULL, 0x0C85194FF2BD08B9ULL, 0x5A327E8306306FCDULL, 0x3630FD0ACD670814ULL, 
            0x482BB7C6A3773E37ULL, 0xF97979FB9B088B59ULL, 0x0230F80AEEA1BE54ULL, 0x7FAF3F51F1BC052BULL, 
            0x5CD9EA2F95852244ULL, 0xDB3B9D7D87524280ULL, 0x6AA1F35B6B69CE56ULL, 0xF0EB8490DBD8050BULL, 
            0x331A7D2388A501A1ULL, 0x0007B76633049029ULL, 0xB12E1DE86F277681ULL, 0x15B01656293D2B1DULL
        },
        {
            0xBE38FA64B3CE8100ULL, 0x02E876F7967043FDULL, 0x265CD51DBD275A5BULL, 0x7D032AAD73DA250BULL, 
            0xF7FB217F9C5543FFULL, 0x5BD6D052884C2375ULL, 0xCC313842170F905BULL, 0x960B224C35B176EBULL, 
            0xFD86BB20758CC32FULL, 0x4CADDAF8E8F201EBULL, 0x3FF55CFB0167BF4CULL, 0x3197EBD751D4E537ULL, 
            0x14AD06037D589FF3ULL, 0xF5BFF24780153231ULL, 0x40DDC348283CFBDFULL, 0x827C1A37AE8635C7ULL, 
            0xF1DB898ED728FB12ULL, 0x91D87F8E92270A72ULL, 0xEE601E434CD448E0ULL, 0xCCF478B07184CC86ULL, 
            0x4FC8334C36E8C89EULL, 0x1A2D5F157C5BABD8ULL, 0x6543635D7C35AC37ULL, 0xD5485FDA15F29CCBULL, 
            0xCA500E06A32E8247ULL, 0x5479166ACB2BC292ULL, 0x67CC1EC50C295EDBULL, 0xD8F499B9772F1505ULL, 
            0x5B51942E5E89FA94ULL, 0xC06CE97453C16BACULL, 0x968E1869BE9E2ECDULL, 0x767D4843CA7641ACULL
        },
        {
            0xCD7C91BAFDDA1DB2ULL, 0x52FB1C17BB1058DEULL, 0xFDC34CBB0C1CA0E6ULL, 0x1C4DB5E46FFA910FULL, 
            0xEB914A8124D2E1FBULL, 0xD63190CD5667BFDEULL, 0x559CA020E9162A29ULL, 0xBC58A12431C32028ULL, 
            0x2A71AB160516B089ULL, 0x6A10322BCB7B83A1ULL, 0xEE700560B87B8FF8ULL, 0xBBB2EA3BBC5F5ED9ULL, 
            0x1F9C62ACBD62E022ULL, 0x3E42FBBB0126945DULL, 0x37C62FF74C80E210ULL, 0x68305B0C76D6F2ECULL, 
            0x7E902B7EA83CF730ULL, 0xAA34C3E4DB45AD1CULL, 0x25E1C9EFFBC1E8D1ULL, 0x196E5FC104A62E7CULL, 
            0x58B0F545C86C551AULL, 0xB7D253C455AE376DULL, 0x29A556A6B2C9B258ULL, 0xA9484376A81E0585ULL, 
            0xF4F7F93EDAE2E27EULL, 0x6670D213D3BA43CEULL, 0x5B767CAC39C7699DULL, 0x4835683FB225B911ULL, 
            0x0747258C53061FB8ULL, 0x861BA77C5A48F624ULL, 0xD4887E261E22F37CULL, 0xBE43A38C69C54748ULL
        }
    },
    {
        {
            0xC8AF1DFCF6C8CB6FULL, 0x436CDBEF06EC4174ULL, 0xC9D54A0EA44F9F48ULL, 0xAF111F4A6B9594FEULL, 
            0x9CAE860EE179EE00ULL, 0x01CD3E40269AC451ULL, 0xEA1E2A02A8D77857ULL, 0x4C53793DCC227D43ULL, 
            0x44B5139DB8B483CFULL, 0x8D633E1780CE7C0FULL, 0xEA16C4F080764C93ULL, 0x5DEE5D538747A1B8ULL, 
            0xF49608A2B302CCF8ULL, 0x4501410A7E0D48E8ULL, 0xEC4F7C9ABCC2FA7AULL, 0xE246FAE46FA32E3AULL, 
            0x90B7D358AFD4CC01ULL, 0x8CB67CF48234AD08ULL, 0xDC63908DAC315534ULL, 0xA993F4607749E19DULL, 
            0xA15C9C8491FFA3B4ULL, 0xED67B1EAE3912F8DULL, 0x544D354B3C435FBFULL, 0x5448A9D1623D1E63ULL, 
            0x34A10667178B5DB3ULL, 0xF07EC4D9F71C05B6ULL, 0xF6F7E079D75192A5ULL, 0xA1EFBE2B7BEF3E73ULL, 
            0x2627309006453650ULL, 0xACA757660B419917ULL, 0xD3779CFBC89FF880ULL, 0x08A55FC7E55163FBULL
        },
        {
            0x8D5574813D2DA145ULL, 0xEF459DA3D77A7724ULL, 0xEFD051244CF51E3BULL, 0x6C25D82BEFF8F6ECULL, 
            0xA1A12B4650CD1731ULL, 0x841459DFC9E9B063ULL, 0x667A0B930E559653ULL, 0x85BF8B6DE1154D44ULL, 
            0x83991459132617DEULL, 0xD41A9E6BDA096666ULL, 0x43F807ABB82BADE5ULL, 0x22B63D7C5BE01F42ULL, 
            0x45D9D69323C5E07EULL, 0x42E236890DC8B30AULL, 0xEAA2244685975023ULL, 0xADDFE0ABF2CC6893ULL, 
            0xA8AE994397719699ULL, 0xB1D054A93F477991ULL, 0x222059F6694F485CULL, 0xFA4AE24FF8B0F35BULL, 
            0xA2E34F5EA823D7FDULL, 0x254E03D757F8687DULL, 0xC8B1F7ACC42E2E52ULL, 0x9B0622462E16471BULL, 
            0xD148B0E9D8BC5439ULL, 0x66696773DF7B5B9BULL, 0x31AAEDEFA1E92E33ULL, 0xBFF814FA9DF489C6ULL, 
            0x4C716CA26E2CE257ULL, 0x058A1D811BD5EE4FULL, 0xE24F53141023B816ULL, 0xB3658D6FF9C0D63CULL
        },
        {
            0x43476264725137E3ULL, 0x4B7E6DA902DEDEF0ULL, 0xC809988C3D4AC000ULL, 0x85E3BE479E5FBDFEULL, 
            0x45D6873096EC53E8ULL, 0x3212B3648AA589F9ULL, 0x2F0A75A812826FE8ULL, 0x2ED826A2CC4BB29DULL, 
            0x01B498FBCEFB81F9ULL, 0xEB97C7338F2BCB13ULL, 0xEBD806D893797F12ULL, 0x92668281768B3EA0ULL, 
            0x77D5B55CD76FEE6AULL, 0xE938BD9B1B1C53E2ULL, 0xB328784FC4AC78F1ULL, 0x7EC1A805DC2293FFULL, 
            0xD2F3605B0ADA25CDULL, 0x7EC2F6F3A693B2D1ULL, 0xFCFA79007EC80C72ULL, 0x8C679ED885ECFFB4ULL, 
            0x78414DAEEDE24F28ULL, 0xFD08B14CB1E1B791ULL, 0xD3B6766A1BE5A562ULL, 0xE056E5CD9B1882F9ULL, 
            0x647DDF1E6CCC77B4ULL, 0x9D7C2A757C3C150BULL, 0x25827CDC4E39D2ECULL, 0x9A4C04DE71999974ULL, 
            0x34E7C3A56638083DULL, 0xA6B8F949CB70DBD2ULL, 0xFDE479529C76909FULL, 0x2A68A07052D9E031ULL
        },
        {
            0x353F7FAE66DD8256ULL, 0xE8ED0E1E891E4018ULL, 0x8FFDBBA4A3029631ULL, 0xCF14B8851B797C51ULL, 
            0x8247B72E09B3BA1BULL, 0x1BC625159D2B02F2ULL, 0xCE548DCE3010E899ULL, 0x78B43E892115E192ULL, 
            0xB94AE2C004227B3EULL, 0xDFF9C989DF93F5E0ULL, 0xB6FFFBA87983A0D2ULL, 0xB50304DE75564A7FULL, 
            0x5A509D2D408E6176ULL, 0x52466E665E14656EULL, 0xD886AB39C3AFDC11ULL, 0xEA46E47117D202D3ULL, 
            0x8068B6045A764E29ULL, 0x5380112F09A87F00ULL, 0x09290B46D8C99A4EULL, 0x5E71078F4398C756ULL, 
            0x1456FE0A8604BD3CULL, 0x5BE48B7AEE3816F3ULL, 0x074EB5D27C145F1DULL, 0xA2ED862972FE07C1ULL, 
            0x27ED1E6A4D087222ULL, 0xE184A773B067DD41ULL, 0x3235D7550381C25FULL, 0x9594677BCDE573F6ULL, 
            0x346F905149E6FCF1ULL, 0xA418004378C551B6ULL, 0x44B6DBEB86F03427ULL, 0x4E3385CA43DCD803ULL
        },
        {
            0x0D07FC5F7AEB884CULL, 0xAA3AD10121499EA7ULL, 0x49F85ABE1DF57D4BULL, 0x9C775C3FE235297AULL, 
            0x8DD308AFF805DE66ULL, 0x793078A28812F2A6ULL, 0x011A3136E5FF7B81ULL, 0x824501F718826F07ULL, 
            0x452125B0E4C8C120ULL, 0x29D08102C16834B1ULL, 0xEDF446D70799C5A2ULL, 0x39FA46B26AB7EC41ULL, 
            0xB924FA98821B1BC3ULL, 0xD1663086F00F7D63ULL, 0x9626B947CE8D7D50ULL, 0xB2E7CB781BB0D795ULL, 
            0xE5B351AB943F397CULL, 0x8753F1342AE2D225ULL, 0x0621F434215B1A46ULL, 0x2756C3B2B02A738DULL, 
            0x323FAAA5686C70E2ULL, 0x81AE69363616F46CULL, 0x14F2E9D58B075534ULL, 0x0FFB314A6264A0ADULL, 
            0x7C10E4621E90ABB2ULL, 0x2FD187F30EEE3D2BULL, 0x601E8F78EBDD2573ULL, 0xD45FA7B9AA517F00ULL, 
            0xAE99DB1EFAEB1306ULL, 0x049D444A4C176225ULL, 0xE6EC6D9F7E6FEAECULL, 0x441DCF511818598FULL
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
        }
    },
    {
        {
            0x6F111A6EFF070E44ULL, 0xA769F6F40EFA6DA5ULL, 0x6F09B9269226322BULL, 0x56B9AB2C62F54912ULL, 
            0x8390FEA666E03898ULL, 0xC1D6DE7057B4777DULL, 0x99EED7818A197EF1ULL, 0xEFD668C168B20030ULL, 
            0x26F19AAB0D30B16CULL, 0x3270CD370C3EC4F0ULL, 0x316E9C221FE87313ULL, 0xE425F57D00685E98ULL, 
            0xAF4E25257149AF1AULL, 0x2B491B135A1C7A9AULL, 0xB2B06A93BB60CEEFULL, 0xE3CF305AAC8066C2ULL, 
            0xC5C6940D47E59F5AULL, 0x070CC3992BC069F8ULL, 0x0CEB0086FCB420D6ULL, 0x9B723E21C6B1B159ULL, 
            0xFA8091461C4E1846ULL, 0xB6A00B2ABB5E5C9BULL, 0x1B4CE84E458E394EULL, 0x87F5FB719E2C588DULL, 
            0x6DC810B18077216BULL, 0xF676D732D016472FULL, 0x0771B41D19B9A7B8ULL, 0x7481D0BC4F661509ULL, 
            0x8244787901BF8FDCULL, 0x566F74CA18D9BE35ULL, 0x60C3C91C1B329AB7ULL, 0x18BB377778262AFBULL
        },
        {
            0xC04413A338FC0F72ULL, 0x9BE4E73DC1253DCDULL, 0x7A629F32F917EAC4ULL, 0x0D3F555CF43DD59EULL, 
            0x59F3DB41322BFE8EULL, 0xAE9F9067A1BE112DULL, 0x12162FEC6C92E6C0ULL, 0x7B76340317B7BD6FULL, 
            0x8390DE8BCC89F196ULL, 0x86DC7738154D51E2ULL, 0xC97B1BA43F2CEEBCULL, 0x1A3D0F930432A4B0ULL, 
            0x74B2A1C09C9C9428ULL, 0xF95E083985BCEA8AULL, 0x38DB3B5001ED332CULL, 0x24028A4E24A0EFD5ULL, 
            0xF3A12418BBB78F54ULL, 0xE089C479E0B3E934ULL, 0x345B06B44B60033AULL, 0x62658B59A6D72D2BULL, 
            0x6BA3F3959310C7D6ULL, 0x46D50712B4FC4572ULL, 0x143785108CC98C52ULL, 0xEF136D823DB064AAULL, 
            0xC1960DB180D41B2CULL, 0x0D7BBAFF2E4D6FCEULL, 0xA89F76A79AE4133FULL, 0x1D7BF4EF032FB6C1ULL, 
            0x5E27B93983E740B4ULL, 0x3764F48479A260FBULL, 0xA5126FE4E92D674EULL, 0x511CE33F55C340EAULL
        },
        {
            0xCE99B1E959E5A4BBULL, 0x6D6B848FE0D4AE0EULL, 0xCCB79E430395C816ULL, 0xDB69DC5C1421E111ULL, 
            0x277899432C7F9416ULL, 0x7CCA4C17229355F1ULL, 0xB80D43B18A531760ULL, 0xB1D0623B34025445ULL, 
            0xD3DF391CE13B8114ULL, 0xEF955FFCB09CE25DULL, 0xCFB2D30EADABCFD7ULL, 0xCE62610F840A7597ULL, 
            0xAE358B39FEEA9F9BULL, 0x5B54CE26939FE1CAULL, 0xE5FF92109984158BULL, 0xC23136BFA303F9ECULL, 
            0x7794843E5471B1C9ULL, 0x0181BF430A27703FULL, 0x51A72D7418AF59B4ULL, 0x10B1A44C88F64710ULL, 
            0x5058E4DB492EB2BFULL, 0x14D7DBE7598014EFULL, 0x746E01514C2E0B80ULL, 0x4BC15BCD8BD766BBULL, 
            0xED09090D8C14A8DFULL, 0x85A3261511F99368ULL, 0x88CD2EA63EE04333ULL, 0xF25B550ED2D2509DULL, 
            0x512C51E321B1D05EULL, 0xB05BCBE785B23EDAULL, 0x3344F02F7B4896F0ULL, 0xF52C79903B98BCFAULL
        },
        {
            0x421F1EE8C9B6DF21ULL, 0x27F1F73A0024E474ULL, 0x8F977052417B8814ULL, 0x5296A99DA2FFCA41ULL, 
            0xA32628A688EF3DB3ULL, 0xEFF3B257EA1515B4ULL, 0x31B361B039234CAFULL, 0x2DCE54715738E04BULL, 
            0x2CDBF8D1A51D7808ULL, 0x34B302183F1C9650ULL, 0x839FBE475CB7583AULL, 0xB8ACC2698AD5A8DDULL, 
            0x4B0147A35087F7B9ULL, 0xDDCF2A99EF1EDD8BULL, 0xF0D1312FA7BEB4AAULL, 0x1D5750E2A817E121ULL, 
            0xF05DB149B3CC045EULL, 0xE9B951507FE49031ULL, 0xD0A688A1E29CB3C0ULL, 0x85B2FC1F2E1115ECULL, 
            0xD4EAC81E6850B526ULL, 0x40768204070CAA52ULL, 0x2A513357F2E97110ULL, 0xE0DFAF5ED0CBC912ULL, 
            0x90C25ADD06CF599DULL, 0xAD3933D963B43635ULL, 0x8AD7D696750396F8ULL, 0x3EF9BDA18FADB99AULL, 
            0x74FFDD7EF4BA3FD0ULL, 0x1DF4188B81E68ADDULL, 0xCBCA31F255DEF2D5ULL, 0x62427BF90E4EBBACULL
        },
        {
            0x831570C8318CA9EAULL, 0x0C0E72AD8BBEE516ULL, 0xE2123572D11C8578ULL, 0x3DC7B69B26F655F5ULL, 
            0xC921D8C3C9363F1FULL, 0x4A42A562AFE283E2ULL, 0xE7389AC26A1E22A2ULL, 0xAF5C7F926BE34A68ULL, 
            0x036C83924822FE8FULL, 0xA7F9E55CBEEB9BBFULL, 0x7FFD455790BD8C99ULL, 0xC61C52533363C3D2ULL, 
            0x2A83EC97D084B2C7ULL, 0xBDD48A3F45BF2202ULL, 0xAEFDABEFFDCA5D9DULL, 0x4F518AEB42FAB8DBULL, 
            0xB4B2FB094DE05F6BULL, 0xB48B5186B1F7D831ULL, 0x165EF3BD1AE42479ULL, 0x087BB9DC79EF2CA2ULL, 
            0xB92B80DF10C526F4ULL, 0x9121F0D579C626DAULL, 0x09A402BE164D2C0DULL, 0x0121D482EE09BBDEULL, 
            0x81B39559D034C917ULL, 0x41F7878BC0207B42ULL, 0x74278563B7B8FE93ULL, 0x4D63B672D17C4437ULL, 
            0xF3EB7A6B5D8D450BULL, 0x2B316D7C88E8FFEFULL, 0x4F0779A3F5E24AC9ULL, 0x31AC5AA6383642F4ULL
        },
        {
            0xF29847E610632743ULL, 0xFABA07C31998B8F3ULL, 0x350DF7BF1ECC2380ULL, 0xA1C8759B713E4608ULL, 
            0x95E0AA2CDC681D44ULL, 0xE6AAFF96200A1914ULL, 0x09A0DCACE4012315ULL, 0xC5612F6E03713E8CULL, 
            0x3FA50246C254D708ULL, 0x928D93A45240F308ULL, 0x77E6366EDA4D09DEULL, 0x30B5D87659EBCB0BULL, 
            0xFB1429A5FAB2E74FULL, 0xA6F87089FD863450ULL, 0xA33474A3E745BAF9ULL, 0x59F5292B7562674EULL, 
            0x1B29B5B70781758EULL, 0x06295C0A46D7F7A5ULL, 0x397C7EEF0C49B56FULL, 0x6CE76728D8B4BEB8ULL, 
            0x87BAA3CF657646BEULL, 0xE8B4AA032D944FCDULL, 0x5F720727FE5D00A6ULL, 0xDE7291A9DC53989BULL, 
            0x0A42FA376DAE47EAULL, 0xA85CCE47EEE588B4ULL, 0xBFEAB9CD24BDE129ULL, 0x1166E7EE79CE6E20ULL, 
            0x69965A380F21618EULL, 0x4BDB455E9A5062CAULL, 0x309EE2EA78841F0BULL, 0xD4C5C54C76D3FF61ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseDConstants = {
    0xE18BC232FA69930EULL,
    0xDBDF5F549DB58B54ULL,
    0x4BE883B6629EA333ULL,
    0xE18BC232FA69930EULL,
    0xDBDF5F549DB58B54ULL,
    0x4BE883B6629EA333ULL,
    0x344B3B224733607CULL,
    0xD77C3F7B74C40C4FULL,
    0x19,
    0x0B,
    0xC0,
    0x27,
    0xB8,
    0x3B,
    0x0F,
    0xE9
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseESalts = {
    {
        {
            0xA58A68A3614B8C9CULL, 0x395F4015C46CFBD8ULL, 0x3FA18B9C1D4F6F53ULL, 0x58FA716552FBD879ULL, 
            0xED51D9161EFEBD2EULL, 0x0886C9E797200B1AULL, 0x88D90DF1B60C79D5ULL, 0x867B2E5F1CC6E4E8ULL, 
            0x3BE4343080E4960DULL, 0x10EEEFF7BBF15365ULL, 0xC8DEF929D4EDE515ULL, 0x5A1A6BEDD3E3D12BULL, 
            0xCF5C0176C7012334ULL, 0x27133DF822EE443AULL, 0xE2F944D0D3EED1F7ULL, 0xEAE90336773EE117ULL, 
            0x4AB558B126E2C95BULL, 0x72C046CB1DE42554ULL, 0x479B525BFA459B74ULL, 0x49671C95A17B4219ULL, 
            0xEE20C65FEA8BD5ADULL, 0x823179D862D0580AULL, 0x5CF9C3A75DAE46E9ULL, 0x4E6C93B322C51152ULL, 
            0x14BAA3E5A15A7AB6ULL, 0x94B5D7BD0B234380ULL, 0x907ED21054525F03ULL, 0x4236A25803FDB4C8ULL, 
            0x60FD0977713F503EULL, 0x733DEC35B8653244ULL, 0x26EC17E6F8C59E45ULL, 0x5345F0C0C82AEDCFULL
        },
        {
            0x27EDF9F246A38DF4ULL, 0xF5A9CB1B8330BCBBULL, 0x8A9A10BBEB0297B3ULL, 0x707F1B9C00143180ULL, 
            0x4B5BEE87FFE222E3ULL, 0x0CA8F8FF7F224364ULL, 0x601B3DD87B8D2914ULL, 0x6DC3983C9D849670ULL, 
            0xA20A57B254420B44ULL, 0x9ABC817012027661ULL, 0x713CCA81EFBDD238ULL, 0xA81499D691D0D970ULL, 
            0xBDECEAC6BFF21869ULL, 0x7DC23D6AF83E4722ULL, 0xCBAE81A0D8460181ULL, 0x775EEFACEE5A2F84ULL, 
            0x300D684BE4E9A0E8ULL, 0xB42EA6723EEB318BULL, 0xE29B2AD4BF210D2BULL, 0xB7CDF4234D28B9CFULL, 
            0x4C0D40489040B3F5ULL, 0x9777EE08FB54FB6DULL, 0xA7E55A30C857B716ULL, 0x9DC02B6362C6AFD2ULL, 
            0x7C5C3525DD18D439ULL, 0xF3ED280EF542A033ULL, 0x9E6384F8746D11C2ULL, 0x034B76647FB99A4FULL, 
            0x253AF73BC6A38435ULL, 0x23DF8DD8FD7E9A28ULL, 0x825FAEBA7DCB10B2ULL, 0x20336AAF8AB7301FULL
        },
        {
            0x1BA204FF74CECC14ULL, 0x46FDF321DE38D025ULL, 0xDD07A5B814DB3CC1ULL, 0xFBDAC093985C62A2ULL, 
            0xD4A8F500D45DE5F6ULL, 0xB980F5D6EBD70081ULL, 0x7C847BA0DC2EDE7AULL, 0x6F10DCB1D72104E0ULL, 
            0xA4C4FB03BBC342E6ULL, 0xD79FA9C16A727301ULL, 0x897F8FC58F6111EBULL, 0x8876CFB92D88A6CEULL, 
            0xC8B041F62E8FDDA1ULL, 0x07B1167B2E8B3BABULL, 0x5EC3AB02A38B7E27ULL, 0x3D3F4F67847EB87FULL, 
            0xB3815B63127D3931ULL, 0xAE3ED1C772E233B6ULL, 0xA0D895D8D221FF63ULL, 0xAFE104BDACF43860ULL, 
            0x3EFFD1E3184AE8CBULL, 0x5852CBAF97655FEAULL, 0x473261F80B88ED35ULL, 0xFAE4422D344528FCULL, 
            0xDA2C8667C9C9BDFBULL, 0x1A7BBE4690E04049ULL, 0x4B465E7C264ADD6AULL, 0xCDF0173752133930ULL, 
            0x7E557AADB7FD6DCBULL, 0x5800A60FB07C36E6ULL, 0x0BFB57FBBFDFF95FULL, 0xF16A2C57070C8D43ULL
        },
        {
            0xF7F9155A73DF2792ULL, 0xD9F2CE24BB636C41ULL, 0x21C0360193198B63ULL, 0xD85AF23773C5C791ULL, 
            0x460FB771B1EA5194ULL, 0xF11164D84618285AULL, 0x9E0B502C96AB20FDULL, 0x6D3788947FEF7520ULL, 
            0x9740D5222C8E1846ULL, 0x7622B5142CFF1D2FULL, 0x08A5927266488B12ULL, 0xA2552B14BA2D9572ULL, 
            0x6738701C7A6A4850ULL, 0x58A72A93DF2C6A48ULL, 0xA96AA2112EC2907FULL, 0xBA27D4CFA8EECC5CULL, 
            0x4CF142FDF8DB70E0ULL, 0x7C7FC0379C969DB8ULL, 0xF965FAEC699A73A0ULL, 0x76368A0E0CBA84C3ULL, 
            0xEA53E410EF6963F2ULL, 0xD529FC1481531C2FULL, 0x6400B9EF575C3096ULL, 0x8CDC460CF4212F97ULL, 
            0x75369B7146827945ULL, 0x267DA95C6F3E644EULL, 0xFA7E479DDA83550AULL, 0xC02883EC1C9B8922ULL, 
            0x92B27AE481F77DFCULL, 0x5261D466AD279F56ULL, 0xE8A8EBDAE5D4B5A6ULL, 0xB64DDAAEF9140005ULL
        },
        {
            0xB369D07CF3B36AACULL, 0xFD22A0BEAF8238C3ULL, 0x0B97B05BB375C42CULL, 0x3A27CC3C6D4CBF41ULL, 
            0xFCCDBD71DDFA1452ULL, 0x5BDA9C27493EB87BULL, 0xBFBA28473A73E1F6ULL, 0x5BB8440BE60A684EULL, 
            0x70491CA4CC404E2EULL, 0xDC6BEDCA9F85F945ULL, 0xC68A2C064162408FULL, 0x7F1832A0EC196146ULL, 
            0x41E515CAA677ED2FULL, 0xAFF02FF64A7347FCULL, 0xBD63E0838C0350A1ULL, 0x2E023677CCB11E1FULL, 
            0x98B196AC36AE4DA6ULL, 0x3CEF7F03337692EEULL, 0x7619CCA2631360C5ULL, 0x643EFEC97CFA9FE9ULL, 
            0x560CAC72C0A49EF8ULL, 0x086A4C7A5A8F05B2ULL, 0x06B22BB391EFDB87ULL, 0x4C57529519FBB888ULL, 
            0x6B381D8A864B2169ULL, 0x2FC1438D55E824D0ULL, 0x6FFBD0D6868316F0ULL, 0x162EEF6353A2365FULL, 
            0xCC4A064DC62E8327ULL, 0xEF0DF089BE255DDFULL, 0x601B4F06056B00CFULL, 0x9BB48E772CF6B5B5ULL
        },
        {
            0x2852EA6594B87E8FULL, 0x51BDEBE0F4390BBCULL, 0x733B8DD9A6C2FFB0ULL, 0x6603001F7F316E77ULL, 
            0xA774C1EECE2D41B6ULL, 0xB9AC7F29829527E4ULL, 0x60662844A0164004ULL, 0xDF83A7C8EAD2B175ULL, 
            0x7ABEEC7CA2EC8E25ULL, 0x69C2B3DF6C9AD009ULL, 0x98A30C7B0E31C7C9ULL, 0x74BBCE7C9EDACE1DULL, 
            0xB2BC7BC92CA122B0ULL, 0x0F58583F5F5657E4ULL, 0xE3E47BDA7D05CB7EULL, 0x41A706FC72F7FF15ULL, 
            0x41B0EF2DC7FC6741ULL, 0xCD204A1A4368DADCULL, 0xFB95D2BCA6488369ULL, 0xEF95452907E7336BULL, 
            0x5D85FD1BD8F351F4ULL, 0x352E15BF8C1AC05EULL, 0x16C17FD4598549ABULL, 0x4182B91478B4F675ULL, 
            0xF4A93589A1B943DFULL, 0xEAC20785C7D03619ULL, 0x11B1C38CE7D6A7ADULL, 0xE001E84A03054A7AULL, 
            0xBB8F279D2F053A77ULL, 0x47FEBA96F10C0E52ULL, 0xF2E7D1DFDA11E890ULL, 0xF7E8D48973D76159ULL
        }
    },
    {
        {
            0x322DCF2BD7D0F3DBULL, 0xF77EC7E423D5FDADULL, 0x49515623053CB098ULL, 0x1BE6350E9261E2BAULL, 
            0x7D7C5298C6170D52ULL, 0xCBB255A83B85EEA4ULL, 0xD051994589E15C76ULL, 0x9371D98354CF355EULL, 
            0x0E83ED7B4BA451EBULL, 0x61057D7C22012593ULL, 0x92B590E14AE889F0ULL, 0xDC7BB52787D1A88FULL, 
            0x5E96AEF5C2B864AFULL, 0x36713E02B6451CB9ULL, 0x0BBED6085F6980D4ULL, 0x28DC1D2F3F7DBEC2ULL, 
            0x1DD358F3DCBEF4E2ULL, 0xBC3AD99EC7E429A3ULL, 0x84E23BCD027AC652ULL, 0x05FB815EA6AC6273ULL, 
            0x36279F995089D618ULL, 0x9D98F835E6F1B513ULL, 0xABF143A6018AE6ADULL, 0x807C2F88C7499174ULL, 
            0x5588606E65F89945ULL, 0x8C1364F37E542994ULL, 0xB18D5CB2960E3E35ULL, 0x97EAC4CAD17BCA86ULL, 
            0x358300217F4B52B4ULL, 0xBDB8C3A2500810BBULL, 0x6BB4CE3CA15F8C25ULL, 0xC0F7CC9C349107E4ULL
        },
        {
            0x7621DF46B6074FF5ULL, 0x113A2CDA721A7A76ULL, 0x36ECD1005BC2CFE2ULL, 0x60544B6ACCE4F01FULL, 
            0x896EB87529C59555ULL, 0x457650D54F22FD49ULL, 0x081C7F7BB9707B98ULL, 0x57C0E378A3179F21ULL, 
            0xD7443B08A4C0D5E4ULL, 0x111D0D0E15E71D83ULL, 0xE13F4C5FCFBA6A57ULL, 0x53E24C820E217C30ULL, 
            0x4E75085F595D2F1EULL, 0x10C51D9E75830721ULL, 0xF34C5A131B50D3BDULL, 0xDB0B92A4859CA009ULL, 
            0xA36DB4FFF6CAF49EULL, 0x016C24D87AD5ADFAULL, 0x23CF3B9BFA74E524ULL, 0x928A36CDF74B8A4FULL, 
            0x540B3BEA2B8B4E5DULL, 0xD1D00558BE06F9B4ULL, 0x4329F43EACAC13E9ULL, 0x57FDC14D65544E85ULL, 
            0xC75F950734ED035AULL, 0x0DD229370AE4E07AULL, 0x9CFE0A73819C7BF6ULL, 0x6919E11B7FF448A4ULL, 
            0x2E9D3AB041A68956ULL, 0x435ABC095C346516ULL, 0x12B82FB24D4F49EEULL, 0x866A1781A4BB6A8CULL
        },
        {
            0x2EF77FECF21ACCA1ULL, 0xA776A22788154BBBULL, 0xF3F561CB206204A0ULL, 0xDFE23DAE188BE931ULL, 
            0xFCF6971BE0E6D995ULL, 0xE48FCBE9F4810ED4ULL, 0x614C9C37DE00C17DULL, 0x9DD64FA3312F1CC0ULL, 
            0x9D08547EA3FBF82EULL, 0xE3E092F165DF1B17ULL, 0x585B28426685123FULL, 0x67EF8D60E7874F60ULL, 
            0xF10201BF0D5FC4E6ULL, 0x8942A047EE44674FULL, 0x93A17F1A06F73061ULL, 0x3B6A8461034322AEULL, 
            0x2C06BE4A8FF07BDAULL, 0xEB874587855381DBULL, 0xA922B12132165207ULL, 0x9F6779EC058DBE69ULL, 
            0xBB8CF376588DC28AULL, 0x9D341873D3D89C0DULL, 0x3F003A10FF78D82FULL, 0xA51B3D339CF8BAC7ULL, 
            0xF83133DBFB07F2FBULL, 0x4EA2321272E9AFD6ULL, 0xA6278CA1C9935048ULL, 0x066334281F539258ULL, 
            0x02B82B61DC852DB5ULL, 0x44FBF725C0C068F2ULL, 0x73B6010DB55D2653ULL, 0x86DD951E10C96763ULL
        },
        {
            0xA96BFDFEFA264BE2ULL, 0x14960E63D5609607ULL, 0x2F81E081B1EABEF3ULL, 0xC1D9701B44005621ULL, 
            0x8EFF3050095946E0ULL, 0x7487FF2414C37CB2ULL, 0xCED0D0F754745E0DULL, 0x5CEAD91F2EB15871ULL, 
            0x95012F29F7313A82ULL, 0xBC8B8EDA3C235320ULL, 0xD3D0D50235BBED7FULL, 0xC54AB4DBEBC391EEULL, 
            0xF08968BC60B584B5ULL, 0xF072753EFED84583ULL, 0x37D7D71900CB1BD1ULL, 0x9C125547C92EA4B8ULL, 
            0x9C26408F73B33FBBULL, 0x1FBE08C644901475ULL, 0xADC9C398C737ABD8ULL, 0x2856E7E4BE50817EULL, 
            0xA5254DDFFAF6580AULL, 0x653446897116073DULL, 0x6F16051C18F7B058ULL, 0x15E0A5A167ECB4F8ULL, 
            0x4456E52F7EAD6A27ULL, 0x4E237481751A0900ULL, 0x5FAC099749D2446DULL, 0xB0853D110BD225A2ULL, 
            0x90E11980937D960EULL, 0xB4EEE880BDC921F8ULL, 0x81AC4DBFA2067E51ULL, 0x11B85F86D6953AE2ULL
        },
        {
            0xF8F8F2E01848E39FULL, 0x8EA5898A7F63049BULL, 0xD23D721581D7EE96ULL, 0x2B4BF81799934134ULL, 
            0x039BBD832151AA40ULL, 0xE36163A412ED1BE0ULL, 0xC75ACE711A738A1DULL, 0x5B700A038D59FEA6ULL, 
            0xF195D1701FB5D4F2ULL, 0xAB0D1ADE08D19ADFULL, 0x730B96075A9F90B9ULL, 0x1B8C6992C3270DABULL, 
            0xE686B6CB97735A90ULL, 0xB3F607674480B604ULL, 0xF648C65203BAAC89ULL, 0xF0E9F9A0136558F8ULL, 
            0xDA22EB6AD94D52A9ULL, 0xAA08442EFD19F795ULL, 0x125EAB4CE28FE28CULL, 0x2CD5981C9F46B153ULL, 
            0xDBDC5A5B8BEC7FAAULL, 0x3965DD36D01867ADULL, 0xD572163174DB6525ULL, 0xBE03C58B53EF2855ULL, 
            0x936B10CC8B0350D8ULL, 0x8FEF6650BCEAC0F0ULL, 0x574161BF39BDEE01ULL, 0x036A71C3D801F3F1ULL, 
            0x1FF597B26E129AB8ULL, 0x47637B8E6664A8CBULL, 0xC5FF25E02C2A3141ULL, 0x1B996817FEEB0372ULL
        },
        {
            0xB52BC9BFA57908D8ULL, 0xFF12CC73462A0FDFULL, 0x83303F51E322518DULL, 0xCE50A73391D79D83ULL, 
            0x25EF96DDF3B3C8D1ULL, 0xC586DA79C26165A5ULL, 0x45B438E9BEE953CBULL, 0x638D53A7509320D3ULL, 
            0xA15006EE46842EE8ULL, 0x21E943CD3225358FULL, 0xBEA57B6247582342ULL, 0x81E656F214C14A05ULL, 
            0x2E18754EA33D5708ULL, 0x59ACC5F7FE689C67ULL, 0xCBE8E2972B02BAD1ULL, 0x201BAE31B9B72CDDULL, 
            0xF1B640439494167DULL, 0xC56BF1ACDD519E6CULL, 0xEE1F6C83EAC3F3F9ULL, 0xC06E02C2EE320FF9ULL, 
            0x2FD65E9493F48B44ULL, 0xAE56A85C4BEE1669ULL, 0xCF65FF298AA67572ULL, 0xEAA8C6666E315653ULL, 
            0x24AB6DAF4F331B2DULL, 0x9572F84401A2593FULL, 0x695C6504FADC3BCEULL, 0xAC45FBC0CD4C3B82ULL, 
            0xF288AC694BF9DA66ULL, 0x7795BE83F97CF6BCULL, 0x3E938A20E011E0B2ULL, 0x5090F45E844706F1ULL
        }
    },
    {
        {
            0x8CAA7573B8AF7A4CULL, 0x13BB7896D27EBB99ULL, 0xE4B8BC20737B40E9ULL, 0x1D64B81A5E530433ULL, 
            0xD83F168DD0220C3DULL, 0x0CB23DF56838446FULL, 0xA248782BE06E2D38ULL, 0x02542BBA0FCBD3E9ULL, 
            0xE702A53599CDB824ULL, 0x0EEA06A02FEB2327ULL, 0x792F754927312637ULL, 0x309D07B63C4FC7CEULL, 
            0xB92B740BA7C78C87ULL, 0x9FF099444B2CFACBULL, 0x9E1EBC54B7F7B5D1ULL, 0x4C79DDEF9E05BC1FULL, 
            0xD8877D54B9525F50ULL, 0x2BF07D685917F58AULL, 0xAEE315D5F578A794ULL, 0x2B974F45D867F710ULL, 
            0x8E5D10F4CA54D1ADULL, 0x5A637E8728A50296ULL, 0x6FEDFE575BDACBACULL, 0x63E72E2DC84BE3D4ULL, 
            0x606D24C5F615218EULL, 0x7241C66BDE71F5CAULL, 0x77432A2E93BEC8E1ULL, 0x902056C5EE6700C6ULL, 
            0xDD882B92AF1D3BEEULL, 0x682C4A0B191C6F06ULL, 0x5CBF79AD8EBCE730ULL, 0x8CDF7C5765E2E9CCULL
        },
        {
            0x8C3EB5CCD5EF2E31ULL, 0x91401ED6A04FC11DULL, 0xA998DD177721869AULL, 0x1BB9243E20866E56ULL, 
            0x08ADDBC653681924ULL, 0x7842E4E027C2AE70ULL, 0x161EB93E6360E985ULL, 0xA1297D0338F72CCCULL, 
            0x408B26A7A015FBBBULL, 0xD74F05FDB6E43E47ULL, 0x271CDC059D473299ULL, 0x799067BACD13FB72ULL, 
            0xD804148E5CD27C1EULL, 0xBA80BF2C293ECFC9ULL, 0xCD05609D58F16794ULL, 0x68775C1DB0417BB9ULL, 
            0x608A7BD2B44E2346ULL, 0x8707894D17884729ULL, 0xA2DDEFE10E616BEDULL, 0x3B66D479266E7035ULL, 
            0xA554AF98E144BEE6ULL, 0x66DFA16A0DA4357AULL, 0x78837CB56F73DB46ULL, 0xA2AA0544731265A8ULL, 
            0xECC65F2B0CFD558BULL, 0x43053BBF9F370F55ULL, 0x9CAC92C15992E6E5ULL, 0xB4227D087C1ADB5DULL, 
            0xAFE85679CD9756F2ULL, 0x0CF64DC5ACC14C19ULL, 0x1B37C7B5BACD85E2ULL, 0x0D26E304A7D7BC9AULL
        },
        {
            0x9602765E60CBB8E1ULL, 0xDAA4FBD18F6086B2ULL, 0xA7E8E1D0D4CA5749ULL, 0x16DA8B6C5C5C23A6ULL, 
            0xF45268AE40A9A466ULL, 0xD2806E09D9DAD011ULL, 0x9B80A590B15447BFULL, 0x38D88C95F1BDECB7ULL, 
            0xA1F0F0729092D6E0ULL, 0xC04B34CB38D6630EULL, 0x50601E539FBC3692ULL, 0x2B7B3BFDA00060D6ULL, 
            0xD37EE79253473793ULL, 0x7D6FE39DECB263C3ULL, 0x51F4EEF5DBD069F2ULL, 0x73DEAE942E371BA2ULL, 
            0x0D8F1EB75D471550ULL, 0xA8561AAA62493493ULL, 0x62A1FBD9D9459857ULL, 0xB1CC3F3ED2FB0BD2ULL, 
            0xB9C4E92C9740AA4FULL, 0x93BB99143D3958F9ULL, 0x05CA888259CF36A0ULL, 0xEB8905C28D41C1F0ULL, 
            0x43F8DBCF04FF86A4ULL, 0x205CADD8C3037889ULL, 0xB2FFDE744545C763ULL, 0xAC72AFF3B96D64C3ULL, 
            0x859AB0B25F716A22ULL, 0xC8A3CCC7ACF7B032ULL, 0x083A08CCE312660FULL, 0x20516840C0CE1BBDULL
        },
        {
            0x6D13DC35C3AC5BAEULL, 0x1ED5029509E94338ULL, 0xAC1610E00CFC771BULL, 0xD99413BE8B2B9D32ULL, 
            0x62065D71FCD12B7AULL, 0xEF0EAC6678C1216AULL, 0xE3E5094686065361ULL, 0x42BA9EED8D5E45F0ULL, 
            0xF12C56C156EA3F27ULL, 0x4A00E4384E0D12B6ULL, 0x9A1E773691DC749CULL, 0x2A9D30943282171AULL, 
            0xB3F6AEAFF255A6E3ULL, 0x3028321E84C77CF0ULL, 0x9F3BA86F518630B1ULL, 0x9DA3E9D31C650E37ULL, 
            0x996436C491F7418FULL, 0x7335D8C675588D7DULL, 0x1EE57A16A754BB5CULL, 0x4B1E7ABD41189533ULL, 
            0x336E177B8A4A262CULL, 0x26063F9374192B7CULL, 0x48FC90487E600D8AULL, 0xE4276ECF52958BCEULL, 
            0x6CD53331453F5373ULL, 0x39C72922762371F9ULL, 0x8357ACC4DF27D2C6ULL, 0x76DF502733C2ADFFULL, 
            0xBD8246473B69D3BCULL, 0x585EA186205A79FAULL, 0x4F88A4E7069B47C5ULL, 0x5CADC144F99C580CULL
        },
        {
            0xB991CE1E0C7FA764ULL, 0xDE5F7D019C98C3CFULL, 0x334E24D1DF6DA837ULL, 0xFD206A9E6453B6FCULL, 
            0x454A52E96D762BD4ULL, 0x0C618DD1D42001C2ULL, 0xF93AEA2296182C6FULL, 0xB70EC2943B0EEAFBULL, 
            0x08DC1B22B603C35DULL, 0xEBF56DF82E2AF839ULL, 0xA55E44AE5E241022ULL, 0x83323562AF2C073AULL, 
            0xC7EA76B0B25FF308ULL, 0x24DD79E770FC6124ULL, 0x9CDF34BF0FA6C5B0ULL, 0x899B2705287AC73CULL, 
            0xA41F950BB49F0901ULL, 0x8A5A8179877C3B03ULL, 0x9CCFC469502AFDBAULL, 0xB69003C506897030ULL, 
            0x1E0D70136F701DEEULL, 0x3A2672CB4A3B342FULL, 0x8FAEB910D0FF6D16ULL, 0x9BEBA070827F2C51ULL, 
            0xA92AF4C53E22400BULL, 0xBBA4C7EB5AB14274ULL, 0x40C5A95DFF36DDC4ULL, 0xCAF367E0A61E1597ULL, 
            0x7928D46BC378A464ULL, 0x9F5B2CF3042497D4ULL, 0x849E59BA525A183EULL, 0x19173E6AD54893E0ULL
        },
        {
            0x7523667ABDC958F5ULL, 0x6384C4745A2C0157ULL, 0xD5CE2A5C0DEE4FD0ULL, 0x8D56ACEF92D0985EULL, 
            0x1F99532CD738295CULL, 0x21F3BA14F5209D18ULL, 0x0F3220341BA6BC4BULL, 0x70AA8412C6ACACF2ULL, 
            0x141BC7938C3295D3ULL, 0x4F2D77E9D437513DULL, 0xB32ADEA01310DDC6ULL, 0xC38FBF9AC9743BC0ULL, 
            0x81C4CEE5C8F31E21ULL, 0x6640B71BBAA98E89ULL, 0x28035DFD2F04D178ULL, 0x48C7EB3953109597ULL, 
            0xA96745E6C2E4EB9EULL, 0x1F5C4890425E6CBEULL, 0x5ADC2794B3D92B6CULL, 0x1DB72C011349CF87ULL, 
            0x2ED1B1C567059C85ULL, 0xA9B4DBF683A8A6B0ULL, 0x6D0F447345EAC13DULL, 0x05E394E8B82F6E16ULL, 
            0x732611AD48B481BDULL, 0x3C4F8B6901ECC612ULL, 0xED5FF9A96A977DF6ULL, 0x59EB423333BD9EEDULL, 
            0xEE6C020F115CF392ULL, 0x5CAB1AB7B05CA79BULL, 0xD541C0C76A90585DULL, 0x2387E865872FB477ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseEConstants = {
    0xFD6E7E76DBE18ADAULL,
    0x3AB93EDFA1E16E42ULL,
    0xFF221AE5AF9FE641ULL,
    0xFD6E7E76DBE18ADAULL,
    0x3AB93EDFA1E16E42ULL,
    0xFF221AE5AF9FE641ULL,
    0x9BB4A7B8B40DEB73ULL,
    0xFE12DFA027B7EED8ULL,
    0xBA,
    0x44,
    0x51,
    0xC1,
    0xE4,
    0x26,
    0x14,
    0xD5
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseFSalts = {
    {
        {
            0x20E046859C7BFB42ULL, 0xF0497644978AF44CULL, 0xE3A620EA1D9AC1A8ULL, 0xB89B728B6589ADF9ULL, 
            0x123ECBA8DF6C250EULL, 0x68A0A9D754982B32ULL, 0xC7078A5DAF813DFFULL, 0xD02C53B64729D6D1ULL, 
            0xFED6180C17BEE94FULL, 0x51F0B3E027E6DCF0ULL, 0x3379A99C2B422200ULL, 0x8BF4580C66989C62ULL, 
            0xAEE1EC020059927FULL, 0xBE87A6B6A8E1010BULL, 0xD0666EC0432095EDULL, 0x2E83A1E3936516D0ULL, 
            0x98E681A67DA31F31ULL, 0x76B4EA91017519D3ULL, 0xB74E2C0401C08F23ULL, 0x7F6F6EDEC165727EULL, 
            0xBBE1FB36EF75FB27ULL, 0xE2D30E9AEB22E86BULL, 0xF8D50EA465191414ULL, 0x98A684BE68274A8BULL, 
            0x350E9D738E5B8E4BULL, 0x98A4EAEB84A1A8F3ULL, 0x5E63D8ADB6597D1BULL, 0x22067BA3220A7A99ULL, 
            0x0A901865BA3DFC7AULL, 0x4F607062E927D1A7ULL, 0x2C514C5292439210ULL, 0xB37EB32F841CB51FULL
        },
        {
            0x7244F3953AF67783ULL, 0x53D997448928C7C2ULL, 0x14483165B8A6D41FULL, 0xA302B6929454FF8EULL, 
            0xB6F0F143C5CF45A9ULL, 0xDD35AD5B2CDA5989ULL, 0x087A1263F66EA0E7ULL, 0xF749EE9FA121EF86ULL, 
            0x158132EF892C7752ULL, 0x4B7B07047F09A83BULL, 0x753CF2E192FDCD4BULL, 0x45927A094B50D7B3ULL, 
            0x46D96AEB95683164ULL, 0x7A8094689EE4E126ULL, 0x4027ECED6C608D63ULL, 0xA1E34B50B9C5A375ULL, 
            0xDAB306BB8E67B3A9ULL, 0x4A184B0EE58D4DC0ULL, 0x6A2EA5D2F75163DCULL, 0x6AE0B2C7F71521A6ULL, 
            0x0AC00BE0D255608DULL, 0xCEB8783DBCAC8B92ULL, 0xB2526BF5591DEE72ULL, 0x5F61ECDEF0B71FAEULL, 
            0x2F93BDD978597E03ULL, 0x81F0AE48E125AD63ULL, 0x2AF1B658FB58DEFAULL, 0x961D53860D551EFEULL, 
            0xBF50B3989B578C9CULL, 0x1814AE9E4FB2F382ULL, 0x273BA60B7E08929EULL, 0x45DDC75D33D2A4B8ULL
        },
        {
            0x76A1FE66F4286A76ULL, 0xDC7CD6770731FDA5ULL, 0xDBE2A03C797C8854ULL, 0x9092BDF58F1D5904ULL, 
            0x5B9FE62827824D8EULL, 0xC5015B72A830C924ULL, 0x5FEC91E5EFBCFEADULL, 0x49E21EC920D24F41ULL, 
            0x5E998805B921DC3BULL, 0x3BC57B12C0DA9961ULL, 0x965D9FEC89F47C70ULL, 0x0D6668B2DB71D502ULL, 
            0x8CAB693C357765FFULL, 0xB55ED9502528FE3AULL, 0x84048A650A203802ULL, 0x455A64BB86B67831ULL, 
            0x79A110FA12C9A006ULL, 0x1F9EDE8CE6E014FEULL, 0x84B7A6A0D9075ACFULL, 0x750E6CDD12400683ULL, 
            0x3B7636BA37BD4C88ULL, 0xFBFA582B6D066396ULL, 0xBB27CBFB381C1CEEULL, 0x0133825F72D804F5ULL, 
            0x8C8F1E0296757A09ULL, 0xD325AEB175A57D6DULL, 0xA715A01A8968F6EFULL, 0xBB090C6D50DEDD43ULL, 
            0xBFF3327E01125889ULL, 0x08EA805BF7B36447ULL, 0xA061CE79B8F2C107ULL, 0x6725969241CCF6CFULL
        },
        {
            0xFA54DB61C270AC30ULL, 0x89D5AF91030ECAFEULL, 0x2BBAAD0D48E63E46ULL, 0x534244FADB2471D8ULL, 
            0x6CC96B03E9CC2E6CULL, 0xF63512417E8097C7ULL, 0x39E523C944E9986FULL, 0x9B6B7BAC2217F651ULL, 
            0xBBB9A2E1A34EC3F0ULL, 0x5D788D95A978953FULL, 0x8781285A2483303EULL, 0x37957DA0A296E6AAULL, 
            0x5412B8F9E4E3F750ULL, 0x0C83F73F86B77354ULL, 0xC4FABB86A0D00623ULL, 0xF3F55D03E795E05CULL, 
            0xF3568DF2824132A6ULL, 0xC9DE4C962824A055ULL, 0x53C83C1029D25766ULL, 0x4B73B946AB68D0E6ULL, 
            0x1C2B4D4041EDBA0DULL, 0x33EB00392E333E93ULL, 0x4CA39B4E22473395ULL, 0xEEDD372DD56A86C4ULL, 
            0xD86B330096239FD6ULL, 0xCEEA19D30D7A8C56ULL, 0x85BBEB9C0B6EFE0CULL, 0x8C5891EBD1A66045ULL, 
            0x33B9A2725854987FULL, 0xD7498C28FEA1BB03ULL, 0xC50CD92E1F3416F8ULL, 0xDC4192D328307AA5ULL
        },
        {
            0x7BF9DDEA5FDC8AE9ULL, 0xA584493F4C6F9DA9ULL, 0x1F61C8E50F87E16AULL, 0xFDAE3A34D4D49423ULL, 
            0xDAB1C0C72E087F8BULL, 0xDB1317F1F65ED1B7ULL, 0x55A4783713FF1BC8ULL, 0xD6D116C698C08500ULL, 
            0x97AB474ABB1E1FACULL, 0x6B5582E2872D4A91ULL, 0x2D851355B87BFD2EULL, 0x866C07ACE42BE426ULL, 
            0x92ABEF47E61E702BULL, 0xBC2426221CDD5A20ULL, 0x7AAB04A0F8187212ULL, 0xF1C6BA1FCB4543B3ULL, 
            0xA9C4E86C383BE2A1ULL, 0xFD4E259E7C044CCAULL, 0x4ADCECE122CC39CEULL, 0xB6236843E50B408DULL, 
            0x22236E58592ADC62ULL, 0x8252FF2D7471EB99ULL, 0x9466394D34418B45ULL, 0xAD9260BE15A3BAF8ULL, 
            0xE323D79CC2C8C1B5ULL, 0x24B6BC72F9D25C11ULL, 0xFF10813DADB11B9BULL, 0xE509B65080AE867DULL, 
            0x6B9C4EC4E395F01CULL, 0x358242B2557381C2ULL, 0xD6C9DA746A1EBF41ULL, 0x28DCAE2F308B7F9FULL
        },
        {
            0xCFC26F0F40C34040ULL, 0x6DE57829B2B34FF1ULL, 0x299E3A6D02E3CE20ULL, 0x680B9835662B38A9ULL, 
            0x90C50E3D16794117ULL, 0xFAF938AA81446651ULL, 0x1C3F3359061496AAULL, 0x2260C52D76F5B5ABULL, 
            0xD85C5C2975A52023ULL, 0xD6BFE12EA400E806ULL, 0xE8ABDA2181B73DA8ULL, 0x4F1B5105341E680CULL, 
            0x784CB82C6569377DULL, 0x5737604E08F8AAB6ULL, 0x1175589CD82905F9ULL, 0xDDC2541D9E0DDB94ULL, 
            0x7D54F34E7FC0C883ULL, 0xA022037B02AB5098ULL, 0x446B62EEC3F39647ULL, 0xE97CE884387E6ECEULL, 
            0x3412A4DFA0A35AC8ULL, 0x4BB1811BC95560EAULL, 0xFF38C215B690EDA7ULL, 0x0583D67A87EAB7CEULL, 
            0x868D56321643C6DEULL, 0x5CE04FBA37D671D3ULL, 0xE25B9714719F0122ULL, 0xFAA4D4A5A89E2C88ULL, 
            0xE94C5726FFCDA5B1ULL, 0x1F47EFC00E2325B3ULL, 0xD9F535A2F226246CULL, 0x7FB78C8B4E30ADDDULL
        }
    },
    {
        {
            0xE124A847D4AF1416ULL, 0xA863120CFCD6D177ULL, 0x94267071E71A0AEDULL, 0x1B1A266C90AB47A8ULL, 
            0x14CB76D7EA80513AULL, 0x6234C85C3800B4E7ULL, 0x92C408C07CCEA85FULL, 0x02E3E22D0042E240ULL, 
            0xEA990F62AECF2155ULL, 0x4FBBC67F2F0E8A21ULL, 0x72984ED6AE9F2CE9ULL, 0x8068710A9026B1A4ULL, 
            0x3D9AACF3588AEF0DULL, 0x81977EF00006AEAFULL, 0x7EA60118E34BC0FAULL, 0x0B61854058A32DFAULL, 
            0xFB4D208651B217B9ULL, 0xAE42D684C0287B23ULL, 0xA3527E0CADA263D3ULL, 0xCFF1BF2385243AC5ULL, 
            0x7F8865A3CE6D5DFFULL, 0x042EEE0B46CD4B6CULL, 0x0BBACC07DDC2728DULL, 0xEDFF6A1B86B52B2AULL, 
            0x404C084A960D8772ULL, 0x39E6D254EC7FA374ULL, 0x04E41963D7974FD1ULL, 0xED98B39EE7A5690CULL, 
            0xEB52A8017BBAE324ULL, 0xE73AC44A88790959ULL, 0x90A489A91F1D96F2ULL, 0xA3B92952FB75322EULL
        },
        {
            0xDF445306116C137AULL, 0xCF2616A9A1140F60ULL, 0x16FD5F4D7A627C7BULL, 0x0F408518A160BF3CULL, 
            0xD92C5D37310F92A4ULL, 0xEC7055BD9ED70B1CULL, 0xC82FFD73B44FC743ULL, 0xC2B06024755F4D9DULL, 
            0x6EE391DB87857B36ULL, 0xEC643C05EECE222FULL, 0x36E55E746B2C23A6ULL, 0x9E30B979E4B1221AULL, 
            0xDA356F04519AE2FDULL, 0xBEA3EE637280B519ULL, 0x22B6518EE88D7114ULL, 0x53E8623CE479E8DBULL, 
            0x276F79C0A81A7A2DULL, 0xD40761EA1E2C4975ULL, 0xBD63032747984568ULL, 0xB5F4251B3C5206B9ULL, 
            0x5A596900CBBE68F8ULL, 0x79790EFCFD494836ULL, 0xE82AD40A406A224BULL, 0x12E6C0422A827FCBULL, 
            0x6F5058FB0DBCF1A1ULL, 0xB06D4DE4EED8E457ULL, 0x62421822100EEC07ULL, 0x859141FF6FD9DBE9ULL, 
            0xA6EAA9AD2DD832FCULL, 0xE18CE37C12F6997AULL, 0xA0BA109F57AD8A0DULL, 0x230599E3C87BEA2CULL
        },
        {
            0x66B3E7CFF4E3FF08ULL, 0x9F6C6BE16130134FULL, 0x366524539016E77FULL, 0x44EFE8F5C2F5FFFDULL, 
            0x20A1D96EF185C385ULL, 0x3A20F16AAFF18B25ULL, 0xF495938C464804F4ULL, 0x8E228E56156D8E95ULL, 
            0x6CEEAFB0FB0304FAULL, 0xEC42DB7D8C86B1FFULL, 0x3783FAD612A99373ULL, 0x2F1241C2B68849A4ULL, 
            0x8FA99FA9DB6B7B94ULL, 0x82CBE38174635912ULL, 0xD2E243FCE658246AULL, 0xEF8EC3B9D22F25DEULL, 
            0xB47F97ED2BE34936ULL, 0xD3BC4741888EB093ULL, 0x6F9297EFA63055B6ULL, 0x49C78F1A4A319E49ULL, 
            0xFE808AF5BCB044A3ULL, 0xA43751AD20F77741ULL, 0x87A1EEEF3FF2DD5FULL, 0x7D6DBB626A3F1208ULL, 
            0xB806B5A80472DC32ULL, 0xE15F9BAF93F4465AULL, 0xBD0A5AC67A92F3AEULL, 0xBE6EEB0443314332ULL, 
            0x847678C977F18E31ULL, 0x29320A61AE7C1578ULL, 0xAF26131DB1CF0EA7ULL, 0xC724CD7B6653989CULL
        },
        {
            0x9E0695910FCD0DB2ULL, 0xD591816D49D4EE9EULL, 0x9D2DE2CF940C5878ULL, 0xA7C18F15494B597BULL, 
            0x688E720C92F3C415ULL, 0x52A3628363FF9C25ULL, 0xA0AC6D9663DD19C0ULL, 0x1D430321459DAF6DULL, 
            0x0EB7D093309D5DADULL, 0x4321E463CDA9EBF4ULL, 0x8104BFC2B9146375ULL, 0x34DD4BF178E7267EULL, 
            0xA8D21E70E210385FULL, 0xA0044BA96FB995FBULL, 0xC7B9851B4FA44063ULL, 0xF41DA90AF918BEB3ULL, 
            0x21027CF1B8FF7310ULL, 0x8826155F5EE690A2ULL, 0x11C7A7491F580D5FULL, 0x939CF30332A04B4DULL, 
            0x814D439F32ECAE28ULL, 0x1F7EA7D9681CCE0AULL, 0x6B34632E54F2C5CCULL, 0x2226A0B34037C9CEULL, 
            0x868684605BE76607ULL, 0x6905EC1321265FDDULL, 0x698E3A3CEEFBF773ULL, 0x73F3D283CE4261B8ULL, 
            0xF838BEC470010816ULL, 0x777106E5EC6E71D2ULL, 0xA90B4C1B80D86782ULL, 0x9B48D08015D1325CULL
        },
        {
            0xBC08B35AC0AEB555ULL, 0x30E527FF690D3AFCULL, 0x549903C36FC5A0FDULL, 0xD32BECD1A8B0BBBBULL, 
            0xDEF0F2BB1B175E84ULL, 0xB58C173142AEF7F5ULL, 0x691B02CDED39153AULL, 0x9FC3DFD264930BE6ULL, 
            0xB8CA510326EB655EULL, 0xB0EB68FFAC98C19CULL, 0x75A5BB2B3B4E31D2ULL, 0x663CB3B934E36202ULL, 
            0x6C78C92665D2C985ULL, 0xB3B41B1861DC0BDAULL, 0xB4EF7B90181F6384ULL, 0x8193A28F69BF2A7CULL, 
            0x858D45A7B9043CD3ULL, 0x31DCCF4FF9F62C1FULL, 0x57FB3ED722B82AB8ULL, 0x64F0B5783EE6E440ULL, 
            0x549AD6CEC6E4BC47ULL, 0x1C62E7A3AF9DDE42ULL, 0xF1144D59414C0AF5ULL, 0xDF112398D1213967ULL, 
            0xE6DBE5F579296129ULL, 0x0D6DA7E74DF5BEBBULL, 0x982F645AB0F40A7EULL, 0x664034D79BF43E70ULL, 
            0x903968BA91082901ULL, 0x10647301EF802676ULL, 0x84C232E07D8D751BULL, 0x8806A98F36F2063CULL
        },
        {
            0x59F8F0502FB6FE94ULL, 0x98F7C1E35612CEF5ULL, 0xC48E0AE78781216CULL, 0xA92202153B91C5DAULL, 
            0xDA30AA4C36044EF0ULL, 0xCCC8CC3D47467405ULL, 0xED27F61FE0E4AE2CULL, 0x5FCBC2D54485B0FAULL, 
            0x0B582E877B0E530AULL, 0xC4500330FEB5000BULL, 0xFA2FCBC623A7FBB3ULL, 0xAF55EF3FBD960912ULL, 
            0x7388F8B81AF9894DULL, 0xDA1B8B8E73BF14D5ULL, 0x8A30E04D7ADB3F90ULL, 0x906709A661D4F7EDULL, 
            0x1B6D81ED0C7E676AULL, 0x42CFCB804E44CD5DULL, 0xCAE63C37AE209928ULL, 0x11473C43A90C3759ULL, 
            0x859DA46709038463ULL, 0x907214BAEB472ACDULL, 0x77CC5B04DF2911EEULL, 0xD707290EC9DBFE37ULL, 
            0x8605D89FCE523E10ULL, 0x53878F0C495B09A2ULL, 0xF71E2E613495B600ULL, 0xF10D2B4EEFE61D8CULL, 
            0xF0695A77C12BC4A0ULL, 0x68A12C4BF9456A0DULL, 0x71E9AA81A1EFFE56ULL, 0x56E58E7E7E86FE5DULL
        }
    },
    {
        {
            0x2015EAECD2A6C155ULL, 0x094E1EFCB634263BULL, 0x7557C81C5B3D5FBDULL, 0x91DCF5211A96B7CDULL, 
            0xBB0EF0DED61FBDBEULL, 0xB705A9CF458408B3ULL, 0xD2FA9108AB689AADULL, 0x727BE842FABF07C2ULL, 
            0x2E6872DD1A554B7BULL, 0x4CB379D6DF534C59ULL, 0xCB51C8F813A288E1ULL, 0xBC77CDA729106BE0ULL, 
            0x55E5ECE210F62B9FULL, 0xD4504BA8DD5AA1EFULL, 0x622A7334D6F985A1ULL, 0xA2811B8D8C61D7B6ULL, 
            0xCC7B9B98844DB160ULL, 0x8776E79F53E5BBC0ULL, 0x957A6D3EAB9EB6F1ULL, 0x8EAC4ACE3A32BD04ULL, 
            0x3C1DA0FCF5CADC2BULL, 0xBBB70BA76AD13980ULL, 0x74421216FE716B9EULL, 0xCD56B145B660E727ULL, 
            0x5A5A1D5EF41611F8ULL, 0x18EC0921548C6FCAULL, 0x96B10ED000A74D11ULL, 0x5F6BB195BC54296BULL, 
            0xEBF35BE9A4275902ULL, 0xC9F353D3082A7568ULL, 0x669EB713B19CA2BBULL, 0x15DC0356E3F3DBBCULL
        },
        {
            0xC0CC9EB614292BDCULL, 0xE858710D93ACA1D4ULL, 0x1E6E0606206E19B2ULL, 0x666FDD79A0DCE1F8ULL, 
            0xD58FEF904C167DA1ULL, 0xDCB2B0E05CD88F6EULL, 0xA770E8EED815AF33ULL, 0x95EE39F0E31AC809ULL, 
            0x1292534141E9ED14ULL, 0x599F59F89B23CF15ULL, 0xF8627188D0506914ULL, 0xBC97905859BCD1BFULL, 
            0xC19683E10972969FULL, 0x4B4F298D2448F81EULL, 0x555F5B43B01ABB40ULL, 0xD058877A849EE0F7ULL, 
            0x5A429154B40E3920ULL, 0x885F58B68F843D30ULL, 0x7922DB72FA4C6B7AULL, 0x4CC1A71050196566ULL, 
            0xEA09ADBEFC180E4AULL, 0x68F2B755AB9C4885ULL, 0x492680DBEF2AEAB1ULL, 0x6317CFCAE0711F54ULL, 
            0xB3099109F205A01FULL, 0x9530B43E471D4FECULL, 0x876FF6319E329153ULL, 0x3A63EE3D2A3BDAD6ULL, 
            0x870921B86B2BFF62ULL, 0xB21BDDBAA98D06FAULL, 0x981C01FBC6DDECF1ULL, 0x9E2527BB25267CBFULL
        },
        {
            0x0EEC93E8D4638EB3ULL, 0xFC7113DAD0B1B10DULL, 0x83D40FDB2C731AE0ULL, 0x5994930387AC4CEFULL, 
            0xC23BFB288CD2545DULL, 0x39495DE43D5C7D3FULL, 0x7FA8209F89475437ULL, 0x82F64FC54F233EDEULL, 
            0x8A6D325A289A623BULL, 0x0B20EAAAFF627AFDULL, 0xFE092E1F99CB0817ULL, 0x31516575D489FF67ULL, 
            0x23132CF73C13F0B2ULL, 0x411C9B40A945F18EULL, 0xF3C84C378F4E4543ULL, 0x39C9913A7E856D68ULL, 
            0xF48CB28FC1786FB0ULL, 0xEA059E81D8620D43ULL, 0xA047120AD2A74FEEULL, 0xE8609C0888600B45ULL, 
            0x1E6BDE46A42EDDE5ULL, 0x27078907294F731EULL, 0xA800A40C3431933AULL, 0x7DE76C239D2A3BF7ULL, 
            0xDAA098F4E8314012ULL, 0x44B5C3FB46F6BC8AULL, 0x36BFD44E084C2DEFULL, 0xA2BE76C8309AB898ULL, 
            0xBBA598C7DDBB9E98ULL, 0xDEFE283495AC155BULL, 0xACED50FA17EA1809ULL, 0x801372EE6AFA23C5ULL
        },
        {
            0x58BC24D4D4B79A04ULL, 0xBFBCC798DB22A6DCULL, 0x1A5BB21318AE0156ULL, 0xD7C12B70744515A0ULL, 
            0x80FB756CFB215BEEULL, 0xB39932C33B8630F9ULL, 0x401C8F47D58D9883ULL, 0x579647AE8E029BD0ULL, 
            0xAEC6D70A592AD874ULL, 0x861CFDDB5A706637ULL, 0xF11910055B3EF564ULL, 0xCA97B4ABCF1650B1ULL, 
            0xCF5D8A8EEB41B1FCULL, 0x6AC4E69A341BB257ULL, 0x049EB4E57C5AA091ULL, 0x262FFFE652721A7BULL, 
            0x2D93BA62A9A56D55ULL, 0x9E3755E5B1301680ULL, 0x5CD31FD986FDB72FULL, 0xFC1AD5311DF011FCULL, 
            0xBAFE407FDA418ACDULL, 0xC171CF79C18BB5F6ULL, 0x4091346F0565A22EULL, 0x936B9B47EA19E049ULL, 
            0xB0F083FDDCA0727BULL, 0xD3ABF64324F50E31ULL, 0xFBB0A3E780BDED09ULL, 0x7590D67A5A00B40AULL, 
            0x6135C1DF62F824B1ULL, 0xE2F9127BB4F668FCULL, 0x51A10981D8352E59ULL, 0x2343927E040BD344ULL
        },
        {
            0x373EF55427E3AFC3ULL, 0x30C5C11A34786A10ULL, 0x79E3D100C89A9ADDULL, 0x746E26ECBC8FF59BULL, 
            0xB28C6B9C654E3F63ULL, 0xCAB133033E33C47DULL, 0xFCDE0966650CB9CDULL, 0xDDC4E78E431ADD2AULL, 
            0x23562DDC5B9B6FD6ULL, 0xA78F35250EFEBF7EULL, 0x81D96F8CA8F50679ULL, 0x7BAD5BFD0A270755ULL, 
            0x31356E247DC9C0ACULL, 0xEA11DB04B3EA4788ULL, 0x31A2CCD51FBC9D73ULL, 0xCD10697F0D0793BFULL, 
            0x5160414EB51F909DULL, 0xE2BADCBF11712664ULL, 0xF80DCCDC64FD3E7DULL, 0x967EA013958784CFULL, 
            0x4B11E0E34642C00EULL, 0x51467C8741C5AA57ULL, 0xF1DC520865A1352CULL, 0x5AFA0D14C67FF99CULL, 
            0x9A0A67CE07387327ULL, 0x554DBE007DF8542EULL, 0x0778D00156D5DEDBULL, 0xE224032556795D7CULL, 
            0x6DE43CA2C4D41ABBULL, 0xE2E1B5FB2542E829ULL, 0xFD7104D43A53D34BULL, 0x971D70F2BDF871DFULL
        },
        {
            0x490AFBE76539C792ULL, 0x5323D9739B4D884CULL, 0xE7A2D2D17A45B640ULL, 0xF68D4736DCB5D4D7ULL, 
            0xDE7E2C59EA6E7347ULL, 0xCAF00E6A87141089ULL, 0xD6536ADDB58FCB4DULL, 0x833B38B786715691ULL, 
            0xE28F39AC1EF5148DULL, 0xBC43FB724867B921ULL, 0xF42DED7C224D7EB4ULL, 0x7BAFE20946AC1275ULL, 
            0x1D4694EC1CA0EE26ULL, 0xE000BCE4793CAB40ULL, 0x72D30724825F089FULL, 0xBE73B77B23B758D6ULL, 
            0xA8C1305DE76706FAULL, 0x17DD4B2743FBE18AULL, 0x85646F3F44CA78FBULL, 0xA43EE71FA3BFB526ULL, 
            0x668BCD8042FF1622ULL, 0x86DFD4EFC22C4B00ULL, 0x264B8EBD5A179B21ULL, 0x3989D3E3391FCE9FULL, 
            0x7BE115023D24C444ULL, 0x3E5A2F1CDACF5D5DULL, 0x7B522C862F0576EEULL, 0x5533FC6B7BEF9CFCULL, 
            0x9CA0D173967E9688ULL, 0x4BE7F834C8D238B2ULL, 0x26CAC6DF5A9A876AULL, 0xF8D3EE769A32E33BULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseFConstants = {
    0x1C22F219DA29C5FCULL,
    0x19B84CFD25BA6DA8ULL,
    0x8F0E2A0CD95AC31DULL,
    0x1C22F219DA29C5FCULL,
    0x19B84CFD25BA6DA8ULL,
    0x8F0E2A0CD95AC31DULL,
    0x7975D141CF7D1489ULL,
    0xF0F6193982116796ULL,
    0xBD,
    0xD6,
    0xCA,
    0x4E,
    0xE1,
    0x53,
    0x4A,
    0xC1
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseGSalts = {
    {
        {
            0x2E182823397DBAB3ULL, 0x8FFD261DA8963528ULL, 0xCA5D585764F85844ULL, 0x27AF41E9095AD722ULL, 
            0x1886F10DFE101752ULL, 0xE24933127A13F7A7ULL, 0x4CF45EC5B7D100EEULL, 0x1D60934C5C6A0AFDULL, 
            0xCF13E852F550EC32ULL, 0x8B5C92BE02916B2AULL, 0x7E3712965E28FC79ULL, 0xF4D84D51E31EC9C2ULL, 
            0x60A3CFE4181FF3F6ULL, 0x83F70E890277249FULL, 0x16FA3871D1EFBD19ULL, 0xB47F5DF39C276ED8ULL, 
            0xA83E388685BCFFC5ULL, 0xFD4CC857D47A29BFULL, 0x20D557247B53D898ULL, 0x5E45165ADA4B85C9ULL, 
            0x2189C8DA06B345B2ULL, 0x0916D34D0F131EC7ULL, 0x39751B0718643ACBULL, 0x0B87FB7F0780B8C4ULL, 
            0xAFBDFE15CAA497D6ULL, 0x11A710ABA1475872ULL, 0x2D77756360E66367ULL, 0x191979FE74240E8FULL, 
            0x43F8331AB4951DDCULL, 0xB83A3B42CAFBD85AULL, 0x35FB816990D14667ULL, 0x7B81AE5388948489ULL
        },
        {
            0x418C7CE55D213CFFULL, 0xD46180C84B0B2575ULL, 0x5E7C6769F5CBC3FEULL, 0x6660EBDA048C1379ULL, 
            0xEC4709AA5A9D7594ULL, 0x091005E0CF7073D0ULL, 0x24835D1EE85AE8EBULL, 0xFEFF8740BA2915EAULL, 
            0xE141A7812C85D6DEULL, 0xC9E398A1B4A2F49CULL, 0x44DB2D20DD3B9364ULL, 0xB70F60DD901DC596ULL, 
            0xC5EA8487E150B5A6ULL, 0x76CADA4669811CFFULL, 0x39E89E0684E3E08DULL, 0x31BE99CBC39A3259ULL, 
            0x0FA3B31362DF6DE8ULL, 0x785907027A61F101ULL, 0x987F7656299071A7ULL, 0x0AFF8F6E29B6FD1FULL, 
            0x64803931667188F9ULL, 0x76DA1AC59DCD5A6FULL, 0x0A8F00C47E16F7E1ULL, 0x209691EE3591D801ULL, 
            0x1350CCC0DDB12ED8ULL, 0x264AC21A5DD1AF32ULL, 0xB122F457745B03A3ULL, 0xDC7438414AF0B708ULL, 
            0xAC657A64AA003699ULL, 0x98AA99EFFABDBC01ULL, 0x62BAF8D0B227B1B7ULL, 0x5E3BDBAEE033399BULL
        },
        {
            0x06EB5C3F3680770CULL, 0xA829851C3BAEF78BULL, 0xD7D9C99557CD7914ULL, 0x6B0A4757161C9DEEULL, 
            0x2172FC8179E4A42DULL, 0x3FA3B3E9CBA6EE29ULL, 0x6C2048FD65CD8223ULL, 0x45ADA85E81626CD6ULL, 
            0x1F5715CB6FE095AFULL, 0xD55340A87C42DB50ULL, 0x6A4F4153D39F40A1ULL, 0x4385BC7BE966AE2AULL, 
            0x2B12EC61CB9CDBF7ULL, 0x5E9CB96485C1EC72ULL, 0x6DBE5F1A2FBD3311ULL, 0x040A39E192662F90ULL, 
            0x420129B1F1331704ULL, 0xE3FFA0D0AAF2C928ULL, 0x0CECF4FC39490D0EULL, 0x6D14DC26F84D0A96ULL, 
            0x0381DF2447042246ULL, 0x3041475C67ACFD9DULL, 0x2D271C9B0FD21675ULL, 0xBB64679DE083B47FULL, 
            0x7FBAF00E32DC4529ULL, 0x498FA56FF9FF572AULL, 0x68226C5C476D40B8ULL, 0x850C03AA8798CEB1ULL, 
            0x4177EBD40A8AFBDEULL, 0xD9BFC873D355B442ULL, 0xCFDCE958FDDAA094ULL, 0xB8496BF80904DA5BULL
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
            0xC1D28AC8D7BFFB74ULL, 0x38DAE7ACF10130EDULL, 0x166C1359C2713881ULL, 0xD6374749E0EE71A0ULL, 
            0xC97104862D9E0D6BULL, 0x9D73B94B37384DDFULL, 0x945390D11962871DULL, 0x663E0D6EC441C7C8ULL, 
            0xF189C677D9454A60ULL, 0x0DED22AED5B9CC40ULL, 0xC7E67F23058DFA4AULL, 0x6D346E46301F792AULL, 
            0x15566DE349FCD440ULL, 0x6847DC46AE074507ULL, 0x90AF34274D8CE9FAULL, 0xFB141958192B5BFFULL, 
            0xBE77D62F059FB726ULL, 0x968987C4570973C1ULL, 0x810F36A69DA09AF9ULL, 0xB292E425E2C4DD05ULL, 
            0x56578B647E56EF39ULL, 0xF67252D76492A4D0ULL, 0x2CDA0182DD5AA7D1ULL, 0x7112D829B6AFB939ULL, 
            0xA9D2ECEC3FB0A6DDULL, 0x29AE73D8E99F30C5ULL, 0xF068E67DF776ACF5ULL, 0xECDD62CD8B22010FULL, 
            0x1ACAE5ECA98001CEULL, 0xA8E771E9730CBFD2ULL, 0xBC16568CAE2657D0ULL, 0x7D002BCFEEFF3976ULL
        },
        {
            0xFE551BCCCA5AE46AULL, 0xE77B3C7B504F5FEBULL, 0x96DFDA3407F42CF3ULL, 0x49CDFF593E3C2958ULL, 
            0x909C49282FBCFE2EULL, 0xC0B82665DFADDA91ULL, 0x7AE370761F98EDA2ULL, 0xC5C8D3963184D7CEULL, 
            0x485ADFD6BAE234E1ULL, 0x6386131DE2C7F069ULL, 0xF989D602DCB2E5DBULL, 0x86802B30DF99DAFBULL, 
            0x08CEA904CA6CE05EULL, 0x8F587DC4A01A13CCULL, 0xB6A95566133C16FFULL, 0x72F1FDC0EC9A79A9ULL, 
            0x18F183F11E68FCAFULL, 0x15531CBDE5C6E950ULL, 0x47A7F2247883AF9DULL, 0x434083827EAF9FC3ULL, 
            0x2C26EF6437E14944ULL, 0xDBE9E04D6D0DB782ULL, 0xBDB85D30633220B9ULL, 0x145A02E141353B91ULL, 
            0x47A37CB8781C052DULL, 0x1D4427EB664ECD88ULL, 0x6435407BEA8265A2ULL, 0xD4C2B8FFECCD4243ULL, 
            0x87097C2096F218EDULL, 0x2ED3E9370427D8F9ULL, 0x3ABBE3333AC858E8ULL, 0x2BF1225ACFD5C6D4ULL
        }
    },
    {
        {
            0xDE73863DA64949CBULL, 0x2F494833AA6AE1D1ULL, 0xCB924F3FD638BFCCULL, 0xC00BB3CBF4FC9943ULL, 
            0x9999A4EF2635C438ULL, 0x7CABF4038C4B97E4ULL, 0xD5B95D75A2D2A8C8ULL, 0x767C2882270FF6D1ULL, 
            0x92D84BFC741C34B1ULL, 0x30DCE1956C0C73DEULL, 0xFE5B5748163C1453ULL, 0x878A65514847D150ULL, 
            0xF0CA79A2CB0130D3ULL, 0x816D7A1B8C409B3BULL, 0xBA9DF793333BEEFDULL, 0xA7F2ED1209897146ULL, 
            0xA986288D264A385DULL, 0x29961BC5C0550F79ULL, 0x65B5C1C9C1273F8AULL, 0xD97B7D43F0B30737ULL, 
            0xBF65A5C7115BF1A0ULL, 0x1812D6B6233F2F48ULL, 0x61E22CF3C2311B4AULL, 0xE15BA6723E953F9DULL, 
            0xBA730117282EE412ULL, 0xBDD7E26FE6B83E03ULL, 0xE28B72C448196017ULL, 0x1294B6BC8B2B5F95ULL, 
            0x4131607E2C1818FEULL, 0x3483EFBCFB01225AULL, 0x300779D55E92D549ULL, 0x87563F1797AA6A0AULL
        },
        {
            0x3DC7201C7F256FBCULL, 0xFC85B0FC6700D810ULL, 0x1296FE13B06A4EF8ULL, 0xEB41749A9A366AC4ULL, 
            0x6359B25726F64C63ULL, 0x9C9C520E2B1097B5ULL, 0x1790B34A2ADF37D8ULL, 0x1854840003FE9AD4ULL, 
            0xE5A734DF9A06630CULL, 0xDD1A7AB2117AFD39ULL, 0x831A76479B94028CULL, 0x33C13F76663A4F2BULL, 
            0x26EB697930BF2194ULL, 0xB0193A02E3C9860CULL, 0xF1BFE35748C8800EULL, 0x02A12B9EF72FBC1DULL, 
            0x2BF7EEA6107723A1ULL, 0xDD893394AF225222ULL, 0x2EEF97D196485789ULL, 0x59B785AD05BB97FAULL, 
            0x6BB9EE0879E1D4A7ULL, 0xFE7815F69E901AD6ULL, 0x236B90AD67293D06ULL, 0x0CE244EE080AF7F4ULL, 
            0x9776454098D78F34ULL, 0x59DE56F7CCF81B53ULL, 0xF216266BEDDC183CULL, 0xF35774883C2CC3D4ULL, 
            0x8E419EF686712D7FULL, 0xA2FD441A9B37D054ULL, 0xE48903AA9E152367ULL, 0x6A843D4CDEA48B7FULL
        },
        {
            0xB27C0FAC8851C37DULL, 0x12CDC1006D90EE03ULL, 0x0104C418A8F5153FULL, 0x98FF619B585B6887ULL, 
            0x3767D7E87D8CA191ULL, 0x03CA17565CEA401AULL, 0x3818A60D4EF894FEULL, 0xFFD577DB4AB5609EULL, 
            0x430661EE636A3E27ULL, 0x9F444481A6468654ULL, 0x166E726847CC9820ULL, 0x7B35C6875B5926A3ULL, 
            0xED691034DB832EBFULL, 0xEF11E02DEB4E9087ULL, 0x1F309B537292DA29ULL, 0x7A6D0FB9292E9206ULL, 
            0x43EE4BD6AD994551ULL, 0xBE74274A7C8C021EULL, 0x4DB853CF29A64851ULL, 0x369F1B7E823E6CAAULL, 
            0x537FA54B645BA795ULL, 0xAC48730FD36120F7ULL, 0x63B3ECEDEA6713ECULL, 0xE529EAC57BBCB939ULL, 
            0x2E8D400202CB98A4ULL, 0x2028CCD355D2256DULL, 0x4F86975164FA5BB4ULL, 0xF664EA030B117677ULL, 
            0xD65FF1F6E7819873ULL, 0x9DE4B83AEB2A416BULL, 0x8B09CF1B7E1D741BULL, 0x90BD0CFB7BC78DF7ULL
        },
        {
            0x8BDFE1C8EE41C864ULL, 0x67238C9A1410857BULL, 0xE1B3CC318B378178ULL, 0x56A2E6498063E839ULL, 
            0x6DD4B3BAECC419B6ULL, 0x78425E4BAABF597EULL, 0x2ED5BB9D2D37C838ULL, 0x2B3C62B6995257CBULL, 
            0x977905499AA55885ULL, 0x3FE6DB39F47DD7A9ULL, 0xA7563A50CFD0F442ULL, 0xF41016E52BFFF224ULL, 
            0x576D16ED9EE0C8EEULL, 0xDE1A4E8AD585AE2FULL, 0x5A5FA9E546F62C2EULL, 0x4052A5FC07D29998ULL, 
            0x4F1327D10C34D0DDULL, 0x58DF9A388EC28750ULL, 0x82583677232C6CBCULL, 0xFB7B9050672C49FDULL, 
            0xEA2FFEA6751DA422ULL, 0xC7B7221F685380EBULL, 0x262D6C34CFF759A6ULL, 0x9B1D9564BCFC48B9ULL, 
            0x42162B8A193676AAULL, 0xEE6ABDB3D4EF81C8ULL, 0xBEF6D402E2216AC3ULL, 0x6E87D1828D33E83DULL, 
            0x5E4E8AED41B0AF99ULL, 0xCFCD4E937D6BA697ULL, 0xD3F386C0F46475DDULL, 0x25A6BCACCFDAC6A6ULL
        },
        {
            0x391F90188F6EDF1EULL, 0x3375CCF8F4680C4EULL, 0x17B1D94ECDA9053AULL, 0x3E09D561C5F3EB0EULL, 
            0x14BADF7E4DEAFA8FULL, 0x114047E192BCB2B4ULL, 0xA82B3A9379B4DB08ULL, 0x6D2F68B18ED9007AULL, 
            0x5C618B35827E7C02ULL, 0xCB0FBFF065B21097ULL, 0x6AC3C9F8AF9A2143ULL, 0x6C5018B561092B98ULL, 
            0x7204611BA3A33478ULL, 0x186E469630253406ULL, 0x83253E2BD2DC8FC1ULL, 0xBD60ABAC22BD631EULL, 
            0xFA7443104C3C2636ULL, 0xAD9D0083CA0A18D0ULL, 0x7AF07A8ED012C909ULL, 0xA8533B1019033BC2ULL, 
            0xBF4212CCF364246BULL, 0x1010443754C9E83DULL, 0x2B2FA6ED8395B588ULL, 0x3C7323B336E4B0CDULL, 
            0x324771BA520DF75BULL, 0x9E5C68265F14007AULL, 0x9710359BAEBC83B4ULL, 0x555E98DAB1C26FECULL, 
            0xE856816937B9B2EDULL, 0x49ED7B167EC3725BULL, 0xC20DEAC666C7C981ULL, 0xAECF4F4A27F7F204ULL
        },
        {
            0xD1CC6B2D9DE0D893ULL, 0x7B06512C1FE1AD02ULL, 0x5E9DF0B52F49DD6BULL, 0xD2824223933F68EAULL, 
            0x31EBE1EB5CBA0DC7ULL, 0xA5CD71D3A2FB5F33ULL, 0xA1E8CD6C2DD64388ULL, 0x54834D2D79A73F86ULL, 
            0x64D7256C5A70B97AULL, 0x0A466AE2606C1293ULL, 0xC37FF39209A516ABULL, 0x61632B364AB82E54ULL, 
            0xE7A7F30F5DF39DEEULL, 0x3F2E8371382F7488ULL, 0x7D5B43E9DE9D69ACULL, 0x0586C150AFD41A12ULL, 
            0xB33C2231CB1E3DE3ULL, 0x26791112A46FBCFAULL, 0x6830F16BD514AA74ULL, 0x4866C1F72B61B6CCULL, 
            0x2888CD2090C22B80ULL, 0x9D109806D7A3EBDDULL, 0x1B46578420922641ULL, 0x1602CD3CBE8BD34DULL, 
            0x945C3D62E6A8B77CULL, 0x79357254E5E0E165ULL, 0x4FDF58840692DBE7ULL, 0x75ADF91E60E35FDAULL, 
            0x4100FB94C8E7077AULL, 0xBA6C31ADC0358C95ULL, 0x0B7E73ACFFB57BBAULL, 0x8432431940B9535EULL
        }
    },
    {
        {
            0xBC434B201701BACCULL, 0xB5A9025AAAF82A88ULL, 0x4A11F671ACB9E6ECULL, 0x5039D14B0F6D9FA6ULL, 
            0xBE498C7C33D729F2ULL, 0xDFEE9EBCBA61A9AFULL, 0x5B7974E016386A80ULL, 0xE4C0FA6D7FE6ACAFULL, 
            0xB7128CA9FF1C4687ULL, 0x7A7274D29996EFFEULL, 0xE77D0ECDCB1462F2ULL, 0x9B0DE866F197C3E1ULL, 
            0xE771F5FE0271E26FULL, 0x1554E8F047DFCF25ULL, 0x5DCB86C5872BFF91ULL, 0x60BCDF6CF6C5023FULL, 
            0x9CE7F73855432A74ULL, 0x54228528B089B71AULL, 0x14D4F709F55D9D5EULL, 0x85EA8FDBF5EBB2E0ULL, 
            0x11DFCF01E4B91AC7ULL, 0xF2FB3CC08EAB8A4EULL, 0xB3FFBCE8740C48E3ULL, 0x564B7EB7AD21FABBULL, 
            0xA0FB52FE30E2EA6FULL, 0x00D1B846304FDFE1ULL, 0x59ABB68D635FB881ULL, 0x29E06ACC0E72F7FBULL, 
            0x53AB4F44589DDF77ULL, 0x436B2EB7FF639D17ULL, 0xC34396A537D0D360ULL, 0x8E8B95118B07FD84ULL
        },
        {
            0x308A1C68D3C68055ULL, 0x3E9657901B5DC1AAULL, 0x9BBDD808479A5E00ULL, 0xBA03C3E4C0187FC8ULL, 
            0xA7704663F3815F34ULL, 0xD61255552AAA722BULL, 0x51475ED42F100890ULL, 0x3DA1FE5CC736088CULL, 
            0xE14B2AA27987C077ULL, 0xDE1CA6CEEB3900ACULL, 0xB1FFE356B3D3E1D4ULL, 0xFA182DFB851CD06CULL, 
            0x4A6D67BC7D0B3FA3ULL, 0x8474CD3112A83B50ULL, 0xD605D72E91E63AE0ULL, 0x549BA2C0C3B903F2ULL, 
            0xF2482CD1DA3ABBFAULL, 0x256282C89DC1F035ULL, 0x7AA591671E99CD0FULL, 0x9B948E221E41999BULL, 
            0x9E3FC5B1A78D0733ULL, 0xB1EE272F8E2E07D9ULL, 0xC13C01B4B863CDFBULL, 0xCAD88110A03AF5FDULL, 
            0x6D3DB39D0734D4C9ULL, 0xED980714DFB3DF30ULL, 0x1D187E25F6ECDB6AULL, 0x28CF08439AD14DCDULL, 
            0x8A61EF490826209DULL, 0x2CB4C993BA2D6070ULL, 0xDAA8EDB33FD30A3BULL, 0x01774FEF1F43D343ULL
        },
        {
            0xB24168EC719B7544ULL, 0x92F13421E059A476ULL, 0xB241F57224829321ULL, 0x39B688255FE05F81ULL, 
            0x0626858F7480D325ULL, 0x09313133C81741DCULL, 0x4810EE2A93FFE33BULL, 0x13CCB1FC00513414ULL, 
            0x567AAA2FE9C4E404ULL, 0xB74D32A87C52CACFULL, 0x909F93E04EF7360CULL, 0xEDE398BEFDED9B5CULL, 
            0xA6F3BAA464483E4EULL, 0x086E351335EE617BULL, 0x64EF2D745AD5CD85ULL, 0xC5E24540501B62F9ULL, 
            0x7217826A6FE17BA1ULL, 0xB3734372ADE56DDBULL, 0xD9F06EB70DFEF1C8ULL, 0x2CF16209920041C3ULL, 
            0xA9A6C9945BFC3489ULL, 0xB44135994BC5FC34ULL, 0x41624D02E6665659ULL, 0x8703C0ADF5879D91ULL, 
            0x30633566641E73D3ULL, 0x8182B7A514B0AAA1ULL, 0xACBE187438B4A792ULL, 0x953E298D3C616BE1ULL, 
            0x75F71E77FC5321F4ULL, 0x3FCA89B4A00E4AAAULL, 0xAD4A0924DCDF05F3ULL, 0x40DDF1A19D7D758EULL
        },
        {
            0x9BFD29C24C5A0013ULL, 0x2291B28BB4466ABBULL, 0xC0F549DFCB0244A4ULL, 0xEDC1B4BC700B7051ULL, 
            0x9CAE1CA8DD14D098ULL, 0xF14A9EC8FCD12634ULL, 0xDE209AC0083C4FD5ULL, 0xD4F9668AFEDDA8F2ULL, 
            0x754C2630305C8428ULL, 0xDD8759B59207D6CCULL, 0x8BA07E3956780095ULL, 0x95E9DA5D3E327AF3ULL, 
            0x6DDBBE11774F2E12ULL, 0x6FD8A72EFEF6F806ULL, 0xC768A6053A3B7973ULL, 0x1CD3CAC64DD7AA81ULL, 
            0x7B627D46D5E01083ULL, 0x1572960DB9DDC829ULL, 0x4314D2E5DC4389C4ULL, 0xD5A0796C3C4C2EA5ULL, 
            0x02C555AD130B5985ULL, 0x6D15E49835BC7053ULL, 0x14B61C20569422A4ULL, 0x30CFB5DE4D9B544BULL, 
            0x2F9DBAFD344EAC2DULL, 0xE4C47A02689D3C8BULL, 0x883C0F2CAF82A979ULL, 0x581E7136778308D9ULL, 
            0xD4A49917D751F869ULL, 0x7CE15B470B7F794FULL, 0xD700AE2A5653E426ULL, 0xA95F1D9B93A75589ULL
        },
        {
            0x60D4738278023B32ULL, 0x88F16D601D252FC4ULL, 0x152B86F72ADF33F3ULL, 0xBBE9382FA93263B7ULL, 
            0x41566EF716936876ULL, 0x49EE6C923448F43DULL, 0xA001F1E9FF01AA18ULL, 0x6013A127F47613E9ULL, 
            0x648CCEF2CB496648ULL, 0x16BF56F62252C173ULL, 0x83F7E407D4071C08ULL, 0xC3A60ADC85A93B73ULL, 
            0x908E506FF92188F9ULL, 0xC9F6A0BD051E4DC2ULL, 0x336CE240386F8306ULL, 0x65C8205132270414ULL, 
            0xD0A201D3E57E97FCULL, 0x978D68B678721AA8ULL, 0x703CCBB43D336C64ULL, 0x7FACC30B0F829967ULL, 
            0x86BC6F5F38ACAF5DULL, 0xB127D3B2C55FBE03ULL, 0xC8B57843DEDC189BULL, 0x1FB20B9777224442ULL, 
            0xBB0EF2652816976CULL, 0x75EF5CE2445D1395ULL, 0xC2861A71E146BD44ULL, 0x32C61ECFEDA819C7ULL, 
            0x8C9EC345151005BBULL, 0x533173792C840E2BULL, 0x0460BF3DF2A195FCULL, 0x16A202FA3C33F2F9ULL
        },
        {
            0x5C78F6D723D3EBBDULL, 0xF778EA75C1BF1837ULL, 0x6FB368F0B26184D8ULL, 0xB55C535B7CDA698BULL, 
            0x22EC5C9E92308E71ULL, 0xAD60565ED457E925ULL, 0xD0A1E758B45B47C9ULL, 0x4EC7CCBF860C97FBULL, 
            0xA3BD12DC6DC21C79ULL, 0x8EFA456817496A64ULL, 0xC48BD579E8005633ULL, 0xA9962BE9C87E783EULL, 
            0x8059C13A953595BAULL, 0x95E6412856E2B99DULL, 0xADBA59B67A81FD2FULL, 0x28037ACDD2615898ULL, 
            0xD2C34439B7D822E8ULL, 0x5B50A7B9B2C491B2ULL, 0xDB5C996F604B25BFULL, 0x74B087F1307A6075ULL, 
            0x114204BFCD9368ACULL, 0x55D78B4DAE4F95C6ULL, 0x701600C47896BD02ULL, 0x4B6B0717ABD0774DULL, 
            0x033DCAF5FE265F60ULL, 0x504271272A05827DULL, 0xDA007C3D8CE34B2DULL, 0xB2BDC24AD3D05D99ULL, 
            0x4770F8FABBF00FB0ULL, 0x81D8538F980B7139ULL, 0x0DF7CD8C909E01A3ULL, 0x2C6FF865F178558FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseGConstants = {
    0xD0717C48B84CEAA7ULL,
    0xE8AECD56FE5CE924ULL,
    0xC953A7B9B5B4706DULL,
    0xD0717C48B84CEAA7ULL,
    0xE8AECD56FE5CE924ULL,
    0xC953A7B9B5B4706DULL,
    0x59144BD988E6BD4AULL,
    0x65C5816CC9122148ULL,
    0x58,
    0xEC,
    0x54,
    0x8F,
    0x72,
    0x24,
    0x10,
    0x97
};

const TwistDomainSaltSet TwistExpander_Arcturus::kPhaseHSalts = {
    {
        {
            0x625C04DA5782BBE9ULL, 0xF96581AB26523411ULL, 0x2BFCE688F12E5A4FULL, 0xAACB2F3A23C187E5ULL, 
            0x4C81B7EE6E1DF0E6ULL, 0x721094D4C642620EULL, 0xA8F43214C34F7E0AULL, 0xE9BA70C812BDCBC8ULL, 
            0xE725C2C58ABF851BULL, 0x054FF8B61F132642ULL, 0xF92D06564FFD9841ULL, 0x4A2CD415FCF0760DULL, 
            0x1F8B5C2708C7A6B7ULL, 0x43238E92F8D712B4ULL, 0xD442F0E66F438083ULL, 0xCA390C00917792CEULL, 
            0x8BE62CD284E00624ULL, 0x435B307428A1B1C0ULL, 0x73F18EC7CBDCCC54ULL, 0xDA913E5931AEDBA1ULL, 
            0xA2DB723E2FA362A3ULL, 0x4BDEEFFF19A3D3FAULL, 0x87AC653B641A0C7FULL, 0x3274AEC625F09FF4ULL, 
            0x728F551DBBF05C18ULL, 0xCA9A409226E0C2C9ULL, 0x9E877C9AF491B428ULL, 0xE18B1F270C691980ULL, 
            0xD511CFE2FBF54697ULL, 0x6832C3515D192FBDULL, 0x69D47B4CBF003A6BULL, 0xB5F51840326ADDA9ULL
        },
        {
            0xB0BF3FE31C72C5B2ULL, 0x46610F1FDDF91FF8ULL, 0x5E9A8B1E24537ACBULL, 0xD874902989C1BDE9ULL, 
            0xF88620D1B2FA4946ULL, 0xB664B045B06196EBULL, 0xD91AB2D07CC9F2AFULL, 0x73891652F456C11AULL, 
            0x0C7922DD2DD9B8CAULL, 0x6153673C63FF361CULL, 0x583D50E870A60810ULL, 0x71E12C6FDF46BBBFULL, 
            0x88C587FF1EE2131EULL, 0x5CADE348EFF32BBBULL, 0x2BA36C7487871F2CULL, 0x5A6B41B32F4F5EE6ULL, 
            0x5ECD7A8BC74C139EULL, 0x494E05BE8177BD03ULL, 0x9741D419AB4B470BULL, 0x04043C82CFE0054DULL, 
            0x4EF4257BBCCEC32CULL, 0x4A3063A68987B108ULL, 0x984296403F107A82ULL, 0x30A3610B3F3C231AULL, 
            0xD2E8A921730DE644ULL, 0xEC67E5A906BF5903ULL, 0x36CF779DDCDFF44BULL, 0xC0311F495C7A1206ULL, 
            0x103D110D697BC774ULL, 0x2B86BD9C599E4736ULL, 0x5530628421F8538EULL, 0x546368CAAF12547AULL
        },
        {
            0xB16E66A5041652A7ULL, 0xE9FF3FE90C300C7FULL, 0x5E24C34C867AA54EULL, 0x1E4D8C32F55950A6ULL, 
            0x659DB83557000004ULL, 0x640104BF6A9C1BCBULL, 0x1A8B3217E7D76708ULL, 0xD67383D005A23F9AULL, 
            0x4C484898B084A497ULL, 0x31E977714C8AF30BULL, 0x7AC4B92D1D5AF0E2ULL, 0x9EE27AC07D0B722AULL, 
            0x7BE51EAA296E3FFDULL, 0xC7C2DB043A504009ULL, 0x11B221459A763A24ULL, 0xA41EEA939BBD62B8ULL, 
            0xC9AE16B2CF8B449BULL, 0x7B70D98F55154B25ULL, 0xFC6C2E24CCD661D0ULL, 0x886A0C4FE31D5DF1ULL, 
            0x5A9B9CFD7A3C18E6ULL, 0x832E9DB29DCFA096ULL, 0xCA0F2A969C7018EDULL, 0xDDFD2B13EF2A334DULL, 
            0xD7EC42A8F34349F5ULL, 0x9A40E69532053284ULL, 0xEE1FD8835DCCD90DULL, 0x0FA734103A9B6F2BULL, 
            0x3BCAAA4FDBA5C669ULL, 0x320E42253AC79B57ULL, 0xAF61CF112E1B010FULL, 0xDC641AF0F486CACFULL
        },
        {
            0xBD4E0A1EB8AC296BULL, 0xB8B0775C33412E54ULL, 0xBCAE2723B1DF2168ULL, 0x7E5FD0413289F874ULL, 
            0x98B6C542F8F572B7ULL, 0x026B864BB4D4119FULL, 0x54709CC398107899ULL, 0xCBE012457C5428A7ULL, 
            0xA3E4F0D5C7621782ULL, 0xA4FBACA3C6EFBD70ULL, 0xB2EC5679B8265F7EULL, 0x9B8DF194BBEBCB94ULL, 
            0x0C68DD611335BD40ULL, 0x9E16FF485F411E9AULL, 0x152DEE1893010A20ULL, 0x40B56B3F2125BA29ULL, 
            0xB49AF4D88C34B232ULL, 0x2E0FC92FFBD5C33CULL, 0x3AEAF202FC5CAEC6ULL, 0x8EEB72D7F2B48C82ULL, 
            0xB2ED252E39367743ULL, 0x74430E6CDDB26E35ULL, 0x1C684B7E043BCD9FULL, 0x25D22C3587C9B330ULL, 
            0x6426CF969D2C8FBEULL, 0x3E30D451725F446EULL, 0xB84C8A925EE20FD9ULL, 0xF286CF4E6987447FULL, 
            0x7F7A25E793FD6EB9ULL, 0x0EC9904CBA407D75ULL, 0x8081BA2561D4D696ULL, 0x2904432EEDA32F74ULL
        },
        {
            0xA1899D95B61849B1ULL, 0x84DC7FAAD7340D69ULL, 0x075020A82A386AC0ULL, 0x5D26E8826D009B8DULL, 
            0xF3370412E1B2ACBDULL, 0xB0E37483EEE18CE8ULL, 0x3ECA43751B5A0A59ULL, 0x7DB64ADC4F526E2DULL, 
            0xFC908D56EE151C4EULL, 0x36D50D1EDD755989ULL, 0x71D8A6B44C81E453ULL, 0x8C6908520BD4EEF2ULL, 
            0x6FC6C745959E7A52ULL, 0x0D11B4A2C4A9AA88ULL, 0x32424D4A72C14BE6ULL, 0x26A57731139BC568ULL, 
            0xDFCF4109210E4214ULL, 0xA0A9B218BB7E56FDULL, 0xC3756D5224A373AAULL, 0x318BD096527D6355ULL, 
            0x691D187A418B5433ULL, 0xFB6D0109ED0603E7ULL, 0x22A4BA4F28E4E2E7ULL, 0xF5CB382C438D950BULL, 
            0x0F523E79499E8309ULL, 0xFA8830B290A14723ULL, 0x0D37B22940760F3BULL, 0x42BF4CD53F1166EAULL, 
            0x9A71BF6E3561B736ULL, 0x8CEBD0D275B83A32ULL, 0x9C4768528B2D1923ULL, 0xA64C4085318EFD3BULL
        },
        {
            0xFFCE647B551828EBULL, 0xB050DE7342BBBD00ULL, 0xC26F422B048F90FCULL, 0xAF7CA8D755BCCED6ULL, 
            0x38A249E8F421C2AAULL, 0x6A7B463619C9FF18ULL, 0xD5AECCDF95B16FD0ULL, 0x33255A85D0E093E4ULL, 
            0x7F6058BE63CFDCA9ULL, 0x5049188182FC2304ULL, 0x02B9C21B4B7AF94BULL, 0xB19685ECFE6BF30AULL, 
            0x6F6C17ACAFEFAE8DULL, 0xA9237BD16E702467ULL, 0x21D295BE815C0A05ULL, 0x696E70565DFDE628ULL, 
            0x02EF816C07429779ULL, 0x0B7ADE448FE178E2ULL, 0xF11EDC4148050C37ULL, 0x9EFD2BFB85842B0DULL, 
            0xB2F6FD7BB98F1810ULL, 0xD4902D254A1B2D38ULL, 0x00EA764D4B11A4BBULL, 0x5C0B8A2115ACE6DAULL, 
            0xF9C773A5C8A1840CULL, 0x1D992B1DB94B087DULL, 0x5A982E4D43BB2609ULL, 0xA15BD65F6320EFF5ULL, 
            0x1B53DBAE72EC827DULL, 0x8EDC674C8C11DA82ULL, 0x175C498FD2FB81E8ULL, 0xACCEFBA0753B2EA5ULL
        }
    },
    {
        {
            0xD683317D0AB6AB69ULL, 0xA6068D08F8903CB9ULL, 0x2BCD6BB8C014A6F0ULL, 0x2F9825896B5E698AULL, 
            0x9ABD7DA00841BB1FULL, 0xFE26337957C4E048ULL, 0x16126E3DBC88B302ULL, 0xCB838AD00B9C4FB3ULL, 
            0x6ECD1756BC487889ULL, 0xDB0BECC7601CFF7AULL, 0x075D2DB91F73E6A6ULL, 0x8636261F4A376CF5ULL, 
            0x5177CBDDEDC5D976ULL, 0xC29057350717560AULL, 0xA2CF1DAA6B4E7720ULL, 0x39478FB4263643D1ULL, 
            0x0181A0E3DADBF057ULL, 0xAA7B4ED5E0BED2F6ULL, 0xC4D534C6B7FE897AULL, 0xA1FC0ADFA3E2EAC9ULL, 
            0x11E7FB5CA407AB2BULL, 0x8AB43AF3E98D1CC9ULL, 0xABF73B7202D2CCB9ULL, 0x71D1ECEAA18767DAULL, 
            0x475F7D8194E158B5ULL, 0x52CC724DEFFB4EE5ULL, 0x17E10370012CEB39ULL, 0x27D4AD08AFB9A90EULL, 
            0xE1FD539E322C6B5CULL, 0xE47F89FFCE96A5FDULL, 0x7784A9E662745177ULL, 0x76E89DEE9220F941ULL
        },
        {
            0x172686D4B834F079ULL, 0x1CC4261265E93C0EULL, 0xC42CFAB5C7917F3EULL, 0x00B7DF9F71A9D188ULL, 
            0xC9B0A6EDBFCBD2FEULL, 0x00964C3FC042412FULL, 0x121F19AD0A800866ULL, 0x5FDEA1819D876A29ULL, 
            0x6210FD49E57D2985ULL, 0xB4548F79ACEDE415ULL, 0xAC31E938BCC492C5ULL, 0x37C91343D7E6431AULL, 
            0xCA37B83021EFABA7ULL, 0xBF52519CB55029B7ULL, 0x13FDF80220A2BE8DULL, 0xA743476372A7FAE9ULL, 
            0x7367B5D9345007EDULL, 0xD4BD7BFBDB767DB9ULL, 0x8D6709C9F640BB2CULL, 0x85615DC5B4DA9D45ULL, 
            0x5A9A9E803B9EC73DULL, 0xE497D9A96A962A5FULL, 0x0329E3AD7BA73DA8ULL, 0x78BDBFE35ED732ECULL, 
            0x2955A328E604F0EEULL, 0xA1FB5367C5C657F0ULL, 0x5277627BFB76286AULL, 0xE3E0CD8874BA4354ULL, 
            0x3ADE55C884A1DDB4ULL, 0x48317BC6BFD31FDBULL, 0x13254785D288ECE3ULL, 0xF6D31A9CC4D9DAAAULL
        },
        {
            0xDD8D2055D5172F1CULL, 0x1A0B89AC038F0926ULL, 0x96A5FD1F5B93DB53ULL, 0xB73B1BC8C66E0E33ULL, 
            0x4CB14ED003B788CEULL, 0x052170D8A937443BULL, 0xCEBD2EBE875ED498ULL, 0xBC67B29906C462E7ULL, 
            0x2E63664EC07F3C67ULL, 0x5C8BD51EEEFEE178ULL, 0x15A059273B8350D4ULL, 0x66328E725C86ABD0ULL, 
            0xDCC62F49EB834991ULL, 0x4CE819FE5402AE2FULL, 0xB9C360149AC30C19ULL, 0xCCF75F8E033F3AC0ULL, 
            0x8AC00821CAF52140ULL, 0xCE6762DCD8105B68ULL, 0xCF5A9F13334845C1ULL, 0x4DAFBC6241D902F3ULL, 
            0x62F250CFA6685D3CULL, 0x1E42691FAA5CABEAULL, 0x7610A6BF18FF7ECCULL, 0x0B4D0FD940248052ULL, 
            0x50B969DA788F30D4ULL, 0x2206F5C67E190B42ULL, 0xCCBE836110683395ULL, 0x417E4719426BDAD8ULL, 
            0x25EDED207C2AFC5EULL, 0xD3D93E43E4F9C9E7ULL, 0xC786D479583737CFULL, 0xC1B28C74805CF77CULL
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
            0x0C7829D61068576FULL, 0xE616D4E651660736ULL, 0x4DDEB693EE07958EULL, 0x62BAC5E963378986ULL, 
            0xAB4C5BEA7D0BE363ULL, 0x30A223F02CCD0CF2ULL, 0xF265F983D885807DULL, 0xAFC5B1A9378442B5ULL, 
            0x92C03E9538CE0672ULL, 0x0160318D48EEA0A3ULL, 0x08C5DB047CD39BEBULL, 0x3EC50EB8359CCDE8ULL, 
            0x8F9229519D01E6ADULL, 0x5ECE5D39F35BF046ULL, 0x0D2CFFC29C31D9CDULL, 0x1BC87B8F0576D96CULL, 
            0xC450CEC60CA9B159ULL, 0x5EBB7102A3845C25ULL, 0x58DBE9DF0A33097AULL, 0xBE154A83E01FF8CAULL, 
            0xDAD268E682CFBC36ULL, 0x1463228E03CBA6C1ULL, 0xED842422628DE2F3ULL, 0x6CECC9881693C682ULL, 
            0x2A68E8F474A549A9ULL, 0xC67A808B2B9CDFFAULL, 0x6934760EABA4A7CCULL, 0x8F3456FE62101F51ULL, 
            0x8CE04CC947E743A5ULL, 0xFAD8EAE132AF9D91ULL, 0x6A23C0FBE8D4320FULL, 0xC147B30FA7989C8AULL
        },
        {
            0xD36A56807D2B20FEULL, 0x9E4C5EDA71F94765ULL, 0x165D11A8C6F8BA6FULL, 0x1A8D21D030A458D1ULL, 
            0x2014980F9E194DDFULL, 0x192F904C4BCBE22BULL, 0x5FA4C8B33488A697ULL, 0x5A7E3D8249004D22ULL, 
            0x1A869D6EA5C63FF9ULL, 0x15A3E762240D29E4ULL, 0xD977011A4968F74EULL, 0x87BB63D8C01B42C1ULL, 
            0x599B0781F7AD9178ULL, 0x079AF1CFC3B2D8B6ULL, 0x0D38FBEEAA2FE224ULL, 0x489C3309D4BE9035ULL, 
            0xAA3EB16DE0088DF6ULL, 0x5C3EDB5B2F3EAF3BULL, 0x5AB43E256443865DULL, 0x266D862D05A840FFULL, 
            0x0403597F764D984EULL, 0x43020067586BA0B0ULL, 0xFE3BCBC999C6697BULL, 0xDADB978A96B47CD4ULL, 
            0x589EB3E26C125B3BULL, 0x9A39DBA5C43AD1FDULL, 0x03BCC36E4566DBD6ULL, 0xE2D9151DA13909AFULL, 
            0x7B99014733EF9A25ULL, 0x65AFDA005E4467B9ULL, 0x3FD1C9AD9E15FAA1ULL, 0xE79C0BF42C0955E3ULL
        }
    },
    {
        {
            0x9BF90AAB36730735ULL, 0xC0098647B1B08CE7ULL, 0xC79F1C2C299E8992ULL, 0xD32F9A5B48C570C7ULL, 
            0x034CF321465ABB74ULL, 0x2F3E170A6C0E3719ULL, 0xEE2A215581E3393EULL, 0x4A1999500E2FA03EULL, 
            0x2D62690458DF41B5ULL, 0xA999D1E773493717ULL, 0xFA73E3B2B1CF8DD3ULL, 0x5C6DF5B6C50FE875ULL, 
            0xB7EBF870629C0DE2ULL, 0xD1D73450F49AC82AULL, 0x9DB2D3BFE10494B5ULL, 0x0B4A21333EF4F987ULL, 
            0x85508DF00A212112ULL, 0xDEA6598DF8950A38ULL, 0x2931BBC21A85AC89ULL, 0x07503733782C628DULL, 
            0x8E5132B9EB3E98D0ULL, 0xD03CB1F3DED12D9DULL, 0x77E381BD32FB224CULL, 0x726B5D07C7820102ULL, 
            0xD398EED72665BA37ULL, 0x29D588F546B55F62ULL, 0x1866AD2EF0D049E5ULL, 0xAC9BCE1995EFDADAULL, 
            0x89E234117ECDC9F7ULL, 0xF4F82EE44D2458C3ULL, 0xFB0D36E17CD8610EULL, 0x4AF062A2683C751BULL
        },
        {
            0x3EF6E532CE6BF1A6ULL, 0x0FF7CC5977E29CE0ULL, 0xA418AD1FF2A3B3B0ULL, 0x672C163CB5687D71ULL, 
            0xA7BF3B8791B479F5ULL, 0x0F37061502D6AAAFULL, 0x550268D51257CB3BULL, 0xD644AF1DA98331DDULL, 
            0xDE1CD22C9A2C54E6ULL, 0x330C9BE9C791EF1EULL, 0xED02EC15345A1332ULL, 0xC3A6FE1668C7375AULL, 
            0x441BF8627538BD1DULL, 0xD88689A3E6D31DEBULL, 0x390D89C172F994B6ULL, 0xFF8A28BAC19E4012ULL, 
            0xED78A18DD1FA458BULL, 0xB00B0D1BF1130132ULL, 0x35F697984761CABDULL, 0xD244E2A52537A9FCULL, 
            0x4CF79C5D699FFDD4ULL, 0xBF1EDE578ECF1A5FULL, 0x984879AEB42AE1F7ULL, 0x851F0E0C4CF1CDD7ULL, 
            0x5D21F2D745F79587ULL, 0xB5D1F0DDDD69A4EEULL, 0x6B10A37EC9C0BA45ULL, 0xADCAF9B77E1D688CULL, 
            0x36AF21C32C99704AULL, 0xD33E84463299839CULL, 0xF99227C1DDEFD02BULL, 0x774EED914B985964ULL
        },
        {
            0x4C5BB3A502D610C1ULL, 0xE51CFAB2DD88E7FDULL, 0xECBD752C3F9FAB1AULL, 0x62500DA9584FF115ULL, 
            0xCCE5B8151FEF180AULL, 0x3C83AA0A26BA46B5ULL, 0x65CC7FF7EA216651ULL, 0x691C6D4B9106FE1FULL, 
            0x546F0D1E0E7FCFF9ULL, 0x2A12EA37142F8BB0ULL, 0x0955062D77BA29F1ULL, 0x769919A919B44682ULL, 
            0x5BF400905EC06F14ULL, 0xDF30EB7107991AC8ULL, 0x6B8AD43CA206047AULL, 0xA80B5D4159B56D22ULL, 
            0x9B336E9F1EBCC8EFULL, 0x4CDD6C777223D6D1ULL, 0x8A5AC6FAF83BC02EULL, 0x7BEE52918D510020ULL, 
            0x9A596229A8D75EF9ULL, 0x017027F8DA84B9A0ULL, 0x72ABF076669270B2ULL, 0x40C435EA2B13A6C0ULL, 
            0x63915FDB310BCBCCULL, 0xAAF0B823EAF558B9ULL, 0xFD9E293C64677DA0ULL, 0x16F33D18D4CF1BE8ULL, 
            0xDC5FF7B61C548852ULL, 0xE20852AC43DD68BDULL, 0xA1ABEBA73E0DB9ACULL, 0xABCCD668BCC0D467ULL
        },
        {
            0xE037ED0D486DA1EAULL, 0xA58EC9BAFB58A69FULL, 0x7C9843D84784D565ULL, 0x6E9E284589627575ULL, 
            0xD035D77F40196FD7ULL, 0x546FC032C4C33DC4ULL, 0xE6978B865848FC49ULL, 0x635CF50D300E5D07ULL, 
            0x80DAF1D0D882D665ULL, 0xE55FFBE4F4FD4EAFULL, 0x193D4F0DF3372B57ULL, 0x901AC651B15DB650ULL, 
            0xC1862B8AD85D32D7ULL, 0xD42FF12B15C5E9EDULL, 0xA1D2A74888FBA01DULL, 0xF344944109F935EFULL, 
            0xF3D9A612D9817F89ULL, 0x78A4C1D9B7390450ULL, 0x8954DD1B51614A79ULL, 0xDF5464F8B5E18777ULL, 
            0xFD5D4AB67CDCF8E2ULL, 0xA270AE058F9DAA5AULL, 0x0FCAFBAFA14D9D7DULL, 0x4FBEC05A1286E996ULL, 
            0xDFA6390211D987EEULL, 0xF477F3115E74E425ULL, 0x03EFCCB6BFDF5BE3ULL, 0x3E07F77B65A84FCFULL, 
            0x209DB128D1B0BF12ULL, 0x805A50E068E1D9A3ULL, 0xE2B6E86FA09E0833ULL, 0x7CFC5BFB3E68D1BFULL
        },
        {
            0x4E97D1CB753971F6ULL, 0xAA1057E825AB57EDULL, 0x8EAB688E97A29D82ULL, 0x3ED5A9A0C8E8AE9BULL, 
            0xA5A28E8C8B5FCA33ULL, 0x1DF31C0B1F19F31FULL, 0xF996D9C9134B370CULL, 0x44EAE9A6DF07FCD0ULL, 
            0x5981D00A1F578139ULL, 0x5327CECEE651ADC9ULL, 0xC897D36FAEF80D99ULL, 0x07DA6446A39533A8ULL, 
            0xA4B9FA2BA89828F7ULL, 0x587D46463CDE6751ULL, 0xFA19715DA1A1F143ULL, 0xCB148DBBBA760331ULL, 
            0x67CB5E73667FE153ULL, 0xF59BF0447A72787BULL, 0xEBFF9F90EE66FDEFULL, 0x73DC89E7B0F2B77CULL, 
            0xB65223698AF9F497ULL, 0x21A713384B62FB63ULL, 0x2FF17D54541CDA1FULL, 0x1E1011DCF2DECC95ULL, 
            0x2A99DCF981DAD0DAULL, 0xEAE024A0D5E9F013ULL, 0xF9D80BD2BE5D7592ULL, 0xA2A9C575E50E30EBULL, 
            0x85EDFCDB576083C7ULL, 0x17073B9575240AD6ULL, 0xEAAF8E8AB0C8F638ULL, 0x803CFF6416E5B44CULL
        },
        {
            0xC390A2A6624A4D66ULL, 0x35D975FE374CDE8DULL, 0xFC7171F49CA2417DULL, 0x8D493C128111387BULL, 
            0x722637788E884E79ULL, 0xAFF09F76C4758F50ULL, 0x6CF2F5F44B5CB3E3ULL, 0x57C325A1DA5A6203ULL, 
            0xC44C313F93C33EE7ULL, 0xEDC5F84BD0C1B5D8ULL, 0x8E55E44E5010C558ULL, 0x654FE3C64439B55DULL, 
            0x536B501B473DC715ULL, 0x9F050C88555DCDB2ULL, 0x8A897CC22AC5BE3EULL, 0x750AD10D6A34716AULL, 
            0xA035E7798B8AFAA8ULL, 0x16114D0DBA744703ULL, 0x5F96AC606470EBCEULL, 0x0A251635DC8197D0ULL, 
            0x5071B44F51775153ULL, 0x3DE0782CC23DF131ULL, 0xDB0A19134C65FD74ULL, 0xF34F16FC9555D1ACULL, 
            0x574A01EDE052BFB9ULL, 0x01103F65EF699A1AULL, 0x5E902331CD2CC1E0ULL, 0x55BB1DD78420A052ULL, 
            0x72F914E213F2F713ULL, 0xACD161D6EB9EEAECULL, 0xAA91E0124C9C0336ULL, 0x8824844410C67179ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Arcturus::kPhaseHConstants = {
    0x63A4F6170CDDDF62ULL,
    0x9F472E7AA9835EA9ULL,
    0xA5B7B08819179662ULL,
    0x63A4F6170CDDDF62ULL,
    0x9F472E7AA9835EA9ULL,
    0xA5B7B08819179662ULL,
    0xC1C8616C5A2B8B91ULL,
    0xED5B1108EF8004D2ULL,
    0xA1,
    0x1F,
    0x81,
    0x1B,
    0x23,
    0x47,
    0x0F,
    0x84
};

