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
    std::uint64_t aPrevious = 0xBE0C87EFD14E377EULL; std::uint64_t aIngress = 0xECCDABB73279278EULL; std::uint64_t aCarry = 0x8321B6A4C8B98958ULL;

    std::uint64_t aWandererA = 0xD3AE2B9B5EC1C616ULL; std::uint64_t aWandererB = 0x902DD5892643C353ULL; std::uint64_t aWandererC = 0xEE75D663F6926170ULL; std::uint64_t aWandererD = 0x85364006AD71AC2DULL;
    std::uint64_t aWandererE = 0xB096CA5885F8AFF4ULL; std::uint64_t aWandererF = 0xBC7B438F81890742ULL; std::uint64_t aWandererG = 0x939C9D21CBB0F67EULL; std::uint64_t aWandererH = 0xC4C6391E003D5366ULL;
    std::uint64_t aWandererI = 0xE4B1FE51C604800CULL; std::uint64_t aWandererJ = 0x93F77D5A86192369ULL; std::uint64_t aWandererK = 0xC34D405BFB9E63DCULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15451483670096644471U;
        aCarry = 11864270740948538042U;
        aWandererA = 11540316160533151730U;
        aWandererB = 16385536210665765667U;
        aWandererC = 10984228334092402484U;
        aWandererD = 10008681741330246135U;
        aWandererE = 13922457443016842412U;
        aWandererF = 11954847285767755514U;
        aWandererG = 17356996933303960305U;
        aWandererH = 15976861569846399388U;
        aWandererI = 14196293780251200949U;
        aWandererJ = 16614972072946410676U;
        aWandererK = 15765150225287800183U;
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
    std::uint64_t aPrevious = 0xDFB5115159D947D5ULL; std::uint64_t aIngress = 0xCF33A3F85F249840ULL; std::uint64_t aCarry = 0x819FA0632CACC473ULL;

    std::uint64_t aWandererA = 0x9976CE3AA2B86133ULL; std::uint64_t aWandererB = 0xCBBD057B01AE75F1ULL; std::uint64_t aWandererC = 0xD83D3FBA922AB4CFULL; std::uint64_t aWandererD = 0xF6048C355C4873B7ULL;
    std::uint64_t aWandererE = 0x8C895DB1FE2D70CAULL; std::uint64_t aWandererF = 0xFC51B632367C7A44ULL; std::uint64_t aWandererG = 0xE19E486E15BD203BULL; std::uint64_t aWandererH = 0xDC7DE389883CD517ULL;
    std::uint64_t aWandererI = 0xA55F7804DC546BE2ULL; std::uint64_t aWandererJ = 0xF24272B7ADBEB03FULL; std::uint64_t aWandererK = 0x910CC4391D8D1389ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 15685150419445618322U;
        aCarry = 14817976125448409063U;
        aWandererA = 15098320831345913555U;
        aWandererB = 18181873301752355478U;
        aWandererC = 11699557869327543092U;
        aWandererD = 13974892714405678888U;
        aWandererE = 12228075387047195732U;
        aWandererF = 12609068684337469904U;
        aWandererG = 10240533900391783973U;
        aWandererH = 13426413212636398346U;
        aWandererI = 11271596241050235933U;
        aWandererJ = 17692470648849073421U;
        aWandererK = 12470522363387077948U;
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
    std::uint64_t aPrevious = 0xCE138928E493ACCCULL;
    std::uint64_t aIngress = 0xAB67EFF413F29F10ULL;
    std::uint64_t aCarry = 0xC2A837257F18C6B0ULL;

    std::uint64_t aWandererA = 0xDA0A2F9605F49D0DULL;
    std::uint64_t aWandererB = 0x9416A2642E3478C1ULL;
    std::uint64_t aWandererC = 0xB6CF590BC2C850E6ULL;
    std::uint64_t aWandererD = 0x9DB6BFAB5CB3164DULL;
    std::uint64_t aWandererE = 0xCFF80346BA1FB620ULL;
    std::uint64_t aWandererF = 0xB56D66709AB7598DULL;
    std::uint64_t aWandererG = 0xC443186EAC8F1B2BULL;
    std::uint64_t aWandererH = 0xB3C64492CF2BEF43ULL;
    std::uint64_t aWandererI = 0x96B111379C0D6180ULL;
    std::uint64_t aWandererJ = 0xBF74B55BBE6072F5ULL;
    std::uint64_t aWandererK = 0xF02DA41DEAA99852ULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::Aria256Counter(aSource, aSnowLaneB);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
    std::uint64_t aPrevious = 0xFA6B30B1F7C3A86FULL; std::uint64_t aIngress = 0xFB6D968B1C4B0E49ULL; std::uint64_t aCarry = 0x8634BA152CD45FD2ULL;

    std::uint64_t aWandererA = 0xDF21A98AA6F83692ULL; std::uint64_t aWandererB = 0xE82CEDFDF9EC151DULL; std::uint64_t aWandererC = 0xBE4C75D4614A477DULL; std::uint64_t aWandererD = 0xE8C79A8EA03DADE3ULL;
    std::uint64_t aWandererE = 0xE4D9BA855C3C997FULL; std::uint64_t aWandererF = 0xC41A2C5650169D04ULL; std::uint64_t aWandererG = 0x9D916047FF36FA2EULL; std::uint64_t aWandererH = 0xE487E72B9B01AF2FULL;
    std::uint64_t aWandererI = 0xD73AF65883BCE041ULL; std::uint64_t aWandererJ = 0xD4A14615BD3B3B2FULL; std::uint64_t aWandererK = 0xCE5F152BD99B30ADULL;

    // [seed]
        aPrevious = 15734298999905057109U;
        aCarry = 9838579497419179733U;
        aWandererA = 14187310044808959955U;
        aWandererB = 16518151475332051045U;
        aWandererC = 13331049962725741004U;
        aWandererD = 11891981874275588725U;
        aWandererE = 12151151120180408791U;
        aWandererF = 12654936870270555883U;
        aWandererG = 18399837949567059531U;
        aWandererH = 17581464158404378649U;
        aWandererI = 11674446249315024876U;
        aWandererJ = 9550414478950490193U;
        aWandererK = 16231428544327342730U;
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseBConstants.mMatrixArgD;
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
            0x9798E08E26DD8A19ULL, 0xBF8B79C25D3D48B5ULL, 0xC36667B23EA8DC6DULL, 0x9CBC88894E0E58D7ULL, 
            0x4295EDF62FCDCB6FULL, 0x7BAF9A352728E7BFULL, 0x4EFB2B3A0C20AACFULL, 0x61D7B65D2033F0F5ULL, 
            0xBF1BFED902DB2D03ULL, 0xC71A93D49B73BDC8ULL, 0x4F794D5A156E17F4ULL, 0x943E7AF19A2B2730ULL, 
            0x2760BA48BC0ED14AULL, 0x9C9E3DDE32DC656AULL, 0xD5D4F7D8D86C15B1ULL, 0xF72254F5639E76D2ULL, 
            0x2E53F5A80CA489F0ULL, 0x328AFE7C1FA8E153ULL, 0x8F5E8226AF15837DULL, 0xE080ED4E5CD3F6BFULL, 
            0x4CBE7AF1B2208ADDULL, 0x5AA50B0B48F24134ULL, 0x722ADA42F142886BULL, 0x2725F00E9D7817ADULL, 
            0x1E14EBF2C4D16F4AULL, 0x609FEF9CFBE89CA1ULL, 0x3414FFAEFBA08A1AULL, 0xF08A81A02284EBD3ULL, 
            0xEC6AF171A7A1E58FULL, 0xC67246C142608BC2ULL, 0xA6D492F58F539A94ULL, 0xC5BA19DD4497F4CBULL
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
            0x97764BF6850BF663ULL, 0xE755C43C5545F90AULL, 0x8518168A65FA0CDFULL, 0xB7899D04D775767AULL, 
            0xB40E9159A561BA6FULL, 0xEC5DEFE7053FA436ULL, 0x523EAB6194E0B36AULL, 0x207D80323810B115ULL, 
            0x955E7D1C14A5354FULL, 0x893898A52B25EC91ULL, 0x2F04FD48DD25D38EULL, 0x7BE1AC713D5226F0ULL, 
            0xE5475F928FE7FB6FULL, 0x753A0FD08676C8F6ULL, 0x7EB6CDD48FA5FDD0ULL, 0xBCFED1439EA78C7DULL, 
            0x27EAF03FCF4EB9CBULL, 0x73D9CFA2C4E7112CULL, 0xDC4C428EB5953135ULL, 0xB779160A419B7486ULL, 
            0x92D059832AA1437DULL, 0xAD47CF3B8F7F70F6ULL, 0x00BFA9492F645CE0ULL, 0x52DBE12956D3E9BCULL, 
            0xC4F72E17DF7D5548ULL, 0x9DC2FAA340EFAD09ULL, 0xF4B87E66468B61FCULL, 0x072B216AF9E97AAFULL, 
            0x939665582A22F077ULL, 0x637BEE16BEA507DDULL, 0x05BFFD7AD5FB4EF1ULL, 0xDAA8AF86A417F300ULL
        },
        {
            0x5BA7A44FCB4D21C8ULL, 0xBD6265D1230332FBULL, 0x0AB534C58BEA4CCCULL, 0x1CD9E18D28FD05CBULL, 
            0x59D9FA37D5532839ULL, 0x43EF504D4A48790CULL, 0x2B1E358405F424B9ULL, 0xAB85D9E770F126E4ULL, 
            0x0D290B6E250E1E6EULL, 0x69CCF2D9A0EB4554ULL, 0xD50838CE0BE4FBECULL, 0x0E74381580349D41ULL, 
            0xCFCE0DD670D2F279ULL, 0x347ACFDDED9A512DULL, 0xB9D8A07CD95460BDULL, 0xBC24432EE8BC7C4FULL, 
            0xD8D8C104CE916606ULL, 0xAA6BDA234301F5F7ULL, 0x54A57E4DE1E825CCULL, 0xD4C57D5E1F816C01ULL, 
            0xD4F3EA577404F418ULL, 0x10B48F1EF98BB46BULL, 0xAC761B95CA8A10EFULL, 0x04C1A51F77E08901ULL, 
            0x36AA1C97894B045EULL, 0x052EF1D9D636E689ULL, 0x1D536534B7207584ULL, 0x4609DF5C213599AFULL, 
            0x08C00503263F8D65ULL, 0xF4223CE142571B3FULL, 0x9C14D89660FC5EF5ULL, 0xA5C22010B1EC1962ULL
        },
        {
            0xE52AA234DE657C7EULL, 0xBC94D69FA0912731ULL, 0x1D8CD19C0E42845BULL, 0x960F499415D73438ULL, 
            0xBAA72DE1038B6386ULL, 0x5E6A4513CC42219AULL, 0xC6BD1C725D7EB4BDULL, 0x82628EC234288620ULL, 
            0x6119281D3DEC3AD6ULL, 0xCCB7AA6A404EEFD0ULL, 0xEDB8CD285CE6AE89ULL, 0x3927685F294CEB18ULL, 
            0x56942BE9E48DC912ULL, 0xCC747C0DE9098014ULL, 0x8AD5FD84B48CB4F7ULL, 0x71C8644C098F4491ULL, 
            0x19E730644A8C84B0ULL, 0xABB9C1CCAE212A63ULL, 0xA7214458371F5966ULL, 0x8F4F634E9E15A954ULL, 
            0x1BAD76F4B240BEE7ULL, 0x2226096452100662ULL, 0x9D45787BB79D7246ULL, 0x59E60B33823CB644ULL, 
            0x1AD3F111CA70F0AAULL, 0x14A4AFD3B57F639BULL, 0xFE89A4820A4A258EULL, 0x41874D9E25397650ULL, 
            0x4D44F87827E9176FULL, 0xD45AC702FEB42FC6ULL, 0xFDB511B80665287DULL, 0x69A60B85C0B5B3D5ULL
        },
        {
            0x0FEECC70588A4182ULL, 0x854B768E5B6B0239ULL, 0xDE35B4412ABDA32CULL, 0xAB4C3FF5BA208D04ULL, 
            0xC730F2DB51C673C4ULL, 0xD0AAECE99F3EADA8ULL, 0x23D772544F32AB02ULL, 0x5C649913ABCD34A4ULL, 
            0x7A8F9A55DF8316EDULL, 0x7600F56FA0BB74BCULL, 0x18C863F4D245E8DEULL, 0x4A7B7B8F30C7C926ULL, 
            0x0FCEB048369ED3AFULL, 0x543F0C23706D35F2ULL, 0x14F18F8210A4C7F0ULL, 0x6B3DCA63F8987BE2ULL, 
            0xEB9CD8004A6DA627ULL, 0x7A9AE133DC7C2563ULL, 0x390DB0E2ADF7BB0FULL, 0xF038B4A0DFA15E5BULL, 
            0xE0F3DC6BD691A14FULL, 0x339C822EC3DBF6A2ULL, 0xFC5E6D7A74B6E20AULL, 0x826F9A49F96CE0B4ULL, 
            0x74A1B1D295262F24ULL, 0x69996D6BBFC62EB9ULL, 0xFA1B7F6A710708DCULL, 0x73072ABFF7EC2013ULL, 
            0x9A65643917083D06ULL, 0x84E3B06A40780CA6ULL, 0x657B25AD6D91E9CBULL, 0x7DBD034878E6AA10ULL
        }
    },
    {
        {
            0x62A432DE869B431BULL, 0x305F587F27DC27EDULL, 0xF417D33967F09D83ULL, 0x79C8C061CBE27F4AULL, 
            0x51DEFB24D5488DCDULL, 0x169257D95066FF2EULL, 0xD2270F9187B9BA9BULL, 0x10B26997E41E226AULL, 
            0x7DDFCA8BF989986EULL, 0x46E29BC97BDA0A21ULL, 0x3978C6263830451CULL, 0xBF62241A211B30E7ULL, 
            0x1B4A568944E2B3ADULL, 0xA7D2769A04DDEEBBULL, 0xB86019CCCD9F0804ULL, 0xC456F7B5013C0578ULL, 
            0xD9AF03116BDE1D2AULL, 0x2A790ABA67E2CEB7ULL, 0xDB1F2B0E56C63B22ULL, 0x04F1A5494EA7DFE6ULL, 
            0xF2E2110CDC10F1E5ULL, 0x423CB1BBFB58DC10ULL, 0xCF22D969608F9DA4ULL, 0xFBB4AC155E4A68ACULL, 
            0x4CB98DB1A7B77566ULL, 0x68984841E05B3797ULL, 0xBFF03A2988451D09ULL, 0x23E47E392FD002FEULL, 
            0x4804E8F813FEA1A7ULL, 0x19FAD08E2E65A5FEULL, 0x07346D4A791F5B1AULL, 0xED62C1FA5ED83AF8ULL
        },
        {
            0x92FA1ACD7F99088AULL, 0x98C0CD953C152DDBULL, 0xEACB3672830E1A34ULL, 0x4563B67CD1D658B5ULL, 
            0x80E99A623FC63A05ULL, 0x84A73EED094DA979ULL, 0x4131C30FBE40A11AULL, 0xDAAAF7D6EA4108CAULL, 
            0xF6139A1BB4F222CDULL, 0x79A77F8C99E04D40ULL, 0x93C98B37D22AAF29ULL, 0x1894A373F3CC56D5ULL, 
            0x4882E4588E2D8867ULL, 0x203493E9F9FDE2FFULL, 0x11947BF219647652ULL, 0x2B2B06737676181AULL, 
            0x50D96ABAE1E3B356ULL, 0x9FDF597D7F01FF09ULL, 0xF3D41D2DD5964054ULL, 0x64C471696DD203A5ULL, 
            0xBE8B83809ABB938AULL, 0xCAABCFE47BEC38EDULL, 0x53F9CF60A9B23AEEULL, 0x80294C1B3A62164FULL, 
            0x18B5F4C9B4DA7E33ULL, 0x26B6CDF34A65BD83ULL, 0x4A13EDFC59606EFEULL, 0x078E010E03798D7DULL, 
            0x4B5BEF4745153B0BULL, 0x7A9907FE3B5A77DFULL, 0xFF86D43D5D191B73ULL, 0x3D4756D942391AE6ULL
        },
        {
            0xAA3A26F3EE04EDB9ULL, 0x7E5B1D8629CA3E9BULL, 0xDECBA3AD06BB3483ULL, 0x3D89C9974CB4D85AULL, 
            0x612CA1BD64BDC749ULL, 0xB2EC411ABFA476C4ULL, 0x82F17E57303F4798ULL, 0x1BBA45499108D379ULL, 
            0x13B458A56D5BF3ACULL, 0xDDC3C848AC84FC1FULL, 0xFB6FB5FE04F168A6ULL, 0x30BBBDF0562369E0ULL, 
            0x13488D16E585C3E7ULL, 0x49207EF065A19AACULL, 0x12635B2C51B19093ULL, 0x30AE3276297F0B46ULL, 
            0x51F387BCCAADA2F7ULL, 0x85FEA1F61AF6FF4DULL, 0xAEFC1D28BAB4ACDAULL, 0x14A64DA4CFBD18E8ULL, 
            0x3813A845D40FC33EULL, 0xAC91EE412F9D1D13ULL, 0x070122A63E1808DEULL, 0x619CBA506A83F166ULL, 
            0x4B4E8F48317530DDULL, 0x6AE9F5672DD72CE3ULL, 0x2478C5E6675C42A0ULL, 0x8A9445FF385A48ACULL, 
            0x56C5965B9BF66E05ULL, 0xAC8DB1DB82A84CCDULL, 0x8E8B5E45DD4F17B7ULL, 0xC592CA630F8849E8ULL
        },
        {
            0x45074855DFB87588ULL, 0xE896323989C9B7B5ULL, 0xBFB5828F2EF8CA54ULL, 0xE3818213BE22ABDFULL, 
            0x9D65A1D4412A8E54ULL, 0x24FC115A0ED54FB6ULL, 0x2B508C227A95B957ULL, 0xAC287C91464118FCULL, 
            0x4C551D79D3E8D3B7ULL, 0xB3B41D75CDD2D73DULL, 0xCE9653DBEE9B4745ULL, 0xF3B8FD071261802BULL, 
            0x14121F474DE8A56CULL, 0x67668B53889B0C35ULL, 0x0B67E7BB24E4BACDULL, 0xE6571D2C72D42E9CULL, 
            0xAC1B6809A1A47461ULL, 0x407D537EF48D0E83ULL, 0x70080A02429ECEA5ULL, 0x346E50B80092398AULL, 
            0x39A3D73810D151DCULL, 0xAAAEBC8345613078ULL, 0xF77A6F5E19C4C00EULL, 0x30AB0CB80E5E12F5ULL, 
            0x0B652BF7BA5A9E35ULL, 0x65E1A7DE445306EBULL, 0x8502D182FE65A5CEULL, 0x95EDF686299DC116ULL, 
            0xB70FADB05C19281DULL, 0xEF8FA8B48ECBDE24ULL, 0xC32BED98D339FED3ULL, 0xB1979E0E916D26ACULL
        },
        {
            0x5B0D2E00BF19A759ULL, 0x0982CFE554678F41ULL, 0x637E991BFDA7FBE0ULL, 0x808662DF9FDC8B19ULL, 
            0x46CBD3F2CD942228ULL, 0x77F5079D0431A4FFULL, 0xE116EF72B132E374ULL, 0xE183A23BA6F3248FULL, 
            0xDE007CEC7B25229EULL, 0x272718A2AA1AC075ULL, 0x4344FACCE5374C86ULL, 0x390D9760A886E16EULL, 
            0x87FE37A8C3A93504ULL, 0xC472AD4AFDBE322EULL, 0x1069C4E503243C82ULL, 0x38C4A07F5966AA9AULL, 
            0xE6A3FCA1D0661628ULL, 0x9C54014E0ADA58C1ULL, 0xAF423222BF783AFBULL, 0x50E2330AE00C1FB0ULL, 
            0xC7A4E7B4E927F4C9ULL, 0xFB838B095A325141ULL, 0x652A3D08C81C338FULL, 0x7D50AD8EF32385E1ULL, 
            0x408A7351B50C1321ULL, 0x6AA0F77D67AFFE9EULL, 0xAF3D23A44936A1C1ULL, 0x8C1F37A131B16095ULL, 
            0xDF948840700DC5A0ULL, 0x67C4B81DE27581E4ULL, 0x380D2DD8F21A551CULL, 0x2CA2ED1F254C8BF2ULL
        },
        {
            0xDAB9C6E62AA6D9B1ULL, 0x25BA0F97D85DEEC0ULL, 0xD6D05F815301AEECULL, 0xC45EF8FE1B104641ULL, 
            0x7051D7BB55AA399DULL, 0xD22FBBC74707CD7CULL, 0x587DF227273310AFULL, 0x8F51947DEAE809B5ULL, 
            0xAFA8A0E8A6A75FE1ULL, 0x908A9805440642ACULL, 0x4DA7F1AC617A4875ULL, 0x9B9A10BF84B7BBABULL, 
            0xF94D872AD80A220FULL, 0x625FABD587891ABAULL, 0x1915B0054414E164ULL, 0x3515E2239145AFEEULL, 
            0xD539AC7202B26455ULL, 0x4494A4F86F60BA59ULL, 0x263BFC0ECA4CE9D3ULL, 0xAEC1C897EE8D1849ULL, 
            0xC440E6DBEC249C9DULL, 0xCE74107294AC0319ULL, 0x40DF7AFF8EF68A4EULL, 0x63B732080163A951ULL, 
            0x63B02DAB1B19BF86ULL, 0x84F5060209FEDACBULL, 0xF01503BE550B69A9ULL, 0x7E2636758FB905A8ULL, 
            0xFBA3D436C2601183ULL, 0x4AB12776D32FF59EULL, 0x2300626EDD0528A5ULL, 0x52BB68ECC265C851ULL
        }
    },
    {
        {
            0x17F139B6259A7811ULL, 0x8B347496F3F97A9DULL, 0xE0061369D55B5816ULL, 0xF64C9A1858B4834CULL, 
            0xC89F6DE98DDC9814ULL, 0x31F0597AFD19FDD8ULL, 0x09537E9A549A117FULL, 0x9BB36CCCB9BB53C8ULL, 
            0x8D18BCFF74B5C37EULL, 0x710E66552DC8B856ULL, 0x0E97B644CAA5723CULL, 0x3C29E9A42EA74F03ULL, 
            0x898F93F3C3B4DEACULL, 0x5DE892872D56760DULL, 0xC623BAA7DE0B25F8ULL, 0x0F119A4A45F8A1C1ULL, 
            0x75EF590E810B965BULL, 0x5DC5124505F03A1FULL, 0x3D76360C3F906138ULL, 0x40033FEBE3A535DBULL, 
            0x522D9A67EBE1ED77ULL, 0xCF24565AB4C9C764ULL, 0xB17A473566C4532CULL, 0x49528E1742C17DCEULL, 
            0xAE5F84E6C099A9C4ULL, 0x141919A517FFECCAULL, 0x8102E58C0EAF1CD9ULL, 0x5CE810840C018BA9ULL, 
            0x4181DF6BF67807D3ULL, 0x0B6B722FD048755CULL, 0x953447318136B678ULL, 0x408BE6ED8794DE80ULL
        },
        {
            0x488611847E302DF7ULL, 0x081CFA485D329581ULL, 0x520B271A272FEDBCULL, 0x2932CE0A1D8A466FULL, 
            0xB7FFB6865DB3540EULL, 0x573BD8A1D7682FF0ULL, 0x4B6B4658BE710E08ULL, 0x2AD4729914606E3EULL, 
            0xD4B3E5009F8FF6AFULL, 0xF7AE318AC923E036ULL, 0xEB1DAB8F20F83A8CULL, 0x6CF9C4A3FD2F300DULL, 
            0xD9B0446C5D60C4EDULL, 0xF7C2DA1EB803C114ULL, 0xC3D7A5FFC0AD726EULL, 0xEA2C707913C69188ULL, 
            0x44D89EE18F585731ULL, 0x59F37D0B2551D111ULL, 0x2120B6AE605BA1FBULL, 0xD2826E4FAFF9C5ECULL, 
            0x68DB3C099F869CCEULL, 0x82B816094A96E8F8ULL, 0x734201399A21DB50ULL, 0x9CC6662DFDF25B19ULL, 
            0x103EB8E2EDB24989ULL, 0xE293075BDA2995AAULL, 0x1A0C4E38C76C0289ULL, 0x29DCDFE523B837B8ULL, 
            0x300D2D6078B1E3ACULL, 0xB0F3C6203548F559ULL, 0x144B3F509C37DBB1ULL, 0xECD9441FB28E9C1EULL
        },
        {
            0xC7DD3A89AB67D670ULL, 0xC2F75EA3A7CC97C8ULL, 0x5E534CDADB71DCA0ULL, 0x7B43AB808CFD258DULL, 
            0x3133350BA0D6E78BULL, 0xEFF0812C1F689FC0ULL, 0xFB2090CE9D693A8DULL, 0x30316373AB2B18AFULL, 
            0xF3893AB5B56BBF98ULL, 0x2F73B632E30BC07AULL, 0x8075439318A7169EULL, 0x43BDE960E2E203B7ULL, 
            0x7EBE024E7B5CEF28ULL, 0xCAC37366F5FD64EEULL, 0x56B16A73E0B710D5ULL, 0x3ED2A7448964877AULL, 
            0x49CD15FF68B3FE10ULL, 0x34201932227881D6ULL, 0xEC78B92FBEEAEB77ULL, 0x3A523112AA647C2FULL, 
            0x360D93678F4D10D9ULL, 0x9DD797956679B3B0ULL, 0xD8046320112F1A6FULL, 0x2B40183FBB80F4B1ULL, 
            0xB6E4E3A4F93FCE26ULL, 0xD4894B8632FD7958ULL, 0xB71669BE6638A639ULL, 0x214605AAA5C25C04ULL, 
            0xC632ACA467C31A52ULL, 0x5A79276D1137A350ULL, 0x0CFE65DE76EAFB88ULL, 0x9207A66038BC07F4ULL
        },
        {
            0x0512B55AEF1D7AEFULL, 0xD8F4E7BE9B2AFC0DULL, 0x40F878F238D936CBULL, 0x29E8FE435D4D52E4ULL, 
            0xC1DB4A0A54ED3B64ULL, 0x6116A4273B224A06ULL, 0x83B199D3E52542BDULL, 0x84AF9198F186D048ULL, 
            0x665CCFF2D7E57AB5ULL, 0xEF2DD2213475CDFCULL, 0xE6C778A2321BACF4ULL, 0x93699BE0D8C7255DULL, 
            0xF94D6A326AC193C4ULL, 0x5B2A8F0D7D062C7EULL, 0x8F646A30D537AA45ULL, 0x78065C4DD97D2D98ULL, 
            0xC9D68860D1CB6ADFULL, 0x66A2019EE25E222FULL, 0x3CBA9E3403D671D9ULL, 0x721C0053B5585971ULL, 
            0x2383F1862C225E44ULL, 0x6B78DEBF46A6C08BULL, 0x01D013B9E5551BAEULL, 0x62C53C6239C638FDULL, 
            0xBDE7628E22A06A90ULL, 0x3D67BE4C657CC300ULL, 0xCFEB77D98897CC62ULL, 0xBDE8A7218FFF634AULL, 
            0x73DC663CA60E4246ULL, 0x0F83B0BDA544AEB2ULL, 0xE805B5B0F6C04274ULL, 0x5DE1880FD724A4F5ULL
        },
        {
            0xD71E964444400A37ULL, 0xB35C1410DC852CC1ULL, 0x12EE4A92AFDCE4D4ULL, 0x2E36DF9B8248C7C2ULL, 
            0x0F103E9D7912A740ULL, 0x3AC3D62507C90853ULL, 0xE1576AEF95EDEB95ULL, 0x2BD2A8D559053EFCULL, 
            0xD8C79667BC14356AULL, 0x9BF5AF3B422AB2F5ULL, 0xF258DABCDD8B5EF8ULL, 0xAB07B1703808B2C0ULL, 
            0x02285A1D5F4BA0F0ULL, 0xDD642D8C30F9D8BDULL, 0x8D92456B64C913E3ULL, 0xFB5D659BD7FAF790ULL, 
            0x67A96B0E2DE73EA7ULL, 0xE576071C314E1CBAULL, 0x3BBBC59DA9C7D0C7ULL, 0x55ABC80C5AB899BCULL, 
            0xAB7BE3DAF7CBC380ULL, 0x30B5DA8A918B99FBULL, 0x0E648F511C63F539ULL, 0x4B4DB7102549905CULL, 
            0xAFB5E8BC2D2869E7ULL, 0x45D01980932DDE78ULL, 0xDD0CECA44411E77AULL, 0xA6574F81796F8D97ULL, 
            0xF1E3FF9DD094BABDULL, 0xFA3C6F32947F6398ULL, 0x1A2A6B1DB5675A8CULL, 0x2D3B9A96F6D1DDDDULL
        },
        {
            0xFA11C459FFFA90BAULL, 0x8D7FFF8CDFAB8C6BULL, 0x28EC4269A0AC5CEEULL, 0x4BA200ED1D120DC3ULL, 
            0x32A952DC776E6539ULL, 0x2CE4F91DA097C6AFULL, 0xF2B86BCCFCF5ABC2ULL, 0x42A65959DB22AE97ULL, 
            0x8BD68E445ED64AB3ULL, 0xB134E10E604B51CBULL, 0xEB0A8BE261DF88BBULL, 0xE6E0599F906FDB2BULL, 
            0x19CCCA3358B5ECD8ULL, 0xE0E37DE49CE3E16FULL, 0x0BD9CA41D83AFE37ULL, 0x4EA9B101FE1DB01FULL, 
            0x85C619E284421F24ULL, 0x91884C07555D3889ULL, 0xA3F8E27ED3694BC1ULL, 0xBD0640FAE92DC7D5ULL, 
            0xB82C80ABE9A8BBD6ULL, 0x0998EF32CB1CAD45ULL, 0xA7EF344660AA3989ULL, 0x06CD30AB23D7A2F2ULL, 
            0x64562858C8DB7D2BULL, 0xE95890CD78B04729ULL, 0x385B72D80157CB8CULL, 0x16FFA1642FCA3164ULL, 
            0x21F4C1F4B412342FULL, 0x35D81AD8FE6C9E91ULL, 0x4D47C10E2FA827E6ULL, 0x1303515317BF7D94ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseAConstants = {
    0x3D65B7894E455CCBULL,
    0xFA74796BA570860FULL,
    0xA1AD5EB29CAB54F4ULL,
    0x3D65B7894E455CCBULL,
    0xFA74796BA570860FULL,
    0xA1AD5EB29CAB54F4ULL,
    0xC685D61B21C627E9ULL,
    0x9A4EBF68631FE447ULL,
    0xA2,
    0x7E,
    0x40,
    0xF3,
    0x06,
    0x34,
    0x8D,
    0x60
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseBSalts = {
    {
        {
            0x1F52789984ADEF2BULL, 0x9F093D7D4977BA4AULL, 0xDF1DC008B079D84CULL, 0x9ACC0F14C10300FBULL, 
            0xA6DD252B8CD99A71ULL, 0xA26099E58722600BULL, 0xAF03A730C996F44CULL, 0x53D0BC68DCC766C6ULL, 
            0x6A1B3F8AEF2823D5ULL, 0xED1D18875035A5C4ULL, 0x670E1F80F4979869ULL, 0xB40CF622AC341048ULL, 
            0x2EBA9DED161E982DULL, 0xC8AF4BD0C45C6374ULL, 0xD5EE3A17F179E6EFULL, 0xEDB61B5124FFE42FULL, 
            0x1FD19F8DBDA147C5ULL, 0xFCC0D8F73D017313ULL, 0xDA0D51392EA4AF24ULL, 0xBEB3517B2D24E92EULL, 
            0xAA31D6772B522E51ULL, 0x7631D93C26ACA4E5ULL, 0xCB929F036E7FB4E2ULL, 0x805B7BE7BC9EA777ULL, 
            0x2094D2C766AA37BDULL, 0xBF8A942FA8DCC82EULL, 0x72EF85474464C9B2ULL, 0xD0FCF57315697618ULL, 
            0x04062A7A95D8C5D3ULL, 0x47CDF9458CE8CE5FULL, 0xA4661A2DAD20F81FULL, 0x22A9269E7BF7D01BULL
        },
        {
            0x63D7B1BE7C79DAB2ULL, 0x547EA0851876A249ULL, 0xA426CF8B8868D7F3ULL, 0x52401110BBF90224ULL, 
            0x112218F6455E9CF8ULL, 0xC198E56390BC25FFULL, 0x14AEFCF7A1EFE0FAULL, 0x83EF60FC809A3926ULL, 
            0x727F2E827386F737ULL, 0xBA1B4E76C5EBC58AULL, 0x04D555CCAA25AEC2ULL, 0x5F77F8A2D824A40AULL, 
            0xF3A8C56A1D22EB41ULL, 0x0D4ED4C4B7A7F730ULL, 0x851E3DAB94F32239ULL, 0x238E288237C15564ULL, 
            0x6CBA6ABFA5DFE67AULL, 0x7EDE7E35747A8725ULL, 0x5925A0384342020FULL, 0x57F6574C9B9C6208ULL, 
            0x991F3142BA6DFC62ULL, 0xD94C028CAFDCDFDAULL, 0x5022079237F67BDFULL, 0x85F7CFEE61549862ULL, 
            0x2178006457BCDAF1ULL, 0xE9D4639E47D0478EULL, 0x8AA2BB7E1AD45C62ULL, 0x3D2F2E8B9596FE4BULL, 
            0x7D7ED99A0EC45BFDULL, 0x624D2132620CAD79ULL, 0xDA82BBA3CC22D891ULL, 0x311434F64B643F73ULL
        },
        {
            0x68BC73C30406AB42ULL, 0xA51B4A236FC33B4DULL, 0x6CC357EA2DEDB59EULL, 0x6A7D9508C66BEEB5ULL, 
            0xABB4DE42243CBD65ULL, 0xF9D71E9FC0FE19B6ULL, 0x7AF3DD35F636DBA3ULL, 0x68DCDE834DF1B329ULL, 
            0xF91D21CF0D61104AULL, 0x6ED7B5D0888CA77DULL, 0x6CB04E091F4C580AULL, 0x3A1980A4A9762A44ULL, 
            0xFD4F2D0441972CC5ULL, 0x1867CFD4497B6026ULL, 0x4DE81E6629825F6FULL, 0xC1C6F606D274589CULL, 
            0x8166A2ABE4331184ULL, 0xDCE04B20774E2DD7ULL, 0x81A87454E3B111A2ULL, 0xF3E79449200B1E4FULL, 
            0x5E6A2C8EEBB5E009ULL, 0x846A7CFCB64F14A8ULL, 0x8170443669AC4B58ULL, 0x005EFFAF9AB06BA7ULL, 
            0xF3C5A2B85BC1F6F6ULL, 0x0D01813B213C7DC6ULL, 0x0258426BDCC538E3ULL, 0x887BEAD0550B8B5AULL, 
            0x56429CED00471D32ULL, 0x5B47134F449E2448ULL, 0xF1728D2F4522B59DULL, 0x1AE96686D3875EFBULL
        },
        {
            0xE52A11805D3FA5F3ULL, 0xF1047B654AA342C1ULL, 0xB46D94530042A45DULL, 0x9FAD7F24D4E2900EULL, 
            0xAEBC4390F8C6A4EFULL, 0xD8007586F43638CAULL, 0xA91556C89D17431BULL, 0xDD6862B5C0B75986ULL, 
            0x4CE34F71982EAD73ULL, 0xED0F80D4A3AC5A74ULL, 0xA0C501CFE305F3B9ULL, 0xB34A05535C995426ULL, 
            0xF39D03E0AD9256BFULL, 0xCFAF160A7A582EB7ULL, 0x71F1A931B108AA6BULL, 0x85532E7D41609593ULL, 
            0x47397462227BF7C5ULL, 0x2020E95397BA478BULL, 0x0258684FADFEF109ULL, 0xA43C808262FB50F0ULL, 
            0x281599573930B393ULL, 0x15003AAFECC230EFULL, 0xE3874AE0D56F5A24ULL, 0xC762ED3336BA2D0BULL, 
            0x4AB489F1C4AA7FB6ULL, 0x6EC54E8CC27185B7ULL, 0x401BE29887ADF8C0ULL, 0x53902BF8870FCA11ULL, 
            0xF7697B60B6F9B2D2ULL, 0xF5B790B62FC73529ULL, 0xF816C0B5EC29FA7BULL, 0xA938640A18ECA160ULL
        },
        {
            0x61C0B703222A5BCFULL, 0x85B310528F99689CULL, 0x569C3DBA0AF0DB55ULL, 0x0121A44657CCFB21ULL, 
            0x6A3E162AD9B13242ULL, 0x8E092DE6C1B85B19ULL, 0xB569EF063768E80CULL, 0xA684CA4708B36E73ULL, 
            0x04D29D18ED2D3B10ULL, 0x235B7A3A2DF3D1D6ULL, 0x5092A500D7823F10ULL, 0xB9B3E83136C19CA9ULL, 
            0x4C3DAD6C21996CCCULL, 0x47D75BCC3097FE1EULL, 0x361C82A4FACA8950ULL, 0xF8DFC8E35C6E532DULL, 
            0xF016579070B2AF4DULL, 0x24ECA82B1A132261ULL, 0x9A4D4D4B9AD6F9DBULL, 0x83C2DC86C8EB18D7ULL, 
            0x16699A3DD51C6E51ULL, 0x5E8EE4CFB53020C6ULL, 0xC8D556A24374C09EULL, 0xAD4FBCF057EEB5D2ULL, 
            0xF91A9377E11C3C14ULL, 0x6BF893BD97CC5579ULL, 0x63DAB78A6FF3A996ULL, 0xE7BF4968E8B2B862ULL, 
            0x24EE87D3322EF499ULL, 0x03753FF23C3DBB0AULL, 0xA225F641337D30C0ULL, 0x27AA70DB1B336C0AULL
        },
        {
            0xBD4E0CF6C0A03776ULL, 0x3725EACF53624AFEULL, 0xE0A126744FCCEE94ULL, 0xEC311DFC8A6AC4FDULL, 
            0x1F8FC41316F6799CULL, 0x5E791B986020E444ULL, 0xF9300DC3C36E608DULL, 0xCB43C079CD0C7678ULL, 
            0x4959E7B0753BC7D8ULL, 0x60B056C231622CBAULL, 0x4ED475FD5DC1A689ULL, 0xDD418897C32F71B8ULL, 
            0x65B9F5806B3A14EFULL, 0x73C22BF6FABE7AACULL, 0xCE9082E0FB30ABAFULL, 0x75EE087ACFD85631ULL, 
            0x7CBEB9ADA2E6B195ULL, 0xE94226D4B555A291ULL, 0x6C52093DB846B318ULL, 0x6F1E555ABC30B29CULL, 
            0x8E49331D50538BECULL, 0xD96CC025078FBC1EULL, 0x0D21B268C79199ACULL, 0xB6DB6621C1AD7710ULL, 
            0xA048C7C0FA255477ULL, 0x33E48333675809E4ULL, 0xED1562EBE4A44CD6ULL, 0xCA1967C193A513E5ULL, 
            0x37856BC9B9BE4EB6ULL, 0xCA18B29060ACD4A1ULL, 0x6AFA84EC38179D55ULL, 0xEE781BE939634111ULL
        }
    },
    {
        {
            0x818093E15FF58A88ULL, 0x94524B65184CAE9DULL, 0x72E0B62F3935BE87ULL, 0xA76E0EE356E45770ULL, 
            0x0B75FB30EF90D3F8ULL, 0x0F39B00C4295C0A1ULL, 0x676D9927506CF02AULL, 0xD3BA28B4CE0CA951ULL, 
            0x1E44147A4AFF7B61ULL, 0xCF4C33188D47672CULL, 0x83E57CC6CEE8E8B5ULL, 0x60D59DD3AF6DC620ULL, 
            0xACE2786C5D1775B2ULL, 0xE0F4F26E86A32BCBULL, 0xDA5532FCD1CE10FDULL, 0x0E3D4B4F2419D498ULL, 
            0x682B6954E38F6F46ULL, 0x80562C889333FD6FULL, 0x23E1AC1FDCFEE7D3ULL, 0x8DC0B0CE6F3C87E7ULL, 
            0xCF8433A4FD97092FULL, 0xCAB0CB994A4E0CD5ULL, 0x20F9F0355214EE78ULL, 0x11DC7EB1615499D2ULL, 
            0x6F03A6D9F3603E6BULL, 0x90991C0BA549889BULL, 0xC13FBFE6847D2232ULL, 0x5DA571F3E4CAFA97ULL, 
            0x2F3EB610F99C6B2AULL, 0xCD35651DB62DE955ULL, 0x796CC0E4EAFCC436ULL, 0xA34087434D45ED09ULL
        },
        {
            0x2813E26C7C79FD6FULL, 0x396E5F9E1FD75203ULL, 0xAF22BD4243D27C6AULL, 0x405AE407F0F501C7ULL, 
            0x75C17E9747FF823EULL, 0xF296BA5FAB15BAD0ULL, 0xD3C8B3D8388B8A27ULL, 0xBB965E08A9F82E9EULL, 
            0x2380BD0F27D91236ULL, 0xD270B2CC79D8077CULL, 0xB23905692EDD5B58ULL, 0x652A574DE9AB0B30ULL, 
            0x7E25B5DD380C505FULL, 0xEB4BDCC5A3C41D9CULL, 0xBE729F0720C02609ULL, 0x8A41377F1DC1DCEBULL, 
            0xE4930373D1754DCCULL, 0x28AD803D760050C3ULL, 0x1A3F573A458D4B2CULL, 0x0B739F876C1E3327ULL, 
            0x5622517FA1FA6F9FULL, 0xEF25BA55C9E6CEEEULL, 0xD3D16DDF9447EFFAULL, 0x33C3ADC0468F1A77ULL, 
            0x841ED5578DDE9903ULL, 0xF199D64D4F4DE1DAULL, 0xD1FA24E7F6F593F2ULL, 0x1DD72D4693757EE2ULL, 
            0xECD6CB3442F229C0ULL, 0xC92768D697078BD4ULL, 0xB252553F3E3548EEULL, 0x80BCA98868835F05ULL
        },
        {
            0x986D0187EB5D4FA0ULL, 0x5CED3697E8014B70ULL, 0x712FEAAAAC5E67E5ULL, 0xB3A113765E56F907ULL, 
            0xC1A5582E7F734DA4ULL, 0x3B69A292A46C8308ULL, 0xC15DBE33EA58B974ULL, 0x756A605F72E357BDULL, 
            0xBBF2024A995A290AULL, 0xADCA5ABF57CC08D3ULL, 0xC1535F3F9142003EULL, 0xD4B9A720AED4003BULL, 
            0x5C8F2B5DA38D9621ULL, 0xF6C22406B961BFC1ULL, 0xA90480502378A16CULL, 0x95F7CCFF6DBEC121ULL, 
            0xC18417F92F40866EULL, 0x89773686798841A1ULL, 0x4F6959AB64C5761BULL, 0xB4062DB66F112A52ULL, 
            0xD33B95A81AEB4366ULL, 0xA9E5D12792189995ULL, 0x94D3D5B623EFDCD0ULL, 0x8C00DCE703131A4DULL, 
            0x9BD8153C6C99B4FBULL, 0x6DF39E966AAD6EEDULL, 0x6227F4423E34FFE1ULL, 0xC32491B806306DFBULL, 
            0x263EE3678C83528AULL, 0x002DA8C548C116A4ULL, 0x2EA6675A54C68C6AULL, 0x68D4898A4115CF58ULL
        },
        {
            0xF31A2B1317AE24ABULL, 0x00A2FA3A952EA12CULL, 0xCC7AF25FD6A1BBADULL, 0x3379D0D008DAC8D7ULL, 
            0x2795D86A89B92572ULL, 0x522A9BB05510D00BULL, 0x1376773A63CFF745ULL, 0x585B402BB7391155ULL, 
            0x0CB58B30511734FFULL, 0x9F38B0A1C63ED392ULL, 0x0B881198DE7DAEE1ULL, 0xF5E2A0C2BD21D5D6ULL, 
            0xF14440B9D7CB2D3BULL, 0xEF2844EC1EC5CEA7ULL, 0xF423D6A9CE4B8DA7ULL, 0xA382295C0D0D2B1FULL, 
            0x2D3F33B667BADF4BULL, 0x6ED6C030188F0A1DULL, 0x68433C27CD5B2F21ULL, 0x72C5C804A4AC103CULL, 
            0x6CE650C1C6E4524BULL, 0xEAA4A4EE754BF4E8ULL, 0xA10BDBF0463F025BULL, 0x13DE05B7CEB5473AULL, 
            0x79C965B6093E664AULL, 0xF94C21B5A582B5ABULL, 0x3F40021E8B42255BULL, 0x25B9A4632A03B979ULL, 
            0x3A5F95109A08DD56ULL, 0xF8E5FCD6611873A8ULL, 0xB11C89E49E43D7F9ULL, 0x0B68642A3C72FDFDULL
        },
        {
            0x58E08BABA06E1DEBULL, 0xB0D46BA6BD14E9D2ULL, 0x0D7805B35B05C6C4ULL, 0xCE7AD90920209323ULL, 
            0xAD67CCA5052D1A92ULL, 0x0F129DDFAA4C0EEEULL, 0x9418803B19905A14ULL, 0xFB934A9315DC24EEULL, 
            0xCD35E1F3955FEACCULL, 0xEDD81AADA5A26E0BULL, 0x26CD7B3534E88772ULL, 0x561BBB3E34C6A57AULL, 
            0xD69364F84FD02FACULL, 0x0247138795CAF5B1ULL, 0xA0C88DACA0053E28ULL, 0x2FEA6CE0E7E6DA46ULL, 
            0x87E831B675BD47C9ULL, 0xC941A40F2618F1B5ULL, 0x36AF7C55EA6ABB12ULL, 0x6EEA43145E7B9137ULL, 
            0x0A7254D7BA53E8D9ULL, 0x913E29F8027A3984ULL, 0xDCDB287A0DA6108FULL, 0xBBBBA18318DCFD5DULL, 
            0x0EC8D74FF7FB19A1ULL, 0x522F113795FC8D7BULL, 0xCE50A11386534A80ULL, 0xCCA458B4E0BDEDA9ULL, 
            0xED85C0493BEF1F36ULL, 0x54E00B7A25B0D8ADULL, 0x7518F089F2A38F7BULL, 0x741E0E5AE4D1BD45ULL
        },
        {
            0x4D4B94C127B10581ULL, 0x111A51C18372BFD7ULL, 0x207A7B6A4D2BD54CULL, 0x973759B8782A903DULL, 
            0x27A86FE8795D9F67ULL, 0xFF659687AD13DF8FULL, 0x39692BA00E1DE60DULL, 0xC2128F1EE631B7D0ULL, 
            0xFB10C0DCAD1C0CCFULL, 0x84E66AA45CBF8416ULL, 0x23E3229A6AAD3067ULL, 0x677E9CC767DA2160ULL, 
            0xDB7FC682C088327EULL, 0xB9E844AB6F3DC29EULL, 0x5DA58E6B3CBA89FEULL, 0x6A02AF7B6F73CEC8ULL, 
            0xC49429F092E43E1AULL, 0xBF75CDE7582672C4ULL, 0x56AA76132EC80E6FULL, 0xB9063278BF6090FCULL, 
            0x5F020F159BC0F1B1ULL, 0x90B9C5DD4EA7854FULL, 0x2EB5B9D1D09806B9ULL, 0xA351CF894FD0D0B6ULL, 
            0x3EBAE0286EA8C14DULL, 0x81A789E4DD9FF9F4ULL, 0xF7C5958E100AFEE9ULL, 0xA25B69995303D2F7ULL, 
            0xFC18111050D4C692ULL, 0x20907AACDED113B4ULL, 0xF9691B3D1DF67F12ULL, 0x3C0EC2E7195071C9ULL
        }
    },
    {
        {
            0xCFF2B64FA791CF81ULL, 0x75393566BCDCCA74ULL, 0xBCFF107F2126919BULL, 0xD89FAF189CADE03FULL, 
            0x345C5E4466ED3E59ULL, 0x6C2385AA73B551D3ULL, 0x748D82C758B14D2AULL, 0x2435A90104A650BDULL, 
            0x2BEB4A67474E420FULL, 0x7DBE4AADA434CA3CULL, 0xD6834BA6DA9CF89BULL, 0x9FEC8B70519A3408ULL, 
            0xDCA975DAC9EF0022ULL, 0x6E781644E4DAA8FFULL, 0xFC21D08727CCF6BBULL, 0x5C3EC8C372D0F4DAULL, 
            0x5F6578A3B37775EDULL, 0x0106806AF1A23D52ULL, 0x5DBAA1DF2BDD94A0ULL, 0xC7F73DA79202F573ULL, 
            0xE7BC3F19E6DF4368ULL, 0x79FA7898008868D7ULL, 0x7EC27FAE7A6A169DULL, 0xFF80A18A348FAF77ULL, 
            0x632E37ADFE798AF3ULL, 0x175D606DE7B317DDULL, 0xFDDF59A7BD5629E5ULL, 0xF3E9A2996BB34F5AULL, 
            0x10AE0177051668C5ULL, 0xDD1D1F603BE3A979ULL, 0xD37319844BC31607ULL, 0x672614FEC62D5D09ULL
        },
        {
            0x02CA0414BAA719EEULL, 0xAC3B4488F0FABEF8ULL, 0x366E1C2074AACF7AULL, 0x825C71CB662C3F9FULL, 
            0x5FD429A077F69D37ULL, 0x7B0ADBD228974A0DULL, 0x827D027884C67C2FULL, 0x133A1974B1572A27ULL, 
            0x57D2849B3C408643ULL, 0x693F02891CAD2D1EULL, 0x248FDB1318B12EBEULL, 0x0A164C24A77FCCE0ULL, 
            0x2607FD6AAA9B13DEULL, 0x55584B73F74DF9CFULL, 0xDD5F9AF0A63F1D93ULL, 0x3D2D0B9B056FF460ULL, 
            0xA594A5481CC6FF0FULL, 0x40B78E40A97DFB65ULL, 0x532556E72660D534ULL, 0x186EBF9A563D5E87ULL, 
            0x1AEB8453B6098A4DULL, 0xDC65AB55A8031455ULL, 0x0C4E538DB84ADDC9ULL, 0x7800A40BD7A95BCCULL, 
            0x6E13A10F77CE1539ULL, 0xE95743E64B458663ULL, 0xB016558B44430617ULL, 0x69670360724B58C4ULL, 
            0xBA62099473D60346ULL, 0x63F6D75223A12CEBULL, 0x49099995FB63EC21ULL, 0x7718F357BA033FF3ULL
        },
        {
            0xE36DE3C4A5EDC565ULL, 0x682621C72D1B1C27ULL, 0x5A156BBF2263B926ULL, 0x452DEEDDAA202973ULL, 
            0x1A1128E9A664F063ULL, 0xD03AABC695932B38ULL, 0xBE43D48A870D7E54ULL, 0xA97A2C147076F420ULL, 
            0x8C4A2ED29626272CULL, 0x25A61E34044BF28DULL, 0x735B6D4F8033AA9DULL, 0xD89AEC232C8DA5B0ULL, 
            0xF0602D1D2252E1B7ULL, 0xCED6E9D0288FC988ULL, 0x1E35B0154FE8FE5BULL, 0x84F1159A37B815EFULL, 
            0x733243AADBA6B3A7ULL, 0xE5DA3542297B6ED5ULL, 0x2C8CFEFC7E2DA9DDULL, 0xB01C1BAEA58B2BD0ULL, 
            0xB1416F1FB140F5F3ULL, 0x1D2A4EFEDA2ABE3CULL, 0x3CCE79C7115018FBULL, 0x3AF3AB6C6CB4C9C8ULL, 
            0xFA2C74F36BF220C9ULL, 0x24D6834855CB392EULL, 0xA437977151468CCCULL, 0xED03F481931B43BDULL, 
            0x3E12A5B589690EB1ULL, 0xA65877872C12F3FBULL, 0xF789165E19F3BC41ULL, 0xD5A2078734111F5EULL
        },
        {
            0xFBA4971B1F43B05FULL, 0x2BD207E46A6B02EDULL, 0x242625713A4B270EULL, 0x7F4281B82117716CULL, 
            0x5C26D70E4FD19F35ULL, 0xCBA2C2F564C39665ULL, 0xEB1D03C2128BBB4BULL, 0x005E4F056F332D2CULL, 
            0x7C99A02CEE1627D3ULL, 0x3865941FB16814A1ULL, 0xEA55AB5EB39B0B21ULL, 0x5F5499B37B0F761AULL, 
            0x64A154D9E23A57D6ULL, 0xB55424366DE0BB46ULL, 0x5F734665B00A68E7ULL, 0x1011ADDB3CBC84ECULL, 
            0x0E4C989F198E16E4ULL, 0xCBBFB9DF83F457ECULL, 0x41435521EB16B33CULL, 0x0406ADADA8F0E118ULL, 
            0xA60AA637C63CDE6DULL, 0x9019ABA17270F404ULL, 0xBB787CB76AF1DF6BULL, 0xD160F923B32D2374ULL, 
            0x75BF01C890C7AEB8ULL, 0xB561E269FB76DFEEULL, 0xFDA72045C9D35C44ULL, 0x090EA9AEF5775C5EULL, 
            0xB03FC0C9EDA36E30ULL, 0xE6650D967906C3CFULL, 0x4EA15F1323EA2DF2ULL, 0x2B9455B126141C81ULL
        },
        {
            0x6E1EC93A7F9DB02EULL, 0x0D0B6C21350A6E43ULL, 0x3FDC7163B8F11A76ULL, 0x917250E92CD55356ULL, 
            0x477374DA924DE055ULL, 0x5978197D1C2E2228ULL, 0xAFA99D2C988FA907ULL, 0x3796CEB57477BDE8ULL, 
            0xE63306CB0F8308A3ULL, 0x6231C757F7B973F3ULL, 0xEE5440ED5B9BF5B5ULL, 0xE32A863D381E5356ULL, 
            0xEBECEB42C12862FAULL, 0x54A820D2879A8B43ULL, 0x4D816B3FB555B9B1ULL, 0x80FB93D9C1135563ULL, 
            0x43AACAC9F1F89C66ULL, 0x065036EA4C965E06ULL, 0x42FBCF8EBCC88E06ULL, 0x43DD238FB3A36B93ULL, 
            0x6DD48C9C67A49F40ULL, 0x95515E4072F87DBDULL, 0xDB71146B3201882EULL, 0xD6CD66AE50620C85ULL, 
            0x0A4D03073BFE1A42ULL, 0xECF2DC66B758871AULL, 0x09247BF911217DA2ULL, 0x40478D02165D6712ULL, 
            0x565D5836966B1D60ULL, 0x7800C52C84B8CBBAULL, 0xD9F9751EF5B44F87ULL, 0xC715CF4599834372ULL
        },
        {
            0x5FC7F5F3918F6C8CULL, 0x28E5EA1FDAFB45AFULL, 0xDF57B6655C6C25C2ULL, 0x34947978D3274643ULL, 
            0x28B743669E53DB79ULL, 0x4AB4AEA28B68BC4AULL, 0xBC79A27F85FD262DULL, 0xE82158D89C7EFABEULL, 
            0x4305246B030653CAULL, 0xEBA2137E5303F1F8ULL, 0x4C0D76847F11F4C9ULL, 0x4DA8F50632586290ULL, 
            0x1CEC6ECA556D7659ULL, 0xEBBE47494CD26261ULL, 0xCE2B1050F4033AD6ULL, 0xE61C8356365C129CULL, 
            0x85DB57449456068EULL, 0xD6F1960D9CD69319ULL, 0xA13BCEFEA0716F75ULL, 0x2650B3D9FA799B39ULL, 
            0x6A5D665EEBB792D2ULL, 0x34150D33360022FBULL, 0xBD16822963817BD7ULL, 0x8B423079F4EE86A6ULL, 
            0x1EA02A2DA52013FBULL, 0xC2C630767C6250FAULL, 0xA44A1C585B61BA72ULL, 0xD0922C24996FDA81ULL, 
            0xA9779775237E2ED1ULL, 0x9902A64AB32E824AULL, 0x1EC39A574F6F0C62ULL, 0xFF46BA0E0701AAFDULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseBConstants = {
    0x0D344A904ED35A74ULL,
    0x086EBD6965B36483ULL,
    0x337C894F77CFD6CAULL,
    0x0D344A904ED35A74ULL,
    0x086EBD6965B36483ULL,
    0x337C894F77CFD6CAULL,
    0xBA6D9F855493E590ULL,
    0x13EBC8BB4DAB9650ULL,
    0x3B,
    0x1D,
    0x06,
    0x1A,
    0x9D,
    0xE3,
    0x8D,
    0x1A
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseCSalts = {
    {
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
            0x1FCCE2FE6559AD00ULL, 0x09FDA6E405317267ULL, 0x20139BB9FA3D4A00ULL, 0xD4F96B82E52A3712ULL, 
            0x64F1FBA6EDEFACD9ULL, 0xCCD4A5E796C2A9DBULL, 0xAF8C721626F7A474ULL, 0xCE1BB7F1C86462B1ULL, 
            0x4A2E69E023D6FD6FULL, 0x6EA3E02F78D3FB90ULL, 0xDD85A989B3CBD9AAULL, 0xBFC7E7D8D2B843CCULL, 
            0x7AB835B5E92354CCULL, 0x694E62C3C1F60C9CULL, 0xFA02F882EAC3883DULL, 0xAD59A3063FEA63F9ULL, 
            0xE5392072B1155173ULL, 0xBD14A4DFC944199BULL, 0x60F414F20CA54C8BULL, 0x5BCCFDBE59CAB21FULL, 
            0x30D4F013D6500351ULL, 0x15AF55CB4F1D9B8BULL, 0x867F5A8694A55A03ULL, 0xB7B5D55FCE8F3F9FULL, 
            0x98F3F26881A0425AULL, 0x117C11BEE60B4C04ULL, 0x90C8893BBE7DFD9CULL, 0x25C9E834EE8FE0B4ULL, 
            0xE054D1EEF00EC37CULL, 0x396CF24B924635D4ULL, 0xC87BC829ED3E3354ULL, 0x3AD127CD991BA59CULL
        },
        {
            0x76D48EA5BFB5482FULL, 0x8E80E57960C4E0EEULL, 0x2A7D8A5D4CF3A363ULL, 0x7DC3755599168EC9ULL, 
            0x4DB9E2668B140795ULL, 0xAFA4F72D84F570C2ULL, 0xEDD2EC66E8D0A4B7ULL, 0xB8E6E1F8BCFC7364ULL, 
            0x5D82E60BDFB2F886ULL, 0x841CC9A80FCF6586ULL, 0x5A6BBAAE9EDDA0D7ULL, 0xD6BBCA72E85F97A1ULL, 
            0x91B2824588EE1566ULL, 0x587FA034FE149005ULL, 0xC85842255F191554ULL, 0x5615996F6C33C934ULL, 
            0xD2D4D144824E7395ULL, 0x98740253768FFE81ULL, 0x509851022C3DEF03ULL, 0x884A0222A1DC710CULL, 
            0xA2F9F5B26EB8DD75ULL, 0x9DF499C1B51BFFB5ULL, 0xE24B8C57D5F97994ULL, 0x2FD46BE738C59A8EULL, 
            0x22906DB7C1279A9BULL, 0x66EEA12950B07681ULL, 0xC9D1B983167E3C57ULL, 0x2F08A95A2E6994E7ULL, 
            0x909A3BFF0CDAEAC4ULL, 0xB4969C37B7852E3DULL, 0xAEF69A6347BAFF0CULL, 0x15D8D5967993C6F1ULL
        },
        {
            0x1D906C289C93DF01ULL, 0xDB892BAFD7AD9A71ULL, 0x5A791C47EA3D2021ULL, 0xA64CBC41D3F85522ULL, 
            0x0CC61DA41873840EULL, 0x995449E37D0417F6ULL, 0x797F6FCFE11ED88BULL, 0x501DDF9FDE4F2AE7ULL, 
            0x5E6ED34F033DD926ULL, 0x13817A1D069B7121ULL, 0xA39621AF56EC4E05ULL, 0xB955CF9B67AE8D25ULL, 
            0x3507D2B2A48583EDULL, 0xB2DE3A391338D46CULL, 0xBAA02A1B29EF1BE3ULL, 0xC54B1B1A03805B22ULL, 
            0x2969CAD7EF55F698ULL, 0x544F3E1110A9FFE3ULL, 0xA81EE517E4AD1E95ULL, 0x6322FB7B9596E07EULL, 
            0x2C96000DDBB919DBULL, 0x0EDC186E877E0F79ULL, 0xC49BDF8C99D5784DULL, 0x1D51455E92121D59ULL, 
            0xD14452A0AC9B9906ULL, 0xDD1631E6848EE64CULL, 0x648FD3F41AF81AC3ULL, 0x151D4F57F8447920ULL, 
            0xD58177B24D97E0EEULL, 0x23BEB431108A8CA2ULL, 0x19010750707257D2ULL, 0xD17BB9C7D3DFFEABULL
        },
        {
            0xA3F316AD34DF3A44ULL, 0x17D7EA3C045B3F62ULL, 0x84D0B19AE4070CACULL, 0xF714DF8E182CA556ULL, 
            0x226B80CD30208D58ULL, 0xA3FC2D1B04190895ULL, 0x4D7F05D3FCA31DD0ULL, 0x6262889CD057A9A0ULL, 
            0xEB7A230C7054E734ULL, 0x659EC60BE60CFC0FULL, 0x62D3CEE6C7FD3193ULL, 0xBCB28DF48B58E5C8ULL, 
            0x6D8D17B93101691EULL, 0x74D6E808141CE782ULL, 0x353269F9278FB3DAULL, 0xD91C2FE9F5A2426CULL, 
            0xA7F8D4CC656A3C36ULL, 0xB23A0DF4CA0D5171ULL, 0xA6B9C43E3D9EAC05ULL, 0x529D1D0C99B0844CULL, 
            0xA356CBEB222B39F3ULL, 0x34A156DF40D0E095ULL, 0xD6F6EB4B375D8251ULL, 0x9C39F73D2CD7E64FULL, 
            0x1DA5064F129B5D03ULL, 0x70878F3B3F25DC74ULL, 0x852B17822CEA7106ULL, 0x9B47E2A4D7839E8EULL, 
            0x1444987F27ED5A7AULL, 0xB62583351745F0EDULL, 0xA1D50CCB7CEFB855ULL, 0x8C07F5C802339EF4ULL
        },
        {
            0xA02812978EF8F6F9ULL, 0x7F1A3B93F7D1E39FULL, 0x8E5916CCB3FA6AAFULL, 0xFC1409884ADE5371ULL, 
            0xEE5A01B266C23A16ULL, 0x6671AE92300CFD20ULL, 0x1194ADF48E89ACA6ULL, 0x05FC0ED296F7899CULL, 
            0x5D6B79FE1257E583ULL, 0xEE93B11CBB53C5B9ULL, 0x3D924498B15F93ADULL, 0x35076775BEFFA3DCULL, 
            0x75440302B3BCCFA6ULL, 0xA367733B5AFF2EECULL, 0xD3711065A5D13574ULL, 0x4B84B4D1758E8264ULL, 
            0x50EFAA85CB2E87C3ULL, 0xBEE77BB6269925A1ULL, 0xE16F3705A6DCF644ULL, 0x308C89AC8DC85867ULL, 
            0x85CC8462BE50DF9DULL, 0x3E0F049096D01408ULL, 0x13D90B8D28422A1AULL, 0x5FB81487778499B8ULL, 
            0x6D656A348CDCACF8ULL, 0x953A74B81757DCE9ULL, 0xAD100601F012DCB3ULL, 0x0C5F610A9995BB7BULL, 
            0xEAA9782CD5EB0577ULL, 0xA3BD02494488BD2EULL, 0xD61D4ECF37BD0AF0ULL, 0xB0525B3E4608252DULL
        }
    },
    {
        {
            0x1F37CCC1BDB67596ULL, 0x3335E8FD01CA8BAAULL, 0x14B26FC93459D192ULL, 0x36D113E96ACB46E6ULL, 
            0xD1D8CF51531B14A8ULL, 0xB0C71FE940391970ULL, 0x5E674147989DB637ULL, 0xC80002EDF970AD62ULL, 
            0xF932601BC61B9724ULL, 0xF1DCDEC08D33C6E6ULL, 0x5CE0D138F76FA29AULL, 0x02A163BC945DEDDAULL, 
            0xB8E1991BA19B872DULL, 0xDACE3236C72BC0FEULL, 0x136B0872D86EC66CULL, 0x45D6C7C35F49FF68ULL, 
            0x9955D6C35992F3FCULL, 0x357DB8FF9E4268CCULL, 0xAE78F35588021F1DULL, 0xE26C84F21CD9927AULL, 
            0x2B2429DEE70C7EF3ULL, 0x77A59F6034688AD0ULL, 0xCF952E828EF8E906ULL, 0x3457D534B1354268ULL, 
            0xD4C9D2DD79C12E21ULL, 0xA3CBB0116E7869BAULL, 0x9BD3B636D59F6B7EULL, 0x67F0E7184EAA09B3ULL, 
            0x1C8C361D3EDE56ABULL, 0x4A3F88E879FEDDC7ULL, 0x154027C47E1DD7B7ULL, 0x253146D086C13F5FULL
        },
        {
            0xD883EE24D2F6999BULL, 0xDF455DF101B53502ULL, 0x05D42EFD0FABE3D2ULL, 0x3509484E46B529E7ULL, 
            0xFF67802887BCF49AULL, 0x3FC628BCCAC92C1FULL, 0xCB1C908BF24FD4CAULL, 0x0CEE4A8BB6D3B301ULL, 
            0xCA63D14EF1C6BCFBULL, 0x5704D95B135453EEULL, 0xCD2AD60B287E57DEULL, 0x65BFE3C48681A9F3ULL, 
            0x348040CA3875D0BEULL, 0x2877ED188BB25C63ULL, 0xF9554AD8DDB6D0C1ULL, 0xF50F166EFFD29EF4ULL, 
            0x0130C585DBE32353ULL, 0x0DBD1D48A7852E7AULL, 0x3B82803F7B2A4870ULL, 0x4CACC50E5A77A24DULL, 
            0xC9C95B766C3B8D7EULL, 0x8AFFB069A8114D3BULL, 0x13E2A3AFC7FF8B50ULL, 0xE3A15B553721DF8EULL, 
            0x24528D6DDD733E89ULL, 0xBD375509BD9599B7ULL, 0x67717634163E9678ULL, 0xB0E4A43C347C670FULL, 
            0x436B993C46085AA5ULL, 0xD612359EEB39BE83ULL, 0xB15CA47C1CF68856ULL, 0x622D6D58226BE03FULL
        },
        {
            0xF4C89B095B88B5A5ULL, 0x9560ABE34C6FA66EULL, 0x71873A56FAAD68F2ULL, 0x4CE70FDA805FB2E2ULL, 
            0x8458FBF7F54F61E6ULL, 0xF405E5B5157BA5A8ULL, 0x9F8A6C763761D4F2ULL, 0xCF354B62337D1A42ULL, 
            0x5970951CB13A1870ULL, 0xC393CE7E0C941925ULL, 0xAA3C55A35F821838ULL, 0xE4A8FDF2D0430ACFULL, 
            0xF6591BA1B910A07BULL, 0xA115708B4EE81756ULL, 0xF24F89A7F841126FULL, 0xE9B4525EC2BBAD77ULL, 
            0xD3D18159BFD8EAF8ULL, 0xA29D3F843D5CE1E4ULL, 0xE38CC67F7211F245ULL, 0x3B9E0125534099D7ULL, 
            0x57C39A07D1691B3BULL, 0x55CBAE23365EAE81ULL, 0x41AE5428D46B4A50ULL, 0xB3ADDFCA276CE401ULL, 
            0x7A5A5B0A6BAF862FULL, 0xAA9BFFD797D49A9FULL, 0xFBDCC8FE9161CC58ULL, 0x2C12A63BC38ACD43ULL, 
            0xB4788E6D42BE24E9ULL, 0xF88A77EA58320CB1ULL, 0x651E52C939802110ULL, 0x484226CBBD1CA2B0ULL
        },
        {
            0xCC98DC30A4C2D200ULL, 0xBB547B570A1CD660ULL, 0xBD1BFC5BF6B2CA97ULL, 0xF684645E50892DFFULL, 
            0x088AC12F2F531E1FULL, 0x64ADE49ECBC94700ULL, 0x2092F371C55794BEULL, 0xB5B96AC2616556EBULL, 
            0x6F579CEE19452D1DULL, 0xD42D9BBE4F695DF6ULL, 0xDAFDCF013B8DDA42ULL, 0x8AEBAB1B0F0E237EULL, 
            0xB8EF994A35C87381ULL, 0x54A09C76A79D28BDULL, 0x4DAA313A04162917ULL, 0x21E825B71E21AA82ULL, 
            0xAC86398E92624803ULL, 0x168E1FB3A325533CULL, 0xD340A55919FC4236ULL, 0x84B035CF7FFC6731ULL, 
            0x32AE46D176597164ULL, 0x2D8409B0C7C3C8F3ULL, 0xE5E15DEE29458EDDULL, 0xA7536651179176B3ULL, 
            0x4686756AFE10FF15ULL, 0x70CBDF259DC8B8CCULL, 0xA5FCA1D6F0EF515AULL, 0xAE98BB0BE37B404BULL, 
            0x3341D978AE54B677ULL, 0x24DB40723168366DULL, 0xE658F440DEEFD63CULL, 0x03FD4799255022D2ULL
        },
        {
            0x1FEDDC922027184CULL, 0xA69F1CB08D9D5ADDULL, 0xE9264F5F2C86EEBDULL, 0x426B27E55B9137B4ULL, 
            0x3666273C6FC9FEC7ULL, 0x01A31EA9824D4683ULL, 0xE439A5C497DBDAE7ULL, 0x3BEA97BD7C2F6C05ULL, 
            0x3838A915BC7FE946ULL, 0x026556AC89EB2E08ULL, 0xD0346BAEBB011159ULL, 0x526478E114729D87ULL, 
            0x39BB61AFDA0DFF68ULL, 0xF5C1E7C28649ACBFULL, 0xC3250E7F52B440DBULL, 0xFB576BF009C79C02ULL, 
            0xF51B057AA6BE9152ULL, 0x2D66BA48782F9814ULL, 0x60EE997ECB3847B0ULL, 0x55C7299AEDB053BDULL, 
            0x697F82D243A34F92ULL, 0x2F805B8884064F54ULL, 0x040E1BD1EB47F292ULL, 0x18289110A5C91055ULL, 
            0x78AFA858A36D4C76ULL, 0x317DAAE6A22F7F2BULL, 0x09EBC376F76BDC0FULL, 0x55B57B4D921FEDA4ULL, 
            0xAF2028F45DF3EACEULL, 0x014B74ED3B906E58ULL, 0x28B1BA7476A17DE7ULL, 0x4D6F44BAE7237155ULL
        },
        {
            0xAFF577E2356412D8ULL, 0x51F03AE0281DCC86ULL, 0xEF804678BD9F122BULL, 0x1010DA44E988BCCFULL, 
            0x1C104F588E1FE409ULL, 0x08159351BAC9557FULL, 0xD6AB5E522C1B6F66ULL, 0xDAC647BD0E9CBBC2ULL, 
            0xB36249958782641DULL, 0x724E02C58A82785FULL, 0xD0A0D4182015E743ULL, 0xBF8EADF64C414F68ULL, 
            0x4673B047157FC010ULL, 0x72D1E8F71F13F6A8ULL, 0x9EC38CFF71341DA9ULL, 0x3B6469ACC226DA12ULL, 
            0x64329610C430E5F4ULL, 0x79692A289AF0286DULL, 0xE3D0E5FB6FB152C3ULL, 0x47FE1F7B9F139A5AULL, 
            0x5202557CFE3135FAULL, 0xD3ED0A30601CB261ULL, 0x2D4C9E4A686D5AD0ULL, 0x6D22BAB30F5C5738ULL, 
            0xA5C3FA9F81A704AAULL, 0x785EC76643480F62ULL, 0x682831D211A45E9BULL, 0x3A474E19D37DD9E2ULL, 
            0x1FFC298CABA9BEE1ULL, 0x4EDD66CE2EEF55CDULL, 0x64EF7A38A73746A8ULL, 0x1C3DBA12AFCFD41FULL
        }
    },
    {
        {
            0xFC7E1F8111ADA892ULL, 0xF2702ECE2DF98D92ULL, 0xB5FB5CD876E235D0ULL, 0x5C6E07F9341E467BULL, 
            0x615E5A88B004A814ULL, 0x633A2282C3AF9EFCULL, 0xA26AB136CBE780A0ULL, 0x3FB5CE45AA25F9B9ULL, 
            0x596D63936BD5750EULL, 0x6D6672329CD7BA88ULL, 0xFF46FDC2425D4F27ULL, 0x3BF716887B4E8B7CULL, 
            0xE64E5FE406298DE0ULL, 0xE23D31A220DB66BCULL, 0x093CD52D3DC34BAAULL, 0x97A00DA64F64DCBEULL, 
            0x7EF9E14D2C77765FULL, 0xC42806627FA89D79ULL, 0x20912D1389CFF4C2ULL, 0xF75979CC9F8EEA23ULL, 
            0xC58719C37640F95FULL, 0x1D98BE57C7C15674ULL, 0x02CD84FD244D8756ULL, 0xC04626B4CCABBEA7ULL, 
            0x687D0A45D97932D8ULL, 0x2759047625F13C82ULL, 0x6262EBBD0EA37440ULL, 0xF987A0D3DB8A818DULL, 
            0xCE4FB54D0C219BC8ULL, 0x90E258D610156F58ULL, 0x18C0C7B22862F776ULL, 0xBD4403EA4AC230B8ULL
        },
        {
            0x925D2BC8DE96EB36ULL, 0x6318778D79E887DFULL, 0xF7343E6ADE7932E7ULL, 0x6A071D4808D032C4ULL, 
            0x1AB37E0B56A3F091ULL, 0x046B4E483654681CULL, 0xAEA1DC2E604D21DAULL, 0xCCA7DB2721FB33EFULL, 
            0xD8EB190FDF18FC98ULL, 0xC1ABBB7219E125D6ULL, 0x59F239A9ADDCDD71ULL, 0x7E568A540F09E6B3ULL, 
            0x203C4E0D929DA354ULL, 0x54C2DA0929003C74ULL, 0x4A71F2930F500EB7ULL, 0x9E5029F8A82D1F9EULL, 
            0x4E1097B90C222205ULL, 0x1AE80FFB4262F586ULL, 0xCDF90D582E400A71ULL, 0x6D2D60C91D023AC1ULL, 
            0x5222E74955B241BCULL, 0x15F60153E928485AULL, 0xBE73AB6FD6387A0CULL, 0x3563F1F211F6A4AEULL, 
            0x9A24C97E38F3D497ULL, 0xC0AF31F53E9B4FA3ULL, 0xBA04C675188AC370ULL, 0xB37D3591D7DDEC6CULL, 
            0x4957710572F5CC7DULL, 0x58B4E830CFE2A44FULL, 0xE3F2254478B383C2ULL, 0x1C151E7CEEACB77DULL
        },
        {
            0x2CB01E31DF0388AAULL, 0x565FE9F115BBCAE0ULL, 0x2B0AB4E6251B1F1EULL, 0xFA53601D5B98AE5BULL, 
            0xBB8ED690968B6A55ULL, 0x13C10608E3D52100ULL, 0x5F38E646354A418DULL, 0x1193F4BD51867896ULL, 
            0x2C170B3D99BE0108ULL, 0xF168EABE844DE0DBULL, 0x5A5154520269F831ULL, 0xF5582A014E7E9FB3ULL, 
            0x1837C28A0CAD7222ULL, 0x148211D1D0D0AC00ULL, 0xBA7E3F5F5406725CULL, 0xD7EB8B62DF7D9249ULL, 
            0x53B98FAF09B36CE0ULL, 0xB7C51E5D6938AA34ULL, 0xE4E1BBA7FFC89D31ULL, 0x0A3B429BC9B89F52ULL, 
            0xD591DDCC1F9E3C31ULL, 0xB7E47FD7D972E8A9ULL, 0xA6F7960F8B26F191ULL, 0x49953A5915DDE09AULL, 
            0xCB184DFC403DB6B1ULL, 0x453C07D089BC8A78ULL, 0x0B0E3ECF732F0C8BULL, 0xB612F1E98B00024BULL, 
            0x89889C05854E2255ULL, 0xA3CAF607D7705689ULL, 0x26FC448759B12194ULL, 0x780B9A8E3739AE0CULL
        },
        {
            0xDF50C3AC2C15171EULL, 0xB66A835B6CF34C93ULL, 0xFAF9DF720786CEF4ULL, 0x6A4D1A53C3F8DECEULL, 
            0x3ED686E542C277BAULL, 0x68EF03CBAA1F1762ULL, 0x3AAAF72DC70B5F8FULL, 0xA76F75F06F321E10ULL, 
            0x93F49ED437DC208EULL, 0xFF64F30F9D9CE96EULL, 0x18CE7CA815DB77E2ULL, 0xDFD24AFD7AED5D2BULL, 
            0xB63096F0892629FAULL, 0xDC96EB7C1F4B5DEFULL, 0xAD91F1EFAB08BE6DULL, 0x220773DD5EA1D733ULL, 
            0xDD52E182A72EE70BULL, 0x3B67929FC0CC0ED3ULL, 0xA3BA87387C191604ULL, 0xDAF89C5B5EB6E09EULL, 
            0x8B80F0EC3F3E7F17ULL, 0xC7F329514AEB6F48ULL, 0xE197AC0C0773A98DULL, 0xD7F2723F84134F2DULL, 
            0x15946592C72384B0ULL, 0xF3025EC95F024AE8ULL, 0xE0BC3A4C1F061517ULL, 0x1F1EA684B39D1FD0ULL, 
            0xF04989D615E03E45ULL, 0xD3836952CA31E6D2ULL, 0xE4227A33ADC6B2FAULL, 0x83C6992167A52FE9ULL
        },
        {
            0xB67FA9EA2B135133ULL, 0x29521693C3CE9217ULL, 0xBF0E4741D8C46101ULL, 0xAD8B375FDB4936B2ULL, 
            0x50A217B33327C36AULL, 0x17F99220F72A6C97ULL, 0xDF2414F327A834BAULL, 0x79627C4AB34FB071ULL, 
            0x03642CEE01365AE8ULL, 0x2C2DE3A23C3EDBA5ULL, 0x892FE4BA01025485ULL, 0x2F29CB55339DD733ULL, 
            0x0AD1115182814F99ULL, 0x842478AF3EF643D6ULL, 0xCB0B308C5F3F522DULL, 0xC58D63CD03F8CDBDULL, 
            0x0F62B74169367EA5ULL, 0x073254ADA78166ADULL, 0x0C3AB742BBF7D976ULL, 0x0458789B68B82DE2ULL, 
            0x791DF4986C97026CULL, 0x16B4A3C382968F8EULL, 0xEA654A5A622C0A2AULL, 0x8F3E403DC959EC06ULL, 
            0x95B3D1FC2E0C7FA8ULL, 0x95D2839BE99E3AA9ULL, 0xB45BD316D634C83BULL, 0xD32F957BCDF28649ULL, 
            0xA096F435A7DF1471ULL, 0x587C07CE7BE46189ULL, 0x744A56B8B8947332ULL, 0x329EBC573E4C6FDCULL
        },
        {
            0xE0E805A7FB411926ULL, 0xBA4FFE3ED785CB09ULL, 0xCBA6C578CF72D48CULL, 0xA82F8C05AD30E2A9ULL, 
            0xB77665BD04E4BAF2ULL, 0xAF28C90ECF797445ULL, 0x4D8504D61E57FB3FULL, 0xB0BC06F0EF9323C6ULL, 
            0xDA7CDA7E00D4B4A9ULL, 0xD185FF3AAAF1FB63ULL, 0x44C9022B4746459AULL, 0xE0B6730FC6611AEFULL, 
            0x78A775D693DBD154ULL, 0xA528DC46FCC22B58ULL, 0x6F0DB2ADD5958F0CULL, 0xCDD4D203C22610B9ULL, 
            0x2643ACD43E3872F5ULL, 0x8021AD6B59CD9E48ULL, 0x2653DFA484B9B320ULL, 0x65CB119184B1FA59ULL, 
            0x514FF10A9C7DF810ULL, 0x2BD172481C423D48ULL, 0x9DC232E4A02191D8ULL, 0xE29A029722123188ULL, 
            0xCD977ECD750AB9FDULL, 0xC0CF927C015BD16DULL, 0xE5A702F404C1C04AULL, 0xE9BCC12E7AA381C1ULL, 
            0x141B55AB85FBF5F6ULL, 0xC9454351A62725A4ULL, 0x4FF2115A09B601D3ULL, 0xCA74BA7B7877110FULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseCConstants = {
    0x3F16DED69C6B3E2AULL,
    0xD3B37AD9D31D74E5ULL,
    0x078711BFA18E6E13ULL,
    0x3F16DED69C6B3E2AULL,
    0xD3B37AD9D31D74E5ULL,
    0x078711BFA18E6E13ULL,
    0xCA2A633D9E9857B9ULL,
    0xABFCF85D7CF584D2ULL,
    0x8A,
    0x77,
    0x9B,
    0x7E,
    0x63,
    0x09,
    0x62,
    0x43
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseDSalts = {
    {
        {
            0xB523C77BAECFAD20ULL, 0x1E3E9667F5F04495ULL, 0x0F4034B99C8E1B1EULL, 0x71CC02C11660E779ULL, 
            0x1F5FA0A2A20FB372ULL, 0x347C9135C63E4EB5ULL, 0x4C6F86338E98125CULL, 0xBCBB8C21E7D97BF9ULL, 
            0x311F810565869467ULL, 0x7B76B580237A9626ULL, 0xF1C10909C4078033ULL, 0xD83BDE8ABB42E845ULL, 
            0x953E98FE7F8A6CD3ULL, 0x2CE9B94D4303611FULL, 0x31A8A6533C2B0282ULL, 0x4CDD8638FBC7DF1AULL, 
            0x23F2C99BBB1DB771ULL, 0x2F03EBD6F0A255FFULL, 0x463D30F86FBD8760ULL, 0xDEFD74EEDF349E33ULL, 
            0x1AFABDE5C21F7535ULL, 0x8D817B5429128BB5ULL, 0x67C5EAD5C98C3AF0ULL, 0xF6CD0FE4BE06CE9FULL, 
            0x7B0A66151C66C1F0ULL, 0xFA2A8955C6FA8D2FULL, 0xC19D84AC55F0B5FBULL, 0x9EFD722A53D17837ULL, 
            0x0EC39CAC4C43D522ULL, 0x7612BB705C0CFDC0ULL, 0x50EFA3F3CB53531DULL, 0xE583DFADA4AA6ECCULL
        },
        {
            0x274665283B21028FULL, 0xDEBCC1BC620E640CULL, 0xBF79F7C65E74192AULL, 0xDCF7455A416B03F0ULL, 
            0x59A1B08C9E46B66CULL, 0x7063B2E420BD4C64ULL, 0xB81C1D6206001469ULL, 0xBC1272E4B8C1F83FULL, 
            0x23D2AFD6B3E94915ULL, 0xB772B6A8E9F3B38EULL, 0x5261DCFEEEF66B27ULL, 0x75987679B652C892ULL, 
            0x3C09B0C6D997E8BCULL, 0x1FF175B9206CD405ULL, 0x53895C77E2EE183EULL, 0xDE2B955003AB6891ULL, 
            0x9E3050EA42C847D4ULL, 0xFFF12FD2D5200FD3ULL, 0x2F5A04F7E0F7B62EULL, 0xB667F1EA501B1E7BULL, 
            0x41572C8F6D09BE37ULL, 0x2F14D1D0D8BF15A7ULL, 0x63AE7C9680454B9DULL, 0xC33C3046CAE8C189ULL, 
            0xC18A05DF880B809FULL, 0xA8B00AD1B9DE3FE1ULL, 0xED1D71BEACC822EEULL, 0x2B4241483239C3F0ULL, 
            0x043D0682D673A2C4ULL, 0x35CBDBB78A9E0EB8ULL, 0x2FC402591D1762DEULL, 0xF3BE07499270A7B4ULL
        },
        {
            0x4EF1A4FEA337B03CULL, 0x18A9FF2E1C9C1585ULL, 0x627EFEFC09A89A53ULL, 0x14BBD398A8E802A3ULL, 
            0xF97CB96D803AF261ULL, 0x1C63A4BE9EF16B48ULL, 0x43BCC16F330F958CULL, 0x7B2F5042222D625AULL, 
            0xF8B03085226FA4E7ULL, 0xD6EE1FBBAB94B525ULL, 0xEA7E834CB7A8A097ULL, 0x1517A999062B3836ULL, 
            0xFF935143D82DD330ULL, 0xDD723E6998606273ULL, 0xD6DCF90D40C5B274ULL, 0x3F43234DB8C6A28BULL, 
            0xF9A0E6D8A3C3CE4FULL, 0x7FF8BF1C3426BAFDULL, 0x4330188E772181A8ULL, 0xF35E1DC3BC8419CEULL, 
            0xE62549CC6BEDC433ULL, 0x69E7095E006C314EULL, 0x3E5BDFB6336F9705ULL, 0x2B11F9ADB1132AA9ULL, 
            0x6A38C9D93D6E56D3ULL, 0x526A04CDA955BFBBULL, 0xE581FFA683009DA1ULL, 0xD9B453F4912B98FFULL, 
            0x482EEC76FC4182CDULL, 0xFB6263B0F7ABC184ULL, 0xFDECC926EBF14CF7ULL, 0xD815379DA1BCBDBFULL
        },
        {
            0x6148E7B088B1F879ULL, 0x90CC0FA89A7CEEF4ULL, 0x66C8085BDCBA40B8ULL, 0xC0BE81BFC50C9C10ULL, 
            0x9F3AA7631D74ADB5ULL, 0x3709D2C01771E21DULL, 0xADD17CEC5637A985ULL, 0xE2809A1B4780A8DAULL, 
            0x580E006FA3ADE614ULL, 0x4063A6168D9AE953ULL, 0x9F910A93DF533F0FULL, 0xCB1A43C3E436817EULL, 
            0x0CCCD4A222C2F4F1ULL, 0xA9D087875B1D77B0ULL, 0xF5083BB984B0C2B8ULL, 0x698FE4F6093E15DCULL, 
            0xA26FF564907B82A3ULL, 0x0E6B1099C72285BBULL, 0x71A5CBAEA3BE41C5ULL, 0x6BBC3BDE7E27C7A4ULL, 
            0xAD7DAD31F840E4BBULL, 0x02C417CA79AB88B7ULL, 0xAC81EF7382120FEBULL, 0xCA80C622826AF770ULL, 
            0x22187178AFA11A66ULL, 0x764A66ABE26CC7DAULL, 0xF4928812744405C8ULL, 0xD3D348DE55D61BF9ULL, 
            0x86DBDC8789CDECE4ULL, 0x9DB9DE5D56572077ULL, 0x88A7C5D13A753F36ULL, 0x28F859923DDDFE94ULL
        },
        {
            0x8316DCBABAB912F1ULL, 0x7C50D3A3397EE8D1ULL, 0x4571FBB782356CB6ULL, 0x5E15B619F9C9D73DULL, 
            0x9FD224C4A095CAADULL, 0xDC5E8D68B5859CE5ULL, 0x808ED17B395574A3ULL, 0x73EE7527B2AC0767ULL, 
            0xBDA88A338DCDD5AEULL, 0x655024E797B00DE8ULL, 0x40FD2482B8D6819BULL, 0x520375B80F9175D2ULL, 
            0x2DB815D81308C142ULL, 0x005159992EEA6FA4ULL, 0x472F676EBB1C1FA1ULL, 0x09DC9267CF5123FBULL, 
            0xF33201120B0C1495ULL, 0xE5115D70DADC6194ULL, 0x80A802CCC9D12BCAULL, 0x8F072590BEBA5C7FULL, 
            0x672AE634B95CFBA3ULL, 0xE51C031718D39C25ULL, 0x5EA0F50B2348CCCDULL, 0xCFF49986890F1BFCULL, 
            0x10AF8544F7510AA8ULL, 0x7316D92D96E031CCULL, 0x261656E8FDFEBC1AULL, 0x2FC577FFC2FEC7E1ULL, 
            0xF3963F55A3427857ULL, 0x2F0C83EEF787971EULL, 0xD53C212653110813ULL, 0xD25CD4C051EEC570ULL
        },
        {
            0x3DF9C61B65B9301CULL, 0x3973BDA8BF5EBE04ULL, 0xD01F348DCAD9DB68ULL, 0x73F5245F0C37DAD8ULL, 
            0x69A78BDEAFFC2A38ULL, 0x5ACBF1DD3339C1FAULL, 0xA4427AF9281910F2ULL, 0x24F3D3E2625E1B1AULL, 
            0x740D31276CE800DFULL, 0xA9DAA13DC9B707CEULL, 0x8953FFB3665F1426ULL, 0x913C98E7563342D7ULL, 
            0x92B84F047ACF2A5AULL, 0xE44597F2AF8E8938ULL, 0xDB3367C76BA116EAULL, 0x849CAC4DB4ECFD45ULL, 
            0xBC63CAB026BEBDF2ULL, 0xBB39DE6CE2619FCEULL, 0xB640AA310E5E9BC8ULL, 0x740B671F817159F7ULL, 
            0x411E25BF9A2BAB36ULL, 0x7EE638A8B60B17D4ULL, 0x79AC0E1EB793A086ULL, 0x188EAC25A926ACF3ULL, 
            0xF432C572127FA1A2ULL, 0xA0E8FB090E3F7370ULL, 0x5677D17C394CDB82ULL, 0x58F053C7DE59D555ULL, 
            0x0C9C06B14C5B924EULL, 0xC060A96552E7F001ULL, 0x3ED98BFF425BDBBAULL, 0x5439F68E8950C870ULL
        }
    },
    {
        {
            0xF821B90FD88BDF12ULL, 0x834A629F3BB454D3ULL, 0xFFBD1601EDE551DBULL, 0xE521D63D2ACC3534ULL, 
            0x496E442522D5434DULL, 0xBE5AB07DC45A07BDULL, 0x52997A7158EB3A4DULL, 0xE2A524221F2807BCULL, 
            0x1255919D43B3E360ULL, 0x37FA4668EED2385FULL, 0xB106BABF75C6A171ULL, 0x986E61943E99ACD7ULL, 
            0xA3C2D7D21A4B5394ULL, 0xA53681B371F5F865ULL, 0x16E0545E158D6477ULL, 0x3AFF2248DEED8659ULL, 
            0x21ED22AAB0643AF5ULL, 0x2ACE9F2EE6C0D15BULL, 0xB2C730007FA6D84CULL, 0x46BFF600C89BC702ULL, 
            0x496F7139E7DAF9B5ULL, 0xF9BA5C1BF719D16BULL, 0xF514FF363E7FA673ULL, 0x684DBB66818AC5E0ULL, 
            0x0D32CF0BAA8B80FEULL, 0x49CB484571B374F8ULL, 0x92C6D702897680BDULL, 0x19428F1DF6A70ACFULL, 
            0x72B5D9DE204B436DULL, 0x3C3213281875D798ULL, 0x5B5876C3BCD101F1ULL, 0x682D07FD5EF4A3C9ULL
        },
        {
            0x2ED213EAAAE73AA1ULL, 0xED4E22AB27B2124CULL, 0xB9EDC475B72FD22EULL, 0xF9F9549DA3C2D209ULL, 
            0x56F9C8F02952487EULL, 0x7970F396379361D4ULL, 0x57DC7FA1B7F6278BULL, 0xF1A0E2795E2F2649ULL, 
            0x4C4D093DE18550CEULL, 0xD9B385E8CD4EB7D7ULL, 0x50FA2DA8406D9A73ULL, 0xB59D3FDE15E07D09ULL, 
            0x1246B6AEDDF08EB2ULL, 0x633CC18CB56077DEULL, 0x8901F4CB05FF01CEULL, 0x230BA49C05BF8994ULL, 
            0xC205EE4EE97E0660ULL, 0xD4011BAAF106ED07ULL, 0xC00CE00970AEE267ULL, 0x0FB74813879EC6DCULL, 
            0xCF43BFBB7BC5F5D6ULL, 0xBD8C3BE1DDCC98DDULL, 0x22FACEEEE2609E2BULL, 0xDFDA016669339292ULL, 
            0x39FFC498DDA3D252ULL, 0xB986568F06B80F88ULL, 0x106173BCB5B1FDE2ULL, 0x9CB9ABE4290045ECULL, 
            0x6F8EC684BBF911BCULL, 0x62F161B90773D064ULL, 0x42FD350EE81DCEB4ULL, 0x88CE8AC606BA697FULL
        },
        {
            0xB16A623EECA8E9FBULL, 0x3C4C5B3B94E8C6B8ULL, 0x1AB34D04B8EA5BE8ULL, 0x9FAFCA935B3B6031ULL, 
            0x3ECE4DABB73DF2A5ULL, 0x7E382F01CB2F2538ULL, 0x1B78B7987C21F46DULL, 0x8F19D3D9E41E737CULL, 
            0xC72B239BB0BA8081ULL, 0x28BE385F6090A0A5ULL, 0x4BCC46CC3D9DA185ULL, 0xED6AD252DF3BA754ULL, 
            0x9D592F1E21567308ULL, 0x4DF3350FE3F809EAULL, 0xA172795966741FF6ULL, 0xB3586AAB2542AF10ULL, 
            0x68851B34283A7CDBULL, 0x8A7761B27EA263C8ULL, 0xCA3B7DE10668282EULL, 0x985216B178A296C6ULL, 
            0x064AAEC0F78A4FBEULL, 0xDAA2C773381DCD09ULL, 0xCC106BD92DE210ACULL, 0xB2D07860878693FAULL, 
            0xA36354A12E0B678FULL, 0xF87B9A25E92C04BBULL, 0xEF0EBEC01A4B2DFCULL, 0x91EB510318F52B43ULL, 
            0x638FC384EB1C546EULL, 0xB44F44A97DA3556FULL, 0x123791C27F7C333BULL, 0x902C2EEBA461E458ULL
        },
        {
            0x699527B04BA382AAULL, 0xC5F48B9799228C2CULL, 0x9CCBC3F29D830DA7ULL, 0x74ED043AD156B630ULL, 
            0x711042CB0B90D549ULL, 0xB1CFC6039297CCE4ULL, 0x7C81ACB03319413DULL, 0xD8C3779117749831ULL, 
            0x0C637224CB2A4E68ULL, 0x614D1BAC1AEAC19CULL, 0x6C8293052994998AULL, 0x334BD698F2328F87ULL, 
            0x6BE3599FD4EA4B80ULL, 0x92D6ECB35A221063ULL, 0xB466755761DA2962ULL, 0x960DA8635AB5A491ULL, 
            0x12FCE73CFFFC2122ULL, 0xB2CA084537A3C5F4ULL, 0x8ED072E2BA697EB2ULL, 0x7289A9D60ECEEB30ULL, 
            0xC8C7567A3F70AF57ULL, 0x04727EA31F630657ULL, 0xF50C4E7A402848FDULL, 0x6677A35A3B000253ULL, 
            0x2EB7311CE80565AFULL, 0x11180AC3AC059E18ULL, 0x78DA1B6B8EBC54A8ULL, 0x1D9213A820265082ULL, 
            0x7C5483419E42694DULL, 0x25C4A7213E2E30EDULL, 0xC9DCC1C80DB649CEULL, 0x2A6C78C09100D756ULL
        },
        {
            0x44103983367350B3ULL, 0x14AA16BE6AB1B79BULL, 0x5F5E55E9E09F8221ULL, 0x253381995E74BF62ULL, 
            0x4298951055B44077ULL, 0x97862CE97B661C4EULL, 0x811423949977CFC0ULL, 0x4440ED42DBEDE269ULL, 
            0xC2A0A94F2E9D3A59ULL, 0x0C189D95EDB127DEULL, 0x19F5D9AC8AF4CFBCULL, 0xFBAB1DABA5D3F752ULL, 
            0xBFD6DF1F4205E255ULL, 0x0AF4E265A38BF93AULL, 0x8B740619D7B511AEULL, 0x6E2EDEE9B0EBC525ULL, 
            0xD64AE860448F44E5ULL, 0x2ADFB00F5EFA97E2ULL, 0xEEBCF97C97697396ULL, 0xD0C21A8119A5462DULL, 
            0xAFC0D490F6624981ULL, 0xA37041FE71D54AA3ULL, 0x4511F4DAEA9C42B3ULL, 0x7ADB31D68394E3B7ULL, 
            0xA5EB40F5DF0E2C11ULL, 0xDD87D93F63781FCAULL, 0x424423763D8F9D98ULL, 0x801A20A0D1A9EB5AULL, 
            0x50D283737E9F7581ULL, 0x060DFBC2517F4567ULL, 0xFD5F11007D372068ULL, 0xA334A9DBF0DE75A0ULL
        },
        {
            0x213F3616557E99BCULL, 0xBFCCB03935A25344ULL, 0xAC37F5FA7E76BF2AULL, 0xE13A42198708867DULL, 
            0x961D44F20B683BD6ULL, 0x409C717C3DB0A241ULL, 0xDF25D6509FC29CD9ULL, 0x16CF336E4528A61EULL, 
            0xED8C97C4BE20016AULL, 0x4B6FA6DE0964A362ULL, 0xB5F96E8699435E4CULL, 0xF008559F79F67469ULL, 
            0x470ACC0299209659ULL, 0xD9A7A65338D57B70ULL, 0x81FB5D93FCF7B103ULL, 0xDAD9371E2478EE03ULL, 
            0xCB647338707A0DAAULL, 0x0BDE4A4A9CBF2805ULL, 0xE4DC17B5A02FE223ULL, 0x0E022853FF7D2022ULL, 
            0x8EF9BE29BA3DC4FCULL, 0x92DDF5734F0B6CC3ULL, 0x45ABA31FD24AEEC9ULL, 0xF68EED59922C1664ULL, 
            0x167B05AECD09A137ULL, 0xF5546CD552837A16ULL, 0x1947FAC3FBCA16B3ULL, 0xEB190D60FAA27F0FULL, 
            0x7A192EF1F6DF9F48ULL, 0x12EB9581E219027BULL, 0x284E30F27BE609C0ULL, 0x19EE4C104FF42F8BULL
        }
    },
    {
        {
            0x27D6DEEFE8B2D46FULL, 0x493261147B81EBB7ULL, 0x56CA13562D6D692BULL, 0xF7A734C2A1634ABDULL, 
            0xE67979968FE85F21ULL, 0xFC94064EF9CD8003ULL, 0x883B0315EA818E74ULL, 0x32B07F30173AF158ULL, 
            0x45BBEAF6623AD0E8ULL, 0x62C26A69C6E8D004ULL, 0xC374D8A496EAC333ULL, 0x3EAAC7F936730BBFULL, 
            0xAFDB071E4B05741CULL, 0x026200C578C7876AULL, 0xA058A7B9B52F2F5DULL, 0x9F07A52B69951EE1ULL, 
            0x03336718085871BFULL, 0xAA9D9B0E67FF8544ULL, 0x2DF4BAADE89FC3C2ULL, 0xFDAAF5F966870E63ULL, 
            0x3683A403D63A3C24ULL, 0xFB8CAA4C95A60EABULL, 0x6E6BE1031162506FULL, 0x8BB235E2CC0554AFULL, 
            0x0F681E68B3A4FD84ULL, 0xAAB698673B120262ULL, 0x65F9B3EA3D11DE2EULL, 0x31DA30F63E44D182ULL, 
            0x56952AEDDAC690A6ULL, 0x147A90DFC8BA3FBDULL, 0xACEC849F230D23A0ULL, 0xAB6F30F2C7531AC2ULL
        },
        {
            0x60F0DD65ECC2F0D9ULL, 0xBAF856603372F8A8ULL, 0x095339768BE76A20ULL, 0x7722FD97C67C806AULL, 
            0x2E067E2844D9CEBFULL, 0xE571DE4CDC3F7A8AULL, 0x9429BB61AFC4401FULL, 0x1E133C1DB29A93C8ULL, 
            0xA6B1A4DAFD2E7DD1ULL, 0x1FF838F3820E41C9ULL, 0x3C4E072D966A3F15ULL, 0xAD1723ED5275B603ULL, 
            0x9C94B7D2A180477BULL, 0x9CA9FE7BA88E1C87ULL, 0x6C51F800549BBA24ULL, 0xE3F8D24D2C22752FULL, 
            0x7D68947108B68305ULL, 0xE8FA2010969866EDULL, 0xF24380AA1631EE9AULL, 0xF0CE775CD0C5C3D0ULL, 
            0x7D26BF3F2B0EA0FFULL, 0xCE56893DF1509ACBULL, 0x6A04FC42BF1C868CULL, 0x0DB0619468A31776ULL, 
            0xE2A1209A4D717A2AULL, 0x99D579334D10DD86ULL, 0x8DA602EF383FA837ULL, 0x2FBAA76621D7D7D5ULL, 
            0xAF845BF660C7CD15ULL, 0x2FA78EF3A78273B0ULL, 0xCA9A10C71B97708DULL, 0x9C45A3AE5E83C085ULL
        },
        {
            0xB23B506283B4249FULL, 0x20327906EB9BF625ULL, 0x2BCFB5BA9403AA47ULL, 0x8129A43E1D1AFB8FULL, 
            0x16F9CAA1FF7667A1ULL, 0x092BAB1DDF5F746CULL, 0xD4F9B1FABA791B8CULL, 0x417B461FD016BDEBULL, 
            0xDE9F220BF9F1B49DULL, 0xAD7058ECA50D2FBDULL, 0xC7CBDCAAB8528710ULL, 0xB202B32F8055CC56ULL, 
            0x1B86C216C986ACCEULL, 0xB6104D0C032F5E04ULL, 0xDB743468AEE5C8CFULL, 0xAE0A642C1564F125ULL, 
            0x96216BFEAD3A2B58ULL, 0xA18CB8E289ADD5F2ULL, 0x60EFDDD3FBC62A20ULL, 0x64584B76C7901194ULL, 
            0x3BC19A411E168454ULL, 0x61A77286AFBB44C5ULL, 0x42549B0B9C2715EDULL, 0xF4FDFE24446FC122ULL, 
            0x3173C3331A6F53F2ULL, 0xB253D25C84BB3486ULL, 0x63DB037EF2913352ULL, 0xBE3FAF30DE93D419ULL, 
            0xC45F7A8BC4653B1DULL, 0x78F2C6CBD99580A4ULL, 0xF795E5789C0D2DF1ULL, 0x22F5952AB3C13940ULL
        },
        {
            0x1DB07E40306ACF75ULL, 0xA342BCA204F43D94ULL, 0x501F0BBE5FDEA7DAULL, 0xDE07BF027158E588ULL, 
            0x4E490B041FDB66F2ULL, 0x9E22B32A211653E8ULL, 0xC1EA8A91DC7A06BFULL, 0x01B670AFF93F1F89ULL, 
            0x88635F3721530A28ULL, 0x40F43E139234D3DBULL, 0xA3F13DFDB1BF41CAULL, 0x440F3A021CA66624ULL, 
            0xA4DB6526B637D0BEULL, 0xFAA70D395810A139ULL, 0x402920CFAE7C48D9ULL, 0xA6864239F0673CA3ULL, 
            0xB7D5B3732798553DULL, 0xD0E23597F5E79C93ULL, 0xE8DEB4ACBB5897C9ULL, 0xF8D09F32125DCD6DULL, 
            0x7748207F5E8C073EULL, 0x2BC6BA18FEC38587ULL, 0xF522C8A2DD8CE2CAULL, 0x7773C608CB37E4E1ULL, 
            0xA6868A5CBD45EB65ULL, 0xC80D461866BD76F1ULL, 0xAF5D491891BA9049ULL, 0xC8AC1F7C19567B5CULL, 
            0x256D8A2D95329B03ULL, 0xD34A78D426A9B9FCULL, 0xC191E6206678A35FULL, 0x0B51E741D07ECEE9ULL
        },
        {
            0x92F95BF0EFA92394ULL, 0x18616BD500CF6DA2ULL, 0xC0BB68C0CDE46F77ULL, 0xE5210BC6475C5DAEULL, 
            0x2CFE61323BE928C6ULL, 0x2386C1C9EE92D442ULL, 0x9A383F62A5DA3BFDULL, 0x3DAA0E7BF38130BDULL, 
            0x86261030836BCA80ULL, 0x9080BD4D0E844D34ULL, 0x90F76D9B2DDC6133ULL, 0x96C4BE9651F41B6CULL, 
            0x35F1678FBDE11CBCULL, 0xF840A8923AF9071EULL, 0x7FCD869594C83335ULL, 0xFA9ABBF173AA8162ULL, 
            0xADFF7CB85B51C961ULL, 0x4C3591DCD3D28756ULL, 0x09B504B7EDCA256CULL, 0xAA85D135F56F1B2EULL, 
            0x4D837315E8924434ULL, 0x52C6DEEF30A50D35ULL, 0x2EA5C6B17B8075B4ULL, 0xD31EA0ABAF37F1F7ULL, 
            0x1159304DCDFA8C89ULL, 0x7A341B28451764C1ULL, 0xD9B3459C64892A3DULL, 0xFF9B7D035D1D70B3ULL, 
            0xECCECCA8902BDA97ULL, 0xD4040FAF8FD8B30AULL, 0xF90269825066C257ULL, 0x8E51507A0843BFA8ULL
        },
        {
            0x63F6800CB4EB8A44ULL, 0x49F06F90A80E8D1DULL, 0xC57F91D51C4DCE66ULL, 0xFF9D567D0C1B0F13ULL, 
            0x8235965871730B9EULL, 0x07EEAA8D44832666ULL, 0x3F876451714C1D85ULL, 0x6ACFE7D0BE616866ULL, 
            0x3343C02F0290A1BAULL, 0x99C88847EB8C4632ULL, 0xE6552E135B713493ULL, 0x3A7F1D2025384BCDULL, 
            0xDC1EC02B7B0E28F4ULL, 0x1A4FA62C8206BD3BULL, 0x07A171515A40B9B1ULL, 0x4A33481962BC1238ULL, 
            0x3902C0F673EED48EULL, 0x2CF46D183EF46803ULL, 0x4258B97F8D0AF8DBULL, 0xC1E40850756E756BULL, 
            0x03D2C03D80899F44ULL, 0x08038EA1A8462437ULL, 0xCCEA4B7C11D33207ULL, 0x8ABD21D6209D90F2ULL, 
            0x242F5D3697D01C29ULL, 0x21E82F4E833E26C8ULL, 0x5A383DF53999D1F3ULL, 0xF506C4D0644CF757ULL, 
            0x0B60DF1CFACD8DECULL, 0xDB0FC1323716EDB2ULL, 0x35FAE737877050CFULL, 0x09990B038DBCE68EULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseDConstants = {
    0x7E067333D8A297F9ULL,
    0xE27C09901AA12590ULL,
    0x6B29410E93DC12CFULL,
    0x7E067333D8A297F9ULL,
    0xE27C09901AA12590ULL,
    0x6B29410E93DC12CFULL,
    0xA27DD92B7B077B94ULL,
    0x8F6170790165C3F4ULL,
    0xB0,
    0x02,
    0xED,
    0x02,
    0x28,
    0xBB,
    0xA1,
    0xF8
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseESalts = {
    {
        {
            0xD74BB2FA92F207C8ULL, 0xB9BBD59FCA2BEC1DULL, 0xDCBF0782E7EAD28DULL, 0x2E0E27403DA82E2AULL, 
            0x1B277AD8809E591EULL, 0x63881E84F2FBA0ACULL, 0xAEEB972AA8593CB0ULL, 0xC29B0B989FFE77E9ULL, 
            0xF1D7D3956E4BCBC1ULL, 0x7A22281ABE6DA740ULL, 0x6C333DBAB4CC5CA7ULL, 0xD5C480FB3C524F24ULL, 
            0x9DF692692A36B80AULL, 0xFEB84AB5BAD4F701ULL, 0xDFD99978FD0867FAULL, 0xBA71FE85F1A9DD25ULL, 
            0x2B814EBBF4D8F1B6ULL, 0xAF842E14317CC212ULL, 0xC0F10782FFE92E74ULL, 0x7C0DA430FF5E4BCDULL, 
            0x2869994EB390687BULL, 0xEBDD68C04F7F9692ULL, 0x67BA72E192FAC0C3ULL, 0xCC64E899624D543DULL, 
            0x91818982C62DA699ULL, 0x51AD0A0B307D180BULL, 0x95F568A2E2BFA080ULL, 0xB0E3FA1DF4335352ULL, 
            0x82D0F1278E3DB7BFULL, 0x57A6C13E32E6F42DULL, 0xFBB522407AC9F49AULL, 0x06C47F4630BBFA4DULL
        },
        {
            0x131A5E2013C27C89ULL, 0xAE1D3A9524AA7AF5ULL, 0x01C2549A0AE68FA9ULL, 0xF82B1696FAC25F17ULL, 
            0xC958115B61DBD29DULL, 0x9FF09726888D107EULL, 0xCC1B26BF72A7DB48ULL, 0xA77984D32032A5B1ULL, 
            0xAA7F30C0D535CB37ULL, 0xD2E7CE6E0440F14EULL, 0x3C6CF7F5680E7DF5ULL, 0x58C8847E01CB6F38ULL, 
            0xDE1AC392317634DBULL, 0x72F1330BA5156DA7ULL, 0x229A93F5E887FE4EULL, 0x30A46E14D888B393ULL, 
            0xAE88393F77A689FAULL, 0xC1D3A3E331D4E083ULL, 0x1DF66BE7B1DDE146ULL, 0x47F3863EEADB6303ULL, 
            0xB62A95EE86FB5721ULL, 0xD8F94C837DA8F760ULL, 0x575195DB061999EAULL, 0xA69D54163A2B60F8ULL, 
            0x8F4C5A2A0A23C1D9ULL, 0x963DA2E652967877ULL, 0x0878791E13BB2336ULL, 0xF1AF2ECED1F127B6ULL, 
            0x48170E3DFB08F25DULL, 0x9FF4CD789F754C03ULL, 0x5002A0954B2BE411ULL, 0xD07A2D230778CB42ULL
        },
        {
            0x8445C4B8E8DBAF6EULL, 0xFBF4DF1E56D977F2ULL, 0x23C1AB2A2BE3D863ULL, 0x0DB6D7698BC65769ULL, 
            0x94FD9C55F79E568AULL, 0x9083F3552594A539ULL, 0xBA88AB5971748CB0ULL, 0x4FD9E8322D032A25ULL, 
            0x6077130D3EC76CFFULL, 0x1EACE31AB10DAFA4ULL, 0x43E9DF3AF4120B2DULL, 0x01D5F545E6F1FF15ULL, 
            0xDED332B82457DD2DULL, 0x73984F3138FF7A26ULL, 0x9BCB41356A3874C7ULL, 0x04E21508C8A9F190ULL, 
            0x79200176321963D5ULL, 0x045905FA97AFE96EULL, 0x796AECBCB88AB0AFULL, 0xFDF232277DDDDE65ULL, 
            0x505F484F4F554F0CULL, 0x2D12509B20478CBAULL, 0xDA90A6241EF4E429ULL, 0x9261E02790D0286DULL, 
            0x9C1982013DD148E3ULL, 0x1C6EEBBBEFB292DBULL, 0x3E11AC883BC1984AULL, 0xDE55BEFE8AA8C28EULL, 
            0x803A7AAB7E3B8A68ULL, 0x7A330CC8B27FEF65ULL, 0x64D66587E11450FCULL, 0x6799AA4EB56D0FA9ULL
        },
        {
            0xFE3C8742DAE287C2ULL, 0xD3CDAADC6D9A8370ULL, 0x99644017D46C6CE2ULL, 0x6F553A9EA66D71DAULL, 
            0x2FEF1B95856C48E2ULL, 0x85E40C3ADF0C4E93ULL, 0x9538AEDB8B3EB105ULL, 0x70D4D7F30600A8BBULL, 
            0xA500F14A41C42FDAULL, 0x15E0691320B7615BULL, 0x9293CDB21609A383ULL, 0x686A9897D9D26630ULL, 
            0x1FE351F757745360ULL, 0xA3A878B7981B4FE3ULL, 0x22885EB513D15B56ULL, 0x182200788A1A070DULL, 
            0x22748C881E587A17ULL, 0xD419C96D3DC220A4ULL, 0x9F367943B6EBD1A3ULL, 0x84BDDB95A9CE9F72ULL, 
            0xCC3F91044D322466ULL, 0x552AB60FF1206958ULL, 0x6B2332BCA905773FULL, 0xC781EEACE654C322ULL, 
            0x4A916D605F37374BULL, 0x2963377FBD4EDA0AULL, 0xEED155EE97CC59A4ULL, 0x333418A195814A59ULL, 
            0xBCAB9B7C94C2BF02ULL, 0x4968D9403824DE3DULL, 0xA31F5A094127345CULL, 0xFC535D4ED9CC62EFULL
        },
        {
            0xB362F583C1737EA7ULL, 0xED8AFBC9CA1023E4ULL, 0x6E428918B1C52F55ULL, 0xBEE9A44C83CDDFE3ULL, 
            0x5EA332CA240E2633ULL, 0x708D0CF642456A68ULL, 0xC4E402388EDA0BDFULL, 0xB1A70131FDD45C8EULL, 
            0xB1E95B9C0447DA7BULL, 0x5F3BD54FDFC53BF8ULL, 0x8FD629860045966CULL, 0x8B39366336CD7E53ULL, 
            0x0B6B824F8B5BC31AULL, 0xB383CB9466BD3955ULL, 0xD9F44B6216270761ULL, 0x4A68A20BACCB3A9FULL, 
            0x993F55B2FD3236C0ULL, 0x8486BDF5ADDCAA1AULL, 0x0309BE220CFDA5D5ULL, 0x74138C77CA31A1E3ULL, 
            0x0C9BD01973BB238CULL, 0x1E41CFCEA09ACC4DULL, 0x8EEFEF385436815FULL, 0xF10482A3138FE148ULL, 
            0x02F4147380A4C05FULL, 0xA23740EFBF0C7E0BULL, 0x12567999505E597CULL, 0xEE795E9917E295C2ULL, 
            0x4020D93D7A76BBD7ULL, 0x6BB16892C0C69ED9ULL, 0x23FC39562F986760ULL, 0x64A943CE33EF56E8ULL
        },
        {
            0xBCC57AB1F81E3552ULL, 0xC44E26F13C668288ULL, 0x7B117EA84C2E8837ULL, 0xC33DC76BA525946AULL, 
            0x704AF1E5C92454F2ULL, 0xB7A3816D2B4442F1ULL, 0x5E5971DF9AE61A9BULL, 0x50E7FF342EF4B06DULL, 
            0x0B989D5431798098ULL, 0xDCED40B6BD4051DEULL, 0x60618B5B9606DC02ULL, 0xD38AABDDC271D439ULL, 
            0x70E2D159A6A32B74ULL, 0x4490CEEC59703848ULL, 0xF94F97E114BDD370ULL, 0x2AD4DB35B389367CULL, 
            0x809ED0D833A43F24ULL, 0x0C5C6A16D2B684BEULL, 0xB8AC7347D7D19A1AULL, 0x1913587C24EBD09AULL, 
            0x64B20D02174E7E30ULL, 0x7575FFDCABB218B1ULL, 0x1793E0EDD5254587ULL, 0x42ACCD11BAAC2AF2ULL, 
            0x3366242DEC214CD3ULL, 0xCE9975CBCF05E933ULL, 0xDF21A80E8662F695ULL, 0x89BD6E994EFF0B5DULL, 
            0x4D536657E4338161ULL, 0x3264337EBB365B71ULL, 0x1EC46B08E89F1EB1ULL, 0xE1063F58C1FE6C7BULL
        }
    },
    {
        {
            0x680503808812E1B5ULL, 0x6E5334D9F6F2BD8CULL, 0xA6B975EAAD08426DULL, 0xF8965A731E42D22CULL, 
            0x84B91845413A968AULL, 0x7E8726313CD0AECAULL, 0x1639F086C1A336B0ULL, 0x7A0168E8CC564626ULL, 
            0xD7784E4E2B956B09ULL, 0xABDB90BC70C4D371ULL, 0xF607421FDAB642E1ULL, 0x67AA46BB8BD6DD90ULL, 
            0x8F74596984FECE5DULL, 0xFDFBFF8DBD17C859ULL, 0x4833137FF99BE5DAULL, 0x3CEC481DF799DA15ULL, 
            0xF251CD60F7F80B8EULL, 0xB01D1CC61CAC93A0ULL, 0x2BE3788595A72E1DULL, 0x32DC32D36AB52C1DULL, 
            0x2C915282FD4653F7ULL, 0xD50AA21C451AF3F5ULL, 0xB460DCF82D80896CULL, 0xAD30E2AE4806CEB7ULL, 
            0x6A1F0264A18C8D67ULL, 0x266F3BCA13B7FC2BULL, 0x4BE70462B50D369BULL, 0xA5754DB246A2C893ULL, 
            0xFB5370FE2492A498ULL, 0xF57E9A560DA60CC3ULL, 0xF7F0AF872F8BD953ULL, 0x4AB90D9394B5958AULL
        },
        {
            0x43BCC31422A6C827ULL, 0x2AC5ABE4BA8CC9E3ULL, 0x2DC08646F6AC157BULL, 0x77B13FBBE495E561ULL, 
            0xA3ABCC5B9897DA2DULL, 0x72DD9DB89CF52D5FULL, 0xDAF3AF442154824EULL, 0x27984FC885ADA07EULL, 
            0xB8E4C35EB43D3C77ULL, 0x2AFD5E692CCFF0A3ULL, 0x70E7F6EC45FEFACDULL, 0xF2B0C0472D22A831ULL, 
            0x124A0FC8A5908586ULL, 0x1409FA344867A755ULL, 0x7B1228CFAC8B6945ULL, 0x0DC93D7FE0442119ULL, 
            0xA6801FE64395A944ULL, 0x80CE484FAED6A727ULL, 0x8B4A9E1C939B4D05ULL, 0x326AB2CF8D6BBB6DULL, 
            0x06C0B826C094E2C3ULL, 0xDC969FECBBA2E9CDULL, 0xBC3248277A3972FFULL, 0x35FA5CC6FBF39F90ULL, 
            0xE31FB8CA89B7AA5BULL, 0x66FB0DB5543696E1ULL, 0xFA3B8F73CA35F0F3ULL, 0x743CFF7D7A9CEAC4ULL, 
            0x92F25A55A8898596ULL, 0x29F18367B07789FAULL, 0xC7D1A274B83DFF6FULL, 0x6E0FCACA505BE720ULL
        },
        {
            0x4AFCA0242FD8C642ULL, 0x4F3C2DEF6952A65BULL, 0x6255F043DFAECE84ULL, 0xE01C16A02A82FDE3ULL, 
            0x637C7CEE631EF116ULL, 0x2ACF4BFAB1F77593ULL, 0x544A56CBC8C7D6E8ULL, 0x0A51B2C7ACFB7C8EULL, 
            0xDBA52BC28B508485ULL, 0x0387A822F70BF085ULL, 0xA237026C5D3E758BULL, 0x775EEA48D8AFC650ULL, 
            0xA385852A2BC81779ULL, 0x27F89B5097D8618BULL, 0x461D20FBFA92A59CULL, 0x9A73F26B70CD8464ULL, 
            0xCE07783142A541B8ULL, 0xF51F83B724A1CABCULL, 0x45FDE8126B8B24DCULL, 0x1818D5018B014D8BULL, 
            0xA5B189F262BC2F47ULL, 0x56484C7E10D5F274ULL, 0x032BD806425C436EULL, 0x64A14CD53ADC729DULL, 
            0x2A7D7A03D343C5B5ULL, 0xA64B5539699BE7F6ULL, 0xD833B47755232B59ULL, 0x87908C1C5A214F4FULL, 
            0x83D8EDB2D50D1B64ULL, 0xE0318CD80F47414BULL, 0x58605CEEDBB7F3F2ULL, 0x2E2B42DFFB4C046AULL
        },
        {
            0x1110410F6A91030AULL, 0x120732734B0DC37FULL, 0x911977FF52F418CAULL, 0xD5E982B806039A99ULL, 
            0xBE34AEBFA9379526ULL, 0x51D289865AA034CBULL, 0x6F7760ECB585B653ULL, 0x448C0697BA559CA6ULL, 
            0x126F0FA8DFDF1E25ULL, 0xF936D725D4EECE86ULL, 0x62E9258B2736BA91ULL, 0x18293378E71C1E47ULL, 
            0xE4BD8DF62204C606ULL, 0xC6A91F73C7A91EF6ULL, 0xB01D667E620B6363ULL, 0x95CE6278A559146EULL, 
            0x6681B9DE04CAB0D0ULL, 0x5878A9EC316FE785ULL, 0x6A9F467C14AE30CCULL, 0xB632373C5C919993ULL, 
            0xFB3FEBB4297DECD8ULL, 0x7E5DC0FB3B16BF30ULL, 0x934AD4CD900557DEULL, 0x2C9906F55E9BFCD8ULL, 
            0xBAD11237E7906A01ULL, 0x1E69FF3BB2428D30ULL, 0xB3735A547EBFA759ULL, 0x09B63F9B480FE9CEULL, 
            0xA6FE7B51E889DD18ULL, 0xB310699A168021E2ULL, 0x63189990BDD69FDDULL, 0x652B1CB8E0B61FFBULL
        },
        {
            0xD25E019290E069B7ULL, 0xE590FC9FB78FFA3AULL, 0x4E67685346781B9BULL, 0x860378118C9615AAULL, 
            0x0A6188E4E590397EULL, 0xE2E28172BEF6A22CULL, 0x571416150114D38AULL, 0x2B657A5FD1056253ULL, 
            0x315112D0AAEB9BE9ULL, 0xE9CEA015D4AADA1AULL, 0x9827037CD75D622BULL, 0xCC9F82F0F81BBC9FULL, 
            0xBE240AA4EF2B80C5ULL, 0xE1D2EB0D067BCC43ULL, 0x646C4F0142431B32ULL, 0x23CCDED3F1222F4CULL, 
            0xB1C7A7243F01A745ULL, 0xFBE10FDA4DA79FFCULL, 0xB6875C0FE5BC1BBFULL, 0x1CD6B40ACB20A589ULL, 
            0x6560633FCDCBEFE4ULL, 0x44C4ABD03E915885ULL, 0x0EB57ACFE538F281ULL, 0xCB861D59CFB27C6CULL, 
            0x1735149B12013DF6ULL, 0x8F37A2528BBA506CULL, 0x6AE6E6FA9D6C8A28ULL, 0x0E7352250F2AEA04ULL, 
            0x5ACDDBEC53BEE1A3ULL, 0xEA174604CC9414D0ULL, 0xBC57FB0A726309AAULL, 0xF3FDB54C6328F18EULL
        },
        {
            0x68A43DA6F5DAC3EBULL, 0x35387F9AC40490B9ULL, 0x5AE99D2E419B36F3ULL, 0x27AED5F15BC521B5ULL, 
            0x11D873A08D8A365CULL, 0x9752CAE8B3E518CEULL, 0x1255445A8F4D65C5ULL, 0x1545A520ADF02F83ULL, 
            0x5CE64580829F55ECULL, 0xB8FDFAB964B5686AULL, 0x6AAD37E8C02265BCULL, 0xC6D72C9C1BF3D32DULL, 
            0xC930608EAFD2E710ULL, 0x863D4F7E963E51B3ULL, 0x46B1D8B66C3A7A4DULL, 0xEDAB2E42CC75F608ULL, 
            0x08364D3803970E68ULL, 0xCBD8D3042D38BAF5ULL, 0x4CA7D856B62E4374ULL, 0x7A59E23AEDCAE3C3ULL, 
            0xAC1921CC2CCA827AULL, 0x9A941E7FFD506474ULL, 0x75C34D27E5E56952ULL, 0xC027A70460724187ULL, 
            0x25786A6CD76377C0ULL, 0xD482BD75731D28B9ULL, 0x420D866EB5F295C6ULL, 0xAAD431A8A85E818AULL, 
            0xB08B0A3F40EB2A39ULL, 0x97C1B13C3885AA52ULL, 0x27A2639168D72F46ULL, 0x33FA3E6D27198C04ULL
        }
    },
    {
        {
            0xD9F2C592A12A4AA8ULL, 0xE93DE49467D020F8ULL, 0x30B36CAE8B40F537ULL, 0xD8FD4F6AFE32DDDAULL, 
            0xA34D04CE28FF579CULL, 0xE8EFBB1DA4D3C625ULL, 0xD00E2E785A0C0FBDULL, 0xFB7E1C4B2CF7C937ULL, 
            0x0B9EBF85B4D47010ULL, 0xB55F8BD3E5B72E72ULL, 0xA39130ADA58AD106ULL, 0x70358C675FC33796ULL, 
            0x2B9715DF59AEC8A3ULL, 0x8E92EFB2EF2ED4FAULL, 0xC55C435777453E3BULL, 0xC09EF632391197E8ULL, 
            0xF071E225D644391FULL, 0x8770E5286AB21F3BULL, 0xA47583AFC877C549ULL, 0x2468D70D9A1E5753ULL, 
            0x6AEB304340269DF8ULL, 0xD20A5433A8B9F62BULL, 0xA5CB52F366EA8C80ULL, 0xB86E8B6BF1FF3C49ULL, 
            0x00D8F9E30C2803DAULL, 0x161A449F2D4C9CF5ULL, 0xE26B303DEF1172B0ULL, 0x7C4DD3867B6FD107ULL, 
            0x40CDEB7FF48E2742ULL, 0x358C76465C66732BULL, 0x60C94958C1FED114ULL, 0x3ED4D1A244CEA72BULL
        },
        {
            0xD34C017732F57C6DULL, 0x8B36F1CB722EC977ULL, 0xCEE933D40792E891ULL, 0x8EF0B42B428C1D26ULL, 
            0xD13A7093DFABFC47ULL, 0xA5B8580186F17461ULL, 0x1AB92188E5D4F43AULL, 0x6BF629EF2447789AULL, 
            0x7C8CEA9F7C5DB866ULL, 0xC73BB87210CD74B9ULL, 0xBD75238637E85AA4ULL, 0x49C5666FEA01BF66ULL, 
            0x2CFD62014F9673DFULL, 0x544F7F71FAD750E4ULL, 0x125BCF3F0B21B707ULL, 0xD788801502EC5AE9ULL, 
            0xD473B0E3BCD5D58BULL, 0x4C4D5B90B86B89EEULL, 0xE3152AD5CCAAF681ULL, 0xFC66ABC3FE7B3689ULL, 
            0x45F8DF2A1D563C29ULL, 0xDAAD2D4FEC6BA115ULL, 0x1713049B21159C69ULL, 0xF2AC0E8EA6B36200ULL, 
            0x1E3CCBE6D49D9733ULL, 0xCA3A397288FA8CA5ULL, 0x9CF209307F2A34A3ULL, 0xB718D9211429DB68ULL, 
            0x799073CC7FEB26D1ULL, 0xC4D6E08DFE472551ULL, 0xD01E749EEF47F622ULL, 0xC93661BB6BBDBBE1ULL
        },
        {
            0x94E4C05650579942ULL, 0x7431091DAA3358C7ULL, 0xF6FA9EA57A070F01ULL, 0xA7347B23730F8D02ULL, 
            0xCADDFAD552715635ULL, 0x3E0C5B06E60BFF8BULL, 0x1ECB6C22E3D9BDEFULL, 0xDFD2B06E2F7F795BULL, 
            0xA75A5A80521EEF9DULL, 0xABE1BDFD3B5FFEA2ULL, 0x9EE2EC6FED0F39C1ULL, 0xB2807BEEB1B40AD7ULL, 
            0x0D0595FC5EBD3FC2ULL, 0xF2BEFE2A63C5D615ULL, 0x795F216EFC49017CULL, 0x3DCDE0FE7760911CULL, 
            0xB867546B2D158FCAULL, 0xD139577DFC0594BEULL, 0xC7CAE47469DB663FULL, 0x16D1ECF16F1FAC8AULL, 
            0x40DFCD7C9D02FDA7ULL, 0x6FA0DACC88D15C81ULL, 0x7DE66888738B70D1ULL, 0x3522BF58B4107AF3ULL, 
            0xE27479B0B4CA02F8ULL, 0xC029062A8B31ADF0ULL, 0xAD5F51A5879C5A6DULL, 0x8388A5D31EB07EEDULL, 
            0xEE75C27FFC200BA2ULL, 0xBEE81345C719272CULL, 0xFDAB446B6DA35254ULL, 0x11532B0D6945B0A9ULL
        },
        {
            0x81A4B8946CA0DF7AULL, 0x7FD46C841BC7EADDULL, 0x8D4665F1EFB66B66ULL, 0x911A288B7EEF2EC2ULL, 
            0xCFA610351AB9BE2FULL, 0x2DF8B2717035D9CAULL, 0x25BED6420F1CC8ACULL, 0x6149DFE84D7B18D9ULL, 
            0x0FB54A964351D81BULL, 0xDC08B0D95E3EAD3CULL, 0x4A53A23C4C8F3FA5ULL, 0x27F8D58E81161EC8ULL, 
            0x618FDB4C73A54B56ULL, 0x577C6773B6394F3EULL, 0x230C3890A93B005EULL, 0x0248DECD522DA568ULL, 
            0x32BAA9D3A300D46CULL, 0x73E395548437F698ULL, 0x40A2352CFE53FDF9ULL, 0x45DCAB2DC6A1182BULL, 
            0xDB93DF02BCE88D3BULL, 0xBB9546B0726977F3ULL, 0x9083195A0231EF75ULL, 0xD67CAC82C5E583A3ULL, 
            0x2945A3B17E8AB738ULL, 0xCA2FD149F68A4A7FULL, 0x5D9DE485FE06EF38ULL, 0x5D7ABCCC3AA754EFULL, 
            0x39E3E574A3CF8815ULL, 0x3890EE91E76AC9B3ULL, 0x8AD16800C4BD42F7ULL, 0xFFB2D6F1A6706BCBULL
        },
        {
            0xC88605D878E00592ULL, 0x3A956DD9E53F61C9ULL, 0x0C026B2FE2A2CA7EULL, 0x856C139630613050ULL, 
            0x5A971895D6CF2793ULL, 0xB1952637E3DCF466ULL, 0x4DF75C1A445F180FULL, 0xD1EB841D9997D008ULL, 
            0x20CBF25DF9D2C12FULL, 0x249FE6691D4D0F62ULL, 0xD1303834CD0590D0ULL, 0x412C13573922E10DULL, 
            0x2F3EDDE22DC5322AULL, 0x3F1B7298980C20B7ULL, 0xA68E81D2C39D8954ULL, 0xF4229A92FA8E0F53ULL, 
            0xAFFEC4781381ED75ULL, 0x2448F0522E7D2CFCULL, 0xA310D00F0E65B32CULL, 0x04063DF412715FBEULL, 
            0x03A6195D2D8D58E7ULL, 0x60FDE51ABC12F3E7ULL, 0xB8F2722CCC7034A3ULL, 0xEE16962DD3E2AA7CULL, 
            0xBF637E06A24DFF0FULL, 0x338DA68309059DBBULL, 0x94F7BB6CB4D8D6A4ULL, 0x70AE92F701EB28BCULL, 
            0x55AEC8600587F864ULL, 0xF24F799906311488ULL, 0xE94EAC9DE646DA1DULL, 0xA7EFE14841C8F844ULL
        },
        {
            0xCAF7A0C1E90238BEULL, 0xABFE32C2A719B46DULL, 0xDB056460639ED20AULL, 0x18167CF6C3D316FAULL, 
            0x659FD0814382CD96ULL, 0x119537F9D4175A7BULL, 0x50B74B6E8C5A5CA0ULL, 0xDAD169D4F80F7850ULL, 
            0x6BEF64BE8B31D0C0ULL, 0x109912E16F8EA682ULL, 0x8DBFA65F36C6FE6EULL, 0xBFAFD8EFA954AFD8ULL, 
            0x928403C19CFCDD76ULL, 0xC1BA9B99D87E9583ULL, 0x4CCA6A02D16E3725ULL, 0x9A53D5996A03A996ULL, 
            0x57B096E64ADA4BEBULL, 0xB248BF0F3A67FB2DULL, 0x1E3BB7F6855DD96EULL, 0x3EB7426145871603ULL, 
            0x2BD84AEB8936D025ULL, 0xAA400678E82149C3ULL, 0x193492861C60B5DCULL, 0x6B7B6EA0517AFCD5ULL, 
            0x43251AA4875EDF99ULL, 0xE8E45F91D4B2C144ULL, 0x888454FD425C03BAULL, 0x173199234C72285DULL, 
            0xD7C8653FE17A1598ULL, 0x0E99992D0BA20845ULL, 0x193DA5D0A5869C03ULL, 0x3A4806FB552A55D5ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseEConstants = {
    0xA6F1DD696CFA2E0CULL,
    0xDC6A0A11DCE7A222ULL,
    0xF6A78FA47409C0A9ULL,
    0xA6F1DD696CFA2E0CULL,
    0xDC6A0A11DCE7A222ULL,
    0xF6A78FA47409C0A9ULL,
    0x73A370D6475F0812ULL,
    0x7FFD9FB1913C202CULL,
    0x41,
    0x66,
    0xFB,
    0xA6,
    0xB8,
    0xD8,
    0xFD,
    0xD7
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseFSalts = {
    {
        {
            0x05AAFFD627015BE4ULL, 0xD9D25B855658D56AULL, 0x9C1459D6CF405763ULL, 0xDB54E05E71FB72D7ULL, 
            0xE0A71536BBBF078BULL, 0x720D82AB6C74AE91ULL, 0xAE69440A7E24E2C5ULL, 0x276B76B6BBFD86B5ULL, 
            0x5D7146EDB0FB976CULL, 0xD5BD37923D52572DULL, 0xFEBEC3F9166BBCEBULL, 0xD0051DE200937E59ULL, 
            0x9438DD8DCBA7FB1FULL, 0x6C4977D331EF3AB1ULL, 0xDBA55BD6428E124FULL, 0x6961123D6F1CF784ULL, 
            0x62B28F3E53F6FFB6ULL, 0x0D5452356B5B144DULL, 0x2C08F46D10614B84ULL, 0x66BE946051810414ULL, 
            0xAF6C8514314E17A9ULL, 0x023F4C6F09F5921BULL, 0x49E816881DA9B079ULL, 0xE179134656185F82ULL, 
            0x46724BFC1037C53DULL, 0x2A7EB260EBCC7B6BULL, 0xE1263C7A8BA67209ULL, 0x504F55C1D64BBAB5ULL, 
            0xAFE2947AF0B49138ULL, 0xF32E204BE70FDE66ULL, 0xA02282B4799E709EULL, 0x9E56909EA99011E6ULL
        },
        {
            0x615C6DB46859A7F5ULL, 0x93F1C999543BCA14ULL, 0x6ECB896BC8BEBD32ULL, 0xF500120BA54D880EULL, 
            0x270E2FFFCE2FC97AULL, 0x25E50D9EB9B8CEB1ULL, 0x31F094FD71A72E4BULL, 0x28B105CD84C472E0ULL, 
            0xD7682B5E8E9B4317ULL, 0x9729A5831998E385ULL, 0xDF6DC635E61F18AAULL, 0x7C2458F680087574ULL, 
            0xBD006121B441CD6EULL, 0xCEC2B2C1F65CC25FULL, 0xFDC91AD7D2755D98ULL, 0x048960BC00572FB3ULL, 
            0x5029FC6F0FE568DAULL, 0xD9C83CDE7E01F1F3ULL, 0xDC4450C7A23051A4ULL, 0xE5E651A6504E1B75ULL, 
            0x16125D6799C00F7CULL, 0x5386D25C2BF32900ULL, 0xAB0774330D3A2D03ULL, 0xDE90F1317B4CCBF9ULL, 
            0xA32E671604E03AB7ULL, 0x1B577A7C37D5055CULL, 0x8452F933A763ADDDULL, 0x45C22A9631A6159BULL, 
            0x22A7771871911681ULL, 0xD2B8F5E45E5002D6ULL, 0x15837568BC68ECCAULL, 0x7F7AEEFF97D03EB0ULL
        },
        {
            0x2F390A9C03D0BFE1ULL, 0xBF4BFA3037637100ULL, 0x72CDA1FE73C04F18ULL, 0xCE78463342F96E3FULL, 
            0xA022456C84861620ULL, 0xE9A48E393F26920CULL, 0xDCAFB349575ABBE1ULL, 0xD96CD93CAF4FF64DULL, 
            0xA502F0BA74EF1A69ULL, 0x90EB20C56FFC2864ULL, 0xBD2C32B65048E8F5ULL, 0xD72492C81CFFBE83ULL, 
            0x63DBAA5D521C76EBULL, 0xBDC3B33171A11412ULL, 0x31DB460D2CE65676ULL, 0x410DCC613B9E6B5CULL, 
            0x6DF777F6447A5A48ULL, 0x30CA1A1477FC2CA0ULL, 0xFA10E4D701D06B10ULL, 0xDA3E8BB66FB6E0EFULL, 
            0x1311BEDBD43C53B5ULL, 0xBADDA720CD351BB6ULL, 0x811E400402CBC92AULL, 0xA566847157A70D80ULL, 
            0xAEFE5287FD56CD0EULL, 0xEC1A79DE7C30323FULL, 0x23DD9F849E94215CULL, 0x322AD1F0B5DB63F9ULL, 
            0x91BFF275DF21B5CFULL, 0x53DE054730CDD92FULL, 0x8F6E9777A93129D4ULL, 0x54ABF2F586593C8BULL
        },
        {
            0xF33E84E52AEE0CD2ULL, 0x92E775E687417C78ULL, 0xA3A8659F64F6AAF4ULL, 0x7C36B773C7F4648BULL, 
            0xF4F5141E6DFE8038ULL, 0x42A1B480BF4B12E1ULL, 0x42EB713D751A0125ULL, 0x63C377825AB15041ULL, 
            0x653D8D6C6C742D44ULL, 0x70B9F94B4075C59CULL, 0xFD0BFA0A1C7E414DULL, 0x9E5112B6A0ABCEDDULL, 
            0xFAEF54CFA4BD3DAFULL, 0xD179940E5D4E9939ULL, 0x01613E3A18EE1061ULL, 0x77EDECD2F9E3DFCBULL, 
            0x7580ED613154000AULL, 0x94401EF9139BED8FULL, 0x9EC569F4CA9CDE27ULL, 0xA0F2B373CA1591C9ULL, 
            0xF8C1D9689E342ABAULL, 0x17A3F6A9BE52370FULL, 0x5E9DE8C1B2BD2093ULL, 0x20BCBCF63E5D839BULL, 
            0x823726B8F35A5557ULL, 0x308F0BE5B3EA8073ULL, 0x1B6B08101BA55EF6ULL, 0xF70502BD82F18BBBULL, 
            0x8519B0D5B198D15AULL, 0x06C4DC6F50495593ULL, 0x98814EECD7772824ULL, 0xA99ACA856BE1B76BULL
        },
        {
            0xC9DCECDDE3BAF192ULL, 0x2FA2B9329E48D290ULL, 0x08B30A027B9B835EULL, 0xDA5D7F3A73B705A2ULL, 
            0x7B5BE5A8C4BD8361ULL, 0x72AA6D482CEF5853ULL, 0x9D656924534C8BFFULL, 0x04F1FDF47EEE6E1EULL, 
            0x27DE13D16C47EAADULL, 0x469929098C1CAB84ULL, 0x8D47A5264D786BB4ULL, 0xA27420F8F5675A2BULL, 
            0x1A1761F14DB8F406ULL, 0x2C67791A3907DB6BULL, 0x1906DBF1CE42A954ULL, 0xB621049AE306F62EULL, 
            0x280BA8121E716A0DULL, 0x4955E79E45AB9360ULL, 0xCB7B0C815F6D7C1AULL, 0x345D0FA63E15F072ULL, 
            0xF116E0E6692ED4C9ULL, 0x00F664C0D207AFBBULL, 0x181CEDDEB8311B12ULL, 0xFE13A60F72F5089FULL, 
            0xBD5EF7B6170806E8ULL, 0xA007A3BAEE87DE62ULL, 0x94BDF67D6FFC6325ULL, 0xF90883D5C75364C3ULL, 
            0xFEE902D1D0483B10ULL, 0xE2829B58C873C3DFULL, 0xC422D261172090B6ULL, 0x8F1FA36A293EDCBEULL
        },
        {
            0xBD67A5EA5C2AB4BAULL, 0x73B511CD046D2740ULL, 0x99959C48B0446D6CULL, 0x6B15288A1181E364ULL, 
            0x5D0B9061A4DD8E8DULL, 0x99EB3A5346C26E45ULL, 0x39FED6131D390C09ULL, 0x8CA4748138217154ULL, 
            0xCF9CB7302DFEE6FCULL, 0x9163F6712DAD6A02ULL, 0x1F811272BC7D2675ULL, 0x2364CC91BCAA25FDULL, 
            0xEBF1E0B603D3D59CULL, 0xDD6313C59E214623ULL, 0x9B315F9C03086D65ULL, 0xD17AF6C9A514B665ULL, 
            0x1641DEE49575BDACULL, 0x2A8892C4B5272A27ULL, 0x6FE9CB319FFD2707ULL, 0xBE7F667604B8B1CCULL, 
            0xF37799370EFA315FULL, 0x565F993AA8E81592ULL, 0x56D0F46EB68A77A3ULL, 0xF533931FB21070A7ULL, 
            0x822580D5862AD597ULL, 0x7AA4586499F022C3ULL, 0x74C26C477EACBAF8ULL, 0x418C1A2EF6C17213ULL, 
            0x94A44291FB5E9213ULL, 0xD38C3A42FDBBB324ULL, 0x932193B9AA4AABA1ULL, 0xA472027CFC332DD5ULL
        }
    },
    {
        {
            0xBEDBD4F3515B5FBAULL, 0xBCE2C4A2178D41D7ULL, 0xC8A0FCC7FE62F83FULL, 0x16871CB40A03BE73ULL, 
            0x7358ABD92A3429FEULL, 0x042740DF1591583AULL, 0x7DE7ED7918DA0B6AULL, 0x3E16AFD8B49BA1DAULL, 
            0x3E45953B80363F50ULL, 0x86BAA14397339A64ULL, 0xBA88C872D253D6E0ULL, 0x197F665E4AF51D6CULL, 
            0x437572DF58FDEE6BULL, 0x8B696270375C19B8ULL, 0x4CCCF08D869E4EC3ULL, 0xC5AC6101B7AC1DBCULL, 
            0x56D71504533B098BULL, 0x01CDD64AFF3F9F5BULL, 0x5DA9E7C9C392D66CULL, 0xBFF8E1963C087319ULL, 
            0x2A761733839D92B5ULL, 0xA436C4AD7399D1CDULL, 0x491DC3980F00B514ULL, 0x88D642FB2B2592D6ULL, 
            0x276E69C368A0EE50ULL, 0x072B60CBE6B3B797ULL, 0xC68891B83697653CULL, 0x171E6B135410ED74ULL, 
            0x57C4D8E128928DDEULL, 0x0E6FBB438F04225FULL, 0xB29F68246760D734ULL, 0x9560D28B3014647BULL
        },
        {
            0x4A30BB485735C32BULL, 0x57BD64C6CF08939AULL, 0x1A57EC3266B71D80ULL, 0x5F57BAEA4C38959FULL, 
            0xB1C0A327EAC0341CULL, 0x25CC8C902BF521F5ULL, 0xCFE5E21EC3CDAC0BULL, 0xA08176E0FDAF45F7ULL, 
            0xA8A98429EC30205CULL, 0xC977E71AB1B0B775ULL, 0xC638B1008488F7C7ULL, 0xE528FA8681AF6ED5ULL, 
            0x13106BD433016F38ULL, 0x3F1169397F088634ULL, 0xA0C3D82DE3B53E02ULL, 0xF351A82C6EF379FBULL, 
            0xBD3A0C9604491895ULL, 0x760F4714DF2760A5ULL, 0xF76114280A35756CULL, 0x86BF2B06E7AF6CD3ULL, 
            0xA493D791FD517871ULL, 0x5177A3565FA7B30EULL, 0x5F5900553DE57E8FULL, 0xB472373F83975BAFULL, 
            0x9FFCFC859844E000ULL, 0x5F2B87D28719792FULL, 0xB1AA4F3FA76BED04ULL, 0xEEA59BC4D36B1EFEULL, 
            0x895F71243111A6DFULL, 0x0DBAE49A78999450ULL, 0x93979071CBD39435ULL, 0x8FE8D27C933D6E0DULL
        },
        {
            0x5E83960330C453D0ULL, 0x3405798EF3FA1430ULL, 0xBCFAF33E882571F0ULL, 0xA5845C9CD0262A95ULL, 
            0xDF8B79E638990560ULL, 0x99CA5EA1F41A7B40ULL, 0xE3245A68DA38B026ULL, 0xD68B33BABEFEBA7BULL, 
            0xC3AEEE12D257D521ULL, 0xA77838F7F93D3E98ULL, 0xF544D6A2802CAFB5ULL, 0x28A03094FAF1A902ULL, 
            0xC21BB40F34F22DAFULL, 0xF2DD0C9AD106DE9AULL, 0xADD4AA43246D3E15ULL, 0x8BA577DD8D622666ULL, 
            0xD46D7A9EC55E9BCFULL, 0xB895CE5A1F2A35BDULL, 0x2BE6671FE8CDE3F0ULL, 0x9634F55CA9483E64ULL, 
            0x4442E7B69C938210ULL, 0x3702E5E809351CC1ULL, 0x9E4B943EE8F6CD7FULL, 0xDE8CED29D9B1D62AULL, 
            0x58977E99493B429DULL, 0x774BE878F8CB5FEDULL, 0x4D7B20874D880A3EULL, 0xE56E8EFE4B71BD79ULL, 
            0x479EEA03337FC1EDULL, 0x5AA2352F1BACB2D9ULL, 0xA7B2915C6956D8DEULL, 0xA87044E5BECF40E1ULL
        },
        {
            0xD3FA59C1424C066DULL, 0x2BC88168B3FFD847ULL, 0x95D718F43D52EE6EULL, 0xE4A2ECB330772218ULL, 
            0xEBDAFFA58810AE5EULL, 0xFC4B686E15BA02A8ULL, 0xEFC421C9358D13E5ULL, 0x78503EE8A0CAB0BDULL, 
            0xEC370ADB0A887B75ULL, 0xB2E85A35073CAA41ULL, 0x5AA87E927FE7555EULL, 0x337B71B116DF5995ULL, 
            0x0CF78D2F11EE1560ULL, 0x1DE0C3818C65A9CFULL, 0x2E1397C3BDB9CCBDULL, 0x616BF0B18CCF2A28ULL, 
            0xF5808B734D76D618ULL, 0x889B9218D39F4F84ULL, 0xFD2237368F4D97F6ULL, 0x3344CB580A6F68C3ULL, 
            0x22ECC6CA5AB866CEULL, 0x039710881FB0A530ULL, 0x3FDDAA1A4FD56B1BULL, 0x95005C8211271588ULL, 
            0x0EE9EC18C0B94901ULL, 0x6E15851BAEF32A29ULL, 0x6277131F645C5EA5ULL, 0x32C25FF984A5A3E1ULL, 
            0xF00097BE13276124ULL, 0x7C3B534D9FB37959ULL, 0x7DB3AC55C0DD537DULL, 0xC6FF062C4748F2D3ULL
        },
        {
            0x3A7E71E3FC0655E3ULL, 0x7B73EDF39834E27DULL, 0x2FA2AE52880F8042ULL, 0x31C5CF5C48E157F9ULL, 
            0xA2F7AD11FE32BD46ULL, 0x4929DD1030FE9875ULL, 0x15124921049994B8ULL, 0x2A626CC01A3DF82FULL, 
            0x44DAD1557B5D3183ULL, 0x964F201E126E3D28ULL, 0xB45950168B58A29BULL, 0xEFECFBE8B33B718CULL, 
            0x61C5302CF9101C60ULL, 0x308C3EF955FD1E71ULL, 0x6E3A6888578B4F21ULL, 0xD10CE189DD9AA9D4ULL, 
            0x21A065807792EF19ULL, 0xB95FA84BF6AE43BDULL, 0xFE2158C6121025CEULL, 0x9DBAA6B5CE7DA66AULL, 
            0xA515BA16B5815B6DULL, 0x338A04740111911DULL, 0x83ED32F55104A7ABULL, 0xCB84ABFC2D10C0CFULL, 
            0x18A24412F7FF2F69ULL, 0x49BCE4107DC555B1ULL, 0x317A6DAEA0001361ULL, 0x080B2FE425A7B611ULL, 
            0xDF30A7AD76125D50ULL, 0x1B4BA5FDEB2E7FFEULL, 0xB28B4F5232B5EF9CULL, 0x6031D7F18FB6C5C0ULL
        },
        {
            0xC62EDFA011212EA1ULL, 0xF9C82515926CCCE2ULL, 0x9B1C738C04989FE9ULL, 0x2C6338137DCA4A6CULL, 
            0xF98DC5096104E4F0ULL, 0x3F4E41210862B391ULL, 0x5595600E081EDD80ULL, 0x317A061127FA3029ULL, 
            0x2EA0C2F6BE1D8CFCULL, 0x2FB4CC172AB9B028ULL, 0x2DB63186D868932EULL, 0xD1207DB8113520D7ULL, 
            0xA937FDE006FF96E6ULL, 0x2DB07F56934831A6ULL, 0xEC45C01A01883AC7ULL, 0x75849713AE56BDAAULL, 
            0x02F64EA49BF76586ULL, 0x44229B588AB336A0ULL, 0xDCC76C15DBAD9968ULL, 0x8328E87409708CFBULL, 
            0x7BC011212647F670ULL, 0x60720554D4AD0C8CULL, 0x6C278558865781E7ULL, 0x1199320048374212ULL, 
            0xE6B45A86A6814FFDULL, 0xD632EC035E5EB4DCULL, 0x58C7B039E5E737CFULL, 0x0299841946F238AFULL, 
            0x3458080BEA93105AULL, 0xC8BFF876F93B91F9ULL, 0xF2068741D3B84210ULL, 0x9920B282B2BC46CAULL
        }
    },
    {
        {
            0x93855D72805E06D6ULL, 0x16677B712A59240AULL, 0xE68794563D861D5BULL, 0x78CB9EA7AA5C177AULL, 
            0x0C9659ACE09D4290ULL, 0xEC3BA15B314BA518ULL, 0x324C1F1FA2D16185ULL, 0x80E62810348382DFULL, 
            0x833FC36EAC3BED90ULL, 0x22E05227866BB8A0ULL, 0xC81F9929EC68A35EULL, 0x3E81EFFB33D43A5FULL, 
            0x04EA38DC6BB3C4E6ULL, 0x7E3EF2434CC75FFDULL, 0x364B03171C29312AULL, 0xE852E64023CFA353ULL, 
            0x90FBDD2F7178CCCFULL, 0x5F6C0FEA248E9E4FULL, 0xEBE615EE6EAAEBA8ULL, 0x83759737914B2A4FULL, 
            0x8B4822F3F84BF704ULL, 0xB0CE6B4363AF6DA4ULL, 0xAC7D2E854BE605A0ULL, 0x78F2AA853FA13F59ULL, 
            0x95B4C8B166B91907ULL, 0x31780BBBE7DF7176ULL, 0xA3745831A5953CFBULL, 0x0F11E36A3A812DD3ULL, 
            0x131FBD37E7FEC131ULL, 0xFA612E8DEF4222E8ULL, 0x2BD0133A6F432F06ULL, 0xF16973A44E65727AULL
        },
        {
            0xDC81B88BE6415388ULL, 0x14C7D4214ABCE6C7ULL, 0x8A038EBBE1C75CA4ULL, 0xD4E4E7C7788DC1E3ULL, 
            0x0010594D3227495AULL, 0xFF7BA47D746B47D8ULL, 0xED9F385CBB96A9D2ULL, 0xA95244491D55D171ULL, 
            0x5AA2CD025419E16BULL, 0x8B020FF05DADAE05ULL, 0xF990B14B5125BB28ULL, 0x93F6493007271385ULL, 
            0xDF683EE91296057FULL, 0x1DEB4FD47412B8B6ULL, 0x2C655B62236BE435ULL, 0x05D2EBDB948EFAFAULL, 
            0x568CFD886B7D30A8ULL, 0xF2C0712579771DBBULL, 0xBA3426B46F813FAAULL, 0xA47439020DC244F4ULL, 
            0xB743B231367CABBBULL, 0x7D116CE728F0CB5AULL, 0x524A59019AF6379DULL, 0xD3FB5204F4FD8F80ULL, 
            0x401051610FF5C123ULL, 0xCC52CC28F55D0343ULL, 0xA3F87E72E8008EE3ULL, 0xC7F3EBFF2F37567FULL, 
            0x995F11F0785827AAULL, 0x9931415C8CDEAF13ULL, 0x219EFD2FD818A76BULL, 0xB989EFD45CD401A3ULL
        },
        {
            0xE68C7EF1BD8610F5ULL, 0x933F9783F75110B8ULL, 0xE73F151EA2D59E0FULL, 0xBA521F2FAB1E903FULL, 
            0xB2113242674BBC66ULL, 0x02234323F3CE662AULL, 0x7465778DCA0D7CB9ULL, 0x58BE1C768C033E2EULL, 
            0x4D8187AFBD9E3BCFULL, 0x61F35B87C7163DE2ULL, 0x7CCD3CC5509FC318ULL, 0x3E8CE2FC9DEEDAC2ULL, 
            0x18CA9EBD18265D91ULL, 0x1B2C6CDF22C0A302ULL, 0x55EABDE228F7C8AFULL, 0x4669FCCFAB42FA65ULL, 
            0x2CDC52CF49EA1E76ULL, 0xC88B9F651BFCAB5BULL, 0x7A983D79F6BE56BDULL, 0x953D7C96A377FCDCULL, 
            0x4ADBBB5CCFAEB91BULL, 0x19FA36D7AD711C2BULL, 0x2F2CD1A969E1DA45ULL, 0xA63A2277DA33F763ULL, 
            0x3430118BEA8E3F7DULL, 0x592B521F0354712BULL, 0x3F9B4658DE102CC4ULL, 0x3BC689E50D00B683ULL, 
            0x64A545CA3931A2C8ULL, 0xBF9D0E842199DB96ULL, 0x4AEE3222C850CFC3ULL, 0x1370B785227F630FULL
        },
        {
            0xD21760D00C9B62B4ULL, 0xD8EFDEEC9AA3673DULL, 0x7CEBC54926630898ULL, 0xBF63738F1584E3DCULL, 
            0x3F0CEA9674A0D8F7ULL, 0x795E0ED1A73373FCULL, 0x2A16A91289370FF5ULL, 0xDAA3D2BB9BEFED24ULL, 
            0xCE34BB327897580DULL, 0x91F4F8C697AA2FA3ULL, 0x918432332A1AD32AULL, 0x69699ACBD2D8F1F9ULL, 
            0xD198E47885974F5FULL, 0x4FD4F9E063EEF9C3ULL, 0xE873292A7A0A2C36ULL, 0xDFD2E484238A80BDULL, 
            0x4DE86CA37B48C052ULL, 0x8239DD252FC8238AULL, 0x08FC839031648EF7ULL, 0xDC3E83D7A68EE32FULL, 
            0x974D17020B757B89ULL, 0xD43ABC0273AEEC62ULL, 0xF87B905FB2844B3BULL, 0xF4360468CB66138EULL, 
            0x6235C9113994909CULL, 0xA4DB7FF154EB564EULL, 0xA0D7B8234171F331ULL, 0x6452BA0422C72C49ULL, 
            0xE4B0E239273B95FFULL, 0x66C4A3F13A080F11ULL, 0xA2E7024A827AF923ULL, 0x9E5AD133FF93BB02ULL
        },
        {
            0x289D510E7945B4BBULL, 0xD1C2AEB8BC38124EULL, 0x4EC21A138963F227ULL, 0x7D883A2824A8DFC3ULL, 
            0x4ED73FCD940EB34FULL, 0x991AB5DF2FB78B4CULL, 0x738DEF7C8DF998CCULL, 0x6522459A58B31BB7ULL, 
            0x180524F7180087CEULL, 0xB63D2507CE33C872ULL, 0x6C3DCA7E70BADE21ULL, 0xB551CB825A88E967ULL, 
            0x835E5188F5994746ULL, 0xE27CF15E22960034ULL, 0x832335F0EB842C3DULL, 0x191B07CA464CEB49ULL, 
            0x9AA05911C6A1FC71ULL, 0xD25E8F352DA55F8CULL, 0x4F1F302EECCA2657ULL, 0xA91BA80CE3F65443ULL, 
            0x5168E7E7A6D61B21ULL, 0xF0067B7915717963ULL, 0x74459BF99940E7CEULL, 0xC061A318B3539385ULL, 
            0x19DF524616CE1041ULL, 0x574337C6195B6ECCULL, 0x2C7A42C09956D832ULL, 0x02B3D744206A3125ULL, 
            0x632DC18152B355B0ULL, 0x6AB764A90E43C9E8ULL, 0x31569348C2F172A7ULL, 0x05B4EE9D91E5509DULL
        },
        {
            0xBB52D4FE913C8372ULL, 0x46B95C0F87C80C97ULL, 0x21A9CF1AF08BB342ULL, 0xFAD873EDD5C0FD1BULL, 
            0x50A13D254F12EF12ULL, 0xFF80779F35F5CE00ULL, 0x23CA3E6A236F82BDULL, 0x217FC96AAC2D4B89ULL, 
            0x02146434502CA6CBULL, 0x52F652DB52064F4BULL, 0xFB7BE22A6FB50F9CULL, 0x8FDC7D3025CE0D2EULL, 
            0xDBBC7B7319D009BAULL, 0x9D40FFF825A38028ULL, 0xCC4EEB491AEB4F80ULL, 0x299E6055A75C7873ULL, 
            0x738FB4BF30EC660DULL, 0xA2A237EF17AC3652ULL, 0x93EE8269BB203DC6ULL, 0x60BD32B1B5B47D97ULL, 
            0xE57338CD4DB60E44ULL, 0xDB2E5E96AB282532ULL, 0x5AC3CB140C5C1178ULL, 0xE9EE131702CBE97BULL, 
            0x66EF56BCD2AAE6ABULL, 0xB1AD3CF3A2289A19ULL, 0xD3BE5ED5C0C4B360ULL, 0xCB5795FDA4B50A4DULL, 
            0xABE6DA49496F45EAULL, 0x3DC4EA77023AA62AULL, 0x8DD86473552B58DBULL, 0xBA1A483447D80A62ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseFConstants = {
    0xE9DAFA8CAFC04B9FULL,
    0x0F922E8A88D97B6EULL,
    0x08DEC87DF24490C4ULL,
    0xE9DAFA8CAFC04B9FULL,
    0x0F922E8A88D97B6EULL,
    0x08DEC87DF24490C4ULL,
    0xB0FA330D53D114EAULL,
    0x126B1BAE5B42AF17ULL,
    0x5A,
    0x56,
    0x17,
    0xDC,
    0xF5,
    0xD8,
    0x2A,
    0x5C
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseGSalts = {
    {
        {
            0x8B126ADDE271F211ULL, 0x7473F09C56CD98DCULL, 0x460A8FC66084E42BULL, 0x201FECBC8885B9ECULL, 
            0xF0509E3F31EE27A2ULL, 0x4CD6934D925C9E1EULL, 0x0D64FACDAC90F20EULL, 0x69450BCB5DF10D86ULL, 
            0x13B4D1232634DA91ULL, 0xF6E0847F7F93B149ULL, 0xA3DD4583DC4261B2ULL, 0xC75CDABB4EA785A5ULL, 
            0xFF867252D0F763C2ULL, 0x9A024ED518A4D259ULL, 0x973F89973B0D2BB0ULL, 0x2DB6416CDD2D4AADULL, 
            0x2BC96D4ABFDEC142ULL, 0x74F878C4611C9A83ULL, 0x1F9D56B1570EE4E2ULL, 0xCA320A40CDA8435EULL, 
            0x57378BECD4F15CC7ULL, 0xE98651EC79E8BC4CULL, 0xC9417016DD04874EULL, 0x20713AC49EA6B57EULL, 
            0x8802E424680F22EEULL, 0x4204642CF0E422A9ULL, 0x4E08623BE6A2BCEDULL, 0xDEC9BA2456373A9AULL, 
            0xE3ADAF8E3EE6417EULL, 0x364EEBB6C749C782ULL, 0x1A8550BDD3D48B3EULL, 0xC93EEC002BBF27BCULL
        },
        {
            0xA54F70295766C835ULL, 0xF2178BB55282885DULL, 0xBB4CB937F5459C59ULL, 0x2C142CA5B79E0EEDULL, 
            0x32548EA28EE39495ULL, 0x66905CBC2B75CB03ULL, 0x4F7DE169D6B0E916ULL, 0x83B2CF580EFC604AULL, 
            0xD72B54FAA73AD00DULL, 0xF2DB9DBA741AA353ULL, 0xF281443B01A1F5D5ULL, 0x5FD4BF63694E7696ULL, 
            0x762CC0418966969AULL, 0xA1234829DFDB7BF0ULL, 0xCA729D5BB4147D76ULL, 0x31AD476FC31E5042ULL, 
            0x7BAA2EE7FB6C9FE8ULL, 0xF5260B1AD3CB3F7BULL, 0x0DF94599B1C57DE8ULL, 0x68FD75D61BE96B75ULL, 
            0x1777E476A9630788ULL, 0xD54D7AE03ED2A9BFULL, 0xF1FB0912C73D05F5ULL, 0xCF4CC1D0D4A5DE32ULL, 
            0xC7C3984A7FE5C9CCULL, 0xC75274A020DD2478ULL, 0x096900B7BA830829ULL, 0x63D2E7995A2E5322ULL, 
            0x3F210D8374B86FB9ULL, 0xC5D4871EF365268BULL, 0x454323DE796CE277ULL, 0x091C136D9D5D7007ULL
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
            0x76966F602125D36DULL, 0xFB3AF79054A6D7F6ULL, 0x25A58B55D54E96AEULL, 0xC7272FC5DD8E2FD9ULL, 
            0x1BB8A73B41DD40E1ULL, 0xF2F496C5754731B2ULL, 0x7DDB82A9196E684FULL, 0xEB553E901E324ECAULL, 
            0xC80E7283547BA752ULL, 0x70994D714A385712ULL, 0x19C8509523D4DFD2ULL, 0x2DE78DABC39102F3ULL, 
            0xFC1F4A60521DA076ULL, 0x2A1CF691C62275ADULL, 0x6869532B9C0757E1ULL, 0x3658CB5124314435ULL, 
            0xFD5B8438D80B2970ULL, 0x87498A5170692CC1ULL, 0x273FFF1354334002ULL, 0xE1FDC02ECA13D8CBULL, 
            0x04D5AD87F1B1160EULL, 0xAB85593613D96580ULL, 0xF5F332202FBD2CD5ULL, 0x1A9A9279EDCBE813ULL, 
            0x727786DE62649C9CULL, 0x93D5F13F6E8A7CC5ULL, 0xA880953DDACC1325ULL, 0x7F06BEDC7A907555ULL, 
            0x7D197A7FA074A6FEULL, 0x4D415E9061332494ULL, 0x0BE5398A97785D12ULL, 0x77346D0E792A3BB9ULL
        },
        {
            0x95F22DA7AE577AFAULL, 0x08319631B716FAB6ULL, 0x8AA38F666E5B0852ULL, 0xB5D6D31FF68F7CCCULL, 
            0xFF0696DA3DD2A8E6ULL, 0x8F31654015D3308BULL, 0xC5C72832FE8DC747ULL, 0x28412EB639C683FFULL, 
            0xB6F70EB630C0B20CULL, 0x6F238BD0D3EFA0D8ULL, 0x38154B8672D77F1BULL, 0xA69FF00277CD24A6ULL, 
            0x48D3D0F766E1207FULL, 0x6F6F292F5CFD395BULL, 0x38A70E88068C0A4AULL, 0x27A4A33E291B1F3CULL, 
            0xEA6D50548A56B9D7ULL, 0xAF1BE6CEBF761298ULL, 0x7E1F63E7CE2398C5ULL, 0x740FA547758C862AULL, 
            0x4CF74C5EA9B45EFDULL, 0x5D7643F0FFBD6AC8ULL, 0xD0B3FE969FE1CB42ULL, 0xD1F83D9215F526AAULL, 
            0x80001D1724E31E98ULL, 0xF27535831AAB04F6ULL, 0xC14BA2E029B9E173ULL, 0xCC1839498BD565F0ULL, 
            0x777ECA91112D6D67ULL, 0xA48ABEBDE6BF0479ULL, 0xA69DE0996C84521BULL, 0x21AF2CAFA22980ABULL
        },
        {
            0x2B504B76053A5194ULL, 0x5D360205DBB5766CULL, 0xE8291D8F60A40AB4ULL, 0xC08187F8450914EBULL, 
            0xDF905B86F22A223BULL, 0x915D102A78C25596ULL, 0x975E454BBA3F5F66ULL, 0x9675E1CCEA1D3BC0ULL, 
            0xE164A5D3ED14D750ULL, 0x811C8C6D0CF4B10AULL, 0x8AA7BF0003EA4D9BULL, 0x9403CF1A13F699F1ULL, 
            0x6A7B2B8F61D36C5BULL, 0x58F54003C1092EACULL, 0x7F4220C36BB51255ULL, 0x5B8B4DD80F0B90AAULL, 
            0x9799A55D18CB05B2ULL, 0x7AF4F23AD3A6AD9AULL, 0x7B08F222F855E2D3ULL, 0x667775AB2CFDE572ULL, 
            0x71AB278E1A8E3588ULL, 0xE0FAFCFE0C4113E5ULL, 0x14CC85D6164F1B05ULL, 0xD020F4C7776C7443ULL, 
            0x2830DAD2C4501F23ULL, 0x92956B972A709000ULL, 0x57BA083C27D596F5ULL, 0xE5A21FC8F7CADD7AULL, 
            0x3AD50B895C0B226BULL, 0xD7FA80101C70129AULL, 0xB328CB67E64E41EEULL, 0x6AE9F5C4BF9D1242ULL
        }
    },
    {
        {
            0x317B5DDB1776FEF7ULL, 0x7EF990D33CDCB4D1ULL, 0xDB767623726E392BULL, 0xCEF2A3A9CDBC6DD8ULL, 
            0x3720B1FE2028298AULL, 0xA4B1AE0A6EB379A3ULL, 0xC2DD6EBE906189BBULL, 0x9B6EA8F5C848994DULL, 
            0xE000C79F6A200C6EULL, 0x9CE399602D93BE15ULL, 0x645B85EE73F34702ULL, 0x6D5EE882DEC10A40ULL, 
            0x96C835246B73063CULL, 0xCA770359BB44570CULL, 0xCE4CC8D101BB2ABAULL, 0x26E24B3EE81FF899ULL, 
            0x9580C0A50D4AEB45ULL, 0x6DEEAC0205F5C28DULL, 0xEB7A36138DF4B208ULL, 0x82FBDFECB96FC157ULL, 
            0x90E34AC90754B65FULL, 0xEA20C3ECB7AB721AULL, 0x70DE7B024FAD2B4AULL, 0xCA3059385E9C355FULL, 
            0x5BA86BABB544DEDEULL, 0x86B88647C7296AD4ULL, 0x57018D7AE15FDCBAULL, 0x68673C2E79AA448BULL, 
            0xD058835E093059F2ULL, 0x7C4E1F8758458C57ULL, 0x785B88E255C209B9ULL, 0xD832E1F0F504C3DDULL
        },
        {
            0xD00A529CB35A2887ULL, 0xA168B7A97478F4C2ULL, 0xB662C252E39B732BULL, 0x7388DA15EFE26878ULL, 
            0x091B8A4FCC8361CFULL, 0x6922F9A3F76D2A1DULL, 0x412D64079D8E1CE9ULL, 0xB3FF92D922BAF2B9ULL, 
            0xD3A8EB88FDE56FF6ULL, 0xA5A01B375A58324BULL, 0xCF34B411F2281F7CULL, 0x1A5637CD6E8262CFULL, 
            0x40BFCCB3EE52CA1DULL, 0x34D83ECE19473EC9ULL, 0xFC143564D8C123A9ULL, 0x942AF3C591B581D4ULL, 
            0xE38568DDD983666EULL, 0xDF8648265B8E936BULL, 0xA1DCB698051C336BULL, 0x056C5D2FCE5DBCB2ULL, 
            0xA927DB9147FB072FULL, 0x8F78D320A4420B21ULL, 0x375814BD7EFCBE3BULL, 0xA8447F14D588EDD7ULL, 
            0x23D9826EEE4C872CULL, 0xFA4EB2F59DB61AACULL, 0xE3A42402924E0235ULL, 0x7244BF33D287B820ULL, 
            0x121CEA0E138FD3C6ULL, 0x8DE7D39AD3E40B29ULL, 0xF12EF49BA7AE311FULL, 0xDE7702D1520FCA2EULL
        },
        {
            0x5E6E01E2078C16BEULL, 0xF82363ED42758AFCULL, 0x6413410A7A762ABBULL, 0xA4C4B39686537C90ULL, 
            0x843A0DF1696C8BA9ULL, 0x553F9477D2EF1E97ULL, 0x594C2D5A8E11F74BULL, 0xB776E53585991A5CULL, 
            0x2F62B2791220DB71ULL, 0x923DC38CCED1D526ULL, 0x5E9648EAC59FBA30ULL, 0x12BA72D4FB5DDACCULL, 
            0xD36BB7581DD99B53ULL, 0xECCD78071DB51E39ULL, 0x81DE967A68CB7B00ULL, 0x88C1D4D1A3A7366AULL, 
            0xF6EC8AC01544CDBEULL, 0x2416B0DA9B03BE3CULL, 0xD13A6AD06CE18E03ULL, 0xDB5985B40B01A41CULL, 
            0x21A9977D653160C8ULL, 0xC9E21E9231B3B405ULL, 0xC45D69B888F1E085ULL, 0x3CD1DEA5CE7584DAULL, 
            0x2BD1F9D37399A96BULL, 0xA768D56C085264DDULL, 0x70AA53A0FE5F6DC5ULL, 0xE17B1266CCD4AA45ULL, 
            0xF18801FE81794BC1ULL, 0xB4597BFCC629279EULL, 0x9CDA9695275C807EULL, 0xAC941E6A8B590958ULL
        },
        {
            0xF265F8064EA68D1EULL, 0xE0B3F431B3FFF969ULL, 0xF9139513024DB5FBULL, 0x7E56469DD524E023ULL, 
            0x0A6005CC73E74D55ULL, 0xA279580C4D3C057DULL, 0xDAADC12EF0F186F4ULL, 0xC8DF6DB0A7A95387ULL, 
            0xD61447A1458152B5ULL, 0xD7CFFC7A24B2AF6DULL, 0x0F0387CE6A570227ULL, 0x510C691E89B7ADA7ULL, 
            0xE53D288DE5DF08E3ULL, 0xB05CED29867F68CCULL, 0x8FDC68026211B1DBULL, 0x67C60888FEF5834CULL, 
            0x4F743FF3F6A1F774ULL, 0xF2C546CF4BC109F6ULL, 0x6BFE0CFB26C38920ULL, 0xD229D235AB94EB5BULL, 
            0xF1E64988236EFFCEULL, 0x2569930DA3FBC68CULL, 0xD3C37A6C3A0366FEULL, 0xC826CA7ABC408C78ULL, 
            0xA30C47C14C4B452EULL, 0x65E78667ED798FC1ULL, 0xE88AE3CB73C87FE8ULL, 0xDE19C2126B241211ULL, 
            0x6B16264920F0AD05ULL, 0xE4547C2E901FB32FULL, 0x621AB8420DE2F3E5ULL, 0x929F2E272978F943ULL
        },
        {
            0xA779F0705C8F47FDULL, 0xFB8BC569C11AF8D7ULL, 0xEE07CCE029985D1FULL, 0x7DE73D4994BE88FDULL, 
            0x468099984290F6B9ULL, 0xE843C32781112D6EULL, 0x4B85565605C598FAULL, 0x43FFE44B73A25CDBULL, 
            0x5E7CCBCC4582158CULL, 0x2F4F3A5C19C7EFD1ULL, 0x772084E7354323F5ULL, 0x621C66ACBF7FF016ULL, 
            0x670419F0D9DE1EE1ULL, 0x8380834654F7DA42ULL, 0x062CD1260DDB7D14ULL, 0x5A8A8A2CD5C60B25ULL, 
            0x1583B7C42FD111DDULL, 0xB8DA5077A7A10E83ULL, 0xD404C7E5FD1AC17AULL, 0x35EFF1B03D96FEABULL, 
            0xF3FDE5B1BBD529DAULL, 0xBCE411775BA2BCC3ULL, 0x2F4E908160247ADCULL, 0x913CBA56E5212C30ULL, 
            0x6A4ECEFC079E9883ULL, 0x8690ADD6CAE3012CULL, 0x0E8840824C14DB5EULL, 0xE12BA4CDDB5E3973ULL, 
            0x1FA4B01AE3A9027FULL, 0x518EBB3BB990E63EULL, 0x11CF27419650798DULL, 0x2076A651F78432E4ULL
        },
        {
            0x9FD391A0E2D9E555ULL, 0x1025694F982A642CULL, 0xA2AC9A1E9AC50656ULL, 0x00337D3B072EAC5CULL, 
            0x8BBFAB05159740B3ULL, 0xAC3064035FCC71B6ULL, 0x83A54166358A6A61ULL, 0x76BC00BDBF2E6FEDULL, 
            0x828D9526FDFA219EULL, 0x49792AA4859F4371ULL, 0x5630B5044CBB793DULL, 0x5619763177038C24ULL, 
            0x3DC8409137B381A3ULL, 0x07071EF023BD0D19ULL, 0x76CF504F29579A10ULL, 0xBB1A7CB892F2D0A8ULL, 
            0x4BAB23A97CD78683ULL, 0x6C9BEFF2620D891AULL, 0x2DE457C3FBA2E4A0ULL, 0xA83D7592DFA82E8BULL, 
            0xDCAE93B8D4DB5E3EULL, 0x2F404B357EC76A01ULL, 0xD32744187934D859ULL, 0x5E1357BB2F5291DBULL, 
            0xC7240D01C6E7F138ULL, 0x977CA987807D8A64ULL, 0x6EAC5078489966F2ULL, 0xE4FE5E05A8B19D8FULL, 
            0xD0E288FB3BD670FFULL, 0x996E35C23579C5C9ULL, 0x369D38C9D43B08C1ULL, 0x1045BB569E985631ULL
        }
    },
    {
        {
            0xB8CD4F9F5AD70249ULL, 0x14C74A44D70EBF8CULL, 0xF6A6E1D6FA95D042ULL, 0x4EA0CCE3B84ED729ULL, 
            0x43E29548599E2507ULL, 0x073DF918A51B03D1ULL, 0x165C8B58667BBADAULL, 0x720F815D63FFE1A3ULL, 
            0x99398CA7ADA37089ULL, 0x582E865482BF8086ULL, 0x3CB0EA85372DD3C5ULL, 0x5668C9A81244E5EAULL, 
            0xA7B234A1C867964AULL, 0xEF0AB562DB0F1B16ULL, 0x22451926F8FA76D9ULL, 0x086C746628DD5BD5ULL, 
            0x492773951FF4CBEBULL, 0xC5C3472E1F1154B8ULL, 0xD774CD09FFEC4E80ULL, 0xCBE2A7D4A3F1B4DDULL, 
            0x9ABF268DCA048A06ULL, 0xB35DE6C4A9616C21ULL, 0xAB7A88FA8DBB3C3FULL, 0x36AF3D727688828BULL, 
            0x8F3A1EB2F09D04A1ULL, 0x5BDAF94BBCE621E6ULL, 0xC5B3776F07B7DE3BULL, 0xC9A2AD22709CF5B8ULL, 
            0x6A109431BD318C50ULL, 0x3DA162C49D82352AULL, 0xDA3030833ACE58C0ULL, 0xEEA35B0A82664FA4ULL
        },
        {
            0x6E1EE452920DDDC4ULL, 0x72288A2A7BAD6EE7ULL, 0xAB12A2211D9378DFULL, 0x0710847F3341677CULL, 
            0xCEF7FEB470E1F503ULL, 0x1AD192E3704EE1D4ULL, 0xA67F7075629A2C49ULL, 0xF1844576B97BF541ULL, 
            0x471A9433A9F17CB1ULL, 0x7E783665ACAF5FB8ULL, 0x91611901862DF17AULL, 0x093F275093967D10ULL, 
            0xE5211ED30B1278B6ULL, 0x59362FF8A309DBDDULL, 0xFEACF49B341EC90EULL, 0xD20A486C3EBE15E3ULL, 
            0xC1B675891CDDC66AULL, 0x6BCF16751425D93AULL, 0x925B292FBDA284F3ULL, 0x709A4ADAF3DF7CBFULL, 
            0xED4CD54C93709560ULL, 0x634A6B8092A73560ULL, 0x929EDC032D67CF32ULL, 0xEB04E54E480B511EULL, 
            0x3594D5EA6D86DB1EULL, 0xD96E2D09C7C87DCAULL, 0xEF43107FC69249D4ULL, 0x1DF6E9DC0D2600E3ULL, 
            0xF09EC47BF34CE063ULL, 0x9815C48590BCB61EULL, 0x13BB877BF16CE524ULL, 0xA45A07955D26471FULL
        },
        {
            0x91A7D9663503B097ULL, 0x1CEDC8DAEB536FF4ULL, 0xAE85F4A5F7FA81D5ULL, 0x0989720D5594F196ULL, 
            0x79291A9FF1B4C865ULL, 0x161FB9C9C5C73CFCULL, 0x7271D55409159E7CULL, 0x5F7930DA5CB6D37FULL, 
            0xB2054250F0F84B3DULL, 0xE81CDCA3FEED0BE8ULL, 0xFBD64BAAA710E05CULL, 0x3BE03D2A1FAE7E4EULL, 
            0x275605248ECF9F1CULL, 0xC2013BCE586F7F97ULL, 0xA02E3B4C9941A5AEULL, 0x589F5F2F08C1B38BULL, 
            0x6DB9BEE4AC74D359ULL, 0xFDA6361942B332D5ULL, 0x40E0F960FA350E9CULL, 0xB7947B902AD2DAF1ULL, 
            0x1D7D2FA4509CF882ULL, 0x016C56EA51212B9BULL, 0x82BBAB6243CA72C5ULL, 0x831235E6AAECC331ULL, 
            0x5C57532DFAC4A901ULL, 0x223E3794E23A9911ULL, 0xA8E7698EC2E5E185ULL, 0x3B9841F20611C290ULL, 
            0x1BA4BBD59BBF29F7ULL, 0xCD38D7BE14406647ULL, 0xDE8AD4C674A051A2ULL, 0x883F72C67E99B7BDULL
        },
        {
            0x0B97D283AA907BDBULL, 0xCDC8D1DB61CEDA58ULL, 0x9FA79A540AEAE80CULL, 0xCEF416229AD980CBULL, 
            0x2A7CF20FA44C377AULL, 0x83BCE5928B7D5B23ULL, 0xB669080B3442E002ULL, 0x20882CAB6C224FF4ULL, 
            0x33B0C07681EFFED0ULL, 0x19F5C64F5EC2C3D8ULL, 0x1ABEC0C074037B37ULL, 0xD5D3825EBA16225AULL, 
            0xFCED44FFCE55C812ULL, 0x303E6AC8D56E6EE9ULL, 0x214B46665F80E048ULL, 0xB347DB6A139C512EULL, 
            0x038637A0EA194817ULL, 0xBB40533214E0522FULL, 0x4C8D583A452B4F1DULL, 0x70238538058794DFULL, 
            0xE3A87D460EBE43B7ULL, 0x771B7272C511FD69ULL, 0x04D979B1D94E0432ULL, 0xE7B1CF0166D0BD4BULL, 
            0x9344BFCAFAB56826ULL, 0x8634F8084A3C5A1FULL, 0xD18FF3C57F985574ULL, 0xB94DEA5797330E07ULL, 
            0xDEC90E0DC27B9B22ULL, 0xF3895888999CC60AULL, 0xD4ECEF0148FCD8EEULL, 0x7AAC98C3695D9620ULL
        },
        {
            0xB3DB81E2F7AAD3D2ULL, 0x5B244A932F70AE55ULL, 0x7D6AC22186278F8CULL, 0x76C06784F13B06ABULL, 
            0x7FA71B40DFB2321BULL, 0xEFEE4B265D19C121ULL, 0xF8211134C162E26DULL, 0x9FC3ADFD0779C9DAULL, 
            0x84C3784158FB9150ULL, 0x88B060702545E31AULL, 0x9136130F963CEFF0ULL, 0x6DE79731C4B60434ULL, 
            0x5DE169263B818247ULL, 0xCCFB47E25493011FULL, 0x08298056ECB94F25ULL, 0xBE32B6CD3CA9C49CULL, 
            0x8F4E14AE58C8E592ULL, 0x28191BC8CCC3182DULL, 0x34B00ACF2CFABDAEULL, 0x588F75E8416B0CFBULL, 
            0x29DCAB38D0368A02ULL, 0x3D920E502BD2FE8BULL, 0x78B08E77C8A21E72ULL, 0xC5FDC9EB22096466ULL, 
            0x19ECBF6F96A7DF9EULL, 0xA51A3F80D8F7E158ULL, 0x534ED886617D5318ULL, 0x7C09AAD8917B042BULL, 
            0xF08630DE60A4002AULL, 0x15ED3D2AB41C6FD3ULL, 0x4DFCEB75E8C22515ULL, 0x7FBCA814DAADB9C4ULL
        },
        {
            0xEFA8B6664270AA4AULL, 0x6DD2BFB7D34E2B29ULL, 0xC0AD7B6D5307251AULL, 0x7B974B80FEA67658ULL, 
            0xC489807B5268EF7EULL, 0xB32A54DA494E4AEFULL, 0x7D4761FE5B47997EULL, 0x3A38A5383CC9BEC1ULL, 
            0x7CF0FDF64FE81C74ULL, 0x25F219B66FA772C9ULL, 0x9F522B60B0B8E365ULL, 0x4AFC02D4A31FDD2AULL, 
            0xFE4D80098388C9EEULL, 0xFD67EA31B3FA7E43ULL, 0x99395272321D3677ULL, 0x25072A3450191DF4ULL, 
            0xE497168FC7D63931ULL, 0x58EB8864F3D235FFULL, 0x294A075433BD7D43ULL, 0xD1862B7FB1B69440ULL, 
            0xD2988C96B7F33DD7ULL, 0x9BDA272A938D09FFULL, 0x767B26CE416BA172ULL, 0x217E1538E130110BULL, 
            0xB29813503D1F0B11ULL, 0xBCA447DB85B17AB7ULL, 0x713B77A486C6EFC0ULL, 0xD928868C6D938BCBULL, 
            0xD189EFDBB5B3F6EFULL, 0xEDEBA0C21990728FULL, 0xD172A903375E4CA0ULL, 0x7E25310CCDA9D8B0ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseGConstants = {
    0xBD9A1E2F16A00A55ULL,
    0x79C09EB48FFA0C21ULL,
    0xCCD3218330BADC71ULL,
    0xBD9A1E2F16A00A55ULL,
    0x79C09EB48FFA0C21ULL,
    0xCCD3218330BADC71ULL,
    0x07E0EE555F1EBAA4ULL,
    0x22083C46A1FEF29DULL,
    0x04,
    0x89,
    0xA7,
    0x76,
    0xF3,
    0xCA,
    0x43,
    0x7E
};

const TwistDomainSaltSet TwistExpander_Naos::kPhaseHSalts = {
    {
        {
            0x2607F2AAB9D0C2E3ULL, 0x6BD6EC4C8C21F1EBULL, 0xB6FC2799F1EF9ACBULL, 0x9A3224C08D39A9E2ULL, 
            0x1614D161D6BA4791ULL, 0x432E91811495FA4EULL, 0x1CDDE533FB316F00ULL, 0x316B00EC9CB8EFC3ULL, 
            0x305BB07A47B63DE4ULL, 0x16BD80A9D3C07AB1ULL, 0x7EFF147CCAEBBBCAULL, 0x5E649174D8484FF3ULL, 
            0x1385AB11102C14A8ULL, 0x9CB9FAD3B52C1E51ULL, 0xFD98A64AC8828FCDULL, 0x81C93C893F6700BAULL, 
            0x9235E4C4DEA44DA2ULL, 0x3849692D3B96C1C2ULL, 0xD052D98A8AEFE505ULL, 0x80E05A450E519714ULL, 
            0x241CEA60BD7CA6E1ULL, 0xC663C23C89178F6FULL, 0xDFBB96373D59399AULL, 0x20E59D94C227CB65ULL, 
            0x08F1E9A8C901491BULL, 0x05DC7C9276676895ULL, 0x6FDCF271E0A216E2ULL, 0x6762005D4E0C0835ULL, 
            0x052ED2B1590DF3C3ULL, 0xC41F003780F8DF89ULL, 0x7F26DEDB3998D2B0ULL, 0x5BAE0C4E7F5DCD92ULL
        },
        {
            0x9401AD20718F350AULL, 0xB6E08C42820AFF8FULL, 0x20E9F1F6B648D7E6ULL, 0x6B7EB7106318FF86ULL, 
            0x94A975028EAEB99CULL, 0x4EF2D0783495D077ULL, 0x05D7117B043A9FE1ULL, 0xD8D17C9128168E82ULL, 
            0xAE98855A3ABA5DA6ULL, 0xFEF7C813199D69FAULL, 0x9DF245633B0E31A3ULL, 0xF750672C13C7418EULL, 
            0x03613CFC60BEF40BULL, 0x11740860D5C17C2CULL, 0x3D5DCB9D2C627841ULL, 0x193A138219E7F9CEULL, 
            0x92EB145E5F357D0FULL, 0x72E01ADB4E41C5B0ULL, 0x5C688203D2B84FA3ULL, 0x4E664184D69366C6ULL, 
            0xBC5B5268A87FAC94ULL, 0x2606B9DCAE66FA57ULL, 0x918B1F53612ADEEDULL, 0xDF5FCBFDF2200A88ULL, 
            0x1C8B1C9C0091C7BBULL, 0x5DE4785E1641F6F7ULL, 0x606B186FBC0811CCULL, 0xDA08AAEF795A8ACAULL, 
            0x131E6BC1E92AF135ULL, 0xE21789C531616F30ULL, 0x5B3EA3EBF464F5B1ULL, 0xFE57C34DCEAA50A3ULL
        },
        {
            0x8C9AC19DE381852DULL, 0xD35B6B526269A7CEULL, 0x3165266BBD228625ULL, 0xA03DC85A5C4E4641ULL, 
            0x3AB4B7A44685C3CCULL, 0xE816F9F23234A41CULL, 0x5F02FDF545495D7FULL, 0x0C696E2EB42632F7ULL, 
            0xC130F2B2083F18C1ULL, 0xF4B5A27372948EF4ULL, 0x252C58E936CC57C8ULL, 0x14AE7E996584C5C3ULL, 
            0xC17BDE9769432E2AULL, 0x5C680860A9EB1617ULL, 0xDBA813F20378E2A6ULL, 0x1C75653A0F3E1038ULL, 
            0xA8D40B8DBC58E819ULL, 0x83079A49C42CE7FDULL, 0x834834B21E92225CULL, 0x4F29D14C8749C197ULL, 
            0x534F09F24240AC7AULL, 0xC0D69E3B2EB780E5ULL, 0x94DE12B99D1F5296ULL, 0x646D52F890A6B303ULL, 
            0xBD5CAB7A05C084EFULL, 0xD8F1BA97A38E0231ULL, 0x88337CEDECEDC1ECULL, 0xA3762A320FC9672DULL, 
            0xB360EC5DD09319EEULL, 0xDCCA32A1BD3D2E65ULL, 0x1AF7F2740577FF31ULL, 0xD5D7D7A99E914956ULL
        },
        {
            0xF929501B2FE42836ULL, 0x22AA4CAB3912A751ULL, 0x26ED1C4E671A5887ULL, 0xC742BA5BE3A24273ULL, 
            0x81A77494ACB6A1B5ULL, 0x6ED1256631C284ADULL, 0x6698EF4D651EDE00ULL, 0x3995F4F64F9EF96FULL, 
            0x62FA8BF2F9794B6DULL, 0xDC93EA4400DF5672ULL, 0xF43E5226C0CF2140ULL, 0xE5E7CAF324A46977ULL, 
            0x1F4428E2E1ABB030ULL, 0xB7A4C6C6952D59AEULL, 0x248CC494116B36F7ULL, 0xDD4DE2DC98BB274CULL, 
            0x17D065166E8E00BFULL, 0x3749C3C817AE030DULL, 0xAC5F7C239BE91FF2ULL, 0x49405FC2792F14A7ULL, 
            0x5BBEF3B64E727B87ULL, 0x837E4658BCCCE8A0ULL, 0x73076D0806F83E4EULL, 0xB14E914C11A762AEULL, 
            0xE3CF739954C8889CULL, 0x645B9EB9F3C37F80ULL, 0xC89BF366FB141F22ULL, 0x6B473761D5A0043FULL, 
            0xF1E37A7192984656ULL, 0xD0DC97F477AA0ADEULL, 0x0BD7C87237A1D54FULL, 0x05D9EDCEDE206684ULL
        },
        {
            0x0146196156F9D265ULL, 0x1A87AE28A79DECC7ULL, 0x695FC38155B26DB5ULL, 0xB9BFBB9F58564F4FULL, 
            0x367C024A1E9A857CULL, 0xFB83843FF442D68DULL, 0xAD22E4EF1AD326A1ULL, 0x76DFC1852513D81AULL, 
            0xD8BD2E8FBD90DCEEULL, 0x4444D7A8A73E3716ULL, 0x02A136707BBF46D8ULL, 0x1B5AB47C972681F8ULL, 
            0x354989F59424F800ULL, 0x9C9A4ABFFCA27790ULL, 0xDA1F255C6522D428ULL, 0x691B696E58FF7C90ULL, 
            0x452813ECF38521AFULL, 0x4BBC12A52A9B5EBFULL, 0x7ADEDEE692852D1BULL, 0xA4133DF47F21E0E0ULL, 
            0x705C7A8CFD21FD50ULL, 0x9D9580C83FF8EA67ULL, 0xE6EB10160CABEA0EULL, 0x61274D1C766D9E61ULL, 
            0x6E17021E2915CFCBULL, 0xC2C50687D4B4998AULL, 0x7DDBF824C5EF91E4ULL, 0xF32F323B475AE32DULL, 
            0x42232505CA5B89B2ULL, 0x7B8DAA91A8E9DE74ULL, 0xB47281D2801B11B9ULL, 0x0EF6282D2CDA5818ULL
        },
        {
            0xB56425536C9E7BB0ULL, 0x1112E53CFED6CA4AULL, 0x41DF1CB4D1FE9A80ULL, 0x0FDE1D24F232EA2DULL, 
            0x7C0C7273C4928262ULL, 0x97C9105A63C00029ULL, 0x4DA353D5121B2382ULL, 0x8951F3BD4C578E2FULL, 
            0x6A98A34C65CEE424ULL, 0xE82250D0FAE30010ULL, 0xBEE66F020140DA5AULL, 0x1E98F8B808C47A2DULL, 
            0x232D3F8A4A4D4A60ULL, 0xFABE6338FEE2F446ULL, 0x225FEBB75F15BBC6ULL, 0x4BECDECD9D5FCDA1ULL, 
            0x1CC41C90097691DBULL, 0x64361C29C1399254ULL, 0x400C8DDFAD3CA269ULL, 0x93B3E9BACA69FFA1ULL, 
            0x353D7B30D5287847ULL, 0x323D3C75797F3792ULL, 0x81C4805A4DFBE30CULL, 0xB1B9A127A112A968ULL, 
            0xDE6954A99A577600ULL, 0x8323921566AB3415ULL, 0x54AF747B75AB7AE2ULL, 0x5CD65DDBC6056989ULL, 
            0x38E3AF12D31B5E57ULL, 0xA0D5CAB9612E27F0ULL, 0x30A88C52CB8EEE4AULL, 0x3455BD0691AE0407ULL
        }
    },
    {
        {
            0xCC75F74FC53902B1ULL, 0xB0060A39429F916EULL, 0x641AFD26CF387286ULL, 0x02B27D92B6CA640FULL, 
            0x1351454284DA1695ULL, 0x5501B9ECBE30777DULL, 0xE2B197F79A0B861FULL, 0xB9ABFB6A5A744725ULL, 
            0x2816CEBDAFE08706ULL, 0x139FB0D005D66238ULL, 0xD483FD111C46BFA9ULL, 0x78513FF7468C6832ULL, 
            0x98F8417BC6AD2B6EULL, 0x37FDAAD1BFCC151EULL, 0x8012C57436C6405FULL, 0x3DE763D12B9F9D8BULL, 
            0x3DCBEED9FF412615ULL, 0x62D406B2A155BA1BULL, 0x39155B2D2672BCFFULL, 0xB73A9047B3467D4FULL, 
            0xFB3CE4105EEFCE2CULL, 0xA0A3A5224037A531ULL, 0x4B7AA613B1C675AAULL, 0xA367E38BAE686A3FULL, 
            0x4AAF2E34D0759E0CULL, 0xBBCE1E221C40450BULL, 0x004A7EDA9D1E0E43ULL, 0x8D1C999B5160B6C7ULL, 
            0xF67327604D0AA964ULL, 0x86C99594315DA038ULL, 0x6D670A4D98502730ULL, 0xD318B52521D7F0E7ULL
        },
        {
            0xD2D673833431F58CULL, 0x1157237106F2B813ULL, 0xE812CADCF4E3FEF2ULL, 0x9321B52B772CCDDEULL, 
            0xBC2629D5F55C3DC0ULL, 0xB9065544DE319C26ULL, 0x6733DE3E40C7F788ULL, 0x03C4D3B9341EF4B6ULL, 
            0x545B8F99F0D160A9ULL, 0x97ED7F17EB0DBFAEULL, 0xF8365E73CF7932F3ULL, 0x3C9E63F885F92F8DULL, 
            0xF5E3F695E7A46AD1ULL, 0xF9524B5053C15ACAULL, 0x19D1DB3802395572ULL, 0x7300E1DB64082FF6ULL, 
            0x7442FC5188BBC5C8ULL, 0x39AA6DA95319DA66ULL, 0xEAD6DD03503D4820ULL, 0x8053EDD3BE04E6A8ULL, 
            0x5C9804AAFF69D774ULL, 0xD80ACA3138577A59ULL, 0xE1653C30834F4D95ULL, 0xAAD707D912877DCEULL, 
            0xF9A7449691B5BBC2ULL, 0x46A27036F6425417ULL, 0x80F5C56BC6AC2226ULL, 0x2317BDA9D7201AC5ULL, 
            0xC3146BD3FFAE03D7ULL, 0xA5AAA27AB355DC5EULL, 0x8A8A32C3FA376700ULL, 0x743FFACD7815712FULL
        },
        {
            0x53F834BC7EFBFBA6ULL, 0x83828A74D8188102ULL, 0x173BE58DC7D84E87ULL, 0xF0C9B856BAD2BABAULL, 
            0x99CB5A1FB8A74728ULL, 0xC9C325E7D2F22D44ULL, 0xD8004C835C826AA6ULL, 0x31AD650D5A0C2D10ULL, 
            0xCE868E8D7FACC2CCULL, 0x2E3E0AC7528DF476ULL, 0x8C09389007300F9AULL, 0x42A521A879C35A51ULL, 
            0x65EC50D567220CAEULL, 0xA0745B2B9AE5650DULL, 0x7BF83C16F5FF115CULL, 0x8342834B9EBDDA11ULL, 
            0xE38C70416B5185F3ULL, 0x329E1AE07C3E4735ULL, 0x14E226574373D225ULL, 0x039886A43BD787DBULL, 
            0x61BD146A425CC5A2ULL, 0x094F878E321AD5BBULL, 0xD70EB51BDA2C9403ULL, 0x4E11E915CA02FE96ULL, 
            0x7EA78C3B5BDF2000ULL, 0x680EB251DCC8CEC7ULL, 0xBB660103565C9008ULL, 0x7217E6ADD8E85D96ULL, 
            0x814A20BC0CA615B4ULL, 0xD48D436A98785624ULL, 0x3556B6A18A3151B4ULL, 0x3351973FE572EFDAULL
        },
        {
            0x2835CF5D021900E1ULL, 0xEE534D38F5664F15ULL, 0x81863D2F1030F4C0ULL, 0x1557A4369F1562CCULL, 
            0xBEE32C7313F7CD55ULL, 0xF73FB5AB172D23CCULL, 0x8CD0D5F240A5FC24ULL, 0xF0E941CAA9C8C46FULL, 
            0x633DD11923556B82ULL, 0x7334986D38FC32DCULL, 0x2116CEA3B15D8566ULL, 0xA5C60E1D938399EAULL, 
            0xDA727492165FFBFAULL, 0x4E57F7119434951BULL, 0xD0F23FF5D403B481ULL, 0xDAB54EFDC5544F59ULL, 
            0xD328A6D613513717ULL, 0x0FC62ECBAD93AD91ULL, 0x960C3F8D0DDC3253ULL, 0x41650CFF762A591DULL, 
            0xDDE70EA64F574AB2ULL, 0x2B143D3C984013C9ULL, 0x5E3FBC819F1067CEULL, 0x571BB06B8D320809ULL, 
            0xC59B732A838AA78AULL, 0xF0042C3FEC77A6F8ULL, 0xCFB55A459C6A4064ULL, 0xD8ED3E84516831F6ULL, 
            0x8AFEB5064AB3E61DULL, 0x49AC1B4618E53FE3ULL, 0x6BBE97637449ED16ULL, 0xF795AF1533D4A46BULL
        },
        {
            0xE66743C7E73A823BULL, 0x1573375CD15A3B89ULL, 0x2C0D6B3A9867C699ULL, 0x5370C61B62B257A5ULL, 
            0xC1AA5DC796EA8782ULL, 0xD61C2B5453F5D086ULL, 0x12BE79D7E052C944ULL, 0xE08BF0A410418A95ULL, 
            0x2EB43B2611D2F904ULL, 0x549BC43950282007ULL, 0x28F82F2CFBF50052ULL, 0x98CDD0961B71EA83ULL, 
            0x0EC1DFF57AE20B69ULL, 0xDA5068CFAF12BD62ULL, 0x26417ED24C97D5EBULL, 0x374695C7BE8E5E8AULL, 
            0x037FDE33116C69E4ULL, 0x0C298F7D7CEA69B1ULL, 0x5EDE4049B2E6606DULL, 0xE5CE3D3F44CFF69EULL, 
            0x022B8EE3ED4F84B8ULL, 0x1C42EA6E0AE92E3EULL, 0xE4F229085712877AULL, 0x1E66393ED7026149ULL, 
            0xA31832891116A20EULL, 0xC3AB0949A40A0CC5ULL, 0xC49B6ED68BBD58ABULL, 0x3A662CD19FD74EF5ULL, 
            0xF819FACBB9707829ULL, 0x162A335DCF612D76ULL, 0x77ECF9921C3F8FA7ULL, 0x738549B4D5A69430ULL
        },
        {
            0x8AEE52D2C9DE4E7DULL, 0x0E049AB56831982BULL, 0x98FA60EF74125C0BULL, 0x3F2734F7478EF0DAULL, 
            0xD3C56624F2C56521ULL, 0xCDEB26F356AD7B92ULL, 0x8EFD399F8253F8BDULL, 0x857C873B489D9360ULL, 
            0x602533653598203CULL, 0x77908A57B3FA43EBULL, 0xF977692CD23F7403ULL, 0xE1B93B1769DC04C0ULL, 
            0xA325553DA32E7D85ULL, 0xB8366CC3F0DBC558ULL, 0x66BF2A882F113966ULL, 0x2C8B0EAC5E639DECULL, 
            0xA1885DE259BA745EULL, 0xFE3DA6016396CC37ULL, 0xAD3C6ED82695BB96ULL, 0xD07BAB5B061D1D8BULL, 
            0xE0867F35E9EC974EULL, 0x1E032554D1B87549ULL, 0x4F06320D1313431EULL, 0x660BD514D93274CFULL, 
            0xB4C408C82AD7F67DULL, 0x8F5C4F99D2B0FD61ULL, 0x448B96819B23A730ULL, 0x9959B077D12AE039ULL, 
            0xCA49B19A822DDA3EULL, 0xABFAE99F8237881AULL, 0x7803D0EEEF7DE0A0ULL, 0x7F2C92F17A08247DULL
        }
    },
    {
        {
            0x107F36E1B5E831C8ULL, 0x10BA5949C47D6E67ULL, 0x395154D0B59A79E7ULL, 0xA9F47F7604554754ULL, 
            0xD1C8932CB5B8D897ULL, 0x358D7456299D28E2ULL, 0xCD54CC2FDB93B191ULL, 0x0BCB695AA9D8AECCULL, 
            0xF5ADD92851A5DE6CULL, 0x6B7AAD3EB1FBDE75ULL, 0x176A690C905C67D6ULL, 0x3120CA7241965EB0ULL, 
            0xD96F7083F21084ADULL, 0xA2D8719AE391CD8BULL, 0xEB687D4C9269A0C9ULL, 0x5BA8F76AB04E114BULL, 
            0x72D5628C4E5A62C9ULL, 0x55DF1B6319D33C75ULL, 0x462157696E60E951ULL, 0x11B118C29BBD9861ULL, 
            0x16EED933874BEC22ULL, 0xFDF425AF8A3F7B14ULL, 0x27800115B799E085ULL, 0x4DF28AAA5BC1DC66ULL, 
            0x1C6DA58681C72E4DULL, 0xF90DC77A3A302218ULL, 0x6A761C33A4D5E4F7ULL, 0x8FAB0482FACBBE13ULL, 
            0x20CDBBD9CE768096ULL, 0xC838DF4141A73F7DULL, 0xD49FB0CDA9736B9DULL, 0x7764167519068FA7ULL
        },
        {
            0x9B6468FFCF3AFA10ULL, 0xBE37CAC5DDD9151EULL, 0xF56D03426D857F86ULL, 0x1FF6B0137227D504ULL, 
            0xBDF65E56E134136AULL, 0x9DC5ED4D1D49F196ULL, 0x8C5F83A7CE082F79ULL, 0xC40DE057DE091936ULL, 
            0xE88A5985B237A335ULL, 0x690C893CB43516E1ULL, 0x3670E5C799F6BC91ULL, 0xDC119F07FFDFBD93ULL, 
            0x98EAF291FDE797E5ULL, 0xD66F6C122A8AD472ULL, 0xA5A30D4520F8AA51ULL, 0xB71DD4A3DCF1A5A0ULL, 
            0x8D528C233E0599BFULL, 0x8506687B227452DBULL, 0xB63BA60C851B4B69ULL, 0x2C36E587283E827AULL, 
            0xBACCBC41B237BA51ULL, 0x18CAD2947158E9AAULL, 0x472224E743BA622CULL, 0x4F9F2A5D83563D73ULL, 
            0x4E053AF3AA0B8765ULL, 0x48EC9BC72B919675ULL, 0x448889FA86C7FCDCULL, 0x43D86D6A91A016FCULL, 
            0xAC1849EB7EFEBD0CULL, 0xE8D18F4A60075E75ULL, 0xE4E451C061EF8728ULL, 0xAE343B5F18CC23A0ULL
        },
        {
            0x37CCF62D99AFCBCCULL, 0xA9D69153D33728B5ULL, 0x2EADC315AB319FE5ULL, 0x3AC90541D5CA5E9BULL, 
            0x5546E22BA189BD8DULL, 0x63DBD6370A92E4F1ULL, 0x45BCD49FBC974779ULL, 0x4C7943D5A8627022ULL, 
            0x3FF8E23F81778E54ULL, 0x0A6996850234D69CULL, 0x04A3FFFDEBC5A893ULL, 0xBADFAF18822A294AULL, 
            0x2842B3E832B04412ULL, 0x98475F99984429FAULL, 0xDF01CC2512F841E2ULL, 0xC05B98B5F0A47AA0ULL, 
            0x514F47FFD41C3AB8ULL, 0x20C3B4A354E5C408ULL, 0x501D977666A21EE5ULL, 0x35162BD9197CB858ULL, 
            0x464EE198D60C8925ULL, 0x24048A51550996D3ULL, 0xAC7A487F995AF304ULL, 0x73343A65CD1F2C13ULL, 
            0x6FB0B7FD9B376408ULL, 0xE952ABC631F22271ULL, 0x2E8016747BF57244ULL, 0x1A15EE3532F02A72ULL, 
            0xF57E1D707833D358ULL, 0x7338253ECBA8565CULL, 0xD1B59230C976B7E6ULL, 0x0A4EC450D1758C43ULL
        },
        {
            0xFEB31513EF743584ULL, 0xC43F1528417F597AULL, 0x66C2F0F320033E92ULL, 0x6651B36301D18AABULL, 
            0x197D97B5D165BFF5ULL, 0x8B2C69A09274EF59ULL, 0xE26B44E3CD80A114ULL, 0xB475F50FF859E2BCULL, 
            0x4856E1862655F46AULL, 0x70FBE198D356247BULL, 0x2C625CE68089ADC3ULL, 0x231568DE2D4966A9ULL, 
            0xE41EC358182B88F9ULL, 0x960E284D54749E25ULL, 0x413FFC93944C9F4EULL, 0x81AC994B7C3474A5ULL, 
            0x95895BD544F2E732ULL, 0xAB0ED35DBA40E7CCULL, 0x04E3C8CBAC3E2396ULL, 0xE5D611F17D6FB2ECULL, 
            0x8E9E49DBC5FBC895ULL, 0x814B7AB58893F9AFULL, 0x46AF0A338AEBCFE9ULL, 0x084C92E9681B06D8ULL, 
            0x49C25E1067CCF025ULL, 0xE9AC6C63702D482CULL, 0x26EE5A5241B1FD0BULL, 0xFB75530E0F9E39BEULL, 
            0x76AC737E1026F7D8ULL, 0x514C1A375797081AULL, 0x0C104316991ACACAULL, 0x9EA20CE965F703DFULL
        },
        {
            0x6C7DBA6E57CD3D17ULL, 0xB1700280E628C12EULL, 0x494472E7D4F8952BULL, 0x0667CDE8034BE70DULL, 
            0x3B3D0DC6C94F5424ULL, 0xD3691E99D15B164BULL, 0xB16CCA48E2DC9056ULL, 0xF5C8B1912812F00AULL, 
            0x8DA1BFAF4EED9491ULL, 0xABDA1A21ED0DA27BULL, 0x6541D87FCEB7D7A2ULL, 0xF07FC85D3099B31EULL, 
            0x61A62CA99AE05687ULL, 0x78B99CEA219563DEULL, 0x54C9166AA1611B59ULL, 0x662EF6CD0AA575B1ULL, 
            0x2EF29B8B68BFC69CULL, 0x99BE346B714BB648ULL, 0x6D0F98C22EADDED9ULL, 0x8837D44EDA5160CEULL, 
            0x9CFC7B4170AFE968ULL, 0xE4A61751BAC0B68BULL, 0xB6F316A7A4038563ULL, 0x21E879D84BF3CF8DULL, 
            0xA98F671E7287663FULL, 0xE0CBBF680E5DFA03ULL, 0xD212FAB47731E4FDULL, 0x7995AB4D66B8C6DAULL, 
            0xD7DA7A85B3EA3202ULL, 0x9F88FB922704F870ULL, 0x33A16C5AE0E4F487ULL, 0x88DB39FF02FEB2B6ULL
        },
        {
            0x1E63F290793F4C7FULL, 0x5F516AEBFE471F2FULL, 0x06CD80D49641AA03ULL, 0x99C37FE29922212DULL, 
            0xF305D255E1C3F413ULL, 0x530E26AAC8A85DCAULL, 0x64B49A6C2FF05162ULL, 0x9181F4E9E4D09174ULL, 
            0xF44DC3369DB5B9B6ULL, 0x83F017646FA7FF73ULL, 0x9F7717ECEBFAE954ULL, 0xFDBAD908DFB69562ULL, 
            0x52D9C959D0722785ULL, 0xF51844698AAE6001ULL, 0x3E467E9AC6A0DE55ULL, 0xACCC917A9E43A7C0ULL, 
            0x4FFBE3469D30C129ULL, 0xA9C006147F121680ULL, 0x608E611139BC21AEULL, 0x4BCCD644E1FB0763ULL, 
            0x7E316995D1B6550DULL, 0x3E73B76288A95F6DULL, 0xD6693249413B5882ULL, 0x61C629A0415DD519ULL, 
            0xAF23E459E812623FULL, 0x98086B86A1A8A79EULL, 0xAFDE2F5F523E2B07ULL, 0x4DC9419EF0A736B7ULL, 
            0x828E73C97F7AAA58ULL, 0x685B353E0158ED3BULL, 0x54FFCB29E5A3798FULL, 0xE696805B45622E83ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Naos::kPhaseHConstants = {
    0x06AEFBA46C5F3FF7ULL,
    0xEFF0A605E497D34FULL,
    0x7BE5175C078EDC61ULL,
    0x06AEFBA46C5F3FF7ULL,
    0xEFF0A605E497D34FULL,
    0x7BE5175C078EDC61ULL,
    0xC238E079A0D1869EULL,
    0xBE980CD2C67C48F8ULL,
    0x10,
    0xEC,
    0x3D,
    0x88,
    0xC1,
    0xFC,
    0x7A,
    0x69
};

