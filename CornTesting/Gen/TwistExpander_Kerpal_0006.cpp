#include "TwistExpander_Kerpal_0006.hpp"
#include "TwistFunctional.hpp"
#include "TwistIndexShuffle.hpp"
#include "TwistMix64.hpp"
#include "TwistFarmSalt.hpp"
#include "TwistFarmConstants.hpp"
#include "TwistInvest.hpp"
#include "TwistMemory.hpp"
#include "TwistShiftBox.hpp"
#include "TwistSnow.hpp"
#include "TwistMasking.hpp"

#include <cstring>

TwistExpander_Kerpal_0006::TwistExpander_Kerpal_0006()
: TwistExpander() {
    mDomainBundleInbuilt.mPhaseASalts = kPhaseASalts;
    mDomainBundleInbuilt.mPhaseAConstants = kPhaseAConstants;
    mDomainBundleInbuilt.mPhaseBSalts = kPhaseBSalts;
    mDomainBundleInbuilt.mPhaseBConstants = kPhaseBConstants;
    mDomainBundleInbuilt.mPhaseCSalts = kPhaseCSalts;
    mDomainBundleInbuilt.mPhaseCConstants = kPhaseCConstants;
    std::memcpy(&mDomainBundleEphemeral, &mDomainBundleInbuilt, sizeof(mDomainBundleEphemeral));
}

