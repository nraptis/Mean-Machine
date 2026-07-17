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
    std::uint64_t aPrevious = 0xA319898679954E36ULL; std::uint64_t aIngress = 0xD28D8C607EA64313ULL; std::uint64_t aCarry = 0xD71CEB62162A9836ULL;

    std::uint64_t aWandererA = 0xF544308497006D94ULL; std::uint64_t aWandererB = 0xBD30B3537894182BULL; std::uint64_t aWandererC = 0xB20F9B25A2C120B9ULL; std::uint64_t aWandererD = 0xDDDC9FFDB9119A5BULL;
    std::uint64_t aWandererE = 0xC3D40548EBCAB4EDULL; std::uint64_t aWandererF = 0xA78F2993DE032CE9ULL; std::uint64_t aWandererG = 0xBE092DDC1DCCDF41ULL; std::uint64_t aWandererH = 0x8EBA4DA44AA16A23ULL;
    std::uint64_t aWandererI = 0xED5600B545F011CCULL; std::uint64_t aWandererJ = 0x8779B1CE0718097BULL; std::uint64_t aWandererK = 0xB0E5083DCF6CA9A6ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 12488652275229650651U;
        aCarry = 15207196088002523990U;
        aWandererA = 16336661408349161368U;
        aWandererB = 16891928717333699972U;
        aWandererC = 14721886966888794043U;
        aWandererD = 15238892632590542367U;
        aWandererE = 12991150212118357050U;
        aWandererF = 17698842542056088850U;
        aWandererG = 13860582680464056856U;
        aWandererH = 12918020380325293630U;
        aWandererI = 14430920471200855853U;
        aWandererJ = 15404194353551550708U;
        aWandererK = 11736485224245207365U;
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
    std::uint64_t aPrevious = 0x8995DF61C5FCFBF8ULL; std::uint64_t aIngress = 0xFE9D1721131A7718ULL; std::uint64_t aCarry = 0xDA796FFEC2BE339AULL;

    std::uint64_t aWandererA = 0xE8FD943F99F839C8ULL; std::uint64_t aWandererB = 0xCB6A42B1E5D59481ULL; std::uint64_t aWandererC = 0x8C8DBCEDD8213421ULL; std::uint64_t aWandererD = 0xA65DFA9ED8D1537BULL;
    std::uint64_t aWandererE = 0x94AF5C4302B41001ULL; std::uint64_t aWandererF = 0x9555488C9E3F6D46ULL; std::uint64_t aWandererG = 0xCD9E50C7AB812663ULL; std::uint64_t aWandererH = 0xE479F33B30A47BA8ULL;
    std::uint64_t aWandererI = 0xDF0732C2C523E877ULL; std::uint64_t aWandererJ = 0x8FD531A53F2B919FULL; std::uint64_t aWandererK = 0xD8803F3C0385F930ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 9480368064536276957U;
        aCarry = 11029159285628508921U;
        aWandererA = 14138179885310559480U;
        aWandererB = 14633555031802912995U;
        aWandererC = 13584488542635337765U;
        aWandererD = 12076641962664383521U;
        aWandererE = 17385197787459202706U;
        aWandererF = 13303277973339069962U;
        aWandererG = 16671965426729351862U;
        aWandererH = 15641670837118988688U;
        aWandererI = 14048132254870223594U;
        aWandererJ = 14589931338030397118U;
        aWandererK = 14995314876686508922U;
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
    std::uint64_t aPrevious = 0x9B26890B71A55297ULL;
    std::uint64_t aIngress = 0x9914A58BDB8DFF13ULL;
    std::uint64_t aCarry = 0xB788ABFB94871989ULL;

    std::uint64_t aWandererA = 0xFAC12D162B494CF5ULL;
    std::uint64_t aWandererB = 0xD79522680AD5F9ACULL;
    std::uint64_t aWandererC = 0xE985DC26D0215A96ULL;
    std::uint64_t aWandererD = 0xE7316AE83C866F1BULL;
    std::uint64_t aWandererE = 0xB4A4B800A7F58254ULL;
    std::uint64_t aWandererF = 0xA007601CA128E380ULL;
    std::uint64_t aWandererG = 0xE5FF9F024D1EC098ULL;
    std::uint64_t aWandererH = 0xAC7E39C4AD751FFEULL;
    std::uint64_t aWandererI = 0x85E1C40BD053F2B5ULL;
    std::uint64_t aWandererJ = 0xAAEAE8EC1AED835AULL;
    std::uint64_t aWandererK = 0xEDF8E0AC2C287585ULL;

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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseAConstants.mMatrixArgD;
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
    std::uint64_t aPrevious = 0xE95360784642614DULL; std::uint64_t aIngress = 0xC2F1A45CD3E40F4BULL; std::uint64_t aCarry = 0x8550B011CFC0E1B5ULL;

    std::uint64_t aWandererA = 0xFBB145B4A1F3E3A1ULL; std::uint64_t aWandererB = 0x8172E69AEFB42A02ULL; std::uint64_t aWandererC = 0xF4A09DC8B56E8EB7ULL; std::uint64_t aWandererD = 0xBF1066BF618B4C6DULL;
    std::uint64_t aWandererE = 0xCC08C239294713E9ULL; std::uint64_t aWandererF = 0xB34A66505B5361B9ULL; std::uint64_t aWandererG = 0xF92EAE8D74505F21ULL; std::uint64_t aWandererH = 0xE0F6819EB3D33B28ULL;
    std::uint64_t aWandererI = 0xB7D79BD8DC927FC0ULL; std::uint64_t aWandererJ = 0xA32FCE55DFD31453ULL; std::uint64_t aWandererK = 0x82D3592C7CDDE6F6ULL;

    // [seed]
        aPrevious = 17797434764709252262U;
        aCarry = 15739391909467611594U;
        aWandererA = 9355324490495870806U;
        aWandererB = 9906340574275852108U;
        aWandererC = 15284188592315096993U;
        aWandererD = 15325231309613477795U;
        aWandererE = 17680415003665978765U;
        aWandererF = 11297275095360183018U;
        aWandererG = 11456266053589861155U;
        aWandererH = 12531663224913048486U;
        aWandererI = 12609821559809653958U;
        aWandererJ = 9518896300015976847U;
        aWandererK = 13198302969044722741U;
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgD;
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
            0x1FBE7BE00AE179B8ULL, 0xD37F79D6B92F9B4AULL, 0x285624C071FFD142ULL, 0xE5C7FFCB3AEC03C7ULL, 
            0xA2A9F9FB83B4ACB8ULL, 0x19271E92EC3F687CULL, 0x30D6F9F0A2CC95D8ULL, 0x7C0319EE8FB8046BULL, 
            0x03E472740F02869CULL, 0x7CF8283CABB0F62CULL, 0x07465746D482182EULL, 0x36142B9E4ACFC82FULL, 
            0x9D31CB14B095C802ULL, 0xF677D73F58B22498ULL, 0x370BD0C8BA91BEB5ULL, 0xB5B90558EC939A7AULL, 
            0x7A782A2018D8C6CEULL, 0xD3C142083A6285D6ULL, 0x6B14114FEA54AA0DULL, 0xE104FAED462DF506ULL, 
            0xA031A52E7CE2CD79ULL, 0x54CB3004CD699E53ULL, 0xA9B766844D18CCBEULL, 0xE7D86D0D6EBAB1DCULL, 
            0xFADC5972A825E7A9ULL, 0xA9C589426D03698AULL, 0xA7EEE64BA4537EC7ULL, 0x49300CA0F3B7A901ULL, 
            0xB4396363F7800200ULL, 0x327BBEC331E40843ULL, 0x5264DB0420F0C7AAULL, 0x7B783DFEBA5C6FA5ULL
        },
        {
            0xAFEB1147D2F2271FULL, 0x6665F17322C75DE3ULL, 0x562CD4A490471FB5ULL, 0x713E2C123468318CULL, 
            0x782EE80E6E3C6758ULL, 0x1BF1B42D7DC05F4CULL, 0x248DB43BA9213FF6ULL, 0x829A258D38B30E84ULL, 
            0xD086D845362DBC69ULL, 0xE6FDEBAF300A16E8ULL, 0xF05F49FD84AF1CC0ULL, 0x5FB2F04DD486A630ULL, 
            0x20380A2F00BB6592ULL, 0xE61C8E06B226DFFBULL, 0xDC8D916AD526E18CULL, 0x189A030A993829CFULL, 
            0x8E1A57D3EC63DA29ULL, 0x559C4B1DD1574A9EULL, 0xD15984B4C60A9EE0ULL, 0x37F71F12B9F7F8A4ULL, 
            0x214D0B89CC6C548FULL, 0xE8077E9F1031A712ULL, 0x6EAB8940E7E36D6CULL, 0x2A1FD8AA3E0A2846ULL, 
            0xA46D7367C34EB6A6ULL, 0xA7DAA9C27C5F280BULL, 0xDB0F903FBDB9F3D0ULL, 0x9392D033C2AB119CULL, 
            0xEA83DC66A5E70148ULL, 0xBBB61593D278E5CEULL, 0xC473438CB6290910ULL, 0xF1EE9B06E5F10EF1ULL
        },
        {
            0xECAE50F27979D56BULL, 0x739AD5C6F7D097DBULL, 0xD5CC4811BF94DFA1ULL, 0x4D0B5D9A0ADE72C6ULL, 
            0x185A9622F44D8EE7ULL, 0x1FAC1D2557AD258CULL, 0xF56C1295F3859EEBULL, 0xBD3C0B6F395A8996ULL, 
            0x7B6153133346441FULL, 0xEC12A429841B47F4ULL, 0xEDCAB6A447400EE9ULL, 0x2F11F9FF57A155BDULL, 
            0x8D28703D2B027C23ULL, 0x61F03D1860880A5DULL, 0x5BDDD38186F22659ULL, 0x2DD78619C0C52289ULL, 
            0xA4F80316CD521BA5ULL, 0x69CBD14AB12F664BULL, 0x718ADCFF9D542EBCULL, 0xCD51573F4EC29CDAULL, 
            0xDFEDF9039AC526C9ULL, 0xBEFDF3AEF945A3A2ULL, 0xB88E93FEEA850863ULL, 0xBBA97FD3B8D7AE03ULL, 
            0x85597DEE3E58DCEEULL, 0x52E8E03ED766BDA2ULL, 0xA34443973EEB2770ULL, 0x14E7C5E0E5225047ULL, 
            0x4CD631430C2FB6FAULL, 0x50557D2ABE4E2ADDULL, 0x01E281961CBAD25EULL, 0x700E573EB55A2362ULL
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
            0x63F4E68EFE681D4CULL, 0x88FF5D8FCC36BA4AULL, 0xC205DD2AA01C4456ULL, 0xB9830A77D7BC4D32ULL, 
            0x448D6C4E7D52B5B4ULL, 0xEC883021E1F418DFULL, 0x7ADC31ED891A6CC8ULL, 0x70ED981903A28261ULL, 
            0xDEE45A0C61160E85ULL, 0xC4B14078758529D3ULL, 0x5193A33DF4F0AF74ULL, 0xACE047994E1E84FEULL, 
            0xBA2CC3A5780E14A3ULL, 0x438E96ADBEB39127ULL, 0x313B4498C3FAC3E6ULL, 0xBBE205B5DE57E95FULL, 
            0x84847093CA8753EDULL, 0xF859F64004519A19ULL, 0xDB7AFDE8CF13C71AULL, 0xCBCCE53A7957BA8FULL, 
            0x5FBD668EAF59E36FULL, 0x527A32E0C56E1425ULL, 0x7487D1E9DEC63769ULL, 0xE3603C98C3D0069BULL, 
            0x4858AF69E6D48FF8ULL, 0x9E38FE6C058031A8ULL, 0x72FBBDE05207849CULL, 0x4A41C2F333EA3FDAULL, 
            0xCF0E29D18630E351ULL, 0x92C45F64FE9AF688ULL, 0xD72672CB743664BCULL, 0xEA23D9416F94DA06ULL
        },
        {
            0x615B4263B09A381CULL, 0x5146935F3C02CA28ULL, 0x75A4CD3EAC5FE08AULL, 0xD83E727CF9E508D6ULL, 
            0x9B90F050BBAC5A0EULL, 0x18CCC4E839BB8ED8ULL, 0x8D626BD5A830A101ULL, 0xF25A94301718F625ULL, 
            0x61EACAAFD64FE73DULL, 0x329A017033D12C1DULL, 0x825EA08CBE6801B6ULL, 0xE63560E8A1661684ULL, 
            0xE83AA8818C2A8231ULL, 0x30170C5A8C1F2517ULL, 0xF015F49814E7D5B7ULL, 0x7B3F762FFA103354ULL, 
            0xD1E43B2083C4A57FULL, 0x58934F7B8A5F934CULL, 0x78418CDB075A437CULL, 0x842CF4D2224FAC7FULL, 
            0x336E7CBE4FFA7343ULL, 0xA3BE6C591EB154A4ULL, 0x3CD2F794586F5C3CULL, 0x1FA03BE2B75F3463ULL, 
            0xF9E940818397B5ADULL, 0xC5DA4CD3A02D79EFULL, 0xC76D5198E55529AFULL, 0xAF8A24EA42A450A2ULL, 
            0xDDC5016BB8E4B934ULL, 0x551AE727B791CA6EULL, 0x390B54020A451F4DULL, 0x327BC77267EAAD36ULL
        }
    },
    {
        {
            0xDC91B16CC47F9493ULL, 0x52835EA79E5971AAULL, 0x32699A3BDB664963ULL, 0x319AFDB24DE4D619ULL, 
            0x8D4092D4064D77C4ULL, 0x041859A4CF69C864ULL, 0xCD027AD61CFDAE74ULL, 0xB99A90D3E1646173ULL, 
            0x78C5B58CFD5780D4ULL, 0xE3F08F1193FA5024ULL, 0xF2ADEDA7D3D4EC6DULL, 0x8E45873D8DC09B5EULL, 
            0x35101C82B7AA0658ULL, 0xC6F99CB53900C63CULL, 0x2BD8ED2D9C5F5D6DULL, 0x7491AC7849DFAC51ULL, 
            0xF7EDEBA7E268808FULL, 0x005B020A83B57128ULL, 0xD9FF08C07F5F953DULL, 0xBF27F46AF986D098ULL, 
            0xCA93B4D2F6D68CB0ULL, 0x09F6E3648B88D439ULL, 0xAD9C310D4E0C9B37ULL, 0x44D4C09B709449DFULL, 
            0xC4E212D2FB917538ULL, 0xDA4BE43D0FBB05D2ULL, 0x5CA8A29615CBF932ULL, 0xAFB9A1D3D2D1C1DCULL, 
            0xCEDC4DEB11DBAABBULL, 0x178B07C946B59C3CULL, 0x2B04E48D99D09D97ULL, 0x41283D8982FC85D1ULL
        },
        {
            0x221C93B36F68AD4CULL, 0xDEA34AD4BC4A72B0ULL, 0xF081FD12705F78FCULL, 0x616019758EFF6B94ULL, 
            0xD576D30964D4BE49ULL, 0x47501D455DFAAD40ULL, 0x7F11931604DC82EDULL, 0xD006727914C3D355ULL, 
            0x961B3D362B75C238ULL, 0x31836E4673CC5B82ULL, 0x1E1E010CB7321FBAULL, 0x501DA28F25A827B4ULL, 
            0x7D6B1F763498CFA0ULL, 0x8D6849141C2C3B34ULL, 0xEEE8B281991A0D1CULL, 0x2EE366A7923FC327ULL, 
            0xD982745E7D4EA158ULL, 0x5A14495AAE0DBBE0ULL, 0xB786326944F346DDULL, 0x7FB676CBD9FA1432ULL, 
            0xE696CA16B6670A99ULL, 0xE2C0EE4978A1D331ULL, 0xCE8E583B9A571D11ULL, 0x62F036BFA91DD232ULL, 
            0x503F1E5F5D4677F5ULL, 0x6DC4020D149D9A56ULL, 0xBE02FD751D4E6D55ULL, 0x51D36B4CE42A1F96ULL, 
            0x13BBF8EA3F9DF343ULL, 0x8BBD4C9B862F15C8ULL, 0xE468F2CC61806549ULL, 0xC1DAB850BD36EF8AULL
        },
        {
            0x8312766967CBF006ULL, 0xFFC1024370F91042ULL, 0xEDD2EF4FCA0028FCULL, 0x1C27576788413A89ULL, 
            0x10477D6FE7A6063FULL, 0xB528F59E203A38B6ULL, 0x72B04642573C4AD7ULL, 0xAC0EB271432EA6BCULL, 
            0xE7D487312FF3F5A9ULL, 0x59DFA8FCBC5BAB26ULL, 0xE482EE75FAE79208ULL, 0x63C7C420017F3EB9ULL, 
            0xA587098303621FADULL, 0x1198DCF51ADE796BULL, 0x2BBC04570F315CBDULL, 0x8145DBDE04C8F33CULL, 
            0xDA1AF271C087EC10ULL, 0x49F2B8DD7D50CEFBULL, 0x21773A80044B654CULL, 0x3B770B73D4C454BBULL, 
            0xEECF5491E5F9235EULL, 0x9047F6AAF5942654ULL, 0x183C099186A6D059ULL, 0x16350BAEF1EA9AEDULL, 
            0x6C3ED289C2072BF7ULL, 0x5017F208ECFC8C23ULL, 0x24E8DFF0C5891224ULL, 0x80B286F810951457ULL, 
            0x0DE848E80E983D0EULL, 0xE1C25EAE84780204ULL, 0xF6D655D32908B9B4ULL, 0x65B3B27F9714A36BULL
        },
        {
            0xE42DD33BC53E5622ULL, 0xDF4D3F5CF4872DE7ULL, 0xB6C7526B12F004C7ULL, 0x7B09C412E3D42CB9ULL, 
            0xA8BFFE051D611FEBULL, 0xF6DAF8C9007CDECAULL, 0xD9291C208BAEAFE1ULL, 0x7B652B490B467302ULL, 
            0x9FDA48B71CACA5B4ULL, 0x7A0AB1A8FEC4ED1AULL, 0x0559CE04D154A71DULL, 0x98694EEA8BFC08E9ULL, 
            0x072D15536B864790ULL, 0x2B2B7A48DD4EA384ULL, 0xD1FE3EBEF64B90BCULL, 0x7C65BD41C9F9FEF3ULL, 
            0x1ED5F46FCA171627ULL, 0x8485FD71D06392D6ULL, 0x0D5906CA8EC17B27ULL, 0x013BDDAAA302D630ULL, 
            0x3B8B0E0D9ECE102EULL, 0x1F537BAC3C637012ULL, 0xE3D8F67B804366B4ULL, 0x576031709C0DBF9BULL, 
            0xFD722437F720D28CULL, 0x63561AC9DD979E8AULL, 0xF2702457750B98BBULL, 0x56F2A631305F7C4DULL, 
            0xEEE7C9E3DC4153CCULL, 0x576625D6E083BA6FULL, 0xE08E84560635EF5CULL, 0xA02870B22A03BA9AULL
        },
        {
            0xB8FAAB6C4FE3EDDBULL, 0x425A5CD08AFAD222ULL, 0x07F4DD7336523845ULL, 0x7AA94A56B2EB620FULL, 
            0xBC38F406C68F73FFULL, 0x4DD3D367E8130F31ULL, 0xE8B63A1B6E13C772ULL, 0x215E999A2249890CULL, 
            0x25BDE3CFA0D9BC47ULL, 0x25C9D392ACD27B3BULL, 0x7AC5BBA221953C19ULL, 0x5568C56682FF29CBULL, 
            0x4F0220A6EB13EB85ULL, 0x1BE25CA5AB041529ULL, 0xB0F8CE212A8C001FULL, 0xE57CF3DDAA82ACABULL, 
            0xD23D619EAE55DD24ULL, 0x5629062EACEA43CFULL, 0xF8EC3B9EAC953F43ULL, 0xA7D22A1A506CB600ULL, 
            0x736685E6431A62C4ULL, 0x299AB993943D9D3DULL, 0x16BDE3D1B5E6A36DULL, 0xA8BA9172820BA419ULL, 
            0x0A270DEA7F7ACD1AULL, 0x98359F1F7458D276ULL, 0xDF6D5F56E45C366CULL, 0x9F5A92DB474ACE35ULL, 
            0xB948680BCFE93119ULL, 0x3EF4D22CAD9824E1ULL, 0x7EC814CDA7981DF0ULL, 0x17BE7D823EBE6CAAULL
        },
        {
            0x03081211EE56505DULL, 0x0AEE92CEBD52EEDFULL, 0x3D4AE7B10EA351E9ULL, 0xA01C30A222178984ULL, 
            0x7F103980B2915B42ULL, 0x9FA4172D0E2E3F17ULL, 0x6656AF716219FF9FULL, 0x5B092E5E08C11B50ULL, 
            0x1B95F5568E587D4BULL, 0x01307A3199FBE8EFULL, 0x3C500F7A0DC0F47EULL, 0xBB925B9D23D0C56BULL, 
            0xD122765155AC8CA1ULL, 0x4BD6B254E6E7A376ULL, 0x7F88EA2A959F1785ULL, 0x92BD9A4FCF781984ULL, 
            0x7A31D00DB87A3841ULL, 0xDC90EC9CA8203971ULL, 0xFA469F6877C49CC8ULL, 0x74B4B968A8247BBCULL, 
            0x48CD2B52F53960B2ULL, 0xDDEE5FAAFC2624F7ULL, 0x52CEB5DBF389BAB6ULL, 0xADA29E089F9156D0ULL, 
            0x09ED7C285D8484D1ULL, 0xFBB3B43D75A356D3ULL, 0x5A19CE22BDBFAF24ULL, 0x27B029F607A62FACULL, 
            0xF49B4C51976F84CFULL, 0xF2A56087A86664D7ULL, 0x993B6B0169990EBCULL, 0xF7CD23BAE4C3B477ULL
        }
    },
    {
        {
            0x3AA18A2A9EA19A0EULL, 0xD9882CCB60B8F5EFULL, 0xB9CFB908B8C8B6CAULL, 0x0653CCE107D0902DULL, 
            0x1C464C6E1639637FULL, 0xC07AB2E8435AE660ULL, 0x194566C6ED1051D6ULL, 0x4BA9C1FC59B96683ULL, 
            0x24D639946BCF0187ULL, 0x699420138BDAD714ULL, 0x4FE7CB2A6DF98567ULL, 0xA66B002B681214B4ULL, 
            0xE4FBA3F330CA7949ULL, 0xEF402227D190B077ULL, 0x273A8BB1EE33607AULL, 0x98A122A3C4FA81F6ULL, 
            0x8B0A276CE7B475A4ULL, 0x25357DF7192A3AD3ULL, 0xCB3FD9BB54AA5D9FULL, 0x82873FF5CE2C4F70ULL, 
            0xFE86E4B2520D6FBDULL, 0x298C7CEF6E6A5505ULL, 0xB87F64206F7C1209ULL, 0xA31E2891118614B3ULL, 
            0x3082C514147C7897ULL, 0x674A8EA5DEEDDB4BULL, 0x8532E6A7113D17C3ULL, 0xBE73BA54052E87CDULL, 
            0x38AA354498D685E8ULL, 0x61E39C7F4F88DD45ULL, 0xD505839C21EE15F2ULL, 0xE21634DF5E207F60ULL
        },
        {
            0x8C76B8D96F6E88C1ULL, 0x6E725887A36C0706ULL, 0xE15301B2136C05E6ULL, 0x0FF0FAF2C5E3B3DEULL, 
            0x737BF3AC07BE11C9ULL, 0x3261E9EAF02BB7D7ULL, 0x88D85336CCD35D9BULL, 0x535EB5660FCAE4D6ULL, 
            0x1312ADEAE0EB094BULL, 0xF9905606AD78B338ULL, 0x3B8CFB42EA484138ULL, 0xD73D1EB9D0450F15ULL, 
            0x66FD53688D4183E4ULL, 0xECBE3C6FCBC86075ULL, 0x2DF33CC889B31212ULL, 0xD4ECD46A7F0BCCD9ULL, 
            0x474C1E9E69D6439DULL, 0xE2A9DF25FD6ED424ULL, 0xBC2575F2AD6A83ECULL, 0x503C36A50D5C0588ULL, 
            0x4BBB4974CC6229A3ULL, 0xC457FD59CC914748ULL, 0x61C1F0E888028F57ULL, 0x4A8C567A2D845AEBULL, 
            0x1AE46C4AAB48C165ULL, 0x9961C56405BB862FULL, 0x51F9521410B8F725ULL, 0x1F0F63650E04B61AULL, 
            0x8DED250C9BAED81AULL, 0x5DCDBD42C0FD8A32ULL, 0xA005C32DB68731B4ULL, 0x55DA96945B7DC569ULL
        },
        {
            0xFCFA91CB19536730ULL, 0x237CF5C692ADE3E0ULL, 0x31406E6633F7690CULL, 0xF513BE395D7632DFULL, 
            0x6D64A25788642636ULL, 0xE487BE46597E8F90ULL, 0xBF45E8985F2ADFA8ULL, 0xB264291C7647DF7AULL, 
            0x124E19301F59447CULL, 0x39FA10C09B0F426AULL, 0xE5308C240CE54BE4ULL, 0xC858BF5DD31EC224ULL, 
            0xDE776448043980F9ULL, 0xE403364758182559ULL, 0x95AC9546777F9766ULL, 0x294DE9333BB81576ULL, 
            0x60FEC83D005A68ABULL, 0xDA4F27EE7C11C85DULL, 0x5323197277EAAFC0ULL, 0xB2DC910A3DB7A1C0ULL, 
            0x0B1F8287FC15A7F2ULL, 0x919435C0F3E21DCAULL, 0x46C2ABBF9910CA7EULL, 0xF99FC04E50F3AE9BULL, 
            0x99B7EC020AAE6492ULL, 0x8677B83C00C45B0AULL, 0xC49276FAB4B6DEE8ULL, 0xCB6756330DF4E23DULL, 
            0xD8861B5161D706D8ULL, 0x6348FA73B42ECC75ULL, 0xD2D7D8422F74F09AULL, 0x786B5768C531EF74ULL
        },
        {
            0x126596C84D844BABULL, 0xF576F2294C416420ULL, 0x63A091FA89D81CE4ULL, 0xFDD2A2B9F1713300ULL, 
            0x6B13655BEC495460ULL, 0x3DF4739FC632CA2EULL, 0x742D92C1EE5409B3ULL, 0xF71256F8B8F125EDULL, 
            0x6F30BF1F01FE70EFULL, 0x42FD79F9FF34E30DULL, 0x92F97D305D32EEAFULL, 0x66D6643822C87136ULL, 
            0x35B7EF5B81E04F1EULL, 0x5F45636F4A9D8EEBULL, 0x47AF5E561A4A586AULL, 0xE9CB4A548C355A19ULL, 
            0xF0DDAF69A6945BECULL, 0xD447C0DA079DDC73ULL, 0x281561C75A0E5087ULL, 0xBC8444D979D8373CULL, 
            0xB8C8D42FE033D017ULL, 0xCE1C422EC3831FC6ULL, 0x40D9C945A34A54D1ULL, 0x03C1509440440584ULL, 
            0x70769C5D3CF15092ULL, 0x5D18D07BAF82A9DDULL, 0x6C1F647C747B6DACULL, 0x844A15BFBA0EC509ULL, 
            0x35FA068EFEF601E7ULL, 0x3372D3D97E92B3D4ULL, 0x90FBE4B3E88E4E54ULL, 0x8305A61D98F9C7B0ULL
        },
        {
            0x88FA16B1C7F60205ULL, 0x8B382C54787CAF57ULL, 0x74101816951F5476ULL, 0xF2A655FBAE59371FULL, 
            0x11C255D1CEAB7890ULL, 0xC8EEE76CB0CF0BCDULL, 0xDED35744C5872DB2ULL, 0x0D70FD965F7A11D7ULL, 
            0x26E6B182C4238DB7ULL, 0x49245A18E68AE4CBULL, 0x11CFDD1843B675FEULL, 0x7998B853CD06BAA2ULL, 
            0xFC1EC0B36430BE79ULL, 0xA0BC6C30B9AE3FB6ULL, 0xA0F7F51C861DF5C2ULL, 0x75E4F452FBC602FDULL, 
            0x6729176045E205FDULL, 0x99D7E2402C7359D6ULL, 0xF442CE108A774267ULL, 0x97A4D6AD59CA3732ULL, 
            0x743C006F8835F9D7ULL, 0x0100482DE00F9837ULL, 0x1E1A8ABBB00DBF19ULL, 0x8FE13F21E0C6E7B5ULL, 
            0xFCF04361835053E3ULL, 0xF3060ABB0EF283EEULL, 0x820924E48BE08D77ULL, 0x5DD58FAF97C2F987ULL, 
            0x349218F31760BDAAULL, 0x6EDCC49A881AD0CEULL, 0xED3ED9717FBFA3A3ULL, 0x03D9609E580DFE7CULL
        },
        {
            0xA1B5670700C53952ULL, 0x55C7749FB9B26B8EULL, 0x0D0E6E2475D17007ULL, 0x11D94615F1AE2E92ULL, 
            0x299CB742502A884AULL, 0x590D324E2D15462FULL, 0x3C96F052183EDE51ULL, 0x00BB64645E5DCD02ULL, 
            0x96D559020EBE9414ULL, 0xF9DBF6767FF531EBULL, 0x475401E161158E3CULL, 0x6DF459D9149532DDULL, 
            0x8D4C08B83F6CE09CULL, 0x8AC0ECBEE4307CCEULL, 0xEF1102D920882F85ULL, 0xAC1AFB8A99C2152AULL, 
            0x78947A284932FA4CULL, 0x72BADB746C4C9C71ULL, 0xB48480C15B785B16ULL, 0x2400A07FC0F34622ULL, 
            0xDEED3E673769B6B3ULL, 0x2956F984101ADB3FULL, 0xE45E8966844F7526ULL, 0x72C3BBA181FB2A22ULL, 
            0x36547D34E97BAE2BULL, 0x894CEB8820AF535AULL, 0xA97A344AF01DCFB1ULL, 0xC46B67A31F5F807CULL, 
            0x7AB7599341C085EEULL, 0x2FE000A41D027461ULL, 0xF30FD8BE8E0AFA88ULL, 0x86B8945079165B61ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseAConstants = {
    0x53B8180C10DBECE0ULL,
    0x5A83A2A190CBC134ULL,
    0x78AE23E54C55DDC2ULL,
    0x53B8180C10DBECE0ULL,
    0x5A83A2A190CBC134ULL,
    0x78AE23E54C55DDC2ULL,
    0x01CE378CC04BA312ULL,
    0x3AE25F4A486CCB5AULL,
    0x07,
    0x1D,
    0x47,
    0xDE,
    0x81,
    0x33,
    0x7F,
    0x7D
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseBSalts = {
    {
        {
            0xDF0C223E04B305A9ULL, 0x8B0939DA48AF29C0ULL, 0xB707AFD4FA9AE72DULL, 0xD8EE4F76F9C94218ULL, 
            0x587159B0A676D71FULL, 0x9732E5799CF50B79ULL, 0xFA72727AE28B5EBFULL, 0xF05519F65491F7AEULL, 
            0xEFCBCA37707D3C83ULL, 0xC37849F9D869ECDDULL, 0x886754F194D3D242ULL, 0x35D7E592F885A234ULL, 
            0x9DBA33B46F4AD4F6ULL, 0x3B784EB6E09F7839ULL, 0x262B975CDB564CA3ULL, 0xF3072BB08269A400ULL, 
            0x19F3F3D52CC1942EULL, 0xF76B121F6C38DBB6ULL, 0x4ED822E5466BF540ULL, 0xF31A5DDBF6684DD2ULL, 
            0x2401C6FBD0F74840ULL, 0x13E359E011A32744ULL, 0xB0D6D9F39079EF31ULL, 0x3BA0B91E47E97C80ULL, 
            0xECB97C92615D9FB4ULL, 0xE0CAE5742059D4EEULL, 0x9AD4EFE4480DE5F1ULL, 0x78BA6EDBC6F3D6D5ULL, 
            0x3F588950E47D89DEULL, 0x37415856A992830EULL, 0x78411F240B4D3276ULL, 0x218B1CB53709CA22ULL
        },
        {
            0xF6E9F9551F82097FULL, 0x60AA3B58B2AE4BF1ULL, 0xEC457329455CA75BULL, 0x627861577DAC5BC6ULL, 
            0x3174CE1F5B20F54BULL, 0xE7DED6FE239B1EABULL, 0x9EFF5E13B20B7C4EULL, 0xD34D7921B3300096ULL, 
            0x677607B8A71F93A2ULL, 0xE13A3BABF61D7FCBULL, 0x9534798F478EE9A8ULL, 0x9075E1C4A72CE8FAULL, 
            0x943A857920E31FE9ULL, 0x47855E5698503DBBULL, 0x64AE413D96FA07CAULL, 0xABC07B1ADAC2A01DULL, 
            0xD7B6AFC7F0BF2F1BULL, 0x7FA118126CF0F523ULL, 0x87B1722E4375F5ADULL, 0x21FD2E695D1572EEULL, 
            0xEA0F34651277F0C2ULL, 0xD6A48A53C4A8E70EULL, 0x5A2E04A7AB0AE37FULL, 0xEBC41CBB1290DCF4ULL, 
            0xC84B49FC1C764AD2ULL, 0x8AA55458AE46A04CULL, 0x2F57EB849D0D2F3AULL, 0x3BF03452A9783483ULL, 
            0x9FA4FED4B3E462A4ULL, 0x4E3A6ACBBBC85083ULL, 0xC15C31219525FE38ULL, 0x40B54F0C4EAEDE86ULL
        },
        {
            0x696DDC87C972EF84ULL, 0xE9DB80C19C6B0F6BULL, 0x7E48921AF82162EFULL, 0x0400E30EDDF6C937ULL, 
            0x9E44E3E9CA033220ULL, 0x9E00F65AD9CA4520ULL, 0x329E5A10CC335904ULL, 0xC99F27192C4169B6ULL, 
            0x3795B40A279AADACULL, 0xE9E1A4AA246F6ADFULL, 0xCC3432DB7EADCFD7ULL, 0x1DDAFBAA4B042119ULL, 
            0x1AE6CE91AD4D1A48ULL, 0xBD5350D52EF0404BULL, 0x4F4042FDD61B4473ULL, 0x8F8AB21E55A3E5C5ULL, 
            0x44152D812BB16D90ULL, 0xAA5009D6AFCE54B7ULL, 0x2F38314855EBBDB9ULL, 0x2404F12BAC1573FBULL, 
            0xC3327C6A3C08C9EAULL, 0x6E1FC12C2DAF60A6ULL, 0xE13A1501A70BB898ULL, 0xE4C8C1DA0168FE85ULL, 
            0x85C027386C306E99ULL, 0xEE01692BE235D63FULL, 0x6BC66AC4F88E3B9DULL, 0xDA597DA76ABB7FBFULL, 
            0x0B9489C520A07BDCULL, 0xCBA21F1A591B16BEULL, 0xC29E28EDECA8EE55ULL, 0x2427CC27F0E70568ULL
        },
        {
            0x4E2C55ABE786124FULL, 0xCA6F441FD40856A3ULL, 0xCAAC1591D7D4D49AULL, 0x323BCF11CFE75586ULL, 
            0xDB9F701754F951E2ULL, 0x0A29E29929D35E3BULL, 0xF1FDE1F70F9360E7ULL, 0xF9D11C630FEAE149ULL, 
            0x46E2AFB4796C1178ULL, 0x2E0EE499076DA5B7ULL, 0x9A6675835ABFC474ULL, 0xA9C5944197894960ULL, 
            0x60EBBDEAA65AEC22ULL, 0x453D6C1D3D46776BULL, 0xC0F75A49DE6CD100ULL, 0x828806CBF09D6BA8ULL, 
            0x29C8A80B047DFD2CULL, 0xA69CDBFB3377935DULL, 0xB224A754C42B5821ULL, 0x36116A4368CEFDF4ULL, 
            0x9A12B15AABD3FFF8ULL, 0xD00C0D7D7AFF2393ULL, 0x0757FA062D987856ULL, 0xDFC454994A67CB9FULL, 
            0xD9660E4A02FFE06AULL, 0x72A5D457E55B6397ULL, 0xFB617A097DAB2F8BULL, 0x23AA0C887C05A5EFULL, 
            0xE7335EA54CAC65D3ULL, 0x39350B4A29A7AC0AULL, 0x2157E288553D3087ULL, 0x6173C1220A255BFCULL
        },
        {
            0xF2ADB90AF5B3BDB4ULL, 0xE1AB5A74C09C9A89ULL, 0xA5F52198EF657243ULL, 0x8A9C2F843C45A3C9ULL, 
            0x1D31F28534CFE22FULL, 0xA22613A7C4A3908FULL, 0x674852FFCCDD95BEULL, 0xDB8CA61B4F12151EULL, 
            0x87283B2DB3930CABULL, 0x226276C7CCBEFDC2ULL, 0xF2CAD085BB4A19F5ULL, 0x78AB21F3EC96319BULL, 
            0xE8D6E08A9B2018A2ULL, 0x18D70D8DC96D3FA4ULL, 0x9AE75754C656C5A2ULL, 0x8DC72F6309AE2436ULL, 
            0x877153F2D1BA6358ULL, 0xE8AC4CF025950360ULL, 0x5F9362E4D3867DAEULL, 0xDAE72EC824BD7355ULL, 
            0xFF194552106186E1ULL, 0x81F146774F5F4CA0ULL, 0x5A7C40D1C8D10645ULL, 0x8EB5BB0353139228ULL, 
            0x18F17FF6CA91FEFEULL, 0x9A6FA6ED0CAE6B6AULL, 0xB1E8B51FB0682E46ULL, 0x21CE8A58D3C13155ULL, 
            0xE8BAE720E6C49F93ULL, 0x20DB43E94DB2F9CBULL, 0xB88931848F9C13E3ULL, 0x040F62C5BB0519E4ULL
        },
        {
            0x69A966A2068EFB08ULL, 0xDE957002009AB321ULL, 0x435E5CCC99A88F53ULL, 0x833CCA34F648B294ULL, 
            0x5E6CE02C36FB88BBULL, 0x815D07C9EBC85F8EULL, 0xA6B5A29BB5DAC552ULL, 0x2C6427814FC723C9ULL, 
            0x730E976DA5115E01ULL, 0x88964203B1F84EE9ULL, 0xDD6A4D9B223C1617ULL, 0xE6A6645CCCC5ADD1ULL, 
            0xE4D300FAE1C3DD6FULL, 0x3FAEEC1870E49537ULL, 0x9D8AF9742E6F0CE7ULL, 0xBD33A0F8EC1DA518ULL, 
            0xE68A7DCFF7C1D19FULL, 0x0EC8024717AB3C3DULL, 0x940E7EE00472F1F0ULL, 0x0914073C2EE9CB5AULL, 
            0x4B62FE37ED7D7EECULL, 0x0B2BB13FAE4B3CE4ULL, 0x0990DDB8F5E1EEB3ULL, 0x5A1EBF54DDF52182ULL, 
            0xD97FA858DEC8C91AULL, 0x4B7769972D9D0694ULL, 0x5328DE8C69DB2158ULL, 0x8B5C71D8F4955924ULL, 
            0x701C4BFDB9B231FDULL, 0x2A4798ABC139B18EULL, 0xD1F4B49964C979B2ULL, 0x534B96842C1F99C2ULL
        }
    },
    {
        {
            0x151A6154CD61D791ULL, 0x97998E394743F1ACULL, 0x42BDB69B014C0027ULL, 0xA5211967E0EC9F03ULL, 
            0x76289C171B1C97F3ULL, 0xE917076C77D11E2BULL, 0xB30A0F6E1793C606ULL, 0x7058798DF845EB09ULL, 
            0xFA7CBB17D6ECC909ULL, 0x6F09BC8AE972CE48ULL, 0x67C0A382688A0D81ULL, 0x8B411D20F6492B71ULL, 
            0x907188929C2359DBULL, 0x0B31E8F4D3BE3D51ULL, 0xDDC10DE971842AE9ULL, 0x4099E111E71D3FF6ULL, 
            0x05F50DA62ABF4CD0ULL, 0xD5020FB8F0CC46A5ULL, 0x8882264C53EAEADEULL, 0x086DC1DA28B68C32ULL, 
            0x98EFF6127E347497ULL, 0x8BDCABAA8B492703ULL, 0xF7FC37171D3E8CE3ULL, 0x8B79F51501C6127DULL, 
            0x345043217FB258CCULL, 0x33A074CE6AFDBF3DULL, 0x6B1861E53856C1D6ULL, 0x3202E0652D75E22CULL, 
            0xE4BDF06EB6E62DFEULL, 0xAA266E2461C0F360ULL, 0x9F1B35C190A2133CULL, 0x07BC18F0C7ACCE14ULL
        },
        {
            0x07CC140A71778099ULL, 0xE092D5458F4842BFULL, 0xF3C959D3A74FF24AULL, 0xFD4EE497C2D3EE92ULL, 
            0x9951393B3EEF5EABULL, 0x502135AA32A9CE55ULL, 0x40670D2FE97043C3ULL, 0xDE488AB7836792A6ULL, 
            0x1BA684E92E561E7AULL, 0xC4A8983D61D8492DULL, 0x1C3C697CE3728193ULL, 0x295E3F9F67A4AD2AULL, 
            0x1E320FD4A5A030C6ULL, 0x1B0C1C43916284AFULL, 0x9E30E81CE59F3967ULL, 0x2FB49D9656B4CA17ULL, 
            0x7B46F8195AB3A8ACULL, 0xB60658C440A997BEULL, 0x86E1895C6B135312ULL, 0xB0628D95204CF505ULL, 
            0x19A5988CA243DCD4ULL, 0x1B8235DFE7825586ULL, 0x314379A958EEFDDDULL, 0xB777EF4C8B1FF772ULL, 
            0xE57F9D16DA049E34ULL, 0xCC6365F2DD350864ULL, 0x9EBAB8D5D29B965AULL, 0x30ECEF3B8D208B3DULL, 
            0x7071E9FDF5659286ULL, 0xCCB368519E20AF0DULL, 0x83132249A3A1F7C4ULL, 0xBD6A4B1E059192C1ULL
        },
        {
            0x0753CB5A8308D3F5ULL, 0x952619D1DD483C2AULL, 0x73F2DF5A366E44DDULL, 0x8FFCCC2AB3183020ULL, 
            0x3092652765680DE9ULL, 0x296D2C4E39108467ULL, 0x7DD2F27773F3522CULL, 0xF17A245A1B5ECF02ULL, 
            0x2B12A19F7C5B86AEULL, 0x590370FFEC06AE48ULL, 0x1D4BFF60A484EBDEULL, 0x2BA4877C55BA6676ULL, 
            0x90C02264D66D19DDULL, 0x3A66E0EEA8CD6AD8ULL, 0x23C3AFA655F365FCULL, 0xA3947E4DADA8142CULL, 
            0xC42BBCF5AA42D7BEULL, 0x0080709FA8585E4DULL, 0xFD8714E3E9EB9A85ULL, 0x0FC9997B3139B5A0ULL, 
            0xB22866F1E7F5EF6AULL, 0x0B5D6AF28612C980ULL, 0xBBCF19AEC3623F94ULL, 0x7A043E738FF5C49BULL, 
            0x99654D4447D6221CULL, 0xCEAFF3F80557CC68ULL, 0x8B76B932DBA74D60ULL, 0xB634D9162E175C16ULL, 
            0x3192DD77274AD5DEULL, 0x2ACE5E67B00119A5ULL, 0x3D511D0B1FE6DD5EULL, 0x766DA03E9831610DULL
        },
        {
            0xDC1EE3D20468E398ULL, 0xEAD8CB5C6D0CB238ULL, 0xB81C0A37BAA2B751ULL, 0x8E6D14A8E8803674ULL, 
            0xC2A2F6C9BBF3F955ULL, 0x34A71F69CADDDF39ULL, 0x5AA2CF85125052DFULL, 0x19C079A1C3DF57FBULL, 
            0xC70BACE12A3FD4E6ULL, 0xFB8D1D771E043E50ULL, 0xF5C890B106D33BF2ULL, 0xCFEC8904B5920929ULL, 
            0xD697538BF58DDBE6ULL, 0x47050349BAF3737BULL, 0x29E791E97C0D27F5ULL, 0xB2B1A609A02F8453ULL, 
            0x4635B2765838556DULL, 0xA8C5BE42198F14C4ULL, 0xFB3B9220ACCD1A50ULL, 0xC6540390B22605F5ULL, 
            0x0AD4DEF8D87D4B92ULL, 0x98E08A3812118BE3ULL, 0xD7427231849938AFULL, 0xC0EDEB3B5152BA6EULL, 
            0x15FE97C4F2ADE135ULL, 0xB4FE10A5088C3100ULL, 0xD6B96D1501A1DB13ULL, 0xA693595090B6D488ULL, 
            0xB8E68697BD2854A8ULL, 0x11A817BFDAB6F0D1ULL, 0xBDC0963EFF1681C9ULL, 0x19D5B80DBF8C571DULL
        },
        {
            0x6A851E070B3F0CDFULL, 0xF62F26F1C4A5C65FULL, 0x9F1B2AAE9C7374E3ULL, 0x4949078C7225C4E1ULL, 
            0xCB8E5144F448527FULL, 0x341944908693DACDULL, 0x90BFAD55AD931CCAULL, 0xDAC1D91E0BB5968BULL, 
            0xFAAA7DD50590B551ULL, 0xE3C2163F44BBA688ULL, 0x8189A0C58223B39DULL, 0x28B190EC8C4EB220ULL, 
            0x69A9515FFCEC3C4BULL, 0x3635A309103E341EULL, 0xBA6C3F947D4EF06AULL, 0x1B4E04598879883FULL, 
            0xC6C3596FD19BD195ULL, 0x4B6C0F81F7D7C8E5ULL, 0xD23F11B915DCE464ULL, 0x6EE31FEA41F62C3FULL, 
            0x1B679506931B6570ULL, 0xC12921F7AD5B3374ULL, 0xC7CB1028E3D497BBULL, 0xE0E1880BC95F34F6ULL, 
            0x9C7263878449080AULL, 0xE49CF9ECA778154EULL, 0xCB764CEF6CFE2283ULL, 0xCE71A432CF1F54B7ULL, 
            0x1AF8B97259D92981ULL, 0xB03CE0E03AEAFD20ULL, 0x1289848A1EF622CAULL, 0xBFE8BA97D558B43BULL
        },
        {
            0x617A4E1FD4E5EA87ULL, 0xA0E9821BBC87083EULL, 0xD51D9D238784C35EULL, 0x57E5A1EF005CEA2FULL, 
            0x59040903B7A79085ULL, 0xD79233914A7E593DULL, 0x678865440D06C307ULL, 0x4EB90EDDA736ADFEULL, 
            0x0D53A4E98FB8570AULL, 0x5109F17D352639ADULL, 0x36DD4C04D3E57D1EULL, 0x67F2F2968D77BA93ULL, 
            0x9B9312DA7CC06182ULL, 0x8D93B7524C44D3FBULL, 0x38D91CFAAFE5EA9BULL, 0x711FBFC4268CB998ULL, 
            0xC18894524865DA34ULL, 0x0EFEA4B9F3BE31EFULL, 0xD2A52618A01A0367ULL, 0xB974AA6A505BD8F2ULL, 
            0x4A330BC525EB3D74ULL, 0x30607EB25C2A95CDULL, 0x68674DDD1941C5C9ULL, 0xED9A2853924B71A3ULL, 
            0x193BBE6452149DECULL, 0x9C3187E08BDC66BAULL, 0x57D5C6C7CC9AC0B0ULL, 0xB83C102B0B4FFFE0ULL, 
            0x90C718E7355BD2C8ULL, 0x85E7B8159F10B3EAULL, 0x9D8BB7D6299ACC71ULL, 0xE37B6EBAC966F6D5ULL
        }
    },
    {
        {
            0xC22C982F8174F19DULL, 0x0CA5A76F60704BF5ULL, 0x53741F72DD0FB050ULL, 0xD525D727A437D3FCULL, 
            0x334ABB67F4242EF9ULL, 0x24823D1821A322AFULL, 0x6B533E77E4311F4FULL, 0x239EF5F436AADC9BULL, 
            0x09EED7998B48B8D7ULL, 0x5933D55AC613D559ULL, 0x644D475CB0B2EBA1ULL, 0x2490F4BD4A7D46B7ULL, 
            0x8B84D34F3F14BFAFULL, 0x28B437BCEB58F86AULL, 0x2A0C60964C3253BFULL, 0xD05BBFF6F9AB9450ULL, 
            0xA0DB9EE8CE18D87DULL, 0xD99719E15F70C47EULL, 0xB3FCE3D47418A5BBULL, 0xAA4FDFDBAC5D42C1ULL, 
            0xB361A87D21E8EED7ULL, 0xB3E4979A989FCBC4ULL, 0xF5A45B70BFAA4D57ULL, 0xD71CAAC07041A225ULL, 
            0x3D7CF2237CEFC174ULL, 0x5379BAAD526FAF04ULL, 0x5D7721D1B0CA4EEBULL, 0x2D072C04A4D3104BULL, 
            0x3858395601470A23ULL, 0x2404430BD375800DULL, 0x3583E364C968099CULL, 0xB1195D6BAC3497F3ULL
        },
        {
            0xE6AADD5F89739A10ULL, 0xB9D39B453D515C0BULL, 0x6DC56F60067C2500ULL, 0x6569959ADDF6833FULL, 
            0xEE39131AEC523D1BULL, 0x1CFC7DE97A7670B7ULL, 0x2D63EA1273FF88F0ULL, 0x30C82B95E6A73845ULL, 
            0x7B7ACB9EF7B206A0ULL, 0x0E334259889FBEC8ULL, 0xE32968851E869884ULL, 0xBDF6E7983CAA2539ULL, 
            0x34C49A53A3BA3881ULL, 0xC94F988C5CCE2E5AULL, 0xE755A3989021E355ULL, 0x57C4D4E7C8DFFE81ULL, 
            0x599F99FC18E7CCC4ULL, 0x57D2770FDDEFE82AULL, 0x737BD31A4130B5CFULL, 0xC32D0A52AE347741ULL, 
            0xADA97E23201790B6ULL, 0x2D40651AC0FAA702ULL, 0xAF0BD8AE2E254D66ULL, 0xB3544A6628C00826ULL, 
            0x2E9FDDA70E3843A8ULL, 0xE66FCCE1826538FEULL, 0xEEB61052F8BF9C71ULL, 0x7F7CA0F13F079531ULL, 
            0xD09AAC90883D6D07ULL, 0xA20B70DA231598E7ULL, 0xA0066A92268C258FULL, 0x8FF93C80D7760CD8ULL
        },
        {
            0xBF9F6237769EC445ULL, 0xD365891D73C64451ULL, 0xC0E93B018D0481E3ULL, 0xA76D14B11A7BEB27ULL, 
            0x6255F0020D518DAAULL, 0x0221F744427FF698ULL, 0xD393E724D2AF30AAULL, 0xDD4973DCB34AE362ULL, 
            0x3944747133C03A3DULL, 0x2CCF8932361BF992ULL, 0x09138CF11EC30744ULL, 0x283F7BAF29684EF4ULL, 
            0xB63CE4F9E1AC978CULL, 0x12525787F6BF377DULL, 0xB7DCBFAC0EEE62BCULL, 0x025E9A1D532C154BULL, 
            0x0302B11054D63851ULL, 0x6E80216584D7916FULL, 0xAE512EA6760D4BFFULL, 0xEE806FBF917C4929ULL, 
            0xCC164C53A45BC946ULL, 0x247B921A8BE29F23ULL, 0x34BA829003027026ULL, 0x0BA4C3B1DFAA08EDULL, 
            0x4B519BA4C40938EEULL, 0x8D5C60135FF83AC9ULL, 0xCAA4EE8A38F0A94AULL, 0x9A174B3729E563FFULL, 
            0x31DB707F7AB4E4FCULL, 0x806851AA6A19CD88ULL, 0xA0B2E06878AEF636ULL, 0xA61B95DF22488E7AULL
        },
        {
            0x9FF607AB008894A5ULL, 0x57B5605BE05FE001ULL, 0xAB6AF445F4E6833DULL, 0x6501433E1F9DF757ULL, 
            0x6754CD9B2265B554ULL, 0x68C48DED36B24C0CULL, 0xFD01DDED99B1E0E6ULL, 0xFA906278A978EC4EULL, 
            0x2B0B449FC431B3E9ULL, 0x7BBBBD821B490171ULL, 0xFA884F08C37BBFCDULL, 0x015E97D83361B396ULL, 
            0x4FB05FA9DB02437BULL, 0x146F433C2A3E1FA6ULL, 0xE7C2FF2927860554ULL, 0xDC2A094D317BCA29ULL, 
            0x78B26C96D4B84F0CULL, 0x1AD7C31F49A8A87DULL, 0xA578203D91543662ULL, 0xDEE98B409A9E9D79ULL, 
            0x502969EB2AFADB29ULL, 0xC0472AB885E23366ULL, 0xC0BF796B21ADAD83ULL, 0x3D27772E6AD979C4ULL, 
            0x540E55A6BAB82DA0ULL, 0xA51313616A20A8D7ULL, 0x9D3B4DC0BDD5FEAFULL, 0xE3D5995DF9723533ULL, 
            0x52BE1BF770B754B4ULL, 0x121CD1E28EDA3E2AULL, 0xB24E8C5BD8425D31ULL, 0x5975CC65ED932C03ULL
        },
        {
            0x941134BAE5C4544CULL, 0xA2A1579A07A1EBE5ULL, 0x2BE285D8FD38F77CULL, 0xF48A49693BE567C0ULL, 
            0xA9056AFF93CC5AE5ULL, 0x27CFD7DFA1C25BDCULL, 0x96B2068508DCFCECULL, 0x77F95FB742A51EEAULL, 
            0x2C61F24A8F83C0BAULL, 0x7919D166AEDF17B9ULL, 0x0E565D526E586182ULL, 0x4081B67094879259ULL, 
            0xAD28C6D877C0D867ULL, 0xC538E7CF6E108C58ULL, 0x256D5C0A5C3F74F0ULL, 0xDDE46F33F991BAE5ULL, 
            0xD0A8F9A4ACD69BDFULL, 0x709F3BE97DCA6815ULL, 0x742C01B2C0642C2FULL, 0x5846F3088D236C88ULL, 
            0x99B5ED0C68BD3A1EULL, 0xD816901EC89C17ACULL, 0xFB8A00E02334D18BULL, 0x68407C06763757F4ULL, 
            0x74CD65689E3C0B7EULL, 0x5BD2628FAD68194EULL, 0x102EBC86A4015593ULL, 0x7457A00BAD95C045ULL, 
            0x2083D3580E55F660ULL, 0x5243D16339AD70A5ULL, 0x8EBED0D0FBAEE000ULL, 0x673BC81E0687617FULL
        },
        {
            0x400AF206EA7602A1ULL, 0x826CE2E52DA5716AULL, 0x6EF21CDDFEF218C6ULL, 0x08883959861943C6ULL, 
            0x1C8CBCA627C2D4F6ULL, 0x83541653A1D3CD96ULL, 0xF4843E86C93DF124ULL, 0x26CE7850F493F5BFULL, 
            0xEB1DDB917DE40B07ULL, 0x618BB1F367253693ULL, 0xB28782E7C9F361AEULL, 0x6AA7A12E19EA91CEULL, 
            0x6EFE29BDBFAE4989ULL, 0x6510D9395484F638ULL, 0xC430CDF0021BCCE5ULL, 0xA141C08492FE7568ULL, 
            0xD1B5A18779F06273ULL, 0x1351E1D2AB18F556ULL, 0x1C3649F4E652B8AAULL, 0x755201F7B97A995FULL, 
            0x1FCBD7340088C9B9ULL, 0xD161B0D6488EEC30ULL, 0x0269224C75698F51ULL, 0xF1E3ECC126A7C12CULL, 
            0xB658BE639B2C4486ULL, 0x183CEAC214F5A20EULL, 0xD654C72A1A73E370ULL, 0xF51792A7F1F0649CULL, 
            0x254D937169A736E3ULL, 0xB4A2E7812DCCC55CULL, 0xCBAC622120DFBF70ULL, 0x5C7C9AB8F6B01F6EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseBConstants = {
    0x655F40439D499269ULL,
    0xF5C44309CBFFC231ULL,
    0x84BF78D3C5FB342CULL,
    0x655F40439D499269ULL,
    0xF5C44309CBFFC231ULL,
    0x84BF78D3C5FB342CULL,
    0xFF5F9D86579D382DULL,
    0x58403BC448142C51ULL,
    0xDA,
    0xD2,
    0x8B,
    0x7E,
    0x16,
    0xAF,
    0x9C,
    0xA4
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseCSalts = {
    {
        {
            0xDBB1D4CFF30F2CC0ULL, 0x52534CF94C8B96D7ULL, 0xDA31B4901B3BD346ULL, 0xA705F22F0AF92356ULL, 
            0x3F455F26797002FCULL, 0xA293DDE643ED0940ULL, 0xE0EA5B23BC89D265ULL, 0x51DBCE0CE0445924ULL, 
            0xAC2AFE2DD417A6B3ULL, 0x7775A1F1770D2E8CULL, 0x02E45AB6D73C23E0ULL, 0x996755291BD2AEDFULL, 
            0xF40CECFA46DE1FF5ULL, 0x0979CA97B3132208ULL, 0xF5E853F68CB363FCULL, 0x5018F0AF5EB42B4DULL, 
            0x49F704EB0B85FC5BULL, 0x993049C070C9DE64ULL, 0x3D2F4F182E8CC817ULL, 0xAC5DD353669265F6ULL, 
            0x0047B19A1C83731FULL, 0x44F7F45DF007FB0EULL, 0xFE4A1EA623504E06ULL, 0xC70281970260E273ULL, 
            0x47E9861E765168E9ULL, 0xEC338C847567500AULL, 0xD913B4B739C77CD3ULL, 0x7A9AB48DBC59A790ULL, 
            0x2325C6E601F4A95CULL, 0xDC97E2E924713B29ULL, 0xCBD52F505C88F5EEULL, 0x3C94FC5454B72E54ULL
        },
        {
            0x576DFAFE04398DEFULL, 0x7D348022B2F9572FULL, 0x7504FBADCAA0205CULL, 0xC22C69FA5E137CB0ULL, 
            0x48F66A5D60A8E9F6ULL, 0xE78ED1B9792735E3ULL, 0x5328C9B13636F150ULL, 0x9A51CD6698866986ULL, 
            0x2EE652EC8F9F5591ULL, 0xC13CD1B62EF7266DULL, 0x18D80B3BD4E81A8FULL, 0x55C3B95E61184664ULL, 
            0x65D2C4CDF05B513FULL, 0xD74B2FE5E142AF03ULL, 0x0C5376C29FCB6138ULL, 0x232F8256675E1DDBULL, 
            0xB7390B029DB93213ULL, 0x72DAE592CC714A2FULL, 0x9737AC481E59ECCCULL, 0x5CADACBA6CAD6C78ULL, 
            0xE6C8DDBF0A386E4FULL, 0x0DB4DA5016FFFF91ULL, 0x13775C5E62082372ULL, 0x32E3DA51577F8529ULL, 
            0xB8D69B27F0225523ULL, 0xACE58EEEB59B232FULL, 0xD2080C2BA21D8B58ULL, 0xEE98AF6DC800AF98ULL, 
            0x4B1448194F26B578ULL, 0x4C381AE68EF9C44EULL, 0x10745D21ABD92A1DULL, 0xA8104213E6B9ADA0ULL
        },
        {
            0x29F52FF3D233957BULL, 0xCC7DB2251774BA76ULL, 0xDA7E1BEDF3236808ULL, 0xC6F6E9CE4CD2026BULL, 
            0xF8324C39C76CFD2EULL, 0x24EE792FE0856744ULL, 0xC60CB23A3CA52FB0ULL, 0x9522EE52D608FF0AULL, 
            0x4FE712C934F42B74ULL, 0x54DEED0140F9A224ULL, 0xEE407C869264979FULL, 0x9BCD9343F40821B3ULL, 
            0x046F8F5667E5688DULL, 0x70BFE67FBA6A44FFULL, 0xFCF7A8A79A48D91CULL, 0x2654642318EC9EE2ULL, 
            0xAFCCE475EEE4184CULL, 0xDC278D020B6AE1EEULL, 0xB9688EDBEECFD37EULL, 0x864196974BE1E87AULL, 
            0x1DA4A5A74BF28A43ULL, 0x1256DDD6A5A2EF44ULL, 0x0FF9447E46A7FAFAULL, 0x2347FCEF6D502ADEULL, 
            0x9DD835DE9EAB3555ULL, 0xAF20C259C9D960EBULL, 0x72EB10A92E354970ULL, 0x929094C4D9D3BFB5ULL, 
            0x2B06902EEB29394BULL, 0x0BB6C1A81481AC13ULL, 0xFC36DE2042E51B08ULL, 0x2E033BAF0BBBD863ULL
        },
        {
            0x0010348A40D10DFAULL, 0xF9D0825CDDBECDF6ULL, 0xEFEC00289E6AE163ULL, 0xE89CEAA77FED8DE7ULL, 
            0x2EDB5A52290C319EULL, 0xA0429736BB8E6DA8ULL, 0xEC731EC0878E82EEULL, 0x4FDDBDCEC5BAD131ULL, 
            0xC2A93126FE2AF9E5ULL, 0xCBEE4FB22A83DA3FULL, 0x847B7F924F00F991ULL, 0x8529179F14707CA8ULL, 
            0x7D3D87A8186DFC96ULL, 0x3A5C735B8751B285ULL, 0xD26BD3DE2FA32615ULL, 0xC954B5C22823FB39ULL, 
            0x04A6875DC648E96DULL, 0x7F4D4C68DCF6D613ULL, 0x6AFAFB3CBC502236ULL, 0x81581A4B07986F1FULL, 
            0x55912772C43C6784ULL, 0x2F078BB3D288E28FULL, 0xCDB6B8AA6D602789ULL, 0x9E43D7235DA92D22ULL, 
            0xADDC9F6779C21592ULL, 0x207D361CBE0564DAULL, 0x7586D37E65499620ULL, 0x4B64F66AA3B20F6DULL, 
            0xD7736D6A0BECC5B3ULL, 0x733BDAEB81E6194FULL, 0x662BDDE09821FAB1ULL, 0x7FCBA0281BB195BEULL
        },
        {
            0xD74A78D7674592C1ULL, 0xB7A0D0A059167328ULL, 0x0F7BCD1E44FB6452ULL, 0x27BE26BF2928F040ULL, 
            0x635275FB8ACFB368ULL, 0x5C9AD2EB2FDD7D09ULL, 0xAFB2F34600443097ULL, 0x3D2413BF94310085ULL, 
            0xB21437EBB2704830ULL, 0xCC2615508E698E32ULL, 0x76C08B0D3014E867ULL, 0x15A45174031E8FC1ULL, 
            0x19751666C2CC3473ULL, 0x30EC1A791751A414ULL, 0xC315BB610A936BD2ULL, 0xC72B6523001D9956ULL, 
            0x670FEB5089E495E2ULL, 0xB24E3CC0BE542915ULL, 0xEB683091BB5C5232ULL, 0x11B5CE356C125292ULL, 
            0xF50AB4EA81D6C361ULL, 0xB944EF2621A138C7ULL, 0xF4C603C936A12B6BULL, 0x5B070F3EF13CB738ULL, 
            0x9D2B5F3F16226D46ULL, 0x2F63894B8107E5A6ULL, 0x2EB27B8D0BA77D88ULL, 0x399EAD36953EB294ULL, 
            0xB2F2EB28A82AA45BULL, 0xDBF64D29A16B31B4ULL, 0x8014C5B24EAFDA4FULL, 0x113843C43DC20595ULL
        },
        {
            0x775BF6296D982718ULL, 0x80CDD63BDD4C1220ULL, 0xD44A6D80124118D7ULL, 0xB8EEDBDE3742E200ULL, 
            0xA7899DF02AE9CD1BULL, 0x3042F2A6508D4135ULL, 0x24D26757D4B2948EULL, 0xA679600659B82B41ULL, 
            0xEBB7C8B4A353C3D5ULL, 0x1C98792C8FE0CA19ULL, 0x0E5AF8EEC297932BULL, 0xBB67932983BE1223ULL, 
            0x724A44A53EB877CDULL, 0xDAD143247B9EFC99ULL, 0x876056ADE83AC3A8ULL, 0x4DF2C07A29B4FB06ULL, 
            0x85A0DE38E1BFA4A6ULL, 0x5B41612D11DE4579ULL, 0x4956045FE4B585A5ULL, 0x557F563CB8FBED1FULL, 
            0x1AA0486057F62540ULL, 0x14659883EE6C3029ULL, 0x0FA8F973A5C0E877ULL, 0xB796A026B6503900ULL, 
            0x6531D24E4127436EULL, 0x45952B58E3FAF7D1ULL, 0x516524C92F60AF19ULL, 0x615CA0CD39296517ULL, 
            0xB71FC44D7BC1F624ULL, 0x0635367EC579B9DEULL, 0x1735AC1829F6FAB8ULL, 0x028966CEB8B0718AULL
        }
    },
    {
        {
            0x4B931F4ADD4D3D29ULL, 0xB373CC661D857422ULL, 0x57EC18521BEDF31AULL, 0xBB0F116CF8C86E43ULL, 
            0xADC0C39E554E4C52ULL, 0x61945EE861E553DCULL, 0xC73FAE8DAC43FF8CULL, 0x4C37535DAACFA7DAULL, 
            0xFDE81F6642F012D0ULL, 0xCA9C7526E31B246DULL, 0x787EB114BBF85CBDULL, 0xBCBD2AC817AC35E6ULL, 
            0x4A80B2A357254547ULL, 0x5A70EE5190CE45E7ULL, 0x2F80F8BD2AFD052FULL, 0xDA147A6BDE1A7AD0ULL, 
            0xF136A2F3CE9797D5ULL, 0x0FE2470392D802F8ULL, 0xE34660161E5335BAULL, 0xAFDEB2BAA5B54D3CULL, 
            0x38CCF756FC4A42DDULL, 0xDEBC945CFE6195DDULL, 0x18FF5EA29C929EB4ULL, 0x866E77667D1D2B70ULL, 
            0xD656474E17D791E9ULL, 0xC42D634A94392A92ULL, 0x1E51CF5965C3AA73ULL, 0x6967AE1B3F902E49ULL, 
            0x3A5078A5A7478FB8ULL, 0x6AB5D9B68FBD4FDDULL, 0x8AB1C710EDC308BDULL, 0x7158006FF450A3EEULL
        },
        {
            0x179A75127EC7D95BULL, 0xD3F6444848570425ULL, 0xA29FD45ED99CD0F3ULL, 0x8F9A65DBB1EB7EEDULL, 
            0x5E71C3AB48D61518ULL, 0xA4FC9976F9C3AA26ULL, 0x174BC0FAB0D17D7CULL, 0xEAED3FBE0E69A887ULL, 
            0xE00D381C6A22A2F6ULL, 0x5386EE99F1FA53E7ULL, 0xEAB75DFEE24E8663ULL, 0x7DA384B1A05E1F48ULL, 
            0xAD1A06A5CA2507D8ULL, 0xEA5918A5F9AD4154ULL, 0x106864B39FC433C2ULL, 0x2A57D399BF581F75ULL, 
            0x107B68D17256D472ULL, 0x38DA25AC69771476ULL, 0xAE201F752D156A9DULL, 0x0886545E0FD70FFDULL, 
            0xDFD98F352D6E6A07ULL, 0x42C98771F4209678ULL, 0xE971FAD7383AE92EULL, 0x19C8A5CA07C0EE28ULL, 
            0x900C2AE89551DEE6ULL, 0x3656126A901091AFULL, 0x6326BF982CE78151ULL, 0x95D2542DF227CD14ULL, 
            0xCB69392AA9C3E9EBULL, 0xF8C3F46AFC0F3BADULL, 0xCE760DC8F6DE6BB1ULL, 0xC7CD41CA74131E8CULL
        },
        {
            0x7BF05C9E1714AD32ULL, 0x6A90A0CE6E4FEDF0ULL, 0x0683DF5FC8C74951ULL, 0x7D8F7444E2EB9F30ULL, 
            0xB2C11DC815AD2BB2ULL, 0x5BC66E9A9EA05C8BULL, 0xDA684D5E0261ACC8ULL, 0xAD453D97BA6883FAULL, 
            0x9CBD1376943922FFULL, 0x8242B57454C6A801ULL, 0x0E3E70C34F03AC2BULL, 0x8329B80B567D128AULL, 
            0xFC1D6C464302C61EULL, 0x8786B434736F4B62ULL, 0xE6269738325BD66DULL, 0x116EE08389B63ED9ULL, 
            0x983A1361AC2C4801ULL, 0x271D54210069CDDDULL, 0x27F2A59EF09053A9ULL, 0x0D06FEC8860DE94FULL, 
            0x74FB5500AD5474FCULL, 0x4273DF385D4722C1ULL, 0x5B504D0E4FB8A9CCULL, 0x0079C106C144D4C6ULL, 
            0xB9D49BFD41827CC2ULL, 0xFAC6081B04EDF80AULL, 0x3F8926E4C5CC4F5AULL, 0x3761BCEAE77B4637ULL, 
            0xDC27AE4F12018A22ULL, 0x39179B409718E6CFULL, 0x943FF00CB2D97731ULL, 0x60337089F6BF4482ULL
        },
        {
            0x84570CC7AD8E8397ULL, 0x86BD1D66B6E155C5ULL, 0xC7EB1F22E34A9F35ULL, 0x2C7C4ADCC03A1C87ULL, 
            0x1FAC978B4A7915CFULL, 0x94D869483E8FC497ULL, 0xB215A8FF32B4D9D9ULL, 0xDF107EDC89AC00E5ULL, 
            0xAB2252C5497DE0E5ULL, 0xB6A924D143457F7DULL, 0x7DD62F5C9D7D821AULL, 0x0A921CB70DF9DA1FULL, 
            0x7950DA3A8E4E588DULL, 0xA0BF57A55DE5A9C0ULL, 0x0F788104B51450AAULL, 0xAE82760D5E1CC4F8ULL, 
            0x9EDC4C9AF043A7DCULL, 0x35B161A06785B97CULL, 0xC8DC9FEC5562FCE1ULL, 0x86DC1A08DF2A3A2BULL, 
            0xCF6CDF3B9B3086B9ULL, 0xFE86DC9D96766AB3ULL, 0x101A53195ABB191CULL, 0x0AC036735A0061B1ULL, 
            0xABE918AC514CDFBDULL, 0x99064F096D9F0FFFULL, 0xC9FF63D14EB173ADULL, 0xFC8E0F08DD10207DULL, 
            0x054A108A845BE575ULL, 0xDA49036163A92E26ULL, 0x8A4A06BA6DFB253EULL, 0xF2EC25523F01C4DFULL
        },
        {
            0xB5475A5DE9C44133ULL, 0x5A6FA25DF4DFE077ULL, 0xC8910F5DA1B488DFULL, 0xBD6691200040F6D4ULL, 
            0x2142A0955275D365ULL, 0xEE3ED205C24427B8ULL, 0x05741909D5A5CEB3ULL, 0x6098893B2653E2DDULL, 
            0x3738750A563A5F74ULL, 0x3936F5B0EB7F52C1ULL, 0x93AF38EA01BC953BULL, 0x1CF8FE1A4ADFE754ULL, 
            0x07FEF5711F2CACF6ULL, 0x17EC758A4BF377AEULL, 0x3814B90AD33B63ECULL, 0x82E7F5B3E94541FFULL, 
            0xD125326594B4E7BFULL, 0x24058BD4AB3C8F4FULL, 0xCC407C25D72DBEBDULL, 0xBC750A87EAEF440FULL, 
            0xE915902280C45D98ULL, 0xBBEEC9143A6F3050ULL, 0x8846CF7CA9DDD175ULL, 0x34E3085D2C221672ULL, 
            0xB5E1369DAF1A3B90ULL, 0xE6B361F58C728612ULL, 0x57FE8169BBF5FA79ULL, 0x21927365E285F641ULL, 
            0x404A6F76ED6EC9DEULL, 0xAD2AAA315843E05FULL, 0x9E024F78CFDB27F2ULL, 0x0201FA0B575D6B92ULL
        },
        {
            0x86F12D21DF415E00ULL, 0x0F98D64593CD3A18ULL, 0x2D256B160258F1FDULL, 0xAC6B95693E0A3EF4ULL, 
            0xFACFA155701C0F9FULL, 0x80A1D41E3C316C18ULL, 0x7B5C1E3F3467C68CULL, 0x52E2D6424A611560ULL, 
            0x6F207D75E654905FULL, 0x3E9E8F62F9DD9119ULL, 0xE27F546F458D6FCAULL, 0xBD7A3FEC83C70A1AULL, 
            0x0EC02FC86B6E1B5CULL, 0x70B81B5080446123ULL, 0x19CE3489640A837FULL, 0x1C695AD5D66A59E2ULL, 
            0x3E13323FD6C91E2CULL, 0xB0C1AA5C66934FC6ULL, 0xB0556108D98B826DULL, 0x93B58E19F2E7CD23ULL, 
            0xD6F5A9E4616E75E0ULL, 0xD65242D3064C45E7ULL, 0xDDBE375A4389D5FEULL, 0xCA98238E81927F0BULL, 
            0xF96FF82A01FFEA11ULL, 0x9F290C85A2CB159BULL, 0x4D64602D71FAC11FULL, 0xDA466EB9645B2D1FULL, 
            0x95A1D419F5E6D108ULL, 0x77C5E5AD1E61E90CULL, 0x77ECEBAB964909DEULL, 0xFE08E9E5C6340671ULL
        }
    },
    {
        {
            0x449459FF0AC07E13ULL, 0xC9FB40AD260C681AULL, 0x3AAC882540F5F497ULL, 0xCB108158024C200FULL, 
            0xC037C5891BFAF1FAULL, 0xF86C8E2FB8623D3AULL, 0x2C585EA4FF742524ULL, 0x33BD625A41FFC7C3ULL, 
            0x4120238FCB37E967ULL, 0xF094E94DDE05F688ULL, 0x732EDC41EBC7C43EULL, 0xE16BD4BCE45DD1A9ULL, 
            0x48E5AC01963F6307ULL, 0xA2D826C947FE8BAFULL, 0xFAFA5728C17F988CULL, 0xD387D1FA0EED6272ULL, 
            0x06FCA4E87F4392FAULL, 0x11F024682E947C05ULL, 0x363284D12676C287ULL, 0xF919606C3507FA7BULL, 
            0xC76ECE0AB5CE7202ULL, 0x8C39D41D7B849204ULL, 0x2ED5082482B4708FULL, 0x64548F1A0AE23B8AULL, 
            0xB145F13E7101C414ULL, 0xC65753A4BE9F2D2CULL, 0xB285A3AF077365DAULL, 0xDF094F2E38069D5BULL, 
            0xB7D31ED080BBE673ULL, 0x1B85DCAE27450269ULL, 0xD824454993E359DEULL, 0xC0A582F6F1457039ULL
        },
        {
            0xFA730B611289B1A4ULL, 0x8CCC6D2CB7D4B4C9ULL, 0xBE1A736A611ADFFFULL, 0x8954A46A369300CCULL, 
            0x4F93BC9346143304ULL, 0x5D98B34B9D1D40D0ULL, 0x22C90D7C3B03D674ULL, 0x4ADEC6E584CAF060ULL, 
            0xDEE0CB193AA24DE0ULL, 0x1D42DB8A0584974AULL, 0xDCAD309E02DC7646ULL, 0x5F4D89237F16CBA2ULL, 
            0xCCC1C4BF1DAED122ULL, 0x2C5EA212DF99E16EULL, 0x585FF9CB4E8EE052ULL, 0x4F6870F5696032FBULL, 
            0xA6922CF46A1B9B84ULL, 0x144E43E73E794E2BULL, 0x14BBC4C42F1AF917ULL, 0x46ED0DD45B39F72CULL, 
            0xB0AD34ECC9C2FD4AULL, 0xACD226B18D2AFC6BULL, 0xBB6AEB0C3BB4D53AULL, 0x4847BA68B4C52374ULL, 
            0x2EF0B1E4453053B0ULL, 0x8B8ECFC16CE0BD39ULL, 0xBAD218452554BD51ULL, 0x433DFFAC7EE20131ULL, 
            0xDC46D89F3C48AC9BULL, 0x58700C16A5E9F1C3ULL, 0x829467E2F285510BULL, 0xAA05ED84D68140BCULL
        },
        {
            0xE7F556C30E75E78DULL, 0x4EDDD66C777F7549ULL, 0xE674643402F19B06ULL, 0x38EF8C2D12B577B0ULL, 
            0x801F83BE15F39D4FULL, 0xFEC6047BFA12F709ULL, 0x104C29CB3F0130BCULL, 0x1894EB45AD429346ULL, 
            0xCB3F2B1FD793A04BULL, 0xFF6EA1FB113757E6ULL, 0x258BE47D61DEB082ULL, 0x231819F5834605BFULL, 
            0x159DDF9044F97432ULL, 0xF4388E78ECBBBCEFULL, 0x77BAAF4D7BFD99B0ULL, 0x4B5825C36EEEB4A7ULL, 
            0xB8DE1DB2ECF3CF58ULL, 0xE82BD1D58ED0B4D8ULL, 0x65B4589B9BCA291BULL, 0x14C7249C108CCB2BULL, 
            0x870C6B849F8CC614ULL, 0xB2CEF1149027FB2EULL, 0x0396BFC9C63749BBULL, 0x3A287425597726E5ULL, 
            0x3449BF1E2477A04FULL, 0x0CC6F0B725778DC8ULL, 0xB9B30D0088E13EB2ULL, 0xF70261BD446B14E1ULL, 
            0x97F46A0550D9AF45ULL, 0x91CCD6C2AE342DD9ULL, 0xA80F0EEED0901B87ULL, 0x9769655C155F8956ULL
        },
        {
            0x5B26DA787C8A31D5ULL, 0x6D4628ADDA4AD718ULL, 0x4969124E90D2F0C7ULL, 0x371F454B6C954FC0ULL, 
            0x4EB26E78FD0A7685ULL, 0x1884BB60701C699EULL, 0xCBA065BC8DEC6E27ULL, 0x7B21D663E5AF802DULL, 
            0x9C3E7BC7EE72C650ULL, 0xCF81E83BE64ABD28ULL, 0xE616B86680E5D06AULL, 0x9758187E38D1A2D4ULL, 
            0x61F564D076BFECF1ULL, 0xCC00108BEFBD8FDFULL, 0xFBA801B4F8364298ULL, 0x74B93D713019FEC2ULL, 
            0xE91D3760A2C6C904ULL, 0x513402D5A475B1F0ULL, 0xA0141976465DACB0ULL, 0x48140E47586A62E5ULL, 
            0x4E8E451D7736B393ULL, 0x5072F20135EEACAEULL, 0xF7225B4A2D79DAD4ULL, 0xAC2795F2269B4DC9ULL, 
            0xEF9BA392C56F345FULL, 0x4FE8F3F0EC1D100DULL, 0x78AB69EEA6EC6BB2ULL, 0x6FAC562D6AC0F6BAULL, 
            0x2C85A0798F8821A2ULL, 0xA47AED17491FDF97ULL, 0x38DA177D430D5AA9ULL, 0x3C852B25A6CF5A92ULL
        },
        {
            0x6D4D3E379C913BCAULL, 0x1782278704F256F9ULL, 0x767332AA1000F8A8ULL, 0xE1039BFD1C05A3EBULL, 
            0xFBCDFC6B6D616C83ULL, 0x6316A33A93AEE5C1ULL, 0x23E76FA8CD0446D8ULL, 0xB258FD50CFBFDF45ULL, 
            0x23AB663947DBDD6EULL, 0x33E6182EAF517E6DULL, 0xA85EF4806C18C0AEULL, 0x1922E2EA5B7E5FF1ULL, 
            0x771D7F1EFDF8945EULL, 0xCCAC5986A2DFEB48ULL, 0x611C4CD1AE12F3E3ULL, 0xA7D9DA3C0ECB1F4CULL, 
            0x8368CC767513F125ULL, 0xDF0C870F2A882C6AULL, 0xE991179C9E527373ULL, 0x9D4EDF7E7859484CULL, 
            0x095BF45BE73542BFULL, 0x2C1DE581DCB41D72ULL, 0xEE74FDADD0DABA47ULL, 0x0FA619A85250A57FULL, 
            0x2513A6D28BF03FD9ULL, 0x81F8119AB0664442ULL, 0x0D31B0BD923CC621ULL, 0xA36CB6B5ED563058ULL, 
            0x66F54E987D8F64FAULL, 0x5A57B761583790FAULL, 0x6A18BC754D322CD8ULL, 0x2BE287C4D15E90B0ULL
        },
        {
            0x4315C696F2CA2107ULL, 0xEB1B7B36FCA61A66ULL, 0x5F9093A1DF0A1E89ULL, 0x2896D422E4770A06ULL, 
            0x9C991E02D9E4D196ULL, 0xF7E9D723DD7516F7ULL, 0x58ECA2A018B149A5ULL, 0x97BE97EF6B0BF50DULL, 
            0xDBF1E31AFFBFD07BULL, 0x24770A59410DFEC4ULL, 0x1B803B97D3332530ULL, 0xE909E28DCAAE70C6ULL, 
            0xC6C6AF86E6552E1AULL, 0xBBF9197FA0A5F180ULL, 0xD66DFB17DBCD15EFULL, 0x6E69DF801380FF56ULL, 
            0xF3D418FB317DF778ULL, 0xC8A19F2B9B1DAF78ULL, 0xD8F00EB74B036750ULL, 0x965CD56C15C77B33ULL, 
            0xD2CEF15105F3A7B9ULL, 0x6DEB1C12C4CDC293ULL, 0xB38966BEBF3AB44CULL, 0xBC91BB2F379ADC1EULL, 
            0xBC7D1E9DA4B0C01FULL, 0x84DF1744452B9CC5ULL, 0xCF72B11FD754834EULL, 0xA8F49DC34227D100ULL, 
            0x469ACF1BDF6CF842ULL, 0xAC698EF9F80C9959ULL, 0x7B35823BEBB0E79AULL, 0x1EC115275FE799F3ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseCConstants = {
    0x2A73015807EE763CULL,
    0xEA0B6DDF996DB2F0ULL,
    0x838ED3541095B507ULL,
    0x2A73015807EE763CULL,
    0xEA0B6DDF996DB2F0ULL,
    0x838ED3541095B507ULL,
    0x662F9211DCF781C4ULL,
    0x3556D792E5E1F7BCULL,
    0x94,
    0x11,
    0xD5,
    0x37,
    0x6D,
    0x4C,
    0x3C,
    0x93
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseDSalts = {
    {
        {
            0xED0541443D13E069ULL, 0x37BF6324F580DF08ULL, 0x919000FEC0B797B5ULL, 0x04D0A6A868F9235FULL, 
            0x837835489E97E272ULL, 0xBF33088F58B72E11ULL, 0x86F28A3E5138CB1CULL, 0x7F2CF9DDA97AE7FFULL, 
            0x902857E37A244467ULL, 0x2C652D54B18D3F38ULL, 0x03F843BB6E2B28A5ULL, 0x6F5497C8FD853654ULL, 
            0xE084103536EC456EULL, 0x941119ACCEF81443ULL, 0x3BA62B7D8B9BF173ULL, 0xDDCABC62DC4C2D40ULL, 
            0x8EBAA64B462D9CD9ULL, 0x98F3CAA4AD429B5AULL, 0x11918FD790B7D7A3ULL, 0xCB7A8A6AC6350F82ULL, 
            0x43F187BCE9D04D41ULL, 0xBD81055B8709EFA9ULL, 0x9557241AA3A1C7F7ULL, 0xFFE468958390C9B9ULL, 
            0x7BEC0891C997B905ULL, 0x96A448B88265A479ULL, 0x0FFDCC9E26574BC4ULL, 0xF9BAED722A02699FULL, 
            0x2F39170B920F4EE8ULL, 0xBB94F81F5116D9A7ULL, 0xF985235B1D1BCBAFULL, 0x1097C87AA51A92D3ULL
        },
        {
            0x53AF06A5A8CDFC18ULL, 0x58A46B6683E590EEULL, 0x84224ECC08732582ULL, 0x29F71963974B01DBULL, 
            0xA8091EE9736D2B6EULL, 0xF9681BAE3487D58FULL, 0xE2B509B9E1DB0543ULL, 0x2F0E9B552FAA584BULL, 
            0x46294A38D8582505ULL, 0xCC7642435DFCD214ULL, 0xAFD96DED4C5ECC7BULL, 0x652A80977EE0AFC0ULL, 
            0x2A5E870520089D8CULL, 0x08D1E8BB10012CE6ULL, 0x411D86A23D5C928DULL, 0xDC6CDEED51F1CB03ULL, 
            0x71DFC7F550922827ULL, 0x00E9795617A47216ULL, 0x8F09721DBDC71CC0ULL, 0xAB356333627ADED8ULL, 
            0x3E2585E3F9FA1597ULL, 0xFE70AAF14D9BD3AAULL, 0xDAB59C64748BE6B2ULL, 0x373E04B74D3870A5ULL, 
            0x513DA4F370A09B71ULL, 0x1415FAF707CDBF72ULL, 0x1F1F43D9EF6C05A2ULL, 0xBEDAB3205532B1C4ULL, 
            0x5AAC17CBCD334E2BULL, 0xE5ACEDB3178E5413ULL, 0x786EDA5B6321C800ULL, 0x5915799DD698B898ULL
        },
        {
            0xD02692C2744EF1BEULL, 0xDB6DC543A01AD8D7ULL, 0xF9679D93EE0F89ECULL, 0x6B8B3F9E8C62DB19ULL, 
            0xE659428CCABB124EULL, 0xE15731B206D03409ULL, 0x0F0BD8E20E473DD8ULL, 0x440B5B3EBA753ADAULL, 
            0xE5354EAE9EE4F2A8ULL, 0xD7C9A50CFDCEE918ULL, 0x03F0134D1171E0BEULL, 0x63AF64E949693584ULL, 
            0xF58591EDA5BAC38EULL, 0x2C26C067943035DBULL, 0x724097D75EC6D66CULL, 0xDCB491A02E5F11B2ULL, 
            0x963E4CC1C652889EULL, 0xE4574C28F977E486ULL, 0x20492B4DB2FC8504ULL, 0xCB1F5CCCEDF8B341ULL, 
            0xECFF6765A4FFB0CEULL, 0x7A9F9F911A41CE34ULL, 0x891783D03F60E70AULL, 0x42F88B2BA0AE90A0ULL, 
            0x8A6550AECFF250D6ULL, 0xABDC45FCBFC17217ULL, 0x4AD1DD98964FDD82ULL, 0xFC8BB2A0B1044EE5ULL, 
            0xDCDB971A737212D2ULL, 0x4591ECC34FCCB408ULL, 0xEAE8B437FF0535F0ULL, 0xFC74EFE793E6CDC1ULL
        },
        {
            0x3BAB8494BB370E3BULL, 0x2BE7DA288EE9FFD9ULL, 0xF5D4FA1EB746B888ULL, 0xF64529BF93FA7E85ULL, 
            0xF52FFC940462E15FULL, 0x7BF3E1F038292309ULL, 0x3C085174A49BF127ULL, 0xE20DFA33C4177B0FULL, 
            0xF5C98D7B9BC98DDCULL, 0xEAF3EA009E8238A0ULL, 0x229C2EF8B9DF64AEULL, 0x7EED6FF8029E9AD6ULL, 
            0xF1FCBC0E109BFF26ULL, 0x269A2A545C251662ULL, 0xC32CDE858AF37B77ULL, 0xB7AB0F57F7121744ULL, 
            0xF67CAAD3AABD8C46ULL, 0x2B9A16CF2C564DFCULL, 0x463B6E7D34AD0B06ULL, 0xD65610FA503CA396ULL, 
            0x6BF3F7A46DE28F04ULL, 0x2D36E5776AFDEB17ULL, 0x29A661C7075AA015ULL, 0x43779F6E63910ABDULL, 
            0xE6E96AC1B1B895EBULL, 0xB880838DD8D7CD37ULL, 0x6DA1F26546F8243CULL, 0x642AE2DEE6E8DA21ULL, 
            0x0C21B6B5CC148D1AULL, 0x7C487B75DF72389FULL, 0x3FEE12AD3443A67FULL, 0xDCA41EA1498D3975ULL
        },
        {
            0x4ADC6840F5AFE50BULL, 0x9D5C4C77C7EB9DFAULL, 0xF89CE6250FD7C18FULL, 0x38653FACD3EC25D5ULL, 
            0x0743A19937197A28ULL, 0xA60517FA36ACAA6BULL, 0xB8DB8442F03DFB06ULL, 0x8D57E72438BDF6F5ULL, 
            0x235D10273B0E5EEBULL, 0x2F47C6DC3AAFFAAEULL, 0x309838A36BDB8D4FULL, 0xD1BDD4C89C7345A7ULL, 
            0xF587A2129D1412CAULL, 0xD858938853CCCABDULL, 0x19BEF10CA0565BA4ULL, 0xD32EE0BDE39D5304ULL, 
            0x98E8D36629AF3A5FULL, 0x7109A2297EB88A4FULL, 0x9EEF08C9E63BAEE9ULL, 0x00D16AECE4C413EEULL, 
            0xDDABD996AC7DA55AULL, 0x98B6E9C20CDE235CULL, 0x433D2AFD7A0307F5ULL, 0x0382DF4E8FA6105DULL, 
            0x2D418B4DB9529677ULL, 0x894B20D173C7002BULL, 0xC88DADE3B457F176ULL, 0x1185C55D5F550EFDULL, 
            0x219809E0EF52506EULL, 0x0CEFEE14DDA8C1FBULL, 0x368015E04613F2E1ULL, 0xE455158B1BA6649FULL
        },
        {
            0x5581B60B3873DDF7ULL, 0xA522E65B5234333EULL, 0xE70A843AB8BC0EE4ULL, 0x449A6FC032574AA5ULL, 
            0x195299327B31D112ULL, 0x928330439F62D19AULL, 0x80C13CFC7A9361E7ULL, 0x556AC4693F8EC500ULL, 
            0x33C1F007BA718A35ULL, 0x9781B9D5FEFF68F7ULL, 0x3E7BFCB4558F9A4CULL, 0x9087438E38C413A7ULL, 
            0x0C300B5CB1AD9D96ULL, 0xBFB9C637850BC209ULL, 0x42E2DC88A026640AULL, 0x3FD1FB1B3F44721CULL, 
            0xFD80F4D32779F9C6ULL, 0xFB07463D5BE5D74AULL, 0xF3162D40B1BBF21BULL, 0x312E2107D7A2718EULL, 
            0xDD65D3A1DCDC0D7DULL, 0x06D378BE29006EC4ULL, 0x8373051E819C5024ULL, 0x07FD557D9E654849ULL, 
            0x797EBE1C2D6C8D5BULL, 0x9A54E1B9856F482DULL, 0x58AA75AC4380E903ULL, 0x765B245B35D992A8ULL, 
            0x55B3C175324F773BULL, 0xC2398E83A6EDAE86ULL, 0x0C2C451C4C8A712AULL, 0xA052E37400A7EE26ULL
        }
    },
    {
        {
            0xB94E4C163E1FA89BULL, 0x2E5645511575FE0EULL, 0xD43E3329CBF25613ULL, 0xFF9FBAA7857EB74EULL, 
            0x296DF2FFFCBF68BAULL, 0xEC97E85FEEBCC189ULL, 0xDB38D77A921785B4ULL, 0x00C1DE752E94473EULL, 
            0x18FB990C1E400644ULL, 0xE621B235170C176EULL, 0xA69C71BF6C7DBBDFULL, 0xB15A7AF82BA5BD5DULL, 
            0x67338E1A7EF850B2ULL, 0x58F034666111867DULL, 0x8D10755C58E2F260ULL, 0x0C5772FF52DD00DFULL, 
            0x814B4F559F39F8F2ULL, 0x464F01FB0D9539ECULL, 0x5FB93AD81B770D10ULL, 0xFEFBAF6C2AC125F4ULL, 
            0xD00C05571DD6C20BULL, 0xDA2DE19160E52CD8ULL, 0x2EC09858AC2F0435ULL, 0x3EDD2CC5FC0F3653ULL, 
            0x006D8CA0143D809CULL, 0x9796C3E0C4D8F57DULL, 0xB26C93094ED9FC1CULL, 0xA0CA1D7719A25A34ULL, 
            0xFD66DAFD33DB0723ULL, 0x3E66AE00E631378FULL, 0x390F962BAA8EAD9FULL, 0x116712CDCAC9660BULL
        },
        {
            0xBCD548B0A5EF4722ULL, 0xED895BEB9200D51BULL, 0xB6C5CC26B75C93F3ULL, 0x80B45B0D042E475DULL, 
            0x89A38AFE3250D773ULL, 0xE13DABDA2AD3FC23ULL, 0x7C0F4A1DB77BE24AULL, 0x6892570A8B085B55ULL, 
            0xF88A93F520C94CE6ULL, 0x7B7369934AD31F48ULL, 0x959AB06C68BD60E8ULL, 0x9E5F873183697AE5ULL, 
            0xB6D267AC3E642E0DULL, 0x2385613D67F4A651ULL, 0xD8A682CAAB1BA10CULL, 0xA2FF62CA2ECCBB2FULL, 
            0x51268B3A1E418495ULL, 0xF332E335FD540217ULL, 0x46DB00C6678B082BULL, 0x576AE675B9CC9B81ULL, 
            0x790213BAEED33F73ULL, 0x87B4CC60F0DE9E20ULL, 0xF3202CF345637BD6ULL, 0x16B273BBD7C1DC35ULL, 
            0x0D55C36FC57F0AE2ULL, 0x762A5C880CB42193ULL, 0x116ED88BB05BF3A7ULL, 0x2A3C04B906562BD4ULL, 
            0xFA670356A3CA3141ULL, 0x0C3AEE5496F8CD91ULL, 0xF19A5A3AE2AC5CC4ULL, 0x6854FD7A4BC4BDEAULL
        },
        {
            0xBA2DFE52BB8060B1ULL, 0xF798E8BD42113FDEULL, 0x1825236F2CFF5650ULL, 0x10BF2135128EE8F9ULL, 
            0xC7175956A3A98A16ULL, 0x9B079DEF650C5752ULL, 0xFC717F6B059C9C7CULL, 0xCC3ED9B9EB4EF13BULL, 
            0xE4AB2ED6406E4237ULL, 0xB0A7A03C2D854E23ULL, 0x82CA9964470AE5CEULL, 0x535FA54EA37840FDULL, 
            0xE16EF6C1CBB882A8ULL, 0xF7372F88E009EDCAULL, 0x3B3F920FE1554BB7ULL, 0x7A0215163230A19FULL, 
            0xB0FC69D03E747696ULL, 0xA9CBCF471907E5B3ULL, 0x2977ED0F9CD52AF3ULL, 0xD5BA4AA54CB05309ULL, 
            0x7E7CFC0CE996EEEDULL, 0x506D146CC56304C8ULL, 0x4BF1D34FF446B698ULL, 0x36ED3F08F388D405ULL, 
            0x15ABD9EE4D00D7A9ULL, 0xD36F9B4DB7F4264AULL, 0xA241DAF101052439ULL, 0xA63157032E7A1D5BULL, 
            0xAF60156DFFF2C02BULL, 0x45C451DF4E857A9EULL, 0x28DFFF9346C616BFULL, 0xBD8B8AE3A2D63A11ULL
        },
        {
            0xCE90E73E5398F0BDULL, 0xDB07B6C46401636AULL, 0x161EF116A9AA0112ULL, 0x5B3AA1F19302A85CULL, 
            0xF70609605FDB2C68ULL, 0xEF5FB18555E042C0ULL, 0x90A120BA0FF12199ULL, 0x8E6207A36F2A0DE0ULL, 
            0xE9F828AA84C02D24ULL, 0xC7B03F20B4F27874ULL, 0xC2AB3B6126C529CAULL, 0xFDEEBB77CA572712ULL, 
            0x220874D5038A56F3ULL, 0x2A999D17D5C8CC27ULL, 0xBF50D1421ADE3103ULL, 0xDAD87B7DAC4DD915ULL, 
            0x4B9E036F7E961C8BULL, 0xE30FC1CCD6B12C3CULL, 0xC4FE04A66756384BULL, 0x07A84F534308B3C2ULL, 
            0x07980DBD26596F04ULL, 0xB4CF86FF027467E8ULL, 0xFA72F972E5BD36F1ULL, 0xC9E08CF34A900CA1ULL, 
            0xFB5EF34CF6E6E1E2ULL, 0x0753FE713E6FEC4BULL, 0x710B74A12CC3D356ULL, 0xDE0C7511BF7F6D03ULL, 
            0xD25373A864959592ULL, 0xAFE4721AC6DAB04BULL, 0x6C92833C77801853ULL, 0x81A4ACF25E99CF30ULL
        },
        {
            0x8D061C16F765CB5DULL, 0xEDB70A17F8B0316AULL, 0xF4C745015A937D54ULL, 0x903F90A2B2056F22ULL, 
            0x5CC2997F4683CA49ULL, 0x1355C9F443B335B4ULL, 0xD0FB1AB39766D01EULL, 0xAEE42F696AEB5B8BULL, 
            0xDA3636B252C51B95ULL, 0x197A8FD6C82B27C3ULL, 0x70E9EBE7E4B9E6F7ULL, 0xD8B3CEE5898A5A0EULL, 
            0xD960BE20C94CC4A4ULL, 0xD216065B0EE2C71FULL, 0x07077946BEFEF326ULL, 0x7C4D9F6DC28A440BULL, 
            0x622EC83CD04276BBULL, 0xFA45DBD7E62268F3ULL, 0x7832D5F577C37E26ULL, 0x9B8617D707DBAC98ULL, 
            0xA2C9ABBCCED16B9FULL, 0x40865F3FB3BE6A86ULL, 0x1965345D31107019ULL, 0x417F370C3BA5279DULL, 
            0x12A47F1CC02090D6ULL, 0x7B07FE6E8CC68FB3ULL, 0x6D816C4536EFA193ULL, 0x1E5C914B7C1687A8ULL, 
            0x78F28D3500EF0351ULL, 0xDFDC8E23326C8669ULL, 0x552CA963F8A4418FULL, 0x5A412BF2E042DAA4ULL
        },
        {
            0x16C675903F944611ULL, 0x6EB6634F62520569ULL, 0x9691E5DA6A2282F8ULL, 0x9C611491FA763A7DULL, 
            0x96ED0008291A4729ULL, 0x2CA30D37A083AE74ULL, 0xC8AA1E0A05E9C9C3ULL, 0x0AA6D625CCD1AB40ULL, 
            0x39F0B21EF5B889A6ULL, 0x6920951030955540ULL, 0xE46AF9D150A56264ULL, 0x88508509B7F4207AULL, 
            0xCF73D8A181DBC6FFULL, 0xEB451C6536731E5AULL, 0x5BE158FA48AC4B78ULL, 0x2E64374D57C37470ULL, 
            0x812DE479B3B7A136ULL, 0xDFBE8176AD7E61A5ULL, 0x0A48BC0E89C2785DULL, 0xC1AF28152F2C7546ULL, 
            0x1D2FEBDE8352B67AULL, 0x0BE2CD4D1D611724ULL, 0xF77878244CCC4C8CULL, 0xD9BFE98AEDC4678AULL, 
            0x98FEF30B0CE242B4ULL, 0x3BF56D76C53B6A49ULL, 0x6EEA789928E8A890ULL, 0x424547947F52D74FULL, 
            0x53DDB4E4EC5E386AULL, 0x58D817AA207A86BAULL, 0x577F0E6F6EDAE1EAULL, 0xDAE6290DE4D442FAULL
        }
    },
    {
        {
            0xBB42E0C906C2843DULL, 0xC703C1CB5F266C8EULL, 0x6DB2368A8A6B4AF6ULL, 0x22DD738110EF20FBULL, 
            0x9508A8AB65028B3CULL, 0x8B8931ACC4F0372EULL, 0x15AC5D53351723C1ULL, 0xD4FFC93D0044C823ULL, 
            0x3010AAE3D74CAA0AULL, 0x726836D646B0A477ULL, 0xB4E275EB64090259ULL, 0x6BF6707858192FCEULL, 
            0xD85C3C623DFC42F5ULL, 0xA9D608CA10675973ULL, 0x9BC98C3B1E953720ULL, 0xADA94995F1F9D70DULL, 
            0x552980B128E9F347ULL, 0x9B1499FBC1B3017FULL, 0xDBC7A46024330BDBULL, 0x0EBBEDD87131FB69ULL, 
            0x9C73BCFAADD18611ULL, 0xF205231919995859ULL, 0xC634186CA3F99E37ULL, 0x92510E1A1D83BC2FULL, 
            0x2D500C5D47344B33ULL, 0x939299158B9A0A60ULL, 0x880719D3C106C4DBULL, 0x22D92A6521CC06FFULL, 
            0xD64E3DEBD2CF7E34ULL, 0xAA35A8A7FBB0EC17ULL, 0x7B2E8C47CFF93019ULL, 0xE6983FDF6D23985FULL
        },
        {
            0x9389A56E2AB47C20ULL, 0x70AFA1D927354D9EULL, 0xE8950FAE17BDF13DULL, 0x8AD975DCD57688F2ULL, 
            0x68DDFC9A5B695963ULL, 0x3E3BF73D4B51AB70ULL, 0x7AE2E787EE889E1FULL, 0x4B2A826446406ABFULL, 
            0x1ED08A724E54ED17ULL, 0x94A719296C51F8CCULL, 0x1B00E001CFC8BCF0ULL, 0x55FEBE5DBF2D5B22ULL, 
            0x0D0DE63A8CE1E537ULL, 0x008AE2A1E3C2D360ULL, 0xA1D812CA55A8AD04ULL, 0x14B741E4D9EBE36FULL, 
            0xC3B3B87C5E974DE5ULL, 0xC1A83FA74C077A9DULL, 0x406A0F9D7BD2A437ULL, 0x39A8A08D4D8E8BBAULL, 
            0xDB17955205644D0FULL, 0x3427570A50CE2B0DULL, 0xD3F72E57650197A4ULL, 0x8278AE74F9AE6C8FULL, 
            0x9F153BCD453FA301ULL, 0xE86631C1C55ED8BEULL, 0x9551F572974C1B5FULL, 0x2FE8D0638730E957ULL, 
            0x1D53A87BC025B5A2ULL, 0x4BFEF50C147186D5ULL, 0xF893423BAEE6B3C5ULL, 0x07EFF821354E8F19ULL
        },
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
            0x5590ACB1116A5464ULL, 0xAFF272A26793800EULL, 0x960CD4CE8E9F96E3ULL, 0xE629B6B1F0B9D7D7ULL, 
            0xBC87431A01F0AEA3ULL, 0xA0DCD7A7E8AFFA44ULL, 0x4C38437FA5C34384ULL, 0x3A21DBC66783906AULL, 
            0x93C28A28528D999EULL, 0x2E1F36C47A7079FDULL, 0xEC0CB393F2DB8790ULL, 0x8E922180DCC9D436ULL, 
            0x8C1268E7FC017431ULL, 0x73F62A5B9AFAE922ULL, 0xA02B2CF3ABC2BE74ULL, 0xE5C4FE19C0586DEEULL, 
            0xBBD089130B9A9C02ULL, 0x0FD7E266ACA1D38BULL, 0x8702D9E22C3870D3ULL, 0xC967277F61EFE9C8ULL, 
            0x6F265737EB80B59EULL, 0x9B96AD8944A061E4ULL, 0x368401F149BE721DULL, 0x7E537AE6E1C8E06BULL, 
            0x9696FE84C02A0BB6ULL, 0x17B0B7B7E3BE5A8CULL, 0xFF1919D38B87F1F8ULL, 0xD1645D7706C94DDEULL, 
            0x38861EAC4CEBD4EBULL, 0x2FF257DAF988B818ULL, 0x3BEBDF22D9FCAF44ULL, 0x99E59421EC80D6E7ULL
        },
        {
            0x4EBA58EA3C4DBDDAULL, 0x64C9C660DD7470A5ULL, 0xEBCC0A404E610F61ULL, 0xD3066E7947D8F032ULL, 
            0xEDA9B079CBCB819FULL, 0x32EED9017E5DAD8FULL, 0x05D09B45370CAD9EULL, 0x8A23F2C1629EA9DAULL, 
            0x1E95CEBE47769009ULL, 0x25B08F4B0C3779EDULL, 0x8D25D396264052B3ULL, 0x3BCD2D95B294CFA7ULL, 
            0xFF611CC976A84151ULL, 0xC1D293767EDE659BULL, 0xFB001819EB0B7713ULL, 0xD0E5B70EC90FA4D9ULL, 
            0x4DD0F61AF5E3BB14ULL, 0x46AA0ED6EDDA5BBBULL, 0xC5F17F9ADDCDA5D0ULL, 0x89A0FB1083EF3316ULL, 
            0xE5985580F7CD1863ULL, 0x73A7FD26254AEF27ULL, 0xD2BC0FB05105E36FULL, 0xF3BBACAE7831C1A0ULL, 
            0x17092C7E7A4915E8ULL, 0xC92D3D25AF0EC082ULL, 0x17874ACFDFCC418CULL, 0x3432FB12361E0E0AULL, 
            0x7B7AA0873F2EF4C1ULL, 0xA25F41D65FF179DFULL, 0x43F27D38BFAAC757ULL, 0x0145FECB268C2D0EULL
        },
        {
            0x48C9241F697A94A2ULL, 0xC4D390894F752D97ULL, 0x6E2CA8EC2E6FEF84ULL, 0x360C62374A9D1A75ULL, 
            0xD1E6CBD0A454D6A5ULL, 0x40B8101D1FD7E3F9ULL, 0xF116D633C7257AC5ULL, 0x42C3CEC8BDC2B3B0ULL, 
            0xB3BF3539757E1BBBULL, 0x36DE8EEE0C47CB0FULL, 0x33F8246072D29132ULL, 0xA35A7DA4174F8985ULL, 
            0x2C6D443E009E1F2FULL, 0x4FA67811932FB6E6ULL, 0x348C1B96B9771303ULL, 0xD3EA8F5207C660F1ULL, 
            0x8298D55E97C6D1DFULL, 0xBE8F57EFBE3BD735ULL, 0x9C931A541A828BDFULL, 0xF990EFB7CC051DDCULL, 
            0x5BB5B935C004473DULL, 0xA8A1598880622FF3ULL, 0x3FF8311CAF52A2A2ULL, 0xF7A1E2131E9C4BD6ULL, 
            0x0D2AF5A129A90A15ULL, 0xF5EE230B43588113ULL, 0x714C8C4722AB263DULL, 0xDE8201BCD68A0915ULL, 
            0x46E4C7952BB0E139ULL, 0x76DB85E8D438F9B9ULL, 0x92BD9CBBA0538AE1ULL, 0xD051768451885763ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseDConstants = {
    0xBD57A19FFCF27F1AULL,
    0x319AA466B32C2EC5ULL,
    0x36218B87C40BF1E4ULL,
    0xBD57A19FFCF27F1AULL,
    0x319AA466B32C2EC5ULL,
    0x36218B87C40BF1E4ULL,
    0xE5AC4AC349961BADULL,
    0xBBC1A25DC17EB924ULL,
    0x6E,
    0xD3,
    0x7D,
    0x14,
    0x51,
    0x2C,
    0xD6,
    0xD6
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseESalts = {
    {
        {
            0x6984B0957FD74613ULL, 0x8A3D9567B0867CCFULL, 0x09FDAA8D952606C6ULL, 0xBE6F34982B8F7BA7ULL, 
            0xF2BACE7B71A7F58BULL, 0x6528F45643C38158ULL, 0x1C5ACBC88EAD3B2CULL, 0x5FE7EEAE3BAA3B09ULL, 
            0x80B4E02420C3DF62ULL, 0x5307BB6B4DC24C40ULL, 0x10D122D2DFAF6DB0ULL, 0x3345DD8D3A8CD2EEULL, 
            0x96144DA952C5B300ULL, 0xD7CC2E9D5A588360ULL, 0x448A2E01C692C02CULL, 0x3C25EFC7FD3181E7ULL, 
            0x6402300AE0E83585ULL, 0x7EDFA19612D02B54ULL, 0x84956E118D820661ULL, 0x00957E6706A7608CULL, 
            0xED1F0D3F8D7A44A9ULL, 0xFD707751EDC1DFB6ULL, 0x996540E853D6295AULL, 0x145D120A8AFAE9A1ULL, 
            0xD71AC0D5793FB8C2ULL, 0x28B56C5049D1A017ULL, 0x0878AD46A7775CB1ULL, 0xE7DF70973DAB356FULL, 
            0x23F6086C48BECA67ULL, 0xF6F0440CE64C6CD6ULL, 0xACC176CFC96244C4ULL, 0x3B9C89C931309C65ULL
        },
        {
            0x31A88804408A4C0BULL, 0x262D84BD317F3A4CULL, 0x33A761B890D32CCEULL, 0x8A6A35E508F24F69ULL, 
            0x4DE1A12B189040CEULL, 0xB77D3333A52AC3CBULL, 0x116690ACEBB07E47ULL, 0xF8A420BEBCF0DF9BULL, 
            0x898124A1302BEF3DULL, 0x943ED553E27A0DC9ULL, 0x73A629A4397CD874ULL, 0x6B44FAD90651508CULL, 
            0x5D938E2F0A2508A2ULL, 0x70F14C94000DE1B0ULL, 0xF50EDB6571911853ULL, 0xC5ACF7B2FF39D7AFULL, 
            0xCDB2746DB855E244ULL, 0x61995541E2D8AB24ULL, 0xCD2E7D75B641ACA1ULL, 0x0B4B04D43A26C8E6ULL, 
            0x9B31E320D0A255A1ULL, 0x00D553DC99EF8ADFULL, 0x6E0D5B34FBCFE224ULL, 0xFC3EA4D49021D04DULL, 
            0xD82BF7F26B03B00DULL, 0x4E3DBC3EF7C349AEULL, 0x127590771CD44C77ULL, 0xD8CEA2D0B29D68CDULL, 
            0x1835361E1286386CULL, 0xB2CBDA72FA0ED749ULL, 0x0640E9A6BBDD71AAULL, 0x8E7F4D70EC82FE89ULL
        },
        {
            0xCD3DBAA437078113ULL, 0xBA29B7F3109A15C4ULL, 0xC4E249CD2D4FAA40ULL, 0xA55F304505470580ULL, 
            0xE2190DDE54BC6F67ULL, 0xBD5D07A90017995EULL, 0x86DD7B0EA8D33F31ULL, 0x80B156A5DFF341AFULL, 
            0x256D1489D6D15901ULL, 0x54C251F5D4A7824FULL, 0x5F5712DB1F001CA8ULL, 0x5FD6C43012CB0E87ULL, 
            0xC629001ECE47B810ULL, 0xC7587AF10C32C0EDULL, 0x89C21F66743E2E3BULL, 0xAE4F1B7843B18B6FULL, 
            0x86D05F23EBAFB8EEULL, 0xB73533CAFD43E25BULL, 0x8F2CB17A53335CD1ULL, 0xAC7BE0D0759A208AULL, 
            0x250239E951990EB4ULL, 0x628DFB6126505EACULL, 0xD2580CC626DF70B2ULL, 0xDE1BD493E2CECD8CULL, 
            0x027A75426A4197E4ULL, 0xA9C842FF2D31E9CDULL, 0xFC84EF46C20D62CEULL, 0xB0C00BA684850B07ULL, 
            0x03715140AA8D8F20ULL, 0xD5FAA8C21377414BULL, 0xDCFEB9F95E386405ULL, 0xCD3619EAB20E9923ULL
        },
        {
            0xC11E56E664B8A715ULL, 0x47393AD1E6DBBE64ULL, 0x2751595EFAA72730ULL, 0x65519D45A72F42BBULL, 
            0xD7C4CA4C0DEEF8E1ULL, 0x354C7195F6C7FDC8ULL, 0xABF8888130036BE2ULL, 0xFF135EDD042DFE6FULL, 
            0x1C85A29066F0A0B9ULL, 0x092857CAD32D963BULL, 0xFF47C926FF3E9D1BULL, 0xC1F4E5DDCBF1895AULL, 
            0x33766E82D7C2D28BULL, 0x5F6C8DC13E1F01A8ULL, 0xC37137CAE12779BDULL, 0x32FDAF322505912AULL, 
            0x86E389EA6E61C5F4ULL, 0x6A6175C6DFE30DD7ULL, 0x1A21525FD1C736F6ULL, 0x61062884B8C6081AULL, 
            0x7F5A25355AD73C49ULL, 0x56C47D2DF79D4054ULL, 0x2D77FBD59B0626F8ULL, 0xE2B38076F18E797EULL, 
            0x7C3BF6444CF641D1ULL, 0x11B40E0661FB3613ULL, 0x0A7ED784ADCFE627ULL, 0x9E6FF5DD111C6591ULL, 
            0x63A814FC3DB9ABCDULL, 0xA1B1898CBE972583ULL, 0xF000F8D37BBF8A08ULL, 0x8351149FA90145C1ULL
        },
        {
            0xD95A3A2D00291544ULL, 0xE42D8B06BDA14270ULL, 0xD2AA65472C126FECULL, 0xF70FE3CC563075D4ULL, 
            0x3D2B44B25B061552ULL, 0x36AED5550650CCCDULL, 0xE9CC200E22FAEC93ULL, 0xFF7D8D1614957BCBULL, 
            0x7ACCD1CE79A7973CULL, 0x3E6190BF5D5877EAULL, 0xA89834E690B36356ULL, 0x3AC49AB8224E3643ULL, 
            0xD8C4611B56071162ULL, 0x4D0CBE7CB5CC7DE0ULL, 0x3D5B4EA6FFCDDD56ULL, 0xABA24CEEAA3C8562ULL, 
            0x7133F013B1F6968DULL, 0x00E5C9B42729EC7CULL, 0x45F1473442BFC56CULL, 0x367F8D5ECDEF891EULL, 
            0xCDAEC7A316C11E1CULL, 0xF739DE3E53BE8C7DULL, 0xE45796DB998EEDE6ULL, 0x352DD028743E1485ULL, 
            0xA77B93AE299B14CBULL, 0x21A785DB92E6CCE6ULL, 0x17B658B4748BFDB7ULL, 0x3239B7396764EBDEULL, 
            0xE809B4C54AA49512ULL, 0x1A0C68C0C129F7F3ULL, 0x9BF76C94B053868AULL, 0x391B52DF13694AF8ULL
        },
        {
            0xE5DBFEEE5069A33EULL, 0x4A5A6C61FE68BB2EULL, 0x630A719B00F43EB2ULL, 0xB2BD5E4F0DE87487ULL, 
            0x653873F314CFE715ULL, 0xCF52F512F0E24EDDULL, 0x148198DB9655FE98ULL, 0xA4BCF99369915C6EULL, 
            0xDFF081ACA3D6D46DULL, 0x4AEF24CFCE676FCDULL, 0x0227E4D2A9854AADULL, 0x813F12B0FFD53BC5ULL, 
            0x677745D5500FCA94ULL, 0xDECF78BEBB226BCCULL, 0xCB1B5E35EE2AD1E9ULL, 0xD18AFB35DF9538A9ULL, 
            0xB1D994DEC03B7FD8ULL, 0xACA92FC90186D71BULL, 0x567F550F74BD09F5ULL, 0x94263A2175044F35ULL, 
            0x93595494FC5B517BULL, 0x6FAD1A85F68EDC03ULL, 0xDB838B9956E7BB07ULL, 0xFF70F7105B21982EULL, 
            0x751D4F83257EC912ULL, 0x5CB789BC1C402A03ULL, 0xA61275F9D94B4DD6ULL, 0xEC4F00512702E27CULL, 
            0x5D693D62F7A65E6AULL, 0x8893B7EF082C4954ULL, 0x4A8EF6566C1010F8ULL, 0x67CC2B2C5511BC5EULL
        }
    },
    {
        {
            0x16DD6C54CE5F4A69ULL, 0xA79FAD619EFCE2ECULL, 0xBB564C4027003CE1ULL, 0x2C630847CC93E867ULL, 
            0x6C58C901A2332315ULL, 0x0CCC9EB0BAD34BDFULL, 0x828E385814574917ULL, 0x7964E95FDB5BB8DAULL, 
            0x285F6BC0A95690BBULL, 0x0622FB078B4C68A1ULL, 0x2A240F8D34955E2DULL, 0xA8BB7B5CBC38EEAAULL, 
            0xE0F617DF30ABD74BULL, 0x7D40D5D73ECCF222ULL, 0xD0C2F4AC27188EEAULL, 0xB59F58D21D88F263ULL, 
            0x760FCBDD7CAC3B1EULL, 0xB7A78668E9E4F33FULL, 0x8B37AC3795A7A487ULL, 0x54EFAFC4FC51A38FULL, 
            0x208C52CB717995D6ULL, 0x7F47D4721979513FULL, 0x6BA65FE8EF18DB41ULL, 0xAABA7B700988CBF7ULL, 
            0x4AEBD5F15697E42FULL, 0x9FEC38EBFEBA763CULL, 0x8D0FF8EBFBD60C61ULL, 0x1595068B66150425ULL, 
            0xFABFB687D0EF038CULL, 0x0F75EDC640B6A924ULL, 0x1F74E30AFDF1607EULL, 0x563A5374922A9CC7ULL
        },
        {
            0xC7B1D842C7F3C3A9ULL, 0x09EF34BE32E68CBBULL, 0x33B9AF933AB56C2FULL, 0xF5C06F6E0BDEE08DULL, 
            0x3A3F196AB3EBAE40ULL, 0x9917004D23456075ULL, 0xFEF2E00E50AE1517ULL, 0x58092A7201AC586CULL, 
            0x45A2FF07C8012488ULL, 0x00280DFAD16F620AULL, 0x0B0AEE170B6281F0ULL, 0xDA5E43C13BF6A1E8ULL, 
            0xEB0347603B94CBA3ULL, 0x6DD4D7D1B36E7C4EULL, 0x0073773DC8E64587ULL, 0x00AA6ADAB54A54BBULL, 
            0x775A14F3C8B1AB4BULL, 0x09118FEFAE7F93D5ULL, 0x638272E1710CF454ULL, 0x2CF66F3909D4CE65ULL, 
            0xC3493FECE430D56BULL, 0xED825E217D6E1BB0ULL, 0x71581EEB2F813E6FULL, 0x0ABA5472AC7C6EFDULL, 
            0xD46DF083EDC4B3B0ULL, 0x833204FAAC807F55ULL, 0x8736A853657950C5ULL, 0xCCC01A0E405D453FULL, 
            0x596C98D6A309B9D9ULL, 0x85E8ACC4463937D7ULL, 0xA4D47505F19B5218ULL, 0x7009334FF50AA424ULL
        },
        {
            0xC28CC753533AD3D6ULL, 0x753BCA9BD0584667ULL, 0x5DC1BE1E2A0F612EULL, 0xD2337AC83078A96DULL, 
            0x22355961D61A9A75ULL, 0xDF6B00E73A479406ULL, 0x855FFD81493E477DULL, 0xC7C779922353D14DULL, 
            0xB325EB37A701C4AFULL, 0x837C504F84C149C1ULL, 0x40A882F36B52F602ULL, 0x3F6DDE7F1EB76992ULL, 
            0x1AE06113030ED220ULL, 0x9EF2E0E874957052ULL, 0xCC9D07E2FB0B3D2AULL, 0xC2CBEEC102994BBAULL, 
            0xA841DD0821AF06E5ULL, 0x4AD57E0B4E14CDA3ULL, 0x8653E049523E36B7ULL, 0xDE074E9B47378D82ULL, 
            0x02678990A62E8A52ULL, 0x176A7DDC756686FBULL, 0xBB60EE011C1323D1ULL, 0x2B3E4F1196157802ULL, 
            0x855AA98AC7575B06ULL, 0x0FBCDFA4505AD94CULL, 0x784327C7B3223CD8ULL, 0xD7D45E42C60E9F8EULL, 
            0xF52FC5575A475CA3ULL, 0x9E9F0142E3EAA6A6ULL, 0xC9CE66EE0E290EEAULL, 0x771166BE68FDEC7DULL
        },
        {
            0x3553271848473666ULL, 0xECAAEC0AA396948CULL, 0x9EAD09ED31C490F8ULL, 0xF211259F7468F792ULL, 
            0x0DB84B26232A4BB5ULL, 0x1819AA813A97D501ULL, 0x1C87DC1232B2EAABULL, 0x1519F5DB5215FE78ULL, 
            0x44BC5D313ABC1F05ULL, 0xB5B43B2D3C1C3FD4ULL, 0x502570475C2CB677ULL, 0xE41DFD3CFFBA1A5AULL, 
            0x98A855BAAA635462ULL, 0x763B8F6CBC56B8E7ULL, 0x1EC10947DCD2BC17ULL, 0x3AF1701AEF2A1F89ULL, 
            0x5C8E15E00E0C28CEULL, 0xBEDD2C2C744E06ACULL, 0x7FBAD4FE5D7DF240ULL, 0x8F9B976D34C6CA3AULL, 
            0xBA1AED03135C05B0ULL, 0xC7B29785C6D70AA3ULL, 0x63F89D1E379FB8D7ULL, 0xC2C8438AB0791F99ULL, 
            0x3A42082804FB7864ULL, 0xAAF1629000AB9A27ULL, 0x66D12FBCA65FCF4CULL, 0xD95DE1FE9CD86412ULL, 
            0x49674FECDB872579ULL, 0x35FD9F90D8FEC909ULL, 0x5793BD77757F345DULL, 0x48879FD3F3686EF3ULL
        },
        {
            0x3C5E138C03C98DBCULL, 0xE854A2140C3E2D7EULL, 0x3DBD414245C7A2E6ULL, 0x04E16050224C6068ULL, 
            0x7AB2226A2BCE4C9DULL, 0x39E43FE0B75A1140ULL, 0x57D6EA3212348800ULL, 0x79F2101599D6BDB1ULL, 
            0x2B7E7F8477274F49ULL, 0x2202B53847D168B8ULL, 0xF0BB26BA8606074FULL, 0x6132F91BFB000A8EULL, 
            0x88A34B37EA280A55ULL, 0x53E254B271DCB2E5ULL, 0xFA754EDFEDEB8857ULL, 0x66ECEF1699E467EAULL, 
            0x34499FFAD25C41B9ULL, 0x758074190CDD0928ULL, 0x5C3D65D7A854CA7DULL, 0x8E8D3BF68DAE72BFULL, 
            0x71430D0CC68B5C17ULL, 0x74F719B008B8BA7EULL, 0x161071EDFD22251EULL, 0xADC522D5BE535381ULL, 
            0x6122DA04065295C0ULL, 0xC9ECDCE32F968F5EULL, 0xF73C29848F830688ULL, 0xA9A773460610A20CULL, 
            0x01D8591F65177AEDULL, 0xC13BFADC00E56C2EULL, 0xC4BE6127BF739E1FULL, 0x987360C70AA23579ULL
        },
        {
            0xB99D77A61D6CA135ULL, 0x3876D2B142A0C028ULL, 0x2C932E8BC3588161ULL, 0xA38C07AA770222B8ULL, 
            0xBB37B66C92A2F3B1ULL, 0xA66C6EDA10E9519EULL, 0xBB9CD4964F702132ULL, 0x3127D35305746AD3ULL, 
            0x52FFA557BFC3301EULL, 0x4E4E0CA2F0780BC8ULL, 0x69A6E7CFA4679177ULL, 0x4B7631A43A937629ULL, 
            0x5A6805AC73A6CA01ULL, 0x8C0DDF1A8BC51F64ULL, 0x9F53755708C2A64CULL, 0xEE786F7662325CA9ULL, 
            0x94098079F087EA92ULL, 0x4B7A2E7D76908B0CULL, 0x3B98B423DC17B13EULL, 0xCC8929A9E063A5FDULL, 
            0x034BA04245759B66ULL, 0x786CDA3B7EB1EAFEULL, 0x122C1EC95A086BC1ULL, 0x1F02A6B13DA1E84BULL, 
            0x14E3B3C3A5D656D0ULL, 0x262A7EAB6414EBC9ULL, 0x4375658D94D4E07BULL, 0x79539A1DB2888B6DULL, 
            0x90E38BB5EDAA4FE7ULL, 0xA1DBE4FF6BC2F401ULL, 0x248D11CB8AFB504FULL, 0xFA4B45D09295EAFCULL
        }
    },
    {
        {
            0x7073ABD95F521E16ULL, 0x978005D98F0125ADULL, 0x2CD27792CF966691ULL, 0x6A02EBB822E7507AULL, 
            0xFD2408D70ED59501ULL, 0xA4D8EDF22EBCD0A0ULL, 0x7336DA813619AEA2ULL, 0x4545B35975810B07ULL, 
            0xFD00E510E17668C0ULL, 0x2C8755B716E8EDF1ULL, 0xB210EC5BE6AFF798ULL, 0xB43B7E87A3973779ULL, 
            0xC3784FB3AF398726ULL, 0x2340EA6D2F3E79B4ULL, 0x197BFF92B154CD23ULL, 0xCE010E58FAD141A3ULL, 
            0x62BF121972116027ULL, 0x54CDBD13895F84E1ULL, 0x23B88B26BDDFE218ULL, 0xA8498D2FCF5B5312ULL, 
            0x7D25B294FCA227A3ULL, 0x12B0905C309F5FA8ULL, 0x63639E343AE3F543ULL, 0xA5843963209C5B5DULL, 
            0x5B7A5F2E7AD22385ULL, 0x9A6152487E493571ULL, 0x9AB639D8E00189A2ULL, 0x4E67C4BDC628A6EBULL, 
            0x29425DF6B47203EFULL, 0x22206293F511164FULL, 0x9A13BE37E669CAF4ULL, 0x2D75A6E8C83C4C4FULL
        },
        {
            0x9908AF4824842137ULL, 0x6A660E9B8FBBD59BULL, 0x22F08043EA330571ULL, 0x5B3B33068897D602ULL, 
            0x0E4861848FFB8924ULL, 0xCF12EE0B059A7AE9ULL, 0xFE36B798B145CF93ULL, 0xA582843E5BD9BE9FULL, 
            0xD3139C00C98978DAULL, 0xD3C05A8FDD1F674FULL, 0x41771CB9FEEE1039ULL, 0x1330EB31D2905FD1ULL, 
            0xC94ECF48DB9CD85EULL, 0x175B4BBCAC481852ULL, 0xC1826A762581968DULL, 0x5D6795A8A47E0A44ULL, 
            0x90320DC634007994ULL, 0xEE57EF540E348180ULL, 0x84DB293E6A748AD7ULL, 0x6293791058E3DF6CULL, 
            0x463FE9BB910D8067ULL, 0xAC4D2ECAF92EBB62ULL, 0xD12BC268451815C5ULL, 0x4DD4768F365550C9ULL, 
            0x2FEC296EB7B9E1FEULL, 0x792F863F2EEBA1E5ULL, 0xBAA7B601703D3761ULL, 0xF1649EAAF43B2F0CULL, 
            0x0F72FA6CD0AB851DULL, 0x5A909E71181F6A62ULL, 0x17D9EDFA33183534ULL, 0x6CD426F6D63D1291ULL
        },
        {
            0xC710384E40F631D1ULL, 0x471F2BD33460B608ULL, 0xFA7AA9BADF970622ULL, 0x0A3800DFF23B2A0BULL, 
            0xC95551A8022EF41AULL, 0xB71A93183D469A10ULL, 0x83A8F5EB5B0A558FULL, 0x8C85A48D2937244FULL, 
            0x0249C1CFE4792195ULL, 0x329D1FB3D7FDC997ULL, 0x3649D4D3E0DFE93CULL, 0xF48E69B3D6CAE8ACULL, 
            0x5B4062A663CC522DULL, 0x0FF1AA481AA574E4ULL, 0x7855A0AD575ECEADULL, 0x67982E0C7662603CULL, 
            0x4CA1F01F73667C07ULL, 0xD9089B2D96D5BA2AULL, 0xC000644BA10DC0B8ULL, 0xA33D06B50D6EF89EULL, 
            0x008FC53DA8936BCCULL, 0xDF532F661DE5EF41ULL, 0x7EB535C8AE8D2E29ULL, 0x561AA99F896B3ABFULL, 
            0x68A93C8CC875903CULL, 0x66BC28919B7AC1DCULL, 0x758E47FD4E9302CAULL, 0x0A3340869F58CDE9ULL, 
            0x971A9ECBB9B57F4CULL, 0x645288BE6CF4E6D3ULL, 0x8754A21B8171F0B0ULL, 0xEC0D357A6FEBD022ULL
        },
        {
            0x8604C79FB96A434DULL, 0xD50E9B65F7C1033AULL, 0x2058CA40C9C80FEFULL, 0x1EC4A8F8AEA6D655ULL, 
            0x7F2EFC5C6342EE4FULL, 0x2DEF594ED35370F3ULL, 0x7C74B11F5B31417FULL, 0x23035F02CBF4D232ULL, 
            0x99C3F3B2B60B4F02ULL, 0x1A354DAF3DA663FAULL, 0x8CB8F4D86E89A795ULL, 0x45A81A6816CC60C5ULL, 
            0x716E3C5D3367B2A6ULL, 0x29DA6C5DBA612570ULL, 0x373738844E5C0CD2ULL, 0x3F62D8115EDED555ULL, 
            0x60A4207CDDE280FDULL, 0xBEDC6D2236668DE7ULL, 0x4F63F409267E858DULL, 0x0BE7BFEC3DC748F1ULL, 
            0x53BE45DBFEB2A6B7ULL, 0x20E61EA68BFA413FULL, 0x8ACCF2057C8814B4ULL, 0x85C79A2357ADFC75ULL, 
            0xA7C79EFDB2308C70ULL, 0x852BBFDEF3412C64ULL, 0x5CF831CA86B7E744ULL, 0xEE66E244EAFC570EULL, 
            0x5C3D3A5597CCB158ULL, 0x83D5C0F65928B1C7ULL, 0x6170196D31BBE911ULL, 0xEA7AF64ACCE2747DULL
        },
        {
            0x5E12B4A944DFEED5ULL, 0x2BBD93552AFA0C54ULL, 0x99DA5677A9576B10ULL, 0xF0ADEFAD99F8D6B0ULL, 
            0x149C51BAEF40516CULL, 0xDBD35D3B26D3F338ULL, 0x79E3749E329D76FFULL, 0x79B3C9BDFA90A894ULL, 
            0x79DBF16CB559EFB9ULL, 0xE32A70784F2FC60BULL, 0xDEC0B18C28320D7BULL, 0x1450F73899BEC4FDULL, 
            0x97E142AC506DB72AULL, 0x2C3794C932419558ULL, 0x5B560A9EE36B00A6ULL, 0xCAA804D180239DBBULL, 
            0x52916310D1944A47ULL, 0x1837F9DC45729071ULL, 0x8D554F31C40E6165ULL, 0xB5D34FA1C158A3B7ULL, 
            0xD91F871931B6482BULL, 0x6D83065034991AEDULL, 0x444B44696BD4D47FULL, 0x30B420CC30B943DDULL, 
            0x423F3A7D1F5B038DULL, 0x560C6635223C2D28ULL, 0xDEFB92CE6CAF6862ULL, 0x2B724BE45AE8B152ULL, 
            0x5D3393A653D0ED7BULL, 0x578633E6914D9249ULL, 0x68E944BF95072CCDULL, 0xE0813C82361411CBULL
        },
        {
            0xBEC0B7924A4C313CULL, 0xF047DD10CFE7098AULL, 0x3B130B744DE10F72ULL, 0xA7D88101B6660BA8ULL, 
            0x40EA1393CEEE9C58ULL, 0xA8842AC974BF9448ULL, 0xE8E0E3DAA605DC23ULL, 0xE8B71C34EB44DEFAULL, 
            0x8F55DDC4A307638BULL, 0x333B0820C9AEAA37ULL, 0x14A2CECDAE31F3B1ULL, 0xA1351DD3BCA976ACULL, 
            0xFD656491A15CE511ULL, 0x60FA5576245DCF0FULL, 0xC0AF23C857330BACULL, 0x1063A6F3071331A9ULL, 
            0x0A7ED7D5011BA54AULL, 0xDFA423E2FAB27590ULL, 0x8046DCC7767DB1ADULL, 0x59E0C07E7D921972ULL, 
            0xA7AE7A69AC6120BFULL, 0x8211E3F34149B1D5ULL, 0xD5708CF2111C12E7ULL, 0x4A4F2E7BCFF6B53AULL, 
            0xFCF94BD114D785CDULL, 0x1865B1E35FDA5445ULL, 0x8F029B5969A996C3ULL, 0x4B594C1F987C5A62ULL, 
            0xC8B2853CCA122DBFULL, 0xDD3F0DA2CACA17E7ULL, 0x6CC703025D58FF6EULL, 0x81BC3923169FEC26ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseEConstants = {
    0x763FDBB946058959ULL,
    0x5FB23E25F2E72827ULL,
    0xF12A5315702E8C45ULL,
    0x763FDBB946058959ULL,
    0x5FB23E25F2E72827ULL,
    0xF12A5315702E8C45ULL,
    0x7EB6A857620EF064ULL,
    0x4E92D03694EF284DULL,
    0xA4,
    0xEC,
    0x9E,
    0x35,
    0xB7,
    0x77,
    0x1E,
    0x88
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseFSalts = {
    {
        {
            0x3859BAA86686E867ULL, 0x655C0375ED937FC6ULL, 0x0E62E6D5A4BDA873ULL, 0x80B1E92DE3E85BA8ULL, 
            0xCC03708B47E4A830ULL, 0x221EF98BCD696DDDULL, 0xAA77C23318450DD8ULL, 0x2F7A4F249CEDA419ULL, 
            0xB31E4116FCE436D8ULL, 0xDCFA6947C04BDC30ULL, 0x7D0E5785B8E6B357ULL, 0xC8487A1C6ECD4208ULL, 
            0xE239DD4CF4A06C6DULL, 0x879CEF78554AAE39ULL, 0xEF5903AB9C007E4EULL, 0x440EB3C18C09D216ULL, 
            0xEF1C35C39DBDBD56ULL, 0x3A7B4E5F26946C31ULL, 0x9FD4B168E4ED3158ULL, 0x20AF930E17ABB9BEULL, 
            0xEB7A5E721C7AC218ULL, 0xB7F490973CBFC67EULL, 0x437A1CCA433E4D53ULL, 0xDB576302C9DD3CB5ULL, 
            0xB138F30028ACF850ULL, 0xBCC118F968D75A86ULL, 0x9526A3A442E94640ULL, 0x5CB0F4CC5D0BB3D4ULL, 
            0xB1C3DE916D2421EAULL, 0x3F91099DFBA0B5D5ULL, 0xC1E1C9805FF70F0FULL, 0x331BBFFAF57B7F2AULL
        },
        {
            0x9115CDA53FAEA3ADULL, 0x4D0E49B66A91891EULL, 0xA3A610004077C51CULL, 0x50A2B9FD2A38362AULL, 
            0x42C41ED1759A5863ULL, 0xAB420192220FA6BAULL, 0xEDBAE92C2C5E9114ULL, 0x732E3A9DBBB448CAULL, 
            0x2DB25A2DD4B5784EULL, 0xC580DBB9C9761668ULL, 0x3C08245149FFD1C2ULL, 0xCF3522BBE4CF1AEAULL, 
            0xFC78C71861711ED6ULL, 0xF91AC73111772B29ULL, 0x078CBA971FBB74DFULL, 0x6EADD969AF7260A9ULL, 
            0x20236B28BEF9B182ULL, 0x19FA4E2666AFDF14ULL, 0x1E8240E276102E6EULL, 0x02479AB7C2289400ULL, 
            0xE3F27914E7AD2B74ULL, 0x783BFFB5400C1904ULL, 0xAB75CD5A1AE51FA6ULL, 0x2BFE63AB7B98C625ULL, 
            0x1589C1CC4FE46A17ULL, 0xA78D9082C965744BULL, 0xD59732A602B358BEULL, 0x0EF96B77FB4B6D67ULL, 
            0xB1427679A8FD9225ULL, 0x115A46AB4F485440ULL, 0x867BA693D249A84CULL, 0xCDA6252681CCCA90ULL
        },
        {
            0x4B1A4303649592A3ULL, 0xCF42B7347488E9F9ULL, 0xB0ED36A9DAD3849DULL, 0x900BB967F0F842D1ULL, 
            0x0D3A1F5C093036D4ULL, 0xA621E7116F4E6D6DULL, 0x9F0AD3AB2E8E4768ULL, 0x17E15E9F130E885DULL, 
            0x732ECC3FD53D06E5ULL, 0xE1256F7BC2E2C46AULL, 0x9FBAA56824B7A0BAULL, 0xD9D4138594F426CAULL, 
            0xE911D1102F477D19ULL, 0x632259B16CC18B03ULL, 0x904EFDEB571C14CFULL, 0xB41BB4E91F6AEEC0ULL, 
            0xD030E1A2D32FC0EBULL, 0x3870865A5A1857D7ULL, 0x8CA1619F8D36F2E7ULL, 0x415E21185832E4F4ULL, 
            0x0F57FA513FE5B4A6ULL, 0x8A4AE52FDEA95C76ULL, 0xBA51DAEE5799859CULL, 0x85F324F384036BF0ULL, 
            0xEF8240B2F92A6CBBULL, 0x220B1BAEAFE03624ULL, 0x02951F4068B60DD8ULL, 0x85952B4BEB686CF1ULL, 
            0x0D918AF78491117DULL, 0x042BA1E18BFF91E0ULL, 0x0575A7C48A31588AULL, 0xA65E52845E5A4C05ULL
        },
        {
            0x9981EDDCAC8D38E9ULL, 0xFF3B6B3DB7855C5BULL, 0xF46F3DC9319E9A4DULL, 0xDBA698A150B17563ULL, 
            0x8F9F7CA2B549D776ULL, 0x47F3B8DD9789D6DAULL, 0xB11A72DD9F7A866EULL, 0x4BCECC705A415B8DULL, 
            0x79C3BC5589ACAC0DULL, 0x9BD191A072C83F4FULL, 0x16D5446D5BAC3556ULL, 0x1075D20159143CC5ULL, 
            0x81E1A6D835E911CFULL, 0x999247D078880923ULL, 0x2EF36ECFB11F694BULL, 0xFE93798FDA94A790ULL, 
            0x836CAE01EAFE9B67ULL, 0x026973F9792F7C31ULL, 0xCE9208CD0DD9A395ULL, 0x91FBA7E63408F63DULL, 
            0xFA540075ADFC1AE7ULL, 0x3B6CCBF7F02931AAULL, 0x3E87D41977ED3844ULL, 0xC7478296FE9564DDULL, 
            0x1C80BB5108EA07C8ULL, 0x2C550CD66B8758C9ULL, 0x70A42C8027CD46ACULL, 0x704D3430D54EF540ULL, 
            0x098469F06989E430ULL, 0x6346637D11612DE4ULL, 0x6E6F1B9C3397FC99ULL, 0xCFC48572A81B365EULL
        },
        {
            0x0F74C40DC3087C95ULL, 0xC470566730AF36B3ULL, 0x07F56D43E3C4FC4BULL, 0x805E24C719AB0D6BULL, 
            0x19E0817829614DC9ULL, 0xFBA7509A399327DDULL, 0xA13E8CF44A2B78D3ULL, 0x85FCED039D537C24ULL, 
            0xB1A51A5CDCBCB99EULL, 0x58F0EE8BC21911C1ULL, 0x00D6EDBEC9E728BDULL, 0xC3BFACAA4B200363ULL, 
            0x5EF55DBE2E51976AULL, 0x4B0298F7AFF14373ULL, 0x0D429E8AD12418F8ULL, 0x410D05AF5DE0F29DULL, 
            0x39347B62BDE6CEC1ULL, 0x34076517ED44D9B9ULL, 0x0E59C74FC0A8C75FULL, 0x3E243A298A2DADE4ULL, 
            0x94455FF7B79F98BBULL, 0x183D934DD06E269CULL, 0x7623C7D767B725A7ULL, 0x95A96A504BE898D8ULL, 
            0xA53AA15BD0821184ULL, 0xD4F49D426649C616ULL, 0xD71DE22DEF9D943DULL, 0x8F292D9EF56D6244ULL, 
            0x48EC41EF0A13B892ULL, 0x04B57DEAF72EF635ULL, 0xB801FD23038A5D45ULL, 0x0CACE5FE25FE8F57ULL
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
        }
    },
    {
        {
            0xA94F07CA10D8FF36ULL, 0x466299C97EBBCA52ULL, 0x38B25DE67782908CULL, 0xDFE50FCBB2007F9DULL, 
            0x9EAF4394BB5B1DB5ULL, 0xB096BBF12AA6F408ULL, 0xB9A7CAB3B438F252ULL, 0x1965ECC5587DA6D2ULL, 
            0xF2D8E2C46250F8A0ULL, 0x51CEC78C4C38E17BULL, 0x25063889B96CFCEDULL, 0x74F11AAB23BD6AE3ULL, 
            0xE49667E76023C8D8ULL, 0x639EF49255B8B17FULL, 0xE6B3FBA363BCF884ULL, 0x258E2FD62428A215ULL, 
            0x9AC3C3FBB5261B05ULL, 0x6C724C342990E3E7ULL, 0x50F127A95F6D4BD5ULL, 0x4E43295C8E2B89CBULL, 
            0xD3F4A5B8F3AC3CD9ULL, 0x59D638576ADC4E7FULL, 0xE1C4EC931B6E21CDULL, 0xCD74A5C79ADF51F9ULL, 
            0xD16C1AD13D6A46E6ULL, 0x60200F7127EEFB2CULL, 0x6D2883CDB573AA27ULL, 0xC606815FB29FFC26ULL, 
            0xB75A296B52AFCB40ULL, 0xFEF36AC741CA805DULL, 0x6D3457F388B90153ULL, 0xDE2D3ED26B9CC54FULL
        },
        {
            0x542B5FF6A17D96ACULL, 0xB252A20DE2758CD9ULL, 0xE2C7DBD533D074D9ULL, 0x3276D1AAE4AFEE05ULL, 
            0xF4EB95F70684A9BFULL, 0xDFD680E62F578D3BULL, 0x1CEDE889E305D17BULL, 0xDFDD0B2C052822EAULL, 
            0x74C821C601E465D4ULL, 0x6AEC0E39900B1DF8ULL, 0x39EBD6AC7E2A0D52ULL, 0xA39E7826AA0E6FB5ULL, 
            0x393C944412561F17ULL, 0xF6847CA592987BE8ULL, 0x337CE25DD17347C3ULL, 0x8FC123465EE03CF6ULL, 
            0x825D4DE5A448A4ABULL, 0x2C3FA0648A10A57CULL, 0x83661A86FDE31A2EULL, 0xA7C9FBE23DC96258ULL, 
            0x6897CF742725F92AULL, 0x9E915DC82BC49D5CULL, 0xC06ABFCFA1B10FCCULL, 0xB6F07F3F023694FFULL, 
            0x490E2997907526D3ULL, 0xF3AE91C6E61D553DULL, 0x389528591DD23C23ULL, 0x6B961B77281D1081ULL, 
            0xF1F7DECA6885B34EULL, 0x5854889C4D5C395EULL, 0xABAC1C34C3695BAEULL, 0x44C59BFBD1673B55ULL
        },
        {
            0x1CFFA2F8B80F777EULL, 0x6B30E7E420ACFC21ULL, 0xEB1B30341352A326ULL, 0x7819EDBEA6ADEEB3ULL, 
            0x9E6832EDADE9C5C5ULL, 0x8BA5975759EFDC03ULL, 0x46971412661ED6D9ULL, 0x4D3F35663F3ACD42ULL, 
            0x189B4DD2B5C76748ULL, 0xCD7A08F5456E7243ULL, 0x5B9327CD9A864D63ULL, 0x34990636DAEA68CBULL, 
            0x922CD704AAB0A887ULL, 0x11508A2B7258D9B9ULL, 0xDCB2E50C8474E3B1ULL, 0x4A93BE8FDED73C2DULL, 
            0xC114D0444AE882B1ULL, 0x5E8A7930B3C0FE48ULL, 0xBD33F8BC228D265DULL, 0xD6F284BF72C79FFDULL, 
            0x3943C1C9C8EF6F63ULL, 0xF8472A6F9AEEF05FULL, 0x258200CED6FE6053ULL, 0xEBB1D32974044732ULL, 
            0x513507E54BF08548ULL, 0x36E2DC576D2757F3ULL, 0x6FCE7E1B04B3836AULL, 0xE37C6D49B7A03288ULL, 
            0xECCEC68317C7E958ULL, 0xF4F319137D53AD6CULL, 0x3FD688BB5A65461BULL, 0xDC8799E936B1B5D7ULL
        },
        {
            0x204130E721923625ULL, 0xC5F278307B2EB837ULL, 0xCE001F4912F618E0ULL, 0x09C7AA578A7F4A5AULL, 
            0xB697C5A6F6F4C265ULL, 0x475AE0EC618E53E1ULL, 0x19DA6499F006C094ULL, 0x019BE53EFD8426E6ULL, 
            0x0FB3E909BA2657A5ULL, 0x930573116231FF21ULL, 0xBC91DDE8C2187BEDULL, 0x8BA8AC4F8A2C3984ULL, 
            0x0C4BCF93F09C013FULL, 0x0F58B58147DFB10BULL, 0x3EFD0A37FE365591ULL, 0xCC3E192A1D5FBA25ULL, 
            0xA25172340F5D2363ULL, 0x9A7A99FCB681F4CDULL, 0xD9583F057CC68EEEULL, 0x4E7CEAB80427050FULL, 
            0x3200B4436D232E35ULL, 0x757D7E7C11CB025BULL, 0x741E79DAC46D8FFBULL, 0xC70EE0044B9EABBAULL, 
            0x4885A6F481461E80ULL, 0xADB07E9C407D4654ULL, 0xD5BF3F5B678DA7C3ULL, 0x2B050A5AFA7C2396ULL, 
            0xBE9C40626B4A0BC0ULL, 0x609530EF32487368ULL, 0xE32C86B7CB54E7D8ULL, 0xC4BBAE4BAE3B664CULL
        },
        {
            0x1F9B1F01F7B3CB2FULL, 0x3F865A1780D89C6DULL, 0x682893DA245D6A32ULL, 0xB92F3ECA2C8A3134ULL, 
            0x7690B82B9A1E82ACULL, 0x6126062625641284ULL, 0x35B5115CFE8F2156ULL, 0x9214F8B3A0157F42ULL, 
            0x97319D42CD7A500AULL, 0xBAAF04CC43DDBDF7ULL, 0xC19D2E8E18DE8895ULL, 0x187B529B0C9C23B8ULL, 
            0x54A053DDE032A003ULL, 0x89740DF8B6C9B5E2ULL, 0x54E2611E87785C28ULL, 0xAB6D9A928A41D5ECULL, 
            0x1D8FF9BC1093DCCBULL, 0x801A5DCB476B12A6ULL, 0x23985B8D29B2B974ULL, 0x3F54CEB6DC223C1DULL, 
            0x1EBCCFB1F689F7D7ULL, 0x58D214B8B4D5C9F7ULL, 0x096D35123D373EA9ULL, 0xB2A31A1710FDBB07ULL, 
            0x2AA185F33027B918ULL, 0x2F98FE52F76DB671ULL, 0x7B17754747D9C550ULL, 0x5D64A3F64C797485ULL, 
            0x32FD5913C49A95E2ULL, 0x2F0C77948DE3474EULL, 0x83E358673837BFD4ULL, 0xCA2C414DBF84ED44ULL
        },
        {
            0x8245529434BF9016ULL, 0x2FCB90E31AD409A1ULL, 0xEC23B39A1A32F0F8ULL, 0xA5077098DC1C099EULL, 
            0x8EF917557B75C290ULL, 0x9342FF7E4D38C14DULL, 0xD9EB5C481A28E263ULL, 0x6BB6B98731608D34ULL, 
            0x02CF30ED1BA38F20ULL, 0xFD92F158B3B1B63AULL, 0xDC17794295CDFE1BULL, 0xB9E7A9357B6BEA70ULL, 
            0x8307696A661E49EBULL, 0x09133C136A3C960CULL, 0x6A6DDCB3CE652A1FULL, 0xC75CF25BF607BA9DULL, 
            0x4075AE46F0901E49ULL, 0x83ED1924F36CB1DEULL, 0xAD9156201A6CCF58ULL, 0x3CB1C6BCA09AB52EULL, 
            0xF39C8F0FE2803B3DULL, 0x1F427BF512522A35ULL, 0xADB20A428687A1C0ULL, 0xA6A2697BB97E345BULL, 
            0x829536BCA5C3D205ULL, 0x9F6FFD52D9CF2295ULL, 0x0359B19CAF747CDCULL, 0x36F9165F379A9972ULL, 
            0x5296AC61C3932F30ULL, 0x1F7C763553BCD02CULL, 0xB8BDF58D51E0C1C4ULL, 0xB21830D5F5B641A3ULL
        }
    },
    {
        {
            0xF92C54B26B49194EULL, 0xBA12ADEF871501A8ULL, 0xF46529EA3DDB09FEULL, 0x6E41106AAEB0CA77ULL, 
            0xD2C598DBCAE6840FULL, 0x1482D59CE4440C93ULL, 0x501264EFE0353704ULL, 0xFDC3464307CBA786ULL, 
            0xF3EE7DDB6FF3386DULL, 0xD806D23ACBBD650BULL, 0xE03967105108EF11ULL, 0x0A82CCABBB6D2C30ULL, 
            0x0DAD6F2CC4AFBD90ULL, 0x022F350D2F08A7A9ULL, 0xD768298C392E2BDFULL, 0x4641EB43428020F8ULL, 
            0x7530E0B1CA326A7DULL, 0x1648FEB50BAC8FD8ULL, 0xAC4835D9F7DA333AULL, 0xBD0413E7C93F1F49ULL, 
            0x2FB929A54E18860EULL, 0x78F37B720D6759D0ULL, 0xCC164FDD03326010ULL, 0xBA5567CBC70C2E37ULL, 
            0x31DAB675B00EDD42ULL, 0x5F45FAD1BA792314ULL, 0x667A97ACCAD2D287ULL, 0x8A7A7233341F8059ULL, 
            0xBCB7D4C5312443C8ULL, 0x3A6E1562DA345543ULL, 0x4FA809E859DB6666ULL, 0xB812785AFEDC3F3BULL
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
            0x38A3DFE2141BBEA1ULL, 0x9CD4FAB4200781D0ULL, 0x55371A20BC6E2F99ULL, 0xB251D987CCEE7C10ULL, 
            0x2B2F00680AE76D1BULL, 0x4F64751F56736D50ULL, 0x6498AB496DEEA064ULL, 0x1FAE93C97A666FC4ULL, 
            0xB116F1F93F9C8D2CULL, 0xC176F9B54F4E8544ULL, 0x5A69784EB24BDCB8ULL, 0x8041778051C5B141ULL, 
            0xC795BACFF86E6DD5ULL, 0xCD51CE844B31840EULL, 0x7C4E786CD2EDC0D8ULL, 0x066F9053E6051701ULL, 
            0x0C983BA8C48C913BULL, 0x9F91F09458F5183EULL, 0x17784E8C6E20553BULL, 0x4749C1197089786FULL, 
            0xA693DD654B970125ULL, 0x1A21ADA426B40A7DULL, 0xBDC88FE6E87E6608ULL, 0x9303FC0AAD8CDB0EULL, 
            0x8921993FC03FE2D7ULL, 0xD202990B4BBA0DBDULL, 0xA272BCD7A630910AULL, 0xFDCC9CB3A3974769ULL, 
            0x4A40E52FED0F7AFDULL, 0x3DA9D31C3CD685ECULL, 0xBD8595E347C073EEULL, 0x77BBE8346E694AA2ULL
        },
        {
            0x3C7E4FABA1AC7DA6ULL, 0xC9938F6D31EFE49EULL, 0xA7C4FE636994EE02ULL, 0x51588741AB60908AULL, 
            0xCD772ADEB0D89BC0ULL, 0xCEB1B43F18361458ULL, 0x66A32778D7D389B9ULL, 0xDCD0A300C991AE03ULL, 
            0x9083B9BE5130522AULL, 0x956561DB89F0B20AULL, 0xA16AC39EF53BF1FFULL, 0xE6EEC85E63901ACCULL, 
            0x271BF91E2642793FULL, 0xC61BB5C4E5C1D067ULL, 0xA8448ADB7A9D49E2ULL, 0x43D69FA6B2465B09ULL, 
            0x4A28FDAD36051F6EULL, 0xA792694848922B0AULL, 0x9CEAC5EBAB29FDAFULL, 0x981DAD1FD5DCAF42ULL, 
            0x1446781BACF0198CULL, 0x46577BFF09806FEDULL, 0x972116B985656645ULL, 0xC96E59DDA743E280ULL, 
            0x580D9E7E820CE3EBULL, 0xE13915E69F51D848ULL, 0x16E54FA48C02622EULL, 0xAAF28653E4D9ACF6ULL, 
            0xE1C575461B7601AAULL, 0x2DA209DDDB049AB6ULL, 0xA6B11B70012EE825ULL, 0xD63BD99C17523014ULL
        },
        {
            0xCC59559C3045BAEBULL, 0x592F16DC7C737F59ULL, 0x5E5FA992A4C0DC13ULL, 0xDA556CC263AA74C7ULL, 
            0xD415A4498934DE1CULL, 0xEFDC7DF81140DD79ULL, 0xC5AC7D82CE964B03ULL, 0x6F568358208CCCA5ULL, 
            0x90BC29AB2A48D6B3ULL, 0xC7D055FAEA773FE4ULL, 0xFD1EFDFD96478A79ULL, 0xFE73C092E7CA8065ULL, 
            0xC4DABE4A4E610178ULL, 0x0B19760190F0DF56ULL, 0x1F1FD82A0CF6B7EDULL, 0x7BF5EBD1FFECB308ULL, 
            0x5B7F212B89D824A9ULL, 0xB8A6289F3DCE5179ULL, 0x9226AC20AC5ACE8BULL, 0x0364EDD36B52883FULL, 
            0x4C2DAFB9C926A8A0ULL, 0x96164DF3954E7B0DULL, 0x035806E93DAC054BULL, 0x273B6815F3A1FAB1ULL, 
            0x7E090040E7B1C1B7ULL, 0xDD6BC9D3D21FFA39ULL, 0xB3E1B7D412BB6B79ULL, 0xAB421D20E3C09B64ULL, 
            0x647F169435BA85EEULL, 0x6A4E1B88E83A1B21ULL, 0x02171A6FC3715958ULL, 0x371B574997E3E62FULL
        },
        {
            0x8594B62D6AD3330DULL, 0x2833EE8978167277ULL, 0x6DCD3D4D04F20319ULL, 0x7071F56446C8E64DULL, 
            0x7D90BFCCE255B74DULL, 0xED525806CF39FD78ULL, 0xEB484C54003F3A04ULL, 0x0FBE4E31AB70FE8CULL, 
            0xBE6437EBB8A4336AULL, 0x0D65B478E6A89B94ULL, 0xABE987C51C22C0B8ULL, 0x6CB224B6F2A6C453ULL, 
            0x44F833286F499F61ULL, 0x431932B9B9551E09ULL, 0x012FC39A1AD46F88ULL, 0x64C6A9E11D580155ULL, 
            0xCF9A9308FFDABA91ULL, 0x9C0FB1C2A7ADD456ULL, 0xDC6A52D6F546AFB0ULL, 0x7B7186460381C90CULL, 
            0x34FBEF6CE88002CEULL, 0x3502D32E83A40B98ULL, 0x608A025C109A9630ULL, 0xADE428BB368C20D4ULL, 
            0x9403CEDE2D1B1EEAULL, 0x2A7ADB4976AE8F2EULL, 0x65C24B686B7386F3ULL, 0x32CE0B7D29BBB8ACULL, 
            0xD8CD3CA65397DE18ULL, 0x79FD5158FA1209DFULL, 0xC86539FF5D660D03ULL, 0x1E1AEA007E5FFB17ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseFConstants = {
    0xBCF0D36C470CC3C1ULL,
    0xB0AECD7AE24DD6E4ULL,
    0x647C55523CD60C23ULL,
    0xBCF0D36C470CC3C1ULL,
    0xB0AECD7AE24DD6E4ULL,
    0x647C55523CD60C23ULL,
    0x2A162829E8F61683ULL,
    0xF8CACAD99F9CA279ULL,
    0x5F,
    0x86,
    0xAE,
    0xC2,
    0xBC,
    0xB4,
    0x4B,
    0xDF
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseGSalts = {
    {
        {
            0x64D5DF6836F962F2ULL, 0xB82BAF593889B7BBULL, 0xB4375C8A1FB55BDEULL, 0x41B90FD651C367ADULL, 
            0x99B06C6ACD4DBD1FULL, 0x56CC385C18EEC9B1ULL, 0xB98DF9E70C611D47ULL, 0xAD364F105852F43FULL, 
            0x33B37241B3AE9D68ULL, 0x24A1B4E862D107C3ULL, 0xFEB16EB0AE9C4C09ULL, 0xE54BE90CA5AA9D3AULL, 
            0xEA27D0A5B5AB580FULL, 0x3D0402A1B616B55BULL, 0x6BF0A3FA59C81AE8ULL, 0x1153CDE29ADB8E7CULL, 
            0x872B7C6344037448ULL, 0xAC52B36F1FD59AC1ULL, 0x6A2014E0A27AAAD9ULL, 0xC0BF1AD243AAA841ULL, 
            0x7D4C68171E2A9559ULL, 0x1E5995CDDDCA8ADCULL, 0x965BEE930D11FA78ULL, 0x0EA10A0074E65043ULL, 
            0x5EDC4FF940B3DEDEULL, 0x584B2682A8518B6BULL, 0xC771F3F61BAD6996ULL, 0xB3C2567CD0DEBBF8ULL, 
            0x37A8EEF59E6B53FFULL, 0x49C8E28BBFB8FF10ULL, 0xD0E91FEFF247EBF1ULL, 0x6EE627F89816896BULL
        },
        {
            0x4EB17E23459FAA69ULL, 0x853170F076FFA42BULL, 0x7B84F5434F5E5319ULL, 0x336773B538C9410EULL, 
            0x1BA5DF0C1D2C70F2ULL, 0xEBEB2298F8AD9C5FULL, 0xF79EA24EAB139612ULL, 0xE0DB17E2AA5431B5ULL, 
            0xD2C028B96DA8FAD3ULL, 0x89A26F3119D57A61ULL, 0x5C6E588F11928881ULL, 0xE32BCCF418653F6DULL, 
            0x6F1511997B44F210ULL, 0x5114041A85CDFE72ULL, 0x29DC631707471935ULL, 0xDBF38B7059EE7458ULL, 
            0xF09EAED2550DA142ULL, 0x42F02711F1D1596EULL, 0x7ACB4D020D6D8287ULL, 0x3E5E45D223A7B5C1ULL, 
            0x5D55E24E0D402C73ULL, 0x479A6B41AACFBDA1ULL, 0xF340F950E0DC62F1ULL, 0xB5186A8F58D58E8BULL, 
            0x704637EFD4F1782CULL, 0x0EBEC20556120EFBULL, 0x3EFE61A97563E132ULL, 0x72B1760BAA2B3A6BULL, 
            0x164A405930717A1CULL, 0x8542222D784DF483ULL, 0xB3A89B8881F15969ULL, 0x6B12AABB5B9512DBULL
        },
        {
            0x21B4061A06B7A26BULL, 0x286DAC55087617FCULL, 0x3A04CF3C4C522F55ULL, 0x200914F2B9925E90ULL, 
            0x0405B5E4E8575737ULL, 0xB91717C4C14CB835ULL, 0xDEB887468C43F3E2ULL, 0x91F8AE1F67BA4EEFULL, 
            0x6962FC500B5550A1ULL, 0x1D371A9D22D2B9F3ULL, 0x09D5C250513D491FULL, 0xEDE4D286A5B445BBULL, 
            0x2E125412B5E9C68AULL, 0x96D3937BE0F8633CULL, 0x659D6D466E98C55EULL, 0x469AF4C1C138939DULL, 
            0x2307D38206A6DBC5ULL, 0xFBB1B22E65C5DEC9ULL, 0xF122C8BECE08D09BULL, 0x580B5625806EE3EDULL, 
            0x8F22B6DCAA90D6D3ULL, 0xD4D643096A4CEDEAULL, 0xDB54638A935012D4ULL, 0x7543515E4303A267ULL, 
            0x350E0F8121DDA59FULL, 0xEEEA25BE6F5C34EAULL, 0xC1740845A91F45FCULL, 0x6B15E98B6EB616BDULL, 
            0xD97B3A4EE5BD6A49ULL, 0x8444BCCDDBC05C31ULL, 0x8568036469DB6088ULL, 0xEA7E0EA2E0AA2BE5ULL
        },
        {
            0x25896E9D5B5F3E7EULL, 0x53DFBD9460E6FA34ULL, 0xDBE52C1FB59B5501ULL, 0x201A869840DC4605ULL, 
            0x458F8DA03D486EE2ULL, 0x3F7321FB66D051D3ULL, 0x4485D989200536B6ULL, 0x6619888C56281556ULL, 
            0x1E59C29BCCE07B6BULL, 0x5F5616D59928D1F1ULL, 0xF863053784167A18ULL, 0xFEE15AB767E95CF1ULL, 
            0xFC47802E31A5ADC8ULL, 0x334FC2EC47C38887ULL, 0xB7AE716564ADAB4EULL, 0x739D75CB55908DBCULL, 
            0xE20D6A6F126EBAC5ULL, 0x5C63706BB94B4CF7ULL, 0x9E994A72FE56F6FCULL, 0x14FAD58B5F56145DULL, 
            0xBBCD6E97688646BCULL, 0xCD32A52D09054516ULL, 0x05E00B2ED43B55AEULL, 0xA7C71112EE0075EDULL, 
            0xA8D592639C12BF9AULL, 0xB23399F4DF1578F1ULL, 0x850A17E102D198A0ULL, 0x9A8579FA80AC525BULL, 
            0x75CF0B984092B7F7ULL, 0xE32D4F14CD368D71ULL, 0x7EF65283EB903286ULL, 0x818CA6D7917FFAEFULL
        },
        {
            0x6B7FB57C8F33125BULL, 0x2AE3CDCE9F4E21EEULL, 0x0958D4E69D3F5F06ULL, 0xAB94DB5688DCE4CDULL, 
            0x4B4583056DC63D80ULL, 0x3DBFEE0DAA8101C9ULL, 0xAA269ED08925CDCCULL, 0x3203DE62CCE7C3CEULL, 
            0xCD3BB2EB62E4B659ULL, 0xAAB65FB4972080B8ULL, 0x55C530238F52D71FULL, 0xB43F4BB642A5CDEEULL, 
            0xD8013B0D9E351921ULL, 0x9EFD900B05CA25B1ULL, 0xD91E21C85B30FF73ULL, 0xA98D8E20605B958BULL, 
            0x67B9D9FB71C6DD6FULL, 0x6B6A1E9E9A0CF343ULL, 0xA71CCD40BA6F3792ULL, 0x0364CFDBE5D5C16DULL, 
            0x5C06554971FF58B3ULL, 0xE876C38A5AF22F66ULL, 0x1B46FF8C8E992982ULL, 0xD05E049C3A9261E2ULL, 
            0xD2A781E917E58334ULL, 0x20D17139E28BB302ULL, 0x635CA41EA9EA2873ULL, 0x1ACD6E40BA4B5E57ULL, 
            0xF4F7B474493F6341ULL, 0x05D7EB6B16B0E989ULL, 0x59C6F22A1C0AB525ULL, 0xE6D1CA19D2608E97ULL
        },
        {
            0x1791A6B8646CDA8EULL, 0x6D13AA123538E7CBULL, 0x23526B174B1694C6ULL, 0x03EE138C6DDBC395ULL, 
            0xEDB899E37DD02221ULL, 0x5C1B05A7FA375819ULL, 0x3B2793480407FFB8ULL, 0xAD0379F658AF7660ULL, 
            0x6F6354A32D5C384BULL, 0x5E8E2E92DF02CE1CULL, 0xF1E437D41D2E3442ULL, 0x5EB5041F9F5DF7E2ULL, 
            0x5FA2133B8318A67BULL, 0x5B602289929C17B9ULL, 0x56B9452784F1E950ULL, 0x1332D9383AFBAC88ULL, 
            0x093F31F5C38DD395ULL, 0x040A64C9FDD843C5ULL, 0xC2F35F9594CC5DD3ULL, 0xE050F3CE90D2594DULL, 
            0x0112EDA27C8E7629ULL, 0x67C721CCC91A3EDBULL, 0xFE90860DA4F03DC8ULL, 0xF93138DC9DC8179FULL, 
            0x309E75680841386BULL, 0x5B70071DDE7600FAULL, 0x931A369B4C000861ULL, 0x8E5356FC242FB21FULL, 
            0x83D763ADE66CC7CDULL, 0x843AC8391FBD1A39ULL, 0x7D46558AFF0231FEULL, 0xD48D1EFA2C2F090AULL
        }
    },
    {
        {
            0x6F13642F04918D0DULL, 0x1C396ABA4C56518CULL, 0xB15BA7F4E5154BC3ULL, 0x8E2DEA08A00E1F13ULL, 
            0x5071633ED189C444ULL, 0xEB6FBE5F788F07E6ULL, 0x507B4A4459CF59DAULL, 0xD69A43A63C9695FCULL, 
            0x2F8479F6C46D8B5BULL, 0xF9EEDB327DBA5251ULL, 0x4BA8761BD6F37D1DULL, 0xCAECF063897EB84FULL, 
            0x41423D8BC663CF8BULL, 0xCBDBCA8D4438F31BULL, 0x6C51BC858D824940ULL, 0x08597CD11D138899ULL, 
            0xF0E1EC4F32C9F2A9ULL, 0xFC3A2321431E15ABULL, 0xA03C999C1FEDC61FULL, 0x0F835752E7E1C645ULL, 
            0x42391839E02BFA0AULL, 0x12F7CB8C24F345D3ULL, 0x400CEEE62684529DULL, 0x3AC1F7DAA4455D39ULL, 
            0xF699D16CCB9F46A9ULL, 0x1ED81126299AEA12ULL, 0xC0285D86DFC4D47AULL, 0x00BDB91AEAADF29CULL, 
            0xFB9029D5A8C27377ULL, 0xBEDF78A5BB01ECF9ULL, 0xE4F96AF6850F3341ULL, 0x4CF8C99320ABD246ULL
        },
        {
            0x9F84E5CAEA2FEC81ULL, 0x39D2BD42BA62631BULL, 0x2DC5959E38C2F67BULL, 0x75CEC89F00A66975ULL, 
            0x3B36688D048037CDULL, 0x53199E9BE5465507ULL, 0x657586EFC9666602ULL, 0x72AFF77B85ECA65BULL, 
            0x7C003EB880740129ULL, 0x348C2FB48B5D4F4DULL, 0x76743E0A34C2AF1EULL, 0x6DFC4041898FC699ULL, 
            0xF28802125897735EULL, 0x71ACD2580921F46EULL, 0xAB228954EB4EB5C7ULL, 0x642EDF7BD38EEB2CULL, 
            0xB410374BF34AE748ULL, 0xEE96D7D0FC34A912ULL, 0x4D88486E4421C4AFULL, 0x7A9A611BCFCFC4E4ULL, 
            0xB66BE16F23B7B84CULL, 0xFA3E28226D478542ULL, 0x922A0C69FE71243FULL, 0xE8BC64F25305A744ULL, 
            0x9AE856FADC9CD2C9ULL, 0x1CCC0F84E30ED238ULL, 0xF375FC4A0EDD5A9FULL, 0xACAD943F0BE97829ULL, 
            0x27D37BD726B4CCB0ULL, 0x02124C7DED33DE15ULL, 0x8A74802C7DA43544ULL, 0xE4D63CD940D39B97ULL
        },
        {
            0xBDFF3113E3D506CFULL, 0xF59B69FC5BC29FFCULL, 0x0E8924F6B9203FB8ULL, 0x2F46B19FD05B3865ULL, 
            0xD2BE5150179AAA02ULL, 0xBEAF34085393F595ULL, 0x527380C1E79CC377ULL, 0x1ED9261E9A24D142ULL, 
            0xBF97980F1375A036ULL, 0xA73553F22E9ACAD7ULL, 0xFD69BCBBF5629E35ULL, 0xAF5081C2F21E92D2ULL, 
            0xF39C2190890A17A3ULL, 0x7065F7F433F7B2E2ULL, 0x1F027A96F05D69D0ULL, 0x3F0D4FF7FC01AFEBULL, 
            0xE75FCCEB5DC3BC00ULL, 0xC02B90B49F877267ULL, 0x274A8BF4283321FCULL, 0xC68A8B2AAD4C44C9ULL, 
            0x6FEADE7B2DAA5368ULL, 0x37AC11A863765F27ULL, 0xC33526CAA94AE552ULL, 0x185FC5C2B97A094BULL, 
            0xD54EAC503BB79CE2ULL, 0x416B5E2B18389588ULL, 0xCBF231F375B6A5BCULL, 0x87B2A11241BD1ADEULL, 
            0x078D4A422E8547ABULL, 0x5FD5CC454E12F772ULL, 0x06C94CDD617FAD51ULL, 0x3F6CC19F70E6FB31ULL
        },
        {
            0xC74CB39382D38F7AULL, 0xDD8A1884DDE4B1C1ULL, 0xE8C23C49D8069CFAULL, 0x032DA688DDA9EC3EULL, 
            0xB814691CBDB7EF98ULL, 0x6AA4B25BBB3DC399ULL, 0x799C6595B2686676ULL, 0xFC8BA5DDB262F9AFULL, 
            0x75AF2E5646052EE9ULL, 0xA63A6B8A60AF3AE3ULL, 0x6ACF167FAB26A84EULL, 0xD1D682EE4A2941CCULL, 
            0x7173F68FEE728C40ULL, 0x935A0EEFE6351B4EULL, 0xC5F811F6BD09560CULL, 0xC5C20D891CFCE86EULL, 
            0x76A18AB38FCC80D3ULL, 0x60D40637C0F458FCULL, 0x2FD6664627EBE403ULL, 0xBCF1D5E8349F631AULL, 
            0x699A6CEF63F658D6ULL, 0x5C58123623D79A20ULL, 0x7FB64A525B672FC0ULL, 0x4B2969E107FFDD58ULL, 
            0xB0B6D252900D7286ULL, 0x18EFC8C1D322B108ULL, 0x3AF4AF63F182D260ULL, 0x4A66665B57C71D58ULL, 
            0xC3DA17BE22C237B7ULL, 0x2D77AB30E6DE8557ULL, 0x00CE1BA4F0255EF0ULL, 0x73568CEAC5BBA715ULL
        },
        {
            0x5A40ACB14A2E2189ULL, 0x5D4D1B5C0F07E479ULL, 0x7DB974952C05694BULL, 0xC6A3DF2914840A2AULL, 
            0x143379638DDCA0B8ULL, 0xB4CE784FE83ED320ULL, 0x877124274F7A8C7BULL, 0xC0089D91F57E964DULL, 
            0x1693840B02E750E1ULL, 0xBD643760DF7A4D8EULL, 0x69DAC1E7C9901EB6ULL, 0x421E02D0571455E3ULL, 
            0xEE109CAA878AB2DFULL, 0xF028C13789014D15ULL, 0x662B47803DA13AF9ULL, 0xB4AFF1D030A5909AULL, 
            0x9B3B4BD850CD1999ULL, 0x5892D1600102780BULL, 0xF8E8D3BF61D7B64EULL, 0xE3639A27553D35E1ULL, 
            0x5B80995330D3418AULL, 0x0F624D6E5BC7458AULL, 0x968B08044319D08FULL, 0x47A1B3ABDE977397ULL, 
            0x4C637357551FF4F6ULL, 0xE67329B7E97F170AULL, 0x8E5287F081BFC102ULL, 0x3381BF0385545D03ULL, 
            0x259FA7DA9265972EULL, 0x82116760B33AE8E1ULL, 0x965B4F68C5E36196ULL, 0x57BB29D71B5158ADULL
        },
        {
            0xCD8B9F4BFFB6794AULL, 0x040B0CAD4956326BULL, 0xDA899343409A0264ULL, 0x86A336EE0943F99DULL, 
            0x8747BE5967AD086DULL, 0x642648337CA23B15ULL, 0xB31C813251A8EC82ULL, 0xA1717CD9F385DF60ULL, 
            0x441603A841A26BEBULL, 0x3ACBC221CAC3FEE4ULL, 0x561F5E8A537E0B88ULL, 0x89578E59F0C8E159ULL, 
            0xC7938C01C00F4753ULL, 0x5F4DBB34E70800EFULL, 0x0F0625F05903A5CEULL, 0x84C101C805295177ULL, 
            0x7324689DB6E11372ULL, 0xBA35F50981ED868DULL, 0x9A324E4EB1BCE6EFULL, 0x36F16AEB4A034C6CULL, 
            0xD329A326B5E1B8F6ULL, 0x30C4DCD2762DDA28ULL, 0xE4DC13C557836AE4ULL, 0xEA61452C484CCBE5ULL, 
            0x69F990E8ECBAFAEAULL, 0x20103CC6607E0117ULL, 0xAE501B0A13A7B534ULL, 0xF8B6838380F62866ULL, 
            0x4B4385F053E2317EULL, 0x1D5AA75B27B3A8F1ULL, 0xBB7B6DB30519F774ULL, 0x6E43EA634CED51F0ULL
        }
    },
    {
        {
            0x6555E7707DBECD37ULL, 0xA0915823C21781D7ULL, 0xE88467E5044DC95BULL, 0xA397EE30A3E1B0E5ULL, 
            0x39EA191B50E7CD1BULL, 0x9EB917012D03DFAFULL, 0x0B9C23173173899CULL, 0x71AF8A9E6012A9C4ULL, 
            0x2BB621E463DEE10BULL, 0xBB33DA876226309BULL, 0x5DD8B9C158AEB0F6ULL, 0x22989968DEC2A924ULL, 
            0x936219D3AF68254AULL, 0x252F64F64C7412ECULL, 0xA93EA271EC6CCCD6ULL, 0xE6F803538DBC2C8DULL, 
            0x3E5AC698F1A142EEULL, 0x773201E730C68351ULL, 0xF801992B5251F97BULL, 0xCCE04D5FB7DE3915ULL, 
            0x6C73613551DE3298ULL, 0x24A02293C2748D65ULL, 0x52BB42B6DED5A9D6ULL, 0x19BC4EFCF8DD78C0ULL, 
            0x7684297BC6BE7B4EULL, 0xA0ED357F551A0A4CULL, 0x0250B830AE52FBB6ULL, 0x240970BACA0D1CA2ULL, 
            0x1D1291CCC9E74D93ULL, 0xB3F7A6F6A6C09DCAULL, 0x881F6C6320AB5DF4ULL, 0xA72D835776B8FA48ULL
        },
        {
            0xFD45BCEBCB98341AULL, 0x5006C9C65316F33AULL, 0x73C3CED7A82A654AULL, 0x8154390A3CF666B4ULL, 
            0xECAE0B282135F84FULL, 0xDF7734780B9C0F63ULL, 0xF7DA7033FDB2D347ULL, 0x3D40DF83AA450993ULL, 
            0xA687D60A3A2A69CBULL, 0x0E0C97153AF74004ULL, 0xCAB6A7DBA4C73CA8ULL, 0xE86AF365005328DAULL, 
            0x30D766A54DFD5DAAULL, 0x06D7AE3295C83F0AULL, 0xBA6ED7CC2CCE5242ULL, 0x156AC8D9628F3339ULL, 
            0x5C569428B88E5164ULL, 0xA6769105EE47F3D0ULL, 0x42768EBBE7087244ULL, 0xFE695596B458093EULL, 
            0x45779175C35DBB1CULL, 0x6F724BF73C9092F5ULL, 0x098C7FD75D14D1EFULL, 0x806F2021A60BD473ULL, 
            0x0CA91F37D9D33339ULL, 0x30BE0C810232A64FULL, 0x2623DE4A048EFFCBULL, 0xFF0643D835D16951ULL, 
            0xA67D4F6F31531B2CULL, 0x922778C45028A31EULL, 0x30CBB87444AEEBC6ULL, 0x53CBD2DA42D58A5CULL
        },
        {
            0x746F8D0AB0696605ULL, 0x932AA597D16398EFULL, 0x047E073ABA81A1ECULL, 0x00EC66BB17E2DD65ULL, 
            0x96196B9E9D0CC27EULL, 0x0D093FA6D80E7172ULL, 0x3E02FCCCD639CB24ULL, 0x12AF5676F942AA4DULL, 
            0xCDA26B4ADE6EE6BEULL, 0xF6FE52DEFCF6F416ULL, 0x511EEA98290600C8ULL, 0x6A9A402F80827759ULL, 
            0x48912BB4CAD11793ULL, 0xA13E04551C031F14ULL, 0x915BA937E4F549EFULL, 0x5B4D5AE594AED2A0ULL, 
            0xC41751430F22F88AULL, 0xDD7421C82317D8C2ULL, 0xE5CD12610234DAECULL, 0x150B26D292DA43F5ULL, 
            0x2A25C231E37AF60EULL, 0x18F7674CDB037D35ULL, 0x79235E7DD8613CFEULL, 0xBFD92F5EE8795570ULL, 
            0xFFF92DC6EAC51E85ULL, 0xE30A6E41434695D9ULL, 0xE10F66374B6606B7ULL, 0x269C9FF2F3AE4584ULL, 
            0xD3A23971FDEEFF6EULL, 0x2592D666EEC684A6ULL, 0x02F03CD00EAF27F1ULL, 0x1C7C94D77A576F1AULL
        },
        {
            0x7C2FB6EEED5EBE41ULL, 0xE52A4B49ACED9BC5ULL, 0x899BDAE51B484BE1ULL, 0xCA74713F271BF435ULL, 
            0x2D416311C361F144ULL, 0x6ED41730C1001DC4ULL, 0xDFC923C41D3464E4ULL, 0xC4E1BF28C2D2BD1CULL, 
            0xA8B7D488720D05BDULL, 0x2335412FAD059D18ULL, 0x22808C354465DA69ULL, 0xF00DECB1C8B7C5EDULL, 
            0x6CA747B43590619FULL, 0xC21CA5E78682C87EULL, 0xFD97A449D6A12B9BULL, 0xA06F9EA9269D07DAULL, 
            0x6CDEB69F82D03307ULL, 0xA99C3C1B7014487FULL, 0x5E5D75BAE82E80E3ULL, 0x07F4287EDE5BEE12ULL, 
            0x4ABBA38D477B8911ULL, 0x2B801CF63EC95E6DULL, 0xC00809F6631A29DDULL, 0x82120FA870DC8D37ULL, 
            0x1567355D6C0F5BD9ULL, 0x8150C646CF5F0A40ULL, 0xA2CFB6D062DA836EULL, 0x6247234026B71B83ULL, 
            0x02705AC79E0298D6ULL, 0xBC4D4B2AE048886AULL, 0x88D2635D289BC7DDULL, 0x43EFAABC7049C530ULL
        },
        {
            0x84AE07E8C3D9768EULL, 0x3E1EBA3E777323D6ULL, 0xCF9F5932F6D284D1ULL, 0x091E781F222CEB98ULL, 
            0xB23B61B76300A529ULL, 0xBAE1DFD6F1FF3C31ULL, 0x4431AA67A4463A83ULL, 0x96937A56FC7964EAULL, 
            0xD896E940AD822736ULL, 0x3EE36008EEACBFFDULL, 0xA4529D9BA9DB34EDULL, 0xAF6228486F9A2DDBULL, 
            0x0B7DBCFB407B7B03ULL, 0xBC39045274859257ULL, 0x02968DA46DF88DDEULL, 0x6BA5D04152C98BD5ULL, 
            0x2ABF1282CF585182ULL, 0x0E73A0AEEF6B8A2AULL, 0x1C764A617A22BE2BULL, 0x1CAC3A41FF81D528ULL, 
            0xAEB10DB8452CBC44ULL, 0x13CF0978442B0BC3ULL, 0x074E3F075A16B779ULL, 0x3020452FF8B1A9FEULL, 
            0x94411005367479D7ULL, 0xE2CBFEB90793999DULL, 0x6736BC3748DF8B29ULL, 0x6FE803D646A3957CULL, 
            0xE7BB8C0F8D3814B3ULL, 0x6F8831371FB917C2ULL, 0xEDE5106A4F506C48ULL, 0x1C273DD50170DA5BULL
        },
        {
            0x19421F2B52E3DEFAULL, 0xA68C12203DCF421FULL, 0x43C824C52884DE6EULL, 0x09E13B51B6D3A847ULL, 
            0x134DE09070CCBB05ULL, 0x282BE77C151B025CULL, 0x6AA716F6A8AA7966ULL, 0xBF4CAAA28496797BULL, 
            0x3B4BFDFC478AC0F1ULL, 0x31417FF1B5541F8BULL, 0x7B12B46AB4AEEC96ULL, 0x66958E7999924DE3ULL, 
            0x7EB2554296DC5843ULL, 0xF0EC1F97CF329054ULL, 0x279AE2F432C63C08ULL, 0xFF32913632A76E00ULL, 
            0xAC131171AE74BA0CULL, 0xED1A9ED40F1A5306ULL, 0x814867C91B396CC8ULL, 0xE54D4E207F65D833ULL, 
            0x30D5C47D73A41446ULL, 0xE5EEE90C4C79D7B9ULL, 0x5E75B2770D9A9923ULL, 0xA0CC16BC7A2C2403ULL, 
            0xDA86437280D8B921ULL, 0x2235E59B4B017998ULL, 0x5EC2BAE3FF9B328DULL, 0xA5276ABE4062DBDEULL, 
            0x3D580B83A5754CBAULL, 0x637B18725E4D2661ULL, 0xDC89EA78C85A324EULL, 0xF80A05130798F215ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseGConstants = {
    0xE84230DB65E87E7DULL,
    0x96EF124B9DB51E5BULL,
    0x522D3CC91DB669EAULL,
    0xE84230DB65E87E7DULL,
    0x96EF124B9DB51E5BULL,
    0x522D3CC91DB669EAULL,
    0x7825621AC686FEF1ULL,
    0xD3DE9A17FC604194ULL,
    0x79,
    0xC6,
    0x3A,
    0x8E,
    0x86,
    0x21,
    0xEE,
    0x27
};

const TwistDomainSaltSet TwistExpander_Antares::kPhaseHSalts = {
    {
        {
            0xE58474B4D9A0EC95ULL, 0x192995D8E76C0075ULL, 0xC3AB026FC8672ECDULL, 0x65AE74C3056C2E7CULL, 
            0x9F4D0187A8CBF2E6ULL, 0xF7719F4F2514B7F6ULL, 0x2AB16BCB8ADDFD7BULL, 0xC2FD3E10C917A373ULL, 
            0x95F57623DDF7E4ACULL, 0x3501F4EDE5FFDF37ULL, 0x54C67F73D004B633ULL, 0x91703CD9DB26FA70ULL, 
            0x9E44A313A854CC6FULL, 0xCEA73F303F37C886ULL, 0x89AB073C7CDDF6D7ULL, 0x07CA9969A4F33614ULL, 
            0xB02F1EBDA2AB3487ULL, 0x9CC942D06BFF77DBULL, 0x2702A361D58A4475ULL, 0x05801253D7072778ULL, 
            0x2E9E83419F207348ULL, 0xD014BA4F2A7817AEULL, 0xBF8763F48C5ACB6EULL, 0x6BD788338F2947D3ULL, 
            0xA031BCB5CE8E87E2ULL, 0x415A73CB9950F926ULL, 0x288B6C331F1F0C03ULL, 0xA2A41C52B0BFA09AULL, 
            0x6782C180F7BCE509ULL, 0x0CFCB061B6C5C296ULL, 0xC31121F46271E630ULL, 0x0D741FC57991DD5BULL
        },
        {
            0x8E2ACD83234F6E10ULL, 0x67609E04DF3220C2ULL, 0x4D4C384BE92FE42FULL, 0x0691E14ABDAC9331ULL, 
            0x22E04020DD2DAFA6ULL, 0x5AE5990C2410B050ULL, 0xB106DC572E179E21ULL, 0x9B846D1205845BBAULL, 
            0x9E5E8F0690CF42EEULL, 0x918085F2A9444FC3ULL, 0x6744FFC3EC37D672ULL, 0x1F4C8DA767B41CA8ULL, 
            0x1E3369F009B3C48FULL, 0x27C4D4C077EACFB8ULL, 0x43E9BE2F7CA5669BULL, 0x70B960D6B2970F7FULL, 
            0xFF2384E853693482ULL, 0x48A6229D4E2DD8D5ULL, 0x7ED233047C6329D1ULL, 0x0881903ADCADB894ULL, 
            0xD391EBF65F8175AAULL, 0x331B768B4F237E4AULL, 0xE53E35EF86D1651BULL, 0xCAA53258A1E49959ULL, 
            0x93AB0FD4740E9A28ULL, 0x362FD491BB70DCDBULL, 0x2638E6840F42D858ULL, 0x69F1FC7E475FE321ULL, 
            0x8B2C1FFEA2EFA001ULL, 0x3397A6D01514C34FULL, 0xA6DC5B4AC57A73C7ULL, 0xD2FD0F55F00F8115ULL
        },
        {
            0xED4EFBDA8FBE0529ULL, 0x2609E4B5EDC38857ULL, 0x3D2A72F563D2B7E8ULL, 0xFE2F8CBA791A8B4FULL, 
            0x07EC3123A16E5995ULL, 0xCF9CDF5221090528ULL, 0x26767EBA5A2C01AEULL, 0xEA02E644B588FAB6ULL, 
            0x6E0C8F191A539163ULL, 0x1F58871257E3B20AULL, 0xB67C00E60C01EFF7ULL, 0xBE0A39A2E06EB713ULL, 
            0xE696278E88EFDFA0ULL, 0x11C5AFADFB1B7D12ULL, 0x7D25A88DE71E8216ULL, 0x05F73B242BC73B93ULL, 
            0x0BB001438134764CULL, 0xD094E24A993C0CBEULL, 0x7FF296A0E8DB1020ULL, 0x2A1AA81AFD6DCED6ULL, 
            0xD83EBBA6089C836BULL, 0x51E8775A30C604C5ULL, 0x82A3C20FBC6BF410ULL, 0x56C8B10A0225EC08ULL, 
            0x025EBFE56655537DULL, 0xA64A1FFEBA43FF95ULL, 0x35E72BB54846DE35ULL, 0x86CF676CABA2239DULL, 
            0x5A03AA1C5E60D7F6ULL, 0x2B3D0A9A3C3CCC7CULL, 0xA47C9F611A8F0FBBULL, 0x882F926A0408C70EULL
        },
        {
            0x6783E7C307BF7CDCULL, 0xF2F4B88BB516480FULL, 0xE41F0F5B6A051291ULL, 0xEAFCD1AC10814F90ULL, 
            0x3665EDB3E0E8D13BULL, 0xF3D22D3987A54FD1ULL, 0x2EF325E7B8F73BFCULL, 0x01DF1915EBA3E379ULL, 
            0xC37971489AB4A5A7ULL, 0xD40FC28FA62536E1ULL, 0xC10DCE0AFC232EA0ULL, 0x7C34F336E74E927DULL, 
            0xC418F75E41314AFEULL, 0x33E0F3770CFAB8E2ULL, 0x3892A3608977607BULL, 0x26FAA709C675A8F7ULL, 
            0x6D4F2D8B30244DA7ULL, 0xDB3F1F37419A7477ULL, 0x7A24DCB284F25972ULL, 0xDD8B48E1F109382BULL, 
            0x2B24611BC2087AB8ULL, 0x8F730A1075EEA57BULL, 0x9E08392EC63B4B00ULL, 0xEE6283E39D03AE19ULL, 
            0xFBF6ADBA016B2F68ULL, 0x28E1F35ACAB54D0BULL, 0x2B236269294AE2F8ULL, 0x68EF0E79B7563DC5ULL, 
            0xFB9FCA52929C2425ULL, 0xCCA0AA7D4106EEEFULL, 0x3899A0B5B93A0850ULL, 0x6F557B14B3745C28ULL
        },
        {
            0xFC55E9BE4F8BAC81ULL, 0x3F80D65DF0E15158ULL, 0x21769C983B9899CFULL, 0xB861AA6831054A31ULL, 
            0xDC087CDBFF684223ULL, 0xC58E2D5E1C3179EEULL, 0x52AAC75F4BD35B13ULL, 0xC50465F2DC41063DULL, 
            0x2E6CA3779228275EULL, 0x5D724E9F415E9F1DULL, 0x6ECCB5D547145F23ULL, 0x774F8FFBE0F3E7E2ULL, 
            0x5C11793ED61E8FD1ULL, 0x53736C17C1DEEF97ULL, 0xE09C239A2F925C25ULL, 0xDF39A71DB1364F92ULL, 
            0xB373F8B1DE806560ULL, 0x4BE31C52D3C82831ULL, 0x91BE0CE90333680BULL, 0xB4D059671EE546DCULL, 
            0x9AE6D72C757886E9ULL, 0x05038F434B62A427ULL, 0x8D0880140C38D3F4ULL, 0x08FCDBC091F204D7ULL, 
            0x99DEA1BCE028E35FULL, 0x67CB4E69588BC972ULL, 0x2295BF68270C6B2BULL, 0xF42B0D4D571FCE98ULL, 
            0x2BF2B31D01396638ULL, 0x5346E5D3547EE236ULL, 0x45ADF0C7D756A6D7ULL, 0xB07FBD6B3FB1C797ULL
        },
        {
            0xD55AD3F9939CEF2EULL, 0xD6AA09E41B26D84AULL, 0xD310501E7B60F7F5ULL, 0x09588A49264675C3ULL, 
            0x4C941C525F502DFBULL, 0x8EC748F71DE2383AULL, 0xCE1EEB22ABAAFA39ULL, 0xB001BB9922B34748ULL, 
            0x6111983E13CB511DULL, 0x9064DC124FBD8CFAULL, 0xED483B08F03C6276ULL, 0x5B84A510CE5B601BULL, 
            0xCE8F9C5B6A93CCF8ULL, 0x4C8C31B842E9802BULL, 0x6EC2C7023E875D67ULL, 0x3149308073CB1B29ULL, 
            0x56B16E378D724DC5ULL, 0x7295DEB483AE9A87ULL, 0x0B78EDDE1E07E27FULL, 0xCA69436A41F8E9D1ULL, 
            0xF18D206F54C83CECULL, 0xB62960CEC1884E80ULL, 0x4F5A024334D9EB42ULL, 0xAC345C28266C8608ULL, 
            0x52B0896198EF50F2ULL, 0xE15DA5461C87228EULL, 0x1710AF4A2557824EULL, 0x0C42CC5D6FEF239FULL, 
            0x338ACD6AF53948E2ULL, 0xC4A5FFD1E2A8CB7FULL, 0xBCBBBEB3D06C638AULL, 0x49D36248139D896FULL
        }
    },
    {
        {
            0xEA3E61E5ADBB1B22ULL, 0xE0F56679D1049945ULL, 0x097BD2CE69986C87ULL, 0x7926B0F7E598BADFULL, 
            0x3FCFE683C27FDA40ULL, 0xA7A5075EB92E81C1ULL, 0xBDFC9522BBCCAACAULL, 0x27FDF1C44FAEF8FEULL, 
            0x0E47CA9C8BD959CEULL, 0xCDCED917BDC43CCBULL, 0xDDF5025EADBE5A39ULL, 0xE5E901531560258AULL, 
            0x30F6A695798DFB9EULL, 0xA4A9B864E9C37528ULL, 0x5672E356612B6D38ULL, 0x310D517C77D35E34ULL, 
            0x99A79BEC0D62E4D6ULL, 0x34B3DB9CF0E5A7BEULL, 0xAA10FEAEDF833D2EULL, 0x5E4326A919EE21CBULL, 
            0x425D3986D15A3DE1ULL, 0x17AE95BD828FFDEEULL, 0x458F7793957A4A3EULL, 0x96C29FD7425442BBULL, 
            0x13BD8F84AD8812C7ULL, 0xEFA5809268C8CA71ULL, 0xC3EAF0BE8EF56B2FULL, 0x21F2191B5D889A9BULL, 
            0xBC067B836D55F37AULL, 0x139743FE2EA48ACCULL, 0xA9C8CC8F5DBD5324ULL, 0x6A307CF7F7F39218ULL
        },
        {
            0x20FB1293DD2B58DEULL, 0x2A25C8BFE243D072ULL, 0x9DA480EB844D1C67ULL, 0x97574E8E07D7FCA2ULL, 
            0x27182BE159C478ACULL, 0xCF9BC97DAD14F096ULL, 0x88E34E1C6B21693DULL, 0x96C0DD95B071BC9AULL, 
            0xEE0A53411638364CULL, 0x7D214B2F8CE48AFBULL, 0xE15ED93A466ADE62ULL, 0xDA83DA48AEBBAF11ULL, 
            0x945DBB6F93835D2DULL, 0x10769EAE1A1ABA03ULL, 0x60783FB3B6353E3BULL, 0x2096E3F205D66837ULL, 
            0x2645DAE82ACE0DD4ULL, 0x3B27C60071106265ULL, 0x9C61488249A65857ULL, 0x9D74F8CE8F81E44DULL, 
            0xCF13B826F4BDDABDULL, 0x45B8CCDA38810C44ULL, 0x63DC24AAA15DE0B7ULL, 0xCBFFE0DFC4835436ULL, 
            0xEEF4AE5D347960D8ULL, 0x2F6CD65944951F9CULL, 0xC1D54DFD39B7EE12ULL, 0x708691F5327C87BCULL, 
            0x7B3713F8FFF121D2ULL, 0x198AEC5A0CCA1952ULL, 0xDCF959AEF91AF8AFULL, 0x83AF6E37F573E9B8ULL
        },
        {
            0x66505896DC6CFACAULL, 0x9B993D61FDFA5DD6ULL, 0x7243FB1E8BD365F1ULL, 0x149B90F55FD70FADULL, 
            0x8106A6396290E96AULL, 0x36B26E7624CF79CCULL, 0x7EE67876379F9E28ULL, 0x851A62F0CE160C19ULL, 
            0xE7A60A428A6F3168ULL, 0x869433F1E9D70A08ULL, 0x5CE8F42989A78AE0ULL, 0xD50289ABDC9DE75DULL, 
            0x4DC615AB0F29FC54ULL, 0xCF54C9170322E39CULL, 0x5C15E285E94B1E32ULL, 0x5A90E667A1C59F92ULL, 
            0x6454AAFE08705736ULL, 0x739F7EA9AEBE6BE4ULL, 0x0E35E357C2222DF5ULL, 0x4511C5B7E713598DULL, 
            0x2D12BFF608490100ULL, 0xAB59BE6E4401A7E6ULL, 0xA56269B7E8AE5CDCULL, 0x2AF13019549C9AC2ULL, 
            0x13BA2CD1DB76D4EDULL, 0x6D8F3E848CB174B2ULL, 0x73ED57615004BC69ULL, 0xBB9EADB0B9C447EEULL, 
            0x1761578E13224B06ULL, 0x5E843C0A43A5FF48ULL, 0x31423AB1A2FAB354ULL, 0x35BBCF05FA8F1EB7ULL
        },
        {
            0xC5D52EF1E999B9E5ULL, 0x0174FF8355F0682FULL, 0x2329BA1DE021FAF6ULL, 0x6821594326EDA1E3ULL, 
            0x607AEC4BA699928DULL, 0x060F678488C11118ULL, 0x0BAEB6E0B45386ACULL, 0x43E74D0CC4BB9DF2ULL, 
            0xB9CE8DE9640F88D6ULL, 0xD2A38D835BE7AFD1ULL, 0x2B8B98855F2377C0ULL, 0xF036FAE479AFA6C2ULL, 
            0x0CAA805DE1BBCF68ULL, 0x9330FD1D78A81B59ULL, 0x7BFDE7E974B0C31CULL, 0xA8880B9A4FD596E7ULL, 
            0xED5C0FCC9C5E70E0ULL, 0xD58CD223E830EEBFULL, 0x9730155B2770A87BULL, 0x98AA5DFCA2D0490FULL, 
            0x3001BC7DA298432FULL, 0x198A9D9B7A08D11DULL, 0x9CE9628B74B072EBULL, 0x7937692574F440C1ULL, 
            0x1A6DEEE0AF8C2697ULL, 0xA734F03057E677C9ULL, 0x0F062AAE9574A6E4ULL, 0x43C3E7E298FD666AULL, 
            0xBA327E1620B4737FULL, 0x5B5FC266590330D1ULL, 0x70F20C10CCF8FB8EULL, 0x16FF748E37DB1E48ULL
        },
        {
            0x300C1CEAFC76E5F3ULL, 0xC56AE16D4FB0DF52ULL, 0x7CF72F570F6211F5ULL, 0x34BC9020A930FAA0ULL, 
            0xAAB7C1E182B79C32ULL, 0x578B360A18E3F995ULL, 0xCAA94A41C9AF4C54ULL, 0xFCF31B5D68794199ULL, 
            0x707BBC6771243DCEULL, 0x412954A437AA718AULL, 0xEDFF977E3F076781ULL, 0x665A25877E2A4AE1ULL, 
            0x998223A654CF6DDAULL, 0xE508013854717382ULL, 0xAC99E35A3164365CULL, 0x1E684C628290D5D4ULL, 
            0xD5285812E34D8DCAULL, 0xFD88D8E4753ED670ULL, 0x4C78B67A20402933ULL, 0xF79DB1E77601EC4CULL, 
            0xAC0E8500909A9D46ULL, 0x616C4AB00739E119ULL, 0x2E390EAB85BB860AULL, 0x173B86835951D29DULL, 
            0x6EE67995ED27276CULL, 0x17661B3FC20C7587ULL, 0x9AF15E22D50DB54AULL, 0x5CB07291A92565ABULL, 
            0xE277770412E934DEULL, 0xDB63F182A5F3A62AULL, 0x49EB380C925E5AA6ULL, 0x7AD799DD9A4B62FEULL
        },
        {
            0x942690A32FF63600ULL, 0x77CD2E87831817D2ULL, 0x926D75623D3A1450ULL, 0x2AA638F465ED394EULL, 
            0xB58F5F26080A1923ULL, 0x1DB6D4C7D229AB5FULL, 0xB9CD9E25CA5DFDD0ULL, 0x0F35BE57C3CC614EULL, 
            0xBFF365333B481D4BULL, 0x66DED0D15C97FD3AULL, 0x732E80BB7D498C4AULL, 0x9ABE2199236A1A04ULL, 
            0x2A42C802480AC519ULL, 0x87F9B4366EDD509EULL, 0x9FEE261E8E34A2D9ULL, 0x5E37AA19F607FD35ULL, 
            0x8FFD3A31EB4BA881ULL, 0x8AAC87F16E14A56EULL, 0x63A2D6727F83317EULL, 0xC041D9B051A02E3AULL, 
            0x64BCEDA8FB5F583CULL, 0xFBCE7496890AC177ULL, 0x2E92A1D630D8A27CULL, 0xFC1752C352070465ULL, 
            0xDE47F1D15663C86EULL, 0xFC4FDE1D156632A8ULL, 0xBFD676B0F08FC78AULL, 0xC150396BAFB51137ULL, 
            0xDE2437F49475F1B8ULL, 0x26A1340A89696565ULL, 0x71DF6BBC75DEA4C6ULL, 0x76902EB38EABD0CAULL
        }
    },
    {
        {
            0x7634D9CF022EC893ULL, 0x48306899C9936F73ULL, 0xAAF46DBDF146FF4EULL, 0x5641A6732391B001ULL, 
            0xB95874AB60B397A3ULL, 0x2D4B67FAA67C6C21ULL, 0xFFCC12F2E4FB50B0ULL, 0x4154ABA517BB93C0ULL, 
            0x5F105F241067F137ULL, 0xB57335613E6EF709ULL, 0xFDA2E4B6682CC610ULL, 0xD3E10AC78AE4038CULL, 
            0x49E49520CE4CB554ULL, 0xD36A32E6E4627D44ULL, 0xF366C46D35848C66ULL, 0xA637D9BCE4E81C9CULL, 
            0x80ED2F9900B09ACAULL, 0x72F5FD339C009AB5ULL, 0x8EA661DAE6E1AFA9ULL, 0x5ACABF41666B93ACULL, 
            0x9351C53912EF5EA9ULL, 0x92282DF86238FA6DULL, 0x0860BB95199BBD3EULL, 0x1C707904C7166C9EULL, 
            0xFD0BFCCD8E19732BULL, 0x471A3286C78B3E3AULL, 0x2F06A47289E68137ULL, 0x62C02C4BA6BEC92AULL, 
            0x4084F477EB086646ULL, 0x594C0D0F52CFBAA5ULL, 0x46E16735EFE706F7ULL, 0x9CEBCCF5B767D17EULL
        },
        {
            0x32C2966FA0573714ULL, 0x28D54747C0499FAFULL, 0x2E7FD34BE783690CULL, 0xB8BF79B2A9352FEEULL, 
            0xE30E3BAF209A9101ULL, 0x65F6944155E2A888ULL, 0x176A62869ED942F6ULL, 0xA49C0DF1E5C8FBB1ULL, 
            0x17819817EC1C0AA8ULL, 0xCD45BB1FEC9937EAULL, 0xC222BDA7B9BE7813ULL, 0x5B0A6D641D20D515ULL, 
            0x3FD3BE6CB07994F8ULL, 0x6F594F67C969BC62ULL, 0xDCB960FBB0486858ULL, 0x4BFF1134DC79FFCCULL, 
            0xAB092CC8DBEC76D4ULL, 0xE8B9A5147713DAC8ULL, 0xBAA86E5AEFDED4E7ULL, 0x39FBFDF3D2D4EB80ULL, 
            0x6E5EAE7EE8E9237EULL, 0x6946338EB3FAF45FULL, 0x2F626C57C7670596ULL, 0xB96C6DA65835C704ULL, 
            0xF3B8D4050CC185DBULL, 0xCCBD712F7439F020ULL, 0x3B0388E30F9A9BBCULL, 0x3362ACA75D3B0426ULL, 
            0xB7AA3B42F49CE08AULL, 0xBFCF94BD4923FB3AULL, 0xC37DBA1BB97C60BFULL, 0x407BFD2F7A31EFDBULL
        },
        {
            0x94AA507D8953E9F1ULL, 0x0AFEE76B12602C04ULL, 0xF80E64FFD72D4B88ULL, 0xF13C91BF08227A15ULL, 
            0xF872F3A802F4C45BULL, 0x6B000E317F14F1FEULL, 0xABB154E18702DC13ULL, 0x9C47CC7EFF5FD9B4ULL, 
            0x51ACDFF4153F4286ULL, 0xBDB0F4EA36641DEAULL, 0x5ADBABF728BA9C11ULL, 0x06032539EE1E6C54ULL, 
            0x5DAE83DAE8273FB7ULL, 0x3F4256F67FD689B2ULL, 0x5B8C2D10D924F9EBULL, 0xAE5B3B99AD912B4DULL, 
            0xF1BB07F074F8C20BULL, 0x36405B43737BC127ULL, 0x0B516FE1443A5404ULL, 0xA9CB4863927976F4ULL, 
            0xD2EF3765CCBB83E7ULL, 0x9568CD0C1DCE1407ULL, 0xCBC0C2D54437AAC2ULL, 0x715D2ABB17AF95FAULL, 
            0x082C5149F643E5C2ULL, 0x6FE78663C3B28BE2ULL, 0xD157DAE6C95854FBULL, 0x1E71234843008E5AULL, 
            0x9F994F5C15188B41ULL, 0x8FCE815AF06496E8ULL, 0x5C8CEA159153F078ULL, 0x3B3F50F48A675545ULL
        },
        {
            0x94803E81A5F6795EULL, 0x4B3AD07532EB73D0ULL, 0x3A4C890B8F7B029CULL, 0xCD1017D7AEA197EFULL, 
            0xC0766BC41489B69FULL, 0x82CE9362B46620CFULL, 0xB051D137E90F6EBFULL, 0x01DC91937C7C1CE9ULL, 
            0x7755297827D11880ULL, 0x0369684323A6ACE3ULL, 0x785D8A59499B2D37ULL, 0xE954A99EFEB6C7A7ULL, 
            0x34BA57C839943ED1ULL, 0x2CD847AB84A1446FULL, 0x3B3912D829838441ULL, 0xE1A83FBE60DD4145ULL, 
            0x552CE848E41935DBULL, 0xD5FC41CA61CE89B2ULL, 0xACC624BC4319724CULL, 0xCDFE50D5CE311A61ULL, 
            0xBFACE8CCE92C135FULL, 0x08C37764A24EC453ULL, 0x775CE7746761C673ULL, 0x53568DD7B98FAB90ULL, 
            0x97F0157FD7978542ULL, 0x1A05EF0B65FC87ABULL, 0xEBC6F06BF641D49DULL, 0x23BDCCE8AEC0289AULL, 
            0xB8DE48F5B79CCB89ULL, 0x3B3A1014DC290B95ULL, 0xA88ADF8A5080CEAEULL, 0xA39FCEEFD0BCE6A9ULL
        },
        {
            0x4A341D67DAF84782ULL, 0x25C085D41B4DC919ULL, 0xA9CAF8046082D211ULL, 0x13082349E64A83B0ULL, 
            0xA3A8DAB460E38B69ULL, 0xB0167C78F0911956ULL, 0x64B2092660C3550DULL, 0x2808AE7A44EE8E5FULL, 
            0xA94A18D57F96FE52ULL, 0x8E9F2AC61BE341DEULL, 0x3F24F2364BEB4C54ULL, 0x463088AA2D61065EULL, 
            0xF212983E7C55249AULL, 0x6307599B947F8493ULL, 0x83BE6ECEBBBDFCDAULL, 0xF97683385A4393F8ULL, 
            0xDF33A15A3CB51F8FULL, 0x901845A2CCD4CB68ULL, 0x8568B1D9531BA417ULL, 0xE97975573C864D34ULL, 
            0x1A4B4904208A14C4ULL, 0x799C4586D75FD6D4ULL, 0x8A19FC12464396DFULL, 0x4991564C62443349ULL, 
            0x081F636BBB81DE6FULL, 0x6C966C7CFC8F3B82ULL, 0xB378655BDC9BA14CULL, 0x8A73401BB8593197ULL, 
            0xE41312E216B964EBULL, 0x169659F759307110ULL, 0xD6613D2F21C3AA44ULL, 0x9988079DEEB27333ULL
        },
        {
            0x8F2C82E485280440ULL, 0xCF059D2CC3E04001ULL, 0xE99A5C3355A5B550ULL, 0xE6D4335F64D959B7ULL, 
            0xC3902773F013361AULL, 0xFDBDA196DCA89EC2ULL, 0x30D67190A841D75EULL, 0xF3A94B718AAB500AULL, 
            0xC1C3922FA5E972EDULL, 0xED13D414DF591F6AULL, 0x2AC320EEF8DC1B70ULL, 0xECDABFFD3879BE20ULL, 
            0x6036633E11CB2C75ULL, 0x2D69382D17809EF8ULL, 0x01768CD281D3EA2AULL, 0xD8F6DD7E348F353FULL, 
            0xB8206707111F8187ULL, 0x724B264E3BA75286ULL, 0x96CFB1898338F2B4ULL, 0xEBB73694DE9AB472ULL, 
            0x781354BE05D5AB46ULL, 0x3044DB5723E307CBULL, 0xD05FF5D08B6C4B42ULL, 0x762F48681123B5E9ULL, 
            0x4139EDE1AE5944E6ULL, 0x13D9322A55F53CA8ULL, 0xDBE51395A5F725CBULL, 0x2603CA0F5D238F51ULL, 
            0x909AE5F323FCA828ULL, 0x7BBA24E362B87224ULL, 0x941BD34E18BD0C35ULL, 0xC627F9EF7DD02629ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Antares::kPhaseHConstants = {
    0x1CB87D0F9F2AF1BFULL,
    0x4ECCCFEACA3BD787ULL,
    0x31E95529AF757E2EULL,
    0x1CB87D0F9F2AF1BFULL,
    0x4ECCCFEACA3BD787ULL,
    0x31E95529AF757E2EULL,
    0x1C74D438CB7D0018ULL,
    0xA5642A6DADCB682DULL,
    0x28,
    0x75,
    0xFD,
    0x91,
    0x54,
    0xF6,
    0x8C,
    0x26
};

