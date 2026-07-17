#include "TwistExpander_Alcor.hpp"
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

TwistExpander_Alcor::TwistExpander_Alcor()
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

void TwistExpander_Alcor::KDF_A(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xBA16B71A93ED5E3FULL; std::uint64_t aIngress = 0x83CB3EBD674CE4EFULL; std::uint64_t aCarry = 0xB586E47870AC959DULL;

    std::uint64_t aWandererA = 0xDF13DB92F49C2645ULL; std::uint64_t aWandererB = 0xC9B5E05F323541F1ULL; std::uint64_t aWandererC = 0xB11261B45BCF64F2ULL; std::uint64_t aWandererD = 0xC9AA46974F0B0F0FULL;
    std::uint64_t aWandererE = 0xF6CFC8CDA96359B1ULL; std::uint64_t aWandererF = 0xB7ACDE8160FA9E09ULL; std::uint64_t aWandererG = 0x93073353334DB220ULL; std::uint64_t aWandererH = 0xA467682279CE20E1ULL;
    std::uint64_t aWandererI = 0xBB8C0D06D6F6151BULL; std::uint64_t aWandererJ = 0xA9D6938F3E16C945ULL; std::uint64_t aWandererK = 0xD829952E34F870FFULL;

    // [kdf-a]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10431334644049431439U;
        aCarry = 12428439526903900620U;
        aWandererA = 10517903370246119599U;
        aWandererB = 11993089339033369909U;
        aWandererC = 11960974105152927754U;
        aWandererD = 10951873265801762316U;
        aWandererE = 11763004571417458992U;
        aWandererF = 14658553986802981627U;
        aWandererG = 16524417129408719272U;
        aWandererH = 17782883457046186211U;
        aWandererI = 17180102218327670299U;
        aWandererJ = 11286800185563142892U;
        aWandererK = 14641295979294302676U;
    TwistExpander_Alcor_Arx::KDF_A_A(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_A_B(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_A_C(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_A_D(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_A_E(pWorkSpace,
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

void TwistExpander_Alcor::KDF_B(std::uint64_t pNonce,
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
    std::uint64_t aPrevious = 0xAAA60E92AE6A35DCULL; std::uint64_t aIngress = 0x84A15FF923ACAD10ULL; std::uint64_t aCarry = 0xCC79F074F9D8BA66ULL;

    std::uint64_t aWandererA = 0xF874AB87698C4414ULL; std::uint64_t aWandererB = 0xA299EFD85BA7D46AULL; std::uint64_t aWandererC = 0xA15140A0D95C8205ULL; std::uint64_t aWandererD = 0xAB7E49ECCE53C049ULL;
    std::uint64_t aWandererE = 0xFEF50FA36B6DB47FULL; std::uint64_t aWandererF = 0x806059FFA062C25FULL; std::uint64_t aWandererG = 0xD5F7762A1A63EA53ULL; std::uint64_t aWandererH = 0xB505206B3B9B1733ULL;
    std::uint64_t aWandererI = 0xA3A7BA7B70164E6DULL; std::uint64_t aWandererJ = 0xE390830185EFE1A6ULL; std::uint64_t aWandererK = 0x9CBB28851A708215ULL;

    // [kdf-b]
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
        aPrevious = 10699330978046429712U;
        aCarry = 15115812314555799281U;
        aWandererA = 9984181116815927728U;
        aWandererB = 13797778602100438460U;
        aWandererC = 11560745500339573331U;
        aWandererD = 10594614331014369927U;
        aWandererE = 10138782099738215195U;
        aWandererF = 15477460446052428140U;
        aWandererG = 13780362312103286083U;
        aWandererH = 9920779215585613513U;
        aWandererI = 11334120618976975079U;
        aWandererJ = 11430917457718095340U;
        aWandererK = 14182223671640534599U;
    TwistExpander_Alcor_Arx::KDF_B_A(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_B_B(pWorkSpace,
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

    TwistExpander_Alcor_Arx::KDF_B_C(pWorkSpace,
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
    TwistExpander_Alcor_Arx::KDF_B_D(pWorkSpace,
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

void TwistExpander_Alcor::Seed(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x9C1A744B3DF87EA8ULL;
    std::uint64_t aIngress = 0xE1D3619EF520001AULL;
    std::uint64_t aCarry = 0x950C2825661CA765ULL;

    std::uint64_t aWandererA = 0xE2D457C386F682F6ULL;
    std::uint64_t aWandererB = 0xD56F8FEF095CC9E7ULL;
    std::uint64_t aWandererC = 0xFE03D56C105406AAULL;
    std::uint64_t aWandererD = 0xE3EA66D7E4C51C65ULL;
    std::uint64_t aWandererE = 0xBBA9990DF53E4013ULL;
    std::uint64_t aWandererF = 0xA741AFDD016D30B9ULL;
    std::uint64_t aWandererG = 0x8E21F7CFC103E512ULL;
    std::uint64_t aWandererH = 0xB11D9012C0DE9DBBULL;
    std::uint64_t aWandererI = 0xC7A689F267CF5A50ULL;
    std::uint64_t aWandererJ = 0x9561CD4DCE131ED8ULL;
    std::uint64_t aWandererK = 0xCC95A7B631060A48ULL;

    // [seed]
        TwistSnow::Sha256Counter(aSource, aSnowLaneA);
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
        TwistSnow::AES256Counter(aSource, aSnowLaneD);
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
    TwistExpander_Alcor_Arx::Seed_A(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_B(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_C(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_D(pWorkSpace,
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
    TwistExpander_Alcor_Arx::Seed_E(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_F(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_G(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Seed_H(pWorkSpace,
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

    aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectA;
    aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixSelectB;
    aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollA;
    aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixUnrollB;
    aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgA;
    aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgB;
    aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgC;
    aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseDConstants.mMatrixArgD;
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
    TwistExpander_Alcor_Arx::Seed_I(pWorkSpace,
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
    TwistExpander_Alcor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alcor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// SmartSquash candidate 2 of 33
// Exploration cases: 50000000
// Nearest-family diversity: 1984 / 1984 (100.00%)
// Total distance from earlier candidates: 1984
void TwistExpander_Alcor::SquashInvestToKeyBoxes() {
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
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 7U), *aFragmentB = aInvestLaneB + (W_KEY * 6U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 11U), *aFragmentD = aInvestLaneD + (W_KEY * 11U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 14U), *aFragmentF = aInvestLaneF + (W_KEY * 10U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 1U), *aFragmentH = aInvestLaneH + (W_KEY * 2U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 537U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1767U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1861U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1189U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 737U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1700U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 259U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1200U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 11U), *aFragmentB = aInvestLaneB + (W_KEY * 11U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 8U), *aFragmentD = aInvestLaneD + (W_KEY * 12U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 12U), *aFragmentF = aInvestLaneF + (W_KEY * 6U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 7U), *aFragmentH = aInvestLaneH + (W_KEY * 6U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 265U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 963U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1737U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 886U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1525U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1204U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 659U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 258U) & W_KEY1)]) << 8U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 4U), *aFragmentB = aInvestLaneB + (W_KEY * 12U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 6U), *aFragmentD = aInvestLaneD + (W_KEY * 6U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 15U), *aFragmentF = aInvestLaneF + (W_KEY * 0U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 15U), *aFragmentH = aInvestLaneH + (W_KEY * 11U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1962U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 881U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2019U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 151U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 364U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 443U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1671U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 382U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 8U), *aFragmentB = aInvestLaneB + (W_KEY * 1U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 1U), *aFragmentD = aInvestLaneD + (W_KEY * 10U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 6U), *aFragmentF = aInvestLaneF + (W_KEY * 14U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 13U), *aFragmentH = aInvestLaneH + (W_KEY * 4U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1479U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 70U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1640U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1560U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 189U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1156U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 353U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 216U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 10U), *aFragmentB = aInvestLaneB + (W_KEY * 8U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 0U), *aFragmentD = aInvestLaneD + (W_KEY * 1U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 0U), *aFragmentF = aInvestLaneF + (W_KEY * 9U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 6U), *aFragmentH = aInvestLaneH + (W_KEY * 0U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1256U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 207U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 252U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 964U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1509U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 127U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1511U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 106U) & W_KEY1)]) << 40U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 13U), *aFragmentB = aInvestLaneB + (W_KEY * 2U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 3U), *aFragmentD = aInvestLaneD + (W_KEY * 15U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 11U), *aFragmentF = aInvestLaneF + (W_KEY * 7U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 14U), *aFragmentH = aInvestLaneH + (W_KEY * 1U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1718U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1046U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1845U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 110U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1183U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1148U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1555U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1457U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 2U), *aFragmentB = aInvestLaneB + (W_KEY * 9U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 7U), *aFragmentD = aInvestLaneD + (W_KEY * 3U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 4U), *aFragmentF = aInvestLaneF + (W_KEY * 1U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 9U), *aFragmentH = aInvestLaneH + (W_KEY * 8U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1045U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1322U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2001U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 310U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 182U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 552U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1279U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 149U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 9U), *aFragmentB = aInvestLaneB + (W_KEY * 10U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 15U), *aFragmentD = aInvestLaneD + (W_KEY * 13U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 7U), *aFragmentF = aInvestLaneF + (W_KEY * 13U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 2U), *aFragmentH = aInvestLaneH + (W_KEY * 12U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxA[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 621U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1764U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 371U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 892U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 904U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 300U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1092U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 2007U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 14U), *aFragmentB = aInvestLaneB + (W_KEY * 0U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 12U), *aFragmentD = aInvestLaneD + (W_KEY * 9U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 2U), *aFragmentF = aInvestLaneF + (W_KEY * 15U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 12U), *aFragmentH = aInvestLaneH + (W_KEY * 14U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[0][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1919U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1871U) & W_KEY1)]) << 8U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1102U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1518U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1190U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1401U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1644U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1543U) & W_KEY1)]) << 16U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 1U), *aFragmentB = aInvestLaneB + (W_KEY * 5U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 4U), *aFragmentD = aInvestLaneD + (W_KEY * 8U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 13U), *aFragmentF = aInvestLaneF + (W_KEY * 11U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 4U), *aFragmentH = aInvestLaneH + (W_KEY * 10U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[1][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 268U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 2012U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 487U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1463U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 667U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1386U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1281U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 405U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 15U), *aFragmentB = aInvestLaneB + (W_KEY * 3U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 5U), *aFragmentD = aInvestLaneD + (W_KEY * 7U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 3U), *aFragmentF = aInvestLaneF + (W_KEY * 2U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 8U), *aFragmentH = aInvestLaneH + (W_KEY * 9U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[2][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 358U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1661U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1307U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 308U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 475U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1503U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1813U) & W_KEY1)]) << 24U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1465U) & W_KEY1)]) << 32U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 12U), *aFragmentB = aInvestLaneB + (W_KEY * 7U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 9U), *aFragmentD = aInvestLaneD + (W_KEY * 2U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 5U), *aFragmentF = aInvestLaneF + (W_KEY * 12U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 3U), *aFragmentH = aInvestLaneH + (W_KEY * 15U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[3][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 379U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 617U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 742U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1427U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 84U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 646U) & W_KEY1)]) << 56U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 453U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 430U) & W_KEY1)]) << 0U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseA(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 5U), *aFragmentB = aInvestLaneB + (W_KEY * 13U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 13U), *aFragmentD = aInvestLaneD + (W_KEY * 5U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 1U), *aFragmentF = aInvestLaneF + (W_KEY * 3U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 0U), *aFragmentH = aInvestLaneH + (W_KEY * 7U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[4][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 256U) & W_KEY1)]) << 0U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1215U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 501U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 681U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 1416U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 247U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1645U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1321U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 6U), *aFragmentB = aInvestLaneB + (W_KEY * 4U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 2U), *aFragmentD = aInvestLaneD + (W_KEY * 14U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 8U), *aFragmentF = aInvestLaneF + (W_KEY * 4U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 5U), *aFragmentH = aInvestLaneH + (W_KEY * 3U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[5][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1989U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 772U) & W_KEY1)]) << 32U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1730U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 120U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 288U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1227U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 735U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 434U) & W_KEY1)]) << 48U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseB(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 3U), *aFragmentB = aInvestLaneB + (W_KEY * 15U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 14U), *aFragmentD = aInvestLaneD + (W_KEY * 4U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 9U), *aFragmentF = aInvestLaneF + (W_KEY * 8U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 11U), *aFragmentH = aInvestLaneH + (W_KEY * 5U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[6][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 188U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 875U) & W_KEY1)]) << 16U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 1313U) & W_KEY1)]) << 56U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1449U) & W_KEY1)]) << 48U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 424U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 1488U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 1562U) & W_KEY1)]) << 40U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 1612U) & W_KEY1)]) << 24U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }

    {
        std::uint8_t *aFragmentA = aInvestLaneA + (W_KEY * 0U), *aFragmentB = aInvestLaneB + (W_KEY * 14U);
        std::uint8_t *aFragmentC = aInvestLaneC + (W_KEY * 10U), *aFragmentD = aInvestLaneD + (W_KEY * 0U);
        std::uint8_t *aFragmentE = aInvestLaneE + (W_KEY * 10U), *aFragmentF = aInvestLaneF + (W_KEY * 5U);
        std::uint8_t *aFragmentG = aInvestLaneG + (W_KEY * 10U), *aFragmentH = aInvestLaneH + (W_KEY * 13U);
        std::uint8_t *aKeyRow = &(mWorkspace->mKeyBoxB[7][0]);
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            std::uint64_t aSquash =
                (static_cast<std::uint64_t>(aFragmentA[((aIndex + 1990U) & W_KEY1)]) << 16U) | (static_cast<std::uint64_t>(aFragmentB[((aIndex + 1170U) & W_KEY1)]) << 0U) |
                (static_cast<std::uint64_t>(aFragmentC[((aIndex + 2044U) & W_KEY1)]) << 8U) | (static_cast<std::uint64_t>(aFragmentD[((aIndex + 1029U) & W_KEY1)]) << 40U) |
                (static_cast<std::uint64_t>(aFragmentE[((aIndex + 826U) & W_KEY1)]) << 32U) | (static_cast<std::uint64_t>(aFragmentF[((aIndex + 20U) & W_KEY1)]) << 24U) |
                (static_cast<std::uint64_t>(aFragmentG[((aIndex + 952U) & W_KEY1)]) << 48U) | (static_cast<std::uint64_t>(aFragmentH[((aIndex + 73U) & W_KEY1)]) << 56U);
            aKeyRow[aIndex] = static_cast<std::uint8_t>(TwistMix64::DiffuseC(aSquash));
        }
    }
}

