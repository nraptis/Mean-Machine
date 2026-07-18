#include "TwistExpander_Naos.hpp"
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

TwistExpander_Naos::TwistExpander_Naos()
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

void TwistExpander_Naos::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xCE46DB08A89FF4A9ULL; std::uint64_t aIngress = 0x87A5C9E0CDD1B066ULL; std::uint64_t aCarry = 0x9D998ECB5E1A0448ULL;

    std::uint64_t aWandererA = 0xD0B15D3B3F8B4BC6ULL; std::uint64_t aWandererB = 0xEF8885514F99A845ULL; std::uint64_t aWandererC = 0xA800E3A936225D8DULL; std::uint64_t aWandererD = 0xC459731D5052BBE2ULL;
    std::uint64_t aWandererE = 0xBFA32FE6E6145F41ULL; std::uint64_t aWandererF = 0x96C470F5242ABE7FULL; std::uint64_t aWandererG = 0xA42B3A6DCD63EE33ULL; std::uint64_t aWandererH = 0xB219112E9C58EA2EULL;
    std::uint64_t aWandererI = 0xD670F2C3205A85B3ULL; std::uint64_t aWandererJ = 0xA6DD326E672419C6ULL; std::uint64_t aWandererK = 0xF0414E1A874D3170ULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 16463618824111584340U;
        aCarry = 10463809409016940955U;
        aWandererA = 14484630648412088243U;
        aWandererB = 17285231409847573051U;
        aWandererC = 9707577272856758806U;
        aWandererD = 12100211257143940635U;
        aWandererE = 17098213209245073441U;
        aWandererF = 9300584684339076362U;
        aWandererG = 14755701600192032300U;
        aWandererH = 16990128204205217730U;
        aWandererI = 15210518012946718509U;
        aWandererJ = 15045760023367659329U;
        aWandererK = 17708862060926460242U;
    TwistExpander_Naos_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Naos_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Naos_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Naos_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Naos_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Naos::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xA4E7C201C9946F34ULL; std::uint64_t aIngress = 0xC2A6692DE4B804F3ULL; std::uint64_t aCarry = 0x854638818EC27D2EULL;

    std::uint64_t aWandererA = 0xE1D1CE8FC6E72045ULL; std::uint64_t aWandererB = 0xF1A0AAC2F16FE2D6ULL; std::uint64_t aWandererC = 0x91F56558F2A3EA97ULL; std::uint64_t aWandererD = 0xC7502029CE1903C3ULL;
    std::uint64_t aWandererE = 0x913F2D87649D4DE1ULL; std::uint64_t aWandererF = 0xC75FFCB4576D4A1DULL; std::uint64_t aWandererG = 0xF0B33219D40AEA4CULL; std::uint64_t aWandererH = 0xDCBF257AD7F99EEDULL;
    std::uint64_t aWandererI = 0xC041F0C445776A89ULL; std::uint64_t aWandererJ = 0xA5D8DD667878244CULL; std::uint64_t aWandererK = 0x8CB44A5F4BB0F115ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 17139988881952124237U;
        aCarry = 13269246886663238541U;
        aWandererA = 17301757532174375375U;
        aWandererB = 14018729777520176964U;
        aWandererC = 16551339969996784262U;
        aWandererD = 16820403173221285846U;
        aWandererE = 12297136843853532645U;
        aWandererF = 12685358089116249941U;
        aWandererG = 14137908964257560012U;
        aWandererH = 12631409478487933631U;
        aWandererI = 14715225518658644755U;
        aWandererJ = 13565734145139541583U;
        aWandererK = 14204942462875509589U;
    TwistExpander_Naos_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Naos_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Naos_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Naos_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Naos::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xDE450DF58686D786ULL;
    std::uint64_t aIngress = 0xFE21AF19BAD238BFULL;
    std::uint64_t aCarry = 0xAEFDD399AD585447ULL;

    std::uint64_t aWandererA = 0xC0964476D1E86422ULL;
    std::uint64_t aWandererB = 0x9D4C5FBC3AC682EEULL;
    std::uint64_t aWandererC = 0xF0C8240944CEB394ULL;
    std::uint64_t aWandererD = 0xFFDC8B1050272D1AULL;
    std::uint64_t aWandererE = 0xF5C570AC227AA5A9ULL;
    std::uint64_t aWandererF = 0xF0731E06258E6488ULL;
    std::uint64_t aWandererG = 0x8E3211794B0F5ED5ULL;
    std::uint64_t aWandererH = 0xED49C79D7C384EB2ULL;
    std::uint64_t aWandererI = 0xE40B25C6A906DC4AULL;
    std::uint64_t aWandererJ = 0xEC41D3B08799C9FAULL;
    std::uint64_t aWandererK = 0x98A30C059768601CULL;

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
    TwistExpander_Naos_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Naos_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Naos_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Naos_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Naos_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Naos_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Naos_Arx::Seed_H(pWorkSpace,
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
    TwistExpander_Naos_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Naos_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Naos_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 23 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1796 / 1984 (90.52%)
// Total distance from earlier candidates: 39954
void TwistExpander_Naos::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1899U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 985U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 972U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1190U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1623U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1394U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 291U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1292U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1254U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1680U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1832U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 423U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1085U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1072U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1674U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 989U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 673U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1220U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 889U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 770U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1064U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 689U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 718U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1042U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 705U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 699U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1436U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 446U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2010U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1499U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1128U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 700U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1922U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1299U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1897U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 411U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1958U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1829U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 2001U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 467U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1008U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1986U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 640U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1491U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 502U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 760U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 955U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 81U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 418U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1106U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1586U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1638U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 246U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 476U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 682U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1721U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 314U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 279U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1328U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 768U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1696U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 149U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 403U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1192U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1628U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1702U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 316U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 469U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1441U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1141U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1661U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1795U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 944U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1593U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 102U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 563U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 232U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 913U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1136U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1507U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 360U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1847U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1789U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1228U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1102U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 244U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 525U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 234U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 968U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 970U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 902U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1401U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1777U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1743U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 849U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 939U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 900U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1854U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 662U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 91U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1455U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 216U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 732U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 36U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1813U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2043U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 638U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 300U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 2018U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1901U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1234U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 253U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1309U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1914U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1842U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 302U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 911U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 826U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 996U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 143U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 369U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 668U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1184U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1083U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1238U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 559U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 272U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 901U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Naos::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0xFD5405F03184FC05ULL; std::uint64_t aIngress = 0xF240BA896014642FULL; std::uint64_t aCarry = 0xAFB6E5CA237110C6ULL;

    std::uint64_t aWandererA = 0xB5CE98630DA77CD9ULL; std::uint64_t aWandererB = 0xC0DAB240AD2ECC12ULL; std::uint64_t aWandererC = 0x8D821E9E7F733D46ULL; std::uint64_t aWandererD = 0x9A88ACB44A88199AULL;
    std::uint64_t aWandererE = 0xACF80F3012ADA0E9ULL; std::uint64_t aWandererF = 0x9D0C04642AE61832ULL; std::uint64_t aWandererG = 0xBC5E5351A49DD59DULL; std::uint64_t aWandererH = 0xC81E376188AEE0DBULL;
    std::uint64_t aWandererI = 0x8C6853A6E939280EULL; std::uint64_t aWandererJ = 0xF0E8ED664EB2D7C3ULL; std::uint64_t aWandererK = 0xC16AA94437FFA830ULL;

    // [seed]
        aPrevious = 9478387082725341213U;
        aCarry = 14896678778880882311U;
        aWandererA = 9806662727867313770U;
        aWandererB = 15164620899019194306U;
        aWandererC = 9688347173412752891U;
        aWandererD = 16334793802044941602U;
        aWandererE = 17408230011028484010U;
        aWandererF = 16924751345203101466U;
        aWandererG = 16315725037514314050U;
        aWandererH = 13176018854237122357U;
        aWandererI = 16081683337789986062U;
        aWandererJ = 17050102078419389731U;
        aWandererK = 16517276748774564103U;
    TwistExpander_Naos_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Naos_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Naos_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Naos_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Naos_Arx::Twist_E(pWorkSpace,
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
    TwistExpander_Naos_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Naos_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Naos_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Naos_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 23 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11931; nearest pair: 480 / 674
void TwistExpander_Naos::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 429U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7839U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1116U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 918U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 2675U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1703U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5073U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6061U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 4016U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 3450U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 4498U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2458U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 7638U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2513U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5772U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3910U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 332U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1491U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 344U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 865U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 291U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1994U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1605U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 492U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 165U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1343U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1462U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1555U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1074U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 596U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 53U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1855U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1349U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 1036U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 222U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 984U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 23 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 11942; nearest pair: 457 / 674
void TwistExpander_Naos::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3746U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 992U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 3248U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2475U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6647U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 5120U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7773U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 550U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 574U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2269U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5085U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 4881U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 301U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2369U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 7132U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6121U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1690U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1826U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1752U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1020U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1102U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1506U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1822U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1538U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
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
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 660U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1453U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1357U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1475U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1786U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 44U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 922U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1016U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1179U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 180U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1742U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 1594U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Naos::kPhaseASalts = {
    {
        {
            0x281D660E6EB87FE5ULL, 0x719BA14372A98DBEULL, 0x84643876CC26676AULL, 0x4729282B465B9AE4ULL, 
            0x562C160398B75380ULL, 0x0FDC7DBFAF4F030DULL, 0x57111C962A8577EDULL, 0xE0B9F1232F87FD84ULL, 
            0xA851BBCC4688C393ULL, 0xD3242CC5E4585CC1ULL, 0x5F978E0B60D7881EULL, 0x6B2FD5F9FCFDC6C1ULL, 
            0xBABA5D80A74401D1ULL, 0xE5FD56BBB0F3C0CCULL, 0xC18646A486A6B1C0ULL, 0x56F2EC49E28DDF25ULL, 
            0xC63D2082E44599BEULL, 0xCFFA342A7528B46DULL, 0xC78AAA30D7AED864ULL, 0xA618085C04E97D4AULL, 
            0xA8E66CE11E955F1FULL, 0x45132CE6F6C8088FULL, 0x428C3977DBE1BB9FULL, 0x6919A7EC1EF920D4ULL, 
            0xFC1FBF6D26E3AF0BULL, 0x269BBE2CFE310CCDULL, 0xAE7A0F2F1382559AULL, 0x93EB86007B017FF1ULL, 
            0x6BA792B4AAD02136ULL, 0xD497CFDBBEB8D74DULL, 0xBE2FD13295465CD4ULL, 0xEB19A26F5A70318CULL
        },
        {
            0x8BB72E8BEEA66FEAULL, 0x11E25BA53319D560ULL, 0xA53C34F8C2E23B13ULL, 0x33111D199F69A16DULL, 
            0xCA740EB361B2C712ULL, 0xA813EA7A3684B094ULL, 0x7338E7EB7202695DULL, 0x22EDD8175F5ABC30ULL, 
            0x8B27A7465BFEA81EULL, 0x16797DBC1EF7B441ULL, 0xE1227F96F43E169EULL, 0x3F3A60D45F769FCFULL, 
            0xBFEE28A4A657EDB9ULL, 0x3215342FA3D468C7ULL, 0x0C7970079AE89BB5ULL, 0x023295D432381D5FULL, 
            0xF57F9BD714FF4634ULL, 0x054B5094946E76EEULL, 0x46B2FFA3CAFBF918ULL, 0xEC78AD3022560E7EULL, 
            0x88B50FD1C5378B45ULL, 0x98C7EA9C94BBCF72ULL, 0xF87B0E8214B21040ULL, 0xD2F08AA93DB4240BULL, 
            0xD43B6F1F12478C53ULL, 0x778ED7C02F30A98AULL, 0xD183E159433F1D28ULL, 0xCE34707D3C93CBD1ULL, 
            0x03C516F6B5F7529AULL, 0x38DD43BAF2C428E5ULL, 0x5BFA30F80FFF75B7ULL, 0x6769E15B75899004ULL
        },
        {
            0x347C06E4751C43ECULL, 0x60581D5805AB65FFULL, 0xBC9BDC5F35985364ULL, 0xD7E0CBC6B9791ABEULL, 
            0xA1937CCDD8170DBCULL, 0x2FA53726CE888D4EULL, 0x1A2D809749B89CC0ULL, 0x5EB8A16D12152592ULL, 
            0x7937960CDF4919F9ULL, 0x1186A13170AD2721ULL, 0xFABA6D71BF15BE8EULL, 0x2F73853B2125DA2FULL, 
            0x8F9074A38F611B80ULL, 0xF440C9F5709BA191ULL, 0x9E34FFFDB36CA7DCULL, 0x54C3CB830E0CFC5AULL, 
            0x59AA7EE675BC8EFAULL, 0x166438C516BE3FE7ULL, 0xEB47610A9925E360ULL, 0xE5227EF2D7711F7DULL, 
            0x20195123E685ACD9ULL, 0x8665F37A7CB62A1FULL, 0xAF26B6BE507543ABULL, 0x324FBE7F4002E037ULL, 
            0xFA9B4F7BF6158307ULL, 0x61978E3742B4D72DULL, 0x5B62D5E1514449ADULL, 0x50C491F200E02014ULL, 
            0xD5F8635FB565C13DULL, 0x601845C8A5D81B16ULL, 0x220F072E936F3B71ULL, 0x14DA1F715F9C94CEULL
        },
        {
            0xA1CC2CA9263E81AFULL, 0xA8E2EEC7A3FD0EF8ULL, 0xC2DAE75A43F1B3B1ULL, 0x2FCDAF51CC33E32CULL, 
            0x252AAF04C6620CC9ULL, 0x2F890A0FB0084EA4ULL, 0xA0C3540E2C4BDD89ULL, 0x2CA197DFFC99E3D9ULL, 
            0xEEFB07FFFFB2BD39ULL, 0xA0CE6D52A8CD62A4ULL, 0xE707471B64B5EF5DULL, 0xA141F5BBA927FB12ULL, 
            0x0102BA41875298F2ULL, 0x7A44E3099FF5C84DULL, 0x79A80D34D80ADF70ULL, 0xC617B995B67255D7ULL, 
            0x53F02D1406AD643CULL, 0xE5F77353B4277A1CULL, 0xF895808FAA3BC30BULL, 0x81C97DF438477665ULL, 
            0xB09614094D68C719ULL, 0xC3807F95585419D1ULL, 0xC7284D7E086DBCEDULL, 0x785B745B9AAEFB45ULL, 
            0x31417449268045D6ULL, 0xCA49BE6DD698C72AULL, 0xE368D59892281E86ULL, 0xFA932CE353EF3F13ULL, 
            0x3DB0EE94FB21FFFCULL, 0x45773A942877D94DULL, 0xA366DA68B0FA581FULL, 0xDDF325EC63981AB4ULL
        },
        {
            0x4D241BA3CA97472BULL, 0xE8643DE86364859BULL, 0x2FE71F2996502D26ULL, 0x722DB43E51CE7758ULL, 
            0x7EF1A29CD293F06CULL, 0xFFA84C92B3EE0B15ULL, 0x8F00CE069ED8E19BULL, 0xEE4D827530B7DDDDULL, 
            0xF77C7CBB1BEE5309ULL, 0xFA201A9EA5EAD4DFULL, 0x83C50179B5F0B5E9ULL, 0x078CC07B7B7C0C73ULL, 
            0xE2E643E5F8707421ULL, 0x2DADCBCD3000B1B6ULL, 0x27D46E2C6EB3D27FULL, 0x7F20FAD09053D66EULL, 
            0x2589936477565C0AULL, 0xE938FBDB90B95943ULL, 0xB8FB9A9C38E23C88ULL, 0x57316EC00179D635ULL, 
            0x3E29883FE4142EB4ULL, 0x72237D4EFE675826ULL, 0xB7AC996D53E40712ULL, 0xBC26AB056B29110DULL, 
            0x887273E4ADBCD5CCULL, 0x3B8723DE62EC88B8ULL, 0x0F1B8AC998A2FA7EULL, 0x2D8780CF3EA4FDE3ULL, 
            0x421F30F5F434CDB0ULL, 0xAC11851D5655BD0EULL, 0x5CCA9991B3F815F7ULL, 0x97C98FD615E7A1E8ULL
        },
        {
            0xF3061D4D13966765ULL, 0x7EC676BCACB67DA3ULL, 0x7F106D9B91514311ULL, 0xA0F6B048D9AA2092ULL, 
            0xEA2C951B13BD6F27ULL, 0xAE65AA22FCA48D15ULL, 0x12CA073833F331FFULL, 0x4FEA01541E7543D0ULL, 
            0xCEF962A180C5898AULL, 0x33B7C0913BC682A9ULL, 0x559C85CE82324793ULL, 0xDD869418B3B6AC88ULL, 
            0x9DD5EC02EF5AF5C1ULL, 0x0550CBC1BDFE0FDDULL, 0x0D4793779FAC1AC9ULL, 0x1842F145E0D1335AULL, 
            0x12CB11FC67602448ULL, 0x1B11F1899C6B88DFULL, 0x28566D1E62E989ECULL, 0x1F4162E750F994E8ULL, 
            0x5CA6CC9A24B02371ULL, 0xD89329C1E4191B73ULL, 0x5FD698F28C4AEB97ULL, 0x539AD5CED6C9A08CULL, 
            0x1DB93DB6556D0ABFULL, 0x987DBF122C2796EBULL, 0x5ED39E3FAC4DF2D5ULL, 0x5A8FA4806DA00929ULL, 
            0xF528E4C624C25CA5ULL, 0x8560E75D8C059A4FULL, 0x00489270DC111051ULL, 0xEC85A4F3788168C9ULL
        }
    },
    {
        {
            0xFDB0BA4456655057ULL, 0x4BB6911C2F90E050ULL, 0x7DAE619DCD5F45F6ULL, 0xEB4D5ACAD7CC8A55ULL, 
            0x02B60FA48A0818F0ULL, 0xBB2138D27D9BD799ULL, 0xC22D9F7C49AE3ED9ULL, 0xFBDBBD5ED1F82E5BULL, 
            0xB7302F967A85D9E7ULL, 0xD8B430441025324EULL, 0x1D92BBBCEFDA44EFULL, 0xFEBF15E2DF8ED327ULL, 
            0x378DF8197E41BEBAULL, 0x6665A98ED03A3CA4ULL, 0xFCBA7984C9817EC6ULL, 0x813A021579FF1970ULL, 
            0xC7BE2974FB6C6916ULL, 0x14626D57BEBA6DCEULL, 0xBA34BB92783CDF94ULL, 0x3274E07A320CEF90ULL, 
            0xCB5BD37EDF67077BULL, 0x64C821F914674764ULL, 0x567F91F163EBB450ULL, 0xA52B5F0934200292ULL, 
            0x91291299F726978FULL, 0x5B831ABCF9598DC3ULL, 0x296C73B06C71F320ULL, 0x91AF621B9011E240ULL, 
            0x7DDA1DC576198B04ULL, 0xF9A914E7FEFAC353ULL, 0x04883E76243D3550ULL, 0x8C66E8AA79C2854EULL
        },
        {
            0x6DEB5F0177B192C8ULL, 0x18B4D8395E927D26ULL, 0xCE3FA1804C3C8D56ULL, 0xAA04AFBD18C26699ULL, 
            0xB5DDC449347F412EULL, 0x99203CB904BE2C49ULL, 0x5CA1C4707AB427D9ULL, 0xBC2C3802F390C738ULL, 
            0x2B4E5D6F22571466ULL, 0x1BECEB2892CC7EA6ULL, 0xAC8541B6F7B4A48AULL, 0x14735A6DDC36001EULL, 
            0xC99EE9209679024BULL, 0x7E8FFB46E94F0FE6ULL, 0x0BBB6B039D17FB81ULL, 0xDE7EC5A327AA5D2FULL, 
            0x6D24E6F426F756CFULL, 0xADD94C78E99B895AULL, 0x99E078F2300B269EULL, 0xBF0F4E0A84C2A4BCULL, 
            0x86B55F080F176D57ULL, 0xF2BF2FF229382F48ULL, 0x62F3C696959630E7ULL, 0xFB84426CF64B286EULL, 
            0xC69037A8E519B880ULL, 0x6E1096DC2B587E06ULL, 0x382AE248ACC41524ULL, 0xE19680568FD5F05FULL, 
            0xA75A1D67B65046D2ULL, 0x15E8D3EE3E4E21D8ULL, 0x02BF6AB63548E2D1ULL, 0xE23F1C28D783C3B0ULL
        },
        {
            0xA92274FA4B4D98A7ULL, 0xB4065B8F8F056212ULL, 0x73DAE759790519A4ULL, 0x76159E515E15680AULL, 
            0xF017658252D51ABDULL, 0x470CD830F12754ECULL, 0xF4F9B5BCF31BC2ECULL, 0x8E2AC1BD01B7C770ULL, 
            0x7E73E886BE077B66ULL, 0x0510A47F7FE0A37AULL, 0xF3B94065E6EF00A4ULL, 0x9877E17707CB537EULL, 
            0xF76ED0CC238E08D2ULL, 0x30010871DB0A50D6ULL, 0x878BA1843FB3C99FULL, 0x8F809F4C271DC50EULL, 
            0xA35AD9BA04D587D8ULL, 0x36740F33B7C1477CULL, 0x1BF2AB1FC9156813ULL, 0xE8262B8DD5B32101ULL, 
            0x2D7D7620949F6A07ULL, 0x5D2782449D27A6E5ULL, 0xEC8265ABA6ABDECBULL, 0x413B1250D775125EULL, 
            0xCCBE179350192062ULL, 0x1DBFE4CC6BAC64EFULL, 0x6A34C8BACC8114CEULL, 0xB522C95210FF7377ULL, 
            0x08521C37A85617BEULL, 0x9910E510801CB044ULL, 0x933564AC4A19559DULL, 0xAF92758CF50EF32DULL
        },
        {
            0xB28454385991D1A6ULL, 0x4BDE0BC0814625AAULL, 0x886BBFFB5C9B6953ULL, 0x96A8C90E09BECE09ULL, 
            0x9AAD1A6A2FF12B6DULL, 0xA57538E530376A26ULL, 0xC55651AA369F42F7ULL, 0x078733423230C896ULL, 
            0x248CE21DCD73E183ULL, 0x475F06E28B96AEE3ULL, 0xAA2CE813F8ABA32AULL, 0x0D93A3E59D9D71C4ULL, 
            0x3090F5C14D546D51ULL, 0x3F258125200732A4ULL, 0x05D0FC6DA4518132ULL, 0x3745CAB6A058AE34ULL, 
            0xB7147E2E0986DB97ULL, 0x362CFA4CE14B43E9ULL, 0xF61EFA9F186370B9ULL, 0x3E0263BD49CCF75AULL, 
            0xC87C519037BA225BULL, 0xF60EE70EE07BB964ULL, 0x7ACA21DE4688E7BDULL, 0xA9F47B159218592CULL, 
            0xB640507844E2037CULL, 0x3F36A1BDC3D35B65ULL, 0xC0E50F26D7CF5AD4ULL, 0xB19AF36490104048ULL, 
            0xA588F36D028D1D41ULL, 0x136D1680C747FC28ULL, 0xFEC994EF4DC93D28ULL, 0xFEA81D1C97E09D48ULL
        },
        {
            0xC0967A9F12E84EBBULL, 0x1BC5566BD41CA19CULL, 0xFC70BD313D48AC16ULL, 0xF1E06DB22E0E70CFULL, 
            0x9520344A8B373D65ULL, 0x71CA7B8FCD105208ULL, 0xC4B59381C02C3E37ULL, 0x61E82E0E0CFDCD42ULL, 
            0x41518C0105927F95ULL, 0x8CEC3B0523D5BBCAULL, 0x8400926103A76D0DULL, 0x696F9935A14BDF39ULL, 
            0xE10D9B43EE6F1280ULL, 0x7B60F36F328202DEULL, 0xDB4AA73A17C17491ULL, 0x9C558C7A678C7C76ULL, 
            0x7B138B433A2B62ACULL, 0x28F297D10013F151ULL, 0xCE7FABC35E89B07FULL, 0x6AA335DB7BF9EF3BULL, 
            0xA1E3287D85653C1DULL, 0x50DA03B81D873AA4ULL, 0x31DAE6C8D5E36D04ULL, 0x1BC5E11F47B25DB4ULL, 
            0x4771950E3F7D27D1ULL, 0x7D17AC83964C1D6FULL, 0x5D170A6EFE8DC3A4ULL, 0x4D62DEAD682C87A8ULL, 
            0x0FFE28F7E5E4FF00ULL, 0x030B259EFCDE6328ULL, 0x8DA4B57B2C28C21EULL, 0xD02A278F080A3AA6ULL
        },
        {
            0xB69105C378E61EEDULL, 0xDBCE8387B415EF9FULL, 0x0EA5A79B139141EFULL, 0xA6A016881458CC3DULL, 
            0xBD9654BB03268770ULL, 0x5C2A3FAB00154C00ULL, 0xA9AB3D3C956F6348ULL, 0xAAF58E6116D84A56ULL, 
            0x8125E434788D1292ULL, 0x26DED1B05DDEB6DCULL, 0x86C1F492B2819A3EULL, 0xAE3DB0196EBDA5BDULL, 
            0xCD1E44A651E79723ULL, 0x6A137996B221DBF2ULL, 0xB095D4198B1C45C1ULL, 0xF7E72446FD11D93DULL, 
            0x93BA2A0C83ACB17DULL, 0x06F31C456C44F9B6ULL, 0x7A33419160A39E7BULL, 0x588B33CB4E353849ULL, 
            0x4741AFAF3D0B581CULL, 0x6C29252E52C0B0D9ULL, 0x36658335E48913D0ULL, 0xF65076096AF4D9D9ULL, 
            0x91C499FD388933BAULL, 0x96F773A9F8E1B5D9ULL, 0x8CC14777E63614C1ULL, 0x6465974DF3B94155ULL, 
            0x7729A817F38C5139ULL, 0x81A726E4A67F753AULL, 0x0EE8C820BFBE3C19ULL, 0xF7179C0C16F89C55ULL
        }
    },
    {
        {
            0x2FE6DA197ED8817BULL, 0xB6401537103F003AULL, 0x605B18CDB15C9854ULL, 0x15A4EAF67E7A20A0ULL, 
            0xAC5244B6E40919D7ULL, 0x0DEAB8E1972B5F8BULL, 0x3C810113B78E1EACULL, 0x606C0F6D2C69C609ULL, 
            0xFD961115873E5290ULL, 0x345549B15A8CA159ULL, 0xF4BF634D6E0649BDULL, 0x49EF4BDF1A58C28AULL, 
            0xB07E977FD807099CULL, 0x0C4044B8A86BFA10ULL, 0x62940546D6395E35ULL, 0x72D1B751BAD554CEULL, 
            0xCC4D824EB49A0186ULL, 0xE785C38E685A6276ULL, 0xD38B7895055FCAC4ULL, 0x05E26B352C2020C8ULL, 
            0x9D34DE0247EF775AULL, 0xC899D924B09188BAULL, 0xF618ED923F5BB251ULL, 0x3DA2D7937CFDAECAULL, 
            0x7149378D69F9DBA3ULL, 0xB5BFD142EA516728ULL, 0x5EB5E5949AF9058CULL, 0x7CBAC0069420700BULL, 
            0xCB8922525DC531EDULL, 0xA26264BA206F6B20ULL, 0x9696287A63BB66CCULL, 0xE955AC8EFFBA62B6ULL
        },
        {
            0xC26311D83A77DD57ULL, 0x8A28A94E8EA2571AULL, 0xC951219B48CCD7D7ULL, 0x704A9B9DB2D045FAULL, 
            0x8A59EAA65960F69CULL, 0x2D646AC4136F2ECAULL, 0xCCB279AF83E1D4E4ULL, 0x9AFA19D95C05A028ULL, 
            0xD5FB33EB55C301F3ULL, 0xC17961903C8101C0ULL, 0xD11586210A7C73A4ULL, 0x48B128D1F2BAE14EULL, 
            0x0BB13F322B668245ULL, 0x449E820CCEDB4049ULL, 0x0719954B30E223ABULL, 0x1283DA88A0D9CB53ULL, 
            0x17645C9071D28AC6ULL, 0x3A66C42184054F44ULL, 0xDC754334BDC26C13ULL, 0xA0C8DB3DFB42B3E3ULL, 
            0x0B561E8190255E43ULL, 0x7808A823EF3B3344ULL, 0xBC5513D8A69005B6ULL, 0x6D97F2F4D8049BBBULL, 
            0xFF2491DB6516AE76ULL, 0x5EC49D23C712DC39ULL, 0x54265A8C50F6584FULL, 0x0387D46C5CDB84CCULL, 
            0xAB662A05A1BE75A2ULL, 0xEC312FB965533AAFULL, 0xC4B73FE233EDE9E3ULL, 0xAA59DCDBDC97625BULL
        },
        {
            0x22D2DA68B6E99F63ULL, 0x21F54F753AE8B025ULL, 0xF13CCBDD342C23E4ULL, 0x0045EF6976B250F9ULL, 
            0xB4A22744FA13805FULL, 0x004430CCD9F23CD5ULL, 0xFEB38714B4AACD0CULL, 0xED59C6EBE770F025ULL, 
            0xC5BFC14A395A2DA5ULL, 0x157290EC7EE04215ULL, 0x3294F9E49630E4BFULL, 0xCB247D230783282DULL, 
            0x153053318D049F6DULL, 0xA2E236689B98D53DULL, 0xD89B1A8B0E28C217ULL, 0x1851FF5D59FA055BULL, 
            0x8BB196EE13FF0D57ULL, 0xCFECF342BD0A51E7ULL, 0xC2B9CC980FE3EBA3ULL, 0x844A365CBA49D6AFULL, 
            0x37818BB67F993C3FULL, 0xD4C6DFD84FAA3BACULL, 0x67F93F924270FDA5ULL, 0x8FFAC740F4000A3CULL, 
            0x13399EDC75EA3011ULL, 0xC3666C8073CB762AULL, 0x3FFD0A3691528F47ULL, 0x08A1C3D246379F82ULL, 
            0xFC888FCB9628262FULL, 0x763684143D2DCF5AULL, 0xDC958B858C4670F9ULL, 0x00E7647FC3EFC457ULL
        },
        {
            0x9FE5CC18DE6334EDULL, 0xD5671C2B42AB4743ULL, 0xB9031CBF1105D89BULL, 0x07420F8BDA6F2626ULL, 
            0xEEAAB0C1337CEC28ULL, 0x20D4277E7F98D55FULL, 0xA562520DBF3E940CULL, 0x504E9A900C0F5ACEULL, 
            0x6D622CF0107166F5ULL, 0x24A913D52F8F267CULL, 0x84DFFEFB48E41BE5ULL, 0xE411093BAC4FB381ULL, 
            0xD6C7EC1DDCB14077ULL, 0xA95282AD04A70423ULL, 0x946BE6585FC5C941ULL, 0x6C5769FBCDD5CDAAULL, 
            0x43C3BEF4A2417248ULL, 0x9F177B7F78CF9C90ULL, 0xACACC1360896EB03ULL, 0xF17D0C5EE4DA66EAULL, 
            0x3F43423E4E64EBE6ULL, 0x6CE44FE70A7E3385ULL, 0x6951E04B4110259AULL, 0xB73635853D3C6FFAULL, 
            0x8F1049B14868CA66ULL, 0x91E99DBFF024770BULL, 0x912BD9DE53CC4D03ULL, 0xABB342BBAAEC9226ULL, 
            0xBEF929BEF2C1C1F1ULL, 0xCF66FBB51F0BEE1CULL, 0x1F7B9975A3B4A8D8ULL, 0x4A5EE8235F4B9E22ULL
        },
        {
            0xAC034180B774F422ULL, 0x04FF7AF06E00AB01ULL, 0xCB98A6374A7EDB81ULL, 0x0E3C95A2B6675483ULL, 
            0xDBB00D67AD775A39ULL, 0x4E462F673E644DAAULL, 0x0F7651E0C08F8B21ULL, 0x443B5DEF8398EE09ULL, 
            0x2A97C45D02FD9409ULL, 0xE04077D60517C39AULL, 0xB5C7061D15C8EAD2ULL, 0x23D14ACB493356E8ULL, 
            0xBEF8B746F0791649ULL, 0xC7D734E32ED8EB4DULL, 0x0D7655A53E722074ULL, 0xDD82F5B114979FBAULL, 
            0xF46C4C1D7E55EE0BULL, 0x3FAFC51DCBED586BULL, 0xEDB8851B2AC996F4ULL, 0x90E6DFB85B4E6D4DULL, 
            0xD4C75D6AC14002E9ULL, 0x1BE1BA9C104E47DFULL, 0x815AAEEA046B6E85ULL, 0x1E05D71E180F994CULL, 
            0xF64E60E77412CFE0ULL, 0xFA7DE816284E9A74ULL, 0xFE3DF9ADD27F3B52ULL, 0xBE86FCB0E4F98916ULL, 
            0x7F7A2D198EEC3F7CULL, 0xDF982F5B87FE6488ULL, 0x654C6204C14DCF21ULL, 0xEA96306825B3006BULL
        },
        {
            0xA44A0CF2C0BD1067ULL, 0xE15DD98E37DB9B6BULL, 0x835CC4F321506A91ULL, 0x8F6B3FD4F318E6BDULL, 
            0x18B0FDA3CB969B5EULL, 0xCDCFE4B5EBA3DEFEULL, 0xEAFBEF670A635554ULL, 0xABAAC6CD9D581FC4ULL, 
            0xC60D974E0EF5D841ULL, 0xAA0B27C82AEED26CULL, 0x7F00597C3C89D110ULL, 0x2F1D29C4992B4E16ULL, 
            0x81FBAF615F5C54C0ULL, 0x802AB09CD4A1027AULL, 0xA79A0271634FED62ULL, 0xADFF958B482F0FE8ULL, 
            0x69E99B4AC56512E7ULL, 0xD72C2E21D49F3D4FULL, 0x7ECFE8B08D721C92ULL, 0xB5A62974EA9B512FULL, 
            0x88B2C6FF50407EDEULL, 0x85A2B5CE49AAD25DULL, 0x197D1827BEAB13F8ULL, 0x713032BA679ADA18ULL, 
            0x5B78B35817E8FF33ULL, 0x5ADC075429BA2C83ULL, 0x0827381BE3F0876FULL, 0x335C0040CDA02CA8ULL, 
            0xD72E7679DFFE43B3ULL, 0x80AEF8FB56A97366ULL, 0x74E454ABE17CF66EULL, 0x363829E2DB69DA73ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseAConstants = {
    0x98DE41503483ED25ULL,
    0x38A792F7F5B41C33ULL,
    0x92D303875A77E0BFULL,
    0x98DE41503483ED25ULL,
    0x38A792F7F5B41C33ULL,
    0x92D303875A77E0BFULL,
    0xCB16E876E4B2281FULL,
    0x1789D8B43E32AC20ULL,
    0x22,
    0xE9,
    0xDF,
    0x71,
    0x3F,
    0x72,
    0x2C,
    0xA3
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseBSalts = {
    {
        {
            0xA95803A708BFA4B3ULL, 0x10DE91B495D14C23ULL, 0x467082F8787FE459ULL, 0x4D50FA2C657E5BA4ULL, 
            0xA581B61927042EB7ULL, 0xD4D020E8F2E4FD2BULL, 0x91612BF3355A00F1ULL, 0x51906DC2F20CF6EAULL, 
            0xA570A56E5B262EF4ULL, 0x8DAF6F5D2D97375EULL, 0xAAD24939AF5034F1ULL, 0x5EF18433AEC9F602ULL, 
            0x21A4DEA2EAD2D4C5ULL, 0xA706A3E1C34E1A19ULL, 0x2C06918C89D54562ULL, 0x7706D33008B9BC0CULL, 
            0xC79BC72139EFE12CULL, 0x900E8919B26DA407ULL, 0x57AD0897434E25C8ULL, 0xE300495C03CF8F13ULL, 
            0x9E756AA8060208F2ULL, 0x7D9B509B6AB40816ULL, 0xDBE2EF4225B46E35ULL, 0x00D9F4E167ABF792ULL, 
            0x8EEF24C3CE5BC0C4ULL, 0x5F2DC78FC7D3D35FULL, 0xECDCFA65260BBD87ULL, 0xC2DAF0581D5F689CULL, 
            0x2CAAEC3DA87E271DULL, 0xB69266478FFCFC6DULL, 0xFA57FBE84AB936B4ULL, 0x24ACBB2BDDB6E051ULL
        },
        {
            0x94F6EB9542FCCECFULL, 0xECAAA82964127717ULL, 0x06EF21A9D55FAF4CULL, 0xA32647019EF3E6DDULL, 
            0x034580A5877CC437ULL, 0xD0B52BDE55BF0BB1ULL, 0x6B3C062B816BC4ACULL, 0x8F1723F8570ED473ULL, 
            0x25EBF7E773734075ULL, 0x82306A44322F3B27ULL, 0xEBD0905EDC406123ULL, 0x608079889181F118ULL, 
            0xE2DF7525948F4269ULL, 0xDDD3788CE2799FCFULL, 0x7B20337146467794ULL, 0x7BD7581718C966F6ULL, 
            0x8C4D84751E1902F8ULL, 0x013350B7D4C25048ULL, 0xAE87F038CDE10EF3ULL, 0xAD91822C10FE5BDBULL, 
            0x0AADF4E56338D182ULL, 0xCDB8367F579F3B4FULL, 0x6C472BD8F998B9C6ULL, 0x5CAB66BA0D8BDCCBULL, 
            0xBE1D96EF7F6D77D5ULL, 0x24B11A79A45E7B2DULL, 0xE268FB3E2318D75DULL, 0xDE37E3C92C314945ULL, 
            0x8E02D6DE87F1E658ULL, 0x600C4313AB4532F4ULL, 0xD64FFAB1F9FF0B8AULL, 0x635A5D077A38747EULL
        },
        {
            0xE67817A8EF9B18EAULL, 0xB99B808EED09894BULL, 0xB8D3DA8707ECB39DULL, 0xDFBE641DD9C18E34ULL, 
            0x3E137CF10AEECC79ULL, 0x51D36BD5EF3A2912ULL, 0x4A9B079D41E998A3ULL, 0x709927ED78A06499ULL, 
            0xF480C9227B73F0CFULL, 0x281C7C4DDE3AB27EULL, 0xEFAD6B63FAD8D121ULL, 0x1DB39C3D021C842DULL, 
            0xE1EA2FD470B465F1ULL, 0x70CF37354F1C7782ULL, 0xB1DEDF4AC8B37D9CULL, 0x2B5747EFAEE96967ULL, 
            0xB68D0AC8B1C0D8B1ULL, 0x3EE1CDDC60747E1EULL, 0xBDF4766D3B133D15ULL, 0xC1F2E59C578DBC40ULL, 
            0x1940A5CAE6A99F2CULL, 0x57E0EA3C81181C1AULL, 0x955DCF858B1A6A8CULL, 0x2902867B652E741BULL, 
            0xC46C96585C4E6427ULL, 0xFA957D5958EF33ADULL, 0x8C56728C32337C9DULL, 0x6370EA3CB1E8F992ULL, 
            0xEBF9A5DE94AE36C7ULL, 0x1429CD80D0382533ULL, 0x60FC70D4BE61D3C6ULL, 0x8D1F5E3BE949EB0AULL
        },
        {
            0x2A0213B470E8571EULL, 0xA268882A40E5A3B3ULL, 0x9C1926793C0A440CULL, 0x649B00F96DCE4C32ULL, 
            0x88BB8E804B57BCEBULL, 0x2C611764E226CB08ULL, 0x1139769D0C9F20C3ULL, 0xCE91D175827A7B05ULL, 
            0x8A6ABEF96FFCF9E7ULL, 0xEF983D634E57472CULL, 0x7CBC1431AEB4BB3CULL, 0x1B2B04A5E9CDB06EULL, 
            0x08A5963BD05016ACULL, 0x360F1211399DFDFBULL, 0xB0782495F07D3C93ULL, 0x3420ECA1751A9F93ULL, 
            0x3BF44D088E5FF869ULL, 0xCC22B6F3F5788EA4ULL, 0x2097159AEFA41B32ULL, 0x20113E0D0D6D1362ULL, 
            0xABDEA8F76521619FULL, 0x33866A45EA797EB3ULL, 0xB9AA43BD1BDFA68AULL, 0x9CB367A9D39A74BAULL, 
            0xD02150CCAC35F4D5ULL, 0xC047971005A1CBC6ULL, 0x02971B2F4B157A5BULL, 0x6F444705B273AB72ULL, 
            0xA530101B3D06CB66ULL, 0x001EEA0693DE037BULL, 0x48D60843B31260D9ULL, 0xE77D9E7968807E6BULL
        },
        {
            0x6F12E1492C22F6EBULL, 0xFD04B878D64E3022ULL, 0xD7BCB11E49A5458AULL, 0x515EB9F65E67018DULL, 
            0xDECAC54475749AB5ULL, 0xD5E2CB1343217777ULL, 0x124958908D828E78ULL, 0x8C201F64335037DBULL, 
            0x134910D6E3B91B1AULL, 0x1C85BA880CCECFBBULL, 0xCF45D3EB7547395BULL, 0x294CD3FA3DFB3E8FULL, 
            0xA2770A7FD83A91C2ULL, 0xED44A4422784BE36ULL, 0xF4E824F9C54DC89CULL, 0x9868CE01ECB41B8FULL, 
            0x6F6C0D96E4686D4CULL, 0x480DE7803D48EF83ULL, 0xB871BBA0E43F1640ULL, 0x2A0C568EF92D244EULL, 
            0xA88011CA9138F0C4ULL, 0x9AF1735D2A89CDACULL, 0x8B94F6C2837C8825ULL, 0x40BD254764312460ULL, 
            0x609AE6CF3E64A98AULL, 0xA0C52B2913DB628CULL, 0x595D3B1C58943A79ULL, 0x35CF646E0E8245CBULL, 
            0x7E6AEBA46FA5B286ULL, 0x54614C23FADF5156ULL, 0x02034AFF19317C95ULL, 0x2524300BB67D57E4ULL
        },
        {
            0x1AFD50C6C5BA62F4ULL, 0xA740C9F54BE3E1C4ULL, 0x766759CD2A101297ULL, 0xE9B9B21BB6189F51ULL, 
            0xBCD8CD1B06500E05ULL, 0x8598064FC7EF2A23ULL, 0x30FA30C13B351189ULL, 0x816DEEBF40576A06ULL, 
            0x9C3C942BBCB21BE3ULL, 0xBD8D4FCFFA4DE904ULL, 0x4DA657FED9B8C582ULL, 0xC62AEDB30B8A35F1ULL, 
            0x7BE9798433BF5955ULL, 0xFDFB0D44BB437AB9ULL, 0x9F16725F26081E2BULL, 0xCA6333FF122ED542ULL, 
            0xA5FE4CEE98E89B91ULL, 0x17C1270350822FB9ULL, 0xA71BF8CA8E342B0DULL, 0x95ED9EA4951CE254ULL, 
            0x93E22EA07E923C79ULL, 0xD192C1028FF0F61AULL, 0xF19AE203E4F2C39DULL, 0x709BBFB893FEA8ACULL, 
            0x6C64A9AA9D8B0485ULL, 0x144E976FF11F1BFCULL, 0xCE467705C20FE5CDULL, 0xDC5B02A4AAFDD050ULL, 
            0xC98BFAA264B19E68ULL, 0xE91659C77A52AAFBULL, 0xFE1A689AB2935818ULL, 0x1D18F21AC905287CULL
        }
    },
    {
        {
            0x1B6F0B2632A9D475ULL, 0xFFA9C8890CC2946BULL, 0x31B639752FDB2A0BULL, 0x5DE5E44B0B7A59E5ULL, 
            0x6C5CA790AF581819ULL, 0x55E7B1C97BE03371ULL, 0xECDA9651E59F7427ULL, 0x76CB1D2982A81C1EULL, 
            0x2B9ED4B6B4704B47ULL, 0x74E83267CCC3A847ULL, 0xBCB2A04DB3ADA0ADULL, 0x2761E3237AB11F2EULL, 
            0x4E64E879AE6423F8ULL, 0xF5235A014844E67BULL, 0x84F32689C29C6E95ULL, 0x0F0BD0191BF172AEULL, 
            0x09840BA9F92FB9DAULL, 0x973AB1165AC59709ULL, 0xA205E112FCA091E0ULL, 0xC48A6CA1E514523BULL, 
            0x2494BB486E78006BULL, 0xC543601D663C194AULL, 0xB82CE5C13209E737ULL, 0x8A7871D9DC83D599ULL, 
            0x3E3EDAA36BBE3B3DULL, 0x95CD106367D0A61EULL, 0x57FEE2BC0737CCB9ULL, 0x55431ABCD4E341FAULL, 
            0x1BEC0F2EC7CC18C2ULL, 0x137C056F0749AB1FULL, 0x15C2B6F3076B03A3ULL, 0x34E9C03394D9E9BBULL
        },
        {
            0xFF5E52D1A2DEEF34ULL, 0x8314EC5103A1750CULL, 0xA874F4BD535A2629ULL, 0xA4DCD595B7901893ULL, 
            0x1C4D36956D9B02AEULL, 0x94C1E46EDDCC8DA4ULL, 0x54A248605509E7FDULL, 0x584E302E0605AE7DULL, 
            0x5DC2C59C9A83AE71ULL, 0xA32B364C45D0894CULL, 0x1C95BDEA60892993ULL, 0xC6CFBE7797B4565EULL, 
            0x50CF9CEAC356CC5CULL, 0x0EDCC513352F07B8ULL, 0x27409FD05C2E99BAULL, 0x4BF8EBC280F67339ULL, 
            0xFE60BA33BFD5DE8FULL, 0xF1B4F13CEB318DEFULL, 0x62FE8D2CE15A2142ULL, 0xA6A3DEA0F50DE18FULL, 
            0x31F92298342F3866ULL, 0xE45A1CB5F421147CULL, 0xDAA18A2B40729BEFULL, 0x75F4B9077B81DEDFULL, 
            0x8A1415BC863C7550ULL, 0x17D00514421DA08DULL, 0xFF15D4DC62F0A7BDULL, 0x9002145F730ADE27ULL, 
            0x9F9B8C487F1E0028ULL, 0x160A100D60753C28ULL, 0xC3ECFF02317FD72CULL, 0xEC0F17973CB355CEULL
        },
        {
            0xC7EB1C7DE55E3170ULL, 0x5772DC6BC480B133ULL, 0x052FB3688E9F8C10ULL, 0x1F1A5DD41EB9F31FULL, 
            0xECC3C41F37E14031ULL, 0xA2ACA9E0C5458764ULL, 0x72E7272F4A3E5E16ULL, 0x28CF816C7C939118ULL, 
            0x0A6C8443924CC3B1ULL, 0xB4111D162F0B2BE4ULL, 0xA372DA8595ADE625ULL, 0x1BC4D6CA215CA417ULL, 
            0xEACD6D98A8FDF429ULL, 0x9E60A4EAFF74C4AEULL, 0xF79C022AF8B098AFULL, 0x2083D9DDE8D7A831ULL, 
            0x8037F031E7B6DF17ULL, 0xC818998019CF6A64ULL, 0xFF169FB2AEA0F264ULL, 0x0C35AD302EA653BFULL, 
            0xDEAFD71621FA8D51ULL, 0xD622BE5CAFCA2DC5ULL, 0xD3F929A938807F1FULL, 0x425FAEFAA0E5BE4DULL, 
            0x2C5B614BBD0B4E1EULL, 0xDDFCFD25C5211575ULL, 0x803D5076A75C3F79ULL, 0x07D0FBDE36B0713BULL, 
            0xFD13F6148D23AB5FULL, 0x4FFF9A9947B1853BULL, 0x5E09F63ACE0B163CULL, 0x5AC16E4D63A980E3ULL
        },
        {
            0xBD5FBF4239A2461CULL, 0x090DAB8923DD8D3DULL, 0x6DB4D5235B436182ULL, 0x466EC102E20C8644ULL, 
            0x18B6F4940D9314C8ULL, 0x4DF030BD15B6B754ULL, 0x71C080221456BD7BULL, 0xBEBF13AE18A8C6C8ULL, 
            0x2433EF4BA59C20FDULL, 0xD4FD522D11A5CE9EULL, 0x9CC97DB97F14F54EULL, 0x0414F29A5767E72AULL, 
            0x233B48F48958AF61ULL, 0x260348CAB5A8B23EULL, 0xC220E3AD6631D952ULL, 0x43D9A478E53FC3CDULL, 
            0xA82B54A530B6D0BFULL, 0x2B70D1F1F2AA7BB5ULL, 0x897F79F77C743E54ULL, 0x122D1F1350FEAD18ULL, 
            0x7F673CE2B64AE2FDULL, 0x65CD7FA2FEE7EA7EULL, 0x511D1B494DB4E1C2ULL, 0xD33B633E93B5F80DULL, 
            0x8EC40F5250CB7CECULL, 0x8B32A294683F0115ULL, 0x6EBBDADCD540CBF0ULL, 0x6BB556AB125A4E82ULL, 
            0x0E81D17A542F079BULL, 0x5923F2EE9B26698CULL, 0x7466B0E781B81332ULL, 0xB128545ADC2D3E60ULL
        },
        {
            0xED5147081B5B5003ULL, 0x0886FABC04D785D9ULL, 0xBCCF7B178C0A9E5EULL, 0x1ED25446D57653FBULL, 
            0x6C2B27EE999C0160ULL, 0x826FFE270C7E2A00ULL, 0x00F4C6AC938EE3F9ULL, 0xA5092EE23CAD415EULL, 
            0x14C9542D243004CDULL, 0x49BB8431D34C5201ULL, 0xA330F72F66547C7DULL, 0xDC76B467B49D54B3ULL, 
            0xC52E7CC0D52FB425ULL, 0x3BDE379E80825647ULL, 0xC6A0ADEA112935C4ULL, 0x9D43645C68E97071ULL, 
            0x2709B26DF61A4F5BULL, 0x21231D6D6523A65BULL, 0x79A952C42A3405BDULL, 0xEBA83DB799E38F7FULL, 
            0x3654D0E826017389ULL, 0x71C7FB980AE1C1C6ULL, 0x32B075264837AA1EULL, 0x2369D27E3B08296FULL, 
            0xA65CE50DADE0368AULL, 0x89B20D6536F4B4AFULL, 0x93C58A86FA690A58ULL, 0x9044B5A7643ED73FULL, 
            0x687F7241D7C23BC1ULL, 0x77C5C6F7CC640787ULL, 0x00A962B5D13D5357ULL, 0xC90653D85AE38642ULL
        },
        {
            0x034759E04DD522A6ULL, 0x524724DF1FC6B91DULL, 0x897B8D08D0FC4596ULL, 0xB91AB57E8F6A14E9ULL, 
            0xB3177AAB53D046A9ULL, 0x0273AF91B8449B29ULL, 0xFBEB166D5CBDF22AULL, 0x6B99B2A04D1A276FULL, 
            0xA1D8C9A245C15B79ULL, 0x477FD8846B16B1E0ULL, 0x21AAD290E872AB1AULL, 0x0B142B39DEA7253EULL, 
            0x3941E55170ADF863ULL, 0xF185BEE3BC85EF3AULL, 0x30BD4337AB52446CULL, 0x7F910C09168DF09CULL, 
            0x7B1580FF1466A02AULL, 0x479066A60A1A1DA4ULL, 0xC4D7F5EA948F26C4ULL, 0xC4C3BAFE22084044ULL, 
            0x39BF0E61BA50EC12ULL, 0x26BBE6913B510339ULL, 0x0A7FF05648CFCB36ULL, 0x62D2FB12EC07C3EDULL, 
            0x830D5237E70E1CBEULL, 0x1C88446260AA7388ULL, 0xA1147C6854FD0A5BULL, 0x4E060DAD28E92D4DULL, 
            0xBF2980E6AFE374A3ULL, 0xE91F03FA42DD163DULL, 0x6A3C1051E52B9E3AULL, 0x0CD26E9D34C77728ULL
        }
    },
    {
        {
            0xE1CD98664CD2F56EULL, 0x24AEE53DE34807F3ULL, 0x487D7D394FD0E20BULL, 0x0684F66C654F81E4ULL, 
            0xC3F691B74230264DULL, 0x2FDD8264B6624A7FULL, 0xFDDCC598DE641D1DULL, 0x00C7F3862A86286BULL, 
            0xD4ECE6A51DB9EA1BULL, 0xDC7532A323B15165ULL, 0xAD095074431F0FE5ULL, 0x37D8987E2983A304ULL, 
            0x670E85979C1E9C3EULL, 0x98802F00135A669FULL, 0x755524328A44304AULL, 0x141B8F4C48DC1630ULL, 
            0x1E90C47E361E60C2ULL, 0xB38DCDDD9B8146A5ULL, 0x0FAC8090EB7F2465ULL, 0xA90CBDE9F7D654CDULL, 
            0x0382AE36CC00D2F0ULL, 0x7391E6B64E9BF3ECULL, 0xE7BFA7BFC5E906CAULL, 0x4A4867A2C22ED1E3ULL, 
            0x865D7731D6E84D99ULL, 0xC3008A25E60F194FULL, 0x26D88A6758515DEDULL, 0x421738967C423DC2ULL, 
            0x6597329468C4269CULL, 0x0E92465713205302ULL, 0xA1AAC37A36105B26ULL, 0x3CE6F14CDC3EDF9DULL
        },
        {
            0xA55724FA97182D83ULL, 0xCB283C668BF7AC7DULL, 0xAEA5D57074F4654EULL, 0x4FF0CC2BCC2E4000ULL, 
            0xA1757B60D31192CDULL, 0x5076585C664E5663ULL, 0xDE6940B301598F77ULL, 0x8E9951BE50AAB059ULL, 
            0xB88509C5E3F6A303ULL, 0x62FCD720E89EC9BEULL, 0x856D1F881359574EULL, 0x5674B79B91ADB893ULL, 
            0xD3FF8620C4825F91ULL, 0x108AB2D94231677CULL, 0xDE50BAF5E0540AE2ULL, 0x357BF9533C0C184CULL, 
            0x5B4CC43FB87414D4ULL, 0xA8C372260BB91729ULL, 0x0EB734829BA8E376ULL, 0xC9F11C3666CD018FULL, 
            0x836C0F4A8A1E7D31ULL, 0x1F49AE583C97E8F4ULL, 0xA7D595BDD125AE2DULL, 0x823B1299E68FE42EULL, 
            0x36A1FEDC0D6E9A65ULL, 0xC3F8F90CA333825AULL, 0xE9B21968C702EC86ULL, 0xA5998DFB404405AEULL, 
            0x36BDAA7A319DACC4ULL, 0x444509329B03A6A3ULL, 0x9D83799FE4CB8965ULL, 0x2042DA1A2EA4C231ULL
        },
        {
            0x3F1A6E153976FF9CULL, 0xF16EA83732C25E00ULL, 0xE3C8599131BC1232ULL, 0xC591AE8A684736EDULL, 
            0x2A289A1D62EA82DDULL, 0xA50B960D05D30730ULL, 0x0D77A3D9BDF79A6BULL, 0xD4D4817D6D0B764DULL, 
            0x0AA7181275188562ULL, 0x709FFDE96EFAC44DULL, 0x089AD566CB504235ULL, 0xE7FEB8F4EEF51BE4ULL, 
            0xFC6D8D24B3E7692EULL, 0x6655C117DA280B3AULL, 0xFEEA03B9B478DA6CULL, 0x918E36C3FBFEEE66ULL, 
            0xFC95A523D7FC207BULL, 0xFFEFAD76E9045BC5ULL, 0xAA61FE99C6C56669ULL, 0x299333203F8EA8F7ULL, 
            0xC7B466BE86DE0655ULL, 0x5650B63F59A5EDD2ULL, 0x7E6E041424E9A6E7ULL, 0xFBD29BA689C0E1CCULL, 
            0xB2F4C6D774758C8FULL, 0x8AE3E1CD3E91C824ULL, 0xC5463EA4DB3F1F9EULL, 0x583AEA54711DE5B8ULL, 
            0xF129BFDB3BDBBF0FULL, 0x2AA6960657BC89F3ULL, 0xAAA3208C2AA2426FULL, 0x14B77E0B17C2D4F2ULL
        },
        {
            0x3A2C1C5EE3211E03ULL, 0xD7D8F62787F61FA3ULL, 0x57F4203CB97CD90EULL, 0x53F2186833848100ULL, 
            0x02B17EEB6C612938ULL, 0xE2435522D5B3E64BULL, 0xE13DF588923C13F6ULL, 0x40D02AF40BE36860ULL, 
            0xC8F6BC5305798C61ULL, 0x680AC1CA4534630FULL, 0x49B5E774C76593B7ULL, 0x96CB3B982F99BF70ULL, 
            0x140EE0A07AB0F999ULL, 0x14E4D75EBCEAC7A5ULL, 0xAD63E91BB08FFE06ULL, 0x7C0B9BB390C79831ULL, 
            0xFE35351CE66B4CA0ULL, 0xC4E2D78ED951CEA2ULL, 0xE38E8E74934830EEULL, 0xC8FE1D021E9822CEULL, 
            0x47E7A45DBFF2B933ULL, 0x73CFE2FCC30F92C3ULL, 0x368F30206E5F3AA4ULL, 0x842CBDD039A0AAF9ULL, 
            0x4E7FFC3BAEBC81B4ULL, 0xA324E5554D937006ULL, 0xD04B05CB414CECF4ULL, 0xA1CA961A72C1A8DDULL, 
            0x471C6854399ABD91ULL, 0x2E98466D91F52E4FULL, 0x819F9F4099F216B8ULL, 0x0D49C0DB7FF5B742ULL
        },
        {
            0x8DB3FB7094AF3C4EULL, 0x9BD4538948690ED4ULL, 0x1AB92BA6B1D9219AULL, 0x56F00B05464AED7AULL, 
            0xC9DADA4167B5487BULL, 0x83EDE9F8DEAB11E0ULL, 0xB01DFE4EABBB45ABULL, 0x3884308C69CC718AULL, 
            0x11552E17E307B6A5ULL, 0xE4C8C2A306FECAD0ULL, 0x08CA17D04426FE51ULL, 0xCFF9299A5F4A017CULL, 
            0x5CDCA1A68CB6DC2CULL, 0xC94D87B35C1550F3ULL, 0xCE30F6538BBC8128ULL, 0xB61B5A8D032C0C9BULL, 
            0xC70EEE5A7AE6B2BEULL, 0x925EDD83E5ECFD21ULL, 0xC00418CC54FFF9FCULL, 0x8765BD4CEBC77B75ULL, 
            0xC882613281BF2A12ULL, 0xF909BB8C1B31C19DULL, 0xC381CF4773428966ULL, 0xC6636B1A0241D3F1ULL, 
            0x4638F0B54D409596ULL, 0x0E5572F4B803AC37ULL, 0x7F0BDFF6AAB25639ULL, 0xEF3F1ED341F02026ULL, 
            0x4FD7605EFB2B8C17ULL, 0x70966CB71B8AA915ULL, 0x19EEE1C2E0C752F0ULL, 0x9055335DF8130DC1ULL
        },
        {
            0x23EDB060883A69CDULL, 0x5C17405BE638FDA7ULL, 0xA647562DB89C15FDULL, 0x15A50512858F55EBULL, 
            0xA1E02F0BDCBCE413ULL, 0x22E89F8B824F9EA0ULL, 0xE576429CE6860B87ULL, 0xD45151A85E218B6DULL, 
            0x6B18EBD6A22DDAD6ULL, 0xB17C3C3D425F4BAFULL, 0xDFF46687843D7F9FULL, 0x28EEE12DE2172BD3ULL, 
            0x22D1A6B2BE4A5296ULL, 0xB9E2D63090C92545ULL, 0x3D26BF17933BA6FEULL, 0x293CFA17F3BDB140ULL, 
            0xAA6B1046690318D7ULL, 0x6EDA228F15F62D0CULL, 0xEDAE1BD5B7BC68ABULL, 0x2C36CCDAFEFC8810ULL, 
            0xC5AC08016037C6BAULL, 0xAF8EEB1D84E19F13ULL, 0xF9F8E85B76944633ULL, 0x1573BC5241F86C2FULL, 
            0xA0BC33A885F38A51ULL, 0x85787710D48CAA0CULL, 0xD5CB40301155BB8FULL, 0x19684C66CFEC34A3ULL, 
            0xDC0245343E9265A5ULL, 0xB09357A603BC48B3ULL, 0x20A2E97EB692246BULL, 0x256584E8E3E3A997ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseBConstants = {
    0x26E9C28EE6B99D04ULL,
    0x67A513FD17452D65ULL,
    0xCE5FD8AD86C86E46ULL,
    0x26E9C28EE6B99D04ULL,
    0x67A513FD17452D65ULL,
    0xCE5FD8AD86C86E46ULL,
    0xE7858BF9D0167905ULL,
    0xCDEAEDC70E3505F3ULL,
    0xBB,
    0x4E,
    0x81,
    0x34,
    0x24,
    0x27,
    0x4D,
    0xCC
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseCSalts = {
    {
        {
            0x578157E65270DD29ULL, 0x407A0C0818315E6BULL, 0xF2D8401044ED7306ULL, 0xE12F61709FE87CB5ULL, 
            0xF9CCBF4A1F943495ULL, 0xA1A448AC27FD1000ULL, 0x48F7B8F45180DF0AULL, 0x9DDE0EB8C579940EULL, 
            0xA3CA658A557A2412ULL, 0x17CE93273799B98DULL, 0xA5D12CD76CED2EB4ULL, 0x3FF21691E4F40393ULL, 
            0xF74B531275500194ULL, 0x2D81AA40B3E81DD5ULL, 0xC36D300BB4D5D803ULL, 0x823812998F41A614ULL, 
            0xA2886F49D5545FC6ULL, 0xA4E7458C17FD5C39ULL, 0x211DB0E74A556EECULL, 0x0A998B319589B760ULL, 
            0x44FAA79888AC86E2ULL, 0x913A4CC5E042CB6DULL, 0x45413F711DAEDB5AULL, 0x51C6E531566AF2EFULL, 
            0x96EE36DF2E54ABC6ULL, 0x33C1E948AE147451ULL, 0x0C7675BEC3EC6293ULL, 0x60D06C078BB9A161ULL, 
            0xCE743716FACECDB0ULL, 0x697EE8EBD81754F5ULL, 0x4A347CC9C2DA2F1AULL, 0x2757BFDA559604ABULL
        },
        {
            0x74AC644B8479F6BAULL, 0x16F462D8514064F9ULL, 0xAD0EA787E6D2321BULL, 0xC5AC838732D05427ULL, 
            0x9D83032E6466A909ULL, 0x944E7671BEEE82B4ULL, 0x5A787BF11AC2CECBULL, 0xE73FCF6E1D326221ULL, 
            0x2D5B2D7B6786E33FULL, 0x57F5C27CC838F94EULL, 0xC682368F2B2E130CULL, 0x8B32DDF238F6C733ULL, 
            0x6A486402308AAA3CULL, 0xA2A936435613C9D0ULL, 0x1B82B6AAF3A22DC6ULL, 0x479C97C6F327C23AULL, 
            0x92C1E77BDAB39C61ULL, 0x27982E7A6E679C60ULL, 0x39AB7CE4352DBE09ULL, 0x7ADFD138E9616741ULL, 
            0x724299E433CFC71CULL, 0x76AAD4159E7B9E43ULL, 0xE993A380D2149A1BULL, 0x4E22651403ED58D0ULL, 
            0xB6090E8D33FB2F82ULL, 0xAE561E446CD0679CULL, 0xB4243DCA6595D1DCULL, 0xC00A7053858087ADULL, 
            0x2BB905421D83E428ULL, 0xD5D1E773C0ED2A4EULL, 0x0F1F9640C69B74F3ULL, 0x9BC8505EB8E18520ULL
        },
        {
            0xC6DAAEAC638276D9ULL, 0x625A6F6F5DC40DF0ULL, 0xAC58F0491A9D7C94ULL, 0xC3F80E8F9A1C89B7ULL, 
            0x4D96C56C61345133ULL, 0xC71F42B0972B5848ULL, 0x2092941CA80C6818ULL, 0x239045EBFF212749ULL, 
            0x2AE961941703E87AULL, 0xC5FD344FC104E972ULL, 0x07A6808198ABA076ULL, 0x4665BC8275E3CA95ULL, 
            0x184E30B4577C6153ULL, 0x71C5E18ECDC699C9ULL, 0xA2A27263C511AEF7ULL, 0xA783C1879CD37480ULL, 
            0xD2833DD0B4E4DB41ULL, 0x39F5E86F8E73E04CULL, 0x2C3AFC1C36659264ULL, 0xB40CE355B52D3B2EULL, 
            0xE05990E93EC82E87ULL, 0xF10456F15931157DULL, 0x1B58684363FBA55EULL, 0xADB3BC2102F60C57ULL, 
            0x2142C6E2078BCA5AULL, 0xB1833B5EFDAE4425ULL, 0x1ACF763C446BCAD1ULL, 0xF0B5F8D9D763E3F2ULL, 
            0x1738CBBFDED3C284ULL, 0x2A63B5BAC1CB7478ULL, 0xAD863B79D9E26426ULL, 0x6A0920FE4533E829ULL
        },
        {
            0xDD4283388D4B1F91ULL, 0xB029BFAF04820BB1ULL, 0x8C5C34DA60E41ECEULL, 0xBE346EF18D25024AULL, 
            0x9CC7D447180F86BBULL, 0x5770115D9CE69ACBULL, 0xD23AA12F4BD72285ULL, 0xFEA9096F299A5AE8ULL, 
            0x832B9FC872A28BF2ULL, 0x4B492ECD14BAC499ULL, 0x97B1DA29F13A10B3ULL, 0xE585564399E1FD06ULL, 
            0x036298106FCC4264ULL, 0xFBD1B6A61CBF39E6ULL, 0x7B47355B22A7E6DBULL, 0x9FBB367DDA651A1BULL, 
            0xE544B5A0A643547EULL, 0x0AE393F95857298AULL, 0xAB8C5A0D225A57D1ULL, 0x47486CC770F098CDULL, 
            0x8D58FBB577B38E50ULL, 0xC069DD8917F94B00ULL, 0x914021A9C03A4736ULL, 0x70D899F1000ADE3FULL, 
            0x04B2A899927454DAULL, 0xB716F339FE2FED70ULL, 0xD9B94965A2764D53ULL, 0x4C36D0583D2F013FULL, 
            0x628C86D90CE755C3ULL, 0x0CFE1784693252D8ULL, 0x1F42ACAEFB42307EULL, 0x149337E7759B4330ULL
        },
        {
            0x270F0F083A3C8095ULL, 0x6D9EE0245A9891E5ULL, 0xDCDF03B40769247DULL, 0x7D3E3D41A8093EBCULL, 
            0xB5832A6C16FB6C58ULL, 0x69970E693984103CULL, 0x77B32EBBE4235CF4ULL, 0x450B6BECD0D0C819ULL, 
            0xFE04D496CF09B350ULL, 0xC1D4B4A84D831EEEULL, 0x7C8D0022E7D6903BULL, 0xB6623CA22547A516ULL, 
            0xF40FBAE78D70DBDDULL, 0x3CF746EDF193F88FULL, 0xB8B74D413E33245EULL, 0xBBE3D4AF64F0B4D3ULL, 
            0x245A16EE6E702E67ULL, 0xC7B93CE4F0C5A28AULL, 0x5511BB104EDEF41DULL, 0x66BAD1C668169F43ULL, 
            0x97D13C755F147556ULL, 0x029260798FCDEFEBULL, 0x035B168E422A0C93ULL, 0xE11456BC086B9416ULL, 
            0xD60054A2E94D443EULL, 0x588F6AD71EEB1FA7ULL, 0xF102B9A145837299ULL, 0x9A90EDDB600E4074ULL, 
            0x34958E1AF189399FULL, 0x38468F463493AC13ULL, 0x3799C228BF139530ULL, 0x87D71ABDE6770D5CULL
        },
        {
            0x01EF73B3706F5FD1ULL, 0x15260A7299D6C7D5ULL, 0x6296B0DBF5CA5DE0ULL, 0x1F018077F166F1E2ULL, 
            0xBB49FF59DDA39E3CULL, 0x2B1C66F14CA8C5ECULL, 0x34024DC53621E7ADULL, 0x7A8732BBA8863FB4ULL, 
            0x519BE5F08E5A9A45ULL, 0x7B78AAF8C518133BULL, 0x2552096E2D115B29ULL, 0xA0122A5BE585D1E4ULL, 
            0xEA4A1AA7F64F92DBULL, 0x8694619A32E82AA2ULL, 0xC3B0EA648E049948ULL, 0xB9932CEAEB4B748CULL, 
            0x6BADEC94AA144E2DULL, 0xCAAFBBCB05795432ULL, 0x1B55295C927679D9ULL, 0xD78EDBF713B879D9ULL, 
            0x5D9FC11789ADFE06ULL, 0x1BC49A70F4B28A49ULL, 0x84F9DC0362BDDB7FULL, 0x9F5B824DAC0FF487ULL, 
            0xB98D12620E81D01FULL, 0xF7B96412F99AA3E7ULL, 0xC2358737F50771EDULL, 0xCBDADBFD5DB5ADEEULL, 
            0xB2F656AD4E339A5BULL, 0x3C15A53A31BB5771ULL, 0x3E1BCD1F9D7ADEE8ULL, 0x72060EDA3DD9CBCAULL
        }
    },
    {
        {
            0x73F2198703DCE8D6ULL, 0x35D8B90C7D1BFA21ULL, 0xEA7F6FFB40FF380DULL, 0x1A0D67AF7DCAF78FULL, 
            0xD7FC7A53DDBF5A16ULL, 0x9FF965839C72D410ULL, 0x755018CC42E20D82ULL, 0x74325B492D858E3FULL, 
            0xA71276C4B1582AD2ULL, 0xB1B8A2DD44A196F7ULL, 0xA36CEF816A47F5CBULL, 0xA71131284D01439CULL, 
            0xE9EDDA2C257A8B26ULL, 0x3896F1C150FB00B1ULL, 0xA552569E0F3EAF9AULL, 0x8CC11E2587B945FEULL, 
            0x382E967E4F4FC9B2ULL, 0x0699C4D2467ED018ULL, 0x30E2C4C29C72A494ULL, 0xE4E0E969DFB0A274ULL, 
            0x11561861A6BEC73CULL, 0x6B589DC78A62668CULL, 0xCBEB3919553460E2ULL, 0xD06EA2DCD64CBB31ULL, 
            0x4242871E6E804890ULL, 0x78C05CBB405613E5ULL, 0x3A26470BB7F7936DULL, 0xE484D4FC3AD02F8CULL, 
            0x67AC8F4AF02F1B47ULL, 0xABF1B8AC3B23A216ULL, 0xC16C23E9ED257407ULL, 0x4CA77D11E0DCACA5ULL
        },
        {
            0x25782C379A63096BULL, 0x8C0E35F0000207B9ULL, 0x0E025850CCF9FC4EULL, 0x3EE82CC68C99F5CCULL, 
            0x9F8D5E56AC013D3BULL, 0x5AE37530949E2C03ULL, 0x94CE924D86D3CFC2ULL, 0xE256E33EFB997083ULL, 
            0xE1227C786A9B86FDULL, 0x787756835B9788F9ULL, 0x4CE12D6F73F319B2ULL, 0xDC0FA9B8867C5658ULL, 
            0x3AB41F3685191F05ULL, 0xA6983505486FF6F9ULL, 0x8A3C192F0434B858ULL, 0x1FFA0CAA4CA47B05ULL, 
            0x9FB83074C0EC92D4ULL, 0xE90CD09E6536EB7DULL, 0x71A6AAC90187D00EULL, 0x66DD9914FBA9AF04ULL, 
            0x134045CA2E12A0F9ULL, 0xE19F54C69319EE31ULL, 0x1B1E6001131D37EBULL, 0xDD2D73F265063B04ULL, 
            0xBC81D251A68EF199ULL, 0x294AF84979C698E0ULL, 0x6D851501D57BA434ULL, 0x2FE4054F943F5E9DULL, 
            0x0B314D17B40C2113ULL, 0x498A41676E6927FDULL, 0xB460158969C8891BULL, 0x217950A8DA9A2E1CULL
        },
        {
            0x6CF01237DB70B00EULL, 0xCB813AAD7D35853EULL, 0x544433015B6262F2ULL, 0xAC9BA7299D498802ULL, 
            0xDE30644105746372ULL, 0x6FA6B8C5639167F5ULL, 0x23C5764F9B3BAC83ULL, 0x3B977D3AA9AE79F7ULL, 
            0xAF2A6EC491838A7EULL, 0x7600AED2581609EAULL, 0x436982488F5FCEC0ULL, 0x78BD32961C1F3602ULL, 
            0x4D39C961360C82C0ULL, 0xFDB98F528A334043ULL, 0xC93D0D922A4497BCULL, 0xED2375E79EA6408DULL, 
            0xFFED024DEA783F61ULL, 0xA92B0A32692B5D0BULL, 0xDC7C689697776541ULL, 0x45FF5B23772717C7ULL, 
            0xF917564655512D9BULL, 0x247834754E2ABDB2ULL, 0x4F220C46B6A36125ULL, 0x240DF790FAE6CC4CULL, 
            0xDE09C8A87F027A9CULL, 0x9F6B37DEDC58FC4FULL, 0x0C8C199BD46FCCD7ULL, 0xA628FF753F79EFF5ULL, 
            0x48C674D66E2C8942ULL, 0x54C53C1FF14CDE73ULL, 0x7EFE7907F4199D7DULL, 0x040E64A6895A9D60ULL
        },
        {
            0xF46D6219924AE50BULL, 0x842BF1BA9405D702ULL, 0x549B9B6BE97C129BULL, 0xFC4AAD4D66C28AA0ULL, 
            0xDC8D34BEE8D0007FULL, 0x4E33E6432EA3659BULL, 0x8928BF1DF489571EULL, 0xE3476EE32863EA25ULL, 
            0x3851978141EBAF03ULL, 0xE154CFF691BC760DULL, 0x35ABD290401276B3ULL, 0x8AE2F89A359A9E1DULL, 
            0xAF190AE587A30B98ULL, 0x0608759ECB75F90CULL, 0x6655B6143E8C9964ULL, 0x56DB8780B0E12D99ULL, 
            0xB45E81023F2EEFD3ULL, 0x53552502B08964F8ULL, 0x5D77AF708DD0D663ULL, 0xB819C480C7C980E0ULL, 
            0xEB88EF6AE0F18A6EULL, 0x7292BA782E277BE4ULL, 0x4C5F6C7ACCD85CB9ULL, 0x7563C025353142B8ULL, 
            0x66C781C56027507DULL, 0x4E14BEAB9BCCEE66ULL, 0x34B23AD5EE8698B5ULL, 0xB5070BF146A282B7ULL, 
            0x946FA1CA1C4B49A8ULL, 0x3FAB6239357DA43AULL, 0x62696E86C417DCDBULL, 0xA13FEBC817A1F093ULL
        },
        {
            0x88717A14C1537678ULL, 0xEDB4CC0B8B9EE968ULL, 0xED61576E4E1FA607ULL, 0x644ED78802E15562ULL, 
            0x6368DF049A6694F3ULL, 0x30A605C50E778427ULL, 0x84EBD4FF2E20E55BULL, 0xC320D2C0CD223F14ULL, 
            0xDF955FC0BF060B71ULL, 0x0CACDFF84D98D54AULL, 0xC634FFFB4ED87B05ULL, 0x943A8131CAE3DE35ULL, 
            0xF152E9DF8877FA65ULL, 0xA5503AA9D43AA38EULL, 0xBE0B5C3284CEAFDAULL, 0x3CB0A63C4F4E0DB6ULL, 
            0x4486D2588B5E49B1ULL, 0xE035909221B88C91ULL, 0x9DF313E4DA8FC58CULL, 0xC08A1A5A18B18274ULL, 
            0x5D5625EA14B32527ULL, 0x32D1C4CD09481072ULL, 0x1FFD7F6C29BE4899ULL, 0xA409D52029C2CC83ULL, 
            0x39C98A2631948B24ULL, 0xCAF1146F68FEEBD9ULL, 0xD9C8C5833E81C2E9ULL, 0x77ED41A342A0D1BDULL, 
            0x7732011552C9046FULL, 0x7E71DB5884DACDB9ULL, 0x117B6508FF05ACC8ULL, 0x0D38C8AB4E435A16ULL
        },
        {
            0xD8AB26EB6A4D92C4ULL, 0x7FDAD5C762A704FBULL, 0xE4ED8CA01140EEA8ULL, 0x897151FE3BD7449FULL, 
            0xB527C3B3FE07520EULL, 0x219C23E83EB50045ULL, 0x9C21FB7B8092D26CULL, 0xE05719C16A7F109AULL, 
            0x55DF912A20706187ULL, 0x34F7B45B9D7CB2C5ULL, 0x48F2F043B501A920ULL, 0x0460414AFFA306FBULL, 
            0xA7F55486A8B9894DULL, 0xD438E36ADAB3AA8FULL, 0xFBBD40EE9501BC22ULL, 0x02EFB8C985322B9EULL, 
            0x398085FD270C5AE1ULL, 0xE659B3370DF085D8ULL, 0x805F22CF30C81C37ULL, 0xA96E545C3D8ACF20ULL, 
            0x8DAE6BC88220BC8DULL, 0x30C6AE83795D7532ULL, 0x5987ECC9427FD843ULL, 0x42E8FD71283BBEADULL, 
            0xAE4FB3E0CC5437EAULL, 0x63E488BE8AEECC8EULL, 0xE686FE14237AECFAULL, 0x109B55475FD2F010ULL, 
            0x7BC67173E8B1AC6BULL, 0xD4F05A3C5E0A517FULL, 0x4FCFCEC9C90FEBAAULL, 0x7B5796956B0D765AULL
        }
    },
    {
        {
            0x805534AC52561D7CULL, 0x3C4A2053EA01365EULL, 0x496A120FCC44C868ULL, 0xA653E66ED86D28E5ULL, 
            0xE94AEFDC056FB653ULL, 0x35C23D3BFD26916EULL, 0x1971F4CFF38E305DULL, 0xA61FC9702F60FFEEULL, 
            0xDA39A393B9A43B55ULL, 0xB5EF27A4EB836CC4ULL, 0xA77751750651D27CULL, 0x8463A4EBCEB3FA71ULL, 
            0xB01424983563A003ULL, 0x1CEBB5652AF61654ULL, 0x428F062CB7A75C83ULL, 0x2C932AE9190ED71FULL, 
            0x047E4B84895B359FULL, 0x139928F19EC439C1ULL, 0x4CC4EA3B40EF7BB6ULL, 0x6DB8983D7A703E49ULL, 
            0xBDE5A7BF68B09795ULL, 0xEF2F904FB663E313ULL, 0xFDD3DF15AD3832DAULL, 0x2987F25FCD34D874ULL, 
            0x2BEDC09D8EF1191DULL, 0x7C0EA644B92B86FDULL, 0xECA2A8AC1E6F2D3CULL, 0x0E9DFCCC34BCD247ULL, 
            0xD6AD4E416961F13AULL, 0x1C31783395013931ULL, 0x3403B999B2AC424FULL, 0x8D5D47E6A760EE37ULL
        },
        {
            0xABF02B73CBBCA4C8ULL, 0x1032340248C59472ULL, 0xB853EC3A71991D7AULL, 0x1B577CDA8DF5F582ULL, 
            0xA17D234C724EC685ULL, 0x4843D884DF0D0EDFULL, 0xF431CE70FCD5C538ULL, 0xEA5772E662DB1A06ULL, 
            0x0B611AE20A6BCD49ULL, 0xDA4D3A3DEEB6C2CCULL, 0xC79ACEF24AE1D035ULL, 0x111DEFC854F46DADULL, 
            0x603498AC8191F040ULL, 0xFFE041E9B9C42C2EULL, 0x35BA762C74199181ULL, 0x1212DFE518380688ULL, 
            0x48C0F9E17F3BF131ULL, 0x2FC132C2BFADFF6EULL, 0xE092FF84CC9623A0ULL, 0x57E7A8FF167BCA83ULL, 
            0x942F46552C79C2A6ULL, 0xDFC160C6E9497151ULL, 0xC762AB15786C6D69ULL, 0xE875539CC9B68F92ULL, 
            0x08B3C26086AD2E4DULL, 0xDDA003B06A17F712ULL, 0x6320B56EAFB5A5E1ULL, 0xCE17BE0DE5D80F7AULL, 
            0x20676AFCE086FC77ULL, 0x74177062D040A3D6ULL, 0x7D16A6DA000E5E35ULL, 0xFE9BC3E46C6752A2ULL
        },
        {
            0xC15B015A2462DDA7ULL, 0xF31ED38367669309ULL, 0xFC782BD644AAA15EULL, 0x347F88FD8C76A2DEULL, 
            0xA5E2CE142F56BD9DULL, 0x15D2D9FBED33C15BULL, 0x593DC4520BEF58BFULL, 0xBC119ECB5AF37AE3ULL, 
            0xE89A7A623443DEBBULL, 0x8C4BF3DFA332B29EULL, 0xA9536152A4135E81ULL, 0x2482DCD9C74A872DULL, 
            0xD371150477A88946ULL, 0x4525CD2D30DEE8ACULL, 0xAA825715177925A2ULL, 0x668CDA93FF0771FBULL, 
            0x81AEE20DDD5FAF24ULL, 0x468FBE57BF6EAEA3ULL, 0x3EB2BB9508A6E085ULL, 0xF8F64A5DAFCFB6E4ULL, 
            0xDB976EA7FAA3D899ULL, 0x25AC08C1243CBF96ULL, 0x720E9BD0E0AB4528ULL, 0x93B384D58E9D75D9ULL, 
            0x1539D9185AE23259ULL, 0xD909C4CFE3222BDDULL, 0xE643EC19882B6CCFULL, 0xB7056B795628F6E1ULL, 
            0xA4DBECBD1E2B6758ULL, 0x6E440695E23FF8B7ULL, 0xCF645272F3DC7CFCULL, 0xE4BFF009F9DD4582ULL
        },
        {
            0x66F2F22B873FDA88ULL, 0x8B85A66B00B202DEULL, 0x4EBA61628A63045DULL, 0x661FEA22CF9A9CFCULL, 
            0x0B5E5D7507315100ULL, 0x559F33086C22BA4AULL, 0x773D8F5C06C19BDCULL, 0x2877B4D91D92C06DULL, 
            0x9138C6D9341D6552ULL, 0x09FC843BBCA2DA74ULL, 0xF1677BE6B30D571AULL, 0x823AD65A5B426EF4ULL, 
            0x104EB9224DF77530ULL, 0x18B7634BC0492644ULL, 0x09E5D7B79E6FEF75ULL, 0x883648471ABDA0F4ULL, 
            0x758414BE2E69B3A3ULL, 0x23FE9833A7060292ULL, 0x18DB07B411C2FC8CULL, 0xA1271050F8F94DEFULL, 
            0xE476DE4489C6FDC6ULL, 0x7AA833E95B688928ULL, 0x72F5C5868282F939ULL, 0x068F5B691C4EC27BULL, 
            0x0A8A8B2B36598EBBULL, 0x0C2397724408300FULL, 0x8827FD349E831BBCULL, 0xD017585A7CFE1ABFULL, 
            0xE7F6EFB08262E681ULL, 0x51D6AD00E6720E3BULL, 0xAD3C4C872C05EBE2ULL, 0x14BBAEF9AF8A2789ULL
        },
        {
            0x7968FE95581B96C7ULL, 0x7EAD299C26D30304ULL, 0xF02EB8107E98FA74ULL, 0xC4FFC90B2C19D9B0ULL, 
            0xB73C8FD85C0A102EULL, 0xCECF369AF5F241D7ULL, 0x5F574AC3719A7D0AULL, 0x923CEA2DDB5BCD41ULL, 
            0x2CF5C56CDFF7FCE2ULL, 0x70AC71A9F4BD568DULL, 0x3AB00B5EBDA8F56DULL, 0x00F72A6396D86C0BULL, 
            0x8E9B23B4B9043848ULL, 0x575C3D58E96EFE2FULL, 0xC212905CAB96B202ULL, 0x156D5DC29E2521FCULL, 
            0xED613FA022E8E026ULL, 0xEAE5ACF21D8D7495ULL, 0xDE520783477EDFA0ULL, 0xD6A6EA51A32E5DC3ULL, 
            0xEE1DF7E4FEB8AB33ULL, 0x0A8E57B25086D9C6ULL, 0x6855C8B060098146ULL, 0x851DE1282FC4AF05ULL, 
            0xCFA4EB5C17B83B09ULL, 0xCFC290C064D0B304ULL, 0x800CD8C6BDFA664FULL, 0x31B5D94F5A080732ULL, 
            0xB6A3299F1ABDD2E0ULL, 0x2B8953B14387CE07ULL, 0x6223D2DB2809902FULL, 0x4B84B51FDFCA0821ULL
        },
        {
            0x75A2115150B26F60ULL, 0x52E1D9A5E35BE3E0ULL, 0x75C61490D64A1D8CULL, 0xBC1007CF64E10055ULL, 
            0x1A02C14BB036FFFCULL, 0x5B3C33322E7BE4A3ULL, 0x13CAA281BAF4122FULL, 0xB0BB19724068397DULL, 
            0x1FABA30A50346AD8ULL, 0xDE7B88287A9B0985ULL, 0x89766DBC62423661ULL, 0x98318D07653FCA87ULL, 
            0x80552D18C271DFC5ULL, 0x7413BBBC7D677BBFULL, 0x327BAC79233A7B92ULL, 0x3493EEAA3738E348ULL, 
            0xD497273FD7BD7EBCULL, 0x30238A80EF79F9C2ULL, 0x214C3E2FBD919678ULL, 0xDCEADA010C439F26ULL, 
            0x6BBFA3B36022A2ABULL, 0x0A0C779B02EC33F9ULL, 0xD70ED471168FE0F1ULL, 0x3D8C5BCFC0CAA078ULL, 
            0x586E529B4E642C58ULL, 0x55371DD0B8F5A1DBULL, 0xD20C24C8F7F4CA45ULL, 0x105ECDB4C01B3ED7ULL, 
            0x1B5998E2FBF7BA82ULL, 0x423460083DF819CCULL, 0xAD443EDAD8C67F1EULL, 0xF53C0962CC79A8F6ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseCConstants = {
    0x5802E81BFF072A1BULL,
    0xBB8F279D2F053A77ULL,
    0x04D454C8D0919916ULL,
    0x5802E81BFF072A1BULL,
    0xBB8F279D2F053A77ULL,
    0x04D454C8D0919916ULL,
    0xEF3316C7C6D91530ULL,
    0x7781B4E6A8E8B29CULL,
    0x64,
    0xFD,
    0xEA,
    0x9A,
    0x46,
    0x4F,
    0x14,
    0x52
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseDSalts = {
    {
        {
            0xBAA518AB8E7C68EBULL, 0x78CC08CE45BFCF00ULL, 0x5A9D8502929EC695ULL, 0xB4AB7AAA1A5CC106ULL, 
            0x74644DF2DE207E34ULL, 0x5B23A13F903695ADULL, 0x6E76209CBA33DDE1ULL, 0x2B08DC780F19D4F3ULL, 
            0x5495FB0CB841D5B2ULL, 0xCC7408BD693AE111ULL, 0xA8AB952BF4EA50DAULL, 0x27B273B0FC9BC44FULL, 
            0x6A72035FCB728957ULL, 0xE028CE1410988C8CULL, 0x31D24E47FDF0BF5CULL, 0x4C29A4D169D61AD6ULL, 
            0xFE5992FEDAB12BE6ULL, 0xEFB6E72ECE4B1971ULL, 0x67574E2A69502F91ULL, 0xFCA4CD1BB5F12921ULL, 
            0x4E68873D204172CCULL, 0xD43C8056AA43049AULL, 0x616C9F75728E8BF8ULL, 0x893873FCA305351BULL, 
            0x8EA9D0C4449035BBULL, 0x28649EE5CDEBFE0BULL, 0x884D3AFC8442AABAULL, 0x3004A289832A7FFDULL, 
            0x017CBA97D65FF247ULL, 0x0D9DAAC21F46C19AULL, 0x1BC4BF8345F717C9ULL, 0x320CA9B1C7575C91ULL
        },
        {
            0x64675B83B3225AADULL, 0xBDAC2F2322DE3253ULL, 0xED3B82CF085AC9A1ULL, 0x04E18240DF6A487AULL, 
            0xD63EB271530009F0ULL, 0x928F400E9283EB24ULL, 0x5D85828BB0D6599AULL, 0xB4942516B3D492C1ULL, 
            0x551B40D94ED127BEULL, 0x66C0C0E8DE90502BULL, 0x2071C05A0ADC05C0ULL, 0x04FA9A9804B96C4BULL, 
            0x2D4A1EE6D56E769FULL, 0x08A157A213AC723BULL, 0x8ADC4E214FBB6E07ULL, 0xA2F2EB631B2D3091ULL, 
            0xDD6DBBA13D56F536ULL, 0x36032252C18FEA43ULL, 0x78E67F859DB80415ULL, 0xF4D7C43A43ED682BULL, 
            0xF15E582413E3F3F0ULL, 0x3478297F33362532ULL, 0xE5370505BCE981C2ULL, 0x18B98EDFE35C1F85ULL, 
            0xCC9E663294102B3BULL, 0x690434232C544EAAULL, 0x2C1978B177E558F3ULL, 0xD8CDB981EA1C848FULL, 
            0x2BB6EB69E3B211E9ULL, 0x7744208199018119ULL, 0x194AAC91D4AA815CULL, 0xAA30CC873F7A4D93ULL
        },
        {
            0xE0A39A7EE46290ACULL, 0x13E3BAF309A6E49DULL, 0x11A8C7B654B407B6ULL, 0x2D4D37929FC0FA47ULL, 
            0x17B61A182B9E0320ULL, 0x8854D310566BD453ULL, 0x6C095E295BD2B18DULL, 0xA030D5AAF1D23916ULL, 
            0x2E5F90565E18519BULL, 0x4294FFF2A2DF1892ULL, 0x141EF7CB54940A9CULL, 0x21506EAE3EB2298CULL, 
            0x23E190C45EEDF088ULL, 0xDC8A3865E96AB404ULL, 0x15AB1F25CCCCC1D6ULL, 0x78855CDE9458DC60ULL, 
            0xAA5DB7EA0EDB1FE7ULL, 0x89BBDAD4286442BCULL, 0xE9BC8A3ADA87A7A1ULL, 0x9307F8240A6F70F1ULL, 
            0x6CDFDA4E44B0B965ULL, 0x2CB0AEACD5D2369BULL, 0x9AAC382BCE189478ULL, 0xC46F000756932956ULL, 
            0x6FEDDF7138AA8D4FULL, 0xC0861AB7563F24CCULL, 0x904CAC57CAECC431ULL, 0xC37FB892B40F78A6ULL, 
            0xFCA4AB869F30673DULL, 0xCBD1FED885782D49ULL, 0x60A3A5353F86B069ULL, 0xCD0B40E38E59761EULL
        },
        {
            0x1A331E548F0AA224ULL, 0x7BF4E5D1D854D475ULL, 0x563492B09DD02ADFULL, 0x3C8833822D3FD0F6ULL, 
            0xF1E54A1C4A1BC0A0ULL, 0xBB8DBCF9CA90ACBCULL, 0x343BEF4631D0BCDBULL, 0x0474FCC9D038CB3CULL, 
            0x5B2E06C6FF7C108BULL, 0x3AE23B04F775DB3FULL, 0x54140B7D066D244EULL, 0x5B1B9100C3D656F0ULL, 
            0x153E3BA29BD2EC15ULL, 0xDDEC153891F42E37ULL, 0x095635769731061AULL, 0x0CD99D80DAA1A690ULL, 
            0xCDE7108A9E8646EAULL, 0x2A3AFB8B103A6AACULL, 0xF8ED7DF4016823FBULL, 0x5F4C99B9709F8347ULL, 
            0x9EC571F086867DADULL, 0x7221F3EA0237D1EDULL, 0x1228137515D238C0ULL, 0xCD49A387EB9F01E1ULL, 
            0x3B2E3446F947207AULL, 0x255DE864F7C16AB0ULL, 0x4E075E8733E78C56ULL, 0x7FE05188EBC44F36ULL, 
            0x918977238E409E3AULL, 0x8D7E52078A216854ULL, 0x2C68FE2B15353CBDULL, 0xDD07E1D049F9CC5FULL
        },
        {
            0xEC325A093D24B50FULL, 0x3A340EDF1CAFDFB6ULL, 0x04B758ABCB91A102ULL, 0x4B8E2BAD1B141AD5ULL, 
            0xAEED316D93EF03F2ULL, 0x7DF64FD78983681EULL, 0x9B6F48BC4D88052BULL, 0x2275B7F363D5F5C0ULL, 
            0xD67A10C5D847A6DDULL, 0x743F291E5EAB00A8ULL, 0xCCD7CEE34924C268ULL, 0xF682F66BB1FA5F5DULL, 
            0x399A87AF6EC3DA23ULL, 0x5ED2D0227C058A24ULL, 0xF4D764642B397268ULL, 0x58452CB8719F3B9BULL, 
            0xCE0A0FABCA8C3AA0ULL, 0x2BA57DF27BF6FAEDULL, 0x0BF03B0999259572ULL, 0x2C5E78F61FD6FE80ULL, 
            0xD6B64A29F5888A5EULL, 0x11AFB1032F34799CULL, 0x69BF888A05821549ULL, 0xE57405ABE4723350ULL, 
            0x334DC5F1B97E7165ULL, 0x853C9A03D4ECE279ULL, 0x9F681C3901E02651ULL, 0x949DAE95B9DA0271ULL, 
            0xB7437E38F64BFDF2ULL, 0x2BFF9A6758C76D4AULL, 0xDFD96D1A8A38185AULL, 0x166D072DF5C423D9ULL
        },
        {
            0x9189CAF5E310367CULL, 0x3748DB99A3A30310ULL, 0x1F5C27CDED4CBFD2ULL, 0x322FD53863285AFBULL, 
            0x6ACB6CB8CF6EACE6ULL, 0x1476AD74309DD75FULL, 0xC65476D721CC39F4ULL, 0x2B8477CCF68A187BULL, 
            0xDCF191AE173F9179ULL, 0x06635D41435B3B73ULL, 0x7537DBFE9E6709ECULL, 0x6034097B0FF9D9ECULL, 
            0x38B0609EFED22994ULL, 0x08487180EC3DAFE1ULL, 0xE1403DE8EDEE1791ULL, 0x3AABD85DEBE487A9ULL, 
            0x21030D1467B2C763ULL, 0xCE41AD6B660A8CB8ULL, 0xDCB43A740C4FF6B3ULL, 0x06C5F7D684A6A716ULL, 
            0x9AFB32A3502DE10FULL, 0xF80F7C32A4F4F776ULL, 0xD90B6DEC1C75DB13ULL, 0xAFB1E1905B78D10BULL, 
            0x32004F3C03BDCC7AULL, 0x3B8511888D7EA535ULL, 0xA8E27631BB5A75BAULL, 0xE0FBD9263DF2F776ULL, 
            0xA739726E1F827672ULL, 0xF9236C11727B2441ULL, 0x5BD1930974115E2CULL, 0x3AD6A3B5C624B4D2ULL
        }
    },
    {
        {
            0x908BF82A1C9E634BULL, 0x3A946886F931916EULL, 0x12E451A1B37686ECULL, 0xEB33EB37665DC429ULL, 
            0x01EFD4942BEEB6D6ULL, 0x7A3A233A5DF0BE9DULL, 0x9821769C6EDD42C5ULL, 0xAB4525479C9CEA9AULL, 
            0x1BD681054393B7ABULL, 0xE116D74FA1496B81ULL, 0x0CBF0948ACE82BC5ULL, 0x3529F99A0D4104F3ULL, 
            0x4525AC4738D66FF3ULL, 0x7B95B340B40183CCULL, 0x5159BCD36B96FD2EULL, 0x7F59AB9D3CF44EA3ULL, 
            0xD23ECCEF4759A684ULL, 0x78A3A4E217B482F4ULL, 0x41DE4527566D9822ULL, 0xAA42FBB5E6A45EA2ULL, 
            0x5A857BC3D1498CD4ULL, 0x8AC511EF796E985FULL, 0x7070D8FC9488380DULL, 0xF9EA411E2E3438EDULL, 
            0x356736A3ABEEF757ULL, 0x9A38FC373C6FCBD2ULL, 0x371B2B618C859378ULL, 0x3E0D090029F6B5F0ULL, 
            0x8F95708BCCE85363ULL, 0x5BCCA4C1FD56350BULL, 0xEE9E52A469C5F4E3ULL, 0x5D37ADC41D02A4F3ULL
        },
        {
            0x5F164D6F23202DF2ULL, 0xE60FC6F0061CDB52ULL, 0x56570C2F126B3F4BULL, 0x618402B72D6DC638ULL, 
            0xA40FDDA1989F8C63ULL, 0xAFA0189337FD81B1ULL, 0xD4D7E53924C0EF49ULL, 0x23EED1289BDB2B50ULL, 
            0x945A9CBC6491C868ULL, 0xDF9078105084783AULL, 0xD5BAA3AC56D40606ULL, 0x66AF25D5026CD80BULL, 
            0xE32E66CF4D18D4BAULL, 0x70DF61C41AF5C9CCULL, 0x7D25A968C90515C4ULL, 0x89B12306DEA0030BULL, 
            0xE713FD3F433B7257ULL, 0x5638A03840CBEDD4ULL, 0xDBFA211CB8CDED08ULL, 0xFC5A870D44FC2726ULL, 
            0x34C3FF6951159FFBULL, 0x8090FE22FC55E2B6ULL, 0x107271154FA482A6ULL, 0xEEC45B9EEA722913ULL, 
            0x2095EE049B8F09BCULL, 0x3744495C310972CAULL, 0xC9D9B3C0B67A0E5EULL, 0x492DFD7EE414E0FEULL, 
            0xB78887BEEBF721A4ULL, 0x4D0C665F3067D91CULL, 0x4FDAE8DE3B1A18C2ULL, 0x7F94B564AD189708ULL
        },
        {
            0x1B51E1D649CCF230ULL, 0x72E97CC42908E9EFULL, 0x7554D3FC9567D902ULL, 0x8C9F6E286D9EC06DULL, 
            0xC3CACF69537DEA1BULL, 0xE07136E2136DC67FULL, 0x3C2C056153AE26A7ULL, 0x6572B9ED7F75C191ULL, 
            0x65E70FD15E1AEC47ULL, 0xD6FB1FFEB6DF1DBEULL, 0x0A2A1AE5414B0094ULL, 0xB75CEB83F9865C3AULL, 
            0x634BC1EF4BCFB6E2ULL, 0xE94F03288738943AULL, 0x9A186DE0F7612A49ULL, 0x006A39C2E705AD28ULL, 
            0x70D8735D2882212DULL, 0x839E80CE08C879F7ULL, 0xFE6C92D40E2750FCULL, 0x9974B8A4B723DD55ULL, 
            0x3B2F9D2D7A0C06F4ULL, 0x1FB47914082C8B60ULL, 0x1AF410A11795F88DULL, 0x08FBF447EFEF9C02ULL, 
            0x60442D89CBA1F799ULL, 0xFF414FB8A4D06E6CULL, 0x63551EB7F7D4BEDAULL, 0x4CA6BA69327B0656ULL, 
            0x31C595DF6D807909ULL, 0x992D0DEAD0CA66E6ULL, 0x31E0E25D40A66512ULL, 0xED1BF15472F35A04ULL
        },
        {
            0xB4294E58A7965C5EULL, 0xD46836FAE441D5FDULL, 0xD7B89B2DEFF7B4FAULL, 0xFC1CF8680A9C56E5ULL, 
            0x736032B7A994281AULL, 0x57C71F272DC24101ULL, 0xEA7CEFDCFA50232FULL, 0x1484910ECFDE6A1EULL, 
            0xF1273D6E124357BFULL, 0x83AF3AA6563A4E9CULL, 0x9FC4BFAE3447A358ULL, 0x9BCA7EB93594DF7DULL, 
            0x557CE64F16E6B481ULL, 0xB15B0798DECE15F4ULL, 0xDC39A1DD5A1FC504ULL, 0x1615AD0DDA1FABE8ULL, 
            0x06B9B04278B02CDAULL, 0xFB23322BB6A6CA8AULL, 0x3D65413BE9037B39ULL, 0xF48EF7C454529FCBULL, 
            0x2C1DB25BAAA53DE0ULL, 0x02FBD0E6DE1C27BEULL, 0xEBDE4A6E15DDEC1BULL, 0x64F83EE41EEB09B6ULL, 
            0x3D4F94739769977DULL, 0x57506467734372D5ULL, 0x3E805AD91C2B0406ULL, 0x9F6A1331CAB5EE75ULL, 
            0xE2BA03F3AA2DCF64ULL, 0x3C39E5392E73D652ULL, 0x085E945A7EF5499AULL, 0x5CEFCD04BB7C7595ULL
        },
        {
            0x2376870A9ACBC1EEULL, 0xD4A279AB3026EF50ULL, 0x5D68EE9603165E9AULL, 0x3092315038CAD950ULL, 
            0x49BA63B33AD0F30CULL, 0xA1CCDEFD5C4C9D5BULL, 0x39A9FB88A5CC49D2ULL, 0x86D1DEB0C532A753ULL, 
            0xC92EA7B52AC36088ULL, 0x8BE6D6534361B4F4ULL, 0x6561E1F77A9E6DE8ULL, 0x688E8F1073C96E99ULL, 
            0x4D6C42A62BD4787CULL, 0x8396A1F26E402370ULL, 0xE5B9ACF32ED5E54DULL, 0xBD2A7F8C4EFE5012ULL, 
            0x2EF2839A984B9D95ULL, 0x5EF2620FC16C2911ULL, 0xE7106E1311F4D24DULL, 0x753F127BFF22F7A4ULL, 
            0xAC6CFEB66F94C623ULL, 0x30AC6674F9F7A662ULL, 0x3BA84C0A10871E8FULL, 0xAB8D9870C93953F1ULL, 
            0x82F8984F940A9BDFULL, 0xD932E5156A816A38ULL, 0x65270319F1EEB856ULL, 0x0EDDCBF732126D33ULL, 
            0x2132A2D986B95231ULL, 0x43C54D148184429EULL, 0x191E89E1A24BB6F2ULL, 0xF700C77EEC681B73ULL
        },
        {
            0xD6CF36277F1D1428ULL, 0x5CCC3AC739B27CFAULL, 0x75109F9D10D5EA00ULL, 0x05A475D78D0DF5CDULL, 
            0xC58F05E7EC8AC527ULL, 0xABB17CEE5002AD63ULL, 0x13C2896631750E04ULL, 0xA0184BAE9C1A9278ULL, 
            0xF5A746D1EBA495ACULL, 0x1A2A882205E7F178ULL, 0x2FDF888D3DB4A08EULL, 0x69AA3902A1B219EFULL, 
            0x36C1C6BC745C52F2ULL, 0x03AEB2912163D2D5ULL, 0xF158D5785EA1F87DULL, 0x83C9D6527799CF84ULL, 
            0xFA23150EBEA892A5ULL, 0xDB10C8FD341FE123ULL, 0x0A90916B9227551CULL, 0x1C9A51F142C14E5BULL, 
            0x5075DCF0CA13C91DULL, 0x5524149A4F2BD912ULL, 0xEC8115946D3B0CC2ULL, 0xAE7B4181FCA9CE7EULL, 
            0x118E9D6434614C20ULL, 0x6C79AF846C5A8216ULL, 0x774D4CB4712F7C81ULL, 0x9B99CEDD366DCEB0ULL, 
            0x2736688FD0F3884BULL, 0x93C91731F160AF5EULL, 0xDEB6433B950DC33DULL, 0x46C2F2F5969BA9A4ULL
        }
    },
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
            0xA463C7917A09FA04ULL, 0xEB46FBDC6082D1D0ULL, 0x72CC0100E20F646DULL, 0x0FDEA27F62CD5B28ULL, 
            0x3A0E147F65C41950ULL, 0xD9AED50DCF278258ULL, 0x1D6BB8A358880D84ULL, 0x3212EF11CF219B82ULL, 
            0x02F37EED2DE8781CULL, 0xA13E55D3696A7D5FULL, 0x47F789D1D8827EA8ULL, 0xA29665C3C6E1128FULL, 
            0x58F2C65A45D11AC4ULL, 0xACDBB29ABF458C95ULL, 0x4C7DE40B323193EDULL, 0xA7CDD0CB0D321A3BULL, 
            0xF7633C717BFDAA97ULL, 0x79AB33D5ACBA3800ULL, 0x571BB0088FABA67DULL, 0x16427A580D19622FULL, 
            0xBC9F2A693F0B4237ULL, 0x0349786D2A769695ULL, 0xC38F3516F4D59A51ULL, 0xFCB5C0601F511328ULL, 
            0x2D8E1B0549785458ULL, 0x9CF459315A0F836CULL, 0x01DBB04D887FA5F2ULL, 0x3C08049E4ADD77D9ULL, 
            0xD4FD9B475C545017ULL, 0xCB8134B3C3DCC5ECULL, 0x773F1AAB2E9AF5B2ULL, 0xBAED954EE58491E2ULL
        },
        {
            0x008E6C1BFED6D573ULL, 0xD47A5A3FD2CC83E0ULL, 0xA014908E5CC38503ULL, 0xB196ACBC44A4F350ULL, 
            0xEBCB1DB337D4A17DULL, 0x29E25EACBD86DA17ULL, 0xC3B33FEEFB7C0EF9ULL, 0x9C1C5AB3AFE3A1B2ULL, 
            0x8681D0607D741AA2ULL, 0x4CAAFB9986E28525ULL, 0x129B562C578282FEULL, 0xC9AD367238590259ULL, 
            0x8E8295926FAEC180ULL, 0x1CCFBC306CC67FFCULL, 0x2665683F25BC3889ULL, 0x997D835D94F0C52AULL, 
            0xE65FDF3D2F662B4CULL, 0xEFF2D6839009B259ULL, 0x7016966E91B67287ULL, 0xACD423E818A9DCF2ULL, 
            0xEF34CDB99AA72EF7ULL, 0x41E0DF39B330994EULL, 0x7CA628DEF5951DD5ULL, 0x759C747B9BA659ABULL, 
            0xDB218ED2916B3100ULL, 0xDC2F82D568A9F0E4ULL, 0x70296268A6FB2C77ULL, 0x1A0F2380862F4CD1ULL, 
            0x636404C91286D0A2ULL, 0x3A2DB656BD492800ULL, 0x986D9D9A20D4FDB0ULL, 0x4FB77B4308AC7771ULL
        },
        {
            0x0F8FF23E2F7EBEE6ULL, 0xBB2EEE9FBE161A3CULL, 0xAD7F69AF7F7C79E2ULL, 0xABA7660E29F53285ULL, 
            0x0E159C3FD181465DULL, 0x176C309599F43CB1ULL, 0x614FA72983F644D5ULL, 0x23584F56B1DBD4E6ULL, 
            0xFF3E69D98B4545AEULL, 0xED3347D1338EDF46ULL, 0x62D7D2D9C6A61EECULL, 0x6B3E1E1DE139CE6BULL, 
            0x84145892FF070FF4ULL, 0x8DB994D1B23FD448ULL, 0x4EA843E6ACA787D0ULL, 0x049BBF028472B5D1ULL, 
            0x33C46D5C548AF84BULL, 0xE208021F8E1BD9ADULL, 0x50EBAA39E892601FULL, 0x9328F2C5DEDA5FDAULL, 
            0xA160AA0F63BD0F35ULL, 0xA9CB16FB1846B9E7ULL, 0x6DAD9D242DC4F0C0ULL, 0x90F299EAA5A32D00ULL, 
            0xD723419145F2E3FFULL, 0x606A49CCF444EC99ULL, 0xDC68EEE166D7511DULL, 0x703F1611300FCBC5ULL, 
            0x53B93900B8796289ULL, 0x88AF8372126F557FULL, 0x4EB6444DC1122E15ULL, 0x51AEB2F68E489BA8ULL
        },
        {
            0x294DAEE0D0DED865ULL, 0xB60D78E5B144EDB7ULL, 0x143EE6164463936EULL, 0xF0C4A6D9E77F88CCULL, 
            0xA110E3C455D92F7AULL, 0xF44F78CFE0AAC3EEULL, 0x669EF795AFF01B7EULL, 0x1C6D69C03EF72793ULL, 
            0x79FE351864550437ULL, 0xAA3B374F287F0616ULL, 0x1C71816B419DE883ULL, 0x3F28A503A36079AEULL, 
            0x473BC5CC5823AEEBULL, 0x353DA068598C35A6ULL, 0xE2B12D63A8413151ULL, 0x9DABB494CD10ECDDULL, 
            0x06E24F3178E46A75ULL, 0xC95A1203D92ABF07ULL, 0xC2524DF171E439E3ULL, 0x88FC64A5E7E6A82CULL, 
            0x475B94B38ED88D02ULL, 0xC6F4D5C8CD1798D0ULL, 0x948F1798B1B1FD2DULL, 0x6A133531C64662BCULL, 
            0xD4A8BB18023F5C12ULL, 0xC7056061E1F4ECB4ULL, 0x35F7D65E9CD17D37ULL, 0x7E26744E2E5FEF8AULL, 
            0x8CF1FED284E78093ULL, 0xC992C05D7953A153ULL, 0xEE7FCDFFC7692ED5ULL, 0x15978142A958063EULL
        },
        {
            0xEDB945E84CC2D72DULL, 0x767339E88892766BULL, 0x6522134786FFFA77ULL, 0x1F8748BE9A4521A3ULL, 
            0xBDC15A5E01D11B4DULL, 0xF12F8DCD0A116054ULL, 0x9C229A121DDFFE90ULL, 0x3D113EE93304B3F7ULL, 
            0x342F3C3AE0FCA29AULL, 0x9C760FB52969A79FULL, 0x4C93178EBC229D11ULL, 0xCAE640FCD34FE5EAULL, 
            0x042FD3C238E6503EULL, 0x2877822B17E9DA35ULL, 0xD8D00E074E902AFDULL, 0xA3E2B0D2A9774ED5ULL, 
            0xAF01026F5170A292ULL, 0xA4079A55353AC1ABULL, 0xA3B365B8CC99C9D6ULL, 0xF91EBAEA7FEEB8D5ULL, 
            0xB6F93EA63CAC52BCULL, 0xA527000161770C85ULL, 0xC38950B72D5A0BA2ULL, 0x0BBBDFE6B9AF6E6CULL, 
            0xC693E66DD20B6928ULL, 0xC2203E98FD79F630ULL, 0xA20AA6684841F923ULL, 0xDC740F89049385E6ULL, 
            0xA168AD647DED8E28ULL, 0x74A0AA7C3D130603ULL, 0xC1724D6DF85BE70EULL, 0xA8E6C9B617A6C968ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseDConstants = {
    0x2F282F66D8CFDF31ULL,
    0x2B4666E85F991774ULL,
    0xA3036172A1833C9AULL,
    0x2F282F66D8CFDF31ULL,
    0x2B4666E85F991774ULL,
    0xA3036172A1833C9AULL,
    0x81ADB9992F247BDEULL,
    0x1FBC7DEBECB0DC1FULL,
    0x59,
    0xB8,
    0xC2,
    0x64,
    0xEC,
    0x7E,
    0x50,
    0x74
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseESalts = {
    {
        {
            0xF61435895C80B029ULL, 0x70618FA4ADA73055ULL, 0x991CA2F79B7E80F3ULL, 0x0F56401886A039E2ULL, 
            0x2B3362008B08B7BAULL, 0xA0724476888C8446ULL, 0x9CBC52B240173FA1ULL, 0x087DCD3BA1479EAAULL, 
            0x17132402DCF4247DULL, 0x1C0CA8C2B815814EULL, 0xDE02F486533D2F56ULL, 0x2E8F8B48C9ACCE84ULL, 
            0xA11577B3A68AB0F3ULL, 0xAEE045021A74BB34ULL, 0x27585136D8883BEFULL, 0x9039BA589A797A50ULL, 
            0x6EEA5AE713E4E65FULL, 0xD9FA659EBFB5D9D1ULL, 0x8FF6DE5589D25B70ULL, 0x71581A92FAEFCAF2ULL, 
            0xC8A4876DF30A76BCULL, 0x6CA486D71C6021C5ULL, 0x8D349479834CF818ULL, 0x47834E2A245D4E42ULL, 
            0x85C5CC3B6CEAB2CCULL, 0x3B4A9171B24C7B16ULL, 0x5C1AE997CF018113ULL, 0x5BFA853AB2748563ULL, 
            0x32BA927F9E7E2E87ULL, 0x86ABDD41E392C140ULL, 0xEDDE2E576E59B470ULL, 0x634E4A324B4A4C7AULL
        },
        {
            0x61BB5AA11E53DB02ULL, 0x0660686ED2DF90C3ULL, 0x9C31A638A9E7E2A2ULL, 0xF85C612D0D8AA42BULL, 
            0x1F2B9EB3993242A4ULL, 0xC5F52986C97D059DULL, 0xCC4E2CA99BCF0A4BULL, 0xC83D3F5ED8BFC090ULL, 
            0x7BE138D6119E98C3ULL, 0x903C05A0B3196267ULL, 0x1DA3AD8953932C0DULL, 0x2F5417B2A4B677DAULL, 
            0x7F1E2246F75B6F7EULL, 0x819DDC5EFE6DA4EFULL, 0xBBCB760B13FA0703ULL, 0x4168F21B81652BDBULL, 
            0x9AB3B9E20478B751ULL, 0x8D00CAD37B56C77BULL, 0xB035A0A11DD1F041ULL, 0xE57562DBF73B22B2ULL, 
            0x7FAF74B14D51F903ULL, 0x5E7CDB574E29A86AULL, 0xD91F830E6E915C89ULL, 0xE695966A5D6D999DULL, 
            0x6BE35CD559A6F758ULL, 0x3452215689465D72ULL, 0x30E05362A646ED62ULL, 0x7A3A0A0C22E4149EULL, 
            0x422A05DE3A4DDA6BULL, 0x6C142098D9FE66EEULL, 0xDFC72269FF7ADC9AULL, 0x063ECE9C87E3FD2CULL
        },
        {
            0x3DDA1BA29E797063ULL, 0xFFCC17258E0A1C37ULL, 0xCDC500BF9FAB17FDULL, 0xD10732F11C6DB334ULL, 
            0x21D3A5E51318E001ULL, 0xB824AD6673603487ULL, 0xF6076F0955EB05D5ULL, 0xF9961FB15165631EULL, 
            0xF1E5CEE524F334E3ULL, 0xA1AD1B57D7F0EA5CULL, 0xB996D82293F00876ULL, 0x49E24CD3E175B869ULL, 
            0xB31A1A6F17219C70ULL, 0x9706FFC70500C249ULL, 0xC97E194922423DD6ULL, 0x050F8457D98AA5D1ULL, 
            0x012F1FB47FEC592AULL, 0xE39880E15FB97A6DULL, 0xC84C68707BEEDB07ULL, 0x0DD91A1FF1F73957ULL, 
            0xBEB566F0C598A494ULL, 0xA558C97756B83DC8ULL, 0x9A4E3B6CD75EB177ULL, 0x9B0AB073FFBCBB72ULL, 
            0xBC552D1A973EA5B9ULL, 0xC9C7E6DD6A8FD7EBULL, 0x2458957BB1DA58B7ULL, 0x9DF8333CDD856AB1ULL, 
            0x4B8FF244DE868888ULL, 0x23A5E36EC11AA697ULL, 0xD3D42BD995F28A68ULL, 0x633302B6EE90146EULL
        },
        {
            0xDE37DA089C7C57B9ULL, 0x1B6623912B1E7D9AULL, 0x7F9743878F701833ULL, 0xB74AD1A4D4450BB6ULL, 
            0x27C12A5706004C1EULL, 0xFF9A1693A7E3684DULL, 0x5E0BD77CE885F255ULL, 0xA7593EB49D5952DFULL, 
            0x1FDB0DC0C24BD9D5ULL, 0x2F7958C1C286DF84ULL, 0x72313A7EE6FE27F7ULL, 0x97CD972E26E86EEFULL, 
            0xFC4AE4C565B3E978ULL, 0x40E185E0F8998E36ULL, 0xDD7DCC9E4DE572A9ULL, 0xE6C18CCEC82B5F3CULL, 
            0xD4A5478215352004ULL, 0xCA65A8ABC3F3E3C3ULL, 0xF5074E36FA3F2C76ULL, 0xCB9A578F6D719BB5ULL, 
            0x50A0FE93EBFBFA64ULL, 0x8EF0642D901DB6F6ULL, 0x927D93E1F2C9A33DULL, 0xDDCDEC478AEA7CE2ULL, 
            0xBE573A4912C6D522ULL, 0x6EB2427DC2DC3C4DULL, 0x5D0EC566A575AC1AULL, 0x6856D011D363D977ULL, 
            0x5ECAADEEAA0064F2ULL, 0x317FE6A7139A371AULL, 0xEEB70A37485EAAD8ULL, 0x63311A240DF476C5ULL
        },
        {
            0x70F0A9F682C1F385ULL, 0x4C86062D1F711237ULL, 0x875045DC9DAC99C7ULL, 0xCC2B1103EF35EEA8ULL, 
            0x67A2F96CE7BA9A35ULL, 0x05E4465838AB7549ULL, 0x8CDECC36F3E9E82CULL, 0x10EC84E32C4F232AULL, 
            0x7114EB601978344EULL, 0xC5B4E66B1E73F370ULL, 0x4245ABA6D0902092ULL, 0xF246D059B5D170DEULL, 
            0xB03F5895D7C16DA3ULL, 0x8F9DC652B88087F2ULL, 0x1D521122ADA0C0CCULL, 0x6E02E2887FF01C99ULL, 
            0x4D7230569DA1FC6EULL, 0xF5226E596CDE887BULL, 0xB46BD0EE135F309CULL, 0xE02C5824655F416BULL, 
            0x86C901C59E848C35ULL, 0x4BDC7374553778CDULL, 0x31A5F6304042E780ULL, 0x1B51B603C35AE89AULL, 
            0x8542E83BE15503A4ULL, 0x4FD6B1BCE5040844ULL, 0xA50691D30DCE65DBULL, 0xAD27BCFDF44B27CBULL, 
            0x1BC9B423C968AF6FULL, 0xF04EC1C4606B2BA8ULL, 0xDD0E541E85C62C71ULL, 0x8263718E94F042A1ULL
        },
        {
            0x0B2305781481AE16ULL, 0x437DFA8131E6EF60ULL, 0x015A4AC0BD447579ULL, 0x5E308DFAD9EBCA72ULL, 
            0x6628837ECF796D93ULL, 0x4A355F7C7105EA91ULL, 0xBCF52C269DDB562FULL, 0x1DB485C33966376CULL, 
            0xDE428CE58B800B19ULL, 0x33F31D7C9594FE01ULL, 0xDD1D8CEA9DC50771ULL, 0x375B1E3D21678185ULL, 
            0xF03230E6D295D075ULL, 0x353E11D9EB155B95ULL, 0x803CAAA4E79F99A6ULL, 0x0AD1840366470D08ULL, 
            0xBEC6B260E1C1614CULL, 0x2553FE5AFD9CE459ULL, 0x9F35D9356924EF4EULL, 0x018DFACD0B778D9EULL, 
            0x6674CD4BC34C50B7ULL, 0xD9903F5872888995ULL, 0x59AF278FCEAC804FULL, 0xB8E16F6740A930CFULL, 
            0x5AC198DDE454F4C0ULL, 0xF035B3EDF9BCEDEBULL, 0x225F900F399956BAULL, 0xA9531D8466E8D35AULL, 
            0xE0E5409C65C6A75CULL, 0xB31F50A2667CED39ULL, 0xE93E0CDF04A7D141ULL, 0x97AFEB145FAEE70FULL
        }
    },
    {
        {
            0xD1DB423D69476A2CULL, 0xEA896B424144EF8AULL, 0x30B11911C08E8EE8ULL, 0xB0587B871AFE108EULL, 
            0xC6852B02BED66AB1ULL, 0x5E58FF2F51BCE305ULL, 0xD5ECA043BAF0C3E2ULL, 0xBC483382B238F8E9ULL, 
            0x5CADEE6324A998C5ULL, 0x5D9C7F08CB035414ULL, 0x7D8DFFB74FD2B8CAULL, 0xA622D291FF8EA8BDULL, 
            0xBCF03BD63A705F1FULL, 0x5F026325849C1002ULL, 0x2CA39395CE300950ULL, 0x879B4407542FC83DULL, 
            0xA868DA947725FF9FULL, 0xEF9B29B87D7BF0CFULL, 0xF2930564FCC55AD2ULL, 0xDD5D099F03291C6DULL, 
            0x0328173820F50C99ULL, 0x3A5EE871C8A7A4BEULL, 0xF26877A18D2B78F3ULL, 0x820A41A7EE19AEFDULL, 
            0x0AF6DDAEE938EEEDULL, 0x123CA58D1D11FE13ULL, 0x00672541AB350982ULL, 0x3AA6A4AB441843FDULL, 
            0x332D82B0BF1C387AULL, 0xADC6635BF5D07AB4ULL, 0x53056A3F868D9475ULL, 0xDA433285EED4771CULL
        },
        {
            0x4B16CBF02AAA19BAULL, 0xEF44473907E4CC3EULL, 0xEDF4447EEFEEFFB2ULL, 0x1CFB72978E33C41FULL, 
            0xFA1D78242507635BULL, 0x11D9D6CE7C2E3589ULL, 0x1244D2A3CFF188FBULL, 0x5AB13C7B4253F083ULL, 
            0xB82D56846EA4F45AULL, 0x0237A2FD8AF79C73ULL, 0x44E8C84840BADF7EULL, 0x7B7B48A3C44A1CD7ULL, 
            0x45726465C7E9758AULL, 0x6B49264D7EF5FE32ULL, 0x3C3DB7BE2F8D0E6BULL, 0x9B705E671EBB6574ULL, 
            0xF6761C1FD371B9CFULL, 0xDF643FF713751CCEULL, 0x0BD8F43A3A3A1BB6ULL, 0x43E1C1E1451A5A85ULL, 
            0x7B5B9BE6E84625EEULL, 0xE7274C91E0E49D14ULL, 0x4C2A4E906C1737CCULL, 0x4FB9E52382C9E583ULL, 
            0x95AEFE53CB946A87ULL, 0x7A1DF5C1CD21C3D1ULL, 0x3AEE9051C0867F70ULL, 0x396126146FBCA378ULL, 
            0x48415E079115617BULL, 0x55BB55FB0D6B1ECCULL, 0xC88034661E0C4360ULL, 0x2630970378A40D30ULL
        },
        {
            0xF3F2AAC47A90BDC9ULL, 0x098B80EAABAD1E12ULL, 0x9F05DC0205560405ULL, 0x5F3B1C46EDC5D9E7ULL, 
            0xEE657754B2F6DE67ULL, 0x9E8E4F0F6D1CCBA2ULL, 0xA97C87A13963B5E4ULL, 0xF061D8325BF46408ULL, 
            0x81B0B9BC376EA41AULL, 0x3F3B38E7BF2DD25DULL, 0x612239B7847311D7ULL, 0xC6ED0B43F7F0B9F7ULL, 
            0xD51B7D446AFC89EFULL, 0xCC36CE984D199E8DULL, 0xF90463740A02F9E5ULL, 0xBC4558A8268E2708ULL, 
            0x242179856D169A74ULL, 0x5A5BCB058411F27EULL, 0xC810830F82E822F1ULL, 0xDDA198E9988CD5FEULL, 
            0x5971B604F4D7E8D0ULL, 0x7CC2C5B18811043DULL, 0x73433A0D4F9B7F82ULL, 0x7489AB6A14ECD206ULL, 
            0xE1F7893BB9607453ULL, 0xF852263E569BE0FDULL, 0x9FAAAA3276ECED33ULL, 0xD5DCA4E069023606ULL, 
            0x0ABDAE42C14F3869ULL, 0x9A7C24B56707559BULL, 0x92FC0D014AA63B64ULL, 0x5CFCF640CF6C5FF8ULL
        },
        {
            0xD4B657E3D129E6BBULL, 0x3AA0A82AC4AA415AULL, 0x24C072CCB29654D8ULL, 0xFAACDD8AB92E2D99ULL, 
            0xDF403E6646F3F970ULL, 0x95B59C4E77E3E38CULL, 0xFF9C5D68ACCEEF07ULL, 0x8CA3B098722E17B7ULL, 
            0xF165F69DEEDAB4B5ULL, 0x3BAC0B4129F345E2ULL, 0x2C82BAC37F0DA812ULL, 0x7F9B19A5F8D1983AULL, 
            0x0F520612B6EA4F9EULL, 0x99F96902FDDA735BULL, 0x68877A4B71E37AF9ULL, 0x3260F1BEE24D32B5ULL, 
            0xB8B121BBEAEC6AF7ULL, 0xAE2D805FD8C1DD48ULL, 0x19889A83F072A6CEULL, 0x3B9BC75C3ECA4D99ULL, 
            0xA48B214D8E3651FFULL, 0xA7381ABF28A1F9D0ULL, 0xD589BE1ED3BD06ECULL, 0xE2C59B0C5CDD1FF3ULL, 
            0x5AA32DC6D80EAF66ULL, 0x292FC1781FEE99D2ULL, 0xE451DF52B2291388ULL, 0xB6866C6E2B208159ULL, 
            0x2225ED91517B3E1CULL, 0x9E3399C5938B1945ULL, 0x4CF1DBD9D92D3AC2ULL, 0xF861146CB23FEA55ULL
        },
        {
            0xE69CBDCDB3CD4D92ULL, 0x47F792206E8D782AULL, 0xB483A08D449F2C67ULL, 0x132E83FB40957ADAULL, 
            0x9408620562CE2A45ULL, 0xAD2225B13456EFDAULL, 0xF5D5AAB2549C2666ULL, 0x8BD6F3A288F01F4CULL, 
            0x4053436676878036ULL, 0xEDC4B969D4E3E68FULL, 0x0177389C6BE6F6FDULL, 0x3D1C5889ADE9D0DCULL, 
            0x1C3D42BD7282E300ULL, 0xF5B793011FC84DF3ULL, 0x57238B59D341488CULL, 0x4DED61C76DCE0B66ULL, 
            0x2FF2BDC519108F92ULL, 0xFAD81C5332F86E9DULL, 0x9F26B3BC1B171749ULL, 0xFCCDC3B9F67C8352ULL, 
            0xBD66B1CABA1071A7ULL, 0xACC6435EA129CF2BULL, 0x9B87702E0CBC84F5ULL, 0x8AF6A6E6969084BFULL, 
            0xEEF6D175215332C2ULL, 0x4D335F45411D33F1ULL, 0xB22D498167412221ULL, 0x1FBBBB84FFDF4C7DULL, 
            0x2D3B3F855FAF8509ULL, 0xCE70BC9BF6034AFAULL, 0xB1EE926DFF29D60FULL, 0x5D564161C12D2173ULL
        },
        {
            0x9841B65E27EAD64EULL, 0xD41C4983E58D1BC5ULL, 0xB4DDE65FAE46FBACULL, 0xF9A00082D170085DULL, 
            0x2978A1B16EFB1172ULL, 0x8F71176939F482F8ULL, 0x88F53E776AC28313ULL, 0x55A5CDFC255A067CULL, 
            0xC87CC72071FE4F1EULL, 0x2C04B3FCA8BF3987ULL, 0x8BF9C7D2DC0BA566ULL, 0x0AD0813CA2114E50ULL, 
            0x539EFDC8B814D643ULL, 0xB3B1E82AC1C8E96BULL, 0xD7469929DD0DEACFULL, 0xDDBB6E3060B0DA85ULL, 
            0xF5168FF79428D89AULL, 0x5E8E1210A3F6B0B1ULL, 0x5ED2268321658B4DULL, 0x0BC2D4DA819AC2BFULL, 
            0xB54A4AB9BEDB41BBULL, 0xF00013A97FBDE2D4ULL, 0x728D6A05488F86A1ULL, 0x1FC3C4989A87D887ULL, 
            0x23D7EECDF70576BEULL, 0xFCD34019F7C372B5ULL, 0x41366DDDB8333089ULL, 0xD13A5BAF2D218A7DULL, 
            0x4303B725F9D4A6FEULL, 0xBBDA253464C7B18DULL, 0x40A5E0701DA3DC4DULL, 0xDBF847CC58F36D3DULL
        }
    },
    {
        {
            0xB5D291B3F358968DULL, 0x5FEC6497EAD03459ULL, 0xC97F8E2E14E56D61ULL, 0x7B958F8CFEC67C62ULL, 
            0xBEC52758F6E8C919ULL, 0x7E10B48ED16C67FFULL, 0xE33CEA9210BDE927ULL, 0xB3E9B918C5BDDF20ULL, 
            0xF6B32BE40AB21D9AULL, 0x12B715281FADE53EULL, 0x0FBBD4C36402E62EULL, 0x5FFE6EAA9CF6B60DULL, 
            0x64A6A6F652F52DE5ULL, 0xDACE96C69D97A5DBULL, 0x21D8DD136646F3C6ULL, 0xF16AA1DC31F522A1ULL, 
            0xBD49BA77408A7E43ULL, 0xC7387232F355F380ULL, 0x9190D77ADDCDF8C4ULL, 0xC237F6EFDE1EDF1AULL, 
            0xA5C090FF4F91B529ULL, 0xCD9C561D2AF9AA2AULL, 0x58ED916304281422ULL, 0x156F2485D5472ED6ULL, 
            0xF8CA8DEE93A41DFDULL, 0x6E3BF51F63E87B95ULL, 0x01DC3A4DAAEDDD4AULL, 0x022577B48A7EFE92ULL, 
            0xBDA27F60C4746CC1ULL, 0x3F5C8788266E9F11ULL, 0x08812BE0128DAFFDULL, 0x83AEA1B32AB80861ULL
        },
        {
            0x11575D7717D8CB96ULL, 0xBF06C320EC82BF34ULL, 0x420E5C9AA03B3E7AULL, 0x0955D1B87063A013ULL, 
            0x385AC3417EC3F708ULL, 0xA6112ED4828882DAULL, 0x3F602CE4C656412DULL, 0x497F7C65A95DC881ULL, 
            0x9BA65AB1A794E5EEULL, 0xEA4E65ADD65D11EAULL, 0x17326B7B09ABA178ULL, 0x539A428ECC7B0C34ULL, 
            0xA85F2780CC2169FDULL, 0xCC3EB012526D20EFULL, 0x4B1FDD53B22E7E0BULL, 0x2D29053B9BEF165AULL, 
            0xE9895D7FD557193BULL, 0xF6C7A32F9A76E818ULL, 0xC6F71804EFA490D9ULL, 0x76AB0F44B8B02B8DULL, 
            0x3DFA13273E99A118ULL, 0x931752B6A8586598ULL, 0x1877EE6562683392ULL, 0x2AA11D141EC97683ULL, 
            0x43645F49F50F3A27ULL, 0x8AC6739452C3FBDBULL, 0xC50FFD2706A3A992ULL, 0x334152831AB55EC8ULL, 
            0x6763ED347648585DULL, 0x4CF5D8E02CCD8F83ULL, 0x396F40AFD9145493ULL, 0x39CC2AD3EF29E196ULL
        },
        {
            0x28000E1EBCC740BDULL, 0xDBB60E45E00C222DULL, 0xD024881D8228CD1AULL, 0xC75A3304B84D3700ULL, 
            0xB357DD5911C1458CULL, 0xA993D09EB5EB2E34ULL, 0xC628F3B3A1EDB12FULL, 0x07CA0747203DA88BULL, 
            0xCEA636B78A2FF452ULL, 0x1FA165F23245B56EULL, 0xDF5C62AAF54F72B1ULL, 0x832FF45B5FD32698ULL, 
            0x1ACAF0B5F24957C8ULL, 0xACC66CE8ABF670C1ULL, 0x5DB6FEAA16581B58ULL, 0xB9D339412F9EF1AEULL, 
            0xCE6CA79F919352BAULL, 0x53160A2407544239ULL, 0xD9B14752590C0230ULL, 0xC470A1246FFBF553ULL, 
            0x6CA8D79B7154FBC5ULL, 0x195B86A753FCBBB6ULL, 0x30F36B4C1B3CEE27ULL, 0xE7545E3DA3720E15ULL, 
            0xE30C5BA619404DFDULL, 0x28CB2E5CFDBED812ULL, 0x5294CBF282B8B0A2ULL, 0x1A6376B7E01569BBULL, 
            0xBCE4CAD1E00B9622ULL, 0x45A2D95959847035ULL, 0x9FF78E376101EC4BULL, 0x9FD04C33C34A31F1ULL
        },
        {
            0xC6821C0F117966BFULL, 0x08A7A2D97BAAD8B0ULL, 0x42258D4314FBFCD4ULL, 0xD9A69F1E723886C6ULL, 
            0x96147AC105B35972ULL, 0xEC0586B4379BC773ULL, 0x67D999D717029F92ULL, 0xBB7D48BF5A9E74ACULL, 
            0x6273FB55DDA606B6ULL, 0xA4A8B95928F86A53ULL, 0xC2E244F29D93DAF1ULL, 0x4E44E2A66056B5F1ULL, 
            0xDEF5859FCF553942ULL, 0xD1B416200B6D6D5DULL, 0xCA6A83AD4DF409D3ULL, 0x493540237768636CULL, 
            0x6DF6BFFF0D63B71EULL, 0xE55D7FE006D55E9EULL, 0x8D07BE3EC3E73D10ULL, 0xF7E10756F8AA2C06ULL, 
            0xC8A08E8811E1F240ULL, 0x26A715F132C66DE3ULL, 0x706877488EC9E5ADULL, 0x2A5345D6531C8766ULL, 
            0x5074746B33C52063ULL, 0x466C214D415A4312ULL, 0x774A5B53B4E0024BULL, 0x444A0E87CC073EF6ULL, 
            0x0E9F9390A57E5B2AULL, 0xF686DB29335F533DULL, 0x4A64DF8FF8DFD11BULL, 0x46F85165F7887F5BULL
        },
        {
            0x1C69A8C6A60F3895ULL, 0xB994CF5A64A18CE3ULL, 0x28C7F65C7FEE391EULL, 0xA7A95586B2C8B8D4ULL, 
            0x130059230CF7F1B8ULL, 0x20DEBED043D26875ULL, 0xB085F9533B895C33ULL, 0x6BC51AE8D83F7E56ULL, 
            0x944C6DDE4162CE9DULL, 0x62D5EC6E0D4D3B23ULL, 0x95ABC4069E26AB80ULL, 0x337ECC11A0397603ULL, 
            0x325319E9F390FE60ULL, 0x92E392533D853C0CULL, 0xB7DA259CB5644BA3ULL, 0x1C448991280155EEULL, 
            0xF9A9E82C7DBB3330ULL, 0x43989EEE751BA24BULL, 0x0619EE27FDA494A4ULL, 0x7089AB3805218F56ULL, 
            0xF6F4E34A28B873ADULL, 0x107EF96803D88E4CULL, 0x70F33985B88B6DE9ULL, 0xC6EF609C17EEF5CAULL, 
            0x215B4E23EADA0200ULL, 0x16C0BEFF84416640ULL, 0xC22C1E36432DD670ULL, 0xE64B3A21CBD47393ULL, 
            0xE76016C067E49B80ULL, 0x68220CDAEBF8524CULL, 0x2ECC431820ABC78EULL, 0xFC5DFFDF35113AF5ULL
        },
        {
            0x6F98A86D9EB0893EULL, 0x182AA4A730BEE3F6ULL, 0xCB684CEB01D19D8FULL, 0xD31B7044752CD336ULL, 
            0xD54DB9819CD8ECDBULL, 0x976B512515446EA3ULL, 0xABD51D34309F656FULL, 0x0202F98E048BA7D5ULL, 
            0x5DC4B3910FC241D8ULL, 0xACC63928D25F621FULL, 0x599EA2C56C2AB3A9ULL, 0x7ED203D8C984CA5DULL, 
            0x3843C92F3F979484ULL, 0xA4A206922D5167CCULL, 0x54347CE2C8AD71F4ULL, 0x2239717CE09BBE75ULL, 
            0x2432321788352BB9ULL, 0xA89B70C2716247E4ULL, 0x1EC5A7571CB0A304ULL, 0x5484D45C46E391CAULL, 
            0xBB3128A1A0A2A71DULL, 0xCFBC3760E630CAF4ULL, 0xEE9D666D93D65327ULL, 0x48CE4C022B8D6993ULL, 
            0x8B0856B717B3FE6FULL, 0x31625D15B544E124ULL, 0xCB11378B4BA727C9ULL, 0x0455D63346E6C347ULL, 
            0x55290E1655E7F44CULL, 0xD665EDBF67E2DDB8ULL, 0xA0B4B9A3A76BC22CULL, 0x561BA1534248A503ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseEConstants = {
    0x4D61E16A74A30FD9ULL,
    0xE89F8E6C705B49B4ULL,
    0x43AD41DB977D85B7ULL,
    0x4D61E16A74A30FD9ULL,
    0xE89F8E6C705B49B4ULL,
    0x43AD41DB977D85B7ULL,
    0x056A9C41FE905297ULL,
    0xE533C4F42662FC99ULL,
    0x8D,
    0x2E,
    0x15,
    0x30,
    0x14,
    0x8A,
    0xDF,
    0xEF
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseFSalts = {
    {
        {
            0xAFA5DCD0A41529D9ULL, 0x738AA2BC79B39117ULL, 0x556B6C34F40EFA66ULL, 0x5CDC0C615981D325ULL, 
            0x9B7AFAC7465D32C8ULL, 0xBE3A22993AADA980ULL, 0xDCA5B4228B23655FULL, 0xF881EC7796DE1BE6ULL, 
            0x5E2F213FE4627E3EULL, 0xFD808E29C683230BULL, 0xAC364DBC67429F0DULL, 0x7A71DB5D25EF15BEULL, 
            0xB02D29EBA22848C1ULL, 0x73EC705784E4D41CULL, 0xBCD951159FA93044ULL, 0x86465DF1DF1CC323ULL, 
            0x005B093946BC2C76ULL, 0xBBF51A7AF0C4EF8BULL, 0x58633C2E8197542BULL, 0x34DE3E8C29647B18ULL, 
            0x05EF7C544E6866D0ULL, 0xC6DF0DE40D25F5A7ULL, 0x9BF147008B462B67ULL, 0x11E49B7594FDEF31ULL, 
            0x0CF91135A15239ABULL, 0x14D378E30F1F695CULL, 0x62987E05EC7950DBULL, 0xCBA21706762790BCULL, 
            0xEC54934889830CAFULL, 0x395E5EE7B531EC58ULL, 0x6B4BD0655E059834ULL, 0xAD1D6CDCD028C769ULL
        },
        {
            0xAC5227608362C35DULL, 0x1D24AE537436F2F5ULL, 0x566A9F7A3EFBC3C8ULL, 0x19CD6B3AD57E7F7EULL, 
            0x04F4D745802D1639ULL, 0x1DB848CB825A7BAEULL, 0x06D287C9AEFA8E42ULL, 0x5E0549F2673C6105ULL, 
            0x57A57F250656A662ULL, 0xA4E8B35E1EA14833ULL, 0x841BB84CE7A6BD35ULL, 0xB0BCACBD39943542ULL, 
            0xDBC8816DE3151021ULL, 0x2DEBA258DDE82F78ULL, 0x6C8421A3D355A6AEULL, 0xD408B91EBB19892DULL, 
            0xCD55534492F00128ULL, 0x7B812C336DC7907CULL, 0x9FD40375C061185EULL, 0x57E84B3D14DEEDC9ULL, 
            0x420A017FBC16AE74ULL, 0xE920B6A77B5A0EFAULL, 0x4A5D4F7FDCBBD08DULL, 0x8C5454A38BB2E387ULL, 
            0x0697A628DB40141EULL, 0x87B142AE95D6D5E2ULL, 0x3F830A60591FC94DULL, 0xB35F26FEEBD592EFULL, 
            0xFB2E94467636B1DEULL, 0x95AFF364E5A927B7ULL, 0x4D3459D95B926968ULL, 0xABE077221E7A03D8ULL
        },
        {
            0x7DB88D0DCAC599FEULL, 0x307FF6DACBF91E47ULL, 0xE7E6E6058B21E2D6ULL, 0x0C85808656D1A08EULL, 
            0x792F97A9E23041B8ULL, 0xC8384AE9A694BD53ULL, 0xC829657CF098B885ULL, 0x7A234288E073FE8CULL, 
            0x61DCB869A81B337FULL, 0xC7D30C4BB9810F13ULL, 0x196D84EEEAFD77D4ULL, 0x1812A5B9B2FB7583ULL, 
            0xE34420391B39E4E3ULL, 0x031D75FF113A33FAULL, 0xB5430F0AF9564D67ULL, 0xC2CFECD60D7500A7ULL, 
            0xBEFE8F298A8B7591ULL, 0x5E38AD2392299C1EULL, 0x6671A7015D186A64ULL, 0x3EC029668703A004ULL, 
            0xCB395DBF40A53871ULL, 0xBAB96E83C3FAAC2CULL, 0xBC2A98C7474EF372ULL, 0x311E4B0E084E3175ULL, 
            0xC41BD40DD376C5F7ULL, 0x4F8B5128BC2F3DB0ULL, 0x7AFB244A5CEB008BULL, 0x3499BC15C220EF54ULL, 
            0x950C26DB2E1FFA94ULL, 0x7D8100B83372FEA7ULL, 0xE8647B086866254CULL, 0x812E4519AA99B7BCULL
        },
        {
            0x47C9EE21A62E1410ULL, 0xF96D114ECD62DCEFULL, 0xB85071D3256F8935ULL, 0x59A0DC0766C1431BULL, 
            0xFCC0C9927325353AULL, 0x7089DE1737E17D8AULL, 0x25CF6A7645329B72ULL, 0xE91B8B432097E858ULL, 
            0xAFC8F3FA9252DDB0ULL, 0xE7914221F2F6DA90ULL, 0x5E3FCE7DC7C04D4BULL, 0x013DE50657B28117ULL, 
            0x67D7595E099276D2ULL, 0x323992DAF98FEC46ULL, 0xB9FC05840705F3D8ULL, 0x73C94D2D2F31CB29ULL, 
            0x9D3D3413FB41B340ULL, 0x05FE8C96215C2E8CULL, 0xD9EECE51C4BC1110ULL, 0x830C1EA52FF2B6F8ULL, 
            0x4C0F22B419BBA551ULL, 0x3E1FED5A39826B60ULL, 0xF3996E8B30A87509ULL, 0x3B0FF5759464C0F1ULL, 
            0xAC6DFB5DA2FA3345ULL, 0xAE33714AB12103A1ULL, 0x59AD94EB4E057CECULL, 0x482F15DB50E9A48BULL, 
            0x2D0EB2CA501D3C1CULL, 0x7EBFAEEF8549CEC0ULL, 0xE82E039B0447F136ULL, 0x2A83FF8EF824CBF1ULL
        },
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
            0xF758322621D15B75ULL, 0x1061D620834AC7F5ULL, 0x4898887B7213B743ULL, 0x20968C131D9B0F72ULL, 
            0x07344D07BFC33D72ULL, 0x373BC2E2E543BBC7ULL, 0x00B0260011AF75B6ULL, 0x4E7B94F13EFBF701ULL, 
            0x5BA648F30402534CULL, 0x3C836BEA97539CD2ULL, 0xCE417D721D175985ULL, 0xC34F0766775FAD26ULL, 
            0x19E5284373641647ULL, 0xA1C2DFC83BA0AFDDULL, 0x7542FFB66C2972ABULL, 0x515C115569A7B844ULL, 
            0x1EBA8F0EA0180E05ULL, 0x5C2ABBF86BCAA399ULL, 0x527FB749EF5B98C3ULL, 0x643D044D6599FAF8ULL, 
            0xB2F742E779C62CF7ULL, 0x1C8081054945A69FULL, 0xC4CAAFD5E7DFFE61ULL, 0x9F3D0C8CAEDAACABULL, 
            0xB7EFC814FF6F68B1ULL, 0xF55C339D62A72490ULL, 0x0D803800D86270ECULL, 0x7AEE4870B002A0AFULL, 
            0x980BA38524CA68CAULL, 0x64D97137AE540627ULL, 0x1C91323CCAB3FE80ULL, 0x564EE2C72F3D4CBAULL
        }
    },
    {
        {
            0xABB884FFD85EF60CULL, 0x3CCF968F2078231AULL, 0x540B57F2AE8A0214ULL, 0x46CBF50A8D766D6AULL, 
            0x2A02164691FA04DCULL, 0xAD986C6B153F3DBDULL, 0x0C2673A5F28E4099ULL, 0x755DA32868B52658ULL, 
            0xF79379D252B26B9EULL, 0x6AECB6388F626FC8ULL, 0xC85BF5367D85640AULL, 0xCD58227A24095031ULL, 
            0xAD203EAE67DF210CULL, 0x6406A4E94C4DB166ULL, 0x70942EBB518298BBULL, 0xEDEB5D294AB6F23CULL, 
            0x37EC5FCC18988516ULL, 0x67CF772BDA015D91ULL, 0xF6772EF57DFCD8C8ULL, 0xE20982427C63824FULL, 
            0x5162CA305D56037EULL, 0x853B061738D367EBULL, 0xD5DA0AFAD35E3DEDULL, 0x05AA2866E2B292AEULL, 
            0x1FC3B8CF49B4051EULL, 0x4523DEA3796A8284ULL, 0xF921656D37F26D30ULL, 0x904860BFC8B13628ULL, 
            0xEBA0F8D3C8103250ULL, 0x89F6B9F3941B043DULL, 0x5E5E5E383AD5FB37ULL, 0x7FBFFC087DBD0154ULL
        },
        {
            0xE08B19906627C7B3ULL, 0xFC766DA6137CE573ULL, 0x5198BCEA41BADD3DULL, 0x4DC286AD86DA484EULL, 
            0x8FEB0C696E6BC30FULL, 0xFF73DF6EBAF2A5D4ULL, 0xD710F970EEC6A0B3ULL, 0xB443AF7F7803B759ULL, 
            0xB55DCF428C09AF02ULL, 0x4DEFA5A21B938001ULL, 0x492D0D9391E1393DULL, 0x16838969E34ED830ULL, 
            0xFAD26BD5F5E41672ULL, 0xD70796DC4187A50BULL, 0x3A7CB1C4514E777FULL, 0xAA1C976E0E98BAA6ULL, 
            0xFB3BE70B8B5F7D69ULL, 0x152D596DA7167E44ULL, 0x1773899B0E78604CULL, 0x69E6F1BA9C3D8AB4ULL, 
            0x430F386AA5703CBFULL, 0x0FAE28DA3BE1BCA2ULL, 0x4227569B84CAE5ECULL, 0x428A7965FADDF09EULL, 
            0xEFBF0C555508C94EULL, 0xC9CF19B5C908420FULL, 0x3923CFDC0C3B9124ULL, 0xE37CB65D726DE927ULL, 
            0x4E47574BD95F2DCAULL, 0x52B577FD8F524142ULL, 0xC4F7AB1AF37DDD22ULL, 0xE0D829D8682F8314ULL
        },
        {
            0xD1D8F1B4ED35278FULL, 0x12E4EA89861AFBAFULL, 0xD4EED89AB3FC9DFCULL, 0x1C9F5CCA82591ACFULL, 
            0x5F39B53A58356629ULL, 0xA17FC984F64ED80BULL, 0x8E2035F1C0794DABULL, 0x7284D57C572BBC62ULL, 
            0x3F813F3F4D5855DCULL, 0x04ECC6BB64CD2DDCULL, 0xE9FE7D0797B4215BULL, 0xA3051E70B8D3549DULL, 
            0xFADAB7BAE99AA391ULL, 0x845C5BBAE986E7BEULL, 0x86E113CC1DB5C026ULL, 0xEFB19BE779108486ULL, 
            0x71A38E3504E498A2ULL, 0x1FD88D080734942BULL, 0xD9E7D274EEA7596AULL, 0x12262A40FD171FD1ULL, 
            0x564182348ABCBB73ULL, 0xB2D00FBF9C45EFAFULL, 0xF22B7BB43BD5B5E6ULL, 0x21F718FCB1BB8BD3ULL, 
            0x8C61D5BA49859248ULL, 0x9480BDC2F56D4742ULL, 0x827541C2294E7F8AULL, 0xE930EACBA7250DB6ULL, 
            0xAAC6AA4167FC281EULL, 0x6473299C3F59D5FBULL, 0xE7DB32FB3B237960ULL, 0xEECED61482EB7D0BULL
        },
        {
            0x0C2E88B041E5D6B5ULL, 0xB6722EF5D1633C1AULL, 0x52D9C1AA75EC5B21ULL, 0x8D22D15ABB1A660DULL, 
            0xFE8F83AA5A083F5EULL, 0x4273B695705508DEULL, 0xFA37AFFB9BA30107ULL, 0xAED7470546ADD50FULL, 
            0x2A85877091462B4BULL, 0xC644D365F6AB1E7FULL, 0x1D298585B0A54A8CULL, 0x49706ED84A868C68ULL, 
            0x4E25B4B0BDC3ED36ULL, 0xEDF07286DECA096BULL, 0x92279212C3D15CDCULL, 0x6F2A2887845A4565ULL, 
            0x5FE6EF1FD19FB75AULL, 0x36F39CBF59FDAE6BULL, 0x58EF0B281CFA3406ULL, 0x7025B4272A0841DBULL, 
            0xE1B0DC4D38B414EBULL, 0x1D587CF9E752B875ULL, 0xC802E77C8D5E9B66ULL, 0x375309D1BE9C932FULL, 
            0xBE4FEB9CDE6928BDULL, 0x688F461EBFB58A1DULL, 0x75CF61BE7A58AB38ULL, 0x0CA5E2E2F07DC37FULL, 
            0x9AD7ED20C4B3C145ULL, 0x219209DB84F14C7AULL, 0x7903FF63044BDF60ULL, 0xF9C8EBEEAE3E3681ULL
        },
        {
            0x3F26929D0B51EFCFULL, 0x101710BC51E362FCULL, 0x91B0D49F682B9860ULL, 0xB0B597050DB4F089ULL, 
            0x9041FAC8FEBDFE6CULL, 0xDD1746F6C45A4AC6ULL, 0x69ADB38260DA678FULL, 0xCD8A20F8B68B6209ULL, 
            0x929EB74700CD6511ULL, 0xBDF566F597C35043ULL, 0xF6F28D68B976150EULL, 0x112E68A546D9E99CULL, 
            0xAA476728F171AEDDULL, 0x141C625E146FB53BULL, 0x34EBB3F183492DA6ULL, 0xBC422721E74B9AA6ULL, 
            0xFDAE73A2A38EE68DULL, 0x30AB9B93971EC7C2ULL, 0xF914E60C5CC3B197ULL, 0xEC686169E6C6F3AAULL, 
            0x9CD166B7B9D22787ULL, 0xE26479BFC211CCC8ULL, 0x44B45821291230C8ULL, 0x91AF5E606BAFC946ULL, 
            0x7840942F7FA9AB4CULL, 0x7883CB93F69F72B4ULL, 0x833CF0F2B112F4EDULL, 0x170D4DA5470BE767ULL, 
            0x0B3C8D6F7AB363ADULL, 0x373FC7BDEAA8AE18ULL, 0x4EE095C7061B3DA2ULL, 0x75D63BA42765F771ULL
        },
        {
            0x091F4BC773F5D8F6ULL, 0xB877BB856D577D8FULL, 0x8159BC5A901D6D28ULL, 0x283850B271CE07A3ULL, 
            0xD45CF9ED6D891C1EULL, 0x65DAD1BAB3DCB022ULL, 0x20638EDB72BA946CULL, 0x5E9F1474EF9AB740ULL, 
            0x72BD72FECF4D80DBULL, 0xF49CFB5DA5E4BD74ULL, 0x6947E7766C8D44F5ULL, 0xCD87A826D18C4B0BULL, 
            0xA7DE39AF97B03C01ULL, 0x94F1833DDC59E5D1ULL, 0x7F4CD827F5B38567ULL, 0xD3A4CF5BDF59EE38ULL, 
            0x3AEF1DCD70D82170ULL, 0xA7AE630153629FA8ULL, 0xB2099ED2F58F88C2ULL, 0xC99D80E8D559016CULL, 
            0x38E7AC89AB139433ULL, 0xFE81C68073090951ULL, 0x96AC5EFB4F5C0EC2ULL, 0x2108CB5409BE9C9BULL, 
            0x3F948BBAC93A2953ULL, 0xA21C9268BD8EC984ULL, 0xC8CAF97DA11AD8BAULL, 0x9B9A887E394EFD01ULL, 
            0x93A47F28F24247E1ULL, 0xC76BB16D5A1A5761ULL, 0xF6EAAE1E115CE7FEULL, 0x6529E4CB54E85EB2ULL
        }
    },
    {
        {
            0x8D5644A19B1C78CAULL, 0x711771399A05CF4AULL, 0x63E14EC0B1D93786ULL, 0x5F6FA0C7EFC05AA0ULL, 
            0xE0DF83762CAF8750ULL, 0xE8F1638FC8D8094DULL, 0xAECD5CF8EC2E6B42ULL, 0xD15BD27FB004A1C1ULL, 
            0x543CD0C253292EBEULL, 0x55FA303DACAF67A0ULL, 0xA977F3011C72B34CULL, 0xC41D7C3C2646E7C1ULL, 
            0xAA14A0E0558DDDEFULL, 0x11FA25D0186058EEULL, 0xA7B7B5DBC04680F3ULL, 0x6C4D61A8BF144C64ULL, 
            0x39D7FF4EFBB7C135ULL, 0x7F76F2825C6ADC58ULL, 0x10E9D6860ECE7203ULL, 0x1F56DFD92E7282FFULL, 
            0xB6711437C3B0B401ULL, 0xCB4E2BAAACED86C3ULL, 0xB10C9170BD230BFFULL, 0xB8632DE10ADC6ABCULL, 
            0xD914C6B8FDC7D454ULL, 0x485543C5B60A7E00ULL, 0x5BC55B411CBE4A51ULL, 0x7487E8DE11EE2837ULL, 
            0x7A4DA7681D3D3042ULL, 0xF0FC0A36EB97E279ULL, 0x40CFC9AFB9B6048AULL, 0xF657723C347FC875ULL
        },
        {
            0xA7982A6B3A8F167FULL, 0x20B26DF6C8967989ULL, 0x6080125BED3255F0ULL, 0x378BE2E8B5F24212ULL, 
            0x940A6C72C5488B64ULL, 0x1EC783687BCAAC63ULL, 0x3261490644DAE1FBULL, 0x315821ADB6E48C23ULL, 
            0x7816374349CC5729ULL, 0x29A99F2AE0E07D84ULL, 0x8471AF517B1550C7ULL, 0x95B6FC1697839954ULL, 
            0xD3908CB10BFA244FULL, 0xE129BA37E2BDED08ULL, 0x69E8FCC48FD2DC9DULL, 0xC54F425F07D852CFULL, 
            0xEDA8FE6B29F72095ULL, 0xE6EFB50FA77C86ACULL, 0x3953537B81FA616BULL, 0xE0C647D9FED5C5A0ULL, 
            0xF34F944705197F07ULL, 0xD0D31A5C7CFB19CAULL, 0xC2D8B2880C1B9986ULL, 0x87508ACF20E3CF5EULL, 
            0xB932B78D4BEF6112ULL, 0xB7AD5C336762243EULL, 0x3A669B1B88247F8DULL, 0x238D19E6E7510F75ULL, 
            0x8981E56C493CA799ULL, 0x2B904B0F8AB022CBULL, 0x498CE5828DBCD8C0ULL, 0xB18368F6514E346FULL
        },
        {
            0x3EC4051C381D0252ULL, 0xCE3E77ADD12F3711ULL, 0x1B360A3DA8FF3811ULL, 0xAD2267C598E5296CULL, 
            0x7F9210BCEAC90D6BULL, 0x17B5E5B0A06153CEULL, 0x6E336716A99B891BULL, 0xBA594FD4219175A5ULL, 
            0xE783CB288A907E59ULL, 0x2DF5AD74364B9DEFULL, 0x518C779BB8E066E2ULL, 0x0FAE7F2779FDD545ULL, 
            0xE98C7E0BAEE5BFDBULL, 0x0CB2590B41A72F72ULL, 0xD0DCEA3F8989F5FBULL, 0x2391914EB4422EE2ULL, 
            0x8722396E5B890AFDULL, 0xA25607789A1278B8ULL, 0x768B0F50D916EAA2ULL, 0x1FEB9B07A7F9E802ULL, 
            0xA744A3A512F9E36EULL, 0x4AA4ECF30FEF2BCFULL, 0x20A5A559DE7401CBULL, 0xFA8CFB764978848BULL, 
            0x3181D0B9DEF79C97ULL, 0xC082299F90CF3168ULL, 0xA365CEBDF7FEA3D7ULL, 0x77C79EC1A6624BEDULL, 
            0x64D42F50C547E293ULL, 0x8A34FF9C8C674768ULL, 0x6E8E2E0ED89A1B15ULL, 0xE71425F9D84A47AFULL
        },
        {
            0xCECC4C98E1DAB5AFULL, 0xD4452F2261372DB0ULL, 0x63627C06B3D94BB1ULL, 0xB1F4A8CFF8ECCC61ULL, 
            0xD078DB1C229EB5DFULL, 0x28AD9EA864A6848AULL, 0xF2493310FC0DB11EULL, 0x99DFAF2CD8727FC1ULL, 
            0x7E289AD0E90890BFULL, 0x354D6F94D60C4463ULL, 0xC15477952D915145ULL, 0x0672484CAA0C91A8ULL, 
            0xCD73E3C4B8D18F44ULL, 0x32EF25C0B26A118BULL, 0x8E6687B1C2E4C805ULL, 0x2EED2A001D6EF88EULL, 
            0xF7076E1F3F258AF0ULL, 0x17B67A24CDF29770ULL, 0xAC018F3A81C0CD88ULL, 0x2F40E46F9C53EDB1ULL, 
            0x3562B2B2F829E4D0ULL, 0xA7C9693B76C8E4D3ULL, 0xF3CC0B9915352246ULL, 0x7934BD6A2AAC065BULL, 
            0x3DFF3D315624426AULL, 0x8237FBD311943D90ULL, 0x4EA7D444AD69ECA5ULL, 0x268C6C5491F6224EULL, 
            0x371292BAE2FA8745ULL, 0x293EF6CBC4693DC0ULL, 0x81D26B4E8E2C98B3ULL, 0xF92493F02096C6C5ULL
        },
        {
            0x09C51FC824D43FF5ULL, 0xC77F286C54424B2EULL, 0x594C9FEF939717FCULL, 0x6CF359A860FBD913ULL, 
            0x5810433A97B6D64BULL, 0x560F78E8ED33DB0BULL, 0x2B746536DE35DA47ULL, 0x2C564378C4FDBCF7ULL, 
            0xE54D7A044D97FE1BULL, 0xF2CEF2EFF9E82005ULL, 0x565FA8F0E8395AFAULL, 0x15313C040B3B213CULL, 
            0xBC0F9989DCE923F3ULL, 0xC482A2851EB7A66EULL, 0x6E0BEA376ABC7418ULL, 0xDE0FD312BD94D124ULL, 
            0xD588902D91FA70CCULL, 0xAFDB7576BD2590ACULL, 0x132C9332801F7A31ULL, 0x82ABEAC63B580755ULL, 
            0xAC9702F5E1BE291AULL, 0xBFBC63DA08BCA347ULL, 0x616A5C5ADBDB07C4ULL, 0x69A9FD30F76BA484ULL, 
            0xA355F296B9EE824CULL, 0xDB1C46432F414E21ULL, 0x904630AE541E9716ULL, 0x4361D2C2403DFED7ULL, 
            0x18B8AC9034C4EE25ULL, 0xBD58DC4334B98CCEULL, 0x39728ACEC8193850ULL, 0x7090D212896B24A6ULL
        },
        {
            0x7C3B0873C80AC017ULL, 0x5B34CAA00B526885ULL, 0x44BAE0F91300C6E7ULL, 0xF7DE19C1DEF491D9ULL, 
            0x687024399A27C31CULL, 0x17C4C35445362738ULL, 0x9A6CA56F979F39C4ULL, 0x358685CA64779806ULL, 
            0x3A51035FF6F314B4ULL, 0xB3667ECEDF250272ULL, 0x6185F2FAA789DAC8ULL, 0x921C21874D3A4CD7ULL, 
            0xC58C1BB0F63D0CC8ULL, 0xEA8D5E1CA6D0E3A2ULL, 0xEEA8FCFFEE6CAA3AULL, 0xA082D79047098A27ULL, 
            0x5A37114AAEC05EC9ULL, 0xFD1427EA2633A87FULL, 0x6C0646D324BF7EF7ULL, 0xA56C9284A0D09901ULL, 
            0x996EC577DD600550ULL, 0x5B033B727FD57762ULL, 0x35F50C8DF2BB8DD9ULL, 0xBFF9F968BF906EF8ULL, 
            0x722E67992BCF7438ULL, 0x353EA083A77A02B3ULL, 0xBAD0B403206698BFULL, 0x6E48271A0B31E706ULL, 
            0x4FFBD4F0350505CCULL, 0x8DE99024DD6636B8ULL, 0xB2EF995FFEE4AD9BULL, 0xA00976D0E05B892CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseFConstants = {
    0x3379914475B7250BULL,
    0xE00E539F46A5AE04ULL,
    0xCC093EC03748952EULL,
    0x3379914475B7250BULL,
    0xE00E539F46A5AE04ULL,
    0xCC093EC03748952EULL,
    0x2AA26155F9EB8B25ULL,
    0x118E4F637D9564C0ULL,
    0x78,
    0x53,
    0xE8,
    0x1E,
    0xC6,
    0x33,
    0x0E,
    0xBD
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseGSalts = {
    {
        {
            0x1DC1467DD447E4D6ULL, 0xB02A01E3CACAC494ULL, 0xBED354ACA9E2EAA5ULL, 0x118A8579443CC165ULL, 
            0x8E1361853B46DD05ULL, 0xD8AD61C334372920ULL, 0x973070553A989FC2ULL, 0x683DA45F63265A08ULL, 
            0x9B0834198AA351EDULL, 0x9A1B8FAAF4494AEEULL, 0x95DFFB3D5BF003EEULL, 0xF79E5452740CC4D0ULL, 
            0x4EA5D4829B057B31ULL, 0x47967B62158FBF56ULL, 0xF9486388476E25BAULL, 0xDB5E35A511BC5866ULL, 
            0xEB67C6CD235D44BCULL, 0xBFA41AE4F02EACF1ULL, 0x35BFE05F37608CA9ULL, 0xD496CB0F2B29140BULL, 
            0xD4AFA68A4390C3ADULL, 0x3B04FE88E7AB1029ULL, 0xABF0FF473B56C56FULL, 0xF0F9FA31894E858EULL, 
            0x3CE6A8EA230FA665ULL, 0x1DD2DE2D5C60163DULL, 0x24DC25AC1C3F3CBDULL, 0xD7CD228F44C4AF6EULL, 
            0x5C9DC1C2749B23F6ULL, 0x23FF2E50623B144EULL, 0xF8865BB07B55F027ULL, 0x6A1EEA2E579951E3ULL
        },
        {
            0x12B232A55234A7D8ULL, 0xD135FFE254A9AD9FULL, 0x5AD099F4EEBBAABFULL, 0x75CA7E4D0F556FA4ULL, 
            0x04D0F418955A5F24ULL, 0x00279FBBEE692565ULL, 0x64F85CC40E42417EULL, 0x899C5C86AE9141ABULL, 
            0xA902D1498550FD4EULL, 0x9C9C4220263EA5B2ULL, 0x457B5B517B80DBA7ULL, 0xE94EBC178FD6EE69ULL, 
            0x87F1417A0D4BFB08ULL, 0x81B0301DDE89A4EBULL, 0x4DD81F4725583AF3ULL, 0x3EEF305D2CB97723ULL, 
            0xD651C3B1BD6D908BULL, 0x38A6808668CB1F91ULL, 0x4B8DA20C1E233687ULL, 0x7F602E6785D8E185ULL, 
            0x13DF258811336210ULL, 0xD7685C2292CB03A5ULL, 0x1A5521C5A8912697ULL, 0x6652ED470627F0A7ULL, 
            0x6479070B46530A36ULL, 0x16E17ACFB50388F5ULL, 0xB769A766AE44E224ULL, 0x9C4FCBE831042B7EULL, 
            0x8C9A2A582FBDA059ULL, 0x1858C9790FF802DBULL, 0xC4C4E0F02E0E099DULL, 0x8571A09AB961B57EULL
        },
        {
            0xE2A91032D34DF05BULL, 0xCEE72B25900CACFBULL, 0x15F49AF212642A27ULL, 0xEB981F1044E80D07ULL, 
            0x02C88A00A067BF00ULL, 0xB7B33DEE0EDA46B3ULL, 0x36AAA1CB6192A0B7ULL, 0xE0551378479284DCULL, 
            0xFC04E8090B87CC47ULL, 0xF334E5AA38300B97ULL, 0x1324834AEB2DFE36ULL, 0xBD1CE6D943958099ULL, 
            0xD443AB9BAEFEE5DEULL, 0x95377BDFB27B7FCDULL, 0x6DD358D3E83957D3ULL, 0xCCEC51D1D0F22A5FULL, 
            0x17A14431488BB294ULL, 0x6436018CE264113EULL, 0x3D732BFB7E14058CULL, 0xE1C54C53B2DD7F09ULL, 
            0xC07ACF0E5DAE4998ULL, 0x52DCA46DDC0C3AB7ULL, 0x55C9F43F706BED3FULL, 0x9B1B4EF771DAFAB6ULL, 
            0xA2F24B26CA559DD2ULL, 0xF9681387324AE418ULL, 0x6311E3F384A8BACEULL, 0x5601E78DA66BBD2BULL, 
            0xE92FCF12337F876DULL, 0x3A1BC992E7199B01ULL, 0x9DCE1EB4E7B8D241ULL, 0x6D605D18FF1669DBULL
        },
        {
            0xB674219D8AD32A98ULL, 0x19B5BFB1B8129952ULL, 0x062BD13568E1C596ULL, 0x33D7823D05589E4EULL, 
            0x54CCBCB5CA9FD93AULL, 0xF666C6DB10D29A85ULL, 0xDD2F85198DAE3DF8ULL, 0x54774BBE8D6B6987ULL, 
            0xC3F0F36E8956F4F8ULL, 0x1BBDA75970A16B25ULL, 0xFC4308F21D0F3053ULL, 0x34460B9E8105EC36ULL, 
            0xD8018BDF570E7CD0ULL, 0x2EEBB3A000732C1AULL, 0x7308B78F2CED8A35ULL, 0x90C868120FE18A8DULL, 
            0xB3B58D647C078B34ULL, 0x4CEA65492F0FCDEEULL, 0x10F52AABBA2ACA32ULL, 0x5D9FD90ED83AF0C9ULL, 
            0x6DBBCBAD8DBC30F1ULL, 0xC13A70411CB1D674ULL, 0x794561604476D93FULL, 0x752547D7683B3850ULL, 
            0x998CD801EE55744BULL, 0x2D2B148F01DA95D4ULL, 0x0918B910CC1C4B01ULL, 0x43E71A1D9445AFA7ULL, 
            0x72B78B6A17B7A06DULL, 0x6BEAE44F9BBB162AULL, 0xE3CEFC9F9FBE7952ULL, 0x07358B36BD8C520FULL
        },
        {
            0x0A40693F69FB6853ULL, 0x88535F476A121C53ULL, 0x3A41AA24AED88411ULL, 0x043791244CBD85A7ULL, 
            0x14DC8A3ACC39D438ULL, 0x795794EE5AA4733DULL, 0x5C694D05929E6D37ULL, 0x39B82644B30AE55DULL, 
            0xDB82748798D6883EULL, 0xA5060CD2678EFB20ULL, 0x8C0364A2F7DDF207ULL, 0x3A026BEF61D81946ULL, 
            0xCAAA7C5741C6F4BAULL, 0x0A91F080B4C2A478ULL, 0xC41CAA415650E609ULL, 0xE133B1193BB8AF8FULL, 
            0x9BC2A705E8FC1ECDULL, 0x456BF4065CB36342ULL, 0xC6CBD29789D4505AULL, 0x8FCDB129F5BCA072ULL, 
            0x275B43269ED0D2FCULL, 0x300A186D63475805ULL, 0x9898A63E09367AE4ULL, 0x0B26481D60FD5F4EULL, 
            0x20E9370DD7393717ULL, 0x166B2F21B0B70C29ULL, 0x9CEA194682BECB40ULL, 0xBE1C352A3549C6C9ULL, 
            0x65B87F53DD0BEDA5ULL, 0xEC2855ECE094A7A5ULL, 0xECDEAD4C7AC216EAULL, 0x3D72E07BEE6AB177ULL
        },
        {
            0x04D4E099492E9562ULL, 0xEBD41E93C7A82D0FULL, 0x2555C1480F904E6BULL, 0x2590ED1B6E6635A6ULL, 
            0x4FC76D2E8DAF1732ULL, 0x7A895A0BCAEE19D4ULL, 0x22935AC6E1A92723ULL, 0x6DF43245B10B9099ULL, 
            0x6F57AA82F565E5AFULL, 0x4DB47F2D0508A245ULL, 0x2129A87C199065C0ULL, 0xE77749547A507A06ULL, 
            0xD824FCE73448FD72ULL, 0xB73893229DCBD6D4ULL, 0x16B05C4CBAD8A830ULL, 0x5629612C39A73A05ULL, 
            0x3D3F4975CB1B682FULL, 0x29C442BA1388E6D6ULL, 0x441E150EB10D47C5ULL, 0x7DB6C70A42912C47ULL, 
            0xEFA7408E6E73E7A6ULL, 0x3EE7F1134E22CE17ULL, 0xCD1A4986C332806EULL, 0x7996DDA216AA2EA6ULL, 
            0x4DEA6964AAB20AD0ULL, 0xD7B73667B043381BULL, 0xCCE64598493C1BD2ULL, 0x99C070993DCFD21DULL, 
            0x7B65D1EE28091971ULL, 0xF76019CFCC5588D0ULL, 0x82DCF9B9105D1BD7ULL, 0xADED7B0E868E1353ULL
        }
    },
    {
        {
            0x795CD2E7E2478EBFULL, 0x26B1F78FC13B900DULL, 0xEAEDDB8DA3D01BD0ULL, 0x9E0CF0F2971FE899ULL, 
            0x5490862BE6AB34E1ULL, 0x069C549C3DDA9F54ULL, 0x92D18D74CE313E7FULL, 0x3A3802D143BC9E70ULL, 
            0xE3E5E86DF004481AULL, 0xE95D8AB0F29127BFULL, 0x16C26504D170DA69ULL, 0x0B06EED04BBA00A6ULL, 
            0xD2D1F1B2667597C7ULL, 0x9972245837122776ULL, 0x61FA28397CE00554ULL, 0xC9219445D3E9865FULL, 
            0xDAAD2BFC4F63CB23ULL, 0x527096DEA8E6D736ULL, 0x0602406B5E676292ULL, 0x5D08691BEDCA48E4ULL, 
            0xCD1D956AE178A674ULL, 0x7EBA4C9D093355CDULL, 0x350F97B6CC5BDCF6ULL, 0x814ACE57E974FE22ULL, 
            0x46D8900F8C5C7485ULL, 0x660FA49BBA21E1FCULL, 0x9D54CD44BDEFA74CULL, 0xF1AC5F35C52B909BULL, 
            0x5AF8A3BDA7EC1579ULL, 0x9FF4A03C204BA9F6ULL, 0x8381331C71820A81ULL, 0xAED5CE1A138A8F01ULL
        },
        {
            0xE42E46269E285C24ULL, 0x650CA0F8F5969764ULL, 0x9A8C705A1EA0AED4ULL, 0x07FCE2730EF05B48ULL, 
            0xF8AE910F21D3C7E3ULL, 0x44DF822389025749ULL, 0x202B9EEE5DD78CCBULL, 0x048562FFAAB4E756ULL, 
            0xC7A497A98A482FBFULL, 0x3F5859B658E11326ULL, 0xD87F022428AB254EULL, 0x371DC50E3740BC52ULL, 
            0xBF99AA6E290F52FEULL, 0x99AD64803B06D180ULL, 0x2199AA7122FD6D50ULL, 0xE07FEB4C3E07A055ULL, 
            0x5358DAE4CC36B165ULL, 0xD71A02A019EB857AULL, 0xA9F271B10382506EULL, 0x536AA37F3EDAB145ULL, 
            0x27801E5BF7425DFDULL, 0xCEDB307D419CC8F1ULL, 0xCF30ADB57CDFD085ULL, 0x436267D3A5CB68DDULL, 
            0x7C34D5BCDA65A2DCULL, 0x9242FF1308DA12A2ULL, 0xDA11EDF453FFEF62ULL, 0x9F4C41FF591CB360ULL, 
            0x35AFD2F55FC9DFF0ULL, 0x09115E5CD69D0DFBULL, 0x17555A43270F1FB6ULL, 0xA6FF195DEA71926FULL
        },
        {
            0x31116C1489F0C33BULL, 0xFF26A32B9E1F49D6ULL, 0x94D3B12F45D91CE2ULL, 0xC63BD95C460645CDULL, 
            0x2E6E6D829F77E50BULL, 0xB7631084E4DBBABCULL, 0xD2884C3F2D85DC02ULL, 0xD6C3FBADE0287DF2ULL, 
            0x454FF04763B27F85ULL, 0x918A57E33857310FULL, 0x3F41C5C5300276F0ULL, 0xD4768F0056DFD4ADULL, 
            0x65B5F77C4029B057ULL, 0xEDEA2B7DE418E3DBULL, 0xA5CC0672DADFEE2AULL, 0xC6409D91E365FFF2ULL, 
            0x9F8D9E01A2B56F4CULL, 0x304AF6C9ED7D6EFBULL, 0x497C07D8491F2C22ULL, 0xE524AA66FA9E9B1CULL, 
            0x7145367996F4002CULL, 0x68FF240B859F60D5ULL, 0x3BD810AC951A5A4CULL, 0x874C8A741C234752ULL, 
            0xFAF72871B5E8EFFEULL, 0xB2E7646B599B7927ULL, 0x3D29CC22C17E7408ULL, 0xD22612F570760A02ULL, 
            0x4418DE4EE71ED289ULL, 0xCB7770CD0F4B4517ULL, 0xA7A101662EF07B37ULL, 0xBB82C2D48842FCDFULL
        },
        {
            0x95E43547568B9DD0ULL, 0x8B4B03CDE0B0C12DULL, 0x07639BFA0FADD08BULL, 0x638EF1AF71032AC7ULL, 
            0xF3BC5C224EB0ED5CULL, 0xBC53C95DE68353A0ULL, 0x12B85A3FC51E73E4ULL, 0xBD723111BFA69AADULL, 
            0x08E6CE69E7F0B34FULL, 0x5D1167FAD192A7D7ULL, 0xDDFA61226630D3B7ULL, 0x48AC42C352B9AD88ULL, 
            0xB92BF75D82A7C1B5ULL, 0x17B4E9480D4D7B00ULL, 0x665D59A38B2270D5ULL, 0x532FFEBF3CCD5D53ULL, 
            0x640E5A2EFF696528ULL, 0x19003D234547C450ULL, 0x30F975D599864A9FULL, 0xEE241682FCC996CFULL, 
            0xE1D86E4AF1C00B92ULL, 0xBC9D23BC560B76B8ULL, 0xC3D7D169A678F5A0ULL, 0xFB76984C5F48EBECULL, 
            0x21F6C141088D1773ULL, 0xFDBECD1B5926461BULL, 0x7493E830A5C6166BULL, 0x6FB3042EA7B56654ULL, 
            0xA89FE48CABE41762ULL, 0x5E625C8820403897ULL, 0xE1980BFD74FDE156ULL, 0x892708B844E469E0ULL
        },
        {
            0x20311CECB2924A70ULL, 0x6FC3A8684C3691B2ULL, 0x5B3AEA07023BB71CULL, 0xD59C26EECCBA6FC1ULL, 
            0x9313360F65B5BB17ULL, 0x07E97119023D6BFBULL, 0x8E5331C1ACA2F14BULL, 0x02A6930ACDDD386FULL, 
            0x782011DC29899273ULL, 0x4CFE21CEABD9F2A6ULL, 0xDA6E37992BD152CCULL, 0x38D04CD460A2E1D6ULL, 
            0x7B760CDF84865EDCULL, 0xF559F4B8433E8547ULL, 0xE8BA4E1702585FB9ULL, 0x7B97B5F4CF13FD49ULL, 
            0xEDB9993D259D91C0ULL, 0x3938A4A53794C777ULL, 0x71945AA5EFC7BE0CULL, 0xF3EE189BA420F925ULL, 
            0xABEBB92B9B3657EEULL, 0x9494F8A5C942F037ULL, 0xD0744005B67FFC6EULL, 0xA632D00167912C4FULL, 
            0x0BA25C8878F48010ULL, 0x6ACD3EF9D1BF9BBFULL, 0x0CB3B2E264661100ULL, 0x9116E28E1C4ECA2FULL, 
            0xBB301CE0CBDAFE19ULL, 0xD1E29022F29CDBB9ULL, 0x2BA45771B5882ECAULL, 0x2B785F86E69AB9FCULL
        },
        {
            0x95E490C40B4217A7ULL, 0xC325C5EFDC5C665CULL, 0x8F829D71DD98E5D0ULL, 0x6EC19891F3662936ULL, 
            0xC67E7D76A1EE8EE7ULL, 0x5F16A6F0AFF2ED7EULL, 0x4782F3E630F3FA58ULL, 0xF28F9FE460BB0296ULL, 
            0x2AE3023628EB75FCULL, 0xC5E1741CC3A9070FULL, 0x611B29FBED939EC9ULL, 0xBDE55567EF1D3DBEULL, 
            0xE8B16EF5C3363FB7ULL, 0xA75381521B532515ULL, 0xFB0D1309874CB1BCULL, 0x53BFCB1792751252ULL, 
            0x1D08E51FE921953FULL, 0x0FFFAD39018CDF66ULL, 0x045CCB499FB32E98ULL, 0xE0FCDC4261045D01ULL, 
            0x8B4958352059747EULL, 0x0CEBE4F1189A88EDULL, 0xF0B1627DDB5F7873ULL, 0x834F905F43A6DB83ULL, 
            0x9D853322F85914C4ULL, 0xA5E30BEEEA229F47ULL, 0xA3D8359900B5764AULL, 0xF02B36D54D89FD94ULL, 
            0xF7A475D70ADFE6A1ULL, 0xFB06CFD5E2D8592BULL, 0xEC2516DE11107720ULL, 0x7EA6F5E277D38A71ULL
        }
    },
    {
        {
            0x77D7EB7901251097ULL, 0xA9A00D84BD361E12ULL, 0x6A38458D3544FDCAULL, 0xB2EA894108077EEFULL, 
            0xFBDEA52B553182F6ULL, 0xE3E7CA0C7A89448FULL, 0xDBBD98B9DD636C82ULL, 0x734F505DD920945DULL, 
            0xFE7FB65BD050ACD0ULL, 0x72D4A630DEFDE19BULL, 0x44CDEDC9659A44A8ULL, 0xE3EAB53D16517A00ULL, 
            0x8F642B132D471604ULL, 0xDA45CE57C4FB0FE3ULL, 0x0DE9A6C4B0261611ULL, 0x676CD8B7C90A10D2ULL, 
            0x9CC278ECA0C5626BULL, 0x9DFE6085FA2D380DULL, 0x46048593CF16417EULL, 0xF25784A9581B07DBULL, 
            0xF7D902F6B2C0C4F3ULL, 0xF26E082CFBB5BD8BULL, 0x6E36E824FB6A2971ULL, 0x7B586B77CF35AAD6ULL, 
            0x48BF68B3ED7CBBDEULL, 0xBBF67801AA276BAEULL, 0x6FC8531E8E5ACB30ULL, 0xC1134580432C782BULL, 
            0xA23790F6A6866C79ULL, 0xEB261A1D2F606138ULL, 0xC7360C1E13DEA88DULL, 0xF08F1AEB0EFB6CB2ULL
        },
        {
            0x91E59179DEEE4729ULL, 0x2F00E08809898306ULL, 0xFBDD1A11F90E0480ULL, 0xEA308CB6ABC06215ULL, 
            0xC844FDFF9AB3CA44ULL, 0x3BCC0E3594B404DEULL, 0x6E8CEC617873EBA0ULL, 0xDAD4C2AA79C00F9CULL, 
            0x885AB5ED93D81453ULL, 0xD7C327977AE35C1BULL, 0x4545F1117059C3FBULL, 0x23031617C18A3ADCULL, 
            0x476BB624455B1F65ULL, 0xD57E2C866EBB9529ULL, 0x2FB01EF1870C0D55ULL, 0xDB3F2BB47C558E64ULL, 
            0xE48F0A9D84143D57ULL, 0xD7F0AD4C5BB8656BULL, 0xE504679189D62606ULL, 0xF691AF5671DFBDC8ULL, 
            0xFA36FA3906670FC7ULL, 0xAF2BA7A1D1A59CC8ULL, 0x425854A0131FB6DAULL, 0xCB445412DA2ADFCFULL, 
            0x3D3FFBB48207CC81ULL, 0x5265B7B399C5B5F1ULL, 0x245621266228107FULL, 0x6667E0B8B72F05A2ULL, 
            0xA118D0C74D25FCC4ULL, 0xF2F82E2279B0E963ULL, 0x821F1C7BCBE834F5ULL, 0x3969B4467F978DB0ULL
        },
        {
            0x1ADDFE2473B52B97ULL, 0xCB862A76A388B529ULL, 0xD38CEE9A8D7564A5ULL, 0x5A656EDC358A2D48ULL, 
            0xDC4F6069DF78D9D8ULL, 0xBA39E0F78BFA9C1AULL, 0xAA9BE854D7E931FEULL, 0xE65502550D2F0B84ULL, 
            0xC76A2C70CEF493FFULL, 0x8081662874F1C963ULL, 0x39EE19854683D547ULL, 0xC7DB8D9FA0EE638BULL, 
            0x47815E060EAA9A6EULL, 0xFFA60C4BE408F0FAULL, 0x3D91145FA9206E37ULL, 0xAA7357A23A1BEC78ULL, 
            0x9B86BD106983C283ULL, 0x12456ECE8F29DE3BULL, 0xC999827699FBB8DDULL, 0x032EFE76E4CB5F87ULL, 
            0x2987AC137291B669ULL, 0x0A998A14ABCBE5C7ULL, 0x28F41AC4CAFE65CBULL, 0x14816FE58E37C329ULL, 
            0x998AFF6D2D9BD9EFULL, 0x07FEB314000C705EULL, 0x2CE84553A9E3B33EULL, 0x83D7C02C205C758BULL, 
            0x5278661EFFC4E3A0ULL, 0x33130457C9C826D3ULL, 0x51F34A4111D6202AULL, 0xA1BD585B716A42CAULL
        },
        {
            0x20BD5C130DDF56F5ULL, 0x6EA8744D07CF3900ULL, 0x96CEFBF48A3BD7F3ULL, 0x28CCE823AAA68C97ULL, 
            0xD9BE10A1FBE76270ULL, 0x6663544B1B09BBE1ULL, 0xB88977C6F52B9523ULL, 0x9EBA0C00A3922B9EULL, 
            0x83EACE0AB518CBEBULL, 0x295582D33F42B620ULL, 0xE5CA7744982C8CCEULL, 0xD3E208B914F303F5ULL, 
            0x49941519F0708631ULL, 0x5A8BF148CF9A804DULL, 0x969C581761D8F5CAULL, 0x132E88A0631575D1ULL, 
            0x45B554B96C12490BULL, 0x90A18A103EE04877ULL, 0x2C1B7F502AAF486DULL, 0x3C660C76411AFB95ULL, 
            0xCFF6EDED007DF546ULL, 0x6225F06267030A63ULL, 0x2CDFFD0C89F79926ULL, 0xB5461139DBFE5936ULL, 
            0x4ADE9999632E48ECULL, 0x2EAB4962719E15BFULL, 0xE83026A7B450753EULL, 0xA8BDA81FB4960657ULL, 
            0x3C2A081B5A6BA0B6ULL, 0x3B8DDDC9008D6F70ULL, 0x85358AD5792DA8FEULL, 0xCE49D0DA53FF42A1ULL
        },
        {
            0x2FBE207BEC78BF44ULL, 0x9D4E2F1102C412CCULL, 0x4E6E924D6E5AB43DULL, 0x77F344901ED800E8ULL, 
            0x5C0FC9F27886C91FULL, 0x400C536B23FAA259ULL, 0x378EE496897E8508ULL, 0x1CF1C43D6E6A0AFBULL, 
            0xD352044571934B33ULL, 0x0098AA2B348C9338ULL, 0xD2AC4E7E7D726D15ULL, 0x6171AAC592C5B6A2ULL, 
            0xB55E74B25BF62020ULL, 0x3A6BA50D58D7F7C1ULL, 0xFCED12382769C35DULL, 0x4A5B397D29A668D8ULL, 
            0x8694FD5F1B42D03DULL, 0x38132DF015239981ULL, 0xCF33974DA4323D97ULL, 0x4C5A17A21C26C580ULL, 
            0x4F48D965459C51DAULL, 0xC6880DB61BE7C9A2ULL, 0xBD8D4A0C1BB4F9D1ULL, 0xDD7E9D43B53FD562ULL, 
            0x406C4B59D6AB5A49ULL, 0x9954C3CD233575E0ULL, 0x9003446F51D8249DULL, 0xB5260EAB4E780274ULL, 
            0xC40FC4E9EBFB3A85ULL, 0xEBFAE041D35CA23BULL, 0x6C04349496A2D748ULL, 0xCEFE1EA0C5F7B2BEULL
        },
        {
            0xAC19D8BFCB742F1CULL, 0x92448143EF073771ULL, 0x152559DB286E3A86ULL, 0xFF39004151FCFD98ULL, 
            0xCCE286473E700326ULL, 0x97EA3E0F837DE8BCULL, 0x6D42EE9F0B86BECCULL, 0x993E92E4F866E507ULL, 
            0x358087F7EE09B9A6ULL, 0xD566E123B59898A2ULL, 0x41617CAE58EFFBC8ULL, 0x3001B114947720C0ULL, 
            0xD740E310163430B0ULL, 0x576A3E6A3E8DB39FULL, 0x77E40A6A58B5D8ECULL, 0x83CB80466CEA4D7DULL, 
            0xC6E908F1F831CA08ULL, 0xA1DCFB9484898410ULL, 0x5546CD7EA6543617ULL, 0xC988180D2C710401ULL, 
            0x8ECD3A9B14E8ECD1ULL, 0xAC3D2713F9877189ULL, 0x0B0827CAC4039149ULL, 0x21A44806CEF3F910ULL, 
            0x8014A7351D2F5431ULL, 0xD841692AFF416734ULL, 0x73D4591A62324290ULL, 0x9BF44B9A8E41CC40ULL, 
            0x9D6D287A190F19ACULL, 0x944572463B0705E2ULL, 0xA2D80C89D54B40FCULL, 0xEEEECB30079FB1E9ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseGConstants = {
    0x39C69174FBA250B8ULL,
    0x26A6B9F5F39DDB4CULL,
    0x398FA13800603C4DULL,
    0x39C69174FBA250B8ULL,
    0x26A6B9F5F39DDB4CULL,
    0x398FA13800603C4DULL,
    0x20E795A78920FCE5ULL,
    0x8F191E7BEDFE8D52ULL,
    0xCF,
    0xF9,
    0xEF,
    0xB9,
    0x73,
    0x57,
    0x0B,
    0x36
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseHSalts = {
    {
        {
            0x2E52C409FE06AD65ULL, 0xB543DDBB2E8716BDULL, 0x7539F9BE238228CBULL, 0xE4AD7CDAF1E044FCULL, 
            0x9ED9A51DE0A017A8ULL, 0x38D712B5C80F2DF1ULL, 0x1DB59836273A9C02ULL, 0xF19927329DB307FCULL, 
            0x9C4EA77194FCBBCDULL, 0x738CC7013D654B24ULL, 0x9B19EA64950698AEULL, 0x5B3E6EF3A05D9C3CULL, 
            0x2A91572227E91425ULL, 0xE61A9AFC1BC14549ULL, 0xD878CBCEB9F5934AULL, 0xEEE298FB0489358DULL, 
            0x04FBE65A6027349CULL, 0x266333C5B5A065B9ULL, 0xC7AFBAABC26F4FF5ULL, 0x1AEFB54B89615E37ULL, 
            0xDA9C4FD991212856ULL, 0x3342006C21F3B837ULL, 0x176F1F6083A37D18ULL, 0xEE16C9BDCE9B8597ULL, 
            0x917765E5C5B42EE3ULL, 0xEE69C7476A60F34FULL, 0x21597CCD6698390CULL, 0xEC948E4A25D911E0ULL, 
            0xD7373E2A396A2908ULL, 0x18B9CDF3A7C6240CULL, 0x23AEF90233C11279ULL, 0xAEE4C7B8250248DCULL
        },
        {
            0x3B204DAB8F6B1EF9ULL, 0x2CED8FE014945C96ULL, 0xC204EAEC0F6DFDF6ULL, 0xB52ECEDEE0538CD8ULL, 
            0xF88AFFDE563B4B72ULL, 0x509026498098D3B8ULL, 0xAA08873EA75DAAADULL, 0x844CC99D79B2C531ULL, 
            0xD0E3DF8D33B19B83ULL, 0x4AA55423F2D4A305ULL, 0x4E78E9645823D1F9ULL, 0x09361E7ADDF26A64ULL, 
            0x49CA18A5488D8449ULL, 0x77F1C445200FB87DULL, 0x265B7E08EEF1D393ULL, 0x911381EFFE111E89ULL, 
            0xC151351F6071E3D4ULL, 0x35B3B4F1C9C84183ULL, 0x31EB7F084A397BB6ULL, 0xC684E0193B21A17EULL, 
            0x44ED29C26FE74052ULL, 0x87CE6A744D7E49DBULL, 0xE02FA19AED67F44AULL, 0x35EBDA16F8DB50D5ULL, 
            0x844F2C3F6BFBC79FULL, 0x3EF650693FD35975ULL, 0xA30324A53D08B885ULL, 0xB66F0695E3B5530CULL, 
            0xEC4CDF532DAC1F3FULL, 0x298F958D21B9E53DULL, 0xA32FF07B82F7039DULL, 0x3EFDDA935ED4C50EULL
        },
        {
            0x44D0395D664AE871ULL, 0xA9E33E5811913F69ULL, 0xAAD20853A01583A3ULL, 0x458750BD52C76AA6ULL, 
            0x448F37AB66E199F3ULL, 0x8A5F1230B5DC6BFFULL, 0x6D1E280C3FBB16ACULL, 0xB1231496B5A91B61ULL, 
            0x9D4F1A31A180CE18ULL, 0xCEA3313DE70BE741ULL, 0x18EC43729D3E0DD3ULL, 0xBB7DE94AFCCCE277ULL, 
            0x8B6B8B8519A60992ULL, 0x8113F3262120C77AULL, 0xB65B3B097FFDB8B9ULL, 0x5E118EC9DE609692ULL, 
            0xAE73D8D6B4AAF2C4ULL, 0x6D1139B8C404612EULL, 0x11ADD85C9683C061ULL, 0x0C2CEF3CEBF4CA6BULL, 
            0xFF8534F84B2B4904ULL, 0x27FC97918854A2C0ULL, 0xEC981DABF286E227ULL, 0x17CE5D46BD8C4ADEULL, 
            0x73A93E0E4428EF7EULL, 0x5271B644C6B2E73CULL, 0x9C5C06A1727275D2ULL, 0x0A2B6765C09661BCULL, 
            0xD51537EED47EF684ULL, 0x0088CB02FE38E46DULL, 0x802A3F64EC246BCAULL, 0xB021DCB0580181BCULL
        },
        {
            0x4AB338554FB31D40ULL, 0x3554C065D0855E89ULL, 0x14F8EF7D3D9C8809ULL, 0x7359D49E873F266EULL, 
            0x40DD3DE3622F8647ULL, 0xC4E86AA487466E5AULL, 0x678D4C0732D55B31ULL, 0xD81DDCAB2CFD2A5FULL, 
            0x5D1CC0D3B2C83D89ULL, 0x76574D9F240719B5ULL, 0x5C4FD5400058EA8CULL, 0x43CD12A5F980F00AULL, 
            0xCD717DFEE8BC2BD1ULL, 0x15A1DFFEFAE4E469ULL, 0x130588A9BB82D09DULL, 0xAF4373035F63386EULL, 
            0x9CE353AC5F0C2A25ULL, 0x6CEFF263FF502A88ULL, 0xC1117AF77E35533BULL, 0x91D0BDF4CFFACA22ULL, 
            0x11DBE9753A1E57BDULL, 0x38C94738763CE7F1ULL, 0xE5B49DFC0CB5A023ULL, 0xF2DB87BB5AE58E4AULL, 
            0x564B44F6997279BCULL, 0x3B7BFB32660A7A50ULL, 0xFFBDD1A6AD057B93ULL, 0x007F32E7CBCE846FULL, 
            0xDE002D2C8476FE65ULL, 0x3C8C5E19CB44C665ULL, 0x024E33026DE1BDCAULL, 0xA2086CE2184E84F8ULL
        },
        {
            0x5CFB82C2C9829B99ULL, 0x21C94387CA3D1FC7ULL, 0xA34D378150A5EFAEULL, 0x19D4A92B831FA5ACULL, 
            0x7D8803231B136284ULL, 0x222D94FE3433C43BULL, 0x4F825193481FD244ULL, 0x22CB359CFFBD1DF2ULL, 
            0x8B9005F52B53BDADULL, 0x6DF3AD4C58717417ULL, 0x3C280C38394E62CBULL, 0x3ED429C1F94735F1ULL, 
            0xB5B187AC323F184FULL, 0x32701C15ED98E2A1ULL, 0xBA0927DB20EF4D29ULL, 0xD33B83BE05E87E24ULL, 
            0x0DA3267AAB34ADE2ULL, 0x92BF654105CCC849ULL, 0x03B2EE6F92C9F28AULL, 0xF7E8CC22F562E69EULL, 
            0x2EFE8F3B3C8CFD65ULL, 0x6E38F5A2F1A083AAULL, 0x7AA4DD8F9E6EDAA6ULL, 0xB1D7DEB811F9D588ULL, 
            0x2DDCD18EADCF6E00ULL, 0xF83DB2F69F0E850BULL, 0xC789254084B55E25ULL, 0x961559A715199959ULL, 
            0x698264FB0E5B433EULL, 0xA929F2B1DCBD920AULL, 0xF31F254B3CA47637ULL, 0xDA0737432D1819DCULL
        },
        {
            0x1B4A718567C6656DULL, 0x7F416DA5D571FC79ULL, 0xEE4905435787E68EULL, 0x57F1D79ABCB8A16CULL, 
            0x6091D99F9340E03FULL, 0x4E529832DD06A074ULL, 0xBF42CA5A07206C29ULL, 0x4E7723BB6E664B08ULL, 
            0x13ABC8D453F23038ULL, 0x9DCE1B5071CFEA56ULL, 0x7D3BF68AD4C65CEFULL, 0x39486B18EC15A109ULL, 
            0xBD7DABEC8139E75EULL, 0xEDB52346FD9BD265ULL, 0xA15CDB3DCC3E346EULL, 0x84ED9589FBBB38CDULL, 
            0x896E2B836F044450ULL, 0x107173F4EA354271ULL, 0xA03328EC3EAE9E06ULL, 0x3E0B8AFCC158C002ULL, 
            0x4128C32F7AE9882CULL, 0xF2E4CB710BB74E73ULL, 0xB14927A86B135C8BULL, 0x5027966B851FEF06ULL, 
            0x8BC1648111BCB3E4ULL, 0xF9B2927F260F855DULL, 0x33D7E9F422B1CD4FULL, 0xD82560571E0422CDULL, 
            0x112D57316E8C789FULL, 0xAECE14128D8F11A5ULL, 0xF12B7F8EDA4F28EFULL, 0x7357DD5F051BF1B0ULL
        }
    },
    {
        {
            0xB9EFDDDE342ECF91ULL, 0xC07996D8A9F00484ULL, 0xBB9D85590C0B16BAULL, 0xDF9E6F9A6DEF6ED3ULL, 
            0xCAB4240EA8450BCFULL, 0xA14BC564957E123EULL, 0xEAB114BA8B5BC4A7ULL, 0xFDB92602D4DD6CB2ULL, 
            0xFF61A7EBDA429D75ULL, 0x8CC35906A3D7E4C4ULL, 0x4193A518E1684353ULL, 0x6D7C1B3D082116D5ULL, 
            0x93F93619280A3116ULL, 0x12049BBA4817C055ULL, 0xA13334AFC97FB422ULL, 0x88EBF146741361FFULL, 
            0x8CD3CD31946BA5EFULL, 0xCE9DCDF906588AA5ULL, 0xFF38FF487B29146DULL, 0x53B820571FDE13DFULL, 
            0xF5C9A2D0CAE91552ULL, 0x8FEBCB6FEEAE6234ULL, 0x5840154D7973C2C6ULL, 0x55167015F7F19969ULL, 
            0x006E731925F8FE47ULL, 0x8436148EB63698A7ULL, 0x0B20D2EE92BA771CULL, 0xBC01B00C4B50127FULL, 
            0x4FCCE4876E377347ULL, 0xE8870C791A64B88EULL, 0x571DB38B1E22D01DULL, 0xCFA10BDFCB8B7044ULL
        },
        {
            0x1C71F7558A285B9CULL, 0x86654F82E3D4CA00ULL, 0x004511BB483F7455ULL, 0xE0A891E1C5053695ULL, 
            0x09390EA02B4694C1ULL, 0x79ADDA2A8FDBCC49ULL, 0xE9F51C633F1C7140ULL, 0xEF7CDCAB4478E289ULL, 
            0xE0CB0DEAE0604475ULL, 0x5D9DB6D13106EC16ULL, 0x3B83EED681FBBDA9ULL, 0x3A4D9E2DA608989BULL, 
            0x0939846CB54DC10CULL, 0x529924107EB01D96ULL, 0x039CF792AAF396B7ULL, 0x6D9EE48F1CA39E40ULL, 
            0xEDBF6567B367B4E4ULL, 0x49B260AACF867B9CULL, 0x9D69FE5BA3A8F19AULL, 0xC5A9C06261A42B64ULL, 
            0xAE1A98D7A6356EDBULL, 0x24CEF1734D9745EDULL, 0x355295927B3B2AD7ULL, 0x138605D0E67A0920ULL, 
            0xAA71306A8B7B9AB9ULL, 0xC373D449ADD5BD1FULL, 0x8E35F76BB7A8E5EDULL, 0xD53328CFF1C1F0B1ULL, 
            0xC4EAB1952FB9B369ULL, 0xFFBEFBC5DDF311A1ULL, 0x373714C31410BB14ULL, 0x0B5CE39A48EB44E8ULL
        },
        {
            0x9B02330CDC726FDBULL, 0x7874354B33DA34C6ULL, 0x7D2B44CAB0551FE5ULL, 0x87C208A40000F85AULL, 
            0xC58E401232B32095ULL, 0x765AC8ED82D7E390ULL, 0x7A763CA695947A46ULL, 0xC1E4C0D432A1AAF3ULL, 
            0x6057941909A7CD70ULL, 0x5BB94E07F546A8B7ULL, 0xF8FF1BD711B63F4FULL, 0xF420E035C35EA92EULL, 
            0x91CDBFFD1E678A70ULL, 0xB7A04606FA88DAF2ULL, 0x839D384C702696A1ULL, 0x96189D88710FC003ULL, 
            0x2EC1E66127B31090ULL, 0x4DEA37F8C179F47BULL, 0xDEA2B2D0FD86D061ULL, 0x9A109CD45DE7D24BULL, 
            0x4164D3CE002D27D0ULL, 0x1C07403598C43463ULL, 0x6F907E6DBF123F9FULL, 0x4D2C18753AFE44F5ULL, 
            0x13BFD8D0DE62840BULL, 0x6A122DF9A6EC6C08ULL, 0xBB4DA38EF993EF67ULL, 0x869664E055005721ULL, 
            0x91E0294C4DCAB0E9ULL, 0x62A65D451C7B2893ULL, 0x30C13104E3D33FC9ULL, 0xBF60A80C7C9FE964ULL
        },
        {
            0xEC8AEEDD98D1B344ULL, 0xC0D44CCF61AD2531ULL, 0x45E94B451413777AULL, 0x9F99127AB5D2FBC6ULL, 
            0xD6639598EFE52389ULL, 0xE6E0F1739DAE16BCULL, 0x6EC095FACBD8CFEAULL, 0x49B2D91A43596D9BULL, 
            0xC7ED5B00789CF96CULL, 0xA5E485AA4E912F8FULL, 0xB5367908FCE4FE39ULL, 0x8CA29A99F69016D8ULL, 
            0xBCD168D030D598D8ULL, 0x776E07DBD7DFE9F0ULL, 0x1046E229D3550BE2ULL, 0xDF5A1AA7A1877C76ULL, 
            0x0D199ED0C17FBC27ULL, 0xA64086A1CE1BA934ULL, 0x9A44DAC9EEF039F1ULL, 0x3202D379064D9740ULL, 
            0x5429ACCD5FC99B72ULL, 0xF12259F0826B3225ULL, 0x59E7A4465D3162B5ULL, 0xD93235151EE712A1ULL, 
            0x6093BD157140C1EDULL, 0xBB7F4593EA5499D6ULL, 0xCBFD1C2448C816E4ULL, 0x1A9B28D3B44A6C9FULL, 
            0x27D62449BAEBDCE1ULL, 0x56B2AB5AE14CEE7DULL, 0x69BB285EF4ED650CULL, 0x65FEF9C753FB5780ULL
        },
        {
            0xA00C0D308EB9981DULL, 0x434F715DAC57FC6BULL, 0x27E42A759142BCDAULL, 0x2AB87C86D94DA005ULL, 
            0x499DF82622EB55E7ULL, 0x0A18CEDFC6550D06ULL, 0x9EA167BF9D1FF67CULL, 0xB68963C7E52A4A56ULL, 
            0x63897CE89EDFC9EAULL, 0x8B9C3A89F474F52AULL, 0x3C280E2416C6EC1EULL, 0x60A002E0A74E00C2ULL, 
            0x6491ABB110951EC9ULL, 0x2F279119BCD744F5ULL, 0xA9814504CE6CF648ULL, 0xDA78C4093E337639ULL, 
            0xD0B496E73D53B3B1ULL, 0xC5CBDA72733747E1ULL, 0x09AF8575CF69CDB6ULL, 0x0942F1A74B61A324ULL, 
            0x2540D1E3FBC2CF11ULL, 0xF37D2C8538FA52E1ULL, 0x29EAEC65AB519452ULL, 0xBAB0F5481028982BULL, 
            0xFC1B07A72CEF62AEULL, 0x29F53C1C516B441FULL, 0x123500F980554947ULL, 0x3F6E4D236E5E715FULL, 
            0x5FD0CFF9379AC96DULL, 0xC55399B12395331CULL, 0xDF52F6F22AD5F53CULL, 0x614D436B727791B5ULL
        },
        {
            0xEC87D28F542AD596ULL, 0xF6BB140903405632ULL, 0xFFA29A1F41867694ULL, 0x39AC26D6A1095830ULL, 
            0xC9B44A3354D9B730ULL, 0x203F041C63C49EABULL, 0x2C90CCDC61B657C6ULL, 0x4061F3CB8621ECC1ULL, 
            0x49BE431255DAE6EFULL, 0x42892EDF23142BC6ULL, 0xEA97406469871D46ULL, 0x06C01D00EE7501A1ULL, 
            0x2D9ED0B49AB846B5ULL, 0xB0E6009B12B5AC84ULL, 0x782D325A11D3F52AULL, 0x76C1A199518D0FC7ULL, 
            0xFB276C522848867EULL, 0x7B270300B1DB5440ULL, 0x9ECD84D7CF6F2CB9ULL, 0x2B3FD295784F0FC1ULL, 
            0xC5FB66449FD96543ULL, 0xB05C6005C55BF780ULL, 0xF67FB190B3E1CA7AULL, 0xFD88EAC38F49D213ULL, 
            0xA1A43F30FBD70250ULL, 0xC075C04BE13F33A8ULL, 0xF9CF43EE4F138199ULL, 0xA6EFBCAF7CFDCA27ULL, 
            0x55B9000C94B4074BULL, 0x55F8C87C166C157FULL, 0x9BFA7C5018494EF2ULL, 0x5B4430841BF06E7DULL
        }
    },
    {
        {
            0x6379AD193959534EULL, 0x03AC7A3732EB43C0ULL, 0xA1899C0A34D8FD74ULL, 0x836EBF4AE6969913ULL, 
            0x6129E763A2D3509EULL, 0xA993BC84CC5FD846ULL, 0x676D4EE51356939AULL, 0x0FF19C9021D55BDDULL, 
            0x80742AC13ADD6BA5ULL, 0x69D1D55B3ED0E020ULL, 0xB14B83771FAE8C8EULL, 0x79BD6A0116DE1C76ULL, 
            0x7F453A4AE8DE02E0ULL, 0x78235BDEA690239CULL, 0xB87F5B22163AEC5BULL, 0x264A4B6B39DC60B5ULL, 
            0x5EF9678133D7DA4EULL, 0x5181928C9BD29DADULL, 0x75CF8E578E245A54ULL, 0x45A799754E07339BULL, 
            0x1DBF06EAA5A528EDULL, 0x68361D687E51F51FULL, 0xAA985F583E2E346AULL, 0x7F333D0DBFA3E3EBULL, 
            0x8C6740CAB6591F01ULL, 0x551F193F07010F37ULL, 0x324AEC84617F57A6ULL, 0xA30F2276D68A206EULL, 
            0x9633BAC9B80CEC40ULL, 0x5FD0B84C87E47114ULL, 0x4E41E5383727D40FULL, 0xFF45F708E9EE1C38ULL
        },
        {
            0x0948C4AC579B2876ULL, 0x93F37396F745A12CULL, 0xC272943F83F83F16ULL, 0xCE7ABD7F8A529450ULL, 
            0xA0967573110FEA48ULL, 0x2640ACA802EE0EA0ULL, 0xF7060444EC7EACDAULL, 0x2A29FB6A0E6671CEULL, 
            0x3FADA3D3E8558B62ULL, 0x183D56060C16EB79ULL, 0x308761B97216416EULL, 0xB6D6F0EBC4A367C0ULL, 
            0xE4C2E76C031B72DFULL, 0xABF2BE481E7E5DB7ULL, 0x8D3016765A92B93CULL, 0x4CA384216733BE99ULL, 
            0x1427D8AD846B9A41ULL, 0xC068EEE2F0617B09ULL, 0xC000300DB2715A7CULL, 0xDE7BA88A8C160B58ULL, 
            0x380C9A54FCCB7E75ULL, 0x25B6599F061D22C8ULL, 0xCE920A86327566A7ULL, 0x401AC545947E1A08ULL, 
            0xF50E1723E51952EFULL, 0x3C7222FEE0ACF96DULL, 0x5DDE4DC25C24DE3EULL, 0x1C149A81A6E1EF6CULL, 
            0x61B626778C852F04ULL, 0xCEE2C130FBCCA68FULL, 0xC004FE1E1433F280ULL, 0x7A3BAE36F2229EAFULL
        },
        {
            0x4DB49F263FA75EA6ULL, 0xC96797170D5EFC51ULL, 0xE59A98F352CE86D4ULL, 0x61AEE1C03C1108BFULL, 
            0x8906FE376A35F37BULL, 0x010BF85B0A0AEA71ULL, 0x9AC18F1362598E4BULL, 0x3B2E0ADF92EDFA6BULL, 
            0x6D4ED91DBEDEC289ULL, 0xFFFB86E292B20746ULL, 0xCD64964C005D4522ULL, 0x0B13C108016E2E0DULL, 
            0xC0B89D95C1E5AC17ULL, 0x8CC3172C8FF0CCF0ULL, 0x89403AB22CB2C505ULL, 0xD65107E3DBB24A36ULL, 
            0x849C00B7D05FB623ULL, 0x6F029CD8387DA2CBULL, 0x6D29464BEFCF81E8ULL, 0x33D21BB8820951EFULL, 
            0xDE761DAA8980E5E3ULL, 0xE1E95AF5CCB7448FULL, 0x89DB537568C79765ULL, 0xAB9C20A2EA076733ULL, 
            0xC6A73935F11D02D4ULL, 0xA1073E2741A59E54ULL, 0xFEE1F57D29027FAFULL, 0xE8C732BDE3F9F590ULL, 
            0x56D56C20E60705B7ULL, 0x6C7D2180562E00B7ULL, 0x7F0ECA6D997BFC2EULL, 0x3D520023F6FAE0F3ULL
        },
        {
            0x08CE0940FB0CE6D5ULL, 0xF3988980CA590E9EULL, 0x6E3666B6EE10A926ULL, 0x1DD4E0A03038C345ULL, 
            0x960ACB72FE4DF467ULL, 0xFE25D2F7BE8DBE6CULL, 0x82FBEAB35DB15997ULL, 0x2841AA4E6ADDF482ULL, 
            0x86FE407527D2F6A0ULL, 0xBDC855E825BA51D7ULL, 0x3BE7A439754E3908ULL, 0x4DFBAC7CB060C75FULL, 
            0x4824D95B3BBD6289ULL, 0xBE256C9D2959B446ULL, 0x6B379E7907A4A904ULL, 0x058A12B075D78FAFULL, 
            0xD168CAE151493B63ULL, 0x834C75A28A65537BULL, 0x468C0DD6046E09C8ULL, 0x2AD28E684CC2FBDEULL, 
            0xCA31CB24EEF9EF18ULL, 0x029999E180EED013ULL, 0x41773894944AD1BCULL, 0x30A67D1319A1EC51ULL, 
            0xCD99F3E1908AEAB0ULL, 0xB13C60746DB6D809ULL, 0x81172C7EFFC3AE63ULL, 0x60DD6E95E72BC79AULL, 
            0xD386EC60C59DBEC8ULL, 0xB629B7C34C4B0563ULL, 0x17014084790CF69AULL, 0x464FB08F3BA8A3A2ULL
        },
        {
            0xFECA8CF8F1CEEF2BULL, 0x98426C4669F37610ULL, 0x835457DF20D425B4ULL, 0xD38BC67852451588ULL, 
            0xD33D0EDC3F2BACCEULL, 0xCFB5839F624FBCDDULL, 0x03D353ABF9D20918ULL, 0x301D44B0DCA79DD6ULL, 
            0xBAB1E4DA39625E00ULL, 0x0BD9C300B2F3EE8EULL, 0x763CDAD182819E9DULL, 0xE2C6ADDA338AC956ULL, 
            0xD51DE09B4C49F502ULL, 0x85B74F97BE283B08ULL, 0x9E49562B32571AB6ULL, 0x2840840D11D69295ULL, 
            0x23E50B3219F8F796ULL, 0xF85829796B53077EULL, 0x182A4C72AD36301DULL, 0x034F13E89DC685F5ULL, 
            0x8A856242A1C6E03AULL, 0xFA080F2701751104ULL, 0xF8E4097CE5CEA9DCULL, 0x438B14FDF2ECB8F1ULL, 
            0x2AB4DE7E5BBCAA53ULL, 0x60FB75B2808DC2D9ULL, 0x3BF10F1F7D158B15ULL, 0x62A1F3FBFF7FA3C9ULL, 
            0xE10FBDE894A3788FULL, 0xEC3345B2F3470524ULL, 0x67C86BE0BBD292CBULL, 0x74179984D0ECA048ULL
        },
        {
            0xA9D4F62A7A17CAA8ULL, 0x6506B6A2259F67CFULL, 0xCDCCBB404C4E4DA4ULL, 0xF37A951B3A49C355ULL, 
            0x70A4A216B5C9BFFDULL, 0xE8FA54360BD689DFULL, 0xA987A6EA7A0E7080ULL, 0x2D38FD767D68FBFCULL, 
            0xC0671CC9B1B59014ULL, 0xAF458DF45C1A44B3ULL, 0x907260A6CC8D7887ULL, 0xE2559A57DC4E44C9ULL, 
            0xAABA3D679DA4E8C1ULL, 0x1C19AA2BAF760959ULL, 0x2CE2CF7F0F4282C8ULL, 0x46EF79A2AB913029ULL, 
            0x94D019C040FC3644ULL, 0x8F61AD3E9F514217ULL, 0xD34C5B91F43381C1ULL, 0x4871DF19AC9C62D5ULL, 
            0x81A2226455AD864DULL, 0x31AA7EFD7838A937ULL, 0xBD8B97BCA25DD298ULL, 0x376A874EB527D10EULL, 
            0x6B52E206DE4BC829ULL, 0x265B3CE44BD9ABF1ULL, 0x8DD76C2427D9FA5BULL, 0x3A61F5E7D8F67670ULL, 
            0x7F37076192716776ULL, 0x456E6FA7B5793D54ULL, 0x93027D5DDB6C813FULL, 0x863C3CEE3BA4F422ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseHConstants = {
    0xB2BB7A470C381E7FULL,
    0x347676C4D7F947F2ULL,
    0xFA51E2FC356CAA79ULL,
    0xB2BB7A470C381E7FULL,
    0x347676C4D7F947F2ULL,
    0xFA51E2FC356CAA79ULL,
    0x1812BD22B82F764EULL,
    0x90F3BD399A0A8A1EULL,
    0x7A,
    0x3D,
    0xFD,
    0x10,
    0x7B,
    0x2A,
    0xE5,
    0x18
};