void TwistExpander_Kerpal_0006::KDF_A(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet) {
    TwistExpander::KDF_A(pNonce, pConstants, pDomainSaltSet);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (mSource == nullptr) ||
        (pConstants == nullptr) || (pDomainSaltSet == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aSource = mSource;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::size_t *aIndexList256A = mIndexList256A;
    [[maybe_unused]] std::size_t *aIndexList256B = mIndexList256B;
    [[maybe_unused]] std::size_t *aIndexList256C = mIndexList256C;
    [[maybe_unused]] std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0; std::uint64_t aIngress = 0; std::uint64_t aCross = 0; std::uint64_t aScatter = 0;
    std::uint64_t aCarry = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    std::uint64_t aWandererA = 0; std::uint64_t aWandererB = 0; std::uint64_t aWandererC = 0; std::uint64_t aWandererD = 0;
    std::uint64_t aWandererE = 0; std::uint64_t aWandererF = 0; std::uint64_t aWandererG = 0; std::uint64_t aWandererH = 0;
    std::uint64_t aWandererI = 0; std::uint64_t aWandererJ = 0; std::uint64_t aWandererK = 0;

    std::uint64_t aMatrixOperationIndex = 0; std::uint64_t aMatrixWriteIndex = 0; std::uint64_t aMatrixSlotA = 0; std::uint64_t aMatrixSlotB = 0;
    std::uint64_t aMatrixLoadIndexA = 0; std::uint64_t aMatrixLoadIndexB = 0; std::uint64_t aSelect = 0; std::uint64_t aMatrixArgA = 0;
    std::uint64_t aMatrixArgC = 0; std::uint64_t aMatrixArgD = 0; std::uint64_t aMatrixUnrollWordA = 0; std::uint64_t aMatrixUnrollWordB = 0;
    std::uint64_t aMatrixStoreIndexA = 0; std::uint64_t aMatrixStoreIndexB = 0; std::uint64_t aMatrixArgB = 0;

    // [gseed-run-kdf2]
    [[maybe_unused]] std::uint64_t aNonceByteA = ((pNonce >> 0U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteB = ((pNonce >> 8U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteC = ((pNonce >> 16U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteD = ((pNonce >> 24U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteE = ((pNonce >> 32U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteF = ((pNonce >> 40U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteG = ((pNonce >> 48U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteH = ((pNonce >> 56U) & 0xFFULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    std::uint8_t aDomainWordMaskMutateA = pConstants->mMaskMutateA;
    std::uint8_t aDomainWordMaskMutateB = pConstants->mMaskMutateB;
    std::uint64_t aDomainWordMatrixSelectA = pConstants->mMatrixSelectA;
    std::uint64_t aDomainWordMatrixSelectB = pConstants->mMatrixSelectB;
    std::uint8_t aDomainWordMatrixUnrollA = pConstants->mMatrixUnrollA;
    std::uint8_t aDomainWordMatrixUnrollB = pConstants->mMatrixUnrollB;
    std::uint8_t aDomainWordMatrixArgA = pConstants->mMatrixArgA;
    std::uint8_t aDomainWordMatrixArgB = pConstants->mMatrixArgB;
    std::uint8_t aDomainWordMatrixArgC = pConstants->mMatrixArgC;
    std::uint8_t aDomainWordMatrixArgD = pConstants->mMatrixArgD;
    {
        aPrevious = 9673793563131396997U;
        aCarry = 16203061942379121665U;
        aWandererA = 16809442251481487926U;
        aWandererB = 15668729676825263146U;
        aWandererC = 9583347455851900959U;
        aWandererD = 14169380248046336635U;
        aWandererE = 13749724987825716574U;
        aWandererF = 9875640635543856066U;
        aWandererG = 11890027443267427355U;
        aWandererH = 15353983174607372539U;
        aWandererI = 10327801579765441093U;
        aWandererJ = 16385893629451064958U;
        aWandererK = 17457262505774271804U;
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 23U) ^ RotL64(aNonceByteD, 60U));
            aIngress = aIngress ^ (RotL64(aSource[((aIndex + 9549U)) & S_BLOCK1], 39U) ^ RotL64(mSnow[((aIndex + 25441U)) & S_BLOCK1], 5U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteH, 57U) ^ RotL64(aNonceByteE, 47U)) ^ RotL64(aNonceByteC, 5U));
            aCross = aCross ^ (RotL64(mSnow[((S_BLOCK1 - aIndex + 5632U)) & S_BLOCK1], 36U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 1952U)) & S_BLOCK1], 27U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 52U) + RotL64(aPrevious, 3U)) + (RotL64(aCarry, 23U) ^ RotL64(aIngress, 35U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterG = ((aWandererA + RotL64(aIngress, 48U)) + RotL64(aCarry, 51U)) + 5697928251815176134U;
            aOrbiterJ = ((aWandererG + RotL64(aCross, 11U)) + RotL64(aCarry, 19U)) + 337587740689259575U;
            aOrbiterK = ((aWandererE + RotL64(aPrevious, 19U)) + RotL64(aCarry, 39U)) + 4927686903263973950U;
            aOrbiterE = (((aWandererB + RotL64(aScatter, 57U)) + 3742409032569801033U) + aOrbiterAssignSaltF[(((31U - aIndex) + 6929U)) & S_SALT1]) + RotL64(aNonceByteF, 47U);
            aOrbiterB = (((aWandererC + RotL64(aPrevious, 39U)) + 1608092659172197650U) + aOrbiterAssignSaltB[(((31U - aIndex) + 661U)) & S_SALT1]) + RotL64(aNonceByteA, 7U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterJ) + 15848744267145717509U) + RotL64(aNonceByteG, 61U);
            aOrbiterK = ((aOrbiterK ^ aOrbiterG) ^ 15300174177963339253U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 4330U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 5771922862677667319U), 11U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterB) + 14162868453323648628U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterE) ^ 12020167069983729869U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 2343U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 2071080217680099017U), 3U);
            //
            aOrbiterJ = (((aOrbiterJ + aOrbiterK) + 16259538291658723956U) + aOrbiterUpdateSaltB[((aIndex + 1097U)) & S_SALT1]) + RotL64(aNonceByteE, 14U);
            aOrbiterE = ((aOrbiterE ^ aOrbiterJ) ^ 8516686212464112245U) ^ aOrbiterUpdateSaltD[((aIndex + 6511U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 4731296903548893627U), 57U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterG) + 3722184575520553132U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterB) ^ 5663609293306386784U;
            aOrbiterJ = RotL64((aOrbiterJ * 14364218128780764749U), 21U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterE) + 15265344442454471986U;
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 3050323350098829515U;
            aOrbiterB = RotL64((aOrbiterB * 5890624677162388135U), 41U);
            //
            aIngress = RotL64(aOrbiterJ, 19U) ^ aOrbiterE;
            aIngress = aIngress + (aOrbiterB ^ RotL64(aOrbiterG, 29U));
            aIngress = aIngress + RotL64(aOrbiterK, 56U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererE = aWandererE + ((((RotL64(aCross, 47U) + aOrbiterJ) + RotL64(aOrbiterB, 21U)) + RotL64(aCarry, 37U)) + RotL64(aNonceByteB, 27U));
            aWandererB = aWandererB ^ (((RotL64(aPrevious, 35U) + aOrbiterE) + RotL64(aOrbiterJ, 47U)) + aWandererUpdateSaltD[(((31U - aIndex) + 5142U)) & S_SALT1]);
            aWandererC = aWandererC + (((RotL64(aIngress, 23U) + RotL64(aOrbiterG, 36U)) + aOrbiterK) + RotL64(aCarry, 5U));
            aWandererA = aWandererA ^ (((RotL64(aScatter, 5U) + RotL64(aOrbiterB, 57U)) + aOrbiterK) + aWandererUpdateSaltA[((aIndex + 5369U)) & S_SALT1]);
            aWandererG = aWandererG + (((RotL64(aIngress, 58U) + RotL64(aOrbiterB, 13U)) + aOrbiterG) + RotL64(aNonceByteD, 39U));
            //
            aCarry = aCarry + (RotL64(aWandererC, 13U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererG, 37U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererE, 51U);
            aCarry = aCarry + RotL64(aIngress, 60U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteD, 5U) ^ RotL64(aNonceByteC, 39U)) ^ RotL64(aNonceByteG, 29U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 17661U)) & S_BLOCK1], 18U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 14930U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteB, 23U) ^ RotL64(aNonceByteE, 3U)) ^ RotL64(aNonceByteA, 57U));
            aCross = aCross ^ (RotL64(mSnow[((S_BLOCK1 - aIndex + 9157U)) & S_BLOCK1], 46U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 1908U)) & S_BLOCK1], 13U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 23U) ^ RotL64(aCross, 35U)) + (RotL64(aCarry, 3U) + RotL64(aPrevious, 48U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = (((aWandererK + RotL64(aScatter, 21U)) + RotL64(aCarry, 23U)) + 12775735908960052604U) + RotL64(aNonceByteD, 59U);
            aOrbiterK = ((aWandererD + RotL64(aPrevious, 13U)) + 11791373812080296887U) + aOrbiterAssignSaltC[(((31U - aIndex) + 6595U)) & S_SALT1];
            aOrbiterC = (aWandererE + RotL64(aIngress, 34U)) + 5537362877706057303U;
            aOrbiterJ = (((aWandererB + RotL64(aCross, 43U)) + RotL64(aCarry, 39U)) + 2023912048504189380U) + RotL64(aNonceByteF, 3U);
            aOrbiterI = (((aWandererH + RotL64(aPrevious, 5U)) + RotL64(aCarry, 11U)) + 17668828109963766893U) + aOrbiterAssignSaltD[((aIndex + 7539U)) & S_SALT1];
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 558908629933941224U;
            aOrbiterC = (((aOrbiterC ^ aOrbiterF) ^ 1479633119685446888U) ^ aOrbiterUpdateSaltE[((aIndex + 1909U)) & S_SALT1]) ^ RotL64(aNonceByteA, 14U);
            aOrbiterC = RotL64((aOrbiterC * 4447153373540811385U), 39U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterJ) + 15460320397843364063U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 87U)) & S_SALT1];
            aOrbiterI = (((aOrbiterI ^ aOrbiterK) ^ 10059749397555469054U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 1355U)) & S_SALT1]) ^ RotL64(aNonceByteE, 53U);
            aOrbiterI = RotL64((aOrbiterI * 8671817118586065469U), 21U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterC) + 9987633811929693924U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterJ) ^ 10087337844580228269U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 2602U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 13817142288940843815U), 5U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterI) + 4446204415503364254U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 15106063243302192717U;
            aOrbiterK = RotL64((aOrbiterK * 13273756657334709803U), 47U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 9430197906134676162U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 1226048679997253363U;
            aOrbiterJ = RotL64((aOrbiterJ * 14247538885252664127U), 57U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterJ, 53U);
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterC, 40U));
            aIngress = aIngress + RotL64(aOrbiterI, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererD = aWandererD ^ (((RotL64(aScatter, 39U) + RotL64(aOrbiterJ, 58U)) + aOrbiterK) + RotL64(aNonceByteC, 25U));
            aWandererE = aWandererE + ((((RotL64(aPrevious, 21U) + RotL64(aOrbiterC, 47U)) + aOrbiterI) + RotL64(aCarry, 3U)) + RotL64(aNonceByteH, 57U));
            aWandererK = aWandererK ^ (((RotL64(aCross, 3U) + RotL64(aOrbiterI, 19U)) + aOrbiterF) + aWandererUpdateSaltB[((aIndex + 5133U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aIngress, 51U) + RotL64(aOrbiterF, 5U)) + aOrbiterK) + RotL64(aCarry, 53U));
            aWandererB = aWandererB ^ (((RotL64(aCross, 30U) + RotL64(aOrbiterJ, 35U)) + aOrbiterF) + aWandererUpdateSaltC[((aIndex + 22U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererD, 27U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererE, 3U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererB, 48U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteH, 43U) ^ RotL64(aNonceByteD, 29U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 6029U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneA[((aIndex + 8999U)) & S_BLOCK1], 60U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteE, 43U) ^ RotL64(aNonceByteF, 35U)) ^ RotL64(aNonceByteG, 27U));
            aCross = aCross ^ (RotL64(aSource[((S_BLOCK1 - aIndex + 14280U)) & S_BLOCK1], 14U) ^ RotL64(mSnow[((aIndex + 2802U)) & S_BLOCK1], 57U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 35U) + RotL64(aPrevious, 13U)) + (RotL64(aIngress, 60U) ^ RotL64(aCross, 47U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterE = ((aWandererK + RotL64(aCross, 53U)) + RotL64(aCarry, 51U)) + 17264605017518259932U;
            aOrbiterD = ((aWandererF + RotL64(aIngress, 27U)) + 15209184354580778643U) + aOrbiterAssignSaltE[((aIndex + 6129U)) & S_SALT1];
            aOrbiterJ = (((aWandererB + RotL64(aScatter, 5U)) + RotL64(aCarry, 21U)) + 3299527965014731384U) + RotL64(aNonceByteA, 7U);
            aOrbiterH = ((((aWandererA + RotL64(aPrevious, 40U)) + RotL64(aCarry, 35U)) + 16293096431816127821U) + aOrbiterAssignSaltA[(((31U - aIndex) + 1259U)) & S_SALT1]) + RotL64(aNonceByteE, 42U);
            aOrbiterF = (aWandererI + RotL64(aScatter, 13U)) + 11031983436878828337U;
            //
            aOrbiterE = ((aOrbiterE + aOrbiterD) + 9188018632448236358U) + aOrbiterUpdateSaltA[((aIndex + 1514U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterE) ^ 13420816400363406556U) ^ RotL64(aNonceByteB, 61U);
            aOrbiterJ = RotL64((aOrbiterJ * 10958221259662190519U), 47U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 2485063384097917101U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 1197U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 3089135816938128264U;
            aOrbiterD = RotL64((aOrbiterD * 8813152992957361153U), 37U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterH) + 10730544971770435788U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 5543U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterF) ^ 10431767565618874806U;
            aOrbiterE = RotL64((aOrbiterE * 4723078464590561545U), 21U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 14883796491656899074U;
            aOrbiterH = ((aOrbiterH ^ aOrbiterJ) ^ 13465877783538483706U) ^ RotL64(aNonceByteD, 55U);
            aOrbiterH = RotL64((aOrbiterH * 14311686051108108503U), 13U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterJ) + 13322163435314643713U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterD) ^ 3307316600284371955U) ^ aOrbiterUpdateSaltB[((aIndex + 1769U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 12337846092069506365U), 57U);
            //
            aIngress = RotL64(aOrbiterF, 21U) ^ aOrbiterH;
            aIngress = aIngress + (RotL64(aOrbiterE, 37U) ^ aOrbiterD);
            aIngress = aIngress + RotL64(aOrbiterJ, 47U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA ^ (((RotL64(aCross, 3U) + aOrbiterH) + RotL64(aOrbiterF, 29U)) + RotL64(aNonceByteF, 19U));
            aWandererK = aWandererK + (((((RotL64(aScatter, 11U) + RotL64(aOrbiterH, 53U)) + aOrbiterE) + RotL64(aCarry, 53U)) + RotL64(aNonceByteC, 41U)) + aWandererUpdateSaltF[((aIndex + 3280U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aIngress, 51U) + aOrbiterJ) + RotL64(aOrbiterD, 20U));
            aWandererF = aWandererF + (((RotL64(aPrevious, 38U) + aOrbiterD) + RotL64(aOrbiterE, 5U)) + RotL64(aCarry, 13U));
            aWandererI = aWandererI ^ (((RotL64(aCross, 27U) + RotL64(aOrbiterJ, 37U)) + aOrbiterH) + aWandererUpdateSaltE[(((31U - aIndex) + 7811U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererK, 21U));
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererF, 56U));
            aCarry = aCarry + RotL64(aWandererB, 13U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteF, 13U) ^ RotL64(aNonceByteG, 60U)) ^ RotL64(aNonceByteC, 47U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 19206U)) & S_BLOCK1], 29U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 2659U)) & S_BLOCK1], 21U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteD, 19U) ^ RotL64(aNonceByteB, 43U)) ^ RotL64(aNonceByteA, 28U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 17779U)) & S_BLOCK1], 57U) ^ RotL64(aSource[((S_BLOCK1 - aIndex + 29996U)) & S_BLOCK1], 5U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 37U) + RotL64(aIngress, 19U)) + (RotL64(aCross, 50U) ^ RotL64(aPrevious, 3U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterB = (((aWandererF + RotL64(aPrevious, 54U)) + RotL64(aCarry, 11U)) + 3339283916456813609U) + aOrbiterAssignSaltF[(((31U - aIndex) + 7242U)) & S_SALT1];
            aOrbiterH = (aWandererD + RotL64(aCross, 23U)) + 11339086426180649584U;
            aOrbiterK = (aWandererH + RotL64(aIngress, 37U)) + 16819191669329316585U;
            aOrbiterF = (((aWandererI + RotL64(aScatter, 3U)) + RotL64(aCarry, 23U)) + 8361916937762630725U) + RotL64(aNonceByteF, 12U);
            aOrbiterD = ((((aWandererJ + RotL64(aCross, 11U)) + RotL64(aCarry, 41U)) + 18031328374429899857U) + aOrbiterAssignSaltB[((aIndex + 8163U)) & S_SALT1]) + RotL64(pNonce, 29U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterH) + 18261756894092897276U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 5359U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterB) ^ 4250319792907645666U;
            aOrbiterK = RotL64((aOrbiterK * 7053489184750217963U), 51U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterD) + 1492411503643460886U) + RotL64(aNonceByteC, 19U);
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 17369549067879344180U;
            aOrbiterB = RotL64((aOrbiterB * 2947354306696216579U), 43U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterK) + 7301713524358676722U) + RotL64(aNonceByteE, 41U);
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 2985193736033012535U) ^ aOrbiterUpdateSaltE[((aIndex + 3987U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 7473297294949338265U), 21U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterB) + 14086975808140927408U) + aOrbiterUpdateSaltB[((aIndex + 7450U)) & S_SALT1];
            aOrbiterH = ((aOrbiterH ^ aOrbiterD) ^ 10390516547834639800U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 2201U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 11441293212275890819U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterF) + 18205555540941493267U;
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 16967799565443938873U;
            aOrbiterD = RotL64((aOrbiterD * 3009081009044782443U), 3U);
            //
            aIngress = RotL64(aOrbiterF, 23U) ^ aOrbiterH;
            aIngress = aIngress + (aOrbiterK ^ RotL64(aOrbiterB, 57U));
            aIngress = aIngress + RotL64(aOrbiterD, 4U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererI = aWandererI + (((RotL64(aPrevious, 13U) + aOrbiterH) + RotL64(aOrbiterB, 19U)) + RotL64(aCarry, 35U));
            aWandererD = aWandererD ^ ((((RotL64(aIngress, 37U) + aOrbiterF) + RotL64(aOrbiterK, 5U)) + RotL64(aNonceByteH, 59U)) + aWandererUpdateSaltD[(((31U - aIndex) + 5835U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aCross, 51U) + RotL64(aOrbiterD, 29U)) + aOrbiterB) + aWandererUpdateSaltA[(((31U - aIndex) + 2417U)) & S_SALT1]);
            aWandererF = aWandererF ^ (((RotL64(aScatter, 22U) + RotL64(aOrbiterH, 37U)) + aOrbiterK) + RotL64(aNonceByteD, 53U));
            aWandererJ = aWandererJ + (((RotL64(aIngress, 3U) + aOrbiterF) + RotL64(aOrbiterD, 52U)) + RotL64(aCarry, 19U));
            //
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererH, 29U));
            aCarry = aCarry + (RotL64(aWandererD, 39U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererF, 47U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteG, 3U) ^ RotL64(aNonceByteC, 53U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 7552U)) & S_BLOCK1], 12U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 32590U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteB, 12U) ^ RotL64(aNonceByteD, 27U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 3016U)) & S_BLOCK1], 53U) ^ RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 19852U)) & S_BLOCK1], 3U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 5U) + RotL64(aCarry, 38U)) ^ (RotL64(aCross, 53U) + RotL64(aIngress, 19U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = (((aWandererH + RotL64(aCross, 21U)) + RotL64(aCarry, 39U)) + 12775735908960052604U) + aOrbiterAssignSaltE[((aIndex + 6875U)) & S_SALT1];
            aOrbiterC = ((aWandererA + RotL64(aPrevious, 53U)) + RotL64(aCarry, 57U)) + 11791373812080296887U;
            aOrbiterE = (((aWandererB + RotL64(aIngress, 29U)) + RotL64(aCarry, 21U)) + 5537362877706057303U) + RotL64(aNonceByteE, 17U);
            aOrbiterK = (aWandererK + RotL64(aScatter, 43U)) + 2023912048504189380U;
            aOrbiterI = (((aWandererE + RotL64(aCross, 6U)) + 17668828109963766893U) + aOrbiterAssignSaltB[((aIndex + 111U)) & S_SALT1]) + RotL64(aNonceByteD, 47U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 558908629933941224U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 5732U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterA) ^ 1479633119685446888U;
            aOrbiterE = RotL64((aOrbiterE * 4447153373540811385U), 37U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterI) + 15460320397843364063U;
            aOrbiterA = (((aOrbiterA ^ aOrbiterK) ^ 10059749397555469054U) ^ aOrbiterUpdateSaltE[((aIndex + 3267U)) & S_SALT1]) ^ RotL64(aNonceByteA, 18U);
            aOrbiterA = RotL64((aOrbiterA * 8671817118586065469U), 3U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 9987633811929693924U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 10087337844580228269U;
            aOrbiterK = RotL64((aOrbiterK * 13817142288940843815U), 13U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterA) + 4446204415503364254U) + aOrbiterUpdateSaltF[((aIndex + 2024U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterI) ^ 15106063243302192717U;
            aOrbiterC = RotL64((aOrbiterC * 13273756657334709803U), 53U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 9430197906134676162U) + RotL64(aNonceByteF, 15U);
            aOrbiterI = ((aOrbiterI ^ aOrbiterE) ^ 1226048679997253363U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 5232U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 14247538885252664127U), 29U);
            //
            aIngress = aOrbiterK ^ RotL64(aOrbiterI, 40U);
            aIngress = aIngress + (RotL64(aOrbiterC, 13U) ^ aOrbiterE);
            aIngress = aIngress + RotL64(aOrbiterA, 3U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererK = aWandererK ^ ((RotL64(aPrevious, 27U) + RotL64(aOrbiterA, 53U)) + aOrbiterK);
            aWandererE = aWandererE + ((((RotL64(aIngress, 57U) + RotL64(aOrbiterI, 12U)) + aOrbiterA) + RotL64(aCarry, 53U)) + RotL64(aNonceByteB, 41U));
            aWandererH = aWandererH ^ (((RotL64(aCross, 10U) + aOrbiterA) + RotL64(aOrbiterE, 3U)) + aWandererUpdateSaltF[((aIndex + 7187U)) & S_SALT1]);
            aWandererB = aWandererB + ((((RotL64(aScatter, 43U) + aOrbiterC) + RotL64(aOrbiterA, 37U)) + RotL64(aCarry, 27U)) + RotL64(aNonceByteH, 7U));
            aWandererA = aWandererA ^ (((RotL64(aPrevious, 35U) + RotL64(aOrbiterC, 27U)) + aOrbiterI) + aWandererUpdateSaltD[((aIndex + 4838U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererB ^ RotL64(aWandererA, 43U));
            aCarry = aCarry + (RotL64(aWandererH, 35U) ^ aWandererK);
            aCarry = aCarry + RotL64(aWandererE, 53U);
            aCarry = aCarry + RotL64(aIngress, 12U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteG, 13U) ^ RotL64(aNonceByteC, 47U));
            aIngress = aIngress ^ (RotL64(aOperationLaneA[((aIndex + 17349U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneD[((aIndex + 30239U)) & S_BLOCK1], 38U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteA, 41U) ^ RotL64(aNonceByteF, 4U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 2547U)) & S_BLOCK1], 13U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 17697U)) & S_BLOCK1], 21U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 29U) + RotL64(aIngress, 58U)) + (RotL64(aPrevious, 43U) ^ RotL64(aCross, 11U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = ((((aWandererD + RotL64(aIngress, 36U)) + RotL64(aCarry, 3U)) + 11274974230580265396U) + aOrbiterAssignSaltF[((aIndex + 313U)) & S_SALT1]) + RotL64(aNonceByteB, 29U);
            aOrbiterC = (((aWandererH + RotL64(aScatter, 21U)) + RotL64(aCarry, 41U)) + 16658438747342741547U) + RotL64(aNonceByteH, 55U);
            aOrbiterF = (((aWandererB + RotL64(aPrevious, 3U)) + RotL64(aCarry, 23U)) + 16612986966106053844U) + aOrbiterAssignSaltD[(((31U - aIndex) + 2771U)) & S_SALT1];
            aOrbiterI = (aWandererK + RotL64(aCross, 53U)) + 9329502236843231290U;
            aOrbiterD = (aWandererJ + RotL64(aPrevious, 13U)) + 14088261356708344656U;
            //
            aOrbiterA = ((aOrbiterA + aOrbiterC) + 13692608802007789581U) + aOrbiterUpdateSaltB[((aIndex + 5675U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterA) ^ 6824473946645682398U;
            aOrbiterF = RotL64((aOrbiterF * 13619437545775237601U), 3U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 2072915876348570040U) + RotL64(aNonceByteE, 9U);
            aOrbiterD = (aOrbiterD ^ aOrbiterC) ^ 7420507753044460759U;
            aOrbiterD = RotL64((aOrbiterD * 13239288539564571257U), 19U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 4677557318688502593U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterI) ^ 15081678577055628459U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 1883U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 16659305295251177155U), 27U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterD) + 7026792817486507482U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterF) ^ 14871665922943969918U) ^ aOrbiterUpdateSaltE[((aIndex + 3815U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 694073180313083145U), 11U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 6807734532159292872U;
            aOrbiterI = (((aOrbiterI ^ aOrbiterD) ^ 17882797335141303280U) ^ aOrbiterUpdateSaltC[((aIndex + 3889U)) & S_SALT1]) ^ RotL64(aNonceByteF, 23U);
            aOrbiterI = RotL64((aOrbiterI * 15439872930381050291U), 43U);
            //
            aIngress = aOrbiterD ^ RotL64(aOrbiterI, 3U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterA, 34U));
            aIngress = aIngress + RotL64(aOrbiterF, 47U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererK = aWandererK + (((RotL64(aCross, 44U) + aOrbiterC) + RotL64(aOrbiterA, 47U)) + RotL64(aNonceByteD, 47U));
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 57U) + aOrbiterA) + RotL64(aOrbiterI, 3U)) + aWandererUpdateSaltB[(((31U - aIndex) + 55U)) & S_SALT1]);
            aWandererB = aWandererB + ((((RotL64(aPrevious, 35U) + aOrbiterD) + RotL64(aOrbiterF, 23U)) + RotL64(aCarry, 51U)) + RotL64(pNonce, 10U));
            aWandererD = aWandererD ^ (((RotL64(aIngress, 13U) + RotL64(aOrbiterA, 56U)) + aOrbiterD) + aWandererUpdateSaltC[(((31U - aIndex) + 2252U)) & S_SALT1]);
            aWandererH = aWandererH + (((RotL64(aCross, 5U) + RotL64(aOrbiterC, 37U)) + aOrbiterI) + RotL64(aCarry, 37U));
            //
            aCarry = aCarry + (RotL64(aWandererH, 48U) ^ aWandererD);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererB, 57U));
            aCarry = aCarry + RotL64(aWandererK, 3U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteD, 3U) ^ RotL64(aNonceByteC, 11U)) ^ RotL64(aNonceByteH, 53U));
            aIngress = aIngress ^ (RotL64(aOperationLaneB[((aIndex + 12023U)) & S_BLOCK1], 37U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 29459U)) & S_BLOCK1], 20U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteE, 30U) ^ RotL64(aNonceByteG, 47U));
            aCross = aCross ^ (RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 11923U)) & S_BLOCK1], 57U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 6853U)) & S_BLOCK1], 13U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 47U) + RotL64(aCarry, 5U)) ^ (RotL64(aCross, 35U) + RotL64(aPrevious, 18U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterD = (((aWandererB + RotL64(aScatter, 13U)) + 10336802574069791273U) + aOrbiterAssignSaltC[(((31U - aIndex) + 470U)) & S_SALT1]) + RotL64(aNonceByteF, 22U);
            aOrbiterC = ((aWandererH + RotL64(aIngress, 47U)) + RotL64(aCarry, 29U)) + 169025388197058936U;
            aOrbiterG = (((aWandererG + RotL64(aPrevious, 57U)) + RotL64(aCarry, 13U)) + 6541354188379168846U) + RotL64(aNonceByteA, 39U);
            aOrbiterK = ((aWandererJ + RotL64(aCross, 24U)) + RotL64(aCarry, 41U)) + 16223920526599306104U;
            aOrbiterE = ((aWandererE + RotL64(aScatter, 3U)) + 12756613707692514808U) + aOrbiterAssignSaltA[(((31U - aIndex) + 201U)) & S_SALT1];
            //
            aOrbiterD = (((aOrbiterD + aOrbiterC) + 5082475548176484035U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 6107U)) & S_SALT1]) + RotL64(aNonceByteG, 3U);
            aOrbiterG = ((aOrbiterG ^ aOrbiterD) ^ 4907435526952698526U) ^ aOrbiterUpdateSaltD[((aIndex + 4124U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 1379692095754989215U), 11U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterD) + 14236627073831834337U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterK) ^ 11502511046130497584U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 6277U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 3460330807286625917U), 27U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterK) + 3679044835550219497U) + aOrbiterUpdateSaltB[((aIndex + 3562U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterE) ^ 11254838916686736746U;
            aOrbiterD = RotL64((aOrbiterD * 8631695922983532915U), 57U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterE) + 10582608424233200966U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterG) ^ 10449735026385340313U) ^ RotL64(aNonceByteH, 61U);
            aOrbiterK = RotL64((aOrbiterK * 7363770199734997411U), 35U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterG) + 4628253464169957835U;
            aOrbiterE = (aOrbiterE ^ aOrbiterC) ^ 17664454668473204465U;
            aOrbiterE = RotL64((aOrbiterE * 4234720298731378527U), 47U);
            //
            aIngress = aOrbiterG ^ RotL64(aOrbiterD, 19U);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterK, 57U));
            aIngress = aIngress + RotL64(aOrbiterC, 34U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererG = aWandererG ^ (((RotL64(aPrevious, 5U) + RotL64(aOrbiterD, 23U)) + aOrbiterC) + RotL64(aNonceByteB, 19U));
            aWandererE = aWandererE + ((((RotL64(aScatter, 41U) + RotL64(aOrbiterE, 37U)) + aOrbiterK) + RotL64(aCarry, 5U)) + aWandererUpdateSaltE[(((31U - aIndex) + 7417U)) & S_SALT1]);
            aWandererB = aWandererB ^ (((RotL64(aCross, 29U) + aOrbiterG) + RotL64(aOrbiterC, 13U)) + RotL64(aNonceByteC, 7U));
            aWandererH = aWandererH + (((RotL64(aIngress, 56U) + RotL64(aOrbiterG, 57U)) + aOrbiterE) + RotL64(aCarry, 23U));
            aWandererJ = aWandererJ ^ (((RotL64(aScatter, 13U) + aOrbiterE) + RotL64(aOrbiterC, 46U)) + aWandererUpdateSaltA[(((31U - aIndex) + 6375U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererE, 21U));
            aCarry = aCarry + (RotL64(aWandererG, 29U) ^ aWandererB);
            aCarry = aCarry + RotL64(aWandererH, 39U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteH, 4U) ^ RotL64(aNonceByteD, 53U));
            aIngress = aIngress ^ (RotL64(aOperationLaneC[((aIndex + 1792U)) & S_BLOCK1], 13U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 19478U)) & S_BLOCK1], 23U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteG, 57U) ^ RotL64(aNonceByteB, 40U));
            aCross = aCross ^ (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 1827U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneD[((aIndex + 18942U)) & S_BLOCK1], 23U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 37U) ^ RotL64(aCross, 53U)) + (RotL64(aPrevious, 20U) ^ RotL64(aCarry, 3U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterB = ((aWandererH + RotL64(aScatter, 19U)) + 3339283916456813609U) + aOrbiterAssignSaltE[(((31U - aIndex) + 4950U)) & S_SALT1];
            aOrbiterC = ((aWandererK + RotL64(aCross, 37U)) + RotL64(aCarry, 27U)) + 11339086426180649584U;
            aOrbiterI = ((((aWandererB + RotL64(aPrevious, 29U)) + RotL64(aCarry, 13U)) + 16819191669329316585U) + aOrbiterAssignSaltB[(((31U - aIndex) + 7035U)) & S_SALT1]) + RotL64(aNonceByteA, 31U);
            aOrbiterF = ((aWandererI + RotL64(aIngress, 5U)) + RotL64(aCarry, 47U)) + 8361916937762630725U;
            aOrbiterA = ((aWandererA + RotL64(aCross, 60U)) + 18031328374429899857U) + RotL64(aNonceByteG, 18U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterC) + 18261756894092897276U;
            aOrbiterI = (((aOrbiterI ^ aOrbiterB) ^ 4250319792907645666U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 4963U)) & S_SALT1]) ^ RotL64(aNonceByteD, 37U);
            aOrbiterI = RotL64((aOrbiterI * 7053489184750217963U), 5U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterA) + 1492411503643460886U;
            aOrbiterB = (aOrbiterB ^ aOrbiterF) ^ 17369549067879344180U;
            aOrbiterB = RotL64((aOrbiterB * 2947354306696216579U), 21U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterI) + 7301713524358676722U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 6416U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterC) ^ 2985193736033012535U;
            aOrbiterF = RotL64((aOrbiterF * 7473297294949338265U), 13U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterB) + 14086975808140927408U;
            aOrbiterC = (aOrbiterC ^ aOrbiterA) ^ 10390516547834639800U;
            aOrbiterC = RotL64((aOrbiterC * 11441293212275890819U), 51U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 18205555540941493267U) + aOrbiterUpdateSaltD[((aIndex + 5081U)) & S_SALT1];
            aOrbiterA = (((aOrbiterA ^ aOrbiterI) ^ 16967799565443938873U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 5703U)) & S_SALT1]) ^ RotL64(aNonceByteE, 27U);
            aOrbiterA = RotL64((aOrbiterA * 3009081009044782443U), 39U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterC, 29U);
            aIngress = aIngress + (aOrbiterF ^ RotL64(aOrbiterI, 18U));
            aIngress = aIngress + RotL64(aOrbiterB, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aCross, 28U) + aOrbiterB) + RotL64(aOrbiterC, 19U));
            aWandererH = aWandererH ^ (((RotL64(aIngress, 37U) + aOrbiterA) + RotL64(aOrbiterF, 35U)) + RotL64(aNonceByteC, 35U));
            aWandererK = aWandererK + (((((RotL64(aScatter, 47U) + RotL64(aOrbiterI, 4U)) + aOrbiterF) + RotL64(aCarry, 13U)) + RotL64(aNonceByteF, 45U)) + aWandererUpdateSaltF[(((31U - aIndex) + 7019U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aPrevious, 5U) + RotL64(aOrbiterF, 57U)) + aOrbiterB) + aWandererUpdateSaltD[(((31U - aIndex) + 5327U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aCross, 19U) + RotL64(aOrbiterI, 27U)) + aOrbiterC) + RotL64(aCarry, 51U));
            //
            aCarry = aCarry + (RotL64(aWandererK, 3U) ^ aWandererB);
            aCarry = aCarry + (RotL64(aWandererH, 29U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererI, 57U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteD, 19U) ^ RotL64(aNonceByteH, 6U));
            aIngress = aIngress ^ (RotL64(aOperationLaneD[((aIndex + 13830U)) & S_BLOCK1], 27U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 9058U)) & S_BLOCK1], 37U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteC, 12U) ^ RotL64(aNonceByteF, 21U));
            aCross = aCross ^ (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 19463U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneA[((aIndex + 5496U)) & S_BLOCK1], 39U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 51U) ^ RotL64(aIngress, 37U)) + (RotL64(aPrevious, 21U) ^ RotL64(aCross, 6U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterC = (((aWandererG + RotL64(aScatter, 35U)) + 11274974230580265396U) + aOrbiterAssignSaltA[((aIndex + 6573U)) & S_SALT1]) + RotL64(aNonceByteG, 52U);
            aOrbiterB = (((aWandererE + RotL64(aIngress, 57U)) + 16658438747342741547U) + aOrbiterAssignSaltD[((aIndex + 1275U)) & S_SALT1]) + RotL64(aNonceByteC, 47U);
            aOrbiterA = ((aWandererA + RotL64(aCross, 5U)) + RotL64(aCarry, 19U)) + 16612986966106053844U;
            aOrbiterD = ((aWandererJ + RotL64(aPrevious, 44U)) + RotL64(aCarry, 57U)) + 9329502236843231290U;
            aOrbiterK = ((aWandererK + RotL64(aScatter, 27U)) + RotL64(aCarry, 43U)) + 14088261356708344656U;
            //
            aOrbiterC = (aOrbiterC + aOrbiterB) + 13692608802007789581U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterC) ^ 6824473946645682398U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 573U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 13619437545775237601U), 41U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterK) + 2072915876348570040U;
            aOrbiterC = (aOrbiterC ^ aOrbiterD) ^ 7420507753044460759U;
            aOrbiterC = RotL64((aOrbiterC * 13239288539564571257U), 5U);
            //
            aOrbiterB = (((aOrbiterB + aOrbiterA) + 4677557318688502593U) + aOrbiterUpdateSaltE[((aIndex + 2638U)) & S_SALT1]) + RotL64(aNonceByteH, 19U);
            aOrbiterD = ((aOrbiterD ^ aOrbiterB) ^ 15081678577055628459U) ^ aOrbiterUpdateSaltD[((aIndex + 6599U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 16659305295251177155U), 13U);
            //
            aOrbiterK = (((aOrbiterK + aOrbiterC) + 7026792817486507482U) + aOrbiterUpdateSaltC[((aIndex + 666U)) & S_SALT1]) + RotL64(aNonceByteA, 41U);
            aOrbiterB = (aOrbiterB ^ aOrbiterK) ^ 14871665922943969918U;
            aOrbiterB = RotL64((aOrbiterB * 694073180313083145U), 29U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 6807734532159292872U;
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 17882797335141303280U;
            aOrbiterK = RotL64((aOrbiterK * 15439872930381050291U), 53U);
            //
            aIngress = aOrbiterA ^ RotL64(aOrbiterB, 57U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterK, 3U));
            aIngress = aIngress + RotL64(aOrbiterD, 37U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + ((RotL64(aCross, 47U) + aOrbiterC) + RotL64(aOrbiterD, 44U));
            aWandererE = aWandererE ^ (((RotL64(aScatter, 10U) + aOrbiterD) + RotL64(aOrbiterB, 35U)) + aWandererUpdateSaltE[(((31U - aIndex) + 598U)) & S_SALT1]);
            aWandererK = aWandererK + (((((RotL64(aPrevious, 57U) + aOrbiterA) + RotL64(aOrbiterK, 13U)) + RotL64(aCarry, 11U)) + RotL64(aNonceByteB, 7U)) + aWandererUpdateSaltF[(((31U - aIndex) + 4739U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aIngress, 19U) + aOrbiterK) + RotL64(aOrbiterB, 27U));
            aWandererG = aWandererG + ((((RotL64(aCross, 27U) + aOrbiterC) + RotL64(aOrbiterK, 57U)) + RotL64(aCarry, 23U)) + RotL64(aNonceByteE, 13U));
            //
            aCarry = aCarry + (RotL64(aWandererE, 19U) ^ aWandererG);
            aCarry = aCarry + (RotL64(aWandererK, 60U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererA, 5U);
            aCarry = aCarry + RotL64(aIngress, 27U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteH, 5U) ^ RotL64(aNonceByteC, 30U));
            aIngress = aIngress ^ (RotL64(aWorkLaneA[((aIndex + 20718U)) & S_BLOCK1], 57U) ^ RotL64(aOperationLaneD[((aIndex + 27864U)) & S_BLOCK1], 19U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteE, 56U) ^ RotL64(aNonceByteG, 13U)) ^ RotL64(aNonceByteB, 3U));
            aCross = aCross ^ (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 17658U)) & S_BLOCK1], 39U) ^ RotL64(aOperationLaneB[((aIndex + 3982U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCross, 27U) ^ RotL64(aPrevious, 60U)) ^ (RotL64(aIngress, 41U) + RotL64(aCarry, 13U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = ((aWandererI + RotL64(aIngress, 54U)) + 12775735908960052604U) + aOrbiterAssignSaltC[((aIndex + 819U)) & S_SALT1];
            aOrbiterG = ((aWandererG + RotL64(aCross, 43U)) + RotL64(aCarry, 23U)) + 11791373812080296887U;
            aOrbiterI = (aWandererD + RotL64(aPrevious, 3U)) + 5537362877706057303U;
            aOrbiterB = ((((aWandererK + RotL64(aScatter, 23U)) + RotL64(aCarry, 35U)) + 2023912048504189380U) + aOrbiterAssignSaltF[((aIndex + 3223U)) & S_SALT1]) + RotL64(aNonceByteE, 53U);
            aOrbiterD = (((aWandererH + RotL64(aPrevious, 13U)) + RotL64(aCarry, 5U)) + 17668828109963766893U) + RotL64(aNonceByteF, 3U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterG) + 558908629933941224U) + aOrbiterUpdateSaltD[((aIndex + 3228U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterH) ^ 1479633119685446888U;
            aOrbiterI = RotL64((aOrbiterI * 4447153373540811385U), 27U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterB) + 15460320397843364063U) + RotL64(aNonceByteA, 28U);
            aOrbiterD = ((aOrbiterD ^ aOrbiterG) ^ 10059749397555469054U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 3661U)) & S_SALT1];
            aOrbiterD = RotL64((aOrbiterD * 8671817118586065469U), 35U);
            //
            aOrbiterB = (((aOrbiterB + aOrbiterI) + 9987633811929693924U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 6481U)) & S_SALT1]) + RotL64(aNonceByteD, 39U);
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 10087337844580228269U;
            aOrbiterH = RotL64((aOrbiterH * 13817142288940843815U), 11U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterD) + 4446204415503364254U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 15106063243302192717U;
            aOrbiterG = RotL64((aOrbiterG * 13273756657334709803U), 3U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterH) + 9430197906134676162U) + aOrbiterUpdateSaltA[((aIndex + 1159U)) & S_SALT1];
            aOrbiterB = (aOrbiterB ^ aOrbiterD) ^ 1226048679997253363U;
            aOrbiterB = RotL64((aOrbiterB * 14247538885252664127U), 53U);
            //
            aIngress = RotL64(aOrbiterI, 37U) ^ aOrbiterD;
            aIngress = aIngress + (RotL64(aOrbiterB, 57U) ^ aOrbiterG);
            aIngress = aIngress + RotL64(aOrbiterH, 47U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererK = aWandererK + (((RotL64(aCross, 23U) + RotL64(aOrbiterH, 43U)) + aOrbiterG) + RotL64(aNonceByteG, 43U));
            aWandererG = aWandererG ^ ((RotL64(aPrevious, 13U) + RotL64(aOrbiterI, 56U)) + aOrbiterD);
            aWandererD = aWandererD + ((((RotL64(aScatter, 5U) + RotL64(aOrbiterB, 3U)) + aOrbiterI) + RotL64(aCarry, 51U)) + aWandererUpdateSaltA[((aIndex + 2130U)) & S_SALT1]);
            aWandererI = aWandererI ^ (((RotL64(aIngress, 41U) + RotL64(aOrbiterB, 13U)) + aOrbiterH) + aWandererUpdateSaltD[(((31U - aIndex) + 6731U)) & S_SALT1]);
            aWandererH = aWandererH + ((((RotL64(aCross, 52U) + aOrbiterG) + RotL64(aOrbiterB, 35U)) + RotL64(aCarry, 27U)) + RotL64(aNonceByteB, 27U));
            //
            aCarry = aCarry + (RotL64(aWandererD, 22U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererH, 57U) ^ aWandererG);
            aCarry = aCarry + RotL64(aWandererK, 13U);
            aCarry = aCarry + RotL64(aIngress, 5U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteF, 3U) ^ RotL64(aNonceByteE, 13U)) ^ RotL64(aNonceByteB, 43U));
            aIngress = aIngress ^ (RotL64(aWorkLaneB[((aIndex + 11738U)) & S_BLOCK1], 52U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 21400U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteA, 26U) ^ RotL64(aNonceByteC, 37U)) ^ RotL64(aNonceByteH, 13U));
            aCross = aCross ^ (RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 24338U)) & S_BLOCK1], 5U) ^ RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 30412U)) & S_BLOCK1], 47U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 6U) ^ RotL64(aCross, 23U)) ^ (RotL64(aIngress, 37U) + RotL64(aCarry, 57U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterA = ((aWandererK + RotL64(aIngress, 11U)) + RotL64(aCarry, 39U)) + 3339283916456813609U;
            aOrbiterG = ((aWandererJ + RotL64(aPrevious, 38U)) + 11339086426180649584U) + RotL64(aNonceByteH, 29U);
            aOrbiterD = (((aWandererD + RotL64(aScatter, 53U)) + RotL64(aCarry, 11U)) + 16819191669329316585U) + RotL64(aNonceByteG, 15U);
            aOrbiterF = (((aWandererH + RotL64(aCross, 21U)) + RotL64(aCarry, 53U)) + 8361916937762630725U) + aOrbiterAssignSaltE[((aIndex + 5543U)) & S_SALT1];
            aOrbiterI = ((aWandererA + RotL64(aPrevious, 29U)) + 18031328374429899857U) + aOrbiterAssignSaltB[((aIndex + 8186U)) & S_SALT1];
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 18261756894092897276U) + RotL64(aNonceByteD, 55U);
            aOrbiterD = (aOrbiterD ^ aOrbiterA) ^ 4250319792907645666U;
            aOrbiterD = RotL64((aOrbiterD * 7053489184750217963U), 11U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 1492411503643460886U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 4211U)) & S_SALT1];
            aOrbiterG = ((aOrbiterG ^ aOrbiterF) ^ 17369549067879344180U) ^ aOrbiterUpdateSaltB[((aIndex + 6653U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 2947354306696216579U), 47U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterF) + 7301713524358676722U;
            aOrbiterA = (((aOrbiterA ^ aOrbiterI) ^ 2985193736033012535U) ^ aOrbiterUpdateSaltE[((aIndex + 7729U)) & S_SALT1]) ^ RotL64(aNonceByteF, 23U);
            aOrbiterA = RotL64((aOrbiterA * 7473297294949338265U), 39U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterI) + 14086975808140927408U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterD) ^ 10390516547834639800U) ^ aOrbiterUpdateSaltA[((aIndex + 4377U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 11441293212275890819U), 3U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterD) + 18205555540941493267U;
            aOrbiterI = (aOrbiterI ^ aOrbiterG) ^ 16967799565443938873U;
            aOrbiterI = RotL64((aOrbiterI * 3009081009044782443U), 29U);
            //
            aIngress = RotL64(aOrbiterG, 47U) ^ aOrbiterA;
            aIngress = aIngress + (RotL64(aOrbiterD, 3U) ^ aOrbiterF);
            aIngress = aIngress + RotL64(aOrbiterI, 35U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aCross, 11U) + aOrbiterA) + RotL64(aOrbiterF, 57U)) + RotL64(aNonceByteA, 52U));
            aWandererJ = aWandererJ ^ (((RotL64(aIngress, 54U) + RotL64(aOrbiterI, 21U)) + aOrbiterF) + RotL64(aNonceByteB, 57U));
            aWandererH = aWandererH + ((((RotL64(aPrevious, 29U) + RotL64(aOrbiterD, 13U)) + aOrbiterI) + RotL64(aCarry, 5U)) + aWandererUpdateSaltC[(((31U - aIndex) + 5704U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aScatter, 41U) + RotL64(aOrbiterG, 34U)) + aOrbiterD) + aWandererUpdateSaltB[((aIndex + 5296U)) & S_SALT1]);
            aWandererK = aWandererK + (((RotL64(aCross, 3U) + aOrbiterD) + RotL64(aOrbiterF, 3U)) + RotL64(aCarry, 51U));
            //
            aCarry = aCarry + (RotL64(aWandererA, 37U) ^ aWandererD);
            aCarry = aCarry + (RotL64(aWandererK, 27U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererH, 5U);
            aCarry = aCarry + RotL64(aIngress, 48U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteA, 41U) ^ RotL64(aNonceByteC, 50U));
            aIngress = aIngress ^ (RotL64(aWorkLaneC[((aIndex + 23513U)) & S_BLOCK1], 19U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 26069U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteG, 47U) ^ RotL64(aNonceByteE, 37U)) ^ RotL64(aNonceByteH, 60U));
            aCross = aCross ^ (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 13062U)) & S_BLOCK1], 13U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 30701U)) & S_BLOCK1], 21U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 53U) + RotL64(aPrevious, 20U)) ^ (RotL64(aCross, 37U) ^ RotL64(aIngress, 5U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterI = (((aWandererI + RotL64(aCross, 29U)) + 5697928251815176134U) + aOrbiterAssignSaltA[((aIndex + 2053U)) & S_SALT1]) + RotL64(aNonceByteF, 25U);
            aOrbiterE = ((aWandererD + RotL64(aPrevious, 3U)) + RotL64(aCarry, 41U)) + 337587740689259575U;
            aOrbiterG = ((((aWandererG + RotL64(aScatter, 57U)) + RotL64(aCarry, 27U)) + 4927686903263973950U) + aOrbiterAssignSaltD[((aIndex + 4137U)) & S_SALT1]) + RotL64(aNonceByteE, 9U);
            aOrbiterD = ((aWandererB + RotL64(aIngress, 48U)) + RotL64(aCarry, 53U)) + 3742409032569801033U;
            aOrbiterF = (aWandererJ + RotL64(aCross, 11U)) + 1608092659172197650U;
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 15848744267145717509U;
            aOrbiterG = (aOrbiterG ^ aOrbiterI) ^ 15300174177963339253U;
            aOrbiterG = RotL64((aOrbiterG * 5771922862677667319U), 57U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 14162868453323648628U) + aOrbiterUpdateSaltB[(((31U - aIndex) + 5165U)) & S_SALT1];
            aOrbiterI = (aOrbiterI ^ aOrbiterD) ^ 12020167069983729869U;
            aOrbiterI = RotL64((aOrbiterI * 2071080217680099017U), 47U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterG) + 16259538291658723956U;
            aOrbiterD = (((aOrbiterD ^ aOrbiterE) ^ 8516686212464112245U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 1595U)) & S_SALT1]) ^ RotL64(pNonce, 51U);
            aOrbiterD = RotL64((aOrbiterD * 4731296903548893627U), 13U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 3722184575520553132U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterF) ^ 5663609293306386784U) ^ RotL64(aNonceByteD, 14U);
            aOrbiterE = RotL64((aOrbiterE * 14364218128780764749U), 3U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterD) + 15265344442454471986U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 1907U)) & S_SALT1];
            aOrbiterF = ((aOrbiterF ^ aOrbiterG) ^ 3050323350098829515U) ^ aOrbiterUpdateSaltC[((aIndex + 4669U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 5890624677162388135U), 29U);
            //
            aIngress = RotL64(aOrbiterI, 47U) ^ aOrbiterD;
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterG, 58U));
            aIngress = aIngress + RotL64(aOrbiterF, 37U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ ((RotL64(aCross, 53U) + RotL64(aOrbiterD, 5U)) + aOrbiterF);
            aWandererG = aWandererG + (((((RotL64(aScatter, 22U) + aOrbiterE) + RotL64(aOrbiterI, 41U)) + RotL64(aCarry, 11U)) + RotL64(aNonceByteA, 31U)) + aWandererUpdateSaltF[((aIndex + 5109U)) & S_SALT1]);
            aWandererD = aWandererD ^ (((RotL64(aPrevious, 43U) + aOrbiterI) + RotL64(aOrbiterF, 27U)) + RotL64(aNonceByteB, 39U));
            aWandererB = aWandererB + ((((RotL64(aIngress, 5U) + RotL64(aOrbiterD, 53U)) + aOrbiterI) + RotL64(aCarry, 47U)) + aWandererUpdateSaltE[(((31U - aIndex) + 3812U)) & S_SALT1]);
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 35U) + RotL64(aOrbiterD, 14U)) + aOrbiterG);
            //
            aCarry = aCarry + (RotL64(aWandererI, 3U) ^ aWandererD);
            aCarry = aCarry + (aWandererJ ^ RotL64(aWandererB, 11U));
            aCarry = aCarry + RotL64(aWandererG, 23U);
            aCarry = aCarry + RotL64(aIngress, 57U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    {
        // kdf-a-matrix-diffusion: yeah
    
        TwistIndexShuffle::ExecuteA(aIndexList256A, aOperationLaneA);
        TwistIndexShuffle::ExecuteA(aIndexList256B, aOperationLaneB);
        TwistIndexShuffle::ExecuteB(aIndexList256C, aOperationLaneA);
        TwistIndexShuffle::ExecuteB(aIndexList256D, aOperationLaneB);
        aMatrixOperationIndex = 0U;
        aMatrixWriteIndex = 0U;
    
        for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
            aMatrixSlotA = aIndexList256A[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixSlotB = aIndexList256B[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixLoadIndexA = aMatrixSlotA * 128U;
            aMatrixLoadIndexB = (aMatrixSlotB * 128U) + 64U;
            mMatrixA.LoadAndReset(aWorkLaneA + aMatrixLoadIndexA);
            mMatrixB.LoadAndReset(aWorkLaneB + aMatrixLoadIndexB);
            aSelect = aOperationLaneC[(aMatrixOperationIndex) & S_BLOCK1] ^ aDomainWordMatrixSelectA;
            switch (aSelect % 4U) {
            	case 0U: {
            		aMatrixArgA = aOperationLaneC[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ReverseColEven(aMatrixArgA);
            		aMatrixArgA = aOperationLaneC[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ShiftRing8A(aMatrixArgA);
            		mMatrixA.PinwheelRightQuarterC();
            		mMatrixA.TransposeMainDiagonalBlocks();
            		mMatrixB.FlipHorizontalSixteenthsQuarterC();
            		aMatrixArgC = aOperationLaneC[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneC[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.RotateRow(aMatrixArgC, aMatrixArgD);
            		mMatrixB.FlipHorizontal();
            		mMatrixB.PinwheelLeftQuarterD();
            		aMatrixUnrollWordA = aOperationLaneC[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneC[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex;
            		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
            		mMatrixA.Store(aExpandLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kD, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 1U: {
            		aMatrixArgA = aOperationLaneC[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ReverseRowOdd(aMatrixArgA);
            		mMatrixA.TransposeMainDiagonalSixteenthsQuarterB();
            		mMatrixA.RotateRight();
            		mMatrixA.TransposeMainDiagonalQuarterA();
            		aMatrixArgC = aOperationLaneC[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneC[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.SwapColsOdd(aMatrixArgC, aMatrixArgD);
            		mMatrixB.TransposeMainDiagonal();
            		mMatrixB.RotateRightEachSixteenthQuarterC();
            		mMatrixB.TransposeAntiDiagonalEachSixteenthEachQuarter();
            		aMatrixUnrollWordA = aOperationLaneC[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneC[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex;
            		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
            		mMatrixA.Store(aExpandLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kB, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 2U: {
            		mMatrixA.FlipHorizontalBlocks();
            		mMatrixA.FlipHorizontalEachQuarter();
            		mMatrixA.RotateLeftQuarterC();
            		mMatrixA.FlipHorizontalEachSixteenthQuarterB();
            		aMatrixArgC = aOperationLaneC[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneC[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.RotateRow(aMatrixArgC, aMatrixArgD);
            		mMatrixB.RotateRight();
            		aMatrixArgC = aOperationLaneC[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ReverseRowEven(aMatrixArgC);
            		mMatrixB.RotateRightSixteenthsQuarterB();
            		aMatrixUnrollWordA = aOperationLaneC[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneC[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex;
            		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
            		mMatrixA.Store(aExpandLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kD, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 3U: {
            		aMatrixArgA = aOperationLaneC[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		aMatrixArgB = aOperationLaneC[((aMatrixOperationIndex + 2U)) & S_BLOCK1] ^ aDomainWordMatrixArgB;
            		mMatrixA.SwapRows(aMatrixArgA, aMatrixArgB);
            		aMatrixArgA = aOperationLaneC[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ShiftRing16G(aMatrixArgA);
            		mMatrixA.PinwheelRight();
            		mMatrixA.PinwheelRightQuarterB();
            		mMatrixB.TransposeAntiDiagonalEachSixteenthQuarterA();
            		aMatrixArgC = aOperationLaneC[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneC[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.RotateCol(aMatrixArgC, aMatrixArgD);
            		mMatrixB.TransposeAntiDiagonalQuarterB();
            		mMatrixB.RotateLeft();
            		aMatrixUnrollWordA = aOperationLaneC[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneC[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex;
            		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
            		mMatrixA.Store(aExpandLaneA + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneA + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kA, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            }
        }
    
        aMatrixOperationIndex = 0U;
        aMatrixWriteIndex = 0U;
    
        for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
            aMatrixSlotA = aIndexList256C[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixSlotB = aIndexList256D[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixLoadIndexA = (aMatrixSlotA * 128U) + 64U;
            aMatrixLoadIndexB = aMatrixSlotB * 128U;
            mMatrixA.LoadAndReset(aWorkLaneA + aMatrixLoadIndexA);
            mMatrixB.LoadAndReset(aWorkLaneB + aMatrixLoadIndexB);
            aSelect = aOperationLaneD[(aMatrixOperationIndex) & S_BLOCK1] ^ aDomainWordMatrixSelectB;
            switch (aSelect % 4U) {
            	case 0U: {
            		aMatrixArgA = aOperationLaneD[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ReverseColOdd(aMatrixArgA);
            		aMatrixArgA = aOperationLaneD[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		aMatrixArgB = aOperationLaneD[((aMatrixOperationIndex + 2U)) & S_BLOCK1] ^ aDomainWordMatrixArgB;
            		mMatrixA.SwapRows(aMatrixArgA, aMatrixArgB);
            		mMatrixA.TransposeMainDiagonalSixteenthsQuarterC();
            		mMatrixA.FlipVerticalQuarterA();
            		aMatrixArgC = aOperationLaneD[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ShiftRing16F(aMatrixArgC);
            		mMatrixB.PinwheelLeft();
            		mMatrixB.FlipHorizontalBlocks();
            		mMatrixB.RotateRightEachSixteenthQuarterA();
            		aMatrixUnrollWordA = aOperationLaneD[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneD[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
            		aMatrixStoreIndexB = aMatrixWriteIndex;
            		mMatrixA.Store(aExpandLaneB + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneB + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kB, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 1U: {
            		mMatrixA.TransposeAntiDiagonalBlocks();
            		mMatrixA.PinwheelLeft();
            		mMatrixA.PinwheelRightQuarterA();
            		mMatrixA.TransposeAntiDiagonalSixteenthsQuarterC();
            		mMatrixB.RotateRightQuarterB();
            		aMatrixArgC = aOperationLaneD[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneD[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.RotateCol(aMatrixArgC, aMatrixArgD);
            		aMatrixArgC = aOperationLaneD[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneD[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.RotateRow(aMatrixArgC, aMatrixArgD);
            		aMatrixArgC = aOperationLaneD[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ShiftRing12A(aMatrixArgC);
            		aMatrixUnrollWordA = aOperationLaneD[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneD[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
            		aMatrixStoreIndexB = aMatrixWriteIndex;
            		mMatrixA.Store(aExpandLaneB + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneB + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kA, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 2U: {
            		mMatrixA.RotateLeftQuarterA();
            		mMatrixA.TransposeMainDiagonal();
            		mMatrixA.FlipVertical();
            		aMatrixArgA = aOperationLaneD[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		aMatrixArgB = aOperationLaneD[((aMatrixOperationIndex + 2U)) & S_BLOCK1] ^ aDomainWordMatrixArgB;
            		mMatrixA.SwapColsOdd(aMatrixArgA, aMatrixArgB);
            		mMatrixB.FlipHorizontalEachSixteenthQuarterD();
            		aMatrixArgC = aOperationLaneD[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ReverseCol(aMatrixArgC);
            		mMatrixB.FlipHorizontalSixteenthsQuarterA();
            		mMatrixB.TransposeAntiDiagonalEachSixteenthEachQuarter();
            		aMatrixUnrollWordA = aOperationLaneD[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneD[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
            		aMatrixStoreIndexB = aMatrixWriteIndex;
            		mMatrixA.Store(aExpandLaneB + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneB + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kD, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 3U: {
            		mMatrixA.PinwheelLeftQuarterD();
            		mMatrixA.TransposeAntiDiagonalBlocks();
            		mMatrixA.FlipHorizontal();
            		aMatrixArgA = aOperationLaneD[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ReverseRowEven(aMatrixArgA);
            		mMatrixB.TransposeMainDiagonalQuarterA();
            		mMatrixB.FlipVerticalEachSixteenthQuarterB();
            		mMatrixB.RotateLeftSixteenthsQuarterA();
            		aMatrixArgC = aOperationLaneD[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ReverseColOdd(aMatrixArgC);
            		aMatrixUnrollWordA = aOperationLaneD[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneD[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
            		aMatrixStoreIndexB = aMatrixWriteIndex;
            		mMatrixA.Store(aExpandLaneB + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kD, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneB + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            }
        }
    }
    {
        // kdf-a-matrix-diffusion: yeah
    
        TwistIndexShuffle::ExecuteA(aIndexList256A, aOperationLaneC);
        TwistIndexShuffle::ExecuteA(aIndexList256B, aOperationLaneD);
        TwistIndexShuffle::ExecuteB(aIndexList256C, aOperationLaneC);
        TwistIndexShuffle::ExecuteB(aIndexList256D, aOperationLaneD);
        aMatrixOperationIndex = 0U;
        aMatrixWriteIndex = 0U;
    
        for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
            aMatrixSlotA = aIndexList256A[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixSlotB = aIndexList256B[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixLoadIndexA = aMatrixSlotA * 128U;
            aMatrixLoadIndexB = (aMatrixSlotB * 128U) + 64U;
            mMatrixA.LoadAndReset(aWorkLaneC + aMatrixLoadIndexA);
            mMatrixB.LoadAndReset(aWorkLaneD + aMatrixLoadIndexB);
            aSelect = aOperationLaneA[(aMatrixOperationIndex) & S_BLOCK1] ^ aDomainWordMatrixSelectA;
            switch (aSelect % 4U) {
            	case 0U: {
            		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ShiftRing16A(aMatrixArgA);
            		mMatrixA.TransposeMainDiagonalSixteenthsQuarterA();
            		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ReverseColOdd(aMatrixArgA);
            		mMatrixA.FlipHorizontalBlocks();
            		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.SwapColsOdd(aMatrixArgC, aMatrixArgD);
            		mMatrixB.FlipVerticalEachSixteenthEachQuarter();
            		mMatrixB.FlipVerticalSixteenthsEachQuarter();
            		mMatrixB.TransposeAntiDiagonal();
            		aMatrixUnrollWordA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex;
            		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
            		mMatrixA.Store(aExpandLaneC + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kD, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneC + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kA, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 1U: {
            		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ShiftRing8A(aMatrixArgA);
            		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1] ^ aDomainWordMatrixArgB;
            		mMatrixA.SwapColsOdd(aMatrixArgA, aMatrixArgB);
            		mMatrixA.FlipVertical();
            		mMatrixA.PinwheelRightQuarterB();
            		mMatrixB.FlipHorizontalQuarterC();
            		mMatrixB.TransposeMainDiagonalBlocks();
            		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.SwapSixteenths(aMatrixArgC, aMatrixArgD);
            		mMatrixB.TransposeAntiDiagonalEachSixteenthQuarterD();
            		aMatrixUnrollWordA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex;
            		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
            		mMatrixA.Store(aExpandLaneC + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneC + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kD, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 2U: {
            		mMatrixA.FlipVerticalBlocks();
            		mMatrixA.RotateRightEachSixteenthQuarterC();
            		mMatrixA.TransposeMainDiagonalQuarterB();
            		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		aMatrixArgB = aOperationLaneA[((aMatrixOperationIndex + 2U)) & S_BLOCK1] ^ aDomainWordMatrixArgB;
            		mMatrixA.SwapRowsOdd(aMatrixArgA, aMatrixArgB);
            		mMatrixB.FlipHorizontalSixteenthsQuarterC();
            		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ReverseRowOdd(aMatrixArgC);
            		mMatrixB.PinwheelLeft();
            		mMatrixB.RotateLeftSixteenthsQuarterD();
            		aMatrixUnrollWordA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex;
            		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
            		mMatrixA.Store(aExpandLaneC + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneC + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 3U: {
            		aMatrixArgA = aOperationLaneA[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ShiftRing16H(aMatrixArgA);
            		mMatrixA.PinwheelRight();
            		mMatrixA.TransposeAntiDiagonalSixteenthsEachQuarter();
            		mMatrixA.RotateRight();
            		mMatrixB.RotateRightQuarterD();
            		mMatrixB.FlipVerticalQuarterA();
            		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ReverseRowOdd(aMatrixArgC);
            		aMatrixArgC = aOperationLaneA[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneA[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.SwapColsOdd(aMatrixArgC, aMatrixArgD);
            		aMatrixUnrollWordA = aOperationLaneA[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneA[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex;
            		aMatrixStoreIndexB = aMatrixWriteIndex + 64U;
            		mMatrixA.Store(aExpandLaneC + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kB, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneC + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kA, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            }
        }
    
        aMatrixOperationIndex = 0U;
        aMatrixWriteIndex = 0U;
    
        for (std::size_t aMatrixDiffusionIndex = 0U; aMatrixDiffusionIndex < static_cast<std::size_t>(256); aMatrixDiffusionIndex += 1U) {
            aMatrixSlotA = aIndexList256C[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixSlotB = aIndexList256D[(aMatrixDiffusionIndex) & S_BLOCK1];
            aMatrixLoadIndexA = (aMatrixSlotA * 128U) + 64U;
            aMatrixLoadIndexB = aMatrixSlotB * 128U;
            mMatrixA.LoadAndReset(aWorkLaneC + aMatrixLoadIndexA);
            mMatrixB.LoadAndReset(aWorkLaneD + aMatrixLoadIndexB);
            aSelect = aOperationLaneB[(aMatrixOperationIndex) & S_BLOCK1] ^ aDomainWordMatrixSelectB;
            switch (aSelect % 4U) {
            	case 0U: {
            		mMatrixA.TransposeAntiDiagonalSixteenthsQuarterC();
            		mMatrixA.FlipVertical();
            		aMatrixArgA = aOperationLaneB[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		aMatrixArgB = aOperationLaneB[((aMatrixOperationIndex + 2U)) & S_BLOCK1] ^ aDomainWordMatrixArgB;
            		mMatrixA.SwapCols(aMatrixArgA, aMatrixArgB);
            		mMatrixA.TransposeAntiDiagonalEachSixteenthQuarterD();
            		mMatrixB.TransposeAntiDiagonal();
            		mMatrixB.FlipHorizontalSixteenthsQuarterB();
            		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneB[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.SwapRowsEven(aMatrixArgC, aMatrixArgD);
            		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ShiftRing20A(aMatrixArgC);
            		aMatrixUnrollWordA = aOperationLaneB[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneB[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
            		aMatrixStoreIndexB = aMatrixWriteIndex;
            		mMatrixA.Store(aExpandLaneD + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kA, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneD + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kB, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 1U: {
            		mMatrixA.PinwheelLeftQuarterA();
            		aMatrixArgA = aOperationLaneB[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		aMatrixArgB = aOperationLaneB[((aMatrixOperationIndex + 2U)) & S_BLOCK1] ^ aDomainWordMatrixArgB;
            		mMatrixA.SwapRowsOdd(aMatrixArgA, aMatrixArgB);
            		mMatrixA.FlipHorizontalBlocks();
            		mMatrixA.TransposeAntiDiagonalQuarterA();
            		mMatrixB.FlipHorizontalEachSixteenthQuarterA();
            		mMatrixB.FlipVertical();
            		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneB[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.RotateRow(aMatrixArgC, aMatrixArgD);
            		mMatrixB.FlipHorizontalEachQuarter();
            		aMatrixUnrollWordA = aOperationLaneB[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneB[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
            		aMatrixStoreIndexB = aMatrixWriteIndex;
            		mMatrixA.Store(aExpandLaneD + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kD, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneD + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 2U: {
            		mMatrixA.RotateRightSixteenthsQuarterB();
            		mMatrixA.FlipHorizontalBlocks();
            		aMatrixArgA = aOperationLaneB[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ShiftRing8F(aMatrixArgA);
            		mMatrixA.RotateLeftEachSixteenthQuarterC();
            		mMatrixB.RotateLeft();
            		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneB[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.SwapRowsEven(aMatrixArgC, aMatrixArgD);
            		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ReverseRowEven(aMatrixArgC);
            		mMatrixB.RotateLeftQuarterA();
            		aMatrixUnrollWordA = aOperationLaneB[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneB[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
            		aMatrixStoreIndexB = aMatrixWriteIndex;
            		mMatrixA.Store(aExpandLaneD + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kD, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneD + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            	case 3U: {
            		mMatrixA.TransposeAntiDiagonalSixteenthsQuarterD();
            		mMatrixA.TransposeAntiDiagonalBlocks();
            		mMatrixA.RotateRightEachQuarter();
            		aMatrixArgA = aOperationLaneB[((aMatrixOperationIndex + 1U)) & S_BLOCK1] ^ aDomainWordMatrixArgA;
            		mMatrixA.ReverseRow(aMatrixArgA);
            		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		mMatrixB.ShiftRing8G(aMatrixArgC);
            		mMatrixB.RotateLeftSixteenthsEachQuarter();
            		mMatrixB.PinwheelRight();
            		aMatrixArgC = aOperationLaneB[((aMatrixOperationIndex + 3U)) & S_BLOCK1] ^ aDomainWordMatrixArgC;
            		aMatrixArgD = aOperationLaneB[((aMatrixOperationIndex + 4U)) & S_BLOCK1] ^ aDomainWordMatrixArgD;
            		mMatrixB.RotateCol(aMatrixArgC, aMatrixArgD);
            		aMatrixUnrollWordA = aOperationLaneB[((aMatrixOperationIndex + 5U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollA;
            		aMatrixUnrollWordB = aOperationLaneB[((aMatrixOperationIndex + 6U)) & S_BLOCK1] ^ aDomainWordMatrixUnrollB;
            		aMatrixStoreIndexA = aMatrixWriteIndex + 64U;
            		aMatrixStoreIndexB = aMatrixWriteIndex;
            		mMatrixA.Store(aExpandLaneD + aMatrixStoreIndexA, TwistFastMatrixUnrollScheme::kB, aMatrixUnrollWordA);
            		mMatrixB.Store(aExpandLaneD + aMatrixStoreIndexB, TwistFastMatrixUnrollScheme::kC, aMatrixUnrollWordB);
            		aMatrixOperationIndex = aMatrixOperationIndex + 7U;
            		aMatrixWriteIndex = aMatrixWriteIndex + 128U;
            		break;
            	}
            }
        }
    }
}

void TwistExpander_Kerpal_0006::KDF_B(std::uint64_t pNonce,
                                  TwistDomainConstants *pConstants,
                                  TwistDomainSaltSet *pDomainSaltSet) {
    TwistExpander::KDF_B(pNonce, pConstants, pDomainSaltSet);
    TwistWorkSpace *pWorkSpace = mWorkspace;
    if ((pWorkSpace == nullptr) || (mSource == nullptr) ||
        (pConstants == nullptr) || (pDomainSaltSet == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aSource = mSource;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltA = pDomainSaltSet->mOrbiterAssign.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltB = pDomainSaltSet->mOrbiterAssign.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltC = pDomainSaltSet->mOrbiterAssign.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltD = pDomainSaltSet->mOrbiterAssign.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltE = pDomainSaltSet->mOrbiterAssign.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterAssignSaltF = pDomainSaltSet->mOrbiterAssign.mSaltF;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltA = pDomainSaltSet->mOrbiterUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltB = pDomainSaltSet->mOrbiterUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltC = pDomainSaltSet->mOrbiterUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltD = pDomainSaltSet->mOrbiterUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltE = pDomainSaltSet->mOrbiterUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aOrbiterUpdateSaltF = pDomainSaltSet->mOrbiterUpdate.mSaltF;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltA = pDomainSaltSet->mWandererUpdate.mSaltA;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltB = pDomainSaltSet->mWandererUpdate.mSaltB;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltC = pDomainSaltSet->mWandererUpdate.mSaltC;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltD = pDomainSaltSet->mWandererUpdate.mSaltD;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltE = pDomainSaltSet->mWandererUpdate.mSaltE;
    [[maybe_unused]] std::uint64_t *aWandererUpdateSaltF = pDomainSaltSet->mWandererUpdate.mSaltF;
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::size_t *aIndexList256A = mIndexList256A;
    [[maybe_unused]] std::size_t *aIndexList256B = mIndexList256B;
    [[maybe_unused]] std::size_t *aIndexList256C = mIndexList256C;
    [[maybe_unused]] std::size_t *aIndexList256D = mIndexList256D;
    std::uint64_t aPrevious = 0; std::uint64_t aIngress = 0; std::uint64_t aCross = 0; std::uint64_t aScatter = 0;
    std::uint64_t aCarry = 0;

    std::uint64_t aOrbiterA = 0; std::uint64_t aOrbiterB = 0; std::uint64_t aOrbiterC = 0; std::uint64_t aOrbiterD = 0;
    std::uint64_t aOrbiterE = 0; std::uint64_t aOrbiterF = 0; std::uint64_t aOrbiterG = 0; std::uint64_t aOrbiterH = 0;
    std::uint64_t aOrbiterI = 0; std::uint64_t aOrbiterJ = 0; std::uint64_t aOrbiterK = 0;

    std::uint64_t aWandererA = 0; std::uint64_t aWandererB = 0; std::uint64_t aWandererC = 0; std::uint64_t aWandererD = 0;
    std::uint64_t aWandererE = 0; std::uint64_t aWandererF = 0; std::uint64_t aWandererG = 0; std::uint64_t aWandererH = 0;
    std::uint64_t aWandererI = 0; std::uint64_t aWandererJ = 0; std::uint64_t aWandererK = 0;

    // [gseed-run-kdf3]
    [[maybe_unused]] std::uint64_t aNonceByteA = ((pNonce >> 0U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteB = ((pNonce >> 8U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteC = ((pNonce >> 16U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteD = ((pNonce >> 24U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteE = ((pNonce >> 32U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteF = ((pNonce >> 40U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteG = ((pNonce >> 48U) & 0xFFULL);
    [[maybe_unused]] std::uint64_t aNonceByteH = ((pNonce >> 56U) & 0xFFULL);
    std::uint64_t aDomainWordIngress = pConstants->mIngress;
    std::uint64_t aDomainWordScatter = pConstants->mScatter;
    std::uint64_t aDomainWordCross = pConstants->mCross;
    std::uint8_t aDomainWordMaskMutateA = pConstants->mMaskMutateA;
    std::uint8_t aDomainWordMaskMutateB = pConstants->mMaskMutateB;
    {
        aPrevious = 14873162954878690470U;
        aCarry = 17277146490738987910U;
        aWandererA = 10721119327631985697U;
        aWandererB = 14776977917513311707U;
        aWandererC = 10591313332926173782U;
        aWandererD = 9588860463064592448U;
        aWandererE = 10896778212152182992U;
        aWandererF = 11482848402848327230U;
        aWandererG = 11655408444512012049U;
        aWandererH = 16827924294059560986U;
        aWandererI = 16024163790761165602U;
        aWandererJ = 17018589140511173993U;
        aWandererK = 12414490155256257797U;
    }
    {
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteE, 24U) ^ RotL64(aNonceByteC, 13U));
            aIngress = aIngress ^ (RotL64(aExpandLaneD[((aIndex + 25788U)) & S_BLOCK1], 51U) ^ RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 17536U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteB, 41U) ^ RotL64(aNonceByteA, 19U)) ^ RotL64(aNonceByteG, 53U));
            aCross = aCross ^ (RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 18137U)) & S_BLOCK1], 6U) ^ RotL64(aExpandLaneA[((aIndex + 16293U)) & S_BLOCK1], 29U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 35U) ^ RotL64(aCross, 23U)) ^ (RotL64(aIngress, 51U) + RotL64(aCarry, 4U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterK = ((aWandererD + RotL64(aCross, 43U)) + 10336802574069791273U) + aOrbiterAssignSaltF[(((31U - aIndex) + 3411U)) & S_SALT1];
            aOrbiterB = (((aWandererA + RotL64(aScatter, 35U)) + RotL64(aCarry, 51U)) + 169025388197058936U) + RotL64(aNonceByteH, 13U);
            aOrbiterG = (((aWandererE + RotL64(aPrevious, 53U)) + RotL64(aCarry, 39U)) + 6541354188379168846U) + aOrbiterAssignSaltB[(((31U - aIndex) + 4042U)) & S_SALT1];
            aOrbiterC = ((aWandererB + RotL64(aIngress, 27U)) + 16223920526599306104U) + RotL64(aNonceByteB, 43U);
            aOrbiterE = ((aWandererI + RotL64(aCross, 10U)) + RotL64(aCarry, 11U)) + 12756613707692514808U;
            //
            aOrbiterK = (aOrbiterK + aOrbiterB) + 5082475548176484035U;
            aOrbiterG = (aOrbiterG ^ aOrbiterK) ^ 4907435526952698526U;
            aOrbiterG = RotL64((aOrbiterG * 1379692095754989215U), 3U);
            //
            aOrbiterC = ((aOrbiterC + aOrbiterE) + 14236627073831834337U) + RotL64(aNonceByteD, 47U);
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 11502511046130497584U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 4932U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 3460330807286625917U), 23U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterG) + 3679044835550219497U) + aOrbiterUpdateSaltC[((aIndex + 7706U)) & S_SALT1];
            aOrbiterC = ((aOrbiterC ^ aOrbiterB) ^ 11254838916686736746U) ^ aOrbiterUpdateSaltF[((aIndex + 3769U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 8631695922983532915U), 51U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 10582608424233200966U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterE) ^ 10449735026385340313U) ^ RotL64(aNonceByteF, 51U);
            aOrbiterB = RotL64((aOrbiterB * 7363770199734997411U), 13U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterC) + 4628253464169957835U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterG) ^ 17664454668473204465U) ^ aOrbiterUpdateSaltE[((aIndex + 6245U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 4234720298731378527U), 39U);
            //
            aIngress = RotL64(aOrbiterC, 19U) ^ aOrbiterK;
            aIngress = aIngress + (RotL64(aOrbiterG, 46U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterE, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererI = aWandererI ^ ((RotL64(aScatter, 51U) + aOrbiterB) + RotL64(aOrbiterE, 41U));
            aWandererB = aWandererB + (((((RotL64(aIngress, 3U) + RotL64(aOrbiterK, 51U)) + aOrbiterE) + RotL64(aCarry, 11U)) + RotL64(aNonceByteE, 4U)) + aWandererUpdateSaltE[((aIndex + 4246U)) & S_SALT1]);
            aWandererE = aWandererE ^ ((RotL64(aCross, 13U) + RotL64(aOrbiterB, 29U)) + aOrbiterC);
            aWandererA = aWandererA + ((((RotL64(aPrevious, 40U) + aOrbiterG) + RotL64(aOrbiterK, 20U)) + RotL64(aCarry, 41U)) + RotL64(aNonceByteC, 3U));
            aWandererD = aWandererD ^ (((RotL64(aIngress, 29U) + RotL64(aOrbiterG, 5U)) + aOrbiterE) + aWandererUpdateSaltA[(((31U - aIndex) + 5069U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererB, 38U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererI, 3U));
            aCarry = aCarry + RotL64(aWandererE, 11U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aWorkLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteE, 5U) ^ RotL64(aNonceByteB, 39U));
            aIngress = aIngress ^ (RotL64(aWorkLaneA[((aIndex + 19299U)) & S_BLOCK1], 30U) ^ RotL64(aExpandLaneD[((aIndex + 17257U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteA, 28U) ^ RotL64(aNonceByteG, 53U)) ^ RotL64(aNonceByteD, 43U));
            aCross = aCross ^ (RotL64(aExpandLaneC[((S_BLOCK1 - aIndex + 5024U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneB[((aIndex + 4249U)) & S_BLOCK1], 19U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 41U) ^ RotL64(aIngress, 3U)) + (RotL64(aCross, 54U) + RotL64(aPrevious, 23U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterE = ((aWandererD + RotL64(aCross, 21U)) + RotL64(aCarry, 51U)) + 3339283916456813609U;
            aOrbiterH = ((((aWandererK + RotL64(aPrevious, 29U)) + RotL64(aCarry, 35U)) + 11339086426180649584U) + aOrbiterAssignSaltE[((aIndex + 4745U)) & S_SALT1]) + RotL64(aNonceByteG, 37U);
            aOrbiterB = (((aWandererF + RotL64(aIngress, 58U)) + RotL64(aCarry, 21U)) + 16819191669329316585U) + aOrbiterAssignSaltA[((aIndex + 7943U)) & S_SALT1];
            aOrbiterD = (aWandererB + RotL64(aScatter, 37U)) + 8361916937762630725U;
            aOrbiterJ = ((aWandererA + RotL64(aPrevious, 3U)) + 18031328374429899857U) + RotL64(aNonceByteF, 61U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterH) + 18261756894092897276U;
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 4250319792907645666U;
            aOrbiterB = RotL64((aOrbiterB * 7053489184750217963U), 3U);
            //
            aOrbiterH = (aOrbiterH + aOrbiterD) + 1492411503643460886U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterH) ^ 17369549067879344180U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 7048U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 2947354306696216579U), 21U);
            //
            aOrbiterD = (((aOrbiterD + aOrbiterB) + 7301713524358676722U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 8182U)) & S_SALT1]) + RotL64(aNonceByteH, 57U);
            aOrbiterE = ((aOrbiterE ^ aOrbiterD) ^ 2985193736033012535U) ^ RotL64(aNonceByteC, 53U);
            aOrbiterE = RotL64((aOrbiterE * 7473297294949338265U), 35U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterJ) + 14086975808140927408U) + aOrbiterUpdateSaltB[((aIndex + 2501U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 10390516547834639800U;
            aOrbiterH = RotL64((aOrbiterH * 11441293212275890819U), 47U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterE) + 18205555540941493267U) + aOrbiterUpdateSaltD[((aIndex + 1132U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterJ) ^ 16967799565443938873U;
            aOrbiterD = RotL64((aOrbiterD * 3009081009044782443U), 11U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterD, 36U);
            aIngress = aIngress + (RotL64(aOrbiterB, 23U) ^ aOrbiterJ);
            aIngress = aIngress + RotL64(aOrbiterE, 5U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererA = aWandererA + (((RotL64(aScatter, 35U) + aOrbiterD) + RotL64(aOrbiterB, 21U)) + aWandererUpdateSaltF[((aIndex + 7853U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aPrevious, 57U) + RotL64(aOrbiterJ, 29U)) + aOrbiterB) + RotL64(aNonceByteA, 3U));
            aWandererF = aWandererF + (((RotL64(aIngress, 5U) + RotL64(aOrbiterE, 37U)) + aOrbiterJ) + RotL64(aCarry, 19U));
            aWandererD = aWandererD ^ ((((RotL64(aCross, 19U) + aOrbiterD) + RotL64(aOrbiterE, 4U)) + RotL64(aNonceByteD, 44U)) + aWandererUpdateSaltB[(((31U - aIndex) + 7325U)) & S_SALT1]);
            aWandererB = aWandererB + (((RotL64(aScatter, 46U) + aOrbiterD) + RotL64(aOrbiterH, 57U)) + RotL64(aCarry, 3U));
            //
            aCarry = aCarry + (aWandererK ^ RotL64(aWandererA, 47U));
            aCarry = aCarry + (aWandererD ^ RotL64(aWandererB, 27U));
            aCarry = aCarry + RotL64(aWandererF, 37U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteE, 57U) ^ RotL64(aNonceByteH, 47U)) ^ RotL64(aNonceByteC, 11U));
            aIngress = aIngress ^ (RotL64(aWorkLaneB[((aIndex + 27307U)) & S_BLOCK1], 3U) ^ RotL64(aWorkLaneA[((aIndex + 23488U)) & S_BLOCK1], 26U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteG, 54U) ^ RotL64(aNonceByteA, 27U));
            aCross = aCross ^ (RotL64(aExpandLaneD[((S_BLOCK1 - aIndex + 19184U)) & S_BLOCK1], 19U) ^ RotL64(aExpandLaneC[((aIndex + 7691U)) & S_BLOCK1], 5U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 39U) + RotL64(aPrevious, 4U)) ^ (RotL64(aCross, 21U) ^ RotL64(aIngress, 53U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterK = (((aWandererH + RotL64(aPrevious, 27U)) + 17264605017518259932U) + aOrbiterAssignSaltC[((aIndex + 3875U)) & S_SALT1]) + RotL64(aNonceByteF, 59U);
            aOrbiterJ = (((aWandererD + RotL64(aCross, 43U)) + 15209184354580778643U) + aOrbiterAssignSaltD[((aIndex + 7725U)) & S_SALT1]) + RotL64(pNonce, 53U);
            aOrbiterI = ((aWandererK + RotL64(aScatter, 5U)) + RotL64(aCarry, 19U)) + 3299527965014731384U;
            aOrbiterH = ((aWandererC + RotL64(aIngress, 18U)) + RotL64(aCarry, 53U)) + 16293096431816127821U;
            aOrbiterC = ((aWandererF + RotL64(aCross, 57U)) + RotL64(aCarry, 5U)) + 11031983436878828337U;
            //
            aOrbiterK = ((aOrbiterK + aOrbiterJ) + 9188018632448236358U) + RotL64(aNonceByteB, 23U);
            aOrbiterI = ((aOrbiterI ^ aOrbiterK) ^ 13420816400363406556U) ^ RotL64(aNonceByteD, 34U);
            aOrbiterI = RotL64((aOrbiterI * 10958221259662190519U), 29U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterK) + 2485063384097917101U) + aOrbiterUpdateSaltF[(((31U - aIndex) + 5807U)) & S_SALT1];
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterH) ^ 3089135816938128264U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 3734U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 8813152992957361153U), 51U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterH) + 10730544971770435788U;
            aOrbiterK = (aOrbiterK ^ aOrbiterC) ^ 10431767565618874806U;
            aOrbiterK = RotL64((aOrbiterK * 4723078464590561545U), 3U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterC) + 14883796491656899074U) + aOrbiterUpdateSaltC[((aIndex + 4678U)) & S_SALT1];
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 13465877783538483706U;
            aOrbiterH = RotL64((aOrbiterH * 14311686051108108503U), 19U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterI) + 13322163435314643713U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 3239U)) & S_SALT1];
            aOrbiterC = (aOrbiterC ^ aOrbiterJ) ^ 3307316600284371955U;
            aOrbiterC = RotL64((aOrbiterC * 12337846092069506365U), 39U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterJ, 13U);
            aIngress = aIngress + (aOrbiterC ^ RotL64(aOrbiterK, 3U));
            aIngress = aIngress + RotL64(aOrbiterI, 51U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererH = aWandererH + (((((RotL64(aIngress, 13U) + RotL64(aOrbiterI, 27U)) + aOrbiterH) + RotL64(aCarry, 41U)) + RotL64(aNonceByteG, 43U)) + aWandererUpdateSaltC[((aIndex + 1177U)) & S_SALT1]);
            aWandererD = aWandererD ^ ((RotL64(aScatter, 48U) + aOrbiterJ) + RotL64(aOrbiterK, 47U));
            aWandererC = aWandererC + ((((RotL64(aPrevious, 29U) + aOrbiterJ) + RotL64(aOrbiterI, 35U)) + RotL64(aNonceByteE, 27U)) + aWandererUpdateSaltD[((aIndex + 2033U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aCross, 5U) + aOrbiterC) + RotL64(aOrbiterI, 60U));
            aWandererF = aWandererF + (((RotL64(aPrevious, 37U) + aOrbiterC) + RotL64(aOrbiterH, 5U)) + RotL64(aCarry, 19U));
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererD, 21U));
            aCarry = aCarry + (RotL64(aWandererF, 51U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererK, 60U);
            aCarry = aCarry + RotL64(aIngress, 13U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aWorkLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteH, 60U) ^ RotL64(aNonceByteC, 51U));
            aIngress = aIngress ^ (RotL64(aWorkLaneC[((aIndex + 25796U)) & S_BLOCK1], 21U) ^ RotL64(aWorkLaneB[((aIndex + 16386U)) & S_BLOCK1], 37U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteA, 35U) ^ RotL64(aNonceByteE, 60U)) ^ RotL64(aNonceByteG, 51U));
            aCross = aCross ^ (RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 25929U)) & S_BLOCK1], 11U) ^ RotL64(aExpandLaneD[((aIndex + 26490U)) & S_BLOCK1], 43U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 39U) + RotL64(aPrevious, 27U)) + (RotL64(aIngress, 51U) ^ RotL64(aCross, 6U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = ((aWandererA + RotL64(aScatter, 27U)) + 12775735908960052604U) + aOrbiterAssignSaltB[((aIndex + 5209U)) & S_SALT1];
            aOrbiterJ = (((aWandererC + RotL64(aPrevious, 19U)) + RotL64(aCarry, 57U)) + 11791373812080296887U) + RotL64(aNonceByteE, 19U);
            aOrbiterH = ((((aWandererF + RotL64(aCross, 11U)) + RotL64(aCarry, 41U)) + 5537362877706057303U) + aOrbiterAssignSaltF[(((31U - aIndex) + 2741U)) & S_SALT1]) + RotL64(aNonceByteG, 47U);
            aOrbiterE = ((aWandererJ + RotL64(aIngress, 48U)) + RotL64(aCarry, 29U)) + 2023912048504189380U;
            aOrbiterD = (aWandererH + RotL64(aPrevious, 39U)) + 17668828109963766893U;
            //
            aOrbiterF = ((aOrbiterF + aOrbiterJ) + 558908629933941224U) + aOrbiterUpdateSaltB[((aIndex + 5501U)) & S_SALT1];
            aOrbiterH = ((aOrbiterH ^ aOrbiterF) ^ 1479633119685446888U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 4745U)) & S_SALT1];
            aOrbiterH = RotL64((aOrbiterH * 4447153373540811385U), 35U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterD) + 15460320397843364063U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 10059749397555469054U;
            aOrbiterF = RotL64((aOrbiterF * 8671817118586065469U), 13U);
            //
            aOrbiterJ = ((aOrbiterJ + aOrbiterH) + 9987633811929693924U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 2755U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterJ) ^ 10087337844580228269U) ^ RotL64(aNonceByteB, 23U);
            aOrbiterE = RotL64((aOrbiterE * 13817142288940843815U), 53U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterF) + 4446204415503364254U) + aOrbiterUpdateSaltF[((aIndex + 1229U)) & S_SALT1];
            aOrbiterJ = (aOrbiterJ ^ aOrbiterD) ^ 15106063243302192717U;
            aOrbiterJ = RotL64((aOrbiterJ * 13273756657334709803U), 21U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterE) + 9430197906134676162U) + RotL64(aNonceByteD, 5U);
            aOrbiterD = (aOrbiterD ^ aOrbiterH) ^ 1226048679997253363U;
            aOrbiterD = RotL64((aOrbiterD * 14247538885252664127U), 3U);
            //
            aIngress = aOrbiterF ^ RotL64(aOrbiterD, 23U);
            aIngress = aIngress + (RotL64(aOrbiterE, 57U) ^ aOrbiterH);
            aIngress = aIngress + RotL64(aOrbiterJ, 4U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererC = aWandererC + (((RotL64(aCross, 43U) + RotL64(aOrbiterF, 11U)) + aOrbiterD) + RotL64(aCarry, 39U));
            aWandererF = aWandererF ^ (((RotL64(aScatter, 51U) + aOrbiterJ) + RotL64(aOrbiterF, 3U)) + aWandererUpdateSaltE[((aIndex + 4378U)) & S_SALT1]);
            aWandererA = aWandererA + (((((RotL64(aIngress, 60U) + aOrbiterE) + RotL64(aOrbiterH, 29U)) + RotL64(aCarry, 5U)) + RotL64(aNonceByteF, 42U)) + aWandererUpdateSaltA[(((31U - aIndex) + 6758U)) & S_SALT1]);
            aWandererH = aWandererH ^ ((RotL64(aPrevious, 29U) + RotL64(aOrbiterJ, 19U)) + aOrbiterH);
            aWandererJ = aWandererJ + (((RotL64(aIngress, 21U) + aOrbiterD) + RotL64(aOrbiterE, 56U)) + RotL64(aNonceByteA, 31U));
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererF, 37U));
            aCarry = aCarry + (RotL64(aWandererJ, 46U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererC, 13U);
            aCarry = aCarry + RotL64(aIngress, 3U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aWorkLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteG, 26U) ^ RotL64(aNonceByteA, 47U)) ^ RotL64(aNonceByteC, 5U));
            aIngress = aIngress ^ (RotL64(aWorkLaneD[((aIndex + 30878U)) & S_BLOCK1], 57U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 27494U)) & S_BLOCK1], 39U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteH, 54U) ^ RotL64(aNonceByteB, 21U));
            aCross = aCross ^ (RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 26607U)) & S_BLOCK1], 29U) ^ RotL64(aWorkLaneA[((S_BLOCK1 - aIndex + 30250U)) & S_BLOCK1], 41U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 23U) + RotL64(aCarry, 37U)) ^ (RotL64(aIngress, 50U) ^ RotL64(aCross, 11U));
            aScatter = TwistMix64::DiffuseB((aScatter ^ aDomainWordScatter));
            //
            aOrbiterB = ((((aWandererG + RotL64(aScatter, 47U)) + RotL64(aCarry, 43U)) + 17264605017518259932U) + aOrbiterAssignSaltA[((aIndex + 3366U)) & S_SALT1]) + RotL64(aNonceByteE, 9U);
            aOrbiterA = ((aWandererI + RotL64(aIngress, 3U)) + 15209184354580778643U) + RotL64(aNonceByteD, 45U);
            aOrbiterE = (aWandererC + RotL64(aCross, 13U)) + 3299527965014731384U;
            aOrbiterJ = (((aWandererB + RotL64(aPrevious, 30U)) + RotL64(aCarry, 19U)) + 16293096431816127821U) + aOrbiterAssignSaltD[(((31U - aIndex) + 4715U)) & S_SALT1];
            aOrbiterF = ((aWandererH + RotL64(aIngress, 21U)) + RotL64(aCarry, 57U)) + 11031983436878828337U;
            //
            aOrbiterB = (aOrbiterB + aOrbiterA) + 9188018632448236358U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterB) ^ 13420816400363406556U) ^ aOrbiterUpdateSaltF[((aIndex + 2439U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 10958221259662190519U), 39U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterF) + 2485063384097917101U;
            aOrbiterB = (((aOrbiterB ^ aOrbiterJ) ^ 3089135816938128264U) ^ aOrbiterUpdateSaltC[(((31U - aIndex) + 7085U)) & S_SALT1]) ^ RotL64(pNonce, 51U);
            aOrbiterB = RotL64((aOrbiterB * 8813152992957361153U), 57U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterE) + 10730544971770435788U;
            aOrbiterJ = (aOrbiterJ ^ aOrbiterA) ^ 10431767565618874806U;
            aOrbiterJ = RotL64((aOrbiterJ * 4723078464590561545U), 47U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterB) + 14883796491656899074U) + aOrbiterUpdateSaltE[(((31U - aIndex) + 7914U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterF) ^ 13465877783538483706U) ^ aOrbiterUpdateSaltD[((aIndex + 4180U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 14311686051108108503U), 11U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterJ) + 13322163435314643713U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterE) ^ 3307316600284371955U) ^ RotL64(aNonceByteA, 46U);
            aOrbiterF = RotL64((aOrbiterF * 12337846092069506365U), 29U);
            //
            aIngress = RotL64(aOrbiterE, 46U) ^ aOrbiterB;
            aIngress = aIngress + (RotL64(aOrbiterF, 57U) ^ aOrbiterA);
            aIngress = aIngress + RotL64(aOrbiterJ, 35U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((((RotL64(aCross, 3U) + aOrbiterB) + RotL64(aOrbiterJ, 57U)) + RotL64(aCarry, 21U)) + aWandererUpdateSaltD[((aIndex + 5737U)) & S_SALT1]);
            aWandererG = aWandererG ^ (((RotL64(aScatter, 47U) + aOrbiterA) + RotL64(aOrbiterF, 27U)) + RotL64(aNonceByteF, 55U));
            aWandererH = aWandererH + (((RotL64(aPrevious, 11U) + aOrbiterJ) + RotL64(aOrbiterA, 19U)) + RotL64(aCarry, 39U));
            aWandererI = aWandererI ^ (((RotL64(aIngress, 21U) + RotL64(aOrbiterE, 38U)) + aOrbiterB) + RotL64(aNonceByteH, 35U));
            aWandererC = aWandererC + (((RotL64(aScatter, 58U) + aOrbiterF) + RotL64(aOrbiterJ, 11U)) + aWandererUpdateSaltE[(((31U - aIndex) + 2965U)) & S_SALT1]);
            //
            aCarry = aCarry + (aWandererG ^ RotL64(aWandererH, 20U));
            aCarry = aCarry + (RotL64(aWandererB, 53U) ^ aWandererC);
            aCarry = aCarry + RotL64(aWandererI, 29U);
            aCarry = aCarry + RotL64(aIngress, 11U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteF, 13U) ^ RotL64(aNonceByteC, 56U)) ^ RotL64(aNonceByteD, 5U));
            aIngress = aIngress ^ (RotL64(aOperationLaneA[((aIndex + 14825U)) & S_BLOCK1], 35U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 14873U)) & S_BLOCK1], 43U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteA, 37U) ^ RotL64(aNonceByteG, 46U)) ^ RotL64(aNonceByteE, 5U));
            aCross = aCross ^ (RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 1458U)) & S_BLOCK1], 57U) ^ RotL64(aWorkLaneB[((S_BLOCK1 - aIndex + 15401U)) & S_BLOCK1], 27U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 3U) + RotL64(aCross, 37U)) + (RotL64(aPrevious, 52U) ^ RotL64(aCarry, 19U));
            aScatter = TwistMix64::DiffuseA((aScatter ^ aDomainWordScatter));
            //
            aOrbiterH = (((aWandererB + RotL64(aIngress, 5U)) + 10336802574069791273U) + aOrbiterAssignSaltC[(((31U - aIndex) + 6403U)) & S_SALT1]) + RotL64(aNonceByteA, 5U);
            aOrbiterG = (((aWandererJ + RotL64(aCross, 57U)) + RotL64(aCarry, 13U)) + 169025388197058936U) + RotL64(aNonceByteB, 59U);
            aOrbiterF = ((aWandererC + RotL64(aPrevious, 24U)) + 6541354188379168846U) + aOrbiterAssignSaltF[(((31U - aIndex) + 4559U)) & S_SALT1];
            aOrbiterB = ((aWandererA + RotL64(aScatter, 13U)) + RotL64(aCarry, 27U)) + 16223920526599306104U;
            aOrbiterK = ((aWandererF + RotL64(aPrevious, 39U)) + RotL64(aCarry, 51U)) + 12756613707692514808U;
            //
            aOrbiterH = (aOrbiterH + aOrbiterG) + 5082475548176484035U;
            aOrbiterF = ((aOrbiterF ^ aOrbiterH) ^ 4907435526952698526U) ^ aOrbiterUpdateSaltE[((aIndex + 3477U)) & S_SALT1];
            aOrbiterF = RotL64((aOrbiterF * 1379692095754989215U), 23U);
            //
            aOrbiterG = (((aOrbiterG + aOrbiterB) + 14236627073831834337U) + aOrbiterUpdateSaltA[(((31U - aIndex) + 7581U)) & S_SALT1]) + RotL64(aNonceByteC, 31U);
            aOrbiterK = (((aOrbiterK ^ aOrbiterG) ^ 11502511046130497584U) ^ aOrbiterUpdateSaltB[((aIndex + 1316U)) & S_SALT1]) ^ RotL64(aNonceByteH, 51U);
            aOrbiterK = RotL64((aOrbiterK * 3460330807286625917U), 43U);
            //
            aOrbiterB = (aOrbiterB + aOrbiterF) + 3679044835550219497U;
            aOrbiterH = (aOrbiterH ^ aOrbiterB) ^ 11254838916686736746U;
            aOrbiterH = RotL64((aOrbiterH * 8631695922983532915U), 57U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterK) + 10582608424233200966U;
            aOrbiterG = (aOrbiterG ^ aOrbiterF) ^ 10449735026385340313U;
            aOrbiterG = RotL64((aOrbiterG * 7363770199734997411U), 35U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterH) + 4628253464169957835U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterK) ^ 17664454668473204465U) ^ aOrbiterUpdateSaltD[((aIndex + 858U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 4234720298731378527U), 5U);
            //
            aIngress = RotL64(aOrbiterG, 11U) ^ aOrbiterF;
            aIngress = aIngress + (RotL64(aOrbiterH, 37U) ^ aOrbiterK);
            aIngress = aIngress + RotL64(aOrbiterB, 47U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ ((((RotL64(aIngress, 29U) + aOrbiterF) + RotL64(aOrbiterB, 58U)) + RotL64(aNonceByteD, 37U)) + aWandererUpdateSaltF[(((31U - aIndex) + 4918U)) & S_SALT1]);
            aWandererA = aWandererA + (((((RotL64(aCross, 54U) + RotL64(aOrbiterB, 27U)) + aOrbiterG) + RotL64(aCarry, 13U)) + RotL64(aNonceByteF, 34U)) + aWandererUpdateSaltA[(((31U - aIndex) + 5038U)) & S_SALT1]);
            aWandererB = aWandererB ^ ((RotL64(aScatter, 11U) + aOrbiterK) + RotL64(aOrbiterF, 35U));
            aWandererF = aWandererF + (((RotL64(aPrevious, 3U) + RotL64(aOrbiterH, 13U)) + aOrbiterF) + RotL64(aCarry, 37U));
            aWandererJ = aWandererJ ^ ((RotL64(aCross, 37U) + aOrbiterH) + RotL64(aOrbiterG, 3U));
            //
            aCarry = aCarry + (RotL64(aWandererF, 47U) ^ aWandererC);
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererB, 38U));
            aCarry = aCarry + RotL64(aWandererJ, 3U);
            aCarry = aCarry + RotL64(aIngress, 21U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aOperationLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteG, 47U) ^ RotL64(aNonceByteD, 30U)) ^ RotL64(aNonceByteE, 21U));
            aIngress = aIngress ^ (RotL64(aOperationLaneB[((aIndex + 32281U)) & S_BLOCK1], 3U) ^ RotL64(aOperationLaneA[((aIndex + 7257U)) & S_BLOCK1], 11U));
            aIngress = TwistMix64::DiffuseC((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteH, 11U) ^ RotL64(aNonceByteC, 56U));
            aCross = aCross ^ (RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 15304U)) & S_BLOCK1], 23U) ^ RotL64(aWorkLaneC[((S_BLOCK1 - aIndex + 22605U)) & S_BLOCK1], 37U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 29U) ^ RotL64(aIngress, 42U)) + (RotL64(aPrevious, 57U) + RotL64(aCross, 5U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterB = (((aWandererA + RotL64(aScatter, 24U)) + RotL64(aCarry, 23U)) + 12775735908960052604U) + aOrbiterAssignSaltB[(((31U - aIndex) + 2169U)) & S_SALT1];
            aOrbiterK = (((aWandererK + RotL64(aCross, 39U)) + RotL64(aCarry, 37U)) + 11791373812080296887U) + aOrbiterAssignSaltE[(((31U - aIndex) + 6767U)) & S_SALT1];
            aOrbiterI = ((aWandererD + RotL64(aPrevious, 57U)) + 5537362877706057303U) + RotL64(aNonceByteA, 4U);
            aOrbiterH = ((aWandererJ + RotL64(aIngress, 3U)) + 2023912048504189380U) + RotL64(aNonceByteG, 13U);
            aOrbiterE = ((aWandererH + RotL64(aPrevious, 47U)) + RotL64(aCarry, 57U)) + 17668828109963766893U;
            //
            aOrbiterB = ((aOrbiterB + aOrbiterK) + 558908629933941224U) + aOrbiterUpdateSaltE[((aIndex + 6613U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterB) ^ 1479633119685446888U) ^ aOrbiterUpdateSaltF[((aIndex + 1975U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 4447153373540811385U), 13U);
            //
            aOrbiterH = ((aOrbiterH + aOrbiterB) + 15460320397843364063U) + RotL64(aNonceByteE, 49U);
            aOrbiterK = (aOrbiterK ^ aOrbiterH) ^ 10059749397555469054U;
            aOrbiterK = RotL64((aOrbiterK * 8671817118586065469U), 29U);
            //
            aOrbiterE = ((aOrbiterE + aOrbiterH) + 9987633811929693924U) + RotL64(aNonceByteB, 47U);
            aOrbiterB = (aOrbiterB ^ aOrbiterE) ^ 10087337844580228269U;
            aOrbiterB = RotL64((aOrbiterB * 13817142288940843815U), 57U);
            //
            aOrbiterI = (aOrbiterI + aOrbiterE) + 4446204415503364254U;
            aOrbiterH = (aOrbiterH ^ aOrbiterI) ^ 15106063243302192717U;
            aOrbiterH = RotL64((aOrbiterH * 13273756657334709803U), 43U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterI) + 9430197906134676162U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 5563U)) & S_SALT1];
            aOrbiterE = ((aOrbiterE ^ aOrbiterK) ^ 1226048679997253363U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 7303U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 14247538885252664127U), 21U);
            //
            aIngress = aOrbiterH ^ RotL64(aOrbiterI, 24U);
            aIngress = aIngress + (RotL64(aOrbiterK, 35U) ^ aOrbiterB);
            aIngress = aIngress + RotL64(aOrbiterE, 13U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererJ = aWandererJ + (((RotL64(aIngress, 53U) + RotL64(aOrbiterH, 13U)) + aOrbiterB) + RotL64(aCarry, 3U));
            aWandererK = aWandererK ^ (((RotL64(aCross, 19U) + aOrbiterH) + RotL64(aOrbiterE, 23U)) + RotL64(aNonceByteD, 59U));
            aWandererD = aWandererD + ((RotL64(aPrevious, 5U) + RotL64(aOrbiterE, 48U)) + aOrbiterI);
            aWandererA = aWandererA ^ (((RotL64(aScatter, 41U) + aOrbiterE) + RotL64(aOrbiterB, 37U)) + aWandererUpdateSaltC[((aIndex + 7314U)) & S_SALT1]);
            aWandererH = aWandererH + (((((RotL64(aPrevious, 30U) + aOrbiterK) + RotL64(aOrbiterI, 3U)) + RotL64(aCarry, 39U)) + RotL64(aNonceByteF, 23U)) + aWandererUpdateSaltB[((aIndex + 457U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererH, 11U) ^ aWandererK);
            aCarry = aCarry + (RotL64(aWandererJ, 29U) ^ aWandererA);
            aCarry = aCarry + RotL64(aWandererD, 57U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aOperationLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ ((RotL64(aNonceByteA, 11U) ^ RotL64(aNonceByteD, 20U)) ^ RotL64(aNonceByteF, 3U));
            aIngress = aIngress ^ (RotL64(aOperationLaneC[((aIndex + 6572U)) & S_BLOCK1], 43U) ^ RotL64(aOperationLaneB[((aIndex + 10530U)) & S_BLOCK1], 57U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteB, 5U) ^ RotL64(aNonceByteE, 13U)) ^ RotL64(aNonceByteH, 51U));
            aCross = aCross ^ (RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 5080U)) & S_BLOCK1], 28U) ^ RotL64(aWorkLaneD[((S_BLOCK1 - aIndex + 28202U)) & S_BLOCK1], 39U));
            aCross = TwistMix64::DiffuseC((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aIngress, 20U) + RotL64(aCross, 39U)) + (RotL64(aCarry, 51U) ^ RotL64(aPrevious, 5U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterF = ((aWandererC + RotL64(aPrevious, 12U)) + 11274974230580265396U) + aOrbiterAssignSaltD[((aIndex + 3429U)) & S_SALT1];
            aOrbiterA = ((aWandererH + RotL64(aIngress, 47U)) + 16658438747342741547U) + RotL64(aNonceByteC, 13U);
            aOrbiterG = (((aWandererD + RotL64(aCross, 37U)) + RotL64(aCarry, 13U)) + 16612986966106053844U) + RotL64(aNonceByteE, 29U);
            aOrbiterK = (((aWandererG + RotL64(aScatter, 21U)) + RotL64(aCarry, 37U)) + 9329502236843231290U) + aOrbiterAssignSaltA[(((31U - aIndex) + 5518U)) & S_SALT1];
            aOrbiterD = ((aWandererI + RotL64(aIngress, 3U)) + RotL64(aCarry, 53U)) + 14088261356708344656U;
            //
            aOrbiterF = ((aOrbiterF + aOrbiterA) + 13692608802007789581U) + RotL64(aNonceByteD, 22U);
            aOrbiterG = ((aOrbiterG ^ aOrbiterF) ^ 6824473946645682398U) ^ aOrbiterUpdateSaltA[(((31U - aIndex) + 4356U)) & S_SALT1];
            aOrbiterG = RotL64((aOrbiterG * 13619437545775237601U), 11U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterD) + 2072915876348570040U) + aOrbiterUpdateSaltE[((aIndex + 829U)) & S_SALT1];
            aOrbiterF = (aOrbiterF ^ aOrbiterK) ^ 7420507753044460759U;
            aOrbiterF = RotL64((aOrbiterF * 13239288539564571257U), 3U);
            //
            aOrbiterA = ((aOrbiterA + aOrbiterG) + 4677557318688502593U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 7623U)) & S_SALT1];
            aOrbiterK = (aOrbiterK ^ aOrbiterA) ^ 15081678577055628459U;
            aOrbiterK = RotL64((aOrbiterK * 16659305295251177155U), 19U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterF) + 7026792817486507482U;
            aOrbiterA = ((aOrbiterA ^ aOrbiterD) ^ 14871665922943969918U) ^ aOrbiterUpdateSaltD[(((31U - aIndex) + 6938U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 694073180313083145U), 29U);
            //
            aOrbiterG = ((aOrbiterG + aOrbiterK) + 6807734532159292872U) + RotL64(aNonceByteG, 39U);
            aOrbiterD = (aOrbiterD ^ aOrbiterG) ^ 17882797335141303280U;
            aOrbiterD = RotL64((aOrbiterD * 15439872930381050291U), 51U);
            //
            aIngress = RotL64(aOrbiterD, 34U) ^ aOrbiterF;
            aIngress = aIngress + (aOrbiterG ^ RotL64(aOrbiterK, 47U));
            aIngress = aIngress + RotL64(aOrbiterA, 3U);
            aIngress = TwistMix64::DiffuseA((aIngress + aScatter));
            //
            aWandererD = aWandererD + ((((RotL64(aCross, 29U) + aOrbiterG) + RotL64(aOrbiterK, 29U)) + RotL64(aCarry, 3U)) + aWandererUpdateSaltE[(((31U - aIndex) + 8155U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aScatter, 43U) + RotL64(aOrbiterD, 13U)) + aOrbiterK) + RotL64(aNonceByteB, 31U));
            aWandererC = aWandererC + (((((RotL64(aPrevious, 57U) + RotL64(aOrbiterG, 5U)) + aOrbiterA) + RotL64(aCarry, 53U)) + RotL64(aNonceByteF, 59U)) + aWandererUpdateSaltD[((aIndex + 1992U)) & S_SALT1]);
            aWandererG = aWandererG ^ ((RotL64(aIngress, 18U) + RotL64(aOrbiterD, 44U)) + aOrbiterF);
            aWandererI = aWandererI + ((RotL64(aScatter, 5U) + aOrbiterA) + RotL64(aOrbiterF, 53U));
            //
            aCarry = aCarry + (aWandererC ^ RotL64(aWandererD, 21U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererG, 60U));
            aCarry = aCarry + RotL64(aWandererH, 51U);
            aCarry = aCarry + RotL64(aIngress, 43U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aOperationLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteH, 10U) ^ RotL64(aNonceByteG, 43U));
            aIngress = aIngress ^ (RotL64(aOperationLaneD[((aIndex + 19271U)) & S_BLOCK1], 51U) ^ RotL64(aOperationLaneC[((aIndex + 12375U)) & S_BLOCK1], 35U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteC, 13U) ^ RotL64(aNonceByteF, 39U)) ^ RotL64(aNonceByteB, 29U));
            aCross = aCross ^ (RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 719U)) & S_BLOCK1], 52U) ^ RotL64(aOperationLaneA[((S_BLOCK1 - aIndex + 2601U)) & S_BLOCK1], 21U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 41U) ^ RotL64(aCross, 56U)) + (RotL64(aIngress, 19U) ^ RotL64(aCarry, 5U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterB = ((aWandererK + RotL64(aScatter, 13U)) + 3339283916456813609U) + RotL64(aNonceByteE, 19U);
            aOrbiterE = (((aWandererI + RotL64(aIngress, 43U)) + RotL64(aCarry, 37U)) + 11339086426180649584U) + aOrbiterAssignSaltC[((aIndex + 8134U)) & S_SALT1];
            aOrbiterI = (aWandererH + RotL64(aCross, 5U)) + 16819191669329316585U;
            aOrbiterF = (((aWandererB + RotL64(aPrevious, 21U)) + RotL64(aCarry, 11U)) + 8361916937762630725U) + aOrbiterAssignSaltA[((aIndex + 5429U)) & S_SALT1];
            aOrbiterJ = (((aWandererE + RotL64(aScatter, 54U)) + RotL64(aCarry, 51U)) + 18031328374429899857U) + RotL64(aNonceByteD, 27U);
            //
            aOrbiterB = ((aOrbiterB + aOrbiterE) + 18261756894092897276U) + aOrbiterUpdateSaltD[((aIndex + 743U)) & S_SALT1];
            aOrbiterI = ((aOrbiterI ^ aOrbiterB) ^ 4250319792907645666U) ^ aOrbiterUpdateSaltA[((aIndex + 5227U)) & S_SALT1];
            aOrbiterI = RotL64((aOrbiterI * 7053489184750217963U), 47U);
            //
            aOrbiterF = ((aOrbiterF + aOrbiterJ) + 1492411503643460886U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 2139U)) & S_SALT1];
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 17369549067879344180U) ^ RotL64(aNonceByteG, 22U);
            aOrbiterB = RotL64((aOrbiterB * 2947354306696216579U), 29U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterI) + 7301713524358676722U;
            aOrbiterF = (aOrbiterF ^ aOrbiterE) ^ 2985193736033012535U;
            aOrbiterF = RotL64((aOrbiterF * 7473297294949338265U), 57U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterB) + 14086975808140927408U;
            aOrbiterE = ((aOrbiterE ^ aOrbiterJ) ^ 10390516547834639800U) ^ aOrbiterUpdateSaltF[(((31U - aIndex) + 3824U)) & S_SALT1];
            aOrbiterE = RotL64((aOrbiterE * 11441293212275890819U), 19U);
            //
            aOrbiterI = ((aOrbiterI + aOrbiterF) + 18205555540941493267U) + RotL64(aNonceByteC, 39U);
            aOrbiterJ = (aOrbiterJ ^ aOrbiterI) ^ 16967799565443938873U;
            aOrbiterJ = RotL64((aOrbiterJ * 3009081009044782443U), 5U);
            //
            aIngress = aOrbiterB ^ RotL64(aOrbiterJ, 47U);
            aIngress = aIngress + (aOrbiterE ^ RotL64(aOrbiterI, 57U));
            aIngress = aIngress + RotL64(aOrbiterF, 3U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((((RotL64(aPrevious, 3U) + RotL64(aOrbiterF, 43U)) + aOrbiterE) + RotL64(aNonceByteB, 13U)) + aWandererUpdateSaltB[(((31U - aIndex) + 1692U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aScatter, 37U) + RotL64(aOrbiterJ, 12U)) + aOrbiterE);
            aWandererE = aWandererE + ((((RotL64(aIngress, 54U) + aOrbiterB) + RotL64(aOrbiterJ, 57U)) + RotL64(aCarry, 35U)) + aWandererUpdateSaltD[((aIndex + 7977U)) & S_SALT1]);
            aWandererK = aWandererK ^ (((RotL64(aCross, 29U) + aOrbiterB) + RotL64(aOrbiterF, 3U)) + RotL64(aNonceByteA, 21U));
            aWandererH = aWandererH + (((RotL64(aPrevious, 19U) + RotL64(aOrbiterJ, 29U)) + aOrbiterI) + RotL64(aCarry, 23U));
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererE, 29U));
            aCarry = aCarry + (aWandererI ^ RotL64(aWandererK, 5U));
            aCarry = aCarry + RotL64(aWandererB, 18U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseC(aCarry);
            //
            aExpandLaneA[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteG, 29U) ^ RotL64(aNonceByteC, 54U));
            aIngress = aIngress ^ (RotL64(aExpandLaneA[((aIndex + 10473U)) & S_BLOCK1], 5U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 23364U)) & S_BLOCK1], 21U));
            aIngress = TwistMix64::DiffuseA((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteD, 41U) ^ RotL64(aNonceByteB, 3U));
            aCross = aCross ^ (RotL64(aOperationLaneC[((S_BLOCK1 - aIndex + 3325U)) & S_BLOCK1], 21U) ^ RotL64(aOperationLaneB[((S_BLOCK1 - aIndex + 28442U)) & S_BLOCK1], 50U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 57U) ^ RotL64(aPrevious, 10U)) + (RotL64(aIngress, 35U) + RotL64(aCross, 23U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterE = (((aWandererJ + RotL64(aCross, 19U)) + RotL64(aCarry, 19U)) + 10336802574069791273U) + RotL64(aNonceByteA, 37U);
            aOrbiterA = (((aWandererH + RotL64(aScatter, 29U)) + RotL64(aCarry, 53U)) + 169025388197058936U) + aOrbiterAssignSaltD[((aIndex + 1238U)) & S_SALT1];
            aOrbiterG = (((aWandererC + RotL64(aIngress, 52U)) + RotL64(aCarry, 5U)) + 6541354188379168846U) + aOrbiterAssignSaltB[(((31U - aIndex) + 4778U)) & S_SALT1];
            aOrbiterD = ((aWandererK + RotL64(aPrevious, 41U)) + 16223920526599306104U) + RotL64(aNonceByteD, 6U);
            aOrbiterK = (aWandererI + RotL64(aIngress, 11U)) + 12756613707692514808U;
            //
            aOrbiterE = ((aOrbiterE + aOrbiterA) + 5082475548176484035U) + RotL64(aNonceByteB, 55U);
            aOrbiterG = (aOrbiterG ^ aOrbiterE) ^ 4907435526952698526U;
            aOrbiterG = RotL64((aOrbiterG * 1379692095754989215U), 3U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterD) + 14236627073831834337U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterA) ^ 11502511046130497584U) ^ aOrbiterUpdateSaltB[((aIndex + 3669U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 3460330807286625917U), 19U);
            //
            aOrbiterD = ((aOrbiterD + aOrbiterG) + 3679044835550219497U) + aOrbiterUpdateSaltD[(((31U - aIndex) + 7069U)) & S_SALT1];
            aOrbiterE = (aOrbiterE ^ aOrbiterD) ^ 11254838916686736746U;
            aOrbiterE = RotL64((aOrbiterE * 8631695922983532915U), 11U);
            //
            aOrbiterG = (aOrbiterG + aOrbiterK) + 10582608424233200966U;
            aOrbiterA = (((aOrbiterA ^ aOrbiterG) ^ 10449735026385340313U) ^ aOrbiterUpdateSaltC[((aIndex + 3824U)) & S_SALT1]) ^ RotL64(aNonceByteE, 17U);
            aOrbiterA = RotL64((aOrbiterA * 7363770199734997411U), 43U);
            //
            aOrbiterK = ((aOrbiterK + aOrbiterE) + 4628253464169957835U) + aOrbiterUpdateSaltE[((aIndex + 2259U)) & S_SALT1];
            aOrbiterD = (aOrbiterD ^ aOrbiterK) ^ 17664454668473204465U;
            aOrbiterD = RotL64((aOrbiterD * 4234720298731378527U), 27U);
            //
            aIngress = RotL64(aOrbiterG, 3U) ^ aOrbiterA;
            aIngress = aIngress + (aOrbiterD ^ RotL64(aOrbiterE, 27U));
            aIngress = aIngress + RotL64(aOrbiterK, 57U);
            aIngress = TwistMix64::DiffuseB((aIngress + aScatter));
            //
            aWandererC = aWandererC ^ (((RotL64(aCross, 3U) + RotL64(aOrbiterE, 13U)) + aOrbiterD) + RotL64(aNonceByteH, 51U));
            aWandererJ = aWandererJ + ((((RotL64(aPrevious, 14U) + RotL64(aOrbiterG, 29U)) + aOrbiterD) + RotL64(aCarry, 37U)) + aWandererUpdateSaltA[(((31U - aIndex) + 6187U)) & S_SALT1]);
            aWandererH = aWandererH ^ (((RotL64(aIngress, 39U) + aOrbiterA) + RotL64(aOrbiterD, 44U)) + RotL64(aNonceByteF, 5U));
            aWandererI = aWandererI + ((((RotL64(aScatter, 27U) + aOrbiterE) + RotL64(aOrbiterA, 21U)) + RotL64(aCarry, 3U)) + aWandererUpdateSaltE[(((31U - aIndex) + 1722U)) & S_SALT1]);
            aWandererK = aWandererK ^ ((RotL64(aCross, 57U) + RotL64(aOrbiterK, 5U)) + aOrbiterE);
            //
            aCarry = aCarry + (aWandererH ^ RotL64(aWandererC, 11U));
            aCarry = aCarry + (RotL64(aWandererI, 39U) ^ aWandererJ);
            aCarry = aCarry + RotL64(aWandererK, 58U);
            aCarry = aCarry + RotL64(aIngress, 47U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneB[S_BLOCK1 - aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteH, 35U) ^ RotL64(aNonceByteC, 22U));
            aIngress = aIngress ^ (RotL64(aExpandLaneB[((aIndex + 5846U)) & S_BLOCK1], 5U) ^ RotL64(aExpandLaneA[((aIndex + 13954U)) & S_BLOCK1], 51U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ (RotL64(aNonceByteF, 3U) ^ RotL64(aNonceByteG, 11U));
            aCross = aCross ^ (RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 161U)) & S_BLOCK1], 29U) ^ RotL64(aOperationLaneC[((aIndex + 30868U)) & S_BLOCK1], 50U));
            aCross = TwistMix64::DiffuseB((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aPrevious, 39U) + RotL64(aCross, 24U)) ^ (RotL64(aIngress, 57U) ^ RotL64(aCarry, 5U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterB = ((aWandererJ + RotL64(aScatter, 11U)) + 17264605017518259932U) + RotL64(aNonceByteA, 43U);
            aOrbiterD = (((aWandererF + RotL64(aPrevious, 54U)) + RotL64(aCarry, 51U)) + 15209184354580778643U) + RotL64(aNonceByteC, 41U);
            aOrbiterA = (((aWandererA + RotL64(aCross, 41U)) + RotL64(aCarry, 3U)) + 3299527965014731384U) + aOrbiterAssignSaltF[(((31U - aIndex) + 4020U)) & S_SALT1];
            aOrbiterI = (((aWandererI + RotL64(aIngress, 27U)) + RotL64(aCarry, 21U)) + 16293096431816127821U) + aOrbiterAssignSaltE[((aIndex + 5421U)) & S_SALT1];
            aOrbiterF = (aWandererH + RotL64(aCross, 19U)) + 11031983436878828337U;
            //
            aOrbiterB = ((aOrbiterB + aOrbiterD) + 9188018632448236358U) + aOrbiterUpdateSaltD[((aIndex + 5321U)) & S_SALT1];
            aOrbiterA = ((aOrbiterA ^ aOrbiterB) ^ 13420816400363406556U) ^ aOrbiterUpdateSaltC[((aIndex + 2744U)) & S_SALT1];
            aOrbiterA = RotL64((aOrbiterA * 10958221259662190519U), 21U);
            //
            aOrbiterI = (((aOrbiterI + aOrbiterB) + 2485063384097917101U) + aOrbiterUpdateSaltF[((aIndex + 7886U)) & S_SALT1]) + RotL64(aNonceByteE, 6U);
            aOrbiterD = (aOrbiterD ^ aOrbiterI) ^ 3089135816938128264U;
            aOrbiterD = RotL64((aOrbiterD * 8813152992957361153U), 3U);
            //
            aOrbiterF = (aOrbiterF + aOrbiterI) + 10730544971770435788U;
            aOrbiterB = ((aOrbiterB ^ aOrbiterF) ^ 10431767565618874806U) ^ aOrbiterUpdateSaltB[(((31U - aIndex) + 7495U)) & S_SALT1];
            aOrbiterB = RotL64((aOrbiterB * 4723078464590561545U), 13U);
            //
            aOrbiterA = (aOrbiterA + aOrbiterF) + 14883796491656899074U;
            aOrbiterI = ((aOrbiterI ^ aOrbiterA) ^ 13465877783538483706U) ^ RotL64(aNonceByteD, 5U);
            aOrbiterI = RotL64((aOrbiterI * 14311686051108108503U), 37U);
            //
            aOrbiterD = (aOrbiterD + aOrbiterA) + 13322163435314643713U;
            aOrbiterF = (aOrbiterF ^ aOrbiterD) ^ 3307316600284371955U;
            aOrbiterF = RotL64((aOrbiterF * 12337846092069506365U), 29U);
            //
            aIngress = RotL64(aOrbiterI, 23U) ^ aOrbiterB;
            aIngress = aIngress + (aOrbiterA ^ RotL64(aOrbiterF, 36U));
            aIngress = aIngress + RotL64(aOrbiterD, 3U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererF = aWandererF ^ ((RotL64(aScatter, 19U) + RotL64(aOrbiterB, 3U)) + aOrbiterD);
            aWandererJ = aWandererJ + (((((RotL64(aCross, 5U) + aOrbiterB) + RotL64(aOrbiterI, 27U)) + RotL64(aCarry, 5U)) + RotL64(aNonceByteB, 49U)) + aWandererUpdateSaltF[(((31U - aIndex) + 37U)) & S_SALT1]);
            aWandererA = aWandererA ^ (((RotL64(aIngress, 47U) + aOrbiterF) + RotL64(aOrbiterA, 12U)) + aWandererUpdateSaltC[((aIndex + 1425U)) & S_SALT1]);
            aWandererH = aWandererH + ((((RotL64(aPrevious, 56U) + RotL64(aOrbiterD, 43U)) + aOrbiterA) + RotL64(aCarry, 29U)) + RotL64(pNonce, 29U));
            aWandererI = aWandererI ^ ((RotL64(aScatter, 29U) + aOrbiterI) + RotL64(aOrbiterA, 57U));
            //
            aCarry = aCarry + (aWandererA ^ RotL64(aWandererI, 60U));
            aCarry = aCarry + (RotL64(aWandererF, 19U) ^ aWandererH);
            aCarry = aCarry + RotL64(aWandererJ, 29U);
            aCarry = aCarry + RotL64(aIngress, 37U);
            aCarry = TwistMix64::DiffuseA(aCarry);
            //
            aExpandLaneC[aIndex] = aIngress;
        }
    
        for (std::size_t aIndex = 0U; aIndex < static_cast<std::size_t>(S_BLOCK); aIndex += 1U) {
            //
            aPrevious = aIngress;
            //
            aIngress = 0U;
            aIngress = aIngress ^ (RotL64(aNonceByteG, 4U) ^ RotL64(aNonceByteA, 29U));
            aIngress = aIngress ^ (RotL64(aExpandLaneC[((aIndex + 19386U)) & S_BLOCK1], 21U) ^ RotL64(aExpandLaneB[((S_BLOCK1 - aIndex + 30528U)) & S_BLOCK1], 41U));
            aIngress = TwistMix64::DiffuseB((aIngress ^ aDomainWordIngress));
            //
            aCross = 0U;
            aCross = aCross ^ ((RotL64(aNonceByteE, 47U) ^ RotL64(aNonceByteC, 13U)) ^ RotL64(aNonceByteH, 29U));
            aCross = aCross ^ (RotL64(aExpandLaneA[((S_BLOCK1 - aIndex + 20608U)) & S_BLOCK1], 56U) ^ RotL64(aOperationLaneD[((S_BLOCK1 - aIndex + 3832U)) & S_BLOCK1], 37U));
            aCross = TwistMix64::DiffuseA((aCross ^ aDomainWordCross));
            //
            aScatter = (RotL64(aCarry, 29U) + RotL64(aPrevious, 56U)) ^ (RotL64(aIngress, 5U) + RotL64(aCross, 43U));
            aScatter = TwistMix64::DiffuseC((aScatter ^ aDomainWordScatter));
            //
            aOrbiterK = (((aWandererB + RotL64(aIngress, 27U)) + RotL64(aCarry, 3U)) + 5697928251815176134U) + aOrbiterAssignSaltC[(((31U - aIndex) + 8081U)) & S_SALT1];
            aOrbiterJ = ((aWandererG + RotL64(aCross, 51U)) + RotL64(aCarry, 47U)) + 337587740689259575U;
            aOrbiterG = ((((aWandererF + RotL64(aPrevious, 18U)) + RotL64(aCarry, 19U)) + 4927686903263973950U) + aOrbiterAssignSaltA[(((31U - aIndex) + 2639U)) & S_SALT1]) + RotL64(aNonceByteD, 15U);
            aOrbiterC = (aWandererI + RotL64(aScatter, 35U)) + 3742409032569801033U;
            aOrbiterE = ((aWandererA + RotL64(aCross, 43U)) + 1608092659172197650U) + RotL64(aNonceByteA, 34U);
            //
            aOrbiterK = (aOrbiterK + aOrbiterJ) + 15848744267145717509U;
            aOrbiterG = ((aOrbiterG ^ aOrbiterK) ^ 15300174177963339253U) ^ RotL64(aNonceByteE, 37U);
            aOrbiterG = RotL64((aOrbiterG * 5771922862677667319U), 53U);
            //
            aOrbiterC = (aOrbiterC + aOrbiterE) + 14162868453323648628U;
            aOrbiterK = ((aOrbiterK ^ aOrbiterC) ^ 12020167069983729869U) ^ aOrbiterUpdateSaltA[((aIndex + 616U)) & S_SALT1];
            aOrbiterK = RotL64((aOrbiterK * 2071080217680099017U), 11U);
            //
            aOrbiterJ = (aOrbiterJ + aOrbiterG) + 16259538291658723956U;
            aOrbiterC = ((aOrbiterC ^ aOrbiterJ) ^ 8516686212464112245U) ^ aOrbiterUpdateSaltD[((aIndex + 3655U)) & S_SALT1];
            aOrbiterC = RotL64((aOrbiterC * 4731296903548893627U), 29U);
            //
            aOrbiterE = (aOrbiterE + aOrbiterK) + 3722184575520553132U;
            aOrbiterJ = ((aOrbiterJ ^ aOrbiterE) ^ 5663609293306386784U) ^ aOrbiterUpdateSaltE[(((31U - aIndex) + 3817U)) & S_SALT1];
            aOrbiterJ = RotL64((aOrbiterJ * 14364218128780764749U), 43U);
            //
            aOrbiterG = (((aOrbiterG + aOrbiterC) + 15265344442454471986U) + aOrbiterUpdateSaltC[(((31U - aIndex) + 3733U)) & S_SALT1]) + RotL64(aNonceByteB, 55U);
            aOrbiterE = (aOrbiterE ^ aOrbiterG) ^ 3050323350098829515U;
            aOrbiterE = RotL64((aOrbiterE * 5890624677162388135U), 19U);
            //
            aIngress = RotL64(aOrbiterK, 46U) ^ aOrbiterG;
            aIngress = aIngress + (aOrbiterJ ^ RotL64(aOrbiterE, 3U));
            aIngress = aIngress + RotL64(aOrbiterC, 27U);
            aIngress = TwistMix64::DiffuseC((aIngress + aScatter));
            //
            aWandererB = aWandererB + ((((RotL64(aScatter, 43U) + aOrbiterC) + RotL64(aOrbiterE, 26U)) + RotL64(aCarry, 13U)) + RotL64(aNonceByteF, 45U));
            aWandererA = aWandererA ^ ((RotL64(aCross, 35U) + RotL64(aOrbiterC, 13U)) + aOrbiterG);
            aWandererG = aWandererG + ((((RotL64(aIngress, 23U) + aOrbiterK) + RotL64(aOrbiterJ, 37U)) + RotL64(aCarry, 39U)) + aWandererUpdateSaltD[(((31U - aIndex) + 4567U)) & S_SALT1]);
            aWandererI = aWandererI ^ ((RotL64(aPrevious, 58U) + RotL64(aOrbiterJ, 53U)) + aOrbiterG);
            aWandererF = aWandererF + ((((RotL64(aCross, 3U) + aOrbiterJ) + RotL64(aOrbiterC, 5U)) + RotL64(aNonceByteC, 17U)) + aWandererUpdateSaltB[((aIndex + 4916U)) & S_SALT1]);
            //
            aCarry = aCarry + (RotL64(aWandererG, 11U) ^ aWandererI);
            aCarry = aCarry + (RotL64(aWandererF, 3U) ^ aWandererB);
            aCarry = aCarry + RotL64(aWandererA, 39U);
            aCarry = aCarry + RotL64(aIngress, 29U);
            aCarry = TwistMix64::DiffuseB(aCarry);
            //
            aExpandLaneD[S_BLOCK1 - aIndex] = aIngress;
        }
    }
    {
        // kdf-a-matrix-diffusion: yeah
    
        TwistMasking::MaskBraid(TwistMaskBraidType::kC, aExpandLaneA, aExpandLaneB, S_BLOCK, aOperationLaneA, S_BLOCK, aDomainWordMaskMutateA);
    }
    {
        // kdf-a-matrix-diffusion: yeah
    
        TwistMasking::MaskBraid(TwistMaskBraidType::kA, aExpandLaneC, aExpandLaneD, S_BLOCK, aOperationLaneB, S_BLOCK, aDomainWordMaskMutateB);
    }
    {
        // kdf-a-matrix-diffusion: yeah
    
        TwistMasking::MaskBraid(TwistMaskBraidType::kB, aExpandLaneD, aExpandLaneA, S_BLOCK, aOperationLaneC, S_BLOCK, aDomainWordMaskMutateA);
    }
    {
        // kdf-a-matrix-diffusion: yeah
    
        TwistMasking::MaskBraid(TwistMaskBraidType::kA, aExpandLaneB, aExpandLaneC, S_BLOCK, aOperationLaneD, S_BLOCK, aDomainWordMaskMutateB);
    }
}

void TwistExpander_Kerpal_0006::Seed(TwistWorkSpace *pWorkSpace,
                                 TwistFarmSalt *pFarmSalt,
                                 std::uint64_t pNonce,
                                 std::uint8_t *pSourceInput,
                                 std::uint8_t *pPassword,
                                 unsigned int pPasswordByteLength) {
    TwistExpander::Seed(pWorkSpace, pFarmSalt, pNonce, pSourceInput, pPassword, pPasswordByteLength);
    if ((pWorkSpace == nullptr) || (pFarmSalt == nullptr) || (pSourceInput == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aSource = TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(0));
    [[maybe_unused]] std::uint8_t *aDestination = TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(1));
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    [[maybe_unused]] std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    [[maybe_unused]] std::uint8_t *aSnowLaneC = pWorkSpace->mSnowLaneC;
    [[maybe_unused]] std::uint8_t *aSnowLaneD = pWorkSpace->mSnowLaneD;
    [[maybe_unused]] std::size_t *aIndexList256A = mIndexList256A;
    [[maybe_unused]] std::size_t *aIndexList256B = mIndexList256B;
    [[maybe_unused]] std::size_t *aIndexList256C = mIndexList256C;
    [[maybe_unused]] std::size_t *aIndexList256D = mIndexList256D;
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledA = &(pWorkSpace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledB = &(pWorkSpace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkSpace->mKeyBoxA[H_KEY_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkSpace->mKeyBoxB[H_KEY_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteA = &(pWorkSpace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteB = &(pWorkSpace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledA = &(pWorkSpace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledB = &(pWorkSpace->mMaskBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadA = &(pWorkSpace->mMaskBoxA[H_MASK_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadB = &(pWorkSpace->mMaskBoxB[H_MASK_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteA = &(pWorkSpace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteB = &(pWorkSpace->mMaskBoxB[0][0]);

    // [seed]
    {
        mSource = pSourceInput;
    }
    {
        TwistMemory::ZeroKeyBoxA(aKeyBoxUnrolledA);
        TwistMemory::ZeroKeyBoxB(aKeyBoxUnrolledB);
        TwistMemory::ZeroMaskBoxA(aMaskBoxUnrolledA);
        TwistMemory::ZeroMaskBoxB(aMaskBoxUnrolledB);
    }
    {
        // Making snow counter: aria 256
    
        TwistSnow::Aria256Counter(aSource, aSnowLaneC);
    
        // Making snow counter: aes 256
    
        TwistSnow::AES256Counter(aSource, aSnowLaneA);
    
        // Making snow counter: cha cha 20
    
        TwistSnow::ChaCha20Counter(aSource, aSnowLaneB);
    
        // Making snow counter: sha 256
    
        TwistSnow::Sha256Counter(aSource, aSnowLaneD);
    }
    mSnow = aSnowLaneC;
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseAConstants), &(mDomainBundleInbuilt.mPhaseASalts));
    TwistInvest::InvestBlockKeyBoxA(aExpandLaneA, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxB(aExpandLaneC, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxB(aExpandLaneD, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxA(aExpandLaneB, pWorkSpace);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltA, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltC, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltE, mDomainBundleEphemeral.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltA, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltC, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltE, mDomainBundleEphemeral.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltA, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltC, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltE, mDomainBundleEphemeral.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(mDomainBundleEphemeral.mPhaseAConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseAConstants), &(mDomainBundleEphemeral.mPhaseASalts));
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltA, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltC, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltE, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseASalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseASalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(pWorkSpace->mDomainBundle.mPhaseAConstants));
    mSnow = aSnowLaneA;
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseBConstants), &(mDomainBundleInbuilt.mPhaseBSalts));
    TwistInvest::InvestBlockKeyBoxA(aExpandLaneA, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxB(aExpandLaneC, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxB(aExpandLaneD, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxA(aExpandLaneB, pWorkSpace);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltA, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltC, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltE, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltA, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltC, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltE, mDomainBundleEphemeral.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltA, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltC, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltE, mDomainBundleEphemeral.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(mDomainBundleEphemeral.mPhaseBConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseBConstants), &(mDomainBundleEphemeral.mPhaseBSalts));
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltA, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltC, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltE, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseBSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneB, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseBSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneA, &(pWorkSpace->mDomainBundle.mPhaseBConstants));
    mSnow = aSnowLaneB;
    KDF_A(pNonce, &(mDomainBundleInbuilt.mPhaseCConstants), &(mDomainBundleInbuilt.mPhaseCSalts));
    TwistInvest::InvestBlockKeyBoxA(aExpandLaneA, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxB(aExpandLaneC, pWorkSpace);
    TwistInvest::InvestBlockKeyBoxB(aExpandLaneD, pWorkSpace);
    TwistInvest::InvestBlockMaskBoxA(aExpandLaneB, pWorkSpace);
    pFarmSalt->Derive(aExpandLaneC, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltA, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltC, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltE, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltA, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltC, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltE, mDomainBundleEphemeral.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltA, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltB, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltC, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltD, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltE, mDomainBundleEphemeral.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(mDomainBundleEphemeral.mPhaseCConstants));
    KDF_B(pNonce, &(mDomainBundleEphemeral.mPhaseCConstants), &(mDomainBundleEphemeral.mPhaseCSalts));
    pFarmSalt->Derive(aExpandLaneC, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltA, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltC, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltE, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterAssign.mSaltF);
    pFarmSalt->Derive(aExpandLaneD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseCSalts.mOrbiterUpdate.mSaltF);
    pFarmSalt->Derive(aExpandLaneA, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltA, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltB, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltC, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltD, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltE, pWorkSpace->mDomainBundle.mPhaseCSalts.mWandererUpdate.mSaltF);
    TwistFarmConstants::Derive(aExpandLaneB, &(pWorkSpace->mDomainBundle.mPhaseCConstants));
}

void TwistExpander_Kerpal_0006::TwistBlock(TwistWorkSpace *pWorkSpace,
                                       std::uint64_t pNonce,
                                       std::uint8_t *pSourceInput,
                                       std::uint8_t *pDestinationOutput) {
    TwistExpander::TwistBlock(pWorkSpace, pNonce, pSourceInput, pDestinationOutput);
    if ((pWorkSpace == nullptr) || (pDestinationOutput == nullptr)) { return; }
    [[maybe_unused]] std::uint8_t *aSource = TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(0));
    [[maybe_unused]] std::uint8_t *aDestination = TwistWorkSpace::GetBuffer(pWorkSpace, this, static_cast<TwistWorkSpaceSlot>(1));
    [[maybe_unused]] std::uint8_t *aExpandLaneA = pWorkSpace->mExpansionLaneA;
    [[maybe_unused]] std::uint8_t *aExpandLaneB = pWorkSpace->mExpansionLaneB;
    [[maybe_unused]] std::uint8_t *aExpandLaneC = pWorkSpace->mExpansionLaneC;
    [[maybe_unused]] std::uint8_t *aExpandLaneD = pWorkSpace->mExpansionLaneD;
    [[maybe_unused]] std::uint8_t *aWorkLaneA = pWorkSpace->mWorkLaneA;
    [[maybe_unused]] std::uint8_t *aWorkLaneB = pWorkSpace->mWorkLaneB;
    [[maybe_unused]] std::uint8_t *aWorkLaneC = pWorkSpace->mWorkLaneC;
    [[maybe_unused]] std::uint8_t *aWorkLaneD = pWorkSpace->mWorkLaneD;
    [[maybe_unused]] std::uint8_t *aOperationLaneA = pWorkSpace->mOperationLaneA;
    [[maybe_unused]] std::uint8_t *aOperationLaneB = pWorkSpace->mOperationLaneB;
    [[maybe_unused]] std::uint8_t *aOperationLaneC = pWorkSpace->mOperationLaneC;
    [[maybe_unused]] std::uint8_t *aOperationLaneD = pWorkSpace->mOperationLaneD;
    [[maybe_unused]] std::uint8_t *aSnowLaneA = pWorkSpace->mSnowLaneA;
    [[maybe_unused]] std::uint8_t *aSnowLaneB = pWorkSpace->mSnowLaneB;
    [[maybe_unused]] std::uint8_t *aSnowLaneC = pWorkSpace->mSnowLaneC;
    [[maybe_unused]] std::uint8_t *aSnowLaneD = pWorkSpace->mSnowLaneD;
    [[maybe_unused]] std::size_t *aIndexList256A = mIndexList256A;
    [[maybe_unused]] std::size_t *aIndexList256B = mIndexList256B;
    [[maybe_unused]] std::size_t *aIndexList256C = mIndexList256C;
    [[maybe_unused]] std::size_t *aIndexList256D = mIndexList256D;
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledA = &(pWorkSpace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyBoxUnrolledB = &(pWorkSpace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadA = &(pWorkSpace->mKeyBoxA[H_KEY_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowReadB = &(pWorkSpace->mKeyBoxB[H_KEY_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteA = &(pWorkSpace->mKeyBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aKeyRowWriteB = &(pWorkSpace->mKeyBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledA = &(pWorkSpace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskBoxUnrolledB = &(pWorkSpace->mMaskBoxB[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadA = &(pWorkSpace->mMaskBoxA[H_MASK_A - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowReadB = &(pWorkSpace->mMaskBoxB[H_MASK_B - 1][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteA = &(pWorkSpace->mMaskBoxA[0][0]);
    [[maybe_unused]] std::uint8_t *aMaskRowWriteB = &(pWorkSpace->mMaskBoxB[0][0]);

    // [twister]
    std::memcpy(pDestinationOutput, pWorkSpace->mWorkLaneD, S_BLOCK);
}

const TwistDomainSaltSet TwistExpander_Kerpal_0006::kPhaseASalts = {
    {
        {
            0xC5DA10C2321876B9ULL, 0x40E04F15528A5AA8ULL, 0x8E819067EE694E16ULL, 0xB28A61DFBBF9203BULL, 
            0xD563A981CA607CD3ULL, 0x8BCF46D7C22837A1ULL, 0x76A3F9619440AB7CULL, 0x2B490A0242D9BA28ULL, 
            0x7F1291D1F4D87D54ULL, 0x9066FEE22D40F603ULL, 0xD49515083E054593ULL, 0xCA5853AC1BF7605DULL, 
            0x9619646130C1BA32ULL, 0xB97A99153216BD24ULL, 0x5232470A622EDE82ULL, 0xAAB4D421DE61DCDCULL, 
            0xD1986821043FC534ULL, 0xBD238A61FB288539ULL, 0x6F601F0995630A41ULL, 0x6E38CAF41975BC0BULL, 
            0x1DDC4B41B74D3E81ULL, 0xDDD548CE6096B094ULL, 0x121805F14A82C446ULL, 0x28CE89C35454EF11ULL, 
            0xE82AA3FA5B61CF45ULL, 0x571DC2827619604BULL, 0x19E32C1BACD16324ULL, 0x68540101095A8A8BULL, 
            0x99437397CB08C772ULL, 0xEE9FED9E418180C1ULL, 0xCC98DA6DD9EABCC3ULL, 0xB89C04EA79108D24ULL
        },
        {
            0xFC03C89B67D207C8ULL, 0xAF2C6960928E9632ULL, 0x14B5C33853077959ULL, 0xF73A54011D3B0545ULL, 
            0x30207532DA17290CULL, 0x4551866A5A334D75ULL, 0x471DB70072D0F677ULL, 0xD6A6BA238AA92AE0ULL, 
            0xEA79476655B7A314ULL, 0xB3CCA561A2836AFDULL, 0x98DCCF38133B06B0ULL, 0x63EF67DF68D26CACULL, 
            0x3243CE03A60BDB88ULL, 0x563C5298D25A9270ULL, 0x5C4B8F003C23C7B7ULL, 0x5B4075F51FD24981ULL, 
            0x8A3634599051E4E7ULL, 0x5BD2CE3FBF844794ULL, 0x9DC56684AE69D2F6ULL, 0x74B4BEAD743CD043ULL, 
            0xF2D0E504AB43B2DFULL, 0xE8590D30B1131EB9ULL, 0x414332DFA769BB41ULL, 0x6732CDA2622C7E41ULL, 
            0x0479A8EE54B6C4A2ULL, 0x053A3E23AD21B421ULL, 0xB33DFE350F3688A8ULL, 0x908CE5309F070C3CULL, 
            0xEEA1C0A71DC32A1FULL, 0x19315497EDB05F8EULL, 0xAED265FD15CDF1CFULL, 0xCA7D6038DD4638F5ULL
        },
        {
            0x3F18C27CFA44F5A3ULL, 0x792A7EF8BBD3AF60ULL, 0x6B7F9362AE3CCCC2ULL, 0x0E5C2F533D5BE0E2ULL, 
            0xA2DAF99EADE248C7ULL, 0xBEB070D79F314E24ULL, 0x9DC2EE96F7224886ULL, 0xBF4738D6B6E27314ULL, 
            0x5CC06D64E510FBC9ULL, 0x9D0E22DD823ACCBAULL, 0x7B869ADB2B805BDFULL, 0x6EEE379F9A941D56ULL, 
            0xE6CA73867B39DF34ULL, 0x5FEAF9E4E618BCCDULL, 0x864FE4A84736C056ULL, 0xD3CF57CAD8DD9184ULL, 
            0x080D8F46AB65125DULL, 0xFA699C71C15B4C81ULL, 0x429668D28AB918ABULL, 0xBC6CBC3D23720B88ULL, 
            0x7B66DA3401553EACULL, 0xF16C1EF7EE054325ULL, 0xDC78EF18AD130D25ULL, 0x51D0406CC723F609ULL, 
            0x4A63A7338C66519CULL, 0x20AFA63A0458AF2EULL, 0x68538E6E9E52125AULL, 0x14F703B8927200BEULL, 
            0x1B8C64CD71D61314ULL, 0xB6018113B1AE1B70ULL, 0x489B803E03ACFA7DULL, 0x5BE8F0C980E2F5BAULL
        },
        {
            0x8064EFCD9F4AE83FULL, 0x705E5ADF23FFED29ULL, 0x3F35BAD196F8E6D4ULL, 0xFD5AD62D3A46D67BULL, 
            0x747104D01FEA6E6CULL, 0x2F9E8247D2AE9B10ULL, 0x3302699A3A0EF355ULL, 0x8B3D4700C801C525ULL, 
            0x1F21B70C64F8BCC4ULL, 0xF68A39CA61887867ULL, 0x550C6921F5DA3883ULL, 0xC1A615C02434C899ULL, 
            0xFB1C8B78B8CB01CDULL, 0x5DC74C377643C8A5ULL, 0xC6F791EB450526E7ULL, 0x4EF3A7542E9AA2CFULL, 
            0xA037F56AEB130E3AULL, 0x8E2D46CFB4D8BF66ULL, 0xEF875634FEC93A39ULL, 0x97F3B4B0827E2200ULL, 
            0x311017DAC7C3F049ULL, 0x0C02B0EB22B599D3ULL, 0x0E239406A173ED79ULL, 0xD0196014CADB050EULL, 
            0xD21DF64034541CFBULL, 0x880B7C6679D62BFCULL, 0x9DD4A5BACE904421ULL, 0xB16E2DCDE8DEE007ULL, 
            0x5B9A1CC66CCEC4B2ULL, 0xAF90574F0691B10BULL, 0x2001852EE372DE1CULL, 0xFA3D6E292AD54E0BULL
        },
        {
            0xFEF99F1EC6019D7CULL, 0xC9F0FDCB17C512F7ULL, 0xD271B2EEEAD9E024ULL, 0xF3E051266212AE06ULL, 
            0xF2F1DCEB61722E69ULL, 0xEBEB4986558B21C6ULL, 0x9643E2D28DA896D8ULL, 0xCC5E112FB7096809ULL, 
            0x0423F8C526302776ULL, 0x76C6BD988A4A9FC5ULL, 0x07E5F8C7102CF975ULL, 0x7C9A0968A904FFECULL, 
            0xB8CD401A402DDBCCULL, 0xBE9470E74C437BE4ULL, 0x12E539AD7A3DE886ULL, 0x07578BC4892EF4D2ULL, 
            0x20319C90261C3190ULL, 0xBA20CACE01D9CCB1ULL, 0x625D110350056062ULL, 0x7670EE2CF235B153ULL, 
            0x762D1635B3F75246ULL, 0x934749073ECF0B11ULL, 0x3AD7680105A2D808ULL, 0x5A023086E6747C87ULL, 
            0x943D457EC60386D0ULL, 0x80902925985326D6ULL, 0x73F8A7E7554AC2D9ULL, 0xAD88C05E449F0C3CULL, 
            0x3003287DDB96DB42ULL, 0x1CEBB389233C0AC0ULL, 0x447AB69B8ABC0DF1ULL, 0xBFBB9ADBA3E0D0F3ULL
        },
        {
            0x7FABB0F940054535ULL, 0xAF9B1937221C30EDULL, 0x16AE2E095D1F791FULL, 0x4AC0E3978DA8A6B0ULL, 
            0xDF365A076D9F8771ULL, 0x401D49A1EC464721ULL, 0xEEFE37279C819BC8ULL, 0xED9DB12769C2933EULL, 
            0xF6A386F344B6A48CULL, 0xF0A85CAD4C255F79ULL, 0xA2F76E8AEA7FDB48ULL, 0x910A8294EC398E46ULL, 
            0xE563557D2F92E563ULL, 0x981D3DBC41AA9B66ULL, 0x8549F9166B8539B1ULL, 0x461CE6C3EB01FE9AULL, 
            0x5E625C1141218A15ULL, 0x63F91D18C30F4297ULL, 0x73B3D296ACB31920ULL, 0x360F628A09D81A98ULL, 
            0x7CDBCDD257B8A89FULL, 0x151D74E5127515B4ULL, 0x77EBE6020BB4F9EAULL, 0x6EC65CCB614EDF28ULL, 
            0xD30538E198B532EFULL, 0x3095139C7AA43A2BULL, 0x4A5D38FDF118E54EULL, 0xAF66A75876577D18ULL, 
            0xFE2BD381864DCF40ULL, 0x05A9B8A11842C1F7ULL, 0x5BE3408779982A42ULL, 0xC7ABF1DC529CE6E9ULL
        }
    },
    {
        {
            0xC46046413A3ABB28ULL, 0xB0BDBA3D304694EDULL, 0x95136412BBA03000ULL, 0x4375E18A479B9CCEULL, 
            0x4656E324C0AB5F11ULL, 0x5687924477AC9DD1ULL, 0x1E0C225706C8B647ULL, 0x78996AD974AB53A9ULL, 
            0xF505DADDD2FBD9CDULL, 0xC1E068BC71A3F9F5ULL, 0xA96C8B406093204FULL, 0x0ECD95F7773C35B4ULL, 
            0x47C02A4C87D06AEAULL, 0x6EBB786AF1AF8039ULL, 0x36DA947BE2BE39CFULL, 0x7EDE100DE8285403ULL, 
            0x19B32240CFBC6EC1ULL, 0xF05E10F18D43FEBEULL, 0xED173312EA64244FULL, 0x379F00EBB9BA36B1ULL, 
            0x3CE330631D61BDDFULL, 0x85DFFA25A4C7FCFEULL, 0xCAF7B11611199387ULL, 0xFBB82042E19C1C9BULL, 
            0x13C59DE10A8D9603ULL, 0x6AD52066B0510D4DULL, 0x96AD7C99FC15E48EULL, 0x63193E5AECCCB935ULL, 
            0x42F28C2D77D9787DULL, 0x7098972E74B7335DULL, 0x541618FA196779ADULL, 0xE8D8B0A880FB97E1ULL
        },
        {
            0x7907A6892138D240ULL, 0x0315B6A898722C9DULL, 0x3D810EA0506B404CULL, 0xD85457B0A3776DACULL, 
            0xB143651694100A4CULL, 0x7BEB69638C586FE4ULL, 0x7894DE83770560D9ULL, 0x6DE4C13621B56581ULL, 
            0x0AC33836C561DB17ULL, 0xFE967330E9222D2CULL, 0x6B98E519C992AFB1ULL, 0xB4B151339E2C1088ULL, 
            0x9DF37A94E8B866C0ULL, 0x94C9ED2E61D43B04ULL, 0xD988E8838A0C0B88ULL, 0xFD8D6A86A5817B3BULL, 
            0x2BFBAD7BD9411C1AULL, 0xBD263BC0F9A5E2E1ULL, 0x36017DB293626143ULL, 0xF9405E16EC32804DULL, 
            0xD34E1CB2F97CE8ACULL, 0x4108708845E69D29ULL, 0x15A7289442D868EDULL, 0x15F8D18C5EEF8B8EULL, 
            0xA5C95BC14CBBB12AULL, 0xBA10BE0CA8096ACDULL, 0x834CA924AB42570DULL, 0xFFB8ECC3ADF6E9F6ULL, 
            0x127BB2E61E348641ULL, 0xA29A31A255CBEA2EULL, 0x22166E44F489E3F8ULL, 0xF0D9AA11A2F80D4CULL
        },
        {
            0x638DE7074789FAE0ULL, 0x511C250840C38714ULL, 0x6CE0C9BD9C1BDCBBULL, 0x9562E5D827DF9E0CULL, 
            0xFD4AEF17B5B3974BULL, 0x21E51B16FDC62107ULL, 0x6CE3C2C81068307CULL, 0xDC4013F5BD56936FULL, 
            0xF9C369DB19FAD39EULL, 0x9E9FFC6B8A66CFF8ULL, 0xA33B15EC2B4B2985ULL, 0xCEC17164AD5B3D4CULL, 
            0xBCACB2FC3F092EBFULL, 0xB2BE905AD0C9BF29ULL, 0x3475DB56447E6BAFULL, 0xCA3ED157972DC012ULL, 
            0x10825F8F86B4D74DULL, 0xE08315F54A85FAF3ULL, 0x4680E749DC3E866DULL, 0xB222600777041078ULL, 
            0x3C96F5A6DA9EA7F6ULL, 0x3A6863FB4B47EE1EULL, 0x6E3C818EE869572CULL, 0x45D4A14AA9CC519CULL, 
            0x45CB893EF5A7F490ULL, 0x6979835ED9C9D2B7ULL, 0xF99BC18418B337E1ULL, 0x910B0E2FFF5565C4ULL, 
            0xC7D4ED45CE3466D1ULL, 0xBFEA225F00AC801DULL, 0xA756DB001B5D9EAAULL, 0x80AE0D458147D089ULL
        },
        {
            0x6B7181E96362F6CFULL, 0x2D20C537595339C1ULL, 0xC2099DCA5E069C11ULL, 0x312333ED2CB0DCDFULL, 
            0xDEFFADB3247F930EULL, 0xADCFFF9E216F65A5ULL, 0xEC8C00CF62EDBF73ULL, 0x5FA71435566F70EFULL, 
            0x2101EF6790F39891ULL, 0x9B17BD58E7597745ULL, 0x0B720922A6492FB7ULL, 0x72BE407A4B1B60C0ULL, 
            0x4BE6293B50DA87B4ULL, 0x1543F9EFF871B094ULL, 0x86C6691E9775B39DULL, 0x4D565956B521EC4AULL, 
            0x505C82D6F70A6D41ULL, 0x4F2768ED7721614CULL, 0xE413392FE54A5B54ULL, 0x6C64FE2F71E3DC90ULL, 
            0x0C231BBA4A5B1A79ULL, 0x2C505B70F75C2FD8ULL, 0x4478D214C14D09EDULL, 0xF3EC436878FDA0C4ULL, 
            0xDD33164DD74D8A9CULL, 0x3FDFD324A4B1E432ULL, 0x5FADA2B82A79FD93ULL, 0xE12D2343AB874677ULL, 
            0x14B4BB866072EDBDULL, 0x1DA35D70573E7ABCULL, 0xE31D61F96E043178ULL, 0xC6A81E0F82A08E6EULL
        },
        {
            0xADE2F6EFA2EF48A8ULL, 0xD68AF98E87694737ULL, 0xD49791EC773EB981ULL, 0xD7D3C1BBAF3144E2ULL, 
            0xD206E5400CCB7BF2ULL, 0x162DB70420F0CFE6ULL, 0x9CBAFB0E635948CBULL, 0x8DD1FBA74531450DULL, 
            0x0618D095B809E024ULL, 0xFA252B18D98DAEA0ULL, 0xCB7BCBFCC59A7B12ULL, 0xB671D58B8B103BBBULL, 
            0x17E57BC77A95EB48ULL, 0xD73AB2E9821CC549ULL, 0x671B718B03E79B83ULL, 0xD5DD2BC5624F4116ULL, 
            0x2490D3C661B7F66CULL, 0xDCA9B2692619AEC8ULL, 0xB3A9ADD880BEE6F9ULL, 0x2555BC9B4C865E88ULL, 
            0x5C2E6B754FF59720ULL, 0x2ED753A691C50E8EULL, 0xEF7AB57C798FBE90ULL, 0x7E152E588A024729ULL, 
            0x7CC010B4297BFBAAULL, 0x634FA09F652EF7DAULL, 0x62D3AF24FE6135C3ULL, 0x0225900715BD5F94ULL, 
            0x5DFF8B293037DAD5ULL, 0x4CA08EE73443FF87ULL, 0xA96A599228960174ULL, 0xF3E01523B1E0A225ULL
        },
        {
            0xDD7D4429208C9A59ULL, 0xB6E466AFEEC7C420ULL, 0x838C31211C2C2D5FULL, 0xD3F909F178A942BBULL, 
            0x0C2EFFED2F979BE3ULL, 0x85D2581162080251ULL, 0x9BFFB6435149F47DULL, 0x55627CA49011A372ULL, 
            0x7255E27BEB2CAEB2ULL, 0x111F566F72D2B612ULL, 0x434E519FDD252EC3ULL, 0xBE88E562E01D2F77ULL, 
            0xB2D17C0FED819D1CULL, 0x005E2E3926D99E41ULL, 0x850EC8FC3DC134B3ULL, 0x00001F787965ABA8ULL, 
            0xCA5CBBD6FFC2D9A6ULL, 0xD6A765B8725CDD07ULL, 0xC36BCC01E5439441ULL, 0x1FFA1334D63C365DULL, 
            0xF35551F53B9FE139ULL, 0x4FC976BC2DCF9E60ULL, 0xDA263283BAFB87A6ULL, 0xA27D3AA7874D8101ULL, 
            0x39637DB81B2C8569ULL, 0x52705FFAD8A3620AULL, 0x7137031D1555903FULL, 0x684EE62AFA4370A1ULL, 
            0x9E9B230FEC057249ULL, 0xEB8D48B2A33661F5ULL, 0x51E177DB927F8282ULL, 0xE84D3F58BAD1744CULL
        }
    },
    {
        {
            0xEC11E7FF8204811BULL, 0xB341DBA3683915B4ULL, 0x4357C2CBF756920CULL, 0x8E30DF9606B67943ULL, 
            0x5E8D7C105A981F31ULL, 0x0A63FBB3827BFA10ULL, 0x28BF35DF3241EE99ULL, 0x6695CB1B193EFD1AULL, 
            0x261CF91CCCBBCFF5ULL, 0x9564C8434B2D0D50ULL, 0xF953815A6A19A52BULL, 0x01A7FDB3F3DD5571ULL, 
            0x7D78645DDD3D710EULL, 0xFD502988A390CD5CULL, 0x2245B4D58D8E0C8EULL, 0xE6B4C9B0B53015D7ULL, 
            0x5485C8EB5920BB6DULL, 0xD80968D431518E5BULL, 0xDF55E9914C852395ULL, 0xACB69AFD1EE10F51ULL, 
            0x542FF2D3EC858615ULL, 0x1A43AC52506605E5ULL, 0xD07F433A53790C6BULL, 0x5F3188D8D98D5A54ULL, 
            0xC939F69BB415658DULL, 0x8489548E4CC8EAF2ULL, 0x2BAB1AAFDCEEAA24ULL, 0x51FE63443E14CF0FULL, 
            0xED5401C3138DF50FULL, 0x318672FF5C36FEB8ULL, 0x2E297C3B303874F8ULL, 0x1204DF36C548D61FULL
        },
        {
            0x128B6637C86FEBB5ULL, 0x5971087434041660ULL, 0x2FB84E153EB4634CULL, 0x503E84B1F25CEDEAULL, 
            0x5C9780C78D5FAC9CULL, 0xA59812974339D975ULL, 0x3EEFC9C297FEDC08ULL, 0xDAD5013767CFE0A8ULL, 
            0x3DCE1CA6CF93899BULL, 0x8CB3A8DDEFF00D26ULL, 0xE9D6F817189C4298ULL, 0xF49114D0C5E7A453ULL, 
            0xD51E127151A48193ULL, 0xB7B9E0BEE5336EC8ULL, 0x0F4C5DB51CA555A5ULL, 0x97126976D9594ADBULL, 
            0xEFEFCC51121361B7ULL, 0x84B04DCA5DCBED1CULL, 0x273D4A81F3E832FCULL, 0xA4040CAE653B914EULL, 
            0x41A061975C5A31B7ULL, 0xF961C0EC2C918B0CULL, 0xCF63636A85A0018CULL, 0x8A6DE81124440B57ULL, 
            0x3DE678E50617787FULL, 0x2D74D2F305972756ULL, 0x8CBF7429C13DB3C7ULL, 0x8C96036005319A1EULL, 
            0x06C94ED8B22BCD93ULL, 0x2CDF1FC67D8B4C9BULL, 0x75C9F23A6D72946EULL, 0xBFB808262BCD52DFULL
        },
        {
            0x4B79343345E48A1DULL, 0x1A7BE888613BC0C5ULL, 0xA270B66B1BFDC847ULL, 0x631C3C4697B35F26ULL, 
            0x3B94534B1042B705ULL, 0x9A4EFEE82C7D708CULL, 0xE3063A251FB2EAA3ULL, 0x9828C1F5368CCA26ULL, 
            0x9DF4286513005CAAULL, 0x0597804956ACF0A9ULL, 0x18F5480D0B42565BULL, 0x8238830C143492E4ULL, 
            0xBA4B8397667AB042ULL, 0xAC5290CBA9A643B7ULL, 0xFDA9E83817B440F9ULL, 0x037C432079B0827BULL, 
            0x6F9715A18F24B038ULL, 0x88FFCB4119D02FDDULL, 0x4494D2A492194243ULL, 0x8835202FA1F0A1F8ULL, 
            0xD5E17351E3DB68D2ULL, 0xE43EA35D24F9E3D5ULL, 0xF03F52063D4CDC5AULL, 0x136C896B3ECDF8BBULL, 
            0x7432D8C9BDF16D84ULL, 0xA19174D8BEE4BCB5ULL, 0x616A56473349B764ULL, 0x279DE01571BF3AC9ULL, 
            0x7E940D11907D5520ULL, 0xA5841FA8DC930C02ULL, 0x4C48258F8CEAE785ULL, 0x38E9A3749E2D74EDULL
        },
        {
            0x1C1B022E6E42E677ULL, 0xCC3B540B980955CDULL, 0x394F04CE8D363FA6ULL, 0x6A6E2B19488C719EULL, 
            0xF6151283E1CFBC7DULL, 0xD696420DAED072EBULL, 0xBD9F9F0F264299BDULL, 0x2445D40C4BD7ADBCULL, 
            0x352A744147F9B32BULL, 0x40B1914F0DEBC6CFULL, 0xD7D8D91ED7B2F8AAULL, 0xBC0E5884DA87CB4EULL, 
            0xC01A7842F9D21596ULL, 0xFBCB2705DD6EAAB4ULL, 0xDA0867ECBA5CBEC1ULL, 0xB986E8B54D4C2560ULL, 
            0xB36E6742D3D4F229ULL, 0xCC1AE45714BFDE12ULL, 0x2EC124FBDCB7ABDCULL, 0x9BA9C0C63926C94CULL, 
            0x67803CCFAEA48C5AULL, 0x73BDA9E849C1BAC3ULL, 0x305C83AB1CA25D8CULL, 0xB094446665BC3997ULL, 
            0xC64C97AE95896BA7ULL, 0x394F59F4191FACF3ULL, 0xADDBDD425853662FULL, 0x9BAD59AA85B91C9AULL, 
            0x94F52165BFFA7B8DULL, 0xF0AD57507E678AF7ULL, 0xF5B174CAA8DDCB01ULL, 0xF25AA16FAC226D39ULL
        },
        {
            0xEE13EC35F2451895ULL, 0x4BEDFC90CED775EDULL, 0xE95B5006D6AC40E6ULL, 0x1F8375EA7C9E6D56ULL, 
            0xDC284021F18C5707ULL, 0x7E897A781CA05F04ULL, 0x68B8E80ACC8130AAULL, 0xB16CCCB079B81882ULL, 
            0xB132316BA6565687ULL, 0xB3D5A8B06CB800C0ULL, 0x6B20B6B7A834CCF3ULL, 0xF3612C820F53B29DULL, 
            0x732C52146965B306ULL, 0x505127D315AB5FCAULL, 0xDD179C96053BAC4FULL, 0xC6D3723E612B2479ULL, 
            0x5EFD4D171E9DE75AULL, 0x482F9859334872ACULL, 0x8C6736C4E3AF12B8ULL, 0x151747AD07EB279AULL, 
            0xDA2A4EA85E17B5A1ULL, 0xBC16C1893932ED21ULL, 0x9469E5EB69FAC8DAULL, 0xB9A8A016FD5C3780ULL, 
            0x97E6A82E22FD2836ULL, 0x759FBF42CD1937B1ULL, 0x3FE10C1815B8B4DDULL, 0x599CA30673B2E8F1ULL, 
            0xD7DB3348E0BA60BDULL, 0x13C7CD9CA8FBA601ULL, 0x672B457EC1F41B64ULL, 0x3AE5978FAA12F3FAULL
        },
        {
            0x58265554EC540C7FULL, 0x7DF223E04FF354F2ULL, 0x2E691814962C61BFULL, 0x906A8182FE0A250BULL, 
            0xE74BBBFB955EA6EBULL, 0x47191010025C2357ULL, 0x2920D106B429A70FULL, 0x8E873657F3EA2A37ULL, 
            0x6BC7472032577F6DULL, 0xCF2B1BC4AD6684FEULL, 0xD6725836CD9BA263ULL, 0x3EE1C97EA7ED78F8ULL, 
            0xC61ECD81BC81885FULL, 0x3498D8DD1B795A68ULL, 0xD7C4D531EC5FA025ULL, 0x455F1B5E89EA3D39ULL, 
            0x33259EB5B56D1598ULL, 0x07655B8B4E88E3CAULL, 0xC9A1564DAAC7F033ULL, 0xABF82C908B586F54ULL, 
            0x5831194E202F4135ULL, 0x3C2207DA33ABF392ULL, 0xAB353E2E82C029B4ULL, 0xE1D2A0B0D6F65B33ULL, 
            0x6A0A3517F8062FAAULL, 0x7E6150C286274AB6ULL, 0x6EDF32B2A8360F4BULL, 0xB6EF7CAF13586F5FULL, 
            0x1F7BC9799503B9CCULL, 0x280D4D91ECDBD4FEULL, 0x9980D1909A19A77AULL, 0x0737BEC16CDFC8E7ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Kerpal_0006::kPhaseAConstants = {
    0x448178816E10223CULL,
    0x41FB101259474C4AULL,
    0x877505F433181981ULL,
    0x448178816E10223CULL,
    0x41FB101259474C4AULL,
    0x877505F433181981ULL,
    0x4041615B28DFAE05ULL,
    0x9E4A373EFD4CE167ULL,
    0xCD,
    0x04,
    0x0E,
    0xEC,
    0x42,
    0x40,
    0x2D,
    0x5C
};

const TwistDomainSaltSet TwistExpander_Kerpal_0006::kPhaseBSalts = {
    {
        {
            0x02464CA60FF923F0ULL, 0x838A95D1CC45AA9CULL, 0x2CE0470FE60AA11BULL, 0xA5130E4506D342BAULL, 
            0xCA11B28D855D9BC9ULL, 0x2DE4F2636ABC1E33ULL, 0x13F6C6B1FADEF142ULL, 0x404A29C9E430C702ULL, 
            0x76B618564853CF84ULL, 0x6F3BF16A895F7B37ULL, 0x82C75E1172BECF85ULL, 0xD5E7BB01911BE01FULL, 
            0x2C4F1D5806CBE2B9ULL, 0xC07DD74F798BBF6AULL, 0x60312C5E5AC60D73ULL, 0x23C1B19FF909FD07ULL, 
            0x4B40A1E528F393BFULL, 0x909310D6EC740772ULL, 0x04E5E38ABA5A09AAULL, 0x5E84053EE17BD945ULL, 
            0x1C52FC7ED3C4AFEDULL, 0x02EC3DFC0E414BEEULL, 0x7C5925DBC8D5BDDEULL, 0x56D2BB0052CC9355ULL, 
            0xD0FA3AB1C34BCD02ULL, 0x63DC7F77B2A0F578ULL, 0x70122C288DCE02B1ULL, 0xB0F2141A1E256E99ULL, 
            0xC2295F26206244E8ULL, 0x2AE4134A55DB2B5EULL, 0x72725FFF6FACCEC8ULL, 0x52E598373A6D7666ULL
        },
        {
            0x1D9006D85F661C8CULL, 0xFDC9BBE9F743B67EULL, 0x851AB030B6090EB8ULL, 0xC332D3F9DB64424CULL, 
            0xBDA11EB48EFD6196ULL, 0x292FE24803B389D2ULL, 0x01923DA725EDB36EULL, 0xB24C4B89367B29D4ULL, 
            0x946E0ED60828C031ULL, 0x01AD5EF94FA7991FULL, 0x2A4E58FD568A94BDULL, 0xCB2DAC57A7BA9628ULL, 
            0x37D5BF6DEA3B4F30ULL, 0xBB9A1925F50ED98CULL, 0x2D55A2A7C2D6B2A9ULL, 0x09CF53CD9CC72086ULL, 
            0x870158EE9614AB76ULL, 0xC58C52BE7BDAF186ULL, 0x566CC87C996FFDBBULL, 0x2A6A99C72A6AF431ULL, 
            0xC45C00C302A0F877ULL, 0x15463042A1B54CF7ULL, 0xC67D27E11A0A76E8ULL, 0x523E867423170339ULL, 
            0x7CC25C6D50B0D58EULL, 0x4C5E79BD99DF75F8ULL, 0x047911539013D6C5ULL, 0x66BE9BF786CF8E66ULL, 
            0xBC765D8EF17DEFBAULL, 0x5551884C517027ABULL, 0xE0F78695A0DF98A9ULL, 0x2A167724039A45C0ULL
        },
        {
            0x4741FD7AE1407635ULL, 0xD4D5F0C01DABCBC3ULL, 0x89EC73DB7091E6CBULL, 0xFC52CB09A5994928ULL, 
            0x83763A02F8217600ULL, 0x529AEF67C9193514ULL, 0x1FDC61A116232359ULL, 0x9F206A346854699BULL, 
            0x8A02781E6F0C3CD7ULL, 0x4055965089DFF501ULL, 0x123B117F8C084F71ULL, 0xED2FBBD49BC182C7ULL, 
            0x296E65B0091E4FC1ULL, 0x7A6842425F74430FULL, 0x56FAB40E3B954F19ULL, 0x2CEE8CAC1A6F190BULL, 
            0xE09E2C2C44C9A36DULL, 0x6A3436664910A3C0ULL, 0x629B499A829A4C11ULL, 0xB194E9361145DB64ULL, 
            0xF95A2E90B754C479ULL, 0x3992EAA40523C22DULL, 0x88A38E4DB8464EECULL, 0x349864D617F24CE7ULL, 
            0x18A0C65C36CB0440ULL, 0x2B70711E16B5D572ULL, 0xECFBFD3D8F5B7D1DULL, 0xFF191DAF0DCFBB8FULL, 
            0x69DEE213D5FA45BCULL, 0xF5A44CA6E3720C1EULL, 0xEB1536502F8549FEULL, 0x130C837A63DFE589ULL
        },
        {
            0x7549489D9C926FE4ULL, 0x3FBDDDB604CE9D41ULL, 0x966852287EE96D88ULL, 0x2B4C4DAF3A7DF169ULL, 
            0xE523068C20A32107ULL, 0xA1D8BA8029D13148ULL, 0x88807FD6B1F9F92AULL, 0xADF0C976ABB30267ULL, 
            0x77055D3EAC216096ULL, 0x688E18BE9B72D5BEULL, 0x5838B36CF3C611D4ULL, 0x6E2539FA60E5CA0EULL, 
            0x114F6377C97CD8BAULL, 0x6A6888EB7528997EULL, 0x099DDCDE02D967EEULL, 0xB3101E1329D6A55FULL, 
            0xD62CB81FCF842E0DULL, 0xDF7DB26E8A39A75AULL, 0xD7369BAA4BFB6CDFULL, 0xEA2BABF3CC33A37EULL, 
            0x7CA2AD5559676ADCULL, 0xF50968893F2CA9F3ULL, 0xDB090E9716A4B372ULL, 0x1561341EA5222925ULL, 
            0x002DAC2963FB0BD4ULL, 0x8E8E27B834C0A06AULL, 0xCA1879EF0BA9F7F7ULL, 0x36057270EA8A443CULL, 
            0xBF81BC8A13AABB23ULL, 0x8B70AE1E23386E10ULL, 0xE949AE13C52B137AULL, 0xC7E5B7E20699B834ULL
        },
        {
            0xE0DFCBE77545C68BULL, 0x9B4E66C302143177ULL, 0xEA78764BCCE35AE6ULL, 0xD14002B3CA44E6C1ULL, 
            0x83F418F1ABDF14CDULL, 0x862B214B4E693DF9ULL, 0xB83B31425389DB0EULL, 0x2B30B02F1D15AF81ULL, 
            0x78C629C7670EA949ULL, 0x94D60F184BC1D7FDULL, 0x5FD5D76821DAE7ABULL, 0x59866CEC6005D0A2ULL, 
            0x8CCA8EBE279009CDULL, 0xE0299CCE2E61E8B7ULL, 0x5CDC8D0A3F9D8AA6ULL, 0x0F24C0B1957D7098ULL, 
            0x3633985B3E07526CULL, 0x81419E3B29F364FEULL, 0x535666C396FABB67ULL, 0xAFBD2424CA3B1421ULL, 
            0x1C99A744BDD49B33ULL, 0x6C886CB8D7563A47ULL, 0xD2FAB6C7162B826AULL, 0x53B4DAAF12CA2B63ULL, 
            0xA49E3846A1203C58ULL, 0xEDBB5AD0303D8B3FULL, 0x354B4C458B51D881ULL, 0x97B5E2CC46D4EDF4ULL, 
            0xA412216FD062CFA9ULL, 0x545CAD8615AA0700ULL, 0xA6777893570107BBULL, 0x5F3083E15948EE17ULL
        },
        {
            0x26C493A5FC6DDD27ULL, 0x9ADD8D3EE12373F0ULL, 0xA7070D3CCE9D75E8ULL, 0x7CF7F2CD8A3AD92DULL, 
            0x4CC81AC7A616143EULL, 0x87809B8AB3F74A7AULL, 0x5ECC57DFF36B1ECAULL, 0x31685D46314375BEULL, 
            0x1E2E36D1BAE5F3F8ULL, 0x103F4E6855877D95ULL, 0x1601525BC7386EFEULL, 0x14B58F705E3AC794ULL, 
            0x54EA590A3BF72885ULL, 0x31FD8D78D71A367CULL, 0x64F7472E2D1B938EULL, 0x23C151364F34F273ULL, 
            0x75B99C073EB0CAEAULL, 0x75A0F4AFBC97C4FAULL, 0xC011F699289C186DULL, 0x4567E9F13A50A34AULL, 
            0x845FFE11634B741CULL, 0x96BF35C9941DC1FDULL, 0x5B7599179379776DULL, 0x691EA5C149ACBB90ULL, 
            0xDC37E674673F945EULL, 0x2B63A479C6C89391ULL, 0x58310A5234D44CC7ULL, 0xB4FB633D16E51178ULL, 
            0xFC7E1A51087F8C03ULL, 0x2125521393358995ULL, 0x4B666D5A23E5863AULL, 0xAF289A8B98BC4C6DULL
        }
    },
    {
        {
            0x604E4712F9631534ULL, 0x9315A96B1453D7B0ULL, 0x7C6E805CD1C0E042ULL, 0x281CA67EFE924D1AULL, 
            0xF0C7EA961DB1D414ULL, 0xBEA62D4B147FBF2DULL, 0x466FE24C66B27EDCULL, 0x9DE14B644E7BBF76ULL, 
            0xD8E1B1A2B551D690ULL, 0x60958EEF96596B63ULL, 0xC322E0EA4999F32AULL, 0x62559FE9B4EEBD86ULL, 
            0xC01658E8D877E916ULL, 0xB7F8B719FBEF6194ULL, 0x4EC51359C29AC9F2ULL, 0x211D52D6DAD8A59CULL, 
            0x216B9ACBDB7C92CFULL, 0x410EA0C2F0290C69ULL, 0x0894D037309C917DULL, 0x6392765D976EBC48ULL, 
            0xFA29B6042572E818ULL, 0xCDBE900174CEA571ULL, 0x60AFE9A8ABCDC977ULL, 0x01791BCF32DC2377ULL, 
            0x227FEB62F68CE470ULL, 0x2C8BEDFB4F51A661ULL, 0xE36103CA81249258ULL, 0x872A3A736E3ADCC9ULL, 
            0x89F71591A5715DB0ULL, 0xF6E25E627940399DULL, 0x852643165EBB9D80ULL, 0xE94DF3468DB0E3E5ULL
        },
        {
            0x0EDF07A800564EC3ULL, 0xE596493C062D8F2EULL, 0xA00DC6724607085DULL, 0xD91701762F9FC623ULL, 
            0x18C0EF2030F30442ULL, 0xA80D3CA1A1B44BCCULL, 0xE4ED75AEFC1A5EA8ULL, 0x4FA32DB8F6DCA8BFULL, 
            0x6D3F2F06AB94B1C4ULL, 0x8FD48AA01B1593C0ULL, 0x65E282D9F82E862CULL, 0xA85B696ED2CA8162ULL, 
            0x0E81CFBAC622628CULL, 0xAD20181263C6FF72ULL, 0xA1F4D2CFD916C3F7ULL, 0xCD7BE460E5BF0E03ULL, 
            0x6F7D7771F1A5EB23ULL, 0x65293A25E28DF8EDULL, 0x91F91572E6F1EA10ULL, 0x4394F8064739395CULL, 
            0x733727D8ABEA1A23ULL, 0x8E712281CA9DA234ULL, 0x473E0F450B31DB12ULL, 0x20195E9FD0FD2AC5ULL, 
            0x252DF0901C19DE03ULL, 0xFD19CAFDEE1F1B67ULL, 0x11186CF8F63BB1C9ULL, 0x98F57FB0B7EB0D95ULL, 
            0x54464AF9E3724CFCULL, 0x04775BC3005F181EULL, 0x5BB8120B468E0E80ULL, 0x24C7736EAB70BA26ULL
        },
        {
            0xC5A3A2AE69581560ULL, 0x6986DF4DCF5571B5ULL, 0xDD4F17E0B4C4E026ULL, 0x549DA8CFC0BBAB07ULL, 
            0x14CBCBD6E14ED2EAULL, 0x656BA069E8A1105BULL, 0x291CB60B4BECB77EULL, 0x7680449489AF7C11ULL, 
            0x13EFC990ED62B07EULL, 0x9804906A889E2448ULL, 0xFA818130B5537907ULL, 0xB6FDB7D1D34C3F79ULL, 
            0xB574221118E75AA4ULL, 0x210FFA3B642868CBULL, 0xFF4E182F09EB6E51ULL, 0x089B845A115D9691ULL, 
            0x0C977DF9CE0072F2ULL, 0x8E8E8A2286FA12FCULL, 0x143BC5037647996AULL, 0x1028F9454BEEB0EEULL, 
            0xFD2C6B3F36903F35ULL, 0x7FB72B0884A549FCULL, 0xD5ECA62835840BF1ULL, 0xF881B9841FEAB200ULL, 
            0x1F70104D0B43AD4BULL, 0x8B4E7BE9A69F9AF3ULL, 0x86D4E8370F5A4C51ULL, 0xA1AA9F93508CB89FULL, 
            0x762E70A9D0445A6AULL, 0xA63BF889A534FC5BULL, 0x2156834B8C6D0E61ULL, 0xB72B4B1363BDDF5AULL
        },
        {
            0xCEEBBB7D2E5BFA30ULL, 0xFF54C4195FD9F844ULL, 0x77797AB6BC2BE7ABULL, 0x6944646B59CB3B74ULL, 
            0x5203D7412919A6F9ULL, 0xFD49970241604E95ULL, 0x9CC53082BA43C1A5ULL, 0xB3604D09773205CAULL, 
            0x703E2F6001394E15ULL, 0x77CFA84C4944DB7FULL, 0x9603C3893EFF38E7ULL, 0xA3B87420A4E74374ULL, 
            0x833F0256F585443DULL, 0xE9E6AAE688BFE127ULL, 0x559D9F6BFCC53582ULL, 0x6C79FEA2DA4432DFULL, 
            0x7943EFEBBF7FAEC5ULL, 0x54B6F8F5E20C3A01ULL, 0x07C56F1AEDF8B313ULL, 0x14F112213F2BB116ULL, 
            0x586250173D01EC8EULL, 0x9211F0BEAC925695ULL, 0x81A7D51C5EE8AE4FULL, 0x9E8A23AE6ABB5140ULL, 
            0x6E72148B441D1464ULL, 0x656371BDEFB620DBULL, 0xAB3A6969C63F47D0ULL, 0xB2FD88A1741BA5C8ULL, 
            0x8C2098F0C2B6E5E0ULL, 0x17ED9993204A6331ULL, 0xE5AC397F56A70273ULL, 0xF8F498ECDDB6AC75ULL
        },
        {
            0xBF42BB1E3CE5A5C5ULL, 0xEAF21EC11774E1DFULL, 0xF33F13DF002ED21FULL, 0xB19332960C89FC62ULL, 
            0x97428FE461042817ULL, 0x54BD4EC42B7BC329ULL, 0xBC72E806BA77E832ULL, 0x499C4859D20BE48FULL, 
            0x9317F8FB6A72DD18ULL, 0x755CDD8178C42D46ULL, 0xFEE30B808B1E5726ULL, 0xDDC567858CE15BBBULL, 
            0xD21FDF2FB25775F0ULL, 0xC7B2062CB8B9B0FEULL, 0xB4ECDD933380A8BAULL, 0x4457FEBA16A698A3ULL, 
            0xCE0B779BAE973613ULL, 0x1DA077C9117AAC0CULL, 0x506EA4F8915FC818ULL, 0x4F9D54F8464BBF30ULL, 
            0x51C8E7FB5BC2E99CULL, 0xD099432C288B7C5FULL, 0xE73E6C1927D49E68ULL, 0x1B57BAA9F8E95CADULL, 
            0x75B7B0BF952FFE2CULL, 0x3DC68A2009724CD4ULL, 0x3F8E27CE1A6619B5ULL, 0x2BB6022CAEE94983ULL, 
            0xEA2AB9E699BE3C09ULL, 0xBB5381F53E883090ULL, 0xD910EBC6AE088FC9ULL, 0xB2A02C036EF2F839ULL
        },
        {
            0x1BE4E2EB8D0D1A17ULL, 0xA0C37A1174059F20ULL, 0x6429DC1BE6297FCBULL, 0x73242DEFD0D253FEULL, 
            0x072C8D75C904B541ULL, 0xB1061B40FD9441ECULL, 0xE687893DDD496B6FULL, 0x14FDB5E5446FE0F5ULL, 
            0x52BA332A5EC850FBULL, 0x9A589DBF1827A7AFULL, 0x8998AA4C605439D9ULL, 0x09CE5E62B094A2C4ULL, 
            0x6B4A0005D26F878CULL, 0x218144F512E1DD8AULL, 0xA92969AD6BA60113ULL, 0x337B6A878ABB684BULL, 
            0xA15B16480089AE49ULL, 0x348FD911CBABCA41ULL, 0x53E9E0D6FFC02873ULL, 0xA5EB2FADFFF93FD9ULL, 
            0x9E9D5DAA94E921E9ULL, 0x9D45315E25A5D8FEULL, 0x8E92D71EDCB0B797ULL, 0xA5826D553A987B9AULL, 
            0x23DE792BB189E2CBULL, 0x1484C53FF92BEA3FULL, 0x403520561FF1B532ULL, 0xE89AA37A16614F3EULL, 
            0x864E102075D71D94ULL, 0xA8524A9675A13D03ULL, 0xC48E0A868C6ADF29ULL, 0x1A732E66A86B5809ULL
        }
    },
    {
        {
            0xF701E114E47CAA4CULL, 0xD79E2E462A858947ULL, 0x2797149F55EDD285ULL, 0x79697E85C5EC6990ULL, 
            0x510108A853872E2FULL, 0x614B9DC54DDABED6ULL, 0x39584C1F90737B70ULL, 0xDC4BB4FF134E4C15ULL, 
            0x0827A48F7DA615F8ULL, 0x159C449708ED5EDFULL, 0xD04B42842DF99DD4ULL, 0x422683651B75ED6EULL, 
            0xA3ED21BFF6E093A3ULL, 0xFE9A944B37227AC0ULL, 0xF2E6C71BA1B48EC8ULL, 0xFBDFC0D69AAE3C61ULL, 
            0x95E5635511AFF9E5ULL, 0xF8D4F50A43EB5515ULL, 0xBBEED89B9C23580EULL, 0x0AB7079154EE2541ULL, 
            0x96197E9927CCC733ULL, 0x829236A3F2C11ACAULL, 0x4CE68B322A707E49ULL, 0x2E3FF5ED6F1F4D02ULL, 
            0x60CEC52258FB922BULL, 0xD20A4AA80476EC56ULL, 0xB2E87232D8AE84F6ULL, 0xF366EC2D02E88445ULL, 
            0x472025D8E7AA7339ULL, 0x76F101AC80C52355ULL, 0x2D6D7C769CFC1ED7ULL, 0x8ED880E5B29FF6D4ULL
        },
        {
            0x055F7DD786489788ULL, 0xC07DF69C1DCCB32CULL, 0xE4271042511A2D4BULL, 0x63D5F2A1CF54BB21ULL, 
            0x39094FA3612A652AULL, 0x288F7623951D42D8ULL, 0x6B8E6E29F8373CB0ULL, 0xACDC95B43168DB1DULL, 
            0xE80478252E993D91ULL, 0x8023A8D50D6B416FULL, 0xE249EB7151F2A763ULL, 0x9CBCA372261E2A7BULL, 
            0x0EF698E5B8F88231ULL, 0x103F3ADC65EF65B3ULL, 0x7D0A8701DB6CE076ULL, 0x68FD8671433BB4B2ULL, 
            0xAE05A7C6B10AED6AULL, 0x2738711C6776D4DBULL, 0xE9AD76AC63540F6DULL, 0x640D9E53E016EC8DULL, 
            0x03F52E1E2570129BULL, 0x06CF13D97CD75A66ULL, 0xA0023128A9834E08ULL, 0x067BA953C2E6416BULL, 
            0x2BAA67FB14CD1037ULL, 0x084A72C538ACF1DAULL, 0x3E62DB8A72C64B97ULL, 0x5CE8BFA1BA5FDFB0ULL, 
            0x00AE40F036B8DC26ULL, 0xDBE072A6C8AF2F3FULL, 0xB7FAF40FFDAFDF9DULL, 0x5E734DFCDA026D9EULL
        },
        {
            0x33561130978573D3ULL, 0x16FA05DF81F628AEULL, 0x313D4E3DFE80C7E1ULL, 0xCD551B8CFFD04F30ULL, 
            0x825CFED2B324A0E4ULL, 0x7B2C79CDDB35B253ULL, 0x0377E3A06C3B47D8ULL, 0xE974FC4D3D10CC73ULL, 
            0x42F23CAE52757E74ULL, 0x914EDD576B36BC1DULL, 0xA7E0B96CB678B123ULL, 0xDE35E9F6EEC16D78ULL, 
            0x73B7328D0ED0C508ULL, 0x84819AF840BC12EEULL, 0x211201BDC1A6166AULL, 0xBD7882E3288E1C0BULL, 
            0x7E89CDEB494AA96FULL, 0x978ABA674FAD7359ULL, 0xFB6AC669E3FFF25FULL, 0x2E0C63C72333FF81ULL, 
            0x369FACC468FDB541ULL, 0x86E72797F804527EULL, 0x2C7058BF8AB8E853ULL, 0xF6CA7A1FA0B5EE44ULL, 
            0x21981DC0DC512413ULL, 0x508F75A642FE618CULL, 0x1437CC91920D9E8CULL, 0x57B07073DC8B9950ULL, 
            0x046080E84011D058ULL, 0xFA5ED0E383F5A822ULL, 0xCFF37A773193137AULL, 0xD3A1F320CE22FABAULL
        },
        {
            0xBD616E4AA0C8DCC2ULL, 0x22F2A63E2C05EE9CULL, 0x65A8B7361ECFC8EBULL, 0xE18F8AF15438E0BEULL, 
            0x6DCB9DAB748D2690ULL, 0xD166E73B7AF1D105ULL, 0x36A83EE538B3DAC9ULL, 0x3E501CE458D0B078ULL, 
            0xC4322B5BE16D4380ULL, 0xEAC6506212A0C518ULL, 0x0129AF4C149C3F95ULL, 0xC1E5E46653447052ULL, 
            0x3D7BB50964E29C12ULL, 0x0A2013F63EC2AE7FULL, 0x32C591F2647AAA49ULL, 0x43A635A57D627CF1ULL, 
            0xFCE85EC1C0BF3CD7ULL, 0x32DCC92EB69A7D53ULL, 0x6CE767A876562207ULL, 0xD41A5308D4D71B79ULL, 
            0x97C44EC1E5F4F345ULL, 0xAF3C21E34EC4769EULL, 0x6551C18304A492C4ULL, 0x8E0CF8299D205E25ULL, 
            0x6B6FCA9AA8647EDBULL, 0x3710CAF57C6276A3ULL, 0x98AB2ABC3BD405A9ULL, 0x56711DD3A1ECF5D6ULL, 
            0x4C87C6E8FBDD3CC7ULL, 0x56A4D08FB6BACA1EULL, 0xEA0A765190DE9018ULL, 0x419E18071D962581ULL
        },
        {
            0x6BB7AF404EF2847AULL, 0x84092BE51D94F953ULL, 0xACFE93BAB82015ECULL, 0x33B8D9DBEB56C447ULL, 
            0xD3A20E0B61D7951AULL, 0x7AB2F52859ACF7C4ULL, 0x58396FDADD9D1D52ULL, 0x64058324D2A96FDFULL, 
            0x3CF67A6155242FBEULL, 0x77237406509EB622ULL, 0x15D95548EBA9FEDEULL, 0xF144D151D4F71ED5ULL, 
            0x05924DAE6875F2F7ULL, 0x0423BEF9D47B420BULL, 0x13EE5633628CAAE7ULL, 0xD4EC99B806378723ULL, 
            0x6EABF5DCF07E3AAEULL, 0x91059E48AE98CBBBULL, 0x675E789529DC31D1ULL, 0xA504214BFAB1CE25ULL, 
            0x21AEBAE226CE01ADULL, 0x65B4B361DE6706BCULL, 0x7A675FF4F2E9C13FULL, 0x857CA3999BCC43CDULL, 
            0x6FA338F16EB452A5ULL, 0xED33E4A60690F20DULL, 0x25A0B545AB954D66ULL, 0x3B63501D7A51D088ULL, 
            0x0F93CDE595338A39ULL, 0x1EB844A6B4C1A56FULL, 0x21590E2122FDB3FFULL, 0xC62487B885D7D583ULL
        },
        {
            0xCD914508C6CB3EF9ULL, 0xCAF29EC924E93DABULL, 0x043978E496105344ULL, 0xA2E933CB3063264DULL, 
            0x82BB5000E525641FULL, 0xA374EF8ED012796EULL, 0x7297CCEEC56910FBULL, 0xACFD8C53FF553C96ULL, 
            0xAE99CCE43C594352ULL, 0xA9CA719C7F0A89C6ULL, 0x87C9285E1629437DULL, 0x83B35EC7C1309819ULL, 
            0x2FE507BC9430EDC9ULL, 0xACA9C81FCEFB05B2ULL, 0x158E9418E1A45B16ULL, 0xCF85978187126242ULL, 
            0xCC4F76FA6F0F4B24ULL, 0x3A7CC9F75CAC88CBULL, 0x3B1B1B6C885E0C63ULL, 0xA897B2FD61D449E4ULL, 
            0x8C5021B6A4E8C42FULL, 0x626585DFD037C8D3ULL, 0xC42771A18DAC2D3CULL, 0xFE9F1975FEF877B4ULL, 
            0x5BF86CE748692F7AULL, 0xEAAE650D2CB94019ULL, 0x2760FB21A2118C5BULL, 0x7F3FBBCF164AB628ULL, 
            0x9B1DB5691826BBA2ULL, 0xC0643D70CE9BD6A5ULL, 0x3E9CC47543A7F6FAULL, 0x390C2BF856610972ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Kerpal_0006::kPhaseBConstants = {
    0xC6E69230C6BF983FULL,
    0xCEE4DF9DA5C1658BULL,
    0xAA02EEDE4E335A1EULL,
    0xC6E69230C6BF983FULL,
    0xCEE4DF9DA5C1658BULL,
    0xAA02EEDE4E335A1EULL,
    0x85CCFF5894DC8DC6ULL,
    0x5C203E4715F5C0C1ULL,
    0x07,
    0xC0,
    0x07,
    0xD8,
    0xAF,
    0x57,
    0xD4,
    0x79
};

const TwistDomainSaltSet TwistExpander_Kerpal_0006::kPhaseCSalts = {
    {
        {
            0xA8E9DC0B64B042DEULL, 0x2D4FAA4F0E5F5CE4ULL, 0x6A5A9D84017E398BULL, 0x13F83458B665A955ULL, 
            0xF03BF4004ABEC4D2ULL, 0xC8EF4480053B12A8ULL, 0x92BCB378D77919ABULL, 0x4883D91B09E654CDULL, 
            0xEE8BD9FF1C1A8CA5ULL, 0xB0E6C78506B282C6ULL, 0xA492AA4478BF0109ULL, 0x283E6D960D422465ULL, 
            0x3A24C5785DDC6AF0ULL, 0xD4933AF3FE9D5E10ULL, 0xC2BB9A5BAF70D515ULL, 0x6D713DD7E9D3D5B8ULL, 
            0x21FC65D19AB94BE7ULL, 0x79358626F7E70FBDULL, 0x5DFE63D7AD6FA558ULL, 0xBEB0DDA1F42943DCULL, 
            0x79378FDA10525D80ULL, 0x0F77A09C77DA72DAULL, 0xD42BBB964F2F4133ULL, 0x94B6D0E61DE3F51CULL, 
            0x735089B455C7F8D3ULL, 0x762F42259181E069ULL, 0x021036D29B3AA27CULL, 0xD88C4ACC8E7D23E6ULL, 
            0x0CB5ADEBCC083139ULL, 0x4059402CA1CF84A3ULL, 0xA4D715CFC67D3821ULL, 0xE2C5878BB5A33595ULL
        },
        {
            0xE52033B2FB16F04EULL, 0x0F26355577AB231EULL, 0xA5321D39E4246C11ULL, 0xBF88C2B58915A684ULL, 
            0xFD57982BEE699581ULL, 0x414E06954FE8FF0EULL, 0x8109E79768802E57ULL, 0x6908531A17F50AF6ULL, 
            0x0D29C88AF19B076EULL, 0x2E1CEE6BB2A90A9EULL, 0x91BF06749F0E6CE7ULL, 0xDCF1EAC8AF0CC72DULL, 
            0x9B7CB0FDA0F2377DULL, 0x6B50C37B463A0703ULL, 0xB1CBACDE5CC34B30ULL, 0xCCBCB6D2C0506756ULL, 
            0x7B635984D40D89C8ULL, 0xD0B0BD23C1AF564FULL, 0x8BB0F66BAB16FC79ULL, 0xEA8D3D7637F7BD96ULL, 
            0x933496E6BDF56448ULL, 0xEC653F39FE3E8A31ULL, 0xEFF45B65D400FA90ULL, 0xD1519B8E70EEB89EULL, 
            0x70CF0A361C13A42DULL, 0x98102D44A6A585D6ULL, 0x0C3480A80A4427A3ULL, 0xC4D866A011D889A4ULL, 
            0x341257FC0D9D9F7AULL, 0x711FADEB226C2D01ULL, 0x1136AE30E2430963ULL, 0xC6FB09844564E452ULL
        },
        {
            0xD308A2AE4893D0CCULL, 0x85827FA362265226ULL, 0x08221C1502767810ULL, 0x981AB4B3D06532F5ULL, 
            0xC9F7B3B4B769916CULL, 0x2FA9A3BE925D5899ULL, 0xD6C3A99C75FA76F7ULL, 0xFCD6FDCE5663B53DULL, 
            0xC4E4CE2D193A885AULL, 0x029A4DC291224BF5ULL, 0x54EB777E42D6D419ULL, 0x199C0DD42D43FC6CULL, 
            0xE907E542C5516F74ULL, 0xF976F5EC5EAFE210ULL, 0x16130AE6D9230FA0ULL, 0x5C03FBE50B33B016ULL, 
            0xAB9B9602D91F9B64ULL, 0x4A12849B282E5B8CULL, 0xDEC6D3B8F341EC18ULL, 0x9FDD7AA1CAFEF854ULL, 
            0x144D0636B5A907E6ULL, 0x4432B599880AB5ECULL, 0xF257DBBC920415A9ULL, 0xE95BBC4D42E5FA9DULL, 
            0xB475F075C675E0FDULL, 0xEDB0DB4FA7367654ULL, 0xB60E49A4425BD739ULL, 0x05CD3D82DE7152F4ULL, 
            0x281BAFC353F4B50CULL, 0x43E0B6A2B1DC03A3ULL, 0xF2BA903EB63585AFULL, 0x74B69B84DEB17119ULL
        },
        {
            0x1A873D3AAE5FAB34ULL, 0xB98205E21DA9E726ULL, 0xCE25A8F185E8F4DAULL, 0xB40393749BCFE0B4ULL, 
            0x1DE63F34685F4ECFULL, 0xF7F649B8D660206BULL, 0x3BC9A00469C8DCECULL, 0xF4D40F4A7C745A02ULL, 
            0x6DA0CFB0B579604EULL, 0xE45017B4BA096BC0ULL, 0xA5F315A52C00BFE0ULL, 0xCB230292B5BC3674ULL, 
            0xC2B23BCAC02D3F97ULL, 0xEFBD503A2D0144B4ULL, 0x7557C817BFE5156AULL, 0x5C8CE3060A4323E0ULL, 
            0x69BC7C49D54D693CULL, 0x33EC23407765E4BCULL, 0x7496E2C6E69A5D3DULL, 0x262C375F6636E442ULL, 
            0xCA408EED6A1B15EBULL, 0x0E2765083B6AC2ECULL, 0x7EF24D04D96BAFDCULL, 0x0ED28C2E0D23BE54ULL, 
            0x0BD9E653C21B6103ULL, 0x72253EF772D2C186ULL, 0xBEAEB522B37894D5ULL, 0xB5DBF25D999C0FB6ULL, 
            0x2A5BC52857F4C5FFULL, 0x21DD0DE16B80E5C4ULL, 0x60C0DB14AB8C2971ULL, 0xB0D1BDECC8337EAFULL
        },
        {
            0xA6B713E492D36542ULL, 0x13E0A27AB6587F59ULL, 0x23B0464184F03A73ULL, 0xE859FAF8579DAA71ULL, 
            0x9D6374B9F021660CULL, 0x98034983DD002431ULL, 0x7AC1C1AAB4ECAF29ULL, 0xC4F96545E6B7C75AULL, 
            0xE8E2D80A306DE36EULL, 0xCDE10FF1C4A77EC9ULL, 0x75979673FB148147ULL, 0x6EA21974608B500BULL, 
            0x5DA00DE66952E9A3ULL, 0xBC99F1F85D91DF88ULL, 0xF00B904455EEECECULL, 0x7A1D7CB9988EED2FULL, 
            0x35377BCE9059305DULL, 0x7A74D5338E925508ULL, 0x400D2015C235DD38ULL, 0x0160BAAE53CDE76AULL, 
            0xCF6104E02768879CULL, 0x59B279B69C3D574FULL, 0x9C9EAA31EB1E8F19ULL, 0xA3068DB1CB091576ULL, 
            0xDFC47FCDD853B35AULL, 0xD0CFE13DD999F1F2ULL, 0x7BC6ABBFE37352D0ULL, 0x4DEEB98DFA12536AULL, 
            0xCA727DF2F6C4658AULL, 0xEB351A55BCE97623ULL, 0x0522684F31374D7CULL, 0x32C5A1EE62840080ULL
        },
        {
            0x71AD1652DD5B2FD3ULL, 0xF1F24480D141EDBBULL, 0x01509040E9574C11ULL, 0xE2AE6350A68F119EULL, 
            0x3F4248CD13E267B2ULL, 0x3FAEAA223C45B412ULL, 0x93A29AB0D271EA9AULL, 0xFF563AA5EDE3D1A6ULL, 
            0x31F7A440A45FE47EULL, 0xF0B0449B9F2F5580ULL, 0xE63FB4C120E35804ULL, 0xC1331EC5A6687775ULL, 
            0xE3A7680154998BABULL, 0x0C6A0862E2889586ULL, 0x13C255F9BB6593A4ULL, 0x7C3AEDA2DC4BB466ULL, 
            0x2F630410CEE97613ULL, 0xB473B3F72AA2CCEEULL, 0xC1DEFA9A6CF4886AULL, 0xA816383DF0520056ULL, 
            0xD8C6D68AFABF6B76ULL, 0xA491F89CCD24C6CBULL, 0x4548E772ABE30818ULL, 0xF6174CF3B7E776EDULL, 
            0x0F1097A331CC9309ULL, 0x8A0ACE133041AFF6ULL, 0x3A38DE4C731A7A7DULL, 0xC3FF9FF2256A13C7ULL, 
            0xC13C0303415ED23FULL, 0x8F3681013DABD78CULL, 0x2DA6BCDB174FAC1EULL, 0xCC65ECA72CAEE705ULL
        }
    },
    {
        {
            0x2BC029BBB0491033ULL, 0x01006DD6B9E82FA1ULL, 0x7BB86671A3C05CDDULL, 0xE18EBBBFE4DB207CULL, 
            0x7B7866A9A5A375D3ULL, 0x28E661FFA78E9114ULL, 0x15BE2E351F5D056DULL, 0xA76AB3350A7B6718ULL, 
            0x2061E9D3C6506F60ULL, 0x8EE81F2E2263CA40ULL, 0x78D61AEF797730E1ULL, 0x4EDA8BFFB30B27A7ULL, 
            0x9E1B9C661C438569ULL, 0x9D8323A6F78A8E0BULL, 0x32F2E0586437827FULL, 0x15FCD2BCAE8A18FCULL, 
            0x0F59B4297EDC663CULL, 0xC45BAFE6B4222498ULL, 0x437D9297359D3FBAULL, 0xB35393E8CD8A38F3ULL, 
            0xEB8C7DDCDBCA3CDDULL, 0xD0DC163AC6FBC421ULL, 0x0F5515F8CF183BDCULL, 0x3272232FCF0939D6ULL, 
            0x9A36E21E55FBDCA8ULL, 0x0936E5E82022FCAFULL, 0x654EBF78481699AAULL, 0xFBE499E6E8081A7CULL, 
            0xEB9B93AB456990D3ULL, 0xBE6E4E4CF3A597FFULL, 0xBE8C940AFB4D1B89ULL, 0x5597AE6BF3A89A6EULL
        },
        {
            0xEBE0CA94970A1E9EULL, 0xC7DCBD1745176715ULL, 0x80171BF0A958DBCCULL, 0xCA13AEC753D159F0ULL, 
            0x7CF0248DFCDC3D78ULL, 0xF4E19EB69A5CBAC7ULL, 0x6329A9922C6325C1ULL, 0xF9B298DF54928B26ULL, 
            0xA2528FBFA1B84455ULL, 0x844D5BB82374DFEAULL, 0x7BBDF268BB1E4B63ULL, 0x92BE6C3CDF19921AULL, 
            0xE23A66A6AD1B2723ULL, 0x650ED18B269B183BULL, 0xA4E2D0B9C77794C6ULL, 0xEF9A9D476DA30F21ULL, 
            0xA60124FDFD875C3EULL, 0x743DDF9008B1F184ULL, 0xF5CEBBF0819207FBULL, 0x928667058F8BC447ULL, 
            0x6EC336177BB0D66AULL, 0x3F39D7509DFFE939ULL, 0x8DF618D5C27D6700ULL, 0xB587849B393DBC0EULL, 
            0xF07DB6387CC56D9BULL, 0x65599C1455EFD423ULL, 0xDB6AB0D835E6DE99ULL, 0x3E69ED46460E4925ULL, 
            0x1251E85B2D2894ACULL, 0xD44E230A1DFBEE46ULL, 0x51F18C4643061B5DULL, 0x7388B0BBAD0CA0DCULL
        },
        {
            0x7DAF1816A80ABE8DULL, 0x5C33EBD330DD4266ULL, 0xE5F1920720B6BED8ULL, 0xE0FD8C6D177CD8F5ULL, 
            0x5A02DB3333C7218AULL, 0x2C663423329066F6ULL, 0x7761EAC491342653ULL, 0x5799415D79E25C27ULL, 
            0xC6C8A7ED0E42EA6EULL, 0x2C5A4DDB60F650E3ULL, 0xA266119FED2DE351ULL, 0x6FF44CC8D28DCD94ULL, 
            0x56E4B9D4BFAA1770ULL, 0x74B645E631AC3A77ULL, 0xABE0B8CB5A6ADEA6ULL, 0xA2AD2CA4E63E7A32ULL, 
            0xD34E1290C1806839ULL, 0x591D48731DEB8B17ULL, 0x350905CBB5C6731FULL, 0xFA126E017A82A58FULL, 
            0x7DD272E7FCA70DBBULL, 0x1AD15977456A9D8DULL, 0xA572A1961FFBF52BULL, 0xEFB32E857E2F2E80ULL, 
            0x5E8B0605E50AA3E8ULL, 0x231B9836D570A986ULL, 0xC712E64DD81968EBULL, 0xFFA3449D1AF0A2ECULL, 
            0x93D72091721EB663ULL, 0x2DB1C20EF3C65A2FULL, 0x529FBFA6601E33F9ULL, 0x4E4220F259174BA8ULL
        },
        {
            0x5F683148F167AFD6ULL, 0x16171F38331D00AEULL, 0x14EFA98DBD9AB49EULL, 0xE925C4FA0F079A1BULL, 
            0x14D1604FB2C59AC0ULL, 0x17E5E21346A7893FULL, 0x4527B75D95ECA0B6ULL, 0x16020F8D1114489CULL, 
            0x8A7D90A0E672EA06ULL, 0x9856E30E936AFC55ULL, 0x3A95C46BA94AF835ULL, 0x88A6623132B97652ULL, 
            0x1E0A557757C999AFULL, 0xBEE5B1D57EF6218AULL, 0xD0E89C15E81B04EDULL, 0xE2309F3F20AECFE2ULL, 
            0xF352DF58F740A379ULL, 0x3A16C6528B41EFDAULL, 0xAD07EC2ACA691C3AULL, 0xEB05F45022334BCCULL, 
            0xDBA6C9C4F5BF0EF2ULL, 0x5C5BC4A4FBEAAFF6ULL, 0x4F69C2139C5264B7ULL, 0xFE15D7E9894A2D2BULL, 
            0x918237C381B34ADBULL, 0xA529164CAF9EB2C9ULL, 0xDC939EAAE8AAD7ADULL, 0xB1AA0BB44B53F721ULL, 
            0x1A1E33671FD44319ULL, 0x064010E8C9BC911DULL, 0xB7C58E1F4BF8B0FFULL, 0xFD7A2DEB4484554FULL
        },
        {
            0x8FADBB242C6FF75AULL, 0xC938370371BC9247ULL, 0x23CB732713DAB8BCULL, 0x8977997531E45E1CULL, 
            0x1BA67274F7CE205AULL, 0x2D9C00BDEAB4F561ULL, 0xA669B595A9F2B5FCULL, 0xF4B5208117BF9E5DULL, 
            0xC6A48C693CC32C0BULL, 0x578891C9CAC76A44ULL, 0xDD565D51212D5BE9ULL, 0x707773AEE1AD69C0ULL, 
            0x1F43A390ACEDF2E4ULL, 0x0ACF572CF94A18B3ULL, 0x17855F874AFDA413ULL, 0x2BD65BD9B6E1A879ULL, 
            0xF37355A3FD489153ULL, 0x4344F49FFD223EFEULL, 0x895C39FF527550D2ULL, 0x44068C33869D5E07ULL, 
            0xA974F4764FE63406ULL, 0x5D7603E81615B049ULL, 0xAC74C816C7AE0501ULL, 0xF0CCF7198D584576ULL, 
            0x45BF07F47B369A5DULL, 0x73BF365B2D3EFD70ULL, 0x49E0D498220BE6EEULL, 0x357981E3BC036426ULL, 
            0x74974CCF5AA30533ULL, 0x9A2C25A76058491DULL, 0xBD3A91F30A45CC86ULL, 0xE9CA42ED72B2931DULL
        },
        {
            0xC7ACF88F8CAA7A06ULL, 0x9386EC949C8BD243ULL, 0xC7AC129BDBE2932DULL, 0x84123E7D407D506CULL, 
            0x43C70D7F506F5CE6ULL, 0x23F04888640B53B2ULL, 0x3BFABA82503AC018ULL, 0xC37D126433F78F7FULL, 
            0x6C32B7571E610D6AULL, 0x99A54B58AF63023EULL, 0x5699EEB4F97CE8F9ULL, 0x3A98E71A7397BE43ULL, 
            0xC317DA349E88E6C9ULL, 0xF85CF184FA2B74F9ULL, 0xC7480F6C43F768C7ULL, 0x9073BD80AD6BF8F8ULL, 
            0x2F2922955392871FULL, 0x7053FE53313E71ECULL, 0x1EF8142BAAA903C6ULL, 0x58258526248C0648ULL, 
            0xE5C4A28CA082842CULL, 0xBC5C543661A21C5AULL, 0x7E614771E9300467ULL, 0x860155397BE13E4EULL, 
            0x0695DE5B26EB89CAULL, 0x2B07090CE3C5D51EULL, 0x90CF515E93F9E351ULL, 0x0255591811E163F0ULL, 
            0x193B458C54E47F31ULL, 0xA72E7B7FFCE36637ULL, 0xE3BFD43A3B6EF6A9ULL, 0xD832B68361D41C68ULL
        }
    },
    {
        {
            0x4EF6D29941048ACEULL, 0x80A171278A75F824ULL, 0x3EC4070A72620857ULL, 0x170D070EC99CD4C1ULL, 
            0xFF5962B755FB7A33ULL, 0x8EE095FD024F3B2BULL, 0xDF735CDB1F837E30ULL, 0x13F292973731EC02ULL, 
            0xBB56D14C8B93176EULL, 0xAF30F91FAC62E73EULL, 0x46EA04A521AC0D20ULL, 0xDDC8B1F74E12BB89ULL, 
            0xA1447E6EAA0186E1ULL, 0x973E98269D40E37AULL, 0x366136817F313CCFULL, 0x217B510F4A8B6D8BULL, 
            0xFECCE0CC6570B3F8ULL, 0xC8CA8B752D4C12F7ULL, 0x9647B29318D08E9DULL, 0xDE4806EE55920171ULL, 
            0xA66FD2A5E29E2C41ULL, 0x16444883B2D99859ULL, 0x61E8D1830897E4FDULL, 0x620B9C4E612885A9ULL, 
            0x389B49F3AE6158FBULL, 0x16D577C4A1A801D4ULL, 0xFE73697BB8C70BCCULL, 0xEBB27A17F2B7096EULL, 
            0x06A2BE1E1DAFBA1EULL, 0x72960BDF687CBD13ULL, 0xA6DFE3925A2C7E72ULL, 0x21EC49C3124D4344ULL
        },
        {
            0x83657EE95E6BD1FAULL, 0x9C47EB4CD3F701B2ULL, 0x0AE8B59035D0C914ULL, 0x4A71CEC1CFE6C3E3ULL, 
            0x540DFF7F0880B8AFULL, 0x9655F3E9F39D02C2ULL, 0x9527953813936C42ULL, 0x2EB05EE866509712ULL, 
            0x94DEEE0EAE462FC7ULL, 0x0CE11A805B69887BULL, 0xEA3F1C839A878877ULL, 0x73BEBA2D176275BFULL, 
            0x845CDF5399890D1DULL, 0x74775EA8F805673FULL, 0xF7D46775BA0405E3ULL, 0xE9331AB76733EEC9ULL, 
            0x1E705BB972F8054CULL, 0x60ABCDA21191D30DULL, 0xF4AFD2474F4D8237ULL, 0xEBAB7CBF41AD04D6ULL, 
            0x73A66C80FF95F74EULL, 0x958131DD9CF2C2E8ULL, 0xD7040D159B182326ULL, 0x82A0661A059A9F78ULL, 
            0x5D7C629DA2E01B30ULL, 0x1EC75F4997A71869ULL, 0x68C0D93F531D6105ULL, 0xF18396F686AF0DAEULL, 
            0xE2C31E908ADF20B4ULL, 0x75F7234F74A43278ULL, 0xCF5F09412D81CAC4ULL, 0x49444B793AF6C1DEULL
        },
        {
            0x3D75AE017A1EDCEAULL, 0x2155F4EC73113F16ULL, 0xFFBC119BCA08C599ULL, 0xF207CD0E36F12276ULL, 
            0x0CA034DA9DFD8AC3ULL, 0xB3ADAE0D26AAFA8EULL, 0x85EDA9FC91369122ULL, 0x2E97D8D4C39A257CULL, 
            0x3222EB212F05FAA6ULL, 0x1B8B796182D70D66ULL, 0x0E63CE9C0E29DEF4ULL, 0x8337570F8196E3A8ULL, 
            0xD344783E8D6C9314ULL, 0x8DAC7133A172D0C0ULL, 0x44EB03521FEAF091ULL, 0x8FC42AF2EDDD472CULL, 
            0xE79A3CB7C529A72FULL, 0xA54E60BFDB70714BULL, 0xAFB50DBCFFF5E462ULL, 0x9343B67BC3AED930ULL, 
            0x68196DB66C23C0BEULL, 0xE7DC2351395F0769ULL, 0x227325D5D12CD94FULL, 0xAFEC31DC0711AA69ULL, 
            0x8B0997BDF23EFC16ULL, 0x28C35A256D6A5A5CULL, 0xCDAE90AEC9EAF40BULL, 0x32963233B1E11A99ULL, 
            0x5A0D4C1AE2D0622CULL, 0x4A7C934CE6A69CE5ULL, 0x637B35CC985E31CAULL, 0x675412B0989A1C58ULL
        },
        {
            0xD0FDD517C60407E2ULL, 0xA9757F4862EBBC12ULL, 0x758491D61165B7CFULL, 0x4BC1CDD749FD3651ULL, 
            0x45A568ACAE814DE6ULL, 0x15575471A62064F3ULL, 0xB8124D42AAD56F0BULL, 0xB4BE83AF103DDCE3ULL, 
            0x953F229104CD78F3ULL, 0x45DD377775542716ULL, 0x79E594DA648495E5ULL, 0x9357DA4DBE731825ULL, 
            0xC93785E9F1D9D435ULL, 0xCFF29961E0349476ULL, 0x7FE32E42DAF74590ULL, 0x2C8D3FB801BF3CC4ULL, 
            0xC5DADB41F176BE67ULL, 0xDFDB308DCB8F9476ULL, 0x97588EEF42B5D4ABULL, 0x639852840FB4A1D7ULL, 
            0x5EBC29BD1EBB0971ULL, 0x172D9497231A5DE5ULL, 0x2C67E75AEFE2FC39ULL, 0x66F494E6BC56D174ULL, 
            0xC16209F833F1286AULL, 0x27E784BB13480E50ULL, 0xBA81122B8510E7A8ULL, 0xA7ADAE0E64499260ULL, 
            0x6265D8CBD3A274B5ULL, 0x182163993A425D78ULL, 0xF42344A3AFA3C48DULL, 0xEB5764BC9570A690ULL
        },
        {
            0x16AD0BA9C7D34863ULL, 0xADA9684EAE252326ULL, 0xB5308181B2878EFDULL, 0x24F4B0A0200494F4ULL, 
            0x595E053CC18BDF1CULL, 0xEDB21EA9147B57F8ULL, 0x9D8FF74477AC6E32ULL, 0x5940553B9F06C321ULL, 
            0x6FA9E80E17ADF8F0ULL, 0x72DE5C48DABB1977ULL, 0xA69DBF415FCDEA73ULL, 0xA498D8D513E38AF1ULL, 
            0x0B24BCB66F450EE7ULL, 0xF8E4301EB747DFC1ULL, 0xAA3B9150D732845EULL, 0x24D14FDE4DFAB198ULL, 
            0x266591620BC824B2ULL, 0xBD9B4D7B4A01D30CULL, 0x8F01F7C88D7DD48FULL, 0x74DEE40BB0727209ULL, 
            0xF7EB0E7F4EA8F1A4ULL, 0x92C4BEA6E2328CC9ULL, 0xD99DF0C8705BD21CULL, 0x10F9DFE706035E82ULL, 
            0xAABE70DE500FE4BEULL, 0xBB31910B2E618789ULL, 0xFE42F38C69AE3BE0ULL, 0xD1CA640D78B60A9CULL, 
            0xB3824B84A03331A0ULL, 0x86865CA3B715C0D0ULL, 0xBD392D86471A5D5CULL, 0x56229FC1A033F082ULL
        },
        {
            0x1CB9B159B07DB41FULL, 0x0A811164B8AA73F9ULL, 0x293FC61BACB8C083ULL, 0xAEEA842F9836A682ULL, 
            0x98B66474681CD3B8ULL, 0x57DD82068DC857A1ULL, 0x5C25EE9598ABE454ULL, 0x22E18E619BB7E693ULL, 
            0x5F921336CCA33890ULL, 0x82EC2ACB9DBEC1AFULL, 0xF73CCCE3268A39A8ULL, 0x7FB21C48C8CA421BULL, 
            0xF7F7A56B7C4CF825ULL, 0x599574689C09138BULL, 0x44B521B3CC932DAAULL, 0xF17BA5EDABE64492ULL, 
            0xD613C807741D22C9ULL, 0x3DAB1247430D3471ULL, 0xE29C6777AFB45E9FULL, 0x63B3070AF6A5DEDBULL, 
            0x6208C10537C04763ULL, 0xB63985A537F001DDULL, 0x50E74B840B32E028ULL, 0x7370EAABF4E8B8D3ULL, 
            0x5D0A641BD39B6C68ULL, 0x47B3B3FFA320EDCAULL, 0xEE8742B6AC0071F5ULL, 0xF1270853429FA211ULL, 
            0x0A72ECE349536B47ULL, 0xF55B5EB2B54F28E9ULL, 0x6987B2DBA779F740ULL, 0x04DF3B65A3541875ULL
        }
    }
};

const TwistDomainConstants TwistExpander_Kerpal_0006::kPhaseCConstants = {
    0x84126BEB9269385BULL,
    0xEE2ED8A5B40ECFECULL,
    0xA3A03ABC627A91E2ULL,
    0x84126BEB9269385BULL,
    0xEE2ED8A5B40ECFECULL,
    0xA3A03ABC627A91E2ULL,
    0x72F8CC1D6D3604AEULL,
    0x275D5A64F334D0C2ULL,
    0x4E,
    0x7B,
    0x34,
    0x94,
    0x35,
    0x04,
    0x83,
    0x02
};