void TwistExpander_Alcor::TwistBlock(TwistWorkSpace *pWorkSpace,
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
    std::uint64_t aPrevious = 0x901D67EA5351FF37ULL; std::uint64_t aIngress = 0xBD0A0F5273AE2DDFULL; std::uint64_t aCarry = 0xA79B18AFDC784736ULL;

    std::uint64_t aWandererA = 0xF08EC2B1F64DABBFULL; std::uint64_t aWandererB = 0x9583FF2CB9C478FBULL; std::uint64_t aWandererC = 0xAE544048DB32871EULL; std::uint64_t aWandererD = 0x953D09B253AE7DBFULL;
    std::uint64_t aWandererE = 0xC3C1D6DFEBECA123ULL; std::uint64_t aWandererF = 0x9FD06A2B7ED5DAD6ULL; std::uint64_t aWandererG = 0xF1856C152AF21509ULL; std::uint64_t aWandererH = 0xFD897D6AE9BBF3BFULL;
    std::uint64_t aWandererI = 0x92565C9D65934C0EULL; std::uint64_t aWandererJ = 0xD4B1CE94CFA1403BULL; std::uint64_t aWandererK = 0x9ED86EF962A12DA7ULL;

    // [seed]
        aPrevious = 14447669410581926024U;
        aCarry = 18116067811571424314U;
        aWandererA = 16053818680639833235U;
        aWandererB = 11352563626449092506U;
        aWandererC = 14958787340858693688U;
        aWandererD = 12496900714717264082U;
        aWandererE = 17630792275413442880U;
        aWandererF = 16622908357432897421U;
        aWandererG = 16286936047499039887U;
        aWandererH = 15914331901731621514U;
        aWandererI = 16699879989630914711U;
        aWandererJ = 12365823539840661330U;
        aWandererK = 12194049713144064336U;
    TwistExpander_Alcor_Arx::Twist_A(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_B(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_C(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_D(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_E(pWorkSpace,
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

    std::uint64_t aDomainWordMatrixSelectA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pWorkSpace->mDomainBundle.mPhaseCConstants.mMatrixArgD;
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
    TwistExpander_Alcor_Arx::Twist_F(pWorkSpace,
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

    TwistExpander_Alcor_Arx::Twist_G(pWorkSpace,
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
    TwistExpander_Alcor_Arx::GROW_A(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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
    TwistExpander_Alcor_Arx::GROW_B(pWorkSpace,
                 &aPrevious,
                 &aIngress,
                 &aCarry,
                 &aWandererA,
                 &aWandererB,
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

// GrowA candidate 2 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 668; nearest pair: 668 / 674
void TwistExpander_Alcor::GrowKeyA(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1356U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4136U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5634U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2086U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 5543U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2646U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 556U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 244U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3214U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 2349U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1621U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2369U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 1U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3220U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 513U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 751U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2491U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aExpandLaneA[aFoldIndexA]) << 8U) | (static_cast<std::uint32_t>(aExpandLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aExpandLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aExpandLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 549U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 988U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 570U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1687U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1717U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 370U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1520U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1588U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1526U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1058U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 351U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1352U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 16U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1922U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 965U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 77U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 704U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 310U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 566U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1569U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 839U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteA[aIndex] = aFoldWord;
        }
    }
}

// GrowB candidate 2 of 33
// Exploration cases: 50000000
// Total structural distance from earlier candidates: 667; nearest pair: 667 / 674
void TwistExpander_Alcor::GrowKeyB(TwistWorkSpace *pWorkSpace) {
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
        const std::size_t aFoldBaseC = 3U * S_QUARTER;
        const std::size_t aFoldBaseD = 3U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3519U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 4364U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 307U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3755U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 24U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * S_QUARTER;
        const std::size_t aFoldBaseB = 3U * S_QUARTER;
        const std::size_t aFoldBaseC = 2U * S_QUARTER;
        const std::size_t aFoldBaseD = 0U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 3395U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 7722U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 6033U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 2085U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 0U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aScrapLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * S_QUARTER;
        const std::size_t aFoldBaseB = 2U * S_QUARTER;
        const std::size_t aFoldBaseC = 0U * S_QUARTER;
        const std::size_t aFoldBaseD = 1U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6548U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 347U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 5988U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 6233U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 0U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aScrapLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * S_QUARTER;
        const std::size_t aFoldBaseB = 0U * S_QUARTER;
        const std::size_t aFoldBaseC = 1U * S_QUARTER;
        const std::size_t aFoldBaseD = 2U * S_QUARTER;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_QUARTER); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 6958U) & S_QUARTER1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1234U) & S_QUARTER1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 497U) & S_QUARTER1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 3976U) & S_QUARTER1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aWorkLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aWorkLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aWorkLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aWorkLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseA(aFoldWord);
            aScrapLaneD[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 1U * W_KEY;
        const std::size_t aFoldBaseB = 0U * W_KEY;
        const std::size_t aFoldBaseC = 3U * W_KEY;
        const std::size_t aFoldBaseD = 2U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 1024U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 243U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 435U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1282U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aMergeLaneA[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 3U * W_KEY;
        const std::size_t aFoldBaseB = 2U * W_KEY;
        const std::size_t aFoldBaseC = 1U * W_KEY;
        const std::size_t aFoldBaseD = 0U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 148U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 258U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 665U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1097U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 16U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneB[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 2U * W_KEY;
        const std::size_t aFoldBaseB = 3U * W_KEY;
        const std::size_t aFoldBaseC = 2U * W_KEY;
        const std::size_t aFoldBaseD = 1U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 142U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 424U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 1387U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1337U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 24U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 8U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneC[aIndex] = aFoldWord;
        }
    }
    {
        const std::size_t aFoldBaseA = 0U * W_KEY;
        const std::size_t aFoldBaseB = 1U * W_KEY;
        const std::size_t aFoldBaseC = 0U * W_KEY;
        const std::size_t aFoldBaseD = 3U * W_KEY;
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = aFoldBaseA + ((aIndex + 611U) & W_KEY1);
            const std::size_t aFoldIndexB = aFoldBaseB + ((aIndex + 1609U) & W_KEY1);
            const std::size_t aFoldIndexC = aFoldBaseC + ((aIndex + 195U) & W_KEY1);
            const std::size_t aFoldIndexD = aFoldBaseD + ((aIndex + 1836U) & W_KEY1);
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aScrapLaneA[aFoldIndexA]) << 16U) | (static_cast<std::uint32_t>(aScrapLaneB[aFoldIndexB]) << 0U) |
                (static_cast<std::uint32_t>(aScrapLaneC[aFoldIndexC]) << 8U) | (static_cast<std::uint32_t>(aScrapLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseC(aFoldWord);
            aMergeLaneD[aIndex] = aFoldWord;
        }
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(W_KEY); aIndex += 1U) {
            const std::size_t aFoldIndexA = (aIndex + 1116U) & W_KEY1;
            const std::size_t aFoldIndexB = (aIndex + 906U) & W_KEY1;
            const std::size_t aFoldIndexC = (aIndex + 1894U) & W_KEY1;
            const std::size_t aFoldIndexD = (aIndex + 781U) & W_KEY1;
            std::uint32_t aFoldWord =
                (static_cast<std::uint32_t>(aMergeLaneA[aFoldIndexA]) << 0U) | (static_cast<std::uint32_t>(aMergeLaneB[aFoldIndexB]) << 8U) |
                (static_cast<std::uint32_t>(aMergeLaneC[aFoldIndexC]) << 16U) | (static_cast<std::uint32_t>(aMergeLaneD[aFoldIndexD]) << 24U);
            aFoldWord = TwistMix32::DiffuseB(aFoldWord);
            aKeyRowWriteB[aIndex] = aFoldWord;
        }
    }
}

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseASalts = {
    {
        {
            0x00105BBFA6D6BE56ULL, 0xB01379D1FE84E34FULL, 0x3767E4A809D1908AULL, 0x6BD6EE5958BA9307ULL, 
            0xCA5C4A224F8D5C03ULL, 0x0148877EF53B8630ULL, 0xAF43F8A65ACBFE1EULL, 0x37A853377D9EC3D2ULL, 
            0xFBADF1EB1B41E98AULL, 0xC99727841E6C8496ULL, 0x4998ADA3F05ED1ECULL, 0x5889B0B3CB6FC146ULL, 
            0x118261A01ABE3649ULL, 0x9B50E324BE0DCCAAULL, 0x5625BEC2AECA868CULL, 0xB4FF309E32E88417ULL, 
            0xCD177B247E0A4C3AULL, 0x7E2B9A9170521CC2ULL, 0xB9F38C666CCA3B40ULL, 0x6166421AB7048105ULL, 
            0x969BAAC9122FB5C5ULL, 0x278CA101B6025A72ULL, 0x9F7F17CC5C3A341AULL, 0x87984B09B7069AF3ULL, 
            0x0BD985EA2AC5CDFAULL, 0xDE78AE6F9D8A2DBEULL, 0xAE40E9145B77C720ULL, 0x780048CB092F826BULL, 
            0x2244F9A3FEBC0446ULL, 0x3ECD4AA934AB5B4DULL, 0xE9E504E988DF2952ULL, 0x07526D937E175AE3ULL
        },
        {
            0xE3DAB31570823611ULL, 0x61D8FB437D9ACD06ULL, 0xDC501D35C15105F0ULL, 0x572F361CF6ACDEF9ULL, 
            0xF1C4355CC729EA39ULL, 0x8607C143CD08A292ULL, 0x1F6571A89FC8C982ULL, 0xE5D591DC19050688ULL, 
            0x24DD740BB5AD743FULL, 0xD2053392C31C9716ULL, 0x47CCFD1594DCF0CAULL, 0xF3A25291248D8527ULL, 
            0xA34CD1FE48B74C68ULL, 0x42B6C8C0C5DF0A5BULL, 0x6C0CD03718DFC219ULL, 0x03DD821D4D9101E3ULL, 
            0x7E636B11E06BF9D0ULL, 0x5F5488E8FE868384ULL, 0x8D1AE9376F3B062EULL, 0xDBD0002A18896C5CULL, 
            0x0E6CC3F83C28FA1EULL, 0xD2B3497E52102FD1ULL, 0x14612CE165D055F5ULL, 0x9AE6CC87714F08B2ULL, 
            0x927ED54B4783BF1CULL, 0x79E9A37958E12393ULL, 0xB7C5B7A27CA30406ULL, 0x66CED6FB6675F906ULL, 
            0x5108161245DD3CB5ULL, 0x3BF37D038F3B49C0ULL, 0x4625F6F84486CA3BULL, 0x1910F35C4C03A952ULL
        },
        {
            0xEA271FDA85311495ULL, 0xAAF5283C0AEC33A0ULL, 0xC0A532A84BA7D97FULL, 0xF6248AA766DD8744ULL, 
            0x889345F2A23BEBF1ULL, 0x1CF3D558380B83A9ULL, 0xD5670C80C64F2459ULL, 0x01180254821B6C56ULL, 
            0x7B8765D244150967ULL, 0x7E1E9583135678B3ULL, 0x2917CB1254BB8E1FULL, 0x3A1856C9328A74F4ULL, 
            0xB3853C0CA6F5ABB5ULL, 0x5F5C9EDD51411F2AULL, 0x4F918B65040A7685ULL, 0x17B64C7FE96B3A64ULL, 
            0xB11172A121F05878ULL, 0xC659042EDBF596D0ULL, 0xCD4B7DEDE68CF0EFULL, 0x5468226ED4F5AA45ULL, 
            0x10797BE7B67F1DDDULL, 0x3BDDA87AB9C90678ULL, 0x023E0301D64B1353ULL, 0xECB4C96D17B546C4ULL, 
            0xF8716ABC74EA55A0ULL, 0xA20160AAFC354E37ULL, 0xB35AF002174F5EE3ULL, 0x59DDB30B1290A73CULL, 
            0x62A24EB81C56BBC8ULL, 0x3BB2FFB4B3BA91BDULL, 0x6E949F077B34E9B9ULL, 0x922CE2BF3AB0B394ULL
        },
        {
            0x982020F1B6D702EFULL, 0x7A4C134DD4AD75E0ULL, 0x4334C740603B43ADULL, 0x3242DF56ADA4DA01ULL, 
            0x56B7485A66113C1FULL, 0xFC13D6B6264C032CULL, 0x09EC94AD6E35C917ULL, 0x62F50D7209155874ULL, 
            0xC2E78192C4F05976ULL, 0xCEDAE1F80E9C3203ULL, 0x4C898A8D204B090EULL, 0xA661CBC8442B7095ULL, 
            0x310AB146B5055829ULL, 0xCC73D1236D64DE6BULL, 0x2084F1FC5DBE97C3ULL, 0x9769CE8E0EEF55DCULL, 
            0x81B7A22683DCFAF2ULL, 0x964AE68CD6A5F874ULL, 0xD21E9CE3AE17C574ULL, 0x3CD649D7468724A9ULL, 
            0xC3E1633650ECD4D5ULL, 0x16011190920F784DULL, 0xA8CEBC92198F8889ULL, 0xB27631E7EB5CF0C4ULL, 
            0xCA06D21E269508BBULL, 0x6FCFD256F24E5603ULL, 0x54D001667A587F51ULL, 0xB645A26159178B2BULL, 
            0xE4B548A1ADBDD3A5ULL, 0xD1A194FF81F16788ULL, 0x5362481B8E2B8C25ULL, 0xD6B8ED58CC12EEEDULL
        },
        {
            0xF8CCE93EBAB01AB4ULL, 0x7249F3CC44F063F4ULL, 0x7E6EAC4259C84A5CULL, 0x49537C58A6D6E63EULL, 
            0x1D22EA39A8B2FCB7ULL, 0xA5F5C796ABE03A9EULL, 0x484756EE41D4FC9CULL, 0x334EE2629936D971ULL, 
            0x21CDA5E7C0C02DEFULL, 0xCA173F35C6CC5582ULL, 0x71371C4257AFBEC6ULL, 0xBB31DF4512536097ULL, 
            0x4F9D4C3D1C950FE7ULL, 0xD5CE5795971B4FB1ULL, 0x72C713212AE4DE02ULL, 0xACCDEFAC0E1C0D9CULL, 
            0x48158494AB0F1381ULL, 0x3AE5D34B3C32CB40ULL, 0x2D27EF1E8DDF27EFULL, 0x577B2349187739B2ULL, 
            0x6B00F4C561B4DD5FULL, 0x27EBBA2327D88C6BULL, 0x5471FAD03655B012ULL, 0x6EE13589560E1E28ULL, 
            0x7CF567A6B14D37EAULL, 0x5BFCE0779E9E1AF9ULL, 0xFEFBF2BCA0A2E4A6ULL, 0x8DD8898105B1D6D4ULL, 
            0xED6C3327602B8888ULL, 0x8F1C65F6F7C2C7BAULL, 0xA50E0E753825B6BCULL, 0x00A53B7362E7DED4ULL
        },
        {
            0xDE368BAE60394AC8ULL, 0x274AF657F6C8A17AULL, 0xB8C0F096E9942AEAULL, 0x1F1B2268B04C47A1ULL, 
            0x2479E18CE2E6A825ULL, 0x3201CEE78853C675ULL, 0xE854E7404168D393ULL, 0xE101F973EC686B7EULL, 
            0x7D1B4A0D360592CFULL, 0x54EC92761DBA72ACULL, 0x4B57E066D3DCCDD7ULL, 0xC220C159C5DEBA46ULL, 
            0xAE24635C9ACBCC31ULL, 0x6803117CFF389069ULL, 0x41CB9DFF367B2719ULL, 0x8302F01E7EB4D8D0ULL, 
            0x840A7C0EE33DF61BULL, 0x323D6E27DF740244ULL, 0x863EB9385C4F3AA8ULL, 0x3437CF6830B7AF05ULL, 
            0xA416848B98B249B5ULL, 0xA324B0A3FEFF5B3EULL, 0x0C7CF2377DA7B39AULL, 0xDBCD63C9304A2DFDULL, 
            0x64B045622540028DULL, 0x49E85456E180AC0EULL, 0xD603DAFEFE0D168EULL, 0x9B07EBB9C242E400ULL, 
            0x2534AC7E420A030CULL, 0x44AADC58A9F26A2CULL, 0x24D3764BA128EAD0ULL, 0x78B2BF862FC7278CULL
        }
    },
    {
        {
            0xFC4D3D5D3B3877C0ULL, 0x53C0EAD72EA4437BULL, 0x2B58AA3C088BCCCDULL, 0xEF3DE7FBCC499C93ULL, 
            0xF6945FB8AD239863ULL, 0xF459337CDD71D6A6ULL, 0xD3353F1710AD4CF1ULL, 0x661A4E90B79F1230ULL, 
            0x54A6DF3916D6E132ULL, 0xC305C2E12194A568ULL, 0x17D03147D8A90508ULL, 0x362D76B995E63353ULL, 
            0xB7389F67F540B177ULL, 0x2E933C076101745DULL, 0xD238AF824F5A12EAULL, 0x9EB9ABF68EC4BCC8ULL, 
            0x20748028049CD07BULL, 0xB3815B1F5DA4FD4BULL, 0xF92954D115D6EDEBULL, 0xF7EE41654C515CC6ULL, 
            0x3BE29191CA5C0356ULL, 0x638C44C1058C3146ULL, 0x470D37B21DF562DAULL, 0x47D03E9FE358FEF3ULL, 
            0x1F2EC473DA9AA07AULL, 0xBCE5CFEC160300B3ULL, 0x61AE225AB275AC8CULL, 0xE26B7452C0B1C3C3ULL, 
            0xF9C2D62BA0AB3A4CULL, 0x7C0588DB820F0DD7ULL, 0xFC7C4169CE70279EULL, 0x61B6CBEE36ACCFE4ULL
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
            0x7DC5ED4242B6B17DULL, 0x72D7BFD07725E642ULL, 0xB7FC57EDFDB14CD1ULL, 0x24333506E6F893EBULL, 
            0x55A236B9204CE179ULL, 0x844979D5413FB673ULL, 0x312BB17C54C6CC0AULL, 0xB29E071CEF7FE544ULL, 
            0x5739CD570C0C9446ULL, 0xFF42CC23F53F517BULL, 0xCEFA3560747C1473ULL, 0x4EA17287B2B451ABULL, 
            0x5225833252E7FC70ULL, 0x6CCDEABCB2813E66ULL, 0x03A0AFE0C6E10D6AULL, 0x1DC2BDA917457F12ULL, 
            0x41508E40FA56E39CULL, 0x8CCFBFAD2A0074CEULL, 0x02935BB25642D19DULL, 0x0D72146C40201835ULL, 
            0x7E8D511C8754CE4AULL, 0x33D71309E79ECF71ULL, 0xF54679F428B4BAC8ULL, 0x49E01A396B0B65D9ULL, 
            0x466FE1CC758ECFBFULL, 0x0CDD52032271004AULL, 0x0A4F2C6848CD403FULL, 0x85AE41D30EA5C2BDULL, 
            0xBC12DF3403F1CC37ULL, 0x19222AF14A5083D4ULL, 0xF1989E7087E99A79ULL, 0xAE56DDB6A999E606ULL
        },
        {
            0x06D2CC848C71E77EULL, 0x454A81AA14855AFBULL, 0xA9C38BE5F998EB35ULL, 0xFFE20D3DAB7BCBC7ULL, 
            0x5E8EFCE7081B047DULL, 0xF6E4F62500151A60ULL, 0xF13FBB372C236638ULL, 0xE31100DB19A80189ULL, 
            0x86D83501A26BE1FFULL, 0xFAF78935ADE8CE99ULL, 0xACA181B085DC9DE8ULL, 0xE6110F1C2D6881E3ULL, 
            0xFE99FDB23F776A1FULL, 0xBADDDAE8F7607163ULL, 0x879F48DB9E54B4F7ULL, 0x1836D44D0117DBCBULL, 
            0x9FBFDB60226B2EF7ULL, 0x15B5E8F88E9311A5ULL, 0x3CABA5B0FF3BB6BBULL, 0x6A9C7D6BE8244FACULL, 
            0x5A23C9D3D218342BULL, 0x5CA95E02D678E6FBULL, 0xD7999F2763AC0FD7ULL, 0x4F0E60BC8FA5F715ULL, 
            0xF36A88BB9E969E3BULL, 0xE7F3FCE86F142BA4ULL, 0x48CA53AFC62820A6ULL, 0x989EACD24DD5B4C9ULL, 
            0xB899CBEB265A3F3DULL, 0xCA20CC32D34CDB8CULL, 0x7DD89BF58FCA9BB8ULL, 0x976720F8DC277EADULL
        },
        {
            0xAE29127A46539936ULL, 0x5AEE8E844F31FFC2ULL, 0x3990D98AA1085964ULL, 0x4FFE837098EFC7A5ULL, 
            0x93CE69EEF426475DULL, 0xFFA6FD2F027F9C78ULL, 0x057A82F3EDA66235ULL, 0xCA83F9E6F15D9EBDULL, 
            0x3121D0287EEC26F9ULL, 0x6E23471302ABB76AULL, 0x0C209EDB3EC117F6ULL, 0xD107D4133E848214ULL, 
            0x462D43ED52844769ULL, 0x860E34A928074AFBULL, 0xA8E88D0D03828864ULL, 0xDF58DEA11569C099ULL, 
            0x69F07F3A10575F19ULL, 0xE2A968C96FE69DBDULL, 0x91C5AD50C2EF2891ULL, 0x81F33729E96A57B4ULL, 
            0x428044F4DD44C640ULL, 0x28D07DD5D36351F0ULL, 0x0ACEE216E34614BAULL, 0x0C662E943DA08EBBULL, 
            0x3F2D6D7F4E383FBFULL, 0xF3434F7128501296ULL, 0xE6B9D6593D962078ULL, 0x48BDAC6C5E074E3CULL, 
            0xFCACDC46DF584FC3ULL, 0x6C0EAF7C56164832ULL, 0x11444B5BC29FA285ULL, 0xC7B1BD04E73C577DULL
        },
        {
            0xBE7C0B01A4B2304DULL, 0x2F860EF11F1132C3ULL, 0xF94C4A9241A72477ULL, 0x17EE60F495A6B8FBULL, 
            0x75ED6A12CBFF2286ULL, 0x4FCBA79DEF5514DEULL, 0x7BE19113350ACFD2ULL, 0xD7BB5ACF46ECF59FULL, 
            0x20616F12E87193C1ULL, 0x7D4E1C52BB458A52ULL, 0xCCC7A4A5C1646DFAULL, 0x737D3CCE477633C8ULL, 
            0x2DD0CFC2B2621CFFULL, 0x49B4AE7A85F1A337ULL, 0x262C4482A3C5DFC2ULL, 0x0598706999BF06B0ULL, 
            0xA7E948512A90A123ULL, 0x375C8B82A35F04F3ULL, 0x67840A577BDA52F6ULL, 0x7D849FBDB0AEE2BEULL, 
            0x949DBFEBDBCBB8EFULL, 0x956D84BBAA154937ULL, 0x7E2DDDE864908035ULL, 0xCD10CD8A9D512857ULL, 
            0x330FA93A9AA3BE33ULL, 0xCCE014854C9CEAE3ULL, 0x29BBF29620E46749ULL, 0x9EAE5D13ACF82755ULL, 
            0xBF4027E46DA34E4FULL, 0xEDC21A17C4FE274DULL, 0xB2A705BDE3E62B6AULL, 0xC503EE548B35ECC0ULL
        }
    },
    {
        {
            0x41BEB0D298F6D708ULL, 0x53E6E3DF2B4E7844ULL, 0xDCA261CFD39CF698ULL, 0x4967F686ACAE82BDULL, 
            0xB62A22996D151D21ULL, 0xA6A63E227341C253ULL, 0x6CD3517577D8EE36ULL, 0x8D3BD657C36A099CULL, 
            0x200361B118CFD1E5ULL, 0xAD70662C530EA8ACULL, 0xE77E486B6B981E3AULL, 0x451EFB4103790FE0ULL, 
            0x8F5FF3ADC623A44DULL, 0xC30FFFFE62445AB0ULL, 0xFBC02B50CC8CC12FULL, 0xA3F97CB23FDF6264ULL, 
            0xFFE19FED654B8429ULL, 0x1563CEBE0924665CULL, 0x0C3B63B1FC841866ULL, 0x0C0665022B55787AULL, 
            0x4D242BD1298052B2ULL, 0x11AE2B72404FB7FCULL, 0x0A38F53BDF18615FULL, 0xF8DF97ED30A78E78ULL, 
            0x0FC07EB99D7ACEC7ULL, 0xEFE3D1096427A987ULL, 0x8E78021F85D3E0DEULL, 0x696241DFA4CE51DCULL, 
            0x8CF5B7721A88E716ULL, 0x7BDEA6F53920CF1AULL, 0x7158B9FE734D85A5ULL, 0x842B1D52E268E7A3ULL
        },
        {
            0xCD774A62F5706877ULL, 0x8CEA64131E692B20ULL, 0x846D914CF6EB08C0ULL, 0x6C47895B0DD45D30ULL, 
            0x9CC25A8BF5F505D4ULL, 0x03CCACBCA592C8BEULL, 0x496D31417A1F12EDULL, 0xC745A9BC560E3CCCULL, 
            0x00A77680AA0CE78AULL, 0xE04939E120823638ULL, 0x2DFA2F36BD38BFEBULL, 0xA446A0B97813EC2EULL, 
            0x7E629BF878E698D6ULL, 0x7FD1C07A04B1630CULL, 0xB22891BEC99AE55BULL, 0x21BA6E6D17DEF9ADULL, 
            0xB5BAB2E6DC9A97C2ULL, 0xBA0F0B893E9E6BEBULL, 0x003C294631DAA852ULL, 0xFA7D7316CEDFDC17ULL, 
            0x670C40A7237C967AULL, 0xF05B6FBF4C45F203ULL, 0x5DB526102056A0C2ULL, 0x7A1C2514C4EE10DCULL, 
            0x4A88CEB8FE065450ULL, 0xBB73B37B79E9F977ULL, 0xA44C80529AF68B81ULL, 0xE4861087C5E2DC3AULL, 
            0x2D30FEA7F150EC52ULL, 0x9F2FB82BC2F7CE4CULL, 0xD48A6BB9D8EE4409ULL, 0xF78D0D6807D9F9EBULL
        },
        {
            0xA92AC4E115B5BD0CULL, 0x9B30D05257F04543ULL, 0xD8D4BDD2BBBB0C88ULL, 0xAE2902513040A96FULL, 
            0xEF36047924F11D41ULL, 0x80505BB423F6CB94ULL, 0x3C7FC87E068B1107ULL, 0x643E1E6FC6B7EC95ULL, 
            0x35EEE95F6738C8C3ULL, 0xFF6552CA32AD459DULL, 0x4FDFE7D9625AFB6DULL, 0x343CB8E9F79D77EEULL, 
            0x458030106C14629FULL, 0x7B4AFC5E282F305AULL, 0x924168DBBE3F1E7CULL, 0xBAA2D9410778CA81ULL, 
            0x0B39AAC54C1714CCULL, 0x80FA42733961F142ULL, 0x7BA5A4246DAB2586ULL, 0x251C91D169D4BC9CULL, 
            0x40F3CD9D5EB58B12ULL, 0xA1F45FE42D205163ULL, 0xC9F6C7FAA6D767F6ULL, 0xBC96959E33EBC08FULL, 
            0xCA4FE52D4D6D2D7CULL, 0x5ABD27B428D366AEULL, 0x389F565C85C0984CULL, 0x62E63C36AC694493ULL, 
            0x62B3292E04A0A8D4ULL, 0x548A1995631C8EBBULL, 0x00FA341EEF3906CDULL, 0x9AF1654DEBEA6709ULL
        },
        {
            0xDBEE82C959C14063ULL, 0x6F29C1F8D3C3B5FEULL, 0x24A2A5E551C2DF3EULL, 0xE1625D21BE1EB0E1ULL, 
            0xFB51BDFFDB2267B9ULL, 0xF7841F59A30C3415ULL, 0x4C2E2C6668390C3AULL, 0x012A2BE14986D56AULL, 
            0x8D0881E2AD1161C0ULL, 0xC8F02CFB728AECB6ULL, 0x12F937F7B7FF4678ULL, 0x84EE83AA31146B2FULL, 
            0x915524DF6286FFDFULL, 0xD5241C1BD18B5201ULL, 0x635926CE4BE9A9D5ULL, 0xE4A181900E9B097AULL, 
            0x1D16E86E01E6E20EULL, 0xAECCCB3B29331B8DULL, 0x3F854C63FCC1A71EULL, 0x8FCC9C17366E3C12ULL, 
            0x9E64F63BFAD8C6A4ULL, 0x715A7DC83BF59B32ULL, 0x8C7EDAAB75DC559FULL, 0xF48E32F42E6700CEULL, 
            0x1ECC5B1CC2F45BC3ULL, 0x8F13AA0B1A570E87ULL, 0xABCADD5294D11104ULL, 0xDF8DBAA506BD5082ULL, 
            0xFF43C35154497531ULL, 0xABF06BC3F37E208FULL, 0xE0123F1981B076CDULL, 0x1993B35EBD023F91ULL
        },
        {
            0xF1A4FAB81B6A67F3ULL, 0xB5F161432CC6DDEBULL, 0x878FC11CAEC9C493ULL, 0xCBD8BB64E71BC376ULL, 
            0x119DE670BDAA64C6ULL, 0x4240658EC3172582ULL, 0x5738C79BD7200E04ULL, 0xA9F1408C932F18A2ULL, 
            0x1A06A5B9F09D45A8ULL, 0xEE80BF4F14F95FFFULL, 0x45AABAEAE9C92233ULL, 0xA942CF03240A41D8ULL, 
            0x9E0B2648443C9FB4ULL, 0x2CB5481AD5E28DE1ULL, 0x745566B5EB63B67FULL, 0x0CF3CD42C5D25226ULL, 
            0x5C1272BFCD99BD66ULL, 0x0A449907EE3DD84EULL, 0x5A5DE0D19F6B697AULL, 0x0C2946CEEEE3BF6BULL, 
            0x50DC790FB365E7B6ULL, 0x441126812B2A2D38ULL, 0x17CB6E7AB5DC4287ULL, 0x0E7202B70CF181B4ULL, 
            0x26A7C19A545FDEF2ULL, 0x260843AE58F74DF2ULL, 0x37758C167844E4EDULL, 0xFE94F50802AF2CE8ULL, 
            0xC061835043FEFF85ULL, 0x797B42A83CD19DB6ULL, 0x56095C2916BE2B64ULL, 0x30E9AD9F5765327CULL
        },
        {
            0xF7E0FBC90CE6C2F4ULL, 0x90931B1236A4493DULL, 0x0D2C9BCD41E72445ULL, 0xDC21BEA370CAE7CEULL, 
            0x5EEC0A21415F856EULL, 0xDB86EBF0A54EE3FEULL, 0x3F2E6641D72D002CULL, 0x0DE503EDA9CB1559ULL, 
            0x48E68490C40CC3E1ULL, 0x7CFF70D140A7E1B4ULL, 0xCF4C2144D68609F8ULL, 0x7DBA8874218716C4ULL, 
            0xC2D660090CAA4DA7ULL, 0x054688E87DBB31D1ULL, 0xD5A04C9BCE556109ULL, 0xF7BD9C56ECBCE421ULL, 
            0x5395648406A2C057ULL, 0x1BE3466E561F31EFULL, 0x629A4D351FA7E830ULL, 0x7F0A4DDF53E36E76ULL, 
            0xF2E3C018A08E5A35ULL, 0xB5261BC6D4F6D6C2ULL, 0x47C7F72C9996ED7AULL, 0xE31D436C668B3BD8ULL, 
            0xD5A332FA4A99B8AEULL, 0x52548410E86F86C8ULL, 0xAD8CD98457959BAEULL, 0x35E210325A59339BULL, 
            0x034123D34D32F60FULL, 0x678F007D60660840ULL, 0x457953D2918912C7ULL, 0xA60632D0B59FFE24ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseAConstants = {
    0xD7EF6A56253D6EBEULL,
    0x3CF57830F2F60379ULL,
    0x56977CA9660CC7E2ULL,
    0xD7EF6A56253D6EBEULL,
    0x3CF57830F2F60379ULL,
    0x56977CA9660CC7E2ULL,
    0xAC883556E467D171ULL,
    0x6D25AC164E91F117ULL,
    0xA0,
    0xAD,
    0x74,
    0x3D,
    0xB1,
    0x6D,
    0xBB,
    0x7B
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseBSalts = {
    {
        {
            0x63187878C5BBA146ULL, 0xF7AF7C1D4F6692A5ULL, 0x5B05AC155CDAF12CULL, 0xC5BF0A26BD8D5F40ULL, 
            0x93DA32FDD9200288ULL, 0x4380449E42F49930ULL, 0x45B8B90DA8FED8E6ULL, 0x139E059B26125733ULL, 
            0x81C1357B91199113ULL, 0x7CB71418873A9D53ULL, 0xE26599EB95F90AF4ULL, 0xA3B4BAA957423926ULL, 
            0x88C6981822B81ED2ULL, 0xFE0D8D7D0A392742ULL, 0x1EB6CC8E75DE40F1ULL, 0x484EA2FE5583F7F3ULL, 
            0x60EFC2CC74DB5DD7ULL, 0xCA12CCAE051804AFULL, 0x50C07D5C04728141ULL, 0x2C64930DBDD1B08EULL, 
            0xD9808259D5198FEFULL, 0xD871F4CE621146C0ULL, 0xDBEA93C4D8BC9918ULL, 0xD78BB505E139FE0DULL, 
            0x5E676A1D41D44380ULL, 0x72DB3D0248EE8637ULL, 0x54F849B2E332BFE0ULL, 0xC2C8E81373E05E95ULL, 
            0x1CBB35F782EF0174ULL, 0x05E9436AA7055A26ULL, 0xABE366B3C60D6B43ULL, 0x4836DB6A6D8FBCC6ULL
        },
        {
            0x9D9CB0F7B4E37619ULL, 0xBE2CD8BBCE68641DULL, 0x136E1214AD1B1A14ULL, 0x7E26A8C772B35DF5ULL, 
            0x6ADF43B163C5555FULL, 0x1FAF379F47826D1BULL, 0x81B78C53F1482FC6ULL, 0x5037D013D2AA8F82ULL, 
            0x98F0836D59C111B3ULL, 0x8C7589F5AE17ED4DULL, 0x7A397DF0DA82A9B3ULL, 0xE82457534B1E34C2ULL, 
            0x75AD1AFB463969D7ULL, 0xC9FE9B26F387D365ULL, 0x62480FFAD7678DDDULL, 0x2272445E4D58EEB4ULL, 
            0xB99C1854ABF77719ULL, 0x18BCF9299C2D194FULL, 0x0056686D26DE12C2ULL, 0x624DACADDE3313DEULL, 
            0x67D2BD2858D7967EULL, 0x03A5E33B22A6B6ADULL, 0xB355995A97F48608ULL, 0x11877CCB9D5B9462ULL, 
            0xCC20493B7743FEEEULL, 0xF05E3F9075B406EBULL, 0xC9D782D83CE679F0ULL, 0x20AC27F1846C7B0CULL, 
            0x443299DAB98391C3ULL, 0x58F38EAF2905F41AULL, 0x606923D1A5407AA0ULL, 0xB18BE36428840C4DULL
        },
        {
            0xB5AC2FB0CE0D83E9ULL, 0x417284122176A47FULL, 0x560CC76383B6AF0CULL, 0xED4D13131E5E9F9BULL, 
            0x8BBEDFF9126B6E15ULL, 0x246F3B8BB3EBB5A2ULL, 0x7E77060C5DBD4F60ULL, 0xE190390DDD4AF765ULL, 
            0x2C2A5B9C733C34CFULL, 0xC243E70CEC196E7FULL, 0x254544ADA68692A3ULL, 0x48D0760A4162BE32ULL, 
            0xBF1B4CF77277E6B9ULL, 0xF4F9F39E88A8D644ULL, 0xD839DEDB88CF418EULL, 0x181C2241E808CBA8ULL, 
            0xEA5E00BF1B97691BULL, 0xA76275448CED0A05ULL, 0x6A880967985D0FB1ULL, 0xA5E148DCD3ADF0FCULL, 
            0x627DAA5B42EF0F4EULL, 0x51D12E142CB4EA4CULL, 0x7C5B82E66DB10022ULL, 0xA11C7FD4183B3C9FULL, 
            0xB3EED1F99A27A4D7ULL, 0x25AFE81945F9E638ULL, 0xCE00E3EE6E7B218BULL, 0xDFD506EFEE465907ULL, 
            0x10843EDD300A1A1FULL, 0xEB09AE5671D74594ULL, 0x106683155923FEB9ULL, 0x2ABFEFF950A467C0ULL
        },
        {
            0x915D4D2A50E9DE8BULL, 0x96B7D87BF2A2FE0DULL, 0x3A58795B08577D41ULL, 0xF68225F6EC72C958ULL, 
            0x24DE787B4BD78CBAULL, 0xA3BB060D5999ACA7ULL, 0x6FEA8A078DB01912ULL, 0xF011E8B98A82743BULL, 
            0xBA5CFE6FFB3F0256ULL, 0x66D3AAFA0DC9C972ULL, 0xA87126AD2D1E6D8DULL, 0x0DC05B747622E788ULL, 
            0xB0AC2FB2D5D440C7ULL, 0x9D94947BC9081558ULL, 0x05212015247E586AULL, 0x958024D35F37A18BULL, 
            0xD87F9063DF957A31ULL, 0x190A4CF27CBFE747ULL, 0xB37968F6621C5E62ULL, 0xA42304AFC0213A36ULL, 
            0x442656E1DEAE4FE5ULL, 0x146759956AE528D5ULL, 0x28610AFC3577F5BFULL, 0x71DDCF035BA6C3D5ULL, 
            0x1B5763F1B40F7904ULL, 0xCCF88EF4E118A820ULL, 0xAF355B7B2642A9D6ULL, 0x55509EFC73F6C8D0ULL, 
            0xF36FA8CE4C037995ULL, 0xF4BA17D3F99C32A3ULL, 0xA1769E9F19CCDF38ULL, 0x7D172AE990751986ULL
        },
        {
            0x9C16990D1797575DULL, 0xC7DFDA7B916D648AULL, 0xADDFE5BFE45C5477ULL, 0x1503551CA9A57869ULL, 
            0xB3969A46F982F898ULL, 0x232DCB53EEE865C1ULL, 0xFCE44DB4B238BE1FULL, 0x06B4F14DB8CFBC6BULL, 
            0x043AAD57E78B8E73ULL, 0x5BFF25F4209234C2ULL, 0xE98ADB6FDD5F102EULL, 0x19D33F6746128F09ULL, 
            0x849AD50AE0A06868ULL, 0x75F0699172E97A6DULL, 0x6A8A9D9A94EC4540ULL, 0x2A8299003D460C99ULL, 
            0x8F03AB7C4AF79891ULL, 0x3B2D494682E903E0ULL, 0x10F90D6A779729BFULL, 0x8B09E94DB16DF6A3ULL, 
            0x133C2E3C270B2421ULL, 0x1BB98A2A716A2C5AULL, 0x7C1D1869AAF799CCULL, 0x7B2EAB77B9A22536ULL, 
            0xB1DCE6414C91468BULL, 0x9DFE4C9FE8756D34ULL, 0xF7AFE2F13649C2CEULL, 0x582AC6807C8A59E1ULL, 
            0x41E68F32738FACA0ULL, 0x962AF52DDCAAB649ULL, 0xBDC194DB5F66DAFFULL, 0xB3AEDF03BF6464F5ULL
        },
        {
            0xD085D1D2C7BB8AC5ULL, 0x67DDB7B226746905ULL, 0x1EFB2522B7A4CDBEULL, 0xAEE064EBC259B0D5ULL, 
            0x73B5A7736CA65DE2ULL, 0x57421CE9D33434D1ULL, 0x7045A9B2EAAA4509ULL, 0x97CD9CED2F1C36C9ULL, 
            0xD1E9AEBF3BD27B43ULL, 0xF7548F28724A2C3FULL, 0xB851924869BF4F67ULL, 0x1D1B160B1021A9BEULL, 
            0xCBAB3D7F8396D65EULL, 0xE6F5549F1AD280E2ULL, 0x3B225D6E7EEBF913ULL, 0xE2A994F84AD4F303ULL, 
            0x55DE0E8A7D0188EBULL, 0x59D3E3A6B20E3B3BULL, 0x571B32CF9D8F8AF5ULL, 0xBE6959EBFCF5E55AULL, 
            0x10041FE8BF6AC7DAULL, 0x06AAB1135B601C63ULL, 0x4C37AE7A543499DAULL, 0x6F55A3F59B990597ULL, 
            0x93A6163223D1E324ULL, 0x1B52972536530F2BULL, 0x5A984E0BCC1BF8EAULL, 0xD4DC7C695AA116C5ULL, 
            0xF4F3FDCE6D5A4AA9ULL, 0x1D20C810AB119067ULL, 0x8E76858FBA1BD86FULL, 0x4A7E7017185B3079ULL
        }
    },
    {
        {
            0x4D4DA2ED131C7308ULL, 0x499A7016A235BADAULL, 0x35CA849077E93092ULL, 0xBA9954C23F1AD2A3ULL, 
            0x507D6FE2BDCEEBC2ULL, 0xB7DC4FFB8B0F9351ULL, 0x599134518402CEDFULL, 0x2E06160AB433100FULL, 
            0xB4FAA6FF7E7465ACULL, 0x909BCC7B72FEBE42ULL, 0x0704C1B6EA6778A9ULL, 0x752985F8EA0A0771ULL, 
            0xF93899445B219306ULL, 0x87B6509662046DF6ULL, 0x16422E91A0267795ULL, 0xC3C67797DF2CD7DDULL, 
            0xE4B92F64F53EDFC6ULL, 0xD299E786B6485E58ULL, 0xFA088683928BCFC0ULL, 0x776F3120C6E90AB5ULL, 
            0x7C5BEDFFA7BEB2A3ULL, 0x8D16935B9CA460A6ULL, 0xE33C8B26AC353D81ULL, 0x6CDF46A7827A7428ULL, 
            0xCC733433DB67A4F5ULL, 0x4FDD3CE2D8988442ULL, 0x648BA125374A6F7CULL, 0x1BB05BB6653EDA94ULL, 
            0x44B9A1DEF37E9D40ULL, 0xAC6FCB416B1AB9B4ULL, 0x7848B65F0965E7AAULL, 0xF3D1BC160FB7374EULL
        },
        {
            0xA16D77CD9402EC48ULL, 0xFD33D05590F9395BULL, 0x5EF697C6AA11D581ULL, 0xAEB7DEA4F07B193FULL, 
            0xDCD98C279571238AULL, 0x695EC0E40F96F359ULL, 0x14BF5B8B0A3A258FULL, 0xE5C4893481AE6DDEULL, 
            0x53DB9722FD64B959ULL, 0xAC80393D3B2D52A3ULL, 0x52027F9687921D49ULL, 0x5BDF45C4E9E3D6D5ULL, 
            0x5CFE2EB27A20237DULL, 0x13F3576B46CB686DULL, 0x5EE584D2D2F0473EULL, 0xFE6B01249C84BBA7ULL, 
            0x8AA7B770935F4D71ULL, 0xA248FFE9C442F5E4ULL, 0xB7AD9E4BBF7D5F97ULL, 0xF6A9CEC09193A00AULL, 
            0x12AB9240815B8D31ULL, 0xB8B0E2E816413D00ULL, 0x58A2981046FD14C7ULL, 0xFE5B2B4CD6F00554ULL, 
            0xCC49F1F92D80F249ULL, 0xCA6FC48D5C8B694EULL, 0xD3FBC4EBC85B93FBULL, 0xFFD3E5400294309BULL, 
            0x41A9C99FFE984E9EULL, 0xF10C1958649C1989ULL, 0x471551641BD08370ULL, 0x4BB89FA5F6FD8DC5ULL
        },
        {
            0x3F4DD9933FC705EEULL, 0xFC0B448CA369B460ULL, 0x0F56ACB389EFCA4BULL, 0xEA835079E23DD0E1ULL, 
            0xCA9485EA3D5544A9ULL, 0x40CA5D9CBA7CD8D5ULL, 0xD0A77A04AAE725BAULL, 0x033A4E97D351EA31ULL, 
            0x4B7DF52200BF3397ULL, 0xF9CD34B4F8E59054ULL, 0x6D44272EC4F0C0CCULL, 0xB5D74CA92F57589FULL, 
            0x79FA291B700F5330ULL, 0xD3DC398926DE641DULL, 0xF2739261E3A0E66FULL, 0x51105E224A556E1FULL, 
            0xE18AE7740046508BULL, 0x32CBBF1E9053924DULL, 0x8E58B94AA9D6332BULL, 0xFA8AB06938E96C2FULL, 
            0xC605A82D7BB4A36CULL, 0xAA612A52A39F2FE9ULL, 0x1E5AE54D937E0629ULL, 0xB6D5C4A51B1080FCULL, 
            0x640D0F39E917FCBDULL, 0x3ED61A72D2409D22ULL, 0xD449B1CBC4BE4FA7ULL, 0xD86AF8E5E1FA4B74ULL, 
            0xC6F73A47911C485DULL, 0x99F3EBF0A78FD697ULL, 0x48711F802C58AF75ULL, 0x3A3E96D794272367ULL
        },
        {
            0x9CE81022BC17BED3ULL, 0x138CDF6E8BF66A6CULL, 0x7C61047FACA3B9EFULL, 0xB93B3193B83535D1ULL, 
            0x8F369CEEBB1F4BBCULL, 0xE254E7AE5ED2D2F5ULL, 0x8029EDC39D958C7DULL, 0x7998603E00E6B9F6ULL, 
            0xF76E7333DA419E82ULL, 0xF13C703702A678E6ULL, 0xD17DA38F02EAB862ULL, 0x77AE12024C8AF9B4ULL, 
            0xB95DCAC2D5E2449BULL, 0xC080A33F4B451FDDULL, 0x95AE8128A1E00335ULL, 0xF6B2AC1EFC028E57ULL, 
            0x87951492C3903CE2ULL, 0x989FAB0472E77245ULL, 0x61A3A78F7BFCF4F8ULL, 0xC4EF6DAE4EE62881ULL, 
            0x8C1E6B48F41B3C92ULL, 0x48E356E44BF779BDULL, 0x1623C2745007ACEDULL, 0x31E9390416523039ULL, 
            0x40EA8FB725F172EFULL, 0x3C05E4843ADC8771ULL, 0xB5E4D623AF289585ULL, 0x3595FEAE65B3EA6CULL, 
            0x2647DB72AAC30C0BULL, 0xE9224D3939FEA454ULL, 0xD2227E903EED78C1ULL, 0x577AF799E5581BA1ULL
        },
        {
            0x69E9A0B4F045E3D0ULL, 0x91A0A0AD2F602DFEULL, 0x1D3873D0841243BFULL, 0xE00DAF14D21E1458ULL, 
            0xE8F733E04B84ACDEULL, 0xDEF9B02A790C641EULL, 0x9212B9A3E4DA3F52ULL, 0x6E4029A86CC4FCA3ULL, 
            0x68604F163A3AFF16ULL, 0xBED8E6BDFB944A91ULL, 0xADA009747127DC59ULL, 0x52CAED45BE9F7BA9ULL, 
            0x1CD871284AAD3878ULL, 0xF0693B2E0111326DULL, 0xB76B723E91D61C2EULL, 0x75AF452BC43118AEULL, 
            0x3E4E4F3FCC8F44FEULL, 0x90EA7F435407A604ULL, 0x59F3E8A307149A11ULL, 0xFFE9795D59D11BEBULL, 
            0xB93FCE5D4BB40266ULL, 0x2DB28069353E34FEULL, 0x92FAC8C405FC2234ULL, 0x8ED968813CCAFBCCULL, 
            0x20F88EDD9687D12DULL, 0x97C2ABECD8B86611ULL, 0xF581C1547F89545DULL, 0xEAA3D293235CB521ULL, 
            0x8247D91039B1CD91ULL, 0x7FC90D6FF80CDED6ULL, 0x00A6DE633AB96246ULL, 0xB6A450B19B1D6887ULL
        },
        {
            0xB14AE54F21731762ULL, 0x149E1A76FDCD554BULL, 0xE37E512F3F7FE1C9ULL, 0x2BAED516AAE8BA8EULL, 
            0x55C6E77E9D709454ULL, 0x8CB0DAEA4C7BF3B7ULL, 0x7086F2F71A9363B6ULL, 0x812501B3F9484728ULL, 
            0xCBEFAB677FEE8587ULL, 0xA155AF1C604B51A1ULL, 0x866D0367469E085FULL, 0x7C0B50F9DD76F293ULL, 
            0x49CD0A563B0B0ED4ULL, 0x0EED0F042D77F6E1ULL, 0xF6B1040B735E04B8ULL, 0x18024FA839177199ULL, 
            0x37145B5B57771CCFULL, 0x538116D1FCC2C436ULL, 0x7D6949A98EFA4955ULL, 0xF08CF90FD478B26FULL, 
            0xF1137A867F20205BULL, 0x1F070FB1DF08EC16ULL, 0x227BCBBBD2782939ULL, 0x26DB1229CB9B90B6ULL, 
            0x1BC59F107602EAE6ULL, 0x1C1ABF99C8E91033ULL, 0x345A5BCD524EB203ULL, 0x40E1BD322C9C89B5ULL, 
            0x4A91156D90FD1A6CULL, 0x35949CF54882A628ULL, 0xEA4720B432EEC00DULL, 0x2276A75C9E837DE0ULL
        }
    },
    {
        {
            0x68D7109E4B522D37ULL, 0x82DE4B5E5483B491ULL, 0xD6E2948468C82259ULL, 0x23823940C4BB6436ULL, 
            0x6584C87DD3D274CFULL, 0x08C18E173FAB809BULL, 0x4B027B3BAA57C2F2ULL, 0xF5AA83F53C58FCE7ULL, 
            0x0E35C45DEB3C725DULL, 0x8918B9D4E2F3D20EULL, 0xCA19E137316B6E0EULL, 0xFF8CA5A6E7E6FECCULL, 
            0xAABED5BEA66BFF3CULL, 0x599459CF65099FB3ULL, 0x301C4B91CDB62CCBULL, 0x0B4DAC259337B620ULL, 
            0x01E696FFF0128FBEULL, 0x42DA193FB772FE9AULL, 0x77653215B5B07102ULL, 0x97AB61FEDC5F7223ULL, 
            0xFC3057745D9D8C24ULL, 0x107E0562C58717F8ULL, 0xE4C5130139840ADDULL, 0x2005BDA901E611C1ULL, 
            0x21CA911CA45BC1A4ULL, 0xA1E7FB32B313E5C0ULL, 0x3160CE351219DAD7ULL, 0x286600FFAE10EEE0ULL, 
            0xD6862459D967C45CULL, 0x1B82672F011626E2ULL, 0xA7A755583FFD5091ULL, 0xA14DA03FF94A6FA9ULL
        },
        {
            0xD2B235AF979DAFBEULL, 0x0EFAC78866640540ULL, 0x1DAEC99E8CAF1FE5ULL, 0x91A0DABC14E4FCA6ULL, 
            0x089888D85C5A589EULL, 0x33ED8A5285CBCFE9ULL, 0x24A565F77A59F0BDULL, 0xC0C86012442BD87AULL, 
            0x75C89D0682BAC5C2ULL, 0x80418AD8AC3469A0ULL, 0xE1B6169930B3A583ULL, 0x0C422DE77D6AE99EULL, 
            0xBB6368CCB0C7B9E3ULL, 0x9ED69963A5B3840CULL, 0x5D2E0A0939ABA896ULL, 0x84552A4C7D2C7BD5ULL, 
            0x2B54C5708C9E6724ULL, 0xCE58316DF89BFF95ULL, 0x4DD6CD7845B06F72ULL, 0x7AC38BB877F483E4ULL, 
            0x367DEE2AD66EB4E4ULL, 0x37FB1ABA41B3E832ULL, 0xA0BE6780D2E77469ULL, 0x16C6D5A051B8ECF5ULL, 
            0xCE688EE3C8FC0DC0ULL, 0x22FA611C42B403CDULL, 0x0FCE8552E2D294C3ULL, 0x4A5170786299F173ULL, 
            0x6834E6ECC15FD50AULL, 0x3FDF613FD8FD6506ULL, 0xF35359D505E8AFAEULL, 0x7751B9AE8F402FD9ULL
        },
        {
            0x4BF81F390A7C5051ULL, 0xF67C340803E605FAULL, 0xA8C49E07645C4652ULL, 0xE7DB33F4296A8735ULL, 
            0x2983C04DAA2A6641ULL, 0x2C4E2CAD995CA049ULL, 0xED2C008C9CF7D140ULL, 0xE44D0F6B356EB029ULL, 
            0x360AF499BA9B9ABAULL, 0xFB6D68394EED061FULL, 0x297422478BF7D2E6ULL, 0xB2DE52AB583DA0F5ULL, 
            0xFDE42B2EE70E666AULL, 0x2C74CB4EFC48D304ULL, 0x206B4FA5F3CF3279ULL, 0x4DC2DF10CDDA410CULL, 
            0x1854DDD63B933699ULL, 0x2A1E843CBC17047CULL, 0xCCA4ACF08FBC3606ULL, 0xC3A78939056746D6ULL, 
            0xB6242D3A11BBED13ULL, 0x9CB918B570AE462BULL, 0xCE650A1B5B8EC93DULL, 0x27678E598AD840C1ULL, 
            0x852BD79576D2F33AULL, 0xD2E0804139FB06D2ULL, 0x81D666834AFB8E3EULL, 0xD4FC8BC91BB612C5ULL, 
            0x22D15261FC447FD6ULL, 0x6B91FA98D42293EEULL, 0x70376C77B2DE56FBULL, 0x6138AB81DD135247ULL
        },
        {
            0x46C175B751031A6BULL, 0x6768B3F88D36D24CULL, 0x36A8BC78593D3E07ULL, 0xD2BD161B84569B10ULL, 
            0x0194101656651641ULL, 0x5DDC97399E6D4250ULL, 0x0DC844C793EFD8AAULL, 0xC694C850FDAC4DECULL, 
            0x327CD453721B221EULL, 0xD7B98E3063FB8C1BULL, 0x4D4949E79EE1EFD9ULL, 0xB154CD01813BA9D6ULL, 
            0x58C6CBDED70D737FULL, 0x9659CB2CB5FAFD62ULL, 0xECF8130265C959E4ULL, 0xFE91A2D45BD9BB09ULL, 
            0x1E33577F80F1053AULL, 0x274E062E21C1F2C3ULL, 0x1136F2A53C859F78ULL, 0xE68CDFBB15A41364ULL, 
            0x4A6E1A89490D0B46ULL, 0xD0DFD3BA19CC9B8CULL, 0x2249ADC7598B708EULL, 0xCED6998696B0A256ULL, 
            0x6F39237EE6BD6EA6ULL, 0xE40CDFBFAB9DEB5FULL, 0x1E2DDF102DA796B5ULL, 0xA1E55C650896AB78ULL, 
            0x20B027791445CB59ULL, 0x847E279780E9BC91ULL, 0xFC967F829C95E233ULL, 0x3CE064FD1D8F1B4EULL
        },
        {
            0x9F5D20F85DA6DE82ULL, 0xBA4F47D41C2A221AULL, 0x9FF3178BA7FAA35EULL, 0xEEDB4CE722E3E737ULL, 
            0x347C4E14F4BE0D01ULL, 0xB6F76F2CE243ACCFULL, 0x1A7EF27C068FB25BULL, 0x9CF76D09C5649A5DULL, 
            0xFD706A74FD1CF372ULL, 0xFA19ED872CCA1BA0ULL, 0x0AF61D717030DFFEULL, 0x9265E1CE3DDE9A55ULL, 
            0xD6C3C35133DC5D53ULL, 0x181FB77EB23D3B6BULL, 0x0A97D32A41C841E3ULL, 0x57EFC5760A778C2AULL, 
            0x148CF8F56F04B5BFULL, 0x746E6C02935AFFFCULL, 0xD48A4CA334C44F02ULL, 0xE96D67F7230A17D1ULL, 
            0xDE9A9441BDDAA225ULL, 0xBDEAB81D7E5AB4BAULL, 0xF9A5C8E8649C8C5AULL, 0xA70E7C2471DD78B7ULL, 
            0x073DA5E7BE7B1E14ULL, 0x4EE8C5E79303DBE9ULL, 0x2089B7BC66669BC1ULL, 0x6263CFE56CA96240ULL, 
            0x3BFD91432A194663ULL, 0x0C61A91CB1E77A85ULL, 0x7DED063F58E42CEBULL, 0x20C0668362DAE4BCULL
        },
        {
            0x8D7045B8B6EF86E2ULL, 0xE3A249A2C3CFBB69ULL, 0x99C5430F346A324FULL, 0xDE0DA7D23FA6F723ULL, 
            0x465504441139A3CFULL, 0x2B83B6FC31854D70ULL, 0x5F268776B529941CULL, 0xF8A5E07F2CEA3562ULL, 
            0x0C420049BDEBA70CULL, 0xCE06036CBE95BEC3ULL, 0xC68CFA0AA3AF2C1FULL, 0x371B28D161FDE2BEULL, 
            0x9A016393025363BFULL, 0xF26CE90EB56F031CULL, 0x5A4EFA816A96EE01ULL, 0x25BF84FF8FAA6C73ULL, 
            0x36BC640124B9411FULL, 0x02E026DFA409983CULL, 0xC48A473306C8C348ULL, 0x167AC505671BB0F7ULL, 
            0x25693B2EC989A990ULL, 0x14DAFB2C6B7D6D5CULL, 0xD5B3B4C220B3355BULL, 0x11673CF7056BF824ULL, 
            0xECE01745B56E2B1DULL, 0x93D2FBF14FBE01DAULL, 0x45CD217FC12CDA92ULL, 0xB5CA9ABF5FF963FEULL, 
            0x160C573CC348CB6FULL, 0xB83DFEECD56058CCULL, 0xDE32267D0823DEACULL, 0x737F35E9A652A76AULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseBConstants = {
    0x16B05C4CBAD8A830ULL,
    0x0F8CC5E9015C9C75ULL,
    0xAAC1786E43A2569AULL,
    0x16B05C4CBAD8A830ULL,
    0x0F8CC5E9015C9C75ULL,
    0xAAC1786E43A2569AULL,
    0xD425FDBBD2131343ULL,
    0x49179748AD6D9C3EULL,
    0x79,
    0x5B,
    0xF0,
    0xCF,
    0x2E,
    0xDF,
    0xE2,
    0xE5
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseCSalts = {
    {
        {
            0x58004ECE92F39F43ULL, 0x327FCCD3C17D3960ULL, 0x59D53553B7EA2FAAULL, 0xAD568B339467ABD7ULL, 
            0x0B98D51819077E5AULL, 0x2B0E69A830AC1E86ULL, 0x59ED525F3DAF3DE2ULL, 0xD28F5A28A874DDB6ULL, 
            0x3D4A343BC70DF42AULL, 0xCC0A2C208106756FULL, 0xA3E19ECF04198166ULL, 0xC5C5962B8375E9E5ULL, 
            0x5BBF973F502317E6ULL, 0x072A46E359D680D8ULL, 0x50ECFB8265D27150ULL, 0x4564B6F6D03779C8ULL, 
            0x18283CDCDDAC5540ULL, 0xBEE4AF3B21D878CCULL, 0x72CE392721B21BA4ULL, 0x7009B2F357F6E42EULL, 
            0x310CFCD7968BE680ULL, 0x241061266E0E4C8DULL, 0x753EBD7BA10A1DAAULL, 0x5843107C9BA90C5FULL, 
            0xD3CDE18B7A1626F7ULL, 0x85121303A687AB15ULL, 0xDA7546C14A8D0899ULL, 0xA81E21663E053288ULL, 
            0x23CA1F296462770FULL, 0x5BA6717F8FDEC6F3ULL, 0x3F4059BF0532DF6CULL, 0xF30EC339FC9BE835ULL
        },
        {
            0xBD82485A0B037729ULL, 0x57FC04B7425CB325ULL, 0x6E575BFC809F8D3DULL, 0x18FEEE14A8AF123EULL, 
            0x5A1A288C058B3A60ULL, 0xBCE8BADA4F0B15BDULL, 0xF13E4F6462A34A16ULL, 0x8AA79CAAAD560337ULL, 
            0xBD2AB77E162BBC8FULL, 0xF38711C47FB53281ULL, 0x290D4949FF5CB89DULL, 0x9C53A063292323CDULL, 
            0x3C001265C8703B74ULL, 0xB5CF394BC152C756ULL, 0xCFB38723DFF486F6ULL, 0x5FE57DE203DE4D4DULL, 
            0x3087181D5FCEA1B1ULL, 0x0718BDB1F702EB5BULL, 0x7816853F6C8927EEULL, 0x293F336D2AAE9D00ULL, 
            0x0B879843CE21581EULL, 0xD8CD7C4171F880DFULL, 0x272438655E313851ULL, 0x1397B014E2D5D36DULL, 
            0x47D31EADE0F549CEULL, 0xD5FACF92BCD8DDB5ULL, 0xED2068BBFF58E479ULL, 0x120D75F27047BDA3ULL, 
            0x41CFEC37CECE149BULL, 0x7B8DBD64BE036791ULL, 0xD10F3C65302FF9C6ULL, 0x986FBF8D57F94AD8ULL
        },
        {
            0xC60CCFEA143072E2ULL, 0x74B599CF7F1BB4DFULL, 0xFA4E16C534225F00ULL, 0x754375677A37F1ECULL, 
            0xBE6D955985F2231FULL, 0x7A8F5D62D29866F9ULL, 0x6B50D08BF7D79216ULL, 0x053C359A6B8FC3D0ULL, 
            0xB2FABE31489F3044ULL, 0xFCD8043E0D85A0AFULL, 0xA3D3C9BF5A507F68ULL, 0xAE8E7E2A2999DFAAULL, 
            0x2AEABBCA0017CEC1ULL, 0x60A4769E6E9C5585ULL, 0x33120874AAB0998CULL, 0xB0CDC268649EA544ULL, 
            0x3410F46937E19746ULL, 0x19D61E99D73F9E5EULL, 0xDDA6466D73DD6CD7ULL, 0x5B54208A8AA82DBFULL, 
            0x751183D0F31A71FBULL, 0xB1A75A173A6C9B0EULL, 0xD4AA38B757D68B08ULL, 0xC77A680C8FF03369ULL, 
            0x45EA37D485EAD3ABULL, 0x4F172DDEFA6D581CULL, 0xAB96EE33ED922FCDULL, 0x9A3B892C179697D7ULL, 
            0x7BA94AFE71DF121FULL, 0x88617A0CFAFFE948ULL, 0xDC1646C02487F436ULL, 0x1B4754A8D3314652ULL
        },
        {
            0x2971F7B91E114AD3ULL, 0xE9A92D015F31585BULL, 0xBE372526A0754908ULL, 0x16AECE87E272B525ULL, 
            0x3F3BC622CCE83996ULL, 0xC895FDD7E567C767ULL, 0x5C6038B5573B52A2ULL, 0x287A881CFE627F8AULL, 
            0x7C749A036DB26518ULL, 0x5424DF645045C26FULL, 0x4D240B461E367283ULL, 0x92462549A364D39CULL, 
            0xF74269FE47929DD3ULL, 0x1EFE720C901BFA44ULL, 0xEDA01014AEF6A58BULL, 0x61313F102A8145A8ULL, 
            0x93DA553C0EBEB4F1ULL, 0xFC6580031CA36120ULL, 0xEB67062412B26946ULL, 0x26C0C1E5E570701AULL, 
            0x23FCF31F92AC2AF4ULL, 0x202DAAA18E67262DULL, 0xFE22CD84CFAB5B96ULL, 0x0B18F533139F6DB5ULL, 
            0x073F63933B1141ACULL, 0xC553CAEC1D4B4E51ULL, 0x6AE7F4C281871F0DULL, 0x5DE4FA146AF5F4F6ULL, 
            0x74FC6AA2926F3476ULL, 0x81A2225D7146B7E8ULL, 0x105B976589B5751CULL, 0x916E0A200910D0B4ULL
        },
        {
            0xA8D4EAB8BF0ADD51ULL, 0xD485DB810F901EB0ULL, 0x2B009355284A2402ULL, 0x07CFA6B4BC78BF72ULL, 
            0x99E7D1854A0561ABULL, 0x18DB7BE9A1381C2FULL, 0xAE4D538B40645FA2ULL, 0x12B9D2065C9D9FA0ULL, 
            0x1CA8B6FC34999E9BULL, 0xF4A4B2E15A9E6FDEULL, 0x80E93A68CA7F978CULL, 0x7F8BCB69CFFA3CDBULL, 
            0xF74F93A93964063CULL, 0x85CAA1555472B922ULL, 0x697B1F8198ED37BFULL, 0x188C9006C15E4CCCULL, 
            0xEAA06668A84C47E6ULL, 0xEEFF75C1FA6BB682ULL, 0x251D4DC6416A7AD0ULL, 0x2C57EE50962A6713ULL, 
            0x86A860E8B676AB4DULL, 0x2B7B316514EF87ECULL, 0x07E7C869492FC759ULL, 0x2423D00D2F25BF5BULL, 
            0x2834E3170207F0CCULL, 0x44AF49BF99643F1FULL, 0x61E8D5B79EFF6748ULL, 0x63C1617C14563140ULL, 
            0xA0211BA36A3C6073ULL, 0x031719E1D910E1D7ULL, 0xE5BEB654C48B6995ULL, 0xC083398E3A31768EULL
        },
        {
            0xE190A87209648F5FULL, 0x00FA59EA1E664320ULL, 0xBE6F5F71313A2BA9ULL, 0x1DDF9226966BF673ULL, 
            0x4F586AE441F0CDF9ULL, 0xA9F3FDD81C500A9BULL, 0xBA686EB8EC354170ULL, 0xD17EB8107BFFF1CBULL, 
            0x9867676D7DC68051ULL, 0xC5DB562F7D89DD25ULL, 0xB2DDABC02551A689ULL, 0x0EDAD120E09581A5ULL, 
            0xB592D4D0AEF75B63ULL, 0x0EA5DD0084CB3688ULL, 0x859F6E08CF50223CULL, 0x73623BC3493B7DB2ULL, 
            0x2656780C4D5899EEULL, 0xEFA0C19AA94C4C56ULL, 0x8E4B1FA45D2DA2C0ULL, 0x3921AE710B309A59ULL, 
            0x583E9D420A4B1F4EULL, 0xEA3D48C67FAD4727ULL, 0xC76C69BEB57EA6C0ULL, 0x8B19A0E2E25B170CULL, 
            0x893B336877158137ULL, 0xEB5A8D3563549E78ULL, 0x9FD7FC778D51EF46ULL, 0x41076A68C5E91BB4ULL, 
            0x24C32105E617A6D4ULL, 0x0D85D224BC2D8832ULL, 0x3DDADF1A6F228FE4ULL, 0x6664D2A5F9CF0666ULL
        }
    },
    {
        {
            0x070F46728D33276CULL, 0x5F9DA1CA7DB9A036ULL, 0x1A79157FEA25664DULL, 0x03853F6B464ADC5EULL, 
            0xA73A694011057694ULL, 0x2BFBA20391CAD71CULL, 0x91E15E04FE80FE8CULL, 0x2B86348F4821197AULL, 
            0x91565473E5F5F0E0ULL, 0xAF17D0DF4D4C5A5BULL, 0x039EFADE785DDC56ULL, 0xCD1B38D9CFA14E0CULL, 
            0x337D11197A3C6F23ULL, 0xDD3A7FDF6D2C7096ULL, 0xE1684F836679A192ULL, 0x479917B8E3346339ULL, 
            0x4C3C9D88BD4288D2ULL, 0x8EF04EA20DD47B88ULL, 0x5E532310B6533E26ULL, 0x21E35CEAC2C203B9ULL, 
            0xEBE184F46FF0ED92ULL, 0xFB9120CE9DDC0507ULL, 0x1AD495CF96C28E99ULL, 0x7163E01B40410394ULL, 
            0x58BBF37C700AB94CULL, 0x0E2477C344A46ED7ULL, 0xFA384FAF678A061DULL, 0x8058FD3451010F62ULL, 
            0x4497AD5B0960B822ULL, 0x4054E5A9891BE25BULL, 0xF51A66D17AEFF0FBULL, 0x37279C3D88DAA760ULL
        },
        {
            0x3682B948C934FFDBULL, 0x4AC72303ED84BA86ULL, 0x49D52536CE93E181ULL, 0xA822E5F6BDFB5933ULL, 
            0x24B4C72C4EB2A3C4ULL, 0x395B2E622430018AULL, 0x2753DB706375C2D0ULL, 0x56012079904C9BE5ULL, 
            0x26064BDE49D4A406ULL, 0xD428ABDF4B8BCE42ULL, 0x5D923D14CE7437CDULL, 0x19F20C82D8735F42ULL, 
            0xA2F8B375BB46BCC5ULL, 0xB37ADAF9FF7D0895ULL, 0x82CBAF6D14B98349ULL, 0xCE1783A062808D54ULL, 
            0x5FAE81AEE6DD5962ULL, 0x3C3A7E07074665BEULL, 0x7984331EFF9DA39AULL, 0x41A1B242DB271112ULL, 
            0x3CF0D2DAF8A65F08ULL, 0x8F4362FEC2725400ULL, 0xE0D5B35A63264067ULL, 0x2D1CCA00989A8353ULL, 
            0x4F3EF5A38BDB9DFFULL, 0x6D895C36B7ED6EC0ULL, 0xD83EE044C885C10BULL, 0xD51535788B043FE2ULL, 
            0x79415E4CC6243AB0ULL, 0x918E6F7DC89699C5ULL, 0x731A08A2111085C0ULL, 0x8893F51C75B60DE4ULL
        },
        {
            0x34498470BEA7530CULL, 0x917EA6A92B84594EULL, 0x7DEB2FD2A483DC41ULL, 0xB38438D1A27F7161ULL, 
            0x68FAAB32C00190AFULL, 0x811A1133DAD7C5E2ULL, 0xF061F8DADFA55E8CULL, 0x2A34BB553426FA6BULL, 
            0xABC57A27F6B2CF46ULL, 0x91E210A26AF5A8E6ULL, 0xD1E204B0692A6359ULL, 0x19F9F0670CCD1633ULL, 
            0xFA2BEAE7D7B6DD9BULL, 0x19E736F3EB7D13CBULL, 0xB0A6D6FC49F3B3E0ULL, 0xB3B89632AC23BAC4ULL, 
            0xF82E273808045504ULL, 0x2EBFE708E25521FCULL, 0x64FC700E97569D7FULL, 0xEE2E048EE6774D5AULL, 
            0x82EA2A08AE5AD995ULL, 0x3C0D89F81D59450EULL, 0xBFB8E4EED7A3066AULL, 0xC013544C2CD030BEULL, 
            0x4FB5DEAF27E5D2F5ULL, 0x4050227F61223541ULL, 0xCE5041B785D5104CULL, 0x1AA94591864607DBULL, 
            0x341FDB7452DB09FDULL, 0xC9193866D8C53BB3ULL, 0x2E2B46F223E5CAF2ULL, 0xE4CA44649C863A76ULL
        },
        {
            0xFF7F76B660DF6A2CULL, 0xBF52336902D9BDA9ULL, 0x856CD6B159DD658BULL, 0x72636416A1D61701ULL, 
            0xB201F20B0C6D9054ULL, 0x6879092ECDED9F5FULL, 0x825131DD21CE733FULL, 0x90AD39591CC4BBE4ULL, 
            0x9C35E35B298BE961ULL, 0x30F82E3DCDB68553ULL, 0xE13860DE90CC3C04ULL, 0x8FE301A420E98ADEULL, 
            0xE02707EA593EE4DBULL, 0xE45E8749C7821069ULL, 0x11455AD9F4481C3BULL, 0x8AC4A9B56E4EB246ULL, 
            0x94598EC9EE024871ULL, 0xFE605A675AB8CAADULL, 0xEF109433DAFC594EULL, 0xB95995451961EBAEULL, 
            0x5AE1F399C49863C3ULL, 0xA4E24C32B8416616ULL, 0x96A08A30D9F39AF4ULL, 0x172DBBFA078DCD01ULL, 
            0x614AB52221342FBCULL, 0x9C080A558B7A6B96ULL, 0x1ABA69CB9C107C90ULL, 0x2F4A02772CA369FAULL, 
            0x40299192139C6CEAULL, 0x3FF88EA0A8B75B80ULL, 0x54E9E9864E27E0F6ULL, 0x64ABBC52B725D479ULL
        },
        {
            0x891BDF6CA45090BAULL, 0x7B95DC76BEF54B7CULL, 0x1B7369DA655CB6D6ULL, 0x14CDB2F04D35B019ULL, 
            0xB80C9FAA01E29B2FULL, 0x25E3A7CCF698C2F0ULL, 0xDC63508E0A2B5442ULL, 0x8091023BCB67FE41ULL, 
            0x20D03A70BD3FBDBCULL, 0xB3CEAEE9AE611624ULL, 0x3FDF8C75BC8EA5CDULL, 0x21EF43B057430A7BULL, 
            0xA3FB652176377248ULL, 0xE95B1F206793C5AAULL, 0xCDD0F8887869A6E1ULL, 0xD4025BFEBC1FA049ULL, 
            0x44BF1FD69BEF9824ULL, 0x15204AE26658BF11ULL, 0x79874FD3DCA07846ULL, 0x08FFBE6C5A6E77AAULL, 
            0x840F9DD4A17DB82DULL, 0x94554301614E3F7BULL, 0xE2BEABEED4F4DF2AULL, 0xDFE37AE2A7B28A3DULL, 
            0x2CC46649CA202E63ULL, 0x693477B6904006D0ULL, 0xF92250523EB4E909ULL, 0x8B008B5EC14587C8ULL, 
            0x79B425CA5673A03EULL, 0x9F6C8BE0D54599A1ULL, 0xA82E1FDE6A753B40ULL, 0xD4873D4E99215C4BULL
        },
        {
            0x912106755A9F475BULL, 0x9A3FEFCDBF49395AULL, 0x4CAECF8D26F18946ULL, 0x78343866EFE73660ULL, 
            0xB7F2D2B32BEF8EADULL, 0x590B41B277234056ULL, 0x83EF7DD74ACBEC70ULL, 0x0A312B0D05BBE875ULL, 
            0x6B0D3CDE0EF93F85ULL, 0x4DE81E7DD716BF76ULL, 0xF0247DEDCDE14D2CULL, 0x384F94A6B71464B1ULL, 
            0xC3F9B272A5DA8B08ULL, 0xF09A9C9A28A17F03ULL, 0xF60455C97716F883ULL, 0x580913016007DFF1ULL, 
            0xF2A5A039A4ED3EA3ULL, 0x3CFF5E29898300A7ULL, 0xD4E2DE227AF53747ULL, 0x4DB8DE20D718D6F5ULL, 
            0x9388EB3E9AA9F062ULL, 0x3F7842E9F819A26EULL, 0x24994FBBA449EFCFULL, 0xACF0F701C612947BULL, 
            0xA181A0D29A323E85ULL, 0x6C9E04D4AE281C70ULL, 0xF37705230F100CD5ULL, 0x4E3AE5B4D0632A5CULL, 
            0x90F892F422A75AD1ULL, 0x07F2DDE5FCE795BCULL, 0x21BD1BC5F42875C1ULL, 0x182358F76681C2EEULL
        }
    },
    {
        {
            0x8E90D5E96B71190AULL, 0x3BDB38945DD465E3ULL, 0x10C2E4512BB4F1C2ULL, 0xB50C0CF1D7D207FCULL, 
            0x4186317C1D45EBA2ULL, 0x9A7267131BAFF74EULL, 0x30DD1A4132CD0830ULL, 0x7B442A9B2B41B30EULL, 
            0x49DE2F17546F5DE9ULL, 0x52742010434D00ACULL, 0x98B959A57B590D5DULL, 0x10D43CFD3B3A96CBULL, 
            0xCCD51B34D1D750ACULL, 0x0D9644A2BEFE553DULL, 0x7D659D83B3B766EEULL, 0x71F7B7C50B41C071ULL, 
            0x55B9B01668CC91C7ULL, 0x1372E1D312FBE58CULL, 0xE6FC66C3A1A2A478ULL, 0xFECF9982FBE310D3ULL, 
            0xA4EA75023E5C8268ULL, 0x33F22CEA2CCD01A4ULL, 0xD8DC7ACB69664DF2ULL, 0x100A91705A418928ULL, 
            0x205428B88665E757ULL, 0x3FDDA92EBA4089E4ULL, 0x56E831AB46C3FFE1ULL, 0xBEC829EEA7FAA4F7ULL, 
            0x792A96BDC4015CABULL, 0x968B06B07AD3B1ADULL, 0xED4FC69883D6E579ULL, 0x1B0A59823D54E0DDULL
        },
        {
            0x50777B6388DB4148ULL, 0x68F664934F2C72C4ULL, 0x6A70A6675A707466ULL, 0x683E04D0D087EEA2ULL, 
            0x1D70490ADFE954D7ULL, 0xAE7DA6F474708107ULL, 0x18DE891BD5487F8AULL, 0x86E19196E0EA4EAFULL, 
            0x5003E555EEBA5F06ULL, 0x3C3CD0CB06BA5109ULL, 0x94DE0A530DDDD105ULL, 0xE2C3061FDCC2FE96ULL, 
            0x3215300BC6B59597ULL, 0x191FC67CC914E916ULL, 0xE0353F73779426A2ULL, 0xAE6800FE4F74D9F8ULL, 
            0xA5FD32DA97BCAC2DULL, 0x0F717FAA3F4B2C30ULL, 0xAB74BB649C8E22B3ULL, 0x2C5CE28797FF596DULL, 
            0xFB7B294D4597305DULL, 0xB3D19674D314CE27ULL, 0x65DF4516436F49D1ULL, 0x75E2DFF34B2ED42FULL, 
            0xD8DB5C0D7888ECC5ULL, 0x1532FB30F59B4D01ULL, 0xD339B8C3A92D5662ULL, 0xBACA5627B2AD64E5ULL, 
            0xE5A72F38C4880564ULL, 0xAC09C005077E505FULL, 0x61A94457B5239AEBULL, 0xBBC1D5453E4F6916ULL
        },
        {
            0xC4004DE746C74A78ULL, 0x8B7D0AA411D2C434ULL, 0x5EEE397744531E02ULL, 0x4F31C8597E939AA2ULL, 
            0xFA393D3995DCD4F6ULL, 0xAADBD907F5C4D464ULL, 0xCEFF6407D0718DC5ULL, 0x53DBEC181D1201E4ULL, 
            0xA6EDF7396F7A48DAULL, 0xDFFCB11D58D0D2BAULL, 0xB57508A997512316ULL, 0x7AA91BFD932A2E29ULL, 
            0xBF598DA771807A25ULL, 0x8B75EBF07FBB11B9ULL, 0x02E498D540857AF6ULL, 0xC2636494F2793ACCULL, 
            0x2229AA5C8EC02C5EULL, 0x1A3B615A7CE03AD2ULL, 0x35B5199B2F81A6C3ULL, 0xBB87532D4E66BFA3ULL, 
            0x8B7C667E9669A895ULL, 0x7915AF1F58A07238ULL, 0xE3FA523F9E3E30E6ULL, 0x12EDB1EF05474434ULL, 
            0x7F3451021D46F731ULL, 0xCD95C72123427FBBULL, 0xBA88664AC28733BEULL, 0x5B9846A63985FFB1ULL, 
            0x51666394A12BEF0BULL, 0x92F75B68435F652CULL, 0x54FA6448727F9FCEULL, 0x877965FBD0DB3FE3ULL
        },
        {
            0xB689B8C5FCE0DF90ULL, 0x09FFF94EB51A89DAULL, 0x3B54EF5250506B31ULL, 0x1A9BE6116BD780BBULL, 
            0x03809DB628FC9CEBULL, 0x2C2A2168A1A522C9ULL, 0xECD192C8F28E7D11ULL, 0xCB2A34881CA833A7ULL, 
            0xDC196C4C5E7C31EAULL, 0x3E12378CB9EA3920ULL, 0x4E841CC00EAFE8ACULL, 0x2D75941260297C88ULL, 
            0xE19999EB19D52805ULL, 0x9C23BE7F91A1153EULL, 0x2284D8784D3A7BE2ULL, 0x92034787779C1875ULL, 
            0xDA8F295B62782501ULL, 0x83D87AD9C629845CULL, 0x21C6FF03B992F917ULL, 0x2745B28BFD600047ULL, 
            0x4380614CB67B4C81ULL, 0x72D0867F38A6FC5FULL, 0xA5985245135ACA21ULL, 0xB5E22CE1B25C66C6ULL, 
            0xB702885A8CA05D4EULL, 0xF300962896DF4307ULL, 0x528AAC9A7A1A071FULL, 0x2A4356CFFAD6C92FULL, 
            0xC4A2D4DFB80FFB61ULL, 0x16B228281D09D55AULL, 0x1216732445792E9DULL, 0xCB0766572D329BC5ULL
        },
        {
            0x93D346C1F89FB3A4ULL, 0xEF1B5B05F5B03EE7ULL, 0x1E4EA6E047DB0438ULL, 0x0BFC666FA7D1317DULL, 
            0xF29347D4DCADEBA7ULL, 0xFDBC7BC450918D4EULL, 0x1BD39EA30AA00AADULL, 0x540DD952F53C7AD9ULL, 
            0x2101BA8397E6AFB8ULL, 0x60CA53B353FD9B80ULL, 0x8767F9C4B53E7543ULL, 0x69CF617B6779777CULL, 
            0x92BC208F1499486FULL, 0x12FBFA4FB23EBB16ULL, 0xE074769848E5659CULL, 0x8C2F8917054C0366ULL, 
            0x40B15AAB6C1946BDULL, 0x24625EA82CC8E149ULL, 0x7FD295BC351BD6B4ULL, 0x4129B5C31DCCE75FULL, 
            0xA06A42D44F0BA210ULL, 0x94F10F984C064BE9ULL, 0x70720F7060403010ULL, 0xD3E87A474228B87BULL, 
            0x6ABCAD14C3F1A8B6ULL, 0x4F999679B027A4A9ULL, 0x4ECBBF152D26B418ULL, 0x0F24A4C59F1401D8ULL, 
            0x01F8B9FC3C6B2120ULL, 0x5085E924C54A4F7CULL, 0x75CFCFC7F03A2535ULL, 0x9BC6FCE8301D4BA8ULL
        },
        {
            0xA6E4C8A23DF79D5FULL, 0x61AA839BA7833757ULL, 0x874317860CC50187ULL, 0xA667011343EE4C8EULL, 
            0xB6168A25BB75FC32ULL, 0xECAA83ED3B1F63D7ULL, 0xE001A57670667C13ULL, 0xCF44E4C2D94F3D26ULL, 
            0x2165B97F156153A0ULL, 0x77E1C52901C67408ULL, 0x9AFA5F56D758A47DULL, 0x5393B5D131F5205AULL, 
            0x7C50F73CDA1B4C08ULL, 0xCDD58818A37B7C8CULL, 0xAB6A0826493BBFCBULL, 0x22A275B8F42AB968ULL, 
            0x4737D865D0C2830AULL, 0xB4AB6FC4A7CD9A3EULL, 0x60A7C04D4B616EB4ULL, 0x0B44598D969B6752ULL, 
            0x36179FD1866CE8A7ULL, 0x448CD603D8CD90EEULL, 0x2F07FD5571216EFBULL, 0x725B78DE27DDCD4FULL, 
            0xE18802E74B95AF4EULL, 0xFCE010F81C93A753ULL, 0x59C9B6D035D33402ULL, 0xA5B0A028D830AC7CULL, 
            0x9953FB79C0C3FB87ULL, 0x11FEAA92F062644CULL, 0x3B7CDA226A257932ULL, 0x12F51A4CAF692575ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseCConstants = {
    0x5DB347C90B050F3AULL,
    0x9E5B060D13F86AC8ULL,
    0x33A0138A74564174ULL,
    0x5DB347C90B050F3AULL,
    0x9E5B060D13F86AC8ULL,
    0x33A0138A74564174ULL,
    0x0CE3F862D1682C50ULL,
    0xDD5C45251F99AD75ULL,
    0x9E,
    0xE1,
    0x19,
    0xE3,
    0xBA,
    0xD2,
    0x11,
    0xFA
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseDSalts = {
    {
        {
            0x228EF86D8ED4D9BBULL, 0x211BE60326F80219ULL, 0x2251142C101125AEULL, 0xF3A7D5F394B1A4DBULL, 
            0x057B66FA0ECA4F0AULL, 0x1C056ED5C5EFC8DFULL, 0x5FF8B1331901138CULL, 0x651CC0F4FF810843ULL, 
            0xABB3DF0ED3561F56ULL, 0xAFE0679370A16ED2ULL, 0x950D06FB4454444AULL, 0xED66C03FDA350E93ULL, 
            0x42CA0096BF8FCC9FULL, 0x706CEBA21D66AA58ULL, 0xBF77353DA24A9C50ULL, 0xB15A950A02EFA6A5ULL, 
            0xB55BBBB84C036411ULL, 0xE4D4188789DCA0C8ULL, 0x99369677806202CFULL, 0x8564537C0D357FBCULL, 
            0x12702A9C852F8321ULL, 0x28CAF0A7811FE458ULL, 0xFCB3ADA77113BD28ULL, 0xF629803A5D9BBDFAULL, 
            0xD6E414971857BE07ULL, 0x9D464E69E845ABB4ULL, 0x7E2B0783491C7432ULL, 0x2A04B5669416E355ULL, 
            0xA0BCF7B7905759C4ULL, 0xB7539B42197E8F49ULL, 0x39E55032A7638E0CULL, 0x46013FC0447EF743ULL
        },
        {
            0x2837397514F8ADB8ULL, 0x361C82ADA9B13393ULL, 0x0303EC67FD8C4851ULL, 0xA7B0FCD73BEA7272ULL, 
            0x84A910A3619865B3ULL, 0x4D269129B3F4ECA7ULL, 0x5A0ACE3A789A2440ULL, 0xAA32A1C04D90C83AULL, 
            0x9E0BB4E0785D67E3ULL, 0x67B3061F6905548AULL, 0xA2EB527C7BE65E62ULL, 0x5C7BD3E5AB8C8B2AULL, 
            0x3DE3EA98EB6A2326ULL, 0xE018A486DAA75FA9ULL, 0x3961FE929F7D2CBDULL, 0xFA47D0A78A4FC9B6ULL, 
            0xB243720DF4358616ULL, 0x57638D5D689612C6ULL, 0x648B4EF4C2A47D64ULL, 0xBF415980E2155EB0ULL, 
            0xDE5204214481D199ULL, 0x44DFD16DC493F4C4ULL, 0xDC7147F617B3E6D3ULL, 0x634343FF037699A9ULL, 
            0xE285AD293575EB2EULL, 0x57E071816A5C8281ULL, 0x9CB5D674CCE0F1F2ULL, 0x2CCC4C1785788376ULL, 
            0x3DC49710398DF3B3ULL, 0x0B12EE69044D06EDULL, 0x903297D5BAFCBADBULL, 0xD6F458152684394BULL
        },
        {
            0xDEC7B61220B5305EULL, 0xD5DA961987DD32A9ULL, 0xE3A13866A9BD22FCULL, 0x9E71CC38A7940BA9ULL, 
            0x76CE02A9438E5501ULL, 0xE335A0525B4723A9ULL, 0x2724683E24053121ULL, 0x4F336453646554DFULL, 
            0x44CD39E716AF0A63ULL, 0xFF9589812A2A7CA7ULL, 0x2FA4356F6C7B22B0ULL, 0x3819FE825C832151ULL, 
            0x70372F8031F07C92ULL, 0x25D6CF1C8AD138DCULL, 0x87BD5145455427E7ULL, 0xE17E5BD06772C2D7ULL, 
            0x0F397C39C85BC86BULL, 0xAE44348DF6CB4259ULL, 0xA4648F3EFE5DB882ULL, 0x9C44D18D031F436EULL, 
            0x8DDED9A0D0735F5FULL, 0x8A3F1432B68EA215ULL, 0xF4A4AFB94B831461ULL, 0xA3D308334E4A30E8ULL, 
            0x74E39A6A61E35ACDULL, 0x9EB98893CD57487AULL, 0x6AE9BCCD9E502A1BULL, 0x8B030802160CD20BULL, 
            0xD90090A76E3105A4ULL, 0x479FD1CD0B7489A6ULL, 0x4E2C653041C5A916ULL, 0xBEC625179AF744CCULL
        },
        {
            0x41E81ACEBA26A76EULL, 0x6A8E2CBBB370F8F2ULL, 0x9BBF8C273AE12D01ULL, 0x7B1BFE16C1DF0D1FULL, 
            0xA8D9EA50A4BB5BE5ULL, 0xDC798BA0A269AC23ULL, 0xB73FB7EDABD40425ULL, 0x9BD5DB5BE0700B70ULL, 
            0xCBE72F6A28475534ULL, 0x5E523477378AD5A1ULL, 0xD5C7EA5F3AFED699ULL, 0x7D80E65095DA1B85ULL, 
            0x1C6332DE3949F75FULL, 0x7AB791AB4564C01EULL, 0xDBD2C8D24EDF138BULL, 0xFC5918898A23B314ULL, 
            0xCFD7F8C47BBBF0A3ULL, 0x7753EC5450DA56CCULL, 0x70326EE7C3DEF3FCULL, 0xA7A66C0B6492CE5BULL, 
            0x28560080FBF2E5ADULL, 0x3CA83468AB018EB7ULL, 0x8BC6069A34FD011DULL, 0x22CA5F098B65B0F0ULL, 
            0xA3356031E9D82750ULL, 0x215382A94FD3FDF2ULL, 0xA6B171E648085256ULL, 0x66D8B4BA9F309655ULL, 
            0x6A63EBE443B1A386ULL, 0xE1108598ACBFE839ULL, 0xEDB3CBC944005EABULL, 0x25DC050B1418363CULL
        },
        {
            0xB390521125AF0A1FULL, 0xC401D1AA2DD91B81ULL, 0x8D9D6269EF4DB4A9ULL, 0xF427D219B9DB5C68ULL, 
            0x0D4716CACA77AEDFULL, 0x383BB4606EF3A986ULL, 0xB69D1FFC6A631D26ULL, 0x90327BAE694D6106ULL, 
            0xB91AD48E2FB8DCDAULL, 0x32B6F0CAFF1724ABULL, 0x7B4575FCF81F016CULL, 0x46D32BBB8908CDDCULL, 
            0x403DD547026E5917ULL, 0xAEE29D718009718DULL, 0x4B95783364D0830DULL, 0x091149D9D4B5BF32ULL, 
            0x43777957E3121E36ULL, 0x5C235923E1DE7225ULL, 0x233E9C1AFE27FD6DULL, 0x33F1E6FC2251BA02ULL, 
            0x973F8CBB09C65790ULL, 0x8D804D4B821B9321ULL, 0x4D6732C7C2A3A5F1ULL, 0x4C9DAB66F062889BULL, 
            0xDC51EEE1CAE968F3ULL, 0x907DAA290CD1CECCULL, 0x283C6F1018423F1DULL, 0x7E9969B4226465ADULL, 
            0x4D35C67E476095B4ULL, 0xBC4ABA3DAB90AAB4ULL, 0x95A35874BE3CEF9EULL, 0x1856B519D89C1DAAULL
        },
        {
            0x050589A626B6170EULL, 0xB396E80DE2D5DF2AULL, 0x2BD7EE12446E3B72ULL, 0x9CC109629A80A846ULL, 
            0x1CC7BB2317A10796ULL, 0xA28173DD0EE718EFULL, 0xF31DE94D430BB62DULL, 0xC46E5A9F7B745976ULL, 
            0x42AD34233603313FULL, 0x11A0327F0C8088FEULL, 0xF74568D52462BC7DULL, 0xE21FCCB9011BCFB5ULL, 
            0xE72E595E1D45F878ULL, 0xCC1A3D4F9EAAE7F9ULL, 0xAFE05E78232413A7ULL, 0x975D3F127FFB1CADULL, 
            0x2AAA4A9F13DCFCD6ULL, 0xB032E144ED669448ULL, 0xDF6E6AB01BF678D8ULL, 0x5458CB4B13CFDCD9ULL, 
            0xA535EB7197701AA4ULL, 0x6455083C0A6B694CULL, 0x2D533D63BE0F4E42ULL, 0xF47937EB44BFA2E4ULL, 
            0x3BB2AF64F683510EULL, 0x44EC90A33708B9ADULL, 0x018278C52EC4C9B3ULL, 0xA89E2794B6F2FE87ULL, 
            0xAE04775BEB2DE112ULL, 0x8F626524262112FDULL, 0xF083BA7032053502ULL, 0x2CF54A73DA43A1C5ULL
        }
    },
    {
        {
            0xF8E1020F1067CD2AULL, 0x112650BBD782CFDBULL, 0x00AA7E1010707F1AULL, 0x396D6A35D5FAEE7BULL, 
            0x5C9810211A36D8F7ULL, 0x3FC2EB955F4F890EULL, 0x832CFB1BC5D545BEULL, 0x897BD6E9326FB61EULL, 
            0x2597688ADA2C4FD8ULL, 0x63014AF3BD4F29D6ULL, 0x8CD82123954EDF4AULL, 0xA4EB8099BE833ACAULL, 
            0x33C2C0B0E3059091ULL, 0x3F0B091047FAE492ULL, 0x49ABFD77B2B67417ULL, 0xE3C2A0D18DF7028CULL, 
            0x8763E03C52A6AC76ULL, 0xC3A696EF0EA82823ULL, 0x41F2566BBF322F9CULL, 0x06985AE4D9535D89ULL, 
            0x66F346EB15D127FAULL, 0xD4FCD7E58A095A5BULL, 0x2ABBA947F8E155FCULL, 0x9F9E2B201FCABB8FULL, 
            0x5D64BAFDD6E0B752ULL, 0xB2A7A7D86CCD4EA8ULL, 0x6A1160D7E57ADCF8ULL, 0x88157431DAB652B9ULL, 
            0xDE9A8F99DDBC8122ULL, 0xDFD5D08B3B1EC93CULL, 0x7AD728DED1B0583CULL, 0x27B885B4A6E66EF6ULL
        },
        {
            0x9C7C8CFF8FE8C83FULL, 0xBB0B043D91DE1886ULL, 0x975FC7BCE846D506ULL, 0x2A72A1C1DF565AC2ULL, 
            0x19D884A50EB967E8ULL, 0x30E2CBDA9F8E9133ULL, 0x4A2B7ED5070986F9ULL, 0x77B2568F6EBE8463ULL, 
            0x8CD08AF61058E52DULL, 0xEB74143F08854162ULL, 0x0A43C88CAF72EA63ULL, 0x6431FB03911766D8ULL, 
            0x4AABBF54FD1D4ACFULL, 0x28319B377862D4DEULL, 0x9CCC63B5049C1F10ULL, 0x5F754F5247F7211AULL, 
            0x1641104D6DA4165CULL, 0x739AB99DC953D573ULL, 0xCB055A59EE37FFB3ULL, 0xB2DE4A9D30C8EDF3ULL, 
            0xBDB37A1B7371BFA4ULL, 0x3BB50FDECCB1D63CULL, 0x9682CE3C17431DA5ULL, 0xBB34231FBDF2B063ULL, 
            0x52484FB93A53F615ULL, 0x2A6930375968811AULL, 0xA295DF79779D0D37ULL, 0x3ED674E45408BBBCULL, 
            0x7B56A92572A4B427ULL, 0xEBA1CC8E94416726ULL, 0xB85BC260855BDD74ULL, 0x829E55FF38D824A7ULL
        },
        {
            0xA7C802AA994329CCULL, 0x1672BA13C39F5928ULL, 0x4BA9F6D487C198DEULL, 0x864041FAF1D33C5BULL, 
            0x6DDF66C24AD573A2ULL, 0x656DDD11BA87D078ULL, 0xD66903607DA37FD2ULL, 0xD67C47794E3F7941ULL, 
            0x531304B0C30762A6ULL, 0x9586E0F251B32960ULL, 0xB3C05FDF590E37FFULL, 0x510701FD6B4ED209ULL, 
            0x1C3FFAF8ACAA1F05ULL, 0x09CBBF879A1D6D6DULL, 0x933AF99E7FB314B6ULL, 0xCF56C71DD0C30DD7ULL, 
            0x19B6BFE44C52A01EULL, 0xE87B5DF84F9064A2ULL, 0x2C5A734C661C924CULL, 0xBD02F1A05FA7D5ADULL, 
            0xCB60BBF00B032133ULL, 0x5568B81EEFA11AA4ULL, 0xDE69F5727F5DC871ULL, 0x94E76B617BBB7416ULL, 
            0x6F59FFA3EB80E5AAULL, 0x3451957ED95C324FULL, 0xE58078529CF603CCULL, 0x629C7C184B31407DULL, 
            0xCCF945363D0280BDULL, 0x982C69D238F74C59ULL, 0x9F929CE1478E0915ULL, 0xC6DE9448D9301163ULL
        },
        {
            0x6F80F7470A3D2F78ULL, 0x0BE942AC158873E1ULL, 0x6EF0E066D3B23BCFULL, 0x26CEDC1C7C1821C1ULL, 
            0x3C71A7954E84BA47ULL, 0x38FB6BBD626CC491ULL, 0x78FA12F0BCF7661DULL, 0xDCAA80088D8DAC09ULL, 
            0x0C070B4BAB87239AULL, 0xD2F90258404F446BULL, 0x1A5DF92817A104B1ULL, 0xE30BC02107523AAEULL, 
            0x6DD8D0D4BFB4D035ULL, 0x1257CC64C052AB2BULL, 0x08659EACC2A3AAC7ULL, 0x75C51B14CF52A7A9ULL, 
            0x112D2626F94A1B22ULL, 0xE32B127EACF4701AULL, 0x20F34576FADB2BDDULL, 0xA3B7433D46F002AEULL, 
            0x57894FBCF9D6221DULL, 0x042CD41D4104EE56ULL, 0xE3A1BFB7816B00C1ULL, 0xC7271E46682C3F9DULL, 
            0x2CAAA26524474548ULL, 0x68D7CB8DDAA17F38ULL, 0x81CC8298B19DA7F0ULL, 0xB1AB26A7F08BA4A4ULL, 
            0xA2277431117F1431ULL, 0x1FAD82D6AF15847AULL, 0x9804EDFE32430719ULL, 0x7F6D05F8E3405EBEULL
        },
        {
            0xC90D7A453FFEDD2CULL, 0xDBA8B19F050CA113ULL, 0x0D4C8E75FE071A20ULL, 0x92E35AB1DE4A6A1BULL, 
            0xF975F7B6F5F68FE8ULL, 0x31B2F981C2255E38ULL, 0x46D6718ABBD33136ULL, 0x3AEC18E8C97C5223ULL, 
            0x3C21EA7CB318B48AULL, 0x2396871552195F04ULL, 0xC492174667C39C44ULL, 0xE34E023F64C5C499ULL, 
            0x245595E433EBC2BEULL, 0xFCBCF454A2674D60ULL, 0x5ADE1E606C4906A8ULL, 0xB2A7B0BE0D10850BULL, 
            0x64DA1801ED152471ULL, 0xA0D796CFA44F747BULL, 0x4C3C8999FA3E5CDBULL, 0x63B8694F399579ABULL, 
            0x921F962084FB1FFEULL, 0xF46BF67BDD852D4BULL, 0x4AEAA8D9EE0B191CULL, 0xBF6511F3DCB69A2FULL, 
            0xDB24E8FA373BF2BCULL, 0x3C8BBC529C64A334ULL, 0x125F57C32B98052AULL, 0x07792113AFDCF8FDULL, 
            0xE387EEF74E7A7DD7ULL, 0xAF232B5392620555ULL, 0x9E3D155AD1B90EE6ULL, 0x9D0889511BB93A2CULL
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
            0x2CE4D33AE04E93EBULL, 0x860066A686FB874AULL, 0x288D09BD4ACA6375ULL, 0xAA2F21EE3349EB5BULL, 
            0x35C69D5B35EA788BULL, 0x38F365E3A18AFF80ULL, 0x4663046E888725E1ULL, 0xA4130277234C4075ULL, 
            0x7926C27698A12E82ULL, 0x38CF060667E2B28FULL, 0xBEC05C35B0AF276EULL, 0x8EC0B4F7344A2762ULL, 
            0x4015E49D6CD02FF8ULL, 0xFABDCB0BAC19BA33ULL, 0x42D91ADBF6D49663ULL, 0xBECB0B1220F89BB6ULL, 
            0x9EFC466D15B894F9ULL, 0x700D4C1161900707ULL, 0xC5BF98FB197D7A7FULL, 0x8AD7303FCA0E15FDULL, 
            0xAD1D650BE7E898DAULL, 0x7678AC2C36627F4DULL, 0x7232A795F8351EABULL, 0x46A14BFB2AFBCD44ULL, 
            0x7D90BAE5ABA34DEAULL, 0x60B1D4AB639F8843ULL, 0x4216104EC5EB28F4ULL, 0xDE99C53F25CAB9BEULL, 
            0x37DB9FB874DA59AFULL, 0x7E214D0EA4220122ULL, 0x6A472B06D525E37BULL, 0xE7F315A620E0B474ULL
        },
        {
            0x94A742D38D372006ULL, 0x400AE3DEA358CF3BULL, 0x6FEF2459319E0CDAULL, 0x66BA542D99CB1AA9ULL, 
            0xE24EA7FB5CD48348ULL, 0x0F1486A383D74B9EULL, 0x52FB79DF26A7AB41ULL, 0xDD93C5165ED1A1BFULL, 
            0x0C4BF3DA0FFDFFDCULL, 0x700D217BF13E91EEULL, 0x8CAB56CC0C1CCE44ULL, 0xF1B5E7DBECA3FC39ULL, 
            0xE9F18810D675A6E2ULL, 0x0B1B282A7F985553ULL, 0xCAEAE4E36BD54445ULL, 0x09EFABC8A3B2CE75ULL, 
            0x79C438C9BB0BB469ULL, 0xEAB34B23C7968203ULL, 0x4D83513F00D29465ULL, 0x27C7BCB9F8DD37DAULL, 
            0xCE5A5DF0E068A633ULL, 0x2075F2F04CFF4E24ULL, 0xE3A597C628BFA730ULL, 0x2094596E72EDC487ULL, 
            0xF47B6441A7989C9AULL, 0x68EFF8C5E0831F16ULL, 0xEDF8CF5FDA3F967BULL, 0xEDC95434A9343182ULL, 
            0xC520CF6571A041DCULL, 0x7B210AA2E9223B6DULL, 0x6AC14B4EA779A661ULL, 0x5758E1B2B630CB33ULL
        },
        {
            0x2ACA1688CEA4B201ULL, 0xC54BD219D5F83FD9ULL, 0xE05E706A537F8AF4ULL, 0x1997F9086D9C4759ULL, 
            0x1682A0109FC3B2DEULL, 0x1AD45370A529E076ULL, 0x2EEA025966AA1B87ULL, 0xE60298DA57EFC67BULL, 
            0x6BD6AF923513F913ULL, 0x7584E604BEB6A92EULL, 0x6FF980654DC4A7CCULL, 0x4AC44E142534FB77ULL, 
            0x778A89ECEEB5C27EULL, 0x1E9C4EDB0BB9643AULL, 0x4E04C277F7DC9F62ULL, 0x23DC526E4AC8BE15ULL, 
            0xAF12DC3D23E599FCULL, 0x8B5CF9A2A990EDD7ULL, 0x37BABF036D0CC47AULL, 0xF45C79583C6BEC99ULL, 
            0x85C6380573AC7D04ULL, 0xBDF3D95C765E3357ULL, 0x46D325D4BE16DCC1ULL, 0x936DCBF7BEF93A04ULL, 
            0xB7C9FD0E8BA58E19ULL, 0x122CEE524E13D94FULL, 0xE7F67C6E90D473CAULL, 0xBD5C02253DAC4D4AULL, 
            0xCA6E5E857E0843CFULL, 0x31C191EA06F1EE11ULL, 0xBCCFF7DE88056F59ULL, 0x1A20D7A67C9E3F40ULL
        },
        {
            0x63FC1DB79492B5A6ULL, 0x1B77E6467F2B043FULL, 0x4053DDCFC6749919ULL, 0x1979E9B28F366DD8ULL, 
            0x5470EDEAC4EC5A49ULL, 0x977CFE655C35E211ULL, 0xEBA6EAA550CBFDCAULL, 0x128BA0B7AF6EE9FBULL, 
            0x87B96EEA11C0749BULL, 0x24BE347D8E4BA782ULL, 0xD4700681D0D87052ULL, 0x3423A3AFDBE92621ULL, 
            0xF8FDF29C88FC7C51ULL, 0xA727C0CC54B0780EULL, 0x2F4B4C3D83929B4FULL, 0xE6F8F03F4FD90FDFULL, 
            0xC45C4903C4168164ULL, 0xC673AE8A4448AC08ULL, 0xD5869385D6D5058DULL, 0x81CC96E625CE0E5EULL, 
            0x1961EF9A3B79E810ULL, 0x848D0FC82A95FDC8ULL, 0xA67EA8FEB9AAAE59ULL, 0xC7FB8EAE63BF0B22ULL, 
            0xA8A2800263DEA971ULL, 0xFF3261BB6072D523ULL, 0xFCC74B8BD0B34127ULL, 0xC9EC4A6CC963BB2AULL, 
            0x67B25ED1A60CF018ULL, 0xF02A10D9B744B867ULL, 0x0B551DD76DECC589ULL, 0x4A2D5692283304E2ULL
        },
        {
            0x57995475F1B3731CULL, 0x35B31791A480DE8AULL, 0xFB871CE3B9666CB2ULL, 0xA71C76EC6E7F43CDULL, 
            0x91B4E08F71005E2FULL, 0xE0F502D5CE750D90ULL, 0x0337F3CC9B12EEFCULL, 0x68413D2587B06019ULL, 
            0x68A283C9AAF552E5ULL, 0xA655F886F15BB7CCULL, 0x040875AD2782B3DBULL, 0x9DC470A1D5CE8C40ULL, 
            0xB296D0ADF0FBBE87ULL, 0xD86352512A7BB237ULL, 0x5659A8A0DB09D0A2ULL, 0xB10590D8A73A1AF9ULL, 
            0x05452A95B8EA5C42ULL, 0xB7C0A4A8F62428C2ULL, 0xA779F9DE85263D6AULL, 0x7EC409D93B41A91AULL, 
            0xE0A88D7A51B2347BULL, 0x3344DEB3565F7B0EULL, 0xD7AD96598CCCF18EULL, 0x11FBF9E03C0748CFULL, 
            0x1B1A1E569453099AULL, 0x0ABDA9FEA221600DULL, 0x45D17B05CC252087ULL, 0x484D6DCE88847DC3ULL, 
            0xC88E7FDDEECDE908ULL, 0xA064AFDCFE61125CULL, 0x8AF1D1AB0898E04FULL, 0x38E03304C87CC341ULL
        },
        {
            0xBA1776DDC6E0A378ULL, 0x56488CD318E41761ULL, 0xB834FA1DAFE13E14ULL, 0xC02498D58C7E146CULL, 
            0x10D6FAA614008149ULL, 0x22F9CBBBEB0EB16CULL, 0x58DA2EC8E4047EC9ULL, 0x7ED51DEC412BFF30ULL, 
            0x48DCF119D68C07B9ULL, 0xE93DD8B648FAF265ULL, 0x1FA86D4F088938C3ULL, 0x875CBE5A5C3A23FBULL, 
            0x146C5D6E8FE29DEEULL, 0x3F95AE4F97E54A02ULL, 0xE55D23A7849F8CEAULL, 0xDCC28EBC4D84C1B6ULL, 
            0x5683D199EE849F87ULL, 0x0652074C3FAD6BACULL, 0xA0B70955CFC82C84ULL, 0x05AF90620A9F5E33ULL, 
            0xDBD41EFA5BC8B0E3ULL, 0x00227A40F302E79AULL, 0x1C5A8EE63746AD45ULL, 0xEFF906807043A17BULL, 
            0xF63FFF344A13609DULL, 0x4AED77C59D1DEDE9ULL, 0x70B083D7CC921237ULL, 0x60F83456DA2734AAULL, 
            0x02CF9282A019D48AULL, 0xF31E5822F349D7F6ULL, 0x549A18A0F57661B2ULL, 0x5774D42F98751358ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseDConstants = {
    0xFA63B81A147B7392ULL,
    0x21FE15A9026D86EAULL,
    0x80A8891FA244A92CULL,
    0xFA63B81A147B7392ULL,
    0x21FE15A9026D86EAULL,
    0x80A8891FA244A92CULL,
    0x7329FDE58065D76FULL,
    0xF1CA7890697F8183ULL,
    0x07,
    0xFE,
    0xE7,
    0xAD,
    0x6A,
    0xC0,
    0x8C,
    0xED
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseESalts = {
    {
        {
            0xD371C183F6C28BD8ULL, 0x0E9D1E806D291730ULL, 0x4A375F8921D6A48DULL, 0xA1E594680C332B25ULL, 
            0xD8AAA0FE9CF422F2ULL, 0x01164928211535F0ULL, 0xAAFFA3799019369CULL, 0x8931CF18C2DFD155ULL, 
            0xAAEDAFF67EA5F3F7ULL, 0x0C79C88206784FB6ULL, 0x8C775B6022718273ULL, 0x0899B0CB4CF8333AULL, 
            0x8ED6054AF8486150ULL, 0x8DCF45A560544BF3ULL, 0xDD857D62F8ADF788ULL, 0x5DEB6AA1CB7D3F3CULL, 
            0xF0AED11434BEA75EULL, 0x2869B4D3F8722FBCULL, 0x7414E0E869734D6CULL, 0x9BBCD33D05E19665ULL, 
            0x863EFAE9419962FAULL, 0x200234069CF4C544ULL, 0x0584C8CA9F71E77BULL, 0x98B510E10D920692ULL, 
            0x6E5F34E7E7867CE7ULL, 0x27E9ADFEA647420BULL, 0x3BA9D5868DE7DA6EULL, 0xF90D584897075944ULL, 
            0x89C4A31EB43BB1ACULL, 0xB11BF958B5ED2640ULL, 0x38B97F37ACCD4A1DULL, 0xE9345FEE7082B08EULL
        },
        {
            0xB0324C6633D0AFB0ULL, 0xAA9641835CE67417ULL, 0xB0537953B7BD00D5ULL, 0xC2977BBC2E6182D2ULL, 
            0xE8022720681F1165ULL, 0x3418520EE193F45FULL, 0x841C367A0190F293ULL, 0xC13A7574AEC09F63ULL, 
            0x58AB39E58CDED154ULL, 0xD44A8399DB6174E4ULL, 0xB2C654140E24AAA9ULL, 0x1D3F0EE38A831590ULL, 
            0x2A50BDB08D9ED060ULL, 0xBEF1C7D73B68BD25ULL, 0xED9ECC56B84F3585ULL, 0x8A26BCB49C849D1BULL, 
            0xD050F69A323F683CULL, 0x756E8A7CCE1B5DB1ULL, 0x92827E1B1B5234C2ULL, 0xB15CC342EB81450EULL, 
            0x7D6713CC506989D9ULL, 0x121614049D7C97B7ULL, 0x13E84020DACED731ULL, 0xE138BFB0371B8D38ULL, 
            0x9892082B5DDEC50CULL, 0x59533CA743D0CBE2ULL, 0xA9DAC9A3AADA6DF0ULL, 0x0835625261C5FA3BULL, 
            0x5E20AE3E339C9D70ULL, 0x2773E9A69D47ADD5ULL, 0x906173218BEA6C29ULL, 0x29F094E8D8F3377FULL
        },
        {
            0x8CF2A8F72B091489ULL, 0x06C166B41729CC98ULL, 0xDE0382B9C9DAD872ULL, 0xE1EC02D5D67085B9ULL, 
            0xDAE2B1FFADC7971AULL, 0x07776031D0010B37ULL, 0xE585966269395FD8ULL, 0x4F46B04623920027ULL, 
            0x38391AB56568D7B3ULL, 0x269E6AB332D69285ULL, 0x238DF067D391777AULL, 0xC8AB00EEEFDE4C4EULL, 
            0xACBD86E45CC6F7A2ULL, 0x385EB4E5040DF3F3ULL, 0x120194FEF5992661ULL, 0x9460E797659B8C90ULL, 
            0x854303C4B696154AULL, 0x37638FDE80B07FC0ULL, 0xE72017C81030BAC7ULL, 0x23CF20B55522E818ULL, 
            0x45B1C7570F94BF37ULL, 0xBCBDEE72F58B8CE9ULL, 0x3C4EDB5600E2ACDAULL, 0x5CC7842B8B4FE097ULL, 
            0x1D24E81F0EE2EE15ULL, 0x4848DFE984C4C0AEULL, 0x4648E0B234339973ULL, 0x78788EE5641BF5F7ULL, 
            0x8D0F068FA1897C2BULL, 0x30781F9EE104C6C3ULL, 0xA593589EC92C0DCFULL, 0xE9D4E3C731A63669ULL
        },
        {
            0xEB21495C6F1721B6ULL, 0x92CE68FD89BF76F1ULL, 0x0FF273247D7727A6ULL, 0x33815C57A14F04B7ULL, 
            0x930499A1EF849022ULL, 0x44C4EA77A694A174ULL, 0x3C752EB7BAE2F71AULL, 0xB40C577FE2191A03ULL, 
            0x3E669CB0A8087CB0ULL, 0x72CF357E70B8B39EULL, 0x24E2666F6168EE93ULL, 0x88253567191F39A2ULL, 
            0xFF77D9947739A165ULL, 0x581E22678B7BC6BBULL, 0x0DE528470FBE7E63ULL, 0x332279AAC95CD018ULL, 
            0xD172EEAD9A26FE5BULL, 0xB927B43B7AB54D0FULL, 0x853BC5752027AB4DULL, 0x6CB1D7BB7281E032ULL, 
            0xEABF9CBDDB90D1E3ULL, 0xC24C9397660D1577ULL, 0xA3795AD05868376FULL, 0x98843DF06152A1B7ULL, 
            0x2264155516A8D122ULL, 0x84051D35F5EF5433ULL, 0x6944A5F269C9DE72ULL, 0x0619ED11827B0C0EULL, 
            0x62BEC1CAE810EBC3ULL, 0xD33FC283482025C4ULL, 0x1A4973F30ADDBEF9ULL, 0xCE4191DEF1E48D17ULL
        },
        {
            0xB754DCBB59E3A6E7ULL, 0x4412AC75B0E2FEF3ULL, 0x3638E9B08E51473EULL, 0x541F99D3F47CEB5BULL, 
            0x9FF7022FD93690F4ULL, 0xD915A4155583B972ULL, 0x55F09ADBCD331C84ULL, 0x4A92BEB8D9B77A4DULL, 
            0xA9381CEF9FD56877ULL, 0xB7FF4BD6EC5239C0ULL, 0x36566779EFBE80BEULL, 0xBF4DE5032F68BD39ULL, 
            0x0D01099002CC80E1ULL, 0x76EA545DBF86D968ULL, 0x283E5C346C6E0CC4ULL, 0x3126E140D60BBF99ULL, 
            0xC44BBDC713B711D2ULL, 0xCFEFD514B875ABFEULL, 0x23DFCD5CD7B57EC3ULL, 0xC0BC5EC1613DD6F7ULL, 
            0xA007435DB18F7BDBULL, 0x3A3B3DD9224124ABULL, 0x4B8CD2D7B34BA331ULL, 0xD163AE12E95D8742ULL, 
            0xDA723A7ECEBCD68FULL, 0x65D4E63972E2481CULL, 0x09524B9F6CA22A95ULL, 0x80D39D7B859ED442ULL, 
            0x46E20CFAA5512728ULL, 0x55A5F4FECCC60792ULL, 0xB24DE8207223170EULL, 0xEB2832FA93BCF854ULL
        },
        {
            0xF7BAAE1F0CA2EF9EULL, 0xC95D4F045BBE2F95ULL, 0x32F45A6FD5FAC1E6ULL, 0x9BC8B9B7015898EDULL, 
            0xA46894A23E790569ULL, 0xE50BACAABE456128ULL, 0x6EC23CA2FC413344ULL, 0xB0C73B133CF32CB5ULL, 
            0x89E5068C81A92A60ULL, 0xBE11847EFD403B63ULL, 0xEFD9B2F5185BF682ULL, 0x93CEC29FB8DD8630ULL, 
            0x2F8D8EE7658A5F1AULL, 0xE1682B132BE8E2D6ULL, 0x45934733530929FAULL, 0xD055255DEC549F97ULL, 
            0x96DE5855054FA836ULL, 0xA526A4718DBA0D42ULL, 0x2EDA1DA49161563AULL, 0x51EFD7C179DA234AULL, 
            0xA7B6EEA9A06E5940ULL, 0xA5840F3FE97CA14BULL, 0x078F9EB8241539C4ULL, 0x5E77FA8DC1A0AC43ULL, 
            0x3D5C2D13608F93D8ULL, 0x8CAA142AC4850251ULL, 0x5824DF280DEB511EULL, 0x43DEB365F8A49BC4ULL, 
            0x0731B8C72580A08BULL, 0x8389643D27F12094ULL, 0x31CDE89DF83A17C1ULL, 0xC2AFF32F458AA82EULL
        }
    },
    {
        {
            0x614F83F6CAA6ADFDULL, 0x26033271D2EA2EE4ULL, 0x0E06C4ACDA2FE81AULL, 0x90A41CE5C4E05898ULL, 
            0xCFD0DD9867D9E1A4ULL, 0xCBD8AD75FEC1626FULL, 0x1C23FD93E89647B0ULL, 0x34D8E813E8C2FF27ULL, 
            0xA6A4A78F71D29E3FULL, 0xD14B3974AC12F49CULL, 0x915FF3C284D168FAULL, 0xF82D850382F1ED24ULL, 
            0x624664B00DE26026ULL, 0xB1F9CFB3AB85C454ULL, 0xDC6E191A7E5BA04CULL, 0xC5F5B79271D0D131ULL, 
            0x97E3B419106F4890ULL, 0xCAA257046CB1BA8DULL, 0xD0D4F0EF974BAE57ULL, 0x191C7408C4E86D7CULL, 
            0xED47C1AD3ECB6F86ULL, 0x8CECBFAC0649B746ULL, 0x1D9BEB314625C2A6ULL, 0xBFF3F2391E85DD3DULL, 
            0xD34784CAFDBC94F9ULL, 0x9866642F3060C73EULL, 0x5D37E2FDBEFE0B11ULL, 0xB6B8AD5E84CF5B68ULL, 
            0xB1D951B46A09D459ULL, 0xBE270DCB8B86C492ULL, 0x6238961E5CDC0C5AULL, 0x4864BB84C9B29051ULL
        },
        {
            0x55E41AF310C31A84ULL, 0xF930489E9C05AF1FULL, 0x013ECCBC8D38420EULL, 0x00E2F17DE7909C26ULL, 
            0xE683D83E7B6B0879ULL, 0xA0C2AF0C642B0900ULL, 0xDE0B8905553F40B8ULL, 0x51A9A33629C70404ULL, 
            0x58A85AC35BD17B3EULL, 0x872FE8FE4672F6D3ULL, 0xF4687DE56E261178ULL, 0x134C9E767A801344ULL, 
            0x231D0260E979CA0EULL, 0x06C71367313E8F3FULL, 0x3C687236DA2FF812ULL, 0xE899FC147A7306E6ULL, 
            0x0A2C52C612FC6DBDULL, 0xD28CAC8BCAD04C71ULL, 0x876FF0921C19D77AULL, 0x9B933B426FDE4DD3ULL, 
            0x771B48ACC1BD0FCBULL, 0x3B647E20B07E848EULL, 0x9239E8B1D5EE0FA7ULL, 0x8167D61CFDF16BA5ULL, 
            0x61A13DA1D5182B4BULL, 0x4D166F33FE2F933AULL, 0x3E7CDFEB4E97DA46ULL, 0x94FFFC073B6C0F8CULL, 
            0x140A75C2C0811DE0ULL, 0xCD5BA73E15DC9D8CULL, 0xF6C8E56D915C78C0ULL, 0xCC78F284FC70439EULL
        },
        {
            0x2720D9FDEFE81FF7ULL, 0x459EA79B429AF151ULL, 0x5A17A2CF9011171FULL, 0x7CEB90509B6CE8BBULL, 
            0xE2176B5DACBD2CEAULL, 0x31361D20C2BEB639ULL, 0xAADBB9FCF0C03A45ULL, 0x4DFA3D4FFF7B421EULL, 
            0x8381ACC653CD105BULL, 0xECD308B8D246BCEAULL, 0x499A81D6B773B617ULL, 0x44B5885EAF106557ULL, 
            0x10EA2F9C9102D83BULL, 0x982C0FB2CEDC9DE4ULL, 0xA79FD659AFBFFD85ULL, 0xF2AACB339E84BCCFULL, 
            0x2AEB1AE4F4DF8D2DULL, 0x8EE8D7D08BBCB6C6ULL, 0xA63FA21C5CFD585BULL, 0xA7073CA961F79B2EULL, 
            0x028D5F46039BBF58ULL, 0x0166FE4D64A62DD9ULL, 0x50D3AA08A1E389E4ULL, 0x008DF0332CE6FB2EULL, 
            0x3C26DB08A67AC501ULL, 0xD1EA668F92672AEEULL, 0x78C2DE3A1F6C3B72ULL, 0x09B25D6C69C2E6D6ULL, 
            0xE13731BF72902C77ULL, 0x9ED4332A98731707ULL, 0x3A35BCE50FDF8E50ULL, 0xF1D4064B186EAF30ULL
        },
        {
            0x5B9148B4D5B9910CULL, 0x9A3E6653D3137DE3ULL, 0xE0B418183660B4A6ULL, 0x7CA4336081ADEE00ULL, 
            0x2EA7E0D93D754AD2ULL, 0x7BCC4CA27E2E74B4ULL, 0x4E8160BEEC1615D8ULL, 0xAFDD09624990FE96ULL, 
            0xC3D27DC25312936DULL, 0xBE53367888B222F8ULL, 0x794716EAC6956FEFULL, 0x58576B45F7A070C4ULL, 
            0x7A5CF0156C10C44BULL, 0xCB64C9BDFC0CB5B2ULL, 0x02A7D65747085D6CULL, 0x5E2FDF31C7122E3CULL, 
            0x010443229AECAB92ULL, 0x0DABF1E81FA42E69ULL, 0xDCD85CD1A8F04394ULL, 0x1DC180E595282B98ULL, 
            0xD6FBA9CB7A67800BULL, 0xCD7A5B35B1E60C13ULL, 0x380C33C36A2662E7ULL, 0xD4925638CE52AF2BULL, 
            0xAAB62F17C6FF903AULL, 0x48DDD34EB1DFCA2DULL, 0x26B9C4BC01286BDBULL, 0xB0E89E1954E10B4CULL, 
            0x4570DAEA1D3D6F77ULL, 0x7CF622E66E32FF4CULL, 0x0814EBD8F446BE57ULL, 0x877C84DC9FA3AF4FULL
        },
        {
            0x419FDA7984230E21ULL, 0x05EE71A1CD2D3CE0ULL, 0xA86A28A3C995956CULL, 0xC8C27226EFEFB45CULL, 
            0x74CD732BE939170EULL, 0x65F7A19CFA785CD0ULL, 0xFEEE98D3D457F139ULL, 0x732F925A2FDE67D3ULL, 
            0xD8FE3CEDE64E5557ULL, 0x66CDAFA10375E78CULL, 0x93B5805F63B15852ULL, 0x21460A2B1D308892ULL, 
            0xB7E975C066D7E6F0ULL, 0xE1EF88B7E3B1E75BULL, 0xE8CED7F439783E27ULL, 0x3D209CA599FE0B86ULL, 
            0xD7DB791C506405F6ULL, 0x09F7A353D0527517ULL, 0x6E70B240454CC3C3ULL, 0x27356E5AD7960FBEULL, 
            0x416F46AF61E65026ULL, 0x29DF7C95E1D2DE39ULL, 0x17A897FC96EA0383ULL, 0xAB33BDA2650BB2E9ULL, 
            0xA7CCEA038B31D49FULL, 0xF932043C9037AED3ULL, 0x84AE17F85AC02F7CULL, 0x8C3B8893406F31B5ULL, 
            0xFD5782213DF202FFULL, 0x53D7787727090403ULL, 0x7C537102A9C7D8E1ULL, 0xB93491BF5AAB4AD6ULL
        },
        {
            0x82BBA20CD6326B77ULL, 0xAA18E730F255B65AULL, 0x6FC4C8E1D496596CULL, 0x4C8FDEA2DEAA61A0ULL, 
            0x450B4DA9FA4A3FDBULL, 0x822696975069CA7BULL, 0xF2D3608CBE033B4FULL, 0x742113733845CB43ULL, 
            0xA39A06929E554CB5ULL, 0xD7AFC500E46871A3ULL, 0xD9A795192FC30073ULL, 0xC328B6BEF6647788ULL, 
            0xBC187307990355DBULL, 0xAC66C05D13A0587EULL, 0x11A6889C77141469ULL, 0xCC4713B06EFCAB97ULL, 
            0x0E800F0B968BD2D8ULL, 0xE844F1F1F31600C6ULL, 0x0E7B96CC3571AAFFULL, 0x98FADBD72AB95D4DULL, 
            0x1A2E1B201901AF3BULL, 0xA51AA5A37B7980FCULL, 0x52F1B9563ED8EA6DULL, 0xF4C849483D5977F2ULL, 
            0xDAC7AFF178930252ULL, 0x039B080651158853ULL, 0xB137028D63969A27ULL, 0x85924E3AD5FE9E88ULL, 
            0x8FD04ADDABDAE301ULL, 0xCF70026CCBDEEDD7ULL, 0x2DD17CD27BDDF3BAULL, 0x77C7BD3C159C72EFULL
        }
    },
    {
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
            0x504F745D632DB30BULL, 0x65E538D3D16AA558ULL, 0x6440424598CE66D7ULL, 0xA4D2AE506864B322ULL, 
            0xB1463F445C88ECE6ULL, 0x7FCE9B69104021E6ULL, 0x03CD95B9FACF7FE9ULL, 0xE326425D73C83D38ULL, 
            0x9B42F74162C24442ULL, 0x812ABEEA890730BEULL, 0xED99A9F260165123ULL, 0x6507B9ACB754D2ACULL, 
            0xC234F593016A9A82ULL, 0x3F895A9EBD0B376CULL, 0x71BFA81BD6DD6328ULL, 0x61FBC209C91842CEULL, 
            0xC46077B46BCF0996ULL, 0xD6804155ECAFC854ULL, 0xBB90D101E41AF3F8ULL, 0xF6CFB0A91C5CB234ULL, 
            0xE02381C840B21F37ULL, 0xABD94ED4D67F9E80ULL, 0x2EA00873A34BF590ULL, 0xE5985578486AF9A8ULL, 
            0x213FD988A312734EULL, 0x9F31228DACB4D54AULL, 0x5DC26B649AC5A05AULL, 0xA3137B374A9D5826ULL, 
            0x958992AC69022EDDULL, 0x365CB249584B6F37ULL, 0x1605F950C939186AULL, 0x0C7953BD06FCBD9DULL
        },
        {
            0xC3CA61AD2F5C02CBULL, 0x7C2C4E348FC3D7AAULL, 0x70B2A5954808048EULL, 0x8A072419A4021048ULL, 
            0x2CA85F4B8EEB041EULL, 0x13E0D0DB228F0AC9ULL, 0xF1BC3A3CBE0DD5C2ULL, 0xFFE4096E976375E3ULL, 
            0xD0242613EF4BE314ULL, 0x58F186BC62B1742DULL, 0x6243F3815B1F1978ULL, 0xC6894E52A3D8F84CULL, 
            0x24606CEF5D89B0A0ULL, 0x3E954D64F023136AULL, 0x6F08F20CBA6D650EULL, 0xAF74434D5CD867ECULL, 
            0x4D15F15697B6756BULL, 0xE67EBDF794448FEEULL, 0xCBED29AC5FE10897ULL, 0x518ABEED74AE5F18ULL, 
            0x4707B4434DCD4BBBULL, 0x2F3E154405E1B27AULL, 0xC059C3650867313FULL, 0xD08F5BB4ABC5871EULL, 
            0xEAC6D1431EBA3471ULL, 0xD843961765BDE287ULL, 0x14547280CC0C57C0ULL, 0x98490B5425432B4DULL, 
            0xDC952BE4D918EE17ULL, 0x8C4A434537FA92CDULL, 0xE0634EE96B97C330ULL, 0x05A839780420ED80ULL
        },
        {
            0xDAA7DF17E97D5579ULL, 0x384A3C90C77A41FCULL, 0x7DDB8BCD363A303AULL, 0x6B1D8F9A6C82079CULL, 
            0x9E03B206CE685012ULL, 0x0E6AED2D9FB0209BULL, 0x8A10CE329C16EE13ULL, 0xF74C6431167008D3ULL, 
            0xCE88607E2E266567ULL, 0xF071B8F8E81FCBEDULL, 0x3DFD01B44EB809E2ULL, 0xAD18A32A7246FAADULL, 
            0xBE2CAFCE3B02ED35ULL, 0x5AAA501EBFFDBE3DULL, 0x7B4C7FE6AD46F595ULL, 0xA248AA00FFE03FE1ULL, 
            0xAE452446313DEAE0ULL, 0x160F342603245638ULL, 0x9B25F4304008B0D3ULL, 0xF1B58CAC0C8170F9ULL, 
            0x30248ACEDA34B3ABULL, 0xAFC5E6650768314BULL, 0x26C34DA84027AA80ULL, 0xD5C340533CFECB61ULL, 
            0x5738D54EF658F47DULL, 0x95CAB1305696DE3DULL, 0xA99DD2D443E8FAFEULL, 0x29477207AD1AF3B6ULL, 
            0xA5C832F66D8F8D82ULL, 0x4C1A2AFDCD00D5DCULL, 0x0557E7F81DD34D9DULL, 0x2FDEAA60AA17EFBBULL
        },
        {
            0xAFA0CDB19C3F838EULL, 0x0E9BB6FECB47EBADULL, 0xA9774C18DDA9D58BULL, 0xCB6D102D8A725219ULL, 
            0x811C03B5A107EC28ULL, 0x1B7EF912CF053D9BULL, 0x4DC56CAD1C0ACA49ULL, 0x9CE89B2ECDBF4603ULL, 
            0xBB934F08AD5B79A3ULL, 0x53DD516FD64DC844ULL, 0xA42A9EA841341467ULL, 0xB16386E1ED91B6ABULL, 
            0xDF5A8CD852368C16ULL, 0x2EAC7E23B36CBA65ULL, 0xE6E58FA57ED5B08FULL, 0x455227E8636D1E9FULL, 
            0xCA146DA2F3EB0520ULL, 0x7279E6ED4BC2CD9AULL, 0xD05695E1BA61018EULL, 0x0B49F1F46F46A29EULL, 
            0x51938A891C699D78ULL, 0x80DCE93C060BB8A0ULL, 0x3F1F906A8E1A31F2ULL, 0x4F17FC27A5457BDAULL, 
            0x2D2D7358A1C93A34ULL, 0xBD2981967E4915A8ULL, 0x1F9CFC2FE76DC3E5ULL, 0x05B214479EC18DFFULL, 
            0x230A8DC449478EF8ULL, 0x682B7F6E4CEB06BBULL, 0x17EF00B7AA30E96FULL, 0x02F53B139DC4B9B4ULL
        },
        {
            0x34A52BE874C36848ULL, 0x65E627F532F3E7DEULL, 0x05956263A34A6DECULL, 0x513E4A15FA201DFAULL, 
            0x638BDB74B9B3EC17ULL, 0xEC8EFDF36027AA65ULL, 0xE839600526C0D0C8ULL, 0xCDC3124B07B4F4B8ULL, 
            0x266FB727E346B50AULL, 0x4929A0171E988133ULL, 0x9A93B58703D7B27FULL, 0x31E032ED7537316BULL, 
            0x6BB697DAD0892AF5ULL, 0xBE7A7C54FC75A9CBULL, 0xC97B0358AC644535ULL, 0x3B0C1FAF64002A70ULL, 
            0x80BB1628017E2C19ULL, 0xF1DAF6FB473201B4ULL, 0x0E438C6812C5027CULL, 0xCD7154A88C87225EULL, 
            0x470B4B6A7C59ABD8ULL, 0x7C3A63DD829F8A7AULL, 0xADFC5BA0E0DB1C40ULL, 0xF832B971792C41ECULL, 
            0x4D24E50873FE0424ULL, 0x5FD1A94A9A455F8AULL, 0x38D27547C54048A1ULL, 0xB5FC968666DBF018ULL, 
            0x3ACDE6E912D625D8ULL, 0x6B942030A6AD08F1ULL, 0xF3034B556A591DE3ULL, 0x51E6EE946F7E0C22ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseEConstants = {
    0xF513ACE71F6B4635ULL,
    0x0448E95EFAFCFD50ULL,
    0x612DCAA4180C97C3ULL,
    0xF513ACE71F6B4635ULL,
    0x0448E95EFAFCFD50ULL,
    0x612DCAA4180C97C3ULL,
    0x3FB025A80E37F5F1ULL,
    0xB5ED4EB251404D40ULL,
    0x86,
    0xAB,
    0x9F,
    0xF1,
    0xE4,
    0xF7,
    0x99,
    0xA1
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseFSalts = {
    {
        {
            0x65FB38A0926E5A2EULL, 0x83D45A8908D52DFDULL, 0x00864743B117686BULL, 0xB34C23B60DEF7F52ULL, 
            0x6C9E420568C0C9B3ULL, 0x31C09A528CFBC716ULL, 0x4E5CB00B237568DDULL, 0x3E9BAA44D57D1F81ULL, 
            0xCEEF8FB7135B8525ULL, 0xB179B2F7015D8133ULL, 0xC52EDE750FA5731CULL, 0x328990051BD23336ULL, 
            0x0F47EFCC4899F73EULL, 0xA9590F0302ECEACCULL, 0xB95B19AD38D289EDULL, 0xE88E3B8B5ED48B5FULL, 
            0x0BBDB69DF339FADDULL, 0x1FAAAD681AEAD6A2ULL, 0x885B67F635E13AAFULL, 0x6547B92B708B9C73ULL, 
            0x144C58F377E2A251ULL, 0xFF8BC4237E6C049BULL, 0x4F28FBE50C2E874CULL, 0x3D11A83B5B2C7DB3ULL, 
            0x5D3B800F391FEEA0ULL, 0x102B5198D57D3E4EULL, 0x8458A80BF54ADEDDULL, 0x0EFA897A53172B06ULL, 
            0x91DC2FF6A8031D90ULL, 0xA70C03EF3DB49711ULL, 0x126DC85DDC47C5A5ULL, 0x909954FF3D8C68BEULL
        },
        {
            0xA3A5B479FB94002CULL, 0xCB10F89E523460B4ULL, 0xE1842C14B1E5F3F9ULL, 0x65E346F8A102DF90ULL, 
            0x9E55A081B4F9B87AULL, 0x2D25C8127C992505ULL, 0x2B7D24E262227A25ULL, 0xA355B92E0E6CEDBFULL, 
            0x28AE7212E79223FEULL, 0x55B615C2B0800371ULL, 0x32B5BDEC429026F8ULL, 0x109E41F42A47AB02ULL, 
            0xD171AA4BA15C8087ULL, 0x43E0EB912CCC749DULL, 0x8C673F9F310EA784ULL, 0x82B2B4F1BDF9B4A4ULL, 
            0x093075421EE48AAFULL, 0xFEC4624212DA26D4ULL, 0x74AE23BB6BF383F9ULL, 0x3B2C5F1BE52388EAULL, 
            0x01AAE6DF932982BFULL, 0x56ECB96F52431573ULL, 0x754221CF86AA2A8EULL, 0xD8814758DC32D8DBULL, 
            0x015FD20B1154FED0ULL, 0xEF22CDC0A5D8B99FULL, 0x8827C1446EDB9D9AULL, 0x6119D0FC6DCAE474ULL, 
            0x328FDA9697197790ULL, 0xE3A101B3FAE93CE8ULL, 0x6DC423846C7DCA73ULL, 0x7CAD9FD146565194ULL
        },
        {
            0x31F683926A9FCA9EULL, 0x9A61C69EC3D72A49ULL, 0x3F70B288EFC2C04DULL, 0x62F393B6AA87F424ULL, 
            0x749BC5C1A7AABFFEULL, 0x567095DC032DFDBAULL, 0xAE90362C9A9C6961ULL, 0x6A01440B0038D904ULL, 
            0x8E23DB8EF32B8180ULL, 0x002734F742109A8BULL, 0xB137607B750C44BBULL, 0x5E68E7CF23EC07B4ULL, 
            0xD39490227A90CC26ULL, 0x802328CCB167E740ULL, 0xC39D6B8900F493E6ULL, 0x17551B7398412269ULL, 
            0x9331BCCFDAB0606BULL, 0x420BE2CF720BEE4AULL, 0x4D96E7A0F154A88EULL, 0x4032040E89B48F26ULL, 
            0x4D70A211E9163985ULL, 0x114FF03E014B6A2AULL, 0xC4C963DD26827B54ULL, 0x86539EF824C7068FULL, 
            0x7807A201C95FF011ULL, 0xCCFCCC877BCC555AULL, 0xFEEECAD9A4575DC0ULL, 0xC325A8AB86A621ADULL, 
            0x3EB75972C29A02ABULL, 0x8B9FB7830F2D613EULL, 0x4599C271C5A21282ULL, 0x98A81141B138E42BULL
        },
        {
            0xEAC133A4B181A75AULL, 0x58CD66ADE3DB6D8EULL, 0xA321E701694D3D66ULL, 0x64A344EF0B3FDA81ULL, 
            0x51C5F27E90017A45ULL, 0xBAC5A7400741AB4CULL, 0x34D08A878D9EF922ULL, 0xC1B0B5575D75A4BDULL, 
            0xECE814DA27963F73ULL, 0xFF254C5495BC81D8ULL, 0xE141227397D0BC2CULL, 0x549B78DB9E1A4C1FULL, 
            0x8AAAFE9F81F8E605ULL, 0x9DB396E9130A928EULL, 0xA3BF1C8DDBD7D577ULL, 0xFB2D2E3DCC71F029ULL, 
            0x71D45ABD2011121CULL, 0xC2FF17A5750544A2ULL, 0xE21FE969B4F8B5A1ULL, 0xAF3CB05332D02E24ULL, 
            0x3F69642A8CDA3A1BULL, 0xA8173ACF6B5100A6ULL, 0x0DDD43D6CA69B5DBULL, 0xE0ECA0BAEB27E84AULL, 
            0x522D97176AC5A653ULL, 0x6B86E2BB694BE570ULL, 0x1CC738E3C66E4A5CULL, 0x1B136D49120F3592ULL, 
            0x949E742EB1DD8935ULL, 0xA582BC490C52CE1FULL, 0x94FFA13FA148209DULL, 0xF8A5CF2E90DA033BULL
        },
        {
            0x476D5D46A5A80C61ULL, 0x0E7D5E5A46E8481EULL, 0x8BEFF345547BCDFBULL, 0x5916C44F395B0548ULL, 
            0x186CCE4B4ED23C9AULL, 0x19FCC5B94B54537FULL, 0x4CD574329954F3D2ULL, 0x20D7E89B1151861DULL, 
            0x85AE5C17055F6D1CULL, 0xEF7D9C9ACBF04C35ULL, 0xE625A3A2D8B78FF9ULL, 0x2983D79440C8703EULL, 
            0x5A7761F37540AB47ULL, 0x5A3745072B703FA3ULL, 0xB963FC4B0198C545ULL, 0xAB5191322FF6010AULL, 
            0x6AC78F51283FE3C2ULL, 0x398DF129B1BDDF27ULL, 0x795F8CE7D38C08BCULL, 0x898305E368B575D7ULL, 
            0x08290D7F81007298ULL, 0xDA6A2A2272922D53ULL, 0xC466F0808AD2CC2FULL, 0x23584ED1E453DA3CULL, 
            0x585BE9DF057BD851ULL, 0xE28979A9AE4DBB4FULL, 0xD196646AE475C967ULL, 0x0B0B42D51737CE44ULL, 
            0x4F1628B4F79362A8ULL, 0x713F63FA2B67F935ULL, 0x275877349992289DULL, 0x4AB3E2E88577ABEBULL
        },
        {
            0x6DAE21F8DA41C8D4ULL, 0x4A007A6F53E06F53ULL, 0xA59F89783895ACC5ULL, 0x4218CF907F49DD86ULL, 
            0x44EBCDFD77C10663ULL, 0x95DF881AAB2982FBULL, 0xE164336E0D66C8B2ULL, 0xF362C8BED19ECEF4ULL, 
            0xE7EA38192256D736ULL, 0xA927A39BCD3BA2DAULL, 0x2074B8E9440F58D9ULL, 0x1E31A098BD7913B8ULL, 
            0x754F5E402685C9CFULL, 0x7F2993BB9B4DF4B4ULL, 0xAC6FFEBB48A5A4ECULL, 0xE47A11FE99AB11FEULL, 
            0xA426B7971CF40F9EULL, 0x59EA75603B8E8536ULL, 0xE27E2083D3A63783ULL, 0xCC68C88C77F99CADULL, 
            0x5345B033C5546AD4ULL, 0x88F6429E3D37F72DULL, 0xA4EC8D4BC9B7600DULL, 0x7AE30B8823A0C424ULL, 
            0xF6D2DE18633874ABULL, 0x4676C7813C6E1ABFULL, 0xD735728F707771B8ULL, 0xCC93B9D5F28CB043ULL, 
            0x4D865BF752570322ULL, 0x85DBD251D4C4FAE4ULL, 0x118C8FA5DDB59272ULL, 0x225E1EEF75FFE7B3ULL
        }
    },
    {
        {
            0xD2CAE0F2C35144C4ULL, 0x1634CA7D481A9A6EULL, 0xE191CD9C5553A7AFULL, 0x698C9EEB0615BE1CULL, 
            0x2546060EFC0B6961ULL, 0xA0AB61FEACEEF5FCULL, 0x82064DCCB91D5F3EULL, 0xBEDCD82D63CCBAD2ULL, 
            0xA63099C5A3ACFD9FULL, 0x00221A3EDD102A9EULL, 0x19E56DD98EE6AD41ULL, 0xE93CE81E0C3C6A0FULL, 
            0x5B71F17026E26922ULL, 0xB5F2649430EB23D6ULL, 0xCE75C1DAD11AB15FULL, 0x6CCB485FFD414DEDULL, 
            0x2F3FAA01421F8DE9ULL, 0x7AC08A618CB7100AULL, 0x4AD1E1B763587E9DULL, 0xE2954C3967198ECEULL, 
            0xA71CA8093E170F40ULL, 0xDD5685F1414C2180ULL, 0xD7C8FA08A76E2C11ULL, 0x116B83BE95B6F4D8ULL, 
            0xC5784F37696CC8C9ULL, 0xBDD7BE7FAA4E9151ULL, 0x3FB4747B6AF47D54ULL, 0xE8D2C51D80EC9452ULL, 
            0x025BAED0A64B477EULL, 0x186AA178DD66D21BULL, 0xFF7545244BED30AAULL, 0x65B9B3B7A26C692FULL
        },
        {
            0xDE26B32F94BFC852ULL, 0xDA247467370FEC0DULL, 0x18271446139170C8ULL, 0xB2934048F2B25576ULL, 
            0xD183D929227E8273ULL, 0xD4A00C8DB03159A2ULL, 0x33429850AFC06D98ULL, 0x3C09FD6E93F0BC2CULL, 
            0x351D31E571B80CEAULL, 0xAEAF853465E7CA7DULL, 0x17A40BFF60B0D6B5ULL, 0x795FBAB72AFFFF5FULL, 
            0x6362FBE001160497ULL, 0x776387362114B736ULL, 0x431341DB91AE2B2DULL, 0x05991CD7552368FEULL, 
            0x7C396DA8CE88220EULL, 0x0E322DE81DC664C5ULL, 0xCFF1EC20397CD239ULL, 0xD3544C784832B356ULL, 
            0x0EBD48E6E5EE2BD5ULL, 0x1DAA149C19B16AF5ULL, 0xCA05CA80E14D5FDAULL, 0xAD8A708854604E68ULL, 
            0xBFEB388F7BC96DC9ULL, 0x96FF65B896C80C71ULL, 0x5E76141696A500A5ULL, 0xD23FF117D5DAE028ULL, 
            0xF05FD4BDB5CED723ULL, 0xE8DA693EE90EC7B5ULL, 0xF4236C231DC23123ULL, 0xD1140F44BA46E2C1ULL
        },
        {
            0x668130BB24B1363DULL, 0x440EFBCE1AEADCF5ULL, 0xFAEA5E0E9D9EB833ULL, 0x8DBC66DB86FB1D48ULL, 
            0x51070BA1B7AE111FULL, 0x0970F4B17998E16AULL, 0xC82197D7F336954FULL, 0x17DD4A33F7652C9CULL, 
            0xBACB50E88441448DULL, 0x9903231A4AFC49F0ULL, 0x2D476A2889217A59ULL, 0x39B7223DC0307FECULL, 
            0x8723C89E406CDF0AULL, 0x447B62B6C54E0049ULL, 0x15C6F6AA3B41A49CULL, 0x65687ED678560CF2ULL, 
            0x6E78F2ECE2159674ULL, 0x529C19F3BCFBF9ECULL, 0x1636A7923FBA8E88ULL, 0xAC51161DA340E872ULL, 
            0xB675517B1FEA443DULL, 0x674AD81AB7A84B42ULL, 0x538F35938488A2B2ULL, 0x74FF0F1677529F3FULL, 
            0x7A6AE0B81F7787AEULL, 0x5C4D4FC54CE019B8ULL, 0x0445B5DDC406DD75ULL, 0xD7E54346C5682740ULL, 
            0x84D6D71DEE3D3AFCULL, 0x6AAAD9ABAD4B9CE2ULL, 0x52AD4515EE551464ULL, 0x05EB6B7967CD8F19ULL
        },
        {
            0x47720C1B01D199ACULL, 0xDB2A5E4D335A97C1ULL, 0x5C8FB7421CA4B543ULL, 0x23CB6DF7A2F58A2DULL, 
            0x8A257F336ADF1A89ULL, 0x0FC1360CF58347CEULL, 0x1DF554C18FB2252EULL, 0xA74FCD9058465501ULL, 
            0x915FE54D009361C4ULL, 0x66A7C08E7963E40DULL, 0xF2A946939BC4B0ECULL, 0xA8DA1FE22094BBAEULL, 
            0xCF859BBFC453AB78ULL, 0x04C996E3EE4C8A2EULL, 0x5A255F105A1D3FB3ULL, 0x08FD6F981B499020ULL, 
            0x44CBDC1F55A09A55ULL, 0x4E44A26FFD54AB51ULL, 0x33E51FDF874F0110ULL, 0x9AAD3093391E0FFFULL, 
            0x27C9A6977F052F61ULL, 0x1F2EA35A4D840335ULL, 0x2B95B65699244D46ULL, 0x26BCE02A3163B7A3ULL, 
            0xB8D96E6E00671549ULL, 0x78A6B868597E4879ULL, 0x9AB8289B844EEE42ULL, 0x648BF6CEE430AE4EULL, 
            0x0C3439C82BD81061ULL, 0x62B3F6501D585653ULL, 0x94823DC757CD7E91ULL, 0xDC81AA46E0C41EE6ULL
        },
        {
            0xBFF0B607E91EE656ULL, 0x8319A31D4FC17D79ULL, 0x6A03DE578E911678ULL, 0x88F73B116676A93AULL, 
            0x2CB40BDF9514C889ULL, 0x007750D9A96FC6A4ULL, 0x9EDDF1132A304A82ULL, 0x6D08E4377727C3BEULL, 
            0x8E12F7DB69A29ED3ULL, 0xDAECB4F795998F36ULL, 0xFE2F298DF62EE367ULL, 0xFD20796E5F07A441ULL, 
            0x7DDE05E4D60597C5ULL, 0x90F30E9C98C17CC3ULL, 0x249041F32996CC9FULL, 0xF6C2E0C34D5FA166ULL, 
            0x51D6635B8805538AULL, 0x82B6218636DB497DULL, 0x435660E26099A191ULL, 0x21E27182ED7FFC13ULL, 
            0x963046406903F82FULL, 0x4A53C8EC73F368F3ULL, 0xFE97EEF97CEF3906ULL, 0xB49277B58B05FD35ULL, 
            0xC1B6F7270EE1424CULL, 0x3530BEC9E742D641ULL, 0xF97949F6FCCFEFD9ULL, 0xD6DDD9300DAC333CULL, 
            0x23D4B4CEA1BF1C6AULL, 0x2204941F3F071912ULL, 0x55D176150CF47DE0ULL, 0x494522FA673842BEULL
        },
        {
            0xF152CDC695A4429FULL, 0xFE5081D2F3EE51A9ULL, 0xB9D3493D6B5A4E2FULL, 0xF7606B426936133CULL, 
            0x5EC291E7A050A7FEULL, 0x80839F33F7B81593ULL, 0xC8A9EAB303D5BAF2ULL, 0xEB975B1F56E7177CULL, 
            0x62A220BEBD957896ULL, 0xE17CE928CD75F9BCULL, 0xBA9D8196EC60E869ULL, 0x253CDED38305E987ULL, 
            0xC43A57F77244A5ADULL, 0xE83EF4DBFAEDE06EULL, 0xFC5C917CED877934ULL, 0x38D4A95401993805ULL, 
            0x754AD18D748F1FD1ULL, 0x1FB19E6132F00271ULL, 0x5C5F642A6CF8EC1DULL, 0x214C01D201CC8D39ULL, 
            0xD62A3CCF141310D0ULL, 0x66662DE1571D590DULL, 0xC0BEEE681AAD3E20ULL, 0x20C1BE67A6E249E3ULL, 
            0xD04BE58216DD01CDULL, 0x146759EEE3347F0DULL, 0x82A2D5F47F8DF9CFULL, 0x639E577E3EA97B01ULL, 
            0x1E3584AEB59C2D9FULL, 0x8C51EF71BCADB24BULL, 0xD0845582E9097B60ULL, 0xE1E7571ED3719498ULL
        }
    },
    {
        {
            0x81DFEA436B77B601ULL, 0x9066882B5D0B0041ULL, 0xEA878AA60DE5E099ULL, 0x42DBA26EBB43EB59ULL, 
            0x2DD80FBB2C9B9B2AULL, 0xF6EFAF8CE3D23DCAULL, 0xCC7DD833D85F4E79ULL, 0x0187E92B721DA6D6ULL, 
            0x6A1AE7C6A2F6E688ULL, 0x8E24C534A78367F2ULL, 0x3FA4B6DB6E8BCD67ULL, 0xC38ACD82E71F5738ULL, 
            0xDC3EC24B7A23A9A8ULL, 0xA963621B0460A3A4ULL, 0x260D43173A35237DULL, 0x36850FDD90C38E8DULL, 
            0x5A302F424A4B863FULL, 0x05234F4222ABB63DULL, 0xA9F612FA085662FBULL, 0x587A520C730138BAULL, 
            0xF2A924FFEC2D826FULL, 0x6850DE666EA575AFULL, 0x877ACA1A82A8D85DULL, 0xBE9E24C33EE881FDULL, 
            0x86C4152DCBE6269EULL, 0x0CDECC8EE2C0B13BULL, 0xE6343E91589CAD8FULL, 0x58EB8434EE042C96ULL, 
            0x1FBE2DF6C9F6C911ULL, 0x1442381278B32CEDULL, 0xFA837BDE169DAC61ULL, 0xF45060B7858CCF75ULL
        },
        {
            0xC6AB717297D6C2F8ULL, 0x60E134AB7B6DC56FULL, 0x71AD40A2256E7848ULL, 0x5BA17C365956E14EULL, 
            0x74C4F3E95C59F424ULL, 0x8347D987A12ED21CULL, 0x06CF5A4ADEB49CE6ULL, 0xFA5B4E3A8D6E880BULL, 
            0x62A95AB64CC17677ULL, 0x8CFD075B52EFA499ULL, 0xB7DE58F925DD8D77ULL, 0x0F627C05DC7E01CFULL, 
            0x2BC7EE35B715717AULL, 0x486A72EC78ACDFC0ULL, 0x6660088DC4834D11ULL, 0xC0F34D679D631201ULL, 
            0x8D4D04CB551B6FACULL, 0xD9AA183553A9B66DULL, 0x674810A653144945ULL, 0x35F6004585FBD875ULL, 
            0x2EBD5CB6AD3E5D08ULL, 0x0EAE58A79C710E40ULL, 0x0D6EC23F784B4511ULL, 0x6CFEAC89CF9DE5CEULL, 
            0x18859166524391B7ULL, 0xE6F3EDECA58C1E00ULL, 0x899B1B77D9AF1DF3ULL, 0x71C22196CA02D699ULL, 
            0x8ED2A1C2FDBD59BEULL, 0x094E2B0584518A60ULL, 0x82008BC8693785F3ULL, 0x029EF6F579EDC776ULL
        },
        {
            0xB66FBBD9B5A8CECAULL, 0x3FB584519337F70BULL, 0x7FBA2E58DF58AEFCULL, 0x9F7E7CB9AFD4E1F7ULL, 
            0x63581C1237CE67CAULL, 0xA912F9FC06462326ULL, 0x999C153E087926EAULL, 0x3BBECEB21BB55FA2ULL, 
            0x089157B67B134AD2ULL, 0x6970A2944C044255ULL, 0xC33F9CB96940C022ULL, 0xBF948D13F3B7F10EULL, 
            0xA0B8D97384AA6F8EULL, 0x2A38DBFD0FE0E856ULL, 0x863A38FDF51D4EDEULL, 0xEF5D3415E7A24B2CULL, 
            0xFF2B83A8EF2F7815ULL, 0x306A9814F9AD3E78ULL, 0x3ED682469E418385ULL, 0x2BFBB5AD99A4FFBCULL, 
            0x327A87053C008E04ULL, 0xC9E719555A47F28AULL, 0xCC4487C6BDF28D74ULL, 0x3C056C6BCE3CBB1DULL, 
            0xD3CD6DA6D9EB2C38ULL, 0x7C8BC731C4E7623EULL, 0x86E2CF43EAC0EC95ULL, 0xD3D272EDC9EE9B7DULL, 
            0x5D481986640DCCBBULL, 0xB8404B3AF7CD28C0ULL, 0xDDDA43D79F131710ULL, 0x831B2FC9754132E2ULL
        },
        {
            0x541FE9EFDBF81B5DULL, 0x931666CBA5193025ULL, 0x0C0FC870C1DF6D13ULL, 0x3A6594EA284E656EULL, 
            0xE1F5F248879F7B31ULL, 0x39F05A6A1C70854BULL, 0x6B7295051A6C5B2FULL, 0xBB1A00B937BA14B6ULL, 
            0xFB0C356FB1431CF5ULL, 0xF528BCD88257C800ULL, 0x39B00772F416935FULL, 0x43FBB8B2ACE026AAULL, 
            0x0C778CD3CD10797EULL, 0xF32F905BE9B8B489ULL, 0xC4E4ED195EF78E64ULL, 0xDB7ECA9E20DBD13EULL, 
            0x406D1ECB24266254ULL, 0xC2FD575AAF78DA06ULL, 0xF40EFF388DBCA9F0ULL, 0xE8196463BF0A49E9ULL, 
            0x67A750B37D19C2A8ULL, 0x935C4918E6290657ULL, 0x7AFFFB742D10CD05ULL, 0xFEFDE4AA877CB0A5ULL, 
            0xAF36E36C59DBD6DDULL, 0xAF91B369D761AEDAULL, 0x68E540D366D00710ULL, 0x902C5EBDB9B324C7ULL, 
            0xA4B6530B5906E60EULL, 0x06C8800368D3B888ULL, 0x696B05BD24739D94ULL, 0xDA6E046AF83B5B5EULL
        },
        {
            0x976E8CF4944DC933ULL, 0x069D98A70B4729E6ULL, 0x12790D5AE6A8D026ULL, 0x19A77E86D8AD4AE1ULL, 
            0xD9F6FD60EE3931A9ULL, 0x7541691400A3721AULL, 0xEC9028EF0C09388EULL, 0xFF2F455D61CBEA5FULL, 
            0x67A0C59DB2D55737ULL, 0xCBF20FC9DC24165AULL, 0x85A499E18834B4B4ULL, 0x6F44064434B4D337ULL, 
            0xDCE217FD73CAA1BBULL, 0x7B2D1D95D1E58810ULL, 0x0552C6BEC08F5530ULL, 0x339B70A2B48BE96EULL, 
            0x7A374EE7D697E928ULL, 0x95135D7A9FE78ED4ULL, 0xA755DA5054E96B74ULL, 0x8F9D8FFFD6E52F08ULL, 
            0x859DBFB4F8BE7853ULL, 0x6C69D196E795D1E7ULL, 0xE85769BE042A5604ULL, 0x17DD528EFF64A0ADULL, 
            0xB35A8FAADAAAA860ULL, 0xFF09C5E1F963D788ULL, 0x1565EAA1B81BD34BULL, 0x67B14D2DD9B5ED41ULL, 
            0x3590079AF2A90729ULL, 0xCD1A740799623765ULL, 0x4E0D27FA3EF2D5E9ULL, 0x9351E88197B9068BULL
        },
        {
            0x3CADD08BEF27370DULL, 0x8C935820CC4D9075ULL, 0x9E82FC173683E6CEULL, 0x7253AB3A64B45499ULL, 
            0x6E705DE1B34761CDULL, 0xC89CB3A8A90B6522ULL, 0xDDEF1B60B686DD54ULL, 0xBFEA119FB125C849ULL, 
            0xBD4E061D920F5820ULL, 0xCF7A3499C84A7B9BULL, 0x000460B610B073C4ULL, 0x462304F8B635C526ULL, 
            0x8FEE66C93080D116ULL, 0x746157471DA3FA6CULL, 0xC3763714B206C99BULL, 0x54DD99F6C5844FF1ULL, 
            0xA47CFF028C99E054ULL, 0xA90C89713DFE8EB3ULL, 0xAEC504D1CB4B0201ULL, 0x58284F5280640068ULL, 
            0x4A18230827B10B48ULL, 0x70F0420AC611FE55ULL, 0xA6CF9AE21F3CBDB2ULL, 0x64C8CC3994F9428EULL, 
            0x6E0F799B0A284C0BULL, 0xD4F67C92DCA367DFULL, 0x92B619F150A5E91CULL, 0x7A60F63B4D48AE5AULL, 
            0xB4FD2BB0901FC243ULL, 0x1AB897430D6E6759ULL, 0xCDD4F104BE1697FEULL, 0x8F4F5EB2B4372029ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseFConstants = {
    0xC4E4932CCF18FCF8ULL,
    0xC0E24E96563C5199ULL,
    0x018E4A3A36F24ADDULL,
    0xC4E4932CCF18FCF8ULL,
    0xC0E24E96563C5199ULL,
    0x018E4A3A36F24ADDULL,
    0x88D7496E2EA5E6CCULL,
    0xA7511C5E712C3600ULL,
    0x0C,
    0xD0,
    0x8D,
    0xAD,
    0xA4,
    0x0B,
    0x2B,
    0x19
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseGSalts = {
    {
        {
            0xD610A4CCE80836F0ULL, 0x64DDEF4806FB0FF1ULL, 0xBE01C27A7E46465FULL, 0x261C8A0B26A65DABULL, 
            0x96F5BAE3D8B3C0FDULL, 0xA15A1D734EA64300ULL, 0xE78EB21D4F368691ULL, 0xC14CD8811061168BULL, 
            0x41E011F99CC5D256ULL, 0x725ABF10349825E7ULL, 0x1CBA80D39CF1FF73ULL, 0x22C61B6C5387590FULL, 
            0xB26CCC1A0D5D0896ULL, 0x3222D59D960F57AEULL, 0xF79C78FC10C1E351ULL, 0x7D0CABC8AAFA6D51ULL, 
            0x2713943368B74DAEULL, 0xFFFA928D302C72AFULL, 0xEBC0FE8FA5C8BF3EULL, 0x38599B53053A04E7ULL, 
            0x07B8A1415ECB932EULL, 0x1F4021ADE7C3B348ULL, 0x65F65DDE119502B0ULL, 0x62090325F340B1D0ULL, 
            0x588D5662F023038CULL, 0xB3B524B0FE9353D5ULL, 0x9FB2603601992A09ULL, 0x13A3231E03A2DE4AULL, 
            0x2F3AD7FA6701D9EBULL, 0xF45BBDE50631D0DDULL, 0x148E59421C89BB9DULL, 0xE261F9A6902081EFULL
        },
        {
            0x9338314841C3693EULL, 0x27595B7CADCE59A0ULL, 0xFEBCB23B6F992595ULL, 0xED9942EC7CB64D5BULL, 
            0x389A761DFF581A12ULL, 0xA6B318F62520A315ULL, 0xA9C28F025079AE8BULL, 0xA6F299631DA71688ULL, 
            0xADDBCCF97F10CC96ULL, 0xF487E2945B63C4C0ULL, 0x6AFB3080A2675735ULL, 0xF593A12DB3D2094DULL, 
            0x61BD5C4A4F49228DULL, 0xBF0AF175C7355F2AULL, 0xF6E32082E9CB2695ULL, 0x917E28ABE7272E8FULL, 
            0x5B8381DB555F965AULL, 0x0E05F56C9B7362F5ULL, 0xF6E1F58795CBD1A9ULL, 0x80685E402344B04EULL, 
            0xAA49A4CA6C83AAB0ULL, 0xDCF929A7E8A10C03ULL, 0x5276BD9162F62AA6ULL, 0xD77FFB4928938D40ULL, 
            0x6EB6C331A877801CULL, 0x33D9DD02529D65B7ULL, 0x17A9A0FE903F4972ULL, 0xB320B71F52015BE1ULL, 
            0xF33A474078806A3FULL, 0x21AA01FAF9085863ULL, 0x4C566DCA3465A961ULL, 0xCDB7F1ABA6F85A2FULL
        },
        {
            0x746310B713A4555BULL, 0x81EB63BF3088B5ADULL, 0xA0394D8E4127F225ULL, 0xCC66058D818D4039ULL, 
            0xB80CA7E1F1DC73E8ULL, 0x55814D48465FFBCFULL, 0x4324BB39DEF1771AULL, 0xC55F043C726149E6ULL, 
            0x8E17FCDB2222A749ULL, 0x991AB91292C8CCFCULL, 0x0B567C7B88C0581CULL, 0xB0D08244EDCFDB45ULL, 
            0xE00824D45ECA1204ULL, 0xBC32AD9711AF16D6ULL, 0x7B955BD5F0E99D4FULL, 0xC2A4E9DDF1B4235EULL, 
            0x8C0D83652D69218FULL, 0xE5869277F8894C26ULL, 0xCEEBB5F0F9ABE219ULL, 0x0CEF7DED0D36BE7DULL, 
            0x3E2B89FB22122C03ULL, 0xD8C0460D794BB2DEULL, 0xC6F088E168967480ULL, 0x0E0C58CF44C53DE8ULL, 
            0x402694CE9A4F602BULL, 0xC829AB724E2D2187ULL, 0xC539C2D644D0D179ULL, 0xD48292318C010D42ULL, 
            0x91C54BDDA4F01F7FULL, 0x18F41C0893089A5FULL, 0x45F66CD6FD2D3B80ULL, 0x9A348F434E8DBB19ULL
        },
        {
            0xB7AD52EDBF91E5F3ULL, 0x6B4DD32568551E84ULL, 0x8F3A36DD43D70E90ULL, 0x11E4CE34D6C9659AULL, 
            0x48A11E954976E68CULL, 0x4C72A02CCAD44F5DULL, 0x5598111F0912EEE6ULL, 0xBF98701A4F42F0BBULL, 
            0xBEDDA1249F26797CULL, 0x65D8B3CC5B6BBE26ULL, 0xFBA18501EDF3A94BULL, 0xAA650703AD113E92ULL, 
            0x2DC1C1B49286765EULL, 0x4A525713265EBE8AULL, 0x1431AA605B262C72ULL, 0xD552ABC50FEA54DEULL, 
            0x2A03668D7DB416A2ULL, 0x85CACFC07223BDC0ULL, 0xC7E3BDBDD16FC48FULL, 0xB6E914DF2091C65AULL, 
            0x137E3E5343288647ULL, 0x193868F227981BB2ULL, 0xB46626597B4664B2ULL, 0x979E45120EB1997FULL, 
            0x54065918D98EA657ULL, 0x54CC6A9080E1CD53ULL, 0x6B38AD5AE67686BCULL, 0xD872A44FB4455639ULL, 
            0x28A0FD49BD5377C0ULL, 0x5E367B66E3AF9600ULL, 0xC88918CAA739BA00ULL, 0x2F6033C167654E1EULL
        },
        {
            0xBDECE6E17ED4B4D8ULL, 0x23E14930C168F426ULL, 0xF603BFBC873506FBULL, 0xFA19000F5535FC0EULL, 
            0x5AF8E21C6D0465DDULL, 0xC78C4B288D723038ULL, 0x9E2585D65B21F47FULL, 0xE5116BEDF99F48D4ULL, 
            0x688D6C5F444E8761ULL, 0x0461EFF62780901DULL, 0x5891B481C526C0ADULL, 0x77A6DC359B82AF7EULL, 
            0x2C81D0BE7BFF367BULL, 0x8E42DBBA77B4221DULL, 0x180B1BB0AE84D117ULL, 0x9A7ED1F9F4038C9EULL, 
            0xD131374ABB8A0B80ULL, 0x4BA03F32E8D12B40ULL, 0x522A24605F9109E7ULL, 0x5549E722F64AAD1EULL, 
            0x740DE76A411692F6ULL, 0x7EFB7CCE2ADCE2B5ULL, 0x3ED574E9331C7517ULL, 0x3826C17F5375B03AULL, 
            0x35A9D11966D5CD88ULL, 0x85B294512318F666ULL, 0x7C40E6D0D4C03FD8ULL, 0xA8FB1D4E9FA51B7CULL, 
            0xB953F410760FA2F1ULL, 0x71DA24B1F108C5CDULL, 0x8DC3B3335125392BULL, 0xA7E5D0EB43B5923BULL
        },
        {
            0x5B4EB62FA51E2495ULL, 0x0AE668BC2DE49C32ULL, 0x2E0BDA304691330CULL, 0x04CED6B1BE1258CCULL, 
            0xEC85028386220320ULL, 0xB6797CA94807E711ULL, 0xF7650267FCBE2C29ULL, 0x2BA83A82D204E7B2ULL, 
            0x183F0A1BD08FA947ULL, 0x1D07EC1F11F3F9ECULL, 0x331E928F1C219974ULL, 0xEA776D95A5691898ULL, 
            0xA14B61AA6D3A4C2BULL, 0xDD2A706165121B3EULL, 0x203855C2BE9B7C03ULL, 0xD939250AC235F383ULL, 
            0xCA5D8EA94348E0B5ULL, 0x674758ED0EF0B750ULL, 0x297DDB75A6149AE4ULL, 0xA9A5C34921515C01ULL, 
            0x1E535E41C03CF3FDULL, 0x32043F3D37889164ULL, 0x2DEB219CD1266D42ULL, 0x9283E428B54C39BDULL, 
            0x983550219DAC35E7ULL, 0x68237CAEE0854BA8ULL, 0x1A18B8BD8490C5F6ULL, 0x8CA3AE40A0056D97ULL, 
            0x2C59EDDA92DDB8E7ULL, 0xE07B19D555418B9AULL, 0xB6B573A41F8BE5EBULL, 0x896A8B2F1D6E87FDULL
        }
    },
    {
        {
            0xCE7186A00B7B1D3EULL, 0x56E1D8FCC7DDC400ULL, 0x024015F6B2351048ULL, 0x3EE69F4F46995388ULL, 
            0xC780370ECB82A000ULL, 0xB12A00EBBA4FA637ULL, 0xBD16410CE8FA25A7ULL, 0xF9F2F5F00DBDDF3DULL, 
            0x76D404108EB887DBULL, 0x35F1E1CD2AA16CB2ULL, 0xE6C40FAE133C5598ULL, 0xB4D13DF65E2707DDULL, 
            0xE85AEFADD21CDEBBULL, 0x8A33D21044121FC9ULL, 0x1E240357818CCAFCULL, 0x64A3FF759AB14A28ULL, 
            0x4E80D14F0492668CULL, 0xE511370806EF26ABULL, 0x625B698B4E5900D9ULL, 0x66F3ACDBA979C440ULL, 
            0x730E162BF7552F39ULL, 0x522329F8A6680B82ULL, 0x1CAA8102C7E65BE3ULL, 0x456FB53590776A97ULL, 
            0x7B7CCF1A363B590AULL, 0xF6BDF419D907A6F5ULL, 0x481AD7F8C883757CULL, 0x30AD4CE0A0FB39E8ULL, 
            0x5379F2994BC545E5ULL, 0x2CA44B3811DDCA2FULL, 0x2A586F8F30908694ULL, 0x0DE9B3E306FB7B8EULL
        },
        {
            0x701B3AED86698372ULL, 0x9FE56B5DFAFC748EULL, 0x1A54294C29C5FECBULL, 0xF69E2425A18BB43CULL, 
            0x4976597991BFEC08ULL, 0xF3A076B531A308D0ULL, 0x29EB072A7559F768ULL, 0x3EA996FF2EBE244EULL, 
            0x9ED5540238A8D8C3ULL, 0x2A9F9CBB7F02E9FCULL, 0x7E33CE22FBBC9BE4ULL, 0x074266B5772DEAE6ULL, 
            0xFDCAC4E2BA5DA8BAULL, 0x9AA75617F9CF1C23ULL, 0x201E6A42DC08D721ULL, 0xFAF7E7D28C0D5A3FULL, 
            0x0DF1B2B3CA2504B8ULL, 0x1FE295A63EDC49FCULL, 0x5FBF0B3014CB61A5ULL, 0xC73F95085D03B6DFULL, 
            0x58D8917BD73795EAULL, 0x04ADD6F0A2AB3BA2ULL, 0xA030AB697B5A8B33ULL, 0x1E16086BC96C71AEULL, 
            0xDBB6F88284C5427BULL, 0x6A44887C388D4DC9ULL, 0x513FED8DE0061BF1ULL, 0x93035EC670BF4F24ULL, 
            0x0C5E09F23E74572CULL, 0x2929AF0EF4FB4651ULL, 0x6EDA2B501F25A367ULL, 0xABAB3215FD05B174ULL
        },
        {
            0xBDEEFAEBDF570559ULL, 0xBB26A49C3578B21AULL, 0x8B74917D0DC1B97DULL, 0x6DE80A1097A50803ULL, 
            0xA018070D273FD462ULL, 0x7ABD1F71399D8605ULL, 0x660A2788A831FB4CULL, 0xE54A6980B48BB222ULL, 
            0x2D515CEE9AFA38EAULL, 0x2C739A1EDDD80FDDULL, 0x40114D63F35537A6ULL, 0x784E9780DF7E1DF5ULL, 
            0xE0ED2F854AA59540ULL, 0xB23AFA1FD6529FDEULL, 0xEEB4271F53736FD7ULL, 0x6C2EED7A1284FF48ULL, 
            0xE77BEA8B26169916ULL, 0x008FED5F5E84C015ULL, 0x604024AD266EFAB3ULL, 0x1CB77BA193CCE3DDULL, 
            0xBEFCBB431D149321ULL, 0xF135075488E5A39CULL, 0x38A60AB4BA7652C9ULL, 0xC6A339F7632F6A23ULL, 
            0xDDDCA81C9FE1AEA8ULL, 0xF4FC6BBA8D95670DULL, 0x6EAFAD295A704E17ULL, 0x6FB58B6FA3F17172ULL, 
            0x222743035D49A53FULL, 0x937E12E5ADD5EE8BULL, 0x4D765811735C8832ULL, 0x01990A79BFD5E2BEULL
        },
        {
            0xE7CD6FB0800CE37BULL, 0xF84EF9F6FC2606B5ULL, 0x27D0AAE7DC7A860CULL, 0x3412EFC5CD201415ULL, 
            0x292584900B0AA7DCULL, 0xF26DC1BF1095AB9DULL, 0x50A44FF8D111729BULL, 0xF8037B77FBEE2693ULL, 
            0xB83C3281890B11C5ULL, 0x63C17BD6E52E63AFULL, 0xE623BEF5D80ACA9EULL, 0xDCA13AC377D7F811ULL, 
            0x2539979CE0528E5EULL, 0xBA75D9AB87F80549ULL, 0xAA843B770C6AC607ULL, 0x699FE2518FFC764EULL, 
            0xCAA283223CD191A9ULL, 0xED8386DA56B6433CULL, 0xA2D5C530D43ED625ULL, 0x0471AD1735559CC7ULL, 
            0x154BC3CED63A9E84ULL, 0x42BDB064006F3372ULL, 0x2F2D09BE96D1AC93ULL, 0xC87A1ABAFC8F512CULL, 
            0x76F82A7A793BC30BULL, 0x5163196556572803ULL, 0xA9C01AAF7C0FEFEFULL, 0x10E2043C20070B55ULL, 
            0x66DF1CEF3A11D7F4ULL, 0xA4BBB00BD1BE660FULL, 0x4659A8595D0DD9E3ULL, 0xA484B8159803091FULL
        },
        {
            0xF27C30B96E364077ULL, 0x4764AA23407EED36ULL, 0x816D8E1180523E54ULL, 0xAF068C1AE6D13D3DULL, 
            0x70E4E6C3F21C5CD3ULL, 0xDF62A492C6F0841EULL, 0x819AC4115E2D9278ULL, 0x9586ED8F2326D259ULL, 
            0x19C32C4F0C9D124CULL, 0x5815A525E032F3BFULL, 0x850A04F67606553EULL, 0x19B9B765A899F6D9ULL, 
            0xEE1FF07ACA7144B3ULL, 0x5E1621C244A11472ULL, 0xF36789F525B6A47BULL, 0xF0D599309EA510BDULL, 
            0xC142B4FAFFEB62B2ULL, 0xCC99BE6405B70B55ULL, 0x02033D9B5573F080ULL, 0x75352FD901FF0310ULL, 
            0xCF7EFE72FD2BEC61ULL, 0x50F7FF5A02349330ULL, 0x75833BE6B38EEA13ULL, 0xFF3A04E63C1F5A48ULL, 
            0x6835A843A232C669ULL, 0xDF9069D013209795ULL, 0x1AAD6D119EF5F95EULL, 0x6D8D98DC9370160AULL, 
            0x3ED68146EBD979C2ULL, 0xFAD7B52D21E53CC2ULL, 0xA60E0C10673EA926ULL, 0x4A633CDD064E4A57ULL
        },
        {
            0x914DBC978609CA67ULL, 0xCAA26C278D96F0B7ULL, 0x92C775938992CCC1ULL, 0x5FFBE70922651795ULL, 
            0x2DC30AB1707A2BFAULL, 0xDFE27DD76834E005ULL, 0x909E0332562EF3C4ULL, 0x3F77C337C5B6E5D3ULL, 
            0x76B074CB677D5D87ULL, 0xF7C40E4DF2970E5FULL, 0xC92AC0A84BF976C3ULL, 0x9FB3D911EA1B3ACEULL, 
            0x2088F1E8EC46DB79ULL, 0x41582D9D0C36B6F5ULL, 0x3BE8855F7C17D6F0ULL, 0x94DECB3808F6A206ULL, 
            0x8FAAAA1A1DA6FB5BULL, 0x345BC1770828D5B8ULL, 0x7B472DF97E90E6AAULL, 0xBA25326BE43C2043ULL, 
            0x2F6CFC3FBB7BE2A1ULL, 0xDE97E338E723ECE9ULL, 0x1ABF7A9367E017B0ULL, 0x92447FC9F48020ABULL, 
            0x8654D785FE0C31F2ULL, 0x6583BE2EC702A06AULL, 0x33DF1C7C9910A659ULL, 0x839CF0638CFCF1F0ULL, 
            0x772450B14C079BC6ULL, 0xF62156312407446DULL, 0xE2FED6B2D5959AD6ULL, 0xFCBD5B87F6B32C91ULL
        }
    },
    {
        {
            0xE6F465BD7423CC2CULL, 0x233773CA5A453837ULL, 0x2414E7729CB08578ULL, 0x82B9739EBEF6F692ULL, 
            0xE9E9E866D867346FULL, 0xF8347AE55E8B4E65ULL, 0xEC6939891F2BF629ULL, 0x9A6601356EA7ED2CULL, 
            0xDE17E3EC3E371ED3ULL, 0x0BF6C7B85317562CULL, 0x70064B5001C2E2D0ULL, 0xDB47C252E59A1FFCULL, 
            0x4605953F6D731790ULL, 0x640E0C50A2A7673AULL, 0xFBDD7F6227186181ULL, 0xC9D2E2DE1B702F17ULL, 
            0xED1D2743F1874C39ULL, 0xDA837CF83DD8328FULL, 0x2EC0C2EACF6AA2A7ULL, 0x5CC6190C638BFE1EULL, 
            0x93EF9B26A0C43C9AULL, 0x2DFCDAB3AA4C68B2ULL, 0x54E25915900B32F8ULL, 0xF8B5A7012E7A859EULL, 
            0x45BD5F7BB13E7653ULL, 0x6C493347A2EED307ULL, 0x1D218C8779040C06ULL, 0x4E798A5E1253C284ULL, 
            0x1831E2E54B3B0D72ULL, 0xD76A0B64A6CD1E89ULL, 0x84F061C3B562903BULL, 0x3945595B31BDA6DAULL
        },
        {
            0xDF2D94660554A2D8ULL, 0x50582CCD530CCE0AULL, 0xC260889F4B71E946ULL, 0xD4C761CA7AE95BC8ULL, 
            0x0174E5E53C91E44CULL, 0x763980C86208519FULL, 0xC2066A36B179F270ULL, 0x1B8C1ABB7FFAB7BDULL, 
            0x3ADD34B50556DBC1ULL, 0xC0790397F0B44743ULL, 0xDE2E4E691BFB8EC4ULL, 0x7C154AE13E53E681ULL, 
            0x8771DDFFEC3A6EEAULL, 0xA8CEA43A734D339DULL, 0x2A7CA84A4981B4E4ULL, 0x8162E4516EC45EFDULL, 
            0xE38CCADF3246A307ULL, 0x121AFF77ABABD9C4ULL, 0x987140CF43EA99FBULL, 0xF11A1227A66C7964ULL, 
            0x504221FB652F3487ULL, 0x0C5644F76CFBC65EULL, 0x946D73B8E2673580ULL, 0x9A77F4DF57D05633ULL, 
            0xA4BBABAAAD31A964ULL, 0x884DA66271EA15A1ULL, 0x0A436B50D5240F10ULL, 0xDACD265DA5336D8FULL, 
            0xC4624DE329EB6047ULL, 0x24E40A8625AAF37DULL, 0xAAD354BA4389FDA4ULL, 0x32BD97BB3D77E9B2ULL
        },
        {
            0x797C911F1129B4E4ULL, 0x6061375F5F316573ULL, 0x9A7F12E6F81A1694ULL, 0xBEC298454C3BDAB4ULL, 
            0xBEEB7EEC0F89923BULL, 0x8744BFCF450B21E6ULL, 0x29A8110578804657ULL, 0xC226DF79EBC9CF2AULL, 
            0x363AFA3B01B7B2CCULL, 0xBF7B5B6D41D80FA8ULL, 0x30BB4973ABA20670ULL, 0x681F6D3FEF0ED028ULL, 
            0x5FF0F1350C9B94FFULL, 0x0A3ADA69E309EE46ULL, 0x82FD1684B4535143ULL, 0x0561EFDE16D71A21ULL, 
            0xC73828C795981136ULL, 0x41A0CC6AC681BB4DULL, 0xF4E46CEABE03CB02ULL, 0xEBD23661850B79B2ULL, 
            0x8575D2B2CB271E0BULL, 0xE310F8EACC4E6591ULL, 0xF62C8756BBC7DD74ULL, 0xECC34E724AE2B231ULL, 
            0xB4F7C7A5162FD95AULL, 0xB4D588C790A3A50EULL, 0xA160852430DD88CEULL, 0x657ADA81207CB20BULL, 
            0x2D09BF968DF93A49ULL, 0x1969ABE75B8796E1ULL, 0xF9BA4E1C50984122ULL, 0xCF998CDBE25D2434ULL
        },
        {
            0x00C39E545F3A6163ULL, 0x67ED9D0EE5AD3670ULL, 0x87EF326B9C2B8F88ULL, 0x4859FD324A479108ULL, 
            0x65CB15F1C4E46969ULL, 0x16623E632B14F549ULL, 0x643E752DD842614BULL, 0xCFB05D4CBDDA19F4ULL, 
            0x2733DC96A80EC799ULL, 0x9E3D6D8E8FE0FEB7ULL, 0x4A7F8B97B8ECD455ULL, 0xA021C16719092738ULL, 
            0xB5E125C06A2B7732ULL, 0xE527AFE366B87890ULL, 0xA3756FDD9CA4EC00ULL, 0xED13F1F5413D7786ULL, 
            0xC2E5E0B2BC40D517ULL, 0x33180F901FB966BFULL, 0x2E4F935F1E576903ULL, 0xCB401331B8B33BF1ULL, 
            0x065CDE94B2C8FE26ULL, 0x4A9492F15DDD3216ULL, 0x6C73A482EA8BFA65ULL, 0xE5399912735060E9ULL, 
            0xBEE6BC1DB7CDD86DULL, 0xD9923D53E56AE2C9ULL, 0xD6297F22083F369DULL, 0x4B0F18CF24B8684CULL, 
            0xA8315823772F40B9ULL, 0x2ADFB2AF7A913912ULL, 0x077F221FDFC3C38EULL, 0xC3E13ECAEE84A094ULL
        },
        {
            0xF4AD53B44806B99DULL, 0x3CB17BFDDCE8DDE5ULL, 0x143F881819CAA3C1ULL, 0x37A5D95865FFAAABULL, 
            0x759F163DA7F5D7A6ULL, 0x427848612A73F9DCULL, 0x9A7DE2632440E3CFULL, 0xB6B12A139B9C587DULL, 
            0xF4D1DAE1D55761F1ULL, 0x8746E7A234F4A152ULL, 0x80C82B2200B2227AULL, 0x55804C3E7D58708EULL, 
            0xE61F25B1924EC45AULL, 0xEE443DAF20A3FD4AULL, 0x4F673A3D3C328823ULL, 0x1C1ADA9C98E07419ULL, 
            0x476BDCDD4ED10123ULL, 0x24B32E4694973564ULL, 0xF53C0F548711EE31ULL, 0x31A1641713E50DE4ULL, 
            0x5BB76280C94859DAULL, 0xF8F7F139FC237F7BULL, 0x3ECB810AB4237366ULL, 0x2ABEC35FBF95514AULL, 
            0x6BE7669B29EBD415ULL, 0xBD9E649FC4842F4EULL, 0x6DE6EF03682AC469ULL, 0xBE524AF898A1A186ULL, 
            0xAB1D0AA68960EC85ULL, 0xE2DD62E01C760F16ULL, 0x534123E4B41D226CULL, 0x1D5C73F8B410D640ULL
        },
        {
            0xDF374F3FE7919FCAULL, 0x6F5D4B402B47F56BULL, 0xB1F9BCED602AD4CAULL, 0x91E87B944487D40EULL, 
            0xDA5328B251CFA035ULL, 0xD0933AC618ABC00EULL, 0x0FAEC79A238FCE6FULL, 0x5224F5BB2681514AULL, 
            0xFA2BC98F533662D4ULL, 0xDB7FD0872ACCA4EEULL, 0x3193A28D687FFC90ULL, 0x45931895D2F5BF83ULL, 
            0x0FF3034C1C3C74ECULL, 0x8CBBE58D49DFCEAEULL, 0x6B922DC56EF6A32DULL, 0xAE9D35C956B06667ULL, 
            0x13499FF6538B343CULL, 0xD89C7846F9CC03C7ULL, 0x0C22342ECEC6FE91ULL, 0x811C7B9EF954205BULL, 
            0xE07FF645DA9D609BULL, 0x47E2AD8E0888E371ULL, 0x6066495ACDAF9202ULL, 0x5A6F5F4077D4B45FULL, 
            0x1D02D972223A54BBULL, 0x5F6DFD9F90D62E31ULL, 0x4C767EE121956A89ULL, 0x35676BA57C9BCD15ULL, 
            0x26DE72303EF244B3ULL, 0x1CF4C6F8997F3A75ULL, 0xB6CE3567C87CDA43ULL, 0x00AAEFFBCD114577ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseGConstants = {
    0x3A82878500C3BDE9ULL,
    0xAF8359050C9FFDF1ULL,
    0x0F9A7134251256DFULL,
    0x3A82878500C3BDE9ULL,
    0xAF8359050C9FFDF1ULL,
    0x0F9A7134251256DFULL,
    0xF63071CA634AC10BULL,
    0x518A4A7FCCF1A666ULL,
    0xE1,
    0x97,
    0x02,
    0x6F,
    0xAC,
    0x7F,
    0x05,
    0x1F
};

const TwistDomainSaltSet TwistExpander_Alcor::kPhaseHSalts = {
    {
        {
            0x11ECD2FE8D1EF01BULL, 0xFA1948B8709F3AEFULL, 0x58B3F9E4C1451942ULL, 0x3C03123445D433C1ULL, 
            0x07149B9E9E6A90DCULL, 0x53F0BEA6C1676B8CULL, 0x9BDCCD6C2A49FE38ULL, 0x13CF9EA8FC68B203ULL, 
            0x350F992706B0D810ULL, 0x98C0DE450F8DADC6ULL, 0xFD181C6B491070C7ULL, 0xDF609C099BC49F25ULL, 
            0x6DB4AFF77CEDE1C9ULL, 0xE3D7C487E011D00CULL, 0xBD67246B52FA3390ULL, 0xA5854B102C4AFAD1ULL, 
            0xF3634E8D471660B7ULL, 0xA48D84F1D04D3190ULL, 0x42CB14F8FE10B528ULL, 0x83C6E1CD39620DDAULL, 
            0x76EBDB6F691CACB1ULL, 0x19DDBFA82E5137F1ULL, 0x1663915C17E913E8ULL, 0xA7651638F4BEE738ULL, 
            0xC5E27D9F548DB365ULL, 0xC6E62D29949C11C9ULL, 0x39D585918D2201F3ULL, 0x872DCE39F378293FULL, 
            0x72CA53344A388BBAULL, 0xB2BA4B3FC63CA025ULL, 0x8DC091BBB282680FULL, 0x4EFFD7754B19C6C4ULL
        },
        {
            0xBBFE5006BD0476DEULL, 0xCD26308C9AC5F872ULL, 0x745F80AB8F64250FULL, 0x1E08A20A840E0EF4ULL, 
            0x360D8143256326FDULL, 0x3B18E994C75439B9ULL, 0x44E7F33269F2D517ULL, 0x5B077E9DE5951A52ULL, 
            0xB26D19F5A49AAA3FULL, 0xFF1901C6C1FCE51FULL, 0xFC19EA5ADD7BBD10ULL, 0x24016044A81F2015ULL, 
            0xBED4746F0DDE38D6ULL, 0xAAA82D6B17B6F106ULL, 0xBCF4C6B1CB2F22D0ULL, 0x9006182B4C181BD6ULL, 
            0x79773DB9CBC5E756ULL, 0x05B039F32FEEB3E8ULL, 0xD6CB763B27678FD6ULL, 0x54C7F0A7AECFB4C7ULL, 
            0x8BBFCAF89313088AULL, 0xA29BA1594CE6A9F4ULL, 0x79616674965A1802ULL, 0x3D7F3FD9DAC7EE30ULL, 
            0x0EB7C193F07B9522ULL, 0xA1CC71323C996877ULL, 0x4D228C0C76DEBCC2ULL, 0x9E006AC26C4ACF9CULL, 
            0xE363A68570D12433ULL, 0xBC343C313B673A58ULL, 0x9AB1205049E7F9E5ULL, 0xACE3065B37F2EFB0ULL
        },
        {
            0x5E6FB27EB676D6A2ULL, 0x96FC7C274B126A12ULL, 0xC8267DC1E291678EULL, 0x0C526237583FABBBULL, 
            0x623D8054A9A52322ULL, 0x78B752B740E51235ULL, 0x2D56E590422879C4ULL, 0xA3812A963C78FA0DULL, 
            0x41900B7EC1E1FC1BULL, 0x6863487F61FB4E8DULL, 0x599EC57E74F1B3A4ULL, 0x76AB4DE6F3DE8257ULL, 
            0x7695C7F9E37A2DC0ULL, 0xB6626322C088F6EDULL, 0xE3C7DCCD59E1B562ULL, 0xC12FEC735BC6B0FDULL, 
            0x7A61E1BF8F0DC729ULL, 0x6CFB116B4CB7373BULL, 0x29440A4FA4915E4DULL, 0x422F0703201C6BB8ULL, 
            0x6A69D141A8459DB9ULL, 0x63F30138242A08A9ULL, 0x536BD5238A91F0DEULL, 0xDF2E5E616C45EF7FULL, 
            0x882F113DE8550A5FULL, 0x2DABE89B7A1FD52AULL, 0x7C2A544DE0029957ULL, 0x284268F80F6B8BBAULL, 
            0x343215BF7B2E6591ULL, 0x26C708ABF80D8E10ULL, 0x94B461F88A252EE9ULL, 0x701C6B36BC42DF7BULL
        },
        {
            0x20DC7F9D736594E8ULL, 0xA89B99D2625A175BULL, 0xBEA0312C8A2DBC97ULL, 0x513E25E95ABFC7C0ULL, 
            0x32A5A49AAAC2BA3DULL, 0x0AC653B8CDE239AFULL, 0x285B87E712D317FCULL, 0xFD1DD930F56B9D3DULL, 
            0x81600AAA91458539ULL, 0x488F7BD61BEEEED9ULL, 0x3772C225B4B5B332ULL, 0x0DAA3F531C1CF4C9ULL, 
            0xAE7022672BAB2309ULL, 0x92618F97D269315BULL, 0xFC8C2E58553DE6B9ULL, 0x66C690FB3FEBA821ULL, 
            0x77FDE1893C889CC7ULL, 0x7F339E427187B243ULL, 0x3EF278E37CAB7ED5ULL, 0xBE91C7ECEE932795ULL, 
            0x82146E58A8B97498ULL, 0xFD7058743AF12E6AULL, 0x2C07CFFBD83AF211ULL, 0x862D90E83AF94A9FULL, 
            0x8A73C3F6101FEEFCULL, 0xE4436BC8BC5054A6ULL, 0xF731FD7B2E3E1894ULL, 0xD5A483D6037775A2ULL, 
            0xE45BCE0BE1DAA877ULL, 0x68A7966DC98B8F6AULL, 0xAB6D747D30A023CDULL, 0x8AF2BD12ECED22CDULL
        },
        {
            0x0D404297DF664A6EULL, 0x3C77CA8A022E2151ULL, 0x3511B9E980B13C0DULL, 0x966FEDB8222E99CAULL, 
            0xFD342A4EB7673DE4ULL, 0xCC7B321D9CA3A015ULL, 0x624C494F16587C7BULL, 0xE8C9B347D1E4A409ULL, 
            0x5C8BA47BAEE773EEULL, 0xC6292AD54A6AB875ULL, 0x82DBF1C2B3792F80ULL, 0x210E1556476490C7ULL, 
            0x3EC409002071CC49ULL, 0x7E500E2FAE6DDDD3ULL, 0xB7EA2AE01F04776FULL, 0x2D41C1E183287D05ULL, 
            0x226AF9AB6018CBD9ULL, 0x896F92138898184AULL, 0xA447D869C8C35014ULL, 0xF6B909AC9D3AC40FULL, 
            0x0835D43D8E6CDA2FULL, 0xD029B1CB30D1375CULL, 0x1EF3FC99E235ED7AULL, 0xB709D5D95193ADB9ULL, 
            0xB19B2A5D777BB2D2ULL, 0x8B42BAF6D3E11E91ULL, 0x145EFA30E6625EAEULL, 0xE26ED77A1E4ADE57ULL, 
            0xCE2D0D16C05D5779ULL, 0x02A98FA051F659A4ULL, 0x05FC942EFF9BCA8AULL, 0x63CAA87857C1B226ULL
        },
        {
            0x3AB6FBA8448276B3ULL, 0xB5449E4A29CFBA43ULL, 0xA86FE49327E8C759ULL, 0xD9478CA50D22CFA1ULL, 
            0x503F7BB289F797C6ULL, 0x34E29620FA9652C3ULL, 0xDD07B0BCB4EC83DBULL, 0xA1FEC4BFE10E6605ULL, 
            0xBEEAFC85ECB32B8CULL, 0xB5B5A59E36DD3AD6ULL, 0x94C08A8947BBAEF4ULL, 0xA8671C9D5E21FB1FULL, 
            0x6F7B2DE8C93E3A1BULL, 0xFA1DA647207209C7ULL, 0xB4E5B14071DA460FULL, 0xC29A0980D819273DULL, 
            0x131AECE5DB1E529FULL, 0xAB9602A50EAB05C6ULL, 0x1FCE3B541BF06FAEULL, 0x173CBC7B72D0DE85ULL, 
            0xB857ECE450BA7CCEULL, 0x2D6D5C41B2219823ULL, 0xCD74D2BC54F8B3A9ULL, 0xD03E1B3E09B0652EULL, 
            0xCE8BED4454FF6CBCULL, 0x3A79D2D66BE73A6DULL, 0x277A69CEDEF56673ULL, 0x38DFD8DEA112F160ULL, 
            0xC9369A8F4779272AULL, 0x82077D6E5CED7933ULL, 0x4F07B07F218D7CB5ULL, 0x830B49C0F9321551ULL
        }
    },
    {
        {
            0xC8E106E40B79EB2BULL, 0x9921C1FA37BDE5F2ULL, 0x6634D44F3732F5C7ULL, 0x7CC4A1C6D1BDE0AFULL, 
            0x55BFDBC99C62A0A5ULL, 0x5B755D3E5EE4BC48ULL, 0xF15E5FFB5AB1BA34ULL, 0x2A36216C22EAA8D4ULL, 
            0x64FD454EE1306750ULL, 0xCF54D0971EEB3688ULL, 0x9376ACAAB5F3AA20ULL, 0x6DA0B715C7C18A06ULL, 
            0x29D13BE50A8BF928ULL, 0xB197023D6BB33EEBULL, 0xECEF0F827DFC129CULL, 0x094BF98E95003CFBULL, 
            0x23952F51F50443F2ULL, 0xFE63808616A0874FULL, 0xDC8964106C59FB51ULL, 0x9CE107DBF0E14713ULL, 
            0x78788C105C2CC8E1ULL, 0xFDC31563A23DBF15ULL, 0x25E6A8E40094F241ULL, 0x33203C322DF365F9ULL, 
            0xC97328EBF5F0DD2EULL, 0x4C70F8D14107F596ULL, 0x74CCDC06C85599B8ULL, 0xEA5C5A3D134836DDULL, 
            0x41FD7C1CC2B1CDFBULL, 0x5D40CC4BFCAD5877ULL, 0x65CB307DE5C78C2DULL, 0x45A0562DE040E50AULL
        },
        {
            0x7DD12846BAEC66DAULL, 0x279C248337AB0EE3ULL, 0x56DBC94FC06212BCULL, 0x703EF5189DF087F3ULL, 
            0xB65F77D30C142BA9ULL, 0x00AEFD5F55D6038EULL, 0xA0E6CA185257D9EFULL, 0x28DDC17CEAF4C7B3ULL, 
            0x998D6AE0D5B0C9B5ULL, 0xBB67B551F3D1B0E0ULL, 0x4789BF426A82B6A5ULL, 0xC38A8B5DDCFA5B08ULL, 
            0x4D2AEA09F1C65E56ULL, 0xCBF037B77C157921ULL, 0xFBE7AC44E6C8CEE8ULL, 0xF11E080266F84D04ULL, 
            0x2495A5B4244FA82EULL, 0x00E2EF2122855FDBULL, 0xF5AB154EBE273232ULL, 0x3876BB7EDECC9D22ULL, 
            0xF35AF41D6217211FULL, 0xF5C8F7DBFB1A2E77ULL, 0x5203E3275B151870ULL, 0xFE570E01EE9E8409ULL, 
            0x958F61CCA45B3E56ULL, 0x30B3D36D8DA6C526ULL, 0xA211FC1CF5A31C8CULL, 0x1A4BEDC7E6AFC57EULL, 
            0x5D0E4682C0B634EEULL, 0xE499A93E973F41D3ULL, 0x73B9EF9A4F018A41ULL, 0x8FD8364FAFF2933FULL
        },
        {
            0x2B06EDBDE31568AEULL, 0xB4E6B8F756797908ULL, 0x47B5AF8485B5E7D3ULL, 0x28072ECA20715211ULL, 
            0xD855027855C39AAFULL, 0xEC2DF5FE8C88EA77ULL, 0x8131FD6C2AF365DFULL, 0x84DA4E480E19C763ULL, 
            0x43CD213BB4217576ULL, 0x1CB0795B8FC7520EULL, 0xA5A663FD74B79145ULL, 0x58DD7DB5A78485F1ULL, 
            0x8FECB07FED738B04ULL, 0x744F3EE64A2601F2ULL, 0x760593949D8CB4EFULL, 0x0234A4F26BB10085ULL, 
            0xFB4A869ED6E318BAULL, 0x1FE674324E41938DULL, 0x79E1E53E78B084D9ULL, 0x90ABE286DD0502B2ULL, 
            0xD84B4CBAB492673BULL, 0x12007593BBA95AF3ULL, 0x00F5A9FC7F3E8D70ULL, 0xC24C9983CD387E92ULL, 
            0x34E105C813FB9D7EULL, 0x08BD86DFA8A68B11ULL, 0xC1E3DF069649EB62ULL, 0x35668E777119649EULL, 
            0x47310A9C6A4D3ED7ULL, 0xC613766DBAADBE03ULL, 0x7C649F74A595D0FDULL, 0x043432D6D98FF9DCULL
        },
        {
            0xDE39403253208450ULL, 0x6CD6F2CF212A6C84ULL, 0x08E06BE84FC66469ULL, 0xB8771FFF7FDD54D1ULL, 
            0xB274227E5C3D390BULL, 0x8DC54CF45398C300ULL, 0xCB4BD2487646E5AAULL, 0xB37B4646CBE86BC0ULL, 
            0x5C0A263605E3370AULL, 0xBFA1F0CE9B7C9FC6ULL, 0x08D3471C57E5B6F5ULL, 0xE8663BE1FFB7BAAAULL, 
            0x171BAF759F99B1EDULL, 0x28D49487F9512884ULL, 0x068B04F877CB6E20ULL, 0xE6C3DFE7E22E01E3ULL, 
            0x5BB6D23246ED2BE3ULL, 0x8C6583794DE30459ULL, 0x4971F8178A9AD864ULL, 0x5D07F203B0591CDFULL, 
            0xE31745224FCEE52AULL, 0x5C34CB3AA28D29FDULL, 0xB76C0376C6E1E9EEULL, 0xEDF6C2A97E8AE270ULL, 
            0xD59DA88C32E89D78ULL, 0xC60BE3E375A7B808ULL, 0x95F27356B7D4D9FDULL, 0x5C65F36061AB8A41ULL, 
            0xDD56F9989944BA46ULL, 0xAE8D48DC61103D6DULL, 0xE65CC9694932058BULL, 0x3C4387EA8720EC97ULL
        },
        {
            0xE82D0EDEACD3F4B5ULL, 0x15F29232A01120C6ULL, 0xB40886A96F6ACB04ULL, 0xA5E824BDE002E422ULL, 
            0x6049B41D55B0C71EULL, 0xB47A6FE8B01A27E6ULL, 0x86BDD4A992582550ULL, 0x1D6A8610308E7F77ULL, 
            0x64589CE59D20A9ECULL, 0xBAE13FFDDBB767A7ULL, 0x65F6BEE1EE988143ULL, 0x14D25CE35A5F96E1ULL, 
            0x5E57D13EB5516768ULL, 0x2153F0CE550A30D9ULL, 0xB9900DF18BE92E56ULL, 0x9166E73454AED8AFULL, 
            0xDA3BAA11059E7B50ULL, 0x78C1D0898DB10CFAULL, 0x7936B19DB66DA759ULL, 0xFD70A54542D84B6BULL, 
            0xF34C360D55E5A031ULL, 0x4E1DF7DAEDD44FCBULL, 0xB5D2E5F4A6BA1EE2ULL, 0xB908531C045DC5DBULL, 
            0xBA61F8741DEECF97ULL, 0xD72EE56042B55692ULL, 0xDD60880B935C55E7ULL, 0xD28449FD7BB170BFULL, 
            0x11508EF1B4A6E4ADULL, 0xCA1785E488665970ULL, 0x543B2CFA506E4441ULL, 0x7CC8B6AAC73C6A90ULL
        },
        {
            0xA0E61F62BC2E5AA0ULL, 0x3A946349CEB4E880ULL, 0x4CE4D2CE72B8AC21ULL, 0x4909CC35CAC47DAFULL, 
            0xCF04C1EA3C6E9B30ULL, 0x876760253E9EAEDBULL, 0x62B86934F33F6B8AULL, 0x2C34679ECCC90836ULL, 
            0xE845B1B988B752DCULL, 0x6D1D779E6E069C89ULL, 0x020ECEB1C3B736CCULL, 0xBD66EEAD140B875AULL, 
            0x8B6964ADD4426053ULL, 0x5F73EE5017A76F66ULL, 0xFD5BD352C5E27DF2ULL, 0x35BA55B87A592D3AULL, 
            0x407487DE56BD1C1BULL, 0xAAE2439BB1FA0EF5ULL, 0xFED88A4D87077D50ULL, 0xAB00DADAA5C91191ULL, 
            0x60981E139F2AB606ULL, 0xE68323320898BF15ULL, 0x7F395380652EA6F4ULL, 0x38E8B69CD4C6E396ULL, 
            0x87E08A79A817D852ULL, 0x2E8E1A14AF9A814DULL, 0x13C7B8AA1634BBBDULL, 0xD16A2FBCE831EBE5ULL, 
            0x0BE328F07DD7AF9EULL, 0x79A834FB3B0AC4B1ULL, 0xCFFF744B202EA6E9ULL, 0xAEB8B469E97A1667ULL
        }
    },
    {
        {
            0xDF538236F8686A0AULL, 0xE1CF909978B14659ULL, 0x450D13098340FFA6ULL, 0x92987C6B78A04530ULL, 
            0xA53FCA1336C752C6ULL, 0x503DA2A999E3E731ULL, 0xF10A9A9E86AEED5DULL, 0x97CAFC2AC07A0401ULL, 
            0xE75F568CC5D3B964ULL, 0xABEA17202F544FD3ULL, 0x086BE0B47741F895ULL, 0x753D930F1AF08D14ULL, 
            0x6DE9953FAB7F4BA4ULL, 0x50C04EB96C455A0CULL, 0x209656AB5E845506ULL, 0x447166A18C594C3CULL, 
            0xBB59E1E06BF71E61ULL, 0x837F29F8B8653E18ULL, 0x28FFFB2236169AD2ULL, 0x62D6D2B722EEEEA3ULL, 
            0xDD225EE542E96331ULL, 0x7EBE3FAB332E362FULL, 0xA2139DC8CC492802ULL, 0xA930F1D9ACA2491CULL, 
            0x6CC406CF108D9EFFULL, 0x3C026C8A234EEE84ULL, 0x21E091122A5CF789ULL, 0xE3B167E4DC1ACF1CULL, 
            0xD37A16F801ACB969ULL, 0xD66540F3F509E666ULL, 0x74CDF3424058DC79ULL, 0xFA9900E33BBF6BBFULL
        },
        {
            0xEF024B871FDC040AULL, 0x5CAAE925CF428573ULL, 0x8239FEA36B1276D3ULL, 0xB6F109762D01DA11ULL, 
            0x0D35D85040517AC4ULL, 0x32F5572CFD282D05ULL, 0xC4B4A88D7170E1CBULL, 0xBFE2BCAC92ED4B09ULL, 
            0x9B7BC148C9B7A5D8ULL, 0x983AC09D242D8C79ULL, 0x3559D86DB7E9E724ULL, 0xB24A3FDC50A360B9ULL, 
            0xC69D92C1AE209252ULL, 0x7855019A193C9F34ULL, 0xCBDAA2DDEC9DCD4DULL, 0xDF82D25E66062A81ULL, 
            0xE365F11B10BF488DULL, 0xA5F25DAECF6D4482ULL, 0x556386961476ABF9ULL, 0xF49BA2187BD9C11BULL, 
            0x9E910D85E5AE0518ULL, 0x75A1676120C2AF49ULL, 0xD3ECCB56398D9AFAULL, 0xEA93D1FD548177C7ULL, 
            0x9E648D020E879094ULL, 0x15A0492E68AE7318ULL, 0xB688BAA19B8EB1F3ULL, 0x90891F8A33835C00ULL, 
            0x95111D3713872851ULL, 0x9525BCCBAD7D0B0CULL, 0xD10F1E5CB8C33D6EULL, 0x0CF98582C577342AULL
        },
        {
            0xECC64EC47CE70B5AULL, 0xB2341A869A40A23CULL, 0x3DA68F0B79D4CA11ULL, 0xA1702F44F7C6AF5EULL, 
            0x7CE26F566869E488ULL, 0x0A5ABF378EE66068ULL, 0x3692EB873C8C6A18ULL, 0x386FE310ADF13BE5ULL, 
            0x778CDA9E2B636F93ULL, 0x98E623B6F6726B7BULL, 0x459DC32408D04542ULL, 0xB01EF6C064D76DEDULL, 
            0x9B9C7FC280010D56ULL, 0x8363FFF520CCD303ULL, 0x948AE4A4BA725E31ULL, 0xCE7D3E9F23EED8AAULL, 
            0xA44D3992BF1EC401ULL, 0x28E706345688CD4DULL, 0xB47FA15C6DC62A82ULL, 0x83626365BCFC017AULL, 
            0x42D6FEFEF64C3CBAULL, 0xC4CB921849C81827ULL, 0x8F7E313EC0FE64C1ULL, 0xF08D4D01608092A0ULL, 
            0x818A1B59FB1D08F1ULL, 0xB9077A6BADE2D9F4ULL, 0x904D1129C0525348ULL, 0x82F9BD0013EF120FULL, 
            0x27B4716B0457C9BEULL, 0xF21D569306A94BC4ULL, 0x81544CD59ED8C17FULL, 0x4F0EED6D27758F99ULL
        },
        {
            0xAEE687F390FFE951ULL, 0x246BEA6EDC96073EULL, 0xC198F60B6BEA260FULL, 0xBBB0210149CBF85CULL, 
            0xE89B685DEAFD0A74ULL, 0x3F3E16C1D5B09D35ULL, 0x2782C0E35F0698DDULL, 0x881624CD10387723ULL, 
            0x61730DFCC4E00CEAULL, 0x6BE9FEC086E7EBF1ULL, 0xD55A52107D0E7F50ULL, 0x562FBE9A9FB4C7C0ULL, 
            0xF3D8717B07BB4700ULL, 0xBE38E4D280561BC1ULL, 0xFDA3F126CCF92E32ULL, 0xC32BFEFF85E48780ULL, 
            0x667A2F41EBA1412FULL, 0x1919F8B0128FC9F8ULL, 0xE3C31E18AC9637DDULL, 0x9D4D990B56569043ULL, 
            0x324687CE38A05518ULL, 0x8ADAEB4BC00DDDC6ULL, 0x6483B385E51CAA1CULL, 0xE93C9ED84C905541ULL, 
            0x388B6925AB5326F2ULL, 0x4BC6B6B6C4BC8070ULL, 0x2BBC87AA688370E8ULL, 0x6CEADFCF577ECFFDULL, 
            0x4717C9FB51D90002ULL, 0xAFEDD3F441A83701ULL, 0x73B57DA730E13C79ULL, 0xDAED5D402D4CF5BBULL
        },
        {
            0x7F5FD6D46ED62D6BULL, 0xE0AADC062DD1B22FULL, 0x551A0511DE0183C7ULL, 0x900B48F692EF9665ULL, 
            0x85A9E4204F11D2D6ULL, 0xD3FADF52C5B08E5FULL, 0x4B4A8FF2AC8E9FABULL, 0x416FC562BA6AF5C2ULL, 
            0xB8922D4D63332711ULL, 0xAE2890C936A1EB35ULL, 0xDDDA90D938E0A84CULL, 0xC6735D5ABCD15998ULL, 
            0x78A8829E21320C25ULL, 0x31B7F61393DAEF45ULL, 0x7BCDDE26C0915E86ULL, 0x8E5198F6FA4191BEULL, 
            0x822587AB2179F167ULL, 0xEDF3CDC816DA50D9ULL, 0xAC6706C3B9F7E1CCULL, 0x440D636714473593ULL, 
            0x67728E10C500913FULL, 0x3632A2D97E44D9C5ULL, 0x47FA0EBFADCC1ED8ULL, 0xA878C5CB822FE3AFULL, 
            0xC8DF939B6A9C5ABDULL, 0xF8D76CACEBDEC1F1ULL, 0xD8AEE9BB66EEA0CCULL, 0xAE8101B51438EFA2ULL, 
            0x10DDC3535D525858ULL, 0x0B3D4747BC07629CULL, 0x8F9CF85F2C045352ULL, 0xB86D638B9E9F93CBULL
        },
        {
            0x35079C8FBAF9F1C7ULL, 0x710F938B51C73AC9ULL, 0x9A313FD9417D646DULL, 0x2D5A720F9D827077ULL, 
            0x20C6CFD3D6909550ULL, 0xA2A02731B6968ECDULL, 0xBADFAB8B3119E5A6ULL, 0x31F8DB22FDCD8B55ULL, 
            0xDFC4D0B3B74FE5A6ULL, 0x055B60F5FED35DADULL, 0xB328546CEC5CC902ULL, 0x6D7A8F4E63D804B5ULL, 
            0x9FBD832352DCCD50ULL, 0xD4A8980B50FAC342ULL, 0xAF32919631EE7475ULL, 0x554FD5C523D3EE7DULL, 
            0x121A58103135FCE0ULL, 0xFC505BDBEC25283AULL, 0xC04B27C8C649DC22ULL, 0xA3F087B83B0AB9E8ULL, 
            0x7CBEFB14DE81E11FULL, 0xEFE7B5C0FE486424ULL, 0x9DEACDB9DE508435ULL, 0xC1A7E6CF3C4147F3ULL, 
            0x16A7D1C09E87ECC7ULL, 0xB2C604292A0472D3ULL, 0x4EBBF42FDF523F14ULL, 0xBF240B18DA0331ADULL, 
            0x10584651AF9F05FFULL, 0x1B6ADA2F49A9843AULL, 0xA2BBD527B469F568ULL, 0xC0CE58E68EC3A75CULL
        }
    }
};

const TwistDomainConstants TwistExpander_Alcor::kPhaseHConstants = {
    0x0773F66480912D9EULL,
    0x4D40A715B93E6586ULL,
    0xC26AA86927F63F3EULL,
    0x0773F66480912D9EULL,
    0x4D40A715B93E6586ULL,
    0xC26AA86927F63F3EULL,
    0xA0B766A0FECAE12DULL,
    0x9F68F503FC3DE7B6ULL,
    0x88,
    0x61,
    0xE0,
    0x02,
    0x2B,
    0x14,
    0x70,
    0x5E
};

